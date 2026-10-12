"""D2 same-run total-median-rep decomposition, with every candidate/reference view."""
from pathlib import Path
import hashlib
import json
import statistics

ROOT = Path(__file__).resolve().parents[1]
OUT = ROOT / 'evidence/round26/extension90m/route-d'
RUN = ROOT / 'evidence/round26/38269236685/screen90-d2/gate'
D1 = 'r26-d-658-selective-depth'
D2 = 'r26-d-658-once-budget'
PARENTS = ['public658', 'public658-shadow']
NAMES = PARENTS + [D1, D2, D2 + '-shadow']
DOMAIN = {'lean.txt', 'multibyte.txt', 'source.c.txt', 'source.rs.txt', 'sourcemap.map.txt'}


def sha(raw):
    return hashlib.sha256(raw).hexdigest()


def main():
    data, bindings, meta, metrics = {}, {}, {}, {}
    for name in NAMES:
        path = RUN / ('round1-' + name + '.jsonl')
        bindings[path.relative_to(ROOT).as_posix()] = sha(path.read_bytes())
        records = [json.loads(x) for x in path.read_text().splitlines()]
        meta[name] = next(x for x in records if x['kind'] == 'meta')
        data[name] = {}
        for row in records:
            if row['kind'] != 'file':
                continue
            methods = {}
            for method in [name, 'incumbent']:
                m = row['methods'][method]
                assert m['deterministic'] and not m['errors']
                reps = [(i, x) for i, x in enumerate(m['reps']) if x['phase'] == 'measured']
                assert len(reps) == 11
                original_index, rep = sorted(reps, key=lambda x: x[1]['total_s'])[5]
                assert abs(rep['total_s'] - rep['time_s'] - rep['encode_s']) < 1e-12
                methods[method] = {'total': rep['total_s'], 'parser': rep['time_s'],
                    'encoder': rep['encode_s'], 'original_rep_index': original_index,
                    'order_index': rep['order_index'],
                    'measured_total_range': [min(x[1]['total_s'] for x in reps),
                                             max(x[1]['total_s'] for x in reps)]}
            data[name][row['file']] = {'methods': methods, 'input_sha256': row['sha256'],
                'raw_bytes': row['raw_bytes'], 'output_bytes': row['methods'][name]['output_bytes'],
                'tokens_sha256': row['methods'][name]['tokens_sha256']}
        assert len(data[name]) == 28
        metrics[name] = {'public_X': statistics.mean(x['methods'][name]['total'] /
                             x['methods']['incumbent']['total'] for x in data[name].values()),
                         'public_Y_pct': statistics.mean(x['output_bytes'] / x['raw_bytes'] * 100
                             for x in data[name].values()),
                         'total_output_bytes': sum(x['output_bytes'] for x in data[name].values()),
                         'competition_pool_share': 'UNKNOWN: this script does not score'}
    comparisons = []
    for candidate in [D1, D2, D2 + '-shadow']:
        for parent in PARENTS + ([D1] if candidate != D1 else []):
            rows = []
            x0 = metrics[parent]['public_X']
            for file, v in data[candidate].items():
                w = data[parent][file]
                assert v['input_sha256'] == w['input_sha256'] and v['raw_bytes'] == w['raw_bytes']
                c, b = v['methods'][candidate], w['methods'][parent]
                ic, ip = v['methods']['incumbent']['total'], w['methods']['incumbent']['total']
                terms = {'parser': (c['parser'] - b['parser']) / ic,
                         'encoder': (c['encoder'] - b['encoder']) / ic,
                         'paired_incumbent': b['total'] * (1 / ic - 1 / ip)}
                actual = c['total'] / ic - b['total'] / ip
                assert abs(sum(terms.values()) - actual) < 1e-12
                rows.append({'file': file, 'modified_domain': file in DOMAIN,
                    'tokens_changed': v['tokens_sha256'] != w['tokens_sha256'],
                    'candidate': c, 'parent': b, 'candidate_incumbent_total': ic,
                    'parent_incumbent_total': ip,
                    'relative_total_axis_contribution_pp': actual / 28 / x0 * 100,
                    'components_pp': {k: z / 28 / x0 * 100 for k, z in terms.items()},
                    'parser_time_change_pct': (c['parser'] / b['parser'] - 1) * 100,
                    'output_bytes_delta': v['output_bytes'] - w['output_bytes'],
                    'public_Y_contribution_pp': (v['output_bytes'] - w['output_bytes']) / v['raw_bytes'] * 100 / 28})
            groups = {}
            for label, selected in [('all', rows),
                ('modified_domain', [x for x in rows if x['modified_domain']]),
                ('outside_domain', [x for x in rows if not x['modified_domain']]),
                ('changed_tokens', [x for x in rows if x['tokens_changed']]),
                ('same_tokens', [x for x in rows if not x['tokens_changed']])]:
                groups[label] = {'files': len(selected),
                    'total_axis_change_pp': sum(x['relative_total_axis_contribution_pp'] for x in selected),
                    'components_pp': {k: sum(x['components_pp'][k] for x in selected)
                                       for k in ['parser', 'encoder', 'paired_incumbent']},
                    'parser_delta_ms_at_total_median_reps': sum((x['candidate']['parser'] - x['parent']['parser']) * 1000 for x in selected),
                    'output_bytes_delta': sum(x['output_bytes_delta'] for x in selected),
                    'public_Y_delta_pp': sum(x['public_Y_contribution_pp'] for x in selected)}
            assert abs(groups['all']['total_axis_change_pp'] -
                       (metrics[candidate]['public_X'] / x0 - 1) * 100) < 1e-10
            comparisons.append({'candidate': candidate, 'parent': parent, 'groups': groups, 'rows': rows})
    result = {'status': 'VERIFIED_ORIGINAL_TOTAL_MEDIAN_REP_ARITHMETIC_NOT_CAUSAL',
        'run_id': '38269236685', 'raw_sha256': bindings, 'metrics': metrics,
        'methods_and_environment': {k: {'methods': v['methods'], 'cpu_model': v['cpu_model'],
            'benchmark_provenance': v['benchmark_provenance']} for k, v in meta.items()},
        'comparisons': comparisons,
        'limits': ['One D2 discovery runner/block; same-source copies/calibrations are not independent confirmation.',
                  'Parser and encoder are from the original rep selected by median total; no separate phase medians.',
                  'The incumbent term is an algebraic denominator decomposition, never a correction to measured time.',
                  'Same-domain signal does not isolate hash peek, source revisit, residual walk, branches, layout or CPU noise.',
                  'No score, formal admission, full proof or all-input correctness is inferred.']}
    path = OUT / 'd2-cost-feedback.json'
    assert not path.exists()
    path.write_bytes((json.dumps(result, indent=2) + '\n').encode())
    print(json.dumps({'metrics': metrics, 'comparisons': [{'candidate': x['candidate'], 'parent': x['parent'],
         'all': x['groups']['all'], 'modified_domain': x['groups']['modified_domain']} for x in comparisons]}, indent=2))


if __name__ == '__main__':
    main()
