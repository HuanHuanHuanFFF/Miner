import ContractTensor

namespace R7W04

/-- Native Float32 self-comparison: true exactly for all non-NaN values. -/
@[inline] def nonNaN (x : Float32) : Bool := x == x

private theorem unpacked_self_beq_eq_not_isNaN (x : Float.Model.UnpackedFloat) :
    x.beq x = !x.isNaN := by
  cases x with
  | infinity sign => cases sign <;> rfl
  | notANumber => rfl
  | zero sign => cases sign <;> rfl
  | finite sign mantissa exponent positive =>
      cases sign <;>
        simp [Float.Model.UnpackedFloat.beq, Float.Model.UnpackedFloat.compare,
          Float.Model.UnpackedFloat.isNaN]

/-- The actual logical model's IEEE Boolean equality is self-true exactly off NaN. -/
theorem model_self_beq_eq_not_isNaN (x : Float32.Model) :
    (x == x) = !x.isNaN := by
  change x.unpack.beq x.unpack = !x.unpack.isNaN
  exact unpacked_self_beq_eq_not_isNaN x.unpack

/-- All-input theorem about the actual Float32 equality and actual Float32.isNaN. -/
theorem self_beq_eq_not_isNaN (x : Float32) :
    (x == x) = !x.isNaN := by
  change (x.toModel == x.toModel) = !x.toModel.isNaN
  exact model_self_beq_eq_not_isNaN x.toModel

/-- Exact Boolean specification of the executable guard. -/
theorem nonNaN_eq_not_isNaN (x : Float32) : nonNaN x = !x.isNaN :=
  self_beq_eq_not_isNaN x

/-- The true branch of the native guard has precisely the intended non-NaN condition. -/
theorem nonNaN_eq_true_iff (x : Float32) :
    nonNaN x = true ↔ x.isNaN = false := by
  rw [nonNaN_eq_not_isNaN]
  simp

/-- The false branch of the same guard has precisely the NaN condition. -/
theorem nonNaN_eq_false_iff (x : Float32) :
    nonNaN x = false ↔ x.isNaN = true := by
  rw [nonNaN_eq_not_isNaN]
  simp


end R7W04

section R7NaNProof

/- R7-W01; exact public model, compiler status in verification-summary.json. -/


/- R7-W01: exact binary32 quiet-bit proofs. The real Model definitions are used.
   Status is recorded in verification logs; no proof assumptions are introduced. -/
namespace R7W01
open FloatLib.Floats.Formats.BinaryInterchange
open FloatLib.Floats.Formats.BinaryInterchange.Model

abbrev F32 := FloatFormat.binary32
abbrev M32 := Model F32

@[inline] def bits32 (x : M32) : BitVec 32 := x.bits
@[inline] def fromBits32 (b : BitVec 32) : M32 := ofBits (fmt := F32) b

private theorem quietMask_getLsbD (i : Nat) :
    (4194304#32 : BitVec 32).getLsbD i = decide (i = 22) := by
  rw [BitVec.getLsbD_ofNat]
  by_cases hi : i < 32
  · simp only [hi, decide_true, Bool.true_and]
    change (2 ^ 22).testBit i = decide (i = 22)
    simpa [eq_comm] using (Nat.testBit_two_pow (n := 22) (m := i))
  · have : i ≠ 22 := by omega
    simp [hi, this]

theorem set_quietMask (bits : BitVec 32) :
    (bits ||| (4194304#32)) &&& (4194304#32) = (4194304#32) := by
  apply BitVec.eq_of_getLsbD_eq
  intro i hi
  simp only [BitVec.getLsbD_and, BitVec.getLsbD_or]
  cases bits.getLsbD i <;> cases (4194304#32 : BitVec 32).getLsbD i <;> rfl

theorem or_quietMask_eq_self (bits : BitVec 32)
    (h : bits &&& (4194304#32) ≠ 0) :
    bits ||| (4194304#32) = bits := by
  have hbit : bits.getLsbD 22 = true := by
    cases hb : bits.getLsbD 22
    · have hz : bits &&& (4194304#32) = 0 := by
        apply BitVec.eq_of_getLsbD_eq
        intro i hi
        by_cases heq : i = 22
        · subst i
          rw [BitVec.getLsbD_and]
          change (bits.getLsbD 22 && true) = false
          rw [hb]
          rfl
        · simp [BitVec.getLsbD_and, quietMask_getLsbD, heq]
      exact (h hz).elim
    · rfl
  apply BitVec.eq_of_getLsbD_eq
  intro i hi
  by_cases heq : i = 22
  · subst i
    rw [BitVec.getLsbD_or]
    change (bits.getLsbD 22 || true) = bits.getLsbD 22
    rw [hbit]
    rfl
  · simp [BitVec.getLsbD_or, quietMask_getLsbD, heq]

/-- Quieting either changes a NaN's bit 22 to one or leaves a non-NaN unchanged. -/
theorem quietNaN32_not_snan (x : M32) :
    isSNaN (quietNaN x) = false := by
  change IEEE.isSNaN
    (if IEEE.isNaN x then fromBits32 (bits32 x ||| (4194304#32)) else x) = false
  cases hn : IEEE.isNaN x
  · simp [hn, IEEE.isSNaN]
  · simp only [hn, Bool.true_eq, ite_true]
    change (IEEE.isNaN (fromBits32 (bits32 x ||| (4194304#32)) : M32) &&
      (((bits32 x ||| (4194304#32)) &&& (4194304#32)) == 0)) = false
    rw [set_quietMask]
    simp

/-- Existing quiet NaNs are unchanged as complete words, including sign and payload. -/
theorem quietNaN32_eq_self (q : M32)
    (hq : isNaN q = true) (hs : isSNaN q = false) :
    quietNaN q = q := by
  change IEEE.isNaN q = true at hq
  change (IEEE.isNaN q && (bits32 q &&& (4194304#32) == 0)) = false at hs
  have hmask : bits32 q &&& (4194304#32) ≠ 0 := by
    intro hz
    simpa [hq, hz] using hs
  change (if IEEE.isNaN q then fromBits32 (bits32 q ||| (4194304#32)) else q) = q
  simp only [hq, Bool.true_eq, ite_true]
  rw [or_quietMask_eq_self (bits32 q) hmask]
  cases q
  rfl

/-- Quieting only changes a fraction bit, so the exponent is unchanged. -/
theorem expField32_set_quietBit (x : M32) :
    expField (fromBits32 (bits32 x ||| (4194304#32)) : M32) = expField x := by
  change (((bits32 x ||| (4194304#32)) >>> 23) &&& (255#32)).toNat =
    ((bits32 x >>> 23) &&& (255#32)).toNat
  rw [BitVec.ushiftRight_or_distrib]
  have hzero : (4194304#32 : BitVec 32) >>> 23 = 0 := by decide
  rw [hzero]
  exact congrArg (fun b : BitVec 32 => (b &&& (255#32)).toNat)
    (BitVec.or_zero (x := bits32 x >>> 23))

/-- The quieted fraction contains bit 22 and therefore cannot be zero. -/
theorem fracField32_set_quietBit_ne_zero (x : M32) :
    fracField (fromBits32 (bits32 x ||| (4194304#32)) : M32) ≠ 0 := by
  intro hz
  have hword : (bits32 x ||| (4194304#32)) &&& (8388607#32) = 0 := by
    apply BitVec.eq_of_toNat_eq
    exact hz
  have hbit := congrArg (fun b : BitVec 32 => b.getLsbD 22) hword
  rw [BitVec.getLsbD_and, BitVec.getLsbD_or] at hbit
  change (((bits32 x).getLsbD 22 || true) && true) = false at hbit
  simp at hbit

/-- Quieting an actual NaN remains NaN under the actual binary32 classifier. -/
theorem quietNaN32_is_nan (x : M32) (hx : isNaN x = true) :
    isNaN (quietNaN x) = true := by
  have hn : IEEE.isNaN x = true := hx
  have he : expField x = 255 := by
    change (expField x == 255 && fracField x != 0) = true at hx
    simp only [Bool.and_eq_true, beq_iff_eq, bne_iff_ne] at hx
    exact hx.1
  change IEEE.isNaN
    (if IEEE.isNaN x then fromBits32 (bits32 x ||| (4194304#32)) else x) = true
  simp only [hn, Bool.true_eq, ite_true]
  change (expField (fromBits32 (bits32 x ||| (4194304#32)) : M32) == 255 &&
    fracField (fromBits32 (bits32 x ||| (4194304#32)) : M32) != 0) = true
  rw [expField32_set_quietBit, he]
  simp [fracField32_set_quietBit_ne_zero]

/-- Quieting a NaN produces a quiet NaN, with no assumption about its original signaling bit. -/
theorem quietNaN32_is_qnan (x : M32) (hx : isNaN x = true) :
    isQNaN (quietNaN x) = true := by
  rw [isQNaN_eq_nan_and_not_signaling]
  rw [quietNaN32_is_nan x hx, quietNaN32_not_snan x]
  rfl

/-- Full idempotence, including non-NaN inputs. -/
theorem quietNaN32_idempotent (x : M32) :
    quietNaN (quietNaN x) = quietNaN x := by
  cases hx : isNaN x
  · have hself : quietNaN x = x := by
      change IEEE.isNaN x = false at hx
      change (if IEEE.isNaN x then fromBits32 (bits32 x ||| (4194304#32)) else x) = x
      simp [hx]
    rw [hself, hself]
  · exact quietNaN32_eq_self _ (quietNaN32_is_nan x hx) (quietNaN32_not_snan x)

/-- Real zero constructor, either sign. -/
theorem zero32_not_snan (sign : Bool) :
    isSNaN (zero F32 sign) = false := by
  exact isSNaN_eq_false_of_isNaN_eq_false _ (isNaN_zero F32 sign)

/-- The actual invalid result is the canonical quiet NaN. -/
theorem invalidResult32_not_snan :
    isSNaN (invalidResult F32) = false := by decide

theorem invalidResult32_is_qnan :
    isQNaN (invalidResult F32) = true := by decide

/-- Every successful real binary NaN selection is quieted before being returned. -/
theorem chooseNaN2_32_not_snan (x y n : M32)
    (h : chooseNaN2 x y = some n) : isSNaN n = false := by
  unfold chooseNaN2 at h
  split at h
  · have hn : quietNaN x = n := Option.some.inj h
    rw [← hn]
    exact quietNaN32_not_snan x
  · split at h
    · have hn : quietNaN y = n := Option.some.inj h
      rw [← hn]
      exact quietNaN32_not_snan y
    · split at h
      · have hn : quietNaN x = n := Option.some.inj h
        rw [← hn]
        exact quietNaN32_not_snan x
      · split at h
        · have hn : quietNaN y = n := Option.some.inj h
          rw [← hn]
          exact quietNaN32_not_snan y
        · contradiction

end R7W01


/-
R7-W01: concrete classification of the real binary32 rounder.
Verification status is recorded in verification-summary.json.
The sole imported contract transitively provides every lemma used here.
-/
namespace R7W01

open FloatLib.Floats.Formats.BinaryInterchange
open FloatLib.Floats.Formats.BinaryInterchange.Model


/-- Every binary32 field tuple whose exponent is at most 254 is non-NaN.
The fraction may be any Nat: the actual ofFields constructor masks it. -/
theorem fields32_not_nan (sign : Bool) (exponent fraction : Nat)
    (he : exponent < 255) :
    isNaN (ofFields F32 sign exponent fraction) = false := by
  apply isNaN_eq_false_of_isFinite_eq_true
  apply isFinite_ofFields_ieee F32 (by decide) sign exponent fraction
  exact he

/-- Native binary32 overflow is signed infinity, never a NaN. -/
theorem nativeOverflow32_not_nan (sign : Bool) :
    isNaN (nativeOverflow F32 sign) = false := by
  rw [nativeOverflow_eq_signedInf_of_isIEEE F32 (by decide)]
  cases sign
  · exact isNaN_posInf F32 (by decide)
  · exact isNaN_negInf F32 (by decide)

/-- Every result of the actual binary32 subnormal packer is non-NaN,
provided its explicitly supplied zero result is non-NaN. -/
theorem packRoundedSubnormal32_not_nan (sign : Bool) (z : M32)
    (hz : isNaN z = false) (fraction : Nat) :
    isNaN (packRoundedSubnormal F32 sign z fraction) = false := by
  unfold packRoundedSubnormal
  split
  · exact hz
  · split
    · exact fields32_not_nan sign 1 0 (by decide)
    · exact fields32_not_nan sign 0 fraction (by decide)

/-- The normal packer's final overflow guard excludes the reserved exponent,
independently of mantissa rounding, exponent carry, or a fraction bound. -/
theorem packRoundedNormal32_not_nan (sign : Bool) (overflow : M32)
    (hoverflow : isNaN overflow = false) (totalExponent : Int)
    (roundedMantissa : Nat) :
    isNaN (packRoundedNormal F32 sign overflow totalExponent roundedMantissa) = false := by
  have hfinish (e : Int) (m : Nat) :
      isNaN
        (if e > F32.maxNormalExponent then overflow else
          if Int.toNat (e + Int.ofNat F32.exponentBias) > F32.maxFiniteExpField ||
              (Int.toNat (e + Int.ofNat F32.exponentBias) == F32.maxFiniteExpField &&
                m - pow2 F32.fracWidth > F32.maxFiniteFracField) then
            overflow
          else
            ofFields F32 sign (Int.toNat (e + Int.ofNat F32.exponentBias))
              (m - pow2 F32.fracWidth)) = false := by
    split
    · exact hoverflow
    · split
      · exact hoverflow
      · apply fields32_not_nan
        rename_i hguard
        have hmax : F32.maxFiniteExpField = 254 := by decide
        rw [hmax] at hguard
        simp only [Bool.or_eq_true, decide_eq_true_eq, beq_iff_eq] at hguard
        omega
  exact hfinish _ _

/-- The complete descriptor general rounder is non-NaN for binary32.
All branches use the real constructors and guards. -/
theorem roundDyadicGeneral32_not_nan (d : FloatLib.Numerics.Dyadic) :
    isNaN (roundDyadicGeneral F32 d) = false := by
  unfold roundDyadicGeneral
  split
  · exact isNaN_zero F32 d.negative
  · dsimp only
    split
    · exact nativeOverflow32_not_nan d.negative
    · split
      · exact packRoundedSubnormal32_not_nan d.negative _
          (isNaN_zero F32 d.negative) _
      · exact packRoundedNormal32_not_nan d.negative _
          (nativeOverflow32_not_nan d.negative) _ _

/-- Actual specification rounder, not a substitute or assumed finite model. -/
theorem roundDyadic32_not_nan (d : FloatLib.Numerics.Dyadic) :
    isNaN (roundDyadic F32 d) = false := by
  rw [← roundDyadicGeneral_eq_roundDyadic F32 d]
  exact roundDyadicGeneral32_not_nan d

/-- Requested non-signaling consequence. -/
theorem roundDyadic32_not_snan (d : FloatLib.Numerics.Dyadic) :
    isSNaN (roundDyadic F32 d) = false := by
  exact isSNaN_eq_false_of_isNaN_eq_false _ (roundDyadic32_not_nan d)

theorem nativeOverflow32_not_snan (sign : Bool) :
    isSNaN (nativeOverflow F32 sign) = false := by
  exact isSNaN_eq_false_of_isNaN_eq_false _ (nativeOverflow32_not_nan sign)


end R7W01


/- This section is concatenated after Helpers and Rounding in R7W01.lean.
   Every helper referenced here is proved concretely in those sections. -/
namespace R7W01
open FloatLib.Floats.Formats.BinaryInterchange
open FloatLib.Floats.Formats.BinaryInterchange.Model

/-- The actual binary32 multiplication specification never produces an sNaN. -/
theorem mul32_not_snan (x y : M32) :
    isSNaN (Spec.mul x y) = false := by
  unfold Spec.mul
  split
  · dsimp only
    split
    · exact zero32_not_snan _
    · exact roundDyadic32_not_snan _
  · split
    · rename_i n hn
      exact chooseNaN2_32_not_snan x y n hn
    · split
      · split
        · exact invalidResult32_not_snan
        · exact nativeOverflow32_not_snan _
      · split
        · split
          · exact invalidResult32_not_snan
          · exact nativeOverflow32_not_snan _
        · exact invalidResult32_not_snan

/-- Exact quiet-NaN absorption when the right input cannot be signaling. -/
theorem add_absorb_of_not_snan (q r : M32)
    (hq : isNaN q = true) (hs : isSNaN q = false)
    (hr : isSNaN r = false) : Spec.add q r = q := by
  have hd : toDyadic? q = none := toDyadic?_eq_none_of_isNaN hq
  have hc : chooseNaN2 q r = some q := by
    simp [chooseNaN2, hs, hr, hq, quietNaN32_eq_self q hq hs]
  simp [Spec.add, hd, hc]

/-- Full sign and payload are preserved because the conclusion is Model equality. -/
theorem add_mul_absorb (q x y : M32)
    (hq : isNaN q = true) (hs : isSNaN q = false) :
    Spec.add q (Spec.mul x y) = q := by
  exact add_absorb_of_not_snan q (Spec.mul x y) hq hs (mul32_not_snan x y)

theorem add_mul_absorb_bits (q x y : M32)
    (hq : isNaN q = true) (hs : isSNaN q = false) :
    (Spec.add q (Spec.mul x y)).bits = q.bits := by
  rw [add_mul_absorb q x y hq hs]

end R7W01

/-
R7-W01 fold fragment. Append after the proved R7W01.add_mul_absorb in the final
single-dependency ContractTensor file. No arithmetic assumptions are introduced here.
The abbreviation R7W01.M32 is supplied by the preceding model proof.
-/

open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange

namespace R7W01

/-- A computable guard: precisely NaN and not signaling. -/
@[inline] def quietGuard (q : M32) : Bool := q.isNaN && !q.isSNaN

theorem quietGuard_nan (q : M32) (h : quietGuard q = true) :
    q.isNaN = true := by
  cases hn : q.isNaN <;> simp_all [quietGuard]

theorem quietGuard_not_signaling (q : M32) (h : quietGuard q = true) :
    q.isSNaN = false := by
  cases hs : q.isSNaN <;> simp_all [quietGuard]

/-- Same pair order, separate multiply and add at every step. -/
def modelDotFold {ι : Type} (a b : ι → M32) (indices : List ι) (acc : M32) : M32 :=
  indices.foldl (fun q i => Model.Spec.add q (Model.Spec.mul (a i) (b i))) acc

/-- Tests before the next operand read/multiply. No suffix is evaluated after success. -/
def modelDotEarly {ι : Type} (a b : ι → M32) : List ι → M32 → M32
  | [], acc => acc
  | i :: is, acc =>
      if quietGuard acc then acc
      else modelDotEarly a b is (Model.Spec.add acc (Model.Spec.mul (a i) (b i)))

theorem modelDotFold_absorb {ι : Type} (a b : ι → M32) (indices : List ι)
    (q : M32) (hn : q.isNaN = true) (hs : q.isSNaN = false) :
    modelDotFold a b indices q = q := by
  induction indices generalizing q with
  | nil => rfl
  | cons i is ih =>
      change modelDotFold a b is (Model.Spec.add q (Model.Spec.mul (a i) (b i))) = q
      rw [add_mul_absorb q (a i) (b i) hn hs]
      exact ih q hn hs

theorem modelDotEarly_eq {ι : Type} (a b : ι → M32) (indices : List ι) (acc : M32) :
    modelDotEarly a b indices acc = modelDotFold a b indices acc := by
  induction indices generalizing acc with
  | nil => rfl
  | cons i is ih =>
      simp only [modelDotEarly]
      split
      · rename_i hq
        exact (modelDotFold_absorb a b (i :: is) acc
          (quietGuard_nan acc hq) (quietGuard_not_signaling acc hq)).symm
      · exact ih (Model.Spec.add acc (Model.Spec.mul (a i) (b i)))

/- The actual configured runtime carrier. This repeats the public source's
   private toModel_execAdd proof pattern, with both arithmetic operations. -/
theorem exec_toModel_add (x y : Competition.Binary32) :
    ExecFloat.Binary.toModel (ExecFloat.add x y) =
      Model.Spec.add (ExecFloat.Binary.toModel x) (ExecFloat.Binary.toModel y) := by
  rw [ExecFloat.Proof.add_eq_spec]
  change Configured.Family.toModel
    (ExecFloat.ModelCodec.liftBinary Model.Spec.add x y) = _
  simp [Configured.Family.toModel, ExecFloat.Binary.toModel]

theorem exec_toModel_mul (x y : Competition.Binary32) :
    ExecFloat.Binary.toModel (ExecFloat.mul x y) =
      Model.Spec.mul (ExecFloat.Binary.toModel x) (ExecFloat.Binary.toModel y) := by
  rw [ExecFloat.Proof.mul_eq_spec]
  change Configured.Family.toModel
    (ExecFloat.ModelCodec.liftBinary Model.Spec.mul x y) = _
  simp [Configured.Family.toModel, ExecFloat.Binary.toModel]

theorem exec_add_mul_absorb (q x y : Competition.Binary32)
    (hn : (ExecFloat.Binary.toModel q).isNaN = true)
    (hs : (ExecFloat.Binary.toModel q).isSNaN = false) :
    ExecFloat.add q (ExecFloat.mul x y) = q := by
  apply Configured.Family.toModel_injective
  change ExecFloat.Binary.toModel (ExecFloat.add q (ExecFloat.mul x y)) =
    ExecFloat.Binary.toModel q
  rw [exec_toModel_add, exec_toModel_mul]
  exact add_mul_absorb _ _ _ hn hs

@[inline] def execQuietGuard (q : Competition.Binary32) : Bool :=
  quietGuard (ExecFloat.Binary.toModel q)


end R7W01

end R7NaNProof

section R7SumProof

/- R7-W02: exact signaling classifier and payload-preserving quieting on UInt32. -/
namespace R7W02
open FloatLib.Floats.Formats.BinaryInterchange

@[inline] def rawSNaN (u : UInt32) : Bool :=
  ((u &&& 0x7fc00000) == 0x7f800000) && ((u &&& 0x003fffff) != 0)

@[inline] def quietRaw (u : UInt32) : UInt32 :=
  u ||| 0x00400000

private theorem mask_split (bits : BitVec 32) :
    bits &&& (2143289344#32) =
      ((((bits >>> 23) &&& (255#32)) <<< 23) ||| (bits &&& (4194304#32))) := by
  apply BitVec.eq_of_getLsbD_eq
  intro i hi
  interval_cases i <;> simp

private theorem fraction_split (bits : BitVec 32) :
    bits &&& (8388607#32) =
      (bits &&& (4194303#32)) ||| (bits &&& (4194304#32)) := by
  have hm : (8388607#32 : BitVec 32) = (4194303#32) ||| (4194304#32) := by decide
  rw [hm, BitVec.and_or_distrib_left]

private theorem mask_snan_classification (bits : BitVec 32) :
    ((bits &&& (2143289344#32) = (2139095040#32)) ∧
      (bits &&& (4194303#32)) ≠ 0) ↔
      ((((bits >>> 23) &&& (255#32)).toNat = 255 ∧
        (bits &&& (8388607#32)).toNat ≠ 0) ∧
        bits &&& (4194304#32) = 0) := by
  constructor
  · rintro ⟨hm, hp⟩
    have he : (bits >>> 23) &&& (255#32) = (255#32) := by
      have hh := congrArg (fun b : BitVec 32 => b >>> 23) hm
      rw [BitVec.ushiftRight_and_distrib] at hh
      exact hh
    have hq : bits &&& (4194304#32) = 0 := by
      have hh := congrArg (fun b : BitVec 32 => b &&& (4194304#32)) hm
      rw [BitVec.and_assoc] at hh
      exact hh
    have hf : (bits &&& (8388607#32)).toNat ≠ 0 := by
      intro hz
      have hzword : bits &&& (8388607#32) = 0 := BitVec.eq_of_toNat_eq hz
      rw [fraction_split, hq] at hzword
      exact hp (by simpa using hzword)
    exact ⟨⟨congrArg BitVec.toNat he, hf⟩, hq⟩
  · rintro ⟨⟨he, hf⟩, hq⟩
    have heword : (bits >>> 23) &&& (255#32) = (255#32) := by
      apply BitVec.eq_of_toNat_eq
      exact he
    constructor
    · rw [mask_split, heword, hq]
      decide
    · intro hp
      have hz : bits &&& (8388607#32) = 0 := by
        rw [fraction_split, hq, hp]
        decide
      exact hf (by rw [hz]; rfl)

/-- All raw words, including either sign and every payload; no input canonicalization. -/
theorem rawSNaN_eq_isSNaN (u : UInt32) :
    rawSNaN u = Model.isSNaN (Model.NativeBinary32.ofUInt32 u) := by
  apply Bool.eq_iff_iff.mpr
  simp only [rawSNaN, Bool.and_eq_true, beq_iff_eq, bne_iff_ne]
  simp only [ne_eq, ← UInt32.toBitVec_inj, UInt32.toBitVec_and]
  change ((u.toBitVec &&& (2143289344#32) = (2139095040#32)) ∧
      (u.toBitVec &&& (4194303#32)) ≠ 0) ↔
    (((((u.toBitVec >>> 23) &&& (255#32)).toNat == 255 &&
      (u.toBitVec &&& (8388607#32)).toNat != 0) &&
      (u.toBitVec &&& (4194304#32)) == 0) = true)
  simp only [Bool.and_eq_true, beq_iff_eq, bne_iff_ne]
  exact mask_snan_classification u.toBitVec

/-- The real quietNaN operation agrees bit-for-bit with setting just bit 22. -/
theorem quietRaw_eq_quietNaN (u : UInt32) (h : rawSNaN u = true) :
    Model.NativeBinary32.ofUInt32 (quietRaw u) =
      Model.quietNaN (Model.NativeBinary32.ofUInt32 u) := by
  have hs : Model.isSNaN (Model.NativeBinary32.ofUInt32 u) = true := by
    rw [← rawSNaN_eq_isSNaN]
    exact h
  have hn := Model.isNaN_of_isSNaN hs
  have hn' : Model.IEEE.isNaN (Model.NativeBinary32.ofUInt32 u) = true := hn
  change Model.ofBits (fmt := FloatFormat.binary32) (u ||| (0x00400000 : UInt32)).toBitVec =
    (if Model.IEEE.isNaN (Model.NativeBinary32.ofUInt32 u) then
      Model.ofBits (fmt := FloatFormat.binary32) (u.toBitVec ||| (4194304#32))
      else Model.NativeBinary32.ofUInt32 u)
  simp only [hn', Bool.true_eq, ite_true, UInt32.toBitVec_or]
  rfl

private theorem quietMask_getLsbD (i : Nat) :
    (4194304#32 : BitVec 32).getLsbD i = decide (i = 22) := by
  rw [BitVec.getLsbD_ofNat]
  by_cases hi : i < 32
  · simp only [hi, decide_true, Bool.true_and]
    change (2 ^ 22).testBit i = decide (i = 22)
    simpa [eq_comm] using (Nat.testBit_two_pow (n := 22) (m := i))
  · have : i ≠ 22 := by omega
    simp [hi, this]

/-- Every bit other than the quiet bit is unchanged, with no input precondition. -/
theorem quietRaw_preserves_bit (u : UInt32) (i : Nat) (hi : i ≠ 22) :
    (quietRaw u).toBitVec.getLsbD i = u.toBitVec.getLsbD i := by
  unfold quietRaw
  rw [UInt32.toBitVec_or]
  change (u.toBitVec ||| (4194304#32)).getLsbD i = u.toBitVec.getLsbD i
  rw [BitVec.getLsbD_or, quietMask_getLsbD]
  simp [hi]

/-- The only overwritten bit is set to one. -/
theorem quietRaw_bit22 (u : UInt32) :
    (quietRaw u).toBitVec.getLsbD 22 = true := by
  unfold quietRaw
  rw [UInt32.toBitVec_or, BitVec.getLsbD_or]
  change (u.toBitVec.getLsbD 22 || true) = true
  simp

/-- The quieted raw signaling NaN is classified as quiet by the actual Model. -/
theorem quietRaw_isQNaN (u : UInt32) (h : rawSNaN u = true) :
    Model.isQNaN (Model.NativeBinary32.ofUInt32 (quietRaw u)) = true := by
  have hs : Model.isSNaN (Model.NativeBinary32.ofUInt32 u) = true := by
    rw [← rawSNaN_eq_isSNaN]
    exact h
  have he : ((u.toBitVec >>> 23) &&& (255#32)).toNat = 255 := by
    change (((((u.toBitVec >>> 23) &&& (255#32)).toNat == 255 &&
      (u.toBitVec &&& (8388607#32)).toNat != 0) &&
      (u.toBitVec &&& (4194304#32)) == 0) = true) at hs
    simp only [Bool.and_eq_true, beq_iff_eq, bne_iff_ne] at hs
    exact hs.1.1
  have he' : ((((quietRaw u).toBitVec >>> 23) &&& (255#32)).toNat) = 255 := by
    unfold quietRaw
    rw [UInt32.toBitVec_or, BitVec.ushiftRight_or_distrib]
    change (((u.toBitVec >>> 23 ||| (0#32)) &&& (255#32)).toNat) = 255
    rw [BitVec.or_zero]
    exact he
  have hq : (quietRaw u).toBitVec &&& (4194304#32) ≠ 0 := by
    intro hz
    have hh := congrArg (fun b : BitVec 32 => b.getLsbD 22) hz
    rw [BitVec.getLsbD_and, quietRaw_bit22] at hh
    change (true && true) = false at hh
    cases hh
  have hf : ((quietRaw u).toBitVec &&& (8388607#32)).toNat ≠ 0 := by
    intro hz
    have hzword : (quietRaw u).toBitVec &&& (8388607#32) = 0 :=
      BitVec.eq_of_toNat_eq hz
    have hh := congrArg (fun b : BitVec 32 => b.getLsbD 22) hzword
    rw [BitVec.getLsbD_and, quietRaw_bit22] at hh
    change (true && true) = false at hh
    cases hh
  change (((((quietRaw u).toBitVec >>> 23) &&& (255#32)).toNat == 255 &&
      ((quietRaw u).toBitVec &&& (8388607#32)).toNat != 0) &&
      ((quietRaw u).toBitVec &&& (4194304#32)) != 0) = true
  simp only [Bool.and_eq_true, beq_iff_eq, bne_iff_ne]
  exact ⟨⟨he', hf⟩, hq⟩

end R7W02

/- Append after Base.lean and Raw.lean under the single dependency ContractTensor.
   The quiet accumulator precondition is explicit in every arithmetic bridge. -/
open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange

namespace R7W02

/-- The actual binary32 specification keeps a quiet left NaN unless the right
    operand is signaling; that right operand is then quieted, with its word retained. -/
theorem model_add_qnan_left (q x : Model FloatFormat.binary32)
    (hq : Model.isQNaN q = true) :
    Model.Spec.add q x =
      if Model.isSNaN x then Model.quietNaN x else q := by
  have hclass : Model.isNaN q = true ∧ Model.isSNaN q = false := by
    simpa [Model.isQNaN_eq_nan_and_not_signaling] using hq
  have hd : Model.toDyadic? q = none :=
    Model.toDyadic?_eq_none_of_isNaN hclass.1
  cases hx : Model.isSNaN x <;>
    simp [Model.Spec.add, hd, Model.chooseNaN2, hclass.1, hclass.2, hx,
      R7W01.quietNaN32_eq_self q hclass.1 hclass.2]

/-- Exact construction of the configured carrier from all 32 stored bits.
    The bound and nominal wrapper are propositions erased by Lean compilation. -/
@[inline] def fromRaw (u : UInt32) : Competition.Binary32 :=
  ExecFloat.ofRaw ⟨u, u.toNat_lt⟩

@[simp] theorem fromRaw_raw (u : UInt32) : (fromRaw u).raw.1 = u := rfl

/-- This codec uses the actual competition carrier, with no native float conversion. -/
theorem exec_toModel_eq_rawModel (q : Competition.Binary32) :
    ExecFloat.Binary.toModel q = Model.NativeBinary32.ofUInt32 q.raw.1 := by
  change Model.ofBits (fmt := FloatFormat.binary32)
      (BitVec.ofNatLT q.raw.1.toNat q.raw.2) =
    Model.ofBits (fmt := FloatFormat.binary32) q.raw.1.toBitVec
  apply congrArg (Model.ofBits (fmt := FloatFormat.binary32))
  apply BitVec.eq_of_toNat_eq
  rfl

@[simp] theorem fromRaw_toModel (u : UInt32) :
    ExecFloat.Binary.toModel (fromRaw u) =
      Model.NativeBinary32.ofUInt32 u := by
  rw [exec_toModel_eq_rawModel, fromRaw_raw]

/-- Full model words agree with the raw carrier words, including sign and payload. -/
theorem exec_toModel_bits_eq_raw (q : Competition.Binary32) :
    (ExecFloat.Binary.toModel q).bits = q.raw.1.toBitVec := by
  rw [exec_toModel_eq_rawModel]
  rfl

/-- Transport the public runtime addition through its exact model codec. -/
theorem exec_toModel_add (x y : Competition.Binary32) :
    ExecFloat.Binary.toModel (ExecFloat.add x y) =
      Model.Spec.add (ExecFloat.Binary.toModel x) (ExecFloat.Binary.toModel y) := by
  rw [ExecFloat.Proof.add_eq_spec]
  change Configured.Family.toModel
    (ExecFloat.ModelCodec.liftBinary Model.Spec.add x y) = _
  simp [Configured.Family.toModel, ExecFloat.Binary.toModel]

/-- During a quiet-NaN suffix, only a signaling input replaces the accumulator. -/
@[inline] def step (q x : Competition.Binary32) : Competition.Binary32 :=
  if rawSNaN x.raw.1 then fromRaw (quietRaw x.raw.1) else q

/-- Exact stored-word behavior of the executable step. -/
theorem step_raw (q x : Competition.Binary32) :
    (step q x).raw.1 =
      if rawSNaN x.raw.1 then quietRaw x.raw.1 else q.raw.1 := by
  cases h : rawSNaN x.raw.1 <;> simp [step, h]

/-- The replacement step is exactly ordinary addition for a quiet accumulator. -/
theorem step_eq_add (q x : Competition.Binary32)
    (hq : Model.isQNaN (ExecFloat.Binary.toModel q) = true) :
    step q x = ExecFloat.add q x := by
  let addResult : Competition.Binary32 := ExecFloat.add q x
  apply Configured.Family.toModel_injective
  change @Eq (Model FloatFormat.binary32)
    (ExecFloat.Binary.toModel (step q x))
    (ExecFloat.Binary.toModel addResult)
  let qm : Model FloatFormat.binary32 := ExecFloat.Binary.toModel q
  let xm : Model FloatFormat.binary32 := ExecFloat.Binary.toModel x
  have hq' : Model.isQNaN qm = true := hq
  refine Eq.trans ?_ (exec_toModel_add q x).symm
  refine Eq.trans ?_ (model_add_qnan_left qm xm hq').symm
  have hx : rawSNaN x.raw.1 = Model.isSNaN xm :=
    (rawSNaN_eq_isSNaN x.raw.1).trans
      (congrArg (fun m : Model FloatFormat.binary32 => Model.isSNaN m)
        (exec_toModel_eq_rawModel x)).symm
  cases hr : rawSNaN x.raw.1
  · have hs : Model.isSNaN xm = false := hx.symm.trans hr
    simp [step, hr, hs, qm]
  · have hs : Model.isSNaN xm = true := hx.symm.trans hr
    simp only [step, hr, Bool.true_eq, ite_true, hs]
    exact (fromRaw_toModel (quietRaw x.raw.1)).trans
      ((quietRaw_eq_quietNaN x.raw.1 hr).trans
        (congrArg (fun m : Model FloatFormat.binary32 => Model.quietNaN m)
          (exec_toModel_eq_rawModel x)).symm)

/-- The executable step preserves the quiet-NaN invariant needed by the next input. -/
theorem step_isQNaN (q x : Competition.Binary32)
    (hq : Model.isQNaN (ExecFloat.Binary.toModel q) = true) :
    Model.isQNaN (ExecFloat.Binary.toModel (step q x)) = true := by
  cases hr : rawSNaN x.raw.1
  · simpa [step, hr] using hq
  · simp only [step, hr, Bool.true_eq, ite_true]
    rw [fromRaw_toModel]
    exact quietRaw_isQNaN x.raw.1 hr

end R7W02


end R7SumProof



/-
MIT License

Copyright (c) 2026 Conjectures.io

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

# Third-party notices

This repository is under the MIT licence in [LICENSE](LICENSE). Some of its files reproduce, adapt
or restate code from the projects below, whose licences ask that their notices travel with that
code; those notices are reproduced here in full. [REUSE.toml](REUSE.toml) records, file by file,
which notices apply, and `reuse lint` checks it.

If you copy a shipped kernel, contract or migration file into your own work, a submission
included, keep the notices that apply to it.

## Included in this repository

### FloatLib

[FloatLib](https://github.com/lean-dojo/FloatLib), MIT licence. The contract
(`lean/contract/`) restates FloatLib's IEEE 754 specification as the obligations a kernel must meet,
and the kernels (`kernels/`) and stage 2 (`lean/stage2/`) reproduce or adapt FloatLib's certified
binary32 word kernels and their helpers: `kernels/add/mirror` runs FloatLib's word addition step
for step on bare words, and the faster kernels are built from it.

```text
MIT License

Copyright (c) 2026 FloatLib

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```

### TorchLean

[TorchLean](https://github.com/lean-dojo/TorchLean), MIT licence. The tensor contract
(`lean/contract/ContractTensor.lean`) restates TorchLean's `reduceSumLeftSpec` and `bmmSpec`, and
the `sum`, `bmmR4` and full-entry kernels and `lean/stage2/` are written against those definitions;
`lean/stage2/Stage2/Link.lean` proves the restatements equal to TorchLean's own.

```text
MIT License

Copyright (c) 2026 TorchLean

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```


-/


/-!
The full entry's incumbent, what every entry starts from and must beat: the best proven `add`
(`tuned`, 0.50x of `ExecFloat.add`) and `mul` (`mul/fast`, 0.55x of `ExecFloat.mul`), copied with
their proofs into namespaces of their own, with TorchLean's `sum` and `bmmR4` built from them, at
0.56x of the baseline's time.
-/

namespace R2W01b

@[inline] def magnitude (u : UInt32) : UInt32 :=
  u &&& 0x7fffffff

@[inline] def fastOK (u : UInt32) : Bool :=
  let a := magnitude u
  decide (0x0bffffff ≤ a - 1) && decide (a < 0x7f800000)

def NormalBand (u : UInt32) : Prop :=
  0x0c000000 ≤ magnitude u ∧ magnitude u < 0x7f800000

theorem wrap_gate_iff (a : UInt32) :
    (decide (0x0bffffff ≤ a - 1) && decide (a < 0x7f800000)) = true ↔
      a = 0 ∨ (0x0c000000 ≤ a ∧ a < 0x7f800000) := by
  have ha := a.toNat_lt_size
  simp only [Bool.and_eq_true, decide_eq_true_eq, UInt32.le_iff_toNat_le,
    UInt32.lt_iff_toNat_lt, UInt32.toNat_sub, ← UInt32.toNat_inj]
  change a.toNat < 4294967296 at ha
  change
    (201326591 ≤ (4294967295 + a.toNat) % 4294967296 ∧
      a.toNat < 2139095040) ↔
    (a.toNat = 0 ∨ (201326592 ≤ a.toNat ∧ a.toNat < 2139095040))
  omega

theorem fastOK_iff (u : UInt32) :
    fastOK u = true ↔ magnitude u = 0 ∨ NormalBand u := by
  exact wrap_gate_iff (magnitude u)

theorem magnitude_toNat (u : UInt32) :
    (magnitude u).toNat = u.toNat % 2147483648 := by
  rw [magnitude, UInt32.toNat_and]
  change u.toNat &&& (2 ^ 31 - 1) = u.toNat % 2 ^ 31
  exact Nat.and_two_pow_sub_one_eq_mod u.toNat 31

theorem magnitude_zero_iff (u : UInt32) :
    magnitude u = 0 ↔ u = 0 ∨ u = 0x80000000 := by
  have hu := u.toNat_lt_size
  simp only [← UInt32.toNat_inj, magnitude_toNat]
  change u.toNat < 4294967296 at hu
  change
    u.toNat % 2147483648 = 0 ↔ u.toNat = 0 ∨ u.toNat = 2147483648
  omega

theorem fastOK_positive_zero : fastOK 0 = true := by
  decide

theorem fastOK_negative_zero : fastOK 0x80000000 = true := by
  decide

@[inline] def tableIndex (u : UInt32) : UInt32 :=
  u >>> 23

@[inline] def mantissa (u : UInt32) : UInt32 :=
  (u &&& 0x7fffff) ||| 0x800000

@[inline] def scaleBits (j : UInt32) : UInt32 :=
  let e := j &&& 255
  let s := (j &&& 256) <<< 23
  if decide (24 ≤ e) && decide (e ≤ 254) then
    s ||| ((e - 23) <<< 23)
  else
    s

theorem tableIndex_toNat_lt (u : UInt32) :
    (tableIndex u).toNat < 512 := by
  have hu := u.toNat_lt_size
  rw [tableIndex, UInt32.toNat_shiftRight]
  change u.toNat >>> 23 < 512
  rw [Nat.shiftRight_eq_div_pow]
  change u.toNat < 4294967296 at hu
  change u.toNat / 8388608 < 512
  omega

def scaleTable : Array Float32 :=
  Array.ofFn fun j : Fin 512 => Float32.ofBits (scaleBits (UInt32.ofNat j.val))

theorem scaleTable_size : scaleTable.size = 512 := by
  simp only [scaleTable, Array.size_ofFn]

theorem scaleTable_entry (j : Fin 512) :
    scaleTable[j.val]'(by rw [scaleTable_size]; exact j.isLt) =
      Float32.ofBits (scaleBits (UInt32.ofNat j.val)) := by
  simp only [scaleTable, Array.getElem_ofFn]

@[inline] def scaleAt (u : UInt32) : Float32 :=
  scaleTable[(tableIndex u).toNat]'(by
    rw [scaleTable_size]
    exact tableIndex_toNat_lt u)

theorem scaleAt_eq (u : UInt32) :
    scaleAt u = Float32.ofBits (scaleBits (tableIndex u)) := by
  simp only [scaleAt, scaleTable, Array.getElem_ofFn, UInt32.ofNat_toNat]

theorem zero_fields (u : UInt32) (h : magnitude u = 0) :
    (u = 0 ∧ tableIndex u = 0 ∧ mantissa u = 0x800000 ∧
      scaleBits (tableIndex u) = 0) ∨
    (u = 0x80000000 ∧ tableIndex u = 256 ∧ mantissa u = 0x800000 ∧
      scaleBits (tableIndex u) = 0x80000000) := by
  cases (magnitude_zero_iff u).mp h with
  | inl hu =>
    subst u
    left
    decide
  | inr hu =>
    subst u
    right
    decide

theorem scaleAt_positive_zero : scaleAt 0 = Float32.ofBits 0 := by
  rw [scaleAt_eq]
  exact congrArg Float32.ofBits (by decide : scaleBits (tableIndex 0) = 0)

theorem scaleAt_negative_zero :
    scaleAt 0x80000000 = Float32.ofBits 0x80000000 := by
  rw [scaleAt_eq]
  exact congrArg Float32.ofBits
    (by decide : scaleBits (tableIndex 0x80000000) = 0x80000000)

theorem zero_mantissa_conversion :
    (0x800000 : UInt32).toFloat32 = Float32.ofBits 0x4b000000 := by
  decide

@[inline] def tableProduct (u : UInt32) : Float32 :=
  (mantissa u).toFloat32 * scaleAt u

theorem tableProduct_positive_zero : tableProduct 0 = Float32.ofBits 0 := by
  rw [tableProduct, scaleAt_positive_zero]
  decide

theorem tableProduct_negative_zero :
    tableProduct 0x80000000 = Float32.ofBits 0x80000000 := by
  rw [tableProduct, scaleAt_negative_zero]
  decide

theorem tableProduct_zero_eq (u : UInt32) (h : magnitude u = 0) :
    tableProduct u = Float32.ofBits u := by
  cases (magnitude_zero_iff u).mp h with
  | inl hu =>
    subst u
    exact tableProduct_positive_zero
  | inr hu =>
    subst u
    exact tableProduct_negative_zero

theorem tableProduct_zero_bits_eq (u : UInt32) (h : magnitude u = 0) :
    (tableProduct u).toBits = (Float32.ofBits u).toBits := by
  exact congrArg Float32.toBits (tableProduct_zero_eq u h)

theorem zero_ofBits_toBits (u : UInt32) (h : magnitude u = 0) :
    (Float32.ofBits u).toBits = u := by
  cases (magnitude_zero_iff u).mp h with
  | inl hu => subst u; decide
  | inr hu => subst u; decide

theorem tableProduct_zero_bits (u : UInt32) (h : magnitude u = 0) :
    (tableProduct u).toBits = u := by
  exact (tableProduct_zero_bits_eq u h).trans (zero_ofBits_toBits u h)

theorem float32_eq_of_toBits_eq {x y : Float32} (h : x.toBits = y.toBits) :
    x = y := by
  cases x with
  | ofModel xm =>
    cases y with
    | ofModel ym =>
      cases xm with
      | mk xb xv =>
        cases ym with
        | mk yb yv =>
          change xb = yb at h
          cases h
          rfl

theorem float32_ofBits_toBits (x : Float32) : Float32.ofBits x.toBits = x := by
  simpa only [FloatLib.Floats.ExecFloat.Binary.toFloat32,
    FloatLib.Floats.ExecFloat.Binary.toBits32_ofFloat32] using
    FloatLib.Floats.ExecFloat.Binary.toFloat32_ofFloat32 x

theorem float32_eq_of_raw_bits {x : Float32} {u : UInt32} (h : x.toBits = u) :
    x = Float32.ofBits u := by
  calc
    x = Float32.ofBits x.toBits := (float32_ofBits_toBits x).symm
    _ = Float32.ofBits u := congrArg Float32.ofBits h

theorem normal_value_of_bits
    (hNormalBits : ∀ u, NormalBand u →
      (tableProduct u).toBits = (Float32.ofBits u).toBits) :
    ∀ u, NormalBand u → tableProduct u = Float32.ofBits u := by
  intro u hn
  exact float32_eq_of_toBits_eq (hNormalBits u hn)

theorem normal_value_of_raw_bits
    (hNormalRawBits : ∀ u, NormalBand u → (tableProduct u).toBits = u) :
    ∀ u, NormalBand u → tableProduct u = Float32.ofBits u := by
  intro u hn
  exact float32_eq_of_raw_bits (hNormalRawBits u hn)

theorem tableProduct_of_fastOK
    (hNormal : ∀ u, NormalBand u → tableProduct u = Float32.ofBits u)
    (u : UInt32) (h : fastOK u = true) :
    tableProduct u = Float32.ofBits u := by
  cases (fastOK_iff u).mp h with
  | inl hz => exact tableProduct_zero_eq u hz
  | inr hn => exact hNormal u hn

@[inline] def convert (u : UInt32) : Float32 :=
  if fastOK u then tableProduct u else Float32.ofBits u

theorem convert_zero_path (u : UInt32) (h : magnitude u = 0) :
    convert u = tableProduct u := by
  have hf : fastOK u = true := (fastOK_iff u).mpr (Or.inl h)
  rw [convert, if_pos hf]

theorem convert_fallback (u : UInt32) (h : fastOK u = false) :
    convert u = Float32.ofBits u := by
  simp [convert, h]

theorem convert_eq
    (hNormal : ∀ u, NormalBand u → tableProduct u = Float32.ofBits u)
    (u : UInt32) : convert u = Float32.ofBits u := by
  by_cases h : fastOK u = true
  · rw [convert, if_pos h]
    exact tableProduct_of_fastOK hNormal u h
  · rw [convert, if_neg h]

theorem convert_bits_eq
    (hNormal : ∀ u, NormalBand u → tableProduct u = Float32.ofBits u)
    (u : UInt32) : (convert u).toBits = (Float32.ofBits u).toBits := by
  exact congrArg Float32.toBits (convert_eq hNormal u)

theorem convert_eq_of_normal_bits
    (hNormalBits : ∀ u, NormalBand u →
      (tableProduct u).toBits = (Float32.ofBits u).toBits)
    (u : UInt32) : convert u = Float32.ofBits u := by
  exact convert_eq (normal_value_of_bits hNormalBits) u

theorem convert_eq_of_normal_raw_bits
    (hNormalRawBits : ∀ u, NormalBand u → (tableProduct u).toBits = u)
    (u : UInt32) : convert u = Float32.ofBits u := by
  exact convert_eq (normal_value_of_raw_bits hNormalRawBits) u

theorem replace_decoder {α : Sort _}
    (hNormal : ∀ u, NormalBand u → tableProduct u = Float32.ofBits u)
    (core : (UInt32 → Float32) → α) : core convert = core Float32.ofBits := by
  exact congrArg core (funext (convert_eq hNormal))

theorem foldl_convert_eq
    (hNormal : ∀ u, NormalBand u → tableProduct u = Float32.ofBits u)
    (xs : List UInt32) (step : Float32 → Float32 → Float32) (acc : Float32) :
    xs.foldl (fun z u => step z (convert u)) acc =
      xs.foldl (fun z u => step z (Float32.ofBits u)) acc := by
  induction xs generalizing acc with
  | nil => rfl
  | cons u us ih =>
    simp only [List.foldl_cons, convert_eq hNormal u]
    exact ih _

end R2W01b

/-
MIT License

Copyright (c) 2026 Conjectures.io

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

# Third-party notices

This repository is under the MIT licence in [LICENSE](LICENSE). Some of its files reproduce, adapt
or restate code from the projects below, whose licences ask that their notices travel with that
code; those notices are reproduced here in full. [REUSE.toml](REUSE.toml) records, file by file,
which notices apply, and `reuse lint` checks it.

If you copy a shipped kernel, contract or migration file into your own work, a submission
included, keep the notices that apply to it.

## Included in this repository

### FloatLib

[FloatLib](https://github.com/lean-dojo/FloatLib), MIT licence. The contract
(`lean/contract/`) restates FloatLib's IEEE 754 specification as the obligations a kernel must meet,
and the kernels (`kernels/`) and stage 2 (`lean/stage2/`) reproduce or adapt FloatLib's certified
binary32 word kernels and their helpers: `kernels/add/mirror` runs FloatLib's word addition step
for step on bare words, and the faster kernels are built from it.

```text
MIT License

Copyright (c) 2026 FloatLib

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```

### TorchLean

[TorchLean](https://github.com/lean-dojo/TorchLean), MIT licence. The tensor contract
(`lean/contract/ContractTensor.lean`) restates TorchLean's `reduceSumLeftSpec` and `bmmSpec`, and
the `sum`, `bmmR4` and full-entry kernels and `lean/stage2/` are written against those definitions;
`lean/stage2/Stage2/Link.lean` proves the restatements equal to TorchLean's own.

```text
MIT License

Copyright (c) 2026 TorchLean

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```


-/

namespace R2W01c

namespace NativeBridge

open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange
open Float.Model.UnpackedFloat
open FloatLib.Floats.Formats.BinaryInterchange.Model

/-
The three target-exponent lemmas below are ported from FloatLib Team, MIT,
commit 1f5771b3e36a98f17fcac2c6d76aaa024b36aa37,
Arithmetic/LeanModel/MulDiv.lean. Official pinned dependencies are unchanged.
-/
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

/--
If two nonzero mantissas and their exponents satisfy Lean's `roundWithAccuracy` precondition, so
do the product of the mantissas and the sum of the exponents.
-/
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

/--
A finite nonzero value unpacked from a format word satisfies Lean's `roundWithAccuracy`
precondition: a subnormal has the minimum exponent and a normal has its leading bit set.
-/
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


/-- The finite multiplication specifications perform the same exact product and one rounding. -/
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

theorem toModelNativeMul (x y : Float32)
    (hx : x.isFinite = true) (hy : y.isFinite = true) :
    ExecFloat.Binary.toModel (ExecFloat.Binary.ofFloat32 (x * y)) =
      Model.mul (ExecFloat.Binary.toModel (ExecFloat.Binary.ofFloat32 x))
        (ExecFloat.Binary.toModel (ExecFloat.Binary.ofFloat32 y)) := by
  rw [ExecFloat.Binary.toModel_ofFloat32, ExecFloat.Binary.toModel_ofFloat32,
    ExecFloat.Binary.toModel_ofFloat32]
  change Model.ofFloat32Model (Float32.Model.mul x.toModel y.toModel) = _
  rw [Float32.Model.mul, Model.ofFloat32Model_pack]
  have h := modelMulFinite (fmt := FloatFormat.binary32)
    (by decide) (Model.ofFloat32Model x.toModel) (Model.ofFloat32Model y.toModel)
    (by simpa only [Model.toModel_ofFloat32Model, Float32.isFinite,
      Float32.Model.isFinite] using hx)
    (by simpa only [Model.toModel_ofFloat32Model, Float32.isFinite,
      Float32.Model.isFinite] using hy)
  rw [Model.toModel_ofFloat32Model, Model.toModel_ofFloat32Model] at h
  exact h.symm

end NativeBridge

open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange

abbrev nativeModel (x : Float32) : Model FloatFormat.binary32 :=
  Model.ofFloat32Model x.toModel

abbrev rawModel (u : UInt32) : Model FloatFormat.binary32 :=
  ExecFloat.Binary.toModel (ExecFloat.Binary.ofBits32 u)

theorem rawModel_eq_native32 (u : UInt32) :
    rawModel u = Model.NativeBinary32.ofUInt32 u := rfl

theorem rawModel_eq_ofUInt32 (u : UInt32) :
    rawModel u = Model.ofUInt32 (fmt := FloatFormat.binary32) u := by
  change Model.ofModelBits (fmt := FloatFormat.binary32) u.toBitVec =
    Model.ofModelBits (fmt := FloatFormat.binary32) (BitVec.ofNat 32 u.toBitVec.toNat)
  simp [BitVec.ofNat_toNat]

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

theorem nativeModel_ofBits_of_decode (u : UInt32) {d : FloatLib.Numerics.Dyadic}
    (hd : Model.toDyadic? (rawModel u) = some d) :
    nativeModel (Float32.ofBits u) = rawModel u := by
  have hc : Model.IsModelCanonical (rawModel u) :=
    modelCanonical_of_decode (by decide) (rawModel u) hd
  change Model.ofFloat32Model
    (ExecFloat.Binary.toFloat32 (ExecFloat.Binary.ofBits32 u)).toModel = rawModel u
  rw [ExecFloat.Binary.toModel_toFloat32_eq, Model.ofFloat32Model_toFloat32Model]
  exact Model.canonicalizeModel_eq_self _ hc

theorem nativeModel_ofBits_decode (u : UInt32) {d : FloatLib.Numerics.Dyadic}
    (hd : Model.toDyadic? (rawModel u) = some d) :
    Model.toDyadic? (nativeModel (Float32.ofBits u)) = some d := by
  rw [nativeModel_ofBits_of_decode u hd]
  exact hd

theorem nativeFinite_of_decode (x : Float32) {d : FloatLib.Numerics.Dyadic}
    (hd : Model.toDyadic? (nativeModel x) = some d) :
    x.isFinite = true := by
  rw [Model.toDyadic?_ieee_eq_model FloatFormat.binary32 (by decide)
    (nativeModel x)] at hd
  rw [nativeModel, Model.toModel_ofFloat32Model] at hd
  change x.toModel.unpack.isFinite = true
  cases hx : x.toModel.unpack <;>
    simp_all [Model.unpackedToDyadic?, Float.Model.UnpackedFloat.isFinite]

theorem native_eq_of_model_eq (x y : Float32)
    (h : nativeModel x = nativeModel y) : x = y := by
  have hw : ExecFloat.Binary.ofFloat32 x = ExecFloat.Binary.ofFloat32 y :=
    ExecFloat.Binary.toModel_inj.mp h
  have hn := congrArg ExecFloat.Binary.toFloat32 hw
  simpa only [ExecFloat.Binary.toFloat32_ofFloat32] using hn

theorem native_mul_eq_of_raw_model_mul_eq
    (x y : Float32) (u : UInt32)
    (hx : x.isFinite = true) (hy : y.isFinite = true)
    (hm : Model.mul (nativeModel x) (nativeModel y) = rawModel u) :
    x * y = Float32.ofBits u := by
  have hw : ExecFloat.Binary.ofFloat32 (x * y) = ExecFloat.Binary.ofBits32 u := by
    apply ExecFloat.Binary.toModel_inj.mp
    rw [NativeBridge.toModelNativeMul x y hx hy]
    exact hm
  calc
    x * y = ExecFloat.Binary.toFloat32 (ExecFloat.Binary.ofFloat32 (x * y)) :=
      (ExecFloat.Binary.toFloat32_ofFloat32 _).symm
    _ = ExecFloat.Binary.toFloat32 (ExecFloat.Binary.ofBits32 u) :=
      congrArg ExecFloat.Binary.toFloat32 hw
    _ = Float32.ofBits u := rfl

theorem native_mul_bits_eq_of_raw_model_mul_eq
    (x y : Float32) (u : UInt32)
    (hx : x.isFinite = true) (hy : y.isFinite = true)
    (hm : Model.mul (nativeModel x) (nativeModel y) = rawModel u) :
    (x * y).toBits = u := by
  have hw : ExecFloat.Binary.ofFloat32 (x * y) = ExecFloat.Binary.ofBits32 u := by
    apply ExecFloat.Binary.toModel_inj.mp
    rw [NativeBridge.toModelNativeMul x y hx hy]
    exact hm
  have hn := congrArg ExecFloat.Binary.toBits32 hw
  simpa only [ExecFloat.Binary.toBits32_ofFloat32,
    ExecFloat.Binary.toBits32_ofBits32] using hn

theorem native_mul_eq_of_decoded_raw_model_mul_eq
    (x y : Float32) (u : UInt32)
    {dx dy : FloatLib.Numerics.Dyadic}
    (hx : Model.toDyadic? (nativeModel x) = some dx)
    (hy : Model.toDyadic? (nativeModel y) = some dy)
    (hm : Model.mul (nativeModel x) (nativeModel y) = rawModel u) :
    x * y = Float32.ofBits u :=
  native_mul_eq_of_raw_model_mul_eq x y u
    (nativeFinite_of_decode x hx) (nativeFinite_of_decode y hy) hm

end R2W01c

namespace R2W01c

open FloatLib.Floats.Formats.BinaryInterchange
open FloatLib.Numerics

theorem uint32_model_eq_roundDyadic (n : UInt32) :
    Model.ofFloat32Model n.toFloat32.toModel =
      Model.roundDyadic FloatFormat.binary32
        { negative := false, significand := n.toNat, exponent := 0 } := by
  change Model.ofFloat32Model
      (Float32.Model.pack
        (Float.Model.UnpackedFloat.ofUInt32 Float.Model.Format.binary32 n)) = _
  rw [Model.ofFloat32Model_pack]
  change Model.ofModel FloatFormat.binary32
      (Float.Model.UnpackedFloat.ofInt FloatFormat.binary32.toModel
        (n.toNat : Int)) = _
  have hn : ¬ (n.toNat : Int) < 0 := by omega
  simpa [Dyadic.ofScaledInt, hn] using
    Model.ofModel_ofInt_eq_roundDyadic FloatFormat.binary32
      (by decide) (n.toNat : Int)

theorem uint32_model_eq_of_decode (n : UInt32)
    (z : Model FloatFormat.binary32)
    (hz : Model.toDyadic? z =
      some { negative := false, significand := n.toNat, exponent := 0 }) :
    Model.ofFloat32Model n.toFloat32.toModel = z := by
  rw [uint32_model_eq_roundDyadic]
  change Model.roundDyadicWithRounding FloatFormat.binary32 .nearestEven
    { negative := false, significand := n.toNat, exponent := 0 } = z
  exact Model.roundDyadicWithRounding_toDyadic? (by decide) .nearestEven hz

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

theorem uint32_mantissa_model_eq_fields (n : UInt32)
    (hlo : 8388608 ≤ n.toNat) (hhi : n.toNat < 16777216) :
    Model.ofFloat32Model n.toFloat32.toModel =
      Model.ofFields FloatFormat.binary32 false 150 (n.toNat - 8388608) := by
  apply uint32_model_eq_of_decode
  have hf : n.toNat - 8388608 < 8388608 := by omega
  have hsum : 8388608 + (n.toNat - 8388608) = n.toNat := by omega
  simpa [hsum] using
    fields32_toDyadic false 150 (n.toNat - 8388608) (by decide) (by decide) hf

theorem uint32_mantissa_model_decode (n : UInt32)
    (hlo : 8388608 ≤ n.toNat) (hhi : n.toNat < 16777216) :
    Model.toDyadic? (Model.ofFloat32Model n.toFloat32.toModel) =
      some { negative := false, significand := n.toNat, exponent := 0 } := by
  rw [uint32_mantissa_model_eq_fields n hlo hhi]
  have hf : n.toNat - 8388608 < 8388608 := by omega
  have hsum : 8388608 + (n.toNat - 8388608) = n.toNat := by omega
  simpa [hsum] using
    fields32_toDyadic false 150 (n.toNat - 8388608) (by decide) (by decide) hf

theorem uint32_mantissa_model_finite (n : UInt32)
    (hlo : 8388608 ≤ n.toNat) (hhi : n.toNat < 16777216) :
    Model.isFinite (Model.ofFloat32Model n.toFloat32.toModel) = true := by
  exact Model.isFinite_eq_true_of_toDyadic?_some
    (uint32_mantissa_model_decode n hlo hhi)

theorem uint32_mantissa_model_toReal (n : UInt32)
    (hlo : 8388608 ≤ n.toNat) (hhi : n.toNat < 16777216) :
    Model.toReal (Model.ofFloat32Model n.toFloat32.toModel) = (n.toNat : Real) := by
  rw [Model.toReal_eq, uint32_mantissa_model_decode n hlo hhi]
  simp [Dyadic.toReal, Dyadic.signedSignificand]

end R2W01c

namespace R2W01cModel

open FloatLib
open FloatLib.Floats.Formats.BinaryInterchange
open Model

theorem mul_eq_of_finite_value
    {fmt : FloatFormat} (x y z : Model fmt)
    (hfmt : fmt.isIEEE = true)
    (hx : isFinite x = true) (hy : isFinite y = true)
    (hz : isFinite z = true) (hz0 : toReal z ≠ 0)
    (hvalue : toReal x * toReal y = toReal z) :
    mul x y = z := by
  have hbound : |toReal x| * |toReal y| ≤ toReal (posMaxFinite fmt) := by
    rw [← abs_mul, hvalue]
    exact abs_toReal_le_posMaxFinite_of_isIEEE_of_isFinite z hfmt hz
  have hmulfinite : isFinite (mul x y) = true :=
    isFinite_mul_of_abs_mul_le_posMaxFinite x y hfmt hx hy hbound
  have hmulvalue : toReal (mul x y) = toReal z := by
    rw [toReal_mul_eq_roundAt x y hfmt hx hy hmulfinite,
      hvalue, roundAt_toReal_eq z hz]
  exact eq_of_toReal_eq_of_nonzero hmulfinite hz hmulvalue
    (by rw [hmulvalue]; exact hz0)

theorem dyadic_scale_value (sign : Bool) (m k : Nat) (e : Int) :
    (Numerics.Dyadic.mk false m 0).toReal *
      (Numerics.Dyadic.mk sign (2 ^ k) e).toReal =
      (Numerics.Dyadic.mk sign m (e + (k : Int))).toReal := by
  cases sign <;>
    simp [Numerics.Dyadic.toReal, Numerics.Dyadic.signedSignificand,
      zpow_add₀ (by norm_num : (2 : ℝ) ≠ 0)] <;> ring <;> simp

theorem mul_eq_of_scale_decodes
    {fmt : FloatFormat} (x y z : Model fmt)
    (hfmt : fmt.isIEEE = true) (sign : Bool) (m k : Nat) (e : Int)
    (hm : m ≠ 0)
    (hx : toDyadic? x = some ⟨false, m, 0⟩)
    (hy : toDyadic? y = some ⟨sign, 2 ^ k, e⟩)
    (hz : toDyadic? z = some ⟨sign, m, e + (k : Int)⟩) :
    mul x y = z := by
  have hxfinite : isFinite x = true := isFinite_eq_true_of_toDyadic?_some hx
  have hyfinite : isFinite y = true := isFinite_eq_true_of_toDyadic?_some hy
  have hzfinite : isFinite z = true := isFinite_eq_true_of_toDyadic?_some hz
  have hz0 : toReal z ≠ 0 := by
    have hd0 : (Numerics.Dyadic.mk sign m (e + (k : Int))).toReal ≠ 0 :=
      (Dyadic.toReal_eq_zero_iff _).not.mpr hm
    simpa only [toReal_eq, hz] using hd0
  apply mul_eq_of_finite_value x y z hfmt hxfinite hyfinite hzfinite hz0
  simpa only [toReal_eq, hx, hy, hz] using dyadic_scale_value sign m k e

theorem binary32_mantissa_scale_mul
    (x y z : Model FloatFormat.binary32) (sign : Bool) (m E : Nat)
    (hm : m ≠ 0)
    (hx : toDyadic? x = some ⟨false, m, 0⟩)
    (hy : toDyadic? y = some ⟨sign, 2 ^ 23, (E : Int) - 173⟩)
    (hz : toDyadic? z = some ⟨sign, m, (E : Int) - 150⟩) :
    mul x y = z := by
  apply mul_eq_of_scale_decodes x y z (by decide)
    sign m 23 ((E : Int) - 173) hm hx hy
  have he : (E : Int) - 173 + ((23 : Nat) : Int) = (E : Int) - 150 := by
    omega
  simpa only [he] using hz

end R2W01cModel

namespace R2W01c

open FloatLib.Floats.Formats.BinaryInterchange
open R2W01b

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

theorem mantissa_toNat (u : UInt32) :
    (mantissa u).toNat = 8388608 + wordFrac u := by
  rw [mantissa, UInt32.toNat_or, UInt32.toNat_and]
  change (u.toNat &&& (2 ^ 23 - 1)) ||| 2 ^ 23 = 8388608 + wordFrac u
  rw [Nat.and_two_pow_sub_one_eq_mod,
    Nat.or_two_pow_eq_add_of_lt (Nat.mod_lt u.toNat (by decide : 0 < 2 ^ 23))]
  exact Nat.add_comm _ _

theorem mantissa_bounds (u : UInt32) :
    8388608 ≤ (mantissa u).toNat ∧ (mantissa u).toNat < 16777216 := by
  rw [mantissa_toNat]
  have hf := wordFrac_lt u
  omega

theorem normal_wordExp_bounds (u : UInt32) (hn : NormalBand u) :
    24 ≤ wordExp u ∧ wordExp u < 255 := by
  rcases hn with ⟨hl, hh⟩
  rw [UInt32.le_iff_toNat_le, magnitude_toNat] at hl
  rw [UInt32.lt_iff_toNat_lt, magnitude_toNat] at hh
  change 201326592 ≤ u.toNat % 2147483648 at hl
  change u.toNat % 2147483648 < 2139095040 at hh
  have hu := u.toNat_lt_size
  change u.toNat < 4294967296 at hu
  unfold wordExp
  omega

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

theorem high_bit_of_lt512 (n : Nat) (hn : n < 512) :
    n &&& 256 = n / 256 * 256 := by
  change n &&& 2 ^ 8 = n / 256 * 256
  rw [Nat.and_two_pow, Nat.testBit_eq_decide_div_mod_eq]
  change (decide (n / 256 % 2 = 1)).toNat * 256 = n / 256 * 256
  by_cases h : n < 256
  · have hd : n / 256 = 0 := Nat.div_eq_of_lt h
    simp [hd]
  · have hd : n / 256 = 1 := by omega
    simp [hd]

theorem tableSign_nat (u : UInt32) :
    ((tableIndex u &&& 256) <<< 23).toNat =
      u.toNat / 2147483648 * 2147483648 := by
  have hu := u.toNat_lt_size
  change u.toNat < 4294967296 at hu
  have hj : u.toNat / 8388608 < 512 := by omega
  rw [UInt32.toNat_shiftLeft, UInt32.toNat_and, tableIndex_nat]
  change (((u.toNat / 8388608) &&& 256) <<< 23) % 4294967296 = _
  rw [high_bit_of_lt512 _ hj, Nat.shiftLeft_eq]
  change (u.toNat / 8388608 / 256 * 256 * 8388608) % 4294967296 = _
  omega

theorem scaleBits_nat (u : UInt32) (hn : NormalBand u) :
    (scaleBits (tableIndex u)).toNat =
      u.toNat / 2147483648 * 2147483648 + (wordExp u - 23) * 8388608 := by
  have he := normal_wordExp_bounds u hn
  have het := tableExp_nat u
  have helo : (24 : UInt32) ≤ (tableIndex u &&& 255) := by
    rw [UInt32.le_iff_toNat_le, het]
    exact he.1
  have hehi : (tableIndex u &&& 255) ≤ (254 : UInt32) := by
    rw [UInt32.le_iff_toNat_le, het]
    change wordExp u ≤ 254
    omega
  have hg :
      (decide (24 ≤ (tableIndex u &&& 255)) &&
        decide ((tableIndex u &&& 255) ≤ 254)) = true := by
    simp only [Bool.and_eq_true, decide_eq_true_eq]
    exact ⟨helo, hehi⟩
  have hsub : ((tableIndex u &&& 255) - 23).toNat = wordExp u - 23 := by
    have hle : (23 : UInt32) ≤ (tableIndex u &&& 255) := by
      rw [UInt32.le_iff_toNat_le, het]
      change 23 ≤ wordExp u
      omega
    have h := UInt32.toNat_sub_of_le (tableIndex u &&& 255) 23 hle
    change ((tableIndex u &&& 255) - 23).toNat = (tableIndex u &&& 255).toNat - 23 at h
    simpa only [het] using h
  have hshift : (((tableIndex u &&& 255) - 23) <<< 23).toNat =
      (wordExp u - 23) * 8388608 := by
    rw [UInt32.toNat_shiftLeft, hsub]
    change ((wordExp u - 23) <<< 23) % 4294967296 = _
    rw [Nat.shiftLeft_eq]
    change ((wordExp u - 23) * 8388608) % 4294967296 = _
    exact Nat.mod_eq_of_lt (by omega)
  unfold scaleBits
  dsimp only
  rw [if_pos hg, UInt32.toNat_or, tableSign_nat, hshift]
  have hlo : (wordExp u - 23) * 8388608 < 2 ^ 31 := by
    change (wordExp u - 23) * 8388608 < 2147483648
    omega
  rw [Nat.mul_comm (u.toNat / 2147483648) 2147483648]
  exact (Nat.two_pow_add_eq_or_of_lt hlo (u.toNat / 2147483648)).symm

theorem scale_wordSign (u : UInt32) (hn : NormalBand u) :
    wordSign (scaleBits (tableIndex u)) = wordSign u := by
  have hu := u.toNat_lt_size
  change u.toNat < 4294967296 at hu
  have he := normal_wordExp_bounds u hn
  apply Bool.eq_iff_iff.mpr
  simp only [wordSign, decide_eq_true_eq]
  rw [scaleBits_nat u hn]
  omega

theorem scale_wordExp (u : UInt32) (hn : NormalBand u) :
    wordExp (scaleBits (tableIndex u)) = wordExp u - 23 := by
  have hu := u.toNat_lt_size
  change u.toNat < 4294967296 at hu
  have he := normal_wordExp_bounds u hn
  change (scaleBits (tableIndex u)).toNat / 8388608 % 256 = wordExp u - 23
  rw [scaleBits_nat u hn]
  omega

theorem scale_wordFrac (u : UInt32) (hn : NormalBand u) :
    wordFrac (scaleBits (tableIndex u)) = 0 := by
  have hu := u.toNat_lt_size
  change u.toNat < 4294967296 at hu
  have he := normal_wordExp_bounds u hn
  change (scaleBits (tableIndex u)).toNat % 8388608 = 0
  rw [scaleBits_nat u hn]
  omega

theorem normal_raw32_decode (u : UInt32) (hn : NormalBand u) :
    Model.toDyadic? (raw32 u) =
      some ⟨wordSign u, (mantissa u).toNat, (wordExp u : Int) - 150⟩ := by
  have he := normal_wordExp_bounds u hn
  rw [raw32_eq_fields, mantissa_toNat]
  exact fields32_toDyadic (wordSign u) (wordExp u) (wordFrac u)
    (by omega) he.2 (wordFrac_lt u)

theorem scale_raw32_decode (u : UInt32) (hn : NormalBand u) :
    Model.toDyadic? (raw32 (scaleBits (tableIndex u))) =
      some ⟨wordSign u, 8388608, (wordExp u : Int) - 173⟩ := by
  have he := normal_wordExp_bounds u hn
  rw [raw32_eq_fields, scale_wordSign u hn, scale_wordExp u hn, scale_wordFrac u hn]
  have hd := fields32_toDyadic (wordSign u) (wordExp u - 23) 0
    (by omega) (by omega) (by decide)
  have hexp : ((wordExp u - 23 : Nat) : Int) - 150 =
      (wordExp u : Int) - 173 := by omega
  simpa only [Nat.add_zero, hexp] using hd

end R2W01c

namespace R2W01c

open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange
open R2W01b

theorem mantissa_native_decode (u : UInt32) :
    Model.toDyadic? (nativeModel (mantissa u).toFloat32) =
      some ⟨false, (mantissa u).toNat, 0⟩ := by
  have hm := mantissa_bounds u
  simpa only [nativeModel] using
    uint32_mantissa_model_decode (mantissa u) hm.1 hm.2

theorem scale_native_decode (u : UInt32) (hn : NormalBand u) :
    Model.toDyadic? (nativeModel (scaleAt u)) =
      some ⟨wordSign u, 2 ^ 23, (wordExp u : Int) - 173⟩ := by
  rw [scaleAt_eq]
  apply nativeModel_ofBits_decode
  rw [rawModel_eq_ofUInt32]
  exact scale_raw32_decode u hn

theorem target_raw_decode (u : UInt32) (hn : NormalBand u) :
    Model.toDyadic? (rawModel u) =
      some ⟨wordSign u, (mantissa u).toNat, (wordExp u : Int) - 150⟩ := by
  rw [rawModel_eq_ofUInt32]
  exact normal_raw32_decode u hn

theorem normal_model_mul (u : UInt32) (hn : NormalBand u) :
    Model.mul (nativeModel (mantissa u).toFloat32) (nativeModel (scaleAt u)) =
      rawModel u := by
  apply R2W01cModel.binary32_mantissa_scale_mul
    (nativeModel (mantissa u).toFloat32) (nativeModel (scaleAt u)) (rawModel u)
    (wordSign u) (mantissa u).toNat (wordExp u)
  · have hm := (mantissa_bounds u).1
    omega
  · exact mantissa_native_decode u
  · exact scale_native_decode u hn
  · exact target_raw_decode u hn

theorem normal_eq (u : UInt32) (hn : NormalBand u) :
    tableProduct u = Float32.ofBits u := by
  exact native_mul_eq_of_decoded_raw_model_mul_eq
    (mantissa u).toFloat32 (scaleAt u) u
    (mantissa_native_decode u) (scale_native_decode u hn) (normal_model_mul u hn)

theorem normal_bits (u : UInt32) (hn : NormalBand u) :
    (tableProduct u).toBits = u := by
  exact native_mul_bits_eq_of_raw_model_mul_eq
    (mantissa u).toFloat32 (scaleAt u) u
    (nativeFinite_of_decode _ (mantissa_native_decode u))
    (nativeFinite_of_decode _ (scale_native_decode u hn)) (normal_model_mul u hn)

theorem normal_finite (u : UInt32) (hn : NormalBand u) :
    (tableProduct u).isFinite = true := by
  rw [normal_eq u hn]
  exact nativeFinite_of_decode _
    (nativeModel_ofBits_decode u (target_raw_decode u hn))

theorem convert_eq (u : UInt32) : convert u = Float32.ofBits u := by
  exact R2W01b.convert_eq normal_eq u

theorem convert_bits_eq (u : UInt32) :
    (convert u).toBits = (Float32.ofBits u).toBits := by
  exact congrArg Float32.toBits (convert_eq u)

theorem replace_decoder {α : Sort _}
    (core : (UInt32 → Float32) → α) : core convert = core Float32.ofBits := by
  exact congrArg core (funext convert_eq)

theorem foldl_convert_eq
    (xs : List UInt32) (step : Float32 → Float32 → Float32) (acc : Float32) :
    xs.foldl (fun z u => step z (convert u)) acc =
      xs.foldl (fun z u => step z (Float32.ofBits u)) acc := by
  exact R2W01b.foldl_convert_eq normal_eq xs step acc

end R2W01c


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

namespace LowScale

/-- The subnormal branch, with the existing rounding and packing unchanged. -/
@[inline] def roundLow (sign : Bool) (product scale : UInt64) : UInt32 :=
  if product == 0 then
    if sign then 0x80000000 else 0
  else
    let fraction := FastMul.rseAny product (149 - scale)
    if fraction == 0 then
      if sign then 0x80000000 else 0
    else if fraction == 0x800000 then
      FastMul.mkW sign 1 0
    else
      FastMul.mkW sign 0 fraction.toUInt32

theorem roundLow_eq (sign : Bool) (product scale : UInt64)
    (hp : product.toNat < 2 ^ 48) (hs : scale.toNat ≤ 123) :
    roundLow sign product scale = FastMul.roundP sign product scale := by
  by_cases hz : product = 0
  · subst product
    simp [roundLow, FastMul.roundP]
  · have hn : product.toNat ≠ 0 := by
      intro h
      apply hz
      apply UInt64.toNat_inj.mp
      exact h
    have hl : (FastMul.fastLog2 product).toNat < 48 := by
      rw [FastMul.fastLog2_eq]
      change product.toNat.log2 < 48
      exact (Nat.log2_lt hn).mpr hp
    have hposition : FastMul.fastLog2 product + scale < (172 : UInt64) := by
      rw [UInt64.lt_iff_toNat_lt, UInt64.toNat_add]
      change ((FastMul.fastLog2 product).toNat + scale.toNat) %
        18446744073709551616 < 172
      rw [Nat.mod_eq_of_lt (by omega)]
      omega
    have hscale : scale < (149 : UInt64) := by
      rw [UInt64.lt_iff_toNat_lt]
      change scale.toNat < 149
      omega
    simp only [roundLow, FastMul.roundP, beq_iff_eq, hz, ite_false,
      hposition, ite_true, hscale]

/-- The word guards make the selector equal to the old rounder on every input. -/
@[inline] def roundSelect (sign : Bool) (product scale : UInt64) : UInt32 :=
  if h : product < (0x1000000000000 : UInt64) ∧ scale ≤ (123 : UInt64) then
    roundLow sign product scale
  else FastMul.roundP sign product scale

theorem roundSelect_eq (sign : Bool) (product scale : UInt64) :
    roundSelect sign product scale = FastMul.roundP sign product scale := by
  unfold roundSelect
  split
  · rename_i h
    apply roundLow_eq
    · have hp := h.1
      rw [UInt64.lt_iff_toNat_lt] at hp
      change product.toNat < 2 ^ 48 at hp
      exact hp
    · have hs := h.2
      rw [UInt64.le_iff_toNat_le] at hs
      change scale.toNat ≤ 123 at hs
      exact hs
  · rfl


open FloatLib.Floats.Formats.BinaryInterchange.Model.NativeBinary32

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
  roundSelect sign (xMantissa * yMantissa) (xScale + yScale)


theorem core_eq (a b : UInt32) : core a b = FastMul.core a b := by
  simp only [core, FastMul.core, roundSelect_eq]

@[inline] def mul (x y : Binary32) : Binary32 :=
  if FastMul.special x.raw.1 y.raw.1 then ExecFloat.mul x y
  else FastMul.ofBits (core x.raw.1 y.raw.1)

theorem mul_eq (x y : Binary32) : mul x y = FastMul.mul x y := by
  simp only [mul, FastMul.mul, core_eq]

theorem mul_spec (x y : Binary32) : mul x y = ExecFloat.Spec.mul x y := by
  rw [mul_eq]
  exact FastMul.mul_spec x y

end LowScale

namespace GuardBridge

open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange

/-- Finiteness excludes the noncanonical NaN representation case. -/
theorem modelCanonicalOfFinite {fmt : FloatFormat} (x : Model fmt)
    (hx : (Model.toModel x).isFinite = true) : Model.IsModelCanonical x := by
  constructor
  intro he hm
  have hnan : Model.toModel x = Float.Model.UnpackedFloat.notANumber := by
    simp only [Model.toModel, Float.Model.UnpackedFloat.unpack, he, hm, ite_true, ite_false]
  rw [hnan] at hx
  cases hx

theorem finiteRoundtrip (x : Competition.Binary32)
    (hx : (ExecFloat.Binary.toFloat32 x).isFinite = true) :
    ExecFloat.Binary.ofFloat32 (ExecFloat.Binary.toFloat32 x) = x := by
  have hcanonical : Model.IsModelCanonical (ExecFloat.Binary.toModel x) := by
    apply modelCanonicalOfFinite
    have hf := hx
    change ((Model.toFloat32Model (ExecFloat.Binary.toModel x)).unpack).isFinite = true at hf
    rw [Model.unpack_toFloat32Model] at hf
    exact hf
  apply Configured.Family.toModel_injective
  change ExecFloat.Binary.toModel
      (ExecFloat.Binary.ofFloat32 (ExecFloat.Binary.toFloat32 x)) =
    ExecFloat.Binary.toModel x
  rw [ExecFloat.Binary.toModel_ofFloat32, ExecFloat.Binary.toModel_toFloat32_eq,
    Model.ofFloat32Model_toFloat32Model]
  exact Model.canonicalizeModel_eq_self _ hcanonical

end GuardBridge

namespace WordFinite

open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange

theorem modelFiniteOfExp (w : UInt32)
    (hw : FloatLib.Floats.Formats.BinaryInterchange.Model.NativeBinary32.expField w ≠ 0xff) :
    (Model.toModel (Model.NativeBinary32.ofUInt32 w)).isFinite = true := by
  have hd : ∃ d, Model.toDyadic? (Model.NativeBinary32.ofUInt32 w) = some d := by
    rw [← Model.NativeBinary32.toDyadic_eq]
    simp only [Model.NativeBinary32.toUInt32_ofUInt32]
    unfold Model.NativeBinary32.toDyadic?
    simp only [beq_iff_eq, hw, ite_false]
    split_ifs <;> exact ⟨_, rfl⟩
  obtain ⟨d, hd⟩ := hd
  rw [Model.toDyadic?_ieee_eq_model FloatFormat.binary32 (by decide)] at hd
  cases hm : Model.toModel (Model.NativeBinary32.ofUInt32 w) <;>
    simp_all [Model.unpackedToDyadic?, Float.Model.UnpackedFloat.isFinite]

theorem nativeFiniteOfExp (x : Competition.Binary32)
    (hx : FloatLib.Floats.Formats.BinaryInterchange.Model.NativeBinary32.expField x.raw.1 ≠ 0xff) :
    (ExecFloat.Binary.toFloat32 x).isFinite = true := by
  change ((Model.toFloat32Model (Model.NativeBinary32.ofUInt32 x.raw.1)).unpack).isFinite = true
  rw [Model.unpack_toFloat32Model]
  exact modelFiniteOfExp x.raw.1 hx

end WordFinite


namespace NativeBridge

open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange
open Float.Model.UnpackedFloat
open FloatLib.Floats.Formats.BinaryInterchange.Model

/-
The three target-exponent lemmas below are ported from FloatLib Team, MIT,
commit 1f5771b3e36a98f17fcac2c6d76aaa024b36aa37,
Arithmetic/LeanModel/MulDiv.lean. Official pinned dependencies are unchanged.
-/
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

/--
If two nonzero mantissas and their exponents satisfy Lean's `roundWithAccuracy` precondition, so
do the product of the mantissas and the sum of the exponents.
-/
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

/--
A finite nonzero value unpacked from a format word satisfies Lean's `roundWithAccuracy`
precondition: a subnormal has the minimum exponent and a normal has its leading bit set.
-/
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


/-- The finite multiplication specifications perform the same exact product and one rounding. -/
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

theorem toModelNativeMul (x y : Float32)
    (hx : x.isFinite = true) (hy : y.isFinite = true) :
    ExecFloat.Binary.toModel (ExecFloat.Binary.ofFloat32 (x * y)) =
      Model.mul (ExecFloat.Binary.toModel (ExecFloat.Binary.ofFloat32 x))
        (ExecFloat.Binary.toModel (ExecFloat.Binary.ofFloat32 y)) := by
  rw [ExecFloat.Binary.toModel_ofFloat32, ExecFloat.Binary.toModel_ofFloat32,
    ExecFloat.Binary.toModel_ofFloat32]
  change Model.ofFloat32Model (Float32.Model.mul x.toModel y.toModel) = _
  rw [Float32.Model.mul, Model.ofFloat32Model_pack]
  have h := modelMulFinite (fmt := FloatFormat.binary32)
    (by decide) (Model.ofFloat32Model x.toModel) (Model.ofFloat32Model y.toModel)
    (by simpa only [Model.toModel_ofFloat32Model, Float32.isFinite,
      Float32.Model.isFinite] using hx)
    (by simpa only [Model.toModel_ofFloat32Model, Float32.isFinite,
      Float32.Model.isFinite] using hy)
  rw [Model.toModel_ofFloat32Model, Model.toModel_ofFloat32Model] at h
  exact h.symm

theorem toModelExecMul (x y : Competition.Binary32) :
    ExecFloat.Binary.toModel (ExecFloat.mul x y) =
      Model.Spec.mul (ExecFloat.Binary.toModel x) (ExecFloat.Binary.toModel y) := by
  rw [ExecFloat.Proof.mul_eq_spec]
  change Configured.Family.toModel
    (ExecFloat.ModelCodec.liftBinary Model.Spec.mul x y) = _
  simp [Configured.Family.toModel, ExecFloat.Binary.toModel]

theorem ofFloat32Mul (x y : Float32)
    (hx : x.isFinite = true) (hy : y.isFinite = true) :
    ExecFloat.Binary.ofFloat32 (x * y) =
      ExecFloat.mul (ExecFloat.Binary.ofFloat32 x) (ExecFloat.Binary.ofFloat32 y) := by
  apply Configured.Family.toModel_injective
  change ExecFloat.Binary.toModel (ExecFloat.Binary.ofFloat32 (x * y)) =
    ExecFloat.Binary.toModel
      (ExecFloat.mul (ExecFloat.Binary.ofFloat32 x) (ExecFloat.Binary.ofFloat32 y))
  rw [toModelExecMul, ← Model.Proof.mul_eq_spec]
  exact toModelNativeMul x y hx hy

end NativeBridge

namespace NotNaNProbe

open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange

/-- Raw non-NaN values, including infinity, have the unique canonical representation. -/
theorem modelCanonicalOfNotNaN {fmt : FloatFormat} (x : Model fmt)
    (hx : (Model.toModel x).isNaN = false) : Model.IsModelCanonical x := by
  constructor
  intro he hm
  have hnan : Model.toModel x = Float.Model.UnpackedFloat.notANumber := by
    simp only [Model.toModel, Float.Model.UnpackedFloat.unpack, he, hm, ite_true, ite_false]
  rw [hnan] at hx
  cases hx

theorem roundtrip (x : Competition.Binary32)
    (hx : (ExecFloat.Binary.toFloat32 x).isNaN = false) :
    ExecFloat.Binary.ofFloat32 (ExecFloat.Binary.toFloat32 x) = x := by
  have hcanonical : Model.IsModelCanonical (ExecFloat.Binary.toModel x) := by
    apply modelCanonicalOfNotNaN
    have hf := hx
    change ((Model.toFloat32Model (ExecFloat.Binary.toModel x)).unpack).isNaN = false at hf
    rw [Model.unpack_toFloat32Model] at hf
    exact hf
  apply Configured.Family.toModel_injective
  change ExecFloat.Binary.toModel
      (ExecFloat.Binary.ofFloat32 (ExecFloat.Binary.toFloat32 x)) =
    ExecFloat.Binary.toModel x
  rw [ExecFloat.Binary.toModel_ofFloat32, ExecFloat.Binary.toModel_toFloat32_eq,
    Model.ofFloat32Model_toFloat32Model]
  exact Model.canonicalizeModel_eq_self _ hcanonical

theorem packNaN_isNaN :
    (Float32.Model.pack Float.Model.UnpackedFloat.notANumber).isNaN = true := by decide

theorem add_inputs (x y : Float32) (h : (x + y).isNaN = false) :
    x.isNaN = false ∧ y.isNaN = false := by
  change (Float32.Model.pack
    (Float.Model.UnpackedFloat.add Float.Model.Format.binary32
      x.toModel.unpack y.toModel.unpack)).isNaN = false at h
  change x.toModel.unpack.isNaN = false ∧ y.toModel.unpack.isNaN = false
  cases hx : x.toModel.unpack <;> cases hy : y.toModel.unpack <;>
    simp_all [Float.Model.UnpackedFloat.add, Float.Model.UnpackedFloat.isNaN,
      packNaN_isNaN]

theorem mul_inputs (x y : Float32) (h : (x * y).isNaN = false) :
    x.isNaN = false ∧ y.isNaN = false := by
  change (Float32.Model.pack
    (Float.Model.UnpackedFloat.mul Float.Model.Format.binary32
      x.toModel.unpack y.toModel.unpack)).isNaN = false at h
  change x.toModel.unpack.isNaN = false ∧ y.toModel.unpack.isNaN = false
  cases hx : x.toModel.unpack <;> cases hy : y.toModel.unpack <;>
    simp_all [Float.Model.UnpackedFloat.mul, Float.Model.UnpackedFloat.isNaN,
      packNaN_isNaN]

end NotNaNProbe

namespace R7Native

open FloatLib.Floats Competition
open FloatLib.Floats.Formats.BinaryInterchange
open Float.Model.UnpackedFloat

abbrev F := FloatFormat.binary32
abbrev M := Model F

theorem finiteDecode (x : M) (hx : (Model.toModel x).isFinite = true) :
    ∃ d, Model.toDyadic? x = some d := by
  have hsome : (Model.toDyadic? x).isSome = true := by
    rw [Model.toDyadic?_ieee_eq_model F (by decide)]
    cases hm : Model.toModel x <;>
      simp_all [Model.unpackedToDyadic?, Float.Model.UnpackedFloat.isFinite]
  cases hd : Model.toDyadic? x with
  | none => simp [hd] at hsome
  | some d => exact ⟨d, rfl⟩

theorem nonNaNView (x : M) (hx : (Model.toModel x).isNaN = false) :
    (Model.toModel x).isFinite = true ∨ ∃ s, Model.toModel x = .infinity s := by
  cases hm : Model.toModel x with
  | notANumber => simp [hm, Float.Model.UnpackedFloat.isNaN] at hx
  | infinity s => exact Or.inr ⟨s, rfl⟩
  | zero s => exact Or.inl rfl
  | finite s m e h => exact Or.inl rfl

theorem eqOfInfinity (x : M) (s : Sign) (hx : Model.toModel x = .infinity s) :
    x = Model.ofModel F (.infinity s) := by
  have hc := NotNaNProbe.modelCanonicalOfNotNaN x
    (by simp [hx, Float.Model.UnpackedFloat.isNaN])
  have h := Model.canonicalizeModel_eq_self x hc
  change Model.ofModel F (Model.toModel x) = x at h
  rw [hx] at h
  exact h.symm

theorem eqOfZero (x : M) (s : Sign) (hx : Model.toModel x = .zero s) :
    x = Model.ofModel F (.zero s) := by
  have hc := NotNaNProbe.modelCanonicalOfNotNaN x
    (by simp [hx, Float.Model.UnpackedFloat.isNaN])
  have h := Model.canonicalizeModel_eq_self x hc
  change Model.ofModel F (Model.toModel x) = x at h
  rw [hx] at h
  exact h.symm

theorem infinityDecode (s : Sign) :
    Model.toDyadic? (Model.ofModel F (.infinity s)) = none := by
  rw [Model.toDyadic?_ieee_eq_model F (by decide), Model.toModel_ofModel_infinity]
  rfl

theorem nativeOverflow_eq (b : Bool) :
    Model.nativeOverflow F b = Model.ofModel F (.infinity (Model.modelSign b)) := by
  cases b <;> decide

theorem specAddInfLeft (s : Sign) (y : M)
    (hn : Model.isNaN y = false) (hi : Model.isInf y = false) :
    Model.Spec.add (Model.ofModel F (.infinity s)) y = Model.ofModel F (.infinity s) := by
  have hxnan := Model.isNaN_ofModel_infinity F (by decide) s
  have hxinf := Model.isInf_ofModel_infinity F (by decide) s
  have hsel := (Model.chooseNaN2_eq_none_iff (Model.ofModel F (.infinity s)) y).mpr
    ⟨hxnan, hn⟩
  unfold Model.Spec.add
  rw [infinityDecode]
  cases hd : Model.toDyadic? y <;> simp [hd, hsel, hxinf, hi]

theorem specAddInfRight (s : Sign) (x : M)
    (hn : Model.isNaN x = false) (hi : Model.isInf x = false) :
    Model.Spec.add x (Model.ofModel F (.infinity s)) = Model.ofModel F (.infinity s) := by
  have hynan := Model.isNaN_ofModel_infinity F (by decide) s
  have hyinf := Model.isInf_ofModel_infinity F (by decide) s
  have hsel := (Model.chooseNaN2_eq_none_iff x (Model.ofModel F (.infinity s))).mpr
    ⟨hn, hynan⟩
  unfold Model.Spec.add
  rw [infinityDecode]
  cases hd : Model.toDyadic? x <;> simp [hd, hsel, hi, hyinf]

theorem specMulInfLeft (s : Sign) (y : M) (d : FloatLib.Numerics.Dyadic)
    (hd : Model.toDyadic? y = some d) (hnz : d.significand ≠ 0) :
    Model.Spec.mul (Model.ofModel F (.infinity s)) y =
      Model.nativeOverflow F (Model.modelSignBit s != d.negative) := by
  have hxnan := Model.isNaN_ofModel_infinity F (by decide) s
  have hxinf := Model.isInf_ofModel_infinity F (by decide) s
  have hynan := Model.isNaN_eq_false_of_toDyadic?_some hd
  have hsel := (Model.chooseNaN2_eq_none_iff (Model.ofModel F (.infinity s)) y).mpr
    ⟨hxnan, hynan⟩
  have hzero := Model.isZero_eq_beq_zero_of_toDyadic?_some hd
  have hsign := Model.sign_eq_signBit_of_toDyadic?_some hd
  simp [Model.Spec.mul, infinityDecode, hd, hsel, hxinf, hzero, hnz,
    Model.signBit_ofModel_infinity, ← hsign]

theorem specMulInfRight (s : Sign) (x : M) (d : FloatLib.Numerics.Dyadic)
    (hd : Model.toDyadic? x = some d) (hnz : d.significand ≠ 0) :
    Model.Spec.mul x (Model.ofModel F (.infinity s)) =
      Model.nativeOverflow F (d.negative != Model.modelSignBit s) := by
  have hynan := Model.isNaN_ofModel_infinity F (by decide) s
  have hyinf := Model.isInf_ofModel_infinity F (by decide) s
  have hxnan := Model.isNaN_eq_false_of_toDyadic?_some hd
  have hxinf := Model.isInf_eq_false_of_toDyadic?_some hd
  have hsel := (Model.chooseNaN2_eq_none_iff x (Model.ofModel F (.infinity s))).mpr
    ⟨hxnan, hynan⟩
  have hzero := Model.isZero_eq_beq_zero_of_toDyadic?_some hd
  have hsign := Model.sign_eq_signBit_of_toDyadic?_some hd
  simp [Model.Spec.mul, infinityDecode, hd, hsel, hxinf, hyinf, hzero, hnz,
    Model.signBit_ofModel_infinity, ← hsign]

theorem modelAdd (x y : M)
    (hx : (Model.toModel x).isNaN = false) (hy : (Model.toModel y).isNaN = false) :
    Model.add x y = Model.ofModel F
      (Float.Model.UnpackedFloat.add F.toModel (Model.toModel x) (Model.toModel y)) := by
  rcases nonNaNView x hx with hxf | ⟨sx, hxi⟩
  · rcases nonNaNView y hy with hyf | ⟨sy, hyi⟩
    · exact Model.add_eq_ofModel_add_of_isFinite (by decide) x y hxf hyf
    · obtain ⟨dx, hdx⟩ := finiteDecode x hxf
      rw [eqOfInfinity y sy hyi, Model.Proof.add_eq_spec,
        specAddInfRight sy x (Model.isNaN_eq_false_of_toDyadic?_some hdx)
          (Model.isInf_eq_false_of_toDyadic?_some hdx)]
      cases hm : Model.toModel x <;>
        simp_all [Float.Model.UnpackedFloat.isFinite, Float.Model.UnpackedFloat.add]
  · rcases nonNaNView y hy with hyf | ⟨sy, hyi⟩
    · obtain ⟨dy, hdy⟩ := finiteDecode y hyf
      rw [eqOfInfinity x sx hxi, Model.Proof.add_eq_spec,
        specAddInfLeft sx y (Model.isNaN_eq_false_of_toDyadic?_some hdy)
          (Model.isInf_eq_false_of_toDyadic?_some hdy)]
      cases hm : Model.toModel y <;>
        simp_all [Float.Model.UnpackedFloat.isFinite, Float.Model.UnpackedFloat.add]
    · rw [eqOfInfinity x sx hxi, eqOfInfinity y sy hyi]
      cases sx <;> cases sy <;> decide

theorem modelMulInfLeft (s : Sign) (y : M)
    (hy : (Model.toModel y).isFinite = true) :
    Model.mul (Model.ofModel F (.infinity s)) y = Model.ofModel F
      (Float.Model.UnpackedFloat.mul F.toModel (.infinity s) (Model.toModel y)) := by
  cases hm : Model.toModel y with
  | notANumber => simp [hm, Float.Model.UnpackedFloat.isFinite] at hy
  | infinity t => simp [hm, Float.Model.UnpackedFloat.isFinite] at hy
  | zero t =>
      rw [eqOfZero y t hm]
      cases s <;> cases t <;> decide
  | finite t m e hp =>
      have hd : Model.toDyadic? y = some ⟨Model.modelSignBit t, m, e⟩ := by
        rw [Model.toDyadic?_ieee_eq_model F (by decide), hm]
        rfl
      rw [Model.Proof.mul_eq_spec, specMulInfLeft s y _ hd (Nat.ne_of_gt hp),
        nativeOverflow_eq]
      cases s <;> cases t <;> rfl

theorem modelMulInfRight (s : Sign) (x : M)
    (hx : (Model.toModel x).isFinite = true) :
    Model.mul x (Model.ofModel F (.infinity s)) = Model.ofModel F
      (Float.Model.UnpackedFloat.mul F.toModel (Model.toModel x) (.infinity s)) := by
  cases hm : Model.toModel x with
  | notANumber => simp [hm, Float.Model.UnpackedFloat.isFinite] at hx
  | infinity t => simp [hm, Float.Model.UnpackedFloat.isFinite] at hx
  | zero t =>
      rw [eqOfZero x t hm]
      cases s <;> cases t <;> decide
  | finite t m e hp =>
      have hd : Model.toDyadic? x = some ⟨Model.modelSignBit t, m, e⟩ := by
        rw [Model.toDyadic?_ieee_eq_model F (by decide), hm]
        rfl
      rw [Model.Proof.mul_eq_spec, specMulInfRight s x _ hd (Nat.ne_of_gt hp),
        nativeOverflow_eq]
      cases s <;> cases t <;> rfl

theorem modelMul (x y : M)
    (hx : (Model.toModel x).isNaN = false) (hy : (Model.toModel y).isNaN = false) :
    Model.mul x y = Model.ofModel F
      (Float.Model.UnpackedFloat.mul F.toModel (Model.toModel x) (Model.toModel y)) := by
  rcases nonNaNView x hx with hxf | ⟨sx, hxi⟩
  · rcases nonNaNView y hy with hyf | ⟨sy, hyi⟩
    · exact NativeBridge.modelMulFinite (by decide) x y hxf hyf
    · rw [eqOfInfinity y sy hyi, Model.toModel_ofModel_infinity]
      exact modelMulInfRight sy x hxf
  · rcases nonNaNView y hy with hyf | ⟨sy, hyi⟩
    · rw [eqOfInfinity x sx hxi, Model.toModel_ofModel_infinity]
      exact modelMulInfLeft sx y hyf
    · rw [eqOfInfinity x sx hxi, eqOfInfinity y sy hyi]
      cases sx <;> cases sy <;> decide

theorem toModelExecAdd (x y : Binary32) :
    ExecFloat.Binary.toModel (ExecFloat.add x y) =
      Model.Spec.add (ExecFloat.Binary.toModel x) (ExecFloat.Binary.toModel y) := by
  rw [ExecFloat.Proof.add_eq_spec]
  change Configured.Family.toModel
    (ExecFloat.ModelCodec.liftBinary Model.Spec.add x y) = _
  simp [Configured.Family.toModel, ExecFloat.Binary.toModel]

theorem ofFloat32Add (x y : Float32) (hx : x.isNaN = false) (hy : y.isNaN = false) :
    ExecFloat.Binary.ofFloat32 (x + y) =
      ExecFloat.add (ExecFloat.Binary.ofFloat32 x) (ExecFloat.Binary.ofFloat32 y) := by
  apply Configured.Family.toModel_injective
  change ExecFloat.Binary.toModel (ExecFloat.Binary.ofFloat32 (x + y)) =
    ExecFloat.Binary.toModel
      (ExecFloat.add (ExecFloat.Binary.ofFloat32 x) (ExecFloat.Binary.ofFloat32 y))
  rw [toModelExecAdd, ← Model.Proof.add_eq_spec]
  rw [ExecFloat.Binary.toModel_ofFloat32, ExecFloat.Binary.toModel_ofFloat32,
    ExecFloat.Binary.toModel_ofFloat32]
  change Model.ofFloat32Model (Float32.Model.add x.toModel y.toModel) = _
  rw [Float32.Model.add, Model.ofFloat32Model_pack]
  have h := modelAdd (Model.ofFloat32Model x.toModel) (Model.ofFloat32Model y.toModel)
    (by simpa only [Model.toModel_ofFloat32Model, Float32.isNaN, Float32.Model.isNaN] using hx)
    (by simpa only [Model.toModel_ofFloat32Model, Float32.isNaN, Float32.Model.isNaN] using hy)
  rw [Model.toModel_ofFloat32Model, Model.toModel_ofFloat32Model] at h
  exact h.symm

theorem ofFloat32Mul (x y : Float32) (hx : x.isNaN = false) (hy : y.isNaN = false) :
    ExecFloat.Binary.ofFloat32 (x * y) =
      ExecFloat.mul (ExecFloat.Binary.ofFloat32 x) (ExecFloat.Binary.ofFloat32 y) := by
  apply Configured.Family.toModel_injective
  change ExecFloat.Binary.toModel (ExecFloat.Binary.ofFloat32 (x * y)) =
    ExecFloat.Binary.toModel
      (ExecFloat.mul (ExecFloat.Binary.ofFloat32 x) (ExecFloat.Binary.ofFloat32 y))
  rw [NativeBridge.toModelExecMul, ← Model.Proof.mul_eq_spec]
  rw [ExecFloat.Binary.toModel_ofFloat32, ExecFloat.Binary.toModel_ofFloat32,
    ExecFloat.Binary.toModel_ofFloat32]
  change Model.ofFloat32Model (Float32.Model.mul x.toModel y.toModel) = _
  rw [Float32.Model.mul, Model.ofFloat32Model_pack]
  have h := modelMul (Model.ofFloat32Model x.toModel) (Model.ofFloat32Model y.toModel)
    (by simpa only [Model.toModel_ofFloat32Model, Float32.isNaN, Float32.Model.isNaN] using hx)
    (by simpa only [Model.toModel_ofFloat32Model, Float32.isNaN, Float32.Model.isNaN] using hy)
  rw [Model.toModel_ofFloat32Model, Model.toModel_ofFloat32Model] at h
  exact h.symm

end R7Native

/- Word NaN selection: fixed public binary32 fields and exact quieting/priority.
   Newly integrated statement probe; NOT_RUN in the official compiler. -/
namespace DWordNaN

open FloatLib.Floats.Formats.BinaryInterchange
abbrev M := Model FloatFormat.binary32

@[inline] def rawNaN (u : UInt32) : Bool :=
  Model.NativeBinary32.expField u == 0xff && Model.NativeBinary32.fracField u != 0

@[inline] def rawSNaN (u : UInt32) : Bool :=
  rawNaN u && (u &&& 0x00400000) == 0

theorem rawNaN_eq (u : UInt32) :
    rawNaN u = Model.isNaN (Model.NativeBinary32.ofUInt32 u) := by
  apply Bool.eq_iff_iff.mpr
  change ((Model.NativeBinary32.expField u == 0xff && Model.NativeBinary32.fracField u != 0) = true) ↔
    ((Model.expField (Model.NativeBinary32.ofUInt32 u) == 255 &&
      Model.fracField (Model.NativeBinary32.ofUInt32 u) != 0) = true)
  simp only [Bool.and_eq_true, beq_iff_eq, bne_iff_ne]
  have he : Model.NativeBinary32.expField u = 0xff ↔
      Model.expField (Model.NativeBinary32.ofUInt32 u) = 255 := by
    change Model.NativeBinary32.expField u = 0xff ↔
      (Model.NativeBinary32.expField u).toNat = 255
    exact UInt32.toNat_inj.symm
  have hf : Model.NativeBinary32.fracField u = 0 ↔
      Model.fracField (Model.NativeBinary32.ofUInt32 u) = 0 := by
    change Model.NativeBinary32.fracField u = 0 ↔
      (Model.NativeBinary32.fracField u).toNat = 0
    exact UInt32.toNat_inj.symm
  exact and_congr he (not_congr hf)

theorem rawSNaN_eq (u : UInt32) :
    rawSNaN u = Model.isSNaN (Model.NativeBinary32.ofUInt32 u) := by
  unfold rawSNaN
  rw [rawNaN_eq]
  change (Model.isNaN (Model.NativeBinary32.ofUInt32 u) && ((u &&& 0x00400000) == 0)) =
    (Model.isNaN (Model.NativeBinary32.ofUInt32 u) &&
      ((u.toBitVec &&& (4194304#32)) == 0))
  apply congrArg (fun b : Bool => Model.isNaN (Model.NativeBinary32.ofUInt32 u) && b)
  apply Bool.eq_iff_iff.mpr
  simp only [beq_iff_eq]
  rw [← UInt32.toBitVec_inj, UInt32.toBitVec_and]
  rfl

theorem quietWord_eq (u : UInt32) (hu : rawNaN u = true) :
    Model.NativeBinary32.ofUInt32 (u ||| 0x00400000) =
      Model.quietNaN (Model.NativeBinary32.ofUInt32 u) := by
  have hm : Model.isNaN (Model.NativeBinary32.ofUInt32 u) = true := by
    rw [← rawNaN_eq]
    exact hu
  have h := Model.NativeBinary32.ofUInt32_or_quietBit
    (Model.NativeBinary32.ofUInt32 u)
  simp only [Model.NativeBinary32.toUInt32_ofUInt32] at h
  rw [h]
  change _ = if Model.isNaN (Model.NativeBinary32.ofUInt32 u) then
    Model.ofBits ((Model.NativeBinary32.ofUInt32 u).bits |||
      FloatFormat.quietBit FloatFormat.binary32)
    else Model.NativeBinary32.ofUInt32 u
  rw [hm]
  rfl

theorem quietWord_eq_snan (u : UInt32) (hu : rawSNaN u = true) :
    Model.NativeBinary32.ofUInt32 (u ||| 0x00400000) =
      Model.quietNaN (Model.NativeBinary32.ofUInt32 u) := by
  apply quietWord_eq
  change (rawNaN u && ((u &&& 0x00400000) == 0)) = true at hu
  have hh : rawNaN u = true ∧ ((u &&& 0x00400000) == 0) = true := by
    simpa only [Bool.and_eq_true] using hu
  exact hh.1

@[inline] def rawChoose (a b : UInt32) : Option UInt32 :=
  if rawSNaN a then some (a ||| 0x00400000)
  else if rawSNaN b then some (b ||| 0x00400000)
  else if rawNaN a then some (a ||| 0x00400000)
  else if rawNaN b then some (b ||| 0x00400000)
  else none

theorem rawChoose_eq (a b : UInt32) :
    (rawChoose a b).map Model.NativeBinary32.ofUInt32 =
      Model.chooseNaN2 (Model.NativeBinary32.ofUInt32 a)
        (Model.NativeBinary32.ofUInt32 b) := by
  unfold rawChoose Model.chooseNaN2
  rw [← rawSNaN_eq a, ← rawSNaN_eq b, ← rawNaN_eq a, ← rawNaN_eq b]
  by_cases ha : rawSNaN a = true
  · simp only [ha, ite_true, Option.map_some]
    exact congrArg some (quietWord_eq_snan a ha)
  · by_cases hb : rawSNaN b = true
    · simp only [ha, hb, ite_false, ite_true, Option.map_some]
      exact congrArg some (quietWord_eq_snan b hb)
    · by_cases hna : rawNaN a = true
      · simp only [ha, hb, hna, ite_false, ite_true, Option.map_some]
        exact congrArg some (quietWord_eq a hna)
      · by_cases hnb : rawNaN b = true
        · simp only [ha, hb, hna, hnb, ite_false, ite_true, Option.map_some]
          exact congrArg some (quietWord_eq b hnb)
        · simp only [ha, hb, hna, hnb, Bool.false_eq_true, ite_false, Option.map_none]

theorem rawNaN_exp (u : UInt32) (hu : rawNaN u = true) :
    Model.NativeBinary32.expField u = 0xff := by
  have hh : Model.NativeBinary32.expField u = 0xff ∧
      Model.NativeBinary32.fracField u ≠ 0 := by
    simpa only [rawNaN, Bool.and_eq_true, beq_iff_eq, bne_iff_ne] using hu
  exact hh.1

theorem rawChoose_nonfinite (a b w : UInt32) (hw : rawChoose a b = some w) :
    Model.NativeBinary32.expField a = 0xff ∨ Model.NativeBinary32.expField b = 0xff := by
  unfold rawChoose at hw
  split at hw
  · rename_i ha
    have hh : rawNaN a = true ∧ ((a &&& 0x00400000) == 0) = true := by
      simpa only [rawSNaN, Bool.and_eq_true] using ha
    exact Or.inl (rawNaN_exp a hh.1)
  · split at hw
    · rename_i hb
      have hh : rawNaN b = true ∧ ((b &&& 0x00400000) == 0) = true := by
        simpa only [rawSNaN, Bool.and_eq_true] using hb
      exact Or.inr (rawNaN_exp b hh.1)
    · split at hw
      · rename_i ha
        exact Or.inl (rawNaN_exp a ha)
      · split at hw
        · rename_i hb
          exact Or.inr (rawNaN_exp b hb)
        · cases hw

theorem specialDecode (u : UInt32) (hu : Model.NativeBinary32.expField u = 0xff) :
    Model.toDyadic? (Model.NativeBinary32.ofUInt32 u) = none := by
  rw [← Model.NativeBinary32.toDyadic_eq]
  simp only [Model.NativeBinary32.toUInt32_ofUInt32]
  unfold Model.NativeBinary32.toDyadic?
  simp [hu]

theorem selected_model_add (a b w : UInt32) (hw : rawChoose a b = some w) :
    Model.NativeBinary32.ofUInt32 w = Model.Spec.add
      (Model.NativeBinary32.ofUInt32 a) (Model.NativeBinary32.ofUInt32 b) := by
  have hc : Model.chooseNaN2 (Model.NativeBinary32.ofUInt32 a)
      (Model.NativeBinary32.ofUInt32 b) = some (Model.NativeBinary32.ofUInt32 w) := by
    rw [← rawChoose_eq, hw]
    rfl
  rcases rawChoose_nonfinite a b w hw with ha | hb
  · unfold Model.Spec.add
    rw [specialDecode a ha]
    cases Model.toDyadic? (Model.NativeBinary32.ofUInt32 b) <;> simp only [hc]
  · unfold Model.Spec.add
    rw [specialDecode b hb]
    cases Model.toDyadic? (Model.NativeBinary32.ofUInt32 a) <;> simp only [hc]

theorem selected_model_mul (a b w : UInt32) (hw : rawChoose a b = some w) :
    Model.NativeBinary32.ofUInt32 w = Model.Spec.mul
      (Model.NativeBinary32.ofUInt32 a) (Model.NativeBinary32.ofUInt32 b) := by
  have hc : Model.chooseNaN2 (Model.NativeBinary32.ofUInt32 a)
      (Model.NativeBinary32.ofUInt32 b) = some (Model.NativeBinary32.ofUInt32 w) := by
    rw [← rawChoose_eq, hw]
    rfl
  rcases rawChoose_nonfinite a b w hw with ha | hb
  · unfold Model.Spec.mul
    rw [specialDecode a ha]
    cases Model.toDyadic? (Model.NativeBinary32.ofUInt32 b) <;> simp only [hc]
  · unfold Model.Spec.mul
    rw [specialDecode b hb]
    cases Model.toDyadic? (Model.NativeBinary32.ofUInt32 a) <;> simp only [hc]

open FloatLib.Floats Competition

theorem selected_add (x y : Binary32) (w : UInt32)
    (hw : rawChoose x.raw.1 y.raw.1 = some w) :
    Submission.FastMul.ofBits w = ExecFloat.Spec.add x y := by
  rw [← ExecFloat.Proof.add_eq_spec]
  apply Configured.Family.toModel_injective
  change Model.NativeBinary32.ofUInt32 w = ExecFloat.Binary.toModel (ExecFloat.add x y)
  rw [Submission.R7Native.toModelExecAdd]
  exact selected_model_add x.raw.1 y.raw.1 w hw

theorem selected_mul (x y : Binary32) (w : UInt32)
    (hw : rawChoose x.raw.1 y.raw.1 = some w) :
    Submission.FastMul.ofBits w = ExecFloat.Spec.mul x y := by
  rw [← ExecFloat.Proof.mul_eq_spec]
  apply Configured.Family.toModel_injective
  change Model.NativeBinary32.ofUInt32 w = ExecFloat.Binary.toModel (ExecFloat.mul x y)
  rw [Submission.NativeBridge.toModelExecMul]
  exact selected_model_mul x.raw.1 y.raw.1 w hw

end DWordNaN

namespace ScalarNaN

@[inline] def add (x y : Binary32) : Binary32 :=
  match DWordNaN.rawChoose x.raw.1 y.raw.1 with
  | some w => FastMul.ofBits w
  | none => ExecFloat.add x y

theorem add_spec (x y : Binary32) : add x y = ExecFloat.Spec.add x y := by
  unfold add
  split
  · rename_i w hw
    exact DWordNaN.selected_add x y w hw
  · exact ExecFloat.Proof.add_eq_spec x y

@[inline] def mul (x y : Binary32) : Binary32 :=
  match DWordNaN.rawChoose x.raw.1 y.raw.1 with
  | some w => FastMul.ofBits w
  | none => FastMul.mul x y

theorem mul_spec (x y : Binary32) : mul x y = ExecFloat.Spec.mul x y := by
  unfold mul
  split
  · rename_i w hw
    exact DWordNaN.selected_mul x y w hw
  · exact FastMul.mul_spec x y

end ScalarNaN

/- R12 None-result reuse. Local classifier proofs copy the accepted R7W05
proof bodies under fresh names; the original declarations and all their
comments remain in their original positions. New integration is NOT_RUN. -/
namespace NoneNativeProof

open FloatLib.Floats Competition
open FloatLib.Floats.Formats.BinaryInterchange

open Float.Model.UnpackedFloat

theorem none_model_toModel_isNaN (x : Model FloatFormat.binary32) :


    (Model.toModel x).isNaN = Model.isNaN x := by


  have he : unpackExponent (Model.toModelBits x) = -1#(FloatFormat.binary32.toModel.exponentBits) ↔


      Model.expField x = FloatFormat.binary32.expAllOnesNat := by


    rw [← BitVec.toNat_inj, Model.unpackExponent_toNat,


      Model.toNat_neg_one_exponentBits]


  have hm : unpackMantissa (Model.toModelBits x) = 0#(FloatFormat.binary32.toModel.mantissaBitsWithoutImplicit) ↔


      Model.fracField x = 0 := by


    rw [← BitVec.toNat_inj, Model.unpackMantissa_toNat]


    rfl


  change (Model.toModel x).isNaN = Model.IEEE.isNaN x


  unfold Model.toModel unpack


  dsimp only


  split_ifs <;>


    simp_all [Float.Model.UnpackedFloat.isNaN, Model.IEEE.isNaN]

theorem none_toFloat32_isNaN (x : Binary32) :


    (ExecFloat.Binary.toFloat32 x).isNaN = Model.isNaN (ExecFloat.Binary.toModel x) := by


  change ((Model.toFloat32Model (ExecFloat.Binary.toModel x)).unpack).isNaN = _


  rw [Model.unpack_toFloat32Model]


  exact none_model_toModel_isNaN _

theorem raw_none_model (x y : Binary32)
    (hnone : DWordNaN.rawChoose x.raw.1 y.raw.1 = none) :
    Model.chooseNaN2 (Model.NativeBinary32.ofUInt32 x.raw.1)
      (Model.NativeBinary32.ofUInt32 y.raw.1) = none := by
  rw [← DWordNaN.rawChoose_eq, hnone]
  rfl

theorem raw_none_native_inputs (x y : Binary32)
    (hnone : DWordNaN.rawChoose x.raw.1 y.raw.1 = none) :
    (ExecFloat.Binary.toFloat32 x).isNaN = false ∧
      (ExecFloat.Binary.toFloat32 y).isNaN = false := by
  have hm := (Model.chooseNaN2_eq_none_iff
    (Model.NativeBinary32.ofUInt32 x.raw.1)
    (Model.NativeBinary32.ofUInt32 y.raw.1)).mp (raw_none_model x y hnone)
  constructor
  · rw [none_toFloat32_isNaN, R7W02.exec_toModel_eq_rawModel]
    exact hm.1
  · rw [none_toFloat32_isNaN, R7W02.exec_toModel_eq_rawModel]
    exact hm.2

theorem native_add_spec_of_none (x y : Binary32)
    (hnone : DWordNaN.rawChoose x.raw.1 y.raw.1 = none) :
    ExecFloat.Binary.ofFloat32
      (ExecFloat.Binary.toFloat32 x + ExecFloat.Binary.toFloat32 y) =
        ExecFloat.Spec.add x y := by
  have hn := raw_none_native_inputs x y hnone
  rw [R7Native.ofFloat32Add _ _ hn.1 hn.2,
    NotNaNProbe.roundtrip x hn.1, NotNaNProbe.roundtrip y hn.2]
  exact ExecFloat.Proof.add_eq_spec x y

theorem native_mul_spec_of_none (x y : Binary32)
    (hnone : DWordNaN.rawChoose x.raw.1 y.raw.1 = none) :
    ExecFloat.Binary.ofFloat32
      (ExecFloat.Binary.toFloat32 x * ExecFloat.Binary.toFloat32 y) =
        ExecFloat.Spec.mul x y := by
  have hn := raw_none_native_inputs x y hnone
  rw [R7Native.ofFloat32Mul _ _ hn.1 hn.2,
    NotNaNProbe.roundtrip x hn.1, NotNaNProbe.roundtrip y hn.2]
  exact ExecFloat.Proof.mul_eq_spec x y

@[inline] def addColdResult (x y : Binary32) (result : Float32) : Binary32 :=
  match DWordNaN.rawChoose x.raw.1 y.raw.1 with
  | some w => FastMul.ofBits w
  | none => ExecFloat.Binary.ofFloat32 result

theorem addColdResult_spec (x y : Binary32) (result : Float32)
    (hr : result = R2W01b.convert x.raw.1 + R2W01b.convert y.raw.1) :
    addColdResult x y result = ExecFloat.Spec.add x y := by
  unfold addColdResult
  split
  · rename_i w hw
    exact DWordNaN.selected_add x y w hw
  · rename_i hw
    rw [hr, R2W01c.convert_eq, R2W01c.convert_eq]
    change ExecFloat.Binary.ofFloat32
      (ExecFloat.Binary.toFloat32 x + ExecFloat.Binary.toFloat32 y) = _
    exact native_add_spec_of_none x y hw

@[inline] def mulColdResult (x y : Binary32) (result : Float32) : Binary32 :=
  match DWordNaN.rawChoose x.raw.1 y.raw.1 with
  | some w => FastMul.ofBits w
  | none => ExecFloat.Binary.ofFloat32 result

theorem mulColdResult_spec (x y : Binary32) (result : Float32)
    (hr : result = R2W01b.convert x.raw.1 * R2W01b.convert y.raw.1) :
    mulColdResult x y result = ExecFloat.Spec.mul x y := by
  unfold mulColdResult
  split
  · rename_i w hw
    exact DWordNaN.selected_mul x y w hw
  · rename_i hw
    rw [hr, R2W01c.convert_eq, R2W01c.convert_eq]
    change ExecFloat.Binary.ofFloat32
      (ExecFloat.Binary.toFloat32 x * ExecFloat.Binary.toFloat32 y) = _
    exact native_mul_spec_of_none x y hw

end NoneNativeProof



/-- Classify the native result; raw NaN inputs/results retain exact fallback. -/
@[inline] def add (x y : Binary32) : Binary32 :=
  let result := R2W01b.convert x.raw.1 + R2W01b.convert y.raw.1
  if hn : R7W04.nonNaN result = true then ExecFloat.Binary.ofFloat32 result
  else NoneNativeProof.addColdResult x y result

theorem add_spec : ∀ x y : Binary32, add x y = ExecFloat.Spec.add x y := by
  intro x y
  unfold add
  dsimp only
  split
  · rename_i hn
    rw [R2W01c.convert_eq, R2W01c.convert_eq] at hn ⊢
    change R7W04.nonNaN (ExecFloat.Binary.toFloat32 x + ExecFloat.Binary.toFloat32 y) = true at hn
    have hi := NotNaNProbe.add_inputs _ _ ((R7W04.nonNaN_eq_true_iff _).mp hn)
    change ExecFloat.Binary.ofFloat32 (ExecFloat.Binary.toFloat32 x + ExecFloat.Binary.toFloat32 y) = _
    rw [R7Native.ofFloat32Add _ _ hi.1 hi.2,
      NotNaNProbe.roundtrip x hi.1, NotNaNProbe.roundtrip y hi.2]
    exact ExecFloat.Proof.add_eq_spec x y
  · exact NoneNativeProof.addColdResult_spec x y _ rfl

/-- Only a native NaN result requires the original raw-word fallback. -/
@[inline] def nativeMul (x y : Binary32) : Binary32 :=
  let result := R2W01b.convert x.raw.1 * R2W01b.convert y.raw.1
  if hn : R7W04.nonNaN result = true then ExecFloat.Binary.ofFloat32 result
  else NoneNativeProof.mulColdResult x y result

theorem nativeMul_spec : ∀ x y : Binary32, nativeMul x y = ExecFloat.Spec.mul x y := by
  intro x y
  unfold nativeMul
  dsimp only
  split
  · rename_i hn
    rw [R2W01c.convert_eq, R2W01c.convert_eq] at hn ⊢
    change R7W04.nonNaN (ExecFloat.Binary.toFloat32 x * ExecFloat.Binary.toFloat32 y) = true at hn
    have hi := NotNaNProbe.mul_inputs _ _ ((R7W04.nonNaN_eq_true_iff _).mp hn)
    change ExecFloat.Binary.ofFloat32 (ExecFloat.Binary.toFloat32 x * ExecFloat.Binary.toFloat32 y) = _
    rw [R7Native.ofFloat32Mul _ _ hi.1 hi.2,
      NotNaNProbe.roundtrip x hi.1, NotNaNProbe.roundtrip y hi.2]
    exact ExecFloat.Proof.mul_eq_spec x y
  · exact NoneNativeProof.mulColdResult_spec x y _ rfl

@[inline] def mul (x y : Binary32) : Binary32 :=
  let ex := FloatLib.Floats.Formats.BinaryInterchange.Model.NativeBinary32.expField x.raw.1
  let ey := FloatLib.Floats.Formats.BinaryInterchange.Model.NativeBinary32.expField y.raw.1
  if ex + ey < (128 : UInt32) then LowScale.mul x y else nativeMul x y

theorem mul_spec (x y : Binary32) : mul x y = ExecFloat.Spec.mul x y := by
  unfold mul
  dsimp only
  split
  · exact LowScale.mul_spec x y
  · exact nativeMul_spec x y

/-- `add` and `mul` are FloatLib's executable operations, whatever they compute internally. -/
theorem add_eq : add = ExecFloat.add := by
  funext x y
  rw [add_spec, ExecFloat.Proof.add_eq_spec]

theorem mul_eq : mul = ExecFloat.mul := by
  funext x y
  rw [mul_spec, ExecFloat.Proof.mul_eq_spec]

/-- TorchLean's sum: the elements left to right, from +0, with `add`. -/
def referenceSum {n : Nat} (x : Vector Binary32 n) : Binary32 := x.foldl add posZero

theorem referenceSum_spec : ∀ (n : Nat) (x : Vector Binary32 n), referenceSum x = sumSpec x.get := by
  intro n x
  conv_lhs => rw [referenceSum, add_eq, ← Vector.ofFn_getElem (xs := x)]
  rw [← Vector.foldl_toList, Vector.toList_ofFn, List.ofFn_eq_map, List.foldl_map]
  rfl

/-- TorchLean's batched matmul: each output a left fold over `k` of `add acc (mul a b)`. -/
def referenceBmm (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
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

theorem referenceBmm_spec : ∀ (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)),
    (referenceBmm batch m n p A B).get = bmmSpec batch m n p A.get B.get := by
  intro batch m n p A B
  funext q
  simp only [referenceBmm, add_eq, mul_eq, Vector.get, Vector.toArray_ofFn, Array.getElem_ofFn,
    Fin.foldl_eq_finRange_foldl, toArray_getD]
  rfl


namespace FinalFinite

/- These lemmas expose the finite-result preimage of native binary32 operations.
   They use Lean 4.34's actual packed model; derived from the actual arithmetic definitions.
   Source definitions: Lean FRO / Apache-2.0, Float.Model.UnpackedFloat.add/mul.
   Proofs below are new, candidate-local proofs. -/

theorem packNaN_notFinite :
    (Float32.Model.pack Float.Model.UnpackedFloat.notANumber).isFinite = false := by
  decide

theorem packInfinity_notFinite (sign : Float.Model.UnpackedFloat.Sign) :
    (Float32.Model.pack (Float.Model.UnpackedFloat.infinity sign)).isFinite = false := by
  cases sign <;> decide

/-- A native finite sum has finite operands, including either sign of zero. -/
theorem add_finite_inputs (x y : Float32) (h : (x + y).isFinite = true) :
    x.isFinite = true ∧ y.isFinite = true := by
  change (Float32.Model.pack
    (Float.Model.UnpackedFloat.add Float.Model.Format.binary32
      x.toModel.unpack y.toModel.unpack)).isFinite = true at h
  change x.toModel.unpack.isFinite = true ∧ y.toModel.unpack.isFinite = true
  cases hx : x.toModel.unpack <;> cases hy : y.toModel.unpack <;>
    simp_all [Float.Model.UnpackedFloat.add, Float.Model.UnpackedFloat.isFinite,
      packNaN_notFinite, packInfinity_notFinite]
  all_goals split at h <;> simp_all [packNaN_notFinite, packInfinity_notFinite]

/-- A native finite product has finite factors; infinity times zero is excluded. -/
theorem mul_finite_inputs (x y : Float32) (h : (x * y).isFinite = true) :
    x.isFinite = true ∧ y.isFinite = true := by
  change (Float32.Model.pack
    (Float.Model.UnpackedFloat.mul Float.Model.Format.binary32
      x.toModel.unpack y.toModel.unpack)).isFinite = true at h
  change x.toModel.unpack.isFinite = true ∧ y.toModel.unpack.isFinite = true
  cases hx : x.toModel.unpack <;> cases hy : y.toModel.unpack <;>
    simp_all [Float.Model.UnpackedFloat.mul, Float.Model.UnpackedFloat.isFinite,
      packNaN_notFinite, packInfinity_notFinite]

end FinalFinite






/- Append after the concrete Dependencies.lean under the sole ContractTensor dependency.
   This section closes every real binary32 Model.Spec.add branch. -/
namespace R7W03
open FloatLib.Floats.Formats.BinaryInterchange
open FloatLib.Floats.Formats.BinaryInterchange.Model

private theorem chooseNaN2_none_not_snan
    (x y : Model FloatFormat.binary32) (h : chooseNaN2 x y = none) :
    isSNaN x = false ∧ isSNaN y = false := by
  have hn := (chooseNaN2_eq_none_iff x y).mp h
  exact ⟨isSNaN_eq_false_of_isNaN_eq_false x hn.1,
    isSNaN_eq_false_of_isNaN_eq_false y hn.2⟩

/-- The actual binary32 addition specification never emits a signaling NaN.
No finite, normal, non-NaN, sign, or payload assumption is made. -/
theorem model_add_not_snan (x y : Model FloatFormat.binary32) :
    isSNaN (Spec.add x y) = false := by
  unfold Spec.add
  split
  · exact R7W01.roundDyadic32_not_snan _
  · split
    · rename_i n hn
      exact R7W01.chooseNaN2_32_not_snan x y n hn
    · rename_i hnone
      have hxy := chooseNaN2_none_not_snan x y hnone
      split
      · split
        · split
          · exact hxy.1
          · exact R7W01.invalidResult32_not_snan
        · exact hxy.1
      · split
        · exact hxy.2
        · exact R7W01.invalidResult32_not_snan

/-- Every NaN arithmetic-add result is already quiet. -/
theorem model_add_isQNaN_eq_isNaN (x y : Model FloatFormat.binary32) :
    isQNaN (Spec.add x y) = isNaN (Spec.add x y) := by
  rw [isQNaN_eq_nan_and_not_signaling, model_add_not_snan]
  simp

/-- A right signaling NaN takes precedence whenever the left word is non-signaling.
The result is the actual right word quieted, with its complete sign and payload. -/
theorem model_add_of_right_snan (x y : Model FloatFormat.binary32)
    (hx : isSNaN x = false) (hy : isSNaN y = true) :
    Spec.add x y = quietNaN y := by
  have hny : isNaN y = true := isNaN_of_isSNaN hy
  have hdy : toDyadic? y = none := toDyadic?_eq_none_of_isNaN hny
  have hc : chooseNaN2 x y = some (quietNaN y) := by
    simp [chooseNaN2, hx, hy]
  cases hdx : toDyadic? x <;> simp [Spec.add, hdx, hdy, hc]

/-- The right-signaling branch concretely establishes the quiet invariant. -/
theorem model_add_of_right_snan_isQNaN (x y : Model FloatFormat.binary32)
    (hx : isSNaN x = false) (hy : isSNaN y = true) :
    isQNaN (Spec.add x y) = true := by
  rw [model_add_of_right_snan x y hx hy]
  exact R7W01.quietNaN32_is_qnan y (isNaN_of_isSNaN hy)

/-- Explicit stored-word version of the exact result, with no quotient of NaNs. -/
theorem model_add_of_right_snan_bits (x y : Model FloatFormat.binary32)
    (hx : isSNaN x = false) (hy : isSNaN y = true) :
    (Spec.add x y).bits = (quietNaN y).bits := by
  rw [model_add_of_right_snan x y hx hy]

end R7W03

/- Append after Dependencies.lean and ModelAdd.lean under only dependency ContractTensor.
   No quiet initial accumulator is required: ordinary +0 is concretely non-signaling. -/
namespace R7W03
open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange

/-- Exact transport of the actual addition's non-signaling output property. -/
theorem exec_add_not_snan (x y : Competition.Binary32) :
    Model.isSNaN (ExecFloat.Binary.toModel (ExecFloat.add x y)) = false := by
  exact (congrArg (fun m : Model FloatFormat.binary32 => Model.isSNaN m)
    (Submission.R7Native.toModelExecAdd x y)).trans
      (model_add_not_snan (ExecFloat.Binary.toModel x) (ExecFloat.Binary.toModel y))


end R7W03

namespace R7W05


open FloatLib.Floats Competition


open FloatLib.Floats.Formats.BinaryInterchange


open Float.Model.UnpackedFloat





/-- The actual raw binary32 NaN classifier agrees exactly with Lean's unpacked model. -/


theorem model_toModel_isNaN (x : Model FloatFormat.binary32) :


    (Model.toModel x).isNaN = Model.isNaN x := by


  have he : unpackExponent (Model.toModelBits x) = -1#(FloatFormat.binary32.toModel.exponentBits) ↔


      Model.expField x = FloatFormat.binary32.expAllOnesNat := by


    rw [← BitVec.toNat_inj, Model.unpackExponent_toNat,


      Model.toNat_neg_one_exponentBits]


  have hm : unpackMantissa (Model.toModelBits x) = 0#(FloatFormat.binary32.toModel.mantissaBitsWithoutImplicit) ↔


      Model.fracField x = 0 := by


    rw [← BitVec.toNat_inj, Model.unpackMantissa_toNat]


    rfl


  change (Model.toModel x).isNaN = Model.IEEE.isNaN x


  unfold Model.toModel unpack


  dsimp only


  split_ifs <;>


    simp_all [Float.Model.UnpackedFloat.isNaN, Model.IEEE.isNaN]





/-- Exact classifier transport for every real competition carrier, including all NaN words. -/


theorem toFloat32_isNaN (x : Binary32) :


    (ExecFloat.Binary.toFloat32 x).isNaN = Model.isNaN (ExecFloat.Binary.toModel x) := by


  change ((Model.toFloat32Model (ExecFloat.Binary.toModel x)).unpack).isNaN = _


  rw [Model.unpack_toFloat32Model]


  exact model_toModel_isNaN _





/-- In Lean's actual canonical Float32 model, a NaN is propositionally equal to native NaN. -/


theorem native_eq_nan_of_isNaN (x : Float32) (hx : x.isNaN = true) :


    x = Float32.nan := by


  have hunpack : x.toModel.unpack = .notANumber := by


    change x.toModel.unpack.isNaN = true at hx


    cases h : x.toModel.unpack <;> simp_all [Float.Model.UnpackedFloat.isNaN]


  cases x with


  | ofModel m =>


      apply congrArg Float32.ofModel


      change m = Float32.Model.pack .notANumber


      have hr := Model.toFloat32Model_ofFloat32Model m


      change Float32.Model.pack m.unpack = m at hr


      change m.unpack = .notANumber at hunpack


      rw [← hr, hunpack]





/-- Raw NaN metadata is erased only by this explicit native conversion boundary. -/


theorem toFloat32_eq_nan_of_model_nan (x : Binary32)


    (hx : Model.isNaN (ExecFloat.Binary.toModel x) = true) :


    ExecFloat.Binary.toFloat32 x = Float32.nan := by


  apply native_eq_nan_of_isNaN


  rw [toFloat32_isNaN]


  exact hx





/-- Every actual binary32 NaN selection returns a NaN, with quieting proved concretely. -/


theorem chooseNaN2_some_nan (x y z : Model FloatFormat.binary32)


    (h : Model.chooseNaN2 x y = some z) : Model.isNaN z = true := by


  unfold Model.chooseNaN2 at h


  split_ifs at h with hsx hsy hnx hny


  · simp only [Option.some.injEq] at h


    cases h


    exact R7W01.quietNaN32_is_nan x (Model.isNaN_of_isSNaN hsx)


  · simp only [Option.some.injEq] at h


    cases h


    exact R7W01.quietNaN32_is_nan y (Model.isNaN_of_isSNaN hsy)


  · simp only [Option.some.injEq] at h


    cases h


    exact R7W01.quietNaN32_is_nan x hnx


  · simp only [Option.some.injEq] at h


    cases h


    exact R7W01.quietNaN32_is_nan y hny





/-- A real left NaN produces a real NaN under the public addition specification. -/


theorem model_add_nan_left (x y : Model FloatFormat.binary32)


    (hx : Model.isNaN x = true) : Model.isNaN (Model.Spec.add x y) = true := by


  have hd := Model.toDyadic?_eq_none_of_isNaN hx


  cases hc : Model.chooseNaN2 x y with


  | none =>


      have hn := (Model.chooseNaN2_eq_none_iff x y).mp hc


      simp [hx] at hn


  | some z =>


      have hout : Model.Spec.add x y = z := by


        cases hdy : Model.toDyadic? y <;> simp [Model.Spec.add, hd, hdy, hc]


      rw [hout]


      exact chooseNaN2_some_nan x y z hc





/-- A real right NaN produces a real NaN, irrespective of left NaN precedence. -/


theorem model_add_nan_right (x y : Model FloatFormat.binary32)


    (hy : Model.isNaN y = true) : Model.isNaN (Model.Spec.add x y) = true := by


  have hd := Model.toDyadic?_eq_none_of_isNaN hy


  cases hc : Model.chooseNaN2 x y with


  | none =>


      have hn := (Model.chooseNaN2_eq_none_iff x y).mp hc


      simp [hy] at hn


  | some z =>


      have hout : Model.Spec.add x y = z := by


        cases hdx : Model.toDyadic? x <;> simp [Model.Spec.add, hd, hdx, hc]


      rw [hout]


      exact chooseNaN2_some_nan x y z hc





/-- Actual native addition propagates a left NaN to its canonical native NaN. -/


theorem native_add_nan_left (x y : Float32) (hx : x.isNaN = true) :


    x + y = Float32.nan := by


  apply native_eq_nan_of_isNaN


  cases h : (x + y).isNaN with


  | true => rfl


  | false =>


      have hn := Submission.NotNaNProbe.add_inputs x y h


      simp [hx] at hn





/-- Actual native addition propagates a right NaN to its canonical native NaN. -/


theorem native_add_nan_right (x y : Float32) (hy : y.isNaN = true) :


    x + y = Float32.nan := by


  apply native_eq_nan_of_isNaN


  cases h : (x + y).isNaN with


  | true => rfl


  | false =>


      have hn := Submission.NotNaNProbe.add_inputs x y h


      simp [hy] at hn





/-- ALL INPUTS: canonical native conversion commutes with the actual binary32 add.


This includes arbitrary signaling/quiet NaN signs and payloads. The equality is


of native Float32 values, not an assertion that canonical conversion retains raw NaN metadata. -/


theorem add_toFloat32 (x y : Binary32) :


    ExecFloat.Binary.toFloat32 (ExecFloat.add x y) =


      ExecFloat.Binary.toFloat32 x + ExecFloat.Binary.toFloat32 y := by


  cases hx : (ExecFloat.Binary.toFloat32 x).isNaN with


  | false =>


      cases hy : (ExecFloat.Binary.toFloat32 y).isNaN with


      | false =>


          have h := Submission.R7Native.ofFloat32Add


            (ExecFloat.Binary.toFloat32 x) (ExecFloat.Binary.toFloat32 y) hx hy


          rw [Submission.NotNaNProbe.roundtrip x hx,


            Submission.NotNaNProbe.roundtrip y hy] at h


          have hp := congrArg ExecFloat.Binary.toFloat32 h


          simpa only [ExecFloat.Binary.toFloat32_ofFloat32] using hp.symm


      | true =>


          have hmy : Model.isNaN (ExecFloat.Binary.toModel y) = true := by


            rw [← toFloat32_isNaN]


            exact hy


          have hz : Model.isNaN (ExecFloat.Binary.toModel (ExecFloat.add x y)) = true := by


            rw [Submission.R7Native.toModelExecAdd]


            exact model_add_nan_right _ _ hmy


          rw [toFloat32_eq_nan_of_model_nan _ hz,


            native_add_nan_right _ _ hy]


  | true =>


      have hmx : Model.isNaN (ExecFloat.Binary.toModel x) = true := by


        rw [← toFloat32_isNaN]


        exact hx


      have hz : Model.isNaN (ExecFloat.Binary.toModel (ExecFloat.add x y)) = true := by


        rw [Submission.R7Native.toModelExecAdd]


        exact model_add_nan_left _ _ hmx


      rw [toFloat32_eq_nan_of_model_nan _ hz,


        native_add_nan_left _ _ hx]





end R7W05











/- Append after the concretely proved Add.lean. These are exact Bool equalities,


   so they transport both the NaN event and its absence in either direction. -/


namespace R7W05


open FloatLib.Floats


open FloatLib.Floats.Formats.BinaryInterchange





/-- Actual raw-result NaN classifier equals the native sum-result classifier on all inputs. -/


theorem add_isNaN_eq_native (x y : Competition.Binary32) :


    ExecFloat.Binary.isNaN (ExecFloat.add x y) =


      (ExecFloat.Binary.toFloat32 x + ExecFloat.Binary.toFloat32 y).isNaN := by


  change Model.isNaN (ExecFloat.Binary.toModel (ExecFloat.add x y)) = _


  rw [← toFloat32_isNaN, add_toFloat32]





/-- The same classifier equality written on the actual model of the executable result. -/


theorem add_model_isNaN_eq_native (x y : Competition.Binary32) :


    Model.isNaN (ExecFloat.Binary.toModel (ExecFloat.add x y)) =


      (ExecFloat.Binary.toFloat32 x + ExecFloat.Binary.toFloat32 y).isNaN :=


  add_isNaN_eq_native x y





/-- The concrete Model.Spec.add classification, without an assumed execution/model bridge. -/


theorem add_spec_isNaN_eq_native (x y : Competition.Binary32) :


    Model.isNaN (Model.Spec.add (ExecFloat.Binary.toModel x) (ExecFloat.Binary.toModel y)) =


      (ExecFloat.Binary.toFloat32 x + ExecFloat.Binary.toFloat32 y).isNaN := by


  rw [← Submission.R7Native.toModelExecAdd]


  exact add_model_isNaN_eq_native x y





/-- A native sum NaN event is equivalent to an actual raw add-result NaN. -/


theorem add_isNaN_true_iff (x y : Competition.Binary32) :


    ExecFloat.Binary.isNaN (ExecFloat.add x y) = true ↔


      (ExecFloat.Binary.toFloat32 x + ExecFloat.Binary.toFloat32 y).isNaN = true := by


  rw [add_isNaN_eq_native]





/-- A native non-NaN result is equivalent to an actual raw add-result non-NaN. -/


theorem add_isNaN_false_iff (x y : Competition.Binary32) :


    ExecFloat.Binary.isNaN (ExecFloat.add x y) = false ↔


      (ExecFloat.Binary.toFloat32 x + ExecFloat.Binary.toFloat32 y).isNaN = false := by


  rw [add_isNaN_eq_native]





end R7W05








/- All-input canonical native multiplication bridge.


Append after Dependencies.lean and Add.lean under the sole ContractTensor dependency. -/


namespace R7W05


open FloatLib.Floats


open FloatLib.Floats.Formats.BinaryInterchange





private theorem mul_unpack_of_isNaN (x : Float32) (hx : x.isNaN = true) :


    x.toModel.unpack = Float.Model.UnpackedFloat.notANumber := by


  change x.toModel.unpack.isNaN = true at hx


  cases h : x.toModel.unpack <;>


    simp_all [Float.Model.UnpackedFloat.isNaN]





/-- Native-model multiplication maps any left NaN to the canonical native NaN. -/


theorem native_mul_nan_left (x y : Float32) (hx : x.isNaN = true) :


    x * y = Float32.nan := by


  change Float32.ofModel (Float32.Model.pack


    (Float.Model.UnpackedFloat.mul Float.Model.Format.binary32


      x.toModel.unpack y.toModel.unpack)) = Float32.nan


  rw [mul_unpack_of_isNaN x hx]


  rfl





/-- Native-model multiplication maps any right NaN to the canonical native NaN. -/


theorem native_mul_nan_right (x y : Float32) (hy : y.isNaN = true) :


    x * y = Float32.nan := by


  change Float32.ofModel (Float32.Model.pack


    (Float.Model.UnpackedFloat.mul Float.Model.Format.binary32


      x.toModel.unpack y.toModel.unpack)) = Float32.nan


  rw [mul_unpack_of_isNaN y hy]


  cases x.toModel.unpack <;> rfl





/-- Public non-NaN-input bridge projected to canonical native values.


The public finite proof includes one exact-product rounding; infinities and invalid


zero-times-infinity cases are covered by the public R7Native extension. -/


theorem mul_toFloat32_of_not_nan (x y : Competition.Binary32)


    (hx : (ExecFloat.Binary.toFloat32 x).isNaN = false)


    (hy : (ExecFloat.Binary.toFloat32 y).isNaN = false) :


    ExecFloat.Binary.toFloat32 (ExecFloat.mul x y) =


      ExecFloat.Binary.toFloat32 x * ExecFloat.Binary.toFloat32 y := by


  have h := Submission.R7Native.ofFloat32Mul


    (ExecFloat.Binary.toFloat32 x) (ExecFloat.Binary.toFloat32 y) hx hy


  rw [Submission.NotNaNProbe.roundtrip x hx,


    Submission.NotNaNProbe.roundtrip y hy] at h


  have hn := congrArg (fun v : Competition.Binary32 => ExecFloat.Binary.toFloat32 v) h.symm


  simpa only [ExecFloat.Binary.toFloat32_ofFloat32] using hn





/-- A left NaN makes actual Model.Spec.mul return a NaN. Its selected metadata


is retained by the raw model; only the later native conversion canonicalizes it. -/


theorem model_mul_nan_left (x y : Model FloatFormat.binary32)


    (hx : Model.isNaN x = true) : Model.isNaN (Model.Spec.mul x y) = true := by


  have hdx := Model.toDyadic?_eq_none_of_isNaN hx


  cases hchoose : Model.chooseNaN2 x y with


  | none =>


      have hnot := ((Model.chooseNaN2_eq_none_iff x y).mp hchoose).1


      simp [hx] at hnot


  | some z =>


      have hz := chooseNaN2_some_nan x y z hchoose


      cases hd : Model.toDyadic? y <;>


        simpa only [Model.Spec.mul, hdx, hd, hchoose] using hz





/-- The corresponding right NaN classification for actual Model.Spec.mul. -/


theorem model_mul_nan_right (x y : Model FloatFormat.binary32)


    (hy : Model.isNaN y = true) : Model.isNaN (Model.Spec.mul x y) = true := by


  have hdy := Model.toDyadic?_eq_none_of_isNaN hy


  cases hchoose : Model.chooseNaN2 x y with


  | none =>


      have hnot := ((Model.chooseNaN2_eq_none_iff x y).mp hchoose).2


      simp [hy] at hnot


  | some z =>


      have hz := chooseNaN2_some_nan x y z hchoose


      cases hd : Model.toDyadic? x <;>


        simpa only [Model.Spec.mul, hdy, hd, hchoose] using hz





/-- All-input canonical native multiplication bridge. No finiteness, non-NaN,


or payload restrictions are imposed on the original Competition.Binary32 inputs. -/


theorem mul_toFloat32 (x y : Competition.Binary32) :


    ExecFloat.Binary.toFloat32 (ExecFloat.mul x y) =


      ExecFloat.Binary.toFloat32 x * ExecFloat.Binary.toFloat32 y := by


  cases hx : (ExecFloat.Binary.toFloat32 x).isNaN with


  | false =>


      cases hy : (ExecFloat.Binary.toFloat32 y).isNaN with


      | false => exact mul_toFloat32_of_not_nan x y hx hy


      | true =>


          rw [native_mul_nan_right _ _ hy]


          apply toFloat32_eq_nan_of_model_nan


          rw [Submission.NativeBridge.toModelExecMul]


          exact model_mul_nan_right _ _ ((toFloat32_isNaN y).symm.trans hy)


  | true =>


      rw [native_mul_nan_left _ _ hx]


      apply toFloat32_eq_nan_of_model_nan


      rw [Submission.NativeBridge.toModelExecMul]


      exact model_mul_nan_left _ _ ((toFloat32_isNaN x).symm.trans hx)





/-- Exact equality of the actual stored-result classifier and the native product classifier. -/


theorem mul_isNaN_eq_native (x y : Competition.Binary32) :


    ExecFloat.Binary.isNaN (ExecFloat.mul x y) =


      (ExecFloat.Binary.toFloat32 x * ExecFloat.Binary.toFloat32 y).isNaN := by


  change Model.isNaN (ExecFloat.Binary.toModel (ExecFloat.mul x y)) = _


  rw [← toFloat32_isNaN, mul_toFloat32]





/-- The same classifier equality written on the complete raw model value. -/


theorem mul_model_isNaN_eq_native (x y : Competition.Binary32) :


    Model.isNaN (ExecFloat.Binary.toModel (ExecFloat.mul x y)) =


      (ExecFloat.Binary.toFloat32 x * ExecFloat.Binary.toFloat32 y).isNaN :=


  mul_isNaN_eq_native x y





/-- Every native-product NaN event is exactly an actual raw multiplication NaN event. -/


theorem mul_isNaN_true_iff (x y : Competition.Binary32) :


    ExecFloat.Binary.isNaN (ExecFloat.mul x y) = true ↔


      (ExecFloat.Binary.toFloat32 x * ExecFloat.Binary.toFloat32 y).isNaN = true := by


  rw [mul_isNaN_eq_native]





/-- Every native-product non-NaN event is exactly an actual raw multiplication non-NaN event. -/


theorem mul_isNaN_false_iff (x y : Competition.Binary32) :


    ExecFloat.Binary.isNaN (ExecFloat.mul x y) = false ↔


      (ExecFloat.Binary.toFloat32 x * ExecFloat.Binary.toFloat32 y).isNaN = false := by


  rw [mul_isNaN_eq_native]





end R7W05








/- Exact repair at a native NaN transition. Append after Dependencies, Add and Mul.


   Only the prior non-NaN native accumulator is imported; original current input


   words are retained for metadata-sensitive recomputation. -/


namespace R7W05


open FloatLib.Floats


open FloatLib.Floats.Formats.BinaryInterchange





@[inline] def nativeSumStep (acc : Float32) (x : Competition.Binary32) : Float32 :=


  acc + ExecFloat.Binary.toFloat32 x





/-- Two separate original-order rounded operations; no fused operation is used. -/


@[inline] def nativeDotStep (acc : Float32) (x y : Competition.Binary32) : Float32 :=


  acc + (ExecFloat.Binary.toFloat32 x * ExecFloat.Binary.toFloat32 y)





@[inline] def repairSumStep (acc : Float32) (x : Competition.Binary32) : Competition.Binary32 :=


  ExecFloat.add (ExecFloat.Binary.ofFloat32 acc) x





@[inline] def repairDotStep (acc : Float32) (x y : Competition.Binary32) : Competition.Binary32 :=


  ExecFloat.add (ExecFloat.Binary.ofFloat32 acc) (ExecFloat.mul x y)





/-- A matching non-NaN native state reconstructs the original full carrier word.


    This includes signed zero and infinity; no finite-only restriction is imposed. -/


theorem native_acc_roundtrip (q : Competition.Binary32) (acc : Float32)


    (hmatch : ExecFloat.Binary.toFloat32 q = acc) (hacc : acc.isNaN = false) :


    ExecFloat.Binary.ofFloat32 acc = q := by


  rw [← hmatch]


  apply Submission.NotNaNProbe.roundtrip


  simpa only [hmatch] using hacc





/-- Exact canonical native result of the ordered mul-then-add reference step. -/


theorem dot_toFloat32 (q x y : Competition.Binary32) :


    ExecFloat.Binary.toFloat32 (ExecFloat.add q (ExecFloat.mul x y)) =


      nativeDotStep (ExecFloat.Binary.toFloat32 q) x y := by


  rw [add_toFloat32, mul_toFloat32]


  rfl





/-- A native sum NaN event is precisely a NaN of the full raw reference result. -/


theorem native_sum_isNaN_eq_raw (q x : Competition.Binary32) :


    (nativeSumStep (ExecFloat.Binary.toFloat32 q) x).isNaN =


      Model.isNaN (ExecFloat.Binary.toModel (ExecFloat.add q x)) := by


  exact (congrArg Float32.isNaN (add_toFloat32 q x)).symm.trans


    (toFloat32_isNaN (ExecFloat.add q x))





/-- The same exact event classification for two separately rounded dot operations. -/


theorem native_dot_isNaN_eq_raw (q x y : Competition.Binary32) :


    (nativeDotStep (ExecFloat.Binary.toFloat32 q) x y).isNaN =


      Model.isNaN (ExecFloat.Binary.toModel (ExecFloat.add q (ExecFloat.mul x y))) := by


  exact (congrArg Float32.isNaN (dot_toFloat32 q x y)).symm.trans


    (toFloat32_isNaN (ExecFloat.add q (ExecFloat.mul x y)))





/-- Metadata-exact recomputation from the prior native state and the original input. -/


theorem repairSumStep_eq_original (q : Competition.Binary32) (acc : Float32)


    (x : Competition.Binary32)


    (hmatch : ExecFloat.Binary.toFloat32 q = acc) (hacc : acc.isNaN = false) :


    repairSumStep acc x = ExecFloat.add q x := by


  unfold repairSumStep


  rw [native_acc_roundtrip q acc hmatch hacc]





/-- The product is recomputed from both original raw words before ordinary addition. -/


theorem repairDotStep_eq_original (q : Competition.Binary32) (acc : Float32)


    (x y : Competition.Binary32)


    (hmatch : ExecFloat.Binary.toFloat32 q = acc) (hacc : acc.isNaN = false) :


    repairDotStep acc x y = ExecFloat.add q (ExecFloat.mul x y) := by


  unfold repairDotStep


  rw [native_acc_roundtrip q acc hmatch hacc]





/-- Exact classification of the repair computation, independent of metadata canonicalization. -/


theorem repairSumStep_isNaN_eq (acc : Float32) (x : Competition.Binary32) :


    Model.isNaN (ExecFloat.Binary.toModel (repairSumStep acc x)) =


      (nativeSumStep acc x).isNaN := by


  have h := native_sum_isNaN_eq_raw (ExecFloat.Binary.ofFloat32 acc) x


  simpa only [ExecFloat.Binary.toFloat32_ofFloat32, repairSumStep] using h.symm





/-- Exact classification of the repaired original-order dot step. -/


theorem repairDotStep_isNaN_eq (acc : Float32) (x y : Competition.Binary32) :


    Model.isNaN (ExecFloat.Binary.toModel (repairDotStep acc x y)) =


      (nativeDotStep acc x y).isNaN := by


  have h := native_dot_isNaN_eq_raw (ExecFloat.Binary.ofFloat32 acc) x y


  simpa only [ExecFloat.Binary.toFloat32_ofFloat32, repairDotStep] using h.symm





/-- An observed native sum NaN event produces a concretely proved quiet repair result. -/


theorem repairSumStep_isQNaN (acc : Float32) (x : Competition.Binary32)


    (hevent : (nativeSumStep acc x).isNaN = true) :


    Model.isQNaN (ExecFloat.Binary.toModel (repairSumStep acc x)) = true := by


  rw [Model.isQNaN_eq_nan_and_not_signaling]


  have hn := (repairSumStep_isNaN_eq acc x).trans hevent


  have hs := Submission.R7W03.exec_add_not_snan (ExecFloat.Binary.ofFloat32 acc) x


  change Model.isSNaN (ExecFloat.Binary.toModel (repairSumStep acc x)) = false at hs


  rw [hn, hs]


  rfl





/-- The outer actual addition guarantees that a repaired dot event is quiet as well. -/


theorem repairDotStep_isQNaN (acc : Float32) (x y : Competition.Binary32)


    (hevent : (nativeDotStep acc x y).isNaN = true) :


    Model.isQNaN (ExecFloat.Binary.toModel (repairDotStep acc x y)) = true := by


  rw [Model.isQNaN_eq_nan_and_not_signaling]


  have hn := (repairDotStep_isNaN_eq acc x y).trans hevent


  have hs := Submission.R7W03.exec_add_not_snan


    (ExecFloat.Binary.ofFloat32 acc) (ExecFloat.mul x y)


  change Model.isSNaN (ExecFloat.Binary.toModel (repairDotStep acc x y)) = false at hs


  rw [hn, hs]


  rfl








end R7W05




namespace R7W12
open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange

/-- The actual native NaN imports to precisely the positive canonical quiet word. -/
theorem ofFloat32_nan_raw :
    (ExecFloat.Binary.ofFloat32 Float32.nan).raw.1 = (0x7fc00000 : UInt32) := rfl

theorem ofFloat32_nan_toModel :
    ExecFloat.Binary.toModel (ExecFloat.Binary.ofFloat32 Float32.nan) =
      Model.canonicalNaN FloatFormat.binary32 := rfl

/-- Actual classifier transport on every canonical native input. -/
theorem ofFloat32_isNaN (x : Float32) :
    Model.isNaN (ExecFloat.Binary.toModel (ExecFloat.Binary.ofFloat32 x)) = x.isNaN := by
  have h := (R7W05.toFloat32_isNaN (ExecFloat.Binary.ofFloat32 x)).symm
  simpa only [ExecFloat.Binary.toFloat32_ofFloat32] using h

/-- No actual native Float32 native constructor is signaling, including the native NaN. -/
theorem ofFloat32_not_snan (x : Float32) :
    Model.isSNaN (ExecFloat.Binary.toModel (ExecFloat.Binary.ofFloat32 x)) = false := by
  cases hx : x.isNaN with
  | false =>
      exact Model.isSNaN_eq_false_of_isNaN_eq_false _ ((ofFloat32_isNaN x).trans hx)
  | true =>
      rw [R7W05.native_eq_nan_of_isNaN x hx, ofFloat32_nan_toModel]
      decide

theorem canonicalNaN_is_nan :
    Model.isNaN (Model.canonicalNaN FloatFormat.binary32) = true := by decide

theorem canonicalNaN_not_snan :
    Model.isSNaN (Model.canonicalNaN FloatFormat.binary32) = false := by decide

theorem canonicalNaN_quiet_self :
    Model.quietNaN (Model.canonicalNaN FloatFormat.binary32) =
      Model.canonicalNaN FloatFormat.binary32 := by decide

/-- Actual binary32 invalid operations use exactly the same canonical NaN. -/
theorem invalidResult_eq_canonical :
    Model.invalidResult FloatFormat.binary32 = Model.canonicalNaN FloatFormat.binary32 := rfl

/-- The real selector keeps the canonical left NaN when the right input is not signaling. -/
theorem chooseCanonicalNaN_left (q : Model FloatFormat.binary32)
    (hs : Model.isSNaN q = false) :
    Model.chooseNaN2 (Model.canonicalNaN FloatFormat.binary32) q =
      some (Model.canonicalNaN FloatFormat.binary32) := by
  simp [Model.chooseNaN2, canonicalNaN_is_nan, canonicalNaN_not_snan,
    canonicalNaN_quiet_self, hs]

/-- A non-NaN left operand allows the actual right canonical NaN to be selected. -/
theorem chooseCanonicalNaN_right (q : Model FloatFormat.binary32)
    (hn : Model.isNaN q = false) :
    Model.chooseNaN2 q (Model.canonicalNaN FloatFormat.binary32) =
      some (Model.canonicalNaN FloatFormat.binary32) := by
  have hs := Model.isSNaN_eq_false_of_isNaN_eq_false q hn
  simp [Model.chooseNaN2, canonicalNaN_is_nan, canonicalNaN_not_snan,
    canonicalNaN_quiet_self, hs, hn]

theorem model_add_canonical_left (q : Model FloatFormat.binary32)
    (hs : Model.isSNaN q = false) :
    Model.Spec.add (Model.canonicalNaN FloatFormat.binary32) q =
      Model.canonicalNaN FloatFormat.binary32 := by
  have hd := Model.toDyadic?_eq_none_of_isNaN canonicalNaN_is_nan
  simp [Model.Spec.add, hd, chooseCanonicalNaN_left q hs]

theorem model_add_canonical_right (q : Model FloatFormat.binary32)
    (hn : Model.isNaN q = false) :
    Model.Spec.add q (Model.canonicalNaN FloatFormat.binary32) =
      Model.canonicalNaN FloatFormat.binary32 := by
  have hd := Model.toDyadic?_eq_none_of_isNaN canonicalNaN_is_nan
  cases hq : Model.toDyadic? q <;>
    simp [Model.Spec.add, hd, hq, chooseCanonicalNaN_right q hn]

theorem model_mul_canonical_left (q : Model FloatFormat.binary32)
    (hs : Model.isSNaN q = false) :
    Model.Spec.mul (Model.canonicalNaN FloatFormat.binary32) q =
      Model.canonicalNaN FloatFormat.binary32 := by
  have hd := Model.toDyadic?_eq_none_of_isNaN canonicalNaN_is_nan
  simp [Model.Spec.mul, hd, chooseCanonicalNaN_left q hs]

theorem model_mul_canonical_right (q : Model FloatFormat.binary32)
    (hn : Model.isNaN q = false) :
    Model.Spec.mul q (Model.canonicalNaN FloatFormat.binary32) =
      Model.canonicalNaN FloatFormat.binary32 := by
  have hd := Model.toDyadic?_eq_none_of_isNaN canonicalNaN_is_nan
  cases hq : Model.toDyadic? q <;>
    simp [Model.Spec.mul, hd, hq, chooseCanonicalNaN_right q hn]

/-- Canonical left NaN propagation is a full-carrier equality on imported inputs. -/
theorem exec_add_import_nan_left (x : Float32) :
    ExecFloat.add (ExecFloat.Binary.ofFloat32 Float32.nan) (ExecFloat.Binary.ofFloat32 x) =
      ExecFloat.Binary.ofFloat32 Float32.nan := by
  apply Configured.Family.toModel_injective
  change ExecFloat.Binary.toModel
    (ExecFloat.add (ExecFloat.Binary.ofFloat32 Float32.nan) (ExecFloat.Binary.ofFloat32 x)) =
      ExecFloat.Binary.toModel (ExecFloat.Binary.ofFloat32 Float32.nan)
  rw [Submission.R7Native.toModelExecAdd]
  change Model.Spec.add (Model.canonicalNaN FloatFormat.binary32)
    (ExecFloat.Binary.toModel (ExecFloat.Binary.ofFloat32 x)) =
      Model.canonicalNaN FloatFormat.binary32
  exact model_add_canonical_left _ (ofFloat32_not_snan x)

theorem exec_add_import_nan_right (x : Float32) (hx : x.isNaN = false) :
    ExecFloat.add (ExecFloat.Binary.ofFloat32 x) (ExecFloat.Binary.ofFloat32 Float32.nan) =
      ExecFloat.Binary.ofFloat32 Float32.nan := by
  apply Configured.Family.toModel_injective
  change ExecFloat.Binary.toModel
    (ExecFloat.add (ExecFloat.Binary.ofFloat32 x) (ExecFloat.Binary.ofFloat32 Float32.nan)) =
      ExecFloat.Binary.toModel (ExecFloat.Binary.ofFloat32 Float32.nan)
  rw [Submission.R7Native.toModelExecAdd]
  change Model.Spec.add (ExecFloat.Binary.toModel (ExecFloat.Binary.ofFloat32 x))
    (Model.canonicalNaN FloatFormat.binary32) = Model.canonicalNaN FloatFormat.binary32
  exact model_add_canonical_right _ ((ofFloat32_isNaN x).trans hx)

theorem exec_mul_import_nan_left (x : Float32) :
    ExecFloat.mul (ExecFloat.Binary.ofFloat32 Float32.nan) (ExecFloat.Binary.ofFloat32 x) =
      ExecFloat.Binary.ofFloat32 Float32.nan := by
  apply Configured.Family.toModel_injective
  change ExecFloat.Binary.toModel
    (ExecFloat.mul (ExecFloat.Binary.ofFloat32 Float32.nan) (ExecFloat.Binary.ofFloat32 x)) =
      ExecFloat.Binary.toModel (ExecFloat.Binary.ofFloat32 Float32.nan)
  rw [Submission.NativeBridge.toModelExecMul]
  change Model.Spec.mul (Model.canonicalNaN FloatFormat.binary32)
    (ExecFloat.Binary.toModel (ExecFloat.Binary.ofFloat32 x)) =
      Model.canonicalNaN FloatFormat.binary32
  exact model_mul_canonical_left _ (ofFloat32_not_snan x)

theorem exec_mul_import_nan_right (x : Float32) (hx : x.isNaN = false) :
    ExecFloat.mul (ExecFloat.Binary.ofFloat32 x) (ExecFloat.Binary.ofFloat32 Float32.nan) =
      ExecFloat.Binary.ofFloat32 Float32.nan := by
  apply Configured.Family.toModel_injective
  change ExecFloat.Binary.toModel
    (ExecFloat.mul (ExecFloat.Binary.ofFloat32 x) (ExecFloat.Binary.ofFloat32 Float32.nan)) =
      ExecFloat.Binary.toModel (ExecFloat.Binary.ofFloat32 Float32.nan)
  rw [Submission.NativeBridge.toModelExecMul]
  change Model.Spec.mul (ExecFloat.Binary.toModel (ExecFloat.Binary.ofFloat32 x))
    (Model.canonicalNaN FloatFormat.binary32) = Model.canonicalNaN FloatFormat.binary32
  exact model_mul_canonical_right _ ((ofFloat32_isNaN x).trans hx)

/-- ALL native inputs: the actual native native constructor is closed under ordinary addition. -/
theorem ofFloat32_add (a b : Float32) :
    ExecFloat.Binary.ofFloat32 (a + b) =
      ExecFloat.add (ExecFloat.Binary.ofFloat32 a) (ExecFloat.Binary.ofFloat32 b) := by
  cases ha : a.isNaN with
  | false =>
      cases hb : b.isNaN with
      | false => exact Submission.R7Native.ofFloat32Add a b ha hb
      | true =>
          rw [R7W05.native_add_nan_right a b hb, R7W05.native_eq_nan_of_isNaN b hb]
          exact (exec_add_import_nan_right a ha).symm
  | true =>
      rw [R7W05.native_add_nan_left a b ha, R7W05.native_eq_nan_of_isNaN a ha]
      exact (exec_add_import_nan_left b).symm

/-- ALL native inputs: multiplication is separate and preserves the canonical image. -/
theorem ofFloat32_mul (a b : Float32) :
    ExecFloat.Binary.ofFloat32 (a * b) =
      ExecFloat.mul (ExecFloat.Binary.ofFloat32 a) (ExecFloat.Binary.ofFloat32 b) := by
  cases ha : a.isNaN with
  | false =>
      cases hb : b.isNaN with
      | false => exact Submission.R7Native.ofFloat32Mul a b ha hb
      | true =>
          rw [R7W05.native_mul_nan_right a b hb, R7W05.native_eq_nan_of_isNaN b hb]
          exact (exec_mul_import_nan_right a ha).symm
  | true =>
      rw [R7W05.native_mul_nan_left a b ha, R7W05.native_eq_nan_of_isNaN a ha]
      exact (exec_mul_import_nan_left b).symm

/-- Requested execution-to-native constructor orientation, with no non-NaN premise. -/
theorem add_ofFloat32 (a b : Float32) :
    ExecFloat.add (ExecFloat.Binary.ofFloat32 a) (ExecFloat.Binary.ofFloat32 b) =
      ExecFloat.Binary.ofFloat32 (a + b) := (ofFloat32_add a b).symm

theorem mul_ofFloat32 (a b : Float32) :
    ExecFloat.mul (ExecFloat.Binary.ofFloat32 a) (ExecFloat.Binary.ofFloat32 b) =
      ExecFloat.Binary.ofFloat32 (a * b) := (ofFloat32_mul a b).symm

end R7W12
namespace R7W12
open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange

/-- Unsigned magnitude at most the positive-infinity word: every non-NaN,
including both infinities. This reads the original raw word without a codec. -/
def rawNotNaN (u : UInt32) : Bool :=
  decide ((u &&& 0x7fffffff) ≤ (0x7f800000 : UInt32))

/-- The exact exponent/fraction decomposition of the magnitude test. -/
theorem magnitude_le_infinity_iff (n : Nat) :
    n % 2147483648 ≤ 2139095040 ↔
      (n / 8388608) % 256 ≠ 255 ∨ n % 8388608 = 0 := by
  omega

/-- All raw32 words: the integer guard is exactly the real model non-NaN classifier. -/
theorem rawNotNaN_true_iff_isNaN_false (u : UInt32) :
    rawNotNaN u = true ↔
      Model.isNaN (Model.NativeBinary32.ofUInt32 u) = false := by
  unfold rawNotNaN
  rw [decide_eq_true_eq, UInt32.le_iff_toNat_le]
  change (u.toNat &&& 2147483647 ≤ 2139095040) ↔
    (((((u.toBitVec >>> 23) &&& (255#32)).toNat == 255) &&
      ((u.toBitVec &&& (8388607#32)).toNat != 0)) = false)
  simp only [BitVec.toNat_and, BitVec.toNat_ushiftRight,
    BitVec.toNat_ofNat, UInt32.toNat_toBitVec]
  change (u.toNat &&& 2147483647 ≤ 2139095040) ↔
    ((((u.toNat >>> 23) &&& 255) == 255 &&
      (u.toNat &&& 8388607) != 0) = false)
  have h31 : u.toNat &&& 2147483647 = u.toNat % 2147483648 :=
    Nat.and_two_pow_sub_one_eq_mod u.toNat 31
  have h23 : u.toNat &&& 8388607 = u.toNat % 8388608 :=
    Nat.and_two_pow_sub_one_eq_mod u.toNat 23
  have h8 : (u.toNat >>> 23) &&& 255 = (u.toNat >>> 23) % 256 :=
    Nat.and_two_pow_sub_one_eq_mod (u.toNat >>> 23) 8
  rw [h31, h23, h8, Nat.shiftRight_eq_div_pow]
  simp only [Bool.and_eq_false_iff, beq_eq_false_iff_ne, bne_eq_false_iff_eq]
  exact magnitude_le_infinity_iff u.toNat

/-- Boolean equality, retaining soundness and completeness on every original word. -/
theorem rawNotNaN_eq_not_isNaN (u : UInt32) :
    rawNotNaN u = !Model.isNaN (Model.NativeBinary32.ofUInt32 u) := by
  apply Bool.eq_iff_iff.mpr
  simpa using rawNotNaN_true_iff_isNaN_false u

/-- Transport through the actual raw carrier-to-model codec, not native ofBits. -/
theorem rawNotNaN_eq_exec_model (q : Competition.Binary32) :
    rawNotNaN q.raw.1 = !Model.isNaN (ExecFloat.Binary.toModel q) := by
  rw [R7W02.exec_toModel_eq_rawModel]
  exact rawNotNaN_eq_not_isNaN q.raw.1

/-- A true original-word guard is exactly a real non-NaN carrier. -/
theorem rawNotNaN_exec_true_iff (q : Competition.Binary32) :
    rawNotNaN q.raw.1 = true ↔
      Model.isNaN (ExecFloat.Binary.toModel q) = false := by
  rw [rawNotNaN_eq_exec_model]
  simp

/-- W05's proved classifier bridge also identifies the canonical native classifier.
The guard itself never constructs a Float32 value or canonicalizes its input. -/
theorem rawNotNaN_eq_native_classifier (q : Competition.Binary32) :
    rawNotNaN q.raw.1 = !(ExecFloat.Binary.toFloat32 q).isNaN := by
  rw [R7W05.toFloat32_isNaN]
  exact rawNotNaN_eq_exec_model q

end R7W12
namespace R7SumRepair

open FloatLib.Floats Competition
open FloatLib.Floats.Formats.BinaryInterchange

@[inline] def step {n : Nat} (x : Vector Binary32 n)
    (acc : Binary32) (i : Fin n) : Binary32 := Submission.add acc (x.get i)

/-- A quiet sum must still inspect later signaling inputs, preserving their full words. -/
def suffixLoop {n : Nat} (x : Vector Binary32 n) (k : Nat) (acc : Binary32) : Binary32 :=
  if hk : k < n then
    suffixLoop x (k + 1) (R7W02.step acc (x.get ⟨k, hk⟩))
  else acc
termination_by n - k

theorem suffixLoop_eq {n : Nat} (x : Vector Binary32 n) (k : Nat) (acc : Binary32)
    (hq : Model.isQNaN (ExecFloat.Binary.toModel acc) = true) :
    suffixLoop x k acc = Fin.foldl.loop n (step x) acc k := by
  rw [suffixLoop]
  split
  · rename_i hk
    rw [Fin.foldl.loop, dif_pos hk]
    have ih := suffixLoop_eq x (k + 1) (R7W02.step acc (x.get ⟨k, hk⟩))
      (R7W02.step_isQNaN acc (x.get ⟨k, hk⟩) hq)
    have hs : R7W02.step acc (x.get ⟨k, hk⟩) = step x acc ⟨k, hk⟩ := by
      simpa only [step, Submission.add_eq] using
        R7W02.step_eq_add acc (x.get ⟨k, hk⟩) hq
    exact ih.trans (congrArg
      (fun a : Binary32 => Fin.foldl.loop n (step x) a (k + 1)) hs)
  · rename_i hk
    rw [Fin.foldl.loop, dif_neg hk]
termination_by n - k


end R7SumRepair


namespace R7NaNReplay

open FloatLib.Floats Competition

/-- The original exact software step, retaining the tuned scalar entry points. -/
@[inline] def replayStep (n baseA baseB p : Nat) (Araw Braw : Array Binary32)
    (acc : Binary32) (i : Fin n) : Binary32 :=
  Submission.add acc (Submission.mul (Araw.getD (baseA + i.val) posZero)
    (Braw.getD (baseB + i.val * p) posZero))

theorem replayStep_absorb (n baseA baseB p : Nat) (Araw Braw : Array Binary32)
    (acc : Binary32) (i : Fin n) (hq : R7W01.execQuietGuard acc = true) :
    replayStep n baseA baseB p Araw Braw acc i = acc := by
  unfold replayStep
  rw [Submission.add_eq, Submission.mul_eq]
  exact R7W01.exec_add_mul_absorb _ _ _
    (R7W01.quietGuard_nan _ hq) (R7W01.quietGuard_not_signaling _ hq)

theorem replayFold_absorb (n baseA baseB p : Nat) (Araw Braw : Array Binary32)
    (k : Nat) (acc : Binary32) (hq : R7W01.execQuietGuard acc = true) :
    Fin.foldl.loop n (replayStep n baseA baseB p Araw Braw) acc k = acc := by
  rw [Fin.foldl.loop]
  split
  · rename_i hk
    rw [replayStep_absorb n baseA baseB p Araw Braw acc ⟨k, hk⟩ hq]
    exact replayFold_absorb n baseA baseB p Araw Braw (k + 1) acc hq
  · rfl
termination_by n - k

/-- No index list is allocated, and a quiet result stops before further array reads. -/
def replayLoop (n baseA baseB p : Nat) (Araw Braw : Array Binary32)
    (k : Nat) (acc : Binary32) : Binary32 :=
  if hk : k < n then
    if R7W01.execQuietGuard acc then acc
    else replayLoop n baseA baseB p Araw Braw (k + 1)
      (replayStep n baseA baseB p Araw Braw acc ⟨k, hk⟩)
  else acc
termination_by n - k

theorem replayLoop_eq (n baseA baseB p : Nat) (Araw Braw : Array Binary32)
    (k : Nat) (acc : Binary32) :
    replayLoop n baseA baseB p Araw Braw k acc =
      Fin.foldl.loop n (replayStep n baseA baseB p Araw Braw) acc k := by
  rw [replayLoop]
  split
  · rename_i hk
    split
    · rename_i hq
      exact (replayFold_absorb n baseA baseB p Araw Braw k acc hq).symm
    · rw [Fin.foldl.loop, dif_pos hk]
      exact replayLoop_eq n baseA baseB p Araw Braw (k + 1) _
  · rename_i hk
    rw [Fin.foldl.loop, dif_neg hk]
termination_by n - k

def replayEarly (n baseA baseB p : Nat) (Araw Braw : Array Binary32) : Binary32 :=
  replayLoop n baseA baseB p Araw Braw 0 posZero

theorem replayEarly_eq (n baseA baseB p : Nat) (Araw Braw : Array Binary32) :
    replayEarly n baseA baseB p Araw Braw =
      Fin.foldl n (replayStep n baseA baseB p Araw Braw) posZero := by
  exact replayLoop_eq n baseA baseB p Araw Braw 0 posZero

/-- Apply the extra early check only to the already-rejected NaN endpoint. -/
def replay (n baseA baseB p : Nat) (Araw Braw : Array Binary32) (result : Float32) : Binary32 :=
  if result.isNaN then replayEarly n baseA baseB p Araw Braw
  else Fin.foldl n (replayStep n baseA baseB p Araw Braw) posZero

theorem replay_eq (n baseA baseB p : Nat) (Araw Braw : Array Binary32) (result : Float32) :
    replay n baseA baseB p Araw Braw result =
      Fin.foldl n (fun acc i => Submission.add acc
        (Submission.mul (Araw.getD (baseA + i.val) posZero)
          (Braw.getD (baseB + i.val * p) posZero))) posZero := by
  unfold replay
  split
  · exact replayEarly_eq n baseA baseB p Araw Braw
  · rfl



end R7NaNReplay

namespace NativeFinal


def dotLoop (n baseA baseB p : Nat) (A B : Array Binary32)
    (k : Nat) (acc : Float32) : Float32 :=
  if hk : k < n then
    let fa := ExecFloat.Binary.toFloat32 (A.getD (baseA + k) posZero)
    let fb := ExecFloat.Binary.toFloat32 (B.getD (baseB + k * p) posZero)
    dotLoop n baseA baseB p A B (k + 1) (acc + fa * fb)
  else acc
termination_by n - k

theorem dotLoop_eq (n baseA baseB p : Nat) (A B : Array Binary32)
    (k : Nat) (acc result : Float32)
    (hs : dotLoop n baseA baseB p A B k acc = result) (hf : result.isNaN = false) :
    acc.isNaN = false ∧ ExecFloat.Binary.ofFloat32 result =
      Fin.foldl.loop n
        (fun a i => ExecFloat.add a
          (ExecFloat.mul (A.getD (baseA + i.val) posZero)
            (B.getD (baseB + i.val * p) posZero)))
        (ExecFloat.Binary.ofFloat32 acc) k := by
  rw [dotLoop] at hs
  split at hs
  · rename_i hk
    dsimp only at hs
    have ih := dotLoop_eq n baseA baseB p A B (k + 1)
      (acc + ExecFloat.Binary.toFloat32 (A.getD (baseA + k) posZero) *
        ExecFloat.Binary.toFloat32 (B.getD (baseB + k * p) posZero)) result hs hf
    have ha := NotNaNProbe.add_inputs acc
      (ExecFloat.Binary.toFloat32 (A.getD (baseA + k) posZero) *
        ExecFloat.Binary.toFloat32 (B.getD (baseB + k * p) posZero)) ih.1
    have hm := NotNaNProbe.mul_inputs
      (ExecFloat.Binary.toFloat32 (A.getD (baseA + k) posZero))
      (ExecFloat.Binary.toFloat32 (B.getD (baseB + k * p) posZero)) ha.2
    refine ⟨ha.1, ?_⟩
    rw [Fin.foldl.loop, dif_pos hk]
    have hnext := ih.2
    rw [R7Native.ofFloat32Add _ _ ha.1 ha.2,
      R7Native.ofFloat32Mul _ _ hm.1 hm.2,
      NotNaNProbe.roundtrip _ hm.1, NotNaNProbe.roundtrip _ hm.2] at hnext
    exact hnext
  · rename_i hk
    refine ⟨?_, ?_⟩
    · simpa only [hs] using hf
    · rw [Fin.foldl.loop, dif_neg hk]
      exact congrArg ExecFloat.Binary.ofFloat32 hs.symm
termination_by n - k

def dot (n baseA baseB p : Nat) (A B : Array Binary32) : Binary32 :=
  let result := dotLoop n baseA baseB p A B 0 (Float32.ofBits 0)
  if hf : R7W04.nonNaN result = true then ExecFloat.Binary.ofFloat32 result
  else R7NaNReplay.replayEarly n baseA baseB p A B

theorem dot_eq (n baseA baseB p : Nat) (A B : Array Binary32) :
    dot n baseA baseB p A B = Fin.foldl n
      (fun a i => ExecFloat.add a (ExecFloat.mul (A.getD (baseA + i.val) posZero)
        (B.getD (baseB + i.val * p) posZero))) posZero := by
  unfold dot
  dsimp only
  split
  · rename_i hf
    have hnon := (R7W04.nonNaN_eq_true_iff _).mp hf
    have h := (dotLoop_eq n baseA baseB p A B 0 (Float32.ofBits 0) _ rfl hnon).2
    change ExecFloat.Binary.ofFloat32 _ = Fin.foldl n _ posZero at h
    exact h
  · refine (R7NaNReplay.replayEarly_eq n baseA baseB p A B).trans ?_
    apply congrArg (fun step : Binary32 → Fin n → Binary32 => Fin.foldl n step posZero)
    funext acc i
    simp only [R7NaNReplay.replayStep, Submission.add_eq, Submission.mul_eq]

end NativeFinal


theorem index_address (a b c d : Nat) : (a + b) * c + d = (a * c + d) + b * c := by
  rw [Nat.add_mul]
  omega

namespace Packed10

structure F10 where
  s0 : Float32
  s1 : Float32
  s2 : Float32
  s3 : Float32
  s4 : Float32
  s5 : Float32
  s6 : Float32
  s7 : Float32
  s8 : Float32
  s9 : Float32

@[inline] def zero32 : Float32 := Float32.ofBits 0

@[inline] def zero10 : F10 := ⟨zero32, zero32, zero32, zero32, zero32, zero32, zero32, zero32, zero32, zero32⟩

@[inline] def lane (v : F10) (l : Fin 10) : Float32 :=
  match l.val with
  | 0 => v.s0
  | 1 => v.s1
  | 2 => v.s2
  | 3 => v.s3
  | 4 => v.s4
  | 5 => v.s5
  | 6 => v.s6
  | 7 => v.s7
  | 8 => v.s8
  | _ => v.s9

@[inline] def packet (read : Nat → Float32) (col : Nat) : F10 :=
  ⟨read col, read (col + 1), read (col + 2), read (col + 3), read (col + 4), read (col + 5), read (col + 6), read (col + 7), read (col + 8), read (col + 9)⟩

@[inline] def update (acc : F10) (a : Float32) (v : F10) : F10 :=
  ⟨acc.s0 + a * v.s0, acc.s1 + a * v.s1, acc.s2 + a * v.s2, acc.s3 + a * v.s3, acc.s4 + a * v.s4, acc.s5 + a * v.s5, acc.s6 + a * v.s6, acc.s7 + a * v.s7, acc.s8 + a * v.s8, acc.s9 + a * v.s9⟩

theorem lane_packet (read : Nat → Float32) (col : Nat) (l : Fin 10) :
    lane (packet read col) l = read (col + l.val) := by
  rcases l with ⟨l, hl⟩
  have h : l = 0 ∨ l = 1 ∨ l = 2 ∨ l = 3 ∨ l = 4 ∨ l = 5 ∨ l = 6 ∨ l = 7 ∨ l = 8 ∨ l = 9 := by omega
  rcases h with rfl | rfl | rfl | rfl | rfl | rfl | rfl | rfl | rfl | rfl <;> rfl

theorem lane_zero10 (l : Fin 10) : lane zero10 l = zero32 := by
  rcases l with ⟨l, hl⟩
  have h : l = 0 ∨ l = 1 ∨ l = 2 ∨ l = 3 ∨ l = 4 ∨ l = 5 ∨ l = 6 ∨ l = 7 ∨ l = 8 ∨ l = 9 := by omega
  rcases h with rfl | rfl | rfl | rfl | rfl | rfl | rfl | rfl | rfl | rfl <;> rfl


theorem lane_update (acc : F10) (a : Float32) (v : F10) (l : Fin 10) :
    lane (update acc a v) l = lane acc l + a * lane v l := by
  rcases l with ⟨l, hl⟩
  have h : l = 0 ∨ l = 1 ∨ l = 2 ∨ l = 3 ∨ l = 4 ∨ l = 5 ∨ l = 6 ∨ l = 7 ∨ l = 8 ∨ l = 9 := by omega
  rcases h with rfl | rfl | rfl | rfl | rfl | rfl | rfl | rfl | rfl | rfl <;> rfl

@[inline] def groups (p : Nat) : Nat := (p + 9) / 10


theorem vector_get_ofFn {α : Type} {n : Nat}
    (f : Fin n → α) (i : Fin n) : (Vector.ofFn f).get i = f i := by
  change (Vector.ofFn f)[i.val]'i.isLt = f i
  exact Vector.getElem_ofFn i.isLt

def packB (batch n p : Nat) (B : Vector Binary32 (batch * n * p)) :
    Vector (Vector (Vector F10 n) (groups p)) batch :=
  Vector.ofFn fun b =>
    Vector.ofFn fun g =>
      Vector.ofFn fun k =>
        let base := (b.val * n + k.val) * p
        packet (fun j =>
          if hj : j < p then
            have hbn : (b.val + 1) * n ≤ batch * n := Nat.mul_le_mul_right n b.isLt
            have hbk : b.val * n + k.val < batch * n := by
              rw [Nat.add_mul] at hbn
              omega
            have hp : (b.val * n + k.val + 1) * p ≤ batch * n * p :=
              Nat.mul_le_mul_right p (Nat.succ_le_of_lt hbk)
            have hi : base + j < B.toArray.size := by
              rw [B.size_toArray]
              dsimp [base]
              rw [Nat.add_mul] at hp
              omega
            ExecFloat.Binary.toFloat32 B.toArray[base + j]
          else zero32) (10 * g.val)

theorem packB_get (batch n p : Nat)
    (B : Vector Binary32 (batch * n * p))
    (b : Fin batch) (g : Fin (groups p)) (k : Fin n) :
    (((packB batch n p B).get b).get g).get k =
      packet (fun j =>
        if j < p then
          ExecFloat.Binary.toFloat32
            (B.toArray.getD ((b.val * n + k.val) * p + j) posZero)
        else zero32) (10 * g.val) := by
  simp only [packB, vector_get_ofFn]
  congr 1
  funext j
  split
  · rename_i hj
    have hbn : (b.val + 1) * n ≤ batch * n := Nat.mul_le_mul_right n b.isLt
    have hbk : b.val * n + k.val < batch * n := by
      rw [Nat.add_mul] at hbn
      omega
    have hp : (b.val * n + k.val + 1) * p ≤ batch * n * p :=
      Nat.mul_le_mul_right p (Nat.succ_le_of_lt hbk)
    have hi : (b.val * n + k.val) * p + j < B.toArray.size := by
      rw [B.size_toArray]
      rw [Nat.add_mul] at hp
      omega
    have hidx : (b.val * n + k.val) * p + j < batch * n * p := by
      simpa only [B.size_toArray] using hi
    simp [Array.getD, hidx, hj]
  · rename_i hj
    simp only [dif_neg hj, if_neg hj]

theorem packB_lane (batch n p : Nat)
    (B : Vector Binary32 (batch * n * p))
    (b : Fin batch) (g : Fin (groups p)) (k : Fin n) (l : Fin 10)
    (hcol : 10 * g.val + l.val < p) :
    lane ((((packB batch n p B).get b).get g).get k) l =
      ExecFloat.Binary.toFloat32
        (B.toArray.getD
          ((b.val * n + k.val) * p + (10 * g.val + l.val)) posZero) := by
  rw [packB_get, lane_packet, if_pos hcol]

end Packed10


namespace Packed10

open FloatLib.Floats Competition

/-- Mapping the input preserves the total read, including the positive-zero default. -/
theorem nativeA_getD (Araw : Array Binary32) (i : Nat) :
    (Araw.map ExecFloat.Binary.toFloat32).getD i zero32 =
      ExecFloat.Binary.toFloat32 (Araw.getD i posZero) := by
  by_cases hi : i < Araw.size
  · simp [Array.getD, hi, zero32]
  · simp [Array.getD, hi, zero32] <;> rfl

/-- Ten independent left folds share each input load from the left operand. -/
def dot10 (n baseA : Nat) (A : Array Float32) (B : Vector F10 n)
    (k : Nat) (s0 s1 s2 s3 s4 s5 s6 s7 s8 s9 : Float32) : F10 :=
  if hk : k < n then
    let sharedA := A.getD (baseA + k) zero32
    let v := B.get ⟨k, hk⟩
    dot10 n baseA A B (k + 1)
      (s0 + sharedA * v.s0)
      (s1 + sharedA * v.s1)
      (s2 + sharedA * v.s2)
      (s3 + sharedA * v.s3)
      (s4 + sharedA * v.s4)
      (s5 + sharedA * v.s5)
      (s6 + sharedA * v.s6)
      (s7 + sharedA * v.s7) (s8 + sharedA * v.s8) (s9 + sharedA * v.s9)
  else ⟨s0, s1, s2, s3, s4, s5, s6, s7, s8, s9⟩
termination_by n - k

theorem dot10_lane (n baseA baseB p : Nat) (Araw Braw : Array Binary32)
    (B : Vector F10 n) (l : Fin 10)
    (hb : ∀ i : Fin n, lane (B.get i) l =
      ExecFloat.Binary.toFloat32 (Braw.getD (baseB + i.val * p) posZero))
    (k : Nat) (s0 s1 s2 s3 s4 s5 s6 s7 s8 s9 : Float32) :
    lane (dot10 n baseA (Araw.map ExecFloat.Binary.toFloat32) B k s0 s1 s2 s3 s4 s5 s6 s7 s8 s9) l =
      NativeFinal.dotLoop n baseA baseB p Araw Braw k (lane ⟨s0, s1, s2, s3, s4, s5, s6, s7, s8, s9⟩ l) := by
  by_cases hk : k < n
  · rw [dot10, NativeFinal.dotLoop]
    simp only [dif_pos hk, if_pos hk]
    try dsimp only
    have ih := dot10_lane n baseA baseB p Araw Braw B l hb (k + 1)
      (s0 + (Araw.map ExecFloat.Binary.toFloat32).getD (baseA + k) zero32 * (B.get ⟨k, hk⟩).s0)
      (s1 + (Araw.map ExecFloat.Binary.toFloat32).getD (baseA + k) zero32 * (B.get ⟨k, hk⟩).s1)
      (s2 + (Araw.map ExecFloat.Binary.toFloat32).getD (baseA + k) zero32 * (B.get ⟨k, hk⟩).s2)
      (s3 + (Araw.map ExecFloat.Binary.toFloat32).getD (baseA + k) zero32 * (B.get ⟨k, hk⟩).s3)
      (s4 + (Araw.map ExecFloat.Binary.toFloat32).getD (baseA + k) zero32 * (B.get ⟨k, hk⟩).s4)
      (s5 + (Araw.map ExecFloat.Binary.toFloat32).getD (baseA + k) zero32 * (B.get ⟨k, hk⟩).s5)
      (s6 + (Araw.map ExecFloat.Binary.toFloat32).getD (baseA + k) zero32 * (B.get ⟨k, hk⟩).s6)
      (s7 + (Araw.map ExecFloat.Binary.toFloat32).getD (baseA + k) zero32 * (B.get ⟨k, hk⟩).s7)
      (s8 + (Araw.map ExecFloat.Binary.toFloat32).getD (baseA + k) zero32 * (B.get ⟨k, hk⟩).s8)
      (s9 + (Araw.map ExecFloat.Binary.toFloat32).getD (baseA + k) zero32 * (B.get ⟨k, hk⟩).s9)
    have hacc :
        lane ⟨s0 + (Araw.map ExecFloat.Binary.toFloat32).getD (baseA + k) zero32 * (B.get ⟨k, hk⟩).s0, s1 + (Araw.map ExecFloat.Binary.toFloat32).getD (baseA + k) zero32 * (B.get ⟨k, hk⟩).s1, s2 + (Araw.map ExecFloat.Binary.toFloat32).getD (baseA + k) zero32 * (B.get ⟨k, hk⟩).s2, s3 + (Araw.map ExecFloat.Binary.toFloat32).getD (baseA + k) zero32 * (B.get ⟨k, hk⟩).s3, s4 + (Araw.map ExecFloat.Binary.toFloat32).getD (baseA + k) zero32 * (B.get ⟨k, hk⟩).s4, s5 + (Araw.map ExecFloat.Binary.toFloat32).getD (baseA + k) zero32 * (B.get ⟨k, hk⟩).s5, s6 + (Araw.map ExecFloat.Binary.toFloat32).getD (baseA + k) zero32 * (B.get ⟨k, hk⟩).s6, s7 + (Araw.map ExecFloat.Binary.toFloat32).getD (baseA + k) zero32 * (B.get ⟨k, hk⟩).s7, s8 + (Araw.map ExecFloat.Binary.toFloat32).getD (baseA + k) zero32 * (B.get ⟨k, hk⟩).s8, s9 + (Araw.map ExecFloat.Binary.toFloat32).getD (baseA + k) zero32 * (B.get ⟨k, hk⟩).s9⟩ l =
          lane ⟨s0, s1, s2, s3, s4, s5, s6, s7, s8, s9⟩ l +
            ExecFloat.Binary.toFloat32 (Araw.getD (baseA + k) posZero) *
              ExecFloat.Binary.toFloat32 (Braw.getD (baseB + k * p) posZero) := by
      change lane (update ⟨s0, s1, s2, s3, s4, s5, s6, s7, s8, s9⟩
        ((Araw.map ExecFloat.Binary.toFloat32).getD (baseA + k) zero32)
        (B.get ⟨k, hk⟩)) l = _
      rw [lane_update, nativeA_getD, hb ⟨k, hk⟩]
    rw [hacc] at ih
    exact ih
  · rw [dot10, NativeFinal.dotLoop]
    simp only [dif_neg hk, if_neg hk]
termination_by n - k

/-- The result guard and exact fallback are the same as in the scalar implementation. -/
def finish (n baseA baseB p : Nat) (Araw Braw : Array Binary32)
    (result : Float32) : Binary32 :=
  if hf : R7W04.nonNaN result = true then ExecFloat.Binary.ofFloat32 result
  else R7NaNReplay.replayEarly n baseA baseB p Araw Braw

theorem finish_eq_dot (n baseA baseB p : Nat) (Araw Braw : Array Binary32)
    (result : Float32)
    (hs : result = NativeFinal.dotLoop n baseA baseB p Araw Braw 0 zero32) :
    finish n baseA baseB p Araw Braw result =
      NativeFinal.dot n baseA baseB p Araw Braw := by
  rw [hs] <;> rfl


theorem finish_dot10_lane (n baseA baseB p : Nat) (Araw Braw : Array Binary32)
    (B : Vector F10 n) (l : Fin 10)
    (hb : ∀ i : Fin n, lane (B.get i) l =
      ExecFloat.Binary.toFloat32 (Braw.getD (baseB + i.val * p) posZero)) :
    finish n baseA baseB p Araw Braw
        (lane (dot10 n baseA (Araw.map ExecFloat.Binary.toFloat32) B 0
          zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32) l) =
      NativeFinal.dot n baseA baseB p Araw Braw := by
  have hs := dot10_lane n baseA baseB p Araw Braw B l hb 0
    zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32
  have hz : lane (⟨zero32, zero32, zero32, zero32, zero32, zero32, zero32, zero32, zero32, zero32⟩ : F10) l = zero32 :=
    lane_zero10 l
  rw [hz] at hs
  exact finish_eq_dot n baseA baseB p Araw Braw _ hs


end Packed10




namespace Packed10Index

open Packed10

theorem addNat (a b : USize) (h : a.toNat + b.toNat < USize.size) :
    (a + b).toNat = a.toNat + b.toNat := by
  rw [USize.toNat_add]
  exact Nat.mod_eq_of_lt h

theorem stepNat {n k : USize} (hk : k < n) : (k + 1).toNat = k.toNat + 1 := by
  rw [USize.toNat_add, USize.toNat_one]
  have hkn := USize.lt_iff_toNat_lt.mp hk
  have hn := USize.toNat_lt_size n
  apply Nat.mod_eq_of_lt
  change k.toNat + 1 < USize.size
  omega

theorem next_decreases {n k : USize} (hk : k < n) :
    n.toNat - (k + 1).toNat < n.toNat - k.toNat := by
  rw [stepNat hk]
  have hkn := USize.lt_iff_toNat_lt.mp hk
  omega

theorem boundA (base n k size : Nat) (h : base + (n - 1) < size) (hk : k < n) :
    base + k < size := by omega

theorem ugetA_getD (A : Array Float32) (i : USize) (h : i.toNat < A.size) :
    A.uget i h = A.getD i.toNat zero32 := by
  simp [Array.uget, Array.getD, h]

theorem ugetB_get {n : Nat} (B : Vector F10 n) (i : USize)
    (hi : i.toNat < n) :
    B.toArray.uget i (by simpa only [B.size_toArray] using hi) =
      B.get ⟨i.toNat, hi⟩ := by
  rfl

/-- The bounds are established once; each iteration reads with machine-word indices. -/
def loop {n : Nat} (count baseA : USize) (A : Array Float32) (B : Vector F10 n)
    (hn : count.toNat = n)
    (hA : baseA.toNat + (count.toNat - 1) < A.size)
    (hAS : A.size < USize.size)
    (k : USize) (s0 s1 s2 s3 s4 s5 s6 s7 s8 s9 : Float32) : F10 :=
  if hk : k < count then
    have hkn : k.toNat < n := by
      rw [← hn]
      exact USize.lt_iff_toNat_lt.mp hk
    have ha := boundA baseA.toNat count.toNat k.toNat A.size hA
      (USize.lt_iff_toNat_lt.mp hk)
    let a := A.uget (baseA + k)
      (by rw [addNat baseA k (Nat.lt_trans ha hAS)]; exact ha)
    let v := B.toArray.uget k (by simpa only [B.size_toArray] using hkn)
    loop count baseA A B hn hA hAS (k + 1)
      (s0 + a * v.s0) (s1 + a * v.s1)
      (s2 + a * v.s2) (s3 + a * v.s3)
      (s4 + a * v.s4) (s5 + a * v.s5)
      (s6 + a * v.s6) (s7 + a * v.s7) (s8 + a * v.s8) (s9 + a * v.s9)
  else ⟨s0, s1, s2, s3, s4, s5, s6, s7, s8, s9⟩
termination_by count.toNat - k.toNat
decreasing_by
  apply next_decreases
  assumption

theorem loop_eq {n : Nat} (count baseA : USize) (A : Array Float32) (B : Vector F10 n)
    (hn : count.toNat = n)
    (hA : baseA.toNat + (count.toNat - 1) < A.size)
    (hAS : A.size < USize.size)
    (k : USize) (s0 s1 s2 s3 s4 s5 s6 s7 s8 s9 : Float32) :
    loop count baseA A B hn hA hAS k s0 s1 s2 s3 s4 s5 s6 s7 s8 s9 =
      Packed10.dot10 n baseA.toNat A B k.toNat s0 s1 s2 s3 s4 s5 s6 s7 s8 s9 := by
  rw [loop]
  split
  · rename_i hk
    have hkn : k.toNat < n := by
      rw [← hn]
      exact USize.lt_iff_toNat_lt.mp hk
    have ha := boundA baseA.toNat count.toNat k.toNat A.size hA
      (USize.lt_iff_toNat_lt.mp hk)
    rw [Packed10.dot10, dif_pos hkn]
    dsimp only
    rw [loop_eq, stepNat hk]
    simp only [ugetA_getD, addNat baseA k (Nat.lt_trans ha hAS), ugetB_get]
    rfl
  · rename_i hk
    have hkn : ¬ k.toNat < n := by
      rw [← hn]
      simpa only [USize.lt_iff_toNat_lt] using hk
    rw [Packed10.dot10, dif_neg hkn]
termination_by count.toNat - k.toNat
decreasing_by
  apply next_decreases
  assumption

@[inline] def within (n baseA : Nat) (A : Array Float32) (B : Vector F10 n)
    (hn : n < USize.size) (ha : baseA < USize.size)
    (hA : baseA + (n - 1) < A.size) (hAS : A.size < USize.size) : F10 :=
  loop (USize.ofNat n) (USize.ofNat baseA) A B
    (USize.toNat_ofNat_of_lt' hn)
    (by simpa only [USize.toNat_ofNat_of_lt' hn, USize.toNat_ofNat_of_lt' ha] using hA)
    hAS 0 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32

theorem within_eq (n baseA : Nat) (A : Array Float32) (B : Vector F10 n)
    (hn : n < USize.size) (ha : baseA < USize.size)
    (hA : baseA + (n - 1) < A.size) (hAS : A.size < USize.size) :
    within n baseA A B hn ha hA hAS =
      Packed10.dot10 n baseA A B 0 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 := by
  simp only [within, loop_eq, USize.toNat_ofNat_of_lt' hn,
    USize.toNat_ofNat_of_lt' ha, USize.toNat_zero]

@[inline] def runDot (n baseA : Nat) (A : Array Float32) (B : Vector F10 n) : F10 :=
  if h : n < USize.size ∧ baseA < USize.size ∧
      baseA + (n - 1) < A.size ∧ A.size < USize.size then
    within n baseA A B h.1 h.2.1 h.2.2.1 h.2.2.2
  else Packed10.dot10 n baseA A B 0 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32

theorem runDot_eq (n baseA : Nat) (A : Array Float32) (B : Vector F10 n) :
    runDot n baseA A B =
      Packed10.dot10 n baseA A B 0 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 := by
  unfold runDot
  split
  · rename_i h
    exact within_eq n baseA A B h.1 h.2.1 h.2.2.1 h.2.2.2
  · rfl

end Packed10Index




end Submission








namespace Submission.RowStream

open FloatLib.Floats Competition

/-- A growing output array contains exactly the reference prefix. -/
def Prefix (f : Nat → Binary32) (k : Nat) (out : Array Binary32) : Prop :=
  out.size = k ∧ ∀ j (hj : j < out.size), out[j] = f j

theorem prefix_push (f : Nat → Binary32) (k : Nat) (out : Array Binary32)
    (h : Prefix f k out) : Prefix f (k + 1) (out.push (f k)) := by
  refine ⟨by simp only [Array.size_push, h.1], ?_⟩
  intro j hj
  have hj' : j < out.size + 1 := by simpa only [Array.size_push] using hj
  by_cases hlt : j < out.size
  · rw [Array.getElem_push_lt hlt]
    exact h.2 j hlt
  · have he : j = out.size := by omega
    subst j
    rw [Array.getElem_push_eq, h.1]

/-- The ordinary finite left fold preserves an indexed invariant. -/
theorem foldl_loop_inv {β : Type} (count : Nat) (step : β → Fin count → β)
    (P : Nat → β → Prop)
    (hstep : ∀ (i : Fin count) (x : β), P i.val x → P (i.val + 1) (step x i))
    (k : Nat) (hk : k ≤ count) (x : β) (hx : P k x) :
    P count (Fin.foldl.loop count step x k) := by
  by_cases hi : k < count
  · rw [Fin.foldl.loop, dif_pos hi]
    exact foldl_loop_inv count step P hstep (k + 1) (by omega)
      (step x ⟨k, hi⟩) (hstep ⟨k, hi⟩ x hx)
  · have he : k = count := by omega
    subst k
    rw [Fin.foldl.loop, dif_neg (Nat.lt_irrefl count)]
    exact hx
termination_by count - k

theorem foldl_inv {β : Type} (count : Nat) (step : β → Fin count → β)
    (P : Nat → β → Prop)
    (hstep : ∀ (i : Fin count) (x : β), P i.val x → P (i.val + 1) (step x i))
    (x : β) (hx : P 0 x) : P count (Fin.foldl count step x) := by
  exact foldl_loop_inv count step P hstep 0 (Nat.zero_le count) x hx

/-- Emit directly into the caller's array; no lane or row array is built. -/
@[inline] def emit (count : Nat) (read : Fin count → Binary32)
    (out : Array Binary32) : Array Binary32 :=
  Fin.foldl count (fun acc l => acc.push (read l)) out

theorem emit_prefix (f : Nat → Binary32) (k count : Nat)
    (read : Fin count → Binary32) (out : Array Binary32)
    (hout : Prefix f k out) (hread : ∀ l, read l = f (k + l.val)) :
    Prefix f (k + count) (emit count read out) := by
  apply foldl_inv count (fun acc l => acc.push (read l))
    (fun i acc => Prefix f (k + i) acc)
  · intro l acc hacc
    rw [hread l]
    simpa only [Nat.add_assoc] using prefix_push f (k + l.val) acc hacc
  · simpa only [Nat.add_zero] using hout

def point (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) (q : Nat) : Binary32 :=
  let (b, i, j) := bmmDecodeC m p q
  NativeFinal.dot n ((b * m + i) * n) (b * n * p + j) p A.toArray B.toArray

theorem decode_row (m p r j : Nat) (hm : 0 < m) (hp : 0 < p) (hj : j < p) :
    bmmDecodeC m p (r * p + j) = (r / m, r % m, j) := by
  have hmp : m * p ≠ 0 := Nat.ne_of_gt (Nat.mul_pos hm hp)
  have hp0 : p ≠ 0 := Nat.ne_of_gt hp
  have hd : (r * p + j) / p = r := by
    rw [Nat.mul_comm r p, Nat.mul_add_div hp, Nat.div_eq_of_lt hj, Nat.add_zero]
  have hb : (r * p + j) / (m * p) = r / m := by
    rw [Nat.mul_comm m p, ← Nat.div_div_eq_div_mul, hd]
  simp only [bmmDecodeC, hmp, hp0, if_false, hb,
    Nat.mod_mul_left_div_self, Nat.mod_mul_left_mod, hd,
    Nat.mul_add_mod_of_lt hj]

theorem point_row (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) (r j : Nat)
    (hm : 0 < m) (hp : 0 < p) (hj : j < p) :
    point batch m n p A B (r * p + j) =
      NativeFinal.dot n (r * n) (r / m * n * p + j) p A.toArray B.toArray := by
  simp only [point, decode_row m p r j hm hp hj, Nat.div_add_mod']

@[inline] def group (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) (nativeA : Array Float32)
    (packedB : Vector (Vector (Vector Packed10.F10 n) (Packed10.groups p)) batch)
    (r : Fin (batch * m)) (out : Array Binary32) (g : Fin (Packed10.groups p)) :
    Array Binary32 :=
  have hm : 0 < m := Nat.pos_of_lt_mul_left r.isLt
  let b : Fin batch := ⟨r.val / m, (Nat.div_lt_iff_lt_mul hm).2 r.isLt⟩
  let result := Packed10Index.runDot n (r.val * n) nativeA ((packedB.get b).get g)
  let count := min 10 (p - 10 * g.val)
  emit count (fun l =>
    let j := 10 * g.val + l.val
    Packed10.finish n (r.val * n) (b.val * n * p + j) p A.toArray B.toArray
      (Packed10.lane result ⟨l.val, Nat.lt_of_lt_of_le l.isLt (Nat.min_le_left _ _)⟩)) out

theorem group_prefix (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) (r : Fin (batch * m))
    (g : Fin (Packed10.groups p)) (out : Array Binary32)
    (hout : Prefix (point batch m n p A B) (r.val * p + min (10 * g.val) p) out) :
    Prefix (point batch m n p A B) (r.val * p + min (10 * (g.val + 1)) p)
      (group batch m n p A B (A.toArray.map ExecFloat.Binary.toFloat32)
        (Packed10.packB batch n p B) r out g) := by
  have hm : 0 < m := Nat.pos_of_lt_mul_left r.isLt
  have hg : 10 * g.val < p := by
    have h := g.isLt
    unfold Packed10.groups at h
    omega
  have hp : 0 < p := by omega
  have hstart : min (10 * g.val) p = 10 * g.val := by omega
  have hend : r.val * p + min (10 * (g.val + 1)) p =
      (r.val * p + 10 * g.val) + min 10 (p - 10 * g.val) := by omega
  rw [hend]
  unfold group
  dsimp only
  apply emit_prefix
  · simpa only [hstart] using hout
  · intro l
    have hcol : 10 * g.val + l.val < p := by
      have hl := l.isLt
      omega
    rw [show r.val * p + 10 * g.val + l.val =
      r.val * p + (10 * g.val + l.val) by omega,
      point_row batch m n p A B r.val (10 * g.val + l.val) hm hp hcol,
      Packed10Index.runDot_eq]
    apply Packed10.finish_dot10_lane
    intro k
    rw [Packed10.packB_lane batch n p B
      ⟨r.val / m, (Nat.div_lt_iff_lt_mul hm).2 r.isLt⟩ g k
      ⟨l.val, Nat.lt_of_lt_of_le l.isLt (Nat.min_le_left _ _)⟩ hcol]
    rw [index_address (r.val / m * n) k.val p (10 * g.val + l.val)]

@[inline] def row (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) (nativeA : Array Float32)
    (packedB : Vector (Vector (Vector Packed10.F10 n) (Packed10.groups p)) batch)
    (out : Array Binary32) (r : Fin (batch * m)) : Array Binary32 :=
  Fin.foldl (Packed10.groups p) (group batch m n p A B nativeA packedB r) out

theorem row_prefix (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) (r : Fin (batch * m)) (out : Array Binary32)
    (hout : Prefix (point batch m n p A B) (r.val * p) out) :
    Prefix (point batch m n p A B) ((r.val + 1) * p)
      (row batch m n p A B (A.toArray.map ExecFloat.Binary.toFloat32)
        (Packed10.packB batch n p B) out r) := by
  have hlast : min (10 * Packed10.groups p) p = p := by
    unfold Packed10.groups
    omega
  have h := foldl_inv (Packed10.groups p)
    (group batch m n p A B (A.toArray.map ExecFloat.Binary.toFloat32)
      (Packed10.packB batch n p B) r)
    (fun g acc => Prefix (point batch m n p A B) (r.val * p + min (10 * g) p) acc)
    (fun g acc hacc => group_prefix batch m n p A B r g acc hacc) out
    (by simpa only [Nat.mul_zero, Nat.zero_min, Nat.add_zero] using hout)
  simpa only [row, hlast, Nat.add_mul, Nat.one_mul] using h

def output (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Array Binary32 :=
  let nativeA := A.toArray.map ExecFloat.Binary.toFloat32
  let packedB := Packed10.packB batch n p B
  Fin.foldl (batch * m) (row batch m n p A B nativeA packedB)
    (Array.mkEmpty (batch * m * p))

theorem output_prefix (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) :
    Prefix (point batch m n p A B) (batch * m * p) (output batch m n p A B) := by
  exact foldl_inv (batch * m)
    (row batch m n p A B (A.toArray.map ExecFloat.Binary.toFloat32)
      (Packed10.packB batch n p B))
    (fun r acc => Prefix (point batch m n p A B) (r * p) acc)
    (fun r acc hacc => row_prefix batch m n p A B r acc hacc)
    (Array.mkEmpty (batch * m * p))
    ⟨by simp, by intro j hj; simp at hj⟩

def core (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Vector Binary32 (batch * m * p) :=
  ⟨output batch m n p A B, (output_prefix batch m n p A B).1⟩

/-- Abstract array-to-vector bridge: keep the concrete output loop opaque. -/
theorem prefix_vector_eq_ofFn (f : Nat → Binary32) (count : Nat)
    (out : Array Binary32) (h : Prefix f count out) :
    (Vector.mk out h.1 : Vector Binary32 count) =
      Vector.ofFn (fun q : Fin count => f q.val) := by
  apply Vector.ext
  intro q hq
  rw [Vector.getElem_mk, Vector.getElem_ofFn]
  exact h.2 q (by rw [h.1]; exact hq)

/-- Scalar address/float bridge, without the concrete writer in its goal. -/
theorem points_eq_reference (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) :
    Vector.ofFn (fun q : Fin (batch * m * p) => point batch m n p A B q.val) =
      referenceBmm batch m n p A B := by
  unfold referenceBmm
  apply congrArg (fun (f : Fin (batch * m * p) → Binary32) => Vector.ofFn f)
  funext q
  dsimp only [point]
  rw [NativeFinal.dot_eq]
  simp only [add_eq, mul_eq]
  apply congrArg (fun (f : Binary32 → Fin n → Binary32) => Fin.foldl n f posZero)
  funext acc k
  rw [index_address ((bmmDecodeC m p q.val).1 * n) k.val p
    (bmmDecodeC m p q.val).2.2]

theorem core_eq_reference (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) :
    core batch m n p A B = referenceBmm batch m n p A B := by
  exact (prefix_vector_eq_ofFn (point batch m n p A B) (batch * m * p)
    (output batch m n p A B) (output_prefix batch m n p A B)).trans
    (points_eq_reference batch m n p A B)


end Submission.RowStream

namespace Submission

open FloatLib.Floats Competition

def bmmPackedBase (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Vector Binary32 (batch * m * p) :=
  if batch * m * p = 0 then referenceBmm batch m n p A B
  else if n = 0 then referenceBmm batch m n p A B
  else RowStream.core batch m n p A B

theorem bmmPackedBase_spec : ∀ (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)),
    (bmmPackedBase batch m n p A B).get = bmmSpec batch m n p A.get B.get := by
  intro batch m n p A B
  have h : bmmPackedBase batch m n p A B = referenceBmm batch m n p A B := by
    unfold bmmPackedBase
    split
    · rfl
    · split
      · rfl
      · exact RowStream.core_eq_reference batch m n p A B
  exact (congrArg (fun v : Vector Binary32 (batch * m * p) => v.get) h).trans
    (referenceBmm_spec batch m n p A B)

end Submission


namespace Submission.DirectSmall

open FloatLib.Floats Competition

def core (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Vector Binary32 (batch * m * p) :=
  Vector.ofFn fun q =>
    let (b, i, j) := bmmDecodeC m p q.val
    NativeFinal.dot n ((b * m + i) * n) (b * n * p + j) p A.toArray B.toArray

theorem core_eq_reference (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) :
    core batch m n p A B = referenceBmm batch m n p A B := by
  unfold core referenceBmm
  apply congrArg (fun (f : Fin (batch * m * p) → Binary32) => Vector.ofFn f)
  funext q
  dsimp only
  rw [NativeFinal.dot_eq]
  simp only [add_eq, mul_eq]
  apply congrArg (fun (f : Binary32 → Fin n → Binary32) => Fin.foldl n f posZero)
  funext acc k
  have hi := index_address ((bmmDecodeC m p q.val).1 * n) k.val p
    (bmmDecodeC m p q.val).2.2
  rw [hi]

end Submission.DirectSmall

namespace Submission

open FloatLib.Floats Competition

def bmmBeforeDirectRows (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Vector Binary32 (batch * m * p) :=
  if n ≤ 4 ∨ p ≤ 2 then DirectSmall.core batch m n p A B
  else bmmPackedBase batch m n p A B

theorem bmmBeforeDirectRows_spec : ∀ (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)),
    (bmmBeforeDirectRows batch m n p A B).get = bmmSpec batch m n p A.get B.get := by
  intro batch m n p A B
  unfold bmmBeforeDirectRows
  split
  · rw [DirectSmall.core_eq_reference]
    exact referenceBmm_spec batch m n p A B
  · exact bmmPackedBase_spec batch m n p A B

end Submission


namespace Submission

namespace R7SinglePassSum

open FloatLib.Floats Competition
open FloatLib.Floats.Formats.BinaryInterchange

/-- The existing decoder's low test cannot reject an infinity or NaN magnitude. -/
theorem low_reject_finite (a : UInt32)
    (h : ¬ ((0x0bffffff : UInt32) ≤ a - 1)) :
    a < (0x7f800000 : UInt32) := by
  by_cases hz : a = 0
  · subst a
    exact False.elim (h (by decide))
  · have hpos : 0 < a := UInt32.pos_iff_ne_zero.mpr hz
    have hone : (1 : UInt32) ≤ a := by
      change 1 ≤ a.toNat
      change 0 < a.toNat at hpos
      omega
    have hnat : ¬ 201326591 ≤ (a - 1).toNat := h
    rw [UInt32.toNat_sub_of_le a 1 hone] at hnat
    change a.toNat < 2139095040
    change ¬ 201326591 ≤ a.toNat - 1 at hnat
    omega

theorem raw_nonNaN_of_le (u : UInt32)
    (h : R2W01b.magnitude u ≤ (0x7f800000 : UInt32)) :
    R7W12.rawNotNaN u = true := by
  unfold R7W12.rawNotNaN
  rw [decide_eq_true_eq]
  exact h

theorem raw_nan_of_high_reject (u : UInt32)
    (h : ¬ R2W01b.magnitude u < (0x7f800000 : UInt32))
    (hi : R2W01b.magnitude u ≠ (0x7f800000 : UInt32)) :
    R7W12.rawNotNaN u = false := by
  have hgt : ¬ R2W01b.magnitude u ≤ (0x7f800000 : UInt32) := by
    intro hle
    exact hi (UInt32.le_antisymm hle (UInt32.not_lt.mp h))
  exact decide_eq_false hgt

theorem table_eq (u : UInt32)
    (hl : (0x0bffffff : UInt32) ≤ R2W01b.magnitude u - 1)
    (hh : R2W01b.magnitude u < (0x7f800000 : UInt32)) :
    R2W01b.tableProduct u = Float32.ofBits u := by
  have h := R2W01c.convert_eq u
  have hg : R2W01b.fastOK u = true := by simp [R2W01b.fastOK, hl, hh]
  simpa only [R2W01b.convert, if_pos hg] using h

/-- The native accumulator may already be canonical NaN. Only the original input is classified. -/
theorem native_step_eq (acc : Float32) (q : Binary32) (value : Float32)
    (hv : value = ExecFloat.Binary.toFloat32 q)
    (hq : R7W12.rawNotNaN q.raw.1 = true) :
    ExecFloat.Binary.ofFloat32 (acc + value) =
      Submission.add (ExecFloat.Binary.ofFloat32 acc) q := by
  have hn : (ExecFloat.Binary.toFloat32 q).isNaN = false := by
    apply Bool.not_inj
    exact (R7W12.rawNotNaN_eq_native_classifier q).symm.trans hq
  rw [hv, R7W12.ofFloat32_add, NotNaNProbe.roundtrip q hn, Submission.add_eq]

/-- A first raw NaN input produces a quiet result, including after earlier invalid arithmetic. -/
theorem repair_quiet (acc : Float32) (q : Binary32)
    (hq : R7W12.rawNotNaN q.raw.1 = false) :
    Model.isQNaN (ExecFloat.Binary.toModel
      (Submission.add (ExecFloat.Binary.ofFloat32 acc) q)) = true := by
  have hn : (ExecFloat.Binary.toFloat32 q).isNaN = true := by
    apply Bool.not_inj
    exact (R7W12.rawNotNaN_eq_native_classifier q).symm.trans hq
  have he : (R7W05.nativeSumStep acc q).isNaN = true := by
    unfold R7W05.nativeSumStep
    rw [R7W05.native_add_nan_right _ _ hn]
    rfl
  simpa only [R7W05.repairSumStep, Submission.add_eq] using
    R7W05.repairSumStep_isQNaN acc q he

/-- Preserve existing decoder decisions; classify Inf versus NaN only in its high cold branch. -/
def natLoop {n : Nat} (x : Vector Binary32 n) (k : Nat) (acc : Float32) : Binary32 :=
  if hk : k < n then
    let q := x.get ⟨k, hk⟩
    let u := q.raw.1
    let a := R2W01b.magnitude u
    if hl : (0x0bffffff : UInt32) ≤ a - 1 then
      if hh : a < (0x7f800000 : UInt32) then
        natLoop x (k + 1) (acc + R2W01b.tableProduct u)
      else if hi : a = (0x7f800000 : UInt32) then
        natLoop x (k + 1) (acc + Float32.ofBits u)
      else R7SumRepair.suffixLoop x (k + 1)
        (Submission.add (ExecFloat.Binary.ofFloat32 acc) q)
    else natLoop x (k + 1) (acc + Float32.ofBits u)
  else ExecFloat.Binary.ofFloat32 acc
termination_by n - k

theorem natLoop_eq {n : Nat} (x : Vector Binary32 n) (k : Nat) (acc : Float32) :
    natLoop x k acc =
      Fin.foldl.loop n (R7SumRepair.step x) (ExecFloat.Binary.ofFloat32 acc) k := by
  rw [natLoop]
  split
  · rename_i hk
    rw [Fin.foldl.loop, dif_pos hk]
    dsimp only
    split
    · rename_i hl
      split
      · rename_i hh
        have ih := natLoop_eq x (k + 1)
          (acc + R2W01b.tableProduct (x.get ⟨k, hk⟩).raw.1)
        have hv : R2W01b.tableProduct (x.get ⟨k, hk⟩).raw.1 =
            ExecFloat.Binary.toFloat32 (x.get ⟨k, hk⟩) := by
          simpa only [ExecFloat.Binary.toFloat32, ExecFloat.Binary.toBits32] using
            table_eq (x.get ⟨k, hk⟩).raw.1 hl hh
        have hs := native_step_eq acc (x.get ⟨k, hk⟩)
          (R2W01b.tableProduct (x.get ⟨k, hk⟩).raw.1) hv
          (raw_nonNaN_of_le _ (UInt32.le_of_lt hh))
        exact ih.trans (congrArg
          (fun a : Binary32 => Fin.foldl.loop n (R7SumRepair.step x) a (k + 1)) hs)
      · rename_i hh
        split
        · rename_i hinf
          have hle : R2W01b.magnitude (x.get ⟨k, hk⟩).raw.1 ≤
              (0x7f800000 : UInt32) := UInt32.le_of_eq hinf
          have ih := natLoop_eq x (k + 1)
            (acc + Float32.ofBits (x.get ⟨k, hk⟩).raw.1)
          have hs := native_step_eq acc (x.get ⟨k, hk⟩)
            (Float32.ofBits (x.get ⟨k, hk⟩).raw.1) rfl (raw_nonNaN_of_le _ hle)
          exact ih.trans (congrArg
            (fun a : Binary32 => Fin.foldl.loop n (R7SumRepair.step x) a (k + 1)) hs)
        · rename_i hinf
          exact R7SumRepair.suffixLoop_eq x (k + 1) _
            (repair_quiet acc (x.get ⟨k, hk⟩) (raw_nan_of_high_reject _ hh hinf))
    · rename_i hl
      have hle := UInt32.le_of_lt (low_reject_finite _ hl)
      have ih := natLoop_eq x (k + 1)
        (acc + Float32.ofBits (x.get ⟨k, hk⟩).raw.1)
      have hs := native_step_eq acc (x.get ⟨k, hk⟩)
        (Float32.ofBits (x.get ⟨k, hk⟩).raw.1) rfl (raw_nonNaN_of_le _ hle)
      exact ih.trans (congrArg
        (fun a : Binary32 => Fin.foldl.loop n (R7SumRepair.step x) a (k + 1)) hs)
  · rename_i hk
    rw [Fin.foldl.loop, dif_neg hk]
termination_by n - k

/-- Machine-indexed ordinary prefix, with a cold transition to the proven raw suffix scan. -/
def loop {n : Nat} (x : Vector Binary32 n) (count : USize)
    (hn : count.toNat = n) (k : USize) (acc : Float32) : Binary32 :=
  if hk : k < count then
    have hkn : k.toNat < n := by rw [← hn]; exact USize.lt_iff_toNat_lt.mp hk
    let q := x.toArray.uget k (by simpa only [x.size_toArray] using hkn)
    let u := q.raw.1
    let a := R2W01b.magnitude u
    if hl : (0x0bffffff : UInt32) ≤ a - 1 then
      if hh : a < (0x7f800000 : UInt32) then
        loop x count hn (k + 1) (acc + R2W01b.tableProduct u)
      else if hi : a = (0x7f800000 : UInt32) then
        loop x count hn (k + 1) (acc + Float32.ofBits u)
      else R7SumRepair.suffixLoop x (k.toNat + 1)
        (Submission.add (ExecFloat.Binary.ofFloat32 acc) q)
    else loop x count hn (k + 1) (acc + Float32.ofBits u)
  else ExecFloat.Binary.ofFloat32 acc
termination_by count.toNat - k.toNat
decreasing_by all_goals exact Packed10Index.next_decreases (by assumption)

theorem loop_eq {n : Nat} (x : Vector Binary32 n) (count : USize)
    (hn : count.toNat = n) (k : USize) (acc : Float32) :
    loop x count hn k acc = natLoop x k.toNat acc := by
  rw [loop]
  split
  · rename_i hk
    have hkn : k.toNat < n := by rw [← hn]; exact USize.lt_iff_toNat_lt.mp hk
    rw [natLoop, dif_pos hkn]
    dsimp only
    have hread : x.toArray.uget k (by simpa only [x.size_toArray] using hkn) =
        x.get ⟨k.toNat, hkn⟩ := by rfl
    rw [hread]
    by_cases hl : (0x0bffffff : UInt32) ≤ R2W01b.magnitude (x.get ⟨k.toNat, hkn⟩).raw.1 - 1
    · simp only [dif_pos hl, if_pos hl]
      by_cases hh : R2W01b.magnitude (x.get ⟨k.toNat, hkn⟩).raw.1 < (0x7f800000 : UInt32)
      · simp only [dif_pos hh, if_pos hh]
        rw [loop_eq, Packed10Index.stepNat hk]
      · simp only [dif_neg hh, if_neg hh]
        by_cases hi : R2W01b.magnitude (x.get ⟨k.toNat, hkn⟩).raw.1 = (0x7f800000 : UInt32)
        · simp only [dif_pos hi, if_pos hi]
          rw [loop_eq, Packed10Index.stepNat hk]
        · simp only [dif_neg hi, if_neg hi]
    · simp only [dif_neg hl, if_neg hl]
      rw [loop_eq, Packed10Index.stepNat hk]
  · rename_i hk
    have hkn : ¬ k.toNat < n := by
      rw [← hn]
      simpa only [USize.lt_iff_toNat_lt] using hk
    rw [natLoop, dif_neg hkn]
termination_by count.toNat - k.toNat
decreasing_by all_goals exact Packed10Index.next_decreases (by assumption)

@[inline] def run {n : Nat} (x : Vector Binary32 n) : Binary32 :=
  if hn : n < USize.size then
    loop x (USize.ofNat n) (USize.toNat_ofNat_of_lt' hn) 0 (Float32.ofBits 0)
  else natLoop x 0 (Float32.ofBits 0)

theorem run_spec : ∀ (n : Nat) (x : Vector Binary32 n), run x = sumSpec x.get := by
  intro n x
  have hrun : run x = natLoop x 0 (Float32.ofBits 0) := by
    unfold run
    split
    · rw [loop_eq, USize.toNat_zero]
    · rfl
  rw [hrun, natLoop_eq]
  have hstep : R7SumRepair.step x = fun (acc : Binary32) (i : Fin n) =>
      ExecFloat.add acc (x.get i) := by
    funext acc i
    exact congrArg (fun f : Binary32 → Binary32 → Binary32 => f acc (x.get i))
      Submission.add_eq
  change Fin.foldl n (R7SumRepair.step x) posZero = sumSpec x.get
  rw [hstep, Fin.foldl_eq_finRange_foldl]
  rfl

end R7SinglePassSum

open FloatLib.Floats Competition

def sum {n : Nat} (x : Vector Binary32 n) : Binary32 := R7SinglePassSum.run x

theorem sum_spec : ∀ (n : Nat) (x : Vector Binary32 n), sum x = sumSpec x.get := R7SinglePassSum.run_spec

end Submission


namespace Submission.DirectRows
open FloatLib.Floats Competition

def core (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Vector Binary32 (batch * m * p) :=
  (Vector.ofFn fun r : Fin (batch * m) => r).flatMap fun r =>
    let b := r.val / m
    let i := r.val % m
    let baseA := (b * m + i) * n
    let baseB := b * n * p
    Vector.ofFn fun j : Fin p =>
      NativeFinal.dot n baseA (baseB + j.val) p A.toArray B.toArray

theorem core_eq (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) :
    core batch m n p A B = DirectSmall.core batch m n p A B := by
  apply Vector.ext
  intro q hq
  have hmp : m * p ≠ 0 := by
    intro h
    have hq' : q < batch * (m * p) := by simpa only [Nat.mul_assoc] using hq
    rw [h, Nat.mul_zero] at hq'
    omega
  have hp : p ≠ 0 := by
    intro h
    apply hmp
    simp only [h, Nat.mul_zero]
  simp only [core, DirectSmall.core, Vector.getElem_flatMap,
    Vector.getElem_ofFn, bmmDecodeC, hmp, hp, if_false,
    Nat.div_div_eq_div_mul, Nat.mul_comm p m,
    Nat.mod_mul_left_div_self, Nat.mod_mul_left_mod]

end Submission.DirectRows

namespace Submission.DirectContinuous

open FloatLib.Floats Competition

/-- Read the original inputs and finish each scalar dot directly into one array. -/
@[inline] def row (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (out : Array Binary32) (r : Fin (batch * m)) : Array Binary32 :=
  let baseA := r.val * n
  let baseB := r.val / m * n * p
  RowStream.emit p (fun j =>
    NativeFinal.dot n baseA (baseB + j.val) p A.toArray B.toArray) out

theorem row_prefix (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (out : Array Binary32) (r : Fin (batch * m))
    (hout : RowStream.Prefix (RowStream.point batch m n p A B) (r.val * p) out) :
    RowStream.Prefix (RowStream.point batch m n p A B) ((r.val + 1) * p)
      (row batch m n p A B out r) := by
  have hm : 0 < m := Nat.pos_of_lt_mul_left r.isLt
  have h := RowStream.emit_prefix (RowStream.point batch m n p A B)
    (r.val * p) p
    (fun j : Fin p => NativeFinal.dot n (r.val * n)
      (r.val / m * n * p + j.val) p A.toArray B.toArray) out hout
    (by
      intro j
      have hp : 0 < p := Nat.zero_lt_of_lt j.isLt
      exact (RowStream.point_row batch m n p A B r.val j.val hm hp j.isLt).symm)
  simpa only [row, Nat.add_mul, Nat.one_mul] using h

def output (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Array Binary32 :=
  Fin.foldl (batch * m) (row batch m n p A B)
    (Array.mkEmpty (batch * m * p))

theorem output_prefix (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) :
    RowStream.Prefix (RowStream.point batch m n p A B) (batch * m * p)
      (output batch m n p A B) := by
  exact RowStream.foldl_inv (batch * m) (row batch m n p A B)
    (fun r acc => RowStream.Prefix (RowStream.point batch m n p A B) (r * p) acc)
    (fun r acc hacc => row_prefix batch m n p A B acc r hacc)
    (Array.mkEmpty (batch * m * p))
    ⟨by simp, by intro j hj; simp at hj⟩

def core (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Vector Binary32 (batch * m * p) :=
  ⟨output batch m n p A B, (output_prefix batch m n p A B).1⟩

theorem core_eq_reference (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) :
    core batch m n p A B = referenceBmm batch m n p A B := by
  exact (RowStream.prefix_vector_eq_ofFn (RowStream.point batch m n p A B)
    (batch * m * p) (output batch m n p A B) (output_prefix batch m n p A B)).trans
    (RowStream.points_eq_reference batch m n p A B)

end Submission.DirectContinuous

namespace Submission
open FloatLib.Floats Competition

def bmmBeforeR11Cross (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Vector Binary32 (batch * m * p) :=
  if n ≤ 4 ∧ 2 < p then DirectContinuous.core batch m n p A B
  else bmmBeforeDirectRows batch m n p A B

theorem bmmBeforeR11Cross_spec : ∀ (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)),
    (bmmBeforeR11Cross batch m n p A B).get = bmmSpec batch m n p A.get B.get := by
  intro batch m n p A B
  unfold bmmBeforeR11Cross
  split
  · rw [DirectContinuous.core_eq_reference]
    exact referenceBmm_spec batch m n p A B
  · exact bmmBeforeDirectRows_spec batch m n p A B

end Submission


/- R11 cross-row p=2 kernel. Four independent row instances, including across
   batch boundaries; each output retains its own ordered mul/add chain. -/
namespace Submission.R11CrossRows
open FloatLib.Floats Competition

structure P12 where
  a0 : Float32
  a1 : Float32
  a2 : Float32
  a3 : Float32
  b0 : Float32
  b1 : Float32
  b2 : Float32
  b3 : Float32
  b4 : Float32
  b5 : Float32
  b6 : Float32
  b7 : Float32

structure F8 where
  s0 : Float32
  s1 : Float32
  s2 : Float32
  s3 : Float32
  s4 : Float32
  s5 : Float32
  s6 : Float32
  s7 : Float32

structure W8 where
  w0 : UInt32
  w1 : UInt32
  w2 : UInt32
  w3 : UInt32
  w4 : UInt32
  w5 : UInt32
  w6 : UInt32
  w7 : UInt32

def select4 (x0 x1 x2 x3 r : Nat) : Nat :=
  match r with | 0 => x0 | 1 => x1 | 2 => x2 | _ => x3

def lane (v : F8) (l : Fin 8) : Float32 :=
  match l.val with
  | 0 => v.s0 | 1 => v.s1 | 2 => v.s2 | 3 => v.s3
  | 4 => v.s4 | 5 => v.s5 | 6 => v.s6 | _ => v.s7

def inputA (v : P12) (l : Fin 8) : Float32 :=
  match l.val % 4 with | 0 => v.a0 | 1 => v.a1 | 2 => v.a2 | _ => v.a3

def inputB (v : P12) (l : Fin 8) : Float32 :=
  match l.val with
  | 0 => v.b0 | 1 => v.b1 | 2 => v.b2 | 3 => v.b3
  | 4 => v.b4 | 5 => v.b5 | 6 => v.b6 | _ => v.b7

def zero8 : F8 :=
  let z := Float32.ofBits 0
  ⟨z,z,z,z,z,z,z,z⟩

def update (s : F8) (v : P12) : F8 :=
  ⟨s.s0 + v.a0 * v.b0, s.s1 + v.a1 * v.b1,
   s.s2 + v.a2 * v.b2, s.s3 + v.a3 * v.b3,
   s.s4 + v.a0 * v.b4, s.s5 + v.a1 * v.b5,
   s.s6 + v.a2 * v.b6, s.s7 + v.a3 * v.b7⟩

theorem lane_zero (l : Fin 8) : lane zero8 l = Float32.ofBits 0 := by
  rcases l with ⟨l,hl⟩
  have h : l=0 ∨ l=1 ∨ l=2 ∨ l=3 ∨ l=4 ∨ l=5 ∨ l=6 ∨ l=7 := by omega
  rcases h with rfl|rfl|rfl|rfl|rfl|rfl|rfl|rfl <;> rfl

theorem lane_update (s : F8) (v : P12) (l : Fin 8) :
    lane (update s v) l = lane s l + inputA v l * inputB v l := by
  rcases l with ⟨l,hl⟩
  have h : l=0 ∨ l=1 ∨ l=2 ∨ l=3 ∨ l=4 ∨ l=5 ∨ l=6 ∨ l=7 := by omega
  rcases h with rfl|rfl|rfl|rfl|rfl|rfl|rfl|rfl <;>
    simp [lane, update, inputA, inputB]

def packGeneral (n p a0 a1 a2 a3 b0 b1 b2 b3 : Nat) (A B : Array Binary32) : Vector P12 n :=
  Vector.ofFn fun k =>
    let kp := k.val * p
    ⟨ExecFloat.Binary.toFloat32 (A.getD (a0+k.val) posZero),
     ExecFloat.Binary.toFloat32 (A.getD (a1+k.val) posZero),
     ExecFloat.Binary.toFloat32 (A.getD (a2+k.val) posZero),
     ExecFloat.Binary.toFloat32 (A.getD (a3+k.val) posZero),
     ExecFloat.Binary.toFloat32 (B.getD (b0+kp) posZero),
     ExecFloat.Binary.toFloat32 (B.getD (b1+kp) posZero),
     ExecFloat.Binary.toFloat32 (B.getD (b2+kp) posZero),
     ExecFloat.Binary.toFloat32 (B.getD (b3+kp) posZero),
     ExecFloat.Binary.toFloat32 (B.getD ((b0+1)+kp) posZero),
     ExecFloat.Binary.toFloat32 (B.getD ((b1+1)+kp) posZero),
     ExecFloat.Binary.toFloat32 (B.getD ((b2+1)+kp) posZero),
     ExecFloat.Binary.toFloat32 (B.getD ((b3+1)+kp) posZero)⟩

theorem packGeneral_a (n p a0 a1 a2 a3 b0 b1 b2 b3 : Nat) (A B : Array Binary32)
    (k : Fin n) (l : Fin 8) :
    inputA ((packGeneral n p a0 a1 a2 a3 b0 b1 b2 b3 A B).get k) l =
      ExecFloat.Binary.toFloat32 (A.getD (select4 a0 a1 a2 a3 (l.val%4)+k.val) posZero) := by
  rcases l with ⟨l,hl⟩
  have h : l=0 ∨ l=1 ∨ l=2 ∨ l=3 ∨ l=4 ∨ l=5 ∨ l=6 ∨ l=7 := by omega
  rcases h with rfl|rfl|rfl|rfl|rfl|rfl|rfl|rfl <;>
    simp [packGeneral, Packed10.vector_get_ofFn, inputA, select4]

theorem packGeneral_b (n p a0 a1 a2 a3 b0 b1 b2 b3 : Nat) (A B : Array Binary32)
    (k : Fin n) (l : Fin 8) :
    inputB ((packGeneral n p a0 a1 a2 a3 b0 b1 b2 b3 A B).get k) l =
      ExecFloat.Binary.toFloat32
        (B.getD ((select4 b0 b1 b2 b3 (l.val%4)+l.val/4)+k.val*p) posZero) := by
  rcases l with ⟨l,hl⟩
  have h : l=0 ∨ l=1 ∨ l=2 ∨ l=3 ∨ l=4 ∨ l=5 ∨ l=6 ∨ l=7 := by omega
  rcases h with rfl|rfl|rfl|rfl|rfl|rfl|rfl|rfl <;>
    simp [packGeneral, Packed10.vector_get_ofFn, inputB, select4]


def packShared (n p a0 a1 a2 a3 b0 : Nat) (A B : Array Binary32) : Vector P12 n :=
  Vector.ofFn fun k =>
    let kp := k.val*p
    let c0 := ExecFloat.Binary.toFloat32 (B.getD (b0+kp) posZero)
    let c1 := ExecFloat.Binary.toFloat32 (B.getD ((b0+1)+kp) posZero)
    ⟨ExecFloat.Binary.toFloat32 (A.getD (a0+k.val) posZero),
     ExecFloat.Binary.toFloat32 (A.getD (a1+k.val) posZero),
     ExecFloat.Binary.toFloat32 (A.getD (a2+k.val) posZero),
     ExecFloat.Binary.toFloat32 (A.getD (a3+k.val) posZero),
     c0,c0,c0,c0,c1,c1,c1,c1⟩

theorem packShared_eq (n p a0 a1 a2 a3 b0 : Nat) (A B : Array Binary32) :
    packShared n p a0 a1 a2 a3 b0 A B =
      packGeneral n p a0 a1 a2 a3 b0 b0 b0 b0 A B := by rfl

def pack (n p a0 a1 a2 a3 b0 b1 b2 b3 : Nat) (A B : Array Binary32) : Vector P12 n :=
  if b1=b0 ∧ b2=b0 ∧ b3=b0 then packShared n p a0 a1 a2 a3 b0 A B
  else packGeneral n p a0 a1 a2 a3 b0 b1 b2 b3 A B

theorem pack_eq_general (n p a0 a1 a2 a3 b0 b1 b2 b3 : Nat) (A B : Array Binary32) :
    pack n p a0 a1 a2 a3 b0 b1 b2 b3 A B = packGeneral n p a0 a1 a2 a3 b0 b1 b2 b3 A B := by
  unfold pack
  split
  · rename_i h
    rcases h with ⟨h1,h2,h3⟩
    subst b1; subst b2; subst b3
    exact packShared_eq n p a0 a1 a2 a3 b0 A B
  · rfl

theorem pack_a (n p a0 a1 a2 a3 b0 b1 b2 b3 : Nat) (A B : Array Binary32)
    (k : Fin n) (l : Fin 8) :
    inputA ((pack n p a0 a1 a2 a3 b0 b1 b2 b3 A B).get k) l =
      ExecFloat.Binary.toFloat32 (A.getD (select4 a0 a1 a2 a3 (l.val%4)+k.val) posZero) := by
  rw [pack_eq_general]
  exact packGeneral_a n p a0 a1 a2 a3 b0 b1 b2 b3 A B k l

theorem pack_b (n p a0 a1 a2 a3 b0 b1 b2 b3 : Nat) (A B : Array Binary32)
    (k : Fin n) (l : Fin 8) :
    inputB ((pack n p a0 a1 a2 a3 b0 b1 b2 b3 A B).get k) l =
      ExecFloat.Binary.toFloat32
        (B.getD ((select4 b0 b1 b2 b3 (l.val%4)+l.val/4)+k.val*p) posZero) := by
  rw [pack_eq_general]
  exact packGeneral_b n p a0 a1 a2 a3 b0 b1 b2 b3 A B k l

def natLoop (n : Nat) (v : Vector P12 n) (k : Nat) (s : F8) : F8 :=
  if hk : k<n then natLoop n v (k+1) (update s (v.get ⟨k,hk⟩)) else s
termination_by n-k

theorem natLoop_lane (n p a0 a1 a2 a3 b0 b1 b2 b3 : Nat) (A B : Array Binary32)
    (k : Nat) (s : F8) (l : Fin 8) :
    lane (natLoop n (pack n p a0 a1 a2 a3 b0 b1 b2 b3 A B) k s) l =
      NativeFinal.dotLoop n (select4 a0 a1 a2 a3 (l.val%4))
        (select4 b0 b1 b2 b3 (l.val%4)+l.val/4) p A B k (lane s l) := by
  rw [natLoop]
  split
  · rename_i hk
    rw [NativeFinal.dotLoop, dif_pos hk]
    dsimp only
    have ih := natLoop_lane n p a0 a1 a2 a3 b0 b1 b2 b3 A B (k+1)
      (update s ((pack n p a0 a1 a2 a3 b0 b1 b2 b3 A B).get ⟨k,hk⟩)) l
    rw [lane_update, pack_a, pack_b] at ih
    exact ih
  · rename_i hk
    rw [NativeFinal.dotLoop, dif_neg hk]
termination_by n-k

def wordLoop (n : Nat) (v : Vector P12 n) (count : USize) (hn : count.toNat=n)
    (k : USize) (s0 s1 s2 s3 s4 s5 s6 s7 : Float32) : F8 :=
  if hk : k<count then
    have hkn : k.toNat<n := by rw [← hn]; exact USize.lt_iff_toNat_lt.mp hk
    let t := v.toArray.uget k (by simpa only [v.size_toArray] using hkn)
    wordLoop n v count hn (k+1)
      (s0+t.a0*t.b0) (s1+t.a1*t.b1) (s2+t.a2*t.b2) (s3+t.a3*t.b3)
      (s4+t.a0*t.b4) (s5+t.a1*t.b5) (s6+t.a2*t.b6) (s7+t.a3*t.b7)
  else ⟨s0,s1,s2,s3,s4,s5,s6,s7⟩
termination_by count.toNat-k.toNat
decreasing_by all_goals exact Packed10Index.next_decreases (by assumption)

theorem wordLoop_eq (n : Nat) (v : Vector P12 n) (count : USize) (hn : count.toNat=n)
    (k : USize) (s0 s1 s2 s3 s4 s5 s6 s7 : Float32) :
    wordLoop n v count hn k s0 s1 s2 s3 s4 s5 s6 s7 =
      natLoop n v k.toNat ⟨s0,s1,s2,s3,s4,s5,s6,s7⟩ := by
  rw [wordLoop]
  split
  · rename_i hk
    have hkn : k.toNat<n := by rw [← hn]; exact USize.lt_iff_toNat_lt.mp hk
    have hread : v.toArray.uget k (by simpa only [v.size_toArray] using hkn) =
        v.get ⟨k.toNat,hkn⟩ := rfl
    rw [natLoop, dif_pos hkn]
    dsimp only [update]
    rw [hread, wordLoop_eq, Packed10Index.stepNat hk]
  · rename_i hk
    have hkn : ¬k.toNat<n := by
      rw [← hn]
      simpa only [USize.lt_iff_toNat_lt] using hk
    rw [natLoop, dif_neg hkn]
termination_by count.toNat-k.toNat
decreasing_by all_goals exact Packed10Index.next_decreases (by assumption)

def dot8 (n p a0 a1 a2 a3 b0 b1 b2 b3 : Nat) (A B : Array Binary32)
    (hn : n<USize.size) : F8 :=
  let v := pack n p a0 a1 a2 a3 b0 b1 b2 b3 A B
  let z := Float32.ofBits 0
  wordLoop n v (USize.ofNat n) (USize.toNat_ofNat_of_lt' hn) 0 z z z z z z z z

theorem dot8_lane (n p a0 a1 a2 a3 b0 b1 b2 b3 : Nat) (A B : Array Binary32)
    (hn : n<USize.size) (l : Fin 8) :
    lane (dot8 n p a0 a1 a2 a3 b0 b1 b2 b3 A B hn) l =
      NativeFinal.dotLoop n (select4 a0 a1 a2 a3 (l.val%4))
        (select4 b0 b1 b2 b3 (l.val%4)+l.val/4) p A B 0 (Float32.ofBits 0) := by
  unfold dot8
  rw [wordLoop_eq, USize.toNat_zero]
  have h := natLoop_lane n p a0 a1 a2 a3 b0 b1 b2 b3 A B 0 zero8 l
  rw [lane_zero] at h
  simpa only [zero8] using h

def laneIndex (r : Fin 4) (j : Fin 2) : Fin 8 :=
  ⟨r.val+4*j.val, by have hr:=r.isLt; have hj:=j.isLt; omega⟩

def wordAt (v : W8) (r : Fin 4) (j : Fin 2) : UInt32 :=
  match r.val with
  | 0 => if j.val=0 then v.w0 else v.w1
  | 1 => if j.val=0 then v.w2 else v.w3
  | 2 => if j.val=0 then v.w4 else v.w5
  | _ => if j.val=0 then v.w6 else v.w7

theorem rebuild (q : Binary32) : ExecFloat.Binary.ofBits32 q.raw.1 = q :=
  ExecFloat.Binary.ofBits32_toBits32 q

def finish8 (n p a0 a1 a2 a3 b0 b1 b2 b3 : Nat) (A B : Array Binary32) (s : F8) : W8 :=
  ⟨(Packed10.finish n a0 b0 p A B s.s0).raw.1,
   (Packed10.finish n a0 (b0+1) p A B s.s4).raw.1,
   (Packed10.finish n a1 b1 p A B s.s1).raw.1,
   (Packed10.finish n a1 (b1+1) p A B s.s5).raw.1,
   (Packed10.finish n a2 b2 p A B s.s2).raw.1,
   (Packed10.finish n a2 (b2+1) p A B s.s6).raw.1,
   (Packed10.finish n a3 b3 p A B s.s3).raw.1,
   (Packed10.finish n a3 (b3+1) p A B s.s7).raw.1⟩

theorem finish8_word (n p a0 a1 a2 a3 b0 b1 b2 b3 : Nat) (A B : Array Binary32)
    (s : F8) (r : Fin 4) (j : Fin 2) :
    ExecFloat.Binary.ofBits32 (wordAt (finish8 n p a0 a1 a2 a3 b0 b1 b2 b3 A B s) r j) =
      Packed10.finish n (select4 a0 a1 a2 a3 r.val) (select4 b0 b1 b2 b3 r.val+j.val)
        p A B (lane s (laneIndex r j)) := by
  rcases r with ⟨r,hr⟩; rcases j with ⟨j,hj⟩
  have h : r=0 ∨ r=1 ∨ r=2 ∨ r=3 := by omega
  have hc : j=0 ∨ j=1 := by omega
  rcases h with rfl|rfl|rfl|rfl <;> rcases hc with rfl|rfl <;>
    simp [finish8, wordAt, select4, lane, laneIndex, rebuild]

def blockAt (n p a0 a1 a2 a3 b0 b1 b2 b3 : Nat) (A B : Array Binary32)
    (hn : n<USize.size) : W8 :=
  finish8 n p a0 a1 a2 a3 b0 b1 b2 b3 A B
    (dot8 n p a0 a1 a2 a3 b0 b1 b2 b3 A B hn)

theorem blockAt_word (n p a0 a1 a2 a3 b0 b1 b2 b3 : Nat) (A B : Array Binary32)
    (hn : n<USize.size) (r : Fin 4) (j : Fin 2) :
    ExecFloat.Binary.ofBits32 (wordAt (blockAt n p a0 a1 a2 a3 b0 b1 b2 b3 A B hn) r j) =
      NativeFinal.dot n (select4 a0 a1 a2 a3 r.val) (select4 b0 b1 b2 b3 r.val+j.val) p A B := by
  unfold blockAt
  rw [finish8_word]
  apply Packed10.finish_eq_dot
  have h := dot8_lane n p a0 a1 a2 a3 b0 b1 b2 b3 A B hn (laneIndex r j)
  rcases r with ⟨r,hr⟩; rcases j with ⟨j,hj⟩
  have hrow : r=0 ∨ r=1 ∨ r=2 ∨ r=3 := by omega
  have hcol : j=0 ∨ j=1 := by omega
  rcases hrow with rfl|rfl|rfl|rfl <;> rcases hcol with rfl|rfl <;>
    simpa [laneIndex, select4, Packed10.zero32] using h

def blockRows (m n p g : Nat) (A B : Array Binary32) (hn : n<USize.size) : W8 :=
  let r0 := 4*g
  let r1 := 4*g+1
  let r2 := 4*g+2
  let r3 := 4*g+3
  blockAt n p (r0*n) (r1*n) (r2*n) (r3*n)
    (r0/m*n*p) (r1/m*n*p) (r2/m*n*p) (r3/m*n*p) A B hn

theorem blockRows_word (m n p g : Nat) (A B : Array Binary32) (hn : n<USize.size)
    (r : Fin 4) (j : Fin 2) :
    ExecFloat.Binary.ofBits32 (wordAt (blockRows m n p g A B hn) r j) =
      NativeFinal.dot n ((4*g+r.val)*n) (((4*g+r.val)/m)*n*p+j.val) p A B := by
  unfold blockRows
  rw [blockAt_word]
  rcases r with ⟨r,hr⟩
  have h : r=0 ∨ r=1 ∨ r=2 ∨ r=3 := by omega
  rcases h with rfl|rfl|rfl|rfl <;> simp [select4]

def groups (rows : Nat) : Nat := (rows+3)/4

theorem group_bound (rows r : Nat) (hr : r<rows) : r/4 < groups rows := by
  unfold groups
  omega

theorem row_decomposition (r : Nat) : 4*(r/4)+r%4=r := by omega

def words (batch m n p : Nat) (A B : Array Binary32) (hn : n<USize.size) :
    Vector W8 (groups (batch*m)) :=
  Vector.ofFn fun g => blockRows m n p g.val A B hn

def rowWord (batch m p : Nat) (v : Vector W8 (groups (batch*m)))
    (r : Fin (batch*m)) (j : Fin p) (hp : p≤2) : Binary32 :=
  let g : Fin (groups (batch*m)) := ⟨r.val/4, group_bound _ _ r.isLt⟩
  let rr : Fin 4 := ⟨r.val%4, Nat.mod_lt _ (by decide)⟩
  let jj : Fin 2 := ⟨j.val, Nat.lt_of_lt_of_le j.isLt hp⟩
  ExecFloat.Binary.ofBits32 (wordAt (v.get g) rr jj)

theorem rowWord_eq (batch m n p : Nat) (A B : Array Binary32) (hn : n<USize.size)
    (r : Fin (batch*m)) (j : Fin p) (hp : p≤2) :
    rowWord batch m p (words batch m n p A B hn) r j hp =
      NativeFinal.dot n ((r.val/m*m+r.val%m)*n) (r.val/m*n*p+j.val) p A B := by
  unfold rowWord words
  dsimp only
  rw [Packed10.vector_get_ofFn, blockRows_word]
  dsimp only
  have hr : r.val/m*m+r.val%m=r.val := by
    simpa only [Nat.mul_comm] using Nat.div_add_mod r.val m
  simp only [row_decomposition, hr]

def core (batch m n p : Nat) (A : Vector Binary32 (batch*m*n))
    (B : Vector Binary32 (batch*n*p)) (hn : n<USize.size) (hp : p≤2) :
    Vector Binary32 (batch*m*p) :=
  let v := words batch m n p A.toArray B.toArray hn
  Vector.ofFn fun q =>
    have hp0 : 0<p := by
      have hq := q.isLt
      by_contra h
      have hz : p=0 := by omega
      simp [hz] at hq
    let r : Fin (batch*m) := ⟨q.val/p, (Nat.div_lt_iff_lt_mul hp0).2 q.isLt⟩
    let j : Fin p := ⟨q.val%p, Nat.mod_lt _ hp0⟩
    rowWord batch m p v r j hp

theorem core_eq_rows (batch m n p : Nat) (A : Vector Binary32 (batch*m*n))
    (B : Vector Binary32 (batch*n*p)) (hn : n<USize.size) (hp : p≤2) :
    core batch m n p A B hn hp = DirectRows.core batch m n p A B := by
  apply Vector.ext
  intro q hq
  have hp0 : 0<p := by
    by_contra h
    have hz : p=0 := by omega
    simp [hz] at hq
  have hr : q/p < batch*m := (Nat.div_lt_iff_lt_mul hp0).2 hq
  have hj : q%p < p := Nat.mod_lt _ hp0
  have h := rowWord_eq batch m n p A.toArray B.toArray hn ⟨q/p,hr⟩ ⟨q%p,hj⟩ hp
  simpa only [core, DirectRows.core, Vector.getElem_ofFn, Vector.getElem_flatMap] using h

end Submission.R11CrossRows

namespace Submission
open FloatLib.Floats Competition

def bmmBeforeUnderflowZero (batch m n p : Nat) (A : Vector Binary32 (batch*m*n))
    (B : Vector Binary32 (batch*n*p)) : Vector Binary32 (batch*m*p) :=
  if h : p=2 ∧ 4≤batch*m ∧ 0<n ∧ n<USize.size ∧
      A.toArray.size<USize.size ∧ B.toArray.size<USize.size ∧ batch*m*p<USize.size then
    R11CrossRows.core batch m n p A B h.2.2.2.1 (Nat.le_of_eq h.1)
  else bmmBeforeR11Cross batch m n p A B

theorem bmmBeforeUnderflowZero_spec : ∀ (batch m n p : Nat) (A : Vector Binary32 (batch*m*n))
    (B : Vector Binary32 (batch*n*p)),
    (bmmBeforeUnderflowZero batch m n p A B).get = bmmSpec batch m n p A.get B.get := by
  intro batch m n p A B
  unfold bmmBeforeUnderflowZero
  split
  · rw [R11CrossRows.core_eq_rows, DirectRows.core_eq, DirectSmall.core_eq_reference]
    exact referenceBmm_spec batch m n p A B
  · exact bmmBeforeR11Cross_spec batch m n p A B

end Submission


namespace Submission.UnderflowZero

open FloatLib.Floats Competition
open FloatLib.Floats.Formats.BinaryInterchange
open Model.NativeBinary32

/-- A sign-independent strict magnitude bound, rejecting all infinities/NaNs. -/
@[inline] def small (x : Binary32) : Bool :=
  R2W01b.magnitude x.raw.1 < (0x16000000 : UInt32)

theorem small_exp (x : Binary32) (h : small x = true) :
    (expField x.raw.1).toNat ≤ 43 := by
  unfold small at h
  simp only [decide_eq_true_eq, UInt32.lt_iff_toNat_lt, R2W01b.magnitude_toNat] at h
  have hw := x.raw.1.toNat_lt
  rw [FastMul.expField_toNat]
  change x.raw.1.toNat / 8388608 % 256 ≤ 43
  change x.raw.1.toNat % 2147483648 < 369098752 at h
  omega

theorem small_posZero : small posZero = true := by decide

theorem small_getD (a : Array Binary32) (ha : a.all small = true) (i : Nat) :
    small (a.getD i posZero) = true := by
  by_cases hi : i < a.size
  · simpa [Array.getD, hi] using (Array.all_eq_true.mp ha) i hi
  · simp [Array.getD, hi, small_posZero]

/- The following scale interpretation proof is ported from FloatLib Team, MIT,
   FiniteProof.lean (captured public R6-W01 source). The dependency is unchanged. -/
theorem finiteScale_toNat (exponent : UInt32) :
    (finiteScale exponent).toNat =
      if exponent = 0 then 0 else exponent.toNat - 1 := by
  by_cases hexponent : exponent = 0
  · subst exponent
    simp [finiteScale, FloatLib.Numerics.FixedWord.finiteScale]
  · have hwidened : exponent.toUInt64 ≠ 0 := by
      intro hzero
      apply hexponent
      apply UInt32.toNat_inj.mp
      have := congrArg UInt64.toNat hzero
      simpa using this
    rw [finiteScale, FloatLib.Numerics.FixedWord.finiteScale_toNat]
    simp [hexponent, hwidened]

theorem scale_small (e : UInt32) (he : e.toNat ≤ 43) :
    (finiteScale e).toNat ≤ 42 := by
  rw [finiteScale_toNat]
  split <;> omega

theorem scale_sum_small (x y : Binary32) (hx : small x = true) (hy : small y = true) :
    (finiteScale (expField x.raw.1) + finiteScale (expField y.raw.1)).toNat ≤ 84 := by
  have hsx := scale_small _ (small_exp x hx)
  have hsy := scale_small _ (small_exp y hy)
  rw [UInt64.toNat_add]
  change ((finiteScale (expField x.raw.1)).toNat +
    (finiteScale (expField y.raw.1)).toNat) % 18446744073709551616 ≤ 84
  rw [Nat.mod_eq_of_lt (by omega)]
  omega

/-- A shift of at least65 returns zero even for an arbitrary 64-bit product. -/
theorem rseAny_zero (product scale : UInt64) (hs : scale.toNat ≤ 84) :
    FastMul.rseAny product (149 - scale) = 0 := by
  have hscale : scale ≤ (149 : UInt64) := by
    rw [UInt64.le_iff_toNat_le]
    change scale.toNat ≤ 149
    omega
  have ht : (149 - scale).toNat = 149 - scale.toNat := by
    rw [UInt64.toNat_sub_of_le _ _ hscale]
    rfl
  have h0 : (149 - scale : UInt64) ≠ 0 := by
    intro h
    have hh := congrArg UInt64.toNat h
    rw [ht] at hh
    change 149 - scale.toNat = 0 at hh
    omega
  have h64 : ¬ (149 - scale : UInt64) < 64 := by
    rw [UInt64.lt_iff_toNat_lt, ht]
    change ¬ 149 - scale.toNat < 64
    omega
  have he64 : (149 - scale : UInt64) ≠ 64 := by
    intro h
    have hh := congrArg UInt64.toNat h
    rw [ht] at hh
    change 149 - scale.toNat = 64 at hh
    omega
  simp [FastMul.rseAny, h0, h64, he64]

/-- No mantissa bound is needed: even a full UInt64 rounds to zero here. -/
theorem roundP_zero (sign : Bool) (product scale : UInt64) (hs : scale.toNat ≤ 84) :
    FastMul.roundP sign product scale = (if sign then 0x80000000 else 0) := by
  have hl : (FastMul.fastLog2 product).toNat < 64 := by
    rw [FastMul.fastLog2_eq]
    exact FastMul.log2_lt_64 product
  have hposition : FastMul.fastLog2 product + scale < (172 : UInt64) := by
    rw [UInt64.lt_iff_toNat_lt, UInt64.toNat_add]
    change ((FastMul.fastLog2 product).toNat + scale.toNat) %
      18446744073709551616 < 172
    rw [Nat.mod_eq_of_lt (by omega)]
    omega
  have hscale : scale < (149 : UInt64) := by
    rw [UInt64.lt_iff_toNat_lt]
    change scale.toNat < 149
    omega
  have hf := rseAny_zero product scale hs
  simp [FastMul.roundP, hposition, hscale, hf]

theorem mul_signed_zero (x y : Binary32) (hx : small x = true) (hy : small y = true) :
    ExecFloat.mul x y = FastMul.ofBits
      (if Bool.xor (signBit x.raw.1) (signBit y.raw.1) then 0x80000000 else 0) := by
  have hxe : expField x.raw.1 ≠ 0xff := by
    intro h
    have hs := small_exp x hx
    have hh := congrArg UInt32.toNat h
    change (expField x.raw.1).toNat = 255 at hh
    omega
  have hye : expField y.raw.1 ≠ 0xff := by
    intro h
    have hs := small_exp y hy
    have hh := congrArg UInt32.toNat h
    change (expField y.raw.1).toNat = 255 at hh
    omega
  have hspecial : FastMul.special x.raw.1 y.raw.1 = false := by
    simp [FastMul.special, FastMul.sm1_eq, hxe, hye]
  have heq : ExecFloat.mul x y = FastMul.mul x y :=
    (ExecFloat.Proof.mul_eq_spec x y).trans (FastMul.mul_spec x y).symm
  rw [heq]
  simp only [FastMul.mul, hspecial, Bool.false_eq_true, ite_false, FastMul.core]
  congr 1
  exact roundP_zero _ _ _ (scale_sum_small x y hx hy)

theorem add_signed_zero (sign : Bool) :
    ExecFloat.add posZero (FastMul.ofBits (if sign then 0x80000000 else 0)) = posZero := by
  cases sign <;> decide

theorem add_mul_zero (x y : Binary32) (hx : small x = true) (hy : small y = true) :
    ExecFloat.add posZero (ExecFloat.mul x y) = posZero := by
  rw [mul_signed_zero x y hx hy]
  exact add_signed_zero _

theorem foldl_loop_zero (n : Nat) (step : Binary32 → Fin n → Binary32)
    (hstep : ∀ i, step posZero i = posZero) (k : Nat) :
    Fin.foldl.loop n step posZero k = posZero := by
  rw [Fin.foldl.loop]
  split
  · rename_i hk
    rw [hstep ⟨k, hk⟩]
    exact foldl_loop_zero n step hstep (k + 1)
  · rfl
termination_by n - k

theorem foldl_zero (n : Nat) (step : Binary32 → Fin n → Binary32)
    (hstep : ∀ i, step posZero i = posZero) :
    Fin.foldl n step posZero = posZero :=
  foldl_loop_zero n step hstep 0

def zeros (batch m p : Nat) : Vector Binary32 (batch * m * p) :=
  Vector.replicate (batch * m * p) posZero

theorem zeros_eq_reference (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n)) (B : Vector Binary32 (batch * n * p))
    (ha : A.toArray.all small = true) (hb : B.toArray.all small = true) :
    zeros batch m p = referenceBmm batch m n p A B := by
  apply Vector.ext
  intro q hq
  simp only [zeros, Vector.getElem_replicate, referenceBmm, Vector.getElem_ofFn,
    Submission.add_eq, Submission.mul_eq]
  symm
  apply foldl_zero
  intro k
  exact add_mul_zero _ _ (small_getD A.toArray ha _) (small_getD B.toArray hb _)

end Submission.UnderflowZero

namespace Submission
open FloatLib.Floats Competition

/-- Both short-circuiting scans and the zero fill are inside the timed entry. -/
def bmm (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Vector Binary32 (batch * m * p) :=
  if A.toArray.all UnderflowZero.small && B.toArray.all UnderflowZero.small then
    UnderflowZero.zeros batch m p
  else bmmBeforeUnderflowZero batch m n p A B

theorem bmm_spec : ∀ (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)),
    (bmm batch m n p A B).get = bmmSpec batch m n p A.get B.get := by
  intro batch m n p A B
  unfold bmm
  split
  · rename_i h
    have hh : A.toArray.all UnderflowZero.small = true ∧
        B.toArray.all UnderflowZero.small = true := by
      simpa only [Bool.and_eq_true] using h
    rw [UnderflowZero.zeros_eq_reference batch m n p A B hh.1 hh.2]
    exact referenceBmm_spec batch m n p A B
  · exact bmmBeforeUnderflowZero_spec batch m n p A B

end Submission
