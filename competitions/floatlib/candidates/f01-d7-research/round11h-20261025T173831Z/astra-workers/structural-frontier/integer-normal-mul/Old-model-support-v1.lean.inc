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
open FloatLib.Floats Competition
open FloatLib.Floats.Formats.BinaryInterchange
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

namespace Submission.R14ExponentShift
open FloatLib.Floats Competition
open FloatLib.Floats.Formats.BinaryInterchange
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


end Submission.R14ExponentShift

namespace Submission.R14ExponentShift
open FloatLib.Floats Competition
open FloatLib.Floats.Formats.BinaryInterchange
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


end Submission.R14ExponentShift

namespace Submission.R14ExponentShift
open FloatLib.Floats Competition
open FloatLib.Floats.Formats.BinaryInterchange
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


end Submission.R14ExponentShift
