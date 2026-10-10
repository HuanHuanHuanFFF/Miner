"""Explain actual calibration/neighbor differences in the BF mixture diagnostic."""
from pathlib import Path
import json
from round10_payability import load_flat_rows, load_official_scorer, validate_policy_for_replay

ROOT = Path(__file__).resolve().parents[1]
E = ROOT / 'evidence/round18'
comp, context, rows = load_flat_rows(E / 'official-extension-30m')
sc = load_official_scorer()
validate_policy_for_replay(comp['policy'], rows, sc)
front = [sc.Point(r['id'], r['metrics']['balanced_time_ratio'], r['metrics']['mean_file_compression_pct'])
         for r in rows if (r.get('score') or {}).get('on_frontier')]
bounds = sc.Boundaries(comp['policy']['max_balanced_time_ratio'], comp['policy']['max_mean_file_compression_pct'])
data = json.loads((E / 'cross-family-bf-29471.json').read_bytes())
options = [data['options'][0], max(data['options'], key=lambda o: o['family_summaries']['591']['median_pct'])]
output = []


def point(p):
    return {'id': p.name, 'time': p.time_s, 'size_pct': p.ratio_pct}


for index, option in enumerate(options):
    for obs in option['observations']:
        p = sc.Point('mixture', obs['projected_time'], obs['projected_size_pct'])
        f = sorted(sc.pareto_front(front + [p]), key=lambda p: p.time_s)
        base = sc.local_global_weights(f, bounds)
        factor = sc.improvement_factors(f, incremental=True, logarithmic=True)
        raw = {name: base[name] * factor[name] for name in base}
        weights = sc.local_global_improvement_space_log_weights(f, bounds)
        i = next((i for i, p in enumerate(f) if p.name == 'mixture'), None)
        assert abs(weights.get('mixture', 0) * 100 - obs['conditional_share_pct']) < 1e-9
        output.append({
            'option': index, 'family': obs['family'], 'calibration': obs['calibration'], 'block': obs['block'],
            'projected_time': p.time_s, 'projected_size_pct': p.ratio_pct, 'share_pct': obs['conditional_share_pct'],
            'left_neighbor': None if i is None or i == 0 else point(f[i - 1]),
            'right_neighbor': None if i is None or i + 1 == len(f) else point(f[i + 1]),
            'frontier_count': len(f), 'removed_existing_ids': sorted({p.name for p in front} - {p.name for p in f}),
            'local_global_base_weight': base.get('mixture', 0), 'log_incremental_factor': factor.get('mixture', 0),
            'normalization_denominator': sum(raw.values()), 'raw_candidate_weight': raw.get('mixture', 0),
        })
result = {'status': 'VERIFIED_SCORER_REPLAY_OF_INFERRED_MIXTURES', 'snapshot': context, 'rows': output,
          'limits': ['No candidate exists for these free file selections.',
                     'Calibration alternatives are not confidence bounds or observed private performance.',
                     'All observed BF blocks and shadows retained; no mean-coordinate score used.']}
(E / 'cross-family-bf-geometry.json').write_bytes((json.dumps(result, indent=2) + '\n').encode())
print(json.dumps([o for o in output if o['block'] == 1 and o['calibration'] == 'primary'], indent=2))
