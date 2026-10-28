namespace Submission.R14NativeProduct

open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange
open FloatLib.Numerics
open Model.NativeBinary32

theorem model_mul_of_nonzero_decodes {fmt : FloatFormat}
    (x y : Model fmt) (dx dy : FloatLib.Numerics.Dyadic)
    (hx : Model.toDyadic? x = some dx) (hy : Model.toDyadic? y = some dy)
    (hx0 : dx.significand ≠ 0) (hy0 : dy.significand ≠ 0) :
    Model.mul x y = Model.roundDyadic fmt
      ⟨Bool.xor dx.negative dy.negative, dx.significand * dy.significand,
        dx.exponent + dy.exponent⟩ := by
  rw [Model.Proof.mul_eq_spec]
  unfold Model.Spec.mul
  rw [hx, hy]
  simp [hx0, hy0]

end Submission.R14NativeProduct


/- Draft: source dependency is retained df5c plus no other R14 fragment.
This version works directly in the actual Nat/Int word-rounder specification. -/
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

/-- Unlike the old NormalBand helper, this covers every normal raw exponent1..254. -/
theorem raw_normal_decode (u : UInt32)
    (he0 : 0 < R2W01c.wordExp u) (hehi : R2W01c.wordExp u < 255) :
    Model.toDyadic? (R2W01c.rawModel u) =
      some ⟨R2W01c.wordSign u, (R2W01b.mantissa u).toNat,
        (R2W01c.wordExp u : Int) - 150⟩ := by
  rw [R2W01c.rawModel_eq_ofUInt32]
  change Model.toDyadic? (R2W01c.raw32 u) = _
  rw [R2W01c.raw32_eq_fields, R2W01c.mantissa_toNat]
  exact R2W01c.fields32_toDyadic (R2W01c.wordSign u) (R2W01c.wordExp u)
    (R2W01c.wordFrac u) he0 hehi (R2W01c.wordFrac_lt u)


end Submission.R14NatNormal



/- Dependencies: model_mul_of_nonzero_decodes; nat-normal-form; exponent-shift-algebra. -/
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

@[inline] def ex (u : UInt32) : UInt32 := Model.NativeBinary32.expField u

theorem ex_nat (u : UInt32) : (ex u).toNat = R2W01c.wordExp u := by
  rw [ex, Model.NativeBinary32.expField, UInt32.toNat_and, UInt32.toNat_shiftRight]
  change (u.toNat >>> 23) &&& (2 ^ 8 - 1) = u.toNat / 8388608 % 256
  rw [Nat.and_two_pow_sub_one_eq_mod, Nat.shiftRight_eq_div_pow]

theorem ex_bound (u : UInt32) : (ex u).toNat < 256 := by
  rw [ex_nat]
  exact Nat.mod_lt _ (by decide)

theorem sum_nat (u v : UInt32) :
    (ex u + ex v).toNat = R2W01c.wordExp u + R2W01c.wordExp v := by
  have hu := ex_bound u
  have hv := ex_bound v
  rw [UInt32.toNat_add, Nat.mod_eq_of_lt (by omega), ex_nat, ex_nat]

@[inline] def sign (u v : UInt32) : Bool :=
  Bool.xor (decide ((2147483648 : UInt32) ≤ u)) (decide ((2147483648 : UInt32) ≤ v))

theorem sign_eq (u v : UInt32) :
    sign u v = Bool.xor (R2W01c.wordSign u) (R2W01c.wordSign v) := by
  simp only [sign, R2W01c.wordSign, UInt32.le_iff_toNat_le]
  rfl


end Submission.R14ExponentShift


/- Developer R14 component draft, NOT_COMPILED.
   Uses retained FastMul.rseAny and R14ExponentShift math namespaces.
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
  FastMul.rseAny (productWord u v) (shiftWord u v)

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
  rw [roundedWord, FastMul.rseAny_eq, FixedWord.roundShiftRightEven_toNat,
    productWord_nat, shiftWord_nat]
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


namespace Submission.R14ExponentShift
open FloatLib.Floats Competition
open FloatLib.Floats.Formats.BinaryInterchange

@[inline] def core (u v : UInt32) : UInt32 := R14DIntegerNormal.core u v

theorem core_word (u v : UInt32)
    (hs : 128 ≤ R2W01c.wordExp u + R2W01c.wordExp v)
    (hs' : R2W01c.wordExp u + R2W01c.wordExp v ≤ 380) :
    core u v = Model.NativeBinary32.mkBits
      (Bool.xor (R2W01c.wordSign u) (R2W01c.wordSign v))
      (middleExponent (product (R2W01b.mantissa u) (R2W01b.mantissa v)) +
        R2W01c.wordExp u + R2W01c.wordExp v - 300)
      (storedFraction (product (R2W01b.mantissa u) (R2W01b.mantissa v))) := by
  exact R14DIntegerNormal.core_word u v hs

theorem model_mul_normal_fields (x y : Model FloatFormat.binary32)
    (sx sy : Bool) (a b eu ev : Nat)
    (ha0 : 8388608 ≤ a) (ha : a < 16777216)
    (hb0 : 8388608 ≤ b) (hb : b < 16777216)
    (hs : 128 ≤ eu + ev) (hs' : eu + ev ≤ 380)
    (hx : Model.toDyadic? x = some ⟨sx, a, (eu : Int) - 150⟩)
    (hy : Model.toDyadic? y = some ⟨sy, b, (ev : Int) - 150⟩) :
    Model.mul x y = Model.ofFields FloatFormat.binary32 (Bool.xor sx sy)
      (middleExponent (a * b) + eu + ev - 300) (storedFraction (a * b)) := by
  let p := a * b
  let s := eu + ev
  have hpLo : 70368744177664 ≤ p := by
    have h := Nat.mul_le_mul ha0 hb0
    norm_num at h
    exact h
  have hpHi : p ≤ 281474943156225 := by
    have h := Nat.mul_le_mul (show a ≤ 16777215 by omega) (show b ≤ 16777215 by omega)
    norm_num at h
    exact h
  have hpFit : p < 281474976710656 := by omega
  have hp0 : p ≠ 0 := by omega
  have hl := R14NatNormal.leading_bounds p hpLo hpFit
  have hc := R14NatNormal.carry_le p
  have hmRange := middle_bounds p hpLo hpHi
  have hmin : -126 ≤ (p.log2 : Int) + ((s : Int) - 300) := by dsimp [s]; omega
  have hmax : (p.log2 : Int) + ((s : Int) - 300) + (R14NatNormal.carry p : Int) ≤ 127 := by
    dsimp [middleExponent, s] at hmRange ⊢
    omega
  have hm := R14NativeProduct.model_mul_of_nonzero_decodes x y
    ⟨sx, a, (eu : Int) - 150⟩ ⟨sy, b, (ev : Int) - 150⟩
    hx hy (show a ≠ 0 by omega) (show b ≠ 0 by omega)
  change Model.mul x y = Model.roundDyadic FloatFormat.binary32
    ⟨Bool.xor sx sy, p, (eu : Int) - 150 + ((ev : Int) - 150)⟩ at hm
  have hExp : (eu : Int) - 150 + ((ev : Int) - 150) = (s : Int) - 300 := by dsimp [s]; omega
  rw [hExp] at hm
  have hTarget : Int.toNat ((p.log2 : Int) + ((s : Int) - 300) +
      (R14NatNormal.carry p : Int) + 127) = middleExponent p + s - 300 := by
    dsimp [middleExponent, s]
    omega
  rw [R14NatNormal.model_round_normal _ p ((s : Int) - 300)
    hp0 (by omega) hmin hmax, hTarget] at hm
  have hmFields : Model.mul x y = Model.ofFields FloatFormat.binary32 (Bool.xor sx sy)
      (middleExponent p + s - 300) (storedFraction p) := hm
  change Model.mul x y = Model.ofFields FloatFormat.binary32 (Bool.xor sx sy)
    (middleExponent p + eu + ev - 300) (storedFraction p)
  rw [Nat.add_assoc (middleExponent p) eu ev]
  exact hmFields

theorem core_model (u v : UInt32)
    (hu0 : 0 < R2W01c.wordExp u) (hu : R2W01c.wordExp u < 255)
    (hv0 : 0 < R2W01c.wordExp v) (hv : R2W01c.wordExp v < 255)
    (hs : 128 ≤ R2W01c.wordExp u + R2W01c.wordExp v)
    (hs' : R2W01c.wordExp u + R2W01c.wordExp v ≤ 380) :
    Model.NativeBinary32.ofUInt32 (core u v) =
      Model.mul (R2W01c.rawModel u) (R2W01c.rawModel v) := by
  have hx := R14NatNormal.raw_normal_decode u hu0 hu
  have hy := R14NatNormal.raw_normal_decode v hv0 hv
  have ha := R2W01c.mantissa_bounds u
  have hb := R2W01c.mantissa_bounds v
  have hm := model_mul_normal_fields (R2W01c.rawModel u) (R2W01c.rawModel v)
    (R2W01c.wordSign u) (R2W01c.wordSign v)
    (R2W01b.mantissa u).toNat (R2W01b.mantissa v).toNat
    (R2W01c.wordExp u) (R2W01c.wordExp v)
    ha.1 ha.2 hb.1 hb.2 hs hs' hx hy
  rw [core_word u v hs hs', Model.NativeBinary32.ofUInt32_mkBits]
  exact hm.symm

theorem core_spec (x y : Binary32)
    (hx0 : 0 < R2W01c.wordExp x.raw.1) (hx : R2W01c.wordExp x.raw.1 < 255)
    (hy0 : 0 < R2W01c.wordExp y.raw.1) (hy : R2W01c.wordExp y.raw.1 < 255)
    (hs : 128 ≤ R2W01c.wordExp x.raw.1 + R2W01c.wordExp y.raw.1)
    (hs' : R2W01c.wordExp x.raw.1 + R2W01c.wordExp y.raw.1 ≤ 380) :
    R7W02.fromRaw (core x.raw.1 y.raw.1) = ExecFloat.Spec.mul x y := by
  apply Configured.Family.toModel_injective
  change ExecFloat.Binary.toModel (R7W02.fromRaw (core x.raw.1 y.raw.1)) =
    ExecFloat.Binary.toModel (ExecFloat.Spec.mul x y)
  rw [R7W02.fromRaw_toModel, ← ExecFloat.Proof.mul_eq_spec, R7W01.exec_toModel_mul,
    ← Model.Proof.mul_eq_spec, R7W02.exec_toModel_eq_rawModel x,
    R7W02.exec_toModel_eq_rawModel y, ← R2W01c.rawModel_eq_native32 x.raw.1,
    ← R2W01c.rawModel_eq_native32 y.raw.1]
  exact core_model x.raw.1 y.raw.1 hx0 hx hy0 hy hs hs'

@[inline] def eligible (u v : UInt32) : Bool :=
  (decide (ex u - 1 ≤ 253) && decide (ex v - 1 ≤ 253)) &&
    decide (ex u + ex v - 128 ≤ 252)

theorem eligible_conditions (u v : UInt32) (h : eligible u v = true) :
    0 < R2W01c.wordExp u ∧ R2W01c.wordExp u < 255 ∧
    0 < R2W01c.wordExp v ∧ R2W01c.wordExp v < 255 ∧
    128 ≤ R2W01c.wordExp u + R2W01c.wordExp v ∧
    R2W01c.wordExp u + R2W01c.wordExp v ≤ 380 := by
  simp only [eligible, Bool.and_eq_true, decide_eq_true_eq] at h
  rcases h with ⟨⟨hu, hv⟩, hs⟩
  have hub := ex_bound u
  have hvb := ex_bound v
  have heSum := sum_nat u v
  rw [UInt32.le_iff_toNat_le, UInt32.toNat_sub] at hu hv hs
  change (4294967295 + (ex u).toNat) % 4294967296 ≤ 253 at hu
  change (4294967295 + (ex v).toNat) % 4294967296 ≤ 253 at hv
  change (4294967168 + (ex u + ex v).toNat) % 4294967296 ≤ 252 at hs
  rw [ex_nat] at hu hv hub hvb
  rw [heSum] at hs
  omega

@[inline] def guardedMul (fallback : Binary32 → Binary32 → Binary32)
    (x y : Binary32) : Binary32 :=
  if eligible x.raw.1 y.raw.1 then R7W02.fromRaw (core x.raw.1 y.raw.1)
  else fallback x y

theorem guardedMul_spec (fallback : Binary32 → Binary32 → Binary32)
    (hf : ∀ x y, fallback x y = ExecFloat.Spec.mul x y) (x y : Binary32) :
    guardedMul fallback x y = ExecFloat.Spec.mul x y := by
  unfold guardedMul
  split
  · rename_i h
    rcases eligible_conditions x.raw.1 y.raw.1 h with ⟨hx0, hx, hy0, hy, hs, hs'⟩
    exact core_spec x y hx0 hx hy0 hy hs hs'
  · exact hf x y

end Submission.R14ExponentShift

