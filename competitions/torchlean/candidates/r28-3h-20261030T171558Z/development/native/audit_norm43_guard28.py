"""Exact source/policy and finite sharp-bound controls for public43guard28."""
from pathlib import Path
from datetime import datetime,timezone
from collections import Counter
import hashlib,importlib.util,json,random,sys,time
sys.dont_write_bytecode=True
HERE=Path(__file__).resolve().parent;ROUND=HERE.parents[1]
def load(p,name):
    s=importlib.util.spec_from_file_location(name,p);m=importlib.util.module_from_spec(s);s.loader.exec_module(m);return m
def sha(b):return hashlib.sha256(b).hexdigest()
if __name__=="__main__":
    started=time.monotonic();raw=(ROUND/"competition-state/source-private/official-43.lean").read_bytes()
    recipe=load(HERE/"build_norm43_guard28.py","r28_norm43_28_recipe")
    a,meta=recipe.build(raw);b,_=recipe.build(raw);assert a==b
    assert b"hR28q" not in raw and b"hR28pk" not in raw
    decl=load(HERE/"source_capability_map.py","r28_norm43_28_decls").declarations
    old,new=decl(raw.decode()),decl(a.decode());assert old.keys()==new.keys()
    changed=[n for n in old if old[n]["body"]!=new[n]["body"]];assert changed==["Ya7G","Ya7Ge"],changed
    assert old["correct"]["body"]==new["correct"]["body"]
    policy=load(ROUND.parent/"r27-5h-20261029T194443Z/development/native/patch_public.py","r28_norm43_28_policy").policy_check(a);assert policy["passed"]
    rng=random.Random(0x4328);count=0;MASK=(1<<64)-1
    for _ in range(12000):
        D=rng.randrange(1,1<<36);r=rng.randrange(D);ks=rng.randrange(29);q=rng.randrange(1<<(61-ks))
        ra=r<<ks;assert ra<1<<64 and (ra&MASK)==ra and ra//D<1<<28
        qa=(q<<ks)+ra//D;assert qa<1<<62;count+=1
    # D is factorized as n*mantissa within the original numerical range.
    D=4095*((1<<24)-1);r=D-1;ks=29
    exact=r<<ks;wrapped=exact&MASK
    assert exact>=1<<64 and exact//D!=wrapped//D
    old_model=ROUND.parent/"r27-5h-20261029T194443Z/research/board-frontier/norm-frontier-result.json"
    saved=json.loads(old_model.read_text())["cells"]
    selected=[v for v in saved if v["seed"]==27051001 and v["profile"]=="typical"]
    assert len(selected)==6
    counts={str(cap):Counter()for cap in [8,26,28]}
    for row in selected:
        for cap in [8,26,28]:counts[str(cap)].update(row["census"][f"cap{cap}"])
    out={"at_utc":datetime.now(timezone.utc).isoformat(),"candidate_sha256":sha(a),"candidate_bytes":len(a),"free_bytes":256000-len(a),"recipe_sha256":sha((HERE/"build_norm43_guard28.py").read_bytes()),
         "two_build_bytes_equal":True,"changed_existing_declarations":changed,"unchanged_existing_declarations":len(old)-len(changed),"original_intake_policy":policy,"finalactualall12theorem_byte_equal":True,
         "finite_arithmetic_fixtures":count,"uniform29_bound_counterexample":{"n":4095,"mantissa":(1<<24)-1,"D":D,"r":r,"ks":ks,"exact_ra":exact,"wrapped_ra_uint64":wrapped,"exact_ra_divD":exact//D,"wrapped_ra_divD":wrapped//D,"classification":"UniformD<2^36 arithmetic bound counterexample, not a fullkernel input witness"},
         "old_seen_NMLP_guard_counts":{"source":str(old_model.relative_to(ROUND.parent)),"sha256":sha(old_model.read_bytes()),"cells":6,"cap_counts":{k:dict(v)for k,v in counts.items()},"boundary":"Reused old finite math census only; no source43native replay or timing, omits finalrrsG fallback"},
         "freshnewgate":"UNKNOWN_NOT_COMPILED","native_speed":"UNKNOWN","family":"Sameexactguardfamily26; cap28 has sharperuniformUInt64 bound. Not independent successes or a currentchampion claim.",
         "queue":"NoextraCIrequest. Only if source36norm26 signal and remainingwindow justify a differentstrongbaseline/board; new exactgate and complete NMLP score/refresh required.","audit_wall_seconds":time.monotonic()-started}
    (HERE/"NORM43-GUARD28-STATIC-AUDIT.json").write_text(json.dumps(out,indent=2,ensure_ascii=False)+"\n",encoding="utf-8")
    print(json.dumps({k:out[k]for k in ["candidate_sha256","candidate_bytes","free_bytes","unchanged_existing_declarations","finite_arithmetic_fixtures","old_seen_NMLP_guard_counts"]}))
