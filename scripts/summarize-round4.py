"""Combine independent round-four receipts without double-counting stage uploads.

Numbers remain public-corpus observations or explicitly conditional transfers;
neither this report nor a passed public gate implies official admission.
"""
from __future__ import annotations
import hashlib
import json
from pathlib import Path
import statistics
import sys

ROOT = Path(__file__).resolve().parents[1]
EVIDENCE = ROOT / 'evidence/round4'


def digest(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def main():
    groups = {}
    runs = []
    for run in sorted(EVIDENCE.iterdir()):
        if not run.is_dir() or not run.name.isdecimal():
            continue
        phase = next((p for p in ['gate', 'refine', 'screen'] if (run / p / 'analysis.json').exists()), None)
        if phase is None:
            continue
        directory = run / phase
        analysis = json.loads((directory / 'analysis.json').read_text())
        state = json.loads((directory / 'state.json').read_text())
        assert analysis['run_id'] == run.name == state['run_id']
        assert analysis['git_sha'] == state['git_sha']
        provenance = {'run': run.name, 'phase': phase, 'git_sha': state['git_sha'],
                      'analysis_sha256': digest(directory / 'analysis.json'),
                      'state_sha256': digest(directory / 'state.json'),
                      'snapshot_id': analysis['snapshot']['snapshot_id']}
        runs.append(provenance)
        entries = {e['name']: e for e in state['spec']['entries']}
        by = {(m['candidate'], m['round']): m for m in analysis['metrics']}
        for row in analysis['summary']:
            name = row['candidate']
            entry = entries[name]
            key = (name, entry['hashes']['parse.rs'], entry['hashes']['Parse.lean'])
            record = groups.setdefault(key, {'candidate': name, 'hashes': entry['hashes'],
                                             'control': entry.get('control', False), 'runners': []})
            blocks = row['blocks']
            deltas = [100 * (by[name, b]['time'] / by['r3-432-fast3', b]['time'] - 1) for b in blocks]
            assert all(abs(a - b) < 1e-10 for a, b in zip(deltas, row['time_change_pct_vs_fast3'], strict=True))
            gate = state['gates'].get(name)
            if gate:
                for file, expected in entry['hashes'].items():
                    assert digest(directory / ('input-' + name) / file) == expected
            equivalent = state.get('equivalence', {}).get(name)
            record['runners'].append({**provenance, 'blocks': blocks, 'public_time': row['time'],
                                     'public_size_pct': row['size_pct'], 'delta_pct_vs_fast3': deltas,
                                     'mean_delta_pct_vs_fast3': statistics.mean(deltas),
                                     'own_anchor': row['own_anchor'], 'fixed_427': row['fixed_427'],
                                     'stress_1pct': row['stress_1pct'], 'public_equivalence': equivalent,
                                     'accepted_public_gate': gate.get('accepted') if gate else None,
                                     'calibration_scope': entry.get('calibration_scope', 'same-family hypothesis; private transfer unverified')})
    result = []
    for g in groups.values():
        runner_deltas = [r['mean_delta_pct_vs_fast3'] for r in g['runners']]
        sizes = {r['public_size_pct'] for r in g['runners']}
        assert len(sizes) == 1, ('output metric drift for exact bytes', g['candidate'])
        g['aggregate'] = {'runner_count': len(runner_deltas), 'public_size_pct': sizes.pop(),
                          'equal_runner_mean_delta_pct': statistics.mean(runner_deltas),
                          'runner_delta_range_pct': [min(runner_deltas), max(runner_deltas)],
                          'every_runner_mean_faster': all(d < 0 for d in runner_deltas),
                          'accepted_public_gate_count': sum(r['accepted_public_gate'] is True for r in g['runners']),
                          'all_own_anchor_frontier': all(r['own_anchor']['on_frontier'] for r in g['runners']),
                          'all_stress_frontier': all(r['stress_1pct']['on_frontier'] for r in g['runners'])}
        result.append(g)
    result.sort(key=lambda g: g['aggregate']['equal_runner_mean_delta_pct'])
    report = {'scope': 'One latest uploaded phase per CI run; equal runner weighting; no confidence or admission claim.',
              'conditional_geometry_warning': 'Snapshot and model can differ across runs; own_anchor is not a private-stage measurement.',
              'runs': runs, 'candidates': result}
    target = EVIDENCE / 'cross-run-summary.json'
    target.write_text(json.dumps(report, indent=2, allow_nan=False) + '\n')
    for g in result:
        a = g['aggregate']
        print(g['candidate'], 'runs', a['runner_count'], 'delta', round(a['equal_runner_mean_delta_pct'], 4),
              'range', [round(x, 4) for x in a['runner_delta_range_pct']],
              'size', round(a['public_size_pct'], 6), 'gates', a['accepted_public_gate_count'],
              'all_stress_front', a['all_stress_frontier'])


if __name__ == '__main__':
    main()
