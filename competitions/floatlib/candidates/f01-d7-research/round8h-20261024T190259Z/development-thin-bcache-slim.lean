/- R14 developer component. Reuse B across multiple rows of thin outputs.
   Earlier M29 only cached n=1,p>2; this route keeps n=1 unchanged and
   targets n>1,p<=2 with m>=4. Original raw arrays remain for exact replay. -/
namespace Submission.R14ThinBCache

open FloatLib.Floats Competition

def loop (n baseA baseB p : Nat) (A : Array Binary32) (B : Array Float32)
    (k : Nat) (acc : Float32) : Float32 :=
  if hk : k < n then
    let fa := ExecFloat.Binary.toFloat32 (A.getD (baseA + k) posZero)
    let fb := B.getD (baseB + k * p) Packed10.zero32
    loop n baseA baseB p A B (k + 1) (acc + fa * fb)
  else acc
termination_by n - k

theorem loop_eq (n baseA baseB p : Nat) (A B : Array Binary32)
    (k : Nat) (acc : Float32) :
    loop n baseA baseB p A (B.map ExecFloat.Binary.toFloat32) k acc =
      NativeFinal.dotLoop n baseA baseB p A B k acc := by
  by_cases hk : k < n
  · rw [loop, NativeFinal.dotLoop]
    simp only [dif_pos hk]
    dsimp only
    rw [Packed10.nativeA_getD]
    exact loop_eq n baseA baseB p A B (k + 1) _
  · rw [loop, NativeFinal.dotLoop]
    simp only [dif_neg hk]
termination_by n - k

def dot (n baseA baseB p : Nat) (Araw Braw : Array Binary32)
    (preparedB : Array Float32) : Binary32 :=
  Packed10.finish n baseA baseB p Araw Braw
    (loop n baseA baseB p Araw preparedB 0 Packed10.zero32)

theorem dot_eq (n baseA baseB p : Nat) (A B : Array Binary32) :
    dot n baseA baseB p A B (B.map ExecFloat.Binary.toFloat32) =
      NativeFinal.dot n baseA baseB p A B := by
  unfold dot
  apply Packed10.finish_eq_dot
  exact loop_eq n baseA baseB p A B 0 Packed10.zero32

@[inline] def row (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) (preparedB : Array Float32)
    (out : Array Binary32) (r : Fin (batch * m)) : Array Binary32 :=
  let baseA := r.val * n
  let baseB := r.val / m * n * p
  RowStream.emit p (fun j => dot n baseA (baseB + j.val) p A.toArray B.toArray preparedB) out

theorem row_eq (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n)) (B : Vector Binary32 (batch * n * p))
    (out : Array Binary32) (r : Fin (batch * m)) :
    row batch m n p A B (B.toArray.map ExecFloat.Binary.toFloat32) out r =
      DirectContinuous.row batch m n p A B out r := by
  dsimp only [row, DirectContinuous.row]
  apply congrArg (fun read : Fin p → Binary32 => RowStream.emit p read out)
  funext j
  exact dot_eq _ _ _ _ _ _

def output (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n)) (B : Vector Binary32 (batch * n * p)) : Array Binary32 :=
  let preparedB := B.toArray.map ExecFloat.Binary.toFloat32
  Fin.foldl (batch * m) (row batch m n p A B preparedB) (Array.mkEmpty (batch * m * p))

theorem output_eq (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n)) (B : Vector Binary32 (batch * n * p)) :
    output batch m n p A B = DirectContinuous.output batch m n p A B := by
  unfold output DirectContinuous.output
  apply congrArg (fun step : Array Binary32 → Fin (batch * m) → Array Binary32 =>
    Fin.foldl (batch * m) step (Array.mkEmpty (batch * m * p)))
  funext out r
  exact row_eq batch m n p A B out r

theorem output_prefix (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n)) (B : Vector Binary32 (batch * n * p)) :
    RowStream.Prefix (RowStream.point batch m n p A B) (batch * m * p) (output batch m n p A B) := by
  rw [output_eq]
  exact DirectContinuous.output_prefix batch m n p A B

def core (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n)) (B : Vector Binary32 (batch * n * p)) : Vector Binary32 (batch * m * p) :=
  ⟨output batch m n p A B, (output_prefix batch m n p A B).1⟩

theorem core_eq_reference (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n)) (B : Vector Binary32 (batch * n * p)) :
    core batch m n p A B = referenceBmm batch m n p A B := by
  exact (RowStream.prefix_vector_eq_ofFn (RowStream.point batch m n p A B)
    (batch * m * p) (output batch m n p A B) (output_prefix batch m n p A B)).trans
    (RowStream.points_eq_reference batch m n p A B)

def dispatch (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n)) (B : Vector Binary32 (batch * n * p)) : Vector Binary32 (batch * m * p) :=
  if 4 ≤ m ∧ 1 < n ∧ 0 < p ∧ p ≤ 2 then core batch m n p A B
  else bmmBeforeR11Cross batch m n p A B

theorem dispatch_spec : ∀ (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n)) (B : Vector Binary32 (batch * n * p)),
    (dispatch batch m n p A B).get = bmmSpec batch m n p A.get B.get := by
  intro batch m n p A B
  unfold dispatch
  split
  · rw [core_eq_reference]
    exact referenceBmm_spec batch m n p A B
  · exact bmmBeforeR11Cross_spec batch m n p A B

end Submission.R14ThinBCache
