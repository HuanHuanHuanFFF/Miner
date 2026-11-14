"""Two proof-only repairs over the exact already-dispatched batch2 recipe.

Preserve old bytes/receipt and delegate reconstruction to its hash-bound frozen
adapter. No source12 implementation or old runtime body is embedded here.
"""
from pathlib import Path
import argparse
import hashlib
import importlib.util
import json
import re
import sys

sys.dont_write_bytecode=True
ROOT=next(p for p in Path(__file__).resolve().parents if (p/"AGENTS.md").is_file())
ADAPTER=ROOT/"competitions/torchlean/candidates/r27-5h-20261029T194443Z/development/ci-bridge/batch2/adapter.py"
ADAPTER_SHA="393a12f05166b527f265afcc5d00bfe2db4a3f0bda415fabb04116efcd8a2ff9"
OLD_SHA="61b98cc582a48723c0f184e49420fe97b449731a145d47d1920d3b871e2e76aa"

def sha(data):
    return hashlib.sha256(data).hexdigest()

def runtime_definitions(text):
    pattern=re.compile(r"^(?:@\[[^\n]*\] )?(?:(?:noncomputable|private) )?(def|lemma|theorem) ([^\s(:]+)",re.M)
    declarations=list(pattern.finditer(text))
    return {m.group(2):text[m.start():(declarations[i+1].start() if i+1<len(declarations) else len(text))]
            for i,m in enumerate(declarations) if m.group(1)=="def"}

def reconstruct(data):
    assert sha(ADAPTER.read_bytes())==ADAPTER_SHA
    spec=importlib.util.spec_from_file_location("r27_frozen_norm_prep_batch2",ADAPTER)
    mod=importlib.util.module_from_spec(spec);spec.loader.exec_module(mod)
    original=mod.transform(data,12,"norm-prep")
    assert sha(original)==OLD_SHA
    text=original.decode("utf-8")
    replacements=[
        ("    rw [r27SquareLoop, rsU, if_neg (by omega), if_neg (by omega)]\n    rfl",
         "    rw [r27SquareLoop, rsU, if_neg (by omega), if_neg (by omega)]"),
        ("unfold YaEf YaE;rw[r27SquareLoop_eq];rw[r27MinIndex_eq];dsimp only",
         "unfold YaEf YaE;dsimp only;simp only[r27MinIndex_eq,r27SquareLoop_eq];dsimp only"),
    ]
    for before,after in replacements:
        assert text.count(before)==1,before
        text=text.replace(before,after,1)
    old_runtime=runtime_definitions(original.decode("utf-8"))
    new_runtime=runtime_definitions(text)
    assert old_runtime==new_runtime,"Proof-only repair changed a runtime declaration"
    return text.encode("utf-8"),len(old_runtime)

def transform(data,submission,variant):
    assert submission==12 and variant=="norm-prep-proof2"
    return reconstruct(data)[0]

def main():
    p=argparse.ArgumentParser()
    p.add_argument("--source",type=Path,required=True)
    p.add_argument("--output",type=Path)
    p.add_argument("--receipt",type=Path,required=True)
    a=p.parse_args()
    result,count=reconstruct(a.source.read_bytes())
    here=Path(__file__).resolve().parent
    spec=importlib.util.spec_from_file_location("r27_norm_repair_policy",here/"patch_public.py")
    mod=importlib.util.module_from_spec(spec);spec.loader.exec_module(mod)
    report={"id":"public12-norm-prep-proof2","prior_candidate_sha256":OLD_SHA,
            "candidate_sha256":sha(result),"candidate_bytes":len(result),
            "runtime_definitions_byte_identical":True,"runtime_definition_count":count,
            "evidence":"CI40948208583 norm-prep build.log/24afc4c4:1708 redundantrfl;2333 let-boundrw",
            "repairs":["Remove redundant rfl after closed zero-case rewrite", "Zeta-expand client lets before simp exactMin/Square projection lemmas"],
            "status":"ACTUAL12_PROOF_REPAIR_NOT_COMPILED_RUNTIME_UNCHANGED",
            "policy":mod.policy_check(result),"upstream_publication":"LOCAL_OR_EPHEMERAL_ONLY"}
    if a.output:
        a.output.parent.mkdir(parents=True,exist_ok=True);a.output.write_bytes(result)
    a.receipt.write_text(json.dumps(report,indent=2)+"\n",encoding="utf-8")
    print(json.dumps(report,indent=2))

if __name__=="__main__":
    main()
