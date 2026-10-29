/- A cheap word proposal with no accuracy premise. It is data, never a proof.
   The exact interval certificate controls acceptance; failure belongs to the
   caller's unchanged exact fallback. Old ContractTensor helper, NOT_RUN. -/
namespace Submission.R24ArbitraryProposal
open FloatLib.Numerics.FixedWord

/-- Normal-range midpoint-up bit proposal. All UInt64 inputs are allowed. -/
@[inline] def magnitudeProposal (bits : UInt64) : UInt32 :=
  ((((bits &&& 0x7fffffffffffffff) + 0x10000000) >>> 29).toUInt32) - 0xc0000000

@[inline] def field (bits : UInt64) : UInt32 :=
  (magnitudeProposal bits >>> 23) &&& 255

@[inline] def mantissa (bits : UInt64) : UInt64 :=
  ((magnitudeProposal bits &&& 0x7fffff) ||| 0x800000).toUInt64

@[inline] def check (lo hi : UInt128) (den : UInt64) (bits : UInt64) : Bool :=
  if mantissa bits == 8388608 then
    R24IntervalWord128.powerCheck lo hi den (field bits)
  else R24IntervalWord128.strictCheck lo hi den (mantissa bits) (field bits)

/-- The result sign comes from the exact expression, separately from the hint. -/
@[inline] def word (sign : Bool) (bits : UInt64) : UInt32 :=
  FloatLib.Floats.Formats.BinaryInterchange.Model.NativeBinary32.mkBits
    sign (field bits).toNat ((mantissa bits).toNat - 8388608)

theorem check_sound (sign : Bool) (lo hi : UInt128) (den : UInt64) (bits : UInt64)
    (num : Nat) (hlo : lo.toNat ≤ num) (hhi : num ≤ hi.toNat)
    (h : check lo hi den bits = true) :
    FloatLib.Floats.Formats.BinaryInterchange.Model.NativeBinary32.roundRatScaled
        sign num den.toNat (((field bits).toNat : Int) - 150) = word sign bits := by
  by_cases hpower : mantissa bits = 8388608
  · have hc : R24IntervalWord128.powerCheck lo hi den (field bits) = true := by
      simpa only [check, beq_iff_eq, hpower, if_true] using h
    have hr := R24IntervalWord128.powerCheck_sound sign lo hi den (field bits) num hlo hhi hc
    simpa [word, hpower] using hr
  · have hc : R24IntervalWord128.strictCheck lo hi den (mantissa bits) (field bits) = true := by
      simpa only [check, beq_iff_eq, hpower, if_false] using h
    exact R24IntervalWord128.strictCheck_sound sign lo hi den (mantissa bits) (field bits) num hlo hhi hc

end Submission.R24ArbitraryProposal
