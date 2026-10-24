"""Only completed discovery plans901/902/904; no new benchmark or future seed.

Reuses the existing generator AST, checks both original generator Git blobs at
the exact official commit, and exactly regenerates each saved public plan.
Array guard counts are deterministic source reconstructions, not runtime traces.
Official verdicts retain cell timings only: individual case weights stay UNKNOWN.
"""
from datetime import datetime, timezone
from hashlib import sha1, sha256
from pathlib import Path
import ast
import json
import time

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[4]
RESEARCH = ROOT / 'competitions/floatlib/research/astra-collab-20261023-r7'
EVIDENCE = ROOT / 'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs'
RUNS = [
    (901, 40013486988, 'download-521db6faa63949a784675afbc1259395'),
    (902, 40014284237, 'download-c940aee00b7a4cba8cc126b8221c5140'),
    (904, 40018666234, 'download-18484078502a49d8aa971e46a005c9e7'),
]
OFFICIAL = '4b7e83841cc0c32c6529f533923c73d33b5ecf97'
A066 = 'a06608bdc419d4647af301bfdd617d52e4796c404661a28672a022eef4a10b78'
UNDERFLOW = '6a69d6edd8afe6240fc6970c5eb8957a26f50595158c2020715f769dd094ea81'
THRESHOLD = 0x16000000

def label(p):
    return p.relative_to(ROOT).as_posix()

def identity(p):
    raw = p.read_bytes()
    return {'path': label(p), 'bytes': len(raw), 'sha256': sha256(raw).hexdigest()}

def blob_id(raw):
    return sha1(b'blob ' + str(len(raw)).encode() + b'\0' + raw).hexdigest()

def load_generator(path):
    tree = ast.parse(path.read_text(encoding='utf-8'))
    wanted = {'word', 'ctz', 'element'}
    constants = {'M64', 'M32'}
    nodes = [n for n in tree.body if isinstance(n, ast.FunctionDef) and n.name in wanted
             or isinstance(n, ast.Assign) and any(isinstance(t, ast.Name) and t.id in constants for t in n.targets)]
    assert {n.name for n in nodes if isinstance(n, ast.FunctionDef)} == wanted
    env = {}
    exec(compile(ast.Module(body=nodes, type_ignores=[]), str(path), 'exec'), env)
    return env

def load_plan_generator(path):
    raw = path.read_text(encoding='utf-8')
    tree = ast.parse(raw)
    allowed = (ast.Import, ast.ImportFrom, ast.Assign, ast.AnnAssign, ast.ClassDef,
               ast.FunctionDef, ast.Expr)
    assert all(isinstance(n, allowed) for n in tree.body)
    assert all(isinstance(n.value, ast.Constant) and isinstance(n.value.value, str)
               for n in tree.body if isinstance(n, ast.Expr))
    allowed_modules = {'__future__', 'hashlib', 'json', 'math', 'os', 'random', 'pathlib'}
    for n in tree.body:
        if isinstance(n, ast.Import):
            assert all(a.name in allowed_modules for a in n.names)
        elif isinstance(n, ast.ImportFrom):
            assert n.module in allowed_modules
    env = {'__name__': 'verified_plan_source_only', '__file__': str(path)}
    exec(compile(tree, str(path), 'exec'), env)
    return env

def scan(c, role, length, row_width, element, deadline):
    """Evaluate independent Array.all, stopping at its first failing word."""
    digest = sha256()
    max_exp = None
    for i in range(length):
        if i % 8192 == 0:
            assert time.monotonic() < deadline, 'Bounded exposure analysis timed out'
        w = element(c, i, role, row_width)
        assert 0 <= w < 2**32
        digest.update(w.to_bytes(4, 'little'))
        e = (w >> 23) & 255
        max_exp = e if max_exp is None else max(max_exp, e)
        if (w & 0x7fffffff) >= THRESHOLD:
            return {'all_small': False, 'words_read_including_failure': i + 1,
                    'passing_words_before_failure': i, 'first_failure_index': i,
                    'first_failure_word': f'{w:08x}', 'first_failure_exponent': e,
                    'scanned_prefix_le_sha256': digest.hexdigest(),
                    'max_exponent_in_scanned_prefix': max_exp,
                    'unread_suffix_words': length - i - 1}
    return {'all_small': True, 'words_read_including_failure': length,
            'passing_words_before_failure': None, 'first_failure_index': None,
            'first_failure_word': None, 'first_failure_exponent': None,
            'scanned_prefix_le_sha256': digest.hexdigest(),
            'max_exponent_in_scanned_prefix': max_exp, 'unread_suffix_words': 0}

def main():
    started = time.monotonic()
    deadline = started + 600
    source_receipt_path = HERE / 'review-output-underflow-source-receipt.json'
    receipt = json.loads(source_receipt_path.read_text(encoding='utf-8'))
    assert receipt['official_commit'] == OFFICIAL and receipt['truncated'] is False
    entries = {x['path']: x for x in receipt['entries']}
    lean = RESEARCH / 'upstream/BenchSuite.lean'
    planner = EVIDENCE / '40005234741/download-9f2affecc48e4d2993e5b715cba86bf6/diagnostics/f01-d7-public-suite/retained-stage-profile/profile-retained-generator.py'
    for official_path, local in [('lean/bench/BenchSuite.lean', lean), ('benchmark_suite.py', planner)]:
        raw = local.read_bytes()
        assert len(raw) == entries[official_path]['size']
        assert blob_id(raw) == entries[official_path]['sha'], 'Local source differs from exact official Git blob'
    transcription = RESEARCH / 'public-nonfinite-opportunity.py'
    generator = load_generator(transcription)
    plan_generator = load_plan_generator(planner)
    kernel = ROOT / 'competitions/floatlib/candidates/f01-d11-bmm-underflow-zero-proof2/Kernel.lean'
    assert sha256(kernel.read_bytes()).hexdigest() == UNDERFLOW
    assert b'A.toArray.all UnderflowZero.small && B.toArray.all UnderflowZero.small' in kernel.read_bytes()
    sources = [identity(p) for p in (source_receipt_path, lean, planner, transcription, kernel)]
    results = []
    for seed, run, download in RUNS:
        base = EVIDENCE / str(run) / download / 'diagnostics/f01-d7-public-suite/public-suite'
        paths = {name: base / name for name in ['public-drawn-plan.json', 'public-v2.json',
                 'provenance.json', 'public-cell-work.json', 'f01-d10-bmm-direct-rows-verdict.json',
                 'inputs/f01-d10-bmm-direct-rows/Kernel.lean']}
        for p in paths.values():
            sources.append(identity(p))
        plan = json.loads(paths['public-drawn-plan.json'].read_text())
        suite = json.loads(paths['public-v2.json'].read_text())
        provenance = json.loads(paths['provenance.json'].read_text())
        verdict = json.loads(paths['f01-d10-bmm-direct-rows-verdict.json'].read_text())
        assert provenance['seed'] == verdict['seed'] == seed
        assert provenance['official_commit'] == OFFICIAL
        assert provenance['official_generator_sha256'] == sha256(planner.read_bytes()).hexdigest()
        assert sha256(paths['inputs/f01-d10-bmm-direct-rows/Kernel.lean'].read_bytes()).hexdigest() == A066
        assert verdict['passed'] and verdict['stage'] == 'score' and verdict['mode'] == 'gate'
        assert len(verdict['rounds']) == 25
        assert verdict['verifier_fingerprint'] == verdict['verifier_fingerprint_end']
        assert plan_generator['make_plan'](suite, seed, 500000) == plan, 'Saved plan does not regenerate exactly'
        timed = [c for c in plan['cases'] if c['timed']]
        work = {cell: sum(c['work'] for c in timed if c['name'].rsplit(':', 1)[0] == cell)
                for cell in verdict['classes']}
        assert json.loads(paths['public-cell-work.json'].read_text()) == work
        cell_ns = {cell: int(round(row['submission_ns'] * work[cell]))
                   for cell, row in verdict['classes'].items()}
        for cell, row in verdict['classes'].items():
            assert abs(cell_ns[cell] - row['submission_ns'] * work[cell]) < 0.01
        total_ns = sum(cell_ns.values())
        bmm_ns = sum(ns for cell, ns in cell_ns.items() if cell.startswith('bmm:'))
        bmm_work = sum(c['work'] for c in timed if c['kernel'] == 'bmm')
        rows = []
        for c in plan['cases']:
            if c['kernel'] != 'bmm':
                continue
            batch, m, n, p = [c[k] for k in ('batch', 'm', 'n', 'p')]
            a_len, b_len = batch * m * n, batch * n * p
            a = scan(c, 0, a_len, n, generator['element'], deadline)
            # Standalone B evaluation is diagnostic only when actual A would reject.
            b = scan(c, 1, b_len, p, generator['element'], deadline)
            hit = a['all_small'] and b['all_small']
            b_runtime_reads = b['words_read_including_failure'] if a['all_small'] else 0
            cell = c['name'].rsplit(':', 1)[0] if c['timed'] else None
            rows.append({
                'name': c['name'], 'timed': c['timed'], 'input_seed': c['seed'],
                'shape_batch_m_n_p': [batch, m, n, p], 'generator_case': c,
                'A_total_words': a_len, 'B_total_words': b_len,
                'A_standalone_scan': a, 'B_standalone_scan': b,
                'whole_matrix_hit_reconstructed': hit,
                'runtime_scan_A_words_reconstructed': a['words_read_including_failure'],
                'runtime_scan_B_words_reconstructed': b_runtime_reads,
                'runtime_B_skipped_reconstructed': not a['all_small'],
                'runtime_total_scan_words_reconstructed': a['words_read_including_failure'] + b_runtime_reads,
                'mac_work': c['work'], 'output_words': batch * m * p,
                'fraction_of_timed_BMM_MAC_work': c['work'] / bmm_work if c['timed'] else None,
                'a066_case_best_ns': 'UNKNOWN_NOT_RETAINED_IN_OFFICIAL_VERDICT',
                'a066_case_time_fraction_of_BMM': 'UNKNOWN',
                'measured_containing_cell': cell,
                'containing_cell_a066_best_ns_sum': cell_ns[cell] if cell else None,
                'containing_cell_fraction_of_BMM_time': cell_ns[cell] / bmm_ns if cell else None,
                'actual_Lean_guard_trace': 'UNKNOWN_NOT_INSTRUMENTED',
            })
        scoring = [r for r in rows if r['timed']]
        hits = [r for r in scoring if r['whole_matrix_hit_reconstructed']]
        contexts = []
        for cell in cell_ns:
            if not cell.startswith('bmm:'):
                continue
            members = [r for r in scoring if r['measured_containing_cell'] == cell]
            contexts.append({'cell': cell, 'a066_best_ns_sum': cell_ns[cell],
                             'fraction_of_BMM_time': cell_ns[cell] / bmm_ns,
                             'case_count': len(members),
                             'reconstructed_hit_cases': [r['name'] for r in members if r['whole_matrix_hit_reconstructed']],
                             'hit_case_actual_ns': 'UNKNOWN',
                             'warning': 'Whole cell is context only; it is not the hit cases time or recoverable cost.'})
        results.append({
            'seed': seed, 'run': run, 'full_a066_gate': 'PASS_25_ROUNDS_EXACT_A066',
            'saved_plan_regeneration': 'EXACT_MATCH',
            'timed_BMM_cases': len(scoring), 'untimed_BMM_cases': len(rows) - len(scoring),
            'hit_count_reconstructed': len(hits),
            'hit_cases_reconstructed': [r['name'] for r in hits],
            'hit_MAC_work': sum(r['mac_work'] for r in hits),
            'total_BMM_MAC_work': bmm_work,
            'hit_fraction_of_BMM_MAC_work': sum(r['mac_work'] for r in hits) / bmm_work,
            'hit_input_scan_words': sum(r['runtime_total_scan_words_reconstructed'] for r in hits),
            'miss_total_scan_words': sum(r['runtime_total_scan_words_reconstructed'] for r in scoring if not r['whole_matrix_hit_reconstructed']),
            'hit_output_fill_words': sum(r['output_words'] for r in hits),
            'actual_hit_case_time_coverage': 'UNKNOWN_CASE_TIMES_NOT_RETAINED',
            'a066_BMM_best_ns_sum': bmm_ns,
            'a066_all_operations_best_ns_sum': total_ns,
            'BMM_fraction_of_whole_a066_time': bmm_ns / total_ns,
            'cell_contexts': contexts, 'cases': rows,
        })
    report = {
        'state': 'COMPLETE_SOURCE_RECONSTRUCTION_ONLY',
        'updated_at_utc': datetime.now(timezone.utc).isoformat(),
        'analysis_seconds': time.monotonic() - started,
        'analysis_source_sha256': sha256(Path(__file__).read_bytes()).hexdigest(),
        'only_exposed_seeds': [901, 902, 904], 'future_confirmation_inputs_read': False,
        'underflow_kernel_sha256': UNDERFLOW, 'threshold_strict_magnitude_lt': '0x16000000',
        'source_identity': 'Both existing original generator files match Git blobs at exact official4b7; saved plans exactly regenerate from original Python planner for their completed seeds.',
        'input_status': 'INFERRED_BY_DETERMINISTIC_WORD_RECONSTRUCTION; no raw Lean input-array dump or actual new-guard trace retained. Generator AST transcription was inspected against exact pinned BenchSuite source; no Float32 execution required for guard.',
        'mag1': 'center - min(ctz(word), spread), then optional block scale and normal clamp; not center plus/minus spread.',
        'time_status': 'Official summarise preserves cell total best times only. All individual a066 case weights/actual hit time coverage UNKNOWN; no equal-case or MAC-proportional time allocation.',
        'not_measured': ['scan nanoseconds', 'zero-fill nanoseconds', 'speedup', 'runtime guard traces', 'new candidate checksums'],
        'sources': sources, 'runs': results,
    }
    (HERE / 'review-output-underflow-exposure.json').write_text(json.dumps(report, indent=2, ensure_ascii=False) + '\n', encoding='utf-8')
    lines = ['# 已执行901/902/904的下溢guard曝光', '',
             '仅按精确官方生成器和已保存种子重建原始字；没有运行Lean或新计时，没有读取确认种子。两个原generator字节与官方4b7 Git blob一致，三个保存计划均由原Python planner逐项精确复现。实际Lean数组dump和新guard运行轨迹未保存，结果标为源重建推断。', '',
             '|已执行seed|整块命中case（重建）|命中MAC工作量份额|命中输入扫描词|其余case短路扫描词|命中输出填充词|',
             '|---|---|---:|---:|---:|---:|']
    for r in results:
        lines.append(f"|{r['seed']}|{', '.join(r['hit_cases_reconstructed']) or '无'}|{r['hit_fraction_of_BMM_MAC_work']:.2%}|{r['hit_input_scan_words']}|{r['miss_total_scan_words']}|{r['hit_output_fill_words']}|")
    lines += ['', '逐BMMcase的A/B独立all结果、首个失败字/索引、含失败字读取数、实际先A后B的短路读取数、形状/输入seed和前缀字节SHA在JSON。A拒绝时B运行读取数为0；B独立诊断结果不冒充运行时执行。mag1严格使用center−min(ctz,spread)，再处理scale/clamp及特殊值优先级。', '',
              '**实际命中case的耗时覆盖为UNKNOWN。** 原完整25轮a066回执只保存cell总时间，未保留逐case时间；脚本没有把case工作量比例当时间比例，也没有按相同case数分摊。命中case所在cell的实际背景为：', '']
    for r in results:
        cells = [c for c in r['cell_contexts'] if c['reconstructed_hit_cases']]
        for c in cells:
            lines.append(f"- seed{r['seed']} {c['cell']}整cell占a066 BMM {c['fraction_of_BMM_time']:.2%}（{len(c['reconstructed_hit_cases'])}/{c['case_count']}case命中）；该整cell份额不等于命中部分或可回收成本。")
    lines += ['', '本次没有scan/fill耗时或提速结论。完整命中消除点积的正确性与实际采用仍以精确6a69的新完整gate为准。来源、全部SHA、官方固定ref和逐项缺项均在JSON及source-receipt。']
    (HERE / 'review-output-underflow-exposure.md').write_text('\n'.join(lines) + '\n', encoding='utf-8')
    print(json.dumps({'state': report['state'], 'analysis_seconds': report['analysis_seconds'],
                      'runs': [{k: r[k] for k in ('seed', 'hit_cases_reconstructed', 'hit_fraction_of_BMM_MAC_work', 'hit_input_scan_words', 'miss_total_scan_words')} for r in results]}, ensure_ascii=False))

if __name__ == '__main__':
    main()
