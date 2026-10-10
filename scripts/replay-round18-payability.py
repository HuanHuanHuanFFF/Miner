"""Separate final public geometry from explicit existing-hotkey payout scenarios."""
from pathlib import Path
import argparse
import hashlib
import json
from round10_payability import analyze_payability, load_flat_rows, load_official_scorer


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--analysis', type=Path, required=True)
    parser.add_argument('--capture', type=Path, required=True)
    parser.add_argument('--output', type=Path, required=True)
    args = parser.parse_args()
    assert not args.output.exists()
    analysis = json.loads(args.analysis.read_bytes())
    competition, context, rows = load_flat_rows(args.capture)
    assert analysis['snapshot']['snapshot_id'] == context['snapshot_id']
    scorer = load_official_scorer()
    policy = competition['policy']
    bounds = scorer.Boundaries(policy['max_balanced_time_ratio'],
                               policy['max_mean_file_compression_pct'])
    scenarios = []
    for candidate in analysis['candidates']:
        for reference_id in ('453', '573'):
            observations = []
            for observation in candidate['observations']:
                replay = analyze_payability(
                    rows, observation['projected_time'], observation['projected_size_pct'],
                    reference_id, scorer, candidate_name='__r18_future__',
                    pareto_share=policy['pareto_share'], improvement_share=policy['improvement_share'],
                    bounds=bounds)
                assert abs(replay['candidate']['geometric_share_pct_of_competition_pareto_pool'] -
                           observation['single_pool_share_pct']) < 1e-10
                same = replay['same_hotkey_payability_if_admission_registration_and_bounty_remain_eligible']
                observations.append({
                    'run_id': observation['run_id'], 'block': observation['block'],
                    'calibration': observation['calibration'],
                    'single_geometric_pool_share_pct': observation['single_pool_share_pct'],
                    'older_same_hotkey_frontier_ids_surviving': same['older_same_hotkey_frontier_ids_surviving'],
                    'oldest_surviving_same_hotkey_id': same['oldest_surviving_same_hotkey_id'],
                    'conditional_candidate_additional_pool_share_pct': same['candidate_additional_share_pct'],
                    'reason': same['reason'],
                })
            scenarios.append({
                'candidate': candidate['candidate'],
                'hypothetical_hotkey_is_the_public_hotkey_of_submission': reference_id,
                'observations': observations,
                'all_candidate_additional_shares_zero': all(
                    o['conditional_candidate_additional_pool_share_pct'] == 0 for o in observations),
            })
    result = {
        'status': 'VERIFIED_OFFICIAL_RULE_REPLAY_CONDITIONAL_OWNERSHIP_SCENARIOS',
        'snapshot': context,
        'analysis_sha256': hashlib.sha256(args.analysis.read_bytes()).hexdigest(),
        'capture_receipt_sha256': hashlib.sha256((args.capture / 'receipt.json').read_bytes()).hexdigest(),
        'scenarios': scenarios,
        'actual_candidate_registration_owner_quota_admission_private_performance_and_payment': 'UNKNOWN_NOT_SUBMITTED',
        'scope': ('453 and573 identify public snapshot ownership groups solely for hypothetical replay; '
                  'this does not verify current user ownership or authorize registration or signing. '
                  'The separately reported single/joint geometric shares assume eligible distinct hotkeys '
                  'without older surviving frontier submissions. A pair on one new shared hotkey would '
                  'also be subject to the oldest-survivor rule. No registration private files are read.'),
    }
    args.output.write_bytes((json.dumps(result, indent=2) + '\n').encode())
    print(json.dumps({'snapshot': context, 'scenarios': [
        {k: v for k, v in scenario.items() if k != 'observations'} for scenario in scenarios]}, indent=2))


if __name__ == '__main__':
    main()
