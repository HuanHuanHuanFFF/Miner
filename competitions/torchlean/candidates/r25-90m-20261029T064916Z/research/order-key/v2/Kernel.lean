import ContractExact

/-!
# Exact runtime, starting champion

Every kernel is built on one exact dot product. Each finite product `±m · 2^idx` goes into 32-bit
limbs (`Acc.add`), and the exact total is rounded once with FloatLib's own rounding. The rounding
(`finishFast`) never builds the total as a big integer: it turns the nonzero limbs into 32-bit
digits of `pos - neg` and rounds from the top two digits and a sticky bit, which rounds the same
(`roundDyadic_jam`). A NaN or an infinity anywhere falls back to FloatLib's `dot`.

`dotFn n fa fb` reads its operands through functions (`dotFn_eq`). `dot` reads two arrays and
`sum` is a dot with ones. Every other dot-based kernel is the contract's own definition run with
`dotFn` instead of the spec's `dotOf` (`linearWith dotFn`, `conv2dWith dotFn`, …), so it reads
its inputs, weights and bias in place and its proof is one rewrite. Max pooling keeps its running
maximum as a word and compares finite words by their exact values (`maxW`, proved against
FloatLib's `maximum`). The residual add and batch norm use their specs.
-/

namespace Submission

open ExactRuntime FloatLib.Floats.Formats.BinaryInterchange FloatLib.Floats

/-! ## The exact accumulator -/

/-- Positive and negative limbs, "a NaN or infinity was seen", and "every term so far was a zero
of negative sign" (which decides the sign of a zero result). -/
structure Acc where
  pos : Array Nat
  neg : Array Nat
  special : Bool
  negZero : Bool

/-- No terms yet: zero limbs, no special value, and "every term was −0" vacuously true. -/
def Acc.empty : Acc := ⟨Array.replicate 18 0, Array.replicate 18 0, false, true⟩

/-- The exact integer total held in the limbs. -/
def Acc.total (acc : Acc) : Int := (limbVal acc.pos.toList : Int) - limbVal acc.neg.toList

/-- Add the exact term `±m · 2^idx`; a zero term only updates the zero-sign flag. -/
@[inline] def Acc.add (acc : Acc) (m idx : Nat) (neg : Bool) : Acc :=
  match acc with
  | ⟨pos, ng, sp, nz⟩ =>
    if m = 0 then ⟨pos, ng, sp, nz && neg⟩
    else if neg then ⟨pos, addLimbs64 ng m.toUInt64 idx, sp, false⟩
    else ⟨addLimbs64 pos m.toUInt64 idx, ng, sp, false⟩

/-- Record that a NaN or an infinity was seen. -/
@[inline] def Acc.markSpecial (acc : Acc) : Acc :=
  match acc with
  | ⟨pos, ng, _, nz⟩ => ⟨pos, ng, true, nz⟩

/-- Everything the proof needs to know about one `Acc.add`. -/
theorem Acc.add_spec (acc : Acc) (m idx : Nat) (neg : Bool)
    (hp : acc.pos.size = 18) (hn : acc.neg.size = 18) (hm : m < 2 ^ 64) (hi : idx / 32 + 1 < 18) :
    (acc.add m idx neg).pos.size = 18 ∧ (acc.add m idx neg).neg.size = 18 ∧
    (acc.add m idx neg).special = acc.special ∧
    (acc.add m idx neg).negZero = (acc.negZero && (decide (m = 0) && neg)) ∧
    (acc.add m idx neg).total = acc.total + (if neg then -(m : Int) else m) * 2 ^ idx := by
  obtain ⟨pos, ng, sp, nz⟩ := acc
  simp only at hp hn
  by_cases hm0 : m = 0
  · simp [Acc.add, Acc.total, hm0, hp, hn]
  · cases neg
    · refine ⟨by simp [Acc.add, hm0, addLimbs64_size, hp], by simp [Acc.add, hm0, hn],
        by simp [Acc.add, hm0], by simp [Acc.add, hm0], ?_⟩
      simp only [Acc.add, hm0, ite_false, Bool.false_eq_true, addLimbs64_eq _ _ _ hm, Acc.total]
      rw [addLimbs_val _ _ _ (by omega)]
      push_cast; ring
    · refine ⟨by simp [Acc.add, hm0, hp], by simp [Acc.add, hm0, addLimbs64_size, hn],
        by simp [Acc.add, hm0], by simp [Acc.add, hm0], ?_⟩
      simp only [Acc.add, hm0, ite_false, ite_true, addLimbs64_eq _ _ _ hm, Acc.total]
      rw [addLimbs_val _ _ _ (by omega)]
      push_cast; ring

theorem Acc.total_empty : Acc.empty.total = 0 := by decide

/-! ## Rounding without big integers -/

section
open FloatLib.Numerics

/-- Jamming the low `j` bits into a sticky bit rounds the same, when at least 25 bits (the 24-bit
significand and a guard bit) stay above them. -/
theorem roundDyadic_jam (s : Bool) (m : Nat) (e : Int) (j : Nat) (h : j + 25 ≤ m.log2) :
    Model.roundDyadic Fmt ⟨s, shiftRightJam m j, e + j⟩ = Model.roundDyadic Fmt ⟨s, m, e⟩ := by
  have hm0 : m ≠ 0 := by rintro rfl; simp at h
  have hpow : 2 ^ m.log2 ≤ m := Nat.log2_self_le hm0
  have hm : 2 ^ (j + 1) ≤ m := le_trans (Nat.pow_le_pow_right (by norm_num) (by omega)) hpow
  have hlog : (shiftRightJam m j).log2 = m.log2 - j := log2_shiftRightJam m j hm
  have hne : shiftRightJam m j ≠ 0 :=
    shiftRightJam_ne_zero m j (le_trans (Nat.pow_le_pow_right (by norm_num) (by omega)) hm)
  rw [← Model.roundDyadicGeneral_eq_roundDyadic, ← Model.roundDyadicGeneral_eq_roundDyadic]
  unfold Model.roundDyadicGeneral
  simp only [hne, hm0, beq_iff_eq, ite_false, hlog]
  have htot : ((m.log2 - j : Nat) : Int) + (e + j) = (m.log2 : Int) + e := by omega
  rw [htot]
  have hfw : Fmt.fracWidth = 23 := rfl
  have hsub : Fmt.minSubnormalExponent = -149 := rfl
  have hmin : Fmt.minNormalExponent = -126 := rfl
  rw [hfw, hsub, hmin]
  split_ifs with h1 h2 h3 h4 <;> try omega
  · rfl
  · congr 1
    obtain ⟨a, ha⟩ : ∃ a : Nat, e - -149 = Int.negSucc a := ⟨(-(e + 149) - 1).toNat, by omega⟩
    have hb : e + j - -149 = Int.negSucc (a - j) := by omega
    rw [ha, hb]
    dsimp only
    rw [show a - j + 1 = (a + 1) - j by omega]
    exact roundShiftRightEven_shiftRightJam m j (a + 1) (by omega)
  · congr 1
    rw [show m.log2 - j - 23 = (m.log2 - 23) - j by omega]
    exact roundShiftRightEven_shiftRightJam m j _ (by omega)

/-! ## Values of limb windows -/

/-- `k` limbs of `a` from index `i`: `a[i] + 2^32·a[i+1] + …`. -/
def winVal (a : Array Nat) (i : Nat) : Nat → Nat
  | 0 => 0
  | k + 1 => a[i]! + 2 ^ 32 * winVal a (i + 1) k

theorem winVal_split (a : Array Nat) (i k m : Nat) :
    winVal a i (k + m) = winVal a i k + 2 ^ (32 * k) * winVal a (i + k) m := by
  induction k generalizing i with
  | zero => simp [winVal]
  | succ k ih =>
    rw [show k + 1 + m = (k + m) + 1 by omega, winVal, winVal, ih, show i + 1 + k = i + (k + 1) by omega]
    rw [show 32 * (k + 1) = 32 + 32 * k by ring, pow_add]
    ring

theorem winVal_congr (a b : Array Nat) (i j k : Nat) (h : ∀ t, t < k → a[i + t]! = b[j + t]!) :
    winVal a i k = winVal b j k := by
  induction k generalizing i j with
  | zero => rfl
  | succ k ih =>
    rw [winVal, winVal, ih (i + 1) (j + 1) (fun t ht => by
      rw [show i + 1 + t = i + (t + 1) by omega, show j + 1 + t = j + (t + 1) by omega]
      exact h (t + 1) (by omega)), show a[i]! = b[j]! from by simpa using h 0 (by omega)]

theorem winVal_eq_zero_iff (a : Array Nat) (i k : Nat) :
    winVal a i k = 0 ↔ ∀ t, t < k → a[i + t]! = 0 := by
  induction k generalizing i with
  | zero => simp [winVal]
  | succ k ih =>
    rw [winVal, Nat.add_eq_zero_iff, Nat.mul_eq_zero, ih (i + 1)]
    have hp : (2 : ℕ) ^ 32 ≠ 0 := by norm_num
    constructor
    · rintro ⟨h0, h1 | h1⟩ t ht
      · exact absurd h1 hp
      · rcases t with _ | t
        · simpa using h0
        · rw [show i + (t + 1) = i + 1 + t by omega]; exact h1 t (by omega)
    · intro h
      refine ⟨by simpa using h 0 (by omega), Or.inr fun t ht => ?_⟩
      rw [show i + 1 + t = i + (t + 1) by omega]; exact h (t + 1) (by omega)

theorem winVal_lt (a : Array Nat) (i k : Nat) (h : ∀ t, t < k → a[i + t]! < 2 ^ 32) :
    winVal a i k < 2 ^ (32 * k) := by
  induction k generalizing i with
  | zero => simp [winVal]
  | succ k ih =>
    have h0 := h 0 (by omega)
    have h1 := ih (i + 1) (fun t ht => by
      rw [show i + 1 + t = i + (t + 1) by omega]; exact h (t + 1) (by omega))
    simp only [Nat.add_zero] at h0
    rw [winVal, show 32 * (k + 1) = 32 + 32 * k by ring, pow_add]
    nlinarith

theorem getElem!_size_le (a : Array Nat) (t : Nat) (h : a.size ≤ t) : a[t]! = 0 := by
  simp [getElem!_neg a t (by omega)]

theorem winVal_eq_limbVal (a : Array Nat) (i k : Nat) (h : a.size ≤ i + k) :
    winVal a i k = limbVal (a.toList.drop i) := by
  induction k generalizing i with
  | zero => simp [winVal, List.drop_of_length_le (by simpa using h : a.toList.length ≤ i), limbVal]
  | succ k ih =>
    rw [winVal, ih (i + 1) (by omega)]
    by_cases hi : i < a.size
    · have hl : i < a.toList.length := by simpa using hi
      simp only [List.drop_eq_getElem_cons hl, limbVal, getElem!_pos a i hi, Array.getElem_toList]
    · rw [getElem!_size_le a i (by omega), List.drop_of_length_le (by simp; omega),
        List.drop_of_length_le (by simp; omega)]
      simp [limbVal]

/-- A limb array's value is its window between two runs of zero limbs. -/
theorem limbVal_eq_win (a : Array Nat) (lo n : Nat) (hlow : ∀ t, t < lo → a[t]! = 0)
    (hhigh : ∀ t, lo + n ≤ t → a[t]! = 0) :
    limbVal a.toList = 2 ^ (32 * lo) * winVal a lo n := by
  rw [← List.drop_zero (l := a.toList), ← winVal_eq_limbVal a 0 (lo + (n + a.size)) (by omega),
    winVal_split, winVal_split]
  rw [(winVal_eq_zero_iff a 0 lo).2 (fun t ht => by simpa using hlow t ht),
    (winVal_eq_zero_iff a (0 + lo + n) a.size).2 (fun t _ => hhigh _ (by omega))]
  simp

/-! ## Digits of `A - B` -/

/-- One pass over limbs `i, i+1, …`: normalise `a` and `b` to 32-bit digits (carries `ca`, `cb`)
and subtract them (borrow `br`), pushing the digits of the difference. -/
def diffGo (a b : Array Nat) (i ca cb br : Nat) (out : Array Nat) :
    Nat → Array Nat × Nat × Nat × Nat
  | 0 => (out, ca, cb, br)
  | k + 1 =>
    let ta := a[i]! + ca
    let tb := b[i]! + cb
    let t := ta % 4294967296 + 4294967296 - tb % 4294967296 - br
    diffGo a b (i + 1) (ta / 4294967296) (tb / 4294967296) (1 - t / 4294967296)
      (out.push (t % 4294967296)) k

theorem diffGo_spec (a b : Array Nat) (i ca cb br : Nat) (out : Array Nat) (k : Nat)
    (hbr : br ≤ 1) (hout : ∀ t, t < out.size → out[t]! < 2 ^ 32) :
    let r := diffGo a b i ca cb br out k
    r.1.size = out.size + k ∧ (∀ t, t < r.1.size → r.1[t]! < 2 ^ 32) ∧
      (winVal r.1 0 r.1.size : Int) + 2 ^ (32 * (out.size + k)) * (r.2.1 - r.2.2.1 - r.2.2.2 : Int) =
        winVal out 0 out.size + 2 ^ (32 * out.size) *
          ((winVal a i k : Int) - winVal b i k + ca - cb - br) := by
  induction k generalizing i ca cb br out with
  | zero => exact ⟨by simp [diffGo], by simpa [diffGo] using hout, by simp [diffGo, winVal]⟩
  | succ k ih =>
    simp only [diffGo]
    set ta := a[i]! + ca
    set tb := b[i]! + cb
    set t := ta % 4294967296 + 4294967296 - tb % 4294967296 - br
    have htb : tb % 4294967296 < 4294967296 := Nat.mod_lt _ (by norm_num)
    have hta : ta % 4294967296 < 4294967296 := Nat.mod_lt _ (by norm_num)
    have ht2 : t < 2 * 4294967296 := by omega
    have hq : t / 4294967296 ≤ 1 := by omega
    have hd : t % 4294967296 < 2 ^ 32 := by have := Nat.mod_lt t (by norm_num : 4294967296 > 0); norm_num; omega
    have hout' : ∀ s, s < (out.push (t % 4294967296)).size → (out.push (t % 4294967296))[s]! < 2 ^ 32 := by
      intro s hs
      simp only [Array.size_push] at hs
      rcases Nat.lt_or_eq_of_le (Nat.lt_succ_iff.mp hs) with hs | rfl
      · rw [getElem!_pos _ s (by simp; omega), Array.getElem_push_lt hs, ← getElem!_pos out s hs]
        exact hout s hs
      · rw [getElem!_pos _ _ (by simp), Array.getElem_push_eq]; exact hd
    obtain ⟨h1, h2, h3⟩ := ih (i + 1) (ta / 4294967296) (tb / 4294967296) (1 - t / 4294967296)
      (out.push (t % 4294967296)) (by omega) hout'
    refine ⟨by simp [h1]; omega, h2, ?_⟩
    have hpush : winVal (out.push (t % 4294967296)) 0 (out.size + 1) =
        winVal out 0 out.size + 2 ^ (32 * out.size) * (t % 4294967296) := by
      rw [winVal_split, winVal_congr _ out 0 0 out.size (fun s hs => by
          rw [getElem!_pos _ _ (by simp; omega), Array.getElem_push_lt (by omega),
            ← getElem!_pos out _ (by omega)])]
      simp only [winVal, Nat.zero_add, Nat.mul_zero, Nat.add_zero]
      rw [getElem!_pos _ _ (by simp), Array.getElem_push_eq]
    simp only [Array.size_push] at h3 ⊢
    rw [show out.size + (k + 1) = out.size + 1 + k by omega]
    rw [h3, hpush, winVal, winVal]
    have hstep : ((t % 4294967296 : Nat) : Int) + 4294967296 * ((ta / 4294967296 : Nat) - (tb / 4294967296 : Nat) - (1 - t / 4294967296 : Nat)) =
        (a[i]! : Int) - b[i]! + ca - cb - br := by
      have e1 := Nat.mod_add_div ta 4294967296
      have e2 := Nat.mod_add_div tb 4294967296
      have e3 := Nat.mod_add_div t 4294967296
      have e4 : (1 - t / 4294967296 : Nat) = 1 - (t / 4294967296 : Int) := by omega
      have e5 : (t : Int) = ta % 4294967296 + 4294967296 - tb % 4294967296 - br := by omega
      push_cast [e4]
      omega
    rw [show 32 * (out.size + 1) = 32 * out.size + 32 by ring, pow_add]
    simp only [Nat.cast_add, Nat.cast_mul, Nat.cast_pow, Nat.cast_ofNat]
    linear_combination (2 : Int) ^ (32 * out.size) * hstep

/-! ## Rounding the digits from a 62-bit window -/

/-- The highest nonzero digit below `k`, or none. -/
def topGo (r : Array Nat) : Nat → Option Nat
  | 0 => none
  | k + 1 => if r[k]! != 0 then some k else topGo r k

/-- "Some digit below `k` is nonzero." -/
def anyGo (r : Array Nat) : Nat → Bool
  | 0 => false
  | k + 1 => r[k]! != 0 || anyGo r k

theorem topGo_none (r : Array Nat) (k : Nat) (h : topGo r k = none) : ∀ t, t < k → r[t]! = 0 := by
  induction k with
  | zero => intro t ht; omega
  | succ k ih =>
    simp only [topGo] at h
    split at h
    · cases h
    · rename_i hk
      intro t ht
      rcases Nat.lt_or_eq_of_le (Nat.lt_succ_iff.mp ht) with ht | rfl
      · exact ih h t ht
      · simpa using hk

theorem topGo_some (r : Array Nat) (k h : Nat) (hh : topGo r k = some h) :
    h < k ∧ r[h]! ≠ 0 ∧ ∀ t, h < t → t < k → r[t]! = 0 := by
  induction k with
  | zero => simp [topGo] at hh
  | succ k ih =>
    simp only [topGo] at hh
    split at hh
    · rename_i hk
      cases hh
      exact ⟨by omega, by simpa using hk, fun t h1 h2 => by omega⟩
    · rename_i hk
      obtain ⟨a, b, c⟩ := ih hh
      refine ⟨by omega, b, fun t h1 h2 => ?_⟩
      rcases Nat.lt_or_eq_of_le (Nat.lt_succ_iff.mp h2) with h2 | rfl
      · exact c t h1 h2
      · simpa using hk

theorem anyGo_false (r : Array Nat) (k : Nat) : anyGo r k = false ↔ ∀ t, t < k → r[t]! = 0 := by
  induction k with
  | zero => simp [anyGo]
  | succ k ih =>
    simp only [anyGo, Bool.or_eq_false_iff, bne_eq_false_iff_eq, ih]
    constructor
    · rintro ⟨h0, h1⟩ t ht
      rcases Nat.lt_or_eq_of_le (Nat.lt_succ_iff.mp ht) with ht | rfl
      · exact h1 t ht
      · exact h0
    · intro h; exact ⟨h k (by omega), fun t ht => h t (by omega)⟩

theorem anyGo_eq (r : Array Nat) (k : Nat) : anyGo r k = (winVal r 0 k != 0) := by
  have hz := winVal_eq_zero_iff r 0 k
  simp only [Nat.zero_add] at hz
  cases h : anyGo r k
  · rw [hz.2 ((anyGo_false r k).1 h)]; rfl
  · have : winVal r 0 k ≠ 0 := fun h0 => by
      have := (anyGo_false r k).2 (hz.1 h0); simp_all
    simp [this]

/-- A 62-bit window of the top two digits and a sticky bit for the rest is `shiftRightJam`. -/
theorem jam_window (low x y h : Nat) (hlow : low < 2 ^ (32 * h)) :
    shiftRightJam (low + 2 ^ (32 * h) * (x + 2 ^ 32 * y)) (32 * h + 2) =
      if x % 4 != 0 || low != 0 then (y * 1073741824 + x / 4) ||| 1 else y * 1073741824 + x / 4 := by
  have hX0 : 0 < 2 ^ (32 * h) := by positivity
  have hdiv : 2 ^ (32 * h + 2) = 4 * 2 ^ (32 * h) := by rw [pow_add]; ring
  have hs : x % 4 < 4 := Nat.mod_lt x (by norm_num)
  have hA : low + 2 ^ (32 * h) * (x % 4) < 4 * 2 ^ (32 * h) := by nlinarith
  have hsplit : low + 2 ^ (32 * h) * (x + 2 ^ 32 * y) =
      (low + 2 ^ (32 * h) * (x % 4)) + 4 * 2 ^ (32 * h) * (y * 1073741824 + x / 4) := by
    have h4 := Nat.mod_add_div x 4
    rw [show (2 : Nat) ^ 32 = 4 * 1073741824 by norm_num]
    conv_lhs => rw [← h4]
    ring
  have hz : low + 2 ^ (32 * h) * (x % 4) = 0 ↔ ¬(x % 4 ≠ 0 ∨ low ≠ 0) := by
    constructor
    · intro h0
      have h1 := Nat.eq_zero_of_add_eq_zero h0
      rcases Nat.mul_eq_zero.mp h1.2 with h2 | h2 <;> omega
    · intro h0; simp only [not_or, not_not] at h0; simp [h0.1, h0.2]
  unfold shiftRightJam
  dsimp only
  rw [hdiv, hsplit, Nat.add_mul_div_left _ _ (by omega), Nat.div_eq_of_lt hA, Nat.zero_add,
    Nat.add_mul_mod_self_left, Nat.mod_eq_of_lt hA]
  by_cases hc : x % 4 ≠ 0 ∨ low ≠ 0
  · have : ¬ (low + 2 ^ (32 * h) * (x % 4) = 0) := fun h0 => hz.mp h0 hc
    have hb : (x % 4 != 0 || low != 0) = true := by simpa [bne_iff_ne] using hc
    simp only [beq_iff_eq, this, ite_false, hb, ite_true]
  · have : low + 2 ^ (32 * h) * (x % 4) = 0 := hz.mpr hc
    have hb : (x % 4 != 0 || low != 0) = false := by simpa [bne_iff_ne] using hc
    simp only [beq_iff_eq, this, ite_true, hb]
    rfl

/-- Round `±R · 2^e`, `R` the value of the digits `r`: exactly while `R` has at most two digits,
otherwise from the top two digits and a sticky bit. -/
def finishDigits (neg : Bool) (r : Array Nat) (e : Int) (negZero : Bool) : UInt32 :=
  match topGo r r.size with
  | none => finishWord 0 e negZero
  | some 0 => finishWord (if neg then -(r[0]! : Int) else r[0]!) e negZero
  | some (h + 1) =>
    let x := r[h]!
    let v := r[h + 1]! * 1073741824 + x / 4
    let m := if x % 4 != 0 || anyGo r h then v ||| 1 else v
    toWord (Model.roundDyadic Fmt ⟨neg, m, e + ((32 * h + 2 : Nat) : Int)⟩)

theorem finishWord_signed (neg : Bool) (R : Nat) (e : Int) (negZero : Bool) (hR : R ≠ 0) :
    finishWord (if neg then -(R : Int) else R) e negZero = toWord (Model.roundDyadic Fmt ⟨neg, R, e⟩) := by
  have hpos : (0 : Int) < R := by exact_mod_cast Nat.pos_of_ne_zero hR
  cases neg <;> simp [finishWord, ofIntDyadic, hR, not_lt.mpr hpos.le, Nat.pos_of_ne_zero hR]

theorem finishDigits_eq (neg : Bool) (r : Array Nat) (e : Int) (negZero : Bool)
    (hr : ∀ t, t < r.size → r[t]! < 2 ^ 32) :
    finishDigits neg r e negZero =
      finishWord (if neg then -(winVal r 0 r.size : Int) else winVal r 0 r.size) e negZero := by
  unfold finishDigits
  split
  · rename_i hnone
    rw [(winVal_eq_zero_iff r 0 r.size).2 (fun t ht => by simpa using topGo_none r _ hnone t ht)]
    simp
  · rename_i hsome
    obtain ⟨h1, h2, h3⟩ := topGo_some r _ 0 hsome
    rw [show r.size = 1 + (r.size - 1) by omega, winVal_split,
      (winVal_eq_zero_iff r (0 + 1) (r.size - 1)).2 (fun t ht => h3 _ (by omega) (by omega))]
    simp [winVal]
  · rename_i h hsome
    obtain ⟨h1, h2, h3⟩ := topGo_some r _ (h + 1) hsome
    have hR : winVal r 0 r.size = winVal r 0 h + 2 ^ (32 * h) * (r[h]! + 2 ^ 32 * r[h + 1]!) := by
      rw [show r.size = h + (2 + (r.size - h - 2)) by omega, winVal_split, winVal_split,
        (winVal_eq_zero_iff r (0 + h + 2) _).2 (fun t ht => h3 _ (by omega) (by omega))]
      simp [winVal]
    have hlow : winVal r 0 h < 2 ^ (32 * h) := winVal_lt r 0 h (fun t ht => hr _ (by omega))
    have hR0 : winVal r 0 r.size ≠ 0 := by
      rw [hR]; have : 0 < 2 ^ (32 * h) * (r[h]! + 2 ^ 32 * r[h + 1]!) := by
        have := Nat.pos_of_ne_zero h2; positivity
      omega
    have hlog : 32 * h + 2 + 25 ≤ (winVal r 0 r.size).log2 := by
      rw [Nat.le_log2 hR0, hR]
      have : 1 ≤ r[h + 1]! := Nat.pos_of_ne_zero h2
      calc 2 ^ (32 * h + 2 + 25) ≤ 2 ^ (32 * h) * 2 ^ 32 := by rw [← pow_add]; exact Nat.pow_le_pow_right (by norm_num) (by omega)
        _ ≤ 2 ^ (32 * h) * (r[h]! + 2 ^ 32 * r[h + 1]!) := by gcongr; nlinarith
        _ ≤ _ := by omega
    rw [finishWord_signed neg _ e negZero hR0, ← roundDyadic_jam neg _ e _ hlog, hR,
      jam_window _ _ _ h hlow, anyGo_eq]

/-! ## The fast final rounding -/

/-- One past the highest limb below `k` where either array is nonzero. -/
def highLimb (pos neg : Array Nat) : Nat → Nat
  | 0 => 0
  | k + 1 => if pos[k]! != 0 || neg[k]! != 0 then k + 1 else highLimb pos neg k

theorem highLimb_zero (pos neg : Array Nat) (k : Nat) :
    ∀ t, highLimb pos neg k ≤ t → t < k → pos[t]! = 0 ∧ neg[t]! = 0 := by
  induction k with
  | zero => intro t _ ht; omega
  | succ k ih =>
    intro t h1 h2
    simp only [highLimb] at h1
    split at h1
    · omega
    · rename_i hk
      rcases Nat.lt_or_eq_of_le (Nat.lt_succ_iff.mp h2) with h2 | rfl
      · exact ih t h1 h2
      · simpa [Bool.or_eq_true, bne_iff_ne, not_or] using hk

/-- `finishLimbs` without big integers: the limbs between the lowest and highest nonzero ones
become 32-bit digits of `pos - neg` (one pass; a second with the operands swapped if the
difference is negative), which are rounded from their top 62 bits and a sticky bit. A carry or
borrow left over, which the accumulator never produces, falls back to `finishLimbs`. -/
def finishFast (pos neg : Array Nat) (e : Int) (negZero : Bool) : UInt32 :=
  let lo := lowLimb pos neg pos.size 0
  let n := highLimb pos neg (max pos.size neg.size) + 1 - lo
  let e' := e + ((32 * lo : Nat) : Int)
  let d := diffGo pos neg lo 0 0 0 (Array.emptyWithCapacity n) n
  if d.2.1 = 0 ∧ d.2.2.1 = 0 ∧ d.2.2.2 = 0 then finishDigits false d.1 e' negZero
  else
    let d' := diffGo neg pos lo 0 0 0 (Array.emptyWithCapacity n) n
    if d'.2.1 = 0 ∧ d'.2.2.1 = 0 ∧ d'.2.2.2 = 0 then finishDigits true d'.1 e' negZero
    else finishLimbs pos neg e negZero

theorem finishFast_eq (pos neg : Array Nat) (e : Int) (negZero : Bool) :
    finishFast pos neg e negZero =
      finishWord ((limbVal pos.toList : Int) - limbVal neg.toList) e negZero := by
  unfold finishFast
  dsimp only
  set lo := lowLimb pos neg pos.size 0
  set n := highLimb pos neg (max pos.size neg.size) + 1 - lo
  have hlow := lowLimb_zero pos neg pos.size 0
  have hhigh := highLimb_zero pos neg (max pos.size neg.size)
  have hzero (a : Array Nat) (ha : a = pos ∨ a = neg) :
      limbVal a.toList = 2 ^ (32 * lo) * winVal a lo n := by
    apply limbVal_eq_win a lo n
    · intro t ht; rcases ha with rfl | rfl
      · exact (hlow t (by omega) ht).1
      · exact (hlow t (by omega) ht).2
    · intro t ht
      by_cases hts : t < max pos.size neg.size
      · rcases ha with rfl | rfl
        · exact (hhigh t (by omega) hts).1
        · exact (hhigh t (by omega) hts).2
      · rcases ha with rfl | rfl <;> exact getElem!_size_le _ t (by omega)
  have hP := hzero pos (Or.inl rfl)
  have hN := hzero neg (Or.inr rfl)
  rw [show (Array.emptyWithCapacity n : Array Nat) = #[] from rfl]
  have hd := diffGo_spec pos neg lo 0 0 0 #[] n (by omega) (by simp)
  have hd' := diffGo_spec neg pos lo 0 0 0 #[] n (by omega) (by simp)
  have hw0 : winVal (#[] : Array Nat) 0 0 = 0 := rfl
  simp only [List.size_toArray, List.length_nil, Nat.mul_zero, pow_zero, one_mul,
    hw0, Nat.cast_zero, zero_add] at hd hd'
  obtain ⟨-, hb, hv⟩ := hd
  obtain ⟨-, hb', hv'⟩ := hd'
  split_ifs with h1 h2
  · rw [finishDigits_eq false _ _ _ hb, finishWord_scale, hP, hN]
    simp only [Bool.false_eq_true, ite_false]
    congr 1
    rw [h1.1, h1.2.1, h1.2.2] at hv
    push_cast at hv ⊢
    linear_combination (2 : Int) ^ (32 * lo) * hv
  · rw [finishDigits_eq true _ _ _ hb', finishWord_scale, hP, hN]
    simp only [ite_true]
    congr 1
    rw [h2.1, h2.2.1, h2.2.2] at hv'
    push_cast at hv' ⊢
    linear_combination (-(2 : Int) ^ (32 * lo)) * hv'
  · exact finishLimbs_eq pos neg e negZero

end

/-! ## The exact dot product -/

/-- One term: a NaN or infinity marks the accumulator, otherwise the exact product goes into the limbs. -/
@[inline] def dotStep (acc : Acc) (wa wb : UInt32) : Acc :=
  if expOf wa = 255 ∨ expOf wb = 255 then acc.markSpecial
  else acc.add (mantOf wa * mantOf wb) (idxOf wa + idxOf wb) (Bool.xor (signOf wa) (signOf wb))

/-- The loop has FloatLib's `dotStateLoop` shape; the accumulator's fields are plain arguments so
the compiled loop allocates nothing per term. -/
@[specialize] def dotLoop (fa fb : Nat → UInt32) (pos neg : Array Nat) (sp nz : Bool)
    (index : Nat) : Nat → Acc
  | 0 => ⟨pos, neg, sp, nz⟩
  | count + 1 =>
    match dotStep ⟨pos, neg, sp, nz⟩ (fa index) (fb index) with
    | ⟨p, n, s, z⟩ => dotLoop fa fb p n s z (index + 1) count

/-- The exact dot product of `[fa 0, …, fa (n-1)]` and `[fb 0, …, fb (n-1)]`. -/
@[inline] def dotFn (n : Nat) (fa fb : Nat → UInt32) : UInt32 :=
  let acc := dotLoop fa fb (Array.replicate 18 0) (Array.replicate 18 0) false true 0 n
  if acc.special then
    dotSpec (Array.ofFn (n := n) fun i => fa i) (Array.ofFn (n := n) fun i => fb i)
  else finishFast acc.pos acc.neg (-298) (n ≠ 0 && acc.negZero)

theorem sv_mul (wa wb : UInt32) :
    (if Bool.xor (signOf wa) (signOf wb) then -((mantOf wa * mantOf wb : Nat) : Int)
      else ((mantOf wa * mantOf wb : Nat) : Int)) = sv wa * sv wb := by
  unfold sv; cases signOf wa <;> cases signOf wb <;> simp

/-- A NaN or infinity, once seen, stays recorded. -/
theorem dotLoop_special (fa fb : Nat → UInt32) (pos neg : Array Nat) (nz : Bool)
    (index count : Nat) : (dotLoop fa fb pos neg true nz index count).special = true := by
  induction count generalizing pos neg nz index with
  | zero => rfl
  | succ count ih =>
    rw [dotLoop]
    have hs : (dotStep ⟨pos, neg, true, nz⟩ (fa index) (fb index)).special = true := by
      unfold dotStep Acc.markSpecial Acc.add; split_ifs <;> rfl
    generalize dotStep ⟨pos, neg, true, nz⟩ (fa index) (fb index) = r at hs ⊢
    obtain ⟨p, q, s, z⟩ := r
    simp only at hs; subst hs
    exact ih ..

/-- What a loop without specials tells us, stated over arrays `A`, `B` that hold the operands (as
the toolkit's FloatLib lemmas are). -/
theorem dotLoopFacts (fa fb : Nat → UInt32) (A B : Array UInt32) (n : Nat)
    (hA : ∀ k, k < n → A[k]! = fa k) (hB : ∀ k, k < n → B[k]! = fb k)
    (acc : Acc) (index remaining : Nat) (h : index + remaining ≤ n)
    (hp : acc.pos.size = 18) (hn : acc.neg.size = 18)
    (hfin : (dotLoop fa fb acc.pos acc.neg acc.special acc.negZero index remaining).special
      = false) :
    acc.special = false ∧
    (∀ k, index ≤ k → k < index + remaining → expOf A[k]! ≠ 255 ∧ expOf B[k]! ≠ 255) ∧
    (dotLoop fa fb acc.pos acc.neg acc.special acc.negZero index remaining).total =
      acc.total + dsum A B index remaining ∧
    (dotLoop fa fb acc.pos acc.neg acc.special acc.negZero index remaining).negZero =
      (acc.negZero && dallNZ A B index remaining) := by
  induction remaining generalizing acc index with
  | zero => obtain ⟨p, n, s, z⟩ := acc; simp_all [dotLoop, dsum, dallNZ]
  | succ count ih =>
    obtain ⟨p, q, s, z⟩ := acc
    simp only at hp hn
    have ha := hA index (by omega)
    have hb := hB index (by omega)
    by_cases he : expOf (fa index) = 255 ∨ expOf (fb index) = 255
    · exfalso
      rw [dotLoop] at hfin
      have hs : (dotStep ⟨p, q, s, z⟩ (fa index) (fb index)).special = true := by
        simp [dotStep, he, Acc.markSpecial]
      generalize dotStep ⟨p, q, s, z⟩ (fa index) (fb index) = r at hs hfin
      obtain ⟨p', q', s', z'⟩ := r
      simp only at hs; subst hs
      rw [dotLoop_special] at hfin
      exact Bool.noConfusion hfin
    · have he' := not_or.mp he
      obtain ⟨h1, h2, h3, h4, h5⟩ :=
        Acc.add_spec ⟨p, q, s, z⟩ (mantOf (fa index) * mantOf (fb index))
          (idxOf (fa index) + idxOf (fb index)) (Bool.xor (signOf (fa index)) (signOf (fb index)))
          hp hn (mul_mant_lt _ _)
          (by have := idxOf_le _ he'.1; have := idxOf_le _ he'.2; omega)
      have hstep : dotStep ⟨p, q, s, z⟩ (fa index) (fb index) =
          Acc.add ⟨p, q, s, z⟩ (mantOf (fa index) * mantOf (fb index))
            (idxOf (fa index) + idxOf (fb index))
            (Bool.xor (signOf (fa index)) (signOf (fb index))) := by
        simp [dotStep, he]
      rw [dotLoop, hstep] at hfin ⊢
      obtain ⟨hs, hall, hD, hz⟩ := ih _ (index + 1) (by omega) h1 h2 hfin
      refine ⟨by rw [← h3, hs], ?_, ?_, ?_⟩
      · intro k k1 k2
        rcases Nat.lt_or_ge k (index + 1) with hk | hk
        · have : k = index := by omega
          subst this; rw [ha, hb]; exact he'
        · exact hall k hk (by omega)
      · rw [hD, h5, dsum, ha, hb, sv_mul]; ring
      · rw [hz, h4, dallNZ, ha, hb]; simp [Bool.and_assoc]

theorem getElem!_ofFn (n : Nat) (f : Nat → UInt32) (k : Nat) (hk : k < n) :
    (Array.ofFn (n := n) fun i => f i.val)[k]! = f k := by
  rw [getElem!_pos _ k (by simpa using hk), Array.getElem_ofFn]

theorem dotFn_eq (n : Nat) (fa fb : Nat → UInt32) :
    dotFn n fa fb =
      dotSpec (Array.ofFn (n := n) fun i => fa i) (Array.ofFn (n := n) fun i => fb i) := by
  unfold dotFn
  set A := Array.ofFn (n := n) fun i => fa i with hA
  set B := Array.ofFn (n := n) fun i => fb i with hB
  set acc := dotLoop fa fb (Array.replicate 18 0) (Array.replicate 18 0) false true 0 n with hacc
  by_cases hsp : acc.special = true
  · simp [hsp]
  · have hsp' : acc.special = false := by simpa using hsp
    obtain ⟨-, hall, hD, hz⟩ := dotLoopFacts fa fb A B n (getElem!_ofFn n fa)
      (getElem!_ofFn n fb) Acc.empty 0 n (by omega) (by simp [Acc.empty]) (by simp [Acc.empty])
      hsp'
    have hD : acc.total = dsum A B 0 n := by
      have := hD; simp only [Acc.total_empty, Int.zero_add] at this; exact this
    have hz : acc.negZero = dallNZ A B 0 n := by
      have := hz; simp only [Acc.empty, Bool.true_and] at this; exact this
    simp only [hsp', Bool.false_eq_true, ite_false]
    rw [finishFast_eq, show ((limbVal acc.pos.toList : Int) - limbVal acc.neg.toList) = acc.total
      from rfl]
    -- FloatLib's side: every word is finite, and its exact total is ours.
    have hAsize : A.size = n := by simp [hA]
    have hBsize : B.size = n := by simp [hB]
    set L := A.map (Model.ofUInt32 (fmt := Fmt)) with hL
    set R := B.map (Model.ofUInt32 (fmt := Fmt)) with hR
    have hLR : L.size = R.size := by simp [hL, hR, hAsize, hBsize]
    have hLsize : L.size = n := by simp [hL, hAsize]
    have hLfin : ∀ k (hk : k < L.size), Model.isFinite L[k] = true := by
      intro k hk
      have hk' : k < A.size := by simpa [hL] using hk
      have := (hall k (by omega) (by omega)).1
      rw [getElem!_pos A k hk'] at this
      simp [hL, isFinite_ofUInt32, this]
    have hRfin : ∀ k (hk : k < R.size), Model.isFinite R[k] = true := by
      intro k hk
      have hk' : k < B.size := by simpa [hR] using hk
      have := (hall k (by omega) (by omega)).2
      rw [getElem!_pos B k hk'] at this
      simp [hR, isFinite_ofUInt32, this]
    have hslice : Model.Reduction.Semantics.finiteDotSlice L R 0 L.size (by simp)
        (by simp [hLR]) = (acc.total : ℚ) * 2 ^ (-298 : ℤ) := by
      have := finiteDotSlice_eq A B 0 L.size (by simp [hL]) (by simp [hL, hAsize, hBsize])
        (by intro k k1 k2; exact hall k k1 (by omega))
      exact this.trans (by rw [hLsize, hD])
    have hexact := Model.Reduction.Internal.dotState_exact_toRat
      (destination := Fmt) L R hLR hLfin hRfin
    unfold dotSpec Model.dot
    by_cases hS0 : acc.total = 0
    · have hz0 : (Model.Reduction.Internal.dotState L R hLR :
          Model.Reduction.Internal.State Fmt).exact.significand = 0 := by
        rw [← FloatLib.Numerics.Dyadic.toRat_eq_zero_iff, hexact, hslice, hS0]; simp
      rw [Model.Reduction.dotWithStatus_eq_zero_of_finite Fmt L R .nearestEven hLR hLfin hRfin
        hz0, hS0, finishWord_zero]
      unfold Model.Reduction.Internal.dotState
      obtain ⟨h1, h2⟩ := dotStateLoop_flags A B {} 0 L.size (by simp [hL])
        (by simp [hL, hAsize, hBsize]) (by intro k k1 k2; exact hall k k1 (by omega))
      have h1' : (Model.Reduction.Internal.dotStateLoop L R
          ({} : Model.Reduction.Internal.State Fmt) 0 L.size (by simp)
          (by simp [hLR])).sawFiniteTerm = decide (L.size ≠ 0) := by
        rw [show decide (L.size ≠ 0) = (false || decide (L.size ≠ 0)) by simp]; exact h1
      have h2' : (Model.Reduction.Internal.dotStateLoop L R
          ({} : Model.Reduction.Internal.State Fmt) 0 L.size (by simp)
          (by simp [hLR])).allTermsNegativeZero = dallNZ A B 0 L.size := by
        rw [show dallNZ A B 0 L.size = (true && dallNZ A B 0 L.size) by simp]; exact h2
      simp only [Except.map, h1', h2']
      rw [hz]
      simp [hLsize]
    · have hnz : Model.Reduction.Semantics.finiteDot L.toList R.toList ≠ .ok 0 := by
        rw [Model.Reduction.Semantics.finiteDot_toList_eq_slice L R hLR]
        intro h
        injection h with h
        rw [hslice] at h
        simp at h; exact hS0 h
      rw [Model.Reduction.dotWithStatus_eq_round_of_finite_nonzero Fmt L R .nearestEven hLR hLfin
        hRfin hnz]
      simp only [Except.map]
      exact finishWord_of_ne _ _ _ _ hS0 (by rw [hexact, hslice])

/-! ## Arrays as functions -/

theorem ofFn_getElem! (a : Array UInt32) (n : Nat) (h : n = a.size) :
    (Array.ofFn (n := n) fun i => a[i.val]!) = a := by
  subst h
  apply Array.ext (by simp)
  intro i h1 h2
  rw [Array.getElem_ofFn, getElem!_pos a i h2]

theorem ofFn_const (n : Nat) (c : UInt32) :
    (Array.ofFn (n := n) fun _ => c) = Array.replicate n c := by
  apply Array.ext (by simp)
  intro i h1 h2
  simp

/-! ## The kernels -/

/-- `dot`: `dotFn` over the two arrays; FloatLib's dot product for unequal sizes. -/
def dotX (a b : Array UInt32) : UInt32 :=
  if a.size = b.size then dotFn a.size (fun i => a[i]!) (fun i => b[i]!) else dotSpec a b

/-- `sum`: a dot product with ones. -/
def sumX (x : Array UInt32) : UInt32 := dotFn x.size (fun i => x[i]!) (fun _ => oneW)

theorem dotX_eq_spec (a b : Array UInt32) : dotX a b = dotSpec a b := by
  unfold dotX
  split
  · rename_i h
    rw [dotFn_eq, ofFn_getElem! a _ rfl, ofFn_getElem! b _ h]
  · rfl

theorem sumX_eq_spec (x : Array UInt32) : sumX x = sumSpec x := by
  rw [sumX, dotFn_eq, ofFn_getElem! x _ rfl, ofFn_const, sumSpec]

/-- `dotFn` is the spec's dot product, so every `…With` definition run with `dotFn` is its spec. -/
theorem dotFn_eq_dotOf : dotFn = dotOf :=
  funext fun n => funext fun fa => funext fun fb => dotFn_eq n fa fb

/-! ## Max pooling on words -/

theorem toWord_ofW (w : Word) : toWord (ofW w) = w := by
  apply UInt32.toNat_inj.mp
  simp only [toWord, ofW, Model.toNatBits, ofUInt32_bits, UInt32.toNat_ofNat']
  exact Nat.mod_eq_of_lt w.toBitVec.isLt

theorem ofW_toWord (z : Model Fmt) : ofW (toWord z) = z := by
  have h : z.toNatBits < 2 ^ 32 := Model.toNatBits_lt_two_pow z
  simp only [ofW, toWord, Model.ofUInt32, UInt32.toNat_ofNat', Nat.mod_eq_of_lt h]
  exact Model.ofNatBits_toNatBits z

/-- A finite word's exact value times `2^149`: `±mant · 2^idx`. -/
@[inline] def keyOf (w : Word) : Int :=
  if signOf w then -((mantOf w <<< idxOf w : Nat) : Int) else ((mantOf w <<< idxOf w : Nat) : Int)

theorem keyOf_eq (w : Word) : keyOf w = sv w * 2 ^ idxOf w := by
  unfold keyOf sv; split <;> simp [Nat.shiftLeft_eq]

theorem toReal_decodeD (w : Word) :
    (decodeD w).toReal = (keyOf w : ℝ) * 2 ^ (-149 : Int) := by
  rw [← FloatLib.Numerics.Dyadic.cast_toRat, decodeD_toRat, keyOf_eq]
  push_cast
  rw [zpow_sub₀ two_ne_zero, zpow_natCast]
  ring

/-- FloatLib's `maximum` on words: finite words compared by `keyOf`; the spec's own steps when
the values are equal (signed zeros) or a NaN or infinity is involved. -/
@[inline] def maxW (a b : Word) : Word :=
  if expOf a = 255 ∨ expOf b = 255 then toWord (Model.maximum (ofW a) (ofW b))
  else match compare (keyOf a) (keyOf b) with
    | .lt => b
    | .gt => a
    | .eq => toWord (if Model.isZero (ofW a) && Model.isZero (ofW b) then
        Model.zero Fmt (Model.signBit (ofW a) && Model.signBit (ofW b)) else ofW a)

theorem cmp_decodeD (a b : Word) :
    Model.cmpDyadic (decodeD a) (decodeD b) = compare (keyOf a) (keyOf b) := by
  have hs : (0 : ℝ) < 2 ^ (-149 : Int) := zpow_pos two_pos _
  cases h : compare (keyOf a) (keyOf b)
  · rw [Model.cmpDyadic_lt_iff, toReal_decodeD, toReal_decodeD]
    exact mul_lt_mul_of_pos_right (by exact_mod_cast compare_lt_iff_lt.mp h) hs
  · rw [Model.cmpDyadic_eq_iff, toReal_decodeD, toReal_decodeD, compare_eq_iff_eq.mp h]
  · rw [Model.cmpDyadic_gt_iff, toReal_decodeD, toReal_decodeD]
    exact mul_lt_mul_of_pos_right (by exact_mod_cast compare_gt_iff_gt.mp h) hs

theorem maxW_spec (a b : Word) : ofW (maxW a b) = Model.maximum (ofW a) (ofW b) := by
  unfold maxW
  split
  · exact ofW_toWord _
  · rename_i hs
    have ha := toDyadic_ofUInt32 a (fun h => hs (Or.inl h))
    have hb := toDyadic_ofUInt32 b (fun h => hs (Or.inr h))
    have hna := Model.isNaN_eq_false_of_toDyadic?_some ha
    have hnb := Model.isNaN_eq_false_of_toDyadic?_some hb
    have hc : Model.compare (ofW a) (ofW b) = some _ :=
      Model.compare_eq_some_cmpDyadic_of_toDyadic? _ _ ha hb
    rw [cmp_decodeD] at hc
    have hnone : Model.chooseNaN2 (ofW a) (ofW b) = none :=
      (Model.chooseNaN2_eq_none_iff _ _).2 ⟨hna, hnb⟩
    unfold Model.maximum
    rw [Model.withNaNSelection_of_none _ _ hnone]
    dsimp only
    rw [Model.compareNonNaN_eq_of_compare_eq_some _ _ _ _ hc]
    cases compare (keyOf a) (keyOf b) <;> simp only [ofW_toWord]

/-- `maxpoolSpec` with the running maximum kept as a word. -/
def maxpoolW (c h w k : Nat) (inp : Array Word) : Array Word :=
  Array.ofFn (n := c * (h / k * (w / k))) fun q =>
    let ch := q.val / (h / k * (w / k))
    let y := q.val / (w / k) % (h / k)
    let x := q.val % (w / k)
    (List.range (k * k)).foldl (fun acc t => maxW acc (poolAt h w k inp ch y x t))
      (poolAt h w k inp ch y x 0)

theorem foldl_maxW (p : Nat → Word) (l : List Nat) (acc : Word) :
    l.foldl (fun m t => Model.maximum m (ofW (p t))) (ofW acc) =
      ofW (l.foldl (fun a t => maxW a (p t)) acc) := by
  induction l generalizing acc with
  | nil => rfl
  | cons t l ih => simp only [List.foldl_cons, ← maxW_spec, ih]

theorem maxpoolW_eq : maxpoolW = maxpoolSpec := by
  funext c h w k inp
  simp only [maxpoolW, maxpoolSpec, foldl_maxW, toWord_ofW]

/-! ## The entry -/

/-- The entry: every dot-based kernel is the contract's definition run with `dotFn`. -/
def kernels : Kernels where
  core := ⟨sumX, dotX⟩
  dense := ⟨linearWith dotFn, gemmWith dotFn⟩
  conv := ⟨conv2dWith dotFn, depthwiseWith dotFn⟩
  elem := ⟨avgpoolWith dotFn, maxpoolW, addReluSpec, scaleShiftSpec⟩
  norm := ⟨rmsnormWith dotFn, layernormWith dotFn⟩

theorem correct : Obligation kernels := by
  simp only [Obligation, kernels, specKernels, specCore, specDense, specConv, specElem, specNorm,
    linearSpec, gemmSpec, conv2dSpec, depthwiseSpec, avgpoolSpec, rmsnormSpec, layernormSpec,
    maxpoolW_eq, dotFn_eq_dotOf, funext sumX_eq_spec, funext fun a => funext (dotX_eq_spec a)]

end Submission


/- R25: the actual portable UInt64 XOR key, not Float.lt or ExactValue.totalOrder.
   Proof probe only until the pinned runner accepts this exact source. -/
namespace Submission.R25OrderKey
open FloatLib.Floats FloatLib.Floats.Formats.BinaryInterchange

abbrev F64 := FloatFormat.binary64
abbrev raw (w : UInt64) : Model F64 := Model.ofBits w.toBitVec
abbrev native (x : Float) : Model F64 := Model.ofFloatModel x.toModel
noncomputable abbrev value (w : UInt64) : Real := Model.toReal (raw w)
noncomputable abbrev nativeValue (x : Float) : Real := Model.toReal (native x)
def negative (w : UInt64) : Bool := decide (9223372036854775808 ≤ w.toNat)
def magnitude (w : UInt64) : Nat := w.toNat % 9223372036854775808
def exponent (w : UInt64) : Nat := w.toNat / 4503599627370496 % 2048
def fraction (w : UInt64) : Nat := w.toNat % 4503599627370496

@[inline] def finite64 (word : UInt64) : Bool :=
  word &&& 0x7ff0000000000000 != 0x7ff0000000000000
@[inline] def orderKey (word : UInt64) : UInt64 :=
  if word &&& 0x8000000000000000 == 0 then word ^^^ 0x8000000000000000
  else word ^^^ 0xffffffffffffffff

theorem raw_sign (w : UInt64) : Model.signBit (raw w) = negative w := by
  rw [Model.signBit_eq_msb]
  exact BitVec.msb_eq_decide w.toBitVec

theorem raw_exp (w : UInt64) : Model.expField (raw w) = exponent w := by
  unfold Model.expField
  change ((w.toBitVec >>> 52) &&& (BitVec.ofNat 64 2047)).toNat = _
  rw [BitVec.toNat_and, BitVec.toNat_ushiftRight]
  change (w.toNat >>> 52) &&& (2 ^ 11 - 1) = w.toNat / 4503599627370496 % 2 ^ 11
  rw [Nat.and_two_pow_sub_one_eq_mod, Nat.shiftRight_eq_div_pow]

theorem raw_frac (w : UInt64) : Model.fracField (raw w) = fraction w := by
  unfold Model.fracField
  change (w.toBitVec &&& (BitVec.ofNat 64 4503599627370495)).toNat = _
  rw [BitVec.toNat_and]
  exact Nat.and_two_pow_sub_one_eq_mod w.toNat 52

theorem raw_fields (w : UInt64) :
    raw w = Model.ofFields F64 (negative w) (exponent w) (fraction w) := by
  rw [← raw_sign, ← raw_exp, ← raw_frac]
  exact (Model.ofFields_signBit_expField_fracField (raw w)).symm

theorem field_bounds (w : UInt64) :
    exponent w < 2048 ∧ fraction w < 4503599627370496 ∧
    magnitude w < 9223372036854775808 := by
  exact ⟨Nat.mod_lt _ (by decide), Nat.mod_lt _ (by decide), Nat.mod_lt _ (by decide)⟩

theorem magnitude_fields (w : UInt64) :
    magnitude w = exponent w * 4503599627370496 + fraction w := by
  unfold magnitude exponent fraction
  omega

theorem magnitude_div (w : UInt64) :
    magnitude w / 4503599627370496 = exponent w := by
  rw [magnitude_fields]
  have hf := (field_bounds w).2.1
  omega

theorem magnitude_mod (w : UInt64) :
    magnitude w % 4503599627370496 = fraction w := by
  rw [magnitude_fields]
  have hf := (field_bounds w).2.1
  omega

private theorem signMask_nat (w : UInt64) :
    (w &&& 0x8000000000000000).toNat =
      (w.toNat / 9223372036854775808) * 9223372036854775808 := by
  rw [UInt64.toNat_and]
  change w.toNat &&& 9223372036854775808 = _
  have hb := w.toNat_lt_size
  change w.toNat < 18446744073709551616 at hb
  have hd := Nat.and_div_two_pow (a := w.toNat) (b := 9223372036854775808) (n := 63)
  have hm := Nat.and_mod_two_pow (a := w.toNat) (b := 9223372036854775808) (n := 63)
  norm_num only [show (2 ^ 63 : Nat) = 9223372036854775808 by decide,
    Nat.div_self, Nat.mod_self, Nat.and_zero] at hd hm
  have hs : w.toNat / 9223372036854775808 = 0 ∨
      w.toNat / 9223372036854775808 = 1 := by omega
  rcases hs with hs | hs <;> simp only [hs] at hd <;> norm_num at hd <;> omega

private theorem expMask_nat (w : UInt64) :
    (w &&& 0x7ff0000000000000).toNat = exponent w * 4503599627370496 := by
  rw [UInt64.toNat_and]
  change w.toNat &&& 9218868437227405312 = _
  have hd := Nat.and_div_two_pow (a := w.toNat) (b := 9218868437227405312) (n := 52)
  have hm := Nat.and_mod_two_pow (a := w.toNat) (b := 9218868437227405312) (n := 52)
  norm_num only [show (2 ^ 52 : Nat) = 4503599627370496 by decide] at hd hm
  change (w.toNat &&& 9218868437227405312) / 4503599627370496 =
    (w.toNat / 4503599627370496) &&& (2 ^ 11 - 1) at hd
  rw [Nat.and_two_pow_sub_one_eq_mod] at hd
  norm_num at hm
  change (w.toNat &&& 9218868437227405312) / 4503599627370496 = exponent w at hd
  omega

theorem finite64_iff_exp (w : UInt64) :
    finite64 w = true ↔ exponent w < 2047 := by
  have he := (field_bounds w).1
  simp only [finite64, bne_iff_ne, ← UInt64.toNat_inj]
  rw [expMask_nat]
  change exponent w * 4503599627370496 ≠ 9218868437227405312 ↔ _
  omega

theorem finite64_model (w : UInt64) (h : finite64 w = true) :
    Model.isFinite (raw w) = true := by
  rw [raw_fields]
  exact Model.isFinite_ofFields_ieee F64 (by decide) _ _ _
    ((finite64_iff_exp w).mp h)

private theorem xor_sign_nat (w : UInt64) (hw : w.toNat < 9223372036854775808) :
    (w ^^^ 0x8000000000000000).toNat = w.toNat + 9223372036854775808 := by
  rw [UInt64.toNat_xor]
  change w.toNat ^^^ 9223372036854775808 = _
  have hd := Nat.xor_div_two_pow (a := w.toNat) (b := 9223372036854775808) (n := 63)
  have hm := Nat.xor_mod_two_pow (a := w.toNat) (b := 9223372036854775808) (n := 63)
  have hz : w.toNat / 9223372036854775808 = 0 := by omega
  norm_num only [show (2 ^ 63 : Nat) = 9223372036854775808 by decide,
    Nat.div_self, Nat.mod_self, hz, Nat.zero_xor, Nat.xor_zero] at hd hm
  rw [Nat.mod_eq_of_lt hw] at hm
  omega

theorem orderKey_nat (w : UInt64) :
    (orderKey w).toNat =
      if negative w then 9223372036854775807 - magnitude w
      else 9223372036854775808 + magnitude w := by
  have hb := w.toNat_lt_size
  change w.toNat < 18446744073709551616 at hb
  by_cases hs : w.toNat < 9223372036854775808
  · have hm : w &&& 0x8000000000000000 = 0 := by
      apply UInt64.toNat_inj.mp
      rw [signMask_nat]
      change w.toNat / 9223372036854775808 * 9223372036854775808 = 0
      omega
    have hn : negative w = false := by simp [negative]; omega
    simp only [orderKey, hm, beq_self_eq_true, ite_true, hn, Bool.false_eq_true,
      ite_false]
    rw [xor_sign_nat w hs]
    unfold magnitude
    rw [Nat.mod_eq_of_lt hs]
    omega
  · have hm : w &&& 0x8000000000000000 ≠ 0 := by
      intro hm
      have h := congrArg UInt64.toNat hm
      rw [signMask_nat] at h
      change w.toNat / 9223372036854775808 * 9223372036854775808 = 0 at h
      omega
    have hn : negative w = true := by simp [negative]; omega
    simp only [orderKey, beq_eq_false_iff_ne.mpr hm, Bool.false_eq_true, ite_false,
      hn, ite_true]
    change (w ^^^ (-1 : UInt64)).toNat = _
    rw [UInt64.xor_neg_one, UInt64.toNat_not]
    change 18446744073709551615 - w.toNat = _
    unfold magnitude
    omega

/-- Actual XOR-key strict order has one signed-zero tie; magnitude isolates it. -/
theorem orderKey_lt_cases (x y : UInt64) (h : orderKey x < orderKey y) :
    (negative x = false ∧ negative y = false ∧ magnitude x < magnitude y) ∨
    (negative x = true ∧ negative y = true ∧ magnitude y < magnitude x) ∨
    (negative x = true ∧ negative y = false) := by
  rw [UInt64.lt_iff_toNat_lt, orderKey_nat, orderKey_nat] at h
  have hx := (field_bounds x).2.2
  have hy := (field_bounds y).2.2
  cases hsx : negative x <;> cases hsy : negative y <;>
    simp [hsx, hsy] at h ⊢ <;> omega

noncomputable def magnitudeReal (m : Nat) : Real :=
  if m / 4503599627370496 = 0 then
    (m % 4503599627370496 : Real) * (2 : Real) ^ (-1074 : Int)
  else
    (4503599627370496 + m % 4503599627370496 : Nat) *
      (2 : Real) ^ ((m / 4503599627370496 : Nat) - (1075 : Int))

private theorem magnitudeReal_nonneg (m : Nat) : 0 ≤ magnitudeReal m := by
  unfold magnitudeReal
  split <;> positivity

private theorem magnitudeReal_zero : magnitudeReal 0 = 0 := by
  simp [magnitudeReal]

private theorem magnitudeReal_lt_same (a b : Nat)
    (he : a / 4503599627370496 = b / 4503599627370496)
    (hf : a % 4503599627370496 < b % 4503599627370496) :
    magnitudeReal a < magnitudeReal b := by
  unfold magnitudeReal
  rw [he]
  split
  · exact mul_lt_mul_of_pos_right (by exact_mod_cast hf) (zpow_pos (by norm_num) _)
  · apply mul_lt_mul_of_pos_right _ (zpow_pos (by norm_num) _)
    exact_mod_cast (Nat.add_lt_add_left hf 4503599627370496)

private theorem pow2_mono {a b : Int} (h : a ≤ b) :
    (2 : Real) ^ a ≤ (2 : Real) ^ b := by
  exact (zpow_le_zpow_iff_right₀ (G₀ := Real) (a := (2 : Real))
    (m := a) (n := b) (by norm_num)).mpr h

private theorem magnitudeReal_lt_exp (a b : Nat)
    (he : a / 4503599627370496 < b / 4503599627370496) :
    magnitudeReal a < magnitudeReal b := by
  have haF : a % 4503599627370496 < 4503599627370496 := Nat.mod_lt _ (by decide)
  have hbF : b % 4503599627370496 < 4503599627370496 := Nat.mod_lt _ (by decide)
  have hb0 : b / 4503599627370496 ≠ 0 := by omega
  unfold magnitudeReal
  rw [if_neg hb0]
  by_cases ha0 : a / 4503599627370496 = 0
  · rw [if_pos ha0]
    have hscale : (2 : Real) ^ (-1074 : Int) ≤
        (2 : Real) ^ ((b / 4503599627370496 : Nat) - (1075 : Int)) := by
      apply pow2_mono
      omega
    calc
      _ < (4503599627370496 : Real) * (2 : Real) ^ (-1074 : Int) :=
        mul_lt_mul_of_pos_right (by exact_mod_cast haF) (zpow_pos (by norm_num) _)
      _ ≤ (4503599627370496 : Real) *
          (2 : Real) ^ ((b / 4503599627370496 : Nat) - (1075 : Int)) :=
        mul_le_mul_of_nonneg_left hscale (by norm_num)
      _ ≤ _ := mul_le_mul_of_nonneg_right (by exact_mod_cast (show 4503599627370496 ≤ 4503599627370496 + b % 4503599627370496 by omega))
        (zpow_nonneg (by norm_num) _)
  · rw [if_neg ha0]
    have hscale : (2 : Real) ^ (((a / 4503599627370496 : Nat) : Int) + 1 - 1075) ≤
        (2 : Real) ^ ((b / 4503599627370496 : Nat) - (1075 : Int)) := by
      apply pow2_mono
      omega
    have hstep :
        (9007199254740992 : Real) *
            (2 : Real) ^ ((a / 4503599627370496 : Nat) - (1075 : Int)) =
          4503599627370496 *
            (2 : Real) ^ (((a / 4503599627370496 : Nat) : Int) + 1 - 1075) := by
      rw [show (((a / 4503599627370496 : Nat) : Int) + 1 - 1075) =
        ((a / 4503599627370496 : Nat) - (1075 : Int)) + 1 by omega]
      rw [zpow_add₀ (by norm_num : (2 : Real) ≠ 0)]
      norm_num
      ring
    calc
      _ < (9007199254740992 : Real) *
            (2 : Real) ^ ((a / 4503599627370496 : Nat) - (1075 : Int)) := by
        apply mul_lt_mul_of_pos_right _ (zpow_pos (by norm_num) _)
        exact_mod_cast (show 4503599627370496 + a % 4503599627370496 < 9007199254740992 by omega)
      _ = _ := hstep
      _ ≤ (4503599627370496 : Real) *
          (2 : Real) ^ ((b / 4503599627370496 : Nat) - (1075 : Int)) :=
        mul_le_mul_of_nonneg_left hscale (by norm_num)
      _ ≤ _ := mul_le_mul_of_nonneg_right (by exact_mod_cast (show 4503599627370496 ≤ 4503599627370496 + b % 4503599627370496 by omega))
        (zpow_nonneg (by norm_num) _)

theorem magnitudeReal_strictMono : StrictMono magnitudeReal := by
  intro a b hab
  rcases lt_or_eq_of_le (Nat.div_le_div_right hab.le) with he | he
  · exact magnitudeReal_lt_exp a b he
  · apply magnitudeReal_lt_same a b he
    omega

theorem magnitudeReal_pos_iff (m : Nat) : 0 < magnitudeReal m ↔ m ≠ 0 := by
  constructor
  · intro h hm
    subst m
    rw [magnitudeReal_zero] at h
    exact (lt_irrefl _ h)
  · intro h
    have hr := magnitudeReal_strictMono (Nat.pos_of_ne_zero h)
    simpa only [magnitudeReal_zero] using hr

/-- Exact raw binary64 decoding, including subnormals and both signed zeros. -/
theorem raw_value (w : UInt64) (hfin : finite64 w = true) :
    value w = if negative w then -magnitudeReal (magnitude w)
      else magnitudeReal (magnitude w) := by
  have he := (field_bounds w).1
  have hf := (field_bounds w).2.1
  have hmodel := finite64_model w hfin
  have hd := Model.toDyadic?_ofFields_of_isFinite F64 (negative w)
    (exponent w) (fraction w) he hf (by simpa only [← raw_fields] using hmodel)
  rw [← raw_fields] at hd
  change Model.toDyadic? (raw w) =
    (if exponent w = 0 then
      if fraction w = 0 then some ⟨negative w, 0, 0⟩
      else some ⟨negative w, fraction w, -1074⟩
    else some ⟨negative w, 4503599627370496 + fraction w,
      (exponent w : Int) - 1023 - 52⟩) at hd
  unfold value
  rw [Model.toReal_eq, hd]
  unfold magnitudeReal
  rw [magnitude_div, magnitude_mod]
  by_cases hE : exponent w = 0 <;> by_cases hF : fraction w = 0 <;>
    cases hs : negative w <;>
    simp [hE, hF, hs, FloatLib.Numerics.Dyadic.toReal,
      FloatLib.Numerics.Dyadic.signedSignificand,
      FloatLib.Floats.Formats.Flocq.bpow, FloatLib.Numerics.binaryRadix,
      FloatLib.Numerics.Radix.toReal, sub_sub, neg_mul]

/-- Strict order of the actual integer key transports to strict real order when
both raw words are finite and at least one magnitude is nonzero.
The disjunction is necessary: key(-0) < key(+0), but both denote real zero. -/
theorem orderKey_lt_real (x y : UInt64)
    (hx : finite64 x = true) (hy : finite64 y = true)
    (hnz : magnitude x ≠ 0 ∨ magnitude y ≠ 0)
    (hkey : orderKey x < orderKey y) :
    value x < value y := by
  rw [raw_value x hx, raw_value y hy]
  rcases orderKey_lt_cases x y hkey with ⟨hsx, hsy, hm⟩ | ⟨hsx, hsy, hm⟩ | ⟨hsx, hsy⟩
  · simp only [hsx, hsy, Bool.false_eq_true, ite_false]
    exact magnitudeReal_strictMono hm
  · simp only [hsx, hsy, ite_true]
    exact neg_lt_neg (magnitudeReal_strictMono hm)
  · simp only [hsx, hsy, Bool.false_eq_true, ite_false, ite_true]
    have hp := magnitudeReal_nonneg (magnitude x)
    have hq := magnitudeReal_nonneg (magnitude y)
    rcases hnz with hnz | hnz
    · have := (magnitudeReal_pos_iff (magnitude x)).mpr hnz
      linarith
    · have := (magnitudeReal_pos_iff (magnitude y)).mpr hnz
      linarith

theorem value_toBits (x : Float) : value x.toBits = nativeValue x := rfl

theorem orderKey_toBits_lt_real (x y : Float)
    (hx : finite64 x.toBits = true) (hy : finite64 y.toBits = true)
    (hnz : magnitude x.toBits ≠ 0 ∨ magnitude y.toBits ≠ 0)
    (hkey : orderKey x.toBits < orderKey y.toBits) :
    nativeValue x < nativeValue y := by
  exact orderKey_lt_real _ _ hx hy hnz hkey

/-- An exact finite raw word survives native ofBits; no NaN payload claim. -/
theorem native_ofBits (w : UInt64) (hfin : finite64 w = true) :
    native (Float.ofBits w) = raw w := by
  obtain ⟨d, hd⟩ := Model.exists_toDyadic?_of_isFinite (finite64_model w hfin)
  have hc : Model.IsModelCanonical (raw w) := by
    constructor
    intro he hm
    have hnan : Model.toModel (raw w) = Float.Model.UnpackedFloat.notANumber := by
      simp only [Model.toModel, Float.Model.UnpackedFloat.unpack, he, hm, ite_true, ite_false]
    rw [Model.toDyadic?_ieee_eq_model F64 (by decide), hnan] at hd
    simp [Model.unpackedToDyadic?] at hd
  change Model.ofFloatModel
    (ExecFloat.Binary.toFloat (ExecFloat.Binary.ofBits64 w)).toModel = raw w
  rw [ExecFloat.Binary.toModel_toFloat_eq, Model.ofFloatModel_toFloatModel]
  exact Model.canonicalizeModel_eq_self _ hc

theorem value_ofBits (w : UInt64) (hfin : finite64 w = true) :
    nativeValue (Float.ofBits w) = value w := by
  unfold nativeValue value
  rw [native_ofBits w hfin]

theorem orderKey_native_endpoints (lower upper : UInt64) (a b : Float)
    (hl : finite64 lower = true) (hu : finite64 upper = true)
    (ha : finite64 a.toBits = true) (hb : finite64 b.toBits = true)
    (hlnz : magnitude lower ≠ 0) (hunz : magnitude upper ≠ 0)
    (hlkey : orderKey lower < orderKey a.toBits)
    (hukey : orderKey b.toBits < orderKey upper) :
    value lower < nativeValue a ∧ nativeValue b < value upper :=
  ⟨orderKey_lt_real _ _ hl ha (Or.inl hlnz) hlkey,
    orderKey_lt_real _ _ hb hu (Or.inr hunz) hukey⟩

end Submission.R25OrderKey


/- Exact expression adapter for the R24 PortableF64 checker.
   Append after R25OrderKey; no import, new axiom, or arithmetic-policy change. -/
namespace Submission.R25Checker
open Submission.R25OrderKey

@[inline] def magnitude32 (q : UInt32) : UInt32 := q &&& 0x7fffffff
@[inline] def eWord (q : UInt32) : UInt32 := (magnitude32 q >>> 23) &&& 255
@[inline] def fWord (q : UInt32) : UInt32 := magnitude32 q &&& 0x7fffff
@[inline] def base (q : UInt32) : UInt64 :=
  ((eWord q).toUInt64 + 896) <<< 52 ||| ((fWord q).toUInt64 <<< 29)
@[inline] def delta (q : UInt32) : UInt64 :=
  if magnitude32 q == 0x00800000 then 0x20000000 else 0x10000000
@[inline] def below (q : UInt32) : UInt64 := base q - delta q
@[inline] def above (q : UInt32) : UInt64 := base q + 0x10000000
@[inline] def negative32 (q : UInt32) : Bool := q &&& 0x80000000 != 0
@[inline] def lowerWord (q : UInt32) : UInt64 :=
  if negative32 q then above q ||| 0x8000000000000000 else below q
@[inline] def upperWord (q : UInt32) : UInt64 :=
  if negative32 q then below q ||| 0x8000000000000000 else above q

@[inline] def certify (sum radius : Float) (sumWord : UInt64) (guess : UInt32) : Bool :=
  if eWord guess == 0 || eWord guess == 255 then false
  else
    let lowerEndpoint := (sum - radius).toBits
    let upperEndpoint := (sum + radius).toBits
    if !(finite64 sumWord && (finite64 lowerEndpoint && finite64 upperEndpoint)) then false
    else
      decide (orderKey (lowerWord guess) < orderKey lowerEndpoint) &&
        decide (orderKey upperEndpoint < orderKey (upperWord guess))

/-- Guards and inequalities are extracted from the actual expression. -/
theorem accepted_components (sum radius : Float) (sumWord : UInt64) (q : UInt32)
    (h : certify sum radius sumWord q = true) :
    eWord q ≠ 0 ∧ eWord q ≠ 255 ∧ finite64 sumWord = true ∧
    finite64 (sum - radius).toBits = true ∧ finite64 (sum + radius).toBits = true ∧
    orderKey (lowerWord q) < orderKey (sum - radius).toBits ∧
    orderKey (sum + radius).toBits < orderKey (upperWord q) := by
  unfold certify at h
  split at h
  · simp at h
  next he =>
    have he' : eWord q ≠ 0 ∧ eWord q ≠ 255 := by
      simpa only [Bool.or_eq_true, beq_iff_eq, not_or] using he
    dsimp only at h
    split at h
    · simp at h
    next hf =>
      have hf' : finite64 sumWord = true ∧
          finite64 (sum - radius).toBits = true ∧
          finite64 (sum + radius).toBits = true := by
        simpa only [Bool.not_eq_true, Bool.not_eq_false, Bool.and_eq_true] using hf
      have hk : orderKey (lowerWord q) < orderKey (sum - radius).toBits ∧
          orderKey (sum + radius).toBits < orderKey (upperWord q) := by
        simpa only [Bool.and_eq_true, decide_eq_true_eq] using h
      exact ⟨he'.1, he'.2, hf'.1, hf'.2.1, hf'.2.2, hk.1, hk.2⟩

private theorem eWord_bound (q : UInt32) : (eWord q).toNat < 256 := by
  rw [eWord, UInt32.toNat_and]
  change (magnitude32 q >>> 23).toNat &&& (2 ^ 8 - 1) < 2 ^ 8
  rw [Nat.and_two_pow_sub_one_eq_mod]
  exact Nat.mod_lt _ (by decide)

private theorem fWord_bound (q : UInt32) : (fWord q).toNat < 8388608 := by
  rw [fWord, UInt32.toNat_and]
  change (magnitude32 q).toNat &&& (2 ^ 23 - 1) < 2 ^ 23
  rw [Nat.and_two_pow_sub_one_eq_mod]
  exact Nat.mod_lt _ (by decide)

private theorem base_nat (q : UInt32) :
    (base q).toNat =
      ((eWord q).toNat + 896) * 4503599627370496 +
        (fWord q).toNat * 536870912 := by
  have he := eWord_bound q
  have hf := fWord_bound q
  have hE : ((((eWord q).toUInt64 + 896) <<< 52) : UInt64).toNat =
      ((eWord q).toNat + 896) * 4503599627370496 := by
    simp only [UInt64.toNat_shiftLeft, UInt64.toNat_add, UInt32.toNat_toUInt64]
    change ((((eWord q).toNat + 896) % 18446744073709551616) <<< 52) %
      18446744073709551616 = _
    rw [Nat.shiftLeft_eq]
    omega
  have hF : (((fWord q).toUInt64 <<< 29) : UInt64).toNat =
      (fWord q).toNat * 536870912 := by
    simp only [UInt64.toNat_shiftLeft, UInt32.toNat_toUInt64]
    change ((fWord q).toNat <<< 29) % 18446744073709551616 = _
    rw [Nat.shiftLeft_eq]
    omega
  rw [base, UInt64.toNat_or, hE, hF]
  have hsmall : (fWord q).toNat * 536870912 < 2 ^ 52 := by omega
  simpa only [Nat.mul_comm 4503599627370496, Nat.add_comm] using
    (Nat.two_pow_add_eq_or_of_lt hsmall ((eWord q).toNat + 896)).symm

private theorem delta_bounds (q : UInt32) :
    268435456 ≤ (delta q).toNat ∧ (delta q).toNat ≤ 536870912 := by
  unfold delta
  split <;> decide

/-- The unsigned midpoint words lie strictly inside finite positive binary64.
The minimum-normal special decrement is included in the bound. -/
theorem unsigned_bounds (q : UInt32) (he0 : eWord q ≠ 0) (he255 : eWord q ≠ 255) :
    0 < (below q).toNat ∧ (below q).toNat < 9218868437227405312 ∧
    0 < (above q).toNat ∧ (above q).toNat < 9218868437227405312 := by
  have he := eWord_bound q
  have hf := fWord_bound q
  have hE0 : (eWord q).toNat ≠ 0 := by
    intro h
    apply he0
    apply UInt32.toNat_inj.mp
    exact h
  have hE255 : (eWord q).toNat ≠ 255 := by
    intro h
    apply he255
    apply UInt32.toNat_inj.mp
    exact h
  have hd := delta_bounds q
  have hbase := base_nat q
  have hdelta : delta q ≤ base q := by
    rw [UInt64.le_iff_toNat_le, hbase]
    omega
  have hbelow : (below q).toNat = (base q).toNat - (delta q).toNat := by
    exact UInt64.toNat_sub_of_le _ _ hdelta
  have habove : (above q).toNat = (base q).toNat + 268435456 := by
    rw [above, UInt64.toNat_add]
    change ((base q).toNat + 268435456) % 18446744073709551616 = _
    omega
  rw [hbelow, habove]
  omega

private theorem signed_magnitude (w : UInt64) (h : w.toNat < 9223372036854775808) :
    magnitude (w ||| 0x8000000000000000) = w.toNat := by
  have hw : (w ||| 0x8000000000000000).toNat =
      9223372036854775808 + w.toNat := by
    rw [UInt64.toNat_or, Nat.or_comm]
    simpa only [Nat.mul_one] using (Nat.two_pow_add_eq_or_of_lt h 1).symm
  unfold magnitude
  rw [hw]
  omega

private theorem unsigned_magnitude (w : UInt64) (h : w.toNat < 9223372036854775808) :
    magnitude w = w.toNat := Nat.mod_eq_of_lt h

private theorem finite_of_magnitude (w : UInt64)
    (h : magnitude w < 9218868437227405312) : finite64 w = true := by
  apply (finite64_iff_exp w).mpr
  rw [← magnitude_div]
  omega

theorem midpoint_finite_nonzero (q : UInt32) (he0 : eWord q ≠ 0) (he255 : eWord q ≠ 255) :
    finite64 (lowerWord q) = true ∧ finite64 (upperWord q) = true ∧
    magnitude (lowerWord q) ≠ 0 ∧ magnitude (upperWord q) ≠ 0 := by
  have hb := unsigned_bounds q he0 he255
  have hlo : (below q).toNat < 9223372036854775808 := by omega
  have hhi : (above q).toNat < 9223372036854775808 := by omega
  have hm : 0 < magnitude (lowerWord q) ∧ magnitude (lowerWord q) < 9218868437227405312 ∧
      0 < magnitude (upperWord q) ∧ magnitude (upperWord q) < 9218868437227405312 := by
    cases hs : negative32 q <;>
      simp only [lowerWord, upperWord, hs, Bool.false_eq_true, ite_false, ite_true,
        unsigned_magnitude _ hlo, unsigned_magnitude _ hhi,
        signed_magnitude _ hlo, signed_magnitude _ hhi] <;> omega
  exact ⟨finite_of_magnitude _ hm.2.1, finite_of_magnitude _ hm.2.2.2,
    Nat.ne_of_gt hm.1, Nat.ne_of_gt hm.2.2.1⟩

/-- Actual checker acceptance gives strict real containment of its computed
native endpoints inside its computed raw midpoint words. No producer premise,
no externally assumed midpoint finiteness/nonzero, and no Float.lt substitution. -/
theorem accepted_native_bounds (sum radius : Float) (sumWord : UInt64) (q : UInt32)
    (h : certify sum radius sumWord q = true) :
    value (lowerWord q) < nativeValue (sum - radius) ∧
      nativeValue (sum + radius) < value (upperWord q) := by
  obtain ⟨he0, he255, _, hlo, hhi, hlkey, hukey⟩ :=
    accepted_components sum radius sumWord q h
  obtain ⟨hl, hu, hlnz, hunz⟩ := midpoint_finite_nonzero q he0 he255
  exact orderKey_native_endpoints _ _ _ _ hl hu hlo hhi hlnz hunz hlkey hukey

end Submission.R25Checker


namespace Submission.R24PortableF64
@[inline] def finite64 (word : UInt64) : Bool :=
  word &&& 0x7ff0000000000000 != 0x7ff0000000000000

/-- Arbitrary midpoint-up proposal, deliberately not a proved RN32 conversion. -/
@[inline] def proposal (word : UInt64) : UInt32 :=
  let magnitude :=
    (((((word &&& 0x7fffffffffffffff) + 0x10000000) >>> 29).toUInt32) - 0xc0000000) &&& 0x7fffffff
  ((word >>> 32).toUInt32 &&& 0x80000000) ||| magnitude

@[inline] def orderKey (word : UInt64) : UInt64 :=
  if word &&& 0x8000000000000000 == 0 then word ^^^ 0x8000000000000000
  else word ^^^ 0xffffffffffffffff

/-- Strict midpoint word checker, including the minimum-normal lower spacing. -/
@[inline] def certify (sum radius : Float) (sumWord : UInt64) (guess : UInt32) : Bool :=
  let magnitude := guess &&& 0x7fffffff
  let e := (magnitude >>> 23) &&& 255
  if e == 0 || e == 255 then false
  else
    let lowerEndpoint := (sum - radius).toBits
    let upperEndpoint := (sum + radius).toBits
    if !(finite64 sumWord && (finite64 lowerEndpoint && finite64 upperEndpoint)) then false
    else
      let base := ((e.toUInt64 + 896) <<< 52) ||| ((magnitude &&& 0x7fffff).toUInt64 <<< 29)
      let lowerDelta : UInt64 := if magnitude == 0x00800000 then 0x20000000 else 0x10000000
      let below := base - lowerDelta
      let above := base + 0x10000000
      let negative := guess &&& 0x80000000 != 0
      let lower := if negative then above ||| 0x8000000000000000 else below
      let upper := if negative then below ||| 0x8000000000000000 else above
      decide (orderKey lower < orderKey lowerEndpoint) &&
        decide (orderKey upperEndpoint < orderKey upper)


end Submission.R24PortableF64


namespace Submission.R25Checker
theorem finite64_eq_runtime (w : UInt64) :
    R25OrderKey.finite64 w = R24PortableF64.finite64 w := rfl
theorem orderKey_eq_runtime (w : UInt64) :
    R25OrderKey.orderKey w = R24PortableF64.orderKey w := rfl
theorem certify_eq_runtime (s r : Float) (sw : UInt64) (q : UInt32) :
    certify s r sw q = R24PortableF64.certify s r sw q := rfl
theorem actual_acceptance_bounds (s r : Float) (sw : UInt64) (q : UInt32)
    (h : R24PortableF64.certify s r sw q = true) :
    R25OrderKey.value (lowerWord q) < R25OrderKey.nativeValue (s - r) ∧
    R25OrderKey.nativeValue (s + r) < R25OrderKey.value (upperWord q) := by
  apply accepted_native_bounds s r sw q
  simpa only [certify_eq_runtime] using h
end Submission.R25Checker
