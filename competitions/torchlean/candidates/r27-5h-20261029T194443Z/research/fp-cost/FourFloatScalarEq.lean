import ContractExact

/- Own small conditional follow-on. Four independent left folds interleave
without reassociation. Not a full kernel or an observed speed improvement. -/
namespace R27FourFloat

def sumOne (a b : FloatArray) (i : Nat) (s : Float) : Nat → Float
  | 0 => s
  | n + 1 => sumOne a b (i + 1) (s + a.get! i * b.get! i) n

@[specialize] def sumFour {α : Type} (kont : Float → Float → Float → Float → α)
    (a0 a1 a2 a3 b : FloatArray) (i : Nat) (s0 s1 s2 s3 : Float) : Nat → α
  | 0 => kont s0 s1 s2 s3
  | n + 1 =>
    let w := b.get! i
    sumFour kont a0 a1 a2 a3 b (i + 1)
      (s0 + a0.get! i * w) (s1 + a1.get! i * w)
      (s2 + a2.get! i * w) (s3 + a3.get! i * w) n

/-- No floating-point associativity premise: every component has exactly
the same sequence of operations as its scalar left fold. -/
theorem sumFour_eq {α : Type} (kont : Float → Float → Float → Float → α)
    (a0 a1 a2 a3 b : FloatArray) (n : Nat) :
    ∀ i s0 s1 s2 s3,
      sumFour kont a0 a1 a2 a3 b i s0 s1 s2 s3 n =
      kont (sumOne a0 b i s0 n) (sumOne a1 b i s1 n)
        (sumOne a2 b i s2 n) (sumOne a3 b i s3 n) := by
  induction n with
  | zero => intro i s0 s1 s2 s3; rfl
  | succ n ih =>
    intro i s0 s1 s2 s3
    dsimp only [sumFour, sumOne]
    exact ih (i + 1) (s0 + a0.get! i * b.get! i)
      (s1 + a1.get! i * b.get! i) (s2 + a2.get! i * b.get! i)
      (s3 + a3.get! i * b.get! i)

end R27FourFloat
