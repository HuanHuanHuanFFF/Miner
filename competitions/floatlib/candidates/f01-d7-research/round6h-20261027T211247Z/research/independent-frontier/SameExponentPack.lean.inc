/- R22 word/normal-Model transport, NOT_RUN. No runtime edits. -/
namespace Submission.R22SameExponentGuard
open FloatLib.Floats FloatLib.Numerics
open FloatLib.Floats.Formats.BinaryInterchange

theorem frac_sum_nat (u v : UInt32) :
    ((u &&& 0x007fffff) + (v &&& 0x007fffff)).toNat =
      R2W01c.wordFrac u + R2W01c.wordFrac v := by
  rw [UInt32.toNat_add, frac_mask_nat, frac_mask_nat]
  have hu := R2W01c.wordFrac_lt u
  have hv := R2W01c.wordFrac_lt v
  exact Nat.mod_eq_of_lt (by change _ < 4294967296; omega)

theorem half_word_nat (t : UInt32) (ht : t.toNat ≤ 16777214) :
    ((t + ((t >>> 1) &&& 1)) >>> 1).toNat =
      (t.toNat + (t.toNat / 2) % 2) / 2 := by
  have hbit : ((t >>> 1) &&& (1 : UInt32)).toNat = (t.toNat / 2) % 2 := by
    rw [UInt32.toNat_and, UInt32.toNat_shiftRight]
    change (t.toNat >>> 1) &&& (2 ^ 1 - 1) = (t.toNat / 2) % 2
    rw [Nat.and_two_pow_sub_one_eq_mod, Nat.shiftRight_eq_div_pow]
    rfl
  rw [UInt32.toNat_shiftRight, UInt32.toNat_add, hbit]
  change ((t.toNat + (t.toNat / 2) % 2) % 4294967296) >>> 1 = _
  rw [Nat.mod_eq_of_lt (by omega), Nat.shiftRight_eq_div_pow]

theorem core_normal_nat (u v : UInt32)
    (he0 : 1 ≤ R2W01c.wordExp u) (he : R2W01c.wordExp u ≤ 253) :
    (R22SameExponent.core u v).toNat =
      u.toNat / 2147483648 * 2147483648 +
      (R2W01c.wordExp u + 1) * 8388608 +
      ((R2W01c.wordFrac u + R2W01c.wordFrac v +
        ((R2W01c.wordFrac u + R2W01c.wordFrac v) / 2) % 2) / 2) := by
  let t := (u &&& 0x007fffff) + (v &&& 0x007fffff)
  let r := (t + ((t >>> 1) &&& 1)) >>> 1
  have ht : t.toNat = R2W01c.wordFrac u + R2W01c.wordFrac v := frac_sum_nat u v
  have hf := R2W01c.wordFrac_lt u
  have hg := R2W01c.wordFrac_lt v
  have htmax : t.toNat ≤ 16777214 := by omega
  have hr : r.toNat = (t.toNat + (t.toNat / 2) % 2) / 2 := half_word_nat t htmax
  have hrmax : r.toNat < 8388608 := by rw [hr]; exact R22SameExponentMath.half_bound _ htmax
  have h0 : (u &&& 0x7f800000) ≠ (0 : UInt32) := by
    intro h
    have hh := congrArg UInt32.toNat h
    rw [exp_mask_nat] at hh
    change R2W01c.wordExp u * 8388608 = 0 at hh
    omega
  have h254 : (u &&& 0x7f800000) ≠ (0x7f000000 : UInt32) := by
    intro h
    have hh := congrArg UInt32.toNat h
    rw [exp_mask_nat] at hh
    change R2W01c.wordExp u * 8388608 = 2130706432 at hh
    omega
  have hp : ((u &&& 0x7f800000) + 0x00800000 + r).toNat =
      (R2W01c.wordExp u + 1) * 8388608 + r.toNat := by
    rw [UInt32.toNat_add, UInt32.toNat_add, exp_mask_nat]
    change (((R2W01c.wordExp u * 8388608 + 8388608) % 4294967296) +
      r.toNat) % 4294967296 = _
    omega
  have hlow : (R2W01c.wordExp u + 1) * 8388608 + r.toNat < 2 ^ 31 := by
    norm_num
    omega
  have hc : R22SameExponent.core u v =
      (u &&& 0x80000000) ||| ((u &&& 0x7f800000) + 0x00800000 + r) := by
    simpa only [R22SameExponent.core, beq_iff_eq, h0, h254, ↓reduceIte]
  rw [hc, UInt32.toNat_or, sign_mask_nat, hp]
  have hor := (Nat.two_pow_add_eq_or_of_lt hlow (u.toNat / 2147483648)).symm
  norm_num at hor
  rw [Nat.mul_comm (u.toNat / 2147483648) 2147483648]
  rw [hor, hr, ht]
  omega

theorem core_normal_model (u v : UInt32)
    (he0 : 1 ≤ R2W01c.wordExp u) (he : R2W01c.wordExp u ≤ 253) :
    R2W01c.rawModel (R22SameExponent.core u v) =
      Model.ofFields FloatFormat.binary32 (R2W01c.wordSign u)
        (R2W01c.wordExp u + 1)
        ((R2W01c.wordFrac u + R2W01c.wordFrac v +
          ((R2W01c.wordFrac u + R2W01c.wordFrac v) / 2) % 2) / 2) := by
  have hc := core_normal_nat u v he0 he
  have hu := u.toNat_lt_size
  change u.toNat < 4294967296 at hu
  have hf := R2W01c.wordFrac_lt u
  have hg := R2W01c.wordFrac_lt v
  have hq := R22SameExponentMath.half_bound
    (R2W01c.wordFrac u + R2W01c.wordFrac v) (by omega)
  have hs : R2W01c.wordSign (R22SameExponent.core u v) = R2W01c.wordSign u := by
    unfold R2W01c.wordSign
    rw [hc]
    congr 1
    omega
  have heq : R2W01c.wordExp (R22SameExponent.core u v) = R2W01c.wordExp u + 1 := by
    change (R22SameExponent.core u v).toNat / 8388608 % 256 = _
    rw [hc]
    omega
  have hfq : R2W01c.wordFrac (R22SameExponent.core u v) =
      (R2W01c.wordFrac u + R2W01c.wordFrac v +
        ((R2W01c.wordFrac u + R2W01c.wordFrac v) / 2) % 2) / 2 := by
    change (R22SameExponent.core u v).toNat % 8388608 = _
    rw [hc]
    omega
  rw [R2W01c.rawModel_eq_ofUInt32]
  change R2W01c.raw32 (R22SameExponent.core u v) = _
  rw [R2W01c.raw32_eq_fields, hs, heq, hfq]

theorem normal_raw_add (u v : UInt32)
    (h : R22SameExponent.eligible u v = true)
    (he0 : 1 ≤ R2W01c.wordExp u) (he : R2W01c.wordExp u ≤ 253) :
    R2W01c.rawModel (R22SameExponent.core u v) =
      Model.Spec.add (R2W01c.rawModel u) (R2W01c.rawModel v) := by
  have hs := eligible_fields u v h
  rw [core_normal_model u v he0 he,
    R2W01c.rawModel_eq_ofUInt32 u, R2W01c.rawModel_eq_ofUInt32 v]
  change _ = Model.Spec.add (R2W01c.raw32 u) (R2W01c.raw32 v)
  rw [R2W01c.raw32_eq_fields u, R2W01c.raw32_eq_fields v, ← hs.1, ← hs.2.1]
  exact (R22SameExponentMath.normal_fields_add (R2W01c.wordSign u)
    (R2W01c.wordExp u) (R2W01c.wordFrac u) (R2W01c.wordFrac v)
    he0 he (R2W01c.wordFrac_lt u) (R2W01c.wordFrac_lt v)).symm

end Submission.R22SameExponentGuard
