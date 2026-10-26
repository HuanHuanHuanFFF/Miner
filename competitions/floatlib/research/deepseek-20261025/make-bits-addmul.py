"""Replace the table-decode convert with Float32.ofBits in add/nativeMul (proof adaption).

The two proofs drop the convert_eq rewrites; the existing `change ... toFloat32 ...`
lines should still close because toFloat32 is definitionally ofBits on raw bits.
"""
import datetime
import hashlib
import json
from pathlib import Path

TRACK = Path(r"D:\CodingProject\Bitget-DeepSeek\competitions\floatlib")
PARENT = TRACK / "candidates/f01-r15-dev-packed-b2-1/Kernel.lean"
SRC = PARENT.read_text(encoding="utf-8")

REPL = [
    ("  let result := R2W01b.convert x.raw.1 + R2W01b.convert y.raw.1",
     "  let result := Float32.ofBits x.raw.1 + Float32.ofBits y.raw.1"),
    ("  let result := R2W01b.convert x.raw.1 * R2W01b.convert y.raw.1",
     "  let result := Float32.ofBits x.raw.1 * Float32.ofBits y.raw.1"),
]
for old, new in REPL:
    assert SRC.count(old) == 1, (old, SRC.count(old))
text = SRC
for old, new in REPL:
    text = text.replace(old, new)

RW = "    rw [R2W01c.convert_eq, R2W01c.convert_eq] at hn ⊢\n"
assert text.count(RW) == 2, text.count(RW)
text = text.replace(RW, "")

data = text.encode("utf-8")
sha = hashlib.sha256(data).hexdigest()
out = TRACK / "candidates/f01-deepseek-bits-addmul"
out.mkdir(parents=True, exist_ok=True)
(out / "Kernel.lean").write_bytes(data)
manifest = {
    "candidate": "f01-deepseek-bits-addmul",
    "candidate_file": "Kernel.lean",
    "candidate_sha256": sha,
    "candidate_bytes": len(data),
    "created_at_utc": datetime.datetime.now(datetime.timezone.utc).isoformat(),
    "parent": "competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean",
    "parent_sha256": "622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58",
    "mechanism": "In scalar add and nativeMul only, replace R2W01b.convert (fastOK table decode) with Float32.ofBits on the raw bits. convert_eq proves they are equal for all UInt32, so this is semantics-preserving; the two proofs drop the now-inapplicable convert_eq rewrites.",
    "proof": "convert_eq : convert u = Float32.ofBits u; the remaining `change` steps identify ofBits x.raw.1 with ExecFloat.Binary.toFloat32 x.",
    "validation_mode": "statement-only",
    "proof_status": "STATIC_PATCH_NOT_COMPILED",
    "performance": "NOT_RUN",
    "hypothesis": "Whether the ofBits bitcast call is cheaper than the table-product decode on the current toolchain; affects add and mul, the largest whole-entry shares.",
    "formal_submission": "NOT_SUBMITTED",
}
(out / "manifest.json").write_text(json.dumps(manifest, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
(out / "manifest.json").write_bytes((out / "manifest.json").read_bytes().replace(b"\r\n", b"\n"))
print("bits-addmul", sha, len(data))
