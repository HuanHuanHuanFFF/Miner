theorem groupFrom_eq_original (n baseA baseB p : Nat) (A B : Array Binary32)
    (out : Array Binary32) (g : Fin (groups p)) :
    groupFrom n baseA baseB p A B out g =
      groupFromOriginal n baseA baseB p A B out g := by
  have hg : 2 * g.val < p := by
    have h := g.isLt
    unfold groups at h
    omega
  by_cases h : min 2 (p - 2 * g.val) = 1
  · simp only [groupFrom, h, if_pos]
  · have hc : min 2 (p - 2 * g.val) = 2 := by omega
    simp only [groupFrom, groupFromOriginal, h, ite_false]
    rw [loopEmit_eq]
    have emit_two (count : Nat) (hcount : count=2) (read : Fin count → Binary32) :
        RowStream.emit count read out =
          (out.push (read ⟨0,by omega⟩)).push (read ⟨1,by omega⟩) := by
      subst count
      unfold RowStream.emit
      rw [Fin.foldl_succ, Fin.foldl_succ, Fin.foldl_zero] <;> rfl
    exact (emit_two (min 2 (p - 2 * g.val)) hc
      (fun l => Packed10.finish n baseA ((baseB + 2 * g.val) + l.val) p A B
        (select (loop n baseA (baseB + 2 * g.val) p A B
          0 Packed10.zero32 Packed10.zero32) l.val))).symm

