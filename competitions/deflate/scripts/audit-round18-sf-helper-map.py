"""Find exact token-structure helper reuse; no behavioral equivalence claim."""
from pathlib import Path
import hashlib
import json
import re

ROOT = Path(__file__).resolve().parents[1]
TOKEN = re.compile(r'[A-Za-z_][A-Za-z_0-9]*|[0-9][A-Za-z_0-9]*|[^\s]')
KEEP = set('pub fn const let mut if else while for in return break continue as true false usize u8 u16 u32 u64 u128 i8 i16 i32 i64 bool Vec Option Some None Self crate super match loop impl use std core alloc'.split())


def items(source):
    # These sources contain no braces in strings inside the selected SF closure.
    source = re.sub(r'//[^\n]*', '', source)
    result = {}
    for match in re.finditer(r'pub fn (\w+)\s*(?:<[^\n]*?>)?\s*\(', source):
        start = match.start()
        a = source.index('{', match.end())
        end, depth = a + 1, 1
        while depth:
            depth += (source[end] == '{') - (source[end] == '}')
            end += 1
        result[match[1]] = source[start:end]
    for match in re.finditer(r'pub const (\w+)[^=]*=', source):
        end = source.index(';', match.end()) + 1
        result[match[1]] = source[match.start():end]
    return result


def fingerprints(declarations):
    cache, pending = {}, set()

    def one(name):
        if name in cache:
            return cache[name]
        if name in pending:
            return 'RECURSIVE:' + name
        pending.add(name)
        tokens = TOKEN.findall(declarations[name])
        local, normalized = {}, []
        for index, token in enumerate(tokens):
            if token == name:
                value = '@SELF'
            elif token in declarations:
                value = '@DECL:' + one(token)
            elif token in KEEP or not re.fullmatch(r'[A-Za-z_][A-Za-z_0-9]*', token):
                value = token
            elif index and tokens[index - 1] == '.':
                value = '.' + token
            else:
                value = '@VAR:' + str(local.setdefault(token, len(local)))
            normalized.append(value)
        digest = hashlib.sha256(' '.join(normalized).encode()).hexdigest()
        cache[name] = digest
        pending.remove(name)
        return digest

    for name in declarations:
        one(name)
    return cache


def main():
    source = items((ROOT / 'references/round18-public-591/parse.rs').read_text())
    target = items((ROOT / 'candidates/r18-586-selective-rf/parse.rs').read_text())
    sf, tf = fingerprints(source), fingerprints(target)
    wanted, queue = {'SFshape'}, ['SFshape']
    while queue:
        name = queue.pop()
        for other in TOKEN.findall(source[name]):
            if other in source and other not in wanted:
                wanted.add(other)
                queue.append(other)
    mapped = {name: [other for other, digest in tf.items() if digest == sf[name]] for name in sorted(wanted)}
    result = {'status': 'SOURCE_TOKEN_STRUCTURE_DIAGNOSTIC_NOT_PROOF',
              'source': 'references/round18-public-591/parse.rs',
              'target': 'candidates/r18-586-selective-rf/parse.rs',
              'closure_items': len(wanted), 'closure_bytes': sum(len(source[n].encode()) for n in wanted),
              'mapped': {n: v for n, v in mapped.items() if v}, 'unmapped': [n for n, v in mapped.items() if not v],
              'scope': 'Alpha-renamed token structure including recursive dependency fingerprints; literal values/operators/types preserved. This is a reuse search, not a Rust AST or equivalence proof. Actual native output and full gate are still required.'}
    (ROOT / 'evidence/round18/sf-helper-map.json').write_bytes((json.dumps(result, indent=2) + '\n').encode())
    print(json.dumps(result, indent=2))


if __name__ == '__main__':
    main()
