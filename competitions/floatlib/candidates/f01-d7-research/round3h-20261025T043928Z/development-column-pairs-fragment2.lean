namespace Submission.R15ThinPairs
open FloatLib.Floats Competition

structure F2 where
  s0 : Float32
  s1 : Float32

def loop (n baseA baseB p : Nat) (A : Array Binary32) (B : Array Float32)
    (k : Nat) (s0 s1 : Float32) : F2 :=
  if hk : k < n then
    let a := ExecFloat.Binary.toFloat32 (A.getD (baseA + k) posZero)
    let b0 := B.getD (baseB + k * p) Packed10.zero32
    let b1 := B.getD (baseB + 1 + k * p) Packed10.zero32
    loop n baseA baseB p A B (k + 1) (s0 + a * b0) (s1 + a * b1)
  else ⟨s0, s1⟩
termination_by n - k

theorem loop_s0 (n baseA baseB p : Nat) (A B : Array Binary32)
    (k : Nat) (s0 s1 : Float32) :
    (loop n baseA baseB p A (B.map ExecFloat.Binary.toFloat32) k s0 s1).s0 =
      NativeFinal.dotLoop n baseA baseB p A B k s0 := by
  by_cases hk : k < n
  · rw [loop, NativeFinal.dotLoop]
    simp only [dif_pos hk]
    simp only [Packed10.nativeA_getD]
    exact loop_s0 n baseA baseB p A B (k + 1) _ _
  · rw [loop, NativeFinal.dotLoop]
    simp only [dif_neg hk]
termination_by n - k

theorem loop_s1 (n baseA baseB p : Nat) (A B : Array Binary32)
    (k : Nat) (s0 s1 : Float32) :
    (loop n baseA baseB p A (B.map ExecFloat.Binary.toFloat32) k s0 s1).s1 =
      NativeFinal.dotLoop n baseA (baseB + 1) p A B k s1 := by
  by_cases hk : k < n
  · rw [loop, NativeFinal.dotLoop]
    simp only [dif_pos hk]
    simp only [Packed10.nativeA_getD]
    exact loop_s1 n baseA baseB p A B (k + 1) _ _
  · rw [loop, NativeFinal.dotLoop]
    simp only [dif_neg hk]
termination_by n - k

@[inline] def select (v : F2) (j : Nat) : Float32 :=
  if j = 0 then v.s0 else v.s1

theorem finish_select (n baseA baseB p : Nat) (A B : Array Binary32)
    (j : Nat) (hj : j < 2) :
    Packed10.finish n baseA (baseB + j) p A B
      (select (loop n baseA baseB p A (B.map ExecFloat.Binary.toFloat32)
        0 Packed10.zero32 Packed10.zero32) j) =
      NativeFinal.dot n baseA (baseB + j) p A B := by
  apply Packed10.finish_eq_dot
  have h : j = 0 ∨ j = 1 := by omega
  rcases h with rfl | rfl
  · simpa only [select, Nat.add_zero, ↓reduceIte] using
      loop_s0 n baseA baseB p A B 0 Packed10.zero32 Packed10.zero32
  · simpa only [select, if_neg Nat.one_ne_zero] using
      loop_s1 n baseA baseB p A B 0 Packed10.zero32 Packed10.zero32

@[inline] def groups (p : Nat) : Nat := (p + 1) / 2

@[inline] def group (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) (preparedB : Array Float32)
    (r : Fin (batch * m)) (out : Array Binary32) (g : Fin (groups p)) :
    Array Binary32 :=
  let baseA := r.val * n
  let baseB := r.val / m * n * p + 2 * g.val
  let result := loop n baseA baseB p A.toArray preparedB
    0 Packed10.zero32 Packed10.zero32
  let count := min 2 (p - 2 * g.val)
  RowStream.emit count (fun l =>
    Packed10.finish n baseA (baseB + l.val) p A.toArray B.toArray
      (select result l.val)) out

theorem group_prefix (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) (r : Fin (batch * m))
    (g : Fin (groups p)) (out : Array Binary32)
    (hout : RowStream.Prefix (RowStream.point batch m n p A B)
      (r.val * p + min (2 * g.val) p) out) :
    RowStream.Prefix (RowStream.point batch m n p A B)
      (r.val * p + min (2 * (g.val + 1)) p)
      (group batch m n p A B (B.toArray.map ExecFloat.Binary.toFloat32) r out g) := by
  have hm : 0 < m := Nat.pos_of_lt_mul_left r.isLt
  have hg : 2 * g.val < p := by
    have h := g.isLt
    unfold groups at h
    omega
  have hp : 0 < p := by omega
  have hstart : min (2 * g.val) p = 2 * g.val := by omega
  have hend : r.val * p + min (2 * (g.val + 1)) p =
      (r.val * p + 2 * g.val) + min 2 (p - 2 * g.val) := by omega
  rw [hend]
  unfold group
  dsimp only
  apply RowStream.emit_prefix
  · simpa only [hstart] using hout
  · intro l
    have hcol : 2 * g.val + l.val < p := by
      have hl := l.isLt
      omega
    rw [show r.val * p + 2 * g.val + l.val =
      r.val * p + (2 * g.val + l.val) by omega,
      RowStream.point_row batch m n p A B r.val (2 * g.val + l.val) hm hp hcol]
    have h := finish_select n (r.val * n) (r.val / m * n * p + 2 * g.val) p
      A.toArray B.toArray l.val (Nat.lt_of_lt_of_le l.isLt (Nat.min_le_left _ _))
    simpa only [Nat.add_assoc] using h

@[inline] def row (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) (preparedB : Array Float32)
    (out : Array Binary32) (r : Fin (batch * m)) : Array Binary32 :=
  Fin.foldl (groups p) (group batch m n p A B preparedB r) out

theorem row_prefix (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) (r : Fin (batch * m))
    (out : Array Binary32)
    (hout : RowStream.Prefix (RowStream.point batch m n p A B) (r.val * p) out) :
    RowStream.Prefix (RowStream.point batch m n p A B) ((r.val + 1) * p)
      (row batch m n p A B (B.toArray.map ExecFloat.Binary.toFloat32) out r) := by
  have hlast : min (2 * groups p) p = p := by
    unfold groups
    omega
  have h := RowStream.foldl_inv (groups p)
    (group batch m n p A B (B.toArray.map ExecFloat.Binary.toFloat32) r)
    (fun g acc => RowStream.Prefix (RowStream.point batch m n p A B)
      (r.val * p + min (2 * g) p) acc)
    (fun g acc hacc => group_prefix batch m n p A B r g acc hacc) out
    (by simpa only [Nat.mul_zero, Nat.zero_min, Nat.add_zero] using hout)
  simpa only [row, hlast, Nat.add_mul, Nat.one_mul] using h

def output (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Array Binary32 :=
  let preparedB := B.toArray.map ExecFloat.Binary.toFloat32
  Fin.foldl (batch * m) (row batch m n p A B preparedB)
    (Array.mkEmpty (batch * m * p))

theorem output_prefix (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) :
    RowStream.Prefix (RowStream.point batch m n p A B) (batch * m * p)
      (output batch m n p A B) := by
  exact RowStream.foldl_inv (batch * m)
    (row batch m n p A B (B.toArray.map ExecFloat.Binary.toFloat32))
    (fun r acc => RowStream.Prefix (RowStream.point batch m n p A B) (r * p) acc)
    (fun r acc hacc => row_prefix batch m n p A B r acc hacc)
    (Array.mkEmpty (batch * m * p))
    ⟨by simp, by intro j hj; simp at hj⟩

def core (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Vector Binary32 (batch * m * p) :=
  ⟨output batch m n p A B, (output_prefix batch m n p A B).1⟩

theorem core_eq_reference (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) :
    core batch m n p A B = referenceBmm batch m n p A B := by
  exact (RowStream.prefix_vector_eq_ofFn (RowStream.point batch m n p A B)
    (batch * m * p) (output batch m n p A B) (output_prefix batch m n p A B)).trans
    (RowStream.points_eq_reference batch m n p A B)

def dispatch (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Vector Binary32 (batch * m * p) :=
  if 2 ≤ p ∧ p ≤ 8 ∧ 1 < n ∧ 4 ≤ m then core batch m n p A B
  else bmmBeforeUnderflowZero batch m n p A B

theorem dispatch_spec : ∀ (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n)) (B : Vector Binary32 (batch * n * p)),
    (dispatch batch m n p A B).get = bmmSpec batch m n p A.get B.get := by
  intro batch m n p A B
  unfold dispatch
  split
  · rw [core_eq_reference]
    exact referenceBmm_spec batch m n p A B
  · exact bmmBeforeUnderflowZero_spec batch m n p A B

end Submission.R15ThinPairs