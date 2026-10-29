/- R24 draft portable transport. Requires B2, quotient2 and ReuseLog23 first.
   Source only: no Kernel/CI/native execution. Actual normal rational-rounder
   equality, including ties and carry; no canonical-Rat or RMS wrapper claim. -/
namespace Submission.R24NormalizedQuotient
open FloatLib.Floats FloatLib.Floats.Formats.BinaryInterchange

@[inline] def normalWord (sign : Bool) (n d q : UInt64) (e : UInt32) : UInt32 :=
  let mantissa := R24QuotientCertificate.rounded n d q
  if mantissa == (0x1000000 : UInt64) then FastMul.mkW sign (e + 1) 0
  else FastMul.mkW sign e (FastMul.fracW mantissa)

theorem normalWord_spec (sign : Bool) (n d q : UInt64) (e : UInt32)
    (hcheck : R24QuotientCertificate.check n d q = true)
    (hlo : 8388608 * d.toNat ≤ n.toNat)
    (hhi : n.toNat < 16777216 * d.toNat)
    (he0 : 1 ≤ e.toNat) (he1 : e.toNat ≤ 253) :
    normalWord sign n d q e =
      Model.NativeBinary32.roundRatScaled sign n.toNat d.toNat
        ((e.toNat : Int) - 150) := by
  have hfit : n < (0x2000000000000 : UInt64) ∧ 0 < d ∧
      d < (0x2000000 : UInt64) ∧ q < (0x2000000 : UInt64) := by
    by_contra hbad
    simp [R24QuotientCertificate.check, hbad] at hcheck
  have hd : 0 < d.toNat := UInt64.lt_iff_toNat_lt.mp hfit.2.1
  have hn : n.toNat ≠ 0 := by
    intro hz
    rw [hz] at hlo
    omega
  let m := R24QuotientCertificate.rounded n d q
  have hr : m.toNat = FloatLib.Numerics.roundQuotientEven n.toNat d.toNat :=
    R24QuotientCertificate.rounded_toNat n d q hcheck
  have hlog := ratio_log23 n.toNat d.toNat hd hlo hhi
  let exponent : Int := (e.toNat : Int) - 150
  have hbig : ¬ (23 : Int) + exponent > 127 := by dsimp [exponent]; omega
  have hsmall : ¬ (23 : Int) + exponent < -150 := by dsimp [exponent]; omega
  have hnormal : ¬ (23 : Int) + exponent < -126 := by dsimp [exponent]; omega
  have hcarryBig : ¬ (23 : Int) + exponent + 1 > 127 := by dsimp [exponent]; omega
  have hencoded : ((23 : Int) + exponent + 127).toNat = e.toNat := by
    dsimp [exponent]
    omega
  have hencodedCarry : ((23 : Int) + exponent + 1 + 127).toNat = e.toNat + 1 := by
    dsimp [exponent]
    omega
  have hp23 : Model.pow2 23 = 8388608 := by decide
  have hp24 : Model.pow2 24 = 16777216 := by decide
  have hpack (a : UInt32) (b : Nat) :
      FastMul.mkW sign a (UInt32.ofNat b) = Model.NativeBinary32.mkBits sign a.toNat b := by
    rw [← FastMul.mkW_ofNat]
    simp only [UInt32.ofNat_toNat]
  by_cases hc : m.toNat = 16777216
  · have hcw : m = (0x1000000 : UInt64) := UInt64.toNat_inj.mp hc
    have headd : (e + 1).toNat = e.toNat + 1 := by
      rw [UInt32.toNat_add]
      change (e.toNat + 1) % 4294967296 = e.toNat + 1
      exact Nat.mod_eq_of_lt (by omega)
    have hleft : normalWord sign n d q e =
        Model.NativeBinary32.mkBits sign (e.toNat + 1) 0 := by
      change (if m == (0x1000000 : UInt64) then FastMul.mkW sign (e + 1) 0
        else FastMul.mkW sign e (FastMul.fracW m)) = _
      simp only [beq_iff_eq, hcw, ite_true]
      have hh := hpack (e + 1) 0
      simpa only [headd] using hh
    have hright : Model.NativeBinary32.roundRatScaled sign n.toNat d.toNat exponent =
        Model.NativeBinary32.mkBits sign (e.toNat + 1) 0 := by
      simp only [Model.NativeBinary32.roundRatScaled, beq_iff_eq,
        Nat.ne_of_gt hd, hn, if_false, hlog, hbig, hsmall, hnormal,
        sub_self, FloatLib.Numerics.RationalBinary.scaleByPowerOfTwo_zero,
        Prod.fst, Prod.snd]
      rw [← hr]
      simp [hc, hp23, hp24, hcarryBig, hencodedCarry]
    exact hleft.trans hright.symm
  · have hcw : m ≠ (0x1000000 : UInt64) := by
      intro hw
      exact hc (congrArg UInt64.toNat hw)
    have hleft : normalWord sign n d q e =
        Model.NativeBinary32.mkBits sign e.toNat (m.toNat - 8388608) := by
      change (if m == (0x1000000 : UInt64) then FastMul.mkW sign (e + 1) 0
        else FastMul.mkW sign e (FastMul.fracW m)) = _
      simp only [beq_iff_eq, hcw, ite_false]
      rw [FastMul.fracW_eq]
      exact hpack e (m.toNat - 8388608)
    have hright : Model.NativeBinary32.roundRatScaled sign n.toNat d.toNat exponent =
        Model.NativeBinary32.mkBits sign e.toNat (m.toNat - 8388608) := by
      simp only [Model.NativeBinary32.roundRatScaled, beq_iff_eq,
        Nat.ne_of_gt hd, hn, if_false, hlog, hbig, hsmall, hnormal,
        sub_self, FloatLib.Numerics.RationalBinary.scaleByPowerOfTwo_zero,
        Prod.fst, Prod.snd]
      rw [← hr]
      simp [hc, hp23, hp24, hbig, hencoded]
    exact hleft.trans hright.symm

end Submission.R24NormalizedQuotient
