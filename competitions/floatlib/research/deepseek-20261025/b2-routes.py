"""B2 bmm route coverage and per-route work share for one public-v2 draw."""
import json
import sys
from pathlib import Path

suite = Path(sys.argv[1])
plan = json.loads((suite / "public-drawn-plan.json").read_text(encoding="utf-8"))
cases = [c for c in plan["cases"] if c["kernel"] == "bmm" and c["timed"]]


def route(c):
    m, n, p = c["m"], c["n"], c["p"]
    if 2 <= p <= 8 and n > 1 and m >= 4:
        return "B2pair"
    if (n <= 4 and 2 < p) or p <= 8:
        return "DirectContinuous"
    return "Packed10"


tot = sum(c["work"] for c in cases)
agg = {}
for c in cases:
    agg.setdefault(route(c), [0, 0])
    agg[route(c)][0] += 1
    agg[route(c)][1] += c["work"]
print("seed", json.loads((suite / "summary.json").read_text())["seed"], "total work", tot)
for k, (cnt, w) in sorted(agg.items(), key=lambda kv: -kv[1][1]):
    print(f"{k:18s} cases={cnt:2d} work={w:9d} {100*w/tot:5.1f}%")
