"""Verify the preventive recursive-simp repair changes proof only."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,importlib.util,json,re,sys
sys.dont_write_bytecode=True
HERE=Path(__file__).resolve().parent;ROUND=HERE.parents[1]
def load(p,name):
    s=importlib.util.spec_from_file_location(name,p);m=importlib.util.module_from_spec(s);s.loader.exec_module(m);return m
def sha(b):return hashlib.sha256(b).hexdigest()
def restore(raw,mapping):
    inverse={b:a for a,b in mapping.items()}
    expr=re.compile(r"(?<![\w.'?!])("+"|".join(map(re.escape,inverse))+r")(?![\w.'?!])")
    return expr.sub(lambda m:inverse[m.group()],raw.decode())
if __name__=="__main__":
    raw=(ROUND/"competition-state/source-private/official-36.lean").read_bytes()
    v1,m1=load(HERE/"build_mixer36_zero_b.py","r28_v1_zeroaudit").build(raw)
    v2,m2=load(HERE/"build_mixer36_zero_b_v2.py","r28_v2_zeroaudit").build(raw)
    repeated,_=load(HERE/"build_mixer36_zero_b_v2.py","r28_v22_zeroaudit").build(raw);assert v2==repeated
    decl=load(HERE/"source_capability_map.py","r28_zero2_decls").declarations
    a,b=decl(restore(v1,m1["proof_names_renamed"])),decl(restore(v2,m2["new_proof_names_renamed"]))
    assert a.keys()==b.keys()
    changed=[n for n in a if a[n]["body"]!=b[n]["body"]];assert changed==["ZMD2"],changed
    assert "simpa only [hw," in b["ZMD2"]["body"]
    policy=load(ROUND.parent/"r27-5h-20261029T194443Z/development/native/patch_public.py","r28_zero2_policy").policy_check(v2);assert policy["passed"]
    out={"at_utc":datetime.now(timezone.utc).isoformat(),"candidate_sha256":sha(v2),"candidate_bytes":len(v2),"free_bytes":256000-len(v2),"recipe_sha256":sha((HERE/"build_mixer36_zero_b_v2.py").read_bytes()),"two_build_bytes_equal":True,"original_intake_policy":policy,
         "changed_after_proof_alpha_inverse":changed,"runtime_definitions_after_alpha_inverse_byte_equal":True,"finalactualall12_after_alpha_inverse_byte_equal":a["correct"]["body"]==b["correct"]["body"],
         "simp_set":"Only hw, UInt64.mul_zero/zero_shiftLeft/add_zero/zero_shiftRight/sub_zero, lt_self_iff_false, ite_false. No recursive MD/MD2/Yai or default simp database.",
         "gate":"UNKNOWN_NOT_COMPILED","native":"UNKNOWN. No runtimealgorithm changed from7100; no generatedC/native identity observed.",
         "boundary":"CI2 externalMobile600stimeout motivated bounded proofengineering only, not a failure result for7100. Noextraqueue; standalone/prefix cap120 before any later600s fullreplay."}
    (HERE/"ZERO-B-V2-STATIC-AUDIT.json").write_text(json.dumps(out,indent=2,ensure_ascii=False)+"\n",encoding="utf-8")
    print(json.dumps({k:out[k]for k in ["candidate_sha256","candidate_bytes","free_bytes","changed_after_proof_alpha_inverse"]}))
