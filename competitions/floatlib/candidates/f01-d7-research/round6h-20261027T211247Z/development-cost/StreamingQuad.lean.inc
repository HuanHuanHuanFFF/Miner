
/- Diagnostic prototype. Full public four-row equivalence is not yet proved. -/
namespace Submission.R22StreamingQuad
open FloatLib.Floats Competition

structure Cell where
  s0 : Float32
  s1 : Float32
  s2 : Float32
  s3 : Float32

abbrev State (p : Nat) := Vector Cell p

@[inline] def update (a0 a1 a2 a3 b : Float32) (s : Cell) : Cell :=
  { s0 := s.s0 + a0 * b, s1 := s.s1 + a1 * b,
    s2 := s.s2 + a2 * b, s3 := s.s3 + a3 * b }

@[inline] def advance (p n baseA baseB : Nat) (A B : Array Binary32)
    (k : Nat) (s : State p) : State p :=
  let a0 := ExecFloat.Binary.toFloat32 (A.getD (baseA + k) posZero)
  let a1 := ExecFloat.Binary.toFloat32 (A.getD (baseA + n + k) posZero)
  let a2 := ExecFloat.Binary.toFloat32 (A.getD (baseA + 2 * n + k) posZero)
  let a3 := ExecFloat.Binary.toFloat32 (A.getD (baseA + 3 * n + k) posZero)
  let rowB := baseB + k * p
  ⟨s.toArray.mapIdx (fun j cell => update a0 a1 a2 a3
      (ExecFloat.Binary.toFloat32 (B.getD (rowB + j) posZero)) cell), by
    simpa only [Array.size_mapIdx] using s.size_toArray⟩

def initial (p : Nat) : State p :=
  ⟨Array.replicate p (⟨Packed10.zero32, Packed10.zero32,
      Packed10.zero32, Packed10.zero32⟩ : Cell), by simp⟩

def loop (p n baseA baseB : Nat) (A B : Array Binary32)
    (k : Nat) (s : State p) : State p :=
  if hk : k < n then
    loop p n baseA baseB A B (k + 1) (advance p n baseA baseB A B k s)
  else s
termination_by n - k

@[noinline] def rows4 (p n baseA baseB : Nat) (A B : Array Binary32)
    (out : Array Binary32) : Array Binary32 :=
  if p = 0 then out else
    let s := loop p n baseA baseB A B 0 (initial p)
    let out := RowStream.emit p (fun j =>
      Packed10.finish n baseA (baseB + j.val) p A B (s.get j).s0) out
    let out := RowStream.emit p (fun j =>
      Packed10.finish n (baseA + n) (baseB + j.val) p A B (s.get j).s1) out
    let out := RowStream.emit p (fun j =>
      Packed10.finish n (baseA + 2 * n) (baseB + j.val) p A B (s.get j).s2) out
    RowStream.emit p (fun j =>
      Packed10.finish n (baseA + 3 * n) (baseB + j.val) p A B (s.get j).s3) out

theorem rows4_size (p n baseA baseB : Nat) (A B : Array Binary32)
    (out : Array Binary32) : (rows4 p n baseA baseB A B out).size = out.size + 4 * p := by
  unfold rows4
  split
  · rename_i hp
    subst p
    simp
  · simp only [R21StreamingPair.emit_size]
    omega

def groups (m n p b : Nat) (A B : Array Binary32) (out : Array Binary32) : Array Binary32 :=
  Fin.foldl (m / 4) (fun acc r => rows4 p n ((b * m + 4 * r.val) * n)
    (b * n * p) A B acc) out

theorem groups_size (m n p b : Nat) (A B : Array Binary32) (out : Array Binary32) :
    (groups m n p b A B out).size = out.size + (m / 4) * (4 * p) := by
  unfold groups
  apply RowStream.foldl_inv (m / 4) _
    (fun k (acc : Array Binary32) => acc.size = out.size + k * (4 * p))
  · intro r acc h
    rw [rows4_size, h, Nat.add_mul]
    simp only [Nat.one_mul, Nat.add_assoc]
  · simp

def rows (m n p b : Nat) (A B : Array Binary32) (out : Array Binary32) : Array Binary32 :=
  let out := groups m n p b A B out
  RowStream.emit ((m % 4) * p) (fun j => NativeFinal.dot n
    ((b * m + m / 4 * 4 + j.val / p) * n) (b * n * p + j.val % p) p A B) out

theorem rows_size (m n p b : Nat) (A B : Array Binary32) (out : Array Binary32) :
    (rows m n p b A B out).size = out.size + m * p := by
  have hd : m / 4 * 4 + m % 4 = m := by omega
  simp only [rows, R21StreamingPair.emit_size, groups_size]
  calc
    out.size + m / 4 * (4 * p) + m % 4 * p =
        out.size + (m / 4 * 4 + m % 4) * p := by
      simp only [Nat.add_mul, Nat.mul_assoc, Nat.add_assoc]
    _ = out.size + m * p := by rw [hd]

def output (batch m n p : Nat) (A B : Array Binary32) : Array Binary32 :=
  Fin.foldl batch (fun acc b => rows m n p b.val A B acc) (Array.mkEmpty (batch * m * p))

theorem output_size (batch m n p : Nat) (A B : Array Binary32) :
    (output batch m n p A B).size = batch * m * p := by
  unfold output
  have h := RowStream.foldl_inv batch (fun acc b => rows m n p b.val A B acc)
    (fun k (acc : Array Binary32) => acc.size = k * (m * p))
    (by
      intro b acc h
      rw [rows_size, h, Nat.add_mul]
      simp)
    (Array.mkEmpty (batch * m * p)) (by simp)
  simpa only [Nat.mul_assoc] using h

def core (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Vector Binary32 (batch * m * p) :=
  ⟨output batch m n p A.toArray B.toArray, output_size batch m n p A.toArray B.toArray⟩

def guarded (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Vector Binary32 (batch * m * p) :=
  if A.toArray.all UnderflowZero.small && B.toArray.all UnderflowZero.small then
    UnderflowZero.zeros batch m p
  else if 1 < n ∧ 4 ≤ m ∧ 2 ≤ p then core batch m n p A B
  else Submission.bmm batch m n p A B

end Submission.R22StreamingQuad
