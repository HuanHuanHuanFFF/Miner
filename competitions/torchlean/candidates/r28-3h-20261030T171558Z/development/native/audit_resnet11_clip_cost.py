"""Static source binding and missing-proof boundary for fused BN cost only."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,importlib.util,json,re,sys
sys.dont_write_bytecode=True
HERE=Path(__file__).resolve().parent;ROUND=HERE.parents[1]
def load(p,name):
    s=importlib.util.spec_from_file_location(name,p);m=importlib.util.module_from_spec(s);s.loader.exec_module(m);return m
def sha(x):return hashlib.sha256(x).hexdigest()
if __name__=="__main__":
    raw=(ROUND/"competition-state/source-private/official-11.lean").read_bytes();donor=(ROUND/"competition-state/source-private/official-53.lean").read_bytes()
    combo=load(HERE/"build_resnet11_combined.py","r28_clip_audit_control")
    control,_=combo.build(raw,donor)
    recipe=load(HERE/"build_resnet11_clip_cost.py","r28_clip_audit_recipe")
    result,meta=recipe.build(raw,donor);same,_=recipe.build(raw,donor);assert result==same
    old,new=combo.declarations(control.decode()),combo.declarations(result.decode())
    assert set(old)-set(new)==set(meta["pruned_proofs"])
    assert set(new)-set(old)=={"R28NativeYsxAct"}
    changed=[n for n in old.keys()&new.keys() if old[n]!=new[n]]
    assert changed==["R28rBnChannels"],changed
    for name in meta["pruned_proofs"]:assert not re.search(r"(?<![\w.'?!])"+name+r"(?![\w.'?!])",result.decode())
    assert "correct" not in new
    out={"at_utc":datetime.now(timezone.utc).isoformat(),"candidate_sha256":sha(result),"candidate_bytes":len(result),"free_bytes":256000-len(result),"recipe_sha256":sha((HERE/"build_resnet11_clip_cost.py").read_bytes()),
         "control_sha256":sha(control),"two_build_bytes_equal":True,"unchanged_control_declarations":len(old)-len(meta["pruned_proofs"])-1,"new_helper":"R28NativeYsxAct","changed_existing_runtime":["R28rBnChannels"],"pruned_proofs":meta["pruned_proofs"],
         "complete12runtimefields_unchanged":old["kernels"]==new["kernels"],"semantic_interface":"Fused negative nativeFMA/ReLU only after old finite/width branch; native positive Ge hint retained. All source11scalar/caches/fallback/convzero/mapIdxadd bodies unchanged.",
         "formal":"UNPROVED_NATIVE_RESEARCH_ONLY, no newcorrect. Nativecompile/currentperformance/checksums UNKNOWN; all12statement would reject intentionally.",
         "future_proof_map":{"source53.N9":"source11.ZaD","source53.B6":"source11.YaPTe","source53.J2":"source11.Zca","source53.P4":"source11.Y0k","source11.Ge":"rewrite via Gc to YaPT before source53clipYaPT/clipFinish logic"},
         "future_minimum":"After positive measured cost, port generic source53clipModel/rounding lemmas with fresh names; prove helper=actYsx; rewrite originalbCp, restoreR28rBnCorrect/actualall12. Source compression/completegate/newfrozenconfirmation all still required.",
         "queue":"NoextraCIrequest, preserve prioritized nearboard core/finalconfirmation. Not proof/productioncandidate."}
    (HERE/"RESNET11-CLIP-COST-STATIC-AUDIT.json").write_text(json.dumps(out,indent=2,ensure_ascii=False)+"\n",encoding="utf-8")
    print(json.dumps({k:out[k] for k in ["candidate_sha256","candidate_bytes","unchanged_control_declarations","changed_existing_runtime","pruned_proofs"]}))
