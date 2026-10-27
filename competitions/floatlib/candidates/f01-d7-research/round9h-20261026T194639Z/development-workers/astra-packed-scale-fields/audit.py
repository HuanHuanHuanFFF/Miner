"""Bounded read-only audit; writes this worker's evidence.json only. No Lean/CI/Git."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json
import re

HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p / 'competitions/floatlib/pins.json').is_file())
R19 = ROOT / 'competitions/floatlib/candidates/f01-d7-research/round9h-20261026T194639Z'
R18 = ROOT / 'competitions/floatlib/candidates/f01-d7-research/round11h-20261025T173831Z'
REVIEW = R19 / 'development-add-cost/actual-ci16-review'
RUNTIME = ROOT / 'competitions/floatlib/research/astra-collab-20261023-r7/upstream'
BASE = ROOT / 'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean'
RUN = ROOT / 'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40436948264'

def sha(p):
    return hashlib.sha256(p.read_bytes()).hexdigest()

def identity(p):
    return {'path': p.relative_to(ROOT).as_posix(), 'sha256': sha(p), 'bytes': p.stat().st_size}

def read(p):
    return p.read_text(encoding='utf-8-sig')

def excerpt(p, first, last):
    lines = read(p).splitlines()
    return {'source': identity(p), 'first_line': first, 'last_line': last,
            'text': '\n'.join(lines[first - 1:last])}

assert sha(BASE) == '622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
assert BASE.stat().st_size == 226829
assert 'def scaleTable : Array Float32 :=' in read(BASE)
index = json.loads(read(RUN / 'original-artifact-hashes.json'))
assert index['artifact']['workflow_run']['head_sha'] == 'a6c829564d4964eee6319b04141f8598a3e8e24c'
raw = RUN / index['directory']
data = raw / 'diagnostics/f01-d7-public-suite/public-suite/diagnostics/f01-r19-dev-add-cost1/add-cost'
c = data / 'actual-new-main.c'
asm = data / 'own-object-0-asm.txt'
assert sha(c) == '7e1a7c77085bd281e05bcb9d1eb314d1f8ee907235840f2223c64c4bc4507539'
assert sha(asm) == '91376197273d060a6bc6730126a18900beab15ff68a522e1dd327da5dc18fc8f'
for p in (c, asm):
    binding = index['files'][p.relative_to(raw).as_posix()]
    assert p.stat().st_size == binding['bytes'] and sha(p) == binding['sha256']
control_c = '\n'.join(read(c).splitlines()[87:421])
assert control_c.startswith('LEAN_EXPORT uint32_t lp_competition_r19CostControlAdd(')
assert control_c.count('lean_array_fget_borrowed(') == 2
assert control_c.count('lean_unbox_float32(') == 2
assert control_c.count('lean_uint32_to_float32(') == 2
assert control_c.count('lean_float32_mul(') == 2
control_asm = read(REVIEW / 'lp_competition_r19CostControlAdd.asm.txt')
assert control_asm.strip() in read(asm)
assert re.search(r'56:\s+mov\s+rax,QWORD PTR \[rax\+rcx\*8\+0x18\]', control_asm)
assert re.search(r'5b:\s+mulss\s+xmm1,DWORD PTR \[rax\+0x8\]', control_asm)
assert re.search(r'b6:\s+mov\s+rax,QWORD PTR \[rax\+rcx\*8\+0x18\]', control_asm)
assert re.search(r'bb:\s+mulss\s+xmm0,DWORD PTR \[rax\+0x8\]', control_asm)

runtime = RUNTIME / 'lean-lean.h'
runtime_receipt = RUNTIME / 'lean-native-sources.json'
r = next(x for x in json.loads(read(runtime_receipt))['sources'] if x['file'] == 'lean-lean.h')
assert r['commit'] == '293d5d0c0c3f3dded4688b3ccd6a33939ac5102b'
assert r['sha256'] == sha(runtime) == '982c731a1fbacc7688006f44f9f7af9d9e3e0247d310a728827f49e7f1466c13'
rt = read(runtime)
assert 'return lean_ctor_get_float32(o, 0);' in rt
assert 'lean_object * m_data[];' in rt

compact_dir = R19 / 'astra-workers/runtime-representation'
compact_kernel = compact_dir / 'Kernel-compact-scales.lean'
assert sha(compact_kernel) == '9c4e9505702231fdb93f47f8d767ba0b2b0c2ad7ec48d8894b5a53ba87657645'
compact_result = R19 / 'result-1927008-f01-r19-dev-compact-scales1-vs-f01-r15-dev-packed-b2-1.json'
cr = json.loads(read(compact_result))
assert cr['sha256'] == sha(compact_kernel) and cr['full_gate_both']
assert abs(cr['relative_normalized_ratio'] - 1.0296713645632587) < 1e-15
initialization = compact_dir / 'compact-40410895344/initialize_competition_Submission.c'
assert 'lean_mark_persistent(lp_competition_R2W01b_scaleTable);' in read(initialization)

old_field_review = ROOT / 'competitions/floatlib/candidates/f01-d7-research/round3h-20261025T091810Z/astra-workers/matrix-architecture/cost-review-401854.json'
old_field_excerpt = old_field_review.parent / 'cost-review-401854-excerpts/Submission_R15PackedB2_loop.txt'
field_binding = next(x for x in json.loads(read(old_field_review))['bindings'] if x['path'].endswith('candidate-generated-0.c'))
field_source = ROOT / field_binding['path']
assert sha(field_source) == field_binding['sha256']
assert read(old_field_excerpt).strip() in read(field_source)
assert 'lean_alloc_ctor(0, 0, 8)' in read(old_field_excerpt)
assert 'lean_ctor_get_float32(v_b_14239_, 0)' in read(old_field_excerpt)
assert 'lean_ctor_get_float32(v_b_14239_, 4)' in read(old_field_excerpt)

cost_data = json.loads(read(REVIEW / 'raw-recomputed.json'))
controls = [x for x in cost_data['samples'] if x['variant'] == 'control']
assert len(controls) == 4
totals = {op: sum(x['ns'][op] for x in controls) for op in ('add', 'mul', 'sum', 'bmm', 'whole')}
shares = {op: totals[op] / totals['whole'] for op in ('add', 'mul', 'sum', 'bmm')}

history = [compact_dir / 'COMPACT-SCALES.md', compact_dir / 'compact-40410895344/REVIEW.md',
           compact_result, R19 / 'astra-quantized-certificate.md',
           R18 / 'astra-workers/structural-frontier/direction.md',
           R18 / 'astra-workers/structural-frontier/core-interface.md']
evidence = {
    'at_utc': datetime.now(timezone.utc).isoformat(),
    'state': 'NO_GO_BEFORE_NEW_LEAN_OR_CI',
    'scope': 'Array of four-native-Float32 records initialized from original static scaleTable; not a universal no-speedup theorem',
    'parent': identity(BASE), 'pins': identity(ROOT / 'competitions/floatlib/pins.json'),
    'actual_ci16': {'run': 40436948264, 'source_commit': index['artifact']['workflow_run']['head_sha'],
                   'index': identity(RUN / 'original-artifact-hashes.json'), 'c': identity(c), 'asm': identity(asm),
                   'control_C_lines': [88, 421], 'control_asm': identity(REVIEW / 'lp_competition_r19CostControlAdd.asm.txt'),
                   'verified_C_sites': {'borrowed_array_read': 2, 'unbox_float32': 2, 'uint32_to_float32': 2, 'float32_scale_multiply': 2},
                   'ordinary_load_sequences': [['0x56: pointer slot', '0x5b: scalar memory operand'], ['0xb6: pointer slot', '0xbb: scalar memory operand']],
                   'limits': 'Saved measured C/ASM bytes checked; no local ELF or new execution. Static sites are not cycles.'},
    'runtime': {'receipt': identity(runtime_receipt), 'source': identity(runtime), 'commit': r['commit'], 'source_url': r['source_url']},
    'field_layout_precedent': {'review': identity(old_field_review), 'excerpt': identity(old_field_excerpt),
                             'raw_c': identity(field_source), 'limits': 'R16 exact native B2 scalar-field code, not new F4 compiled evidence'},
    'history': [identity(p) for p in history],
    'compact_negative': {'kernel': identity(compact_kernel), 'run': cr['run'], 'relative_normalized_ratio': cr['relative_normalized_ratio'],
                         'gain_p05': cr['gain_p05'], 'sample_role': cr['sample_role'],
                         'initialization_C': identity(initialization),
                         'difference': 'F4 avoids Float64 conversion and global validity; unlike FloatArray it retains a per-read array-element pointer load.'},
    'complete_cost_delta': {
        'deleted_per_hot_read': [],
        'retained_per_hot_read': ['global table address/access', 'array slot pointer load', 'native Float32 payload load',
                                  'mantissa UInt32-to-Float32 conversion', 'FP32 scale multiplication', 'original per-input eligibility'],
        'added_per_hot_read': ['quotient/remainder or equivalent bit index work', 'one-of-four dynamic field selection; final lowering UNKNOWN'],
        'possible_benefit': 'smaller accessed record/slot footprint, locality only; cache-miss or latency savings UNKNOWN',
        'startup': 'original table is consumed when constructing F4 and remains persistent under the audited initialization pattern; 128 extra records plus new array, 512 old-value loads and field writes',
        'other_retained': ['ADD/MUL arithmetic', 'result nonNaN checks', 'output codec', 'cold fallback', 'SUM/BMM order'],
    },
    'logical_requested_byte_model': {
        'assumptions': 'ELF64 8-byte object header, 24-byte Array header, exact capacity; before allocator rounding; not RSS or time',
        'old_512_float_boxes_and_slots': 24 + 512 * (8 + 4 + 8),
        'new_128_F4_records_and_slots': 24 + 128 * (8 + 16 + 8),
        'old_plus_new_if_original_retained': (24 + 512 * (8 + 4 + 8)) + (24 + 128 * (8 + 16 + 8)),
    },
    'coverage': {'ci16_control_ns_totals': totals, 'operation_shares': shares,
                 'add_mul_share': shares['add'] + shares['mul'],
                 'required_average_add_mul_reduction_for_10pct_whole': 0.10 / (shares['add'] + shares['mul']),
                 'eligible_dynamic_weight': 'UNKNOWN', 'scale_read_stall_fraction': 'UNKNOWN',
                 'limits': 'Descriptive complete-case time on four already-seen CI16 control blocks; excludes attribution to individual instructions.'},
    'proof_outline': {'status': 'PAPER_INTERFACE_ONLY_NOT_RUN',
        'idea': 'For j<512 use j=4*(j/4)+j%4 and four remainder cases. Array.ofFn projection and field beta reduction yield the identical original Float32 value, with no Float32/Float64 casts.',
        'gaps': 'No typed new Lean draft, no root audit, no replay, no generated F4 C, no new performance. Cost premise failed before implementing.'},
    'decision': 'Do not spend D CI slot on Array F4 solely for packing. Revisit only with evidence that scale-table cache stalls can pay new selection/index work, or a distinct legal representation that removes an actual dependent load.',
    'resources': {'started_utc': '2026-10-27T02:58:44Z', 'parent_deadline_utc': '2026-10-27T03:30:00Z',
                  'new_Lean_runs': 0, 'new_CI_runs': 0, 'new_candidates': 0,
                  'token_available': 'UNKNOWN', 'token_used': 'UNKNOWN', 'cached_input_tokens': 'UNKNOWN'},
    'read_boundary': 'Only named historical/pre-freeze sources and CI16; no D17/D18 or subsequent confirmation inputs/results inspected.',
    'excerpts': {'baseline_table': excerpt(BASE, 896, 914), 'runtime_scalar_projection': excerpt(runtime, 847, 850),
                 'runtime_box': excerpt(runtime, 3007, 3015), 'control_first_table_read': excerpt(c, 348, 361),
                 'control_second_table_read': excerpt(c, 403, 416)},
}
(HERE / 'evidence.json').write_text(json.dumps(evidence, ensure_ascii=False, indent=2) + '\n', encoding='utf-8')
print(json.dumps({'state': evidence['state'], 'parent': evidence['parent'], 'control_operation_shares': shares,
                  'requested_bytes': evidence['logical_requested_byte_model'], 'evidence': identity(HERE / 'evidence.json')}, ensure_ascii=False, indent=2))
