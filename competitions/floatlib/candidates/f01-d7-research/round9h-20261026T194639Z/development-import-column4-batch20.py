from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json

HERE=Path(__file__).resolve().parent;ROOT=HERE.parents[4]
repair=HERE/'development-workers/astra-row-fusion/repair2'
sha=lambda raw:hashlib.sha256(raw).hexdigest()
helper=HERE/'development-helper-audit-v5.py'
old_root=ROOT/'competitions/floatlib/candidates/f01-r19-dev-column4-core2'
old_meta=json.loads((old_root/'manifest.json').read_bytes())
audit=HERE/'development-workers/astra-row-fusion/broad-draft/HelperAudit.lean.inc'
broad_roots=[line.removeprefix('#print axioms ').strip() for line in audit.read_text().splitlines() if line.strip()]
assert len(broad_roots)==19
entries=[
 ('f01-r19-dev-column4-core3','Kernel-core-repair2.lean','036372fd3fdca079ef36e6ee2773c9ce27d8aeddc3f29d01257772f29c931e20',249691,
  old_meta['explicit_helper_audit'],old_root.name,'Normalize both dependent Fin sizes before the two pack proof simplifications; runtime/public entries unchanged'),
 ('f01-r19-dev-column4-broad1','Kernel-column4-broad-retained-repair2.lean','386b5fec7a2595b1fa7e47b283abb3bdbd75066a4591ab3a5740e1cf0106741d',255721,
  broad_roots,'f01-r15-dev-packed-b2-1','Broad B16/A4 four-column entry; exact retained B2 fallback restored, unused R19 outer shells removed; all lifecycle costs retained')]
rows=[]
for name,filename,expected,size,roots,parent,mechanism in entries:
    source=repair/filename;raw=source.read_bytes()
    assert sha(raw)==expected and len(raw)==size<=256000 and b'\r' not in raw
    base=ROOT/'competitions/floatlib/candidates'/parent
    target=ROOT/'competitions/floatlib/candidates'/name;target.mkdir(exist_ok=False)
    (target/'Kernel.lean').write_bytes(raw)
    value=dict(candidate=name,candidate_file='Kernel.lean',candidate_sha256=expected,candidate_bytes=size,
        created_at_utc=datetime.now(timezone.utc).isoformat(),parent=parent,parent_sha256=sha((base/'Kernel.lean').read_bytes()),
        mechanism=mechanism,validation_mode='statement-only',proof_status='NOT_RUN',performance='NOT_RUN',
        explicit_helper_audit=roots,helper_audit_expected_count=len(roots),helper_audit_source_sha256=expected,
        helper_audit_required_endpoints=['Submission.bmm_spec', roots[-1]],helper_audit_module=helper.name,
        helper_audit_module_sha256=sha(helper.read_bytes()),source_producer_path=source.relative_to(ROOT).as_posix(),
        source_producer_sha256=expected,formal_submission='NOT_SUBMITTED')
    if 'broad' in name:
        value.update(runtime_guard='m>0,n>1,p>=3 and equal ceil padded width vs pairs; outer UnderflowZero preserved',
            fallback='R15PackedB2.dispatch exact retained namespace restored',
            cost_caveat='New DC/other routes add A4/B16 preparation, residency, destruction; DC odd p adds one phantom MAC lane. No free reuse or speed claim.')
    (target/'manifest.json').write_bytes((json.dumps(value,ensure_ascii=False,indent=2)+'\n').encode())
    rows.append(dict(candidate=name,sha256=expected,bytes=size,roots=len(roots)))
old_meta.update(proof_status='STATEMENT_TWO_PACK_REWRITE_IMPLICIT_FIN_TYPE_MISMATCH',statement_run=40442288468)
(old_root/'manifest.json').write_bytes((json.dumps(old_meta,ensure_ascii=False,indent=2)+'\n').encode())
(HERE/'development-column4-batch20-import.json').write_bytes((json.dumps(rows,indent=2)+'\n').encode())
print(json.dumps(rows))
