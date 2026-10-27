from pathlib import Path
from datetime import datetime,timezone
import hashlib,json
H=Path(__file__).resolve().parent;R=H.parents[3]
s=json.loads((H/'research-status.json').read_text(encoding='utf-8'));w=json.loads((H/'web-deliveries.json').read_text(encoding='utf-8'))
sources=[]
for x in s['ready_candidates']:
 p=R/x['kernel'];b=p.read_bytes();assert hashlib.sha256(b).hexdigest()==x['sha256'];assert len(b)==x['bytes']
 sources.append({'candidate':x['candidate'],'path':str(p.resolve()),'sha256':x['sha256'],'bytes':len(b),'requested_mode':x['mode'],'proof_status':x['proof_status'],'manifest':str(p.with_name('manifest.json').resolve()),'manifest_sha256':hashlib.sha256(p.with_name('manifest.json').read_bytes()).hexdigest()})
downloads=[]
for d in w['deliveries']:
 for f in d['files']:
  p=Path(f['path']);b=p.read_bytes();assert hashlib.sha256(b).hexdigest()==f['sha256']
  downloads.append({'job':d['job'],'kind':f['kind'],'path':str(p),'bytes':len(b),'sha256':f['sha256'],'receipt':str((H/d['receipt']).resolve())})
out={'snapshot_utc':datetime.now(timezone.utc).isoformat(),'state':'PREVIEW_WINDOW_STILL_ACTIVE','authoritative_R_state':str((H/'research-status.json').resolve()),'D_handoff_protocol':str((R/'competitions/floatlib/coordination/astra-handoff-r7.md').resolve()),'deadline_utc':s['deadline_utc'],'runtime_freeze_utc':s['runtime_source_freeze_utc'],'new_goal_achieved':False,'candidate_sources':sources,'downloaded_originals':downloads,'download_jobs':len(w['deliveries']),'download_main_files':len(downloads),'scope':'ConcretefilemanifestforD; no publicupload/formalsubmission/funds. D ownsGit/CI/integration. No acceptance beyondexactrecordedsource/status. OriginalEZIP/report andfailed evidencepreserved. Private candidate sources staylocal untilthealreadyasked specificpublicpush authorization.'}
(H/'handoff-materials-preview.json').write_text(json.dumps(out,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps({'sources':len(sources),'web_jobs':out['download_jobs'],'main_files':len(downloads),'deadline':s['deadline_utc'],'state':out['state']}))
