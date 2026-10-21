"""Attribute frozen confirmation axes to actual files without averaging coordinates into scores."""
from pathlib import Path
from datetime import datetime, timezone
import argparse, hashlib, json, statistics as st

ROOT = Path(__file__).resolve().parents[1]
E = ROOT / 'evidence/round24'


def read(p):
    return json.loads(p.read_bytes())


def digest(p):
    return hashlib.sha256(p.read_bytes()).hexdigest()


def dist(v):
    return {'n': len(v), 'minimum': min(v), 'median': st.median(v), 'maximum': max(v)}


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--output', required=True, type=Path)
    a = ap.parse_args()
    assert not a.output.exists()
    plan = read(E / 'confirm-final-plan.json')
    names = plan['candidates']
    data, raw_audit, axes = [], [], []
    for run, batch in [('38106900587', 'confirm-final-1'), ('38106909000', 'confirm-final-2'), ('38106920250', 'confirm-final-3')]:
        folder = E / run / batch / 'gate'
        state = read(folder / 'state.json')
        inv = read(folder / 'raw-artifact-files.json')['files']
        for block in [1, 2, 3]:
            for name in names:
                path = folder / f'round{block}-{name}.jsonl'
                expected = inv[path.name]
                assert path.stat().st_size == expected['bytes'] and digest(path) == expected['sha256']
                items = [json.loads(line) for line in path.read_text().splitlines()]
                meta = items[0]
                assert meta['methods'][name]['source_sha256'] == plan['files'][name]['parse.rs']
                assert meta['measured_rounds'] == 11 and meta['warmup_rounds'] == 1
                files = [r for r in items if r['kind'] == 'file']
                assert len(files) == 28
                block_rows = []
                for row in files:
                    c, inc = row['methods'][name], row['methods']['incumbent']
                    assert c['deterministic'] and inc['deterministic'] and not c['errors'] and not inc['errors']
                    reps = [r for r in c['reps'] if r['phase'] == 'measured']
                    irep = [r for r in inc['reps'] if r['phase'] == 'measured']
                    assert len(reps) == len(irep) == 11
                    assert all(abs(r['total_s'] - r['time_s'] - r['encode_s']) < 1e-9 for r in reps + irep)
                    total, itotal = st.median(r['total_s'] for r in reps), st.median(r['total_s'] for r in irep)
                    r = {'candidate': name, 'run_id': run, 'block': block, 'file': row['file'], 'input_sha256': row['sha256'], 'raw_bytes': row['raw_bytes'], 'output_bytes': c['output_bytes'], 'output_sha256': c['output_sha256'], 'tokens': c['tokens'], 'tokens_sha256': c['tokens_sha256'], 'total_s': total, 'incumbent_total_s': itotal, 'parse_s': st.median(x['time_s'] for x in reps), 'encode_s': st.median(x['encode_s'] for x in reps), 'per_rep_parse_fraction_median': st.median(x['time_s'] / x['total_s'] for x in reps), 'time_ratio': total / itotal, 'axis_contribution': total / itotal / 28, 'size_axis_contribution_pp': 100 * c['output_bytes'] / row['raw_bytes'] / 28}
                    block_rows.append(r)
                axis = sum(r['axis_contribution'] for r in block_rows)
                sm = next(m for m in state['metrics'] if m['candidate'] == name and m['round'] == block)
                assert abs(axis - sm['time']) < 1e-12 and abs(sum(r['size_axis_contribution_pp'] for r in block_rows) - sm['size_pct']) < 1e-12
                for r in block_rows:
                    r['fraction_of_time_axis'] = r['axis_contribution'] / axis
                data.extend(block_rows)
                axes.append({'candidate': name, 'run_id': run, 'block': block, 'public_time_axis': axis, 'size_axis_pct': sm['size_pct'], 'sum_file_median_total_s_DIAGNOSTIC_NOT_SCORE': sum(r['total_s'] for r in block_rows)})
                raw_audit.append({'path': path.relative_to(ROOT).as_posix(), **expected})
    summaries = []
    for name in names:
        rows = [r for r in data if r['candidate'] == name]
        files = []
        for filename in sorted({r['file'] for r in rows}):
            rs = [r for r in rows if r['file'] == filename]
            assert len(rs) == 9
            for key in ['input_sha256', 'output_bytes', 'output_sha256', 'tokens', 'tokens_sha256']:
                assert len({r[key] for r in rs}) == 1, (name, filename, key)
            files.append({'file': filename, **{k: rs[0][k] for k in ['raw_bytes', 'output_bytes', 'tokens', 'output_sha256', 'tokens_sha256']}, **{k: dist([r[k] for r in rs]) for k in ['total_s', 'incumbent_total_s', 'parse_s', 'encode_s', 'per_rep_parse_fraction_median', 'time_ratio', 'axis_contribution', 'fraction_of_time_axis']}})
        files.sort(key=lambda r: r['axis_contribution']['median'], reverse=True)
        top = [r['file'] for r in files[:5]]
        top_fraction = [sum(r['fraction_of_time_axis'] for r in rows if r['run_id'] == run and r['block'] == b and r['file'] in top) for run in sorted({r['run_id'] for r in rows}) for b in [1, 2, 3]]
        summaries.append({'candidate': name, 'files_by_measured_axis_contribution': files, 'top5_files': top, 'top5_fraction_of_axis': dist(top_fraction), 'public_time_axis': dist([r['public_time_axis'] for r in axes if r['candidate'] == name])})
    fa, fb = [{r['file']: r for r in s['files_by_measured_axis_contribution']} for s in summaries]
    changes = [{'file': f, 'A_output_bytes': fa[f]['output_bytes'], 'B_output_bytes': fb[f]['output_bytes'], 'B_minus_A_bytes': fb[f]['output_bytes'] - fa[f]['output_bytes'], 'A_tokens': fa[f]['tokens'], 'B_tokens': fb[f]['tokens'], 'tokens_same': fa[f]['tokens_sha256'] == fb[f]['tokens_sha256'], 'output_same': fa[f]['output_sha256'] == fb[f]['output_sha256']} for f in sorted(fa)]
    out = {'status': 'VERIFIED_ORIGINAL_FROZEN_PER_FILE_ATTRIBUTION', 'computed_utc': datetime.now(timezone.utc).isoformat(), 'frozen_files': plan['files'], 'raw_audit': raw_audit, 'main_blocks_per_candidate': 9, 'candidates': summaries, 'A_B_output_differences': changes, 'total_B_minus_A_bytes': sum(r['B_minus_A_bytes'] for r in changes), 'block_axes': axes, 'per_file_observations': data, 'limits': ['Official time axis is mean of per-file median total-time ratios; aggregate wall seconds or parser-only timers are diagnostics.', 'Separate medians of parse and encode are not assumed to add to median total. Fractions use measured repetitions.', 'Same searched public corpus; this attribution creates no new independent blocks, performance result, formal coordinate or private guarantee.']}
    a.output.write_bytes((json.dumps(out, indent=2) + '\n').encode())
    print(json.dumps({'candidates': [{'candidate': s['candidate'], 'top5_files': s['top5_files'], 'top5_fraction_of_axis': s['top5_fraction_of_axis'], 'time_axis': s['public_time_axis']} for s in summaries], 'output_difference': out['total_B_minus_A_bytes'], 'changed_files': [r for r in changes if not r['output_same']]}, indent=2))


if __name__ == '__main__':
    main()
