"""One source/closure/policy review for the requested input-zero NativeOnly."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,importlib.util,json,re,sys
sys.dont_write_bytecode=True
HERE=Path(__file__).resolve().parent;ROUND=HERE.parents[1]
def load(p,name):
    s=importlib.util.spec_from_file_location(name,p);m=importlib.util.module_from_spec(s);s.loader.exec_module(m);return m
def sha(b):return hashlib.sha256(b).hexdigest()
if __name__=="__main__":
    raw=(ROUND/"competition-state/source-private/official-36.lean").read_bytes()
    recipe=load(HERE/"build_mixer36_input_zero_cost.py","r28_inputzero_audit")
    control=recipe.norm_control(raw);a,meta=recipe.build(raw);b,_=recipe.build(raw);assert a==b
    od,nd=recipe.declarations(control.decode()),recipe.declarations(a.decode())
    assert set(od)-set(nd)==set(meta["pruned_proofs"])
    assert set(nd)-set(od)=={"R28MD2InputZero","R28HasInputZero"}
    changed=[]
    for name in od.keys()&nd.keys():
        x,y=od[name],nd[name]
        if control.decode()[x["start"]:x["end"]]!=a.decode()[y["start"]:y["end"]]:changed.append(name)
    assert set(changed)=={"MVj","MVi","YaVM"},changed
    for name in meta["pruned_proofs"]:assert not re.search(r"(?<![\w.'?!])"+re.escape(name)+r"(?![\w.'?!])",a.decode())
    def body(d,s,name):return s[d[name]["start"]:d[name]["end"]]
    assert body(od,control.decode(),"MD2")==body(nd,a.decode(),"MD2")
    assert body(od,control.decode(),"kernels")==body(nd,a.decode(),"kernels")
    assert body(od,control.decode(),"Ya3M")==body(nd,a.decode(),"Ya3M")
    policy=load(ROUND.parent/"r27-5h-20261029T194443Z/development/native/patch_public.py","r28_inputzero_policy").policy_check(a)
    # Intake/policy can pass without correct; statement/fullgate intentionally cannot.
    assert policy["passed"]
    model=json.loads((HERE/"MIXER-INPUT-ZERO-CENSUS.json").read_text())
    out={"at_utc":datetime.now(timezone.utc).isoformat(),"candidate_sha256":sha(a),"candidate_bytes":len(a),"free_bytes":256000-len(a),"recipe_sha256":sha((HERE/"build_mixer36_input_zero_cost.py").read_bytes()),
         "control_sha256":sha(control),"norm_recipe_sha256":meta["norm_recipe_sha256"],"two_build_bytes_equal":True,"intake_policy_only":policy,"pruned_proofs":meta["pruned_proofs"],
         "changed_existing_runtime":sorted(changed),"unchanged_control_declarations":len(od)-len(changed)-len(meta["pruned_proofs"]),"MD2_original_hot_loop_byte_equal":True,"original_GEMM_and_kernel_fields_byte_equal":True,
         "actual_binding":"YaVM after oldpreparation -> MVi(rawHasZero) -> MVj(flag) -> directMD2InputZero onlyifflag; dense nozero calls originalMD2. No new extra prepared payload/correction, no functionvaluedcall selector.",
         "model_summary":{"cells":len(model["cells"]),"oldseen_hashes_match":True,"linear1_zero_calls":0,"linear2_zero_calls":18,"probe_words":6211,"second_native_base_products":274108,"inputzero_deleted_products":137559,"doublezero_terms":36522,"singlezero_terms":64515,"raw_uint64_identities":16000},
         "proof_boundary":"UNPROVED_NATIVE_RESEARCH_ONLY, correct absent; fullgate statement intentionallymissing. Runtime zero identities/oldnorm26fullgate do not certify this exact source. Nativecompile/checksums/wholeweightedscore UNKNOWN.",
         "cost_risk":"Two data-dependent zero tests may mispredict or ifconvert; percall scan/perdot dispatch/oddrowfallback/cacheprep/destruction retained in full timing. Counts are not time or qualification probability.",
         "next":"Root191300 requested onecandidate. If no Mobile qualifying signal, may pair with alreadyplannedNorm26 standard retention, one existingfinalbatch only; otherwise hold and prioritize currentqualifier proof/confirmation."}
    (HERE/"INPUT-ZERO-COST-STATIC-AUDIT.json").write_text(json.dumps(out,indent=2,ensure_ascii=False)+"\n",encoding="utf-8")
    print(json.dumps({k:out[k]for k in ["candidate_sha256","candidate_bytes","free_bytes","changed_existing_runtime","unchanged_control_declarations"]}))
