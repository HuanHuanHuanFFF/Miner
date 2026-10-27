from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[4]
sha = lambda raw: hashlib.sha256(raw).hexdigest()
source = HERE / 'astra-workers/runtime-representation/grs-pre-guard-frontier/Kernel-grs32-pre-guard.lean'
raw = source.read_bytes()
assert len(raw) == 228686 and sha(raw) == 'd3c550da05a3e91b5b037bed77623545dbe72af385d826ebc73236d2ed7ec2b5'
parent = ROOT / 'competitions/floatlib/candidates/f01-r19-dev-grs-add-runtime2'
meta = json.loads((parent / 'manifest.json').read_bytes())
name = 'f01-r19-dev-grs-pre-guard1'
meta.update(candidate=name, candidate_sha256=sha(raw), candidate_bytes=len(raw),
    parent=parent.name, parent_sha256=sha((parent / 'Kernel.lean').read_bytes()),
    created_at_utc=datetime.now(timezone.utc).isoformat(), helper_audit_source_sha256=sha(raw),
    source_producer_path=source.relative_to(ROOT).as_posix(), source_producer_sha256=sha(raw),
    proof_status='NOT_RUN_NEW_PRE_GUARD_RUNTIME', performance='NOT_RUN',
    mechanism='One mathematically bounded pre-codec guard and delta pack; public entries remain exact B2. Cost discriminator only, no new ADD equality claim.')
target = ROOT / 'competitions/floatlib/candidates' / name
target.mkdir(exist_ok=False)
(target / 'Kernel.lean').write_bytes(raw)
(target / 'manifest.json').write_bytes((json.dumps(meta, ensure_ascii=False, indent=2) + '\n').encode())
print(json.dumps(dict(candidate=name, sha256=sha(raw), bytes=len(raw), roots=meta['helper_audit_expected_count'])))
