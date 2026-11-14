namespace Submission.R26WordBlock

def Represents64 (q : UInt64) (z : Int) : Prop :=
  ∃ k : Int, (q.toNat : Int) = z + k * 18446744073709551616

def Represents128 (lo hi : UInt64) (z : Int) : Prop :=
  ∃ k : Int, (lo.toNat : Int) + (hi.toNat : Int) * 18446744073709551616 =
    z + k * 340282366920938463463374607431768211456

def exactTerms (a b : Nat → UInt32) : Nat → Nat → Int
  | 0, _ => 0
  | fuel + 1, i =>
    signed64 (extend32 (a i)) * signed64 (extend32 (b i)) + exactTerms a b fuel (i + 1)

def termMass (a b : Nat → UInt32) : Nat → Nat → Int
  | 0, _ => 0
  | fuel + 1, i =>
    |signed64 (extend32 (a i)) * signed64 (extend32 (b i))| + termMass a b fuel (i + 1)

theorem represents64_refl (q : UInt64) : Represents64 q q.toNat := by
  exact ⟨0, by omega⟩

theorem signed64_represents (q : UInt64) : Represents64 q (signed64 q) := by
  unfold Represents64 signed64
  split_ifs with h
  · exact ⟨0, by omega⟩
  · exact ⟨1, by omega⟩

theorem add_represents64 (a b : UInt64) (x y : Int)
    (ha : Represents64 a x) (hb : Represents64 b y) : Represents64 (a + b) (x + y) := by
  obtain ⟨ka, ha⟩ := ha
  obtain ⟨kb, hb⟩ := hb
  have hnat : (a + b).toNat + 18446744073709551616 *
      ((a.toNat + b.toNat) / 18446744073709551616) = a.toNat + b.toNat := by
    rw [UInt64.toNat_add]
    exact Nat.mod_add_div _ _
  have hint : ((a + b).toNat : Int) + 18446744073709551616 *
      (((a.toNat + b.toNat) / 18446744073709551616 : Nat) : Int) =
      (a.toNat : Int) + b.toNat := by exact_mod_cast hnat
  refine ⟨ka + kb - (((a.toNat + b.toNat) / 18446744073709551616 : Nat) : Int), ?_⟩
  omega

theorem mul_represents64 (a b : UInt64) (x y : Int)
    (ha : Represents64 a x) (hb : Represents64 b y) : Represents64 (a * b) (x * y) := by
  obtain ⟨ka, ha⟩ := ha
  obtain ⟨kb, hb⟩ := hb
  have hnat : (a * b).toNat + 18446744073709551616 *
      ((a.toNat * b.toNat) / 18446744073709551616) = a.toNat * b.toNat := by
    rw [UInt64.toNat_mul]
    exact Nat.mod_add_div _ _
  have hint : ((a * b).toNat : Int) + 18446744073709551616 *
      (((a.toNat * b.toNat) / 18446744073709551616 : Nat) : Int) =
      (a.toNat : Int) * b.toNat := by exact_mod_cast hnat
  refine ⟨x * kb + y * ka + ka * kb * 18446744073709551616 -
    (((a.toNat * b.toNat) / 18446744073709551616 : Nat) : Int), ?_⟩
  rw [ha, hb] at hint
  linear_combination hint

theorem block_represents (a b : Nat → UInt32) (fuel i : Nat)
    (acc : UInt64) (initial : Int) (h : Represents64 acc initial) :
    Represents64 (block a b fuel i acc) (initial + exactTerms a b fuel i) := by
  induction fuel generalizing i acc initial with
  | zero => simpa [block, exactTerms] using h
  | succ fuel ih =>
    have hp := mul_represents64 (extend32 (a i)) (extend32 (b i))
      (signed64 (extend32 (a i))) (signed64 (extend32 (b i)))
      (signed64_represents _) (signed64_represents _)
    have hs := add_represents64 acc _ initial _ h hp
    simpa only [block, exactTerms, Int.add_assoc] using
      ih (i + 1) (acc + extend32 (a i) * extend32 (b i))
        (initial + signed64 (extend32 (a i)) * signed64 (extend32 (b i))) hs

theorem signed64_unique (q : UInt64) (z : Int) (h : Represents64 q z)
    (hz : -9223372036854775808 ≤ z ∧ z < 9223372036854775808) : signed64 q = z := by
  obtain ⟨k, hk⟩ := h
  have hu := q.toNat_lt
  unfold signed64
  split_ifs with hs <;> omega

theorem exactTerms_abs_le (a b : Nat → UInt32) (fuel i : Nat) :
    |exactTerms a b fuel i| ≤ termMass a b fuel i := by
  induction fuel generalizing i with
  | zero => simp [exactTerms, termMass]
  | succ fuel ih =>
    calc
      |exactTerms a b (fuel + 1) i| ≤
          |signed64 (extend32 (a i)) * signed64 (extend32 (b i))| +
          |exactTerms a b fuel (i + 1)| := abs_add _ _
      _ ≤ termMass a b (fuel + 1) i := add_le_add_left (ih (i + 1)) _

theorem block_exact (a b : Nat → UInt32) (fuel i : Nat)
    (h : termMass a b fuel i < 9223372036854775808) :
    signed64 (block a b fuel i 0) = exactTerms a b fuel i := by
  have hb := lt_of_le_of_lt (exactTerms_abs_le a b fuel i) h
  have hz : Represents64 (0 : UInt64) 0 := ⟨0, by simp⟩
  apply signed64_unique _ _
  · simpa using block_represents a b fuel i 0 0 hz
  · exact ⟨(abs_lt.mp hb).1.le, (abs_lt.mp hb).2⟩

theorem add_nat_carry (a b : UInt64) :
    (a + b).toNat + (if a + b < a then 18446744073709551616 else 0) =
      a.toNat + b.toNat := by
  have ha := a.toNat_lt
  have hb := b.toNat_lt
  rw [UInt64.lt_iff_toNat_lt]
  rw [UInt64.toNat_add]
  split_ifs <;> omega

theorem merge_represents128 (lo hi q : UInt64) (z : Int)
    (h : Represents128 lo hi z) :
    Represents128 (lo + q) (mergeHi lo hi q) (z + signed64 q) := by
  obtain ⟨k, hk⟩ := h
  have hcarry := add_nat_carry lo q
  have hcarryInt : ((lo + q).toNat : Int) +
      (if lo + q < lo then 18446744073709551616 else 0) =
      (lo.toNat : Int) + q.toNat := by exact_mod_cast hcarry
  have hpad : Represents64
      (if negative64 q then (0xffffffffffffffff : UInt64) else 0)
      (if negative64 q then (-1 : Int) else 0) := by
    cases negative64 q
    · exact ⟨0, by simp⟩
    · exact ⟨1, by norm_num⟩
  have hc : Represents64 (if lo + q < lo then (1 : UInt64) else 0)
      (if lo + q < lo then (1 : Int) else 0) := by
    split_ifs <;> exact ⟨0, by simp⟩
  have hs := add_represents64 hi _ (hi.toNat : Int) _ (represents64_refl hi) hpad
  have ht := add_represents64 _ _ _ _ hs hc
  change Represents64 (mergeHi lo hi q) _ at ht
  obtain ⟨j, hj⟩ := ht
  refine ⟨k + j, ?_⟩
  unfold negative64 signed64 at hj ⊢
  simp only [UInt64.lt_iff_toNat_lt] at hj
  norm_num only [UInt64.toNat_ofNat] at hj
  split_ifs at hj hcarryInt ⊢ <;> omega

theorem signed128_unique (lo hi : UInt64) (z : Int) (h : Represents128 lo hi z)
    (hz : -170141183460469231731687303715884105728 ≤ z ∧
      z < 170141183460469231731687303715884105728) : signed128 lo hi = z := by
  obtain ⟨k, hk⟩ := h
  have hlo := lo.toNat_lt
  have hhi := hi.toNat_lt
  unfold signed128 signed64
  split_ifs <;> omega

end Submission.R26WordBlock
