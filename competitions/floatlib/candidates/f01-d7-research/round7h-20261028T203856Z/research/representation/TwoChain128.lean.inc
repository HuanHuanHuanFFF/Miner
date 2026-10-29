/- R24 clean-room two-chain word probe. Only fixed MIT FloatLib APIs are
   used. This consumes standard two's-complement Int64 encodings, not the
   former source's deferred S-c state. Caller integration remains separate. -/
namespace Submission.R24TwoChain128
open FloatLib.Numerics.FixedWord

def signed64 (q : UInt64) : Int :=
  if q.toNat < 2 ^ 63 then (q.toNat : Int) else (q.toNat : Int) - 2 ^ 64

def signed128 (v : UInt128) : Int :=
  if v.toNat < 2 ^ 127 then (v.toNat : Int) else (v.toNat : Int) - 2 ^ 128

def Represents (v : UInt128) (z : Int) : Prop :=
  ∃ k : Int, (v.toNat : Int) = z + k * 2 ^ 128

@[inline] def high (q : UInt64) : UInt64 :=
  if q < 0x8000000000000000 then 0 else 0xffffffffffffffff

@[inline] def extend (q : UInt64) : UInt128 := ⟨high q, q⟩

/- Native word implementation. UInt128 is returned only at the outer
   boundary; the actual accumulation loop below carries four scalar words. -/
@[inline] def merge (ahi alo bhi blo : UInt64) : UInt128 :=
  let lo := alo + blo
  let carry : UInt64 := if lo < alo then 1 else 0
  ⟨ahi + bhi + carry, lo⟩

def loop : List UInt64 → UInt64 → UInt64 → UInt64 → UInt64 → UInt128
  | [], alo, ahi, blo, bhi => merge ahi alo bhi blo
  | q :: qs, alo, ahi, blo, bhi =>
    let lo := alo + q
    let carry : UInt64 := if lo < alo then 1 else 0
    let hi := ahi + high q + carry
    loop qs blo bhi lo hi

def run2 (xs : List UInt64) : UInt128 := loop xs 0 0 0 0
def total (xs : List UInt64) : Int := (xs.map signed64).sum

theorem merge_eq_add128 (ahi alo bhi blo : UInt64) :
    merge ahi alo bhi blo = (add128 ⟨ahi, alo⟩ ⟨bhi, blo⟩).value := by
  simp [merge, add128, addCarry64, add64]

theorem merge_represents (x y : UInt128) (sx sy : Int)
    (hx : Represents x sx) (hy : Represents y sy) :
    Represents (merge x.hi x.lo y.hi y.lo) (sx + sy) := by
  have hw := add128_toNat x y
  dsimp only at hw
  rw [← merge_eq_add128 x.hi x.lo y.hi y.lo] at hw
  have hwI : ((merge x.hi x.lo y.hi y.lo).toNat : Int) +
      ((add128 x y).carry.toNat : Int) * 2 ^ 128 = (x.toNat : Int) + (y.toNat : Int) := by
    exact_mod_cast hw
  obtain ⟨kx, hx⟩ := hx
  obtain ⟨ky, hy⟩ := hy
  refine ⟨kx + ky - ((add128 x y).carry.toNat : Int), ?_⟩
  calc
    _ = (x.toNat : Int) + (y.toNat : Int) - ((add128 x y).carry.toNat : Int) * 2 ^ 128 := by
      linarith only [hwI]
    _ = sx + sy + (kx + ky - ((add128 x y).carry.toNat : Int)) * 2 ^ 128 := by
      rw [hx, hy]
      ring

theorem extend_represents (q : UInt64) : Represents (extend q) (signed64 q) := by
  by_cases h : q.toNat < 2 ^ 63
  · have hw : q < 0x8000000000000000 := UInt64.lt_iff_toNat_lt.mpr h
    refine ⟨0, ?_⟩
    simp [extend, high, hw, signed64, h, UInt128.toNat]
  · have hw : ¬q < 0x8000000000000000 := by
      simpa only [UInt64.lt_iff_toNat_lt] using h
    refine ⟨1, ?_⟩
    simp only [extend, high, if_neg hw, UInt128.toNat, signed64, if_neg h]
    norm_num <;> omega

theorem zero_represents : Represents (⟨0, 0⟩ : UInt128) 0 := by
  refine ⟨0, ?_⟩
  simp [UInt128.toNat]

/- No no-overflow assumption is hidden in merge: modular arithmetic is
   proved first. A bounded signed result then has one unique interpretation. -/
theorem signed128_of_represents (v : UInt128) (z : Int)
    (hr : Represents v z) (hz : -(2 ^ 127 : Int) ≤ z ∧ z < 2 ^ 127) :
    signed128 v = z := by
  obtain ⟨k, hk⟩ := hr
  have hu : (v.toNat : Int) < 2 ^ 128 := by exact_mod_cast v.toNat_lt
  have hn : (0 : Int) ≤ v.toNat := by omega
  unfold signed128
  split_ifs with hs <;> omega

theorem total_nil : total [] = 0 := rfl
theorem total_cons (q : UInt64) (xs : List UInt64) :
    total (q :: xs) = signed64 q + total xs := rfl

/- The scalar-word loop alternates which accumulator receives each term.
   Its invariant is the same complete term multiset, with no merge premise. -/
theorem loop_represents (xs : List UInt64) (alo ahi blo bhi : UInt64) (sa sb : Int)
    (ha : Represents (⟨ahi, alo⟩ : UInt128) sa)
    (hb : Represents (⟨bhi, blo⟩ : UInt128) sb) :
    Represents (loop xs alo ahi blo bhi) (sa + sb + total xs) := by
  induction xs generalizing alo ahi blo bhi sa sb with
  | nil =>
    simpa only [loop, total_nil, add_zero] using
      merge_represents ⟨ahi, alo⟩ ⟨bhi, blo⟩ sa sb ha hb
  | cons q qs ih =>
    let next := merge ahi alo (high q) q
    have hn : Represents next (sa + signed64 q) :=
      merge_represents ⟨ahi, alo⟩ (extend q) sa (signed64 q) ha (extend_represents q)
    have ht := ih blo bhi next.lo next.hi sb (sa + signed64 q) hb hn
    simpa only [loop, next, merge, total_cons, add_assoc, add_comm, add_left_comm] using ht

theorem run2_represents (xs : List UInt64) : Represents (run2 xs) (total xs) := by
  simpa only [run2, zero_add] using
    loop_represents xs 0 0 0 0 0 0 zero_represents zero_represents

theorem total_abs_le (xs : List UInt64)
    (h : ∀ q ∈ xs, |signed64 q| < (2 ^ 62 : Int)) :
    |total xs| ≤ (xs.length : Int) * 2 ^ 62 := by
  induction xs with
  | nil => simp [total]
  | cons q qs ih =>
    have hq := h q (by simp)
    have ht := ih (by intro a ha; exact h a (by simp [ha]))
    rw [total_cons]
    calc
      _ ≤ |signed64 q| + |total qs| := abs_add_le _ _
      _ ≤ 2 ^ 62 + (qs.length : Int) * 2 ^ 62 := add_le_add hq.le ht
      _ = ((q :: qs).length : Int) * 2 ^ 62 := by
        simp only [List.length_cons, Nat.cast_add, Nat.cast_one]
        ring

theorem total_abs_lt_82 (xs : List UInt64) (hn : xs.length < 2 ^ 20)
    (h : ∀ q ∈ xs, |signed64 q| < (2 ^ 62 : Int)) : |total xs| < (2 ^ 82 : Int) := by
  have hb := total_abs_le xs h
  have hnI : (xs.length : Int) < 2 ^ 20 := by exact_mod_cast hn
  omega

/- Exact signed result for the actual two-chain word loop. The term encoder
   must supply standard Int64 two's-complement words. This is not yet a
   theorem about any original raw32 product/shift loop or its final rounder. -/
theorem run2_exact_signed_sum (xs : List UInt64) (hn : xs.length < 2 ^ 20)
    (h : ∀ q ∈ xs, |signed64 q| < (2 ^ 62 : Int)) :
    signed128 (run2 xs) = (xs.map signed64).sum := by
  have hb := total_abs_lt_82 xs hn h
  have hbounds := abs_lt.mp hb
  exact signed128_of_represents (run2 xs) (total xs) (run2_represents xs) (by
    constructor <;> omega)

end Submission.R24TwoChain128
