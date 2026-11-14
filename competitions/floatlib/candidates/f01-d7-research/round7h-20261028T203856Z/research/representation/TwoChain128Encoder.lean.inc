/- Independent encoder bridge for the standard-complement two-chain helper.
   This is original word code, not a copy of the anonymous packed caller.
   Exact raw32 field/base/index and final rounding transport remain separate. -/
namespace Submission.R24TwoChain128Encoder
open FloatLib.Numerics.FixedWord
open Submission.R24TwoChain128 (signed64 signed128 run2 run2_exact_signed_sum)

structure Term where
  negative : Bool
  left : UInt64
  right : UInt64
  shift : UInt64

def Guard (t : Term) : Prop :=
  t.left.toNat < 2 ^ 24 ∧ t.right.toNat < 2 ^ 24 ∧
    (t.left = 0 ∨ t.right = 0 ∨ t.shift.toNat ≤ 14)

@[inline] def guard (t : Term) : Bool :=
  decide (t.left < 0x1000000) && decide (t.right < 0x1000000) &&
    ((t.left == 0) || (t.right == 0) || decide (t.shift ≤ 14))

@[inline] def wordMagnitude (t : Term) : UInt64 := (t.left * t.right) <<< t.shift
@[inline] def encode (t : Term) : UInt64 :=
  let m := wordMagnitude t
  if t.negative then 0 - m else m

def mathematicalMagnitude (t : Term) : Nat :=
  t.left.toNat * t.right.toNat * 2 ^ t.shift.toNat
def integerTerm (t : Term) : Int :=
  if t.negative then -(mathematicalMagnitude t : Int) else (mathematicalMagnitude t : Int)
def runEncoded (ts : List Term) : UInt128 := run2 (ts.map encode)

theorem guard_iff (t : Term) : guard t = true ↔ Guard t := by
  simp [guard, Guard, UInt64.lt_iff_toNat_lt, UInt64.le_iff_toNat_le, and_assoc]

theorem product_lt_48 (t : Term) (h : Guard t) :
    t.left.toNat * t.right.toNat < 2 ^ 48 := by
  calc
    _ < 2 ^ 24 * 2 ^ 24 := Nat.mul_lt_mul'' h.1 h.2.1
    _ = 2 ^ 48 := by norm_num

theorem mathematicalMagnitude_lt_62 (t : Term) (h : Guard t) :
    mathematicalMagnitude t < 2 ^ 62 := by
  rcases h.2.2 with hz | hz | hs
  · simp [mathematicalMagnitude, hz]
  · simp [mathematicalMagnitude, hz]
  · have hp := product_lt_48 t h
    have hs' : 2 ^ t.shift.toNat ≤ 2 ^ 14 := Nat.pow_le_pow_right (by decide) hs
    unfold mathematicalMagnitude
    calc
      _ ≤ (t.left.toNat * t.right.toNat) * 2 ^ 14 := Nat.mul_le_mul_left _ hs'
      _ < 2 ^ 48 * 2 ^ 14 := Nat.mul_lt_mul_of_pos_right hp (by decide)
      _ = 2 ^ 62 := by norm_num

theorem wordMagnitude_toNat (t : Term) (h : Guard t) :
    (wordMagnitude t).toNat = mathematicalMagnitude t := by
  by_cases hz : t.left = 0 ∨ t.right = 0
  · rcases hz with hz | hz <;>
      simp [wordMagnitude, mathematicalMagnitude, hz, UInt64.toNat_shiftLeft]
  · have hs0 := (h.2.2.resolve_left (fun hl => hz (Or.inl hl))).resolve_left
      (fun hr => hz (Or.inr hr))
    have hs : t.shift.toNat < 64 := by omega
    have hp := product_lt_48 t h
    have hm : (t.left * t.right).toNat = t.left.toNat * t.right.toNat :=
      uint64_mul_toNat_of_lt _ _ (by omega)
    have hfit : (t.left * t.right).toNat <<< t.shift.toNat < 2 ^ 64 := by
      rw [hm, Nat.shiftLeft_eq]
      have hh := mathematicalMagnitude_lt_62 t h
      unfold mathematicalMagnitude at hh
      omega
    have hw := shiftLeft_toNat (t.left * t.right) t.shift.toNat hs hfit
    simpa only [UInt64.ofNat_toNat, Nat.shiftLeft_eq, hm, wordMagnitude,
      mathematicalMagnitude] using hw

theorem signed_magnitude (negative : Bool) (m : UInt64) (hm : m.toNat < 2 ^ 62) :
    signed64 (if negative then 0 - m else m) =
      if negative then -(m.toNat : Int) else (m.toNat : Int) := by
  cases negative with
  | false =>
    change signed64 m = (m.toNat : Int)
    rw [signed64, if_pos (by omega)]
  | true =>
    change signed64 (0 - m) = -(m.toNat : Int)
    by_cases hz : m.toNat = 0
    · have hm0 : m = 0 := UInt64.toNat_inj.mp (by simpa using hz)
      subst m
      norm_num [signed64]
    · have hneg : (0 - m).toNat = 2 ^ 64 - m.toNat := by
        rw [UInt64.toNat_sub, UInt64.toNat_zero, Nat.add_zero]
        exact Nat.mod_eq_of_lt (by omega)
      rw [signed64, hneg, if_neg (by omega)]
      omega

theorem encode_exact (t : Term) (h : Guard t) : signed64 (encode t) = integerTerm t := by
  have hm := wordMagnitude_toNat t h
  have hb : (wordMagnitude t).toNat < 2 ^ 62 := by
    rw [hm]
    exact mathematicalMagnitude_lt_62 t h
  simpa only [encode, integerTerm, hm] using signed_magnitude t.negative (wordMagnitude t) hb

theorem encode_bound (t : Term) (h : Guard t) : |signed64 (encode t)| < (2 ^ 62 : Int) := by
  have hm : (mathematicalMagnitude t : Int) < 2 ^ 62 := by
    exact_mod_cast mathematicalMagnitude_lt_62 t h
  have hn : (0 : Int) ≤ mathematicalMagnitude t := by omega
  rw [encode_exact t h]
  unfold integerTerm
  split_ifs <;> simpa only [abs_neg, abs_of_nonneg hn] using hm

/- The top root assumes only actual word guards and length. Neither product
   correctness nor the strict signed62 bound is supplied by the caller. -/
theorem runEncoded_exact (ts : List Term) (hn : ts.length < 2 ^ 20)
    (hg : ∀ t ∈ ts, guard t = true) :
    signed128 (runEncoded ts) = (ts.map integerTerm).sum := by
  have hb : ∀ q ∈ ts.map encode, |signed64 q| < (2 ^ 62 : Int) := by
    intro q hq
    obtain ⟨t, ht, rfl⟩ := List.mem_map.mp hq
    exact encode_bound t ((guard_iff t).mp (hg t ht))
  calc
    _ = ((ts.map encode).map signed64).sum :=
      run2_exact_signed_sum _ (by simpa using hn) hb
    _ = (ts.map integerTerm).sum := by
      rw [List.map_map]
      congr 1
      apply List.map_congr_left
      intro t ht
      exact encode_exact t ((guard_iff t).mp (hg t ht))

end Submission.R24TwoChain128Encoder
