"""Audit B15 quality, pure production coarse cost and independent actual tagged graph."""
from pathlib import Path
from datetime import datetime, timezone
import argparse
import hashlib
import json

ROOT = Path(__file__).resolve().parents[1]
PARENT = 'public552'
CANDIDATE = 'r26-b-552-discarded'
EXPECTED = '8974acb8e1c1087d1b4560fd2dc451d8d19c6e3e6f81905b81e9df9a3be4ecdf'
PARENT_RUST = '5adaaeac471b86128778bf6b67f786542f5c8e079adbf1160f0502309f7befb9'
LEAN = '51b5ea83cbad026c044b5c7812c9189231f5273cc0902342c850af02a1c0b592'


def sha(raw):
    return hashlib.sha256(raw).hexdigest()


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('run_id')
    args = parser.parse_args()
    assert args.run_id.isdigit()
    native = ROOT/'evidence/round26'/args.run_id/'discard-b15-native/diagnostics'
    inventory = json.loads((native/'raw-artifact-files.json').read_bytes())['files']
    hashes = {}
    for relative, entry in inventory.items():
        raw = (native/relative).read_bytes()
        assert len(raw) == entry['bytes'] and sha(raw) == entry['sha256']
        hashes[(native/relative).relative_to(ROOT).as_posix()] = sha(raw)
    encoder = json.loads((native/'r13-encoder/encoder.json').read_bytes())
    profile = json.loads((native/'r18-functions/functions.json').read_bytes())
    graph = json.loads((native/'r26-b-tag-graph/receipt.json').read_bytes())
    ci = json.loads((native/'ci-run.json').read_bytes())
    assert str(ci['databaseId']) == encoder['run_id'] == profile['run_id'] == args.run_id
    assert ci['headSha'] == encoder['git_sha'] == profile['git_sha']
    assert graph['run_id'] == args.run_id and graph['git_sha'] == ci['headSha']
    assert ci['status'] == 'completed' and ci['conclusion'] == 'success'
    assert encoder['source_hashes'][PARENT] == {'parse.rs': PARENT_RUST, 'Parse.lean': LEAN}
    assert encoder['source_hashes'][CANDIDATE] == profile['source_hashes'] == {'parse.rs': EXPECTED, 'Parse.lean': LEAN}
    assert graph['source_hashes'] == profile['source_hashes'] and graph['parent_hashes'] == encoder['source_hashes'][PARENT]
    parent = {row['file']: row for row in encoder['rows'] if row['candidate'] == PARENT}
    candidate = {row['file']: row for row in encoder['rows'] if row['candidate'] == CANDIDATE}
    b12path = ROOT/'evidence/round26/38186466076/overlap-b12-native/diagnostics/r26-b-a-overlap/receipt.json'
    b12raw = b12path.read_bytes()
    b12 = json.loads(b12raw)
    hashes[b12path.relative_to(ROOT).as_posix()] = sha(b12raw)
    original = {row['file']: row for row in b12['rows']}
    phases = {row['file']: row for row in profile['rows']}
    graphs = {row['file']: row for row in graph['rows']}
    assert len(parent) == len(candidate) == len(phases) == len(original) == 28
    assert sum(row['raw_bytes'] for row in parent.values()) == 15930000
    rows = []
    for name, old in parent.items():
        new = candidate[name]
        assert old['input_sha256'] == new['input_sha256'] == original[name]['input_sha256'] == phases[name]['input_sha256'] == graphs[name]['input_sha256']
        assert old['raw_bytes'] == new['raw_bytes']
        active = original[name]['counts']['dp_calls'] > 0
        identical = all(old[key] == new[key] for key in ['tokens','tokens_sha256','output_bytes','output_sha256'])
        assert active or identical
        g = graphs[name]
        assert g['counts']['tagged_records'] == g['counts']['tagged_bytevalid_records']
        assert len(g['actual_finder_contexts']) == g['counts']['finder_calls']
        assert sum(c['original_record_words'] for c in g['actual_finder_contexts']) == g['counts']['preserved_original_records']
        assert sum(c['new_record_words']-c['original_record_words'] for c in g['actual_finder_contexts']) == g['counts']['tagged_records']
        assert active or not any(g['counts'].values())
        delta = new['output_bytes']-old['output_bytes']
        rows.append({'file':name, 'input_sha256':old['input_sha256'], 'raw_bytes':old['raw_bytes'],
                     'actual_original_A_path':active, 'token_and_output_identity':identical,
                     'output_bytes_delta':delta, 'tokens_delta':new['tokens']-old['tokens'],
                     'mean_quality_pp_delta':100*delta/old['raw_bytes']/28,
                     'parent':old, 'candidate':new, 'candidate_coarse_phases':phases[name]['functions'],
                     'original_B12_local_counts':original[name]['counts'], 'native_graph_integrity':g})
    quality_delta = sum(row['mean_quality_pp_delta'] for row in rows)
    result = {
        'status':'VERIFIED_B15_RAW_ORIGINAL_ENCODER_QUALITY_AND_COARSE_COST',
        'computed_utc':datetime.now(timezone.utc).isoformat(), 'run_id':args.run_id,
        'git_sha':ci['headSha'], 'source_hashes':encoder['source_hashes'][CANDIDATE],
        'actual_output_bytes_delta':sum(row['output_bytes_delta'] for row in rows),
        'actual_mean_quality_delta_pp':quality_delta,
        'parent_public_size_pct':sum(100*row['output_bytes']/row['raw_bytes'] for row in parent.values())/28,
        'candidate_public_size_pct':sum(100*row['output_bytes']/row['raw_bytes'] for row in candidate.values())/28,
        'non_A_identity_files':[row['file'] for row in rows if not row['actual_original_A_path']],
        'changed_files':[row['file'] for row in rows if not row['token_and_output_identity']],
        'candidate_complete_coarse_work':profile['totals'], 'rows':rows,
        'native_tag_graph_totals':graph['totals'], 'max_perfile_new_graph_capacity_bytes':graph['max_perfile_new_graph_capacity_bytes'],
        'native_graph_status':graph['status'],
        'decision':'NO_GO_B15_PAIRED_AND_PROOF: actual21byte gain is micro despite9.31M newrecords and complete extraDPwork. Root confirms stop this frozen variant; no price/retention threshold sweeps.',
        'raw_input_hashes':hashes,
        'limits':['All deltas use the actual public552 parent, not the first public514 reference in the generic encoder summary.',
                  'Original encoder finite decode and candidate-frozen profiler token identity do not establish original obligations or full gate.',
                  'Original B12/B14 trajectories and fixedsubset gaps are not causal output deltas after refitting/segment changes, and are not extrapolated to all positions.',
                  'Pure production finder/DP phases contain epoch/touched maintenance, cache append/growth, suffix stripping and exact extra queries. Nested phases are not additive savings; no hothelper clock.',
                  'Independent graph observer recomputes parent at actual args and checks all taggedprefixes; these extra check/recomputation costs do not enter the production profiler.',
                  'Actual public graph identity/prefix validity is finite, not universal equivalence or accepted originalobligation.',
                  'Native instrumented clocks across jobs are not original-protocol speed or a stable share. No paired, independentconfirmation, formal admission or reward result.'],
    }
    output = ROOT/'evidence/round26/route-b/b15-discarded-feedback.json'
    output.write_bytes((json.dumps(result,indent=2)+'\n').encode())
    print(json.dumps({key:result[key] for key in ['actual_output_bytes_delta','actual_mean_quality_delta_pp','parent_public_size_pct','candidate_public_size_pct','decision']},indent=2))
    print(json.dumps([{key:row[key] for key in ['file','output_bytes_delta','tokens_delta','mean_quality_pp_delta']} for row in rows if not row['token_and_output_identity']],indent=2))


if __name__=='__main__':
    main()
