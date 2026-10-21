"""Independently check single/joint R25 scores and expose observed domination gaps."""
from pathlib import Path
from datetime import datetime, timezone
import argparse
import hashlib
import importlib
import json
from round10_payability import load_flat_rows

ROOT = Path(__file__).resolve().parents[1]
expanded = importlib.import_module('audit-round24-score-algebra').expanded


def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--capture', type=Path, required=True)
    ap.add_argument('--analysis', type=Path, required=True)
    ap.add_argument('--output', type=Path, required=True)
    a = ap.parse_args()
    assert not a.output.exists()
    analysis = json.loads(a.analysis.read_bytes())
    comp, context, rows = load_flat_rows(a.capture)
    assert analysis['snapshot'] == context
    policy = comp['policy']
    assert policy['method'] == 'local-global-improvement-space-log'
    assert policy['pareto_share'] == 1 and policy['improvement_share'] == 0
    formal = [r for r in rows if (r.get('score') or {}).get('on_frontier')]
    base = [(str(r['id']), r['metrics']['balanced_time_ratio'],
             r['metrics']['mean_file_compression_pct']) for r in formal]
    initial = expanded(base)
    top = max(formal, key=lambda r: r['score'].get('payable_weight') or 0)
    top_id = str(top['id'])
    baseline_error = max(abs(initial[str(r['id'])]['share_pct'] -
                             100 * r['score']['pareto_weight']) for r in formal)
    assert baseline_error < 1e-10

    def insert(points):
        eligible = [(name, x, y) for name, x, y in points
                    if 0 < x <= policy['max_balanced_time_ratio'] and
                    0 < y <= policy['max_mean_file_compression_pct'] and
                    not any(t <= x and q <= y for _, t, q in base)]
        return expanded(base + eligible)

    errors, effects, indexed = [], [], {}
    for candidate in analysis['candidates']:
        name = candidate['candidate']
        for o in candidate['observations']:
            key = (name, o['run_id'], o['block'], o['calibration'], o['entry_name'])
            assert key not in indexed
            indexed[key] = o
            x, y = o['projected_time'], o['projected_size_pct']
            weights = insert([(name, x, y)])
            value = weights.get(name, {}).get('share_pct', 0)
            errors.append(abs(value - o['single_pool_share_pct']))
            dominators = [(n, t, q) for n, t, q in base if t <= x and q <= y]
            time_bound = min((t for _, t, q in base if q <= y), default=None)
            size_bound = min((q for _, t, q in base if t <= x), default=None)
            effects.append({'candidate': name,
                            **{k: o[k] for k in ('run_id', 'block', 'role', 'entry_role',
                                                'entry_name', 'calibration', 'projected_time',
                                                'projected_size_pct')},
                            'share_pct': value, 'candidate_terms': weights.get(name),
                            'current_payable_top_id': top_id,
                            'current_top_geometric_change_pp': weights[top_id]['share_pct'] - initial[top_id]['share_pct'] if top_id in weights else -initial[top_id]['share_pct'],
                            'official_dominators': [{'id': n, 'time': t, 'quality': q} for n, t, q in dominators],
                            'fixed_quality_time_dominance_boundary': time_bound,
                            'fixed_time_quality_dominance_boundary': size_bound,
                            'boundary_scope': 'Necessary to escape existing dominance with one axis held fixed; not sufficient for first place, admission or stable payout.'})
    joint_errors, joint_effects = [], []
    for pair in analysis['joint']:
        for row in pair['matched_observations']:
            points = []
            for name in pair['candidates']:
                selected = row['selected_entries'][name]
                key = (name, row['run_id'], row['block'], row['calibration'], selected['name'])
                o = indexed[key]
                assert o['entry_role'] == selected['role']
                alternatives = [v for k, v in indexed.items() if k[:4] == key[:4] and
                                v['entry_role'] == 'candidate']
                if alternatives:
                    assert len(alternatives) == 1 and alternatives[0]['entry_name'] == selected['name']
                points.append((name, o['projected_time'], o['projected_size_pct']))
            weights = insert(points)
            values = {name: weights.get(name, {}).get('share_pct', 0) for name in pair['candidates']}
            for name in pair['candidates']:
                joint_errors.append(abs(values[name] - row['simultaneous_geometric_pct'][name]))
            joint_effects.append({'candidates': pair['candidates'],
                                  **{k: row[k] for k in ('run_id', 'block', 'calibration', 'selected_entries')},
                                  'shares_pct': values,
                                  'top_before_pct': initial[top_id]['share_pct'],
                                  'top_after_pct': weights.get(top_id, {}).get('share_pct', 0)})
    assert errors and joint_errors and max(errors + joint_errors) < 1e-10
    result = {'status': 'VERIFIED_INDEPENDENT_SCORING_ALGEBRA_AND_ROLE_SELECTION',
              'checked_utc': datetime.now(timezone.utc).isoformat(), 'snapshot': context,
              'baseline_frontier_points': len(base), 'single_views': len(errors),
              'joint_cases': len(joint_effects), 'baseline_max_api_error_pp': baseline_error,
              'single_max_error_pp': max(errors), 'joint_max_error_pp': max(joint_errors),
              'single_effects': effects, 'joint_effects': joint_effects,
              'input_sha256': {'analysis': sha(a.analysis),
                              'expanded_algebra_source': sha(ROOT / 'scripts/audit-round24-score-algebra.py')},
              'method': 'Independent Pareto sweep; expanded local/global corner products and incremental log-axis budget; one final normalization. Official scorer implementation is not imported.',
              'limits': ['Coordinate transfers are conditional; algebra agreement is not evidence of private performance.',
                         'Views include controls and repeated calibrations, not independent sample count.',
                         'Fixed-axis dominance boundaries are hypothetical geometry, not measured speedups or noise bounds.']}
    a.output.write_text(json.dumps(result, indent=2) + '\n', encoding='utf-8')
    print(json.dumps({k: result[k] for k in ('status', 'single_views', 'joint_cases',
                     'baseline_max_api_error_pp', 'single_max_error_pp', 'joint_max_error_pp')}))


if __name__ == '__main__':
    main()
