"""B2 dispatch-extension coverage: shapes currently outside the pair path."""
import json
import sys
from pathlib import Path

for arg in sys.argv[1:]:
    suite = Path(arg)
    plan = json.loads((suite / "public-drawn-plan.json").read_text(encoding="utf-8"))
    cases = [c for c in plan["cases"] if c["kernel"] == "bmm" and c["timed"]]
    total = sum(c["work"] for c in cases)
    def in_b2(c):
        return 2 <= c["p"] <= 8 and c["n"] > 1 and c["m"] >= 4
    m23 = sum(c["work"] for c in cases if 2 <= c["p"] <= 8 and c["n"] > 1 and c["m"] in (2, 3))
    n1 = sum(c["work"] for c in cases if 2 <= c["p"] <= 8 and c["n"] == 1 and c["m"] >= 4)
    print(Path(arg).parts[-5] if len(Path(arg).parts) > 5 else arg,
          f"total={total} b2={100*sum(c['work'] for c in cases if in_b2(c))/total:.1f}% "
          f"m2-3={100*m23/total:.1f}% n1={100*n1/total:.1f}%")
