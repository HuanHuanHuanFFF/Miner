"""Reproduce and decompose captured641same-binary timing disagreements.

No new timing, candidate edits, network, CI, or corrected score is produced.
"""
from pathlib import Path
from datetime import datetime, timezone
import argparse
import csv
import importlib
import json
import statistics as st

M = importlib.import_module('r26-score-map')
ROOT = M.ROOT
OUT = ROOT / 'evidence/round26/measurement-diagnosis'
RUNS = [('38176445754', 'screen-a3'), ('38178081169', 'screen-a5'), ('38179533008', 'screen-a67')]


def median(method):
    reps = [r for r in method['reps'] if r['phase'] == 'measured']
    assert method['deterministic'] and not method['errors'] and len(reps) == 11
    chosen = sorted(reps, key=lambda r: r['total_s'])[5]
    assert abs(chosen['time_s'] + chosen['encode_s'] - chosen['total_s']) < 1e-12
    return {'parse_s': chosen['time_s'], 'encode_s': chosen['encode_s'], 'total_s': chosen['total_s'],
            'order_index': chosen['order_index'], 'reps': reps,
            'total_min_s': min(r['total_s'] for r in reps), 'total_max_s': max(r['total_s'] for r in reps),
            'first3_vs_last3_total_change_pct': 100 * (st.median(r['total_s'] for r in reps[-3:]) / st.median(r['total_s'] for r in reps[:3]) - 1)}


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--symptom-check', action='store_true')
    args = ap.parse_args()
    OUT.mkdir(parents=True, exist_ok=True)
    replay = M.Replay(ROOT / 'evidence/round26/official-route2', ROOT / 'evidence/round26/official-rules-start-live')
    assert replay.context['snapshot_id'] == '29795'
    input_files, runs, pair_rows, candidate_rows = {}, [], [], []
    binary_by_source = {}
    baseline_error = max(abs(replay.initial.get(str(r['id']), {}).get('share_pct', 0) - 100 * (r.get('score') or {}).get('pareto_weight', 0)) for r in replay.rows)
    assert baseline_error < 1e-10
    for run, batch in RUNS:
        folder = ROOT / 'evidence/round26' / run / batch / 'gate'
        state = json.loads((folder / 'state.json').read_bytes())
        ci = json.loads((folder / 'ci-run.json').read_bytes())
        inventory = json.loads((folder / 'raw-artifact-files.json').read_bytes())
        entries = {e['name']: e for e in state['spec']['entries']}
        metrics = {(m['candidate'], m['round']): m for m in state['metrics']}
        measurements = {}
        for (name, block), metric in metrics.items():
            path = folder / f'round{block}-{name}.jsonl'
            expected = inventory['files'][path.name]
            assert M.digest(path) == expected['sha256'] and path.stat().st_size == expected['bytes']
            input_files[path.relative_to(ROOT).as_posix()] = expected
            records = [json.loads(line) for line in path.read_text().splitlines() if line.strip()]
            meta = records[0]
            assert meta['measured_rounds'] == 11 and meta['warmup_rounds'] == 1
            assert meta['methods'][name]['source_sha256'] == entries[name]['hashes']['parse.rs']
            binary_by_source.setdefault(meta['methods'][name]['source_sha256'], set()).add(meta['methods'][name]['lib_sha256'])
            files = {r['file']: r for r in records if r['kind'] == 'file'}
            assert len(files) == 28 and sum(r['raw_bytes'] for r in files.values()) == 15930000
            for file, row in files.items():
                row['chosen'] = {method: median(row['methods'][method]) for method in [name, 'incumbent']}
                assert {r['order_index'] % 2 for r in row['chosen']['incumbent']['reps']} == {1}
                assert {r['order_index'] % 2 for r in row['chosen'][name]['reps']} == {0}
            axis = st.mean(r['chosen'][name]['total_s'] / r['chosen']['incumbent']['total_s'] for r in files.values())
            assert abs(axis - metric['time']) < 1e-12
            measurements[name, block] = {'meta': meta, 'files': files, 'axis': axis}
        contexts = sorted([{'name': name, 'block': block, 'started_at_unix': x['meta']['started_at_unix'],
                            'cpu_model': x['meta']['cpu_model'], 'cpu_governor': x['meta']['cpu_governor'],
                            'methods': x['meta']['methods'], 'benchmark_provenance': x['meta']['benchmark_provenance']}
                           for (name, block), x in measurements.items()], key=lambda r: r['started_at_unix'])
        runrow = {'run_id': run, 'batch': batch, 'ci_status': ci['status'], 'ci_conclusion': ci['conclusion'],
                  'git_sha': state['git_sha'], 'raw_measurements': len(measurements), 'process_order': contexts,
                  'role': state['spec'].get('r18_role', 'discovery'), 'declared_screen_orders': state['spec'].get('screen_orders')}
        runs.append(runrow)
        pairs = [(n, n + '-shadow') for n in entries if n + '-shadow' in entries]
        comparisons = [('same_source', a, b) for a, b in pairs]
        comparisons += [('candidate_vs_parent', 'public641', n) for n, e in entries.items() if not e.get('control')]
        for kind, a, b in comparisons:
            for block in [1, 2]:
                aa, bb = measurements[a, block], measurements[b, block]
                same_source = entries[a]['hashes']['parse.rs'] == entries[b]['hashes']['parse.rs']
                same_binary = aa['meta']['methods'][a]['lib_sha256'] == bb['meta']['methods'][b]['lib_sha256']
                assert aa['meta']['methods']['incumbent']['lib_sha256'] == bb['meta']['methods']['incumbent']['lib_sha256']
                if kind == 'same_source':
                    assert same_source and same_binary
                files, corners = [], {'A_over_A': [], 'B_over_A': [], 'A_over_B': [], 'B_over_B': []}
                for file, ar in aa['files'].items():
                    br = bb['files'][file]
                    assert ar['sha256'] == br['sha256'] and ar['raw_bytes'] == br['raw_bytes']
                    for n1, n2 in [('incumbent', 'incumbent')] + ([(a, b)] if same_source else []):
                        assert all(ar['methods'][n1][k] == br['methods'][n2][k] for k in ['tokens_sha256', 'output_sha256', 'output_bytes'])
                    ac, ai, bc, bi = ar['chosen'][a], ar['chosen']['incumbent'], br['chosen'][b], br['chosen']['incumbent']
                    w = .5 * (1 / ai['total_s'] + 1 / bi['total_s'])
                    parse = (bc['parse_s'] - ac['parse_s']) * w / 28
                    encode = (bc['encode_s'] - ac['encode_s']) * w / 28
                    denom = .5 * (bc['total_s'] + ac['total_s']) * (1 / bi['total_s'] - 1 / ai['total_s']) / 28
                    axis_delta = (bc['total_s'] / bi['total_s'] - ac['total_s'] / ai['total_s']) / 28
                    assert abs(parse + encode + denom - axis_delta) < 1e-12
                    for key, value in zip(corners, [ac['total_s'] / ai['total_s'], bc['total_s'] / ai['total_s'], ac['total_s'] / bi['total_s'], bc['total_s'] / bi['total_s']]):
                        corners[key].append(value)
                    files.append({'file': file, 'input_sha256': ar['sha256'], 'axis_delta': axis_delta,
                                  'parse_relative_pct_contribution': 100 * parse / aa['axis'],
                                  'encode_relative_pct_contribution': 100 * encode / aa['axis'],
                                  'denominator_relative_pct_contribution': 100 * denom / aa['axis'],
                                  'candidate_total_change_pct': 100 * (bc['total_s'] / ac['total_s'] - 1),
                                  'incumbent_total_change_pct': 100 * (bi['total_s'] / ai['total_s'] - 1),
                                  'same_tokens_output': all(ar['methods'][a][k] == br['methods'][b][k] for k in ['tokens_sha256', 'output_sha256', 'output_bytes']),
                                  'A_candidate': ac, 'A_incumbent': ai, 'B_candidate': bc, 'B_incumbent': bi})
                row = {'run_id': run, 'batch': batch, 'block': block, 'comparison_kind': kind,
                       'A': a, 'B': b, 'same_source': same_source, 'same_binary': same_binary,
                       'A_axis': aa['axis'], 'B_axis': bb['axis'], 'axis_gap_pct': 100 * (bb['axis'] / aa['axis'] - 1),
                       'A_started_unix': aa['meta']['started_at_unix'], 'B_started_unix': bb['meta']['started_at_unix'],
                       'process_start_gap_seconds': bb['meta']['started_at_unix'] - aa['meta']['started_at_unix'],
                       'four_corners_DIAGNOSTIC_NOT_SCORES': {k: st.mean(v) for k, v in corners.items()},
                       'components': {k: sum(r[k] for r in files) for k in ['parse_relative_pct_contribution', 'encode_relative_pct_contribution', 'denominator_relative_pct_contribution']},
                       'candidate_sum_total_change_pct': 100 * (sum(r['B_candidate']['total_s'] for r in files) / sum(r['A_candidate']['total_s'] for r in files) - 1),
                       'incumbent_sum_total_change_pct': 100 * (sum(r['B_incumbent']['total_s'] for r in files) / sum(r['A_incumbent']['total_s'] for r in files) - 1),
                       'files': files}
                assert abs(sum(row['components'].values()) - row['axis_gap_pct']) < 1e-10
                (pair_rows if kind == 'same_source' else candidate_rows).append(row)
        # Actual observations only: map each candidate/control measurement with its
        # own paired incumbent, then use primary and shadow anchor views separately.
        anchor = replay.byid['641']['metrics']
        for block in [1, 2]:
            for name, entry in entries.items():
                if not name.startswith('r26-a-641-'):
                    continue
                actual = measurements[name, block]
                public_y = st.mean(100 * row['methods'][name]['output_bytes'] / row['raw_bytes'] for row in actual['files'].values())
                for label in ['public641', 'public641-shadow']:
                    reference = measurements[label, block]
                    ref_y = st.mean(100 * row['methods'][label]['output_bytes'] / row['raw_bytes'] for row in reference['files'].values())
                    x, y = anchor['balanced_time_ratio'] * actual['axis'] / reference['axis'], anchor['mean_file_compression_pct'] * public_y / ref_y
                    term = replay.score([(name, x, y)]).get(name, {})
                    actual.setdefault('projections', []).append({'run_id': run, 'block': block, 'entry_name': name,
                                                                'entry_role': 'control' if entry.get('control') else 'candidate',
                                                                'calibration': label, 'projected_x': x, 'projected_y_pct': y,
                                                                'share_pct': term.get('share_pct', 0)})
        runrow['observed_coordinate_views'] = [p for x in measurements.values() for p in x.get('projections', [])]
    root_symptom = [r for r in pair_rows if r['A'] == 'public641']
    red = any(abs(r['axis_gap_pct']) >= .5 for r in root_symptom)
    if args.symptom_check:
        print(json.dumps({'captured_symptom': 'same-source same-binary public641/shadow axis gap >=0.5%',
                          'verdict': 'RED_OBSERVED' if red else 'GREEN_NOT_OBSERVED',
                          'gaps': [{k: r[k] for k in ['run_id', 'block', 'axis_gap_pct']} for r in root_symptom]}))
        raise SystemExit(1 if red else 0)
    result = {'status': 'VERIFIED_CAPTURED_SAME_BINARY_DISAGREEMENT_AND_COMPONENT_ACCOUNTING',
              'checked_utc': datetime.now(timezone.utc).isoformat(), 'snapshot': replay.context,
              'max_independent_baseline_api_error_pp': baseline_error,
              'red_capable_replay_symptom_detected': red, 'runs': runs, 'same_source_pairs': pair_rows,
              'candidate_vs_parent': candidate_rows,
              'binary_identities_by_source': {k: sorted(v) for k, v in binary_by_source.items()},
              'input_files': input_files,
              'limits': ['Captured raw replay is deterministic and red-capable for the observed disagreement; it does not reproduce the unknown environmental cause on a new runner.',
                         'Actual total-median reps are used for exact component accounting. Components and cross-corners are descriptive, never corrected scores or causal attribution.',
                         'All candidate/control/calibration views retain original roles and paired incumbent; none adds independent confirmation samples.',
                         'Only29795isusedforcurrentprojection; no averagecoordinate or artificialpressure is scored.']}
    M.dump(OUT / 'raw-decomposition-29795.json', result)
    simple = [{k: r[k] for k in ['run_id', 'batch', 'block', 'A', 'B', 'axis_gap_pct', 'components', 'candidate_sum_total_change_pct', 'incumbent_sum_total_change_pct', 'process_start_gap_seconds']} for r in pair_rows]
    print(json.dumps({'root_same_source': [r for r in simple if r['A'] == 'public641'], 'all_same_source': simple}, indent=2))


if __name__ == '__main__':
    main()
