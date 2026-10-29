namespace Submission.R26WordBlock

theorem termMass_uniform (a b : Nat → UInt32) (fuel i : Nat) (bound : Int)
    (h : ∀ j, i ≤ j → j < i + fuel →
      |signed64 (extend32 (a j)) * signed64 (extend32 (b j))| ≤ bound) :
    termMass a b fuel i ≤ (fuel : Int) * bound := by
  induction fuel generalizing i with
  | zero => simp [termMass]
  | succ fuel ih =>
    have hh := h i (by omega) (by omega)
    have ht := ih (i + 1) (fun j h1 h2 => h j (by omega) (by omega))
    simp only [termMass, Nat.cast_add, Nat.cast_one]
    nlinarith

theorem block_exact_16 (a b : Nat → UInt32) (fuel i : Nat) (hf : fuel ≤ 16)
    (h : ∀ j, i ≤ j → j < i + fuel →
      |signed64 (extend32 (a j)) * signed64 (extend32 (b j))| < 576460752303423488) :
    signed64 (block a b fuel i 0) = exactTerms a b fuel i := by
  apply block_exact
  have hu := termMass_uniform a b fuel i 576460752303423487
    (fun j h1 h2 => by have := h j h1 h2; omega)
  omega

def blockSums (a b : Nat → UInt32) : Nat → Nat → Int
  | 0, _ => 0
  | count + 1, i => exactTerms a b 16 i + blockSums a b count (i + 16)

theorem exactTerms_add (a b : Nat → UInt32) (m n i : Nat) :
    exactTerms a b (m + n) i = exactTerms a b m i + exactTerms a b n (i + m) := by
  induction m generalizing i with
  | zero => simp [exactTerms]
  | succ m ih =>
    simp [Nat.succ_add, exactTerms, ih, Nat.add_assoc, Nat.add_comm,
      Nat.add_left_comm, Int.add_assoc]

theorem blockSums_eq (a b : Nat → UInt32) (count i : Nat) :
    blockSums a b count i = exactTerms a b (count * 16) i := by
  induction count generalizing i with
  | zero => simp [blockSums, exactTerms]
  | succ count ih =>
    rw [blockSums, ih]
    have hn : (count + 1) * 16 = 16 + count * 16 := by omega
    rw [hn, exactTerms_add]

theorem blocks_represents (a b : Nat → UInt32) (count i : Nat)
    (lo hi : UInt64) (initial : Int) (hinit : Represents128 lo hi initial)
    (hblock : ∀ j, j < count →
      termMass a b 16 (i + j * 16) < 9223372036854775808) :
    Represents128 (blocks a b count i lo hi).1 (blocks a b count i lo hi).2
      (initial + blockSums a b count i) := by
  induction count generalizing i lo hi initial with
  | zero => simpa [blocks, blockSums] using hinit
  | succ count ih =>
    have hfirst : signed64 (block a b 16 i 0) = exactTerms a b 16 i := by
      exact block_exact a b 16 i (by simpa using hblock 0 (by omega))
    have hs := merge_represents128 lo hi (block a b 16 i 0) initial hinit
    rw [hfirst] at hs
    have ht : ∀ j, j < count →
        termMass a b 16 (i + 16 + j * 16) < 9223372036854775808 := by
      intro j hj
      have hh := hblock (j + 1) (by omega)
      convert hh using 1 <;> omega
    simpa only [blocks, blockSums, Int.add_assoc] using
      ih (i + 16) (lo + block a b 16 i 0) (mergeHi lo hi (block a b 16 i 0))
        (initial + exactTerms a b 16 i) hs ht

theorem body128_represents (n : Nat) (a b : Nat → UInt32)
    (hblock : ∀ j, j < n / 16 →
      termMass a b 16 (j * 16) < 9223372036854775808)
    (htail : termMass a b (n % 16) (n / 16 * 16) < 9223372036854775808) :
    Represents128 (body128 n a b).1 (body128 n a b).2 (exactTerms a b n 0) := by
  have hz : Represents128 (0 : UInt64) 0 0 := ⟨0, by simp⟩
  have hb := blocks_represents a b (n / 16) 0 0 0 0 hz (by simpa using hblock)
  simp only [zero_add, blockSums_eq] at hb
  have ht := merge_represents128 (blocks a b (n / 16) 0 0 0).1
    (blocks a b (n / 16) 0 0 0).2 (block a b (n % 16) (n / 16 * 16) 0)
    (exactTerms a b (n / 16 * 16) 0) hb
  rw [block_exact a b (n % 16) (n / 16 * 16) htail] at ht
  have hn : n / 16 * 16 + n % 16 = n := by omega
  have hsplit := exactTerms_add a b (n / 16 * 16) (n % 16) 0
  rw [hn, zero_add] at hsplit
  simpa only [body128, hsplit] using ht

theorem body128_exact (n : Nat) (a b : Nat → UInt32)
    (hblock : ∀ j, j < n / 16 →
      termMass a b 16 (j * 16) < 9223372036854775808)
    (htail : termMass a b (n % 16) (n / 16 * 16) < 9223372036854775808)
    (hglobal : -170141183460469231731687303715884105728 ≤ exactTerms a b n 0 ∧
      exactTerms a b n 0 < 170141183460469231731687303715884105728) :
    signed128 (body128 n a b).1 (body128 n a b).2 = exactTerms a b n 0 :=
  signed128_unique _ _ _ (body128_represents n a b hblock htail) hglobal

theorem finish_body128 (n : Nat) (a b : Nat → UInt32) (bias exponent : Int) (nz : Bool)
    (hexact : signed128 (body128 n a b).1 (body128 n a b).2 = exactTerms a b n 0) :
    ExactRuntime.finishWord (signed128 (body128 n a b).1 (body128 n a b).2 + bias) exponent nz =
      ExactRuntime.finishWord (exactTerms a b n 0 + bias) exponent nz := by
  rw [hexact]

end Submission.R26WordBlock
