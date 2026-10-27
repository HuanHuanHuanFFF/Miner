from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json

HERE=Path(__file__).resolve().parent;ROOT=HERE.parents[4]
sha=lambda raw:hashlib.sha256(raw).hexdigest()
parent=ROOT/'competitions/floatlib/candidates/f01-r19-dev-column4-broad2'
source=HERE/'development-workers/structural-cost/b16-bbase-hoist/Kernel-bbase-hoist.draft.lean'
raw=source.read_bytes()
assert len(raw)==255745 and sha(raw)=='f49458b99475b1b7e4a368908c81590b7f357a06938f38d0df141ffa3df5dc5d'
value=json.loads((parent/'manifest.json').read_bytes())
for field in ('statement_run','proof_evidence','first_discovery','first_discovery_evidence','full_gate','full_performance_gate'):
    value.pop(field,None)
name='f01-r19-dev-column4-bbase1'
value.update(candidate=name,candidate_sha256=sha(raw),candidate_bytes=len(raw),parent=parent.name,
    parent_sha256=sha((parent/'Kernel.lean').read_bytes()),created_at_utc=datetime.now(timezone.utc).isoformat(),
    helper_audit_source_sha256=sha(raw),source_producer_path=source.relative_to(ROOT).as_posix(),source_producer_sha256=sha(raw),
    proof_status='NOT_RUN_PURE_LET_BBASE_CACHE',performance='NOT_RUN',source_adoption='NOT_ADOPTED',
    mechanism='Cache B base exactly once after runDot and before emit; callback uses baseB+j; all proof text and other runtime expressions unchanged',
    full_gate='NOT_RUN')
target=ROOT/'competitions/floatlib/candidates'/name;target.mkdir(exist_ok=False)
(target/'Kernel.lean').write_bytes(raw)
(target/'manifest.json').write_bytes((json.dumps(value,ensure_ascii=False,indent=2)+'\n').encode())
old=json.loads((parent/'manifest.json').read_bytes())
result_path=HERE/'result-1927022-f01-r19-dev-column4-broad2-vs-f01-r15-dev-packed-b2-1.json'
result=json.loads(result_path.read_bytes())
assert result['full_gate_both'] and not result['local_discovery_screen_passed']
old.update(full_gate='PASS',performance='FIRST_D_BELOW_ADOPTION_THRESHOLD_NO_RESEED',
    first_discovery={key:result[key] for key in ('run','seed','relative_normalized_ratio','gain_p05','per_operation_normalized','local_discovery_screen_passed')},
    first_discovery_evidence=dict(path=result_path.relative_to(ROOT).as_posix(),sha256=sha(result_path.read_bytes())))
(parent/'manifest.json').write_bytes((json.dumps(old,ensure_ascii=False,indent=2)+'\n').encode())
print(json.dumps(dict(candidate=name,sha256=sha(raw),bytes=len(raw),roots=value['helper_audit_expected_count'])))
