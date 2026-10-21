"""Re-rank measured public points against a frozen official snapshot.

Usage: python scripts/rank-round3.py evidence/round3/snapshot-ID RUN_ID ...
This is conditional geometry. It does not produce admission or payment evidence.
"""
from __future__ import annotations
import importlib.util
import json
from pathlib import Path
import random
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
    all_official = {r['id']: r for p in pages for r in p['items']}
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
    measured_by_run = {}
    for run in runs:
        assert run.isdecimal()
        analysis = json.loads((ROOT / 'evidence/round3' / run / 'analysis.json').read_text())
        measured_by_run[run] = {(m['candidate'], m['round']): m for m in analysis['metrics']}
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
        own = None
        family = ('407' if name.startswith('round3-speed-407-') or name == 'public407'
                  else '432' if name.startswith('r3-432-') or name == 'public432' else None)
        if family:
            control = 'public' + family
            formal = all_official[family]['metrics']
            per_run = []
            per_file_runs = []
            for run, _ in evidence:
                ms = measured_by_run[run]
                common = sorted(b for n, b in ms if n == name and (control, b) in ms)
                if not common:
                    continue
                times = [formal['balanced_time_ratio'] * ms[name, b]['time'] / ms[control, b]['time'] for b in common]
                sizes = [formal['mean_file_compression_pct'] * ms[name, b]['size_pct'] / ms[control, b]['size_pct'] for b in common]
                filenames = sorted(ms[name, common[0]]['per_file_time'])
                per_file_runs.append({f: (statistics.mean(ms[control, b]['per_file_time'][f] for b in common),
                                         statistics.mean(ms[name, b]['per_file_time'][f] for b in common)) for f in filenames})
                per_run.append({'run': run, 'matched_blocks': common, 'time': statistics.mean(times), 'size_pct': statistics.mean(sizes),
                                'time_range': [min(times), max(times)],
                                'time_change_pct_by_block': [100 * (ms[name, b]['time'] / ms[control, b]['time'] - 1) for b in common],
                                'size_change_pp': ms[name, common[0]]['size_pct'] - ms[control, common[0]]['size_pct']})
            if per_run:
                own_x = statistics.mean(r['time'] for r in per_run)
                own_y = statistics.mean(r['size_pct'] for r in per_run)
                own_g = helper.geometry(own_x / helper.TIME_FACTOR, own_y / helper.SIZE_FACTOR, points)
                own_front = scorer.pareto_front(official + [scorer.Point('hypothetical', own_x, own_y)])
                own_weight = scorer.local_global_improvement_space_log_weights(own_front).get('hypothetical', 0)
                own_stress = helper.geometry(max(r['time_range'][1] for r in per_run) * 1.01 / helper.TIME_FACTOR,
                                             own_y / helper.SIZE_FACTOR, points)
                # Descriptive only: files are resampled from the public corpus.
                # This omits private stage2, host uncertainty and search selection.
                paired = [(statistics.mean(r[f][0] for r in per_file_runs), statistics.mean(r[f][1] for r in per_file_runs)) for f in filenames]
                rng = random.Random(20261007)
                draws = []
                for _ in range(2000):
                    sample = rng.choices(paired, k=len(paired))
                    reference_sum = sum(a for a, _ in sample)
                    draws.append(100 * (reference_sum - sum(b for _, b in sample)) / reference_sum)
                draws.sort()
                own = {'reference_submission_id': family, 'scope': 'relative changes transfer to this same-family formal reference; still no private-stage2 observation',
                       **own_g, 'slower_observed_block_plus_1pct': own_stress,
                       'descriptive_public_file_bootstrap': {'draws': 2000, 'lower5_speed_gain_pct': draws[99], 'upper95_speed_gain_pct': draws[1899],
                                                            'scope': 'public-file resampling of matched-block means; excludes private stage2, host and selection uncertainty; not official admission'},
                       'conditional_geometry_share_if_admitted': own_weight if own_g['on_geometric_frontier'] else 0, 'per_run': per_run}
        probe3_weight = weight if anchor['on_geometric_frontier'] else 0
        all_calibrations = fixed['on_geometric_frontier'] and anchor['on_geometric_frontier'] and (own is None or own['on_geometric_frontier'])
        result.append({'candidate': name, 'runs': [run for run, _ in evidence],
                       'public_time_mean_across_runners': x, 'public_size_pct': y,
                       'fixed_factor': fixed, 'probe3_anchored': anchor,
                       'slower_observed_block_plus_1pct': stressed,
                       'passes_all_available_calibrations': all_calibrations,
                       'probe3_anchor_conditional_geometry_share_if_admitted': probe3_weight,
                       'conditional_geometry_share_if_admitted': own['conditional_geometry_share_if_admitted'] if own else probe3_weight,
                       'own_family_anchor': own,
                       'fresh_gates': {run: r['fresh_gate'] for run, r in evidence if r.get('fresh_gate') is not None}})
    result.sort(key=lambda r: (-r['passes_all_available_calibrations'], -r['conditional_geometry_share_if_admitted'], r['probe3_anchored']['size_gap_pp']))
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
              'conditional_share=', round(100 * r['conditional_geometry_share_if_admitted'], 4),
              'own_family_frontier=', r['own_family_anchor']['on_geometric_frontier'] if r['own_family_anchor'] else None)


if __name__ == '__main__':
    main()
