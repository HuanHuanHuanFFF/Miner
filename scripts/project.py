"""Read-only task lookup, legacy-path resolution, and repository checks."""
from pathlib import Path
import argparse
import ast
import hashlib
import json
import os
import re
import sys
from urllib.parse import unquote

ROOT = Path(__file__).resolve().parents[1]


def read(name):
    return json.loads((ROOT / name).read_text(encoding='utf-8'))


def aliases():
    return read('docs/path-aliases.json')


def resolve(name):
    value = name.replace('\\', '/').split('#', 1)[0]
    value = re.sub(r':\d+$', '', value)
    p = Path(value)
    if p.is_absolute():
        value = p.relative_to(ROOT).as_posix()
    else:
        while value.startswith('./'):
            value = value[2:]
    value = os.path.normpath(value).replace('\\', '/')
    mapping, seen = aliases(), set()
    mapping = {key.casefold(): record for key, record in mapping.items()}
    while value.casefold() in mapping:
        key = value.casefold()
        if key in seen:
            raise ValueError('路径映射循环: ' + value)
        seen.add(key)
        value = mapping[key]['path']
    target = (ROOT / value).resolve()
    if not target.is_relative_to(ROOT):
        raise ValueError('路径不在仓库内')
    return target


def show_tasks(query=None):
    catalog = read('docs/tasks.json')
    words = query.casefold().split() if query else []
    found = []
    for task in catalog['tasks']:
        haystack = ' '.join([task['id'], task['title'], task['decision'], task['report'], *task['tags'], *task['evidence']]).casefold()
        if words and not all(word in haystack for word in words):
            continue
        found.append(task)
        print(task['id'] + ' | ' + task['title'])
        print('  结论: ' + task['decision'])
        print('  报告: ' + str(ROOT / task['report']))
        print('  证据: ' + ', '.join(task['evidence']))
        conversation = task.get('conversation', catalog['conversation'])
        caption = conversation.get('title', '')
        print('  会话: ' + (caption + ' / ' if caption else '') + conversation['thread_id'])
    print(f"匹配 {len(found)} 个任务")
    return 0 if found else 1


def candidates(query=None):
    count = 0
    for source in sorted((ROOT / 'candidates').glob('*/parse.rs')):
        folder = source.parent
        if query and query.casefold() not in folder.name.casefold():
            continue
        proof = folder / 'Parse.lean'
        if not proof.is_file():
            continue
        count += 1
        files = {p.name: {'bytes': p.stat().st_size, 'sha256': hashlib.sha256(p.read_bytes()).hexdigest()} for p in (source, proof)}
        print(json.dumps({'candidate': folder.name, 'files': files,
                          'verification_record': (folder / 'VERIFICATION.json').is_file(),
                          'upload_file_limits_ok': all(v['bytes'] <= 524288 for v in files.values())}, ensure_ascii=False))
    print(f'共 {count} 个源码／证明包；verification_record 只表示文件存在，具体通过范围见原记录。')
    return 0 if count else 1


def check():
    failures, counts, digest_cache = [], {}, {}
    def digest(path):
        if path not in digest_cache:
            digest_cache[path] = hashlib.sha256(path.read_bytes()).hexdigest()
        return digest_cache[path]
    catalog = read('docs/tasks.json')
    ids = [t['id'] for t in catalog['tasks']]
    if len(ids) != len(set(ids)):
        failures.append('任务 ID 重复')
    for task in catalog['tasks']:
        for name in [task['report'], *task['evidence']]:
            if not resolve(name).exists():
                failures.append('任务路径缺失: ' + name)
    counts['tasks'] = len(ids)
    for old, record in aliases().items():
        target = resolve(old)
        if not target.exists():
            failures.append('映射目标缺失: ' + old)
        elif record.get('sha256') and digest(target) != record['sha256']:
            failures.append('去重目标哈希不一致: ' + old)
    counts['aliases'] = len(aliases())
    markdown = [ROOT / 'README.md', ROOT / 'AGENTS.md', *(ROOT / 'docs').rglob('*.md')]
    link_count = 0
    for path in markdown:
        text = path.read_text(encoding='utf-8')
        for match in re.finditer(r'\]\((<[^>]+>|[^)\n]+)\)', text):
            name = match[1].strip('<>')
            if re.match(r'[a-z][a-z0-9+.-]*://|mailto:', name, re.I):
                continue
            name = unquote(name.split('#', 1)[0])
            if not name:
                continue
            name = re.sub(r':\d+$', '', name)
            target = ROOT / name.lstrip('/') if name.startswith('/') else path.parent / name
            try:
                relative = target.resolve().relative_to(ROOT).as_posix()
                if not resolve(relative).exists():
                    failures.append(f'{path.relative_to(ROOT)}: 链接缺失 {name}')
            except ValueError:
                failures.append(f'{path.relative_to(ROOT)}: 非仓库文件链接 {name}')
            link_count += 1
    counts['markdown_files'] = len(markdown)
    counts['local_links'] = link_count
    try:
        import yaml
    except ImportError:
        failures.append('工作流自检需要本地 PyYAML；未运行这一项')
    else:
        workflows = [p for p in (ROOT / '.github/workflows').iterdir() if p.suffix in ('.yml', '.yaml')]
        for path in workflows:
            document = yaml.safe_load(path.read_text(encoding='utf-8'))
            events = document.get('on', document.get(True))
            if set(events or {}) != {'workflow_dispatch'}:
                failures.append(path.name + ': 含自动触发事件')
            if document.get('concurrency', {}).get('cancel-in-progress') is not False:
                failures.append(path.name + ': 可能自动取消运行')
            inputs = (events or {}).get('workflow_dispatch', {}).get('inputs', {})
            if inputs.get('allow_private', {}).get('default') is not False:
                failures.append(path.name + ': 私有运行开关默认不正确')
            for script in re.findall(r'\bscripts/[A-Za-z0-9._/-]+', path.read_text(encoding='utf-8')):
                if not (ROOT / script).is_file():
                    failures.append(path.name + ': 脚本缺失 ' + script)
        counts['manual_workflows'] = len(workflows)
    manifests = 0
    for folder in (ROOT / 'candidates').iterdir():
        manifest = folder / 'manifest.json'
        if not manifest.is_file():
            continue
        data = json.loads(manifest.read_text(encoding='utf-8'))
        bound = data.get('hashes') or {}
        checked = 0
        for name in ('parse.rs', 'Parse.lean'):
            expected = bound.get(name)
            if not isinstance(expected, str) or not re.fullmatch(r'[0-9a-f]{64}', expected):
                continue
            if not (folder / name).is_file() or digest(folder / name) != expected:
                failures.append(folder.name + ': manifest 哈希不一致 ' + name)
            checked += 1
        if checked == 2:
            manifests += 1
    counts['candidate_hash_pairs'] = manifests
    for path in (ROOT / 'scripts').glob('*.py'):
        try:
            ast.parse(path.read_text(encoding='utf-8'))
        except (SyntaxError, UnicodeError) as error:
            failures.append(str(path.relative_to(ROOT)) + ': ' + str(error))
    result = {'status': 'PASS' if not failures else 'FAIL', 'checks': counts, 'failures': failures,
              'scope': '本地任务／路径／字节／配置／语法自检，不运行 CI、Rust、Lean 或链操作。'}
    print(json.dumps(result, ensure_ascii=False, indent=2))
    return 1 if failures else 0


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    commands = parser.add_subparsers(dest='command', required=True)
    commands.add_parser('tasks')
    commands.add_parser('check')
    find = commands.add_parser('find'); find.add_argument('query')
    paths = commands.add_parser('resolve'); paths.add_argument('path')
    bundles = commands.add_parser('candidates'); bundles.add_argument('query', nargs='?')
    args = parser.parse_args()
    if args.command in ('tasks', 'find'):
        return show_tasks(getattr(args, 'query', None))
    if args.command == 'candidates':
        return candidates(args.query)
    if args.command == 'resolve':
        path = resolve(args.path)
        print(path)
        return 0 if path.exists() else 1
    return check()


if __name__ == '__main__':
    raise SystemExit(main())
