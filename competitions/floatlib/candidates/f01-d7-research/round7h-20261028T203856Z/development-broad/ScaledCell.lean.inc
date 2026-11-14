/- Old ContractTensor mathematical component. Source and candidate exponents
   remain separate; logical normalization may use arbitrary Nat denominators,
   but the executable checker below never constructs them. NOT_COMPILED. -/
namespace Submission.R24ScaledCell

open FloatLib.Floats FloatLib.Floats.Formats.BinaryInterchange
open FloatLib.Numerics

theorem normalize_strict (num den mant : Nat) (source target : Int)
    (hd : 0 < den)
    (hl : (den : Real) * (2 * mant - 1 : Nat) * Model.bpow target <
      2 * (num : Real) * Model.bpow source)
    (hu : 2 * (num : Real) * Model.bpow source <
      (den : Real) * (2 * mant + 1 : Nat) * Model.bpow target) :
    let scaled := RationalBinary.scaleByPowerOfTwo num den (source - target)
    0 < scaled.2 ∧ scaled.2 * (2 * mant - 1) < 2 * scaled.1 ∧
      2 * scaled.1 < scaled.2 * (2 * mant + 1) := by
  let scaled := RationalBinary.scaleByPowerOfTwo num den (source - target)
  let v : Real := (num : Real) / den * Model.bpow (source - target)
  have hdR : (0 : Real) < den := by exact_mod_cast hd
  have hs : Model.bpow (source - target) * Model.bpow target = Model.bpow source := by
    rw [← Model.bpow_add]
    congr 1
    omega
  have hlN : (den : Real) * (2 * mant - 1 : Nat) <
      2 * (num : Real) * Model.bpow (source - target) := by
    apply (mul_lt_mul_right (Model.bpow_pos target)).mp
    simpa only [mul_assoc, hs] using hl
  have huN : 2 * (num : Real) * Model.bpow (source - target) <
      (den : Real) * (2 * mant + 1 : Nat) := by
    apply (mul_lt_mul_right (Model.bpow_pos target)).mp
    simpa only [mul_assoc, hs] using hu
  have hDv : (den : Real) * (2 * v) =
      2 * (num : Real) * Model.bpow (source - target) := by
    dsimp [v]
    field_simp [hdR.ne'] <;> ring
  have hlV : (2 * mant - 1 : Nat) < 2 * v := by
    apply (mul_lt_mul_left hdR).mp
    rw [hDv]
    exact hlN
  have huV : 2 * v < (2 * mant + 1 : Nat) := by
    apply (mul_lt_mul_left hdR).mp
    rw [hDv]
    exact huN
  have hdS : 0 < scaled.2 := Nat.pos_of_ne_zero
    (RationalBinary.scaleByPowerOfTwo_snd_ne_zero num den (source - target) (Nat.ne_of_gt hd))
  have hdSR : (0 : Real) < scaled.2 := by exact_mod_cast hdS
  have hv : (scaled.1 : Real) / scaled.2 = v := by
    simpa only [Model.scaledRatToReal] using Model.scaleByPowerOfTwo_real num den (source - target)
  have hSv : (scaled.2 : Real) * v = scaled.1 := by
    rw [← hv]
    field_simp [hdSR.ne']
  have hlS : (scaled.2 : Real) * (2 * mant - 1 : Nat) < 2 * (scaled.1 : Real) := by
    calc
      (scaled.2 : Real) * (2 * mant - 1 : Nat) < (scaled.2 : Real) * (2 * v) :=
        mul_lt_mul_of_pos_left hlV hdSR
      _ = 2 * (scaled.1 : Real) := by nlinarith only [hSv]
  have huS : 2 * (scaled.1 : Real) < (scaled.2 : Real) * (2 * mant + 1 : Nat) := by
    calc
      2 * (scaled.1 : Real) = (scaled.2 : Real) * (2 * v) := by nlinarith only [hSv]
      _ < (scaled.2 : Real) * (2 * mant + 1 : Nat) := mul_lt_mul_of_pos_left huV hdSR
  refine ⟨hdS, ?_, ?_⟩
  · exact_mod_cast hlS
  · exact_mod_cast huS

theorem native32_scaled_strict (sign : Bool) (num den mant : Nat) (source target : Int)
    (hd : 0 < den) (hmlo : 8388608 < mant) (hmhi : mant < 16777216)
    (hexplo : 1 ≤ target + 150) (hexphi : target + 150 ≤ 254)
    (hl : (den : Real) * (2 * mant - 1 : Nat) * Model.bpow target <
      2 * (num : Real) * Model.bpow source)
    (hu : 2 * (num : Real) * Model.bpow source <
      (den : Real) * (2 * mant + 1 : Nat) * Model.bpow target) :
    Model.NativeBinary32.roundRatScaled sign num den source =
      Model.NativeBinary32.mkBits sign (target + 150).toNat (mant - 8388608) := by
  let scaled := RationalBinary.scaleByPowerOfTwo num den (source - target)
  let v : Real := (num : Real) / den * Model.bpow (source - target)
  obtain ⟨hdS, hlS, huS⟩ := normalize_strict num den mant source target hd hl hu
  have hv : (scaled.1 : Real) / scaled.2 = v := by
    simpa only [Model.scaledRatToReal] using Model.scaleByPowerOfTwo_real num den (source - target)
  have hdSR : (0 : Real) < scaled.2 := by exact_mod_cast hdS
  obtain ⟨hboundL, hboundU⟩ := Submission.R24CellPrimitive.normal_ratio_nat_bounds
    scaled.1 scaled.2 mant hdS hmlo hmhi hlS huS
  have hvL : (8388608 : Real) ≤ v := by
    rw [← hv]
    apply (le_div_iff₀ hdSR).mpr
    exact_mod_cast hboundL
  have hvU : v < (16777216 : Real) := by
    rw [← hv]
    apply (div_lt_iff₀ hdSR).mpr
    exact_mod_cast hboundU
  have hn : num ≠ 0 := by
    intro hz
    simp only [v, hz, Nat.cast_zero, zero_div, zero_mul] at hvL
    norm_num at hvL
  have hp23 : Model.bpow (23 : Int) = (8388608 : Real) := by
    norm_num [Model.bpow, FloatLib.Floats.Formats.Flocq.bpow,
      binaryRadix, Radix.toReal]
  have hp24 : Model.bpow (24 : Int) = (16777216 : Real) := by
    norm_num [Model.bpow, FloatLib.Floats.Formats.Flocq.bpow,
      binaryRadix, Radix.toReal]
  have hs : Model.bpow (source - target) * Model.bpow (target - source) = 1 := by
    rw [← Model.bpow_add, show source - target + (target - source) = 0 by omega,
      Model.bpow_zero]
  have hback : v * Model.bpow (target - source) = (num : Real) / den := by
    dsimp [v]
    rw [mul_assoc, hs, mul_one]
  have hlog : RationalBinary.floorLog2 num den = target - source + 23 := by
    apply Model.floorLog2_eq_of_bounds num den (target - source + 23) hn (Nat.ne_of_gt hd)
    · rw [Model.bpow_add, hp23, mul_comm]
      calc
        (8388608 : Real) * Model.bpow (target - source) ≤
            v * Model.bpow (target - source) :=
          mul_le_mul_of_nonneg_right hvL (Model.bpow_nonneg _)
        _ = (num : Real) / den := hback
    · rw [show target - source + 23 + 1 = target - source + 24 by omega,
        Model.bpow_add, hp24, mul_comm]
      calc
        (num : Real) / den = v * Model.bpow (target - source) := hback.symm
        _ < (16777216 : Real) * Model.bpow (target - source) :=
          mul_lt_mul_of_pos_right hvU (Model.bpow_pos _)
  have hr := Submission.R24CellPrimitive.quotient_strict_midpoint
    scaled.1 scaled.2 mant hdS (by omega) hlS huS
  have htotal : target - source + 23 + source = target + 23 := by omega
  have hshift : (23 : Int) - (target - source + 23) = source - target := by omega
  have hbig : ¬ target + 23 > 127 := by omega
  have hsmall : ¬ target + 23 < -150 := by omega
  have hnormal : ¬ target + 23 < -126 := by omega
  have hc : mant ≠ Model.pow2 24 := by
    have hp : Model.pow2 24 = 16777216 := by decide
    rw [hp]
    omega
  have hencoded : target + 23 + 127 = target + 150 := by omega
  have hpow23 : Model.pow2 23 = 8388608 := by decide
  simp only [Model.NativeBinary32.roundRatScaled, beq_iff_eq, Nat.ne_of_gt hd,
    hn, if_false, hlog, htotal, hbig, hsmall, hnormal, hshift]
  simp only [hr, beq_iff_eq, hc, if_false, hbig, hencoded, hpow23]

end Submission.R24ScaledCell
