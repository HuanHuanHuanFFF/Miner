"""Build mul low-scale-threshold variants (constant change only, no proof change)."""
import datetime
import hashlib
import json
from pathlib import Path

TRACK = Path(r"D:\CodingProject\Bitget-DeepSeek\competitions\floatlib")
PARENT = TRACK / "candidates/f01-r15-dev-packed-b2-1/Kernel.lean"
SRC = PARENT.read_text(encoding="utf-8")
PARENT_SHA = hashlib.sha256(PARENT.read_bytes()).hexdigest()

OLD = "  if ex + ey < (128 : UInt32) then LowScale.mul x y else nativeMul x y"
assert SRC.count(OLD) == 1, SRC.count(OLD)
SPECS = [("f01-deepseek-multh0", 0, "always nativeMul; LowScale unreachable for scored inputs"),
         ("f01-deepseek-multh64", 64, "only products with ex+ey<64 use the software low-scale rounder"),
         ("f01-deepseek-multh112", 112, "only products with ex+ey<112 use the software low-scale rounder")]
for name, th, mech in SPECS:
    new = f"  if ex + ey < ({th} : UInt32) then LowScale.mul x y else nativeMul x y"
    text = SRC.replace(OLD, new)
    data = text.encode("utf-8")
    sha = hashlib.sha256(data).hexdigest()
    out = TRACK / "candidates" / name
    out.mkdir(parents=True, exist_ok=True)
    (out / "Kernel.lean").write_bytes(data)
    manifest = {
        "candidate": name,
        "candidate_file": "Kernel.lean",
        "candidate_sha256": sha,
        "candidate_bytes": len(data),
        "created_at_utc": datetime.datetime.now(datetime.timezone.utc).isoformat(),
        "parent": "competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean",
        "parent_sha256": PARENT_SHA,
        "mechanism": f"Only the mul low-scale dispatch constant changes 128 -> {th}: {mech}. Both branches keep their proofs; no other runtime byte changes.",
        "proof": "mul_spec splits on the same predicate; LowScale.mul_spec and nativeMul_spec are unconditional.",
        "validation_mode": "full-gate",
        "proof_status": "NOT_RUN_STATIC_CONSTANT_ONLY",
        "performance": "NOT_RUN",
        "hypothesis": "Whether the software low-scale rounder still pays off on the current runner CPU, or native denormal handling is cheaper.",
        "formal_submission": "NOT_SUBMITTED",
    }
    (out / "manifest.json").write_text(json.dumps(manifest, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    print(name, sha)
