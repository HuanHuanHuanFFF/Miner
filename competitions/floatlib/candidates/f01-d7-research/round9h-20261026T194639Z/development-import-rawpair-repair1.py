from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json

here = Path(__file__).resolve().parent
root = here.parents[4]
sha = lambda data: hashlib.sha256(data).hexdigest()
worker = here / 'development-workers/structural-cost/dc-decode-frontier/repair1'
source = worker / 'Kernel-dc-rawpair-repair1.draft.lean'
raw = source.read_bytes()
assert len(raw) == 235456 and sha(raw) == '6a0c18c52d736a1b8856877d6056372e13f70b095e36e34bd05203bcb7a5d1c0'
parent = root / 'competitions/floatlib/candidates/f01-r19-dev-dc-rawpair1'
manifest = json.loads((parent / 'manifest.json').read_bytes())
manifest.update(candidate='f01-r19-dev-dc-rawpair2', candidate_sha256=sha(raw), candidate_bytes=len(raw),
    created_at_utc=datetime.now(timezone.utc).isoformat(), parent=parent.name, parent_sha256=sha((parent / 'Kernel.lean').read_bytes()),
    proof_status='NOT_RUN_PROOF_ONLY_LOCAL_FUNCTION_EQUALITY_BRIDGE', performance='NOT_RUN',
    helper_audit_source_sha256=sha(raw), source_producer_path=source.relative_to(root).as_posix(), source_producer_sha256=sha(raw),
    repair_scope='Only row_prefix callback equality hgroup via funext/rfl, runtime/domain/specs/14roots unchanged; reverse patch restores8134')
target = root / 'competitions/floatlib/candidates' / manifest['candidate']
target.mkdir(exist_ok=False)
(target / 'Kernel.lean').write_bytes(raw)
(target / 'manifest.json').write_bytes((json.dumps(manifest, ensure_ascii=False, indent=2) + '\n').encode())
receipt = {'at_utc': manifest['created_at_utc'], 'candidate': manifest['candidate'], 'sha256': sha(raw), 'bytes': len(raw),
           'source': source.relative_to(root).as_posix(), 'scope': manifest['repair_scope']}
(here / 'development-rawpair-repair1-import.json').write_bytes((json.dumps(receipt, indent=2) + '\n').encode())
print(json.dumps(receipt))
