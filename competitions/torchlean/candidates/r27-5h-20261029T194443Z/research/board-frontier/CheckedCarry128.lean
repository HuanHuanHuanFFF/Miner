import ContractExact

/- Self-authored small proof carrier for a dynamic overflow certificate.
It proves word addition only; it is not an entire norm/matrix proof. -/
namespace R27CheckedCarry

theorem add_no_wrap (a b : UInt64) (h : a ≤ a + b) :
    (a + b).toNat = a.toNat + b.toNat := by
  have ha := a.toNat_lt
  have hb := b.toNat_lt
  have hc := UInt64.le_iff_toNat_le.mp h
  rw [UInt64.toNat_add] at hc ⊢
  omega

theorem low_with_carry (a b : UInt64) :
    (a + b).toNat + (if a + b < a then 2^64 else 0) = a.toNat + b.toNat := by
  have ha := a.toNat_lt
  have hb := b.toNat_lt
  by_cases h : a + b < a
  · rw [if_pos h]
    have hc := UInt64.lt_iff_toNat_lt.mp h
    rw [UInt64.toNat_add] at hc ⊢
    omega
  · rw [if_neg h]
    have hc : a ≤ a + b := UInt64.le_iff_toNat_le.mpr
      (Nat.le_of_not_lt (by simpa only [UInt64.lt_iff_toNat_lt] using h))
    rw [add_no_wrap a b hc]
    omega

def add (h l ah al : UInt64) : Bool × UInt64 × UInt64 :=
  let ll := l + al
  let c : UInt64 := if ll < l then 1 else 0
  let h1 := h + c
  let h2 := h1 + ah
  (decide (h ≤ h1) && decide (h1 ≤ h2), h2, ll)

theorem add_sound (h l ah al : UInt64) (ok : (add h l ah al).1 = true) :
    (add h l ah al).2.1.toNat * 2^64 + (add h l ah al).2.2.toNat =
      h.toNat * 2^64 + l.toNat + (ah.toNat * 2^64 + al.toNat) := by
  unfold add at ok ⊢
  dsimp only at ok ⊢
  simp only [Bool.and_eq_true, decide_eq_true_eq] at ok
  rw [add_no_wrap _ _ ok.2, add_no_wrap _ _ ok.1]
  have hc := low_with_carry l al
  split_ifs at hc ⊢ with c <;> simp only [UInt64.toNat_one, UInt64.toNat_zero] <;> omega

end R27CheckedCarry
