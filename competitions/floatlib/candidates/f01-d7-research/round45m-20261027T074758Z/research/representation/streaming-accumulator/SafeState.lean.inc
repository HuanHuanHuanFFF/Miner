/- R20 next-round interface, not a public BMM implementation. -/
namespace Submission.R20StreamingState
open FloatLib.Floats Competition

abbrev Cell := R15ThinPairs.F2

@[inline] def updateCell (a0 a1 b : Float32) (s : Cell) : Cell :=
  { s with s0 := s.s0 + a0 * b, s1 := s.s1 + a1 * b }

theorem updateCell_s0 (a0 a1 b : Float32) (s : Cell) :
    (updateCell a0 a1 b s).s0 = s.s0 + a0 * b := rfl

theorem updateCell_s1 (a0 a1 b : Float32) (s : Cell) :
    (updateCell a0 a1 b s).s1 = s.s1 + a1 * b := rfl

@[inline] def updateSlot (state : Array Cell) (j : Nat)
    (a0 a1 b : Float32) : Array Cell :=
  state.modify j (updateCell a0 a1 b)

theorem updateSlot_size (state : Array Cell) (j : Nat) (a0 a1 b : Float32) :
    (updateSlot state j a0 a1 b).size = state.size := by
  simp only [updateSlot, Array.size_modify]

theorem updateSlot_get? (state : Array Cell) (j i : Nat) (a0 a1 b : Float32) :
    (updateSlot state j a0 a1 b)[i]? =
      if j = i then state[i]?.map (updateCell a0 a1 b) else state[i]? := by
  simpa only [updateSlot] using
    (Array.getElem?_modify (xs := state) (i := j) (f := updateCell a0 a1 b) (j := i))

def projection0 (state : Array Cell) (j : Nat) : Option Float32 :=
  state[j]?.map (fun s => s.s0)

def projection1 (state : Array Cell) (j : Nat) : Option Float32 :=
  state[j]?.map (fun s => s.s1)

def initial (p : Nat) : Array Cell :=
  Array.replicate p (⟨Packed10.zero32, Packed10.zero32⟩ : Cell)

def advance (p k baseA0 baseA1 baseB : Nat) (A B : Array Binary32)
    (state : Array Cell) : Array Cell :=
  let a0 := ExecFloat.Binary.toFloat32 (A.getD (baseA0 + k) posZero)
  let a1 := ExecFloat.Binary.toFloat32 (A.getD (baseA1 + k) posZero)
  let rowB := baseB + k * p
  Fin.foldl p (fun state j =>
    let b := ExecFloat.Binary.toFloat32 (B.getD (rowB + j.val) posZero)
    updateSlot state j.val a0 a1 b) state

def Represents (p k baseA0 baseA1 baseB : Nat) (A B : Array Binary32)
    (state : Array Cell) : Prop :=
  state.size = p ∧ ∀ j : Fin p,
    projection0 state j.val = some
      (NativeFinal.dotLoop k baseA0 (baseB + j.val) p A B 0 Packed10.zero32) ∧
    projection1 state j.val = some
      (NativeFinal.dotLoop k baseA1 (baseB + j.val) p A B 0 Packed10.zero32)

end Submission.R20StreamingState
