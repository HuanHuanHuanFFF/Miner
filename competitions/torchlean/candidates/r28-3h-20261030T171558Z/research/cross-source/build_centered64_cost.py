"""Same centered cost mechanism, sharp valid unsigned64 product guard<=62.

Does not modify the earlier <=61 diagnostic. Not a second independent route;
if the coordinator has not frozen that earlier diagnostic, this is the preferred
single cost discriminator. Both are native-only and lack Submission.correct.
"""
from pathlib import Path
import argparse
from datetime import datetime,timezone
import hashlib
import json
from build_centered36_cost import build,BASE

HERE=Path(__file__).resolve().parent
PREVIOUS="51fd24bd4597980fe64ae9eb0b7cf13147cefc6deb1e16f5e67a9fcc2ef1fc48"


def transform(raw,submission=36,variant='centered64-cost'):
    assert submission==36 and variant=='centered64-cost'
    previous,_=build(raw)
    assert hashlib.sha256(previous).hexdigest()==PREVIOUS
    text=previous.decode('utf-8')
    patterns=['cx1.2.2+cw.2.2<=61','cx2.2.2+cw.2.2<=61','ca.2.2+cb.2.2<=61']
    for pattern in patterns:
        assert text.count(pattern)==1
        text=text.replace(pattern,pattern[:-2]+'62')
    result=text.encode('utf-8')
    assert len(result)<=256000
    return result


def main():
    p=argparse.ArgumentParser();p.add_argument('--source',type=Path,required=True);p.add_argument('--output',type=Path,required=True);p.add_argument('--receipt',type=Path,required=True);a=p.parse_args()
    raw=a.source.read_bytes();result=transform(raw);a.output.parent.mkdir(parents=True,exist_ok=True);a.output.write_bytes(result)
    receipt={'at_utc':datetime.now(timezone.utc).isoformat(),'state':'UNPROVED_COMPLETE_RUNTIME_COST_ONLY_NOT_ADOPTABLE',
             'base_submission':36,'base_sha256':BASE,'previous_native_diagnostic_sha256':PREVIOUS,
             'candidate_sha256':hashlib.sha256(result).hexdigest(),'candidate_bytes':len(result),
             'recipe_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
             'required_dependencies':{name:hashlib.sha256((HERE/name).read_bytes()).hexdigest()for name in ['build_centered36_cost.py','CenteredDotRuntime.leanfrag']},
             'difference':'Only three offset-bit-sum guards61 to62; same producer, loop, full paths, exact correction/bias/fallback. Positive products may occupy the entire UInt64 range, so use unsigned carry, not signed extension.',
             'bound':'u<2^(ex+1),v<2^(ew+1),ex+ew<=62 imply u*v<2^64. Each offset exponent<=39 and n<2^20 separately imply cached sums<2^60. Product bound63 is invalid: raw-word counterexample inunsigned64-extension.json.',
             'old_seen_coverage':'Actual paired linear+scalarGEMM coverage rises353855 to466862MACs/857004. Same84348extra prepitems. Not elapsed time or speed.',
             'proof':'No new Submission.correct. CenteredArithmetic.lean unsigned128_step draft is uncompiled and does not close full source.',
             'queue':'Same mechanism, one preferred diagnostic if earlier51fd not frozen. Do not launch both or change a frozen source/group.',
             'publication':'Own recipes/fragment/receipts only; whole source stays private/ephemeral'}
    a.receipt.write_text(json.dumps(receipt,indent=2)+'\n',encoding='utf-8');print(json.dumps({k:receipt[k]for k in ['candidate_sha256','candidate_bytes','state']}))


if __name__=='__main__':main()
