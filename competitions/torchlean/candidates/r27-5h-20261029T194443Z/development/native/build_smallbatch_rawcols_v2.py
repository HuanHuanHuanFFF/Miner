"""Dense-input-only refinement of the new source12 small-batch scheduler.

Sparse inputs retain the already-pruned prepared-P implementation; the extra
count is O(inW), never O(inW*outW), and runs only when rows=1. No new arithmetic.
"""
from pathlib import Path
import argparse
import hashlib
import importlib.util
import json
import sys

sys.dont_write_bytecode=True
HERE=Path(__file__).resolve().parent

def sha(data):
    return hashlib.sha256(data).hexdigest()

def transform(data,submission=12,variant="smallbatch-rawcols-v2"):
    assert submission==12 and variant=="smallbatch-rawcols-v2"
    spec=importlib.util.spec_from_file_location("r27_smallbatch_rawcols_v1",HERE/"build_smallbatch_rawcols.py")
    m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m)
    raw=m.transform(data,12,"smallbatch-rawcols-v1")
    assert sha(raw)=="bf383d07cc6dbab387e7cfe7411b24191fc89e9d7f3c9592ff750a62fab4d1e1"
    text=raw.decode("utf-8")
    before="  if rows == 1 then r27RawColumns rows inW outW relu input weights bias\n  else YaV rows inW outW relu input weights bias"
    after="""  if rows == 1 then
    let count := input.foldl (fun total word =>
      if word &&& 0x7fffffff == 0 then total else total + 1) (0 : Nat)
    if 4 * count > 3 * inW then r27RawColumns rows inW outW relu input weights bias
    else YaV rows inW outW relu input weights bias
  else YaV rows inW outW relu input weights bias"""
    assert text.count(before)==1
    text=text.replace(before,after,1)
    before="  unfold r27LinearSmallBatch\n  split\n  · rw [r27RawColumns_eq]\n  · rw [ZcC]"
    after="""  unfold r27LinearSmallBatch
  split
  · dsimp only
    split
    · rw [r27RawColumns_eq]
    · rw [ZcC]
  · rw [ZcC]"""
    assert text.count(before)==1
    return text.replace(before,after,1).encode("utf-8")

def main():
    p=argparse.ArgumentParser()
    p.add_argument("--source",type=Path,required=True)
    p.add_argument("--output",type=Path)
    p.add_argument("--receipt",type=Path,required=True)
    a=p.parse_args()
    result=transform(a.source.read_bytes())
    spec=importlib.util.spec_from_file_location("r27_smallbatch_rawcols2_policy",HERE/"patch_public.py")
    m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m)
    report={"id":"public12-smallbatch-rawcols-v2","candidate_sha256":sha(result),"candidate_bytes":len(result),
            "actual_entry":"Submission.kernels / Submission.correct","proof_status":"OWN_SCHEDULING_EQ_PLUS_ORIGINAL12_DECLARED_NOT_COMPILED",
            "changes":"Onlyrows1 with>75percent nonzeroinputs selects existing native4-column loop withoutP construction; sparseorotherrows retain originalprunedYaV",
            "cost":"Completecall gainUNKNOWN; decodedraw4cols canstilllose toP, so no benefitclaimbeforefullmodelpaireddata",
            "shape_specials":"Both branches intendedequallinearSpec unconditionally; bias/specials/zero/empty semantics come from existingprovedYaU/YaUc4 afterthe newproofcompiles",
            "policy":m.policy_check(result),"source27_dependency":False,
            "source_handling":"Ownrecipe+proof public; full12source local/ephemeralonly"}
    if a.output:
        a.output.parent.mkdir(parents=True,exist_ok=True);a.output.write_bytes(result)
    a.receipt.write_text(json.dumps(report,indent=2)+"\n",encoding="utf-8")
    print(json.dumps(report,indent=2))

if __name__=="__main__":
    main()
