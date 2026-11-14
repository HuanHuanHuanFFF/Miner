
namespace Submission.R25Checker
theorem finite64_eq_runtime (w : UInt64) :
    R25OrderKey.finite64 w = R24PortableF64.finite64 w := rfl
theorem orderKey_eq_runtime (w : UInt64) :
    R25OrderKey.orderKey w = R24PortableF64.orderKey w := rfl
theorem certify_eq_runtime (s r : Float) (sw : UInt64) (q : UInt32) :
    certify s r sw q = R24PortableF64.certify s r sw q := rfl
theorem actual_acceptance_bounds (s r : Float) (sw : UInt64) (q : UInt32)
    (h : R24PortableF64.certify s r sw q = true) :
    R25OrderKey.value (lowerWord q) < R25OrderKey.nativeValue (s - r) ∧
    R25OrderKey.nativeValue (s + r) < R25OrderKey.value (upperWord q) := by
  apply accepted_native_bounds s r sw q
  simpa only [certify_eq_runtime] using h
end Submission.R25Checker
