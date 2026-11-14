/- R22 mathematical component, NOT_RUN. Uses only pinned ContractTensor/B2.
   nativeNormal/modelNormal follow the already gate-accepted R18A.N18 proof
   at f01-r17-dev-add-public2/Kernel.lean:4479-4515, with namespace renamed.
   New normal-field formula does not establish the UInt32 guard/packing bridge. -/
namespace Submission.R22SameExponentMath
open FloatLib.Floats FloatLib.Numerics
open FloatLib.Floats.Formats.BinaryInterchange

def rounded (p : Nat) : Nat := roundShiftRightEven p (p.log2 - 23)
def carry (p : Nat) : Nat := if rounded p = 16777216 then 1 else 0
def mantissa (p : Nat) : Nat := if rounded p = 16777216 then 8388608 else rounded p

theorem nativeNormal (sign : Bool) (p : Nat) (e : Int)
    (hp : p ≠ 0) (hl : 23 ≤ p.log2)
    (hmin : -126 ≤ (p.log2 : Int) + e)
    (hmax : (p.log2 : Int) + e + (carry p : Int) ≤ 127) :
    Model.NativeBinary32.roundDyadic ⟨sign, p, e⟩ =
      Model.NativeBinary32.mkBits sign
        (Int.toNat ((p.log2 : Int) + e + (carry p : Int) + 127))
        (mantissa p - 8388608) := by
  have hnormal : ¬(p.log2 : Int) + e < -126 := by omega
  by_cases hc : roundShiftRightEven p (p.log2 - 23) = 16777216
  · have hc1 : carry p = 1 := by simp [carry, rounded, hc]
    have hf : ¬(p.log2 : Int) + e + 1 > 127 := by
      rw [hc1] at hmax
      norm_num at hmax
      omega
    simp [Model.NativeBinary32.roundDyadic, Model.pow2_eq_two_pow,
      hp, hl, hnormal, hf, carry, rounded, mantissa, hc]
  · have hc0 : carry p = 0 := by simp [carry, rounded, hc]
    have hf : ¬(p.log2 : Int) + e > 127 := by
      rw [hc0] at hmax
      norm_num at hmax
      omega
    simp [Model.NativeBinary32.roundDyadic, Model.pow2_eq_two_pow,
      hp, hl, hnormal, hf, carry, rounded, mantissa, hc]

theorem half_round (t : Nat) :
    roundShiftRightEven (16777216 + t) 1 =
      8388608 + (t + (t / 2) % 2) / 2 := by
  rw [roundShiftRightEven_eq_roundQuotientEven]
  norm_num [roundQuotientEven]
  split_ifs <;> omega

theorem half_bound (t : Nat) (ht : t ≤ 16777214) :
    (t + (t / 2) % 2) / 2 < 8388608 := by omega

theorem sum_log (t : Nat) (ht : t ≤ 16777214) :
    (16777216 + t).log2 = 24 := by
  apply (Nat.log2_eq_iff (by omega : 16777216 + t ≠ 0)).2
  norm_num
  omega

theorem normal_round (s : Bool) (e t : Nat)
    (he0 : 1 ≤ e) (he : e ≤ 253) (ht : t ≤ 16777214) :
    Model.roundDyadic FloatFormat.binary32 ⟨s, 16777216 + t, (e : Int) - 150⟩ =
      Model.ofFields FloatFormat.binary32 s (e + 1) ((t + (t / 2) % 2) / 2) := by
  have hlog := sum_log t ht
  have hr : rounded (16777216 + t) = 8388608 + (t + (t / 2) % 2) / 2 := by
    simpa only [rounded, hlog] using half_round t
  have hb := half_bound t ht
  have hc : carry (16777216 + t) = 0 := by
    simp only [carry, hr]
    split <;> omega
  have hm : mantissa (16777216 + t) = 8388608 + (t + (t / 2) % 2) / 2 := by
    simp only [mantissa, hr]
    split <;> omega
  have hmin : -126 ≤ ((16777216 + t).log2 : Int) + ((e : Int) - 150) := by
    rw [hlog]
    omega
  have hmax : ((16777216 + t).log2 : Int) + ((e : Int) - 150) +
      (carry (16777216 + t) : Int) ≤ 127 := by
    rw [hlog, hc]
    omega
  rw [← Model.NativeBinary32.ofUInt32_roundDyadic,
    nativeNormal s (16777216 + t) ((e : Int) - 150) (by omega)
      (by rw [hlog]; decide) hmin hmax,
    Model.NativeBinary32.ofUInt32_mkBits, hlog, hc, hm]
  congr 2 <;> omega

theorem normal_fields_add (s : Bool) (e f g : Nat)
    (he0 : 1 ≤ e) (he : e ≤ 253) (hf : f < 8388608) (hg : g < 8388608) :
    Model.Spec.add (Model.ofFields FloatFormat.binary32 s e f)
      (Model.ofFields FloatFormat.binary32 s e g) =
      Model.ofFields FloatFormat.binary32 s (e + 1)
        ((f + g + ((f + g) / 2) % 2) / 2) := by
  unfold Model.Spec.add
  rw [R2W01c.fields32_toDyadic s e f (by omega) (by omega) hf,
      R2W01c.fields32_toDyadic s e g (by omega) (by omega) hg]
  rw [Model.addDyadic_sameSign_sameExponent s (8388608 + f) (8388608 + g)
    ((e : Int) - 150) (by omega) (by omega)]
  have hsum : 8388608 + f + (8388608 + g) = 16777216 + (f + g) := by omega
  rw [hsum]
  exact normal_round s e (f + g) he0 he (by omega)

end Submission.R22SameExponentMath
