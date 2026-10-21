"""A19 raw process/repetition audit; no scores or diagnostic correction."""
from pathlib import Path
import datetime as dt
import hashlib
import json
import statistics as st

ROOT = Path(__file__).resolve().parents[1]
FOLDER = ROOT / 'evidence/round26/38224543411/screen-a19/gate'
OUT = ROOT / 'evidence/round26/route-a/a19-process-audit.json'

def sha(p):
    return hashlib.sha256(p.read_bytes()).hexdigest()

def summary(values):
    return {'min': min(values), 'median': st.median(values), 'max': max(values),
            'relative_range_pct': 100 * (max(values) - min(values)) / st.median(values)}

def describe(row, name):
    reps = [r for r in row['methods'][name]['reps'] if r['phase'] == 'measured']
    assert len(reps) == 11
    return {field: summary([r[field] for r in reps]) for field in ('time_s', 'encode_s', 'total_s')}

def main():
    inventory = json.loads((FOLDER / 'raw-artifact-files.json').read_bytes())['files']
    docs = {}
    processes = []
    inputs = {}
    for p in FOLDER.glob('round*-*.jsonl'):
        assert sha(p) == inventory[p.name]['sha256']
        records = [json.loads(s) for s in p.read_text().splitlines()]
        meta = records[0]
        name = next(n for n in meta['methods'] if n != 'incumbent')
        block = int(p.name[5])
        rows = [r for r in records if r['kind'] == 'file']
        assert len(rows) == 28
        for row in rows:
            for n, parity in [('incumbent', 1), (name, 0)]:
                assert {r['order_index'] % 2 for r in row['methods'][n]['reps']} == {parity}
        docs[name, block] = {'meta': meta, 'rows': {r['file']: r for r in rows}}
        processes.append({'name': name, 'block': block,
                          'started_at_unix': meta['started_at_unix'],
                          'started_at_utc': dt.datetime.fromtimestamp(meta['started_at_unix'], dt.timezone.utc).isoformat(),
                          'provenance': meta['benchmark_provenance'],
                          'candidate_binary_sha256': meta['methods'][name]['lib_sha256'],
                          'incumbent_binary_sha256': meta['methods']['incumbent']['lib_sha256'],
                          'file_order': [r['file'] for r in rows]})
        inputs[p.relative_to(ROOT).as_posix()] = inventory[p.name]
    comparisons = []
    for a in ('public658', 'r26-a-658-safe-word-offsets'):
        b = a + '-shadow'
        for block in (1, 2):
            da, db = docs[a, block], docs[b, block]
            assert da['meta']['methods'][a]['lib_sha256'] == db['meta']['methods'][b]['lib_sha256']
            files = []
            for f, ra in da['rows'].items():
                rb = db['rows'][f]
                assert ra['sha256'] == rb['sha256']
                for x, y in [(a, b), ('incumbent', 'incumbent')]:
                    for k in ('tokens_sha256', 'output_sha256'):
                        assert ra['methods'][x][k] == rb['methods'][y][k]
                stages = {}
                for role, x, y in [('candidate', a, b), ('incumbent', 'incumbent', 'incumbent')]:
                    sa, sb = describe(ra, x), describe(rb, y)
                    stages[role] = {}
                    for field in sa:
                        stages[role][field] = {'A': sa[field], 'B': sb[field],
                            'B_to_A_median_pct': 100 * (sb[field]['median'] / sa[field]['median'] - 1),
                            'nonoverlap': 'B_all_lower' if sb[field]['max'] < sa[field]['min'] else
                                          'B_all_higher' if sb[field]['min'] > sa[field]['max'] else 'overlap'}
                files.append({'file': f, 'stages': stages})
            aggregate = {}
            for role in ('candidate', 'incumbent'):
                aggregate[role] = {}
                for field in ('time_s', 'encode_s', 'total_s'):
                    s = [r['stages'][role][field] for r in files]
                    aggregate[role][field] = {
                        'median_file_B_to_A_pct': st.median(r['B_to_A_median_pct'] for r in s),
                        'nonoverlap_lower_count': sum(r['nonoverlap'] == 'B_all_lower' for r in s),
                        'nonoverlap_higher_count': sum(r['nonoverlap'] == 'B_all_higher' for r in s),
                        'median_within_A_range_pct': st.median(r['A']['relative_range_pct'] for r in s),
                        'median_within_B_range_pct': st.median(r['B']['relative_range_pct'] for r in s)}
            same_direction = sum(r['stages']['candidate']['encode_s']['B_to_A_median_pct'] *
                                 r['stages']['incumbent']['encode_s']['B_to_A_median_pct'] > 0 for r in files)
            comparisons.append({'A': a, 'B': b, 'block': block,
                                'B_minus_A_started_seconds': db['meta']['started_at_unix'] - da['meta']['started_at_unix'],
                                'candidate_and_incumbent_encoder_same_sign_files': same_direction,
                                'aggregate': aggregate, 'files': files})
    report = {'status': 'VERIFIED_EXISTING_RAW_REPETITIONS_NO_CAUSAL_ATTRIBUTION',
              'run_id': '38224543411', 'inputs': inputs,
              'processes_chronological': sorted(processes, key=lambda x: x['started_at_unix']),
              'same_source_comparisons': comparisons,
              'interpretation_limits': [
                  'Stage medians here diagnose distribution shifts only; original score uses total-median selected repetition.',
                  'Every process measures incumbent first and candidate second on every repetition; reverse blocks reverse process order only.',
                  'Driver affinity metadata does not establish actual benchmark-engine affinity/cgroup or per-call CPU.',
                  'No frequency, migration, ASLR, address, cache, or host-noise cause is identified.',
                  'No corrected timing, score projection, or independent confirmation is generated.']}
    OUT.write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps({'process_order': [{k:p[k] for k in ('name','block','started_at_utc')} for p in report['processes_chronological']],
                      'summary': [{k:c[k] for k in ('A','block','B_minus_A_started_seconds','candidate_and_incumbent_encoder_same_sign_files','aggregate')} for c in comparisons]}, indent=2))

if __name__ == '__main__':
    main()
