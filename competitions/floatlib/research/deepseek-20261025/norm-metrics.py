"""Compute raw and reference-normalized A/B metrics for one public-v2 run.

normalized = (sub_score/inc_score)_cand / (sub_score/inc_score)_baseline
raw        = sub_score_cand / sub_score_baseline
score      = sum over classes of cell_work * ns
"""
import json
import sys
from pathlib import Path

run = Path(sys.argv[1])
cand = sys.argv[2]
base = sys.argv[3] if len(sys.argv) > 3 else "f01-r15-dev-packed-b2-1"
suite = next(p for p in run.rglob("public-suite") if (p / "public-cell-work.json").exists())
work = json.loads((suite / "public-cell-work.json").read_text(encoding="utf-8"))


def verdict(name):
    return json.loads((suite / f"{name}-verdict.json").read_text(encoding="utf-8"))


a, b = verdict(base), verdict(cand)


def score(v, classes):
    return sum(work[c] * v["classes"][c]["submission_ns"] for c in classes)


def score_inc(v, classes):
    return sum(work[c] * v["classes"][c]["incumbent_ns"] for c in classes)


classes = list(work)
print(f"{run.name} {cand} vs {base}")
for op in ("add", "mul", "sum", "bmm"):
    cls = [c for c in classes if c.startswith(op + ":")]
    norm = (score(b, cls) / score_inc(b, cls)) / (score(a, cls) / score_inc(a, cls))
    raw = score(b, cls) / score(a, cls)
    print(f"  {op:4s} norm={norm:.6f} raw={raw:.6f}")
norm = (score(b, classes) / score_inc(b, classes)) / (score(a, classes) / score_inc(a, classes))
raw = score(b, classes) / score(a, classes)
print(f"  whole norm={norm:.6f} raw={raw:.6f}")
