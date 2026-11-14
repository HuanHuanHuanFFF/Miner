/- Direct field view of the executable midpoint arithmetic. -/
namespace Submission.R25Checker
open Submission.R25OrderKey

private theorem mag32_nat (q : UInt32) :
    (magnitude32 q).toNat = q.toNat % 2147483648 := by
  rw [magnitude32, UInt32.toNat_and]
  exact Nat.and_two_pow_sub_one_eq_mod q.toNat 31

private theorem e32_nat (q : UInt32) :
    (eWord q).toNat = (magnitude32 q).toNat / 8388608 := by
  rw [eWord, UInt32.toNat_and, UInt32.toNat_shiftRight]
  change ((magnitude32 q).toNat >>> 23) &&& (2 ^ 8 - 1) = _
  rw [Nat.and_two_pow_sub_one_eq_mod, Nat.shiftRight_eq_div_pow]
  have hm : (magnitude32 q).toNat < 2147483648 := by
    rw [mag32_nat]
    exact Nat.mod_lt _ (by decide)
  exact Nat.mod_eq_of_lt (by omega)

private theorem f32_nat (q : UInt32) :
    (fWord q).toNat = (magnitude32 q).toNat % 8388608 := by
  rw [fWord, UInt32.toNat_and]
  exact Nat.and_two_pow_sub_one_eq_mod (magnitude32 q).toNat 23

theorem mag32_fields (q : UInt32) :
    (magnitude32 q).toNat = (eWord q).toNat * 8388608 + (fWord q).toNat := by
  rw [e32_nat, f32_nat]
  omega

theorem minnormal_fields (q : UInt32) :
    magnitude32 q = 0x00800000 ↔ (eWord q).toNat = 1 ∧ (fWord q).toNat = 0 := by
  have hf := fWord_bound q
  constructor
  · intro h
    have hn := congrArg UInt32.toNat h
    rw [mag32_fields] at hn
    change (eWord q).toNat * 8388608 + (fWord q).toNat = 8388608 at hn
    omega
  · rintro ⟨he, hf⟩
    apply UInt32.toNat_inj.mp
    rw [mag32_fields, he, hf]
    decide

theorem delta_nat_fields (q : UInt32) :
    (delta q).toNat =
      if (eWord q).toNat = 1 ∧ (fWord q).toNat = 0 then 536870912 else 268435456 := by
  simp only [delta, beq_iff_eq, minnormal_fields]
  split <;> rfl

theorem above_nat_fields (q : UInt32) :
    (above q).toNat = ((eWord q).toNat + 896) * 4503599627370496 +
      (fWord q).toNat * 536870912 + 268435456 := by
  have he := eWord_bound q
  have hf := fWord_bound q
  rw [above, UInt64.toNat_add, base_nat]
  change (_ + 268435456) % 18446744073709551616 = _
  omega

theorem below_nat_fields (q : UInt32) :
    (below q).toNat = ((eWord q).toNat + 896) * 4503599627370496 +
      (fWord q).toNat * 536870912 - (delta q).toNat := by
  have hd := delta_bounds q
  have hbase := base_nat q
  have hle : delta q ≤ base q := by
    rw [UInt64.le_iff_toNat_le, hbase]
    omega
  change (base q - delta q).toNat = _
  rw [UInt64.toNat_sub_of_le _ _ hle, hbase]

theorem above_decode_fields (q : UInt32) :
    exponent (above q) = (eWord q).toNat + 896 ∧
    fraction (above q) = (fWord q).toNat * 536870912 + 268435456 := by
  have he := eWord_bound q
  have hf := fWord_bound q
  unfold exponent fraction
  rw [above_nat_fields]
  omega

theorem below_decode_fields_inner (q : UInt32) (hf0 : 0 < (fWord q).toNat) :
    exponent (below q) = (eWord q).toNat + 896 ∧
    fraction (below q) = (fWord q).toNat * 536870912 - 268435456 := by
  have he := eWord_bound q
  have hf := fWord_bound q
  have hn : ¬ ((eWord q).toNat = 1 ∧ (fWord q).toNat = 0) := by omega
  unfold exponent fraction
  rw [below_nat_fields, delta_nat_fields, if_neg hn]
  omega

theorem below_decode_fields_power (q : UInt32) (hf0 : (fWord q).toNat = 0)
    (he1 : (eWord q).toNat ≠ 1) :
    exponent (below q) = (eWord q).toNat + 895 ∧
    fraction (below q) = 4503599358935040 := by
  have he := eWord_bound q
  have hn : ¬ ((eWord q).toNat = 1 ∧ (fWord q).toNat = 0) := by omega
  unfold exponent fraction
  rw [below_nat_fields, delta_nat_fields, if_neg hn, hf0]
  omega

theorem below_decode_fields_minnormal (q : UInt32) (hf0 : (fWord q).toNat = 0)
    (he1 : (eWord q).toNat = 1) :
    exponent (below q) = 896 ∧ fraction (below q) = 4503599090499584 := by
  unfold exponent fraction
  rw [below_nat_fields, delta_nat_fields, if_pos ⟨he1, hf0⟩, he1, hf0]
  decide

end Submission.R25Checker
