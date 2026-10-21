"""Account for original paired-axis deltas without replacing official scores.

Generalizes Astra's R25 dual8 same-run decomposition to later frozen candidates.
Each component comes from the actual total-median repetition, never from sums
of independently selected component medians. This is descriptive, not causal.
"""
from pathlib import Path
import argparse
import hashlib
import json

ROOT = Path(__file__).resolve().parents[1]


def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def median_rep(method):
    assert method['deterministic'] and not method['errors']
    values = sorted((r for r in method['reps'] if r['phase'] == 'measured'),
                    key=lambda r: r['total_s'])
    assert len(values) == 11 and all(r['total_s'] > 0 for r in values)
    r = values[5]
    assert abs(r['time_s'] + r['encode_s'] - r['total_s']) < 1e-10
    return {'parse_s': r['time_s'], 'encode_s': r['encode_s'],
            'total_s': r['total_s'], 'order_index': r['order_index']}


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('receipt', type=Path)
    ap.add_argument('--candidate', nargs='+', required=True)
    ap.add_argument('--parent', required=True)
    ap.add_argument('--output', type=Path, required=True)
    a = ap.parse_args()
    assert not a.output.exists(), 'Keep prior descriptions immutable'
    folder = a.receipt.resolve()
    state = json.loads((folder/'state.json').read_bytes())
    inv = json.loads((folder/'raw-artifact-files.json').read_bytes())
    entries = {e['name']: e for e in state['spec']['entries']}
    metrics = {(m['candidate'], m['round']): m for m in state['metrics']}

    def read(name, block):
        path = folder/f'round{block}-{name}.jsonl'
        expected = inv['files'][path.name]
        assert path.stat().st_size == expected['bytes'] and sha(path) == expected['sha256']
        records = [json.loads(x) for x in path.read_text().splitlines() if x.strip()]
        meta = records[0]
        assert meta['measured_rounds'] == 11 and meta['warmup_rounds'] == 1
        assert meta['methods'][name]['source_sha256'] == entries[name]['hashes']['parse.rs']
        rows = {r['file']: r for r in records if r['kind'] == 'file'}
        assert len(rows) == 28 and sum(r['raw_bytes'] for r in rows.values()) == 15930000
        return {'path': path.relative_to(ROOT).as_posix(), 'sha256': sha(path),
                'methods': meta['methods'], 'rows': rows}

    analyses = []
    for name in a.candidate:
        blocks = sorted(b for n, b in metrics if n == name)
        assert blocks
        for block in blocks:
            assert (a.parent, block) in metrics
            parent, candidate = read(a.parent, block), read(name, block)
            rows = []
            for file, pr in parent['rows'].items():
                cr = candidate['rows'][file]
                assert (pr['raw_bytes'], pr['sha256']) == (cr['raw_bytes'], cr['sha256'])
                p, pi = [median_rep(pr['methods'][k]) for k in (a.parent, 'incumbent')]
                c, ci = [median_rep(cr['methods'][k]) for k in (name, 'incumbent')]
                dp, dc = pi['total_s'], ci['total_s']
                weight = .5*(1/dc + 1/dp)
                parse = (c['parse_s'] - p['parse_s'])*weight
                encode = (c['encode_s'] - p['encode_s'])*weight
                denominator = .5*(c['total_s'] + p['total_s'])*(1/dc - 1/dp)
                pa, ca = p['total_s']/dp, c['total_s']/dc
                assert abs(parse + encode + denominator - (ca - pa)) < 1e-10
                same = all(pr['methods'][a.parent][k] == cr['methods'][name][k]
                           for k in ('tokens_sha256', 'output_sha256', 'output_bytes'))
                rows.append({'file': file, 'input_sha256': pr['sha256'],
                    'identical_token_and_output': same,
                    'parent': p, 'candidate': c, 'parent_incumbent': pi,
                    'candidate_incumbent': ci, 'parent_axis': pa, 'candidate_axis': ca,
                    'parse_axis_delta': parse/28, 'encode_axis_delta': encode/28,
                    'paired_denominator_axis_delta': denominator/28})
            pa = sum(r['parent_axis'] for r in rows)/28
            ca = sum(r['candidate_axis'] for r in rows)/28
            assert abs(pa - metrics[a.parent, block]['time']) < 1e-12
            assert abs(ca - metrics[name, block]['time']) < 1e-12
            keys = ('parse_axis_delta', 'encode_axis_delta', 'paired_denominator_axis_delta')

            def components(selected):
                return {k.replace('axis_delta', 'relative_pct_contribution'):
                        sum(r[k] for r in selected)/pa*100 for k in keys}

            groups = {}
            for flag in (False, True):
                selected = [r for r in rows if r['identical_token_and_output'] == flag]
                groups['identical_output' if flag else 'changed_output'] = {
                    'files': len(selected), **components(selected)}
            analyses.append({'block': block, 'candidate': name, 'parent': a.parent,
                'parent_axis': pa, 'candidate_axis': ca,
                'relative_total_change_pct': 100*(ca/pa - 1), **components(rows),
                'groups': groups, 'rows': rows,
                'parent_receipt': {k: v for k, v in parent.items() if k != 'rows'},
                'candidate_receipt': {k: v for k, v in candidate.items() if k != 'rows'}})
    result = {'status': 'VERIFIED_DESCRIPTIVE_SAME_RUN_RAW_COMPONENT_DECOMPOSITION',
        'run': state['run_id'], 'git_sha': state['git_sha'],
        'role': state['spec'].get('r18_role', 'discovery'),
        'method': 'Actual total-median rep per method/file; symmetric algebra separates parser, encoder and independently paired incumbent denominator. Components sum to the original mean paired-axis difference.',
        'limits': ['Descriptive accounting only, not a modified official score, causal attribution, confidence interval or recoverable speedup.',
                   'Identical tokens/output do not imply identical generated code or environment. Separate processes and runners are not pooled.'],
        'analyses': analyses}
    a.output.write_bytes((json.dumps(result, indent=2)+'\n').encode())
    print(json.dumps([{k: v for k, v in r.items() if k not in
                      ('rows', 'parent_receipt', 'candidate_receipt')} for r in analyses], indent=2))


if __name__ == '__main__':
    main()
