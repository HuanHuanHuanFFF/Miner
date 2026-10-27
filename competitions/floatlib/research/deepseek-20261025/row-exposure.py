"""Estimate per-row overhead exposure: total (batch*m) over bmm cases."""
import json
import sys
from pathlib import Path

suite = Path(sys.argv[1])
plan = json.loads((suite / "public-drawn-plan.json").read_text(encoding="utf-8"))
cases = [c for c in plan["cases"] if c["kernel"] == "bmm" and c["timed"]]
total_rows = sum(c["batch"] * c["m"] for c in cases)
total_work = sum(c["work"] for c in cases)
print("bmm rows", total_rows, "work", total_work)
for ns in (25, 50, 100):
    print(f"  at {ns}ns/row -> {total_rows*ns/1e6:.2f} ms")
