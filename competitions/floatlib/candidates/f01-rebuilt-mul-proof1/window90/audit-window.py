"""Audit collected evidence for the authorized 90-minute research window."""
from pathlib import Path
from statistics import median
import hashlib,json,importlib.util,datetime,os,sys,subprocess
ROOT=Path.cwd();OWN=Path(__file__).resolve().parent
CAND=ROOT/'competitions/floatlib/candidates';RUNS=CAND/'f01-mul-log2-proof1/ci-runs'
IDS=[39568030328,39568673167,39569856174,39570515461,39571438465,39571489959,39572722399,39573248838,39574369008,39575344774,39575944885,39577094266]
spec=importlib.util.spec_from_file_location('window_audit_support',CAND/'f01-mul-log2-proof1/analyze.py');support=importlib.util.module_from_spec(spec);spec.loader.exec_module(support)
def sha(b):return hashlib.sha256(b).hexdigest()
records=[];payloads=[];jobs=[]
for run in IDS:
 r=RUNS/str(run);ix=r/'original-artifact-hashes.json'
 if not ix.exists():jobs.append({'run':run,'evidence':'NOT_COLLECTED'});continue
 index=json.loads(ix.read_bytes());a=r/index['directory']
 for name,row in index['files'].items():
  p=a/name;b=p.read_bytes();assert len(b)==row['bytes'] and sha(b)==row['sha256'];payloads.append((p,row['sha256']))
 s=json.loads((a/'summary.json').read_bytes());assert s['run_id']==str(run) or s['run_id']==run
 assert s['complete'];jobs.append({'run':run,'source_commit':s['source_commit'],'complete':True,'artifact':str(a.relative_to(ROOT))})
 for row in s['results']:
  p=a/'inputs'/row['candidate']/'Kernel.lean';assert sha(p.read_bytes())==row['kernel_sha256']
  current=ROOT/'competitions/floatlib'/('references/official-incumbent/Kernel.lean' if row['candidate']=='baseline' else 'candidates/'+row['candidate']+'/Kernel.lean');assert sha(current.read_bytes())==row['kernel_sha256']
  v=json.loads((a/row['verdict']).read_bytes());full=row['full_gate'];mode=row.get('validation_mode','full-gate')
  rec={'run':run,'candidate':row['candidate'],'kernel_sha256':row['kernel_sha256'],'mode':mode,'full_gate':full,'stage':v.get('stage'),'passed':v.get('passed'),'reason':v.get('reason'),'seed':row['seed'],'ratio':None,'gain_p05':None,'formal_result':'NOT_SUBMITTED'}
  if full or row.get('benchmark_only_pass'):
   assert v['passed'] and v['stage']=='score' and v['verifier_fingerprint']==v['verifier_fingerprint_end'];assert len(v['classes'])==12 and len(v['rounds'])==25
   assert v['mode']==('gate' if full else 'bench')
   ratio=sum(x['submission_ns'] for x in v['classes'].values())/sum(x['incumbent_ns'] for x in v['classes'].values());assert abs(ratio-v['ratio'])<1e-10
   gain=support.gain_p05(v['rounds']);rec.update(ratio=ratio,gain_p05=gain,public_shipped_reference_bar_pass=bool(full and ratio<=.97 and gain>0))
   rec['kernels']={k:sum(x['submission_ns'] for n,x in v['classes'].items() if n.startswith(k+':'))/sum(x['incumbent_ns'] for n,x in v['classes'].items() if n.startswith(k+':')) for k in ['add','mul','sum','bmm']}
  records.append(rec)
groups={}
for name in sorted({x['candidate'] for x in records if x['candidate']!='baseline'}):
 xs=[x for x in records if x['candidate']==name and x['full_gate']];ys=[x['ratio'] for x in xs]
 groups[name]={'full_gate_runs':len(xs),'ratio_min':min(ys) if ys else None,'ratio_median':median(ys) if ys else None,'ratio_max':max(ys) if ys else None,'public_reference_bar_passes':sum(x.get('public_shipped_reference_bar_pass',False) for x in xs),'independent_confirmation':'Two frozen-source runs with distinct seeds/runners' if len(xs)>=2 else 'NOT_RUN'}
for p in CAND.glob('*/manifest.json'):
 m=json.loads(p.read_bytes());assert sha((p.parent/'Kernel.lean').read_bytes())==m['candidate_sha256']
git_audit=None
if '--git' in sys.argv:
 requests=b''.join(('HEAD:'+p.relative_to(ROOT).as_posix()+'\n').encode() for p,h in payloads);raw=subprocess.check_output(['git','cat-file','--batch'],input=requests);pos=0
 for p,h in payloads:
  end=raw.index(b'\n',pos);header=raw[pos:end].split();assert header[1]==b'blob';size=int(header[2]);pos=end+1;assert sha(raw[pos:pos+size])==h;pos+=size+1
 git_audit={'verified_payloads':len(payloads),'commit':subprocess.check_output(['git','rev-parse','HEAD'],text=True).strip()}
result={'goal':'Attempt the next live champion','goal_status':'UNACHIEVED; current champion direct comparison UNKNOWN','window_start_utc':'2026-10-21T08:10:19Z','window_end_utc':'2026-10-21T09:40:19Z','audited_at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'jobs':jobs,'payload_files_verified':len(payloads),'records':records,'candidate_statistics':groups,'git_byte_audit':git_audit,'scope':'All ratios here use exact shipped reference, not the live champion. Unproved bench rows cannot qualify for acceptance.'}
p=OWN/'summary.json';t=p.with_suffix('.json.tmp');t.write_bytes((json.dumps(result,ensure_ascii=False,indent=2)+'\n').encode());os.replace(t,p)
print(json.dumps({'collected_jobs':sum(x.get('complete',False) for x in jobs),'total_jobs':len(jobs),'payloads':len(payloads),'candidates':groups,'git_byte_audit':git_audit}))
