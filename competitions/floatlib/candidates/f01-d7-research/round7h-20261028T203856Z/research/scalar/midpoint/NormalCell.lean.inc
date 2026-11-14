/- Strict real cells for the actual native32 rational rounder.
   All source scalings are exact logical expressions. No finite-width
   normalized denominator, floating proposal, or finite-result premise. -/
namespace Submission.R24NormalCell
open FloatLib.Numerics
open FloatLib.Floats FloatLib.Floats.Formats.BinaryInterchange

noncomputable def lowerMagnitude (e f : Nat) : Real :=
  (8388608 + (f : Real) - (if f = 0 ∧ 1 < e then (1 : Real) / 4 else 1 / 2)) *
    Model.bpow ((e : Int) - 150)

noncomputable def upperMagnitude (e f : Nat) : Real :=
  (8388608 + (f : Real) + (1 : Real) / 2) * Model.bpow ((e : Int) - 150)

noncomputable def lowerSigned (sign : Bool) (e f : Nat) : Real :=
  if sign then -upperMagnitude e f else lowerMagnitude e f

noncomputable def upperSigned (sign : Bool) (e f : Nat) : Real :=
  if sign then -lowerMagnitude e f else upperMagnitude e f

theorem lowerMagnitude_pos (e f : Nat) : 0 < lowerMagnitude e f := by
  have hf : (0 : Real) ≤ f := Nat.cast_nonneg f
  unfold lowerMagnitude
  split <;> apply mul_pos _ (Model.bpow_pos _) <;> linarith

private theorem normalized_value (num den : Nat) (source target : Int) :
    let scaled := RationalBinary.scaleByPowerOfTwo num den (source - target)
    (scaled.1 : Real) / scaled.2 * Model.bpow target =
      Model.scaledRatToReal num den source := by
  dsimp only
  rw [Model.scaleByPowerOfTwo_real]
  rw [Model.scaledRatToReal_mul_bpow]
  congr 1
  omega

theorem native32_field_strict (sign : Bool) (num den e f : Nat) (source : Int)
    (hd : 0 < den) (he0 : 1 ≤ e) (he1 : e ≤ 254) (hf : f < 8388608)
    (hl : lowerMagnitude e f < Model.scaledRatToReal num den source)
    (hu : Model.scaledRatToReal num den source < upperMagnitude e f) :
    Model.NativeBinary32.roundRatScaled sign num den source =
      Model.NativeBinary32.mkBits sign e f := by
  let mant : Nat := 8388608 + f
  let target : Int := (e : Int) - 150
  let scaled := RationalBinary.scaleByPowerOfTwo num den (source - target)
  have hm0 : 8388608 ≤ mant := by dsimp [mant]; omega
  have hm1 : mant < 16777216 := by dsimp [mant]; omega
  have ht0 : 1 ≤ target + 150 := by dsimp [target]; omega
  have ht1 : target + 150 ≤ 254 := by dsimp [target]; omega
  have hte : (target + 150).toNat = e := by dsimp [target]; omega
  have hmf : mant - 8388608 = f := by dsimp [mant]; omega
  have hmc : (mant : Real) = 8388608 + (f : Real) := by simp [mant]
  have hdR : (0 : Real) < den := by exact_mod_cast hd
  have hp : 0 < Model.bpow target := Model.bpow_pos target
  have hvalue : (den : Real) * Model.scaledRatToReal num den source =
      (num : Real) * Model.bpow source := by
    unfold Model.scaledRatToReal
    field_simp [hdR.ne'] <;> ring
  have hlweak : ((mant : Real) - (1 : Real) / 2) * Model.bpow target <
      Model.scaledRatToReal num den source := by
    by_cases hpower : f = 0 ∧ 1 < e
    · have h := hl
      simp only [lowerMagnitude, hpower, ite_true] at h
      rw [hmc]
      change (8388608 + (f : Real) - (1 : Real) / 2) *
        Model.bpow ((e : Int) - 150) < _
      have hp' := Model.bpow_pos ((e : Int) - 150)
      nlinarith only [h, hp']
    · simpa only [lowerMagnitude, hpower, ite_false, hmc, target] using hl
  have hupper : Model.scaledRatToReal num den source <
      ((mant : Real) + (1 : Real) / 2) * Model.bpow target := by
    simpa only [upperMagnitude, hmc, target] using hu
  have hcL : ((2 * mant - 1 : Nat) : Real) = 2 * (mant : Real) - 1 := by
    rw [Nat.cast_sub (by omega : 1 ≤ 2 * mant)]
    norm_num
  have hcU : ((2 * mant + 1 : Nat) : Real) = 2 * (mant : Real) + 1 := by norm_num
  have hl2 : (den : Real) * (2 * mant - 1 : Nat) * Model.bpow target <
      2 * (num : Real) * Model.bpow source := by
    have h := mul_lt_mul_of_pos_left hlweak hdR
    rw [hvalue] at h
    rw [hcL]
    nlinarith only [h]
  have hu2 : 2 * (num : Real) * Model.bpow source <
      (den : Real) * (2 * mant + 1 : Nat) * Model.bpow target := by
    have h := mul_lt_mul_of_pos_left hupper hdR
    rw [hvalue] at h
    rw [hcU]
    nlinarith only [h]
  obtain ⟨hdS, hlS, huS⟩ := R24ScaledCell.normalize_strict
    num den mant source target hd hl2 hu2
  have hrescale := R24RescaleNative32.roundRatScaled_rescale sign num den source target
  change Model.NativeBinary32.roundRatScaled sign num den source =
    Model.NativeBinary32.roundRatScaled sign scaled.1 scaled.2 target at hrescale
  rw [hrescale]
  by_cases hf0 : f = 0
  · have hm : mant = 8388608 := by simp only [mant, hf0, Nat.add_zero]
    by_cases he : e = 1
    · have ht : target = -149 := by dsimp [target]; omega
      have h := R24PowerCell.native32_min_normal sign scaled.1 scaled.2 hdS
        (by simpa only [hm] using Nat.le_of_lt hlS)
        (by simpa only [hm] using Nat.le_of_lt huS)
      simpa only [ht, he, hf0] using h
    · have he2 : 2 ≤ e := by omega
      have hpower : f = 0 ∧ 1 < e := ⟨hf0, by omega⟩
      have hv := normalized_value num den source target
      change (scaled.1 : Real) / scaled.2 * Model.bpow target =
        Model.scaledRatToReal num den source at hv
      have hlow : (33554431 : Real) / 4 * Model.bpow target <
          (scaled.1 : Real) / scaled.2 * Model.bpow target := by
        rw [hv]
        have h := hl
        simp only [lowerMagnitude, hpower, ite_true, hf0, Nat.cast_zero, add_zero] at h
        norm_num only at h
        simpa only [target] using h
      have hratio : (33554431 : Real) / 4 < (scaled.1 : Real) / scaled.2 :=
        (mul_lt_mul_right hp).mp hlow
      have hdSR : (0 : Real) < scaled.2 := by exact_mod_cast hdS
      have hmul := (lt_div_iff₀ hdSR).mp hratio
      have hcross : (scaled.2 : Real) * 33554431 < 4 * (scaled.1 : Real) := by
        nlinarith only [hmul]
      have hl4 : scaled.2 * 33554431 ≤ 4 * scaled.1 := by
        exact Nat.le_of_lt (by exact_mod_cast hcross)
      have h := R24PowerCell.native32_power_above_min sign scaled.1 scaled.2 target
        hdS (by dsimp [target]; omega) ht1 hl4
        (by simpa only [hm] using Nat.le_of_lt huS)
      simpa only [hte, hf0] using h
  · have h := R24CellPrimitive.native32_strict_cell sign scaled.1 scaled.2 mant target
      hdS (by dsimp [mant]; omega) hm1 ht0 ht1 hlS huS
    simpa only [hte, hmf] using h

theorem mkBits_fields (q : UInt32) :
    Model.NativeBinary32.mkBits (Model.NativeBinary32.signBit q)
      (Model.NativeBinary32.expField q).toNat (Model.NativeBinary32.fracField q).toNat = q := by
  have hs := Model.NativeBinary32.signBit_eq (Model.NativeBinary32.ofUInt32 q)
  have he := Model.NativeBinary32.expField_toNat (Model.NativeBinary32.ofUInt32 q)
  have hf := Model.NativeBinary32.fracField_toNat (Model.NativeBinary32.ofUInt32 q)
  simp only [Model.NativeBinary32.toUInt32_ofUInt32] at hs he hf
  have h := congrArg Model.NativeBinary32.toUInt32
    (Model.ofFields_signBit_expField_fracField (Model.NativeBinary32.ofUInt32 q))
  simpa only [Model.NativeBinary32.toUInt32_ofFields,
    Model.NativeBinary32.toUInt32_ofUInt32, ← hs, ← he, ← hf] using h

theorem native32_raw_strict (q : UInt32) (sign : Bool) (num den : Nat)
    (source : Int) (S : Real) (hd : 0 < den)
    (he0 : 1 ≤ (Model.NativeBinary32.expField q).toNat)
    (he1 : (Model.NativeBinary32.expField q).toNat ≤ 254)
    (hf : (Model.NativeBinary32.fracField q).toNat < 8388608)
    (hsource : S = Model.signedScaledRatToReal sign num den source)
    (hl : lowerSigned (Model.NativeBinary32.signBit q)
      (Model.NativeBinary32.expField q).toNat (Model.NativeBinary32.fracField q).toNat < S)
    (hu : S < upperSigned (Model.NativeBinary32.signBit q)
      (Model.NativeBinary32.expField q).toNat (Model.NativeBinary32.fracField q).toNat) :
    Model.NativeBinary32.roundRatScaled sign num den source = q := by
  let e := (Model.NativeBinary32.expField q).toNat
  let f := (Model.NativeBinary32.fracField q).toNat
  have hm0 := Model.scaledRatToReal_nonneg num den source
  have hL0 := lowerMagnitude_pos e f
  have hsign : sign = Model.NativeBinary32.signBit q := by
    cases sign <;> cases hq : Model.NativeBinary32.signBit q
    · rfl
    · have hS : S = Model.scaledRatToReal num den source := by
        simpa only [Model.signedScaledRatToReal, Bool.false_eq_true, ite_false] using hsource
      have hU : S < -lowerMagnitude e f := by
        simpa only [upperSigned, hq, ite_true, e, f] using hu
      linarith
    · have hS : S = -Model.scaledRatToReal num den source := by
        simpa only [Model.signedScaledRatToReal, ite_true] using hsource
      have hL : lowerMagnitude e f < S := by
        simpa only [lowerSigned, hq, Bool.false_eq_true, ite_false, e, f] using hl
      linarith
    · rfl
  rw [← hsign] at hl hu
  have hlow : lowerMagnitude e f < Model.scaledRatToReal num den source := by
    cases sign
    · have hS : S = Model.scaledRatToReal num den source := by simpa [Model.signedScaledRatToReal] using hsource
      have hL : lowerMagnitude e f < S := by
        simpa only [lowerSigned, Bool.false_eq_true, ite_false, e, f] using hl
      simpa only [hS] using hL
    · have hS : S = -Model.scaledRatToReal num den source := by simpa [Model.signedScaledRatToReal] using hsource
      have hU : S < -lowerMagnitude e f := by simpa only [upperSigned, ite_true, e, f] using hu
      linarith
  have hupp : Model.scaledRatToReal num den source < upperMagnitude e f := by
    cases sign
    · have hS : S = Model.scaledRatToReal num den source := by simpa [Model.signedScaledRatToReal] using hsource
      have hU : S < upperMagnitude e f := by
        simpa only [upperSigned, Bool.false_eq_true, ite_false, e, f] using hu
      simpa only [hS] using hU
    · have hS : S = -Model.scaledRatToReal num den source := by simpa [Model.signedScaledRatToReal] using hsource
      have hL : -upperMagnitude e f < S := by simpa only [lowerSigned, ite_true, e, f] using hl
      linarith
  calc
    Model.NativeBinary32.roundRatScaled sign num den source =
        Model.NativeBinary32.mkBits sign e f :=
      native32_field_strict sign num den e f source hd he0 he1 hf hlow hupp
    _ = q := by rw [hsign]; exact mkBits_fields q

end Submission.R24NormalCell
