"""Audit B14 sparse-source/consumer receipts without extrapolating subset gaps."""
from pathlib import Path
from datetime import datetime, timezone
import argparse
import hashlib
import importlib
import json

ROOT = Path(__file__).resolve().parents[1]
PAIR = {'parse.rs':'5adaaeac471b86128778bf6b67f786542f5c8e079adbf1160f0502309f7befb9',
        'Parse.lean':'51b5ea83cbad026c044b5c7812c9189231f5273cc0902342c850af02a1c0b592'}


def sha(raw):
    return hashlib.sha256(raw).hexdigest()


def consistent(c):
    assert c['discarded_codes_before_dedup'] == c['samecode_fullprefix_redundant_codes']+c['novel_codes_after_dedup']
    assert c['novel_codes_after_dedup'] == c['prefix_check_calls'] == c['byte_valid_candidates']+c['byte_invalid_candidates']
    assert c['stored_sparse_records'] == c['byte_valid_candidates']
    assert c['sparse_logical_bytes'] == c['stored_sparse_records']*8 <= c['sum_final_capacity_bytes']
    assert c['selected_tree_positions'] <= c['tree_search_positions']
    assert c['slot_reset_writes'] == c['selected_tree_positions']*64
    assert c['original_best_improving_positions'] <= c['sampled_dp_positions_with_cache'] <= c['dp_positions']
    assert c['samecost_tie_positions'] <= c['original_best_improving_positions']
    assert c['cheaper_domain_pairs'] <= c['novel_length_candidate_domains'] <= c['consumer_sparse_record_visits']
    assert c['query_terms'] >= c['cheaper_domain_pairs']


def rates(c):
    return {
        'selected_search_position_pct':100*c['selected_tree_positions']/max(1,c['tree_search_positions']),
        'samecode_source_redundant_candidate_pct':100*c['samecode_fullprefix_redundant_codes']/max(1,c['discarded_codes_before_dedup']),
        'novel_retained_codes_per_selected_search_position':c['stored_sparse_records']/max(1,c['selected_tree_positions']),
        'true_price_improvement_positions':c['original_best_improving_positions']-c['samecost_tie_positions'],
        'true_price_improvement_pct_of_examined_dp_cache_positions':100*(c['original_best_improving_positions']-c['samecost_tie_positions'])/max(1,c['sampled_dp_positions_with_cache']),
        'diagnostic_queries_per_examined_dp_cache_position':c['query_terms']/max(1,c['sampled_dp_positions_with_cache']),
        'samecost_tie_share_of_improvement_pct':100*c['samecost_tie_positions']/max(1,c['original_best_improving_positions']),
        'consumer_records_per_examined_dp_cache_position':c['consumer_sparse_record_visits']/max(1,c['sampled_dp_positions_with_cache']),
    }


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('run_id')
    args = parser.parse_args()
    assert args.run_id.isdigit()
    native = ROOT/'evidence/round26'/args.run_id/'discard-b14-native/diagnostics'
    inventory = json.loads((native/'raw-artifact-files.json').read_bytes())['files']
    hashes = {}
    for relative,entry in inventory.items():
        raw=(native/relative).read_bytes()
        assert len(raw)==entry['bytes'] and sha(raw)==entry['sha256']
        hashes[(native/relative).relative_to(ROOT).as_posix()]=sha(raw)
    receipt=json.loads((native/'r26-b-a-discarded/receipt.json').read_bytes())
    ci=json.loads((native/'ci-run.json').read_bytes())
    assert receipt['source_hashes']==PAIR
    assert str(ci['databaseId'])==receipt['run_id']==args.run_id and ci['headSha']==receipt['git_sha']
    assert ci['status']=='completed' and ci['conclusion']=='success'
    module=importlib.import_module('r26-b-a-discarded-diagnostic')
    assert sha(module.instrument((ROOT/'references/round24-public-552/parse.rs').read_bytes()))==receipt['observer_sha256']
    b12path=ROOT/'evidence/round26/38186466076/overlap-b12-native/diagnostics/r26-b-a-overlap/receipt.json'
    original=json.loads(b12path.read_bytes())
    hashes[b12path.relative_to(ROOT).as_posix()]=sha(b12path.read_bytes())
    inputs={row['file']:row for row in original['rows']}
    planned=json.loads((ROOT/'evidence/round26/route-b/a-discarded-sample-plan.json').read_bytes())
    maximum={row['file']:row for row in planned['rows']}
    assert len(receipt['rows'])==len({row['file'] for row in receipt['rows']})==28
    assert sum(row['raw_bytes'] for row in receipt['rows'])==15930000
    for row in receipt['rows']:
        assert row['input_sha256']==inputs[row['file']]['input_sha256']
        consistent(row['counts'])
        assert row['counts']['dp_calls']==inputs[row['file']]['counts']['dp_calls']
        assert row['counts']['dp_positions']==inputs[row['file']]['counts']['positions']
        if row['file'] in maximum:
            assert row['counts']['selected_tree_positions']<=maximum[row['file']]['deterministic_selected_positions']
            assert row['counts']['sparse_logical_bytes']<=maximum[row['file']]['worst_sparse30code_logical_bytes']
        else:
            assert not any(row['counts'].values())
    totals={field:sum(row['counts'][field] for row in receipt['rows']) for field in module.FIELDS}
    assert totals==receipt['totals']
    consistent(totals)
    result={
        'status':'VERIFIED_B14_RAW_FIXED_SUBSET_NOVEL_SOURCE_AND_CONSUMER_ACCOUNTING',
        'computed_utc':datetime.now(timezone.utc).isoformat(),'run_id':args.run_id,'git_sha':receipt['git_sha'],
        'source_hashes':PAIR,'observer_sha256':receipt['observer_sha256'],
        'totals':totals,'rates':rates(totals),
        'byte_validity':receipt['proposal_byte_status'],
        'max_perfile_final_capacity_bytes':max(row['counts']['sum_final_capacity_bytes'] for row in receipt['rows']),
        'active_rows':[{**row,'rates':rates(row['counts'])} for row in receipt['rows'] if row['counts']['finder_calls']],
        'decision':'REQUIRES_EXPLICIT_TRUE_PRICE_COVERAGE_AND_PRODUCTION_COST_REVIEW; no output extrapolation',
        'raw_input_hashes':hashes,
        'limits':['Sample fixed before result; only this subset was examined. Fractions use explicitly examined original DP cache positions, not a representative-input probability.',
                  'Per-pass repeated positions/candidates are distinct workload observations, not new independent inputs or final selected tokens.',
                  'Both cached complete-prefix samecode availability and inherited samecode availability are excluded; existing-source missing offers intentionally outside this new-source test.',
                  'All28 originaltokens/decode identity is asserted by the exact observer harness. No original encoder variant or byte/speed/formal/proof result.',
                  'Logical/cache-capacity totals are not RSS; maintenance/cursor scans/query counts are not assumed free production costs.',
                  'Packed gaps cannot be added to predict output bytes, even when every sampled new prefix is valid.'],
    }
    path=ROOT/'evidence/round26/route-b/b14-discarded-feedback.json'
    path.write_bytes((json.dumps(result,indent=2)+'\n').encode())
    print(json.dumps({key:result[key] for key in ['totals','rates','byte_validity','max_perfile_final_capacity_bytes']},indent=2))


if __name__=='__main__':
    main()
