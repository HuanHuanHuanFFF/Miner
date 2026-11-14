/- NOT_RUN: one k2 loop interface on unchanged B2 storage.
   No public BMM integration, source-order floating operations only. -/
namespace Submission.R22PairK2
open FloatLib.Floats Competition

def loop (n baseA : Nat) (A : Array Binary32) (packed : Vector R15PackedB2.B2 n)
    (k : Nat) (s0 s1 : Float32) : R15ThinPairs.F2 :=
  if hk1 : k + 1 < n then
    have hk : k < n := by omega
    let a0 := ExecFloat.Binary.toFloat32 (A.getD (baseA + k) posZero)
    let b0 := packed.get ⟨k, hk⟩
    let p00 := a0 * b0.s0
    let p01 := a0 * b0.s1
    let a1 := ExecFloat.Binary.toFloat32 (A.getD (baseA + (k + 1)) posZero)
    let b1 := packed.get ⟨k + 1, hk1⟩
    let p10 := a1 * b1.s0
    let p11 := a1 * b1.s1
    loop n baseA A packed (k + 2) ((s0 + p00) + p10) ((s1 + p01) + p11)
  else if hk : k < n then
    let a := ExecFloat.Binary.toFloat32 (A.getD (baseA + k) posZero)
    let b := packed.get ⟨k, hk⟩
    ⟨s0 + a * b.s0, s1 + a * b.s1⟩
  else ⟨s0, s1⟩
termination_by n - k
decreasing_by omega

def run (n baseA : Nat) (A : Array Binary32) (packed : Vector R15PackedB2.B2 n) :
    R15ThinPairs.F2 :=
  loop n baseA A packed 0 Packed10.zero32 Packed10.zero32

end Submission.R22PairK2
