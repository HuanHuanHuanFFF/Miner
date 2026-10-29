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


/- Old ContractTensor mathematical component. Source and candidate exponents
   remain separate; logical normalization may use arbitrary Nat denominators,
   but the executable checker below never constructs them. NOT_COMPILED. -/
namespace Submission.R24ScaledCell

open FloatLib.Floats FloatLib.Floats.Formats.BinaryInterchange
open FloatLib.Numerics

theorem normalize_strict (num den mant : Nat) (source target : Int)
    (hd : 0 < den)
    (hl : (den : Real) * (2 * mant - 1 : Nat) * Model.bpow target <
      2 * (num : Real) * Model.bpow source)
    (hu : 2 * (num : Real) * Model.bpow source <
      (den : Real) * (2 * mant + 1 : Nat) * Model.bpow target) :
    let scaled := RationalBinary.scaleByPowerOfTwo num den (source - target)
    0 < scaled.2 ∧ scaled.2 * (2 * mant - 1) < 2 * scaled.1 ∧
      2 * scaled.1 < scaled.2 * (2 * mant + 1) := by
  let scaled := RationalBinary.scaleByPowerOfTwo num den (source - target)
  let v : Real := (num : Real) / den * Model.bpow (source - target)
  have hdR : (0 : Real) < den := by exact_mod_cast hd
  have hs : Model.bpow (source - target) * Model.bpow target = Model.bpow source := by
    rw [← Model.bpow_add]
    congr 1
    omega
  have hlN : (den : Real) * (2 * mant - 1 : Nat) <
      2 * (num : Real) * Model.bpow (source - target) := by
    apply (mul_lt_mul_right (Model.bpow_pos target)).mp
    simpa only [mul_assoc, hs] using hl
  have huN : 2 * (num : Real) * Model.bpow (source - target) <
      (den : Real) * (2 * mant + 1 : Nat) := by
    apply (mul_lt_mul_right (Model.bpow_pos target)).mp
    simpa only [mul_assoc, hs] using hu
  have hDv : (den : Real) * (2 * v) =
      2 * (num : Real) * Model.bpow (source - target) := by
    dsimp [v]
    field_simp [hdR.ne'] <;> ring
  have hlV : (2 * mant - 1 : Nat) < 2 * v := by
    apply (mul_lt_mul_left hdR).mp
    rw [hDv]
    exact hlN
  have huV : 2 * v < (2 * mant + 1 : Nat) := by
    apply (mul_lt_mul_left hdR).mp
    rw [hDv]
    exact huN
  have hdS : 0 < scaled.2 := Nat.pos_of_ne_zero
    (RationalBinary.scaleByPowerOfTwo_snd_ne_zero num den (source - target) (Nat.ne_of_gt hd))
  have hdSR : (0 : Real) < scaled.2 := by exact_mod_cast hdS
  have hv : (scaled.1 : Real) / scaled.2 = v := by
    simpa only [Model.scaledRatToReal] using Model.scaleByPowerOfTwo_real num den (source - target)
  have hSv : (scaled.2 : Real) * v = scaled.1 := by
    rw [← hv]
    field_simp [hdSR.ne']
  have hlS : (scaled.2 : Real) * (2 * mant - 1 : Nat) < 2 * (scaled.1 : Real) := by
    calc
      (scaled.2 : Real) * (2 * mant - 1 : Nat) < (scaled.2 : Real) * (2 * v) :=
        mul_lt_mul_of_pos_left hlV hdSR
      _ = 2 * (scaled.1 : Real) := by nlinarith only [hSv]
  have huS : 2 * (scaled.1 : Real) < (scaled.2 : Real) * (2 * mant + 1 : Nat) := by
    calc
      2 * (scaled.1 : Real) = (scaled.2 : Real) * (2 * v) := by nlinarith only [hSv]
      _ < (scaled.2 : Real) * (2 * mant + 1 : Nat) := mul_lt_mul_of_pos_left huV hdSR
  refine ⟨hdS, ?_, ?_⟩
  · exact_mod_cast hlS
  · exact_mod_cast huS

theorem native32_scaled_strict (sign : Bool) (num den mant : Nat) (source target : Int)
    (hd : 0 < den) (hmlo : 8388608 < mant) (hmhi : mant < 16777216)
    (hexplo : 1 ≤ target + 150) (hexphi : target + 150 ≤ 254)
    (hl : (den : Real) * (2 * mant - 1 : Nat) * Model.bpow target <
      2 * (num : Real) * Model.bpow source)
    (hu : 2 * (num : Real) * Model.bpow source <
      (den : Real) * (2 * mant + 1 : Nat) * Model.bpow target) :
    Model.NativeBinary32.roundRatScaled sign num den source =
      Model.NativeBinary32.mkBits sign (target + 150).toNat (mant - 8388608) := by
  let scaled := RationalBinary.scaleByPowerOfTwo num den (source - target)
  let v : Real := (num : Real) / den * Model.bpow (source - target)
  obtain ⟨hdS, hlS, huS⟩ := normalize_strict num den mant source target hd hl hu
  have hv : (scaled.1 : Real) / scaled.2 = v := by
    simpa only [Model.scaledRatToReal] using Model.scaleByPowerOfTwo_real num den (source - target)
  have hdSR : (0 : Real) < scaled.2 := by exact_mod_cast hdS
  obtain ⟨hboundL, hboundU⟩ := Submission.R24CellPrimitive.normal_ratio_nat_bounds
    scaled.1 scaled.2 mant hdS hmlo hmhi hlS huS
  have hvL : (8388608 : Real) ≤ v := by
    rw [← hv]
    apply (le_div_iff₀ hdSR).mpr
    exact_mod_cast hboundL
  have hvU : v < (16777216 : Real) := by
    rw [← hv]
    apply (div_lt_iff₀ hdSR).mpr
    exact_mod_cast hboundU
  have hn : num ≠ 0 := by
    intro hz
    simp only [v, hz, Nat.cast_zero, zero_div, zero_mul] at hvL
    norm_num at hvL
  have hp23 : Model.bpow (23 : Int) = (8388608 : Real) := by
    norm_num [Model.bpow, FloatLib.Floats.Formats.Flocq.bpow,
      binaryRadix, Radix.toReal]
  have hp24 : Model.bpow (24 : Int) = (16777216 : Real) := by
    norm_num [Model.bpow, FloatLib.Floats.Formats.Flocq.bpow,
      binaryRadix, Radix.toReal]
  have hs : Model.bpow (source - target) * Model.bpow (target - source) = 1 := by
    rw [← Model.bpow_add, show source - target + (target - source) = 0 by omega,
      Model.bpow_zero]
  have hback : v * Model.bpow (target - source) = (num : Real) / den := by
    dsimp [v]
    rw [mul_assoc, hs, mul_one]
  have hlog : RationalBinary.floorLog2 num den = target - source + 23 := by
    apply Model.floorLog2_eq_of_bounds num den (target - source + 23) hn (Nat.ne_of_gt hd)
    · rw [Model.bpow_add, hp23, mul_comm]
      calc
        (8388608 : Real) * Model.bpow (target - source) ≤
            v * Model.bpow (target - source) :=
          mul_le_mul_of_nonneg_right hvL (Model.bpow_nonneg _)
        _ = (num : Real) / den := hback
    · rw [show target - source + 23 + 1 = target - source + 24 by omega,
        Model.bpow_add, hp24, mul_comm]
      calc
        (num : Real) / den = v * Model.bpow (target - source) := hback.symm
        _ < (16777216 : Real) * Model.bpow (target - source) :=
          mul_lt_mul_of_pos_right hvU (Model.bpow_pos _)
  have hr := Submission.R24CellPrimitive.quotient_strict_midpoint
    scaled.1 scaled.2 mant hdS (by omega) hlS huS
  have htotal : target - source + 23 + source = target + 23 := by omega
  have hshift : (23 : Int) - (target - source + 23) = source - target := by omega
  have hbig : ¬ target + 23 > 127 := by omega
  have hsmall : ¬ target + 23 < -150 := by omega
  have hnormal : ¬ target + 23 < -126 := by omega
  have hc : mant ≠ Model.pow2 24 := by
    have hp : Model.pow2 24 = 16777216 := by decide
    rw [hp]
    omega
  have hencoded : target + 23 + 127 = target + 150 := by omega
  have hpow23 : Model.pow2 23 = 8388608 := by decide
  simp only [Model.NativeBinary32.roundRatScaled, beq_iff_eq, Nat.ne_of_gt hd,
    hn, if_false, hlog, htotal, hbig, hsmall, hnormal, hshift]
  simp only [hr, beq_iff_eq, hc, if_false, hbig, hencoded, hpow23]

end Submission.R24ScaledCell


/- Concrete fixed-word check with independent source/candidate exponents.
   No normalized denominator is constructed by this runtime. NOT_COMPILED. -/
namespace Submission.R24ScaledWord128

open FloatLib.Numerics FloatLib.Numerics.FixedWord
open FloatLib.Floats FloatLib.Floats.Formats.BinaryInterchange

@[inline] def fastAllowed (num : UInt128) (source : Int) (word : UInt64) (target : Int) : Bool :=
  if num.hi != 0 then true
  else if source ≤ target then
    let shift := (target - source).toNat
    decide (shift < 64) && decide (DyadicCompare.shiftFits word shift)
  else
    let shift := (source - target).toNat
    decide (shift < 64) && decide (DyadicCompare.shiftFits num.lo shift)

@[inline] def midpointWords (den mant : UInt64) : UInt64 × UInt64 :=
  let twice := den * (mant + mant)
  (twice - den, twice + den)

theorem midpointWords_exact (den mant : UInt64)
    (hdcap : den.toNat < 274877906944)
    (hmlo : 8388608 < mant.toNat) (hmhi : mant.toNat < 16777216) :
    (midpointWords den mant).1.toNat = den.toNat * (2 * mant.toNat - 1) ∧
      (midpointWords den mant).2.toNat = den.toNat * (2 * mant.toNat + 1) := by
  have htwiceFit : mant.toNat + mant.toNat < UInt64.size := by
    change mant.toNat + mant.toNat < 18446744073709551616
    omega
  have htwice : (mant + mant).toNat = 2 * mant.toNat := by
    rw [UInt64.toNat_add, Nat.mod_eq_of_lt htwiceFit]
    omega
  have hbound : den.toNat * (2 * mant.toNat + 1) < 9223372036854775808 := by
    calc
      den.toNat * (2 * mant.toNat + 1) < 274877906944 * 33554432 :=
        Nat.mul_lt_mul'' hdcap (by omega)
      _ = 9223372036854775808 := by decide
  have hmidFit : den.toNat * (2 * mant.toNat) < UInt64.size := by
    change den.toNat * (2 * mant.toNat) < 18446744073709551616
    nlinarith
  have hmid : (den * (mant + mant)).toNat = den.toNat * (2 * mant.toNat) := by
    rw [UInt64.toNat_mul, htwice, Nat.mod_eq_of_lt hmidFit]
  have hle : den ≤ den * (mant + mant) := by
    apply UInt64.le_iff_toNat_le.mpr
    rw [hmid]
    nlinarith
  have hupperFit : (den * (mant + mant)).toNat + den.toNat < UInt64.size := by
    rw [hmid]
    change den.toNat * (2 * mant.toNat) + den.toNat < 18446744073709551616
    nlinarith
  have hcut : 2 * mant.toNat - 1 + 1 = 2 * mant.toNat := by omega
  have hcutD : den.toNat * (2 * mant.toNat - 1) + den.toNat =
      den.toNat * (2 * mant.toNat) := by
    calc
      den.toNat * (2 * mant.toNat - 1) + den.toNat =
          den.toNat * ((2 * mant.toNat - 1) + 1) := by ring
      _ = _ := by rw [hcut]
  constructor
  · change (den * (mant + mant) - den).toNat = _
    rw [UInt64.toNat_sub_of_le _ _ hle, hmid]
    omega
  · change (den * (mant + mant) + den).toNat = _
    rw [UInt64.toNat_add, Nat.mod_eq_of_lt hupperFit, hmid]
    ring

theorem compare_lt (num : UInt128) (source : Int) (word : UInt64) (target : Int)
    (h : DyadicCompare.compareNonnegative128ToWord num source word target = .lt) :
    (num.toNat : Real) * Model.bpow source < (word.toNat : Real) * Model.bpow target := by
  rw [DyadicCompare.compareNonnegative128ToWord_eq,
    Dyadic.compareNonnegativeFields_eq_compareFields, Dyadic.compareFields_eq] at h
  let left : Dyadic := ⟨false, num.toNat, source⟩
  let right : Dyadic := ⟨false, word.toNat, target⟩
  change left.compare right = .lt at h
  have hr := (Dyadic.compare_eq_lt_iff left right).mp h
  have hrR : (left.toRat : Real) < (right.toRat : Real) := by exact_mod_cast hr
  simpa [left, right, Dyadic.toRat, Dyadic.signedSignificand, Model.bpow,
    FloatLib.Floats.Formats.Flocq.bpow, binaryRadix, Radix.toReal] using hrR

theorem compare_gt (num : UInt128) (source : Int) (word : UInt64) (target : Int)
    (h : DyadicCompare.compareNonnegative128ToWord num source word target = .gt) :
    (word.toNat : Real) * Model.bpow target < (num.toNat : Real) * Model.bpow source := by
  rw [DyadicCompare.compareNonnegative128ToWord_eq,
    Dyadic.compareNonnegativeFields_eq_compareFields, Dyadic.compareFields_eq] at h
  let left : Dyadic := ⟨false, num.toNat, source⟩
  let right : Dyadic := ⟨false, word.toNat, target⟩
  change left.compare right = .gt at h
  have hr := (Dyadic.compare_eq_gt_iff left right).mp h
  have hrR : (right.toRat : Real) < (left.toRat : Real) := by exact_mod_cast hr
  simpa [left, right, Dyadic.toRat, Dyadic.signedSignificand, Model.bpow,
    FloatLib.Floats.Formats.Flocq.bpow, binaryRadix, Radix.toReal] using hrR

@[inline] def check (num : UInt128) (den mant : UInt64) (source target : Int) : Bool :=
  if (0 : UInt64) < den ∧ den < 274877906944 ∧ 8388608 < mant ∧ mant < 16777216 ∧
      1 ≤ target + 150 ∧ target + 150 ≤ 254 then
    let bounds := midpointWords den mant
    if fastAllowed num (source + 1) bounds.1 target && fastAllowed num (source + 1) bounds.2 target then
      DyadicCompare.compareNonnegative128ToWord num (source + 1) bounds.1 target == .gt &&
        DyadicCompare.compareNonnegative128ToWord num (source + 1) bounds.2 target == .lt
    else false
  else false

theorem check_sound (sign : Bool) (num : UInt128) (den mant : UInt64) (source target : Int)
    (h : check num den mant source target = true) :
    Model.NativeBinary32.roundRatScaled sign num.toNat den.toNat source =
      Model.NativeBinary32.mkBits sign (target + 150).toNat (mant.toNat - 8388608) := by
  have hfit : (0 : UInt64) < den ∧ den < 274877906944 ∧ 8388608 < mant ∧ mant < 16777216 ∧
      1 ≤ target + 150 ∧ target + 150 ≤ 254 := by
    by_contra hn
    simp only [check, if_neg hn] at h
    contradiction
  have hd : 0 < den.toNat := UInt64.lt_iff_toNat_lt.mp hfit.1
  have hdcap : den.toNat < 274877906944 := UInt64.lt_iff_toNat_lt.mp hfit.2.1
  have hmlo : 8388608 < mant.toNat := UInt64.lt_iff_toNat_lt.mp hfit.2.2.1
  have hmhi : mant.toNat < 16777216 := UInt64.lt_iff_toNat_lt.mp hfit.2.2.2.1
  let bounds := midpointWords den mant
  have hcmp : DyadicCompare.compareNonnegative128ToWord num (source + 1) bounds.1 target = .gt ∧
      DyadicCompare.compareNonnegative128ToWord num (source + 1) bounds.2 target = .lt := by
    unfold check at h
    simp only [if_pos hfit] at h
    split at h
    · simpa only [Bool.and_eq_true, beq_iff_eq] using h
    · simp at h
  have hl := compare_gt num (source + 1) bounds.1 target hcmp.1
  have hu := compare_lt num (source + 1) bounds.2 target hcmp.2
  obtain ⟨hbl, hbu⟩ := midpointWords_exact den mant hdcap hmlo hmhi
  have hpower : (num.toNat : Real) * Model.bpow (source + 1) =
      2 * (num.toNat : Real) * Model.bpow source := by
    rw [Model.bpow_add, Model.bpow_one]
    ring
  apply Submission.R24ScaledCell.native32_scaled_strict sign num.toNat den.toNat mant.toNat
    source target hd hmlo hmhi hfit.2.2.2.2.1 hfit.2.2.2.2.2
  · simpa only [bounds, hbl, Nat.cast_mul, hpower] using hl
  · simpa only [bounds, hbu, Nat.cast_mul, hpower] using hu

end Submission.R24ScaledWord128


/- Scaled dyadic interval controller. Endpoint words and logical exponents avoid
   constructing the exact value or a widened normalized denominator at runtime.
   Old ContractTensor mathematical helper; typing/replay/AX/native cost NOT_RUN. -/
namespace Submission.R24DyadicInterval128
open FloatLib.Numerics FloatLib.Numerics.FixedWord
open FloatLib.Floats FloatLib.Floats.Formats.BinaryInterchange

@[inline] def check (lo hi : UInt128) (scale : Int) (mant : UInt64) (field : UInt32) : Bool :=
  if (1 : UInt32) ≤ field ∧ field ≤ 254 ∧ (8388608 : UInt64) < mant ∧ mant < 16777216 then
    let target := (field.toNat : Int) - 150
    let bounds := R24ScaledWord128.midpointWords 1 mant
    if R24ScaledWord128.fastAllowed lo (scale + 1) bounds.1 target &&
        R24ScaledWord128.fastAllowed hi (scale + 1) bounds.2 target then
      (!UInt128.less hi lo) &&
        ((DyadicCompare.compareNonnegative128ToWord lo (scale + 1) bounds.1 target == .gt) &&
          (DyadicCompare.compareNonnegative128ToWord hi (scale + 1) bounds.2 target == .lt))
    else false
  else false

theorem check_bounds (lo hi : UInt128) (scale : Int) (mant : UInt64) (field : UInt32)
    (h : check lo hi scale mant field = true) :
    1 ≤ field.toNat ∧ field.toNat ≤ 254 ∧ 8388608 < mant.toNat ∧ mant.toNat < 16777216 ∧
      ((2 * mant.toNat - 1 : Nat) : Real) * Model.bpow ((field.toNat : Int) - 150) <
        2 * (lo.toNat : Real) * Model.bpow scale ∧
      2 * (hi.toNat : Real) * Model.bpow scale <
        ((2 * mant.toNat + 1 : Nat) : Real) * Model.bpow ((field.toNat : Int) - 150) := by
  have hfit : (1 : UInt32) ≤ field ∧ field ≤ 254 ∧ (8388608 : UInt64) < mant ∧ mant < 16777216 := by
    by_contra hn
    simp only [check, if_neg hn] at h
    contradiction
  have hf0 : 1 ≤ field.toNat := UInt32.le_iff_toNat_le.mp hfit.1
  have hf1 : field.toNat ≤ 254 := UInt32.le_iff_toNat_le.mp hfit.2.1
  have hm0 : 8388608 < mant.toNat := UInt64.lt_iff_toNat_lt.mp hfit.2.2.1
  have hm1 : mant.toNat < 16777216 := UInt64.lt_iff_toNat_lt.mp hfit.2.2.2
  let target := (field.toNat : Int) - 150
  let bounds := R24ScaledWord128.midpointWords 1 mant
  have hcmp : DyadicCompare.compareNonnegative128ToWord lo (scale + 1) bounds.1 target = .gt ∧
      DyadicCompare.compareNonnegative128ToWord hi (scale + 1) bounds.2 target = .lt := by
    unfold check at h
    simp only [if_pos hfit] at h
    split at h
    · have hh : (!UInt128.less hi lo) = true ∧
          (DyadicCompare.compareNonnegative128ToWord lo (scale + 1) bounds.1 target = .gt ∧
            DyadicCompare.compareNonnegative128ToWord hi (scale + 1) bounds.2 target = .lt) := by
        simpa only [Bool.and_eq_true, beq_iff_eq] using h
      exact hh.2
    · simp at h
  have hl := R24ScaledWord128.compare_gt lo (scale + 1) bounds.1 target hcmp.1
  have hu := R24ScaledWord128.compare_lt hi (scale + 1) bounds.2 target hcmp.2
  obtain ⟨hbl, hbu⟩ := R24ScaledWord128.midpointWords_exact 1 mant (by decide) hm0 hm1
  have hpower (n : UInt128) : (n.toNat : Real) * Model.bpow (scale + 1) =
      2 * (n.toNat : Real) * Model.bpow scale := by
    rw [Model.bpow_add, Model.bpow_one]
    ring
  refine ⟨hf0, hf1, hm0, hm1, ?_, ?_⟩
  · simpa only [bounds, hbl, one_mul, hpower] using hl
  · simpa only [bounds, hbu, one_mul, hpower] using hu

theorem check_sound (sign : Bool) (lo hi : UInt128) (scale : Int) (mant : UInt64)
    (field : UInt32) (num den : Nat) (source : Int) (hd : 0 < den)
    (hlo : (lo.toNat : Real) * Model.bpow scale ≤ Model.scaledRatToReal num den source)
    (hhi : Model.scaledRatToReal num den source ≤ (hi.toNat : Real) * Model.bpow scale)
    (h : check lo hi scale mant field = true) :
    Model.NativeBinary32.roundRatScaled sign num den source =
      Model.NativeBinary32.mkBits sign field.toNat (mant.toNat - 8388608) := by
  obtain ⟨hf0, hf1, hm0, hm1, hl, hu⟩ := check_bounds lo hi scale mant field h
  let value := Model.scaledRatToReal num den source
  have hlow : ((2 * mant.toNat - 1 : Nat) : Real) * Model.bpow ((field.toNat : Int) - 150) <
      2 * value := by
    dsimp [value]
    linarith
  have hhigh : 2 * value <
      ((2 * mant.toNat + 1 : Nat) : Real) * Model.bpow ((field.toNat : Int) - 150) := by
    dsimp [value]
    linarith
  have hdR : (0 : Real) < den := by exact_mod_cast hd
  have hDv : (den : Real) * value = (num : Real) * Model.bpow source := by
    dsimp [value, Model.scaledRatToReal]
    field_simp [hdR.ne'] <;> ring
  have hl' : (den : Real) * (2 * mant.toNat - 1 : Nat) * Model.bpow ((field.toNat : Int) - 150) <
      2 * (num : Real) * Model.bpow source := by
    have hm := mul_lt_mul_of_pos_left hlow hdR
    nlinarith only [hm, hDv]
  have hu' : 2 * (num : Real) * Model.bpow source <
      (den : Real) * (2 * mant.toNat + 1 : Nat) * Model.bpow ((field.toNat : Int) - 150) := by
    have hm := mul_lt_mul_of_pos_left hhigh hdR
    nlinarith only [hm, hDv]
  have hr := R24ScaledCell.native32_scaled_strict sign num den mant.toNat source
    ((field.toNat : Int) - 150) hd hm0 hm1 (by omega) (by omega) hl' hu'
  simpa only [sub_add_cancel, Int.toNat_natCast] using hr

end Submission.R24DyadicInterval128
