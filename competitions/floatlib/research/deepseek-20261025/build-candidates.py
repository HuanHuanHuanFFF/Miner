"""Build DeepSeek dispatch candidates from the retained df5c kernel.

Each candidate changes only a dispatch predicate, so every branch keeps its
existing full-shape correctness theorem. The script refuses to run unless each
replacement matches exactly once and the result stays under the byte cap.
"""
import datetime
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
CONT_OLD = "  if n ≤ 4 ∧ 2 < p then DirectContinuous.core batch m n p A B"
CONT_NEW = "  if (n ≤ 4 ∧ 2 < p) ∨ p ≤ 2 then DirectContinuous.core batch m n p A B"
CONT8_NEW = "  if (n ≤ 4 ∧ 2 < p) ∨ p ≤ 8 then DirectContinuous.core batch m n p A B"
CONT64_NEW = "  if (n ≤ 4 ∧ 2 < p) ∨ p ≤ 64 then DirectContinuous.core batch m n p A B"

SPECS = [
    {
        "name": "f01-deepseek-p8-direct",
        "edits": [(P8_OLD, P8_NEW)],
        "mechanism": (
            "Only the bmmBeforeDirectRows predicate changes from `n ≤ 4 ∨ p ≤ 2` to "
            "`n ≤ 4 ∨ p ≤ 8`; shapes with n>4 and 3<=p<=8 use DirectSmall instead of Packed10. "
            "No other runtime bytes change."),
        "hypothesis": (
            "Packed10 pads every row to 10 lanes, so p=3 wastes about 70% of its lane work; the "
            "direct scalar core may win for short p even though it re-reads A."),
    },
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
    {
        "name": "f01-deepseek-p2cont",
        "edits": [(P2_OLD, P2_NEW), (CONT_OLD, CONT_NEW)],
        "mechanism": (
            "p=2 with batch*m>=4 skips R11CrossRows; DirectContinuous's guard is widened from "
            "`n ≤ 4 ∧ 2 < p` to `(n ≤ 4 ∧ 2 < p) ∨ p ≤ 2`. DirectContinuous.core is proven equal "
            "to the reference for all shapes and writes each row directly with an Array.mkEmpty "
            "output, avoiding per-output decode div/mod."),
        "hypothesis": (
            "For p=2 rows, two direct dots with one shared row base may beat Cross's four-row P12 "
            "packing and its fixed preparation/output machinery."),
    },
    {
        "name": "f01-deepseek-p2cont8",
        "edits": [(P2_OLD, P2_NEW), (CONT_OLD, CONT_NEW), (P8_OLD, P8_NEW)],
        "mechanism": (
            "Combines the p=2 DirectContinuous routing, the widened DirectContinuous guard and the "
            "p ≤ 8 DirectSmall predicate. All three branches retain their unconditional spec "
            "theorems; no new proof obligation is introduced."),
        "hypothesis": (
            "Composite direct-routing candidate: p=2 rows and 3<=p<=8 rows both leave Cross/Packed10."),
    },
    {
        "name": "f01-deepseek-p2contp8",
        "edits": [(P2_OLD, P2_NEW), (CONT_OLD, CONT8_NEW)],
        "mechanism": (
            "p=2 with batch*m>=4 skips R11CrossRows and the DirectContinuous guard is widened to "
            "`(n ≤ 4 ∧ 2 < p) ∨ p ≤ 8`, so both p=2 rows and 3<=p<=8 rows use the direct writer "
            "instead of DirectSmall or Packed10. No other runtime bytes change."),
        "hypothesis": (
            "One direct row writer for all p<=8 avoids both the Cross packing and the DirectSmall "
            "per-output decode; tests whether DirectContinuous generalises better than DirectSmall."),
    },
    {
        "name": "f01-deepseek-directall",
        "edits": [(P2_OLD, P2_NEW), (CONT_OLD, CONT64_NEW)],
        "mechanism": (
            "Extreme routing probe: p=2 leaves Cross and DirectContinuous's guard becomes "
            "`(n ≤ 4 ∧ 2 < p) ∨ p ≤ 64`, so every scored p<=64 shape uses the direct row writer; "
            "only p>64 can still reach DirectSmall/Packed10. No other runtime bytes change."),
        "hypothesis": (
            "Brackets the packed path's value: if direct wins even at p=32/59, the Packed10 "
            "preparation and lane padding are pure overhead on this suite."),
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
        "at_utc": datetime.datetime.now(datetime.timezone.utc).isoformat(),
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
