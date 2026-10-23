"""Exact retained41 diagnostic profile. Never an official scored gate or adoption input."""
from pathlib import Path
import argparse, hashlib, json, re, shlex, shutil, statistics, subprocess, time, traceback
HEAD = '4b7e83841cc0c32c6529f533923c73d33b5ecf97'
PARENT = '41bce4856c4c921dd67b6115928df16e5e8ed08a55b71f1296d28b77cf9ce9a7'
FIXTURE_C = 'fb421a595ceced1cf8994f19ccb32704ac20a02a0430eda6c4134bf042d075db'
GATE_SHA = '1eb74ef7479b0023c721e776cc5e4073af21c6662b4afffcf16a48a124d27194'
GENERATOR_SHA = '7198464dfc08f4bb2a3a5e31ce5a105964d1d73ad6b11ee49e682a30c04daf69'
SUITE_SHA = 'a16494e97c6a073bfd8accf72480c34534c87808092c56074fdcfa42cd34868a'
PAIRS, INNER, PROCESSES = 500000, 3, 3
PREFIX = 'profile-retained-'
CORE = 'lp_competition_Submission_RowStream_core'
ROW = 'lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_RowStream_core_spec__0___redArg'
BMM = 'lp_competition_Submission_bmm'
DIRECT = 'lp_competition_Submission_DirectSmall_core'
DOT = 'lp_competition_Submission_NativeFinal_dot'
REPLAY = 'lp_competition_Submission_R7NaNReplay_replayEarly'
RETURN = re.compile(r'^return (v_[^;\n]+);$', re.M)
STAGES = ('nativeA_ns', 'packB_ns', 'tile_ns', 'output_ns', 'direct_ns')
FIELDS = ('call','detail','route','core','direct','total_ns',*STAGES,'native_dot_ns','replay_ns','rows','dot_calls','replay_calls')
CALL = re.compile(r'FL_CALL ' + ' '.join(k + r'=(\d+)' for k in FIELDS))
END = re.compile(r'FL_END bmm_calls=(\d+) core_calls=(\d+) direct_calls=(\d+)')


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
    pattern = (r'^LEAN_EXPORT (?:lean_object\*|uint32_t|float) ' + re.escape(symbol)
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


def instrument(text, detailed=True):
    require(sha(text.encode()) == FIXTURE_C, 'retained41 generated C differs from exact reviewed fixture')
    coverage = {}
    def replace(symbol, transform):
        nonlocal text
        match = function(text, symbol)
        body = match.group()
        expected = len(RETURN.findall(body))
        require(expected and len(re.findall(r'\breturn\b', clean_c(body))) == expected,
                'unrecognized real return in ' + symbol)
        body = transform(body)
        require(len(RETURN.findall(body)) == expected, 'return inventory changed: ' + symbol)
        balanced(body)
        text = text[:match.start()] + body + text[match.end():]
        coverage[symbol] = {'real_returns': expected, 'covered_returns': expected}
    def returns(body, code):
        changed, count = RETURN.subn(lambda m: code + '\n' + m.group(), body)
        require(count > 0 and changed.count(code) == count, 'duplicate/missing return probe')
        for ret in RETURN.finditer(changed):
            require(changed[:ret.start()].rstrip().endswith(code), 'incomplete real-return probe')
        return changed
    def around(body, needle, counter, count=''):
        lines = body.splitlines()
        indexes = [i for i, line in enumerate(lines) if needle in line]
        require(len(indexes) == 1, 'stage call-site drift: ' + needle)
        i = indexes[0]
        lines.insert(i, '{ unsigned long long fl_local_t=FL_STAGE_NOW(); ' + count)
        lines.insert(i+2, counter + ' += FL_STAGE_NOW()-fl_local_t; }')
        return '\n'.join(lines)
    def core(body):
        body = insert_start(body, 'unsigned long long fl_start=FL_STAGE_NOW(), fl_a=fl_start, fl_b=fl_start;\nfl_ret_core_calls++; fl_ret_route=2;')
        body = after_line(body, '= lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Submission_Packed10_core_spec__0(', 'fl_a=FL_STAGE_NOW();')
        body = after_line(body, '= lp_competition_Submission_Packed10_packB(', 'fl_b=FL_STAGE_NOW();')
        return returns(body, 'fl_ret_nativeA_ns+=fl_a-fl_start; fl_ret_packB_ns+=fl_b-fl_a;')
    replace(CORE, core)
    def row(body):
        body = around(body, '= l_Array_ofFn___redArg(', 'fl_ret_tile_ns')
        return around(body, '= lp_competition_Submission_RowOutput_row___redArg(', 'fl_ret_output_ns', 'fl_ret_rows++;')
    replace(ROW, row)
    def direct(body):
        body = insert_start(body, 'unsigned long long fl_start=FL_STAGE_NOW(); fl_ret_direct_calls++; fl_ret_route=1;')
        return returns(body, 'fl_ret_direct_ns+=FL_STAGE_NOW()-fl_start;')
    replace(DIRECT, direct)
    def dot(body):
        return around(body, '= lp_competition_Submission_NativeFinal_dotLoop(', 'fl_ret_native_dot_ns', 'fl_ret_dot_calls++;')
    replace(DOT, dot)
    def replay(body):
        body = insert_start(body, 'unsigned long long fl_start=FL_STAGE_NOW(); fl_ret_replay_calls++;')
        return returns(body, 'fl_ret_replay_ns+=FL_STAGE_NOW()-fl_start;')
    replace(REPLAY, replay)
    def bmm(body):
        body = insert_start(body, 'unsigned long long fl_start=fl_ret_now(); fl_ret_bmm_calls++; fl_ret_reset();')
        return returns(body, 'fl_ret_emit(fl_start);')
    replace(BMM, bmm)
    # Subcalls are measured at their unique complete invocation. Their return
    # inventory is checked, but only entry/core/replay functions need exit probes.
    coverage[ROW]['coverage_kind'] = 'unique tile and output invocation sites'
    coverage[DOT]['coverage_kind'] = 'unique complete native dotLoop invocation'
    prelude = r"""
/* Diagnostic Linux x86_64 POSIX ABI; not part of an official submission. */
struct timespec;
struct fl_ret_timespec { long sec; long nsec; };
extern int clock_gettime(int, struct timespec *);
extern int printf(const char *, ...);
static unsigned long long fl_ret_bmm_calls, fl_ret_core_calls, fl_ret_direct_calls;
static unsigned long long fl_ret_route, fl_ret_nativeA_ns, fl_ret_packB_ns, fl_ret_tile_ns, fl_ret_output_ns;
static unsigned long long fl_ret_direct_ns, fl_ret_native_dot_ns, fl_ret_replay_ns, fl_ret_rows, fl_ret_dot_calls, fl_ret_replay_calls;
static unsigned long long fl_ret_now(void) {
    struct fl_ret_timespec t;
    if (clock_gettime(1,(struct timespec *)&t)) __builtin_trap();
    return (unsigned long long)t.sec*1000000000ULL+(unsigned long long)t.nsec;
}
#define FL_DETAIL @DETAIL@
#define FL_STAGE_NOW() @CLOCK@
static void fl_ret_reset(void) {
    fl_ret_route=fl_ret_nativeA_ns=fl_ret_packB_ns=fl_ret_tile_ns=fl_ret_output_ns=0;
    fl_ret_direct_ns=fl_ret_native_dot_ns=fl_ret_replay_ns=fl_ret_rows=fl_ret_dot_calls=fl_ret_replay_calls=0;
}
static void fl_ret_emit(unsigned long long start) {
    unsigned long long end=fl_ret_now();
    printf("FL_CALL call=%llu detail=%llu route=%llu core=%llu direct=%llu total_ns=%llu nativeA_ns=%llu packB_ns=%llu tile_ns=%llu output_ns=%llu direct_ns=%llu native_dot_ns=%llu replay_ns=%llu rows=%llu dot_calls=%llu replay_calls=%llu\n",
      fl_ret_bmm_calls,(unsigned long long)FL_DETAIL,fl_ret_route,fl_ret_core_calls,fl_ret_direct_calls,end-start,
      fl_ret_nativeA_ns,fl_ret_packB_ns,fl_ret_tile_ns,fl_ret_output_ns,fl_ret_direct_ns,fl_ret_native_dot_ns,fl_ret_replay_ns,fl_ret_rows,fl_ret_dot_calls,fl_ret_replay_calls);
}
__attribute__((destructor)) static void fl_ret_end(void) {
    printf("FL_END bmm_calls=%llu core_calls=%llu direct_calls=%llu\n",fl_ret_bmm_calls,fl_ret_core_calls,fl_ret_direct_calls);
}
"""
    prelude = prelude.replace('@DETAIL@', str(int(detailed))).replace('@CLOCK@', 'fl_ret_now()' if detailed else '0ULL')
    return prelude + text, {'functions':coverage, 'all_real_returns_checked':True,
                            'bmm_emit_sites':coverage[BMM]['real_returns'], 'detailed_timers':bool(detailed)}


def call_map(plan):
    require(plan.get('version') == 'suite-v2' and isinstance(plan.get('cases'),list), 'expected suite-v2 drawn plan')
    require(len({c['name'] for c in plan['cases']}) == len(plan['cases']), 'duplicate case names')
    mapping=[]
    for case in plan['cases']:
        require(type(case['timed']) is bool, 'invalid timed flag')
        if case['kernel'] != 'bmm': continue
        require(all(type(case[k]) is int and case[k]>0 for k in ('batch','m','n','p','work')), 'positive dimensions required')
        route = 1 if case['n']<=4 or case['p']<=2 else 2
        phases=[('checksum',0)]+[('timed',i) for i in range(1,INNER+1)] if case['timed'] else [('raw',0)]
        for phase,rep in phases:
            mapping.append({'call':len(mapping)+1,'case':case['name'],'phase':phase,'rep':rep,'case_timed':case['timed'],
                            'expected_route':route,'route_name':'direct' if route==1 else 'packed',
                            'expected_rows':case['batch']*case['m'] if route==2 else 0,
                            'expected_dot_calls':case['batch']*case['m']*case['p'] if route==1 else 0,
                            **{k:case[k] for k in ('batch','m','n','p','work')}})
    require(mapping,'no BMM calls')
    return mapping


def parse_calls(log,mapping,detailed=1):
    lines=[line for line in log.splitlines() if line.startswith('FL_CALL')]
    require(len(lines)==len(mapping),'FL_CALL total differs from original plan')
    rows=[]; cores=directs=0
    for line,expected in zip(lines,mapping):
        match=CALL.fullmatch(line);require(match,'malformed FL_CALL')
        row=dict(zip(FIELDS,map(int,match.groups())))
        cores += expected['expected_route']==2; directs += expected['expected_route']==1
        require(row['call']==expected['call'] and row['detail']==detailed and row['route']==expected['expected_route'], 'call/detail/route mismatch')
        require(row['core']==cores and row['direct']==directs, 'direct/packed cumulative totals mismatch')
        require(row['rows']==expected['expected_rows'] and row['dot_calls']==expected['expected_dot_calls'], 'row/output invocation count mismatch')
        if row['route']==1:
            require(all(row[k]==0 for k in ('nativeA_ns','packB_ns','tile_ns','output_ns')), 'direct call contains packed stages')
        else:require(row['direct_ns']==row['native_dot_ns']==0,'packed call contains direct stages')
        require(row['replay_ns']<=row['total_ns'], 'overlapping replay substage exceeds total')
        require(row['replay_calls']<=expected['batch']*expected['m']*expected['p'], 'too many exact replay calls')
        parent_stage = row['direct_ns'] if row['route']==1 else row['output_ns']
        require(row['replay_ns']<=parent_stage and row['native_dot_ns']<=row['direct_ns'],
                'overlapping substage exceeds its measured parent stage')
        row['residual_ns']=row['total_ns']-sum(row[k] for k in STAGES)
        require(row['residual_ns']>=0,'negative disjoint stage residual')
        if not detailed:require(all(row[k]==0 for k in (*STAGES,'native_dot_ns','replay_ns')), 'control has detailed timers enabled')
        rows.append({**expected,**row})
    ends=[line for line in log.splitlines() if line.startswith('FL_END')]
    require(len(ends)==1,'missing/duplicate FL_END')
    match=END.fullmatch(ends[0]);require(match and list(map(int,match.groups()))==[len(mapping),cores,directs], 'final direct/packed totals mismatch')
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
        require(sha(kernel_raw) == PARENT, 'only exact retained41 is supported')
        require(sha(g.WORK.read_bytes()) == PARENT, 'statement source does not match retained41 input')
        head = subprocess.check_output(['git', 'rev-parse', 'HEAD'], cwd=g.HERE, text=True).strip()
        require(head == HEAD, f'current official commit differs: {head}')
        generator = g.HERE / 'benchmark_suite.py'
        suite = g.HERE / 'suites/public-v2.json'
        require(file_sha(g.HERE / 'gate.py') == GATE_SHA and file_sha(generator) == GENERATOR_SHA and file_sha(suite) == SUITE_SHA,
                'official gate/generator/suite bytes changed')
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
        control_c, control_coverage = instrument(original.decode('utf-8'), detailed=False)
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
        compiles = [a for a in parsed if Path(a[0]).name == 'clang' and '-c' in a and str(g.BUILD / 'ir/Submission.c') in a]
        links = [a for a in parsed if Path(a[0]).name == 'clang' and '-c' not in a and '-o' in a and a[a.index('-o') + 1] == str(bench)]
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
        save('harness-control.c', control_c.encode())
        save('kernel.lean', kernel_raw)
        save('generator.py', generator.read_bytes())
        save('suite.json', suite.read_bytes())
        save('public-plan.compact.json', compact)
        save_json('public-plan.json', public_plan)
        env = {'BENCH_PLAN': compact.decode(), 'BENCH_SEED': str(seed), 'BENCH_PAIRS': str(PAIRS),
               'BENCH_INNER': str(INNER), 'LEAN_ABORT_ON_PANIC': '1'}
        cpu = getattr(g, '_BENCH_CPU', '')
        bench_argv = (['taskset', '-c', str(cpu)] if cpu and shutil.which('taskset') else []) + [str(bench)]
        plan = {'diagnostic_only': True, 'scope': 'Instrumented exact retained41 direct and packed entries; no full gate, ranking or official stage-share claim.',
                'official_commit': head, 'kernel_sha256': sha(kernel_raw), 'seed': seed, 'pairs': PAIRS, 'inner': INNER,
                'processes': PROCESSES, 'control_processes': 1, 'harness_control_processes': 1, 'harness_control_c_sha256': sha(control_c.encode()), 'harness_control_coverage': control_coverage, 'execution_order': ['control-0','harness-control-0'] + [f'instrumented-{i}' for i in range(PROCESSES)],
                'expected_calls_per_process': len(mapping), 'call_map': mapping, 'coverage': coverage,
                'public_plan_compact_sha256': sha(compact), 'generator_sha256': file_sha(generator),
                'suite_sha256': file_sha(suite), 'gate_sha256': file_sha(g.HERE / 'gate.py'),
                'module_sha256': file_sha(Path(__file__)), 'original_c_sha256': sha(original), 'instrumented_c_sha256': sha(changed),
                'compile_argv': compile_argv, 'link_argv': link_argv, 'bench_argv': bench_argv, 'response_files': response_files,
                'bench_cpu_requested': cpu, 'stage_zero_ns_valid': True,
                'stage_boundaries': {'nativeA_ns':'Packed core entry through nativeA map completion, including initial row-index array preparation',
                    'packB_ns':'From nativeA completion through packB completion',
                    'tile_ns':'Sum of complete per-row rowTiles Array.ofFn calls',
                    'output_ns':'Sum of complete per-row RowOutput.row calls',
                    'direct_ns':'Complete DirectSmall.core invocation',
                    'native_dot_ns':'NativeFinal.dotLoop calls within direct path; overlaps direct_ns',
                    'replay_ns':'Complete replayEarly calls in either route; overlaps direct_ns/output_ns',
                    'residual_ns':'BMM total minus the five disjoint stages; includes dispatch, row-loop bookkeeping, append and probe overhead'},
                'overhead_scope': 'Per-case best_ns against original uninstrumented binary, plus per-call timed/checksum/raw comparison against the same counter/output harness with internal clocks disabled. Sequential processes include process noise; controls do not establish official stage shares.',
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
        command([compile_argv[0], '--version'], 'compiler-version', 'read', 15)
        compiler_path = Path(compile_argv[0])
        if not compiler_path.is_absolute():
            resolved = shutil.which(compile_argv[0])
            require(resolved is not None, 'compiler executable identity cannot be resolved')
            compiler_path = Path(resolved)
        compiler_identity = receipt(compiler_path)
        require(compiler_identity['state'] == 'VERIFIED', 'compiler executable is inaccessible')
        save_json('compiler.json', {'argv0':compile_argv[0], 'binary': compiler_identity,
                                  'version_log': PREFIX+'compiler-version.log',
                                  'version_log_sha256':file_sha(out/(PREFIX+'compiler-version.log'))})
        cpath.write_bytes(control_c.encode())
        command(compile_argv, 'harness-control-compile', 'write', 60)
        command(link_argv, 'harness-control-link', 'write', 60)
        save_json('harness-control-build-identities.json', {'object':receipt(obj),'binary':receipt(bench)})
        harness_log = command(bench_argv, 'harness-control-0', 'read')
        harness_cells = bench_rows(harness_log, public_plan)
        require({n:r['checksum'] for n,r in harness_cells.items()} == {n:r['checksum'] for n,r in control.items()}, 'harness-control checksum differs from original')
        harness_calls = parse_calls(harness_log,mapping,detailed=0)
        save_json('harness-control-0.json', {'benchmark_rows':harness_cells,'calls':harness_calls})
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
            call_overhead = [{**{k:c[k] for k in ('call','case','phase','rep','route_name')}, 'control_total_ns':b['total_ns'], 'instrumented_total_ns':c['total_ns'], 'added_ns':c['total_ns']-b['total_ns'], 'ratio':c['total_ns']/b['total_ns'] if b['total_ns']>0 else None, 'scope':'same counter/output harness, internal stage clocks disabled in control; sequential process noise remains'} for c,b in zip(calls,harness_calls)]
            result = {'call_overhead': call_overhead, 'process': process, 'benchmark_rows': cells, 'calls': calls, 'case_overhead': overhead,
                      'phase_counts': {phase: sum(c['phase'] == phase for c in calls) for phase in ('timed', 'checksum', 'raw')}}
            result['route_phase_totals'] = {route:{phase:{'calls':len(group),
                **{key:sum(c[key] for c in group) for key in ('total_ns',*STAGES,'native_dot_ns','replay_ns','residual_ns','rows','dot_calls','replay_calls')}}
                for phase in ('timed','checksum','raw')
                for group in [[c for c in calls if c['route_name']==route and c['phase']==phase]]}
                for route in ('direct','packed')}
            save_json(f'instrumented-{process}.json', result)
            measurements.append(result)
        summary = {'diagnostic_only': True, 'complete': True, 'checksum_matches_control': True, 'complete_call_mapping': True,
                   'official_gate_status': 'NOT_RUN_BY_THIS_MODULE', 'plan_artifact': PREFIX + 'plan.json',
                   'expected_calls_per_process': len(mapping), 'measurements': measurements,
                   'case_overhead_median_ratio': {name: statistics.median(r['case_overhead'][name]['ratio'] for r in measurements)
                                                  if control[name]['timed'] and control[name]['best_ns'] > 0 else None
                                                  for name in measurements[0]['case_overhead']},
                   'executions': executions, 'build_identities': identities, 'harness_control_artifact': PREFIX+'harness-control-0.json', 'substage_scope':'native_dot_ns and replay_ns overlap direct_ns/output_ns; exclude them from disjoint residual sums',
                   'warning': 'Per-row clock probes and printf change execution cost. Timed, checksum and raw records remain separate; no official stage shares are inferred.'}
        save_json('result.json', summary)
        return summary
    except Exception as error:
        path = out / (PREFIX + 'error.json')
        if not path.exists():
            save_json('error.json', {'diagnostic_only': True, 'complete': False, 'error': str(error), 'traceback': traceback.format_exc()})
        raise


def selftest():
    root=Path(__file__).resolve().parents[5]
    directory=root/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/39945391484/download-8f572f9d52f14db8ab7c867729396308/diagnostics/f01-d7-public-suite/public-suite'
    fixture=directory/'diagnostics/f01-r8-combined-result-guard/candidate-generated-0.c'
    raw=fixture.read_bytes();require(sha(raw)==FIXTURE_C,'fixture C changed')
    index=json.loads(fixture.with_name('candidate-c-index.json').read_bytes())
    require(any(r['sha256']==FIXTURE_C and r['kernel_sha256']==PARENT and r['module']=='Submission' for r in index),'codegen snapshot not bound to retained41')
    original=raw.decode();changed,coverage=instrument(original);control,cc=instrument(original,False)
    require(changed!=control and coverage['bmm_emit_sites']==3,'BMM return coverage drift')
    require(coverage['functions'][CORE]['real_returns']==4 and coverage['functions'][DIRECT]['real_returns']==1,'core return drift')
    require(changed.replace('#define FL_DETAIL 1','#define FL_DETAIL 0').replace('#define FL_STAGE_NOW() fl_ret_now()','#define FL_STAGE_NOW() 0ULL')==control,'control is not structurally identical except timer switches')
    plan=json.loads((directory/'public-drawn-plan.json').read_bytes());mapping=call_map(plan)
    packed=sum(x['expected_route']==2 for x in mapping);direct=len(mapping)-packed
    require(packed>0 and direct>0 and len(mapping)==137,'actual fixture route/call coverage')
    synthetic=[];cores=directs=0
    for c in mapping:
        cores+=c['expected_route']==2;directs+=c['expected_route']==1
        values={k:0 for k in FIELDS};values.update(call=c['call'],detail=1,route=c['expected_route'],core=cores,direct=directs,rows=c['expected_rows'],dot_calls=c['expected_dot_calls'])
        synthetic.append('FL_CALL '+' '.join(k+'='+str(values[k]) for k in FIELDS))
    log='\n'.join(synthetic+[f'FL_END bmm_calls={len(mapping)} core_calls={packed} direct_calls={direct}'])
    parsed=parse_calls(log,mapping)
    require(len(parsed)==137,'synthetic route parser failed')
    print(json.dumps({'selftest':'PASS','kernel_sha256':PARENT,'fixture_c_sha256':FIXTURE_C,'instrumented_c_sha256':sha(changed.encode()),'harness_control_c_sha256':sha(control.encode()),'coverage':coverage,'expected_calls':len(mapping),'direct_calls':direct,'packed_calls':packed,'phases':{phase:sum(x['phase']==phase for x in mapping) for phase in ('timed','checksum','raw')},'linux_runtime':'NOT_RUN'},indent=2))

if __name__=='__main__':
    ap=argparse.ArgumentParser(description=__doc__);ap.add_argument('--selftest',action='store_true',required=True);ap.parse_args();selftest()
