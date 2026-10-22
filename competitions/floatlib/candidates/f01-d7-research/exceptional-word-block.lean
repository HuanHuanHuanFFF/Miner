/-
R7 exceptional-word preparation. EVERY NEW DECLARATION BELOW IS NOT_RUN.
This is an append-only proof draft, not a candidate or a compilation receipt.

Intended context: exact f01-d7-nan-choice-probe ad014e0b...a3cb9, whose
global DWordNaN block is nan-choice-block.lean 584ace54...4c93c.
The new namespace is global. Do not insert it inside Submission without
adjusting the documented namespace context and rechecking the exact file.
Requires the original ContractTensor-only context and fixed FloatLib 0d918257.

Primary sources: fixed NativeBinary32 Agreement.lean, Base/Runtime.lean,
Model/Carrier.lean, Dyadic/Rounding.lean and Spec/Dyadic.lean, FloatLib Team/MIT.
The carrier projection follows the public R7-W01b Codec.lean proof.
The private library constant lemmas are NOT referenced; tiny local proofs
are written below. Existing context/options are retained; no Submission export.
-/
namespace DExceptionalWord

open FloatLib.Floats Competition
open FloatLib.Floats.Formats.BinaryInterchange

abbrev M := Model FloatFormat.binary32

/-- Word-only field tests. Mask-only replacements are a separate future proof. -/
@[inline] def rawInf (u : UInt32) : Bool :=
  Model.NativeBinary32.expField u == 0xff &&
    Model.NativeBinary32.fracField u == 0

@[inline] def rawZero (u : UInt32) : Bool :=
  Model.NativeBinary32.expField u == 0 &&
    Model.NativeBinary32.fracField u == 0

@[inline] def rawSign (u : UInt32) : Bool :=
  Model.NativeBinary32.signBit u

@[inline] def invalidWord : UInt32 := 0x7fc00000

/-- Bool inequality is the exact sign-XOR expression used by the fixed Spec. -/
@[inline] def infinityWord (negative : Bool) : UInt32 :=
  if negative then 0xff800000 else 0x7f800000

theorem rawInf_eq (u : UInt32) :
    rawInf u = Model.isInf (Model.NativeBinary32.ofUInt32 u) := by
  change
    (Model.NativeBinary32.expField u == 0xff &&
      Model.NativeBinary32.fracField u == 0) =
    (Model.expField (Model.NativeBinary32.ofUInt32 u) == 255 &&
      Model.fracField (Model.NativeBinary32.ofUInt32 u) == 0)
  have he := Model.NativeBinary32.expField_beq_allOnes
    (Model.NativeBinary32.ofUInt32 u)
  have hf := Model.NativeBinary32.fracField_beq_zero
    (Model.NativeBinary32.ofUInt32 u)
  simp only [Model.NativeBinary32.toUInt32_ofUInt32] at he hf
  rw [he, hf]

theorem rawZero_eq (u : UInt32) :
    rawZero u = Model.isZero (Model.NativeBinary32.ofUInt32 u) := by
  change
    (Model.NativeBinary32.expField u == 0 &&
      Model.NativeBinary32.fracField u == 0) =
    (Model.expField (Model.NativeBinary32.ofUInt32 u) == 0 &&
      Model.fracField (Model.NativeBinary32.ofUInt32 u) == 0)
  have he := Model.NativeBinary32.expField_beq_zero
    (Model.NativeBinary32.ofUInt32 u)
  have hf := Model.NativeBinary32.fracField_beq_zero
    (Model.NativeBinary32.ofUInt32 u)
  simp only [Model.NativeBinary32.toUInt32_ofUInt32] at he hf
  rw [he, hf]

theorem rawSign_eq (u : UInt32) :
    rawSign u = Model.signBit (Model.NativeBinary32.ofUInt32 u) := by
  simpa only [rawSign, Model.NativeBinary32.toUInt32_ofUInt32] using
    Model.NativeBinary32.signBit_eq (Model.NativeBinary32.ofUInt32 u)

/-- This is a closed constant equality, not enumeration of input words. -/
theorem invalidWord_eq :
    Model.NativeBinary32.ofUInt32 invalidWord =
      Model.invalidResult FloatFormat.binary32 := by
  change Model.NativeBinary32.ofUInt32 0x7fc00000 =
    Model.canonicalNaN FloatFormat.binary32
  decide

theorem infinityWord_eq (negative : Bool) :
    Model.NativeBinary32.ofUInt32 (infinityWord negative) =
      Model.nativeOverflow FloatFormat.binary32 negative := by
  rw [Model.nativeOverflow_eq_signedInf_of_isIEEE
    FloatFormat.binary32 (by decide)]
  cases negative <;> decide

/-- Correct only as an exceptional fallback; no finite arithmetic is done here. -/
@[inline] def addNoNaN (a b : UInt32) : UInt32 :=
  if rawInf a then
    if rawInf b then
      if rawSign a == rawSign b then a else invalidWord
    else a
  else if rawInf b then b
  else invalidWord

@[inline] def mulNoNaN (a b : UInt32) : UInt32 :=
  if rawInf a then
    if rawZero b then invalidWord
    else infinityWord (rawSign a != rawSign b)
  else if rawInf b then
    if rawZero a then invalidWord
    else infinityWord (rawSign a != rawSign b)
  else invalidWord

/-
Fused direct words: NO runtime call to rawChoose and NO Option-valued stage.
The Option form exists only in the following equality theorem for proof reuse.
-/
@[inline] def addWord (a b : UInt32) : UInt32 :=
  if DWordNaN.rawSNaN a then a ||| 0x00400000
  else if DWordNaN.rawSNaN b then b ||| 0x00400000
  else if DWordNaN.rawNaN a then a ||| 0x00400000
  else if DWordNaN.rawNaN b then b ||| 0x00400000
  else addNoNaN a b

@[inline] def mulWord (a b : UInt32) : UInt32 :=
  if DWordNaN.rawSNaN a then a ||| 0x00400000
  else if DWordNaN.rawSNaN b then b ||| 0x00400000
  else if DWordNaN.rawNaN a then a ||| 0x00400000
  else if DWordNaN.rawNaN b then b ||| 0x00400000
  else mulNoNaN a b

theorem addWord_eq_choice (a b : UInt32) :
    addWord a b =
      match DWordNaN.rawChoose a b with
      | some w => w
      | none => addNoNaN a b := by
  by_cases hsa : DWordNaN.rawSNaN a = true
  · simp [addWord, DWordNaN.rawChoose, hsa]
  · by_cases hsb : DWordNaN.rawSNaN b = true
    · simp [addWord, DWordNaN.rawChoose, hsa, hsb]
    · by_cases hna : DWordNaN.rawNaN a = true
      · simp [addWord, DWordNaN.rawChoose, hsa, hsb, hna]
      · by_cases hnb : DWordNaN.rawNaN b = true
        · simp [addWord, DWordNaN.rawChoose, hsa, hsb, hna, hnb]
        · simp [addWord, DWordNaN.rawChoose, hsa, hsb, hna, hnb]

theorem mulWord_eq_choice (a b : UInt32) :
    mulWord a b =
      match DWordNaN.rawChoose a b with
      | some w => w
      | none => mulNoNaN a b := by
  by_cases hsa : DWordNaN.rawSNaN a = true
  · simp [mulWord, DWordNaN.rawChoose, hsa]
  · by_cases hsb : DWordNaN.rawSNaN b = true
    · simp [mulWord, DWordNaN.rawChoose, hsa, hsb]
    · by_cases hna : DWordNaN.rawNaN a = true
      · simp [mulWord, DWordNaN.rawChoose, hsa, hsb, hna]
      · by_cases hnb : DWordNaN.rawNaN b = true
        · simp [mulWord, DWordNaN.rawChoose, hsa, hsb, hna, hnb]
        · simp [mulWord, DWordNaN.rawChoose, hsa, hsb, hna, hnb]

theorem addNoNaN_model (a b : UInt32) :
    Model.NativeBinary32.ofUInt32 (addNoNaN a b) =
      (if Model.isInf (Model.NativeBinary32.ofUInt32 a) then
        if Model.isInf (Model.NativeBinary32.ofUInt32 b) then
          if Model.signBit (Model.NativeBinary32.ofUInt32 a) ==
              Model.signBit (Model.NativeBinary32.ofUInt32 b) then
            Model.NativeBinary32.ofUInt32 a
          else Model.invalidResult FloatFormat.binary32
        else Model.NativeBinary32.ofUInt32 a
      else if Model.isInf (Model.NativeBinary32.ofUInt32 b) then
        Model.NativeBinary32.ofUInt32 b
      else Model.invalidResult FloatFormat.binary32) := by
  simp only [addNoNaN, rawInf_eq, rawSign_eq] <;>
    (split_ifs <;> simp only [invalidWord_eq])

theorem mulNoNaN_model (a b : UInt32) :
    Model.NativeBinary32.ofUInt32 (mulNoNaN a b) =
      (if Model.isInf (Model.NativeBinary32.ofUInt32 a) then
        if Model.isZero (Model.NativeBinary32.ofUInt32 b) then
          Model.invalidResult FloatFormat.binary32
        else Model.nativeOverflow FloatFormat.binary32
          (Model.signBit (Model.NativeBinary32.ofUInt32 a) !=
            Model.signBit (Model.NativeBinary32.ofUInt32 b))
      else if Model.isInf (Model.NativeBinary32.ofUInt32 b) then
        if Model.isZero (Model.NativeBinary32.ofUInt32 a) then
          Model.invalidResult FloatFormat.binary32
        else Model.nativeOverflow FloatFormat.binary32
          (Model.signBit (Model.NativeBinary32.ofUInt32 a) !=
            Model.signBit (Model.NativeBinary32.ofUInt32 b))
      else Model.invalidResult FloatFormat.binary32) := by
  simp only [mulNoNaN, rawInf_eq, rawZero_eq, rawSign_eq] <;>
    (split_ifs <;> simp only [invalidWord_eq, infinityWord_eq])

/-- The real call-site rejection implies a special exponent on at least one side. -/
theorem special_of_rejected (a b : UInt32)
    (h : ¬ (Model.NativeBinary32.expField a ≠ 0xff ∧
      Model.NativeBinary32.expField b ≠ 0xff)) :
    Model.NativeBinary32.expField a = 0xff ∨
      Model.NativeBinary32.expField b = 0xff := by
  by_cases ha : Model.NativeBinary32.expField a = 0xff
  · exact Or.inl ha
  · by_cases hb : Model.NativeBinary32.expField b = 0xff
    · exact Or.inr hb
    · exact False.elim (h ⟨ha, hb⟩)

theorem addWord_model (a b : UInt32)
    (h : Model.NativeBinary32.expField a = 0xff ∨
      Model.NativeBinary32.expField b = 0xff) :
    Model.NativeBinary32.ofUInt32 (addWord a b) =
      Model.Spec.add (Model.NativeBinary32.ofUInt32 a)
        (Model.NativeBinary32.ofUInt32 b) := by
  rw [addWord_eq_choice]
  cases hc : DWordNaN.rawChoose a b with
  | some w => exact DWordNaN.selected_model_add a b w hc
  | none =>
    have hm : Model.chooseNaN2 (Model.NativeBinary32.ofUInt32 a)
        (Model.NativeBinary32.ofUInt32 b) = none := by
      simp only [← DWordNaN.rawChoose_eq, hc, Option.map_none]
    have hbody := addNoNaN_model a b
    rcases h with ha | hb
    · unfold Model.Spec.add
      rw [DWordNaN.specialDecode a ha]
      cases Model.toDyadic? (Model.NativeBinary32.ofUInt32 b) <;>
        simpa only [hm] using hbody
    · unfold Model.Spec.add
      rw [DWordNaN.specialDecode b hb]
      cases Model.toDyadic? (Model.NativeBinary32.ofUInt32 a) <;>
        simpa only [hm] using hbody

theorem mulWord_model (a b : UInt32)
    (h : Model.NativeBinary32.expField a = 0xff ∨
      Model.NativeBinary32.expField b = 0xff) :
    Model.NativeBinary32.ofUInt32 (mulWord a b) =
      Model.Spec.mul (Model.NativeBinary32.ofUInt32 a)
        (Model.NativeBinary32.ofUInt32 b) := by
  rw [mulWord_eq_choice]
  cases hc : DWordNaN.rawChoose a b with
  | some w => exact DWordNaN.selected_model_mul a b w hc
  | none =>
    have hm : Model.chooseNaN2 (Model.NativeBinary32.ofUInt32 a)
        (Model.NativeBinary32.ofUInt32 b) = none := by
      simp only [← DWordNaN.rawChoose_eq, hc, Option.map_none]
    have hbody := mulNoNaN_model a b
    rcases h with ha | hb
    · unfold Model.Spec.mul
      rw [DWordNaN.specialDecode a ha]
      cases Model.toDyadic? (Model.NativeBinary32.ofUInt32 b) <;>
        simpa only [hm] using hbody
    · unfold Model.Spec.mul
      rw [DWordNaN.specialDecode b hb]
      cases Model.toDyadic? (Model.NativeBinary32.ofUInt32 a) <;>
        simpa only [hm] using hbody

/-- Concrete existing carrier projection, including every NaN sign/payload bit. -/
theorem carrier_model (q : Binary32) :
    ExecFloat.Binary.toModel q = Model.NativeBinary32.ofUInt32 q.raw.1 := by
  change Model.ofBits (fmt := FloatFormat.binary32)
      (BitVec.ofNatLT q.raw.1.toNat q.raw.2) =
    Model.ofBits (fmt := FloatFormat.binary32) q.raw.1.toBitVec
  apply congrArg (Model.ofBits (fmt := FloatFormat.binary32))
  apply BitVec.eq_of_toNat_eq
  rfl

theorem ofBits_model (w : UInt32) :
    ExecFloat.Binary.toModel (Submission.FastMul.ofBits w) =
      Model.NativeBinary32.ofUInt32 w := by
  exact carrier_model (Submission.FastMul.ofBits w)

@[inline] def addCold (x y : Binary32) : Binary32 :=
  Submission.FastMul.ofBits (addWord x.raw.1 y.raw.1)

@[inline] def mulCold (x y : Binary32) : Binary32 :=
  Submission.FastMul.ofBits (mulWord x.raw.1 y.raw.1)

theorem addCold_spec (x y : Binary32)
    (h : ¬ (Model.NativeBinary32.expField x.raw.1 ≠ 0xff ∧
      Model.NativeBinary32.expField y.raw.1 ≠ 0xff)) :
    addCold x y = ExecFloat.Spec.add x y := by
  rw [← ExecFloat.Proof.add_eq_spec]
  apply Configured.Family.toModel_injective
  change ExecFloat.Binary.toModel
      (Submission.FastMul.ofBits (addWord x.raw.1 y.raw.1)) =
    ExecFloat.Binary.toModel (ExecFloat.add x y)
  rw [ofBits_model, Submission.R7Native.toModelExecAdd,
    carrier_model x, carrier_model y]
  exact addWord_model _ _ (special_of_rejected _ _ h)

theorem mulCold_spec (x y : Binary32)
    (h : ¬ (Model.NativeBinary32.expField x.raw.1 ≠ 0xff ∧
      Model.NativeBinary32.expField y.raw.1 ≠ 0xff)) :
    mulCold x y = ExecFloat.Spec.mul x y := by
  rw [← ExecFloat.Proof.mul_eq_spec]
  apply Configured.Family.toModel_injective
  change ExecFloat.Binary.toModel
      (Submission.FastMul.ofBits (mulWord x.raw.1 y.raw.1)) =
    ExecFloat.Binary.toModel (ExecFloat.mul x y)
  rw [ofBits_model, Submission.NativeBridge.toModelExecMul,
    carrier_model x, carrier_model y]
  exact mulWord_model _ _ (special_of_rejected _ _ h)

end DExceptionalWord
