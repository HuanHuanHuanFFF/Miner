"""Full public43 portfolio, sharp uniform UInt64 remainder guard8->28.

Same arithmetic family as accepted R27 guard26 and R28 source36norm26, now
retaining the newly public43 native RMS/dense portfolio. No new gain claimed.
With D<2^36 and r<D, r*2^28<2^64. Its quotient is<2^28, so qa stays<2^62.
"""
from pathlib import Path
from datetime import datetime,timezone
import argparse,hashlib,json
HERE=Path(__file__).resolve().parent
PIN="4fef6fd4dbb39fe6fbf8fa85407228d6ebce9fb98dfbecf0d378e6f3b0df7c8b"
def sha(b):return hashlib.sha256(b).hexdigest()
def once(s,a,b):assert s.count(a)==1,(a,s.count(a));return s.replace(a,b,1)
def build(raw):
    assert sha(raw)==PIN
    source=raw.decode();start=source.index("@[inline] def Ya7G ");end=source.index("\nend\n",start)
    body=once(source[start:end],"ks <= 8","ks <= 28");source=source[:start]+body+source[end:]
    start=source.index("lemma Ya7Ge ");end=source.index("\ndef MYbc ",start)
    proof=source[start:end];assert proof.count("2^44")==1
    proof=proof.replace("2^44","2^64")
    anchor=" have hqs:"
    extra=""" have hR28q:ra.toNat/D.toNat<2^28:=by
  apply (Nat.div_lt_iff_lt_mul hDp).mpr
  rw[hra]
  have hR28pk:2^ks.toNat<=2^28:=Nat.pow_le_pow_right (by decide) hks8
  have ht:=Nat.mul_lt_mul_of_pos_right (Nat.mod_lt (cv.toNat%D.toNat*mantOf gw) hDp) (Nat.two_pow_pos ks.toNat)
  have hu:=Nat.mul_le_mul_left D.toNat hR28pk
  exact ht.trans_le (hu.trans_eq (Nat.mul_comm D.toNat (2^28)))
"""
    proof=once(proof,anchor,extra+anchor)
    source=source[:start]+proof+source[end:]
    result=source.encode();assert len(result)<=256000
    return result,{"base_sha256":PIN,"uniform_cap":28,"runtime_changed":["Ya7G"],"proof_changed":["Ya7Ge"],
                   "bounds":"r=(cvmodD*mantgw)modD<D<2^36, ks<=28 => ra<2^64, ra/D<2^28. qMain<2^61 plus quotient<2^28 => qa<2^62, preserving original finalbias/round constraints.",
                   "preserves":"Complete public43 nativeRMS/Ybb2,FFr/nativeLayerNorm,originaldenseYaV/sparsepreparedportfolio,all12exactfallbacks and actualcorrect theorem",
                   "new_fact":"Public43 strongRMS baseline is available R28; unlike old source12/23 incomplete portfolios it is retained whole. Cap28 is sharp uniform64bit product bound, not chosen from freshnative/confirmation data.",
                   "family_boundary":"Sameguardfamily as26, not independent statisticalsuccess. New source43 gate/performance/current51 chain remainUNKNOWN; no extraCI request.",
                   "publication":"Ownrecipe/receipt only; whole sourceprivate/ephemeral"}
def transform(raw,submission=43,variant="norm43-guard28"):
    assert submission==43 and variant=="norm43-guard28"
    return build(raw)[0]
if __name__=="__main__":
    p=argparse.ArgumentParser();p.add_argument("--source",type=Path,required=True);p.add_argument("--output",type=Path);p.add_argument("--receipt",type=Path,required=True)
    a=p.parse_args();result,meta=build(a.source.read_bytes())
    if a.output:a.output.parent.mkdir(parents=True,exist_ok=True);a.output.write_bytes(result)
    out={"at_utc":datetime.now(timezone.utc).isoformat(),"candidate_sha256":sha(result),"candidate_bytes":len(result),"free_bytes":256000-len(result),"recipe_sha256":sha(Path(__file__).read_bytes()),**meta,
         "state":"ACTUAL_ALL12_SOURCE_NOT_COMPILED","gate":"UNKNOWN","native_speed":"UNKNOWN","extra_CI_request":False,
         "planning_snapshot":"Saved currentNMLP51/public43 requires26.6104percent additionalreduction at0.97bar; not refreshed bythisrole or treatedasdirectcandidateperformance"}
    a.receipt.write_text(json.dumps(out,indent=2,ensure_ascii=False)+"\n",encoding="utf-8")
    print(json.dumps({k:out[k]for k in ["candidate_sha256","candidate_bytes","free_bytes","recipe_sha256","state"]}))
