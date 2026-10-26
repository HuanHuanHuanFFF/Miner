"""Summarize wall seconds of past FloatLib gate rows from retained artifacts."""
import json
from pathlib import Path

BASE = Path(r"D:\CodingProject\Bitget-DeepSeek\competitions\floatlib\candidates\f01-mul-log2-proof1\ci-runs")
rows = []
for summary in BASE.glob("*/download-*/summary.json"):
    try:
        d = json.loads(summary.read_text(encoding="utf-8"))
    except Exception:
        continue
    for r in d.get("results", []):
        rows.append((summary.parts[-3], r.get("candidate"), r.get("wall_seconds"),
                     r.get("full_gate"), r.get("validation_mode")))
rows.sort(key=lambda x: (x[0] or "", x[1] or ""))
for run, cand, wall, full, mode in rows[-40:]:
    print(f"{run:>12} {str(cand):32s} wall={wall!s:>10} full={full} mode={mode}")
print("count", len(rows))
