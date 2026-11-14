/- Instantiates CacheAgreement from the exact Pair8 pack producer. NOT_RUN.
   Requires unchanged Pair8CacheProof and Pair8Projection definitions. -/
namespace Submission.R22Pair8
open FloatLib.Floats Competition

theorem cache_selected (batch n p : Nat) (B : Array Binary32)
    (row : Fin (batch * n)) (j : Fin p) :
    (if j.val % 2 = 0 then
      ((packB batch n p B).getD (row.val * groups p + j.val / 2) zeroPair).s0
     else ((packB batch n p B).getD (row.val * groups p + j.val / 2) zeroPair).s1) =
      ExecFloat.Binary.toFloat32 (B.getD (row.val * p + j.val) posZero) := by
  have hj := j.isLt
  have hg : j.val / 2 < groups p := by unfold groups; omega
  have hdiv := Nat.div_add_mod j.val 2
  by_cases he : j.val % 2 = 0
  · rw [if_pos he]
    have hcol : 2 * (j.val / 2) = j.val := by omega
    simpa only [hcol] using packB_s0 batch n p B row ⟨j.val / 2, hg⟩
  · rw [if_neg he]
    have hmod := Nat.mod_lt j.val (by decide : 0 < 2)
    have hcol : 2 * (j.val / 2) + 1 = j.val := by omega
    have hv : 2 * (j.val / 2) + 1 < p := by omega
    simpa only [Nat.add_assoc, hcol] using packB_s1 batch n p B row ⟨j.val / 2, hg⟩ hv

theorem cacheAgreement_packB (batch n p : Nat) (B : Array Binary32) (bi : Fin batch) :
    CacheAgreement n p (bi.val * n * p) (bi.val * n * groups p) B (packB batch n p B) := by
  intro k hk j
  have hb := Nat.mul_le_mul_right n (Nat.succ_le_of_lt bi.isLt)
  simp only [Nat.succ_mul] at hb
  have hrow : bi.val * n + k < batch * n := by omega
  have h := cache_selected batch n p B ⟨bi.val * n + k, hrow⟩ j
  have haddr : (bi.val * n + k) * p + j.val = bi.val * n * p + j.val + k * p := by
    rw [Nat.add_mul]
    omega
  rw [haddr] at h
  simpa only [Nat.add_mul] using h

end Submission.R22Pair8
