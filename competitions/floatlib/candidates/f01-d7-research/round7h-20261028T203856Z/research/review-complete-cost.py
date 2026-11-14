"""Independent read-only reconstruction from 64 original DOT_SAMPLE logs.

Does not import D's parser, rerun native code, or treat finite checks as proofs.
Writes only this research role's review receipt.
"""
from pathlib import Path
from collections import defaultdict
from statistics import median
import datetime
import hashlib
import json
import math

HERE = Path(__file__).resolve().parent
ROUND = HERE.parent
ARTIFACT = ROUND / 'ci-runs/40804860824/download-a29c9d41975b4c67b67aefb0158b1440'
SUMMARY = ROUND / 'development-dot-cost/timeout-review/full-408048-comparison.json'
SOURCES = {
    'original': '5bf2a8893b01a5ed44393e80065fbd91e9b3686133e9ddd5d4dfb633379d4d2a',
    'tail': 'e50bf8769d0bef3cc7883d9c1285fd26439282d7c1fd8c141cb84073f90a7f78',
}
ORDER = ['exact', 'eager', 'eager', 'exact', 'exact', 'lazy', 'lazy', 'exact']


def digest(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def main():
    summary = json.loads(SUMMARY.read_bytes())
    assert summary['status'] == 'COMPLETE_EXPLORATORY_NUMERIC_ONLY'
    assert summary['source_hashes'] == SOURCES
    observations = {x['source_sha256']: x for x in summary['observed_runtime_results']}
    reconstructed, reviewed_logs = {}, []
    sample_count = 0
    for role, source in SOURCES.items():
        result_path = ARTIFACT / observations[source]['path']
        body = json.loads(result_path.read_bytes())
        assert body['source_sha256'] == source and body['complete'] is True
        assert len(body['runs']) == 32
        native = body['native_oracle']
        assert body['native_oracle_exit_code'] == 0
        assert native['dots'] == 148 and native['word_rounds'] == 1049
        assert native['all_complete_words_match'] and native['all_expected_accept_miss_match']
        reconstructed[role] = {}
        for run in body['runs']:
            group, boundary, order, variant = str(run['group']), run['boundary'], run['order'], run['variant']
            assert run['exit_code'] == 0 and ORDER[order] == variant
            assert run['argv'][:3] == ['taskset', '-c', '0']
            path = result_path.parent / f'{group}-{boundary}-{order}-{variant}.log'
            assert digest(path) == run['log_sha256']
            samples = defaultdict(dict)
            for line in path.read_text(encoding='utf-8').splitlines():
                fields = line.split('\t')
                if fields[0] != 'DOT_SAMPLE':
                    continue
                assert len(fields) == 13
                _, name, row_group, row_variant, row_boundary, trial, n, iters, macs, ns, sink, expected, witness = fields
                assert row_group in (group, 'directed')
                assert row_variant == variant and row_boundary == boundary
                trial, n, iters, macs, ns, sink, expected, witness = map(int, (trial,n,iters,macs,ns,sink,expected,witness))
                assert trial not in samples[name] and ns > 0 and sink == expected
                assert macs == n * iters
                record = run['rows'][name]
                cached = next(s for s in record['samples'] if s['trial'] == trial)
                assert (n,iters,macs,ns,sink,expected,witness) == tuple(cached[k] for k in
                    ('n','iterations','actual_macs','ns','sink','expected_sink','witness_word'))
                samples[name][trial] = ns
                sample_count += 1
            assert len(samples) == 49 and set(samples) == set(run['rows'])
            medians = {}
            for name, trials in samples.items():
                assert set(trials) == {0,1,2}
                medians[name] = median(trials.values())
                assert medians[name] == run['rows'][name]['median_ns']
            key = (group,boundary,order)
            assert key not in reconstructed[role]
            reconstructed[role][key] = medians
            reviewed_logs.append({'path':path.relative_to(ROUND).as_posix(), 'sha256':digest(path), 'samples':147})
        assert set(reconstructed[role]) == {(g,b,o) for g in ('24282403','24282405') for b in ('full','prepared') for o in range(8)}

    ratios = []
    for role, body in summary['bodies'].items():
        for pair in body['paired_results']:
            key = (pair['group'], pair['boundary'])
            control = reconstructed[role][(*key,pair['control_order'])]
            variant = reconstructed[role][(*key,pair['variant_order'])]
            assert set(control) == set(variant)
            ratio = sum(variant.values()) / sum(control.values())
            assert math.isclose(ratio,pair['all_49']['ratio_of_summed_medians'], rel_tol=1e-14)
            for name in control:
                assert math.isclose(variant[name]/control[name],pair['per_case_ratios'][name],rel_tol=1e-14)
            expected_regressions = {n for n in control if variant[n] > control[n]}
            assert expected_regressions == {v['name'] for v in pair['per_case_regressions']}
            ratios.append({'body':role,'group':key[0],'boundary':key[1],'variant':pair['variant'],
                           'replicate':pair['replicate'],'ratio':ratio,'regressions':len(expected_regressions)})
    assert len(reviewed_logs) == 64 and sample_count == 9408 and len(ratios) == 32
    selected = [x['ratio'] for x in ratios if x['body']=='tail' and x['boundary']=='full' and x['variant']=='lazy']
    receipt = {
        'at_utc': datetime.datetime.now(datetime.timezone.utc).isoformat(),
        'status':'PASS_INDEPENDENT_RAW_RECONSTRUCTION', 'workflow_run':40804860824,
        'summary_sha256':digest(SUMMARY), 'source_sha256':SOURCES,
        'original_logs':64,'raw_ns_values':sample_count,'paired_records':len(ratios),
        'tail_full_lazy_ratios':selected,
        'tail_full_lazy_elapsed_reduction_range':[1-max(selected),1-min(selected)],
        'ratios':ratios,'reviewed_logs':reviewed_logs,
        'boundaries':{
            'full':'Each timed adapter call starts from raw input arrays and performs its own preparation and fallback. Lean value cleanup is within its typed call/native loop. Raw input generation is outside timing.',
            'prepared':'Preparation once per operand outside the repeated timed loop; preparation and lifecycle ns are recorded separately. Do not describe the principal prepared ns ratio as including initial preparation.',
            'weighting':'Ratio of sums of 49 case medians. Most cases repeat to about 131072 MACs per trial; this is a synthetic case mixture, not measured model-layer frequencies.',
        },
        'limits':[
            'Same-run exploratory data; not a frozen independent new-runner confirmation.',
            'Control is the self-written UInt64/UInt128 exact tier, not the official or former2 complete model.',
            'All slow cases retained; no individual regression is erased by an aggregate ratio.',
            '148 dots and 1049 rounds are finite numerical checks, not a universal proof.',
            'Cost bodies have no full correctness proof, formal adoption, whole-model measurement, or official score.',
            'Math8 failure is a separate source artifact and is not converted into acceptance by these cost results.',
        ],
    }
    out = HERE/'complete-cost-independent-review.json'
    out.write_text(json.dumps(receipt,ensure_ascii=False,indent=2)+'\n',encoding='utf-8',newline='\n')
    print(json.dumps({k:receipt[k] for k in ('status','original_logs','raw_ns_values','paired_records','tail_full_lazy_elapsed_reduction_range')}))


if __name__ == '__main__':
    main()
