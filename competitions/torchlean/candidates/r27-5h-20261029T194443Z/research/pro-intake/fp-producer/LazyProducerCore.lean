import ContractExact

/-!
# LazyFPOnly: small arithmetic producer core

STATUS: NOT_COMPILED. No Lean executable was available to the author.
This file contains original mathematical lemmas only. It does not claim a
FloatLib/native-Float bridge, a checked Kernel, or a performance result.

`R : ℝ → ℝ` is an explicit, abstract rounding map. Its hypotheses below are
ordinary theorem parameters, not axioms and not claims about Lean's `Float`.
The real-valued interface matches FloatLib `roundAt` / `toReal` directly.
The actual binary64 instantiation must prove endpoint-envelope preservation,
exactness of the first product, and the absolute half-ulp cap. Nothing
in this file assumes a nonexistent FloatLib API.

For the intended instantiation:
* M = 2^(H-250), N = 2^L, 0 <= H <= 506, 0 <= L <= 30;
* every exact product t[k] satisfies |t[k]| < M;
* R is RN-even binary64 on the finite range reached by this fold;
* C = N*M/2^54 for the uniform-cap proof;
* hgrid follows from *finite-range* RN monotonicity and exact endpoints
  ±(k*M), k <= N, because k <= 2^30 and M is a power of two. It does not
  assume native Float is monotone on NaN/Infinity or any unguarded domain;
* R(t[0]) = t[0], because the binary32 product has at most 48 bits;
* |z| < N*M gives |R(z)-z| <= C, including zero and the normal-boundary
  cases. The cap is far above binary64's underflow region and far below
  its overflow region.

Then the error is <= (n-1)*C < N*C for 0<n<=N. N*C is precisely the radius
encoded by replacing the helper's exponent-field constant 720 with 719.
The original 720 radius is twice as large. The final theorem requires term
bounds only for the n actual products. It does not pad or change the fold.

The alternative triangular theorem is a pure telescoping lemma. To apply it
to native binary64 one must separately establish the *actual* local bound
|local error at zero-based step k| <= k*C, with C = M/2^53. Its k=0 case
requires the exact first product/addition and is not silently dropped.
-/

namespace LazyFPOnlyProducerCore

noncomputable def exactPrefix (t : Nat → ℝ) : Nat → ℝ
  | 0 => 0
  | k + 1 => exactPrefix t k + t k

noncomputable def roundedPrefix (R : ℝ → ℝ) (t : Nat → ℝ) : Nat → ℝ
  | 0 => 0
  | k + 1 => R (roundedPrefix R t k + t k)

theorem empty_exact (R : ℝ → ℝ) (t : Nat → ℝ) :
    roundedPrefix R t 0 = exactPrefix t 0 := rfl

theorem round_abs_le
    (R : ℝ → ℝ) (hmono : Monotone R) (x K : ℝ)
    (hneg : R (-K) = -K) (hpos : R K = K)
    (hx : |x| ≤ K) : |R x| ≤ K := by
  rcases abs_le.mp hx with ⟨hl, hr⟩
  apply abs_le.mpr
  constructor
  · calc
      -K = R (-K) := hneg.symm
      _ ≤ R x := hmono hl
  · calc
      R x ≤ R K := hmono hr
      _ = K := hpos

/-- The rounded fold cannot escape the exactly representable endpoints
    ±kM. This is the reason no growth factor is needed in the cap proof. -/
theorem rounded_envelope
    (R : ℝ → ℝ) (t : Nat → ℝ) (N : Nat) (M : ℝ)
    (hgrid : ∀ k, k ≤ N → ∀ z,
      |z| ≤ (k : ℝ) * M → |R z| ≤ (k : ℝ) * M)
    (hterm : ∀ k, k < N → |t k| < M) :
    ∀ k, k ≤ N → |roundedPrefix R t k| ≤ (k : ℝ) * M := by
  intro k
  induction k with
  | zero =>
      intro hk
      simp [roundedPrefix]
  | succ k ih =>
      intro hk
      have hp := ih (show k ≤ N by omega)
      have ht := hterm k (show k < N by omega)
      have hz : |roundedPrefix R t k + t k| < ((k + 1 : Nat) : ℝ) * M := by
        calc
          |roundedPrefix R t k + t k| ≤ |roundedPrefix R t k| + |t k| :=
            abs_add _ _
          _ < (k : ℝ) * M + M := add_lt_add_of_le_of_lt hp ht
          _ = ((k + 1 : Nat) : ℝ) * M := by push_cast; ring
      change |R (roundedPrefix R t k + t k)| ≤ ((k + 1 : Nat) : ℝ) * M
      exact hgrid (k + 1) hk _ (le_of_lt hz)

/-- The exact pre-round addition is strictly below the common cap N*M. -/
theorem pre_round_lt_cap
    (R : ℝ → ℝ) (t : Nat → ℝ) (N : Nat) (M : ℝ)
    (hM : 0 ≤ M)
    (hgrid : ∀ k, k ≤ N → ∀ z,
      |z| ≤ (k : ℝ) * M → |R z| ≤ (k : ℝ) * M)
    (hterm : ∀ k, k < N → |t k| < M)
    (k : Nat) (hk : k < N) :
    |roundedPrefix R t k + t k| < (N : ℝ) * M := by
  have hp := rounded_envelope R t N M hgrid hterm k (Nat.le_of_lt hk)
  have ht := hterm k hk
  have hkq : (k : ℝ) + 1 ≤ (N : ℝ) := by exact_mod_cast (show k + 1 ≤ N by omega)
  calc
    |roundedPrefix R t k + t k| ≤ |roundedPrefix R t k| + |t k| := abs_add _ _
    _ < (k : ℝ) * M + M := add_lt_add_of_le_of_lt hp ht
    _ = ((k : ℝ) + 1) * M := by ring
    _ ≤ (N : ℝ) * M := mul_le_mul_of_nonneg_right hkq hM

theorem one_step_error (R : ℝ → ℝ) (s S t : ℝ) :
    |R (s + t) - (S + t)| ≤ |R (s + t) - (s + t)| + |s - S| := by
  calc
    |R (s + t) - (S + t)| = |(R (s + t) - (s + t)) + (s - S)| := by
      congr 1
      ring
    _ ≤ |R (s + t) - (s + t)| + |s - S| := abs_add _ _

/-- Uniform half-ulp cap, with the exact first addition counted explicitly. -/
theorem uniform_error_le
    (R : ℝ → ℝ) (t : Nat → ℝ) (N : Nat) (M C : ℝ)
    (hM : 0 ≤ M)
    (hgrid : ∀ k, k ≤ N → ∀ z,
      |z| ≤ (k : ℝ) * M → |R z| ≤ (k : ℝ) * M)
    (hterm : ∀ k, k < N → |t k| < M)
    (hfirst : R (t 0) = t 0)
    (hlocal : ∀ z, |z| < (N : ℝ) * M → |R z - z| ≤ C) :
    ∀ k, k + 1 ≤ N →
      |roundedPrefix R t (k + 1) - exactPrefix t (k + 1)| ≤ (k : ℝ) * C := by
  intro k
  induction k with
  | zero =>
      intro hk
      simp [roundedPrefix, exactPrefix, hfirst]
  | succ k ih =>
      intro hk
      have hp := ih (show k + 1 ≤ N by omega)
      have hz := pre_round_lt_cap R t N M hM hgrid hterm (k + 1)
        (show k + 1 < N by omega)
      have he := hlocal _ hz
      calc
        |roundedPrefix R t ((k + 1) + 1) - exactPrefix t ((k + 1) + 1)| =
            |R (roundedPrefix R t (k + 1) + t (k + 1)) -
              (exactPrefix t (k + 1) + t (k + 1))| := rfl
        _ ≤ |R (roundedPrefix R t (k + 1) + t (k + 1)) -
                (roundedPrefix R t (k + 1) + t (k + 1))| +
              |roundedPrefix R t (k + 1) - exactPrefix t (k + 1)| :=
            one_step_error R _ _ _
        _ ≤ C + (k : ℝ) * C := add_le_add he hp
        _ = ((k + 1 : Nat) : ℝ) * C := by push_cast; ring

/-- Strict positive radius: n=1 has error zero; n=0 is handled separately. -/
theorem uniform_error_strict
    (R : ℝ → ℝ) (t : Nat → ℝ) (N n : Nat) (M C : ℝ)
    (hM : 0 ≤ M) (hC : 0 < C)
    (hgrid : ∀ k, k ≤ n → ∀ z,
      |z| ≤ (k : ℝ) * M → |R z| ≤ (k : ℝ) * M)
    (hterm : ∀ k, k < n → |t k| < M)
    (hfirst : R (t 0) = t 0)
    (hlocal : ∀ z, |z| < (N : ℝ) * M → |R z - z| ≤ C)
    (hn : 0 < n) (hnN : n ≤ N) :
    |roundedPrefix R t n - exactPrefix t n| < (N : ℝ) * C := by
  have hcount : (n : ℝ) ≤ (N : ℝ) := by exact_mod_cast hnN
  have hlocaln : ∀ z, |z| < (n : ℝ) * M → |R z - z| ≤ C := by
    intro z hz
    apply hlocal z
    exact lt_of_lt_of_le hz (mul_le_mul_of_nonneg_right hcount hM)
  have hbound := uniform_error_le R t n M C hM hgrid hterm hfirst hlocaln
  cases n with
  | zero => omega
  | succ k =>
      have he := hbound k (show k + 1 ≤ k + 1 by omega)
      have hk : (k : ℝ) < (N : ℝ) := by exact_mod_cast (show k < N by omega)
      exact lt_of_le_of_lt he (mul_lt_mul_of_pos_right hk hC)

/-- A separate exact triangular telescope. `hstep` includes the zero-error
    first step at k=0; no gamma_n approximation occurs anywhere. -/
theorem triangular_error_le
    (R : ℝ → ℝ) (t : Nat → ℝ) (C : ℝ) :
    ∀ n, (∀ k, k < n →
      |R (roundedPrefix R t k + t k) - (roundedPrefix R t k + t k)| ≤ (k : ℝ) * C) →
      |roundedPrefix R t n - exactPrefix t n| ≤
        C * (n : ℝ) * ((n : ℝ) - 1) / 2 := by
  intro n
  induction n with
  | zero =>
      intro hs
      simp [roundedPrefix, exactPrefix]
  | succ n ih =>
      intro hs
      have hp := ih (fun k hk => hs k (Nat.lt_succ_of_lt hk))
      have he := hs n (Nat.lt_succ_self n)
      calc
        |roundedPrefix R t (n + 1) - exactPrefix t (n + 1)| =
            |R (roundedPrefix R t n + t n) - (exactPrefix t n + t n)| := rfl
        _ ≤ |R (roundedPrefix R t n + t n) - (roundedPrefix R t n + t n)| +
              |roundedPrefix R t n - exactPrefix t n| := one_step_error R _ _ _
        _ ≤ (n : ℝ) * C + C * (n : ℝ) * ((n : ℝ) - 1) / 2 := add_le_add he hp
        _ = C * ((n + 1 : Nat) : ℝ) * (((n + 1 : Nat) : ℝ) - 1) / 2 := by
          push_cast
          ring

theorem triangular_strict_radius
    (C : ℝ) (n N : Nat) (hC : 0 < C) (hn : 0 < n) (hnN : n ≤ N) :
    C * (n : ℝ) * ((n : ℝ) - 1) / 2 < C * (N : ℝ) * (N : ℝ) / 2 := by
  have hnp : (0 : ℝ) < (n : ℝ) := by exact_mod_cast hn
  have hnq : (n : ℝ) ≤ (N : ℝ) := by exact_mod_cast hnN
  have hsq : (n : ℝ) * (n : ℝ) ≤ (N : ℝ) * (N : ℝ) :=
    mul_le_mul hnq hnq (Nat.cast_nonneg _) (Nat.cast_nonneg _)
  have htri : (n : ℝ) * ((n : ℝ) - 1) < (N : ℝ) * (N : ℝ) := by nlinarith
  have hm := mul_lt_mul_of_pos_left htri hC
  nlinarith

/-- Relates the uniform-cap result to the two radius constants without any
    floating-point, word, or exponent-decoding assumptions. -/
theorem half_radius_identity (M : ℝ) (N : Nat) :
    (N : ℝ) * (((N : ℝ) * M) / (2 : ℝ)^54) =
      (M * (N : ℝ)^2 / (2 : ℝ)^53) / 2 := by
  norm_num <;> ring

end LazyFPOnlyProducerCore
