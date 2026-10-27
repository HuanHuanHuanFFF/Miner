from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json

HERE=Path(__file__).resolve().parent; ROOT=HERE.parents[4]
source=HERE/'development-workers/astra-row-fusion/repair1/Kernel-core-repair1.lean'
raw=source.read_bytes(); sha=lambda data:hashlib.sha256(data).hexdigest()
assert sha(raw)=='118d8efc9e8c3d92189913c0aae3d66bca1394a677ec09957174c9d9e97eb1fc' and len(raw)==249625
parent=ROOT/'competitions/floatlib/candidates/f01-r19-dev-column4-core1'
value=json.loads((parent/'manifest.json').read_bytes())
name='f01-r19-dev-column4-core2'
value.update(candidate=name,candidate_sha256=sha(raw),candidate_bytes=len(raw),parent=parent.name,
    parent_sha256=sha((parent/'Kernel.lean').read_bytes()),created_at_utc=datetime.now(timezone.utc).isoformat(),
    helper_audit_source_sha256=sha(raw),source_producer_path=source.relative_to(ROOT).as_posix(),
    source_producer_sha256=sha(raw),proof_status='NOT_RUN_TWO_PACK_BRIDGE_REPAIRS_ONLY',
    repair_scope='Only pack_low/pack_high proof scripts use existing pack_get before simplifying; runtime/public entries unchanged')
target=ROOT/'competitions/floatlib/candidates'/name;target.mkdir(exist_ok=False)
(target/'Kernel.lean').write_bytes(raw)
(target/'manifest.json').write_bytes((json.dumps(value,ensure_ascii=False,indent=2)+'\n').encode())
old=json.loads((parent/'manifest.json').read_bytes())
old.update(proof_status='STATEMENT_TWO_UNSOLVED_PACK_LOW_HIGH_GOALS',statement_run=40440668379)
(parent/'manifest.json').write_bytes((json.dumps(old,ensure_ascii=False,indent=2)+'\n').encode())
print(json.dumps(dict(candidate=name,sha256=sha(raw),bytes=len(raw),roots=value['helper_audit_expected_count'])))
