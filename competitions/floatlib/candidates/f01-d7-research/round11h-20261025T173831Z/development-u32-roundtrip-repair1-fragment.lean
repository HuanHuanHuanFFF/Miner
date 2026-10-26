
namespace Submission.R14NatNormal

open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange
open FloatLib.Numerics

def rounded (p : Nat) : Nat := roundShiftRightEven p (p.log2 - 23)
def carry (p : Nat) : Nat := if rounded p = 16777216 then 1 else 0
def mantissa (p : Nat) : Nat := if rounded p = 16777216 then 8388608 else rounded p

theorem carry_le (p : Nat) : carry p ≤ 1 := by
  unfold carry
  split <;> omega

/-- A normal finite rounding has the same mantissa at every admissible exponent.
The hypotheses explicitly include the carry in the upper boundary. -/
theorem native_round_normal (sign : Bool) (p : Nat) (e : Int)
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

theorem model_round_normal (sign : Bool) (p : Nat) (e : Int)
    (hp : p ≠ 0) (hl : 23 ≤ p.log2)
    (hmin : -126 ≤ (p.log2 : Int) + e)
    (hmax : (p.log2 : Int) + e + (carry p : Int) ≤ 127) :
    Model.roundDyadic FloatFormat.binary32 ⟨sign, p, e⟩ =
      Model.ofFields FloatFormat.binary32 sign
        (Int.toNat ((p.log2 : Int) + e + (carry p : Int) + 127))
        (mantissa p - 8388608) := by
  rw [← Model.NativeBinary32.ofUInt32_roundDyadic,
    native_round_normal sign p e hp hl hmin hmax,
    Model.NativeBinary32.ofUInt32_mkBits]

/-- Unlike the old NormalBand helper, this covers every normal raw exponent1..254. -/
theorem raw_normal_decode (u : UInt32)
    (he0 : 0 < R2W01c.wordExp u) (hehi : R2W01c.wordExp u < 255) :
    Model.toDyadic? (R2W01c.rawModel u) =
      some ⟨R2W01c.wordSign u, (R2W01b.mantissa u).toNat,
        (R2W01c.wordExp u : Int) - 150⟩ := by
  rw [R2W01c.rawModel_eq_ofUInt32]
  change Model.toDyadic? (R2W01c.raw32 u) = _
  rw [R2W01c.raw32_eq_fields, R2W01c.mantissa_toNat]
  exact R2W01c.fields32_toDyadic (R2W01c.wordSign u) (R2W01c.wordExp u)
    (R2W01c.wordFrac u) he0 hehi (R2W01c.wordFrac_lt u)


end Submission.R14NatNormal

namespace Submission.R14WordAddRounding

open FloatLib.Numerics

theorem rounded_bounds (n : Nat) (hn : n ≠ 0) (hh : 23 ≤ n.log2) :
    8388608 ≤ Submission.R14NatNormal.rounded n ∧
    Submission.R14NatNormal.rounded n ≤ 16777216 := by
  let k := n.log2 - 23
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
  change n >>> k ≤ roundShiftRightEven n k at hrlo
  change roundShiftRightEven n k ≤ (n >>> k) + 1 at hrhi
  rw [Nat.shiftRight_eq_div_pow] at hrlo hrhi
  change 8388608 ≤ roundShiftRightEven n k ∧ roundShiftRightEven n k ≤ 16777216
  omega

theorem shift_carry (n : Nat) (hn : n ≠ 0) (hh : 23 ≤ n.log2) :
    Submission.R14NatNormal.rounded n >>> 24 = Submission.R14NatNormal.carry n := by
  have hb := rounded_bounds n hn hh
  rw [Nat.shiftRight_eq_div_pow]
  unfold Submission.R14NatNormal.carry
  split <;> norm_num at * <;> omega

theorem masked_fraction (n : Nat) (hn : n ≠ 0) (hh : 23 ≤ n.log2) :
    Submission.R14NatNormal.rounded n % 8388608 =
      Submission.R14NatNormal.mantissa n - 8388608 := by
  have hb := rounded_bounds n hn hh
  unfold Submission.R14NatNormal.mantissa
  split <;> norm_num at * <;> omega

end Submission.R14WordAddRounding

/- R16 numerical round-trip proof probe. NOT_COMPILED. -/
namespace Submission.R16UInt32Roundtrip

open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange
open FloatLib.Numerics

def roundedShift (n : Nat) : Nat := n.log2 + R14NatNormal.carry n - 23
def roundedInteger (n : Nat) : Nat := R14NatNormal.mantissa n * 2 ^ roundedShift n

theorem high_log (n : Nat) (hlo : 8388608 ≤ n) (hhi : n ≤ 2164260735) :
    23 ≤ n.log2 ∧ n.log2 ≤ 31 := by
  have hn : n ≠ 0 := by omega
  have hl : 23 ≤ n.log2 := (Nat.le_log2 hn).2 (by norm_num; exact hlo)
  have hu : n.log2 < 32 := (Nat.log2_lt hn).2 (by norm_num; omega)
  omega

theorem no_carry_at_31 (n : Nat) (hhi : n ≤ 2164260735) (hlog : n.log2=31) :
    R14NatNormal.carry n = 0 := by
  have hq : n / 256 ≤ 8454143 := by omega
  have hr := roundShiftRightEven_le_shiftRight_add1 n 8
  norm_num [Nat.shiftRight_eq_div_pow] at hr
  have hb : R14NatNormal.rounded n ≤ 8454144 := by
    unfold R14NatNormal.rounded
    rw [hlog]
    change roundShiftRightEven n 8 ≤ 8454144
    omega
  have hn : R14NatNormal.rounded n ≠ 16777216 := by omega
  simp [R14NatNormal.carry, hn]

theorem rounded_leading (n : Nat) (hlo : 8388608 ≤ n) (hhi : n ≤ 2164260735) :
    23 ≤ n.log2 + R14NatNormal.carry n ∧
      n.log2 + R14NatNormal.carry n ≤ 31 := by
  have hl := high_log n hlo hhi
  have hc := R14NatNormal.carry_le n
  by_cases hh : n.log2=31
  · rw [no_carry_at_31 n hhi hh]
    omega
  · omega

theorem high_mantissa (n : Nat) (hlo : 8388608 ≤ n) (hhi : n ≤ 2164260735) :
    8388608 ≤ R14NatNormal.mantissa n ∧ R14NatNormal.mantissa n < 16777216 := by
  have hn : n ≠ 0 := by omega
  have hl := high_log n hlo hhi
  have hr := R14WordAddRounding.rounded_bounds n hn hl.1
  by_cases hc : R14NatNormal.rounded n = 16777216
  · simp [R14NatNormal.mantissa, hc]
  · simp only [R14NatNormal.mantissa, hc, ↓reduceIte]
    omega

theorem roundedInteger_fit (n : Nat) (hlo : 8388608 ≤ n) (hhi : n ≤ 2164260735) :
    roundedInteger n < UInt32.size := by
  have hl := rounded_leading n hlo hhi
  have hm := high_mantissa n hlo hhi
  have he : roundedShift n ≤ 8 := by unfold roundedShift; omega
  have hp : 2 ^ roundedShift n ≤ 256 := by
    have h := Nat.pow_le_pow_right (by decide : 0 < 2) he
    norm_num at h
    exact h
  unfold roundedInteger
  calc
    R14NatNormal.mantissa n * 2 ^ roundedShift n < 16777216 * 2 ^ roundedShift n :=
      Nat.mul_lt_mul_of_pos_right hm.2 (Nat.two_pow_pos _)
    _ ≤ 16777216 * 256 := Nat.mul_le_mul_left _ hp
    _ = UInt32.size := by decide

/-- This is the rounded integer, not the original input integer. -/
theorem roundedInteger_eq_RNE (n : Nat) (hlo : 8388608 ≤ n) (hhi : n ≤ 2164260735) :
    roundedInteger n = R14NatNormal.rounded n * 2 ^ (n.log2-23) := by
  have hl := (high_log n hlo hhi).1
  by_cases hc : R14NatNormal.rounded n = 16777216
  · have he : n.log2+1-23 = (n.log2-23)+1 := by omega
    simp only [roundedInteger, roundedShift, R14NatNormal.mantissa,
      R14NatNormal.carry, hc, ↓reduceIte, he, pow_succ]
    ring
  · simp only [roundedInteger, roundedShift, R14NatNormal.mantissa,
      R14NatNormal.carry, hc, ↓reduceIte, Nat.add_zero]

/-- The existing RNE word shape supplies an exact nonnegative-exponent dyadic. -/
theorem native_high_decode (n : UInt32)
    (hlo : 8388608 ≤ n.toNat) (hhi : n.toNat ≤ 2164260735) :
    Model.toDyadic? (Model.ofFloat32Model n.toFloat32.toModel) =
      some ⟨false, R14NatNormal.mantissa n.toNat, (roundedShift n.toNat : Int)⟩ := by
  have hn : n.toNat ≠ 0 := by omega
  have hl := high_log n.toNat hlo hhi
  have hc := R14NatNormal.carry_le n.toNat
  have hm := high_mantissa n.toNat hlo hhi
  have hexp : Int.toNat ((n.toNat.log2 : Int)+0+(R14NatNormal.carry n.toNat : Int)+127) =
      n.toNat.log2+R14NatNormal.carry n.toNat+127 := by omega
  have he0 : 0 < n.toNat.log2+R14NatNormal.carry n.toNat+127 := by omega
  have hehi : n.toNat.log2+R14NatNormal.carry n.toNat+127 < 255 := by omega
  have hf : R14NatNormal.mantissa n.toNat-8388608 < 8388608 := by omega
  have hsum : 8388608+(R14NatNormal.mantissa n.toNat-8388608) =
      R14NatNormal.mantissa n.toNat := by omega
  have he : ((n.toNat.log2+R14NatNormal.carry n.toNat+127 : Nat) : Int)-150 =
      (roundedShift n.toNat : Int) := by unfold roundedShift; omega
  rw [R2W01c.uint32_model_eq_roundDyadic,
    R14NatNormal.model_round_normal false n.toNat 0 hn hl.1 (by omega) (by omega),hexp]
  have hd := R2W01c.fields32_toDyadic false
    (n.toNat.log2+R14NatNormal.carry n.toNat+127)
    (R14NatNormal.mantissa n.toNat-8388608) he0 hehi hf
  simpa only [hsum,he] using hd

/-- A genuine reusable conditional lemma. Both premises are discharged below. -/
theorem toUInt32_of_nonnegative_integral_decode (x : Float32) (m e : Nat)
    (hd : Model.toDyadic? (Model.ofFloat32Model x.toModel) =
      some ⟨false,m,(e : Int)⟩)
    (hfit : m*2^e < UInt32.size) :
    x.toUInt32.toNat = m*2^e := by
  have hv := Model.exactValue_eq_finite_of_toDyadic?_eq_some hd
  have hi := Model.toInt_toModel_eq (fmt := FloatFormat.binary32) (by decide)
    (Model.ofFloat32Model x.toModel) 0 (UInt32.size-1)
  rw [Model.toModel_ofFloat32Model,hv] at hi
  change x.toModel.unpack.toInt 0 (UInt32.size-1) =
    Model.roundDyadicToInt .towardZero
      (⟨false,m,(e : Int)⟩ : FloatLib.Numerics.Dyadic) at hi
  have hr : Model.roundDyadicToInt .towardZero (⟨false,m,(e : Int)⟩ : FloatLib.Numerics.Dyadic) =
      ((m*2^e : Nat) : Int) := by
    by_cases hm : m=0
    · subst m
      simp [Model.roundDyadicToInt]
    · simp [Model.roundDyadicToInt,hm,Nat.shiftLeft_eq]
  change (UInt32.ofNatClamp
    ((x.toModel.unpack.toInt 0 (UInt32.size-1)).toNat)).toNat = _
  rw [hi,hr]
  simpa using (UInt32.toNat_ofNatClamp_of_lt hfit)

/-- Target numeric bridge. No shape or cast behavior is left as a hypothesis. -/
theorem high_roundtrip (n : UInt32)
    (hlo : 8388608 ≤ n.toNat) (hhi : n.toNat ≤ 2164260735) :
    n.toFloat32.toUInt32.toNat = roundedInteger n.toNat := by
  exact toUInt32_of_nonnegative_integral_decode n.toFloat32
    (R14NatNormal.mantissa n.toNat) (roundedShift n.toNat)
    (native_high_decode n hlo hhi) (roundedInteger_fit n.toNat hlo hhi)

theorem high_roundtrip_RNE (n : UInt32)
    (hlo : 8388608 ≤ n.toNat) (hhi : n.toNat ≤ 2164260735) :
    n.toFloat32.toUInt32.toNat =
      R14NatNormal.rounded n.toNat * 2^(n.toNat.log2-23) := by
  rw [high_roundtrip n hlo hhi, roundedInteger_eq_RNE n.toNat hlo hhi]

end Submission.R16UInt32Roundtrip
