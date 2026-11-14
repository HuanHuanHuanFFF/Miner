from __future__ import annotations
import hashlib
import json
import statistics
from pathlib import Path

OWNER = Path(__file__).resolve().parent
REPO = OWNER.parents[6]
RUN_DIR = REPO / 'competitions/floatlib/candidates/f01-d7-research/round7h-20261028T203856Z/ci-runs/40801622733'
HASH_INDEX_PATH = RUN_DIR / 'original-artifact-hashes.json'
CANDIDATE_MANIFEST = REPO / 'competitions/floatlib/candidates/f01-r24-dev-dot-cost1/manifest.json'
FIXTURES = REPO / 'competitions/floatlib/candidates/f01-d7-research/round7h-20261028T203856Z/development-dot-cost/fixtures.json'
PAIRING_SOURCE = REPO / 'competitions/floatlib/candidates/f01-d7-research/round7h-20261028T203856Z/development-dot-cost/parse-results.py'
JOBS_INDEX = REPO / 'competitions/floatlib/candidates/f01-d7-research/round7h-20261028T203856Z/development-jobs.json'
ROUTE_INDEX = REPO / 'competitions/floatlib/candidates/f01-d7-research/round7h-20261028T203856Z/development-route-decisions.json'
OUT_JSON = OWNER / 'partial-analysis-results.json'
OUT_MD = OWNER / 'partial-analysis-findings.md'
FIRST_GROUP = '24282403'
SECOND_GROUP = '24282405'
NORMAL_KINDS = {'narrow', 'moderate', 'wide'}


def sha_bytes(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()

def sha_path(path: Path) -> str:
    return sha_bytes(path.read_bytes())

def load_json(path: Path):
    return json.loads(path.read_bytes())

def verify_original_artifact():
    raw = HASH_INDEX_PATH.read_bytes()
    index = json.loads(raw)
    root = (RUN_DIR / index['directory']).resolve()
    assert root.is_relative_to(REPO.resolve()), 'artifact root outside repo'
    expected = index['files']
    actual_paths = {p.relative_to(root).as_posix() for p in root.rglob('*') if p.is_file()}
    expected_paths = set(expected)
    details = []
    for rel in sorted(expected_paths):
        path = (root / Path(rel)).resolve()
        assert path.is_relative_to(root), f'indexed path escapes artifact root: {rel}'
        if not path.is_file():
            details.append({'path': rel, 'pass': False, 'reason': 'missing'})
            continue
        data = path.read_bytes()
        record = expected[rel]
        actual_sha = sha_bytes(data)
        actual_size = len(data)
        details.append({'path': rel, 'pass': actual_sha == record['sha256'] and actual_size == record['bytes'],
                        'expected_sha256': record['sha256'], 'actual_sha256': actual_sha,
                        'expected_bytes': record['bytes'], 'actual_bytes': actual_size})
    missing = sorted(expected_paths - actual_paths)
    extra = sorted(actual_paths - expected_paths)
    failures = [x for x in details if not x['pass']]
    audit = {
        'status': 'PASS' if len(expected) == 119 and len(actual_paths) == 119 and not missing and not extra and not failures else 'FAIL',
        'artifact_id': index['artifact']['id'], 'workflow_run_id': index['artifact']['workflow_run']['id'],
        'artifact_zip_sha256_receipt': index['artifact']['digest'].removeprefix('sha256:'),
        'artifact_zip_digest_recomputed': False, 'hash_index_sha256': sha_bytes(raw),
        'expected_file_count': len(expected), 'actual_file_count': len(actual_paths),
        'matched_file_count': sum(x['pass'] for x in details), 'missing_paths': missing,
        'unexpected_paths': extra, 'failed_files': failures, 'files': details,
    }
    (OWNER / 'partial-analysis-hash-audit.json').write_text(json.dumps(audit, indent=2) + '\n', encoding='utf-8')
    if audit['status'] != 'PASS':
        raise AssertionError('parent original artifact hash verification failed')
    return index, root, audit

def case_rollup(names, control_rows, variant_rows):
    if not names:
        return {'case_count': 0}
    control_sum = sum(control_rows[n]['median_ns'] for n in names)
    variant_sum = sum(variant_rows[n]['median_ns'] for n in names)
    ratios = {n: variant_rows[n]['median_ns'] / control_rows[n]['median_ns'] for n in names}
    best_name = min(ratios, key=ratios.get)
    worst_name = max(ratios, key=ratios.get)
    return {
        'case_count': len(names), 'control_median_ns_sum': control_sum,
        'variant_median_ns_sum': variant_sum, 'ratio_of_summed_medians': variant_sum / control_sum,
        'sum_of_per_case_ratios': sum(ratios.values()),
        'best_case': {'name': best_name, 'ratio': ratios[best_name], 'kind': control_rows[best_name]['kind'], 'n': control_rows[best_name]['n']},
        'worst_case': {'name': worst_name, 'ratio': ratios[worst_name], 'kind': control_rows[worst_name]['kind'], 'n': control_rows[worst_name]['n']},
    }

def main():
    # Artifact hashes are recalculated before any timing rows or fixtures are opened.
    artifact_index, artifact_root, hash_audit = verify_original_artifact()
    runtime = artifact_root / 'diagnostics/f01-d7-public-suite/public-suite/diagnostics/f01-r24-dev-dot-cost1/runtime-cost'
    result_path = runtime / 'result.json'
    result = load_json(result_path)
    manifest = load_json(CANDIDATE_MANIFEST)
    fixture_bytes = FIXTURES.read_bytes()
    fixtures = json.loads(fixture_bytes)
    jobs_index = load_json(JOBS_INDEX)
    indexed_jobs = [j for j in jobs_index['jobs'] if j.get('run') == 40801622733]
    assert len(indexed_jobs) == 1
    job = indexed_jobs[0]
    indexed_summary_path = RUN_DIR.parents[1] / job['result']
    indexed_summary = load_json(indexed_summary_path)
    ci_run_receipt = load_json(RUN_DIR / 'ci-run.json')
    route_index = load_json(ROUTE_INDEX)
    fixture_component = next(c for c in manifest['components'] if c['path'].endswith('/development-dot-cost/fixtures.json'))
    fixture_sha = sha_bytes(fixture_bytes)
    assert fixture_sha == fixture_component['sha256'] and len(fixture_bytes) == fixture_component['bytes'], 'frozen fixtures differ from candidate manifest'
    assert manifest['candidate'] == 'f01-r24-dev-dot-cost1'
    assert result['source_sha256'] == manifest['candidate_sha256'] == '5bf2a8893b01a5ed44393e80065fbd91e9b3686133e9ddd5d4dfb633379d4d2a'

    case_defs_by_group = {group: {c['name']: c for c in fixtures['cases'] if c['timed'] and c['group'] in (group, 'directed')}
                          for group in (FIRST_GROUP, SECOND_GROUP)}
    case_defs = case_defs_by_group[FIRST_GROUP]
    assert len(case_defs) == 49, f'expected 49 frozen timed cases, got {len(case_defs)}'
    run_records = result['runs']
    first = [r for r in run_records if r['group'] == FIRST_GROUP]
    second = [r for r in run_records if r['group'] == SECOND_GROUP]
    assert len(first) == 16 and len(second) == 2 and len(run_records) == 18
    assert result['complete'] is False and result['formal_adoption'] is False

    # Verify stored row artifacts against result.json and take the median of all three raw ns values.
    normalized = {}
    raw_row_file_count = 0
    raw_sample_value_count = 0
    raw_sample_value_count_by_group = {FIRST_GROUP: 0, SECOND_GROUP: 0}
    for run in run_records:
        group, boundary, order, variant = run['group'], run['boundary'], run['order'], run['variant']
        row_path = runtime / f'{group}-{boundary}-{order}-{variant}-rows.json'
        raw_rows = load_json(row_path)
        rows = run['rows']
        assert raw_rows == rows, f'raw row artifact differs from result.json: {row_path.name}'
        defs_for_group = case_defs_by_group[group]
        assert set(rows) == set(defs_for_group), f'case set mismatch in {row_path.name}'
        assert run['exit_code'] == 0, f'nonzero measurement process: {row_path.name}'
        checked = {}
        for name, row in rows.items():
            definition = defs_for_group[name]
            ns_values = [sample['ns'] for sample in row['samples']]
            assert len(ns_values) == 3, f'raw sample count not 3: {name}'
            assert row['median_ns'] == statistics.median(ns_values), f'median not computed from all three raw ns: {name}'
            assert row['n'] == len(definition['x']) == len(definition['y']), f'fixture length mismatch: {name}'
            assert row['kind'] == definition['kind'], f'fixture kind mismatch: {name}'
            checked[name] = row
            raw_sample_value_count += 3
            raw_sample_value_count_by_group[group] += 3
        normalized[(group, boundary, order)] = {**run, 'rows': checked}
        raw_row_file_count += 1

    expected_order = ['exact', 'eager', 'eager', 'exact', 'exact', 'lazy', 'lazy', 'exact']
    for boundary in ('full', 'prepared'):
        block = sorted([r for r in first if r['boundary'] == boundary], key=lambda r:r['order'])
        assert [r['order'] for r in block] == list(range(8))
        assert [r['variant'] for r in block] == expected_order
    assert [(r['boundary'], r['order'], r['variant']) for r in sorted(second, key=lambda r:(r['boundary'],r['order']))] == [('full',0,'exact'),('full',1,'eager')]

    # Pairing exactly follows the frozen ABBA parser: E0/A0, E1/A1, L0/A0, L1/A1.
    source_text = PAIRING_SOURCE.read_text(encoding='utf-8')
    assert "for variant,start in [('eager',0),('lazy',4)]" in source_text
    assert '[(0,start,start+1),(1,start+3,start+2)]' in source_text
    pair_specs = [('eager', 1, 0, 1), ('eager', 2, 3, 2), ('lazy', 1, 4, 5), ('lazy', 2, 7, 6)]
    paired = []
    for boundary in ('full', 'prepared'):
        for variant, replicate, control_order, variant_order in pair_specs:
            control = normalized[(FIRST_GROUP, boundary, control_order)]
            treatment = normalized[(FIRST_GROUP, boundary, variant_order)]
            control_rows, variant_rows = control['rows'], treatment['rows']
            assert set(control_rows) == set(variant_rows) == set(case_defs)
            all_rollup = case_rollup(list(case_defs), control_rows, variant_rows)
            per_case = {n: variant_rows[n]['median_ns'] / control_rows[n]['median_ns'] for n in sorted(case_defs)}
            kind_rollups = {}
            for kind in sorted({c['kind'] for c in case_defs.values()}):
                names = [n for n,c in case_defs.items() if c['kind'] == kind]
                kind_rollups[kind] = case_rollup(names, control_rows, variant_rows)
            n_lt32 = [n for n,c in case_defs.items() if len(c['x']) < 32]
            n_ge32 = [n for n,c in case_defs.items() if len(c['x']) >= 32]
            short_normal = [n for n in n_lt32 if case_defs[n]['kind'] in NORMAL_KINDS]
            long_normal = [n for n in n_ge32 if case_defs[n]['kind'] in NORMAL_KINDS]
            normal_by_kind_n = {}
            for kind in sorted(NORMAL_KINDS):
                for label, names in [('n_lt32', short_normal), ('n_ge32', long_normal)]:
                    selected = [n for n in names if case_defs[n]['kind'] == kind]
                    normal_by_kind_n[f'{kind}_{label}'] = case_rollup(selected, control_rows, variant_rows)
            range_rollups = {
                'all_n_lt32': case_rollup(n_lt32, control_rows, variant_rows),
                'all_n_ge32': case_rollup(n_ge32, control_rows, variant_rows),
                'short_normal_n_lt32': case_rollup(short_normal, control_rows, variant_rows),
                'long_normal_n_ge32': case_rollup(long_normal, control_rows, variant_rows),
                'normal_by_kind_and_n': normal_by_kind_n,
            }
            paired.append({
                'group': FIRST_GROUP, 'boundary': boundary, 'variant': variant, 'replicate': replicate,
                'control_order': control_order, 'variant_order': variant_order,
                'control_wall_seconds': control['wall_seconds'], 'variant_wall_seconds': treatment['wall_seconds'],
                'process_wall_ratio': treatment['wall_seconds'] / control['wall_seconds'],
                'all_49': all_rollup, 'per_case_ratios': per_case,
                'per_case_best': all_rollup['best_case'], 'per_case_worst': all_rollup['worst_case'],
                'kind_rollups': kind_rollups, 'length_rollups': range_rollups,
                'long_normal_best': range_rollups['long_normal_n_ge32'].get('best_case'),
                'long_normal_worst': range_rollups['long_normal_n_ge32'].get('worst_case'),
                'scope': 'Exploratory synthetic harness ratios; not official score, current champion comparison, or success probability.',
            })

    native = result['native_oracle']
    caller = result['actual_caller_audit']
    flags = result['flags']
    flag_checks = {name: {'only_owned_barrier_removed': flags[name]['only_owned_barrier_removed'],
                          'equal_after_only_root_mapping': flags[name]['equal_after_only_root_mapping']}
                   for name in ('compile','link','response')}
    assert flag_checks['compile']['only_owned_barrier_removed'] == []
    assert flag_checks['link']['only_owned_barrier_removed'] == []
    response_removed = flag_checks['response']['only_owned_barrier_removed']
    assert len(response_removed) == 1 and Path(response_removed[0]['path']).name == 'R24DotBarrier.c.o.export'
    assert all(x['equal_after_only_root_mapping'] for x in flag_checks.values())
    assert caller['pass'] is True and all(x['pass'] for x in caller['records'])
    assert result['build_exit_code'] == 0 and result['native_oracle_exit_code'] == 0
    assert native['dots'] == 148 and native['word_rounds'] == 1049
    assert native['all_complete_words_match'] and native['all_expected_accept_miss_match']
    stage_receipt = load_json(runtime / 'stage-receipt.json')
    candidate_verdict = load_json(artifact_root / 'diagnostics/f01-d7-public-suite/public-suite/f01-r24-dev-dot-cost1-verdict.json')
    suite_verdict = load_json(artifact_root / 'diagnostics/f01-d7-public-suite/diagnostic-only-verdict.json')
    outer_suite_index_path = artifact_root / 'diagnostics/f01-d7-public-suite/index.json'
    outer_suite_index = load_json(outer_suite_index_path)
    nested_candidate_index_path = artifact_root / 'diagnostics/f01-d7-public-suite/public-suite/diagnostics/f01-r24-dev-dot-cost1/index.json'
    nested_candidate_index = load_json(nested_candidate_index_path)
    assert stage_receipt['status'] == 'RUNNING' and candidate_verdict['stage'] == 'diagnostic-timeout'
    assert suite_verdict['diagnostic_only'] is True and suite_verdict['passed'] is False
    assert nested_candidate_index['replay'] == 'diagnostic-only replay process group timed out at 120s'
    assert nested_candidate_index['replay_seconds'] == 120.004
    assert nested_candidate_index.get('r24_statement_timeout') is None

    # Aggregated two-replicate ranges are descriptive only; preserve each pair above.
    combined = {}
    for boundary in ('full','prepared'):
        for variant in ('eager','lazy'):
            chosen = [p for p in paired if p['boundary']==boundary and p['variant']==variant]
            ratios = [p['all_49']['ratio_of_summed_medians'] for p in chosen]
            combined[f'{boundary}_{variant}'] = {'replicate_ratio_of_summed_medians': ratios,
                                                  'min_observed': min(ratios), 'max_observed': max(ratios),
                                                  'median_of_two_ratios': statistics.median(ratios)}

    hash_records = {p['path']:p for p in hash_audit['files']}
    result_rel = 'diagnostics/f01-d7-public-suite/public-suite/diagnostics/f01-r24-dev-dot-cost1/runtime-cost/result.json'
    nested_index_rel = 'diagnostics/f01-d7-public-suite/public-suite/diagnostics/f01-r24-dev-dot-cost1/index.json'
    outer_index_rel = 'diagnostics/f01-d7-public-suite/index.json'
    row_paths = [p for p in hash_records if p.endswith('-rows.json') and p.startswith('diagnostics/f01-d7-public-suite/public-suite/diagnostics/f01-r24-dev-dot-cost1/runtime-cost/')]
    assert hash_records[result_rel]['pass'] and len(row_paths) == 18
    assert hash_records[nested_index_rel]['pass'] and hash_records[outer_index_rel]['pass']
    diagnostic_index_path = artifact_root/'diagnostics/f01-d7-public-suite/index.json'
    artifact_workflow = artifact_index['artifact']['workflow_run']
    uncompressed_artifact_bytes = sum(x['actual_bytes'] for x in hash_audit['files'])
    assert job['status'] == 'FAILURE_COLLECTED_OUTER120_TIMEOUT_PARTIAL18PROCESSES'
    assert job['raw_files'] == hash_audit['matched_file_count'] == 119
    assert job['raw_bytes'] == uncompressed_artifact_bytes == 15208417
    assert indexed_summary['run'] == 40801622733 and indexed_summary['source_commit'] == job['source_commit']
    assert indexed_summary['candidate'] == manifest['candidate'] and indexed_summary['sha256'] == result['source_sha256']
    assert indexed_summary['status'] == job['status'] and indexed_summary['raw_files'] == job['raw_files']
    assert indexed_summary['raw_bytes'] == job['raw_bytes'] and indexed_summary['completed_processes'] == 18
    assert indexed_summary['measurement_complete'] is False
    assert indexed_summary['full_final_provenance'] == 'NOT_EXECUTED_AFTER_EXTERNALKILL'
    assert ci_run_receipt['databaseId'] == 40801622733 and ci_run_receipt['status'] == 'completed' and ci_run_receipt['conclusion'] == 'failure'
    assert ci_run_receipt['headSha'] == job['source_commit'] == artifact_workflow['head_sha']
    assert ci_run_receipt['headBranch'] == artifact_workflow['head_branch'] == 'huan/codex-gpt'
    report = {
        'status': 'PARTIAL_EXPLORATION_ANALYSIS_COMPLETE',
        'artifact_integrity': {
            'status': hash_audit['status'], 'artifact_id': hash_audit['artifact_id'],
            'workflow_run_id': hash_audit['workflow_run_id'], 'all_119_file_hashes_and_sizes_match': True,
            'missing_or_extra_files': 0, 'hash_index_sha256': hash_audit['hash_index_sha256'],
            'artifact_zip_sha256_from_receipt_not_recomputed': hash_audit['artifact_zip_sha256_receipt'],
        },
        'source_hashes': {
            'original_artifact_hash_index_sha256': sha_path(HASH_INDEX_PATH),
            'result_json_sha256': hash_records[result_rel]['actual_sha256'],
            'candidate_kernel_sha256': result['source_sha256'],
            'candidate_manifest_sha256': sha_path(CANDIDATE_MANIFEST),
            'frozen_fixtures_path': str(FIXTURES.relative_to(REPO)), 'frozen_fixtures_sha256': fixture_sha,
            'frozen_fixtures_manifest_component_sha256': fixture_component['sha256'],
            'parse_results_pairing_source_sha256': sha_path(PAIRING_SOURCE),
            'development_jobs_index_sha256': sha_path(JOBS_INDEX),
            'development_first_result_index_sha256': sha_path(indexed_summary_path),
            'development_route_decisions_sha256': sha_path(ROUTE_INDEX),
            'ci_run_receipt_sha256': sha_path(RUN_DIR/'ci-run.json'),
            'nested_candidate_index_sha256': hash_records[nested_index_rel]['actual_sha256'],
            'outer_suite_index_sha256': hash_records[outer_index_rel]['actual_sha256'],
        },
        'source_index_consistency': {
            'job_entry_status': job['status'], 'job_source_commit': job['source_commit'],
            'job_raw_files': job['raw_files'], 'verified_raw_files': hash_audit['matched_file_count'],
            'job_raw_bytes': job['raw_bytes'], 'verified_uncompressed_bytes': uncompressed_artifact_bytes,
            'indexed_result_completed_processes': indexed_summary['completed_processes'],
            'indexed_measurement_complete': indexed_summary['measurement_complete'],
            'indexed_full_final_provenance': indexed_summary['full_final_provenance'],
            'indexed_failure_cause': indexed_summary['failure_cause'],
            'indexed_fix': indexed_summary['fix'], 'indexed_next': indexed_summary['next'],
            'ci_run_state': ci_run_receipt['status'], 'ci_run_conclusion': ci_run_receipt['conclusion'],
            'ci_run_head_sha_matches_job_and_artifact_receipt': True,
            'route_state': route_index['state'],
            'route_new_target_policy': route_index['newtarget_implementation_or_CI'],
        },
        'data_shape': {
            'result_complete': result['complete'], 'formal_adoption': result['formal_adoption'],
            'first_group': FIRST_GROUP, 'first_group_runs': len(first), 'first_group_full_runs': 8,
            'first_group_prepared_runs': 8, 'cases_per_run': len(case_defs), 'raw_samples_per_case': 3,
            'raw_sample_ns_values_crosschecked': raw_sample_value_count,
            'first_group_raw_sample_ns_values_used': raw_sample_value_count_by_group[FIRST_GROUP],
            'raw_row_files_crosschecked': raw_row_file_count,
            'all_49_cases_retained_no_slow_filter': True,
            'n_ge_32_normal_cases': sum(1 for c in case_defs.values() if c['kind'] in NORMAL_KINDS and len(c['x']) >= 32),
            'n_lt_32_normal_cases': sum(1 for c in case_defs.values() if c['kind'] in NORMAL_KINDS and len(c['x']) < 32),
            'n_ge_32_all_cases': sum(1 for c in case_defs.values() if len(c['x']) >= 32),
            'n_lt_32_all_cases': sum(1 for c in case_defs.values() if len(c['x']) < 32),
            'n_1024_cases_included_each_run': sum(1 for c in case_defs.values() if len(c['x']) == 1024),
            'second_group': {'group': SECOND_GROUP, 'runs': len(second), 'records': [{'boundary':r['boundary'],'order':r['order'],'variant':r['variant']} for r in second],
                             'paired': False, 'reason': 'Incomplete ABBA block; excluded from ratios.'},
        },
        'native_and_premeasurement_evidence': {
            'build_exit_code': result['build_exit_code'], 'premeasurement_flags': flag_checks,
            'actual_caller_audit_pass': caller['pass'], 'actual_caller_record_count': len(caller['records']),
            'actual_caller_pass_suffixes': [x['pass_suffix'] for x in caller['records']],
            'native_oracle_exit_code': result['native_oracle_exit_code'],
            'native_dot_cases': native['dots'], 'native_word_round_cases': native['word_rounds'],
            'native_all_complete_words_match': native['all_complete_words_match'],
            'native_expected_accept_miss_match': native['all_expected_accept_miss_match'],
            'native_scope': native['scope'],
        },
        'partial_completion_boundary': {
            'runtime_result_complete': result['complete'], 'stage_receipt_status': stage_receipt['status'],
            'candidate_verdict_stage': candidate_verdict['stage'], 'candidate_verdict_passed': candidate_verdict['passed'],
            'suite_diagnostic_verdict_stage': suite_verdict['stage'], 'suite_diagnostic_verdict_passed': suite_verdict['passed'],
            'full_gate': stage_receipt['full_gate'], 'formal_adoption': stage_receipt['formal_adoption'],
            'nested_candidate_timeout_record': nested_candidate_index.get('r24_statement_timeout'),
            'nested_candidate_replay': nested_candidate_index.get('replay'),
            'nested_candidate_replay_seconds': nested_candidate_index.get('replay_seconds'),
            'outer_suite_replay_exit_code': outer_suite_index.get('replay_exit_code'),
            'outer_suite_replay_seconds': outer_suite_index.get('replay_seconds'),
            'outer_suite_timeout_record': outer_suite_index.get('r24_statement_timeout'),
            'stage_remaining_seconds_at_last_save': result['remaining_seconds'],
            'outer_120_timeout_indexed': True,
            'indexed_final_provenance': indexed_summary['full_final_provenance'],
            'cutoff_scope_resolution': 'Nested candidate index explicitly reports the diagnostic process-group timeout at 120s and 120.004 seconds. The outer suite wrapper separately reports 191.459 seconds and exit 1; these are distinct scopes.',
            'prior_outer_only_lookup_note': 'Earlier first-pass lookup read only the outer suite index (191.459s, no R24 timeout metadata) and marked stop attribution UNKNOWN. That outer-scope note is retained here; the nested candidate index now resolves the 120s candidate timeout.',
            'final_provenance_checks': 'NOT_EXECUTED_AFTER_EXTERNALKILL per development-dot-cost-first-result.json; not evidenced in runtime artifact.',
            'new_full_rerun_with_590_monitor': 'PLANNING_ONLY; not executed here',
        },
        'pairing_protocol': {
            'reference': str(PAIRING_SOURCE.relative_to(REPO)),
            'rule': 'For each boundary: exact order 0 vs eager 1; exact 3 vs eager 2; exact 4 vs lazy 5; exact 7 vs lazy 6.',
            'row_median': 'Median of all three raw sample ns values per case/run.',
            'aggregate_ratio': 'Sum of variant per-case medians divided by sum of control per-case medians; also retain sum of per-case ratios.',
            'lower_than_1': 'Variant is faster in this synthetic paired comparison.',
        },
        'paired_results': paired,
        'two_replicate_descriptive_ranges': combined,
        'interpretation_boundary': [
            'These are two exploratory first-group paired repetitions on an internal own word64/128 control, not the actual former/current champion.',
            'They are neither official score nor proof, adoption, prediction, or success probability.',
            'The incomplete second group is preserved but excluded from paired analysis.',
        ],
    }
    OUT_JSON.write_text(json.dumps(report, indent=2) + '\n', encoding='utf-8')

    lines = [
        '# R24 dot-cost first-group partial analysis', '',
        '**Scope:** exploratory synthetic runtime-cost evidence only. No official score, correctness proof, adoption, or probability claim.', '',
        f"- Parent artifact #{hash_audit['artifact_id']}: all **{hash_audit['matched_file_count']}/119** files matched original SHA-256 and byte-count records; no missing or extra files.",
        f"- Frozen fixture SHA-256 `{fixture_sha}` matches the candidate manifest component. It defines **49 timed cases** for this seed plus directed cases.",
        f"- First group `{FIRST_GROUP}`: **16 complete runs** (8 full, 8 prepared), each with 49 cases × 3 raw ns samples. All `{raw_sample_value_count_by_group[FIRST_GROUP]:,}` first-group sample values were included; no slow-case filter. All 18 stored row files (including two unpaired second-group files) matched `result.json`.",
        f"- Second group `{SECOND_GROUP}` has only full orders 0/1 (exact/eager); it is incomplete and excluded from paired ratios.",
        f"- Source index cross-check: `development-jobs.json` and `development-dot-cost-first-result.json` agree on `{job['status']}`, 18 completed processes, 119 files, and 15,208,417 uncompressed bytes. The CI receipt is completed/failure at the indexed commit.",
        '- Pairing follows the frozen parser: exact 0→eager 1, exact 3→eager 2, exact 4→lazy 5, exact 7→lazy 6, separately for full and prepared.',
        '', '## All 49 cases: paired sum-time ratios', '',
        'Ratio is sum of variant case medians / sum of exact control case medians; below 1 is faster for this pilot. Each cell shows pair 1 / pair 2.', '',
        '| Boundary | Variant | All-49 ratio of sums | Sum of per-case ratios |', '|---|---|---:|---:|',
    ]
    for boundary in ('full','prepared'):
        for variant in ('eager','lazy'):
            vals = [p for p in paired if p['boundary']==boundary and p['variant']==variant]
            a,b = vals
            lines.append(f"| {boundary} | {variant} | {a['all_49']['ratio_of_summed_medians']:.6f} / {b['all_49']['ratio_of_summed_medians']:.6f} | {a['all_49']['sum_of_per_case_ratios']:.4f} / {b['all_49']['sum_of_per_case_ratios']:.4f} |")
    lines += ['', '## Long normal cases (`n ≥ 32`)', '', 'Each cell gives narrow / moderate / wide ratio-of-summed medians; pair 1 / pair 2.', '', '| Boundary | Variant | Narrow | Moderate | Wide |', '|---|---|---:|---:|---:|']
    for boundary in ('full','prepared'):
        for variant in ('eager','lazy'):
            vals = [p for p in paired if p['boundary']==boundary and p['variant']==variant]
            cells=[]
            for kind in ('narrow','moderate','wide'):
                v=[]
                for p in vals:
                    v.append(p['length_rollups']['normal_by_kind_and_n'][f'{kind}_n_ge32']['ratio_of_summed_medians'])
                cells.append(f'{v[0]:.6f} / {v[1]:.6f}')
            lines.append(f'| {boundary} | {variant} | {cells[0]} | {cells[1]} | {cells[2]} |')
    lines += ['', '## Per-case extremes across all 49 cases', '', 'Ratios are variant/control per-case medians; best is the smallest ratio and worst the largest. Pair 1 / pair 2.', '', '| Boundary | Variant | Best case | Worst case |', '|---|---|---|---|']
    for boundary in ('full','prepared'):
        for variant in ('eager','lazy'):
            vals = [p for p in paired if p['boundary']==boundary and p['variant']==variant]
            best=' / '.join(f"{p['per_case_best']['name']} ({p['per_case_best']['ratio']:.6f})" for p in vals)
            worst=' / '.join(f"{p['per_case_worst']['name']} ({p['per_case_worst']['ratio']:.6f})" for p in vals)
            lines.append(f'| {boundary} | {variant} | {best} | {worst} |')
    lines += [
        '', '## Completion and gate boundary', '',
        f"- Build exit 0; compile/link records show no removed files, response shows only `R24DotBarrier.c.o.export` removed, and arguments match after root mapping in all three records. Actual caller audit: {len(caller['records'])}/{len(caller['records'])} records passed.",
        f"- Finite native check exit 0: {native['dots']} dot cases and {native['word_rounds']} word-round cases; all recorded acceptance/miss checks matched. This remains finite checking, not an all-input proof.",
        f"- The runtime result is `complete: {result['complete']}`; stage receipt is `{stage_receipt['status']}`, candidate verdict is `{candidate_verdict['stage']}`, and formal adoption/full gate are false. Final provenance checks are not recorded.",
        f"- The source index marks outer120 timeout/partial18 and `full_final_provenance: {indexed_summary['full_final_provenance']}`. The exact nested candidate index records `{nested_candidate_index.get('replay')}` at {nested_candidate_index.get('replay_seconds')} seconds. Its missing R24-specific timeout metadata is expected from the pre-fix source; the outer suite wrapper separately reports {outer_suite_index.get('replay_seconds')} seconds / exit {outer_suite_index.get('replay_exit_code')}.",
        '- Correction retained: an earlier lookup read only the outer suite wrapper and left stop attribution UNKNOWN. The nested candidate receipt resolves the 120-second cutoff; no upstream raw evidence was changed.',
        '- The 590-second-monitor rerun remains planning only.',
        '', 'Detailed per-pair, per-kind, n-range, best/worst and hash-audit data are in `partial-analysis-results.json` and `partial-analysis-hash-audit.json`.',
    ]
    OUT_MD.write_text('\n'.join(lines) + '\n', encoding='utf-8')
    print(json.dumps({
        'status': report['status'], 'hashes_matched': hash_audit['matched_file_count'],
        'first_group_runs': len(first), 'paired_comparisons': len(paired), 'cases': len(case_defs),
        'first_group_raw_ns_values_used': raw_sample_value_count_by_group[FIRST_GROUP],
        'raw_ns_values_crosschecked': raw_sample_value_count, 'second_group_runs_ignored': len(second),
        'result_json_sha256': report['source_hashes']['result_json_sha256'],
        'fixtures_sha256': fixture_sha, 'output_json': str(OUT_JSON), 'output_md': str(OUT_MD),
    }, indent=2))

if __name__ == '__main__':
    main()
