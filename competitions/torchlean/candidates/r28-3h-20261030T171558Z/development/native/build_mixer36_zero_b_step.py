"""Nonrecursive-step proof interface over pairlinear+norm26+zeroB runtime.

Implements Root190100's proof-engineering suggestion without editing any
frozen ingredient. The original ZMD2 induction body is reused verbatim except
its unfold name; zero-case reasoning is isolated in a nonrecursive step lemma.
"""
from pathlib import Path
from datetime import datetime,timezone
import argparse,hashlib,importlib.util,json,re
HERE=Path(__file__).resolve().parent
PORTFOLIO_RECIPE="007654614939d697ff450736ff80065f9f2773636e555dd67d2017557ddc6468"
ZERO_RECIPE="d667fd288e81c667cf5deaf7d211da04958ab007304282a4496827b1ef229cbb"
CONTROL="3d59846e41292d26c84d1e7dd9e089a403983db78b2434b63ee647ab3a71ab9f"
ARGS="X W b inW outW relu i j n A1 A2 B hA1 hA2 hB d1 d2 lo1 lo2 bw h1 l1 h2 l2 k out"
def sha(x):return hashlib.sha256(x).hexdigest()
def load(p,name,pin):
    assert sha(p.read_bytes())==pin
    s=importlib.util.spec_from_file_location(name,p);m=importlib.util.module_from_spec(s);s.loader.exec_module(m);return m
def build(raw36,raw27):
    port=load(HERE/"build_mixer36_portfolio.py","r28_step_port_loader",PORTFOLIO_RECIPE)
    pair,_=port.load("pair").build(raw36,raw27);norm,_=port.load("norm").build(raw36)
    source=pair.decode();old=port.declarations(raw36.decode());nd=port.declarations(norm.decode())
    for name in ["Ya7G","Ya7Ge"]:
        assert source.count(old[name])==1;source=source.replace(old[name],nd[name],1)
    assert sha(source.encode())==CONTROL
    zero=load(HERE/"build_mixer36_zero_b.py","r28_step_zero_loader",ZERO_RECIPE)
    zraw,zmeta=zero.build(raw36);inverse={b:a for a,b in zmeta["proof_names_renamed"].items()}
    expr=re.compile(r"(?<![\w.'?!])("+"|".join(map(re.escape,inverse))+r")(?![\w.'?!])")
    zcanonical=expr.sub(lambda m:inverse[m.group()],zraw.decode())
    zdecl=port.declarations(zcanonical)
    md=old["MD2"];marker=":Array ο :=\n";where=md.index(marker)
    signature=md[:where].replace("def MD2 ","lemma R28MD2_step ",1)
    rhs=md[where+len(marker):md.index("\ntermination_by",where)].rstrip()
    step=signature+":\n MD2 "+ARGS+"=\n"+rhs+" :=by\n"+""" by_cases hk:k<n
 . conv_lhs => rw[MD2]
   rw[dif_pos hk,dif_pos hk]
   dsimp only
   by_cases hw:(B.uget k (by have:=υ.mp hk;omega))ڈ-4611686018427387904=0
   . rw[if_pos hw] <;> simp only[hw,UInt64.mul_zero,UInt64.zero_shiftLeft,UInt64.add_zero,UInt64.zero_shiftRight,UInt64.sub_zero,lt_self_iff_false,ite_false]
   . rw[if_neg hw]
 . conv_lhs => rw[MD2]
   rw[dif_neg hk,dif_neg hk]
"""
    assert "R28MD2_step" not in source
    assert source.count(md)==1;source=source.replace(md,zdecl["MD2"]+step+"\n",1)
    begin=source.index("lemma ZMD2 ");end=source.index("\nlemma ZSb ",begin)
    proof=source[begin:end];assert proof.count("rw [MD2,MD,MD]")==2
    proof=proof.replace("rw [MD2,MD,MD]","rw [R28MD2_step,MD,MD]")
    source=source[:begin]+proof+source[end:]
    result=source.encode();assert len(result)<=256000,len(result)
    return result,{"control_pair_norm_sha256":CONTROL,"portfolio_recipe_sha256":PORTFOLIO_RECIPE,"zero_recipe_sha256":ZERO_RECIPE,
                   "runtime":"Existingpair-v2+norm26, plus zeroB directtailrecursion exactly samecanonicalMD2 as7100. No singleton/prepare-filter branch added.",
                   "proof":"R28MD2_step isolates newzero branch, nonrecursive proof with fixedwordzero simp rules. Original ZMD2 induction has only rw-name replacement; no newbycases/IHduplication in recursive equality.",
                   "source":"Rootrequest190100 is proof-engineering suggestion, not proofacceptance. New exact all12/prefix gate stillUNKNOWN.",
                   "scope":"SamezeroBalgorithm/family, no independent confidence or newperformance claim. NoextraCIrequest; useboundedprefix beforefull600 if selected later.",
                   "publication":"Ownrecipe/receipt only; whole Kernelprivate/ephemeral"}
def transform(raw,submission=36,variant="mixer36-zero-b-step",donor_raw=None):
    assert submission==36 and variant=="mixer36-zero-b-step"
    if donor_raw is None:
        import os
        root=os.environ.get("TORCHLEAN_ROOT");path=Path(root)/"r28-source-private/official-27.lean" if root else HERE.parents[2]/"r27-5h-20261029T194443Z/competition-state/source-private/submission27-Kernel.lean";donor_raw=path.read_bytes()
    return build(raw,donor_raw)[0]
if __name__=="__main__":
    p=argparse.ArgumentParser();p.add_argument("--source",type=Path,required=True);p.add_argument("--donor",type=Path,required=True);p.add_argument("--output",type=Path);p.add_argument("--receipt",type=Path,required=True)
    a=p.parse_args();result,meta=build(a.source.read_bytes(),a.donor.read_bytes())
    if a.output:a.output.parent.mkdir(parents=True,exist_ok=True);a.output.write_bytes(result)
    out={"at_utc":datetime.now(timezone.utc).isoformat(),"candidate_sha256":sha(result),"candidate_bytes":len(result),"free_bytes":256000-len(result),"recipe_sha256":sha(Path(__file__).read_bytes()),**meta,"state":"NONRECURSIVE_STEP_PROOF_ACTUAL_ALL12_NOT_COMPILED","gate":"UNKNOWN","native_speed":"UNKNOWN","extra_CI_request":False}
    a.receipt.write_text(json.dumps(out,indent=2,ensure_ascii=False)+"\n",encoding="utf-8")
    print(json.dumps({k:out[k]for k in ["candidate_sha256","candidate_bytes","free_bytes","recipe_sha256","state"]}))
