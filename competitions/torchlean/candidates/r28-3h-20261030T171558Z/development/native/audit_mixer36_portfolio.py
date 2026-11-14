"""One exact-source composition review, using existing fixed original policy."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,importlib.util,json,sys
sys.dont_write_bytecode=True
HERE=Path(__file__).resolve().parent;ROUND=HERE.parents[1]
def load(path,name):
    s=importlib.util.spec_from_file_location(name,path);m=importlib.util.module_from_spec(s);s.loader.exec_module(m);return m
def sha(x):return hashlib.sha256(x).hexdigest()
if __name__=="__main__":
    recipe=load(HERE/"build_mixer36_portfolio.py","r28_mixportfolio_audit")
    raw=(ROUND/"competition-state/source-private/official-36.lean").read_bytes();donor=(ROUND.parent/"r27-5h-20261029T194443Z/competition-state/source-private/submission27-Kernel.lean").read_bytes()
    a,meta=recipe.build(raw,donor);b,_=recipe.build(raw,donor);assert a==b
    control,_=recipe.load("pair").build(raw,donor);cd=recipe.declarations(control.decode());nd=recipe.declarations(a.decode())
    changed=sorted(n for n in cd.keys()&nd.keys() if cd[n]!=nd[n]);assert changed==["Ya7G","Ya7Ge","YaVM"],changed
    assert set(nd)-set(cd)=={"R28FastProbe"} and not(set(cd)-set(nd))
    assert cd["ZMV0"]==nd["ZMV0"] and cd["correct"]==nd["correct"]
    policy=load(ROUND.parent/"r27-5h-20261029T194443Z/development/native/patch_public.py","r28_mixportfolio_policy").policy_check(a);assert policy["passed"]
    out={"at_utc":datetime.now(timezone.utc).isoformat(),"candidate_sha256":sha(a),"candidate_bytes":len(a),"free_bytes":256000-len(a),"recipe_sha256":sha((HERE/"build_mixer36_portfolio.py").read_bytes()),"two_build_bytes_equal":True,
         "original_intake_policy":policy,"dependencies":meta["dependencies"],"changed_vs_pair_v2":changed,"new_declarations":["R28FastProbe"],"unchanged_existing_declarations":len(cd)-len(changed),
         "YaVM_correct_proof_and_final_all12_theorem_bytes_unchanged":True,"proof_scope":"Only norm26 Ya7Ge has proof-semantic changes; rootR mathematical quotient bound reviewed. New R28FastProbe has only termination obligation, dispatch correctness uses existing arbitrary-branch ZMV0. Whole exactall12 gate stillNOT_RUN.",
         "retains":"pairv2 positivefinitek, public36 MD2/nativeadd/LN, original small/nonfinite/shape/sentinel/fallback; profile any/probe/prepare/transpose costs are inside measured call",
         "unmeasured":"NativeC/ASM, exactnewprogram checksums, completeweightedscore/currentchampioncomparison and freshfrozenconfirmation UNKNOWN",
         "source_snapshot":"AfterRootrequest181600, ResNetnow64 with19.015percent required reduction; no stale6.07percent goal. This is available for the plannedMixer batch, not an extraCI request.",
         "publication":"Ownrecipe/receipt only; fullsource ignored/private"}
    (HERE/"MIXER-PORTFOLIO-STATIC-AUDIT.json").write_text(json.dumps(out,indent=2,ensure_ascii=False)+"\n",encoding="utf-8")
    print(json.dumps({k:out[k] for k in ["candidate_sha256","candidate_bytes","free_bytes","changed_vs_pair_v2","unchanged_existing_declarations"]}))
