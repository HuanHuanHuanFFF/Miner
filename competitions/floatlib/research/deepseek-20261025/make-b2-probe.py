"""Create a statement-only probe copy of B2 to capture generated C for static analysis."""
import hashlib
import json
from pathlib import Path

TRACK = Path(r"D:\CodingProject\Bitget-DeepSeek\competitions\floatlib")
src = TRACK / "candidates/f01-r15-dev-packed-b2-1/Kernel.lean"
data = src.read_bytes()
digest = hashlib.sha256(data).hexdigest()
assert digest == "622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58"
out = TRACK / "candidates/f01-deepseek-b2-probe"
out.mkdir(parents=True, exist_ok=True)
(out / "Kernel.lean").write_bytes(data)
manifest = {
    "candidate": "f01-deepseek-b2-probe",
    "candidate_file": "Kernel.lean",
    "candidate_sha256": digest,
    "candidate_bytes": len(data),
    "parent": "competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean",
    "parent_sha256": digest,
    "validation_mode": "statement-only",
    "mechanism": "Byte-identical B2 source; statement-only copy used solely to capture the generated C/asm for static hot-loop analysis.",
    "performance": "NOT_MEASURED_BY_DESIGN",
    "scope": "Diagnostic only; no gate, no performance claim, no adoption.",
}
(out / "manifest.json").write_text(json.dumps(manifest, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
print("probe written", digest, len(data))
