import ContractExact

namespace Submission.R27WordProduct

-- UInt32 multiplication is widened before multiplying. The result is exact
-- for every UInt32 pair; no successful caller guard is assumed here.
@[inline] def product (a b : UInt32) : Nat :=
  (a.toUInt64 * b.toUInt64).toNat

theorem product_exact (a b : UInt32) : product a b = a.toNat * b.toNat := by
  have ha := a.toNat_lt
  have hb := b.toNat_lt
  have hp : a.toNat * b.toNat ≤ 4294967295 * 4294967295 :=
    Nat.mul_le_mul (by omega) (by omega)
  unfold product
  rw [UInt64.toNat_mul, UInt32.toNat_toUInt64, UInt32.toNat_toUInt64]
  apply Nat.mod_eq_of_lt
  omega

-- Deliberately use Nat addition but NOT Nat multiplication in the hot loop:
-- the pinned runtime's small-Nat multiply checks overflow using division.
@[specialize] def block (ma mb : Nat → UInt32) (sa sb : Nat → Bool) :
    Nat → Nat → Nat → Nat → Nat × Nat
  | 0, _, pos, neg => (pos, neg)
  | fuel + 1, i, pos, neg =>
    let p := product (ma i) (mb i)
    if sa i = sb i then block ma mb sa sb fuel (i + 1) (pos + p) neg
    else block ma mb sa sb fuel (i + 1) pos (neg + p)

def terms (ma mb : Nat → UInt32) (sa sb : Nat → Bool) : Nat → Nat → Int
  | 0, _ => 0
  | fuel + 1, i =>
    (if sa i = sb i then ((ma i).toNat * (mb i).toNat : Nat)
      else -(((ma i).toNat * (mb i).toNat : Nat) : Int)) +
      terms ma mb sa sb fuel (i + 1)

theorem block_exact (ma mb : Nat → UInt32) (sa sb : Nat → Bool)
    (fuel i pos neg : Nat) :
    ((block ma mb sa sb fuel i pos neg).1 : Int) -
      (block ma mb sa sb fuel i pos neg).2 =
      (pos : Int) - neg + terms ma mb sa sb fuel i := by
  induction fuel generalizing i pos neg with
  | zero => simp [block, terms]
  | succ fuel ih =>
    by_cases h : sa i = sb i
    · simp only [block, terms, if_pos h]
      rw [ih, product_exact]
      push_cast
      ring
    · simp only [block, terms, if_neg h]
      rw [ih, product_exact]
      push_cast
      ring

end Submission.R27WordProduct
