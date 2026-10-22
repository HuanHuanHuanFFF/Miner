/- NOT_RUN -/
namespace DDotNonNaNScan

open FloatLib.Floats Competition
open FloatLib.Floats.Formats.BinaryInterchange

/- NOT_RUN -/
def loop (n baseA baseB p : Nat) (A B : Array Binary32) (k : Nat) : Bool :=
  if hk : k < n then
    if DWordNaN.rawNaN (A.getD (baseA + k) posZero).raw.1 = true then false
    else if DWordNaN.rawNaN (B.getD (baseB + k * p) posZero).raw.1 = true then false
    else loop n baseA baseB p A B (k + 1)
  else true
termination_by n - k
decreasing_by omega

/- NOT_RUN -/
theorem loop_true_iff (n baseA baseB p : Nat) (A B : Array Binary32) (k : Nat) :
    loop n baseA baseB p A B k = true ↔
      ∀ i : Nat, k ≤ i → i < n →
        DWordNaN.rawNaN (A.getD (baseA + i) posZero).raw.1 = false ∧
        DWordNaN.rawNaN (B.getD (baseB + i * p) posZero).raw.1 = false := by
  rw [loop]
  split
  · rename_i hk
    split
    · rename_i ha
      constructor
      · intro h
        cases h
      · intro h
        have e := (h k (Nat.le_refl k) hk).1
        rw [ha] at e
        cases e
    · rename_i ha
      split
      · rename_i hb
        constructor
        · intro h
          cases h
        · intro h
          have e := (h k (Nat.le_refl k) hk).2
          rw [hb] at e
          cases e
      · rename_i hb
        have haf : DWordNaN.rawNaN (A.getD (baseA + k) posZero).raw.1 = false := by
          cases h : DWordNaN.rawNaN (A.getD (baseA + k) posZero).raw.1 <;> simp_all
        have hbf : DWordNaN.rawNaN (B.getD (baseB + k * p) posZero).raw.1 = false := by
          cases h : DWordNaN.rawNaN (B.getD (baseB + k * p) posZero).raw.1 <;> simp_all
        rw [loop_true_iff n baseA baseB p A B (k + 1)]
        constructor
        · intro h i hki hin
          by_cases hi : i = k
          · subst i
            exact ⟨haf, hbf⟩
          · exact h i (by omega) hin
        · intro h i hki hin
          exact h i (by omega) hin
  · rename_i hk
    constructor
    · intro _ i hki hin
      omega
    · intro _
      rfl
termination_by n - k
decreasing_by omega

/- NOT_RUN -/
@[inline] def whole (n baseA baseB p : Nat) (A B : Array Binary32) : Bool :=
  loop n baseA baseB p A B 0

/- NOT_RUN -/
theorem whole_true_iff (n baseA baseB p : Nat) (A B : Array Binary32) :
    whole n baseA baseB p A B = true ↔
      ∀ k : Fin n,
        DWordNaN.rawNaN (A.getD (baseA + k.val) posZero).raw.1 = false ∧
        DWordNaN.rawNaN (B.getD (baseB + k.val * p) posZero).raw.1 = false := by
  unfold whole
  rw [loop_true_iff]
  constructor
  · intro h k
    exact h k.val (Nat.zero_le _) k.isLt
  · intro h i _ hin
    exact h ⟨i, hin⟩

/- NOT_RUN -/
theorem whole_raw_nonNaN (n baseA baseB p : Nat) (A B : Array Binary32)
    (h : whole n baseA baseB p A B = true) :
    ∀ k : Fin n,
      DWordNaN.rawNaN (A.getD (baseA + k.val) posZero).raw.1 = false ∧
      DWordNaN.rawNaN (B.getD (baseB + k.val * p) posZero).raw.1 = false :=
  (whole_true_iff n baseA baseB p A B).mp h

/- NOT_RUN -/
theorem whole_model_nonNaN (n baseA baseB p : Nat) (A B : Array Binary32)
    (h : whole n baseA baseB p A B = true) :
    ∀ k : Fin n,
      Model.isNaN (Model.NativeBinary32.ofUInt32
        (A.getD (baseA + k.val) posZero).raw.1) = false ∧
      Model.isNaN (Model.NativeBinary32.ofUInt32
        (B.getD (baseB + k.val * p) posZero).raw.1) = false := by
  intro k
  obtain ⟨ha, hb⟩ := whole_raw_nonNaN n baseA baseB p A B h k
  exact ⟨(DWordNaN.rawNaN_eq _).symm.trans ha,
    (DWordNaN.rawNaN_eq _).symm.trans hb⟩

end DDotNonNaNScan
