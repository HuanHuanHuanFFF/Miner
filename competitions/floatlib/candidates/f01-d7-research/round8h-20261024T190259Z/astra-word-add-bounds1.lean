/- Draft / NOT_RUN. Requires astra-word-add-alignment1.lean only.
   Nat bounds certify the UInt32 arithmetic and the complete, unmasked exponent.
   In particular, accepting a packed exponent is justified only after E<=256. -/
namespace Submission.R14WordAddAlignment

open FloatLib.Numerics

def leadingBase (hiSign loSign : Bool) (gap : Nat) : Nat :=
  (if hiSign = loSign then 23 else 22) + gap

theorem magnitude_bounds (hiSign loSign : Bool) (hi lo gap : Nat)
    (hhi : 8388608 ≤ hi) (hhiUpper : hi < 16777216)
    (hlo : 8388608 ≤ lo) (hloUpper : lo < 16777216)
    (hgap : gap ≤ 7) (hdomain : hiSign = loSign ∨ 2 ≤ gap) :
    16777216 ≤ magnitude hiSign loSign hi lo gap ∧
    magnitude hiSign loSign hi lo gap ≤ 2164260735 ∧
    2 ^ leadingBase hiSign loSign gap ≤ magnitude hiSign loSign hi lo gap ∧
    magnitude hiSign loSign hi lo gap < 2 ^ (leadingBase hiSign loSign gap + 2) ∧
    magnitude hiSign loSign hi lo gap < 2 ^ (gap + 25) := by
  by_cases hs : hiSign = loSign
  · interval_cases gap <;>
      simp only [magnitude, leadingBase, if_pos hs, Nat.shiftLeft_eq',
        Nat.shiftLeft_eq] <;> norm_num <;> omega
  · have hd : 2 ≤ gap := hdomain.resolve_left hs
    interval_cases gap <;>
      simp only [magnitude, leadingBase, if_neg hs, Nat.shiftLeft_eq',
        Nat.shiftLeft_eq] <;> norm_num <;> omega

theorem two_bit_log2 (n base : Nat) (hbase0 : 22 ≤ base) (hbase1 : base ≤ 30)
    (hlo : 2 ^ base ≤ n) (hhi : n < 2 ^ (base + 2)) :
    n.log2 = base + (n >>> (base + 1)) := by
  have hn : n ≠ 0 := by have hp := Nat.two_pow_pos base; omega
  by_cases hcut : n < 2 ^ (base + 1)
  · have hq : n >>> (base + 1) = 0 := by
      rw [Nat.shiftRight_eq_div_pow]
      exact Nat.div_eq_of_lt hcut
    rw [hq, Nat.add_zero]
    exact (Nat.log2_eq_iff hn).2 ⟨hlo, hcut⟩
  · have hq : n >>> (base + 1) = 1 := by
      interval_cases base <;>
        norm_num [Nat.shiftRight_eq_div_pow] at * <;> omega
    rw [hq]
    apply (Nat.log2_eq_iff hn).2
    constructor
    · omega
    · simpa only [Nat.add_assoc] using hhi

theorem exact_log2 (hiSign loSign : Bool) (hi lo gap : Nat)
    (hhi : 8388608 ≤ hi) (hhiUpper : hi < 16777216)
    (hlo : 8388608 ≤ lo) (hloUpper : lo < 16777216)
    (hgap : gap ≤ 7) (hdomain : hiSign = loSign ∨ 2 ≤ gap) :
    (magnitude hiSign loSign hi lo gap).log2 = leadingBase hiSign loSign gap +
      (magnitude hiSign loSign hi lo gap >>> (leadingBase hiSign loSign gap + 1)) := by
  have hb := magnitude_bounds hiSign loSign hi lo gap hhi hhiUpper hlo hloUpper hgap hdomain
  have hbase : 22 ≤ leadingBase hiSign loSign gap ∧
      leadingBase hiSign loSign gap ≤ 30 := by
    unfold leadingBase
    split <;> omega
  exact two_bit_log2 _ _ hbase.1 hbase.2 hb.2.2.1 hb.2.2.2.1

theorem log2_bounds (hiSign loSign : Bool) (hi lo gap : Nat)
    (hhi : 8388608 ≤ hi) (hhiUpper : hi < 16777216)
    (hlo : 8388608 ≤ lo) (hloUpper : lo < 16777216)
    (hgap : gap ≤ 7) (hdomain : hiSign = loSign ∨ 2 ≤ gap) :
    24 ≤ (magnitude hiSign loSign hi lo gap).log2 ∧
    (magnitude hiSign loSign hi lo gap).log2 ≤ 31 ∧
    (magnitude hiSign loSign hi lo gap).log2 ≤ gap + 24 := by
  have hb := magnitude_bounds hiSign loSign hi lo gap hhi hhiUpper hlo hloUpper hgap hdomain
  have hn : magnitude hiSign loSign hi lo gap ≠ 0 := by omega
  have hl : 24 ≤ (magnitude hiSign loSign hi lo gap).log2 :=
    (Nat.le_log2 hn).2 (by norm_num; exact hb.1)
  have hu : (magnitude hiSign loSign hi lo gap).log2 < 32 :=
    (Nat.log2_lt hn).2 (by norm_num; omega)
  have hd : (magnitude hiSign loSign hi lo gap).log2 < gap + 25 :=
    (Nat.log2_lt hn).2 hb.2.2.2.2
  omega

theorem unpacked_exponent_bounds (h elo ehi carry : Nat)
    (hh : 24 ≤ h) (hhgap : h ≤ ehi - elo + 24)
    (helo : 1 ≤ elo) (hehi : ehi ≤ 254) (horder : elo ≤ ehi)
    (hc : carry ≤ 1) :
    2 ≤ h + elo - 23 + carry ∧ h + elo - 23 + carry ≤ 256 := by
  omega

theorem packed_exponent_accept_iff (e : Nat) (he : 2 ≤ e) (he256 : e ≤ 256) :
    (1 ≤ e % 256 ∧ e % 256 ≤ 254) ↔ e ≤ 254 := by
  omega

theorem word_exponent_accept_iff (e : UInt32) (he : 2 ≤ e.toNat) :
    (e - 1 ≤ (253 : UInt32)) ↔ e.toNat ≤ 254 := by
  have he1 : (1 : UInt32) ≤ e := by
    rw [UInt32.le_iff_toNat_le]
    change 1 ≤ e.toNat
    omega
  rw [UInt32.le_iff_toNat_le, UInt32.toNat_sub_of_le _ _ he1]
  change e.toNat - 1 ≤ 253 ↔ e.toNat ≤ 254
  omega

end Submission.R14WordAddAlignment
