from pathlib import Path
from datetime import datetime,timezone
import json
HERE=Path(__file__).resolve().parent
now=datetime.now(timezone.utc).isoformat()
request='CI-REQUEST-14-PUBLIC23-NATIVE-COST.json'
candidate={'name':'public23-row-reciprocal-native-cost-v1','sha256':'c688f1074370dd1436e67e7691de027f231239c0a11357d63c2f06d2dbf6ce32','bytes':255415,'free_bytes':585,'state':'NATIVE_RESEARCH_ONLY_NO_NEW_CORRECT_NOT_COMPILED'}
for name in ['READY.json','status.json']:
    data=json.loads((HERE/name).read_text(encoding='utf-8'))
    data['updated_at_utc']=now;data['preferred']=request;data['request']=request
    data['cost_candidate']=candidate
    data['formal_parallel']='CI-REQUEST-13-PUBLIC23-RECIPROCAL.json; same9654b727/253499B candidate, immutable v3 recipe'
    data['processed_parent_request']='COMPACT23-NATIVE-COST-PRIORITY.json/22:26'
    data['state']='ACTUAL_PUBLIC23_NATIVE_COST_READY_SEPARATE_FORMAL_REPAIR'
    (HERE/name).write_text(json.dumps(data,indent=2)+'\n',encoding='utf-8')
text=(HERE/'HANDOFF.md').read_text(encoding='utf-8')
insert='''
**22:33 priority update:** Parent22:26 native-cost request accepted before22:45 target. `CI-REQUEST-14-PUBLIC23-NATIVE-COST.json`, recipe `public23_reciprocal_cost.py`/ecb0aea1 gives **255415B/c688f107…f6ce32**,585B free, policy PASS. Appends only small runtime provider/new norm caller, reuses existingm64, imports no large failedproof. Original theorem is explicitly `retainedCorrect:Obligation retainedKernels`; actual new `kernels` has **NO correct**. Native research screen only. Full formal9654b727 remains parallel, do not wait on it to buy actual wholemodel cost. Frozen v3 ownscope compactor fixes mutable cross-role recipe drift without changing9654 bytes.
'''
text=text.replace('# R27 native current handoff\n','# R27 native current handoff\n'+insert,1)
(HERE/'HANDOFF.md').write_text(text,encoding='utf-8')
print(now)
