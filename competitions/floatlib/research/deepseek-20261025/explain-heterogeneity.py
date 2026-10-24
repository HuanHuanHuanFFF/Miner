"""Relate per-run BMM gain to the shape mix of that drawn seed.

For each collected public-v2 run: work-weighted bmm ratio (candidate/baseline)
and the share of BMM work in p buckets. Read-only analysis.
"""
import json
from pathlib import Path

RUNS = Path(r"D:\CodingProject\Bitget-DeepSeek\competitions\floatlib\research\deepseek-20261025\ci-runs")
CAND = "f01-deepseek-p2contp8"
BASE = "f01-d12-scalar-combined"

rows = []
for d in sorted(RUNS.iterdir()):
    if not d.is_dir() or not d.name.isdigit():
        continue
    suite = next((p for p in d.rglob("public-suite") if (p / "public-drawn-plan.json").exists()), None)
    if not suite:
        continue
    plan = json.loads((suite / "public-drawn-plan.json").read_text(encoding="utf-8"))
    work = json.loads((suite / "public-cell-work.json").read_text(encoding="utf-8"))
    try:
        vc = json.loads((suite / f"{CAND}-verdict.json").read_text(encoding="utf-8"))
        vb = json.loads((suite / f"{BASE}-verdict.json").read_text(encoding="utf-8"))
    except FileNotFoundError:
        continue
    bmm_a = sum(vb["classes"][c]["submission_ns"] * work[c] for c in work if c.startswith("bmm:"))
    bmm_c = sum(vc["classes"][c]["submission_ns"] * work[c] for c in work if c.startswith("bmm:"))
    cases = [c for c in plan["cases"] if c["kernel"] == "bmm" and c["timed"]]
    total = sum(c["work"] for c in cases)
    share = {
        "p1": 100 * sum(c["work"] for c in cases if c["p"] == 1) / total,
        "p2": 100 * sum(c["work"] for c in cases if c["p"] == 2) / total,
        "p3_8": 100 * sum(c["work"] for c in cases if 3 <= c["p"] <= 8) / total,
        "p_gt8": 100 * sum(c["work"] for c in cases if c["p"] > 8) / total,
    }
    rows.append((d.name, vc["seed"], bmm_c / bmm_a, share))

print(f"{'run':>12} {'seed':>8} {'bmm':>7} {'p1%':>6} {'p2%':>6} {'p3-8%':>6} {'p>8%':>6}")
for run, seed, ratio, s in sorted(rows, key=lambda r: r[2]):
    print(f"{run:>12} {seed:>8} {ratio:7.4f} {s['p1']:6.1f} {s['p2']:6.1f} {s['p3_8']:6.1f} {s['p_gt8']:6.1f}")
