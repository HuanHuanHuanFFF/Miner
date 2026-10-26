namespace BranchlessRNESeed
open FloatLib.Numerics


#eval do
  let stream ← IO.getStdout
  stream.putStrLn "[DEBUG-R19-SEED] BEFORE 0:quotient_bias"
  stream.flush

private theorem quotient_bias (p half : Nat) (hhalf : 0 < half) :
    roundQuotientEven p (2 * half) =
      (p + half - 1 + (p / (2 * half)) % 2) / (2 * half) := by
  let q := p / (2 * half)
  let r := p % (2 * half)
  have hr : r < 2 * half := Nat.mod_lt _ (by omega)
  have hparity : q % 2 < 2 := Nat.mod_lt _ (by decide)
  have hp : p = (2 * half) * q + r := (Nat.div_add_mod p (2 * half)).symm
  have hb : p + half - 1 + q % 2 =
      (r + half - 1 + q % 2) + (2 * half) * q := by omega
  change (if 2 * r < 2 * half then q
    else if 2 * half < 2 * r then q + 1
    else if q % 2 == 0 then q else q + 1) =
      (p + half - 1 + q % 2) / (2 * half)
  rw [hb, Nat.add_mul_div_left _ _ (by omega)]
  simp only [beq_iff_eq]
  split_ifs with hbelow habove heven
  · have hd : (r + half - 1 + q % 2) / (2 * half) = 0 :=
      Nat.div_eq_of_lt (by omega)
    rw [hd]
    omega
  · have hd : (r + half - 1 + q % 2) / (2 * half) = 1 :=
      Nat.div_eq_of_lt_le (by omega) (by omega)
    rw [hd]
    omega
  · have hd : (r + half - 1 + q % 2) / (2 * half) = 0 :=
      Nat.div_eq_of_lt (by omega)
    rw [hd]
    omega
  · have hd : (r + half - 1 + q % 2) / (2 * half) = 1 :=
      Nat.div_eq_of_lt_le (by omega) (by omega)
    rw [hd]
    omega


#eval do
  let stream ← IO.getStdout
  stream.putStrLn "[DEBUG-R19-SEED] AFTER 0:quotient_bias"
  stream.flush


#eval do
  let stream ← IO.getStdout
  stream.putStrLn "[DEBUG-R19-SEED] BEFORE 1:nat_bias"
  stream.flush

theorem nat_bias (p t : Nat) (ht : t = 23 ∨ t = 24) :
    roundShiftRightEven p t =
      (p + 2 ^ (t - 1) - 1 + (p >>> t) % 2) >>> t := by
  rcases ht with rfl | rfl
  · simpa [roundShiftRightEven_eq_roundQuotientEven, Nat.shiftRight_eq_div_pow] using
      quotient_bias p 4194304 (by decide)
  · simpa [roundShiftRightEven_eq_roundQuotientEven, Nat.shiftRight_eq_div_pow] using
      quotient_bias p 8388608 (by decide)



#eval do
  let stream ← IO.getStdout
  stream.putStrLn "[DEBUG-R19-SEED] AFTER 1:nat_bias"
  stream.flush


#eval do
  let stream ← IO.getStdout
  stream.putStrLn "[DEBUG-R19-SEED] BEFORE 2:nat_grouped_bias"
  stream.flush

theorem nat_grouped_bias (p t : Nat) (ht : t=23 ∨ t=24) :
    roundShiftRightEven p t =
      (p+(2^(t-1)-1)+(p >>> t)%2) >>> t := by
  have hpos := Nat.two_pow_pos (t-1)
  have he : p+2^(t-1)-1 = p+(2^(t-1)-1) := by omega
  simpa only [he] using nat_bias p t ht


#eval do
  let stream ← IO.getStdout
  stream.putStrLn "[DEBUG-R19-SEED] AFTER 2:nat_grouped_bias"
  stream.flush


#eval do
  let stream ← IO.getStdout
  stream.putStrLn "[DEBUG-R19-SEED] BEFORE 3:grouped"
  stream.flush

@[inline] def grouped (p t : UInt64) : UInt64 :=
  (p+(((1 : UInt64) <<< (t-1))-1)+((p >>> t) &&& 1)) >>> t


#eval do
  let stream ← IO.getStdout
  stream.putStrLn "[DEBUG-R19-SEED] AFTER 3:grouped"
  stream.flush


#eval do
  let stream ← IO.getStdout
  stream.putStrLn "[DEBUG-R19-SEED] BEFORE 4:word_grouped"
  stream.flush

theorem word_grouped (p t : UInt64) (hp : p.toNat ≤ 281474943156225)
    (ht : t=23 ∨ t=24) :
    grouped p t = FixedWord.roundShiftRightEven p t.toNat := by
  let half : UInt64 := (1 : UInt64) <<< (t-1)
  let bias : UInt64 := half-1
  let parity : UInt64 := (p >>> t) &&& 1
  have htNat : t.toNat=23 ∨ t.toNat=24 := by
    rcases ht with rfl | rfl <;> norm_num
  have ht64 : t.toNat < 64 := by omega
  have hhalf : half.toNat=2^(t.toNat-1) := by
    rcases ht with rfl | rfl <;> decide
  have hb : 4194304 ≤ half.toNat ∧ half.toNat ≤ 8388608 := by
    rcases ht with rfl | rfl <;> decide
  have hone : (1 : UInt64) ≤ half := by
    rw [UInt64.le_iff_toNat_le]
    change 1 ≤ half.toNat
    omega
  have hminus : bias.toNat=half.toNat-1 := by
    dsimp only [bias]
    rw [UInt64.toNat_sub_of_le _ _ hone]
    rfl
  have hshift : (p >>> t).toNat=p.toNat >>> t.toNat := by
    rw [UInt64.toNat_shiftRight,Nat.mod_eq_of_lt ht64]
  have hparity : parity.toNat=(p.toNat >>> t.toNat)%2 := by
    dsimp only [parity]
    rw [UInt64.toNat_and,hshift]
    change (p.toNat >>> t.toNat) &&& (2^1-1) = (p.toNat >>> t.toNat)%2
    exact Nat.and_two_pow_sub_one_eq_mod _ 1
  have hparityBound : parity.toNat ≤ 1 := by rw [hparity]; omega
  have hplus : (p+bias).toNat=p.toNat+(half.toNat-1) := by
    rw [UInt64.toNat_add,hminus,Nat.mod_eq_of_lt (by omega)]
  have hsum : (p+bias+parity).toNat=p.toNat+(half.toNat-1)+parity.toNat := by
    rw [UInt64.toNat_add,hplus,Nat.mod_eq_of_lt (by omega)]
  apply UInt64.toNat.inj
  change ((p+bias+parity) >>> t).toNat = (FixedWord.roundShiftRightEven p t.toNat).toNat
  rw [UInt64.toNat_shiftRight,Nat.mod_eq_of_lt ht64,hsum,
    FixedWord.roundShiftRightEven_toNat,hhalf,hparity]
  exact (nat_grouped_bias p.toNat t.toNat htNat).symm


#eval do
  let stream ← IO.getStdout
  stream.putStrLn "[DEBUG-R19-SEED] AFTER 4:word_grouped"
  stream.flush


#eval do
  let stream ← IO.getStdout
  stream.putStrLn "[DEBUG-R19-SEED] BEFORE 5:grouped_eq_existing_rse"
  stream.flush

theorem grouped_eq_existing_rse (p t : UInt64) (hp : p.toNat ≤ 281474943156225)
    (ht : t=23 ∨ t=24) :
    grouped p t = Submission.FastMul.rse p t := by
  calc
    _ = FixedWord.roundShiftRightEven p t.toNat := word_grouped p t hp ht
    _ = Submission.FastMul.rseAny p t := (Submission.FastMul.rseAny_eq p t).symm
    _ = Submission.FastMul.rse p t := by rcases ht with rfl | rfl <;> rfl

end BranchlessRNESeed

namespace R19PostBias
open FloatLib.Numerics


#eval do
  let stream ← IO.getStdout
  stream.putStrLn "[DEBUG-R19-SEED] AFTER 5:grouped_eq_existing_rse"
  stream.flush


#eval do
  let stream ← IO.getStdout
  stream.putStrLn "[DEBUG-R19-SEED] BEFORE 6:shift"
  stream.flush

def shift (p : Nat) : Nat := if p < 140737488355328 then 23 else 24

#eval do
  let stream ← IO.getStdout
  stream.putStrLn "[DEBUG-R19-SEED] AFTER 6:shift"
  stream.flush


#eval do
  let stream ← IO.getStdout
  stream.putStrLn "[DEBUG-R19-SEED] BEFORE 7:biased"
  stream.flush

def biased (p : Nat) : Nat := p + (2 ^ (shift p - 1) - 1) + (p >>> shift p) % 2


#eval do
  let stream ← IO.getStdout
  stream.putStrLn "[DEBUG-R19-SEED] AFTER 7:biased"
  stream.flush


#eval do
  let stream ← IO.getStdout
  stream.putStrLn "[DEBUG-R19-SEED] BEFORE 8:biased_quotient"
  stream.flush

/-- Uses the retained uncompiled bias proof, not an independent new proof. -/
theorem biased_quotient (p : Nat) :
    biased p >>> shift p = roundShiftRightEven p (shift p) := by
  have hk : shift p = 23 ∨ shift p = 24 := by
    unfold shift
    split <;> simp_all
  exact (BranchlessRNESeed.nat_grouped_bias p (shift p) hk).symm


#eval do
  let stream ← IO.getStdout
  stream.putStrLn "[DEBUG-R19-SEED] AFTER 8:biased_quotient"
  stream.flush


#eval do
  let stream ← IO.getStdout
  stream.putStrLn "[DEBUG-R19-SEED] BEFORE 9:biased_bounds"
  stream.flush

theorem biased_bounds (p : Nat)
    (hlo : 70368744177664 ≤ p) (hhi : p ≤ 281474943156225) :
    70368744177664 ≤ biased p ∧ biased p ≤ 281474951544833 := by
  have hpar : (p >>> shift p) % 2 < 2 := Nat.mod_lt _ (by decide)
  unfold biased
  by_cases hp : p < 140737488355328
  · simp only [shift,if_pos hp]
    norm_num only [Nat.reduceSub,Nat.reducePow]
    simp only [shift,if_pos hp] at hpar
    omega
  · simp only [shift,if_neg hp]
    norm_num only [Nat.reduceSub,Nat.reducePow]
    simp only [shift,if_neg hp] at hpar
    omega


#eval do
  let stream ← IO.getStdout
  stream.putStrLn "[DEBUG-R19-SEED] AFTER 9:biased_bounds"
  stream.flush


#eval do
  let stream ← IO.getStdout
  stream.putStrLn "[DEBUG-R19-SEED] BEFORE 10:normalized_quotient"
  stream.flush

/-- The actual product cap prevents a second carry beyond bit47. -/
theorem normalized_quotient (p : Nat)
    (hlo : 70368744177664 ≤ p) (hhi : p ≤ 281474943156225) :
    let q := roundShiftRightEven p (shift p)
    let h := biased p >>> 47
    h = (if p < 140737488355328 then 0 else 1) + (if q = 16777216 then 1 else 0) ∧
      biased p >>> (23 + h) = (if q = 16777216 then 8388608 else q) := by
  have hb := biased_bounds p hlo hhi
  have hq := biased_quotient p
  dsimp only
  by_cases hp : p < 140737488355328
  · have hk : shift p = 23 := by simp [shift,hp]
    have hsmall : biased p < 140737496743936 := by
      have hpar : (p >>> 23) % 2 < 2 := Nat.mod_lt _ (by decide)
      unfold biased
      rw [hk]
      norm_num only [Nat.reduceSub,Nat.reducePow]
      omega
    rw [hk] at hq ⊢
    rw [← hq]
    simp only [hp,↓reduceIte,Nat.shiftRight_eq_div_pow]
    have hh : biased p / 140737488355328 = 0 ∨ biased p / 140737488355328 = 1 := by omega
    rcases hh with hh | hh
    · rw [hh]
      norm_num only [Nat.reduceAdd,Nat.reducePow]
      have hn : biased p / 8388608 ≠ 16777216 := by omega
      simp [hn]
    · rw [hh]
      norm_num only [Nat.reduceAdd,Nat.reducePow]
      have he : biased p / 8388608 = 16777216 := by omega
      simp only [he,↓reduceIte]
      constructor <;> omega
  · have hk : shift p = 24 := by simp [shift,hp]
    have hlarge : 140737488355328 ≤ biased p := by
      unfold biased
      omega
    rw [hk] at hq ⊢
    rw [← hq]
    simp only [hp,↓reduceIte,Nat.shiftRight_eq_div_pow]
    have hh : biased p / 140737488355328 = 1 := by omega
    rw [hh]
    norm_num only [Nat.reduceAdd,Nat.reducePow]
    have hn : biased p / 16777216 ≠ 16777216 := by omega
    simp [hn]

end R19PostBias


#eval do
  let stream ← IO.getStdout
  stream.putStrLn "[DEBUG-R19-SEED] AFTER 10:normalized_quotient"
  stream.flush

