"""Verify the R11 branch archive without compiling or executing its contents."""
from __future__ import annotations

import argparse
import hashlib
import json
from pathlib import Path, PurePosixPath
import subprocess

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[4]


def sha(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def safe_file(name: str) -> Path:
    parts = PurePosixPath(name)
    if (parts.is_absolute() or not parts.parts or '\\' in name or ':' in name
            or any(p in ('.', '..') for p in parts.parts)):
        raise ValueError(f'Unsafe archived path: {name}')
    path = HERE.joinpath(*parts.parts).resolve()
    path.relative_to(HERE)
    return path


def verify(check_git: bool, check_sources: bool) -> None:
    manifest_path = HERE / 'manifest.json'
    manifest = json.loads(manifest_path.read_bytes())
    rows = [f for p in manifest['packages'] for f in p['files']]
    rows += manifest['third_party_licenses']
    rows += manifest.get('project_evidence', [])
    git_inputs = []
    for row in rows:
        path = safe_file(row['path'])
        data = path.read_bytes()
        if len(data) != row['bytes'] or sha(data) != row['sha256']:
            raise ValueError(f'Changed branch archive: {row["path"]}')
        if check_sources and 'source_path' in row:
            if Path(row['source_path']).read_bytes() != data:
                raise ValueError(f'Original differs: {row["source_path"]}')
        git_inputs.append((path.relative_to(ROOT).as_posix(), data))
    if check_git:
        git_inputs.append((manifest_path.relative_to(ROOT).as_posix(), manifest_path.read_bytes()))
        process = subprocess.run(
            ['git', 'cat-file', '--batch'], cwd=ROOT, check=True, capture_output=True,
            input=''.join(f'HEAD:{name}\n' for name, _ in git_inputs).encode())
        offset = 0
        for name, expected in git_inputs:
            end = process.stdout.index(b'\n', offset)
            fields = process.stdout[offset:end].split()
            if len(fields) != 3 or fields[1] != b'blob':
                raise ValueError(f'Not committed: {name}')
            length = int(fields[2])
            data = process.stdout[end + 1:end + 1 + length]
            if data != expected:
                raise ValueError(f'Committed bytes differ: {name}')
            offset = end + length + 2
        if offset != len(process.stdout):
            raise ValueError('Unexpected Git batch output')
    print(json.dumps({
        'status': 'PASS', 'original_files': manifest['original_file_count'],
        'third_party_licenses': len(manifest['third_party_licenses']),
        'project_evidence_files': len(manifest.get('project_evidence', [])),
        'archived_bytes_verified': sum(r['bytes'] for r in rows),
        'committed_bytes_checked': check_git, 'e_drive_sources_checked': check_sources,
        'scope': 'File integrity only; no Lean, CI, performance or formal admission claim.'
    }))


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--git', action='store_true')
    parser.add_argument('--sources', action='store_true')
    args = parser.parse_args()
    verify(args.git, args.sources)
