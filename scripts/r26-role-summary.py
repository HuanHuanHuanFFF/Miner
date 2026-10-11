"""Keep discovery/confirmation, declared candidates/copies and calibration views separate."""
from pathlib import Path
import argparse
import hashlib
import json
import statistics
from collections import defaultdict

ROOT = Path(__file__).resolve().parents[1]

def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('analyses', nargs='+', type=Path)
    ap.add_argument('--output', required=True, type=Path)
    a = ap.parse_args()
    assert not a.output.exists()
    buckets, names, seen, receipts = defaultdict(list), defaultdict(set), {}, {}
    snapshot = None
    for path in a.analyses:
        analysis = json.loads(path.read_bytes())
        if snapshot is None:
            snapshot = analysis['snapshot']
        assert analysis['snapshot'] == snapshot, 'Only one current captured snapshot per summary'
        for filename, identity in analysis['raw_input_audit'].items():
            assert hashlib.sha256((ROOT/filename).read_bytes()).hexdigest() == identity['sha256']
        for candidate in analysis['candidates']:
            rust = candidate['rust_sha256']
            names[rust].add(candidate['candidate'])
            for row in candidate['observations']:
                key = (rust, row['run_id'], row['block'], row['entry_name'], row['calibration'])
                if key in seen:
                    assert seen[key] == row, 'Conflicting repeated observation'
                    continue
                seen[key] = row
                buckets[(rust, row['role'], row['entry_role'], row['calibration'])].append(row)
        for run in analysis['runs']:
            receipts[run['run_id']] = run
    summaries = []
    for (rust, role, entry_role, calibration), rows in buckets.items():
        values = [r['single_pool_share_pct'] for r in rows]
        summaries.append({'rust_sha256': rust, 'candidate_names': sorted(names[rust]),
            'role': role, 'entry_role': entry_role, 'calibration': calibration,
            'observations': len(rows), 'runners': len({r['run_id'] for r in rows}),
            'minimum_pct': min(values), 'median_pct': statistics.median(values), 'maximum_pct': max(values),
            'zero_count': sum(v == 0 for v in values),
            'at_least_5_count': sum(v >= 5 for v in values), 'at_least_10_count': sum(v >= 10 for v in values),
            'blocks': [{k: r[k] for k in ('run_id', 'block', 'entry_name', 'single_pool_share_pct',
                                           'time_change_pct_vs_parent', 'proof_sha256')} for r in rows]})
    # Detect same-source aliases by exact pair, independent of '-copy'/'-shadow' naming.
    controls = []
    for run in receipts.values():
        folder = ROOT/'evidence/round26'/run['run_id']/run['batch']/'gate'
        state = json.loads((folder/'state.json').read_bytes())
        groups = defaultdict(list)
        for entry in state['spec']['entries']:
            groups[tuple(sorted(entry['hashes'].items()))].append(entry)
        metrics = {(m['candidate'], m['round']): m for m in state['metrics']}
        for entries in groups.values():
            if len(entries) < 2:
                continue
            primary = [e for e in entries if not e.get('control')]
            assert len(primary) <= 1, 'Ambiguous duplicate main candidates'
            base = primary[0] if primary else next((e for e in entries if e.get('formal_id')), entries[0])
            for other in entries:
                if other['name'] == base['name']:
                    continue
                for block in range(1, state['spec']['screen_blocks']+1):
                    left, right = (base['name'], block), (other['name'], block)
                    if left not in metrics or right not in metrics:
                        continue
                    hashes = []
                    for name, _ in (left, right):
                        rawpath = folder/f'round{block}-{name}.jsonl'
                        meta = json.loads(rawpath.read_text().splitlines()[0])
                        hashes.append(meta['methods'][name]['lib_sha256'])
                    controls.append({'run_id': run['run_id'], 'block': block, 'main': base['name'],
                        'copy': other['name'], 'same_binary_sha256': hashes[0] == hashes[1],
                        'binary_hashes': hashes,
                        'relative_time_gap_pct': 100*(metrics[right]['time']/metrics[left]['time']-1)})
    result = {'status': 'VERIFIED_ROLE_SEPARATION_ON_CONDITIONALLY_PROJECTED_SHARES',
        'snapshot': snapshot, 'inputs': {str(p): hashlib.sha256(p.read_bytes()).hexdigest() for p in a.analyses},
        'runs': list(receipts.values()), 'summaries': summaries, 'all_same_source_controls': controls,
        'limits': ['Copies and alternative calibrations are not additional independent candidate confirmations.',
                   'Observed success counts are not probabilities. Conditional public projection is not formal reward.',
                   'Failed workflow status is retained even where all original measurements completed before a summary error.']}
    a.output.write_text(json.dumps(result, indent=2)+'\n', encoding='utf-8')
    print(json.dumps({'main': [r for r in summaries if r['entry_role']=='candidate'],
                      'same_source_pairs': len(controls), 'all_same_binary': all(r['same_binary_sha256'] for r in controls)}, indent=2))

if __name__ == '__main__':
    main()
