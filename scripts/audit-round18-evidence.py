"""Audit immutable R18 receipts and review payloads, including committed raw bytes."""
from pathlib import Path
from datetime import datetime, timezone
import argparse
import hashlib
import json
import subprocess
import zipfile

ROOT = Path(__file__).resolve().parents[1]
E = ROOT / 'evidence/round18'


def digest(data):
    return hashlib.sha256(data).hexdigest()


def read(path):
    return json.loads(path.read_bytes())


def check_file(folder, name, expected):
    path = (folder / name).resolve()
    assert path.is_relative_to(folder.resolve()) and path.is_file(), path
    data = path.read_bytes()
    assert len(data) == expected['bytes'] and digest(data) == expected['sha256'], path
    return path.relative_to(ROOT).as_posix(), expected['sha256'], len(data)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--output', type=Path, required=True)
    args = parser.parse_args()
    output = args.output.resolve()
    assert output.is_relative_to(E.resolve()) and not output.exists()
    raw = {}
    inventories = {}
    for path in sorted(E.glob('*/**/raw-artifact-files.json')):
        inventory = read(path)
        files = [check_file(path.parent, name, expected)
                 for name, expected in inventory['files'].items()]
        for name, sha, size in files:
            assert name not in raw
            raw[name] = {'sha256': sha, 'bytes': size}
        inventories[path.relative_to(ROOT).as_posix()] = {
            'sha256': digest(path.read_bytes()),
            'artifact_name': inventory['artifact_name'],
            'file_count': len(files),
        }
    captures = []
    for path in sorted(E.glob('official-*/receipt.json')):
        receipt = read(path)
        if receipt.get('status') != 'VERIFIED_OFFICIAL_READ_ONLY_API_CAPTURE':
            continue
        for item in receipt['raw_response_files']:
            check_file(path.parent, item['file'], item)
        for name, expected in receipt['derived_files'].items():
            check_file(path.parent, name, expected)
        captures.append({'receipt': path.relative_to(ROOT).as_posix(),
                         'sha256': digest(path.read_bytes()),
                         'snapshot_id': receipt['snapshot_id'],
                         'raw_response_count': len(receipt['raw_response_files'])})
    public_sources = []
    reference_files = {}
    for path in sorted((ROOT / 'references').glob('round18-public-*/source-receipt.json')):
        receipt = read(path)
        ident = receipt.get('submission_id', receipt.get('source', {}).get('id'))
        assert ident
        original = receipt.get('original_response', receipt.get('official_response'))
        if original:
            response = (ROOT / original).resolve()
            assert response.is_relative_to(E.resolve())
            expected_response_sha = receipt.get('original_response_sha256', receipt.get('official_response_sha256'))
        else:
            found = list(E.glob('**/' + str(ident) + '.response.json'))
            assert len(found) == 1
            response = found[0]
            expected_response_sha = receipt['source']['sha256']
        assert digest(response.read_bytes()) == expected_response_sha
        data = read(response)
        assert str(data['id']) == str(ident)
        for filename, field in (('parse.rs', 'parse_rs'), ('Parse.lean', 'proof_lean')):
            name, sha, size = check_file(path.parent, filename, receipt['files'][filename])
            assert (path.parent / filename).read_bytes() == data[field].encode()
            reference_files[name] = {'sha256': sha, 'bytes': size}
        public_sources.append({'submission_id': str(ident), 'receipt': path.relative_to(ROOT).as_posix(),
                               'receipt_sha256': digest(path.read_bytes()),
                               'raw_response': response.relative_to(ROOT).as_posix(),
                               'raw_response_sha256': expected_response_sha})
    code_rechecks = []
    for path in sorted(E.glob('official-code-*/receipt.json')):
        receipt = read(path)
        for record in receipt.get('raw_responses', []):
            check_file(path.parent, record['file'], record)
        if 'raw_response_sha256' in receipt:
            assert digest((path.parent / 'main-head.response.json').read_bytes()) == receipt['raw_response_sha256']
        if 'prior_code_audit' in receipt:
            prior = (ROOT / receipt['prior_code_audit']).resolve()
            assert prior.is_relative_to(E.resolve())
            assert digest(prior.read_bytes()) == receipt['prior_code_audit_sha256']
        code_rechecks.append({'receipt': path.relative_to(ROOT).as_posix(),
                              'sha256': digest(path.read_bytes())})
    payloads = []
    for path in sorted((E / 'review-packages').glob('*.json')):
        manifest = read(path)
        source = (ROOT / manifest['source_path']).resolve()
        assert source.is_relative_to((ROOT / 'candidates').resolve())
        certificate = read(source / 'VERIFICATION.json')
        assert manifest['files'] == certificate['files']
        assert certificate['status'] == 'VERIFIED_EXACT_ORIGINAL_PUBLIC_GATE_PASSED'
        receipt = ROOT / manifest['original_gate_receipt']
        gate = read(receipt)
        assert digest(receipt.read_bytes()) == manifest['original_gate_receipt_sha256']
        assert gate['status'] == 'EXACT_ORIGINAL_PUBLIC_GATE_ACCEPTED'
        assert all(gate['checks'].values()) and gate['spec']['files'] == manifest['files']
        payload = ROOT / manifest['payload_path']
        assert digest(payload.read_bytes()) == manifest['payload_sha256']
        assert payload.stat().st_size == manifest['payload_bytes']
        with zipfile.ZipFile(payload) as archive:
            assert archive.namelist() == ['parse.rs', 'Parse.lean']
            for name, sha in manifest['files'].items():
                assert digest(archive.read(name)) == digest((source / name).read_bytes()) == sha
        payloads.append({'candidate': manifest['candidate'], 'files': manifest['files'],
                         'payload_sha256': manifest['payload_sha256'],
                         'manifest': path.relative_to(ROOT).as_posix()})
    # The extension may preserve more than the two original review packages.
    # Package count is not evidence that reward goals or independent mechanisms exist.
    assert len(payloads) >= 2
    assert len({(p['files']['parse.rs'], p['files']['Parse.lean']) for p in payloads}) == len(payloads)
    tracked = set(subprocess.check_output(['git', 'ls-files', 'evidence/round18', 'references'],
                                         cwd=ROOT, text=True).splitlines())
    commit = subprocess.check_output(['git', 'rev-parse', 'HEAD'], cwd=ROOT, text=True).strip()
    checked = []
    not_committed = []
    process = subprocess.Popen(['git', 'cat-file', '--batch'], cwd=ROOT,
                               stdin=subprocess.PIPE, stdout=subprocess.PIPE)
    try:
        for path, expected in (raw | reference_files).items():
            if path not in tracked:
                not_committed.append(path)
                continue
            process.stdin.write(('HEAD:' + path + '\n').encode())
            process.stdin.flush()
            header = process.stdout.readline().split()
            assert len(header) == 3 and header[1] == b'blob', header
            data = process.stdout.read(int(header[2]))
            assert process.stdout.read(1) == b'\n'
            assert len(data) == expected['bytes'] and digest(data) == expected['sha256'], path
            checked.append(path)
    finally:
        process.stdin.close()
        process.stdout.close()
        process.wait()
    assert process.returncode == 0
    result = {
        'status': 'VERIFIED_RAW_BYTES_SNAPSHOT_AND_EXACT_PAYLOAD_AUDIT',
        'recorded_at_utc': datetime.now(timezone.utc).isoformat(),
        'git_head_audited': commit,
        'artifact_inventory_count': len(inventories),
        'local_raw_file_count': len(raw),
        'local_raw_bytes': sum(v['bytes'] for v in raw.values()),
        'committed_raw_files_checked': sum(p in raw for p in checked),
        'public_source_file_count': len(reference_files),
        'committed_public_source_files_checked': sum(p in reference_files for p in checked),
        'uncommitted_raw_file_count': sum(p in raw for p in not_committed),
        'uncommitted_raw_files': [p for p in not_committed if p in raw],
        'uncommitted_public_source_file_count': sum(p in reference_files for p in not_committed),
        'inventory_sha256': inventories,
        'official_captures': captures,
        'public_sources': public_sources,
        'official_code_rechecks': code_rechecks,
        'review_payloads': payloads,
        'scope': ('Checks local original artifact byte inventories, stored HEAD blobs for '
                  'already tracked raw files and public reference sources, complete API '
                  'capture receipts, public source API field bytes, official code rechecks and exact '
                  'two-file review ZIPs. It does not redownload ZIPs or equate GitHub '
                  'artifact digest with an independently verified ZIP digest. No formal '
                  'admission, private-corpus or payout result is established.'),
    }
    output.write_bytes((json.dumps(result, indent=2) + '\n').encode())
    print(json.dumps({k: v for k, v in result.items()
                      if k not in ('inventory_sha256', 'uncommitted_raw_files', 'review_payloads')},
                     indent=2))


if __name__ == '__main__':
    main()
