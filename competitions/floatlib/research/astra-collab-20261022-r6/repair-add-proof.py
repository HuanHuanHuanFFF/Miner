from pathlib import Path
import json,hashlib
from datetime import datetime,timezone
ROOT=Path(__file__).resolve().parents[4]
for name in ['f01-r6-fused-add','f01-r6-normal-add']:
    d=ROOT/'competitions/floatlib/candidates'/name
    b=(d/'Kernel.lean').read_bytes();s=b.decode()
    if name.endswith('fused-add'):
        old='''    have hx := (Bool.and_eq_true.mp h).1
    have hy := (Bool.and_eq_true.mp h).2'''
        new='''    simp only [Bool.and_eq_true] at h
    have hx := h.1
    have hy := h.2'''
    else:
        old='''    have hx := R6NormalAdd.fastOK_of_normalOK _ (Bool.and_eq_true.mp h).1
    have hy := R6NormalAdd.fastOK_of_normalOK _ (Bool.and_eq_true.mp h).2'''
        new='''    simp only [Bool.and_eq_true] at h
    have hx := R6NormalAdd.fastOK_of_normalOK _ h.1
    have hy := R6NormalAdd.fastOK_of_normalOK _ h.2'''
    assert s.count(old)==1
    out=s.replace(old,new).encode()
    dest=d.with_name(name+'-proof1');dest.mkdir(exist_ok=True)
    (dest/'Kernel.lean').write_bytes(out)
    m=json.loads((d/'manifest.json').read_text())
    m.update(candidate=dest.name,candidate_sha256=hashlib.sha256(out).hexdigest(),candidate_bytes=len(out),parent=name,parent_sha256=hashlib.sha256(b).hexdigest(),proof_status='NOT_RUN',created_at_utc=datetime.now(timezone.utc).isoformat(),repair='Actual704 statement failure: Bool.and_eq_true.mp unknown. Use simp only [Bool.and_eq_true] at h then projections. Runtime definition unchanged. Original failed source retained.')
    (dest/'manifest.json').write_text(json.dumps(m,indent=2)+'\n')
    print(json.dumps(m,indent=2))
