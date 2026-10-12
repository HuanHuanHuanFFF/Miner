"""Record all retained source/API/artifact input hashes for the R26 score audit."""
from datetime import datetime, timezone
import importlib
import json

M = importlib.import_module('r26-score-map')
ROOT = M.ROOT
OUT = ROOT / 'evidence/round26/score-verification'


def main():
    files = {}

    def add(path, role, expected=None):
        actual = M.digest(path)
        if expected is not None:
            assert actual == expected
        key = path.relative_to(ROOT).as_posix()
        if key not in files:
            files[key] = {'sha256': actual, 'bytes': path.stat().st_size, 'roles': []}
        else:
            assert files[key]['sha256'] == actual
        if role not in files[key]['roles']:
            files[key]['roles'].append(role)

    for root in ['official-start-live', 'official-rules-start-live']:
        folder = ROOT / 'evidence/round26' / root
        receipt = json.loads((folder / 'receipt.json').read_bytes())
        add(folder / 'receipt.json', 'official_capture_receipt')
        for item in receipt.get('raw_response_files', receipt.get('files')):
            add(folder / item['file'], 'official_original_response_or_captured_source', item['sha256'])
        for file, item in receipt.get('derived_files', {}).items():
            add(folder / file, 'official_derived_capture', item['sha256'])
    summary = json.loads((OUT / 'historical-replay-summary-29785.json').read_bytes())
    folders = set()
    for era in summary['historical_sets']:
        add(ROOT / era['source_registry'], 'historical_original_selection_registry', era['source_registry_sha256'])
        replay = json.loads((ROOT / era['raw_replay_file']).read_bytes())
        for run in replay['runs']:
            found = list((ROOT / 'evidence').glob('round*/' + run['run_id'] + '/' + run['batch'] + '/gate/state.json'))
            assert len(found) == 1
            folders.add(found[0].parent)
    for folder in sorted(folders):
        for file in ['state.json', 'ci-run.json', 'raw-artifact-files.json']:
            add(folder / file, 'historical_original_receipt_or_inventory')
        inventory = json.loads((folder / 'raw-artifact-files.json').read_bytes())
        for name, evidence in inventory['files'].items():
            add(folder / name, 'historical_original_artifact', evidence['sha256'])
    for file in ['audit-round24-score-algebra.py', 'analyze-round18.py', 'round10_payability.py', 'round3.py']:
        add(ROOT / 'scripts' / file, 'reused_analysis_source')
    for folder in ['round25-public-628', 'round26-public-629']:
        for file in ['parse.rs', 'Parse.lean', 'source-receipt.json']:
            add(ROOT / 'references' / folder / file, 'official_same_source_reference')
    result = {'status': 'VERIFIED_ALL_CAPTURED_AND_HISTORICAL_ORIGINAL_INPUT_HASHES',
              'checked_utc': datetime.now(timezone.utc).isoformat(), 'files': dict(sorted(files.items())),
              'unique_input_files': len(files), 'historical_artifact_runner_count': len(folders),
              'scope': 'Original API responses, capture derivations, rules sources, historical registries/receipts/inventories/artifacts, reused analysis source, and628/629reference source. No new timing or API call.'}
    M.dump(OUT / 'input-hashes-29785.json', result)
    print(json.dumps({k: result[k] for k in ['status', 'unique_input_files', 'historical_artifact_runner_count']}))


if __name__ == '__main__':
    main()
