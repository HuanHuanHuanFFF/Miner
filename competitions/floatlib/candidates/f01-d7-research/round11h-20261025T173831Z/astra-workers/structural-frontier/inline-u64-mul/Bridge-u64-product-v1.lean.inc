namespace Submission.R17UInt64Product

open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange
open FloatLib.Numerics

def roundedShift (p : Nat) : Nat := R14ExponentShift.middleExponent p - 150
def roundedInteger (p : Nat) : Nat := R14NatNormal.mantissa p * 2 ^ roundedShift p

theorem rounded_shift_cases (p : Nat)
    (hlo : 70368744177664 ≤ p) (hhi : p ≤ 281474943156225) :
    roundedShift p = 23 ∨ roundedShift p = 24 := by
  have h := R14ExponentShift.middle_bounds p hlo hhi
  unfold roundedShift
  omega

theorem rounded_integer_bounds (p : Nat)
    (hlo : 70368744177664 ≤ p) (hhi : p ≤ 281474943156225) :
    70368744177664 ≤ roundedInteger p ∧ roundedInteger p < 281474976710656 := by
  have hm := R14NatNormal.mantissa_bounds p hlo (by omega)
  have hs := rounded_shift_cases p hlo hhi
  rcases hs with hs | hs <;>
    simp only [roundedInteger, hs] <;> norm_num <;> omega

theorem rounded_integer_fit (p : Nat)
    (hlo : 70368744177664 ≤ p) (hhi : p ≤ 281474943156225) :
    roundedInteger p < UInt64.size := by
  have h := rounded_integer_bounds p hlo hhi
  change roundedInteger p < 18446744073709551616
  omega

theorem toUInt64_of_nonnegative_integral_decode (x : Float32) (m e : Nat)
    (hd : Model.toDyadic? (Model.ofFloat32Model x.toModel) =
      some ⟨false,m,(e : Int)⟩)
    (hfit : m*2^e < UInt64.size) :
    x.toUInt64.toNat = m*2^e := by
  have hv := Model.exactValue_eq_finite_of_toDyadic?_eq_some hd
  have hi := Model.toInt_toModel_eq (fmt := FloatFormat.binary32) (by decide)
    (Model.ofFloat32Model x.toModel) 0 (UInt64.size-1)
  rw [Model.toModel_ofFloat32Model,hv] at hi
  change x.toModel.unpack.toInt 0 (UInt64.size-1) =
    Model.roundDyadicToInt .towardZero
      (⟨false,m,(e : Int)⟩ : FloatLib.Numerics.Dyadic) at hi
  have hr : Model.roundDyadicToInt .towardZero
      (⟨false,m,(e : Int)⟩ : FloatLib.Numerics.Dyadic) = ((m*2^e : Nat) : Int) := by
    by_cases hm : m=0
    · subst m
      simp [Model.roundDyadicToInt]
    · simp [Model.roundDyadicToInt,hm,Nat.shiftLeft_eq]
  change (UInt64.ofNatClamp
    ((x.toModel.unpack.toInt 0 (UInt64.size-1)).toNat)).toNat = _
  rw [hi,hr]
  simpa using (UInt64.toNat_ofNatClamp_of_lt hfit)

theorem native_product_decode (a b : UInt32)
    (ha0 : 8388608 ≤ a.toNat) (ha : a.toNat < 16777216)
    (hb0 : 8388608 ≤ b.toNat) (hb : b.toNat < 16777216) :
    Model.toDyadic? (Model.ofFloat32Model (a.toFloat32*b.toFloat32).toModel) =
      some ⟨false,R14NatNormal.mantissa (R14ExponentShift.product a b),
        (roundedShift (R14ExponentShift.product a b) : Int)⟩ := by
  let p := R14ExponentShift.product a b
  have hp := R14ExponentShift.product_bounds a b ha0 ha hb0 hb
  have he := R14ExponentShift.middle_bounds p hp.1 hp.2
  have hm := R14NatNormal.mantissa_bounds p hp.1 (by omega)
  have hsum : 8388608 + R14ExponentShift.storedFraction p = R14NatNormal.mantissa p := by
    unfold R14ExponentShift.storedFraction
    omega
  have hshift : (R14ExponentShift.middleExponent p : Int) - 150 =
      (roundedShift p : Int) := by
    unfold roundedShift
    omega
  have hd := R2W01c.fields32_toDyadic false (R14ExponentShift.middleExponent p)
    (R14ExponentShift.storedFraction p) (by omega) (by omega) he.2.2
  have hraw : Model.toDyadic? (R2W01c.rawModel
      (Model.NativeBinary32.mkBits false (R14ExponentShift.middleExponent p)
        (R14ExponentShift.storedFraction p))) =
      some ⟨false,R14NatNormal.mantissa p,(roundedShift p : Int)⟩ := by
    rw [R2W01c.rawModel_eq_native32,Model.NativeBinary32.ofUInt32_mkBits]
    simpa only [hsum,hshift] using hd
  have hbits := R14ExponentShift.first_product_bits a b ha0 ha hb0 hb
  have hnative := R2W01b.float32_eq_of_raw_bits hbits
  rw [hnative]
  exact R2W01c.nativeModel_ofBits_decode _ hraw

theorem numeric_product (a b : UInt32)
    (ha0 : 8388608 ≤ a.toNat) (ha : a.toNat < 16777216)
    (hb0 : 8388608 ≤ b.toNat) (hb : b.toNat < 16777216) :
    (a.toFloat32*b.toFloat32).toUInt64.toNat =
      roundedInteger (R14ExponentShift.product a b) := by
  have hp := R14ExponentShift.product_bounds a b ha0 ha hb0 hb
  exact toUInt64_of_nonnegative_integral_decode _ _ _
    (native_product_decode a b ha0 ha hb0 hb)
    (rounded_integer_fit _ hp.1 hp.2)

theorem rounded_threshold (p : Nat)
    (hlo : 70368744177664 ≤ p) (hhi : p ≤ 281474943156225) :
    (if 140737488355328 ≤ roundedInteger p then 1 else 0) =
      R14ExponentShift.middleExponent p - 173 := by
  have he := R14ExponentShift.middle_bounds p hlo hhi
  have hm := R14NatNormal.mantissa_bounds p hlo (by omega)
  have hc : R14ExponentShift.middleExponent p=173 ∨
      R14ExponentShift.middleExponent p=174 := by omega
  rcases hc with hc | hc
  · have hs : roundedShift p=23 := by simp [roundedShift,hc]
    have hr : roundedInteger p < 140737488355328 := by
      simp only [roundedInteger,hs]
      norm_num
      omega
    simp [Nat.not_le_of_lt hr,hc]
  · have hs : roundedShift p=24 := by simp [roundedShift,hc]
    have hr : 140737488355328 ≤ roundedInteger p := by
      simp only [roundedInteger,hs]
      norm_num
      omega
    simp [hr,hc]

theorem shift_recovery (a b : UInt32) (s64 : UInt64)
    (ha0 : 8388608 ≤ a.toNat) (ha : a.toNat < 16777216)
    (hb0 : 8388608 ≤ b.toNat) (hb : b.toNat < 16777216)
    (hs : s64.toNat = roundedShift (R14ExponentShift.product a b)) :
    ((a.toFloat32*b.toFloat32).toUInt64 >>> s64).toNat =
      R14NatNormal.mantissa (R14ExponentShift.product a b) := by
  have hp := R14ExponentShift.product_bounds a b ha0 ha hb0 hb
  have hc := rounded_shift_cases _ hp.1 hp.2
  have hsbound : s64.toNat < 64 := by rw [hs]; omega
  rw [UInt64.toNat_shiftRight,Nat.mod_eq_of_lt hsbound,hs,
    numeric_product a b ha0 ha hb0 hb]
  unfold roundedInteger
  simp [Nat.shiftRight_eq_div_pow,Nat.two_pow_pos]

end Submission.R17UInt64Product
