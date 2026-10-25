section R16NativeAddProof
set_option maxRecDepth 8192
namespace Submission.A16F
open FloatLib.Floats Competition
open FloatLib.Floats.Formats.BinaryInterchange
@[inline] def ex (u : UInt32) : UInt32 := Model.NativeBinary32.expField u

theorem ex_nat (u : UInt32) : (ex u).toNat = R2W01c.wordExp u := by
  rw [ex, Model.NativeBinary32.expField, UInt32.toNat_and, UInt32.toNat_shiftRight]
  change (u.toNat >>> 23) &&& (2 ^ 8 - 1) = u.toNat / 8388608 % 256
  rw [Nat.and_two_pow_sub_one_eq_mod, Nat.shiftRight_eq_div_pow]

theorem ex_bound (u : UInt32) : (ex u).toNat < 256 := by
  rw [ex_nat]
  exact Nat.mod_lt _ (by decide)

@[inline] def sign (u v : UInt32) : Bool :=
  Bool.xor (decide ((2147483648 : UInt32) ≤ u)) (decide ((2147483648 : UInt32) ≤ v))

theorem sign_eq (u v : UInt32) :
    sign u v = Bool.xor (R2W01c.wordSign u) (R2W01c.wordSign v) := by
  simp only [sign, R2W01c.wordSign, UInt32.le_iff_toNat_le]
  rfl

end Submission.A16F

namespace Submission.A16N

open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange
open FloatLib.Numerics

def rounded (p : Nat) : Nat := roundShiftRightEven p (p.log2 - 23)
def carry (p : Nat) : Nat := if rounded p = 16777216 then 1 else 0
def mantissa (p : Nat) : Nat := if rounded p = 16777216 then 8388608 else rounded p

theorem carry_le (p : Nat) : carry p ≤ 1 := by
  unfold carry
  split <;> omega

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

end Submission.A16N

namespace Submission.A16R

open FloatLib.Numerics

theorem rounded_bounds (n : Nat) (hn : n ≠ 0) (hh : 23 ≤ n.log2) :
    8388608 ≤ Submission.A16N.rounded n ∧
    Submission.A16N.rounded n ≤ 16777216 := by
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

end Submission.A16R

namespace Submission.R16AddWord
open FloatLib.Floats Competition
open FloatLib.Floats.Formats.BinaryInterchange
@[inline] def high (u v : UInt32) : UInt32 :=
  if A16F.ex u < A16F.ex v then v else u

@[inline] def low (u v : UInt32) : UInt32 :=
  if A16F.ex u < A16F.ex v then u else v

@[inline] def gap (u v : UInt32) : UInt32 :=
  A16F.ex (high u v) - A16F.ex (low u v)

@[inline] def sameSign (u v : UInt32) : Bool :=
  A16F.sign u v == false

@[inline] def eligible (u v : UInt32) : Bool :=
  (decide (A16F.ex u - 1 ≤ (253 : UInt32)) &&
    decide (A16F.ex v - 1 ≤ (253 : UInt32))) &&
  (decide (gap u v ≤ (7 : UInt32)) && (sameSign u v || decide ((1 : UInt32) ≤ gap u v)))

@[inline] def magW (u v : UInt32) : UInt32 :=
  let left := R2W01b.mantissa (high u v) <<< gap u v
  let right := R2W01b.mantissa (low u v)
  if sameSign u v then left + right else left - right
theorem normal_field (u : UInt32)
    (h : A16F.ex u - 1 ≤ (253 : UInt32)) :
    0 < R2W01c.wordExp u ∧ R2W01c.wordExp u < 255 := by
  have hb := A16F.ex_bound u
  rw [UInt32.le_iff_toNat_le, UInt32.toNat_sub] at h
  change (4294967295 + (A16F.ex u).toNat) % 4294967296 ≤ 253 at h
  rw [A16F.ex_nat] at h hb
  omega

theorem sorted_exponents (u v : UInt32) :
    R2W01c.wordExp (high u v) = max (R2W01c.wordExp u) (R2W01c.wordExp v) ∧
    R2W01c.wordExp (low u v) = min (R2W01c.wordExp u) (R2W01c.wordExp v) := by
  by_cases h : A16F.ex u < A16F.ex v
  · have hn : R2W01c.wordExp u < R2W01c.wordExp v := by
      have hh := UInt32.lt_iff_toNat_lt.mp h
      simpa only [A16F.ex_nat] using hh
    simp only [high, low, if_pos h]
    exact ⟨(Nat.max_eq_right (Nat.le_of_lt hn)).symm,
      (Nat.min_eq_left (Nat.le_of_lt hn)).symm⟩
  · have hn : R2W01c.wordExp v ≤ R2W01c.wordExp u := by
      have hh : ¬ (A16F.ex u).toNat < (A16F.ex v).toNat := by
        simpa only [UInt32.lt_iff_toNat_lt] using h
      rw [A16F.ex_nat, A16F.ex_nat] at hh
      omega
    simp only [high, low, if_neg h]
    exact ⟨(Nat.max_eq_left hn).symm, (Nat.min_eq_right hn).symm⟩

theorem gap_nat (u v : UInt32) :
    (gap u v).toNat = max (R2W01c.wordExp u) (R2W01c.wordExp v) -
      min (R2W01c.wordExp u) (R2W01c.wordExp v) := by
  have hs := sorted_exponents u v
  have hle : A16F.ex (low u v) ≤ A16F.ex (high u v) := by
    rw [UInt32.le_iff_toNat_le, A16F.ex_nat, A16F.ex_nat, hs.1, hs.2]
    exact Nat.le_trans (Nat.min_le_left _ _) (Nat.le_max_left _ _)
  rw [gap, UInt32.toNat_sub_of_le _ _ hle, A16F.ex_nat,
    A16F.ex_nat, hs.1, hs.2]

theorem sameSign_eq (u v : UInt32) :
    sameSign u v = (R2W01c.wordSign u == R2W01c.wordSign v) := by
  rw [sameSign, A16F.sign_eq]
  cases R2W01c.wordSign u <;> cases R2W01c.wordSign v <;> rfl

theorem sameSign_true (u v : UInt32) (h : sameSign u v = true) :
    R2W01c.wordSign u = R2W01c.wordSign v := by
  rw [sameSign_eq, beq_iff_eq] at h
  exact h

theorem eligible_conditions (u v : UInt32) (h : eligible u v = true) :
    (0 < R2W01c.wordExp u ∧ R2W01c.wordExp u < 255) ∧
    (0 < R2W01c.wordExp v ∧ R2W01c.wordExp v < 255) ∧
    (gap u v).toNat ≤ 7 ∧
    (R2W01c.wordSign u = R2W01c.wordSign v ∨ 1 ≤ (gap u v).toNat) := by
  simp only [eligible, Bool.and_eq_true, Bool.or_eq_true, decide_eq_true_eq] at h
  rcases h with ⟨⟨hu, hv⟩, hg, hs⟩
  refine ⟨normal_field u hu, normal_field v hv, ?_, ?_⟩
  · have hh := UInt32.le_iff_toNat_le.mp hg
    exact hh
  · rcases hs with hs | hs
    · exact Or.inl (sameSign_true u v hs)
    · have hh := UInt32.le_iff_toNat_le.mp hs
      exact Or.inr hh
end Submission.R16AddWord

namespace Submission.A16L

open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange

def magnitude (hiSign loSign : Bool) (hi lo gap : Nat) : Nat :=
  if hiSign = loSign then (hi <<< gap) + lo else (hi <<< gap) - lo

theorem shifted_ne_zero (m d : Nat) (hm : m ≠ 0) : m <<< d ≠ 0 := by
  have hp := (Nat.mul_pos (Nat.pos_of_ne_zero hm) (Nat.two_pow_pos d)).ne'
  simpa only [Nat.shiftLeft_eq', Nat.shiftLeft_eq] using hp

theorem large_left (hi lo gap : Nat)
    (hhi : 8388608 ≤ hi) (hlo : lo < 16777216) (hgap : 1 ≤ gap) :
    lo < hi <<< gap := by
  have hp : 2 ≤ 2 ^ gap := by
    have h : 2 ^ 1 ≤ 2 ^ gap := Nat.pow_le_pow_right (by decide) hgap
    norm_num at h
    exact h
  have hm := Nat.mul_le_mul_left hi hp
  simp only [Nat.shiftLeft_eq', Nat.shiftLeft_eq]
  omega

theorem align_high_low (hiSign loSign : Bool) (hi lo ehi elo : Nat)
    (hhi : hi ≠ 0) (hlo : lo ≠ 0) (he : elo ≤ ehi) :
    Model.addDyadic
      { negative := hiSign, significand := hi, exponent := (ehi : Int) - 150 }
      { negative := loSign, significand := lo, exponent := (elo : Int) - 150 } =
    Model.addDyadic
      { negative := hiSign, significand := hi <<< (ehi - elo),
        exponent := (elo : Int) - 150 }
      { negative := loSign, significand := lo, exponent := (elo : Int) - 150 } := by
  rcases Nat.eq_or_lt_of_le he with heq | hlt
  · subst ehi
    simp only [Nat.sub_self, Nat.shiftLeft_eq', Nat.shiftLeft_eq, Nat.pow_zero,
      Nat.mul_one]
  · exact
      Model.addDyadic_alignLeftOffset 150 hiSign loSign hi lo ehi elo hhi hlo hlt

theorem exact_high_low (hiSign loSign : Bool) (hi lo ehi elo : Nat)
    (hhi : 8388608 ≤ hi) (hlo : 0 < lo) (hloUpper : lo < 16777216)
    (he : elo ≤ ehi) (hdomain : hiSign = loSign ∨ 1 ≤ ehi - elo) :
    Model.addDyadic
      { negative := hiSign, significand := hi, exponent := (ehi : Int) - 150 }
      { negative := loSign, significand := lo, exponent := (elo : Int) - 150 } =
      { negative := hiSign, significand := magnitude hiSign loSign hi lo (ehi - elo),
        exponent := (elo : Int) - 150 } := by
  have hhi0 : hi ≠ 0 := by omega
  have hlo0 : lo ≠ 0 := by omega
  have hshift := shifted_ne_zero hi (ehi - elo) hhi0
  rw [align_high_low hiSign loSign hi lo ehi elo hhi0 hlo0 he]
  by_cases hs : hiSign = loSign
  · subst loSign
    simpa only [magnitude, ↓reduceIte] using
      Model.addDyadic_sameSign_sameExponent hiSign (hi <<< (ehi - elo)) lo
        ((elo : Int) - 150) hshift hlo0
  · have hd : 1 ≤ ehi - elo := hdomain.resolve_left hs
    simpa only [magnitude, if_neg hs, ↓reduceIte] using
      Model.addDyadic_oppositeSign_sameExponent_largeLeft hiSign loSign
        (hi <<< (ehi - elo)) lo ((elo : Int) - 150) hshift hlo0 hs
        (large_left hi lo (ehi - elo) hhi hloUpper hd)

theorem exact_low_high (hiSign loSign : Bool) (hi lo ehi elo : Nat)
    (hhi : 8388608 ≤ hi) (hlo : 0 < lo) (hloUpper : lo < 16777216)
    (he : elo ≤ ehi) (hdomain : hiSign = loSign ∨ 1 ≤ ehi - elo) :
    Model.addDyadic
      { negative := loSign, significand := lo, exponent := (elo : Int) - 150 }
      { negative := hiSign, significand := hi, exponent := (ehi : Int) - 150 } =
      { negative := hiSign, significand := magnitude hiSign loSign hi lo (ehi - elo),
        exponent := (elo : Int) - 150 } := by
  rw [Model.addDyadic_comm]
  exact exact_high_low hiSign loSign hi lo ehi elo hhi hlo hloUpper he hdomain

theorem spec_add_of_decodes {fmt : FloatFormat} (x y : Model fmt)
    (dx dy : FloatLib.Numerics.Dyadic)
    (hx : Model.toDyadic? x = some dx) (hy : Model.toDyadic? y = some dy) :
    Model.Spec.add x y = Model.roundDyadic fmt (Model.addDyadic dx dy) := by
  unfold Model.Spec.add
  rw [hx, hy]

end Submission.A16L

namespace Submission.A16L
theorem magnitude_bounds (sh sl : Bool) (hi lo d : Nat)
    (hhi : 8388608 ≤ hi) (hhi' : hi < 16777216)
    (hlo : 8388608 ≤ lo) (hlo' : lo < 16777216)
    (hd : d ≤ 7) (hdom : sh = sl ∨ 1 ≤ d) :
    1 ≤ magnitude sh sl hi lo d ∧ magnitude sh sl hi lo d ≤ 2164260735 := by
  by_cases hs : sh = sl
  · interval_cases d <;> simp only [magnitude, if_pos hs, Nat.shiftLeft_eq', Nat.shiftLeft_eq] <;> norm_num <;> omega
  · have hg : 1 ≤ d := hdom.resolve_left hs
    interval_cases d <;> simp only [magnitude, if_neg hs, Nat.shiftLeft_eq', Nat.shiftLeft_eq] <;> norm_num <;> omega
end Submission.A16L

namespace Submission.R16AddWord
open FloatLib.Floats Competition
open FloatLib.Floats.Formats.BinaryInterchange
open FloatLib.Numerics
abbrev magN (u v : UInt32) : Nat :=
  A16L.magnitude (R2W01c.wordSign (high u v))
    (R2W01c.wordSign (low u v)) (R2W01b.mantissa (high u v)).toNat
    (R2W01b.mantissa (low u v)).toNat (gap u v).toNat
theorem gap_pair (u v : UInt32) :
    (gap u v).toNat = R2W01c.wordExp (high u v) - R2W01c.wordExp (low u v) := by
  rw [gap_nat, (sorted_exponents u v).1, (sorted_exponents u v).2]

theorem sameSign_sorted (u v : UInt32) :
    sameSign u v = (R2W01c.wordSign (high u v) == R2W01c.wordSign (low u v)) := by
  rw [sameSign_eq]
  by_cases h : A16F.ex u < A16F.ex v
  · simp only [high, low, if_pos h]
    cases R2W01c.wordSign u <;> cases R2W01c.wordSign v <;> rfl
  · simp only [high, low, if_neg h]

theorem sorted_domain (u v : UInt32) (hd : eligible u v = true) :
    (0 < R2W01c.wordExp (high u v) ∧ R2W01c.wordExp (high u v) < 255) ∧
    (0 < R2W01c.wordExp (low u v) ∧ R2W01c.wordExp (low u v) < 255) ∧
    (gap u v).toNat ≤ 7 ∧
    (R2W01c.wordSign (high u v) = R2W01c.wordSign (low u v) ∨
      1 ≤ (gap u v).toNat) := by
  have hc := eligible_conditions u v hd
  have hs := sorted_exponents u v
  have hehi : 0 < R2W01c.wordExp (high u v) ∧
      R2W01c.wordExp (high u v) < 255 := by rw [hs.1]; omega
  have helo : 0 < R2W01c.wordExp (low u v) ∧
      R2W01c.wordExp (low u v) < 255 := by rw [hs.2]; omega
  refine ⟨hehi, helo, hc.2.2.1, ?_⟩
  · rcases hc.2.2.2 with hsign | hgap
    · left
      by_cases h : A16F.ex u < A16F.ex v
      · simpa only [high, low, if_pos h] using hsign.symm
      · simpa only [high, low, if_neg h] using hsign
    · exact Or.inr hgap
theorem magN_bounds (u v : UInt32) (hd : eligible u v = true) :
    1 ≤ magN u v ∧ magN u v ≤ 2164260735 := by
  have hh := R2W01c.mantissa_bounds (high u v)
  have hl := R2W01c.mantissa_bounds (low u v)
  have hs := sorted_domain u v hd
  exact A16L.magnitude_bounds _ _ _ _ _ hh.1 hh.2 hl.1 hl.2 hs.2.2.1 hs.2.2.2
theorem left_word_nat (u v : UInt32) (hd : eligible u v = true) :
    (R2W01b.mantissa (high u v) <<< gap u v).toNat =
      (R2W01b.mantissa (high u v)).toNat <<< (gap u v).toNat := by
  have hm := R2W01c.mantissa_bounds (high u v)
  have hg := (eligible_conditions u v hd).2.2.1
  have hp : 2 ^ (gap u v).toNat ≤ 128 := by
    have h : 2 ^ (gap u v).toNat ≤ 2 ^ 7 :=
      Nat.pow_le_pow_right (by decide : 1 ≤ (2 : Nat)) hg
    norm_num at h
    exact h
  have hx := Nat.mul_le_mul_left (R2W01b.mantissa (high u v)).toNat hp
  rw [UInt32.toNat_shiftLeft, Nat.mod_eq_of_lt (show (gap u v).toNat < 32 by omega)]
  rw [Nat.shiftLeft_eq]
  exact Nat.mod_eq_of_lt (by omega)

theorem magW_nat (u v : UInt32) (hd : eligible u v = true) :
    (magW u v).toNat = magN u v := by
  have hb := magN_bounds u v hd
  have hs := sorted_domain u v hd
  by_cases hsame : sameSign u v = true
  · have heq : R2W01c.wordSign (high u v) = R2W01c.wordSign (low u v) := by
      rw [sameSign_sorted, beq_iff_eq] at hsame
      exact hsame
    rw [magW, if_pos hsame, UInt32.toNat_add, left_word_nat u v hd]
    have hn : magN u v =
        ((R2W01b.mantissa (high u v)).toNat <<< (gap u v).toNat) +
          (R2W01b.mantissa (low u v)).toNat := by
      simp only [magN, A16L.magnitude, if_pos heq]
    rw [hn] at hb ⊢
    exact Nat.mod_eq_of_lt (by omega)
  · have hne : R2W01c.wordSign (high u v) ≠ R2W01c.wordSign (low u v) := by
      intro heq
      have ht : sameSign u v = true := by rw [sameSign_sorted, beq_iff_eq]; exact heq
      exact hsame ht
    have hg : 1 ≤ (gap u v).toNat := hs.2.2.2.resolve_left hne
    have hleft := A16L.large_left _ _ _
      (R2W01c.mantissa_bounds (high u v)).1
      (R2W01c.mantissa_bounds (low u v)).2 hg
    have hle : R2W01b.mantissa (low u v) ≤ R2W01b.mantissa (high u v) <<< gap u v := by
      rw [UInt32.le_iff_toNat_le, left_word_nat u v hd]
      omega
    rw [magW, if_neg hsame, UInt32.toNat_sub_of_le _ _ hle, left_word_nat u v hd]
    exact (if_neg hne).symm
theorem raw_add_dyadic (u v : UInt32) (hd : eligible u v = true) :
    Model.add (R2W01c.rawModel u) (R2W01c.rawModel v) =
      Model.roundDyadic FloatFormat.binary32
        ⟨R2W01c.wordSign (high u v), magN u v,
          (R2W01c.wordExp (low u v) : Int) - 150⟩ := by
  have hc := eligible_conditions u v hd
  have hs := sorted_domain u v hd
  have hsort := sorted_exponents u v
  have horder : R2W01c.wordExp (low u v) ≤ R2W01c.wordExp (high u v) := by
    rw [hsort.1, hsort.2]
    exact Nat.le_trans (Nat.min_le_left _ _) (Nat.le_max_left _ _)
  have hgap := gap_pair u v
  have hdomain : R2W01c.wordSign (high u v) = R2W01c.wordSign (low u v) ∨
      1 ≤ R2W01c.wordExp (high u v) - R2W01c.wordExp (low u v) := by
    rw [← hgap]
    exact hs.2.2.2
  have hhi := R2W01c.mantissa_bounds (high u v)
  have hlo := R2W01c.mantissa_bounds (low u v)
  have hmag : A16L.magnitude
      (R2W01c.wordSign (high u v)) (R2W01c.wordSign (low u v))
      (R2W01b.mantissa (high u v)).toNat (R2W01b.mantissa (low u v)).toNat
      (R2W01c.wordExp (high u v) - R2W01c.wordExp (low u v)) = magN u v := by
    unfold magN
    rw [hgap]
  have hsum : Model.addDyadic
      { negative := R2W01c.wordSign u, significand := (R2W01b.mantissa u).toNat,
        exponent := (R2W01c.wordExp u : Int) - 150 }
      { negative := R2W01c.wordSign v, significand := (R2W01b.mantissa v).toNat,
        exponent := (R2W01c.wordExp v : Int) - 150 } =
      { negative := R2W01c.wordSign (high u v), significand := magN u v,
        exponent := (R2W01c.wordExp (low u v) : Int) - 150 } := by
    by_cases ho : A16F.ex u < A16F.ex v
    · have hx := A16L.exact_low_high
        (R2W01c.wordSign (high u v)) (R2W01c.wordSign (low u v))
        (R2W01b.mantissa (high u v)).toNat (R2W01b.mantissa (low u v)).toNat
        (R2W01c.wordExp (high u v)) (R2W01c.wordExp (low u v))
        hhi.1 (by omega) hlo.2 horder hdomain
      rw [hmag] at hx
      simpa only [high, low, if_pos ho] using hx
    · have hx := A16L.exact_high_low
        (R2W01c.wordSign (high u v)) (R2W01c.wordSign (low u v))
        (R2W01b.mantissa (high u v)).toNat (R2W01b.mantissa (low u v)).toNat
        (R2W01c.wordExp (high u v)) (R2W01c.wordExp (low u v))
        hhi.1 (by omega) hlo.2 horder hdomain
      rw [hmag] at hx
      simpa only [high, low, if_neg ho] using hx

  rw [Model.Proof.add_eq_spec]
  rw [A16L.spec_add_of_decodes _ _ _ _
    (A16N.raw_normal_decode u hc.1.1 hc.1.2)
    (A16N.raw_normal_decode v hc.2.1.1 hc.2.1.2), hsum]
end Submission.R16AddWord

namespace Submission.A16I

open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange
open FloatLib.Numerics

theorem uint32_bits_eq_roundDyadic (n : UInt32) :
    n.toFloat32.toBits = Model.NativeBinary32.roundDyadic
      (⟨false, n.toNat, 0⟩ : FloatLib.Numerics.Dyadic) := by
  have hw : ExecFloat.Binary.ofFloat32 n.toFloat32 =
      ExecFloat.Binary.ofBits32
        (Model.NativeBinary32.roundDyadic (⟨false, n.toNat, 0⟩ : FloatLib.Numerics.Dyadic)) := by
    apply ExecFloat.Binary.toModel_inj.mp
    change R2W01c.nativeModel n.toFloat32 = R2W01c.rawModel
      (Model.NativeBinary32.roundDyadic (⟨false, n.toNat, 0⟩ : FloatLib.Numerics.Dyadic))
    rw [R2W01c.rawModel_eq_native32, Model.NativeBinary32.ofUInt32_roundDyadic]
    exact R2W01c.uint32_model_eq_roundDyadic n
  have hbits := congrArg ExecFloat.Binary.toBits32 hw
  simpa only [ExecFloat.Binary.toBits32_ofFloat32,
    ExecFloat.Binary.toBits32_ofBits32] using hbits

theorem uint32_native_fields_of_shape (n : UInt32) (em f : Nat)
    (he : em < 256) (hf : f < 8388608)
    (hshape : Model.NativeBinary32.roundDyadic
      (⟨false, n.toNat, 0⟩ : FloatLib.Numerics.Dyadic) = Model.NativeBinary32.mkBits false em f) :
    (Model.NativeBinary32.expField n.toFloat32.toBits).toNat = em ∧
    (Model.NativeBinary32.fracField n.toFloat32.toBits).toNat = f := by
  rw [uint32_bits_eq_roundDyadic, hshape]
  constructor
  · rw [← Model.NativeBinary32.toUInt32_ofFields, Model.NativeBinary32.expField_toNat]
    exact Model.expField_ofFields_of_lt FloatFormat.binary32 false em f he
  · rw [← Model.NativeBinary32.toUInt32_ofFields, Model.NativeBinary32.fracField_toNat]
    exact Model.fracField_ofFields_of_lt FloatFormat.binary32 false em f hf

end Submission.A16I

namespace Submission.R16AddWord
open FloatLib.Floats Competition
open FloatLib.Floats.Formats.BinaryInterchange
open FloatLib.Numerics

theorem native_high_fields (n : UInt32) (hn : 8388608 ≤ n.toNat) :
    (Model.NativeBinary32.expField n.toFloat32.toBits).toNat =
      n.toNat.log2 + A16N.carry n.toNat + 127 ∧
    (Model.NativeBinary32.fracField n.toFloat32.toBits).toNat =
      A16N.mantissa n.toNat - 8388608 ∧
    150 ≤ n.toNat.log2 + A16N.carry n.toNat + 127 ∧
    n.toNat.log2 + A16N.carry n.toNat + 127 ≤ 159 := by
  have hn0 : n.toNat ≠ 0 := by omega
  have hl : 23 ≤ n.toNat.log2 := (Nat.le_log2 hn0).2 (by norm_num; exact hn)
  have hb := n.toNat_lt_size
  have hu : n.toNat.log2 < 32 := (Nat.log2_lt hn0).2 hb
  have hc := A16N.carry_le n.toNat
  have hr := A16R.rounded_bounds n.toNat hn0 hl
  have hf : A16N.mantissa n.toNat - 8388608 < 8388608 := by
    by_cases h : A16N.rounded n.toNat = 16777216
    · simp [A16N.mantissa, h]
    · simp only [A16N.mantissa, h, ↓reduceIte]
      omega
  have hs := A16N.native_round_normal false n.toNat 0 hn0 hl (by omega) (by omega)
  have he : Int.toNat ((n.toNat.log2 : Int) + 0 + (A16N.carry n.toNat : Int) + 127) =
      n.toNat.log2 + A16N.carry n.toNat + 127 := by omega
  rw [he] at hs
  have hp := A16I.uint32_native_fields_of_shape n _ _ (by omega) hf hs
  exact ⟨hp.1, hp.2, by omega, by omega⟩

@[inline] def middleWord (u v : UInt32) : UInt32 := (magW u v).toFloat32.toBits
@[inline] def resultExponent (u v : UInt32) : UInt32 :=
  A16F.ex (middleWord u v) + A16F.ex (low u v) - (150 : UInt32)
@[inline] def resultSign (u v : UInt32) : Bool := decide ((2147483648 : UInt32) ≤ high u v)
@[inline] def nativeCore (u v : UInt32) : UInt32 :=
  let mid := middleWord u v
  FastMul.mkW (resultSign u v)
    (A16F.ex mid + A16F.ex (low u v) - (150 : UInt32))
    (Model.NativeBinary32.fracField mid)

theorem resultSign_eq (u v : UInt32) : resultSign u v = R2W01c.wordSign (high u v) := by
  simp only [resultSign, R2W01c.wordSign, UInt32.le_iff_toNat_le]
  rfl

theorem result_fields (u v : UInt32) (hd : eligible u v = true)
    (hn : (8388608 : UInt32) ≤ magW u v) :
    (resultExponent u v).toNat =
      (magN u v).log2 + A16N.carry (magN u v) +
        R2W01c.wordExp (low u v) - 23 ∧
    1 ≤ (resultExponent u v).toNat ∧
    (Model.NativeBinary32.fracField (middleWord u v)).toNat =
      A16N.mantissa (magN u v) - 8388608 := by
  have hn' : 8388608 ≤ (magW u v).toNat := UInt32.le_iff_toNat_le.mp hn
  have hp := native_high_fields (magW u v) hn'
  rw [magW_nat u v hd] at hp
  have hd' := sorted_domain u v hd
  have ha0 := hd'.2.1.1
  have ha1 := hd'.2.1.2
  have hm : (A16F.ex (middleWord u v)).toNat =
      (magN u v).log2 + A16N.carry (magN u v) + 127 := hp.1
  have hadd : (A16F.ex (middleWord u v) + A16F.ex (low u v)).toNat =
      (magN u v).log2 + A16N.carry (magN u v) + 127 +
        R2W01c.wordExp (low u v) := by
    rw [UInt32.toNat_add, hm, A16F.ex_nat]
    exact Nat.mod_eq_of_lt (by omega)
  have hle : (150 : UInt32) ≤ A16F.ex (middleWord u v) + A16F.ex (low u v) := by
    rw [UInt32.le_iff_toNat_le, hadd]
    change 150 ≤ _
    omega
  have he : (resultExponent u v).toNat =
      (magN u v).log2 + A16N.carry (magN u v) +
        R2W01c.wordExp (low u v) - 23 := by
    rw [resultExponent, UInt32.toNat_sub_of_le _ _ hle, hadd]
    change _ - 150 = _
    omega
  exact ⟨he, by rw [he]; omega, hp.2.1⟩

theorem nativeCore_word (u v : UInt32) (hd : eligible u v = true)
    (hn : (8388608 : UInt32) ≤ magW u v) :
    nativeCore u v = Model.NativeBinary32.mkBits (R2W01c.wordSign (high u v))
      ((magN u v).log2 + A16N.carry (magN u v) + R2W01c.wordExp (low u v) - 23)
      (A16N.mantissa (magN u v) - 8388608) := by
  have h := result_fields u v hd hn
  change FastMul.mkW (resultSign u v) (resultExponent u v)
    (Model.NativeBinary32.fracField (middleWord u v)) = _
  calc
    _ = FastMul.mkW (resultSign u v) (UInt32.ofNat (resultExponent u v).toNat)
        (UInt32.ofNat (Model.NativeBinary32.fracField (middleWord u v)).toNat) := by
          rw [UInt32.ofNat_toNat, UInt32.ofNat_toNat]
    _ = _ := by rw [FastMul.mkW_ofNat, resultSign_eq, h.1, h.2.2]

theorem nativeCore_model (u v : UInt32) (hd : eligible u v = true)
    (hn : (8388608 : UInt32) ≤ magW u v)
    (he : resultExponent u v - 1 ≤ (253 : UInt32)) :
    Model.NativeBinary32.ofUInt32 (nativeCore u v) =
      Model.add (R2W01c.rawModel u) (R2W01c.rawModel v) := by
  have hf := result_fields u v hd hn
  have hN : 8388608 ≤ magN u v := by
    have h := UInt32.le_iff_toNat_le.mp hn
    simpa [magW_nat u v hd] using h
  have hN0 : magN u v ≠ 0 := by omega
  have hl : 23 ≤ (magN u v).log2 := (Nat.le_log2 hN0).2 (by norm_num; exact hN)
  have ha := (sorted_domain u v hd).2.1.1
  have hc := A16N.carry_le (magN u v)
  have hle : (1 : UInt32) ≤ resultExponent u v := UInt32.le_iff_toNat_le.mpr hf.2.1
  have hup : (resultExponent u v).toNat ≤ 254 := by
    rw [UInt32.le_iff_toNat_le, UInt32.toNat_sub_of_le _ _ hle] at he
    change (resultExponent u v).toNat - 1 ≤ 253 at he
    omega
  rw [hf.1] at hup
  have hmin : -126 ≤ ((magN u v).log2 : Int) + ((R2W01c.wordExp (low u v) : Int) - 150) := by omega
  have hmax : ((magN u v).log2 : Int) + ((R2W01c.wordExp (low u v) : Int) - 150) +
      (A16N.carry (magN u v) : Int) ≤ 127 := by omega
  have hexp : Int.toNat (((magN u v).log2 : Int) + ((R2W01c.wordExp (low u v) : Int) - 150) +
      (A16N.carry (magN u v) : Int) + 127) =
      (magN u v).log2 + A16N.carry (magN u v) + R2W01c.wordExp (low u v) - 23 := by omega
  rw [nativeCore_word u v hd hn, Model.NativeBinary32.ofUInt32_mkBits,
    raw_add_dyadic u v hd, A16N.model_round_normal _ _ _ hN0 hl hmin hmax, hexp]

theorem nativeCore_spec (x y : Binary32) (hd : eligible x.raw.1 y.raw.1 = true)
    (hn : (8388608 : UInt32) ≤ magW x.raw.1 y.raw.1)
    (he : resultExponent x.raw.1 y.raw.1 - 1 ≤ (253 : UInt32)) :
    R7W02.fromRaw (nativeCore x.raw.1 y.raw.1) = ExecFloat.Spec.add x y := by
  apply Configured.Family.toModel_injective
  change ExecFloat.Binary.toModel (R7W02.fromRaw (nativeCore x.raw.1 y.raw.1)) = ExecFloat.Binary.toModel (ExecFloat.Spec.add x y)
  rw [R7W02.fromRaw_toModel, ← ExecFloat.Proof.add_eq_spec x y,
    R7Native.toModelExecAdd, ← Model.Proof.add_eq_spec,
    R7W02.exec_toModel_eq_rawModel x, R7W02.exec_toModel_eq_rawModel y,
    ← R2W01c.rawModel_eq_native32 x.raw.1, ← R2W01c.rawModel_eq_native32 y.raw.1]
  exact nativeCore_model x.raw.1 y.raw.1 hd hn he

@[inline] def guardedAdd (fallback : Binary32 → Binary32 → Binary32) (x y : Binary32) : Binary32 :=
  let u := x.raw.1
  let v := y.raw.1
  if eligible u v then
    let n := magW u v
    if (8388608 : UInt32) ≤ n then
      let mid := n.toFloat32.toBits
      let e := A16F.ex mid + A16F.ex (low u v) - (150 : UInt32)
      if e - 1 ≤ (253 : UInt32) then
        R7W02.fromRaw (FastMul.mkW (resultSign u v) e (Model.NativeBinary32.fracField mid))
      else fallback x y
    else fallback x y
  else fallback x y

theorem guardedAdd_spec (fallback : Binary32 → Binary32 → Binary32)
    (hf : ∀ x y, fallback x y = ExecFloat.Spec.add x y) (x y : Binary32) :
    guardedAdd fallback x y = ExecFloat.Spec.add x y := by
  unfold guardedAdd
  try dsimp only
  split
  · rename_i hd
    try dsimp only
    split
    · rename_i hn
      try dsimp only
      split
      · rename_i he
        exact nativeCore_spec x y hd hn he
      · exact hf x y
    · exact hf x y
  · exact hf x y
end Submission.R16AddWord

end R16NativeAddProof
