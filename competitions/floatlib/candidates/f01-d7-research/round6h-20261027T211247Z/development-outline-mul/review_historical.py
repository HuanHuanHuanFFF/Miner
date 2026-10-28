"""Recheck the precise timed 748999 caller bytes recovered by read-only GitHub API."""
from pathlib import Path
from collections import Counter
import hashlib
import json
import re

HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p / 'AGENTS.md').is_file())
SHA = lambda p: hashlib.sha256(p.read_bytes()).hexdigest()


def functions(raw):
    result, name = {}, None
    for line in raw.splitlines():
        m = re.fullmatch(r'[0-9a-f]+ <([^>]+)>:', line)
        if m:
            name = m[1]
            result[name] = []
            continue
        m = re.match(r'\s*([0-9a-f]+):\s+(\S+)\s*(.*)', line)
        if name and m and not m[2].startswith('R_'):
            result[name].append({'address': int(m[1], 16), 'op': m[2], 'args': m[3], 'line': line})
    return result


def body(c, symbol):
    starts = list(re.finditer(r'LEAN_EXPORT [^\n]+?\b' + re.escape(symbol) + r'\([^\n]*\)\{\n', c))
    assert len(starts) == 1, symbol
    start = starts[0].start()
    depth = 0
    for i in range(c.index('{', start), len(c)):
        if c[i] == '{':
            depth += 1
        elif c[i] == '}':
            depth -= 1
            if not depth:
                return c[start:i + 1] + '\n'
    raise AssertionError(symbol)


def main():
    cpath = HERE / 'historical-40432634558-Main.c'
    apath = HERE / 'historical-40432634558-Main.asm.txt'
    assert SHA(cpath) == '24770ecaad37241f73605bac97e4273604355e85fc893f57e59ccb7d2caa1ed9'
    assert SHA(apath) == '0d85c8736a3b9b1dcb8a866ecdf10ca36ee8fe1ebbd5b286c5789266b7ef288e'
    inventory = json.loads((ROOT / 'competitions/floatlib/evidence/maintenance-20261027/recoverable-evidence.json').read_bytes())
    bound = []
    for end, p in [('/build-product-0-R19RuntimeCostMain.c', cpath), ('/own-object-0-asm.txt', apath)]:
        old_path, item = next((k, v) for k, v in inventory['entries'].items() if '40432634558' in k and k.endswith(end))
        assert SHA(p) == item['sha256'] and p.stat().st_size == item['bytes']
        bound.append({'original_path': old_path, 'recovered_path': p.name, **item,
                      'recovery': 'Read-only connected GitHub fetch_blob; no Git CLI or index modification.'})
    c = cpath.read_text()
    fs = functions(apath.read_text())
    name = 'lp_competition_main___lam__1'
    ranges = [(0, 0x2d), (0x76, 0x88), (0x122, 0x12f), (0x33d, 0x3a4), (0xc06, 0xc12)]
    fast = [i for i in fs[name] if any(lo <= i['address'] <= hi for lo, hi in ranges)]
    assert not any(i['op'].startswith('call') for i in fast)
    assert not any('xmm' in i['args'] or ' PTR [' in i['args'] for i in fast)
    assert sum(i['op'] == 'imul' for i in fast) == 1
    pushes = [i['args'] for i in fast if i['op'] == 'push']
    pops = [i['args'] for i in fast if i['op'] == 'pop']
    assert pushes == ['rbp', 'r15', 'r14', 'r12', 'rbx']
    assert pops == list(reversed(pushes))
    assert any(i['op'] == 'sub' and i['args'] == 'rsp,0x10' for i in fast)
    assert any(i['op'] == 'add' and i['args'] == 'rsp,0x10' for i in fast)
    selected = body(c, name)
    assert 'uint8_t ' in selected.splitlines()[0]
    assert 'diagnosticEntry' not in c and not re.search(r'lp_competition_r19CostGuardedMul\s*\(', selected)
    (HERE / 'historical-selected-guarded.c').write_text(selected, newline='')
    (HERE / 'historical-selected-hot-path.asm.txt').write_text('\n'.join(i['line'] for i in fast) + '\n', newline='')
    compiler_root = ROOT / 'competitions/floatlib/research/materials/20261024-r11/originals/W03/original-extracted/R11-W03/agent-runtime/primary'
    compiler_manifest = json.loads((compiler_root / 'manifest.json').read_bytes())
    compiler_bound = []
    for relative in ('src/Lean/Compiler/InlineAttrs.lean', 'src/Lean/Compiler/LCNF/Simp/InlineCandidate.lean',
                     'src/Lean/Compiler/LCNF/EmitC.lean', 'src/Lean/Compiler/LCNF/ExplicitBoxing.lean'):
        item = next(x for x in compiler_manifest if x['path'] == relative)
        p = compiler_root / relative
        assert p.stat().st_size == item['bytes'] and SHA(p) == item['sha256']
        assert '/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/' in item['url']
        compiler_bound.append(item)
    result = {
        'source': '74899988939a056a40675aefe8c63f2f9db1c7b4728f3d496bf140ede6ad85dc',
        'timed_diagnostic_run': 40432634558,
        'original_bytes_recovered_and_rehashed': bound,
        'timed_callback': name,
        'typed_signature': selected.splitlines()[0],
        'selected_body_sha256': hashlib.sha256(selected.encode()).hexdigest(),
        'accepted_ranges_hex': [[hex(a), hex(b)] for a, b in ranges],
        'accepted_instruction_count_not_cycles': len(fast),
        'accepted_opcodes': dict(Counter(i['op'] for i in fast)),
        'accepted_one_imul_no_call_FP_table_or_explicit_data_spill': True,
        'accepted_pushes': pushes, 'accepted_pops': pops, 'accepted_frame_bytes': 16,
        'captured_Bool_arity3_still_present_in_precise_old_Main': True,
        'original_MainFull_absolute_cost_equivalence': 'NOT_ESTABLISHED; old timed harness captured Bool arity3',
        'compiler_sources_pinned_and_rehashed': compiler_bound,
        'noinline_conclusion': 'Lean noinline blocks ordinary LCNF inlining. EmitC emits LEAN_EXPORT C functions, not an explicit native noinline attribute here; actual translation-unit/link boundary and caller ASM still decide.',
        'new_candidate_codegen': 'NOT_RUN', 'new_candidate_performance': 'NOT_RUN',
        'native_ELF_local_rehash': 'NOT_AVAILABLE; recovered native disassembly is bound to historical remote object identity only.'
    }
    (HERE / 'historical-review.json').write_text(json.dumps(result, ensure_ascii=False, indent=2) + '\n', encoding='utf-8')
    print(json.dumps({'exact_old_C_ASM_rehashed': True, 'accepted_instructions': len(fast), 'pushes': pushes,
                      'frame_bytes': 16, 'compiler_sources_rehashed': len(compiler_bound)}))


if __name__ == '__main__':
    main()
