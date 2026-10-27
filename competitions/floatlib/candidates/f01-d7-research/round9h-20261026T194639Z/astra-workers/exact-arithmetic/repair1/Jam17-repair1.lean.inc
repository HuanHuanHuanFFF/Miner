namespace Submission.R19Jam17

open FloatLib.Numerics

/-- Keep every quotient bit, and make the bottom bit sticky. -/
def jamNat (p : Nat) : Nat :=
  p / 131072 + if p % 131072 = 0 then 0 else 1 - (p / 131072) % 2

theorem or_one (n : Nat) : n ||| 1 = n + (1 - n % 2) := by
  have hd : (n ||| 1) / 2 = n / 2 := by
    rw [Nat.or_div_two]
    simp
  have hm : (n ||| 1) % 2 = 1 := by
    apply Nat.or_mod_two_eq_one.mpr
    right
    decide
  omega

theorem jamNat_eq (p : Nat) :
    jamNat p = (p / 131072) ||| (if p % 131072 = 0 then 0 else 1) := by
  by_cases hz : p % 131072 = 0
  · simp [jamNat, hz]
  · simp [jamNat, hz, or_one]

/-- Both possible original product exponents retain at least six low bits. -/
theorem rne_jam (p k : Nat) (hk : k = 6 ∨ k = 7) :
    roundShiftRightEven (jamNat p) k = roundShiftRightEven p (k + 17) := by
  rcases hk with rfl | rfl <;>
    simp only [roundShiftRightEven_eq_roundQuotientEven] <;>
    norm_num <;>
    unfold jamNat roundQuotientEven <;>
    dsimp only <;>
    simp only [beq_iff_eq] <;>
    split_ifs <;> omega

theorem jam_bounds (p : Nat)
    (hlo : 70368744177664 ≤ p) (hhi : p ≤ 281474943156225) :
    536870912 ≤ jamNat p ∧ jamNat p ≤ 2147483393 := by
  unfold jamNat
  split <;> omega

theorem leading_cases (p : Nat)
    (hlo : 70368744177664 ≤ p) (hhi : p ≤ 281474943156225) :
    (p.log2 = 46 ∧ (jamNat p).log2 = 29) ∨
      (p.log2 = 47 ∧ (jamNat p).log2 = 30) := by
  have hp : p ≠ 0 := by omega
  have hj := jam_bounds p hlo hhi
  have hj0 : jamNat p ≠ 0 := by omega
  have hl : 46 ≤ p.log2 := (Nat.le_log2 hp).2 (by norm_num; omega)
  have hu : p.log2 < 48 := (Nat.log2_lt hp).2 (by norm_num; omega)
  have hjl : 29 ≤ (jamNat p).log2 := (Nat.le_log2 hj0).2 (by norm_num; omega)
  have hju : (jamNat p).log2 < 31 := (Nat.log2_lt hj0).2 (by norm_num; omega)
  by_cases hb : p < 140737488355328
  · have hp46 : p.log2 < 47 := (Nat.log2_lt hp).2 (by norm_num; omega)
    have hjb : jamNat p < 1073741824 := by
      unfold jamNat
      split <;> omega
    have hj29 : (jamNat p).log2 < 30 := (Nat.log2_lt hj0).2 (by norm_num; omega)
    exact Or.inl ⟨by omega, by omega⟩
  · have hp47 : 47 ≤ p.log2 := (Nat.le_log2 hp).2 (by norm_num; omega)
    have hjb : 1073741824 ≤ jamNat p := by
      unfold jamNat
      split <;> omega
    have hj30 : 30 ≤ (jamNat p).log2 := (Nat.le_log2 hj0).2 (by norm_num; omega)
    exact Or.inr ⟨by omega, by omega⟩

@[inline] def jamWord (p : UInt64) : UInt32 :=
  (p >>> 17).toUInt32 ||| (if p &&& 131071 == 0 then 0 else 1)

theorem jamWord_nat (p : UInt64) (hp : p.toNat ≤ 281474943156225) :
    (jamWord p).toNat = jamNat p.toNat := by
  have hs : (p >>> 17).toNat = p.toNat / 131072 := by
    rw [UInt64.toNat_shiftRight]
    change p.toNat >>> 17 = _
    rw [Nat.shiftRight_eq_div_pow]
  have hn : (p >>> 17).toUInt32.toNat = p.toNat / 131072 := by
    rw [Submission.FastMul.toUInt32_eq]
    change (p >>> 17).toNat % 4294967296 = _
    rw [hs]
    exact Nat.mod_eq_of_lt (by omega)
  have hm : (p &&& 131071).toNat = p.toNat % 131072 := by
    rw [UInt64.toNat_and]
    change p.toNat &&& (2 ^ 17 - 1) = p.toNat % 2 ^ 17
    exact Nat.and_two_pow_sub_one_eq_mod _ 17
  have hz : (p &&& 131071 == 0) = true ↔ p.toNat % 131072 = 0 := by
    simp only [beq_iff_eq]
    constructor
    · intro h
      rw [← hm, h]
      rfl
    · intro h
      apply UInt64.toNat.inj
      change (p &&& 131071).toNat = 0
      exact hm.trans h
  rw [jamNat_eq]
  by_cases h : p.toNat % 131072 = 0
  · have hh := hz.mpr h
    simp [jamWord, hh, UInt32.toNat_or, hn, h]
  · have hh : (p &&& 131071 == 0) = false := Bool.eq_false_iff.mpr (by
      intro hc
      exact h (hz.mp hc))
    simp [jamWord, hh, UInt32.toNat_or, hn, h]

theorem jam_roundtrip (p : UInt64)
    (hlo : 70368744177664 ≤ p.toNat) (hhi : p.toNat ≤ 281474943156225) :
    (jamWord p).toFloat32.toUInt32.toNat =
      roundShiftRightEven p.toNat (p.toNat.log2 - 23) * 2 ^ (p.toNat.log2 - 40) := by
  have hw := jamWord_nat p hhi
  have hj := jam_bounds p.toNat hlo hhi
  have hr := R16UInt32Roundtrip.high_roundtrip_RNE (jamWord p)
    (by rw [hw]; omega) (by rw [hw]; omega)
  rw [hw] at hr
  rw [hr]
  unfold R14NatNormal.rounded
  rcases leading_cases p.toNat hlo hhi with ⟨hp,hj⟩ | ⟨hp,hj⟩
  · rw [hp,hj]
    exact congrArg (fun q => q * 64) (rne_jam p.toNat 6 (Or.inl rfl))
  · rw [hp,hj]
    exact congrArg (fun q => q * 128) (rne_jam p.toNat 7 (Or.inr rfl))

@[inline] def normalCore (sum u v : UInt32) : UInt32 :=
  let a := (u &&& (0x7fffff : UInt32)) ||| (0x800000 : UInt32)
  let b := (v &&& (0x7fffff : UInt32)) ||| (0x800000 : UInt32)
  let product : UInt64 := a.toUInt64 * b.toUInt64
  let r : UInt32 := (jamWord product).toFloat32.toUInt32
  let high : UInt32 := r >>> 30
  let q := r >>> ((6 : UInt32) + high)
  let e := sum - (127 : UInt32) + high
  ((u ^^^ v) &&& (0x80000000 : UInt32)) ||| (e <<< 23) ||| (q - (0x800000 : UInt32))

@[inline] def guardedMul (fallback : Competition.Binary32 → Competition.Binary32 → Competition.Binary32)
    (x y : Competition.Binary32) : Competition.Binary32 :=
  let u := x.raw.1
  let v := y.raw.1
  let eu := (u >>> 23) &&& (255 : UInt32)
  let ev := (v >>> 23) &&& (255 : UInt32)
  if eu - 1 ≤ (253 : UInt32) ∧ ev - 1 ≤ (253 : UInt32) then
    let s := eu + ev
    if s - 128 ≤ (252 : UInt32) then R7W02.fromRaw (normalCore s u v)
    else fallback x y
  else fallback x y

/-- Complete guarded diagnostic caller; not the public benchmark entry yet. -/
@[noinline] def diagnosticEntry (x y : Competition.Binary32) : Competition.Binary32 :=
  guardedMul Submission.mul x y

end Submission.R19Jam17
