from pathlib import Path
import json,hashlib
from datetime import datetime,timezone
H=Path(__file__).parent;ROOT=Path.cwd()
cur=json.loads((H/'CI-REQUEST.json').read_bytes());num=json.loads((H/'CI-REQUEST-003.json').read_bytes());prep=json.loads((H/'producer-v2/repair-receipt.json').read_bytes());finite=json.loads((H/'CI-REQUEST-002.json').read_bytes());rounder=json.loads((H/'rounder-v1/receipt.json').read_bytes())
rows=[cur['candidates'][0],next(x for x in finite['candidates'] if x['name']=='FiniteWidenContractOnly'),next(x for x in prep['sources'] if x['name']=='PreparePeakContractOnly')]
rows += [x for x in num['candidates'] if x['name'] in ['Sum3ContractOnly','RadiusContractOnly','NativeMulContractOnly']]
rows += [dict(name='RounderPrimitivesContractOnly',path=rounder['path'],bytes=rounder['bytes'],sha256=rounder['sha256'],helper_roots=rounder['helper_roots'])]
for r in rows:
 b=(ROOT/r['path']).read_bytes();assert hashlib.sha256(b).hexdigest()==r['sha256'];r['seconds']=120
r=dict(at_utc=datetime.now(timezone.utc).isoformat(),state='SCHEDULING_OPTION_NOT_DISPATCHED',owner='fp-proof',executor='Droot',purpose='After batch2 feedback, diagnose7independent small proof blocks in onepublicrunner rather than delaying every independent block until the final160KBclosure. Each source<=38493B. Do not queue knownbroken Realprefix unchanged if batch2 exposes one; update exact dependent hashes first.',helpers=rows,aggregate_helper_budget_seconds=600,cap_enforced_by_executor='UNKNOWN_Droot_decision',runtime_per_helper_seconds='UNKNOWN; firstbatch logs omit individual helpertimings',allow_private=False,local_build=False,full_gate=False,measurement=False,priority='Optional after active norm batch; main current request remains CI-REQUEST.json, D selects by throughput',independent_of_real=['FiniteWidenContractOnly','PreparePeakContractOnly','Sum3ContractOnly','RadiusContractOnly','NativeMulContractOnly','RounderPrimitivesContractOnly'])
(H/'BATCH3-HELPER-BUNDLE.json').write_text(json.dumps(r,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
with (H/'HANDOFF.md').open('a',encoding='utf-8') as f:f.write('\n可选吞吐方案（未派发）：`BATCH3-HELPER-BUNDLE.json`把7块互相独立的13–38KB证明放同一publicrunner顺序诊断，总cap600s供D选择；避免等到最终大闭包才发现无关错误。batch2若Real失败，先修共享前缀再选guarded块；其余6块不依赖Real。\n')
print(json.dumps({'helper_names':[x['name'] for x in rows],'bytes':[x['bytes'] for x in rows],'state':r['state']},indent=2))
