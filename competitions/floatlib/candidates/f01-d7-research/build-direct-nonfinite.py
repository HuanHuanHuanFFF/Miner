"""Compose two feedback-backed mechanisms; performance/complete gate stay unknown."""
from datetime import datetime, timezone
import hashlib
import json
from pathlib import Path
import re

HERE = Path(__file__).resolve().parent
CANDIDATES = HERE.parent
parent = CANDIDATES / "f01-r7-nonfinite-combined-proof2"
layout = CANDIDATES / "f01-d7-direct-nonnan"
raw = (parent / "Kernel.lean").read_bytes()
layout_raw = (layout / "Kernel.lean").read_bytes()
assert hashlib.sha256(raw).hexdigest() == "0e8bc05ce954e3e8213fbef05ac6041f8f882673c88c1071a3c9d4254a3064cd"
assert hashlib.sha256(layout_raw).hexdigest() == "60f74aa4af01a9b35ece66a7c310e6b05b5b84b9b7121a4cccd12a0a9c987e15"
text = raw.decode()
start = text.rindex("\ndef bmm (batch m n p : Nat)")
old_tail = text[start:]
assert old_tail.count("theorem bmm_spec") == 1
assert old_tail.rstrip().endswith("end Submission")
assert text[:start].count("\ndef bmm (") == 0
renamed_tail = re.sub(r"\bbmm\b", "bmmPackedBase", old_tail)
renamed_tail = renamed_tail.replace("bmm_spec", "bmmPackedBase_spec")
assert renamed_tail.count("bmmPackedBase") == 5
layout_text = layout_raw.decode()
addition = layout_text[layout_text.index("namespace Submission.DirectSmall\n"):]
assert addition.count("def bmm (") == 1
assert addition.count("NativeFinal.dot_eq") == 1
data = (text[:start] + renamed_tail + "\n\n" + addition).encode()
assert data.startswith(text[:start].encode())
assert data.endswith(addition.encode())
assert len(data) < 256000
out = CANDIDATES / "f01-d7-direct-nonfinite"
out.mkdir(exist_ok=True)
(out / "Kernel.lean").write_bytes(data)
manifest = {
    "candidate": out.name, "candidate_file": "Kernel.lean",
    "candidate_sha256": hashlib.sha256(data).hexdigest(), "candidate_bytes": len(data),
    "created_at_utc": datetime.now(timezone.utc).isoformat(),
    "parent": parent.name, "parent_sha256": hashlib.sha256(raw).hexdigest(),
    "layout_parent": layout.name, "layout_parent_sha256": hashlib.sha256(layout_raw).hexdigest(),
    "validation_mode": "statement-only", "proof_status": "NOT_RUN_NEW_COMPOSITION",
    "mechanism": "Apply the exact accepted n<=4 or p<=2 direct shape route to the repaired nonNaN endpoint plus quiet-NaN replay parent. The parent algorithm/proofs remain unchanged except renaming the final packed dispatcher. DirectSmall implementation/proof and exported dispatcher/proof are copied byte-for-byte from retained60f.",
    "component_feedback": "Direct layout and nonNaN endpoint combination60f full807+frozen809 PASS; quiet-NaN replay9a full806+808 PASS. Exact0e8 combined proof has supplied fixed Lean/four original specs/axiom PASS, but original complete gate and all composition timing remain NOT_RUN.",
    "copied_layout_suffix_sha256": hashlib.sha256(addition.encode()).hexdigest(),
    "gain": "UNKNOWN; direct layout and NaN replay target overlapping BMM costs. Measure this exact composition against retained60f; never multiply standalone speedups.",
    "formal_submission": "NOT_SUBMITTED",
}
(out / "manifest.json").write_text(json.dumps(manifest, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
print(json.dumps({"candidate": out.name, "sha256": manifest["candidate_sha256"], "bytes": len(data)}))
