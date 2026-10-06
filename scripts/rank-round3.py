"""Re-rank measured public points against a frozen official snapshot.

Usage: python scripts/rank-round3.py evidence/round3/snapshot-ID RUN_ID ...
This is conditional geometry. It does not produce admission or payment evidence.
"""
from __future__ import annotations
import importlib.util
import json
from pathlib import Path
import statistics
import sys

ROOT = Path(__file__).resolve().parents[1]


def main():
    snapshot = Path(sys.argv[1]).resolve()
    runs = sys.argv[2:]
    pages = json.loads((snapshot / 'pareto-pages.json').read_text())
    context = pages[0]['context']
    assert all(p['context'] == context for p in pages)
    rows = [r for p in pages for r in p['items'] if (r.get('score') or {}).get('on_frontier')]
    spec = importlib.util.spec_from_file_location('rank3_tools', ROOT / 'scripts/round3.py')
    helper = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(helper)
    scorer = helper.load_scorer(ROOT / 'sources/conjectures-optimisation-deflate/validator/scoring/pareto.py')
    points = [{'id': r['id'], 'official_time': r['metrics']['balanced_time_ratio'], 'official_size': r['metrics']['mean_file_compression_pct']} for r in rows]
    official = [scorer.Point(p['id'], p['official_time'], p['official_size']) for p in points]
    w = scorer.local_global_improvement_space_log_weights(official)
    err = max(abs(w[r['id']] - r['score']['pareto_weight']) for r in rows)
    assert err < 1e-10
    collected = {}
    for run in runs:
        assert run.isdecimal()
        analysis = json.loads((ROOT / 'evidence/round3' / run / 'analysis.json').read_text())
        for row in analysis['summaries']:
            collected.setdefault(row['candidate'], []).append((run, row))
    result = []
    for name, evidence in collected.items():
        # Each independent runner receives equal weight, regardless of whether
        # that candidate was screened in two or refined in four order blocks.
        x = statistics.mean(r['public_time_mean'] for _, r in evidence)
        y = evidence[0][1]['public_size_pct']
        assert all(abs(r['public_size_pct'] - y) < 1e-12 for _, r in evidence)
        anchor_x = statistics.mean(r['probe3_anchored']['calibrated_time'] for _, r in evidence)
        fixed = helper.geometry(x, y, points)
        anchor = helper.geometry(anchor_x / helper.TIME_FACTOR, y, points)
        slow_anchor = max(r['probe3_anchored_time_range'][1] for _, r in evidence)
        stressed = helper.geometry(slow_anchor * 1.01 / helper.TIME_FACTOR, y, points)
        f = scorer.pareto_front(official + [scorer.Point('hypothetical', anchor['calibrated_time'], anchor['calibrated_size'])])
        weight = scorer.local_global_improvement_space_log_weights(f).get('hypothetical', 0)
        result.append({'candidate': name, 'runs': [run for run, _ in evidence],
                       'public_time_mean_across_runners': x, 'public_size_pct': y,
                       'fixed_factor': fixed, 'probe3_anchored': anchor,
                       'slower_observed_block_plus_1pct': stressed,
                       'conditional_geometry_share_if_admitted': weight if anchor['on_geometric_frontier'] else 0,
                       'fresh_gates': {run: r['fresh_gate'] for run, r in evidence if r.get('fresh_gate') is not None}})
    result.sort(key=lambda r: (-int(r['fixed_factor']['on_geometric_frontier'] and r['probe3_anchored']['on_geometric_frontier']), -r['slower_observed_block_plus_1pct']['on_geometric_frontier'], -r['conditional_geometry_share_if_admitted'], r['probe3_anchored']['size_gap_pp']))
    output = {'scope': 'conditional geometry under #427 transfer assumptions; not official admission, payout or private-stage2 evidence',
              'context': context, 'scorer_weight_max_error': err, 'candidates': result}
    dest = ROOT / 'evidence/round3' / ('ranking-' + context['snapshot_id'] + '.json')
    dest.write_text(json.dumps(output, indent=2) + '\n')
    print('snapshot', context['snapshot_id'], 'result', dest)
    for r in result:
        print(r['candidate'], 'public=', round(r['public_time_mean_across_runners'], 6), round(r['public_size_pct'], 6),
              'fixed=', r['fixed_factor']['on_geometric_frontier'], 'anchor=', r['probe3_anchored']['on_geometric_frontier'],
              'anchor_xy=', round(r['probe3_anchored']['calibrated_time'], 6), round(r['probe3_anchored']['calibrated_size'], 6),
              'stress=', r['slower_observed_block_plus_1pct']['on_geometric_frontier'],
              'conditional_share=', round(100 * r['conditional_geometry_share_if_admitted'], 4))


if __name__ == '__main__':
    main()
