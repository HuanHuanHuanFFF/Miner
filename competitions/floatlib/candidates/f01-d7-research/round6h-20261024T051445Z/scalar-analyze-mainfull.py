"""Derive exact current6c scalar call-chain evidence from original40067286343 capture."""
from pathlib import Path
import hashlib
import json
import re

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[4]
PUBLIC = ROOT / 'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40067286343/download-5936990717ed4c0996f1c31b985d1aa3/diagnostics/f01-d7-public-suite/public-suite'
CAPTURE = PUBLIC / 'codegen/f01-d11-bmm-combined-classifier/capture-ad2a97ee7ace4c67983e4c060817926c'


def sha(raw):
    return hashlib.sha256(raw).hexdigest()


def function(raw, symbol):
    text = raw.decode('utf-8')
    pattern = re.compile(r'^LEAN_EXPORT [^;\n]*\b' + re.escape(symbol) + r'\([^;\n]*\)\s*\{', re.M)
    match = pattern.search(text)
    assert match, symbol
    start = match.start()
    braces = 1
    end = match.end()
    while braces:
        braces += (text[end] == '{') - (text[end] == '}')
        end += 1
    body = text[start:end]
    first_line = text[:start].count('\n') + 1
    calls = sorted(set(re.findall(r'\b((?:lean_|lp_)[A-Za-z0-9_]+)\(', body)))
    return {'symbol': symbol, 'start_line': first_line, 'end_line': first_line+body.count('\n'),
            'sha256': sha(body.encode()), 'calls_in_source_not_dynamic_counts': calls}


def main():
    record_raw = (CAPTURE / 'capture-record.json').read_bytes()
    record = json.loads(record_raw)
    summary = json.loads((PUBLIC / 'summary.json').read_bytes())
    assert record['state'] == record['snapshot']['state'] == 'CAPTURED'
    assert record['kernel_sha256'] == '6c2d394dd34e8854d0d44d5d6605c194ecb27c152a1768d236481fc03fa4277d'
    assert record['private_objects_removed'] and record['private_directory_removed']
    for item in record['snapshot']['files']:
        raw = (CAPTURE / item['artifact']).read_bytes()
        assert sha(raw) == item['sha256']
    compiled = (CAPTURE / 'compiled-Submission.lean').read_bytes()
    assert sha(compiled) == record['kernel_sha256']
    bodies = {}
    module_file = {'MainFull': 'file-0-MainFull.c', 'Submission': 'file-3-Submission.c', 'BenchSuite': 'file-6-BenchSuite.c'}
    wanted = {'MainFull': ['lp_competition_main___lam__0', 'lp_competition_main___lam__0___boxed',
                           'lp_competition_main___lam__3', 'lp_competition_main___lam__3___boxed', '_lean_main'],
              'BenchSuite': ['lp_competition_Bench_Suite_run', 'lp_competition_Bench_Suite_measure', 'lp_competition_Bench_Suite_runScalar',
                    'lp_competition_Bench_Suite_runScalar___lam__1',
                    'lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Bench_Suite_runScalar_spec__0'],
              'Submission': ['lp_competition_Submission_TunedAdd_add', 'lp_competition_Submission_FastMul_mul']}
    for module, symbols in wanted.items():
        raw = (CAPTURE / module_file[module]).read_bytes()
        bodies[module] = [function(raw, name) for name in symbols]
    captured = {s['symbol']: {'module': o['module'], 'object_sha256': o['object_sha256'],
        'size_bytes': s['size_bytes'], 'artifact': s['assembly']['artifact'], 'sha256': s['assembly']['sha256']}
        for o in record['disassembly']['objects'] for s in o['symbols']}
    required_asm = wanted['MainFull'] + wanted['BenchSuite']
    for symbol in required_asm:
        assert symbol in captured, symbol
        row = captured[symbol]
        assert sha((CAPTURE / row['artifact']).read_bytes()) == row['sha256']
    verdict = (PUBLIC / 'f01-d11-bmm-combined-classifier-verdict.json').read_bytes()
    v = json.loads(verdict)
    assert v['passed'] and v['stage'] == 'score' and len(v['rounds']) == 25
    report = {'run': 40067286343, 'source_commit': summary['source_commit'],
        'kernel_sha256': record['kernel_sha256'], 'original_full_gate': 'PASS25', 'verdict_sha256': sha(verdict),
        'capture_record_sha256': sha(record_raw), 'capture_directory': CAPTURE.relative_to(ROOT).as_posix(),
        'all_c_trace_hashes_checked': True, 'exact_compiled_source_sha256_checked': True,
        'source_binding': record['snapshot'].get('mainfull_identity'),
        'snapshot_started_utc': record['snapshot']['started_at_utc'],
        'snapshot_finished_utc': record['snapshot']['finished_at_utc'],
        'original_stage_log': record['original_stage_log'],
        'time_boundary': 'UTC snapshot readings are local observer times; original emission timezone UNKNOWN. Arrival is not emission. No stronger before-axioms timestamp claim.',
        'final_link_identity': record['snapshot']['final_link_identity'],
        'linked_provenance': [x for x in record['snapshot']['files'] if x.get('kind') == 'link-provenance'],
        'objects': [{'module': o['module'], 'sha256': o['object_sha256'],
                    'captured_symbols': len(o['symbols']), 'omitted_symbols': o['omitted_symbols']} for o in record['disassembly']['objects']],
        'actual_c_functions': bodies, 'critical_caller_assembly': {s: captured[s] for s in required_asm},
        'critical_caller_assembly_complete': True,
        'dispatch': 'BENCH_PLAN present: _lean_main uses closed1(add main lam0 boxed) and closed5(mul main lam3 boxed), passed to Bench.Suite.run. Legacy Bench.runFull uses lam1 for mul.',
        'measured_chain': 'Suite.run selects runScalar; setup makes input pairs outside measure. measure invokes runScalar lam1 which runs Array forInUnsafe runScalar_spec__0; each element calls lean_apply_2, reaches MainFull boxed lambda then unboxed arithmetic body, then checksum XOR/multiply.',
        'immutable_costs': ['Official Array pair loads/iteration, closure apply, refcount tests, checksum update and measurement shell',
                            'Entrypoint UInt32 boxed adapter ABI; captured machine result is tagged immediate lea*2+1, not per-element heap allocation'],
        'ordinary_add': 'Actual225B lam0 has existing numeric window tests, table loads, integer-to-float/multiply or of_bits fallback, addss, self ucomiss, and to_bits tail. No duplicated same-operand conversion was observed.',
        'ordinary_mul': 'Actual870B lam3 includes retained LowScale. Normal branch has two of_bits foreign relocations (0x25/0x32), one float spill/reload, mulss/ucomiss and to_bits tail relocation0x4d. No duplicated same-operand conversion was observed.',
        'candidate_cost_boundary': 'Runtime bitcast calls and current numeric decoder have real costs but no legally editable duplicate was identified in the caller. Source-level decoder alternatives are cost tradeoffs, not elimination of an observed duplicate; numeric-band retries remain parked.',
        'cold_route_evidence': 'NaN add body tail reloc0xdd reaches TunedAdd.add; NaN mul body tail reaches FastMul.mul. Captured Submission C retains special checks/software backend fallback. Cold helper asm was not selected; no cold cycle/gain estimate is claimed.',
        'selected_mechanism': 'Conditional existing4a30 rawChoose selection after current result NaN guard, certified None fallback, exact old proof reuse; remove TunedAdd namespace for capacity and use official add None fallback. Keep all ordinary expressions and LowScale/tensor tail.',
        'runtime_candidate': 'f01-d12-scalar-cold-nan-select', 'candidate_sha256': 'b15dd4116f79ccdbb1ef6ffd203f33bfe70abebcf9eb4b3146e21a3a20461325',
        'candidate_acceptance': 'NOT_RUN', 'candidate_gain': 'UNKNOWN', 'observer_performance_role': 'DISCOVERY_ONLY'}
    (HERE / 'scalar-mainfull-analysis.json').write_text(json.dumps(report, ensure_ascii=False, indent=2)+'\n', encoding='utf-8', newline='\n')
    print(json.dumps({'source_commit': report['source_commit'], 'record_sha256': report['capture_record_sha256'],
                      'critical_caller_assembly_complete': True, 'function_ranges': {m: [{k: r[k] for k in ('symbol','start_line','end_line')} for r in rows] for m, rows in bodies.items()}}, indent=2))


if __name__ == '__main__':
    main()
