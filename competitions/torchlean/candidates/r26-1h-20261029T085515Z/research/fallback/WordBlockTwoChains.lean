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
