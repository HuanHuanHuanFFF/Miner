/- Connect the unchanged actual PortableF64 normal/zero branches to Widen7.
   Requires the exact three FastMul log2 runtime definitions and actual
   R24PortableF64.widenBits. No nonzero subnormal claim is made here. -/
namespace Submission.R25ActualWiden
open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange
open R2W01c
open Submission.R24RepresentationWiden

theorem actual_sign_eq (u : UInt32) :
    (u.toUInt64 &&& 0x80000000) <<< 32 = signWord u := by
  apply UInt64.toNat_inj.mp
  rw [UInt64.toNat_shiftLeft, UInt64.toNat_and, UInt32.toNat_toUInt64,
    signWord_toNat]
  change ((u.toNat &&& 2 ^ 31) <<< 32) % 18446744073709551616 =
    u.toNat / 2147483648 * 9223372036854775808
  rw [Nat.and_two_pow, Nat.testBit_eq_decide_div_mod_eq, Nat.shiftLeft_eq]
  have hu := u.toNat_lt_size
  change u.toNat < 4294967296 at hu
  by_cases h : u.toNat < 2147483648
  · have hd : u.toNat / 2147483648 = 0 := Nat.div_eq_of_lt h
    norm_num [hd]
  · have hd : u.toNat / 2147483648 = 1 := by omega
    norm_num [hd]

theorem actual_widenBits_eq (u : UInt32) (h : Domain u) :
    Submission.R24PortableF64.widenBits u = widenBits u := by
  rcases h with hn | hz
  · have he : expWord u ≠ 0 := by
      intro hx
      have hnat := expWord_toNat u
      rw [hx] at hnat
      change 0 = wordExp u at hnat
      omega
    have he' : (u >>> 23) &&& 255 ≠ 0 := he
    simp only [Submission.R24PortableF64.widenBits, beq_iff_eq, he', ite_false]
    rw [actual_sign_eq]
    simp only [widenBits, he, ite_false, expWide, expWord, fracWord]
  · rcases zero_word_cases u hz.1 hz.2 with rfl | rfl <;> decide

theorem actual_native_model (u : UInt32) (h : Domain u) :
    native64 (Float.ofBits (Submission.R24PortableF64.widenBits u)) =
      raw64 (widenBits u) := by
  rw [actual_widenBits_eq u h]
  exact native_model u h

theorem actual_native_finite (u : UInt32) (h : Domain u) :
    (Float.ofBits (Submission.R24PortableF64.widenBits u)).isFinite = true := by
  rw [actual_widenBits_eq u h]
  exact native_finite u h

theorem actual_native_value (u : UInt32) (h : Domain u) :
    Model.toReal (ExecFloat.Binary.toModel (ExecFloat.Binary.ofFloat
      (Float.ofBits (Submission.R24PortableF64.widenBits u)))) =
      Model.toReal (Model.ofUInt32 (fmt := FloatFormat.binary32) u) := by
  rw [actual_widenBits_eq u h]
  exact Submission.R24RepresentationWiden.actual_native_value u h

theorem actual_signed_zero_bits :
    (Float.ofBits (Submission.R24PortableF64.widenBits 0)).toBits = 0 ∧
    (Float.ofBits (Submission.R24PortableF64.widenBits 0x80000000)).toBits =
      0x8000000000000000 := by decide

end Submission.R25ActualWiden
