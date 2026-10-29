"""Generate ContractExact-only checker probes; preserve the original key probe."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json,re
HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/"AGENTS.md").is_file())
old=ROOT/"competitions/floatlib/candidates/f01-d7-research/round7h-20261028T203856Z/development-scalar/PortableF64Dot.lean.inc"
incumbent=ROOT/"competitions/floatlib/candidates/f01-d7-research/round7h-20261028T203856Z/source-snapshot/torchlean/kernels/exact/incumbent/Kernel.lean"
sha=lambda b:hashlib.sha256(b).hexdigest()
key=(HERE/"OrderKey.lean.inc").read_text(encoding="utf-8")
checker=(HERE/"ActualChecker.lean.inc").read_text(encoding="utf-8")
raw=old.read_text(encoding="utf-8")
runtime=raw[raw.index("@[inline] def finite64"):raw.index("/-- Zero is a miss sentinel.")]
runtime="namespace Submission.R24PortableF64\n"+runtime+"\nend Submission.R24PortableF64\n"
identity="""
namespace Submission.R25Checker
theorem finite64_eq_runtime (w : UInt64) :
    R25OrderKey.finite64 w = R24PortableF64.finite64 w := rfl
theorem orderKey_eq_runtime (w : UInt64) :
    R25OrderKey.orderKey w = R24PortableF64.orderKey w := rfl
theorem certify_eq_runtime (s r : Float) (sw : UInt64) (q : UInt32) :
    certify s r sw q = R24PortableF64.certify s r sw q := rfl
theorem actual_acceptance_bounds (s r : Float) (sw : UInt64) (q : UInt32)
    (h : R24PortableF64.certify s r sw q = true) :
    R25OrderKey.value (lowerWord q) < R25OrderKey.nativeValue (s - r) ∧
    R25OrderKey.nativeValue (s + r) < R25OrderKey.value (upperWord q) := by
  apply accepted_native_bounds s r sw q
  simpa only [certify_eq_runtime] using h
end Submission.R25Checker
"""
components=[("ActualRuntime.lean.inc",runtime),("RuntimeIdentity.lean.inc",identity)]
for fn,s in components:
    (HERE/fn).write_text(s,encoding="utf-8",newline="\n")
combined=key+"\n"+checker+"\n"+runtime+"\n"+identity
(HERE/"ActualCheckerContractOnly.lean").write_text("import ContractExact\n"+combined,encoding="utf-8",newline="\n")
carrier=incumbent.read_bytes()+b"\n"+combined.encode()
assert len(carrier)<=256000
assert not re.search(rb"(?m)^\s*(axiom|unsafe)\b",carrier)
for forbidden in (b"sorry",b"admit",b"native_decide",b"bv_decide",b"implemented_by",b"@[extern"):
    assert forbidden not in carrier,forbidden
(HERE/"Kernel.lean").write_bytes(carrier)
extra=["accepted_components","unsigned_bounds","midpoint_finite_nonzero","accepted_native_bounds",
       "finite64_eq_runtime","orderKey_eq_runtime","certify_eq_runtime","actual_acceptance_bounds"]
files=[HERE/x for x in ["ActualChecker.lean.inc","ActualRuntime.lean.inc","RuntimeIdentity.lean.inc",
                       "ActualCheckerContractOnly.lean","Kernel.lean"]]
manifest=dict(at_utc=datetime.now(timezone.utc).isoformat(),status="NOT_RUN",
    imports_allowed=["ContractExact"],proof_status="NOT_RUN",axiom_audit="NOT_RUN",kernel_replay="NOT_RUN",
    formal_submission="NOT_SUBMITTED",CI_owner="Droot",
    source_runtime=dict(path=old.relative_to(ROOT).as_posix(),sha256=sha(old.read_bytes())),
    runtime_extract=dict(first="@[inline] def finite64",last="before Zero is a miss sentinel",
                         copy="Exact bytes of finite64/proposal/orderKey/certify; namespace restored."),
    incumbent_prefix=dict(path=incumbent.relative_to(ROOT).as_posix(),sha256=sha(incumbent.read_bytes()),
                           bytes=incumbent.stat().st_size,byte_identical=True),
    files=[dict(path=p.relative_to(ROOT).as_posix(),bytes=p.stat().st_size,sha256=sha(p.read_bytes())) for p in files],
    explicit_axiom_roots=["Submission.R25Checker."+x for x in extra],
    key_roots="manifest.json explicit_axiom_roots",
    result_scope="Actual old runtime certify=true implies computed native endpoints strictly inside computed raw midpoint words, with actual midpoint finite/nonzero established.",
    remaining="Lean acceptance; link midpoint words to binary32 rounder cell; actual producer enclosure; full optimized Kernel and model performance.",
    tokens="UNKNOWN",cached_input_tokens="UNKNOWN",deadline_utc="2026-10-29T08:19:16Z")
(HERE/"checker-manifest.json").write_text(json.dumps(manifest,indent=2)+"\n",encoding="utf-8")
print(json.dumps(manifest,indent=2))

