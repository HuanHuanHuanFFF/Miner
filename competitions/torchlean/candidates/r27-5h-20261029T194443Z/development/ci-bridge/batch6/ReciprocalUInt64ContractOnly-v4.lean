import ContractExact

namespace R27ReciprocalProof

-- R is floor((B-1)/d), so multiply-high underestimates by at most one.
-- This theorem is about mathematical integers, independent of word wrapping.
theorem reciprocal_estimate_bounds (B a d : Nat) (hB : 0 < B) (ha : a < B) (hd : 0 < d) :
    let R := (B - 1) / d
    let q := a * R / B
    q * d ≤ a ∧ a < (q + 2) * d := by
  dsimp only
  let R := (B - 1) / d
  let q := a * R / B
  change q * d ≤ a ∧ a < (q + 2) * d
  have hR0 : R * d ≤ B - 1 := by
    simpa only [R] using Nat.div_mul_le_self (B - 1) d
  have hR1 : B ≤ (R + 1) * d := by
    have he := Nat.mod_add_div (B - 1) d
    have hr := Nat.mod_lt (B - 1) hd
    change (B - 1) % d + d * R = B - 1 at he
    rw [Nat.add_mul, Nat.one_mul, Nat.mul_comm R d]
    omega
  have hq0 : q * B ≤ a * R := by
    simpa only [q] using Nat.div_mul_le_self (a * R) B
  have hq1 : a * R < (q + 1) * B := by
    have he := Nat.mod_add_div (a * R) B
    have hr := Nat.mod_lt (a * R) hB
    change a * R % B + B * q = a * R at he
    rw [Nat.add_mul, Nat.one_mul, Nat.mul_comm q B]
    omega
  have low : (q * d) * B ≤ a * B := calc
    (q * d) * B = (q * B) * d := by ring
    _ ≤ (a * R) * d := Nat.mul_le_mul_right d hq0
    _ = a * (R * d) := by ring
    _ ≤ a * B := Nat.mul_le_mul_left a (by omega)
  have high : a * B < ((q + 2) * d) * B := calc
    a * B ≤ a * ((R + 1) * d) := Nat.mul_le_mul_left a hR1
    _ = (a * R) * d + a * d := by ring
    _ < ((q + 1) * B) * d + B * d :=
      Nat.add_lt_add (Nat.mul_lt_mul_of_pos_right hq1 hd)
        (Nat.mul_lt_mul_of_pos_right ha hd)
    _ = ((q + 2) * d) * B := by ring
  constructor
  · by_contra h
    have h' : a * B < (q * d) * B :=
      Nat.mul_lt_mul_of_pos_right (by omega) hB
    omega
  · by_contra h
    have h' : ((q + 2) * d) * B ≤ a * B := Nat.mul_le_mul_right B (by omega)
    omega

def corrected (B a d : Nat) : Nat × Nat :=
  let q := a * ((B - 1) / d) / B
  let r := a - q * d
  if d ≤ r then (q + 1, r - d) else (q, r)

theorem corrected_exact (B a d : Nat) (hB : 0 < B) (ha : a < B) (hd : 0 < d) :
    corrected B a d = (a / d, a % d) := by
  have hb := reciprocal_estimate_bounds B a d hB ha hd
  let q := a * ((B - 1) / d) / B
  change q * d ≤ a ∧ a < (q + 2) * d at hb
  let r := a - q * d
  have he : r + q * d = a := Nat.sub_add_cancel hb.1
  have hr : r < 2 * d := by
    have hu := hb.2
    rw [Nat.add_mul] at hu
    omega
  change (if d ≤ r then (q + 1, r - d) else (q, r)) = _
  by_cases hc : d ≤ r
  · rw [if_pos hc]
    have hq : a / d = q + 1 := Nat.div_eq_of_lt_le
      (by rw [Nat.add_mul, Nat.one_mul]; omega)
      (by simpa [Nat.add_assoc] using hb.2)
    have hm := Nat.mod_add_div a d
    rw [hq, Nat.mul_add, Nat.mul_one, Nat.mul_comm d q] at hm
    have hm' : a % d = r - d := by omega
    rw [hq, hm']
  · rw [if_neg hc]
    have hq : a / d = q := Nat.div_eq_of_lt_le hb.1
      (by rw [Nat.add_mul, Nat.one_mul]; omega)
    have hm := Nat.mod_add_div a d
    rw [hq, Nat.mul_comm d q] at hm
    have hm' : a % d = r := by omega
    rw [hq, hm']


theorem reciprocal_divrem (base numerator divisor : Nat)
    (base_pos : 0 < base) (numerator_bound : numerator < base)
    (divisor_pos : 0 < divisor) :
    let reciprocal := (base - 1) / divisor
    let estimate := numerator * reciprocal / base
    let remainder := numerator - estimate * divisor
    (if divisor ≤ remainder then (estimate + 1, remainder - divisor)
     else (estimate, remainder)) = (numerator / divisor, numerator % divisor) :=
  corrected_exact base numerator divisor base_pos numerator_bound divisor_pos

end R27ReciprocalProof



/- R27 owned primitive prototype. Pure word arithmetic only. Correctness bridge
   and emitted native cost remain to be accepted; never use retainedCorrect. -/
namespace R27Reciprocal

@[inline] def mulHigh (a b : UInt64) : UInt64 :=
  let mask : UInt64 := 0xffffffff
  let aLow := a &&& mask
  let bLow := b &&& mask
  let aHigh := a >>> 32
  let bHigh := b >>> 32
  let lowProduct := aLow * bLow
  let crossA := aHigh * bLow
  let crossB := aLow * bHigh
  let middle := (lowProduct >>> 32) + (crossA &&& mask) + (crossB &&& mask)
  aHigh * bHigh + (crossA >>> 32) + (crossB >>> 32) + (middle >>> 32)

@[inline] def prepare (denominator : UInt64) : UInt64 :=
  0xffffffffffffffff / denominator

@[inline] def divRem (numerator denominator reciprocal : UInt64) : UInt64 × UInt64 :=
  if denominator == 0 then (numerator / denominator, numerator % denominator)
  else
    let estimate := mulHigh numerator reciprocal
    let remainder := numerator - estimate * denominator
    if denominator ≤ remainder then (estimate + 1, remainder - denominator)
    else (estimate, remainder)

end R27Reciprocal


/- Own R27 word carrier proof. Split the mathematical product at32 bits, then
   prove each UInt64 intermediate has the required non-wrapping interpretation. -/
namespace R27Reciprocal

theorem low32_value (word : UInt64) :
    (word &&& 0xffffffff).toNat = word.toNat % 2^32 := by
  rw [UInt64.toNat_and]
  exact Nat.and_two_pow_sub_one_eq_mod word.toNat 32

theorem high32_value (word : UInt64) :
    (word >>> 32).toNat = word.toNat / 2^32 := by
  rw [UInt64.toNat_shiftRight]
  simp [Nat.shiftRight_eq_div_pow]

theorem mul32_value (left right : UInt64)
    (left_small : left.toNat < 2^32) (right_small : right.toNat < 2^32) :
    (left * right).toNat = left.toNat * right.toNat := by
  rw [UInt64.toNat_mul]
  apply Nat.mod_eq_of_lt
  have bound := Nat.mul_lt_mul'' left_small right_small
  simpa using bound

theorem high_parts_identity (ll lh hl hh : Nat) :
    (hh * 2^64 + (lh + hl) * 2^32 + ll) / 2^64 =
      hh + lh / 2^32 + hl / 2^32 +
        (ll / 2^32 + lh % 2^32 + hl % 2^32) / 2^32 := by
  omega

theorem mulHigh_toNat (left right : UInt64) :
    (mulHigh left right).toNat = left.toNat * right.toNat / 2^64 := by
  let leftLow := left &&& (0xffffffff : UInt64)
  let rightLow := right &&& (0xffffffff : UInt64)
  let leftHigh := left >>> (32 : UInt64)
  let rightHigh := right >>> (32 : UInt64)
  have leftLow_bound : leftLow.toNat < 2^32 := by dsimp [leftLow]; rw [low32_value]; omega
  have rightLow_bound : rightLow.toNat < 2^32 := by dsimp [rightLow]; rw [low32_value]; omega
  have leftHigh_bound : leftHigh.toNat < 2^32 := by
    have h := left.toNat_lt
    dsimp [leftHigh]; rw [high32_value]; omega
  have rightHigh_bound : rightHigh.toNat < 2^32 := by
    have h := right.toNat_lt
    dsimp [rightHigh]; rw [high32_value]; omega
  let ll := leftLow * rightLow
  let lh := leftLow * rightHigh
  let hl := leftHigh * rightLow
  let hh := leftHigh * rightHigh
  have ll_value : ll.toNat = leftLow.toNat * rightLow.toNat :=
    mul32_value leftLow rightLow leftLow_bound rightLow_bound
  have lh_value : lh.toNat = leftLow.toNat * rightHigh.toNat :=
    mul32_value leftLow rightHigh leftLow_bound rightHigh_bound
  have hl_value : hl.toNat = leftHigh.toNat * rightLow.toNat :=
    mul32_value leftHigh rightLow leftHigh_bound rightLow_bound
  have hh_value : hh.toNat = leftHigh.toNat * rightHigh.toNat :=
    mul32_value leftHigh rightHigh leftHigh_bound rightHigh_bound
  have left_split : left.toNat = leftHigh.toNat * 2^32 + leftLow.toNat := by
    dsimp [leftHigh, leftLow]
    rw [high32_value, low32_value]
    omega
  have right_split : right.toNat = rightHigh.toNat * 2^32 + rightLow.toNat := by
    dsimp [rightHigh, rightLow]
    rw [high32_value, low32_value]
    omega
  have product_split : left.toNat * right.toNat =
      hh.toNat * 2^64 + (lh.toNat + hl.toNat) * 2^32 + ll.toNat := by
    rw [ll_value, lh_value, hl_value, hh_value]
    conv_lhs => rw [left_split, right_split]
    ring
  let middle := (ll >>> (32 : UInt64)) + (hl &&& 0xffffffff) + (lh &&& 0xffffffff)
  have middle_value : middle.toNat = ll.toNat / 2^32 + hl.toNat % 2^32 + lh.toNat % 2^32 := by
    have ll_bound := ll.toNat_lt
    dsimp [middle]
    rw [UInt64.toNat_add, UInt64.toNat_add, high32_value, low32_value, low32_value]
    omega
  have mathematical_high : hh.toNat + hl.toNat / 2^32 + lh.toNat / 2^32 + middle.toNat / 2^32 =
      left.toNat * right.toNat / 2^64 := by
    rw [product_split, middle_value]
    have identity := high_parts_identity ll.toNat lh.toNat hl.toNat hh.toNat
    omega
  have product_bound : left.toNat * right.toNat < 2^64 * 2^64 :=
    Nat.mul_lt_mul'' left.toNat_lt right.toNat_lt
  have high_bound : hh.toNat + hl.toNat / 2^32 + lh.toNat / 2^32 + middle.toNat / 2^32 < 2^64 := by
    rw [mathematical_high]
    omega
  change (hh + (hl >>> 32) + (lh >>> 32) + (middle >>> 32)).toNat = _
  rw [UInt64.toNat_add, UInt64.toNat_add, UInt64.toNat_add,
    high32_value, high32_value, high32_value]
  omega

theorem prepare_toNat (denominator : UInt64) :
    (prepare denominator).toNat = (2^64 - 1) / denominator.toNat := by
  exact UInt64.toNat_div (0xffffffffffffffff : UInt64) denominator

theorem divRem_correct (numerator denominator : UInt64) :
    divRem numerator denominator (prepare denominator) =
      (numerator / denominator, numerator % denominator) := by
  unfold divRem
  split
  · rfl
  · rename_i nonzero
    have denominator_ne : denominator ≠ 0 := by simpa only [beq_iff_eq] using nonzero
    have denominator_pos : 0 < denominator.toNat := by
      apply Nat.pos_of_ne_zero
      intro zero
      exact denominator_ne (UInt64.toNat_inj.mp zero)
    let estimate := mulHigh numerator (prepare denominator)
    let remainder := numerator - estimate * denominator
    change (if denominator ≤ remainder then (estimate + 1, remainder - denominator)
      else (estimate, remainder)) = _
    have estimate_value : estimate.toNat =
        numerator.toNat * ((2^64 - 1) / denominator.toNat) / 2^64 := by
      dsimp [estimate]
      rw [mulHigh_toNat, prepare_toNat]
      norm_num
    obtain ⟨lower, upper⟩ := R27ReciprocalProof.reciprocal_estimate_bounds
      (2^64) numerator.toNat denominator.toNat (by decide) numerator.toNat_lt denominator_pos
    rw [← estimate_value] at lower upper
    have product_fit : estimate.toNat * denominator.toNat < 2^64 :=
      lt_of_le_of_lt lower numerator.toNat_lt
    have product_value : (estimate * denominator).toNat = estimate.toNat * denominator.toNat := by
      rw [UInt64.toNat_mul]
      exact Nat.mod_eq_of_lt product_fit
    have remainder_value : remainder.toNat = numerator.toNat - estimate.toNat * denominator.toNat := by
      dsimp [remainder]
      rw [UInt64.toNat_sub_of_le _ _ (UInt64.le_iff_toNat_le.mpr (by rw [product_value]; exact lower)), product_value]
    have natural_result := R27ReciprocalProof.reciprocal_divrem
      (2^64) numerator.toNat denominator.toNat (by decide) numerator.toNat_lt denominator_pos
    dsimp only at natural_result
    rw [← estimate_value] at natural_result
    by_cases correction : denominator ≤ remainder
    · rw [if_pos correction]
      have natural_correction : denominator.toNat ≤ numerator.toNat - estimate.toNat * denominator.toNat := by
        have h := UInt64.le_iff_toNat_le.mp correction
        rwa [remainder_value] at h
      rw [if_pos natural_correction] at natural_result
      have quotient_eq := congrArg Prod.fst natural_result
      have remainder_eq := congrArg Prod.snd natural_result
      dsimp only at quotient_eq remainder_eq
      have quotient_fit : estimate.toNat + 1 < 2^64 := by
        rw [quotient_eq]
        have h := (numerator / denominator).toNat_lt
        rwa [UInt64.toNat_div] at h
      apply Prod.ext
      · apply UInt64.toNat_inj.mp
        rw [UInt64.toNat_add, UInt64.toNat_one, Nat.mod_eq_of_lt quotient_fit, UInt64.toNat_div]
        exact quotient_eq
      · apply UInt64.toNat_inj.mp
        rw [UInt64.toNat_sub_of_le _ _ correction, remainder_value, UInt64.toNat_mod]
        exact remainder_eq
    · rw [if_neg correction]
      have natural_correction : ¬ denominator.toNat ≤ numerator.toNat - estimate.toNat * denominator.toNat := by
        intro h
        apply correction
        apply UInt64.le_iff_toNat_le.mpr
        rwa [remainder_value]
      rw [if_neg natural_correction] at natural_result
      have quotient_eq := congrArg Prod.fst natural_result
      have remainder_eq := congrArg Prod.snd natural_result
      dsimp only at quotient_eq remainder_eq
      apply Prod.ext
      · apply UInt64.toNat_inj.mp
        rw [UInt64.toNat_div]
        exact quotient_eq
      · apply UInt64.toNat_inj.mp
        rw [remainder_value, UInt64.toNat_mod]
        exact remainder_eq

end R27Reciprocal
