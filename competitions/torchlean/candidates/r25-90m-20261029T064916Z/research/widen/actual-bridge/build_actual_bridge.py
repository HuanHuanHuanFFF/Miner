"""Extract exact runtime fragments and append actual normal/zero proofs."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json
import re

HERE = Path(__file__).resolve().parent
WIDEN = HERE.parent
ROOT = next(p for p in HERE.parents if (p / "AGENTS.md").is_file())
OLD = ROOT / "competitions/floatlib/candidates"
R24 = OLD / "f01-d7-research/round7h-20261028T203856Z"
sha = lambda b: hashlib.sha256(b).hexdigest()
base_raw = (OLD / "f01-r15-dev-packed-b2-1/Kernel.lean").read_bytes()
assert sha(base_raw) == "622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58"
base = base_raw.decode().replace("\r\n", "\n")
runtime_path = R24 / "development-dot-cost/PortableF64Dot-tail-v2.lean.inc"
runtime_raw = runtime_path.read_bytes()
runtime = runtime_raw.decode().replace("\r\n", "\n")

def between(source, start, end):
    assert source.count(start) == 1, start
    return source[source.index(start):source.index(end, source.index(start))].rstrip() + "\n"

fastlog = between(base, "@[inline] def sx (k x : UInt64)", "@[inline] def rse (")
actual_widen = between(runtime, "@[inline] def widenBits (word : UInt32)", "def prepare (")
runtime_fragment = "namespace Submission.FastMul\n\n" + fastlog + "\nend Submission.FastMul\n\n"
runtime_fragment += "namespace Submission.R24PortableF64\n\n" + actual_widen + "\nend Submission.R24PortableF64\n"
proof = (HERE / "ActualWidenBridge.lean.inc").read_bytes()
frozen = WIDEN / "carrier-receipt.json"
receipt = json.loads(frozen.read_text())
for record in receipt["outputs"]:
    assert sha((WIDEN / record["path"]).read_bytes()) == record["sha256"], record["path"]
standalone = (WIDEN / "WidenCarrier.lean").read_bytes() + b"\n" + runtime_fragment.encode() + b"\n" + proof
kernel = (WIDEN / "Kernel.lean").read_bytes() + b"\n" + runtime_fragment.encode() + b"\n" + proof
outputs = {"ActualRuntime.lean.inc": runtime_fragment.encode(), "ActualWidenCarrier.lean": standalone, "Kernel.lean": kernel}
for name, blob in outputs.items():
    assert len(blob) < 256000
    for token in (b"sorry", b"axiom ", b"unsafe ", b"implemented_by", b"@[extern", b"native_decide"):
        assert token not in blob, (name, token)
    (HERE / name).write_bytes(blob)
roots = ["Submission.R25ActualWiden." + name for name in ("actual_sign_eq", "actual_widenBits_eq", "actual_native_model", "actual_native_finite", "actual_native_value", "actual_signed_zero_bits")]
result = {
    "created_at_utc": datetime.now(timezone.utc).isoformat(),
    "status": "STATIC_CHECKS_PASS_LEAN_NOT_RUN",
    "proof_status": "NOT_RUN",
    "scope": "Exact R24PortableF64 widening runtime, normals and signed zeros only",
    "runtime_source": str(runtime_path.relative_to(ROOT)).replace("\\", "/"),
    "runtime_source_sha256": sha(runtime_raw),
    "runtime_widen_fragment_sha256": sha(actual_widen.encode()),
    "fastlog_fragment_sha256": sha(fastlog.encode()),
    "runtime_changes": "NONE; normalized line endings only, extracted exact sx/sr/fastLog2/widenBits definitions",
    "primary_carrier_unchanged": True,
    "new_roots": roots,
    "inherited_roots": receipt["explicit_helper_roots"],
    "outputs": [{"path": name, "bytes": len(blob), "sha256": sha(blob)} for name, blob in outputs.items()],
    "proof_fragment": {"path": "ActualWidenBridge.lean.inc", "bytes": len(proof), "sha256": sha(proof)},
    "unclosed": ["Nonzero subnormal correctness", "prepare/FloatArray getter correspondence", "Tail accumulation", "actual checker/rounder/fallback"],
}
(HERE / "actual-bridge-receipt.json").write_text(json.dumps(result, indent=2) + "\n")
print(json.dumps({"status": result["status"], "outputs": result["outputs"], "new_roots": roots}))
