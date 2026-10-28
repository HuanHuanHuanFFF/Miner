/- Requires Nat8WordProjection5277ada5 (and accepted795 projection).
   NOT_RUN. Address/field/encoded-word facts only, no floating arithmetic. -/
namespace Submission.R22Resident8Projection
open FloatLib.Floats Competition

theorem column_parts (p : Nat) (j : Fin p) :
    j.val / 2 < R22Pair8.groups p ∧ j.val % 2 < 2 ∧
    2 * (j.val / 2) + j.val % 2 = j.val ∧
    (j.val % 2 = 1 → 2 * (j.val / 2) + 1 < p) := by
  have hj := j.isLt
  have hm := Nat.mod_lt j.val (show 0 < 2 by decide)
  have hd := Nat.mod_add_div j.val 2
  unfold R22Pair8.groups
  omega

def readRow {p : Nat} (t : Vector R22Resident8.Words (R22Pair8.groups p))
    (r : Fin 4) (j : Fin p) : Binary32 :=
  match r.val with
  | 0 => R22Resident8.read0 t j
  | 1 => R22Resident8.read1 t j
  | 2 => R22Resident8.read2 t j
  | _ => R22Resident8.read3 t j

theorem readRow_word {p : Nat} (t : Vector R22Resident8.Words (R22Pair8.groups p))
    (r : Fin 4) (j : Fin p) :
    readRow t r j = FastMul.ofBits
      (selectWords (R22Resident8.getTile t j) r ⟨j.val % 2, (column_parts p j).2.1⟩) := by
  rcases r with ⟨r, hr⟩
  have hs : r = 0 ∨ r = 1 ∨ r = 2 ∨ r = 3 := by omega
  rcases hs with rfl | rfl | rfl | rfl <;> rfl

theorem rawWord_reconstruct (value : Binary32) : FastMul.ofBits value.raw.1 = value := by
  apply FloatLib.Floats.ExecFloat.ext
  apply Subtype.ext
  rfl

end Submission.R22Resident8Projection
