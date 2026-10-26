"""Print per-class official-gate A/B for two candidates in a collected run."""
import json
import sys
from pathlib import Path

run_dir = Path(sys.argv[1])
a_name, b_name = sys.argv[2], sys.argv[3]
stage = next(run_dir.glob("download-*"))
rows = {r["candidate"]: r for r in json.loads((stage / "summary.json").read_text(encoding="utf-8"))["results"]}
a, b = rows[a_name]["classes"], rows[b_name]["classes"]
print(f"{'class':20s} {a_name:>10s} {b_name:>10s} {'b/a':>8s}")
for k in a:
    av, bv = a[k]["submission_ns"], b[k]["submission_ns"]
    print(f"{k:20s} {av:10.1f} {bv:10.1f} {bv/av:8.4f}")
