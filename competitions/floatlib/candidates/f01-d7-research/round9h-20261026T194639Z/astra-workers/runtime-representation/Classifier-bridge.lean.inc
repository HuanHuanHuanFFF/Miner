
/- R19 runtime classifier: the two rejection domains are disjoint.
   All arithmetic, table reads, native codecs and fallbacks are unchanged. -/
theorem r19_low_reject_finite (a : UInt32)
    (h : ¬ ((0x0bffffff : UInt32) ≤ a - 1)) :
    a < (0x7f800000 : UInt32) := by
  by_cases hz : a = 0
  · subst a
    exact False.elim (h (by decide))
  · have hpos : 0 < a := UInt32.pos_iff_ne_zero.mpr hz
    have hone : (1 : UInt32) ≤ a := by
      change 1 ≤ a.toNat
      change 0 < a.toNat at hpos
      omega
    have hnat : ¬ 201326591 ≤ (a - 1).toNat := h
    rw [UInt32.toNat_sub_of_le a 1 hone] at hnat
    change a.toNat < 2139095040
    change ¬ 201326591 ≤ a.toNat - 1 at hnat
    omega

theorem r19_eager_gate_eq (a : UInt32) :
    (decide (0x0bffffff ≤ a - 1) == decide (a < 0x7f800000)) =
      (decide (0x0bffffff ≤ a - 1) && decide (a < 0x7f800000)) := by
  by_cases hl : (0x0bffffff : UInt32) ≤ a - 1
  · by_cases hh : a < (0x7f800000 : UInt32) <;> simp [hl, hh]
  · have hh := r19_low_reject_finite a hl
    simp [hl, hh]

theorem r19_fastOK_eq_old (u : UInt32) :
    fastOK u = (decide (0x0bffffff ≤ magnitude u - 1) &&
      decide (magnitude u < 0x7f800000)) := by
  exact r19_eager_gate_eq (magnitude u)

