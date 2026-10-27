namespace Submission.R17UInt64Integer

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

theorem uint64_model_eq_roundDyadic (n : UInt64) :
    Model.ofFloat32Model n.toFloat32.toModel =
      Model.roundDyadic FloatFormat.binary32
        { negative := false, significand := n.toNat, exponent := 0 } := by
  change Model.ofFloat32Model
      (Float32.Model.pack
        (Float.Model.UnpackedFloat.ofUInt64 Float.Model.Format.binary32 n)) = _
  rw [Model.ofFloat32Model_pack]
  change Model.ofModel FloatFormat.binary32
      (Float.Model.UnpackedFloat.ofInt FloatFormat.binary32.toModel
        (n.toNat : Int)) = _
  have hn : ¬ (n.toNat : Int) < 0 := by omega
  simpa [FloatLib.Numerics.Dyadic.ofScaledInt, hn] using
    Model.ofModel_ofInt_eq_roundDyadic FloatFormat.binary32
      (by decide) (n.toNat : Int)

theorem native_uint64_decode (n : UInt64)
    (hlo : 70368744177664 ≤ n.toNat) (hhi : n.toNat ≤ 281474943156225) :
    Model.toDyadic? (Model.ofFloat32Model n.toFloat32.toModel) =
      some ⟨false,R14NatNormal.mantissa n.toNat,(roundedShift n.toNat : Int)⟩ := by
  have hl := R14NatNormal.leading_bounds n.toNat hlo (by omega)
  have hc := R14NatNormal.carry_le n.toNat
  have he := R14ExponentShift.middle_bounds n.toNat hlo hhi
  have hshift : (n.toNat.log2 : Int)+0+(R14NatNormal.carry n.toNat : Int)-23 =
      (roundedShift n.toNat : Int) := by
    unfold roundedShift R14ExponentShift.middleExponent
    omega
  rw [uint64_model_eq_roundDyadic]
  have hd := R14NatNormal.round_normal_decode false n.toNat 0 hlo (by omega)
    (by omega) (by omega)
  simpa only [hshift] using hd

theorem uint64_roundtrip (n : UInt64)
    (hlo : 70368744177664 ≤ n.toNat) (hhi : n.toNat ≤ 281474943156225) :
    n.toFloat32.toUInt64.toNat = roundedInteger n.toNat := by
  exact toUInt64_of_nonnegative_integral_decode _ _ _
    (native_uint64_decode n hlo hhi) (rounded_integer_fit _ hlo hhi)

theorem product_word_nat (a b : UInt32)
    (ha0 : 8388608 ≤ a.toNat) (ha : a.toNat < 16777216)
    (hb0 : 8388608 ≤ b.toNat) (hb : b.toNat < 16777216) :
    (a.toUInt64*b.toUInt64).toNat = R14ExponentShift.product a b := by
  have hp := R14ExponentShift.product_bounds a b ha0 ha hb0 hb
  unfold R14ExponentShift.product
  rw [UInt64.toNat_mul,UInt32.toNat_toUInt64,UInt32.toNat_toUInt64]
  exact Nat.mod_eq_of_lt (by change R14ExponentShift.product a b < _; omega)

theorem numeric_integer_product (a b : UInt32)
    (ha0 : 8388608 ≤ a.toNat) (ha : a.toNat < 16777216)
    (hb0 : 8388608 ≤ b.toNat) (hb : b.toNat < 16777216) :
    (a.toUInt64*b.toUInt64).toFloat32.toUInt64.toNat =
      roundedInteger (R14ExponentShift.product a b) := by
  have hp := R14ExponentShift.product_bounds a b ha0 ha hb0 hb
  have hw := product_word_nat a b ha0 ha hb0 hb
  have hd := uint64_roundtrip (a.toUInt64*b.toUInt64)
    (by rw [hw]; exact hp.1) (by rw [hw]; exact hp.2)
  simpa only [hw] using hd

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
    ((a.toUInt64*b.toUInt64).toFloat32.toUInt64 >>> s64).toNat =
      R14NatNormal.mantissa (R14ExponentShift.product a b) := by
  have hp := R14ExponentShift.product_bounds a b ha0 ha hb0 hb
  have hc := rounded_shift_cases _ hp.1 hp.2
  have hsbound : s64.toNat < 64 := by rw [hs]; omega
  rw [UInt64.toNat_shiftRight,Nat.mod_eq_of_lt hsbound,hs,
    numeric_integer_product a b ha0 ha hb0 hb]
  unfold roundedInteger
  simp [Nat.shiftRight_eq_div_pow,Nat.two_pow_pos]

end Submission.R17UInt64Integer
