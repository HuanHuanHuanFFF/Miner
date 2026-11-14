namespace Submission.R24DotEnclosure
open FloatLib.Floats FloatLib.Floats.Formats.BinaryInterchange FloatLib.Floats.Formats.Flocq
open Submission.R24RepresentationSum
open Submission.R24RepresentationWiden (Domain value native_value native_finite)
open R2W01c (wordExp wordFrac wordSign wordFrac_lt raw32_eq_fields fields32_toDyadic)

noncomputable abbrev rawReal (u : UInt32) : ℝ := Model.toReal (raw32 u)
def PairGuard (H : Nat) (p : UInt32 × UInt32) : Prop :=
  Domain p.1 ∧ Domain p.2 ∧ (wordExp p.1 - 1) + (wordExp p.2 - 1) ≤ H
def product (p : UInt32 × UInt32) : Float := value p.1 * value p.2
def dot (ps : List (UInt32 × UInt32)) : Float := sum (ps.map product)
noncomputable def exactDot (ps : List (UInt32 × UInt32)) : ℝ :=
  (ps.map (fun p => rawReal p.1 * rawReal p.2)).sum

theorem raw_finite (u : UInt32) (h : Domain u) : Model.isFinite (raw32 u) = true := by
  rcases h with hn | hz
  · apply Model.isFinite_eq_true_of_toDyadic?_some
    rw [raw32_eq_fields]
    exact fields32_toDyadic _ _ _ hn.1 hn.2 (wordFrac_lt u)
  · rcases Submission.R24RepresentationWiden.zero_word_cases u hz.1 hz.2 with rfl | rfl <;> decide

theorem raw_abs_bound (u : UInt32) (h : Domain u) :
    |rawReal u| < p2 ((wordExp u : Int) - 126) := by
  rcases h with hn | hz
  · rw [raw32_eq_fields, Model.toReal_ofFields_normal F32 (wordSign u)
      (wordExp u) (wordFrac u) (by omega) hn.2 (wordFrac_lt u)]
    change |(if wordSign u then (-1 : ℝ) else 1) *
      ((8388608 + wordFrac u : Nat) : ℝ) * p2 ((wordExp u : Int) - 127 - 23)| < _
    have hs : |(if wordSign u then (-1 : ℝ) else 1)| = 1 := by cases wordSign u <;> norm_num
    rw [abs_mul, abs_mul, hs, one_mul,
      abs_of_nonneg (Nat.cast_nonneg _), abs_of_pos (p2_pos _)]
    have hm : ((8388608 + wordFrac u : Nat) : ℝ) < ((2 ^ 24 : Nat) : ℝ) := by
      exact_mod_cast (show 8388608 + wordFrac u < 2 ^ 24 by have := wordFrac_lt u; omega)
    calc
      _ < ((2 ^ 24 : Nat) : ℝ) * p2 ((wordExp u : Int) - 127 - 23) :=
        mul_lt_mul_of_pos_right hm (p2_pos _)
      _ = p2 ((wordExp u : Int) - 126) := by
        rw [← p2_nat, ← p2_add]
        congr 1
        omega
  · rcases Submission.R24RepresentationWiden.zero_word_cases u hz.1 hz.2 with rfl | rfl
    · change |Model.toReal (Model.zero F32 false)| < p2 (-126)
      simpa using p2_pos (-126)
    · change |Model.toReal (Model.zero F32 true)| < p2 (-126)
      simpa using p2_pos (-126)

theorem raw_product_bound (H : Nat) (p : UInt32 × UInt32) (h : PairGuard H p) :
    |rawReal p.1 * rawReal p.2| < p2 ((H : Int) - 250) := by
  have ha := raw_abs_bound p.1 h.1
  have hb := raw_abs_bound p.2 h.2.1
  rw [abs_mul]
  calc
    _ ≤ |rawReal p.1| * p2 ((wordExp p.2 : Int) - 126) :=
      mul_le_mul_of_nonneg_left hb.le (abs_nonneg _)
    _ < p2 ((wordExp p.1 : Int) - 126) * p2 ((wordExp p.2 : Int) - 126) :=
      mul_lt_mul_of_pos_right ha (p2_pos _)
    _ = p2 (((wordExp p.1 : Int) - 126) + ((wordExp p.2 : Int) - 126)) :=
      (p2_add _ _).symm
    _ ≤ p2 ((H : Int) - 250) := p2_mono (by have := h.2.2; omega)

theorem product_exact (H : Nat) (p : UInt32 × UInt32)
    (hH : H ≤ 506) (h : PairGuard H p) :
    (product p).isFinite = true ∧ rval (product p) = rawReal p.1 * rawReal p.2 ∧
      |rval (product p)| < p2 ((H : Int) - 250) := by
  have ha := native_finite p.1 h.1
  have hb := native_finite p.2 h.2.1
  have va : rval (value p.1) = rawReal p.1 := native_value p.1 h.1
  have vb : rval (value p.2) = rawReal p.2 := native_value p.2 h.2.1
  have hm : native (product p) = Model.mul (native (value p.1)) (native (value p.2)) := by
    exact native_mul _ _ ha hb
  have hma : Model.isFinite (native (value p.1)) = true := by rw [native_finite_eq, ha]
  have hmb : Model.isFinite (native (value p.2)) = true := by rw [native_finite_eq, hb]
  have bound : |rval (value p.1)| * |rval (value p.2)| ≤ Model.toReal (Model.posMaxFinite F64) := by
    rw [va, vb, ← abs_mul]
    exact (raw_product_bound H p h).le.trans ((p2_mono (by omega)).trans max_finite_large)
  have hf := Model.isFinite_mul_of_abs_mul_le_posMaxFinite
    (native (value p.1)) (native (value p.2)) (by decide) hma hmb bound
  have hv : rval (product p) = rawReal p.1 * rawReal p.2 := by
    change Model.toReal (native (product p)) = _
    rw [hm, Model.toReal_mul_eq_roundAt _ _ (by decide) hma hmb hf]
    change Model.roundAt F64 (rval (value p.1) * rval (value p.2)) = _
    rw [va, vb]
    exact round_preserves_generic nearestEven _
      (f32_product_grid (raw32 p.1) (raw32 p.2) (raw_finite _ h.1) (raw_finite _ h.2.1))
  refine ⟨?_, hv, ?_⟩
  · rw [← native_finite_eq, hm]
    exact hf
  · rw [hv]
    exact raw_product_bound H p h

theorem actual_dot_enclosure (ps : List (UInt32 × UInt32)) (H L : Nat)
    (hH : H ≤ 506) (hL : L ≤ 30) (hn : ps.length ≤ 2 ^ L)
    (hp : ∀ p ∈ ps, PairGuard H p) :
    (dot ps).isFinite = true ∧
      |rval (dot ps) - exactDot ps| ≤ p2 ((H : Int) + 2 * (L : Int) - 303) := by
  have hx : ∀ x ∈ ps.map product, x.isFinite = true ∧ |rval x| < p2 ((H : Int) - 250) := by
    intro x hx
    obtain ⟨p, hmem, rfl⟩ := List.mem_map.mp hx
    have hh := product_exact H p hH (hp p hmem)
    exact ⟨hh.1, hh.2.2⟩
  have he : exactSum (ps.map product) = exactDot ps := by
    unfold exactSum exactDot
    rw [List.map_map]
    congr 1
    apply List.map_congr_left
    intro p hmem
    exact (product_exact H p hH (hp p hmem)).2.1
  have hh := sum_enclosure (ps.map product) L ((H : Int) - 250)
    (by omega) (by omega) hL (by simpa using hn) hx
  rw [he] at hh
  have hexp : (H : Int) - 250 + 2 * (L : Int) - 53 = (H : Int) + 2 * (L : Int) - 303 := by omega
  simpa only [dot, hexp] using hh
end Submission.R24DotEnclosure
