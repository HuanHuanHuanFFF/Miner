
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

theorem raw_mkBits_decode (sign : Bool) (e f : Nat)
    (he0 : 0 < e) (hehi : e < 255) (hf : f < 8388608) :
    Model.toDyadic? (R2W01c.rawModel (Model.NativeBinary32.mkBits sign e f)) =
      some ⟨sign, 8388608 + f, (e : Int) - 150⟩ := by
  rw [R2W01c.rawModel_eq_native32, Model.NativeBinary32.ofUInt32_mkBits]
  exact R2W01c.fields32_toDyadic sign e f he0 hehi hf

end Submission.R14NatNormal
