/- Scaled dyadic interval controller. Endpoint words and logical exponents avoid
   constructing the exact value or a widened normalized denominator at runtime.
   Old ContractTensor mathematical helper; typing/replay/AX/native cost NOT_RUN. -/
namespace Submission.R24DyadicInterval128
open FloatLib.Numerics FloatLib.Numerics.FixedWord
open FloatLib.Floats FloatLib.Floats.Formats.BinaryInterchange

@[inline] def check (lo hi : UInt128) (scale : Int) (mant : UInt64) (field : UInt32) : Bool :=
  if (1 : UInt32) ≤ field ∧ field ≤ 254 ∧ (8388608 : UInt64) < mant ∧ mant < 16777216 then
    let target := (field.toNat : Int) - 150
    let bounds := R24ScaledWord128.midpointWords 1 mant
    if R24ScaledWord128.fastAllowed lo (scale + 1) bounds.1 target &&
        R24ScaledWord128.fastAllowed hi (scale + 1) bounds.2 target then
      (!UInt128.less hi lo) &&
        ((DyadicCompare.compareNonnegative128ToWord lo (scale + 1) bounds.1 target == .gt) &&
          (DyadicCompare.compareNonnegative128ToWord hi (scale + 1) bounds.2 target == .lt))
    else false
  else false

theorem check_bounds (lo hi : UInt128) (scale : Int) (mant : UInt64) (field : UInt32)
    (h : check lo hi scale mant field = true) :
    1 ≤ field.toNat ∧ field.toNat ≤ 254 ∧ 8388608 < mant.toNat ∧ mant.toNat < 16777216 ∧
      ((2 * mant.toNat - 1 : Nat) : Real) * Model.bpow ((field.toNat : Int) - 150) <
        2 * (lo.toNat : Real) * Model.bpow scale ∧
      2 * (hi.toNat : Real) * Model.bpow scale <
        ((2 * mant.toNat + 1 : Nat) : Real) * Model.bpow ((field.toNat : Int) - 150) := by
  have hfit : (1 : UInt32) ≤ field ∧ field ≤ 254 ∧ (8388608 : UInt64) < mant ∧ mant < 16777216 := by
    by_contra hn
    simp only [check, if_neg hn] at h
    contradiction
  have hf0 : 1 ≤ field.toNat := UInt32.le_iff_toNat_le.mp hfit.1
  have hf1 : field.toNat ≤ 254 := UInt32.le_iff_toNat_le.mp hfit.2.1
  have hm0 : 8388608 < mant.toNat := UInt64.lt_iff_toNat_lt.mp hfit.2.2.1
  have hm1 : mant.toNat < 16777216 := UInt64.lt_iff_toNat_lt.mp hfit.2.2.2
  let target := (field.toNat : Int) - 150
  let bounds := R24ScaledWord128.midpointWords 1 mant
  have hcmp : DyadicCompare.compareNonnegative128ToWord lo (scale + 1) bounds.1 target = .gt ∧
      DyadicCompare.compareNonnegative128ToWord hi (scale + 1) bounds.2 target = .lt := by
    unfold check at h
    simp only [if_pos hfit] at h
    split at h
    · have hh : (!UInt128.less hi lo) = true ∧
          (DyadicCompare.compareNonnegative128ToWord lo (scale + 1) bounds.1 target = .gt ∧
            DyadicCompare.compareNonnegative128ToWord hi (scale + 1) bounds.2 target = .lt) := by
        simpa only [Bool.and_eq_true, beq_iff_eq] using h
      exact hh.2
    · simp at h
  have hl := R24ScaledWord128.compare_gt lo (scale + 1) bounds.1 target hcmp.1
  have hu := R24ScaledWord128.compare_lt hi (scale + 1) bounds.2 target hcmp.2
  obtain ⟨hbl, hbu⟩ := R24ScaledWord128.midpointWords_exact 1 mant (by decide) hm0 hm1
  have hpower (n : UInt128) : (n.toNat : Real) * Model.bpow (scale + 1) =
      2 * (n.toNat : Real) * Model.bpow scale := by
    rw [Model.bpow_add, Model.bpow_one]
    ring
  refine ⟨hf0, hf1, hm0, hm1, ?_, ?_⟩
  · simpa only [bounds, hbl, one_mul, hpower] using hl
  · simpa only [bounds, hbu, one_mul, hpower] using hu

theorem check_sound (sign : Bool) (lo hi : UInt128) (scale : Int) (mant : UInt64)
    (field : UInt32) (num den : Nat) (source : Int) (hd : 0 < den)
    (hlo : (lo.toNat : Real) * Model.bpow scale ≤ Model.scaledRatToReal num den source)
    (hhi : Model.scaledRatToReal num den source ≤ (hi.toNat : Real) * Model.bpow scale)
    (h : check lo hi scale mant field = true) :
    Model.NativeBinary32.roundRatScaled sign num den source =
      Model.NativeBinary32.mkBits sign field.toNat (mant.toNat - 8388608) := by
  obtain ⟨hf0, hf1, hm0, hm1, hl, hu⟩ := check_bounds lo hi scale mant field h
  let value := Model.scaledRatToReal num den source
  have hlow : ((2 * mant.toNat - 1 : Nat) : Real) * Model.bpow ((field.toNat : Int) - 150) <
      2 * value := by
    dsimp [value]
    linarith
  have hhigh : 2 * value <
      ((2 * mant.toNat + 1 : Nat) : Real) * Model.bpow ((field.toNat : Int) - 150) := by
    dsimp [value]
    linarith
  have hdR : (0 : Real) < den := by exact_mod_cast hd
  have hDv : (den : Real) * value = (num : Real) * Model.bpow source := by
    dsimp [value, Model.scaledRatToReal]
    field_simp [hdR.ne'] <;> ring
  have hl' : (den : Real) * (2 * mant.toNat - 1 : Nat) * Model.bpow ((field.toNat : Int) - 150) <
      2 * (num : Real) * Model.bpow source := by
    have hm := mul_lt_mul_of_pos_left hlow hdR
    nlinarith only [hm, hDv]
  have hu' : 2 * (num : Real) * Model.bpow source <
      (den : Real) * (2 * mant.toNat + 1 : Nat) * Model.bpow ((field.toNat : Int) - 150) := by
    have hm := mul_lt_mul_of_pos_left hhigh hdR
    nlinarith only [hm, hDv]
  have hr := R24ScaledCell.native32_scaled_strict sign num den mant.toNat source
    ((field.toNat : Int) - 150) hd hm0 hm1 (by omega) (by omega) hl' hu'
  simpa only [sub_add_cancel, Int.toNat_natCast] using hr

end Submission.R24DyadicInterval128
