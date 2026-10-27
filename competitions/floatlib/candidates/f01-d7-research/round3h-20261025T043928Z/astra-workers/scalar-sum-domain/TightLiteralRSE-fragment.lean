/- R15 optional reserve. Replace only LowScale.roundSelect and roundSelect_eq
   by this block, inside namespace Submission.LowScale. Keep roundLow and the
   original <=123 roundLow_eq unchanged. New elaboration/full gate NOT_RUN. -/

theorem roundLow_eq_tight (sign : Bool) (product scale : UInt64) (width : Nat)
    (hp : product.toNat < 2 ^ width)
    (hb : width + scale.toNat ≤ 172) (hs : scale.toNat < 149) :
    roundLow sign product scale = FastMul.roundP sign product scale := by
  by_cases hz : product = 0
  · subst product
    simp [roundLow, FastMul.roundP]
  · have hn : product.toNat ≠ 0 := by
      intro h
      apply hz
      apply UInt64.toNat_inj.mp
      exact h
    have hl : (FastMul.fastLog2 product).toNat < width := by
      rw [FastMul.fastLog2_eq]
      change product.toNat.log2 < width
      exact (Nat.log2_lt hn).mpr hp
    have hposition : FastMul.fastLog2 product + scale < (172 : UInt64) := by
      rw [UInt64.lt_iff_toNat_lt, UInt64.toNat_add]
      change ((FastMul.fastLog2 product).toNat + scale.toNat) %
        18446744073709551616 < 172
      rw [Nat.mod_eq_of_lt (by omega)]
      omega
    have hscale : scale < (149 : UInt64) := by
      rw [UInt64.lt_iff_toNat_lt]
      exact hs
    simp only [roundLow, FastMul.roundP, beq_iff_eq, hz, ite_false,
      hposition, ite_true, hscale]

/-- Preserve the entire old successful guard before the three literal cases. -/
@[inline] def roundSelect (sign : Bool) (product scale : UInt64) : UInt32 :=
  if h : product < (0x1000000000000 : UInt64) ∧ scale ≤ (123 : UInt64) then
    roundLow sign product scale
  else if h124 : scale = 124 ∧ product < (0x1000000000000 : UInt64) then
    roundLow sign product 124
  else if h125 : scale = 125 ∧ product < (0x800000000000 : UInt64) then
    roundLow sign product 125
  else if h126 : scale = 126 ∧ product < (0x400000000000 : UInt64) then
    roundLow sign product 126
  else FastMul.roundP sign product scale

theorem roundSelect_eq (sign : Bool) (product scale : UInt64) :
    roundSelect sign product scale = FastMul.roundP sign product scale := by
  unfold roundSelect
  split
  · rename_i h
    apply roundLow_eq
    · have hp := h.1
      rw [UInt64.lt_iff_toNat_lt] at hp
      change product.toNat < 2 ^ 48 at hp
      exact hp
    · have hs := h.2
      rw [UInt64.le_iff_toNat_le] at hs
      change scale.toNat ≤ 123 at hs
      exact hs
  · split
    · rename_i h124
      have hp := UInt64.lt_iff_toNat_lt.mp h124.2
      change product.toNat < 2 ^ 48 at hp
      rw [h124.1]
      exact roundLow_eq_tight sign product 124 48 hp (by decide) (by decide)
    · split
      · rename_i h125
        have hp := UInt64.lt_iff_toNat_lt.mp h125.2
        change product.toNat < 2 ^ 47 at hp
        rw [h125.1]
        exact roundLow_eq_tight sign product 125 47 hp (by decide) (by decide)
      · split
        · rename_i h126
          have hp := UInt64.lt_iff_toNat_lt.mp h126.2
          change product.toNat < 2 ^ 46 at hp
          rw [h126.1]
          exact roundLow_eq_tight sign product 126 46 hp (by decide) (by decide)
        · rfl
