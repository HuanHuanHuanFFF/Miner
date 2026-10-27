/- R15 matrix worker: fuse two independent columns while reusing one prepared B.
   Based on this repository's NativeFinal, Packed10 and DirectContinuous proofs.
   No external implementation code copied. UNCOMPILED proof attempt. -/
namespace Submission.R15ThinDual
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
    dsimp only
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
    dsimp only
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
  · simpa only [select, Nat.add_zero, if_pos rfl] using
      loop_s0 n baseA baseB p A B 0 Packed10.zero32 Packed10.zero32
  · simpa only [select, if_neg Nat.one_ne_zero] using
      loop_s1 n baseA baseB p A B 0 Packed10.zero32 Packed10.zero32

@[inline] def row (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) (preparedB : Array Float32)
    (out : Array Binary32) (r : Fin (batch * m)) : Array Binary32 :=
  let baseA := r.val * n
  let baseB := r.val / m * n * p
  let result := loop n baseA baseB p A.toArray preparedB
    0 Packed10.zero32 Packed10.zero32
  RowStream.emit p (fun j =>
    Packed10.finish n baseA (baseB + j.val) p A.toArray B.toArray
      (select result j.val)) out

theorem row_eq (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) (hp : p = 2)
    (out : Array Binary32) (r : Fin (batch * m)) :
    row batch m n p A B (B.toArray.map ExecFloat.Binary.toFloat32) out r =
      DirectContinuous.row batch m n p A B out r := by
  dsimp only [row, DirectContinuous.row]
  apply congrArg (fun read : Fin p → Binary32 => RowStream.emit p read out)
  funext j
  exact finish_select n (r.val * n) (r.val / m * n * p) p A.toArray B.toArray
    j.val (by simpa only [hp] using j.isLt)

def output (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Array Binary32 :=
  let preparedB := B.toArray.map ExecFloat.Binary.toFloat32
  Fin.foldl (batch * m) (row batch m n p A B preparedB)
    (Array.mkEmpty (batch * m * p))

theorem output_eq (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) (hp : p = 2) :
    output batch m n p A B = DirectContinuous.output batch m n p A B := by
  unfold output DirectContinuous.output
  apply congrArg (fun step : Array Binary32 → Fin (batch * m) → Array Binary32 =>
    Fin.foldl (batch * m) step (Array.mkEmpty (batch * m * p)))
  funext out r
  exact row_eq batch m n p A B hp out r

theorem output_prefix (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) (hp : p = 2) :
    RowStream.Prefix (RowStream.point batch m n p A B) (batch * m * p)
      (output batch m n p A B) := by
  rw [output_eq batch m n p A B hp]
  exact DirectContinuous.output_prefix batch m n p A B

def core (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) (hp : p = 2) :
    Vector Binary32 (batch * m * p) :=
  ⟨output batch m n p A B, (output_prefix batch m n p A B hp).1⟩

theorem core_eq_reference (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) (hp : p = 2) :
    core batch m n p A B hp = referenceBmm batch m n p A B := by
  exact (RowStream.prefix_vector_eq_ofFn (RowStream.point batch m n p A B)
    (batch * m * p) (output batch m n p A B) (output_prefix batch m n p A B hp)).trans
    (RowStream.points_eq_reference batch m n p A B)

def dispatch (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Vector Binary32 (batch * m * p) :=
  if h : p = 2 ∧ 1 < n ∧ 4 ≤ m then core batch m n p A B h.1
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

end Submission.R15ThinDual
