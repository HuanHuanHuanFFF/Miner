"""Proof-only bounded simplification repair after Mobile statement timeout.

Original zero-B source7100 remains frozen. This version uses an explicit
finite simp set, avoiding default simplification over the recursive theorem
type. Runtime is identical after proof-name alpha inversion; gate still open.
"""
from pathlib import Path
from datetime import datetime,timezone
import argparse,hashlib,importlib.util,json,re
HERE=Path(__file__).resolve().parent
PREVIOUS_RECIPE="d667fd288e81c667cf5deaf7d211da04958ab007304282a4496827b1ef229cbb"
PREVIOUS_SOURCE="7100aaec2125bb7987e4403fd006d7a796980e006c35fd0984a7d4a58bbc21a2"
def sha(x):return hashlib.sha256(x).hexdigest()
def build(raw):
    path=HERE/"build_mixer36_zero_b.py";assert sha(path.read_bytes())==PREVIOUS_RECIPE
    sp=importlib.util.spec_from_file_location("r28_zero_b_v1_frozen",path);m=importlib.util.module_from_spec(sp);sp.loader.exec_module(m)
    previous,meta=m.build(raw);assert sha(previous)==PREVIOUS_SOURCE
    inverse={new:old for old,new in meta["proof_names_renamed"].items()}
    expression=re.compile(r"(?<![\w.'?!])("+"|".join(map(re.escape,inverse))+r")(?![\w.'?!])")
    source=expression.sub(lambda x:inverse[x.group()],previous.decode())
    old="simpa [hw] using ih (k+1) h1 l1 h2 l2 א"
    new="simpa only [hw,UInt64.mul_zero,UInt64.zero_shiftLeft,UInt64.add_zero,UInt64.zero_shiftRight,UInt64.sub_zero,lt_self_iff_false,ite_false] using ih (k+1) h1 l1 h2 l2 א"
    assert source.count(old)==1;source=source.replace(old,new,1)
    source,renames,saving=m.compact_proof_names(source)
    result=source.encode();assert len(result)<=256000
    return result,{"previous_candidate_sha256":PREVIOUS_SOURCE,"previous_recipe_sha256":PREVIOUS_RECIPE,
                   "new_proof_names_renamed":renames,"proof_name_saving":saving,
                   "proof_delta":"Only ZMD2 zero branch defaultsimpa -> simpaonly fixedwordzero rules; no MD/MD2 recursive unfolding or matrix defs in simp set",
                   "runtime_delta":"NONE after proof-name alpha inversion; zeroB directrecursion and all originalsource36 runtime exact unchanged from7100",
                   "motivation":"Rootrequest182200 Mobile600s statementtimeout is external evidence of recursive-simp risk, not evidence7100 timedout. This is a preventative source-only repair, UNCOMPILED.",
                   "next":"If zeroB route selected later, bounded helper/prefix discriminator before any600s fullreplay. Do not add anotherCI now or cancel/change any running source.",
                   "publication":"Ownrecipe/receipts only; whole Kernelprivate/ephemeral"}
def transform(raw,submission=36,variant="mixer36-zero-b-v2"):
    assert submission==36 and variant=="mixer36-zero-b-v2"
    return build(raw)[0]
if __name__=="__main__":
    p=argparse.ArgumentParser();p.add_argument("--source",type=Path,required=True);p.add_argument("--output",type=Path);p.add_argument("--receipt",type=Path,required=True)
    a=p.parse_args();result,meta=build(a.source.read_bytes())
    if a.output:a.output.parent.mkdir(parents=True,exist_ok=True);a.output.write_bytes(result)
    out={"at_utc":datetime.now(timezone.utc).isoformat(),"candidate_sha256":sha(result),"candidate_bytes":len(result),"free_bytes":256000-len(result),"recipe_sha256":sha(Path(__file__).read_bytes()),**meta,"state":"PROOF_ONLY_REPAIR_ACTUAL_ALL12_NOT_COMPILED","gate":"UNKNOWN","native_speed":"UNKNOWN","extra_CI_request":False}
    a.receipt.write_text(json.dumps(out,indent=2,ensure_ascii=False)+"\n",encoding="utf-8")
    print(json.dumps({k:out[k]for k in ["candidate_sha256","candidate_bytes","free_bytes","recipe_sha256","state"]}))
