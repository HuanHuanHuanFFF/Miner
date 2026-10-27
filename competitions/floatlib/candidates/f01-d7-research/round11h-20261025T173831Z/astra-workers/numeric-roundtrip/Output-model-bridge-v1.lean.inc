/- R17 output reconstruction bridge. Fixed-environment elaboration is pending. -/
namespace Submission.R17NumericOutput

open FloatLib.Floats Competition
open FloatLib.Floats.Formats.BinaryInterchange

theorem pack_of_masked_fraction (sign : Bool) (e fraction : UInt32) (F : Nat)
    (hF : F < 8388608) (hf : (fraction &&& (0x7fffff : UInt32)).toNat = F) :
    FastMul.mkW sign e fraction = Model.NativeBinary32.mkBits sign e.toNat F := by
  have hF32 : F < UInt32.size := by change F < 4294967296; omega
  have hmask : fraction &&& (0x7fffff : UInt32) = UInt32.ofNat F := by
    apply UInt32.toNat_inj.mp
    rw [hf, UInt32.toNat_ofNat_of_lt' hF32]
  have hself : (UInt32.ofNat F) &&& (0x7fffff : UInt32) = UInt32.ofNat F := by
    apply UInt32.toNat_inj.mp
    simp only [UInt32.toNat_and, UInt32.toNat_ofNat_of_lt' hF32]
    change F &&& (2 ^ 23 - 1) = F
    rw [Nat.and_two_pow_sub_one_eq_mod]
    exact Nat.mod_eq_of_lt hF
  calc
    FastMul.mkW sign e fraction = FastMul.mkW sign e (UInt32.ofNat F) := by
      unfold FastMul.mkW
      rw [hmask, hself]
    _ = _ := by
      simpa only [UInt32.ofNat_toNat] using (FastMul.mkW_ofNat sign e.toNat F)

theorem word_exponent_shift_relation (ehi elo gap adjust bump : UInt32)
    (hhi : ehi.toNat ≤ 254) (hg : gap.toNat ≤ 7)
    (hgap : ehi.toNat = elo.toNat + gap.toNat)
    (hadj : adjust.toNat ≤ gap.toNat) (hbump : bump.toNat ≤ 1) :
    ((ehi - adjust) + bump).toNat = elo.toNat + ((gap - adjust) + bump).toNat := by
  have hadg : adjust ≤ gap := UInt32.le_iff_toNat_le.mpr hadj
  have hade : adjust ≤ ehi := UInt32.le_iff_toNat_le.mpr (by omega)
  have hefit : ehi.toNat - adjust.toNat + bump.toNat < UInt32.size := by
    change _ < 4294967296
    omega
  have hgfit : gap.toNat - adjust.toNat + bump.toNat < UInt32.size := by
    change _ < 4294967296
    omega
  rw [UInt32.toNat_add, UInt32.toNat_sub_of_le _ _ hade, Nat.mod_eq_of_lt hefit,
    UInt32.toNat_add, UInt32.toNat_sub_of_le _ _ hadg, Nat.mod_eq_of_lt hgfit]
  omega

theorem numeric_pack_model (n shift e : UInt32) (sign : Bool) (elo : Nat)
    (hlo : 8388608 ≤ n.toNat) (hhi : n.toNat ≤ 2164260735)
    (hs : shift.toNat = R16UInt32Roundtrip.roundedShift n.toNat)
    (he : e.toNat = elo + shift.toNat) (helo : 1 ≤ elo) (hehi : e.toNat < 255) :
    Model.NativeBinary32.ofUInt32
        (FastMul.mkW sign e (n.toFloat32.toUInt32 >>> shift)) =
      Model.roundDyadic FloatFormat.binary32
        (⟨sign, n.toNat, (elo : Int) - 150⟩ : FloatLib.Numerics.Dyadic) := by
  have hm := R16UInt32Roundtrip.high_mantissa n.toNat hlo hhi
  have hF : R14NatNormal.mantissa n.toNat - 8388608 < 8388608 := by omega
  have hf := R17NumericNormalize.numeric_fraction_toNat n shift hlo hhi hs
  have hn : n.toNat ≠ 0 := by omega
  have hl := (R16UInt32Roundtrip.high_log n.toNat hlo hhi).1
  have hshift : shift.toNat = n.toNat.log2 + R14NatNormal.carry n.toNat - 23 := hs
  have hmin : -126 ≤ (n.toNat.log2 : Int) + ((elo : Int) - 150) := by omega
  have hmax : (n.toNat.log2 : Int) + ((elo : Int) - 150) +
      (R14NatNormal.carry n.toNat : Int) ≤ 127 := by omega
  have hexp : Int.toNat ((n.toNat.log2 : Int) + ((elo : Int) - 150) +
      (R14NatNormal.carry n.toNat : Int) + 127) = e.toNat := by omega
  rw [pack_of_masked_fraction sign e _ _ hF hf, Model.NativeBinary32.ofUInt32_mkBits,
    R14NatNormal.model_round_normal sign n.toNat ((elo : Int) - 150) hn hl hmin hmax,
    hexp]

theorem numeric_add_of_alignment (x y : Binary32) (n shift e : UInt32)
    (sign : Bool) (elo : Nat)
    (hlo : 8388608 ≤ n.toNat) (hhi : n.toNat ≤ 2164260735)
    (hs : shift.toNat = R16UInt32Roundtrip.roundedShift n.toNat)
    (he : e.toNat = elo + shift.toNat) (helo : 1 ≤ elo) (hehi : e.toNat < 255)
    (halign : Model.add (R2W01c.rawModel x.raw.1) (R2W01c.rawModel y.raw.1) =
      Model.roundDyadic FloatFormat.binary32
        (⟨sign, n.toNat, (elo : Int) - 150⟩ : FloatLib.Numerics.Dyadic)) :
    R7W02.fromRaw (FastMul.mkW sign e (n.toFloat32.toUInt32 >>> shift)) =
      ExecFloat.Spec.add x y := by
  apply Configured.Family.toModel_injective
  change ExecFloat.Binary.toModel
      (R7W02.fromRaw (FastMul.mkW sign e (n.toFloat32.toUInt32 >>> shift))) =
    ExecFloat.Binary.toModel (ExecFloat.Spec.add x y)
  rw [R7W02.fromRaw_toModel, ← ExecFloat.Proof.add_eq_spec x y,
    R7Native.toModelExecAdd, ← Model.Proof.add_eq_spec,
    R7W02.exec_toModel_eq_rawModel x, R7W02.exec_toModel_eq_rawModel y,
    ← R2W01c.rawModel_eq_native32 x.raw.1, ← R2W01c.rawModel_eq_native32 y.raw.1,
    halign]
  exact numeric_pack_model n shift e sign elo hlo hhi hs he helo hehi

end Submission.R17NumericOutput
