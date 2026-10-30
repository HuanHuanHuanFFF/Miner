"""Full source recipe: do not prepare rows rejected by native width metadata.

Compose onto frozen pairlinear-v2, preserving its nonempty finite small-k
route and the complete source36 portfolio. Cache-length implies exact cache
entries remains the original ZMaU interface; empty skipped caches fall back.
"""
from pathlib import Path
from datetime import datetime,timezone
import argparse,hashlib,importlib.util,json
HERE=Path(__file__).resolve().parent
PAIR_RECIPE="8a59c56f8c92d9f62d85375f3606224cd5bb9c756d4168519940fc4381391e08"
PAIR_SOURCE="7b6e0cbaa7165488eef9fdd2f482bef522bb9b6d165649a88494e210f2a06ae3"
def sha(b):return hashlib.sha256(b).hexdigest()
def once(s,a,b):assert s.count(a)==1,(a,s.count(a));return s.replace(a,b,1)
def build(raw36,raw27):
    path=HERE/"build_gemm36_pairlinear_v2.py";assert sha(path.read_bytes())==PAIR_RECIPE
    sp=importlib.util.spec_from_file_location("r28_prep_pair_frozen",path);m=importlib.util.module_from_spec(sp);sp.loader.exec_module(m)
    pair,meta=m.build(raw36,raw27);assert sha(pair)==PAIR_SOURCE
    source=pair.decode()
    row="MPx A (r*inW) inW (Yk (B[r]!>>>16)) 0 (Ι inW)"
    marker="def MPr "
    helper="""def R28PrepRow (A:Array ο) (B:Array ז) (inW r:Nat):Array Nat :=
 let bm:=B[r]!
 if (bm&&&0xFFFF)!=255 && Yk (bm&&&0xFFFF)-Yk (bm>>>16)<=15 then
  MPx A (r*inW) inW (Yk (bm>>>16)) 0 (Ι inW)
 else #[]
"""
    source=once(source,marker,helper+marker)
    source=once(source,"acc.push ("+row+")","acc.push (R28PrepRow A B inW r)")
    # Generic list/array traversal proofs change only their mapped row expression.
    source=once(source,"(Φ r (n-r)).map (λ s=>MPx A (s*inW) inW (Yk (B[s]!>>>16)) 0 (Ι inW))","(Φ r (n-r)).map (λ s=>R28PrepRow A B inW s)")
    source=once(source,"ς (n:=n) (λ s=>MPx A (sک*inW) inW (Yk (B[sک]!>>>16)) 0 (Ι inW))","ς (n:=n) (λ s=>R28PrepRow A B inW sک)")
    lemma="""lemma R28PrepGet (A:Array ο) (B:Array ז) (inW r:Nat)
 (hs:(R28PrepRow A B inW r).size=inW) (t:Nat) (ht:t<inW):
 (R28PrepRow A B inW r)[t]! =MxA A[r*inW+t]! (Yk (B[r]!>>>16)):=by
 unfold R28PrepRow at hs ⊢
 dsimp only at hs ⊢
 split_ifs at hs ⊢
 . rw[ZMPy,ZeF (α:=Nat) _ _ _ ht]
 . simp at hs
   omega
"""
    source=once(source,"lemma ZMVa ",lemma+"lemma ZMVa ")
    begin=source.index("lemma ZMVa ");end=source.index("\nlemma ZMV0:",begin)
    piece=source[begin:end]
    old=" . intro _ t ht;rw [ZeF (α:=Nat) _ _ _ ht]"
    assert piece.count(old)==2
    new1=""" . intro hs t ht
   have h:=R28PrepGet X (ς (n:=rows) λ i=>Yc X inW iک) inW r hs t ht
   simpa only[ZeF (α:=ז) _ _ _ hr]using h"""
    new2=""" . intro hs t ht
   have h:=R28PrepGet W (ς (n:=outW) λ j=>Yc W inW jک) inW c hs t ht
   simpa only[ZeF (α:=ז) _ _ _ hc]using h"""
    piece=piece.replace(old,new1,1).replace(old,new2,1)
    source=source[:begin]+piece+source[end:]
    result=source.encode();assert len(result)<=256000
    return result,{"pairlinear_control_sha256":PAIR_SOURCE,"pairlinear_recipe_sha256":PAIR_RECIPE,
                   "runtime_changed":"MPr maps each row to R28PrepRow: metadata finite and unsigned span<=15 packs original MPx, otherwise empty cache; all old MaU/MD2 fallbacks unchanged",
                   "proof_changed":["ZMPr","ZMPs","ZMVa"],"new_proof":"R28PrepGet: cache length=inW implies original MxA entries; skipped empty cache and t<inW contradict unless nonempty. Original ZMaU correctness interface retained.",
                   "scope":"Actualall12 connected, NOT_COMPILED. No source36 retired result or previous proof/gate transfers.",
                   "cost_risk":"One metadata branch per prepared row; may trade rare valid zero-weight native dots for original exact fallback. Per-call prep/allocation/fallback/destruction stay inside complete model.",
                   "publication":"Ownrecipe/receipts only; full upstream/reconstructed source private/ephemeral"}
def transform(raw,submission=36,variant="mixer36-selective-prep",donor_raw=None):
    assert submission==36 and variant=="mixer36-selective-prep"
    if donor_raw is None:
        import os
        root=os.environ.get("TORCHLEAN_ROOT");path=Path(root)/"r28-source-private/official-27.lean" if root else HERE.parents[2]/"r27-5h-20261029T194443Z/competition-state/source-private/submission27-Kernel.lean";donor_raw=path.read_bytes()
    return build(raw,donor_raw)[0]
if __name__=="__main__":
    p=argparse.ArgumentParser();p.add_argument("--source",type=Path,required=True);p.add_argument("--donor",type=Path,required=True);p.add_argument("--output",type=Path);p.add_argument("--receipt",type=Path,required=True)
    a=p.parse_args();result,meta=build(a.source.read_bytes(),a.donor.read_bytes())
    if a.output:a.output.parent.mkdir(parents=True,exist_ok=True);a.output.write_bytes(result)
    out={"at_utc":datetime.now(timezone.utc).isoformat(),"candidate_sha256":sha(result),"candidate_bytes":len(result),"free_bytes":256000-len(result),"recipe_sha256":sha(Path(__file__).read_bytes()),**meta,"state":"ACTUAL_ALL12_DECLARED_NOT_COMPILED","gate":"UNKNOWN","native_speed":"UNKNOWN","extra_CI_request":False}
    a.receipt.write_text(json.dumps(out,indent=2,ensure_ascii=False)+"\n",encoding="utf-8")
    print(json.dumps({k:out[k] for k in ["candidate_sha256","candidate_bytes","free_bytes","recipe_sha256","state"]}))
