import ContractTensor

namespace R5W02

open Float.Model
open Float.Model.UnpackedFloat

@[inline] def finiteBits (u : UInt32) : Bool :=
  ((u >>> 23) &&& 255) != 255

theorem unpack_isFinite_eq (spec : Format) (bits : BitVec spec.numBits) :
    (Float.Model.UnpackedFloat.unpack spec bits).isFinite =
      if unpackExponent bits = (-1 : BitVec spec.exponentBits) then false else true := by
  unfold Float.Model.UnpackedFloat.unpack
  split_ifs <;> rfl

theorem exponent_toNat (u : UInt32) :
    (unpackExponent (spec := Format.binary32) u.toBitVec).toNat =
      (((u >>> 23) &&& 255) : UInt32).toNat := by
  simp only [unpackExponent, BitVec.extractLsb'_toNat, UInt32.toNat_toBitVec,
    UInt32.toNat_and, UInt32.toNat_shiftRight]
  change (u.toNat >>> 23) % 256 = (u.toNat >>> 23) &&& (2 ^ 8 - 1)
  rw [Nat.and_two_pow_sub_one_eq_mod]

theorem exponent_allOnes_iff (u : UInt32) :
    unpackExponent (spec := Format.binary32) u.toBitVec = -1#8 ↔
      (((u >>> 23) &&& 255) : UInt32) = 255 := by
  constructor
  · intro h
    apply UInt32.toNat_inj.mp
    have hh := congrArg BitVec.toNat h
    rw [exponent_toNat] at hh
    exact hh
  · intro h
    apply BitVec.toNat_inj.mp
    rw [exponent_toNat]
    exact congrArg UInt32.toNat h

theorem isFinite_eq_finiteBits (v : Float32) :
    v.isFinite = finiteBits v.toBits := by
  change (Float.Model.UnpackedFloat.unpack Format.binary32 v.toBits.toBitVec).isFinite = _
  rw [unpack_isFinite_eq]
  by_cases h : (((v.toBits >>> 23) &&& 255) : UInt32) = 255
  · have he := (exponent_allOnes_iff v.toBits).2 h
    simp [he, finiteBits, h]
  · have he : unpackExponent (spec := Format.binary32) v.toBits.toBitVec ≠ -1#8 := by
      intro he
      exact h ((exponent_allOnes_iff v.toBits).1 he)
    simp [he, finiteBits, h]

theorem isFinite_true_iff (v : Float32) :
    v.isFinite = true ↔ finiteBits v.toBits = true := by
  rw [isFinite_eq_finiteBits]


theorem ofBits32_toBits_eq_ofFloat32 (v : Float32) :
    FloatLib.Floats.ExecFloat.Binary.ofBits32 v.toBits =
      FloatLib.Floats.ExecFloat.Binary.ofFloat32 v :=
  rfl

theorem finish_expr_eq (v : Float32) (fallback : Competition.Binary32) :
    (let u := v.toBits
     if hf : finiteBits u = true then
       FloatLib.Floats.ExecFloat.Binary.ofBits32 u
     else fallback) =
    (if hf : v.isFinite = true then
       FloatLib.Floats.ExecFloat.Binary.ofFloat32 v
     else fallback) := by
  change
    (if hf : finiteBits v.toBits = true then
       FloatLib.Floats.ExecFloat.Binary.ofBits32 v.toBits
     else fallback) =
    (if hf : v.isFinite = true then
       FloatLib.Floats.ExecFloat.Binary.ofBits32 v.toBits
     else fallback)
  rw [isFinite_eq_finiteBits v]

end R5W02
