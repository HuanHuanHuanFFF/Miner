import ContractTensor

/-!
The full entry's incumbent, what every entry starts from and must beat: the best proven `add`
(`tuned`, 0.50x of `ExecFloat.add`) and `mul` (`mul/fast`, 0.55x of `ExecFloat.mul`), copied with
their proofs into namespaces of their own, with TorchLean's `sum` and `bmm` built from them, at
0.56x of the baseline's time.
-/

namespace Submission

/-!
`fastlog` with two cheap-tier changes, and the proof that they change nothing.

The special-operand test is one compare per operand, `(a <<< 1) - 1 ≥ 0xfeffffff`, instead of
four comparisons: shifting out the sign and subtracting one wraps a zero to the top and puts every
exponent-0xff word above the bound. The rounding step never leaves machine words: `rseAny` is
`roundShiftRightEven` with a `UInt64` shift and `mkW` packs the fields as `UInt32`. `sp1_eq`,
`rseAny_eq` and `mkW_ofNat` prove each equal to what it replaces; everything after reuses
fastlog's chain down to `wordAdd_eq_spec`. No new floating-point reasoning.
-/

namespace TunedAdd

open FloatLib.Floats Competition
open FloatLib.Floats.Formats.BinaryInterchange
open Model.NativeBinary32

/-- One binary-search step for `log2` on the value: shift down by `k` if anything is left there. -/
@[inline] def sx (k x : UInt64) : UInt64 := bif x >>> k == 0 then x else x >>> k

/-- The same step on the running result: add `k` when the value moved. -/
@[inline] def sr (k x r : UInt64) : UInt64 := bif x >>> k == 0 then r else r + k

/-- `UInt64.log2` by binary search: six steps instead of one per bit. -/
@[inline] def fastLog2 (x0 : UInt64) : UInt64 :=
  let x1 := sx 32 x0
  let r1 := sr 32 x0 0
  let x2 := sx 16 x1
  let r2 := sr 16 x1 r1
  let x3 := sx 8 x2
  let r3 := sr 8 x2 r2
  let x4 := sx 4 x3
  let r4 := sr 4 x3 r3
  let x5 := sx 2 x4
  let r5 := sr 2 x4 r4
  sr 1 x5 r5

/-- `roundShiftRightEven` with a word shift; the caller passes 1 ≤ shift < 64. -/
@[inline] def rse (value shift : UInt64) : UInt64 :=
  let quotient := value >>> shift
  let remainder := value &&& ((1 <<< shift) - 1)
  let half := (1 : UInt64) <<< (shift - 1)
  if remainder < half then quotient
  else if remainder > half then quotient + 1
  else if (quotient &&& 1) == 0 then quotient
  else quotient + 1

/-- `rse` for any shift, matching roundShiftRightEven's 0 and ≥ 64 cases. -/
@[inline] def rseAny (value shift : UInt64) : UInt64 :=
  if shift == 0 then value
  else if shift < 64 then rse value shift
  else if shift == 64 then (if value > 0x8000000000000000 then 1 else 0)
  else 0

/-- `mkBits` on words. -/
@[inline] def mkW (sign : Bool) (e f : UInt32) : UInt32 :=
  (if sign then (0x80000000 : UInt32) else 0) ||| ((e &&& 0xff) <<< 23) ||| (f &&& 0x007fffff)

/-- The stored fraction of a normalised mantissa, as `mkBits` receives it: zero below 2^23. -/
@[inline] def fracW (n : UInt64) : UInt32 :=
  (if n < 0x800000 then 0 else n - 0x800000).toUInt32

/-- `roundProduct` with `fastLog2`, on words throughout. -/
@[inline] def roundP (sign : Bool) (product scale : UInt64) : UInt32 :=
  if product == 0 then
    if sign then 0x80000000 else 0
  else
    let leading := fastLog2 product
    let position := leading + scale
    if position < 172 then
      let fraction :=
        if scale < 149 then
          rseAny product (149 - scale)
        else
          product <<< (scale - 149)
      if fraction == 0 then
        if sign then 0x80000000 else 0
      else if fraction == 0x800000 then
        mkW sign 1 0
      else
        mkW sign 0 fraction.toUInt32
    else
      let roundedMantissa :=
        if leading < 23 then
          product <<< (23 - leading)
        else
          rseAny product (leading - 23)
      let carry := roundedMantissa == 0x1000000
      let normalizedPosition := if carry then position + 1 else position
      if normalizedPosition > 425 then
        if sign then 0xff800000 else 0x7f800000
      else
        let normalizedMantissa := if carry then 0x800000 else roundedMantissa
        let encodedExponent := normalizedPosition - 171
        mkW sign encodedExponent.toUInt32 (fracW normalizedMantissa)

/-- The word kernel's finite path on bits; the caller has excluded NaN, infinity and zero. -/
@[inline] def core (xBits yBits : UInt32) : UInt32 :=
  let xExponent := expField xBits
  let yExponent := expField yBits
  let xSign := signBit xBits
  let ySign := signBit yBits
  let xMantissa := finiteMantissa xExponent (fracField xBits)
  let yMantissa := finiteMantissa yExponent (fracField yBits)
  let xScale := finiteScale xExponent
  let yScale := finiteScale yExponent
  if xScale ≤ yScale then
    let shift := yScale - xScale
    if shift ≤ 39 then
      let sum := FloatLib.Numerics.FixedWord.addSignedMagnitudes xSign ySign xMantissa (yMantissa <<< shift)
      roundP sum.1 sum.2 (xScale + 149)
    else yBits
  else
    let shift := xScale - yScale
    if shift ≤ 39 then
      let sum := FloatLib.Numerics.FixedWord.addSignedMagnitudes xSign ySign (xMantissa <<< shift) yMantissa
      roundP sum.1 sum.2 (yScale + 149)
    else xBits

/-- One operand is a NaN, an infinity or a zero, in one compare. -/
@[inline] def sp1 (a : UInt32) : Bool := (a <<< 1) - 1 ≥ 0xfeffffff

/-- The operands `core` leaves to the certified kernel: a NaN, an infinity or a zero. -/
@[inline] def special (a b : UInt32) : Bool := sp1 a || sp1 b

/-- Stored bits as a `Binary32`; the wrapper keeps goal terms well typed for `split` and `rw`. -/
@[inline] def ofBits (w : UInt32) : Binary32 := Configured.NativeFPU.ofBinary32Bits w

/-- `core` on ordinary operands, the certified kernel on special ones. -/
def add (x y : Binary32) : Binary32 :=
  if special x.raw.1 y.raw.1 then ExecFloat.add x y
  else ofBits (core x.raw.1 y.raw.1)

/-- The binary32 descriptor, storage plan and family that `Binary32` unfolds to. -/
abbrev Fmt := ExecFloat.Binary.format (exponentBits := 8) (fractionBits := 23)
abbrev Plan := Configured.StoragePlan.forKnownWidth Fmt (1 + 8 + 23) (by rfl)
abbrev Fam := Configured.Family Fmt (Configured.Code Plan) Plan

/-- The carrier's decode, with its codec instance pinned. -/
def dec (z : Binary32) : Model Fmt :=
  ExecFloat.ModelCodec.decode (F := Fam) (plan := Plan) (Model := Model Fmt) z

/-- Decoding a stored value is reading its bits. -/
theorem dec_eq (z : Binary32) : dec z = ofUInt32 z.raw.1 := rfl

/-- Decoding wrapped bits is rewrapping them in the model. -/
theorem dec_ofBits (w : UInt32) : dec (ofBits w) = ofUInt32 w := rfl

/-- On binary32 the dispatcher is the word kernel with the generic fallback. -/
theorem word32 (a b : Model Fmt) :
    Model.AddBackend.word a b =
      match addFiniteImpl? a b with
      | some s => s
      | none => Model.AddBackend.generic a b := by
  unfold Model.AddBackend.word
  rw [dif_pos (by decide)]
  rfl

/-- The planner's `wordAdd` decodes to the dispatcher on the decoded operands. -/
theorem dec_word (x y : Binary32) :
    dec (Configured.Backend.wordAdd x y) = Model.AddBackend.word (dec x) (dec y) :=
  ExecFloat.ModelCodec.decode_liftBinary (F := Fam) (plan := Plan) (Model := Model Fmt) _ x y

/-- Rewrapping a word and reading it back gives the word. -/
theorem toUInt32_ofUInt32 (b : UInt32) : toUInt32 (ofUInt32 b) = b := by
  simp [toUInt32, ofUInt32, Model.ofBits]

/-- Shifting out `k` low bits lowers `log2` by exactly `k`, while anything is left. -/
theorem log2_shift (n k : Nat) (h : n >>> k ≠ 0) : n.log2 = k + (n >>> k).log2 := by
  have hn : n ≠ 0 := by rintro rfl; simp at h
  rw [Nat.log2_eq_iff hn]
  rw [Nat.shiftRight_eq_div_pow] at h ⊢
  have h1 := Nat.log2_self_le h
  have h2 := Nat.lt_log2_self (n := n / 2 ^ k)
  have hk : 0 < 2 ^ k := Nat.two_pow_pos k
  constructor
  · calc 2 ^ (k + (n / 2 ^ k).log2) = 2 ^ k * 2 ^ (n / 2 ^ k).log2 := Nat.pow_add 2 _ _
      _ ≤ 2 ^ k * (n / 2 ^ k) := Nat.mul_le_mul_left _ h1
      _ ≤ n := Nat.mul_div_le n (2 ^ k)
  · calc n < 2 ^ k * (n / 2 ^ k + 1) := Nat.lt_mul_div_succ n hk
      _ ≤ 2 ^ k * 2 ^ ((n / 2 ^ k).log2 + 1) := Nat.mul_le_mul_left _ h2
      _ = 2 ^ (k + (n / 2 ^ k).log2 + 1) := by rw [← Nat.pow_add]; ring_nf

/-- Every 64-bit word has `log2` below 64. -/
theorem log2_lt_64 (x : UInt64) : x.toNat.log2 < 64 := by
  rcases Nat.eq_zero_or_pos x.toNat with h | h
  · simp [h]
  · exact (Nat.log2_lt (by omega)).mpr x.toNat_lt

/-- One `sx`/`sr` step keeps `log2 x0 = r + log2 x` and halves the bound on `x`. -/
theorem step (x0 r x k : UInt64) (hk : k.toNat ≤ 32) (hk0 : 0 < k.toNat)
    (hinv : x0.toNat.log2 = r.toNat + x.toNat.log2) (hb : x.toNat < 2 ^ (2 * k.toNat)) :
    x0.toNat.log2 = (sr k x r).toNat + (sx k x).toNat.log2 ∧ (sx k x).toNat < 2 ^ k.toNat := by
  have hs : (x >>> k).toNat = x.toNat >>> k.toNat := by
    rw [UInt64.toNat_shiftRight, Nat.mod_eq_of_lt (by omega)]
  unfold sx sr
  by_cases hz : x >>> k = 0
  · simp only [hz, beq_self_eq_true, Bool.cond_true]
    refine ⟨hinv, ?_⟩
    have h0 : x.toNat >>> k.toNat = 0 := by rw [← hs, hz]; rfl
    rw [Nat.shiftRight_eq_div_pow, Nat.div_eq_zero_iff] at h0
    rcases h0 with h0 | h0
    · exact absurd h0 (Nat.two_pow_pos _).ne'
    · exact h0
  · have hz' : (x >>> k == 0) = false := by simpa using hz
    simp only [hz', Bool.cond_false]
    have hne : x.toNat >>> k.toNat ≠ 0 := by
      rw [← hs]
      intro h
      exact hz (UInt64.toNat_inj.mp (by simpa using h))
    have hl := log2_shift x.toNat k.toNat hne
    have h64 := log2_lt_64 x0
    constructor
    · rw [UInt64.toNat_add, Nat.mod_eq_of_lt (by omega), hs]
      omega
    · rw [hs, Nat.shiftRight_eq_div_pow]
      apply Nat.div_lt_of_lt_mul
      rw [← Nat.pow_add]
      exact lt_of_lt_of_eq hb (by congr 1; omega)

/-- Zero and one have `log2` zero. -/
theorem log2_lt_two (n : Nat) (h : n < 2) : n.log2 = 0 := by
  interval_cases n <;> decide

/-- The binary search computes `UInt64.log2` on every word. -/
theorem fastLog2_eq (x : UInt64) : fastLog2 x = x.log2 := by
  apply UInt64.toNat_inj.mp
  rw [show x.log2.toNat = x.toNat.log2 from rfl]
  have b0 : x.toNat < 2 ^ (2 * (32 : UInt64).toNat) := x.toNat_lt
  obtain ⟨e1, b1⟩ := step x 0 x 32 (by decide) (by decide) (by simp) b0
  obtain ⟨e2, b2⟩ := step x _ _ 16 (by decide) (by decide) e1 (by simpa using b1)
  obtain ⟨e3, b3⟩ := step x _ _ 8 (by decide) (by decide) e2 (by simpa using b2)
  obtain ⟨e4, b4⟩ := step x _ _ 4 (by decide) (by decide) e3 (by simpa using b3)
  obtain ⟨e5, b5⟩ := step x _ _ 2 (by decide) (by decide) e4 (by simpa using b4)
  obtain ⟨e6, b6⟩ := step x _ _ 1 (by decide) (by decide) e5 (by simpa using b5)
  rw [log2_lt_two (sx 1 (sx 2 (sx 4 (sx 8 (sx 16 (sx 32 x)))))).toNat (by simpa using b6)] at e6
  unfold fastLog2
  dsimp only
  omega
/-- The exponent field as a natural number. -/
theorem expField_toNat (a : UInt32) : (expField a).toNat = a.toNat / 2 ^ 23 % 2 ^ 8 := by
  unfold expField
  rw [UInt32.toNat_and, UInt32.toNat_shiftRight]
  rw [show (0xff : UInt32).toNat = 2 ^ 8 - 1 from rfl, Nat.and_two_pow_sub_one_eq_mod]
  simp [Nat.shiftRight_eq_div_pow]

/-- The fraction field as a natural number. -/
theorem fracField_toNat (a : UInt32) : (fracField a).toNat = a.toNat % 2 ^ 23 := by
  unfold fracField
  rw [UInt32.toNat_and, show (0x007fffff : UInt32).toNat = 2 ^ 23 - 1 from rfl,
    Nat.and_two_pow_sub_one_eq_mod]

/-- The one-compare test as a natural-number condition. -/
theorem sp1_iff (a : UInt32) :
    sp1 a = true ↔ (a.toNat % 2 ^ 31 = 0 ∨ a.toNat % 2 ^ 31 ≥ 0x7f800000) := by
  have ha := a.toNat_lt
  unfold sp1
  simp only [decide_eq_true_eq, ge_iff_le, UInt32.le_iff_toNat_le, UInt32.toNat_sub,
    UInt32.toNat_shiftLeft]
  simp
  omega

/-- The mantissa is zero exactly when the exponent and the fraction both are. -/
theorem finiteMantissa_eq_zero (e f : UInt32) :
    finiteMantissa e f = 0 ↔ e = 0 ∧ f = 0 := by
  unfold finiteMantissa
  split
  · rename_i he
    have he : e = 0 := by simpa using he
    simp only [he, true_and]
    constructor
    · intro h
      apply UInt32.toNat_inj.mp
      simpa using congrArg UInt64.toNat h
    · rintro rfl; rfl
  · rename_i he
    have he : ¬e = 0 := by simpa using he
    simp only [he, false_and, iff_false]
    intro h
    have := congrArg (fun x => x.toNat.testBit 23) h
    simp [UInt64.toNat_or, Nat.testBit_or] at this
    exact absurd this.2 (by decide)

/-- The one-compare test is the four-comparison test, on one operand. -/
theorem sp1_eq (a : UInt32) :
    sp1 a = (expField a == 0xff || finiteMantissa (expField a) (fracField a) == 0) := by
  have ha := a.toNat_lt
  have he := expField_toNat a
  have hf := fracField_toNat a
  apply Bool.eq_iff_iff.mpr
  rw [sp1_iff]
  simp only [Bool.or_eq_true, beq_iff_eq, finiteMantissa_eq_zero]
  rw [← UInt32.toNat_inj, ← UInt32.toNat_inj, ← UInt32.toNat_inj, he, hf]
  simp only [show (0xff : UInt32).toNat = 255 from rfl, show (0 : UInt32).toNat = 0 from rfl]
  omega
/-- The word shift rounds exactly as FloatLib's natural-number-shift version. -/
theorem rseAny_eq (value shift : UInt64) :
    rseAny value shift = FloatLib.Numerics.FixedWord.roundShiftRightEven value shift.toNat := by
  unfold rseAny rse FloatLib.Numerics.FixedWord.roundShiftRightEven
  have hs := shift.toNat_lt
  by_cases h0 : shift = 0
  · subst h0; rfl
  · have h0' : shift.toNat ≠ 0 := by
      intro h; exact h0 (UInt64.toNat_inj.mp (by simpa using h))
    simp only [h0, beq_iff_eq, h0', reduceIte]
    have e1 : UInt64.ofNat shift.toNat = shift := UInt64.ofNat_toNat
    have e2 : UInt64.ofNat (shift.toNat - 1) = shift - 1 := by
      apply UInt64.toNat_inj.mp
      have hle : (1 : UInt64) ≤ shift := by rw [UInt64.le_iff_toNat_le]; simp; omega
      rw [UInt64.toNat_sub_of_le _ _ hle]
      simp
      omega
    have c1 : (shift < 64) ↔ shift.toNat < 64 := UInt64.lt_iff_toNat_lt
    have c2 : shift = 64 ↔ shift.toNat = 64 := by rw [← UInt64.toNat_inj]; rfl
    simp only [e1, e2, ← c1, ← c2]

/-- `mkW` packs what `mkBits` packs: `mkBits` only ever reads its fields through `ofNat`. -/
theorem mkW_ofNat (sign : Bool) (e f : Nat) :
    mkW sign (UInt32.ofNat e) (UInt32.ofNat f) = mkBits sign e f := by
  unfold mkW mkBits
  cases sign <;> rfl

/-- A 64-bit word narrowed to 32 bits is its value taken mod 2^32. -/
theorem toUInt32_eq (x : UInt64) : x.toUInt32 = UInt32.ofNat x.toNat := rfl

/-- `fracW` is the natural-number subtraction it replaces. -/
theorem fracW_eq (n : UInt64) : fracW n = UInt32.ofNat (n.toNat - 0x800000) := by
  unfold fracW
  split
  · rename_i h
    rw [UInt64.lt_iff_toNat_lt] at h
    simp only [toUInt32_eq]
    rw [show n.toNat - 0x800000 = 0 by simp at h; omega]
    rfl
  · rename_i h
    rw [UInt64.lt_iff_toNat_lt] at h
    simp only [toUInt32_eq]
    rw [UInt64.toNat_sub_of_le _ _ (by rw [UInt64.le_iff_toNat_le]; simp at h ⊢; omega)]
    rfl

/-- `roundP` is FloatLib's `roundProduct`: they differ in `log2` and in staying on words. -/
theorem roundP_eq (sign : Bool) (product scale : UInt64) :
    roundP sign product scale = roundProduct sign product scale := by
  unfold roundP roundProduct
  simp only [fastLog2_eq, rseAny_eq, fracW_eq, toUInt32_eq]
  rw [show (1 : UInt32) = UInt32.ofNat 1 from rfl, show (0 : UInt32) = UInt32.ofNat 0 from rfl]
  simp only [mkW_ofNat]

/-- Off the fallback, the word kernel returns exactly `core` on the same bits. -/
theorem impl_eq (a b : UInt32) (ha : expField a ≠ 0xff) (hb : expField b ≠ 0xff)
    (hma : finiteMantissa (expField a) (fracField a) ≠ 0)
    (hmb : finiteMantissa (expField b) (fracField b) ≠ 0) :
    addFiniteImpl? (ofUInt32 a) (ofUInt32 b) = some (ofUInt32 (core a b)) := by
  unfold addFiniteImpl? core
  simp only [roundP_eq, toUInt32_ofUInt32, ha, hb, hma, hmb, beq_iff_eq, Bool.or_eq_true, or_self,
    if_false]
  split_ifs <;> rfl

/-- The kernel equals the planner's word addition on every pair of operands. -/
theorem add_eq_word (x y : Binary32) : add x y = Configured.Backend.wordAdd x y := by
  unfold add
  split
  · rfl
  · rename_i h
    simp only [special, sp1_eq, Bool.or_eq_true, beq_iff_eq, not_or] at h
    obtain ⟨⟨ha, hma⟩, hb, hmb⟩ := h
    apply ExecFloat.ModelCodec.decode_injective (F := Fam) (plan := Plan) (Model := Model Fmt)
    change dec (ofBits (core x.raw.1 y.raw.1)) = dec (Configured.Backend.wordAdd x y)
    rw [dec_ofBits, dec_word, word32, dec_eq x, dec_eq y, impl_eq _ _ ha hb hma hmb]

theorem add_spec : ∀ x y : Binary32, add x y = ExecFloat.Spec.add x y := fun x y => by
  rw [add_eq_word]
  exact Configured.Backend.wordAdd_eq_spec x y

end TunedAdd

/-!
FloatLib's binary32 word multiplication on raw bits, with tuned's rounding step.

`ExecFloat.mul` decodes into the generic model, runs `mulFiniteImpl?` inside an `Option` and
encodes back, and its `roundProduct` computes `UInt64.log2` one bit at a time over a product of up
to 48 bits. `core` is `mulFiniteImpl?` on bare words and `roundP` is `roundProduct` with a six-step
binary-search `log2` and no `Nat` round trips, both taken from `tuned` with their proofs. NaN and
infinity go to `ExecFloat.mul`; zeros need no fallback, the rounding step signs them. `sm1_eq`
proves the one-compare test, and the rest reuses `wordMul_eq_spec`: no floating-point reasoning.
-/

namespace FastMul

open FloatLib.Floats Competition
open FloatLib.Floats.Formats.BinaryInterchange
open Model.NativeBinary32

/-- One binary-search step for `log2` on the value: shift down by `k` if anything is left there. -/
@[inline] def sx (k x : UInt64) : UInt64 := bif x >>> k == 0 then x else x >>> k

/-- The same step on the running result: add `k` when the value moved. -/
@[inline] def sr (k x r : UInt64) : UInt64 := bif x >>> k == 0 then r else r + k

/-- `UInt64.log2` by binary search: six steps instead of one per bit. -/
@[inline] def fastLog2 (x0 : UInt64) : UInt64 :=
  let x1 := sx 32 x0
  let r1 := sr 32 x0 0
  let x2 := sx 16 x1
  let r2 := sr 16 x1 r1
  let x3 := sx 8 x2
  let r3 := sr 8 x2 r2
  let x4 := sx 4 x3
  let r4 := sr 4 x3 r3
  let x5 := sx 2 x4
  let r5 := sr 2 x4 r4
  sr 1 x5 r5

/-- `roundShiftRightEven` with a word shift; the caller passes 1 ≤ shift < 64. -/
@[inline] def rse (value shift : UInt64) : UInt64 :=
  let quotient := value >>> shift
  let remainder := value &&& ((1 <<< shift) - 1)
  let half := (1 : UInt64) <<< (shift - 1)
  if remainder < half then quotient
  else if remainder > half then quotient + 1
  else if (quotient &&& 1) == 0 then quotient
  else quotient + 1

/-- `rse` for any shift, matching roundShiftRightEven's 0 and ≥ 64 cases. -/
@[inline] def rseAny (value shift : UInt64) : UInt64 :=
  if shift == 0 then value
  else if shift < 64 then rse value shift
  else if shift == 64 then (if value > 0x8000000000000000 then 1 else 0)
  else 0

/-- `mkBits` on words. -/
@[inline] def mkW (sign : Bool) (e f : UInt32) : UInt32 :=
  (if sign then (0x80000000 : UInt32) else 0) ||| ((e &&& 0xff) <<< 23) ||| (f &&& 0x007fffff)

/-- The stored fraction of a normalised mantissa, as `mkBits` receives it: zero below 2^23. -/
@[inline] def fracW (n : UInt64) : UInt32 :=
  (if n < 0x800000 then 0 else n - 0x800000).toUInt32

/-- `roundProduct` with `fastLog2`, on words throughout. -/
@[inline] def roundP (sign : Bool) (product scale : UInt64) : UInt32 :=
  if product == 0 then
    if sign then 0x80000000 else 0
  else
    let leading := fastLog2 product
    let position := leading + scale
    if position < 172 then
      let fraction :=
        if scale < 149 then
          rseAny product (149 - scale)
        else
          product <<< (scale - 149)
      if fraction == 0 then
        if sign then 0x80000000 else 0
      else if fraction == 0x800000 then
        mkW sign 1 0
      else
        mkW sign 0 fraction.toUInt32
    else
      let roundedMantissa :=
        if leading < 23 then
          product <<< (23 - leading)
        else
          rseAny product (leading - 23)
      let carry := roundedMantissa == 0x1000000
      let normalizedPosition := if carry then position + 1 else position
      if normalizedPosition > 425 then
        if sign then 0xff800000 else 0x7f800000
      else
        let normalizedMantissa := if carry then 0x800000 else roundedMantissa
        let encodedExponent := normalizedPosition - 171
        mkW sign encodedExponent.toUInt32 (fracW normalizedMantissa)

/-- The word multiplication's finite path on bits; the caller has excluded NaN and infinity. -/
@[inline] def core (xBits yBits : UInt32) : UInt32 :=
  let xExponent := expField xBits
  let yExponent := expField yBits
  let sign := Bool.xor (signBit xBits) (signBit yBits)
  let xFraction := fracField xBits
  let yFraction := fracField yBits
  let xMantissa := finiteMantissa xExponent xFraction
  let yMantissa := finiteMantissa yExponent yFraction
  let xScale := finiteScale xExponent
  let yScale := finiteScale yExponent
  roundP sign (xMantissa * yMantissa) (xScale + yScale)

/-- One operand is a NaN or an infinity, in one compare: its exponent field is all ones. -/
@[inline] def sm1 (a : UInt32) : Bool := a <<< 1 ≥ 0xff000000

/-- The operands `core` leaves to the certified kernel: a NaN or an infinity. -/
@[inline] def special (a b : UInt32) : Bool := sm1 a || sm1 b

/-- Stored bits as a `Binary32`; the wrapper keeps goal terms well typed for `split` and `rw`. -/
@[inline] def ofBits (w : UInt32) : Binary32 := Configured.NativeFPU.ofBinary32Bits w

/-- `core` on ordinary operands, the certified kernel on special ones. -/
def mul (x y : Binary32) : Binary32 :=
  if special x.raw.1 y.raw.1 then ExecFloat.mul x y
  else ofBits (core x.raw.1 y.raw.1)

/-- The binary32 descriptor, storage plan and family that `Binary32` unfolds to. -/
abbrev Fmt := ExecFloat.Binary.format (exponentBits := 8) (fractionBits := 23)
abbrev Plan := Configured.StoragePlan.forKnownWidth Fmt (1 + 8 + 23) (by rfl)
abbrev Fam := Configured.Family Fmt (Configured.Code Plan) Plan

/-- The carrier's decode, with its codec instance pinned. -/
def dec (z : Binary32) : Model Fmt :=
  ExecFloat.ModelCodec.decode (F := Fam) (plan := Plan) (Model := Model Fmt) z

/-- Decoding a stored value is reading its bits. -/
theorem dec_eq (z : Binary32) : dec z = ofUInt32 z.raw.1 := rfl

/-- Decoding wrapped bits is rewrapping them in the model. -/
theorem dec_ofBits (w : UInt32) : dec (ofBits w) = ofUInt32 w := rfl

/-- On binary32 the dispatcher is the word kernel with the generic fallback. -/
theorem word32 (a b : Model Fmt) :
    Model.MulBackend.word a b =
      match mulFiniteImpl? a b with
      | some s => s
      | none => Model.MulBackend.generic a b := by
  unfold Model.MulBackend.word
  rw [dif_pos (by decide)]
  rfl

/-- The planner's `wordMul` decodes to the dispatcher on the decoded operands. -/
theorem dec_word (x y : Binary32) :
    dec (Configured.Backend.wordMul x y) = Model.MulBackend.word (dec x) (dec y) :=
  ExecFloat.ModelCodec.decode_liftBinary (F := Fam) (plan := Plan) (Model := Model Fmt) _ x y

/-- Rewrapping a word and reading it back gives the word. -/
theorem toUInt32_ofUInt32 (b : UInt32) : toUInt32 (ofUInt32 b) = b := by
  simp [toUInt32, ofUInt32, Model.ofBits]

/-- Shifting out `k` low bits lowers `log2` by exactly `k`, while anything is left. -/
theorem log2_shift (n k : Nat) (h : n >>> k ≠ 0) : n.log2 = k + (n >>> k).log2 := by
  have hn : n ≠ 0 := by rintro rfl; simp at h
  rw [Nat.log2_eq_iff hn]
  rw [Nat.shiftRight_eq_div_pow] at h ⊢
  have h1 := Nat.log2_self_le h
  have h2 := Nat.lt_log2_self (n := n / 2 ^ k)
  have hk : 0 < 2 ^ k := Nat.two_pow_pos k
  constructor
  · calc 2 ^ (k + (n / 2 ^ k).log2) = 2 ^ k * 2 ^ (n / 2 ^ k).log2 := Nat.pow_add 2 _ _
      _ ≤ 2 ^ k * (n / 2 ^ k) := Nat.mul_le_mul_left _ h1
      _ ≤ n := Nat.mul_div_le n (2 ^ k)
  · calc n < 2 ^ k * (n / 2 ^ k + 1) := Nat.lt_mul_div_succ n hk
      _ ≤ 2 ^ k * 2 ^ ((n / 2 ^ k).log2 + 1) := Nat.mul_le_mul_left _ h2
      _ = 2 ^ (k + (n / 2 ^ k).log2 + 1) := by rw [← Nat.pow_add]; ring_nf

/-- Every 64-bit word has `log2` below 64. -/
theorem log2_lt_64 (x : UInt64) : x.toNat.log2 < 64 := by
  rcases Nat.eq_zero_or_pos x.toNat with h | h
  · simp [h]
  · exact (Nat.log2_lt (by omega)).mpr x.toNat_lt

/-- One `sx`/`sr` step keeps `log2 x0 = r + log2 x` and halves the bound on `x`. -/
theorem step (x0 r x k : UInt64) (hk : k.toNat ≤ 32) (hk0 : 0 < k.toNat)
    (hinv : x0.toNat.log2 = r.toNat + x.toNat.log2) (hb : x.toNat < 2 ^ (2 * k.toNat)) :
    x0.toNat.log2 = (sr k x r).toNat + (sx k x).toNat.log2 ∧ (sx k x).toNat < 2 ^ k.toNat := by
  have hs : (x >>> k).toNat = x.toNat >>> k.toNat := by
    rw [UInt64.toNat_shiftRight, Nat.mod_eq_of_lt (by omega)]
  unfold sx sr
  by_cases hz : x >>> k = 0
  · simp only [hz, beq_self_eq_true, Bool.cond_true]
    refine ⟨hinv, ?_⟩
    have h0 : x.toNat >>> k.toNat = 0 := by rw [← hs, hz]; rfl
    rw [Nat.shiftRight_eq_div_pow, Nat.div_eq_zero_iff] at h0
    rcases h0 with h0 | h0
    · exact absurd h0 (Nat.two_pow_pos _).ne'
    · exact h0
  · have hz' : (x >>> k == 0) = false := by simpa using hz
    simp only [hz', Bool.cond_false]
    have hne : x.toNat >>> k.toNat ≠ 0 := by
      rw [← hs]
      intro h
      exact hz (UInt64.toNat_inj.mp (by simpa using h))
    have hl := log2_shift x.toNat k.toNat hne
    have h64 := log2_lt_64 x0
    constructor
    · rw [UInt64.toNat_add, Nat.mod_eq_of_lt (by omega), hs]
      omega
    · rw [hs, Nat.shiftRight_eq_div_pow]
      apply Nat.div_lt_of_lt_mul
      rw [← Nat.pow_add]
      exact lt_of_lt_of_eq hb (by congr 1; omega)

/-- Zero and one have `log2` zero. -/
theorem log2_lt_two (n : Nat) (h : n < 2) : n.log2 = 0 := by
  interval_cases n <;> decide

/-- The binary search computes `UInt64.log2` on every word. -/
theorem fastLog2_eq (x : UInt64) : fastLog2 x = x.log2 := by
  apply UInt64.toNat_inj.mp
  rw [show x.log2.toNat = x.toNat.log2 from rfl]
  have b0 : x.toNat < 2 ^ (2 * (32 : UInt64).toNat) := x.toNat_lt
  obtain ⟨e1, b1⟩ := step x 0 x 32 (by decide) (by decide) (by simp) b0
  obtain ⟨e2, b2⟩ := step x _ _ 16 (by decide) (by decide) e1 (by simpa using b1)
  obtain ⟨e3, b3⟩ := step x _ _ 8 (by decide) (by decide) e2 (by simpa using b2)
  obtain ⟨e4, b4⟩ := step x _ _ 4 (by decide) (by decide) e3 (by simpa using b3)
  obtain ⟨e5, b5⟩ := step x _ _ 2 (by decide) (by decide) e4 (by simpa using b4)
  obtain ⟨e6, b6⟩ := step x _ _ 1 (by decide) (by decide) e5 (by simpa using b5)
  rw [log2_lt_two (sx 1 (sx 2 (sx 4 (sx 8 (sx 16 (sx 32 x)))))).toNat (by simpa using b6)] at e6
  unfold fastLog2
  dsimp only
  omega
/-- The exponent field as a natural number. -/
theorem expField_toNat (a : UInt32) : (expField a).toNat = a.toNat / 2 ^ 23 % 2 ^ 8 := by
  unfold expField
  rw [UInt32.toNat_and, UInt32.toNat_shiftRight]
  rw [show (0xff : UInt32).toNat = 2 ^ 8 - 1 from rfl, Nat.and_two_pow_sub_one_eq_mod]
  simp [Nat.shiftRight_eq_div_pow]

/-- The one-compare test is the exponent-field test, on one operand. -/
theorem sm1_eq (a : UInt32) : sm1 a = (expField a == 0xff) := by
  have ha := a.toNat_lt
  have he := expField_toNat a
  apply Bool.eq_iff_iff.mpr
  unfold sm1
  simp only [decide_eq_true_eq, ge_iff_le, UInt32.le_iff_toNat_le, UInt32.toNat_shiftLeft,
    beq_iff_eq]
  rw [← UInt32.toNat_inj, he]
  simp only [show (0xff : UInt32).toNat = 255 from rfl]
  simp
  omega

/-- The word shift rounds exactly as FloatLib's natural-number-shift version. -/
theorem rseAny_eq (value shift : UInt64) :
    rseAny value shift = FloatLib.Numerics.FixedWord.roundShiftRightEven value shift.toNat := by
  unfold rseAny rse FloatLib.Numerics.FixedWord.roundShiftRightEven
  have hs := shift.toNat_lt
  by_cases h0 : shift = 0
  · subst h0; rfl
  · have h0' : shift.toNat ≠ 0 := by
      intro h; exact h0 (UInt64.toNat_inj.mp (by simpa using h))
    simp only [h0, beq_iff_eq, h0', reduceIte]
    have e1 : UInt64.ofNat shift.toNat = shift := UInt64.ofNat_toNat
    have e2 : UInt64.ofNat (shift.toNat - 1) = shift - 1 := by
      apply UInt64.toNat_inj.mp
      have hle : (1 : UInt64) ≤ shift := by rw [UInt64.le_iff_toNat_le]; simp; omega
      rw [UInt64.toNat_sub_of_le _ _ hle]
      simp
      omega
    have c1 : (shift < 64) ↔ shift.toNat < 64 := UInt64.lt_iff_toNat_lt
    have c2 : shift = 64 ↔ shift.toNat = 64 := by rw [← UInt64.toNat_inj]; rfl
    simp only [e1, e2, ← c1, ← c2]

/-- `mkW` packs what `mkBits` packs: `mkBits` only ever reads its fields through `ofNat`. -/
theorem mkW_ofNat (sign : Bool) (e f : Nat) :
    mkW sign (UInt32.ofNat e) (UInt32.ofNat f) = mkBits sign e f := by
  unfold mkW mkBits
  cases sign <;> rfl

/-- A 64-bit word narrowed to 32 bits is its value taken mod 2^32. -/
theorem toUInt32_eq (x : UInt64) : x.toUInt32 = UInt32.ofNat x.toNat := rfl

/-- `fracW` is the natural-number subtraction it replaces. -/
theorem fracW_eq (n : UInt64) : fracW n = UInt32.ofNat (n.toNat - 0x800000) := by
  unfold fracW
  split
  · rename_i h
    rw [UInt64.lt_iff_toNat_lt] at h
    simp only [toUInt32_eq]
    rw [show n.toNat - 0x800000 = 0 by simp at h; omega]
    rfl
  · rename_i h
    rw [UInt64.lt_iff_toNat_lt] at h
    simp only [toUInt32_eq]
    rw [UInt64.toNat_sub_of_le _ _ (by rw [UInt64.le_iff_toNat_le]; simp at h ⊢; omega)]
    rfl

/-- `roundP` is FloatLib's `roundProduct`: they differ in `log2` and in staying on words. -/
theorem roundP_eq (sign : Bool) (product scale : UInt64) :
    roundP sign product scale = roundProduct sign product scale := by
  unfold roundP roundProduct
  simp only [fastLog2_eq, rseAny_eq, fracW_eq, toUInt32_eq]
  rw [show (1 : UInt32) = UInt32.ofNat 1 from rfl, show (0 : UInt32) = UInt32.ofNat 0 from rfl]
  simp only [mkW_ofNat]

/-- Off the fallback, the word kernel returns exactly `core` on the same bits. -/
theorem impl_eq (a b : UInt32) (ha : expField a ≠ 0xff) (hb : expField b ≠ 0xff) :
    mulFiniteImpl? (ofUInt32 a) (ofUInt32 b) = some (ofUInt32 (core a b)) := by
  unfold mulFiniteImpl? core
  simp only [roundP_eq, toUInt32_ofUInt32, ha, hb, beq_iff_eq, Bool.or_eq_true, or_self,
    if_false]

/-- The kernel equals the planner's word multiplication on every pair of operands. -/
theorem mul_eq_word (x y : Binary32) : mul x y = Configured.Backend.wordMul x y := by
  unfold mul
  split
  · rfl
  · rename_i h
    simp only [special, sm1_eq, Bool.or_eq_true, beq_iff_eq, not_or] at h
    obtain ⟨ha, hb⟩ := h
    apply ExecFloat.ModelCodec.decode_injective (F := Fam) (plan := Plan) (Model := Model Fmt)
    change dec (ofBits (core x.raw.1 y.raw.1)) = dec (Configured.Backend.wordMul x y)
    rw [dec_ofBits, dec_word, word32, dec_eq x, dec_eq y, impl_eq _ _ ha hb]

theorem mul_spec : ∀ x y : Binary32, mul x y = ExecFloat.Spec.mul x y := fun x y => by
  rw [mul_eq_word]
  exact Configured.Backend.wordMul_eq_spec x y

end FastMul

open FloatLib.Floats Competition

/-- Stage 1's `tuned` addition. -/
def add (x y : Binary32) : Binary32 := TunedAdd.add x y

theorem add_spec : ∀ x y : Binary32, add x y = ExecFloat.Spec.add x y := TunedAdd.add_spec

/-- Stage 1's `mul/fast` multiplication. -/
def mul (x y : Binary32) : Binary32 := FastMul.mul x y

theorem mul_spec : ∀ x y : Binary32, mul x y = ExecFloat.Spec.mul x y := FastMul.mul_spec

/-- `add` and `mul` are FloatLib's executable operations, whatever they compute internally. -/
theorem add_eq : add = ExecFloat.add := by
  funext x y
  rw [add_spec, ExecFloat.Proof.add_eq_spec]

theorem mul_eq : mul = ExecFloat.mul := by
  funext x y
  rw [mul_spec, ExecFloat.Proof.mul_eq_spec]

/-- TorchLean's sum: the elements left to right, from +0, with `add`. -/
def sum {n : Nat} (x : Vector Binary32 n) : Binary32 := x.foldl add posZero

theorem sum_spec : ∀ (n : Nat) (x : Vector Binary32 n), sum x = sumSpec x.get := by
  intro n x
  conv_lhs => rw [sum, add_eq, ← Vector.ofFn_getElem (xs := x)]
  rw [← Vector.foldl_toList, Vector.toList_ofFn, List.ofFn_eq_map, List.foldl_map]
  rfl

/-- TorchLean's batched matmul: each output a left fold over `k` of `add acc (mul a b)`. -/
def bmm (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Vector Binary32 (batch * m * p) :=
  Vector.ofFn fun q =>
    let (b, i, j) := bmmDecodeC m p q.val
    Fin.foldl n
      (fun acc k =>
        add acc (mul (A.toArray.getD ((b * m + i) * n + k.val) posZero)
          (B.toArray.getD ((b * n + k.val) * p + j) posZero)))
      posZero

/-- The kernel's bounded read is the rule's `getD`: same element in bounds, +0 outside. -/
theorem toArray_getD {N : Nat} (A : Vector Binary32 N) (i : Nat) :
    A.toArray.getD i posZero = getD A.get i := by
  unfold getD
  split <;> simp_all [Array.getD, Vector.get]

theorem bmm_spec : ∀ (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)),
    (bmm batch m n p A B).get = bmmSpec batch m n p A.get B.get := by
  intro batch m n p A B
  funext q
  simp only [bmm, add_eq, mul_eq, Vector.get, Vector.toArray_ofFn, Array.getElem_ofFn,
    Fin.foldl_eq_finRange_foldl, toArray_getD]
  rfl

end Submission


set_option maxRecDepth 4096
set_option maxHeartbeats 1000000

namespace R2W01c

namespace NativeBridge

open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange
open Float.Model.UnpackedFloat
open FloatLib.Floats.Formats.BinaryInterchange.Model






theorem le_targetExponent_totalExponent_iff (spec : Float.Model.Format)
    (mantissa : Nat) (exponent : Int) :
    exponent ≤ spec.targetExponent (Float.Model.totalExponent mantissa exponent) ↔
      exponent ≤ spec.minExponent ∨ 2 ^ spec.mantissaBitsWithoutImplicit ≤ mantissa := by
  have hlog : spec.mantissaBitsWithoutImplicit ≤ mantissa.log2 ↔
      2 ^ spec.mantissaBitsWithoutImplicit ≤ mantissa := by
    rcases Nat.eq_zero_or_pos mantissa with rfl | hmantissa
    · have hwidth := spec.hm
      have hpow := Nat.two_pow_pos spec.mantissaBitsWithoutImplicit
      rw [Nat.log2_zero]
      omega
    · exact Nat.le_log2 hmantissa.ne'
  rw [← hlog]
  simp only [Float.Model.Format.targetExponent, Float.Model.totalExponent,
    Float.Model.Format.mantissaBits]
  omega





theorem add_le_targetExponent_totalExponent_mul (spec : Float.Model.Format)
    {mantissa₁ mantissa₂ : Nat} {exponent₁ exponent₂ : Int}
    (hmantissa₁ : 0 < mantissa₁) (hmantissa₂ : 0 < mantissa₂)
    (hle₁ :
      exponent₁ ≤ spec.targetExponent (Float.Model.totalExponent mantissa₁ exponent₁))
    (hle₂ :
      exponent₂ ≤ spec.targetExponent (Float.Model.totalExponent mantissa₂ exponent₂)) :
    exponent₁ + exponent₂ ≤
      spec.targetExponent
        (Float.Model.totalExponent (mantissa₁ * mantissa₂) (exponent₁ + exponent₂)) := by
  rw [le_targetExponent_totalExponent_iff] at hle₁ hle₂ ⊢
  have hmin : spec.minExponent ≤ 0 := by
    have hwidth := spec.hm
    have hpow : (1 : Int) ≤ 2 ^ (spec.exponentBits - 1) := by
      exact_mod_cast Nat.two_pow_pos (spec.exponentBits - 1)
    simp only [Float.Model.Format.minExponent, Float.Model.Format.mantissaBits]
    omega
  rcases hle₁ with hle₁ | hle₁
  · rcases hle₂ with hle₂ | hle₂
    · exact Or.inl (by omega)
    · exact Or.inr (hle₂.trans (Nat.le_mul_of_pos_left mantissa₂ hmantissa₁))
  · exact Or.inr (hle₁.trans (Nat.le_mul_of_pos_right mantissa₁ hmantissa₂))





theorem le_targetExponent_totalExponent_of_toModel_eq_finite {fmt : FloatFormat} (x : Model fmt)
    {sign : Sign} {mantissa : Nat} {exponent : Int} {hmantissa : 0 < mantissa}
    (hx : toModel x = .finite sign mantissa exponent hmantissa) :
    exponent ≤
      (FloatFormat.toModel fmt).targetExponent (Float.Model.totalExponent mantissa exponent) := by
  rw [le_targetExponent_totalExponent_iff, toModel_minExponent]
  change exponent ≤ FloatFormat.ieeeMinSubnormalExponent fmt ∨ 2 ^ fmt.fracWidth ≤ mantissa
  have hdecode := ieeeToDyadic?_eq_unpackedToDyadic?_toModel x
  rw [hx] at hdecode
  simp only [unpackedToDyadic?, ieeeToDyadic?] at hdecode
  split_ifs at hdecode
  · simp only [Option.some.injEq, FloatLib.Numerics.Dyadic.mk.injEq] at hdecode
    exact absurd hdecode.2.1.symm hmantissa.ne'
  · simp only [Option.some.injEq, FloatLib.Numerics.Dyadic.mk.injEq] at hdecode
    exact Or.inl hdecode.2.2.symm.le
  · simp only [Option.some.injEq, FloatLib.Numerics.Dyadic.mk.injEq] at hdecode
    refine Or.inr ?_
    rw [← hdecode.2.1, pow2_eq_two_pow]
    exact Nat.le_add_right _ _



theorem modelMulFinite {fmt : FloatFormat} (hfmt : fmt.isIEEE = true)
    (x y : Model fmt) (hx : (Model.toModel x).isFinite = true)
    (hy : (Model.toModel y).isFinite = true) :
    Model.mul x y =
      Model.ofModel fmt
        (Float.Model.UnpackedFloat.mul (FloatFormat.toModel fmt)
          (Model.toModel x) (Model.toModel y)) := by
  have hzero := FloatFormat.supportsSignedZero_eq_true_of_isIEEE fmt hfmt
  cases hxmodel : Model.toModel x <;> cases hymodel : Model.toModel y <;>
    simp only [hxmodel, hymodel, Float.Model.UnpackedFloat.isFinite,
      Bool.false_eq_true] at hx hy
  case zero.zero sign₁ sign₂ =>
    rw [Model.Proof.mul_eq_spec, Model.Spec.mul,
      Model.toDyadic?_ieee_eq_model fmt hfmt x,
      Model.toDyadic?_ieee_eq_model fmt hfmt y, hxmodel, hymodel]
    cases sign₁ <;> cases sign₂ <;>
      simp [Model.unpackedToDyadic?, Float.Model.UnpackedFloat.mul,
        Model.modelSignBit, Model.zero, Model.posZero_eq_ofModel_zero,
        Model.negZero_eq_ofModel_zero, hzero,
        show Sign.negative * Sign.negative = Sign.positive from rfl,
        show Sign.negative * Sign.positive = Sign.negative from rfl,
        show Sign.positive * Sign.negative = Sign.negative from rfl,
        show Sign.positive * Sign.positive = Sign.positive from rfl]
  case zero.finite sign₁ sign₂ mantissa₂ exponent₂ hmantissa₂ =>
    rw [Model.Proof.mul_eq_spec, Model.Spec.mul,
      Model.toDyadic?_ieee_eq_model fmt hfmt x,
      Model.toDyadic?_ieee_eq_model fmt hfmt y, hxmodel, hymodel]
    cases sign₁ <;> cases sign₂ <;>
      simp [Model.unpackedToDyadic?, Float.Model.UnpackedFloat.mul,
        Model.modelSignBit, Model.zero, Model.posZero_eq_ofModel_zero,
        Model.negZero_eq_ofModel_zero, hzero,
        show Sign.negative * Sign.negative = Sign.positive from rfl,
        show Sign.negative * Sign.positive = Sign.negative from rfl,
        show Sign.positive * Sign.negative = Sign.negative from rfl,
        show Sign.positive * Sign.positive = Sign.positive from rfl]
  case finite.zero sign₁ mantissa₁ exponent₁ hmantissa₁ sign₂ =>
    rw [Model.Proof.mul_eq_spec, Model.Spec.mul,
      Model.toDyadic?_ieee_eq_model fmt hfmt x,
      Model.toDyadic?_ieee_eq_model fmt hfmt y, hxmodel, hymodel]
    cases sign₁ <;> cases sign₂ <;>
      simp [Model.unpackedToDyadic?, Float.Model.UnpackedFloat.mul,
        Model.modelSignBit, Model.zero, Model.posZero_eq_ofModel_zero,
        Model.negZero_eq_ofModel_zero, hzero,
        show Sign.negative * Sign.negative = Sign.positive from rfl,
        show Sign.negative * Sign.positive = Sign.negative from rfl,
        show Sign.positive * Sign.negative = Sign.negative from rfl,
        show Sign.positive * Sign.positive = Sign.positive from rfl]
  case finite.finite sign₁ mantissa₁ exponent₁ hmantissa₁ sign₂ mantissa₂ exponent₂ hmantissa₂ =>
    have hle := add_le_targetExponent_totalExponent_mul (FloatFormat.toModel fmt)
      hmantissa₁ hmantissa₂
      (le_targetExponent_totalExponent_of_toModel_eq_finite x hxmodel)
      (le_targetExponent_totalExponent_of_toModel_eq_finite y hymodel)
    have hr (sign : Sign) :
        Float.Model.UnpackedFloat.roundWithAccuracy (FloatFormat.toModel fmt) sign
          (mantissa₁ * mantissa₂) (exponent₁ + exponent₂) .exact =
        Float.Model.UnpackedFloat.round (FloatFormat.toModel fmt) sign
          (mantissa₁ * mantissa₂) (exponent₁ + exponent₂) :=
      Model.roundWithAccuracy_exact_eq_round_of_le_targetExponent _ _ _ _ hle
    rw [Model.Proof.mul_eq_spec, Model.Spec.mul,
      Model.toDyadic?_ieee_eq_model fmt hfmt x,
      Model.toDyadic?_ieee_eq_model fmt hfmt y, hxmodel, hymodel]
    cases sign₁ <;> cases sign₂ <;>
      simp [Model.unpackedToDyadic?, Float.Model.UnpackedFloat.mul,
        Model.roundDyadic, hfmt, Model.ieeeRoundDyadic,
        Model.modelSignBit, Model.modelSign, hmantissa₁.ne', hmantissa₂.ne',
        hr,
        show Sign.negative * Sign.negative = Sign.positive from rfl,
        show Sign.negative * Sign.positive = Sign.negative from rfl,
        show Sign.positive * Sign.negative = Sign.negative from rfl,
        show Sign.positive * Sign.positive = Sign.positive from rfl]

end NativeBridge

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


namespace R2W01b

@[inline] def tableIndex (u : UInt32) : UInt32 :=
  u >>> 23

end R2W01b

namespace R2W01c

open FloatLib.Floats.Formats.BinaryInterchange
open FloatLib.Numerics
open R2W01b

theorem fields32_toDyadic (s : Bool) (e f : Nat)
    (he0 : 0 < e) (he : e < 255) (hf : f < 8388608) :
    Model.toDyadic? (Model.ofFields FloatFormat.binary32 s e f) =
      some ⟨s, 8388608 + f, (e : Int) - 150⟩ := by
  have h := Model.toDyadic?_ofFields_normal FloatFormat.binary32 s e f
    (Nat.ne_of_gt he0) he hf
  change Model.toDyadic? (Model.ofFields FloatFormat.binary32 s e f) =
    some ⟨s, 8388608 + f, (e : Int) - 127 - 23⟩ at h
  have hexp : (e : Int) - 127 - 23 = (e : Int) - 150 := by omega
  simpa only [hexp] using h

abbrev raw32 (u : UInt32) : Model FloatFormat.binary32 :=
  Model.ofUInt32 u

def wordSign (u : UInt32) : Bool :=
  decide (2147483648 ≤ u.toNat)

def wordExp (u : UInt32) : Nat :=
  u.toNat / 8388608 % 256

def wordFrac (u : UInt32) : Nat :=
  u.toNat % 8388608

theorem raw32_bits (u : UInt32) : (raw32 u).bits = u.toBitVec := by
  change BitVec.ofNat 32 u.toNat = u.toBitVec
  exact BitVec.ofNat_uInt32ToNat u

theorem raw32_sign (u : UInt32) : Model.signBit (raw32 u) = wordSign u := by
  rw [Model.signBit_eq_msb, raw32_bits]
  exact BitVec.msb_eq_decide u.toBitVec

theorem raw32_exp (u : UInt32) : Model.expField (raw32 u) = wordExp u := by
  unfold Model.expField
  rw [raw32_bits]
  change ((u.toBitVec >>> 23) &&& (BitVec.ofNat 32 255)).toNat = wordExp u
  rw [BitVec.toNat_and, BitVec.toNat_ushiftRight]
  change (u.toNat >>> 23) &&& (2 ^ 8 - 1) = u.toNat / 8388608 % 256
  rw [Nat.and_two_pow_sub_one_eq_mod, Nat.shiftRight_eq_div_pow]

theorem raw32_frac (u : UInt32) : Model.fracField (raw32 u) = wordFrac u := by
  unfold Model.fracField
  rw [raw32_bits]
  change (u.toBitVec &&& (BitVec.ofNat 32 8388607)).toNat = wordFrac u
  rw [BitVec.toNat_and]
  change u.toNat &&& (2 ^ 23 - 1) = u.toNat % 2 ^ 23
  exact Nat.and_two_pow_sub_one_eq_mod u.toNat 23

theorem raw32_eq_fields (u : UInt32) :
    raw32 u = Model.ofFields FloatFormat.binary32 (wordSign u) (wordExp u)
      (wordFrac u) := by
  rw [← raw32_sign, ← raw32_exp, ← raw32_frac]
  exact (Model.ofFields_signBit_expField_fracField (raw32 u)).symm

theorem wordFrac_lt (u : UInt32) : wordFrac u < 8388608 :=
  Nat.mod_lt _ (by decide)

theorem tableIndex_nat (u : UInt32) :
    (tableIndex u).toNat = u.toNat / 8388608 := by
  rw [tableIndex, UInt32.toNat_shiftRight]
  change u.toNat >>> 23 = u.toNat / 8388608
  exact Nat.shiftRight_eq_div_pow u.toNat 23

theorem tableExp_nat (u : UInt32) :
    (tableIndex u &&& 255).toNat = wordExp u := by
  rw [UInt32.toNat_and, tableIndex_nat]
  change (u.toNat / 8388608) &&& (2 ^ 8 - 1) =
    u.toNat / 8388608 % 2 ^ 8
  exact Nat.and_two_pow_sub_one_eq_mod _ 8

end R2W01c


/-
R24 portable UInt64 quotient certificate. This is a helper-only probe;
the retained B2 public endpoints are unchanged.

The RNE expression in `rounded` is adapted from FloatLib Team's MIT-licensed
FloatLib/Kernels/FixedWord/Core/Runtime.lean, fixed revision
0d91825727839f597fd06b22fdd038ea21480f0c (blob71d1bf2462da2cf1d6eff8b8fc3580fb681400b4).
The candidate guess is arbitrary; no native floating-point equation is assumed.
-/
namespace Submission.R24QuotientCertificate

@[inline] def check (n d q : UInt64) : Bool :=
  if n < (0x2000000000000 : UInt64) ∧ 0 < d ∧
      d < (0x2000000 : UInt64) ∧ q < (0x2000000 : UInt64) then
    decide (q * d ≤ n) && decide (n - q * d < d)
  else false

@[inline] def rounded (n d q : UInt64) : UInt64 :=
  let remainder := n - q * d
  let complement := d - remainder
  if remainder < complement then q
  else if complement < remainder then q + 1
  else if q % 2 == 0 then q
  else q + 1

/-- The checked machine product/subtraction determine the exact quotient and remainder. -/
theorem checker_sound (n d q : UInt64) (h : check n d q = true) :
    q.toNat = n.toNat / d.toNat ∧
      (n - q * d).toNat = n.toNat % d.toNat := by
  have hfit : n < (0x2000000000000 : UInt64) ∧ 0 < d ∧
      d < (0x2000000 : UInt64) ∧ q < (0x2000000 : UInt64) := by
    by_contra hbad
    simp [check, hbad] at h
  have hchecks : q * d ≤ n ∧ n - q * d < d := by
    simpa only [check, if_pos hfit, Bool.and_eq_true, decide_eq_true_eq] using h
  have hdpos : 0 < d.toNat := UInt64.lt_iff_toNat_lt.mp hfit.2.1
  have hdcap : d.toNat < 33554432 := UInt64.lt_iff_toNat_lt.mp hfit.2.2.1
  have hqcap : q.toNat < 33554432 := UInt64.lt_iff_toNat_lt.mp hfit.2.2.2
  have hproduct50 : q.toNat * d.toNat < 1125899906842624 := by
    calc
      q.toNat * d.toNat < 33554432 * 33554432 := Nat.mul_lt_mul'' hqcap hdcap
      _ = 1125899906842624 := by decide
  have hproductFit : q.toNat * d.toNat < UInt64.size := by
    change q.toNat * d.toNat < 18446744073709551616
    omega
  have hproduct : (q * d).toNat = q.toNat * d.toNat := by
    rw [UInt64.toNat_mul, Nat.mod_eq_of_lt hproductFit]
  have hproductLe : q.toNat * d.toNat ≤ n.toNat := by
    have hh := UInt64.le_iff_toNat_le.mp hchecks.1
    simpa only [hproduct] using hh
  have hremainder : (n - q * d).toNat = n.toNat - q.toNat * d.toNat := by
    rw [UInt64.toNat_sub_of_le _ _ hchecks.1, hproduct]
  have hremainderLt : n.toNat - q.toNat * d.toNat < d.toNat := by
    have hh := UInt64.lt_iff_toNat_lt.mp hchecks.2
    simpa only [hremainder] using hh
  have hdecomposition :
      q.toNat * d.toNat + (n.toNat - q.toNat * d.toNat) = n.toNat := by omega
  have hunique : n.toNat / d.toNat = q.toNat ∧
      n.toNat % d.toNat = n.toNat - q.toNat * d.toNat :=
    (Nat.div_mod_unique hdpos).2 <| by
      refine ⟨?_, hremainderLt⟩
      simpa only [Nat.add_comm, Nat.mul_comm] using hdecomposition
  exact ⟨hunique.1.symm, hremainder.trans hunique.2.symm⟩

/-- A checked guess can feed the existing word RNE expression without performing division. -/
theorem rounded_toNat (n d q : UInt64) (h : check n d q = true) :
    (rounded n d q).toNat = FloatLib.Numerics.roundQuotientEven n.toNat d.toNat := by
  have hfit : n < (0x2000000000000 : UInt64) ∧ 0 < d ∧
      d < (0x2000000 : UInt64) ∧ q < (0x2000000 : UInt64) := by
    by_contra hbad
    simp [check, hbad] at h
  have hqr := checker_sound n d q h
  have hquotient : q = n / d := by
    apply UInt64.toNat_inj.mp
    simpa only [UInt64.toNat_div] using hqr.1
  have hremainder : n - q * d = n % d := by
    apply UInt64.toNat_inj.mp
    simpa only [UInt64.toNat_mod] using hqr.2
  have hden : d ≠ 0 := by
    intro hzero
    have hpositive : 0 < d.toNat := UInt64.lt_iff_toNat_lt.mp hfit.2.1
    have hzeroNat : d.toNat = 0 := by
      simpa only [UInt64.toNat_zero] using congrArg UInt64.toNat hzero
    omega
  have hqcap : q.toNat < 33554432 := UInt64.lt_iff_toNat_lt.mp hfit.2.2.2
  have hquotientFit : n.toNat / d.toNat + 1 < 2 ^ 64 := by
    rw [← hqr.1]
    change q.toNat + 1 < 18446744073709551616
    omega
  have hword : rounded n d q = FloatLib.Numerics.FixedWord.roundQuotientEven n d := by
    unfold rounded
    rw [hremainder, hquotient]
    simp only [FloatLib.Numerics.FixedWord.roundQuotientEven, beq_iff_eq, hden, ite_false]
  rw [hword]
  exact FloatLib.Numerics.FixedWord.roundQuotientEven_toNat n d hden hquotientFit

end Submission.R24QuotientCertificate


/- R24 portable mathematical primitive. Old ContractTensor/B2 only.
   Real FloatLib quotient and binary32 word-rounder conclusions; NOT_COMPILED.
   Public interfaces remain unchanged; no native assumption or abstract hcell input. -/
namespace Submission.R24CellPrimitive

open FloatLib.Floats FloatLib.Floats.Formats.BinaryInterchange

theorem quotient_strict_midpoint (num den mant : Nat)
    (hd : 0 < den) (hm : 0 < mant)
    (hl : den * (2 * mant - 1) < 2 * num)
    (hu : 2 * num < den * (2 * mant + 1)) :
    FloatLib.Numerics.roundQuotientEven num den = mant := by
  cases mant with
  | zero => omega
  | succ k =>
    have hleft : 2 * (k + 1) - 1 = 2 * k + 1 := by omega
    have hright : 2 * (k + 1) + 1 = 2 * k + 3 := by omega
    rw [hleft] at hl
    rw [hright] at hu
    have hlo : k * den ≤ num := by nlinarith
    have hhi : num < (k + 2) * den := by nlinarith
    have hql : k ≤ num / den := (Nat.le_div_iff_mul_le hd).2 hlo
    have hqu : num / den < k + 2 := (Nat.div_lt_iff_lt_mul hd).2 hhi
    have hdiv := Nat.mod_add_div num den
    have hcases : num / den = k ∨ num / den = k + 1 := by omega
    rcases hcases with hq | hq
    · have hr : den < 2 * (num % den) := by rw [hq] at hdiv; nlinarith
      have hn : ¬ 2 * (num % den) < den := by omega
      simp [FloatLib.Numerics.roundQuotientEven, hq, hn, hr]
    · have hr : 2 * (num % den) < den := by rw [hq] at hdiv; nlinarith
      simp [FloatLib.Numerics.roundQuotientEven, hq, hr]

theorem quotient_even_closed_midpoint (num den mant : Nat)
    (hd : 0 < den) (hm : 0 < mant) (heven : mant % 2 = 0)
    (hl : den * (2 * mant - 1) ≤ 2 * num)
    (hu : 2 * num ≤ den * (2 * mant + 1)) :
    FloatLib.Numerics.roundQuotientEven num den = mant := by
  cases mant with
  | zero => omega
  | succ k =>
    have hleft : 2 * (k + 1) - 1 = 2 * k + 1 := by omega
    have hright : 2 * (k + 1) + 1 = 2 * k + 3 := by omega
    rw [hleft] at hl
    rw [hright] at hu
    have hlo : k * den ≤ num := by nlinarith
    have hhi : num < (k + 2) * den := by nlinarith
    have hql : k ≤ num / den := (Nat.le_div_iff_mul_le hd).2 hlo
    have hqu : num / den < k + 2 := (Nat.div_lt_iff_lt_mul hd).2 hhi
    have hdiv := Nat.mod_add_div num den
    have hcases : num / den = k ∨ num / den = k + 1 := by omega
    rcases hcases with hq | hq
    · have hr : den ≤ 2 * (num % den) := by rw [hq] at hdiv; nlinarith
      have hn : ¬ 2 * (num % den) < den := by omega
      by_cases hs : den < 2 * (num % den)
      · simp [FloatLib.Numerics.roundQuotientEven, hq, hn, hs]
      · have he : 2 * (num % den) = den := by omega
        have hk : k % 2 = 1 := by omega
        simp [FloatLib.Numerics.roundQuotientEven, hq, he, hk]
    · have hr : 2 * (num % den) ≤ den := by rw [hq] at hdiv; nlinarith
      by_cases hs : 2 * (num % den) < den
      · simp [FloatLib.Numerics.roundQuotientEven, hq, hs]
      · have he : 2 * (num % den) = den := by omega
        simp [FloatLib.Numerics.roundQuotientEven, hq, he, heven]

@[inline] def strictCell (num den mant : Nat) : Bool :=
  decide (0 < den ∧ 0 < mant ∧ den * (2 * mant - 1) < 2 * num ∧
    2 * num < den * (2 * mant + 1))

theorem strictCell_sound (num den mant : Nat) (h : strictCell num den mant = true) :
    FloatLib.Numerics.roundQuotientEven num den = mant := by
  have hh : 0 < den ∧ 0 < mant ∧ den * (2 * mant - 1) < 2 * num ∧
      2 * num < den * (2 * mant + 1) := of_decide_eq_true h
  exact quotient_strict_midpoint num den mant hh.1 hh.2.1 hh.2.2.1 hh.2.2.2

theorem normal_ratio_nat_bounds (num den mant : Nat)
    (hd : 0 < den) (hmlo : 8388608 < mant) (hmhi : mant < 16777216)
    (hl : den * (2 * mant - 1) < 2 * num)
    (hu : 2 * num < den * (2 * mant + 1)) :
    8388608 * den ≤ num ∧ num < 16777216 * den := by
  have hmlo' : 8388609 ≤ mant := by omega
  have hmhi' : mant ≤ 16777215 := by omega
  have hscaleL := Nat.mul_le_mul_right den hmlo'
  have hscaleU := Nat.mul_le_mul_right den hmhi'
  have hcut : 2 * mant - 1 + 1 = 2 * mant := by omega
  have hexpand : den * (2 * mant - 1) + den = 2 * (mant * den) := by
    calc
      den * (2 * mant - 1) + den = den * ((2 * mant - 1) + 1) := by ring
      _ = den * (2 * mant) := by rw [hcut]
      _ = 2 * (mant * den) := by ring
  constructor <;> nlinarith

theorem normal_ratio_log23 (num den mant : Nat)
    (hd : 0 < den) (hmlo : 8388608 < mant) (hmhi : mant < 16777216)
    (hl : den * (2 * mant - 1) < 2 * num)
    (hu : 2 * num < den * (2 * mant + 1)) :
    FloatLib.Numerics.RationalBinary.floorLog2 num den = 23 := by
  obtain ⟨hlo, hhi⟩ := normal_ratio_nat_bounds num den mant hd hmlo hmhi hl hu
  have hn : num ≠ 0 := by intro h; subst num; nlinarith
  have hdr : (0 : Real) < den := by exact_mod_cast hd
  have hlr : (8388608 : Real) ≤ (num : Real) / den := by
    apply (le_div_iff₀ hdr).2
    exact_mod_cast hlo
  have hur : (num : Real) / den < (16777216 : Real) := by
    apply (div_lt_iff₀ hdr).2
    exact_mod_cast hhi
  apply Model.floorLog2_eq_of_bounds num den 23 hn (Nat.ne_of_gt hd)
  · have hp : Model.bpow (23 : Int) = (8388608 : Real) := by
      norm_num [Model.bpow, FloatLib.Floats.Formats.Flocq.bpow,
        FloatLib.Numerics.binaryRadix, FloatLib.Numerics.Radix.toReal]
    simpa only [hp] using hlr
  · have hp : Model.bpow ((23 : Int) + 1) = (16777216 : Real) := by
      norm_num [Model.bpow, FloatLib.Floats.Formats.Flocq.bpow,
        FloatLib.Numerics.binaryRadix, FloatLib.Numerics.Radix.toReal]
    simpa only [hp] using hur

theorem native32_strict_cell (sign : Bool) (num den mant : Nat) (exponent : Int)
    (hd : 0 < den) (hmlo : 8388608 < mant) (hmhi : mant < 16777216)
    (hexplo : 1 ≤ exponent + 150) (hexphi : exponent + 150 ≤ 254)
    (hl : den * (2 * mant - 1) < 2 * num)
    (hu : 2 * num < den * (2 * mant + 1)) :
    Model.NativeBinary32.roundRatScaled sign num den exponent =
      Model.NativeBinary32.mkBits sign (exponent + 150).toNat (mant - 8388608) := by
  have hn : num ≠ 0 := by
    have hb := (normal_ratio_nat_bounds num den mant hd hmlo hmhi hl hu).1
    intro h; subst num; nlinarith
  have hlog := normal_ratio_log23 num den mant hd hmlo hmhi hl hu
  have hr := quotient_strict_midpoint num den mant hd (by omega) hl hu
  have hbig : ¬ (23 : Int) + exponent > 127 := by omega
  have hsmall : ¬ (23 : Int) + exponent < -150 := by omega
  have hnormal : ¬ (23 : Int) + exponent < -126 := by omega
  have hp23 : Model.pow2 23 = 8388608 := by decide
  have hp24 : Model.pow2 24 = 16777216 := by decide
  have hc : mant ≠ Model.pow2 24 := by rw [hp24]; omega
  have hencoded : (23 : Int) + exponent + 127 = exponent + 150 := by omega
  have hround : Model.NativeBinary32.roundRatScaled sign num den exponent =
      Model.NativeBinary32.mkBits sign ((23 : Int) + exponent + 127).toNat
        (mant - Model.pow2 23) := by
    simp only [Model.NativeBinary32.roundRatScaled, beq_iff_eq,
      Nat.ne_of_gt hd, hn, if_false, hlog, hbig, hsmall, hnormal,
      sub_self, FloatLib.Numerics.RationalBinary.scaleByPowerOfTwo_zero,
      Prod.fst, Prod.snd]
    rw [hr]
    simp only [hr, beq_iff_eq, hc, if_false, hbig]
  simpa only [hp23, hencoded] using hround

@[inline] def normalStrictCell (num den mant : Nat) (exponent : Int) : Bool :=
  decide (0 < den ∧ 8388608 < mant ∧ mant < 16777216 ∧
    1 ≤ exponent + 150 ∧ exponent + 150 ≤ 254 ∧
    den * (2 * mant - 1) < 2 * num ∧ 2 * num < den * (2 * mant + 1))

theorem normalStrictCell_sound (sign : Bool) (num den mant : Nat) (exponent : Int)
    (h : normalStrictCell num den mant exponent = true) :
    Model.NativeBinary32.roundRatScaled sign num den exponent =
      Model.NativeBinary32.mkBits sign (exponent + 150).toNat (mant - 8388608) := by
  have hh : 0 < den ∧ 8388608 < mant ∧ mant < 16777216 ∧
      1 ≤ exponent + 150 ∧ exponent + 150 ≤ 254 ∧
      den * (2 * mant - 1) < 2 * num ∧ 2 * num < den * (2 * mant + 1) :=
    of_decide_eq_true h
  exact native32_strict_cell sign num den mant exponent hh.1 hh.2.1 hh.2.2.1
    hh.2.2.2.1 hh.2.2.2.2.1 hh.2.2.2.2.2.1 hh.2.2.2.2.2.2

end Submission.R24CellPrimitive


/- R24 exact power-of-two rounding cells. Old ContractTensor mathematics only.
   New proofs are NOT_COMPILED. The quotient tie lemma is reused from broad.
   No native proposal accuracy or abstract rounding-cell premise is assumed. -/
namespace Submission.R24PowerCell
open FloatLib.Floats FloatLib.Floats.Formats.BinaryInterchange

theorem common_bounds (num den : Nat) (hd : 0 < den)
    (hl : den * 16777215 ≤ 2 * num)
    (hu : 2 * num ≤ den * 16777217) :
    4194304 * den ≤ num ∧ num < 16777216 * den := by
  constructor <;> omega

theorem ratio_log22 (num den : Nat) (hd : 0 < den)
    (hl : 4194304 * den ≤ num) (hu : num < 8388608 * den) :
    FloatLib.Numerics.RationalBinary.floorLog2 num den = 22 := by
  have hn : num ≠ 0 := by intro h; subst num; omega
  have hdr : (0 : Real) < den := by exact_mod_cast hd
  have hlr : (4194304 : Real) ≤ (num : Real) / den := by
    apply (le_div_iff₀ hdr).2
    exact_mod_cast hl
  have hur : (num : Real) / den < (8388608 : Real) := by
    apply (div_lt_iff₀ hdr).2
    exact_mod_cast hu
  apply Model.floorLog2_eq_of_bounds num den 22 hn (Nat.ne_of_gt hd)
  · have hp : Model.bpow (22 : Int) = (4194304 : Real) := by
      norm_num [Model.bpow, FloatLib.Floats.Formats.Flocq.bpow,
        FloatLib.Numerics.binaryRadix, FloatLib.Numerics.Radix.toReal]
    simpa only [hp] using hlr
  · have hp : Model.bpow ((22 : Int) + 1) = (8388608 : Real) := by
      norm_num [Model.bpow, FloatLib.Floats.Formats.Flocq.bpow,
        FloatLib.Numerics.binaryRadix, FloatLib.Numerics.Radix.toReal]
    simpa only [hp] using hur

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

theorem native32_power_above_min (sign : Bool) (num den : Nat) (exponent : Int)
    (hd : 0 < den) (he0 : 2 ≤ exponent + 150) (he1 : exponent + 150 ≤ 254)
    (hl : den * 33554431 ≤ 4 * num)
    (hu : 2 * num ≤ den * 16777217) :
    Model.NativeBinary32.roundRatScaled sign num den exponent =
      Model.NativeBinary32.mkBits sign (exponent + 150).toNat 0 := by
  have hlold : den * 16777215 ≤ 2 * num := by omega
  have hb := common_bounds num den hd hlold hu
  have hn : num ≠ 0 := by intro h; subst num; omega
  have hp23 : Model.pow2 23 = 8388608 := by decide
  have hp24 : Model.pow2 24 = 16777216 := by decide
  by_cases hregion : 8388608 * den ≤ num
  · have hlog := ratio_log23 num den hd hregion hb.2
    have hq := R24CellPrimitive.quotient_even_closed_midpoint num den 8388608
      hd (by decide) (by decide) hlold hu
    have hbig : ¬ (23 : Int) + exponent > 127 := by omega
    have hsmall : ¬ (23 : Int) + exponent < -150 := by omega
    have hnormal : ¬ (23 : Int) + exponent < -126 := by omega
    have hencoded : (23 : Int) + exponent + 127 = exponent + 150 := by omega
    have hround : Model.NativeBinary32.roundRatScaled sign num den exponent =
        Model.NativeBinary32.mkBits sign ((23 : Int) + exponent + 127).toNat
          (8388608 - Model.pow2 23) := by
      simp only [Model.NativeBinary32.roundRatScaled, beq_iff_eq,
        Nat.ne_of_gt hd, hn, if_false, hlog, hbig, hsmall, hnormal,
        sub_self, FloatLib.Numerics.RationalBinary.scaleByPowerOfTwo_zero,
        Prod.fst, Prod.snd]
      rw [hq]
      norm_num [hq, hp23, hp24, hbig]
    simpa only [hp23, hencoded, Nat.sub_self] using hround
  · have hregion' : num < 8388608 * den := by omega
    have hlog := ratio_log22 num den hd hb.1 hregion'
    have hq : FloatLib.Numerics.roundQuotientEven (num * 2) den = 16777216 := by
      apply R24CellPrimitive.quotient_even_closed_midpoint (num * 2) den 16777216
        hd (by decide) (by decide)
      · omega
      · omega
    have hbig : ¬ (22 : Int) + exponent > 127 := by omega
    have hsmall : ¬ (22 : Int) + exponent < -150 := by omega
    have hnormal : ¬ (22 : Int) + exponent < -126 := by omega
    have hlast : ¬ (22 : Int) + exponent + 1 > 127 := by omega
    have hscaled : FloatLib.Numerics.RationalBinary.scaleByPowerOfTwo num den
        ((23 : Int) - 22) = (num * 2, den) := by
      norm_num [FloatLib.Numerics.RationalBinary.scaleByPowerOfTwo, Nat.shiftLeft_eq]
    have hencoded : (22 : Int) + exponent + 1 + 127 = exponent + 150 := by omega
    have hround : Model.NativeBinary32.roundRatScaled sign num den exponent =
        Model.NativeBinary32.mkBits sign ((22 : Int) + exponent + 1 + 127).toNat 0 := by
      simp only [Model.NativeBinary32.roundRatScaled, beq_iff_eq,
        Nat.ne_of_gt hd, hn, if_false, hlog, hbig, hsmall, hnormal,
        hscaled, Prod.fst, Prod.snd]
      rw [hq]
      norm_num [hq, hp23, hp24, hlast]
    simpa only [hencoded] using hround

theorem native32_min_normal (sign : Bool) (num den : Nat) (hd : 0 < den)
    (hl : den * 16777215 ≤ 2 * num)
    (hu : 2 * num ≤ den * 16777217) :
    Model.NativeBinary32.roundRatScaled sign num den (-149) =
      Model.NativeBinary32.mkBits sign 1 0 := by
  have hb := common_bounds num den hd hl hu
  have hn : num ≠ 0 := by intro h; subst num; omega
  have hq := R24CellPrimitive.quotient_even_closed_midpoint num den 8388608
    hd (by decide) (by decide) hl hu
  have hp23 : Model.pow2 23 = 8388608 := by decide
  have hp24 : Model.pow2 24 = 16777216 := by decide
  by_cases hregion : 8388608 * den ≤ num
  · have hlog := ratio_log23 num den hd hregion hb.2
    simp [Model.NativeBinary32.roundRatScaled, Nat.ne_of_gt hd, hn, hlog,
      hq, hp23, hp24, FloatLib.Numerics.RationalBinary.scaleByPowerOfTwo]
  · have hregion' : num < 8388608 * den := by omega
    have hlog := ratio_log22 num den hd hb.1 hregion'
    simp [Model.NativeBinary32.roundRatScaled, Nat.ne_of_gt hd, hn, hlog,
      hq, hp23, hp24, FloatLib.Numerics.RationalBinary.scaleByPowerOfTwo]

@[inline] def powerCell (num den : Nat) (exponent : Int) : Bool :=
  decide (0 < den ∧ 1 ≤ exponent + 150 ∧ exponent + 150 ≤ 254 ∧
    (if exponent + 150 = 1 then den * 16777215 ≤ 2 * num
      else den * 33554431 ≤ 4 * num) ∧ 2 * num ≤ den * 16777217)

theorem powerCell_sound (sign : Bool) (num den : Nat) (exponent : Int)
    (h : powerCell num den exponent = true) :
    Model.NativeBinary32.roundRatScaled sign num den exponent =
      Model.NativeBinary32.mkBits sign (exponent + 150).toNat 0 := by
  have hh : 0 < den ∧ 1 ≤ exponent + 150 ∧ exponent + 150 ≤ 254 ∧
      (if exponent + 150 = 1 then den * 16777215 ≤ 2 * num
        else den * 33554431 ≤ 4 * num) ∧ 2 * num ≤ den * 16777217 :=
    of_decide_eq_true h
  rcases hh with ⟨hd, he0, he1, hl, hu⟩
  by_cases hmin : exponent + 150 = 1
  · have hl' : den * 16777215 ≤ 2 * num := by simpa [hmin] using hl
    have he : exponent = -149 := by omega
    simpa [he] using native32_min_normal sign num den hd hl' hu
  · have hl' : den * 33554431 ≤ 4 * num := by simpa [hmin] using hl
    exact native32_power_above_min sign num den exponent hd (by omega) he1 hl' hu

end Submission.R24PowerCell


/- R24 portable binary32-to-native-binary64 component. Normal values and
   signed zeros only; nonzero subnormals and exponent-255 words are outside
   Domain. Public B2 endpoints are unchanged. All new proofs are NOT_RUN. -/
namespace Submission.R24RepresentationWiden
open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange
open R2W01c

@[inline] def expWord (u : UInt32) : UInt32 := (u >>> 23) &&& 255
@[inline] def fracWord (u : UInt32) : UInt32 := u &&& 0x7fffff
@[inline] def signWord (u : UInt32) : UInt64 := (u.toUInt64 >>> 31) <<< 63
@[inline] def expWide (u : UInt32) : UInt64 := (expWord u).toUInt64 + 896

@[inline] def widenBits (u : UInt32) : UInt64 :=
  if expWord u = 0 then signWord u
  else signWord u ||| (expWide u <<< 52) ||| ((fracWord u).toUInt64 <<< 29)

@[inline] def value (u : UInt32) : Float := Float.ofBits (widenBits u)

def Domain (u : UInt32) : Prop :=
  (0 < wordExp u ∧ wordExp u < 255) ∨ (wordExp u = 0 ∧ wordFrac u = 0)

abbrev raw64 (w : UInt64) : Model FloatFormat.binary64 := Model.ofBits w.toBitVec
abbrev native64 (x : Float) : Model FloatFormat.binary64 := Model.ofFloatModel x.toModel

theorem expWord_toNat (u : UInt32) : (expWord u).toNat = wordExp u := by
  exact tableExp_nat u

theorem fracWord_toNat (u : UInt32) : (fracWord u).toNat = wordFrac u := by
  rw [fracWord, UInt32.toNat_and]
  change u.toNat &&& (2 ^ 23 - 1) = u.toNat % 2 ^ 23
  exact Nat.and_two_pow_sub_one_eq_mod u.toNat 23

theorem wordExp_lt (u : UInt32) : wordExp u < 256 := Nat.mod_lt _ (by decide)

theorem signWord_toNat (u : UInt32) :
    (signWord u).toNat = u.toNat / 2147483648 * 9223372036854775808 := by
  rw [signWord, UInt64.toNat_shiftLeft, UInt64.toNat_shiftRight, UInt32.toNat_toUInt64]
  change ((u.toNat >>> 31) <<< 63) % 18446744073709551616 = _
  rw [Nat.shiftRight_eq_div_pow, Nat.shiftLeft_eq]
  have hu := u.toNat_lt_size
  change u.toNat < 4294967296 at hu
  omega

theorem expWide_toNat (u : UInt32) : (expWide u).toNat = wordExp u + 896 := by
  rw [expWide, UInt64.toNat_add, UInt32.toNat_toUInt64, expWord_toNat]
  have he := wordExp_lt u
  change (wordExp u + 896) % 18446744073709551616 = _
  omega

theorem expWide_shift_toNat (u : UInt32) :
    (expWide u <<< 52).toNat = (wordExp u + 896) * 4503599627370496 := by
  rw [UInt64.toNat_shiftLeft, expWide_toNat]
  change ((wordExp u + 896) <<< 52) % 18446744073709551616 = _
  rw [Nat.shiftLeft_eq]
  have he := wordExp_lt u
  omega

theorem fracWide_shift_toNat (u : UInt32) :
    ((fracWord u).toUInt64 <<< 29).toNat = wordFrac u * 536870912 := by
  rw [UInt64.toNat_shiftLeft, UInt32.toNat_toUInt64, fracWord_toNat]
  change (wordFrac u <<< 29) % 18446744073709551616 = _
  rw [Nat.shiftLeft_eq]
  have hf := wordFrac_lt u
  omega

theorem widenBits_normal_toNat (u : UInt32) (he0 : 0 < wordExp u) :
    (widenBits u).toNat = u.toNat / 2147483648 * 9223372036854775808 +
      (wordExp u + 896) * 4503599627370496 + wordFrac u * 536870912 := by
  have hne : expWord u ≠ 0 := by
    intro h
    have hh := expWord_toNat u
    rw [h] at hh
    change 0 = wordExp u at hh
    omega
  unfold widenBits
  rw [if_neg hne, UInt64.toNat_or, UInt64.toNat_or, signWord_toNat,
    expWide_shift_toNat, fracWide_shift_toNat]
  have he := wordExp_lt u
  have hf := wordFrac_lt u
  have hE : (wordExp u + 896) * 4503599627370496 < 2 ^ 63 := by
    change (wordExp u + 896) * 4503599627370496 < 9223372036854775808
    omega
  have hF : wordFrac u * 536870912 < 2 ^ 52 := by
    change wordFrac u * 536870912 < 4503599627370496
    omega
  have hSE :
      (u.toNat / 2147483648 * 9223372036854775808) |||
          ((wordExp u + 896) * 4503599627370496) =
        u.toNat / 2147483648 * 9223372036854775808 +
          (wordExp u + 896) * 4503599627370496 := by
    rw [Nat.mul_comm (u.toNat / 2147483648) 9223372036854775808]
    exact (Nat.two_pow_add_eq_or_of_lt hE (u.toNat / 2147483648)).symm
  rw [hSE]
  have hbase : u.toNat / 2147483648 * 9223372036854775808 +
      (wordExp u + 896) * 4503599627370496 =
        2 ^ 52 * (u.toNat / 2147483648 * 2048 + wordExp u + 896) := by
    change _ = 4503599627370496 * _
    omega
  rw [hbase]
  exact (Nat.two_pow_add_eq_or_of_lt hF _).symm

theorem raw64_bits (w : UInt64) : (raw64 w).bits = w.toBitVec := rfl

theorem raw64_sign (w : UInt64) :
    Model.signBit (raw64 w) = decide (9223372036854775808 ≤ w.toNat) := by
  rw [Model.signBit_eq_msb, raw64_bits]
  exact BitVec.msb_eq_decide w.toBitVec

theorem raw64_exp (w : UInt64) :
    Model.expField (raw64 w) = w.toNat / 4503599627370496 % 2048 := by
  unfold Model.expField
  rw [raw64_bits]
  change ((w.toBitVec >>> 52) &&& (BitVec.ofNat 64 2047)).toNat = _
  rw [BitVec.toNat_and, BitVec.toNat_ushiftRight]
  change (w.toNat >>> 52) &&& (2 ^ 11 - 1) = w.toNat / 4503599627370496 % 2 ^ 11
  rw [Nat.and_two_pow_sub_one_eq_mod, Nat.shiftRight_eq_div_pow]

theorem raw64_frac (w : UInt64) :
    Model.fracField (raw64 w) = w.toNat % 4503599627370496 := by
  unfold Model.fracField
  rw [raw64_bits]
  change (w.toBitVec &&& (BitVec.ofNat 64 4503599627370495)).toNat = _
  rw [BitVec.toNat_and]
  change w.toNat &&& (2 ^ 52 - 1) = w.toNat % 2 ^ 52
  exact Nat.and_two_pow_sub_one_eq_mod w.toNat 52

theorem raw64_eq_fields (w : UInt64) :
    raw64 w = Model.ofFields FloatFormat.binary64
      (decide (9223372036854775808 ≤ w.toNat))
      (w.toNat / 4503599627370496 % 2048) (w.toNat % 4503599627370496) := by
  rw [← raw64_sign, ← raw64_exp, ← raw64_frac]
  exact (Model.ofFields_signBit_expField_fracField (raw64 w)).symm

theorem widenBits_normal_fields (u : UInt32) (he0 : 0 < wordExp u) :
    raw64 (widenBits u) = Model.ofFields FloatFormat.binary64 (wordSign u)
      (wordExp u + 896) (wordFrac u * 536870912) := by
  have hw := widenBits_normal_toNat u he0
  have hu := u.toNat_lt_size
  change u.toNat < 4294967296 at hu
  have he := wordExp_lt u
  have hf := wordFrac_lt u
  have hs : decide (9223372036854775808 ≤ (widenBits u).toNat) = wordSign u := by
    apply Bool.eq_iff_iff.mpr
    simp only [wordSign, decide_eq_true_eq]
    rw [hw]
    omega
  have hE : (widenBits u).toNat / 4503599627370496 % 2048 = wordExp u + 896 := by
    rw [hw]
    omega
  have hF : (widenBits u).toNat % 4503599627370496 = wordFrac u * 536870912 := by
    rw [hw]
    omega
  rw [raw64_eq_fields, hs, hE, hF]

theorem normal_decode (u : UInt32) (hn : 0 < wordExp u ∧ wordExp u < 255) :
    Model.toDyadic? (raw64 (widenBits u)) =
      some ⟨wordSign u, (8388608 + wordFrac u) * 536870912,
        (wordExp u : Int) - 150 - 29⟩ := by
  rw [widenBits_normal_fields u hn.1]
  have hf := wordFrac_lt u
  have h := Model.toDyadic?_ofFields_normal FloatFormat.binary64
    (wordSign u) (wordExp u + 896) (wordFrac u * 536870912)
    (by omega) (by change wordExp u + 896 < 2047; omega)
    (by change wordFrac u * 536870912 < 4503599627370496; omega)
  change Model.toDyadic? (Model.ofFields FloatFormat.binary64 (wordSign u)
    (wordExp u + 896) (wordFrac u * 536870912)) =
    some ⟨wordSign u, 4503599627370496 + wordFrac u * 536870912,
      ((wordExp u + 896 : Nat) : Int) - 1023 - 52⟩ at h
  have hm : 4503599627370496 + wordFrac u * 536870912 =
      (8388608 + wordFrac u) * 536870912 := by omega
  have hexp : ((wordExp u + 896 : Nat) : Int) - 1023 - 52 =
      (wordExp u : Int) - 150 - 29 := by omega
  simpa only [hm, hexp] using h

theorem zero_word_cases (u : UInt32) (he : wordExp u = 0) (hf : wordFrac u = 0) :
    u = 0 ∨ u = 0x80000000 := by
  have hu := u.toNat_lt_size
  change u.toNat < 4294967296 at hu
  have hz : u.toNat = 0 ∨ u.toNat = 2147483648 := by
    unfold wordExp at he
    unfold wordFrac at hf
    omega
  rcases hz with hz | hz
  · left; apply UInt32.toNat_inj.mp; exact hz
  · right; apply UInt32.toNat_inj.mp; exact hz

theorem widenBits_posZero : widenBits 0 = 0 := by decide
theorem widenBits_negZero : widenBits 0x80000000 = 0x8000000000000000 := by decide

theorem raw_finite (u : UInt32) (h : Domain u) :
    Model.isFinite (raw64 (widenBits u)) = true := by
  rcases h with hn | hz
  · exact Model.isFinite_eq_true_of_toDyadic?_some (normal_decode u hn)
  · rcases zero_word_cases u hz.1 hz.2 with rfl | rfl
    · rw [widenBits_posZero]
      change Model.isFinite (Model.zero FloatFormat.binary64 false) = true
      simp
    · rw [widenBits_negZero]
      change Model.isFinite (Model.zero FloatFormat.binary64 true) = true
      simp

theorem native_ofBits_of_decode (w : UInt64) {d : FloatLib.Numerics.Dyadic}
    (hd : Model.toDyadic? (raw64 w) = some d) :
    native64 (Float.ofBits w) = raw64 w := by
  have hc : Model.IsModelCanonical (raw64 w) :=
    R2W01c.modelCanonical_of_decode (by decide) (raw64 w) hd
  change Model.ofFloatModel
    (ExecFloat.Binary.toFloat (ExecFloat.Binary.ofBits64 w)).toModel = raw64 w
  rw [ExecFloat.Binary.toModel_toFloat_eq, Model.ofFloatModel_toFloatModel]
  exact Model.canonicalizeModel_eq_self _ hc

theorem native_model (u : UInt32) (h : Domain u) :
    native64 (value u) = raw64 (widenBits u) := by
  obtain ⟨d, hd⟩ := Model.exists_toDyadic?_of_isFinite (raw_finite u h)
  exact native_ofBits_of_decode _ hd

theorem native_finite_of_decode (x : Float) {d : FloatLib.Numerics.Dyadic}
    (hd : Model.toDyadic? (native64 x) = some d) : x.isFinite = true := by
  rw [Model.toDyadic?_ieee_eq_model FloatFormat.binary64 (by decide),
    Model.toModel_ofFloatModel] at hd
  change x.toModel.unpack.isFinite = true
  cases hx : x.toModel.unpack <;>
    simp_all [Model.unpackedToDyadic?, Float.Model.UnpackedFloat.isFinite]

theorem native_finite (u : UInt32) (h : Domain u) : (value u).isFinite = true := by
  obtain ⟨d, hd⟩ := Model.exists_toDyadic?_of_isFinite (raw_finite u h)
  apply native_finite_of_decode
  rw [native_model u h]
  exact hd

theorem shift29_toReal (s : Bool) (m : Nat) (e : Int) :
    (FloatLib.Numerics.Dyadic.mk s (m * 536870912) (e - 29)).toReal =
      (FloatLib.Numerics.Dyadic.mk s m e).toReal := by
  let d : FloatLib.Numerics.Dyadic := ⟨s, m, e⟩
  have hs :
      ((FloatLib.Numerics.Dyadic.mk s (m * 536870912) (e - 29)).signedSignificand : ℝ) =
        (d.signedSignificand : ℝ) *
          FloatLib.Floats.Formats.Flocq.bpow FloatLib.Numerics.binaryRadix 29 := by
    simpa only [Nat.shiftLeft_eq] using Model.Dyadic.signedSignificand_shiftLeft d 29
  rw [Model.Dyadic.toReal_eq_signedSignificand, hs, mul_assoc,
    ← FloatLib.Floats.Formats.Flocq.bpow.add_exp]
  have he : (29 : Int) + (e - 29) = e := by omega
  rw [he]
  exact (Model.Dyadic.toReal_eq_signedSignificand d).symm

theorem native_value (u : UInt32) (h : Domain u) :
    Model.toReal (native64 (value u)) =
      Model.toReal (Model.ofUInt32 (fmt := FloatFormat.binary32) u) := by
  rw [native_model u h]
  rcases h with hn | hz
  · have hd32 : Model.toDyadic? (raw32 u) =
        some ⟨wordSign u, 8388608 + wordFrac u, (wordExp u : Int) - 150⟩ := by
      rw [raw32_eq_fields]
      exact fields32_toDyadic _ _ _ hn.1 hn.2 (wordFrac_lt u)
    change Model.toReal (raw64 (widenBits u)) = Model.toReal (raw32 u)
    rw [Model.toReal_eq, normal_decode u hn, Model.toReal_eq, hd32]
    exact shift29_toReal _ _ _
  · rcases zero_word_cases u hz.1 hz.2 with rfl | rfl
    · rw [widenBits_posZero]
      change Model.toReal (Model.zero FloatFormat.binary64 false) =
        Model.toReal (Model.zero FloatFormat.binary32 false)
      simp
    · rw [widenBits_negZero]
      change Model.toReal (Model.zero FloatFormat.binary64 true) =
        Model.toReal (Model.zero FloatFormat.binary32 true)
      simp

theorem actual_native_value (u : UInt32) (h : Domain u) :
    Model.toReal (ExecFloat.Binary.toModel (ExecFloat.Binary.ofFloat (value u))) =
      Model.toReal (Model.ofUInt32 (fmt := FloatFormat.binary32) u) := by
  rw [ExecFloat.Binary.toModel_ofFloat]
  exact native_value u h

theorem signed_zero_bits : (value 0).toBits = 0 ∧
    (value 0x80000000).toBits = 0x8000000000000000 := by decide

end Submission.R24RepresentationWiden


/-
R24 portable binary64 native multiplication bridge.
The complete retained B2 prefix and its four public endpoints are unchanged.
This reuses B2's format-polymorphic modelMulFinite proof; it does not assume
an opaque Float32/Float cast and does not depend on the uncompiled widen1 helper.
-/
namespace Submission.R24NativeMul

open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange

abbrev F64 := FloatFormat.binary64
abbrev F32 := FloatFormat.binary32
abbrev view (x : Float) : Model F64 := Model.ofFloatModel x.toModel
noncomputable abbrev value (x : Float) : Real := Model.toReal (view x)
abbrev raw32 (u : UInt32) : Model F32 := Model.ofUInt32 u

/-- Actual native Float multiplication agrees with Model.mul on every finite
input, including signed zeros. The result is allowed to overflow. -/
theorem native_mul_toModel (x y : Float)
    (hx : x.isFinite = true) (hy : y.isFinite = true) :
    ExecFloat.Binary.toModel (ExecFloat.Binary.ofFloat (x * y)) =
      Model.mul (ExecFloat.Binary.toModel (ExecFloat.Binary.ofFloat x))
        (ExecFloat.Binary.toModel (ExecFloat.Binary.ofFloat y)) := by
  rw [ExecFloat.Binary.toModel_ofFloat, ExecFloat.Binary.toModel_ofFloat,
    ExecFloat.Binary.toModel_ofFloat]
  change Model.ofFloatModel (Float.Model.mul x.toModel y.toModel) = _
  rw [Float.Model.mul, Model.ofFloatModel_pack]
  have h := R2W01c.NativeBridge.modelMulFinite (fmt := F64)
    (by decide) (Model.ofFloatModel x.toModel) (Model.ofFloatModel y.toModel)
    (by simpa only [Model.toModel_ofFloatModel, Float.isFinite,
      Float.Model.isFinite] using hx)
    (by simpa only [Model.toModel_ofFloatModel, Float.isFinite,
      Float.Model.isFinite] using hy)
  rw [Model.toModel_ofFloatModel, Model.toModel_ofFloatModel] at h
  exact h.symm

private theorem mul_view (x y : Float)
    (hx : x.isFinite = true) (hy : y.isFinite = true) :
    view (x * y) = Model.mul (view x) (view y) := by
  simpa only [ExecFloat.Binary.toModel_ofFloat] using native_mul_toModel x y hx hy

private theorem model_finite (x : Float) (hx : x.isFinite = true) :
    Model.isFinite (view x) = true := by
  have hxmodel : (Model.toModel (view x)).isFinite = true := by
    simpa only [view, Model.toModel_ofFloatModel, Float.isFinite,
      Float.Model.isFinite] using hx
  have hsome : (Model.toDyadic? (view x)).isSome = true := by
    rw [Model.toDyadic?_ieee_eq_model F64 (by decide)]
    cases hm : Model.toModel (view x) <;>
      simp_all [Model.unpackedToDyadic?, Float.Model.UnpackedFloat.isFinite]
  cases hd : Model.toDyadic? (view x) with
  | none => simp [hd] at hsome
  | some d => exact Model.isFinite_eq_true_of_toDyadic?_some hd

private theorem native_finite (x : Float) (hx : Model.isFinite (view x) = true) :
    x.isFinite = true := by
  obtain ⟨d, hd⟩ := Model.exists_toDyadic?_of_isFinite hx
  rw [Model.toDyadic?_ieee_eq_model F64 (by decide),
    Model.toModel_ofFloatModel] at hd
  change x.toModel.unpack.isFinite = true
  cases hm : x.toModel.unpack <;>
    simp_all [Model.unpackedToDyadic?, Float.Model.UnpackedFloat.isFinite]

/-- A symbolic exact-product bound gives finiteness and the real RNE64
semantics of the actual native multiplication; output finiteness is proved. -/
theorem native_mul_finite_roundAt (x y : Float)
    (hx : x.isFinite = true) (hy : y.isFinite = true)
    (hbound : |value x| * |value y| ≤ Model.toReal (Model.posMaxFinite F64)) :
    (x * y).isFinite = true ∧
      value (x * y) = Model.roundAt F64 (value x * value y) := by
  have hmx := model_finite x hx
  have hmy := model_finite y hy
  have hp := Model.isFinite_mul_of_abs_mul_le_posMaxFinite
    (view x) (view y) (by decide) hmx hmy hbound
  have hpview : Model.isFinite (view (x * y)) = true := by
    rw [mul_view x y hx hy]
    exact hp
  refine ⟨native_finite (x * y) hpview, ?_⟩
  change Model.toReal (view (x * y)) = _
  rw [mul_view x y hx hy]
  exact Model.toReal_mul_eq_roundAt (view x) (view y) (by decide) hmx hmy hp

private theorem max32_squared_le_max64 :
    Model.toReal (Model.posMaxFinite F32) * Model.toReal (Model.posMaxFinite F32) ≤
      Model.toReal (Model.posMaxFinite F64) := by
  simp only [Model.toReal_posMaxFinite]
  change ((16777215 : Real) * (2 : Real) ^ (104 : Int)) *
      ((16777215 : Real) * (2 : Real) ^ (104 : Int)) ≤
    (9007199254740991 : Real) * (2 : Real) ^ (971 : Int)
  norm_num

private theorem f32_product_bound (a b : Model F32)
    (ha : Model.isFinite a = true) (hb : Model.isFinite b = true) :
    |Model.toReal a| * |Model.toReal b| ≤ Model.toReal (Model.posMaxFinite F64) := by
  have hA := Model.abs_toReal_le_posMaxFinite_of_isIEEE_of_isFinite a (by decide) ha
  have hB := Model.abs_toReal_le_posMaxFinite_of_isIEEE_of_isFinite b (by decide) hb
  have hnonneg : 0 ≤ Model.toReal (Model.posMaxFinite F32) :=
    (abs_nonneg (Model.toReal a)).trans hA
  exact (mul_le_mul hA hB (abs_nonneg _) hnonneg).trans max32_squared_le_max64

private theorem f32_product_grid (a b : Model F32)
    (ha : Model.isFinite a = true) (hb : Model.isFinite b = true) :
    FloatLib.Floats.Formats.Flocq.genericFormat FloatLib.Numerics.binaryRadix
      (Model.fexpOf F64) (Model.toReal a * Model.toReal b) := by
  obtain ⟨da, hda⟩ := Model.exists_toDyadic?_of_isFinite ha
  obtain ⟨db, hdb⟩ := Model.exists_toDyadic?_of_isFinite hb
  let d : FloatLib.Numerics.Dyadic :=
    ⟨Bool.xor da.negative db.negative, da.significand * db.significand,
      da.exponent + db.exponent⟩
  have hma := Model.toDyadic?_significand_lt a hda
  have hmb := Model.toDyadic?_significand_lt b hdb
  change da.significand < 2 ^ 24 at hma
  change db.significand < 2 ^ 24 at hmb
  have hsig : d.significand < 2 ^ (F64.fracWidth + 1) := by
    change da.significand * db.significand < 2 ^ 53
    calc
      da.significand * db.significand < 2 ^ 24 * 2 ^ 24 := Nat.mul_lt_mul'' hma hmb
      _ < 2 ^ 53 := by norm_num
  have hea := Model.minSubnormalExponent_le_toDyadic? a hda
  have heb := Model.minSubnormalExponent_le_toDyadic? b hdb
  change (-149 : Int) ≤ da.exponent at hea
  change (-149 : Int) ≤ db.exponent at heb
  have he : F64.minSubnormalExponent ≤ d.exponent := by
    change (-1074 : Int) ≤ da.exponent + db.exponent
    omega
  have hg := Model.Dyadic.genericFormat_of_significand_lt F64 d hsig he
  have hv : d.toReal = Model.toReal a * Model.toReal b := by
    simpa only [d, Model.toReal_eq, hda, hdb] using Model.Dyadic.toReal_mul da db
  rw [hv] at hg
  exact hg

/-- Once two native inputs have finite binary32 values, native binary64 MUL
is finite and exact. The product's 48-bit/grid and magnitude facts are proved,
not assumed. This theorem does not assert correctness of any widening cast. -/
theorem native_mul_exact_from_raw32_values (x y : Float) (a b : UInt32)
    (hx : x.isFinite = true) (hy : y.isFinite = true)
    (ha : Model.isFinite (raw32 a) = true) (hb : Model.isFinite (raw32 b) = true)
    (hxa : value x = Model.toReal (raw32 a))
    (hyb : value y = Model.toReal (raw32 b)) :
    (x * y).isFinite = true ∧
      value (x * y) = Model.toReal (raw32 a) * Model.toReal (raw32 b) := by
  have hbound : |value x| * |value y| ≤ Model.toReal (Model.posMaxFinite F64) := by
    rw [hxa, hyb]
    exact f32_product_bound (raw32 a) (raw32 b) ha hb
  obtain ⟨hfinite, hround⟩ := native_mul_finite_roundAt x y hx hy hbound
  refine ⟨hfinite, ?_⟩
  rw [hround, hxa, hyb]
  exact FloatLib.Floats.Formats.Flocq.round_preserves_generic
    FloatLib.Floats.Formats.Flocq.nearestEven _
    (f32_product_grid (raw32 a) (raw32 b) ha hb)

end Submission.R24NativeMul


/- R24 portable actual Float64 fold. Input values are arbitrary finite Float
   values, bounded by a power of two; no widening or multiplication theorem is
   assumed. New declarations are NOT_RUN until the fixed helper gate checks them. -/
namespace Submission.R24RepresentationSum
open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange
open FloatLib.Floats.Formats.Flocq

abbrev native (x : Float) : Model FloatFormat.binary64 := Model.ofFloatModel x.toModel
noncomputable def rval (x : Float) : ℝ := Model.toReal (native x)
noncomputable def p2 (e : Int) : ℝ := bpow FloatLib.Numerics.binaryRadix e
noncomputable def exactSum (xs : List Float) : ℝ := (xs.map rval).sum

def loop : List Float → Float → Float
  | [], acc => acc
  | x :: xs, acc => loop xs (acc + x)

def sum (xs : List Float) : Float := loop xs (Float.ofBits 0)

theorem p2_pos (e : Int) : 0 < p2 e := bpow.pos _ _

theorem p2_mono {a b : Int} (h : a ≤ b) : p2 a ≤ p2 b :=
  (bpow_le_bpow_iff FloatLib.Numerics.binaryRadix a b).2 h

theorem p2_add (a b : Int) : p2 (a + b) = p2 a * p2 b :=
  bpow.add_exp _ _ _

theorem p2_nat (n : Nat) : p2 (n : Int) = ((2 ^ n : Nat) : ℝ) := by
  simp [p2, bpow, FloatLib.Numerics.binaryRadix, FloatLib.Numerics.Radix.toReal]

theorem scaled_count_le (j L : Nat) (k : Int) (hj : j ≤ 2 ^ L) :
    (j : ℝ) * p2 k ≤ p2 (k + (L : Int)) := by
  have hjR : (j : ℝ) ≤ ((2 ^ L : Nat) : ℝ) := by exact_mod_cast hj
  calc
    (j : ℝ) * p2 k ≤ ((2 ^ L : Nat) : ℝ) * p2 k :=
      mul_le_mul_of_nonneg_right hjR (p2_pos k).le
    _ = p2 (k + (L : Int)) := by
      rw [← p2_nat, ← p2_add]
      congr 1
      omega

theorem native_finite_eq (x : Float) : Model.isFinite (native x) = x.isFinite := by
  rw [← Model.toDyadic?_isSome_eq_isFinite,
    Model.toDyadic?_ieee_eq_model FloatFormat.binary64 (by decide),
    Model.toModel_ofFloatModel]
  change (Model.unpackedToDyadic? x.toModel.unpack).isSome = x.toModel.unpack.isFinite
  cases x.toModel.unpack <;> rfl

theorem native_add (x y : Float) (hx : x.isFinite = true) (hy : y.isFinite = true) :
    native (x + y) = Model.add (native x) (native y) := by
  simpa only [ExecFloat.Binary.toModel_ofFloat] using
    ExecFloat.Binary.toModel_ofFloat_add_of_isFinite x y hx hy

theorem max_finite_large : p2 286 ≤ Model.toReal (Model.posMaxFinite FloatFormat.binary64) := by
  change p2 286 ≤ Model.toReal
    (Model.ofFields FloatFormat.binary64 false 2046 4503599627370495)
  rw [Model.toReal_ofFields_normal FloatFormat.binary64 false 2046 4503599627370495
    (by decide) (by decide) (by decide)]
  change p2 286 ≤ (1 : ℝ) * 9007199254740991 * p2 971
  rw [one_mul]
  have hpow : p2 286 ≤ p2 971 := p2_mono (by omega)
  have hp := p2_pos 971
  nlinarith

theorem native_add_finite_real (x y : Float)
    (hx : x.isFinite = true) (hy : y.isFinite = true)
    (hb : |rval x| + |rval y| ≤ p2 286) :
    (x + y).isFinite = true ∧
      rval (x + y) = Model.roundAt FloatFormat.binary64 (rval x + rval y) := by
  have hxm : Model.isFinite (native x) = true := by rw [native_finite_eq, hx]
  have hym : Model.isFinite (native y) = true := by rw [native_finite_eq, hy]
  have hbm : |Model.toReal (native x)| + |Model.toReal (native y)| ≤
      Model.toReal (Model.posMaxFinite FloatFormat.binary64) := hb.trans max_finite_large
  constructor
  · rw [← native_finite_eq, native_add x y hx hy]
    exact Model.isFinite_add_of_abs_add_le_posMaxFinite (native x) (native y)
      (by decide) hxm hym hbm
  · change Model.toReal (native (x + y)) =
      Model.roundAt FloatFormat.binary64 (Model.toReal (native x) + Model.toReal (native y))
    rw [native_add x y hx hy]
    exact Model.toReal_add_eq_roundAt_of_abs_add_le_posMaxFinite (native x) (native y)
      (by decide) hxm hym hbm

/- A bounded integer times the given power of two belongs to the actual
   binary64 gradual-underflow grid. This closes the j*M exactness premise. -/
theorem round_grid (j : Nat) (k : Int) (hj : j ≤ 2 ^ 30) (hk : -250 ≤ k) :
    Model.roundAt FloatFormat.binary64 ((j : ℝ) * p2 k) = (j : ℝ) * p2 k := by
  have hfmt : FLTFormat (β := FloatLib.Numerics.binaryRadix) (-1074) 53
      ((j : ℝ) * p2 k) := by
    refine ⟨by norm_num, ⟨(j : Int), k⟩, ?_, ?_, by omega⟩
    · simp only [FloatLib.Floats.Formats.Flocq.toReal, Int.cast_natCast]
      rfl
    · change j < 2 ^ 53
      exact lt_of_le_of_lt hj (by decide)
  apply round_preserves_generic
  exact generic_of_fltFormat (-1074) 53 (by norm_num) _ hfmt

/- This is obtained from the library's real RNE half-ULP bound, not assumed
   as a property of a hypothetical step operation. The looser full-ULP
   bound deliberately avoids extra one-bit engineering. -/
theorem round_error_power (x : ℝ) (K : Int) (hK : -250 ≤ K) (hx : |x| < p2 K) :
    |Model.roundAt FloatFormat.binary64 x - x| ≤ p2 (K - 53) := by
  by_cases hz : x = 0
  · subst x
    rw [Model.roundAt_zero, sub_self, abs_zero]
    exact (p2_pos _).le
  · have hm : magnitude FloatLib.Numerics.binaryRadix x ≤ K :=
      magnitude_le_of_abs_lt_bpow _ _ _ hz hx
    have hc : cexp FloatLib.Numerics.binaryRadix (Model.fexpOf FloatFormat.binary64) x ≤
        K - 53 := by
      change max (magnitude FloatLib.Numerics.binaryRadix x - 53) (-1074) ≤ K - 53
      exact max_le (by omega) (by omega)
    have hu : ulp FloatLib.Numerics.binaryRadix (Model.fexpOf FloatFormat.binary64) x ≤
        p2 (K - 53) := by
      rw [ulp.of_ne_zero _ _ _ hz]
      exact p2_mono hc
    have he := error_bound_ulp (β := FloatLib.Numerics.binaryRadix)
      (fexp := Model.fexpOf FloatFormat.binary64) nearestEven x
    have hn := ulp.nonneg FloatLib.Numerics.binaryRadix (Model.fexpOf FloatFormat.binary64) x
    change |Model.roundAt FloatFormat.binary64 x - x| ≤
      ulp FloatLib.Numerics.binaryRadix (Model.fexpOf FloatFormat.binary64) x / 2 at he
    exact he.trans (by linarith)

theorem exactSum_nil : exactSum [] = 0 := rfl
theorem exactSum_cons (x : Float) (xs : List Float) :
    exactSum (x :: xs) = rval x + exactSum xs := rfl

theorem zero_native : native (Float.ofBits 0) = Model.zero FloatFormat.binary64 false := by
  decide

theorem zero_value : rval (Float.ofBits 0) = 0 := by
  unfold rval
  rw [zero_native, Model.toReal_zero]

theorem zero_finite : (Float.ofBits 0).isFinite = true := by decide

/- Actual loop invariant: the native addition, result finiteness, real RNE
   step, exact grid bounds, and local error are all proved inside the step. -/
theorem loop_invariant (xs : List Float) (acc : Float) (j L : Nat) (k : Int)
    (hklo : -250 ≤ k) (hkhi : k ≤ 256) (hL : L ≤ 30)
    (hcount : j + xs.length ≤ 2 ^ L)
    (hacc : acc.isFinite = true) (hmag : |rval acc| ≤ (j : ℝ) * p2 k)
    (hxs : ∀ x ∈ xs, x.isFinite = true ∧ |rval x| < p2 k) :
    (loop xs acc).isFinite = true ∧
      |rval (loop xs acc)| ≤ ((j + xs.length : Nat) : ℝ) * p2 k ∧
      |rval (loop xs acc) - (rval acc + exactSum xs)| ≤
        (xs.length : ℝ) * p2 (k + (L : Int) - 53) := by
  induction xs generalizing acc j with
  | nil =>
    simpa only [loop, List.length_nil, Nat.add_zero, exactSum_nil, add_zero,
      sub_self, abs_zero, Nat.cast_zero, zero_mul, le_refl, and_true] using And.intro hacc hmag
  | cons x xs ih =>
    have hx := hxs x (by simp)
    have htail : ∀ y ∈ xs, y.isFinite = true ∧ |rval y| < p2 k := by
      intro y hy
      exact hxs y (by simp [hy])
    have hj : j + 1 ≤ 2 ^ L := by simp only [List.length_cons] at hcount; omega
    have hj30 : j + 1 ≤ 2 ^ 30 :=
      hj.trans (Nat.pow_le_pow_right (by decide) hL)
    have hnextCount : (j + 1) + xs.length ≤ 2 ^ L := by
      simp only [List.length_cons] at hcount
      omega
    have htri : |rval acc| + |rval x| < ((j + 1 : Nat) : ℝ) * p2 k := by
      have hh := add_lt_add_of_le_of_lt hmag hx.2
      convert hh using 1 <;> push_cast <;> ring
    have hglobal : ((j + 1 : Nat) : ℝ) * p2 k ≤ p2 (k + (L : Int)) :=
      scaled_count_le _ _ _ hj
    have htop : p2 (k + (L : Int)) ≤ p2 286 := p2_mono (by omega)
    have hstep := native_add_finite_real acc x hacc hx.1
      (htri.le.trans (hglobal.trans htop))
    have hinput : |rval acc + rval x| < ((j + 1 : Nat) : ℝ) * p2 k :=
      (abs_add_le _ _).trans_lt htri
    have hgrid := round_grid (j + 1) k hj30 hklo
    have hnextMag : |rval (acc + x)| ≤ ((j + 1 : Nat) : ℝ) * p2 k := by
      rw [hstep.2]
      obtain ⟨hlo, hhi⟩ := abs_le.mp hinput.le
      have a := Model.roundAt_mono FloatFormat.binary64 hlo
      have b := Model.roundAt_mono FloatFormat.binary64 hhi
      rw [Model.roundAt_neg, hgrid] at a
      rw [hgrid] at b
      exact abs_le.mpr ⟨a, b⟩
    have herr : |rval (acc + x) - (rval acc + rval x)| ≤
        p2 (k + (L : Int) - 53) := by
      rw [hstep.2]
      exact round_error_power _ _ (by omega) (hinput.trans_le hglobal)
    have hout := ih (acc + x) (j + 1) hnextCount hstep.1 hnextMag htail
    refine ⟨hout.1, ?_, ?_⟩
    · convert hout.2.1 using 1 <;> simp only [List.length_cons] <;> push_cast <;> ring
    · have heq : rval (loop xs (acc + x)) - (rval acc + exactSum (x :: xs)) =
          (rval (loop xs (acc + x)) - (rval (acc + x) + exactSum xs)) +
            (rval (acc + x) - (rval acc + rval x)) := by
        rw [exactSum_cons]
        ring
      change |rval (loop xs (acc + x)) - (rval acc + exactSum (x :: xs))| ≤ _
      rw [heq]
      calc
        _ ≤ |rval (loop xs (acc + x)) - (rval (acc + x) + exactSum xs)| +
              |rval (acc + x) - (rval acc + rval x)| := abs_add_le _ _
        _ ≤ (xs.length : ℝ) * p2 (k + (L : Int) - 53) +
              p2 (k + (L : Int) - 53) := add_le_add hout.2.2 herr
        _ = ((x :: xs).length : ℝ) * p2 (k + (L : Int) - 53) := by
          simp only [List.length_cons, Nat.cast_add, Nat.cast_one]
          ring

theorem sum_enclosure (xs : List Float) (L : Nat) (k : Int)
    (hklo : -250 ≤ k) (hkhi : k ≤ 256) (hL : L ≤ 30)
    (hcount : xs.length ≤ 2 ^ L)
    (hxs : ∀ x ∈ xs, x.isFinite = true ∧ |rval x| < p2 k) :
    (sum xs).isFinite = true ∧
      |rval (sum xs) - exactSum xs| ≤ p2 (k + 2 * (L : Int) - 53) := by
  have h := loop_invariant xs (Float.ofBits 0) 0 L k hklo hkhi hL
    (by simpa using hcount) zero_finite (by simp [zero_value]) hxs
  refine ⟨h.1, ?_⟩
  have he : |rval (sum xs) - exactSum xs| ≤
      (xs.length : ℝ) * p2 (k + (L : Int) - 53) := by
    simpa only [sum, zero_value, zero_add] using h.2.2
  have hc : (xs.length : ℝ) ≤ ((2 ^ L : Nat) : ℝ) := by exact_mod_cast hcount
  calc
    _ ≤ (xs.length : ℝ) * p2 (k + (L : Int) - 53) := he
    _ ≤ ((2 ^ L : Nat) : ℝ) * p2 (k + (L : Int) - 53) :=
      mul_le_mul_of_nonneg_right hc (p2_pos _).le
    _ = p2 (k + 2 * (L : Int) - 53) := by
      rw [← p2_nat, ← p2_add]
      congr 1
      ring

theorem actual_sum_enclosure (xs : List Float) (L : Nat) (k : Int)
    (hklo : -250 ≤ k) (hkhi : k ≤ 256) (hL : L ≤ 30)
    (hcount : xs.length ≤ 2 ^ L)
    (hxs : ∀ x ∈ xs, x.isFinite = true ∧
      |Model.toReal (ExecFloat.Binary.toModel (ExecFloat.Binary.ofFloat x))| < p2 k) :
    (sum xs).isFinite = true ∧
      |Model.toReal (ExecFloat.Binary.toModel (ExecFloat.Binary.ofFloat (sum xs))) -
        (xs.map (fun x => Model.toReal (ExecFloat.Binary.toModel (ExecFloat.Binary.ofFloat x)))).sum|
        ≤ p2 (k + 2 * (L : Int) - 53) := by
  have hx : ∀ x ∈ xs, x.isFinite = true ∧ |rval x| < p2 k := by
    simpa only [ExecFloat.Binary.toModel_ofFloat, rval] using hxs
  simpa only [ExecFloat.Binary.toModel_ofFloat, rval, exactSum] using
    sum_enclosure xs L k hklo hkhi hL hcount hx

end Submission.R24RepresentationSum


/- R24 portable strict-endpoint core, fixed ContractTensor-imported FloatLib.
   These roots prove the nearest64 pullback, not raw-word cell construction,
   actual native endpoint evaluation, RNE32 cell membership or kernel adoption.
   No external monotonicity/fixed-point assumption or outward-rounding premise. -/
namespace Submission.R24StrictEnclosure

open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange

abbrev F64 := FloatFormat.binary64

theorem strict_lower_pullback (x : Real) (lower : Model F64)
    (hfinite : Model.isFinite lower = true)
    (h : Model.toReal lower < Model.roundAt F64 x) :
    Model.toReal lower < x := by
  by_contra hn
  have hx : x ≤ Model.toReal lower := le_of_not_gt hn
  have hm := Model.roundAt_mono F64 hx
  rw [Model.roundAt_toReal_eq lower hfinite] at hm
  exact (not_lt_of_ge hm) h

theorem strict_upper_pullback (x : Real) (upper : Model F64)
    (hfinite : Model.isFinite upper = true)
    (h : Model.roundAt F64 x < Model.toReal upper) :
    x < Model.toReal upper := by
  by_contra hn
  have hx : Model.toReal upper ≤ x := le_of_not_gt hn
  have hm := Model.roundAt_mono F64 hx
  rw [Model.roundAt_toReal_eq upper hfinite] at hm
  exact (not_lt_of_ge hm) h

theorem strict_enclosure_of_rounded_bounds
    (s target radius : Real) (lower upper : Model F64)
    (hlfinite : Model.isFinite lower = true)
    (hufinite : Model.isFinite upper = true)
    (herror : |s - target| ≤ radius)
    (hlower : Model.toReal lower < Model.roundAt F64 (s - radius))
    (hupper : Model.roundAt F64 (s + radius) < Model.toReal upper) :
    Model.toReal lower < target ∧ target < Model.toReal upper := by
  have hl := strict_lower_pullback (s - radius) lower hlfinite hlower
  have hu := strict_upper_pullback (s + radius) upper hufinite hupper
  obtain ⟨hel, heu⟩ := abs_le.mp herror
  constructor <;> linarith

end Submission.R24StrictEnclosure
