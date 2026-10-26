"""Mark Packed10.finish inline (attribute-only)."""
import datetime
import hashlib
import json
from pathlib import Path

TRACK = Path(r"D:\CodingProject\Bitget-DeepSeek\competitions\floatlib")
PARENT = TRACK / "candidates/f01-r15-dev-packed-b2-1/Kernel.lean"
SRC = PARENT.read_text(encoding="utf-8")
OLD = "def finish (n baseA baseB p : Nat) (Araw Braw : Array Binary32)"
NEW = "@[inline] def finish (n baseA baseB p : Nat) (Araw Braw : Array Binary32)"
assert SRC.count(OLD) == 1
data = SRC.replace(OLD, NEW).encode("utf-8")
sha = hashlib.sha256(data).hexdigest()
out = TRACK / "candidates/f01-deepseek-inline-finish"
out.mkdir(parents=True, exist_ok=True)
(out / "Kernel.lean").write_bytes(data)
manifest = {
    "candidate": "f01-deepseek-inline-finish",
    "candidate_file": "Kernel.lean",
    "candidate_sha256": sha,
    "candidate_bytes": len(data),
    "created_at_utc": datetime.datetime.now(datetime.timezone.utc).isoformat(),
    "parent": "competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean",
    "parent_sha256": "622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58",
    "mechanism": "Attribute-only: mark Packed10.finish @[inline]. finish is called once per output column in the pair route; inlining removes a per-output call while keeping arithmetic identical.",
    "proof": "Attributes do not change statements or proofs.",
    "validation_mode": "full-gate",
    "proof_status": "NOT_RUN_ATTRIBUTE_ONLY",
    "performance": "NOT_RUN",
    "formal_submission": "NOT_SUBMITTED",
}
(out / "manifest.json").write_text(json.dumps(manifest, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
(out / "manifest.json").write_bytes((out / "manifest.json").read_bytes().replace(b"\r\n", b"\n"))
print("inline-finish", sha, len(data))
