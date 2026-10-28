from pathlib import Path
from datetime import datetime,timezone
import hashlib,json,re

HERE=Path(__file__).resolve().parent
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
files=['FlatScaleBridge.lean.inc','SmallPickDiscriminator.lean.inc','proof-map.md','source-shape-check.json','namespace-repair-binding.json']
roots=[]
for f in files[:2]:
    roots += ['Submission.R22FlatScale.'+r for r in re.findall(r'^theorem ([A-Za-z0-9_]+)',(HERE/f).read_text(),re.M)]
(HERE/'HelperAudit.lean.inc').write_text(''.join('#print axioms '+r+'\n' for r in roots),encoding='utf-8')
files+=['HelperAudit.lean.inc']
out={
 'created_utc':datetime.now(timezone.utc).isoformat(),'state':'MINIMAL_CONDITIONAL_BRIDGE_READY_NOT_RUN',
 'start_utc':'2026-10-27T22:29:43Z','shared_deadline_utc':'2026-10-28T03:12:47Z',
 'runtime_sha256':'82ebf77c97d26d3ccfc0b9c085ec47cb5a140803233141a8d1e00bcfc5fda63f',
 'current_D_carrier_sha256':'ef1fa46164ecce62cb27c7f101d488eff386c03f21c19636760832f79c04926b',
 'repaired_component_sha256':'f5fbc6d85d18ebfacabd1ac19a65633f1c973459b057673c8f85bb4320c28b44',
 'files':{f:{'sha256':sha(HERE/f),'bytes':(HERE/f).stat().st_size} for f in files},
 'explicit_helper_audit':roots,'root_count':len(roots),
 'block_equations':'Four explicit unproved premises, each all128slots; no512case proof generated.',
 'small_discriminator':'block0 first4 slots plusblock3 lastslot,2theorems/5literal leaves,NOT_RUN',
 'future_compact_route':'Proof-only blockOfFn and single128case projection helper, thenfour rfl block identities; waitselectorcost beforegeneration.',
 'new_Lean':'NOT_RUN','selector_C_ASM':'D_PENDING','complete_cost':'UNKNOWN',
 'public_candidate':False,'CI':False,'local_Lean':False,
}
(HERE/'manifest.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf-8')
print(json.dumps({k:v for k,v in out.items() if k!='explicit_helper_audit'},indent=2))
