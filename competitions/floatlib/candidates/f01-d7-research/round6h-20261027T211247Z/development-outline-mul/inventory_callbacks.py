"""Read-only C/object-ASM inventory. It never infers selected callbacks or performance by name alone."""
from pathlib import Path
from collections import Counter
import argparse
import hashlib
import json
import re


def c_functions(c):
    out = {}
    for m in re.finditer(r'(?m)^(?:LEAN_EXPORT|static) ([^\n{};=]+?) ([A-Za-z_]\w*)\(([^\n]*)\)\{\n', c):
        depth, end = 0, None
        for i in range(c.index('{', m.start()), len(c)):
            depth += (c[i] == '{') - (c[i] == '}')
            if depth == 0:
                end = i + 1
                break
        assert end is not None
        out[m[2]] = {'return_type': m[1], 'parameters': m[3], 'start': m.start(), 'end': end,
                     'body_sha256': hashlib.sha256(c[m.start():end].encode()).hexdigest(),
                     'calls': sorted(set(re.findall(r'\b(lp_competition_\w+)\s*\(', c[m.end():end])))}
    return out


def inventory(cpath, apath):
    raw = cpath.read_bytes()
    c = raw.decode()
    fs = c_functions(c)
    static = []
    for m in re.finditer(r'static const lean_closure_object (\w+)_value = .*?\.m_fun = \(void\*\)(\w+), \.m_arity = (\d+), \.m_num_fixed = (\d+)', c):
        static.append({'constant': m[1], 'function': m[2], 'arity': int(m[3]), 'fixed': int(m[4]),
                       'typed_function': fs.get(m[2].removesuffix('___boxed'))})
    dynamic = []
    for m in re.finditer(r'(\w+) = lean_alloc_closure\(\(void\*\)\((\w+)\), (\d+), (\d+)\);', c):
        owner = next((k for k, v in fs.items() if v['start'] < m.start() < v['end']), None)
        dynamic.append({'variable': m[1], 'function': m[2], 'arity': int(m[3]), 'fixed': int(m[4]),
                        'owner_function': owner, 'typed_function': fs.get(m[2].removesuffix('___boxed'))})
    asm, name, last = {}, None, None
    for line in apath.read_text().splitlines():
        m = re.fullmatch(r'[0-9a-f]+ <([^>]+)>:', line)
        if m:
            name, last = m[1], None
            asm[name] = {'instructions': [], 'relocations': []}
            continue
        if not name:
            continue
        relocation = re.search(r'R_X86_64_\S+\s+(\S+)', line)
        if relocation:
            asm[name]['relocations'].append({'at_instruction': last, 'target': relocation[1], 'line': line})
            continue
        m = re.match(r'\s*([0-9a-f]+):\s+(\S+)\s*(.*)', line)
        if m:
            last = {'address': '0x' + m[1], 'op': m[2], 'args': m[3]}
            asm[name]['instructions'].append(last)
    shapes = {}
    for name, data in asm.items():
        ins = data['instructions']
        shapes[name] = {'instruction_count_not_cycles': len(ins), 'opcodes': dict(Counter(i['op'] for i in ins)),
                        'pushes': [i for i in ins if i['op'] == 'push'],
                        'frame_adjustments': [i for i in ins if i['op'] in ('sub', 'add') and i['args'].startswith('rsp,')],
                        'external_relocations': data['relocations']}
    return {'C': {'path': str(cpath), 'bytes': len(raw), 'sha256': hashlib.sha256(raw).hexdigest()},
            'ASM': {'path': str(apath), 'bytes': apath.stat().st_size,
                    'sha256': hashlib.sha256(apath.read_bytes()).hexdigest()},
            'static_closures': static, 'dynamic_closure_sites': dynamic, 'C_function_graph': fs,
            'ASM_function_shapes': shapes,
            'verdict': 'INVENTORY_ONLY; trace each runner Suite call to closure and typed body manually, then audit exact hot/miss paths. No source/correctness/performance PASS is implied.'}


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--c', type=Path, required=True)
    parser.add_argument('--asm', type=Path, required=True)
    parser.add_argument('--out', type=Path, required=True)
    args = parser.parse_args()
    data = inventory(args.c, args.asm)
    args.out.write_text(json.dumps(data, indent=2) + '\n', encoding='utf-8')
    print(json.dumps({'static_closures': len(data['static_closures']),
                      'dynamic_closure_sites': [{'arity': c['arity'], 'fixed': c['fixed'], 'owner': c['owner_function']}
                                                for c in data['dynamic_closure_sites']],
                      'verdict': 'INVENTORY_ONLY'}))


if __name__ == '__main__':
    main()
