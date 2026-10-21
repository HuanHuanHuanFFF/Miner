"""Sample fixed-quality #552 planning slices on an already captured official snapshot."""
from pathlib import Path
from datetime import datetime, timezone
import argparse
import hashlib
import importlib
import json

M = importlib.import_module('r26-score-map')
ROOT = M.ROOT


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--capture', type=Path, required=True)
    parser.add_argument('--output', type=Path, required=True)
    args = parser.parse_args()
    assert not args.output.exists()
    replay = M.Replay(args.capture, ROOT / 'evidence/round26/official-rules-start-live')
    audit = M.audit(replay)
    metrics = replay.byid['552']['metrics']
    x0 = metrics['balanced_time_ratio']
    y0 = metrics['mean_file_compression_pct']
    rows = []
    for index in range(2501):
        x = 0.5 + index * 0.001
        point = replay.describe([('hypothetical552', x, y0)])['points']['hypothetical552']
        rows.append({'x': x, 'share_pct': point['share_pct']})
    targets = {}
    for target in (5, 10):
        groups, active = [], []
        for row in rows:
            if row['share_pct'] >= target:
                active.append(row)
            elif active:
                groups.append(active)
                active = []
        if active:
            groups.append(active)
        targets[str(target)] = {
            'sampled_time_intervals': [{'min': group[0]['x'], 'max': group[-1]['x']} for group in groups],
            'least_sampled_time_reduction_pct': 100 * (1 - max(group[-1]['x'] for group in groups) / x0) if groups else None,
        }
    result = {
        'status': 'INFERRED_CAPTURED_SNAPSHOT_PLANNING_ONLY',
        'computed_utc': datetime.now(timezone.utc).isoformat(),
        'capture': str(args.capture), 'context': replay.context,
        'capture_retrieval_end_utc': replay.receipt['retrieval_end_utc'],
        'captured_official552': metrics, 'policy_audit': audit,
        'grid': {'min': 0.5, 'max': 3.0, 'step': 0.001}, 'targets': targets,
        'sampled_peak': max(rows, key=lambda row: row['share_pct']),
        'input_sha256': hashlib.sha256((args.capture / 'pareto-pages.json').read_bytes()).hexdigest(),
        'limits': ['No new API query: root captured this pinned snapshot; it may have advanced since retrieval.',
                   'Coordinates are hypothetical admission on an independently eligible identity. No candidate measurement, private assurance, payout or success probability.',
                   'Sampled sets are not continuous thresholds. Current source reuse only establishes an implementation starting point; R10 historical speedup is not a #552 result.'],
    }
    args.output.write_bytes((json.dumps(result, indent=2) + '\n').encode())
    print(json.dumps({'snapshot': replay.context['snapshot_id'], 'official552': metrics,
                      'targets': targets, 'sampled_peak': result['sampled_peak']}, indent=2))


if __name__ == '__main__':
    main()
