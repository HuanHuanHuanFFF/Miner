"""Narrow B2 pair dispatch by column-count band (predicate-only, no proof change)."""
import datetime
import hashlib
import json
from pathlib import Path

TRACK = Path(r"D:\CodingProject\Bitget-DeepSeek\competitions\floatlib")
PARENT = TRACK / "candidates/f01-r15-dev-packed-b2-1/Kernel.lean"
SRC = PARENT.read_text(encoding="utf-8")
PARENT_SHA = hashlib.sha256(PARENT.read_bytes()).hexdigest()
OLD = "  if 2 ≤ p ∧ p ≤ 8 ∧ 1 < n ∧ 4 ≤ m then core batch m n p A B"
assert SRC.count(OLD) == 2, SRC.count(OLD)
SPECS = [
    ("f01-deepseek-b2-p3", 3),
    ("f01-deepseek-b2-p4", 4),
    ("f01-deepseek-b2-p6", 6),
]
for name, lo in SPECS:
    new = f"  if {lo} ≤ p ∧ p ≤ 8 ∧ 1 < n ∧ 4 ≤ m then core batch m n p A B"
    data = SRC.replace(OLD, new).encode("utf-8")
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
        "mechanism": f"Only the B2 pair dispatch lower bound changes 2 -> {lo}: shapes with p<{lo} and m>=4,n>1 go back to bmmBeforeR11Cross (DirectContinuous) instead of packB+pair groups.",
        "proof": "No new obligation: both dispatch definitions split on the same predicate; core_eq_reference and bmmBeforeR11Cross_spec are unconditional.",
        "validation_mode": "full-gate",
        "proof_status": "NOT_RUN_STATIC_PREDICATE_ONLY",
        "performance": "NOT_RUN",
        "hypothesis": "Pair groups need >=2 groups to amortize packB; p=2..3 may be faster on the direct path.",
        "formal_submission": "NOT_SUBMITTED",
    }
    (out / "manifest.json").write_text(json.dumps(manifest, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    (out / "manifest.json").write_bytes((out / "manifest.json").read_bytes().replace(b"\r\n", b"\n"))
    print(name, sha)
