"""Draft diagnostic: original benchFull timers + separate route metadata. NOT_RUN."""
from pathlib import Path
import hashlib,importlib.util,json,os,shutil,subprocess,time

HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'competitions/floatlib/pins.json').is_file())
SOURCE='622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
sha=lambda p:hashlib.sha256(Path(p).read_bytes()).hexdigest()
def require(test,message):
    if not test:raise RuntimeError(message)

def shape_route(c,underflow):
    m,n,p=(c[k]for k in ('m','n','p'))
    if underflow:return 'UnderflowZero'
    if 2<=p<=8 and n>1 and m>=4:return 'B2'
    if m>=4 and n>1 and 0<p<=2:return 'B1'
    if (n<=4 and p>2)or p<=8:return 'DirectContinuous'
    if n<=4 or p<=2:return 'DirectSmall'
    if c['batch']*m*p==0 or n==0:return 'Reference'
    return 'Packed10'

def parse_labels(log,plan):
    expected={c['name']:c for c in plan['cases']if c['kernel']=='bmm'};rows={}
    for line in log.splitlines():
        if not line.startswith('ROUTE19 '):continue
        p=line.split();require(len(p)==5,'malformed route label')
        _,name,route,a,b=p
        require(name in expected and name not in rows,'unknown/duplicate route label')
        require(a in ('true','false')and b in ('true','false'),'invalid small flags')
        underflow=a==b=='true'
        require(route==shape_route(expected[name],underflow),'route guard mismatch')
        rows[name]=dict(route=route,aSmall=a=='true',bSmall=b=='true')
    require(set(rows)==set(expected),'missing route labels')
    return rows

def summarise(plan,processes,labels):
    timed=[c for c in plan['cases']if c['timed']]
    def one(times):
        whole=sum(times[c['name']]for c in timed)
        bmm=sum(times[c['name']]for c in timed if c['kernel']=='bmm')
        routes={}
        for c in timed:
            if c['kernel']!='bmm':continue
            tag=labels[c['name']]['route'];r=routes.setdefault(tag,dict(ns=0,cases=[]))
            r['ns']+=times[c['name']];r['cases'].append(c['name'])
        return dict(whole_ns=whole,BMM_ns=bmm,routes={tag:dict(**r,BMM_share=r['ns']/bmm,whole_share=r['ns']/whole)for tag,r in routes.items()})
    amounts=[{name:r['best_ns']for name,r in rows.items()}for rows in processes]
    average={name:sum(p[name]for p in amounts)/len(amounts)for name in amounts[0]}
    return dict(processes=[one(p)for p in amounts],mean_of_case_timers=one(average),
                units='Raw whole-case ns, not ns/work or process wall time; no MAC weighting')

def run(g,kernel,out,initial_plan,initial_seed):
    request=json.loads((HERE/'request.json').read_text());kernel=Path(kernel);out=Path(out)
    require([r['seed']for r in request['plans']]==[1927003,1927005]and request['inner']==3 and request['processes_per_plan']==2,'fixed exposed diagnostic request required')
    require(initial_seed==1927003 and initial_plan==json.loads((HERE/request['plans'][0]['path']).read_text()),'initial plan context differs')
    require(sha(kernel)==sha(g.WORK)==SOURCE==request['kernel_sha256'],'exact622d required')
    require(getattr(g,'_SANDBOX',False),'original candidate layer required')
    require(not any(name=='score'for name,_ in g.STAGES),'diagnostic must not replace an original score')
    require(subprocess.check_output(['git','rev-parse','HEAD'],cwd=g.HERE,text=True).strip()==request['official_commit'],'official commit changed')
    require(sha(g.HERE/'benchmark_suite.py')==request['generator_sha256'],'generator changed')
    require(sha(g.LIB/'bench/BenchSuite.lean')==request['BenchSuite_lean_sha256'],'BenchSuite changed')
    require(sha(g.HERE/'suites/public-v2.json')==request['suite_sha256'],'suite changed')
    # Reuse only the authenticated156-row parser from the old whole diagnostic.
    parser=ROOT/'competitions/floatlib/candidates/f01-d7-research/round3h-20261024T112622Z/profile-whole-multi-current.py'
    require(sha(parser)=='8726e1e5debcfc335a11585d2a432a74ef379727fa393c686abecf631fedd23e','old parser changed')
    spec=importlib.util.spec_from_file_location('r19_original_row_parser',parser)
    old=importlib.util.module_from_spec(spec);spec.loader.exec_module(old)
    out.mkdir(parents=True,exist_ok=False);deadline=time.monotonic()+request['maximum_module_seconds']
    def save(name,data):
        raw=data if isinstance(data,bytes)else(json.dumps(data,indent=2)+'\n').encode()
        (out/name).write_bytes(raw)
    def remaining(cap):
        value=min(cap,deadline-time.monotonic());require(value>0,'module deadline exhausted');return value
    save('request.json',request);save('driver-source.py',Path(__file__).read_bytes())
    upper=g.LAYER/'upper'
    def visible(logical):
        path=upper/Path(logical).relative_to(g.BUILD)
        return path if path.is_file()else Path(logical)
    logicals={name:g.BUILD/rel for name,rel in {'binary':'bin/benchFull','Submission_object':'ir/Submission.c.o.export',
              'MainFull_object':'ir/MainFull.c.o.export','BenchSuite_object':'ir/BenchSuite.c.o.export',
              'Submission_C':'ir/Submission.c','MainFull_C':'ir/MainFull.c','BenchSuite_C':'ir/BenchSuite.c'}.items()}
    def identity():
        return {name:dict(bytes=visible(path).stat().st_size,sha256=sha(visible(path)))for name,path in logicals.items()}
    before=identity()
    require(before['MainFull_C']['sha256']=='94f69ed19083e0fbb5d4b540d16d4575b82d4aac75779ce88043ef4f908bfecb','actual MainFull caller changed')
    for name in ('Submission_C','MainFull_C','BenchSuite_C'):save(name+'.c',visible(logicals[name]).read_bytes())
    c_bytes=visible(logicals['Submission_C']).read_bytes()
    require(not any(tag in c_bytes for tag in (b'FL13 cat=',b'FC13 cat=',b'pr13_')),'instrumented C refused')
    immutable=[g.HERE/'gate.py',g.HERE/'benchmark_suite.py',g.HERE/'suites/public-v2.json',
               g.LIB/'bench/BenchSuite.lean',g.LIB/'bench/MainFull.lean',*sorted((g.LIB/'contract').rglob('*.lean')),
               ROOT/'competitions/floatlib/pins.json']
    immutable_before={str(p):sha(p)for p in immutable};save('Kernel.lean',kernel.read_bytes())
    save('config.json',dict(request=request,CPU=getattr(g,'_BENCH_CPU',None),memory_mb=g._BENCH_MEMORY_MB,
                            requested_affinity=sorted(os.sched_getaffinity(0))if hasattr(os,'sched_getaffinity')else None))
    if Path('/proc/cpuinfo').is_file():save('cpuinfo.txt',Path('/proc/cpuinfo').read_bytes())
    cpu=getattr(g,'_BENCH_CPU','');argv=(['taskset','-c',str(cpu)]if cpu and shutil.which('taskset')else[])+[str(logicals['binary'])]
    helper=g.WORK.parent/'R19RouteLabels.lean';plan_file=g.WORK.parent/'R19RoutePlan.json'
    require(not helper.exists()and not plan_file.exists(),'temporary metadata files already exist')
    results=[]
    try:
        helper.write_bytes((HERE/'RouteLabels.lean').read_bytes());save('RouteLabels.lean',helper.read_bytes())
        for rec in request['plans']:
            require(rec['seed']in(1927003,1927005),'unseen plan refused')
            plan_path=HERE/rec['path'];require(sha(plan_path)==rec['sha256'],'seen plan changed')
            raw=plan_path.read_bytes();plan=json.loads(raw);require(len(plan['cases'])==156,'wrong plan size')
            plan_file.write_bytes(raw);save(f"seen-{rec['seed']}-plan.json",raw)
            code,log=g.own([g.LAKE,'env','lean','--run','work/R19RouteLabels.lean','work/R19RoutePlan.json'],remaining(90),build='read')
            save(f"labels-{rec['seed']}.log",log.encode());require(code==0,'metadata failed; no timing attribution')
            labels=parse_labels(log,plan);save(f"labels-{rec['seed']}.json",labels)
            env={'BENCH_PLAN':json.dumps(plan,separators=(',',':')),'BENCH_SEED':str(rec['seed']),
                 'BENCH_PAIRS':'500000','BENCH_INNER':'3','LEAN_ABORT_ON_PANIC':'1'}
            processes=[]
            for process in range(2):
                code,log=g.run(argv,remaining(90),build='read',env_extra=env,memory_mb=g._BENCH_MEMORY_MB)
                save(f"whole-{rec['seed']}-{process}.log",log.encode());require(code==0,'original binary failed')
                require('ROUTE19 'not in log,'metadata observer in timed binary')
                rows=old.bench_rows(log,plan);processes.append(rows);save(f"rows-{rec['seed']}-{process}.json",rows)
                require(identity()==before,'source/object/binary changed between processes')
            old.verify_same_seed(*processes)
            results.append(dict(seed=rec['seed'],plan_sha256=rec['sha256'],labels=labels,
                                complete_case_rows=processes,timing=summarise(plan,processes,labels)))
            save(f"result-{rec['seed']}.json",results[-1])
        require({str(p):sha(p)for p in immutable}==immutable_before,'official source/pins changed')
        require(identity()==before and sha(g.WORK)==SOURCE,'final build/source changed')
        record=dict(diagnostic_only=True,full_gate=False,complete=True,kernel_sha256=SOURCE,results=results,
                    build_identity_before=before,build_identity_after=identity(),official_hashes=immutable_before,
                    route_metadata='Separate process; exact official operands and original candidate underflow predicate',
                    timer='Unmodified original BenchSuite.measure; best of3 complete passes per raw row',
                    destruction='Actual BenchSuite C saved for lifetime audit; no complete-destruction claim before that review',
                    complete_boundary_audit='PENDING_SAVED_BENCHSUITE_C_LIFETIME_REVIEW',
                    score='No official score/adoption; two same-runner processes are diagnostic only')
        save('route-results.json',record);return record
    except Exception as error:
        save('error.json',dict(diagnostic_only=True,complete=False,error=str(error),partial_results=results));raise
    finally:
        if helper.exists():helper.unlink()
        if plan_file.exists():plan_file.unlink()
