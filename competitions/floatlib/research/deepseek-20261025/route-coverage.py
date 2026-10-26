"""Coverage of BMM work by routing predicates across collected public-v2 plans."""
import json
import sys
from pathlib import Path

preds = {
    "p<=8": lambda c: c["p"] <= 8,
    "p>8 and n<=8": lambda c: c["p"] > 8 and c["n"] <= 8,
    "p>8 and n<=16": lambda c: c["p"] > 8 and c["n"] <= 16,
    "p>8 and n>8": lambda c: c["p"] > 8 and c["n"] > 8,
}
for arg in sys.argv[1:]:
    plan = Path(arg) / "public-drawn-plan.json"
    cases = [c for c in json.loads(plan.read_text(encoding="utf-8"))["cases"]
             if c["kernel"] == "bmm" and c["timed"]]
    total = sum(c["work"] for c in cases)
    print(Path(arg).parts[-5] if len(Path(arg).parts) > 5 else arg,
          "total work", total)
    for name, fn in preds.items():
        w = sum(c["work"] for c in cases if fn(c))
        print(f"  {name:16s} {100*w/total:5.1f}%")
