"""Recheck R26 immutable receipts, source manifests and dispatched job coverage."""
from pathlib import Path
from datetime import datetime, timezone
from collections import Counter
import argparse
import hashlib
import io
import json
import subprocess
import zipfile

ROOT = Path(__file__).resolve().parents[1]
BASE = ROOT / 'evidence/round26'


def digest(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--output', type=Path, required=True)
    ap.add_argument('--git-ref', help='Also verify every audited file against this committed tree')
    ap.add_argument('--dashboard', type=Path, help='Audit this round-close public dashboard summary and receipts')
    args = ap.parse_args()
    assert not args.output.exists(), 'Preserve earlier audit observations'
    checked = {}
    manifests = []

    def verify(folder, name, expected):
        p = (folder / name).resolve()
        assert p.is_relative_to(ROOT) and p.is_file(), str(p)
        actual = {'bytes': p.stat().st_size, 'sha256': digest(p)}
        for key in ('bytes', 'sha256'):
            if key in expected:
                assert actual[key] == expected[key], (p, key)
        checked[p.relative_to(ROOT).as_posix()] = actual

    for p in sorted(BASE.rglob('raw-artifact-files.json')):
        inv = json.loads(p.read_bytes())
        for name, expected in inv['files'].items():
            verify(p.parent, name, expected)
        manifests.append({'path': p.relative_to(ROOT).as_posix(),
                          'sha256': digest(p), 'entries': len(inv['files'])})
        for name in ('raw-artifact-files.json', 'ci-run.json', 'ci.log', 'artifact-receipt.json', 'failure-receipt.json'):
            if (p.parent / name).is_file():
                verify(p.parent, name, {})
    capture_receipts = []
    for p in sorted(BASE.glob('official-*/receipt.json')):
        receipt = json.loads(p.read_bytes())
        entries = receipt.get('raw_response_files', receipt.get('files', []))
        if isinstance(entries, dict):
            entries = [dict(value, file=key) for key, value in entries.items()]
        if not entries and 'sha256' in receipt and 'bytes' in receipt:
            response_files = list(p.parent.glob('*.response.json'))
            assert len(response_files) == 1
            entries = [dict(receipt, file=response_files[0].name)]
        n = 0
        for entry in entries:
            if 'file' not in entry or 'sha256' not in entry:
                continue
            verify(p.parent, entry['file'], entry)
            n += 1
        for name, entry in receipt.get('derived_files', {}).items():
            verify(p.parent, name, entry)
        verify(p.parent, p.name, {})
        capture_receipts.append({'path': p.relative_to(ROOT).as_posix(),
                                 'sha256': digest(p), 'checked_files': n})
    for p in sorted(BASE.glob('public-*/receipt.json')):
        records = json.loads(p.read_bytes())
        for record in records:
            if 'sha256' not in record:
                continue
            verify(p.parent, record['id'] + '.response.json', record)
            if record.get('http_status') == 200:
                reference = ROOT / ('references/round26-public-' + record['id'])
                for name, expected in record['files'].items():
                    verify(reference, name, expected)
                verify(reference, 'source-receipt.json', {})
        verify(p.parent, p.name, {})
    sources = []
    for p in sorted((ROOT / 'candidates').glob('r26-*/manifest.json')):
        manifest = json.loads(p.read_bytes())
        for name, expected in manifest['hashes'].items():
            verify(p.parent, name, {'sha256': expected})
        verify(p.parent, p.name, {})
        if (p.parent / 'VERIFICATION.json').exists():
            verify(p.parent, 'VERIFICATION.json', {})
        sources.append({'path': p.parent.relative_to(ROOT).as_posix(),
                        'files': manifest['hashes'],
                        'proof_status': manifest.get('proof_status', 'UNKNOWN')})
    ci_by_id = {}
    for p in BASE.rglob('ci-run.json'):
        ci = json.loads(p.read_bytes())
        key = str(ci['databaseId'])
        assert key not in ci_by_id, ('Duplicate CI run metadata', key)
        ci_by_id[key] = (p, ci)
    runs = []
    for p in sorted(BASE.glob('dispatch-*.json')):
        dispatch = json.loads(p.read_bytes())
        key = str(dispatch['run']['databaseId'])
        assert key in ci_by_id, ('Missing final CI metadata', key)
        cp, ci = ci_by_id[key]
        assert ci['headSha'] == dispatch['git_sha']
        assert ci['status'] == 'completed', ('Still running', key)
        runs.append({'run_id': key, 'batch': dispatch['batch'],
                     'mode': dispatch['mode'], 'git_sha': ci['headSha'],
                     'conclusion': ci['conclusion'],
                     'dispatch': p.relative_to(ROOT).as_posix(),
                     'dispatch_sha256': digest(p),
                     'ci_metadata': cp.relative_to(ROOT).as_posix(),
                     'ci_metadata_sha256': digest(cp)})
        jobs = [j for j in ci.get('jobs', []) if j.get('startedAt') and j.get('completedAt') and j.get('conclusion') != 'skipped']
        seconds = sum((datetime.fromisoformat(j['completedAt'].replace('Z', '+00:00')) - datetime.fromisoformat(j['startedAt'].replace('Z', '+00:00'))).total_seconds() for j in jobs)
        runs[-1]['recorded_runner_seconds'] = seconds
        runs[-1]['runner_time_scope'] = 'Sum completed non-skipped job wall time; not billing or model cost'
        verify(p.parent, p.name, {})
        verify(cp.parent, cp.name, {})
    assert len(runs) == len(ci_by_id)
    package_file = BASE / 'review-packages/packages.json'
    packages = {'packages': []}
    if package_file.exists():
        packages = json.loads(package_file.read_bytes())
    for package in packages['packages']:
        archive = ROOT / package['archive']
        verify(archive.parent, archive.name,
               {'sha256': package['archive_sha256'], 'bytes': package['archive_bytes']})
        with zipfile.ZipFile(archive) as z:
            assert z.namelist() == ['parse.rs', 'Parse.lean'] and z.testzip() is None
            for name, expected in package['files'].items():
                assert hashlib.sha256(z.read(name)).hexdigest() == expected
                assert z.read(name) == (ROOT / package['source_path'] / name).read_bytes()
    if package_file.exists():
        verify(package_file.parent, package_file.name, {})
    dashboard = None
    if args.dashboard:
        summary_path = args.dashboard.resolve()
        assert summary_path.is_relative_to((ROOT / 'evidence/dashboard').resolve())
        for receipt in json.loads((summary_path.parent / 'receipts.json').read_bytes()):
            verify(summary_path.parent, receipt['raw_file'], receipt)
        for path in sorted(summary_path.parent.rglob('*')):
            if path.is_file():
                verify(path.parent, path.name, {})
        summary = json.loads(summary_path.read_bytes())
        dashboard = {'summary': summary_path.relative_to(ROOT).as_posix(),
                     'snapshot_id': summary['context']['snapshot_id'],
                     'submissions': len(summary['submissions']),
                     'status': 'VERIFIED_PUBLIC_API_RECEIPTS_AND_RETAINED_CHAIN_READ_BYTES'}
    committed = None
    if args.git_ref:
        revision = subprocess.check_output(['git', 'rev-parse', args.git_ref], cwd=ROOT, text=True).strip()
        names = sorted(checked)
        for start in range(0, len(names), 32):
            chunk = names[start:start + 32]
            request = ''.join(revision + ':' + n + '\n' for n in chunk).encode()
            content = subprocess.check_output(['git', 'cat-file', '--batch'], input=request, cwd=ROOT)
            stream = io.BytesIO(content)
            for name in chunk:
                header = stream.readline().decode().strip()
                assert not header.endswith(' missing'), ('Uncommitted audit input', name)
                _, kind, size = header.split()
                assert kind == 'blob'
                blob = stream.read(int(size))
                assert stream.read(1) == b'\n'
                assert len(blob) == checked[name]['bytes'], name
                assert hashlib.sha256(blob).hexdigest() == checked[name]['sha256'], name
            assert stream.read() == b''
        committed = {'status': 'VERIFIED_EXACT_COMMITTED_BYTES',
                     'git_sha': revision, 'file_count': len(names)}
    out = {'status': 'VERIFIED_RETAINED_RAW_HASHES_SOURCES_AND_CI_COVERAGE',
           'checked_utc': datetime.now(timezone.utc).isoformat(),
           'raw_artifact_manifests': manifests,
           'official_capture_receipts': capture_receipts,
           'checked_file_count': len(checked),
           'checked_total_bytes': sum(x['bytes'] for x in checked.values()),
           'checked_files': checked, 'source_pairs': sources,
           'distinct_rust_count': len({s['files']['parse.rs'] for s in sources}),
           'source_only_packages': len(packages['packages']), 'committed_bytes': committed,
           'dashboard': dashboard,
           'run_count': len(runs), 'ci_conclusions': dict(Counter(r['conclusion'] for r in runs)),
           'runs': runs,
           'recorded_runner_seconds': sum(r['recorded_runner_seconds'] for r in runs),
           'limits': ['Hash agreement proves retained bytes and provenance, not private acceptance or reward.',
                      'Public predictions and exact gate acceptance are audited separately.',
                      'Counts do not turn aliases, calibrations or repeated blocks into independent runners.']}
    args.output.write_text(json.dumps(out, indent=2) + '\n', encoding='utf-8')
    print(json.dumps({k: out[k] for k in ('status', 'checked_file_count',
          'checked_total_bytes', 'distinct_rust_count', 'run_count', 'ci_conclusions')}))


if __name__ == '__main__':
    main()
