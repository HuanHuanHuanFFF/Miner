from pathlib import Path
import hashlib,json
from datetime import datetime,timezone
ROOT=Path(__file__).resolve().parents[4];HERE=Path(__file__).resolve().parent
base=ROOT/'competitions/floatlib/candidates/f01-r6-web-lowguards/Kernel.lean'
b=base.read_bytes(); assert hashlib.sha256(b).hexdigest()=='75ddbcff076c7fe17ba3d38616025eec9b74d647fe711ed6d77459454d3fbdbf'
s=b.decode()
w1b=HERE/'web/R6-W01b/original-extracted/R6-W01b/ParentWithBridge.lean'
bridge=w1b.read_bytes()
parent=(ROOT/'competitions/floatlib/candidates/f01-d5-stream-pack/Kernel.lean').read_bytes()
assert bridge.startswith(parent)
append=bridge[len(parent):].decode()
assert 'theorem active_roundLowBits_eq_roundP' in append
idx=s.index('namespace R6Domain')
s=s[:idx]+'end Submission\n\n'+append+'\nnamespace Submission\n\n'+s[idx:]
old='''  if s ≤ (123 : UInt64) then LowScale.roundLow sign p s
  else FastMul.roundP sign p s'''
new='''  if s ≤ (123 : UInt64) then
    if (101 : UInt64) ≤ s then R6BiasRuntime.roundLowBits sign p s
    else LowScale.roundLow sign p s
  else FastMul.roundP sign p s'''
assert s.count(old)==1;s=s.replace(old,new)
a=s.index('theorem core_eq (a b : UInt32)',s.index('namespace R6Domain'))
z=s.index('/-- The outer exponent sum',a)
newproof='''theorem core_eq (a b : UInt32) : core a b = FastMul.core a b := by
  unfold core FastMul.core
  dsimp only
  split
  · rename_i hs
    have hsNat := hs
    rw [UInt64.le_iff_toNat_le] at hsNat
    split
    · rename_i hlo
      apply R6BiasBridge.active_roundLowBits_eq_roundP
      · exact product_lt a b
      · rw [UInt64.le_iff_toNat_le] at hlo
        exact hlo
      · exact hsNat
    · apply LowScale.roundLow_eq
      · exact product_lt a b
      · exact hsNat
  · rfl

'''
s=s[:a]+newproof+s[z:]
out=s.encode();d=ROOT/'competitions/floatlib/candidates/f01-r6-active-bias';d.mkdir(exist_ok=True)
(d/'Kernel.lean').write_bytes(out)
m={'candidate':d.name,'candidate_file':'Kernel.lean','candidate_sha256':hashlib.sha256(out).hexdigest(),'candidate_bytes':len(out),'parent':'f01-r6-web-lowguards','parent_sha256':hashlib.sha256(b).hexdigest(),'proof_bridge_source':str(w1b.relative_to(ROOT)).replace('\\','/'),'proof_bridge_sha256':hashlib.sha256(bridge).hexdigest(),'validated_ancestor':'f01-d5-stream-pack 8eb63a2fea39f8c483eb16857cb1dcc35ac4a30168ab91046a48aa1cb561e045','created_at_utc':datetime.now(timezone.utc).isoformat(),'proof_status':'NOT_RUN','validation_mode':'full-gate','mechanism':'On scale101..123 use exact bias RN-even and direct sign-or-fraction packing; scales<=100 preserve old roundLow, larger scales preserve old roundP. Reuse web product-width proof to avoid runtime width guard. Parent special dispatch and native high-exponent route retained.','expected_gain':'UNKNOWN; legacy tiny fully active but new public-v2/paid suite exposure differs. Whole-call cost and full gate required.','formal_submission':'NOT_SUBMITTED'}
(d/'manifest.json').write_text(json.dumps(m,indent=2)+'\n');print(json.dumps(m,indent=2))
