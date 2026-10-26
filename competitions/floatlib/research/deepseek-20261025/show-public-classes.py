"""Per-class public-v2 A/B between two candidates in a collected nested run."""
import json
import sys
from pathlib import Path

run_dir = Path(sys.argv[1])
a_name, b_name = sys.argv[2], sys.argv[3]
suite = next(p for p in run_dir.rglob("public-suite") if (p / "public-cell-work.json").exists())
work = json.loads((suite / "public-cell-work.json").read_text(encoding="utf-8"))
va = json.loads((suite / (a_name + "-verdict.json")).read_text(encoding="utf-8"))
vb = json.loads((suite / (b_name + "-verdict.json")).read_text(encoding="utf-8"))
print(f"{'cell':20s} {'work':>9s} {a_name[:12]:>12s} {b_name[:12]:>12s} {'time b/a':>9s} {'ns b/a':>8s}")
for cell in sorted(va["classes"]):
    a, b = va["classes"][cell], vb["classes"][cell]
    ta = a["submission_ns"] * work[cell]
    tb = b["submission_ns"] * work[cell]
    print(f"{cell:20s} {work[cell]:9d} {ta/1e6:10.2f}ms {tb/1e6:10.2f}ms {tb/ta:9.4f} {b['submission_ns']/a['submission_ns']:8.4f}")
print("\nop totals")
for op in ("add", "mul", "sum", "bmm"):
    ta = sum(r["submission_ns"] * work[c] for c, r in va["classes"].items() if c.startswith(op + ":"))
    tb = sum(r["submission_ns"] * work[c] for c, r in vb["classes"].items() if c.startswith(op + ":"))
    print(f"{op:5s} {ta/1e6:8.2f}ms -> {tb/1e6:8.2f}ms  {tb/ta:.4f}")
