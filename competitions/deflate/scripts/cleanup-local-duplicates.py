"""Explicit local cleanup: byte-identical backups, caches, immutable evidence links.

Plan first. Preserve every evidence pathname and byte; Git does not store hardlinks.
Never traverse reparse points or touch wallet, source, candidate or Git directories.
"""
from pathlib import Path
import argparse
import collections
import datetime
import hashlib
import json
import os
import shutil
import stat
import subprocess

ROOT = Path(__file__).resolve().parents[1]
OUT = ROOT / 'evidence/maintenance/2026-10-13-local-cleanup'


def stamp():
    return datetime.datetime.now(datetime.timezone.utc).isoformat()


def digest(path):
    with path.open('rb') as stream:
        return hashlib.file_digest(stream, 'sha256').hexdigest()


def safe(name, allowed):
    path = ROOT / name
    assert path.resolve().is_relative_to(ROOT)
    assert any(path.is_relative_to(ROOT / prefix) for prefix in allowed), name
    for component in [path, *path.parents]:
        if component == ROOT:
            break
        if component.exists():
            attrs = component.lstat().st_file_attributes
            assert not attrs & stat.FILE_ATTRIBUTE_REPARSE_POINT, str(component)
    return path


def files(prefix):
    start = safe(prefix, [prefix])
    for base, dirs, names in os.walk(start, followlinks=False):
        dirs[:] = [d for d in dirs if not (Path(base) / d).lstat().st_file_attributes & stat.FILE_ATTRIBUTE_REPARSE_POINT]
        for name in names:
            path = Path(base) / name
            if not path.lstat().st_file_attributes & stat.FILE_ATTRIBUTE_REPARSE_POINT:
                yield path


def rel(path):
    return path.relative_to(ROOT).as_posix()


def equal(a, b):
    with a.open('rb') as left, b.open('rb') as right:
        while True:
            chunk = left.read(1024 * 1024)
            if chunk != right.read(1024 * 1024):
                return False
            if not chunk:
                return True


def save(path, value):
    path.write_text(json.dumps(value, ensure_ascii=False, indent=2) + '\n', encoding='utf-8', newline='\n')


def plan():
    assert not OUT.exists(), 'Preserve prior cleanup receipts'
    status = subprocess.check_output(['git', 'status', '--porcelain'], cwd=ROOT, text=True)
    assert all(line == '?? scripts/cleanup-local-duplicates.py' for line in status.splitlines()), status
    baseline, grouped = [], collections.defaultdict(list)
    for path in files('evidence'):
        record = {'path': rel(path), 'bytes': path.stat().st_size, 'sha256': digest(path)}
        baseline.append(record)
        grouped[(record['bytes'], record['sha256'])].append(path)
    links = []
    for (size, sha), paths in grouped.items():
        if size < 4096 or len(paths) < 2:
            continue
        paths.sort(key=rel)
        original = paths[0]
        for path in paths[1:]:
            if os.path.samefile(original, path):
                continue
            assert equal(original, path)
            links.append({'path': rel(path), 'keep': rel(original), 'bytes': size, 'sha256': sha})
    deletes = []
    evidence_sizes = {key[0] for key in grouped}
    for prefix in ['.local-maintenance', '.runtime']:
        for path in files(prefix):
            size = path.stat().st_size
            if size not in evidence_sizes:
                continue
            sha = digest(path)
            sources = grouped.get((size, sha), [])
            if sources:
                assert equal(path, sources[0])
                deletes.append({'path': rel(path), 'keep': rel(sources[0]), 'bytes': size, 'sha256': sha})
    caches = [{'path': rel(p), 'bytes': p.stat().st_size, 'sha256': digest(p)}
              for p in files('scripts') if p.suffix == '.pyc' and '__pycache__' in p.parts]
    OUT.mkdir(parents=True)
    value = {'created_utc': stamp(), 'root': str(ROOT), 'head': subprocess.check_output(['git', 'rev-parse', 'HEAD'], cwd=ROOT, text=True).strip(),
             'free_bytes_before': shutil.disk_usage(ROOT).free,
             'evidence_baseline': baseline, 'evidence_hardlinks': links, 'duplicate_backup_deletions': deletes, 'cache_deletions': caches,
             'logical_backup_bytes': sum(x['bytes'] for x in deletes), 'logical_cache_bytes': sum(x['bytes'] for x in caches),
             'logical_hardlink_bytes': sum(x['bytes'] for x in links),
             'limitations': ['Git checkout does not preserve hardlink topology.', 'Original evidence is immutable; break a hardlink before deliberate future edits.',
                             'Disk free-space delta includes unrelated system activity.', 'CIM process inventory unavailable; no recursive directory or worktree removal is performed.']}
    save(OUT / 'plan.json', value)
    print(json.dumps({k: v for k, v in value.items() if k not in ('evidence_baseline', 'evidence_hardlinks', 'duplicate_backup_deletions', 'cache_deletions')}, ensure_ascii=False))
    print(json.dumps({'hardlinks': len(links), 'backups': len(deletes), 'caches': len(caches), 'evidence_files': len(baseline)}))


def execute():
    assert os.name == 'nt', 'NTFS local operation only'
    plan_path = OUT / 'plan.json'
    value = json.loads(plan_path.read_text(encoding='utf-8'))
    assert value['root'] == str(ROOT)
    assert value['head'] == subprocess.check_output(['git', 'rev-parse', 'HEAD'], cwd=ROOT, text=True).strip()
    if (OUT / 'receipt.json').exists():
        prior = json.loads((OUT / 'receipt.json').read_text(encoding='utf-8'))
        assert prior['status'] == 'INCOMPLETE' and not any(prior[key] for key in ['linked', 'deleted_backups', 'deleted_caches'])
        archived = OUT / 'receipt-attempt1.json'
        assert not archived.exists()
        (OUT / 'receipt.json').rename(archived)
    result = {'started_utc': stamp(), 'plan_sha256': digest(plan_path), 'status': 'RUNNING', 'linked': [], 'deleted_backups': [], 'deleted_caches': [], 'errors': []}
    save(OUT / 'receipt.json', result)
    try:
        for index, record in enumerate(value['evidence_hardlinks']):
            target = safe(record['path'], ['evidence'])
            source = safe(record['keep'], ['evidence'])
            assert digest(target) == digest(source) == record['sha256']
            assert equal(target, source)
            assert source.stat().st_nlink < 1000
            temp = target.with_name(target.name + '.cleanup-hardlink')
            assert not temp.exists()
            try:
                os.link(source, temp)
                os.replace(temp, target)
            finally:
                if temp.exists():
                    temp.unlink()
            assert os.path.samefile(source, target)
            result['linked'].append(record['path'])
            if index % 100 == 0:
                save(OUT / 'receipt.json', result)
        for key, output, prefixes in [('duplicate_backup_deletions', 'deleted_backups', ['.local-maintenance', '.runtime']), ('cache_deletions', 'deleted_caches', ['scripts'])]:
            for record in value[key]:
                target = safe(record['path'], prefixes)
                assert digest(target) == record['sha256']
                if 'keep' in record:
                    source = safe(record['keep'], ['evidence'])
                    assert digest(source) == record['sha256'] and equal(source, target)
                target.unlink()
                result[output].append(record['path'])
        # Remove empty cache folders only; no recursive deletion.
        for directory in sorted({(ROOT / x['path']).parent for x in value['cache_deletions']}, reverse=True):
            if directory.exists() and not any(directory.iterdir()):
                safe(rel(directory), ['scripts']).rmdir()
        for record in value['evidence_baseline']:
            path = safe(record['path'], ['evidence'])
            assert path.stat().st_size == record['bytes'] and digest(path) == record['sha256'], record['path']
        result['evidence_files_verified'] = len(value['evidence_baseline'])
        result['free_bytes_after'] = shutil.disk_usage(ROOT).free
        result['observed_free_space_delta_bytes'] = result['free_bytes_after'] - value['free_bytes_before']
        result['status'] = 'VERIFIED'
    except Exception as error:
        result['status'] = 'INCOMPLETE'
        result['errors'].append(repr(error))
        raise
    finally:
        result['ended_utc'] = stamp()
        save(OUT / 'receipt.json', result)
        print(json.dumps({k: v for k, v in result.items() if not isinstance(v, list)}, ensure_ascii=False))


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('mode', choices=['plan', 'execute'])
    args = parser.parse_args()
    (plan if args.mode == 'plan' else execute)()
