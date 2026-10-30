"""Exact-source, deletion-reference, and original policy preflight; no Lean run."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,importlib.util,json,re,sys
sys.dont_write_bytecode=True
HERE=Path(__file__).resolve().parent
ROUND=HERE.parents[1]
R27=ROUND.parent/"r27-5h-20261029T194443Z"
def load(p,name):
    spec=importlib.util.spec_from_file_location(name,p);m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m);return m
def sha(x):return hashlib.sha256(x).hexdigest()
if __name__=="__main__":
    recipe=load(HERE/"build_gemm36_pairlinear.py","r28_pairlinear_recipe")
    raw=(ROUND/"competition-state/source-private/official-36.lean").read_bytes()
    donor=(R27/"competition-state/source-private/submission27-Kernel.lean").read_bytes()
    a,meta=recipe.build(raw,donor);b,_=recipe.build(raw,donor)
    assert a==b
    source=raw.decode();begin=source.index("def MPc ");end=source.index("lemma ZLj ",begin)
    deleted=re.findall(r"(?m)^(?:@\[[^\n]*\]\s*)?(?:def|lemma|theorem)\s+([\w']+)",source[begin:end])
    left=source[:begin]+source[end:]
    left=left.replace("dense:=⟨YaVM,Ya3M⟩","").replace("ZMV0,ZcC,ZM3,Zc0,ZdC,ZdN,Zdt]","")
    live={n:len(re.findall(r"(?<![\w.'?!])"+re.escape(n)+r"(?![\w.'?!])",left)) for n in deleted}
    assert not any(live.values()),live
    base_decls=load(HERE/"source_capability_map.py","r28_source_map").declarations(source)
    new_decls=load(HERE/"source_capability_map.py","r28_source_map2").declarations(a.decode())
    unchanged=[n for n in base_decls if n not in deleted and n not in ["kernels","correct"]]
    assert all(base_decls[n]["body"]==new_decls[n]["body"] for n in unchanged)
    policy=load(R27/"development/native/patch_public.py","r28_original_policy").policy_check(a)
    assert policy["passed"]
    out={"at_utc":datetime.now(timezone.utc).isoformat(),"candidate_sha256":sha(a),"candidate_bytes":len(a),
         "recipe_sha256":sha((HERE/"build_gemm36_pairlinear.py").read_bytes()),"two_build_bytes_equal":True,
         "deleted_declarations":deleted,"deleted_external_reference_counts":live,
         "unchanged_existing_declarations":len(unchanged),"original_intake_policy":policy,
         "proof_boundary":"Submission.correct remains actual all12 declaration, but new source has NOT been Lean compiled or checked by kernel/axiom gate",
         "native_boundary":"No local native build/timing; original source36 official result does not transfer performance to this recipe",
         "next":"Root sole CI: full original all12 gate, then complete Mixer timed screen; on source edit freeze new candidate and use new group"}
    (HERE/"PAIRLINEAR36-STATIC-AUDIT.json").write_text(json.dumps(out,indent=2,ensure_ascii=False)+"\n",encoding="utf-8")
    print(json.dumps({k:out[k] for k in ["candidate_sha256","candidate_bytes","two_build_bytes_equal","unchanged_existing_declarations"]}))
