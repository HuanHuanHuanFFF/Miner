"""Copy the peer candidate exact bytes for independent replication (verification only)."""
import hashlib
import json
from pathlib import Path

SRC = Path(r"D:\CodingProject\Bitget\competitions\floatlib\candidates\f01-r19-dev-temporal-b2-1\Kernel.lean")
EXPECT = "c70cf9479ca48b4690990ebbd0b3781139cbeb94e46b28bbe61563e3eeaced1c"
data = SRC.read_bytes()
sha = hashlib.sha256(data).hexdigest()
assert sha == EXPECT, sha
TRACK = Path(r"D:\CodingProject\Bitget-DeepSeek\competitions\floatlib")
out = TRACK / "candidates/f01-deepseek-peercheck-temporal-b2-1"
out.mkdir(parents=True, exist_ok=True)
(out / "Kernel.lean").write_bytes(data)
manifest = {
    "candidate": "f01-deepseek-peercheck-temporal-b2-1",
    "candidate_file": "Kernel.lean",
    "candidate_sha256": sha,
    "candidate_bytes": len(data),
    "parent": "peer:f01-r19-dev-temporal-b2-1 (Codex worktree, byte-identical copy)",
    "parent_sha256": sha,
    "mechanism": "Independent replication copy of the peer temporal B2 candidate (one native8 record per 4 k positions, two original ordered chains, exact tail and raw replay). No bytes changed.",
    "proof": "Peer full gate PASS on their run 40398675395; this copy exists only to re-measure on DeepSeek seeds/runner CPUs.",
    "validation_mode": "full-gate",
    "proof_status": "PEER_FULL_GATE_PASS_COPIED_BYTES",
    "performance": "PEER_FIRST_DISCOVERY 0.9902051201132431 / p05 +0.007790588198369641 (seed 1927003)",
    "usage": "VERIFICATION_ONLY_NO_ADOPTION",
    "formal_submission": "NOT_SUBMITTED",
}
(out / "manifest.json").write_text(json.dumps(manifest, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
(out / "manifest.json").write_bytes((out / "manifest.json").read_bytes().replace(b"\r\n", b"\n"))
print("peer copy", sha, len(data))
