"""Planning thresholds from the unchanged frozen model; never a new estimate."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json
import statistics

OUT = Path(__file__).resolve().parent
MODEL = OUT.parent / 'champion-time-estimate.json'
raw = MODEL.read_bytes()
assert hashlib.sha256(raw).hexdigest() == '8e6812617ed0dc8c3b7a050bc274c44e884a9312fa49f24531d18ca9a7fc3915'
model = json.loads(raw)
samples = model['samples']
operations = ('add', 'mul', 'sum', 'bmm')


def ratio(speedups):
    return statistics.median(
        sum(row['candidate_total_ns'][op] / speedups.get(op, 1.0) for op in operations)
        / sum(row['champion_projected_total_ns'].values()) for row in samples)


assert abs(ratio({}) - model['whole']['ratio_median']) < 1e-12
scenarios = []
for speeds in [dict(bmm=2.0), dict(mul=2.0), dict(mul=3.0), dict(mul=2.0, bmm=1.2), dict(mul=1.5, bmm=2.0), dict(add=1.5, mul=1.5, bmm=1.2)]:
    scenarios.append(dict(assumed_actual_whole_operation_speedups=speeds, scenario_champion_ratio=ratio(speeds)))
requirements = []
for bmm in (1.0, 1.2, 1.5, 2.0):
    lo, hi = 1.0, 64.0
    assert ratio(dict(mul=hi, bmm=bmm)) <= .97
    for _ in range(60):
        middle = (lo + hi) / 2
        if ratio(dict(mul=middle, bmm=bmm)) <= .97:
            hi = middle
        else:
            lo = middle
    requirements.append(dict(assumed_actual_whole_bmm_speedup=bmm, required_actual_whole_mul_speedup_for_ratio097=hi))
result = dict(at_utc=datetime.now(timezone.utc).isoformat(), state='PLANNING_SCENARIOS_ONLY', frozen_model_sha256=hashlib.sha256(raw).hexdigest(),
              unchanged_baseline_champion_ratio=ratio({}), champion=model['champion_submission'], scenarios=scenarios,
              required_speedups=requirements,
              scope='Uniform speedups over complete operation costs, including guards/preparation/fallback, are assumptions for a required-effect threshold. Not source-level instruction counts, eligible-input fractions, candidate forecasts or measured improvements. All six original frozen workload projections retained; model and dashboard unchanged.')
(OUT / 'development-required-gains.json').write_bytes((json.dumps(result, indent=2) + '\n').encode())
assert MODEL.read_bytes() == raw
print(json.dumps(result))
