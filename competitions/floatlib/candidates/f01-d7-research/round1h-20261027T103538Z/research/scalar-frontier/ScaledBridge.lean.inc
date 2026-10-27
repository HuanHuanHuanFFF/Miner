/- Requires the exact B2 prefix and Runtime-scaled-u32.lean.inc. NOT_RUN.
   This proves the proposed small scaling interface, not a public mul_spec. -/
namespace Submission.R21ScaledU32
open FloatLib FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange

def outBits (m e : Nat) : UInt32 :=
  Model.NativeBinary32.mkBits false (e+127) (m-8388608)

theorem out_decode (m e : Nat) (hm0 : 8388608 ≤ m) (hm1 : m < 16777216)
    (he : e=23 ∨ e=24) :
    Model.toDyadic? (R2W01c.rawModel (outBits m e)) =
      some ⟨false,m,((e-23 : Nat) : Int)⟩ := by
  have hf : m-8388608 < 8388608 := by omega
  have hs : 8388608+(m-8388608)=m := by omega
  have hx : ((e+127 : Nat) : Int)-150 = ((e-23 : Nat) : Int) := by omega
  rw [outBits,R2W01c.rawModel_eq_native32,Model.NativeBinary32.ofUInt32_mkBits]
  have h := R2W01c.fields32_toDyadic false (e+127) (m-8388608)
    (by omega) (by omega) hf
  simpa only [hs,hx] using h

theorem powNeg23_decode :
    Model.toDyadic? (R2W01c.nativeModel powNeg23) =
      some ⟨false,8388608,(-46 : Int)⟩ := by
  unfold powNeg23
  apply R2W01c.nativeModel_ofBits_decode
  change Model.toDyadic? (R2W01c.rawModel
    (Model.NativeBinary32.mkBits false 104 0)) = _
  rw [R2W01c.rawModel_eq_native32,Model.NativeBinary32.ofUInt32_mkBits]
  simpa using R2W01c.fields32_toDyadic false 104 0 (by decide) (by decide) (by decide)

theorem scaled_value (m e : Nat) (he : e=23 ∨ e=24) :
    (Numerics.Dyadic.mk false m (e : Int)).toReal *
        (Numerics.Dyadic.mk false 8388608 (-46)).toReal =
      (Numerics.Dyadic.mk false m ((e-23 : Nat) : Int)).toReal := by
  rcases he with rfl | rfl <;>
    norm_num [Numerics.Dyadic.toReal,Numerics.Dyadic.signedSignificand] <;> ring

theorem scaled_decode (x : Float32) (m e : Nat)
    (hm0 : 8388608 ≤ m) (hm1 : m < 16777216) (he : e=23 ∨ e=24)
    (hx : Model.toDyadic? (R2W01c.nativeModel x) = some ⟨false,m,(e : Int)⟩) :
    Model.toDyadic? (R2W01c.nativeModel (x*powNeg23)) =
      some ⟨false,m,((e-23 : Nat) : Int)⟩ := by
  have hy := powNeg23_decode
  have hz := out_decode m e hm0 hm1 he
  have hn : m ≠ 0 := by omega
  have hz0 : Model.toReal (R2W01c.rawModel (outBits m e)) ≠ 0 := by
    have hd0 : (Numerics.Dyadic.mk false m ((e-23 : Nat) : Int)).toReal ≠ 0 := by
      apply ne_of_gt
      simp only [Numerics.Dyadic.toReal_mk_false]
      have hmpos : (0 : ℝ) < m := by exact_mod_cast (show 0 < m by omega)
      positivity
    simpa only [Model.toReal_eq,hz] using hd0
  have hmul : Model.mul (R2W01c.nativeModel x) (R2W01c.nativeModel powNeg23) =
      R2W01c.rawModel (outBits m e) := by
    apply R2W01cModel.mul_eq_of_finite_value _ _ _ (by decide)
      (Model.isFinite_eq_true_of_toDyadic?_some hx)
      (Model.isFinite_eq_true_of_toDyadic?_some hy)
      (Model.isFinite_eq_true_of_toDyadic?_some hz) hz0
    simpa only [Model.toReal_eq,hx,hy,hz] using scaled_value m e he
  have hnative := R2W01c.native_mul_eq_of_decoded_raw_model_mul_eq
    x powNeg23 (outBits m e) hx hy hmul
  rw [hnative]
  exact R2W01c.nativeModel_ofBits_decode (outBits m e) hz

theorem toUInt32_of_nonnegative_integral_decode (x : Float32) (m e : Nat)
    (hd : Model.toDyadic? (Model.ofFloat32Model x.toModel) =
      some ⟨false,m,(e : Int)⟩)
    (hfit : m*2^e < UInt32.size) :
    x.toUInt32.toNat = m*2^e := by
  have hv := Model.exactValue_eq_finite_of_toDyadic?_eq_some hd
  have hi := Model.toInt_toModel_eq (fmt := FloatFormat.binary32) (by decide)
    (Model.ofFloat32Model x.toModel) 0 (UInt32.size-1)
  rw [Model.toModel_ofFloat32Model,hv] at hi
  change x.toModel.unpack.toInt 0 (UInt32.size-1) =
    Model.roundDyadicToInt .towardZero
      (⟨false,m,(e : Int)⟩ : FloatLib.Numerics.Dyadic) at hi
  have hr : Model.roundDyadicToInt .towardZero (⟨false,m,(e : Int)⟩ : FloatLib.Numerics.Dyadic) =
      ((m*2^e : Nat) : Int) := by
    by_cases hm : m=0
    · subst m
      simp [Model.roundDyadicToInt]
    · simp [Model.roundDyadicToInt,hm,Nat.shiftLeft_eq]
  change (UInt32.ofNatClamp
    ((x.toModel.unpack.toInt 0 (UInt32.size-1)).toNat)).toNat = _
  rw [hi,hr]
  simpa only [Int.toNat_natCast] using (UInt32.toNat_ofNatClamp_of_lt hfit)

theorem scaled_toUInt32 (x : Float32) (m e : Nat)
    (hm0 : 8388608 ≤ m) (hm1 : m < 16777216) (he : e=23 ∨ e=24)
    (hx : Model.toDyadic? (R2W01c.nativeModel x) = some ⟨false,m,(e : Int)⟩) :
    (x*powNeg23).toUInt32.toNat = m*2^(e-23) := by
  apply toUInt32_of_nonnegative_integral_decode _ m (e-23)
    (scaled_decode x m e hm0 hm1 he hx)
  change m*2^(e-23) < 4294967296
  rcases he with rfl | rfl <;> norm_num <;> omega

theorem scaled_fields (x : Float32) (m e : Nat)
    (hm0 : 8388608 ≤ m) (hm1 : m < 16777216) (he : e=23 ∨ e=24)
    (hx : Model.toDyadic? (R2W01c.nativeModel x) = some ⟨false,m,(e : Int)⟩) :
    let z := (x*powNeg23).toUInt32
    (z >>> 24).toNat = e-23 ∧ (z >>> (z >>> 24)).toNat = m := by
  let z := (x*powNeg23).toUInt32
  have hz : z.toNat = m*2^(e-23) := scaled_toUInt32 x m e hm0 hm1 he hx
  have hh : (z >>> 24).toNat = e-23 := by
    rw [UInt32.toNat_shiftRight]
    change z.toNat >>> 24 = e-23
    rw [hz]
    rcases he with rfl | rfl <;>
      norm_num [Nat.shiftRight_eq_div_pow] <;> omega
  have hh32 : (z >>> 24).toNat < 32 := by
    rw [hh]
    rcases he with rfl | rfl <;> decide
  change (z >>> 24).toNat = e-23 ∧ (z >>> (z >>> 24)).toNat = m
  refine ⟨hh,?_⟩
  rw [UInt32.toNat_shiftRight,Nat.mod_eq_of_lt hh32,hh,hz]
  rcases he with rfl | rfl <;>
    norm_num [Nat.shiftRight_eq_div_pow] <;> omega

end Submission.R21ScaledU32
