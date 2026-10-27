from pathlib import Path
import hashlib,json
from datetime import datetime, timezone
ROOT=Path(__file__).resolve().parents[4]
HERE=Path(__file__).resolve().parent
p=ROOT/'competitions/floatlib/candidates/f01-d5-stream-pack/Kernel.lean'
b=p.read_bytes()
assert hashlib.sha256(b).hexdigest()=='8eb63a2fea39f8c483eb16857cb1dcc35ac4a30168ab91046a48aa1cb561e045'
s=b.decode()
fast=s[s.index('namespace FastMul'):s.index('end FastMul')]
r=fast[fast.index('@[inline] def roundP'):fast.index('/-- The word multiplication\'s finite path')]
r=r.replace('let leading := fastLog2 product','let leading := R6NormalMul.leading product').replace('rseAny ', 'FastMul.rseAny ').replace('mkW ', 'FastMul.mkW ').replace('fracW ', 'FastMul.fracW ')
c=fast[fast.index('@[inline] def core'):fast.index('/-- One operand is a NaN')]
block=(HERE/'normal-log2-block.lean').read_text()+r+'''
theorem roundP_eq (sign : Bool) (product scale : UInt64) :
    roundP sign product scale = FastMul.roundP sign product scale := by
  simp only [roundP, FastMul.roundP, leading_eq]

'''+c+'''
theorem core_eq (x y : UInt32) : core x y = FastMul.core x y := by
  simp only [core, FastMul.core, roundP_eq]

@[inline] def mul (x y : Binary32) : Binary32 :=
  if FastMul.special x.raw.1 y.raw.1 then ExecFloat.mul x y
  else FastMul.ofBits (core x.raw.1 y.raw.1)

theorem mul_spec (x y : Binary32) : mul x y = ExecFloat.Spec.mul x y := by
  have h : mul x y = FastMul.mul x y := by
    simp only [mul, FastMul.mul, core_eq]
  rw [h]
  exact FastMul.mul_spec x y

end R6NormalMul

'''
index=s.index('end FastMul')+len('end FastMul')
s=s[:index]+'\n\n'+block+s[index:]
old='if ex + ey < (128 : UInt32) then LowScale.mul x y else nativeMul x y'
assert s.count(old)==1
s=s.replace(old,'if ex + ey < (128 : UInt32) then LowScale.mul x y else R6NormalMul.mul x y')
oldproof='  · exact LowScale.mul_spec x y\n  · exact nativeMul_spec x y'
assert s.count(oldproof)==1
s=s.replace(oldproof,'  · exact LowScale.mul_spec x y\n  · exact R6NormalMul.mul_spec x y')
out=s.encode()
d=ROOT/'competitions/floatlib/candidates/f01-r6-normal-mul'
d.mkdir(exist_ok=True)
(d/'Kernel.lean').write_bytes(out)
m={'candidate':d.name,'candidate_file':'Kernel.lean','candidate_sha256':hashlib.sha256(out).hexdigest(),'candidate_bytes':len(out),'parent':'f01-d5-stream-pack','parent_sha256':hashlib.sha256(b).hexdigest(),'created_at_utc':datetime.now(timezone.utc).isoformat(),'proof_status':'NOT_RUN','validation_mode':'full-gate','mechanism':'Keep existing low-exponent route. Replace remaining native multiplication with exact word kernel whose leading-bit search is reduced to46/47 in the 24x24-bit significand product band, with original all-input leading fallback. No new float arithmetic theorem required.','expected_gain':'UNKNOWN: removes native conversion calls but adds integer rounding. Must compare whole mul classes, especially near-one and spread, against8eb in actual full gate.','formal_submission':'NOT_SUBMITTED'}
(d/'manifest.json').write_text(json.dumps(m,indent=2)+'\n')
print(json.dumps(m,indent=2))
