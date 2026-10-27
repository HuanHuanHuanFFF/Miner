namespace Submission.R17UInt64Fields

open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange

theorem normalCore_eq_fields (sum u v : UInt32) (sign : Bool)
    (hs0 : 128 ≤ sum.toNat) (hs : sum.toNat ≤ 380)
    (hsign : ((u ^^^ v) &&& (0x80000000 : UInt32)) =
      (if sign then (0x80000000 : UInt32) else 0)) :
    R17NumericMulInteger.normalCore sum u v =
      Model.NativeBinary32.mkBits sign
        (R14ExponentShift.middleExponent
          (R14ExponentShift.product (R2W01b.mantissa u) (R2W01b.mantissa v))+sum.toNat-300)
        (R14ExponentShift.storedFraction
          (R14ExponentShift.product (R2W01b.mantissa u) (R2W01b.mantissa v))) := by
  have ha := R2W01c.mantissa_bounds u
  have hb := R2W01c.mantissa_bounds v
  change ((u ^^^ v) &&& (0x80000000 : UInt32)) |||
      (exponentWord sum (R2W01b.mantissa u) (R2W01b.mantissa v) <<< 23) |||
      fractionWord (R2W01b.mantissa u) (R2W01b.mantissa v) = _
  rw [hsign]
  exact packed_fields sign sum _ _ ha.1 ha.2 hb.1 hb.2 hs0 hs

end Submission.R17UInt64Fields
