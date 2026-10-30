"""Source/size/policy/deletion audit for the independent BN traversal candidate."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,importlib.util,json,re,sys
sys.dont_write_bytecode=True
HERE=Path(__file__).resolve().parent
ROUND=HERE.parents[1]
R27=ROUND.parent/"r27-5h-20261029T194443Z"
def load(path,name):
    spec=importlib.util.spec_from_file_location(name,path);m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m);return m
def sha(x):return hashlib.sha256(x).hexdigest()
if __name__=="__main__":
    m=load(HERE/"build_resnet11_inplace_bn.py","r28_bn_recipe")
    base=(ROUND/"competition-state/source-private/official-11.lean").read_bytes()
    donor=(ROUND/"competition-state/source-private/official-53.lean").read_bytes()
    result,meta=m.build(base,donor);same,_=m.build(base,donor);assert result==same
    assert len(result)<=256000
    old=base.decode();start=old.index("def Ysj ");stop=old.index("def Ysm ",start)
    outside=old[:start]+old[stop:]
    outside=outside.replace("elem:=⟨YbkF,Ybl,Ybf,Ybe⟩","").replace("ZdSF,ZdC,ZdB,  ZdT]","")
    references={name:len(re.findall(r"(?<![\w.'?!])"+re.escape(name)+r"(?![\w.'?!])",outside)) for name in meta["removed_declarations"]}
    assert not any(references.values())
    declarations=load(HERE/"source_capability_map.py","r28_bn_source_map").declarations
    before=declarations(old);after=declarations(result.decode())
    unchanged=[name for name in before if name not in meta["removed_declarations"]+["kernels","correct"]]
    assert all(before[name]["body"]==after[name]["body"] for name in unchanged)
    policy=load(R27/"development/native/patch_public.py","r28_bn_policy").policy_check(result)
    assert policy["passed"]
    out={"at_utc":datetime.now(timezone.utc).isoformat(),"candidate_sha256":sha(result),"candidate_bytes":len(result),"free_bytes":256000-len(result),
         "recipe_sha256":sha((HERE/"build_resnet11_inplace_bn.py").read_bytes()),"two_build_bytes_equal":True,"original_intake_policy":policy,
         "deleted_external_reference_counts":references,"unchanged_existing_declarations":len(unchanged),
         "arithmetic_scope":"Source11 Ysx/YsxE/YaY and final FMA unchanged byte-for-byte; donor53 output clipping not imported. Cache my/iy/mz/iq outside f closure.",
         "native_scope":"Input-backed array uset may reuse storage if exclusive; otherwise runtime copies before first mutation. All allocations/refcounts are inside full-model call; no measured benefit claim.",
         "proof":"Actual new all12 declared, NOT_COMPILED. Static audit does not prove Lean elaboration/statement/kernel/axioms.",
         "coordination":"Read172700. Distinct from Root batch1 mapIdx add; intended optionally compose after stage cost evidence, new exact hash/gate/confirmation required."}
    (HERE/"INPLACE-BN11-STATIC-AUDIT.json").write_text(json.dumps(out,indent=2,ensure_ascii=False)+"\n",encoding="utf-8")
    print(json.dumps({k:out[k] for k in ["candidate_sha256","candidate_bytes","free_bytes","unchanged_existing_declarations"]}))
