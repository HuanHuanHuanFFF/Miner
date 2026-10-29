/- Word certificates for an independently established exact rational enclosure.
   The caller supplies enclosure inequalities, not a rounding-cell hypothesis.
   Old ContractTensor helpers only; typing/replay/dependency audit NOT_RUN. -/
namespace Submission.R24IntervalWord128
open FloatLib.Numerics.FixedWord

@[inline] def ordered (lo hi : UInt128) : Bool :=
  !UInt128.less hi lo

@[inline] def strictCheck (lo hi : UInt128) (den mant : UInt64) (field : UInt32) : Bool :=
  ordered lo hi &&
    (decide ((1 : UInt32) ≤ field) &&
      (decide (field ≤ (254 : UInt32)) &&
        (decide ((8388608 : UInt64) < mant) &&
          (decide (mant < (16777216 : UInt64)) &&
            (R24WordGap128.check lo den mant && R24WordGap128.check hi den mant)))))

theorem strictCheck_sound (sign : Bool) (lo hi : UInt128) (den mant : UInt64)
    (field : UInt32) (num : Nat) (hlo : lo.toNat ≤ num) (hhi : num ≤ hi.toNat)
    (h : strictCheck lo hi den mant field = true) :
    FloatLib.Floats.Formats.BinaryInterchange.Model.NativeBinary32.roundRatScaled
        sign num den.toNat ((field.toNat : Int) - 150) =
      FloatLib.Floats.Formats.BinaryInterchange.Model.NativeBinary32.mkBits
        sign field.toNat (mant.toNat - 8388608) := by
  have hh : ordered lo hi = true ∧ ((1 : UInt32) ≤ field ∧
      (field ≤ (254 : UInt32) ∧ ((8388608 : UInt64) < mant ∧
        (mant < (16777216 : UInt64) ∧
          (R24WordGap128.check lo den mant = true ∧
            R24WordGap128.check hi den mant = true))))) := by
    simpa only [strictCheck, Bool.and_eq_true, decide_eq_true_eq] using h
  obtain ⟨hd, _, hlow, _⟩ := R24WordGap128.check_midpoint_bounds lo den mant hh.2.2.2.2.2.1
  obtain ⟨_, _, _, hhigh⟩ := R24WordGap128.check_midpoint_bounds hi den mant hh.2.2.2.2.2.2
  have hm0 : 8388608 < mant.toNat := UInt64.lt_iff_toNat_lt.mp hh.2.2.2.1
  have hm1 : mant.toNat < 16777216 := UInt64.lt_iff_toNat_lt.mp hh.2.2.2.2.1
  have hf0 : 1 ≤ field.toNat := UInt32.le_iff_toNat_le.mp hh.2.1
  have hf1 : field.toNat ≤ 254 := UInt32.le_iff_toNat_le.mp hh.2.2.1
  have hl : den.toNat * (2 * mant.toNat - 1) < 2 * num := by omega
  have hu : 2 * num < den.toNat * (2 * mant.toNat + 1) := by omega
  have hr := R24CellPrimitive.native32_strict_cell sign num den.toNat mant.toNat
    ((field.toNat : Int) - 150) hd hm0 hm1 (by omega) (by omega) hl hu
  simpa only [sub_add_cancel, Int.toNat_natCast] using hr

@[inline] def powerCheck (lo hi : UInt128) (den : UInt64) (field : UInt32) : Bool :=
  ordered lo hi && (R24PowerGap128.check lo den field && R24PowerGap128.check hi den field)

theorem powerCheck_cell (lo hi : UInt128) (den : UInt64) (field : UInt32)
    (num : Nat) (hlo : lo.toNat ≤ num) (hhi : num ≤ hi.toNat)
    (h : powerCheck lo hi den field = true) :
    R24PowerCell.powerCell num den.toNat ((field.toNat : Int) - 150) = true := by
  have hh : ordered lo hi = true ∧
      (R24PowerGap128.check lo den field = true ∧ R24PowerGap128.check hi den field = true) := by
    simpa only [powerCheck, Bool.and_eq_true] using h
  have hlow := R24PowerGap128.check_powerCell lo den field hh.2.1
  have hhigh := R24PowerGap128.check_powerCell hi den field hh.2.2
  have hl : 0 < den.toNat ∧ 1 ≤ (field.toNat : Int) - 150 + 150 ∧
      (field.toNat : Int) - 150 + 150 ≤ 254 ∧
      (if (field.toNat : Int) - 150 + 150 = 1 then den.toNat * 16777215 ≤ 2 * lo.toNat
        else den.toNat * 33554431 ≤ 4 * lo.toNat) ∧
      2 * lo.toNat ≤ den.toNat * 16777217 := of_decide_eq_true hlow
  have hu : 0 < den.toNat ∧ 1 ≤ (field.toNat : Int) - 150 + 150 ∧
      (field.toNat : Int) - 150 + 150 ≤ 254 ∧
      (if (field.toNat : Int) - 150 + 150 = 1 then den.toNat * 16777215 ≤ 2 * hi.toNat
        else den.toNat * 33554431 ≤ 4 * hi.toNat) ∧
      2 * hi.toNat ≤ den.toNat * 16777217 := of_decide_eq_true hhigh
  have hlower :
      (if (field.toNat : Int) - 150 + 150 = 1 then den.toNat * 16777215 ≤ 2 * num
        else den.toNat * 33554431 ≤ 4 * num) := by
    split_ifs at hl ⊢ <;> omega
  unfold R24PowerCell.powerCell
  apply decide_eq_true
  exact ⟨hl.1, hl.2.1, hl.2.2.1, hlower, by omega⟩

theorem powerCheck_sound (sign : Bool) (lo hi : UInt128) (den : UInt64) (field : UInt32)
    (num : Nat) (hlo : lo.toNat ≤ num) (hhi : num ≤ hi.toNat)
    (h : powerCheck lo hi den field = true) :
    FloatLib.Floats.Formats.BinaryInterchange.Model.NativeBinary32.roundRatScaled
        sign num den.toNat ((field.toNat : Int) - 150) =
      FloatLib.Floats.Formats.BinaryInterchange.Model.NativeBinary32.mkBits sign field.toNat 0 := by
  have hr := R24PowerCell.powerCell_sound sign num den.toNat
    ((field.toNat : Int) - 150) (powerCheck_cell lo hi den field num hlo hhi h)
  simpa only [sub_add_cancel, Int.toNat_natCast] using hr

end Submission.R24IntervalWord128
