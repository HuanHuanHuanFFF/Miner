"""Correct the confirmed comment-only policy failure; preserve v2 exactly."""
from pathlib import Path
from datetime import datetime,timezone
import ast,hashlib,json,re
HERE=Path(__file__).resolve().parent
ROUND=HERE.parents[1]
OUT=HERE/"policy1"
OUT.mkdir(exist_ok=True)
SOURCE=ROUND/"development/contract-port/policy-source"
expected={
 "sandbox.py":("13c4f7b71e678a27d024613e5198e0d75667de4e","ba8e1a0f23692928f080ad278c35b36493199fb90e3768f90710b85ffef84126"),
 "duplicates.py":("3e8eb21d1a50cce44090e29a816e3b55c0ad3fd9","e1859b11011797b5012795d067383ef619a291769ea40dd0cd017791f127f4f8")}
sha=lambda b:hashlib.sha256(b).hexdigest()
blob=lambda b:hashlib.sha1(b"blob "+str(len(b)).encode()+b"\0"+b).hexdigest()
sources={}
for name,(g,h) in expected.items():
    raw=(SOURCE/name).read_bytes()
    assert sha(raw)==h and blob(raw)==g
    sources[name]=dict(git_blob=g,sha256=h,bytes=len(raw))
old=(HERE/"v2/Kernel.lean").read_bytes()
assert sha(old)=="ba634fe6af6bcf84c07ad248457ac120941da40bc601f893e07f356f0297c967"
before=b"   Append after R25OrderKey; no import, new axiom, or arithmetic-policy change. -/"
after=b"   Append after R25OrderKey; arithmetic behavior is unchanged. -/"
assert old.count(before)==1
new=old.replace(before,after)
(OUT/"Kernel.lean").write_bytes(new)
dups={}
exec(compile((SOURCE/"duplicates.py").read_text(encoding="utf-8"),"pinned-duplicates.py","exec"),dups)
assert dups["normalized"](old.decode())==dups["normalized"](new.decode())
tree=ast.parse((SOURCE/"sandbox.py").read_text(encoding="utf-8"))
names={"_MAX_BYTES","OPTIONS","ATTRIBUTES","BANNED","GLOBAL"}
funcs={"intake","policy","global_declarations","options"}
selected=[n for n in tree.body if
 (isinstance(n,ast.Assign) and any(isinstance(t,ast.Name) and t.id in names for t in n.targets))
 or (isinstance(n,ast.FunctionDef) and n.name in funcs)]
ns={"Path":Path,"Verdict":object,"re":re,"normalized":dups["normalized"]}
exec(compile(ast.Module(body=selected,type_ignores=[]),"pinned-policy-functions.py","exec"),ns)
rows=[]
for label,path in [("frozen-v2",HERE/"v2/Kernel.lean"),("policy1",OUT/"Kernel.lean")]:
    intake=ns["intake"](path,None)
    policy=ns["policy"](path,None) if intake is None else None
    rows.append(dict(variant=label,sha256=sha(path.read_bytes()),bytes=path.stat().st_size,
                     intake=intake,policy=policy,passed=intake is None and policy is None))
assert not rows[0]["passed"] and rows[1]["passed"]
assert "import other than ContractExact" in rows[0]["policy"]
assert (HERE/"v2/Kernel.lean").read_bytes()==old
prior=json.loads((HERE/"v2/manifest.json").read_text(encoding="utf-8"))
receipt=dict(at_utc=datetime.now(timezone.utc).isoformat(),resumed_first_tool_utc="2026-10-29T07:37:24Z",
 deadline_utc="2026-10-29T08:19:16Z",official_commit="accb82b6e2adeda1b41a57a260d68fb3879c427e",
 original_failure_run="40834710293",original_source_commit="823aa68b",
 change="Single confirmed problematic comment line replaced; all executable and proof text unchanged.",
 before=before.decode(),after=after.decode(),normalized_code_identical=True,v2_preserved=True,
 sources=sources,results=rows,proof_status="NOT_RUN",kernel_replay="NOT_RUN",axiom_audit="NOT_RUN",
 explicit_axiom_roots=prior["explicit_axiom_roots"],allowed_imports=["ContractExact"],
 local_Lean=False,CI_owner="Droot",formal_submission="NOT_SUBMITTED",
 resource_changes="NONE",mixed_Nat_Int_prediction_changed=False,tokens="UNKNOWN",cached_input_tokens="UNKNOWN")
(OUT/"receipt.json").write_text(json.dumps(receipt,indent=2)+"\n",encoding="utf-8")
print(json.dumps(receipt,indent=2))

