"""Audit B16 full-D-forward actual quality and complete D coarse cost, no timing promotion."""
from pathlib import Path
from datetime import datetime, timezone
import argparse
import hashlib
import json

ROOT = Path(__file__).resolve().parents[1]
PARENT = 'public552'
CANDIDATE = 'r26-b-552-dense-forward'
EXPECTED = '01bc288459303be392ed19f026443835a8c69aec5fa525eec40316aa4bd7beca'
PARENT_RUST = '5adaaeac471b86128778bf6b67f786542f5c8e079adbf1160f0502309f7befb9'
LEAN = '51b5ea83cbad026c044b5c7812c9189231f5273cc0902342c850af02a1c0b592'


def sha(raw):
    return hashlib.sha256(raw).hexdigest()


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('run_id')
    args = parser.parse_args()
    assert args.run_id.isdigit()
    native = ROOT/'evidence/round26'/args.run_id/'dense-b16-native/diagnostics'
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
    priorpath = ROOT/'evidence/round26/38181703981/dfront-b8-native/diagnostics/r18-functions/functions.json'
    priorraw = priorpath.read_bytes()
    prior = json.loads(priorraw)
    hashes[priorpath.relative_to(ROOT).as_posix()] = sha(priorraw)
    original = {row['file']: row for row in prior['rows']}
    phases = {row['file']: row for row in profile['rows']}
    assert len(parent) == len(candidate) == len(phases) == len(original) == 28
    assert sum(row['raw_bytes'] for row in parent.values()) == 15930000
    rows = []
    for name, old in parent.items():
        new = candidate[name]
        assert old['input_sha256'] == new['input_sha256'] == original[name]['input_sha256'] == phases[name]['input_sha256']
        assert old['raw_bytes'] == new['raw_bytes']
        active = original[name]['functions']['d_parse']['calls'] > 0
        identical = all(old[key] == new[key] for key in ['tokens','tokens_sha256','output_bytes','output_sha256'])
        assert active or identical
        delta = new['output_bytes']-old['output_bytes']
        rows.append({'file':name, 'input_sha256':old['input_sha256'], 'raw_bytes':old['raw_bytes'],
                     'actual_original_D_path':active, 'token_and_output_identity':identical,
                     'output_bytes_delta':delta, 'tokens_delta':new['tokens']-old['tokens'],
                     'mean_quality_pp_delta':100*delta/old['raw_bytes']/28,
                     'parent':old, 'candidate':new, 'candidate_coarse_phases':phases[name]['functions'],
                     'original_B8_coarse_phases':original[name]['functions']})
    quality_delta = sum(row['mean_quality_pp_delta'] for row in rows)
    result = {
        'status':'VERIFIED_B16_RAW_ORIGINAL_ENCODER_QUALITY_AND_COARSE_COST',
        'computed_utc':datetime.now(timezone.utc).isoformat(), 'run_id':args.run_id,
        'git_sha':ci['headSha'], 'source_hashes':encoder['source_hashes'][CANDIDATE],
        'actual_output_bytes_delta':sum(row['output_bytes_delta'] for row in rows),
        'actual_mean_quality_delta_pp':quality_delta,
        'parent_public_size_pct':sum(100*row['output_bytes']/row['raw_bytes'] for row in parent.values())/28,
        'candidate_public_size_pct':sum(100*row['output_bytes']/row['raw_bytes'] for row in candidate.values())/28,
        'non_D_identity_files':[row['file'] for row in rows if not row['actual_original_D_path']],
        'changed_files':[row['file'] for row in rows if not row['token_and_output_identity']],
        'candidate_complete_coarse_work':profile['totals'], 'rows':rows,
        'decision':'NO_GO_B16_PAIRED_AND_PROOF: actual+80B/+0.00067397305pp is a quality regression. CompleteDcost retained; stop exactfull-domain restoration, no flen sweep.',
        'raw_input_hashes':hashes,
        'limits':['All deltas use the actual public552 parent, not the first public514 reference in the generic encoder summary.',
                  'Original encoder finite decode and candidate-frozen profiler token identity do not establish original obligations or full gate.',
                  'B8 prior-trajectory omitted6.62M lengths are not measuredB16 newwrites or recoverablebytes. Denseforward may change initialplan/prices/refinement/encodercontext.',
                  'Complete production D phases include actual denseforward/newbacktracking/tally/backDP/extract. Nested phases cannot be added; no hotrelax timer.',
                  'No same-plan or all-matching-graph equivalence is assumed from changing only onehelper; sourceimplementation/budgets retained and output is intentionally different.',
                  'Native instrumented clocks across jobs are not original-protocol speed or a stable share. No paired, independentconfirmation, formal admission or reward result.'],
    }
    output = ROOT/'evidence/round26/route-b/b16-dense-forward-feedback.json'
    output.write_bytes((json.dumps(result,indent=2)+'\n').encode())
    print(json.dumps({key:result[key] for key in ['actual_output_bytes_delta','actual_mean_quality_delta_pp','parent_public_size_pct','candidate_public_size_pct','decision']},indent=2))
    print(json.dumps([{key:row[key] for key in ['file','output_bytes_delta','tokens_delta','mean_quality_pp_delta']} for row in rows if not row['token_and_output_identity']],indent=2))


if __name__=='__main__':
    main()
