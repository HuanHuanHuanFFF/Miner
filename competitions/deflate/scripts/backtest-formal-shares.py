"""Replay public measurements for previously submitted candidates, excluding self.

No new benchmark, admission replay, submission, wallet operation, or stress offset.
"""
from pathlib import Path
import hashlib
import json
import statistics as st
from round10_payability import load_official_scorer

ROOT = Path(__file__).resolve().parents[1]
OUT = ROOT / 'evidence/round17'
SC = load_official_scorer()
INPUTS = {}
AUDIT = {}


def read(p):
    return json.loads(p.read_bytes())


def digest(p):
    return hashlib.sha256(p.read_bytes()).hexdigest()


def snapshot(path):
    pages = read(ROOT / path)
    ctx = pages[0]['context']
    assert all(p['context']['snapshot_id'] == ctx['snapshot_id'] for p in pages)
    rows = [r for p in pages for r in p['items']]
    points = [SC.Point(r['id'], r['metrics']['balanced_time_ratio'],
                       r['metrics']['mean_file_compression_pct'])
              for r in rows if (r.get('score') or {}).get('on_frontier')]
    weights = SC.local_global_improvement_space_log_weights(SC.pareto_front(points))
    assert max(abs(weights.get(r['id'], 0) - r['score']['pareto_weight'])
               for r in rows if (r.get('score') or {}).get('on_frontier')) < 1e-10
    return ctx, {r['id']: r for r in rows}


def projected_share(rows, own_id, x, y):
    # Retain ALL admitted, in-bounds points: removing the actual submission can
    # uncover a previously dominated accepted point. Keep admission decisions fixed.
    eligible = [r for r in rows.values() if r['id'] != own_id
                and r.get('metrics') and (r.get('admission') or {}).get('admitted')
                and (r.get('bounds') or {}).get('eligible')]
    assert eligible
    if not (0 < x <= 10 and 0 < y <= 40):
        return 0.0
    points = [SC.Point(r['id'], r['metrics']['balanced_time_ratio'],
                       r['metrics']['mean_file_compression_pct']) for r in eligible]
    points.append(SC.Point('__replay__', x, y))
    return 100 * SC.local_global_improvement_space_log_weights(SC.pareto_front(points)).get('__replay__', 0)


def measured(folder, name, block, source):
    p = folder / f'round{block}-{name}.jsonl'
    raw = [json.loads(s) for s in p.read_text().splitlines()]
    meta, fs = raw[0], [v for v in raw if v['kind'] == 'file']
    assert meta['corpus'] == 'corpus-stage1' and len(fs) == 28
    assert sum(f['raw_bytes'] for f in fs) == 15930000
    assert meta['measured_rounds'] == 11 and meta['warmup_rounds'] == 1
    assert meta['methods'][name]['source_sha256'] == digest(ROOT / source / 'parse.rs')
    invpath = folder / 'raw-artifact-files.json'
    if invpath.exists():
        record = read(invpath)['files'][p.name]
        assert digest(p) == record['sha256'] and p.stat().st_size == record['bytes']
    ratios, sizes = [], []
    for f in fs:
        assert INPUTS.setdefault(f['file'], f['sha256']) == f['sha256']
        times = []
        for method in (name, 'incumbent'):
            m = f['methods'][method]
            assert m['deterministic'] and not m['errors']
            values = [v['total_s'] for v in m['reps'] if v['phase'] == 'measured']
            assert len(values) == 11 and min(values) > 0
            times.append(st.median(values))
        ratios.append(times[0] / times[1])
        sizes.append(100 * f['methods'][name]['output_bytes'] / f['raw_bytes'])
    AUDIT[str(p.relative_to(ROOT))] = {'sha256': digest(p), 'legacy_no_download_inventory': not invpath.exists()}
    return st.mean(ratios), st.mean(sizes)


def observations(folder, candidate_path, primary, anchor_id):
    folder = ROOT / folder
    ci = read(folder / 'ci-run.json')
    assert ci['status'] == 'completed'
    if (folder / 'state.json').exists():
        state = read(folder / 'state.json')
        assert state['git_sha'] == ci['headSha'] and state['run_id'] == str(ci['databaseId'])
        es = {e['name']: e for e in state['spec']['entries']}
        name = next(e['name'] for e in es.values() if e['path'] == candidate_path)
        metrics = state['metrics']
        anchors = [primary] + ([primary + '-shadow'] if primary + '-shadow' in es else [])
    else:
        # Round3 receipts predate state/artifact inventories; source hashes and
        # raw repetitions remain verifiable, but no retroactive download claim.
        state = read(folder / 'analysis.json')
        metrics = state['metrics']
        name = 'r3-432-fast3'
        anchors = [primary]
        es = {name: {'path': candidate_path}, primary: {'path': 'references/round3-public-432'}}
    mm = {(m['candidate'], m['round']): m for m in metrics}
    result = []
    for n, b in mm:
        if n != name:
            continue
        x, y = measured(folder, name, b, candidate_path)
        assert abs(x - mm[n, b]['time']) < 1e-12 and abs(y - mm[n, b]['size_pct']) < 1e-12
        for anchor in anchors:
            if (anchor, b) not in mm:
                continue
            ax, ay = measured(folder, anchor, b, es[anchor]['path'])
            result.append({'run_id': str(ci['databaseId']), 'block': b,
                           'anchor_id': anchor_id, 'anchor_name': anchor,
                           'relative_time': x / ax, 'relative_size': y / ay})
    return result


def summary(obs, rows, own_id):
    groups = {}
    for o in obs:
        a = rows[o['anchor_id']]['metrics']
        x, y = a['balanced_time_ratio'] * o['relative_time'], a['mean_file_compression_pct'] * o['relative_size']
        groups.setdefault(o['anchor_name'], []).append({**o, 'time': x, 'size_pct': y,
                                                      'share_pct': projected_share(rows, own_id, x, y)})
    out = {}
    for anchor, entries in groups.items():
        shares = [v['share_pct'] for v in entries]
        runs = sorted({v['run_id'] for v in entries})
        x = st.mean(st.mean(v['time'] for v in entries if v['run_id'] == rid) for rid in runs)
        y = entries[0]['size_pct']
        assert max(abs(v['size_pct'] - y) for v in entries) < 1e-10
        out[anchor] = {'blocks': len(entries), 'independent_runs': len(runs),
                       'min_pct': min(shares), 'median_pct': st.median(shares), 'max_pct': max(shares),
                       'zero_blocks': sum(v == 0 for v in shares), 'ge1pct_blocks': sum(v >= 1 for v in shares),
                       'mean_coordinate': {'time': x, 'size_pct': y, 'share_pct': projected_share(rows, own_id, x, y)},
                       'observations': entries}
    return out


def main():
    current_path = 'evidence/round17/official-calibration-20261010/pareto-pages.json'
    ctx, current = snapshot(current_path)
    cases = [
        ('453', 'r3-432-fast3', 'public432', '432',
         ['evidence/round3/37493517227'], 'evidence/round3/snapshot-23961/pareto-pages.json'),
        ('573', 'r15-550-base-only', 'public550', '550',
         [f'evidence/round15/{rid}/{batch}/gate' for rid, batch in [
             ('37910359897', 'high-f'), ('37913605062', 'range-n'),
             ('37915493157', 'ring-s'), ('37916106579', 'confirm-u')]],
         'evidence/round15/official-confirmation/pareto-pages.json'),
        ('474', 'r5-h16-small-proofopt', 'public299', '299',
         [str(p.parent.relative_to(ROOT)) for p in sorted((ROOT / 'evidence/round6').glob('*/*/gate/state.json'))],
         'evidence/round6/formal-474/pareto-26567.json'),
        (None, 'r14-514-dna-nofold', 'public514', '514',
         ['evidence/round14/37901182218/dna-j/gate',
          'evidence/round17/37949768851/retest-a/gate', 'evidence/round17/37949875804/retest-b/gate'],
         'evidence/round17/official-final/pareto-pages.json')]
    output = {'current_snapshot': ctx, 'current_capture': current_path, 'cases': [],
              'scorer_sha256': digest(ROOT / 'sources/conjectures-optimisation-deflate/validator/scoring/pareto.py'),
              'projection': 'anchor formal axis * candidate public axis / paired anchor public axis; score on the named frozen frontier',
              'known_formal_rows': {fid: current[fid] for fid in ('427', '453', '474', '573')},
              'scope': 'Original public repetitions replayed, no new CI. Same-family transfer except H16/public299 approximate family reference. Historical snapshots preserve original competition context; H16 historical context is post-submission. Current replacement projections remove the same formal ID, retain all other admitted in-bounds points, and hold their admission fixed. No self-anchor, payout guarantee, future success probability, or stress offset. API freshness remains as reported.'}
    for fid, name, anchor, aid, folders, historical_path in cases:
        obs = [o for folder in folders for o in observations(folder, 'candidates/' + name, anchor, aid)]
        hctx, hist = snapshot(historical_path)
        item = {'candidate': name, 'formal_id': fid, 'historical_snapshot': hctx,
                'historical_source': historical_path,
                'historical_all': summary(obs, hist, fid), 'current_all': summary(obs, current, fid)}
        if fid == '573':
            conf = [o for o in obs if o['run_id'] == '37916106579']
            item['historical_confirmation'] = summary(conf, hist, fid)
            item['current_confirmation'] = summary(conf, current, fid)
            saved = read(ROOT / 'evidence/round15/confirm-u-decision.json')['decisions'][0]['calibrations']
            for a, expected in saved.items():
                actual = item['historical_confirmation'][a]['observations']
                assert all(abs(v['share_pct'] / 100 - e) < 1e-12 for v, e in zip(actual, expected['block_pool_fractions']))
        if fid is None:
            item['current_new_only'] = summary([o for o in obs if o['run_id'] != '37901182218'], current, fid)
        if fid:
            m = current[fid]['metrics']
            item['formal_coordinates_on_historical_frontier_pct'] = projected_share(hist, fid, m['balanced_time_ratio'], m['mean_file_compression_pct'])
            if current[fid]['admission']['admitted']:
                back = projected_share(current, fid, m['balanced_time_ratio'], m['mean_file_compression_pct'])
                assert abs(back / 100 - current[fid]['score']['pareto_weight']) < 1e-10
                item['actual_point_reinsertion_verified_pct'] = back
        output['cases'].append(item)
    h453ctx, h453 = snapshot('evidence/round5/frontier-refresh/pareto-pages.json')
    h573ctx, h573 = snapshot('evidence/round16/official-start/pareto-pages.json')
    output['historical_official_examples'] = {
        '453': {'context': h453ctx, 'row': h453['453'], 'source': 'evidence/round5/frontier-refresh/pareto-pages.json'},
        '573': {'context': h573ctx, 'row': h573['573'], 'source': 'evidence/round16/official-start/pareto-pages.json'}}
    output['raw_input_audit'] = AUDIT
    (OUT / 'formal-calibration-backtest.json').write_bytes((json.dumps(output, ensure_ascii=False, indent=2) + '\n').encode())
    for case in output['cases']:
        print(case['candidate'])
        for section in ('historical_all', 'historical_confirmation', 'current_all', 'current_confirmation', 'current_new_only'):
            if section in case:
                print(section, json.dumps({a: {k: v for k, v in s.items() if k != 'observations'} for a, s in case[section].items()}))


if __name__ == '__main__':
    main()
