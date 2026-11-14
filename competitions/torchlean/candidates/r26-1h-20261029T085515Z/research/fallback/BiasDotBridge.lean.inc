namespace Submission.R26WordBlock
open ExactRuntime

def biasedA (n : Nat) (a : Nat → UInt32) (i : Nat) : UInt32 := if i < n then a i else oneW
def biasedB (n : Nat) (b : Nat → UInt32) (bias : UInt32) (i : Nat) : UInt32 :=
  if i < n then b i else bias

theorem rawSum_add (a b : Nat → UInt32) (m n i : Nat) :
    rawSum a b (m + n) i = rawSum a b m i + rawSum a b n (i + m) := by
  induction m generalizing i with
  | zero => simp [rawSum]
  | succ m ih =>
    simp [Nat.succ_add, rawSum, ih, Nat.add_assoc, Nat.add_comm,
      Nat.add_left_comm, Int.add_assoc]

theorem rawSum_congr (a b c d : Nat → UInt32) (fuel i : Nat)
    (h : ∀ j, i ≤ j → j < i + fuel → a j = c j ∧ b j = d j) :
    rawSum a b fuel i = rawSum c d fuel i := by
  induction fuel generalizing i with
  | zero => rfl
  | succ fuel ih =>
    have hh := h i (by omega) (by omega)
    rw [rawSum, rawSum, hh.1, hh.2,
      ih (i + 1) (fun j h1 h2 => h j (by omega) (by omega))]

theorem rawSum_biased (n : Nat) (a b : Nat → UInt32) (bias : UInt32) :
    rawSum (biasedA n a) (biasedB n b bias) (n + 1) 0 =
      rawSum a b n 0 + sv bias * 2 ^ (idxOf bias + 149) := by
  rw [rawSum_add]
  have hbody : rawSum (biasedA n a) (biasedB n b bias) n 0 = rawSum a b n 0 := by
    apply rawSum_congr
    intro j _ hj
    simp only [biasedA, biasedB, if_pos (by omega : j < n)]
    exact ⟨rfl, rfl⟩
  rw [hbody]
  simp only [zero_add, rawSum, biasedA, biasedB, Nat.lt_irrefl, if_false, add_zero]
  have hone : sv oneW = 8388608 ∧ idxOf oneW = 126 := by decide
  rw [hone.1, hone.2]
  congr 1
  calc
    8388608 * sv bias * (2 : Int) ^ (126 + idxOf bias) =
        sv bias * ((2 : Int) ^ 23 * 2 ^ (126 + idxOf bias)) := by norm_num; ring
    _ = sv bias * 2 ^ (idxOf bias + 149) := by
      rw [← pow_add]
      congr 2
      omega

theorem biased_dsum (n : Nat) (a b : Nat → UInt32) (bias : UInt32) :
    dsum (rawWords (n + 1) (biasedA n a)) (rawWords (n + 1) (biasedB n b bias)) 0 (n + 1) =
      dsum (rawWords n a) (rawWords n b) 0 n + sv bias * 2 ^ (idxOf bias + 149) := by
  rw [← rawSum_dsum (n + 1) _ _ (n + 1) 0 (by omega), rawSum_biased,
    rawSum_dsum n a b n 0 (by omega)]

theorem finish_prepared_bias_dot (n : Nat) (a b : Nat → UInt32) (baseA baseB : Nat)
    (hn : n ≤ 1048576) (bias : UInt32) (nz : Bool)
    (ha : ∀ j, j < n → mantOf (a j) * 2 ^ (idxOf (a j) - baseA) < 2147483648)
    (hb : ∀ j, j < n → mantOf (b j) * 2 ^ (idxOf (b j) - baseB) < 2147483648)
    (hla : ∀ j, j < n → mantOf (a j) ≠ 0 → baseA ≤ idxOf (a j))
    (hlb : ∀ j, j < n → mantOf (b j) ≠ 0 → baseB ≤ idxOf (b j))
    (hbi : baseA + baseB ≤ idxOf bias + 149)
    (hfinite : ∀ j, j < n → expOf (a j) ≠ 255 ∧ expOf (b j) ≠ 255)
    (hfb : expOf bias ≠ 255)
    (hzero : nz = dallNZ (rawWords (n + 1) (biasedA n a))
      (rawWords (n + 1) (biasedB n b bias)) 0 (n + 1)) :
    preparedFinish n (fun j => prepareFactor (a j) baseA) (fun j => prepareFactor (b j) baseB)
      (scaledBias bias (baseA + baseB)) (-298 + ((baseA + baseB : Nat) : Int)) nz =
      dotOf (n + 1) (biasedA n a) (biasedB n b bias) := by
  rw [finish_prepared_scaled n a b baseA baseB hn bias nz ha hb hla hlb hbi, ← biased_dsum]
  have hf : ∀ j, j < n + 1 → expOf (biasedA n a j) ≠ 255 ∧
      expOf (biasedB n b bias j) ≠ 255 := by
    intro j hj
    by_cases hbody : j < n
    · simpa [biasedA, biasedB, hbody] using hfinite j hbody
    · simp [biasedA, biasedB, hbody, hfb, oneW, expOf]
  rw [dotOf_finite_finish (n + 1) _ _ hf]
  simp [hzero]

end Submission.R26WordBlock
