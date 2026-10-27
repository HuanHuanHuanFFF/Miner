"""NOT_RUN trusted diagnostic functions; reuse Lake/g and R13 parser, no stages.

Parent must invoke in a dedicated diagnostic budget, never a score/adoption path.
No commands execute on import. Local verification calls preparation/pure summaries only.
"""
from pathlib import Path
import hashlib
import importlib.util
import json
import re
import shutil
import sys
import time

sys.dont_write_bytecode = True

HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p / 'competitions/floatlib/scripts/estimate_champion_time.py').is_file())
R13 = ROOT / 'competitions/floatlib/candidates/f01-d7-research/round3h-20261024T112622Z/profile-whole-multi-current.py'
CAPTURE = ROOT / 'competitions/floatlib/candidates/f01-d7-research/capture-codegen.py'
PINS = {R13: '8726e1e5debcfc335a11585d2a432a74ef379727fa393c686abecf631fedd23e',
        CAPTURE: '926e0e72695156c79c56612a20fe6ed015a2ea4a8373d8d9fc9ac5f37c12d90d'}
SOURCE = '74899988939a056a40675aefe8c63f2f9db1c7b4728f3d496bf140ede6ad85dc'
PLANS = [(1927003, 'b3d19580bc8d5c6674edcbfa4eda0c405d0f83bcef9064af827243503e5bb6a9'),
         (1927005, '8c385cab83fdb6243420ed4dc80c8dbf9e843564e249602bccab16288c8eec90')]
sha = lambda p: hashlib.sha256(Path(p).read_bytes()).hexdigest()
encode = lambda x: (json.dumps(x, ensure_ascii=False, indent=2)+'\n').encode()


def require(ok, message):
    if not ok: raise RuntimeError(message)


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
    return {str(p): sha(p) for p in paths}


def original_build(g):
    paths = [g.BUILD/'bin/benchFull', g.BUILD/'ir/MainFull.c', g.BUILD/'ir/Submission.c']
    paths += [g.BUILD/'ir'/n for n in ('MainFull.c.o.export', 'Submission.c.o.export')]
    return {str(p): sha(visible(g,p)) for p in paths}


def prepare(g, kernel, out):
    """Only writes two owned work files and metadata; no build or run command."""
    require(getattr(g, '_SANDBOX', False), 'Original isolated build layer required')
    require(not any(n == 'score' for n, _ in g.STAGES), 'Diagnostic-only context required')
    require(sha(kernel) == sha(g.WORK) == SOURCE, 'Exact compiled748999 runtime required')
    config = (g.LIB/'lakefile.lean').read_bytes()
    text = config.decode()
    match = re.search(r'^lean_exe benchFull where\s*\n((?:[ \t]+[^\n]*\n|\n)*)', text, re.M)
    require(match is not None, 'Unknown current benchFull configuration')
    fields = [x.strip() for x in match.group(1).splitlines() if x.strip() and not x.lstrip().startswith('--')]
    require(set(fields) == {'srcDir := "bench"', 'root := `MainFull'} and len(fields) == 2,
            'benchFull target-specific options require independent review')
    require('r19RuntimeCost' not in text, 'Owned target collision')
    template = (HERE/'R19RuntimeCostMain.lean').read_bytes()
    require(b'diagnosticEntry' not in template and b'@[inline]' in template and b'guardedMul Submission.mul' in template, 'Wrong guarded alias')
    out = Path(out); out.mkdir(parents=True, exist_ok=True)
    source = g.WORK.parent/'R19RuntimeCostMain.lean'
    alternate = g.WORK.parent/'R19RuntimeCostLake.lean'
    require(not source.exists() and not alternate.exists(), 'Fresh owned files required')
    require(not visible(g, g.BUILD/'bin/r19RuntimeCost').exists(), 'Fresh owned executable target required')
    owned_config = config + b'\n\nlean_exe r19RuntimeCost where\n  srcDir := "work"\n  root := `R19RuntimeCostMain\n'
    before = official_sources(g); original = original_build(g)
    for path, raw in ((source, template), (alternate, owned_config)):
        with path.open('xb') as stream: stream.write(raw)
    result = {'official_before': before, 'original_build_before': original,
        'owned_files': {str(source): sha(source), str(alternate): sha(alternate)},
        'original_lakefile_sha256': sha(g.LIB/'lakefile.lean'), 'alternate_config_original_prefix_bytes': len(config),
        'build_argv': [g.LAKE, '-f', 'work/R19RuntimeCostLake.lean', 'build', 'r19RuntimeCost'],
        'build_cap_seconds': min(180, g._BUILD_TIMEOUT), 'logical_binary': str(g.BUILD/'bin/r19RuntimeCost'),
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


def build_and_measure(g, prepared, out):
    """Remote-only draft for parent: one new target,8 exposed-plan processes.

    No STAGES patching or official score call. Needs dedicated outer allowance
    beyond the individual120s diagnostic: build<=180s, runs<=300s, capture<=32s.
    """
    out = Path(out); parser = load_module(R13, 'r19_reused_R13_rows')
    record = {'diagnostic_only':True, 'full_gate':False, 'public_correctness':'UNKNOWN',
        'source_sha256':SOURCE, 'runs':[], 'caller_C_ASM_review':'PENDING_REQUIRED_BEFORE_COST_DECISION'}
    record['execution_config']={'requested_benchmark_cpu':getattr(g,'_BENCH_CPU',None),
        'benchmark_memory_mb':g._BENCH_MEMORY_MB,'inner':3,'pairs':500000,'processes':8,'platform':sys.platform}
    if Path('/proc/cpuinfo').is_file(): (out/'cpuinfo.txt').write_bytes(Path('/proc/cpuinfo').read_bytes())
    try:
        require(sha(g.WORK)==SOURCE and all(sha(p)==h for p,h in prepared['owned_files'].items()), 'Prepared sources changed')
        require(official_sources(g) == prepared['official_before'], 'Official source changed before build')
        start = time.monotonic()
        code, log = g.own(prepared['build_argv'], prepared['build_cap_seconds'], build='write')
        (out/'build.log').write_bytes(log.encode()); record.update(build_exit_code=code, build_seconds=time.monotonic()-start)
        require(code == 0, 'New target did not build; no timing')
        require(original_build(g) == prepared['original_build_before'], 'Original build identity changed; stop')
        binary = Path(prepared['logical_binary']); root = 'R19RuntimeCostMain'
        products = [visible(g,binary), g.LAYER/'upper/ir'/f'{root}.c']
        products += sorted((g.LAYER/'upper/ir').glob(root+'*.trace'))
        objects = [p for p in (g.LAYER/'upper/ir').glob(root+'*.o.*') if p.is_file() and p.read_bytes().startswith(b'\x7fELF')]
        require(products[0].is_file() and products[1].is_file() and objects, 'Own C/object/binary absent')
        main_c = products[1].read_bytes(); require(b'BENCH_VARIANT' in main_c, 'Wrong Main module')
        require(b'R19DirectBias_diagnosticEntry' not in main_c, 'Noinline diagnosticEntry reached from harness')
        link_trace = visible(g, binary.with_suffix('.trace'))
        if link_trace.is_file(): products.append(link_trace)
        identities = {str(p): sha(p) for p in products + objects}
        for i,p in enumerate(products[1:]): (out/f'build-product-{i}-{p.name}').write_bytes(p.read_bytes())
        record['build_identities'] = identities
        cpu = getattr(g,'_BENCH_CPU',''); argv = (['taskset','-c',str(cpu)] if cpu and shutil.which('taskset') else [])+[str(binary)]
        deadline = time.monotonic()+300; pairs=[]
        for seed, expected in PLANS:
            path = HERE/f'plan-{seed}.json'; require(sha(path)==expected, 'Exposed plan changed')
            plan=json.loads(path.read_bytes()); results=[]
            for number,variant in enumerate(('control','guarded','guarded','control')):
                remaining=deadline-time.monotonic(); require(remaining>0,'Run budget exhausted')
                env={'BENCH_PLAN':json.dumps(plan,separators=(',',':')),'BENCH_SEED':str(seed),'BENCH_PAIRS':'500000',
                     'BENCH_INNER':'3','BENCH_VARIANT':variant,'LEAN_ABORT_ON_PANIC':'1'}
                begun=time.monotonic();code,log=g.run(argv,min(120,remaining),build='read',env_extra=env,memory_mb=g._BENCH_MEMORY_MB)
                name=f'{seed}-{number}-{variant}';(out/(name+'.log')).write_bytes(log.encode())
                record['runs'].append({'seed':seed,'order':number,'variant':variant,'exit_code':code,'seconds':time.monotonic()-begun,
                    'environment':env,'argv':argv,'log_sha256':hashlib.sha256(log.encode()).hexdigest()})
                (out/'runs.json').write_bytes(encode(record['runs']))
                require(code==0,'Process failed; raw log retained')
                rows=parser.bench_rows(log,plan);(out/(name+'-rows.json')).write_bytes(encode(rows));results.append(rows)
            for rows in results[1:]: parser.verify_same_seed(results[0],rows)
            pairs.append({'seed':seed,'same_seed_checksums_match':True,
                'block_0':summarize(plan,results[0],results[1]),'block_1':summarize(plan,results[3],results[2])})
        require(all(sha(p)==h for p,h in identities.items()),'Measured artifacts changed')
        require(sha(g.WORK)==SOURCE and all(sha(p)==h for p,h in prepared['owned_files'].items()), 'Prepared sources changed during timing')
        require(official_sources(g)==prepared['official_before'] and original_build(g)==prepared['original_build_before'],'Original files/build changed')
        record.update(complete=True,pairs=pairs,official_originals_unchanged=True,
            scope='Full156-case diagnostic composition,152 timed cases; not original25-round score/adoption. ADD/SUM/BMM remain old B2 callbacks; future caller/transitive shape may differ.')
        capture=load_module(CAPTURE,'r19_reused_bounded_capture'); tools=[]
        for i,obj in enumerate(objects[:2]):
            tools.append(capture._bounded_tool(['nm','-S','--defined-only',str(obj)],out/f'own-object-{i}-nm.txt',8,2*1024*1024))
            tools.append(capture._bounded_tool(['objdump','-dr','--no-show-raw-insn','-Mintel',str(obj)],out/f'own-object-{i}-asm.txt',8,8*1024*1024))
        record['post_timing_existing_capture_tools']=tools
        record['flags_and_link_review']='REQUIRED: compare actual new root compile/link traces against original MainFull facets; no compiler flags were passed by this module'
    except Exception as error:
        record.update(complete=False,error_type=type(error).__name__,error=str(error));raise
    finally:
        (out/'result.json').write_bytes(encode(record))


def cleanup_owned(prepared):
    for name,expected in prepared['owned_files'].items():
        path=Path(name);require(sha(path)==expected,'Owned file changed; preserve it');path.unlink()
