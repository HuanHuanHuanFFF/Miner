"""Relate measured public changes to the bounded R10 mechanism diagnostics."""
from pathlib import Path
import argparse
import hashlib
import json
import statistics

ROOT = Path(__file__).resolve().parents[1]


def load(path):
    return json.loads(path.read_bytes())


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('receipt', type=Path)
    args = ap.parse_args()
    folder = args.receipt
    state = load(folder / 'state.json')
    entries = {e['name']: e for e in state['spec']['entries']}
    by = {}
    for metric in state['metrics']:
        name, block = metric['candidate'], metric['round']
        data = [json.loads(line) for line in (folder / f'round{block}-{name}.jsonl').read_text().splitlines()]
        assert data[0]['methods'][name]['source_sha256'] == entries[name]['hashes']['parse.rs']
        rows = [r for r in data if r['kind'] == 'file']
        assert len(rows) == 28
        out = {}
        for r in rows:
            def median(method, field):
                reps = [x for x in r['methods'][method]['reps'] if x['phase'] == 'measured']
                assert len(reps) == 11 and not r['methods'][method]['errors']
                return statistics.median(x[field] for x in reps)
            out[r['file']] = {'input_sha256': r['sha256'], 'raw_bytes': r['raw_bytes'],
                'time_ratio': median(name, 'total_s') / median('incumbent', 'total_s'),
                'parser_fraction': median(name, 'time_s') / median(name, 'total_s'),
                'size_pct': 100 * r['methods'][name]['output_bytes'] / r['raw_bytes'],
                'output_bytes': r['methods'][name]['output_bytes'],
                'tokens_sha256': r['methods'][name]['tokens_sha256'],
                'output_sha256': r['methods'][name]['output_sha256']}
        by[name, block] = out
    result = {'run_id': state['run_id'], 'source_commit': state['git_sha'], 'phase': state['phase'],
              'scope': 'Public per-file measurements recomputed from original repetitions; diagnostic timers remain parser-only and allocation/order-sensitive.',
              'candidates': [], 'forward': None, 'finder': None, 'endprobe': None, 'costcache': None}
    forward_path = folder / 'forward-diagnostics/forward.json'
    routes = {}
    if forward_path.exists():
        forward = load(forward_path)
        assert forward['status'] == 'VERIFIED_FINITE_FORWARD_DIAGNOSTIC'
        public = [r for r in forward['seed_records'] if not r['synthetic']]
        for r in public:
            name = forward['corpus'][r['case']]['file']
            routes[name] = 'native-D' if r['row'] < 5 else 'general-text-D'
        result['forward'] = {'status': forward['status'], 'public_seed_checks': len(public),
            'synthetic_seed_checks': sum(r['synthetic'] for r in forward['seed_records']),
            'profile_comparisons': len(forward['records']),
            'all_rs_equal': all(r['rs_equal'] for r in forward['seed_records']),
            'coarse_equal_file_collect_plus_seed_over_old_forward': statistics.mean((r['collect_ns'] + r['seed_ns']) / r['forward_ns'] for r in public),
            'coarse_equal_file_seed_share_in_new_frontend': statistics.mean(r['seed_ns'] / (r['collect_ns'] + r['seed_ns']) for r in public),
            'timing_limits': 'One uninstrumented old/collect/seed ordering, Vec allocation scopes differ from production. Not an official time axis or causal decomposition.',
            'public_files': [{'file': forward['corpus'][r['case']]['file'], 'route_group': routes[forward['corpus'][r['case']]['file']], **r} for r in public],
            'profile_limits': 'Sampled helper timers overlap and perturb code. Do not add their inclusive estimates.'}
    for name, entry in entries.items():
        if entry.get('control'):
            continue
        blocks = sorted(block for n, block in by if n == name and ('r9-block-scalar', block) in by)
        if not blocks:
            continue
        files = []
        for file in by[name, blocks[0]]:
            metrics = [by[name, b][file] for b in blocks]
            parents = [by['r9-block-scalar', b][file] for b in blocks]
            assert all(a['input_sha256'] == p['input_sha256'] for a, p in zip(metrics, parents))
            assert len({a['output_sha256'] for a in metrics}) == 1
            files.append({'file': file, 'route_group': routes.get(file, 'other'),
                'candidate_time_ratio': statistics.mean(a['time_ratio'] for a in metrics),
                'scalar_time_ratio': statistics.mean(a['time_ratio'] for a in parents),
                'time_axis_delta_contribution': statistics.mean(a['time_ratio'] - p['time_ratio'] for a, p in zip(metrics, parents)) / 28,
                'size_axis_delta_contribution_pp': (metrics[0]['size_pct'] - parents[0]['size_pct']) / 28,
                'output_byte_delta': metrics[0]['output_bytes'] - parents[0]['output_bytes'],
                'tokens_equal_to_scalar': metrics[0]['tokens_sha256'] == parents[0]['tokens_sha256']})
        groups = {}
        for group in sorted({f['route_group'] for f in files}):
            subset = [f for f in files if f['route_group'] == group]
            groups[group] = {'files': len(subset),
                'time_axis_delta_contribution': sum(f['time_axis_delta_contribution'] for f in subset),
                'size_axis_delta_contribution_pp': sum(f['size_axis_delta_contribution_pp'] for f in subset)}
        result['candidates'].append({'name': name, 'source_sha256': entry['hashes']['parse.rs'],
            'blocks': blocks, 'groups': groups, 'files': sorted(files, key=lambda f: f['size_axis_delta_contribution_pp'])})
    finder_path = folder / 'finder-diagnostics/finder-diagnostics.json'
    if finder_path.exists():
        finder = load(finder_path)
        result['finder'] = {'status': finder['status'], 'totals': finder.get('totals'),
            'coverage_scope': finder['coverage_scope'], 'not_measured': finder['not_measured']}
    endprobe_path = folder / 'endprobe-diagnostics/endprobe.json'
    if endprobe_path.exists():
        ep = load(endprobe_path)
        assert ep['status'] == 'VERIFIED_FINITE_ENDPROBE_DIAGNOSTIC'
        records = ep['records']
        result['endprobe'] = {'status': ep['status'], 'scope': ep['scope'], 'totals': ep['totals'],
            'records': len(records), 'source_sha256': ep['candidate_sha256'],
            'count_limit': 'Additional match/length/backward coverage overlaps and is not a count of bytes saved.'}
    costcache_path = folder / 'costcache-diagnostics/costcache.json'
    if costcache_path.exists():
        cc = load(costcache_path)
        assert cc['status'] == 'VERIFIED_FINITE_COSTCACHE_COUNTS'
        result['costcache'] = {'status': cc['status'], 'scope': cc['scope'], 'totals': cc['totals'],
            'source_sha256': cc['source_sha256'], 'files': len(cc['records'])}
    result['evidence_files_sha256'] = {p.relative_to(folder).as_posix(): hashlib.sha256(p.read_bytes()).hexdigest()
                                      for p in [folder / 'state.json', forward_path, finder_path, endprobe_path, costcache_path] if p.exists()}
    (folder / 'mechanism-analysis.json').write_bytes((json.dumps(result, indent=2) + '\n').encode())
    print(json.dumps({'run_id': result['run_id'], 'forward': None if result['forward'] is None else
        {k: v for k, v in result['forward'].items() if k != 'public_files'},
        'finder': result['finder'], 'endprobe': result['endprobe'], 'costcache': result['costcache'],
        'candidate_groups': {r['name']: r['groups'] for r in result['candidates']}}, indent=2))


if __name__ == '__main__':
    main()
