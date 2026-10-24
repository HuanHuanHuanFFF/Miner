"""One controlled existing-converter revisit on exact6c nativeMul only."""
from pathlib import Path
from datetime import datetime, timezone
import argparse
import hashlib
import importlib.util
import json

HERE = Path(__file__).resolve().parent
CANDIDATES = HERE.parents[1]
TARGET = CANDIDATES / 'f01-d12-mul-existing-convert'
BASE_SHA = '6c2d394dd34e8854d0d44d5d6605c194ecb27c152a1768d236481fc03fa4277d'


def sha(raw):
    return hashlib.sha256(raw).hexdigest()


def build():
    base = (CANDIDATES / 'f01-d11-bmm-combined-classifier/Kernel.lean').read_bytes()
    assert sha(base) == BASE_SHA
    start = base.index(b'@[inline] def nativeMul (x y : Binary32)')
    stop = base.index(b'\n@[inline] def mul (x y : Binary32)', start)
    before = base[start:stop]
    old_result = b'  let result := ExecFloat.Binary.toFloat32 x * ExecFloat.Binary.toFloat32 y\n'
    new_result = b'  let result := R2W01b.convert x.raw.1 * R2W01b.convert y.raw.1\n'
    assert before.count(old_result) == 1
    after = before.replace(old_result, new_result)
    old_leaf = '''  · rename_i hn
    have hi := NotNaNProbe.mul_inputs _ _ ((R7W04.nonNaN_eq_true_iff _).mp hn)
    rw [R7Native.ofFloat32Mul _ _ hi.1 hi.2,
'''.encode()
    new_leaf = '''  · rename_i hn
    rw [R2W01c.convert_eq, R2W01c.convert_eq] at hn ⊢
    change R7W04.nonNaN (ExecFloat.Binary.toFloat32 x * ExecFloat.Binary.toFloat32 y) = true at hn
    have hi := NotNaNProbe.mul_inputs _ _ ((R7W04.nonNaN_eq_true_iff _).mp hn)
    change ExecFloat.Binary.ofFloat32 (ExecFloat.Binary.toFloat32 x * ExecFloat.Binary.toFloat32 y) = _
    rw [R7Native.ofFloat32Mul _ _ hi.1 hi.2,
'''.encode()
    assert after.count(old_leaf) == 1
    after = after.replace(old_leaf, new_leaf)
    result = base[:start] + after + base[stop:]
    assert len(result) <= 256000
    inverse = result[:start] + before + result[start+len(after):]
    assert inverse == base
    parser_path = CANDIDATES / 'f01-r8-combined-result-guard/build.py'
    spec = importlib.util.spec_from_file_location('r12_mul_inventory', parser_path)
    parser = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(parser)
    old_decls, new_decls = parser.declarations(base.decode()), parser.declarations(result.decode())
    assert set(old_decls) == set(new_decls) and all(len(v) == 1 for v in new_decls.values())
    exports = ['Submission.' + x for x in ('add', 'add_spec', 'mul', 'mul_spec', 'sum', 'sum_spec', 'bmm', 'bmm_spec')]
    checks = {}
    for name in exports:
        def signature(raw, line):
            return '\n'.join(raw.decode().splitlines()[line-1:]).split(':=',1)[0]
        assert signature(base, old_decls[name][0]) == signature(result, new_decls[name][0])
        checks[name] = 'TYPE_UNCHANGED'
    for namespace in ('TunedAdd', 'LowScale', 'R2W01b', 'R2W01c'):
        begin, end = ('namespace '+namespace+'\n').encode(), ('end '+namespace+'\n').encode()
        lo, hi = base.index(begin), base.index(end)+len(end)
        assert base[lo:hi] in result
    assert base[:start] == result[:start] and base[stop:] == result[start+len(after):]
    report = {'base_sha256': BASE_SHA, 'candidate_sha256': sha(result), 'candidate_bytes': len(result),
        'headroom_bytes': 256000-len(result), 'byte_interval_in_parent': [start,stop],
        'before': before.decode(), 'after': after.decode(), 'before_sha256': sha(before), 'after_sha256': sha(after),
        'inverse_parent_exact': True, 'inverse_parent_sha256': sha(inverse),
        'all_other_parent_bytes_unchanged': True, 'declaration_inventory_unchanged_unique': True,
        'public_types': checks, 'runtime_substitution_count': 2, 'new_runtime_guards': 0,
        'old_negative': {'candidate': 'f01-d4-scalar-decode', 'sha256': 'a7dca716f0076511875209b043f761559235a74b5729227916360e4d9373e7e9',
            'run':39746211363, 'mul_normalized_ratio':1.0374780640, 'near_one':.915636,'spread':1.046081,'tiny':1.061716},
        'new_condition': 'OldR4 scalar mul had no LowScale predispatch. Current6c ex+ey<128 LowScale excludes old tiny input pairs (ex55..65,ey50..60,sums105..125) from modified nativeMul. Current native-result guard is also retained instead of old finite-input guard. This is a controlled revisit, not a new decoder.',
        'actual_machine_target': 'Current6c actual public MainFull lam3 native branch has two of_bits foreign relocations and one float spill. When each existing converter takes its numeric branch, their removal is testable; foreign/spill removal and gain are NOT_ASSUMED.',
        'proof': 'Existing all-input R2W01c.convert_eq rewrites result guard and output before the original native-mul proof. Four full specs still need original gate acceptance.',
        'acceptance': 'NOT_RUN', 'performance': 'UNKNOWN'}
    return result, report


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--write', action='store_true')
    args = ap.parse_args()
    raw, report = build()
    manifest = {'candidate': TARGET.name, 'candidate_file':'Kernel.lean', 'candidate_sha256':sha(raw),
        'candidate_bytes':len(raw), 'created_at_utc':datetime.now(timezone.utc).isoformat(),
        'parent':'f01-d11-bmm-combined-classifier', 'parent_sha256':BASE_SHA,
        'mechanism':'Only replace nativeMul two toFloat32 inputs with existing proven per-input R2W01b.convert. No joint guard/new band; add,TunedAdd,LowScale,NaN-result guard/FastMul fallback and all tensor bytes retained.',
        'new_mechanism':False, 'history':report['old_negative'], 'revisit_condition':report['new_condition'],
        'checks':{k:report[k] for k in ('inverse_parent_exact','all_other_parent_bytes_unchanged','declaration_inventory_unchanged_unique','public_types')},
        'proof_route':report['proof'], 'state':'READY_FOR_STATEMENT', 'proof_status':'NOT_RUN_EXACT_INTEGRATION',
        'validation_mode':'statement first, then original full gate', 'leanchecker':'NOT_RUN','axiom_audit':'NOT_RUN',
        'checksum':'NOT_RUN','full_gate':'NOT_RUN','codegen':'NOT_RUN_EXACT_CANDIDATE','performance':'UNKNOWN',
        'formal_submission':'NOT_SUBMITTED','ci_owner':'Root','build_script_sha256':sha(Path(__file__).read_bytes()),
        'attribution':'All parent notices/source bytes outside nativeMul and its proof preserved. Existing converter/proof is reused; no source or historical negative claim is renamed as new.'}
    if args.write:
        TARGET.mkdir(exist_ok=False)
        (TARGET/'Kernel.lean').write_bytes(raw)
        (TARGET/'manifest.json').write_text(json.dumps(manifest,ensure_ascii=False,indent=2)+'\n',encoding='utf-8',newline='\n')
        (TARGET/'exact-inverse.json').write_text(json.dumps(report,ensure_ascii=False,indent=2)+'\n',encoding='utf-8',newline='\n')
    else:
        assert (TARGET/'Kernel.lean').read_bytes()==raw
        assert json.loads((TARGET/'manifest.json').read_bytes())['candidate_sha256']==sha(raw)
    print(json.dumps({'candidate':TARGET.name,'sha256':sha(raw),'bytes':len(raw),'static_checks':'PASS',
        'actual_Lean':'NOT_RUN','full_gate':'NOT_RUN','performance':'UNKNOWN'},indent=2))


if __name__=='__main__':
    main()
