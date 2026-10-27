/- Draft / NOT_RUN. Common normal-rounding shape for arbitrary nonzero integer
   magnitudes, including h<23 cancellation. Sole existing-kernel dependency:
   Submission.FastMul.log2_shift. The final shifted theorem additionally needs
   R14ExponentAlgebra.shifted_signed_word_general from the separate draft.
   No runtime candidate or CI request is created by this fragment. -/
section
set_option maxRecDepth 8192

namespace Submission.R14IntegerShape

open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange
open FloatLib.Numerics

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
    simpa only [roundedMantissa, h23, ↓reduceIte, Nat.shiftLeft_eq] using hu

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
      have hlog := Submission.FastMul.log2_shift n k hq
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
        simp only [roundedMantissa, h23, ↓reduceIte, Nat.shiftLeft_eq]
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
  by_cases hc : (if 23 ≤ n.log2 then roundShiftRightEven n (n.log2 - 23)
      else Nat.shiftLeft n (23 - n.log2)) = 16777216
  · have hc1 : carry n = 1 := by simp [carry, roundedMantissa, hc]
    have hf : ¬ (n.log2 : Int) + e + 1 > 127 := by
      rw [hc1] at hmax
      norm_num at hmax
      omega
    simp [Model.NativeBinary32.roundDyadic, Model.pow2_eq_two_pow,
      hn, hnormal, hf, carry, roundedMantissa, normalized, hc]
  · have hc0 : carry n = 0 := by simp [carry, roundedMantissa, hc]
    have hf : ¬ (n.log2 : Int) + e > 127 := by
      rw [hc0] at hmax
      norm_num at hmax
      omega
    simp [Model.NativeBinary32.roundDyadic, Model.pow2_eq_two_pow,
      hn, hnormal, hf, carry, roundedMantissa, normalized, hc]

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
end
