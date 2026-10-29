/- Actual native64 midpoint words to the strict normal-cell real endpoints.
   Positive fields only; the word decodes and native model bridge are reused.
   This is a real-value equality, not an inverse inference about native bits. -/
namespace Submission.R24MidpointReal
open FloatLib.Numerics
open FloatLib.Floats FloatLib.Floats.Formats.BinaryInterchange

noncomputable def nativeReal (word : UInt64) : Real :=
  Model.toReal (R24RepresentationWiden.native64 (Float.ofBits word))

private theorem of_decode (word : UInt64) (d : Dyadic)
    (hd : Model.toDyadic? (R24MidpointWords.raw word) = some d) :
    nativeReal word = d.toReal := by
  unfold nativeReal
  rw [R24RepresentationWiden.native_ofBits_of_decode word hd]
  rw [Model.toReal_eq, hd]

private theorem positive_dyadic_real (mantissa : Nat) (exponent : Int) :
    (Dyadic.mk false mantissa exponent).toReal = (mantissa : Real) * Model.bpow exponent := by
  simpa only [Model.bpow, FloatLib.Floats.Formats.Flocq.bpow, binaryRadix, Radix.toReal] using
    Dyadic.toReal_mk_false mantissa exponent

private theorem bpow_neg29 : Model.bpow (-29 : Int) = (1 : Real) / 536870912 := by
  norm_num [Model.bpow, FloatLib.Floats.Formats.Flocq.bpow, binaryRadix, Radix.toReal]

private theorem bpow_neg30 : Model.bpow (-30 : Int) = (1 : Real) / 1073741824 := by
  norm_num [Model.bpow, FloatLib.Floats.Formats.Flocq.bpow, binaryRadix, Radix.toReal]

theorem upper_real (e f : UInt64)
    (he0 : 0 < e.toNat) (he : e.toNat < 255) (hf : f.toNat < 8388608) :
    nativeReal (R24MidpointWords.upper e f) = R24NormalCell.upperMagnitude e.toNat f.toNat := by
  have hd := R24MidpointWords.upper_decode e f he0 he hf
  rw [of_decode _ _ hd, positive_dyadic_real]
  have hexp : ((e.toNat + 896 : Nat) : Int) - 1023 - 52 =
      (e.toNat : Int) - 150 + (-29) := by omega
  rw [hexp, Model.bpow_add, bpow_neg29]
  unfold R24NormalCell.upperMagnitude
  push_cast <;> ring

theorem lower_real (e f : UInt64)
    (he0 : 0 < e.toNat) (he : e.toNat < 255) (hf : f.toNat < 8388608) :
    nativeReal (R24MidpointWords.lower e f) = R24NormalCell.lowerMagnitude e.toNat f.toNat := by
  by_cases hf0 : f.toNat = 0
  · have hfw : f = 0 := by
      apply UInt64.toNat_inj.mp
      simpa only [UInt64.toNat_zero] using hf0
    subst f
    by_cases he1 : e.toNat = 1
    · have hew : e = 1 := by
        apply UInt64.toNat_inj.mp
        change e.toNat = 1
        exact he1
      subst e
      rw [of_decode _ _ R24MidpointWords.lower_minNormal_decode, positive_dyadic_real]
      rw [show (-179 : Int) = (-149) + (-30) by decide, Model.bpow_add, bpow_neg30]
      have hone : (1 : UInt64).toNat = 1 := rfl
      rw [hone, UInt64.toNat_zero]
      norm_num only [R24NormalCell.lowerMagnitude, Nat.cast_zero, add_zero] <;> ring
    · have he2 : 1 < e.toNat := by omega
      have hd := R24MidpointWords.lower_power_decode e he2 he
      rw [of_decode _ _ hd, positive_dyadic_real]
      have hexp : ((e.toNat + 895 : Nat) : Int) - 1023 - 52 =
          (e.toNat : Int) - 150 + (-30) := by omega
      rw [hexp, Model.bpow_add, bpow_neg30]
      have hpower : (0 : UInt64).toNat = 0 ∧ 1 < e.toNat := ⟨rfl, he2⟩
      simp only [R24NormalCell.lowerMagnitude, hpower, ite_true, UInt64.toNat_zero,
        Nat.cast_zero, add_zero]
      norm_num only <;> ring
  · have hfpos : 0 < f.toNat := by omega
    have hd := R24MidpointWords.lower_inner_decode e f he0 he hfpos hf
    rw [of_decode _ _ hd, positive_dyadic_real]
    have hexp : ((e.toNat + 896 : Nat) : Int) - 1023 - 52 =
        (e.toNat : Int) - 150 + (-29) := by omega
    rw [hexp, Model.bpow_add, bpow_neg29]
    have hpower : ¬ (f.toNat = 0 ∧ 1 < e.toNat) := fun h => hf0 h.1
    simp only [R24NormalCell.lowerMagnitude, hpower, ite_false]
    rw [Nat.cast_add, Nat.cast_mul, Nat.cast_sub (by omega : 1 ≤ 2 * f.toNat)]
    push_cast <;> ring

end Submission.R24MidpointReal
