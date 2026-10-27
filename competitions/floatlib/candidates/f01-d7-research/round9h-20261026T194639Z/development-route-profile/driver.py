"""Draft diagnostic: original benchFull timers + separate route metadata. NOT_RUN."""
from pathlib import Path
import hashlib,importlib.util,json,os,shutil,subprocess,time,traceback

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

def run(g,kernel,out,initial_plan,initial_seed,absolute_deadline=None):
    started=time.monotonic();request=json.loads((HERE/'request.json').read_text());kernel,out=Path(kernel),Path(out)
    require(request['maximum_module_seconds']==60,'exact60s request required')
    deadline=min(started+60,absolute_deadline if absolute_deadline is not None else started+60)
    out.mkdir(parents=True,exist_ok=False);results=[];current={};helper=None;plan_file=None;owned_helper=False;owned_plan=False
    def save(name,data):
        raw=data if isinstance(data,bytes)else(json.dumps(data,indent=2)+'\n').encode()
        (out/name).write_bytes(raw)
    def remaining(cap):
        value=min(cap,deadline-time.monotonic());require(value>0,'60s collection deadline exhausted');return value
    def progress(stage,**details):
        current.update(stage=stage,elapsed_seconds=time.monotonic()-started,**details)
        save('partial-progress.json',dict(current=current,completed_results=results))
    def call(label,action):
        progress(label)
        try:code,log=action()
        except subprocess.TimeoutExpired as error:
            raw=error.stdout if error.stdout is not None else error.output
            available=raw is not None
            raw=raw.encode()if isinstance(raw,str)else(raw or b'')
            save(label+'.log.partial',raw)
            save(label+'-timeout.json',dict(partial_output_available=available,timeout=error.timeout,elapsed_seconds=time.monotonic()-started))
            raise
        save(label+'.log',log.encode()if isinstance(log,str)else log)
        progress(label+'-returned',exit_code=code)
        return code,log
    save('request.json',request);save('driver-source.py',Path(__file__).read_bytes())
    try:
        require([p['seed']for p in request['plans']]==[1927003,1927005]and request['inner']==3 and request['processes_per_plan']==2,'fixed seen plans required')
        require(initial_seed==1927003 and initial_plan==json.loads((HERE/request['plans'][0]['path']).read_text()),'initial plan mismatch')
        require(sha(kernel)==sha(g.WORK)==SOURCE==request['kernel_sha256'],'exact622d required')
        require(getattr(g,'_SANDBOX',False),'original candidate layer required')
        require(not any(name=='score'for name,_ in g.STAGES),'score stage refused')
        require(subprocess.check_output(['git','rev-parse','HEAD'],cwd=g.HERE,text=True,timeout=remaining(5)).strip()==request['official_commit'],'official commit changed')
        require(sha(g.HERE/'benchmark_suite.py')==request['generator_sha256'],'generator changed')
        require(sha(g.LIB/'bench/BenchSuite.lean')==request['BenchSuite_lean_sha256'],'BenchSuite changed')
        require(sha(g.HERE/'suites/public-v2.json')==request['suite_sha256'],'suite changed')
        parser=HERE/request['parser']['path'];require(sha(parser)==request['parser']['sha256']=='8726e1e5debcfc335a11585d2a432a74ef379727fa393c686abecf631fedd23e','parser drift refused')
        spec=importlib.util.spec_from_file_location('r19_bound_raw_parser',parser);old=importlib.util.module_from_spec(spec);spec.loader.exec_module(old)
        upper=g.LAYER/'upper'
        def visible(logical):
            path=upper/Path(logical).relative_to(g.BUILD);return path if path.is_file()else Path(logical)
        logicals={name:g.BUILD/rel for name,rel in {'binary':'bin/benchFull','Submission_object':'ir/Submission.c.o.export','MainFull_object':'ir/MainFull.c.o.export','BenchSuite_object':'ir/BenchSuite.c.o.export','Submission_C':'ir/Submission.c','MainFull_C':'ir/MainFull.c','BenchSuite_C':'ir/BenchSuite.c'}.items()}
        def identity():return {n:dict(bytes=visible(p).stat().st_size,sha256=sha(visible(p)))for n,p in logicals.items()}
        before=identity();save('build-identity-before.json',before)
        require(before['MainFull_C']['sha256']=='94f69ed19083e0fbb5d4b540d16d4575b82d4aac75779ce88043ef4f908bfecb','MainFull caller drift')
        for n in ('Submission_C','MainFull_C','BenchSuite_C'):save(n+'.c',visible(logicals[n]).read_bytes())
        require(not any(t in visible(logicals['Submission_C']).read_bytes()for t in(b'FL13 cat=',b'FC13 cat=',b'pr13_')),'instrumented source refused')
        immutable=[g.HERE/'gate.py',g.HERE/'benchmark_suite.py',g.HERE/'suites/public-v2.json',g.LIB/'bench/BenchSuite.lean',g.LIB/'bench/MainFull.lean',*sorted((g.LIB/'contract').rglob('*.lean')),ROOT/'competitions/floatlib/pins.json']
        frozen={str(p):sha(p)for p in immutable};save('Kernel.lean',kernel.read_bytes())
        save('config.json',dict(request=request,CPU=getattr(g,'_BENCH_CPU',None),memory_mb=g._BENCH_MEMORY_MB))
        if Path('/proc/cpuinfo').is_file():save('cpuinfo.txt',Path('/proc/cpuinfo').read_bytes())
        cpu=getattr(g,'_BENCH_CPU','');argv=(['taskset','-c',str(cpu)]if cpu and shutil.which('taskset')else[])+[str(logicals['binary'])]
        helper=g.WORK.parent/'R19RouteLabels.lean';plan_file=g.WORK.parent/'R19RoutePlan.json'
        require(not helper.exists()and not plan_file.exists(),'metadata temporary path occupied')
        helper.write_bytes((HERE/'RouteLabels.lean').read_bytes());owned_helper=True;save('RouteLabels.lean',helper.read_bytes())
        for rec in request['plans']:
            require(rec['seed']in(1927003,1927005),'unseen input refused')
            path=HERE/rec['path'];require(sha(path)==rec['sha256'],'seen plan drift')
            raw=path.read_bytes();plan=json.loads(raw);require(len(plan['cases'])==156,'wrong plan coverage')
            plan_file.write_bytes(raw);owned_plan=True;save(f"seen-{rec['seed']}-plan.json",raw)
            progress('metadata-pending',seed=rec['seed'],process=None)
            code,log=call(f"labels-{rec['seed']}",lambda:g.own([g.LAKE,'env','lean','--run','work/R19RouteLabels.lean','work/R19RoutePlan.json'],remaining(90),build='read'))
            require(code==0,'metadata failed');labels=parse_labels(log,plan);save(f"labels-{rec['seed']}.json",labels)
            env={'BENCH_PLAN':json.dumps(plan,separators=(',',':')),'BENCH_SEED':str(rec['seed']),'BENCH_PAIRS':'500000','BENCH_INNER':'3','LEAN_ABORT_ON_PANIC':'1'}
            processes=[]
            for process in range(2):
                progress('whole-pending',seed=rec['seed'],process=process)
                code,log=call(f"whole-{rec['seed']}-{process}",lambda:g.run(argv,remaining(90),build='read',env_extra=env,memory_mb=g._BENCH_MEMORY_MB))
                require(code==0,'original binary failed');require('ROUTE19 'not in log,'metadata observer in timer binary')
                rows=old.bench_rows(log,plan);processes.append(rows);save(f"rows-{rec['seed']}-{process}.json",rows)
                save('partial-case-rows.json',dict(seed=rec['seed'],processes=processes,labels=labels))
                require(identity()==before,'build drift during collection')
            old.verify_same_seed(*processes)
            results.append(dict(seed=rec['seed'],plan_sha256=rec['sha256'],labels=labels,complete_case_rows=processes,timing=summarise(plan,processes,labels)))
            save(f"result-{rec['seed']}.json",results[-1])
        require({str(p):sha(p)for p in immutable}==frozen,'official sources or pins changed')
        require(identity()==before and sha(g.WORK)==SOURCE,'final source/build drift')
        remaining(0.001)
        record=dict(diagnostic_only=True,full_gate=False,complete=True,kernel_sha256=SOURCE,results=results,build_identity_before=before,build_identity_after=identity(),official_hashes=frozen,collection_seconds=time.monotonic()-started,module_cap_seconds=60,complete_boundary_audit='PENDING_SAVED_BENCHSUITE_C_LIFETIME_REVIEW',timer='Unchanged original whole-case best-of3; no internal instrumentation or score')
        save('route-results.json',record);return record
    except Exception as error:
        save('error.json',dict(diagnostic_only=True,complete=False,error_type=type(error).__name__,error=str(error),traceback=traceback.format_exc(),partial_results=results,current_progress=current,elapsed_seconds=time.monotonic()-started));raise
    finally:
        if owned_helper and helper.exists():helper.unlink()
        if owned_plan and plan_file.exists():plan_file.unlink()
