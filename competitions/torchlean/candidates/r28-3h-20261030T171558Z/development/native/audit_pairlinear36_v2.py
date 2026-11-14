"""The sole dispatch-literal change has distinct source/size/policy evidence."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,importlib.util,json,sys
sys.dont_write_bytecode=True
HERE=Path(__file__).resolve().parent;ROUND=HERE.parents[1]
def load(p,name):
    s=importlib.util.spec_from_file_location(name,p);m=importlib.util.module_from_spec(s);s.loader.exec_module(m);return m
def sha(b):return hashlib.sha256(b).hexdigest()
if __name__=="__main__":
    r27=ROUND.parent/"r27-5h-20261029T194443Z"
    raw=(ROUND/"competition-state/source-private/official-36.lean").read_bytes()
    donor=(r27/"competition-state/source-private/submission27-Kernel.lean").read_bytes()
    v1,_=load(HERE/"build_gemm36_pairlinear.py","r28_v2_audit_v1").build(raw,donor)
    v2,meta=load(HERE/"build_gemm36_pairlinear_v2.py","r28_v2_audit_v2").build(raw,donor)
    same,_=load(HERE/"build_gemm36_pairlinear_v2.py","r28_v2_audit_v22").build(raw,donor)
    assert v2==same
    assert v1.count(b"if k<20||!")==1 and v2.count(b"if k<1||!")==1
    assert v1.replace(b"if k<20||!",b"if k<1||!")==v2
    policy=load(r27/"development/native/patch_public.py","r28_v2_policy").policy_check(v2)
    assert policy["passed"]
    out={"at_utc":datetime.now(timezone.utc).isoformat(),"candidate_sha256":sha(v2),"candidate_bytes":len(v2),"free_bytes":256000-len(v2),
         "recipe_sha256":sha((HERE/"build_gemm36_pairlinear_v2.py").read_bytes()),"v1_sha256":sha(v1),"sole_delta":"dispatch literal20->1", "two_build_bytes_equal":True,"original_intake_policy":policy,
         "shared_static_review":"PAIRLINEAR36-STATIC-AUDIT.json and PAIRLINEAR36-ROOT-REQUEST-REVIEW.json cover unchanged dependency/name closure; exact new gate stillUNKNOWN",
         "dispatch_gap_evidence":"Prior pinned mixer-call-coverage.json shows k=T8..32; current runner model/config/proof equality remainsRoot responsibility. Source36Ya3M allpositivek branch verified directly.",
         "no_native_feedback_used":True,"native_speed":"UNKNOWN", "all12_kernel_axioms":"UNKNOWN_NOT_COMPILED"}
    (HERE/"PAIRLINEAR36-V2-STATIC-AUDIT.json").write_text(json.dumps(out,indent=2,ensure_ascii=False)+"\n",encoding="utf-8")
    print(json.dumps({k:out[k] for k in ["candidate_sha256","candidate_bytes","free_bytes","sole_delta"]}))
