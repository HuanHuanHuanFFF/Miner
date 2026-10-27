from pathlib import Path
import hashlib, json
from datetime import datetime, timezone
HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'AGENTS.md').exists())
parent=ROOT/'competitions/floatlib/candidates/f01-d12-scalar-combined/Kernel.lean'
raw=parent.read_bytes()
assert hashlib.sha256(raw).hexdigest()=='df5c61a0ca24a8ef18c0c42d83bdd23466872d3fe8f39dd912e9c347b27fb172'
text=raw.decode('utf-8').replace('\r\n','\n')
under=text[text.index('namespace Submission.UnderflowZero'):]
scale=under[under.index('theorem finiteScale_toNat'):under.index('theorem scale_small')]
rounds=under[under.index('/-- A shift of at least65'):under.index('theorem mul_signed_zero')]
helper=('namespace R15LowCutoff\n\nopen FloatLib.Floats Competition\n'
        'open FloatLib.Floats.Formats.BinaryInterchange.Model.NativeBinary32\n\n'
        '/- Reused exact proof bodies from the full-gated df5c UnderflowZero component;\n'
        '   finiteScale proof originally ported from FloatLib Team, MIT. -/\n'+scale+rounds+
        (HERE/'LowCutoff84-new.lean').read_text(encoding='utf-8')+'\nend R15LowCutoff\n\n')
old='''@[inline] def mul (x y : Binary32) : Binary32 :=
  let ex := FloatLib.Floats.Formats.BinaryInterchange.Model.NativeBinary32.expField x.raw.1
  let ey := FloatLib.Floats.Formats.BinaryInterchange.Model.NativeBinary32.expField y.raw.1
  if ex + ey < (128 : UInt32) then LowScale.mul x y else nativeMul x y

theorem mul_spec (x y : Binary32) : mul x y = ExecFloat.Spec.mul x y := by
  unfold mul
  dsimp only
  split
  · exact LowScale.mul_spec x y
  · exact nativeMul_spec x y
'''
new='''@[inline] def mul (x y : Binary32) : Binary32 :=
  let ex := FloatLib.Floats.Formats.BinaryInterchange.Model.NativeBinary32.expField x.raw.1
  let ey := FloatLib.Floats.Formats.BinaryInterchange.Model.NativeBinary32.expField y.raw.1
  if ex + ey < (128 : UInt32) then
    if ex + ey ≤ (84 : UInt32) then
      FastMul.ofBits
        (if Bool.xor
            (FloatLib.Floats.Formats.BinaryInterchange.Model.NativeBinary32.signBit x.raw.1)
            (FloatLib.Floats.Formats.BinaryInterchange.Model.NativeBinary32.signBit y.raw.1)
          then 0x80000000 else 0)
    else LowScale.mul x y
  else nativeMul x y

theorem mul_spec (x y : Binary32) : mul x y = ExecFloat.Spec.mul x y := by
  unfold mul
  dsimp only
  split
  · split
    · rename_i hcut
      rw [R15LowCutoff.shortcut_eq_low x y hcut]
      exact LowScale.mul_spec x y
    · exact LowScale.mul_spec x y
  · exact nativeMul_spec x y
'''
assert text.count(old)==1
candidate=text.replace(old,helper+new)
assert candidate.replace(helper+new,old)==text
data=candidate.encode('utf-8')
assert text.encode('utf-8') == raw
assert len(data)<=256000, len(data)
(HERE/'Kernel-cutoff84.lean').write_bytes(data)
(HERE/'LowCutoff84-complete-fragment.lean').write_text(helper+new,encoding='utf-8')
receipt={'status':'SOURCE_READY_NOT_RUN','created_at_utc':datetime.now(timezone.utc).isoformat(),
 'parent':str(parent.relative_to(ROOT)),'parent_sha256':hashlib.sha256(raw).hexdigest(),
 'candidate':'Kernel-cutoff84.lean','candidate_sha256':hashlib.sha256(data).hexdigest(),
 'bytes':len(data),'parent_bytes':len(raw),'reverse_patch_exact':True,
 'reused_accepted_proofs':{'finiteScale_toNat_sha256':hashlib.sha256(scale.encode()).hexdigest(),
                          'rseAny_zero_and_roundP_zero_sha256':hashlib.sha256(rounds.encode()).hexdigest()},
 'changed_runtime':'Only exported scalar mul, inside the pre-existing exponent sum<128 branch',
 'untouched_runtime':['add','sum','bmm','nativeMul','LowScale.mul'],
 'new_proof_obligations':['cutoff_nat','cutoff_special_false','scale_sum_le','shortcut_eq_low','mul_spec integration'],
 'Lean':'NOT_RUN','full_gate':'NOT_RUN','performance':'UNKNOWN','formal_submission':'NOT_AUTHORIZED'}
(HERE/'cutoff84-manifest.json').write_text(json.dumps(receipt,indent=2)+'\n',encoding='utf-8')
print(json.dumps(receipt))
