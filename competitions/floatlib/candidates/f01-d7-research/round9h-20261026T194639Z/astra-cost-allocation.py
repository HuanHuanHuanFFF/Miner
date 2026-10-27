"""Read frozen model only; do not fit new control timings or change global status."""
from pathlib import Path
import hashlib, json, statistics

ROOT = Path(__file__).resolve().parents[5]
HERE = Path(__file__).resolve().parent
path = ROOT / 'competitions/floatlib/candidates/f01-d7-research/champion-time-estimate.json'
raw = path.read_bytes()
model = json.loads(raw)
samples = []
for s in model['samples']:
    own = s['candidate_total_ns']
    champ = s['champion_projected_total_ns']
    total = sum(own.values())
    ctotal = sum(champ.values())
    samples.append({
        'run': s['run'], 'seed': s['seed'],
        'operation_fraction': {k: v / total for k, v in own.items()},
        'matrix_elimination_max_whole_gain': own['bmm'] / total,
        'matrix_2x_whole_gain': 0.5 * own['bmm'] / total,
        'matrix_3x_whole_gain': (2 / 3) * own['bmm'] / total,
        'matrix_3x_whole_ratio_to_champion_model': (total - (2 / 3) * own['bmm']) / ctotal,
        'matrix_zero_whole_ratio_to_champion_model': (total - own['bmm']) / ctotal,
        'whole_ratio': total / ctotal,
    })
result = {
    'status': 'INFERRED_FROZEN_MODEL_COST_ALLOCATION_ONLY',
    'source_model_sha256': hashlib.sha256(raw).hexdigest(),
    'source_sha256': model['kernel_sha256'],
    'champion': model['champion_submission'],
    'direct_champion_timing': 'UNKNOWN',
    'interpretation': 'BMM coverage/implementation cost requires actual public-v2 path evidence; theoretical whole gain is not measured improvement.',
    'median_fraction': {k: statistics.median(s['operation_fraction'][k] for s in samples) for k in ['add','mul','sum','bmm']},
    'median_matrix_2x_whole_gain': statistics.median(s['matrix_2x_whole_gain'] for s in samples),
    'median_matrix_3x_whole_gain': statistics.median(s['matrix_3x_whole_gain'] for s in samples),
    'samples': samples,
}
out = HERE / 'astra-cost-allocation.json'
out.write_text(json.dumps(result, ensure_ascii=False, indent=2) + '\n', encoding='utf-8')
print(json.dumps({k:v for k,v in result.items() if k!='samples'}, ensure_ascii=False, indent=2))
