"""Compose proven add decode and word sum; revisit tiny mul with a new cheaper rounder."""
from pathlib import Path
import hashlib,json
ROOT=Path(__file__).resolve().parents[1];OUT=Path(__file__).resolve().parent
raw=(ROOT/'f01-d4-scalar-decode/Kernel.lean').read_bytes()
assert hashlib.sha256(raw).hexdigest()=='a7dca716f0076511875209b043f761559235a74b5729227916360e4d9373e7e9'
s=raw.decode()
# Scalar multiply keeps the original native conversion; only add adopts numeric conversion.
s=s.replace('ExecFloat.Binary.ofFloat32 (R2W01b.convert x.raw.1 * R2W01b.convert y.raw.1)','ExecFloat.Binary.ofFloat32 (ExecFloat.Binary.toFloat32 x * ExecFloat.Binary.toFloat32 y)',1)
s=s.replace('    rw [R2W01c.convert_eq, R2W01c.convert_eq]\n    change ExecFloat.Binary.ofFloat32 (ExecFloat.Binary.toFloat32 x * ExecFloat.Binary.toFloat32 y) = _\n','',1)
helper=(ROOT/'f01-d2-low-scale-rounding-proof1/Kernel.lean').read_text();helper=helper[helper.index('namespace Submission.LowScale'):].replace('namespace Submission.LowScale','namespace LowScale').replace('end Submission.LowScale','end LowScale')
old=(ROOT/'f01-d3-final-package/Kernel.lean').read_text();a=old.index('@[inline] def core (xBits yBits : UInt32)');b=old.index('/-- One operand is a NaN',a);core=old[a:b].replace('  roundP sign','  roundSelect sign')
extra='''
open FloatLib.Floats.Formats.BinaryInterchange.Model.NativeBinary32

'''+core+'''
theorem core_eq (a b : UInt32) : core a b = FastMul.core a b := by
  simp only [core, FastMul.core, roundSelect_eq]

@[inline] def mul (x y : Binary32) : Binary32 :=
  if FastMul.special x.raw.1 y.raw.1 then ExecFloat.mul x y
  else FastMul.ofBits (core x.raw.1 y.raw.1)

theorem mul_eq (x y : Binary32) : mul x y = FastMul.mul x y := by
  simp only [mul, FastMul.mul, core_eq]

theorem mul_spec (x y : Binary32) : mul x y = ExecFloat.Spec.mul x y := by
  rw [mul_eq]
  exact FastMul.mul_spec x y

'''
helper=helper.replace('end LowScale',extra+'end LowScale')
marker='namespace GuardBridge\n';pos=s.index(marker);s=s[:pos]+helper+'\n'+s[pos:]
a=s.index('/-- Raw finite input guards retain the original multiplication fallback. -/');b=s.index('/-- `add` and `mul` are FloatLib',a)
block=s[a:b].replace('def mul (','def nativeMul (').replace('theorem mul_spec','theorem nativeMul_spec').replace('mul x y = ExecFloat.Spec.mul','nativeMul x y = ExecFloat.Spec.mul').replace('  unfold mul\n','  unfold nativeMul\n')
block+='''@[inline] def mul (x y : Binary32) : Binary32 :=
  let ex := FloatLib.Floats.Formats.BinaryInterchange.Model.NativeBinary32.expField x.raw.1
  let ey := FloatLib.Floats.Formats.BinaryInterchange.Model.NativeBinary32.expField y.raw.1
  if ex + ey < (128 : UInt32) then LowScale.mul x y else nativeMul x y

theorem mul_spec (x y : Binary32) : mul x y = ExecFloat.Spec.mul x y := by
  unfold mul
  dsimp only
  split
  \u00b7 exact LowScale.mul_spec x y
  \u00b7 exact nativeMul_spec x y

'''
s=s[:a]+block+s[b:]
word=(ROOT/'f01-d4-sum-word/Kernel.lean').read_text();a=word.index('namespace Submission.NativeDecodeSumWord\n');b=word.index('end Submission.NativeDecodeSumWord',a)+len('end Submission.NativeDecodeSumWord');extra=word[a:b]+'\n\n';pos=s.index('namespace Submission\n\nopen FloatLib.Floats Competition\n\ndef sum');s=s[:pos]+extra+s[pos:]
s=s.replace('let result := NativeDecodeSum.loop x 0 (Float32.ofBits 0)','let result := NativeDecodeSumWord.run x',1).replace('rw [NativeDecodeSum.loop_eq]','rw [NativeDecodeSumWord.run_eq, NativeDecodeSum.loop_eq]',1)
data=s.encode();(OUT/'Kernel.lean').write_bytes(data)
m=dict(candidate=OUT.name,candidate_file='Kernel.lean',candidate_sha256=hashlib.sha256(data).hexdigest(),candidate_bytes=len(data),parents=['f01-d4-scalar-decode','f01-d4-sum-word','f01-d2-low-scale-rounding-proof1'],validation_mode='full-gate',proof_status='NOT_RUN',mechanism='Numeric decoder only for add, proven USize sum, native mul with low-exponent software path using new proven cheap rounder. Revisit condition: actual Intel tiny-mul50ns regression and removal of old log2 cost. Original8lane bmm unchanged.')
(OUT/'manifest.json').write_bytes((json.dumps(m,indent=2)+'\n').encode());print(json.dumps(m))
