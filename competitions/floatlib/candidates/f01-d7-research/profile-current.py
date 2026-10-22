"""Diagnostic stage profile of parent8eb in a throwaway current-public statement layer.

API: run(g, kernel, out, public_plan, seed). Never call from a scored gate.
Local validation needs only Python: python profile-current.py --selftest
"""
from pathlib import Path
import argparse
import hashlib
import json
import re
import shlex
import shutil
import statistics
import subprocess
import time
import traceback

HEAD = '4b7e83841cc0c32c6529f533923c73d33b5ecf97'
PARENT = '8eb63a2fea39f8c483eb16857cb1dcc35ac4a30168ab91046a48aa1cb561e045'
PAIRS, INNER, PROCESSES = 500000, 3, 3
PREFIX = 'profile-current-'
CORE = 'lp_competition_Submission_RowStream_core'
ROW = 'lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_RowStream_core_spec__0___redArg'
BMM = 'lp_competition_Submission_bmm'
RETURN = re.compile(r'^return (v_[^;\n]+);$', re.M)
STAGES = ('nativeA_ns', 'packB_ns', 'tile_ns', 'output_ns')
FIELDS = ('call', 'core', 'total_ns', *STAGES, 'rows')
CALL = re.compile(r'FL_CALL ' + ' '.join(k + r'=(\d+)' for k in FIELDS))
END = re.compile(r'FL_END bmm_calls=(\d+) core_calls=(\d+)')


def require(ok, message):
    if not ok:
        raise RuntimeError(message)


def sha(data):
    return hashlib.sha256(data).hexdigest()


def file_sha(path):
    h = hashlib.sha256()
    with path.open('rb') as stream:
        for chunk in iter(lambda: stream.read(1024 * 1024), b''):
            h.update(chunk)
    return h.hexdigest()


def clean_c(body):
    return re.sub(r'"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'|/\*.*?\*/|//[^\n]*',
                  '', body, flags=re.S)


def balanced(body):
    # Strip C comments/literals before checking braces. No generated-code parser is needed.
    clean = clean_c(body)
    first = clean.find('{')
    require(first >= 0, 'generated C function has no body')
    depth = 0
    for i, char in enumerate(clean[first:], first):
        depth += (char == '{') - (char == '}')
        require(depth >= 0, 'generated C function has unmatched closing brace')
        if depth == 0:
            require(not clean[i + 1:].strip(), 'function extraction crosses its true closing brace')
    require(depth == 0, 'generated C function extraction is truncated')


def function(text, symbol):
    pattern = (r'^LEAN_EXPORT lean_object\* ' + re.escape(symbol)
               + r'\([^;{]*?\)\s*\{.*?\n}\n}(?=\n(?:LEAN_EXPORT |lean_object\* initialize_))')
    matches = list(re.finditer(pattern, text, re.M | re.S))
    require(len(matches) == 1, f'generated C format drift: expected one full {symbol}, got {len(matches)}')
    match = matches[0]
    balanced(match.group())
    return match


def insert_start(body, code):
    require('goto _start;' not in body, 'entry counter cannot be inserted into a tail-recursive entry')
    body, count = re.subn(r'(_start:\s*\{)', lambda m: m.group() + '\n' + code, body, count=1)
    require(count == 1, 'generated C entry label drift')
    return body


def after_line(body, needle, code):
    lines = body.splitlines()
    indexes = [i for i, line in enumerate(lines) if needle in line]
    require(len(indexes) == 1, f'generated C call-site drift: {needle} ({len(indexes)} matches)')
    lines.insert(indexes[0] + 1, code)
    return '\n'.join(lines)


def instrument(text):
    require('FL_CALL ' not in text and 'fl_current_' not in text, 'source is already instrumented')
    core = function(text, CORE)
    body = core.group()
    returns = list(RETURN.finditer(body))
    require(len(returns) == 4, f'parent core return-count drift: {len(returns)} instead of 4')
    require(len(re.findall(r'\breturn\b', clean_c(body))) == len(returns),
            'unrecognized core return format; refusing incomplete return instrumentation')
    body = insert_start(body, 'unsigned long long fl_start=fl_current_now(), fl_a=fl_start, fl_b=fl_start;\n'
                        'fl_current_core_calls++; fl_current_tile_ns=fl_current_output_ns=fl_current_rows=0;')
    body = after_line(body, '= lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Submission_Packed10_core_spec__0(', 'fl_a=fl_current_now();')
    body = after_line(body, '= lp_competition_Submission_Packed10_packB(', 'fl_b=fl_current_now();')
    body, count = RETURN.subn(lambda m: 'fl_current_emit(fl_start,fl_a,fl_b);\n' + m.group(), body)
    require(count == 4, 'not every parent core return was instrumented')
    balanced(body)
    text = text[:core.start()] + body + text[core.end():]
    row = function(text, ROW)
    body = row.group()
    for needle, counter in [('= l_Array_ofFn___redArg(', 'fl_current_tile_ns'),
                            ('= lp_competition_Submission_RowOutput_row___redArg(', 'fl_current_output_ns')]:
        lines = body.splitlines()
        indexes = [i for i, line in enumerate(lines) if needle in line]
        require(len(indexes) == 1, f'row call-site drift: {needle}')
        i = indexes[0]
        lines.insert(i, '{ unsigned long long fl_local_t=fl_current_now();')
        extra = ' fl_current_rows++;' if counter == 'fl_current_output_ns' else ''
        lines.insert(i + 2, counter + ' += fl_current_now()-fl_local_t; }' + extra)
        body = '\n'.join(lines)
    balanced(body)
    text = text[:row.start()] + body + text[row.end():]
    bmm = function(text, BMM)
    body = insert_start(bmm.group(), 'fl_current_bmm_calls++;')
    balanced(body)
    text = text[:bmm.start()] + body + text[bmm.end():]
    checked = function(text, CORE).group()
    for ret in RETURN.finditer(checked):
        require(checked[:ret.start()].rstrip().endswith('fl_current_emit(fl_start,fl_a,fl_b);'),
                'full-function return coverage check failed')
    require(checked.count('fl_current_emit(fl_start,fl_a,fl_b);') == 4, 'duplicate/missing emit site')
    prelude = r'''
/* Diagnostic Linux x86_64 POSIX ABI; the pinned sysroot omits time.h. */
struct timespec;
struct fl_current_timespec { long sec; long nsec; };
extern int clock_gettime(int, struct timespec *);
extern int printf(const char *, ...);
static unsigned long long fl_current_bmm_calls, fl_current_core_calls;
static unsigned long long fl_current_tile_ns, fl_current_output_ns, fl_current_rows;
static unsigned long long fl_current_now(void) {
    struct fl_current_timespec t;
    if (clock_gettime(1,(struct timespec *)&t)) __builtin_trap();
    return (unsigned long long)t.sec*1000000000ULL+(unsigned long long)t.nsec;
}
static void fl_current_emit(unsigned long long start, unsigned long long a, unsigned long long b) {
    unsigned long long end=fl_current_now();
    printf("FL_CALL call=%llu core=%llu total_ns=%llu nativeA_ns=%llu packB_ns=%llu tile_ns=%llu output_ns=%llu rows=%llu\n",
      fl_current_bmm_calls,fl_current_core_calls,end-start,a-start,b-a,
      fl_current_tile_ns,fl_current_output_ns,fl_current_rows);
}
__attribute__((destructor)) static void fl_current_end(void) {
    printf("FL_END bmm_calls=%llu core_calls=%llu\n",fl_current_bmm_calls,fl_current_core_calls);
}
'''
    return prelude + text, {'full_core_returns': count, 'emit_sites': 4,
                            'full_core_and_row_balanced': True, 'bmm_entry_counter': True}


def call_map(plan):
    require(plan.get('version') == 'suite-v2' and isinstance(plan.get('cases'), list), 'expected suite-v2 plan')
    mapping = []
    names = [c['name'] for c in plan['cases']]
    require(len(names) == len(set(names)), 'duplicate plan case names')
    for case in plan['cases']:
        require(type(case['timed']) is bool, f"invalid timed flag: {case['name']}")
        if case['kernel'] != 'bmm':
            continue
        require(all(type(case[k]) is int and case[k] > 0 for k in ('batch', 'm', 'n', 'p', 'work')),
                f"parent route requires positive dimensions/work: {case['name']}")
        phases = [('checksum', 0)] + [('timed', r) for r in range(1, INNER + 1)] if case['timed'] else [('raw', 0)]
        for phase, rep in phases:
            mapping.append({'call': len(mapping) + 1, 'case': case['name'], 'phase': phase, 'rep': rep,
                            'case_timed': case['timed'], 'expected_rows': case['batch'] * case['m'],
                            **{k: case[k] for k in ('batch', 'm', 'n', 'p', 'work')}})
    require(mapping, 'public plan has no BMM calls')
    return mapping


def bench_rows(log, plan):
    expected = {c['name']: c for c in plan['cases']}
    rows = {}
    for line in log.splitlines():
        p = line.split()
        if len(p) != 4 or p[1] not in ('true', 'false'):
            continue
        require(p[0] in expected and p[0] not in rows, f'unknown/duplicate benchmark row: {line}')
        require(p[2].isdigit() and p[3].isdigit(), f'invalid benchmark row: {line}')
        timed = p[1] == 'true'
        require(timed == expected[p[0]]['timed'], f'benchmark timed flag mismatch: {p[0]}')
        rows[p[0]] = {'timed': timed, 'best_ns': int(p[2]), 'checksum': int(p[3])}
    require(set(rows) == set(expected), f'benchmark case coverage differs: missing={sorted(set(expected)-set(rows))}')
    return rows


def parse_calls(log, mapping):
    lines = [line for line in log.splitlines() if line.startswith('FL_CALL')]
    require(len(lines) == len(mapping), f'FL_CALL count {len(lines)} != expected {len(mapping)}')
    rows = []
    for line, expected in zip(lines, mapping):
        match = CALL.fullmatch(line)
        require(match, f'malformed FL_CALL: {line}')
        row = dict(zip(FIELDS, map(int, match.groups())))
        require(row['call'] == row['core'] == expected['call'], f'BMM/core sequence mismatch: {line}')
        require(row['rows'] == expected['expected_rows'], f"row count mismatch for {expected['case']}: {line}")
        row['residual_ns'] = row['total_ns'] - sum(row[k] for k in STAGES)
        require(row['residual_ns'] >= 0, f'negative residual: {line}')
        rows.append({**expected, **row})
    ends = [line for line in log.splitlines() if line.startswith('FL_END')]
    require(len(ends) == 1, 'missing/duplicate FL_END route totals')
    end = END.fullmatch(ends[0])
    require(end and list(map(int, end.groups())) == [len(mapping)] * 2, 'BMM/core final route totals differ')
    return rows


def run(g, kernel: Path, out: Path, public_plan: dict, seed: int):
    """Instrument only the disposable upper layer; leave its binary diagnostic-only."""
    kernel, out = Path(kernel), Path(out)
    out.mkdir(parents=True, exist_ok=True)
    require(not (out / (PREFIX + 'plan.json')).exists(), 'profile output already exists; use a fresh out directory')

    def save(name, data):
        with (out / (PREFIX + name)).open('xb') as stream:
            stream.write(data)

    def save_json(name, value):
        save(name, (json.dumps(value, indent=2) + '\n').encode())

    try:
        require(getattr(g, '_SANDBOX', False), 'requires the official sandbox throwaway upper layer')
        require(not any(name == 'score' for name, _ in g.STAGES), 'refusing a scored gate: call only in statement-only replay')
        require(g._PAIRS == PAIRS and type(seed) is int and 0 <= seed < 2**32, 'expected pairs=500000 and uint32 seed')
        kernel_raw = kernel.read_bytes()
        require(sha(kernel_raw) == PARENT, 'only exact parent8eb is supported')
        require(sha(g.WORK.read_bytes()) == PARENT, 'statement source does not match parent8eb input')
        head = subprocess.check_output(['git', 'rev-parse', 'HEAD'], cwd=g.HERE, text=True).strip()
        require(head == HEAD, f'current official commit differs: {head}')
        generator = g.HERE / 'benchmark_suite.py'
        suite = g.HERE / 'suites/public-v2.json'
        require(Path(g.benchmark_suite.__file__).resolve() == generator.resolve(), 'gate imported a different suite generator')
        drawn = g.benchmark_suite.make_plan(g.benchmark_suite.load(suite), seed, PAIRS)
        require(drawn == public_plan, 'public_plan differs from exact official generator/seed/public-v2/work')
        compact = json.dumps(public_plan, separators=(',', ':')).encode()
        mapping = call_map(public_plan)
        upper = g.LAYER / 'upper'
        cpaths = list(upper.rglob('Submission.c'))
        require(len(cpaths) == 1, f'expected one upper-layer Submission.c, got {len(cpaths)}')
        cpath = cpaths[0]
        original = cpath.read_bytes()
        changed, coverage = instrument(original.decode('utf-8'))
        changed = changed.encode()
        commands = []
        for path in sorted(upper.rglob('*.trace')):
            try:
                commands.extend(row['message'][3:] for row in json.loads(path.read_bytes()).get('log', [])
                                if row.get('message', '').startswith('.> '))
            except (OSError, ValueError):
                continue
        commands = list(dict.fromkeys(commands))
        save_json('build-commands.json', commands)
        parsed = [shlex.split(command) for command in commands]
        bench = g.BUILD / 'bin/benchFull'
        compiles = [a for a in parsed if '-c' in a and str(g.BUILD / 'ir/Submission.c') in a]
        links = [a for a in parsed if '-c' not in a and '-o' in a and a[a.index('-o') + 1] == str(bench)]
        require(len(compiles) == len(links) == 1, 'ambiguous/missing Submission compile or benchFull link trace')
        compile_argv, link_argv = compiles[0], links[0]
        obj = Path(compile_argv[compile_argv.index('-o') + 1])

        def visible(logical):
            logical = Path(logical)
            try:
                top = upper / logical.relative_to(g.BUILD)
                if top.is_file():
                    return top
            except ValueError:
                pass
            return logical if logical.is_file() else None

        def receipt(logical):
            path = visible(logical)
            return {'logical': str(logical), 'state': 'VERIFIED', 'actual': str(path),
                    'bytes': path.stat().st_size, 'sha256': file_sha(path)} if path else {
                        'logical': str(logical), 'state': 'UNAVAILABLE'}

        identities = {'before': {'object': receipt(obj), 'binary': receipt(bench)}}
        save_json('build-identities-before.json', identities['before'])
        response_files = []
        for i, arg in enumerate(a for a in link_argv if a.startswith('@')):
            logical = Path(arg[1:])
            row = receipt(logical)
            path = visible(logical)
            if path:
                name = f'link-response-{i}.rsp'
                save(name, path.read_bytes())
                row['artifact'] = PREFIX + name
            response_files.append(row)
        save('original.c', original)
        save('instrumented.c', changed)
        save('kernel.lean', kernel_raw)
        save('generator.py', generator.read_bytes())
        save('suite.json', suite.read_bytes())
        save('public-plan.compact.json', compact)
        save_json('public-plan.json', public_plan)
        env = {'BENCH_PLAN': compact.decode(), 'BENCH_SEED': str(seed), 'BENCH_PAIRS': str(PAIRS),
               'BENCH_INNER': str(INNER), 'LEAN_ABORT_ON_PANIC': '1'}
        cpu = getattr(g, '_BENCH_CPU', '')
        bench_argv = (['taskset', '-c', str(cpu)] if cpu and shutil.which('taskset') else []) + [str(bench)]
        plan = {'diagnostic_only': True, 'scope': 'Instrumented parent8eb core only; no full gate, ranking or official stage-share claim.',
                'official_commit': head, 'kernel_sha256': sha(kernel_raw), 'seed': seed, 'pairs': PAIRS, 'inner': INNER,
                'processes': PROCESSES, 'control_processes': 1, 'execution_order': ['control-0'] + [f'instrumented-{i}' for i in range(PROCESSES)],
                'expected_calls_per_process': len(mapping), 'call_map': mapping, 'coverage': coverage,
                'public_plan_compact_sha256': sha(compact), 'generator_sha256': file_sha(generator),
                'suite_sha256': file_sha(suite), 'gate_sha256': file_sha(g.HERE / 'gate.py'),
                'module_sha256': file_sha(Path(__file__)), 'original_c_sha256': sha(original), 'instrumented_c_sha256': sha(changed),
                'compile_argv': compile_argv, 'link_argv': link_argv, 'bench_argv': bench_argv, 'response_files': response_files,
                'bench_cpu_requested': cpu, 'stage_zero_ns_valid': True,
                'overhead_scope': 'Per-case instrumented benchmark best_ns versus the one earlier uninstrumented control; includes profiler overhead and process noise. Checksum/raw pass overhead has no uninstrumented per-pass timer and remains UNKNOWN.',
                'throwaway_layer_left_instrumented': True}
        save_json('plan.json', plan)
        executions = []

        def command(argv, name, build, cap=120):
            started = time.monotonic()
            code, log = g.run(argv, cap, build=build, env_extra=env,
                              memory_mb=g._BUILD_MEMORY_MB if build == 'write' else g._BENCH_MEMORY_MB)
            save(name + '.log', log.encode())
            executions.append({'name': name, 'argv': argv, 'build': build, 'exit_code': code,
                               'elapsed_seconds': time.monotonic() - started, 'log_sha256': sha(log.encode()),
                               'bench_plan_sha256': sha(compact)})
            save_json(f'execution-{len(executions)-1}.json', executions[-1])
            require(code == 0, f'{name}: exit {code}; raw log retained')
            return log

        control_log = command(bench_argv, 'control-0', 'read')
        require('FL_CALL' not in control_log and 'FL_END' not in control_log, 'control binary was already instrumented')
        control = bench_rows(control_log, public_plan)
        save_json('control-0.json', control)
        cpath.write_bytes(changed)
        command(compile_argv, 'compile', 'write', 60)
        identities['after_compile'] = {'object': receipt(obj)}
        save_json('build-identities-after-compile.json', identities['after_compile'])
        command(link_argv, 'link', 'write', 60)
        identities['after_link'] = {'object': receipt(obj), 'binary': receipt(bench)}
        save_json('build-identities.json', identities)
        for kind in ('object', 'binary'):
            after = identities['after_link'][kind]
            before = identities['before'][kind]
            require(after['state'] == 'VERIFIED', f'instrumented {kind} is inaccessible')
            require(before.get('sha256') != after['sha256'], f'{kind} did not change after instrumentation')
            with Path(after['actual']).open('rb') as stream:
                tail, found = b'', False
                for chunk in iter(lambda: stream.read(1024 * 1024), b''):
                    combined = tail + chunk
                    if b'FL_CALL call=' in combined:
                        found = True
                        break
                    tail = combined[-32:]
            require(found, f'FL_CALL marker missing from rebuilt {kind}; stop before profiling')
        measurements = []
        for process in range(PROCESSES):
            log = command(bench_argv, f'instrumented-{process}', 'read')
            cells = bench_rows(log, public_plan)
            require({n: r['checksum'] for n, r in cells.items()} == {n: r['checksum'] for n, r in control.items()},
                    f'process {process}: checksum differs from exact control')
            calls = parse_calls(log, mapping)
            overhead = {}
            for case in (c for c in public_plan['cases'] if c['kernel'] == 'bmm'):
                name = case['name']
                base, profiled = control[name]['best_ns'], cells[name]['best_ns']
                measured = case['timed'] and base > 0
                overhead[name] = {'control_best_ns': base, 'instrumented_best_ns': profiled,
                                  'added_ns': profiled - base if measured else None,
                                  'ratio': profiled / base if measured else None,
                                  'status': 'DIAGNOSTIC_OBSERVED' if measured else 'UNKNOWN',
                                  'reason': None if measured else 'No positive timed control baseline for this case/pass.'}
            result = {'process': process, 'benchmark_rows': cells, 'calls': calls, 'case_overhead': overhead,
                      'phase_counts': {phase: sum(c['phase'] == phase for c in calls) for phase in ('timed', 'checksum', 'raw')}}
            save_json(f'instrumented-{process}.json', result)
            measurements.append(result)
        summary = {'diagnostic_only': True, 'complete': True, 'checksum_matches_control': True, 'complete_call_mapping': True,
                   'official_gate_status': 'NOT_RUN_BY_THIS_MODULE', 'plan_artifact': PREFIX + 'plan.json',
                   'expected_calls_per_process': len(mapping), 'measurements': measurements,
                   'case_overhead_median_ratio': {name: statistics.median(r['case_overhead'][name]['ratio'] for r in measurements)
                                                  if control[name]['timed'] and control[name]['best_ns'] > 0 else None
                                                  for name in measurements[0]['case_overhead']},
                   'executions': executions, 'build_identities': identities,
                   'warning': 'Per-row clock probes and printf change execution cost. Timed, checksum and raw records remain separate; no official stage shares are inferred.'}
        save_json('result.json', summary)
        return summary
    except Exception as error:
        path = out / (PREFIX + 'error.json')
        if not path.exists():
            save_json('error.json', {'diagnostic_only': True, 'complete': False, 'error': str(error), 'traceback': traceback.format_exc()})
        raise


def selftest():
    candidates = Path(__file__).resolve().parents[1]
    base = candidates / 'f01-mul-log2-proof1/ci-runs/39789494626/download-1355dba2673f427a90994d7eab3b7f9e/diagnostics/f01-d6-costsplit'
    original = (base / 'candidate-generated-0.c').read_bytes()
    require(sha(original) == '65665cb68141c2603e48f62731058e45414af8faeffce9b1d02040e8a7705677', 'R6 original fixture changed')
    legacy = {}
    exec((candidates / 'f01-d6-research/profile-scored.py').read_text(encoding='utf-8'), legacy)
    old = legacy['instrument'](original.decode())
    require(old.encode() == (base / 'profile-instrumented.c').read_bytes(), 'R6 byte replay no longer matches')
    old_full = function(old, CORE).group()
    require(len(list(RETURN.finditer(old_full))) == 4 and old_full.count('FL_CALL ') == 3,
            'old missing-return red check no longer reproduces')
    last = list(RETURN.finditer(old_full))[-1]
    require('FL_CALL' not in old_full[max(0, last.start()-100):last.start()], 'old final return unexpectedly instrumented')
    changed, coverage = instrument(original.decode())
    require(coverage['full_core_returns'] == coverage['emit_sites'] == 4, 'new complete-return green failed')
    plan_raw = (candidates / 'f01-d7-research/initial-public-plan.json').read_bytes()
    require(sha(plan_raw) == '903683eb628c5344bda06c111083207fe3f1a821d31693b4556ef978a20843e4', 'R7 actual plan fixture changed')
    plan = json.loads(plan_raw)
    mapping = call_map(plan)
    require(len(mapping) == 137, 'actual R7 fixture must yield 137 BMM calls at inner=3')
    phases = {phase: sum(c['phase'] == phase for c in mapping) for phase in ('timed', 'checksum', 'raw')}
    require(phases == {'timed': 102, 'checksum': 34, 'raw': 1}, 'phase separation failed')
    lines = ['FL_CALL ' + ' '.join(f'{k}={c["call"] if k in ("call","core") else c["expected_rows"] if k == "rows" else 0}' for k in FIELDS)
             for c in mapping]
    log = '\n'.join(lines + ['FL_END bmm_calls=137 core_calls=137'])
    require(len(parse_calls(log, mapping)) == 137, 'zero stage times must be accepted')
    rejected = []
    for label, bad in [('missing call', log.replace(lines[-1] + '\n', '')),
                       ('negative residual', log.replace('nativeA_ns=0', 'nativeA_ns=1', 1)),
                       ('wrong rows', log.replace('rows=' + str(mapping[0]['expected_rows']), 'rows=0', 1)),
                       ('route mismatch', log.replace('core=1 ', 'core=0 ', 1)),
                       ('truncated function', old_full[:old_full.rfind('}')])]:
        try:
            balanced(bad) if label == 'truncated function' else parse_calls(bad, mapping)
        except RuntimeError:
            rejected.append(label)
        else:
            raise RuntimeError('selftest failed to reject ' + label)
    print(json.dumps({'selftest': 'PASS', 'old_missing_return': 'RED_REPRODUCED', 'old_emit_sites': 3,
                      'new_full_core_returns': 4, 'new_emit_sites': 4, 'new_balanced_functions': True,
                      'actual_plan_calls': len(mapping), 'phase_counts': phases, 'zero_stage_ns': 'ACCEPTED',
                      'rejected': rejected, 'original_c_sha256': sha(original), 'new_instrumented_c_sha256': sha(changed.encode()),
                      'actual_plan_sha256': sha(plan_raw), 'module_sha256': file_sha(Path(__file__)),
                      'linux_runtime': 'NOT_RUN'}, indent=2))


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--selftest', action='store_true', required=True)
    parser.parse_args()
    selftest()
