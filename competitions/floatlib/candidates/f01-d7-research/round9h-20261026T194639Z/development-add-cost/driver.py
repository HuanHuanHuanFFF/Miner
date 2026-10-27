"""NOT_RUN trusted diagnostic functions; reuse Lake/g and R13 parser, no stages.

Parent must invoke in a dedicated diagnostic budget, never a score/adoption path.
No commands execute on import. Local verification calls preparation/pure summaries only.
"""
from pathlib import Path
import hashlib
import importlib.util
import json
import re
import shlex
import shutil
import sys
import time

sys.dont_write_bytecode = True

HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p / 'competitions/floatlib/scripts/estimate_champion_time.py').is_file())
R13 = HERE / 'legacy-whole-parser.py'
CAPTURE = HERE / 'bounded-capture-source.py'
PINS = {R13: '8726e1e5debcfc335a11585d2a432a74ef379727fa393c686abecf631fedd23e',
        CAPTURE: '926e0e72695156c79c56612a20fe6ed015a2ea4a8373d8d9fc9ac5f37c12d90d'}
SOURCE = 'd3c550da05a3e91b5b037bed77623545dbe72af385d826ebc73236d2ed7ec2b5'
GATE = '1eb74ef7479b0023c721e776cc5e4073af21c6662b4afffcf16a48a124d27194'
PLANS = [(1927003, 'b3d19580bc8d5c6674edcbfa4eda0c405d0f83bcef9064af827243503e5bb6a9'),
         (1927005, '8c385cab83fdb6243420ed4dc80c8dbf9e843564e249602bccab16288c8eec90')]
def sha(path):
    value=hashlib.sha256()
    with Path(path).open('rb') as stream:
        for block in iter(lambda:stream.read(1024*1024),b''):value.update(block)
    return value.hexdigest()
encode = lambda x: (json.dumps(x, ensure_ascii=False, indent=2)+'\n').encode()


def require(ok, message):
    if not ok: raise RuntimeError(message)


class Budget:
    """All phases share an absolute deadline starting before original statement."""
    def __init__(self, deadline, clock=time.monotonic):
        self.deadline, self.clock, self.events = deadline, clock, []

    def cap(self, label, ceiling, reserve=20, phase_deadline=None):
        remaining = min(self.deadline-reserve, phase_deadline or self.deadline)-self.clock()
        cap = min(ceiling, remaining)
        self.events.append({'stage':label,'cap_seconds':max(0,cap),'overall_remaining_seconds':self.deadline-self.clock(),'reserve_seconds':reserve})
        require(cap >= 1, 'Overall remaining budget exhausted before '+label)
        return cap


def trace_command(path):
    trace=json.loads(Path(path).read_bytes())
    require(trace.get('synthetic') is False,'Synthetic or missing build trace')
    commands=[x['message'][3:] for x in trace.get('log',[]) if x.get('message','').startswith('.> ')]
    require(len(commands)==1,'Ambiguous compiler/link trace')
    return shlex.split(commands[0])


def normalize(argv):
    return [re.sub(r'(?<=/)(?:MainFull|R19AddCostMain)(?=\.)','<MAIN>',
                   re.sub(r'(?<=/)(?:benchFull|r19AddCost)(?=\.|$)','<BIN>',x)) for x in argv]


def compare_flags(g,out):
    pairs={
        'compile':(g.BUILD/'ir/MainFull.c.o.export.trace',g.BUILD/'ir/R19AddCostMain.c.o.export.trace'),
        'link':(g.BUILD/'bin/benchFull.trace',g.BUILD/'bin/r19AddCost.trace'),
        'link_response':(g.BUILD/'bin/benchFull.rsp',g.BUILD/'bin/r19AddCost.rsp')}
    result={}
    for kind,paths in pairs.items():
        values=[]
        for role,path in zip(('original','new'),paths):
            p=visible(g,path); raw=p.read_bytes();(out/(role+'-'+kind+'.raw')).write_bytes(raw)
            values.append(shlex.split(raw.decode()) if kind=='link_response' else trace_command(p))
        result[kind]={'original_argv':values[0],'new_argv':values[1],'equal_after_only_root_target_path_mapping':normalize(values[0])==normalize(values[1])}
    (out/'flags-and-link.json').write_bytes(encode(result))
    require(all(v['equal_after_only_root_target_path_mapping'] for v in result.values()),'Actual flags/link inputs differ; no timing')
    return result


def load_module(path, name):
    require(sha(path) == PINS[path], 'Reused helper changed')
    spec = importlib.util.spec_from_file_location(name, path)
    value = importlib.util.module_from_spec(spec); spec.loader.exec_module(value)
    return value


def visible(g, logical):
    upper = g.LAYER/'upper'/Path(logical).relative_to(g.BUILD)
    return upper if upper.is_file() else Path(logical)


def official_sources(g):
    paths = [g.HERE/'gate.py', g.HERE/'benchmark_suite.py', g.HERE/'suites/public-v2.json',
             g.LIB/'lakefile.lean', g.LIB/'lake-manifest.json', g.LIB/'lean-toolchain']
    paths += list((g.LIB/'contract').rglob('*.lean')) + list((g.LIB/'bench').rglob('*.lean'))
    paths += [p for p in (g.HERE/'pins.json', g.HERE/'pinned/full') if p.is_file()]
    return {str(p): sha(p) for p in paths}


def original_build(g):
    paths = [g.BUILD/'bin/benchFull', g.BUILD/'ir/MainFull.c', g.BUILD/'ir/Submission.c']
    paths += [g.BUILD/'ir'/n for n in ('MainFull.c.o.export', 'Submission.c.o.export')]
    paths += [g.BUILD/'bin'/('benchFull'+s) for s in ('.trace','.rsp')]
    paths += [g.BUILD/'ir/MainFull.c.o.export.trace']
    for arg in shlex.split(visible(g,g.BUILD/'bin/benchFull.rsp').read_text()):
        p=Path(arg)
        if p.is_absolute() and p.is_relative_to(g.BUILD) and p.suffix in ('.export','.noexport','.o','.a'):paths.append(p)
    return {str(p): sha(visible(g,p)) for p in paths}


def prepare(g, kernel, out):
    """Only writes two owned work files and metadata; no build or run command."""
    require(getattr(g, '_SANDBOX', False), 'Original isolated build layer required')
    require(sha(g.HERE/'gate.py')==GATE,'Pinned4b7 gate identity differs')
    require(g.foreign(g.LAYER/'upper')==[],'Original statement layer already foreign')
    require(not any(n == 'score' for n, _ in g.STAGES), 'Diagnostic-only context required')
    require(sha(kernel) == sha(g.WORK) == SOURCE, 'Exact compiledD3c550da runtime required')
    config = (g.LIB/'lakefile.lean').read_bytes()
    text = config.decode()
    match = re.search(r'^lean_exe benchFull where\s*\n((?:[ \t]+[^\n]*\n|\n)*)', text, re.M)
    require(match is not None, 'Unknown current benchFull configuration')
    fields = [x.strip() for x in match.group(1).splitlines() if x.strip() and not x.lstrip().startswith('--')]
    require(set(fields) == {'srcDir := "bench"', 'root := `MainFull'} and len(fields) == 2,
            'benchFull target-specific options require independent review')
    require('r19AddCost' not in text, 'Owned target collision')
    template = (HERE/'R19AddCostMain.lean').read_bytes()
    require(b'diagnosticEntry' not in template and b'@[noinline] def r19CostGuardedAdd' in template
            and b'@[noinline] def r19CostControlAdd' in template
            and template.count(b'Submission.R19GRS32Add.guardedAdd Submission.add x y') == 1
            and template.count(b'pure r19CostControlAdd') == 1 and template.count(b'pure r19CostGuardedAdd') == 1
            and template.count(b'Bench.Suite.run add Submission.mul Submission.sum Submission.bmm') == 1
            and template.count(b'Bench.Suite.run ') == 1 and b'guardedMul' not in template, 'Wrong ADD function alias or callback composition')
    out = Path(out); out.mkdir(parents=True, exist_ok=True)
    source = g.WORK.parent/'R19AddCostMain.lean'
    alternate = g.WORK.parent/'R19AddCostLake.lean'
    require(not source.exists() and not alternate.exists(), 'Fresh owned files required')
    require(not visible(g, g.BUILD/'bin/r19AddCost').exists(), 'Fresh owned executable target required')
    owned_config = config + b'\n\nlean_exe r19AddCost where\n  srcDir := "work"\n  root := `R19AddCostMain\n'
    before = official_sources(g); original = original_build(g)
    created=[]
    try:
        for path, raw in ((source, template), (alternate, owned_config)):
            with path.open('xb') as stream: stream.write(raw)
            created.append((path,hashlib.sha256(raw).hexdigest()))
    except Exception:
        for path,expected in created:
            if path.is_file() and sha(path)==expected:path.unlink()
        raise
    (out/'caller.lean').write_bytes(template);(out/'alternate-lakefile.lean').write_bytes(owned_config)
    result = {'official_before': before, 'original_build_before': original,
        'owned_files': {str(source): sha(source), str(alternate): sha(alternate)},
        'original_lakefile_sha256': sha(g.LIB/'lakefile.lean'), 'alternate_config_original_prefix_bytes': len(config),
        'build_argv': [g.LAKE, '-f', 'work/R19AddCostLake.lean', 'build', 'r19AddCost'],
        'build_cap_seconds': min(180, g._BUILD_TIMEOUT), 'logical_binary': str(g.BUILD/'bin/r19AddCost'),
        'scope': 'New target via separate config. Original gate/contracts/bench/pins/lakefile untouched. Not admissible gate artifacts.'}
    (out/'prepare.json').write_bytes(encode(result))
    return result


def summarize(plan, control_rows, guarded_rows):
    result = {}
    for op in ('add','mul','sum','bmm','whole'):
        names = [c['name'] for c in plan['cases'] if c['timed'] and (op == 'whole' or c['kernel'] == op)]
        c = sum(control_rows[n]['best_ns'] for n in names)
        t = sum(guarded_rows[n]['best_ns'] for n in names)
        require(c > 0, 'Missing positive control cost')
        result[op] = {'cases':len(names),'control_ns_sum':c,'guarded_ns_sum':t,'guarded_over_control':t/c}
    return result


def build_and_measure(g, prepared, out, absolute_deadline):
    """Remote-only draft for parent: one new target,8 exposed-plan processes.

    No STAGES patching or official score call. Needs dedicated outer allowance
    beyond the individual120s diagnostic: build<=180s, runs<=300s, capture<=32s.
    """
    out = Path(out); parser = load_module(R13, 'r19_add_reused_R13_rows');budget=Budget(absolute_deadline)
    record = {'complete':False,'diagnostic_only':True, 'full_gate':False, 'public_correctness':'UNKNOWN', 'original25_round_score':'NOT_RUN',
        'source_sha256':SOURCE, 'changed_operation':'ADD', 'runs':[], 'caller_C_ASM_review':'PENDING_REQUIRED_BEFORE_COST_DECISION'}
    record['execution_config']={'requested_benchmark_cpu':getattr(g,'_BENCH_CPU',None),
        'benchmark_memory_mb':g._BENCH_MEMORY_MB,'build_memory_mb':g._BUILD_MEMORY_MB,
        'original_entry_budget_remaining_before':g._budget.left,'inner':3,'pairs':500000,'processes':8,'platform':sys.platform,
        'budget':'Single580s absolute from stage registration;180/300/32 are phase ceilings,20s receipt reserve; original g.own budget also applies'}
    if Path('/proc/cpuinfo').is_file(): (out/'cpuinfo.txt').write_bytes(Path('/proc/cpuinfo').read_bytes())
    def persist():
        record['budget_events']=budget.events;record['remaining_seconds']=absolute_deadline-time.monotonic()
        (out/'result.json').write_bytes(encode(record))
    persist()
    try:
        require(sha(g.WORK)==SOURCE and all(sha(p)==h for p,h in prepared['owned_files'].items()), 'Prepared sources changed')
        require(official_sources(g) == prepared['official_before'], 'Official source changed before build')
        start = time.monotonic()
        code, log = g.own(prepared['build_argv'], budget.cap('build',prepared['build_cap_seconds'],52), build='write')
        (out/'build.log').write_bytes(log.encode()); record.update(build_exit_code=code, build_seconds=time.monotonic()-start)
        persist()
        require(code == 0, 'New target did not build; no timing')
        require(original_build(g) == prepared['original_build_before'], 'Original build identity changed; stop')
        foreign=g.foreign(g.LAYER/'upper');record['original_foreign_after_new_target']=foreign
        record['new_target_is_original_gate_admissible']=False
        require(all(Path(n).name.split('.')[0] in ('R19AddCostMain','r19AddCost') for n in foreign),'Unexpected dependency rebuild/foreign artifact')
        rebuilt=re.findall(r'(?:Built|Building)\s+([^\s(]+)',log);record['observed_build_targets']=rebuilt
        require(all(n.split(':')[0] in ('R19AddCostMain','r19AddCost') for n in rebuilt),'Non-owned dependency rebuild; no timing')
        record['flags_and_link']=compare_flags(g,out)
        for name in ('MainFull.c','Submission.c'):
            (out/('original-statement-'+name)).write_bytes(visible(g,g.BUILD/'ir'/name).read_bytes())
        binary = Path(prepared['logical_binary']); root = 'R19AddCostMain'
        products = [visible(g,binary), g.LAYER/'upper/ir'/f'{root}.c']
        products += sorted((g.LAYER/'upper/ir').glob(root+'*.trace'))
        objects = [p for p in (g.LAYER/'upper/ir').glob(root+'*.o.*') if p.is_file() and p.read_bytes().startswith(b'\x7fELF')]
        require(products[0].is_file() and products[1].is_file() and objects, 'Own C/object/binary absent')
        main_c = products[1].read_bytes(); require(b'BENCH_VARIANT' in main_c, 'Wrong Main module')
        require(b'R19GRS32Add_diagnosticEntry' not in main_c, 'Noinline diagnosticEntry reached from harness')
        (out/'actual-new-main.c').write_bytes(main_c)
        closure_lines=[line for line in main_c.decode().splitlines() if 'static const lean_closure_object' in line]
        closure_check={}
        for name in ('r19CostControlAdd','r19CostGuardedAdd'):
            hits=[line for line in closure_lines if re.search(r'\.m_fun\s*=\s*\(void\*\)\(?[^,]*'+name+r'___boxed\)?\s*,',line)]
            closure_check[name]={'lines':hits,'static_arity2_zero_captures':len(hits)==1 and bool(re.search(r'\.m_arity\s*=\s*2\s*,',hits[0])) and bool(re.search(r'\.m_num_fixed\s*=\s*0\s*[,}]',hits[0]))}
        (out/'caller-closure-check.json').write_bytes(encode(closure_check))
        require(all(v['static_arity2_zero_captures'] for v in closure_check.values()),'ADD wrapper is not two static arity2 zero-capture closures; no timing')
        link_trace = visible(g, binary.with_suffix('.trace'))
        if link_trace.is_file(): products.append(link_trace)
        products.append(visible(g,binary.with_suffix('.rsp')))
        identities = {str(p): sha(p) for p in products + objects}
        for i,p in enumerate(products[1:]): (out/f'build-product-{i}-{p.name}').write_bytes(p.read_bytes())
        record['build_identities'] = identities
        persist()
        cpu = getattr(g,'_BENCH_CPU','');require(not cpu or shutil.which('taskset'),'Configured CPU affinity unavailable')
        argv = (['taskset','-c',str(cpu)] if cpu else [])+[str(binary)]
        deadline = min(time.monotonic()+300,absolute_deadline-52); pairs=[]
        for seed, expected in PLANS:
            path = HERE/f'plan-{seed}.json'; require(sha(path)==expected, 'Exposed plan changed')
            plan=json.loads(path.read_bytes());require(sum(bool(c['timed']) for c in plan['cases'])==152,'Timed row count differs'); results=[]
            (out/path.name).write_bytes(path.read_bytes())
            for number,variant in enumerate(('control','guarded','guarded','control')):
                cap=budget.cap(f'measure-{seed}-{number}',120,52,deadline)
                env={'BENCH_PLAN':json.dumps(plan,separators=(',',':')),'BENCH_SEED':str(seed),'BENCH_PAIRS':'500000',
                     'BENCH_INNER':'3','BENCH_VARIANT':variant,'LEAN_ABORT_ON_PANIC':'1'}
                begun=time.monotonic();code,log=g.own(argv,cap,build='read',env_extra=env,memory_mb=g._BENCH_MEMORY_MB)
                name=f'{seed}-{number}-{variant}';(out/(name+'.log')).write_bytes(log.encode())
                record['runs'].append({'seed':seed,'order':number,'variant':variant,'exit_code':code,'seconds':time.monotonic()-begun,
                    'environment':env,'argv':argv,'effective_cap_seconds':cap,'log_sha256':hashlib.sha256(log.encode()).hexdigest()})
                (out/'runs.json').write_bytes(encode(record['runs']))
                persist()
                require(code==0,'Process failed; raw log retained')
                rows=parser.bench_rows(log,plan);(out/(name+'-rows.json')).write_bytes(encode(rows));results.append(rows)
                record['runs'][-1].update(rows=len(rows),timed_rows=sum(r['timed'] for r in rows.values()))
                persist()
            for rows in results[1:]: parser.verify_same_seed(results[0],rows)
            pairs.append({'seed':seed,'same_seed_checksums_match':True,
                'block_0':summarize(plan,results[0],results[1]),'block_1':summarize(plan,results[3],results[2])})
            record['pairs']=pairs;persist()
        require(all(sha(p)==h for p,h in identities.items()),'Measured artifacts changed')
        require(sha(g.WORK)==SOURCE and all(sha(p)==h for p,h in prepared['owned_files'].items()), 'Prepared sources changed during timing')
        require(official_sources(g)==prepared['official_before'] and original_build(g)==prepared['original_build_before'],'Original files/build changed')
        record.update(measurement_complete=True,pairs=pairs,official_originals_unchanged=True,
            scope='Full156-case diagnostic composition,152 timed cases; not original25-round score/adoption. MUL/SUM/BMM remain old B2 callbacks; future caller/transitive shape may differ.')
        capture=load_module(CAPTURE,'r19_add_reused_bounded_capture'); tools=[];tool_end=min(time.monotonic()+32,absolute_deadline-20)
        for i,obj in enumerate(objects[:2]):
            tools.append(capture._bounded_tool(['nm','-S','--defined-only',str(obj)],out/f'own-object-{i}-nm.txt',budget.cap('post-nm',8,20,tool_end),2*1024*1024))
            record['post_timing_existing_capture_tools']=tools;persist()
            tools.append(capture._bounded_tool(['objdump','-dr','--no-show-raw-insn','-Mintel',str(obj)],out/f'own-object-{i}-asm.txt',budget.cap('post-asm',8,20,tool_end),8*1024*1024))
            record['post_timing_existing_capture_tools']=tools;persist()
        record['post_timing_existing_capture_tools']=tools
        require(all(t.get('ok') for t in tools),'Post-timing C/ASM evidence incomplete')
        record['complete']=True
        record['flags_and_link_review']='Exact actual compile/link/rsp comparison passed after only root/target path mapping; caller C/ASM semantic review remains required.'
    except Exception as error:
        record.update(complete=False,error_type=type(error).__name__,error=str(error));raise
    finally:
        record['budget_events']=budget.events;record['remaining_seconds']=absolute_deadline-time.monotonic()
        record['original_entry_budget_remaining_after']=g._budget.left
        (out/'result.json').write_bytes(encode(record))


def cleanup_owned(prepared):
    for name,expected in prepared['owned_files'].items():
        path=Path(name);require(sha(path)==expected,'Owned file changed; preserve it');path.unlink()
