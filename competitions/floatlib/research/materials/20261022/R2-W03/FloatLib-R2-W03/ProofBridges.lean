import ContractTensor

/-
R2-W03 proof diagnostics. Status: NOT_RUN (no Lean toolchain in research environment).
These are helper lemmas and finite kernel-evaluation examples. This file does NOT
assert the all-input decoder equivalence or a sum/bmm obligation.
No added axioms, unsafe definitions, externs, native_decide, or proof holes.
All arithmetic bridges below use the fixed Lean 4.34.0 logical model directly.
-/

namespace R2W03Proof

open Float.Model
open Float.Model.UnpackedFloat

namespace FM
-- This alias avoids changing any imported definition.
abbrev spec := Float.Model.Format.binary32
end FM

/-- UInt32's native C cast has a transparent logical integer-conversion model. -/
theorem uint32_toModel (n : UInt32) :
    n.toFloat32.toModel = Float32.Model.ofUInt32 n := rfl

/-- The same is true for UInt64, including large but exactly representable integers. -/
theorem uint64_toModel (n : UInt64) :
    n.toFloat32.toModel = Float32.Model.ofUInt64 n := rfl

/-- A direct bit-level statement of the UInt32 conversion's logical implementation. -/
theorem uint32_cast_bits (n : UInt32) :
    n.toFloat32.toBits = UInt32.ofBitVec
      (Float.Model.UnpackedFloat.pack FM.spec
        (Float.Model.UnpackedFloat.ofNat FM.spec n.toNat)) := rfl

/-- No Float32 -> Float -> Float32 bridge is needed for the candidate. -/
theorem uint32_mul_toModel (n scaleBits : UInt32) :
    (n.toFloat32 * Float32.ofBits scaleBits).toModel =
      Float32.Model.mul (Float32.Model.ofUInt32 n)
        (Float32.Model.ofBits scaleBits) := rfl

/-- Sign application also has a direct model, including its signed-zero semantics. -/
theorem neg_toModel (x : Float32) :
    (-x).toModel = Float32.Model.neg x.toModel := rfl

/-- Structural Float32 equality can be discharged in the packed model. -/
theorem toModel_injective (x y : Float32) :
    x.toModel = y.toModel ↔ x = y := by
  cases x
  cases y
  constructor
  · intro h
    cases h
    rfl
  · intro h
    cases h
    rfl

/-
Local adaptation of the private helper round_eq_finite_of_targetExponent in
FloatLib/Floats/Formats/IEEE754/Native/Integer/Constructors.lean,
commit 0d91825727839f597fd06b22fdd038ea21480f0c, lines 99--109.
FloatLib is MIT licensed; copyright (c) 2026 FloatLib, FloatLib Team.
-/
theorem round_at_target
    (spec : Format) (sign : Sign) (n : Nat) (e : Int) (hn : n ≠ 0)
    (he : spec.targetExponent (totalExponent n e) = e) :
    Float.Model.UnpackedFloat.round spec sign n e =
      .finite sign n e (Nat.pos_of_ne_zero hn) := by
  have hshift (em : ExtendedMantissa) : em >>> 0 = em := rfl
  simp [Float.Model.UnpackedFloat.round, decreaseExponent, he, roundWithAccuracy,
    shiftToTargetExponent, shiftToExponent, ExtendedMantissa.ofMantissaAndAccuracy,
    ExtendedMantissa.roundedMantissa, ExtendedMantissa.accuracy,
    Accuracy.roundToNearestEven, hshift, hn]

/--
A normalized 24-bit mantissa is unchanged by the logical rounder at any legal
minimum exponent. This is an *unpacked* statement: the caller must separately
ensure that packing does not overflow; e <= 104 suffices for binary32 normals.
-/
theorem round_normalized24 (m : Nat) (hm : m ≠ 0) (hlog : m.log2 = 23)
    (e : Int) (hmin : -149 ≤ e) :
    Float.Model.UnpackedFloat.round FM.spec .positive m e =
      .finite .positive m e (Nat.pos_of_ne_zero hm) := by
  apply round_at_target FM.spec .positive m e hm
  simp only [FM.spec, Format.targetExponent, totalExponent, hlog]
  change max (24 + e - 24) (-149) = e
  have he : 24 + e - 24 = e := by omega
  rw [he]
  exact max_eq_left hmin

/--
A shifted 24-significant-bit integer is exact even when its numeric value exceeds
2^24. The shift is on unbounded Nat here; an executable UInt shift must separately
be proved not to wrap. Packing also needs the normal exponent upper bound.
-/
theorem round_shifted24 (m k : Nat) (hm : m ≠ 0) (hlog : m.log2 = 23) :
    Float.Model.UnpackedFloat.round FM.spec .positive (m <<< k) 0 =
      .finite .positive m (k : Int) (Nat.pos_of_ne_zero hm) := by
  have hs :=
    FloatLib.Floats.Formats.BinaryInterchange.Model.round_shiftLeft
      FM.spec .positive m k (k : Int) hm
  simp only [sub_self] at hs
  rw [hs]
  exact round_normalized24 m hm hlog (k : Int) (by omega)

/- Small closed kernel-evaluation checks, not tests of the general theorem.
   `decide` checks the transparent logical model, not compiled native arithmetic.
   These must still be compiled in the fixed environment; status remains NOT_RUN. -/

-- E=1: the scale is the smallest subnormal, while the output is normal.
example : (8388608 : UInt32).toFloat32 * Float32.ofBits 0x00000001 =
    Float32.ofBits 0x00800000 := by decide

-- E=1, largest fraction.
example : (16777215 : UInt32).toFloat32 * Float32.ofBits 0x00000001 =
    Float32.ofBits 0x00ffffff := by decide

-- E=23: last exponent whose scale is subnormal.
example : (16777215 : UInt32).toFloat32 * Float32.ofBits 0x00400000 =
    Float32.ofBits 0x0bffffff := by decide

-- E=24: the scale becomes the smallest normal.
example : (16777215 : UInt32).toFloat32 * Float32.ofBits 0x00800000 =
    Float32.ofBits 0x0c7fffff := by decide

-- Maximum finite normal, E=254.
example : (16777215 : UInt32).toFloat32 * Float32.ofBits 0x73800000 =
    Float32.ofBits 0x7f7fffff := by decide

-- Negative normal: arithmetic negation changes the sign exactly.
example : -((16777215 : UInt32).toFloat32 * Float32.ofBits 0x73800000) =
    Float32.ofBits 0xff7fffff := by decide

-- A reconstruction for a subnormal must omit the implicit bit.
example : (8388607 : UInt32).toFloat32 * Float32.ofBits 0x00000001 =
    Float32.ofBits 0x007fffff := by decide

-- Signed zero can be retained by explicit negation of the +0 integer conversion.
example : -((0 : UInt32).toFloat32 * Float32.ofBits 0x00000001) =
    Float32.ofBits 0x80000000 := by decide

-- Large integer, 24 significant bits: root's dense shift scheme, E=130.
example : ((16777215 : UInt32) <<< (6 : UInt32)).toFloat32 *
    Float32.ofBits 0x32800000 = Float32.ofBits 0x417fffff := by decide

-- Large UInt64, 24 significant bits: root's first wide bucket, E=133.
example : ((16777215 : UInt64) <<< (31 : UInt64)).toFloat32 *
    Float32.ofBits 0x27800000 = Float32.ofBits 0x42ffffff := by decide

#print axioms uint32_toModel
#print axioms uint64_toModel
#print axioms uint32_cast_bits
#print axioms uint32_mul_toModel
#print axioms neg_toModel
#print axioms toModel_injective
#print axioms round_at_target
#print axioms round_normalized24
#print axioms round_shifted24

end R2W03Proof
