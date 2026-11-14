"""Exact one-tactic repair after the real proof2 build in40952423982.

Old source and logs stay immutable. Every runtime declaration is byte-identical
to both earlier preparation versions; no acceptance is inferred before CI.
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
PREVIOUS=HERE/"repair_norm_prep_v2.py"
PREVIOUS_SHA="047268276b50df861b188399f306095bdd470ac932167523020a5d15d1bf05d9"
OLD_SHA="40b17282cebbd1d97256f4a945edb041de5e5a00023369e235c11d8e048a3a8e"

def sha(data):
    return hashlib.sha256(data).hexdigest()

def reconstruct(data):
    assert sha(PREVIOUS.read_bytes())==PREVIOUS_SHA
    spec=importlib.util.spec_from_file_location("r27_norm_prep_proof2_exact",PREVIOUS)
    m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m)
    original,count=m.reconstruct(data)
    assert sha(original)==OLD_SHA
    before="unfold YaEf YaE;dsimp only;simp only[r27MinIndex_eq,r27SquareLoop_eq];dsimp only"
    after="unfold YaEf YaE;dsimp only;simp only[r27MinIndex_eq,r27SquareLoop_eq]"
    text=original.decode("utf-8")
    assert text.count(before)==1
    result=text.replace(before,after,1).encode("utf-8")
    assert m.runtime_definitions(original.decode())==m.runtime_definitions(result.decode())
    return result,count

def transform(data,submission,variant):
    assert submission==12 and variant=="norm-prep-proof3"
    return reconstruct(data)[0]

def main():
    p=argparse.ArgumentParser()
    p.add_argument("--source",type=Path,required=True)
    p.add_argument("--output",type=Path)
    p.add_argument("--receipt",type=Path,required=True)
    a=p.parse_args()
    result,count=reconstruct(a.source.read_bytes())
    spec=importlib.util.spec_from_file_location("r27_prep_proof3_policy",HERE/"patch_public.py")
    m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m)
    report={"id":"public12-norm-prep-proof3","prior_sha256":OLD_SHA,
            "candidate_sha256":sha(result),"candidate_bytes":len(result),
            "runtime_declarations_byte_identical":True,"runtime_definition_count":count,
            "exact_error":"40952423982 line2332:71 dsimp made no progress",
            "raw_log_sha256":"1f2e399efb0d2a12e22131d8d03265611f70859f75bd3097ac48db37b0c00121",
            "repair":"Remove only trailing dsimp after simp alreadyperformed requiredzeta/projection rewrites",
            "status":"ACTUAL12_ONE_TACTIC_REPAIR_NOT_COMPILED_NO_RUNTIME_CHANGE",
            "policy":m.policy_check(result),"whole_upstream_publication":"LOCAL_OR_EPHEMERAL_ONLY"}
    if a.output:
        a.output.parent.mkdir(parents=True,exist_ok=True);a.output.write_bytes(result)
    a.receipt.write_text(json.dumps(report,indent=2)+"\n",encoding="utf-8")
    print(json.dumps(report,indent=2))

if __name__=="__main__":
    main()
