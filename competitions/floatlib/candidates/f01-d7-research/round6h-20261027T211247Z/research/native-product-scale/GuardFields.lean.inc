namespace Submission.R22NativeProductGuard
open FloatLib.Floats Competition

abbrev rawExponent (u : UInt32) : UInt32 :=
  (u >>> (23 : UInt32)) &&& (255 : UInt32)

/-- The actual runtime guards, including wrapping subtraction. No core/spec premise. -/
theorem guard_fields (u v : UInt32)
    (hnormal : rawExponent u - (1 : UInt32) <= (253 : UInt32) ∧
      rawExponent v - (1 : UInt32) <= (253 : UInt32))
    (hsum : rawExponent u + rawExponent v - (174 : UInt32) <= (206 : UInt32)) :
    (rawExponent u + rawExponent v).toNat = R2W01c.wordExp u + R2W01c.wordExp v ∧
    0 < R2W01c.wordExp u ∧ R2W01c.wordExp u < 255 ∧
    0 < R2W01c.wordExp v ∧ R2W01c.wordExp v < 255 ∧
    174 <= R2W01c.wordExp u + R2W01c.wordExp v ∧
    R2W01c.wordExp u + R2W01c.wordExp v <= 380 := by
  have hex (w : UInt32) : (rawExponent w).toNat = R2W01c.wordExp w := by
    rw [rawExponent, UInt32.toNat_and, UInt32.toNat_shiftRight]
    change (w.toNat >>> 23) &&& (2^8-1) = w.toNat / 8388608 % 256
    rw [Nat.and_two_pow_sub_one_eq_mod, Nat.shiftRight_eq_div_pow]
  have hub : (rawExponent u).toNat < 256 := by
    rw [hex]; exact Nat.mod_lt _ (by decide)
  have hvb : (rawExponent v).toNat < 256 := by
    rw [hex]; exact Nat.mod_lt _ (by decide)
  have hsumNat : (rawExponent u + rawExponent v).toNat =
      R2W01c.wordExp u + R2W01c.wordExp v := by
    rw [UInt32.toNat_add, Nat.mod_eq_of_lt (by omega), hex, hex]
  refine ⟨hsumNat, ?_⟩
  rcases hnormal with ⟨hu, hv⟩
  rw [UInt32.le_iff_toNat_le, UInt32.toNat_sub] at hu hv hsum
  change (4294967295 + (rawExponent u).toNat) % 4294967296 <= 253 at hu
  change (4294967295 + (rawExponent v).toNat) % 4294967296 <= 253 at hv
  change (4294967122 + (rawExponent u + rawExponent v).toNat) % 4294967296 <= 206 at hsum
  rw [hex] at hu hv hub hvb
  rw [hsumNat] at hsum
  omega

end Submission.R22NativeProductGuard
