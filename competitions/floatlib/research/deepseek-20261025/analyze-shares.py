"""Absolute per-class cost shares for the retained df5c candidate on public-v2.

Input: public-suite-results.json (last f01-d12-scalar-combined record).
Output: op:class rows with candidate ns totals and within-operation shares.

Read-only analysis. No Lean, no CI.
"""
import json
from pathlib import Path

ROOT = Path(r"D:\CodingProject\Bitget-DeepSeek\competitions\floatlib")
RESULTS = ROOT / "candidates/f01-d7-research/public-suite-results.json"

d = json.loads(RESULTS.read_text(encoding="utf-8"))
recs = [r for r in d["records"] if r.get("candidate") == "f01-d12-scalar-combined"]
r = recs[-1]
work = r["cell_work"]
print("run", r["run"], "seed", r["seed"], "ratio", r["ratio"])
print("cell_work keys:", len(work))
print("operation_total_ns:", r["operation_total_ns"])

rows = []
for cell, cls in r["classes"].items():
    op = cell.split(":")[0]
    w = work.get(cell)
    if w is None:
        raise SystemExit(f"missing work for {cell}")
    total = cls["submission_ns"] * w
    rows.append((op, cell, total, cls["ratio"], cls["submission_ns"], w, cls["spread_sub"]))

for op in ("add", "mul", "sum", "bmm"):
    sub = [x for x in rows if x[0] == op]
    s = sum(x[2] for x in sub)
    print(f"\n== {op}: total {s/1e6:.2f} ms; reported {r['operation_total_ns'][op]/1e6:.2f} ms; share {r['time_share_percent'][op]:.2f}%")
    for _, cell, total, ratio, ns, w, spread in sorted(sub, key=lambda x: -x[2]):
        print(f"  {cell:18s} {total/1e6:8.2f} ms  {100*total/s:6.2f}%  ratio={ratio:.4f} ns/work={ns:.3f} work={w} spread={spread:.2f}")
