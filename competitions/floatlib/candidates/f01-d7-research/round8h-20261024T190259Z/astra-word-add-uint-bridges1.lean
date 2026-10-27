/- Draft / NOT_RUN. Primitive machine-word lemmas for D's field composition.
   No dependency on or modification of R14WordAdd runtime definitions.
   Kept in an independent namespace so D can select only useful statements. -/
namespace Submission.R14AlignedWords

theorem shift_small (m d : UInt32) (hm : m.toNat < 16777216)
    (hd : d.toNat ≤ 7) : (m <<< d).toNat = m.toNat <<< d.toNat := by
  have hp : 2 ^ d.toNat ≤ 128 := by
    have h : 2 ^ d.toNat ≤ 2 ^ 7 := Nat.pow_le_pow_right (by decide) hd
    norm_num at h
    exact h
  have hb := Nat.mul_le_mul_left m.toNat hp
  have hshift : m.toNat <<< d.toNat < 4294967296 := by
    simp only [Nat.shiftLeft_eq', Nat.shiftLeft_eq]
    omega
  rw [UInt32.toNat_shiftLeft, Nat.mod_eq_of_lt (show d.toNat < 32 by omega)]
  exact Nat.mod_eq_of_lt hshift

theorem shift_bound (m d : UInt32) (hm : m.toNat < 16777216)
    (hd : d.toNat ≤ 7) : (m <<< d).toNat ≤ 2147483520 := by
  have hp : 2 ^ d.toNat ≤ 128 := by
    have h : 2 ^ d.toNat ≤ 2 ^ 7 := Nat.pow_le_pow_right (by decide) hd
    norm_num at h
    exact h
  have hb := Nat.mul_le_mul_left m.toNat hp
  rw [shift_small m d hm hd]
  simp only [Nat.shiftLeft_eq', Nat.shiftLeft_eq]
  omega

theorem add_aligned (hi lo d : UInt32)
    (hhi : hi.toNat < 16777216) (hlo : lo.toNat < 16777216)
    (hd : d.toNat ≤ 7) :
    ((hi <<< d) + lo).toNat = (hi.toNat <<< d.toNat) + lo.toNat := by
  have hb := shift_bound hi d hhi hd
  have hs := shift_small hi d hhi hd
  rw [UInt32.toNat_add, Nat.mod_eq_of_lt (by omega), hs]

theorem sub_aligned (hi lo d : UInt32)
    (hhi : hi.toNat < 16777216) (hd : d.toNat ≤ 7)
    (hle : lo.toNat ≤ hi.toNat <<< d.toNat) :
    ((hi <<< d) - lo).toNat = (hi.toNat <<< d.toNat) - lo.toNat := by
  have hs := shift_small hi d hhi hd
  have hleWord : lo ≤ hi <<< d := by
    rw [UInt32.le_iff_toNat_le, hs]
    exact hle
  rw [UInt32.toNat_sub_of_le _ _ hleWord, hs]

theorem leading_small (n base : UInt32) (hb : base.toNat ≤ 30)
    (hh : base.toNat + (n.toNat >>> (base.toNat + 1)) ≤ 31) :
    (base + (n >>> (base + 1))).toNat =
      base.toNat + (n.toNat >>> (base.toNat + 1)) := by
  have hs : (base + 1).toNat = base.toNat + 1 := by
    rw [UInt32.toNat_add, Nat.mod_eq_of_lt (by change base.toNat + 1 < 4294967296; omega)]
  have hr : (n >>> (base + 1)).toNat = n.toNat >>> (base.toNat + 1) := by
    rw [UInt32.toNat_shiftRight, hs, Nat.mod_eq_of_lt (by omega)]
  rw [UInt32.toNat_add, hr, Nat.mod_eq_of_lt (by omega)]

theorem shift_count (h : UInt32) (hh : 23 ≤ h.toNat) :
    (h - 23).toUInt64.toNat = h.toNat - 23 := by
  have hle : (23 : UInt32) ≤ h := by
    rw [UInt32.le_iff_toNat_le]
    exact hh
  simpa only [UInt32.toNat_toUInt64] using
    (UInt32.toNat_sub_of_le h 23 hle)

theorem carry_narrow (q : UInt64) (hq : q.toNat ≤ 16777216) :
    (q >>> 24).toUInt32.toNat = q.toNat >>> 24 := by
  have hs : (q >>> 24).toNat = q.toNat >>> 24 := by
    simpa only using (UInt64.toNat_shiftRight q 24)
  have hb : q.toNat >>> 24 < 4294967296 := by
    rw [Nat.shiftRight_eq_div_pow]
    change q.toNat / 16777216 < 4294967296
    omega
  rw [Submission.FastMul.toUInt32_eq, UInt32.toNat_ofNat', hs, Nat.mod_eq_of_lt hb]

theorem fraction_narrow (q : UInt64) (hq : q.toNat ≤ 16777216) :
    (q.toUInt32 &&& (0x007fffff : UInt32)).toNat = q.toNat % 8388608 := by
  rw [Submission.FastMul.toUInt32_eq, UInt32.toNat_and, UInt32.toNat_ofNat',
    Nat.mod_eq_of_lt (show q.toNat < 4294967296 by omega)]
  change q.toNat &&& (2 ^ 23 - 1) = q.toNat % 2 ^ 23
  exact Nat.and_two_pow_sub_one_eq_mod _ 23

end Submission.R14AlignedWords
