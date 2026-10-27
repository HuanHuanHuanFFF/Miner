/- NOT_RUN. Append only after the frozen JamVariable.lean/a78a source.
   Mathematical translation lemmas, not a runtime or public ADD candidate. -/
namespace R19JamVariableProbe

theorem jam_block (D q r : Nat) (hD : 0<D) (hr : r<D) :
    jamDiv (D*q+r) D = lowJam q r := by
  simp only [jamDiv, lowJam, Nat.mul_add_div hD q r, Nat.mul_add_mod,
    Nat.div_eq_of_lt hr, Nat.mod_eq_of_lt hr, Nat.add_zero]

theorem jam_mul (D q : Nat) (hD : 0<D) : jamDiv (D*q) D = q := by
  simpa [lowJam] using jam_block D q 0 hD hD

theorem jam_add_even (D X m : Nat) (hD : 0<D) (hX : X%2=0) :
    jamDiv (X*D+m) D = X+jamDiv m D := by
  have hu : (X*D+m)/D = X+m/D := by
    rw [Nat.mul_comm X D, Nat.mul_add_div hD]
  have hm : (X*D+m)%D = m%D := Nat.mul_add_mod' X D m
  simp only [jamDiv, hu, hm, Nat.add_mod, hX, Nat.zero_add,
    Nat.mod_mod, Nat.add_assoc]

/-- Pure parity arithmetic: no divisor or multiplied quotient enters omega. -/
theorem complement_sticky (X q : Nat) (hX : X%2=0) (hq : q<X) :
    (X-(q+1))+(1-(X-(q+1))%2) = X-(q+(1-q%2)) := by
  have hqmod := Nat.mod_lt q (by decide : 0<2)
  have hsmod := Nat.mod_lt (X-(q+1)) (by decide : 0<2)
  by_cases he : q%2=0 <;> omega

/-- A borrow changes the quotient by one and complements the remainder. -/
theorem borrow_decomp (D X q r : Nat) (hq : q<X) (hr : r≤D) :
    D*X-(D*q+r) = D*(X-(q+1))+(D-r) := by
  have hs : (X-(q+1))+(q+1)=X :=
    Nat.sub_add_cancel (Nat.succ_le_of_lt hq)
  have hrem : D-r+r=D := Nat.sub_add_cancel hr
  have hbalance : D*(X-(q+1))+(D-r)+(D*q+r)=D*X := by
    calc
      D*(X-(q+1))+(D-r)+(D*q+r) =
          D*(X-(q+1))+D*q+((D-r)+r) := by ac_rfl
      _ = D*(X-(q+1))+D*q+D := by rw [hrem]
      _ = D*(X-(q+1))+D*(q+1) := by
        simp only [Nat.mul_add, Nat.mul_one, Nat.add_assoc]
      _ = D*X := by rw [← Nat.mul_add, hs]
  rw [← hbalance, Nat.add_sub_cancel]

theorem jam_sub_decomposed (D X q r : Nat) (hD : 0<D) (hX : X%2=0)
    (hr : r<D) (hm : D*q+r≤D*X) :
    jamDiv (D*X-(D*q+r)) D = X-lowJam q r := by
  by_cases hz : r=0
  · subst r
    rw [Nat.add_zero, ← Nat.mul_sub_left_distrib, jam_mul D (X-q) hD] <;>
      simp [lowJam]
  · have hrpos : 0<r := Nat.pos_of_ne_zero hz
    have hlt : D*q<D*X := Nat.lt_of_lt_of_le
      (by simpa only [Nat.add_zero] using Nat.add_lt_add_left hrpos (D*q)) hm
    have hq : q<X := Nat.lt_of_mul_lt_mul_left hlt
    have hrempos : 0<D-r := Nat.sub_pos_of_lt hr
    have hremlt : D-r<D := Nat.sub_lt hD hrpos
    rw [borrow_decomp D X q r hq (Nat.le_of_lt hr),
      jam_block D (X-(q+1)) (D-r) hD hremlt]
    simp only [lowJam, if_neg (Nat.ne_of_gt hrempos), if_neg hz]
    exact complement_sticky X q hX hq

theorem jam_sub_even (D X m : Nat) (hD : 0<D) (hX : X%2=0)
    (hm : m≤X*D) : jamDiv (X*D-m) D = X-jamDiv m D := by
  have hd : D*(m/D)+m%D=m := Nat.div_add_mod m D
  have hb : D*(m/D)+m%D≤D*X := by
    rw [hd, Nat.mul_comm D X]
    exact hm
  have h := jam_sub_decomposed D X (m/D) (m%D) hD hX
    (Nat.mod_lt m hD) hb
  change jamDiv (X*D-m) D = X-lowJam (m/D) (m%D)
  simpa only [hd, Nat.mul_comm D X] using h

/-- Cancel the same positive scale in numerator and divisor, including sticky. -/
theorem jam_scale (s p D : Nat) (hs : 0<s) :
    jamDiv (s*p) (s*D) = jamDiv p D := by
  unfold jamDiv
  rw [Nat.mul_div_mul_left p D hs, Nat.mul_mod_mul_left]
  simp only [Nat.mul_eq_zero, Nat.ne_of_gt hs, false_or]

end R19JamVariableProbe
