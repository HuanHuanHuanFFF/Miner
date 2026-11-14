/- Fixed-word closed cells for binary32 powers, including the minimum normal.
   Old ContractTensor helper only. New typing/replay/dependency audit NOT_RUN. -/
namespace Submission.R24PowerGap128
open FloatLib.Numerics.FixedWord

@[inline] def halfCheck (gap den : UInt64) : Bool :=
  decide (gap < den) && decide (gap ≤ den - gap)

@[inline] def quarterCheck (gap den : UInt64) : Bool :=
  halfCheck gap den && decide (gap + gap ≤ den - (gap + gap))

theorem halfCheck_bound (gap den : UInt64) (h : halfCheck gap den = true) :
    2 * gap.toNat ≤ den.toNat := by
  have hh : gap < den ∧ gap ≤ den - gap := by
    simpa only [halfCheck, Bool.and_eq_true, decide_eq_true_eq] using h
  have hlt := UInt64.lt_iff_toNat_lt.mp hh.1
  have hle := UInt64.le_iff_toNat_le.mp hh.2
  rw [UInt64.toNat_sub_of_le den gap (UInt64.le_iff_toNat_le.mpr hlt.le)] at hle
  omega

theorem quarterCheck_bound (gap den : UInt64) (h : quarterCheck gap den = true) :
    4 * gap.toNat ≤ den.toNat := by
  have hh : halfCheck gap den = true ∧ gap + gap ≤ den - (gap + gap) := by
    simpa only [quarterCheck, Bool.and_eq_true, decide_eq_true_eq] using h
  have hhalf := halfCheck_bound gap den hh.1
  have hadd : (gap + gap).toNat = 2 * gap.toNat := by
    have hsize := den.toNat_lt_size
    change den.toNat < 18446744073709551616 at hsize
    rw [UInt64.toNat_add]
    change (gap.toNat + gap.toNat) % 18446744073709551616 = 2 * gap.toNat
    rw [Nat.mod_eq_of_lt (by omega)]
    omega
  have hordered : gap + gap ≤ den :=
    UInt64.le_iff_toNat_le.mpr (by rw [hadd]; exact hhalf)
  have hle := UInt64.le_iff_toNat_le.mp hh.2
  rw [UInt64.toNat_sub_of_le den (gap + gap) hordered, hadd] at hle
  omega

/-- The guessed exponent field is raw-word data. Only accepted results are used. -/
@[inline] def check (num : UInt128) (den : UInt64) (field : UInt32) : Bool :=
  let residue := R24WordGap128.gap num den 8388608
  decide ((1 : UInt32) ≤ field) &&
    (decide (field ≤ (254 : UInt32)) &&
      (decide ((0 : UInt64) < den) &&
        ((residue.hi == 0) &&
          (if UInt128.less num (mul64 8388608 den) then
            if field == 1 then halfCheck residue.lo den else quarterCheck residue.lo den
          else halfCheck residue.lo den))))

theorem check_powerCell (num : UInt128) (den : UInt64) (field : UInt32)
    (h : check num den field = true) :
    R24PowerCell.powerCell num.toNat den.toNat ((field.toNat : Int) - 150) = true := by
  let residue := R24WordGap128.gap num den 8388608
  have hh : (1 : UInt32) ≤ field ∧ (field ≤ (254 : UInt32) ∧
      ((0 : UInt64) < den ∧ (residue.hi = 0 ∧
        (if UInt128.less num (mul64 8388608 den) then
          if field == 1 then halfCheck residue.lo den else quarterCheck residue.lo den
        else halfCheck residue.lo den) = true))) := by
    simpa only [check, Bool.and_eq_true, decide_eq_true_eq, beq_iff_eq] using h
  have hf0 : 1 ≤ field.toNat := UInt32.le_iff_toNat_le.mp hh.1
  have hf1 : field.toNat ≤ 254 := UInt32.le_iff_toNat_le.mp hh.2.1
  have hd : 0 < den.toNat := by
    simpa only [UInt64.toNat_zero] using UInt64.lt_iff_toNat_lt.mp hh.2.2.1
  have hresidue : residue.toNat = residue.lo.toNat := by
    simp only [UInt128.toNat, hh.2.2.2.1, UInt64.toNat_zero, zero_mul, add_zero]
  have hgap := R24WordGap128.gap_toNat_cases num den 8388608
  change (num.toNat < 8388608 * den.toNat ∧
      residue.toNat = 8388608 * den.toNat - num.toNat) ∨
    (8388608 * den.toNat ≤ num.toNat ∧
      residue.toNat = num.toNat - 8388608 * den.toNat) at hgap
  rw [hresidue] at hgap
  have hbounds :
      (if field.toNat = 1 then den.toNat * 16777215 ≤ 2 * num.toNat
        else den.toNat * 33554431 ≤ 4 * num.toNat) ∧
      2 * num.toNat ≤ den.toNat * 16777217 := by
    by_cases hbelow : UInt128.less num (mul64 8388608 den) = true
    · have hlt : num.toNat < 8388608 * den.toNat := by
        simpa only [mul64_toNat] using UInt128.less_eq_true_iff.mp hbelow
      have hres : residue.lo.toNat = 8388608 * den.toNat - num.toNat := by
        rcases hgap with hg | hg
        · exact hg.2
        · omega
      have hsum := Nat.sub_add_cancel hlt.le
      have hc := hh.2.2.2.2
      simp only [hbelow, if_true] at hc
      by_cases hmin : field = 1
      · have hc' : halfCheck residue.lo den = true := by simpa only [hmin, beq_self_eq_true, if_true] using hc
        have hhalf := halfCheck_bound residue.lo den hc'
        have hfmin : field.toNat = 1 := by rw [hmin]; rfl
        simp only [hfmin, if_true]
        constructor <;> nlinarith
      · have hc' : quarterCheck residue.lo den = true := by
          simpa only [beq_iff_eq, hmin, if_false] using hc
        have hquarter := quarterCheck_bound residue.lo den hc'
        have hfmin : field.toNat ≠ 1 := by
          intro he
          apply hmin
          apply UInt32.toNat_inj.mp
          exact he
        simp only [hfmin, if_false]
        constructor <;> nlinarith
    · have hle : 8388608 * den.toNat ≤ num.toNat := by
        by_contra hn
        have hlt : num.toNat < (mul64 8388608 den).toNat := by
          simp only [mul64_toNat]
          omega
        exact hbelow (UInt128.less_eq_true_iff.mpr hlt)
      have hres : residue.lo.toNat = num.toNat - 8388608 * den.toNat := by
        rcases hgap with hg | hg
        · omega
        · exact hg.2
      have hsum := Nat.sub_add_cancel hle
      have hc : halfCheck residue.lo den = true := by
        simpa only [hbelow, if_false] using hh.2.2.2.2
      have hhalf := halfCheck_bound residue.lo den hc
      by_cases hmin : field.toNat = 1
      · simp only [hmin, if_true]
        constructor <;> nlinarith
      · simp only [hmin, if_false]
        constructor <;> nlinarith
  unfold R24PowerCell.powerCell
  change decide (0 < den.toNat ∧ 1 ≤ (field.toNat : Int) - 150 + 150 ∧
    (field.toNat : Int) - 150 + 150 ≤ 254 ∧
    (if (field.toNat : Int) - 150 + 150 = 1 then den.toNat * 16777215 ≤ 2 * num.toNat
      else den.toNat * 33554431 ≤ 4 * num.toNat) ∧
    2 * num.toNat ≤ den.toNat * 16777217) = true
  have hfmin : ((field.toNat : Int) = 1) ↔ field.toNat = 1 := by omega
  apply decide_eq_true
  simpa only [sub_add_cancel, hfmin] using
    (show 0 < den.toNat ∧ 1 ≤ (field.toNat : Int) ∧ (field.toNat : Int) ≤ 254 ∧
      (if field.toNat = 1 then den.toNat * 16777215 ≤ 2 * num.toNat
        else den.toNat * 33554431 ≤ 4 * num.toNat) ∧
      2 * num.toNat ≤ den.toNat * 16777217 from
      ⟨hd, by omega, by omega, hbounds.1, hbounds.2⟩)

theorem check_sound (sign : Bool) (num : UInt128) (den : UInt64) (field : UInt32)
    (h : check num den field = true) :
    FloatLib.Floats.Formats.BinaryInterchange.Model.NativeBinary32.roundRatScaled
        sign num.toNat den.toNat ((field.toNat : Int) - 150) =
      FloatLib.Floats.Formats.BinaryInterchange.Model.NativeBinary32.mkBits sign field.toNat 0 := by
  have hp := R24PowerCell.powerCell_sound sign num.toNat den.toNat
    ((field.toNat : Int) - 150) (check_powerCell num den field h)
  simpa only [sub_add_cancel, Int.toNat_natCast] using hp

end Submission.R24PowerGap128
