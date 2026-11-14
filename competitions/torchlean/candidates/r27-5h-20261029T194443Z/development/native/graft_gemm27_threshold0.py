"""Optional same-proof GEMM boundary: finite nonempty small k uses YaV too.

No extra queue by default. The donor Gsn lemma only needs k>0, not k>=20;
the existing proof's `omega` step can use the new k!=0 hypothesis.
"""
from pathlib import Path
from datetime import datetime,timezone
import argparse,hashlib,importlib.util,json
HERE=Path(__file__).resolve().parent
def sha(x):return hashlib.sha256(x).hexdigest()
def build(raw,donor):
 path=HERE/'graft_gemm27_public23.py';assert sha(path.read_bytes())=='437d00f50d06c57fcbb5c389ab2dd5f8e503917c2c84a8c56661cd00a7c9a946'
 s=importlib.util.spec_from_file_location('r27_gemm_threshold_parent',path);m=importlib.util.module_from_spec(s);s.loader.exec_module(m)
 first,meta=m.build(raw,donor)
 old='if k<20||!(A.all finiteWord&&B.all finiteWord) then'
 new='if k=0||!(A.all finiteWord&&B.all finiteWord) then'
 text=first.decode();assert text.count(old)==1;result=text.replace(old,new).encode()
 return result,meta
if __name__=='__main__':
 p=argparse.ArgumentParser();p.add_argument('--source',type=Path,required=True);p.add_argument('--donor',type=Path,required=True);p.add_argument('--receipt',type=Path,required=True)
 a=p.parse_args();result,meta=build(a.source.read_bytes(),a.donor.read_bytes())
 sp=importlib.util.spec_from_file_location('r27_threshold_policy',HERE/'patch_public.py');m=importlib.util.module_from_spec(sp);sp.loader.exec_module(m)
 out={'at_utc':datetime.now(timezone.utc).isoformat(),'candidate_sha256':sha(result),'candidate_bytes':len(result),'free_bytes':256000-len(result),
  'recipe_sha256':sha(Path(__file__).read_bytes()),'state':'OPTIONAL_BOUNDARY_SOURCE_ACTUAL_ALL12_DECLARED_NOT_COMPILED_NOT_QUEUED',
  'policy':m.policy_check(result),'delta':'Only k<20 guard becomes k=0; same actual proof text, Gsn needs k>0 and existing omega derives it',
  'fallback':'Nonfinite or empty k still original kernels0.dense.2. Finite1<=k<20 now strong23 YaV/rawnative rather than legacy Yn GEMM',
  'proof':'No inherited acceptance; fresh all12 needed, especially proof condition elaboration',
  'selection':'Parent chooses boundary if useful; no automatic extra queue or mutation of bbd75849 candidate',
  'comparison':'CurrentMixer36 only via frozen public27 report chain; full native cost including smallktranspose/prep unknown',
  **meta}
 a.receipt.write_text(json.dumps(out,indent=2)+'\n',encoding='utf-8');print(json.dumps(out,indent=2))
