/- Thin exact-dyadic corollary; requires both portable source fragments.
   No finite-result assumption excludes the maximum-finite upper cell. -/
namespace Submission.R24DyadicCell
open FloatLib.Numerics
open FloatLib.Floats FloatLib.Floats.Formats.BinaryInterchange

theorem native32_dyadic_raw_strict (q : UInt32) (value : Dyadic)
    (he0 : 1 ≤ (Model.NativeBinary32.expField q).toNat)
    (he1 : (Model.NativeBinary32.expField q).toNat ≤ 254)
    (hf : (Model.NativeBinary32.fracField q).toNat < 8388608)
    (hl : R24NormalCell.lowerSigned (Model.NativeBinary32.signBit q)
      (Model.NativeBinary32.expField q).toNat (Model.NativeBinary32.fracField q).toNat < value.toReal)
    (hu : value.toReal < R24NormalCell.upperSigned (Model.NativeBinary32.signBit q)
      (Model.NativeBinary32.expField q).toNat (Model.NativeBinary32.fracField q).toNat) :
    Model.NativeBinary32.roundDyadic value = q := by
  rcases value with ⟨sign, num, exponent⟩
  rw [R24DyadicAgreement.roundDyadic_eq_roundRatScaled]
  apply R24NormalCell.native32_raw_strict q sign num 1 exponent
    (Dyadic.mk sign num exponent).toReal (by decide) he0 he1 hf _ hl hu
  cases sign <;>
    simp [Dyadic.toReal, Dyadic.signedSignificand, Model.signedScaledRatToReal,
      Model.scaledRatToReal, Model.bpow, FloatLib.Floats.Formats.Flocq.bpow,
      binaryRadix, Radix.toReal]

end Submission.R24DyadicCell
