/- R22 B-only checked FloatArray. Runtime/size helpers only; NOT_RUN.
   Dependencies: retained622d; R21StreamingPair.emit_size; B fb7d NativeTarget.
   Each tile stores exactly the old B2 left/right reads, including odd padding. -/
namespace Submission.R22FloatArrayB2Expected
open FloatLib.Floats Competition

abbrev Tile (n : Nat) := { data : FloatArray // data.size = 2 * n }

theorem push_size (out : FloatArray) (d : Float) :
    (out.push d).size = out.size + 1 := by
  cases out with
  | mk ds => simp only [FloatArray.push, FloatArray.size, Array.size_push]

def packTileLoop (n base p : Nat) (B : Array Binary32)
    (k : Nat) (hk : k ≤ n) (out : FloatArray) (hs : out.size = 2 * k) :
    Option (Tile n) :=
  if h : k < n then
    let raw0 := B.getD (base + k * p) posZero
    let f0 := ExecFloat.Binary.toFloat32 raw0
    let d0 := f0.toFloat
    if R22ExpectedB2Check.check raw0 d0 then
      let raw1 := B.getD (base + 1 + k * p) posZero
      let f1 := ExecFloat.Binary.toFloat32 raw1
      let d1 := f1.toFloat
      if R22ExpectedB2Check.check raw1 d1 then
        packTileLoop n base p B (k + 1) (by omega) ((out.push d0).push d1)
          (by rw [push_size, push_size, hs]; omega)
      else none
    else none
  else some ⟨out, by have he : k = n := by omega; simpa only [he] using hs⟩
termination_by n - k

def packTile (n base p : Nat) (B : Array Binary32) : Option (Tile n) :=
  packTileLoop n base p B 0 (Nat.zero_le n)
    (FloatArray.emptyWithCapacity (2 * n)) (by rfl)

def packTilesLoop (count n p : Nat) (B : Array Binary32)
    (t : Nat) (ht : t ≤ count) (out : Array (Tile n)) (hs : out.size = t) :
    Option (Vector (Tile n) count) :=
  if h : t < count then
    let b := t / R15ThinPairs.groups p
    let g := t % R15ThinPairs.groups p
    match packTile n (b * n * p + 2 * g) p B with
    | none => none
    | some tile => packTilesLoop count n p B (t + 1) (by omega) (out.push tile)
        (by simpa only [Array.size_push, hs])
  else some ⟨out, by have he : t = count := by omega; simpa only [he] using hs⟩
termination_by count - t

def packB (batch n p : Nat) (B : Array Binary32) :
    Option (Vector (Tile n) (batch * R15ThinPairs.groups p)) :=
  packTilesLoop (batch * R15ThinPairs.groups p) n p B 0 (Nat.zero_le _)
    (Array.mkEmpty (batch * R15ThinPairs.groups p)) (by rfl)

def loop (n baseA : Nat) (A : Array Binary32) (packed : Tile n)
    (k : Nat) (s0 s1 : Float32) : R15ThinPairs.F2 :=
  if hk : k < n then
    let a := ExecFloat.Binary.toFloat32 (A.getD (baseA + k) posZero)
    let b0 := (packed.val.get (2 * k) (by rw [packed.property]; omega)).toFloat32
    let b1 := (packed.val.get (2 * k + 1) (by rw [packed.property]; omega)).toFloat32
    loop n baseA A packed (k + 1) (s0 + a * b0) (s1 + a * b1)
  else ⟨s0, s1⟩
termination_by n - k

@[inline] def group (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n)) (B : Vector Binary32 (batch * n * p))
    (packedB : Vector (Tile n) (batch * R15ThinPairs.groups p))
    (r : Fin (batch * m)) (out : Array Binary32) (g : Fin (R15ThinPairs.groups p)) :
    Array Binary32 :=
  have hm : 0 < m := Nat.pos_of_lt_mul_left r.isLt
  let b : Fin batch := ⟨r.val / m, (Nat.div_lt_iff_lt_mul hm).2 r.isLt⟩
  let baseA := r.val * n
  let baseB := b.val * n * p + 2 * g.val
  let result := loop n baseA A.toArray (packedB.get (R15PackedB2.tileIndex batch p b g))
    0 Packed10.zero32 Packed10.zero32
  let count := min 2 (p - 2 * g.val)
  RowStream.emit count (fun l =>
    Packed10.finish n baseA (baseB + l.val) p A.toArray B.toArray
      (R15ThinPairs.select result l.val)) out

theorem group_size (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n)) (B : Vector Binary32 (batch * n * p))
    (packedB : Vector (Tile n) (batch * R15ThinPairs.groups p))
    (r : Fin (batch * m)) (out : Array Binary32) (g : Fin (R15ThinPairs.groups p)) :
    (group batch m n p A B packedB r out g).size = out.size + min 2 (p - 2 * g.val) := by
  dsimp only [group]
  exact R21StreamingPair.emit_size _ _ _

@[inline] def row (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n)) (B : Vector Binary32 (batch * n * p))
    (packedB : Vector (Tile n) (batch * R15ThinPairs.groups p))
    (out : Array Binary32) (r : Fin (batch * m)) : Array Binary32 :=
  Fin.foldl (R15ThinPairs.groups p) (group batch m n p A B packedB r) out

theorem row_size (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n)) (B : Vector Binary32 (batch * n * p))
    (packedB : Vector (Tile n) (batch * R15ThinPairs.groups p))
    (out : Array Binary32) (r : Fin (batch * m)) :
    (row batch m n p A B packedB out r).size = out.size + p := by
  have hlast : min (2 * R15ThinPairs.groups p) p = p := by
    unfold R15ThinPairs.groups
    omega
  unfold row
  have h := RowStream.foldl_inv (R15ThinPairs.groups p)
    (group batch m n p A B packedB r)
    (fun k (acc : Array Binary32) => acc.size = out.size + min (2 * k) p)
    (by
      intro g acc h
      rw [group_size, h]
      omega)
    out (by simp)
  simpa only [hlast] using h

def output (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n)) (B : Vector Binary32 (batch * n * p))
    (packedB : Vector (Tile n) (batch * R15ThinPairs.groups p)) : Array Binary32 :=
  Fin.foldl (batch * m) (row batch m n p A B packedB)
    (Array.mkEmpty (batch * m * p))

theorem output_size (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n)) (B : Vector Binary32 (batch * n * p))
    (packedB : Vector (Tile n) (batch * R15ThinPairs.groups p)) :
    (output batch m n p A B packedB).size = batch * m * p := by
  unfold output
  exact RowStream.foldl_inv (batch * m) (row batch m n p A B packedB)
    (fun k (acc : Array Binary32) => acc.size = k * p)
    (by
      intro r acc h
      rw [row_size, h, Nat.add_mul]
      simp)
    (Array.mkEmpty (batch * m * p)) (by simp)

def guarded (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n)) (B : Vector Binary32 (batch * n * p)) :
    Vector Binary32 (batch * m * p) :=
  if A.toArray.all UnderflowZero.small && B.toArray.all UnderflowZero.small then
    UnderflowZero.zeros batch m p
  else if 2 ≤ p ∧ p ≤ 8 ∧ 1 < n ∧ 4 ≤ m then
    match packB batch n p B.toArray with
    | none => Submission.bmm batch m n p A B
    | some packedB => ⟨output batch m n p A B packedB,
        output_size batch m n p A B packedB⟩
  else Submission.bmm batch m n p A B

end Submission.R22FloatArrayB2Expected
