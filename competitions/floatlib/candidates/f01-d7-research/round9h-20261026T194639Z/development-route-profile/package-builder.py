"""Package existing draft into reserved R19 hook scope; no Git mutation or Lean."""
from pathlib import Path
from datetime import datetime,timezone
import base64,hashlib,json,subprocess

H=Path(__file__).resolve().parent
ROOT=next(p for p in H.parents if(p/'competitions/floatlib/pins.json').is_file())
R19=H.parent;OLD=R19/'development-workers/structural-cost/route-profile'
C=ROOT/'competitions/floatlib/candidates';SOURCE='622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
sha=lambda b:hashlib.sha256(b).hexdigest()
old_names=['route-profile-driver.py','RouteLabels.lean','seen-1927003-plan.json','seen-1927005-plan.json','request.json']
old_before={n:sha((OLD/n).read_bytes())for n in old_names}
parser_rel='competitions/floatlib/candidates/f01-d7-research/round3h-20261024T112622Z/profile-whole-multi-current.py'
blob=subprocess.check_output(['git','rev-parse','HEAD:'+parser_rel],cwd=ROOT,text=True).strip()
assert blob=='abc3d912dac66d1b2970ba1a7e5288a3d51446a4'
parser_raw=subprocess.check_output(['git','cat-file','blob',blob],cwd=ROOT)
assert sha(parser_raw)=='8726e1e5debcfc335a11585d2a432a74ef379727fa393c686abecf631fedd23e'
assert parser_raw==(ROOT/parser_rel).read_bytes()
for name in ('RouteLabels.lean','seen-1927003-plan.json','seen-1927005-plan.json'):(H/name).write_bytes((OLD/name).read_bytes())
(H/'legacy-whole-parser.py').write_bytes(parser_raw)
provenance=dict(original_path=parser_rel,git_head=subprocess.check_output(['git','rev-parse','HEAD'],cwd=ROOT,text=True).strip(),
                git_blob=blob,sha256=sha(parser_raw),worktree_equals_git_blob=True)
(H/'parser-provenance.json').write_text(json.dumps(provenance,indent=2)+'\n',newline='\n')
original=(OLD/'request.json').read_bytes();canonical_original=original.replace(b'\r\n',b'\n')
(H/'request-original-240.json').write_bytes(canonical_original)
request=json.loads(original);assert request['maximum_module_seconds']==240
request.update(maximum_module_seconds=60,original_maximum_module_seconds=240,
               original_request_sha256=sha(canonical_original),original_worker_request_sha256=sha(original),
               original_request_copy='Canonical LF reference; original bytes retained unchanged in worker and base64 in package receipt',
               parser=dict(path='legacy-whole-parser.py',sha256=sha(parser_raw),git_blob=blob),
               timeout_context=dict(inner_process=120,nested_statement=180,receipt_reserve=8,
                                    effective_cap='min(60,120-process_age-8)'))
(H/'request.json').write_text(json.dumps(request,indent=2)+'\n',newline='\n')
prefix=(OLD/'route-profile-driver.py').read_text().split('def run(g,kernel,out,initial_plan,initial_seed):',1)[0]
prefix=prefix.replace('import hashlib,importlib.util,json,os,shutil,subprocess,time','import hashlib,importlib.util,json,os,shutil,subprocess,time,traceback')
run=r'''def run(g,kernel,out,initial_plan,initial_seed,absolute_deadline=None):
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
'''
(H/'driver.py').write_text(prefix+run,newline='\n')
components=[]
for name in ('driver.py','RouteLabels.lean','legacy-whole-parser.py','parser-provenance.json','seen-1927003-plan.json','seen-1927005-plan.json','request.json','request-original-240.json'):
    p=H/name;components.append(dict(path=p.relative_to(ROOT).as_posix(),bytes=p.stat().st_size,sha256=sha(p.read_bytes())))
kernel=(C/'f01-r15-dev-packed-b2-1/Kernel.lean').read_bytes();assert sha(kernel)==SOURCE
target=C/'f01-r19-dev-route-profile1';target.mkdir(exist_ok=True);(target/'Kernel.lean').write_bytes(kernel)
hook=R19/'development-route-audit.py'
manifest=dict(candidate=target.name,candidate_file='Kernel.lean',candidate_sha256=SOURCE,candidate_bytes=len(kernel),
              parent='f01-r15-dev-packed-b2-1',parent_sha256=SOURCE,created_at_utc=datetime.now(timezone.utc).isoformat(),
              validation_mode='statement-only',diagnostic_only=True,proof_status='UNCHANGED_622D_PRIOR_FULL_GATES_NOT_RERUN_HERE',
              performance='EXPLICIT_ROUTE_DIAGNOSTIC_ONLY_NOT_SCORE',
              mechanism='ExactB2 statement then independent metadata and unchanged original per-case timer collection; no kernel/axiom/score stage',
              helper_audit_module='development-route-audit.py',helper_audit_module_sha256=sha(hook.read_bytes()),
              helper_audit_source_sha256=SOURCE,route_profile_request_sha256=sha((H/'request.json').read_bytes()),
              route_profile_maximum_seconds=60,components=components,
              destruction_scope='PENDING_ACTUAL_BENCHSUITE_C_REVIEW',full_gate='NOT_RUN_DIAGNOSTIC_ONLY')
(target/'manifest.json').write_text(json.dumps(manifest,indent=2)+'\n',newline='\n')
assert old_before=={n:sha((OLD/n).read_bytes())for n in old_names}
receipt=dict(at_utc=datetime.now(timezone.utc).isoformat(),state='PACKAGED_READY_FOR_INDEPENDENT_REVIEW_RUNTIME_NOT_RUN',
             kernel_sha256=SOURCE,manifest_sha256=sha((target/'manifest.json').read_bytes()),hook_sha256=sha(hook.read_bytes()),
             parser=provenance,source_worker_files_unchanged=old_before,
             original_worker_request_sha256=sha(original),original_request_sha256=sha(canonical_original),
             original_request_bytes_base64=base64.b64encode(original).decode('ascii'),
             new_request_sha256=sha((H/'request.json').read_bytes()),
             cap_change=dict(original=240,requested=60,inner=120,parent_statement=180,reserve=8),
             components=components,Git_mutations=0,CI_runs=0,local_Lean_runs=0)
(H/'package-receipt.json').write_text(json.dumps(receipt,indent=2)+'\n',newline='\n')
print(json.dumps({k:receipt[k]for k in ('state','kernel_sha256','manifest_sha256','hook_sha256','cap_change')},indent=2))
