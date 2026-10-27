/- Source proposal only: reuse the already present exact native self-BEq theorem.
   The opportunity is one fewer foreign classifier call, not a new UInt32 ABI. -/
namespace Submission.R11FinishWord
open FloatLib.Floats Competition

@[inline] def finishWord (n baseA baseB p : Nat) (A B : Array Binary32)
    (x : Float32) : UInt32 :=
  if R7W04.nonNaN x then x.toBits
  else (R7NaNReplay.replayEarly n baseA baseB p A B).raw.1

theorem finishWord_eq_raw (n baseA baseB p : Nat) (A B : Array Binary32)
    (x : Float32) :
    finishWord n baseA baseB p A B x = (Packed10.finish n baseA baseB p A B x).raw.1 := by
  unfold finishWord Packed10.finish
  rw [R7W04.nonNaN_eq_not_isNaN]
  cases hn : x.isNaN <;> simp [hn] <;> rfl

end Submission.R11FinishWord
