import ContractTensor

/- NOT_RUN: bounded mathematical probe only; not appended to a candidate.
   Same arithmetic jam convention as the verified R19Jam17 proof.
   No local Lean or CI has run this file. -/
namespace R19JamVariableProbe
open FloatLib.Numerics

def jamDiv (p D : Nat) : Nat :=
  p / D + if p % D = 0 then 0 else 1 - (p / D) % 2

def lowJam (v r : Nat) : Nat :=
  v + if r = 0 then 0 else 1 - v % 2

def decision (q r C : Nat) : Nat :=
  if 2*r < C then q
  else if C < 2*r then q+1
  else if q % 2 == 0 then q else q+1

/-- Strip the entire quotient block before any arithmetic decision proof. -/
theorem quotient_block (q r C : Nat) (hC : 0<C) (hr : r<C) :
    roundQuotientEven (C*q+r) C = decision q r C := by
  simp only [roundQuotientEven, decision,
    Nat.mul_add_div hC q r, Nat.mul_add_mod,
    Nat.div_eq_of_lt hr, Nat.mod_eq_of_lt hr, Nat.add_zero]

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


/-- The variable divisor is handled by exact div/mod APIs, not nonlinear omega. -/
theorem quotient_jam_decomposed (D C q v r : Nat) (hD : 0<D) (hr : r<D)
    (hv : v<C) (hC : C=4 ∨ C=8 ∨ C=16) :
    roundQuotientEven (jamDiv (D*(C*q+v)+r) D) C =
      roundQuotientEven (D*(C*q+v)+r) (D*C) := by
  have hCpos : 0<C := by rcases hC with rfl | rfl | rfl <;> decide
  have hu : (D*(C*q+v)+r)/D = C*q+v := by
    rw [Nat.mul_add_div hD, Nat.div_eq_of_lt hr, Nat.add_zero]
  have hm : (D*(C*q+v)+r)%D = r := by
    rw [Nat.mul_add_mod, Nat.mod_eq_of_lt hr]
  have hp : (C*q+v)%2 = v%2 := by
    rcases hC with rfl | rfl | rfl <;>
      simp [Nat.add_mod, Nat.mul_mod]
  have hjam : jamDiv (D*(C*q+v)+r) D = C*q+lowJam v r := by
    simp only [jamDiv, hu, hm, hp, lowJam, Nat.add_assoc]
  have hrem : D*v+r < D*C := by
    calc
      D*v+r < D*v+D := Nat.add_lt_add_left hr _
      _ = D*(v+1) := by simp only [Nat.mul_add, Nat.mul_one]
      _ ≤ D*C := Nat.mul_le_mul_left D (Nat.succ_le_of_lt hv)
  have hnum : D*(C*q+v)+r = (D*C)*q+(D*v+r) := by
    simp only [Nat.mul_add, Nat.mul_assoc, Nat.add_assoc]
  have hj := low_states D C q v r hD hr hv hC
  rw [hjam, hnum, quotient_block q (lowJam v r) C hCpos hj.1,
    quotient_block q (D*v+r) (D*C) (Nat.mul_pos hD hCpos) hrem]
  exact hj.2

theorem quotient_jam (p D C : Nat) (hD : 0<D)
    (hC : C=4 ∨ C=8 ∨ C=16) :
    roundQuotientEven (jamDiv p D) C = roundQuotientEven p (D*C) := by
  have hCpos : 0<C := by rcases hC with rfl | rfl | rfl <;> decide
  have hp : D*(C*((p/D)/C)+(p/D)%C)+p%D = p := by
    rw [Nat.div_add_mod (p/D) C, Nat.div_add_mod p D]
  have h := quotient_jam_decomposed D C ((p/D)/C) ((p/D)%C) (p%D)
    hD (Nat.mod_lt p hD) (Nat.mod_lt (p/D) hCpos) hC
  simpa only [hp] using h

/-- All d, including d=0; target k is exactly the GRS-required 2/3/4. -/
theorem rne_jam (p d k : Nat) (hk : k=2 ∨ k=3 ∨ k=4) :
    roundShiftRightEven (jamDiv p (2^d)) k =
      roundShiftRightEven p (d+k) := by
  simp only [roundShiftRightEven_eq_roundQuotientEven, Nat.pow_add]
  apply quotient_jam p (2^d) (2^k) (Nat.two_pow_pos d)
  rcases hk with rfl | rfl | rfl <;> norm_num

end R19JamVariableProbe
