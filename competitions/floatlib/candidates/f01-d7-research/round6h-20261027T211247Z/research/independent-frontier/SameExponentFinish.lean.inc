/- R22 complete raw/Binary32 composition draft. NOT_RUN. Runtime unchanged. -/
namespace Submission.R22SameExponentGuard
open FloatLib.Floats FloatLib.Numerics Competition
open FloatLib.Floats.Formats.BinaryInterchange

theorem raw_model_of_nat_fields (w u : UInt32) (e f : Nat)
    (he : e < 256) (hf : f < 8388608)
    (hw : w.toNat = u.toNat / 2147483648 * 2147483648 + e * 8388608 + f) :
    R2W01c.rawModel w = Model.ofFields FloatFormat.binary32 (R2W01c.wordSign u) e f := by
  have hu := u.toNat_lt_size
  change u.toNat < 4294967296 at hu
  have hs : R2W01c.wordSign w = R2W01c.wordSign u := by
    unfold R2W01c.wordSign
    rw [hw]
    congr 1
    omega
  have hex : R2W01c.wordExp w = e := by
    change w.toNat / 8388608 % 256 = _
    rw [hw]
    omega
  have hfr : R2W01c.wordFrac w = f := by
    change w.toNat % 8388608 = _
    rw [hw]
    omega
  rw [R2W01c.rawModel_eq_ofUInt32]
  change R2W01c.raw32 w = _
  rw [R2W01c.raw32_eq_fields, hs, hex, hfr]

theorem core_low_nat (u v : UInt32) (he : R2W01c.wordExp u = 0) :
    (R22SameExponent.core u v).toNat =
      u.toNat / 2147483648 * 2147483648 + R2W01c.wordFrac u + R2W01c.wordFrac v := by
  have hword : u &&& 0x7f800000 = (0 : UInt32) := by
    apply UInt32.toNat_inj.mp
    rw [exp_mask_nat, he]
    rfl
  have hlo : R2W01c.wordFrac u + R2W01c.wordFrac v < 2 ^ 31 := by
    have hf := R2W01c.wordFrac_lt u
    have hg := R2W01c.wordFrac_lt v
    norm_num
    omega
  simp only [R22SameExponent.core, hword, beq_self_eq_true, ↓reduceIte]
  rw [UInt32.toNat_or, sign_mask_nat, frac_sum_nat]
  have hor := (Nat.two_pow_add_eq_or_of_lt hlo (u.toNat / 2147483648)).symm
  norm_num at hor
  rw [Nat.mul_comm (u.toNat / 2147483648) 2147483648, hor]
  omega

theorem core_low_model (u v : UInt32) (he : R2W01c.wordExp u = 0) :
    R2W01c.rawModel (R22SameExponent.core u v) =
      Model.ofFields FloatFormat.binary32 (R2W01c.wordSign u)
        ((R2W01c.wordFrac u + R2W01c.wordFrac v) / 8388608)
        ((R2W01c.wordFrac u + R2W01c.wordFrac v) % 8388608) := by
  have hf := R2W01c.wordFrac_lt u
  have hg := R2W01c.wordFrac_lt v
  have hc := core_low_nat u v he
  apply raw_model_of_nat_fields _ u _ _ (by omega) (by omega)
  omega

theorem core_overflow_nat (u v : UInt32) (he : R2W01c.wordExp u = 254) :
    (R22SameExponent.core u v).toNat =
      u.toNat / 2147483648 * 2147483648 + 2139095040 := by
  have hword : u &&& 0x7f800000 = (0x7f000000 : UInt32) := by
    apply UInt32.toNat_inj.mp
    rw [exp_mask_nat, he]
    rfl
  have hlo : 2139095040 < 2 ^ 31 := by decide
  simp only [R22SameExponent.core, hword]
  norm_num
  rw [UInt32.toNat_or, sign_mask_nat]
  change (u.toNat / 2147483648 * 2147483648) ||| 2139095040 = _
  rw [Nat.mul_comm (u.toNat / 2147483648) 2147483648]
  exact (Nat.two_pow_add_eq_or_of_lt hlo (u.toNat / 2147483648)).symm

theorem core_overflow_model (u v : UInt32) (he : R2W01c.wordExp u = 254) :
    R2W01c.rawModel (R22SameExponent.core u v) =
      Model.ofFields FloatFormat.binary32 (R2W01c.wordSign u) 255 0 := by
  apply raw_model_of_nat_fields _ u 255 0 (by decide) (by decide)
  simpa using core_overflow_nat u v he

theorem all_raw_add (u v : UInt32) (h : R22SameExponent.eligible u v = true) :
    R2W01c.rawModel (R22SameExponent.core u v) =
      Model.Spec.add (R2W01c.rawModel u) (R2W01c.rawModel v) := by
  have hs := eligible_fields u v h
  have hfu : R2W01c.rawModel u = Model.ofFields FloatFormat.binary32
      (R2W01c.wordSign u) (R2W01c.wordExp u) (R2W01c.wordFrac u) := by
    rw [R2W01c.rawModel_eq_ofUInt32]
    exact R2W01c.raw32_eq_fields u
  have hfv : R2W01c.rawModel v = Model.ofFields FloatFormat.binary32
      (R2W01c.wordSign u) (R2W01c.wordExp u) (R2W01c.wordFrac v) := by
    rw [R2W01c.rawModel_eq_ofUInt32]
    change R2W01c.raw32 v = _
    rw [R2W01c.raw32_eq_fields, ← hs.1, ← hs.2.1]
  by_cases he0 : R2W01c.wordExp u = 0
  · rw [core_low_model u v he0, hfu, hfv, he0]
    exact (R22SameExponentMath.subnormal_fields_add (R2W01c.wordSign u)
      (R2W01c.wordFrac u) (R2W01c.wordFrac v)
      (R2W01c.wordFrac_lt u) (R2W01c.wordFrac_lt v)).symm
  by_cases he254 : R2W01c.wordExp u = 254
  · rw [core_overflow_model u v he254, hfu, hfv, he254]
    exact (R22SameExponentMath.overflow_fields_add (R2W01c.wordSign u)
      (R2W01c.wordFrac u) (R2W01c.wordFrac v)
      (R2W01c.wordFrac_lt u) (R2W01c.wordFrac_lt v)).symm
  · exact normal_raw_add u v h (by omega) (by omega)

theorem core_spec (x y : Binary32) (h : R22SameExponent.eligible x.raw.1 y.raw.1 = true) :
    FastMul.ofBits (R22SameExponent.core x.raw.1 y.raw.1) = ExecFloat.Spec.add x y := by
  rw [← ExecFloat.Proof.add_eq_spec]
  apply Configured.Family.toModel_injective
  change Model.NativeBinary32.ofUInt32 (R22SameExponent.core x.raw.1 y.raw.1) =
    ExecFloat.Binary.toModel (ExecFloat.add x y)
  rw [R7Native.toModelExecAdd, R7W02.exec_toModel_eq_rawModel,
    R7W02.exec_toModel_eq_rawModel]
  simpa only [R2W01c.rawModel_eq_native32] using all_raw_add x.raw.1 y.raw.1 h

theorem diagnosticEntry_spec (x y : Binary32) :
    R22SameExponent.diagnosticEntry x y = ExecFloat.Spec.add x y := by
  unfold R22SameExponent.diagnosticEntry
  split
  · rename_i h
    exact core_spec x y h
  · exact Submission.add_spec x y

end Submission.R22SameExponentGuard
