/- Append after UInt32NativeRound-interface.lean. NOT_COMPILED.
   Uses only the exact B2/R16 parent definitions and imported Nat/model lemmas. -/
namespace Submission.R16AddUInt32Interface
open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange
open FloatLib.Numerics

def lowMantissa (n : Nat) : Nat := Nat.shiftLeft n (23 - n.log2)

theorem lowMantissa_bounds (n : Nat) (hn : n ≠ 0) (hh : n.log2 < 23) :
    8388608 ≤ lowMantissa n ∧ lowMantissa n < 16777216 := by
  have hlo := Nat.mul_le_mul_right (2 ^ (23 - n.log2)) (Nat.log2_self_le hn)
  have hhi := Nat.mul_lt_mul_of_pos_right (Nat.lt_log2_self (n := n))
    (Nat.two_pow_pos (23 - n.log2))
  have he0 : n.log2 + (23 - n.log2) = 23 := by omega
  have he1 : n.log2 + 1 + (23 - n.log2) = 24 := by omega
  have hp0 : 2 ^ n.log2 * 2 ^ (23 - n.log2) = 8388608 := by
    rw [← Nat.pow_add, he0]
    norm_num
  have hp1 : 2 ^ (n.log2 + 1) * 2 ^ (23 - n.log2) = 16777216 := by
    rw [← Nat.pow_add, he1]
    norm_num
  rw [hp0] at hlo
  rw [hp1] at hhi
  simpa only [lowMantissa, Nat.shiftLeft_eq] using And.intro hlo hhi

theorem native_round_low (sign : Bool) (n : Nat) (e : Int)
    (hn : n ≠ 0) (hh : n.log2 < 23)
    (hmin : -126 ≤ (n.log2 : Int) + e)
    (hmax : (n.log2 : Int) + e ≤ 127) :
    Model.NativeBinary32.roundDyadic (⟨sign, n, e⟩ : Dyadic) =
      Model.NativeBinary32.mkBits sign
        (Int.toNat ((n.log2 : Int) + e + 127)) (lowMantissa n - 8388608) := by
  have hb := lowMantissa_bounds n hn hh
  have hcarry : Nat.shiftLeft n (23 - n.log2) ≠ 16777216 := ne_of_lt hb.2
  have hhigh : ¬ 23 ≤ n.log2 := by omega
  have hsub : ¬ (n.log2 : Int) + e < -126 := by omega
  have hover : ¬ (n.log2 : Int) + e > 127 := by omega
  simp [Model.NativeBinary32.roundDyadic, Model.pow2_eq_two_pow,
    hn, hhigh, hsub, hover, hcarry, lowMantissa]

theorem uint32_native_low_fields (n : UInt32)
    (hn : n.toNat ≠ 0) (hh : n.toNat.log2 < 23) :
    (Model.NativeBinary32.expField n.toFloat32.toBits).toNat = n.toNat.log2 + 127 ∧
    (Model.NativeBinary32.fracField n.toFloat32.toBits).toNat =
      lowMantissa n.toNat - 8388608 := by
  have hb := lowMantissa_bounds n.toNat hn hh
  apply uint32_native_fields_of_shape n (n.toNat.log2 + 127)
    (lowMantissa n.toNat - 8388608) (by omega) (by omega)
  have h := native_round_low false n.toNat 0 hn hh (by omega) (by omega)
  have he : Int.toNat ((n.toNat.log2 : Int) + 0 + 127) = n.toNat.log2 + 127 := by omega
  simpa only [he] using h

theorem low_scaled_round_fields (sign : Bool) (n a : Nat)
    (hn : n ≠ 0) (hh : n.log2 < 23)
    (hE0 : 1 ≤ n.log2 + a - 23) (hE : n.log2 + a - 23 ≤ 254) :
    Model.NativeBinary32.roundDyadic (⟨sign, n, (a : Int) - 150⟩ : Dyadic) =
      Model.NativeBinary32.mkBits sign (n.log2 + a - 23) (lowMantissa n - 8388608) := by
  have hmin : -126 ≤ (n.log2 : Int) + ((a : Int) - 150) := by omega
  have hmax : (n.log2 : Int) + ((a : Int) - 150) ≤ 127 := by omega
  have h := native_round_low sign n ((a : Int) - 150) hn hh hmin hmax
  have he : Int.toNat ((n.log2 : Int) + ((a : Int) - 150) + 127) =
      n.log2 + a - 23 := by omega
  simpa only [he] using h

end Submission.R16AddUInt32Interface
