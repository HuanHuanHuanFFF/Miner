"""Direct B10 encoder deltas versus exact #552, never versus first514 control."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json

ROOT = Path(__file__).resolve().parents[1]
NATIVE = ROOT / 'evidence/round26/38183515701/greedy-b10-native/diagnostics'
PARENT = 'public552'
CANDIDATE = 'r26-b-552-greedy-fit'
EXPECTED_PARENT = '5adaaeac471b86128778bf6b67f786542f5c8e079adbf1160f0502309f7befb9'
EXPECTED_CANDIDATE = 'd483514a06a7a614aa1e8ffe15120eddb3b03e2b6ef56c4763bb8a2b26ef08b5'


def sha(raw):
    return hashlib.sha256(raw).hexdigest()


def main():
    inventory = json.loads((NATIVE / 'raw-artifact-files.json').read_bytes())['files']
    inputs, loaded = {}, {}
    for file in ['r13-encoder/encoder.json', 'r18-functions/functions.json', 'execution-start.json']:
        raw = (NATIVE / file).read_bytes()
        assert len(raw) == inventory[file]['bytes'] and sha(raw) == inventory[file]['sha256']
        loaded[file] = json.loads(raw)
        inputs[(NATIVE / file).relative_to(ROOT).as_posix()] = sha(raw)
    encoder = loaded['r13-encoder/encoder.json']
    profile = loaded['r18-functions/functions.json']
    ci = json.loads((NATIVE / 'ci-run.json').read_bytes())
    assert str(ci['databaseId']) == encoder['run_id'] == profile['run_id'] == '38183515701'
    assert ci['headSha'] == encoder['git_sha'] == profile['git_sha']
    assert ci['status'] == 'completed' and ci['conclusion'] == 'success'
    assert encoder['source_hashes'][PARENT]['parse.rs'] == EXPECTED_PARENT
    assert encoder['source_hashes'][CANDIDATE]['parse.rs'] == EXPECTED_CANDIDATE
    assert profile['source_hashes'] == encoder['source_hashes'][CANDIDATE]
    parent = {row['file']: row for row in encoder['rows'] if row['candidate'] == PARENT}
    candidate = {row['file']: row for row in encoder['rows'] if row['candidate'] == CANDIDATE}
    previous_path = ROOT / 'evidence/round26/38182721892/repeat-b9-native/diagnostics/r26-b-a-repeat/receipt.json'
    previous_raw = previous_path.read_bytes()
    original_A = json.loads(previous_raw)
    active_files = {row['file'] for row in original_A['rows'] if row['counts']['a_engine_calls']}
    inputs[previous_path.relative_to(ROOT).as_posix()] = sha(previous_raw)
    assert len(parent) == len(candidate) == 28 and sum(row['raw_bytes'] for row in parent.values()) == 15930000
    rows = []
    for name, old in parent.items():
        new = candidate[name]
        assert (old['raw_bytes'], old['input_sha256']) == (new['raw_bytes'], new['input_sha256'])
        identity = all(old[key] == new[key] for key in ['tokens', 'tokens_sha256', 'output_bytes', 'output_sha256'])
        assert name in active_files or identity
        rows.append({'file': name, 'raw_bytes': old['raw_bytes'], 'input_sha256': old['input_sha256'],
                     'actual_original_A_path': name in active_files, 'token_and_output_identity': identity,
                     'extra_output_bytes': new['output_bytes'] - old['output_bytes'],
                     'token_count_delta': new['tokens'] - old['tokens'],
                     'mean_quality_pp_contribution': 100 * (new['output_bytes'] - old['output_bytes']) / old['raw_bytes'] / 28,
                     'parent': old, 'candidate': new})
    parse_ns = profile['totals']['parse']['inclusive_ns']
    result = {
        'status': 'VERIFIED_B10_ORIGINAL_ENCODER_PATH_AND_COARSE_WORK_FEEDBACK',
        'computed_utc': datetime.now(timezone.utc).isoformat(), 'run_id': encoder['run_id'],
        'git_sha': encoder['git_sha'], 'source_hashes': encoder['source_hashes'][CANDIDATE],
        'output_bytes_change': sum(row['extra_output_bytes'] for row in rows),
        'mean_quality_change_pp': sum(row['mean_quality_pp_contribution'] for row in rows),
        'parent_public_size_pct': sum(100 * row['output_bytes'] / row['raw_bytes'] for row in parent.values()) / 28,
        'candidate_public_size_pct': sum(100 * row['output_bytes'] / row['raw_bytes'] for row in candidate.values()) / 28,
        'changed_A_files': [row['file'] for row in rows if not row['token_and_output_identity']],
        'identical_non_A_files': [row['file'] for row in rows if not row['actual_original_A_path']],
        'rows': rows,
        'actual_candidate_coarse_work': {name: {'calls': value['calls'], 'inclusive_s': value['inclusive_ns'] / 1e9,
                                               'percent_observed_parse_seconds': 100 * value['inclusive_ns'] / parse_ns}
                                          for name, value in profile['totals'].items()},
        'decision': 'NO_GO exactB10 originalpaired/proof: actual+.039518pp quality loss moves target geometry far beyond this fit-stage opportunity. Retain fixed candidate and negative evidence. A model-source quality failure, not a decoder/safety failure or universal rejection of all statistical-fit mechanisms.',
        'input_hashes': inputs,
        'limits': ['Encoder summary changed_files uses firstcontrol public514; all reported deltas here are recomputed from actual28rows against exactpublic552.',
                   'Original A membership is verified from B9 real parent trajectory. All21non-A files preserve fulltoken/output identities.',
                   'Coarse clocks include all actual newfit/finalDP/finder/initial-model/construct work. Nested A/parse and child times are not additive gains.',
                   'Different diagnostic runs cannot establish originalpaired speed. No pairedconfirmation/fullgate/formal admission or reward.'],
    }
    target = ROOT / 'evidence/round26/route-b/b10-greedy-feedback.json'
    target.write_bytes((json.dumps(result, indent=2) + '\n').encode())
    print(json.dumps({key: result[key] for key in ['output_bytes_change', 'mean_quality_change_pp',
                                                'parent_public_size_pct', 'candidate_public_size_pct', 'changed_A_files']}))
    print(json.dumps([{key: row[key] for key in ['file', 'extra_output_bytes', 'token_count_delta', 'mean_quality_pp_contribution']}
                      for row in rows if not row['token_and_output_identity']], indent=2))


if __name__ == '__main__':
    main()
