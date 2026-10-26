"""Show bmm cases with outputs=work/n and route for one draw."""
import json
import sys
from pathlib import Path

suite = Path(sys.argv[1])
plan = json.loads((suite / "public-drawn-plan.json").read_text(encoding="utf-8"))
for c in plan["cases"]:
    if c["kernel"] != "bmm" or not c["timed"]:
        continue
    outs = c["work"] // max(c["n"], 1)
    if c["name"].split(":")[1] in ("extremes", "specials", "dense"):
        print(f"{c['name']:18s} m={c['m']:<4d} n={c['n']:<4d} p={c['p']:<3d} batch={c['batch']:<6d} "
              f"work={c['work']:<9d} outputs={outs}")
