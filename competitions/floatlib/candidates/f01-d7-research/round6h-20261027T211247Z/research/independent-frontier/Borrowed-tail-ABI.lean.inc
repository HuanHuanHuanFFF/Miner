/- ABI probe only; not a BMM algorithm. NOT_RUN. -/
namespace Submission.R22TailABI
open FloatLib.Floats Competition
@[inline] def done (q0 q1 q2 q3 q4 q5 q6 q7 : Float32) : R15ThinPairs.F2 :=
  ⟨((q0+q1)+q2)+q3, ((q4+q5)+q6)+q7⟩
mutual
@[noinline] def hot (n a0 a1 a2 a3 s : USize) (A B : @& Array UInt32) (k c : USize)
    (q0 q1 q2 q3 q4 q5 q6 q7 : Float32) : R15ThinPairs.F2 :=
  if h : k < n then
    let u := A.getD 0 0 ^^^ B.getD 0 0
    if (u &&& (1 : UInt32)) == (0 : UInt32) then
      let z := u.toFloat32
      hot n a0 a1 a2 a3 s A B (k+1) (c+s)
        (q0+z) (q1+z) (q2+z) (q3+z) (q4+z) (q5+z) (q6+z) (q7+z)
    else cold n a0 a1 a2 a3 s A B k c q0 q1 q2 q3 q4 q5 q6 q7
  else done q0 q1 q2 q3 q4 q5 q6 q7
termination_by 2*(n.toNat-k.toNat)+1
decreasing_by all_goals
  have d := Packed10Index.next_decreases (n := n) (k := k) (by assumption)
  omega
@[noinline] def cold (n a0 a1 a2 a3 s : USize) (A B : @& Array UInt32) (k c : USize)
    (q0 q1 q2 q3 q4 q5 q6 q7 : Float32) : R15ThinPairs.F2 :=
  if h : k < n then
    let z := Float32.ofBits (a0+a1+a2+a3+s+c).toUInt32
    hot n a0 a1 a2 a3 s A B (k+1) (c+s)
      (q0+z) (q1+z) (q2+z) (q3+z) (q4+z) (q5+z) (q6+z) (q7+z)
  else done q0 q1 q2 q3 q4 q5 q6 q7
termination_by 2*(n.toNat-k.toNat)
decreasing_by all_goals
  have d := Packed10Index.next_decreases (n := n) (k := k) (by assumption)
  omega
end
end Submission.R22TailABI
