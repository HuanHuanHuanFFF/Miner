"""Exact algebraic split of same-binary timing gaps; no causal attribution claim."""
from pathlib import Path
import argparse
import hashlib
import json
import statistics as st

ROOT = Path(__file__).resolve().parents[1]


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('folder', type=Path)
    ap.add_argument('--parent', required=True)
    ap.add_argument('--output', type=Path, required=True)
    args = ap.parse_args()
    folder = args.folder.resolve()
    state = json.loads((folder / 'state.json').read_bytes())
    inventory = json.loads((folder / 'raw-artifact-files.json').read_bytes())
    result = []
    for block in range(1, state['spec']['screen_blocks'] + 1):
        methods, metas = {}, {}
        for name in (args.parent, args.parent + '-shadow'):
            path = folder / f'round{block}-{name}.jsonl'
            raw = path.read_bytes()
            assert hashlib.sha256(raw).hexdigest() == inventory['files'][path.name]['sha256']
            data = [json.loads(line) for line in raw.splitlines()]
            meta = data[0]
            assert meta['measured_rounds'] == 11 and meta['warmup_rounds'] == 1
            metas[name] = meta
            methods[name] = {}
            for f in data:
                if f['kind'] != 'file':
                    continue
                med = {}
                for method in (name, 'incumbent'):
                    v = f['methods'][method]
                    assert v['deterministic'] and not v['errors']
                    times = [x['total_s'] for x in v['reps'] if x['phase'] == 'measured']
                    assert len(times) == 11
                    med[method] = st.median(times)
                methods[name][f['file']] = {'time': med[name], 'incumbent': med['incumbent'],
                                           'input': f['sha256'], 'tokens': f['methods'][name]['tokens_sha256'],
                                           'output': f['methods'][name]['output_sha256']}
        parent, shadow = args.parent, args.parent + '-shadow'
        assert metas[parent]['methods'][parent]['lib_sha256'] == metas[shadow]['methods'][shadow]['lib_sha256']
        assert metas[parent]['methods']['incumbent']['lib_sha256'] == metas[shadow]['methods']['incumbent']['lib_sha256']
        files = []
        for file, a in methods[parent].items():
            b = methods[shadow][file]
            assert all(a[k] == b[k] for k in ('input', 'tokens', 'output'))
            delta = b['time'] / b['incumbent'] - a['time'] / a['incumbent']
            candidate_part = 0.5 * (b['time'] - a['time']) * (1 / a['incumbent'] + 1 / b['incumbent'])
            incumbent_part = 0.5 * (a['time'] + b['time']) * (1 / b['incumbent'] - 1 / a['incumbent'])
            assert abs(delta - candidate_part - incumbent_part) < 1e-12
            files.append({'file': file, 'parent_total_s': a['time'], 'shadow_total_s': b['time'],
                          'parent_incumbent_s': a['incumbent'], 'shadow_incumbent_s': b['incumbent'],
                          'axis_delta_contribution': delta / 28, 'candidate_part': candidate_part / 28,
                          'incumbent_part': incumbent_part / 28})
        assert len(files) == 28
        x = st.mean(a['time'] / a['incumbent'] for a in methods[parent].values())
        result.append({'block': block, 'same_binary_sha256': metas[parent]['methods'][parent]['lib_sha256'],
                       'parent_axis': x, 'axis_gap_relative_pct': 100 * sum(f['axis_delta_contribution'] for f in files) / x,
                       'candidate_time_component_pct': 100 * sum(f['candidate_part'] for f in files) / x,
                       'incumbent_time_component_pct': 100 * sum(f['incumbent_part'] for f in files) / x,
                       'per_file': sorted(files, key=lambda f: abs(f['axis_delta_contribution']), reverse=True)})
    output = {'status': 'VERIFIED_ALGEBRAIC_DECOMPOSITION_NOT_CAUSAL_DIAGNOSIS', 'run_id': state['run_id'],
              'parent': args.parent, 'blocks': result,
              'formula': 'delta(T/R) = .5 deltaT(1/Ra+1/Rb) + .5(Ta+Tb)delta(1/R)',
              'limits': ['Different paired processes in the same outer block; not simultaneous counters.',
                         'Both candidate and incumbent timings vary. The split is exact algebra, not proof of CPU or scheduling cause.',
                         'No corrected official score is substituted for the actual raw protocol measurements.']}
    args.output.write_bytes((json.dumps(output, indent=2) + '\n').encode())
    print(json.dumps([{k: v for k, v in row.items() if k != 'per_file'} for row in result], indent=2))


if __name__ == '__main__':
    main()
