namespace Submission.RowOutput

open FloatLib.Floats Competition

def row (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (b : Fin batch) (i : Fin m)
    (tiles : Vector Packed10.F10 (Packed10.groups p)) : Vector Binary32 p :=
  let baseA := (b.val * m + i.val) * n
  let baseB := b.val * n * p
  Vector.ofFn fun j =>
    let g : Fin (Packed10.groups p) :=
      ⟨j.val / 10, Packed10.groups_pos_of_col p j.val j.isLt⟩
    let l : Fin 10 := ⟨j.val % 10, Nat.mod_lt _ (by decide)⟩
    Packed10.finish n baseA (baseB + j.val) p A.toArray B.toArray
      (Packed10.lane (tiles.get g) l)

def output (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (tiles : Vector (Vector (Vector Packed10.F10 (Packed10.groups p)) m) batch) :
    Vector Binary32 (batch * m * p) :=
  ((Vector.ofFn fun b : Fin batch =>
    let batchTiles := tiles.get b
    (Vector.ofFn fun i : Fin m => row batch m n p A B b i (batchTiles.get i)).flatten
  ).flatten).cast (Nat.mul_assoc batch m p).symm

theorem output_eq (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (tiles : Vector (Vector (Vector Packed10.F10 (Packed10.groups p)) m) batch) :
    output batch m n p A B tiles =
      Vector.ofFn (Packed10.outputFromTiles batch m n p A B tiles) := by
  apply Vector.ext
  intro q hq
  have hmp : m * p ≠ 0 := by
    intro h
    have hq' : q < batch * (m * p) := by simpa only [Nat.mul_assoc] using hq
    rw [h, Nat.mul_zero] at hq'
    omega
  have hp : p ≠ 0 := by
    intro h
    apply hmp
    simp only [h, Nat.mul_zero]
  simp only [output, Vector.getElem_cast, Vector.getElem_flatten,
    Vector.getElem_ofFn, row, Packed10.outputFromTiles,
    Packed10.inlineDecodeC, hmp, hp, if_false]

def core (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Vector Binary32 (batch * m * p) :=
  let nativeA := A.toArray.map ExecFloat.Binary.toFloat32
  let packedB := Packed10.packB batch n p B
  let tiles := Packed10.tileResults batch m n p nativeA packedB
  output batch m n p A B tiles

theorem core_eq (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) :
    core batch m n p A B = Packed10.core batch m n p A B := by
  unfold core Packed10.core
  exact output_eq batch m n p A B _

end Submission.RowOutput

namespace Submission

open FloatLib.Floats Competition

def bmm (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Vector Binary32 (batch * m * p) :=
  if batch * m * p = 0 then referenceBmm batch m n p A B
  else if n = 0 then referenceBmm batch m n p A B
  else RowOutput.core batch m n p A B

theorem bmm_spec : ∀ (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)),
    (bmm batch m n p A B).get = bmmSpec batch m n p A.get B.get := by
  intro batch m n p A B
  have h : bmm batch m n p A B = bmmR4 batch m n p A B := by
    unfold bmm bmmR4
    split
    · rfl
    · split
      · rfl
      · exact RowOutput.core_eq batch m n p A B
  exact (congrArg (fun v : Vector Binary32 (batch * m * p) => v.get) h).trans
    (bmmR4_spec batch m n p A B)

end Submission
