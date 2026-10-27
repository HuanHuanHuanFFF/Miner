from pathlib import Path
from datetime import datetime,timezone
import hashlib,json
H=Path(__file__).resolve().parent;R=H.parents[3]
now=datetime.now(timezone.utc);scheduled=datetime.fromisoformat('2026-10-23T02:45:00+00:00')
assert now>=scheduled,'Scheduledfreezehasnotarrived; no statechange'
target=H/'runtime-source-freeze.json';assert not target.exists(),'Existingfreeze receipt preserved'
s=json.loads((H/'research-status.json').read_text(encoding='utf-8'));rows=[]
for x in s['ready_candidates']:
 p=R/x['kernel'];b=p.read_bytes();sha=hashlib.sha256(b).hexdigest();assert sha==x['sha256'] and len(b)==x['bytes']
 rows.append({'candidate':x['candidate'],'kernel':str(p.resolve()),'bytes':len(b),'sha256':sha,'proof_status':x['proof_status'],'intended_mode':x['mode']})
controls=[]
for name,expected in [('f01-r7-nonnan-runtime','c76056882d69a1122da44b4bc0bb3ab5274251826f0677af2aec5771926d7435'),('f01-r7-nan-replay-fullpath','9a2a05cd8e033d3cc079744ade77dd42464926d04ef5c9a8e7c050a1605ec854'),('f01-d7-direct-nonnan','60f74aa4af01a9b35ece66a7c310e6b05b5b84b9b7121a4cccd12a0a9c987e15')]:
 p=R/'competitions/floatlib/candidates'/name/'Kernel.lean';b=p.read_bytes();assert hashlib.sha256(b).hexdigest()==expected;controls.append({'candidate':name,'sha256':expected,'bytes':len(b),'role':'Previouslyfullpublicgateacceptedreference,read-onlysnapshot; notnewchampionacceptance'})
out={'scheduled_freeze_utc':scheduled.isoformat(),'frozen_at_utc':now.isoformat(),'R_sources':rows,'accepted_references_readonly':controls,'current_web_index_sha256':hashlib.sha256((H/'web-deliveries.json').read_bytes()).hexdigest(),'sources_modified_by_freeze':False,'goal_achieved':False,'scope':'Records exactcurrentR runtime sources atpreagreedfreeze. No filesystemlocks, Git, upload, CI, orformalcontestaction. Newsourceacceptance/performance remainasrecorded; laterproof/verificationrepairs require explicitnewreceipt andmustnotreusefrozenhashclaims.'}
target.write_text(json.dumps(out,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
s.update(state='R7_RUNTIME_SOURCES_FROZEN_VALIDATION_AND_HANDOFF_ONLY',updated_at_utc=now.isoformat(),runtime_freeze_receipt=target.name,next_checkpoint_utc='2026-10-23T03:15:00Z')
(H/'research-status.json').write_text(json.dumps(s,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps({'frozen_at_utc':out['frozen_at_utc'],'R_sources':len(rows),'accepted_reference_snapshots':len(controls),'goal_achieved':False}))
