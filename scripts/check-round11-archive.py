"""Verify R11 raw receipt bytes and frozen source pairs; optionally audit Git blobs."""
from pathlib import Path
import argparse
import hashlib
import importlib.util
import json

ROOT = Path(__file__).resolve().parents[1]
BASE = ROOT / 'evidence/round11'


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--git-ref')
    parser.add_argument('--output', type=Path, required=True)
    args = parser.parse_args()
    checks, targets, inventories, source_pairs, captures, cli_failures = [], {}, [], [], [], []

    def verify(path, expected, size=None, kind='raw_artifact'):
        path = path.resolve()
        assert path.is_relative_to(ROOT.resolve())
        raw = path.read_bytes()
        actual = hashlib.sha256(raw).hexdigest()
        relative = path.relative_to(ROOT).as_posix()
        item = {'path': relative, 'kind': kind, 'sha256': actual,
                'bytes': len(raw), 'expected_sha256': expected,
                'match': actual == expected and (size is None or len(raw) == size)}
        checks.append(item)
        targets[relative] = {'path': path, 'kind': kind, 'sha256': expected, 'bytes': len(raw)}

    def metadata(path, kind):
        raw = path.read_bytes()
        verify(path, hashlib.sha256(raw).hexdigest(), len(raw), kind)

    for manifest in sorted(BASE.rglob('raw-artifact-files.json')):
        inv = json.loads(manifest.read_bytes())
        metadata(manifest, 'inventory')
        for name, expected in inv['files'].items():
            path = (manifest.parent / name).resolve()
            assert path.is_relative_to(manifest.parent.resolve())
            verify(path, expected['sha256'], expected['bytes'])
        inventories.append({'path': manifest.relative_to(ROOT).as_posix(),
                            'artifact_name': inv['artifact_name'], 'files': len(inv['files'])})
        ci_path = manifest.parent / 'ci-run.json'
        if ci_path.exists():
            metadata(ci_path, 'ci_metadata')
        state_path = manifest.parent / 'state.json'
        if manifest.parent.name != 'gate' or not state_path.exists():
            continue
        ci = json.loads(ci_path.read_bytes())
        state = json.loads(state_path.read_bytes())
        assert ci['status'] == 'completed'
        assert str(ci['databaseId']) == str(state['run_id'])
        assert ci['headSha'] == state['git_sha']
        for entry in state['spec']['entries']:
            for name, digest in entry['hashes'].items():
                verify(ROOT / entry['path'] / name, digest, kind='frozen_source_pair')
            source_pairs.append({'run_id': state['run_id'], 'name': entry['name'],
                                 'path': entry['path'], 'hashes': entry['hashes']})

    for manifest in sorted(BASE.rglob('raw-cli-files.json')):
        record = json.loads(manifest.read_bytes())
        metadata(manifest, 'cli_failure_inventory')
        for name, expected in record['files'].items():
            path = (manifest.parent/name).resolve()
            assert path.is_relative_to(manifest.parent.resolve())
            verify(path, expected['sha256'], expected['bytes'], 'raw_cli_failure_output')
        ci = json.loads((manifest.parent/'ci-run.raw.json').read_bytes())
        assert ci['status']=='completed' and ci['conclusion']=='failure'
        assert str(ci['databaseId'])==record['run_id'] and ci['headSha']==record['git_sha']
        cli_failures.append({'run_id':record['run_id'], 'batch':record['batch'],
                             'path':manifest.relative_to(ROOT).as_posix(), 'files':len(record['files'])})

    for folder in sorted(BASE.glob('official-*')):
        receipt_path = folder / 'receipt.json'
        if not receipt_path.exists():
            receipt_path = folder / 'capture-failure.json'
        if not receipt_path.exists():
            continue
        receipt = json.loads(receipt_path.read_bytes())
        metadata(receipt_path, 'capture_metadata')
        for entry in receipt['raw_response_files']:
            verify(folder / entry['file'], entry['sha256'], entry['bytes'], 'official_raw_response')
        for name, entry in receipt.get('derived_files', {}).items():
            verify(folder / name, entry['sha256'], entry['bytes'], 'official_derived')
        captures.append({'path': folder.relative_to(ROOT).as_posix(), 'status': receipt['status'],
                         'snapshot_id': receipt.get('snapshot_id')})

    git_result = None
    if args.git_ref:
        spec = importlib.util.spec_from_file_location('r10_archive', ROOT / 'scripts/check-round10-archive.py')
        module = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(module)
        git_result = module.git_blob_audit(args.git_ref, targets)
    passed = all(x['match'] for x in checks)
    if git_result:
        passed = passed and git_result['counts']['matched'] == git_result['counts']['paths_checked']
    result = {'status': 'VERIFIED_ARCHIVE_BYTES' if passed else 'ARCHIVE_MISMATCH',
              'checks': len(checks), 'unique_paths': len(targets),
              'mismatches': [x for x in checks if not x['match']],
              'inventories': inventories, 'source_pairs': source_pairs, 'captures': captures,
              'cli_failures_without_artifacts': cli_failures,
              'git': git_result,
              'limits': ['Byte preservation and CI/source binding only; no new correctness, timing or admission claim.']}
    args.output.write_bytes((json.dumps(result, indent=2) + '\n').encode())
    print(json.dumps({'status': result['status'], 'checks': len(checks), 'unique_paths': len(targets),
                      'inventories': len(inventories), 'captures': len(captures),
                      'git_counts': git_result['counts'] if git_result else None}))
    if not passed:
        raise SystemExit(1)


if __name__ == '__main__':
    main()
