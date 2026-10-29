namespace Submission.R26ProducerNumerics
open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange
open R2W01c
open Submission.R24PortableF64
open Submission.R24RepresentationWiden (expWord expWord_toNat wordExp_lt)
open Submission.R25PrepareAgreement
open Submission.R26PreparePeak

noncomputable def p2 (e : Int) : Real := Model.bpow e
noncomputable def rawValue (u : UInt32) : Real := Model.toReal (raw32 u)

theorem raw_finite (u : UInt32) (hf : expWord u ≠ 255) :
    Model.isFinite (raw32 u) = true := by
  have he := wordExp_lt u
  have hne : wordExp u ≠ 255 := by
    intro h
    apply hf
    apply UInt32.toNat_inj.mp
    simpa only [expWord_toNat] using h
  rw [raw32_eq_fields]
  exact Model.isFinite_ofFields_ieee FloatFormat.binary32 (by decide) _ _ _ (by
    change wordExp u < 255
    omega)

theorem prepare_get_finite_value (raw : Array UInt32) (hv : (prepare raw).valid = true)
    (i : Nat) (hi : i < raw.size) :
    ((prepare raw).values.get! i).isFinite = true ∧
      Model.toReal (ExecFloat.Binary.toModel (ExecFloat.Binary.ofFloat
        ((prepare raw).values.get! i))) = rawValue raw[i] := by
  rw [prepare_get raw hv i hi]
  exact Submission.R25FiniteWiden.finite_actual_value raw[i]
    (prepare_valid_rawfinite raw hv i hi)

theorem prepared_product_exact (rawX rawY : Array UInt32)
    (hx : (prepare rawX).valid = true) (hy : (prepare rawY).valid = true)
    (i : Nat) (hix : i < rawX.size) (hiy : i < rawY.size) :
    ((prepare rawX).values.get! i * (prepare rawY).values.get! i).isFinite = true ∧
      Submission.R24NativeMul.value
        ((prepare rawX).values.get! i * (prepare rawY).values.get! i) =
      rawValue rawX[i] * rawValue rawY[i] := by
  have hxv := prepare_get_finite_value rawX hx i hix
  have hyv := prepare_get_finite_value rawY hy i hiy
  have hfx := raw_finite rawX[i] (prepare_valid_rawfinite rawX hx i hix)
  have hfy := raw_finite rawY[i] (prepare_valid_rawfinite rawY hy i hiy)
  apply Submission.R24NativeMul.native_mul_exact_from_raw32_values
    _ _ rawX[i] rawY[i] hxv.1 hyv.1 hfx hfy
  · simpa only [ExecFloat.Binary.toModel_ofFloat] using hxv.2
  · simpa only [ExecFloat.Binary.toModel_ofFloat] using hyv.2

theorem signed_abs (s : Bool) (m : Nat) (e : Int) :
    |(if s then (-1 : Real) else 1) * (m : Real) * Model.bpow e| =
      (m : Real) * Model.bpow e := by
  cases s <;>
    simp [abs_mul, abs_of_nonneg (Nat.cast_nonneg m),
      abs_of_nonneg (Model.bpow_nonneg e)]

theorem raw_magnitude (u : UInt32) (hf : expWord u ≠ 255) :
    |rawValue u| < p2 ((index32 u).toNat - (125 : Int)) := by
  have he := wordExp_lt u
  have hfrac := wordFrac_lt u
  have hne : wordExp u ≠ 255 := by
    intro h
    apply hf
    apply UInt32.toNat_inj.mp
    simpa only [expWord_toNat] using h
  rw [index_nat, expWord_toNat]
  unfold rawValue
  rw [raw32_eq_fields]
  by_cases hz : wordExp u = 0
  · rw [hz]
    change |Model.toReal (Model.ofFields FloatFormat.binary32 (wordSign u) 0 (wordFrac u))| <
      Model.bpow (-125)
    by_cases hfz : wordFrac u = 0
    · rw [hfz]
      change |Model.toReal (Model.zero FloatFormat.binary32 (wordSign u))| < _
      rw [Model.toReal_zero, abs_zero]
      exact Model.bpow_pos _
    · rw [Model.toReal_ofFields_subnormal FloatFormat.binary32 (wordSign u)
        (wordFrac u) hfz hfrac, signed_abs]
      change (wordFrac u : Real) * Model.bpow (-149) < Model.bpow (-125)
      have hc : (wordFrac u : Real) < (16777216 : Real) := by exact_mod_cast (by omega : wordFrac u < 16777216)
      calc
        _ < (16777216 : Real) * Model.bpow (-149) :=
          mul_lt_mul_of_pos_right hc (Model.bpow_pos _)
        _ = Model.bpow (-125) := by
          have hp : Model.bpow 24 = (16777216 : Real) := by
            norm_num [Model.bpow, FloatLib.Floats.Formats.Flocq.bpow,
              FloatLib.Numerics.binaryRadix, FloatLib.Numerics.Radix.toReal]
          rw [← hp, ← Model.bpow_add]
          norm_num
  · have hpos : 0 < wordExp u := by omega
    rw [Model.toReal_ofFields_normal FloatFormat.binary32 (wordSign u) (wordExp u)
      (wordFrac u) hz (by change wordExp u < 255; omega) hfrac]
    change |(if wordSign u then (-1 : Real) else 1) *
      ((8388608 + wordFrac u : Nat) : Real) * Model.bpow ((wordExp u : Int) - 127 - 23)| < _
    rw [signed_abs]
    have hc : ((8388608 + wordFrac u : Nat) : Real) < (16777216 : Real) := by
      exact_mod_cast (by omega : 8388608 + wordFrac u < 16777216)
    calc
      _ < (16777216 : Real) * Model.bpow ((wordExp u : Int) - 127 - 23) :=
        mul_lt_mul_of_pos_right hc (Model.bpow_pos _)
      _ = p2 (((wordExp u - 1 : Nat) : Int) - 125) := by
        have hp : Model.bpow 24 = (16777216 : Real) := by
          norm_num [Model.bpow, FloatLib.Floats.Formats.Flocq.bpow,
            FloatLib.Numerics.binaryRadix, FloatLib.Numerics.Radix.toReal]
        rw [← hp, ← Model.bpow_add]
        unfold p2
        congr 1
        omega

theorem prepared_raw_magnitude (raw : Array UInt32) (hv : (prepare raw).valid = true)
    (i : Nat) (hi : i < raw.size) :
    |rawValue raw[i]| < p2 ((prepare raw).maxIndex.toNat - (125 : Int)) := by
  have hb := raw_magnitude raw[i] (prepare_valid_rawfinite raw hv i hi)
  have hp := prepare_index_bound raw hv i hi
  refine hb.trans_le ?_
  exact Model.bpow_le_bpow_of_le (by omega)

end Submission.R26ProducerNumerics
