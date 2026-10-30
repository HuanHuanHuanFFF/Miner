import ContractExact

namespace R2W01c
open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange

theorem modelCanonicalOfFinite {fmt : FloatFormat} (x : Model fmt)
    (hx : (Model.toModel x).isFinite = true) : Model.IsModelCanonical x := by
  constructor
  intro he hm
  have hnan : Model.toModel x = Float.Model.UnpackedFloat.notANumber := by
    simp only [Model.toModel, Float.Model.UnpackedFloat.unpack, he, hm, ite_true, ite_false]
  rw [hnan] at hx
  cases hx

theorem modelCanonical_of_decode {fmt : FloatFormat}
    (hfmt : fmt.isIEEE = true) (x : Model fmt) {d : FloatLib.Numerics.Dyadic}
    (hd : Model.toDyadic? x = some d) : Model.IsModelCanonical x := by
  apply modelCanonicalOfFinite
  rw [Model.toDyadic?_ieee_eq_model fmt hfmt x] at hd
  cases hx : Model.toModel x <;>
    simp_all [Model.unpackedToDyadic?, Float.Model.UnpackedFloat.isFinite]


end R2W01c

/- R24 actual radius-word and native endpoint semantics.
   This is a portable helper fragment, not a replacement public kernel.
   Endpoint values are nearest-even results; no outward-rounding premise. -/
namespace Submission.R24RadiusEndpoints

open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange

abbrev F64 := FloatFormat.binary64
abbrev raw (w : UInt64) : Model F64 := Model.ofBits w.toBitVec
abbrev native (x : Float) : Model F64 := Model.ofFloatModel x.toModel
noncomputable def rval (x : Float) : Real := Model.toReal (native x)
noncomputable def p2 (e : Int) : Real :=
  FloatLib.Floats.Formats.Flocq.bpow FloatLib.Numerics.binaryRadix e

@[inline] def radiusWord (H L : UInt64) : UInt64 := (H + (L + L) + 720) <<< 52
@[inline] def radius (H L : UInt64) : Float := Float.ofBits (radiusWord H L)
abbrev radiusExp (H L : UInt64) : Int := (H.toNat : Int) + 2 * (L.toNat : Int) - 303

private theorem p2_pos (e : Int) : 0 < p2 e :=
  FloatLib.Floats.Formats.Flocq.bpow.pos _ _

private theorem p2_mono {a b : Int} (h : a ≤ b) : p2 a ≤ p2 b :=
  (FloatLib.Floats.Formats.Flocq.bpow_le_bpow_iff FloatLib.Numerics.binaryRadix a b).2 h

private theorem p2_add (a b : Int) : p2 (a + b) = p2 a * p2 b :=
  FloatLib.Floats.Formats.Flocq.bpow.add_exp _ _ _

private theorem p2_nat (n : Nat) : p2 (n : Int) = ((2 ^ n : Nat) : Real) := by
  simp [p2, FloatLib.Floats.Formats.Flocq.bpow,
    FloatLib.Numerics.binaryRadix, FloatLib.Numerics.Radix.toReal]

private theorem native_finite_eq (x : Float) : Model.isFinite (native x) = x.isFinite := by
  rw [← Model.toDyadic?_isSome_eq_isFinite,
    Model.toDyadic?_ieee_eq_model F64 (by decide), Model.toModel_ofFloatModel]
  change (Model.unpackedToDyadic? x.toModel.unpack).isSome = x.toModel.unpack.isFinite
  cases x.toModel.unpack <;> rfl

private theorem native_ofBits_decode (w : UInt64) {d : FloatLib.Numerics.Dyadic}
    (hd : Model.toDyadic? (raw w) = some d) : native (Float.ofBits w) = raw w := by
  have hc := R2W01c.modelCanonical_of_decode (by decide) (raw w) hd
  change Model.ofFloatModel (Float.Model.ofBits w) = raw w
  rw [Float.Model.ofBits, Model.ofFloatModel_pack]
  change Model.canonicalizeModel (raw w) = raw w
  exact Model.canonicalizeModel_eq_self _ hc

private theorem radiusWord_nat (H L : UInt64)
    (hH : H.toNat ≤ 506) (hL : L.toNat ≤ 30) :
    (radiusWord H L).toNat = (H.toNat + L.toNat + L.toNat + 720) * 4503599627370496 := by
  have hLL : (L + L).toNat = L.toNat + L.toNat := by
    rw [UInt64.toNat_add]
    change (L.toNat + L.toNat) % 18446744073709551616 = _
    omega
  have hE : (H + (L + L) + 720).toNat = H.toNat + L.toNat + L.toNat + 720 := by
    rw [UInt64.toNat_add, UInt64.toNat_add, hLL]
    change ((H.toNat + (L.toNat + L.toNat)) % 18446744073709551616 + 720) %
      18446744073709551616 = _
    omega
  rw [radiusWord, UInt64.toNat_shiftLeft, hE]
  change ((H.toNat + L.toNat + L.toNat + 720) <<< 52) %
    18446744073709551616 = _
  rw [Nat.shiftLeft_eq]
  omega

private theorem raw_power_fields (w : UInt64) (E : Nat)
    (hE : E < 2047) (hw : w.toNat = E * 4503599627370496) :
    raw w = Model.ofFields F64 false E 0 := by
  have hs : Model.signBit (raw w) = false := by
    rw [Model.signBit_eq_msb, BitVec.msb_eq_decide]
    change decide (9223372036854775808 ≤ w.toNat) = false
    apply Bool.eq_iff_iff.mpr
    simp only [decide_eq_true_eq, Bool.false_eq_true]
    omega
  have he : Model.expField (raw w) = E := by
    unfold Model.expField
    change ((w.toBitVec >>> 52) &&& (BitVec.ofNat 64 2047)).toNat = E
    rw [BitVec.toNat_and, BitVec.toNat_ushiftRight]
    change (w.toNat >>> 52) &&& (2 ^ 11 - 1) = E
    rw [Nat.and_two_pow_sub_one_eq_mod, Nat.shiftRight_eq_div_pow, hw]
    omega
  have hf : Model.fracField (raw w) = 0 := by
    unfold Model.fracField
    change (w.toBitVec &&& (BitVec.ofNat 64 4503599627370495)).toNat = 0
    rw [BitVec.toNat_and]
    change w.toNat &&& (2 ^ 52 - 1) = 0
    rw [Nat.and_two_pow_sub_one_eq_mod, hw]
    omega
  rw [← hs, ← he, ← hf]
  exact (Model.ofFields_signBit_expField_fracField (raw w)).symm

private theorem radius_decode (H L : UInt64)
    (hH : H.toNat ≤ 506) (hL : L.toNat ≤ 30) :
    Model.toDyadic? (raw (radiusWord H L)) =
      some ⟨false, 4503599627370496,
        ((H.toNat + L.toNat + L.toNat + 720 : Nat) : Int) - 1023 - 52⟩ := by
  rw [raw_power_fields (radiusWord H L) (H.toNat + L.toNat + L.toNat + 720)
    (by omega) (radiusWord_nat H L hH hL)]
  exact Model.toDyadic?_ofFields_normal F64 false
    (H.toNat + L.toNat + L.toNat + 720) 0 (by omega) (by omega) (by decide)

/-- The actual UInt64 additions/shift and Float.ofBits radius are finite,
positive, and denote the prescribed power of two. -/
theorem radius_finite_value (H L : UInt64)
    (hH : H.toNat ≤ 506) (hL : L.toNat ≤ 30) :
    (radius H L).isFinite = true ∧
      rval (radius H L) = p2 (radiusExp H L) ∧ 0 < rval (radius H L) := by
  have hd := radius_decode H L hH hL
  have hn : native (radius H L) = raw (radiusWord H L) := native_ofBits_decode _ hd
  have hfin : (radius H L).isFinite = true := by
    rw [← native_finite_eq, hn]
    exact Model.isFinite_eq_true_of_toDyadic?_some hd
  have hv : rval (radius H L) = p2 (radiusExp H L) := by
    unfold rval
    rw [hn, Model.toReal_eq, hd]
    simp only [Model.Dyadic.toReal_eq_signedSignificand,
      FloatLib.Numerics.Dyadic.signedSignificand, Bool.false_eq_true, ite_false,
      Int.cast_natCast]
    change (4503599627370496 : Real) *
      p2 (((H.toNat + L.toNat + L.toNat + 720 : Nat) : Int) - 1023 - 52) = _
    have h52 : p2 52 = (4503599627370496 : Real) := by simpa using p2_nat 52
    rw [← h52, ← p2_add]
    congr 1
    unfold radiusExp
    push_cast
    omega
  refine ⟨hfin, hv, ?_⟩
  rw [hv]
  exact p2_pos _

private theorem native_add (x y : Float) (hx : x.isFinite = true) (hy : y.isFinite = true) :
    native (x + y) = Model.add (native x) (native y) := by
  change Model.ofFloatModel (Float.Model.add x.toModel y.toModel) = _
  rw [Float.Model.add, Model.ofFloatModel_pack]
  have h := Model.add_eq_ofModel_add_of_isFinite (fmt := F64)
    (by decide) (Model.ofFloatModel x.toModel) (Model.ofFloatModel y.toModel)
    (by simpa only [Model.toModel_ofFloatModel, Float.isFinite, Float.Model.isFinite] using hx)
    (by simpa only [Model.toModel_ofFloatModel, Float.isFinite, Float.Model.isFinite] using hy)
  rw [Model.toModel_ofFloatModel, Model.toModel_ofFloatModel] at h
  exact h.symm

private theorem native_sub (x y : Float) (hx : x.isFinite = true) (hy : y.isFinite = true) :
    native (x - y) = Model.sub (native x) (native y) := by
  change Model.ofFloatModel (Float.Model.sub x.toModel y.toModel) = _
  rw [Float.Model.sub, Model.ofFloatModel_pack]
  have h := Model.sub_eq_ofModel_sub_of_isFinite (fmt := F64)
    (by decide) (Model.ofFloatModel x.toModel) (Model.ofFloatModel y.toModel)
    (by simpa only [Model.toModel_ofFloatModel, Float.isFinite, Float.Model.isFinite] using hx)
    (by simpa only [Model.toModel_ofFloatModel, Float.isFinite, Float.Model.isFinite] using hy)
  rw [Model.toModel_ofFloatModel, Model.toModel_ofFloatModel] at h
  exact h.symm

private theorem max_finite_large : p2 287 ≤ Model.toReal (Model.posMaxFinite F64) := by
  change p2 287 ≤ Model.toReal (Model.ofFields F64 false 2046 4503599627370495)
  rw [Model.toReal_ofFields_normal F64 false 2046 4503599627370495
    (by decide) (by decide) (by decide)]
  change p2 287 ≤ (1 : Real) * 9007199254740991 * p2 971
  rw [one_mul]
  have hpow : p2 287 ≤ p2 971 := p2_mono (by decide)
  have hp := p2_pos 971
  nlinarith

/-- Actual native subtraction/addition endpoints are finite and equal the
respective RNE64 values. Their finiteness is derived, not a premise. -/
theorem native_endpoints_finite_real (s : Float) (H L : UInt64)
    (hH : H.toNat ≤ 506) (hL : L.toNat ≤ 30)
    (hs : s.isFinite = true) (hsize : |rval s| ≤ p2 286) :
    (s - radius H L).isFinite = true ∧
      (s + radius H L).isFinite = true ∧
      rval (s - radius H L) = Model.roundAt F64 (rval s - p2 (radiusExp H L)) ∧
      rval (s + radius H L) = Model.roundAt F64 (rval s + p2 (radiusExp H L)) := by
  obtain ⟨hr, hrv, hrpos⟩ := radius_finite_value H L hH hL
  have he : radiusExp H L ≤ 263 := by unfold radiusExp; omega
  have hsmall : |rval (radius H L)| ≤ p2 286 := by
    rw [abs_of_pos hrpos, hrv]
    exact (p2_mono he).trans (p2_mono (by decide : (263 : Int) ≤ 286))
  have hsum : p2 286 + p2 286 = p2 287 := by
    rw [show (287 : Int) = 286 + 1 by decide, p2_add]
    have h1 : p2 1 = 2 := by simpa using p2_nat 1
    rw [h1]
    ring
  have hbound : |rval s| + |rval (radius H L)| ≤ Model.toReal (Model.posMaxFinite F64) :=
    ((add_le_add hsize hsmall).trans_eq hsum).trans max_finite_large
  have hms : Model.isFinite (native s) = true := by rw [native_finite_eq, hs]
  have hmr : Model.isFinite (native (radius H L)) = true := by rw [native_finite_eq, hr]
  have hsub := Model.isFinite_sub_of_abs_add_le_posMaxFinite
    (native s) (native (radius H L)) (by decide) hms hmr hbound
  have hadd := Model.isFinite_add_of_abs_add_le_posMaxFinite
    (native s) (native (radius H L)) (by decide) hms hmr hbound
  refine ⟨?_, ?_, ?_, ?_⟩
  · rw [← native_finite_eq, native_sub s (radius H L) hs hr]
    exact hsub
  · rw [← native_finite_eq, native_add s (radius H L) hs hr]
    exact hadd
  · unfold rval
    rw [native_sub s (radius H L) hs hr,
      Model.toReal_sub_eq_roundAt _ _ (by decide) hms hmr hsub]
    change Model.roundAt F64 (rval s - rval (radius H L)) = _
    rw [hrv]
  · unfold rval
    rw [native_add s (radius H L) hs hr,
      Model.toReal_add_eq_roundAt _ _ (by decide) hms hmr hadd]
    change Model.roundAt F64 (rval s + rval (radius H L)) = _
    rw [hrv]

end Submission.R24RadiusEndpoints
