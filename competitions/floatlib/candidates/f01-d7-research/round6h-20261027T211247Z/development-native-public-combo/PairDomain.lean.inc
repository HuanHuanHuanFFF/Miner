/- After B2 and exact e3b NativeCold runtime. NOT_RUN. -/
namespace Submission.R22NativeColdReview

theorem pairOK_normal (u v : UInt32) (h : R22NativeCold.pairOK u v = true) :
    R2W01b.NormalBand u ∧ R2W01b.NormalBand v := by
  have one (w : UInt32)
      (hw : (R2W01b.magnitude w - (0x20000000 : UInt32)).toNat < 1073741824) :
      R2W01b.NormalBand w := by
    have hb := (R2W01b.magnitude w).toNat_lt_size
    rw [UInt32.toNat_sub] at hw
    simp only [R2W01b.NormalBand, UInt32.le_iff_toNat_le, UInt32.lt_iff_toNat_lt]
    change (R2W01b.magnitude w).toNat < 4294967296 at hb
    change (3758096384 + (R2W01b.magnitude w).toNat) % 4294967296 < 1073741824 at hw
    change 201326592 <= (R2W01b.magnitude w).toNat ∧
      (R2W01b.magnitude w).toNat < 2139095040
    omega
  unfold R22NativeCold.pairOK at h
  change decide (((R2W01b.magnitude u - 0x20000000) |||
    (R2W01b.magnitude v - 0x20000000)) < (0x40000000 : UInt32)) = true at h
  simp only [decide_eq_true_eq, UInt32.lt_iff_toNat_lt, UInt32.toNat_or] at h
  exact ⟨one u (Nat.lt_of_le_of_lt Nat.left_le_or h),
    one v (Nat.lt_of_le_of_lt Nat.right_le_or h)⟩

end Submission.R22NativeColdReview
