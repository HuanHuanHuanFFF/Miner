import ContractExact

namespace Submission.R27SignedBlock

@[specialize] def block (a b : Nat → UInt32) : Nat → Nat → Int64 → Int64
  | 0, _, acc => acc
  | fuel + 1, i, acc =>
    block a b fuel (i + 1) (acc + (a i).toInt32.toInt64 * (b i).toInt32.toInt64)

def terms (a b : Nat → UInt32) : Nat → Nat → Int
  | 0, _ => 0
  | fuel + 1, i => (a i).toInt32.toInt * (b i).toInt32.toInt + terms a b fuel (i + 1)

theorem bounded_bmod (z : Int) (hlo : -9223372036854775808 ≤ z)
    (hhi : z < 9223372036854775808) : z.bmod (2^64) = z := by
  apply Int.bmod_eq_of_le
  · norm_num
    exact hlo
  · norm_num
    exact hhi

theorem block_bmod (a b : Nat → UInt32) (fuel i : Nat) (acc : Int64) :
    (block a b fuel i acc).toInt = (acc.toInt + terms a b fuel i).bmod (2^64) := by
  induction fuel generalizing i acc with
  | zero =>
    simp only [block, terms, Int.add_zero]
    exact (bounded_bmod _ (Int64.le_toInt acc) (Int64.toInt_lt acc)).symm
  | succ fuel ih =>
    rw [block, ih, Int64.toInt_add, Int64.toInt_mul,
      Int32.toInt_toInt64, Int32.toInt_toInt64, Int.bmod_add_bmod, terms]
    calc
      _ = ((acc.toInt + terms a b fuel (i + 1)) +
          ((a i).toInt32.toInt * (b i).toInt32.toInt).bmod (2^64)).bmod (2^64) := by
        congr 1
        ring
      _ = ((acc.toInt + terms a b fuel (i + 1)) +
          (a i).toInt32.toInt * (b i).toInt32.toInt).bmod (2^64) := Int.add_bmod_bmod
      _ = _ := by congr 1; ring

theorem block_exact (a b : Nat → UInt32) (fuel i : Nat)
    (hlo : -9223372036854775808 ≤ terms a b fuel i)
    (hhi : terms a b fuel i < 9223372036854775808) :
    (block a b fuel i 0).toInt = terms a b fuel i := by
  rw [block_bmod]
  simpa using bounded_bmod (terms a b fuel i) hlo hhi

end Submission.R27SignedBlock
