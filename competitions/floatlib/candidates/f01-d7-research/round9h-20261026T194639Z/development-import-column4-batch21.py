from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json

HERE=Path(__file__).resolve().parent;ROOT=HERE.parents[4]
repair=HERE/'development-workers/astra-row-fusion/repair3'
sha=lambda raw:hashlib.sha256(raw).hexdigest()
entries=[('f01-r19-dev-column4-core4','f01-r19-dev-column4-core3','Kernel-core-repair3.lean',
          'c7e7ad380238b3a7e848b460c28fd6bbe6d4aa5c354b57483ef1243b91eb844a',249694),
         ('f01-r19-dev-column4-broad2','f01-r19-dev-column4-broad1','Kernel-column4-broad-retained-repair3.lean',
          'bb058c75f59ca36b4952cffae0c943fd296de02cb3e83d164409736b0252c061',255724)]
rows=[]
for name,parent,filename,expected,size in entries:
    source=repair/filename;raw=source.read_bytes()
    folder=ROOT/'competitions/floatlib/candidates'/parent
    old=(folder/'Kernel.lean').read_bytes()
    before=b'@[inline] def blocks (n : Nat) : Nat := (n+3)/4'
    after=b'@[inline] abbrev blocks (n : Nat) : Nat := (n+3)/4'
    assert old.count(before)==1 and raw==old.replace(before,after)
    assert sha(raw)==expected and len(raw)==size<=256000
    value=json.loads((folder/'manifest.json').read_bytes())
    value.update(candidate=name,candidate_sha256=expected,candidate_bytes=size,parent=parent,parent_sha256=sha(old),
        created_at_utc=datetime.now(timezone.utc).isoformat(),helper_audit_source_sha256=expected,
        source_producer_path=source.relative_to(ROOT).as_posix(),source_producer_sha256=expected,
        proof_status='NOT_RUN_REDUCIBLE_LENGTH_ALIAS_INTERFACE',performance='NOT_RUN',
        repair_scope='Only blocks def becomes abbrev; pure Nat RHS/inline/proof scripts/runtime expressions unchanged; fresh source gates required')
    value['explicit_helper_audit'].append('Submission.R19DualTemporal.blocks')
    value['helper_audit_expected_count']=len(value['explicit_helper_audit'])
    value['helper_audit_required_endpoints']=['Submission.bmm_spec','Submission.R19DualTemporal.blocks']
    target=ROOT/'competitions/floatlib/candidates'/name;target.mkdir(exist_ok=False)
    (target/'Kernel.lean').write_bytes(raw)
    (target/'manifest.json').write_bytes((json.dumps(value,ensure_ascii=False,indent=2)+'\n').encode())
    prior=json.loads((folder/'manifest.json').read_bytes())
    prior.update(proof_status='STATEMENT_IMPLICIT_FIN_VECTOR_LENGTH_ALIAS_TYPE_MISMATCH',statement_run=40443955689)
    (folder/'manifest.json').write_bytes((json.dumps(prior,ensure_ascii=False,indent=2)+'\n').encode())
    rows.append(dict(candidate=name,sha256=expected,bytes=size,roots=value['helper_audit_expected_count']))
(HERE/'development-column4-batch21-import.json').write_bytes((json.dumps(rows,indent=2)+'\n').encode())
print(json.dumps(rows))
