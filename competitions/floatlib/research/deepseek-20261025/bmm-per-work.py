"""Print BMM per-cell work and ns/work for one verdict."""
import json
import sys
from pathlib import Path

suite = Path(sys.argv[1])
name = sys.argv[2]
work = json.loads((suite / "public-cell-work.json").read_text(encoding="utf-8"))
v = json.loads((suite / f"{name}-verdict.json").read_text(encoding="utf-8"))
for cell in sorted(work):
    if not cell.startswith("bmm"):
        continue
    row = v["classes"][cell]
    print(f"{cell:18s} work={work[cell]:9d} total={row['submission_ns']*work[cell]/1e6:7.2f}ms "
          f"{row['submission_ns']:7.2f} ns/work")
