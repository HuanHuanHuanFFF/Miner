namespace Submission.R22ExtractorBoundary

theorem exact_scale_and_no_clamp_not_sufficient :
    let z : UInt32 := 50331648
    (z >>> 24).toNat = 3 ∧ (z >>> (z >>> 24)).toNat = 6291456 := by
  decide

theorem mantissa_only_check_not_sufficient :
    let z : UInt32 := 2281701376
    (z >>> 24).toNat = 136 ∧ (z >>> (z >>> 24)).toNat = 8912896 := by
  decide

end Submission.R22ExtractorBoundary
