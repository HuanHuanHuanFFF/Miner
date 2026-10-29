namespace Submission.R26WordBlockTwo
open Submission.R26WordBlock

@[specialize] def blockPairs (a b : Nat → UInt32) :
    Nat → Nat → UInt64 → UInt64 → UInt64
  | 0, _, even, odd => even + odd
  | pairs + 1, i, even, odd =>
    blockPairs a b pairs (i + 2)
      (even + extend32 (a i) * extend32 (b i))
      (odd + extend32 (a (i + 1)) * extend32 (b (i + 1)))

@[specialize] def blocks (a b : Nat → UInt32) : Nat → Nat → UInt64 → UInt64 → UInt64 × UInt64
  | 0, _, lo, hi => (lo, hi)
  | count + 1, i, lo, hi =>
    let q := blockPairs a b 8 i 0 0
    blocks a b count (i + 16) (lo + q) (mergeHi lo hi q)

@[specialize] def body128 (n : Nat) (a b : Nat → UInt32) : UInt64 × UInt64 :=
  let full := blocks a b (n / 16) 0 0 0
  let tail := n % 16
  if tail = 0 then full else
    let q := block a b tail (n / 16 * 16) 0
    (full.1 + q, mergeHi full.1 full.2 q)

@[specialize] def body128SingleNoEmpty (n : Nat) (a b : Nat → UInt32) : UInt64 × UInt64 :=
  let full := Submission.R26WordBlock.blocks a b (n / 16) 0 0 0
  let tail := n % 16
  if tail = 0 then full else
    let q := block a b tail (n / 16 * 16) 0
    (full.1 + q, mergeHi full.1 full.2 q)

theorem blockPairs_represents (a b : Nat → UInt32) (pairs i : Nat)
    (even odd : UInt64) (ev od : Int)
    (he : Represents64 even ev) (ho : Represents64 odd od) :
    Represents64 (blockPairs a b pairs i even odd)
      (ev + od + exactTerms a b (pairs * 2) i) := by
  induction pairs generalizing i even odd ev od with
  | zero => simpa [blockPairs, exactTerms] using add_represents64 even odd ev od he ho
  | succ pairs ih =>
    have hp0 := mul_represents64 _ _ _ _ (signed64_represents (extend32 (a i)))
      (signed64_represents (extend32 (b i)))
    have hp1 := mul_represents64 _ _ _ _ (signed64_represents (extend32 (a (i + 1))))
      (signed64_represents (extend32 (b (i + 1))))
    have hs0 := add_represents64 _ _ _ _ he hp0
    have hs1 := add_represents64 _ _ _ _ ho hp1
    have ht := ih (i + 2) _ _ _ _ hs0 hs1
    have hn : (pairs + 1) * 2 = pairs * 2 + 1 + 1 := by omega
    simp only [blockPairs, hn, exactTerms] at ht ⊢
    simp only [show i + 1 + 1 = i + 2 by omega]
    convert ht using 1 <;> ring

theorem blockPairs_exact (a b : Nat → UInt32) (pairs i : Nat)
    (h : termMass a b (pairs * 2) i < 9223372036854775808) :
    signed64 (blockPairs a b pairs i 0 0) = exactTerms a b (pairs * 2) i := by
  have hz : Represents64 (0 : UInt64) 0 := ⟨0, by simp⟩
  have hp := blockPairs_represents a b pairs i 0 0 0 0 hz hz
  have hb := lt_of_le_of_lt (exactTerms_abs_le a b (pairs * 2) i) h
  apply signed64_unique
  · simpa using hp
  · exact ⟨(abs_lt.mp hb).1.le, (abs_lt.mp hb).2⟩

end Submission.R26WordBlockTwo
