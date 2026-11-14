/- Diagnostic only. One flat A4 and one flat B2 cache per whole call.
   Same eight ordered scalar chains and four-row Words lifetime as R22Resident8.
   Full-input correctness and actual machine code are NOT_RUN. -/
namespace Submission.R22PreparedResident8
open FloatLib.Floats Competition

abbrev BP := R22Pair8.BP
abbrev Acc := R22Pair8.Cell
abbrev Words := R22Resident8.Words

structure A4 where
  r0 : Float32
  r1 : Float32
  r2 : Float32
  r3 : Float32

def zeroA : A4 :=
  ⟨Packed10.zero32, Packed10.zero32, Packed10.zero32, Packed10.zero32⟩

def packARows (n base : Nat) (A : Array Binary32) (out : Array A4) : Array A4 :=
  Fin.foldl n (fun acc k => acc.push
    (⟨R2W01b.convert ((A.getD (base + k.val) posZero).raw.1),
      R2W01b.convert ((A.getD (base + n + k.val) posZero).raw.1),
      R2W01b.convert ((A.getD (base + 2 * n + k.val) posZero).raw.1),
      R2W01b.convert ((A.getD (base + 3 * n + k.val) posZero).raw.1)⟩ : A4)) out

theorem packARows_size (n base : Nat) (A : Array Binary32) (out : Array A4) :
    (packARows n base A out).size = out.size + n := by
  unfold packARows
  apply RowStream.foldl_inv n _ (fun k (acc : Array A4) => acc.size = out.size + k)
  · intro k acc h
    simp only [Array.size_push, h]
    omega
  · simp

def packABatch (m n b : Nat) (A : Array Binary32) (out : Array A4) : Array A4 :=
  Fin.foldl (m / 4) (fun acc r =>
    packARows n ((b * m + 4 * r.val) * n) A acc) out

theorem packABatch_size (m n b : Nat) (A : Array Binary32) (out : Array A4) :
    (packABatch m n b A out).size = out.size + (m / 4) * n := by
  unfold packABatch
  apply RowStream.foldl_inv (m / 4) _
    (fun k (acc : Array A4) => acc.size = out.size + k * n)
  · intro r acc h
    rw [packARows_size, h, Nat.add_mul]
    simp only [Nat.one_mul, Nat.add_assoc]
  · simp

def packA (batch m n : Nat) (A : Array Binary32) : Array A4 :=
  Fin.foldl batch (fun acc b => packABatch m n b.val A acc)
    (Array.mkEmpty (batch * (m / 4) * n))

theorem packA_size (batch m n : Nat) (A : Array Binary32) :
    (packA batch m n A).size = batch * (m / 4) * n := by
  unfold packA
  have h := RowStream.foldl_inv batch (fun acc b => packABatch m n b.val A acc)
    (fun k (acc : Array A4) => acc.size = k * ((m / 4) * n))
    (by
      intro b acc h
      rw [packABatch_size, h, Nat.add_mul]
      simp)
    (Array.mkEmpty (batch * (m / 4) * n)) (by simp)
  simpa only [Nat.mul_assoc] using h

def packBPair (n p base : Nat) (B : Array Binary32) (second : Bool)
    (out : Array BP) : Array BP :=
  Fin.foldl n (fun acc k =>
    let i := base + k.val * p
    let b0 := R2W01b.convert ((B.getD i posZero).raw.1)
    let b1 := if second then R2W01b.convert ((B.getD (i + 1) posZero).raw.1)
      else Packed10.zero32
    acc.push (⟨b0, b1⟩ : BP)) out

theorem packBPair_size (n p base : Nat) (B : Array Binary32) (second : Bool)
    (out : Array BP) : (packBPair n p base B second out).size = out.size + n := by
  unfold packBPair
  apply RowStream.foldl_inv n _ (fun k (acc : Array BP) => acc.size = out.size + k)
  · intro k acc h
    simp only [Array.size_push, h]
    omega
  · simp

def packBBatch (n p b : Nat) (B : Array Binary32) (out : Array BP) : Array BP :=
  Fin.foldl (R22Pair8.groups p) (fun acc g =>
    packBPair n p (b * n * p + 2 * g.val) B (decide (2 * g.val + 1 < p)) acc) out

theorem packBBatch_size (n p b : Nat) (B : Array Binary32) (out : Array BP) :
    (packBBatch n p b B out).size = out.size + R22Pair8.groups p * n := by
  unfold packBBatch
  apply RowStream.foldl_inv (R22Pair8.groups p) _
    (fun k (acc : Array BP) => acc.size = out.size + k * n)
  · intro g acc h
    rw [packBPair_size, h, Nat.add_mul]
    simp only [Nat.one_mul, Nat.add_assoc]
  · simp

def packB (batch n p : Nat) (B : Array Binary32) : Array BP :=
  Fin.foldl batch (fun acc b => packBBatch n p b.val B acc)
    (Array.mkEmpty (batch * R22Pair8.groups p * n))

theorem packB_size (batch n p : Nat) (B : Array Binary32) :
    (packB batch n p B).size = batch * R22Pair8.groups p * n := by
  unfold packB
  have h := RowStream.foldl_inv batch (fun acc b => packBBatch n p b.val B acc)
    (fun k (acc : Array BP) => acc.size = k * (R22Pair8.groups p * n))
    (by
      intro b acc h
      rw [packBBatch_size, h, Nat.add_mul]
      simp)
    (Array.mkEmpty (batch * R22Pair8.groups p * n)) (by simp)
  simpa only [Nat.mul_assoc] using h

def loop (n aCursor bCursor : Nat) (PA : Array A4) (PB : Array BP)
    (k : Nat) (q00 q10 q20 q30 q01 q11 q21 q31 : Float32) : Acc :=
  if hk : k < n then
    let a := PA.getD (aCursor + k) zeroA
    let b := PB.getD (bCursor + k) R22Pair8.zeroPair
    loop n aCursor bCursor PA PB (k + 1)
      (q00 + a.r0 * b.s0) (q10 + a.r1 * b.s0)
      (q20 + a.r2 * b.s0) (q30 + a.r3 * b.s0)
      (q01 + a.r0 * b.s1) (q11 + a.r1 * b.s1)
      (q21 + a.r2 * b.s1) (q31 + a.r3 * b.s1)
  else ⟨q00, q10, q20, q30, q01, q11, q21, q31⟩
termination_by n - k

@[noinline] def tile (p n baseA baseB aCursor bCursor : Nat) (A B : Array Binary32)
    (PA : Array A4) (PB : Array BP) (second : Bool) : Words :=
  let r := loop n aCursor bCursor PA PB 0
    Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32
    Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32
  match r with
  | ⟨q00, q10, q20, q30, q01, q11, q21, q31⟩ =>
    let w00 := (Packed10.finish n baseA baseB p A B q00).raw.1
    let w10 := (Packed10.finish n (baseA + n) baseB p A B q10).raw.1
    let w20 := (Packed10.finish n (baseA + 2 * n) baseB p A B q20).raw.1
    let w30 := (Packed10.finish n (baseA + 3 * n) baseB p A B q30).raw.1
    if second then
      ⟨w00, w10, w20, w30,
        (Packed10.finish n baseA (baseB + 1) p A B q01).raw.1,
        (Packed10.finish n (baseA + n) (baseB + 1) p A B q11).raw.1,
        (Packed10.finish n (baseA + 2 * n) (baseB + 1) p A B q21).raw.1,
        (Packed10.finish n (baseA + 3 * n) (baseB + 1) p A B q31).raw.1⟩
    else ⟨w00, w10, w20, w30, (0 : UInt32), (0 : UInt32), (0 : UInt32), (0 : UInt32)⟩

def tiles (p n baseA baseB aCursor bCursor : Nat) (A B : Array Binary32)
    (PA : Array A4) (PB : Array BP) : Vector Words (R22Pair8.groups p) :=
  Vector.ofFn (fun g => tile p n baseA (baseB + 2 * g.val)
    aCursor (bCursor + g.val * n) A B PA PB (decide (2 * g.val + 1 < p)))

@[noinline] def rows4 (p n baseA baseB aCursor bCursor : Nat) (A B : Array Binary32)
    (PA : Array A4) (PB : Array BP) (out : Array Binary32) : Array Binary32 :=
  if p = 0 then out else
    let t := tiles p n baseA baseB aCursor bCursor A B PA PB
    let out := RowStream.emit p (R22Resident8.read0 t) out
    let out := RowStream.emit p (R22Resident8.read1 t) out
    let out := RowStream.emit p (R22Resident8.read2 t) out
    RowStream.emit p (R22Resident8.read3 t) out

theorem rows4_size (p n baseA baseB aCursor bCursor : Nat) (A B : Array Binary32)
    (PA : Array A4) (PB : Array BP) (out : Array Binary32) :
    (rows4 p n baseA baseB aCursor bCursor A B PA PB out).size = out.size + 4 * p := by
  unfold rows4
  split
  · rename_i hp
    subst p
    simp
  · simp only [R21StreamingPair.emit_size]
    omega

def blocks (m n p b : Nat) (A B : Array Binary32) (PA : Array A4) (PB : Array BP)
    (out : Array Binary32) : Array Binary32 :=
  Fin.foldl (m / 4) (fun acc r => rows4 p n ((b * m + 4 * r.val) * n)
    (b * n * p) ((b * (m / 4) + r.val) * n)
    (b * R22Pair8.groups p * n) A B PA PB acc) out

theorem blocks_size (m n p b : Nat) (A B : Array Binary32) (PA : Array A4) (PB : Array BP)
    (out : Array Binary32) :
    (blocks m n p b A B PA PB out).size = out.size + (m / 4) * (4 * p) := by
  unfold blocks
  apply RowStream.foldl_inv (m / 4) _
    (fun k (acc : Array Binary32) => acc.size = out.size + k * (4 * p))
  · intro r acc h
    rw [rows4_size, h, Nat.add_mul]
    simp only [Nat.one_mul, Nat.add_assoc]
  · simp

def rows (m n p b : Nat) (A B : Array Binary32) (PA : Array A4) (PB : Array BP)
    (out : Array Binary32) : Array Binary32 :=
  let out := blocks m n p b A B PA PB out
  RowStream.emit ((m % 4) * p) (fun j => NativeFinal.dot n
    ((b * m + m / 4 * 4 + j.val / p) * n) (b * n * p + j.val % p) p A B) out

theorem rows_size (m n p b : Nat) (A B : Array Binary32) (PA : Array A4) (PB : Array BP)
    (out : Array Binary32) : (rows m n p b A B PA PB out).size = out.size + m * p := by
  have hd : m / 4 * 4 + m % 4 = m := by omega
  simp only [rows, R21StreamingPair.emit_size, blocks_size]
  calc
    out.size + m / 4 * (4 * p) + m % 4 * p =
        out.size + (m / 4 * 4 + m % 4) * p := by
      simp only [Nat.add_mul, Nat.mul_assoc, Nat.add_assoc]
    _ = out.size + m * p := by rw [hd]

def output (batch m n p : Nat) (A B : Array Binary32) (PA : Array A4) (PB : Array BP) :
    Array Binary32 :=
  Fin.foldl batch (fun acc b => rows m n p b.val A B PA PB acc)
    (Array.mkEmpty (batch * m * p))

theorem output_size (batch m n p : Nat) (A B : Array Binary32) (PA : Array A4) (PB : Array BP) :
    (output batch m n p A B PA PB).size = batch * m * p := by
  unfold output
  have h := RowStream.foldl_inv batch (fun acc b => rows m n p b.val A B PA PB acc)
    (fun k (acc : Array Binary32) => acc.size = k * (m * p))
    (by
      intro b acc h
      rw [rows_size, h, Nat.add_mul]
      simp)
    (Array.mkEmpty (batch * m * p)) (by simp)
  simpa only [Nat.mul_assoc] using h

def core (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Vector Binary32 (batch * m * p) :=
  let PA := packA batch m n A.toArray
  let PB := packB batch n p B.toArray
  ⟨output batch m n p A.toArray B.toArray PA PB,
    output_size batch m n p A.toArray B.toArray PA PB⟩

def guarded (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Vector Binary32 (batch * m * p) :=
  if A.toArray.all UnderflowZero.small && B.toArray.all UnderflowZero.small then
    UnderflowZero.zeros batch m p
  else if 1 < n ∧ 4 ≤ m ∧ 2 ≤ p then core batch m n p A B
  else Submission.bmm batch m n p A B

end Submission.R22PreparedResident8
