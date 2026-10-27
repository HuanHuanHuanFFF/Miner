import ContractTensor

namespace Submission.LowScale

/-- The subnormal branch, with the existing rounding and packing unchanged. -/
@[inline] def roundLow (sign : Bool) (product scale : UInt64) : UInt32 :=
  if product == 0 then
    if sign then 0x80000000 else 0
  else
    let fraction := FastMul.rseAny product (149 - scale)
    if fraction == 0 then
      if sign then 0x80000000 else 0
    else if fraction == 0x800000 then
      FastMul.mkW sign 1 0
    else
      FastMul.mkW sign 0 fraction.toUInt32

theorem roundLow_eq (sign : Bool) (product scale : UInt64)
    (hp : product.toNat < 2 ^ 48) (hs : scale.toNat ≤ 123) :
    roundLow sign product scale = FastMul.roundP sign product scale := by
  by_cases hz : product = 0
  · subst product
    simp [roundLow, FastMul.roundP]
  · have hn : product.toNat ≠ 0 := by
      intro h
      apply hz
      apply UInt64.toNat_inj.mp
      exact h
    have hl : (FastMul.fastLog2 product).toNat < 48 := by
      rw [FastMul.fastLog2_eq]
      change product.toNat.log2 < 48
      exact (Nat.log2_lt hn).mpr hp
    have hposition : FastMul.fastLog2 product + scale < (172 : UInt64) := by
      rw [UInt64.lt_iff_toNat_lt, UInt64.toNat_add]
      change ((FastMul.fastLog2 product).toNat + scale.toNat) %
        18446744073709551616 < 172
      rw [Nat.mod_eq_of_lt (by omega)]
      omega
    have hscale : scale < (149 : UInt64) := by
      rw [UInt64.lt_iff_toNat_lt]
      change scale.toNat < 149
      omega
    simp only [roundLow, FastMul.roundP, beq_iff_eq, hz, ite_false,
      hposition, ite_true, hscale]

/-- The word guards make the selector equal to the old rounder on every input. -/
@[inline] def roundSelect (sign : Bool) (product scale : UInt64) : UInt32 :=
  if h : product < (0x1000000000000 : UInt64) ∧ scale ≤ (123 : UInt64) then
    roundLow sign product scale
  else FastMul.roundP sign product scale

theorem roundSelect_eq (sign : Bool) (product scale : UInt64) :
    roundSelect sign product scale = FastMul.roundP sign product scale := by
  unfold roundSelect
  split
  · rename_i h
    apply roundLow_eq
    · simpa only [UInt64.lt_iff_toNat_lt] using h.1
    · simpa only [UInt64.le_iff_toNat_le] using h.2
  · rfl

end Submission.LowScale
