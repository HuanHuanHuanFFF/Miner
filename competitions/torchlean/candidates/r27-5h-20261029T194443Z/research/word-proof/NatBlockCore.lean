import ContractExact

namespace Submission.R27NatBlock

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

-- Both signs and magnitudes are prepared once per reusable vector. No Int is
-- constructed in the MAC loop. Bounds are cost guards, not soundness premises.
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
    (if sa i = sb i then (((ma i).toNat * (mb i).toNat : Nat) : Int) else -(((ma i).toNat * (mb i).toNat : Nat) : Int)) +
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

theorem terms_add (ma mb : Nat → UInt32) (sa sb : Nat → Bool) (m n i : Nat) :
    terms ma mb sa sb (m + n) i =
      terms ma mb sa sb m i + terms ma mb sa sb n (i + m) := by
  induction m generalizing i with
  | zero => simp [terms]
  | succ m ih =>
    simp [Nat.succ_add, terms, ih, Nat.add_assoc, Nat.add_comm,
      Nat.add_left_comm, Int.add_assoc]

@[specialize] def blocks (ma mb : Nat → UInt32) (sa sb : Nat → Bool) :
    Nat → Nat → Nat → Nat → Nat × Nat
  | 0, _, pos, neg => (pos, neg)
  | fuel + 1, i, pos, neg =>
    let q := block ma mb sa sb 16 i 0 0
    blocks ma mb sa sb fuel (i + 16) (pos + q.1) (neg + q.2)

theorem blocks_exact (ma mb : Nat → UInt32) (sa sb : Nat → Bool)
    (fuel i pos neg : Nat) :
    ((blocks ma mb sa sb fuel i pos neg).1 : Int) -
      (blocks ma mb sa sb fuel i pos neg).2 =
      (pos : Int) - neg + terms ma mb sa sb (16 * fuel) i := by
  induction fuel generalizing i pos neg with
  | zero => simp [blocks, terms]
  | succ fuel ih =>
    simp only [blocks]
    rw [ih]
    have hb := block_exact ma mb sa sb 16 i 0 0
    have ht := terms_add ma mb sa sb 16 (16 * fuel) i
    rw [show 16 * (fuel + 1) = 16 + 16 * fuel by omega, ht]
    push_cast at hb ⊢
    omega

@[specialize] def body (n : Nat) (ma mb : Nat → UInt32) (sa sb : Nat → Bool) : Int :=
  let full := blocks ma mb sa sb (n / 16) 0 0 0
  let tail := block ma mb sa sb (n % 16) (16 * (n / 16)) 0 0
  ((full.1 + tail.1 : Nat) : Int) - (full.2 + tail.2 : Nat)

theorem body_exact (n : Nat) (ma mb : Nat → UInt32) (sa sb : Nat → Bool) :
    body n ma mb sa sb = terms ma mb sa sb n 0 := by
  have hf := blocks_exact ma mb sa sb (n / 16) 0 0 0
  have ht := block_exact ma mb sa sb (n % 16) (16 * (n / 16)) 0 0
  have hs := terms_add ma mb sa sb (16 * (n / 16)) (n % 16) 0
  have hn : 16 * (n / 16) + n % 16 = n := by omega
  rw [hn] at hs
  unfold body
  push_cast at hf ht ⊢
  simp only [Nat.zero_add] at hs
  omega

@[specialize] def finish (guard : Bool) (n : Nat) (ma mb : Nat → UInt32)
    (sa sb : Nat → Bool) (bias exponent : Int) (shipped : Unit → UInt32) : UInt32 :=
  if guard then
    let total := body n ma mb sa sb + bias
    if total = 0 then shipped () else ExactRuntime.finishWord total exponent false
  else shipped ()

theorem finish_false (n : Nat) (ma mb : Nat → UInt32) (sa sb : Nat → Bool)
    (bias exponent : Int) (shipped : Unit → UInt32) :
    finish false n ma mb sa sb bias exponent shipped = shipped () := rfl

theorem finish_nonzero (n : Nat) (ma mb : Nat → UInt32) (sa sb : Nat → Bool)
    (bias exponent : Int) (shipped : Unit → UInt32)
    (h : terms ma mb sa sb n 0 + bias ≠ 0) :
    finish true n ma mb sa sb bias exponent shipped =
      ExactRuntime.finishWord (terms ma mb sa sb n 0 + bias) exponent false := by
  simp [finish, body_exact, h]

end Submission.R27NatBlock
