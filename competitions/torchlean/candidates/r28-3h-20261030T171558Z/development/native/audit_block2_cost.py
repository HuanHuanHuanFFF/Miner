"""Static binding audit for an explicitly unproved NativeOnly prototype."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,importlib.util,json,re,sys
sys.dont_write_bytecode=True
HERE=Path(__file__).resolve().parent;ROUND=HERE.parents[1]
def load(path,name):
    s=importlib.util.spec_from_file_location(name,path);m=importlib.util.module_from_spec(s);s.loader.exec_module(m);return m
def sha(x):return hashlib.sha256(x).hexdigest()
if __name__=="__main__":
    recipe=load(HERE/"build_mixer36_block2_cost.py","r28_block2_cost_audit")
    raw=(ROUND/"competition-state/source-private/official-36.lean").read_bytes()
    a,meta=recipe.build(raw);b,_=recipe.build(raw);assert a==b
    declarations=load(HERE/"source_capability_map.py","r28_block2_cost_decl").declarations
    old,new=declarations(raw.decode()),declarations(a.decode())
    for name in meta["pruned_proofs"]:assert name not in new
    assert "correct" not in new
    unchanged=[n for n in old if n not in meta["pruned_proofs"]+["MVj"]]
    assert all(old[n]["body"]==new[n]["body"] for n in unchanged)
    for name in meta["pruned_proofs"]:
        assert not re.search(r"(?<![\w.'?!])"+re.escape(name)+r"(?![\w.'?!])",a.decode())
    assert "R28MD2B2 X W b" in new["MVj"]["body"]
    assert "then R28MD2B2 else MD2" not in new["MVj"]["body"]
    assert old["kernels"]["body"]==new["kernels"]["body"]
    out={"at_utc":datetime.now(timezone.utc).isoformat(),"candidate_sha256":sha(a),"candidate_bytes":len(a),"recipe_sha256":sha((HERE/"build_mixer36_block2_cost.py").read_bytes()),
         "two_build_bytes_equal":True,"unchanged_old_declarations":len(unchanged),"deleted_proofs":meta["pruned_proofs"],"deleted_external_references":0,
         "runtime_binding":"kernels.dense.1=YaVM ->MVi->MVj ->R28MD2B2 if both bias-inclusive native widths<=14, otherwise originalMD2; tail originalMD2. Original Ya3M/GEMM and otherall12 fields unchanged.",
         "native_dispatch":"Direct branch/call, no intentional function-valued conditional; actual C/ASM not yet observed",
         "formal_state":"UNPROVED_NATIVE_RESEARCH_ONLY; correct removed, all12 gate would fail statement; no adopted/complete/certified claim",
         "model":"BLOCK2-PAIR-MODEL.json:9oldcells outputs reference hashmatch,4490pair accumulators match,110582/180132linear logicalMACs covered; no native timing or probability",
         "cost_risk":"Source-level halved signed merges on admitted pairs may be offset by boundary checks, register pressure, and native/compiler behavior. Full measured model including preparation/destruction needed.",
         "queue":"NoextraCIrequest. Root can add one NativeOnly discriminator only if it does not displace nearboard gate or final confirmation. Expensive loop proof postponed until positive cost evidence."}
    (HERE/"BLOCK2-COST-STATIC-AUDIT.json").write_text(json.dumps(out,indent=2,ensure_ascii=False)+"\n",encoding="utf-8")
    print(json.dumps({k:out[k] for k in ["candidate_sha256","candidate_bytes","unchanged_old_declarations","deleted_proofs"]}))
