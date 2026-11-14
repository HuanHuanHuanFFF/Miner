
/- Diagnostic: eight scalar accumulators, bounded four-row result lifetime. -/
namespace Submission.R22Resident8
open FloatLib.Floats Competition

abbrev BP := R22Pair8.BP
abbrev Acc := R22Pair8.Cell

def loop (n a0 a1 a2 a3 stride : Nat) (A : Array Binary32) (cache : Array BP)
    (k cursor : Nat) (q00 q10 q20 q30 q01 q11 q21 q31 : Float32) : Acc :=
  if hk : k < n then
    let f0 := R2W01b.convert ((A.getD (a0 + k) posZero).raw.1)
    let f1 := R2W01b.convert ((A.getD (a1 + k) posZero).raw.1)
    let f2 := R2W01b.convert ((A.getD (a2 + k) posZero).raw.1)
    let f3 := R2W01b.convert ((A.getD (a3 + k) posZero).raw.1)
    let b := cache.getD cursor R22Pair8.zeroPair
    loop n a0 a1 a2 a3 stride A cache (k + 1) (cursor + stride)
      (q00 + f0 * b.s0) (q10 + f1 * b.s0) (q20 + f2 * b.s0) (q30 + f3 * b.s0)
      (q01 + f0 * b.s1) (q11 + f1 * b.s1) (q21 + f2 * b.s1) (q31 + f3 * b.s1)
  else ⟨q00, q10, q20, q30, q01, q11, q21, q31⟩
termination_by n - k

structure Words where
  w00 : UInt32
  w10 : UInt32
  w20 : UInt32
  w30 : UInt32
  w01 : UInt32
  w11 : UInt32
  w21 : UInt32
  w31 : UInt32

@[noinline] def tile (p n baseA baseB baseC : Nat) (A B : Array Binary32)
    (cache : Array BP) (second : Bool) : Words :=
  let r := loop n baseA (baseA + n) (baseA + 2 * n) (baseA + 3 * n)
    (R22Pair8.groups p) A cache 0 baseC
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
    else ⟨w00, w10, w20, w30, 0, 0, 0, 0⟩

def tiles (p n baseA baseB baseC : Nat) (A B : Array Binary32) (cache : Array BP) :
    Vector Words (R22Pair8.groups p) :=
  Vector.ofFn (fun g => tile p n baseA (baseB + 2 * g.val) (baseC + g.val) A B cache
    (decide (2 * g.val + 1 < p)))

@[inline] def getTile {p : Nat} (t : Vector Words (R22Pair8.groups p)) (j : Fin p) : Words :=
  t.get ⟨j.val / 2, by have hj := j.isLt; unfold R22Pair8.groups; omega⟩

@[inline] def read0 {p : Nat} (t : Vector Words (R22Pair8.groups p)) (j : Fin p) : Binary32 :=
  let w := getTile t j
  FastMul.ofBits (if j.val % 2 = 0 then w.w00 else w.w01)
@[inline] def read1 {p : Nat} (t : Vector Words (R22Pair8.groups p)) (j : Fin p) : Binary32 :=
  let w := getTile t j
  FastMul.ofBits (if j.val % 2 = 0 then w.w10 else w.w11)
@[inline] def read2 {p : Nat} (t : Vector Words (R22Pair8.groups p)) (j : Fin p) : Binary32 :=
  let w := getTile t j
  FastMul.ofBits (if j.val % 2 = 0 then w.w20 else w.w21)
@[inline] def read3 {p : Nat} (t : Vector Words (R22Pair8.groups p)) (j : Fin p) : Binary32 :=
  let w := getTile t j
  FastMul.ofBits (if j.val % 2 = 0 then w.w30 else w.w31)

@[noinline] def rows4 (p n baseA baseB baseC : Nat) (A B : Array Binary32)
    (cache : Array BP) (out : Array Binary32) : Array Binary32 :=
  if p = 0 then out else
    let t := tiles p n baseA baseB baseC A B cache
    let out := RowStream.emit p (read0 t) out
    let out := RowStream.emit p (read1 t) out
    let out := RowStream.emit p (read2 t) out
    RowStream.emit p (read3 t) out

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
    (b * n * p) (b * n * R22Pair8.groups p) A B cache acc) out

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
  let cache := R22Pair8.packB batch n p B.toArray
  ⟨output batch m n p A.toArray B.toArray cache,
    output_size batch m n p A.toArray B.toArray cache⟩

def guarded (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Vector Binary32 (batch * m * p) :=
  if A.toArray.all UnderflowZero.small && B.toArray.all UnderflowZero.small then
    UnderflowZero.zeros batch m p
  else if 1 < n ∧ 4 ≤ m ∧ 2 ≤ p then core batch m n p A B
  else Submission.bmm batch m n p A B

end Submission.R22Resident8
