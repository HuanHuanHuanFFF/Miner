namespace Submission.A16L

open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange

def magnitude (hiSign loSign : Bool) (hi lo gap : Nat) : Nat :=
  if hiSign = loSign then (hi <<< gap) + lo else (hi <<< gap) - lo

theorem shifted_ne_zero (m d : Nat) (hm : m ≠ 0) : m <<< d ≠ 0 := by
  have hp := (Nat.mul_pos (Nat.pos_of_ne_zero hm) (Nat.two_pow_pos d)).ne'
  simpa only [Nat.shiftLeft_eq', Nat.shiftLeft_eq] using hp

theorem large_left (hi lo gap : Nat)
    (hhi : 8388608 ≤ hi) (hlo : lo < 16777216) (hgap : 1 ≤ gap) :
    lo < hi <<< gap := by
  have hp : 2 ≤ 2 ^ gap := by
    have h : 2 ^ 1 ≤ 2 ^ gap := Nat.pow_le_pow_right (by decide) hgap
    norm_num at h
    exact h
  have hm := Nat.mul_le_mul_left hi hp
  simp only [Nat.shiftLeft_eq', Nat.shiftLeft_eq]
  omega

theorem align_high_low (hiSign loSign : Bool) (hi lo ehi elo : Nat)
    (hhi : hi ≠ 0) (hlo : lo ≠ 0) (he : elo ≤ ehi) :
    Model.addDyadic
      { negative := hiSign, significand := hi, exponent := (ehi : Int) - 150 }
      { negative := loSign, significand := lo, exponent := (elo : Int) - 150 } =
    Model.addDyadic
      { negative := hiSign, significand := hi <<< (ehi - elo),
        exponent := (elo : Int) - 150 }
      { negative := loSign, significand := lo, exponent := (elo : Int) - 150 } := by
  rcases Nat.eq_or_lt_of_le he with heq | hlt
  · subst ehi
    simp only [Nat.sub_self, Nat.shiftLeft_eq', Nat.shiftLeft_eq, Nat.pow_zero,
      Nat.mul_one]
  · exact
      Model.addDyadic_alignLeftOffset 150 hiSign loSign hi lo ehi elo hhi hlo hlt

theorem exact_high_low (hiSign loSign : Bool) (hi lo ehi elo : Nat)
    (hhi : 8388608 ≤ hi) (hlo : 0 < lo) (hloUpper : lo < 16777216)
    (he : elo ≤ ehi) (hdomain : hiSign = loSign ∨ 1 ≤ ehi - elo) :
    Model.addDyadic
      { negative := hiSign, significand := hi, exponent := (ehi : Int) - 150 }
      { negative := loSign, significand := lo, exponent := (elo : Int) - 150 } =
      { negative := hiSign, significand := magnitude hiSign loSign hi lo (ehi - elo),
        exponent := (elo : Int) - 150 } := by
  have hhi0 : hi ≠ 0 := by omega
  have hlo0 : lo ≠ 0 := by omega
  have hshift := shifted_ne_zero hi (ehi - elo) hhi0
  rw [align_high_low hiSign loSign hi lo ehi elo hhi0 hlo0 he]
  by_cases hs : hiSign = loSign
  · subst loSign
    simpa only [magnitude, ↓reduceIte] using
      Model.addDyadic_sameSign_sameExponent hiSign (hi <<< (ehi - elo)) lo
        ((elo : Int) - 150) hshift hlo0
  · have hd : 1 ≤ ehi - elo := hdomain.resolve_left hs
    simpa only [magnitude, if_neg hs, ↓reduceIte] using
      Model.addDyadic_oppositeSign_sameExponent_largeLeft hiSign loSign
        (hi <<< (ehi - elo)) lo ((elo : Int) - 150) hshift hlo0 hs
        (large_left hi lo (ehi - elo) hhi hloUpper hd)

theorem exact_low_high (hiSign loSign : Bool) (hi lo ehi elo : Nat)
    (hhi : 8388608 ≤ hi) (hlo : 0 < lo) (hloUpper : lo < 16777216)
    (he : elo ≤ ehi) (hdomain : hiSign = loSign ∨ 1 ≤ ehi - elo) :
    Model.addDyadic
      { negative := loSign, significand := lo, exponent := (elo : Int) - 150 }
      { negative := hiSign, significand := hi, exponent := (ehi : Int) - 150 } =
      { negative := hiSign, significand := magnitude hiSign loSign hi lo (ehi - elo),
        exponent := (elo : Int) - 150 } := by
  rw [Model.addDyadic_comm]
  exact exact_high_low hiSign loSign hi lo ehi elo hhi hlo hloUpper he hdomain

theorem spec_add_of_decodes {fmt : FloatFormat} (x y : Model fmt)
    (dx dy : FloatLib.Numerics.Dyadic)
    (hx : Model.toDyadic? x = some dx) (hy : Model.toDyadic? y = some dy) :
    Model.Spec.add x y = Model.roundDyadic fmt (Model.addDyadic dx dy) := by
  unfold Model.Spec.add
  rw [hx, hy]

end Submission.A16L
namespace Submission.A16L
theorem magnitude_bounds (sh sl : Bool) (hi lo d : Nat)
    (hhi : 8388608 ≤ hi) (hhi' : hi < 16777216)
    (hlo : 8388608 ≤ lo) (hlo' : lo < 16777216)
    (hd : d ≤ 7) (hdom : sh = sl ∨ 1 ≤ d) :
    1 ≤ magnitude sh sl hi lo d ∧ magnitude sh sl hi lo d ≤ 2164260735 := by
  by_cases hs : sh = sl
  · interval_cases d <;> simp only [magnitude, if_pos hs, Nat.shiftLeft_eq', Nat.shiftLeft_eq] <;> norm_num <;> omega
  · have hg : 1 ≤ d := hdom.resolve_left hs
    interval_cases d <;> simp only [magnitude, if_neg hs, Nat.shiftLeft_eq', Nat.shiftLeft_eq] <;> norm_num <;> omega
end Submission.A16L
