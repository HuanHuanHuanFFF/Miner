"""Uninstrumented exactDF whole calls on three already exposed input seeds."""
from pathlib import Path
import hashlib,json,os,platform,shutil,subprocess,time,traceback

HEAD='4b7e83841cc0c32c6529f533923c73d33b5ecf97'
SOURCE='df5c61a0ca24a8ef18c0c42d83bdd23466872d3fe8f39dd912e9c347b27fb172'
INITIAL_SEED=1224016
SEEDS=(1224011,1224091,1224092)
PAIRS=500000
INNER=3
PROCESSES=2
MAX_SECONDS=300
PREFIX='profile-whole-multi-'


def require(ok,message):
    if not ok:raise RuntimeError(message)


def sha(raw):return hashlib.sha256(raw).hexdigest()


def file_sha(path):
    digest=hashlib.sha256()
    with Path(path).open('rb')as stream:
        for block in iter(lambda:stream.read(1024*1024),b''):digest.update(block)
    return digest.hexdigest()


def bench_rows(log,plan):
    expected={c['name']:c for c in plan['cases']};rows={}
    require(len(expected)==len(plan['cases'])==156,'plan must contain156 unique cases')
    for line in log.splitlines():
        p=line.split()
        if len(p)!=4 or p[1]not in ('true','false'):continue
        require(p[0]in expected and p[0]not in rows,'unknown/duplicate whole row')
        require(p[2].isdigit()and p[3].isdigit(),'invalid whole row')
        timed=p[1]=='true';require(timed==expected[p[0]]['timed'],'whole timed flag mismatch')
        ns=int(p[2]);require(ns>0 if timed else ns==0,'invalid whole timing')
        rows[p[0]]={'timed':timed,'best_ns':ns,'checksum':int(p[3])}
    require(set(rows)==set(expected),'whole156case coverage mismatch')
    require(not any(s in log for s in ('FL13 cat=','FC13 cat=')),'refusing instrumented executable')
    return rows


def verify_same_seed(first,second):
    require(set(first)==set(second),'same-seed coverage differs')
    require(all(first[name]['checksum']==second[name]['checksum']and first[name]['timed']==second[name]['timed']for name in first),
        'same-seed whole checksum differs')


def run(g,kernel,out,public_plan,seed):
    kernel,out=Path(kernel),Path(out);out.mkdir(parents=True,exist_ok=True)
    require(not(out/(PREFIX+'result.json')).exists(),'fresh output required')
    started=time.monotonic();deadline=started+MAX_SECONDS;executions=[]
    def save(name,raw):
        require(not raw.startswith(b'\x7fELF'),'binary export prohibited')
        with(out/(PREFIX+name)).open('xb')as stream:stream.write(raw)
    def save_json(name,data):save(name,(json.dumps(data,ensure_ascii=False,indent=2)+'\n').encode())
    try:
        require(getattr(g,'_SANDBOX',False),'original candidate layer required')
        require(not any(name=='score'for name,_ in g.STAGES),'refusing score stage')
        require(seed==INITIAL_SEED and g._PAIRS==PAIRS,'initial context must remain exposed1224016/500000')
        require(sha(kernel.read_bytes())==SOURCE==sha(g.WORK.read_bytes()),'exactDF mismatch')
        require(subprocess.check_output(['git','rev-parse','HEAD'],cwd=g.HERE,text=True).strip()==HEAD,'official version differs')
        require(Path(g.benchmark_suite.__file__).resolve()==(g.HERE/'benchmark_suite.py').resolve(),'wrong official generator')
        suite=g.benchmark_suite.load(g.HERE/'suites/public-v2.json')
        require(public_plan==g.benchmark_suite.make_plan(suite,INITIAL_SEED,PAIRS),'initial official plan differs')
        upper=g.LAYER/'upper';bench=g.BUILD/'bin/benchFull';obj=g.BUILD/'ir/Submission.c.o.export'
        def visible(logical):
            p=upper/Path(logical).relative_to(g.BUILD)
            return p if p.is_file()else Path(logical)
        def identity(logical):
            p=visible(logical);require(p.is_file(),'original build product unavailable')
            return {'logical':str(logical),'bytes':p.stat().st_size,'sha256':file_sha(p),'binary_exported':False}
        source_c=upper/'ir/Submission.c';require(source_c.is_file(),'actualDF original C unavailable')
        c_raw=source_c.read_bytes();require(b'pr13_'not in c_raw and b'FC13 cat='not in c_raw,'generated C already instrumented')
        before={'object':identity(obj),'binary':identity(bench),'source_c_sha256':sha(c_raw)}
        save('Kernel.lean',kernel.read_bytes());save('original-Submission.c',c_raw);save_json('initial-context-plan.json',public_plan)
        immutable_paths=[g.HERE/'gate.py',g.HERE/'benchmark_suite.py',g.HERE/'suites/public-v2.json',
            g.LIB/'bench/MainFull.lean',g.LIB/'bench/BenchSuite.lean',*sorted((g.LIB/'contract').rglob('*.lean'))]
        immutable={str(p.relative_to(g.HERE)):file_sha(p)for p in immutable_paths}
        cpu_config={'platform':platform.platform(),'machine':platform.machine(),'processor':platform.processor(),
            'parent_affinity':sorted(os.sched_getaffinity(0))if hasattr(os,'sched_getaffinity')else None,
            'requested_benchmark_cpu':getattr(g,'_BENCH_CPU',None),'benchmark_memory_mb':g._BENCH_MEMORY_MB,
            'inner':INNER,'pairs':PAIRS,'processes_per_seed':PROCESSES,'actual_seeds':list(SEEDS),'module_seconds':MAX_SECONDS,
            'initial_context_seed':seed,'no_instrumentation':True,'no_relink':True}
        if Path('/proc/cpuinfo').is_file():save('cpuinfo.txt',Path('/proc/cpuinfo').read_bytes())
        if Path('/proc/version').is_file():save('proc-version.txt',Path('/proc/version').read_bytes())
        save_json('config.json',cpu_config)
        cpu=getattr(g,'_BENCH_CPU','');argv=(['taskset','-c',str(cpu)]if cpu and shutil.which('taskset')else[])+[str(bench)]
        seeds=[]
        for actual_seed in SEEDS:
            plan=g.benchmark_suite.make_plan(suite,actual_seed,PAIRS)
            require(len(plan['cases'])==156 and len({c['name']for c in plan['cases']})==156,'official plan incomplete')
            save_json(f'seed-{actual_seed}-plan.json',plan);compact=json.dumps(plan,separators=(',',':'))
            env={'BENCH_PLAN':compact,'BENCH_SEED':str(actual_seed),'BENCH_PAIRS':str(PAIRS),
                'BENCH_INNER':str(INNER),'LEAN_ABORT_ON_PANIC':'1'}
            processes=[]
            for process in range(PROCESSES):
                remain=deadline-time.monotonic();require(remain>0,'300second whole diagnostic exhausted')
                t=time.monotonic();code,log=g.run(argv,min(120,remain),build='read',env_extra=env,memory_mb=g._BENCH_MEMORY_MB)
                name=f'seed-{actual_seed}-process-{process}';save(name+'.log',log.encode())
                execution={'seed':actual_seed,'process':process,'exit_code':code,'seconds':time.monotonic()-t,
                    'argv':argv,'environment':env,'log_sha256':sha(log.encode()),'name':name}
                executions.append(execution);save_json('executions.json.part-'+str(len(executions)),executions)
                require(code==0,'whole process failed; returned log preserved')
                rows=bench_rows(log,plan);save_json(name+'-rows.json',rows)
                processes.append({'process':process,'rows':rows,'log_sha256':sha(log.encode())})
            verify_same_seed(processes[0]['rows'],processes[1]['rows'])
            seeds.append({'seed':actual_seed,'plan':plan,'plan_compact_sha256':sha(compact.encode()),
                'processes':processes,'same_seed_checksums_match':True,'cases':156})
            save_json(f'seed-{actual_seed}-result.json',seeds[-1])
        after={'object':identity(obj),'binary':identity(bench),'source_c_sha256':sha(source_c.read_bytes())}
        require(before==after,'original source/object/binary changed during whole calls')
        require(all(file_sha(g.HERE/name)==value for name,value in immutable.items()),'official source changed')
        require(sha(g.WORK.read_bytes())==SOURCE,'Kernel work changed')
        result={'diagnostic_only':True,'full_gate':False,'complete':True,'kernel_sha256':SOURCE,'official_commit':HEAD,
            'initial_context_seed':seed,'actual_seeds':list(SEEDS),'pairs':PAIRS,'inner':INNER,'processes_per_seed':PROCESSES,
            'seeds':seeds,'executions':executions,'config':cpu_config,'build_identities':{'before':before,'after':after},
            'official_source_hashes_unchanged':immutable,'module_sha256':file_sha(Path(__file__)),
            'elapsed_seconds':time.monotonic()-started,'measurement':'Six complete original uninstrumented benchFull processes on one compiled exactDF binary. Each whole row is fastest of3 sweeps after checksum/warmup, with official caller/cleanup.',
            'checksum_scope':'Only compare two processes of the SAME seed; different inputs need not have the same checksums.',
            'limits':'Already exposed inputs only. Two processes on one runner do not establish independent performance confirmation, official score or champion multiplier.',
            'artifacts':'Original plans/source/logs/rows, CPU/config and binary/object hashes; no ELF/object bytes, no C timers, no relink or score.'}
        save_json('result.json',result);return result
    except Exception as exc:
        save_json('error.json',{'diagnostic_only':True,'complete':False,'error':str(exc),'traceback':traceback.format_exc(),'executions':executions})
        raise
