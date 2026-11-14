namespace Submission.R26WordBlock

theorem signed32_abs_bound (w : UInt32) : |signed32 w| ≤ 2147483648 := by
  have hw := w.toNat_lt
  unfold signed32
  split_ifs with h
  · rw [abs_of_nonneg (by omega)]
    omega
  · rw [abs_of_nonpos (by omega)]
    omega

theorem term_abs_bound (a b : UInt32) :
    |signed64 (extend32 a) * signed64 (extend32 b)| ≤ 4611686018427387904 := by
  rw [extend32_signed, extend32_signed, abs_mul]
  have ha := signed32_abs_bound a
  have hb := signed32_abs_bound b
  nlinarith [abs_nonneg (signed32 a), abs_nonneg (signed32 b)]

theorem each_product_exact (a b : UInt32) :
    signed64 (extend32 a * extend32 b) = signed64 (extend32 a) * signed64 (extend32 b) := by
  apply signed64_unique
  · exact mul_represents64 _ _ _ _ (signed64_represents _) (signed64_represents _)
  · have h := term_abs_bound a b
    have hh := abs_le.mp h
    omega

theorem body128Each_represents (a b : Nat → UInt32) (fuel i : Nat)
    (lo hi : UInt64) (initial : Int) (h : Represents128 lo hi initial) :
    Represents128 (body128Each a b fuel i lo hi).1 (body128Each a b fuel i lo hi).2
      (initial + exactTerms a b fuel i) := by
  induction fuel generalizing i lo hi initial with
  | zero => simpa [body128Each, exactTerms] using h
  | succ fuel ih =>
    have hs := merge_represents128 lo hi (extend32 (a i) * extend32 (b i)) initial h
    rw [each_product_exact] at hs
    simpa only [body128Each, exactTerms, Int.add_assoc] using
      ih (i + 1) (lo + extend32 (a i) * extend32 (b i))
        (mergeHi lo hi (extend32 (a i) * extend32 (b i)))
        (initial + signed64 (extend32 (a i)) * signed64 (extend32 (b i))) hs

theorem exactTerms_global_bound (n : Nat) (a b : Nat → UInt32) (hn : n ≤ 1048576) :
    -170141183460469231731687303715884105728 ≤ exactTerms a b n 0 ∧
      exactTerms a b n 0 < 170141183460469231731687303715884105728 := by
  have hb := termMass_uniform a b n 0 4611686018427387904
    (fun j _ _ => term_abs_bound (a j) (b j))
  have ha := exactTerms_abs_le a b n 0
  have hh := abs_le.mp (le_trans ha hb)
  omega

theorem body128Each_exact (n : Nat) (a b : Nat → UInt32) (hn : n ≤ 1048576) :
    signed128 (body128Each a b n 0 0 0).1 (body128Each a b n 0 0 0).2 =
      exactTerms a b n 0 := by
  apply signed128_unique
  · have hz : Represents128 (0 : UInt64) 0 0 := ⟨0, by simp⟩
    simpa using body128Each_represents a b n 0 0 0 0 hz
  · exact exactTerms_global_bound n a b hn

theorem signMask32_nat (w : UInt32) :
    (w &&& 0x80000000).toNat = (w.toNat / 2147483648) * 2147483648 := by
  rw [UInt32.toNat_and]
  change w.toNat &&& 2147483648 = _
  have hw := w.toNat_lt
  have hd := Nat.and_div_two_pow (a := w.toNat) (b := 2147483648) (n := 31)
  have hm := Nat.and_mod_two_pow (a := w.toNat) (b := 2147483648) (n := 31)
  norm_num only [show (2 ^ 31 : Nat) = 2147483648 by decide,
    Nat.div_self, Nat.mod_self, Nat.and_zero] at hd hm
  have hs : w.toNat / 2147483648 = 0 ∨ w.toNat / 2147483648 = 1 := by omega
  rcases hs with hs | hs <;> simp only [hs] at hd <;> norm_num at hd <;> omega

theorem magnitude32_abs (w : UInt32) : (magnitude32 w).toNat = (signed32 w).natAbs := by
  have hw := w.toNat_lt
  have hm := signMask32_nat w
  by_cases hs : w.toNat < 2147483648
  · have hz : w &&& 0x80000000 = 0 := by
      apply UInt32.toNat_inj.mp
      rw [hm]
      change w.toNat / 2147483648 * 2147483648 = 0
      omega
    simp [magnitude32, hz, signed32, hs]
  · have hn : w &&& 0x80000000 ≠ 0 := by
      intro hz
      have he := congrArg UInt32.toNat hz
      rw [hm] at he
      change w.toNat / 2147483648 * 2147483648 = 0 at he
      omega
    have hi : (w.toNat : Int) - 4294967296 ≤ 0 := by omega
    have hiabs : ((w.toNat : Int) - 4294967296).natAbs = 4294967296 - w.toNat := by
      apply Int.ofNat_inj.mp
      rw [Int.natCast_natAbs, abs_of_nonpos hi]
      omega
    simp only [magnitude32, bne_iff_ne.mpr hn, ite_true, UInt32.toNat_sub,
      UInt32.toNat_zero, Nat.add_zero, signed32, if_neg hs, hiabs]
    omega

theorem maxMagnitude_initial (f : Nat → UInt32) (fuel i : Nat) (mx : UInt32) :
    mx ≤ maxMagnitude f fuel i mx := by
  induction fuel generalizing i mx with
  | zero => simp [maxMagnitude]
  | succ fuel ih =>
    simp only [maxMagnitude]
    split_ifs with h
    · exact le_trans (le_of_lt h) (ih (i + 1) (magnitude32 (f i)))
    · exact ih (i + 1) mx

theorem maxMagnitude_term (f : Nat → UInt32) (fuel i : Nat) (mx : UInt32)
    (j : Nat) (hj : i ≤ j) (hstop : j < i + fuel) :
    magnitude32 (f j) ≤ maxMagnitude f fuel i mx := by
  induction fuel generalizing i mx with
  | zero => omega
  | succ fuel ih =>
    by_cases heq : j = i
    · subst j
      simp only [maxMagnitude]
      split_ifs with h
      · exact maxMagnitude_initial f fuel (i + 1) _
      · exact le_trans (le_of_not_gt h) (maxMagnitude_initial f fuel (i + 1) mx)
    · simp only [maxMagnitude]
      exact ih (i + 1) _ (by omega) (by omega)

theorem maxMagnitude_abs (f : Nat → UInt32) (n j : Nat) (hj : j < n) :
    |signed64 (extend32 (f j))| ≤ ((maxMagnitude f n 0 0).toNat : Int) := by
  have h := maxMagnitude_term f n 0 0 j (by omega) (by omega)
  rw [UInt32.le_iff_toNat_le, magnitude32_abs] at h
  rw [extend32_signed, ← Int.natCast_natAbs]
  exact_mod_cast h

theorem canBlock16_terms (n : Nat) (a b : Nat → UInt32)
    (hg : canBlock16 n (maxMagnitude a n 0 0) (maxMagnitude b n 0 0) = true)
    (j : Nat) (hj : j < n) :
    |signed64 (extend32 (a j)) * signed64 (extend32 (b j))| < 576460752303423488 := by
  have ha := maxMagnitude_abs a n j hj
  have hb := maxMagnitude_abs b n j hj
  have hma := (maxMagnitude a n 0 0).toNat_lt
  have hmb := (maxMagnitude b n 0 0).toNat_lt
  have hp : (maxMagnitude a n 0 0).toNat * (maxMagnitude b n 0 0).toNat < 18446744073709551616 := by
    have h := Nat.mul_lt_mul'' hma hmb
    norm_num at h
    exact h
  simp only [canBlock16, Bool.and_eq_true, decide_eq_true_eq] at hg
  have hlt := hg.2
  rw [UInt64.lt_iff_toNat_lt, UInt64.toNat_mul, UInt32.toNat_toUInt64,
    UInt32.toNat_toUInt64, Nat.mod_eq_of_lt hp] at hlt
  change (maxMagnitude a n 0 0).toNat * (maxMagnitude b n 0 0).toNat <
    576460752303423488 at hlt
  rw [abs_mul]
  have hab : |signed64 (extend32 (a j))| * |signed64 (extend32 (b j))| ≤
      ((maxMagnitude a n 0 0).toNat : Int) * (maxMagnitude b n 0 0).toNat :=
    mul_le_mul ha hb (abs_nonneg _) (by positivity)
  have hcast : ((maxMagnitude a n 0 0).toNat : Int) * (maxMagnitude b n 0 0).toNat <
      576460752303423488 := by exact_mod_cast hlt
  exact lt_of_le_of_lt hab hcast

theorem preparedBody_exact (n : Nat) (a b : Nat → UInt32) (hn : n ≤ 1048576) :
    signed128 (preparedBody n a b).1 (preparedBody n a b).2 = exactTerms a b n 0 := by
  unfold preparedBody
  split_ifs with hg
  · apply body128_exact
    · intro j hj
      have hu := termMass_uniform a b 16 (j * 16) 576460752303423487
        (fun k h1 h2 => by
          have hkn : k < n := by omega
          have hh := canBlock16_terms n a b hg k hkn
          omega)
      norm_num at hu
      omega
    · have hu := termMass_uniform a b (n % 16) (n / 16 * 16) 576460752303423487
        (fun k h1 h2 => by
          have hkn : k < n := by omega
          have hh := canBlock16_terms n a b hg k hkn
          omega)
      have hrem : n % 16 < 16 := Nat.mod_lt _ (by omega)
      omega
    · exact exactTerms_global_bound n a b hn
  · exact body128Each_exact n a b hn

theorem preparedFinish_exact (n : Nat) (a b : Nat → UInt32) (hn : n ≤ 1048576)
    (bias exponent : Int) (nz : Bool) :
    preparedFinish n a b bias exponent nz =
      ExactRuntime.finishWord (exactTerms a b n 0 + bias) exponent nz := by
  simp only [preparedFinish, preparedBody_exact n a b hn]

end Submission.R26WordBlock
