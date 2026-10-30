"""Static and finite inspection of the exact owned public23 recipe.

This script emits only self-authored helper source and numeric receipts.
It does not compile Lean or establish the original gate.
"""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,importlib.util,json,random,re
HERE=Path(__file__).resolve().parent
BASE=HERE.parents[1]
def sha(data):return hashlib.sha256(data).hexdigest()
spec=importlib.util.spec_from_file_location('r27_recip23_inspection',HERE/'public23_reciprocal_v3.py')
m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m)
raw=(BASE/'competition-state/source-private/submission23-Kernel.lean').read_bytes()
result,helper,metadata=m.build(raw)
(HERE/'Reciprocal23Compact-v2.lean.inc').write_text(helper,encoding='utf-8')
start=result.decode().index('@[inline] def Ya7G ')
stop=result.decode().index('\nend\n',start)
runtime=result.decode()[start:stop]
assert runtime.count('R27D.r')==3
assert 'let recs:=Array.ofFn' in result.decode()
assert result.decode().count('theorem correct:Obligation kernels:=')==1
# A fixed pre-confirmation finite integer audit, including difficult boundaries.
B=1<<64; rng=random.Random(0x27D23)
divisors=set([1,2,3,7,31,(1<<32)-1,1<<32,(1<<32)+1,B-1])
for p in range(64):
    for delta in [-1,0,1]:
        d=(1<<p)+delta
        if 0<d<B:divisors.add(d)
divisors.update(rng.randrange(1,B) for _ in range(1000))
cases=0;corrected=0
for d in sorted(divisors):
    R=(B-1)//d
    aa=set([0,1,d-1,d,min(B-1,d+1),B-1])
    aa.update(rng.randrange(B) for _ in range(30))
    for a in aa:
        q=a*R//B;r=a-q*d
        assert q*d<=a<(q+2)*d and 0<=r<B
        if d<=r:q+=1;r-=d;corrected+=1
        assert (q,r)==divmod(a,d)
        cases+=1
receipt={'at_utc':datetime.now(timezone.utc).isoformat(),
 'candidate_sha256':sha(result),'candidate_bytes':len(result),
 'helper_sha256':sha(helper.encode()),'helper_bytes':len(helper.encode()),
 'actual_caller_divrem_calls':3,'row_prepare_cache_present':True,'actual_all12_entry_present':True,
 'finite_cases':cases,'finite_correction_taken':corrected,'finite_mismatches':0,
 'finite_scope':'Mathematical integer model only, d>0. d=0 delegates original operations in runtime, not audited here',
 'proof_state':'NOT_COMPILED; finite checks never substitute all12 gate',
 'cost_boundary':{
  'old_per_output':'Three logical quotient/remainder pairs; native C may fuse each pair into one hardware divide',
  'new_per_output':'Three existing m64 high-word calculations, each four 32x32 partial products plus carry arithmetic; one correction each; temporary pair allocation elimination UNKNOWN',
  'new_per_row':'One UInt64 division and one cached UInt64; O(rows) Array.ofFn preparation',
  'whole_model_gain':'UNKNOWN until complete paired normalized_mlp samples',
  'assumption':'Norm output must remain a material share after native128 RMS/layer statistics. No multiplier claim from operation counts'}}
(HERE/'public23-reciprocal-v2-inspection.json').write_text(json.dumps(receipt,indent=2)+'\n',encoding='utf-8')
print(json.dumps(receipt,indent=2))
