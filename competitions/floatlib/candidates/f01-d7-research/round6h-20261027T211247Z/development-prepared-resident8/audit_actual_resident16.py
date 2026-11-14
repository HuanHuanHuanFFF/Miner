"""Existing40607316341 bytes only: exact selected C/object linkage and all cases."""
from pathlib import Path
import collections
import hashlib
import json
import re

HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p / 'competitions/floatlib/pins.json').is_file())
EVIDENCE = HERE.parent / ('ci-runs/40607316341/download-86f74aadcd134570a1c86bacf233a1b2/'
    'diagnostics/f01-d7-public-suite/public-suite/diagnostics/f01-r22-dev-multistatic-cost1')
RUNTIME = EVIDENCE / 'runtime-cost'
SOURCE = 'fd4e5b5144d00f3413b0b367a748e9be8f55d51017b4a8aaa5be53d404b1d6c1'
sha = lambda b: hashlib.sha256(b).hexdigest()


def functions(text):
    result = {}
    for m in re.finditer(r'(?m)^LEAN_EXPORT [^;\n]+?\b(\w+)\(([^;\n]*)\)\{', text):
        start = text.index('{', m.start())
        end, level = start + 1, 1
        while level:
            level += (text[end] == '{') - (text[end] == '}')
            end += 1
        result[m.group(1)] = {'body': text[m.start():end],
            'args': m.group(2), 'line': text.count('\n', 0, m.start()) + 1}
    return result


def eligible(c):
    return c['n'] > 1 and c['m'] >= 4 and c['p'] >= 4


def main():
    bindings = {}
    def raw(path):
        b = path.read_bytes()
        bindings[str(path.relative_to(ROOT)).replace('\\', '/')] = sha(b)
        return b
    def read(path): return json.loads(raw(path))
    result = read(RUNTIME / 'result.json')
    prep = read(RUNTIME / 'prepare.json')
    cindex = read(EVIDENCE / 'candidate-c-index.json')
    aindex = read(EVIDENCE / 'native-assembly-index.json')
    assert result['complete'] and result['measurement_complete'] and result['official_originals_unchanged']
    assert result['source_sha256'] == SOURCE
    c_entry = next(x for x in cindex if x['module'] == 'Submission')
    c_raw = raw(EVIDENCE / c_entry['file'])
    assert sha(c_raw) == c_entry['sha256'] == next(v for k,v in prep['original_build_before'].items() if k.endswith('/ir/Submission.c'))
    assert raw(RUNTIME / 'original-statement-Submission.c') == c_raw
    obj = next(v for k,v in prep['original_build_before'].items() if k.endswith('/ir/Submission.c.o.export'))
    assert all(x['object_sha256'] == obj for x in aindex
        if x.get('kind') == 'actual-built-object-disassembly' and x.get('source','').endswith('/Submission.c.o.export'))
    funcs = functions(c_raw.decode())
    names = ['wordLoop___redArg', 'runDot___redArg', 'tile___redArg',
             'tiles___redArg', 'tiles___redArg___lam__0', 'rows4___redArg',
             'packA', 'packA___lam__0', 'packBGroup', 'packBGroup___lam__0', 'core___redArg', 'guarded']
    selected = {}
    excerpt = []
    for short in names:
        name = 'lp_competition_Submission_R22Resident16_' + short
        f = funcs[name]
        body = f['body']
        calls = collections.Counter(re.findall(r'\b((?:lean_|lp_competition_)\w+)\(', body))
        selected[short] = {'symbol': name, 'line': f['line'], 'body_sha256': sha(body.encode()),
            'argument_count': len(f['args'].split(',')), 'float_argument_count': f['args'].count('float '),
            'primitive_counts': {n: body.count(n + '(') for n in ('lean_array_uget_borrowed', 'lean_float32_mul',
                'lean_float32_add', 'lean_alloc_ctor', 'lean_alloc_closure', 'lean_box_float32', 'lean_float32_of_bits')},
            'alloc_requests': re.findall(r'lean_alloc_ctor\(([^)]*)\)', body),
            'direct_calls': dict(calls)}
        excerpt.append(body)
    hot = funcs['lp_competition_Submission_R22Resident16_wordLoop___redArg']['body']
    assert hot.count('lean_array_uget_borrowed(') == 2
    assert hot.count('lean_float32_mul(') == hot.count('lean_float32_add(') == 16
    assert hot.count('lean_alloc_ctor(') == 1
    assert not any(x in hot for x in ('lean_float32_of_bits(', 'lean_box_float32(', 'lean_apply_', 'lean_nat_'))
    # Its only allocation is in the terminal return arm, before the nonterminal else.
    terminal, backedge = hot.split('\nelse\n', 1)
    assert 'lean_alloc_ctor(' in terminal and 'return ' in terminal
    assert 'lean_alloc_ctor(' not in backedge and 'goto _start;' in backedge
    extracted = '\n\n'.join(excerpt).encode()
    (HERE / 'resident16-selected-actual.c').write_bytes(extracted)
    # Audit exact captured native tile caller. The actual wordLoop ASM was omitted by capture.
    symbol = 'lp_competition_Submission_R22Resident16_tile___redArg'
    tile_entry = next(x for x in aindex if x.get('symbol') == symbol)
    tile_raw = raw(EVIDENCE / tile_entry['file'])
    assert sha(tile_raw) == tile_entry['sha256'] and tile_entry['kernel_sha256'] == SOURCE
    tile_asm = tile_raw.decode().split('<' + symbol + '>:', 1)[1]
    assert 'lp_competition_Submission_R22Resident16_wordLoop___redArg-0x4' in tile_asm
    missing = [s for s in ('wordLoop___redArg', 'runDot___redArg')
        if not any(x.get('symbol') == 'lp_competition_Submission_R22Resident16_' + s for x in aindex)]
    (HERE / 'resident16-tile-actual.asm.txt').write_text(tile_asm, encoding='utf-8')
    # Every frozen control block is retained. The resident pairs are12->13 and15->14.
    pairs, drift = [], []
    for seed in (2220001, 2220003):
        plan = read(RUNTIME / f'plan-{seed}.json')
        cases = [c for c in plan['cases'] if c['timed']]
        all_rows = {order: read(RUNTIME / f'{seed}-{order}-control-rows.json') for order in (0,3,4,7,8,11,12,15)}
        for op in ('add','mul','sum','bmm','whole'):
            chosen = [c for c in cases if op == 'whole' or c['kernel'] == op]
            values = {o: sum(rows[c['name']]['best_ns'] for c in chosen) for o, rows in all_rows.items()}
            drift.append({'seed': seed, 'kernel': op, 'control_sums_ns_by_order': values,
                          'max_over_min': max(values.values()) / min(values.values())})
        for control, variant in ((12,13), (15,14)):
            cr = all_rows[control]
            vr = read(RUNTIME / f'{seed}-{variant}-resident16-rows.json')
            assert set(vr) == set(cr) == {c['name'] for c in plan['cases']}
            assert all(vr[n]['checksum'] == cr[n]['checksum'] for n in cr)
            buckets = {}
            for name, pred in [('whole',lambda c:True), ('add',lambda c:c['kernel']=='add'),
                ('mul',lambda c:c['kernel']=='mul'), ('sum',lambda c:c['kernel']=='sum'),
                ('bmm',lambda c:c['kernel']=='bmm'),
                ('bmm_static_eligible',lambda c:c['kernel']=='bmm' and eligible(c)),
                ('bmm_static_miss',lambda c:c['kernel']=='bmm' and not eligible(c))]:
                group = [c for c in cases if pred(c)]
                cns = sum(cr[c['name']]['best_ns'] for c in group)
                vns = sum(vr[c['name']]['best_ns'] for c in group)
                buckets[name] = {'cases': len(group), 'control_ns': cns, 'variant_ns': vns,
                    'variant_over_control': vns/cns, 'delta_ns': vns-cns}
            detail = []
            for c in cases:
                if c['kernel'] != 'bmm': continue
                ct, vt = cr[c['name']]['best_ns'], vr[c['name']]['best_ns']
                detail.append({'name': c['name'], 'shape': [c['batch'],c['m'],c['n'],c['p']],
                    'static_eligible': eligible(c), 'control_ns': ct, 'variant_ns': vt,
                    'ratio': vt/ct, 'delta_ns': vt-ct, 'tail_rows': c['m']%4,
                    'extra_padded_cols_vs_pair2': 4*((c['p']+3)//4)-2*((c['p']+1)//2),
                    'specRate': c['specRate'], 'subPct': c['subPct']})
            pairs.append({'seed': seed,'control_order':control,'variant_order':variant,
                'all156_checksums_match': True,'buckets':buckets,
                'BMM_cases_by_delta_ns':sorted(detail,key=lambda x:x['delta_ns'])})
    report = {'source_sha256': SOURCE, 'actual_Submission_C_sha256': sha(c_raw),
        'measured_linked_Submission_object_sha256': obj, 'object_prepost_binding': 'prepare baseline + unchanged final checks',
        'actual_selected_C':selected,'selected_C_file_sha256':sha(extracted),
        'wordLoop_C_nonterminal_16_independent_native_MACs_two_borrowed_reads_no_codec_alloc_apply': True,
        'native_tile': {'symbol':symbol,'file':tile_entry['file'],'sha256':sha(tile_raw),
            'calls_wordLoop_out_of_line':True,'initial_extra_FP_stack_argument_bytes':64,
            'local_frame_bytes':184,'terminal_16_Float32_save_finish_cost_present':True},
        'missing_actual_native_functions':missing,'actual_wordLoop_SIMD_and_hot_spill':'UNKNOWN_MISSING_CAPTURE',
        'fallback': 'OuterUnderflowZero; eligible core; miss calls retained public bmm and repeats UnderflowZero check.',
        'pairs':pairs,'all_controls':drift,'input_bindings':bindings,
        'limits':['No new source, seed, kernel, build or CI.',
            'C confirms native parameters/operations, not final SIMD/register allocation.',
            'Static eligible case costs include prep/output/tails/replay, not isolated hot-loop time.',
            'Control variation and changes to untargeted operations cannot be assigned to BMM.',
            'Whole corrected-for-other-ops counterfactuals are not measured gate/adoption scores.']}
    (HERE / 'resident16-actual-review.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf-8')
    print(json.dumps({'object':obj,'C':sha(c_raw),'missing_ASM':missing,
        'pairs':[{'seed':p['seed'],'control':p['control_order'],'buckets':p['buckets']} for p in pairs],
        'control_ranges':[{'seed':r['seed'],'op':r['kernel'],'max_over_min':r['max_over_min']} for r in drift]}))


if __name__ == '__main__':
    main()
