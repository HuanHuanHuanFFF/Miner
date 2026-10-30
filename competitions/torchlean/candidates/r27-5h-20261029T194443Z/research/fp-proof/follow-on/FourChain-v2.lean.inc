/- Four native Float64 fold results can be merged under the existing radius.
   Array-lane partition, runtime selection, and full kernels remain separate. -/
namespace Submission.R27FourChain
open FloatLib.Floats FloatLib.Floats.Formats.BinaryInterchange
open Submission.R24RepresentationSum

private theorem p2_one : p2 1 = (2 : Real) := by simpa using p2_nat 1
private theorem p2_two : p2 2 = (4 : Real) := by simpa using p2_nat 2
private theorem p2_four : p2 4 = (16 : Real) := by simpa using p2_nat 4

/-- A native merge preserves the exact count-grid magnitude bound. -/
theorem merge_grid (a b : Float) (i j L : Nat) (k : Int)
    (hklo : -250 ≤ k) (hkhi : k ≤ 256) (hL : L ≤ 30)
    (hc : i + j ≤ 2 ^ L)
    (ha : a.isFinite = true) (hb : b.isFinite = true)
    (hma : |rval a| ≤ (i : Real) * p2 k)
    (hmb : |rval b| ≤ (j : Real) * p2 k) :
    (a + b).isFinite = true ∧
      |rval (a + b)| ≤ ((i + j : Nat) : Real) * p2 k ∧
      |rval (a + b) - (rval a + rval b)| ≤ p2 (k + (L : Int) - 52) := by
  have hpre : |rval a| + |rval b| ≤ ((i + j : Nat) : Real) * p2 k := by
    convert add_le_add hma hmb using 1 <;> push_cast <;> ring
  have hglobal := scaled_count_le (i + j) L k hc
  have htop : p2 (k + (L : Int)) ≤ p2 286 := p2_mono (by omega)
  have step := native_add_finite_real a b ha hb (hpre.trans (hglobal.trans htop))
  have hinput : |rval a + rval b| ≤ ((i + j : Nat) : Real) * p2 k :=
    (abs_add_le _ _).trans hpre
  have hc30 : i + j ≤ 2 ^ 30 := hc.trans (Nat.pow_le_pow_right (by decide) hL)
  have grid := round_grid (i + j) k hc30 hklo
  have hmag : |rval (a + b)| ≤ ((i + j : Nat) : Real) * p2 k := by
    rw [step.2]
    obtain ⟨hl, hu⟩ := abs_le.mp hinput
    have lo := Model.roundAt_mono FloatFormat.binary64 hl
    have hi := Model.roundAt_mono FloatFormat.binary64 hu
    rw [Model.roundAt_neg, grid] at lo
    rw [grid] at hi
    exact abs_le.mpr ⟨lo, hi⟩
  have hpower : p2 (k + (L : Int)) < p2 (k + (L : Int) + 1) := by
    rw [p2_add (k + (L : Int)) 1, p2_one]
    have hp := p2_pos (k + (L : Int))
    nlinarith
  have herr := round_error_power (rval a + rval b) (k + (L : Int) + 1)
    (by omega) ((hinput.trans hglobal).trans_lt hpower)
  have hshift : k + (L : Int) + 1 - 53 = k + (L : Int) - 52 := by omega
  refine ⟨step.1, hmag, ?_⟩
  rw [step.2, ← hshift]
  exact herr

private theorem merge_error (a b : Float) (A B E ea eb : Real)
    (h : |rval (a + b) - (rval a + rval b)| ≤ E)
    (ha : |rval a - A| ≤ ea) (hb : |rval b - B| ≤ eb) :
    |rval (a + b) - (A + B)| ≤ E + ea + eb := by
  have heq : rval (a + b) - (A + B) =
      (rval (a + b) - (rval a + rval b)) + ((rval a - A) + (rval b - B)) := by ring
  rw [heq]
  calc
    _ ≤ |rval (a + b) - (rval a + rval b)| + |(rval a - A) + (rval b - B)| := abs_add_le _ _
    _ ≤ E + (ea + eb) := add_le_add h ((abs_add_le _ _).trans (add_le_add ha hb))
    _ = E + ea + eb := by ring

private theorem sum_info (xs : List Float) (L : Nat) (k : Int)
    (hklo : -250 ≤ k) (hkhi : k ≤ 256) (hL : L ≤ 30)
    (hc : xs.length ≤ 2 ^ L)
    (hx : ∀ x ∈ xs, x.isFinite = true ∧ |rval x| < p2 k) :
    (sum xs).isFinite = true ∧ |rval (sum xs)| ≤ (xs.length : Real) * p2 k ∧
      |rval (sum xs) - exactSum xs| ≤ p2 (k + 2 * (L : Int) - 53) := by
  have he := sum_enclosure xs L k hklo hkhi hL hc hx
  have hm := loop_invariant xs (Float.ofBits 0) 0 L k hklo hkhi hL
    (by simpa using hc) zero_finite (by simp [zero_value]) hx
  exact ⟨he.1, by simpa only [sum, Nat.zero_add] using hm.2.1, he.2⟩

/-- Four already partitioned actual native folds need no larger radius than
    the old sequential producer when L>=3. The final target is the exact sum
    of all four lane targets; no native associativity assumption is used. -/
theorem four_sums_enclosure (x0 x1 x2 x3 : List Float) (L : Nat) (k : Int)
    (hklo : -250 ≤ k) (hkhi : k ≤ 256) (hLlo : 3 ≤ L) (hLhi : L ≤ 30)
    (hc0 : x0.length ≤ 2 ^ (L - 2)) (hc1 : x1.length ≤ 2 ^ (L - 2))
    (hc2 : x2.length ≤ 2 ^ (L - 2)) (hc3 : x3.length ≤ 2 ^ (L - 2))
    (hx0 : ∀ x ∈ x0, x.isFinite = true ∧ |rval x| < p2 k)
    (hx1 : ∀ x ∈ x1, x.isFinite = true ∧ |rval x| < p2 k)
    (hx2 : ∀ x ∈ x2, x.isFinite = true ∧ |rval x| < p2 k)
    (hx3 : ∀ x ∈ x3, x.isFinite = true ∧ |rval x| < p2 k) :
    ((sum x0 + sum x1) + (sum x2 + sum x3)).isFinite = true ∧
      |rval ((sum x0 + sum x1) + (sum x2 + sum x3)) -
        ((exactSum x0 + exactSum x1) + (exactSum x2 + exactSum x3))| ≤
          p2 (k + 2 * (L : Int) - 53) := by
  have hLs : L - 2 ≤ 30 := by omega
  have s0 := sum_info x0 (L - 2) k hklo hkhi hLs hc0 hx0
  have s1 := sum_info x1 (L - 2) k hklo hkhi hLs hc1 hx1
  have s2 := sum_info x2 (L - 2) k hklo hkhi hLs hc2 hx2
  have s3 := sum_info x3 (L - 2) k hklo hkhi hLs hc3 hx3
  have hp : 4 * 2 ^ (L - 2) = 2 ^ L := by
    have hsplit : L = (L - 2) + 2 := by omega
    conv_rhs => rw [hsplit, Nat.pow_add]
    norm_num <;> ring
  have hcount : (x0.length + x1.length) + (x2.length + x3.length) ≤ 2 ^ L := by omega
  have p01 := merge_grid (sum x0) (sum x1) x0.length x1.length L k
    hklo hkhi hLhi (by omega) s0.1 s1.1 s0.2.1 s1.2.1
  have p23 := merge_grid (sum x2) (sum x3) x2.length x3.length L k
    hklo hkhi hLhi (by omega) s2.1 s3.1 s2.2.1 s3.2.1
  have pAll := merge_grid (sum x0 + sum x1) (sum x2 + sum x3)
    (x0.length + x1.length) (x2.length + x3.length) L k hklo hkhi hLhi
    hcount p01.1 p23.1 p01.2.1 p23.2.1
  let G := p2 (k + 2 * ((L - 2 : Nat) : Int) - 53)
  let J := p2 (k + (L : Int) - 52)
  have e01 := merge_error (sum x0) (sum x1) (exactSum x0) (exactSum x1)
    J G G p01.2.2 s0.2.2 s1.2.2
  have e23 := merge_error (sum x2) (sum x3) (exactSum x2) (exactSum x3)
    J G G p23.2.2 s2.2.2 s3.2.2
  have eAll := merge_error (sum x0 + sum x1) (sum x2 + sum x3)
    (exactSum x0 + exactSum x1) (exactSum x2 + exactSum x3)
    J (J + G + G) (J + G + G) pAll.2.2 e01 e23
  have hJ : J ≤ 4 * G := by
    calc
      J ≤ p2 ((k + 2 * ((L - 2 : Nat) : Int) - 53) + 2) := p2_mono (by omega)
      _ = 4 * G := by rw [p2_add, p2_two]; dsimp [G]; ring
  have hR : p2 (k + 2 * (L : Int) - 53) = 16 * G := by
    rw [show k + 2 * (L : Int) - 53 =
      (k + 2 * ((L - 2 : Nat) : Int) - 53) + 4 by omega, p2_add, p2_four]
    dsimp [G]
    ring
  refine ⟨pAll.1, eAll.trans ?_⟩
  rw [hR]
  linarith

end Submission.R27FourChain
