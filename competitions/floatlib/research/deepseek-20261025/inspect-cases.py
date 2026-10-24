"""Print value parameters for selected public-v2 cases (read-only)."""
import json
import sys
from pathlib import Path

BASE = Path(
    r"D:\CodingProject\Bitget-DeepSeek\competitions\floatlib\candidates"
    r"\f01-mul-log2-proof1\ci-runs\40098465163"
    r"\download-d2c241d84c5e420bacc37ec73af7fb48"
    r"\diagnostics\f01-d7-public-suite\public-suite"
)
group = sys.argv[1] if len(sys.argv) > 1 else "sparse"
plan = json.loads((BASE / "public-drawn-plan.json").read_text(encoding="utf-8"))
cases = [c for c in plan["cases"] if c["timed"] and c["name"].split(":")[1] == group]
cols = ["center", "spread", "positive", "zeroPct", "zeroKind", "zeroCluster", "subPct",
        "specRate", "mantBits", "work", "m", "n", "p", "batch", "length"]
print(f"{'name':20s} " + " ".join(f"{c:>10s}" for c in cols))
for c in cases:
    print(f"{c['name']:20s} " + " ".join(f"{c.get(k, ''):>10}" for k in cols))
