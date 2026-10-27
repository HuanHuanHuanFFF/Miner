from pathlib import Path
from hashlib import sha256
from datetime import datetime,timezone
import json,collections,random,statistics
D=Path(__file__).resolve().parent;R=next(p for p in D.parents if (p/'AGENTS.md').exists())
run=R/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40407333869'
idx=json.loads((run/'original-artifact-hashes.json').read_bytes());base=run/idx['directory']
assert idx['artifact']['workflow_run']['head_sha']=='76b1e7943924e0334ee38c62de6c188a11f20883'
bound=[]
for rel,m in idx['files'].items():
 p=base/rel;b=p.read_bytes();assert len(b)==m['bytes'] and sha256(b).hexdigest()==m['sha256'],rel
 bound.append({'path':str(p.relative_to(R)).replace('\\','/'),'bytes':len(b),'sha256':m['sha256']})
b=base/'diagnostics/f01-d7-public-suite/public-suite'
names=['f01-r19-dev-jam17-public1','f01-r15-dev-packed-b2-1'];expected=['b2710197d387bb22c4f0395f24d39543299965867b95cabb6965ce3df48f4bff','622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58']
plan=json.loads((b/'requested-plan.json').read_bytes());drawn=json.loads((b/'public-drawn-plan.json').read_bytes())
assert plan['seed']==1927005 and not plan.get('profile_parent') and not plan.get('profile_current')
assert all(not p.get('capture_codegen') for p in plan['candidates'])
work=collections.Counter()
for c in drawn['cases']:
 if c['timed']:work[c['name'].rsplit(':',1)[0]]+=c['work']
verdicts=[]
for n,h in zip(names,expected):
 inp=b/'inputs'/n/'Kernel.lean';assert sha256(inp.read_bytes()).hexdigest()==h
 v=json.loads((b/(n+'-verdict.json')).read_bytes());assert v['passed'] and v['mode']=='gate' and v['stage']=='score' and v['seed']==1927005
 assert len(v['rounds'])==25 and v['reference_complete'] and not v['incumbent_failed'] and not v['exhausted']
 assert v['verifier_fingerprint']==v['verifier_fingerprint_end'] and v['suite']['sha256']=='a16494e97c6a073bfd8accf72480c34534c87808092c56074fdcfa42cd34868a'
 assert set(v['classes'])==set(work)
 total={k:sum(v['classes'][c][k+'_ns']*w for c,w in work.items()) for k in ['submission','incumbent']}
 assert abs(total['submission']/total['incumbent']-v['ratio'])<1e-10
 verdicts.append(v)
assert verdicts[0]['verifier_fingerprint']==verdicts[1]['verifier_fingerprint']
values=[[sub/inc for inc,sub in v['rounds']] for v in verdicts];rng=random.Random(90423);gains=[]
for _ in range(2000):
 ms=[statistics.median(v[rng.randrange(25)] for _ in range(25)) for v in values];gains.append(1-ms[0]/ms[1])
gains.sort();k=.05*1999;lo=int(k);p05=gains[lo]+(gains[lo+1]-gains[lo])*(k-lo)
whole=verdicts[0]['ratio']/verdicts[1]['ratio'];ops={};cells={}
for op in ['add','mul','sum','bmm']:
 sums=[{kind:sum(v['classes'][c][kind+'_ns']*w for c,w in work.items() if c.startswith(op+':')) for kind in ['submission','incumbent']} for v in verdicts]
 ops[op]=(sums[0]['submission']/sums[0]['incumbent'])/(sums[1]['submission']/sums[1]['incumbent'])
for c in work:
 cells[c]=(verdicts[0]['classes'][c]['submission_ns']/verdicts[0]['classes'][c]['incumbent_ns'])/(verdicts[1]['classes'][c]['submission_ns']/verdicts[1]['classes'][c]['incumbent_ns'])
assert abs(whole-0.9988850281272739)<1e-12 and abs(p05+0.010814804174515524)<1e-12
out={'verified_utc':datetime.now(timezone.utc).isoformat(),'run':40407333869,'source_commit':'76b1e7943924e0334ee38c62de6c188a11f20883','status':'FULL_GATE_PASS_PERFORMANCE_NEGATIVE','original_files_verified':len(bound),'files':bound,'candidate':names[0],'candidate_sha256':expected[0],'baseline':names[1],'baseline_sha256':expected[1],'full_gate_both':True,'paired_rounds_each':25,'headline_classes_recomputed':True,'observers_disabled':True,'whole_vs_B2':whole,'gain_p05':p05,'per_operation_normalized':ops,'per_cell_normalized':cells,'bootstrap':'2000 draws,Random90423,candidate thenbaseline,medianpairedsub/inc,linear(n-1)*.05','adoption_screen_passed':False,'action':'Park exact b271 runtime; preserve allproof/fullgate evidence; noA/B, no seed-retry. Continue distinct directbias interface only.','gate_seconds_reported':{n:v['seconds'] for n,v in zip(names,verdicts)},'limitations':'Ratios are candidate/reference normalized againstB2/reference withinonebatch, not a directpaired candidate/B2 gate. One discovery only; no formalcompetition admission.'}
(D/'full-discovery-40407333869.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf8')
print(json.dumps({k:v for k,v in out.items() if k not in ['files','per_cell_normalized']},indent=2))
