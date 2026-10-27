"""Read-only recheck of the prior proof-leaf removal plan on the R22 probe."""
from pathlib import Path
import hashlib, json, re
from datetime import datetime, timezone

HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p/'AGENTS.md').exists())
plan_path = ROOT/'competitions/floatlib/candidates/f01-d7-research/round11h-20261025T173831Z/astra-workers/structural-frontier/integer-normal-mul/byte-budget-preview.json'
plan = json.loads(plan_path.read_text())
source = (HERE/'Kernel-probe1.lean').read_bytes()
rows = []
for old in plan['removed']:
    raw = source[old['start']:old['end']]
    count = len(re.findall(rb'(?<![A-Za-z_0-9])'+old['name'].encode()+rb'(?![A-Za-z_0-9])',source))
    rows.append({**old,'current_bytes_identical':hashlib.sha256(raw).hexdigest()==old['sha256'],
                 'current_name_occurrences':count,'eligible_now':count==1 and hashlib.sha256(raw).hexdigest()==old['sha256']})
assert all(r['eligible_now'] for r in rows)
result = {
    'checked_at_utc':datetime.now(timezone.utc).isoformat(),
    'status':'READ_ONLY_CAPACITY_RECHECK',
    'source_sha256':hashlib.sha256(source).hexdigest(),
    'source_bytes':len(source),'existing_margin':256000-len(source),
    'prior_plan_sha256':hashlib.sha256(plan_path.read_bytes()).hexdigest(),
    'eligible_proof_leaf_bytes':sum(r['bytes'] for r in rows),
    'prospective_margin':256000-len(source)+sum(r['bytes'] for r in rows),
    'rows':rows,
    'mutation':'NONE',
    'limitation':'Recheck on completed final source before removal; name occurrence check is not Lean elaboration, replay or an axiom audit.',
}
(HERE/'capacity-recheck.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf-8')
print(json.dumps({k:v for k,v in result.items() if k!='rows'},indent=2))
