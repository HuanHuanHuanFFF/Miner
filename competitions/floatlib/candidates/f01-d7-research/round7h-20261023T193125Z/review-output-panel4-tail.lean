/- NOT_RUN proof/implementation asset, not a new Kernel or an active entry.
Requires the retained Packed10/Packed10Index/RowStream interfaces of749b.
All appearances of a global native map below are in proofs, not tail runtime. -/
namespace Submission.Panel4Tail
open FloatLib.Floats Competition

/-- At most three rows in the intended caller; total reads retain +0 defaults. -/
def prepare (rows n rawBase : Nat) (Araw : Array Binary32) : Array Float32 :=
  Array.ofFn fun q : Fin (rows * n) =>
    ExecFloat.Binary.toFloat32 (Araw.getD (rawBase + q.val) posZero)

theorem prepare_getD (rows n rawBase : Nat) (Araw : Array Binary32)
    (i : Nat) (hi : i < rows * n) :
    (prepare rows n rawBase Araw).getD i Packed10.zero32 =
      ExecFloat.Binary.toFloat32 (Araw.getD (rawBase + i) posZero) := by
  simp [prepare, Array.getD, hi, Array.size_ofFn, Array.getElem_ofFn]

theorem prepare_read (rows n rawBase : Nat) (Araw : Array Binary32)
    (r : Fin rows) (k : Fin n) :
    (prepare rows n rawBase Araw).getD (r.val * n + k.val) Packed10.zero32 =
      (Araw.map ExecFloat.Binary.toFloat32).getD (rawBase + r.val * n + k.val) Packed10.zero32 := by
  have hs := Nat.mul_le_mul_right n r.isLt
  rw [Nat.succ_mul] at hs
  have hi : r.val * n + k.val < rows * n := by have hk := k.isLt; omega
  rw [prepare_getD rows n rawBase Araw _ hi, Packed10.nativeA_getD]
  simp only [Nat.add_assoc]

/-- Only equality of the actually read A words is needed. No FP reassociation. -/
theorem dot10_shift (n localBase rawBase : Nat) (tailA source : Array Float32)
    (B : Vector Packed10.F10 n)
    (hread : ∀ i : Fin n, tailA.getD (localBase + i.val) Packed10.zero32 =
      source.getD (rawBase + i.val) Packed10.zero32)
    (k : Nat) (s0 s1 s2 s3 s4 s5 s6 s7 s8 s9 : Float32) :
    Packed10.dot10 n localBase tailA B k s0 s1 s2 s3 s4 s5 s6 s7 s8 s9 =
      Packed10.dot10 n rawBase source B k s0 s1 s2 s3 s4 s5 s6 s7 s8 s9 := by
  by_cases hk : k < n
  · conv_lhs => rw [Packed10.dot10]
    conv_rhs => rw [Packed10.dot10]
    simp only [dif_pos hk]
    dsimp only
    rw [hread ⟨k, hk⟩]
    exact dot10_shift n localBase rawBase tailA source B hread (k + 1)
      _ _ _ _ _ _ _ _ _ _
  · conv_lhs => rw [Packed10.dot10]
    conv_rhs => rw [Packed10.dot10]
    simp only [dif_neg hk]
termination_by n - k
decreasing_by omega

theorem runDot_shift (n localBase rawBase : Nat) (tailA source : Array Float32)
    (B : Vector Packed10.F10 n)
    (hread : ∀ i : Fin n, tailA.getD (localBase + i.val) Packed10.zero32 =
      source.getD (rawBase + i.val) Packed10.zero32) :
    Packed10Index.runDot n localBase tailA B = Packed10Index.runDot n rawBase source B := by
  rw [Packed10Index.runDot_eq, Packed10Index.runDot_eq]
  exact dot10_shift n localBase rawBase tailA source B hread 0 _ _ _ _ _ _ _ _ _ _

theorem runDot_prepared (rows n rawBase : Nat) (Araw : Array Binary32)
    (r : Fin rows) (B : Vector Packed10.F10 n) :
    Packed10Index.runDot n (r.val * n) (prepare rows n rawBase Araw) B =
      Packed10Index.runDot n (rawBase + r.val * n) (Araw.map ExecFloat.Binary.toFloat32) B := by
  apply runDot_shift
  intro k
  exact prepare_read rows n rawBase Araw r k

/-- Local numeric base and original raw finish base are deliberately separate. -/
@[inline] def group (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n)) (B : Vector Binary32 (batch * n * p))
    (tailA : Array Float32)
    (packedB : Vector (Vector (Vector Packed10.F10 n) (Packed10.groups p)) batch)
    (b : Fin batch) (first : Nat) (r : Fin (m - first))
    (out : Array Binary32) (g : Fin (Packed10.groups p)) : Array Binary32 :=
  let result := Packed10Index.runDot n (r.val * n) tailA ((packedB.get b).get g)
  let count := min 10 (p - 10 * g.val)
  RowStream.emit count (fun l =>
    let j := 10 * g.val + l.val
    Packed10.finish n ((b.val * m + first + r.val) * n) (b.val * n * p + j)
      p A.toArray B.toArray
      (Packed10.lane result ⟨l.val, Nat.lt_of_lt_of_le l.isLt (Nat.min_le_left _ _)⟩)) out

theorem group_prefix (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n)) (B : Vector Binary32 (batch * n * p))
    (b : Fin batch) (first : Nat) (r : Fin (m - first))
    (out : Array Binary32) (g : Fin (Packed10.groups p))
    (hout : RowStream.Prefix (RowStream.point batch m n p A B)
      ((b.val * m + first + r.val) * p + min (10 * g.val) p) out) :
    RowStream.Prefix (RowStream.point batch m n p A B)
      ((b.val * m + first + r.val) * p + min (10 * (g.val + 1)) p)
      (group batch m n p A B (prepare (m - first) n ((b.val * m + first) * n) A.toArray)
        (Packed10.packB batch n p B) b first r out g) := by
  have hr := r.isLt
  have hrow : first + r.val < m := by omega
  have hm : 0 < m := by omega
  have hg : 10 * g.val < p := by have hh := g.isLt; unfold Packed10.groups at hh; omega
  have hp : 0 < p := by omega
  have hdiv : (b.val * m + first + r.val) / m = b.val := by
    rw [show b.val * m + first + r.val = b.val * m + (first + r.val) by omega,
      Nat.mul_comm b.val m, Nat.mul_add_div hm, Nat.div_eq_of_lt hrow, Nat.add_zero]
  have hstart : min (10 * g.val) p = 10 * g.val := by omega
  have hend : (b.val * m + first + r.val) * p + min (10 * (g.val + 1)) p =
      ((b.val * m + first + r.val) * p + 10 * g.val) + min 10 (p - 10 * g.val) := by omega
  rw [hend]
  unfold group
  dsimp only
  apply RowStream.emit_prefix
  · simpa only [hstart] using hout
  · intro l
    have hcol : 10 * g.val + l.val < p := by have hl := l.isLt; omega
    rw [show (b.val * m + first + r.val) * p + 10 * g.val + l.val =
        (b.val * m + first + r.val) * p + (10 * g.val + l.val) by omega,
      RowStream.point_row batch m n p A B (b.val * m + first + r.val)
        (10 * g.val + l.val) hm hp hcol, hdiv,
      runDot_prepared]
    rw [show (b.val * m + first) * n + r.val * n = (b.val * m + first + r.val) * n
        by rw [Nat.add_mul], Packed10Index.runDot_eq]
    apply Packed10.finish_dot10_lane
    intro k
    rw [Packed10.packB_lane batch n p B b g k
      ⟨l.val, Nat.lt_of_lt_of_le l.isLt (Nat.min_le_left _ _)⟩ hcol]
    rw [index_address (b.val * n) k.val p (10 * g.val + l.val)]

@[inline] def row (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n)) (B : Vector Binary32 (batch * n * p))
    (tailA : Array Float32)
    (packedB : Vector (Vector (Vector Packed10.F10 n) (Packed10.groups p)) batch)
    (b : Fin batch) (first : Nat) (out : Array Binary32) (r : Fin (m - first)) : Array Binary32 :=
  Fin.foldl (Packed10.groups p) (group batch m n p A B tailA packedB b first r) out

theorem row_prefix (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n)) (B : Vector Binary32 (batch * n * p))
    (b : Fin batch) (first : Nat) (out : Array Binary32) (r : Fin (m - first))
    (hout : RowStream.Prefix (RowStream.point batch m n p A B)
      ((b.val * m + first + r.val) * p) out) :
    RowStream.Prefix (RowStream.point batch m n p A B)
      ((b.val * m + first + r.val + 1) * p)
      (row batch m n p A B (prepare (m - first) n ((b.val * m + first) * n) A.toArray)
        (Packed10.packB batch n p B) b first out r) := by
  have hlast : min (10 * Packed10.groups p) p = p := by unfold Packed10.groups; omega
  have h := RowStream.foldl_inv (Packed10.groups p)
    (group batch m n p A B (prepare (m - first) n ((b.val * m + first) * n) A.toArray)
      (Packed10.packB batch n p B) b first r)
    (fun g acc => RowStream.Prefix (RowStream.point batch m n p A B)
      ((b.val * m + first + r.val) * p + min (10 * g) p) acc)
    (fun g acc hacc => group_prefix batch m n p A B b first r acc g hacc) out
    (by simpa only [Nat.mul_zero, Nat.zero_min, Nat.add_zero] using hout)
  simpa only [row, hlast, Nat.add_mul, Nat.one_mul] using h

/-- The local tail array is prepared once, before any tail row or column group. -/
def tail (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n)) (B : Vector Binary32 (batch * n * p))
    (packedB : Vector (Vector (Vector Packed10.F10 n) (Packed10.groups p)) batch)
    (b : Fin batch) (first : Nat) (out : Array Binary32) : Array Binary32 :=
  let tailA := prepare (m - first) n ((b.val * m + first) * n) A.toArray
  Fin.foldl (m - first) (row batch m n p A B tailA packedB b first) out

theorem tail_prefix (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n)) (B : Vector Binary32 (batch * n * p))
    (b : Fin batch) (first : Nat) (hfirst : first ≤ m) (out : Array Binary32)
    (hout : RowStream.Prefix (RowStream.point batch m n p A B) ((b.val * m + first) * p) out) :
    RowStream.Prefix (RowStream.point batch m n p A B) ((b.val + 1) * m * p)
      (tail batch m n p A B (Packed10.packB batch n p B) b first out) := by
  have h := RowStream.foldl_inv (m - first)
    (row batch m n p A B (prepare (m - first) n ((b.val * m + first) * n) A.toArray)
      (Packed10.packB batch n p B) b first)
    (fun r acc => RowStream.Prefix (RowStream.point batch m n p A B)
      ((b.val * m + first + r) * p) acc)
    (fun r acc hacc => by simpa only [Nat.add_assoc] using row_prefix batch m n p A B b first acc r hacc)
    out (by simpa only [Nat.add_zero] using hout)
  have hend : b.val * m + first + (m - first) = (b.val + 1) * m := by
    rw [Nat.add_mul, Nat.one_mul]
    omega
  simpa only [tail, hend] using h

end Submission.Panel4Tail
