"""New same-scale/same-sign addition dataflow, exact fallback elsewhere."""
from pathlib import Path
import hashlib,json
OWN=Path(__file__).resolve().parent;TRACK=OWN.parents[1]
base=(TRACK/'references/official-incumbent/Kernel.lean').read_text(encoding='utf-8')
new=r'''
namespace RebuiltAdd
open FloatLib.Floats Competition
open FloatLib.Floats.Formats.BinaryInterchange
open Model.NativeBinary32

@[inline] def round24 (sign : Bool) (product scale : UInt64) : UInt32 :=
  let mantissa := TunedAdd.rse product 1
  let carry := mantissa == 0x1000000
  let position := (24 : UInt64) + scale
  let position := if carry then position + 1 else position
  if position > 425 then (if sign then 0xff800000 else 0x7f800000)
  else TunedAdd.mkW sign (position - 171).toUInt32
    (TunedAdd.fracW (if carry then 0x800000 else mantissa))

theorem leading24 (x : UInt64) (h : x >>> 24 = 1) : TunedAdd.fastLog2 x = 24 := by
  rw [TunedAdd.fastLog2_eq]
  have hs : (x >>> (24 : UInt64)).toNat = x.toNat >>> 24 := by
    rw [UInt64.toNat_shiftRight]
    rfl
  have hn : x.toNat >>> 24 = 1 := by rw [← hs, h]; rfl
  have hl := TunedAdd.log2_shift x.toNat 24 (by omega)
  rw [hn, show (1 : Nat).log2 = 0 from by decide, Nat.add_zero] at hl
  apply UInt64.toNat_inj.mp
  change x.toNat.log2 = 24
  exact hl

theorem round24_eq (sign : Bool) (product scale : UInt64)
    (h : product >>> 24 = 1) (hn : 172 ≤ (24 : UInt64) + scale) :
    round24 sign product scale = TunedAdd.roundP sign product scale := by
  have hp : product ≠ 0 := by
    intro hp
    rw [hp] at h
    exact (by decide : ((0 : UInt64) >>> 24) ≠ 1) h
  have hl := leading24 product h
  have hlt : ¬ ((24 : UInt64) + scale < 172) := by
    rw [UInt64.lt_iff_toNat_lt]
    rw [UInt64.le_iff_toNat_le] at hn
    omega
  simp [round24, TunedAdd.roundP, hp, hl, hlt, TunedAdd.rseAny]

theorem same_scale (a b : UInt32)
    (hs : finiteScale (expField a) = finiteScale (expField b))
    (hsg : signBit a = signBit b) :
    TunedAdd.core a b = TunedAdd.roundP (signBit a)
      (finiteMantissa (expField a) (fracField a) + finiteMantissa (expField b) (fracField b))
      (finiteScale (expField a) + 149) := by
  simp [TunedAdd.core, hs, hsg, FloatLib.Numerics.FixedWord.addSignedMagnitudes]

@[inline] def core (a b : UInt32) : UInt32 :=
  let scale := finiteScale (expField a)
  if scale == finiteScale (expField b) then
    if signBit a == signBit b then
      let product := finiteMantissa (expField a) (fracField a) + finiteMantissa (expField b) (fracField b)
      if product >>> 24 == 1 then
        if 172 ≤ (24 : UInt64) + (scale + 149) then round24 (signBit a) product (scale + 149)
        else TunedAdd.core a b
      else TunedAdd.core a b
    else TunedAdd.core a b
  else TunedAdd.core a b

theorem core_eq (a b : UInt32) : core a b = TunedAdd.core a b := by
  unfold core
  split
  · rename_i hs
    split
    · rename_i hsg
      split
      · rename_i hp
        split
        · rename_i hn
          rw [round24_eq _ _ _ (by simpa using hp) hn]
          exact (same_scale a b (by simpa using hs) (by simpa using hsg)).symm
        · rfl
      · rfl
    · rfl
  · rfl

def add (x y : Binary32) : Binary32 :=
  if TunedAdd.special x.raw.1 y.raw.1 then ExecFloat.add x y
  else TunedAdd.ofBits (core x.raw.1 y.raw.1)

theorem add_eq (x y : Binary32) : add x y = TunedAdd.add x y := by
  simp only [add, TunedAdd.add, core_eq]

theorem add_spec : ∀ x y : Binary32, add x y = ExecFloat.Spec.add x y := by
  intro x y
  rw [add_eq]
  exact TunedAdd.add_spec x y

end RebuiltAdd
'''
source=base.replace('end TunedAdd\n','end TunedAdd\n'+new,1)
source=source.replace('def add (x y : Binary32) : Binary32 := TunedAdd.add x y','def add (x y : Binary32) : Binary32 := RebuiltAdd.add x y')
source=source.replace(':= TunedAdd.add_spec\n',':= RebuiltAdd.add_spec\n')
(OWN/'Kernel.lean').write_bytes(source.encode())
(OWN/'manifest.json').write_text(json.dumps({'candidate':OWN.name,'parent':'official-incumbent','kernel_sha256':hashlib.sha256(source.encode()).hexdigest(),'kernel_bytes':len(source.encode()),'mechanism':'Independent same-scale/same-sign addition dataflow with fixed one-bit rounding and direct pack; exact fallback outside protected domain','proof_status':'NOT_RUN','validation_mode':'statement-only','scope':'First proof checkpoint; full gate and performance pending'},indent=2)+'\n',encoding='utf-8')
print(OWN.name,hashlib.sha256(source.encode()).hexdigest(),len(source.encode()))
