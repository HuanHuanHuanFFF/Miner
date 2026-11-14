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


/- Generic old-ContractTensor mathematical helper. No candidate-generation or
   floating-point accuracy premise: the rounded candidate is arbitrary.
   Core gap/check runtime uses fixed words; the normal wrapper also checks Int
   exponent bounds. Typing/replay/dependency audit NOT_RUN. -/
namespace Submission.R24WordGap128

open FloatLib.Numerics.FixedWord

/-- Absolute difference from the exact 64 by 64 product, without wrapping. -/
@[inline] def gap (num : UInt128) (den mant : UInt64) : UInt128 :=
  let product := mul64 mant den
  if UInt128.less num product then UInt128.sub product num
  else UInt128.sub num product

/-- Strict midpoint check; each subtraction is ordered before its value is used. -/
@[inline] def check (num : UInt128) (den mant : UInt64) : Bool :=
  let residue := gap num den mant
  decide ((0 : UInt64) < den) &&
    (decide ((0 : UInt64) < mant) &&
      ((residue.hi == 0) &&
        (decide (residue.lo < den) && decide (residue.lo < den - residue.lo))))

theorem gap_toNat_cases (num : UInt128) (den mant : UInt64) :
    (num.toNat < mant.toNat * den.toNat ∧
      (gap num den mant).toNat = mant.toNat * den.toNat - num.toNat) ∨
    (mant.toNat * den.toNat ≤ num.toNat ∧
      (gap num den mant).toNat = num.toNat - mant.toNat * den.toNat) := by
  by_cases h : UInt128.less num (mul64 mant den) = true
  · left
    have hlt := UInt128.less_eq_true_iff.mp h
    have hsub := UInt128.sub_toNat (mul64 mant den) num hlt.le
    constructor
    · simpa only [mul64_toNat] using hlt
    · simpa only [gap, if_pos h, mul64_toNat] using hsub
  · right
    have hle : (mul64 mant den).toNat ≤ num.toNat := by
      by_contra hn
      have hlt : num.toNat < (mul64 mant den).toNat := by omega
      exact h (UInt128.less_eq_true_iff.mpr hlt)
    have hsub := UInt128.sub_toNat num (mul64 mant den) hle
    constructor
    · simpa only [mul64_toNat] using hle
    · simpa only [gap, if_neg h, mul64_toNat] using hsub

theorem check_midpoint_bounds (num : UInt128) (den mant : UInt64)
    (h : check num den mant = true) :
    0 < den.toNat ∧ 0 < mant.toNat ∧
      den.toNat * (2 * mant.toNat - 1) < 2 * num.toNat ∧
      2 * num.toNat < den.toNat * (2 * mant.toNat + 1) := by
  let residue := gap num den mant
  have hh : (0 : UInt64) < den ∧ ((0 : UInt64) < mant ∧
      (residue.hi = 0 ∧ (residue.lo < den ∧ residue.lo < den - residue.lo))) := by
    simpa only [check, Bool.and_eq_true, decide_eq_true_eq, beq_iff_eq] using h
  have hd : 0 < den.toNat := by
    simpa only [UInt64.toNat_zero] using UInt64.lt_iff_toNat_lt.mp hh.1
  have hm : 0 < mant.toNat := by
    simpa only [UInt64.toNat_zero] using UInt64.lt_iff_toNat_lt.mp hh.2.1
  have hlo := UInt64.lt_iff_toNat_lt.mp hh.2.2.2.1
  have hhalf := UInt64.lt_iff_toNat_lt.mp hh.2.2.2.2
  have hsub : (den - residue.lo).toNat = den.toNat - residue.lo.toNat :=
    UInt64.toNat_sub_of_le den residue.lo (UInt64.le_iff_toNat_le.mpr hlo.le)
  rw [hsub] at hhalf
  have htwice : 2 * residue.lo.toNat < den.toNat := by omega
  have hresidue : residue.toNat = residue.lo.toNat := by
    simp only [UInt128.toNat, hh.2.2.1, UInt64.toNat_zero, zero_mul, add_zero]
  have hgap := gap_toNat_cases num den mant
  change (num.toNat < mant.toNat * den.toNat ∧
      residue.toNat = mant.toNat * den.toNat - num.toNat) ∨
    (mant.toNat * den.toNat ≤ num.toNat ∧
      residue.toNat = num.toNat - mant.toNat * den.toNat) at hgap
  rw [hresidue] at hgap
  have hcut : 2 * mant.toNat - 1 + 1 = 2 * mant.toNat := by omega
  have hexpand : den.toNat * (2 * mant.toNat - 1) + den.toNat =
      2 * (mant.toNat * den.toNat) := by
    calc
      den.toNat * (2 * mant.toNat - 1) + den.toNat =
          den.toNat * ((2 * mant.toNat - 1) + 1) := by ring
      _ = den.toNat * (2 * mant.toNat) := by rw [hcut]
      _ = 2 * (mant.toNat * den.toNat) := by ring
  have hmid : den.toNat * (2 * mant.toNat - 1) < 2 * num.toNat ∧
      2 * num.toNat < den.toNat * (2 * mant.toNat + 1) := by
    rcases hgap with ⟨hlt, hres⟩ | ⟨hle, hres⟩
    · have hsum := Nat.sub_add_cancel hlt.le
      constructor <;> nlinarith
    · have hsum := Nat.sub_add_cancel hle
      constructor <;> nlinarith
  exact ⟨hd, hm, hmid.1, hmid.2⟩

theorem check_sound (num : UInt128) (den mant : UInt64)
    (h : check num den mant = true) :
    FloatLib.Numerics.roundQuotientEven num.toNat den.toNat = mant.toNat := by
  obtain ⟨hd, hm, hl, hu⟩ := check_midpoint_bounds num den mant h
  exact Submission.R24CellPrimitive.quotient_strict_midpoint
    num.toNat den.toNat mant.toNat hd hm hl hu

@[inline] def normalCheck (num : UInt128) (den mant : UInt64) (exponent : Int) : Bool :=
  check num den mant &&
    (decide ((8388608 : UInt64) < mant) &&
      (decide (mant < (16777216 : UInt64)) &&
        (decide (1 ≤ exponent + 150) && decide (exponent + 150 ≤ 254))))

theorem normalCheck_sound (sign : Bool) (num : UInt128) (den mant : UInt64)
    (exponent : Int) (h : normalCheck num den mant exponent = true) :
    FloatLib.Floats.Formats.BinaryInterchange.Model.NativeBinary32.roundRatScaled
        sign num.toNat den.toNat exponent =
      FloatLib.Floats.Formats.BinaryInterchange.Model.NativeBinary32.mkBits
        sign (exponent + 150).toNat (mant.toNat - 8388608) := by
  have hh : check num den mant = true ∧ ((8388608 : UInt64) < mant ∧
      (mant < (16777216 : UInt64) ∧
        (1 ≤ exponent + 150 ∧ exponent + 150 ≤ 254))) := by
    simpa only [normalCheck, Bool.and_eq_true, decide_eq_true_eq] using h
  have hmlo : 8388608 < mant.toNat := UInt64.lt_iff_toNat_lt.mp hh.2.1
  have hmhi : mant.toNat < 16777216 := UInt64.lt_iff_toNat_lt.mp hh.2.2.1
  obtain ⟨hd, _, hl, hu⟩ := check_midpoint_bounds num den mant hh.1
  exact Submission.R24CellPrimitive.native32_strict_cell
    sign num.toNat den.toNat mant.toNat exponent hd hmlo hmhi
    hh.2.2.2.1 hh.2.2.2.2 hl hu

end Submission.R24WordGap128


/- Fixed-word closed cells for binary32 powers, including the minimum normal.
   Old ContractTensor helper only. New typing/replay/dependency audit NOT_RUN. -/
namespace Submission.R24PowerGap128
open FloatLib.Numerics.FixedWord

@[inline] def halfCheck (gap den : UInt64) : Bool :=
  decide (gap < den) && decide (gap ≤ den - gap)

@[inline] def quarterCheck (gap den : UInt64) : Bool :=
  halfCheck gap den && decide (gap + gap ≤ den - (gap + gap))

theorem halfCheck_bound (gap den : UInt64) (h : halfCheck gap den = true) :
    2 * gap.toNat ≤ den.toNat := by
  have hh : gap < den ∧ gap ≤ den - gap := by
    simpa only [halfCheck, Bool.and_eq_true, decide_eq_true_eq] using h
  have hlt := UInt64.lt_iff_toNat_lt.mp hh.1
  have hle := UInt64.le_iff_toNat_le.mp hh.2
  rw [UInt64.toNat_sub_of_le den gap (UInt64.le_iff_toNat_le.mpr hlt.le)] at hle
  omega

theorem quarterCheck_bound (gap den : UInt64) (h : quarterCheck gap den = true) :
    4 * gap.toNat ≤ den.toNat := by
  have hh : halfCheck gap den = true ∧ gap + gap ≤ den - (gap + gap) := by
    simpa only [quarterCheck, Bool.and_eq_true, decide_eq_true_eq] using h
  have hhalf := halfCheck_bound gap den hh.1
  have hadd : (gap + gap).toNat = 2 * gap.toNat := by
    have hsize := den.toNat_lt_size
    change den.toNat < 18446744073709551616 at hsize
    rw [UInt64.toNat_add]
    change (gap.toNat + gap.toNat) % 18446744073709551616 = 2 * gap.toNat
    rw [Nat.mod_eq_of_lt (by omega)]
    omega
  have hordered : gap + gap ≤ den :=
    UInt64.le_iff_toNat_le.mpr (by rw [hadd]; exact hhalf)
  have hle := UInt64.le_iff_toNat_le.mp hh.2
  rw [UInt64.toNat_sub_of_le den (gap + gap) hordered, hadd] at hle
  omega

/-- The guessed exponent field is raw-word data. Only accepted results are used. -/
@[inline] def check (num : UInt128) (den : UInt64) (field : UInt32) : Bool :=
  let residue := R24WordGap128.gap num den 8388608
  decide ((1 : UInt32) ≤ field) &&
    (decide (field ≤ (254 : UInt32)) &&
      (decide ((0 : UInt64) < den) &&
        ((residue.hi == 0) &&
          (if UInt128.less num (mul64 8388608 den) then
            if field == 1 then halfCheck residue.lo den else quarterCheck residue.lo den
          else halfCheck residue.lo den))))

theorem check_powerCell (num : UInt128) (den : UInt64) (field : UInt32)
    (h : check num den field = true) :
    R24PowerCell.powerCell num.toNat den.toNat ((field.toNat : Int) - 150) = true := by
  let residue := R24WordGap128.gap num den 8388608
  have hh : (1 : UInt32) ≤ field ∧ (field ≤ (254 : UInt32) ∧
      ((0 : UInt64) < den ∧ (residue.hi = 0 ∧
        (if UInt128.less num (mul64 8388608 den) then
          if field == 1 then halfCheck residue.lo den else quarterCheck residue.lo den
        else halfCheck residue.lo den) = true))) := by
    simpa only [check, Bool.and_eq_true, decide_eq_true_eq, beq_iff_eq] using h
  have hf0 : 1 ≤ field.toNat := UInt32.le_iff_toNat_le.mp hh.1
  have hf1 : field.toNat ≤ 254 := UInt32.le_iff_toNat_le.mp hh.2.1
  have hd : 0 < den.toNat := by
    simpa only [UInt64.toNat_zero] using UInt64.lt_iff_toNat_lt.mp hh.2.2.1
  have hresidue : residue.toNat = residue.lo.toNat := by
    simp only [UInt128.toNat, hh.2.2.2.1, UInt64.toNat_zero, zero_mul, add_zero]
  have hgap := R24WordGap128.gap_toNat_cases num den 8388608
  change (num.toNat < 8388608 * den.toNat ∧
      residue.toNat = 8388608 * den.toNat - num.toNat) ∨
    (8388608 * den.toNat ≤ num.toNat ∧
      residue.toNat = num.toNat - 8388608 * den.toNat) at hgap
  rw [hresidue] at hgap
  have hbounds :
      (if field.toNat = 1 then den.toNat * 16777215 ≤ 2 * num.toNat
        else den.toNat * 33554431 ≤ 4 * num.toNat) ∧
      2 * num.toNat ≤ den.toNat * 16777217 := by
    by_cases hbelow : UInt128.less num (mul64 8388608 den) = true
    · have hlt : num.toNat < 8388608 * den.toNat := by
        simpa only [mul64_toNat] using UInt128.less_eq_true_iff.mp hbelow
      have hres : residue.lo.toNat = 8388608 * den.toNat - num.toNat := by
        rcases hgap with hg | hg
        · exact hg.2
        · omega
      have hsum := Nat.sub_add_cancel hlt.le
      have hc := hh.2.2.2.2
      simp only [hbelow, if_true] at hc
      by_cases hmin : field = 1
      · have hc' : halfCheck residue.lo den = true := by simpa only [hmin, beq_self_eq_true, if_true] using hc
        have hhalf := halfCheck_bound residue.lo den hc'
        have hfmin : field.toNat = 1 := by rw [hmin]; rfl
        simp only [hfmin, if_true]
        constructor <;> nlinarith
      · have hc' : quarterCheck residue.lo den = true := by
          simpa only [beq_iff_eq, hmin, if_false] using hc
        have hquarter := quarterCheck_bound residue.lo den hc'
        have hfmin : field.toNat ≠ 1 := by
          intro he
          apply hmin
          apply UInt32.toNat_inj.mp
          exact he
        simp only [hfmin, if_false]
        constructor <;> nlinarith
    · have hle : 8388608 * den.toNat ≤ num.toNat := by
        by_contra hn
        have hlt : num.toNat < (mul64 8388608 den).toNat := by
          simp only [mul64_toNat]
          omega
        exact hbelow (UInt128.less_eq_true_iff.mpr hlt)
      have hres : residue.lo.toNat = num.toNat - 8388608 * den.toNat := by
        rcases hgap with hg | hg
        · omega
        · exact hg.2
      have hsum := Nat.sub_add_cancel hle
      have hc : halfCheck residue.lo den = true := by
        simpa only [hbelow, if_false] using hh.2.2.2.2
      have hhalf := halfCheck_bound residue.lo den hc
      by_cases hmin : field.toNat = 1
      · simp only [hmin, if_true]
        constructor <;> nlinarith
      · simp only [hmin, if_false]
        constructor <;> nlinarith
  unfold R24PowerCell.powerCell
  change decide (0 < den.toNat ∧ 1 ≤ (field.toNat : Int) - 150 + 150 ∧
    (field.toNat : Int) - 150 + 150 ≤ 254 ∧
    (if (field.toNat : Int) - 150 + 150 = 1 then den.toNat * 16777215 ≤ 2 * num.toNat
      else den.toNat * 33554431 ≤ 4 * num.toNat) ∧
    2 * num.toNat ≤ den.toNat * 16777217) = true
  have hfmin : ((field.toNat : Int) = 1) ↔ field.toNat = 1 := by omega
  apply decide_eq_true
  simpa only [sub_add_cancel, hfmin] using
    (show 0 < den.toNat ∧ 1 ≤ (field.toNat : Int) ∧ (field.toNat : Int) ≤ 254 ∧
      (if field.toNat = 1 then den.toNat * 16777215 ≤ 2 * num.toNat
        else den.toNat * 33554431 ≤ 4 * num.toNat) ∧
      2 * num.toNat ≤ den.toNat * 16777217 from
      ⟨hd, by omega, by omega, hbounds.1, hbounds.2⟩)

theorem check_sound (sign : Bool) (num : UInt128) (den : UInt64) (field : UInt32)
    (h : check num den field = true) :
    FloatLib.Floats.Formats.BinaryInterchange.Model.NativeBinary32.roundRatScaled
        sign num.toNat den.toNat ((field.toNat : Int) - 150) =
      FloatLib.Floats.Formats.BinaryInterchange.Model.NativeBinary32.mkBits sign field.toNat 0 := by
  have hp := R24PowerCell.powerCell_sound sign num.toNat den.toNat
    ((field.toNat : Int) - 150) (check_powerCell num den field h)
  simpa only [sub_add_cancel, Int.toNat_natCast] using hp

end Submission.R24PowerGap128


/- Word certificates for an independently established exact rational enclosure.
   The caller supplies enclosure inequalities, not a rounding-cell hypothesis.
   Old ContractTensor helpers only; typing/replay/dependency audit NOT_RUN. -/
namespace Submission.R24IntervalWord128
open FloatLib.Numerics.FixedWord

@[inline] def ordered (lo hi : UInt128) : Bool :=
  !UInt128.less hi lo

@[inline] def strictCheck (lo hi : UInt128) (den mant : UInt64) (field : UInt32) : Bool :=
  ordered lo hi &&
    (decide ((1 : UInt32) ≤ field) &&
      (decide (field ≤ (254 : UInt32)) &&
        (decide ((8388608 : UInt64) < mant) &&
          (decide (mant < (16777216 : UInt64)) &&
            (R24WordGap128.check lo den mant && R24WordGap128.check hi den mant)))))

theorem strictCheck_sound (sign : Bool) (lo hi : UInt128) (den mant : UInt64)
    (field : UInt32) (num : Nat) (hlo : lo.toNat ≤ num) (hhi : num ≤ hi.toNat)
    (h : strictCheck lo hi den mant field = true) :
    FloatLib.Floats.Formats.BinaryInterchange.Model.NativeBinary32.roundRatScaled
        sign num den.toNat ((field.toNat : Int) - 150) =
      FloatLib.Floats.Formats.BinaryInterchange.Model.NativeBinary32.mkBits
        sign field.toNat (mant.toNat - 8388608) := by
  have hh : ordered lo hi = true ∧ ((1 : UInt32) ≤ field ∧
      (field ≤ (254 : UInt32) ∧ ((8388608 : UInt64) < mant ∧
        (mant < (16777216 : UInt64) ∧
          (R24WordGap128.check lo den mant = true ∧
            R24WordGap128.check hi den mant = true))))) := by
    simpa only [strictCheck, Bool.and_eq_true, decide_eq_true_eq] using h
  obtain ⟨hd, _, hlow, _⟩ := R24WordGap128.check_midpoint_bounds lo den mant hh.2.2.2.2.2.1
  obtain ⟨_, _, _, hhigh⟩ := R24WordGap128.check_midpoint_bounds hi den mant hh.2.2.2.2.2.2
  have hm0 : 8388608 < mant.toNat := UInt64.lt_iff_toNat_lt.mp hh.2.2.2.1
  have hm1 : mant.toNat < 16777216 := UInt64.lt_iff_toNat_lt.mp hh.2.2.2.2.1
  have hf0 : 1 ≤ field.toNat := UInt32.le_iff_toNat_le.mp hh.2.1
  have hf1 : field.toNat ≤ 254 := UInt32.le_iff_toNat_le.mp hh.2.2.1
  have hl : den.toNat * (2 * mant.toNat - 1) < 2 * num := by omega
  have hu : 2 * num < den.toNat * (2 * mant.toNat + 1) := by omega
  have hr := R24CellPrimitive.native32_strict_cell sign num den.toNat mant.toNat
    ((field.toNat : Int) - 150) hd hm0 hm1 (by omega) (by omega) hl hu
  simpa only [sub_add_cancel, Int.toNat_natCast] using hr

@[inline] def powerCheck (lo hi : UInt128) (den : UInt64) (field : UInt32) : Bool :=
  ordered lo hi && (R24PowerGap128.check lo den field && R24PowerGap128.check hi den field)

theorem powerCheck_cell (lo hi : UInt128) (den : UInt64) (field : UInt32)
    (num : Nat) (hlo : lo.toNat ≤ num) (hhi : num ≤ hi.toNat)
    (h : powerCheck lo hi den field = true) :
    R24PowerCell.powerCell num den.toNat ((field.toNat : Int) - 150) = true := by
  have hh : ordered lo hi = true ∧
      (R24PowerGap128.check lo den field = true ∧ R24PowerGap128.check hi den field = true) := by
    simpa only [powerCheck, Bool.and_eq_true] using h
  have hlow := R24PowerGap128.check_powerCell lo den field hh.2.1
  have hhigh := R24PowerGap128.check_powerCell hi den field hh.2.2
  have hl : 0 < den.toNat ∧ 1 ≤ (field.toNat : Int) - 150 + 150 ∧
      (field.toNat : Int) - 150 + 150 ≤ 254 ∧
      (if (field.toNat : Int) - 150 + 150 = 1 then den.toNat * 16777215 ≤ 2 * lo.toNat
        else den.toNat * 33554431 ≤ 4 * lo.toNat) ∧
      2 * lo.toNat ≤ den.toNat * 16777217 := of_decide_eq_true hlow
  have hu : 0 < den.toNat ∧ 1 ≤ (field.toNat : Int) - 150 + 150 ∧
      (field.toNat : Int) - 150 + 150 ≤ 254 ∧
      (if (field.toNat : Int) - 150 + 150 = 1 then den.toNat * 16777215 ≤ 2 * hi.toNat
        else den.toNat * 33554431 ≤ 4 * hi.toNat) ∧
      2 * hi.toNat ≤ den.toNat * 16777217 := of_decide_eq_true hhigh
  have hlower :
      (if (field.toNat : Int) - 150 + 150 = 1 then den.toNat * 16777215 ≤ 2 * num
        else den.toNat * 33554431 ≤ 4 * num) := by
    split_ifs at hl ⊢ <;> omega
  unfold R24PowerCell.powerCell
  apply decide_eq_true
  exact ⟨hl.1, hl.2.1, hl.2.2.1, hlower, by omega⟩

theorem powerCheck_sound (sign : Bool) (lo hi : UInt128) (den : UInt64) (field : UInt32)
    (num : Nat) (hlo : lo.toNat ≤ num) (hhi : num ≤ hi.toNat)
    (h : powerCheck lo hi den field = true) :
    FloatLib.Floats.Formats.BinaryInterchange.Model.NativeBinary32.roundRatScaled
        sign num den.toNat ((field.toNat : Int) - 150) =
      FloatLib.Floats.Formats.BinaryInterchange.Model.NativeBinary32.mkBits sign field.toNat 0 := by
  have hr := R24PowerCell.powerCell_sound sign num den.toNat
    ((field.toNat : Int) - 150) (powerCheck_cell lo hi den field num hlo hhi h)
  simpa only [sub_add_cancel, Int.toNat_natCast] using hr

end Submission.R24IntervalWord128


/- A cheap word proposal with no accuracy premise. It is data, never a proof.
   The exact interval certificate controls acceptance; failure belongs to the
   caller's unchanged exact fallback. Old ContractTensor helper, NOT_RUN. -/
namespace Submission.R24ArbitraryProposal
open FloatLib.Numerics.FixedWord

/-- Normal-range midpoint-up bit proposal. All UInt64 inputs are allowed. -/
@[inline] def magnitudeProposal (bits : UInt64) : UInt32 :=
  ((((bits &&& 0x7fffffffffffffff) + 0x10000000) >>> 29).toUInt32) - 0xc0000000

@[inline] def field (bits : UInt64) : UInt32 :=
  (magnitudeProposal bits >>> 23) &&& 255

@[inline] def mantissa (bits : UInt64) : UInt64 :=
  ((magnitudeProposal bits &&& 0x7fffff) ||| 0x800000).toUInt64

@[inline] def check (lo hi : UInt128) (den : UInt64) (bits : UInt64) : Bool :=
  if mantissa bits == 8388608 then
    R24IntervalWord128.powerCheck lo hi den (field bits)
  else R24IntervalWord128.strictCheck lo hi den (mantissa bits) (field bits)

/-- The result sign comes from the exact expression, separately from the hint. -/
@[inline] def word (sign : Bool) (bits : UInt64) : UInt32 :=
  FloatLib.Floats.Formats.BinaryInterchange.Model.NativeBinary32.mkBits
    sign (field bits).toNat ((mantissa bits).toNat - 8388608)

theorem check_sound (sign : Bool) (lo hi : UInt128) (den : UInt64) (bits : UInt64)
    (num : Nat) (hlo : lo.toNat ≤ num) (hhi : num ≤ hi.toNat)
    (h : check lo hi den bits = true) :
    FloatLib.Floats.Formats.BinaryInterchange.Model.NativeBinary32.roundRatScaled
        sign num den.toNat (((field bits).toNat : Int) - 150) = word sign bits := by
  by_cases hpower : mantissa bits = 8388608
  · have hc : R24IntervalWord128.powerCheck lo hi den (field bits) = true := by
      simpa only [check, beq_iff_eq, hpower, if_true] using h
    have hr := R24IntervalWord128.powerCheck_sound sign lo hi den (field bits) num hlo hhi hc
    simpa [word, hpower] using hr
  · have hc : R24IntervalWord128.strictCheck lo hi den (mantissa bits) (field bits) = true := by
      simpa only [check, beq_iff_eq, hpower, if_false] using h
    exact R24IntervalWord128.strictCheck_sound sign lo hi den (mantissa bits) (field bits) num hlo hhi hc

end Submission.R24ArbitraryProposal
