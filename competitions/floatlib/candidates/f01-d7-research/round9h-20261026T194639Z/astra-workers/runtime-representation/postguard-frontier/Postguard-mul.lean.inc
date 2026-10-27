/- Restricted revisit of the repository's R11 normal-band MUL front door.
   Material new parent condition: retained B2 already uses guarded table decoding
   in nativeMul; the R11 parent used two direct ofBits calls. ADD is unchanged.
   Range and arithmetic are the exact old E64..191 choice, not a threshold grid. -/
namespace R19PostguardMul
open R2W01b
open FloatLib.Floats.Formats.BinaryInterchange

@[inline] def pairOK (x y : UInt32) : Bool :=
  ((magnitude x - 0x20000000) ||| (magnitude y - 0x20000000)) <
    (0x40000000 : UInt32)

theorem normal_of_shift (u : UInt32)
    (h : (magnitude u - 0x20000000).toNat < 1073741824) : NormalBand u := by
  have hu := u.toNat_lt_size
  rw [UInt32.toNat_sub] at h
  simp only [NormalBand, UInt32.le_iff_toNat_le, UInt32.lt_iff_toNat_lt]
  change u.toNat < 4294967296 at hu
  change (3758096384 + (magnitude u).toNat) % 4294967296 < 1073741824 at h
  change 201326592 ≤ (magnitude u).toNat ∧ (magnitude u).toNat < 2139095040
  omega

theorem pairOK_normal (x y : UInt32) (h : pairOK x y = true) :
    NormalBand x ∧ NormalBand y := by
  unfold pairOK at h
  simp only [decide_eq_true_eq, UInt32.lt_iff_toNat_lt, UInt32.toNat_or] at h
  refine ⟨normal_of_shift x ?_, normal_of_shift y ?_⟩
  · exact Nat.lt_of_le_of_lt Nat.left_le_or h
  · exact Nat.lt_of_le_of_lt Nat.right_le_or h

theorem finite_of_fastOK (u : UInt32) (h : R2W01b.fastOK u = true) :
    Model.NativeBinary32.expField u ≠ 0xff := by
  have hm := R2W01b.magnitude_toNat u
  have he := FastMul.expField_toNat u
  have hu := u.toNat_lt_size
  have hb : (R2W01b.magnitude u).toNat < 2139095040 := by
    rcases (R2W01b.fastOK_iff u).mp h with hz | hn
    · rw [hz]; decide
    · have ht := hn.2
      rw [UInt32.lt_iff_toNat_lt] at ht
      exact ht
  intro hf
  have hf' := congrArg UInt32.toNat hf
  change (Model.NativeBinary32.expField u).toNat = 255 at hf'
  change u.toNat < 4294967296 at hu
  rw [he] at hf'
  norm_num at hf'
  omega

theorem finiteRoundtrip (x : Competition.Binary32)
    (hx : (ExecFloat.Binary.toFloat32 x).isFinite = true) :
    ExecFloat.Binary.ofFloat32 (ExecFloat.Binary.toFloat32 x) = x := by
  have hcanonical : Model.IsModelCanonical (ExecFloat.Binary.toModel x) := by
    apply GuardBridge.modelCanonicalOfFinite
    have hf := hx
    change ((Model.toFloat32Model (ExecFloat.Binary.toModel x)).unpack).isFinite = true at hf
    rw [Model.unpack_toFloat32Model] at hf
    exact hf
  apply Configured.Family.toModel_injective
  change ExecFloat.Binary.toModel
      (ExecFloat.Binary.ofFloat32 (ExecFloat.Binary.toFloat32 x)) =
    ExecFloat.Binary.toModel x
  rw [ExecFloat.Binary.toModel_ofFloat32, ExecFloat.Binary.toModel_toFloat32_eq,
    Model.ofFloat32Model_toFloat32Model]
  exact Model.canonicalizeModel_eq_self _ hcanonical

theorem table_eq_native (x : Binary32) (hx : NormalBand x.raw.1) :
    tableProduct x.raw.1 = ExecFloat.Binary.toFloat32 x := by
  rw [R2W01c.normal_eq x.raw.1 hx]
  rfl

theorem native_finite (x : Binary32) (hx : NormalBand x.raw.1) :
    (ExecFloat.Binary.toFloat32 x).isFinite = true := by
  exact WordFinite.nativeFiniteOfExp x
    (finite_of_fastOK x.raw.1 ((R2W01b.fastOK_iff x.raw.1).mpr (Or.inr hx)))

end R19PostguardMul

@[inline] def mul (x y : Binary32) : Binary32 :=
  if R19PostguardMul.pairOK x.raw.1 y.raw.1 then
    ExecFloat.Binary.ofFloat32 (R2W01b.tableProduct x.raw.1 * R2W01b.tableProduct y.raw.1)
  else mulBeforePostguard x y

theorem mul_spec (x y : Binary32) : mul x y = ExecFloat.Spec.mul x y := by
  unfold mul
  split
  · rename_i h
    have hh := R19PostguardMul.pairOK_normal x.raw.1 y.raw.1 h
    have hx := R19PostguardMul.native_finite x hh.1
    have hy := R19PostguardMul.native_finite y hh.2
    rw [R19PostguardMul.table_eq_native x hh.1, R19PostguardMul.table_eq_native y hh.2]
    rw [NativeBridge.ofFloat32Mul _ _ hx hy,
      R19PostguardMul.finiteRoundtrip x hx, R19PostguardMul.finiteRoundtrip y hy]
    exact ExecFloat.Proof.mul_eq_spec x y
  · exact mulBeforePostguard_spec x y

