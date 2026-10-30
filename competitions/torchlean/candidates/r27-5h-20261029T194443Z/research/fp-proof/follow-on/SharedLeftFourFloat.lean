import ContractExact

/- Four output columns sharing the original LEFT operand. Every scalar fold
keeps both multiplication operand order and addition order. Cost remains unknown. -/
namespace R27SharedLeftFourFloat

def scalar (a b : FloatArray) (i : Nat) (s : Float) : Nat → Float
  | 0 => s
  | n + 1 => scalar a b (i + 1) (s + a.get! i * b.get! i) n

@[specialize] def interleave {α : Type} (finish : Float → Float → Float → Float → α)
    (a b0 b1 b2 b3 : FloatArray) (i : Nat) (s0 s1 s2 s3 : Float) : Nat → α
  | 0 => finish s0 s1 s2 s3
  | n + 1 =>
    let x := a.get! i
    interleave finish a b0 b1 b2 b3 (i + 1)
      (s0 + x * b0.get! i) (s1 + x * b1.get! i)
      (s2 + x * b2.get! i) (s3 + x * b3.get! i) n

theorem interleave_eq {α : Type} (finish : Float → Float → Float → Float → α)
    (a b0 b1 b2 b3 : FloatArray) (n : Nat) :
    ∀ i s0 s1 s2 s3,
      interleave finish a b0 b1 b2 b3 i s0 s1 s2 s3 n =
      finish (scalar a b0 i s0 n) (scalar a b1 i s1 n)
        (scalar a b2 i s2 n) (scalar a b3 i s3 n) := by
  induction n with
  | zero => intro i s0 s1 s2 s3; rfl
  | succ n ih =>
    intro i s0 s1 s2 s3
    dsimp only [interleave, scalar]
    exact ih (i + 1) (s0 + a.get! i * b0.get! i)
      (s1 + a.get! i * b1.get! i) (s2 + a.get! i * b2.get! i)
      (s3 + a.get! i * b3.get! i)

end R27SharedLeftFourFloat
