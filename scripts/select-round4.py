"""Recompute research-only frontier geometry from all collected round4 runs.

This report cannot establish private-corpus performance, admission or payment.
Only #432 and #299 derivatives have a corresponding formal-family anchor.
"""
from __future__ import annotations
import argparse
from datetime import datetime, timezone
import hashlib
import json
from pathlib import Path
import statistics
import subprocess

from round4 import load_scorer, TIME_FACTOR, SIZE_FACTOR

ROOT = Path(__file__).resolve().parents[1]
OUT = ROOT / 'evidence/round4'


def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--snapshot', required=True)
    args = ap.parse_args()
    snapshot = ROOT / args.snapshot
    pages = json.loads(snapshot.read_text())
    context = pages[0]['context']
    assert all(p['context'] == context for p in pages)
    items = [i for p in pages for i in p['items']]
    assert len({i['id'] for i in items}) == len(items)
    official = {i['id']: i for i in items}
    scorer = load_scorer(ROOT / 'sources/conjectures-optimisation-deflate/validator/scoring/pareto.py')
    front = [scorer.Point(i['id'], i['metrics']['balanced_time_ratio'], i['metrics']['mean_file_compression_pct'])
             for i in items if (i.get('score') or {}).get('on_frontier')]
    weights = scorer.local_global_improvement_space_log_weights(front)
    score_error = max(abs(weights[p.name] - official[p.name]['score']['pareto_weight']) for p in front)
    assert score_error < 1e-10

    def geometry(x, y):
        dominators = [p.name for p in front if p.time_s <= x and p.ratio_pct <= y]
        eligible = x <= 10 and y <= 40
        on_front = eligible and not dominators
        conditional_weight = 0.0
        if on_front:
            nf = scorer.pareto_front(front + [scorer.Point('hypothetical', x, y)])
            conditional_weight = scorer.local_global_improvement_space_log_weights(nf).get('hypothetical', 0)
        size_limit = min((p.ratio_pct for p in front if p.time_s <= x), default=40)
        time_limit = min((p.time_s for p in front if p.ratio_pct <= y), default=10)
        return {'time': x, 'size_pct': y, 'on_geometric_frontier': on_front,
                'dominating_ids': dominators, 'size_gap_pp': max(0, y - size_limit),
                'time_margin_pct': 100 * (time_limit / x - 1),
                'conditional_geometry_weight': conditional_weight}

    summary = json.loads((OUT / 'cross-run-summary.json').read_text())
    results = []
    for c in summary['candidates']:
        name, runners = c['candidate'], c['runners']
        x = statistics.mean(r['public_time'] for r in runners)
        y = c['aggregate']['public_size_pct']
        anchors = {r['anchor'] for r in runners}
        assert len(anchors) == 1
        anchor = anchors.pop()
        anchor_id = {'public432': '432', 'public299': '299', 'probe3': '427'}[anchor]
        formal = official[anchor_id]['metrics']
        txs = [formal['balanced_time_ratio'] * (1 + r['mean_delta_pct_vs_anchor'] / 100) for r in runners]
        anchor_public = next(g for g in summary['candidates'] if g['candidate'] == anchor)
        ay = formal['mean_file_compression_pct'] * y / anchor_public['aggregate']['public_size_pct']
        family = 'unknown_H_family' if ('-h' in name and name.startswith('r4-parse-')) else (
            'same_family_hypothesis' if anchor in {'public432', 'public299'} else 'probe3_anchor')
        if name == 'r4-parse-plan-d8':
            family = 'cross_family_heuristic'
        if name.startswith('r4-hybrid-'):
            family = 'unknown_hybrid_family'
        stress_x = max(formal['balanced_time_ratio'] * (1 + d / 100)
                       for r in runners for d in r['delta_pct_vs_anchor']) * 1.01
        result = {'candidate': name, 'hashes': c['hashes'], 'runner_count': len(runners),
                  'cpu_models': sorted({r['cpu_model'] for r in runners}),
                  'public_time_equal_runner_mean': x, 'public_size_pct': y,
                  'anchor': anchor_id, 'anchor_scope': family,
                  'anchor_time_change_pct_equal_runner_mean': statistics.mean(r['mean_delta_pct_vs_anchor'] for r in runners),
                  'anchor_time_change_pct_runner_median': statistics.median(r['mean_delta_pct_vs_anchor'] for r in runners),
                  'anchor_time_change_pct_runner_range': [min(r['mean_delta_pct_vs_anchor'] for r in runners), max(r['mean_delta_pct_vs_anchor'] for r in runners)],
                  'runner_geometry_pass_count': sum(geometry(tx, ay)['on_geometric_frontier'] for tx in txs),
                  'fixed_427': geometry(x * TIME_FACTOR, y * SIZE_FACTOR),
                  'matched_anchor': geometry(statistics.mean(txs), ay),
                  'slowest_observed_anchor_block_plus_1pct': geometry(stress_x, ay),
                  'accepted_gate_runs': [r['run'] for r in runners if r['accepted_public_gate'] is True]}
        if anchor == 'public299' or family in {'unknown_H_family', 'unknown_hybrid_family'}:
            # #299 is only a sensitivity comparison for uniform H, never a
            # claimed same-family calibration for that different parser.
            base = next(g for g in summary['candidates'] if g['candidate'] == 'public299')
            factor = official['299']['metrics']['mean_file_compression_pct'] / base['aggregate']['public_size_pct']
            result['size_with_299_factor_sensitivity'] = y * factor
        results.append(result)
    prior = json.loads((ROOT / 'evidence/round3/selection.json').read_text())
    base = next(c for c in results if c['candidate'] == 'r3-432-fast3')
    assert base['hashes'] == {f: v['sha256'] for f, v in prior['files'].items()}
    for f, expected in base['hashes'].items():
        assert sha(ROOT / 'candidates/r3-432-fast3' / f) == expected
    old_run = ROOT / 'evidence/round3/37493517227'
    old_ci = json.loads((old_run / 'ci-run.json').read_text())
    old_gate = json.loads((old_run / 'r3-432-fast3-gate.json').read_text())
    assert old_ci['headSha'] == prior['candidate_ci_commit']
    assert old_ci['conclusion'] == 'success' and old_gate['accepted'] is True
    old_hashes = {}
    for f, expected in base['hashes'].items():
        blob = subprocess.check_output(['git', '-c', f'safe.directory={ROOT.as_posix()}',
                                        'show', f"{old_ci['headSha']}:candidates/r3-432-fast3/{f}"], cwd=ROOT)
        old_hashes[f] = hashlib.sha256(blob).hexdigest()
        assert old_hashes[f] == expected
    base['accepted_gate_runs'].append('37493517227')
    base['prior_gate_binding'] = {'ci_commit': old_ci['headSha'], 'git_tree_sha256': old_hashes,
                                  'accepted_gate_json_sha256': sha(old_run / 'r3-432-fast3-gate.json')}
    measured_new = [c for c in results if c['candidate'].startswith('r4-')]
    research_front = [c['candidate'] for c in measured_new if c['accepted_gate_runs'] and
                      c['matched_anchor']['on_geometric_frontier'] and c['fixed_427']['on_geometric_frontier']]
    report = {'checked_at_utc': datetime.now(timezone.utc).isoformat(),
              'research_window': ['2026-10-06T18:44:59Z', '2026-10-06T23:44:59Z'],
              'status': 'RESEARCH_EVIDENCE_ONLY; FORMAL_ADMISSION_AND_REWARD_UNKNOWN',
              'selected_baseline': 'r3-432-fast3', 'new_gated_candidates_passing_both_geometry_hypotheses': research_front,
              'selection_warning': 'Geometry alone is insufficient. H has no formal-family anchor. Small CPU gains failed independent reproduction; selection requires reading the accompanying evidence.',
              'snapshot': context, 'snapshot_path': snapshot.relative_to(ROOT).as_posix(), 'snapshot_sha256': sha(snapshot),
              'official_weight_replay_max_error': score_error,
              'new_candidates_with_public_measurements': len(measured_new),
              'paired_public_measurement_processes': sum(r['measurement_processes'] for r in summary['runs']),
              'fresh_successful_gate_executions': sum(len(c['accepted_gate_runs']) for c in measured_new),
              'distinct_new_candidates_with_accepted_gate': sum(bool(c['accepted_gate_runs']) for c in measured_new),
              'runs': summary['runs'], 'candidates': results,
              'formal_submission_performed': False, 'wallet_or_payment_action_performed': False}
    (OUT / 'selection.json').write_text(json.dumps(report, indent=2, allow_nan=False) + '\n')
    print('SNAPSHOT', context['snapshot_id'], 'new measured', len(measured_new), 'processes', report['paired_public_measurement_processes'])
    print('BASELINE', json.dumps(base, ensure_ascii=False))
    print('NEW_GATED_GEOMETRY_HYPOTHESES', research_front)


if __name__ == '__main__':
    main()
