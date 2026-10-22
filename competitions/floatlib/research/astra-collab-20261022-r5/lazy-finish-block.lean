namespace Submission.LazyFinish

open FloatLib.Floats Competition

def finishAt (m n p b i j : Nat) (Araw Braw : Array Binary32)
    (result : Float32) : Binary32 :=
  if hf : result.isFinite = true then ExecFloat.Binary.ofFloat32 result
  else
    let baseA := (b * m + i) * n
    let baseB := b * n * p + j
    Fin.foldl n
      (fun a k => Submission.add a
        (Submission.mul (Araw.getD (baseA + k.val) posZero)
          (Braw.getD (baseB + k.val * p) posZero))) posZero

theorem finishAt_eq (m n p b i j : Nat) (Araw Braw : Array Binary32)
    (result : Float32) :
    finishAt m n p b i j Araw Braw result =
      Packed10.finish n ((b * m + i) * n) (b * n * p + j) p Araw Braw result := by
  rfl

def output (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (tiles : Vector (Vector (Vector Packed10.F10 (Packed10.groups p)) m) batch)
    (q : Fin (batch * m * p)) : Binary32 :=
  let d := Packed10.inlineDecodeC m p q.val
  let b : Fin batch := ⟨d.1, (Packed10.decode_bounds batch m p q).1⟩
  let i : Fin m := ⟨d.2.1, (Packed10.decode_bounds batch m p q).2.1⟩
  let g : Fin (Packed10.groups p) :=
    ⟨d.2.2 / 10, Packed10.groups_pos_of_col p d.2.2 (Packed10.decode_bounds batch m p q).2.2⟩
  let l : Fin 10 := ⟨d.2.2 % 10, Nat.mod_lt _ (by decide)⟩
  finishAt m n p d.1 d.2.1 d.2.2 A.toArray B.toArray
    (Packed10.lane (((tiles.get b).get i).get g) l)

theorem output_eq (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (tiles : Vector (Vector (Vector Packed10.F10 (Packed10.groups p)) m) batch)
    (q : Fin (batch * m * p)) :
    output batch m n p A B tiles q = Packed10.outputFromTiles batch m n p A B tiles q := by
  rfl

def core (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Vector Binary32 (batch * m * p) :=
  let nativeA := A.toArray.map ExecFloat.Binary.toFloat32
  let packedB := Packed10.packB batch n p B
  let tiles := Packed10.tileResults batch m n p nativeA packedB
  Vector.ofFn (output batch m n p A B tiles)

theorem core_eq (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) :
    core batch m n p A B = Packed10.core batch m n p A B := by
  rfl

end Submission.LazyFinish

namespace Submission

open FloatLib.Floats Competition

def bmm (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Vector Binary32 (batch * m * p) :=
  if batch * m * p = 0 then referenceBmm batch m n p A B
  else if n = 0 then referenceBmm batch m n p A B
  else LazyFinish.core batch m n p A B

theorem bmm_spec : ∀ (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)),
    (bmm batch m n p A B).get = bmmSpec batch m n p A.get B.get := by
  intro batch m n p A B
  have h : bmm batch m n p A B = bmmR4 batch m n p A B := by rfl
  exact (congrArg (fun v : Vector Binary32 (batch * m * p) => v.get) h).trans
    (bmmR4_spec batch m n p A B)

end Submission
