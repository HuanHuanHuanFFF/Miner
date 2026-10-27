"""Research-only checkpoint; preserve private UI evidence outside Git."""
from pathlib import Path
from hashlib import sha256
from datetime import datetime, timezone
import json

base=Path(__file__).resolve().parent; root=base.parents[4]
now=datetime.now(timezone.utc).isoformat()
shot=Path('C:/Users/幻/.codex/visualizations/2026/10/21/01a15e06-b75c-7811-b0a0-194d8877365d/r14-pro-limit-20261025.png')
cap=dict(checked_utc=now,state='PRO_DISABLED_USAGE_LIMIT_REACHED',
         observed_ui=['Locked, opens access options Usage limit reached','GPT-6','GPT-5.6 Sol selected','Pro disabled'],
         new_consultations_submitted=0,new_uploads=0,new_downloads=0,
         empty_temporary_tabs_closed=True,prior_completed_tabs_preserved=True,
         screenshot_local_path=str(shot),screenshot_sha256=sha256(shot.read_bytes()).hexdigest(),
         reset_time='UNKNOWN_IN_THIS_MENU',purchase_upgrade_or_reset=False,
         decision='No downgraded review presented as Pro. Continue independent math/source work; prior four raw downloads already curated.')
(base/'astra-web-pro-limit-20261025T0038Z.json').write_text(json.dumps(cap,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')

names=['astra-word-add-model-bridge1.lean','astra-word-add-boundary-screen.py',
       'astra-word-add-boundary-screen.json','astra-word-add-subdomain-opportunity.py',
       'astra-word-add-subdomain-opportunity.json','astra-general-bias-rne-draft.lean',
       'astra-general-bias-screen.py','astra-general-bias-screen.json',
       'astra-nearest-multiple-draft.lean','astra-far-add-nat-draft.lean',
       'astra-far-add-model-draft.lean','astra-add-wide-gap-opportunity.py',
       'astra-add-wide-gap-opportunity.json','astra-mul-edge-opportunity.py',
       'astra-mul-edge-opportunity.json','astra-proof-size-audit.py',
       'astra-proof-size-audit.json','astra-proof-size-audit.failed-v1.py',
       'astra-web-pro-limit-20261025T0038Z.json']
files=[]
for name in names:
    b=(base/name).read_bytes()
    files.append(dict(path=(base/name).relative_to(root).as_posix(),bytes=len(b),sha256=sha256(b).hexdigest()))
receipt=dict(timestamp_utc=now,state='RESEARCH_ACTIVE_NEW_MATH_DRAFTS_NOT_COMPILED',files=files,
             resource='All bounded local integer screens below0.1 seconds except preserved first scanner overrun4.87sec; no local Lean.',
             current_developer_support=dict(candidate='f01-r14-dev-word-add-support1',
                manifest_read_sha='69119fbd8c8a51c7b3e2ded092aaf9419219edf4aa8f2564e70a68acbe104cf8',
                bytes=254557,status='MANIFEST_OBSERVED_NOT_INDEPENDENTLY_ASSEMBLED_YET'),
             next='Independently validate exact developer support composition and fixed name/local-let repairs; retain optional far-gap math without expanding CI queue.')
(base/'astra-checkpoint-20261025T0040Z.json').write_text(json.dumps(receipt,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
status_path=base/'astra-status.json'; status=json.loads(status_path.read_text(encoding='utf-8'))
status['updated_at_utc']=now
status['next_action']=receipt['next']
status['web_pro_resources']['current_cap']='PRO_DISABLED_USAGE_LIMIT_REACHED_20261025T0038Z; zero new submissions/uploads'
status['web_pro_resources']['cap_receipt']='astra-web-pro-limit-20261025T0038Z.json'
status['web_pro_resources']['next_checkpoint']='No automatic retry while current menu explicitly disables Pro; continue math. Preserve prior four raw files, do not claim full Pro backend.'
for f in files:
    if f['path'] not in status['artifacts']:status['artifacts'].append(f['path'])
status['optional_math']={'generic_bias':'astra-general-bias-rne-draft.lean',
    'nearest_multiple':'astra-nearest-multiple-draft.lean',
    'far_gap':['astra-far-add-nat-draft.lean','astra-far-add-model-draft.lean'],
    'state':'PAPER_ONLY_NOT_COMPILED_NO_NEW_RUNTIME_OR_CI'}
temp=base/'astra-status.json.tmp';temp.write_text(json.dumps(status,ensure_ascii=False,indent=2)+'\n',encoding='utf-8');temp.replace(status_path)
print(json.dumps(dict(updated_at_utc=now,files=len(files),web=cap['state'],next=receipt['next']),ensure_ascii=False))
