import ContractExact

/- Minimal actual raw-factor bridge, proof draft; no local Lean compilation.
   Definitions mirror R24ExactDotCost used by fp-raw5, with a fresh namespace.
   The sign predicate is left as official signOf; no false native-sign bridge. -/
namespace Submission.R26RawFactorProof
open ExactRuntime
open FloatLib.Floats FloatLib.Floats.Formats.BinaryInterchange

@[inline] def rawExp (w : UInt32) : UInt32 := (w >>> 23) &&& 255
@[inline] def rawFrac (w : UInt32) : UInt32 := w &&& 0x7fffff
@[inline] def rawMant (w : UInt32) : UInt64 :=
  if rawExp w == 0 then (rawFrac w).toUInt64
  else ((rawFrac w) ||| 0x800000).toUInt64
@[inline] def rawIdx (w : UInt32) : UInt32 := if rawExp w == 0 then 0 else rawExp w - 1

theorem rawExp_eq (w : UInt32) : rawExp w = expOf w := by rfl
theorem rawFrac_eq (w : UInt32) : rawFrac w = fracOf w := by rfl

theorem frac_or_hidden_toNat (w : UInt32) :
    (fracOf w ||| 0x800000).toNat = 2 ^ 23 + (fracOf w).toNat := by
  rw [UInt32.toNat_or, Nat.or_comm]
  change 8388608 ||| (fracOf w).toNat = 8388608 + (fracOf w).toNat
  simpa only [Nat.mul_one] using
    (Nat.two_pow_add_eq_or_of_lt (n := 23) (fracOf_toNat_lt w) 1).symm

theorem rawMant_toNat (w : UInt32) : (rawMant w).toNat = mantOf w := by
  unfold rawMant mantOf
  rw [rawExp_eq, rawFrac_eq]
  by_cases he : expOf w = 0
  · simp [he, UInt32.toNat_toUInt64]
  · simp [he, UInt32.toNat_toUInt64, frac_or_hidden_toNat]

theorem rawIdx_toNat (w : UInt32) : (rawIdx w).toNat = idxOf w := by
  unfold rawIdx idxOf
  rw [rawExp_eq]
  by_cases he : expOf w = 0
  · simp [he]
  · have hp : 1 ≤ (expOf w).toNat := by
      have hn : (expOf w).toNat ≠ 0 := by
        intro h
        apply he
        exact UInt32.toNat_inj.mp (by simpa using h)
      omega
    simp only [beq_iff_eq, he, ↓reduceIte]
    exact UInt32.toNat_sub_of_le _ _ (by simpa using hp)

theorem rawMant_lt (w : UInt32) : (rawMant w).toNat < 2 ^ 24 := by
  rw [rawMant_toNat]
  exact mantOf_lt_24 w

theorem rawProduct_toNat (a b : UInt32) :
    (rawMant a * rawMant b).toNat = mantOf a * mantOf b := by
  rw [UInt64.toNat_mul, rawMant_toNat, rawMant_toNat]
  exact Nat.mod_eq_of_lt (mul_mant_lt a b)

theorem rawIdx_le (w : UInt32) (h : expOf w ≠ 255) : (rawIdx w).toNat ≤ 253 := by
  rw [rawIdx_toNat]
  exact idxOf_le w h

theorem raw_factor_value (w : UInt32) :
    (decodeD w).toRat =
      ((if signOf w then -((rawMant w).toNat : Int) else ((rawMant w).toNat : Int)) : ℚ) *
        2 ^ (((rawIdx w).toNat : Int) - 149) := by
  rw [decodeD_toRat, rawMant_toNat, rawIdx_toNat]
  rfl

end Submission.R26RawFactorProof
