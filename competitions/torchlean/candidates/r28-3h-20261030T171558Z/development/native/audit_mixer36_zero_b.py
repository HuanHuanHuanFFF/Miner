"""Exact source audit for zero-B native paired loop; no local native build."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,importlib.util,json,re,sys
sys.dont_write_bytecode=True
HERE=Path(__file__).resolve().parent;ROUND=HERE.parents[1]
def load(p,name):
    s=importlib.util.spec_from_file_location(name,p);m=importlib.util.module_from_spec(s);s.loader.exec_module(m);return m
def sha(b):return hashlib.sha256(b).hexdigest()
if __name__=="__main__":
    recipe=load(HERE/"build_mixer36_zero_b.py","r28_zeroB_audit_recipe")
    raw=(ROUND/"competition-state/source-private/official-36.lean").read_bytes()
    result,meta=recipe.build(raw);same,_=recipe.build(raw);assert result==same
    source=result.decode();mapping=meta["proof_names_renamed"]
    before_tokens=set(re.findall(r"[\w']+",raw.decode()))
    assert all(fresh not in before_tokens for fresh in mapping.values())
    inverse={new:old for old,new in mapping.items()}
    expr=re.compile(r"(?<![\w.'?!])("+"|".join(map(re.escape,inverse))+r")(?![\w.'?!])")
    unrenamed=expr.sub(lambda m:inverse[m.group()],source)
    decl=load(HERE/"source_capability_map.py","r28_zeroB_decls").declarations
    old,new=decl(raw.decode()),decl(unrenamed)
    unchanged=[n for n in old if n not in ["MD2","ZMD2"]]
    assert set(old)==set(new)
    assert all(old[n]["body"]==new[n]["body"] for n in unchanged)
    policy=load(ROUND.parent/"r27-5h-20261029T194443Z/development/native/patch_public.py","r28_zeroB_policy").policy_check(result)
    assert policy["passed"]
    out={"at_utc":datetime.now(timezone.utc).isoformat(),"candidate_sha256":sha(result),"candidate_bytes":len(result),"free_bytes":256000-len(result),"recipe_sha256":sha((HERE/"build_mixer36_zero_b.py").read_bytes()),
         "two_build_bytes_equal":True,"original_intake_policy":policy,"same_declaration_names_after_alpha_inverse":True,"existing_declarations_byte_equal_after_alpha_inverse":len(unchanged),
         "fresh_proof_names_absent_before":mapping,"only_semantic_declaration_changes":["MD2","ZMD2"],
         "all12_entry_preserved_after_proof_alpha_inverse":old["correct"]["body"]==new["correct"]["body"],
         "zero_identity":"For decoded shared B=0 both UInt64 products are0, shifts are0, low words and sign/carry high increments are0. Exact for all h/l/A/shift values, not dependent on benchmark distribution.",
         "proof_state":"NOT_COMPILED. ZMD2 dsimp/split/simpa branch and duplicate termination goals require exact original Lean all12/kernel/axiom gate.",
         "native_state":"UNKNOWN. Newbranch may be hoisted, left, or dominate costs; exact generated C probe and complete paired model determine usefulness.",
         "freeze":"This is a new candidate independent of queued pairlinearv1/v2 and RootMobilezero. No old/frozen source edited."}
    (HERE/"MIXER36-ZERO-B-STATIC-AUDIT.json").write_text(json.dumps(out,indent=2,ensure_ascii=False)+"\n",encoding="utf-8")
    print(json.dumps({k:out[k] for k in ["candidate_sha256","candidate_bytes","free_bytes","existing_declarations_byte_equal_after_alpha_inverse"]}))
