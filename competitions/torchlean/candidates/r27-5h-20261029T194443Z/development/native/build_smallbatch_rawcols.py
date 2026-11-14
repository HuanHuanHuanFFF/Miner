"""Own small-batch scheduling patch over exact public12, not source27.

Four-column raw arithmetic and all exception/bias handling are reused from12;
the added proof connects the actual new scheduling definition to linearSpec.
"""
from pathlib import Path
import argparse
import hashlib
import importlib.util
import json
import sys

sys.dont_write_bytecode=True
HERE=Path(__file__).resolve().parent
PIN="e2c1f1f1ba52e32563fb193ceea7e2a271b989fd3ba2eb16cff747987879b521"

def sha(data):
    return hashlib.sha256(data).hexdigest()

def transform(data,submission=12,variant="smallbatch-rawcols-v1"):
    assert submission==12 and variant=="smallbatch-rawcols-v1" and sha(data)==PIN
    text=data.decode("utf-8")
    marker="def kernels:Kernels where"
    assert text.count(marker)==1
    text=text.replace(marker,(HERE/"SmallBatchRawColumns.lean.inc").read_text(encoding="utf-8")+"\n"+marker,1)
    old="dense:=⟨YaV,kernels0.dense.2⟩"
    assert text.count(old)==1
    text=text.replace(old,"dense:=⟨r27LinearSmallBatch,kernels0.dense.2⟩",1)
    old="ZcC,T4b,Zdt]"
    assert text.count(old)==1
    text=text.replace(old,"ZcC,T4b,Zdt,r27LinearSmallBatch_eq]",1)
    return text.encode("utf-8")

def main():
    p=argparse.ArgumentParser()
    p.add_argument("--source",type=Path,required=True)
    p.add_argument("--output",type=Path)
    p.add_argument("--receipt",type=Path,required=True)
    a=p.parse_args()
    result=transform(a.source.read_bytes())
    spec=importlib.util.spec_from_file_location("r27_rawcols_policy",HERE/"patch_public.py")
    m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m)
    report={"id":"public12-smallbatch-rawcols-v1","upstream_sha256":PIN,
            "candidate_sha256":sha(result),"candidate_bytes":len(result),
            "owned_extension_sha256":sha((HERE/"SmallBatchRawColumns.lean.inc").read_bytes()),
            "status":"ACTUAL12_CORRECT_WITH_SCHEDULING_EQ_PROOF_NOT_COMPILED",
            "mechanism":"rows=1 uses alreadyproved native4outputcolumn loop; no P preparation, arithmetic unchanged; otherrows retain originalYaV",
            "proof_interfaces":["Yuc4","Zk4","ZB","ZcB","gO","ZcC"],
            "correctness":"Bias/zero/special/shape behavior inherited onlyafter actualnew proofscompile; no acceptanceclaim yet",
            "cost":"UNKNOWN; rawdecode may lose to preparedP even with4columnreuse; complete B1 costs required",
            "policy":m.policy_check(result),"no_source27_dependency":True,
            "publication":"Only ownedpatch/proof/receipt public; full12output stayslocal/ephemeral"}
    if a.output:
        a.output.parent.mkdir(parents=True,exist_ok=True);a.output.write_bytes(result)
    a.receipt.write_text(json.dumps(report,indent=2)+"\n",encoding="utf-8")
    print(json.dumps(report,indent=2))

if __name__=="__main__":
    main()
