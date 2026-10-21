"""B23 original total-axis decomposition with actual selected total-median rep parts."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json
import statistics

ROOT = Path(__file__).resolve().parents[1]
FOLDER = ROOT/'evidence/round26/38217538333/screen-b23/gate'
CANDIDATE = 'r26-b-552-tree-prefix'
NAMES = ['public552', 'public552-shadow', CANDIDATE, CANDIDATE+'-shadow']


def sha(raw):
    return hashlib.sha256(raw).hexdigest()


def median_rep(method):
    reps = [r for r in method['reps'] if r['phase'] == 'measured']
    assert len(reps) == 11 and all(not method['errors'] for _ in [0])
    chosen = sorted(reps, key=lambda r: r['total_s'])[5]
    assert chosen['total_s'] == statistics.median(r['total_s'] for r in reps)
    assert abs(chosen['time_s']+chosen['encode_s']-chosen['total_s']) < 1e-12
    return {'total': chosen['total_s'], 'parse': chosen['time_s'], 'encode': chosen['encode_s'],
            'selected_order_index': chosen['order_index']}


def read(block, name):
    path = FOLDER/f'round{block}-{name}.jsonl'
    rows = [json.loads(line) for line in path.read_text().splitlines()]
    meta = next(r for r in rows if r['kind']=='meta')
    result = {}
    for r in rows:
        if r['kind']=='file':
            result[r['file']] = {'input_sha256': r['sha256'], 'raw_bytes': r['raw_bytes'],
                                 'method': median_rep(r['methods'][name]), 'incumbent': median_rep(r['methods']['incumbent'])}
    assert len(result) == 28
    axis = statistics.mean(r['method']['total']/r['incumbent']['total'] for r in result.values())
    return {'rows': result, 'axis': axis, 'source_sha256': meta['methods'][name]['source_sha256'],
            'binary_sha256': meta['methods'][name]['lib_sha256'], 'raw_path': path.relative_to(ROOT).as_posix(),
            'raw_sha256': sha(path.read_bytes())}


def main():
    active_receipt = ROOT/'evidence/round26/38215726866/tree-b19-native/diagnostics/r26-b-tree-edge/receipt.json'
    active = {r['file'] for r in json.loads(active_receipt.read_bytes())['rows'] if r['counts']['finder_calls']}
    blocks = []
    for block in [1, 2]:
        runs = {name: read(block, name) for name in NAMES}
        same_sources = []
        for name in ['public552', CANDIDATE]:
            a, b = runs[name], runs[name+'-shadow']
            assert a['source_sha256'] == b['source_sha256'] and a['binary_sha256'] == b['binary_sha256']
            same_sources.append({'name': name, 'primary_axis': a['axis'], 'shadow_axis': b['axis'],
                                 'same_binary_sha256': a['binary_sha256'], 'shadow_gap_pct': 100*(b['axis']/a['axis']-1)})
        comparisons = []
        for child in [CANDIDATE, CANDIDATE+'-shadow']:
            for parent in ['public552', 'public552-shadow']:
                c, p = runs[child], runs[parent]
                rows = []
                for file, cr in c['rows'].items():
                    pr = p['rows'][file]
                    assert cr['input_sha256'] == pr['input_sha256']
                    cm, pm, ci, pi = cr['method'], pr['method'], cr['incumbent']['total'], pr['incumbent']['total']
                    dp = (cm['parse']-pm['parse'])/pi
                    de = (cm['encode']-pm['encode'])/pi
                    denom = cm['total']*(1/ci-1/pi)
                    difference = cm['total']/ci-pm['total']/pi
                    assert abs(dp+de+denom-difference) < 1e-11
                    rows.append({'file': file, 'input_sha256': cr['input_sha256'], 'actual_A_finder_input': file in active,
                                 'candidate_total_seconds': cm['total'], 'parent_total_seconds': pm['total'],
                                 'candidate_selected_total_rep': cm, 'parent_selected_total_rep': pm,
                                 'candidate_incumbent_median_total': ci, 'parent_incumbent_median_total': pi,
                                 'axis_delta': difference, 'parse_numerator_delta': dp, 'encode_numerator_delta': de,
                                 'incumbent_denominator_delta': denom})
                groups = []
                for label, choose in [('actual_A_inputs', lambda r: r['actual_A_finder_input']), ('non_A_inputs', lambda r: not r['actual_A_finder_input'])]:
                    rs = [r for r in rows if choose(r)]
                    groups.append({'group': label, 'files': len(rs),
                                   **{k: sum(r[k] for r in rs)/28 for k in ['axis_delta', 'parse_numerator_delta', 'encode_numerator_delta', 'incumbent_denominator_delta']}})
                assert abs(sum(g['axis_delta'] for g in groups)-(c['axis']-p['axis'])) < 1e-11
                comparisons.append({'candidate_entry': child, 'parent_entry': parent, 'candidate_axis': c['axis'], 'parent_axis': p['axis'],
                                    'relative_axis_change_pct': 100*(c['axis']/p['axis']-1), 'groups': groups, 'per_file': rows})
        blocks.append({'block': block, 'runs': {name: {k:v for k,v in run.items() if k!='rows'} for name, run in runs.items()},
                       'same_source_controls': same_sources, 'comparisons': comparisons})
    result = {'status': 'VERIFIED_ORIGINAL_TOTAL_AXIS_ALGEBRA_USING_ACTUAL_MEDIAN_TOTAL_REP_COMPONENTS',
              'computed_utc': datetime.now(timezone.utc).isoformat(), 'run_id': '38217538333', 'active_A_inputs': sorted(active),
              'blocks': blocks, 'decision': 'STOP_EXACT_U16_GATE; both main blocks and candidate shadows are slower. Preserve fixed31 packed representation as separate actual-maintenance experiment, never inherit the U16 timing or gate.',
              'limits': ['Per-file medians of total_s select an actual measured rep; its parse/encode parts sum exactly to that total. Independent parse/encode medians are not substituted.',
                         'Numerator and incumbent-denominator terms are exact algebra, not causal attribution or corrected scores.',
                         'Active A input grouping uses same exact parent graph contexts; observed parse differences include any compiler/layout/environment effects.',
                         'No same-run isolated finder timer exists in this original protocol, so finder milliseconds cannot be separately measured by these rows.',
                         'Main/shadow are same-source controls within discovery, not new independent confirmations or stable success probabilities.'],
              'input_hashes': {active_receipt.relative_to(ROOT).as_posix(): sha(active_receipt.read_bytes())}}
    output = ROOT/'evidence/round26/route-b/b28-tree-pair-cost-feedback.json'
    assert not output.exists()
    output.write_text(json.dumps(result, indent=2)+'\n')
    print(json.dumps([{'block': b['block'], 'same_source_controls': b['same_source_controls'],
                       'main': next({k:v for k,v in c.items() if k!='per_file'} for c in b['comparisons'] if c['candidate_entry']==CANDIDATE and c['parent_entry']=='public552')} for b in blocks], indent=2))


if __name__ == '__main__':
    main()
