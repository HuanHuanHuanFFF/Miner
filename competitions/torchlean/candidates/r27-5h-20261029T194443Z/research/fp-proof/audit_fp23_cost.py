from pathlib import Path
import datetime
import hashlib
import json
import math

H = Path(__file__).resolve().parent
ROOT = next(p for p in H.parents if (p / 'AGENTS.md').is_file())
BASE = H.parent.parent
RESULT_PATH = BASE / 'CI-RESULTS-BATCH8.json'
E = BASE / 'evidence/40970353723/download-e74828874f4f47e09415b05a7ad79a2a'

report = json.loads(RESULT_PATH.read_text())
result = next(x for x in report['results'] if x['candidate'] == 'public23-fp-only-lazy')
plan = json.loads((E / 'plan.json').read_text())
candidate = next(x for x in plan['candidates'] if x['name'] == result['candidate'])
assert candidate['sha256'] == result['candidate_sha256']
entries = {x['path']: x for x in report['outer_hashes']['entries']}
receipts = []
pairs = ns_values = checksum_pairs = 0
binary_hashes = set()

for seed in [27102981, 27102983]:
    stem = f'public23-fp-only-lazy-{seed}'
    measurement = json.loads((E / (stem + '-measurement.json')).read_text())['result']
    assert len(measurement['rounds']) == 5
    assert len(measurement['workloads']) == 6
    binary_hashes.add(measurement['provenance']['candidate_binary'])
    for round_index, round_data in enumerate(measurement['rounds']):
        raw = {}
        for side in ['candidate', 'reference']:
            path = E / f'{stem}-round{round_index}-{side}.json'
            raw[side] = json.loads(path.read_text())
        assert len(round_data['cells']) == 36
        assert set(raw['candidate']) == set(round_data['cells']) == set(raw['reference'])
        for cell, value in round_data['cells'].items():
            assert raw['candidate'][cell] == [value['candidate_ns'], value['candidate_checksum']]
            assert raw['reference'][cell] == [value['reference_ns'], value['reference_checksum']]
            assert value['candidate_ns'] > 0 and value['reference_ns'] > 0
            assert value['candidate_checksum'] == value['reference_checksum']
            pairs += 1
            ns_values += 2
            checksum_pairs += 1
    paths = [E / (stem + '-measurement.json'), E / (stem + '-request.json')]
    paths += [E / f'{stem}-round{i}-{side}.json' for i in range(5) for side in ['candidate', 'reference']]
    for path in paths:
        data = path.read_bytes()
        expected = entries[path.name]
        assert len(data) == expected['bytes']
        assert hashlib.sha256(data).hexdigest() == expected['sha256']
        receipts.append({'path': path.relative_to(ROOT).as_posix(), 'bytes': len(data),
                         'sha256': expected['sha256']})

assert len(binary_hashes) == 1
champion = plan['champion']
estimate = result['score_vs_calibration_internal']['score'] / champion['current_champion_over_calibration']
assert math.isclose(estimate, result['candidate_time_over_current_champion_estimate'], rel_tol=1e-13)
output = {
    'at_utc': datetime.datetime.now(datetime.timezone.utc).isoformat(),
    'state': 'EXACT_FROZEN_FP23_NATIVE_COST_NEGATIVE_PRIMARY_PROOF_EXPANSION_STOPPED',
    'run': report['run'],
    'source_commit': report['source_commit'],
    'candidate_sha256': result['candidate_sha256'],
    'candidate_bytes': candidate['bytes'],
    'own_raw_verification': {'paired_rows': pairs, 'raw_ns_values': ns_values,
                             'checksum_pairs': checksum_pairs, 'all_match': True,
                             'unique_complete_cells': 72, 'rounds_per_cell': 5,
                             'raw_files_sha256_verified': len(receipts)},
    'native_flags_D_fixed_validator': result['native_flags'],
    'candidate_binary': next(iter(binary_hashes)),
    'current_champion_snapshot': champion,
    'candidate_time_over_snapshot43_estimate': estimate,
    'comparison_status': result['champion_comparison'],
    'direct_current_champion_measurement': 'UNKNOWN_CURRENT_SOURCE_PRIVATE',
    'latest_live_rank_refreshed_by_A': False,
    'native_proof_scope': result['candidate_proof'],
    'full_all12_gate': 'NOT_RUN_FOR_FP_CANDIDATE',
    'complete_boundary': 'Full native model call, same flags, actual prepare/check/lazy fallback/output/drop costs per D protocol; not isolated MAC timing.',
    'decision': 'Stop broad actual FP producer/whole-kernel proof and further same-mechanism cost queue this round. Preserve 19 accepted generic roots and pre-freeze independent follow-on material. No claim that every future FP mechanism fails.',
    'new_behavior_tuning_from_this_data': False,
    'frozen_artifacts_changed': False,
    'not_inherited': 'Unmeasured preplanned b1 guard6a134 or checked-getter/four-output alternatives do not inherit this exact-source timing or proof.',
    'source_result_sha256': hashlib.sha256(RESULT_PATH.read_bytes()).hexdigest(),
    'raw_evidence': receipts,
    'profile_boundary': report['profile_boundary'],
    'profile_usage': 'Three-entry public23 instrumented shares are not whole-model/current-champion or FP-MAC fractions; not used to infer optimizer speed.',
    'attempt_history': 'Initial inline audit script had a Python syntax error before execution; this persisted readable version performed all checks.'
}
(H / 'FP23-COST-NEGATIVE-RECEIPT.json').write_text(json.dumps(output, indent=2) + '\n')
print(json.dumps({'paired_rows': pairs, 'ns_values': ns_values, 'checksum_pairs': checksum_pairs,
                  'candidate_time_over_snapshot43_estimate': estimate,
                  'scope': 'INFERRED_SCREEN_NOT_DIRECT_CHAMPION_MEASUREMENT'}, indent=2))
