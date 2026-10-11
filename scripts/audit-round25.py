"""Recheck R25 immutable receipts, source manifests and dispatched job coverage."""
from pathlib import Path
from datetime import datetime, timezone
from collections import Counter
import argparse
import hashlib
import json

ROOT = Path(__file__).resolve().parents[1]
BASE = ROOT / 'evidence/round25'


def digest(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--output', type=Path, required=True)
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
    failed = BASE / '38131861001/counts-k-native/failed-setup/receipt.json'
    for name, expected in json.loads(failed.read_bytes())['files'].items():
        verify(failed.parent, name, expected)
    capture_receipts = []
    for p in sorted(BASE.glob('official-*/receipt.json')):
        receipt = json.loads(p.read_bytes())
        entries = receipt.get('raw_response_files', receipt.get('files', []))
        if isinstance(entries, dict):
            entries = [dict(value, file=key) for key, value in entries.items()]
        n = 0
        for entry in entries:
            if 'file' not in entry or 'sha256' not in entry:
                continue
            verify(p.parent, entry['file'], entry)
            n += 1
        capture_receipts.append({'path': p.relative_to(ROOT).as_posix(),
                                 'sha256': digest(p), 'checked_files': n})
    sources = []
    for p in sorted((ROOT / 'candidates').glob('r25-*/manifest.json')):
        manifest = json.loads(p.read_bytes())
        for name, expected in manifest['hashes'].items():
            verify(p.parent, name, {'sha256': expected})
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
    assert len(runs) == len(ci_by_id)
    out = {'status': 'VERIFIED_RETAINED_RAW_HASHES_SOURCES_AND_CI_COVERAGE',
           'checked_utc': datetime.now(timezone.utc).isoformat(),
           'raw_artifact_manifests': manifests,
           'official_capture_receipts': capture_receipts,
           'checked_file_count': len(checked),
           'checked_total_bytes': sum(x['bytes'] for x in checked.values()),
           'checked_files': checked, 'source_pairs': sources,
           'distinct_rust_count': len({s['files']['parse.rs'] for s in sources}),
           'run_count': len(runs), 'ci_conclusions': dict(Counter(r['conclusion'] for r in runs)),
           'runs': runs,
           'limits': ['Hash agreement proves retained bytes and provenance, not private acceptance or reward.',
                      'Public predictions and exact gate acceptance are audited separately.',
                      'Counts do not turn aliases, calibrations or repeated blocks into independent runners.']}
    args.output.write_text(json.dumps(out, indent=2) + '\n', encoding='utf-8')
    print(json.dumps({k: out[k] for k in ('status', 'checked_file_count',
          'checked_total_bytes', 'distinct_rust_count', 'run_count', 'ci_conclusions')}))


if __name__ == '__main__':
    main()
