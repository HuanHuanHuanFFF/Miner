"""B37 same-block whole encoder decomposition from selected total-median reps."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import importlib
import json
import statistics
import sys

sys.dont_write_bytecode = True
ROOT = Path(__file__).resolve().parents[1]
BASE = importlib.import_module('r26-b-tree-pair-cost')
FOLDER = ROOT/'evidence/round26/38227360774/screen-b37/gate'
CANDIDATE = 'r26-b-552-a-no-owner'
FULL = 'r26-b-552-a-flatten'
NAMES = ['public552', 'public552-shadow', CANDIDATE, CANDIDATE+'-shadow', FULL]
KEYS = ['axis_delta', 'parse_numerator_delta', 'encode_numerator_delta', 'incumbent_denominator_delta']


def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def read(block, name):
    path = FOLDER/f'round{block}-{name}.jsonl'
    raw = [json.loads(s) for s in path.read_text().splitlines()]
    meta = next(r for r in raw if r['kind'] == 'meta')
    rows = {}
    for row in raw:
        if row['kind'] == 'file':
            rows[row['file']] = {'input_sha256': row['sha256'], 'raw_bytes': row['raw_bytes'],
                                 'method': BASE.median_rep(row['methods'][name]),
                                 'incumbent': BASE.median_rep(row['methods']['incumbent'])}
    assert len(rows) == 28
    return {'rows': rows, 'axis': statistics.mean(r['method']['total']/r['incumbent']['total'] for r in rows.values()),
            'selected_rep_seconds_sum': {part: sum(r['method'][part] for r in rows.values()) for part in ['total', 'parse', 'encode']},
            'incumbent_median_total_seconds_sum': sum(r['incumbent']['total'] for r in rows.values()),
            'source_sha256': meta['methods'][name]['source_sha256'],
            'binary_sha256': meta['methods'][name]['lib_sha256'],
            'environment': {key: meta[key] for key in ['os', 'arch', 'rustc_version', 'cpu_model', 'cpu_governor', 'benchmark_provenance']},
            'raw_path': path.relative_to(ROOT).as_posix(), 'raw_sha256': sha(path)}


def compare(child, parent, runs, active):
    c, p = runs[child], runs[parent]
    rows = []
    for file, cr in c['rows'].items():
        pr = p['rows'][file]
        assert cr['input_sha256'] == pr['input_sha256']
        cm, pm = cr['method'], pr['method']
        ci, pi = cr['incumbent']['total'], pr['incumbent']['total']
        delta = cm['total']/ci-pm['total']/pi
        dp = (cm['parse']-pm['parse'])/pi
        de = (cm['encode']-pm['encode'])/pi
        denominator = cm['total']*(1/ci-1/pi)
        assert abs(dp+de+denominator-delta) < 1e-11
        rows.append({'file': file, 'input_sha256': cr['input_sha256'], 'actual_A_DP_input': file in active,
                     'child_selected_total_rep': cm, 'parent_selected_total_rep': pm,
                     'child_incumbent_median_total': ci, 'parent_incumbent_median_total': pi,
                     'axis_delta': delta, 'parse_numerator_delta': dp, 'encode_numerator_delta': de,
                     'incumbent_denominator_delta': denominator})
    groups = []
    for label, keep in [('actual_A_DP_inputs', lambda r: r['actual_A_DP_input']),
                        ('non_A_DP_inputs', lambda r: not r['actual_A_DP_input'])]:
        rs = [r for r in rows if keep(r)]
        groups.append({'group': label, 'files': len(rs), **{key: sum(r[key] for r in rs)/28 for key in KEYS}})
    totals = {key: sum(r[key] for r in rows)/28 for key in KEYS}
    assert abs(totals['axis_delta']-(c['axis']-p['axis'])) < 1e-11
    raw_time = {part: c['selected_rep_seconds_sum'][part]-p['selected_rep_seconds_sum'][part] for part in ['total', 'parse', 'encode']}
    assert abs(raw_time['parse']+raw_time['encode']-raw_time['total']) < 1e-11
    return {'child': child, 'parent': parent, 'child_axis': c['axis'], 'parent_axis': p['axis'],
            'relative_axis_change_pct': 100*(c['axis']/p['axis']-1),
            'selected_rep_seconds_sum_delta': raw_time,
            'selected_rep_total_sum_change_pct': 100*(c['selected_rep_seconds_sum']['total']/p['selected_rep_seconds_sum']['total']-1),
            'axis_decomposition': totals, 'groups': groups, 'per_file': rows}


def main():
    receipt = ROOT/'evidence/round26/38226501675/quality-b36-native/diagnostics/r26-b-a-flatten/receipt.json'
    active = {r['file'] for r in json.loads(receipt.read_bytes())['rows'] if r['counts']['dp_calls']}
    blocks = []
    for block in [1, 2]:
        runs = {name: read(block, name) for name in NAMES}
        assert len({json.dumps(r['environment'], sort_keys=True) for r in runs.values()}) == 1
        controls = []
        for name in ['public552', CANDIDATE]:
            a, b = runs[name], runs[name+'-shadow']
            assert a['source_sha256'] == b['source_sha256'] and a['binary_sha256'] == b['binary_sha256']
            controls.append({'name': name, 'primary_axis': a['axis'], 'shadow_axis': b['axis'],
                             'shadow_axis_gap_pct': 100*(b['axis']/a['axis']-1),
                             'shadow_selected_rep_total_sum_gap_pct': 100*(b['selected_rep_seconds_sum']['total']/a['selected_rep_seconds_sum']['total']-1),
                             'same_binary_sha256': a['binary_sha256']})
        pairs = [(child, parent) for child in [CANDIDATE, CANDIDATE+'-shadow', FULL]
                 for parent in ['public552', 'public552-shadow']]
        pairs += [(child, FULL) for child in [CANDIDATE, CANDIDATE+'-shadow']]
        blocks.append({'block': block, 'runs': {name: {key: value for key, value in r.items() if key != 'rows'} for name, r in runs.items()},
                       'same_source_controls': controls, 'comparisons': [compare(c, p, runs, active) for c, p in pairs]})
    output = ROOT/'evidence/round26/route-b/b39-no-owner-paired-cost.json'
    assert not output.exists()
    result = {'status': 'VERIFIED_EXACT_AXIS_DECOMPOSITION_FROM_ACTUAL_TOTAL_MEDIAN_REPS',
              'computed_utc': datetime.now(timezone.utc).isoformat(), 'run_id': '38227360774',
              'active_A_DP_inputs': sorted(active), 'active_receipt_sha256': sha(receipt), 'blocks': blocks,
              'decision': 'STOP_NO_OWNER_AND_FULL_OWNER_LINEAGE_GATE_NO_NEW_RESEARCH',
              'limits': ['Parse/encode components belong to each actual selected median-total rep; independent component medians are not substituted.',
                         'Public axis is mean of per-file total/incumbent ratios, not summed seconds. Both summaries are shown without conflating them.',
                         'Parse, encoder and denominator terms are exact algebra, not isolated DP clocks or causal attribution.',
                         'Same-source/shadow processes share one discovery runner and are not independent confirmations.',
                         'Fixed-denominator numerator terms are diagnosis only, never replacement scoring or proof of a corrected gain.']}
    output.write_text(json.dumps(result, indent=2)+'\n')
    print(json.dumps([{'block': b['block'], 'runs': {name: {'axis': r['axis'], 'seconds': r['selected_rep_seconds_sum']} for name, r in b['runs'].items()},
                       'controls': b['same_source_controls'], 'comparisons': [{k: v for k, v in c.items() if k not in ['per_file', 'groups']} for c in b['comparisons']]} for b in blocks], indent=2))


if __name__ == '__main__':
    main()
