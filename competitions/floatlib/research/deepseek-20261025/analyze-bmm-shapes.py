"""BMM case shape distribution for one public-v2 draw (seed 1324009).

Joins case parameters with class-level timing aggregates so we can size the
population currently routed to Packed10 (n>4 and p>2). Read-only analysis.
"""
import json
from pathlib import Path

BASE = Path(
    r"D:\CodingProject\Bitget-DeepSeek\competitions\floatlib\candidates"
    r"\f01-mul-log2-proof1\ci-runs\40098465163"
    r"\download-d2c241d84c5e420bacc37ec73af7fb48"
    r"\diagnostics\f01-d7-public-suite\public-suite"
)
plan = json.loads((BASE / "public-drawn-plan.json").read_text(encoding="utf-8"))
verdict = json.loads(
    (BASE / "f01-d12-scalar-combined-verdict.json").read_text(encoding="utf-8")
)

group_ns = {}
for cls, row in verdict["classes"].items():
    op, grp = cls.split(":")
    group_ns[(op, grp)] = row["submission_ns"]

cases = [c for c in plan["cases"] if c["kernel"] == "bmm" and c["timed"]]
print(f"{'case':18s} {'m':>4s} {'n':>4s} {'p':>4s} {'batch':>5s} {'work':>10s} route")
by_grp = {}
for c in cases:
    grp = c["name"].split(":")[1]
    route = "DirectSmall" if (c["n"] <= 4 or c["p"] <= 2) else (
        "DirectContinuous" if (c["n"] <= 4 and c["p"] > 2) else "Packed10")
    by_grp.setdefault(grp, []).append((c, route))
    print(f"{c['name']:18s} {c['m']:4d} {c['n']:4d} {c['p']:4d} {c['batch']:5d} {c['work']:10d} {route}")

print("\nPer-group totals (work = scored work units; ns from class aggregate):")
grand = 0.0
for grp, rows in by_grp.items():
    w = sum(c["work"] for c, _ in rows)
    ns = group_ns.get(("bmm", grp))
    total = ns * w if ns else None
    grand += total or 0
    packed = sum(c["work"] for c, r in rows if r == "Packed10")
    small_p = sum(c["work"] for c, r in rows if r == "Packed10" and c["p"] <= 8)
    print(f"{grp:9s} cases={len(rows):2d} work={w:9d} ns/work={ns:7.3f} total={total/1e6:6.2f}ms "
          f"packed_work={100*packed/w:5.1f}% packed_p<=8={100*small_p/w:5.1f}%")
print(f"bmm total {grand/1e6:.2f} ms")
