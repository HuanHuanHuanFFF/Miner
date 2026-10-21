"""Describe exact B8 work and a separately labeled historical paired-weight model."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import importlib
import json

ROOT = Path(__file__).resolve().parents[1]
EXPECTED = '5adaaeac471b86128778bf6b67f786542f5c8e079adbf1160f0502309f7befb9'
NATIVE = ROOT / 'evidence/round26/38181703981/dfront-b8-native/diagnostics'
HISTORY = ROOT / 'evidence/round24/38082906439/screen-h/gate'


def sha(raw):
    return hashlib.sha256(raw).hexdigest()


def main():
    inventory = json.loads((NATIVE / 'raw-artifact-files.json').read_bytes())['files']
    inputs = {}
    loaded = {}
    for path in ['r26-b-d-front/receipt.json', 'r18-functions/functions.json']:
        raw = (NATIVE / path).read_bytes()
        assert len(raw) == inventory[path]['bytes'] and sha(raw) == inventory[path]['sha256']
        loaded[path] = json.loads(raw)
        inputs[(NATIVE / path).relative_to(ROOT).as_posix()] = sha(raw)
    counts = loaded['r26-b-d-front/receipt.json']
    profile = loaded['r18-functions/functions.json']
    assert counts['source_hashes']['parse.rs'] == EXPECTED == profile['source_hashes']['parse.rs']
    assert counts['run_id'] == profile['run_id'] == '38181703981'
    assert counts['git_sha'] == profile['git_sha']
    by_file = {row['file']: row for row in profile['rows']}
    assert {row['file']: row['input_sha256'] for row in counts['rows']} == {
        name: row['input_sha256'] for name, row in by_file.items()}
    total_ns = profile['totals']['parse']['inclusive_ns']
    phases = {name: {'calls': row['calls'], 'inclusive_s': row['inclusive_ns'] / 1e9,
                     'percent_of_observed_parse_seconds': 100 * row['inclusive_ns'] / total_ns}
              for name, row in profile['totals'].items()}
    old_inventory = json.loads((HISTORY / 'raw-artifact-files.json').read_bytes())['files']
    median_rep = importlib.import_module('decompose-round25-cost').median_rep
    models = []
    for name in ['public552', 'public552-shadow']:
        for block in [1, 2]:
            path = HISTORY / f'round{block}-{name}.jsonl'
            raw = path.read_bytes()
            assert len(raw) == old_inventory[path.name]['bytes'] and sha(raw) == old_inventory[path.name]['sha256']
            inputs[path.relative_to(ROOT).as_posix()] = sha(raw)
            records = [json.loads(line) for line in raw.splitlines() if line.strip()]
            assert records[0]['methods'][name]['source_sha256'] == EXPECTED
            axis = 0.0
            weights = {phase: 0.0 for phase in ['d_parse', 'd_dp', 'a_engine', 's_plan', 'e_parse', 'q9_parse', 'refine']}
            for row in records:
                if row['kind'] != 'file':
                    continue
                profiled = by_file[row['file']]
                assert profiled['input_sha256'] == row['sha256']
                candidate = median_rep(row['methods'][name])
                incumbent = median_rep(row['methods']['incumbent'])
                axis += candidate['total_s'] / incumbent['total_s'] / 28
                scale = candidate['parse_s'] / incumbent['total_s'] / 28 / profiled['functions']['parse']['inclusive_ns']
                for phase in weights:
                    weights[phase] += scale * profiled['functions'][phase]['inclusive_ns']
            models.append({'source_control': name, 'block': block, 'historical_axis': axis,
                           'relative_parent_axis_percent_proxy': {key: 100 * value / axis for key, value in weights.items()}})
    totals = counts['totals']
    result = {
        'status': 'VERIFIED_B8_RAW_WORK_AND_PHASE_ACCOUNTING_WITH_INFERRED_PRIORITY_MODEL',
        'computed_utc': datetime.now(timezone.utc).isoformat(),
        'run_id': counts['run_id'], 'git_sha': counts['git_sha'], 'source_hashes': counts['source_hashes'],
        'counts': totals,
        'nonempty_mean_actual_sampled_writes': totals['actual_sampled_writes'] / totals['nonempty_calls'],
        'long_share_of_actual_writes_pct': 100 * totals['long_sampled_writes'] / totals['actual_sampled_writes'],
        'phases': phases, 'historical_paired_weight_priority_models': models,
        'decision': 'No generic long-domain event implementation: actual dense-long coverage is zero. Do not allocate standalone D-backend work to the current5percent target on this model. Investigate exact whole-A-state repeat only after nearest R18/R24 negative-case exclusion.',
        'input_hashes': inputs,
        'limits': [
            'Counter and coarse phase sources are separately compiled; clocks are not attached to hot pair/relax operations. No original paired performance measurement was added.',
            's_plan contains a_engine, d_plan contains d_parse/d_dp. Inclusive parent and child phases are not independent savings.',
            'Historical R24 paired weights times B8 observer fractions are priority proxies, not current candidate scores, causal estimates, valid upper bounds or achievable gains.',
            'Public observation/token/decode identity does not prove universal equivalence, original obligation/gate, formal admission or reward.',
        ],
    }
    target = ROOT / 'evidence/round26/route-b/b8-work-and-priority.json'
    target.write_bytes((json.dumps(result, indent=2) + '\n').encode())
    print(json.dumps({'mean_writes': result['nonempty_mean_actual_sampled_writes'],
                      'long_write_pct': result['long_share_of_actual_writes_pct'],
                      'models': models}, indent=2))


if __name__ == '__main__':
    main()
