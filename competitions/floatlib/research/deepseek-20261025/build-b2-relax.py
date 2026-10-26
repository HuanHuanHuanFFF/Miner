"""Build B2 dispatch-relaxation candidates (predicate only, no code/proof changes)."""
import datetime
import hashlib
import json
from pathlib import Path

TRACK = Path(r"D:\CodingProject\Bitget-DeepSeek\competitions\floatlib")
PARENT = TRACK / "candidates/f01-r15-dev-packed-b2-1/Kernel.lean"
PARENT_SHA = hashlib.sha256(PARENT.read_bytes()).hexdigest()
assert PARENT_SHA == "622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58", PARENT_SHA
SRC = PARENT.read_text(encoding="utf-8")

OLD = "  if 2 ≤ p ∧ p ≤ 8 ∧ 1 < n ∧ 4 ≤ m then core batch m n p A B"
assert SRC.count(OLD) == 2

SPECS = [
    ("f01-deepseek-b2-m2", "  if 2 ≤ p ∧ p ≤ 8 ∧ 1 < n ∧ 2 ≤ m then core batch m n p A B",
     "Only the B2 dispatch predicate changes: m>=4 -> m>=2. Shapes with m=2,3 and 2<=p<=8,n>1 now use the existing proven B2 pair core instead of DirectContinuous."),
    ("f01-deepseek-b2-m1", "  if 2 ≤ p ∧ p ≤ 8 ∧ 1 < n ∧ 0 < m then core batch m n p A B",
     "Only the B2 dispatch predicate changes: m>=4 -> m>=1. All positive-row shapes with 2<=p<=8,n>1 now use the B2 pair core."),
    ("f01-deepseek-b2-all", "  if 2 ≤ p ∧ p ≤ 8 ∧ 0 < n ∧ 0 < m then core batch m n p A B",
     "Only the B2 dispatch predicate changes: m>=4 and n>1 relaxed to m>=1 and n>=1, so every non-empty 2<=p<=8 shape uses the B2 pair core."),
]

for name, new, mechanism in SPECS:
    text = SRC.replace(OLD, new)
    data = text.encode("utf-8")
    assert len(data) <= 256000, len(data)
    digest = hashlib.sha256(data).hexdigest()
    out = TRACK / "candidates" / name
    out.mkdir(parents=True, exist_ok=True)
    (out / "Kernel.lean").write_bytes(data)
    manifest = {
        "candidate": name,
        "candidate_file": "Kernel.lean",
        "candidate_sha256": digest,
        "candidate_bytes": len(data),
        "created_at_utc": datetime.datetime.now(datetime.timezone.utc).isoformat(),
        "parent": "competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean",
        "parent_sha256": PARENT_SHA,
        "mechanism": mechanism,
        "proof": "No new proof obligation: bmmBeforeUnderflowZero_spec and dispatch_spec still split on the same predicate and apply the same unconditional core_eq_reference. Only the decidable condition changes.",
        "validation_mode": "full-gate",
        "proof_status": "NOT_RUN_STATIC_PREDICATE_ONLY",
        "performance": "NOT_RUN",
        "first_falsifier": "Same-run public-v2 A/B against B2; BMM must improve beyond run noise, and the relaxed shapes must not regress dense/ml materially.",
        "formal_submission": "NOT_SUBMITTED",
    }
    (out / "manifest.json").write_text(json.dumps(manifest, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    (out / "README.md").write_text(
        f"# {name}\n\n{mechanism}\n\n## 证明\n\n仅改分派谓词，两支定理不变；无新增证明义务。\n\n"
        f"## 验收\n\n本地静态 diff；完整 gate 与 public-v2 计时 NOT_RUN。\n", encoding="utf-8")
    print(name, len(data), digest)
