import ContractExact

/- R25: the actual portable UInt64 XOR key, not Float.lt or ExactValue.totalOrder.
   Proof probe only until the pinned runner accepts this exact source. -/
namespace Submission.R25OrderKey
open FloatLib.Floats FloatLib.Floats.Formats.BinaryInterchange

abbrev F64 := FloatFormat.binary64
abbrev raw (w : UInt64) : Model F64 := Model.ofBits w.toBitVec
abbrev native (x : Float) : Model F64 := Model.ofFloatModel x.toModel
noncomputable abbrev value (w : UInt64) : Real := Model.toReal (raw w)
noncomputable abbrev nativeValue (x : Float) : Real := Model.toReal (native x)
def negative (w : UInt64) : Bool := decide (9223372036854775808 ≤ w.toNat)
def magnitude (w : UInt64) : Nat := w.toNat % 9223372036854775808
def exponent (w : UInt64) : Nat := w.toNat / 4503599627370496 % 2048
def fraction (w : UInt64) : Nat := w.toNat % 4503599627370496

@[inline] def finite64 (word : UInt64) : Bool :=
  word &&& 0x7ff0000000000000 != 0x7ff0000000000000
@[inline] def orderKey (word : UInt64) : UInt64 :=
  if word &&& 0x8000000000000000 == 0 then word ^^^ 0x8000000000000000
  else word ^^^ 0xffffffffffffffff

theorem raw_sign (w : UInt64) : Model.signBit (raw w) = negative w := by
  rw [Model.signBit_eq_msb]
  exact BitVec.msb_eq_decide w.toBitVec

theorem raw_exp (w : UInt64) : Model.expField (raw w) = exponent w := by
  unfold Model.expField
  change ((w.toBitVec >>> 52) &&& (BitVec.ofNat 64 2047)).toNat = _
  rw [BitVec.toNat_and, BitVec.toNat_ushiftRight]
  change (w.toNat >>> 52) &&& (2 ^ 11 - 1) = w.toNat / 4503599627370496 % 2 ^ 11
  rw [Nat.and_two_pow_sub_one_eq_mod, Nat.shiftRight_eq_div_pow]

theorem raw_frac (w : UInt64) : Model.fracField (raw w) = fraction w := by
  unfold Model.fracField
  change (w.toBitVec &&& (BitVec.ofNat 64 4503599627370495)).toNat = _
  rw [BitVec.toNat_and]
  exact Nat.and_two_pow_sub_one_eq_mod w.toNat 52

theorem raw_fields (w : UInt64) :
    raw w = Model.ofFields F64 (negative w) (exponent w) (fraction w) := by
  rw [← raw_sign, ← raw_exp, ← raw_frac]
  exact (Model.ofFields_signBit_expField_fracField (raw w)).symm

theorem field_bounds (w : UInt64) :
    exponent w < 2048 ∧ fraction w < 4503599627370496 ∧
    magnitude w < 9223372036854775808 := by
  exact ⟨Nat.mod_lt _ (by decide), Nat.mod_lt _ (by decide), Nat.mod_lt _ (by decide)⟩

theorem magnitude_fields (w : UInt64) :
    magnitude w = exponent w * 4503599627370496 + fraction w := by
  unfold magnitude exponent fraction
  omega

theorem magnitude_div (w : UInt64) :
    magnitude w / 4503599627370496 = exponent w := by
  rw [magnitude_fields]
  have hf := (field_bounds w).2.1
  omega

theorem magnitude_mod (w : UInt64) :
    magnitude w % 4503599627370496 = fraction w := by
  rw [magnitude_fields]
  have hf := (field_bounds w).2.1
  omega

private theorem signMask_nat (w : UInt64) :
    (w &&& 0x8000000000000000).toNat =
      (w.toNat / 9223372036854775808) * 9223372036854775808 := by
  rw [UInt64.toNat_and]
  change w.toNat &&& 9223372036854775808 = _
  have hb := w.toNat_lt_size
  change w.toNat < 18446744073709551616 at hb
  have hd := Nat.and_div_two_pow (a := w.toNat) (b := 9223372036854775808) (n := 63)
  have hm := Nat.and_mod_two_pow (a := w.toNat) (b := 9223372036854775808) (n := 63)
  norm_num only [show (2 ^ 63 : Nat) = 9223372036854775808 by decide,
    Nat.div_self, Nat.mod_self, Nat.and_zero] at hd hm
  have hs : w.toNat / 9223372036854775808 = 0 ∨
      w.toNat / 9223372036854775808 = 1 := by omega
  rcases hs with hs | hs <;> simp only [hs] at hd <;> norm_num at hd <;> omega

private theorem expMask_nat (w : UInt64) :
    (w &&& 0x7ff0000000000000).toNat = exponent w * 4503599627370496 := by
  rw [UInt64.toNat_and]
  change w.toNat &&& 9218868437227405312 = _
  have hd := Nat.and_div_two_pow (a := w.toNat) (b := 9218868437227405312) (n := 52)
  have hm := Nat.and_mod_two_pow (a := w.toNat) (b := 9218868437227405312) (n := 52)
  norm_num only [show (2 ^ 52 : Nat) = 4503599627370496 by decide] at hd hm
  change (w.toNat &&& 9218868437227405312) / 4503599627370496 =
    (w.toNat / 4503599627370496) &&& (2 ^ 11 - 1) at hd
  rw [Nat.and_two_pow_sub_one_eq_mod] at hd
  norm_num at hm
  change (w.toNat &&& 9218868437227405312) / 4503599627370496 = exponent w at hd
  omega

theorem finite64_iff_exp (w : UInt64) :
    finite64 w = true ↔ exponent w < 2047 := by
  have he := (field_bounds w).1
  change (w &&& 0x7ff0000000000000 != 0x7ff0000000000000) = true ↔ _
  rw [bne_iff_ne]
  constructor
  · intro hn
    have hnNat : (w &&& 0x7ff0000000000000).toNat ≠ 9218868437227405312 := by
      intro heq
      apply hn
      apply UInt64.toNat_inj.mp
      exact heq
    rw [expMask_nat] at hnNat
    omega
  · intro hexp heq
    have hnNat := congrArg UInt64.toNat heq
    rw [expMask_nat] at hnNat
    change exponent w * 4503599627370496 = 9218868437227405312 at hnNat
    omega

theorem finite64_model (w : UInt64) (h : finite64 w = true) :
    Model.isFinite (raw w) = true := by
  rw [raw_fields]
  exact Model.isFinite_ofFields_ieee F64 (by decide) _ _ _
    ((finite64_iff_exp w).mp h)

private theorem xor_sign_nat (w : UInt64) (hw : w.toNat < 9223372036854775808) :
    (w ^^^ 0x8000000000000000).toNat = w.toNat + 9223372036854775808 := by
  rw [UInt64.toNat_xor]
  change w.toNat ^^^ 9223372036854775808 = _
  have hd := Nat.xor_div_two_pow (a := w.toNat) (b := 9223372036854775808) (n := 63)
  have hm := Nat.xor_mod_two_pow (a := w.toNat) (b := 9223372036854775808) (n := 63)
  have hz : w.toNat / 9223372036854775808 = 0 := by omega
  norm_num only [show (2 ^ 63 : Nat) = 9223372036854775808 by decide,
    Nat.div_self, Nat.mod_self, hz, Nat.zero_xor, Nat.xor_zero] at hd hm
  rw [Nat.mod_eq_of_lt hw] at hm
  omega

theorem orderKey_nat (w : UInt64) :
    (orderKey w).toNat =
      if negative w then 9223372036854775807 - magnitude w
      else 9223372036854775808 + magnitude w := by
  have hb := w.toNat_lt_size
  change w.toNat < 18446744073709551616 at hb
  by_cases hs : w.toNat < 9223372036854775808
  · have hm : w &&& 0x8000000000000000 = 0 := by
      apply UInt64.toNat_inj.mp
      rw [signMask_nat]
      change w.toNat / 9223372036854775808 * 9223372036854775808 = 0
      omega
    have hn : negative w = false := by simp [negative]; omega
    simp only [orderKey, hm, beq_self_eq_true, ite_true, hn, Bool.false_eq_true,
      ite_false]
    rw [xor_sign_nat w hs]
    unfold magnitude
    rw [Nat.mod_eq_of_lt hs]
    omega
  · have hm : w &&& 0x8000000000000000 ≠ 0 := by
      intro hm
      have h := congrArg UInt64.toNat hm
      rw [signMask_nat] at h
      change w.toNat / 9223372036854775808 * 9223372036854775808 = 0 at h
      omega
    have hn : negative w = true := by simp [negative]; omega
    simp only [orderKey, beq_eq_false_iff_ne.mpr hm, Bool.false_eq_true, ite_false,
      hn, ite_true]
    change (w ^^^ (-1 : UInt64)).toNat = _
    rw [UInt64.xor_neg_one, UInt64.toNat_not]
    change 18446744073709551615 - w.toNat = _
    unfold magnitude
    omega

/-- Actual XOR-key strict order has one signed-zero tie; magnitude isolates it. -/
theorem orderKey_lt_cases (x y : UInt64) (h : orderKey x < orderKey y) :
    (negative x = false ∧ negative y = false ∧ magnitude x < magnitude y) ∨
    (negative x = true ∧ negative y = true ∧ magnitude y < magnitude x) ∨
    (negative x = true ∧ negative y = false) := by
  rw [UInt64.lt_iff_toNat_lt, orderKey_nat, orderKey_nat] at h
  have hx := (field_bounds x).2.2
  have hy := (field_bounds y).2.2
  cases hsx : negative x <;> cases hsy : negative y <;>
    simp [hsx, hsy] at h ⊢ <;> omega


end Submission.R25OrderKey

namespace Submission.R24PortableF64
@[inline] def finite64 (word : UInt64) : Bool :=
  word &&& 0x7ff0000000000000 != 0x7ff0000000000000

/-- Arbitrary midpoint-up proposal, deliberately not a proved RN32 conversion. -/
@[inline] def proposal (word : UInt64) : UInt32 :=
  let magnitude :=
    (((((word &&& 0x7fffffffffffffff) + 0x10000000) >>> 29).toUInt32) - 0xc0000000) &&& 0x7fffffff
  ((word >>> 32).toUInt32 &&& 0x80000000) ||| magnitude

@[inline] def orderKey (word : UInt64) : UInt64 :=
  if word &&& 0x8000000000000000 == 0 then word ^^^ 0x8000000000000000
  else word ^^^ 0xffffffffffffffff

/-- Strict midpoint word checker, including the minimum-normal lower spacing. -/
@[inline] def certify (sum radius : Float) (sumWord : UInt64) (guess : UInt32) : Bool :=
  let magnitude := guess &&& 0x7fffffff
  let e := (magnitude >>> 23) &&& 255
  if e == 0 || e == 255 then false
  else
    let lowerEndpoint := (sum - radius).toBits
    let upperEndpoint := (sum + radius).toBits
    if !(finite64 sumWord && (finite64 lowerEndpoint && finite64 upperEndpoint)) then false
    else
      let base := ((e.toUInt64 + 896) <<< 52) ||| ((magnitude &&& 0x7fffff).toUInt64 <<< 29)
      let lowerDelta : UInt64 := if magnitude == 0x00800000 then 0x20000000 else 0x10000000
      let below := base - lowerDelta
      let above := base + 0x10000000
      let negative := guess &&& 0x80000000 != 0
      let lower := if negative then above ||| 0x8000000000000000 else below
      let upper := if negative then below ||| 0x8000000000000000 else above
      decide (orderKey lower < orderKey lowerEndpoint) &&
        decide (orderKey upperEndpoint < orderKey upper)


end Submission.R24PortableF64

namespace Submission.R27EndpointCore
open FloatLib.Floats FloatLib.Floats.Formats.BinaryInterchange
open Submission.R25OrderKey

theorem actual_finite_guards (s r : Float) (q : UInt32)
    (hacc : Submission.R24PortableF64.certify s r s.toBits q = true) :
    finite64 s.toBits = true ∧ finite64 (s - r).toBits = true ∧
      finite64 (s + r).toBits = true := by
  unfold Submission.R24PortableF64.certify at hacc
  split at hacc
  · simp at hacc
  next he =>
    dsimp only at hacc
    split at hacc
    · simp at hacc
    next hf =>
      have hh : Submission.R24PortableF64.finite64 s.toBits = true ∧
          Submission.R24PortableF64.finite64 (s - r).toBits = true ∧
          Submission.R24PortableF64.finite64 (s + r).toBits = true := by
        cases hs : Submission.R24PortableF64.finite64 s.toBits <;>
          cases hl : Submission.R24PortableF64.finite64 (s - r).toBits <;>
          cases hu : Submission.R24PortableF64.finite64 (s + r).toBits <;> simp_all
      exact hh

private theorem native_finite_eq (x : Float) :
    Model.isFinite (native x) = x.isFinite := by
  rw [← Model.toDyadic?_isSome_eq_isFinite,
    Model.toDyadic?_ieee_eq_model F64 (by decide), Model.toModel_ofFloatModel]
  change (Model.unpackedToDyadic? x.toModel.unpack).isSome = x.toModel.unpack.isFinite
  cases x.toModel.unpack <;> rfl

private theorem native_add (x y : Float) (hx : x.isFinite = true)
    (hy : y.isFinite = true) :
    native (x + y) = Model.add (native x) (native y) := by
  change Model.ofFloatModel (Float.Model.add x.toModel y.toModel) = _
  rw [Float.Model.add, Model.ofFloatModel_pack]
  have h := Model.add_eq_ofModel_add_of_isFinite (fmt := F64)
    (by decide) (Model.ofFloatModel x.toModel) (Model.ofFloatModel y.toModel)
    (by simpa only [Model.toModel_ofFloatModel, Float.isFinite, Float.Model.isFinite] using hx)
    (by simpa only [Model.toModel_ofFloatModel, Float.isFinite, Float.Model.isFinite] using hy)
  rw [Model.toModel_ofFloatModel, Model.toModel_ofFloatModel] at h
  exact h.symm

private theorem native_sub (x y : Float) (hx : x.isFinite = true)
    (hy : y.isFinite = true) :
    native (x - y) = Model.sub (native x) (native y) := by
  change Model.ofFloatModel (Float.Model.sub x.toModel y.toModel) = _
  rw [Float.Model.sub, Model.ofFloatModel_pack]
  have h := Model.sub_eq_ofModel_sub_of_isFinite (fmt := F64)
    (by decide) (Model.ofFloatModel x.toModel) (Model.ofFloatModel y.toModel)
    (by simpa only [Model.toModel_ofFloatModel, Float.isFinite, Float.Model.isFinite] using hx)
    (by simpa only [Model.toModel_ofFloatModel, Float.isFinite, Float.Model.isFinite] using hy)
  rw [Model.toModel_ofFloatModel, Model.toModel_ofFloatModel] at h
  exact h.symm

theorem accepted_endpoint_equations (s r : Float) (q : UInt32)
    (hr : r.isFinite = true)
    (hacc : Submission.R24PortableF64.certify s r s.toBits q = true) :
    nativeValue (s - r) = Model.roundAt F64 (nativeValue s - nativeValue r) ∧
      nativeValue (s + r) = Model.roundAt F64 (nativeValue s + nativeValue r) := by
  obtain ⟨hsf, hlof, hhif⟩ := actual_finite_guards s r q hacc
  have hms : Model.isFinite (native s) = true := finite64_model s.toBits hsf
  have hmlo : Model.isFinite (native (s - r)) = true :=
    finite64_model (s - r).toBits hlof
  have hmhi : Model.isFinite (native (s + r)) = true :=
    finite64_model (s + r).toBits hhif
  have hs : s.isFinite = true := by rw [← native_finite_eq]; exact hms
  have hmr : Model.isFinite (native r) = true := by rw [native_finite_eq, hr]
  have hsub : Model.isFinite (Model.sub (native s) (native r)) = true := by
    rw [← native_sub s r hs hr]
    exact hmlo
  have hadd : Model.isFinite (Model.add (native s) (native r)) = true := by
    rw [← native_add s r hs hr]
    exact hmhi
  constructor
  · unfold nativeValue
    rw [native_sub s r hs hr]
    exact Model.toReal_sub_eq_roundAt _ _ (by decide) hms hmr hsub
  · unfold nativeValue
    rw [native_add s r hs hr]
    exact Model.toReal_add_eq_roundAt _ _ (by decide) hms hmr hadd


end Submission.R27EndpointCore
