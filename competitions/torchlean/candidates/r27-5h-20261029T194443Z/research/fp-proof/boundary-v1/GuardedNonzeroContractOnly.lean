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

noncomputable def magnitudeReal (m : Nat) : Real :=
  if m / 4503599627370496 = 0 then
    ((m % 4503599627370496 : Nat) : Real) * (2 : Real) ^ (-1074 : Int)
  else
    (4503599627370496 + m % 4503599627370496 : Nat) *
      (2 : Real) ^ ((m / 4503599627370496 : Nat) - (1075 : Int))

private theorem magnitudeReal_nonneg (m : Nat) : 0 ≤ magnitudeReal m := by
  unfold magnitudeReal
  split <;> positivity

private theorem magnitudeReal_zero : magnitudeReal 0 = 0 := by
  simp [magnitudeReal]

private theorem magnitudeReal_lt_same (a b : Nat)
    (he : a / 4503599627370496 = b / 4503599627370496)
    (hf : a % 4503599627370496 < b % 4503599627370496) :
    magnitudeReal a < magnitudeReal b := by
  unfold magnitudeReal
  rw [he]
  split
  · exact mul_lt_mul_of_pos_right (by exact_mod_cast hf) (zpow_pos (by norm_num) _)
  · apply mul_lt_mul_of_pos_right _ (zpow_pos (by norm_num) _)
    exact_mod_cast (Nat.add_lt_add_left hf 4503599627370496)

private theorem pow2_mono {a b : Int} (h : a ≤ b) :
    (2 : Real) ^ a ≤ (2 : Real) ^ b := by
  exact (zpow_le_zpow_iff_right₀ (G₀ := Real) (a := (2 : Real))
    (m := a) (n := b) (by norm_num)).mpr h

private theorem magnitudeReal_lt_exp (a b : Nat)
    (he : a / 4503599627370496 < b / 4503599627370496) :
    magnitudeReal a < magnitudeReal b := by
  have haF : a % 4503599627370496 < 4503599627370496 := Nat.mod_lt _ (by decide)
  have hbF : b % 4503599627370496 < 4503599627370496 := Nat.mod_lt _ (by decide)
  have hb0 : b / 4503599627370496 ≠ 0 := by omega
  unfold magnitudeReal
  rw [if_neg hb0]
  by_cases ha0 : a / 4503599627370496 = 0
  · rw [if_pos ha0]
    have hscale : (2 : Real) ^ (-1074 : Int) ≤
        (2 : Real) ^ ((b / 4503599627370496 : Nat) - (1075 : Int)) := by
      apply pow2_mono
      omega
    calc
      _ < (4503599627370496 : Real) * (2 : Real) ^ (-1074 : Int) :=
        mul_lt_mul_of_pos_right (by exact_mod_cast haF) (zpow_pos (by norm_num) _)
      _ ≤ (4503599627370496 : Real) *
          (2 : Real) ^ ((b / 4503599627370496 : Nat) - (1075 : Int)) :=
        mul_le_mul_of_nonneg_left hscale (by norm_num)
      _ ≤ _ := mul_le_mul_of_nonneg_right (by exact_mod_cast (show 4503599627370496 ≤ 4503599627370496 + b % 4503599627370496 by omega))
        (zpow_nonneg (by norm_num) _)
  · rw [if_neg ha0]
    have hscale : (2 : Real) ^ (((a / 4503599627370496 : Nat) : Int) + 1 - 1075) ≤
        (2 : Real) ^ ((b / 4503599627370496 : Nat) - (1075 : Int)) := by
      apply pow2_mono
      omega
    have hstep :
        (9007199254740992 : Real) *
            (2 : Real) ^ ((a / 4503599627370496 : Nat) - (1075 : Int)) =
          4503599627370496 *
            (2 : Real) ^ (((a / 4503599627370496 : Nat) : Int) + 1 - 1075) := by
      rw [show (((a / 4503599627370496 : Nat) : Int) + 1 - 1075) =
        ((a / 4503599627370496 : Nat) - (1075 : Int)) + 1 by omega]
      rw [zpow_add₀ (by norm_num : (2 : Real) ≠ 0)]
      norm_num
      ring
    calc
      _ < (9007199254740992 : Real) *
            (2 : Real) ^ ((a / 4503599627370496 : Nat) - (1075 : Int)) := by
        apply mul_lt_mul_of_pos_right _ (zpow_pos (by norm_num) _)
        exact_mod_cast (show 4503599627370496 + a % 4503599627370496 < 9007199254740992 by omega)
      _ = _ := hstep
      _ ≤ (4503599627370496 : Real) *
          (2 : Real) ^ ((b / 4503599627370496 : Nat) - (1075 : Int)) :=
        mul_le_mul_of_nonneg_left hscale (by norm_num)
      _ ≤ _ := mul_le_mul_of_nonneg_right (by exact_mod_cast (show 4503599627370496 ≤ 4503599627370496 + b % 4503599627370496 by omega))
        (zpow_nonneg (by norm_num) _)

theorem magnitudeReal_strictMono : StrictMono magnitudeReal := by
  intro a b hab
  rcases lt_or_eq_of_le (Nat.div_le_div_right hab.le) with he | he
  · exact magnitudeReal_lt_exp a b he
  · apply magnitudeReal_lt_same a b he
    omega

theorem magnitudeReal_pos_iff (m : Nat) : 0 < magnitudeReal m ↔ m ≠ 0 := by
  constructor
  · intro h hm
    subst m
    rw [magnitudeReal_zero] at h
    exact (lt_irrefl _ h)
  · intro h
    have hr := magnitudeReal_strictMono (Nat.pos_of_ne_zero h)
    simpa only [magnitudeReal_zero] using hr

/-- Exact raw binary64 decoding, including subnormals and both signed zeros. -/
theorem raw_value (w : UInt64) (hfin : finite64 w = true) :
    value w = if negative w then -magnitudeReal (magnitude w)
      else magnitudeReal (magnitude w) := by
  have he := (field_bounds w).1
  have hf := (field_bounds w).2.1
  have hmodel := finite64_model w hfin
  have hd := Model.toDyadic?_ofFields_of_isFinite F64 (negative w)
    (exponent w) (fraction w) he hf (by simpa only [← raw_fields] using hmodel)
  rw [← raw_fields] at hd
  change Model.toDyadic? (raw w) =
    (if exponent w = 0 then
      if fraction w = 0 then some ⟨negative w, 0, 0⟩
      else some ⟨negative w, fraction w, -1074⟩
    else some ⟨negative w, 4503599627370496 + fraction w,
      (exponent w : Int) - 1023 - 52⟩) at hd
  unfold value
  rw [Model.toReal_eq, hd]
  unfold magnitudeReal
  rw [magnitude_div, magnitude_mod]
  by_cases hE : exponent w = 0 <;> by_cases hF : fraction w = 0 <;>
    cases hs : negative w <;>
    simp [hE, hF, hs, FloatLib.Numerics.Dyadic.toReal,
      FloatLib.Numerics.Dyadic.signedSignificand,
      FloatLib.Floats.Formats.Flocq.bpow, FloatLib.Numerics.binaryRadix,
      FloatLib.Numerics.Radix.toReal, sub_sub, neg_mul] <;> ring

/-- Strict order of the actual integer key transports to strict real order when
both raw words are finite and at least one magnitude is nonzero.
The disjunction is necessary: key(-0) < key(+0), but both denote real zero. -/
theorem orderKey_lt_real (x y : UInt64)
    (hx : finite64 x = true) (hy : finite64 y = true)
    (hnz : magnitude x ≠ 0 ∨ magnitude y ≠ 0)
    (hkey : orderKey x < orderKey y) :
    value x < value y := by
  rw [raw_value x hx, raw_value y hy]
  rcases orderKey_lt_cases x y hkey with ⟨hsx, hsy, hm⟩ | ⟨hsx, hsy, hm⟩ | ⟨hsx, hsy⟩
  · simp only [hsx, hsy, Bool.false_eq_true, ite_false]
    exact magnitudeReal_strictMono hm
  · simp only [hsx, hsy, ite_true]
    exact neg_lt_neg (magnitudeReal_strictMono hm)
  · simp only [hsx, hsy, Bool.false_eq_true, ite_false, ite_true]
    have hp := magnitudeReal_nonneg (magnitude x)
    have hq := magnitudeReal_nonneg (magnitude y)
    rcases hnz with hnz | hnz
    · have := (magnitudeReal_pos_iff (magnitude x)).mpr hnz
      linarith
    · have := (magnitudeReal_pos_iff (magnitude y)).mpr hnz
      linarith

theorem value_toBits (x : Float) : value x.toBits = nativeValue x := rfl

theorem orderKey_toBits_lt_real (x y : Float)
    (hx : finite64 x.toBits = true) (hy : finite64 y.toBits = true)
    (hnz : magnitude x.toBits ≠ 0 ∨ magnitude y.toBits ≠ 0)
    (hkey : orderKey x.toBits < orderKey y.toBits) :
    nativeValue x < nativeValue y := by
  exact orderKey_lt_real _ _ hx hy hnz hkey

/-- An exact finite raw word survives native ofBits; no NaN payload claim. -/
theorem native_ofBits (w : UInt64) (hfin : finite64 w = true) :
    native (Float.ofBits w) = raw w := by
  obtain ⟨d, hd⟩ := Model.exists_toDyadic?_of_isFinite (finite64_model w hfin)
  have hc : Model.IsModelCanonical (raw w) := by
    constructor
    intro he hm
    have hnan : Model.toModel (raw w) = Float.Model.UnpackedFloat.notANumber := by
      simp only [Model.toModel, Float.Model.UnpackedFloat.unpack, he, hm, ite_true, ite_false]
    rw [Model.toDyadic?_ieee_eq_model F64 (by decide), hnan] at hd
    simp [Model.unpackedToDyadic?] at hd
  change Model.ofFloatModel
    (ExecFloat.Binary.toFloat (ExecFloat.Binary.ofBits64 w)).toModel = raw w
  rw [ExecFloat.Binary.toModel_toFloat_eq, Model.ofFloatModel_toFloatModel]
  exact Model.canonicalizeModel_eq_self _ hc

theorem value_ofBits (w : UInt64) (hfin : finite64 w = true) :
    nativeValue (Float.ofBits w) = value w := by
  unfold nativeValue value
  rw [native_ofBits w hfin]

theorem orderKey_native_endpoints (lower upper : UInt64) (a b : Float)
    (hl : finite64 lower = true) (hu : finite64 upper = true)
    (ha : finite64 a.toBits = true) (hb : finite64 b.toBits = true)
    (hlnz : magnitude lower ≠ 0) (hunz : magnitude upper ≠ 0)
    (hlkey : orderKey lower < orderKey a.toBits)
    (hukey : orderKey b.toBits < orderKey upper) :
    value lower < nativeValue a ∧ nativeValue b < value upper :=
  ⟨orderKey_lt_real _ _ hl ha (Or.inl hlnz) hlkey,
    orderKey_lt_real _ _ hb hu (Or.inr hunz) hukey⟩

end Submission.R25OrderKey


/- Exact expression adapter for the R24 PortableF64 checker.
   Append after R25OrderKey; arithmetic behavior is unchanged. -/
namespace Submission.R25Checker
open Submission.R25OrderKey

@[inline] def magnitude32 (q : UInt32) : UInt32 := q &&& 0x7fffffff
@[inline] def eWord (q : UInt32) : UInt32 := (magnitude32 q >>> 23) &&& 255
@[inline] def fWord (q : UInt32) : UInt32 := magnitude32 q &&& 0x7fffff
@[inline] def base (q : UInt32) : UInt64 :=
  ((eWord q).toUInt64 + 896) <<< 52 ||| ((fWord q).toUInt64 <<< 29)
@[inline] def delta (q : UInt32) : UInt64 :=
  if magnitude32 q == 0x00800000 then 0x20000000 else 0x10000000
@[inline] def below (q : UInt32) : UInt64 := base q - delta q
@[inline] def above (q : UInt32) : UInt64 := base q + 0x10000000
@[inline] def negative32 (q : UInt32) : Bool := q &&& 0x80000000 != 0
@[inline] def lowerWord (q : UInt32) : UInt64 :=
  if negative32 q then above q ||| 0x8000000000000000 else below q
@[inline] def upperWord (q : UInt32) : UInt64 :=
  if negative32 q then below q ||| 0x8000000000000000 else above q

@[inline] def certify (sum radius : Float) (sumWord : UInt64) (guess : UInt32) : Bool :=
  if eWord guess == 0 || eWord guess == 255 then false
  else
    let lowerEndpoint := (sum - radius).toBits
    let upperEndpoint := (sum + radius).toBits
    if !(finite64 sumWord && (finite64 lowerEndpoint && finite64 upperEndpoint)) then false
    else
      decide (orderKey (lowerWord guess) < orderKey lowerEndpoint) &&
        decide (orderKey upperEndpoint < orderKey (upperWord guess))

/-- Guards and inequalities are extracted from the actual expression. -/
theorem accepted_components (sum radius : Float) (sumWord : UInt64) (q : UInt32)
    (h : certify sum radius sumWord q = true) :
    eWord q ≠ 0 ∧ eWord q ≠ 255 ∧ finite64 sumWord = true ∧
    finite64 (sum - radius).toBits = true ∧ finite64 (sum + radius).toBits = true ∧
    orderKey (lowerWord q) < orderKey (sum - radius).toBits ∧
    orderKey (sum + radius).toBits < orderKey (upperWord q) := by
  unfold certify at h
  split at h
  · simp at h
  next he =>
    have he' : eWord q ≠ 0 ∧ eWord q ≠ 255 := by
      simpa only [Bool.or_eq_true, beq_iff_eq, not_or] using he
    dsimp only at h
    split at h
    · simp at h
    next hf =>
      have hf' : finite64 sumWord = true ∧
          finite64 (sum - radius).toBits = true ∧
          finite64 (sum + radius).toBits = true := by
        cases hsum : finite64 sumWord <;>
          cases hlo : finite64 (sum - radius).toBits <;>
          cases hhi : finite64 (sum + radius).toBits <;> simp_all
      have hk : orderKey (lowerWord q) < orderKey (sum - radius).toBits ∧
          orderKey (sum + radius).toBits < orderKey (upperWord q) := by
        simpa only [Bool.and_eq_true, decide_eq_true_eq] using h
      exact ⟨he'.1, he'.2, hf'.1, hf'.2.1, hf'.2.2, hk.1, hk.2⟩

private theorem eWord_bound (q : UInt32) : (eWord q).toNat < 256 := by
  rw [eWord, UInt32.toNat_and]
  change (magnitude32 q >>> 23).toNat &&& (2 ^ 8 - 1) < 2 ^ 8
  rw [Nat.and_two_pow_sub_one_eq_mod]
  exact Nat.mod_lt _ (by decide)

private theorem fWord_bound (q : UInt32) : (fWord q).toNat < 8388608 := by
  rw [fWord, UInt32.toNat_and]
  change (magnitude32 q).toNat &&& (2 ^ 23 - 1) < 2 ^ 23
  rw [Nat.and_two_pow_sub_one_eq_mod]
  exact Nat.mod_lt _ (by decide)

private theorem base_nat (q : UInt32) :
    (base q).toNat =
      ((eWord q).toNat + 896) * 4503599627370496 +
        (fWord q).toNat * 536870912 := by
  have he := eWord_bound q
  have hf := fWord_bound q
  have hE : ((((eWord q).toUInt64 + 896) <<< 52) : UInt64).toNat =
      ((eWord q).toNat + 896) * 4503599627370496 := by
    simp only [UInt64.toNat_shiftLeft, UInt64.toNat_add, UInt32.toNat_toUInt64]
    change ((((eWord q).toNat + 896) % 18446744073709551616) <<< 52) %
      18446744073709551616 = _
    rw [Nat.shiftLeft_eq]
    omega
  have hF : (((fWord q).toUInt64 <<< 29) : UInt64).toNat =
      (fWord q).toNat * 536870912 := by
    simp only [UInt64.toNat_shiftLeft, UInt32.toNat_toUInt64]
    change ((fWord q).toNat <<< 29) % 18446744073709551616 = _
    rw [Nat.shiftLeft_eq]
    omega
  rw [base, UInt64.toNat_or, hE, hF]
  have hsmall : (fWord q).toNat * 536870912 < 2 ^ 52 := by omega
  simpa only [Nat.mul_comm 4503599627370496, Nat.add_comm] using
    (Nat.two_pow_add_eq_or_of_lt hsmall ((eWord q).toNat + 896)).symm

private theorem delta_bounds (q : UInt32) :
    268435456 ≤ (delta q).toNat ∧ (delta q).toNat ≤ 536870912 := by
  unfold delta
  split <;> decide

/-- The unsigned midpoint words lie strictly inside finite positive binary64.
The minimum-normal special decrement is included in the bound. -/
theorem unsigned_bounds (q : UInt32) (he0 : eWord q ≠ 0) (he255 : eWord q ≠ 255) :
    0 < (below q).toNat ∧ (below q).toNat < 9218868437227405312 ∧
    0 < (above q).toNat ∧ (above q).toNat < 9218868437227405312 := by
  have he := eWord_bound q
  have hf := fWord_bound q
  have hE0 : (eWord q).toNat ≠ 0 := by
    intro h
    apply he0
    apply UInt32.toNat_inj.mp
    exact h
  have hE255 : (eWord q).toNat ≠ 255 := by
    intro h
    apply he255
    apply UInt32.toNat_inj.mp
    exact h
  have hd := delta_bounds q
  have hbase := base_nat q
  have hdelta : delta q ≤ base q := by
    rw [UInt64.le_iff_toNat_le, hbase]
    omega
  have hbelow : (below q).toNat = (base q).toNat - (delta q).toNat := by
    exact UInt64.toNat_sub_of_le _ _ hdelta
  have habove : (above q).toNat = (base q).toNat + 268435456 := by
    rw [above, UInt64.toNat_add]
    change ((base q).toNat + 268435456) % 18446744073709551616 = _
    omega
  rw [hbelow, habove]
  omega

private theorem signed_magnitude (w : UInt64) (h : w.toNat < 9223372036854775808) :
    magnitude (w ||| 0x8000000000000000) = w.toNat := by
  have hw : (w ||| 0x8000000000000000).toNat =
      9223372036854775808 + w.toNat := by
    rw [UInt64.toNat_or, Nat.or_comm]
    have hp : w.toNat < 2 ^ 63 := h
    simpa only [Nat.mul_one] using (Nat.two_pow_add_eq_or_of_lt hp 1).symm
  unfold magnitude
  rw [hw]
  omega

private theorem unsigned_magnitude (w : UInt64) (h : w.toNat < 9223372036854775808) :
    magnitude w = w.toNat := Nat.mod_eq_of_lt h

private theorem finite_of_magnitude (w : UInt64)
    (h : magnitude w < 9218868437227405312) : finite64 w = true := by
  apply (finite64_iff_exp w).mpr
  rw [← magnitude_div]
  omega

theorem midpoint_finite_nonzero (q : UInt32) (he0 : eWord q ≠ 0) (he255 : eWord q ≠ 255) :
    finite64 (lowerWord q) = true ∧ finite64 (upperWord q) = true ∧
    magnitude (lowerWord q) ≠ 0 ∧ magnitude (upperWord q) ≠ 0 := by
  have hb := unsigned_bounds q he0 he255
  have hlo : (below q).toNat < 9223372036854775808 := by omega
  have hhi : (above q).toNat < 9223372036854775808 := by omega
  have hm : 0 < magnitude (lowerWord q) ∧ magnitude (lowerWord q) < 9218868437227405312 ∧
      0 < magnitude (upperWord q) ∧ magnitude (upperWord q) < 9218868437227405312 := by
    cases hs : negative32 q <;>
      simp only [lowerWord, upperWord, hs, Bool.false_eq_true, ite_false, ite_true,
        unsigned_magnitude _ hlo, unsigned_magnitude _ hhi,
        signed_magnitude _ hlo, signed_magnitude _ hhi] <;> omega
  exact ⟨finite_of_magnitude _ hm.2.1, finite_of_magnitude _ hm.2.2.2,
    Nat.ne_of_gt hm.1, Nat.ne_of_gt hm.2.2.1⟩

/-- Actual checker acceptance gives strict real containment of its computed
native endpoints inside its computed raw midpoint words. No producer premise,
no externally assumed midpoint finiteness/nonzero, and no Float.lt substitution. -/
theorem accepted_native_bounds (sum radius : Float) (sumWord : UInt64) (q : UInt32)
    (h : certify sum radius sumWord q = true) :
    value (lowerWord q) < nativeValue (sum - radius) ∧
      nativeValue (sum + radius) < value (upperWord q) := by
  obtain ⟨he0, he255, _, hlo, hhi, hlkey, hukey⟩ :=
    accepted_components sum radius sumWord q h
  obtain ⟨hl, hu, hlnz, hunz⟩ := midpoint_finite_nonzero q he0 he255
  exact orderKey_native_endpoints _ _ _ _ hl hu hlo hhi hlnz hunz hlkey hukey

end Submission.R25Checker


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

namespace Submission.R25Checker
theorem finite64_eq_runtime (w : UInt64) :
    R25OrderKey.finite64 w = R24PortableF64.finite64 w := rfl
theorem orderKey_eq_runtime (w : UInt64) :
    R25OrderKey.orderKey w = R24PortableF64.orderKey w := rfl
theorem certify_eq_runtime (s r : Float) (sw : UInt64) (q : UInt32) :
    certify s r sw q = R24PortableF64.certify s r sw q := rfl
theorem actual_acceptance_bounds (s r : Float) (sw : UInt64) (q : UInt32)
    (h : R24PortableF64.certify s r sw q = true) :
    R25OrderKey.value (lowerWord q) < R25OrderKey.nativeValue (s - r) ∧
    R25OrderKey.nativeValue (s + r) < R25OrderKey.value (upperWord q) := by
  apply accepted_native_bounds s r sw q
  simpa only [certify_eq_runtime] using h
end Submission.R25Checker

/- Pull strict raw-midpoint comparisons back through actual nearest64 endpoints.
   No outward-rounding premise is used. -/
namespace Submission.R26RnePullback
open Submission.R25OrderKey Submission.R25Checker
open FloatLib.Floats FloatLib.Floats.Formats.BinaryInterchange

private theorem strict_lower (x : Real) (w : UInt64) (hf : finite64 w = true)
    (h : value w < Model.roundAt F64 x) : value w < x := by
  by_contra hn
  have hm := Model.roundAt_mono F64 (le_of_not_gt hn)
  change Model.roundAt F64 x ≤ Model.roundAt F64 (Model.toReal (raw w)) at hm
  rw [Model.roundAt_toReal_eq (raw w) (finite64_model w hf)] at hm
  exact (not_lt_of_ge hm) h

private theorem strict_upper (x : Real) (w : UInt64) (hf : finite64 w = true)
    (h : Model.roundAt F64 x < value w) : x < value w := by
  by_contra hn
  have hm := Model.roundAt_mono F64 (le_of_not_gt hn)
  change Model.roundAt F64 (Model.toReal (raw w)) ≤ Model.roundAt F64 x at hm
  rw [Model.roundAt_toReal_eq (raw w) (finite64_model w hf)] at hm
  exact (not_lt_of_ge hm) h

/-- This matches the actual producer's error and nearest-endpoint outputs.
The exact target is in the strict cell even though native endpoints need not
round outward. Normality and finite representable midpoint facts are derived. -/
theorem accepted_contains_exact (s r : Float) (sw : UInt64) (q : UInt32)
    (S R : Real)
    (herr : |nativeValue s - S| ≤ R)
    (hlo : nativeValue (s - r) = Model.roundAt F64 (nativeValue s - R))
    (hhi : nativeValue (s + r) = Model.roundAt F64 (nativeValue s + R))
    (hacc : certify s r sw q = true) :
    value (lowerWord q) < S ∧ S < value (upperWord q) := by
  obtain ⟨he0, he255, _⟩ := accepted_components s r sw q hacc
  obtain ⟨hlf, huf, _, _⟩ := midpoint_finite_nonzero q he0 he255
  have hb := accepted_native_bounds s r sw q hacc
  rw [hlo, hhi] at hb
  have hl := strict_lower (nativeValue s - R) (lowerWord q) hlf hb.1
  have hu := strict_upper (nativeValue s + R) (upperWord q) huf hb.2
  obtain ⟨hel, heu⟩ := abs_le.mp herr
  constructor <;> linarith

end Submission.R26RnePullback

namespace Submission.R27ActualBoundary
open Submission.R25OrderKey Submission.R25Checker
open FloatLib.Floats FloatLib.Floats.Formats.BinaryInterchange

theorem actual_acceptance_contains_exact (s r : Float) (sw : UInt64) (q : UInt32)
    (S R : Real)
    (herr : |nativeValue s - S| ≤ R)
    (hlo : nativeValue (s - r) = Model.roundAt F64 (nativeValue s - R))
    (hhi : nativeValue (s + r) = Model.roundAt F64 (nativeValue s + R))
    (hacc : Submission.R24PortableF64.certify s r sw q = true) :
    value (lowerWord q) < S ∧ S < value (upperWord q) := by
  apply Submission.R26RnePullback.accepted_contains_exact s r sw q S R herr hlo hhi
  simpa only [certify_eq_runtime] using hacc

end Submission.R27ActualBoundary

/- Derive the endpoint equations from the actual finite guards. This avoids
   asking the producer for separate endpoint-enclosure or magnitude premises. -/
namespace Submission.R27GuardedEndpoints
open FloatLib.Floats FloatLib.Floats.Formats.BinaryInterchange
open Submission.R25OrderKey Submission.R25Checker

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
  have hc : certify s r s.toBits q = true := by
    simpa only [certify_eq_runtime] using hacc
  obtain ⟨_, _, hsf, hlof, hhif, _, _⟩ := accepted_components s r s.toBits q hc
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

/-- Only actual finite radius and forward error remain as producer obligations.
    Native endpoint RNE equations are derived from actual checker guards. -/
theorem actual_acceptance_contains_exact_of_error (s r : Float) (q : UInt32)
    (S : Real) (hr : r.isFinite = true)
    (herr : |nativeValue s - S| ≤ nativeValue r)
    (hacc : Submission.R24PortableF64.certify s r s.toBits q = true) :
    value (lowerWord q) < S ∧ S < value (upperWord q) := by
  have he := accepted_endpoint_equations s r q hr hacc
  exact Submission.R27ActualBoundary.actual_acceptance_contains_exact
    s r s.toBits q S (nativeValue r) herr he.1 he.2 hacc

end Submission.R27GuardedEndpoints

namespace Submission.R26CheckerConsequences
open Submission.R25OrderKey Submission.R25Checker

private theorem negative_of_nat_lt (w : UInt64)
    (hw : w.toNat < 9223372036854775808) : negative w = false := by
  simp [negative]
  omega

private theorem negative_or_sign (w : UInt64)
    (hw : w.toNat < 9223372036854775808) :
    negative (w ||| 0x8000000000000000) = true := by
  have hp : w.toNat < 2 ^ 63 := hw
  have hn : (w ||| 0x8000000000000000).toNat =
      w.toNat + 9223372036854775808 := by
    rw [UInt64.toNat_or]
    exact Nat.or_two_pow_eq_add_of_lt hp
  simp only [negative, hn, decide_eq_true_eq]
  omega

/-- Normality guards force both actual raw midpoint signs to match q. -/
theorem midpoint_signs (q : UInt32) (he0 : eWord q ≠ 0) (he255 : eWord q ≠ 255) :
    negative (lowerWord q) = negative32 q ∧
    negative (upperWord q) = negative32 q := by
  have hb := unsigned_bounds q he0 he255
  have hlo : (below q).toNat < 9223372036854775808 := by omega
  have hhi : (above q).toNat < 9223372036854775808 := by omega
  cases hs : negative32 q <;>
    simp only [lowerWord, upperWord, hs, Bool.false_eq_true, ite_false, ite_true]
  · exact ⟨negative_of_nat_lt _ hlo, negative_of_nat_lt _ hhi⟩
  · exact ⟨negative_or_sign _ hhi, negative_or_sign _ hlo⟩


end Submission.R26CheckerConsequences


namespace Submission.R27GuardedEndpoints
open FloatLib.Floats FloatLib.Floats.Formats.BinaryInterchange
open Submission.R25OrderKey Submission.R25Checker

theorem actual_accepted_exact_nonzero (s r : Float) (q : UInt32) (S : Real)
    (hr : r.isFinite = true)
    (herr : |nativeValue s - S| ≤ nativeValue r)
    (hacc : Submission.R24PortableF64.certify s r s.toBits q = true) : S ≠ 0 := by
  have ha : certify s r s.toBits q = true := by
    simpa only [certify_eq_runtime] using hacc
  obtain ⟨he0, he255, _⟩ := accepted_components s r s.toBits q ha
  obtain ⟨hlf, huf, hlnz, hunz⟩ := midpoint_finite_nonzero q he0 he255
  have hs := Submission.R26CheckerConsequences.midpoint_signs q he0 he255
  have hp := (magnitudeReal_pos_iff (magnitude (lowerWord q))).mpr hlnz
  have hn := (magnitudeReal_pos_iff (magnitude (upperWord q))).mpr hunz
  have hc := actual_acceptance_contains_exact_of_error s r q S hr herr hacc
  rw [raw_value _ hlf, raw_value _ huf, hs.1, hs.2] at hc
  cases hsign : negative32 q <;>
    simp only [hsign, Bool.false_eq_true, ite_false, ite_true] at hc <;>
    intro hz <;> subst S <;> linarith

theorem actual_accepted_total_nonzero (s r : Float) (q : UInt32) (T e : Int)
    (hr : r.isFinite = true)
    (herr : |nativeValue s - (T : Real) * (2 : Real) ^ e| ≤ nativeValue r)
    (hacc : Submission.R24PortableF64.certify s r s.toBits q = true) : T ≠ 0 := by
  have hn := actual_accepted_exact_nonzero s r q ((T : Real) * (2 : Real) ^ e) hr herr hacc
  intro hz
  apply hn
  simp only [hz, Int.cast_zero, zero_mul]

end Submission.R27GuardedEndpoints
