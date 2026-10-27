
/- Draft dependencies: native-product1, nat-normal-form-draft,
general-scale-fusion-draft and table-factor-draft. Public mul is not rewired here. -/
namespace Submission.R14IntegerTable

open FloatLib.Floats Competition
open FloatLib.Floats.Formats.BinaryInterchange

def core (u v : UInt32) : Float32 :=
  ((R2W01b.mantissa u).toFloat32 * (R2W01b.mantissa v).toFloat32) *
    R2W01b.scaleAt (Model.NativeBinary32.mkBits
      (Bool.xor (R2W01c.wordSign u) (R2W01c.wordSign v))
      (R2W01c.wordExp u + R2W01c.wordExp v - 150) 0)

theorem core_model (u v : UInt32)
    (hu0 : 0 < R2W01c.wordExp u) (hu : R2W01c.wordExp u < 255)
    (hv0 : 0 < R2W01c.wordExp v) (hv : R2W01c.wordExp v < 255)
    (hs : 174 ≤ R2W01c.wordExp u + R2W01c.wordExp v)
    (hs' : R2W01c.wordExp u + R2W01c.wordExp v ≤ 380) :
    R2W01c.nativeModel (core u v) =
      Model.mul (R2W01c.rawModel u) (R2W01c.rawModel v) := by
  have hx := R14NatNormal.raw_normal_decode u hu0 hu
  have hy := R14NatNormal.raw_normal_decode v hv0 hv
  have hmu := R2W01c.mantissa_bounds u
  have hmv := R2W01c.mantissa_bounds v
  have hm := R14NativeProduct.model_mul_of_nonzero_decodes
    (R2W01c.rawModel u) (R2W01c.rawModel v)
    ⟨R2W01c.wordSign u, (R2W01b.mantissa u).toNat, (R2W01c.wordExp u : Int) - 150⟩
    ⟨R2W01c.wordSign v, (R2W01b.mantissa v).toNat, (R2W01c.wordExp v : Int) - 150⟩
    hx hy (by omega) (by omega)
  have he : (R2W01c.wordExp u : Int) - 150 +
      ((R2W01c.wordExp v : Int) - 150) =
      ((R2W01c.wordExp u + R2W01c.wordExp v : Nat) : Int) - 300 := by omega
  rw [he] at hm
  have hfused := R14TableFactor.integer_table_fusion (R2W01b.mantissa u) (R2W01b.mantissa v)
    (R2W01c.wordExp u + R2W01c.wordExp v)
    (Bool.xor (R2W01c.wordSign u) (R2W01c.wordSign v))
    hmu.1 hmu.2 hmv.1 hmv.2 hs hs'
  exact hfused.trans hm.symm

theorem core_spec (x y : Binary32)
    (hx0 : 0 < R2W01c.wordExp x.raw.1) (hx : R2W01c.wordExp x.raw.1 < 255)
    (hy0 : 0 < R2W01c.wordExp y.raw.1) (hy : R2W01c.wordExp y.raw.1 < 255)
    (hs : 174 ≤ R2W01c.wordExp x.raw.1 + R2W01c.wordExp y.raw.1)
    (hs' : R2W01c.wordExp x.raw.1 + R2W01c.wordExp y.raw.1 ≤ 380) :
    ExecFloat.Binary.ofFloat32 (core x.raw.1 y.raw.1) = ExecFloat.Spec.mul x y := by
  apply Configured.Family.toModel_injective
  change ExecFloat.Binary.toModel (ExecFloat.Binary.ofFloat32 (core x.raw.1 y.raw.1)) =
    ExecFloat.Binary.toModel (ExecFloat.Spec.mul x y)
  rw [ExecFloat.Binary.toModel_ofFloat32, ← ExecFloat.Proof.mul_eq_spec,
    R7W01.exec_toModel_mul, ← Model.Proof.mul_eq_spec,
    R7W02.exec_toModel_eq_rawModel x, R7W02.exec_toModel_eq_rawModel y,
    ← R2W01c.rawModel_eq_native32 x.raw.1, ← R2W01c.rawModel_eq_native32 y.raw.1]
  exact core_model x.raw.1 y.raw.1 hx0 hx hy0 hy hs hs'

def valid (u v : UInt32) : Prop :=
  0 < R2W01c.wordExp u ∧ R2W01c.wordExp u < 255 ∧
  0 < R2W01c.wordExp v ∧ R2W01c.wordExp v < 255 ∧
  174 ≤ R2W01c.wordExp u + R2W01c.wordExp v ∧
  R2W01c.wordExp u + R2W01c.wordExp v ≤ 380

instance (u v : UInt32) : Decidable (valid u v) := by
  unfold valid
  infer_instance

def guardedMul (fallback : Binary32 → Binary32 → Binary32) (x y : Binary32) : Binary32 :=
  if valid x.raw.1 y.raw.1 then ExecFloat.Binary.ofFloat32 (core x.raw.1 y.raw.1)
  else fallback x y

theorem guardedMul_spec (fallback : Binary32 → Binary32 → Binary32)
    (hf : ∀ x y, fallback x y = ExecFloat.Spec.mul x y) (x y : Binary32) :
    guardedMul fallback x y = ExecFloat.Spec.mul x y := by
  unfold guardedMul
  split
  · rename_i h
    rcases h with ⟨hx0, hx, hy0, hy, hs, hs'⟩
    exact core_spec x y hx0 hx hy0 hy hs hs'
  · exact hf x y

end Submission.R14IntegerTable
