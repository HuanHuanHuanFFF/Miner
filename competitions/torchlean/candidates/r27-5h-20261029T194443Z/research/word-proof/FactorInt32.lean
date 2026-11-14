import ContractExact

namespace Submission.R27Factor

def value (w : UInt32) (base : Nat) : Int :=
  ExactRuntime.sv w * 2 ^ (ExactRuntime.idxOf w - base)

def valid (w : UInt32) (base : Nat) : Bool :=
  decide (ExactRuntime.expOf w ≠ 255 ∧
    (ExactRuntime.mantOf w = 0 ∨ base ≤ ExactRuntime.idxOf w) ∧
    -2147483648 ≤ value w base ∧ value w base < 2147483648)

@[inline] def factor (w : UInt32) (base : Nat) : UInt32 :=
  (Int32.ofInt (value w base)).toUInt32

theorem valid_sound (w : UInt32) (base : Nat) (h : valid w base = true) :
    ExactRuntime.expOf w ≠ 255 ∧
    (ExactRuntime.mantOf w = 0 ∨ base ≤ ExactRuntime.idxOf w) ∧
    -2147483648 ≤ value w base ∧ value w base < 2147483648 := by
  exact of_decide_eq_true h

theorem factor_exact (w : UInt32) (base : Nat) (h : valid w base = true) :
    (factor w base).toInt32.toInt = value w base := by
  obtain ⟨_, _, hlo, hhi⟩ := valid_sound w base h
  unfold factor
  rw [Int32.toInt32_toUInt32]
  exact Int32.toInt_ofInt_of_le hlo hhi

@[specialize] def allValid (f : Nat → UInt32) (base : Nat) : Nat → Nat → Bool
  | 0, _ => true
  | fuel + 1, i => valid (f i) base && allValid f base fuel (i + 1)

theorem allValid_sound (f : Nat → UInt32) (base fuel i : Nat)
    (h : allValid f base fuel i = true) (j : Nat) (hlo : i ≤ j) (hhi : j < i + fuel) :
    valid (f j) base = true := by
  induction fuel generalizing i with
  | zero => omega
  | succ fuel ih =>
    simp only [allValid, Bool.and_eq_true] at h
    by_cases hj : j = i
    · simpa only [hj] using h.1
    · exact ih (i + 1) h.2 (by omega) (by omega)

def prepared (n : Nat) (f : Nat → UInt32) (base : Nat) : Array UInt32 :=
  Array.ofFn (n := n) fun i => factor (f i.val) base

theorem prepared_get (n : Nat) (f : Nat → UInt32) (base j : Nat) (hj : j < n) :
    (prepared n f base)[j]! = factor (f j) base := by
  rw [getElem!_pos _ j (by simpa [prepared] using hj)]
  simp [prepared]

theorem prepared_get_exact (n : Nat) (f : Nat → UInt32) (base j : Nat)
    (h : allValid f base n 0 = true) (hj : j < n) :
    ((prepared n f base)[j]!).toInt32.toInt = value (f j) base := by
  rw [prepared_get n f base j hj]
  exact factor_exact (f j) base (allValid_sound f base n 0 h j (by omega) (by omega))

end Submission.R27Factor
