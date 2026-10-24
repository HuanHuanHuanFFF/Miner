"""Recheck the old exact scalar numeric-converter negative and current new domain."""
from pathlib import Path
import hashlib
import json

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[4]
OLD = ROOT / 'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/39746211363/download-9ecc44efe1974c5f9eec1ce22ec302f6'


def sha(raw):
    return hashlib.sha256(raw).hexdigest()


def main():
    source_path = ROOT / 'competitions/floatlib/candidates/f01-d4-scalar-decode/Kernel.lean'
    source = source_path.read_bytes()
    assert sha(source) == 'a7dca716f0076511875209b043f761559235a74b5729227916360e4d9373e7e9'
    assert (OLD/'inputs/f01-d4-scalar-decode/Kernel.lean').read_bytes() == source
    assert b'LowScale' not in source
    verdicts = {}
    for name in ('f01-d4-scalar-decode','f01-d3-final-package'):
        raw = (OLD/(name+'-verdict.json')).read_bytes()
        v = json.loads(raw)
        assert v['passed'] and v['mode']=='gate' and v['stage']=='score' and v['seed']==504 and len(v['rounds'])==25
        verdicts[name] = {'raw':raw,'v':v}
    candidate, parent = (verdicts[n]['v'] for n in ('f01-d4-scalar-decode','f01-d3-final-package'))
    rows = {}
    for name in ('mul:near-one','mul:spread','mul:tiny'):
        c,p = candidate['classes'][name],parent['classes'][name]
        rows[name]={'raw_ratio':c['submission_ns']/p['submission_ns'],
                    'reference_normalized_ratio':c['ratio']/p['ratio']}
    names = tuple(rows)
    total = lambda v,key:sum(v['classes'][n][key] for n in names)
    normalized = (total(candidate,'submission_ns')/total(parent,'submission_ns'))/(total(candidate,'incumbent_ns')/total(parent,'incumbent_ns'))
    current = (ROOT/'competitions/floatlib/candidates/f01-d11-bmm-combined-classifier/Kernel.lean').read_bytes()
    assert b'if ex + ey < (128 : UInt32) then LowScale.mul x y else nativeMul x y' in current
    excluded = all(ex+ey<128 for ex in range(55,66) for ey in range(50,61))
    assert excluded
    report = {'old_run':39746211363,'old_suite':'legacy12','current_suite':'public-v2; no old timing inheritance',
        'old_scalar_source_sha256':sha(source),'old_source_contains_LowScale':False,
        'verdict_sha256':{n:sha(r['raw']) for n,r in verdicts.items()},'all_original_full25':True,
        'mul_per_class':rows,'mul_all_three_reference_normalized':normalized,
        'old_change_scope':'Both scalar add and public mul input converters only; exact same R2W01b per-input converter. No LowScale predispatch existed.',
        'current_new_condition':'Only nativeMul changes after current ex+ey<128 LowScale guard. The full old tiny input exponent product domain55..65 x50..60 has sums105..125, so it never reaches modified nativeMul.',
        'old_tiny_full_input_domain_excluded':excluded,'new_decoder':False,
        'decision':'ONE_CONTROLLED_REVISIT_WITH_NEW_DOMAIN_NOT_A_PARAMETER_GRID',
        'candidate':'f01-d12-mul-existing-convert','sha256':'59de0e17223abebdd802bba98347ad8a4a7d6e90bfdca5ffd94bed3ad7005ce4',
        'new_performance':'UNKNOWN','new_Lean_full_gate':'NOT_RUN'}
    (HERE/'scalar-mul-convert-history.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf-8',newline='\n')
    print(json.dumps(report,indent=2))


if __name__=='__main__':
    main()
