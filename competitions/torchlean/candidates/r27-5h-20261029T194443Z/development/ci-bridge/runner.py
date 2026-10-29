"""Owned native-only diagnostic target; original tools and source remain unchanged."""
from pathlib import Path
import datetime,hashlib,json,os,re,shlex,shutil,subprocess,sys,time,urllib.request,importlib.util
ROOT=Path(os.environ['GITHUB_WORKSPACE']);UP=Path(os.environ['TORCHLEAN_ROOT']);OUT=Path(os.environ['TORCHLEAN_REPORTS']);OUT.mkdir(exist_ok=True)
PLAN=ROOT/'competitions/torchlean/candidates/r27-5h-20261029T194443Z/ci-plan.json';plan=json.loads(PLAN.read_bytes());START=time.monotonic();END=START+1800
ENV=os.environ.copy();ENV.update(PATH=str(Path.home()/'.elan/bin')+os.pathsep+ENV.get('PATH',''),PYTHONPATH='.:validator',GATE_BUDGET_SECONDS='600',GATE_BUILD_MEMORY_MB='4096',GATE_BENCH_MEMORY_MB='512')
sha=lambda p:hashlib.sha256(Path(p).read_bytes()).hexdigest()
record={'source_commit':os.environ['GITHUB_SHA'],'run_id':os.environ['GITHUB_RUN_ID'],'official_commit':plan['official_commit'],'scope':'UNPROVED_NATIVE_RESEARCH_ONLY_NO_ORIGINAL_GATE_PASS_FOR_PROTOTYPE','primary_board':plan['board'],'complete':False,'results':[],'commands':[],'started_at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'current_champion_measurement':False}
def save(): (OUT/'summary.json').write_text(json.dumps(record,indent=2)+'\n')
def run(args,label,cap,cwd=None):
 left=END-time.monotonic();assert left>10,'Runnerbudgetexhausted';cap=min(cap,left-5)
 with (OUT/(label+'.log')).open('wb') as f:
  began=time.monotonic();proc=subprocess.run(list(map(str,args)),cwd=cwd or UP,env=ENV,stdout=f,stderr=subprocess.STDOUT,timeout=cap)
 record['commands'].append({'label':label,'argv':list(map(str,args)),'exit_code':proc.returncode,'seconds':time.monotonic()-began,'cap':cap,'log_sha256':sha(OUT/(label+'.log'))});save();return proc.returncode
def protected():
 return {x.decode():sha(UP/x.decode()) for x in subprocess.check_output(['git','ls-files','-z'],cwd=UP).split(b'\0') if x and (UP/x.decode()).is_file() and x.decode()!='lean/work/Submission.lean'}
def load_tools():
 import site
 original_site=UP/'.venv/lib'/('python'+str(sys.version_info.major)+'.'+str(sys.version_info.minor))/'site-packages'
 assert original_site.is_dir(),'PinnedvenvABIcannotloadunderhostinterpreter'
 site.addsitedir(str(original_site))
 os.chdir(UP);sys.path[:0]=[str(UP),str(UP/'validator')]
 import sandbox as g,benchmark as bm,fingerprint,config,multiseed
 return g,bm,fingerprint,config,multiseed

def main():
 assert datetime.datetime.now(datetime.timezone.utc)<datetime.datetime.fromisoformat(plan['start_cutoff_utc']), 'QUEUE_ACQUIRED_AFTER_EXISTING_EXPERIMENT_START_LIMIT'
 assert subprocess.check_output(['git','rev-parse','HEAD'],cwd=UP,text=True).strip()==plan['official_commit']
 before=protected();record['protected_before']=before;(OUT/'plan.json').write_bytes(PLAN.read_bytes());(OUT/'cpuinfo.raw').write_bytes(Path('/proc/cpuinfo').read_bytes());save()
 assert run(['systemd-run','--user','--scope','--quiet','-p','MemoryMax=4096M','-p','MemorySwapMax=0','bash','setup.sh','--benchmark-worker'],'setup',600)==0
 assert run(['bash','setup.sh','--check'],'setup-check',30)==0
 g,bm,fp,cfg,ms=load_tools();assert g._SANDBOX and g._BUILD_MEMORY_MB==4096 and g._BENCH_MEMORY_MB==512
 for entry in plan.get('helpers',[]):
  source=ROOT/entry['path'];assert sha(source)==entry['sha256'];g.wipe(g.LAYER);(g.LAYER/'upper').mkdir(parents=True);(g.LAYER/'work').mkdir();target=g.LIB/'work'/('R27Helper_'+entry['name']+'.lean');diagnostic=source.read_bytes()+b'\n'+('\n'.join('#print axioms '+x for x in entry.get('helper_roots',[]))+'\n').encode();target.write_bytes(diagnostic);g._budget.reset(entry.get('seconds',120));code,log=g.own([g.LAKE,'env','lean','work/'+target.name],entry.get('seconds',120),build='write');(OUT/(entry['name']+'-helper.log')).write_text(log);record.setdefault('helper_diagnostics',[]).append({'name':entry['name'],'source_sha256':entry['sha256'],'exit_code':code,'scope':'Standalone helper elaboration only; not original all12 gate or replay'});save();g.wipe(g.LAYER)
 def materialize(entry):
  if 'fetch' not in entry:return ROOT/entry['path']
  pin=entry['fetch'];folder=UP/'r27-source-private';folder.mkdir(exist_ok=True);original=folder/('official-'+str(pin['submission'])+'.lean')
  if not original.exists():
   with urllib.request.urlopen(urllib.request.Request(pin['url'],headers={'User-Agent':'TorchLean-research-readonly/1.0'}),timeout=45) as response:original.write_bytes(response.read())
  assert sha(original)==pin['sha256'],'Official released source hash mismatch'
  raw=original.read_bytes()
  if entry.get('variant'):
   patch=ROOT/entry['patch_script'];assert sha(patch)==entry['patch_script_sha256'];spec=importlib.util.spec_from_file_location('r27_owned_patch',patch);module=importlib.util.module_from_spec(spec);spec.loader.exec_module(module);raw=module.transform(raw,pin['submission'],entry['variant'])
  dest=folder/(entry['name']+'-Kernel.lean');dest.write_bytes(raw);assert sha(dest)==entry['sha256'];assert len(raw)==entry['bytes'];return dest
 reference=materialize(plan['reference']);refdir=UP/'r27-reference';refdir.mkdir();(refdir/'Kernel.lean').write_bytes(reference.read_bytes());py=UP/'.venv/bin/python'
 record['reference_proof']={'scope':'Official public predecessor declared Correct; full original replay not run in this native exploration'};save()
 assert run([py,'scripts/exact-config.py','--quick','--board',plan['board'],'--reference',refdir/'Kernel.lean','--output',OUT/'overall-config.toml'],'quick-config',30)==0
 config=cfg.Config.load(OUT/'overall-config.toml');baseconfig=(g.LIB/'lakefile.lean').read_bytes();mainbytes=(g.LIB/'bench/MainExact.lean').read_bytes();record['owned_main_equals_original_sha256']=hashlib.sha256(mainbytes).hexdigest()
 target=re.search(rb'^lean_exe benchExact where\s*\n((?:[ \t]+[^\n]*\n|\n)*)',baseconfig,re.M);assert target
 assert {x.strip() for x in target[1].decode().splitlines() if x.strip()}=={'srcDir := "bench"','root := `MainExact'}
 mainfile=g.LIB/'work/R27NativeMain.lean';lakefile=g.LIB/'work/R27NativeLake.lean';mainfile.write_bytes(mainbytes);lakefile.write_bytes(baseconfig+b'\n\nlean_exe r27Native where\n  srcDir := "work"\n  root := `R27NativeMain\n')
 assert mainfile.read_bytes()==mainbytes
 original={str(p):sha(p) for p in [g.BUILD/'ir/MainExact.c',g.BUILD/'ir/MainExact.c.o.export',g.BUILD/'ir/MainExact.c.o.export.trace',g.BUILD/'bin/benchExact',g.BUILD/'bin/benchExact.trace',g.BUILD/'bin/benchExact.rsp']}
 def visible(p):
  candidate=g.LAYER/'upper'/p.relative_to(g.BUILD);return candidate if candidate.is_file() else p
 def trace(p):
  d=json.loads(p.read_bytes());assert d.get('synthetic') is False;xs=[x['message'][3:] for x in d.get('log',[]) if x.get('message','').startswith('.> ')];assert len(xs)==1;return shlex.split(xs[0])
 def norm(args):return [re.sub(r'(?<=/)(?:MainExact|R27NativeMain)(?=\.)','<MAIN>',re.sub(r'(?<=/)(?:benchExact|r27Native)(?=\.|$)','<BIN>',x)) for x in args]
 def build(entry):
  name=entry['name'];source=materialize(entry);assert sha(source)==entry['sha256'];folder=OUT/name;folder.mkdir()
  if entry.get('full_gate'):
   gate_dir=UP/'r27-full-gates'/name;gate_dir.mkdir(parents=True);(gate_dir/'Kernel.lean').write_bytes(source.read_bytes());verdict_file=folder/'full-gate-verdict.json'
   gate_code=run([py,'-m','verification',gate_dir,'--verdict',verdict_file],name+'-full-gate',650)
   verdict=json.loads(verdict_file.read_bytes()) if verdict_file.is_file() else {};record.setdefault('full_gates',[]).append({'name':name,'source_sha256':entry['sha256'],'exit_code':gate_code,'verdict':verdict});save()
   if gate_code!=0 or not verdict.get('passed'):
    g.wipe(g.LAYER);(g.LAYER/'upper').mkdir(parents=True);(g.LAYER/'work').mkdir();g.WORK.write_bytes(source.read_bytes());g._budget.reset(150,deadline=min(END-20,time.monotonic()+150));raw_code,raw_log=g.own([g.LAKE,'build','VerifyExact'],150,build='write');(folder/'full-gate-raw-statement.log').write_text(raw_log);raise AssertionError('Originalfullgaterejected:'+name+':'+str(verdict.get('reason')))
   assert verdict['stage']=='axioms' and verdict['verifier_fingerprint']==verdict['verifier_fingerprint_end']
  g.wipe(g.LAYER);(g.LAYER/'upper').mkdir(parents=True);(g.LAYER/'work').mkdir();g.WORK.write_bytes(source.read_bytes());v=g.Verdict(submission=name)
  assert g.intake(g.WORK,v) is None and g.policy(g.WORK,v) is None,'Originalintakepolicyrejected'
  g._budget.reset(300,deadline=min(END-30,time.monotonic()+300));code,log=g.own([g.LAKE,'-f','work/R27NativeLake.lean','build','r27Native'],300,build='write');(folder/'build.log').write_text(log);assert code==0,'Ownednativebuildfailed:'+name
  foreign=g.foreign(g.LAYER/'upper');assert all(Path(x).name.split('.')[0] in {'Submission','R27NativeMain','r27Native'} for x in foreign),foreign
  flags={}
  for kind,a,b in [('compile',g.BUILD/'ir/MainExact.c.o.export.trace',g.BUILD/'ir/R27NativeMain.c.o.export.trace'),('link',g.BUILD/'bin/benchExact.trace',g.BUILD/'bin/r27Native.trace'),('response',g.BUILD/'bin/benchExact.rsp',g.BUILD/'bin/r27Native.rsp')]:
   aa=visible(a);bb=visible(b);(folder/('original-'+kind+'.raw')).write_bytes(aa.read_bytes());(folder/('owned-'+kind+'.raw')).write_bytes(bb.read_bytes());av=shlex.split(aa.read_text()) if kind=='response' else trace(aa);bv=shlex.split(bb.read_text()) if kind=='response' else trace(bb);flags[kind]={'original_args':av,'owned_args':bv,'equal_only_root_mapping':norm(av)==norm(bv)}
   assert flags[kind]['equal_only_root_mapping'],'Flagdelta:'+kind
  assert all(sha(Path(p))==digest for p,digest in original.items()),'Originalsharedbuildchanged'
  (folder/'flags.json').write_text(json.dumps(flags,indent=2)+'\n')
  generated={}
  for stem in ['Submission','R27NativeMain']:
   c=visible(g.BUILD/'ir'/(stem+'.c'));assert c.is_file();obj=visible(g.BUILD/'ir'/(stem+'.c.o.export'));generated[stem]={'c_sha256':sha(c),'c_bytes':c.stat().st_size,'object_sha256':sha(obj)}
  (folder/'generated-code-hashes.json').write_text(json.dumps(generated,indent=2)+'\n')
  binary=g.LIB/'work/r27-binaries'/name;binary.parent.mkdir(exist_ok=True);shutil.copy2(visible(g.BUILD/'bin/r27Native'),binary);assert binary.stat().st_size<512*2**20
  info={'name':name,'source_sha256':entry['sha256'],'source_path':entry['path'],'proof_state':'FULL_ORIGINAL_GATE_REPLAYED' if entry.get('full_gate') else 'DECLARED_CORRECT_TYPECHECKED_NO_FULL_ORIGINAL_REPLAY' if entry.get('fetch') else 'NOT_PROVED_NATIVE_ONLY','binary_sha256':sha(binary),'foreign':foreign,'flags_pass':True,'measurements':[],'measurement_state':'NOT_RUN'};record['results'].append(info);save();g.wipe(g.LAYER);return binary,info
 refentry={**plan['reference'],'name':'calibration','reference':True};refbin,refinfo=build(refentry)
 for entry in plan['candidates']:
  try:
   binary,info=build(entry)
   for seed in plan['seeds']:
    timing=config.timing|config.plan(plan['board'])['timing']|config.environments['local']['timing'];timing.update(build_seconds=300,cached_build_seconds=180,benchmark_seconds=300,run_seconds=120)
    request={'environment':'local','identity':bm.machine_identity(),'seed':seed,'candidate_hash':entry['sha256'],'reference_hash':refentry['sha256'],'cells':list(config.plan(plan['board'])['cells']),'timing':timing,'benchmark_identity':fp.benchmark(),'workloads':ms.workloads(seed)};cfg.MeasurementRequest.parse(request);request_path=OUT/(entry['name']+'-'+str(seed)+'-request.json');request_path.write_text(json.dumps(request,indent=2)+'\n')
    clock=bm.Deadline('benchmark',min(300,max(1,END-time.monotonic()-20)));initial=bm.run_binary(refbin,request,{},3,'reference',clock);reps=ms.calibrated_counts(initial,timing['cell_ms']);checked=bm.run_binary(refbin,request,reps,3,'reference',clock);reps=ms.calibrated_counts(checked,timing['cell_ms'],reps);rounds=[]
    for i in range(timing['rounds']):
     sides=[('reference',refbin),('candidate',binary)];sides.reverse() if i%2 else None;observed={}
     for side,exe in sides:
      observed[side]=bm.run_binary(exe,request,reps,timing['inner'],side,clock);(OUT/(entry['name']+'-'+str(seed)+'-round'+str(i)+'-'+side+'.json')).write_text(json.dumps(observed[side],indent=2)+'\n')
     cells={}
     for cell in reps:
      a,b=observed['reference'][cell],observed['candidate'][cell];assert a[1]==b[1],'CHECKSUM_MISMATCH:'+str(seed)+':'+cell+':ref='+str(a[1])+':candidate='+str(b[1]);cells[cell]={'reference_ns':a[0],'candidate_ns':b[0],'reference_checksum':a[1],'candidate_checksum':b[1]}
     rounds.append({'reference_first':i%2==0,'cells':cells})
    value={'request_hash':cfg.measurement_hash(request),'workloads':request['workloads'],'provenance':{'identity':bm.machine_identity(),'machine':__import__('socket').gethostname(),'architecture':__import__('platform').machine(),'cpu_affinity':g._BENCH_CPU,'load':os.getloadavg(),'candidate_binary':sha(binary),'reference_binary':sha(refbin)},'calibration':{c:v[0] for c,v in initial.items()},'repetitions':reps,'rounds':rounds,'timing_seconds':clock.elapsed(),'preparation':{'mode':'OWN_NATIVE_ONLY_TARGET','original_full_gate_not_called_for_exploration':True}}
    (OUT/(entry['name']+'-'+str(seed)+'-measurement.json')).write_text(json.dumps({'result':value},indent=2)+'\n');info['measurements'].append({'seed':seed,'complete':True,'paired_rows':len(rounds)*len(reps)});save()
   info['measurement_state']='COMPLETE_NATIVE_ONLY_EXPLORATION';save()
  except Exception as error:
   record.setdefault('candidate_errors',[]).append({'candidate':entry['name'],'error_type':type(error).__name__,'error':str(error)});save()
 for entry in plan.get('proof_diagnostics',[]):
  if END-time.monotonic()<60:break
  source=ROOT/entry['path'];assert sha(source)==entry['sha256'];g.wipe(g.LAYER);(g.LAYER/'upper').mkdir(parents=True);(g.LAYER/'work').mkdir();g.WORK.write_bytes(source.read_bytes());g._budget.reset(150,deadline=min(END-15,time.monotonic()+150));code,text=g.own([g.LAKE,'build','VerifyExact'],150,build='write');(OUT/(entry['name']+'-raw-statement.log')).write_text(text);record.setdefault('proof_diagnostics',[]).append({'name':entry['name'],'sha256':entry['sha256'],'exit_code':code,'scope':'RAW_STATEMENT_DIAGNOSTIC_ONLY_NOT_FULL_GATE'});save();g.wipe(g.LAYER)
 assert protected()==before;assert (g.LIB/'lakefile.lean').read_bytes()==baseconfig and (g.LIB/'bench/MainExact.lean').read_bytes()==mainbytes;record['originals_unchanged']=True;record['protected_after']=protected();record['complete']=all(any(x['name']==e['name'] and x['measurement_state']=='COMPLETE_NATIVE_ONLY_EXPLORATION' for x in record['results']) for e in plan['candidates']);save()
try:main()
except Exception as e:record.update(complete=False,error_type=type(e).__name__,error=str(e))
finally:
 record.update(finished_at_utc=datetime.datetime.now(datetime.timezone.utc).isoformat(),elapsed_seconds=time.monotonic()-START);save();files=[p for p in OUT.rglob('*') if p.is_file()];(OUT/'file-hashes.json').write_text(json.dumps({p.relative_to(OUT).as_posix():{'bytes':p.stat().st_size,'sha256':sha(p)} for p in files},indent=2)+'\n');print(json.dumps({'complete':record['complete'],'scope':record['scope'],'error':record.get('error'),'candidate_errors':record.get('candidate_errors')}))
if not record['complete']:raise SystemExit(1)
