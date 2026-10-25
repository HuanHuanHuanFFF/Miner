/- Developer R14 component draft, NOT_COMPILED.
   Depends on frozen R14BiasRNE and R14ExponentShift math namespaces.
   No claim that the final public mul proof or runtime package is complete. -/
namespace Submission.R14DIntegerNormal

open FloatLib.Floats Competition
open FloatLib.Floats.Formats.BinaryInterchange
open FloatLib.Numerics

@[inline] def productWord (u v : UInt32) : UInt64 :=
  (R2W01b.mantissa u).toUInt64 * (R2W01b.mantissa v).toUInt64

abbrev productNat (u v : UInt32) : Nat :=
  R14ExponentShift.product (R2W01b.mantissa u) (R2W01b.mantissa v)

theorem product_bounds (u v : UInt32) :
    70368744177664 ≤ productNat u v ∧ productNat u v ≤ 281474943156225 := by
  have hu := R2W01c.mantissa_bounds u
  have hv := R2W01c.mantissa_bounds v
  exact R14ExponentShift.product_bounds _ _ hu.1 hu.2 hv.1 hv.2

theorem productWord_nat (u v : UInt32) :
    (productWord u v).toNat = productNat u v := by
  have hb := product_bounds u v
  unfold productWord productNat R14ExponentShift.product
  rw [UInt64.toNat_mul, UInt32.toNat_toUInt64, UInt32.toNat_toUInt64]
  exact Nat.mod_eq_of_lt (by change productNat u v < _; omega)

@[inline] def highWord (u v : UInt32) : UInt64 := productWord u v >>> 47
@[inline] def shiftWord (u v : UInt32) : UInt64 := 23 + highWord u v
@[inline] def roundedWord (u v : UInt32) : UInt64 :=
  R14BiasRNE.biased (productWord u v) (shiftWord u v)

theorem highWord_nat (u v : UInt32) :
    (highWord u v).toNat = (productNat u v).log2 - 46 := by
  have hb := product_bounds u v
  have hp : productNat u v ≠ 0 := by omega
  have hl := R14NatNormal.leading_bounds (productNat u v) hb.1 (by omega)
  have hlo := Nat.log2_self_le hp
  have hhi := Nat.lt_log2_self (n := productNat u v)
  have hc : (productNat u v).log2 = 46 ∨ (productNat u v).log2 = 47 := by omega
  rw [highWord, UInt64.toNat_shiftRight, productWord_nat]
  change productNat u v >>> 47 = (productNat u v).log2 - 46
  rw [Nat.shiftRight_eq_div_pow]
  rcases hc with hc | hc <;> rw [hc] at hlo hhi ⊢ <;> norm_num at hlo hhi ⊢ <;> omega

theorem shiftWord_values (u v : UInt32) : shiftWord u v = 23 ∨ shiftWord u v = 24 := by
  have hb := product_bounds u v
  have hl := R14NatNormal.leading_bounds (productNat u v) hb.1 (by omega)
  by_cases hc : (productNat u v).log2 = 46
  · have hh : highWord u v = 0 := by
      apply UInt64.toNat_inj.mp
      rw [highWord_nat, hc]
      rfl
    left
    simp [shiftWord, hh]
  · have hc' : (productNat u v).log2 = 47 := by omega
    have hh : highWord u v = 1 := by
      apply UInt64.toNat_inj.mp
      rw [highWord_nat, hc']
      rfl
    right
    simp [shiftWord, hh]

theorem shiftWord_nat (u v : UInt32) :
    (shiftWord u v).toNat = (productNat u v).log2 - 23 := by
  have hb := product_bounds u v
  have hl := R14NatNormal.leading_bounds (productNat u v) hb.1 (by omega)
  rw [shiftWord, UInt64.toNat_add, highWord_nat]
  change (23 + ((productNat u v).log2 - 46)) % 18446744073709551616 = _
  rw [Nat.mod_eq_of_lt (by omega)]
  omega

theorem roundedWord_nat (u v : UInt32) :
    (roundedWord u v).toNat = R14NatNormal.rounded (productNat u v) := by
  have hb := product_bounds u v
  have hp : (productWord u v).toNat < 281474976710656 := by rw [productWord_nat]; omega
  rw [roundedWord, R14BiasRNE.word_bias _ _ hp (shiftWord_values u v),
    FixedWord.roundShiftRightEven_toNat, productWord_nat, shiftWord_nat]
  rfl

theorem rounded_bounds (u v : UInt32) :
    8388608 ≤ R14NatNormal.rounded (productNat u v) ∧
      R14NatNormal.rounded (productNat u v) ≤ 16777216 := by
  let p := productNat u v
  have hb := product_bounds u v
  have hp : p ≠ 0 := by dsimp [p]; omega
  have hl := R14NatNormal.leading_bounds p hb.1 (by omega)
  have hlo := Nat.log2_self_le hp
  have hhi := Nat.lt_log2_self (n := p)
  have hrlo := shiftRight_le_roundShiftRightEven p (p.log2 - 23)
  have hrhi := roundShiftRightEven_le_shiftRight_add1 p (p.log2 - 23)
  have hc : p.log2 = 46 ∨ p.log2 = 47 := by omega
  change 8388608 ≤ roundShiftRightEven p (p.log2 - 23) ∧
    roundShiftRightEven p (p.log2 - 23) ≤ 16777216
  rcases hc with hc | hc <;>
    simp only [hc, Nat.shiftRight_eq_div_pow] at hlo hhi hrlo hrhi ⊢ <;>
    norm_num at hlo hhi hrlo hrhi ⊢ <;> omega

@[inline] def carryWord (u v : UInt32) : UInt64 := roundedWord u v >>> 24

theorem carryWord_nat (u v : UInt32) :
    (carryWord u v).toNat = R14NatNormal.carry (productNat u v) := by
  have hb := rounded_bounds u v
  rw [carryWord, UInt64.toNat_shiftRight, roundedWord_nat]
  change R14NatNormal.rounded (productNat u v) >>> 24 = _
  rw [Nat.shiftRight_eq_div_pow]
  unfold R14NatNormal.carry
  split <;> norm_num at * <;> omega

@[inline] def exponentWord (u v : UInt32) : UInt32 :=
  R14ExponentShift.ex u + R14ExponentShift.ex v - 127 +
    (highWord u v).toUInt32 + (carryWord u v).toUInt32

@[inline] def fractionWord (u v : UInt32) : UInt32 :=
  (roundedWord u v).toUInt32 &&& 0x007fffff

@[inline] def core (u v : UInt32) : UInt32 :=
  FastMul.mkW (R14ExponentShift.sign u v) (exponentWord u v) (fractionWord u v)

theorem small64_to32_nat (x : UInt64) (hx : x.toNat < 4294967296) :
    x.toUInt32.toNat = x.toNat := by
  rw [FastMul.toUInt32_eq]
  change x.toNat % 4294967296 = x.toNat
  exact Nat.mod_eq_of_lt hx

theorem exponentWord_nat (u v : UInt32)
    (hs : 128 ≤ R2W01c.wordExp u + R2W01c.wordExp v) :
    (exponentWord u v).toNat = R14ExponentShift.middleExponent (productNat u v) +
      R2W01c.wordExp u + R2W01c.wordExp v - 300 := by
  have hb := product_bounds u v
  have hl := R14NatNormal.leading_bounds (productNat u v) hb.1 (by omega)
  have hc := R14NatNormal.carry_le (productNat u v)
  have hu := R14ExponentShift.ex_bound u
  have hv := R14ExponentShift.ex_bound v
  rw [R14ExponentShift.ex_nat] at hu hv
  have hle : (127 : UInt32) ≤ R14ExponentShift.ex u + R14ExponentShift.ex v := by
    rw [UInt32.le_iff_toNat_le, R14ExponentShift.sum_nat]
    change 127 ≤ R2W01c.wordExp u + R2W01c.wordExp v
    omega
  have hbase : (R14ExponentShift.ex u + R14ExponentShift.ex v - 127).toNat =
      R2W01c.wordExp u + R2W01c.wordExp v - 127 := by
    rw [UInt32.toNat_sub_of_le _ _ hle, R14ExponentShift.sum_nat]
    rfl
  have hh : (highWord u v).toUInt32.toNat = (productNat u v).log2 - 46 := by
    rw [small64_to32_nat _ (by rw [highWord_nat]; omega), highWord_nat]
  have hcarry : (carryWord u v).toUInt32.toNat = R14NatNormal.carry (productNat u v) := by
    rw [small64_to32_nat _ (by rw [carryWord_nat]; omega), carryWord_nat]
  unfold exponentWord
  rw [UInt32.toNat_add, UInt32.toNat_add, hbase, hh, hcarry]
  rw [Nat.mod_eq_of_lt (by omega), Nat.mod_eq_of_lt (by omega)]
  unfold R14ExponentShift.middleExponent
  omega

theorem fractionWord_nat (u v : UInt32) :
    (fractionWord u v).toNat = R14ExponentShift.storedFraction (productNat u v) := by
  have hb := rounded_bounds u v
  have hr : (roundedWord u v).toNat < 4294967296 := by rw [roundedWord_nat]; omega
  rw [fractionWord, UInt32.toNat_and, small64_to32_nat _ hr, roundedWord_nat]
  change R14NatNormal.rounded (productNat u v) &&& (2 ^ 23 - 1) = _
  rw [Nat.and_two_pow_sub_one_eq_mod]
  unfold R14ExponentShift.storedFraction
  by_cases hc : R14NatNormal.rounded (productNat u v) = 16777216
  · simp [R14NatNormal.mantissa, hc]
  · simp only [R14NatNormal.mantissa, hc, ↓reduceIte]
    omega

theorem core_word (u v : UInt32)
    (hs : 128 ≤ R2W01c.wordExp u + R2W01c.wordExp v) :
    core u v = Model.NativeBinary32.mkBits
      (Bool.xor (R2W01c.wordSign u) (R2W01c.wordSign v))
      (R14ExponentShift.middleExponent (productNat u v) +
        R2W01c.wordExp u + R2W01c.wordExp v - 300)
      (R14ExponentShift.storedFraction (productNat u v)) := by
  calc
    core u v = FastMul.mkW (R14ExponentShift.sign u v)
        (UInt32.ofNat (exponentWord u v).toNat)
        (UInt32.ofNat (fractionWord u v).toNat) := by
          rw [UInt32.ofNat_toNat, UInt32.ofNat_toNat]
          rfl
    _ = Model.NativeBinary32.mkBits (R14ExponentShift.sign u v)
        (exponentWord u v).toNat (fractionWord u v).toNat :=
          FastMul.mkW_ofNat _ _ _
    _ = _ := by rw [exponentWord_nat u v hs, fractionWord_nat, R14ExponentShift.sign_eq]

end Submission.R14DIntegerNormal
