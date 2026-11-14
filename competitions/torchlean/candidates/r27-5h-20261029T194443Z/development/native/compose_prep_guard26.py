"""Contingent source12-only composition; not a new queued experiment.

Combines the exact proof3 preparation repair with C's accepted guard26-v2
recipe. No source27 fetch, whole-source publication or inherited gate claim.
"""
from pathlib import Path
import argparse
import hashlib
import importlib.util
import json
import sys

sys.dont_write_bytecode=True
HERE=Path(__file__).resolve().parent
ROUND=HERE.parent.parent
GUARD=ROUND/"research/board-frontier/patch_norm_guard_v2.py"
GUARD_SHA="9fa6e555df8af97cb942b779bf7b9888fea662b4553914590f68ae5289cf0ad6"

def sha(data):
    return hashlib.sha256(data).hexdigest()

def load(name,path):
    spec=importlib.util.spec_from_file_location(name,path)
    m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m)
    return m

def transform(data,submission=12,variant="prep3-guard26-v2"):
    assert submission==12 and variant=="prep3-guard26-v2"
    assert sha(GUARD.read_bytes())==GUARD_SHA
    guard=load("r27_owned_guard26_v2",GUARD)
    prep=load("r27_owned_prep3",HERE/"repair_norm_prep_v3.py")
    before,_=prep.reconstruct(data)
    assert sha(before)=="39f377f9dad7fa358d08ea2035327527b32caa7d5f97b08244d59ffdc6e2160a"
    after=guard.transform(before.decode("utf-8")).encode("utf-8")
    compare=load("r27_owned_defs_compare",HERE/"repair_norm_prep_v2.py")
    olddefs=compare.runtime_definitions(before.decode())
    newdefs=compare.runtime_definitions(after.decode())
    assert olddefs.keys()==newdefs.keys()
    changed=[name for name in olddefs if olddefs[name]!=newdefs[name]]
    assert changed==["Ya7G"],changed
    return after

def main():
    p=argparse.ArgumentParser()
    p.add_argument("--source",type=Path,required=True)
    p.add_argument("--output",type=Path)
    p.add_argument("--receipt",type=Path,required=True)
    a=p.parse_args()
    result=transform(a.source.read_bytes())
    policy=load("r27_own_composition_policy",HERE/"patch_public.py").policy_check(result)
    report={"id":"public12-prep3-guard26-v2","candidate_sha256":sha(result),"candidate_bytes":len(result),
            "components":{"prep3":"39f377f9dad7fa358d08ea2035327527b32caa7d5f97b08244d59ffdc6e2160a",
                          "guard26_v2":"dced7848655a50a136750c1837b46f084a25ec26d13df72fe907d4a162bf1cb9"},
            "change_from_prep3":"Only Ya7G runtimebody changes, exactly ownedguard26-v2;141runtime definitionnames retained",
            "scope":"CONTINGENT_COMPOSITION_NOT_COMPILED_NOT_QUEUED_NO_GAIN_ADDITION",
            "proof":"Actual12correct entry present; acceptedguard component does not certify thiscombinedsource",
            "policy":policy,"no_source27_dependency":True,"publication":"Ownedrecipe/receipt only; full12source remains local/ephemeral"}
    if a.output:
        a.output.parent.mkdir(parents=True,exist_ok=True);a.output.write_bytes(result)
    a.receipt.write_text(json.dumps(report,indent=2)+"\n",encoding="utf-8")
    print(json.dumps(report,indent=2))

if __name__=="__main__":
    main()
