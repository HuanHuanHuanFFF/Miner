"""List BMM p values across collected public-v2 runs (routing analysis)."""
import json
import sys
from pathlib import Path

for arg in sys.argv[1:]:
    base = Path(arg)
    plan = base / "public-drawn-plan.json"
    if not plan.exists():
        print(arg, "no plan")
        continue
    cases = [c for c in json.loads(plan.read_text(encoding="utf-8"))["cases"]
             if c["kernel"] == "bmm" and c["timed"]]
    ps = sorted({c["p"] for c in cases})
    work_9_16 = sum(c["work"] for c in cases if 9 <= c["p"] <= 16)
    work_all = sum(c["work"] for c in cases)
    print(base.parts[-5] if len(base.parts) > 5 else base, "p values:", ps,
          f"work_9_16={100*work_9_16/work_all:.1f}%")
