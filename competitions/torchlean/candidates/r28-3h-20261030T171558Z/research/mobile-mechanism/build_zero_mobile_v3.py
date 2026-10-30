"""Archive-only minimal repair of actual CI4 remaining termination goals.

The measured zero runtime is slower; no new full gate or timing is requested.
"""
from pathlib import Path
import importlib.util,hashlib,json,datetime,argparse
HERE=Path(__file__).resolve().parent
PREV=HERE/'build_zero_mobile_v2.py'
PREV_SHA='120b5adf73a39ff95ea28a12902cb0d0399d00827d657a0c2b29d3be6fa6a056'
BASE=HERE.parents[1]/'competition-state/source-private/official-53.lean'
def transform(raw,submission,variant):
    assert submission==53 and variant in ['zero-both-proof-v3','repair-q14-v3']
    assert hashlib.sha256(PREV.read_bytes()).hexdigest()==PREV_SHA
    spec=importlib.util.spec_from_file_location('r28zeroV3base',PREV);m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m)
    s=m.transform(raw,53,'zero-both-proof-v2').decode()
    for start,end in [('lemma qCtx8 ','@[specialize] def qCtx9 '),('lemma qCtx14 ','@[inline] def qCtx15 ')]:
      a=s.index(start);b=s.index(end,a);part=s[a:b]
      old='decreasing_by exact ZI n k ‹k<n›';assert part.count(old)==1
      part=part.replace(old,'decreasing_by all_goals exact ZI n k ‹k<n›');s=s[:a]+part+s[b:]
    if variant=='repair-q14-v3':s=s[:s.index('@[inline] def qCtx15 ')]+'\nend Submission\n'
    out=s.encode();assert len(out)<=256000
    return out
if __name__=='__main__':
    p=argparse.ArgumentParser();p.add_argument('--base',type=Path,default=BASE);a=p.parse_args();raw=a.base.read_bytes();rows=[]
    for mode in ['zero-both-proof-v3','repair-q14-v3']:
      data=transform(raw,53,mode);path=HERE/'private/zero-proof-diagnostic'/(mode+'.lean');path.write_bytes(data)
      rows.append({'variant':mode,'sha256':hashlib.sha256(data).hexdigest(),'bytes':len(data)})
    r={'at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'artifacts':rows,'recipe_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),'dependencies':{'build_zero_mobile_v2.py':PREV_SHA,'build_zero_mobile.py':'88f651e2b226d4810a062650b1b72c2d5f6091211e0312e58e0627ef699e221b'},'exact_change':'Add all_goals to the two lemma decreasing_by blocks; actual CI4 error is the second branch measure inequality with k<n available. Runtime unchanged.','state':'UNCOMPILED_ARCHIVED_REPAIR; no accepted root/all12 claim','cost_decision':'Zero runtime measured1.21539785x public53 and INFERRED1.27120324x current57, guard failed. Stop full proof/variant investment; no CI request.'}
    (HERE/'zero-proof-v3-receipt.json').write_text(json.dumps(r,indent=2)+'\n');print(json.dumps(r,indent=2))
