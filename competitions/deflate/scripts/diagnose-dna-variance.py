"""Replay the DNA score instability from immutable evidence; no benchmark runs."""
from pathlib import Path
import argparse
import json
import hashlib
import statistics as st
from round10_payability import load_flat_rows, load_official_scorer, validate_policy_for_replay

ROOT = Path(__file__).resolve().parents[1]
CAPTURE = ROOT / 'evidence/round17/official-calibration-20261010'
NAME = 'r14-514-dna-nofold'


def analyze(sc, front, pair, replay):
    folders = [('old', ROOT / 'evidence/round14/37901182218/dna-j/gate'),
               ('A', ROOT / 'evidence/round17/37949768851/retest-a/gate'),
               ('B', ROOT / 'evidence/round17/37949875804/retest-b/gate')]
    measurements, control_diffs, audit, blocks = [], [], {}, []
    identities = {}
    for label, folder in folders:
        state = json.loads((folder / 'state.json').read_bytes())
        inventory = json.loads((folder / 'raw-artifact-files.json').read_bytes())['files']
        for b in range(1, state['spec']['screen_blocks'] + 1):
            current = {}
            for name in (NAME, 'public514', 'public514-shadow'):
                p = folder / f'round{b}-{name}.jsonl'
                h = hashlib.sha256(p.read_bytes()).hexdigest()
                assert h == inventory[p.name]['sha256']
                audit[str(p.relative_to(ROOT))] = h
                raw = [json.loads(v) for v in p.read_text().splitlines()]
                meta, fs = raw[0], [v for v in raw if v['kind'] == 'file']
                assert len(fs) == 28 and meta['measured_rounds'] == 11
                record = {'run': label, 'block': b, 'name': name,
                          'cpu': meta['cpu_model'], 'governor': meta['cpu_governor'],
                          'binary': meta['methods'][name]['lib_sha256'],
                          'started_at_unix': meta['started_at_unix'],
                          'cpus_requested': meta['benchmark_provenance']['cpus'],
                          'reported_affinity': meta['benchmark_provenance']['process_affinity'], 'files': {}}
                for f in fs:
                    stats = {}
                    for method in (name, 'incumbent'):
                        m = f['methods'][method]
                        assert m['deterministic'] and not m['errors']
                        reps = [v for v in m['reps'] if v['phase'] == 'measured']
                        assert len(reps) == 11
                        stats[method] = {k: st.median(v[k] for v in reps) for k in ('total_s', 'time_s', 'encode_s')}
                        vals = [v['total_s'] for v in reps]
                        stats[method]['within_process_max_over_min_pct'] = 100 * (max(vals) / min(vals) - 1)
                    key = (meta['methods'][name]['source_sha256'], f['file'])
                    identity = (f['sha256'], f['methods'][name]['tokens_sha256'], f['methods'][name]['output_sha256'])
                    assert identities.setdefault(key, identity) == identity
                    record['files'][f['file']] = {
                        'ratio': stats[name]['total_s'] / stats['incumbent']['total_s'],
                        'candidate': stats[name], 'incumbent': stats['incumbent']}
                record['coordinate'] = st.mean(v['ratio'] for v in record['files'].values())
                expected = next(m['time'] for m in state['metrics'] if m['candidate'] == name and m['round'] == b)
                assert abs(expected - record['coordinate']) < 1e-12
                current[name] = record
                measurements.append(record)
            a, s, c = current['public514'], current['public514-shadow'], current[NAME]
            diff = s['coordinate'] - a['coordinate']
            contributions = [{'file': f,
                              'coordinate_delta': (s['files'][f]['ratio'] - a['files'][f]['ratio']) / 28,
                              'anchor_ratio': a['files'][f]['ratio'], 'shadow_ratio': s['files'][f]['ratio'],
                              'candidate_time_change_pct': 100 * (s['files'][f]['candidate']['total_s'] / a['files'][f]['candidate']['total_s'] - 1),
                              'incumbent_time_change_pct': 100 * (s['files'][f]['incumbent']['total_s'] / a['files'][f]['incumbent']['total_s'] - 1)}
                             for f in a['files']]
            assert abs(sum(v['coordinate_delta'] for v in contributions) - diff) < 1e-12
            control_diffs.append({'run': label, 'block': b,
                                  'same_binary': a['binary'] == s['binary'],
                                  'shadow_coordinate_vs_anchor_pct': 100 * (s['coordinate'] / a['coordinate'] - 1),
                                  'seconds_between_starts': s['started_at_unix'] - a['started_at_unix'],
                                  'top_contributions': sorted(contributions, key=lambda v: abs(v['coordinate_delta']), reverse=True)[:6]})
            blocks.append({'run': label, 'block': b, 'cpu': c['cpu'],
                           'candidate_coordinate': c['coordinate'], 'anchor_coordinate': a['coordinate'],
                           'shadow_coordinate': s['coordinate'],
                           'candidate_over_anchor': c['coordinate'] / a['coordinate'],
                           'candidate_over_shadow': c['coordinate'] / s['coordinate']})

    def score_at(x):
        point = sc.Point('DNA', x, pair[0]['size_pct'])
        f = sc.pareto_front(front + [point])
        w = sc.local_global_improvement_space_log_weights(f)
        o = sorted(f, key=lambda p: p.time_s)
        i = next((i for i, p in enumerate(o) if p.name == 'DNA'), None)
        result = {'time': x, 'pool_pct': 100 * w.get('DNA', 0),
                  'removed_frontier_ids': [p.name for p in front if p.name not in w]}
        if i is not None:
            result.update(neighbors=[{'id': p.name, 'time': p.time_s, 'size_pct': p.ratio_pct}
                                     for p in o[max(0, i - 1):i + 2]],
                          local_coefficient=sc.local_coefficients(o, 2, 0)['DNA'],
                          global_coefficient=sc.global_coefficients(o, 2, 0)['DNA'],
                          improvement_factor=sc.improvement_factors(o, incremental=True, logarithmic=True)['DNA'])
        return result

    left = next(p for p in front if p.name == '533')
    right = next(p for p in front if p.name == '539')
    eps = 1e-10
    edges = [score_at(left.time_s - eps), score_at(left.time_s + eps),
             score_at(right.time_s - eps), score_at(right.time_s + eps)]
    assert edges[0]['pool_pct'] < 1 and edges[1]['pool_pct'] > 10
    assert edges[2]['pool_pct'] > 10 and edges[3]['pool_pct'] == 0
    groups = {}
    for label in ('old', 'A', 'B', 'new-A-and-B'):
        selected = [v for v in blocks if v['run'] == label or label == 'new-A-and-B' and v['run'] in ('A', 'B')]
        groups[label] = {}
        for k in ('candidate_coordinate', 'anchor_coordinate', 'shadow_coordinate', 'candidate_over_anchor', 'candidate_over_shadow'):
            vs = [v[k] for v in selected]
            groups[label][k] = {'min': min(vs), 'max': max(vs), 'mean': st.mean(vs), 'max_over_min_pct': 100 * (max(vs) / min(vs) - 1)}
    # File contributions to candidate normalized-time span on the SAME A runner.
    candidates = [v for v in measurements if v['name'] == NAME and v['run'] == 'A']
    low, high = min(candidates, key=lambda v: v['coordinate']), max(candidates, key=lambda v: v['coordinate'])
    file_deltas = [{'file': f, 'coordinate_delta': (high['files'][f]['ratio'] - low['files'][f]['ratio']) / 28,
                   'low_block': low['block'], 'high_block': high['block'],
                   'candidate_total_change_pct': 100 * (high['files'][f]['candidate']['total_s'] / low['files'][f]['candidate']['total_s'] - 1),
                   'incumbent_total_change_pct': 100 * (high['files'][f]['incumbent']['total_s'] / low['files'][f]['incumbent']['total_s'] - 1),
                   'low': low['files'][f], 'high': high['files'][f]} for f in low['files']]
    file_deltas.sort(key=lambda v: abs(v['coordinate_delta']), reverse=True)
    result = {'replay': replay, 'scoring_edges': edges,
              'high_share_interval': {'lower_exclusive': left.time_s, 'upper_exclusive': right.time_s,
                                      'relative_width_pct': 100 * (right.time_s / left.time_s - 1)},
              'blocks': blocks, 'coordinate_spreads': groups, 'same_source_control_differences': control_diffs,
              'same_A_runner_candidate_span_files': file_deltas,
              'all_input_and_output_hashes_identical_for_each_source': True,
              'raw_evidence_sha256': audit,
              'limits': ['Captured evidence identifies scoring discontinuity and measured noise, not physical cause of every timing deviation.',
                         'Requested cpus=0; driver provenance records parent affinity before the child cgroup. Multiple CPUs in that field are not evidence of failed child pinning. Child actual affinity was not captured.',
                         'Same-source controls have separate compiled artifact names; binary equality is checked explicitly, not assumed.',
                         'No submitted Rust/Lean, official scorer, or original benchmark configuration was modified. No deliberate timing delay.']}
    dest = ROOT / 'evidence/round17/dna-variance-diagnosis.json'
    dest.write_bytes((json.dumps(result, indent=2) + '\n').encode())
    print(json.dumps({'high_share_interval': result['high_share_interval'], 'edges': edges,
                      'coordinate_spreads': groups, 'controls': [{k: v for k, v in d.items() if k != 'top_contributions'} for d in control_diffs],
                      'candidate_span_top_files': [{k: v for k, v in d.items() if k not in ('low', 'high')} for d in file_deltas[:7]],
                      'A2_control_top_files': next(d['top_contributions'] for d in control_diffs if d['run'] == 'A' and d['block'] == 2)}, indent=2))


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--check-stability', action='store_true')
    ap.add_argument('--analyze', action='store_true')
    args = ap.parse_args()
    comp, context, rows = load_flat_rows(CAPTURE)
    sc = load_official_scorer()
    validate_policy_for_replay(comp['policy'], rows, sc)
    front = [sc.Point(r['id'], r['metrics']['balanced_time_ratio'],
                      r['metrics']['mean_file_compression_pct']) for r in rows
             if (r.get('score') or {}).get('on_frontier')]
    saved = json.loads((ROOT / 'evidence/round17/formal-calibration-backtest.json').read_bytes())
    dna = next(c for c in saved['cases'] if c['candidate'] == 'r14-514-dna-nofold')
    pair = []
    for anchor in ('public514', 'public514-shadow'):
        o = next(v for v in dna['current_new_only'][anchor]['observations']
                 if v['run_id'] == '37949768851' and v['block'] == 2)
        point = sc.Point('__replay__', o['time'], o['size_pct'])
        share = 100 * sc.local_global_improvement_space_log_weights(sc.pareto_front(front + [point])).get(point.name, 0)
        assert abs(share - o['share_pct']) < 1e-9
        pair.append({'anchor': anchor, 'time': point.time_s, 'size_pct': point.ratio_pct, 'pool_pct': share})
    assert pair[0]['size_pct'] == pair[1]['size_pct']
    time_gap = 100 * (max(o['time'] for o in pair) / min(o['time'] for o in pair) - 1)
    share_gap = abs(pair[0]['pool_pct'] - pair[1]['pool_pct'])
    result = {'snapshot': context, 'same_candidate_same_block': True,
              'observations': pair, 'relative_time_gap_pct': time_gap,
              'share_gap_percentage_points': share_gap,
              'unstable_under_control_swap': time_gap < 1 and share_gap > 10,
              'scope': 'Minimal scorer replay: exact candidate/block/size/frontier unchanged; only same-source anchor choice differs. Red criterion is diagnostic, not an official rule.'}
    print(json.dumps(result, indent=2))
    if args.analyze:
        analyze(sc, front, pair, result)
    if args.check_stability and result['unstable_under_control_swap']:
        raise SystemExit(1)


if __name__ == '__main__':
    main()
