import ContractTensor

/- R14 common-rounding proof fragment -- NOT_RUN / UNVERIFIED.
Lean 4.34.0: 293d5d0c0c3f3dded4688b3ccd6a33939ac5102b
FloatLib: 0d91825727839f597fd06b22fdd038ea21480f0c
Source input SHA256:
9de663c43f518aa0dbd09b5336f28d46a68e943138d739223a2cbd0f163f2a4e

This file contains only the new packing, modular-word, integer-shape, and
proof-only caller bridges. The three shape definitions are unchanged.
No old public function or runtime algorithm is replaced.

Standalone import: ContractTensor only. To integrate into the exact supplied
parent, retain original lines 1--6648 and replace its old appendix with this
file after removing this file's first import line. Do not append a second copy
of the old R14 namespaces. The local log2_shift helper closes the sole previous
Submission.FastMul dependency. All proof scripts require the fixed runner.
-/

section
set_option maxRecDepth 8192

namespace Submission.R14ExponentAlgebra

open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange

theorem mkBits_nat (sign : Bool) (e f : Nat) (he : e < 256) (hf : f < 8388608) :
    (Model.NativeBinary32.mkBits sign e f).toNat =
      (if sign then 2147483648 else 0) + e * 8388608 + f := by
  have heMask : (UInt32.ofNat e &&& 255).toNat = e := by
    rw [UInt32.toNat_and]
    change (e % 4294967296) &&& (2 ^ 8 - 1) = e
    rw [Nat.mod_eq_of_lt (by omega), Nat.and_two_pow_sub_one_eq_mod,
      Nat.mod_eq_of_lt he]
  have heField : ((UInt32.ofNat e &&& 255) <<< 23).toNat = e * 8388608 := by
    rw [UInt32.toNat_shiftLeft, heMask]
    change (e <<< 23) % 4294967296 = e * 8388608
    rw [Nat.shiftLeft_eq]
    change (e * 8388608) % 4294967296 = _
    exact Nat.mod_eq_of_lt (by omega)
  have hfField : (UInt32.ofNat f &&& 8388607).toNat = f := by
    rw [UInt32.toNat_and]
    change (f % 4294967296) &&& (2 ^ 23 - 1) = f
    rw [Nat.mod_eq_of_lt (by omega), Nat.and_two_pow_sub_one_eq_mod,
      Nat.mod_eq_of_lt hf]
  have horEF : e * 8388608 ||| f = e * 8388608 + f := by
    have h := (Nat.two_pow_add_eq_or_of_lt (show f < 2 ^ 23 by exact hf) e).symm
    simpa [Nat.mul_comm] using h
  have hlow : e * 8388608 + f < 2 ^ 31 := by norm_num; omega
  have horSign : 2147483648 ||| (e * 8388608 + f) =
      2147483648 + (e * 8388608 + f) := by
    simpa using (Nat.two_pow_add_eq_or_of_lt hlow 1).symm
  cases sign <;>
    simp [Model.NativeBinary32.mkBits, UInt32.toNat_or, heField, hfField,
      Nat.or_assoc, horEF, horSign, Nat.add_assoc]

end Submission.R14ExponentAlgebra
/- Draft reusable word-algebra extension. Depends only on the earlier
Submission.R14ExponentAlgebra.mkBits_nat packing theorem, not any Float32 operation.
No runtime candidate or floating equivalence follows merely from this identity. -/
namespace Submission.R14ExponentAlgebra

open FloatLib.Floats.Formats.BinaryInterchange

theorem translated_nat_general (em f s k : Nat)
    (he : em < 256) (hf : f < 8388608)
    (hs : s < 512) (hk : k ≤ 512)
    (hE0 : 0 < em + s - k) (hE : em + s - k < 255) :
    (em * 8388608 + f +
      (((((4294967296 - k + s) % 4294967296) <<< 23) % 4294967296))) % 4294967296 =
      (em + s - k) * 8388608 + f := by
  have hks : k < em + s := by omega
  have hout : (em + s - k) * 8388608 + f < 4294967296 := by omega
  rw [Nat.shiftLeft_eq]
  change (em * 8388608 + f +
      (((4294967296 - k + s) % 4294967296 * 8388608) % 4294967296)) % 4294967296 = _
  by_cases hsmall : s < k
  · have hsub : (4294967296 - k + s) % 4294967296 = 4294967296 - k + s :=
      Nat.mod_eq_of_lt (by omega)
    rw [hsub]
    have hdEq : (4294967296 - k + s) * 8388608 =
        4294967296 * 8388607 + (s + 512 - k) * 8388608 := by omega
    have hdLt : (s + 512 - k) * 8388608 < 4294967296 := by omega
    have hd : ((4294967296 - k + s) * 8388608) % 4294967296 =
        (s + 512 - k) * 8388608 := by
      rw [hdEq]
      simp [Nat.add_mod, Nat.mod_eq_of_lt hdLt]
    rw [hd]
    have hnum : em * 8388608 + f + (s + 512 - k) * 8388608 =
        4294967296 + ((em + s - k) * 8388608 + f) := by omega
    rw [hnum]
    simp [Nat.add_mod, Nat.mod_eq_of_lt hout]
  · have hsubEq : 4294967296 - k + s = 4294967296 + (s - k) := by omega
    have hsub : (4294967296 - k + s) % 4294967296 = s - k := by
      rw [hsubEq]
      simp [Nat.add_mod, Nat.mod_eq_of_lt (show s - k < 4294967296 by omega)]
    rw [hsub, Nat.mod_eq_of_lt (show (s - k) * 8388608 < 4294967296 by omega)]
    have hnum : em * 8388608 + f + (s - k) * 8388608 =
        (em + s - k) * 8388608 + f := by omega
    rw [hnum]
    exact Nat.mod_eq_of_lt hout

theorem shifted_word_general (sign : Bool) (em f : Nat) (s k : UInt32)
    (he : em < 256) (hf : f < 8388608)
    (hs : s.toNat < 512) (hk : k.toNat ≤ 512)
    (hE0 : 0 < em + s.toNat - k.toNat)
    (hE : em + s.toNat - k.toNat < 255) :
    (if sign then (2147483648 : UInt32) else 0) |||
        (Model.NativeBinary32.mkBits false em f + ((s - k) <<< 23)) =
      Model.NativeBinary32.mkBits sign (em + s.toNat - k.toNat) f := by
  have hmag :
      (Model.NativeBinary32.mkBits false em f + ((s - k) <<< 23)).toNat =
        (em + s.toNat - k.toNat) * 8388608 + f := by
    rw [UInt32.toNat_add, mkBits_nat false em f he hf,
      UInt32.toNat_shiftLeft, UInt32.toNat_sub]
    simp only [Bool.false_eq_true, ↓reduceIte, Nat.zero_add]
    change (em * 8388608 + f +
      (((((4294967296 - k.toNat + s.toNat) % 4294967296) <<< 23) % 4294967296))) % 4294967296 = _
    exact translated_nat_general em f s.toNat k.toNat he hf hs hk hE0 hE
  apply UInt32.toNat_inj.mp
  rw [UInt32.toNat_or, hmag, mkBits_nat sign (em + s.toNat - k.toNat) f (by omega) hf]
  have hlow : (em + s.toNat - k.toNat) * 8388608 + f < 2 ^ 31 := by norm_num; omega
  have hor : 2147483648 ||| ((em + s.toNat - k.toNat) * 8388608 + f) =
      2147483648 + ((em + s.toNat - k.toNat) * 8388608 + f) := by
    simpa using (Nat.two_pow_add_eq_or_of_lt hlow 1).symm
  cases sign <;> simp [hor, Nat.add_assoc]

/-- The signed64 conversion already carries the sign in its raw word.
This version preserves that stored sign while adding the exponent delta. -/
theorem shifted_signed_word_general (sign : Bool) (em f : Nat) (s k : UInt32)
    (he : em < 256) (hf : f < 8388608)
    (hs : s.toNat < 512) (hk : k.toNat ≤ 512)
    (hE0 : 0 < em + s.toNat - k.toNat)
    (hE : em + s.toNat - k.toNat < 255) :
    Model.NativeBinary32.mkBits sign em f + ((s - k) <<< 23) =
      Model.NativeBinary32.mkBits sign (em + s.toNat - k.toNat) f := by
  let delta := ((((4294967296 - k.toNat + s.toNat) % 4294967296) <<< 23) % 4294967296)
  have hmag : (em * 8388608 + f + delta) % 4294967296 =
      (em + s.toNat - k.toNat) * 8388608 + f :=
    translated_nat_general em f s.toNat k.toNat he hf hs hk hE0 hE
  apply UInt32.toNat_inj.mp
  rw [UInt32.toNat_add, mkBits_nat sign em f he hf,
    UInt32.toNat_shiftLeft, UInt32.toNat_sub,
    mkBits_nat sign (em + s.toNat - k.toNat) f (by omega) hf]
  cases sign
  · change (0 + em * 8388608 + f + delta) % 4294967296 =
      0 + (em + s.toNat - k.toNat) * 8388608 + f
    simpa only [Nat.zero_add] using hmag
  · change (2147483648 + em * 8388608 + f + delta) % 4294967296 =
      2147483648 + (em + s.toNat - k.toNat) * 8388608 + f
    have hsign : 2147483648 % 4294967296 = 2147483648 := by decide
    have hcalc :
        (2147483648 + (em * 8388608 + f + delta)) % 4294967296 =
          2147483648 + ((em + s.toNat - k.toNat) * 8388608 + f) := by
      calc
        _ = (2147483648 % 4294967296 +
              (em * 8388608 + f + delta) % 4294967296) % 4294967296 :=
          Nat.add_mod _ _ _
        _ = (2147483648 + ((em + s.toNat - k.toNat) * 8388608 + f)) % 4294967296 := by
          rw [hsign, hmag]
        _ = _ := Nat.mod_eq_of_lt (by omega)
    simpa only [Nat.add_assoc] using hcalc

end Submission.R14ExponentAlgebra

namespace Submission.R14IntegerShape

open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange
open FloatLib.Numerics

private theorem log2_shift (n k : Nat) (h : n >>> k ≠ 0) : n.log2 = k + (n >>> k).log2 := by
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

def roundedMantissa (n : Nat) : Nat :=
  if 23 ≤ n.log2 then roundShiftRightEven n (n.log2 - 23)
  else Nat.shiftLeft n (23 - n.log2)

def carry (n : Nat) : Nat := if roundedMantissa n = 16777216 then 1 else 0

def normalized (n : Nat) : Nat :=
  if roundedMantissa n = 16777216 then 8388608 else roundedMantissa n

theorem carry_le (n : Nat) : carry n ≤ 1 := by
  unfold carry
  split <;> omega

theorem rounded_small (n : Nat) (hh : n.log2 ≤ 23) :
    roundedMantissa n < 16777216 := by
  by_cases h23 : 23 ≤ n.log2
  · have heq : n.log2 = 23 := by omega
    have hu := Nat.lt_log2_self (n := n)
    rw [heq] at hu
    simpa only [roundedMantissa, h23, ↓reduceIte, heq, Nat.sub_self,
      roundShiftRightEven_zero] using hu
  · have hexp : n.log2 + 1 + (23 - n.log2) = 24 := by omega
    have hu := Nat.mul_lt_mul_of_pos_right (Nat.lt_log2_self (n := n))
      (Nat.two_pow_pos (23 - n.log2))
    have hp : 2 ^ (n.log2 + 1) * 2 ^ (23 - n.log2) = 16777216 := by
      rw [← Nat.pow_add, hexp]
      norm_num
    rw [hp] at hu
    simpa only [roundedMantissa, h23, ↓reduceIte, Nat.shiftLeft_eq', Nat.shiftLeft_eq] using hu

theorem carry_small (n : Nat) (hh : n.log2 ≤ 23) : carry n = 0 := by
  have hne : roundedMantissa n ≠ 16777216 := ne_of_lt (rounded_small n hh)
  simp [carry, hne]

theorem carry_one_leading (n : Nat) (hc : carry n = 1) : 24 ≤ n.log2 := by
  by_contra h
  have hh : n.log2 ≤ 23 := by omega
  have hz := carry_small n hh
  omega

theorem normalized_bounds (n : Nat) (hn : n ≠ 0) :
    8388608 ≤ normalized n ∧ normalized n < 16777216 := by
  have hb : 8388608 ≤ roundedMantissa n ∧ roundedMantissa n ≤ 16777216 := by
    by_cases h23 : 23 ≤ n.log2
    · let k := n.log2 - 23
      have hpow : 2 ^ k ≤ n :=
        le_trans (Nat.pow_le_pow_right (by decide) (show k ≤ n.log2 by dsimp [k]; omega))
          (Nat.log2_self_le hn)
      have hq : n >>> k ≠ 0 := by
        intro hz
        rw [Nat.shiftRight_eq_div_pow, Nat.div_eq_zero_iff] at hz
        rcases hz with hz | hz
        · exact (Nat.two_pow_pos k).ne' hz
        · omega
      have hlog := log2_shift n k hq
      have hqlog : (n >>> k).log2 = 23 := by
        dsimp [k] at hlog ⊢
        omega
      have hqlo := Nat.log2_self_le hq
      have hqhi := Nat.lt_log2_self (n := n >>> k)
      rw [hqlog] at hqlo hqhi
      norm_num at hqlo hqhi
      have hrlo := shiftRight_le_roundShiftRightEven n k
      have hrhi := roundShiftRightEven_le_shiftRight_add1 n k
      have hr : roundedMantissa n = roundShiftRightEven n k := by
        simp only [roundedMantissa, h23, ↓reduceIte, k]
      rw [hr]
      omega
    · have heq : n.log2 + (23 - n.log2) = 23 := by omega
      have hl := Nat.mul_le_mul_right (2 ^ (23 - n.log2)) (Nat.log2_self_le hn)
      have hp : 2 ^ n.log2 * 2 ^ (23 - n.log2) = 8388608 := by
        rw [← Nat.pow_add, heq]
        norm_num
      rw [hp] at hl
      have hr : roundedMantissa n = n * 2 ^ (23 - n.log2) := by
        simp only [roundedMantissa, h23, ↓reduceIte, Nat.shiftLeft_eq', Nat.shiftLeft_eq]
      have hu := rounded_small n (by omega)
      rw [hr] at hu ⊢
      omega
  by_cases hc : roundedMantissa n = 16777216
  · simp [normalized, hc]
  · simp only [normalized, hc, ↓reduceIte]
    omega

/-- The dynamic postguard's lower bound gives the original normal branch for
integer-aligned normal inputs: low integer magnitudes cannot round upward. -/
theorem postguard_pre_normal (n a : Nat) (ha : 1 ≤ a)
    (hE : 1 ≤ n.log2 + carry n + a - 23) :
    -126 ≤ (n.log2 : Int) + ((a : Int) - 150) := by
  have hc := carry_le n
  have hcases : carry n = 0 ∨ carry n = 1 := by omega
  rcases hcases with hz | ho
  · rw [hz] at hE
    omega
  · have hh := carry_one_leading n ho
    omega

theorem native_round_normal (sign : Bool) (n : Nat) (e : Int)
    (hn : n ≠ 0)
    (hmin : -126 ≤ (n.log2 : Int) + e)
    (hmax : (n.log2 : Int) + e + (carry n : Int) ≤ 127) :
    Model.NativeBinary32.roundDyadic
        (⟨sign, n, e⟩ : FloatLib.Numerics.Dyadic) =
      Model.NativeBinary32.mkBits sign
        (Int.toNat ((n.log2 : Int) + e + (carry n : Int) + 127))
        (normalized n - 8388608) := by
  have hnormal : ¬ (n.log2 : Int) + e < -126 := by omega
  unfold Model.NativeBinary32.roundDyadic
  simp only [beq_iff_eq, hn, ↓reduceIte, hnormal, Model.pow2_eq_two_pow]
  change
    (if (if roundedMantissa n = 16777216
          then (n.log2 : Int) + e + 1
          else (n.log2 : Int) + e) > 127 then
        (if sign then (0xff800000 : UInt32) else 0x7f800000)
      else Model.NativeBinary32.mkBits sign
        (Int.toNat ((if roundedMantissa n = 16777216
          then (n.log2 : Int) + e + 1
          else (n.log2 : Int) + e) + 127))
        (normalized n - 8388608)) =
      Model.NativeBinary32.mkBits sign
        (Int.toNat ((n.log2 : Int) + e + (carry n : Int) + 127))
        (normalized n - 8388608)
  by_cases hc : roundedMantissa n = 16777216
  · have hc1 : carry n = 1 := by simp only [carry, hc, ↓reduceIte]
    have hf : ¬ (n.log2 : Int) + e + 1 > 127 := by
      rw [hc1] at hmax
      norm_num at hmax
      omega
    simp [hc, hf, hc1]
  · have hc0 : carry n = 0 := by simp only [carry, hc, ↓reduceIte]
    have hf : ¬ (n.log2 : Int) + e > 127 := by
      rw [hc0] at hmax
      norm_num at hmax
      omega
    simp [hc, hf, hc0]

theorem model_round_normal (sign : Bool) (n : Nat) (e : Int)
    (hn : n ≠ 0)
    (hmin : -126 ≤ (n.log2 : Int) + e)
    (hmax : (n.log2 : Int) + e + (carry n : Int) ≤ 127) :
    Model.roundDyadic FloatFormat.binary32
        (⟨sign, n, e⟩ : FloatLib.Numerics.Dyadic) =
      Model.ofFields FloatFormat.binary32 sign
        (Int.toNat ((n.log2 : Int) + e + (carry n : Int) + 127))
        (normalized n - 8388608) := by
  rw [← Model.NativeBinary32.ofUInt32_roundDyadic,
    native_round_normal sign n e hn hmin hmax,
    Model.NativeBinary32.ofUInt32_mkBits]

/-- Actual fixed word-rounder identity. Its pre-rounding normal condition and
carry-inclusive upper bound are explicit; it is not a real-number shortcut. -/
theorem native_round_shifted (sign : Bool) (n : Nat) (s k : UInt32)
    (hn : n ≠ 0) (hs : s.toNat < 512) (hk : k.toNat ≤ 512)
    (hfirst : (n.log2 : Int) + (carry n : Int) ≤ 127)
    (hmin : -126 ≤ (n.log2 : Int) + ((s.toNat : Int) - (k.toNat : Int)))
    (hmax : (n.log2 : Int) + ((s.toNat : Int) - (k.toNat : Int)) + (carry n : Int) ≤ 127) :
    Model.NativeBinary32.roundDyadic
        (⟨sign, n, (s.toNat : Int) - (k.toNat : Int)⟩ : FloatLib.Numerics.Dyadic) =
      Model.NativeBinary32.roundDyadic (⟨sign, n, 0⟩ : FloatLib.Numerics.Dyadic) +
        ((s - k) <<< 23) := by
  let em := n.log2 + carry n + 127
  have hm := normalized_bounds n hn
  have hc := carry_le n
  have hf : normalized n - 8388608 < 8388608 := by omega
  have hem : em < 256 := by dsimp [em]; omega
  have hE0 : 0 < em + s.toNat - k.toNat := by dsimp [em]; omega
  have hE : em + s.toNat - k.toNat < 255 := by dsimp [em]; omega
  have heFirst : Int.toNat ((n.log2 : Int) + 0 + (carry n : Int) + 127) = em := by
    dsimp [em]
    omega
  have heTarget :
      Int.toNat ((n.log2 : Int) + ((s.toNat : Int) - (k.toNat : Int)) +
        (carry n : Int) + 127) = em + s.toNat - k.toNat := by
    dsimp [em]
    omega
  rw [native_round_normal sign n ((s.toNat : Int) - (k.toNat : Int)) hn hmin hmax,
    native_round_normal sign n 0 hn (by omega) (by omega), heTarget, heFirst]
  exact (R14ExponentAlgebra.shifted_signed_word_general sign em
    (normalized n - 8388608) s k hem hf hs hk hE0 hE).symm

end Submission.R14IntegerShape

namespace Submission.R14IntegerShape

open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange

theorem postguard_normal_bounds (n a : Nat) (ha : 1 ≤ a)
    (hlo : 1 ≤ n.log2 + carry n + a - 23)
    (hhi : n.log2 + carry n + a - 23 ≤ 254) :
    -126 ≤ (n.log2 : Int) + ((a : Int) - 150) ∧
      (n.log2 : Int) + ((a : Int) - 150) + (carry n : Int) ≤ 127 := by
  constructor
  · exact postguard_pre_normal n a ha hlo
  · omega

theorem postguard_encodedExponent (n a : Nat)
    (hlo : 1 ≤ n.log2 + carry n + a - 23) :
    Int.toNat ((n.log2 : Int) + ((a : Int) - 150) + (carry n : Int) + 127) =
      n.log2 + carry n + a - 23 := by
  omega

theorem native_round_aligned_normal (sign : Bool) (n a : Nat)
    (hn : n ≠ 0) (ha : 1 ≤ a)
    (hlo : 1 ≤ n.log2 + carry n + a - 23)
    (hhi : n.log2 + carry n + a - 23 ≤ 254) :
    Model.NativeBinary32.roundDyadic
        (⟨sign, n, (a : Int) - 150⟩ : FloatLib.Numerics.Dyadic) =
      Model.NativeBinary32.mkBits sign (n.log2 + carry n + a - 23)
        (normalized n - 8388608) := by
  have hb := postguard_normal_bounds n a ha hlo hhi
  rw [native_round_normal sign n ((a : Int) - 150) hn hb.1 hb.2,
    postguard_encodedExponent n a hlo]

theorem native_round_posZero (e : Int) :
    Model.NativeBinary32.roundDyadic
      (⟨false, 0, e⟩ : FloatLib.Numerics.Dyadic) = 0 := by
  rfl

theorem native_round_aligned_int_zero (z : Int) (a : Nat) (hz : z = 0) :
    Model.NativeBinary32.roundDyadic
      (⟨decide (z < 0), z.natAbs, (a : Int) - 150⟩ : FloatLib.Numerics.Dyadic) = 0 := by
  subst z
  rfl

theorem first_round_bound_of_u64 (n : Nat) (hn : n ≠ 0) (hN : n < 2 ^ 64) :
    (n.log2 : Int) + (carry n : Int) ≤ 127 := by
  have hh : n.log2 < 64 := (Nat.log2_lt hn).2 hN
  have hc := carry_le n
  omega

/-- Here z is the exact aligned integer sum. The theorem rounds z.natAbs with
    its actual sign, and retains the complete postguard and magnitude bound.
    No assertion about a wrapping machine addition or signed conversion is used. -/
theorem native_round_aligned_int_shifted (z : Int) (a : UInt32)
    (hz : z ≠ 0) (ha : 1 ≤ a.toNat) (haHi : a.toNat < 512)
    (hN : z.natAbs < 2 ^ 64)
    (hlo : 1 ≤ z.natAbs.log2 + carry z.natAbs + a.toNat - 23)
    (hhi : z.natAbs.log2 + carry z.natAbs + a.toNat - 23 ≤ 254) :
    Model.NativeBinary32.roundDyadic
        (⟨decide (z < 0), z.natAbs, (a.toNat : Int) - 150⟩ : FloatLib.Numerics.Dyadic) =
      Model.NativeBinary32.roundDyadic
        (⟨decide (z < 0), z.natAbs, 0⟩ : FloatLib.Numerics.Dyadic) + ((a - 150) <<< 23) := by
  have hn : z.natAbs ≠ 0 := Int.natAbs_ne_zero.mpr hz
  have hb := postguard_normal_bounds z.natAbs a.toNat ha hlo hhi
  exact native_round_shifted (decide (z < 0)) z.natAbs a (150 : UInt32)
    hn haHi (by decide) (first_round_bound_of_u64 z.natAbs hn hN) hb.1 hb.2

theorem product_leading_lower (mx my : Nat)
    (hx : 8388608 ≤ mx) (hy : 8388608 ≤ my) :
    46 ≤ (mx * my).log2 := by
  have hprod : 2 ^ 46 ≤ mx * my := by
    calc
      2 ^ 46 = (8388608 : Nat) * 8388608 := by decide
      _ ≤ mx * my := Nat.mul_le_mul hx hy
  have hn : mx * my ≠ 0 := by
    norm_num at hprod
    omega
  exact (Nat.le_log2 hn).2 hprod

theorem multiplication_pre_normal (n S : Nat)
    (hh : 46 ≤ n.log2) (hS : 128 ≤ S) :
    -126 ≤ (n.log2 : Int) + ((S : Int) - 300) := by
  omega

theorem normal_product_pre_normal (mx my S : Nat)
    (hx : 8388608 ≤ mx) (hy : 8388608 ≤ my) (hS : 128 ≤ S) :
    -126 ≤ ((mx * my).log2 : Int) + ((S : Int) - 300) := by
  exact multiplication_pre_normal (mx * my) S (product_leading_lower mx my hx hy) hS

end Submission.R14IntegerShape

end
