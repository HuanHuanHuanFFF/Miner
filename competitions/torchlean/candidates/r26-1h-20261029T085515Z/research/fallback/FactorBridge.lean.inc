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
