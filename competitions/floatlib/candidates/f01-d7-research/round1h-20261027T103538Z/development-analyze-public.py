"""Authenticate one new run with the unchanged guard; screen against retained B2."""
from pathlib import Path
from datetime import datetime, timezone
import argparse
import importlib.util
import json
import random
import statistics

HERE=Path(__file__).resolve().parent
ROOT=HERE.parents[4]
OWN=HERE.parent
BASE='f01-r15-dev-packed-b2-1'
CONTROL='f01-r8-combined-result-guard'


def main():
    ap=argparse.ArgumentParser();ap.add_argument('--run',type=int,required=True);ap.add_argument('--candidate',required=True);a=ap.parse_args()
    source=OWN/'round9h-20261026T194639Z/adoption-guard.py'
    spec=importlib.util.spec_from_file_location('unchanged_r19_guard',source)
    guard=importlib.util.module_from_spec(spec);spec.loader.exec_module(guard)
    packet=guard.load_run(ROOT,OWN,a.run,[BASE,CONTROL,a.candidate])
    assert packet['hosted_ubuntu24'] and not packet['codegen_present']
    assert packet['plan']['selection_policy']==guard.SELECTION_POLICY
    candidate,baseline=(packet['verdicts'][n] for n in (a.candidate,BASE))
    for v in (candidate,baseline):
        assert v['passed'] and v['mode']=='gate' and v['stage']=='score'
        assert v['seed']==packet['seed'] and len(v['rounds'])==25
        assert v['verifier_fingerprint']==v['verifier_fingerprint_end']
    assert candidate['verifier_fingerprint']==baseline['verifier_fingerprint']
    ratios=[[sub/inc for inc,sub in v['rounds']] for v in (candidate,baseline)]
    rng=random.Random(guard.SELECTION_POLICY['bootstrap_seed']);gains=[]
    for _ in range(guard.SELECTION_POLICY['bootstrap_samples']):
        medians=[statistics.median(values[rng.randrange(25)] for _ in range(25)) for values in ratios]
        gains.append(1-medians[0]/medians[1])
    gains.sort();k=.05*(len(gains)-1);lo=int(k);p05=gains[lo]+(gains[lo+1]-gains[lo])*(k-lo)
    relative=candidate['ratio']/baseline['ratio'];work=packet['cell_work']
    operations={}
    for op in ('add','mul','sum','bmm'):
        normalized=[]
        for v in (candidate,baseline):
            cells={n:c for n,c in v['classes'].items() if n.startswith(op+':')}
            normalized.append(sum(c['submission_ns']*work[n] for n,c in cells.items())/sum(c['incumbent_ns']*work[n] for n,c in cells.items()))
        operations[op]=normalized[0]/normalized[1]
    result={'at_utc':datetime.now(timezone.utc).isoformat(),'run':a.run,'seed':packet['seed'],
        'candidate':a.candidate,'candidate_sha256':packet['kernel_hashes'][a.candidate],
        'baseline':BASE,'baseline_sha256':packet['kernel_hashes'][BASE],
        'sample_role':packet['plan'].get('sample_role'),'relative_normalized_ratio':relative,
        'gain_p05':p05,'per_operation_normalized':operations,
        'local_discovery_screen_passed':relative<=.97 and p05>0,
        'selection_policy':guard.SELECTION_POLICY,'evidence':packet['evidence'],
        'scope':'One authenticated complete public run, original25 rounds. Same-source official336 is separate. New-runner frozen A+B still required for retention; no private ranking prediction.'}
    dest=HERE/f'development-result-{a.run}-{a.candidate}.json'
    dest.write_bytes((json.dumps(result,indent=2)+'\n').encode())
    print(json.dumps({k:result[k] for k in ('run','candidate','relative_normalized_ratio','gain_p05','per_operation_normalized','local_discovery_screen_passed')}))


if __name__=='__main__':
    main()
