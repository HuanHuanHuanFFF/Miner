/- Requires Nat8ReadProjectiona8cf1655 and Nat8FinishLane1cde7134.
   NOT_RUN. Conditional pointwise bridge, not a whole public BMM theorem. -/
namespace Submission.R22Resident8Projection
open FloatLib.Floats Competition

theorem readRow_eq_dot (p n baseA baseB baseC : Nat) (A B : Array Binary32)
    (cache : Array BP) (r : Fin 4) (j : Fin p)
    (hread : ∀ i : Fin n,
      R15ThinPairs.select
        ((cacheView n p (baseC + j.val / 2) cache).get i) (j.val % 2) =
      ExecFloat.Binary.toFloat32 (B.getD (baseB + j.val + i.val * p) posZero)) :
    readRow (R22Resident8.tiles p n baseA baseB baseC A B cache) r j =
      NativeFinal.dot n (baseA + r.val * n) (baseB + j.val) p A B := by
  have parts := column_parts p j
  let g : Fin (R22Pair8.groups p) := ⟨j.val / 2, parts.1⟩
  let c : Fin 2 := ⟨j.val % 2, parts.2.1⟩
  have hj : 2 * g.val + c.val = j.val := parts.2.2.1
  have haddr : baseB + 2 * g.val + c.val = baseB + j.val := by omega
  have hright : c.val = 1 → decide (2 * g.val + 1 < p) = true := by
    intro hc
    rw [decide_eq_true_eq]
    exact parts.2.2.2 hc
  have hread' : ∀ i : Fin n,
      R15ThinPairs.select ((cacheView n p (baseC + g.val) cache).get i) c.val =
        ExecFloat.Binary.toFloat32
          (B.getD (baseB + 2 * g.val + c.val + i.val * p) posZero) := by
    intro i
    simpa only [haddr] using hread i
  rw [readRow_word]
  change FastMul.ofBits (selectWords
    ((R22Resident8.tiles p n baseA baseB baseC A B cache).get g) r c) = _
  simp only [R22Resident8.tiles, Packed10.vector_get_ofFn]
  rw [tile_word p n baseA (baseB + 2 * g.val) (baseC + g.val) A B cache _ r c hright]
  rw [finish_lane n p baseA (baseB + 2 * g.val) (baseC + g.val) A B cache r c hread']
  rw [rawWord_reconstruct, haddr]

end Submission.R22Resident8Projection
