"""Own compact row-reciprocal patch over exact newly public23.

Reuse its existing m64/m64_v rather than republishing or reproving the native
multiply carrier. Modify Ya7G/MYbc and their actual proofs in place, retaining
the original all12 correct entry. Whole upstream source stays ephemeral.
"""
from pathlib import Path
import argparse
import hashlib
import importlib.util
import json
import re
import sys

sys.dont_write_bytecode=True
HERE=Path(__file__).resolve().parent
PIN="1010c0744f0506974c64601e8ce7335bea56d0cb21b655543d390794df0665fe"
OLD_HELPER="032dd2d40779f88b49cc28a23d5dc2bf4f1b9f371b0b7c071f5b36fe482ae97f"

def sha(data):
    return hashlib.sha256(data).hexdigest()

def compact_helper(source):
    raw=(HERE/"ReciprocalUInt64ContractOnly-v3.lean").read_bytes()
    assert sha(raw)==OLD_HELPER
    old=raw.decode("utf-8")
    nat_end=old.index("end R27ReciprocalProof")+len("end R27ReciprocalProof")
    natural=old[len("import ContractExact\n"):nat_end]
    runtime_start=old.index("@[inline] def prepare",nat_end)
    runtime_end=old.index("end R27Reciprocal",runtime_start)
    runtime=old[runtime_start:runtime_end]
    proof_start=old.index("theorem prepare_toNat",runtime_end)
    proof_end=old.rindex("end R27Reciprocal")
    proof=old[proof_start:proof_end]
    bridge="""@[inline] def mulHigh (a b : UInt64) : UInt64 := (m64 a b).1
theorem mulHigh_toNat (a b : UInt64) :
    (mulHigh a b).toNat = a.toNat * b.toNat / 2^64 := by
  unfold mulHigh
  have value := m64_v a b
  have low := (m64 a b).2.toNat_lt
  omega
"""
    helper=natural+"\nnamespace R27Reciprocal\n"+bridge+runtime+proof+"\nend R27Reciprocal\n"
    assert "R27D" not in source and "R27N" not in source
    replacements={
        "R27ReciprocalProof":"R27N","R27Reciprocal":"R27D",
        "reciprocal_estimate_bounds":"b","reciprocal_divrem":"c",
        "mulHigh_toNat":"hv","prepare_toNat":"pn","divRem_correct":"v",
        "mulHigh":"h","prepare":"p","divRem":"r",
        "base_pos":"bp","numerator_bound":"ab","divisor_pos":"dp",
        "reciprocal_low":"rl","reciprocal_high":"rh","estimate_low":"el","estimate_high":"eh",
        "remainder_bound":"rb","decomposition":"dc","original_subtraction":"os",
        "correction_subtraction":"cs","equation":"eq","small":"sm","quotient":"Q",
        "estimate_value":"e","product_fit":"pf","product_value":"pv","remainder_value":"rv",
        "natural_result":"nr","natural_correction":"nc","quotient_eq":"qe","remainder_eq":"re",
        "quotient_fit":"qf","denominator_ne":"dn","denominator_pos":"dp","nonzero":"nz",
        "numerator":"a","denominator":"d","divisor":"d","base":"B",
        "reciprocal":"R","estimate":"q","remainder":"r","correction":"k",
        "lower":"l","upper":"u","left":"L","right":"H","gap":"g","scaled":"s",
        "value":"vv","low":"ll",
    }
    for before,after in sorted(replacements.items(),key=lambda item:-len(item[0])):
        helper=re.sub(r"(?<![\w'])"+re.escape(before)+r"(?![\w'])",after,helper)
    helper=re.sub(r"/-.*?-/","",helper,flags=re.S)
    aliases={}
    prefix=source.split("\nstructure Acc",1)[0]
    for block in re.finditer(r"\bopen ([\w.]+) renaming (.*?)(?= open | local |$)",prefix):
        namespace,renamings=block.groups()
        for name,alias in re.findall(r"([\w.']+)->([\w]+)",renamings):
            qualified=namespace+"."+name
            if qualified in helper:
                aliases[qualified]=alias
    for qualified,alias in sorted(aliases.items(),key=lambda item:-len(item[0])):
        helper=re.sub(r"(?<!\w)"+re.escape(qualified)+r"(?![\w'])",alias,helper)
    helper=re.sub(r"(?<=[\w)\]!])\.toNat(?![A-Za-z0-9_'])","˧",helper)
    for typename,notation in [("UInt64","ػ"),("Nat","ٳ")]:
        helper=re.sub(r"(?<![\w.])"+typename+r"(?![\w.])",notation,helper)
    lines=[]
    for line in helper.splitlines():
        if not line.strip():
            continue
        indent=line[:len(line)-len(line.lstrip(" "))]
        body=re.sub(r"[ \t]+"," ",line[len(indent):].strip())
        body=re.sub(r"\s*([,:;])\s*",r"\1",body)
        body=re.sub(r"\s*([\[\]{}()])\s*",r"\1",body)
        lines.append(indent+body)
    return "\n".join(lines)+"\n",{"renames":replacements,"existing_aliases":aliases}

def once(text,before,after):
    assert text.count(before)==1,(before,text.count(before))
    return text.replace(before,after,1)

def transform(data,submission=23,variant="row-reciprocal23-v1"):
    assert submission==23 and variant=="row-reciprocal23-v1" and sha(data)==PIN
    text=data.decode("utf-8")
    helper,meta=compact_helper(text)
    marker="@[inline] def Ya7G ("
    text=once(text,marker,helper+"\n"+marker)
    text=once(text,"(S1a:UInt64):Word :=","(S1a R27R:UInt64):Word :=")
    text=once(text,"let q0:=cv/D\n   let r0:=cv%D*Yf gw\n   let qq:=q0*Yf gw+r0/D",
      "let qr0:=R27D.r cv D R27R\n   let q0:=qr0.1\n   let r0:=qr0.2*Yf gw\n   let qr1:=R27D.r r0 D R27R\n   let qq:=q0*Yf gw+qr1.1")
    text=once(text,"let ra:=(r0%D)<<<ks\n    let qa:=(qq<<<ks)+ra/D\n    let rr:=ra%D",
      "let ra:=qr1.2<<<ks\n    let qr2:=R27D.r ra D R27R\n    let qa:=(qq<<<ks)+qr2.1\n    let rr:=qr2.2")
    text=once(text,"Ya7G n w gw bw b0 S1 dw mean nU b0U S1n S1a = MYa7",
      "Ya7G n w gw bw b0 S1 dw mean nU b0U S1n S1a (R27D.p (nU*Yf dw)) = MYa7")
    text=once(text," unfold Ya7G\n dsimp only"," unfold Ya7G\n simp only[R27D.v]")
    text=once(text,"  let nU:=if n < 4096 then n.toUInt64 else 0\n",
      "  let nU:=if n < 4096 then n.toUInt64 else 0\n  let recs:=Array.ofFn (n:=rows) fun r=>R27D.p (nU*Yf st[r.val]!.2.2)\n")
    text=once(text," nU u.2.2 u.1 u.2.1\n"," nU u.2.2 u.1 u.2.1 recs[r]!\n")
    anchor="have hq:q.val/n*n+q.val%n=q.val:=Nat.div_add_mod' q.val n;rw ["
    cache="gO rows (λ r=>R27D.p ((if n < 4096 then n.toUInt64 else 0)*Yf (Array.ofFn (n:=rows) (λ i=>Y8f x n eps i.val))[r]!.2.2)) _ hr"
    text=once(text,anchor,"have hq:q.val/n*n+q.val%n=q.val:=Nat.div_add_mod' q.val n;rw ["+cache+"];rw [")
    return text.encode("utf-8"),helper,meta

def main():
    p=argparse.ArgumentParser()
    p.add_argument("--source",type=Path,required=True)
    p.add_argument("--output",type=Path)
    p.add_argument("--receipt",type=Path,required=True)
    a=p.parse_args()
    result,helper,meta=transform(a.source.read_bytes())
    spec=importlib.util.spec_from_file_location("r27_public23_recip_policy",HERE/"patch_public.py")
    m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m)
    report={"id":"public23-row-reciprocal-v1","source23_sha256":PIN,
            "candidate_sha256":sha(result),"candidate_bytes":len(result),"delta_bytes":len(result)-252639,
            "helper_bytes":len(helper.encode("utf-8")),"pruning_needed_bytes":max(0,len(result)-256000),
            "reuse":"Existing public23m64/m64_v; no duplicate native multiplyproof or runtime",
            "runtime":"Three q/r pairs through exact cachedreciprocal; one prepare perrowinsideMYbc; finalround/fallback unchanged",
            "actual_proof":"Ya7Ge statement/proof and Zdt cachegetter proof updatedinplace; actualkernels/correct entry retained; NOT_COMPILED",
            "status":"EXACT_RECIPE_AND_SPACE_COST_NOT_COMPILED",
            "policy":m.policy_check(result),"compaction":meta,
            "target":"Current43 via exactretired23reportchain; directcurrent sourceUNKNOWN",
            "publication":"Own recipe andhelper proof only; whole23source remainslocal/ephemeral"}
    if a.output:
        a.output.parent.mkdir(parents=True,exist_ok=True);a.output.write_bytes(result)
    a.receipt.write_text(json.dumps(report,indent=2)+"\n",encoding="utf-8")
    print(json.dumps({k:v for k,v in report.items() if k!="compaction"},indent=2))

if __name__=="__main__":
    main()
