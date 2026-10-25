"""Bound a distinct n=1 cache opportunity using only completed discovery data."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[4]
D7 = HERE.parent
COMMON = ROOT / 'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs'
index_path = D7 / 'public-suite-results.json'
raw_index = index_path.read_bytes()
rows = [r for r in json.loads(raw_index)['records'] if r['kernel_sha256'] ==
        '622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58' and r.get('full_gate')]
result = []
for row in rows:
    run = COMMON / str(row['run'])
    index = json.loads((run / 'original-artifact-hashes.json').read_bytes())
    path = run / index['directory'] / 'diagnostics/f01-d7-public-suite/public-suite/public-drawn-plan.json'
    data = path.read_bytes()
    record = index['files'][path.relative_to(run / index['directory']).as_posix()]
    assert hashlib.sha256(data).hexdigest() == record['sha256'] and len(data) == record['bytes']
    cells = {}
    eligible = []
    for case in json.loads(data)['cases']:
        if not case['timed'] or case['kernel'] != 'bmm':
            continue
        target = case['n'] == 1 and case['m'] >= 4 and case['p'] >= 2
        cells.setdefault(case['name'].rsplit(':', 1)[0], []).append(target)
        if target:
            eligible.append({k: case[k] for k in ('name', 'batch', 'm', 'n', 'p', 'work')})
    whole = sum(c['submission_ns'] * row['cell_work'][name] for name, c in row['classes'].items())
    cell_cost = {name: row['classes'][name]['submission_ns'] * row['cell_work'][name] for name in cells}
    result.append(dict(run=row['run'], seed=row['seed'], target_cases=eligible,
                       whole_time_lower_percent=100 * sum(cell_cost[n] for n, flags in cells.items() if all(flags)) / whole,
                       whole_time_upper_percent=100 * sum(cell_cost[n] for n, flags in cells.items() if any(flags)) / whole,
                       drawn_plan_sha256=record['sha256']))
report = dict(at_utc=datetime.now(timezone.utc).isoformat(), records=result,
              input_index_sha256=hashlib.sha256(raw_index).hexdigest(),
              scope='Completed B2 samples only; class-total bounds for n=1,m>=4,p>=2, before underflow routing. Bounds are not measured subset time or speedup. No R16 confirmation input exists or is read.')
destination = HERE / 'development-n1-coverage-screen.json'
with destination.open('xb') as stream:
    stream.write((json.dumps(report, ensure_ascii=False, indent=2)+'\n').encode())
print(json.dumps([{k: row[k] for k in ('run', 'seed', 'whole_time_lower_percent', 'whole_time_upper_percent')} |
                 dict(target_shapes=len(row['target_cases'])) for row in result]))
