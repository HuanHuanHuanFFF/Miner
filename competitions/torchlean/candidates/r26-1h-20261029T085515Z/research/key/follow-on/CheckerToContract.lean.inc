/- Composition after the direct midpoint layer, CheckerConsequences,
   the retained NormalCell/DyadicCell closure, and ContractWordCore. -/
namespace Submission.R26CheckerToContract
open ExactRuntime FloatLib.Numerics
open FloatLib.Floats FloatLib.Floats.Formats.BinaryInterchange
open Submission.R25OrderKey Submission.R25Checker

private theorem exact_integer_real (T e : Int) :
    (ofIntDyadic T e).toReal = (T : Real) * (2 : Real) ^ e := by
  rw [← Dyadic.cast_toRat, toRat_ofIntDyadic]
  push_cast

/-- Only the genuine native endpoint enclosure remains a producer premise.
The actual guard derives normality/nonzero, the actual word cell gives native
rounding, and the official integer finisher is the resulting output. -/
theorem accepted_finishWord (s r : Float) (sw : UInt64) (q : UInt32)
    (T e : Int) (negZero : Bool)
    (henc : nativeValue (s - r) ≤ (T : Real) * (2 : Real) ^ e ∧
      (T : Real) * (2 : Real) ^ e ≤ nativeValue (s + r))
    (hacc : certify s r sw q = true) :
    finishWord T e negZero = q := by
  obtain ⟨he0, he255, _⟩ := accepted_components s r sw q hacc
  have hT := R26CheckerConsequences.accepted_total_nonzero s r sw q T e henc hacc
  have hc := R26CheckerConsequences.accepted_contains_exact s r sw q
    ((T : Real) * (2 : Real) ^ e) henc hacc
  have heB := eWord_bound q
  have hfB := fWord_bound q
  have heN0 : (eWord q).toNat ≠ 0 := by
    intro hz
    exact he0 (UInt32.toNat_inj.mp hz)
  have heN255 : (eWord q).toNat ≠ 255 := by
    intro hz
    exact he255 (UInt32.toNat_inj.mp hz)
  have hn0 : 1 ≤ (Model.NativeBinary32.expField q).toNat := by
    rw [← eWord_eq_native]
    omega
  have hn255 : (Model.NativeBinary32.expField q).toNat ≤ 254 := by
    rw [← eWord_eq_native]
    omega
  have hnf : (Model.NativeBinary32.fracField q).toNat < 8388608 := by
    rw [← fWord_eq_native]
    exact hfB
  have hv := signed_midpoint_values q he0 he255
  have hl : R24NormalCell.lowerSigned (Model.NativeBinary32.signBit q)
      (Model.NativeBinary32.expField q).toNat (Model.NativeBinary32.fracField q).toNat <
      (ofIntDyadic T e).toReal := by
    rw [exact_integer_real]
    rw [hv.1] at hc
    simpa only [negative32_eq_native, eWord_eq_native, fWord_eq_native,
      cellLower, cellUpper, R24NormalCell.lowerSigned,
      R24NormalCell.lowerMagnitude, R24NormalCell.upperMagnitude,
      Model.bpow, FloatLib.Floats.Formats.Flocq.bpow,
      binaryRadix, Radix.toReal] using hc.1
  have hu : (ofIntDyadic T e).toReal <
      R24NormalCell.upperSigned (Model.NativeBinary32.signBit q)
        (Model.NativeBinary32.expField q).toNat (Model.NativeBinary32.fracField q).toNat := by
    rw [exact_integer_real]
    rw [hv.2] at hc
    simpa only [negative32_eq_native, eWord_eq_native, fWord_eq_native,
      cellLower, cellUpper, R24NormalCell.upperSigned,
      R24NormalCell.lowerMagnitude, R24NormalCell.upperMagnitude,
      Model.bpow, FloatLib.Floats.Formats.Flocq.bpow,
      binaryRadix, Radix.toReal] using hc.2
  have hr := R24DyadicCell.native32_dyadic_raw_strict q (ofIntDyadic T e)
    hn0 hn255 hnf hl hu
  exact R25ContractWordBridge.finishWord_of_native_result (ofIntDyadic T e)
    T e negZero q hT (toRat_ofIntDyadic T e) hr

/-- The same theorem consumes acceptance from the actual runtime definition. -/
theorem actual_accepted_finishWord (s r : Float) (sw : UInt64) (q : UInt32)
    (T e : Int) (negZero : Bool)
    (henc : nativeValue (s - r) ≤ (T : Real) * (2 : Real) ^ e ∧
      (T : Real) * (2 : Real) ^ e ≤ nativeValue (s + r))
    (hacc : R24PortableF64.certify s r sw q = true) :
    finishWord T e negZero = q := by
  apply accepted_finishWord s r sw q T e negZero henc
  simpa only [certify_eq_runtime] using hacc

end Submission.R26CheckerToContract
