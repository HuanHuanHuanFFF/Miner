"""Build subnormal and total finite carriers without the complete B2 prefix."""
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
sub_path = R24 / "research/rounding-review/SubnormalWiden-v1.lean.inc"
sub_raw = sub_path.read_bytes()
assert sha(sub_raw) == "62380963f91440fc18649c56e9a7403b88a88ff0fe841fc905ddbaf0d9199782"
sub = sub_raw.decode().replace("\r\n", "\n")

def between(source, start, end):
    assert source.count(start) == 1, start
    return source[source.index(start):source.index(end, source.index(start))].rstrip() + "\n"

log_proof = "namespace Submission.FastMul\n\n" + between(base, "theorem log2_shift (", "theorem expField_toNat (") + "\nend Submission.FastMul\n"
count_old = "  rw [UInt64.toNat_sub_of_le _ _ hle, lead_nat]\n  rfl\n"
assert sub.count(count_old) == 1
sub = sub.replace(count_old, "  simpa only [lead_nat] using UInt64.toNat_sub_of_le (52 : UInt64) (lead u) hle\n")
native_old = between(sub, "private theorem native_ofBits_decode", "private theorem shift_value")
native_new = """private theorem native_ofBits_decode (w : UInt64) {d : FloatLib.Numerics.Dyadic}
    (hd : Model.toDyadic? (raw w) = some d) : native (Float.ofBits w) = raw w := by
  exact Submission.R24RepresentationWiden.native_ofBits_of_decode w hd
"""
sub = sub.replace(native_old, native_new)
shift_old = between(sub, "private theorem shift_value", "/-- The existing cost-body widening")
shift_new = (HERE / "ShiftGeneral.lean.inc").read_text().rstrip() + "\n"
sub = sub.replace(shift_old, shift_new)
sub = sub.replace("/- R24: the existing R24PortableF64.widenBits nonzero-subnormal branch only.",
    "/- R25 minimal carrier of the existing R24PortableF64.widenBits nonzero-subnormal branch.")
bridge = (HERE / "FiniteWidenBridge.lean.inc").read_bytes()
actual_receipt = json.loads((WIDEN / "actual-bridge/actual-bridge-receipt.json").read_text())
for record in actual_receipt["outputs"]:
    assert sha((WIDEN / "actual-bridge" / record["path"]).read_bytes()) == record["sha256"]
tail = b"\n" + log_proof.encode() + b"\n" + sub.encode() + b"\n" + bridge
carrier = (WIDEN / "actual-bridge/ActualWidenCarrier.lean").read_bytes() + tail
kernel = (WIDEN / "actual-bridge/Kernel.lean").read_bytes() + tail
outputs = {"FastLog2Proof.lean.inc": log_proof.encode(), "SubnormalWiden2.lean.inc": sub.encode(), "FiniteWidenCarrier.lean": carrier, "Kernel.lean": kernel}
for name, blob in outputs.items():
    assert len(blob) < 256000
    for token in (b"sorry", b"axiom ", b"unsafe ", b"implemented_by", b"@[extern", b"native_decide"):
        assert token not in blob, (name, token)
    (HERE / name).write_bytes(blob)
roots = ["Submission.FastMul.fastLog2_eq", "Submission.R24SubnormalWiden.subnormal_finite_value", "Submission.R25FiniteWiden.subnormal_actual_value", "Submission.R25FiniteWiden.finite_domain_split", "Submission.R25FiniteWiden.finite_actual_value"]
result = {
    "created_at_utc": datetime.now(timezone.utc).isoformat(), "proof_status": "NOT_RUN", "status": "STATIC_SOURCE_CHECKS_PASS_LEAN_NOT_RUN",
    "new_roots": roots, "inherited_roots": actual_receipt["inherited_roots"] + actual_receipt["new_roots"],
    "scope": "Actual widening on every finite binary32 input; no new runtime definitions or changes beyond the exact extracted sx/sr/fastLog2/widenBits",
    "source_subnormal_sha256": sha(sub_raw), "source_subnormal_path": sub_path.relative_to(ROOT).as_posix(),
    "changes": ["count_nat uses a single simpa to avoid potential no-goals rfl", "native_ofBits_decode reuses minimal W7 support theorem", "shift_value uses W7-style explicit sign/cast/zpow proof; avoids old shift-helper whnf timeout route"],
    "log2_helper_theorems": re.findall(r"(?m)^theorem ([A-Za-z0-9_]+)", log_proof),
    "outputs": [{"path": name, "bytes": len(blob), "sha256": sha(blob)} for name, blob in outputs.items()],
    "limits": "Nonzero subnormal branch never compiled in R24; no previous PASS inferred. Need exact fixed-source statement/replay/axiom checks. No prepare/getter/Tail/checker/fallback proof or timing claim.",
}
(HERE / "finite-bridge-receipt.json").write_text(json.dumps(result, indent=2) + "\n")
print(json.dumps({"status": result["status"], "outputs": result["outputs"], "new_roots": roots}))
