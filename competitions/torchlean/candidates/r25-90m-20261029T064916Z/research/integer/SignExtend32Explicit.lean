import ContractExact

/- Original R25 explicit arithmetic proof draft. NOT_COMPILED/AX_NOT_RUN.
   The Nat xor quotient/remainder decomposition follows the already accessible
   R25 OrderKey.xor_sign_nat approach, specialized to bit31 and both cases.
   No bv_decide/native_decide, extra import, external code or axiom declaration. -/
namespace R25SignExtend32Explicit

@[inline] def extend (w : UInt32) : UInt64 :=
  (w.toUInt64 ^^^ 0x80000000) - 0x80000000

def signed32 (w : UInt32) : Int :=
  if w.toNat < 2147483648 then (w.toNat : Int) else (w.toNat : Int) - 4294967296

def signed64 (w : UInt64) : Int :=
  if w.toNat < 9223372036854775808 then (w.toNat : Int)
  else (w.toNat : Int) - 18446744073709551616

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

theorem xor_word_nat (w : UInt32) :
    (w.toUInt64 ^^^ 0x80000000).toNat =
      if w.toNat < 2147483648 then w.toNat + 2147483648 else w.toNat - 2147483648 := by
  rw [UInt64.toNat_xor, UInt32.toNat_toUInt64]
  change w.toNat ^^^ 2147483648 = _
  have hw := w.toNat_lt_size
  change w.toNat < 4294967296 at hw
  exact xor_bit31_nat w.toNat hw

theorem extend_nat (w : UInt32) :
    (extend w).toNat =
      if w.toNat < 2147483648 then w.toNat else w.toNat + 18446744069414584320 := by
  have hw := w.toNat_lt_size
  change w.toNat < 4294967296 at hw
  unfold extend
  rw [UInt64.toNat_sub, xor_word_nat]
  change ((if w.toNat < 2147483648 then w.toNat + 2147483648
        else w.toNat - 2147483648) + 18446744073709551616 - 2147483648) %
        18446744073709551616 = _
  by_cases hs : w.toNat < 2147483648
  · simp only [if_pos hs]
    omega
  · simp only [if_neg hs]
    omega

/-- Exact all-UInt32 integer interpretation of the actual xor/sub load. -/
theorem extend_signed (w : UInt32) : signed64 (extend w) = signed32 w := by
  have hw := w.toNat_lt_size
  change w.toNat < 4294967296 at hw
  unfold signed64 signed32
  simp only [extend_nat]
  split_ifs <;> omega

end R25SignExtend32Explicit
