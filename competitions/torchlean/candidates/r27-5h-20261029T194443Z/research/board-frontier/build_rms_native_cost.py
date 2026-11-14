"""Exact RMS terminal cost carrier. Retained proof certifies retainedKernels only."""
from __future__ import annotations
import argparse,hashlib,json,re
from pathlib import Path
from datetime import datetime,timezone
HERE=Path(__file__).resolve().parent
PIN="1010c0744f0506974c64601e8ce7335bea56d0cb21b655543d390794df0665fe"
HELPER="460d81146ce96b4a0681afa3df3e7530432b3e16cd937627c86f95dec0adc419"
def transform(raw,submission=23,variant="rms-native-cost"):
 assert submission==23 and variant=="rms-native-cost"
 assert hashlib.sha256(raw).hexdigest()==PIN
 s=raw.decode();h=(HERE/"RmsNativeFinish.lean.inc").read_bytes();assert hashlib.sha256(h).hexdigest()==HELPER
 runtime=h.decode().split("lemma R27RmsFinish_eq",1)[0]
 begin=s.index("def Ybb2 (rows n:Nat)");end=s.index("lemma T4b:",begin)
 norm=s[begin:end].replace("def Ybb2 ","def R27RmsNorm ").replace("=>Ya7 ","=>R27RmsFinish ")
 assert norm.count("R27RmsFinish")==1
 begin=s.index("def kernels:Kernels where");end=s.index("end Submission",begin)
 old=s[begin:end];retained=re.sub(r"\bkernels\b","retainedKernels",old).replace("theorem correct:","theorem retainedCorrect:")
 new=runtime+norm+"def kernels:Kernels := { retainedKernels with norm := ⟨R27RmsNorm,MYbc⟩ }\n"
 result=(s[:begin]+retained+new+s[end:]).encode();assert len(result)<=256000
 assert b"theorem correct:"not in result and b"theorem retainedCorrect:Obligation retainedKernels:="in result
 return result
if __name__=="__main__":
 p=argparse.ArgumentParser();p.add_argument("--source",type=Path,required=True);p.add_argument("--output",type=Path,required=True);p.add_argument("--receipt",type=Path,required=True);a=p.parse_args();raw=a.source.read_bytes();result=transform(raw);a.output.parent.mkdir(parents=True,exist_ok=True);a.output.write_bytes(result)
 r={"at_utc":datetime.now(timezone.utc).isoformat(),"state":"NATIVE_COST_ONLY_NO_NEW_CORRECT_UNCOMPILED","base_sha256":PIN,"candidate_sha256":hashlib.sha256(result).hexdigest(),"candidate_bytes":len(result),"delta_bytes":len(result)-len(raw),"free_bytes":256000-len(result),"helper_sha256":HELPER,"recipe_sha256":hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),"mechanism":"Same RmsNativeFinish runtime as full source d0e60a6e; copied existing RMS caller changes only terminal","proof_boundary":"All original declarations and retainedCorrect preserved for old retainedKernels; new kernels has NO correct. No full12 claim.","entry":"transform(raw,submission=23,variant=rms-native-cost)","cost_boundary":"Complete normalized_mlp, includes originalstats/sqrt, preparation, zeros/fallbacks, output; bothbatch1/8","publication":"Owned recipe only; whole23 source private"};a.receipt.write_text(json.dumps(r,indent=2),encoding="utf8");print(json.dumps(r))
