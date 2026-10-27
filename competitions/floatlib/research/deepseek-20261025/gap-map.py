"""Inferred per-class remaining gap vs champion #323.

Assumption (INFERRED): both suites' references are 'the same baseline family', so
(cand/inc) ratios are comparable across suites. Then champ/B2 ~= ratio_champ / ratio_B2.
Only used to rank targets, never as measured head-to-head.
"""
import json
import sys
from pathlib import Path

b2_run = Path(sys.argv[1])
champ_report = Path(sys.argv[2])
suite = next(p for p in b2_run.rglob("public-suite") if (p / "public-cell-work.json").exists())
work = json.loads((suite / "public-cell-work.json").read_text(encoding="utf-8"))
b2 = json.loads((suite / "f01-r15-dev-packed-b2-1-verdict.json").read_text(encoding="utf-8"))
champ = json.loads(champ_report.read_text(encoding="utf-8"))
if "report" in champ:
    champ = json.loads(champ["report"])

rows = []
for cls, rec in champ["classes"].items():
    if cls not in work:
        continue
    r_champ = rec["submission_ns"] / rec["incumbent_ns"]
    r_b2 = b2["classes"][cls]["submission_ns"] / b2["classes"][cls]["incumbent_ns"]
    est = r_champ / r_b2
    ms = work[cls] * b2["classes"][cls]["submission_ns"] / 1e6
    rows.append((cls, ms, r_b2, r_champ, est, ms * (est - 1)))

rows.sort(key=lambda r: -r[5])
tot_ms = sum(r[1] for r in rows)
tot_gap = sum(r[5] for r in rows)
print(f"B2 total {tot_ms:.2f}ms, inferred gap {tot_gap:.2f}ms ({100*tot_gap/tot_ms:.1f}%)")
for cls, ms, r_b2, r_c, est, gap in rows:
    print(f"{cls:18s} b2={ms:7.2f}ms r_b2={r_b2:.4f} r_c={r_c:.4f} est={est:.3f} gap={gap:6.2f}ms")
