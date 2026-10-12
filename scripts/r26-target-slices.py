"""Small latest-snapshot investment slices; hypothetical coordinates, never measurements."""
from pathlib import Path
import argparse
import hashlib
import importlib
import json

M = importlib.import_module('r26-score-map')
ROOT = M.ROOT

def intervals(rows, target, key):
    groups, active = [], []
    for row in rows:
        if row['minimum_share_pct'] >= target:
            active.append(row)
        elif active:
            groups.append(active)
            active = []
    if active:
        groups.append(active)
    return [{'min': g[0][key], 'max': g[-1][key], 'minimum_share_pct': min(r['minimum_share_pct'] for r in g),
             'maximum_share_pct': max(r['maximum_share_pct'] for r in g)} for g in groups]

def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--capture', type=Path, required=True)
    ap.add_argument('--output', type=Path, required=True)
    a = ap.parse_args()
    assert not a.output.exists()
    replay = M.Replay(a.capture, ROOT/'evidence/round26/official-rules-start-live')
    audit = M.audit(replay)
    history = [ROOT/'evidence/round26'/f for f in ('a3-analysis-29789.json', 'a5-analysis-29793.json', 'a67-analysis-29795.json')]
    factors = [1.0]
    refs = []
    for file in history:
        for row in json.loads(file.read_bytes())['same_source_controls']:
            if row['parent'] == 'public641':
                assert row['same_binary_sha256']
                factors.append(1/(1+row['relative_time_gap_pct']/100))
                refs.append(row)
    x0 = replay.byid['641']['metrics']['balanced_time_ratio']
    y0 = replay.byid['641']['metrics']['mean_file_compression_pct']
    result = {'status': 'INFERRED_INVESTMENT_SLICES_NOT_PERFORMANCE_OR_STABILITY', 'snapshot': replay.context,
        'official641': replay.byid['641']['metrics'], 'reference_factors': factors, 'reference_observations': refs,
        'audited_frontier_size': len(replay.base), 'slices': []}
    def shares(x, y, fs):
        scores = [replay.describe([('hypothetical', x*f, y)])['points']['hypothetical']['share_pct'] for f in fs]
        return min(scores), max(scores)
    for label, fs in [('primary_only', [1.0]), ('primary_and_observed_parent_shadow_factors', factors)]:
        times, qualities = [], []
        for i in range(2001):
            x = .425 + i*.00002
            low, high = shares(x, y0, fs)
            times.append({'x': x, 'minimum_share_pct': low, 'maximum_share_pct': high})
        for i in range(3501):
            y = 35.3 + i*.0002
            low, high = shares(x0, y, fs)
            qualities.append({'y': y, 'minimum_share_pct': low, 'maximum_share_pct': high})
        targets = {}
        for t in (5, 10):
            tx, qy = intervals(times, t, 'x'), intervals(qualities, t, 'y')
            targets[str(t)] = {'fixed_quality_time_intervals': tx, 'fixed_time_quality_intervals': qy}
            targets[str(t)]['least_sample_time_reduction_pct'] = 100*(1-max(g['max'] for g in tx)/x0) if tx else None
            targets[str(t)]['least_sample_quality_reduction_pp'] = y0-max(g['max'] for g in qy) if qy else None
        result['slices'].append({'view': label, 'targets': targets,
            'time_grid': {'min': .425, 'max': .465, 'step': .00002},
            'quality_grid': {'min': 35.3, 'max': 36.0, 'step': .0002}})
    result['limits'] = ['Sampled sets are not continuous thresholds. Faster/smaller endpoints can lose share.',
        'Shadow factors are observed same-source calibration disagreements, not candidate noise bounds.',
        'Uniformly applying a factor is a planning assumption, not an achievable improvement or future success probability.',
        'Real candidate decisions require new original paired totals and frozen independent confirmation.']
    result['input_hashes'] = {str(p.relative_to(ROOT)): hashlib.sha256(p.read_bytes()).hexdigest() for p in history}
    a.output.write_text(json.dumps(result, indent=2)+'\n', encoding='utf-8')
    print(json.dumps(result['slices'], indent=2))

if __name__ == '__main__':
    main()
