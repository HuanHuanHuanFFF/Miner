from pathlib import Path
H=Path(__file__).parent;ROOT=Path.cwd();P=ROOT/'competitions/floatlib/candidates/f01-d7-research/round7h-20261028T203856Z/development-broad/CellPrimitive-v2.lean.inc';s=P.read_text(encoding='utf-8-sig')
a=s[s.index('theorem quotient_strict_midpoint'):s.index('theorem quotient_even_closed_midpoint')]
b=s[s.index('theorem normal_ratio_nat_bounds'):s.index('theorem normal_ratio_log23')]
header='import ContractExact\n\n/- ExactRuntime finite dot integer totals have the fixed scale2^-298.\nThis root targets that scale directly; it is not the actual caller theorem. -/\nnamespace Submission.R27FixedScaleCell\nopen FloatLib.Floats FloatLib.Floats.Formats.BinaryInterchange\nopen FloatLib.Numerics\n\n'
tail='''
/-- Interior normal non-power cell at the official dot's fixed integer scale.
No general dyadic/rational rescaling bridge is needed for this statement. -/
theorem native32_fixed298_strict (sign : Bool) (num E mant : Nat)
    (hElo : 2 ≤ E) (hEhi : E ≤ 253)
    (hmlo : 8388608 < mant) (hmhi : mant < 16777216)
    (hl : 2 ^ (E + 148) * (2 * mant - 1) < 2 * num)
    (hu : 2 * num < 2 ^ (E + 148) * (2 * mant + 1)) :
    Model.NativeBinary32.roundDyadic ⟨sign, num, -298⟩ =
      Model.NativeBinary32.mkBits sign E (mant - 8388608) := by
  have hd : 0 < 2 ^ (E + 148) := Nat.two_pow_pos _
  obtain ⟨hlo, hhi⟩ := normal_ratio_nat_bounds num (2 ^ (E + 148)) mant
    hd hmlo hmhi hl hu
  have hn : num ≠ 0 := by omega
  have hlog : num.log2 = E + 171 := by
    rw [Nat.log2_eq_iff hn]
    constructor
    · rw [show E + 171 = 23 + (E + 148) by omega, Nat.pow_add]
      change 8388608 * 2 ^ (E + 148) ≤ num
      exact hlo
    · rw [show E + 171 + 1 = 24 + (E + 148) by omega, Nat.pow_add]
      change num < 16777216 * 2 ^ (E + 148)
      exact hhi
  have hr : roundShiftRightEven num (E + 148) = mant := by
    rw [roundShiftRightEven_eq_roundQuotientEven]
    exact quotient_strict_midpoint num (2 ^ (E + 148)) mant hd (by omega) hl hu
  have htotal : ((E + 171 : Nat) : Int) + (-298) = (E : Int) - 127 := by omega
  have hsub : ¬ (E : Int) - 127 < -126 := by omega
  have hlead : 23 ≤ E + 171 := by omega
  have hshift : E + 171 - 23 = E + 148 := by omega
  have hcarry : mant ≠ Model.pow2 24 := by change mant ≠ 16777216; omega
  have hbig : ¬ (E : Int) - 127 > 127 := by omega
  have hencoded : ((E : Int) - 127 + 127).toNat = E := by omega
  simp only [Model.NativeBinary32.roundDyadic, beq_iff_eq, hn, ite_false,
    hlog, htotal, hsub, hlead, ite_true, hshift, hr, hcarry, hbig,
    hencoded, show Model.pow2 23 = 8388608 by decide]

end Submission.R27FixedScaleCell
'''
(H/'fixed-scale/Fixed298NatCellContractOnly.lean').write_text(header+a+'\n'+b+'\n'+tail,encoding='utf-8',newline='\n')
print('Fixed298 Nat cell source prepared')
