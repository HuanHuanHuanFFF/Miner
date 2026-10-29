"""Verify source identities and original policy; no Lean, Git mutation, or CI."""
from pathlib import Path
from datetime import datetime,timezone
import ast,hashlib,json,re
HERE=Path(__file__).resolve().parent
ROUND=HERE.parents[2]
sha=lambda b:hashlib.sha256(b).hexdigest()
blob=lambda b:hashlib.sha1(b"blob "+str(len(b)).encode()+b"\0"+b).hexdigest()
sources=[
 ("source-private/Values.lean","9662350c91092ee5b18ed93fb10e71858d3f7dd2",
  "https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/accb82b6e2adeda1b41a57a260d68fb3879c427e/lean/contract/ExactToolkit/Values.lean",False),
 ("source-private/Round.lean","b135b1c53167600a53638e9f474e3ef4e7390ab6",
  "https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/accb82b6e2adeda1b41a57a260d68fb3879c427e/lean/contract/ExactToolkit/Round.lean",False),
 ("sources/Narrow-Agreement.lean.raw","f319e0d19a7aa8f421a169c0c4f8bf6d2497722a",
  "https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/ExecFloat/Backends/Word/Narrow/Agreement.lean",True),
 ("sources/Reduction-Proof.lean.raw","c0dbc2f67929605cdace2655b3b5bd76db38c01d",
  "https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Reduction/Proof.lean",True)]
source_rows=[]
for path,g,url,publish in sources:
    b=(HERE/path).read_bytes();assert blob(b)==g,(path,blob(b))
    source_rows.append(dict(path=path,git_blob_sha1=g,bytes=len(b),sha256=sha(b),
                            url=url,public_source_copy=publish,blob_verified=True))
text=(HERE/"ContractWordBridge.lean").read_text(encoding="utf-8")
assert text.startswith("import ContractExact\n")
inc=text.split("\n",1)[1]
(HERE/"ContractWordBridge.lean.inc").write_text(inc,encoding="utf-8",newline="\n")
source=ROUND/"development/contract-port/policy-source"
assert sha((source/"sandbox.py").read_bytes())=="ba8e1a0f23692928f080ad278c35b36493199fb90e3768f90710b85ffef84126"
assert sha((source/"duplicates.py").read_bytes())=="e1859b11011797b5012795d067383ef619a291769ea40dd0cd017791f127f4f8"
dups={}
exec(compile((source/"duplicates.py").read_text(encoding="utf-8"),"pinned-duplicates.py","exec"),dups)
tree=ast.parse((source/"sandbox.py").read_text(encoding="utf-8"))
names={"_MAX_BYTES","OPTIONS","ATTRIBUTES","BANNED","GLOBAL"}
funcs={"intake","policy","global_declarations","options"}
nodes=[n for n in tree.body if (isinstance(n,ast.Assign) and any(isinstance(t,ast.Name) and t.id in names for t in n.targets)) or (isinstance(n,ast.FunctionDef) and n.name in funcs)]
ns={"Path":Path,"Verdict":object,"re":re,"normalized":dups["normalized"]}
exec(compile(ast.Module(body=nodes,type_ignores=[]),"pinned-policy.py","exec"),ns)
p=HERE/"ContractWordBridge.lean"
intake,policy=ns["intake"](p,None),ns["policy"](p,None)
assert intake is None and policy is None,(intake,policy)
roots=re.findall(r"(?m)^theorem ([A-Za-z0-9_]+)",text)
optional=[dict(path=n,bytes=(HERE/n).stat().st_size,sha256=sha((HERE/n).read_bytes()),proof_status="NOT_RUN") for n in ["DotZeroBridge.lean.inc","RationalDenOneBridge.lean.inc"]]
receipt=dict(at_utc=datetime.now(timezone.utc).isoformat(),resumed_first_tool_utc="2026-10-29T07:56:17Z",
    deadline_utc="2026-10-29T08:19:16Z",official_commit="accb82b6e2adeda1b41a57a260d68fb3879c427e",
    FloatLib="0d91825727839f597fd06b22fdd038ea21480f0c",sources=source_rows,
    policy=dict(intake=intake,policy=policy,status="PASS_ORIGINAL_AST_ONLY"),
    files=[dict(path=n,bytes=(HERE/n).stat().st_size,sha256=sha((HERE/n).read_bytes())) for n in ["ContractWordBridge.lean","ContractWordBridge.lean.inc"]],
    explicit_axiom_roots=["Submission.R25ContractWordBridge."+n for n in roots],
    proof_status="NOT_RUN",full_gate="NOT_APPLICABLE_PROBE_ONLY",kernel_replay="NOT_RUN",axiom_audit="NOT_RUN",optional_interfaces=optional,
    new_Kernel=False,local_Lean=False,CI_started=False,existing_policy1_unchanged=sha((HERE.parent/"policy1/Kernel.lean").read_bytes())=="82399ee3da291a1ad82dbb0432bc2c5bd2a4097db9dcc37bdbca111ff4867111",
    nonzero_finish_scope="T != 0 and d.toRat = (T:Rat)*2^e; NB.roundDyadic d=q implies actual finishWord T e negZero=q for any negZero.",
    zero_scope="finishWord 0 e negZero equals NB.roundDyadic of the zero dyadic with sign=negZero; erasing sign through ofIntDyadic 0 e is explicitly unequal when negZero=true.",
    actual_dot_scope="The exact official dotState of the actual n input functions is used. Requires all actual input models finite, semantic finiteDot not .ok 0, and NB rounding of that exact state equals q.",
    remaining="These thin bridges are not compiled. Producer equality to actualDotExact and nonzero semantic condition still need proofs. Prior cell/Native32 internal agreement remains separately unaccepted.",
    tokens="UNKNOWN",cached_input_tokens="UNKNOWN")
(HERE/"receipt.json").write_text(json.dumps(receipt,indent=2)+"\n",encoding="utf-8")
print(json.dumps(receipt,indent=2))

