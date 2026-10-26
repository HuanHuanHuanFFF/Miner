"""Mark the per-output NativeFinal.dot (and the p<=2 cache dot) inline (attribute-only)."""
import datetime
import hashlib
import json
from pathlib import Path

TRACK = Path(r"D:\CodingProject\Bitget-DeepSeek\competitions\floatlib")
PARENT = TRACK / "candidates/f01-r15-dev-packed-b2-1/Kernel.lean"
SRC = PARENT.read_text(encoding="utf-8")

OLD1 = "def dot (n baseA baseB p : Nat) (A B : Array Binary32) : Binary32 :=\n"
NEW1 = "@[inline] def dot (n baseA baseB p : Nat) (A B : Array Binary32) : Binary32 :=\n"
OLD2 = "def dot (n baseA baseB p : Nat) (Araw Braw : Array Binary32)\n    (preparedB : Array Float32) : Binary32 :=\n"
NEW2 = "@[inline] def dot (n baseA baseB p : Nat) (Araw Braw : Array Binary32)\n    (preparedB : Array Float32) : Binary32 :=\n"
for old in (OLD1, OLD2):
    assert SRC.count(old) == 1, (old, SRC.count(old))
text = SRC.replace(OLD1, NEW1).replace(OLD2, NEW2)
data = text.encode("utf-8")
sha = hashlib.sha256(data).hexdigest()
out = TRACK / "candidates/f01-deepseek-inline-dot"
out.mkdir(parents=True, exist_ok=True)
(out / "Kernel.lean").write_bytes(data)
manifest = {
    "candidate": "f01-deepseek-inline-dot",
    "candidate_file": "Kernel.lean",
    "candidate_sha256": sha,
    "candidate_bytes": len(data),
    "created_at_utc": datetime.datetime.now(datetime.timezone.utc).isoformat(),
    "parent": "competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean",
    "parent_sha256": "622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58",
    "mechanism": "Attribute-only change: mark NativeFinal.dot and R14ThinBCache.dot @[inline], so per-output dot calls can be inlined into the row writers. Semantics, arithmetic and order unchanged.",
    "proof": "Attributes do not change statements or proofs.",
    "validation_mode": "full-gate",
    "proof_status": "NOT_RUN_ATTRIBUTE_ONLY",
    "performance": "NOT_RUN",
    "hypothesis": "Per-output call overhead is visible; inlining shrinks it without depending on CPU denormal behavior.",
    "formal_submission": "NOT_SUBMITTED",
}
(out / "manifest.json").write_text(json.dumps(manifest, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
(out / "manifest.json").write_bytes((out / "manifest.json").read_bytes().replace(b"\r\n", b"\n"))
print("inline-dot", sha, len(data))
