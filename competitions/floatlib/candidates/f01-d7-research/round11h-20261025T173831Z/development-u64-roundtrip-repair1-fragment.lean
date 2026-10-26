
section R17UInt64InterfaceProbe
set_option maxRecDepth 8192

namespace Submission.R14NatNormal

open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange
open FloatLib.Numerics

def rounded (p : Nat) : Nat := roundShiftRightEven p (p.log2 - 23)
def carry (p : Nat) : Nat := if rounded p = 16777216 then 1 else 0
def mantissa (p : Nat) : Nat := if rounded p = 16777216 then 8388608 else rounded p

theorem carry_le (p : Nat) : carry p ≤ 1 := by
  unfold carry
  split <;> omega

theorem leading_bounds (p : Nat)
    (hlo : 70368744177664 ≤ p) (hhi : p < 281474976710656) :
    46 ≤ p.log2 ∧ p.log2 ≤ 47 := by
  have hn : p ≠ 0 := by omega
  have hl : 46 ≤ p.log2 := (Nat.le_log2 hn).2 (by norm_num; exact hlo)
  have hh : p.log2 < 48 := (Nat.log2_lt hn).2 (by norm_num; exact hhi)
  omega

theorem no_carry_at_47 (p : Nat)
    (hmax : p ≤ 281474943156225) (hlog : p.log2 = 47) : carry p = 0 := by
  have hq : p / 16777216 ≤ 16777214 := by omega
  have hr := roundShiftRightEven_le_shiftRight_add1 p 24
  norm_num [Nat.shiftRight_eq_div_pow] at hr
  have hb : rounded p ≤ 16777215 := by
    unfold rounded
    rw [hlog]
    change roundShiftRightEven p 24 ≤ 16777215
    omega
  have hn : rounded p ≠ 16777216 := by omega
  simp [carry, hn]

theorem mantissa_bounds (p : Nat)
    (hlo : 70368744177664 ≤ p) (hhi : p < 281474976710656) :
    8388608 ≤ mantissa p ∧ mantissa p < 16777216 := by
  have hn : p ≠ 0 := by omega
  have hl := leading_bounds p hlo hhi
  have hlow := Nat.log2_self_le hn
  have hupp := Nat.lt_log2_self (n := p)
  have hquotient :
      8388608 ≤ Nat.shiftRight p (p.log2 - 23) ∧
      Nat.shiftRight p (p.log2 - 23) < 16777216 := by
    have hc : p.log2 = 46 ∨ p.log2 = 47 := by omega
    rcases hc with hc | hc <;>
      simp only [hc] at hlow hupp ⊢ <;>
      norm_num [Nat.shiftRight_eq_div_pow] at hlow hupp ⊢ <;> omega
  have hrlo := shiftRight_le_roundShiftRightEven p (p.log2 - 23)
  have hrhi := roundShiftRightEven_le_shiftRight_add1 p (p.log2 - 23)
  by_cases hc : rounded p = 16777216
  · simp [mantissa, hc]
  · simp only [mantissa, hc, ↓reduceIte]
    change roundShiftRightEven p (p.log2 - 23) ≠ 16777216 at hc
    unfold rounded
    omega

/-- A normal finite rounding has the same mantissa at every admissible exponent.
The hypotheses explicitly include the carry in the upper boundary. -/
theorem native_round_normal (sign : Bool) (p : Nat) (e : Int)
    (hp : p ≠ 0) (hl : 23 ≤ p.log2)
    (hmin : -126 ≤ (p.log2 : Int) + e)
    (hmax : (p.log2 : Int) + e + (carry p : Int) ≤ 127) :
    Model.NativeBinary32.roundDyadic ⟨sign, p, e⟩ =
      Model.NativeBinary32.mkBits sign
        (Int.toNat ((p.log2 : Int) + e + (carry p : Int) + 127))
        (mantissa p - 8388608) := by
  have hnormal : ¬(p.log2 : Int) + e < -126 := by omega
  by_cases hc : roundShiftRightEven p (p.log2 - 23) = 16777216
  · have hc1 : carry p = 1 := by simp [carry, rounded, hc]
    have hf : ¬(p.log2 : Int) + e + 1 > 127 := by
      rw [hc1] at hmax
      norm_num at hmax
      omega
    simp [Model.NativeBinary32.roundDyadic, Model.pow2_eq_two_pow,
      hp, hl, hnormal, hf, carry, rounded, mantissa, hc]
  · have hc0 : carry p = 0 := by simp [carry, rounded, hc]
    have hf : ¬(p.log2 : Int) + e > 127 := by
      rw [hc0] at hmax
      norm_num at hmax
      omega
    simp [Model.NativeBinary32.roundDyadic, Model.pow2_eq_two_pow,
      hp, hl, hnormal, hf, carry, rounded, mantissa, hc]

theorem model_round_normal (sign : Bool) (p : Nat) (e : Int)
    (hp : p ≠ 0) (hl : 23 ≤ p.log2)
    (hmin : -126 ≤ (p.log2 : Int) + e)
    (hmax : (p.log2 : Int) + e + (carry p : Int) ≤ 127) :
    Model.roundDyadic FloatFormat.binary32 ⟨sign, p, e⟩ =
      Model.ofFields FloatFormat.binary32 sign
        (Int.toNat ((p.log2 : Int) + e + (carry p : Int) + 127))
        (mantissa p - 8388608) := by
  rw [← Model.NativeBinary32.ofUInt32_roundDyadic,
    native_round_normal sign p e hp hl hmin hmax,
    Model.NativeBinary32.ofUInt32_mkBits]

theorem round_normal_decode (sign : Bool) (p : Nat) (e : Int)
    (hlo : 70368744177664 ≤ p) (hhi : p < 281474976710656)
    (hmin : -126 ≤ (p.log2 : Int) + e)
    (hmax : (p.log2 : Int) + e + (carry p : Int) ≤ 127) :
    Model.toDyadic? (Model.roundDyadic FloatFormat.binary32 ⟨sign, p, e⟩) =
      some ⟨sign, mantissa p, (p.log2 : Int) + e + (carry p : Int) - 23⟩ := by
  have hp : p ≠ 0 := by omega
  have hl := leading_bounds p hlo hhi
  have hm := mantissa_bounds p hlo hhi
  have hc := carry_le p
  let E := Int.toNat ((p.log2 : Int) + e + (carry p : Int) + 127)
  have hE0 : 0 < E := by dsimp [E]; omega
  have hEhi : E < 255 := by dsimp [E]; omega
  have hE : (E : Int) = (p.log2 : Int) + e + (carry p : Int) + 127 := by
    dsimp [E]
    omega
  have hf : mantissa p - 8388608 < 8388608 := by omega
  have hsum : 8388608 + (mantissa p - 8388608) = mantissa p := by omega
  rw [model_round_normal sign p e hp (by omega) hmin hmax]
  have hd := R2W01c.fields32_toDyadic sign E (mantissa p - 8388608) hE0 hEhi hf
  have he : (E : Int) - 150 = (p.log2 : Int) + e + (carry p : Int) - 23 := by
    rw [hE]
    omega
  simpa only [hsum, he] using hd

end Submission.R14NatNormal

namespace Submission.R14ExponentShift

open FloatLib.Floats Competition
open FloatLib.Floats.Formats.BinaryInterchange

def product (mx my : UInt32) : Nat := mx.toNat * my.toNat
def middleExponent (p : Nat) : Nat := p.log2 + R14NatNormal.carry p + 127
def storedFraction (p : Nat) : Nat := R14NatNormal.mantissa p - 8388608

theorem product_bounds (mx my : UInt32)
    (hx0 : 8388608 ≤ mx.toNat) (hx : mx.toNat < 16777216)
    (hy0 : 8388608 ≤ my.toNat) (hy : my.toNat < 16777216) :
    70368744177664 ≤ product mx my ∧ product mx my ≤ 281474943156225 := by
  have hl := Nat.mul_le_mul hx0 hy0
  have hh := Nat.mul_le_mul (show mx.toNat ≤ 16777215 by omega)
    (show my.toNat ≤ 16777215 by omega)
  norm_num at hl hh
  exact ⟨hl, hh⟩

theorem middle_bounds (p : Nat)
    (hp0 : 70368744177664 ≤ p) (hp : p ≤ 281474943156225) :
    173 ≤ middleExponent p ∧ middleExponent p ≤ 174 ∧ storedFraction p < 8388608 := by
  have hh : p < 281474976710656 := by omega
  have hl := R14NatNormal.leading_bounds p hp0 hh
  have hc := R14NatNormal.carry_le p
  have hm := R14NatNormal.mantissa_bounds p hp0 hh
  have hcases : p.log2 = 46 ∨ p.log2 = 47 := by omega
  unfold middleExponent storedFraction
  rcases hcases with h46 | h47
  · rw [h46]
    omega
  · have hc0 := R14NatNormal.no_carry_at_47 p hp h47
    rw [h47, hc0]
    omega

end Submission.R14ExponentShift

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
  simpa only [Int.toNat_natCast] using (UInt64.toNat_ofNatClamp_of_lt hfit)

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

end R17UInt64InterfaceProbe
