"""Read-only verification of the exact stage artifacts, except its own receipt."""
from pathlib import Path
from datetime import datetime,timezone
import ast,hashlib,json,re
HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/"AGENTS.md").is_file())
sha=lambda b:hashlib.sha256(b).hexdigest()
m=json.loads((HERE/"v2/manifest.json").read_text(encoding="utf-8"))
checks=[]
for f in m["files"]:
    p=ROOT/f["path"];b=p.read_bytes()
    assert len(b)==f["bytes"] and sha(b)==f["sha256"],f["path"]
    checks.append({"path":f["path"],"sha256":f["sha256"],"bytes":len(b)})
inc=ROOT/"competitions/floatlib/candidates/f01-d7-research/round7h-20261028T203856Z/source-snapshot/torchlean/kernels/exact/incumbent/Kernel.lean"
b=inc.read_bytes();k=(HERE/"v2/Kernel.lean").read_bytes()
assert k[:len(b)]==b
assert len(k)<=256000
assert re.findall(rb"(?m)^import (.*)$",k)==[b"ContractExact"]
for forbidden in (b"sorry",b"admit",b"native_decide",b"bv_decide",b"implemented_by",b"@[extern"):
    assert forbidden not in k,forbidden
assert not re.search(rb"(?m)^\s*(axiom|unsafe)\b",k)
old=ROOT/"competitions/floatlib/candidates/f01-d7-research/round7h-20261028T203856Z/development-scalar/PortableF64Dot.lean.inc"
raw=old.read_text(encoding="utf-8")
body=raw[raw.index("@[inline] def finite64"):raw.index("/-- Zero is a miss sentinel.")]
expect="namespace Submission.R24PortableF64\n"+body+"\nend Submission.R24PortableF64\n"
assert (HERE/"ActualRuntime.lean.inc").read_text(encoding="utf-8")==expect
sr=json.loads((HERE/"source-receipt.json").read_text(encoding="utf-8"))
for s in sr["sources"]:
    raw=(HERE/"sources"/s["file"]).read_bytes()
    h=hashlib.sha1(b"blob "+str(len(raw)).encode()+b"\0"+raw).hexdigest()
    assert h==s["git_blob_sha1"] and sha(raw)==s["sha256"]
builders=sorted(HERE.glob("*.py"))
for p in builders:ast.parse(p.read_text(encoding="utf-8"),filename=str(p))
small=json.loads((HERE/"small-model.json").read_text())
boundary=json.loads((HERE/"checker-boundaries.json").read_text())
assert small["small"]["equal_value_key_strict_pairs"]==[[64,0]]
assert small["binary64"]["equal_value_key_strict_pairs"]==[[1<<63,0]]
assert boundary["cases"]==2540
assert boundary["v2_actual_checker_sha256"]==sha((HERE/"v2/ActualChecker.lean.inc").read_bytes())
receipt=dict(verified_at_utc=datetime.now(timezone.utc).isoformat(),
    stage_first_tool_utc="2026-10-29T06:52:57Z",shared_deadline_utc="2026-10-29T08:19:16Z",
    static_status="PASS",Lean="NOT_RUN",gate="NOT_RUN",replay="NOT_RUN",axioms="NOT_RUN",
    official_submission="NOT_SUBMITTED",files=checks,allowed_imports=["ContractExact"],
    prefix_byte_identity=dict(bytes=len(b),sha256=sha(b),match=True),
    runtime_extract_exact=True,fixed_source_blobs_verified=len(sr["sources"]),
    scripts_AST_checked=[p.name for p in builders],axiom_roots=len(m["explicit_axiom_roots"]),
    model_receipts=dict(small_model="small-model.json",midpoint_boundary="checker-boundaries.json",
                        rerun_this_verification=False),
    next_action="Use exact v2 CI diagnostics to repair elaboration; do not infer acceptance from this static receipt.",
    tokens="UNKNOWN",cached_input_tokens="UNKNOWN",model_CPU_seconds="UNKNOWN")
(HERE/"stage-verification.json").write_text(json.dumps(receipt,indent=2)+"\n",encoding="utf-8")
print(json.dumps(receipt,indent=2))

