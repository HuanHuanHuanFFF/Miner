/- R24 single warm prefix. No prescan, record, callback or cold-to-hot edge.
   At the first non-warm input, the original loop resumes BEFORE that input.
   Ordinary pinned compilation and complete performance remain NOT_RUN. -/
namespace Submission.R24RepresentationWarmSum
open FloatLib.Floats Competition

def loop {n : Nat} (x : Vector Binary32 n) (count : USize)
    (hn : count.toNat = n) (k : USize) (acc : Float32) : Binary32 :=
  if hk : k < count then
    have hkn : k.toNat < n := by rw [← hn]; exact USize.lt_iff_toNat_lt.mp hk
    let q := x.toArray.uget k (by simpa only [x.size_toArray] using hkn)
    let u := q.raw.1
    let a := R2W01b.magnitude u
    if hl : (0x0bffffff : UInt32) ≤ a - 1 then
      if hh : a < (0x7f800000 : UInt32) then
        loop x count hn (k + 1) (acc + R2W01b.tableProduct u)
      else R7SinglePassSum.loop x count hn k acc
    else R7SinglePassSum.loop x count hn k acc
  else ExecFloat.Binary.ofFloat32 acc
termination_by count.toNat - k.toNat
decreasing_by all_goals exact Packed10Index.next_decreases (by assumption)

theorem loop_eq {n : Nat} (x : Vector Binary32 n) (count : USize)
    (hn : count.toNat = n) (k : USize) (acc : Float32) :
    loop x count hn k acc = R7SinglePassSum.loop x count hn k acc := by
  rw [loop]
  split
  · rename_i hk
    dsimp only
    split
    · rename_i hl
      split
      · rename_i hh
        conv_rhs => rw [R7SinglePassSum.loop]
        simp only [dif_pos hk]
        dsimp only
        simp only [dif_pos hl, dif_pos hh]
        exact loop_eq x count hn (k + 1) _
      · rfl
    · rfl
  · rename_i hk
    rw [R7SinglePassSum.loop, dif_neg hk]
termination_by count.toNat - k.toNat
decreasing_by all_goals exact Packed10Index.next_decreases (by assumption)

@[inline] def run {n : Nat} (x : Vector Binary32 n) : Binary32 :=
  if hn : n < USize.size then
    loop x (USize.ofNat n) (USize.toNat_ofNat_of_lt' hn) 0 (Float32.ofBits 0)
  else R7SinglePassSum.natLoop x 0 (Float32.ofBits 0)

theorem run_eq {n : Nat} (x : Vector Binary32 n) :
    run x = R7SinglePassSum.run x := by
  unfold run R7SinglePassSum.run
  split
  · exact loop_eq x _ _ _ _
  · rfl

theorem run_spec : ∀ (n : Nat) (x : Vector Binary32 n), run x = sumSpec x.get := by
  intro n x
  rw [run_eq]
  exact R7SinglePassSum.run_spec n x

end Submission.R24RepresentationWarmSum
