"""Repair only elaboration of the exact 808 special-dispatch statement probe."""
from pathlib import Path
import hashlib,json

root=Path(__file__).resolve().parents[1]
parent=root/'f01-d7-special-model'
raw=(parent/'Kernel.lean').read_bytes()
assert hashlib.sha256(raw).hexdigest()=='285ed400c999e0d1e5c227607550905bd0d98156170cb1122ee483f4359437af'
s=raw.decode()
for operation in ('Add','Mul'):
    old='  · unfold Model.Spec.'+operation.lower()+'\n'
    new='  · unfold model'+operation+' Model.Spec.'+operation.lower()+'\n'
    assert s.count(old)==2
    s=s.replace(old,new)
old='''  rw [TunedAdd.dec_eq, ← Model.NativeBinary32.toDyadic_eq]
  simp only [Model.NativeBinary32.toUInt32_ofUInt32]
  unfold Model.NativeBinary32.toDyadic?
  simp [hx]'''
new='''  have hw : Model.toDyadic? (Model.NativeBinary32.ofUInt32 x.raw.1) = none := by
    rw [← Model.NativeBinary32.toDyadic_eq]
    simp only [Model.NativeBinary32.toUInt32_ofUInt32]
    unfold Model.NativeBinary32.toDyadic?
    simp [hx]
  exact hw'''
assert s.count(old)==1;s=s.replace(old,new)
out=root/'f01-d7-special-model-proof1';out.mkdir(exist_ok=True)
data=s.encode();(out/'Kernel.lean').write_bytes(data)
m=json.loads((parent/'manifest.json').read_bytes())
m.update(candidate=out.name,candidate_sha256=hashlib.sha256(data).hexdigest(),candidate_bytes=len(data),parent=parent.name,parent_sha256=hashlib.sha256(raw).hexdigest(),proof_status='NOT_RUN_PROOF_REPAIR_AFTER_808',repair='Explicitly unfold both sides of model special branches. Establish toDyadic-none at the native descriptor before transporting definitionally to the codec descriptor; avoid ill-typed intermediate rw target. Runtime definitions unchanged; failed original retained.')
(out/'manifest.json').write_text(json.dumps(m,indent=2)+'\n',encoding='utf-8')
print(json.dumps({'candidate':out.name,'sha256':m['candidate_sha256'],'bytes':len(data)}))
