/- R20 cost discriminator. Public B2 remains unchanged. The raw pair recurrence
   and finish/replay are retained; only the terminal result is consumed directly. -/
namespace Submission.R20TerminalPair
open FloatLib.Floats Competition

def loopPair (n baseA baseB p : Nat) (A B : Array Binary32)
    (k : Nat) (s0 s1 : Float32) : R15ThinPairs.F2 :=
  if hk : k < n then
    let a := ExecFloat.Binary.toFloat32 (A.getD (baseA + k) posZero)
    let b0 := ExecFloat.Binary.toFloat32 (B.getD (baseB + k * p) posZero)
    let b1 := ExecFloat.Binary.toFloat32 (B.getD (baseB + 1 + k * p) posZero)
    loopPair n baseA baseB p A B (k + 1) (s0 + a * b0) (s1 + a * b1)
  else ⟨s0, s1⟩
termination_by n - k

theorem loopPair_s0 (n baseA baseB p : Nat) (A B : Array Binary32)
    (k : Nat) (s0 s1 : Float32) :
    (loopPair n baseA baseB p A B k s0 s1).s0 =
      NativeFinal.dotLoop n baseA baseB p A B k s0 := by
  by_cases hk : k < n
  · rw [loopPair, NativeFinal.dotLoop]
    simp only [dif_pos hk]
    exact loopPair_s0 n baseA baseB p A B (k + 1) _ _
  · rw [loopPair, NativeFinal.dotLoop]
    simp only [dif_neg hk]
termination_by n - k

theorem loopPair_s1 (n baseA baseB p : Nat) (A B : Array Binary32)
    (k : Nat) (s0 s1 : Float32) :
    (loopPair n baseA baseB p A B k s0 s1).s1 =
      NativeFinal.dotLoop n baseA (baseB + 1) p A B k s1 := by
  by_cases hk : k < n
  · rw [loopPair, NativeFinal.dotLoop]
    simp only [dif_pos hk]
    exact loopPair_s1 n baseA baseB p A B (k + 1) _ _
  · rw [loopPair, NativeFinal.dotLoop]
    simp only [dif_neg hk]
termination_by n - k

@[inline] def emit2 (n baseA baseB p : Nat) (A B : Array Binary32)
    (out : Array Binary32) (s0 s1 : Float32) : Array Binary32 :=
  let out := out.push (Packed10.finish n baseA baseB p A B s0)
  out.push (Packed10.finish n baseA (baseB + 1) p A B s1)

def loopEmit (n baseA baseB p : Nat) (A B : Array Binary32)
    (out : Array Binary32) (k : Nat) (s0 s1 : Float32) : Array Binary32 :=
  if hk : k < n then
    let a := ExecFloat.Binary.toFloat32 (A.getD (baseA + k) posZero)
    let b0 := ExecFloat.Binary.toFloat32 (B.getD (baseB + k * p) posZero)
    let b1 := ExecFloat.Binary.toFloat32 (B.getD (baseB + 1 + k * p) posZero)
    loopEmit n baseA baseB p A B out (k + 1) (s0 + a * b0) (s1 + a * b1)
  else emit2 n baseA baseB p A B out s0 s1
termination_by n - k

theorem loopEmit_eq (n baseA baseB p : Nat) (A B : Array Binary32)
    (out : Array Binary32) (k : Nat) (s0 s1 : Float32) :
    loopEmit n baseA baseB p A B out k s0 s1 =
      let r := loopPair n baseA baseB p A B k s0 s1
      emit2 n baseA baseB p A B out r.s0 r.s1 := by
  by_cases hk : k < n
  · rw [loopEmit, loopPair]
    simp only [dif_pos hk]
    exact loopEmit_eq n baseA baseB p A B out (k + 1) _ _
  · rw [loopEmit, loopPair]
    simp only [dif_neg hk]
termination_by n - k

@[noinline] def control (n baseA baseB p : Nat) (A B : Array Binary32)
    (out : Array Binary32) : Array Binary32 :=
  let r := loopPair n baseA baseB p A B 0 Packed10.zero32 Packed10.zero32
  emit2 n baseA baseB p A B out r.s0 r.s1

@[noinline] def terminal (n baseA baseB p : Nat) (A B : Array Binary32)
    (out : Array Binary32) : Array Binary32 :=
  loopEmit n baseA baseB p A B out 0 Packed10.zero32 Packed10.zero32

theorem terminal_eq_control (n baseA baseB p : Nat) (A B : Array Binary32)
    (out : Array Binary32) : terminal n baseA baseB p A B out = control n baseA baseB p A B out :=
  loopEmit_eq n baseA baseB p A B out 0 Packed10.zero32 Packed10.zero32

end Submission.R20TerminalPair
