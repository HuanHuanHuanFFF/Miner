"""Owned RMS terminal reuse over exact retired public23; no upstream source embedded."""
from __future__ import annotations
import argparse,hashlib,json
from pathlib import Path
from datetime import datetime,timezone
HERE=Path(__file__).resolve().parent
PIN="1010c0744f0506974c64601e8ce7335bea56d0cb21b655543d390794df0665fe"
def transform(raw,submission=23,variant="rms-native-finish"):
 assert submission==23 and variant=="rms-native-finish"
 assert hashlib.sha256(raw).hexdigest()==PIN
 s=raw.decode();piece=(HERE/"RmsNativeFinish.lean.inc").read_text(encoding="utf8")
 marker="def Ybb2 (rows n:Nat)"
 assert s.count(marker)==1
 s=s.replace(marker,piece+"\n"+marker)
 old="YT rows n λ r j=>Ya7 x[r*n+j]! g[j]! den[r]!"
 assert s.count(old)==1;s=s.replace(old,old.replace("Ya7 ","R27RmsFinish "))
 old="funext c n a x g;unfold Ybb2 rmsnormSpec rmsnormWith;split"
 assert s.count(old)==1;s=s.replace(old,"funext c n a x g;unfold Ybb2; simp only [R27RmsFinish_eq];unfold rmsnormSpec rmsnormWith;split")
 result=s.encode();assert len(result)<=256000
 assert result.count(b"theorem correct:Obligation kernels:=")==1
 return result
if __name__=="__main__":
 p=argparse.ArgumentParser();p.add_argument("--source",type=Path,required=True);p.add_argument("--output",type=Path,required=True);p.add_argument("--receipt",type=Path,required=True);a=p.parse_args();raw=a.source.read_bytes();result=transform(raw);a.output.parent.mkdir(parents=True,exist_ok=True);a.output.write_bytes(result)
 r={"at_utc":datetime.now(timezone.utc).isoformat(),"state":"REAL_ALL12_CALLER_CONNECTED_UNCOMPILED","base_sha256":PIN,"candidate_sha256":hashlib.sha256(result).hexdigest(),"candidate_bytes":len(result),"delta_bytes":len(result)-len(raw),"free_bytes":256000-len(result),"helper_sha256":hashlib.sha256((HERE/"RmsNativeFinish.lean.inc").read_bytes()).hexdigest(),"recipe_sha256":hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),"mechanism":"RMS output terminal uses existing guarded native rrsG instead of generic YN; stats/sqrt and all fallback exact paths unchanged","proof":"Actual Ybb2/T4b caller connected through unconditional equality to Ya7; complete correct retained, not compiled","entry":"transform(raw,submission=23,variant=rms-native-finish)","limits":["Not all12 gate accepted","Not native measured","Retired23 base not current43 champion","Unknown-license whole source private"]};a.receipt.write_text(json.dumps(r,indent=2),encoding="utf8");print(json.dumps(r))
