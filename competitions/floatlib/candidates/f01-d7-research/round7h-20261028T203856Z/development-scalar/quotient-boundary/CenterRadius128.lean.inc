/- Exact word interval and sign construction, independent of a native hint.
   The approximate center/error-bound link is an explicit caller obligation.
   Old ContractTensor helper; new typing/replay/AX/native cost NOT_RUN. -/
namespace Submission.R24CenterRadius128
open FloatLib.Numerics.FixedWord
open FloatLib.Floats FloatLib.Floats.Formats.BinaryInterchange

structure Result where
  lo : UInt128
  hi : UInt128
  valid : Bool

/-- Strict separation from zero and carry checking precede accepted use. -/
@[inline] def make (center radius : UInt128) : Result :=
  let upper := add128 center radius
  ⟨UInt128.sub center radius, upper.value,
    UInt128.less radius center && (upper.carry == 0)⟩

theorem make_bounds (center radius : UInt128) (h : (make center radius).valid = true) :
    (make center radius).lo.toNat + radius.toNat = center.toNat ∧
      (make center radius).hi.toNat = center.toNat + radius.toNat ∧
      radius.toNat < center.toNat := by
  have hh : UInt128.less radius center = true ∧ (add128 center radius).carry = 0 := by
    simpa only [make, Bool.and_eq_true, beq_iff_eq] using h
  have hlt := UInt128.less_eq_true_iff.mp hh.1
  have hsub := UInt128.sub_toNat center radius hlt.le
  have hadd := add128_value_toNat_of_carry_zero center radius hh.2
  refine ⟨?_, ?_, hlt⟩
  · change (UInt128.sub center radius).toNat + radius.toNat = center.toNat
    rw [hsub]
    exact Nat.sub_add_cancel hlt.le
  · exact hadd

theorem make_encloses (sign : Bool) (center radius : UInt128) (scale : Int) (value : Real)
    (h : (make center radius).valid = true)
    (herror : |(if sign then -((center.toNat : Real) * Model.bpow scale)
      else (center.toNat : Real) * Model.bpow scale) - value| ≤
        (radius.toNat : Real) * Model.bpow scale) :
    decide (value < 0) = sign ∧
      ((make center radius).lo.toNat : Real) * Model.bpow scale ≤ |value| ∧
      |value| ≤ ((make center radius).hi.toNat : Real) * Model.bpow scale := by
  obtain ⟨hl, hu, hsep⟩ := make_bounds center radius h
  have hlR : ((make center radius).lo.toNat : Real) + (radius.toNat : Real) = center.toNat := by
    exact_mod_cast hl
  have huR : ((make center radius).hi.toNat : Real) = (center.toNat : Real) + radius.toNat := by
    exact_mod_cast hu
  have hpos : 0 < (make center radius).lo.toNat := by omega
  have hloPos : (0 : Real) < ((make center radius).lo.toNat : Real) * Model.bpow scale :=
    mul_pos (by exact_mod_cast hpos) (Model.bpow_pos scale)
  have hlo : ((make center radius).lo.toNat : Real) * Model.bpow scale +
      (radius.toNat : Real) * Model.bpow scale = (center.toNat : Real) * Model.bpow scale := by
    rw [← add_mul, hlR]
  have hhi : ((make center radius).hi.toNat : Real) * Model.bpow scale =
      (center.toNat : Real) * Model.bpow scale + (radius.toNat : Real) * Model.bpow scale := by
    rw [huR, add_mul]
  cases sign with
  | false =>
      change |(center.toNat : Real) * Model.bpow scale - value| ≤
        (radius.toNat : Real) * Model.bpow scale at herror
      obtain ⟨hel, heu⟩ := abs_le.mp herror
      have hv : 0 < value := by linarith
      have hn : ¬ value < 0 := by linarith
      refine ⟨by simp only [hn, decide_false], ?_, ?_⟩ <;>
        rw [abs_of_pos hv] <;> linarith
  | true =>
      change |-((center.toNat : Real) * Model.bpow scale) - value| ≤
        (radius.toNat : Real) * Model.bpow scale at herror
      obtain ⟨hel, heu⟩ := abs_le.mp herror
      have hv : value < 0 := by linarith
      refine ⟨by simp only [hv, decide_true], ?_, ?_⟩ <;>
        rw [abs_of_neg hv] <;> linarith

theorem make_word_sound (sign : Bool) (center radius : UInt128) (scale : Int)
    (mant : UInt64) (field : UInt32) (value : Real) (num den : Nat) (source : Int)
    (hd : 0 < den) (hvalue : |value| = Model.scaledRatToReal num den source)
    (herror : |(if sign then -((center.toNat : Real) * Model.bpow scale)
      else (center.toNat : Real) * Model.bpow scale) - value| ≤
        (radius.toNat : Real) * Model.bpow scale)
    (h : (make center radius).valid = true)
    (hcheck : R24DyadicInterval128.check (make center radius).lo (make center radius).hi scale mant field = true) :
    Model.NativeBinary32.roundRatScaled (decide (value < 0)) num den source =
      Model.NativeBinary32.mkBits sign field.toNat (mant.toNat - 8388608) := by
  obtain ⟨hsign, hl, hu⟩ := make_encloses sign center radius scale value h herror
  rw [hsign]
  apply R24DyadicInterval128.check_sound sign (make center radius).lo (make center radius).hi
    scale mant field num den source hd
  · simpa only [← hvalue] using hl
  · simpa only [← hvalue] using hu
  · exact hcheck

end Submission.R24CenterRadius128
