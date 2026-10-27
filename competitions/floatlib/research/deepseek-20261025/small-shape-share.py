"""Estimate bmm time share in n==1 or p==1 cases using class-level ns/work."""
import json
import sys
from pathlib import Path

suite = Path(sys.argv[1])
cand = sys.argv[2]
plan = json.loads((suite / "public-drawn-plan.json").read_text(encoding="utf-8"))
verdict = json.loads((suite / f"{cand}-verdict.json").read_text(encoding="utf-8"))
tot = 0.0
small = 0.0
rows = []
for c in plan["cases"]:
    if c["kernel"] != "bmm" or not c["timed"]:
        continue
    cell = c["name"].rsplit(":", 1)[0]
    est = verdict["classes"][cell]["submission_ns"] * c["work"] / 1e6
    is_small = c["n"] <= 4
    tot += est
    if is_small:
        small += est
    rows.append((c["name"], c["n"], c["p"], c["m"], c["batch"], c["work"], est, is_small))
for r in rows:
    print(f"{r[0]:18s} n={r[1]:<4d} p={r[2]:<3d} m={r[3]:<3d} b={r[4]:<6d} work={r[5]:<8d} est={r[6]:7.3f}ms {'SMALL' if r[7] else ''}")
print(f"TOTAL {tot:.3f}ms n<=4 {small:.3f}ms share {100*small/tot:.1f}%")
