namespace Submission.R26WordBlock
open ExactRuntime

def rawSum (a b : Nat → UInt32) : Nat → Nat → Int
  | 0, _ => 0
  | fuel + 1, i => sv (a i) * sv (b i) * 2 ^ (idxOf (a i) + idxOf (b i)) +
      rawSum a b fuel (i + 1)

theorem rawSum_dsum (n : Nat) (a b : Nat → UInt32) (fuel i : Nat) (hi : i + fuel ≤ n) :
    rawSum a b fuel i = dsum (rawWords n a) (rawWords n b) i fuel := by
  induction fuel generalizing i with
  | zero => rfl
  | succ fuel ih =>
    rw [rawSum, dsum, rawWords_get n a i (by omega), rawWords_get n b i (by omega),
      ih (i + 1) (by omega)]

theorem sv_zero (w : UInt32) (h : mantOf w = 0) : sv w = 0 := by
  simp [sv, h]

theorem alignedTerms_scale (a b : Nat → UInt32) (baseA baseB fuel i : Nat)
    (ha : ∀ j, i ≤ j → j < i + fuel → mantOf (a j) ≠ 0 → baseA ≤ idxOf (a j))
    (hb : ∀ j, i ≤ j → j < i + fuel → mantOf (b j) ≠ 0 → baseB ≤ idxOf (b j)) :
    alignedTerms a b baseA baseB fuel i * 2 ^ (baseA + baseB) = rawSum a b fuel i := by
  induction fuel generalizing i with
  | zero => simp [alignedTerms, rawSum]
  | succ fuel ih =>
    rw [alignedTerms, add_mul,
      ih (i + 1) (fun j h1 h2 hn => ha j (by omega) (by omega) hn)
        (fun j h1 h2 hn => hb j (by omega) (by omega) hn), rawSum]
    congr 1
    by_cases hza : mantOf (a i) = 0
    · simp [sv_zero (a i) hza]
    by_cases hzb : mantOf (b i) = 0
    · simp [sv_zero (b i) hzb]
    have hia := ha i (by omega) (by omega) hza
    have hib := hb i (by omega) (by omega) hzb
    have hexp : idxOf (a i) - baseA + (idxOf (b i) - baseB) + (baseA + baseB) =
        idxOf (a i) + idxOf (b i) := by omega
    rw [mul_assoc, ← pow_add, hexp]

theorem prepared_body_scaled (n : Nat) (a b : Nat → UInt32) (baseA baseB : Nat)
    (ha : ∀ j, j < n → mantOf (a j) * 2 ^ (idxOf (a j) - baseA) < 2147483648)
    (hb : ∀ j, j < n → mantOf (b j) * 2 ^ (idxOf (b j) - baseB) < 2147483648)
    (hla : ∀ j, j < n → mantOf (a j) ≠ 0 → baseA ≤ idxOf (a j))
    (hlb : ∀ j, j < n → mantOf (b j) ≠ 0 → baseB ≤ idxOf (b j)) :
    exactTerms (fun j => prepareFactor (a j) baseA) (fun j => prepareFactor (b j) baseB) n 0 *
      2 ^ (baseA + baseB) = dsum (rawWords n a) (rawWords n b) 0 n := by
  rw [actual_getters_exact a b baseA baseB n 0 (fun j _ hj => ha j (by omega))
      (fun j _ hj => hb j (by omega)),
    alignedTerms_scale a b baseA baseB n 0 (fun j _ hj hn => hla j (by omega) hn)
      (fun j _ hj hn => hlb j (by omega) hn),
    rawSum_dsum n a b n 0 (by omega)]

def scaledBias (word : UInt32) (base : Nat) : Int :=
  sv word * 2 ^ (idxOf word + 149 - base)

theorem scaledBias_exact (word : UInt32) (base : Nat) (h : base ≤ idxOf word + 149) :
    scaledBias word base * 2 ^ base = sv word * 2 ^ (idxOf word + 149) := by
  unfold scaledBias
  rw [mul_assoc, ← pow_add]
  congr 2
  omega

theorem finish_prepared_scaled (n : Nat) (a b : Nat → UInt32) (baseA baseB : Nat)
    (hn : n ≤ 1048576) (biasWord : UInt32) (nz : Bool)
    (ha : ∀ j, j < n → mantOf (a j) * 2 ^ (idxOf (a j) - baseA) < 2147483648)
    (hb : ∀ j, j < n → mantOf (b j) * 2 ^ (idxOf (b j) - baseB) < 2147483648)
    (hla : ∀ j, j < n → mantOf (a j) ≠ 0 → baseA ≤ idxOf (a j))
    (hlb : ∀ j, j < n → mantOf (b j) ≠ 0 → baseB ≤ idxOf (b j))
    (hbi : baseA + baseB ≤ idxOf biasWord + 149) :
    preparedFinish n (fun j => prepareFactor (a j) baseA) (fun j => prepareFactor (b j) baseB)
      (scaledBias biasWord (baseA + baseB)) (-298 + ((baseA + baseB : Nat) : Int)) nz =
      finishWord (dsum (rawWords n a) (rawWords n b) 0 n +
        sv biasWord * 2 ^ (idxOf biasWord + 149)) (-298) nz := by
  rw [preparedFinish_exact _ _ _ hn, finishWord_scale, add_mul,
    prepared_body_scaled n a b baseA baseB ha hb hla hlb,
    scaledBias_exact biasWord (baseA + baseB) hbi]

end Submission.R26WordBlock
