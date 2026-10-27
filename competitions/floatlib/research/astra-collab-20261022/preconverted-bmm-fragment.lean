namespace Preconverted

def floats (x : Array Binary32) : Array Float32 :=
  x.map ExecFloat.Binary.toFloat32

theorem getD_floats (x : Array Binary32) (i : Nat) :
    (floats x).getD i (Float32.ofBits 0) =
      ExecFloat.Binary.toFloat32 (x.getD i posZero) := by
  by_cases h : i < x.size
  · simp [floats, Array.getD, h]
  · simp [floats, Array.getD, h] <;> rfl

/-- Inputs are converted once per full bmm call, not once per multiply-add. -/
def dotLoop (n baseA baseB p : Nat) (A B : Array Float32)
    (k : Nat) (acc : Float32) : Float32 :=
  if hk : k < n then
    let fa := A.getD (baseA + k) (Float32.ofBits 0)
    let fb := B.getD (baseB + k * p) (Float32.ofBits 0)
    dotLoop n baseA baseB p A B (k + 1) (acc + fa * fb)
  else acc
termination_by n - k

theorem dotLoop_map_eq (n baseA baseB p : Nat) (A B : Array Binary32)
    (k : Nat) (acc : Float32) :
    dotLoop n baseA baseB p (floats A) (floats B) k acc =
      NativeFinal.dotLoop n baseA baseB p A B k acc := by
  rw [dotLoop, NativeFinal.dotLoop]
  split
  · rename_i hk
    simp only [dif_pos hk, if_pos hk, getD_floats]
    exact dotLoop_map_eq n baseA baseB p A B (k + 1)
      (acc + ExecFloat.Binary.toFloat32 (A.getD (baseA + k) posZero) *
        ExecFloat.Binary.toFloat32 (B.getD (baseB + k * p) posZero))
  · rename_i hk
    simp only [dif_neg hk, if_neg hk]
termination_by n - k

def dot (n baseA baseB p : Nat) (A B : Array Binary32)
    (AF BF : Array Float32) : Binary32 :=
  let result := dotLoop n baseA baseB p AF BF 0 (Float32.ofBits 0)
  if hf : result.isFinite = true then ExecFloat.Binary.ofFloat32 result
  else Fin.foldl n
    (fun a i => add a (mul (A.getD (baseA + i.val) posZero)
      (B.getD (baseB + i.val * p) posZero))) posZero

theorem dot_map_eq (n baseA baseB p : Nat) (A B : Array Binary32) :
    dot n baseA baseB p A B (floats A) (floats B) =
      NativeFinal.dot n baseA baseB p A B := by
  unfold dot NativeFinal.dot
  rw [dotLoop_map_eq]

end Preconverted
