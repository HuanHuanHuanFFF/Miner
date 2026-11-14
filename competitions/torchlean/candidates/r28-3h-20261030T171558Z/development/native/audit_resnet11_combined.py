"""Exact-composition source audit; no inherited proof or performance claim."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,importlib.util,json,sys
sys.dont_write_bytecode=True
HERE=Path(__file__).resolve().parent;ROUND=HERE.parents[1]
def load(p,name):
    s=importlib.util.spec_from_file_location(name,p);m=importlib.util.module_from_spec(s);s.loader.exec_module(m);return m
def sha(b):return hashlib.sha256(b).hexdigest()
if __name__=="__main__":
    recipe=load(HERE/"build_resnet11_combined.py","r28_combined_audit")
    raw=(ROUND/"competition-state/source-private/official-11.lean").read_bytes()
    donor=(ROUND/"competition-state/source-private/official-53.lean").read_bytes()
    a,meta=recipe.build(raw,donor);b,_=recipe.build(raw,donor);assert a==b
    old=recipe.declarations(raw.decode());new=recipe.declarations(a.decode())
    removed=sorted(set(old)-set(new));added=sorted(set(new)-set(old))
    changed=[n for n in old.keys()&new.keys() if old[n]!=new[n]]
    assert removed==sorted(["Ysj","YsjL","Ysk","YskE","Ybe","ZdB"])
    assert set(changed)=={"Ybf","ZdC","Yt3g","Yt3gL","kernels","correct"},changed
    policy=load(ROUND.parent/"r27-5h-20261029T194443Z/development/native/patch_public.py","r28_combined_policy").policy_check(a)
    assert policy["passed"]
    profile=next((ROUND/"evidence/41099255272").rglob("cost-profile/profile.json"))
    out={"at_utc":datetime.now(timezone.utc).isoformat(),"candidate_sha256":sha(a),"candidate_bytes":len(a),"free_bytes":256000-len(a),"recipe_sha256":sha((HERE/"build_resnet11_combined.py").read_bytes()),
         "two_build_bytes_equal":True,"original_intake_policy":policy,"removed_declarations":removed,"new_declarations":added,"changed_existing_declarations":sorted(changed),
         "existing_unchanged_declarations":len(old)-len(removed)-len(changed),"profile_read":{"path":str(profile.relative_to(ROUND)),"sha256":sha(profile.read_bytes()),"boundary":"instrumentedreferenceentrycostonly"},
         "dependencies":meta["dependencies"],"proof":"Actual complete12 kernel/correct binding present; all three changed proof paths connected. No old or component gate transfers; exact originalstatement/kernel/axioms UNKNOWN.",
         "native":"UNKNOWN. Root's originalmapidxv1 failed proof before candidatetiming; v2syntaxrepair not measured. Nativezero helper might allocate tuple; BNcopy/refcounts inside full boundary.",
         "next":"Root alreadyplanned Rescore batch can select this exact fit if useful; no added queue request. Originalsource11 control and fresh complete paired runtime required; no summingcomponentgains."}
    (HERE/"RESNET11-COMBINED-STATIC-AUDIT.json").write_text(json.dumps(out,indent=2,ensure_ascii=False)+"\n",encoding="utf-8")
    print(json.dumps({k:out[k] for k in ["candidate_sha256","candidate_bytes","free_bytes","changed_existing_declarations","existing_unchanged_declarations"]}))
