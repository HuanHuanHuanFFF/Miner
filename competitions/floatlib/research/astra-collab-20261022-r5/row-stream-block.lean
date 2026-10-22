namespace Submission.RowStream

open FloatLib.Floats Competition

def core (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Vector Binary32 (batch * m * p) :=
  let nativeA := A.toArray.map ExecFloat.Binary.toFloat32
  let packedB := Packed10.packB batch n p B
  (Vector.ofFn fun r : Fin (batch * m) => r).flatMap fun r =>
    have hm : 0 < m := Nat.pos_of_lt_mul_left r.isLt
    let b : Fin batch := ⟨r.val / m, (Nat.div_lt_iff_lt_mul hm).2 r.isLt⟩
    let i : Fin m := ⟨r.val % m, Nat.mod_lt _ hm⟩
    let rowTiles := Vector.ofFn fun g : Fin (Packed10.groups p) =>
      Packed10Index.runDot n ((b.val * m + i.val) * n) nativeA ((packedB.get b).get g)
    RowOutput.row batch m n p A B b i rowTiles

theorem core_eq (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) :
    core batch m n p A B = Packed10.core batch m n p A B := by
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
  simp only [core, Packed10.core, Vector.getElem_flatMap,
    Vector.getElem_ofFn, RowOutput.row, Packed10.outputFromTiles,
    Packed10.inlineDecodeC, hmp, hp, if_false,
    Packed10.tileResults, Packed10.vector_get_ofFn,
    Nat.div_div_eq_div_mul, Nat.mul_comm p m,
    Nat.mod_mul_left_div_self, Nat.mod_mul_left_mod]

end Submission.RowStream

namespace Submission

open FloatLib.Floats Competition

def bmm (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Vector Binary32 (batch * m * p) :=
  if batch * m * p = 0 then referenceBmm batch m n p A B
  else if n = 0 then referenceBmm batch m n p A B
  else RowStream.core batch m n p A B

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
      · exact RowStream.core_eq batch m n p A B
  exact (congrArg (fun v : Vector Binary32 (batch * m * p) => v.get) h).trans
    (bmmR4_spec batch m n p A B)

end Submission
