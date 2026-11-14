import ContractExact

/-!
R28 original mathematical fragments. NOT_COMPILED.

This file does not replace a kernel, import an upstream Submission, change a
contract, or assert the final word-level rounding bridge. It contains intended proof scripts for the small
arithmetic core needed by a strict, division-free rounding-cell verifier.
All declarations below are original, with explicit proof bodies.
-/

namespace R28Cell

/-- Keep the bias inside the same exact quotient; do not round the centred
product before adding it. `k` and `b` are the two nonnegative power-of-two
alignment factors in the intended application. -/
theorem affine_identity (n d X S G B k b : ℚ)
    (hn : n ≠ 0) (hd : d ≠ 0) :
    ((n * X - S) * G * k + n * B * d * b) / (n * d) =
      ((X - S / n) * G / d) * k + B * b := by
  field_simp [hn, hd] <;> ring

/-- The actual imported quotient rounder is determined by a strict integer
midpoint certificate. This proof uses quotient/remainder only in the proof;
the proposed runtime certificate evaluates just the two inequalities. -/
theorem roundQuotientEven_of_strict_cell (N D M : Nat) (hD : 0 < D)
    (hlo : 2 * M * D < 2 * N + D)
    (hhi : 2 * N < 2 * M * D + D) :
    FloatLib.Numerics.roundQuotientEven N D = M := by
  let q := N / D
  let r := N % D
  have hqr : q * D + r = N := by
    dsimp [q, r]
    exact Nat.div_add_mod' N D
  have hrD : r < D := Nat.mod_lt N hD
  have hq : q ≤ M := by
    by_contra h
    have hstep : M + 1 ≤ q := by omega
    have hprod := Nat.mul_le_mul_right D hstep
    nlinarith
  have hMq : M ≤ q + 1 := by
    by_contra h
    have hstep : q + 2 ≤ M := by omega
    have hprod := Nat.mul_le_mul_right D hstep
    nlinarith
  rcases Nat.eq_or_lt_of_le hq with heq | hlt
  · have hr : 2 * (N % D) < D := by
      change 2 * r < D
      nlinarith
    unfold FloatLib.Numerics.roundQuotientEven
    dsimp only
    rw [if_pos hr]
    exact heq
  · have heq : M = q + 1 := by omega
    have hr : D < 2 * (N % D) := by
      change D < 2 * r
      nlinarith
    unfold FloatLib.Numerics.roundQuotientEven
    dsimp only
    rw [if_neg (by omega), if_pos hr]
    exact heq.symm

/-- The ordinary normal/subnormal lattice: values are multiples of `4B`
in the common quarter-ULP coordinate used below. -/
theorem ordinary_grid_cell (A B M : Nat) (hB : 0 < B)
    (hlo : 4 * M * B < A + 2 * B)
    (hhi : A < 4 * M * B + 2 * B) :
    FloatLib.Numerics.roundQuotientEven A (4 * B) = M := by
  apply roundQuotientEven_of_strict_cell A (4 * B) M (by omega)
  · nlinarith
  · nlinarith

/-- Immediately below a normal power of two (except the minimum normal),
the lattice spacing is half as large. The mantissa rounds to `2M`, which
the final packing bridge must carry into the next binade. -/
theorem power_boundary_lower_grid (A B M : Nat) (hB : 0 < B)
    (hlo : 4 * M * B < A + B)
    (hhi : A ≤ 4 * M * B) :
    FloatLib.Numerics.roundQuotientEven A (2 * B) = 2 * M := by
  apply roundQuotientEven_of_strict_cell A (2 * B) (2 * M) (by omega)
  · nlinarith
  · nlinarith

def normalValue (e f : Nat) : ℚ :=
  ((8388608 + f : Nat) : ℚ) * (2 : ℚ) ^ ((e : Int) - 150)

/-- A mathematical predecessor value, including the subnormal predecessor
of minimum normal. The input is intended to satisfy 1 ≤ e ≤ 254 and
f < 2^23. Its equivalence to raw-word predecessor is a separate bridge. -/
def previousValue (e f : Nat) : ℚ :=
  if f = 0 ∧ 1 < e then
    16777215 * (2 : ℚ) ^ ((e : Int) - 151)
  else
    (((8388608 + f : Nat) : ℚ) - 1) *
      (2 : ℚ) ^ ((e : Int) - 150)

/-- At the largest finite value this is the virtual successor 2^128,
whose midpoint is the RN overflow threshold. It is not a finite binary32. -/
def nextOrVirtualValue (e f : Nat) : ℚ :=
  (((8388608 + f : Nat) : ℚ) + 1) *
    (2 : ℚ) ^ ((e : Int) - 150)

def lowerCoeff (e f : Nat) : Nat :=
  if f = 0 ∧ 1 < e then 4 * (8388608 + f) - 1
  else 4 * (8388608 + f) - 2

def upperCoeff (f : Nat) : Nat := 4 * (8388608 + f) + 2

private theorem exponent_step_one (e : Nat) :
    (2 : ℚ) ^ ((e : Int) - 151) =
      2 * (2 : ℚ) ^ ((e : Int) - 152) := by
  rw [show (e : Int) - 151 = ((e : Int) - 152) + 1 by omega,
    zpow_add₀ (by norm_num : (2 : ℚ) ≠ 0)]
  norm_num <;> ring

private theorem exponent_step_two (e : Nat) :
    (2 : ℚ) ^ ((e : Int) - 150) =
      4 * (2 : ℚ) ^ ((e : Int) - 152) := by
  rw [show (e : Int) - 150 = ((e : Int) - 152) + 2 by omega,
    zpow_add₀ (by norm_num : (2 : ℚ) ≠ 0)]
  norm_num <;> ring

theorem lower_midpoint (e f : Nat) :
    (previousValue e f + normalValue e f) / 2 =
      (lowerCoeff e f : ℚ) * (2 : ℚ) ^ ((e : Int) - 152) := by
  by_cases h : f = 0 ∧ 1 < e
  · rcases h with ⟨hf, he⟩
    subst f
    simp only [previousValue, normalValue, lowerCoeff,
      show (0 = 0 ∧ 1 < e) from ⟨rfl, he⟩, if_true, add_zero]
    simp only [exponent_step_one, exponent_step_two]
    norm_num <;> ring
  · simp only [previousValue, normalValue, lowerCoeff, h, if_false]
    simp only [exponent_step_two]
    have hsub : 2 ≤ 4 * (8388608 + f) := by omega
    rw [Nat.cast_sub hsub]
    push_cast
    ring

theorem upper_midpoint (e f : Nat) :
    (normalValue e f + nextOrVirtualValue e f) / 2 =
      (upperCoeff f : ℚ) * (2 : ℚ) ^ ((e : Int) - 152) := by
  unfold normalValue nextOrVirtualValue upperCoeff
  simp only [exponent_step_two]
  push_cast
  ring

theorem minimum_normal_uses_full_gap : lowerCoeff 1 0 = 33554430 := by
  norm_num [lowerCoeff]

theorem other_normal_power_uses_half_gap (e : Nat) (he : 1 < e) :
    lowerCoeff e 0 = 33554431 := by
  simp [lowerCoeff, he]

theorem maximum_finite_virtual_successor :
    nextOrVirtualValue 254 8388607 = (2 : ℚ) ^ (128 : Int) := by
  norm_num [nextOrVirtualValue]

/-- A common exponent shift is moved to the integer side only after its
direction has been chosen. This statement has no saturating Nat subtraction. -/
theorem quotient_cell_scaled (A D L U : ℚ) (hD : 0 < D)
    (k : ℚ) (hk : 0 < k)
    (hlo : L * D < A) (hhi : A < U * D) :
    L * k < (A / D) * k ∧ (A / D) * k < U * k := by
  constructor
  · exact mul_lt_mul_of_pos_right ((lt_div_iff₀ hD).2 hlo) hk
  · exact mul_lt_mul_of_pos_right ((div_lt_iff₀ hD).2 hhi) hk

/-- Strict midpoint membership gives strict superiority to both neighbours.
The raw32 RNE theorem must still connect these rational neighbours to the
imported rounder, including normalisation carry and overflow. -/
theorem strictly_closer_than_neighbours (p q r y : ℚ)
    (hpq : p < q) (hqr : q < r)
    (hlo : (p + q) / 2 < y) (hhi : y < (q + r) / 2) :
    (y - q) ^ 2 < (y - p) ^ 2 ∧
      (y - q) ^ 2 < (y - r) ^ 2 := by
  constructor
  · have hp := mul_pos (sub_pos.mpr hpq)
        (show 0 < 2 * y - p - q by linarith)
    nlinarith
  · have hp := mul_pos (sub_pos.mpr hqr)
        (show 0 < r + q - 2 * y by linarith)
    nlinarith

/-- A concrete counterexample to using a symmetric full ULP below 1.0.
The erroneous wider cell accepts this value for 1.0; the actual lower
midpoint of 1.0 lies above it. -/
theorem power_of_two_symmetric_gap_counterexample :
    (1 : ℚ) - 1 / 16777216 < 1 - 3 / 67108864 ∧
      (1 : ℚ) - 3 / 67108864 < 1 - 1 / 33554432 := by
  norm_num

/-- A vanished term imposes no exponent-alignment requirement. The runtime
returns to the old implementation when both coefficients vanish. -/
def activeBase (A B : Int) (alpha beta : Nat) : Nat :=
  if A = 0 then beta else if B = 0 then alpha else min alpha beta

def activeShift (A : Int) (e c : Nat) : Nat :=
  if A = 0 then 0 else e - c

theorem activeBase_le_left (A B : Int) (alpha beta : Nat)
    (hA : A ≠ 0) : activeBase A B alpha beta ≤ alpha := by
  unfold activeBase
  rw [if_neg hA]
  split_ifs
  · exact le_refl _
  · exact min_le_left _ _

theorem activeBase_le_right (A B : Int) (alpha beta : Nat)
    (hB : B ≠ 0) : activeBase A B alpha beta ≤ beta := by
  unfold activeBase
  by_cases hA : A = 0
  · rw [if_pos hA]
  · rw [if_neg hA, if_neg hB]
    exact min_le_right _ _

/-- For a zero coefficient, a zero shift is exact even if e < c. For a
nonzero coefficient, the actual lower-bound premise prevents Nat saturation. -/
theorem active_term_alignment (A : Int) (e c : Nat)
    (hc : A ≠ 0 → c ≤ e) :
    (A : ℚ) * (2 : ℚ) ^ activeShift A e c * (2 : ℚ) ^ (c : Int) =
      (A : ℚ) * (2 : ℚ) ^ (e : Int) := by
  by_cases hA : A = 0
  · simp [hA]
  · have hce := hc hA
    have he : ((e - c : Nat) : Int) + (c : Int) = (e : Int) := by omega
    simp only [activeShift, hA, if_false]
    rw [← zpow_natCast (2 : ℚ) (e - c), mul_assoc,
      ← zpow_add₀ (by norm_num : (2 : ℚ) ≠ 0), he]

/-- Exact alignment of both signed coefficients with zero terms ignored.
In layernorm use A=(nX-S)*sg*mg and B=n*sb*mb*md. -/
theorem zero_aware_alignment (A B : Int) (alpha beta : Nat) :
    let c := activeBase A B alpha beta
    ((A : ℚ) * (2 : ℚ) ^ activeShift A alpha c +
      (B : ℚ) * (2 : ℚ) ^ activeShift B beta c) *
        (2 : ℚ) ^ (c : Int) =
      (A : ℚ) * (2 : ℚ) ^ (alpha : Int) +
        (B : ℚ) * (2 : ℚ) ^ (beta : Int) := by
  dsimp only
  rw [add_mul,
    active_term_alignment A alpha (activeBase A B alpha beta)
      (activeBase_le_left A B alpha beta),
    active_term_alignment B beta (activeBase A B alpha beta)
      (activeBase_le_right A B alpha beta)]

end R28Cell
