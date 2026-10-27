/-- Separate small arithmetic facts so the kernel does not normalize 28 combined cases. -/
theorem lowJam_ge (v r : Nat) : v ≤ lowJam v r := by
  unfold lowJam
  exact Nat.le_add_right _ _

theorem lowJam_lt_even (v r H : Nat) (hv : v<H) (hH : H%2=0) :
    lowJam v r < H := by
  unfold lowJam
  by_cases hz : r=0
  · simpa only [if_pos hz, Nat.add_zero] using hv
  · rw [if_neg hz]
    have hvmod := Nat.mod_lt v (by decide : 0<2)
    omega

theorem decision_below (q r C : Nat) (h : 2*r<C) : decision q r C=q := by
  simp only [decision, if_pos h]

theorem decision_above (q r C : Nat) (h : C<2*r) : decision q r C=q+1 := by
  have hn : ¬2*r<C := Nat.not_lt_of_ge (Nat.le_of_lt h)
  simp only [decision, if_neg hn, if_pos h]

theorem decision_tie (q r C : Nat) (h : 2*r=C) :
    decision q r C = (if q%2==0 then q else q+1) := by
  simp only [decision, h, Nat.lt_irrefl, ite_false]

/-- Three midpoint cases; variable products are handled by monotonicity, never omega. -/
theorem decision_midpoint (D H q v r : Nat) (hD : 0<D) (hr : r<D)
    (hH : H%2=0) :
    decision q (lowJam v r) (2*H) = decision q (D*v+r) (D*(2*H)) := by
  rcases Nat.lt_trichotomy v H with hv | he | hv
  · have hj := lowJam_lt_even v r H hv hH
    have hl : 2*lowJam v r < 2*H :=
      Nat.mul_lt_mul_of_pos_left hj (by decide : 0<2)
    have hw : D*v+r < D*H := by
      calc
        D*v+r < D*v+D := Nat.add_lt_add_left hr _
        _ = D*(v+1) := by simp only [Nat.mul_add, Nat.mul_one]
        _ ≤ D*H := Nat.mul_le_mul_left D (Nat.succ_le_of_lt hv)
    have hh : 2*(D*v+r) < D*(2*H) := by
      calc
        2*(D*v+r) < 2*(D*H) := Nat.mul_lt_mul_of_pos_left hw (by decide : 0<2)
        _ = D*(2*H) := by ac_rfl
    rw [decision_below q (lowJam v r) (2*H) hl,
      decision_below q (D*v+r) (D*(2*H)) hh]
  · subst v
    by_cases hz : r=0
    · subst r
      have hl : 2*lowJam H 0 = 2*H := by simp [lowJam]
      have hh : 2*(D*H+0)=D*(2*H) := by
        simp only [Nat.add_zero]
        ac_rfl
      rw [decision_tie q (lowJam H 0) (2*H) hl,
        decision_tie q (D*H+0) (D*(2*H)) hh]
    · have hrpos : 0<r := Nat.pos_of_ne_zero hz
      have hl : 2*H < 2*lowJam H r := by
        simp only [lowJam, hH, if_neg hz, Nat.sub_zero]
        omega
      have hw : D*H < D*H+r := by
        simpa only [Nat.add_zero] using Nat.add_lt_add_left hrpos (D*H)
      have hh : D*(2*H) < 2*(D*H+r) := by
        calc
          D*(2*H) = 2*(D*H) := by ac_rfl
          _ < 2*(D*H+r) := Nat.mul_lt_mul_of_pos_left hw (by decide : 0<2)
      rw [decision_above q (lowJam H r) (2*H) hl,
        decision_above q (D*H+r) (D*(2*H)) hh]
  · have hj : H < lowJam v r := Nat.lt_of_lt_of_le hv (lowJam_ge v r)
    have hl : 2*H < 2*lowJam v r :=
      Nat.mul_lt_mul_of_pos_left hj (by decide : 0<2)
    have hw : D*H < D*v+r := Nat.lt_of_lt_of_le
      (Nat.mul_lt_mul_of_pos_left hv hD) (Nat.le_add_right _ _)
    have hh : D*(2*H) < 2*(D*v+r) := by
      calc
        D*(2*H) = 2*(D*H) := by ac_rfl
        _ < 2*(D*v+r) := Nat.mul_lt_mul_of_pos_left hw (by decide : 0<2)
    rw [decision_above q (lowJam v r) (2*H) hl,
      decision_above q (D*v+r) (D*(2*H)) hh]

/-- Original interface retained; only three literal midpoint instantiations remain. -/
theorem low_states (D C q v r : Nat) (hD : 0<D) (hr : r<D)
    (hv : v<C) (hC : C=4 ∨ C=8 ∨ C=16) :
    lowJam v r < C ∧
      decision q (lowJam v r) C = decision q (D*v+r) (D*C) := by
  constructor
  · apply lowJam_lt_even v r C hv
    rcases hC with rfl | rfl | rfl <;> decide
  · rcases hC with rfl | rfl | rfl
    · exact decision_midpoint D 2 q v r hD hr (by decide)
    · exact decision_midpoint D 4 q v r hD hr (by decide)
    · exact decision_midpoint D 8 q v r hD hr (by decide)

