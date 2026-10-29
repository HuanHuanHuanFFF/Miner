"""R25 original TorchLean verifier and original overall measurement CLI; no rewrites."""
from pathlib import Path
import datetime,hashlib,json,os,signal,subprocess,sys,time
ROOT=Path(os.environ['GITHUB_WORKSPACE']);UP=Path(os.environ['TORCHLEAN_ROOT']);OUT=Path(os.environ['TORCHLEAN_REPORTS']);OUT.mkdir(exist_ok=True)
PLAN=ROOT/'competitions/torchlean/candidates/r25-90m-20261029T064916Z/ci-plan.json'
plan=json.loads(PLAN.read_bytes());sha=lambda b:hashlib.sha256(b).hexdigest()
ENV=os.environ.copy();ENV.update(PATH=str(Path.home()/'.elan/bin')+os.pathsep+ENV.get('PATH',''),PYTHONPATH='.:validator',GATE_BUDGET_SECONDS='600',GATE_BUILD_MEMORY_MB='4096',GATE_BENCH_MEMORY_MB='512')
START=time.monotonic();END=START+2200
summary={'source_commit':os.environ['GITHUB_SHA'],'run_id':os.environ['GITHUB_RUN_ID'],'official_commit':plan['official_commit'],'primary_board':'overall','started_at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'complete':False,'results':[],'commands':[],'formal_submission':False,'reference_kind':'UNCHANGED_SHIPPED_NOT_CURRENT_CHAMPION','sample_role':'EXPLORATION_ORIGINAL_QUICK5_2MS_2ROOTSEEDS'}
def save():
 (OUT/'summary.json').write_text(json.dumps(summary,indent=2)+'\n')
def run(args,label,cap,limited=True,cwd=None):
 left=END-time.monotonic();assert left>15,'Runner phasebudget exhausted'
 cap=min(cap,left-10);unit='r25-'+os.environ['GITHUB_RUN_ID']+'-'+sha(label.encode())[:10]+'.scope';cmd=list(map(str,args))
 if limited:cmd=['systemd-run','--user','--scope','--quiet','--unit',unit,'-p','MemoryMax=4096M','-p','MemorySwapMax=0',*cmd]
 began=time.monotonic();log=OUT/(label+'.log')
 with log.open('wb') as f:
  proc=subprocess.Popen(cmd,cwd=cwd or UP,env=ENV,stdout=f,stderr=subprocess.STDOUT,start_new_session=True)
  try:code=proc.wait(timeout=cap)
  except subprocess.TimeoutExpired:
   code=124
   if limited:subprocess.run(['systemctl','--user','kill','--kill-whom=all','--signal=SIGKILL',unit],capture_output=True,timeout=10)
   try:os.killpg(proc.pid,signal.SIGKILL)
   except ProcessLookupError:pass
   proc.wait(timeout=10)
 summary['commands'].append({'label':label,'argv':cmd,'cap_seconds':cap,'exit_code':code,'seconds':time.monotonic()-began,'log_sha256':sha(log.read_bytes()),'log_bytes':log.stat().st_size});save();return code

def protected():
 raw=subprocess.check_output(['git','ls-files','-z'],cwd=UP)
 return {x.decode():sha((UP/x.decode()).read_bytes()) for x in raw.split(b'\0') if x and (UP/x.decode()).is_file() and x.decode()!='lean/work/Submission.lean'}

def main():
 if datetime.datetime.now(datetime.timezone.utc)>=datetime.datetime.fromisoformat(plan['start_cutoff_utc']):raise RuntimeError('Latequeue_notstarted')
 assert subprocess.check_output(['git','rev-parse','HEAD'],cwd=UP,text=True).strip()==plan['official_commit']
 assert (UP/'lean/lean-toolchain').read_text().strip()=='leanprover/lean4:v4.34.0'
 before=protected();summary['protected_before']=before;save()
 (OUT/'plan.json').write_bytes(PLAN.read_bytes());(OUT/'cpuinfo.raw').write_bytes(Path('/proc/cpuinfo').read_bytes())
 assert run(['bash','setup.sh','--benchmark-worker'],'setup',900)==0,'Originalsetupfailed'
 assert run(['bash','setup.sh','--check'],'setup-check',90)==0
 py=UP/'.venv/bin/python'
 assert run([py,'scripts/exact-config.py','--quick','--board','overall','--output',OUT/'overall-config.toml'],'official-quick-config',30)==0
 inputs=UP/'r25-inputs';inputs.mkdir(exist_ok=False)
 reference=UP/'kernels/exact/incumbent/Kernel.lean';assert sha(reference.read_bytes())==plan['shipped_sha256']
 ready=[]
 def measure_one(entry,target,result):
  results=[]
  for seed in plan['seeds']:
   request=OUT/(entry['name']+'-'+str(seed)+'-request.json');output=OUT/(entry['name']+'-'+str(seed)+'-measurement.json')
   # Request construction imports only pinned official modules. Alltiming fields resolved by officialconfig.
   builder=UP/'r25-request.py';builder.write_text("""import sys,json
from pathlib import Path
sys.path[:0]=['.','validator']
from config import Config,MODELS,BATCHES,KINDS
from multiseed import workloads
from benchmark import machine_identity
import fingerprint
c=Config.load(sys.argv[1]);plan=c.plan('overall');timing=c.timing|plan['timing']|c.environments['local']['timing'];timing.update(build_seconds=600,cached_build_seconds=180,benchmark_seconds=300,run_seconds=120)
r={'environment':'local','identity':machine_identity(),'seed':int(sys.argv[2]),'candidate_hash':sys.argv[3],'reference_hash':sys.argv[4],'cells':[f'{m}:b{b}:{k}' for m in MODELS for b in BATCHES[m] for k in KINDS],'timing':timing,'benchmark_identity':fingerprint.benchmark(),'workloads':workloads(int(sys.argv[2]))}
from config import MeasurementRequest
MeasurementRequest.parse(r)
Path(sys.argv[5]).write_text(json.dumps(r,indent=2)+'\\n')
""")
   assert run([py,builder,OUT/'overall-config.toml',seed,entry['sha256'],plan['shipped_sha256'],request],entry['name']+'-'+str(seed)+'-request',30)==0
   code=run([py,'-m','benchmark','--request',request,'--candidate',target/'Kernel.lean','--reference',reference,'--result',output],entry['name']+'-'+str(seed)+'-measure',940)
   data=json.loads(output.read_bytes()) if output.exists() else {'error':{'reason':'missingoutput'}}
   results.append({'seed':seed,'process_exit_code':code,'result_file':output.name,'has_result':isinstance(data.get('result'),dict),'error':data.get('error')});result['measurements']=results;save()
   if code!=0 or not isinstance(data.get('result'),dict):break
  result['measurement_state']='COMPLETE_ORIGINAL_QUICK_OVERALL' if len(results)==len(plan['seeds']) and all(x['has_result'] and x['process_exit_code']==0 for x in results) else 'FAILED_PARTIAL_RETAINED';save()
 for entry in plan['candidates']:
  source=ROOT/entry['path'];assert sha(source.read_bytes())==entry['sha256'];target=inputs/entry['name'];target.mkdir();(target/'Kernel.lean').write_bytes(source.read_bytes())
  result={'name':entry['name'],'sha256':entry['sha256'],'source_path':entry['path'],'proof_state':'NOT_RUN','measurement_state':'NOT_RUN'};summary['results'].append(result);save()
  verdict=OUT/(entry['name']+'-verdict.json');code=run([py,'-m','verification',target,'--verdict',verdict],entry['name']+'-proof',650)
  result['proof_exit_code']=code
  if verdict.exists():result['verdict']=json.loads(verdict.read_bytes())
  ok=code==0 and result.get('verdict',{}).get('passed') is True and result['verdict'].get('verifier_fingerprint')==result['verdict'].get('verifier_fingerprint_end')
  result['proof_state']='FULL_ORIGINAL_PROOF_GATE_PASS' if ok else 'REJECTED_OR_INFRASTRUCTURE';save()
  assert protected()==before,'Protectedsourcechanged'
  if entry.get('baseline') and not ok:raise RuntimeError('Unchangedbaselinefailed')
  if ok and entry.get('measure'):measure_one(entry,target,result)
  if ok and entry.get('helper_roots'):
   extra=source.read_text()+ '\n'+ '\n'.join('#print axioms '+n for n in entry['helper_roots'])+'\n'
   audit=UP/'lean/work/R25HelperAudit.lean';audit.write_text(extra)
   code=run([str(Path.home()/'.elan/bin/lake'),'env','lean',audit],'helper-'+entry['name'],180,cwd=UP/'lean')
   text=(OUT/('helper-'+entry['name']+'.log')).read_text(errors='replace')
   import re
   roots=re.findall(r'(?:depends on axioms: \[([^\]]*)\]|does not depend on any axioms)',text.replace('\n',' '))
   result['helper_audit']={'exit_code':code,'expected':len(entry['helper_roots']),'printed':len(roots),'allowed_only':all(set(x.strip() for x in row.split(',') if x.strip())<={'propext','Classical.choice','Quot.sound'} for row in roots)}
   result['helper_audit']['pass']=code==0 and len(roots)==len(entry['helper_roots']) and result['helper_audit']['allowed_only'];save()
 summary['protected_after']=protected();assert summary['protected_after']==before
 summary['all_requested_measurements_complete']=all(not entry.get('measure') or any(x['name']==entry['name'] and x['measurement_state']=='COMPLETE_ORIGINAL_QUICK_OVERALL' for x in summary['results']) for entry in plan['candidates']);summary['originals_unchanged']=True;summary['complete']=len(summary['results'])==len(plan['candidates']) and summary['all_requested_measurements_complete'] and summary['originals_unchanged'];summary['all_requested_proofs_pass']=all(x['proof_state']=='FULL_ORIGINAL_PROOF_GATE_PASS' and x.get('helper_audit',{'pass':True})['pass'] for x in summary['results']);save()
try:main()
except Exception as e:summary.update(error_type=type(e).__name__,error=str(e),complete=False)
finally:
 summary.update(finished_at_utc=datetime.datetime.now(datetime.timezone.utc).isoformat(),elapsed_seconds=time.monotonic()-START);save()
 files=[p for p in OUT.rglob('*') if p.is_file()];(OUT/'file-hashes.json').write_text(json.dumps({p.relative_to(OUT).as_posix():{'bytes':p.stat().st_size,'sha256':sha(p.read_bytes())} for p in files},indent=2)+'\n')
 print(json.dumps({'complete':summary['complete'],'all_proofs':summary.get('all_requested_proofs_pass'),'all_measurements':summary.get('all_requested_measurements_complete'),'error':summary.get('error')}))
if not summary['complete'] or not summary.get('all_requested_proofs_pass') or not summary.get('all_requested_measurements_complete'):raise SystemExit(1)
