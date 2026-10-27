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

/-- Exactly 4+8+16 low states. D and r stay variable and linear in every leaf. -/
theorem low_states (D C q v r : Nat) (hD : 0<D) (hr : r<D)
    (hv : v<C) (hC : C=4 ∨ C=8 ∨ C=16) :
    lowJam v r < C ∧
      decision q (lowJam v r) C = decision q (D*v+r) (D*C) := by
  rcases hC with rfl | rfl | rfl <;>
    interval_cases v <;> constructor <;>
    simp only [lowJam, decision, beq_iff_eq] <;>
    split_ifs <;> omega

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
