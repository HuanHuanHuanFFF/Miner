/- New execution adapter only. All declarations are NOT_RUN. -/
namespace Submission.NativeFinal

open FloatLib.Floats Competition

/- This equality places no condition on the seed, input words or native result.
It connects the actual Nat loop to exactly the same ordered native Fin fold;
it does not establish any raw-carrier refinement by itself. -/
theorem dotLoop_eq_nativeFold (n baseA baseB p : Nat) (A B : Array Binary32)
    (k : Nat) (acc : Float32) :
    dotLoop n baseA baseB p A B k acc =
      Fin.foldl.loop n
        (fun a i => a +
          ExecFloat.Binary.toFloat32 (A.getD (baseA + i.val) posZero) *
          ExecFloat.Binary.toFloat32 (B.getD (baseB + i.val * p) posZero))
        acc k := by
  rw [dotLoop, Fin.foldl.loop]
  split
  · rename_i hk
    exact dotLoop_eq_nativeFold n baseA baseB p A B (k + 1)
      (acc + ExecFloat.Binary.toFloat32 (A.getD (baseA + k) posZero) *
        ExecFloat.Binary.toFloat32 (B.getD (baseB + k * p) posZero))
  · rfl
termination_by n - k
decreasing_by omega

theorem dotLoop_zero_eq_nativeFold (n baseA baseB p : Nat)
    (A B : Array Binary32) (acc : Float32) :
    dotLoop n baseA baseB p A B 0 acc =
      Fin.foldl n
        (fun a i => a +
          ExecFloat.Binary.toFloat32 (A.getD (baseA + i.val) posZero) *
          ExecFloat.Binary.toFloat32 (B.getD (baseB + i.val * p) posZero))
        acc :=
  dotLoop_eq_nativeFold n baseA baseB p A B 0 acc

end Submission.NativeFinal
