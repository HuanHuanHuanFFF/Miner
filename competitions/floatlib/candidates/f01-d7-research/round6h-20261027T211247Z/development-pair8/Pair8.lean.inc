
/- Complete diagnostic path. Public all-input equivalence is not yet proved. -/
namespace Submission.R22Pair8
open FloatLib.Floats Competition

abbrev BP := R15ThinPairs.F2
def groups (p : Nat) : Nat := (p + 1) / 2

def zeroPair : BP := ⟨Packed10.zero32, Packed10.zero32⟩

def packRow (p base : Nat) (B : Array Binary32) (out : Array BP) : Array BP :=
  Fin.foldl (groups p) (fun acc j =>
    let c := 2 * j.val
    let b0 := ExecFloat.Binary.toFloat32 (B.getD (base + c) posZero)
    let b1 := if c + 1 < p then
      ExecFloat.Binary.toFloat32 (B.getD (base + c + 1) posZero) else Packed10.zero32
    acc.push (⟨b0, b1⟩ : BP)) out

theorem packRow_size (p base : Nat) (B : Array Binary32) (out : Array BP) :
    (packRow p base B out).size = out.size + groups p := by
  unfold packRow
  apply RowStream.foldl_inv (groups p) _
    (fun k (acc : Array BP) => acc.size = out.size + k)
  · intro j acc h
    simp only [Array.size_push, h]
    omega
  · simp

def packB (batch n p : Nat) (B : Array Binary32) : Array BP :=
  Fin.foldl (batch * n) (fun acc row => packRow p (row.val * p) B acc)
    (Array.mkEmpty (batch * n * groups p))

theorem packB_size (batch n p : Nat) (B : Array Binary32) :
    (packB batch n p B).size = batch * n * groups p := by
  unfold packB
  exact RowStream.foldl_inv (batch * n) (fun acc row => packRow p (row.val * p) B acc)
    (fun k (acc : Array BP) => acc.size = k * groups p)
    (by
      intro row acc h
      rw [packRow_size, h, Nat.add_mul]
      simp)
    (Array.mkEmpty (batch * n * groups p)) (by simp)

structure Cell where
  c00 : Float32
  c10 : Float32
  c20 : Float32
  c30 : Float32
  c01 : Float32
  c11 : Float32
  c21 : Float32
  c31 : Float32

abbrev State (p : Nat) := Vector Cell (groups p)

@[inline] def update (a0 a1 a2 a3 b0 b1 : Float32) (s : Cell) : Cell :=
  { c00 := s.c00 + a0 * b0, c10 := s.c10 + a1 * b0,
    c20 := s.c20 + a2 * b0, c30 := s.c30 + a3 * b0,
    c01 := s.c01 + a0 * b1, c11 := s.c11 + a1 * b1,
    c21 := s.c21 + a2 * b1, c31 := s.c31 + a3 * b1 }

@[inline] def advance (p n baseA baseC : Nat) (A : Array Binary32) (cache : Array BP)
    (k : Nat) (s : State p) : State p :=
  let a0 := ExecFloat.Binary.toFloat32 (A.getD (baseA + k) posZero)
  let a1 := ExecFloat.Binary.toFloat32 (A.getD (baseA + n + k) posZero)
  let a2 := ExecFloat.Binary.toFloat32 (A.getD (baseA + 2 * n + k) posZero)
  let a3 := ExecFloat.Binary.toFloat32 (A.getD (baseA + 3 * n + k) posZero)
  let row := baseC + k * groups p
  ⟨s.toArray.mapIdx (fun j cell =>
    let b := cache.getD (row + j) zeroPair
    update a0 a1 a2 a3 b.s0 b.s1 cell), by
      simpa only [Array.size_mapIdx] using s.size_toArray⟩

def initial (p : Nat) : State p :=
  ⟨Array.replicate (groups p) (⟨Packed10.zero32, Packed10.zero32,
    Packed10.zero32, Packed10.zero32, Packed10.zero32, Packed10.zero32,
    Packed10.zero32, Packed10.zero32⟩ : Cell), by simp⟩

def loop (p n baseA baseC : Nat) (A : Array Binary32) (cache : Array BP)
    (k : Nat) (s : State p) : State p :=
  if hk : k < n then
    loop p n baseA baseC A cache (k + 1) (advance p n baseA baseC A cache k s)
  else s
termination_by n - k

@[inline] def cell {p : Nat} (s : State p) (j : Fin p) : Cell :=
  s.get ⟨j.val / 2, by have hj := j.isLt; unfold groups; omega⟩

@[inline] def view0 {p : Nat} (s : State p) (j : Fin p) : Float32 :=
  let c := cell s j
  if j.val % 2 = 0 then c.c00 else c.c01
@[inline] def view1 {p : Nat} (s : State p) (j : Fin p) : Float32 :=
  let c := cell s j
  if j.val % 2 = 0 then c.c10 else c.c11
@[inline] def view2 {p : Nat} (s : State p) (j : Fin p) : Float32 :=
  let c := cell s j
  if j.val % 2 = 0 then c.c20 else c.c21
@[inline] def view3 {p : Nat} (s : State p) (j : Fin p) : Float32 :=
  let c := cell s j
  if j.val % 2 = 0 then c.c30 else c.c31

@[noinline] def rows4 (p n baseA baseB baseC : Nat) (A B : Array Binary32)
    (cache : Array BP) (out : Array Binary32) : Array Binary32 :=
  if p = 0 then out else
    let s := loop p n baseA baseC A cache 0 (initial p)
    let out := RowStream.emit p (fun j =>
      Packed10.finish n baseA (baseB + j.val) p A B (view0 s j)) out
    let out := RowStream.emit p (fun j =>
      Packed10.finish n (baseA + n) (baseB + j.val) p A B (view1 s j)) out
    let out := RowStream.emit p (fun j =>
      Packed10.finish n (baseA + 2 * n) (baseB + j.val) p A B (view2 s j)) out
    RowStream.emit p (fun j =>
      Packed10.finish n (baseA + 3 * n) (baseB + j.val) p A B (view3 s j)) out

theorem rows4_size (p n baseA baseB baseC : Nat) (A B : Array Binary32)
    (cache : Array BP) (out : Array Binary32) :
    (rows4 p n baseA baseB baseC A B cache out).size = out.size + 4 * p := by
  unfold rows4
  split
  · rename_i hp
    subst p
    simp
  · simp only [R21StreamingPair.emit_size]
    omega

def blocks (m n p b : Nat) (A B : Array Binary32) (cache : Array BP)
    (out : Array Binary32) : Array Binary32 :=
  Fin.foldl (m / 4) (fun acc r => rows4 p n ((b * m + 4 * r.val) * n)
    (b * n * p) (b * n * groups p) A B cache acc) out

theorem blocks_size (m n p b : Nat) (A B : Array Binary32) (cache : Array BP)
    (out : Array Binary32) :
    (blocks m n p b A B cache out).size = out.size + (m / 4) * (4 * p) := by
  unfold blocks
  apply RowStream.foldl_inv (m / 4) _
    (fun k (acc : Array Binary32) => acc.size = out.size + k * (4 * p))
  · intro r acc h
    rw [rows4_size, h, Nat.add_mul]
    simp only [Nat.one_mul, Nat.add_assoc]
  · simp

def rows (m n p b : Nat) (A B : Array Binary32) (cache : Array BP)
    (out : Array Binary32) : Array Binary32 :=
  let out := blocks m n p b A B cache out
  RowStream.emit ((m % 4) * p) (fun j => NativeFinal.dot n
    ((b * m + m / 4 * 4 + j.val / p) * n) (b * n * p + j.val % p) p A B) out

theorem rows_size (m n p b : Nat) (A B : Array Binary32) (cache : Array BP)
    (out : Array Binary32) : (rows m n p b A B cache out).size = out.size + m * p := by
  have hd : m / 4 * 4 + m % 4 = m := by omega
  simp only [rows, R21StreamingPair.emit_size, blocks_size]
  calc
    out.size + m / 4 * (4 * p) + m % 4 * p =
        out.size + (m / 4 * 4 + m % 4) * p := by
      simp only [Nat.add_mul, Nat.mul_assoc, Nat.add_assoc]
    _ = out.size + m * p := by rw [hd]

def output (batch m n p : Nat) (A B : Array Binary32) (cache : Array BP) : Array Binary32 :=
  Fin.foldl batch (fun acc b => rows m n p b.val A B cache acc)
    (Array.mkEmpty (batch * m * p))

theorem output_size (batch m n p : Nat) (A B : Array Binary32) (cache : Array BP) :
    (output batch m n p A B cache).size = batch * m * p := by
  unfold output
  have h := RowStream.foldl_inv batch (fun acc b => rows m n p b.val A B cache acc)
    (fun k (acc : Array Binary32) => acc.size = k * (m * p))
    (by
      intro b acc h
      rw [rows_size, h, Nat.add_mul]
      simp)
    (Array.mkEmpty (batch * m * p)) (by simp)
  simpa only [Nat.mul_assoc] using h

def core (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Vector Binary32 (batch * m * p) :=
  let cache := packB batch n p B.toArray
  ⟨output batch m n p A.toArray B.toArray cache,
    output_size batch m n p A.toArray B.toArray cache⟩

def guarded (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Vector Binary32 (batch * m * p) :=
  if A.toArray.all UnderflowZero.small && B.toArray.all UnderflowZero.small then
    UnderflowZero.zeros batch m p
  else if 1 < n ∧ 4 ≤ m ∧ 2 ≤ p then core batch m n p A B
  else Submission.bmm batch m n p A B

end Submission.R22Pair8
