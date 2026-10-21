"""Audit B13 original-encoder results and complete coarse A cost after raw collection."""
from pathlib import Path
from datetime import datetime, timezone
import argparse
import hashlib
import json

ROOT = Path(__file__).resolve().parents[1]
PARENT = 'public552'
CANDIDATE = 'r26-b-552-overlap-select'
EXPECTED = '9e0aa3b25acb32bd440b016dd1aa7f72a71faf11d795f50b37b0bd341e7df029'
PARENT_RUST = '5adaaeac471b86128778bf6b67f786542f5c8e079adbf1160f0502309f7befb9'
LEAN = '51b5ea83cbad026c044b5c7812c9189231f5273cc0902342c850af02a1c0b592'


def sha(raw):
    return hashlib.sha256(raw).hexdigest()


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('run_id')
    args = parser.parse_args()
    assert args.run_id.isdigit()
    native = ROOT/'evidence/round26'/args.run_id/'select-b13-native/diagnostics'
    inventory = json.loads((native/'raw-artifact-files.json').read_bytes())['files']
    hashes = {}
    for relative, entry in inventory.items():
        raw = (native/relative).read_bytes()
        assert len(raw) == entry['bytes'] and sha(raw) == entry['sha256']
        hashes[(native/relative).relative_to(ROOT).as_posix()] = sha(raw)
    encoder = json.loads((native/'r13-encoder/encoder.json').read_bytes())
    profile = json.loads((native/'r18-functions/functions.json').read_bytes())
    ci = json.loads((native/'ci-run.json').read_bytes())
    assert str(ci['databaseId']) == encoder['run_id'] == profile['run_id'] == args.run_id
    assert ci['headSha'] == encoder['git_sha'] == profile['git_sha']
    assert ci['status'] == 'completed' and ci['conclusion'] == 'success'
    assert encoder['source_hashes'][PARENT] == {'parse.rs': PARENT_RUST, 'Parse.lean': LEAN}
    assert encoder['source_hashes'][CANDIDATE] == profile['source_hashes'] == {'parse.rs': EXPECTED, 'Parse.lean': LEAN}
    parent = {row['file']: row for row in encoder['rows'] if row['candidate'] == PARENT}
    candidate = {row['file']: row for row in encoder['rows'] if row['candidate'] == CANDIDATE}
    b12path = ROOT/'evidence/round26/38186466076/overlap-b12-native/diagnostics/r26-b-a-overlap/receipt.json'
    b12raw = b12path.read_bytes()
    b12 = json.loads(b12raw)
    hashes[b12path.relative_to(ROOT).as_posix()] = sha(b12raw)
    original = {row['file']: row for row in b12['rows']}
    phases = {row['file']: row for row in profile['rows']}
    assert len(parent) == len(candidate) == len(phases) == len(original) == 28
    assert sum(row['raw_bytes'] for row in parent.values()) == 15930000
    rows = []
    for name, old in parent.items():
        new = candidate[name]
        assert old['input_sha256'] == new['input_sha256'] == original[name]['input_sha256'] == phases[name]['input_sha256']
        assert old['raw_bytes'] == new['raw_bytes']
        active = original[name]['counts']['dp_calls'] > 0
        identical = all(old[key] == new[key] for key in ['tokens','tokens_sha256','output_bytes','output_sha256'])
        assert active or identical
        delta = new['output_bytes']-old['output_bytes']
        rows.append({'file':name, 'input_sha256':old['input_sha256'], 'raw_bytes':old['raw_bytes'],
                     'actual_original_A_path':active, 'token_and_output_identity':identical,
                     'output_bytes_delta':delta, 'tokens_delta':new['tokens']-old['tokens'],
                     'mean_quality_pp_delta':100*delta/old['raw_bytes']/28,
                     'parent':old, 'candidate':new, 'candidate_coarse_phases':phases[name]['functions'],
                     'original_B12_local_counts':original[name]['counts']})
    quality_delta = sum(row['mean_quality_pp_delta'] for row in rows)
    result = {
        'status':'VERIFIED_B13_RAW_ORIGINAL_ENCODER_QUALITY_AND_COARSE_COST',
        'computed_utc':datetime.now(timezone.utc).isoformat(), 'run_id':args.run_id,
        'git_sha':ci['headSha'], 'source_hashes':encoder['source_hashes'][CANDIDATE],
        'actual_output_bytes_delta':sum(row['output_bytes_delta'] for row in rows),
        'actual_mean_quality_delta_pp':quality_delta,
        'parent_public_size_pct':sum(100*row['output_bytes']/row['raw_bytes'] for row in parent.values())/28,
        'candidate_public_size_pct':sum(100*row['output_bytes']/row['raw_bytes'] for row in candidate.values())/28,
        'non_A_identity_files':[row['file'] for row in rows if not row['actual_original_A_path']],
        'changed_files':[row['file'] for row in rows if not row['token_and_output_identity']],
        'candidate_complete_coarse_work':profile['totals'], 'rows':rows,
        'decision':'PENDING_ROOT_SAME_SNAPSHOT_QUALITY_GEOMETRY_AND_COST_REVIEW' if quality_delta<0 else 'NO_GO_QUALITY_CHECKPOINT: no aggregate quality gain; do not add price thresholds or restore fixedgap',
        'raw_input_hashes':hashes,
        'limits':['All deltas use the actual public552 parent, not the first public514 reference in the generic encoder summary.',
                  'Original encoder finite decode and candidate-frozen profiler token identity do not establish original obligations or full gate.',
                  'The original B12 trajectory is a different pre-change path. Its local price gaps are not causal explanations of output deltas after refitting and segment changes.',
                  'Coarse A DP contains guard, carriedprice, helper and unchangedpasses; nested phases are not additive savings and no hothelper clock was used.',
                  'Native instrumented clocks across jobs are not original-protocol speed or a stable share. No paired, independentconfirmation, formal admission or reward result.'],
    }
    output = ROOT/'evidence/round26/route-b/b13-select-feedback.json'
    output.write_bytes((json.dumps(result,indent=2)+'\n').encode())
    print(json.dumps({key:result[key] for key in ['actual_output_bytes_delta','actual_mean_quality_delta_pp','parent_public_size_pct','candidate_public_size_pct','decision']},indent=2))
    print(json.dumps([{key:row[key] for key in ['file','output_bytes_delta','tokens_delta','mean_quality_pp_delta']} for row in rows if not row['token_and_output_identity']],indent=2))


if __name__=='__main__':
    main()
