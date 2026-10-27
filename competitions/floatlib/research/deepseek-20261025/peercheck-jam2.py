"""Copy a peer jam probe (v2) byte-identically and emit a statement-only candidate."""
import hashlib
import json
import sys
from pathlib import Path

src = Path(sys.argv[1])
expect = sys.argv[2] if len(sys.argv) > 2 else None
data = src.read_bytes()
sha = hashlib.sha256(data).hexdigest()
if expect and sha != expect:
    raise SystemExit(f"sha mismatch {sha} != {expect}")
out = Path(r"D:\CodingProject\Bitget-DeepSeek\competitions\floatlib\candidates\f01-deepseek-peercheck-jam-probe2")
out.mkdir(parents=True, exist_ok=True)
(out / "Kernel.lean").write_bytes(data)
manifest = {
    "candidate": "f01-deepseek-peercheck-jam-probe2",
    "candidate_file": "Kernel.lean",
    "candidate_sha256": sha,
    "candidate_bytes": len(data),
    "parent": f"peer:{src.name} (byte-identical repair)",
    "parent_sha256": sha,
    "mechanism": "Independent statement compilation of the peer GRS/Jam proof-probe repair (9 roots; no public arithmetic change).",
    "proof": "Peer state NOT_RUN; this copy only compiles it on the DeepSeek runner/toolchain.",
    "validation_mode": "statement-only",
    "proof_status": "PEER_REPAIR_NOT_RUN_COPIED_BYTES",
    "performance": "NOT_RUN",
    "roots": [
        "Submission.add_spec", "Submission.mul_spec", "Submission.sum_spec", "Submission.bmm_spec",
        "R19JamVariableProbe.quotient_block", "R19JamVariableProbe.low_states",
        "R19JamVariableProbe.quotient_jam_decomposed", "R19JamVariableProbe.quotient_jam",
        "R19JamVariableProbe.rne_jam",
    ],
    "usage": "PEER_MATH_VERIFICATION_ONLY",
}
(out / "manifest.json").write_bytes((json.dumps(manifest, ensure_ascii=False, indent=2) + "\n").encode("utf-8"))
print("probe2", sha, len(data))
