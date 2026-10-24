"""Aggregate public-v2 per-class ratios for DeepSeek candidates across collected runs."""
import json
import sys
from collections import defaultdict
from pathlib import Path

BASE = Path(r"D:\CodingProject\Bitget-DeepSeek\competitions\floatlib\research\deepseek-20261025\ci-runs")
CANDIDATES = sys.argv[1].split(",") if len(sys.argv) > 1 else ["f01-deepseek-p2contp8"]
ANCHOR = "f01-d12-scalar-combined"

acc = {c: defaultdict(list) for c in CANDIDATES}
runs = []
for d in sorted(BASE.iterdir()):
    if not d.is_dir() or not d.name.isdigit():
        continue
    suite = next((p for p in d.rglob("public-suite") if (p / "public-cell-work.json").exists()), None)
    if not suite:
        continue
    work = json.loads((suite / "public-cell-work.json").read_text(encoding="utf-8"))
    try:
        a = json.loads((suite / f"{ANCHOR}-verdict.json").read_text(encoding="utf-8"))
    except FileNotFoundError:
        continue
    for name in CANDIDATES:
        vf = suite / f"{name}-verdict.json"
        if not vf.exists():
            continue
        b = json.loads(vf.read_text(encoding="utf-8"))
        if not (a.get("passed") and b.get("passed")):
            continue
        for cell in a["classes"]:
            ta = a["classes"][cell]["submission_ns"] * work[cell]
            tb = b["classes"][cell]["submission_ns"] * work[cell]
            acc[name][cell].append(tb / ta)
        runs.append((d.name, name))

for name in CANDIDATES:
    print(f"\n== {name} across {len({r for r,n in runs if n==name})} runs")
    print(f"{'cell':20s} {'n':>2s} {'mean':>7s} {'min':>7s} {'max':>7s}  per-run")
    for cell in sorted(acc[name]):
        xs = acc[name][cell]
        print(f"{cell:20s} {len(xs):2d} {sum(xs)/len(xs):7.4f} {min(xs):7.4f} {max(xs):7.4f}  "
              + " ".join(f"{x:.3f}" for x in xs))
print("\nruns:", runs)
