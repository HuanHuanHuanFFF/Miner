

namespace Submission.R21StreamingPair
open FloatLib.Floats Competition
theorem emit_size (p : Nat) (read : Fin p → Binary32) (out : Array Binary32) :
    (RowStream.emit p read out).size = out.size + p := by
  unfold RowStream.emit
  exact RowStream.foldl_inv (β := Array Binary32) p
    (fun (acc : Array Binary32) (j : Fin p) => acc.push (read j))
    (fun k (acc : Array Binary32) => acc.size = out.size + k)
    (by
      intro j acc h
      simp only [Array.size_push, h]
      omega)
    out (by omega)

end Submission.R21StreamingPair

/- Diagnostic only: A4 per four-row panel, B4 per column-group/k.
   Sixteen independent original-order scalar chains, no temporal unrolling.
   Complete new Float32/Lean/cost validation remains NOT_RUN. -/
namespace Submission.R22Resident16
open FloatLib.Floats Competition

def groups (p : Nat) : Nat := (p + 3) / 4

structure A4 where
  r0 : Float32
  r1 : Float32
  r2 : Float32
  r3 : Float32

structure B4 where
  s0 : Float32
  s1 : Float32
  s2 : Float32
  s3 : Float32

structure Acc where
  q00 : Float32
  q10 : Float32
  q20 : Float32
  q30 : Float32
  q01 : Float32
  q11 : Float32
  q21 : Float32
  q31 : Float32
  q02 : Float32
  q12 : Float32
  q22 : Float32
  q32 : Float32
  q03 : Float32
  q13 : Float32
  q23 : Float32
  q33 : Float32

structure Words where
  w00 : UInt32
  w10 : UInt32
  w20 : UInt32
  w30 : UInt32
  w01 : UInt32
  w11 : UInt32
  w21 : UInt32
  w31 : UInt32
  w02 : UInt32
  w12 : UInt32
  w22 : UInt32
  w32 : UInt32
  w03 : UInt32
  w13 : UInt32
  w23 : UInt32
  w33 : UInt32

def packA (n base : Nat) (A : Array Binary32) : Vector A4 n :=
  Vector.ofFn fun k =>
    ⟨ExecFloat.Binary.toFloat32 (A.getD (base + k.val) posZero),
     ExecFloat.Binary.toFloat32 (A.getD (base + n + k.val) posZero),
     ExecFloat.Binary.toFloat32 (A.getD (base + 2 * n + k.val) posZero),
     ExecFloat.Binary.toFloat32 (A.getD (base + 3 * n + k.val) posZero)⟩

def packBGroup (n p base : Nat) (B : Array Binary32) (valid : Nat) : Vector B4 n :=
  Vector.ofFn fun k =>
    let i := base + k.val * p
    ⟨ExecFloat.Binary.toFloat32 (B.getD i posZero),
     if 1 < valid then ExecFloat.Binary.toFloat32 (B.getD (i + 1) posZero) else Packed10.zero32,
     if 2 < valid then ExecFloat.Binary.toFloat32 (B.getD (i + 2) posZero) else Packed10.zero32,
     if 3 < valid then ExecFloat.Binary.toFloat32 (B.getD (i + 3) posZero) else Packed10.zero32⟩

def packBBatch (n p b : Nat) (B : Array Binary32) (out : Array (Vector B4 n)) :
    Array (Vector B4 n) :=
  Fin.foldl (groups p) (fun acc g =>
    acc.push (packBGroup n p (b * n * p + 4 * g.val) B (min 4 (p - 4 * g.val)))) out

theorem packBBatch_size (n p b : Nat) (B : Array Binary32) (out : Array (Vector B4 n)) :
    (packBBatch n p b B out).size = out.size + groups p := by
  unfold packBBatch
  apply RowStream.foldl_inv (groups p) _
    (fun k (acc : Array (Vector B4 n)) => acc.size = out.size + k)
  · intro g acc h
    simp only [Array.size_push, h]
    omega
  · simp

def packBData (batch n p : Nat) (B : Array Binary32) : Array (Vector B4 n) :=
  Fin.foldl batch (fun acc b => packBBatch n p b.val B acc)
    (Array.mkEmpty (batch * groups p))

theorem packBData_size (batch n p : Nat) (B : Array Binary32) :
    (packBData batch n p B).size = batch * groups p := by
  unfold packBData
  exact RowStream.foldl_inv batch (fun acc b => packBBatch n p b.val B acc)
    (fun k (acc : Array (Vector B4 n)) => acc.size = k * groups p)
    (by
      intro b acc h
      rw [packBBatch_size, h, Nat.add_mul]
      simp)
    (Array.mkEmpty (batch * groups p)) (by simp)

abbrev PackedB (batch n p : Nat) := Vector (Vector B4 n) (batch * groups p)

def packB (batch n p : Nat) (B : Array Binary32) : PackedB batch n p :=
  ⟨packBData batch n p B, packBData_size batch n p B⟩

def tileIndex (batch p : Nat) (b : Fin batch) (g : Fin (groups p)) :
    Fin (batch * groups p) :=
  ⟨b.val * groups p + g.val, by
    have h := Nat.mul_le_mul_right (groups p) b.isLt
    rw [Nat.succ_mul] at h
    have hg := g.isLt
    omega⟩

def wordLoop {n : Nat} (count : USize) (A : Vector A4 n) (B : Vector B4 n)
    (hn : count.toNat = n) (k : USize)
    (q00 q10 q20 q30 : Float32)
    (q01 q11 q21 q31 : Float32)
    (q02 q12 q22 q32 : Float32)
    (q03 q13 q23 q33 : Float32)
    : Acc :=
  if hk : k < count then
    have hkn : k.toNat < n := by rw [←hn]; exact USize.lt_iff_toNat_lt.mp hk
    let a := A.toArray.uget k (by simpa only [A.size_toArray] using hkn)
    let b := B.toArray.uget k (by simpa only [B.size_toArray] using hkn)
    wordLoop count A B hn (k + 1)
      (q00 + a.r0 * b.s0) (q10 + a.r1 * b.s0) (q20 + a.r2 * b.s0) (q30 + a.r3 * b.s0)
      (q01 + a.r0 * b.s1) (q11 + a.r1 * b.s1) (q21 + a.r2 * b.s1) (q31 + a.r3 * b.s1)
      (q02 + a.r0 * b.s2) (q12 + a.r1 * b.s2) (q22 + a.r2 * b.s2) (q32 + a.r3 * b.s2)
      (q03 + a.r0 * b.s3) (q13 + a.r1 * b.s3) (q23 + a.r2 * b.s3) (q33 + a.r3 * b.s3)
  else ⟨q00, q10, q20, q30, q01, q11, q21, q31, q02, q12, q22, q32, q03, q13, q23, q33⟩
termination_by count.toNat - k.toNat
decreasing_by all_goals exact Packed10Index.next_decreases (by assumption)

def runDot (n : Nat) (A : Vector A4 n) (B : Vector B4 n) (hn : n < USize.size) : Acc :=
  wordLoop (USize.ofNat n) A B (USize.toNat_ofNat_of_lt' hn) 0
    Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32
    Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32
    Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32
    Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32

@[noinline] def tile (p n baseA baseB valid : Nat) (A B : Array Binary32)
    (PA : Vector A4 n) (PB : Vector B4 n) (hn : n < USize.size) : Words :=
  let q := runDot n PA PB hn
  let w00 := (Packed10.finish n baseA baseB p A B q.q00).raw.1
  let w10 := (Packed10.finish n (baseA + 1 * n) baseB p A B q.q10).raw.1
  let w20 := (Packed10.finish n (baseA + 2 * n) baseB p A B q.q20).raw.1
  let w30 := (Packed10.finish n (baseA + 3 * n) baseB p A B q.q30).raw.1
  let w01 := if 1 < valid then (Packed10.finish n baseA (baseB + 1) p A B q.q01).raw.1 else (0 : UInt32)
  let w11 := if 1 < valid then (Packed10.finish n (baseA + 1 * n) (baseB + 1) p A B q.q11).raw.1 else (0 : UInt32)
  let w21 := if 1 < valid then (Packed10.finish n (baseA + 2 * n) (baseB + 1) p A B q.q21).raw.1 else (0 : UInt32)
  let w31 := if 1 < valid then (Packed10.finish n (baseA + 3 * n) (baseB + 1) p A B q.q31).raw.1 else (0 : UInt32)
  let w02 := if 2 < valid then (Packed10.finish n baseA (baseB + 2) p A B q.q02).raw.1 else (0 : UInt32)
  let w12 := if 2 < valid then (Packed10.finish n (baseA + 1 * n) (baseB + 2) p A B q.q12).raw.1 else (0 : UInt32)
  let w22 := if 2 < valid then (Packed10.finish n (baseA + 2 * n) (baseB + 2) p A B q.q22).raw.1 else (0 : UInt32)
  let w32 := if 2 < valid then (Packed10.finish n (baseA + 3 * n) (baseB + 2) p A B q.q32).raw.1 else (0 : UInt32)
  let w03 := if 3 < valid then (Packed10.finish n baseA (baseB + 3) p A B q.q03).raw.1 else (0 : UInt32)
  let w13 := if 3 < valid then (Packed10.finish n (baseA + 1 * n) (baseB + 3) p A B q.q13).raw.1 else (0 : UInt32)
  let w23 := if 3 < valid then (Packed10.finish n (baseA + 2 * n) (baseB + 3) p A B q.q23).raw.1 else (0 : UInt32)
  let w33 := if 3 < valid then (Packed10.finish n (baseA + 3 * n) (baseB + 3) p A B q.q33).raw.1 else (0 : UInt32)
  ⟨w00, w10, w20, w30, w01, w11, w21, w31, w02, w12, w22, w32, w03, w13, w23, w33⟩

def tiles (batch m n p : Nat) (A B : Array Binary32) (PB : PackedB batch n p)
    (hn : n < USize.size) (b : Fin batch) (first : Nat) : Vector Words (groups p) :=
  let baseA := (b.val * m + first) * n
  let PA := packA n baseA A
  Vector.ofFn (fun g => tile p n baseA (b.val * n * p + 4 * g.val)
    (min 4 (p - 4 * g.val)) A B PA (PB.get (tileIndex batch p b g)) hn)

@[inline] def getTile {p : Nat} (t : Vector Words (groups p)) (j : Fin p) : Words :=
  t.get ⟨j.val / 4, by have hj := j.isLt; unfold groups; omega⟩

@[inline] def read0 {p : Nat} (t : Vector Words (groups p)) (j : Fin p) : Binary32 :=
  let w := getTile t j
  FastMul.ofBits (match j.val % 4 with
    | 0 => w.w00 | 1 => w.w01 | 2 => w.w02 | _ => w.w03)
@[inline] def read1 {p : Nat} (t : Vector Words (groups p)) (j : Fin p) : Binary32 :=
  let w := getTile t j
  FastMul.ofBits (match j.val % 4 with
    | 0 => w.w10 | 1 => w.w11 | 2 => w.w12 | _ => w.w13)
@[inline] def read2 {p : Nat} (t : Vector Words (groups p)) (j : Fin p) : Binary32 :=
  let w := getTile t j
  FastMul.ofBits (match j.val % 4 with
    | 0 => w.w20 | 1 => w.w21 | 2 => w.w22 | _ => w.w23)
@[inline] def read3 {p : Nat} (t : Vector Words (groups p)) (j : Fin p) : Binary32 :=
  let w := getTile t j
  FastMul.ofBits (match j.val % 4 with
    | 0 => w.w30 | 1 => w.w31 | 2 => w.w32 | _ => w.w33)

@[noinline] def rows4 (batch m n p : Nat) (A B : Array Binary32) (PB : PackedB batch n p)
    (hn : n < USize.size) (b : Fin batch) (first : Nat) (out : Array Binary32) : Array Binary32 :=
  if p = 0 then out else
    let t := tiles batch m n p A B PB hn b first
    let out := RowStream.emit p (read0 t) out
    let out := RowStream.emit p (read1 t) out
    let out := RowStream.emit p (read2 t) out
    RowStream.emit p (read3 t) out

theorem rows4_size (batch m n p : Nat) (A B : Array Binary32) (PB : PackedB batch n p)
    (hn : n < USize.size) (b : Fin batch) (first : Nat) (out : Array Binary32) :
    (rows4 batch m n p A B PB hn b first out).size = out.size + 4 * p := by
  unfold rows4
  split
  · rename_i hp
    subst p
    simp
  · simp only [R21StreamingPair.emit_size]
    omega

def blocks (batch m n p : Nat) (A B : Array Binary32) (PB : PackedB batch n p)
    (hn : n < USize.size) (b : Fin batch) (out : Array Binary32) : Array Binary32 :=
  Fin.foldl (m / 4) (fun acc r => rows4 batch m n p A B PB hn b (4 * r.val) acc) out

theorem blocks_size (batch m n p : Nat) (A B : Array Binary32) (PB : PackedB batch n p)
    (hn : n < USize.size) (b : Fin batch) (out : Array Binary32) :
    (blocks batch m n p A B PB hn b out).size = out.size + (m / 4) * (4 * p) := by
  unfold blocks
  apply RowStream.foldl_inv (m / 4) _
    (fun k (acc : Array Binary32) => acc.size = out.size + k * (4 * p))
  · intro r acc h
    rw [rows4_size, h, Nat.add_mul]
    simp only [Nat.one_mul, Nat.add_assoc]
  · simp

def rows (batch m n p : Nat) (A B : Array Binary32) (PB : PackedB batch n p)
    (hn : n < USize.size) (b : Fin batch) (out : Array Binary32) : Array Binary32 :=
  let out := blocks batch m n p A B PB hn b out
  RowStream.emit ((m % 4) * p) (fun j => NativeFinal.dot n
    ((b.val * m + m / 4 * 4 + j.val / p) * n) (b.val * n * p + j.val % p) p A B) out

theorem rows_size (batch m n p : Nat) (A B : Array Binary32) (PB : PackedB batch n p)
    (hn : n < USize.size) (b : Fin batch) (out : Array Binary32) :
    (rows batch m n p A B PB hn b out).size = out.size + m * p := by
  have hd : m / 4 * 4 + m % 4 = m := by omega
  simp only [rows, R21StreamingPair.emit_size, blocks_size]
  calc
    out.size + m / 4 * (4 * p) + m % 4 * p =
        out.size + (m / 4 * 4 + m % 4) * p := by
      simp only [Nat.add_mul, Nat.mul_assoc, Nat.add_assoc]
    _ = out.size + m * p := by rw [hd]

def output (batch m n p : Nat) (A B : Array Binary32) (PB : PackedB batch n p)
    (hn : n < USize.size) : Array Binary32 :=
  Fin.foldl batch (fun acc b => rows batch m n p A B PB hn b acc)
    (Array.mkEmpty (batch * m * p))

theorem output_size (batch m n p : Nat) (A B : Array Binary32) (PB : PackedB batch n p)
    (hn : n < USize.size) : (output batch m n p A B PB hn).size = batch * m * p := by
  unfold output
  have h := RowStream.foldl_inv batch (fun acc b => rows batch m n p A B PB hn b acc)
    (fun k (acc : Array Binary32) => acc.size = k * (m * p))
    (by
      intro b acc h
      rw [rows_size, h, Nat.add_mul]
      simp)
    (Array.mkEmpty (batch * m * p)) (by simp)
  simpa only [Nat.mul_assoc] using h

def core (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) (hn : n < USize.size) :
    Vector Binary32 (batch * m * p) :=
  let PB := packB batch n p B.toArray
  ⟨output batch m n p A.toArray B.toArray PB hn,
    output_size batch m n p A.toArray B.toArray PB hn⟩

def guarded (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Vector Binary32 (batch * m * p) :=
  if A.toArray.all UnderflowZero.small && B.toArray.all UnderflowZero.small then
    UnderflowZero.zeros batch m p
  else if h : 1 < n ∧ 4 ≤ m ∧ 4 ≤ p ∧ n < USize.size then core batch m n p A B h.2.2.2
  else Submission.bmm batch m n p A B

end Submission.R22Resident16
