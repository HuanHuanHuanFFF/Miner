/- Four early slots and one last slot only. NOT_RUN.
   This tests structural projection/seed normalization, not the512-entry bridge. -/
namespace Submission.R22FlatScale

theorem pick_block0_first_four (i : Nat) (hi : i<4) :
    pick block0 i = seed (UInt32.ofNat i) := by
  have hc : i=0 ∨ i=1 ∨ i=2 ∨ i=3 := by omega
  rcases hc with rfl | rfl | rfl | rfl <;> rfl

theorem pick_block3_last : pick block3 127 = seed (UInt32.ofNat (384+127)) := by
  rfl

end Submission.R22FlatScale
