from pathlib import Path
import json,hashlib
from datetime import datetime,timezone
H=Path(__file__).parent;ROOT=Path.cwd();O=ROOT/'competitions/torchlean/candidates/r26-1h-20261029T085515Z/research/key/follow-on'
fragments=[O/n for n in ['MidpointFields.lean.inc','MidpointRealDirect.lean.inc','MidpointSignedDirect.lean.inc']]
s=(H/'sources-v1/ActualCheckerContractOnly.lean').read_text(encoding='utf-8')+'\n'+'\n\n'.join(p.read_text(encoding='utf-8-sig')for p in fragments)
p=H/'boundary-v1/MidpointDirectContractOnly.lean';p.write_text(s,encoding='utf-8',newline='\n');b=p.read_bytes()
r=dict(at_utc=datetime.now(timezone.utc).isoformat(),state='PREPARED_PENDING_ACTUAL_CHECKER',name='MidpointDirectContractOnly',path=p.relative_to(ROOT).as_posix(),bytes=len(b),sha256=hashlib.sha256(b).hexdigest(),helper_roots=['Submission.R25Checker.unsigned_midpoint_values','Submission.R25Checker.signed_midpoint_values','Submission.R25Checker.eWord_eq_native','Submission.R25Checker.fWord_eq_native'],dependencies='RealStrict exacte004 accepted; actualchecker24KB pending; no finitewiden producer dependency',source_origins=[dict(path=p.relative_to(ROOT).as_posix(),sha256=hashlib.sha256(p.read_bytes()).hexdigest())for p in fragments],proof='NOT_RUN',finite_model_boundary='R26 existing3048word/6096endpoint model not promoted to Lean',formal_submission=False)
(H/'boundary-v1/midpoint-receipt.json').write_text(json.dumps(r,indent=2)+'\n',encoding='utf-8')
p=H/'BATCH3-HELPER-BUNDLE.json';d=json.loads(p.read_bytes());d['next_after_checker']=r;p.write_text(json.dumps(d,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps(r,indent=2))
