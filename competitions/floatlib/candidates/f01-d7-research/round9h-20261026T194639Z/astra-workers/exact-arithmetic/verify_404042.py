from pathlib import Path
from hashlib import sha256
from datetime import datetime,timezone
import json,re
D=Path(__file__).resolve().parent
R=next(p for p in D.parents if (p/'AGENTS.md').exists())
run=R/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40404258098'
index=json.loads((run/'original-artifact-hashes.json').read_bytes());base=run/index['directory']
assert index['artifact']['workflow_run']['head_sha']=='ba0602feb3863d16302c37fce2c225d378c48717'
names={'f01-r19-dev-jam17-probe2':('12341d5b5ddaa82e234a6da3ac1868a59634c9d99d6f6c621d4ee413a315b182',D/'repair1/Probe-jam17-repair1.lean',12),'f01-r19-dev-jam17-public1':('b2710197d387bb22c4f0395f24d39543299965867b95cabb6965ce3df48f4bff',D/'repair1/Kernel-jam17-public-repair1-parser.lean',40)}
bound=[]
for rel,meta in index['files'].items():
 if not any(n in rel for n in names):continue
 p=base/rel;b=p.read_bytes();assert len(b)==meta['bytes'] and sha256(b).hexdigest()==meta['sha256'],rel
 bound.append({'path':str(p.relative_to(R)).replace('\\','/'),'bytes':len(b),'sha256':meta['sha256']})
prefix=base/'diagnostics/f01-d7-public-suite/public-suite';rows=[]
for name,(expected,local,count) in names.items():
 inp=prefix/'inputs'/name/'Kernel.lean';assert inp.read_bytes()==local.read_bytes();assert sha256(inp.read_bytes()).hexdigest()==expected
 verdict=prefix/(name+'-verdict.json');v=json.loads(verdict.read_bytes());diag=prefix/'diagnostics'/name
 audit=diag/'helper-audit.json';a=json.loads(audit.read_bytes());log=(diag/'replay.log').read_text(encoding='utf8')
 assert v['passed'] and v['stage']=='helper-axioms' and v.get('ratio') is None and not v.get('rounds')
 assert a['kernel_sha256']==expected and a['accepted'] and a['kernel_replay'] and a['exit_code']==0
 assert len(a['names'])==a['expected_count']==count and len(a['reports'])==count and set(a['names'])==set(a['reports'])
 assert all(set(x)<= {'Classical.choice','Quot.sound','propext'} for x in a['reports'].values())
 assert 'Submission replays cleanly' in log and 'VerifyFull replays cleanly' in log
 if name.endswith('public1'):
  requested=[line.split('#print axioms ',1)[1] for line in (D/'HelperAudit-public-jam17.lean.inc').read_text().splitlines() if line.startswith('#print axioms ')]
  assert a['names']==requested
 else:
  requested=[line.split('#print axioms ',1)[1] for line in (D/'HelperAudit-jam17.lean.inc').read_text().splitlines() if line.startswith('#print axioms ')]
  assert set(requested)<=set(a['names'])
 rows.append({'candidate':name,'kernel_sha256':expected,'bytes':inp.stat().st_size,'statement':'PASS','Submission_and_VerifyFull_replay':'PASS','explicit_axiom_roots':count,'allowed_axioms_only':True,'requested_roots_covered':True,'verdict_sha256':sha256(verdict.read_bytes()).hexdigest(),'helper_audit_sha256':sha256(audit.read_bytes()).hexdigest(),'replay_log_sha256':sha256((diag/'replay.log').read_bytes()).hexdigest(),'full_gate':'NOT_RUN','performance':'NOT_RUN'})
out={'verified_utc':datetime.now(timezone.utc).isoformat(),'run':40404258098,'source_commit':'ba0602feb3863d16302c37fce2c225d378c48717','status':'VERIFIED_SELECTED_ORIGINAL_ARTIFACTS','files_verified':len(bound),'files':bound,'sources':rows,'scope':'Exact two Jam17 sources and their raw original artifacts; statement/replay/explicit allowed-axiom audit only. No performance/checksum/full gate inferred.'}
(D/'verified-40404258098.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf8')
print(json.dumps({k:v for k,v in out.items() if k!='files'},indent=2))
