"""Check declared immutable R24 evidence against Git objects, preserving raw line endings."""
from pathlib import Path
from datetime import datetime, timezone
import argparse, hashlib, io, json, subprocess, zipfile

ROOT = Path(__file__).resolve().parents[1]
E = ROOT / 'evidence/round24'


def read(p):
    return json.loads(p.read_bytes())


def sha(data):
    return hashlib.sha256(data).hexdigest()


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--ref', default='HEAD')
    ap.add_argument('--output', required=True, type=Path)
    a = ap.parse_args()
    assert not a.output.exists()
    revision = subprocess.check_output(['git', 'rev-parse', a.ref], cwd=ROOT, text=True).strip()
    expected = {}

    def add(p, digest=None, size=None):
        path = p.resolve()
        assert path.is_relative_to(ROOT.resolve())
        data = path.read_bytes()
        assert digest is None or sha(data) == digest, path
        assert size is None or len(data) == size, path
        value = {'bytes': len(data), 'sha256': sha(data)}
        name = path.relative_to(ROOT).as_posix()
        assert expected.setdefault(name, value) == value

    for p in E.glob('[0-9]*/**/raw-artifact-files.json'):
        inv = read(p)
        add(p)
        for n, value in inv['files'].items():
            target = (p.parent / n).resolve()
            assert target.is_relative_to(p.parent.resolve())
            add(target, value['sha256'], value['bytes'])
        for n in ['ci-run.json', 'ci.log', 'artifact-receipt.json']:
            if (p.parent / n).exists():
                add(p.parent / n)
    for p in E.glob('official*/receipt.json'):
        receipt = read(p)
        add(p)
        for value in receipt.get('raw_response_files', []) + receipt.get('files', []):
            if 'file' in value and 'sha256' in value:
                add(p.parent / value['file'], value['sha256'], value.get('bytes'))
        for name, value in receipt.get('derived_files', {}).items():
            add(p.parent / name, value['sha256'], value['bytes'])
    plan = read(E / 'confirm-final-plan.json')
    for manifest in (ROOT / 'candidates').glob('r24-*/manifest.json'):
        for filename, digest in read(manifest)['hashes'].items():
            add(manifest.parent / filename, digest)
    for name, files in plan['files'].items():
        for filename, digest in files.items():
            add(ROOT / 'candidates' / name / filename, digest)
    packages = read(E / 'review-packages/packages.json')
    # Archive contents are checked directly against the immutable source plan.
    zips = list((E / 'review-packages').glob('*.zip'))
    assert len(zips) == 2
    for p in zips:
        name = next(n for n in plan['candidates'] if n in p.name)
        record = next(r for r in packages['packages'] if r['candidate'] == name)
        assert sha(p.read_bytes()) == record['archive_sha256']
        assert p.stat().st_size == record['archive_bytes']
        with zipfile.ZipFile(p) as z:
            assert z.namelist() == ['parse.rs', 'Parse.lean']
            for filename, digest in plan['files'][name].items():
                assert sha(z.read(filename)) == digest
        add(p)
    add(E / 'review-packages/packages.json')
    checked, uncommitted = [], []
    names = sorted(expected)
    for start in range(0, len(names), 32):
        chunk = names[start:start + 32]
        request = ''.join(revision + ':' + n + '\n' for n in chunk).encode()
        data = subprocess.check_output(['git', 'cat-file', '--batch'], input=request, cwd=ROOT)
        stream = io.BytesIO(data)
        for n in chunk:
            header = stream.readline().decode().strip()
            if header.endswith(' missing'):
                uncommitted.append(n)
                continue
            _, kind, count = header.split()
            assert kind == 'blob'
            content = stream.read(int(count))
            assert stream.read(1) == b'\n'
            assert len(content) == expected[n]['bytes'] and sha(content) == expected[n]['sha256'], n
            checked.append(n)
        assert stream.read() == b''
    out = {'status': 'VERIFIED_COMMITTED_BYTE_IDENTITIES' if not uncommitted else 'VERIFIED_PRESENT_COMMITTED_BYTES_WITH_NEW_UNCOMMITTED_FILES_LISTED', 'checked_utc': datetime.now(timezone.utc).isoformat(), 'git_sha': revision, 'checked_files': len(checked), 'checked_bytes': sum(expected[n]['bytes'] for n in checked), 'uncommitted_files': uncommitted, 'files': expected, 'limits': ['Git blob checks preserve raw bytes and line endings. Raw logs containing trailing spaces are retained, not reformatted to satisfy whitespace lint.', 'New uncommitted evidence is explicitly listed and must be rechecked after the next commit before complete archival delivery.', 'This is byte identity and payload correctness, not formal admission or a new performance result.']}
    a.output.write_bytes((json.dumps(out, indent=2) + '\n').encode())
    print(json.dumps({k: out[k] for k in ['status', 'git_sha', 'checked_files', 'checked_bytes', 'uncommitted_files']}, indent=2))


if __name__ == '__main__':
    main()
