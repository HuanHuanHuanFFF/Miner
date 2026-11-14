namespace Submission.R26WordBlock
open ExactRuntime

@[specialize] def zeroSafeFinish (guard : Bool) (n : Nat) (a b : Nat → UInt32)
    (bias exponent : Int) (shipped : Unit → UInt32) : UInt32 :=
  if guard then
    let pair := preparedBody n a b
    let total := signed128 pair.1 pair.2 + bias
    if total = 0 then shipped () else finishWord total exponent false
  else shipped ()

theorem zeroSafeFinish_false (n : Nat) (a b : Nat → UInt32)
    (bias exponent : Int) (shipped : Unit → UInt32) :
    zeroSafeFinish false n a b bias exponent shipped = shipped () := rfl

theorem zeroSafeFinish_zero (n : Nat) (a b : Nat → UInt32)
    (bias exponent : Int) (shipped : Unit → UInt32)
    (hz : signed128 (preparedBody n a b).1 (preparedBody n a b).2 + bias = 0) :
    zeroSafeFinish true n a b bias exponent shipped = shipped () := by
  simp [zeroSafeFinish, hz]

theorem finishWord_flag_irrelevant (T e : Int) (nz : Bool) (h : T ≠ 0) :
    finishWord T e false = finishWord T e nz := by
  simp [finishWord, h]

theorem zeroSafeFinish_of_prepared (guard : Bool) (n : Nat) (a b : Nat → UInt32)
    (bias exponent : Int) (nz : Bool) (shipped : Unit → UInt32) (wanted : UInt32)
    (hship : shipped () = wanted)
    (hfast : guard = true → preparedFinish n a b bias exponent nz = wanted) :
    zeroSafeFinish guard n a b bias exponent shipped = wanted := by
  cases guard
  · exact hship
  · unfold zeroSafeFinish
    simp only [Bool.true_eq_true, ite_true]
    split_ifs with hz
    · exact hship
    · rw [finishWord_flag_irrelevant _ _ nz hz]
      exact hfast rfl

theorem zeroSafeFinish_bias_dot (n : Nat) (a b : Nat → UInt32) (baseA baseB : Nat)
    (hn : n ≤ 1048576) (bias : UInt32) (shipped : Unit → UInt32)
    (hship : shipped () = dotOf (n + 1) (biasedA n a) (biasedB n b bias))
    (ha : ∀ j, j < n → mantOf (a j) * 2 ^ (idxOf (a j) - baseA) < 2147483648)
    (hb : ∀ j, j < n → mantOf (b j) * 2 ^ (idxOf (b j) - baseB) < 2147483648)
    (hla : ∀ j, j < n → mantOf (a j) ≠ 0 → baseA ≤ idxOf (a j))
    (hlb : ∀ j, j < n → mantOf (b j) ≠ 0 → baseB ≤ idxOf (b j))
    (hbi : baseA + baseB ≤ idxOf bias + 149)
    (hfinite : ∀ j, j < n → expOf (a j) ≠ 255 ∧ expOf (b j) ≠ 255)
    (hfb : expOf bias ≠ 255) :
    zeroSafeFinish true n (fun j => prepareFactor (a j) baseA) (fun j => prepareFactor (b j) baseB)
      (scaledBias bias (baseA + baseB)) (-298 + ((baseA + baseB : Nat) : Int)) shipped =
      dotOf (n + 1) (biasedA n a) (biasedB n b bias) := by
  apply zeroSafeFinish_of_prepared _ _ _ _ _ _
    (dallNZ (rawWords (n + 1) (biasedA n a)) (rawWords (n + 1) (biasedB n b bias)) 0 (n + 1))
    _ _ hship
  intro _
  exact finish_prepared_bias_dot n a b baseA baseB hn bias _ ha hb hla hlb hbi hfinite hfb rfl

end Submission.R26WordBlock
