"""Construct one exact R12 cold-NaN asset reuse; no Git, CI or Lean execution."""
from pathlib import Path
from datetime import datetime, timezone
import argparse
import ast
import hashlib
import importlib.util
import json
import re

HERE = Path(__file__).resolve().parent
CANDIDATES = HERE.parents[1]
ROOT = HERE.parents[4]
TARGET = CANDIDATES / 'f01-d12-scalar-cold-nan-select'
BASE_SHA = '6c2d394dd34e8854d0d44d5d6605c194ecb27c152a1768d236481fc03fa4277d'
ASSET_SHA = '4a30c99f8230aae6d1b0cd238d1a6b1c9ac0aac0c448ca67d3005d3a6d00d528'


def sha(raw):
    return hashlib.sha256(raw).hexdigest()


def block(raw, begin, end):
    assert raw.count(begin) == raw.count(end) == 1
    start = raw.index(begin)
    stop = raw.index(end, start) + len(end)
    return raw[start:stop]


def build():
    base = (CANDIDATES / 'f01-d11-bmm-combined-classifier/Kernel.lean').read_bytes()
    asset = (CANDIDATES / 'f01-d7-scalar-nan-select/Kernel.lean').read_bytes()
    assert sha(base) == BASE_SHA and sha(asset) == ASSET_SHA
    result, operations = base, []

    def replace(before, after, name):
        nonlocal result
        assert result.count(before) == 1, name
        offset = result.index(before)
        old_sha = sha(result)
        result = result[:offset] + after + result[offset + len(before):]
        operations.append({'name': name, 'offset_in_previous_stage': offset,
            'before': before.decode('utf-8'), 'after': after.decode('utf-8'),
            'before_bytes': len(before), 'after_bytes': len(after),
            'before_sha256': sha(before), 'after_sha256': sha(after),
            'previous_source_sha256': old_sha, 'next_source_sha256': sha(result)})

    tuned = block(base, b'namespace TunedAdd\n', b'end TunedAdd\n')
    assert len(tuned) == 15524 and sha(tuned) == '04f2b622654ce1c70972fa600a27736339b74129a8cd5ca38c922cca6cef9743'
    assert (base.replace(tuned, b'')).count(b'TunedAdd.') == 2
    replace(b'  else TunedAdd.add x y\n', b'  else ScalarNaN.add x y\n', 'route original native add NaN-result branch')
    replace('  · exact TunedAdd.add_spec x y\n'.encode(), '  · exact ScalarNaN.add_spec x y\n'.encode(), 'original native add cold proof leaf')
    native_begin = b'@[inline] def nativeMul (x y : Binary32)'
    assert result.count(native_begin) == 1
    native_start = result.index(native_begin)
    native_stop = result.index(b'\n@[inline] def mul (x y : Binary32)', native_start)
    native = result[native_start:native_stop]
    assert native.count(b'else FastMul.mul x y') == native.count(b'exact FastMul.mul_spec x y') == 1
    edited_native = native.replace(b'else FastMul.mul x y', b'else ScalarNaN.mul x y').replace(
        b'exact FastMul.mul_spec x y', b'exact ScalarNaN.mul_spec x y')
    replace(native, edited_native, 'route original native multiply NaN-result branch and proof')
    replace(tuned, b'', 'reclaim isolated TunedAdd namespace; preserve surrounding notices')
    nan = block(asset, b'namespace DWordNaN\n', b'end DWordNaN\n')
    notice = b'/- Word NaN selection: fixed public binary32 fields and exact quieting/priority.\n   Newly integrated statement probe; NOT_RUN in the official compiler. -/\n'
    assert asset.count(notice + nan) == 1
    scalar = block(asset, b'namespace ScalarNaN\n', b'end ScalarNaN\n')
    original_scalar_sha = sha(scalar)
    scalar = scalar.replace(b'TunedAdd.add x y', b'ExecFloat.add x y').replace(
        b'TunedAdd.add_spec x y', b'ExecFloat.Proof.add_eq_spec x y')
    insertion = b'\n' + notice + nan + b'\n' + scalar + b'\n'
    replace(b'end R7Native\n', b'end R7Native\n' + insertion, 'reuse exact4a30 NaN proof/selection block and certified none fallbacks')
    inverse = result
    for op in reversed(operations):
        offset = op['offset_in_previous_stage']
        after = op['after'].encode('utf-8')
        assert inverse[offset:offset+len(after)] == after
        inverse = inverse[:offset] + op['before'].encode('utf-8') + inverse[offset+len(after):]
    assert inverse == base and len(result) <= 256000

    parser_path = CANDIDATES / 'f01-r8-combined-result-guard/build.py'
    spec = importlib.util.spec_from_file_location('r12_source_inventory', parser_path)
    parser = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(parser)
    before, after = parser.declarations(base.decode()), parser.declarations(result.decode())
    assert not {name: rows for name, rows in after.items() if len(rows) != 1}
    exports = ['Submission.' + name for name in ('add', 'add_spec', 'mul', 'mul_spec', 'sum', 'sum_spec', 'bmm', 'bmm_spec')]
    signatures = {}
    for name in exports:
        assert len(before[name]) == len(after[name]) == 1
        def signature(raw, row):
            return '\n'.join(raw.decode().splitlines()[row-1:]).split(':=', 1)[0]
        x, y = signature(base, before[name][0]), signature(result, after[name][0])
        assert x == y, name
        signatures[name] = {'type_unchanged': True, 'sha256': sha(x.encode())}
    for namespace in ('LowScale', 'R7SinglePassSum', 'NativeFinal', 'R11CrossRows', 'DirectContinuous'):
        first = ('namespace ' + namespace + '\n').encode()
        last = ('end ' + namespace + '\n').encode()
        if base.count(first) == base.count(last) == 1:
            assert block(base, first, last) == block(result, first, last), namespace
    # All code after the unchanged public mul dispatcher is byte-identical.
    tail_start = b'@[inline] def mul (x y : Binary32) : Binary32 :=\n  let ex := FloatLib.Floats.Formats.BinaryInterchange.Model.NativeBinary32.expField x.raw.1'
    assert base.count(tail_start) == result.count(tail_start) == 1
    assert base[base.index(tail_start):] == result[result.index(tail_start):]
    gate = ROOT / 'competitions/floatlib/research/astra-collab-20261023-r7/upstream/gate-4b7e838.py'
    assert sha(gate.read_bytes()) == '1eb74ef7479b0023c721e776cc5e4073af21c6662b4afffcf16a48a124d27194'
    tree = ast.parse(gate.read_text())
    assignment = lambda name: next(n for n in tree.body if isinstance(n, ast.Assign) and any(isinstance(t, ast.Name) and t.id == name for t in n.targets))
    text = result.decode()
    assert not re.compile(ast.literal_eval(assignment('BANNED').value.args[0])).search(text)
    attrs = ast.literal_eval(assignment('ATTRIBUTES').value)
    env = {'re': re, 'OPTIONS': ast.literal_eval(assignment('OPTIONS').value)}
    node = next(n for n in tree.body if isinstance(n, ast.FunctionDef) and n.name == 'options')
    exec(compile(ast.Module(body=[node], type_ignores=[]), str(gate), 'exec'), env)
    assert env['options'](text) is None
    assert [line for line in text.splitlines() if re.search(r'\bimport\b', line)] == ['import ContractTensor']
    for group in re.findall(r'@\[([^\]]*)\]', text):
        for item in group.split(','):
            assert item.split()[-1] in attrs
    report = {'base_sha256': BASE_SHA, 'asset_sha256': ASSET_SHA, 'candidate_sha256': sha(result),
        'candidate_bytes': len(result), 'headroom_bytes': 256000-len(result), 'operations': operations,
        'inverse_parent_sha256': sha(inverse), 'inverse_parent_exact': True,
        'reused_DWordNaN_sha256': sha(nan), 'reused_DWordNaN_bytes': len(nan),
        'original_ScalarNaN_sha256': original_scalar_sha, 'adapted_ScalarNaN_sha256': sha(scalar),
        'exported_types': signatures, 'entire_tail_from_original_mul_dispatcher_unchanged': True,
        'static_original_policy': 'PASS', 'declaration_inventory': 'PASS_STATIC_ONLY',
        'removed_declarations': sorted(set(before)-set(after)), 'new_declarations': sorted(set(after)-set(before)),
        'scope': 'Static exact source/inverse/capacity/type/policy checks only; no Lean, gate or performance result.'}
    return result, report


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--write', action='store_true')
    args = ap.parse_args()
    raw, report = build()
    manifest = {'candidate': TARGET.name, 'candidate_file': 'Kernel.lean', 'candidate_sha256': sha(raw),
        'candidate_bytes': len(raw), 'created_at_utc': datetime.now(timezone.utc).isoformat(),
        'parent': 'f01-d11-bmm-combined-classifier', 'parent_sha256': BASE_SHA,
        'asset': 'f01-d7-scalar-nan-select', 'asset_sha256': ASSET_SHA,
        'mechanism': 'Reuse existing4a30 rawChoose/selected_add/selected_mul only after current native-result NaN guard. None keeps certified add/mul fallbacks. Remove isolated TunedAdd and use official ExecFloat.add for add none capacity; preserve current numeric/native finite expressions and complete LowScale/mul/sum/BMM tail.',
        'new_mechanism': False, 'decision_evidence': {'run': 40067286343, 'source_commit': 'c2d92ffb',
            'MainFull_c_sha256': '9e8d7b111ac7a28b5497c6d3fc0b1e30cca28eb26511d3c1106609bb96873621',
            'MainFull_object_sha256': 'e1685ee1b3766c4956ab639928f83f63c7ba4848394aaa4e469254387eddee41'},
        'proof_route': 'Exact old selected-word theorems; rawChoose=some supplies its own premise. None uses ExecFloat.Proof.add_eq_spec or FastMul.mul_spec. No result-NaN implies raw-exp255 assumption.',
        'checks': {k: report[k] for k in ('inverse_parent_exact', 'exported_types', 'entire_tail_from_original_mul_dispatcher_unchanged', 'static_original_policy', 'declaration_inventory')},
        'validation_mode': 'statement first, then original full gate', 'proof_status': 'NOT_RUN_EXACT_INTEGRATION',
        'leanchecker': 'NOT_RUN', 'axiom_audit': 'NOT_RUN', 'checksum': 'NOT_RUN', 'full_gate': 'NOT_RUN',
        'codegen': 'NOT_RUN_EXACT_CANDIDATE', 'performance': 'UNKNOWN', 'state': 'READY_FOR_STATEMENT',
        'attribution': 'All existing parent legal/author notices retained outside exact isolated TunedAdd namespace. Exact old Word NaN selection notice and DWordNaN block retained. FloatLib Team MIT public raw/model source and prior4a30 glue are reused, not a new invention.',
        'formal_submission': 'NOT_SUBMITTED', 'ci_owner': 'Root', 'build_script_sha256': sha(Path(__file__).read_bytes())}
    if args.write:
        TARGET.mkdir(exist_ok=False)
        (TARGET / 'Kernel.lean').write_bytes(raw)
        (TARGET / 'manifest.json').write_text(json.dumps(manifest, ensure_ascii=False, indent=2)+'\n', encoding='utf-8', newline='\n')
        (TARGET / 'exact-inverse.json').write_text(json.dumps(report, ensure_ascii=False, indent=2)+'\n', encoding='utf-8', newline='\n')
    else:
        assert (TARGET / 'Kernel.lean').read_bytes() == raw
        assert json.loads((TARGET / 'manifest.json').read_bytes())['candidate_sha256'] == sha(raw)
    print(json.dumps({'candidate': TARGET.name, 'sha256': sha(raw), 'bytes': len(raw), 'static_checks': 'PASS',
                      'actual_Lean': 'NOT_RUN', 'full_gate': 'NOT_RUN', 'performance': 'UNKNOWN'}, indent=2))


if __name__ == '__main__':
    main()
