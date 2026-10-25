"""Separate candidate cost from reference drift in completed control gates."""
from pathlib import Path
from datetime import datetime, timezone
import argparse
import importlib.util
import json

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[4]
ap = argparse.ArgumentParser()
ap.add_argument('--run', type=int, required=True)
a = ap.parse_args()
spec = importlib.util.spec_from_file_location('r16_control_decomposition', HERE / 'adoption-guard.py')
g = importlib.util.module_from_spec(spec)
spec.loader.exec_module(g)
names = ('f01-r15-dev-packed-b2-1', 'f01-r8-combined-result-guard')
p = g.load_run(ROOT, HERE.parent, a.run, names)
assert all(v.get('passed') and v.get('stage') == 'score' for v in p['verdicts'].values())
result = {}
for op in ('add', 'mul', 'sum', 'bmm'):
    totals = {name: {kind: sum(cell[kind + '_ns'] * p['cell_work'][key]
                              for key, cell in v['classes'].items() if key.startswith(op + ':'))
                     for kind in ('submission', 'incumbent')} for name, v in p['verdicts'].items()}
    left, right = (totals[n] for n in names)
    result[op] = dict(totals=totals,
                     raw_submission_B2_over_41=left['submission'] / right['submission'],
                     raw_reference_B2_gate_over_41_gate=left['incumbent'] / right['incumbent'],
                     reference_normalized_B2_over_41=(left['submission']/left['incumbent'])/(right['submission']/right['incumbent']))
report = dict(at_utc=datetime.now(timezone.utc).isoformat(), run=a.run, seed=p['seed'],
              evidence=p['evidence'], operations=result,
              scope='Completed same-plan original controls; decomposition diagnoses reference drift, without recalibration, source selection, reseeding or an adoption claim.')
out = HERE / f'development-baseline-control-decomposition-{a.run}.json'
with out.open('xb') as stream:
    stream.write((json.dumps(report, ensure_ascii=False, indent=2)+'\n').encode())
print(json.dumps({op: {k: v for k, v in row.items() if k != 'totals'} for op, row in result.items()}))
