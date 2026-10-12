"""Audit B9 exact repeats and real adjacent-range cost; retain non-exercised idempotence."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import importlib
import json

ROOT = Path(__file__).resolve().parents[1]
NATIVE = ROOT / 'evidence/round26/38182721892/repeat-b9-native/diagnostics'
HISTORY = ROOT / 'evidence/round24/38082906439/screen-h/gate'
EXPECTED = '5adaaeac471b86128778bf6b67f786542f5c8e079adbf1160f0502309f7befb9'


def sha(raw):
    return hashlib.sha256(raw).hexdigest()


def main():
    inventory = json.loads((NATIVE / 'raw-artifact-files.json').read_bytes())['files']
    input_hashes = {}
    values = {}
    for file in ['r26-b-a-repeat/receipt.json', 'r18-functions/functions.json', 'execution-start.json']:
        raw = (NATIVE / file).read_bytes()
        assert len(raw) == inventory[file]['bytes'] and sha(raw) == inventory[file]['sha256']
        values[file] = json.loads(raw)
        input_hashes[(NATIVE / file).relative_to(ROOT).as_posix()] = sha(raw)
    repeat = values['r26-b-a-repeat/receipt.json']
    profile = values['r18-functions/functions.json']
    ci = json.loads((NATIVE / 'ci-run.json').read_bytes())
    assert str(ci['databaseId']) == repeat['run_id'] == profile['run_id'] == '38182721892'
    assert ci['headSha'] == repeat['git_sha'] == profile['git_sha']
    assert ci['status'] == 'completed' and ci['conclusion'] == 'success'
    assert repeat['source_hashes'] == profile['source_hashes']
    assert repeat['source_hashes']['parse.rs'] == EXPECTED
    rows = {row['file']: row for row in repeat['rows']}
    phases = {row['file']: row for row in profile['rows']}
    potential, entropy, huff = {}, {}, {}
    for name, row in rows.items():
        assert row['input_sha256'] == phases[name]['input_sha256']
        keys = row['full_key_trajectory']
        counts = row['counts']
        assert len(keys) == counts['full_dp_calls']
        assert sum(key['original_full_dp_ns'] for key in keys) == counts['full_dp_ns']
        assert sum(key['eligible'] for key in keys) == counts['eligible_calls'] == counts['idempotence_checks']
        potential[name] = sum(key['original_full_dp_ns'] for key in keys if key['prior_same_interval'])
        entropy[name] = sum(key['original_full_dp_ns'] for key in keys if not key['incoming_huff_prices'])
        huff[name] = sum(key['original_full_dp_ns'] for key in keys if key['incoming_huff_prices'])
    old_inventory = json.loads((HISTORY / 'raw-artifact-files.json').read_bytes())['files']
    median_rep = importlib.import_module('decompose-round25-cost').median_rep
    models = []
    for name in ['public552', 'public552-shadow']:
        for block in [1, 2]:
            path = HISTORY / f'round{block}-{name}.jsonl'
            raw = path.read_bytes()
            assert len(raw) == old_inventory[path.name]['bytes'] and sha(raw) == old_inventory[path.name]['sha256']
            input_hashes[path.relative_to(ROOT).as_posix()] = sha(raw)
            records = [json.loads(line) for line in raw.splitlines() if line.strip()]
            assert records[0]['methods'][name]['source_sha256'] == EXPECTED
            axis = 0.0
            terms = {key: 0.0 for key in ['hypothetical_masked_all_interval', 'full_entropy_stage',
                                        'full_huff_stage', 'sample_stage', 'all_A_DP', 'A_finder']}
            for row in records:
                if row['kind'] != 'file':
                    continue
                observed = rows[row['file']]
                assert observed['input_sha256'] == row['sha256']
                candidate = median_rep(row['methods'][name])
                incumbent = median_rep(row['methods']['incumbent'])
                axis += candidate['total_s'] / incumbent['total_s'] / 28
                weight = candidate['parse_s'] / incumbent['total_s'] / 28
                scale = weight / observed['counts']['parse_inclusive_ns']
                terms['hypothetical_masked_all_interval'] += scale * potential[row['file']]
                terms['full_entropy_stage'] += scale * entropy[row['file']]
                terms['full_huff_stage'] += scale * huff[row['file']]
                terms['sample_stage'] += scale * observed['counts']['sample_parent_ns']
                profiled = phases[row['file']]['functions']
                scale2 = weight / profiled['parse']['inclusive_ns']
                terms['all_A_DP'] += scale2 * profiled['a_dp_pass']['inclusive_ns']
                terms['A_finder'] += scale2 * profiled['a_find_all']['inclusive_ns']
            models.append({'historical_control': name, 'block': block, 'historical_axis': axis,
                           'relative_parent_axis_percent_proxy': {key: 100 * value / axis for key, value in terms.items()}})
    result = {
        'status': 'VERIFIED_B9_RAW_IDENTITY_AND_REPEAT_COST_WITH_INFERRED_PRIORITY_MODELS',
        'computed_utc': datetime.now(timezone.utc).isoformat(), 'run_id': repeat['run_id'],
        'git_sha': repeat['git_sha'], 'source_hashes': repeat['source_hashes'],
        'totals': repeat['totals'], 'same_interval_actual_dp_ns': sum(potential.values()),
        'full_entropy_dp_ns': sum(entropy.values()), 'full_huff_dp_ns': sum(huff.values()),
        'idempotence_status': 'NOT_EXERCISED: zero eligible calls, no idempotence acceptance',
        'historical_paired_weight_priority_models': models,
        'rows': repeat['rows'], 'original_coarse_profile_totals': profile['totals'],
        'decision': 'Stop exact800price and masked equality on this adjacent-retained-output route this round; even all14same-range calls are about.94percent of the planning axis proxy. Next controlled different-statistic-source mechanism keeps the full cache/finalDP and permits genuine measured quality/time tradeoff.',
        'input_hashes': input_hashes,
        'limits': ['Native observer token/decode matches frozen original552, but no original paired timing or fullgate was added.',
                   'Diagnostic parent/parse clocks include traces/snapshots; full-call clocks exclude them. Original coarse source profiling is separate.',
                   'Historical paired weights times diagnostic fractions are priority models, not current scores, causal/achievable gains or strict bounds.',
                   'Fixed-quality geometry slices are planning scenarios, not universal exclusions for different quality/time tradeoffs.',
                   'No all-input convergence, formal admission or reward conclusion.'],
    }
    path = ROOT / 'evidence/round26/route-b/b9-repeat-feedback.json'
    path.write_bytes((json.dumps(result, indent=2) + '\n').encode())
    print(json.dumps({key: result[key] for key in ['idempotence_status', 'same_interval_actual_dp_ns',
                                                'full_entropy_dp_ns', 'full_huff_dp_ns']}))


if __name__ == '__main__':
    main()
