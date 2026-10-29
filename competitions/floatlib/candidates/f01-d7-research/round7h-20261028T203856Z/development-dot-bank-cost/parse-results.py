"""Strict parser for the R24 whole-bank diagnostic protocol.

This parses harness receipts only. It does not claim all-input correctness,
official benchmark status, or success probability.
"""
from __future__ import annotations

import hashlib
import statistics

MASK32 = (1 << 32) - 1
DEFAULT_MAC_TARGET = 131072
GROUPS = ('24282601', '24282603')
ORDER = ('exact', 'eager', 'eager', 'exact', 'exact', 'lazy', 'lazy', 'exact')


def _require(condition, message):
    if not condition:
        raise ValueError(message)


def _int(value, field):
    try:
        return int(value)
    except (TypeError, ValueError) as error:
        raise ValueError(f'Invalid integer in {field}: {value!r}') from error


def _shape(case):
    rows_a = case.get('rowsA')
    rows_b = case.get('rowsB')
    _require(isinstance(rows_a, list) and rows_a and all(isinstance(r, list) and r for r in rows_a),
             f"Invalid rowsA for {case.get('name')}")
    _require(isinstance(rows_b, list) and rows_b and all(isinstance(r, list) and r for r in rows_b),
             f"Invalid rowsB for {case.get('name')}")
    m, k, n = len(rows_a), len(rows_a[0]), len(rows_b)
    _require(all(len(r) == k for r in rows_a), f"Ragged rowsA for {case.get('name')}")
    _require(all(len(r) == k for r in rows_b), f"Ragged rowsB for {case.get('name')}")
    _require((m, k, n) == (case.get('rows'), case.get('inner'), case.get('cols')),
             f"Declared/actual dimensions differ for {case.get('name')}")
    expected = case.get('expected')
    _require(isinstance(expected, list) and len(expected) == m * n,
             f"Expected output count differs from m*n for {case.get('name')}")
    _require(all(isinstance(x, int) and 0 <= x <= MASK32 for x in expected),
             f"Invalid UInt32 expected output for {case.get('name')}")
    frame = case.get('frame', {})
    _require(frame.get('output_words') == len(expected), f"Frame output_words differs for {case.get('name')}")
    return {'m': m, 'k': k, 'n': n, 'work': m * n * k, 'output_words': len(expected),
            'expected_sum': sum(expected) & MASK32}


def validate_fixtures(fixtures):
    cases = fixtures.get('cases')
    _require(isinstance(cases, list) and len(cases) == 6, 'Expected exactly six frozen bank cases')
    groups = tuple(str(x) for x in fixtures.get('seeds', []))
    _require(groups == GROUPS, f'Unexpected fixture groups: {groups!r}')
    by_name = {}
    outputs = 0
    work_sum = 0
    group_counts = {group: 0 for group in GROUPS}
    for case in cases:
        name = case.get('name')
        group = str(case.get('group'))
        _require(isinstance(name, str) and name and name not in by_name, 'Missing/duplicate fixture case name')
        _require(group in group_counts, f'Unexpected fixture group for {name}')
        shape = _shape(case)
        by_name[name] = {'case': case, **shape}
        outputs += shape['output_words']
        work_sum += shape['work']
        group_counts[group] += 1
    _require(group_counts == {GROUPS[0]: 3, GROUPS[1]: 3}, f'Expected 3 cases in each group, got {group_counts}')
    _require(outputs == 464, f'Expected 464 frozen output words, got {outputs}')
    _require(work_sum == fixtures.get('total_macs') == 44032, 'Fixture work total differs from frozen total_macs')
    return {'by_name': by_name, 'group_counts': group_counts, 'case_count': len(by_name),
            'output_words': outputs, 'base_work_sum': work_sum, 'groups': groups}


def verify(text, fixtures):
    """Validate BANK_VERIFY rows and the six-case/464-word/3-backend footer."""
    meta = validate_fixtures(fixtures)
    seen = {}
    footers = []
    for line in text.splitlines():
        if not line.strip():
            continue
        fields = line.split('\t')
        if fields[0] == 'BANK_VERIFY':
            _require(len(fields) == 8, 'BANK_VERIFY must contain exactly 8 fields')
            name = fields[1]
            _require(name in meta['by_name'] and name not in seen, f'Unknown/duplicate BANK_VERIFY case: {name}')
            expected = meta['by_name'][name]
            outputs, expected_sum, exact_sum, eager_sum, lazy_sum = [
                _int(value, 'BANK_VERIFY') for value in fields[2:7]
            ]
            _require(outputs == expected['output_words'], f'BANK_VERIFY output count differs for {name}')
            _require(expected_sum == expected['expected_sum'], f'BANK_VERIFY expected sum differs for {name}')
            _require(exact_sum == eager_sum == lazy_sum == expected_sum, f'BANK_VERIFY backend sum mismatch for {name}')
            _require(fields[7] == 'true', f'BANK_VERIFY word checker rejected {name}')
            seen[name] = {'outputs': outputs, 'expected_sum': expected_sum,
                          'exact_sum': exact_sum, 'eager_sum': eager_sum, 'lazy_sum': lazy_sum}
        elif fields[0] == 'BANK_VERIFY_DONE':
            _require(len(fields) == 4, 'BANK_VERIFY_DONE must contain exactly 4 fields')
            footers.append(tuple(_int(x, 'BANK_VERIFY_DONE') for x in fields[1:]))
        else:
            raise ValueError(f'Unexpected verify record: {line[:160]}')
    _require(set(seen) == set(meta['by_name']), 'BANK_VERIFY cases are incomplete')
    _require(footers == [(6, 464, 3)], f'Expected one BANK_VERIFY_DONE 6 464 3 footer, got {footers!r}')
    return {'cases': 6, 'output_words': 464, 'backends': 3, 'bank_sum_checks': 18,
            'all_case_sums_match': True, 'scope': 'Harness-reported wordwise verification plus strict logged count/sum checks.'}


def rows(text, fixtures, group, variant, mac_target=DEFAULT_MAC_TARGET):
    """Parse one full-boundary process; keep all three raw ns samples per case."""
    meta = validate_fixtures(fixtures)
    group = str(group)
    _require(group in GROUPS, f'Unknown bank group: {group}')
    _require(variant in ('exact', 'eager', 'lazy'), f'Unknown bank variant: {variant}')
    _require(isinstance(mac_target, int) and 0 < mac_target <= (1 << 24), 'Invalid MAC target')
    selected = {name: item for name, item in meta['by_name'].items() if str(item['case']['group']) == group}
    _require(len(selected) == 3, f'Expected three bank cases in group {group}')
    samples = {name: [] for name in selected}
    setups = {}
    footers = []
    for line in text.splitlines():
        if not line.strip():
            continue
        fields = line.split('\t')
        kind = fields[0]
        if kind == 'BANK_SAMPLE':
            _require(len(fields) == 13, 'BANK_SAMPLE must contain exactly 13 fields')
            name = fields[1]
            _require(name in selected, f'Unknown BANK_SAMPLE case for group {group}: {name}')
            item = selected[name]
            _require(fields[2] == group and fields[3] == variant and fields[4] == 'full',
                     f'BANK_SAMPLE identity differs for {name}')
            trial, work, iters, actual_macs, ns, sink, expected_sink, keep_word = [
                _int(value, 'BANK_SAMPLE') for value in fields[5:13]
            ]
            _require(trial in (0, 1, 2), f'Invalid trial number for {name}: {trial}')
            _require(all(sample['trial'] != trial for sample in samples[name]), f'Duplicate trial {trial} for {name}')
            _require(work == item['work'], f'BANK_SAMPLE actual-array work differs for {name}')
            wanted_iters = max(1, (mac_target + work - 1) // work)
            _require(iters == wanted_iters, f'BANK_SAMPLE iteration count differs for {name}')
            _require(actual_macs == work * iters, f'BANK_SAMPLE actualMACs differs for {name}')
            _require(ns > 0, f'BANK_SAMPLE ns must be positive for {name}')
            seed = (2654435769 + 1664525 * trial) & MASK32
            wanted_sink = (seed + iters * item['expected_sum']) & MASK32
            _require(expected_sink == wanted_sink and sink == wanted_sink, f'BANK_SAMPLE sink checksum differs for {name}')
            _require(keep_word == item['expected_sum'], f'BANK_SAMPLE keepWord differs from full expected sum for {name}')
            samples[name].append({'trial': trial, 'work': work, 'iters': iters, 'actual_macs': actual_macs,
                                  'ns': ns, 'sink': sink, 'expected_sink': expected_sink,
                                  'keep_word': keep_word})
        elif kind == 'BANK_SETUP':
            _require(len(fields) == 9, 'BANK_SETUP must contain exactly 9 fields')
            name = fields[1]
            _require(name in selected and name not in setups, f'Unknown/duplicate BANK_SETUP case: {name}')
            item = selected[name]
            _require(fields[2] == group and fields[3] == variant and fields[4] == 'full',
                     f'BANK_SETUP identity differs for {name}')
            _require(fields[5] == '0', f'BANK_SETUP reserved preparation field differs for {name}')
            lifecycle_ns, trial_count, last_witness = [_int(x, 'BANK_SETUP') for x in fields[6:9]]
            _require(lifecycle_ns > 0 and trial_count == 3, f'BANK_SETUP lifecycle/trial count invalid for {name}')
            _require(last_witness == item['expected_sum'], f'BANK_SETUP last witness differs for {name}')
            setups[name] = {'lifecycle_wall_ns': lifecycle_ns, 'trials': trial_count,
                            'last_witness': last_witness}
        elif kind == 'BANK_MEASURE_DONE':
            _require(len(fields) == 6, 'BANK_MEASURE_DONE must contain exactly 6 fields')
            footer = (fields[1], fields[2], fields[3], _int(fields[4], kind), _int(fields[5], kind))
            footers.append(footer)
        else:
            raise ValueError(f'Unexpected measure record: {line[:160]}')
    _require(set(setups) == set(selected), 'BANK_SETUP case set is incomplete')
    _require(all(len(samples[name]) == 3 and {s['trial'] for s in samples[name]} == {0, 1, 2} for name in selected),
             'Each bank case must retain exactly trials 0, 1, and 2')
    _require(footers == [(group, variant, 'full', 3, 3)], f'Expected one matching BANK_MEASURE_DONE footer, got {footers!r}')
    result = {}
    for name, item in selected.items():
        ordered = sorted(samples[name], key=lambda sample: sample['trial'])
        ns_values = [sample['ns'] for sample in ordered]
        result[name] = {'group': group, 'variant': variant, 'boundary': 'full',
                        'm': item['m'], 'k': item['k'], 'n': item['n'], 'work': item['work'],
                        'expected_sum': item['expected_sum'], 'output_words': item['output_words'],
                        'median_ns': statistics.median(ns_values), 'samples': ordered,
                        'setup': setups[name]}
    return result


def paired(runs, fixtures):
    """Pair four ABBA treatment/control runs in each of the two fixed groups."""
    meta = validate_fixtures(fixtures)
    _require(len(runs) == 16, f'Expected 16 measurement processes, got {len(runs)}')
    run_map = {}
    for run in runs:
        group = str(run.get('group'))
        boundary = run.get('boundary')
        order = run.get('order')
        _require(group in GROUPS and boundary == 'full' and isinstance(order, int) and 0 <= order < 8,
                 f'Invalid paired run identity: {group}/{boundary}/{order}')
        key = (group, order)
        _require(key not in run_map, f'Duplicate paired run: {key}')
        _require(run.get('variant') == ORDER[order], f'ABBA order/variant differs for {key}')
        expected_names = {name for name, item in meta['by_name'].items() if str(item['case']['group']) == group}
        _require(set(run.get('rows', {})) == expected_names, f'Paired case set differs for {key}')
        run_map[key] = run
    expected_keys = {(group, order) for group in GROUPS for order in range(8)}
    _require(set(run_map) == expected_keys, 'Paired run set is incomplete')
    specs = [('eager', 1, 0, 1), ('eager', 2, 3, 2), ('lazy', 1, 4, 5), ('lazy', 2, 7, 6)]
    results = []
    for group in GROUPS:
        for variant, replicate, control_order, variant_order in specs:
            control = run_map[(group, control_order)]
            treatment = run_map[(group, variant_order)]
            control_rows, candidate_rows = control['rows'], treatment['rows']
            names = sorted(control_rows)
            _require(set(names) == set(candidate_rows), f'Control/candidate cases differ in {group}/{variant}/{replicate}')
            control_sum = sum(control_rows[name]['median_ns'] for name in names)
            candidate_sum = sum(candidate_rows[name]['median_ns'] for name in names)
            _require(control_sum > 0 and candidate_sum > 0, 'Paired timing sums must be positive')
            per_case = {}
            for name in names:
                numerator = candidate_rows[name]['median_ns']
                denominator = control_rows[name]['median_ns']
                per_case[name] = {'candidate_ns': numerator, 'control_ns': denominator,
                                  'ratio_numerator': numerator, 'ratio_denominator': denominator,
                                  'ratio': numerator / denominator,
                                  'regression': numerator > denominator,
                                  'samples': candidate_rows[name]['samples']}
            results.append({'group': group, 'boundary': 'full', 'variant': variant, 'replicate': replicate,
                            'control_order': control_order, 'candidate_order': variant_order,
                            'control_ns_sum': control_sum, 'candidate_ns_sum': candidate_sum,
                            'ratio_numerator': candidate_sum, 'ratio_denominator': control_sum,
                            'ratio': candidate_sum / control_sum,
                            'per_case': per_case,
                            'regressions': [name for name in names if per_case[name]['regression']],
                            'cases': len(names), 'samples_per_case': 3})
    _require(len(results) == 8, 'Expected eight paired ratios from sixteen processes')
    summaries = {}
    for variant in ('eager', 'lazy'):
        subset = [row for row in results if row['variant'] == variant]
        numerators = [row['ratio_numerator'] for row in subset]
        denominators = [row['ratio_denominator'] for row in subset]
        summaries[variant] = {'pair_count': len(subset),
                              'integer_pairs': [{'numerator': n, 'denominator': d} for n, d in zip(numerators, denominators)],
                              'ratio_values': [row['ratio'] for row in subset],
                              'all_raw_case_samples_retained': True}
    return {'processes': 16, 'pairs': results, 'variant_summaries': summaries,
            'scope': 'Within-body exact control on the same frozen bank inputs; diagnostic cost only.'}


def _synthetic_measure_log(fixtures, group, variant):
    meta = validate_fixtures(fixtures)
    lines = []
    for index, (name, item) in enumerate(sorted(meta['by_name'].items())):
        case = item['case']
        if str(case['group']) != str(group):
            continue
        expected_sum = item['expected_sum']
        work = item['work']
        iters = max(1, (DEFAULT_MAC_TARGET + work - 1) // work)
        factor_num = {'exact': 100, 'eager': 90, 'lazy': 110}[variant]
        for trial in range(3):
            seed = (2654435769 + 1664525 * trial) & MASK32
            sink = (seed + iters * expected_sum) & MASK32
            ns = ((1000 + index) * factor_num) // 100 + trial
            lines.append('\t'.join(map(str, ['BANK_SAMPLE', name, group, variant, 'full', trial,
                                              work, iters, work*iters, ns, sink, sink, expected_sum])))
        lines.append('\t'.join(map(str, ['BANK_SETUP', name, group, variant, 'full', 0, 1000, 3, expected_sum])))
    lines.append('\t'.join(['BANK_MEASURE_DONE', group, variant, 'full', '3', '3']))
    return '\n'.join(lines) + '\n'


def selftest(fixtures):
    """Run parser-only positive and fail-closed controls on frozen fixture data."""
    meta = validate_fixtures(fixtures)
    verify_lines = []
    for name, item in meta['by_name'].items():
        outputs = item['output_words']
        expected_sum = item['expected_sum']
        verify_lines.append('\t'.join(map(str, ['BANK_VERIFY', name, outputs, expected_sum,
                                                expected_sum, expected_sum, expected_sum, 'true'])))
    verify_lines.append('\t'.join(['BANK_VERIFY_DONE', '6', '464', '3']))
    verification = verify('\n'.join(verify_lines), fixtures)
    sample_log = _synthetic_measure_log(fixtures, GROUPS[0], 'exact')
    one_run = rows(sample_log, fixtures, GROUPS[0], 'exact')
    _require(len(one_run) == 3 and all(len(x['samples']) == 3 for x in one_run.values()), 'Positive row parser self-test failed')

    run_records = []
    for group in GROUPS:
        for order, variant in enumerate(ORDER):
            run_records.append({'group': group, 'boundary': 'full', 'order': order, 'variant': variant,
                                'rows': rows(_synthetic_measure_log(fixtures, group, variant), fixtures, group, variant)})
    paired_result = paired(run_records, fixtures)
    _require(paired_result['processes'] == 16 and len(paired_result['pairs']) == 8, 'Paired parser self-test failed')
    _require(all(x['ratio_denominator'] > 0 and x['ratio_numerator'] > 0 for x in paired_result['pairs']), 'Integer control ratio self-test failed')

    def rejects(label, bad_text):
        try:
            rows(bad_text, fixtures, GROUPS[0], 'exact')
        except ValueError as error:
            return {'name': label, 'pass': True, 'rejection': str(error)}
        return {'name': label, 'pass': False, 'rejection': None}

    lines = sample_log.splitlines()
    sample_index = next(i for i, line in enumerate(lines) if line.startswith('BANK_SAMPLE\t'))
    fields = lines[sample_index].split('\t')
    fields[10] = str((int(fields[10]) + 1) & MASK32)
    bad_checksum = list(lines); bad_checksum[sample_index] = '\t'.join(fields)
    duplicate_trial = list(lines); duplicate_trial.insert(sample_index + 1, lines[sample_index])
    negative = [
        rejects('missing_footer', '\n'.join(lines[:-1])),
        rejects('wrong_checksum', '\n'.join(bad_checksum)),
        rejects('duplicate_trial', '\n'.join(duplicate_trial)),
    ]
    _require(all(x['pass'] for x in negative), 'A negative parser self-test was accepted')
    return {'status': 'PASS', 'fixture_case_count': meta['case_count'],
            'fixture_output_words': meta['output_words'], 'fixture_base_work_sum': meta['base_work_sum'],
            'verify_summary': verification, 'positive_measure_cases': len(one_run),
            'raw_samples_per_case': 3, 'paired_process_count': 16,
            'paired_ratio_records': len(paired_result['pairs']),
            'control_ratio_integer_fields_present': all('ratio_numerator' in x and 'ratio_denominator' in x for x in paired_result['pairs']),
            'negative_controls': negative,
            'scope': 'Synthetic parser protocol checks only; no benchmark data, proof, or score.'}
