"""Keep R25 main blocks, copies, calibration views and confirmed pairs distinct."""
from pathlib import Path
from datetime import datetime, timezone
import argparse
import hashlib
import json
import statistics as st

ROOT = Path(__file__).resolve().parents[1]


def read(path):
    return json.loads(path.read_bytes())


def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def statistics(rows):
    values = [r['single_pool_share_pct'] for r in rows]
    return {'observations': len(rows), 'runs': len({r['run_id'] for r in rows}),
            'minimum_pct': min(values), 'median_pct': st.median(values),
            'maximum_pct': max(values), 'zero_count': sum(x == 0 for x in values),
            'at_least_10_count': sum(x >= 10 for x in values),
            'at_least_15_count': sum(x >= 15 for x in values),
            'relative_time_vs_actual_parent_range_pct':
                [min(v), max(v)] if (v := [r['time_change_pct_vs_parent'] for r in rows
                    if r.get('time_change_pct_vs_parent') is not None]) else None}


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--analysis', type=Path, required=True)
    ap.add_argument('--rank', type=Path, required=True)
    ap.add_argument('--anchors', type=Path, required=True)
    ap.add_argument('--output', type=Path, required=True)
    a = ap.parse_args()
    assert not a.output.exists()
    analysis, rank, anchors = [read(p) for p in (a.analysis, a.rank, a.anchors)]
    assert analysis['snapshot'] == rank['snapshot'] == anchors['snapshot']
    candidates = []
    compact_keys = ('run_id', 'block', 'role', 'entry_role', 'entry_name',
                    'calibration', 'anchor_name', 'projected_time',
                    'projected_size_pct', 'single_pool_share_pct',
                    'time_change_pct_vs_parent', 'size_change_pp_vs_parent',
                    'proof_sha256')
    for candidate in analysis['candidates']:
        observations = candidate['observations']
        cohorts = []
        for role, entry_role, calibration in sorted({
            (r['role'], r['entry_role'], r['calibration']) for r in observations}):
            selected = [r for r in observations if
                        (r['role'], r['entry_role'], r['calibration']) ==
                        (role, entry_role, calibration)]
            cohorts.append({'role': role, 'entry_role': entry_role,
                            'calibration': calibration, **statistics(selected)})
        comparisons = []
        keys = sorted({(r['run_id'], r['block'], r['entry_name']) for r in observations})
        for run, block, name in keys:
            views = {r['calibration']: r for r in observations
                     if (r['run_id'], r['block'], r['entry_name']) == (run, block, name)}
            if set(views) != {'primary', 'shadow'}:
                continue
            p, s = [views[c]['single_pool_share_pct'] for c in ('primary', 'shadow')]
            comparisons.append({'run_id': run, 'block': block, 'entry_name': name,
                                'primary_pct': p, 'shadow_pct': s,
                                'positive_verdict_disagrees': (p > 0) != (s > 0),
                                'ten_pct_verdict_disagrees': (p >= 10) != (s >= 10),
                                'fifteen_pct_verdict_disagrees': (p >= 15) != (s >= 15)})
        candidates.append({'candidate': candidate['candidate'],
                           'rust_sha256': candidate['rust_sha256'],
                           'verified_pairs': candidate['verified_pairs'],
                           'cohorts': cohorts,
                           'by_run': candidate['by_run_summary'],
                           'main_rank_summary': next(r['summary'] for r in rank['candidates']
                                                     if r['candidate'] == candidate['candidate']),
                           'observations': [{k: r.get(k) for k in compact_keys} for r in observations],
                           'same_source_anchor_comparisons': comparisons})
    pair = next(j for j in analysis['joint'] if set(j['candidates']) ==
                {'r25-astra-end4', 'r25-root-tiny-pc8'})
    pair_rows = [{k: r[k] for k in ('run_id', 'block', 'calibration',
                                  'selected_entries', 'separate_pct', 'simultaneous_geometric_pct')}
                 for r in pair['matched_observations']]
    native = {}
    for p in sorted((ROOT / 'evidence/round25').glob('feedback-*-native.json')):
        data = read(p)
        if data.get('status') != 'VERIFIED_ORIGINAL_ENCODER_BYTES_ONLY':
            continue
        for row in data['summary']:
            name = row['candidate']
            h = data['candidate_hashes'][name]['parse.rs']
            first_batch = p.name == 'feedback-a-native.json'
            parent = 'combo' if first_batch else data['parent']
            delta_bytes = row['delta_bytes_vs_combo' if first_batch else 'delta_bytes_vs_parent']
            delta_pp = row['delta_balanced_pp_vs_combo' if first_batch else 'delta_balanced_pp_vs_parent']
            native.setdefault(h, []).append({'receipt': p.relative_to(ROOT).as_posix(),
                 'run_id': data['run'], 'entry_name': name, 'parent': parent,
                 'delta_bytes_vs_parent': delta_bytes, 'delta_balanced_pp_vs_parent': delta_pp,
                 **{k: row[k] for k in ('public_size_pct', 'total_bytes')}})
    sources = []
    for p in sorted((ROOT / 'candidates').glob('r25-*/manifest.json')):
        data = read(p)
        for name, digest in data['hashes'].items():
            assert sha(p.parent / name) == digest
        sources.append({'path': p.parent.relative_to(ROOT).as_posix(),
                        'files': data['hashes'], 'parent': data['parent'],
                        'mechanism': data['mechanism'], 'proof_status': data['proof_status'],
                        'native_quality_observations': native.get(data['hashes']['parse.rs'], []),
                        'timed': any(c['rust_sha256'] == data['hashes']['parse.rs'] for c in candidates)})
    out = {'status': 'INFERRED_CURRENT_PUBLIC_PROJECTIONS_TARGET_NOT_ESTABLISHED',
           'calculated_utc': datetime.now(timezone.utc).isoformat(),
           'snapshot': analysis['snapshot'], 'input_hashes':
               {p.relative_to(ROOT).as_posix() if p.is_absolute() else p.as_posix(): sha(p)
                for p in (a.analysis, a.rank, a.anchors)},
           'original_paired_processes': analysis['paired_processes'], 'runs': analysis['runs'],
           'source_pairs': sources, 'distinct_rust_count': len({s['files']['parse.rs'] for s in sources}),
           'candidates': candidates, 'same_source_controls': analysis['same_source_controls'],
           'retained_pair_joint': pair_rows,
           'related_anchor_main_observations': anchors['candidate_observations'],
           'related_anchor_reference_backtest': anchors['reference_backtest'],
           'stable_first_established': False, 'formal_submission_sent': False,
           'formal_admission': 'UNKNOWN', 'formal_payable_share_pct': None,
           'limits': ['Every projection is conditional on public-to-private transfer and future admission.',
                      'Only entry_role=candidate is a main block. Same-source copies and calibration views do not add independent samples.',
                      'Incidental control observations and every zero remain visible; they are not relabeled as frozen confirmation.',
                      'The two retained sources were jointly reinserted into the same frontier, not added arithmetically.',
                      'Observed frequencies are not probabilities of a future formal result.']}
    a.output.write_text(json.dumps(out, indent=2) + '\n', encoding='utf-8')
    print(json.dumps({'snapshot': out['snapshot']['snapshot_id'],
                      'distinct_rust_count': out['distinct_rust_count'],
                      'original_paired_processes': out['original_paired_processes'],
                      'retained_pair_joint_rows': len(pair_rows)}))


if __name__ == '__main__':
    main()
