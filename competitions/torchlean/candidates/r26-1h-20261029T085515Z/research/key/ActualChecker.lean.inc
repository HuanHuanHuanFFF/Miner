/- Exact expression adapter for the R24 PortableF64 checker.
   Append after R25OrderKey; arithmetic behavior is unchanged. -/
namespace Submission.R25Checker
open Submission.R25OrderKey

@[inline] def magnitude32 (q : UInt32) : UInt32 := q &&& 0x7fffffff
@[inline] def eWord (q : UInt32) : UInt32 := (magnitude32 q >>> 23) &&& 255
@[inline] def fWord (q : UInt32) : UInt32 := magnitude32 q &&& 0x7fffff
@[inline] def base (q : UInt32) : UInt64 :=
  ((eWord q).toUInt64 + 896) <<< 52 ||| ((fWord q).toUInt64 <<< 29)
@[inline] def delta (q : UInt32) : UInt64 :=
  if magnitude32 q == 0x00800000 then 0x20000000 else 0x10000000
@[inline] def below (q : UInt32) : UInt64 := base q - delta q
@[inline] def above (q : UInt32) : UInt64 := base q + 0x10000000
@[inline] def negative32 (q : UInt32) : Bool := q &&& 0x80000000 != 0
@[inline] def lowerWord (q : UInt32) : UInt64 :=
  if negative32 q then above q ||| 0x8000000000000000 else below q
@[inline] def upperWord (q : UInt32) : UInt64 :=
  if negative32 q then below q ||| 0x8000000000000000 else above q

@[inline] def certify (sum radius : Float) (sumWord : UInt64) (guess : UInt32) : Bool :=
  if eWord guess == 0 || eWord guess == 255 then false
  else
    let lowerEndpoint := (sum - radius).toBits
    let upperEndpoint := (sum + radius).toBits
    if !(finite64 sumWord && (finite64 lowerEndpoint && finite64 upperEndpoint)) then false
    else
      decide (orderKey (lowerWord guess) < orderKey lowerEndpoint) &&
        decide (orderKey upperEndpoint < orderKey (upperWord guess))

/-- Guards and inequalities are extracted from the actual expression. -/
theorem accepted_components (sum radius : Float) (sumWord : UInt64) (q : UInt32)
    (h : certify sum radius sumWord q = true) :
    eWord q ≠ 0 ∧ eWord q ≠ 255 ∧ finite64 sumWord = true ∧
    finite64 (sum - radius).toBits = true ∧ finite64 (sum + radius).toBits = true ∧
    orderKey (lowerWord q) < orderKey (sum - radius).toBits ∧
    orderKey (sum + radius).toBits < orderKey (upperWord q) := by
  unfold certify at h
  split at h
  · simp at h
  next he =>
    have he' : eWord q ≠ 0 ∧ eWord q ≠ 255 := by
      simpa only [Bool.or_eq_true, beq_iff_eq, not_or] using he
    dsimp only at h
    split at h
    · simp at h
    next hf =>
      have hf' : finite64 sumWord = true ∧
          finite64 (sum - radius).toBits = true ∧
          finite64 (sum + radius).toBits = true := by
        cases hsum : finite64 sumWord <;>
          cases hlo : finite64 (sum - radius).toBits <;>
          cases hhi : finite64 (sum + radius).toBits <;> simp_all
      have hk : orderKey (lowerWord q) < orderKey (sum - radius).toBits ∧
          orderKey (sum + radius).toBits < orderKey (upperWord q) := by
        simpa only [Bool.and_eq_true, decide_eq_true_eq] using h
      exact ⟨he'.1, he'.2, hf'.1, hf'.2.1, hf'.2.2, hk.1, hk.2⟩

private theorem eWord_bound (q : UInt32) : (eWord q).toNat < 256 := by
  rw [eWord, UInt32.toNat_and]
  change (magnitude32 q >>> 23).toNat &&& (2 ^ 8 - 1) < 2 ^ 8
  rw [Nat.and_two_pow_sub_one_eq_mod]
  exact Nat.mod_lt _ (by decide)

private theorem fWord_bound (q : UInt32) : (fWord q).toNat < 8388608 := by
  rw [fWord, UInt32.toNat_and]
  change (magnitude32 q).toNat &&& (2 ^ 23 - 1) < 2 ^ 23
  rw [Nat.and_two_pow_sub_one_eq_mod]
  exact Nat.mod_lt _ (by decide)

private theorem base_nat (q : UInt32) :
    (base q).toNat =
      ((eWord q).toNat + 896) * 4503599627370496 +
        (fWord q).toNat * 536870912 := by
  have he := eWord_bound q
  have hf := fWord_bound q
  have hE : ((((eWord q).toUInt64 + 896) <<< 52) : UInt64).toNat =
      ((eWord q).toNat + 896) * 4503599627370496 := by
    simp only [UInt64.toNat_shiftLeft, UInt64.toNat_add, UInt32.toNat_toUInt64]
    change ((((eWord q).toNat + 896) % 18446744073709551616) <<< 52) %
      18446744073709551616 = _
    rw [Nat.shiftLeft_eq]
    omega
  have hF : (((fWord q).toUInt64 <<< 29) : UInt64).toNat =
      (fWord q).toNat * 536870912 := by
    simp only [UInt64.toNat_shiftLeft, UInt32.toNat_toUInt64]
    change ((fWord q).toNat <<< 29) % 18446744073709551616 = _
    rw [Nat.shiftLeft_eq]
    omega
  rw [base, UInt64.toNat_or, hE, hF]
  have hsmall : (fWord q).toNat * 536870912 < 2 ^ 52 := by omega
  simpa only [Nat.mul_comm 4503599627370496, Nat.add_comm] using
    (Nat.two_pow_add_eq_or_of_lt hsmall ((eWord q).toNat + 896)).symm

private theorem delta_bounds (q : UInt32) :
    268435456 ≤ (delta q).toNat ∧ (delta q).toNat ≤ 536870912 := by
  unfold delta
  split <;> decide

/-- The unsigned midpoint words lie strictly inside finite positive binary64.
The minimum-normal special decrement is included in the bound. -/
theorem unsigned_bounds (q : UInt32) (he0 : eWord q ≠ 0) (he255 : eWord q ≠ 255) :
    0 < (below q).toNat ∧ (below q).toNat < 9218868437227405312 ∧
    0 < (above q).toNat ∧ (above q).toNat < 9218868437227405312 := by
  have he := eWord_bound q
  have hf := fWord_bound q
  have hE0 : (eWord q).toNat ≠ 0 := by
    intro h
    apply he0
    apply UInt32.toNat_inj.mp
    exact h
  have hE255 : (eWord q).toNat ≠ 255 := by
    intro h
    apply he255
    apply UInt32.toNat_inj.mp
    exact h
  have hd := delta_bounds q
  have hbase := base_nat q
  have hdelta : delta q ≤ base q := by
    rw [UInt64.le_iff_toNat_le, hbase]
    omega
  have hbelow : (below q).toNat = (base q).toNat - (delta q).toNat := by
    exact UInt64.toNat_sub_of_le _ _ hdelta
  have habove : (above q).toNat = (base q).toNat + 268435456 := by
    rw [above, UInt64.toNat_add]
    change ((base q).toNat + 268435456) % 18446744073709551616 = _
    omega
  rw [hbelow, habove]
  omega

private theorem signed_magnitude (w : UInt64) (h : w.toNat < 9223372036854775808) :
    magnitude (w ||| 0x8000000000000000) = w.toNat := by
  have hw : (w ||| 0x8000000000000000).toNat =
      9223372036854775808 + w.toNat := by
    rw [UInt64.toNat_or, Nat.or_comm]
    have hp : w.toNat < 2 ^ 63 := h
    simpa only [Nat.mul_one] using (Nat.two_pow_add_eq_or_of_lt hp 1).symm
  unfold magnitude
  rw [hw]
  omega

private theorem unsigned_magnitude (w : UInt64) (h : w.toNat < 9223372036854775808) :
    magnitude w = w.toNat := Nat.mod_eq_of_lt h

private theorem finite_of_magnitude (w : UInt64)
    (h : magnitude w < 9218868437227405312) : finite64 w = true := by
  apply (finite64_iff_exp w).mpr
  rw [← magnitude_div]
  omega

theorem midpoint_finite_nonzero (q : UInt32) (he0 : eWord q ≠ 0) (he255 : eWord q ≠ 255) :
    finite64 (lowerWord q) = true ∧ finite64 (upperWord q) = true ∧
    magnitude (lowerWord q) ≠ 0 ∧ magnitude (upperWord q) ≠ 0 := by
  have hb := unsigned_bounds q he0 he255
  have hlo : (below q).toNat < 9223372036854775808 := by omega
  have hhi : (above q).toNat < 9223372036854775808 := by omega
  have hm : 0 < magnitude (lowerWord q) ∧ magnitude (lowerWord q) < 9218868437227405312 ∧
      0 < magnitude (upperWord q) ∧ magnitude (upperWord q) < 9218868437227405312 := by
    cases hs : negative32 q <;>
      simp only [lowerWord, upperWord, hs, Bool.false_eq_true, ite_false, ite_true,
        unsigned_magnitude _ hlo, unsigned_magnitude _ hhi,
        signed_magnitude _ hlo, signed_magnitude _ hhi] <;> omega
  exact ⟨finite_of_magnitude _ hm.2.1, finite_of_magnitude _ hm.2.2.2,
    Nat.ne_of_gt hm.1, Nat.ne_of_gt hm.2.2.1⟩

/-- Actual checker acceptance gives strict real containment of its computed
native endpoints inside its computed raw midpoint words. No producer premise,
no externally assumed midpoint finiteness/nonzero, and no Float.lt substitution. -/
theorem accepted_native_bounds (sum radius : Float) (sumWord : UInt64) (q : UInt32)
    (h : certify sum radius sumWord q = true) :
    value (lowerWord q) < nativeValue (sum - radius) ∧
      nativeValue (sum + radius) < value (upperWord q) := by
  obtain ⟨he0, he255, _, hlo, hhi, hlkey, hukey⟩ :=
    accepted_components sum radius sumWord q h
  obtain ⟨hl, hu, hlnz, hunz⟩ := midpoint_finite_nonzero q he0 he255
  exact orderKey_native_endpoints _ _ _ _ hl hu hlo hhi hlnz hunz hlkey hukey

end Submission.R25Checker

