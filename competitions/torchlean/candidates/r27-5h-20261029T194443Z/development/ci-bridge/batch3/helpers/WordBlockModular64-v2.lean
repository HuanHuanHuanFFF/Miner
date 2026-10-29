import ContractExact

namespace Submission.R26WordBlock

@[inline] def extend32 (w : UInt32) : UInt64 :=
  (w.toUInt64 ^^^ 0x80000000) - 0x80000000

@[inline] def negative64 (w : UInt64) : Bool :=
  if w < 0x8000000000000000 then false else true

@[inline] def mergeHi (lo hi q : UInt64) : UInt64 :=
  let next := lo + q
  hi + (if negative64 q then 0xffffffffffffffff else 0) +
    (if next < lo then 1 else 0)

def signed64 (q : UInt64) : Int :=
  if q.toNat < 9223372036854775808 then (q.toNat : Int)
  else (q.toNat : Int) - 18446744073709551616

def signed128 (lo hi : UInt64) : Int :=
  (lo.toNat : Int) + signed64 hi * 18446744073709551616

@[specialize] def block (a b : Nat → UInt32) : Nat → Nat → UInt64 → UInt64
  | 0, _, acc => acc
  | fuel + 1, i, acc =>
    block a b fuel (i + 1) (acc + extend32 (a i) * extend32 (b i))

@[specialize] def blocks (a b : Nat → UInt32) : Nat → Nat → UInt64 → UInt64 → UInt64 × UInt64
  | 0, _, lo, hi => (lo, hi)
  | count + 1, i, lo, hi =>
    let q := block a b 16 i 0
    blocks a b count (i + 16) (lo + q) (mergeHi lo hi q)

@[specialize] def body128 (n : Nat) (a b : Nat → UInt32) : UInt64 × UInt64 :=
  let full := blocks a b (n / 16) 0 0 0
  let q := block a b (n % 16) (n / 16 * 16) 0
  (full.1 + q, mergeHi full.1 full.2 q)

@[specialize] def body128Each (a b : Nat → UInt32) : Nat → Nat → UInt64 → UInt64 → UInt64 × UInt64
  | 0, _, lo, hi => (lo, hi)
  | fuel + 1, i, lo, hi =>
    let q := extend32 (a i) * extend32 (b i)
    body128Each a b fuel (i + 1) (lo + q) (mergeHi lo hi q)

@[inline] def magnitude32 (w : UInt32) : UInt32 :=
  if w &&& 0x80000000 != 0 then 0 - w else w

@[specialize] def maxMagnitude (f : Nat → UInt32) : Nat → Nat → UInt32 → UInt32
  | 0, _, mx => mx
  | fuel + 1, i, mx =>
    let v := magnitude32 (f i)
    maxMagnitude f fuel (i + 1) (if mx < v then v else mx)

@[inline] def canBlock16 (n : Nat) (ma mb : UInt32) : Bool :=
  n <= 1048576 && ma.toUInt64 * mb.toUInt64 < 576460752303423488

@[specialize] def preparedBody (n : Nat) (a b : Nat → UInt32) : UInt64 × UInt64 :=
  let ma := maxMagnitude a n 0 0
  let mb := maxMagnitude b n 0 0
  if canBlock16 n ma mb then body128 n a b else body128Each a b n 0 0 0

@[specialize] def preparedFinish (n : Nat) (a b : Nat → UInt32)
    (bias : Int) (exponent : Int) (negativeZero : Bool) : UInt32 :=
  let total := preparedBody n a b
  ExactRuntime.finishWord (signed128 total.1 total.2 + bias) exponent negativeZero

@[specialize] def guardedFinish (guard : Bool) (n : Nat) (a b : Nat → UInt32)
    (bias : Int) (exponent : Int) (negativeZero : Bool)
    (shipped : Unit → UInt32) : UInt32 :=
  if guard then preparedFinish n a b bias exponent negativeZero else shipped ()

theorem guardedFinish_false (n : Nat) (a b : Nat → UInt32)
    (bias exponent : Int) (negativeZero : Bool) (shipped : Unit → UInt32) :
    guardedFinish false n a b bias exponent negativeZero shipped = shipped () := by
  rfl

theorem guardedFinish_true (n : Nat) (a b : Nat → UInt32)
    (bias exponent : Int) (negativeZero : Bool) (shipped : Unit → UInt32) :
    guardedFinish true n a b bias exponent negativeZero shipped =
      preparedFinish n a b bias exponent negativeZero := by
  rfl

end Submission.R26WordBlock

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
    rw [exactTerms, termMass]
    exact (abs_add_le _ _).trans (add_le_add_left (ih (i + 1)) _)

theorem block_exact (a b : Nat → UInt32) (fuel i : Nat)
    (h : termMass a b fuel i < 9223372036854775808) :
    signed64 (block a b fuel i 0) = exactTerms a b fuel i := by
  have hb := lt_of_le_of_lt (exactTerms_abs_le a b fuel i) h
  have hz : Represents64 (0 : UInt64) 0 := ⟨0, by simp⟩
  apply signed64_unique _ _
  · simpa using block_represents a b fuel i 0 0 hz
  · exact ⟨(abs_lt.mp hb).1.le, (abs_lt.mp hb).2⟩


end Submission.R26WordBlock
