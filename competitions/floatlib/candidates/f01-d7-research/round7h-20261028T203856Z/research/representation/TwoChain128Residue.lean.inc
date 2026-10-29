/- Proof-only residue/terminal bridge. No new runtime loop or signed range
   bound is introduced; the frozen concrete two-chain loop is reused. -/
namespace Submission.R24TwoChain128Residue
open FloatLib.Numerics.FixedWord
open Submission.R24TwoChain128

theorem represents_canonical_residue (v : UInt128) (z : Int)
    (h : Represents v z) : (v.toNat : Int) = z % (2 ^ 128 : Int) := by
  obtain ⟨k, hk⟩ := h
  have hlo : (0 : Int) ≤ v.toNat := by exact_mod_cast Nat.zero_le v.toNat
  have hhi : (v.toNat : Int) < 2 ^ 128 := by exact_mod_cast v.toNat_lt
  calc
    (v.toNat : Int) = (v.toNat : Int) % (2 ^ 128 : Int) :=
      (Int.emod_eq_of_lt hlo hhi).symm
    _ = (z + k * 2 ^ 128) % (2 ^ 128 : Int) :=
      congrArg (fun x : Int => x % (2 ^ 128 : Int)) hk
    _ = z % (2 ^ 128 : Int) := Int.add_mul_emod_self_right z k (2 ^ 128)

theorem represents_unique (x y : UInt128) (z : Int)
    (hx : Represents x z) (hy : Represents y z) : x = y := by
  apply UInt128.toNat_injective
  have h : (x.toNat : Int) = (y.toNat : Int) :=
    (represents_canonical_residue x z hx).trans (represents_canonical_residue y z hy).symm
  exact_mod_cast h

/- `old` may be an original loop's word state. Its required interface is
   modular representation of the same actual getter sequence, not word
   equality, signed exactness, no-overflow, or terminal correctness.
   The run2 premise comes from its concrete merge/add128_toNat proof. -/
theorem run2_terminal_of_represents {β : Type} (finish : UInt128 → β)
    (xs : List UInt64) (old : UInt128) (hold : Represents old (total xs)) :
    finish (run2 xs) = finish old :=
  congrArg finish (represents_unique (run2 xs) old (total xs) (run2_represents xs) hold)

end Submission.R24TwoChain128Residue
