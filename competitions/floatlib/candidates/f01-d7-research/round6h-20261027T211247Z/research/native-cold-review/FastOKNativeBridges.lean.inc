/- Proof-only interface after exact B2. NOT_RUN; no runtime/public source changes. -/
namespace Submission.R22NativeColdReview
open FloatLib.Floats Competition

theorem fastOK_notNaN (x : Binary32) (hx : R2W01b.fastOK x.raw.1 = true) :
    (ExecFloat.Binary.toFloat32 x).isNaN = false := by
  have hle : R2W01b.magnitude x.raw.1 <= (0x7f800000 : UInt32) := by
    rcases (R2W01b.fastOK_iff x.raw.1).mp hx with hz | hn
    · rw [hz]; decide
    · exact UInt32.le_of_lt hn.2
  have hr : R7W12.rawNotNaN x.raw.1 = true := decide_eq_true hle
  apply Bool.not_inj
  exact (R7W12.rawNotNaN_eq_native_classifier x).symm.trans hr

theorem native_add_spec_of_fastOK (x y : Binary32)
    (hx : R2W01b.fastOK x.raw.1 = true) (hy : R2W01b.fastOK y.raw.1 = true) :
    ExecFloat.Binary.ofFloat32 (R2W01b.tableProduct x.raw.1 + R2W01b.tableProduct y.raw.1) =
      ExecFloat.Spec.add x y := by
  rw [R2W01b.tableProduct_of_fastOK R2W01c.normal_eq _ hx,
    R2W01b.tableProduct_of_fastOK R2W01c.normal_eq _ hy]
  have hnx := fastOK_notNaN x hx
  have hny := fastOK_notNaN y hy
  change ExecFloat.Binary.ofFloat32
    (ExecFloat.Binary.toFloat32 x + ExecFloat.Binary.toFloat32 y) = _
  rw [R7Native.ofFloat32Add _ _ hnx hny,
    NotNaNProbe.roundtrip x hnx, NotNaNProbe.roundtrip y hny]
  exact ExecFloat.Proof.add_eq_spec x y

theorem native_mul_spec_of_fastOK (x y : Binary32)
    (hx : R2W01b.fastOK x.raw.1 = true) (hy : R2W01b.fastOK y.raw.1 = true) :
    ExecFloat.Binary.ofFloat32 (R2W01b.tableProduct x.raw.1 * R2W01b.tableProduct y.raw.1) =
      ExecFloat.Spec.mul x y := by
  rw [R2W01b.tableProduct_of_fastOK R2W01c.normal_eq _ hx,
    R2W01b.tableProduct_of_fastOK R2W01c.normal_eq _ hy]
  have hnx := fastOK_notNaN x hx
  have hny := fastOK_notNaN y hy
  change ExecFloat.Binary.ofFloat32
    (ExecFloat.Binary.toFloat32 x * ExecFloat.Binary.toFloat32 y) = _
  rw [R7Native.ofFloat32Mul _ _ hnx hny,
    NotNaNProbe.roundtrip x hnx, NotNaNProbe.roundtrip y hny]
  exact ExecFloat.Proof.mul_eq_spec x y

end Submission.R22NativeColdReview
