/- R22 raw-field connection, NOT_RUN. No new runtime and no native proof oracle. -/
namespace Submission.R22SameExponentGuard
open FloatLib.Floats.Formats.BinaryInterchange

theorem high_eq (u v : UInt32) (h : (u ^^^ v) < (0x00800000 : UInt32)) :
    u >>> 23 = v >>> 23 := by
  have hn : (u ^^^ v).toNat < 8388608 := UInt32.lt_iff_toNat_lt.mp h
  have hz : (u ^^^ v) >>> 23 = (0 : UInt32) := by
    apply UInt32.toNat_inj.mp
    rw [UInt32.toNat_shiftRight]
    change (u ^^^ v).toNat >>> 23 = 0
    rw [Nat.shiftRight_eq_div_pow]
    exact Nat.div_eq_of_lt hn
  rw [UInt32.shiftRight_xor] at hz
  exact UInt32.xor_eq_zero_iff.mp hz

theorem same_fields (u v : UInt32) (h : (u ^^^ v) < (0x00800000 : UInt32)) :
    R2W01c.wordSign u = R2W01c.wordSign v ∧
      R2W01c.wordExp u = R2W01c.wordExp v := by
  have he := congrArg UInt32.toNat (high_eq u v h)
  simp only [UInt32.toNat_shiftRight] at he
  change u.toNat >>> 23 = v.toNat >>> 23 at he
  rw [Nat.shiftRight_eq_div_pow] at he
  change u.toNat / 8388608 = v.toNat / 8388608 at he
  constructor
  · unfold R2W01c.wordSign
    congr 1
    omega
  · exact congrArg (fun n => n % 256) he

theorem exp_mask_eq (u : UInt32) :
    u &&& 0x7f800000 = Model.NativeBinary32.expField u <<< 23 := by
  apply UInt32.toBitVec_inj.mp
  apply BitVec.eq_of_getLsbD_eq
  intro i hi
  interval_cases i <;> simp [Model.NativeBinary32.expField]

theorem sign_mask_eq (u : UInt32) :
    u &&& 0x80000000 = ((R2W01b.tableIndex u &&& 256) <<< 23) := by
  apply UInt32.toBitVec_inj.mp
  apply BitVec.eq_of_getLsbD_eq
  intro i hi
  interval_cases i <;> simp [R2W01b.tableIndex]

theorem exp_nat (u : UInt32) :
    (Model.NativeBinary32.expField u).toNat = R2W01c.wordExp u := by
  exact FastMul.expField_toNat u

theorem exp_bound (u : UInt32) : R2W01c.wordExp u < 256 := by
  unfold R2W01c.wordExp
  omega

theorem exp_mask_nat (u : UInt32) :
    (u &&& 0x7f800000).toNat = R2W01c.wordExp u * 8388608 := by
  rw [exp_mask_eq, UInt32.toNat_shiftLeft, exp_nat]
  change (R2W01c.wordExp u <<< 23) % 4294967296 = _
  rw [Nat.shiftLeft_eq]
  have he := exp_bound u
  change (R2W01c.wordExp u * 8388608) % 4294967296 = _
  exact Nat.mod_eq_of_lt (by omega)

theorem sign_mask_nat (u : UInt32) :
    (u &&& 0x80000000).toNat = u.toNat / 2147483648 * 2147483648 := by
  rw [sign_mask_eq]
  exact R2W01c.tableSign_nat u

theorem frac_mask_nat (u : UInt32) :
    (u &&& 0x007fffff).toNat = R2W01c.wordFrac u := by
  rw [UInt32.toNat_and]
  change u.toNat &&& (2 ^ 23 - 1) = u.toNat % 2 ^ 23
  exact Nat.and_two_pow_sub_one_eq_mod u.toNat 23

theorem eligible_fields (u v : UInt32)
    (h : R22SameExponent.eligible u v = true) :
    R2W01c.wordSign u = R2W01c.wordSign v ∧
      R2W01c.wordExp u = R2W01c.wordExp v ∧ R2W01c.wordExp u < 255 := by
  have hh : (u ^^^ v) < (0x00800000 : UInt32) ∧
      (u &&& 0x7f800000) ≠ (0x7f800000 : UInt32) := by
    simpa only [R22SameExponent.eligible, Bool.and_eq_true,
      decide_eq_true_eq, bne_iff_ne] using h
  have hs := same_fields u v hh.1
  refine ⟨hs.1, hs.2, ?_⟩
  have hb := exp_bound u
  by_contra he
  have heq : R2W01c.wordExp u = 255 := by omega
  apply hh.2
  apply UInt32.toNat_inj.mp
  rw [exp_mask_nat, heq]
  rfl

end Submission.R22SameExponentGuard
