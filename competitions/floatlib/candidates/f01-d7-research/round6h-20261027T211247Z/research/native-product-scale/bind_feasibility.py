from pathlib import Path
from datetime import datetime,timezone
import hashlib,json
HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'AGENTS.md').exists())
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
paths={
 'R13_paper':ROOT/'competitions/floatlib/candidates/f01-d7-research/round3h-20261024T112622Z/astra-scale-fusion-feasibility.json',
 'R16_deferred_note':ROOT/'competitions/floatlib/candidates/f01-d7-research/round3h-20261025T091810Z/astra-workers/scalar-representation/cost-and-coverage.md',
 'R17_actual_runtime':ROOT/'competitions/floatlib/candidates/f01-d7-research/round11h-20261025T173831Z/astra-workers/structural-frontier/inline-u64-mul/Runtime-u64-mul-integer-v3-lf.lean.inc',
 'R17_full_source':ROOT/'competitions/floatlib/candidates/f01-r17-dev-u64-public2/Kernel.lean',
 'R21_scaled_runtime':ROOT/'competitions/floatlib/candidates/f01-d7-research/round1h-20261027T103538Z/research/scalar-frontier/Runtime-scaled-u32.lean.inc',
 'accepted_actual_product':HERE.parent/'scaled-mul/probe1-acceptance-40588875685.json',
}
r13=json.loads(paths['R13_paper'].read_text())
assert 'no candidate' in r13['scope'] and r13['finite_check']['cases']==8852
assert 'product.toFloat32.toUInt64' in paths['R17_actual_runtime'].read_text()
assert sha(paths['R17_full_source'])=='00ab99c7ff16a8f0f58c5a0b6ad5c87c10c2407589ee17c5f9cba444b7cfd080'
assert ').toUInt32' in paths['R21_scaled_runtime'].read_text()
actual=json.loads(paths['accepted_actual_product'].read_text())
assert actual['new_substantive_bridge_roots']==2 and actual['source_sha256'].startswith('6589f24d')
files=['Runtime.lean.inc','Kernel-probe1.lean','feasibility.md','directed-check.json']
out={'checked_utc':datetime.now(timezone.utc).isoformat(),'state':'PREMISE_AND_HISTORY_BOUND_COST_FIRST',
 'references':{k:{'path':str(p.relative_to(ROOT)).replace('\\','/'),'sha256':sha(p),'bytes':p.stat().st_size} for k,p in paths.items()},
 'current_files':{f:{'sha256':sha(HERE/f),'bytes':(HERE/f).stat().st_size} for f in files},
 'historical_scope':'R13 exactformula waspaper/modelonly; R16 explicitlydeferred; R17/R21 actualinspectedbodies reversecast. No samebodyfulltiming found in checkedmanifest/notes search, not a universalnovelty assertion.',
 'formal_gain_this_round':'6589 actualU64product decode accepted; its reverse-extraction runtime remains negative. Newsecondscale/syntheticword/fullMUL notproved.',
 'next':'Dcompletecallbackcost/selectedCfirst; no largeproof orCI fromB',
 'new_Lean':'NOT_RUN','performance':'UNKNOWN'}
(HERE/'feasibility-binding.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf-8')
print(json.dumps({k:v for k,v in out.items() if k!='references'},indent=2))
