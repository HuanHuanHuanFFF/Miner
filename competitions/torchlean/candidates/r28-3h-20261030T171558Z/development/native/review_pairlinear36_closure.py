"""One focused dependency/name review requested by Root before batch2."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,importlib.util,json,re,sys
sys.dont_write_bytecode=True
HERE=Path(__file__).resolve().parent;ROUND=HERE.parents[1]
def load(path,name):
    spec=importlib.util.spec_from_file_location(name,path);m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m);return m
def sha(b):return hashlib.sha256(b).hexdigest()
def aliases(source,extra):
    prelude=source[:source.index("structure Acc")]
    groups=re.finditer(r"\bopen\s+([\w.]+)\s+renaming\s+(.+?)(?=\s+open\s+|\s+local\s+notation|\s+local\s+postfix|$)",prelude)
    result={}
    for g in groups:
        for name,alias in re.findall(r"([\w.'?!]+)->([\w'?!]+)",g.group(2)):result[alias]=g.group(1)+"."+name
    result.update(extra);return result
def normalize(body,mapping):
    expr=re.compile(r"(?<![\w.'?!])("+"|".join(re.escape(k) for k in sorted(mapping,key=len,reverse=True))+r")(?![\w.'?!])")
    body=expr.sub(lambda m:mapping[m.group()],body)
    body=body.replace("ExactRuntime.Word","UInt32")
    return re.sub(r"\s+","",body)
if __name__=="__main__":
    recipe=load(HERE/"build_gemm36_pairlinear.py","r28_pairreview_recipe")
    decl=load(HERE/"source_capability_map.py","r28_pairreview_map").declarations
    raw=(ROUND/"competition-state/source-private/official-36.lean").read_bytes()
    donor=(ROUND.parent/"r27-5h-20261029T194443Z/competition-state/source-private/submission27-Kernel.lean").read_bytes()
    result,meta=recipe.build(raw,donor);base=raw.decode();ds=donor.decode();candidate=result.decode()
    bd,dd,cd=decl(base),decl(ds),decl(candidate)
    map36=aliases(base,{"ו":"UInt64","ז":"UInt32"})
    map27=aliases(ds,{"ٳ":"Nat","ٴ":"Int","ؼ":"UInt32","ػ":"UInt64","ؽ":"Array","ف":"Bool"})
    proof_compatible={name:normalize(bd[name]["body"],map36)==normalize(dd[name]["body"],map27) for name in ["Yo","Yq"]}
    assert all(proof_compatible.values()),proof_compatible
    collisions={new:len(re.findall(r"(?<![\w.'?!])"+re.escape(new)+r"(?![\w.'?!])",base)) for new in meta["renamed_declarations"].values()}
    assert not any(collisions.values())
    runtime=cd["R28Ya3Q"]["body"]
    assert "YaVM m k n false" in runtime and "then Ya3 batch m k n A B else" in runtime
    assert "0x80000000" in runtime and "gemmSpec" not in runtime
    assert "R28Zc0Q" in cd["correct"]["body"] and "dense:=⟨YaVM,R28Ya3Q⟩" in cd["kernels"]["body"]
    root_bridge=(ROUND/"development/ci-bridge/runner.py").read_text()
    # Symbol strings are expectations for the generated module, not observed C.
    out={"at_utc":datetime.now(timezone.utc).isoformat(),"reply_to":"requests/172700-native-pairlinear-queued.md",
         "candidate_sha256":sha(result),"candidate_bytes":len(result),"recipe_sha256":sha((HERE/"build_gemm36_pairlinear.py").read_bytes()),
         "actual_proof_shared_definitions_normalized_equal":proof_compatible,"fresh_name_existing_source_occurrences":collisions,
         "binding":"Submission.kernels.dense.2=R28Ya3Q; correct simp R28Zc0Q; fallback Ya3; fast call YaVM (native MD2) with negative-zero bias",
         "runtime_symbols_expected":["competition.Submission.R28Ya3Q","competition.Submission.YaVM","competition.Submission.MD2","competition.Submission.Ya3","competition.Submission.YbcN","competition.Submission.Ybf"],
         "native_symbol_observation":"UNKNOWN until exact compiled C/native binary; Lean4.34 generated prefix lp_competition_Submission_ from R27 evidence, do not use old l_Submission_ hardcode",
         "alias_resolution":"All copied donor open-renaming aliases explicitly qualified, local type notations expanded, Array.ofFn prefix and size postfix rewritten. Shared Yo/Yq normalized exact definitions equal. Other new names prefixed R28 and absent in base.",
         "gate_boundary":"No local compile. Exact full statement/kernel/axioms gate remains required. This is source review, not independent formal verification.",
         "next":"Root can keep queued candidate unchanged; read exact gate goals if any. Freshsource edits require distinct recipe/hash."}
    (HERE/"PAIRLINEAR36-ROOT-REQUEST-REVIEW.json").write_text(json.dumps(out,indent=2,ensure_ascii=False)+"\n",encoding="utf-8")
    print(json.dumps({k:out[k] for k in ["candidate_sha256","candidate_bytes","actual_proof_shared_definitions_normalized_equal"]}))
