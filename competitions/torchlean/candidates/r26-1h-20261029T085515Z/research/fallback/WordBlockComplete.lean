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

namespace Submission.R26WordBlock

def signed32 (w : UInt32) : Int :=
  if w.toNat < 2147483648 then (w.toNat : Int) else (w.toNat : Int) - 4294967296

theorem xor_bit31_nat (n : Nat) (hn : n < 4294967296) :
    n ^^^ 2147483648 =
      if n < 2147483648 then n + 2147483648 else n - 2147483648 := by
  have hd := Nat.xor_div_two_pow (a := n) (b := 2147483648) (n := 31)
  have hm := Nat.xor_mod_two_pow (a := n) (b := 2147483648) (n := 31)
  norm_num only [show (2 ^ 31 : Nat) = 2147483648 by decide,
    Nat.div_self, Nat.mod_self, Nat.xor_zero] at hd hm
  by_cases hs : n < 2147483648
  · have hz : n / 2147483648 = 0 := by omega
    simp only [hz, Nat.zero_xor] at hd
    rw [Nat.mod_eq_of_lt hs] at hm
    rw [if_pos hs]
    omega
  · have hz : n / 2147483648 = 1 := by omega
    simp only [hz, Nat.xor_self] at hd
    rw [if_neg hs]
    omega

theorem xor32_to64_nat (w : UInt32) :
    (w.toUInt64 ^^^ 0x80000000).toNat =
      if w.toNat < 2147483648 then w.toNat + 2147483648 else w.toNat - 2147483648 := by
  rw [UInt64.toNat_xor, UInt32.toNat_toUInt64]
  change w.toNat ^^^ 2147483648 = _
  exact xor_bit31_nat w.toNat w.toNat_lt

theorem extend32_nat (w : UInt32) :
    (extend32 w).toNat =
      if w.toNat < 2147483648 then w.toNat else w.toNat + 18446744069414584320 := by
  have hw := w.toNat_lt
  unfold extend32
  rw [UInt64.toNat_sub, xor32_to64_nat]
  norm_num only [UInt64.toNat_ofNat]
  split_ifs <;> omega

theorem extend32_signed (w : UInt32) : signed64 (extend32 w) = signed32 w := by
  have hw := w.toNat_lt
  unfold signed64 signed32
  simp only [extend32_nat]
  split_ifs <;> omega

def encodeMagnitude (negative : Bool) (m : Nat) : UInt32 :=
  if negative then 0 - UInt32.ofNat m else UInt32.ofNat m

theorem encodeMagnitude_signed (negative : Bool) (m : Nat) (hm : m < 2147483648) :
    signed32 (encodeMagnitude negative m) = if negative then -(m : Int) else m := by
  have hm32 : m < 4294967296 := by omega
  cases negative
  · simp [encodeMagnitude, signed32, UInt32.toNat_ofNat, Nat.mod_eq_of_lt hm32, hm]
  · simp only [encodeMagnitude, Bool.true_eq_true, ite_true, signed32, UInt32.toNat_sub,
      UInt32.toNat_zero, UInt32.toNat_ofNat, Nat.mod_eq_of_lt hm32, Nat.add_zero]
    split_ifs <;> omega

@[inline] def prepareFactor (w : UInt32) (base : Nat) : UInt32 :=
  encodeMagnitude (ExactRuntime.signOf w)
    (ExactRuntime.mantOf w * 2 ^ (ExactRuntime.idxOf w - base))

theorem prepareFactor_getter (w : UInt32) (base : Nat)
    (hm : ExactRuntime.mantOf w * 2 ^ (ExactRuntime.idxOf w - base) < 2147483648) :
    signed64 (extend32 (prepareFactor w base)) =
      ExactRuntime.sv w * (2 : Int) ^ (ExactRuntime.idxOf w - base) := by
  rw [extend32_signed]
  unfold prepareFactor
  rw [encodeMagnitude_signed _ _ hm]
  unfold ExactRuntime.sv
  split_ifs <;> push_cast <;> ring

def preparedArray (words : Array UInt32) (base : Nat) : Array UInt32 :=
  words.map (fun w => prepareFactor w base)

theorem preparedArray_get (words : Array UInt32) (base i : Nat) (hi : i < words.size) :
    (preparedArray words base)[i]! = prepareFactor words[i]! base := by
  simp [preparedArray, hi]

def encodedTerms (a b : Nat → UInt32) : Nat → Nat → Int
  | 0, _ => 0
  | fuel + 1, i => signed32 (a i) * signed32 (b i) + encodedTerms a b fuel (i + 1)

theorem exactTerms_encoded (a b : Nat → UInt32) (fuel i : Nat) :
    exactTerms a b fuel i = encodedTerms a b fuel i := by
  induction fuel generalizing i with
  | zero => rfl
  | succ fuel ih => simp only [exactTerms, encodedTerms, extend32_signed, ih]

def alignedTerms (a b : Nat → UInt32) (baseA baseB : Nat) : Nat → Nat → Int
  | 0, _ => 0
  | fuel + 1, i =>
    ExactRuntime.sv (a i) * ExactRuntime.sv (b i) *
      2 ^ (ExactRuntime.idxOf (a i) - baseA + (ExactRuntime.idxOf (b i) - baseB)) +
      alignedTerms a b baseA baseB fuel (i + 1)

theorem actual_getters_exact (a b : Nat → UInt32) (baseA baseB fuel i : Nat)
    (ha : ∀ j, i ≤ j → j < i + fuel →
      ExactRuntime.mantOf (a j) * 2 ^ (ExactRuntime.idxOf (a j) - baseA) < 2147483648)
    (hb : ∀ j, i ≤ j → j < i + fuel →
      ExactRuntime.mantOf (b j) * 2 ^ (ExactRuntime.idxOf (b j) - baseB) < 2147483648) :
    exactTerms (fun j => prepareFactor (a j) baseA) (fun j => prepareFactor (b j) baseB)
      fuel i = alignedTerms a b baseA baseB fuel i := by
  induction fuel generalizing i with
  | zero => rfl
  | succ fuel ih =>
    rw [exactTerms, alignedTerms,
      prepareFactor_getter _ _ (ha i (by omega) (by omega)),
      prepareFactor_getter _ _ (hb i (by omega) (by omega)),
      ih (i + 1) (fun j h1 h2 => ha j (by omega) (by omega))
        (fun j h1 h2 => hb j (by omega) (by omega)), pow_add]
    ring

end Submission.R26WordBlock

namespace Submission.R26WordBlock

theorem termMass_uniform (a b : Nat → UInt32) (fuel i : Nat) (bound : Int)
    (h : ∀ j, i ≤ j → j < i + fuel →
      |signed64 (extend32 (a j)) * signed64 (extend32 (b j))| ≤ bound) :
    termMass a b fuel i ≤ (fuel : Int) * bound := by
  induction fuel generalizing i with
  | zero => simp [termMass]
  | succ fuel ih =>
    have hh := h i (by omega) (by omega)
    have ht := ih (i + 1) (fun j h1 h2 => h j (by omega) (by omega))
    simp only [termMass, Nat.cast_add, Nat.cast_one]
    nlinarith

theorem block_exact_16 (a b : Nat → UInt32) (fuel i : Nat) (hf : fuel ≤ 16)
    (h : ∀ j, i ≤ j → j < i + fuel →
      |signed64 (extend32 (a j)) * signed64 (extend32 (b j))| < 576460752303423488) :
    signed64 (block a b fuel i 0) = exactTerms a b fuel i := by
  apply block_exact
  have hu := termMass_uniform a b fuel i 576460752303423487
    (fun j h1 h2 => by have := h j h1 h2; omega)
  omega

def blockSums (a b : Nat → UInt32) : Nat → Nat → Int
  | 0, _ => 0
  | count + 1, i => exactTerms a b 16 i + blockSums a b count (i + 16)

theorem exactTerms_add (a b : Nat → UInt32) (m n i : Nat) :
    exactTerms a b (m + n) i = exactTerms a b m i + exactTerms a b n (i + m) := by
  induction m generalizing i with
  | zero => simp [exactTerms]
  | succ m ih =>
    simp [Nat.succ_add, exactTerms, ih, Nat.add_assoc, Nat.add_comm,
      Nat.add_left_comm, Int.add_assoc]

theorem blockSums_eq (a b : Nat → UInt32) (count i : Nat) :
    blockSums a b count i = exactTerms a b (count * 16) i := by
  induction count generalizing i with
  | zero => simp [blockSums, exactTerms]
  | succ count ih =>
    rw [blockSums, ih]
    have hn : (count + 1) * 16 = 16 + count * 16 := by omega
    rw [hn, exactTerms_add]

theorem blocks_represents (a b : Nat → UInt32) (count i : Nat)
    (lo hi : UInt64) (initial : Int) (hinit : Represents128 lo hi initial)
    (hblock : ∀ j, j < count →
      termMass a b 16 (i + j * 16) < 9223372036854775808) :
    Represents128 (blocks a b count i lo hi).1 (blocks a b count i lo hi).2
      (initial + blockSums a b count i) := by
  induction count generalizing i lo hi initial with
  | zero => simpa [blocks, blockSums] using hinit
  | succ count ih =>
    have hfirst : signed64 (block a b 16 i 0) = exactTerms a b 16 i := by
      exact block_exact a b 16 i (by simpa using hblock 0 (by omega))
    have hs := merge_represents128 lo hi (block a b 16 i 0) initial hinit
    rw [hfirst] at hs
    have ht : ∀ j, j < count →
        termMass a b 16 (i + 16 + j * 16) < 9223372036854775808 := by
      intro j hj
      have hh := hblock (j + 1) (by omega)
      convert hh using 1 <;> omega
    simpa only [blocks, blockSums, Int.add_assoc] using
      ih (i + 16) (lo + block a b 16 i 0) (mergeHi lo hi (block a b 16 i 0))
        (initial + exactTerms a b 16 i) hs ht

theorem body128_represents (n : Nat) (a b : Nat → UInt32)
    (hblock : ∀ j, j < n / 16 →
      termMass a b 16 (j * 16) < 9223372036854775808)
    (htail : termMass a b (n % 16) (n / 16 * 16) < 9223372036854775808) :
    Represents128 (body128 n a b).1 (body128 n a b).2 (exactTerms a b n 0) := by
  have hz : Represents128 (0 : UInt64) 0 0 := ⟨0, by simp⟩
  have hb := blocks_represents a b (n / 16) 0 0 0 0 hz (by simpa using hblock)
  simp only [zero_add, blockSums_eq] at hb
  have ht := merge_represents128 (blocks a b (n / 16) 0 0 0).1
    (blocks a b (n / 16) 0 0 0).2 (block a b (n % 16) (n / 16 * 16) 0)
    (exactTerms a b (n / 16 * 16) 0) hb
  rw [block_exact a b (n % 16) (n / 16 * 16) htail] at ht
  have hn : n / 16 * 16 + n % 16 = n := by omega
  have hsplit := exactTerms_add a b (n / 16 * 16) (n % 16) 0
  rw [hn, zero_add] at hsplit
  simpa only [body128, hsplit] using ht

theorem body128_exact (n : Nat) (a b : Nat → UInt32)
    (hblock : ∀ j, j < n / 16 →
      termMass a b 16 (j * 16) < 9223372036854775808)
    (htail : termMass a b (n % 16) (n / 16 * 16) < 9223372036854775808)
    (hglobal : -170141183460469231731687303715884105728 ≤ exactTerms a b n 0 ∧
      exactTerms a b n 0 < 170141183460469231731687303715884105728) :
    signed128 (body128 n a b).1 (body128 n a b).2 = exactTerms a b n 0 :=
  signed128_unique _ _ _ (body128_represents n a b hblock htail) hglobal

theorem finish_body128 (n : Nat) (a b : Nat → UInt32) (bias exponent : Int) (nz : Bool)
    (hexact : signed128 (body128 n a b).1 (body128 n a b).2 = exactTerms a b n 0) :
    ExactRuntime.finishWord (signed128 (body128 n a b).1 (body128 n a b).2 + bias) exponent nz =
      ExactRuntime.finishWord (exactTerms a b n 0 + bias) exponent nz := by
  rw [hexact]

end Submission.R26WordBlock

namespace Submission.R26WordBlock

theorem signed32_abs_bound (w : UInt32) : |signed32 w| ≤ 2147483648 := by
  have hw := w.toNat_lt
  unfold signed32
  split_ifs with h
  · rw [abs_of_nonneg (by omega)]
    omega
  · rw [abs_of_nonpos (by omega)]
    omega

theorem term_abs_bound (a b : UInt32) :
    |signed64 (extend32 a) * signed64 (extend32 b)| ≤ 4611686018427387904 := by
  rw [extend32_signed, extend32_signed, abs_mul]
  have ha := signed32_abs_bound a
  have hb := signed32_abs_bound b
  nlinarith [abs_nonneg (signed32 a), abs_nonneg (signed32 b)]

theorem each_product_exact (a b : UInt32) :
    signed64 (extend32 a * extend32 b) = signed64 (extend32 a) * signed64 (extend32 b) := by
  apply signed64_unique
  · exact mul_represents64 _ _ _ _ (signed64_represents _) (signed64_represents _)
  · have h := term_abs_bound a b
    have hh := abs_le.mp h
    omega

theorem body128Each_represents (a b : Nat → UInt32) (fuel i : Nat)
    (lo hi : UInt64) (initial : Int) (h : Represents128 lo hi initial) :
    Represents128 (body128Each a b fuel i lo hi).1 (body128Each a b fuel i lo hi).2
      (initial + exactTerms a b fuel i) := by
  induction fuel generalizing i lo hi initial with
  | zero => simpa [body128Each, exactTerms] using h
  | succ fuel ih =>
    have hs := merge_represents128 lo hi (extend32 (a i) * extend32 (b i)) initial h
    rw [each_product_exact] at hs
    simpa only [body128Each, exactTerms, Int.add_assoc] using
      ih (i + 1) (lo + extend32 (a i) * extend32 (b i))
        (mergeHi lo hi (extend32 (a i) * extend32 (b i)))
        (initial + signed64 (extend32 (a i)) * signed64 (extend32 (b i))) hs

theorem exactTerms_global_bound (n : Nat) (a b : Nat → UInt32) (hn : n ≤ 1048576) :
    -170141183460469231731687303715884105728 ≤ exactTerms a b n 0 ∧
      exactTerms a b n 0 < 170141183460469231731687303715884105728 := by
  have hb := termMass_uniform a b n 0 4611686018427387904
    (fun j _ _ => term_abs_bound (a j) (b j))
  have ha := exactTerms_abs_le a b n 0
  have hh := abs_le.mp (le_trans ha hb)
  omega

theorem body128Each_exact (n : Nat) (a b : Nat → UInt32) (hn : n ≤ 1048576) :
    signed128 (body128Each a b n 0 0 0).1 (body128Each a b n 0 0 0).2 =
      exactTerms a b n 0 := by
  apply signed128_unique
  · have hz : Represents128 (0 : UInt64) 0 0 := ⟨0, by simp⟩
    simpa using body128Each_represents a b n 0 0 0 0 hz
  · exact exactTerms_global_bound n a b hn

theorem signMask32_nat (w : UInt32) :
    (w &&& 0x80000000).toNat = (w.toNat / 2147483648) * 2147483648 := by
  rw [UInt32.toNat_and]
  change w.toNat &&& 2147483648 = _
  have hw := w.toNat_lt
  have hd := Nat.and_div_two_pow (a := w.toNat) (b := 2147483648) (n := 31)
  have hm := Nat.and_mod_two_pow (a := w.toNat) (b := 2147483648) (n := 31)
  norm_num only [show (2 ^ 31 : Nat) = 2147483648 by decide,
    Nat.div_self, Nat.mod_self, Nat.and_zero] at hd hm
  have hs : w.toNat / 2147483648 = 0 ∨ w.toNat / 2147483648 = 1 := by omega
  rcases hs with hs | hs <;> simp only [hs] at hd <;> norm_num at hd <;> omega

theorem magnitude32_abs (w : UInt32) : (magnitude32 w).toNat = (signed32 w).natAbs := by
  have hw := w.toNat_lt
  have hm := signMask32_nat w
  by_cases hs : w.toNat < 2147483648
  · have hz : w &&& 0x80000000 = 0 := by
      apply UInt32.toNat_inj.mp
      rw [hm]
      change w.toNat / 2147483648 * 2147483648 = 0
      omega
    simp [magnitude32, hz, signed32, hs]
  · have hn : w &&& 0x80000000 ≠ 0 := by
      intro hz
      have he := congrArg UInt32.toNat hz
      rw [hm] at he
      change w.toNat / 2147483648 * 2147483648 = 0 at he
      omega
    have hi : (w.toNat : Int) - 4294967296 ≤ 0 := by omega
    have hiabs : ((w.toNat : Int) - 4294967296).natAbs = 4294967296 - w.toNat := by
      apply Int.ofNat_inj.mp
      rw [Int.natCast_natAbs, abs_of_nonpos hi]
      omega
    simp only [magnitude32, bne_iff_ne.mpr hn, ite_true, UInt32.toNat_sub,
      UInt32.toNat_zero, Nat.add_zero, signed32, if_neg hs, hiabs]
    omega

theorem maxMagnitude_initial (f : Nat → UInt32) (fuel i : Nat) (mx : UInt32) :
    mx ≤ maxMagnitude f fuel i mx := by
  induction fuel generalizing i mx with
  | zero => simp [maxMagnitude]
  | succ fuel ih =>
    simp only [maxMagnitude]
    split_ifs with h
    · exact le_trans (le_of_lt h) (ih (i + 1) (magnitude32 (f i)))
    · exact ih (i + 1) mx

theorem maxMagnitude_term (f : Nat → UInt32) (fuel i : Nat) (mx : UInt32)
    (j : Nat) (hj : i ≤ j) (hstop : j < i + fuel) :
    magnitude32 (f j) ≤ maxMagnitude f fuel i mx := by
  induction fuel generalizing i mx with
  | zero => omega
  | succ fuel ih =>
    by_cases heq : j = i
    · subst j
      simp only [maxMagnitude]
      split_ifs with h
      · exact maxMagnitude_initial f fuel (i + 1) _
      · exact le_trans (le_of_not_gt h) (maxMagnitude_initial f fuel (i + 1) mx)
    · simp only [maxMagnitude]
      exact ih (i + 1) _ (by omega) (by omega)

theorem maxMagnitude_abs (f : Nat → UInt32) (n j : Nat) (hj : j < n) :
    |signed64 (extend32 (f j))| ≤ ((maxMagnitude f n 0 0).toNat : Int) := by
  have h := maxMagnitude_term f n 0 0 j (by omega) (by omega)
  rw [UInt32.le_iff_toNat_le, magnitude32_abs] at h
  rw [extend32_signed, ← Int.natCast_natAbs]
  exact_mod_cast h

theorem canBlock16_terms (n : Nat) (a b : Nat → UInt32)
    (hg : canBlock16 n (maxMagnitude a n 0 0) (maxMagnitude b n 0 0) = true)
    (j : Nat) (hj : j < n) :
    |signed64 (extend32 (a j)) * signed64 (extend32 (b j))| < 576460752303423488 := by
  have ha := maxMagnitude_abs a n j hj
  have hb := maxMagnitude_abs b n j hj
  have hma := (maxMagnitude a n 0 0).toNat_lt
  have hmb := (maxMagnitude b n 0 0).toNat_lt
  have hp : (maxMagnitude a n 0 0).toNat * (maxMagnitude b n 0 0).toNat < 18446744073709551616 := by
    have h := Nat.mul_lt_mul'' hma hmb
    norm_num at h
    exact h
  simp only [canBlock16, Bool.and_eq_true, decide_eq_true_eq] at hg
  have hlt := hg.2
  rw [UInt64.lt_iff_toNat_lt, UInt64.toNat_mul, UInt32.toNat_toUInt64,
    UInt32.toNat_toUInt64, Nat.mod_eq_of_lt hp] at hlt
  change (maxMagnitude a n 0 0).toNat * (maxMagnitude b n 0 0).toNat <
    576460752303423488 at hlt
  rw [abs_mul]
  have hab : |signed64 (extend32 (a j))| * |signed64 (extend32 (b j))| ≤
      ((maxMagnitude a n 0 0).toNat : Int) * (maxMagnitude b n 0 0).toNat :=
    mul_le_mul ha hb (abs_nonneg _) (by positivity)
  have hcast : ((maxMagnitude a n 0 0).toNat : Int) * (maxMagnitude b n 0 0).toNat <
      576460752303423488 := by exact_mod_cast hlt
  exact lt_of_le_of_lt hab hcast

theorem preparedBody_exact (n : Nat) (a b : Nat → UInt32) (hn : n ≤ 1048576) :
    signed128 (preparedBody n a b).1 (preparedBody n a b).2 = exactTerms a b n 0 := by
  unfold preparedBody
  split_ifs with hg
  · apply body128_exact
    · intro j hj
      have hu := termMass_uniform a b 16 (j * 16) 576460752303423487
        (fun k h1 h2 => by
          have hkn : k < n := by omega
          have hh := canBlock16_terms n a b hg k hkn
          omega)
      norm_num at hu
      omega
    · have hu := termMass_uniform a b (n % 16) (n / 16 * 16) 576460752303423487
        (fun k h1 h2 => by
          have hkn : k < n := by omega
          have hh := canBlock16_terms n a b hg k hkn
          omega)
      have hrem : n % 16 < 16 := Nat.mod_lt _ (by omega)
      omega
    · exact exactTerms_global_bound n a b hn
  · exact body128Each_exact n a b hn

theorem preparedFinish_exact (n : Nat) (a b : Nat → UInt32) (hn : n ≤ 1048576)
    (bias exponent : Int) (nz : Bool) :
    preparedFinish n a b bias exponent nz =
      ExactRuntime.finishWord (exactTerms a b n 0 + bias) exponent nz := by
  simp only [preparedFinish, preparedBody_exact n a b hn]

end Submission.R26WordBlock

namespace Submission.R26WordBlock
open ExactRuntime FloatLib.Numerics
open FloatLib.Floats FloatLib.Floats.Formats.BinaryInterchange

def rawWords (n : Nat) (f : Nat → UInt32) : Array UInt32 :=
  Array.ofFn (n := n) fun i => f i.val

theorem rawWords_get (n : Nat) (f : Nat → UInt32) (k : Nat) (hk : k < n) :
    (rawWords n f)[k]! = f k := by
  rw [getElem!_pos _ k (by simpa [rawWords] using hk)]
  simp [rawWords]

theorem dotOf_finite_finish (n : Nat) (fa fb : Nat → UInt32)
    (hfin : ∀ k, k < n → expOf (fa k) ≠ 255 ∧ expOf (fb k) ≠ 255) :
    dotOf n fa fb = finishWord (dsum (rawWords n fa) (rawWords n fb) 0 n) (-298)
      (decide (n ≠ 0) && dallNZ (rawWords n fa) (rawWords n fb) 0 n) := by
  let A := rawWords n fa
  let B := rawWords n fb
  let L := A.map (Model.ofUInt32 (fmt := Fmt))
  let R := B.map (Model.ofUInt32 (fmt := Fmt))
  let T := dsum A B 0 n
  have hAs : A.size = n := by simp [A, rawWords]
  have hBs : B.size = n := by simp [B, rawWords]
  have hLs : L.size = n := by simp [L, hAs]
  have hRs : R.size = n := by simp [R, hBs]
  have hLR : L.size = R.size := by omega
  have hall : ∀ k, 0 ≤ k → k < n → expOf A[k]! ≠ 255 ∧ expOf B[k]! ≠ 255 := by
    intro k _ hk
    simpa only [A, B, rawWords_get n fa k hk, rawWords_get n fb k hk] using hfin k hk
  have hLfin : ∀ k (hk : k < L.size), Model.isFinite L[k] = true := by
    intro k hk
    have hkA : k < A.size := by omega
    have hf := (hall k (by omega) (by omega)).1
    rw [getElem!_pos A k hkA] at hf
    simpa [L, isFinite_ofUInt32] using hf
  have hRfin : ∀ k (hk : k < R.size), Model.isFinite R[k] = true := by
    intro k hk
    have hkB : k < B.size := by omega
    have hf := (hall k (by omega) (by omega)).2
    rw [getElem!_pos B k hkB] at hf
    simpa [R, isFinite_ofUInt32] using hf
  have hslice : Model.Reduction.Semantics.finiteDotSlice L R 0 L.size (by simp)
      (by simp [hLR]) = (T : Rat) * 2 ^ (-298 : Int) := by
    have h := finiteDotSlice_eq A B 0 L.size (by simp [L]) (by simp [L, hAs, hBs])
      (fun k h1 h2 => hall k h1 (by omega))
    simpa only [hLs] using h
  have hexact := Model.Reduction.Internal.dotState_exact_toRat
    (destination := Fmt) L R hLR hLfin hRfin
  change dotSpec A B = finishWord T (-298) (decide (n ≠ 0) && dallNZ A B 0 n)
  unfold dotSpec Model.dot
  by_cases hT : T = 0
  · have hzero : (Model.Reduction.Internal.dotState L R hLR :
        Model.Reduction.Internal.State Fmt).exact.significand = 0 := by
      rw [← Dyadic.toRat_eq_zero_iff, hexact, hslice, hT]
      simp
    rw [Model.Reduction.dotWithStatus_eq_zero_of_finite Fmt L R .nearestEven hLR hLfin hRfin
      hzero, hT, finishWord_zero]
    unfold Model.Reduction.Internal.dotState
    obtain ⟨h1, h2⟩ := dotStateLoop_flags A B {} 0 L.size (by simp [L])
      (by simp [L, hAs, hBs]) (fun k h1 h2 => hall k h1 (by omega))
    simp only [Bool.false_or, Bool.true_and] at h1 h2
    simp only [Except.map, h1, h2, hLs]
  · have hnz : Model.Reduction.Semantics.finiteDot L.toList R.toList ≠ .ok 0 := by
      rw [Model.Reduction.Semantics.finiteDot_toList_eq_slice L R hLR]
      intro hz
      injection hz with hz
      rw [hslice] at hz
      simp at hz
      exact hT hz
    rw [Model.Reduction.dotWithStatus_eq_round_of_finite_nonzero Fmt L R .nearestEven hLR
      hLfin hRfin hnz]
    simp only [Except.map]
    exact (finishWord_of_ne _ _ _ _ hT (by rw [hexact, hslice])).symm

theorem guardedFinish_correct (guard : Bool) (n : Nat) (fa fb a b : Nat → UInt32)
    (bias exponent : Int) (nz : Bool) (shipped : Unit → UInt32)
    (hship : shipped () = dotOf n fa fb)
    (hsize : guard = true → n ≤ 1048576)
    (hfinite : guard = true → ∀ k, k < n → expOf (fa k) ≠ 255 ∧ expOf (fb k) ≠ 255)
    (hvalue : guard = true → finishWord (exactTerms a b n 0 + bias) exponent nz =
      finishWord (dsum (rawWords n fa) (rawWords n fb) 0 n) (-298)
        (decide (n ≠ 0) && dallNZ (rawWords n fa) (rawWords n fb) 0 n)) :
    guardedFinish guard n a b bias exponent nz shipped = dotOf n fa fb := by
  cases guard
  · simpa only [guardedFinish_false] using hship
  · rw [guardedFinish_true, preparedFinish_exact n a b (hsize rfl), hvalue rfl]
    exact (dotOf_finite_finish n fa fb (hfinite rfl)).symm

end Submission.R26WordBlock

namespace Submission.R26WordBlock
open ExactRuntime

def rawSum (a b : Nat → UInt32) : Nat → Nat → Int
  | 0, _ => 0
  | fuel + 1, i => sv (a i) * sv (b i) * 2 ^ (idxOf (a i) + idxOf (b i)) +
      rawSum a b fuel (i + 1)

theorem rawSum_dsum (n : Nat) (a b : Nat → UInt32) (fuel i : Nat) (hi : i + fuel ≤ n) :
    rawSum a b fuel i = dsum (rawWords n a) (rawWords n b) i fuel := by
  induction fuel generalizing i with
  | zero => rfl
  | succ fuel ih =>
    rw [rawSum, dsum, rawWords_get n a i (by omega), rawWords_get n b i (by omega),
      ih (i + 1) (by omega)]

theorem sv_zero (w : UInt32) (h : mantOf w = 0) : sv w = 0 := by
  simp [sv, h]

theorem alignedTerms_scale (a b : Nat → UInt32) (baseA baseB fuel i : Nat)
    (ha : ∀ j, i ≤ j → j < i + fuel → mantOf (a j) ≠ 0 → baseA ≤ idxOf (a j))
    (hb : ∀ j, i ≤ j → j < i + fuel → mantOf (b j) ≠ 0 → baseB ≤ idxOf (b j)) :
    alignedTerms a b baseA baseB fuel i * 2 ^ (baseA + baseB) = rawSum a b fuel i := by
  induction fuel generalizing i with
  | zero => simp [alignedTerms, rawSum]
  | succ fuel ih =>
    rw [alignedTerms, add_mul,
      ih (i + 1) (fun j h1 h2 hn => ha j (by omega) (by omega) hn)
        (fun j h1 h2 hn => hb j (by omega) (by omega) hn), rawSum]
    congr 1
    by_cases hza : mantOf (a i) = 0
    · simp [sv_zero (a i) hza]
    by_cases hzb : mantOf (b i) = 0
    · simp [sv_zero (b i) hzb]
    have hia := ha i (by omega) (by omega) hza
    have hib := hb i (by omega) (by omega) hzb
    have hexp : idxOf (a i) - baseA + (idxOf (b i) - baseB) + (baseA + baseB) =
        idxOf (a i) + idxOf (b i) := by omega
    rw [mul_assoc, ← pow_add, hexp]

theorem prepared_body_scaled (n : Nat) (a b : Nat → UInt32) (baseA baseB : Nat)
    (ha : ∀ j, j < n → mantOf (a j) * 2 ^ (idxOf (a j) - baseA) < 2147483648)
    (hb : ∀ j, j < n → mantOf (b j) * 2 ^ (idxOf (b j) - baseB) < 2147483648)
    (hla : ∀ j, j < n → mantOf (a j) ≠ 0 → baseA ≤ idxOf (a j))
    (hlb : ∀ j, j < n → mantOf (b j) ≠ 0 → baseB ≤ idxOf (b j)) :
    exactTerms (fun j => prepareFactor (a j) baseA) (fun j => prepareFactor (b j) baseB) n 0 *
      2 ^ (baseA + baseB) = dsum (rawWords n a) (rawWords n b) 0 n := by
  rw [actual_getters_exact a b baseA baseB n 0 (fun j _ hj => ha j (by omega))
      (fun j _ hj => hb j (by omega)),
    alignedTerms_scale a b baseA baseB n 0 (fun j _ hj hn => hla j (by omega) hn)
      (fun j _ hj hn => hlb j (by omega) hn),
    rawSum_dsum n a b n 0 (by omega)]

def scaledBias (word : UInt32) (base : Nat) : Int :=
  sv word * 2 ^ (idxOf word + 149 - base)

theorem scaledBias_exact (word : UInt32) (base : Nat) (h : base ≤ idxOf word + 149) :
    scaledBias word base * 2 ^ base = sv word * 2 ^ (idxOf word + 149) := by
  unfold scaledBias
  rw [mul_assoc, ← pow_add]
  congr 2
  omega

theorem finish_prepared_scaled (n : Nat) (a b : Nat → UInt32) (baseA baseB : Nat)
    (hn : n ≤ 1048576) (biasWord : UInt32) (nz : Bool)
    (ha : ∀ j, j < n → mantOf (a j) * 2 ^ (idxOf (a j) - baseA) < 2147483648)
    (hb : ∀ j, j < n → mantOf (b j) * 2 ^ (idxOf (b j) - baseB) < 2147483648)
    (hla : ∀ j, j < n → mantOf (a j) ≠ 0 → baseA ≤ idxOf (a j))
    (hlb : ∀ j, j < n → mantOf (b j) ≠ 0 → baseB ≤ idxOf (b j))
    (hbi : baseA + baseB ≤ idxOf biasWord + 149) :
    preparedFinish n (fun j => prepareFactor (a j) baseA) (fun j => prepareFactor (b j) baseB)
      (scaledBias biasWord (baseA + baseB)) (-298 + ((baseA + baseB : Nat) : Int)) nz =
      finishWord (dsum (rawWords n a) (rawWords n b) 0 n +
        sv biasWord * 2 ^ (idxOf biasWord + 149)) (-298) nz := by
  rw [preparedFinish_exact _ _ _ hn, finishWord_scale, add_mul,
    prepared_body_scaled n a b baseA baseB ha hb hla hlb,
    scaledBias_exact biasWord (baseA + baseB) hbi]

end Submission.R26WordBlock

namespace Submission.R26WordBlock
open ExactRuntime

def biasedA (n : Nat) (a : Nat → UInt32) (i : Nat) : UInt32 := if i < n then a i else oneW
def biasedB (n : Nat) (b : Nat → UInt32) (bias : UInt32) (i : Nat) : UInt32 :=
  if i < n then b i else bias

theorem rawSum_add (a b : Nat → UInt32) (m n i : Nat) :
    rawSum a b (m + n) i = rawSum a b m i + rawSum a b n (i + m) := by
  induction m generalizing i with
  | zero => simp [rawSum]
  | succ m ih =>
    simp [Nat.succ_add, rawSum, ih, Nat.add_assoc, Nat.add_comm,
      Nat.add_left_comm, Int.add_assoc]

theorem rawSum_congr (a b c d : Nat → UInt32) (fuel i : Nat)
    (h : ∀ j, i ≤ j → j < i + fuel → a j = c j ∧ b j = d j) :
    rawSum a b fuel i = rawSum c d fuel i := by
  induction fuel generalizing i with
  | zero => rfl
  | succ fuel ih =>
    have hh := h i (by omega) (by omega)
    rw [rawSum, rawSum, hh.1, hh.2,
      ih (i + 1) (fun j h1 h2 => h j (by omega) (by omega))]

theorem rawSum_biased (n : Nat) (a b : Nat → UInt32) (bias : UInt32) :
    rawSum (biasedA n a) (biasedB n b bias) (n + 1) 0 =
      rawSum a b n 0 + sv bias * 2 ^ (idxOf bias + 149) := by
  rw [rawSum_add]
  have hbody : rawSum (biasedA n a) (biasedB n b bias) n 0 = rawSum a b n 0 := by
    apply rawSum_congr
    intro j _ hj
    simp only [biasedA, biasedB, if_pos (by omega : j < n)]
    exact ⟨rfl, rfl⟩
  rw [hbody]
  simp only [zero_add, rawSum, biasedA, biasedB, Nat.lt_irrefl, if_false, add_zero]
  have hone : sv oneW = 8388608 ∧ idxOf oneW = 126 := by decide
  rw [hone.1, hone.2]
  congr 1
  calc
    8388608 * sv bias * (2 : Int) ^ (126 + idxOf bias) =
        sv bias * ((2 : Int) ^ 23 * 2 ^ (126 + idxOf bias)) := by norm_num; ring
    _ = sv bias * 2 ^ (idxOf bias + 149) := by
      rw [← pow_add]
      congr 2
      omega

theorem biased_dsum (n : Nat) (a b : Nat → UInt32) (bias : UInt32) :
    dsum (rawWords (n + 1) (biasedA n a)) (rawWords (n + 1) (biasedB n b bias)) 0 (n + 1) =
      dsum (rawWords n a) (rawWords n b) 0 n + sv bias * 2 ^ (idxOf bias + 149) := by
  rw [← rawSum_dsum (n + 1) _ _ (n + 1) 0 (by omega), rawSum_biased,
    rawSum_dsum n a b n 0 (by omega)]

theorem finish_prepared_bias_dot (n : Nat) (a b : Nat → UInt32) (baseA baseB : Nat)
    (hn : n ≤ 1048576) (bias : UInt32) (nz : Bool)
    (ha : ∀ j, j < n → mantOf (a j) * 2 ^ (idxOf (a j) - baseA) < 2147483648)
    (hb : ∀ j, j < n → mantOf (b j) * 2 ^ (idxOf (b j) - baseB) < 2147483648)
    (hla : ∀ j, j < n → mantOf (a j) ≠ 0 → baseA ≤ idxOf (a j))
    (hlb : ∀ j, j < n → mantOf (b j) ≠ 0 → baseB ≤ idxOf (b j))
    (hbi : baseA + baseB ≤ idxOf bias + 149)
    (hfinite : ∀ j, j < n → expOf (a j) ≠ 255 ∧ expOf (b j) ≠ 255)
    (hfb : expOf bias ≠ 255)
    (hzero : nz = dallNZ (rawWords (n + 1) (biasedA n a))
      (rawWords (n + 1) (biasedB n b bias)) 0 (n + 1)) :
    preparedFinish n (fun j => prepareFactor (a j) baseA) (fun j => prepareFactor (b j) baseB)
      (scaledBias bias (baseA + baseB)) (-298 + ((baseA + baseB : Nat) : Int)) nz =
      dotOf (n + 1) (biasedA n a) (biasedB n b bias) := by
  rw [finish_prepared_scaled n a b baseA baseB hn bias nz ha hb hla hlb hbi, ← biased_dsum]
  have hf : ∀ j, j < n + 1 → expOf (biasedA n a j) ≠ 255 ∧
      expOf (biasedB n b bias j) ≠ 255 := by
    intro j hj
    by_cases hbody : j < n
    · simpa [biasedA, biasedB, hbody] using hfinite j hbody
    · simp [biasedA, biasedB, hbody, hfb, oneW, expOf]
  rw [dotOf_finite_finish (n + 1) _ _ hf]
  simp [hzero]

end Submission.R26WordBlock

namespace Submission.R26WordBlock
open ExactRuntime

@[specialize] def zeroSafeFinish (guard : Bool) (n : Nat) (a b : Nat → UInt32)
    (bias exponent : Int) (shipped : Unit → UInt32) : UInt32 :=
  if guard then
    let pair := preparedBody n a b
    let total := signed128 pair.1 pair.2 + bias
    if total = 0 then shipped () else finishWord total exponent false
  else shipped ()

theorem zeroSafeFinish_false (n : Nat) (a b : Nat → UInt32)
    (bias exponent : Int) (shipped : Unit → UInt32) :
    zeroSafeFinish false n a b bias exponent shipped = shipped () := rfl

theorem zeroSafeFinish_zero (n : Nat) (a b : Nat → UInt32)
    (bias exponent : Int) (shipped : Unit → UInt32)
    (hz : signed128 (preparedBody n a b).1 (preparedBody n a b).2 + bias = 0) :
    zeroSafeFinish true n a b bias exponent shipped = shipped () := by
  simp [zeroSafeFinish, hz]

theorem finishWord_flag_irrelevant (T e : Int) (nz : Bool) (h : T ≠ 0) :
    finishWord T e false = finishWord T e nz := by
  simp [finishWord, h]

theorem zeroSafeFinish_of_prepared (guard : Bool) (n : Nat) (a b : Nat → UInt32)
    (bias exponent : Int) (nz : Bool) (shipped : Unit → UInt32) (wanted : UInt32)
    (hship : shipped () = wanted)
    (hfast : guard = true → preparedFinish n a b bias exponent nz = wanted) :
    zeroSafeFinish guard n a b bias exponent shipped = wanted := by
  cases guard
  · exact hship
  · unfold zeroSafeFinish
    simp only [Bool.true_eq_true, ite_true]
    split_ifs with hz
    · exact hship
    · rw [finishWord_flag_irrelevant _ _ nz hz]
      exact hfast rfl

theorem zeroSafeFinish_bias_dot (n : Nat) (a b : Nat → UInt32) (baseA baseB : Nat)
    (hn : n ≤ 1048576) (bias : UInt32) (shipped : Unit → UInt32)
    (hship : shipped () = dotOf (n + 1) (biasedA n a) (biasedB n b bias))
    (ha : ∀ j, j < n → mantOf (a j) * 2 ^ (idxOf (a j) - baseA) < 2147483648)
    (hb : ∀ j, j < n → mantOf (b j) * 2 ^ (idxOf (b j) - baseB) < 2147483648)
    (hla : ∀ j, j < n → mantOf (a j) ≠ 0 → baseA ≤ idxOf (a j))
    (hlb : ∀ j, j < n → mantOf (b j) ≠ 0 → baseB ≤ idxOf (b j))
    (hbi : baseA + baseB ≤ idxOf bias + 149)
    (hfinite : ∀ j, j < n → expOf (a j) ≠ 255 ∧ expOf (b j) ≠ 255)
    (hfb : expOf bias ≠ 255) :
    zeroSafeFinish true n (fun j => prepareFactor (a j) baseA) (fun j => prepareFactor (b j) baseB)
      (scaledBias bias (baseA + baseB)) (-298 + ((baseA + baseB : Nat) : Int)) shipped =
      dotOf (n + 1) (biasedA n a) (biasedB n b bias) := by
  apply zeroSafeFinish_of_prepared _ _ _ _ _ _
    (dallNZ (rawWords (n + 1) (biasedA n a)) (rawWords (n + 1) (biasedB n b bias)) 0 (n + 1))
    _ _ hship
  intro _
  exact finish_prepared_bias_dot n a b baseA baseB hn bias _ ha hb hla hlb hbi hfinite hfb rfl

end Submission.R26WordBlock
