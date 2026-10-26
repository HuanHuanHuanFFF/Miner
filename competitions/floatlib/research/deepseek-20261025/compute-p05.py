"""Independent re-implementation of the local adoption bootstrap (not official admission).

Mirrors candidates/f01-d7-research/adoption-guard.py:
- ratios per candidate = submission/incumbent per paired round (25 rounds)
- 2000 replicates, one Random(90423) stream, candidate ratios first then baseline
- median of 25 bootstrap draws per side, gain = 1 - median_candidate / median_baseline
- p05 = linear interpolation at (n-1)*0.05
"""
import json
import random
import statistics
import sys
from pathlib import Path

RUNS = Path(r"D:\CodingProject\Bitget-DeepSeek\competitions\floatlib\research\deepseek-20261025\ci-runs")
CANDIDATE = sys.argv[1] if len(sys.argv) > 1 else "f01-deepseek-p2contp8"
BASELINE = "f01-d12-scalar-combined"


def verdict(run_dir, name):
    suite = next(p for p in run_dir.rglob("public-suite") if (p / f"{name}-verdict.json").exists())
    return json.loads((suite / f"{name}-verdict.json").read_text(encoding="utf-8"))


def p05(run_dir, cand=CANDIDATE, base=BASELINE):
    vc, vb = verdict(run_dir, cand), verdict(run_dir, base)
    cand_ratios = [sub / inc for inc, sub in vc["rounds"]]
    base_ratios = [sub / inc for inc, sub in vb["rounds"]]
    rng = random.Random(90423)
    gains = []
    for _ in range(2000):
        med_c = statistics.median(cand_ratios[rng.randrange(25)] for _ in range(25))
        med_b = statistics.median(base_ratios[rng.randrange(25)] for _ in range(25))
        gains.append(1 - med_c / med_b)
    gains.sort()
    k = 0.05 * (len(gains) - 1)
    lo = int(k)
    value = gains[lo] + (gains[lo + 1] - gains[lo]) * (k - lo)
    return vc["ratio"] / vb["ratio"], value


for d in sorted(RUNS.iterdir()):
    if not d.is_dir() or not d.name.isdigit():
        continue
    try:
        rel, p = p05(d)
    except Exception as exc:
        print(d.name, "skip", exc)
        continue
    seeds = set()
    for v in d.rglob("public-suite/*-verdict.json"):
        seeds.add(json.loads(v.read_text(encoding="utf-8"))["seed"])
    print(f"{d.name:>12} seed={sorted(seeds)} normalized={rel:.7f} p05={p:+.6f}")
