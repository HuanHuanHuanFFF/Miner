/- R24 portable proof of actual Float.lt on finite binary64 values.
   Canonical numerical exponents come from decoded native values, not from
   an assumption about arbitrary UnpackedFloat tuples or NaN canonicality.
   No runtime Model.compare, totalOrder, raw-key algorithm or opaque cast. -/
namespace Submission.R24NativeCompare

open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange
open Float.Model.UnpackedFloat

abbrev F64 := FloatFormat.binary64
abbrev view (x : Float) : Model F64 := Model.ofFloatModel x.toModel
noncomputable abbrev value (x : Float) : Real := Model.toReal (view x)
noncomputable abbrev scale (m : Nat) (e : Int) : Real :=
  (m : Real) * FloatLib.Floats.Formats.Flocq.bpow FloatLib.Numerics.binaryRadix e

private theorem scale_pos (m : Nat) (e : Int) (hm : 0 < m) : 0 < scale m e :=
  mul_pos (by exact_mod_cast hm)
    (FloatLib.Floats.Formats.Flocq.bpow.pos FloatLib.Numerics.binaryRadix e)

private theorem value_eq_unpack (x : Float) :
    value x = Model.unpackedToReal x.toModel.unpack := by
  simpa only [value, view, Model.toModel_ofFloatModel] using
    Model.toReal_eq_unpackedToReal_toModel (fmt := F64) (by decide) (view x)

private theorem decode_of_finite (x : Float) (s : Sign) (m : Nat) (e : Int)
    (hm : 0 < m) (h : x.toModel.unpack = .finite s m e hm) :
    Model.toDyadic? (view x) = some ⟨Model.modelSignBit s, m, e⟩ := by
  rw [Model.toDyadic?_ieee_eq_model F64 (by decide)]
  change Model.unpackedToDyadic? x.toModel.unpack = _
  rw [h]
  rfl

private theorem value_finite (x : Float) (s : Sign) (m : Nat) (e : Int)
    (hm : 0 < m) (h : x.toModel.unpack = .finite s m e hm) :
    value x = if Model.modelSignBit s then -scale m e else scale m e := by
  rw [value_eq_unpack, h, Model.unpackedToReal_finite]
  cases s <;> simp [scale, Model.modelSignBit]

private theorem abs_value_finite (x : Float) (s : Sign) (m : Nat) (e : Int)
    (hm : 0 < m) (h : x.toModel.unpack = .finite s m e hm) :
    |value x| = scale m e := by
  rw [value_finite x s m e hm h]
  cases s <;> simp [Model.modelSignBit, abs_of_pos (scale_pos m e hm)]

private theorem canonical_exponent (x : Float) (s : Sign) (m : Nat) (e : Int)
    (hm : 0 < m) (h : x.toModel.unpack = .finite s m e hm) :
    FloatLib.Floats.Formats.Flocq.cexp FloatLib.Numerics.binaryRadix
      (Model.fexpOf F64) (value x) = e := by
  have hd := decode_of_finite x s m e hm h
  have hc := Model.cexp_toDyadic? hd (show m ≠ 0 from hm.ne')
  have hv : value x =
      (FloatLib.Numerics.Dyadic.mk (Model.modelSignBit s) m e).toReal := by
    simp only [value, Model.toReal_eq, hd]
  rw [← hv] at hc
  exact hc

private theorem exponent_lt_scale_lt (x y : Float)
    (sx sy : Sign) (mx my : Nat) (ex ey : Int) (hmx : 0 < mx) (hmy : 0 < my)
    (hx : x.toModel.unpack = .finite sx mx ex hmx)
    (hy : y.toModel.unpack = .finite sy my ey hmy) (he : ex < ey) :
    scale mx ex < scale my ey := by
  letI : FloatLib.Floats.Formats.Flocq.MonotoneExp (Model.fexpOf F64) :=
    FloatLib.Floats.Formats.Flocq.fltMonotoneExp
      F64.minSubnormalExponent (F64.fracWidth + 1)
  by_contra hnot
  have hreverse : |value y| ≤ |value x| := by
    rw [abs_value_finite y sy my ey hmy hy, abs_value_finite x sx mx ex hmx hx]
    exact le_of_not_gt hnot
  have hy0 : value y ≠ 0 := by
    apply abs_pos.mp
    rw [abs_value_finite y sy my ey hmy hy]
    exact scale_pos my ey hmy
  have hc := FloatLib.Floats.Formats.Flocq.cexp_mono_abs
    FloatLib.Numerics.binaryRadix (fexp := Model.fexpOf F64) hy0 hreverse
  rw [canonical_exponent y sy my ey hmy hy,
    canonical_exponent x sx mx ex hmx hx] at hc
  omega

private theorem lex_compare_eq (x y : Float)
    (sx sy : Sign) (mx my : Nat) (ex ey : Int) (hmx : 0 < mx) (hmy : 0 < my)
    (hx : x.toModel.unpack = .finite sx mx ex hmx)
    (hy : y.toModel.unpack = .finite sy my ey hmy) :
    (compare ex ey).then (compare mx my) = compare (scale mx ex) (scale my ey) := by
  rcases lt_trichotomy ex ey with he | he | he
  · have hE : compare ex ey = .lt := compare_lt_iff_lt.mpr he
    have hR : compare (scale mx ex) (scale my ey) = .lt :=
      compare_lt_iff_lt.mpr (exponent_lt_scale_lt x y sx sy mx my ex ey hmx hmy hx hy he)
    simp [hE, hR, Ordering.then]
  · subst ey
    rcases lt_trichotomy mx my with hm | hm | hm
    · have hM : compare mx my = .lt := compare_lt_iff_lt.mpr hm
      have hscaled : scale mx ex < scale my ex :=
        mul_lt_mul_of_pos_right (by exact_mod_cast hm)
          (FloatLib.Floats.Formats.Flocq.bpow.pos FloatLib.Numerics.binaryRadix ex)
      have hR : compare (scale mx ex) (scale my ex) = .lt := compare_lt_iff_lt.mpr hscaled
      simp [hM, hR, Ordering.then]
    · subst my
      simp [Ordering.then]
    · have hM : compare mx my = .gt := compare_gt_iff_gt.mpr hm
      have hscaled : scale my ex < scale mx ex :=
        mul_lt_mul_of_pos_right (by exact_mod_cast hm)
          (FloatLib.Floats.Formats.Flocq.bpow.pos FloatLib.Numerics.binaryRadix ex)
      have hR : compare (scale mx ex) (scale my ex) = .gt := compare_gt_iff_gt.mpr hscaled
      simp [hM, hR, Ordering.then]
  · have hE : compare ex ey = .gt := compare_gt_iff_gt.mpr he
    have hR : compare (scale mx ex) (scale my ey) = .gt :=
      compare_gt_iff_gt.mpr (exponent_lt_scale_lt y x sy sx my mx ey ex hmy hmx hy hx he)
    simp [hE, hR, Ordering.then]

private theorem swapped_lt (o : Ordering) : o.swap = .lt ↔ o = .gt := by
  cases o <;> decide

private theorem native_lt_unpacked (x y : Float) :
    Float.lt x y = true ↔ x.toModel.unpack.compare y.toModel.unpack = some .lt := by
  change decide (x.toModel < y.toModel) = true ↔ _
  rw [decide_eq_true_eq]
  change (x.toModel.unpack.compare y.toModel.unpack == some .lt) = true ↔ _
  exact beq_iff_eq

/-- Actual native Float.lt is exactly strict real order on finite inputs.
Signed zeros compare equal; all finite normals/subnormals are included. -/
theorem native_lt_iff_real (x y : Float)
    (hx : x.isFinite = true) (hy : y.isFinite = true) :
    Float.lt x y = true ↔ value x < value y := by
  change x.toModel.unpack.isFinite = true at hx
  change y.toModel.unpack.isFinite = true at hy
  rw [native_lt_unpacked, value_eq_unpack x, value_eq_unpack y]
  cases hxv : x.toModel.unpack <;> cases hyv : y.toModel.unpack <;>
    simp only [hxv, hyv, Float.Model.UnpackedFloat.isFinite, Bool.false_eq_true] at hx hy
  case zero.zero sx sy =>
    simp [Float.Model.UnpackedFloat.compare, Model.unpackedToReal_zero]
  case zero.finite sx sy my ey hmy =>
    have hp : 0 < (my : Real) *
        FloatLib.Floats.Formats.Flocq.bpow FloatLib.Numerics.binaryRadix ey := scale_pos my ey hmy
    cases sy <;> simp [Float.Model.UnpackedFloat.compare, Model.unpackedToReal_zero,
      Model.unpackedToReal_finite, Model.modelSignBit, hp, hp.le, not_lt_of_ge hp.le]
  case finite.zero sx mx ex hmx sy =>
    have hp : 0 < (mx : Real) *
        FloatLib.Floats.Formats.Flocq.bpow FloatLib.Numerics.binaryRadix ex := scale_pos mx ex hmx
    cases sx <;> simp [Float.Model.UnpackedFloat.compare, Model.unpackedToReal_zero,
      Model.unpackedToReal_finite, Model.modelSignBit, hp, hp.le, not_lt_of_ge hp.le]
  case finite.finite sx mx ex hmx sy my ey hmy =>
    have hlex := lex_compare_eq x y sx sy mx my ex ey hmx hmy hxv hyv
    have hp : 0 < (mx : Real) *
        FloatLib.Floats.Formats.Flocq.bpow FloatLib.Numerics.binaryRadix ex := scale_pos mx ex hmx
    have hq : 0 < (my : Real) *
        FloatLib.Floats.Formats.Flocq.bpow FloatLib.Numerics.binaryRadix ey := scale_pos my ey hmy
    cases sx with
    | positive =>
      cases sy with
      | positive =>
        simp [Float.Model.UnpackedFloat.compare, Model.unpackedToReal_finite,
          Model.modelSignBit, hlex, compare_lt_iff_lt, scale]
      | negative =>
        have hnot : ¬ (mx : Real) *
            FloatLib.Floats.Formats.Flocq.bpow FloatLib.Numerics.binaryRadix ex <
            -((my : Real) * FloatLib.Floats.Formats.Flocq.bpow FloatLib.Numerics.binaryRadix ey) := by
          linarith
        simp [Float.Model.UnpackedFloat.compare, Model.unpackedToReal_finite,
          Model.modelSignBit, hnot]
    | negative =>
      cases sy with
      | positive =>
        have hlt : -((mx : Real) *
            FloatLib.Floats.Formats.Flocq.bpow FloatLib.Numerics.binaryRadix ex) <
            (my : Real) * FloatLib.Floats.Formats.Flocq.bpow FloatLib.Numerics.binaryRadix ey := by
          linarith
        simp [Float.Model.UnpackedFloat.compare, Model.unpackedToReal_finite,
          Model.modelSignBit, hlt]
      | negative =>
        simp [Float.Model.UnpackedFloat.compare, Model.unpackedToReal_finite,
          Model.modelSignBit, hlex, swapped_lt, compare_gt_iff_gt, scale]

end Submission.R24NativeCompare
