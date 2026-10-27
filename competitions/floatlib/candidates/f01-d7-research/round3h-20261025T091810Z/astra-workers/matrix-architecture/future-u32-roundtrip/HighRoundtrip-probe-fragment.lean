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
  have hr : Model.roundDyadicToInt .towardZero (⟨false,m,(e : Int)⟩ : Dyadic) =
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
