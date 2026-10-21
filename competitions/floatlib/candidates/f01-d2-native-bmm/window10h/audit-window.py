"""Audit the exact artifacts of the ten-hour Astra/development continuation."""
from pathlib import Path
from statistics import median
import ast,datetime,hashlib,importlib.util,json,os,re,subprocess,sys
ROOT=Path.cwd();OWN=Path(__file__).resolve().parent
STATE=ROOT/'competitions/floatlib/coordination/development-status.json'
RUNS=ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs'
spec=importlib.util.spec_from_file_location('floatlib_gain_support',RUNS.parent/'analyze.py');support=importlib.util.module_from_spec(spec);spec.loader.exec_module(support)
state=json.loads(STATE.read_bytes());ids=list(dict.fromkeys(x['run'] for x in state['collaboration']['active_ci']))
records=[];jobs=[];payloads=[]
for rid in ids:
 p=RUNS/str(rid);index=p/'original-artifact-hashes.json'
 if not index.exists():jobs.append({'run':rid,'collected':False});continue
 ix=json.loads(index.read_bytes());a=p/ix['directory'];meta=json.loads((p/'ci-run.json').read_bytes());assert meta['status']=='completed'
 for name,row in ix['files'].items():
  file=a/name;data=file.read_bytes();assert len(data)==row['bytes'] and hashlib.sha256(data).hexdigest()==row['sha256'];payloads.append((file,row['sha256']))
 batch=json.loads((a/'summary.json').read_bytes());assert batch['complete'];assert batch['source_commit']==meta['headSha']
 provenance=json.loads((a/'provenance.json').read_bytes());environment=json.loads((a/'environment.json').read_bytes());assert environment['official_source_diff']=='CLEAN'
 cpu=next(x.split(':',1)[1].strip() for x in provenance['lscpu'].splitlines() if x.startswith('Model name:'))
 jobs.append({'run':rid,'collected':True,'conclusion':meta['conclusion'],'commit':meta['headSha'],'artifact':a.relative_to(ROOT).as_posix(),'cpu':cpu,'cpu_affinity':provenance['cpu_affinity'],'environment_path':(a/'environment.json').relative_to(ROOT).as_posix(),'provenance_path':(a/'provenance.json').relative_to(ROOT).as_posix()})
 for row in batch['results']:
  data=(a/'inputs'/row['candidate']/'Kernel.lean').read_bytes();assert hashlib.sha256(data).hexdigest()==row['kernel_sha256']
  local=ROOT/'competitions/floatlib'/('references/official-incumbent/Kernel.lean' if row['candidate']=='baseline' else 'candidates/'+row['candidate']+'/Kernel.lean');assert data==local.read_bytes()
  v=json.loads((a/row['verdict']).read_bytes());rec={'run':rid,'candidate':row['candidate'],'kernel_sha256':row['kernel_sha256'],'validation_mode':row.get('validation_mode'),'full_gate':row['full_gate'],'compile_pass':row.get('compile_pass',False),'stage':v['stage'],'passed':v['passed'],'reason':v.get('reason'),'seed':row['seed'],'ratio_vs_shipped':None,'direct_champion_ratio':'UNKNOWN','formal_submission':'NOT_SUBMITTED','verdict_path':(a/row['verdict']).relative_to(ROOT).as_posix()}
  if row['full_gate']:
   assert v['passed'] and v['mode']=='gate' and v['stage']=='score';assert len(v['classes'])==12 and len(v['rounds'])==25;assert v['verifier_fingerprint']==v['verifier_fingerprint_end']
   assert v['champion_sha256']==state['baseline_sha256']
   log=re.sub(r'\x1b\[[0-9;]*m','',(a/(row['candidate']+'-gate.log')).read_text(encoding='utf-8'))
   axioms=ast.literal_eval(re.search(r'\[axioms\] (\[[^\n]*?\])',log).group(1));assert set(axioms)<=set(provenance['pins']['allowed_axioms'])
   assert 'Submission replays cleanly' in log and 'VerifyFull replays cleanly' in log
   rec.update(axioms=axioms,reference_sha256=v['champion_sha256'],cpu=cpu,cpu_affinity=provenance['cpu_affinity'])
   ratio=sum(x['submission_ns'] for x in v['classes'].values())/sum(x['incumbent_ns'] for x in v['classes'].values());assert abs(ratio-v['ratio'])<1e-10
   rec.update(ratio_vs_shipped=ratio,paired_gain_p05=support.gain_p05(v['rounds']),kernels_vs_shipped={k:sum(x['submission_ns'] for n,x in v['classes'].items() if n.startswith(k+':'))/sum(x['incumbent_ns'] for n,x in v['classes'].items() if n.startswith(k+':')) for k in ['add','mul','sum','bmm']})
  records.append(rec)
result={'window_id':state['collaboration']['window_id'],'window_start_utc':state['collaboration']['start_utc'],'window_end_utc':state['collaboration']['end_utc'],'audited_at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'jobs':jobs,'payload_files_verified':len(payloads),'records':records,'scope':'Full gate, compile-only and missing results remain separate. Ratios here are paired to exact shipped reference; dashboard champion-relative conversion is separately evidenced.'}
if '--git' in sys.argv:
 requested=b''.join(('HEAD:'+p.relative_to(ROOT).as_posix()+'\n').encode() for p,h in payloads);raw=subprocess.check_output(['git','cat-file','--batch'],input=requested);pos=0
 for p,h in payloads:
  end=raw.index(b'\n',pos);header=raw[pos:end].split();assert header[1]==b'blob';size=int(header[2]);pos=end+1;assert hashlib.sha256(raw[pos:pos+size]).hexdigest()==h;pos+=size+1
 result['git_payload_audit']={'commit':subprocess.check_output(['git','rev-parse','HEAD'],text=True).strip(),'verified':len(payloads)}
for p in (ROOT/'competitions/floatlib/candidates').glob('f01-d2-*/manifest.json'):
 m=json.loads(p.read_bytes());assert hashlib.sha256((p.parent/'Kernel.lean').read_bytes()).hexdigest()==m['candidate_sha256']
out=OWN/'summary.json';tmp=out.with_suffix('.update-tmp');tmp.write_bytes((json.dumps(result,ensure_ascii=False,indent=2)+'\n').encode());os.replace(tmp,out)
print(json.dumps({'jobs_collected':sum(x['collected'] for x in jobs),'jobs_total':len(jobs),'payloads_verified':len(payloads),'nonbaseline_results':[{k:r[k] for k in ['run','candidate','full_gate','compile_pass','stage','ratio_vs_shipped']} for r in records if r['candidate']!='baseline']},indent=2))
