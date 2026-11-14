/- R22 proof interface for batch-local row blocks. NOT_RUN.
   A concrete runtime must discharge hread/hblock/hrow; this is not that runtime's proof. -/
namespace Submission.R22BlockWriter
open FloatLib.Floats Competition

def emitRows (rows p : Nat) (read : Fin rows → Fin p → Binary32)
    (out : Array Binary32) : Array Binary32 :=
  Fin.foldl rows (fun acc i => RowStream.emit p (read i) acc) out

theorem emitRows_four (p : Nat) (read : Fin 4 → Fin p → Binary32) (out : Array Binary32) :
    emitRows 4 p read out =
      RowStream.emit p (read 3) (RowStream.emit p (read 2)
        (RowStream.emit p (read 1) (RowStream.emit p (read 0) out))) := by
  unfold emitRows
  rw [Fin.foldl_succ, Fin.foldl_succ, Fin.foldl_succ, Fin.foldl_succ, Fin.foldl_zero] <;> rfl

theorem emitRows_prefix (f : Nat → Binary32) (start rows p : Nat)
    (read : Fin rows → Fin p → Binary32) (out : Array Binary32)
    (hout : RowStream.Prefix f start out)
    (hread : ∀ i j, read i j = f (start + i.val * p + j.val)) :
    RowStream.Prefix f (start + rows * p) (emitRows rows p read out) := by
  unfold emitRows
  exact RowStream.foldl_inv (β := Array Binary32) rows
    (fun acc i => RowStream.emit p (read i) acc)
    (fun i acc => RowStream.Prefix f (start + i * p) acc)
    (by
      intro i acc hacc
      have h := RowStream.emit_prefix f (start + i.val * p) p (read i) acc hacc (hread i)
      simpa only [Nat.add_mul, Nat.one_mul, Nat.add_assoc] using h)
    out (by simpa only [Nat.zero_mul, Nat.add_zero] using hout)

theorem block_row_valid (width m : Nat) (g : Fin (m / width)) (lane : Fin width) :
    width * g.val + lane.val < m := by
  have hg0 := g.isLt
  have hlane := lane.isLt
  have hg : g.val + 1 ≤ m / width := by omega
  have hmul := Nat.mul_le_mul_left width hg
  have hdiv := Nat.div_add_mod m width
  simp only [Nat.mul_add, Nat.mul_one] at hmul
  omega

theorem tail_row_valid (width m : Nat) (lane : Fin (m % width)) :
    width * (m / width) + lane.val < m := by
  have hlane := lane.isLt
  have hdiv := Nat.div_add_mod m width
  omega

theorem four_tail_bound (m : Nat) : m % 4 ≤ 3 := by
  have h := Nat.mod_lt m (by decide : 0 < 4)
  omega

theorem emitRows_point_prefix (batch m n p offset rows : Nat)
    (A : Vector Binary32 (batch * m * n)) (B : Vector Binary32 (batch * n * p))
    (bi : Fin batch) (hrows : offset + rows ≤ m)
    (read : Fin rows → Fin p → Binary32) (out : Array Binary32)
    (hout : RowStream.Prefix (RowStream.point batch m n p A B) ((bi.val * m + offset) * p) out)
    (hread : ∀ lane j, read lane j = NativeFinal.dot n
      ((bi.val * m + offset + lane.val) * n) (bi.val * n * p + j.val) p A.toArray B.toArray) :
    RowStream.Prefix (RowStream.point batch m n p A B) ((bi.val * m + offset + rows) * p)
      (emitRows rows p read out) := by
  have h := emitRows_prefix (RowStream.point batch m n p A B)
    ((bi.val * m + offset) * p) rows p read out hout (by
      intro lane j
      rw [hread lane j]
      have hlane := lane.isLt
      have hi : offset + lane.val < m := by omega
      have hm : 0 < m := by omega
      have hp : 0 < p := Nat.zero_lt_of_lt j.isLt
      have hq : (bi.val * m + offset + lane.val) / m = bi.val := by
        rw [Nat.add_assoc, Nat.mul_comm bi.val m, Nat.mul_add_div hm,
          Nat.div_eq_of_lt hi, Nat.add_zero]
      have hpoint := RowStream.point_row batch m n p A B
        (bi.val * m + offset + lane.val) j.val hm hp j.isLt
      rw [hq] at hpoint
      simpa only [Nat.add_mul, Nat.add_assoc] using hpoint.symm)
  simpa only [Nat.add_mul, Nat.add_assoc] using h

theorem blocks_tail_prefix (f : Nat → Binary32) (start width m p : Nat)
    (blockStep : Array Binary32 → Fin (m / width) → Array Binary32)
    (rowStep : Array Binary32 → Fin (m % width) → Array Binary32)
    (hblock : ∀ (g : Fin (m / width)) (acc : Array Binary32),
      RowStream.Prefix f (start + width * g.val * p) acc →
      RowStream.Prefix f (start + width * (g.val + 1) * p) (blockStep acc g))
    (hrow : ∀ (i : Fin (m % width)) (acc : Array Binary32),
      RowStream.Prefix f (start + (width * (m / width) + i.val) * p) acc →
      RowStream.Prefix f (start + (width * (m / width) + i.val + 1) * p) (rowStep acc i))
    (out : Array Binary32) (hout : RowStream.Prefix f start out) :
    RowStream.Prefix f (start + m * p)
      (Fin.foldl (m % width) rowStep (Fin.foldl (m / width) blockStep out)) := by
  have hblocks := RowStream.foldl_inv (β := Array Binary32) (m / width) blockStep
    (fun g acc => RowStream.Prefix f (start + width * g * p) acc) hblock
    out (by simpa only [Nat.mul_zero, Nat.zero_mul, Nat.add_zero] using hout)
  have htail := RowStream.foldl_inv (β := Array Binary32) (m % width) rowStep
    (fun i acc => RowStream.Prefix f (start + (width * (m / width) + i) * p) acc)
    (by
      intro i acc hacc
      simpa only [Nat.add_assoc] using hrow i acc hacc)
    (Fin.foldl (m / width) blockStep out)
    (by simpa only [Nat.add_zero] using hblocks)
  have hdiv : width * (m / width) + m % width = m := Nat.div_add_mod m width
  simpa only [hdiv] using htail

theorem batch_fold_prefix (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n)) (B : Vector Binary32 (batch * n * p))
    (step : Array Binary32 → Fin batch → Array Binary32)
    (hstep : ∀ (bi : Fin batch) (acc : Array Binary32),
      RowStream.Prefix (RowStream.point batch m n p A B) (bi.val * m * p) acc →
      RowStream.Prefix (RowStream.point batch m n p A B) ((bi.val + 1) * m * p) (step acc bi)) :
    RowStream.Prefix (RowStream.point batch m n p A B) (batch * m * p)
      (Fin.foldl batch step (Array.mkEmpty (batch * m * p))) := by
  exact RowStream.foldl_inv (β := Array Binary32) batch step
    (fun bi acc => RowStream.Prefix (RowStream.point batch m n p A B) (bi * m * p) acc)
    hstep (Array.mkEmpty (batch * m * p))
    ⟨by simp, by intro j hj; simp at hj⟩

end Submission.R22BlockWriter
