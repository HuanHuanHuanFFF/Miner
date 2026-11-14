"""Read-only byte/syntax verification; never Lean, native, Git or CI acceptance."""
import ast
import hashlib
import json
from pathlib import Path
import sys

HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p / 'AGENTS.md').is_file())


def entries(value):
    if isinstance(value, dict):
        return [dict(item, path=path) for path, item in value.items()]
    return value


def check(items, bases):
    failures = []
    count = 0
    for item in items:
        candidates = [(base / item['path']).resolve() for base in bases]
        path = next((p for p in candidates if p.is_file()), None)
        if path is None or not path.is_relative_to(ROOT):
            failures.append({'path': item['path'], 'error': 'MISSING_OR_OUTSIDE_ROOT'})
            continue
        data = path.read_bytes()
        count += 1
        if len(data) != item['bytes'] or hashlib.sha256(data).hexdigest() != item['sha256']:
            failures.append({'path': item['path'], 'error': 'BYTE_HASH_MISMATCH'})
    return {'checked': count, 'failures': failures}


def main():
    result = {'scope': 'PACKAGE_BYTES_AND_SYNTAX_ONLY', 'roles': {}}
    for lane, name in [('resnet-mechanism', 'public-manifest.json'),
                       ('mobile-mechanism', 'PUBLIC-MANIFEST.json'),
                       ('cross-source', 'PUBLIC-MANIFEST.json')]:
        value = json.loads((HERE / lane / name).read_text(encoding='utf-8-sig'))
        result['roles'][lane] = check(entries(value.get('public_files', value.get('files'))),
                                      [HERE / lane, ROOT, HERE])
    failures = sum(len(v['failures']) for v in result['roles'].values())
    if '--roles-only' not in sys.argv:
        value = json.loads((HERE / 'public-research-manifest.json').read_text(encoding='utf-8'))
        result['root'] = check(value['files'], [ROOT])
        failures += len(result['root']['failures'])
        paths = {v['path'] for v in value['files']}
        paths.update((HERE / n).relative_to(ROOT).as_posix()
                     for n in ['public-research-manifest.json', 'public-research-allowlist.txt'])
        listed = (HERE / 'public-research-allowlist.txt').read_text(encoding='utf-8').splitlines()
        assert len(listed) == len(set(listed)) and set(listed) == paths
        syntax = {'python': 0, 'json': 0}
        for item in value['files']:
            p = ROOT / item['path']
            assert not any(part in {'private', 'source-private', 'local-private', 'pro-results'}
                           for part in p.relative_to(HERE).parts)
            if p.suffix == '.py':
                ast.parse(p.read_text(encoding='utf-8-sig'), filename=str(p))
                syntax['python'] += 1
            elif p.suffix == '.json':
                json.loads(p.read_text(encoding='utf-8-sig'))
                syntax['json'] += 1
        result['syntax'] = syntax
        result['allowlist_paths'] = len(listed)
    result['failures'] = failures
    print(json.dumps(result, ensure_ascii=False))
    assert failures == 0


if __name__ == '__main__':
    main()
