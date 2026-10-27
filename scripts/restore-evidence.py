"""Restore pruned evidence from immutable Git blobs, checking original bytes."""
from pathlib import Path, PurePosixPath
import argparse
from collections import Counter
import hashlib
import json
import os
import re
import stat
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[1]
CATALOG = ROOT / 'competitions/floatlib/evidence/maintenance-20261027/recoverable-evidence.json'


def destination(root, name):
    path = PurePosixPath(name)
    if (not name or not path.parts or '\\' in name or ':' in name or path.is_absolute()
            or '..' in path.parts or path.as_posix() != name):
        raise ValueError(f'Unsafe evidence path: {name!r}')
    root = root.resolve(strict=True)
    target = root.joinpath(*path.parts)
    for part in (target, *target.parents):
        if part == root:
            break
        if part.is_symlink() or (part.exists() and
                getattr(part.lstat(), 'st_file_attributes', 0) & stat.FILE_ATTRIBUTE_REPARSE_POINT):
            raise ValueError(f'Linked evidence path: {name}')
    if not target.resolve().is_relative_to(root):
        raise ValueError(f'Evidence path escapes repository: {name}')
    return target


def matches(path, entry):
    if not path.is_file() or path.stat().st_size != entry['bytes']:
        return False
    digest = hashlib.sha256()
    with path.open('rb') as source:
        for block in iter(lambda: source.read(1024 * 1024), b''):
            digest.update(block)
    return digest.hexdigest() == entry['sha256']


class GitBlobs:
    def __init__(self, root):
        self.process = subprocess.Popen(['git', 'cat-file', '--batch'], cwd=root,
                                        stdin=subprocess.PIPE, stdout=subprocess.PIPE)

    def __enter__(self):
        return self

    def __exit__(self, *unused):
        self.process.stdin.close()
        self.process.stdout.close()
        if self.process.poll() is None:
            self.process.terminate()
        self.process.wait()

    def copy(self, entry, output):
        oid = entry['git_blob']
        if not re.fullmatch(r'[0-9a-f]{40}', oid):
            raise ValueError('Invalid Git blob ID')
        self.process.stdin.write((oid + '\n').encode('ascii'))
        self.process.stdin.flush()
        header = self.process.stdout.readline().decode('ascii').split()
        if len(header) != 3 or header[:2] != [oid, 'blob']:
            raise ValueError(f'Git blob unavailable: {oid}; fetch the catalog source_commit first')
        remaining = int(header[2])
        if remaining != entry['bytes']:
            raise ValueError(f'Git blob length mismatch: {oid}')
        digest = hashlib.sha256()
        while remaining:
            block = self.process.stdout.read(min(1024 * 1024, remaining))
            if not block:
                raise ValueError(f'Truncated Git blob: {oid}')
            remaining -= len(block)
            digest.update(block)
            output.write(block)
        if self.process.stdout.read(1) != b'\n' or digest.hexdigest() != entry['sha256']:
            raise ValueError(f'Git blob digest mismatch: {oid}')


def restore(root, name, entry, blobs):
    target = destination(root, name)
    if target.exists():
        if matches(target, entry):
            return 'already_present'
        raise ValueError(f'Refusing to overwrite changed file: {name}')
    target.parent.mkdir(parents=True, exist_ok=True)
    temporary = None
    try:
        with tempfile.NamedTemporaryFile(dir=target.parent, prefix='.evidence-', delete=False) as output:
            temporary = Path(output.name)
            blobs.copy(entry, output)
        destination(root, name)
        if target.exists():
            raise ValueError(f'Destination appeared during restoration: {name}')
        os.replace(temporary, target)
        return 'restored'
    finally:
        if temporary is not None and temporary.exists():
            temporary.unlink()


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--path', action='append', default=[], help='Exact repository-relative evidence path')
    parser.add_argument('--run', action='append', default=[], help='Restore a complete indexed CI run')
    parser.add_argument('--all', action='store_true', help='Restore every pruned file for historical full audits')
    parser.add_argument('--list', action='store_true', help='Show selection totals without writing')
    args = parser.parse_args()
    catalog = json.loads(CATALOG.read_bytes())
    entries = catalog['entries']
    missing = set(args.path) - entries.keys()
    known_runs = {e['ci_run_id'] for e in entries.values() if e['ci_run_id']}
    if missing or set(args.run) - known_runs:
        parser.error('Requested path or CI run is absent from the evidence catalog')
    selected = {name: entry for name, entry in entries.items()
                if args.all or name in args.path or entry['ci_run_id'] in args.run}
    if not selected and not args.list:
        parser.error('Select --path, --run or --all; use --list for totals')
    if args.list:
        shown = selected or entries
        print(json.dumps({'files': len(shown), 'bytes': sum(e['bytes'] for e in shown.values()),
                          'source_commit': catalog['source_commit']}, indent=2))
        return
    counts = Counter()
    with GitBlobs(ROOT) as blobs:
        for name, entry in selected.items():
            counts[restore(ROOT, name, entry, blobs)] += 1
    print(json.dumps(dict(counts), indent=2))


if __name__ == '__main__':
    main()
