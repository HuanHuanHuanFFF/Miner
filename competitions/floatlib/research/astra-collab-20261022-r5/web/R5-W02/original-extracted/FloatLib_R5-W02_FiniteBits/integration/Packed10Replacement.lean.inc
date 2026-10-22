def finish (n baseA baseB p : Nat) (Araw Braw : Array Binary32)
    (result : Float32) : Binary32 :=
  let u := result.toBits
  if hf : R5W02.finiteBits u = true then ExecFloat.Binary.ofBits32 u
  else Fin.foldl n
    (fun a i => Submission.add a
      (Submission.mul (Araw.getD (baseA + i.val) posZero)
        (Braw.getD (baseB + i.val * p) posZero))) posZero

theorem finish_eq_original (n baseA baseB p : Nat) (Araw Braw : Array Binary32)
    (result : Float32) :
    finish n baseA baseB p Araw Braw result =
      (if hf : result.isFinite = true then ExecFloat.Binary.ofFloat32 result
       else Fin.foldl n
         (fun a i => Submission.add a
           (Submission.mul (Araw.getD (baseA + i.val) posZero)
             (Braw.getD (baseB + i.val * p) posZero))) posZero) := by
  exact R5W02.finish_expr_eq result _

theorem finish_eq_dot (n baseA baseB p : Nat) (Araw Braw : Array Binary32)
    (result : Float32)
    (hs : result = NativeFinal.dotLoop n baseA baseB p Araw Braw 0 zero32) :
    finish n baseA baseB p Araw Braw result =
      NativeFinal.dot n baseA baseB p Araw Braw := by
  rw [finish_eq_original, hs] <;> rfl

