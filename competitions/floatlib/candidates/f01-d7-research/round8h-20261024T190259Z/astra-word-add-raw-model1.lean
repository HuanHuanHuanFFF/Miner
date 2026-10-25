/- Draft / NOT_RUN. Requested final finite-decoding bridge.
   Requires runtime3, development word-bridges, alignment2, bounds1, and
   model-bridge1. D must define R14WordAdd.magnitudeNat with the agreed exact
   interface BEFORE this component. No D source or runtime is changed here.
   Original u/v order is preserved; only decoded dyadic addition is reordered. -/
namespace Submission.R14WordAdd

open FloatLib.Floats Competition
open FloatLib.Floats.Formats.BinaryInterchange

theorem raw_add_sorted_conditions (u v : UInt32) (hd : eligible u v = true) :
    (0 < R2W01c.wordExp (high u v) ∧ R2W01c.wordExp (high u v) < 255) ∧
    (0 < R2W01c.wordExp (low u v) ∧ R2W01c.wordExp (low u v) < 255) ∧
    (gap u v).toNat ≤ 7 ∧
    (R2W01c.wordSign (high u v) = R2W01c.wordSign (low u v) ∨
      2 ≤ (gap u v).toNat) := by
  have hc := eligible_conditions u v hd
  by_cases hs : R14ExponentShift.ex u < R14ExponentShift.ex v
  · simp only [high, low, if_pos hs]
    refine ⟨hc.2.1, hc.1, hc.2.2.1, ?_⟩
    rcases hc.2.2.2 with heq | hg
    · exact Or.inl heq.symm
    · exact Or.inr hg
  · simpa only [high, low, if_neg hs] using hc

theorem raw_add_gap_nat (u v : UInt32) :
    (gap u v).toNat = R2W01c.wordExp (high u v) - R2W01c.wordExp (low u v) := by
  have hs := sorted_exponents u v
  rw [gap_nat u v, hs.1, hs.2]

theorem raw_add_model (u v : UInt32) (hd : eligible u v = true)
    (he : (magnitudeNat u v).log2 + R2W01c.wordExp (low u v) - 23 +
      R14NatNormal.carry (magnitudeNat u v) ≤ 254) :
    Model.add (R2W01c.rawModel u) (R2W01c.rawModel v) =
      Model.ofFields FloatFormat.binary32 (R2W01c.wordSign (high u v))
        ((magnitudeNat u v).log2 + R2W01c.wordExp (low u v) - 23 +
          R14NatNormal.carry (magnitudeNat u v))
        (R14NatNormal.mantissa (magnitudeNat u v) - 8388608) := by
  have hc := eligible_conditions u v hd
  have hs := raw_add_sorted_conditions u v hd
  have hsort := sorted_exponents u v
  have horder : R2W01c.wordExp (low u v) ≤ R2W01c.wordExp (high u v) := by
    rw [hsort.1, hsort.2]
    exact Nat.le_trans (Nat.min_le_left _ _) (Nat.le_max_left _ _)
  have hgap := raw_add_gap_nat u v
  have hdomain : R2W01c.wordSign (high u v) = R2W01c.wordSign (low u v) ∨
      2 ≤ R2W01c.wordExp (high u v) - R2W01c.wordExp (low u v) := by
    rw [← hgap]
    exact hs.2.2.2
  have hhi := R2W01c.mantissa_bounds (high u v)
  have hlo := R2W01c.mantissa_bounds (low u v)
  have hmag : R14WordAddAlignment.magnitude
      (R2W01c.wordSign (high u v)) (R2W01c.wordSign (low u v))
      (R2W01b.mantissa (high u v)).toNat (R2W01b.mantissa (low u v)).toNat
      (R2W01c.wordExp (high u v) - R2W01c.wordExp (low u v)) = magnitudeNat u v := by
    unfold magnitudeNat
    rw [hgap]
  have hsum : Model.addDyadic
      { negative := R2W01c.wordSign u, significand := (R2W01b.mantissa u).toNat,
        exponent := (R2W01c.wordExp u : Int) - 150 }
      { negative := R2W01c.wordSign v, significand := (R2W01b.mantissa v).toNat,
        exponent := (R2W01c.wordExp v : Int) - 150 } =
      { negative := R2W01c.wordSign (high u v), significand := magnitudeNat u v,
        exponent := (R2W01c.wordExp (low u v) : Int) - 150 } := by
    by_cases ho : R14ExponentShift.ex u < R14ExponentShift.ex v
    · have hx := R14WordAddAlignment.exact_low_high
        (R2W01c.wordSign (high u v)) (R2W01c.wordSign (low u v))
        (R2W01b.mantissa (high u v)).toNat (R2W01b.mantissa (low u v)).toNat
        (R2W01c.wordExp (high u v)) (R2W01c.wordExp (low u v))
        hhi.1 (by omega) hlo.2 horder hdomain
      rw [hmag] at hx
      simpa only [high, low, if_pos ho] using hx
    · have hx := R14WordAddAlignment.exact_high_low
        (R2W01c.wordSign (high u v)) (R2W01c.wordSign (low u v))
        (R2W01b.mantissa (high u v)).toNat (R2W01b.mantissa (low u v)).toNat
        (R2W01c.wordExp (high u v)) (R2W01c.wordExp (low u v))
        hhi.1 (by omega) hlo.2 horder hdomain
      rw [hmag] at hx
      simpa only [high, low, if_neg ho] using hx
  have hb := R14WordAddAlignment.magnitude_bounds
    (R2W01c.wordSign (high u v)) (R2W01c.wordSign (low u v))
    (R2W01b.mantissa (high u v)).toNat (R2W01b.mantissa (low u v)).toNat
    (gap u v).toNat hhi.1 hhi.2 hlo.1 hlo.2 hs.2.2.1 hs.2.2.2
  have hn : magnitudeNat u v ≠ 0 := by
    have hmin : 16777216 ≤ magnitudeNat u v := by
      simpa only [magnitudeNat] using hb.1
    omega
  have hh : 24 ≤ (magnitudeNat u v).log2 := by
    have hl := R14WordAddAlignment.log2_bounds
      (R2W01c.wordSign (high u v)) (R2W01c.wordSign (low u v))
      (R2W01b.mantissa (high u v)).toNat (R2W01b.mantissa (low u v)).toNat
      (gap u v).toNat hhi.1 hhi.2 hlo.1 hlo.2 hs.2.2.1 hs.2.2.2
    simpa only [magnitudeNat] using hl.1
  exact R14WordAddAlignment.model_add_normal (R2W01c.rawModel u) (R2W01c.rawModel v)
    ⟨R2W01c.wordSign u, (R2W01b.mantissa u).toNat, (R2W01c.wordExp u : Int) - 150⟩
    ⟨R2W01c.wordSign v, (R2W01b.mantissa v).toNat, (R2W01c.wordExp v : Int) - 150⟩
    (R2W01c.wordSign (high u v)) (magnitudeNat u v) (R2W01c.wordExp (low u v))
    (R14NatNormal.raw_normal_decode u hc.1.1 hc.1.2)
    (R14NatNormal.raw_normal_decode v hc.2.1.1 hc.2.1.2)
    hsum hn hh (by have hl := hs.2.1.1; omega) he

end Submission.R14WordAdd
