"""Audit original B12 overlap observations without promoting local gaps to output savings."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import importlib
import json

ROOT = Path(__file__).resolve().parents[1]
NATIVE = ROOT/'evidence/round26/38186466076/overlap-b12-native/diagnostics'
PAIR = {'parse.rs': '5adaaeac471b86128778bf6b67f786542f5c8e079adbf1160f0502309f7befb9',
        'Parse.lean': '51b5ea83cbad026c044b5c7812c9189231f5273cc0902342c850af02a1c0b592'}


def sha(raw):
    return hashlib.sha256(raw).hexdigest()


def rates(counts):
    positions = counts['positions']
    return {
        'valid_prefix_share_of_inherited_guard_pct': 100*counts['byte_valid_positions']/max(1, counts['inherited_guard_positions']),
        'strict_cheaper_covered_domains_per_record_pct': 100*counts['strict_cheaper_covered_domains']/max(1, counts['all_record_visits']),
        'lowprice_original_best_improving_positions_pct': 100*counts['lowprice_best_improving_positions']/max(1, positions),
        'fixedgap_original_best_improving_positions_pct': 100*counts['fixedgap_best_improving_positions']/max(1, positions),
        'either_original_best_improving_positions_pct': 100*counts['either_best_improving_positions']/max(1, positions),
        'diagnostic_extra_queries_per_position': counts['candidate_query_terms']/max(1, positions),
        'diagnostic_prefixcheck_terms_per_position': counts['byte_checked_terms']/max(1, positions),
        'fixedgap_share_of_diagnostic_extra_queries_pct': 100*counts['fixed_only_missing_terms']/max(1, counts['candidate_query_terms']),
        'modeled_packed_gap_units_per_all_position': counts['either_packed_gap_units']/max(1, positions),
    }


def consistent(counts):
    assert counts['byte_valid_positions']+counts['byte_invalid_positions'] == counts['inherited_guard_positions'] == counts['full_match_check_calls']
    assert counts['candidate_query_terms'] == counts['strict_cheaper_covered_terms']+counts['fixed_only_missing_terms']
    assert counts['strict_cheaper_covered_domains'] <= counts['overlap_variable_domains']+counts['overlap_fixed_points'] <= counts['all_record_visits']
    assert counts['eligible_intersection_positions'] <= counts['byte_valid_positions'] <= counts['positions']
    assert max(counts['lowprice_best_improving_positions'], counts['fixedgap_best_improving_positions']) <= counts['either_best_improving_positions']
    assert counts['either_best_improving_positions'] <= counts['lowprice_best_improving_positions']+counts['fixedgap_best_improving_positions']
    assert counts['either_best_improving_positions'] <= counts['eligible_intersection_positions']
    for family in ('lowprice', 'fixedgap', 'either'):
        assert counts[family+'_samecost_tie_positions'] <= counts[family+'_best_improving_positions']


def main():
    inventory = json.loads((NATIVE/'raw-artifact-files.json').read_bytes())['files']
    hashes = {}
    for relative, entry in inventory.items():
        raw = (NATIVE/relative).read_bytes()
        assert len(raw) == entry['bytes'] and sha(raw) == entry['sha256']
        hashes[(NATIVE/relative).relative_to(ROOT).as_posix()] = sha(raw)
    result = json.loads((NATIVE/'r26-b-a-overlap/receipt.json').read_bytes())
    ci = json.loads((NATIVE/'ci-run.json').read_bytes())
    assert result['source_hashes'] == PAIR
    assert str(ci['databaseId']) == result['run_id'] == '38186466076'
    assert result['git_sha'] == ci['headSha'] and ci['headSha'].startswith('ff12b352')
    assert ci['status'] == 'completed' and ci['conclusion'] == 'success'
    module = importlib.import_module('r26-b-a-overlap-diagnostic')
    assert result['observer_sha256'] == sha(module.instrument((ROOT/'references/round24-public-552/parse.rs').read_bytes()))
    old = json.loads((ROOT/'evidence/round26/38182721892/repeat-b9-native/diagnostics/r26-b-a-repeat/receipt.json').read_bytes())
    inputs = {row['file']: row['input_sha256'] for row in old['rows']}
    assert len(result['rows']) == len({row['file'] for row in result['rows']}) == 28
    assert sum(row['raw_bytes'] for row in result['rows']) == 15930000
    for row in result['rows']:
        assert row['input_sha256'] == inputs[row['file']]
        consistent(row['counts'])
    totals = {field: sum(row['counts'][field] for row in result['rows']) for field in module.FIELDS}
    assert totals == result['totals']
    consistent(totals)
    rows = [{**row, 'rates': rates(row['counts'])} for row in result['rows'] if row['counts']['dp_calls']]
    output = {
        'status': 'VERIFIED_B12_RAW_IDENTITY_AND_ORIGINAL_TRAJECTORY_COUNTS',
        'computed_utc': datetime.now(timezone.utc).isoformat(),
        'run_id': result['run_id'], 'git_sha': result['git_sha'], 'source_hashes': PAIR,
        'observer_sha256': result['observer_sha256'], 'totals': totals,
        'rates': rates(totals), 'active_rows': rows,
        'byte_validity': result['proposal_byte_status'],
        'decision': 'REQUIRES_EXPLICIT_COVERAGE_AND_COST_REVIEW_BEFORE_ANY_PRODUCTION_VARIANT',
        'production_cost_boundary': {
            'covered_domains': 'May consume the same original cost/lc loads with two packed comparisons. Cheaper-base substitution needs a reachable-state wrap bound; no duplicate scan presumed mandatory or free.',
            'fixed_only_missing_prefixes': 'Genuine additional offered lengths and reductions; cannot label as only distance replacement.',
            'full_prefix_validation': 'Performed by this observer. Omitting it in production depends on cache-validity/inherited-pair invariant and original obligation acceptance.',
        },
        'limits': ['Original28token/decode equality is asserted by the frozen observer harness; no production edge or encoder quality measurement occurred.',
                   'All A full and sampled DP calls contribute. Repeated positions/passes are not distinct inputs or final chosen tokens.',
                   'Packed gaps and same-cost ties do not establish emitted byte savings, speed gains, formal admission or stable shares.',
                   'No hot pair clocks, no new original-protocol paired timing. Diagnostic operation counts are not total time.',
                   'R8D distance-reselection negative evidence remains applicable context; this observation only checks a different inherited A source.'],
        'raw_input_hashes': hashes,
    }
    path = ROOT/'evidence/round26/route-b/b12-overlap-feedback.json'
    path.write_bytes((json.dumps(output, indent=2)+'\n').encode())
    print(json.dumps({'totals': totals, 'rates': output['rates'], 'byte_validity': output['byte_validity']}, indent=2))


if __name__ == '__main__':
    main()
