"""Own reconstruction of a row-amortized exact reciprocal norm candidate.

The upstream full source stays local/ephemeral; publish only this owned recipe,
owned proof extensions and exact receipts. No local Lean/native build occurs.
"""
from pathlib import Path
import argparse
import hashlib
import importlib.util
import json
import sys

sys.dont_write_bytecode=True
HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/"AGENTS.md").is_file())
PIN12="e2c1f1f1ba52e32563fb193ceea7e2a271b989fd3ba2eb16cff747987879b521"
HELPER_SHA="9555634b7ef92dfb7312eaf9b5103ff0034c0dcc81359f62bcb99129797799de"

def sha(data):
    return hashlib.sha256(data).hexdigest()

def transform(source):
    assert sha(source)==PIN12
    text=source.decode("utf-8")
    helper=(HERE/"ReciprocalUInt64ContractOnly-v2.lean").read_bytes()
    assert sha(helper)==HELPER_SHA and helper.startswith(b"import ContractExact\n")
    helper=helper[len(b"import ContractExact\n"):].decode("utf-8")
    start=text.index("@[inline] def Ya7G (")
    stop=text.index("\nend\nsection\n",start)
    original=text[start:stop]
    element=original.replace("def Ya7G (","def r27Ya7G (",1)
    assert element.count("(S1a:UInt64):Word :=")==1
    element=element.replace("(S1a:UInt64):Word :=","(S1a reciprocalD:UInt64):Word :=",1)
    pairs=[
        ("let q0:=cv/D\n   let r0:=cv%D*Yf gw\n   let qq:=q0*Yf gw+r0/D",
         "let cvQR:=R27Reciprocal.divRem cv D reciprocalD\n   let q0:=cvQR.1\n   let r0:=cvQR.2*Yf gw\n   let r0QR:=R27Reciprocal.divRem r0 D reciprocalD\n   let qq:=q0*Yf gw+r0QR.1"),
        ("let ra:=(r0%D)<<<ks\n    let qa:=(qq<<<ks)+ra/D\n    let rr:=ra%D",
         "let ra:=r0QR.2<<<ks\n    let raQR:=R27Reciprocal.divRem ra D reciprocalD\n    let qa:=(qq<<<ks)+raQR.1\n    let rr:=raQR.2"),
    ]
    for before,after in pairs:
        assert element.count(before)==1,before
        element=element.replace(before,after,1)
    element_eq=(HERE/"NormElementReciprocalEq.lean.inc").read_text(encoding="utf-8")
    text=text[:start]+helper+"\n"+original+"\n\n"+element+"\n\n"+element_eq+text[stop:]
    row_start=text.index("def MYbc (rows n:Nat)")
    row_stop=text.index("lemma Zdt:",row_start)
    original_row=text[row_start:row_stop]
    row=original_row.replace("def MYbc (","def r27MYbc (",1)
    before="  let nU:=if n < 4096 then n.toUInt64 else 0\n"
    assert row.count(before)==1
    row=row.replace(before,before+"  let reciprocals:=Array.ofFn (n:=rows) fun r=>R27Reciprocal.prepare (nU*Yf st[r.val]!.2.2)\n",1)
    assert row.count(";Ya7G ")==1
    row=row.replace(";Ya7G ",";r27Ya7G ",1)
    before=" nU u.2.2 u.1 u.2.1\n"
    assert row.count(before)==1
    row=row.replace(before," nU u.2.2 u.1 u.2.1 reciprocals[r]!\n",1)
    row_eq=(HERE/"NormRowReciprocalEq.lean.inc").read_text(encoding="utf-8")
    marker="@[inline] def YaEf ("
    assert text.count(marker)==1
    text=text.replace(marker,row+"\n"+row_eq+"\n"+marker,1)
    assert text.count("norm:=⟨Ybb2,MYbc⟩")==1
    text=text.replace("norm:=⟨Ybb2,MYbc⟩","norm:=⟨Ybb2,r27MYbc⟩",1)
    assert text.count("ZcC,T4b,Zdt]")==1
    text=text.replace("ZcC,T4b,Zdt]","ZcC,T4b,Zdt,r27MYbc_eq]",1)
    return text.encode("utf-8")

def main():
    p=argparse.ArgumentParser()
    p.add_argument("--source",type=Path,default=HERE.parent.parent/"competition-state/source-private/submission12-Kernel.lean")
    p.add_argument("--output",type=Path)
    p.add_argument("--receipt",type=Path)
    a=p.parse_args()
    raw=transform(a.source.read_bytes())
    spec=importlib.util.spec_from_file_location("r27_norm_recip_policy",HERE/"patch_public.py")
    mod=importlib.util.module_from_spec(spec);spec.loader.exec_module(mod)
    receipt={"id":"public12-row-reciprocal-v1","upstream_sha256":PIN12,
             "helper_sha256":HELPER_SHA,"candidate_sha256":sha(raw),"candidate_bytes":len(raw),
             "entry":"Submission.kernels","proof_entry":"Submission.correct",
             "status":"ACTUAL12_REFINEMENT_PROOFS_PRESENT_NOT_COMPILED",
             "scope":"Three elementdiv/rem pairs replaced; reciprocalprepared onceperrow insidekernel; originalfallbackandroundingunchanged",
             "source_publication":"Wholeupstream and reconstructedoutput LOCAL_OR_EPHEMERAL_ONLY",
             "policy":mod.policy_check(raw)}
    if a.output:
        a.output.parent.mkdir(parents=True,exist_ok=True);a.output.write_bytes(raw)
    if a.receipt:
        a.receipt.write_text(json.dumps(receipt,indent=2)+"\n",encoding="utf-8")
    print(json.dumps(receipt,indent=2))

if __name__=="__main__":
    main()
