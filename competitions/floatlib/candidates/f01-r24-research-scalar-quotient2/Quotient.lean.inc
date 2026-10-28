/-
R24 portable UInt64 quotient certificate. This is a helper-only probe;
the retained B2 public endpoints are unchanged.

The RNE expression in `rounded` is adapted from FloatLib Team's MIT-licensed
FloatLib/Kernels/FixedWord/Core/Runtime.lean, fixed revision
0d91825727839f597fd06b22fdd038ea21480f0c (blob71d1bf2462da2cf1d6eff8b8fc3580fb681400b4).
The candidate guess is arbitrary; no native floating-point equation is assumed.
-/
namespace Submission.R24QuotientCertificate

@[inline] def check (n d q : UInt64) : Bool :=
  if n < (0x2000000000000 : UInt64) ∧ 0 < d ∧
      d < (0x2000000 : UInt64) ∧ q < (0x2000000 : UInt64) then
    decide (q * d ≤ n) && decide (n - q * d < d)
  else false

@[inline] def rounded (n d q : UInt64) : UInt64 :=
  let remainder := n - q * d
  let complement := d - remainder
  if remainder < complement then q
  else if complement < remainder then q + 1
  else if q % 2 == 0 then q
  else q + 1

/-- The checked machine product/subtraction determine the exact quotient and remainder. -/
theorem checker_sound (n d q : UInt64) (h : check n d q = true) :
    q.toNat = n.toNat / d.toNat ∧
      (n - q * d).toNat = n.toNat % d.toNat := by
  have hfit : n < (0x2000000000000 : UInt64) ∧ 0 < d ∧
      d < (0x2000000 : UInt64) ∧ q < (0x2000000 : UInt64) := by
    by_contra hbad
    simp [check, hbad] at h
  have hchecks : q * d ≤ n ∧ n - q * d < d := by
    simpa only [check, if_pos hfit, Bool.and_eq_true, decide_eq_true_eq] using h
  have hdpos : 0 < d.toNat := UInt64.lt_iff_toNat_lt.mp hfit.2.1
  have hdcap : d.toNat < 33554432 := UInt64.lt_iff_toNat_lt.mp hfit.2.2.1
  have hqcap : q.toNat < 33554432 := UInt64.lt_iff_toNat_lt.mp hfit.2.2.2
  have hproduct50 : q.toNat * d.toNat < 1125899906842624 := by
    calc
      q.toNat * d.toNat < 33554432 * 33554432 := Nat.mul_lt_mul'' hqcap hdcap
      _ = 1125899906842624 := by decide
  have hproductFit : q.toNat * d.toNat < UInt64.size := by
    change q.toNat * d.toNat < 18446744073709551616
    omega
  have hproduct : (q * d).toNat = q.toNat * d.toNat := by
    rw [UInt64.toNat_mul, Nat.mod_eq_of_lt hproductFit]
  have hproductLe : q.toNat * d.toNat ≤ n.toNat := by
    have hh := UInt64.le_iff_toNat_le.mp hchecks.1
    simpa only [hproduct] using hh
  have hremainder : (n - q * d).toNat = n.toNat - q.toNat * d.toNat := by
    rw [UInt64.toNat_sub_of_le _ _ hchecks.1, hproduct]
  have hremainderLt : n.toNat - q.toNat * d.toNat < d.toNat := by
    have hh := UInt64.lt_iff_toNat_lt.mp hchecks.2
    simpa only [hremainder] using hh
  have hdecomposition :
      q.toNat * d.toNat + (n.toNat - q.toNat * d.toNat) = n.toNat := by omega
  have hunique : n.toNat / d.toNat = q.toNat ∧
      n.toNat % d.toNat = n.toNat - q.toNat * d.toNat :=
    (Nat.div_mod_unique hdpos).2 <| by
      refine ⟨?_, hremainderLt⟩
      simpa only [Nat.add_comm, Nat.mul_comm] using hdecomposition
  exact ⟨hunique.1.symm, hremainder.trans hunique.2.symm⟩

/-- A checked guess can feed the existing word RNE expression without performing division. -/
theorem rounded_toNat (n d q : UInt64) (h : check n d q = true) :
    (rounded n d q).toNat = FloatLib.Numerics.roundQuotientEven n.toNat d.toNat := by
  have hfit : n < (0x2000000000000 : UInt64) ∧ 0 < d ∧
      d < (0x2000000 : UInt64) ∧ q < (0x2000000 : UInt64) := by
    by_contra hbad
    simp [check, hbad] at h
  have hqr := checker_sound n d q h
  have hquotient : q = n / d := by
    apply UInt64.toNat_inj.mp
    simpa only [UInt64.toNat_div] using hqr.1
  have hremainder : n - q * d = n % d := by
    apply UInt64.toNat_inj.mp
    simpa only [UInt64.toNat_mod] using hqr.2
  have hden : d ≠ 0 := by
    intro hzero
    have hpositive : 0 < d.toNat := UInt64.lt_iff_toNat_lt.mp hfit.2.1
    have hzeroNat : d.toNat = 0 := by
      simpa only [UInt64.toNat_zero] using congrArg UInt64.toNat hzero
    omega
  have hqcap : q.toNat < 33554432 := UInt64.lt_iff_toNat_lt.mp hfit.2.2.2
  have hquotientFit : n.toNat / d.toNat + 1 < 2 ^ 64 := by
    rw [← hqr.1]
    change q.toNat + 1 < 18446744073709551616
    omega
  have hword : rounded n d q = FloatLib.Numerics.FixedWord.roundQuotientEven n d := by
    unfold rounded
    rw [hremainder, hquotient]
    simp only [FloatLib.Numerics.FixedWord.roundQuotientEven, beq_iff_eq, hden, ite_false]
  rw [hword]
  exact FloatLib.Numerics.FixedWord.roundQuotientEven_toNat n d hden hquotientFit

end Submission.R24QuotientCertificate
