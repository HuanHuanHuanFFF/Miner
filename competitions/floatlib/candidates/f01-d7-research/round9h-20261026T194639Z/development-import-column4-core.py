from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json

HERE=Path(__file__).resolve().parent
ROOT=HERE.parents[4]
worker=HERE/'development-workers/astra-row-fusion'
source=worker/'Kernel-core-probe.lean'
raw=source.read_bytes();digest=hashlib.sha256(raw).hexdigest()
assert digest=='8adff3a04e9f30b6416b4c192276d704b88ea20b34d2bbafcbaa6987d20df9ef' and len(raw)==249605
parent=ROOT/'competitions/floatlib/candidates/f01-r19-dev-dual-temporal-a4-5'
assert raw.startswith((parent/'Kernel.lean').read_bytes())
roots=[line.removeprefix('#print axioms ').strip() for line in (worker/'HelperAudit.lean.inc').read_text().splitlines() if line.strip()]
assert len(roots)==8
roots += ['Submission.add_spec','Submission.mul_spec','Submission.sum_spec','Submission.bmm_spec']
helper=HERE/'development-helper-audit-v5.py'
name='f01-r19-dev-column4-core1'
target=ROOT/'competitions/floatlib/candidates'/name;target.mkdir(exist_ok=False)
(target/'Kernel.lean').write_bytes(raw)
meta=dict(candidate=name,candidate_file='Kernel.lean',candidate_sha256=digest,candidate_bytes=len(raw),
    created_at_utc=datetime.now(timezone.utc).isoformat(),parent=parent.name,
    parent_sha256=hashlib.sha256((parent/'Kernel.lean').read_bytes()).hexdigest(),
    mechanism='One temporal B16/four-column core and equivalence to two parent pair loops; public entries remain c36, full packB/output integration not implemented',
    validation_mode='statement-only',proof_status='NOT_RUN',performance='NOT_RUN_CORE_PROBE_ONLY',
    explicit_helper_audit=roots,helper_audit_expected_count=len(roots),helper_audit_source_sha256=digest,
    helper_audit_required_endpoints=['Submission.R19Column4Temporal.runDot_pack_eq','Submission.bmm_spec'],
    helper_audit_module=helper.name,helper_audit_module_sha256=hashlib.sha256(helper.read_bytes()).hexdigest(),
    source_producer_path=source.relative_to(ROOT).as_posix(),source_producer_sha256=digest,
    formal_submission='NOT_SUBMITTED')
(target/'manifest.json').write_bytes((json.dumps(meta,ensure_ascii=False,indent=2)+'\n').encode())
print(json.dumps(dict(candidate=name,sha256=digest,bytes=len(raw),roots=len(roots))))
