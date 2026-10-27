"""Prepare an optional exact-source fragment; no full candidate or compilation.
Math is copied from e139's fully accepted LowZero component. Runtime reaches the
extra zero guard only after cutoff84 rejects, a distinct dynamic scope.
"""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json
HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'AGENTS.md').exists())
old=ROOT/'competitions/floatlib/candidates/f01-d7-low-zero/Kernel.lean'
raw=old.read_bytes();text=raw.decode()
assert hashlib.sha256(raw).hexdigest()=='e139093ac7f8fc6133bba266d1f2dee25e282d185996e72f2cd91dd073630d24'
start=text.index('namespace LowZero\n')
end=text.index('end LowZero\n',start)+len('end LowZero\n')
proof=text[start:end]
renamed=proof.replace('namespace LowZero\n','namespace R15ResidualZero\n').replace('end LowZero\n','end R15ResidualZero\n')
assert renamed.replace('namespace R15ResidualZero\n','namespace LowZero\n').replace('end R15ResidualZero\n','end LowZero\n')==proof
runtime='''@[inline] def mul (x y : Binary32) : Binary32 :=
  let ex := FloatLib.Floats.Formats.BinaryInterchange.Model.NativeBinary32.expField x.raw.1
  let ey := FloatLib.Floats.Formats.BinaryInterchange.Model.NativeBinary32.expField y.raw.1
  if ex + ey < (128 : UInt32) then
    if ex + ey ≤ (84 : UInt32) then
      FastMul.ofBits
        (if Bool.xor
            (FloatLib.Floats.Formats.BinaryInterchange.Model.NativeBinary32.signBit x.raw.1)
            (FloatLib.Floats.Formats.BinaryInterchange.Model.NativeBinary32.signBit y.raw.1)
          then 0x80000000 else 0)
    else if R2W01b.magnitude x.raw.1 = 0 ∨ R2W01b.magnitude y.raw.1 = 0 then
      FastMul.ofBits (R15ResidualZero.signedZero
        (Bool.xor
          (FloatLib.Floats.Formats.BinaryInterchange.Model.NativeBinary32.signBit x.raw.1)
          (FloatLib.Floats.Formats.BinaryInterchange.Model.NativeBinary32.signBit y.raw.1)))
    else LowScale.mul x y
  else nativeMul x y

theorem mul_spec (x y : Binary32) : mul x y = ExecFloat.Spec.mul x y := by
  unfold mul
  dsimp only
  split
  · rename_i hlow
    split
    · rename_i hcut
      rw [R15LowCutoff.shortcut_eq_low x y hcut]
      exact LowScale.mul_spec x y
    · split
      · rename_i hzero
        rw [R15ResidualZero.zero_eq_low x y hlow hzero]
        exact LowScale.mul_spec x y
      · exact LowScale.mul_spec x y
  · exact nativeMul_spec x y
'''
header='''/- OPTIONAL RESERVE / NOT_COMPILED_THIS_COMPOSITION.
   Insert while namespace Submission is open, after R15LowCutoff helpers;
   replace its exported mul + mul_spec with the final two declarations here.
   Do not append duplicate exported declarations.
   LowZero proofs copied from exact full-gated e139, namespace rename only.
   This is not a request for another full D and not a speed claim. -/
'''
data=(header+renamed+'\n'+runtime).encode()
(HERE/'ResidualLowZero-reserve-fragment.lean').write_bytes(data)
receipt={'state':'OPTIONAL_RESERVE_NOT_COMPILED','created_at_utc':datetime.now(timezone.utc).isoformat(),
 'proof_source':str(old.relative_to(ROOT)),'proof_source_sha256':hashlib.sha256(raw).hexdigest(),
 'accepted_run':39904491256,'accepted_seed':816,
 'proof_block_original_sha256':hashlib.sha256(proof.encode()).hexdigest(),
 'proof_change':'namespace rename only; exact reverse verified',
 'fragment':'ResidualLowZero-reserve-fragment.lean','fragment_bytes':len(data),
 'fragment_sha256':hashlib.sha256(data).hexdigest(),
 'new_dynamic_scope':'84 < raw exponent sum < 128; zero input only; cutoff84 hits do not pay this guard',
 'new_validation_gap':'Composition mul_spec and full candidate byte budget/gate/performance are not run',
 'priority':'Do not enqueue on this evidence alone; evaluate only if existing D feedback justifies incremental work',
 'original_failure_preserved':{'mul_normalized':1.0709083050820591,'whole_normalized':1.0243151644675506},
 'cost_claim':'Can only avoid front-end special/field/mantissa/scale/product/roundSelect work; old product==0 already avoids log2/RNE',
 'guard':'Original proven magnitude==0 retained. No unmeasured shift-vs-mask speed assertion.'}
(HERE/'residual-lowzero-fragment-manifest.json').write_text(json.dumps(receipt,indent=2)+'\n',encoding='utf-8')
print(json.dumps(receipt))
