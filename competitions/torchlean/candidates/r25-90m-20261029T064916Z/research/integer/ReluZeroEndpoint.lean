import ContractExact

/- Original small ContractExact endpoint. NOT_COMPILED.
   For a guarded finite linear/conv branch with relu=true, the final activation
   erases the exact-zero sign policy. This does not weaken core dot or relu=false
   obligations, and supplies no prepared-value or total-exactness premise. -/
namespace R25ReluZeroEndpoint
open ExactRuntime

theorem reluW_posZero : reluW 0 = 0 := by decide

theorem reluW_negZero : reluW 0x80000000 = 0 := by decide

/-- An exact integer sum may use positive zero when its caller applies ReLU. -/
theorem act_finishWord_zero_policy (total exponent : Int) (negativeZero : Bool) :
    act true (finishWord total exponent negativeZero) =
      act true (finishWord total exponent false) := by
  by_cases h : total = 0
  · subst total
    cases negativeZero <;>
      simp [act, finishWord, reluW_posZero, reluW_negZero]
  · simp [finishWord, h]

end R25ReluZeroEndpoint
