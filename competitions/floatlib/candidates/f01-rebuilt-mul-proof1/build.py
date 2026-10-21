"""Independent normal-product rounding pipeline, with certified fallback."""
from pathlib import Path
import json,hashlib
OWN=Path(__file__).resolve().parent;TRACK=OWN.parents[1]
base=(TRACK/'references/official-incumbent/Kernel.lean').read_text(encoding='utf-8')
assert hashlib.sha256(base.encode()).hexdigest()=='5d0cef3ff21093ca05cde92e516edfe45afca8e11996ad4858e7fb2407d65868'
core=base[base.index('@[inline] def core',base.index('namespace FastMul')):base.index('/-- The operands',base.index('namespace FastMul'))]
core=core.replace('roundP sign (xMantissa * yMantissa)','roundN sign (xMantissa * yMantissa)')
assert 'roundN sign (xMantissa * yMantissa)' in core
runtime=r'''
namespace RebuiltMul
open FloatLib.Floats Competition
open FloatLib.Floats.Formats.BinaryInterchange
open Model.NativeBinary32 FastMul

/-- Fixed-width normalized product: one rounding and one exponent/field pack. -/
@[inline] def roundFixed (sign : Bool) (product scale leading : UInt64) : UInt32 :=
  let roundedMantissa := FastMul.rse product (leading - 23)
  let carry := roundedMantissa == 0x1000000
  let position := leading + scale
  let normalizedPosition := if carry then position + 1 else position
  if normalizedPosition > 425 then
    if sign then 0xff800000 else 0x7f800000
  else
    let mantissa := if carry then 0x800000 else roundedMantissa
    FastMul.mkW sign (normalizedPosition - 171).toUInt32 (FastMul.fracW mantissa)
'''
proofs=[]
for k in [46,47]:
 proofs.append(f'''
theorem leading{k} (x : UInt64) (h : x >>> {k} = 1) :
    FastMul.fastLog2 x = {k} := by
  rw [FastMul.fastLog2_eq]
  have hs : (x >>> ({k} : UInt64)).toNat = x.toNat >>> {k} := by
    rw [UInt64.toNat_shiftRight]
    rfl
  have hn : x.toNat >>> {k} = 1 := by rw [← hs, h]; rfl
  have hl := FastMul.log2_shift x.toNat {k} (by omega)
  rw [hn, show (1 : Nat).log2 = 0 from by decide, Nat.add_zero] at hl
  apply UInt64.toNat_inj.mp
  change x.toNat.log2 = {k}
  exact hl

theorem round{k}_eq (sign : Bool) (product scale : UInt64)
    (h : product >>> {k} = 1) (hn : 172 ≤ ({k} : UInt64) + scale) :
    roundFixed sign product scale {k} = FastMul.roundP sign product scale := by
  have hp : product ≠ 0 := by
    intro hp
    rw [hp] at h
    exact (by decide : ((0 : UInt64) >>> {k}) ≠ 1) h
  have hl := leading{k} product h
  have hlt : ¬ (({k} : UInt64) + scale < 172) := by
    rw [UInt64.lt_iff_toNat_lt]
    rw [UInt64.le_iff_toNat_le] at hn
    omega
  simp [roundFixed, FastMul.roundP, hp, hl, hlt, FastMul.rseAny]
''')
rounder=r'''
/-- The 24x24 product uses only shifts 23 or 24 on its normalized range. -/
@[inline] def roundN (sign : Bool) (product scale : UInt64) : UInt32 :=
  if product >>> 47 == 1 then
    if 172 ≤ (47 : UInt64) + scale then roundFixed sign product scale 47
    else FastMul.roundP sign product scale
  else if product >>> 46 == 1 then
    if 172 ≤ (46 : UInt64) + scale then roundFixed sign product scale 46
    else FastMul.roundP sign product scale
  else FastMul.roundP sign product scale

theorem roundN_eq (sign : Bool) (product scale : UInt64) :
    roundN sign product scale = FastMul.roundP sign product scale := by
  unfold roundN
  split
  · rename_i h
    split
    · rename_i hn
      exact round47_eq sign product scale (by simpa using h) hn
    · rfl
  · split
    · rename_i h
      split
      · rename_i hn
        exact round46_eq sign product scale (by simpa using h) hn
      · rfl
    · rfl
'''
finish=r'''
theorem core_eq (a b : UInt32) : core a b = FastMul.core a b := by
  simp only [core, FastMul.core, roundN_eq]

def mul (x y : Binary32) : Binary32 :=
  if FastMul.special x.raw.1 y.raw.1 then ExecFloat.mul x y
  else FastMul.ofBits (core x.raw.1 y.raw.1)

theorem mul_eq (x y : Binary32) : mul x y = FastMul.mul x y := by
  simp only [mul, FastMul.mul, core_eq]

theorem mul_spec : ∀ x y : Binary32, mul x y = ExecFloat.Spec.mul x y := by
  intro x y
  rw [mul_eq]
  exact FastMul.mul_spec x y

end RebuiltMul
'''
insert=runtime+''.join(proofs)+rounder+core+finish
marker='end FastMul\n'
source=base.replace(marker,marker+insert,1)
source=source.replace('def mul (x y : Binary32) : Binary32 := FastMul.mul x y','def mul (x y : Binary32) : Binary32 := RebuiltMul.mul x y')
source=source.replace(':= FastMul.mul_spec\n',':= RebuiltMul.mul_spec\n')
(OWN/'Kernel.lean').write_bytes(source.encode())
(OWN/'manifest.json').write_text(json.dumps({'candidate':OWN.name,'parent':'official-incumbent','kernel_sha256':hashlib.sha256(source.encode()).hexdigest(),'kernel_bytes':len(source.encode()),'mechanism':'Independent fixed-width normalized multiplication round/pack pipeline, constant shifts 23 or 24, exact old fallback outside protected domain; tensor loops unchanged','proof_status':'NOT_RUN','benchmark':'NOT_RUN','source_attribution':'Official incumbent proofs and author comments retained; reconstructed normalized rounding authored in RebuiltMul'},indent=2)+'\n',encoding='utf-8')
print(OWN.name,hashlib.sha256(source.encode()).hexdigest(),len(source.encode()))
