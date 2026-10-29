/- Logical exact rescaling for the actual native32 rational rounder.
   No shifted numerator/denominator is introduced by an executable caller.
   Old ContractTensor helper; typing/replay/AX still NOT_RUN. -/
namespace Submission.R24RescaleNative32
open FloatLib.Numerics
open FloatLib.Floats FloatLib.Floats.Formats.BinaryInterchange

private theorem scale_zero_num (den : Nat) (scale : Int) :
    (RationalBinary.scaleByPowerOfTwo 0 den scale).1 = 0 := by
  cases scale <;> simp [RationalBinary.scaleByPowerOfTwo, Nat.shiftLeft_eq]

private theorem scale_zero_den (num : Nat) (scale : Int) :
    (RationalBinary.scaleByPowerOfTwo num 0 scale).2 = 0 := by
  cases scale <;> simp [RationalBinary.scaleByPowerOfTwo, Nat.shiftLeft_eq]

theorem roundRatScaled_rescale (sign : Bool) (num den : Nat) (source target : Int) :
    let scaled := RationalBinary.scaleByPowerOfTwo num den (source - target)
    Model.NativeBinary32.roundRatScaled sign num den source =
      Model.NativeBinary32.roundRatScaled sign scaled.1 scaled.2 target := by
  let delta := source - target
  let scaled := RationalBinary.scaleByPowerOfTwo num den delta
  change Model.NativeBinary32.roundRatScaled sign num den source =
    Model.NativeBinary32.roundRatScaled sign scaled.1 scaled.2 target
  by_cases hd : den = 0
  · have hsd : scaled.2 = 0 := by
      simpa only [scaled, hd] using scale_zero_den num delta
    simp only [Model.NativeBinary32.roundRatScaled, beq_iff_eq, hd, hsd, if_true]
  have hsd : scaled.2 ≠ 0 :=
    RationalBinary.scaleByPowerOfTwo_snd_ne_zero num den delta hd
  by_cases hn : num = 0
  · have hsn : scaled.1 = 0 := by
      simpa only [scaled, hn] using scale_zero_num den delta
    simp only [Model.NativeBinary32.roundRatScaled, beq_iff_eq, hd, hsd, hn, hsn, if_false, if_true]
  have hsn : scaled.1 ≠ 0 :=
    RationalBinary.scaleByPowerOfTwo_fst_ne_zero num den delta hn
  have hlog : RationalBinary.floorLog2 scaled.1 scaled.2 =
      RationalBinary.floorLog2 num den + delta :=
    Model.floorLog2_scaleByPowerOfTwo num den delta hn hd
  have htotal : RationalBinary.floorLog2 num den + delta + target =
      RationalBinary.floorLog2 num den + source := by dsimp [delta]; omega
  have hsub : delta + (target + 149) = source + 149 := by dsimp [delta]; omega
  have hnormal : delta + (23 - (RationalBinary.floorLog2 num den + delta)) =
      23 - RationalBinary.floorLog2 num den := by omega
  have hqsub := Model.roundQuotientEven_scaleByPowerOfTwo_add num den delta (target + 149) hd
  dsimp only at hqsub
  change roundQuotientEven (RationalBinary.scaleByPowerOfTwo scaled.1 scaled.2 (target + 149)).1
      (RationalBinary.scaleByPowerOfTwo scaled.1 scaled.2 (target + 149)).2 =
    roundQuotientEven (RationalBinary.scaleByPowerOfTwo num den (delta + (target + 149))).1
      (RationalBinary.scaleByPowerOfTwo num den (delta + (target + 149))).2 at hqsub
  rw [hsub] at hqsub
  have hqnormal := Model.roundQuotientEven_scaleByPowerOfTwo_add num den delta
    (23 - (RationalBinary.floorLog2 num den + delta)) hd
  dsimp only at hqnormal
  change roundQuotientEven
      (RationalBinary.scaleByPowerOfTwo scaled.1 scaled.2 (23 - (RationalBinary.floorLog2 num den + delta))).1
      (RationalBinary.scaleByPowerOfTwo scaled.1 scaled.2 (23 - (RationalBinary.floorLog2 num den + delta))).2 =
    roundQuotientEven (RationalBinary.scaleByPowerOfTwo num den
      (delta + (23 - (RationalBinary.floorLog2 num den + delta)))).1
      (RationalBinary.scaleByPowerOfTwo num den
        (delta + (23 - (RationalBinary.floorLog2 num den + delta)))).2 at hqnormal
  rw [hnormal] at hqnormal
  simp only [Model.NativeBinary32.roundRatScaled, beq_iff_eq, hd, hsd, hn, hsn,
    if_false, hlog, htotal, hqsub, hqnormal]

end Submission.R24RescaleNative32
