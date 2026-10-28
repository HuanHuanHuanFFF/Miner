"""Independent source/actual-caller/32-process audit of the new complete diagnostic."""
from pathlib import Path
import hashlib
import json
import re
import shlex
from inventory_callbacks import inventory
from review_historical import functions, body
from review_old_cost import rows, totals
from static_runner_audit import audit_static_runners

HERE = Path(__file__).resolve().parent
ROUND = HERE.parent
RUN = ROUND / 'ci-runs/40607316341'
RAW = RUN / 'download-86f74aadcd134570a1c86bacf233a1b2'
BASE = RAW / 'diagnostics/f01-d7-public-suite/public-suite/diagnostics/f01-r22-dev-multistatic-cost1'
COST = BASE / 'runtime-cost'
SOURCE = 'fd4e5b5144d00f3413b0b367a748e9be8f55d51017b4a8aaa5be53d404b1d6c1'
sha = lambda p: hashlib.sha256(p.read_bytes()).hexdigest()


def save(name, data):
    (HERE / name).write_text(json.dumps(data, ensure_ascii=False, indent=2) + '\n', encoding='utf-8')


def norm_c(source):
    source = re.sub(r'\b(lp_competition_\w+)\(', 'FUNCTION(', source, count=1)
    names = {}
    return re.sub(r'\bv_\w+\b', lambda m: names.setdefault(m[0], f'v{len(names)}'), source)


def argv(p):
    d = json.loads(p.read_bytes())
    commands = [x['message'][3:] for x in d['log'] if x['message'].startswith('.> ')]
    assert len(commands) == 1
    return shlex.split(commands[0])


def norm_args(values):
    out = []
    for value in values:
        value = value.replace('/MainFull.', '/<ROOT>.').replace('/R22MultiStaticCostMain.', '/<ROOT>.')
        value = value.replace('/benchFull.', '/<EXE>.').replace('/r22MultiStaticCost.', '/<EXE>.')
        for name in ('benchFull', 'r22MultiStaticCost'):
            if value.endswith('/' + name):
                value = value[:-len(name)] + '<EXE>'
        out.append(value)
    return out


def main():
    artifact = json.loads((RUN / 'original-artifact-hashes.json').read_bytes())
    assert artifact['artifact']['workflow_run']['head_sha'].startswith('11d392ce')
    bindings, total_bytes = [], 0
    for relative, item in artifact['files'].items():
        p = RAW / relative
        assert p.stat().st_size == item['bytes'] and sha(p) == item['sha256'], relative
        bindings.append({'path': str(p), **item})
        total_bytes += item['bytes']
    source_rel = next(k for k in artifact['files'] if '/inputs/f01-r22-dev-multistatic-cost1/Kernel.lean' in k)
    source = RAW / source_rel
    assert sha(source) == SOURCE and source.read_bytes().startswith((HERE / 'Kernel.lean').read_bytes())
    cpath, apath = COST / 'build-product-0-R22MultiStaticCostMain.c', COST / 'own-object-0-asm.txt'
    c, asm = cpath.read_text(), apath.read_text()
    assert sha(cpath) == '6f226ced069d97a51638960813316e28d884cbbc5943386fbd0b1abfffe4c48a'
    pref = audit_static_runners(cpath.read_bytes())
    save('actual406073-strong-C-audit.json', pref)
    inv = inventory(cpath, apath)
    fs = functions(asm)
    closures = {x['constant']: x for x in inv['static_closures']}
    chains = {}
    for name in pref['wanted_entries']:
        sym = pref['entries'][name]['symbol']
        fn = inv['C_function_graph'][sym]
        cb = c[fn['start']:fn['end']]
        local = dict(re.findall(r'(?m)^(\w+) = \(\(lean_object\*\)\((\w+)\)\);$', cb))
        calls = re.findall(r'lp_competition_Bench_Suite_run\(([^)]+)\)', cb)
        assert len(calls) == 1
        args = [x.strip() for x in calls[0].split(',')]
        assert len(args) == 4
        chosen = [closures[local[a]] for a in args]
        mul_box = chosen[1]['function']
        mul = mul_box.removesuffix('___boxed')
        typed = inv['C_function_graph'][mul]
        assert chosen[1]['arity'] == 2 and chosen[1]['fixed'] == 0
        assert typed['return_type'] == 'uint32_t'
        assert re.fullmatch(r'uint32_t \w+, uint32_t \w+', typed['parameters'])
        assert mul in inv['C_function_graph'][mul_box]['calls']
        chains[name] = {'Suite_arguments_add_mul_sum_bmm': [{k: x[k] for k in ('constant', 'function', 'arity', 'fixed')} for x in chosen],
                        'mul_boxed': mul_box, 'mul_typed': mul, 'typed_parameters': typed['parameters'],
                        'runner_C_body_sha256': fn['body_sha256']}
    shared = chains['runControl']['Suite_arguments_add_mul_sum_bmm']
    assert all(chains[n]['Suite_arguments_add_mul_sum_bmm'][i] == shared[i]
               for n in ('runInlineOld', 'runOutline', 'runNativeProduct') for i in (0, 2, 3))
    outline, old = chains['runOutline']['mul_typed'], chains['runInlineOld']['mul_typed']
    hot = fs[outline]
    assert len(hot) == 45 and sum(x['op'] == 'imul' for x in hot) == 1
    assert not any(x['op'] in ('push', 'pop', 'call') or 'xmm' in x['args'] or 'rsp' in x['args'] or ' PTR [' in x['args'] for x in hot)
    rel = inv['ASM_function_shapes'][outline]['external_relocations']
    assert len(rel) == 3 and all(x['at_instruction']['op'] == 'jbe' and
        x['target'] == 'lp_competition_Submission_R22OutlineMul_retainedMul-0x4' for x in rel)
    assert [x['at_instruction']['address'] for x in rel] == ['0x14', '0x2e', '0x43']
    assert not any(x['args'].split(',')[0] in ('rdi', 'rsi', 'edi', 'esi')
                   and x['op'] not in ('cmp', 'test') for x in hot if x['address'] <= 0x43)
    ranges = [(0, 0x2d), (0x74, 0x86), (0x266, 0x272), (0x45b, 0x4bd), (0xb47, 0xb53)]
    old_hot = [x for x in fs[old] if any(a <= x['address'] <= b for a, b in ranges)]
    assert len(old_hot) == 58 and [x['args'] for x in old_hot if x['op'] == 'push'] == ['rbp', 'r15', 'r14', 'r12', 'rbx']
    assert any(x['op'] == 'sub' and x['args'] == 'rsp,0x10' for x in old_hot)
    assert not any(x['op'] == 'call' or 'xmm' in x['args'] or ' PTR [' in x['args'] for x in old_hot)
    boxed = {}
    for n in ('runControl', 'runInlineOld', 'runOutline'):
        sym = chains[n]['mul_boxed']
        boxed[n] = [(x['op'], x['args'].replace(sym, '<BOXED>').replace(chains[n]['mul_typed'], '<TYPED>')) for x in fs[sym]]
    assert boxed['runControl'] == boxed['runInlineOld'] == boxed['runOutline']
    index = json.loads((BASE / 'native-assembly-index.json').read_bytes())
    retained = next(x for x in index if x.get('symbol') == 'lp_competition_Submission_R22OutlineMul_retainedMul')
    assert sha(BASE / retained['file']) == retained['sha256']
    prepare = json.loads((COST / 'prepare.json').read_bytes())
    assert retained['object_sha256'] == next(v for k, v in prepare['original_build_before'].items() if k.endswith('/Submission.c.o.export'))
    submission = (COST / 'original-statement-Submission.c').read_text()
    retained_c = body(submission, retained['symbol'])
    control_c = body(c, chains['runControl']['mul_typed'])
    retained_equals_control = norm_c(retained_c) == norm_c(control_c)
    cold_ins = functions((BASE / retained['file']).read_text())[retained['symbol']]
    control_ins = fs[chains['runControl']['mul_typed']]
    cold_norm = [(x['op'], x['args'].replace(retained['symbol'], '<MUL>')) for x in cold_ins]
    control_norm = [(x['op'], x['args'].replace(chains['runControl']['mul_typed'], '<MUL>')) for x in control_ins]
    flags = {}
    for kind in ('compile', 'link', 'link_response'):
        a, b = COST / ('original-' + kind + '.raw'), COST / ('new-' + kind + '.raw')
        aa, bb = (shlex.split(a.read_text()), shlex.split(b.read_text())) if kind == 'link_response' else (argv(a), argv(b))
        assert norm_args(aa) == norm_args(bb)
        if kind == 'compile':
            assert '-O3' in bb and not any(x.startswith('-flto') for x in bb)
        flags[kind] = {'arguments': len(aa), 'equal_after_root_target_mapping_only': True,
                       'original_sha256': sha(a), 'new_sha256': sha(b)}
    result = json.loads((COST / 'result.json').read_bytes())
    assert result['complete'] and result['measurement_complete'] and result['official_originals_unchanged']
    assert result['source_sha256'] == SOURCE and len(result['runs']) == 32
    order = ('control', 'inlineOld', 'inlineOld', 'control', 'control', 'outline', 'outline', 'control',
             'control', 'nativeprod', 'nativeprod', 'control', 'control', 'resident16', 'resident16', 'control')
    samples, blocks, outline_cases = [], [], []
    domains = json.loads((HERE / 'guard-domain-partition.json').read_bytes())
    domain_map = {(p['seed'], c['name']): c['domain'] for p in domains['plans'] for c in p['cases']}
    for seed in (2220001, 2220003):
        plan_path = COST / f'plan-{seed}.json'
        plan = json.loads(plan_path.read_bytes())
        subset = []
        for i, variant in enumerate(order):
            meta = result['runs'][len(samples)]
            assert (meta['seed'], meta['order'], meta['variant'], meta['exit_code']) == (seed, i, variant, 0)
            assert json.loads(meta['environment']['BENCH_PLAN']) == plan
            assert meta['environment']['BENCH_VARIANT'] == variant and meta['environment']['BENCH_INNER'] == '3'
            assert meta['environment']['BENCH_PAIRS'] == '500000' and meta['argv'][:3] == ['taskset', '-c', '0']
            p = COST / f'{seed}-{i}-{variant}.log'
            assert sha(p) == meta['log_sha256']
            data = rows(p.read_text(), plan)
            subset.append(data)
            samples.append({'seed': seed, 'order': i, 'variant': variant, 'ns': totals(data, plan), 'log_sha256': sha(p)})
        assert all(all(v['checksum'] == subset[0][k]['checksum'] for k, v in d.items()) for d in subset)
        stored = next(p for p in result['pairs'] if p['seed'] == seed)
        for offset, variant in ((0, 'inlineOld'), (4, 'outline'), (8, 'nativeprod'), (12, 'resident16')):
            for block, (ci, gi) in enumerate(((offset, offset + 1), (offset + 3, offset + 2))):
                ct, gt = totals(subset[ci], plan), totals(subset[gi], plan)
                ratios = {op: gt[op] / ct[op] for op in ct}
                for op in ct:
                    assert stored[f'{variant}_block_{block}'][op]['variant_over_control'] == ratios[op]
                blocks.append({'seed': seed, 'variant': variant, 'block': block, 'control_ns': ct, 'variant_ns': gt, 'ratios': ratios})
                if variant == 'outline':
                    for case in plan['cases']:
                        if case['timed'] and case['kernel'] == 'mul':
                            name = case['name']
                            outline_cases.append({'seed': seed, 'block': block, 'case': name, 'domain': domain_map[(seed, name)],
                                                  'control_ns': subset[ci][name]['ns'], 'outline_ns': subset[gi][name]['ns'],
                                                  'ratio': subset[gi][name]['ns'] / subset[ci][name]['ns']})
    (HERE / 'actual406073-outline-selected.c').write_text(body(c, outline), newline='')
    asm_start = asm.index('0000000000000000 <' + outline + '>:')
    asm_stop = asm.find('\nDisassembly of section ', asm_start)
    (HERE / 'actual406073-outline-selected.asm.txt').write_text(asm[asm_start:asm_stop if asm_stop >= 0 else len(asm)], newline='')
    save('actual406073-originals.json', {'head': artifact['artifact']['workflow_run']['head_sha'], 'count': len(bindings), 'bytes': total_bytes, 'files': bindings})
    report = {'run': 40607316341, 'source_sha256': SOURCE, 'C_sha256': sha(cpath), 'ASM_sha256': sha(apath),
              'all_originals_rehashed': len(bindings), 'raw_bytes': total_bytes, 'chains': chains,
              'actual_outline_typed': {'symbol': outline, 'instructions_not_cycles': 45, 'one_imul_no_push_pop_frame_call_FP_data_spill': True,
                                       'three_original_guard_misses_are_conditional_tail_branches': rel, 'incoming_xy_preserved_on_all_misses': True},
              'actual_inlineOld_typed': {'symbol': old, 'accepted_ranges_hex': [[hex(a), hex(b)] for a, b in ranges],
                                        'accepted_instructions_not_cycles': 58, 'push_pop_pairs': 5, 'frame_bytes': 16},
              'three_MUL_boxed_wrappers_instruction_identical_after_symbol_mapping': True,
              'cold_retained_C_normalized_equal_same_binary_B2_control': retained_equals_control,
              'cold_retained_native_shape': {'instructions_not_cycles': len(cold_ins), 'control_instructions_not_cycles': len(control_ins),
                                             'ASM_equal_after_symbol_mapping': cold_norm == control_norm,
                                             'scope': 'Both source-denote B2 but C/ASM clones differ in layout/conditions. Do not attribute all measured gains uniquely to frame deletion.'},
              'cold_retained_object_binding': retained, 'flags': flags,
              'samples': samples, 'blocks': blocks, 'outline_mul_all168_case_pairs': outline_cases,
              'scope': 'Exact same-binary complete32-process diagnostic discovery only. Four old/new inputs remain seen. Newpublic88cdf proof/actualMainFull/gate/timing/confirmation NOT_RUN; no formal score inherited.',
              'native_ELF_rehash_limit': 'Native object/binary bytes not exported. Raw disassemblies and C rehashed; actual linkedSubmission object identity bound to unchanged original_build_before remote receipt.'}
    save('actual406073-review.json', report)
    print(json.dumps({'all_originals': len(bindings), 'raw_bytes': total_bytes, 'static_closures': len(closures), 'dynamic_closures': 0,
                      'outline_typed_no_frame_three_tail_branches': True, 'retained_C_equals_control': retained_equals_control,
                      'outline_blocks': [{'seed': b['seed'], 'block': b['block'], 'mul': b['ratios']['mul'], 'whole': b['ratios']['whole']} for b in blocks if b['variant'] == 'outline']}))


if __name__ == '__main__':
    main()
