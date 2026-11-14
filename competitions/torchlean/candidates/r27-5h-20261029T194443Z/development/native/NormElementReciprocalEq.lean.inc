theorem r27Ya7G_eq (n : Nat) (word gain bias : Word) (base : Nat)
    (firstMoment : Int) (denominator : Word) (mean : Unit → ℚ)
    (nU baseU : UInt64) (momentSign : Bool) (momentMagnitude : UInt64) :
    r27Ya7G n word gain bias base firstMoment denominator mean
      nU baseU momentSign momentMagnitude
      (R27Reciprocal.prepare (nU * Yf denominator)) =
    Ya7G n word gain bias base firstMoment denominator mean
      nU baseU momentSign momentMagnitude := by
  unfold r27Ya7G Ya7G
  simp only [R27Reciprocal.divRem_correct]
