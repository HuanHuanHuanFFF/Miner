"""NativeOnly whole-model cost prototype for source36 conditional pair blocks.

No new Submission.correct exists. Four now-inapplicable proof declarations
are removed transitively; all twelve runtime fields and original GEMM remain.
The exact metadata branch admits width<=14, so two signed products have total
mass<2^63 and can be merged once. Full formal loop/cache proof is still open.
"""
from pathlib import Path
from datetime import datetime,timezone
import argparse,hashlib,json,re
HERE=Path(__file__).resolve().parent
PIN="595a90fa2b6bc5d3657434fae7d1292b27910ef653da2b7f409ed9c34c956e2b"
DECL=re.compile(r"(?m)^(?:@\[[^\n]*\]\s*)?(?:noncomputable\s+)?(def|lemma|theorem|structure|abbrev)\s+([\w.'?!]+)")
STOP=re.compile(r"(?m)^(?:@\[[^\n]*\]\s*)?(?:noncomputable\s+)?(?:def|lemma|theorem|structure|abbrev|section|end|open|namespace|set_option)\b")
def sha(b):return hashlib.sha256(b).hexdigest()
def once(s,a,b):assert s.count(a)==1,(a,s.count(a));return s.replace(a,b,1)
def prune_proofs(source):
    boundaries=[m.start() for m in STOP.finditer(source)];decl=[]
    for m in DECL.finditer(source):
        end=next((x for x in boundaries if x>m.start()),len(source))
        decl.append((m.group(1),m.group(2),m.start(),end,source[m.start():end]))
    deleted={"ZMVj"}
    while True:
        new={name for kind,name,a,b,text in decl if kind in ["lemma","theorem"] and any(re.search(r"(?<![\w.'?!])"+re.escape(n)+r"(?![\w.'?!])",text) for n in deleted)}
        if new<=deleted:break
        deleted|=new
    spans=[(a,b,name) for kind,name,a,b,text in decl if name in deleted]
    for a,b,name in reversed(spans):source=source[:a]+source[b:]
    assert "correct" in deleted and not re.search(r"(?m)^theorem correct\b",source)
    return source,sorted(deleted),sum(b-a for a,b,n in spans)
def build(raw):
    assert sha(raw)==PIN
    source=raw.decode();source,deleted,pruned=prune_proofs(source)
    begin=source.index("def MD2 ");head_end=source.index(":Array ο :=\n",begin)+len(":Array ο :=\n")
    header=source[begin:head_end].replace("def MD2 ","def R28MD2B2 ",1)
    body=""" if hk:k<n ∧ k+1<n then
  let w0:=(B.uget k (by have:=υ.mp hk.1;omega))ڈ-4611686018427387904
  let w1:=(B.uget (k+1) (by have:=υ.mp hk.2;omega))ڈ-4611686018427387904
  let p10:=(((A1.uget k (by have:=υ.mp hk.1;omega))ڈ-4611686018427387904)*w0)<<<d1
  let p11:=(((A1.uget (k+1) (by have:=υ.mp hk.2;omega))ڈ-4611686018427387904)*w1)<<<d1
  let p20:=(((A2.uget k (by have:=υ.mp hk.1;omega))ڈ-4611686018427387904)*w0)<<<d2
  let p21:=(((A2.uget (k+1) (by have:=υ.mp hk.2;omega))ڈ-4611686018427387904)*w1)<<<d2
  let q1:=p10+p11
  let q2:=p20+p21
  let m1:=l1+q1
  let m2:=l2+q2
  R28MD2B2 X W b inW outW relu i j n A1 A2 B hA1 hA2 hB d1 d2 lo1 lo2 bw
   (h1+((0:ו)-(q1>>>63))+(if m1<l1 then 1 else 0)) m1
   (h2+((0:ו)-(q2>>>63))+(if m2<l2 then 1 else 0)) m2 ((k+1)+1) out
 else MD2 X W b inW outW relu i j n A1 A2 B hA1 hA2 hB d1 d2 lo1 lo2 bw h1 l1 h2 l2 k out
termination_by nڇ-kڇ
decreasing_by
 have h0:=ZI n k hk.1
 have h1:=ZI n (k+1) hk.2
 omega
"""
    marker="\ndef MVj "
    source=once(source,marker,"\n"+header+body+marker)
    start=source.index("def MVj ");stop=source.index("\ndef MVo ",start)
    piece=source[start:stop]
    old="    MD2 X W b inW outW relu i j inWژ xp1 xp2 wp"
    new="    (if hi1-lo1<=14 && hi2-lo2<=14 then R28MD2B2 else MD2) X W b inW outW relu i j inWژ xp1 xp2 wp"
    piece=once(piece,old,new);source=source[:start]+piece+source[stop:]
    result=source.encode();assert len(result)<=256000
    assert "def kernels:Kernels where" in source and "theorem correct:" not in source
    return result,{"base_sha256":PIN,"pruned_proofs":deleted,"pruned_proof_bytes":pruned,
                   "new_runtime":"R28MD2B2 merges two native products per row when both original bias-inclusive widths<=14; original MD2 tail and nonnarrow route retained",
                   "preserved":"Source36 YaVM/Ya3M preparation, all12 runtime fields, smallK/nativeAdd/LN/empty/nonfinite/sentinel/bias/rounding fallbacks",
                   "formal_scope":"UNPROVED_NATIVE_RESEARCH_ONLY; no Submission.correct. Old reference correct and generic merge helper do not certify this prototype.",
                   "proof_route":"WordPairMerge2 conditional equality plus per-product Zpt/R28L14 mass bounds; then scalar block_eq_MD and paired structural equality, original cache/caller/all12 proof",
                   "native_measurement":"UNKNOWN; costOnly complete paired Mixer with exactsource36 control and all allocation/preparation/destruction, checksums mandatory",
                   "publication":"Ownrecipe/receipts only; full source private/ephemeral"}
def transform(raw,submission=36,variant="mixer36-block2-cost"):
    assert submission==36 and variant=="mixer36-block2-cost"
    return build(raw)[0]
if __name__=="__main__":
    p=argparse.ArgumentParser();p.add_argument("--source",type=Path,required=True);p.add_argument("--output",type=Path);p.add_argument("--receipt",type=Path,required=True)
    a=p.parse_args();result,meta=build(a.source.read_bytes())
    if a.output:a.output.parent.mkdir(parents=True,exist_ok=True);a.output.write_bytes(result)
    out={"at_utc":datetime.now(timezone.utc).isoformat(),"candidate_sha256":sha(result),"candidate_bytes":len(result),"free_bytes":256000-len(result),"recipe_sha256":sha(Path(__file__).read_bytes()),**meta,"state":"UNPROVED_NATIVE_RESEARCH_ONLY_NOT_COMPILED","full_gate":False,"declares_correct":False,"native_speed":"UNKNOWN","extra_CI_request":False}
    a.receipt.write_text(json.dumps(out,indent=2,ensure_ascii=False)+"\n",encoding="utf-8")
    print(json.dumps({k:out[k] for k in ["candidate_sha256","candidate_bytes","free_bytes","recipe_sha256","state","pruned_proofs"]}))
