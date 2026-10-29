/- Exact project-local dependency extracted from D scalar CellPower-v2; not a new theorem claim. -/
namespace Submission.R24NormalizedQuotient
open FloatLib.Floats FloatLib.Floats.Formats.BinaryInterchange

theorem ratio_log23 (num den : Nat) (hd : 0 < den)
    (hl : 8388608 * den ≤ num) (hu : num < 16777216 * den) :
    FloatLib.Numerics.RationalBinary.floorLog2 num den = 23 := by
  have hn : num ≠ 0 := by intro h; subst num; omega
  have hdr : (0 : Real) < den := by exact_mod_cast hd
  have hlr : (8388608 : Real) ≤ (num : Real) / den := by
    apply (le_div_iff₀ hdr).2
    exact_mod_cast hl
  have hur : (num : Real) / den < (16777216 : Real) := by
    apply (div_lt_iff₀ hdr).2
    exact_mod_cast hu
  apply Model.floorLog2_eq_of_bounds num den 23 hn (Nat.ne_of_gt hd)
  · have hp : Model.bpow (23 : Int) = (8388608 : Real) := by
      norm_num [Model.bpow, FloatLib.Floats.Formats.Flocq.bpow,
        FloatLib.Numerics.binaryRadix, FloatLib.Numerics.Radix.toReal]
    simpa only [hp] using hlr
  · have hp : Model.bpow ((23 : Int) + 1) = (16777216 : Real) := by
      norm_num [Model.bpow, FloatLib.Floats.Formats.Flocq.bpow,
        FloatLib.Numerics.binaryRadix, FloatLib.Numerics.Radix.toReal]
    simpa only [hp] using hur

end Submission.R24NormalizedQuotient
