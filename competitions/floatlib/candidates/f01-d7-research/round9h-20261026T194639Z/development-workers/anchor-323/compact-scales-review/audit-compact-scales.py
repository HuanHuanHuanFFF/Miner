"""Rehash known terminal artifacts and audit selected diagnostic C/ASM only."""
from datetime import datetime, timezone
import hashlib
import json
from pathlib import Path
import re
import sys

sys.dont_write_bytecode = True
HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p / 'competitions/floatlib/scripts/estimate_champion_time.py').is_file())
BASE = ROOT / 'competitions/floatlib/candidates'
RUN = BASE / 'f01-mul-log2-proof1/ci-runs/40410895344'
SUITE = RUN / 'download-9af980463e0648dabd2d03b5c409c96e/diagnostics/f01-d7-public-suite/public-suite'
DIAG = SUITE / 'diagnostics/f01-r19-dev-compact-scales1'
OLD_SUITE = BASE / 'f01-mul-log2-proof1/ci-runs/40395429076/download-01d3ee43e7ff4ae088ca57488a71a0b2/diagnostics/f01-d7-public-suite/public-suite'
OLD = OLD_SUITE / 'diagnostics/f01-r19-dev-b2-index1'
SOURCE = BASE / 'f01-r19-dev-compact-scales1/Kernel.lean'
SOURCE_SHA = '9c4e9505702231fdb93f47f8d767ba0b2b0c2ad7ec48d8894b5a53ba87657645'
BENCH = BASE / 'f01-d7-research/round8h-20261024T190259Z/astra-official-source/lean/bench/BenchSuite.lean'
read = lambda p: json.loads(Path(p).read_bytes())
sha = lambda p: hashlib.sha256(Path(p).read_bytes()).hexdigest()
rel = lambda p: Path(p).resolve().relative_to(ROOT).as_posix()
encode = lambda x: (json.dumps(x, ensure_ascii=False, indent=2) + '\n').encode()


def require(ok, text):
    if not ok:
        raise ValueError(text)


def cfun(text, name):
    match = re.search(r'^(?:LEAN_EXPORT|static) [^;\n]*?\b' + re.escape(name) + r'\([^;\n]*\)\s*\{', text, re.M)
    require(match is not None, 'C function absent: ' + name)
    start, i, depth = match.start(), text.find('{', match.start()), 0
    while i < len(text):
        if text[i] in ('"', "'"):
            quote = text[i]; i += 1
            while i < len(text) and text[i] != quote:
                i += 2 if text[i] == '\\' else 1
        elif text[i] == '{': depth += 1
        elif text[i] == '}':
            depth -= 1
            if depth == 0:
                return {'start_line': text[:start].count('\n')+1, 'end_line': text[:i+1].count('\n')+1, 'text': text[start:i+1]}
        i += 1
    raise ValueError('Unclosed C function')


def asmfun(text, name):
    match = re.search(r'^0+ <' + re.escape(name) + r'>:\n', text, re.M)
    require(match is not None, 'ASM symbol absent: ' + name)
    end = re.search(r'^Disassembly of section|^[0-9a-f]+ <', text[match.end():], re.M)
    stop = match.end() + end.start() if end else len(text)
    return {'start_line': text[:match.start()].count('\n')+1, 'text': text[match.start():stop]}


def lean_runtime(text, name):
    marker = '@[inline] def ' + name + ' (x y : Binary32) : Binary32 :=\n'
    start = text.find(marker)
    require(start >= 0, 'Lean scalar absent: ' + name)
    stop = text.find('\ntheorem ' + name + '_spec', start)
    require(stop > start, 'Scalar theorem boundary absent')
    return text[start:stop]


def main():
    inputs = set()
    original_index = read(RUN / 'original-artifact-hashes.json')
    require(len(original_index['files']) == 88 and original_index['artifact']['workflow_run']['id'] == 40410895344, 'Wrong terminal artifact set')
    download = RUN / original_index['directory']
    for name, expected in original_index['files'].items():
        path = download / name
        require(path.stat().st_size == expected['bytes'] and sha(path) == expected['sha256'], 'Original artifact changed: ' + name)
        inputs.add(path)
    inputs.add(RUN / 'original-artifact-hashes.json')
    source, intake = SOURCE.read_bytes(), (SUITE / 'inputs/f01-r19-dev-compact-scales1/Kernel.lean').read_bytes()
    manifest_path = SOURCE.parent / 'manifest.json'; manifest = read(manifest_path)
    require(source == intake and sha(SOURCE) == manifest['candidate_sha256'] == SOURCE_SHA and len(source) == 229293, 'Source/manifest binding differs')
    inputs.update((SOURCE, manifest_path))
    c_index, asm_index = read(DIAG / 'candidate-c-index.json'), read(DIAG / 'native-assembly-index.json')
    for row in c_index:
        require(row['kernel_sha256'] == SOURCE_SHA and sha(DIAG / row['file']) == row['sha256'], 'Generated C binding differs')
    for row in asm_index:
        require(sha(DIAG / row['file']) == row['sha256'], 'ASM/trace bytes differ')
        if row['kind'] == 'actual-built-object-disassembly':
            require(row['kernel_sha256'] == SOURCE_SHA and row['exit_code'] == 0 and 'not the cleaned-up timed gate object' in row['scope'], 'Wrong disassembly scope')
    helper = read(DIAG / 'helper-audit.json')
    raw = (DIAG / 'helper-axioms.raw').read_text('utf-8').splitlines()
    require(helper['kernel_sha256'] == SOURCE_SHA and helper['accepted'] and helper['kernel_replay'] and helper['expected_count'] == len(helper['reports']) == 10, 'Helper audit incomplete')
    require(all(set(v) <= {'propext', 'Classical.choice', 'Quot.sound'} for v in helper['reports'].values()), 'Unexpected axioms')
    require([x.strip() for x in raw if x.strip()][-2:] == ['true', '512'], 'Actual evaluation output differs')
    sub_c_path, main_c_path = DIAG / 'candidate-generated-0.c', DIAG / 'candidate-generated-1.c'
    sub_c, main_c = sub_c_path.read_text('utf-8'), main_c_path.read_text('utf-8')
    selected = {}
    snippets = []
    for operation, suffix, asm_file in [('add', '0', 'native-loop-10.asm.txt'), ('mul', '3', 'native-loop-12.asm.txt')]:
        symbol = 'lp_competition_main___lam__' + suffix
        c = cfun(main_c, symbol); asm = asmfun((DIAG / asm_file).read_text('utf-8'), symbol)
        require(c['text'].count('= lp_competition_R19CompactScales_valid;') == 1, 'Wrong per-scalar flag count')
        require(c['text'].count('lean_float_array_fget(') == 2 and c['text'].count('lean_float_to_float32(') == 2, 'Compact table load/narrow absent')
        require(c['text'].count('lean_array_fget_borrowed(') == 2, 'Original boxed fallback absent')
        forbidden = ('lean_float_array_data(', 'lean_float_array_mk(', 'R19CompactScales_checkOne(', '_init_', 'mapMUnsafe_map___at___00R19CompactScales_packed')
        require(not any(x in c['text'] for x in forbidden), 'Hot materialization/rebuild/check loop found')
        require(len(re.findall(r'\bmovsd\s+.*QWORD PTR \[', asm['text'])) == 2 and asm['text'].count('cvtsd2ss') == 2, 'Actual selected ASM does not implement compact loads')
        require(len(re.findall(r'\bcmp\s+BYTE PTR \[[^\]]+\],0x0', asm['text'])) == 1, 'Actual selected ASM flag check differs')
        require('ucomiss' in asm['text'], 'Non-NaN result guard missing')
        selected[operation] = {'symbol': symbol, 'C': {'path': rel(main_c_path), 'start_line': c['start_line'], 'end_line': c['end_line']},
            'ASM': {'path': rel(DIAG / asm_file), 'symbol_start_line': asm['start_line']},
            'valid_static_load_and_test_count': 1, 'max_compact_double_loads': 2, 'max_narrow_casts': 2,
            'boxed_fallback_static_hits': 2, 'hot_data_materialization': False, 'hot_rebuild_or_validation_loop': False,
            'nonNaN_result_guard_present': True}
        snippets.extend([f'// {rel(main_c_path)}:{c["start_line"]}\n' + c['text'], f'; {rel(DIAG / asm_file)}:{asm["start_line"]}\n' + asm['text']])
    require('cmp    ecx,0x80' in asmfun((DIAG / 'native-loop-12.asm.txt').read_text(), 'lp_competition_main___lam__3')['text'], 'MUL LowScale first guard missing')
    require('lp_competition_main___lam__0___boxed' in main_c and 'lp_competition_main___lam__3___boxed' in main_c and 'lp_competition_Bench_Suite_run(v___f_1364_, v___f_1365_' in main_c, 'MainFull closure selector absent')
    require(re.search(r'^static const lean_closure_object lp_competition_main___closed__1_value.*lp_competition_main___lam__0___boxed', main_c, re.M) and
            re.search(r'^static const lean_closure_object lp_competition_main___closed__5_value.*lp_competition_main___lam__3___boxed', main_c, re.M), 'Selected closure mapping changed')
    require('v___f_1364_ = ((lean_object*)(lp_competition_main___closed__1));' in main_c and 'v___f_1365_ = ((lean_object*)(lp_competition_main___closed__5));' in main_c and '"BENCH_PLAN"' in main_c, 'Suite ADD/MUL argument mapping changed')
    require('lean_float_array_data' not in main_c, 'MainFull references materializing data API')
    data_helpers = re.findall(r'^LEAN_EXPORT [^\n;]+? (lp_competition___private_Submission_0__FloatArray_(?:size|get)_match\w+)\([^;\n]*\)\{', sub_c, re.M)
    require(len(data_helpers) == 4 and all(len(re.findall(r'\b'+re.escape(n)+r'\b', sub_c)) == 2 for n in data_helpers), 'Proof splitter usage changed')
    init = cfun(sub_c, 'initialize_competition_Submission')
    init_main = cfun(main_c, 'initialize_competition_MainFull')
    require('if (_G_initialized)' in init['text'] and 'R19CompactScales_packed = _init_' in init['text'] and 'R19CompactScales_valid = _init_' in init['text'], 'Global once initialization absent')
    require('initialize_competition_Submission(builtin)' in init_main['text'] and main_c.index('res = initialize_competition_MainFull(1') < main_c.index('res = lean_run_main('), 'Startup ordering differs')
    snippets.extend([f'// {rel(sub_c_path)}:{init["start_line"]}\n'+init['text'], f'// {rel(main_c_path)}:{init_main["start_line"]}\n'+init_main['text']])
    require('lean_float_array_mk(' in sub_c and 'lean_obj_once(' in sub_c and 'lean_uint8_once(' in sub_c, 'Expected cold construction/once cells absent')
    map_name = 'lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00R19CompactScales_packed_spec__0'
    valid_name = 'lp_competition___private_Init_Data_Array_Basic_0__Array_anyMUnsafe_any___at___00R19CompactScales_valid_spec__0'
    for symbol in (map_name, valid_name):
        body = cfun(sub_c, symbol)
        snippets.append(f'// {rel(sub_c_path)}:{body["start_line"]}\n'+body['text'])
    # Exact B2 scalar bodies are preserved in the old index-only BMM control.
    old_source = OLD_SUITE / 'inputs/f01-r19-dev-b2-index1/Kernel.lean'
    b2_source = BASE / 'f01-r15-dev-packed-b2-1/Kernel.lean'
    require(sha(b2_source) == '622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58', 'Retained B2 changed')
    old_index = read(OLD / 'candidate-c-index.json')
    require(sha(old_source) == old_index[0]['kernel_sha256'] == '9f7f96d71c153681c6a2500fd229e0627cd2ea38a3ad375afdeee25a1657eee1', 'Control source differs')
    for name in ('add', 'nativeMul', 'mul'):
        require(lean_runtime(old_source.read_text('utf-8'), name) == lean_runtime(b2_source.read_text('utf-8'), name), 'Control scalar body differs from B2: ' + name)
    for row in old_index:
        require(sha(OLD / row['file']) == row['sha256'], 'Control C changed'); inputs.add(OLD / row['file'])
    old_asm_index = read(OLD / 'native-assembly-index.json')
    old_trace = next(x for x in old_asm_index if x['kind'] == 'trace' and x['source'].endswith('Submission.c.o.export.trace'))
    require(sha(OLD / old_trace['file']) == old_trace['sha256'], 'Control build trace changed')
    for trace_path in (OLD / old_trace['file'], DIAG / 'build-trace-0.txt', DIAG / 'build-trace-9.txt'):
        trace_text = trace_path.read_text('utf-8')
        require('-O3 -DNDEBUG -DLEAN_EXPORTING' in trace_text and '-ffp-contract=off' in trace_text and 'Lean 4.34.0, commit 293d5d0c' in trace_text, 'Different code generation boundary')
        inputs.add(trace_path)
    for filename, symbol in [('native-loop-5.asm.txt', 'lp_competition_Submission_add'), ('native-loop-7.asm.txt', 'lp_competition_Submission_nativeMul')]:
        row = next(x for x in old_asm_index if x['file'] == filename)
        require(sha(OLD / filename) == row['sha256'] and row['kind'] == 'actual-built-object-disassembly', 'Control ASM binding differs')
        asm = asmfun((OLD / filename).read_text('utf-8'), symbol)
        require('cvtsd2ss' not in asm['text'] and len(re.findall(r'mulss\s+.*DWORD PTR \[', asm['text'])) == 2, 'Original boxed cost pattern differs')
        snippets.append(f'; {rel(OLD / filename)}:{asm["start_line"]}\n'+asm['text']); inputs.add(OLD / filename)
    old_main = (OLD / 'candidate-generated-1.c').read_text('utf-8')
    for suffix in ('0', '3'):
        c = cfun(old_main, 'lp_competition_main___lam__'+suffix)
        require('R19CompactScales' not in c['text'] and c['text'].count('lean_array_fget_borrowed(') == 2, 'Old MainFull scalar comparison differs')
    inputs.update((old_source, b2_source, OLD / 'candidate-c-index.json', OLD / 'native-assembly-index.json', BENCH))
    bench_text = BENCH.read_text('utf-8')
    require('let t0 ← IO.monoNanosNow' in bench_text and 'let elapsed := (← IO.monoNanosNow) - t0' in bench_text, 'Cached bench timer boundary differs')
    object_rows = [x for x in asm_index if x.get('symbol') in ('lp_competition_main___lam__0', 'lp_competition_main___lam__3')]
    result = {'status': 'PASS_STATIC_COST_PRECONDITIONS_WITH_LIMITS', 'verified_at_utc': datetime.now(timezone.utc).isoformat(),
        'source_sha256': SOURCE_SHA, 'source_bytes': len(source), 'source_manifest': rel(manifest_path),
        'run': 40410895344, 'run_head': original_index['artifact']['workflow_run']['head_sha'], 'original_files_rehashed': 88,
        'build_flags': 'Lean4.34.0/293d5d0c; clang -O3 -DNDEBUG -DLEAN_EXPORTING -ffp-contract=off, unchanged pinned build',
        'helper_roots_allowed': 10, 'helper_actual_final_output': ['true', '512'], 'full_gate_and_timing': 'NOT_RUN',
        'evidence_status': {'selected_C_and_actual_diagnostic_ASM': 'VERIFIED', 'helper_true_and512': 'VERIFIED_DIAGNOSTIC_EVALUATION',
            'module_startup_order': 'VERIFIED_GENERATED_C', 'future_timed_object_identity': 'UNKNOWN_UNSEEN',
            'native_initializer_iteration_count': 'UNKNOWN', 'cost_trade_and_first_D_recommendation': 'INFERRED_DECISION'},
        'selected_MainFull': selected, 'selected_suite_chain': 'C main initialization -> _lean_main BENCH_PLAN present -> Bench.Suite.run(ADD closure lambda0, MUL closure lambda3)',
        'proof_materialization_helpers': {'count': 4, 'names': data_helpers, 'references_each_in_Submission_C': 2, 'scope': 'Prototype+definition only; not referenced by selected MainFull/scalar chains. Do not claim entire C has no data materialization.'},
        'valid_dynamic_checks': {'add_pair_operation': 1, 'mul_native_pair_operation': 1, 'mul_LowScale_pair_operation': 0, 'per_operand_extra_check': 0},
        'table_hit_mechanism': 'Indexed contiguous8-byte FloatArray storage load -> numerical cvtsd2ss -> unchanged float32 mantissa multiply; not vectorized adjacent-operand loads.',
        'fallbacks': {'valid_false_boxed_arm': 'PRESENT_REACHABLE_IN_CODE', 'per_input_fastOK_false_ofBits': 'PRESENT', 'result_NaN_scalar_repair': 'PRESENT', 'MUL_LowScale_before_valid': 'PRESENT'},
        'initialization': {'where': 'initialize_competition_Submission called from MainFull startup before lean_run_main/Bench.Suite.run',
            'once_scope': 'Per process/module initialization guard and once cells, not once for the entire gate/CI',
            'C_map_trip_count': 512, 'C_validation_trip_count_if_true': 512,
            'native_exact_validation_check_count': 'UNKNOWN_INITIALIZER_ASM_NOT_CAPTURED',
            'helper_true_and512_prove_native_trip_count': False,
            'hot_initialization_or_validation_loop': False,
            'inside_scalar_benchmark_clock': 'NO_BY_STARTUP_ORDER_AND_CACHED_BENCH_SOURCE',
            'future_timed_clock_scope': 'INFERRED_FROM_DIAGNOSTIC_STARTUP_AND_CACHED_OFFICIAL_SOURCE_NOT_MEASURED',
            'startup_wall_time_allocation_and_both_tables_live': 'RETAINED_COST_NOT_FREE',
            'construction_boundary': 'Original boxed table retained; map512 widening and intermediate boxed Float64 array, lean_float_array_mk packing; separate all-check of source table.'},
        'comparison': {'run': 40395429076, 'candidate': 'f01-r19-dev-b2-index1', 'source_sha256': sha(old_source),
            'add_nativeMul_mul_Lean_bodies_equal_exact_B2': True,
            'C_object_level': 'Selected MainFull control C versus compact selected MainFull C',
            'ASM_object_level': 'Control Submission.add/nativeMul versus compact selected MainFull lambda0/lambda3; all diagnostic statement build objects, not cleaned timed gate objects',
            'trade': 'Each compact hit removes one dependent boxed-entry hop and adds double-to-float narrowing; each native scalar op adds global flag address-load/byte-test/branch. PIC flag reads can offset removed memory-reference counts. No fewer-total-load or speed claim.',
            'ADD_both_fastOK_illustration': {'compact_MainFull': 'Flag address0xc/byte0x30; table address/global/payload0x6c/0x73/0x7b and0xbf/0xc6/0xce; two narrowing instructions0x81/0xd4',
                'old_Submission_add': 'Table address/global/entry/payload0x47/0x4e/0x56/0x5b and0xa7/0xae/0xb6/0xbb; no narrowing',
                'scope': 'Diagnostic chosen straight paths have8 listed memory reads each; this is not a cycle model or same-symbol timed comparison.'}},
        'object_binding': {'rows': object_rows, 'raw_object_bytes_retained_and_independently_rehashed': False,
            'scope': 'Object SHA is attested by original assembly index; retained C/ASM/trace bytes independently rehashed. Not the timed object.'},
        'recommendation': {'decision': 'WORTH_ONE_FIRST_COMPLETE_DISCOVERY_D', 'basis': 'Actual selected path meets representation/no-hot-rebuild prerequisites; full D should decide dependent-load versus narrow+flag trade.',
            'expected_speedup': 'UNKNOWN', 'do_not_prebook_confirmations': True,
            'required': 'Exact9c4e source, original full25 gate, B2 and existing41 controls, no observers, original .97/positivep05 policy; failed firstD is retained, no seed reset.'},
        'future_compact_full_D_or_holdout_read': False,
        'inputs': [{'path': rel(p), 'bytes': p.stat().st_size, 'sha256': sha(p)} for p in sorted(inputs, key=rel)]}
    (HERE / 'selected-excerpts.txt').write_bytes(('\n\n'.join(snippets)+'\n').encode())
    (HERE / 'cost-review.json').write_bytes(encode(result))
    print(json.dumps({'status': result['status'], 'original_files_rehashed': 88, 'helper_actual_final_output': result['helper_actual_final_output'],
        'valid_dynamic_checks': result['valid_dynamic_checks'], 'initialization_native_count': result['initialization']['native_exact_validation_check_count'],
        'source_sha256': SOURCE_SHA, 'decision': result['recommendation']['decision'], 'input_count': len(inputs)}))


if __name__ == '__main__':
    main()
