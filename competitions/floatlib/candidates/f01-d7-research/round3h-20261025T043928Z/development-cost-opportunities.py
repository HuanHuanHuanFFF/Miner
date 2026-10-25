"""Use measured work-weighted retained cost, never input-domain frequency."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import importlib.util
import json

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[4]
spec = importlib.util.spec_from_file_location('r15_cost_guard', HERE / 'adoption-guard.py')
g = importlib.util.module_from_spec(spec)
spec.loader.exec_module(g)
run = 40155753018
name = 'f01-d12-scalar-combined'
p = g.load_run(ROOT, HERE.parent, run, (name,))
v = p['verdicts'][name]
assert v['passed'] and v['stage'] == 'score' and len(v['rounds']) == 25
costs = {c: float(v['classes'][c]['submission_ns']) * work for c, work in p['cell_work'].items()}
total = sum(costs.values())
rows = []
for op in ('add', 'mul', 'sum', 'bmm'):
    cells = [dict(cell=c, work=p['cell_work'][c], submission_ns=v['classes'][c]['submission_ns'],
                  weighted_cost=costs[c], total_time_share=costs[c] / total)
             for c in costs if c.startswith(op + ':')]
    cost = sum(row['weighted_cost'] for row in cells)
    share = cost / total
    rows.append(dict(operation=op, total_time_share=share,
                     whole_time_reduction_if_2x=share / 2,
                     maximum_whole_time_reduction_if_free=share,
                     cells=sorted(cells, key=lambda r: -r['weighted_cost'])))
record = dict(at_utc=datetime.now(timezone.utc).isoformat(), run=run, candidate=name,
              sha256=p['kernel_hashes'][name], evidence=p['evidence'], rows=rows,
              meaning='Measured submission_ns times official cell_work. Counterfactual reductions only, not promised realizable gains; input-domain frequencies are not time shares.',
              champion_model_sha256=hashlib.sha256((HERE.parent / 'champion-time-estimate.json').read_bytes()).hexdigest())
target = HERE / 'development-cost-opportunities.json'
assert not target.exists()
target.write_bytes((json.dumps(record, ensure_ascii=False, indent=2) + '\n').encode())
print(json.dumps(dict(run=run, rows=[{k: r[k] for k in ('operation', 'total_time_share', 'whole_time_reduction_if_2x')} for r in rows])))
