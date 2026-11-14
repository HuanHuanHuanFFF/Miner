from pathlib import Path
from hashlib import sha256
from datetime import datetime, timezone
import importlib.util
import json

here = Path(__file__).resolve().parent
repo = next(p for p in here.parents if (p / 'AGENTS.md').is_file())
round_dir = here.parents[1]
oracle_path = repo / 'competitions/floatlib/research/astra-collab-20261023-r7/nonfinite-oracle.py'
assert sha256(oracle_path.read_bytes()).hexdigest() == '3dfaeec2bde1364a4f06abd292f0ba265376da79e678d3827aa88bd33219ad72'
spec = importlib.util.spec_from_file_location('old_word_oracle', oracle_path)
oracle = importlib.util.module_from_spec(spec)
spec.loader.exec_module(oracle)
mask = (1 << 32) - 1

def fast(w):
    a = w & 0x7fffffff
    return 0x0bffffff <= ((a - 1) & mask) and a < 0x7f800000

def pair(a, b):
    return ((((a & 0x7fffffff) - 0x20000000) & mask) |
            (((b & 0x7fffffff) - 0x20000000) & mask)) < 0x40000000

def table(w):
    e = (w >> 23) & 255
    scale = (w & 0x80000000) | (((e - 23) << 23) if 24 <= e <= 254 else 0)
    mantissa = oracle.rounded((w & 0x7fffff) | 0x800000, 0)
    return oracle.native_model(oracle.mul, mantissa, scale)

cases = [
    ('zero_pp', 0, 0), ('zero_pn', 0, 0x80000000),
    ('zero_np', 0x80000000, 0), ('zero_nn', 0x80000000, 0x80000000),
    ('negative_zero_negative_one', 0x80000000, 0xbf800000),
    ('positive_zero_negative_one', 0, 0xbf800000),
    ('subnormal_pair', 1, 1), ('largest_subnormal', 0x007fffff, 0x3f800000),
    ('normal_to_subnormal_mul', 0x00800000, 0x3f000000),
    ('E23_cancel_to_subnormal', 0x0b800001, 0x8b800000),
    ('E24_cancel_to_min_normal', 0x0c000001, 0x8c000000),
    ('E24_lower', 0x0c000000, 0x3f800000),
    ('E63_lower_pair_miss', 0x1f800000, 0x1f800000),
    ('E64_lower_pair_hit', 0x20000000, 0x20000000),
    ('E64_negative_pair_hit', 0xa0000000, 0x20000000),
    ('E191_upper_pair_hit', 0x5fffffff, 0x5fffffff),
    ('E192_pair_miss', 0x60000000, 0x3f800000),
    ('E254_add_overflow', 0x7f7fffff, 0x7f7fffff),
    ('ordinary_cancel', 0x3f800000, 0xbf800000),
    ('opposite_infinities', 0x7f800000, 0xff800000),
    ('infinity_zero', 0x7f800000, 0),
    ('qnan_payload_left', 0x7fc00001, 0x3f800000),
    ('negative_qnan_payload', 0xffc00042, 0x3f800000),
    ('snan_before_qnan', 0x7f800123, 0x7fc00456),
    ('qnan_before_snan', 0x7fc00456, 0xff800123),
]
rows = []
for name, a, b in cases:
    for op_name, op, hit in [('add', oracle.add, fast(a) and fast(b)), ('mul', oracle.mul, pair(a, b))]:
        exact = op(a, b)
        hot = oracle.native_model(op, table(a), table(b))
        result = hot if hit else exact
        assert result == exact
        if hit:
            assert not oracle.nan(a) and not oracle.nan(b) and not oracle.nan(hot)
        rows.append({'name': name, 'op': op_name, 'a': f'{a:08x}', 'b': f'{b:08x}',
                     'hit': hit, 'exact': f'{exact:08x}', 'guarded_model': f'{result:08x}',
                     'forced_bare_table': f'{hot:08x}',
                     'unconditional_native_import': f'{oracle.native_model(op,a,b):08x}'})
targets = {
    'mul_runtime': round_dir / 'development-nativecold/NativeCold.lean.inc',
    'add_runtime': round_dir / 'development-nativecold/NativeColdAdd.lean.inc',
    'B2': repo / 'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean',
    'R11_pair_interface': repo / 'competitions/floatlib/candidates/f01-d11-scalar-normal-band/normal-band-block.lean',
    'R19_pair_interface': repo / 'competitions/floatlib/candidates/f01-d7-research/round9h-20261026T194639Z/astra-workers/runtime-representation/postguard-frontier/Postguard-mul.lean.inc',
}
bindings = {k: {'path': p.relative_to(repo).as_posix(), 'sha256': sha256(p.read_bytes()).hexdigest(), 'bytes': p.stat().st_size} for k, p in targets.items()}
assert bindings['mul_runtime']['sha256'] == 'e3b93d3ab1383ce09da56dbf7b203760c037b8d779fc2aedae9e9b704fa1ce13'
assert bindings['add_runtime']['sha256'] == '21cd91284ee5bc31fed0e7aaa3b1cf35e6a705cbe2e680d8095baf2388551f50'
out = {'checked_utc': datetime.now(timezone.utc).isoformat(), 'source_bindings': bindings,
       'oracle_sha256': sha256(oracle_path.read_bytes()).hexdigest(), 'cases': len(rows),
       'mismatches': 0, 'rows': rows,
       'scope': '50 fixed integer/source-word boundary witnesses, not native execution, Lean or performance. No domain sweep or new runtime.'}
(here / 'boundary-witnesses.json').write_text(json.dumps(out, ensure_ascii=False, indent=2) + '\n', encoding='utf-8')
print(json.dumps({'cases': len(rows), 'mismatches': 0, 'bindings': bindings}, ensure_ascii=False))
