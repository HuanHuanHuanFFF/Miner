"""Cost breakdown for one public-v2 candidate run."""
import json
import sys
from pathlib import Path

suite = Path(sys.argv[1])
name = sys.argv[2]
work = json.loads((suite / "public-cell-work.json").read_text(encoding="utf-8"))
v = json.loads((suite / f"{name}-verdict.json").read_text(encoding="utf-8"))
print("seed", v["seed"], "ratio", v["ratio"], "passed", v["passed"])
tot = {}
for cell, row in v["classes"].items():
    op = cell.split(":")[0]
    t = row["submission_ns"] * work[cell]
    tot[op] = tot.get(op, 0) + t
    print(f"{cell:20s} {t/1e6:8.2f} ms  ratio={row['ratio']:.4f}")
whole = sum(tot.values())
print("\nop totals and shares:")
for op in ("add", "mul", "sum", "bmm"):
    print(f"  {op:4s} {tot[op]/1e6:8.2f} ms  {100*tot[op]/whole:5.2f}%")
print(f"  whole {whole/1e6:.2f} ms")
