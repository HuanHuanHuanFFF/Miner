"""Build DeepSeek dispatch candidates from the retained df5c kernel.

Each candidate changes only a dispatch predicate, so every branch keeps its
existing full-shape correctness theorem. The script refuses to run unless each
replacement matches exactly once and the result stays under the byte cap.
"""
import hashlib
import json
from pathlib import Path

TRACK = Path(r"D:\CodingProject\Bitget-DeepSeek\competitions\floatlib")
PARENT = TRACK / "candidates/f01-d12-scalar-combined/Kernel.lean"
PARENT_SHA = hashlib.sha256(PARENT.read_bytes()).hexdigest()
assert PARENT_SHA == "df5c61a0ca24a8ef18c0c42d83bdd23466872d3fe8f39dd912e9c347b27fb172", PARENT_SHA
SRC = PARENT.read_text(encoding="utf-8")

P8_OLD = "  if n ≤ 4 ∨ p ≤ 2 then DirectSmall.core batch m n p A B"
P8_NEW = "  if n ≤ 4 ∨ p ≤ 8 then DirectSmall.core batch m n p A B"
P2_OLD = "  if h : p=2 ∧ 4≤batch*m ∧ 0<n ∧ n<USize.size ∧"
P2_NEW = "  if h : p=2 ∧ batch*m < 4 ∧ 0<n ∧ n<USize.size ∧"

SPECS = [
    {
        "name": "f01-deepseek-p2-direct",
        "edits": [(P2_OLD, P2_NEW)],
        "mechanism": (
            "Only the p=2 Cross guard changes: `4≤batch*m` becomes `batch*m < 4`, so p=2 "
            "shapes with batch*m>=4 fall through to the proven DirectSmall scalar-dot core "
            "instead of R11CrossRows. No other runtime bytes change."),
        "hypothesis": (
            "R11CrossRows packs four rows and two columns (8 outputs) through the p=2 Cross "
            "machinery; direct scalar dots may avoid its fixed packing/output overhead at the "
            "cost of reading A twice per row. Public-v2 dense, sparse and extremes groups hold "
            "most p=2 scored work."),
    },
    {
        "name": "f01-deepseek-p2p8",
        "edits": [(P2_OLD, P2_NEW), (P8_OLD, P8_NEW)],
        "mechanism": (
            "Combines the p=2 Cross guard change (`batch*m < 4`) with the bmmBeforeDirectRows "
            "predicate change (`n ≤ 4 ∨ p ≤ 8`). Both edits only choose between branches whose "
            "unconditional correctness theorems already exist."),
        "hypothesis": (
            "Tests whether the two direct-routing changes compose: p=2 work plus 3<=p<=8 work "
            "leave the packed/Cross paths."),
    },
]


def build(spec):
    text = SRC
    for old, new in spec["edits"]:
        assert text.count(old) == 1, (spec["name"], old, text.count(old))
        text = text.replace(old, new)
    data = text.encode("utf-8")
    assert len(data) <= 256000, len(data)
    digest = hashlib.sha256(data).hexdigest()
    out = TRACK / "candidates" / spec["name"]
    out.mkdir(parents=True, exist_ok=True)
    (out / "Kernel.lean").write_bytes(data)
    edits = [{"old": o, "new": n, "occurrences": 1} for o, n in spec["edits"]]
    manifest = {
        "candidate": spec["name"],
        "candidate_file": "Kernel.lean",
        "candidate_sha256": digest,
        "candidate_bytes": len(data),
        "parent": "competitions/floatlib/candidates/f01-d12-scalar-combined/Kernel.lean",
        "parent_sha256": PARENT_SHA,
        "at_utc": "2026-10-24T19:30:00Z",
        "author_role": "deepseek free research/development agent",
        "mechanism": spec["mechanism"],
        "hypothesis": spec["hypothesis"],
        "proof": (
            "No new proof obligation: each edited `if` keeps both branches and their existing "
            "spec theorems; only the decidable predicate changes."),
        "validation_mode": "full-gate",
        "compile_status": "STATIC_DIFF_ONLY",
        "full_gate_status": "NOT_RUN",
        "benchmark": "NOT_RUN",
        "formal_submission": "NOT_SUBMITTED",
        "edits": edits,
    }
    (out / "manifest.json").write_text(json.dumps(manifest, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    (out / "README.md").write_text(
        f"# {spec['name']}\n\n{spec['mechanism']}\n\n## 假设\n\n{spec['hypothesis']}\n\n"
        f"## 证明\n\n分支条件改动，两支都有全形状定理；无新增证明义务。\n\n"
        f"## 验收\n\n本地仅静态 diff；完整 gate、公共套件与性能 NOT_RUN。\n",
        encoding="utf-8",
    )
    print(spec["name"], len(data), digest)


for s in SPECS:
    build(s)
