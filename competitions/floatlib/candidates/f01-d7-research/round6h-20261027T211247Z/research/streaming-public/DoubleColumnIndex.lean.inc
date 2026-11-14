/- Minimal proof interface for G=ceil(p/2) cells carrying 4 rows x 2 columns.
   No concrete F8 runtime or prepared-B layout is defined here. NOT_RUN. -/
namespace Submission.R22DoubleColumnIndex
open FloatLib.Floats Competition

theorem group_lt (p : Nat) (j : Fin p) : j.val / 2 < R15ThinPairs.groups p := by
  have hj := j.isLt
  unfold R15ThinPairs.groups
  omega

theorem lane_lt (j : Nat) : j % 2 < 2 := Nat.mod_lt j (by decide)

theorem column_recompose (j : Nat) : 2 * (j / 2) + j % 2 = j :=
  Nat.div_add_mod j 2

theorem first_column_lt (p : Nat) (g : Fin (R15ThinPairs.groups p)) : 2 * g.val < p := by
  have hg := g.isLt
  unfold R15ThinPairs.groups at hg
  omega

theorem padding_column (p : Nat) (g : Fin (R15ThinPairs.groups p))
    (h : ¬2 * g.val + 1 < p) : 2 * g.val + 1 = p ∧ p % 2 = 1 := by
  have hg := g.isLt
  unfold R15ThinPairs.groups at hg
  omega

theorem selected_field_step {Cell : Type} (p baseB k : Nat) (a : Float32)
    (Braw : Array Binary32) (s next : Vector Cell (R15ThinPairs.groups p))
    (read : Cell → Fin 4 → Fin 2 → Float32) (row : Fin 4)
    (hfield : ∀ (g : Fin (R15ThinPairs.groups p)) (col : Fin 2),
      2 * g.val + col.val < p →
      read (next.get g) row col = read (s.get g) row col + a *
        ExecFloat.Binary.toFloat32 (Braw.getD (baseB + (2 * g.val + col.val) + k * p) posZero))
    (j : Fin p) :
    read (next.get ⟨j.val / 2, group_lt p j⟩) row ⟨j.val % 2, lane_lt j.val⟩ =
      read (s.get ⟨j.val / 2, group_lt p j⟩) row ⟨j.val % 2, lane_lt j.val⟩ + a *
        ExecFloat.Binary.toFloat32 (Braw.getD (baseB + j.val + k * p) posZero) := by
  have hj : 2 * (j.val / 2) + j.val % 2 < p := by
    simpa only [column_recompose] using j.isLt
  have h := hfield ⟨j.val / 2, group_lt p j⟩ ⟨j.val % 2, lane_lt j.val⟩ hj
  simpa only [column_recompose] using h

end Submission.R22DoubleColumnIndex
