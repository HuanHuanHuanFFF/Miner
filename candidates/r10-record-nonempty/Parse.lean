import Lz77
import Slot

namespace Submission
open Aeneas Aeneas.Std Result ControlFlow

set_option maxRecDepth 8192
set_option maxHeartbeats 1000000

set_option linter.unusedTactic false
set_option linter.unreachableTactic false
set_option linter.unusedSimpArgs false
set_option linter.unusedVariables false

attribute [-instance] instNoNatZeroDivisorsOfIsAddTorsionFree

open LZ77 (toks bytes bytes_getElem! Matches emit_lit emit_match)

@[local step]
theorem lift_spec {α : Type} (x : α) : lift x ⦃ fun y => y = x ⦄ := by
  simp [lift, WP.spec_ok]

@[local step]
theorem get0_spec (v : Slice Std.U32) (i : Std.Usize) : slot.get0 v i ⦃ fun _ => True ⦄ := by
  rw [slot.get0]; split <;> step*

@[local scalar_tac x &&& y]
theorem nat_and_le_right (x y : Nat) : x &&& y ≤ y := Nat.and_le_right

@[local scalar_tac x >>> y]
theorem nat_shiftRight_le (x y : Nat) : x >>> y ≤ x := Nat.shiftRight_le x y

theorem numBits_ge : 32 ≤ System.Platform.numBits := by
  cases System.Platform.numBits_eq <;> simp [*]

@[local scalar_tac System.Platform.numBits]
theorem numBits_ge' : 32 ≤ System.Platform.numBits := numBits_ge

theorem lz_le_w {w : Nat} (x : BitVec w) : BitVec.leadingZeros x ≤ w := by
  unfold BitVec.leadingZeros; split <;> omega

theorem lz32_val (x : Std.U32) :
    (core.num.U32.leading_zeros x).val = BitVec.leadingZeros x.bv := by
  simp only [core.num.U32.leading_zeros, UScalar.val]
  have := lz_le_w x.bv
  apply Nat.mod_eq_of_lt
  simp at this ⊢
  omega

theorem lz32_eq (x : Std.U32) (h : x.val ≠ 0) :
    (core.num.U32.leading_zeros x).val = 31 - Nat.log 2 x.val := by
  rw [lz32_val]
  unfold BitVec.leadingZeros
  have hx : x.bv ≠ 0 := by
    intro h0; apply h; show x.bv.toNat = 0; rw [h0]; rfl
  rw [if_neg hx, UScalar.bv_toNat]
  omega

theorem lz32_le (x : Std.U32) : (core.num.U32.leading_zeros x).val ≤ 32 := by
  rw [lz32_val]; exact lz_le_w x.bv

theorem lz32_le_of_pow_le (x : Std.U32) (k : Nat) (h : 2 ^ k ≤ x.val) :
    (core.num.U32.leading_zeros x).val + k ≤ 31 := by
  have hx : x.val ≠ 0 := by have := Nat.one_le_two_pow (n := k); omega
  rw [lz32_eq x hx]
  have hk : k ≤ Nat.log 2 x.val := Nat.le_log_of_pow_le (by norm_num) h
  have : x.val < 2 ^ 32 := by scalar_tac
  have hl : Nat.log 2 x.val < 32 := Nat.log_lt_of_lt_pow (by omega) this
  omega

theorem lz32_ge_of_lt_pow (x : Std.U32) (k : Nat) (h : x.val < 2 ^ k) :
    32 - k ≤ (core.num.U32.leading_zeros x).val := by
  by_cases hx : x.val = 0
  · rw [lz32_val]; unfold BitVec.leadingZeros
    have : x.bv = 0 := by
      apply BitVec.eq_of_toNat_eq; rw [UScalar.bv_toNat]; simpa using hx
    rw [if_pos this]; omega
  · rw [lz32_eq x hx]
    have hl : Nat.log 2 x.val < k := Nat.log_lt_of_lt_pow hx h
    omega

theorem lz64_val (x : Std.U64) :
    (core.num.U64.leading_zeros x).val = BitVec.leadingZeros x.bv := by
  simp only [core.num.U64.leading_zeros, UScalar.val]
  have := lz_le_w x.bv
  apply Nat.mod_eq_of_lt
  simp at this ⊢
  omega

theorem lz64_le (x : Std.U64) : (core.num.U64.leading_zeros x).val ≤ 64 := by
  rw [lz64_val]; exact lz_le_w x.bv

@[local scalar_tac core.num.U32.leading_zeros x]
theorem lz32_bound (x : Std.U32) :
    (core.num.U32.leading_zeros x).val ≤ 32 ∧
      (x.val = 0 ∨ (core.num.U32.leading_zeros x).val ≤ 31) := by
  refine ⟨lz32_le x, ?_⟩
  by_cases h : x.val = 0
  · exact Or.inl h
  · right; rw [lz32_eq x h]; omega

@[local scalar_tac core.num.U64.leading_zeros x]
theorem lz64_bound (x : Std.U64) : (core.num.U64.leading_zeros x).val ≤ 64 := lz64_le x

def LeAll {ty : UScalarTy} (l : List (UScalar ty)) (B : Nat) : Prop :=
  ∀ j (h : j < l.length), (l[j]).val ≤ B

theorem LeAll_get {ty : UScalarTy} {l : List (UScalar ty)} {B : Nat} (hl : LeAll l B)
    (j : Nat) (hj : j < l.length) : (l[j]).val ≤ B := hl j hj

theorem LeAll_get! {ty : UScalarTy} {l : List (UScalar ty)} {B : Nat} (hl : LeAll l B)
    (j : Nat) (hj : j < l.length) : (l[j]!).val ≤ B := by
  rw [List.getElem!_eq_getElem?_getD, List.getElem?_eq_getElem hj]; exact hl j hj

theorem LeAll_mono {ty : UScalarTy} {l : List (UScalar ty)} {B B' : Nat} (hl : LeAll l B)
    (h : B ≤ B') : LeAll l B' := fun j hj => Nat.le_trans (hl j hj) h

theorem LeAll_replicate {ty : UScalarTy} (n : Nat) (x : UScalar ty) (B : Nat) (h : x.val ≤ B) :
    LeAll (List.replicate n x) B := by
  intro j hj; simp [List.getElem_replicate]; exact h

theorem LeAll_set {ty : UScalarTy} {l : List (UScalar ty)} {B : Nat} (hl : LeAll l B)
    (i : Nat) (x : UScalar ty) (hx : x.val ≤ B) : LeAll (l.set i x) B := by
  intro j hj
  rw [List.getElem_set]
  split
  · exact hx
  · exact hl j (by simpa using hj)

theorem LeAll_append {ty : UScalarTy} {l : List (UScalar ty)} {B : Nat} (hl : LeAll l B)
    (x : UScalar ty) (hx : x.val ≤ B) : LeAll (l ++ [x]) B := by
  intro j hj
  rw [List.getElem_append]
  split
  · exact hl j (by assumption)
  · simp; exact hx

theorem LeAll_set_succ {ty : UScalarTy} {l : List (UScalar ty)} {t : Nat} (hl : LeAll l t)
    (i : Nat) (x : UScalar ty) (hx : x.val ≤ t + 1) : LeAll (l.set i x) (t + 1) :=
  LeAll_set (LeAll_mono hl (Nat.le_succ t)) i x hx

@[local step]
theorem set_in_spec (v : Slice Std.U32) (i : Std.Usize) (x : Std.U32) :
    slot.set_in v i x ⦃ fun r => r.length = v.length ⦄ := by
  rw [slot.set_in]; split <;> step*

def DpNextl (nextl : Array Std.U16 512#usize) : Prop := ∀ j, j < 512 → j < (nextl.val[j]!).val

theorem dp_size {n : Nat} (h : n + n ≤ Std.Usize.max) : n + 2147483648 ≤ Std.Usize.max := by
  have : Std.Usize.max = 2 ^ System.Platform.numBits - 1 := by
    simp [Std.Usize.max, Std.Usize.numBits]
  rcases System.Platform.numBits_eq with h32 | h64
  · rw [this, h32] at h ⊢; omega
  · rw [this, h64] at h ⊢; omega

theorem dp_RING_val : slot.RING.val = 8192 := by simp [slot.RING]
theorem dp_WN_val : slot.WN.val = 32768 := by simp [slot.WN]
theorem dp_H3N_val : slot.H3N.val = 16384 := by simp [slot.H3N]
theorem dp_H4N_val : slot.H4N.val = 65536 := by simp [slot.H4N]
theorem dp_H7N_val : slot.H7N.val = 65536 := by simp [slot.H7N]
theorem dp_H3B_bound : 1 ≤ slot.H3B.val ∧ slot.H3B.val ≤ 32 := by simp [slot.H3B]
theorem dp_H4B_bound : 1 ≤ slot.H4B.val ∧ slot.H4B.val ≤ 32 := by simp [slot.H4B]
theorem dp_H7B_bound : 1 ≤ slot.H7B.val ∧ slot.H7B.val ≤ 64 := by simp [slot.H7B]
theorem dp_KB7_bound : slot.KB7.val ≤ 8 := by simp [slot.KB7]
theorem dp_UPD_bound : slot.UPD.val ≤ 1048576 := by simp [slot.UPD]
theorem dp_TMAX_bound : slot.TMAX.val ≤ 1048576 := by simp [slot.TMAX]
theorem dp_BEXT_TOP_bound : slot.BEXT_TOP.val ≤ 1048576 := by simp [slot.BEXT_TOP]

theorem dp_FRAC_le : LeAll slot.FRAC.val 16 := by
  unfold slot.FRAC LeAll; simp only [Array.make]; decide

theorem dp_shr9 (c : Std.U32) : c.val >>> 9 < 8388608 := by
  rw [Nat.shiftRight_eq_div_pow]
  have : c.val < 2 ^ 32 := by (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  omega

theorem dp_wadd_self (n : Std.Usize) (h : n.val < (core.num.Usize.wrapping_add n n).val) :
    n.val + n.val ≤ Std.Usize.max := by
  rw [core.num.Usize.wrapping_add_val_eq] at h
  have hs : Std.Usize.max = UScalar.size .Usize - 1 := by
    simp [Std.Usize.max, Std.Usize.size, Std.Usize.numBits]
  have hn : n.val < UScalar.size .Usize := by
    have := n.hBounds; simp only [UScalar.size]; exact this
  by_contra hc
  have h2 : UScalar.size .Usize ≤ n.val + n.val := by omega
  rw [Nat.mod_eq_sub_mod h2, Nat.mod_eq_of_lt (by omega)] at h
  omega

theorem dp_or_one_le (x : Nat) : x ||| 1 ≤ x + 1 := by
  have h := Nat.two_pow_add_eq_or_of_lt (i := 1) (b := 1) (by omega) (x / 2)
  have hx : x ||| 1 = 2 ^ 1 * (x / 2) ||| 1 := by
    rcases Nat.mod_two_eq_zero_or_one x with h0 | h1
    · have : x = 2 ^ 1 * (x / 2) := by omega
      conv_lhs => rw [this]
    · have e := Nat.two_pow_add_eq_or_of_lt (i := 1) (b := 1) (by omega) (x / 2)
      have : x = 2 ^ 1 * (x / 2) ||| 1 := by omega
      conv_lhs => rw [this]
      rw [Nat.or_assoc, Nat.or_self]
  rw [hx, ← h]
  omega

theorem dp_LeAll_repeat {ty : UScalarTy} (n : Std.Usize) (x : UScalar ty) (B : Nat) (h : x.val ≤ B) :
    LeAll (Array.repeat n x).val B := by
  rw [Array.repeat_val]; exact LeAll_replicate _ _ _ h

theorem dp_LeAll_set_of_eq {ty : UScalarTy} {n : Std.Usize} {a r : Array (UScalar ty) n} {i : Std.Usize}
    {v : UScalar ty} {B : Nat} (hr : r = a.set i v) (ha : LeAll a.val B) (hv : v.val ≤ B) : LeAll r.val B := by
  rw [hr, Array.set_val_eq]; exact LeAll_set ha _ _ hv

theorem dp_getElem!_set {ty : UScalarTy} (l : List (UScalar ty)) (i j : Nat) (x : UScalar ty)
    (hi : i < l.length) : (l.set i x)[j]! = if i = j then x else l[j]! := by
  simp only [List.getElem!_eq_getElem?_getD, List.getElem?_set]
  split
  · simp [*]
  · rfl

@[local step] theorem be8_spec (s : Slice Std.U8) (i : Std.Usize) (h : i.val + 8 ≤ Std.Usize.max) :
    slot.be8 s i ⦃ fun _ => True ⦄ := by
  rw [slot.be8]
  step*

@[local step]
theorem common_loop0_spec (s : Slice Std.U8) (a b cap k : Std.Usize) (run : Std.U32)
    (ha : a.val + cap.val + 8 ≤ Std.Usize.max) (hb : b.val + cap.val + 8 ≤ Std.Usize.max) (hk : k.val ≤ cap.val) :
    slot.common_loop0 s a b cap k run ⦃ fun r => r.1.val ≤ cap.val ⦄ := by
  rw [slot.common_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (k', run') => cap.val + 9 - k'.val + run'.val)
    (inv := fun (k', _) => k'.val ≤ cap.val)
  · rintro ⟨k', run'⟩ hk'
    simp only [slot.common_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals try (have := lz64_bound x)
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · exact hk

@[local step]
theorem common_loop1_spec (s : Slice Std.U8) (a b cap k : Std.Usize) (run : Std.U32)
    (ha : a.val + cap.val + 8 ≤ Std.Usize.max) (hb : b.val + cap.val + 8 ≤ Std.Usize.max) (hk : k.val ≤ cap.val) :
    slot.common_loop1 s a b cap k run ⦃ fun r => r.val ≤ cap.val ⦄ := by
  rw [slot.common_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (k', run') => cap.val + 1 - k'.val + run'.val)
    (inv := fun (k', _) => k'.val ≤ cap.val)
  · rintro ⟨k', run'⟩ hk'
    simp only [slot.common_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · exact hk

@[local step] theorem common_spec (s : Slice Std.U8) (a b cap : Std.Usize)
    (ha : a.val + cap.val + 8 ≤ Std.Usize.max) (hb : b.val + cap.val + 8 ≤ Std.Usize.max) :
    slot.common s a b cap ⦃ fun r => r.val ≤ cap.val ⦄ := by
  rw [slot.common]
  step*

@[local step] theorem hash3_spec (x : Std.U32) : slot.hash3 x ⦃ fun r => r.val < 16384 ⦄ := by
  have := dp_H3B_bound
  have := dp_H3N_val
  rw [slot.hash3]
  step*

@[local step] theorem hash4_spec (x : Std.U32) : slot.hash4 x ⦃ fun r => r.val < 65536 ⦄ := by
  have := dp_H4B_bound
  have := dp_H4N_val
  rw [slot.hash4]
  step*

@[local step] theorem hash7_spec (x : Std.U64) : slot.hash7 x ⦃ fun r => r.val < 65536 ⦄ := by
  have := dp_H7B_bound
  have := dp_H7N_val
  rw [slot.hash7]
  step*

@[local step] theorem probe_spec (s : Slice Std.U8) (c i : Std.Usize) (b8 : Std.U64) (cap best : Std.Usize)
    (hc : c.val ≤ i.val) (hcap : 9 ≤ cap.val) (hic : i.val + cap.val ≤ s.length)
    (hs8 : s.length + 8 ≤ Std.Usize.max) :
    slot.probe s c i b8 cap best ⦃ fun r => r.val ≤ cap.val ∧ (r.val = 0 ∨ best.val < r.val) ⦄ := by
  rw [slot.probe]
  step*
  repeat' (split <;> step*)
  all_goals try (have := lz64_bound x)
  all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))

@[local step]
theorem walk_loop_spec (s : Slice Std.U8) (prev) (i : Std.Usize) (b8 : Std.U64) (cap : Std.Usize)
    (cands) (nc best c k : Std.Usize)
    (hc : c.val ≤ i.val) (hcap : 9 ≤ cap.val) (hic : i.val + cap.val ≤ s.length)
    (hs8 : s.length + 8 ≤ Std.Usize.max) (hb : best.val ≤ cap.val) :
    slot.walk_loop s prev i b8 cap cands nc best c k ⦃ fun r => best.val ≤ r.2.2.val ∧ r.2.2.val ≤ cap.val ⦄ := by
  have hwn := dp_WN_val
  rw [slot.walk_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, k') => k'.val)
    (inv := fun (_, _, best', c', _) => c'.val ≤ i.val ∧ best.val ≤ best'.val ∧ best'.val ≤ cap.val)
  · rintro ⟨cands', nc', best', c', k'⟩ ⟨h1, h2, h3⟩
    simp only [slot.walk_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · exact ⟨hc, le_refl _, hb⟩

@[local step] theorem walk_spec (s : Slice Std.U8) (prev) (i start depth : Std.Usize) (b8 : Std.U64)
    (cap : Std.Usize) (cands) (nc0 best0 : Std.Usize)
    (hst : start.val ≤ i.val) (hcap : 9 ≤ cap.val) (hic : i.val + cap.val ≤ s.length)
    (hs8 : s.length + 8 ≤ Std.Usize.max) (hb : best0.val ≤ cap.val) :
    slot.walk s prev i start depth b8 cap cands nc0 best0 ⦃ fun r => best0.val ≤ r.1.2.val ∧ r.1.2.val ≤ cap.val ⦄ := by
  rw [slot.walk]
  step*

@[local step] theorem skip_same_spec (prev) (start depth : Std.Usize) (same : Bool) :
    slot.skip_same prev start depth same ⦃ fun r => r.1.val ≤ start.val ⦄ := by
  have hwn := dp_WN_val
  rw [slot.skip_same]
  step*
  repeat' (split <;> step*)
  all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))

@[local step] theorem insert_pos_spec (head3 : Array Std.U32 16384#usize) (head4 : Array Std.U32 65536#usize)
    (prev4) (head7 : Array Std.U32 65536#usize) (prev7) (q : Std.Usize) (b8 : Std.U64) (sh7 : Std.U32) (B : Nat)
    (h3 : LeAll head3.val B) (h4 : LeAll head4.val B) (h7 : LeAll head7.val B) (hq : q.val ≤ B) :
    slot.insert_pos head3 head4 prev4 head7 prev7 q b8 sh7 ⦃ fun r =>
      r.1.1.val ≤ B ∧ r.1.2.1.val ≤ B ∧ r.1.2.2.val ≤ B ∧
      LeAll r.2.1.val B ∧ LeAll r.2.2.1.val B ∧ LeAll r.2.2.2.2.1.val B ⦄ := by
  have hwn := dp_WN_val
  have H3 := h3
  have H4 := h4
  have H7 := h7
  rw [slot.insert_pos]
  step*
  have e3 := LeAll_get H3 h3.val (by scalar_tac)
  have e4 := LeAll_get H4 h4.val (by scalar_tac)
  have e7 := LeAll_get H7 h7.val (by scalar_tac)
  refine ⟨by scalar_tac, by scalar_tac, by scalar_tac, ?_, ?_, ?_⟩
  · exact dp_LeAll_set_of_eq head31_post H3 (by scalar_tac)
  · exact dp_LeAll_set_of_eq head41_post H4 (by scalar_tac)
  · exact dp_LeAll_set_of_eq head71_post H7 (by scalar_tac)

@[local step]
theorem insert_range_loop_spec (input : Slice Std.U8) (head3 : Array Std.U32 16384#usize)
    (head4 : Array Std.U32 65536#usize) (prev4) (head7 : Array Std.U32 65536#usize) (prev7)
    (e : Std.Usize) (sh7 : Std.U32) (q : Std.Usize) (B : Nat)
    (h3 : LeAll head3.val B) (h4 : LeAll head4.val B) (h7 : LeAll head7.val B)
    (he : e.val ≤ B + 1) (he8 : e.val + 8 ≤ Std.Usize.max) :
    slot.insert_range_loop input head3 head4 prev4 head7 prev7 e sh7 q ⦃ fun r =>
      LeAll r.1.val B ∧ LeAll r.2.1.val B ∧ LeAll r.2.2.2.1.val B ⦄ := by
  rw [slot.insert_range_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, _, q') => e.val - q'.val)
    (inv := fun (h3', h4', _, h7', _, _) => LeAll h3'.val B ∧ LeAll h4'.val B ∧ LeAll h7'.val B)
  · rintro ⟨h3', h4', p4', h7', p7', q'⟩ ⟨i3, i4, i7⟩
    simp only [slot.insert_range_loop.body]
    split
    · step*
      all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
    · step*
  · exact ⟨h3, h4, h7⟩

@[local step] theorem insert_range_spec (input : Slice Std.U8) (head3 : Array Std.U32 16384#usize)
    (head4 : Array Std.U32 65536#usize) (prev4) (head7 : Array Std.U32 65536#usize) (prev7)
    (f e : Std.Usize) (sh7 : Std.U32) (B : Nat)
    (h3 : LeAll head3.val B) (h4 : LeAll head4.val B) (h7 : LeAll head7.val B)
    (he : e.val ≤ B + 1) (he8 : e.val + 8 ≤ Std.Usize.max) :
    slot.insert_range input head3 head4 prev4 head7 prev7 f e sh7 ⦃ fun r =>
      LeAll r.1.val B ∧ LeAll r.2.1.val B ∧ LeAll r.2.2.2.1.val B ⦄ := by
  rw [slot.insert_range]
  exact insert_range_loop_spec input head3 head4 prev4 head7 prev7 e sh7 f B h3 h4 h7 he he8

theorem dp_nextl_lt {nextl : Array Std.U16 512#usize} (hnx : DpNextl nextl) (j : Nat)
    (hj : j < nextl.val.length) : j < (nextl.val[j]).val := by
  have hl : nextl.val.length = 512 := by simp
  have := hnx j (by omega)
  rwa [List.getElem!_eq_getElem?_getD, List.getElem?_eq_getElem hj, Option.getD_some] at this

@[local step] theorem relax_one_spec (pa) (slt : Std.Usize) (cost choice : Std.U32) :
    slot.relax_one pa slt cost choice ⦃ fun _ => True ⦄ := by
  have := dp_RING_val
  rw [slot.relax_one]
  step*
  repeat' (split <;> step*)

@[local step]
theorem relax_run_loop_spec (pa lc) (nextl : Array Std.U16 512#usize) (i hi : Std.Usize) (base dpack : Std.U32)
    (l : Std.Usize) (hnx : DpNextl nextl) (hhi : hi.val ≤ 512) (hih : i.val + hi.val ≤ Std.Usize.max) :
    slot.relax_run_loop pa lc nextl i hi base dpack l ⦃ fun _ => True ⦄ := by
  have := dp_RING_val
  rw [slot.relax_run_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, l') => hi.val - l'.val)
    (inv := fun _ => True)
  · rintro ⟨pa', l'⟩ _
    simp only [slot.relax_run_loop.body]
    split
    · step*
      repeat' (split <;> step*)
      all_goals
        have hx := dp_nextl_lt hnx i1.val (by scalar_tac)
        scalar_tac
    · step*
  · trivial

@[local step] theorem relax_run_spec (pa lc) (nextl : Array Std.U16 512#usize) (i lo hi : Std.Usize)
    (base dpack : Std.U32) (hnx : DpNextl nextl) (hhi : hi.val < 512) (hih : i.val + hi.val ≤ Std.Usize.max) :
    slot.relax_run pa lc nextl i lo hi base dpack ⦃ fun _ => True ⦄ := by
  have := dp_RING_val
  rw [slot.relax_run]
  step*
  repeat' (split <;> step*)

@[local step]
theorem back_best_loop_spec (input : Slice Std.U8) (pa lc) (i s len dd tmax t bt : Std.Usize) (bv : Std.U32)
    (hi : i.val < input.length) (hlen : len.val < 512) (hdd : dd.val < 8388608)
    (hN : input.length + 2147483648 ≤ Std.Usize.max)
    (ht : t.val ≤ i.val) (hbt : bt.val ≤ t.val) (ht258 : t.val = 0 ∨ len.val + t.val ≤ 258) :
    slot.back_best_loop input pa lc i s len dd tmax t bt bv ⦃ fun r =>
      r.1.val ≤ i.val ∧ (r.1.val = 0 ∨ len.val + r.1.val ≤ 258) ⦄ := by
  have := dp_RING_val
  rw [slot.back_best_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (t', _, _) => tmax.val - t'.val)
    (inv := fun (t', bt', _) => t'.val ≤ i.val ∧ bt'.val ≤ t'.val ∧ (t'.val = 0 ∨ len.val + t'.val ≤ 258))
  · rintro ⟨t', bt', bv'⟩ ⟨h1, h2, h3⟩
    simp only [slot.back_best_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · exact ⟨ht, hbt, ht258⟩

@[local step] theorem back_best_spec (input : Slice Std.U8) (pa lc) (i s len dd tmax : Std.Usize)
    (hi : i.val < input.length) (hlen : len.val < 512) (hdd : dd.val < 8388608)
    (hN : input.length + 2147483648 ≤ Std.Usize.max) :
    slot.back_best input pa lc i s len dd tmax ⦃ fun r => r.1.val ≤ i.val ∧ (r.1.val = 0 ∨ len.val + r.1.val ≤ 258) ⦄ := by
  rw [slot.back_best]
  step*

@[local step] theorem dsym_spec (dtab) (d : Std.Usize) : slot.dsym dtab d ⦃ fun _ => True ⦄ := by
  rw [slot.dsym]
  step*
  repeat' (split <;> step*)
  all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))

@[local step]
theorem relax_cands_loop_spec (input : Slice Std.U8) (pa cands nc lc) (nextl : Array Std.U16 512#usize)
    (dtab dcc) (i s : Std.Usize) (base : Std.U32) (pcd lo k : Std.Usize)
    (hnx : DpNextl nextl) (hi : i.val < input.length) (hN : input.length + 2147483648 ≤ Std.Usize.max) :
    slot.relax_cands_loop input pa cands nc lc nextl dtab dcc i s base pcd lo k ⦃ fun _ => True ⦄ := by
  have := dp_RING_val
  have := dp_BEXT_TOP_bound
  rw [slot.relax_cands_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, k') => 16 - k'.val)
    (inv := fun _ => True)
  · rintro ⟨pa', lo', k'⟩ _
    simp only [slot.relax_cands_loop.body]
    step*
    have := dp_shr9 c

    apply WP.spec_bind (Pₘ := fun _ => True)
    · repeat' (split <;> step*)
      all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
    · intro pa2 _
      step*
  · trivial

@[local step] theorem relax_cands_spec (input : Slice Std.U8) (pa cands nc lc) (nextl : Array Std.U16 512#usize)
    (dtab dcc) (i s : Std.Usize) (base : Std.U32) (pcd : Std.Usize)
    (hnx : DpNextl nextl) (hi : i.val < input.length) (hN : input.length + 2147483648 ≤ Std.Usize.max) :
    slot.relax_cands input pa cands nc lc nextl dtab dcc i s base pcd ⦃ fun _ => True ⦄ := by
  rw [slot.relax_cands]
  step*

@[local step]
theorem drop_farther_loop_spec (cands) (cd nc : Std.Usize) :
    slot.drop_farther_loop cands cd nc ⦃ fun _ => True ⦄ := by
  rw [slot.drop_farther_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun nc' => nc'.val)
    (inv := fun _ => True)
  · rintro nc' _
    simp only [slot.drop_farther_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · trivial

@[local step] theorem drop_farther_spec (cands) (nc0 cd : Std.Usize) : slot.drop_farther cands nc0 cd ⦃ fun _ => True ⦄ := by
  rw [slot.drop_farther]
  step*

@[local step] theorem next_anchor_spec (anchor i cl best : Std.Usize) : slot.next_anchor anchor i cl best ⦃ fun _ => True ⦄ := by
  rw [slot.next_anchor]
  repeat' (split <;> step*)

@[local step]
theorem ext_back_loop_spec (input : Slice Std.U8) (i d s max t : Std.Usize)
    (hi : i.val < input.length) (hd : d.val < 8388608) (hN : input.length + 2147483648 ≤ Std.Usize.max)
    (hsi : s.val ≤ i.val) (ht : t.val ≤ i.val - s.val) :
    slot.ext_back_loop input i d s max t ⦃ fun r => r.val ≤ i.val - s.val ⦄ := by
  rw [slot.ext_back_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun t' => max.val - t'.val)
    (inv := fun t' => t'.val ≤ i.val - s.val)
  · rintro t' h1
    simp only [slot.ext_back_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · exact ht

@[local step] theorem ext_back_spec (input : Slice Std.U8) (i d s max : Std.Usize)
    (hi : i.val < input.length) (hd : d.val < 8388608) (hN : input.length + 2147483648 ≤ Std.Usize.max)
    (hsi : s.val ≤ i.val) :
    slot.ext_back input i d s max ⦃ fun r => r.val ≤ i.val - s.val ⦄ := by
  rw [slot.ext_back]
  step*

@[local step]
theorem open_chunk_loop_spec (pa) (s u : Std.Usize) (hs : s.val + 259 ≤ Std.Usize.max) :
    slot.open_chunk_loop pa s u ⦃ fun _ => True ⦄ := by
  have := dp_RING_val
  rw [slot.open_chunk_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, u') => 259 - u'.val)
    (inv := fun _ => True)
  · rintro ⟨pa', u'⟩ _
    simp only [slot.open_chunk_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · trivial

@[local step] theorem open_chunk_spec (pa) (s : Std.Usize) (hs : s.val + 259 ≤ Std.Usize.max) :
    slot.open_chunk pa s ⦃ fun _ => True ⦄ := by
  have := dp_RING_val
  rw [slot.open_chunk]
  step*

@[local step]
theorem push_rev_loop_spec (plan tb lim k) : slot.push_rev_loop plan tb lim k ⦃ fun _ => True ⦄ := by
  have := dp_RING_val
  rw [slot.push_rev_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, k') => k'.val)
    (inv := fun _ => True)
  · rintro ⟨plan', k'⟩ _
    simp only [slot.push_rev_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · trivial

@[local step] theorem push_rev_spec (plan tb nt lim) : slot.push_rev plan tb nt lim ⦃ fun _ => True ⦄ := by
  rw [slot.push_rev]
  step*

@[local step]
theorem backtrack_loop_spec (input : Slice Std.U8) (pa) (s : Std.Usize) (lsym dtab lf df tb) (j nt guard : Std.Usize)
    (hs : s.val ≤ j.val) (hg : nt.val + guard.val ≤ Std.Usize.max) :
    slot.backtrack_loop input pa s lsym dtab lf df tb j nt guard ⦃ fun _ => True ⦄ := by
  have := dp_RING_val
  rw [slot.backtrack_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, _, g') => g'.val)
    (inv := fun (_, _, _, j', nt', g') => s.val ≤ j'.val ∧ nt'.val + g'.val ≤ Std.Usize.max)
  · rintro ⟨lf', df', tb', j', nt', g'⟩ ⟨h1, h2⟩
    simp only [slot.backtrack_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · exact ⟨hs, hg⟩

@[local step] theorem backtrack_spec (input : Slice Std.U8) (pa plan) (s e : Std.Usize) (lsym dtab lf df tb)
    (hse : s.val ≤ e.val) (he : e.val < Std.Usize.max) :
    slot.backtrack input pa plan s e lsym dtab lf df tb ⦃ fun _ => True ⦄ := by
  rw [slot.backtrack]
  step*

@[local step]
theorem halve_loop0_spec (lf s) : slot.halve_loop0 lf s ⦃ fun _ => True ⦄ := by
  rw [slot.halve_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, s') => 286 - s'.val)
    (inv := fun _ => True)
  · rintro ⟨lf', s'⟩ _
    simp only [slot.halve_loop0.body]
    step*
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · trivial

@[local step]
theorem halve_loop1_spec (df k) : slot.halve_loop1 df k ⦃ fun _ => True ⦄ := by
  rw [slot.halve_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, k') => 30 - k'.val)
    (inv := fun _ => True)
  · rintro ⟨df', k'⟩ _
    simp only [slot.halve_loop1.body]
    step*
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · trivial

@[local step] theorem halve_spec (lf df) : slot.halve lf df ⦃ fun _ => True ⦄ := by
  rw [slot.halve]
  step*

@[local step] theorem log2_16_spec (x : Std.U32) : slot.log2_16 x ⦃ fun _ => True ⦄ := by
  rw [slot.log2_16]
  split
  · step*
  · step*
    all_goals try (have := lz32_bound x)
    repeat' (split <;> step*)
    all_goals try (have := LeAll_get dp_FRAC_le i3.val (by (subst_vars; scalar_tac (simpAllMaxSteps := 0))))
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))

@[local step]
theorem costs_from_loop0_spec (freq total s) : slot.costs_from_loop0 freq total s ⦃ fun _ => True ⦄ := by
  rw [slot.costs_from_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, s') => freq.length - s'.val)
    (inv := fun _ => True)
  · rintro ⟨total', s'⟩ _
    simp only [slot.costs_from_loop0.body]
    step*
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · trivial

@[local step]
theorem costs_from_loop1_spec (freq out lt t) : slot.costs_from_loop1 freq out lt t ⦃ fun _ => True ⦄ := by
  rw [slot.costs_from_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, t') => freq.length - t'.val)
    (inv := fun _ => True)
  · rintro ⟨out', t'⟩ _
    simp only [slot.costs_from_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · trivial

@[local step] theorem costs_from_spec (freq out) : slot.costs_from freq out ⦃ fun _ => True ⦄ := by
  rw [slot.costs_from]
  step*

@[local step]
theorem huff_slot_loop_spec (freq : Slice Std.U32) (sym) (f : Std.U32) (j : Std.Usize) (hf : 0 < freq.length) :
    slot.huff_slot_loop freq sym f j ⦃ fun _ => True ⦄ := by
  rw [slot.huff_slot_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, j') => j'.val)
    (inv := fun _ => True)
  · rintro ⟨sym', j'⟩ _
    simp only [slot.huff_slot_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · trivial

@[local step] theorem huff_slot_spec (freq : Slice Std.U32) (sym) (ns : Std.Usize) (f : Std.U32) (hf : 0 < freq.length) :
    slot.huff_slot freq sym ns f ⦃ fun _ => True ⦄ := by
  rw [slot.huff_slot]
  step*

@[local step]
theorem huff_sort_loop_spec (freq : Slice Std.U32) (m sym) (ns i : Std.Usize)
    (hf : 0 < freq.length) (hns : ns.val ≤ i.val) (hi : i.val ≤ 320) :
    slot.huff_sort_loop freq m sym ns i ⦃ fun r => r.1.val ≤ 320 ⦄ := by
  rw [slot.huff_sort_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, i') => 320 - i'.val)
    (inv := fun (_, ns', i') => ns'.val ≤ i'.val ∧ i'.val ≤ 320)
  · rintro ⟨sym', ns', i'⟩ ⟨h1, h2⟩
    simp only [slot.huff_sort_loop.body]
    step*
    apply WP.spec_bind (Pₘ := fun (x : Std.Array Std.Usize 320#usize × Std.Usize) => x.2.val ≤ ns'.val + 1)
    · split
      · step*
      · step*
    · intro x hx
      rcases x with ⟨sym1, ns1⟩
      step*
      all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · exact ⟨hns, hi⟩

@[local step] theorem huff_sort_spec (freq : Slice Std.U32) (m sym) (hf : 0 < freq.length) :
    slot.huff_sort freq m sym ⦃ fun r => r.1.val ≤ 320 ⦄ := by
  rw [slot.huff_sort]
  step*

@[local step] theorem huff_take_spec (w) (a b ns nx : Std.Usize) (hab : a.val + b.val < Std.Usize.max) :
    slot.huff_take w a b ns nx ⦃ fun r => r.2.1.val + r.2.2.val = a.val + b.val + 1 ⦄ := by
  rw [slot.huff_take]
  step*
  repeat' (split <;> step*)
  all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))

@[local step]
theorem huff_build_loop_spec (w par) (ns a b nx : Std.Usize) (hns : ns.val ≤ 320) (hnx : nx.val ≤ 639)
    (hab : a.val + b.val + ns.val = 2 * nx.val) :
    slot.huff_build_loop w par ns a b nx ⦃ fun _ => True ⦄ := by
  rw [slot.huff_build_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, nx') => 639 - nx'.val)
    (inv := fun (_, _, a', b', nx') => nx'.val ≤ 639 ∧ a'.val + b'.val + ns.val = 2 * nx'.val)
  · rintro ⟨w', par', a', b', nx'⟩ ⟨h1, h2⟩
    simp only [slot.huff_build_loop.body]
    step*
    rcases y with ⟨i7, a1, b1⟩
    step*
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · exact ⟨hnx, hab⟩

@[local step] theorem huff_build_spec (w par) (ns : Std.Usize) (hns : ns.val ≤ 320) :
    slot.huff_build w par ns ⦃ fun _ => True ⦄ := by
  rw [slot.huff_build]
  step*

@[local step]
theorem huff_depths_loop_spec (par depth ns mx q) : slot.huff_depths_loop par depth ns mx q ⦃ fun _ => True ⦄ := by
  rw [slot.huff_depths_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, q') => q'.val)
    (inv := fun _ => True)
  · rintro ⟨depth', mx', q'⟩ _
    simp only [slot.huff_depths_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · trivial

@[local step] theorem huff_depths_spec (par depth nx ns) : slot.huff_depths par depth nx ns ⦃ fun _ => True ⦄ := by
  rw [slot.huff_depths]
  step*
  repeat' (split <;> step*)

@[local step]
theorem huff_costs_loop0_spec (freq : Slice Std.U32) (sym ns w k) (hf : 0 < freq.length) :
    slot.huff_costs_loop0 freq sym ns w k ⦃ fun _ => True ⦄ := by
  rw [slot.huff_costs_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, k') => ns.val - k'.val)
    (inv := fun _ => True)
  · rintro ⟨w', k'⟩ _
    simp only [slot.huff_costs_loop0.body]
    step*
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · trivial

@[local step]
theorem huff_costs_loop1_spec (m out) (mx : Std.U32) (t : Std.Usize) (hmx : mx.val ≤ 15) :
    slot.huff_costs_loop1 m out mx t ⦃ fun _ => True ⦄ := by
  rw [slot.huff_costs_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, t') => m.val - t'.val)
    (inv := fun _ => True)
  · rintro ⟨out', t'⟩ _
    simp only [slot.huff_costs_loop1.body]
    step*
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · trivial

@[local step]
theorem huff_costs_loop2_spec (out sym ns depth r) : slot.huff_costs_loop2 out sym ns depth r ⦃ fun _ => True ⦄ := by
  rw [slot.huff_costs_loop2]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, r') => ns.val - r'.val)
    (inv := fun _ => True)
  · rintro ⟨out', r'⟩ _
    simp only [slot.huff_costs_loop2.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · trivial

@[local step] theorem huff_costs_spec (freq : Slice Std.U32) (m out) (hf : 0 < freq.length) :
    slot.huff_costs freq m out ⦃ fun _ => True ⦄ := by
  rw [slot.huff_costs]
  step*
  apply WP.spec_bind (Pₘ := fun _ => True)
  · split
    · step*
    · step*
  · intro x _
    rcases x with ⟨depth1, mx⟩
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))

@[local step]
theorem make_costs_loop0_spec (litc llc b) : slot.make_costs_loop0 litc llc b ⦃ fun _ => True ⦄ := by
  rw [slot.make_costs_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, b') => 256 - b'.val)
    (inv := fun _ => True)
  · rintro ⟨litc', b'⟩ _
    simp only [slot.make_costs_loop0.body]
    step*
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · trivial

@[local step]
theorem make_costs_loop1_spec (lsym : Array Std.U8 512#usize) (lc) (llc : Array Std.U32 286#usize) (l : Std.Usize)
    (hls : LeAll lsym.val 28) : slot.make_costs_loop1 lsym lc llc l ⦃ fun _ => True ⦄ := by
  rw [slot.make_costs_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, l') => 259 - l'.val)
    (inv := fun _ => True)
  · rintro ⟨lc', l'⟩ _
    simp only [slot.make_costs_loop1.body]
    step*
    all_goals try (have := LeAll_get hls l'.val (by (subst_vars; scalar_tac (simpAllMaxSteps := 0))))
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · trivial

@[local step]
theorem make_costs_loop2_spec (dcc dc k) : slot.make_costs_loop2 dcc dc k ⦃ fun _ => True ⦄ := by
  rw [slot.make_costs_loop2]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, k') => 30 - k'.val)
    (inv := fun _ => True)
  · rintro ⟨dcc', k'⟩ _
    simp only [slot.make_costs_loop2.body]
    step*
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · trivial

@[local step] theorem make_costs_spec (lf df) (lsym : Array Std.U8 512#usize) (litc lc dcc huff)
    (hls : LeAll lsym.val 28) : slot.make_costs lf df lsym litc lc dcc huff ⦃ fun _ => True ⦄ := by
  rw [slot.make_costs]
  step*
  apply WP.spec_bind (Pₘ := fun _ => True)
  · split
    · step*
    · step*
  · intro x _
    rcases x with ⟨llc1, dc1⟩
    step*

@[local step]
theorem update_costs_h_loop_spec (lf tot z) : slot.update_costs_h_loop lf tot z ⦃ fun _ => True ⦄ := by
  rw [slot.update_costs_h_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, z') => 286 - z'.val)
    (inv := fun _ => True)
  · rintro ⟨tot', z'⟩ _
    simp only [slot.update_costs_h_loop.body]
    step*
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · trivial

@[local step] theorem update_costs_h_spec (lf df) (lsym : Array Std.U8 512#usize) (litc lc dcc huff half)
    (hls : LeAll lsym.val 28) : slot.update_costs_h lf df lsym litc lc dcc huff half ⦃ fun _ => True ⦄ := by
  rw [slot.update_costs_h]
  step*
  repeat' (split <;> step*)

@[local step] theorem update_costs_spec (lf df) (lsym : Array Std.U8 512#usize) (litc lc dcc huff)
    (hls : LeAll lsym.val 28) : slot.update_costs lf df lsym litc lc dcc huff ⦃ fun _ => True ⦄ := by
  rw [slot.update_costs]
  step*

@[local step]
theorem init_counts_loop0_spec (input : Slice Std.U8) (lf) (n step i : Std.Usize)
    (hn : n.val = input.length) (hstep : 1 ≤ step.val) (hns : n.val + step.val ≤ Std.Usize.max) :
    slot.init_counts_loop0 input lf n step i ⦃ fun _ => True ⦄ := by
  rw [slot.init_counts_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, i') => n.val - i'.val)
    (inv := fun _ => True)
  · rintro ⟨lf', i'⟩ _
    simp only [slot.init_counts_loop0.body]
    step*
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · trivial

@[local step]
theorem init_counts_loop1_spec (lf s) : slot.init_counts_loop1 lf s ⦃ fun _ => True ⦄ := by
  rw [slot.init_counts_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, s') => 286 - s'.val)
    (inv := fun _ => True)
  · rintro ⟨lf', s'⟩ _
    simp only [slot.init_counts_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · trivial

@[local step]
theorem init_counts_loop2_spec (df k) : slot.init_counts_loop2 df k ⦃ fun _ => True ⦄ := by
  rw [slot.init_counts_loop2]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, k') => 30 - k'.val)
    (inv := fun _ => True)
  · rintro ⟨df', k'⟩ _
    simp only [slot.init_counts_loop2.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · trivial

@[local step] theorem init_counts_spec (input : Slice Std.U8) (lf df)
    (hN : input.length + input.length ≤ Std.Usize.max) :
    slot.init_counts input lf df ⦃ fun _ => True ⦄ := by
  rw [slot.init_counts]
  step*
  all_goals
    have h1 := dp_or_one_le (input.length / 8192)
    have h2 : 1 ≤ input.length / 8192 ||| 1 := Nat.right_le_or
    scalar_tac

@[local step]
theorem fill_tables_loop0_spec (lsym : Array Std.U8 512#usize) (code l : Std.Usize)
    (hc : code.val ≤ 28) (hls : LeAll lsym.val 28) :
    slot.fill_tables_loop0 lsym code l ⦃ fun r => LeAll r.val 28 ⦄ := by
  rw [slot.fill_tables_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, l') => 259 - l'.val)
    (inv := fun (ls', c', _) => c'.val ≤ 28 ∧ LeAll ls'.val 28)
  · rintro ⟨ls', c', l'⟩ ⟨h1, h2⟩
    simp only [slot.fill_tables_loop0.body]
    split
    · apply WP.spec_bind (Pₘ := fun (x : Std.Usize) => x.val ≤ 28)
      · repeat' (split <;> step*)
        all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
      · intro code1 hc1
        step*
        and_intros
        all_goals first
          | exact dp_LeAll_set_of_eq a_post h2 (by (subst_vars; scalar_tac (simpAllMaxSteps := 0)))
          | (subst_vars; scalar_tac (simpAllMaxSteps := 0))
    · step*
  · exact ⟨hc, hls⟩

@[local step]
theorem fill_tables_loop1_spec (dtab c j) : slot.fill_tables_loop1 dtab c j ⦃ fun _ => True ⦄ := by
  rw [slot.fill_tables_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, j') => 256 - j'.val)
    (inv := fun _ => True)
  · rintro ⟨dtab', c', j'⟩ _
    simp only [slot.fill_tables_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · trivial

@[local step]
theorem fill_tables_loop2_loop0_spec (c2 d) : slot.fill_tables_loop2_loop0 c2 d ⦃ fun _ => True ⦄ := by
  rw [slot.fill_tables_loop2_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun c2' => 29 - c2'.val)
    (inv := fun _ => True)
  · rintro c2' _
    simp only [slot.fill_tables_loop2_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · trivial

@[local step]
theorem fill_tables_loop2_spec (dtab c2 k) : slot.fill_tables_loop2 dtab c2 k ⦃ fun _ => True ⦄ := by
  rw [slot.fill_tables_loop2]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, k') => 256 - k'.val)
    (inv := fun _ => True)
  · rintro ⟨dtab', c2', k'⟩ _
    simp only [slot.fill_tables_loop2.body]
    step*
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · trivial

@[local step] theorem fill_tables_spec (lsym : Array Std.U8 512#usize) (dtab) (hls : LeAll lsym.val 28) :
    slot.fill_tables lsym dtab ⦃ fun r => LeAll r.1.val 28 ⦄ := by
  rw [slot.fill_tables]
  step*

@[local step] theorem dp_sh7_spec (kb7 : Std.Usize) : slot.dp_sh7 kb7 ⦃ fun _ => True ⦄ := by
  rw [slot.dp_sh7]
  repeat' (split <;> step*)
  all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))

@[local step] theorem dp_upd_spec (upd : Std.Usize) : slot.dp_upd upd ⦃ fun r => r.val ≤ 1048576 ⦄ := by
  rw [slot.dp_upd]
  split <;> simp only [WP.spec_ok] <;> (subst_vars; scalar_tac (simpAllMaxSteps := 0))

@[local step] theorem dp_half_spec (half : Std.Usize) : slot.dp_half half ⦃ fun _ => True ⦄ := by
  rw [slot.dp_half]
  split <;> simp only [WP.spec_ok]

@[local step] theorem hashes_spec (b8 : Std.U64) (sh7 : Std.U32) : slot.hashes b8 sh7 ⦃ fun _ => True ⦄ := by
  rw [slot.hashes]
  step*

theorem lc_max_size : Std.Usize.max + 1 = Usize.size := by
  simp only [Std.Usize.max, Usize.size, Std.Usize.numBits, UScalar.size, UScalarTy.numBits]
  have := Nat.one_le_two_pow (n := System.Platform.numBits)
  omega

theorem lc_wadd1 (x : Std.Usize) (h : x.val + 1 ≤ Std.Usize.max) :
    (core.num.Usize.wrapping_add x 1#usize).val = x.val + 1 := by
  have hmx := lc_max_size
  have h1 : (1#usize).val = 1 := by simp
  rw [core.num.Usize.wrapping_add_val_eq, UScalar.size_UScalarTyUsize, h1, Nat.mod_eq_of_lt (by omega)]

theorem lc_tail_val (x b : Std.Usize) (h : x.val + b.val + 1 ≤ Std.Usize.max) (hb : 8 ≤ b.val) :
    (core.num.Usize.wrapping_sub (core.num.Usize.wrapping_add x b) 7#usize).val = x.val + b.val - 7 := by
  have hmx := lc_max_size
  have e1 : (core.num.Usize.wrapping_add x b).val = x.val + b.val := by
    rw [core.num.Usize.wrapping_add_val_eq, UScalar.size_UScalarTyUsize, Nat.mod_eq_of_lt (by omega)]
  rw [core.num.Usize.wrapping_sub_val_eq, UScalar.size_UScalarTyUsize, e1]
  have h7 : (7#usize).val = 7 := by simp
  rw [h7, show x.val + b.val + (Usize.size - 7) = (x.val + b.val - 7) + Usize.size by omega,
    Nat.add_mod_right, Nat.mod_eq_of_lt (by omega)]

@[local step] theorem tailw_spec (s : Slice Std.U8) (i best : Std.Usize) (h : i.val + best.val + 1 ≤ Std.Usize.max) :
    slot.tailw s i best ⦃ fun _ => True ⦄ := by
  rw [slot.tailw]
  split
  · have hb : 8 ≤ best.val := by scalar_tac
    have e := lc_tail_val i best h hb
    simp only [lift, bind_tc_ok]
    exact be8_spec _ _ (by rw [e]; omega)
  · simp only [WP.spec_ok]

@[local step]
theorem walk_t_loop_spec (s : Slice Std.U8) (prev) (i : Std.Usize) (b8 : Std.U64) (cap : Std.Usize)
    (cands) (nc best : Std.Usize) (tw : Std.U64) (c k : Std.Usize)
    (hc : c.val ≤ i.val) (hcap : 9 ≤ cap.val) (hic : i.val + cap.val ≤ s.length)
    (hs8 : s.length + 8 ≤ Std.Usize.max) (hb : best.val ≤ cap.val) :
    slot.walk_t_loop s prev i b8 cap cands nc best tw c k ⦃ fun r => best.val ≤ r.2.2.val ∧ r.2.2.val ≤ cap.val ⦄ := by
  have hwn := dp_WN_val
  rw [slot.walk_t_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, _, k') => k'.val)
    (inv := fun (_, _, best', _, c', _) => c'.val ≤ i.val ∧ best.val ≤ best'.val ∧ best'.val ≤ cap.val)
  · rintro ⟨cands', nc', best', tw', c', k'⟩ ⟨h1, h2, h3⟩
    simp only [slot.walk_t_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · exact ⟨hc, le_refl _, hb⟩

@[local step] theorem walk_t_spec (s : Slice Std.U8) (prev) (i start depth : Std.Usize) (b8 : Std.U64)
    (cap : Std.Usize) (cands) (nc0 best0 : Std.Usize)
    (hst : start.val ≤ i.val) (hcap : 9 ≤ cap.val) (hic : i.val + cap.val ≤ s.length)
    (hs8 : s.length + 8 ≤ Std.Usize.max) (hb : best0.val ≤ cap.val) :
    slot.walk_t s prev i start depth b8 cap cands nc0 best0 ⦃ fun r => best0.val ≤ r.1.2.val ∧ r.1.2.val ≤ cap.val ⦄ := by
  rw [slot.walk_t]
  step*
  all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))

@[local step] theorem dp_store_spec (head3 : Array Std.U32 16384#usize) (head4 : Array Std.U32 65536#usize)
    (prev4) (head7 : Array Std.U32 65536#usize) (prev7) (i x3 x4 x7 c4 c7 : Std.Usize) (B : Nat)
    (h3 : LeAll head3.val B) (h4 : LeAll head4.val B) (h7 : LeAll head7.val B) (hi : i.val ≤ B) :
    slot.dp_store head3 head4 prev4 head7 prev7 i x3 x4 x7 c4 c7 ⦃ fun r =>
      LeAll r.1.val B ∧ LeAll r.2.1.val B ∧ LeAll r.2.2.2.1.val B ⦄ := by
  have hwn := dp_WN_val
  have H3 := h3
  have H4 := h4
  have H7 := h7
  rw [slot.dp_store]
  step*
  refine ⟨?_, ?_, ?_⟩
  · exact dp_LeAll_set_of_eq head31_post H3 (by scalar_tac)
  · exact dp_LeAll_set_of_eq head41_post H4 (by scalar_tac)
  · exact dp_LeAll_set_of_eq head71_post H7 (by scalar_tac)

@[local step] theorem dp_heads_spec (head3 : Array Std.U32 16384#usize) (head4 : Array Std.U32 65536#usize)
    (head7 : Array Std.U32 65536#usize) (x3 x4 x7 : Std.Usize) (B : Nat)
    (h3 : LeAll head3.val B) (h4 : LeAll head4.val B) (h7 : LeAll head7.val B) :
    slot.dp_heads head3 head4 head7 x3 x4 x7 ⦃ fun r => r.1.val ≤ B ∧ r.2.1.val ≤ B ∧ r.2.2.val ≤ B ⦄ := by
  have H3 := h3
  have H4 := h4
  have H7 := h7
  rw [slot.dp_heads]
  step*
  have e3 := LeAll_get H3 i.val (by scalar_tac)
  have e4 := LeAll_get H4 i3.val (by scalar_tac)
  have e7 := LeAll_get H7 i6.val (by scalar_tac)
  refine ⟨by scalar_tac, by scalar_tac, by scalar_tac⟩

@[local step]
theorem relax_seq_loop_spec (pa lc) (i hi : Std.Usize) (base dpack : Std.U32) (l : Std.Usize) :
    slot.relax_seq_loop pa lc i hi base dpack l ⦃ fun _ => True ⦄ := by
  have := dp_RING_val
  rw [slot.relax_seq_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, l') => 512 - l'.val)
    (inv := fun _ => True)
  · rintro ⟨pa', l'⟩ _
    simp only [slot.relax_seq_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · trivial

@[local step] theorem relax_seq_spec (pa lc) (i lo hi : Std.Usize) (base dpack : Std.U32) :
    slot.relax_seq pa lc i lo hi base dpack ⦃ fun _ => True ⦄ := by
  rw [slot.relax_seq]
  step*

@[local step]
theorem rc_seq_loop_spec (input : Slice Std.U8) (pa cands nc lc dtab dcc) (i s : Std.Usize) (base : Std.U32)
    (pcd tmax lo k : Std.Usize)
    (hi : i.val < input.length) (hN : input.length + 2147483648 ≤ Std.Usize.max) :
    slot.rc_seq_loop input pa cands nc lc dtab dcc i s base pcd tmax lo k ⦃ fun _ => True ⦄ := by
  have := dp_RING_val
  have := dp_BEXT_TOP_bound
  rw [slot.rc_seq_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, k') => 16 - k'.val)
    (inv := fun _ => True)
  · rintro ⟨pa', lo', k'⟩ _
    simp only [slot.rc_seq_loop.body]
    step*
    have := dp_shr9 c
    apply WP.spec_bind (Pₘ := fun _ => True)
    · repeat' (split <;> step*)
      all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
    · intro pa2 _
      step*
  · trivial

@[local step] theorem rc_seq_spec (input : Slice Std.U8) (pa cands nc lc dtab dcc) (i s : Std.Usize)
    (base : Std.U32) (pcd tmax : Std.Usize)
    (hi : i.val < input.length) (hN : input.length + 2147483648 ≤ Std.Usize.max) :
    slot.rc_seq input pa cands nc lc dtab dcc i s base pcd tmax ⦃ fun _ => True ⦄ := by
  rw [slot.rc_seq]
  step*

theorem dp_sat_sub_val (x y : Std.Usize) :
    (core.num.Usize.saturating_sub x y).val = x.val - y.val := by
  have hx := x.hBounds
  show (BitVec.ofNat _ (max 0 (x.val - y.val))).toNat = x.val - y.val
  rw [BitVec.toNat_ofNat, Nat.zero_max]
  exact Nat.mod_eq_of_lt (lt_of_le_of_lt (Nat.sub_le _ _) hx)

theorem dp_ite3_spec {α : Type} {a b c : Prop} [Decidable a] [Decidable b] [Decidable c]
    {X Y : Result α} {P : α → Prop} (hX : a → b → ¬c → X ⦃ P ⦄) (hY : Y ⦃ P ⦄) :
    (if a then (if b then (if c then Y else X) else Y) else Y) ⦃ P ⦄ := by
  by_cases ha : a
  · rw [if_pos ha]
    by_cases hb : b
    · rw [if_pos hb]
      by_cases hc : c
      · rw [if_pos hc]; exact hY
      · rw [if_neg hc]; exact hX ha hb hc
    · rw [if_neg hb]; exact hY
  · rw [if_neg ha]; exact hY

theorem dp_ite_spec {α : Type} {c : Prop} [Decidable c] {A B : Result α} {P : α → Prop}
    (hA : c → A ⦃ P ⦄) (hB : ¬c → B ⦃ P ⦄) : (if c then A else B) ⦃ P ⦄ := by
  by_cases h : c
  · rw [if_pos h]; exact hA h
  · rw [if_neg h]; exact hB h

theorem dp_ite2_spec {α : Type} {a b : Prop} [Decidable a] [Decidable b]
    {X Y : Result α} {P : α → Prop} (hX : a → b → X ⦃ P ⦄) (hY : Y ⦃ P ⦄) :
    (if a then (if b then X else Y) else Y) ⦃ P ⦄ := by
  by_cases ha : a
  · rw [if_pos ha]
    by_cases hb : b
    · rw [if_pos hb]; exact hX ha hb
    · rw [if_neg hb]; exact hY
  · rw [if_neg ha]; exact hY

theorem d3_le_max (x : Std.Usize) : x.val ≤ Std.Usize.max := by scalar_tac

theorem d3_ok {α : Type} {x : α} {P : α → Prop} (h : P x) : (ok x : Result α) ⦃ P ⦄ := (WP.spec_ok x).mpr h

theorem d3_bind {α β : Type} {m : Result α} {k : α → Result β} {Q : α → Prop} {P : β → Prop}
    (h1 : m ⦃ Q ⦄) (h2 : ∀ x, Q x → k x ⦃ P ⦄) : (do let x ← m; k x) ⦃ P ⦄ := WP.spec_bind h1 h2

theorem d3_unc {α β γ : Type} {f : α → β → Result γ} {a : α} {b : β} {P : γ → Prop} (h : f a b ⦃ P ⦄) :
    (uncurry f (a, b)) ⦃ P ⦄ := h

theorem d3_add {x y : Std.Usize} {β : Type} {k : Std.Usize → Result β} {P : β → Prop} {a b : Nat}
    (hx : x.val = a) (hy : y.val = b) (h : a + b ≤ Std.Usize.max)
    (hk : ∀ z : Std.Usize, z.val = a + b → k z ⦃ P ⦄) : (do let z ← x + y; k z) ⦃ P ⦄ := by
  subst hx hy; exact WP.spec_bind (Usize.add_spec h) hk

theorem d3_sub {x y : Std.Usize} {β : Type} {k : Std.Usize → Result β} {P : β → Prop} {a b : Nat}
    (hx : x.val = a) (hy : y.val = b) (h : b ≤ a)
    (hk : ∀ z : Std.Usize, z.val + b = a → k z ⦃ P ⦄) : (do let z ← x - y; k z) ⦃ P ⦄ := by
  subst hx hy; exact WP.spec_bind (Usize.sub_spec h) (fun z hz => hk z (by omega))

theorem d3_rem {ty : UScalarTy} {x y : UScalar ty} {β : Type} {k : UScalar ty → Result β} {P : β → Prop} {b : Nat}
    (hy : y.val = b) (h : 0 < b) (hk : ∀ z : UScalar ty, z.val < b → k z ⦃ P ⦄) :
    (do let z ← x % y; k z) ⦃ P ⦄ := by
  subst hy
  exact WP.spec_bind (UScalar.rem_spec x (by omega)) (fun z hz => hk z (by rw [hz]; exact Nat.mod_lt _ h))

theorem d3_alen {α : Type} {n : Std.Usize} (v : Array α n) {i : Std.Usize} {c : Nat}
    (hn : n.val = c) (h : i.val < c) : i.val < v.length :=
  lt_of_lt_of_eq h ((Array.length_eq v).trans hn).symm

theorem d3_idx {α β : Type} {n : Std.Usize} {v : Array α n} {i : Std.Usize} {k : α → Result β} {P : β → Prop}
    {c : Nat} (hn : n.val = c) (h : i.val < c) (hk : ∀ x, k x ⦃ P ⦄) :
    (do let x ← Array.index_usize v i; k x) ⦃ P ⦄ :=
  WP.spec_bind (Array.index_usize_spec v i (d3_alen v hn h)) (fun x _ => hk x)

theorem d3_upd {α β : Type} {n : Std.Usize} {v : Array α n} {i : Std.Usize} {x : α}
    {k : Array α n → Result β} {P : β → Prop}
    {c : Nat} (hn : n.val = c) (h : i.val < c) (hk : ∀ a, a = v.set i x → k a ⦃ P ⦄) :
    (do let a ← Array.update v i x; k a) ⦃ P ⦄ :=
  WP.spec_bind (Array.update_spec v i x (d3_alen v hn h)) hk

theorem d3_sidx {α β : Type} {v : Slice α} {i : Std.Usize} {k : α → Result β} {P : β → Prop}
    (h : i.val < v.length) (hk : ∀ x, k x ⦃ P ⦄) : (do let x ← Slice.index_usize v i; k x) ⦃ P ⦄ :=
  WP.spec_bind (Slice.index_usize_spec v i h) (fun x _ => hk x)

theorem d3_shl {ty : UScalarTy} {ty1 : IScalarTy} {x : UScalar ty} {y : IScalar ty1} {β : Type}
    {k : UScalar ty → Result β} {P : β → Prop}
    (h : 0 ≤ y.val ∧ y.val < ty.numBits) (hk : ∀ z, k z ⦃ P ⦄) : (do let z ← x <<< y; k z) ⦃ P ⦄ :=
  WP.spec_bind (UScalar.ShiftLeft_IScalar_spec x y _ h.1 h.2 rfl) (fun z _ => hk z)

theorem d3_shr {ty : UScalarTy} {ty1 : IScalarTy} {x : UScalar ty} {y : IScalar ty1} {β : Type}
    {k : UScalar ty → Result β} {P : β → Prop} {n : Nat}
    (h : 0 ≤ y.val ∧ y.val < ty.numBits) (hn : y.toNat = n) (hk : ∀ z : UScalar ty, z.val = x.val >>> n → k z ⦃ P ⦄) :
    (do let z ← x >>> y; k z) ⦃ P ⦄ := by
  subst hn
  exact WP.spec_bind (UScalar.ShiftRight_IScalar_spec x y h.1 h.2) (fun z hz => hk z hz.1)

theorem d3_cast_le {src : UScalarTy} (tgt : UScalarTy) (x : UScalar src) : (UScalar.cast tgt x).val ≤ x.val := by
  rw [UScalar.cast_val_eq]; exact Nat.mod_le _ _

theorem d3_max_ge : 4294967295 ≤ Std.Usize.max := by scalar_tac

theorem d3_true {α : Type} {m : Result α} {Q : α → Prop} (h : m ⦃ Q ⦄) : m ⦃ fun _ => True ⦄ :=
  WP.spec_mono h (fun _ _ => trivial)

theorem dp_parse_loop_spec (input : Slice Std.U8) (plan) (ct lazyn d4 d7 skip h3d huff tmax n : Std.Usize)
    (head3 : Array Std.U32 16384#usize) (head4 : Array Std.U32 65536#usize) (prev4)
    (head7 : Array Std.U32 65536#usize) (prev7 pa tb) (lsym : Array Std.U8 512#usize) (dtab)
    (lf df litc lc dcc) (lim : Std.Usize) (sh7 : Std.U32) (updn : Std.Usize) (halfn : Std.U32)
    (s next_upd : Std.Usize) (cands) (cl cd : Std.Usize) (cdc : Std.U32) (i anchor alen : Std.Usize)
    (b8 : Std.U64) (x3 x4 x7 : Std.Usize) (pre : Std.Usize × Std.Usize × Std.Usize)
    (hn : n.val = input.length) (hlim : lim.val + 8 = n.val)
    (hN : input.length + input.length ≤ Std.Usize.max)
    (hls : LeAll lsym.val 28) (hupd : updn.val ≤ 1048576)
    (hsi : s.val ≤ i.val) (hin : i.val ≤ n.val) (hcl : cl.val < 512)
    (h3 : LeAll head3.val i.val) (h4 : LeAll head4.val i.val) (h7 : LeAll head7.val i.val)
    (hc3 : pre.1.val ≤ i.val) (hc4 : pre.2.1.val ≤ i.val) (hc7 : pre.2.2.val ≤ i.val) :
    slot.dp_parse_loop input plan ct lazyn d4 d7 skip h3d huff tmax n head3 head4 prev4 head7 prev7 pa tb
      lsym dtab lf df litc lc dcc lim sh7 updn halfn s next_upd cands cl cd cdc i anchor alen b8 x3 x4 x7 pre
      ⦃ fun _ => True ⦄ := by
  have hS := dp_size hN
  rw [slot.dp_parse_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, i', _, _, _, _, _, _, _) => lim.val - i'.val)
    (inv := fun (_, h3', h4', _, h7', _, _, _, _, _, _, _, _, s', _, _, cl', _, _, i', _, _, _, _, _, _, pre') =>
       s'.val ≤ i'.val ∧ i'.val ≤ n.val ∧ cl'.val < 512 ∧ LeAll h3'.val i'.val ∧ LeAll h4'.val i'.val ∧
       LeAll h7'.val i'.val ∧ pre'.1.val ≤ i'.val ∧ pre'.2.1.val ≤ i'.val ∧ pre'.2.2.val ≤ i'.val)
  · rintro ⟨plan', h3', h4', p4', h7', p7', pa', tb', lf', df', litc', lc', dcc', s', nu', cands', cl', cd', cdc',
      i', anc', alen', b8', x3', x4', x7', c3, c4, c7⟩ ⟨hs', hi', hcl', hh3, hh4, hh7, hq1, hq2, hq3⟩
    have hq1 : c3.val ≤ i'.val := hq1
    have hq2 : c4.val ≤ i'.val := hq2
    have hq3 : c7.val ≤ i'.val := hq3
    clear hsi hin hcl h3 h4 h7 hc3 hc4 hc7
    clear plan head3 head4 prev4 head7 prev7 pa tb lf df litc lc dcc s next_upd cands cl cd cdc i anchor alen b8 x3 x4 x7
      pre
    simp only [slot.dp_parse_loop.body, lift, bind_tc_ok]
    apply dp_ite_spec <;> intro hlt
    swap
    · exact d3_ok trivial
    have hlt' : i'.val < lim.val := (UScalar.lt_equiv _ _).mp hlt
    have hiM : i'.val + 2147483648 ≤ Std.Usize.max := by clear * - hi' hn hS; omega

    refine d3_bind (Q := fun _ => True) ?_ ?_
    · apply dp_ite_spec <;> intro _
      · refine d3_add (b := 258) rfl rfl (by clear * - hiM; omega) ?_; intro i1 _
        refine d3_rem (b := 8192) dp_RING_val (by decide) ?_; intro i2 hi2
        exact d3_true (Array.update_spec _ _ _ (d3_alen _ rfl hi2))
      · exact d3_ok trivial
    intro pa1 _

    refine d3_bind (dp_store_spec _ _ _ _ _ _ _ _ _ _ _ i'.val hh3 hh4 hh7 (le_refl _)) ?_
    rintro ⟨head31, head41, prev41, head71, prev71⟩ ⟨hL3, hL4, hL7⟩
    have hL3 : LeAll head31.val i'.val := hL3
    have hL4 : LeAll head41.val i'.val := hL4
    have hL7 : LeAll head71.val i'.val := hL7
    iterate 4 refine d3_unc ?_
    have hw1 : (core.num.Usize.wrapping_add i' 1#usize).val = i'.val + 1 :=
      lc_wadd1 i' (by clear * - hiM; omega)
    refine d3_bind (be8_spec _ _ (by rw [hw1]; clear * - hiM; omega)) ?_; intro b8n _
    refine d3_bind (hashes_spec _ _) ?_; rintro ⟨i8, i9, i10⟩ _
    iterate 2 refine d3_unc ?_
    refine d3_bind (dp_heads_spec _ _ _ _ _ _ i'.val hL3 hL4 hL7) ?_; intro pn1 hpn
    have hn1 : pn1.1.val ≤ i'.val := hpn.1
    have hn2 : pn1.2.1.val ≤ i'.val := hpn.2.1
    have hn3 : pn1.2.2.val ≤ i'.val := hpn.2.2
    clear hpn hh3 hh4 hh7

    refine d3_rem (b := 8192) dp_RING_val (by decide) ?_; intro i11 hi11
    refine d3_idx (c := 8192) rfl hi11 ?_; intro i12
    refine d3_shr (n := 32) (by decide) rfl ?_; intro i13 _
    refine d3_add (b := 1) rfl rfl (by clear * - hiM; omega) ?_; intro i14 hi14
    refine d3_shr (n := 56) (by decide) rfl ?_; intro i15 _
    refine d3_rem (b := 256) rfl (by decide) ?_; intro i17 hi17
    refine d3_idx (c := 256) rfl hi17 ?_; intro i18
    refine d3_bind (relax_one_spec _ _ _ _) ?_; intro pa2 _
    refine d3_bind (Q := fun _ => True) ?_ ?_
    · apply dp_ite_spec <;> intro _ <;> exact d3_ok trivial
    intro lzn _
    clear hi11 hi17 hlt
    refine d3_bind (Q := fun (x : alloc.vec.Vec Std.U32 × Array Std.U32 16384#usize × Array Std.U32 65536#usize ×
          Array Std.U32 32768#usize × Array Std.U32 65536#usize × Array Std.U32 32768#usize × Array Std.U64 8192#usize ×
          Array Std.U32 8192#usize × Array Std.U32 320#usize × Array Std.U32 32#usize × Std.Usize × Array Std.U32 16#usize ×
          Std.Usize × Std.Usize × Std.U32 × Std.Usize × Std.Usize × Std.Usize × Bool) =>
        match x with
        | (_, g3, g4, _, g7, _, _, _, _, _, s1, _, cl1, _, _, i12, _, _, _) =>
          s1.val ≤ i12.val ∧ i'.val < i12.val ∧ i12.val ≤ n.val ∧ cl1.val < 512 ∧
          LeAll g3.val i12.val ∧ LeAll g4.val i12.val ∧ LeAll g7.val i12.val) ?_ ?_
    · apply dp_ite3_spec
      ·
        intro _ hc3 _
        have hc3' : 3 ≤ cl'.val := (UScalar.le_equiv _ _).mp hc3
        have h14 : i'.val < i14.val := by clear * - hi14; omega
        refine d3_add rfl rfl (by clear * - hiM hcl'; omega) ?_; intro i23 _
        refine d3_rem (b := 512) rfl (by decide) ?_; intro i25 hi25
        refine d3_idx (c := 512) rfl hi25 ?_; intro i26
        refine d3_shl (by decide) ?_; intro i29
        refine d3_bind (relax_one_spec _ _ _ _) ?_; intro pa4 _
        refine d3_sub (b := 1) rfl rfl (by clear * - hc3'; omega) ?_; intro cl2 hcl2
        exact d3_ok ⟨(by clear * - hs' h14; omega : s'.val ≤ i14.val), h14,
          (by clear * - hi14 hlt' hlim; omega : i14.val ≤ n.val), (by clear * - hcl2 hcl'; omega : cl2.val < 512),
          LeAll_mono hL3 (Nat.le_of_lt h14), LeAll_mono hL4 (Nat.le_of_lt h14), LeAll_mono hL7 (Nat.le_of_lt h14)⟩
      ·
        refine d3_sub rfl rfl hi' ?_; intro cap hcap
        refine d3_bind (Q := fun (x : Std.Usize) => 9 ≤ x.val ∧ i'.val + x.val ≤ n.val) ?_ ?_
        · apply dp_ite_spec <;> intro h
          · have h' : 258 < cap.val := (UScalar.lt_equiv _ _).mp h
            exact d3_ok ⟨(by decide : 9 ≤ 258), (by clear * - h' hcap; omega : i'.val + 258 ≤ n.val)⟩
          · exact d3_ok ⟨(by clear * - hcap hlt' hlim; omega : 9 ≤ cap.val),
              (by clear * - hcap; omega : i'.val + cap.val ≤ n.val)⟩
        rintro cap1 ⟨hcap1, hcap2⟩
        have hic : i'.val + cap1.val ≤ input.length := by clear * - hcap2 hn; omega
        have hs8 : input.length + 8 ≤ Std.Usize.max := by clear * - hS; omega
        have hilt : i'.val < input.length := by clear * - hic hcap1; omega
        clear hcap cap

        refine d3_bind (Q := fun (x : Array Std.U32 16#usize × Std.Usize × Std.Usize × Bool) =>
          2 ≤ x.2.2.1.val ∧ x.2.2.1.val ≤ cap1.val) ?_ ?_
        · apply dp_ite_spec <;> intro _
          · refine d3_bind (probe_spec _ _ _ _ _ _ hq1 hcap1 hic hs8) ?_; intro l3 hl3
            refine d3_bind (Q := fun (x : Array Std.U32 16#usize × Std.Usize × Std.Usize) =>
              2 ≤ x.2.2.val ∧ x.2.2.val ≤ cap1.val) ?_ ?_
            · apply dp_ite_spec <;> intro h0
              · have h0' : 0 < l3.val := (UScalar.lt_equiv _ _).mp h0
                have hl3' : l3.val = 0 ∨ 2 < l3.val := hl3.2
                refine d3_shl (by decide) ?_; intro i21
                refine d3_upd (c := 16) rfl (by decide) ?_; intro a1 _
                exact d3_ok ⟨(by clear * - h0' hl3'; omega : 2 ≤ l3.val), hl3.1⟩
              · exact d3_ok ⟨(by decide : 2 ≤ 2), (by clear * - hcap1; omega : 2 ≤ cap1.val)⟩
            rintro ⟨a, i17, i18⟩ ⟨hb1, hb2⟩
            exact d3_unc (d3_unc (d3_ok ⟨hb1, hb2⟩))
          · exact d3_ok ⟨(by decide : 2 ≤ 2), (by clear * - hcap1; omega : 2 ≤ cap1.val)⟩
        rintro ⟨cands2, nc, best, p3⟩ ⟨hb1, hb2⟩
        have hb1 : 2 ≤ best.val := hb1
        have hb2 : best.val ≤ cap1.val := hb2
        iterate 3 refine d3_unc ?_
        refine d3_bind (Q := fun _ => True) ?_ ?_
        · apply dp_ite_spec <;> intro _ <;> exact d3_ok trivial
        intro b _

        refine d3_bind (skip_same_spec _ _ _ _) ?_; rintro ⟨i24, i25⟩ hsk
        have hsk : i24.val ≤ i'.val := Nat.le_trans hsk hq2
        refine d3_unc ?_
        refine d3_bind (walk_spec _ _ _ _ _ _ _ _ _ _ hsk hcap1 hic hs8 hb2) ?_
        rintro ⟨⟨nc1, best1⟩, cands3⟩ ⟨hw1, hw2⟩
        have hw1 : 2 ≤ best1.val := Nat.le_trans hb1 hw1
        have hw2 : best1.val ≤ cap1.val := hw2
        iterate 2 refine d3_unc ?_
        refine d3_bind (Q := fun _ => True) ?_ ?_
        · apply dp_ite_spec <;> intro _
          · exact d3_ok trivial
          · refine d3_bind (Q := fun _ => True) ?_ ?_
            · apply dp_ite_spec <;> intro _ <;> exact d3_ok trivial
            intro _ _; exact d3_ok trivial
        rintro ⟨cands4, dep7⟩ _
        refine d3_unc ?_
        refine d3_bind (Q := fun _ => True) ?_ ?_
        · apply dp_ite_spec <;> intro _
          · apply dp_ite_spec <;> intro _
            · exact d3_ok trivial
            · apply dp_ite_spec <;> intro _ <;> exact d3_ok trivial
          · apply dp_ite_spec <;> intro _ <;> exact d3_ok trivial
        intro b1 _

        refine d3_bind (skip_same_spec _ _ _ _) ?_; rintro ⟨i26, i27⟩ hsk2
        have hsk2 : i26.val ≤ i'.val := Nat.le_trans hsk2 hq3
        refine d3_unc ?_
        refine d3_bind (walk_t_spec _ _ _ _ _ _ _ _ _ _ hsk2 hcap1 hic hs8 hw2) ?_
        rintro ⟨⟨nc2, best2⟩, cands5⟩ ⟨hw3, hw4⟩
        have hw3 : 2 ≤ best2.val := Nat.le_trans hw1 hw3
        have hw4 : best2.val ≤ cap1.val := hw4
        iterate 2 refine d3_unc ?_

        refine d3_bind (Q := fun (x : Array Std.U32 16#usize × Std.Usize × Std.Usize) =>
          2 ≤ x.2.2.val ∧ x.2.2.val ≤ cap1.val) ?_ ?_
        · apply dp_ite2_spec
          · intro hgt hle
            have hgt' : best2.val < cl'.val := (UScalar.lt_equiv _ _).mp hgt
            refine d3_bind (drop_farther_spec _ _ _) ?_; intro nc4 _
            refine d3_shl (by decide) ?_; intro i30
            refine d3_rem (b := 16) rfl (by decide) ?_; intro i31 hi31
            refine d3_upd (c := 16) rfl hi31 ?_; intro a _
            refine d3_bind (Q := fun _ => True) ?_ ?_
            · apply dp_ite_spec <;> intro h16
              · have h16' : nc4.val < 16 := (UScalar.lt_equiv _ _).mp h16
                exact d3_true (Usize.add_spec (by
                  have := d3_max_ge
                  show nc4.val + 1 ≤ Std.Usize.max
                  clear * - h16' this; omega))
              · exact d3_ok trivial
            intro i33 _
            exact d3_ok ⟨(by clear * - hgt' hw3; omega : 2 ≤ cl'.val), (UScalar.le_equiv _ _).mp hle⟩
          · exact d3_ok ⟨hw3, hw4⟩
        rintro ⟨cands6, nc3, best3⟩ ⟨hb3, hb4⟩
        have hb3 : 2 ≤ best3.val := hb3
        have hb4 : best3.val ≤ cap1.val := hb4
        iterate 2 refine d3_unc ?_
        clear hb1 hb2 hw1 hw2 hw3 hw4 hsk hsk2 hq1 hq2 hq3

        refine d3_bind (Q := fun _ => True) ?_ ?_
        · apply dp_ite_spec <;> intro _ <;> exact d3_ok trivial
        intro pcd _
        refine d3_bind (next_anchor_spec _ _ _ _) ?_; intro alen2 _
        refine d3_bind (next_anchor_spec _ _ _ _) ?_; intro anchor2 _
        refine d3_bind (Q := fun (x : Std.Usize × Std.Usize × Std.U32) => x.1.val < 512) ?_ ?_
        · apply dp_ite_spec <;> intro hnc
          · have hnc' : 0 < nc3.val := (UScalar.lt_equiv _ _).mp hnc
            refine d3_sub (b := 1) rfl rfl hnc' ?_; intro i28 _
            refine d3_rem (b := 16) rfl (by decide) ?_; intro i29 hi29
            refine d3_idx (c := 16) rfl hi29 ?_; intro top
            refine d3_rem (b := 512) rfl (by decide) ?_; intro i30 hi30
            refine d3_shr (n := 9) (by decide) rfl ?_; intro i32 _
            refine d3_bind (dsym_spec _ _) ?_; intro i33 _
            refine d3_rem (b := 32) rfl (by decide) ?_; intro i34 hi34
            refine d3_idx (c := 32) rfl hi34 ?_; intro cdc3
            have hsat := dp_sat_sub_val (UScalar.cast .Usize i30) 1#usize
            have hcst := d3_cast_le .Usize i30
            exact d3_ok (by
              show (core.num.Usize.saturating_sub (UScalar.cast .Usize i30) 1#usize).val < 512
              clear * - hsat hcst hi30; omega)
          · exact d3_ok (by decide : 0 < 512)
        rintro ⟨cl2, cd2, cdc2⟩ hcl2
        have hcl2 : cl2.val < 512 := hcl2
        iterate 2 refine d3_unc ?_

        refine d3_bind (Q := fun (x : alloc.vec.Vec Std.U32 × Array Std.U32 16384#usize ×
              Array Std.U32 65536#usize × Array Std.U32 32768#usize × Array Std.U32 65536#usize ×
              Array Std.U32 32768#usize × Array Std.U64 8192#usize × Array Std.U32 8192#usize ×
              Array Std.U32 320#usize × Array Std.U32 32#usize × Std.Usize × Std.Usize × Std.Usize × Bool) =>
            match x with
            | (_, g3, g4, _, g7, _, _, _, _, _, s1, cl1, i12, _) =>
              s1.val ≤ i12.val ∧ i'.val < i12.val ∧ i12.val ≤ n.val ∧ cl1.val < 512 ∧
              LeAll g3.val i12.val ∧ LeAll g4.val i12.val ∧ LeAll g7.val i12.val) ?_ ?_
        · apply dp_ite2_spec
          · intro _ hnc
            have hnc' : 0 < nc3.val := (UScalar.lt_equiv _ _).mp hnc
            refine d3_sub (b := 1) rfl rfl hnc' ?_; intro i31 _
            refine d3_rem (b := 16) rfl (by decide) ?_; intro i32 hi32
            refine d3_idx (c := 16) rfl hi32 ?_; intro c0
            refine d3_shr (n := 9) (by decide) rfl ?_; intro i33 hi33
            refine d3_rem (b := 259) rfl (by decide) ?_; intro i34 hi34
            refine d3_sub (a := 258) rfl rfl (by clear * - hi34; omega) ?_; intro i35 _
            have hd0 : (UScalar.cast .Usize i33).val < 8388608 := by
              have h9 := dp_shr9 c0
              have hc := d3_cast_le .Usize i33
              clear * - h9 hc hi33; omega
            refine d3_bind (ext_back_spec _ _ _ _ _ hilt hd0 hS hs') ?_; intro t ht
            have ht' : t.val ≤ i'.val := by clear * - ht; omega
            refine d3_sub rfl rfl ht' ?_; intro st hst
            refine d3_bind (backtrack_spec _ _ _ _ _ _ _ _ _ _
              (by clear * - hst ht hs'; omega) (by clear * - hst hiM; omega)) ?_
            rintro ⟨plan2, lf2, df2, tb2⟩ _
            iterate 3 refine d3_unc ?_
            refine d3_bind (Q := fun _ => True) ?_ ?_
            · apply dp_ite_spec <;> intro hpl
              · have hpl' := (UScalar.lt_equiv _ _).mp hpl
                have hlv : plan2.len.val = plan2.val.length := alloc.vec.Vec.len_val plan2
                have hnm := d3_le_max n
                exact d3_true (alloc.vec.Vec.push_spec _ _ (by clear * - hpl' hlv hnm; omega))
              · exact d3_ok trivial
            intro plan3 _
            refine d3_add rfl rfl (by clear * - ht' hb4 hic hS; omega) ?_; intro i37 _
            refine d3_rem (b := 512) rfl (by decide) ?_; intro i38 hi38
            refine d3_idx (c := 512) rfl hi38 ?_; intro i39
            refine d3_rem (b := 32) rfl (by decide) ?_; intro ls hls'
            refine d3_add (a := 257) rfl rfl (by have := d3_max_ge; clear * - hls' this; omega) ?_; intro i41 hi41
            have hi41' : i41.val < 320 := by clear * - hi41 hls'; omega
            refine d3_idx (c := 320) rfl hi41' ?_; intro i42
            refine d3_upd (c := 320) rfl hi41' ?_; intro a9 _
            refine d3_bind (dsym_spec _ _) ?_; intro i44 _
            refine d3_rem (b := 32) rfl (by decide) ?_; intro ds hds
            refine d3_idx (c := 32) rfl hds ?_; intro i45
            refine d3_upd (c := 32) rfl hds ?_; intro a10 _
            refine d3_add rfl rfl (by clear * - hb4 hic hS; omega) ?_; intro «end» hend
            refine d3_bind (Q := fun (x : Std.Usize) => x.val ≤ «end».val ∧ x.val ≤ lim.val) ?_ ?_
            · apply dp_ite_spec <;> intro h
              · have h' : lim.val < «end».val := (UScalar.lt_equiv _ _).mp h
                exact d3_ok ⟨Nat.le_of_lt h', Nat.le_refl _⟩
              · have h' : ¬ (lim.val < «end».val) := (UScalar.lt_equiv _ _).not.mp h
                exact d3_ok ⟨Nat.le_refl _, (by clear * - h'; omega : «end».val ≤ lim.val)⟩
            rintro end1 ⟨he1, he2⟩
            have hE : i'.val ≤ «end».val := by clear * - hend; omega
            refine d3_bind (insert_range_spec _ _ _ _ _ _ _ _ _ «end».val (LeAll_mono hL3 hE) (LeAll_mono hL4 hE)
              (LeAll_mono hL7 hE) (by clear * - he1; omega) (by clear * - he2 hlim hn hS; omega)) ?_
            rintro ⟨head33, head43, prev43, head73, prev73⟩ ⟨hr3, hr4, hr7⟩
            iterate 4 refine d3_unc ?_
            refine d3_bind (open_chunk_spec _ _ (by clear * - hend hb4 hic hS; omega)) ?_; intro pa4 _
            exact d3_ok ⟨Nat.le_refl _, (by clear * - hend hb3; omega : i'.val < «end».val),
              (by clear * - hend hb4 hcap2; omega : «end».val ≤ n.val), (by decide : 0 < 512), hr3, hr4, hr7⟩
          · have h14 : i'.val < i14.val := by clear * - hi14; omega
            refine d3_bind (rc_seq_spec _ _ _ _ _ _ _ _ _ _ _ _ hilt hS) ?_; intro pa4 _
            exact d3_ok ⟨(by clear * - hs' h14; omega : s'.val ≤ i14.val), h14,
              (by clear * - hi14 hlt' hlim; omega : i14.val ≤ n.val), hcl2,
              LeAll_mono hL3 (Nat.le_of_lt h14), LeAll_mono hL4 (Nat.le_of_lt h14), LeAll_mono hL7 (Nat.le_of_lt h14)⟩
        rintro ⟨v, a, a1, a2, a3, a4, a5, a6, a7, a8, i28, i29, i30, b2⟩ ⟨hv1, hv2, hv3, hv4, hv5, hv6, hv7⟩
        iterate 13 refine d3_unc ?_
        exact d3_ok ⟨hv1, hv2, hv3, hv4, hv5, hv6, hv7⟩
    rintro ⟨plan1, head32, head42, prev42, head72, prev72, pa3, tb1, lf1, df1, s1, cands1, cl1, cd1, cdc1, i22,
      anchor1, alen1, jumped⟩ ⟨hs1, hii, hin1, hcl1, hk3, hk4, hk7⟩
    iterate 18 refine d3_unc ?_
    have hs1 : s1.val ≤ i22.val := hs1
    have hii : i'.val < i22.val := hii
    have hin1 : i22.val ≤ n.val := hin1
    have hcl1 : cl1.val < 512 := hcl1
    have hk3 : LeAll head32.val i22.val := hk3
    have hk4 : LeAll head42.val i22.val := hk4
    have hk7 : LeAll head72.val i22.val := hk7
    have hms : lim.val - i22.val < lim.val - i'.val := by clear * - hii hlt'; omega
    have h22M : i22.val + 2147483648 ≤ Std.Usize.max := by clear * - hin1 hn hS; omega

    refine d3_bind (Q := fun (x : Std.U64 × Std.Usize × Std.Usize × Std.Usize × (Std.Usize × Std.Usize × Std.Usize)) =>
        x.2.2.2.2.1.val ≤ i22.val ∧ x.2.2.2.2.2.1.val ≤ i22.val ∧ x.2.2.2.2.2.2.val ≤ i22.val) ?_ ?_
    · apply dp_ite_spec <;> intro _
      · refine d3_bind (be8_spec _ _ (by clear * - h22M; omega)) ?_; intro b82 _
        refine d3_bind (hashes_spec _ _) ?_; rintro ⟨i26, i27, i28⟩ _
        iterate 2 refine d3_unc ?_
        refine d3_bind (dp_heads_spec _ _ _ _ _ _ i22.val hk3 hk4 hk7) ?_; intro pre2 hpre2
        exact d3_ok hpre2
      · exact d3_ok ⟨Nat.le_trans hn1 (Nat.le_of_lt hii), Nat.le_trans hn2 (Nat.le_of_lt hii),
          Nat.le_trans hn3 (Nat.le_of_lt hii)⟩
    rintro ⟨b81, i23, i24, i25, pre1⟩ ⟨hp1, hp2, hp3⟩
    iterate 4 refine d3_unc ?_
    refine d3_sub rfl rfl hs1 ?_; intro i26 _

    refine d3_bind (Q := fun (x : alloc.vec.Vec Std.U32 × Array Std.U64 8192#usize × Array Std.U32 8192#usize ×
        Array Std.U32 320#usize × Array Std.U32 32#usize × Std.Usize) => x.2.2.2.2.2.val ≤ i22.val) ?_ ?_
    · apply dp_ite_spec <;> intro _
      · refine d3_bind (backtrack_spec _ _ _ _ _ _ _ _ _ _ hs1 (by clear * - h22M; omega)) ?_
        rintro ⟨plan3, lf3, df3, tb3⟩ _
        iterate 3 refine d3_unc ?_
        refine d3_bind (open_chunk_spec _ _ (by clear * - h22M; omega)) ?_; intro pa5 _
        exact d3_ok (Nat.le_refl _)
      · exact d3_ok hs1
    rintro ⟨plan2, pa4, tb2, lf2, df2, s2⟩ hs2
    have hs2 : s2.val ≤ i22.val := hs2
    iterate 5 refine d3_unc ?_

    apply dp_ite_spec <;> intro _
    · refine d3_add rfl rfl (by clear * - h22M hupd; omega) ?_; intro next_upd1 _
      refine d3_bind (update_costs_h_spec _ _ _ _ _ _ _ _ hls) ?_
      rintro ⟨lf3, df3, litc1, lc1, dcc1⟩ _
      iterate 4 refine d3_unc ?_
      refine d3_bind (dsym_spec _ _) ?_; intro i27 _
      refine d3_rem (b := 32) rfl (by decide) ?_; intro i28 hi28
      refine d3_idx (c := 32) rfl hi28 ?_; intro cdc2
      exact d3_ok ⟨⟨hs2, hin1, hcl1, hk3, hk4, hk7, hp1, hp2, hp3⟩, hms⟩
    · exact d3_ok ⟨⟨hs2, hin1, hcl1, hk3, hk4, hk7, hp1, hp2, hp3⟩, hms⟩
  · exact ⟨hsi, hin, hcl, h3, h4, h7, hc3, hc4, hc7⟩

attribute [local step] dp_parse_loop_spec

@[local step] theorem dp_parse_spec (input : Slice Std.U8) (plan) (ct lazyn d4 d7 skip h3d huff kb7 upd half tmax : Std.Usize)
    (h16 : 16 ≤ input.length) (hN : input.length + input.length ≤ Std.Usize.max) :
    slot.dp_parse input plan ct lazyn d4 d7 skip h3d huff kb7 upd half tmax ⦃ fun _ => True ⦄ := by
  have hS := dp_size hN
  have z8 : LeAll (Array.repeat 512#usize 0#u8).val 28 := dp_LeAll_repeat _ _ _ (by simp)
  have z3 : LeAll (Array.repeat 16384#usize 0#u32).val (0#usize).val := dp_LeAll_repeat _ _ _ (by simp)
  have z4 : LeAll (Array.repeat 65536#usize 0#u32).val (0#usize).val := dp_LeAll_repeat _ _ _ (by simp)
  rw [slot.dp_parse]
  step*
  split <;> step*
  all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))

@[local step]
theorem d_push32_spec (v x)  :
    slot.d_push32 v x ⦃ fun r => True ⦄ := by
  rw [slot.d_push32]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

@[local step]
theorem d_byte_spec (s i)  :
    slot.d_byte s i ⦃ fun r => True ⦄ := by
  rw [slot.d_byte]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

@[local step]
theorem d_cell_spec (ring i)  :
    slot.d_cell ring i ⦃ fun r => True ⦄ := by
  rw [slot.d_cell]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

@[local step]
theorem d_min_spec (a b)  :
    slot.d_min a b ⦃ fun r => r.val ≤ a.val ∧ r.val ≤ b.val ⦄ := by
  rw [slot.d_min]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

theorem d1_ok {α : Type} {x : α} {P : α → Prop} (h : P x) : WP.spec (ok x) P :=
  (WP.spec_ok x).2 h

theorem d1_ite {α : Type} {c : Prop} {inst : Decidable c} {X Y : Result α} {P : α → Prop}
    (hX : c → WP.spec X P) (hY : ¬c → WP.spec Y P) : WP.spec (@ite _ c inst X Y) P := by
  by_cases h : c
  · rw [if_pos h]; exact hX h
  · rw [if_neg h]; exact hY h

theorem d1_ite_ok {α : Type} (c : Prop) [Decidable c] (a b : α) :
    (if c then (ok a : Result α) else ok b) = ok (if c then a else b) := by split <;> rfl

theorem d1_bind {α β : Type} {m : Result α} {Q : α → Prop} {k : α → Result β} {P : β → Prop}
    (hm : WP.spec m Q) (hk : ∀ x, Q x → WP.spec (k x) P) : WP.spec (Bind.bind m k) P :=
  WP.spec_bind hm hk

theorem d1_tot {α β : Type} {m : Result α} {Q : α → Prop} {k : α → Result β} {P : β → Prop}
    (hm : WP.spec m Q) (hk : ∀ x, WP.spec (k x) P) : WP.spec (Bind.bind m k) P :=
  WP.spec_bind hm (fun x _ => hk x)

theorem d1_true {α : Type} {m : Result α} {Q : α → Prop} (h : WP.spec m Q) : WP.spec m (fun _ => True) :=
  WP.spec_mono h (fun _ _ => trivial)

theorem d1_add {ty : UScalarTy} {β : Type} {x y : UScalar ty} {k : UScalar ty → Result β} {P : β → Prop}
    (w : UScalar ty) (h : x.val + y.val ≤ w.val) (hk : ∀ z : UScalar ty, z.val = x.val + y.val → WP.spec (k z) P) :
    WP.spec (Bind.bind (HAdd.hAdd x y : Result (UScalar ty)) k) P :=
  WP.spec_bind (UScalar.add_spec (Nat.le_trans h (ScalarTac.UScalar.bounds w))) hk

theorem d1_add' {ty : UScalarTy} {x y : UScalar ty} (w : UScalar ty) (h : x.val + y.val ≤ w.val) :
    WP.spec (HAdd.hAdd x y : Result (UScalar ty)) (fun _ => True) :=
  d1_true (UScalar.add_spec (Nat.le_trans h (ScalarTac.UScalar.bounds w)))

theorem d1_sub {ty : UScalarTy} {β : Type} {x y : UScalar ty} {k : UScalar ty → Result β} {P : β → Prop}
    (h : y.val ≤ x.val) (hk : ∀ z : UScalar ty, z.val + y.val = x.val → WP.spec (k z) P) :
    WP.spec (Bind.bind (HSub.hSub x y : Result (UScalar ty)) k) P :=
  WP.spec_bind (UScalar.sub_spec h) (fun z hz => hk z ((congrArg (· + y.val) hz.1).trans (Nat.sub_add_cancel h)))

theorem d1_rem {ty : UScalarTy} {β : Type} {x y : UScalar ty} {k : UScalar ty → Result β} {P : β → Prop}
    (h : 0 < y.val) (hk : ∀ z : UScalar ty, z.val < y.val → WP.spec (k z) P) :
    WP.spec (Bind.bind (HMod.hMod x y : Result (UScalar ty)) k) P :=
  WP.spec_bind (UScalar.rem_spec x (Nat.pos_iff_ne_zero.mp h)) (fun z hz => hk z (hz ▸ Nat.mod_lt _ h))

theorem d1_div {β : Type} {x y : Std.Usize} {k : Std.Usize → Result β} {P : β → Prop}
    (h : y.val ≠ 0) (hk : ∀ z : Std.Usize, WP.spec (k z) P) :
    WP.spec (Bind.bind (HDiv.hDiv x y : Result Std.Usize) k) P :=
  WP.spec_bind (Usize.div_spec x h) (fun z _ => hk z)

theorem d1_shr {ty ty1 : UScalarTy} {β : Type} {x : UScalar ty} {y : UScalar ty1} {k : UScalar ty → Result β}
    {P : β → Prop} (h : y.val < ty.numBits) (hk : ∀ z : UScalar ty, WP.spec (k z) P) :
    WP.spec (Bind.bind (HShiftRight.hShiftRight x y : Result (UScalar ty)) k) P :=
  WP.spec_bind (UScalar.ShiftRight_spec x y h) (fun z _ => hk z)

theorem d1_shl {ty ty1 : UScalarTy} {β : Type} {x : UScalar ty} {y : UScalar ty1} {k : UScalar ty → Result β}
    {P : β → Prop} (h : y.val < ty.numBits) (hk : ∀ z : UScalar ty, WP.spec (k z) P) :
    WP.spec (Bind.bind (HShiftLeft.hShiftLeft x y : Result (UScalar ty)) k) P :=
  WP.spec_bind (UScalar.ShiftLeft_spec x y _ h rfl) (fun z _ => hk z)

theorem d1_shri {ty : UScalarTy} {ty1 : IScalarTy} {β : Type} {x : UScalar ty} {y : IScalar ty1}
    {k : UScalar ty → Result β} {P : β → Prop} (h0 : 0 ≤ y.val) (h : y.val < ty.numBits)
    (hk : ∀ z : UScalar ty, WP.spec (k z) P) :
    WP.spec (Bind.bind (HShiftRight.hShiftRight x y : Result (UScalar ty)) k) P :=
  WP.spec_bind (UScalar.ShiftRight_IScalar_spec x y h0 h) (fun z _ => hk z)

theorem d1_idx {α β : Type} {n : Std.Usize} {a : Std.Array α n} {i : Std.Usize} {k : α → Result β} {P : β → Prop}
    (h : i.val < n.val) (hk : ∀ x, WP.spec (k x) P) : WP.spec (Bind.bind (Array.index_usize a i) k) P :=
  WP.spec_bind (Array.index_usize_spec a i (Nat.lt_of_lt_of_eq h a.property.symm)) (fun x _ => hk x)

theorem d1_upd {α β : Type} {n : Std.Usize} {a : Std.Array α n} {i : Std.Usize} {v : α}
    {k : Std.Array α n → Result β} {P : β → Prop} (h : i.val < n.val) (hk : ∀ x, WP.spec (k x) P) :
    WP.spec (Bind.bind (Array.update a i v) k) P :=
  WP.spec_bind (Array.update_spec a i v (Nat.lt_of_lt_of_eq h a.property.symm)) (fun x _ => hk x)

theorem d1_sidx {α β : Type} {s : Slice α} {i : Std.Usize} {k : α → Result β} {P : β → Prop}
    (h : i.val < (Slice.len s).val) (hk : ∀ x, WP.spec (k x) P) :
    WP.spec (Bind.bind (Slice.index_usize s i) k) P :=
  WP.spec_bind (Slice.index_usize_spec s i h) (fun x _ => hk x)

theorem d1_u8 (b : Std.U8) : (UScalar.cast .Usize b).val < (288#usize).val := by
  rw [U8.cast_Usize_val_eq]; exact Nat.lt_of_le_of_lt (U8.le_max b) (by decide)

theorem d1_c32 (l : Std.U8) {n : Nat} (h : l.val < n + 1) : (UScalar.cast .U32 l).val ≤ n := by
  rw [U8.cast_U32_val_eq]; exact Nat.le_of_lt_succ h

theorem d1_pos {n : Nat} : 0 < n + 1 := Nat.zero_lt_succ n

theorem d1_pred {a b : Nat} (h : a + 1 = b) : a < b := h ▸ Nat.lt_succ_self a
theorem d1_msub {e l l1 : Nat} (h : l < e) (h1 : l1 = l + 1) : e - l1 < e - l :=
  h1 ▸ Nat.sub_succ_lt_self e l h
theorem d1_msubd {e l d l1 : Nat} (h : l < e) (hd : 0 < d) (h1 : l1 = l + d) : e - l1 < e - l :=
  h1 ▸ Nat.sub_lt_sub_left h (Nat.lt_add_of_pos_right hd)

theorem d1_fit {a b c n : Nat} (h : b ≤ c) (hc : c + a = n) : a + b ≤ n :=
  Nat.le_trans (Nat.add_le_add_left h a) (Nat.le_of_eq ((Nat.add_comm a c).trans hc))

@[local step]
theorem d_take_spec (w a b ns nx) :
    slot.d_take w a b ns nx ⦃ fun _ => True ⦄ := by
  simp only [slot.d_take, lift, bind_tc_ok]
  refine d1_ite (fun ha => ?_) (fun _ => d1_ok trivial)
  refine d1_ite (fun _ => ?_) (fun _ => ?_)
  · exact d1_add ns (Nat.succ_le_of_lt ha) fun _ _ => d1_ok trivial
  · refine d1_rem d1_pos fun i hi => ?_
    refine d1_idx hi fun i1 => ?_
    refine d1_rem d1_pos fun i2 hi2 => ?_
    refine d1_idx hi2 fun i3 => ?_
    exact d1_ite (fun _ => d1_add ns (Nat.succ_le_of_lt ha) fun _ _ => d1_ok trivial) (fun _ => d1_ok trivial)

@[local step]
theorem d_clamp_len_spec (d) :
    slot.d_clamp_len d ⦃ fun _ => True ⦄ := by
  rw [slot.d_clamp_len]
  exact d1_ite (fun _ => d1_ok trivial) (fun _ => d1_ite (fun _ => d1_ok trivial) (fun _ => d1_ok trivial))

@[local step]
theorem d_huff_loop0_loop0_spec (freq sym f j) :
    slot.d_huff_loop0_loop0 freq sym f j ⦃ fun _ => True ⦄ := by
  rw [slot.d_huff_loop0_loop0]
  apply Std.loop.spec_decr_nat (measure := fun x => x.2.val) (inv := fun _ => True)
  · rintro ⟨sym', j'⟩ _
    simp only [slot.d_huff_loop0_loop0.body, lift, bind_tc_ok]
    refine d1_ite (fun hj => ?_) (fun _ => d1_ok trivial)
    refine d1_sub (Nat.succ_le_of_lt hj) fun i hi => ?_
    refine d1_rem d1_pos fun i1 hi1 => ?_
    refine d1_idx hi1 fun i2 => ?_
    refine d1_rem d1_pos fun i4 hi4 => ?_
    refine d1_idx hi4 fun i5 => ?_
    refine d1_ite (fun _ => ?_) (fun _ => d1_ok trivial)
    refine d1_rem d1_pos fun i6 hi6 => ?_
    refine d1_idx hi6 fun i7 => ?_
    refine d1_rem d1_pos fun i8 hi8 => ?_
    refine d1_upd hi8 fun a => ?_
    exact d1_ok ⟨trivial, d1_pred hi⟩
  · trivial

@[local step]
theorem d_huff_loop0_spec (freq m len sym ns i) :
    slot.d_huff_loop0 freq m len sym ns i ⦃ fun _ => True ⦄ := by
  rw [slot.d_huff_loop0]
  apply Std.loop.spec_decr_nat (measure := fun x => 288 - x.2.2.2.val) (inv := fun _ => True)
  · rintro ⟨len', sym', ns', i'⟩ _
    simp only [slot.d_huff_loop0.body, lift, bind_tc_ok]
    refine d1_ite (fun _ => ?_) (fun _ => d1_ok trivial)
    refine d1_ite (fun hi => ?_) (fun _ => d1_ok trivial)
    refine d1_idx hi fun f => ?_
    refine d1_ite (fun _ => ?_) (fun _ => ?_)
    · refine d1_tot (d_huff_loop0_loop0_spec _ _ _ _) fun ⟨sym1, j⟩ => ?_
      refine d1_rem d1_pos fun i1 hi1 => ?_
      refine d1_upd hi1 fun a => ?_
      refine d1_upd hi fun a1 => ?_
      refine d1_add 288#usize (Nat.succ_le_of_lt hi) fun i3 hi3 => ?_
      exact d1_ok ⟨trivial, d1_msub hi hi3⟩
    · refine d1_upd hi fun a => ?_
      refine d1_add 288#usize (Nat.succ_le_of_lt hi) fun i1 hi1 => ?_
      exact d1_ok ⟨trivial, d1_msub hi hi1⟩
  · trivial

@[local step]
theorem d_huff_loop1_spec (freq sym ns w k) :
    slot.d_huff_loop1 freq sym ns w k ⦃ fun _ => True ⦄ := by
  rw [slot.d_huff_loop1]
  apply Std.loop.spec_decr_nat (measure := fun x => ns.val - x.2.val) (inv := fun _ => True)
  · rintro ⟨w', k'⟩ _
    simp only [slot.d_huff_loop1.body, lift, bind_tc_ok]
    refine d1_ite (fun hk => ?_) (fun _ => d1_ok trivial)
    refine d1_rem d1_pos fun i hi => ?_
    refine d1_idx hi fun i1 => ?_
    refine d1_rem d1_pos fun i3 hi3 => ?_
    refine d1_idx hi3 fun i4 => ?_
    refine d1_rem d1_pos fun i5 hi5 => ?_
    refine d1_upd hi5 fun a => ?_
    refine d1_add ns (Nat.succ_le_of_lt hk) fun k1 hk1 => ?_
    exact d1_ok ⟨trivial, d1_msub hk hk1⟩
  · trivial

@[local step]
theorem d_huff_loop2_spec (ns w par a b nx) :
    slot.d_huff_loop2 ns w par a b nx ⦃ fun _ => True ⦄ := by
  rw [slot.d_huff_loop2]
  apply Std.loop.spec_decr_nat (measure := fun x => 575 - x.2.2.2.2.val) (inv := fun _ => True)
  · rintro ⟨w', par', a', b', nx'⟩ _
    simp only [slot.d_huff_loop2.body, lift, bind_tc_ok]
    refine d1_ite (fun hn => ?_) (fun _ => d1_ok trivial)
    refine d1_add 575#usize (Nat.succ_le_of_lt hn) fun i hi => ?_
    refine d1_div (by decide) fun i1 => ?_
    refine d1_ite (fun _ => ?_) (fun _ => d1_ok trivial)
    refine d1_tot (d_take_spec _ _ _ _ _) fun ⟨x, a1, b1⟩ => ?_
    refine d1_tot (d_take_spec _ _ _ _ _) fun ⟨y, a2, b2⟩ => ?_
    refine d1_rem d1_pos fun i2 hi2 => ?_
    refine d1_idx hi2 fun i3 => ?_
    refine d1_rem d1_pos fun i4 hi4 => ?_
    refine d1_idx hi4 fun i5 => ?_
    refine d1_rem d1_pos fun i7 hi7 => ?_
    refine d1_upd hi7 fun a3 => ?_
    refine d1_upd hi2 fun par1 => ?_
    refine d1_upd hi4 fun a4 => ?_
    exact d1_ok ⟨trivial, d1_msub hn hi⟩
  · trivial

@[local step]
theorem d_huff_loop3_spec (par depth q) :
    slot.d_huff_loop3 par depth q ⦃ fun _ => True ⦄ := by
  rw [slot.d_huff_loop3]
  apply Std.loop.spec_decr_nat (measure := fun x => x.2.val) (inv := fun _ => True)
  · rintro ⟨depth', q'⟩ _
    simp only [slot.d_huff_loop3.body, lift, bind_tc_ok]
    refine d1_ite (fun hq => ?_) (fun _ => d1_ok trivial)
    refine d1_sub (Nat.succ_le_of_lt hq) fun q1 hq1 => ?_
    refine d1_rem d1_pos fun i hi => ?_
    refine d1_idx hi fun i1 => ?_
    refine d1_rem d1_pos fun i3 hi3 => ?_
    refine d1_idx hi3 fun i4 => ?_
    refine d1_upd hi fun a => ?_
    exact d1_ok ⟨trivial, d1_pred hq1⟩
  · trivial

@[local step]
theorem d_huff_loop4_spec (len sym ns k depth mx kraft) :
    slot.d_huff_loop4 len sym ns k depth mx kraft ⦃ fun _ => True ⦄ := by
  rw [slot.d_huff_loop4]
  apply Std.loop.spec_decr_nat (measure := fun x => ns.val - x.2.1.val) (inv := fun _ => True)
  · rintro ⟨len', k', mx', kraft'⟩ _
    simp only [slot.d_huff_loop4.body, d1_ite_ok, lift, bind_tc_ok]
    refine d1_ite (fun hk => ?_) (fun _ => d1_ok trivial)
    refine d1_rem d1_pos fun i hi => ?_
    refine d1_idx hi fun i1 => ?_
    refine d1_tot (d_clamp_len_spec _) fun l => ?_
    refine d1_rem d1_pos fun i2 hi2 => ?_
    refine d1_shr (Nat.lt_trans hi2 (by decide)) fun i3 => ?_
    refine d1_rem d1_pos fun i4 hi4 => ?_
    refine d1_idx hi4 fun i5 => ?_
    refine d1_rem d1_pos fun i7 hi7 => ?_
    refine d1_upd hi7 fun a => ?_
    refine d1_add ns (Nat.succ_le_of_lt hk) fun k1 hk1 => ?_
    exact d1_ok ⟨trivial, d1_msub hk hk1⟩
  · trivial

@[local step]
theorem d_huff_loop5_spec (len sym ns mx kraft r fuel) :
    slot.d_huff_loop5 len sym ns mx kraft r fuel ⦃ fun _ => True ⦄ := by
  rw [slot.d_huff_loop5]
  apply Std.loop.spec_decr_nat (measure := fun x => x.2.2.2.2.val) (inv := fun _ => True)
  · rintro ⟨len', mx', kraft', r', fuel'⟩ _
    simp only [slot.d_huff_loop5.body, lift, bind_tc_ok]
    refine d1_ite (fun _ => ?_) (fun _ => d1_ok trivial)
    refine d1_ite (fun hr => ?_) (fun _ => d1_ok trivial)
    refine d1_ite (fun hf => ?_) (fun _ => d1_ok trivial)
    refine d1_sub (Nat.succ_le_of_lt hf) fun fuel1 hf1 => ?_
    refine d1_rem d1_pos fun i hi => ?_
    refine d1_idx hi fun i1 => ?_
    refine d1_rem d1_pos fun s2 hs2 => ?_
    refine d1_idx hs2 fun l => ?_
    refine d1_ite (fun hl => ?_) (fun _ => ?_)
    · have hc := d1_c32 l (n := 14) hl
      refine d1_sub hc fun i4 hi4 => ?_
      refine d1_shl (Nat.lt_of_le_of_lt (Nat.le_of_add_right_le (Nat.le_of_eq hi4)) (by decide)) fun i5 => ?_
      refine d1_add 15#u32 (Nat.succ_le_succ hc) fun i7 _ => ?_
      refine d1_tot (Q := fun _ => True)
        (d1_ite (fun _ => d1_add' 15#u32 (Nat.succ_le_succ hc)) (fun _ => d1_ok trivial)) fun mx1 => ?_
      refine d1_add 15#u8 (Nat.succ_le_of_lt hl) fun i8 _ => ?_
      refine d1_upd hs2 fun a => ?_
      exact d1_ok ⟨trivial, d1_pred hf1⟩
    · refine d1_add ns (Nat.succ_le_of_lt hr) fun r1 _ => ?_
      exact d1_ok ⟨trivial, d1_pred hf1⟩
  · trivial

@[local step]
theorem d_huff_spec (freq m len) :
    slot.d_huff freq m len ⦃ fun _ => True ⦄ := by
  simp only [slot.d_huff, lift, bind_tc_ok]
  refine d1_tot (d_huff_loop0_spec _ _ _ _ _ _) fun ⟨len1, sym1, ns⟩ => ?_
  refine d1_ite (fun _ => d1_ok trivial) (fun _ => ?_)
  refine d1_ite (fun _ => ?_) (fun _ => ?_)
  · refine d1_idx (by decide) fun i => ?_
    refine d1_rem d1_pos fun i2 hi2 => ?_
    exact d1_upd hi2 fun _ => d1_ok trivial
  · refine d1_tot (d_huff_loop1_spec _ _ _ _ _) fun w1 => ?_
    refine d1_tot (d_huff_loop2_spec _ _ _ _ _ _) fun ⟨par1, nx⟩ => ?_
    refine d1_tot (d_huff_loop3_spec _ _ _) fun depth1 => ?_
    refine d1_tot (d_huff_loop4_spec _ _ _ _ _ _ _) fun ⟨len2, mx, kraft⟩ => ?_
    exact d_huff_loop5_spec _ _ _ _ _ _ _

@[local step]
theorem d_ecost_spec (f lt) :
    slot.d_ecost f lt ⦃ fun _ => True ⦄ := by
  rw [slot.d_ecost]
  refine d1_tot (Q := fun _ => True)
    (d1_ite (fun _ => d1_ok trivial) (fun _ => d1_tot (log2_16_spec _) fun _ => d1_ok trivial)) fun e => ?_
  exact d1_ite (fun _ => d1_ok trivial) (fun _ => d1_ite (fun _ => d1_ok trivial) (fun _ => d1_ok trivial))

@[local step]
theorem d_mix_spec (h e ck) :
    slot.d_mix h e ck ⦃ fun _ => True ⦄ := by
  simp only [slot.d_mix, d1_ite_ok, lift, bind_tc_ok]
  refine d1_ite (fun _ => d1_ok trivial) (fun _ => ?_)
  refine d1_ite (fun _ => d1_ok trivial) (fun _ => ?_)
  refine d1_ite (fun _ => d1_true (U32.div_spec _ (by decide))) (fun _ => ?_)
  refine d1_ite (fun hgt => ?_) (fun hle => ?_)
  · exact d1_sub (Nat.le_of_lt hgt) fun _ _ => d1_ok trivial
  · exact d1_sub (Nat.le_of_not_lt hle) fun _ _ => d1_ok trivial

@[local step]
theorem d_sym_costs_loop0_spec (freq m total i) :
    slot.d_sym_costs_loop0 freq m total i ⦃ fun _ => True ⦄ := by
  rw [slot.d_sym_costs_loop0]
  apply Std.loop.spec_decr_nat (measure := fun x => 288 - x.2.val) (inv := fun _ => True)
  · rintro ⟨total', i'⟩ _
    simp only [slot.d_sym_costs_loop0.body, lift, bind_tc_ok]
    refine d1_ite (fun _ => ?_) (fun _ => d1_ok trivial)
    refine d1_ite (fun hi => ?_) (fun _ => d1_ok trivial)
    refine d1_idx hi fun i1 => ?_
    refine d1_add 288#usize (Nat.succ_le_of_lt hi) fun i2 hi2 => ?_
    exact d1_ok ⟨trivial, d1_msub hi hi2⟩
  · trivial

@[local step]
theorem d_sym_costs_loop1_spec (freq m hl unseen ck out i lt) :
    slot.d_sym_costs_loop1 freq m hl unseen ck out i lt ⦃ fun _ => True ⦄ := by
  rw [slot.d_sym_costs_loop1]
  apply Std.loop.spec_decr_nat (measure := fun x => 288 - x.2.val) (inv := fun _ => True)
  · rintro ⟨out', i'⟩ _
    simp only [slot.d_sym_costs_loop1.body, d1_ite_ok, lift, bind_tc_ok]
    refine d1_ite (fun _ => ?_) (fun _ => d1_ok trivial)
    refine d1_ite (fun hi => ?_) (fun _ => d1_ok trivial)
    refine d1_idx hi fun i1 => ?_
    refine d1_idx hi fun i2 => ?_
    refine d1_tot (d_ecost_spec _ _) fun e => ?_
    refine d1_tot (d_mix_spec _ _ _) fun i4 => ?_
    refine d1_upd hi fun a => ?_
    refine d1_add 288#usize (Nat.succ_le_of_lt hi) fun i5 hi5 => ?_
    exact d1_ok ⟨trivial, d1_msub hi hi5⟩
  · trivial

@[local step]
theorem d_sym_costs_spec (freq m hl unseen ck out) :
    slot.d_sym_costs freq m hl unseen ck out ⦃ fun _ => True ⦄ := by
  simp only [slot.d_sym_costs, lift, bind_tc_ok]
  refine d1_tot (d_sym_costs_loop0_spec _ _ _ _) fun total => ?_
  refine d1_tot (log2_16_spec _) fun lt => ?_
  exact d_sym_costs_loop1_spec _ _ _ _ _ _ _ _

@[local step]
theorem d_unseen_spec (mx) :
    slot.d_unseen mx ⦃ fun _ => True ⦄ := by
  rw [slot.d_unseen]
  exact d1_ite (fun h => d1_add' 15#u32 (Nat.succ_le_of_lt h)) (fun _ => d1_ok trivial)

@[local step]
theorem d_push_table_loop0_spec (tabs lcst i) :
    slot.d_push_table_loop0 tabs lcst i ⦃ fun _ => True ⦄ := by
  rw [slot.d_push_table_loop0]
  apply Std.loop.spec_decr_nat (measure := fun x => 256 - x.2.val) (inv := fun _ => True)
  · rintro ⟨tabs', i'⟩ _
    simp only [slot.d_push_table_loop0.body]
    refine d1_ite (fun hi => ?_) (fun _ => d1_ok trivial)
    refine d1_idx (Nat.lt_trans hi (by decide)) fun i1 => ?_
    refine d1_tot (d_push32_spec _ _) fun tabs1 => ?_
    refine d1_add 256#usize (Nat.succ_le_of_lt hi) fun i2 hi2 => ?_
    exact d1_ok ⟨trivial, d1_msub hi hi2⟩
  · trivial

@[local step]
theorem d_push_table_loop1_spec (tabs lsym lcst l) :
    slot.d_push_table_loop1 tabs lsym lcst l ⦃ fun _ => True ⦄ := by
  rw [slot.d_push_table_loop1]
  apply Std.loop.spec_decr_nat (measure := fun x => 264 - x.2.val) (inv := fun _ => True)
  · rintro ⟨tabs', l'⟩ _
    simp only [slot.d_push_table_loop1.body, lift, bind_tc_ok]
    refine d1_ite (fun hl => ?_) (fun _ => d1_ok trivial)
    refine d1_rem d1_pos fun i hi => ?_
    refine d1_idx hi fun i1 => ?_
    refine d1_rem d1_pos fun c hc => ?_
    refine d1_tot (Q := fun _ => True) ?_ fun x => ?_
    · refine d1_ite (fun _ => d1_ok trivial) (fun _ => d1_ite (fun _ => d1_ok trivial) (fun _ => ?_))
      refine d1_add 288#usize (Nat.add_le_add_left (Nat.le_of_lt_succ hc) 257) fun i3 _ => ?_
      refine d1_rem d1_pos fun i4 hi4 => ?_
      refine d1_idx hi4 fun i5 => ?_
      exact d1_idx hc fun _ => d1_ok trivial
    refine d1_tot (d_push32_spec _ _) fun tabs1 => ?_
    refine d1_add 264#usize (Nat.succ_le_of_lt hl) fun l1 hl1 => ?_
    exact d1_ok ⟨trivial, d1_msub hl hl1⟩
  · trivial

@[local step]
theorem d_push_table_loop2_spec (tabs dcst i) :
    slot.d_push_table_loop2 tabs dcst i ⦃ fun _ => True ⦄ := by
  rw [slot.d_push_table_loop2]
  apply Std.loop.spec_decr_nat (measure := fun x => 40 - x.2.val) (inv := fun _ => True)
  · rintro ⟨tabs', i'⟩ _
    simp only [slot.d_push_table_loop2.body, lift, bind_tc_ok]
    refine d1_ite (fun hi => ?_) (fun _ => d1_ok trivial)
    refine d1_tot (Q := fun _ => True) ?_ fun x => ?_
    · refine d1_ite (fun h30 => ?_) (fun _ => d1_ok trivial)
      refine d1_idx (Nat.lt_trans h30 (by decide)) fun i1 => ?_
      refine d1_rem d1_pos fun i2 hi2 => ?_
      exact d1_idx hi2 fun _ => d1_ok trivial
    refine d1_tot (d_push32_spec _ _) fun tabs1 => ?_
    refine d1_add 40#usize (Nat.succ_le_of_lt hi) fun i1 hi1 => ?_
    exact d1_ok ⟨trivial, d1_msub hi hi1⟩
  · trivial

@[local step]
theorem d_push_table_spec (tabs lf df lsym ck) :
    slot.d_push_table tabs lf df lsym ck ⦃ fun _ => True ⦄ := by
  simp only [slot.d_push_table]
  refine d1_tot (d_huff_spec _ _ _) fun ⟨mxl, ll1⟩ => ?_
  refine d1_tot (d_huff_spec _ _ _) fun ⟨mxd, dl1⟩ => ?_
  refine d1_tot (d_unseen_spec _) fun i => ?_
  refine d1_tot (d_sym_costs_spec _ _ _ _ _ _) fun lcst1 => ?_
  refine d1_tot (d_unseen_spec _) fun i1 => ?_
  refine d1_tot (d_sym_costs_spec _ _ _ _ _ _) fun dcst1 => ?_
  refine d1_tot (d_push_table_loop0_spec _ _ _) fun tabs1 => ?_
  refine d1_tot (d_push_table_loop1_spec _ _ _ _) fun tabs2 => ?_
  exact d_push_table_loop2_spec _ _ _

@[local step]
theorem d_block_end_spec (tabs bstart lf df lsym ck p t) :
    slot.d_block_end tabs bstart lf df lsym ck p t ⦃ fun _ => True ⦄ := by
  simp only [slot.d_block_end, lift, bind_tc_ok]
  refine d1_ite (fun _ => d1_ok trivial) (fun _ => ?_)
  refine d1_upd (by decide) fun lf1 => ?_
  refine d1_tot (d_push_table_spec _ _ _ _ _) fun tabs1 => ?_
  exact d1_tot (d_push32_spec _ _) fun _ => d1_ok trivial

@[local step]
theorem d_tally_loop_spec (s plan lsym dtab tabs bstart ck lf df p t k) :
    slot.d_tally_loop s plan lsym dtab tabs bstart ck lf df p t k ⦃ fun _ => True ⦄ := by
  rw [slot.d_tally_loop]
  apply Std.loop.spec_decr_nat (measure := fun x => (Slice.len s).val - x.2.2.2.2.1.val) (inv := fun _ => True)
  · rintro ⟨tabs', bstart', lf', df', p', t', k'⟩ _
    simp only [slot.d_tally_loop.body, lift, bind_tc_ok]
    refine d1_ite (fun hp => ?_) (fun _ => d1_ok trivial)
    refine d1_tot (d_block_end_spec _ _ _ _ _ _ _ _) fun ⟨t1, tabs1, bstart1, lf1, df1⟩ => ?_
    refine d1_tot (get0_spec _ _) fun v => ?_
    refine d1_rem d1_pos fun i1 _ => ?_

    refine d1_bind (Q := fun r => (Slice.len s).val - r.2.2.2.2.val < (Slice.len s).val - p'.val) ?_
      fun ⟨tabs2, bstart2, lf2, df2, p1⟩ hq => d1_ok ⟨trivial, hq⟩
    refine d1_ite (fun h3 => ?_) (fun _ => ?_)
    · refine d1_sub (Nat.le_of_lt hp) fun i3 hi3 => ?_
      refine d1_bind (Q := fun r => (Slice.len s).val - r.2.2.val < (Slice.len s).val - p'.val) ?_
        fun ⟨a, a1, i4⟩ hq => d1_ok hq
      refine d1_ite (fun hle => ?_) (fun _ => ?_)
      ·
        refine d1_rem d1_pos fun i5 hi5 => ?_
        refine d1_idx hi5 fun i6 => ?_
        refine d1_rem d1_pos fun c hc => ?_
        refine d1_add 288#usize (Nat.add_le_add_left (Nat.le_of_lt_succ hc) 257) fun i8 _ => ?_
        refine d1_rem d1_pos fun i9 hi9 => ?_
        refine d1_idx hi9 fun i10 => ?_
        refine d1_rem d1_pos fun i12 hi12 => ?_
        refine d1_upd hi12 fun a2 => ?_
        refine d1_shri (by decide) (by decide) fun i13 => ?_
        refine d1_tot (dsym_spec _ _) fun i15 => ?_
        refine d1_rem d1_pos fun dc hdc => ?_
        refine d1_idx (Nat.lt_trans hdc (by decide)) fun i16 => ?_
        refine d1_upd (Nat.lt_trans hdc (by decide)) fun a3 => ?_
        refine d1_add (Slice.len s) (d1_fit hle hi3) fun p2 hp2 => ?_
        exact d1_ok (d1_msubd hp (Nat.lt_of_lt_of_le (by decide) h3) hp2)
      ·
        refine d1_sidx hp fun i5 => ?_
        refine d1_idx (d1_u8 i5) fun i7 => ?_
        refine d1_upd (d1_u8 i5) fun a2 => ?_
        refine d1_add (Slice.len s) (Nat.succ_le_of_lt hp) fun p2 hp2 => ?_
        exact d1_ok (d1_msub hp hp2)
    ·
      refine d1_sidx hp fun i2 => ?_
      refine d1_idx (d1_u8 i2) fun i4 => ?_
      refine d1_upd (d1_u8 i2) fun a => ?_
      refine d1_add (Slice.len s) (Nat.succ_le_of_lt hp) fun p2 hp2 => ?_
      exact d1_ok (d1_msub hp hp2)
  · trivial

@[local step]
theorem d_tally_spec (s plan lsym dtab tabs bstart ck) :
    slot.d_tally s plan lsym dtab tabs bstart ck ⦃ fun _ => True ⦄ := by
  simp only [slot.d_tally]
  refine d1_tot (d_push32_spec _ _) fun bstart1 => ?_
  refine d1_tot (d_tally_loop_spec _ _ _ _ _ _ _ _ _ _ _ _) fun ⟨tabs1, bstart2, lf1, df1⟩ => ?_
  refine d1_upd (by decide) fun lf2 => ?_
  exact d1_tot (d_push_table_spec _ _ _ _ _) fun _ => d1_ok trivial

@[local step]
theorem d_load_loop0_spec (tabs tb litc i) :
    slot.d_load_loop0 tabs tb litc i ⦃ fun _ => True ⦄ := by
  rw [slot.d_load_loop0]
  apply Std.loop.spec_decr_nat (measure := fun x => 256 - x.2.val) (inv := fun _ => True)
  · rintro ⟨litc', i'⟩ _
    simp only [slot.d_load_loop0.body, lift, bind_tc_ok]
    refine d1_ite (fun hi => ?_) (fun _ => d1_ok trivial)
    refine d1_tot (get0_spec _ _) fun i2 => ?_
    refine d1_upd hi fun a => ?_
    refine d1_add 256#usize (Nat.succ_le_of_lt hi) fun i3 hi3 => ?_
    exact d1_ok ⟨trivial, d1_msub hi hi3⟩
  · trivial

@[local step]
theorem d_load_loop1_spec (tabs tb lc l) :
    slot.d_load_loop1 tabs tb lc l ⦃ fun _ => True ⦄ := by
  rw [slot.d_load_loop1]
  apply Std.loop.spec_decr_nat (measure := fun x => 512 - x.2.val) (inv := fun _ => True)
  · rintro ⟨lc', l'⟩ _
    simp only [slot.d_load_loop1.body, lift, bind_tc_ok]
    refine d1_ite (fun hl => ?_) (fun _ => d1_ok trivial)
    refine d1_tot (Q := fun _ => True) (d1_ite (fun _ => get0_spec _ _) (fun _ => d1_ok trivial)) fun i => ?_
    refine d1_upd hl fun a => ?_
    refine d1_add 512#usize (Nat.succ_le_of_lt hl) fun l1 hl1 => ?_
    exact d1_ok ⟨trivial, d1_msub hl hl1⟩
  · trivial

@[local step]
theorem d_load_loop2_spec (tabs tb dcc i) :
    slot.d_load_loop2 tabs tb dcc i ⦃ fun _ => True ⦄ := by
  rw [slot.d_load_loop2]
  apply Std.loop.spec_decr_nat (measure := fun x => 32 - x.2.val) (inv := fun _ => True)
  · rintro ⟨dcc', i'⟩ _
    simp only [slot.d_load_loop2.body, lift, bind_tc_ok]
    refine d1_ite (fun hi => ?_) (fun _ => d1_ok trivial)
    refine d1_tot (get0_spec _ _) fun i3 => ?_
    refine d1_upd hi fun a => ?_
    refine d1_add 32#usize (Nat.succ_le_of_lt hi) fun i4 hi4 => ?_
    exact d1_ok ⟨trivial, d1_msub hi hi4⟩
  · trivial

@[local step]
theorem d_load_spec (tabs tb litc lc dcc) :
    slot.d_load tabs tb litc lc dcc ⦃ fun _ => True ⦄ := by
  rw [slot.d_load]
  refine d1_tot (d_load_loop0_spec _ _ _ _) fun litc1 => ?_
  refine d1_tot (d_load_loop1_spec _ _ _ _) fun lc1 => ?_
  exact d1_tot (d_load_loop2_spec _ _ _ _) fun _ => d1_ok trivial

theorem d2_ok {α : Type} {x : α} {P : α → Prop} (h : P x) : WP.spec (ok x) P :=
  (WP.spec_ok x).2 h

theorem d2_ite {α : Type} {c : Prop} {inst : Decidable c} {X Y : Result α} {P : α → Prop}
    (hX : c → WP.spec X P) (hY : ¬c → WP.spec Y P) : WP.spec (@ite _ c inst X Y) P := by
  by_cases h : c
  · rw [if_pos h]; exact hX h
  · rw [if_neg h]; exact hY h

theorem d2_itev {α : Type} {c : Prop} {inst : Decidable c} {a b : α} :
    WP.spec (@ite _ c inst (ok a) (ok b)) (fun _ => True) :=
  d2_ite (fun _ => d2_ok trivial) (fun _ => d2_ok trivial)

theorem d2_lt {ty : UScalarTy} {α : Type} {a b : UScalar ty} {inst : Decidable (a < b)} {X Y : Result α}
    {P : α → Prop} (hX : a.val < b.val → WP.spec X P) (hY : b.val ≤ a.val → WP.spec Y P) :
    WP.spec (@ite _ (a < b) inst X Y) P :=
  d2_ite hX (fun h => hY (Nat.le_of_not_lt h))

theorem d2_le {ty : UScalarTy} {α : Type} {a b : UScalar ty} {inst : Decidable (a ≤ b)} {X Y : Result α}
    {P : α → Prop} (hX : a.val ≤ b.val → WP.spec X P) (hY : b.val < a.val → WP.spec Y P) :
    WP.spec (@ite _ (a ≤ b) inst X Y) P :=
  d2_ite hX (fun h => hY (Nat.lt_of_not_le h))

theorem d2_tot {α β : Type} {m : Result α} {Q : α → Prop} {k : α → Result β} {P : β → Prop}
    (hm : WP.spec m Q) (hk : ∀ x, WP.spec (k x) P) : WP.spec (Bind.bind m k) P :=
  WP.spec_bind hm (fun x _ => hk x)

theorem d2_bind {α β : Type} {m : Result α} {Q : α → Prop} {k : α → Result β} {P : β → Prop}
    (hm : WP.spec m Q) (hk : ∀ x, Q x → WP.spec (k x) P) : WP.spec (Bind.bind m k) P :=
  WP.spec_bind hm hk

theorem d2_lift {α β : Type} {x : α} {k : α → Result β} {P : β → Prop}
    (h : WP.spec (k x) P) : WP.spec (Bind.bind (lift x) k) P := h

theorem d2_umax (x : Usize) : x.val ≤ Usize.max := UScalar.max_USize_eq ▸ ScalarTac.UScalar.bounds x

theorem d2_u32max : 4294967295 ≤ Usize.max := by
  rcases Usize.bounds_eq with h | h
  · rw [h, U32.max_eq]
  · rw [h, U64.max_eq]; decide

theorem d2_sub {β : Type} {x y : Usize} {k : Usize → Result β} {P : β → Prop}
    (h : y.val ≤ x.val) (hk : ∀ z : Usize, z.val + y.val = x.val → WP.spec (k z) P) :
    WP.spec (Bind.bind (HSub.hSub x y : Result Usize) k) P :=
  WP.spec_bind (Usize.sub_spec h) (fun z hz => hk z ((congrArg (· + y.val) hz.1).trans (Nat.sub_add_cancel h)))

theorem d2_dec {β : Type} {x y : Usize} {k : Usize → Result β} {P : β → Prop}
    (h : y.val < x.val) (hk : ∀ z : Usize, z.val + 1 = x.val → WP.spec (k z) P) :
    WP.spec (Bind.bind (HSub.hSub x 1#usize : Result Usize) k) P :=
  d2_sub (Nat.succ_le_of_lt (Nat.lt_of_le_of_lt (Nat.zero_le _) h)) hk

theorem d2_inc {β : Type} {x y : Usize} {k : Usize → Result β} {P : β → Prop}
    (h : x.val < y.val) (hk : ∀ z : Usize, z.val = x.val + 1 → WP.spec (k z) P) :
    WP.spec (Bind.bind (HAdd.hAdd x 1#usize : Result Usize) k) P :=
  WP.spec_bind (Usize.add_spec (Nat.le_trans (Nat.succ_le_of_lt h) (d2_umax y))) hk

theorem d2_inck {β : Type} {x : Usize} {k : Usize → Result β} {P : β → Prop} (c : Nat)
    (h : x.val ≤ c) (hc : c < 4294967295) (hk : ∀ z : Usize, z.val = x.val + 1 → WP.spec (k z) P) :
    WP.spec (Bind.bind (HAdd.hAdd x 1#usize : Result Usize) k) P :=
  WP.spec_bind (Usize.add_spec (Nat.le_trans (Nat.succ_le_of_lt (Nat.lt_of_le_of_lt h hc)) d2_u32max)) hk

theorem d2_addb {β : Type} {x y w : Usize} {k : Usize → Result β} {P : β → Prop}
    (h : x.val + y.val ≤ w.val) (hk : ∀ z : Usize, z.val = x.val + y.val → WP.spec (k z) P) :
    WP.spec (Bind.bind (HAdd.hAdd x y : Result Usize) k) P :=
  WP.spec_bind (Usize.add_spec (Nat.le_trans h (d2_umax w))) hk

theorem d2_rem {ty : UScalarTy} {β : Type} {x y : UScalar ty} {k : UScalar ty → Result β} {P : β → Prop}
    (h : 0 < y.val) (hk : ∀ z : UScalar ty, z.val < y.val → WP.spec (k z) P) :
    WP.spec (Bind.bind (HMod.hMod x y : Result (UScalar ty)) k) P :=
  WP.spec_bind (UScalar.rem_spec x (Nat.pos_iff_ne_zero.mp h)) (fun z hz => hk z (hz ▸ Nat.mod_lt _ h))

theorem d2_remR {β : Type} {x : Usize} {k : Usize → Result β} {P : β → Prop}
    (hk : ∀ z : Usize, z.val < (1024#usize).val → WP.spec (k z) P) :
    WP.spec (Bind.bind (HMod.hMod x slot.D_RING : Result Usize) k) P := by
  rw [slot.D_RING]; exact d2_rem (by decide) hk

theorem d2_div {β : Type} {x y : Usize} {k : Usize → Result β} {P : β → Prop}
    (h : y.val ≠ 0) (hk : ∀ z : Usize, WP.spec (k z) P) :
    WP.spec (Bind.bind (HDiv.hDiv x y : Result Usize) k) P :=
  WP.spec_bind (Usize.div_spec x h) (fun z _ => hk z)

theorem d2_shr32 (x : U64) : WP.spec (HShiftRight.hShiftRight x 32#i32 : Result U64) (fun _ => True) :=
  WP.spec_mono (U64.ShiftRight_IScalar_spec x 32#i32 (by decide) (by decide)) (fun _ _ => trivial)
theorem d2_shl32 (x : U64) : WP.spec (HShiftLeft.hShiftLeft x 32#i32 : Result U64) (fun _ => True) :=
  WP.spec_mono (U64.ShiftLeft_IScalar_spec x 32#i32 (by decide) (by decide)) (fun _ _ => trivial)
theorem d2_shr9 (x : U64) : WP.spec (HShiftRight.hShiftRight x 9#i32 : Result U64) (fun _ => True) :=
  WP.spec_mono (U64.ShiftRight_IScalar_spec x 9#i32 (by decide) (by decide)) (fun _ _ => trivial)
theorem d2_shl9 (x : U64) : WP.spec (HShiftLeft.hShiftLeft x 9#i32 : Result U64) (fun _ => True) :=
  WP.spec_mono (U64.ShiftLeft_IScalar_spec x 9#i32 (by decide) (by decide)) (fun _ _ => trivial)
theorem d2_shr9w (x : U32) : WP.spec (HShiftRight.hShiftRight x 9#i32 : Result U32) (fun _ => True) :=
  WP.spec_mono (U32.ShiftRight_IScalar_spec x 9#i32 (by decide) (by decide)) (fun _ _ => trivial)
theorem d2_shr24w (x : U32) : WP.spec (HShiftRight.hShiftRight x 24#i32 : Result U32) (fun _ => True) :=
  WP.spec_mono (U32.ShiftRight_IScalar_spec x 24#i32 (by decide) (by decide)) (fun _ _ => trivial)

theorem d2_idx {α β : Type} {n : Usize} {a : Std.Array α n} {i : Usize} {k : α → Result β} {P : β → Prop}
    (h : i.val < n.val) (hk : ∀ x, WP.spec (k x) P) : WP.spec (Bind.bind (Array.index_usize a i) k) P :=
  WP.spec_bind (Array.index_usize_spec a i (Nat.lt_of_lt_of_eq h a.property.symm)) (fun x _ => hk x)

theorem d2_upd {α β : Type} {n : Usize} {a : Std.Array α n} {i : Usize} {v : α} {k : Std.Array α n → Result β}
    {P : β → Prop} (h : i.val < n.val) (hk : ∀ x, WP.spec (k x) P) :
    WP.spec (Bind.bind (Array.update a i v) k) P :=
  WP.spec_bind (Array.update_spec a i v (Nat.lt_of_lt_of_eq h a.property.symm)) (fun x _ => hk x)

theorem d2_sidx {α β : Type} {s : Slice α} {i : Usize} {k : α → Result β} {P : β → Prop}
    (h : i.val < (Slice.len s).val) (hk : ∀ x, WP.spec (k x) P) :
    WP.spec (Bind.bind (Slice.index_usize s i) k) P :=
  WP.spec_bind (Slice.index_usize_spec s i h) (fun x _ => hk x)

theorem d2_supd {α β : Type} {s : Slice α} {i : Usize} {v : α} {k : Slice α → Result β} {P : β → Prop}
    (h : i.val < (Slice.len s).val) (hk : ∀ x : Slice α, x.length = s.length → WP.spec (k x) P) :
    WP.spec (Bind.bind (Slice.update s i v) k) P :=
  WP.spec_bind (Slice.update_spec s i v h) (fun x hx => hk x (hx ▸ Slice.set_length s i v))

theorem d2_push {α β : Type} {v : alloc.vec.Vec α} {x : α} {n : Usize} {k : alloc.vec.Vec α → Result β}
    {P : β → Prop} (h : (alloc.vec.Vec.len v).val < n.val) (hk : ∀ w, WP.spec (k w) P) :
    WP.spec (Bind.bind (alloc.vec.Vec.push v x) k) P :=
  WP.spec_bind (alloc.vec.Vec.push_spec v x (Nat.lt_of_lt_of_le h (d2_umax n))) (fun w _ => hk w)

theorem d2_inc_dm {β : Type} {i : U32} {k : Usize → Result β} {P : β → Prop}
    (h : i.val < (32768#u32).val) (hk : ∀ z : Usize, z.val ≤ 32768 → WP.spec (k z) P) :
    WP.spec (Bind.bind (HAdd.hAdd (UScalar.cast .Usize i) 1#usize : Result Usize) k) P := by
  have hi : (UScalar.cast .Usize i).val ≤ 32767 := by
    rw [U32.cast_Usize_val_eq]; exact Nat.le_of_lt_succ h
  exact d2_inck 32767 hi (by decide) (fun z hz => hk z (Nat.le_trans (Nat.le_of_eq hz) (Nat.succ_le_succ hi)))

theorem d2_mul_dm {β : Type} {z : Usize} {k : U64 → Result β} {P : β → Prop}
    (h : z.val ≤ 32768) (hk : ∀ c : U64, WP.spec (k c) P) :
    WP.spec (Bind.bind (HMul.hMul (UScalar.cast .U64 z) 512#u64 : Result U64) k) P := by
  have h1 : (UScalar.cast .U64 z).val ≤ 32768 := by
    rw [UScalar.cast_val_eq]; exact Nat.le_trans (Nat.mod_le _ _) h
  have h2 : (UScalar.cast .U64 z).val * (512#u64).val ≤ U64.max := by
    rw [U64.max_eq]; exact Nat.le_trans (Nat.mul_le_mul_right _ h1) (by decide)
  exact WP.spec_bind (U64.mul_spec h2) (fun c _ => hk c)

theorem d2_u8 (b : U8) : (UScalar.cast .Usize b).val < (256#usize).val := by
  rw [U8.cast_Usize_val_eq]; exact b.hBounds

theorem d2_ne0 {x : Usize} (h : ¬ x = 0#usize) : (0#usize).val < x.val :=
  Nat.pos_of_ne_zero (fun h0 => h (UScalar.eq_imp x 0#usize h0))

theorem d2_ts : slot.D_TS.val ≠ 0 := by rw [slot.D_TS]; decide

theorem d2_pred {a b : Nat} (h : a + 1 = b) : a < b := h ▸ Nat.lt_succ_self a
theorem d2_le_pred {a b c : Nat} (h : a + 1 = b) (hb : b ≤ c) : a < c := Nat.lt_of_lt_of_le (d2_pred h) hb
theorem d2_msub {e l l1 : Nat} (h : l < e) (h1 : l1 = l + 1) : e - l1 < e - l := by omega
theorem d2_msub3 {e l d l1 : Nat} (h : l < e) (hd : 0 < d) (h1 : l1 = l + d) : e - l1 < e - l := by omega
theorem d2_dp_meas {a k i e : Nat} (h1 : a + k = i) (h2 : i + 2 = e) : a < e := by omega

@[local step]
theorem d_clip_spec (x stop q) :
    slot.d_clip x stop q ⦃ fun r => True ⦄ := by
  rw [slot.d_clip]; exact d2_ite (fun _ => d2_itev) (fun _ => d2_ok trivial)

@[local step]
theorem d_gap_loop0_spec (s litc ring out lo dlit q nxt mid) :
    slot.d_gap_loop0 s litc ring out lo dlit q nxt mid ⦃ fun r => r.2.1.length = out.length ⦄ := by
  rw [slot.d_gap_loop0]
  apply Std.loop.spec_decr_nat (measure := fun x => x.2.2.1.val) (inv := fun x => x.2.1.length = out.length)
  · rintro ⟨ring', out', q', nxt'⟩ hinv
    unfold slot.d_gap_loop0.body
    refine d2_lt (fun h1 => ?_) (fun _ => d2_ok hinv)
    refine d2_le (fun h2 => ?_) (fun _ => d2_ok hinv)
    refine d2_le (fun h3 => ?_) (fun _ => d2_ok hinv)
    refine d2_dec h1 fun q1 hq1 => ?_
    refine d2_tot (d2_shr32 _) fun i2 => ?_
    refine d2_sidx (d2_le_pred hq1 h2) fun i3 => ?_
    refine d2_lift <| d2_idx (d2_u8 i3) fun i5 => ?_
    refine d2_lift <| d2_lift <| d2_tot (d2_shl32 _) fun i8 => ?_

    refine d2_lift <| d2_tot (Q := fun _ => True) ?_ fun v1 => ?_
    · exact d2_ite (fun _ => d2_remR fun i9 hi9 => d2_idx hi9 fun o => d2_itev) (fun _ => d2_ok trivial)
    refine d2_remR fun i9 hi9 => ?_
    refine d2_upd hi9 fun a => ?_
    refine d2_lift <| d2_supd (d2_le_pred hq1 h3) fun s1 hs1 => ?_
    exact d2_ok ⟨hs1.trans hinv, d2_pred hq1⟩
  · rfl

@[local step]
theorem d_gap_loop1_spec (s litc lc ring out «end» chd dlit q nxt kc s1) :
    slot.d_gap_loop1 s litc lc ring out «end» chd dlit q nxt kc s1 ⦃ fun r => r.2.1.length = out.length ⦄ := by
  rw [slot.d_gap_loop1]
  apply Std.loop.spec_decr_nat (measure := fun x => x.2.2.1.val) (inv := fun x => x.2.1.length = out.length)
  · rintro ⟨ring', out', q', nxt'⟩ hinv
    unfold slot.d_gap_loop1.body
    refine d2_lt (fun h1 => ?_) (fun _ => d2_ok hinv)
    refine d2_le (fun h2 => ?_) (fun _ => d2_ok hinv)
    refine d2_le (fun h3 => ?_) (fun _ => d2_ok hinv)
    refine d2_le (fun h4 => ?_) (fun _ => d2_ok hinv)
    refine d2_dec h1 fun q1 hq1 => ?_
    refine d2_sub (Nat.le_of_lt (d2_le_pred hq1 h4)) fun rem _ => ?_
    refine d2_tot (d2_shr32 _) fun i2 => ?_
    refine d2_sidx (d2_le_pred hq1 h2) fun i3 => ?_
    refine d2_lift <| d2_idx (d2_u8 i3) fun i5 => ?_
    refine d2_lift <| d2_lift <| d2_tot (d2_shl32 _) fun i8 => ?_
    refine d2_lift <| d2_rem (by decide) fun i9 hi9 => ?_
    refine d2_idx hi9 fun i10 => ?_
    refine d2_lift <| d2_lift <| d2_tot (d2_shl32 _) fun i13 => ?_
    refine d2_lift <| d2_lift <| d2_lift <| d2_tot d2_itev fun v => ?_
    refine d2_remR fun i16 hi16 => ?_
    refine d2_idx hi16 fun o => ?_
    refine d2_tot d2_itev fun v1 => ?_
    refine d2_upd hi16 fun a => ?_
    refine d2_lift <| d2_supd (d2_le_pred hq1 h3) fun s2 hs2 => ?_
    exact d2_ok ⟨hs2.trans hinv, d2_pred hq1⟩
  · rfl

@[local step]
theorem d_gap_loop2_spec (s litc lc ring out stop «end» chd dlit q nxt kc) :
    slot.d_gap_loop2 s litc lc ring out stop «end» chd dlit q nxt kc ⦃ fun r => r.2.2.length = out.length ⦄ := by
  rw [slot.d_gap_loop2]
  apply Std.loop.spec_decr_nat (measure := fun x => x.2.2.1.val) (inv := fun x => x.2.1.length = out.length)
  · rintro ⟨ring', out', q', nxt'⟩ hinv
    unfold slot.d_gap_loop2.body
    refine d2_lt (fun h1 => ?_) (fun _ => d2_ok hinv)
    refine d2_le (fun h2 => ?_) (fun _ => d2_ok hinv)
    refine d2_le (fun h3 => ?_) (fun _ => d2_ok hinv)
    refine d2_le (fun h4 => ?_) (fun _ => d2_ok hinv)
    refine d2_dec h1 fun q1 hq1 => ?_
    refine d2_sub (Nat.le_of_lt (d2_le_pred hq1 h4)) fun rem _ => ?_
    refine d2_tot (d2_shr32 _) fun i2 => ?_
    refine d2_sidx (d2_le_pred hq1 h2) fun i3 => ?_
    refine d2_lift <| d2_idx (d2_u8 i3) fun i5 => ?_
    refine d2_lift <| d2_lift <| d2_tot (d2_shl32 _) fun i8 => ?_
    refine d2_lift <| d2_rem (by decide) fun i9 hi9 => ?_
    refine d2_idx hi9 fun i10 => ?_
    refine d2_lift <| d2_lift <| d2_tot (d2_shl32 _) fun i13 => ?_
    refine d2_lift <| d2_lift <| d2_lift <| d2_tot d2_itev fun v => ?_
    refine d2_remR fun i16 hi16 => ?_
    refine d2_upd hi16 fun a => ?_
    refine d2_lift <| d2_supd (d2_le_pred hq1 h3) fun s2 hs2 => ?_
    exact d2_ok ⟨hs2.trans hinv, d2_pred hq1⟩
  · rfl

@[local step]
theorem d_gap_spec (s litc lc ring out hi stop «end» kcd chd lo nxt0 dlit) :
    slot.d_gap s litc lc ring out hi stop «end» kcd chd lo nxt0 dlit ⦃ fun r => r.2.2.length = out.length ⦄ := by
  rw [slot.d_gap]
  refine d2_lift <| d2_tot (d_clip_spec _ _ _) fun mid => ?_
  refine d2_bind (d_gap_loop0_spec s litc ring out lo dlit hi nxt0 mid) ?_
  rintro ⟨ring1, out1, q, nxt⟩ h0
  refine d2_tot (d_cell_spec _ _) fun i1 => ?_
  refine d2_tot (d2_shr32 _) fun i2 => ?_
  refine d2_lift <| d2_tot (d_clip_spec _ _ _) fun s1 => ?_
  refine d2_bind (d_gap_loop1_spec s litc lc ring1 out1 «end» chd dlit q nxt _ s1) ?_
  rintro ⟨ring2, out2, q1, nxt1⟩ h1
  exact WP.spec_mono (d_gap_loop2_spec s litc lc ring2 out2 stop «end» chd dlit q1 nxt1 _)
    (fun r h2 => h2.trans (h1.trans h0))

@[local step]
theorem d_bcost_spec (lc ring p l) :
    slot.d_bcost lc ring p l ⦃ fun _ => True ⦄ := by
  have hring : slot.D_RING.val = 1024 := by simp [slot.D_RING]
  rw [slot.d_bcost]
  step*
  all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))

@[local step]
theorem d_best_len_scalar_loop_spec (lc ring p e) (best : Std.U64) (bl l : Std.Usize) :
    slot.d_best_len_scalar_loop lc ring p e best bl l ⦃ fun _ => True ⦄ := by
  rw [slot.d_best_len_scalar_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, l') => e.val - l'.val)
    (inv := fun _ => True)
  · rintro ⟨best', bl', l'⟩ _
    simp only [slot.d_best_len_scalar_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · trivial

@[local step]
theorem d_best_len_scalar_spec (lc ring p lo e) :
    slot.d_best_len_scalar lc ring p lo e ⦃ fun _ => True ⦄ := by
  rw [slot.d_best_len_scalar]
  step*

@[local step]
theorem d_best_len_old_loop_spec (lc ring p e bv l) :
    slot.d_best_len_old_loop lc ring p e bv l ⦃ fun r => True ⦄ := by
  rw [slot.d_best_len_old_loop]
  apply Std.loop.spec_decr_nat (measure := fun x => e.val - x.2.val) (inv := fun _ => True)
  · rintro ⟨bv', l'⟩ _
    unfold slot.d_best_len_old_loop.body
    refine d2_lt (fun h1 => ?_) (fun _ => d2_ok trivial)
    refine d2_lift <| d2_remR fun i1 hi1 => ?_
    refine d2_idx hi1 fun i2 => ?_
    refine d2_tot (d2_shr32 _) fun i3 => ?_
    refine d2_rem (by decide) fun i4 hi4 => ?_
    refine d2_idx hi4 fun i5 => ?_
    refine d2_lift <| d2_lift <| d2_tot (d2_shl9 _) fun i8 => ?_
    refine d2_lift <| d2_lift <| d2_tot d2_itev fun bv1 => ?_
    refine d2_inc h1 fun l1 hl1 => ?_
    exact d2_ok ⟨trivial, d2_msub h1 hl1⟩
  · trivial

@[local step]
theorem d_best_len_old_spec (lc ring p lo e) :
    slot.d_best_len_old lc ring p lo e ⦃ fun r => True ⦄ :=
  d_best_len_old_loop_spec lc ring p e _ lo

@[local step]
theorem d_best_len_spec (lc ring p lo e) :
    slot.d_best_len lc ring p lo e ⦃ fun _ => True ⦄ := by
  rw [slot.d_best_len]
  step*
  repeat' (split <;> step*)
  all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))

@[local step]
theorem d_push_loop_spec (lc ring p el t f chd x) :
    slot.d_push_loop lc ring p el t f chd x ⦃ fun r => True ⦄ := by
  rw [slot.d_push_loop]
  apply Std.loop.spec_decr_nat (measure := fun x => 259 - x.2.val) (inv := fun _ => True)
  · rintro ⟨ring', x'⟩ _
    unfold slot.d_push_loop.body
    refine d2_le (fun h1 => ?_) (fun _ => d2_ok trivial)
    refine d2_le (fun h2 => ?_) (fun _ => d2_ok trivial)
    refine d2_le (fun h3 => ?_) (fun _ => d2_ok trivial)
    refine d2_sub h3 fun i hi => ?_
    refine d2_le (fun h4 => ?_) (fun _ => d2_ok trivial)

    have hx : el.val + x'.val ≤ (258#usize).val :=
      Nat.add_comm x'.val el.val ▸ (Nat.add_le_add_right h4 el.val).trans (Nat.le_of_eq hi)
    have hx' : x'.val ≤ 258 := Nat.le_trans (Nat.le_add_left _ _) hx
    refine d2_addb hx fun i1 _ => ?_
    refine d2_rem (by decide) fun i2 hi2 => ?_
    refine d2_idx hi2 fun i3 => ?_
    refine d2_lift <| d2_lift <| d2_tot (d2_shl32 _) fun i6 => ?_
    refine d2_lift <| d2_lift <| d2_lift <| d2_sub h2 fun i9 _ => ?_
    refine d2_remR fun i10 hi10 => ?_
    refine d2_idx hi10 fun o => ?_
    refine d2_tot d2_itev fun v1 => ?_
    refine d2_remR fun i11 hi11 => ?_
    refine d2_upd hi11 fun a => ?_
    refine d2_inck 258 hx' (by decide) fun x1 hx1 => ?_
    exact d2_ok ⟨trivial, d2_msub (Nat.lt_succ_of_le hx') hx1⟩
  · trivial

@[local step]
theorem d_push_spec (lc ring p el t f chd) :
    slot.d_push lc ring p el t f chd ⦃ fun r => True ⦄ :=
  d_push_loop_spec lc ring p el t f chd _

@[local step]
theorem d_init_loop_spec (ring top z) :
    slot.d_init_loop ring top z ⦃ fun r => True ⦄ := by
  rw [slot.d_init_loop]
  apply Std.loop.spec_decr_nat (measure := fun x => top.val - x.2.val) (inv := fun _ => True)
  · rintro ⟨ring', z'⟩ _
    unfold slot.d_init_loop.body
    refine d2_lt (fun h1 => ?_) (fun _ => d2_ok trivial)
    refine d2_remR fun i hi => ?_
    refine d2_upd hi fun a => ?_
    refine d2_inc h1 fun z1 hz1 => ?_
    exact d2_ok ⟨trivial, d2_msub h1 hz1⟩
  · trivial

@[local step]
theorem d_init_spec (ring st p z0) :
    slot.d_init ring st p z0 ⦃ fun r => True ⦄ := by
  rw [slot.d_init]
  refine d2_idx (by decide) fun i => ?_
  refine d2_lift <| d2_ite (fun _ => ?_) (fun _ => d2_ok trivial)
  refine d2_tot (d_min_spec _ _) fun top => ?_
  refine d2_tot (d_init_loop_spec _ _ _) fun ring1 => ?_
  exact d2_lift <| d2_upd (by decide) fun st1 => d2_ok trivial

@[local step]
theorem d_back_spec (lc ring p len bl t dcst chd2 pbest st) :
    slot.d_back lc ring p len bl t dcst chd2 pbest st ⦃ fun r => True ⦄ := by
  rw [slot.d_back]
  refine d2_ite (fun _ => d2_ok trivial) (fun _ => ?_)
  refine d2_bind (d_min_spec t p) fun tt htt => ?_
  refine d2_sub htt.2 fun i _ => ?_
  refine d2_tot (d_init_spec ring st p i) ?_
  rintro ⟨ring1, st1⟩
  refine d2_lift <| d2_tot (d_cell_spec _ _) fun i2 => ?_
  refine d2_tot (d2_shr32 _) fun i3 => ?_
  refine d2_lift <| d2_tot (d_push_spec _ _ _ _ _ _ _) fun ring2 => ?_
  refine d2_ite (fun _ => ?_) (fun _ => d2_ok trivial)
  refine d2_ite (fun _ => ?_) (fun _ => d2_ok trivial)
  refine d2_ite (fun _ => ?_) (fun _ => d2_ok trivial)
  refine d2_lift <| d2_tot (d_cell_spec _ _) fun i5 => ?_
  refine d2_tot (d2_shr32 _) fun i6 => ?_
  exact d2_lift <| d2_tot (d_push_spec _ _ _ _ _ _ _) fun ring3 => d2_ok trivial

@[local step]
theorem d_cand_spec (lc dcc dtab ring r p prev room pbest st) :
    slot.d_cand lc dcc dtab ring r p prev room pbest st ⦃ fun r => True ⦄ := by
  rw [slot.d_cand]
  refine d2_rem (by decide) fun i _ => ?_
  refine d2_lift <| d2_le (fun _ => d2_ok trivial) (fun hA => ?_)
  refine d2_lt (fun _ => d2_ok trivial) (fun hB => ?_)
  refine d2_ite (fun _ => d2_ok trivial) (fun _ => ?_)
  refine d2_tot (d2_shr9w _) fun i1 => ?_
  refine d2_rem (by decide) fun i2 hi2 => ?_
  refine d2_lift <| d2_tot (d2_shr24w _) fun i3 => ?_
  refine d2_lift <| d2_inc_dm hi2 fun i4 hi4 => ?_
  refine d2_tot (dsym_spec _ _) fun i5 => ?_
  refine d2_rem (by decide) fun i6 hi6 => ?_
  refine d2_idx hi6 fun i7 => ?_
  refine d2_lift <| d2_lift <| d2_mul_dm hi4 fun chd2 => ?_

  refine d2_inc hA fun i9 _ => ?_
  refine d2_inck 258 hB (by decide) fun i10 _ => ?_
  refine d2_tot (d_best_len_spec _ _ _ _ _) fun bb => ?_
  refine d2_rem (by decide) fun i11 _ => ?_
  refine d2_lift <| d2_tot (d2_shr9 _) fun i12 => ?_
  refine d2_lift <| d2_tot (d2_shl32 _) fun i14 => ?_
  refine d2_lift <| d2_lift <| d2_lift <| d2_tot (d_back_spec _ _ _ _ _ _ _ _ _ _) ?_
  rintro ⟨ring1, st1⟩
  refine d2_idx (by decide) fun s0 => ?_
  refine d2_tot d2_itev fun cand1 => ?_
  exact d2_upd (by decide) fun st2 => d2_ok trivial

@[local step]
theorem d_block_spec (tabs bstart litc lc dcc bs pos) :
    slot.d_block tabs bstart litc lc dcc bs pos ⦃ fun r => True ⦄ := by
  rw [slot.d_block]
  refine d2_idx (by decide) fun i => ?_
  refine d2_ite (fun _ => ?_) (fun _ => d2_ok trivial)
  refine d2_idx (by decide) fun i1 => ?_
  refine d2_lt (fun h => ?_) (fun _ => d2_ok trivial)
  refine d2_dec h fun b _ => ?_
  refine d2_lift <| d2_tot (d_load_spec _ _ _ _ _) ?_
  rintro ⟨litc1, lc1, dcc1⟩
  refine d2_upd (by decide) fun bs1 => ?_
  refine d2_tot (get0_spec _ _) fun i3 => ?_
  exact d2_lift <| d2_upd (by decide) fun bs2 => d2_ok trivial

@[local step]
theorem d_top_spec (rs e k) :
    slot.d_top rs e k ⦃ fun r => True ⦄ := by
  rw [slot.d_top]
  exact d2_ite (fun _ => d2_lift (get0_spec _ _)) (fun _ => d2_ok trivial)

@[local step]
theorem d_end_spec (p cl room) :
    slot.d_end p cl room ⦃ fun r => True ⦄ := by
  rw [slot.d_end]; exact d2_itev

@[local step]
theorem d_stop_spec (bfirst p1 q) :
    slot.d_stop bfirst p1 q ⦃ fun r => True ⦄ := by
  rw [slot.d_stop]; exact d2_ite (fun _ => d2_itev) (fun _ => d2_ok trivial)

@[local step]
theorem d_node_best_spec (ring p lo best) :
    slot.d_node_best ring p lo best ⦃ fun r => True ⦄ := by
  rw [slot.d_node_best]
  exact d2_ite (fun _ => d2_remR fun i hi => d2_idx hi fun o => d2_itev) (fun _ => d2_ok trivial)

@[local step]
theorem d_dp_loop0_loop0_spec (s tabs bstart out ring litc lc dcc dlit bs dslot chd «end» lo p1 q nxt fuel) :
    slot.d_dp_loop0_loop0 s tabs bstart out ring litc lc dcc dlit bs dslot chd «end» lo p1 q nxt fuel
      ⦃ fun r => r.1.length = out.length ⦄ := by
  rw [slot.d_dp_loop0_loop0]
  apply Std.loop.spec_decr_nat (measure := fun x => x.2.2.2.2.2.2.2.2.val) (inv := fun x => x.1.length = out.length)
  · rintro ⟨out', ring', litc', lc', dcc', bs', q', nxt', fuel'⟩ hinv
    unfold slot.d_dp_loop0_loop0.body
    refine d2_lt (fun h1 => ?_) (fun _ => d2_ok hinv)
    refine d2_lt (fun h2 => ?_) (fun _ => d2_ok hinv)
    refine d2_dec h2 fun fuel1 hf => ?_
    refine d2_dec h1 fun i _ => ?_
    refine d2_tot (d_block_spec _ _ _ _ _ _ _) ?_
    rintro ⟨litc1, lc1, dcc1, bs1⟩
    refine d2_idx (by decide) fun i1 => ?_
    refine d2_tot (d_stop_spec _ _ _) fun stop => ?_
    refine d2_rem (by decide) fun i2 hi2 => ?_
    refine d2_idx hi2 fun i3 => ?_
    refine d2_lift <| d2_bind (d_gap_spec s litc1 lc1 ring' out' q' stop «end» _ chd lo nxt' dlit) ?_
    rintro ⟨nxt1, ring1, out1⟩ hg
    exact d2_ok ⟨hg.trans hinv, d2_pred hf⟩
  · rfl

@[local step]
theorem d_dp_loop0_loop1_spec (rs dtab ring lc dcc pbest st p e2 room prev j) :
    slot.d_dp_loop0_loop1 rs dtab ring lc dcc pbest st p e2 room prev j ⦃ fun r => True ⦄ := by
  rw [slot.d_dp_loop0_loop1]
  apply Std.loop.spec_decr_nat (measure := fun x => e2.val - x.2.2.2.val) (inv := fun _ => True)
  · rintro ⟨ring', st', prev', j'⟩ _
    unfold slot.d_dp_loop0_loop1.body
    refine d2_lt (fun h1 => ?_) (fun _ => d2_ok trivial)
    refine d2_tot (get0_spec _ _) fun i => ?_
    refine d2_tot (d_cand_spec _ _ _ _ _ _ _ _ _ _) ?_
    rintro ⟨prev1, ring1, st1⟩
    refine d2_inc h1 fun j1 hj1 => ?_
    exact d2_ok ⟨trivial, d2_msub h1 hj1⟩
  · trivial

@[local step]
theorem d_dp_loop0_spec (s rs tabs bstart dtab out n ring litc lc dcc dlit pbest st bs e hi) :
    slot.d_dp_loop0 s rs tabs bstart dtab out n ring litc lc dcc dlit pbest st bs e hi
      ⦃ fun r => r.length = out.length ⦄ := by
  rw [slot.d_dp_loop0]
  apply Std.loop.spec_decr_nat (measure := fun x => x.2.2.2.2.2.2.2.1.val) (inv := fun x => x.1.length = out.length)
  · rintro ⟨out', ring', litc', lc', dcc', st', bs', e', hi'⟩ hinv
    unfold slot.d_dp_loop0.body
    refine d2_le (fun h1 => ?_) (fun _ => d2_ok hinv)
    have he0 : (0#usize).val < e'.val := Nat.lt_of_lt_of_le (by decide) h1
    refine d2_dec he0 fun i _ => ?_
    refine d2_tot (get0_spec _ _) fun i1 => ?_
    refine d2_lift <| d2_sub h1 fun i2 hi2 => ?_
    refine d2_tot (get0_spec _ _) fun i3 => ?_

    refine d2_lift <| d2_lt (fun _ => d2_ok ⟨hinv, he0⟩) (fun hk => ?_)
    refine d2_le (fun _ => d2_ok ⟨hinv, he0⟩) (fun hp => ?_)
    refine d2_sub hk fun a ha => ?_
    refine d2_tot (d_top_spec _ _ _) fun top => ?_
    refine d2_rem (by decide) fun i4 _ => ?_
    refine d2_lift <| d2_tot (d2_shr9w _) fun i5 => ?_
    refine d2_rem (by decide) fun i6 hi6 => ?_
    refine d2_lift <| d2_inc_dm hi6 fun i7 hi7 => ?_
    refine d2_tot (dsym_spec _ _) fun dslot => ?_
    refine d2_lift <| d2_mul_dm hi7 fun chd => ?_
    refine d2_lift <| d2_tot (d_end_spec _ _ _) fun «end» => ?_
    refine d2_idx (by decide) fun i9 => ?_
    refine d2_lift <| d2_inc hp fun p1 _ => ?_
    refine d2_tot (d_cell_spec _ _) fun nxt => ?_

    refine d2_lift <| d2_bind (d_dp_loop0_loop0_spec s tabs bstart out' ring' litc' lc' dcc' dlit bs' dslot chd «end»
      _ p1 hi' nxt _) ?_
    rintro ⟨out1, ring1, litc1, lc1, dcc1, bs1, nxt1⟩ ho1
    refine d2_tot (d_block_spec _ _ _ _ _ _ _) ?_
    rintro ⟨litc2, lc2, dcc2, bs2⟩
    refine d2_tot (d2_shr32 _) fun i11 => ?_
    refine d2_tot (d_byte_spec _ _) fun i12 => ?_
    refine d2_rem (by decide) fun i13 hi13 => ?_
    refine d2_idx hi13 fun i14 => ?_
    refine d2_lift <| d2_lift <| d2_tot (d2_shl32 _) fun i17 => ?_
    refine d2_lift <| d2_upd (by decide) fun a1 => ?_
    refine d2_tot (d_dp_loop0_loop1_spec _ _ _ _ _ _ _ _ _ _ _ _) ?_
    rintro ⟨ring2, st1⟩
    refine d2_idx (by decide) fun i19 => ?_
    refine d2_tot (d_node_best_spec _ _ _ _) fun best => ?_
    refine d2_remR fun i20 hi20 => ?_
    refine d2_upd hi20 fun a2 => ?_
    refine d2_lift <| d2_bind (set_in_spec out1 _ _) fun out2 ho2 => ?_
    exact d2_ok ⟨ho2.trans (ho1.trans hinv), d2_dp_meas ha hi2⟩
  · rfl

@[local step]
theorem d_dp_spec (s rs tabs bstart dtab out pmode) :
    slot.d_dp s rs tabs bstart dtab out pmode ⦃ fun r => r.length = out.length ⦄ := by
  rw [slot.d_dp]
  refine d2_ite (fun _ => d2_ok rfl) (fun _ => ?_)
  refine d2_ite (fun _ => d2_ok rfl) (fun h0 => ?_)
  refine d2_div d2_ts fun i3 => ?_
  refine d2_ite (fun _ => d2_ok rfl) (fun _ => ?_)
  refine d2_remR fun i5 hi5 => ?_
  refine d2_upd hi5 fun a => ?_
  refine d2_tot d2_itev fun dlit => ?_
  refine d2_rem (by decide) fun pbest _ => ?_
  refine d2_lift <| d2_dec (d2_ne0 h0) fun b0 _ => ?_
  refine d2_tot (get0_spec _ _) fun i8 => ?_
  refine d2_lift <| d2_lift <| d2_tot (d_load_spec _ _ _ _ _) ?_
  rintro ⟨litc1, lc1, dcc1⟩
  exact d_dp_loop0_spec _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _

@[local step]
theorem d_extract_loop_spec (out n plan p) :
    slot.d_extract_loop out n plan p ⦃ fun r => True ⦄ := by
  rw [slot.d_extract_loop]
  apply Std.loop.spec_decr_nat (measure := fun x => n.val - x.2.val) (inv := fun _ => True)
  · rintro ⟨plan', p'⟩ _
    unfold slot.d_extract_loop.body
    refine d2_lt (fun h1 => ?_) (fun _ => d2_ok trivial)
    refine d2_lt (fun h2 => ?_) (fun _ => d2_ok trivial)
    refine d2_tot (get0_spec _ _) fun v => ?_
    refine d2_rem (by decide) fun i1 _ => ?_

    refine d2_lift <| d2_le (fun h3 => ?_)
      (fun _ => d2_push h2 fun plan1 => d2_inc h1 fun p1 hp1 => d2_ok ⟨trivial, d2_msub h1 hp1⟩)
    refine d2_sub (Nat.le_of_lt h1) fun i2 hi2 => ?_
    refine d2_le (fun h4 => ?_)
      (fun _ => d2_push h2 fun plan1 => d2_inc h1 fun p1 hp1 => d2_ok ⟨trivial, d2_msub h1 hp1⟩)
    refine d2_ite (fun _ => ?_)
      (fun _ => d2_push h2 fun plan1 => d2_inc h1 fun p1 hp1 => d2_ok ⟨trivial, d2_msub h1 hp1⟩)
    refine d2_push h2 fun plan1 => ?_
    have hle : p'.val + (UScalar.cast UScalarTy.Usize i1).val ≤ n.val :=
      Nat.add_comm _ p'.val ▸ (Nat.add_le_add_right h4 p'.val).trans (Nat.le_of_eq hi2)
    refine d2_addb hle fun p1 hp1 => ?_
    exact d2_ok ⟨trivial, d2_msub3 h1 (Nat.lt_of_lt_of_le (by decide) h3) hp1⟩
  · trivial

@[local step]
theorem d_extract_spec (out n plan) :
    slot.d_extract out n plan ⦃ fun r => True ⦄ :=
  d_extract_loop_spec out n plan _

@[local step]
theorem d_le8_spec (s i) : slot.d_le8 s i ⦃ fun _ => True ⦄ := by
  rw [slot.d_le8]
  simp only [lift, bind_tc_ok]
  apply dp_ite_spec <;> intro h8
  · have h8' : 8 ≤ s.len.val := (UScalar.le_equiv _ _).mp h8
    refine d3_sub (b := 8) rfl rfl h8' ?_; intro i1 hi1
    apply dp_ite_spec <;> intro hle
    · have hb : i.val + 8 ≤ s.length := by
        have hl := Slice.len_val s
        have hle' : i.val ≤ i1.val := (UScalar.le_equiv _ _).mp hle
        omega
      have hm : s.length ≤ Std.Usize.max := Slice.length_ineq s
      clear hle hi1 h8' h8 i1
      refine d3_add (b := 7) rfl rfl (by omega) ?_; intro i2 hi2
      refine d3_sidx (by omega) ?_; intro i3; clear hi2
      refine d3_shl (by decide) ?_; intro i5
      refine d3_add (b := 6) rfl rfl (by omega) ?_; intro i6 hi6
      refine d3_sidx (by omega) ?_; intro i7; clear hi6
      refine d3_shl (by decide) ?_; intro i9
      refine d3_add (b := 5) rfl rfl (by omega) ?_; intro i11 hi11
      refine d3_sidx (by omega) ?_; intro i12; clear hi11
      refine d3_shl (by decide) ?_; intro i14
      refine d3_add (b := 4) rfl rfl (by omega) ?_; intro i16 hi16
      refine d3_sidx (by omega) ?_; intro i17; clear hi16
      refine d3_shl (by decide) ?_; intro i19
      refine d3_add (b := 3) rfl rfl (by omega) ?_; intro i21 hi21
      refine d3_sidx (by omega) ?_; intro i22; clear hi21
      refine d3_shl (by decide) ?_; intro i24
      refine d3_add (b := 2) rfl rfl (by omega) ?_; intro i26 hi26
      refine d3_sidx (by omega) ?_; intro i27; clear hi26
      refine d3_shl (by decide) ?_; intro i29
      refine d3_add (b := 1) rfl rfl (by omega) ?_; intro i31 hi31
      refine d3_sidx (by omega) ?_; intro i32; clear hi31
      refine d3_shl (by decide) ?_; intro i34
      refine d3_sidx (by omega) ?_; intro i36
      exact d3_ok trivial
    · exact d3_ok trivial
  · exact d3_ok trivial

@[local step]
theorem d_backext_loop0_spec (s i d cap t run) :
    slot.d_backext_loop0 s i d cap t run ⦃ fun _ => True ⦄ := by
  rw [slot.d_backext_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (t', run') => cap.val - t'.val + run'.val)
    (inv := fun _ => True)
  · rintro ⟨t', run'⟩ _
    simp only [slot.d_backext_loop0.body, lift, bind_tc_ok]
    apply dp_ite_spec <;> intro hrun
    · have hr : run'.val = 1 := congrArg UScalar.val hrun
      apply dp_ite_spec <;> intro hcap
      · have hcap' : 8 ≤ cap.val := (UScalar.le_equiv _ _).mp hcap
        refine d3_sub (b := 8) rfl rfl hcap' ?_; intro i1 hi1
        apply dp_ite_spec <;> intro ht
        · have ht' : t'.val ≤ i1.val := (UScalar.le_equiv _ _).mp ht
          have hm := d3_le_max cap
          refine d3_bind (d_le8_spec _ _) ?_; intro i3 _
          refine d3_bind (d_le8_spec _ _) ?_; intro i5 _
          apply dp_ite_spec <;> intro hx
          · refine d3_add (b := 8) rfl rfl (by omega) ?_; intro t1 ht1
            exact d3_ok ⟨trivial, (by omega : cap.val - t1.val + run'.val < cap.val - t'.val + run'.val)⟩
          · refine d3_bind (U32.div_spec _ (by decide)) ?_; intro i7 hi7
            have hi7' : i7.val = (core.num.U64.leading_zeros (i3 ^^^ i5)).val / 8 := hi7
            have hlz := lz64_le (i3 ^^^ i5)
            have hc := d3_cast_le .Usize i7
            refine d3_add rfl rfl (by omega) ?_; intro t1 ht1
            exact d3_ok ⟨trivial, (by omega : cap.val - t1.val + 0 < cap.val - t'.val + run'.val)⟩
        · exact d3_ok trivial
      · exact d3_ok trivial
    · exact d3_ok trivial
  · trivial

@[local step]
theorem d_backext_loop1_spec (s i d cap t run) :
    slot.d_backext_loop1 s i d cap t run ⦃ fun _ => True ⦄ := by
  rw [slot.d_backext_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (t', run') => cap.val - t'.val + run'.val)
    (inv := fun _ => True)
  · rintro ⟨t', run'⟩ _
    simp only [slot.d_backext_loop1.body, lift, bind_tc_ok]
    apply dp_ite_spec <;> intro hrun
    · have hr : run'.val = 1 := congrArg UScalar.val hrun
      apply dp_ite_spec <;> intro ht
      · have ht' : t'.val < cap.val := (UScalar.lt_equiv _ _).mp ht
        have hm := d3_le_max cap
        apply dp_ite_spec <;> intro ha
        · have ha' := (UScalar.lt_equiv _ _).mp ha
          have hl := Slice.len_val s
          apply dp_ite_spec <;> intro hd
          · have hd' := (UScalar.le_equiv _ _).mp hd
            refine d3_sidx (by omega) ?_; intro i3
            refine d3_sub rfl rfl hd' ?_; intro i4 hi4
            refine d3_sidx (by omega) ?_; intro i5
            apply dp_ite_spec <;> intro he
            · refine d3_add (b := 1) rfl rfl (by omega) ?_; intro t1 ht1
              exact d3_ok ⟨trivial, (by omega : cap.val - t1.val + run'.val < cap.val - t'.val + run'.val)⟩
            · exact d3_ok ⟨trivial, (by omega : cap.val - t'.val + 0 < cap.val - t'.val + run'.val)⟩
          · exact d3_ok ⟨trivial, (by omega : cap.val - t'.val + 0 < cap.val - t'.val + run'.val)⟩
        · exact d3_ok ⟨trivial, (by omega : cap.val - t'.val + 0 < cap.val - t'.val + run'.val)⟩
      · exact d3_ok trivial
    · exact d3_ok trivial
  · trivial

@[local step]
theorem d_backext_spec (s i d max) : slot.d_backext s i d max ⦃ fun _ => True ⦄ := by
  rw [slot.d_backext]
  simp only [lift, bind_tc_ok]
  refine d3_bind (d3_true (d_min_spec ..)) ?_; intro cap _
  refine d3_bind (d_backext_loop0_spec _ _ _ _ _ _) ?_; rintro ⟨t, run⟩ _
  exact d3_unc (d_backext_loop1_spec _ _ _ _ _ _)

@[local step]
theorem d_seen_loop_spec (pc pn want dup z) : slot.d_seen_loop pc pn want dup z ⦃ fun _ => True ⦄ := by
  rw [slot.d_seen_loop]
  apply Std.loop.spec_decr_nat (measure := fun (_, z') => 16 - z'.val) (inv := fun _ => True)
  · rintro ⟨dup', z'⟩ _
    simp only [slot.d_seen_loop.body]
    apply dp_ite_spec <;> intro h1
    · apply dp_ite_spec <;> intro h2
      · have h2' : z'.val < 16 := (UScalar.lt_equiv _ _).mp h2
        refine d3_idx (c := 16) rfl h2' ?_; intro x
        refine d3_bind (Q := fun _ => True) ?_ ?_
        · split <;> exact d3_ok trivial
        intro dup1 _
        refine d3_add (b := 1) rfl rfl (by have := d3_max_ge; omega) ?_; intro z1 hz1
        exact d3_ok ⟨trivial, (by omega : 16 - z1.val < 16 - z'.val)⟩
      · exact d3_ok trivial
    · exact d3_ok trivial
  · trivial

@[local step]
theorem d_seen_spec (pc pn want) : slot.d_seen pc pn want ⦃ fun _ => True ⦄ := by
  rw [slot.d_seen]; exact d_seen_loop_spec _ _ _ _ _

@[local step]
theorem d_isdup_spec (pc pn c len dist cl cd adj dupmode) :
    slot.d_isdup pc pn c len dist cl cd adj dupmode ⦃ fun _ => True ⦄ := by
  rw [slot.d_isdup]
  simp only [lift, bind_tc_ok]
  apply dp_ite_spec <;> intro _
  · exact d3_ok trivial
  apply dp_ite_spec <;> intro _
  · apply dp_ite_spec <;> intro _
    · apply dp_ite_spec <;> intro _
      · exact d3_ok trivial
      · apply dp_ite_spec <;> intro _
        · exact d_seen_spec _ _ _
        · exact d3_ok trivial
    · apply dp_ite_spec <;> intro _
      · exact d_seen_spec _ _ _
      · exact d3_ok trivial
  · apply dp_ite_spec <;> intro _
    · exact d_seen_spec _ _ _
    · exact d3_ok trivial

@[local step]
theorem d_rec_cand_spec (input rs c i last pc pn adj cl cd tbmax dupmode) :
    slot.d_rec_cand input rs c i last pc pn adj cl cd tbmax dupmode ⦃ fun _ => True ⦄ := by
  rw [slot.d_rec_cand]
  simp only [lift, bind_tc_ok]
  refine d3_rem (b := 512) rfl (by decide) ?_; intro i1 _
  refine d3_shr (n := 9) (by decide) rfl ?_; intro i2 _
  apply dp_ite_spec <;> intro h1
  · exact d3_ok trivial
  apply dp_ite_spec <;> intro h2
  · exact d3_ok trivial
  apply dp_ite_spec <;> intro h3
  · exact d3_ok trivial
  apply dp_ite_spec <;> intro h4
  · exact d3_ok trivial
  apply dp_ite_spec <;> intro h5
  · exact d3_ok trivial
  refine d3_bind (d_isdup_spec _ _ _ _ _ _ _ _ _) ?_; intro dup _
  refine d3_bind (Q := fun _ => True) ?_ ?_
  · apply dp_ite_spec <;> intro hd
    · have h5' : ¬ (258 < (UScalar.cast .Usize i1).val) := (UScalar.lt_equiv _ _).not.mp h5
      refine d3_sub (a := 258) rfl rfl (by omega) ?_; intro i3 _
      refine d3_bind (d3_true (d_min_spec ..)) ?_; intro i4 _
      exact d_backext_spec _ _ _ _
    · exact d3_ok trivial
  intro t _
  have h2' : ¬ ((UScalar.cast .Usize i2).val < 1) := (UScalar.lt_equiv _ _).not.mp h2
  refine d3_sub (b := 1) rfl rfl (by omega) ?_; intro i4 _
  refine d3_shl (by decide) ?_; intro i6
  refine d3_shl (by decide) ?_; intro i9
  refine d3_bind (d3_true (d_push32_spec ..)) ?_; intro rs1 _
  exact d3_ok trivial

@[local step]
theorem d_record_loop_spec (input rs cands nc i pc pn cl cd tbmax dupmode adj q last) :
    slot.d_record_loop input rs cands nc i pc pn cl cd tbmax dupmode adj q last ⦃ fun _ => True ⦄ := by
  rw [slot.d_record_loop]
  apply Std.loop.spec_decr_nat (measure := fun (_, q', _) => 16 - q'.val) (inv := fun _ => True)
  · rintro ⟨rs', q', last'⟩ _
    simp only [slot.d_record_loop.body]
    apply dp_ite_spec <;> intro h1
    · apply dp_ite_spec <;> intro h2
      · have h2' : q'.val < 16 := (UScalar.lt_equiv _ _).mp h2
        refine d3_idx (c := 16) rfl h2' ?_; intro c
        refine d3_bind (d_rec_cand_spec _ _ _ _ _ _ _ _ _ _ _ _) ?_; rintro ⟨last1, rs1⟩ _
        refine d3_unc ?_
        refine d3_add (b := 1) rfl rfl (by have := d3_max_ge; omega) ?_; intro q1 hq1
        exact d3_ok ⟨trivial, (by omega : 16 - q1.val < 16 - q'.val)⟩
      · exact d3_ok trivial
    · exact d3_ok trivial
  · trivial

@[local step]
theorem d_record_spec (input rs cands nc i pc pn ppos cl cd tbmax dupmode) :
    slot.d_record input rs cands nc i pc pn ppos cl cd tbmax dupmode ⦃ fun _ => True ⦄ := by
  rw [slot.d_record]
  step*
  repeat' (split <;> step*)

@[local step]
theorem d_fill_nextl_loop0_loop0_spec (lsym) (l e : Std.Usize) (hl : l.val < 257) (he : e.val ≤ 258) :
    slot.d_fill_nextl_loop0_loop0 lsym l e ⦃ fun r => e.val ≤ r.val ∧ r.val ≤ 258 ⦄ := by
  rw [slot.d_fill_nextl_loop0_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun e' => 258 - e'.val)
    (inv := fun e' => e.val ≤ e'.val ∧ e'.val ≤ 258)
  · rintro e' ⟨h1, h2⟩
    simp only [slot.d_fill_nextl_loop0_loop0.body]
    have hM := d3_max_ge
    apply dp_ite_spec <;> intro hlt
    · have hlt' : e'.val < 258 := (UScalar.lt_equiv _ _).mp hlt
      refine d3_add (b := 1) rfl rfl (by omega) ?_; intro i hi
      refine d3_idx (c := 512) rfl (by omega) ?_; intro i1
      refine d3_add (b := 1) rfl rfl (by omega) ?_; intro i2 hi2
      refine d3_idx (c := 512) rfl (by omega) ?_; intro i3
      apply dp_ite_spec <;> intro _
      · exact d3_ok ⟨⟨(by omega : e.val ≤ i.val), (by omega : i.val ≤ 258)⟩,
          (by omega : 258 - i.val < 258 - e'.val)⟩
      · exact d3_ok ⟨h1, h2⟩
    · exact d3_ok ⟨h1, h2⟩
  · exact ⟨le_refl _, he⟩

theorem d3_nextl_step (nx a : Array Std.U16 512#usize) (l : Std.Usize) (v : Std.U16)
    (hl : l.val < 512) (hv : l.val < v.val) (ha : a = nx.set l v)
    (h2 : ∀ j, j < l.val → j < (nx.val[j]!).val) :
    ∀ j, j < l.val + 1 → j < (a.val[j]!).val := by
  intro j hj
  rw [ha, Array.set_val_eq, dp_getElem!_set _ _ _ _ (lt_of_lt_of_eq hl (Array.length_eq nx).symm)]
  split
  · omega
  · exact h2 j (by omega)

@[local step]
theorem d_fill_nextl_loop0_spec (lsym) (nextl : Array Std.U16 512#usize) (flen l : Std.Usize)
    (hl : l.val ≤ 512) (hnx : ∀ j, j < l.val → j < (nextl.val[j]!).val) :
    slot.d_fill_nextl_loop0 lsym nextl flen l ⦃ fun r => DpNextl r ⦄ := by
  rw [slot.d_fill_nextl_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, l') => 512 - l'.val)
    (inv := fun (nx', l') => l'.val ≤ 512 ∧ ∀ j, j < l'.val → j < (nx'.val[j]!).val)
  · rintro ⟨nx', l'⟩ ⟨h1, h2⟩
    simp only [slot.d_fill_nextl_loop0.body, lift, bind_tc_ok]
    have hM := d3_max_ge
    apply dp_ite_spec <;> intro hlt
    · have hlt' : l'.val < 512 := (UScalar.lt_equiv _ _).mp hlt
      apply dp_ite_spec <;> intro _
      · refine d3_add (b := 1) rfl rfl (by omega) ?_; intro i hi
        refine d3_upd (c := 512) rfl hlt' ?_; intro a ha
        have hv : (UScalar.cast .U16 i).val = i.val :=
          UScalar.cast_val_mod_pow_of_inBounds_eq _ _ (by show i.val < 65536; omega)
        have hs := d3_nextl_step nx' a l' _ hlt' (by omega) ha h2
        exact d3_ok ⟨⟨(by omega : i.val ≤ 512), fun j (hj : j < i.val) => hs j (by omega)⟩,
          (by omega : 512 - i.val < 512 - l'.val)⟩
      · apply dp_ite_spec <;> intro h257
        · refine d3_add (b := 1) rfl rfl (by omega) ?_; intro i hi
          refine d3_upd (c := 512) rfl hlt' ?_; intro a ha
          have hv : (UScalar.cast .U16 i).val = i.val :=
            UScalar.cast_val_mod_pow_of_inBounds_eq _ _ (by show i.val < 65536; omega)
          have hs := d3_nextl_step nx' a l' _ hlt' (by omega) ha h2
          exact d3_ok ⟨⟨(by omega : i.val ≤ 512), fun j (hj : j < i.val) => hs j (by omega)⟩,
            (by omega : 512 - i.val < 512 - l'.val)⟩
        · have h257' : ¬ (257 ≤ l'.val) := (UScalar.le_equiv _ _).not.mp h257
          refine d3_add (b := 1) rfl rfl (by omega) ?_; intro e he
          refine d3_bind (d_fill_nextl_loop0_loop0_spec _ _ _ (by omega) (by omega)) ?_; intro e1 he1
          refine d3_upd (c := 512) rfl hlt' ?_; intro a ha
          refine d3_add (b := 1) rfl rfl (by omega) ?_; intro l1 hl1
          have hv : (UScalar.cast .U16 e1).val = e1.val :=
            UScalar.cast_val_mod_pow_of_inBounds_eq _ _ (by show e1.val < 65536; omega)
          have hs := d3_nextl_step nx' a l' _ hlt' (by omega) ha h2
          exact d3_ok ⟨⟨(by omega : l1.val ≤ 512), fun j (hj : j < l1.val) => hs j (by omega)⟩,
            (by omega : 512 - l1.val < 512 - l'.val)⟩
    · have hge : ¬ (l'.val < 512) := (UScalar.lt_equiv _ _).not.mp hlt
      exact d3_ok (fun j hj => h2 j (by omega))
  · exact ⟨hl, hnx⟩

@[local step]
theorem d_fill_nextl_spec (lsym) (nextl : Array Std.U16 512#usize) (flen : Std.Usize) :
    slot.d_fill_nextl lsym nextl flen ⦃ fun r => DpNextl r ⦄ := by
  rw [slot.d_fill_nextl]
  exact d_fill_nextl_loop0_spec _ _ _ _ (Nat.zero_le _) (fun j hj => absurd hj (Nat.not_lt_zero _))

@[local step]
theorem d_walk_loop_spec (s : Slice Std.U8) (prev : Array Std.U32 32768#usize) (i : Std.Usize) (b8 : Std.U64)
    (cap : Std.Usize) (cands) (nice nc best c k : Std.Usize)
    (hc : c.val ≤ i.val) (hcap : 9 ≤ cap.val) (hic : i.val + cap.val ≤ s.length)
    (hs8 : s.length + 8 ≤ Std.Usize.max) (hb : best.val ≤ cap.val) :
    slot.d_walk_loop s prev i b8 cap cands nice nc best c k
      ⦃ fun r => best.val ≤ r.2.2.val ∧ r.2.2.val ≤ cap.val ⦄ := by
  rw [slot.d_walk_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, k') => k'.val)
    (inv := fun (_, _, best', c', _) => c'.val ≤ i.val ∧ best.val ≤ best'.val ∧ best'.val ≤ cap.val)
  · rintro ⟨cands', nc', best', c', k'⟩ ⟨h1, h2, h3⟩
    simp only [slot.d_walk_loop.body, lift, bind_tc_ok]
    apply dp_ite_spec <;> intro hk
    · have hk' : 0 < k'.val := (UScalar.lt_equiv _ _).mp hk
      apply dp_ite_spec <;> intro _
      · apply dp_ite_spec <;> intro _
        · apply dp_ite_spec <;> intro _
          · apply dp_ite_spec <;> intro hnc
            · have hnc' : nc'.val < 15 := (UScalar.lt_equiv _ _).mp hnc
              refine d3_bind (probe_spec _ _ _ _ _ _ h1 hcap hic hs8) ?_; intro l hl
              refine d3_bind (Q := fun (x : Array Std.U32 16#usize × Std.Usize × Std.Usize) =>
                best.val ≤ x.2.2.val ∧ x.2.2.val ≤ cap.val) ?_ ?_
              · apply dp_ite_spec <;> intro hl0
                · have hl0' : 0 < l.val := (UScalar.lt_equiv _ _).mp hl0
                  apply dp_ite_spec <;> intro _
                  · refine d3_shl (by decide) ?_; intro i4
                    refine d3_rem (b := 16) rfl (by decide) ?_; intro i5 hi5
                    refine d3_upd (c := 16) rfl hi5 ?_; intro a _
                    refine d3_add (b := 1) rfl rfl (by have := d3_max_ge; omega) ?_; intro nc2 _
                    exact d3_ok ⟨(by omega : best.val ≤ l.val), hl.1⟩
                  · exact d3_ok ⟨h2, h3⟩
                · exact d3_ok ⟨h2, h3⟩
              rintro ⟨cands1, nc1, best1⟩ ⟨hb1, hb2⟩
              refine d3_unc (d3_unc ?_)
              refine d3_rem (b := 32768) dp_WN_val (by decide) ?_; intro i2 hi2
              refine d3_idx (c := 32768) rfl hi2 ?_; intro i3
              apply dp_ite_spec <;> intro hnx
              · have hnx' := (UScalar.lt_equiv _ _).mp hnx
                refine d3_sub (b := 1) rfl rfl (by omega) ?_; intro k1 hk1
                exact d3_ok ⟨⟨(by omega : (UScalar.cast .Usize i3).val ≤ i.val), hb1, hb2⟩,
                  (by omega : k1.val < k'.val)⟩
              · exact d3_ok ⟨⟨h1, hb1, hb2⟩, hk'⟩
            · exact d3_ok ⟨⟨h1, h2, h3⟩, hk'⟩
          · exact d3_ok ⟨⟨h1, h2, h3⟩, hk'⟩
        · exact d3_ok ⟨⟨h1, h2, h3⟩, hk'⟩
      · exact d3_ok ⟨⟨h1, h2, h3⟩, hk'⟩
    · exact d3_ok ⟨h2, h3⟩
  · exact ⟨hc, le_refl _, hb⟩

@[local step]
theorem d_walk_spec (s : Slice Std.U8) (prev) (i start depth : Std.Usize) (b8 : Std.U64)
    (cap : Std.Usize) (cands) (nc0 best0 nice : Std.Usize)
    (hst : start.val ≤ i.val) (hcap : 9 ≤ cap.val) (hic : i.val + cap.val ≤ s.length)
    (hs8 : s.length + 8 ≤ Std.Usize.max) (hb : best0.val ≤ cap.val) :
    slot.d_walk s prev i start depth b8 cap cands nc0 best0 nice
      ⦃ fun r => best0.val ≤ r.1.2.val ∧ r.1.2.val ≤ cap.val ⦄ := by
  rw [slot.d_walk]
  refine d3_bind (d_walk_loop_spec _ _ _ _ _ _ _ _ _ _ _ hst hcap hic hs8 hb) ?_
  rintro ⟨cands1, nc, best⟩ ⟨h1, h2⟩
  exact d3_unc (d3_unc (d3_ok ⟨h1, h2⟩))

@[local step]
theorem d_back_best_loop_spec (input : Slice Std.U8) (pa lc) (i s len dd tmax t bt : Std.Usize) (bv : Std.U32)
    (hi : i.val < input.length) (hlen : len.val < 512) (hdd : dd.val < 8388608)
    (hN : input.length + 2147483648 ≤ Std.Usize.max)
    (ht : t.val ≤ i.val) (hbt : bt.val ≤ t.val) :
    slot.d_back_best_loop input pa lc i s len dd tmax t bt bv ⦃ fun r => r.1.val ≤ i.val ⦄ := by
  rw [slot.d_back_best_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (t', _, _) => tmax.val - t'.val)
    (inv := fun (t', bt', _) => t'.val ≤ i.val ∧ bt'.val ≤ t'.val)
  · rintro ⟨t', bt', bv'⟩ ⟨h1, h2⟩
    simp only [slot.d_back_best_loop.body, lift, bind_tc_ok]
    have hbi : bt'.val ≤ i.val := Nat.le_trans h2 h1
    have hiM : i.val + 2147483648 ≤ Std.Usize.max := by omega
    clear hN ht hbt
    apply dp_ite_spec <;> intro ht
    · have ht' : t'.val < tmax.val := (UScalar.lt_equiv _ _).mp ht
      refine d3_add rfl rfl (by omega) ?_; intro i1 _
      apply dp_ite_spec <;> intro _
      · refine d3_add (b := 1) rfl rfl (by omega) ?_; intro i2 hi2
        refine d3_add rfl rfl (by omega) ?_; intro i3 hi3
        apply dp_ite_spec <;> intro hge
        · have hA : i2.val + dd.val ≤ i.val := by have := (UScalar.le_equiv _ _).mp hge; omega
          clear hge hi3 i3 hdd
          refine d3_sub rfl rfl h1 ?_; intro i4 hi4
          refine d3_sub (b := 1) rfl rfl (by omega) ?_; intro i5 _
          apply dp_ite_spec <;> intro _
          · refine d3_sub (b := 1) rfl rfl (by omega) ?_; intro i6 hi6
            refine d3_sidx (by omega) ?_; intro i7; clear hi6
            refine d3_sub (b := 1) rfl rfl (by omega) ?_; intro i8 hi8
            refine d3_sub rfl rfl (by omega) ?_; intro i9 hi9
            refine d3_sidx (by omega) ?_; intro i10; clear hi9 hi8 hi4
            apply dp_ite_spec <;> intro _
            · have hle : i2.val ≤ i.val := Nat.le_trans (Nat.le_add_right _ _) hA
              have hbt2 : bt'.val ≤ i2.val := by omega
              have hms : tmax.val - i2.val < tmax.val - t'.val := by omega
              refine d3_sub rfl rfl hle ?_; intro i11 _
              refine d3_rem (b := 8192) dp_RING_val (by decide) ?_; intro i12 hi12
              refine d3_idx (c := 8192) rfl hi12 ?_; intro i13
              refine d3_shr (n := 32) (by decide) rfl ?_; intro i14 _
              refine d3_add rfl rfl (by omega) ?_; intro i16 _
              refine d3_rem (b := 512) rfl (by decide) ?_; intro i17 hi17
              refine d3_idx (c := 512) rfl hi17 ?_; intro i18
              apply dp_ite_spec <;> intro _
              · exact d3_ok ⟨⟨hle, le_refl _⟩, hms⟩
              · exact d3_ok ⟨⟨hle, hbt2⟩, hms⟩
            · exact d3_ok hbi
          · exact d3_ok hbi
        · exact d3_ok hbi
      · exact d3_ok hbi
    · exact d3_ok hbi
  · exact ⟨ht, hbt⟩

@[local step]
theorem d_back_best_spec (input : Slice Std.U8) (pa lc) (i s len dd tmax : Std.Usize)
    (hi : i.val < input.length) (hlen : len.val < 512) (hdd : dd.val < 8388608)
    (hN : input.length + 2147483648 ≤ Std.Usize.max) :
    slot.d_back_best input pa lc i s len dd tmax ⦃ fun r => r.1.val ≤ i.val ⦄ := by
  rw [slot.d_back_best]
  exact d_back_best_loop_spec _ _ _ _ _ _ _ _ _ _ _ hi hlen hdd hN (Nat.zero_le _) (le_refl _)

@[local step]
theorem d_relax_cands_loop_spec (input : Slice Std.U8) (pa cands nc lc) (nextl : Array Std.U16 512#usize)
    (dtab dcc) (i s : Std.Usize) (base : Std.U32) (pcd fback lo k : Std.Usize)
    (hnx : DpNextl nextl) (hi : i.val < input.length) (hN : input.length + 2147483648 ≤ Std.Usize.max) :
    slot.d_relax_cands_loop input pa cands nc lc nextl dtab dcc i s base pcd fback lo k ⦃ fun _ => True ⦄ := by
  rw [slot.d_relax_cands_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, k') => 16 - k'.val)
    (inv := fun _ => True)
  · rintro ⟨pa', lo', k'⟩ _
    simp only [slot.d_relax_cands_loop.body, lift, bind_tc_ok]
    apply dp_ite_spec <;> intro _
    · apply dp_ite_spec <;> intro h2
      · have h2' : k'.val < 16 := (UScalar.lt_equiv _ _).mp h2
        have hM := d3_max_ge
        refine d3_idx (c := 16) rfl h2' ?_; intro c
        refine d3_rem (b := 512) rfl (by decide) ?_; intro i1 hi1
        refine d3_shr (n := 9) (by decide) rfl ?_; intro i2 hi2
        have hlen := d3_cast_le .Usize i1
        have hdd := d3_cast_le .Usize i2
        have h9 := dp_shr9 c
        refine d3_bind (dsym_spec _ _) ?_; intro i3 _
        refine d3_rem (b := 32) rfl (by decide) ?_; intro ds hds
        refine d3_idx (c := 32) rfl hds ?_; intro i4
        refine d3_bind (relax_run_spec _ _ _ _ _ _ _ _ hnx (by omega) (by omega)) ?_; intro pa1 _
        refine d3_add (b := 1) rfl rfl (by omega) ?_; intro lo1 _
        refine d3_bind (Q := fun _ => True) ?_ ?_
        · apply dp_ite_spec <;> intro _
          · apply dp_ite_spec <;> intro _
            · refine d3_add rfl rfl (by have := dp_BEXT_TOP_bound; omega) ?_; intro i7 _
              apply dp_ite_spec <;> intro _
              · refine d3_bind (d_back_best_spec _ _ _ _ _ _ _ _ hi (by omega) (by omega) hN) ?_
                rintro ⟨i8, i9⟩ hbb
                have hbb' : i8.val ≤ i.val := hbb
                refine d3_unc ?_
                apply dp_ite_spec <;> intro _
                · refine d3_add rfl rfl (by omega) ?_; intro i10 _
                  refine d3_add rfl rfl (by omega) ?_; intro i14 _
                  exact relax_one_spec _ _ _ _
                · exact d3_ok trivial
              · exact d3_ok trivial
            · exact d3_ok trivial
          · exact d3_ok trivial
        intro pa2 _
        refine d3_add (b := 1) rfl rfl (by omega) ?_; intro k1 hk1
        exact d3_ok ⟨trivial, (by omega : 16 - k1.val < 16 - k'.val)⟩
      · exact d3_ok trivial
    · exact d3_ok trivial
  · trivial

@[local step]
theorem d_relax_cands_spec (input : Slice Std.U8) (pa cands nc lc) (nextl : Array Std.U16 512#usize)
    (dtab dcc) (i s : Std.Usize) (base : Std.U32) (pcd fback : Std.Usize)
    (hnx : DpNextl nextl) (hi : i.val < input.length) (hN : input.length + 2147483648 ≤ Std.Usize.max) :
    slot.d_relax_cands input pa cands nc lc nextl dtab dcc i s base pcd fback ⦃ fun _ => True ⦄ := by
  rw [slot.d_relax_cands]
  exact d_relax_cands_loop_spec _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ hnx hi hN

@[local step]
theorem d_relax_spec (input : Slice Std.U8) (pa cands nc lc) (nextl : Array Std.U16 512#usize)
    (dtab dcc) (i s : Std.Usize) (base : Std.U32) (pcd fback : Std.Usize)
    (hnx : DpNextl nextl) (hi : i.val < input.length) (hN : input.length + 2147483648 ≤ Std.Usize.max) :
    slot.d_relax input pa cands nc lc nextl dtab dcc i s base pcd fback ⦃ fun _ => True ⦄ := by
  rw [slot.d_relax]
  apply dp_ite_spec <;> intro _
  · exact relax_cands_spec _ _ _ _ _ _ _ _ _ _ _ _ hnx hi hN
  · exact d_relax_cands_spec _ _ _ _ _ _ _ _ _ _ _ _ _ hnx hi hN

@[local step]
theorem d_parse_loop_spec (input : Slice Std.U8) (plan rs)
    (ct lazyn d4 d7 skip h3d tbmax lz2max dupmode fback d7l d7e nice n : Std.Usize)
    (head3 : Array Std.U32 16384#usize) (head4 : Array Std.U32 65536#usize) (prev4)
    (head7 : Array Std.U32 65536#usize) (prev7 pa tb) (lsym : Array Std.U8 512#usize) (dtab)
    (nextl : Array Std.U16 512#usize) (lf df litc lc dcc) (lim : Std.Usize) (sh7 : Std.U32)
    (s next_upd : Std.Usize) (cands pc) (pn ppos cl cd : Std.Usize) (cdc : Std.U32) (i anchor alen : Std.Usize)
    (hn : n.val = input.length) (hlim : lim.val + 8 = n.val)
    (hN : input.length + input.length ≤ Std.Usize.max)
    (hls : LeAll lsym.val 28) (hnx : DpNextl nextl)
    (hsi : s.val ≤ i.val) (hin : i.val ≤ n.val) (hcl : cl.val < 512)
    (h3 : LeAll head3.val i.val) (h4 : LeAll head4.val i.val) (h7 : LeAll head7.val i.val) :
    slot.d_parse_loop input plan rs ct lazyn d4 d7 skip h3d tbmax lz2max dupmode fback d7l d7e nice n
      head3 head4 prev4 head7 prev7 pa tb lsym dtab nextl lf df litc lc dcc lim sh7 s next_upd cands pc pn ppos
      cl cd cdc i anchor alen ⦃ fun _ => True ⦄ := by
  have hS := dp_size hN
  rw [slot.d_parse_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, i', _, _) => lim.val - i'.val)
    (inv := fun (_, _, h3', h4', _, h7', _, _, _, _, _, _, _, _, s', _, _, _, _, _, cl', _, _, i', _, _) =>
       s'.val ≤ i'.val ∧ i'.val ≤ n.val ∧ cl'.val < 512 ∧ LeAll h3'.val i'.val ∧ LeAll h4'.val i'.val ∧
       LeAll h7'.val i'.val)
  · rintro ⟨plan', rs', h3', h4', p4', h7', p7', pa', tb', lf', df', litc', lc', dcc', s', nu', cands', pc', pn',
      ppos', cl', cd', cdc', i', anc', alen'⟩ ⟨hs', hi', hcl', hh3, hh4, hh7⟩
    clear hsi hin hcl h3 h4 h7
    clear plan rs head3 head4 prev4 head7 prev7 pa tb lf df litc lc dcc s next_upd cands pc pn ppos cl cd cdc i
      anchor alen
    simp only [slot.d_parse_loop.body, lift, bind_tc_ok]
    apply dp_ite_spec <;> intro hlt
    swap
    · exact d3_ok trivial
    have hlt' : i'.val < lim.val := (UScalar.lt_equiv _ _).mp hlt
    have hiM : i'.val + 2147483648 ≤ Std.Usize.max := by clear * - hi' hn hS; omega

    refine d3_bind (Q := fun _ => True) ?_ ?_
    · apply dp_ite_spec <;> intro _
      · refine d3_add (b := 258) rfl rfl (by clear * - hiM; omega) ?_; intro i1 _
        refine d3_rem (b := 8192) dp_RING_val (by decide) ?_; intro i2 hi2
        exact d3_true (Array.update_spec _ _ _ (d3_alen _ rfl hi2))
      · exact d3_ok trivial
    intro pa1 _
    refine d3_bind (be8_spec _ _ (by clear * - hiM; omega)) ?_; intro b8 _
    refine d3_bind (insert_pos_spec _ _ _ _ _ _ _ _ i'.val hh3 hh4 hh7 (le_refl _)) ?_
    rintro ⟨⟨c3, c4, c7⟩, head31, head41, prev41, head71, prev71⟩ ⟨hq1, hq2, hq3, hL3, hL4, hL7⟩
    have hq1 : c3.val ≤ i'.val := hq1
    have hq2 : c4.val ≤ i'.val := hq2
    have hq3 : c7.val ≤ i'.val := hq3
    have hL3 : LeAll head31.val i'.val := hL3
    have hL4 : LeAll head41.val i'.val := hL4
    have hL7 : LeAll head71.val i'.val := hL7
    iterate 5 refine d3_unc ?_
    refine d3_rem (b := 8192) dp_RING_val (by decide) ?_; intro i1 hi1
    refine d3_idx (c := 8192) rfl hi1 ?_; intro i2
    refine d3_shr (n := 32) (by decide) rfl ?_; intro i3 _
    refine d3_add (b := 1) rfl rfl (by clear * - hiM; omega) ?_; intro i4 hi4
    refine d3_shr (n := 56) (by decide) rfl ?_; intro i5 _
    refine d3_rem (b := 256) rfl (by decide) ?_; intro i7 hi7
    refine d3_idx (c := 256) rfl hi7 ?_; intro i8
    refine d3_bind (relax_one_spec _ _ _ _) ?_; intro pa2 _
    refine d3_bind (Q := fun _ => True) ?_ ?_
    · apply dp_ite_spec <;> intro _ <;> exact d3_ok trivial
    intro lzn _
    refine d3_bind (Q := fun _ => True) ?_ ?_
    · apply dp_ite_spec <;> intro _
      · exact d3_ok trivial
      · refine d3_bind (Q := fun _ => True) ?_ ?_
        · apply dp_ite_spec <;> intro _ <;> exact d3_ok trivial
        intro _ _; exact d3_ok trivial
    rintro ⟨lazy_here, dep7⟩ _
    refine d3_unc ?_
    clear hi1 hi7 hh3 hh4 hh7 hlt
    refine d3_bind (Q := fun (x : alloc.vec.Vec Std.U32 × alloc.vec.Vec Std.U32 × Array Std.U32 16384#usize ×
          Array Std.U32 65536#usize × Array Std.U32 32768#usize × Array Std.U32 65536#usize × Array Std.U32 32768#usize ×
          Array Std.U64 8192#usize × Array Std.U32 8192#usize × Array Std.U32 320#usize × Array Std.U32 32#usize ×
          Std.Usize × Array Std.U32 16#usize × Array Std.U32 16#usize × Std.Usize × Std.Usize × Std.Usize × Std.Usize ×
          Std.U32 × Std.Usize × Std.Usize × Std.Usize) =>
        match x with
        | (_, _, g3, g4, _, g7, _, _, _, _, _, s1, _, _, _, _, cl1, _, _, i12, _, _) =>
          s1.val ≤ i12.val ∧ i'.val < i12.val ∧ i12.val ≤ n.val ∧ cl1.val < 512 ∧
          LeAll g3.val i12.val ∧ LeAll g4.val i12.val ∧ LeAll g7.val i12.val) ?_ ?_
    · apply dp_ite3_spec
      ·
        intro _ hc3 _
        have hc3' : 3 ≤ cl'.val := (UScalar.le_equiv _ _).mp hc3
        have h14 : i'.val < i4.val := by clear * - hi4; omega
        refine d3_add rfl rfl (by clear * - hiM hcl'; omega) ?_; intro i13 _
        refine d3_rem (b := 512) rfl (by decide) ?_; intro i15 hi15
        refine d3_idx (c := 512) rfl hi15 ?_; intro i16
        refine d3_shl (by decide) ?_; intro i19
        refine d3_bind (relax_one_spec _ _ _ _) ?_; intro pa4 _
        refine d3_sub (b := 1) rfl rfl (by clear * - hc3'; omega) ?_; intro cl2 hcl2
        exact d3_ok ⟨(by clear * - hs' h14; omega : s'.val ≤ i4.val), h14,
          (by clear * - hi4 hlt' hlim; omega : i4.val ≤ n.val), (by clear * - hcl2 hcl'; omega : cl2.val < 512),
          LeAll_mono hL3 (Nat.le_of_lt h14), LeAll_mono hL4 (Nat.le_of_lt h14), LeAll_mono hL7 (Nat.le_of_lt h14)⟩
      ·
        refine d3_sub rfl rfl hi' ?_; intro cap hcap
        refine d3_bind (Q := fun (x : Std.Usize) => 9 ≤ x.val ∧ i'.val + x.val ≤ n.val) ?_ ?_
        · apply dp_ite_spec <;> intro h
          · have h' : 258 < cap.val := (UScalar.lt_equiv _ _).mp h
            exact d3_ok ⟨(by decide : 9 ≤ 258), (by clear * - h' hcap; omega : i'.val + 258 ≤ n.val)⟩
          · exact d3_ok ⟨(by clear * - hcap hlt' hlim; omega : 9 ≤ cap.val),
              (by clear * - hcap; omega : i'.val + cap.val ≤ n.val)⟩
        rintro cap1 ⟨hcap1, hcap2⟩
        iterate 2 refine d3_unc ?_
        have hic : i'.val + cap1.val ≤ input.length := by clear * - hcap2 hn; omega
        have hs8 : input.length + 8 ≤ Std.Usize.max := by clear * - hS; omega
        have hilt : i'.val < input.length := by clear * - hic hcap1; omega
        clear hcap cap

        refine d3_bind (Q := fun (x : Array Std.U32 16#usize × Std.Usize × Std.Usize × Bool) =>
          2 ≤ x.2.2.1.val ∧ x.2.2.1.val ≤ cap1.val) ?_ ?_
        · apply dp_ite_spec <;> intro _
          · refine d3_bind (probe_spec _ _ _ _ _ _ hq1 hcap1 hic hs8) ?_; intro l3 hl3
            refine d3_bind (Q := fun (x : Array Std.U32 16#usize × Std.Usize × Std.Usize) =>
              2 ≤ x.2.2.val ∧ x.2.2.val ≤ cap1.val) ?_ ?_
            · apply dp_ite_spec <;> intro h0
              · have h0' : 0 < l3.val := (UScalar.lt_equiv _ _).mp h0
                have hl3' : l3.val = 0 ∨ 2 < l3.val := hl3.2
                refine d3_shl (by decide) ?_; intro i21
                refine d3_upd (c := 16) rfl (by decide) ?_; intro a1 _
                exact d3_ok ⟨(by clear * - h0' hl3'; omega : 2 ≤ l3.val), hl3.1⟩
              · exact d3_ok ⟨(by decide : 2 ≤ 2), (by clear * - hcap1; omega : 2 ≤ cap1.val)⟩
            rintro ⟨a, i17, i18⟩ ⟨hb1, hb2⟩
            exact d3_unc (d3_unc (d3_ok ⟨hb1, hb2⟩))
          · exact d3_ok ⟨(by decide : 2 ≤ 2), (by clear * - hcap1; omega : 2 ≤ cap1.val)⟩
        rintro ⟨cands2, nc, best, p3⟩ ⟨hb1, hb2⟩
        have hb1 : 2 ≤ best.val := hb1
        have hb2 : best.val ≤ cap1.val := hb2
        iterate 3 refine d3_unc ?_
        refine d3_bind (Q := fun _ => True) ?_ ?_
        · apply dp_ite_spec <;> intro _ <;> exact d3_ok trivial
        intro b _

        refine d3_bind (skip_same_spec _ _ _ _) ?_; rintro ⟨i17, i18⟩ hsk
        have hsk : i17.val ≤ i'.val := Nat.le_trans hsk hq2
        refine d3_unc ?_
        refine d3_bind (d_walk_spec _ _ _ _ _ _ _ _ _ _ _ hsk hcap1 hic hs8 hb2) ?_
        rintro ⟨⟨nc1, best1⟩, cands3⟩ ⟨hw1, hw2⟩
        have hw1 : 2 ≤ best1.val := Nat.le_trans hb1 hw1
        have hw2 : best1.val ≤ cap1.val := hw2
        iterate 2 refine d3_unc ?_
        refine d3_bind (Q := fun _ => True) ?_ ?_
        · apply dp_ite_spec <;> intro _
          · exact d3_ok trivial
          · refine d3_bind (Q := fun _ => True) ?_ ?_
            · apply dp_ite_spec <;> intro _ <;> exact d3_ok trivial
            intro _ _; exact d3_ok trivial
        rintro ⟨cands4, dep71⟩ _
        refine d3_unc ?_
        refine d3_bind (Q := fun _ => True) ?_ ?_
        · apply dp_ite_spec <;> intro _
          · apply dp_ite_spec <;> intro _
            · exact d3_ok trivial
            · apply dp_ite_spec <;> intro _ <;> exact d3_ok trivial
          · apply dp_ite_spec <;> intro _ <;> exact d3_ok trivial
        intro b1 _

        refine d3_bind (skip_same_spec _ _ _ _) ?_; rintro ⟨i19, i20⟩ hsk2
        have hsk2 : i19.val ≤ i'.val := Nat.le_trans hsk2 hq3
        refine d3_unc ?_
        refine d3_bind (d_walk_spec _ _ _ _ _ _ _ _ _ _ _ hsk2 hcap1 hic hs8 hw2) ?_
        rintro ⟨⟨nc2, best2⟩, cands5⟩ ⟨hw3, hw4⟩
        have hw3 : 2 ≤ best2.val := Nat.le_trans hw1 hw3
        have hw4 : best2.val ≤ cap1.val := hw4
        iterate 2 refine d3_unc ?_

        refine d3_bind (Q := fun (x : Array Std.U32 16#usize × Std.Usize × Std.Usize) =>
          2 ≤ x.2.2.val ∧ x.2.2.val ≤ cap1.val) ?_ ?_
        · apply dp_ite2_spec
          · intro hgt hle
            have hgt' : best2.val < cl'.val := (UScalar.lt_equiv _ _).mp hgt
            refine d3_bind (drop_farther_spec _ _ _) ?_; intro nc4 _
            refine d3_shl (by decide) ?_; intro i23
            refine d3_rem (b := 16) rfl (by decide) ?_; intro i24 hi24
            refine d3_upd (c := 16) rfl hi24 ?_; intro a _
            refine d3_bind (Q := fun _ => True) ?_ ?_
            · apply dp_ite_spec <;> intro h16
              · have h16' : nc4.val < 16 := (UScalar.lt_equiv _ _).mp h16
                exact d3_true (Usize.add_spec (by
                  have := d3_max_ge
                  show nc4.val + 1 ≤ Std.Usize.max
                  clear * - h16' this; omega))
              · exact d3_ok trivial
            intro i26 _
            exact d3_ok ⟨(by clear * - hgt' hw3; omega : 2 ≤ cl'.val), (UScalar.le_equiv _ _).mp hle⟩
          · exact d3_ok ⟨hw3, hw4⟩
        rintro ⟨cands6, nc3, best3⟩ ⟨hb3, hb4⟩
        have hb3 : 2 ≤ best3.val := hb3
        have hb4 : best3.val ≤ cap1.val := hb4
        iterate 2 refine d3_unc ?_
        clear hb1 hb2 hw1 hw2 hw3 hw4 hsk hsk2 hq1 hq2 hq3

        refine d3_bind (d_record_spec _ _ _ _ _ _ _ _ _ _ _ _) ?_; intro rs2 _
        refine d3_bind (Q := fun _ => True) ?_ ?_
        · apply dp_ite_spec <;> intro _ <;> exact d3_ok trivial
        intro pcd _
        refine d3_bind (next_anchor_spec _ _ _ _) ?_; intro alen2 _
        refine d3_bind (next_anchor_spec _ _ _ _) ?_; intro anchor2 _
        refine d3_bind (Q := fun (x : Std.Usize × Std.Usize × Std.U32) => x.1.val < 512) ?_ ?_
        · apply dp_ite_spec <;> intro hnc
          · have hnc' : 0 < nc3.val := (UScalar.lt_equiv _ _).mp hnc
            refine d3_sub (b := 1) rfl rfl hnc' ?_; intro i21 _
            refine d3_rem (b := 16) rfl (by decide) ?_; intro i22 hi22
            refine d3_idx (c := 16) rfl hi22 ?_; intro top
            refine d3_rem (b := 512) rfl (by decide) ?_; intro i23 hi23
            refine d3_shr (n := 9) (by decide) rfl ?_; intro i25 _
            refine d3_bind (dsym_spec _ _) ?_; intro i26 _
            refine d3_rem (b := 32) rfl (by decide) ?_; intro i27 hi27
            refine d3_idx (c := 32) rfl hi27 ?_; intro cdc3
            have hsat := dp_sat_sub_val (UScalar.cast .Usize i23) 1#usize
            have hcst := d3_cast_le .Usize i23
            exact d3_ok (by
              show (core.num.Usize.saturating_sub (UScalar.cast .Usize i23) 1#usize).val < 512
              clear * - hsat hcst hi23; omega)
          · exact d3_ok (by decide : 0 < 512)
        rintro ⟨cl2, cd2, cdc2⟩ hcl2
        have hcl2 : cl2.val < 512 := hcl2
        iterate 2 refine d3_unc ?_

        refine d3_bind (Q := fun (x : alloc.vec.Vec Std.U32 × Array Std.U32 16384#usize ×
              Array Std.U32 65536#usize × Array Std.U32 32768#usize × Array Std.U32 65536#usize ×
              Array Std.U32 32768#usize × Array Std.U64 8192#usize × Array Std.U32 8192#usize ×
              Array Std.U32 320#usize × Array Std.U32 32#usize × Std.Usize × Std.Usize × Std.Usize) =>
            match x with
            | (_, g3, g4, _, g7, _, _, _, _, _, s1, cl1, i12) =>
              s1.val ≤ i12.val ∧ i'.val < i12.val ∧ i12.val ≤ n.val ∧ cl1.val < 512 ∧
              LeAll g3.val i12.val ∧ LeAll g4.val i12.val ∧ LeAll g7.val i12.val) ?_ ?_
        · apply dp_ite2_spec
          · intro _ hnc
            have hnc' : 0 < nc3.val := (UScalar.lt_equiv _ _).mp hnc
            refine d3_sub (b := 1) rfl rfl hnc' ?_; intro i24 _
            refine d3_rem (b := 16) rfl (by decide) ?_; intro i25 hi25
            refine d3_idx (c := 16) rfl hi25 ?_; intro c0
            refine d3_shr (n := 9) (by decide) rfl ?_; intro i26 hi26
            refine d3_rem (b := 259) rfl (by decide) ?_; intro i27 hi27
            refine d3_sub (a := 258) rfl rfl (by clear * - hi27; omega) ?_; intro i28 _
            have hd0 : (UScalar.cast .Usize i26).val < 8388608 := by
              have h9 := dp_shr9 c0
              have hc := d3_cast_le .Usize i26
              clear * - h9 hc hi26; omega
            refine d3_bind (ext_back_spec _ _ _ _ _ hilt hd0 hS hs') ?_; intro t ht
            have ht' : t.val ≤ i'.val := by clear * - ht; omega
            refine d3_sub rfl rfl ht' ?_; intro st hst
            refine d3_bind (backtrack_spec _ _ _ _ _ _ _ _ _ _
              (by clear * - hst ht hs'; omega) (by clear * - hst hiM; omega)) ?_
            rintro ⟨plan2, lf2, df2, tb2⟩ _
            iterate 3 refine d3_unc ?_
            refine d3_bind (Q := fun _ => True) ?_ ?_
            · apply dp_ite_spec <;> intro hpl
              · have hpl' := (UScalar.lt_equiv _ _).mp hpl
                have hlv : plan2.len.val = plan2.val.length := alloc.vec.Vec.len_val plan2
                have hnm := d3_le_max n
                exact d3_true (alloc.vec.Vec.push_spec _ _ (by clear * - hpl' hlv hnm; omega))
              · exact d3_ok trivial
            intro plan3 _
            refine d3_add rfl rfl (by clear * - ht' hb4 hic hS; omega) ?_; intro i30 _
            refine d3_rem (b := 512) rfl (by decide) ?_; intro i31 hi31
            refine d3_idx (c := 512) rfl hi31 ?_; intro i32
            refine d3_rem (b := 32) rfl (by decide) ?_; intro ls hls'
            refine d3_add (a := 257) rfl rfl (by have := d3_max_ge; clear * - hls' this; omega) ?_; intro i34 hi34
            have hi34' : i34.val < 320 := by clear * - hi34 hls'; omega
            refine d3_idx (c := 320) rfl hi34' ?_; intro i35
            refine d3_upd (c := 320) rfl hi34' ?_; intro a9 _
            refine d3_bind (dsym_spec _ _) ?_; intro i37 _
            refine d3_rem (b := 32) rfl (by decide) ?_; intro ds hds
            refine d3_idx (c := 32) rfl hds ?_; intro i38
            refine d3_upd (c := 32) rfl hds ?_; intro a10 _
            refine d3_add rfl rfl (by clear * - hb4 hic hS; omega) ?_; intro «end» hend
            refine d3_bind (Q := fun (x : Std.Usize) => x.val ≤ «end».val ∧ x.val ≤ lim.val) ?_ ?_
            · apply dp_ite_spec <;> intro h
              · have h' : lim.val < «end».val := (UScalar.lt_equiv _ _).mp h
                exact d3_ok ⟨Nat.le_of_lt h', Nat.le_refl _⟩
              · have h' : ¬ (lim.val < «end».val) := (UScalar.lt_equiv _ _).not.mp h
                exact d3_ok ⟨Nat.le_refl _, (by clear * - h'; omega : «end».val ≤ lim.val)⟩
            rintro end1 ⟨he1, he2⟩
            have hE : i'.val ≤ «end».val := by clear * - hend; omega
            refine d3_bind (insert_range_spec _ _ _ _ _ _ _ _ _ «end».val (LeAll_mono hL3 hE) (LeAll_mono hL4 hE)
              (LeAll_mono hL7 hE) (by clear * - he1; omega) (by clear * - he2 hlim hn hS; omega)) ?_
            rintro ⟨head33, head43, prev43, head73, prev73⟩ ⟨hr3, hr4, hr7⟩
            iterate 4 refine d3_unc ?_
            refine d3_bind (open_chunk_spec _ _ (by clear * - hend hb4 hic hS; omega)) ?_; intro pa4 _
            exact d3_ok ⟨Nat.le_refl _, (by clear * - hend hb3; omega : i'.val < «end».val),
              (by clear * - hend hb4 hcap2; omega : «end».val ≤ n.val), (by decide : 0 < 512), hr3, hr4, hr7⟩
          · have h14 : i'.val < i4.val := by clear * - hi4; omega
            refine d3_bind (d_relax_spec _ _ _ _ _ _ _ _ _ _ _ _ _ hnx hilt hS) ?_; intro pa4 _
            exact d3_ok ⟨(by clear * - hs' h14; omega : s'.val ≤ i4.val), h14,
              (by clear * - hi4 hlt' hlim; omega : i4.val ≤ n.val), hcl2,
              LeAll_mono hL3 (Nat.le_of_lt h14), LeAll_mono hL4 (Nat.le_of_lt h14), LeAll_mono hL7 (Nat.le_of_lt h14)⟩
        rintro ⟨v, a, a1, a2, a3, a4, a5, a6, a7, a8, i21, i22, i23⟩ ⟨hv1, hv2, hv3, hv4, hv5, hv6, hv7⟩
        iterate 12 refine d3_unc ?_
        exact d3_ok ⟨hv1, hv2, hv3, hv4, hv5, hv6, hv7⟩
    rintro ⟨plan1, rs1, head32, head42, prev42, head72, prev72, pa3, tb1, lf1, df1, s1, cands1, pc1, pn1, ppos1,
      cl1, cd1, cdc1, i12, anchor1, alen1⟩ ⟨hs1, hii, hin1, hcl1, hk3, hk4, hk7⟩
    iterate 21 refine d3_unc ?_
    have hs1 : s1.val ≤ i12.val := hs1
    have hii : i'.val < i12.val := hii
    have hin1 : i12.val ≤ n.val := hin1
    have hms : lim.val - i12.val < lim.val - i'.val := by clear * - hii hlt'; omega
    have h12M : i12.val + 2147483648 ≤ Std.Usize.max := by clear * - hin1 hn hS; omega
    refine d3_sub rfl rfl hs1 ?_; intro i13 _
    refine d3_bind (Q := fun (x : alloc.vec.Vec Std.U32 × Array Std.U64 8192#usize × Array Std.U32 8192#usize ×
        Array Std.U32 320#usize × Array Std.U32 32#usize × Std.Usize) => x.2.2.2.2.2.val ≤ i12.val) ?_ ?_
    · apply dp_ite_spec <;> intro _
      · refine d3_bind (backtrack_spec _ _ _ _ _ _ _ _ _ _ hs1 (by clear * - h12M; omega)) ?_
        rintro ⟨plan3, lf3, df3, tb3⟩ _
        iterate 3 refine d3_unc ?_
        refine d3_bind (open_chunk_spec _ _ (by clear * - h12M; omega)) ?_; intro pa5 _
        exact d3_ok (Nat.le_refl _)
      · exact d3_ok hs1
    rintro ⟨plan2, pa4, tb2, lf2, df2, s2⟩ hs2
    have hs2 : s2.val ≤ i12.val := hs2
    iterate 5 refine d3_unc ?_
    apply dp_ite_spec <;> intro _
    · refine d3_add rfl rfl (by have hU := dp_UPD_bound; clear * - h12M hU; omega) ?_; intro next_upd1 _
      refine d3_bind (update_costs_spec _ _ _ _ _ _ _ hls) ?_
      rintro ⟨lf3, df3, litc1, lc1, dcc1⟩ _
      iterate 4 refine d3_unc ?_
      refine d3_bind (dsym_spec _ _) ?_; intro i14 _
      refine d3_rem (b := 32) rfl (by decide) ?_; intro i15 hi15
      refine d3_idx (c := 32) rfl hi15 ?_; intro cdc2
      exact d3_ok ⟨⟨hs2, hin1, hcl1, hk3, hk4, hk7⟩, hms⟩
    · exact d3_ok ⟨⟨hs2, hin1, hcl1, hk3, hk4, hk7⟩, hms⟩
  · exact ⟨hsi, hin, hcl, h3, h4, h7⟩

@[local step]
theorem d_parse_spec (input : Slice Std.U8) (plan rs)
    (ct lazyn d4 d7 skip h3d flen tbmax lz2max dupmode fback d7l d7e nice : Std.Usize)
    (h16 : 16 ≤ input.length) (hN : input.length + input.length ≤ Std.Usize.max) :
    slot.d_parse input plan rs ct lazyn d4 d7 skip h3d flen tbmax lz2max dupmode fback d7l d7e nice
      ⦃ fun _ => True ⦄ := by
  have hl := Slice.len_val input
  have hM := d3_max_ge
  have hk := dp_KB7_bound
  rw [slot.d_parse]
  refine d3_bind (fill_tables_spec _ _ (dp_LeAll_repeat _ _ _ (Nat.zero_le _))) ?_
  rintro ⟨lsym1, dtab1⟩ hls
  have hls : LeAll lsym1.val 28 := hls
  refine d3_unc ?_
  refine d3_bind (d_fill_nextl_spec _ _ _) ?_; intro nextl1 hnx
  refine d3_bind (init_counts_spec _ _ _ hN) ?_; rintro ⟨lf1, df1⟩ _
  refine d3_unc ?_
  refine d3_bind (make_costs_spec _ _ _ _ _ _ _ hls) ?_; rintro ⟨litc1, lc1, dcc1⟩ _
  iterate 2 refine d3_unc ?_
  refine d3_bind (halve_spec _ _) ?_; rintro ⟨lf2, df2⟩ _
  refine d3_unc ?_
  refine d3_bind (halve_spec _ _) ?_; rintro ⟨lf3, df3⟩ _
  refine d3_unc ?_
  refine d3_sub (b := 8) rfl rfl (by clear * - hl h16; omega) ?_; intro lim hlim
  refine d3_bind (U32.mul_spec (by
    have := U32.max_eq
    show 8 * slot.KB7.val ≤ U32.max
    clear * - hk this; omega)) ?_
  intro i hi
  have hi : i.val = 8 * slot.KB7.val := hi
  refine d3_bind (U32.sub_spec (by show i.val ≤ 64; clear * - hi hk; omega)) ?_; intro sh7 _
  refine d3_bind (open_chunk_spec _ _ (by show 0 + 259 ≤ Std.Usize.max; clear * - hM; omega)) ?_; intro pa1 _
  refine d3_bind (d_parse_loop_spec (hn := hl) (hlim := hlim) (hN := hN) (hls := hls) (hnx := hnx)
    (hsi := Nat.le_refl _) (hin := Nat.zero_le _) (hcl := by decide)
    (h3 := dp_LeAll_repeat _ _ _ (Nat.le_refl _)) (h4 := dp_LeAll_repeat _ _ _ (Nat.le_refl _))
    (h7 := dp_LeAll_repeat _ _ _ (Nat.le_refl _)) ..) ?_
  rintro ⟨plan1, rs1, pa2, tb1, lf4, df4, s, i1⟩ _
  iterate 7 refine d3_unc ?_
  apply dp_ite_spec <;> intro _
  · apply dp_ite_spec <;> intro hin
    · have hin' : i1.val ≤ input.len.val := (UScalar.le_equiv _ _).mp hin
      refine d3_bind (Q := fun (e : Std.Usize) => e.val ≤ input.len.val) ?_ ?_
      · apply dp_ite_spec <;> intro _
        · exact d3_ok hin'
        · exact d3_ok (by clear * - hlim; omega : lim.val ≤ input.len.val)
      intro e he
      apply dp_ite_spec <;> intro hes
      · have hes' : s.val < e.val := (UScalar.lt_equiv _ _).mp hes
        refine d3_bind (backtrack_spec _ _ _ _ _ _ _ _ _ _ (Nat.le_of_lt hes')
          (by clear * - he hl hN h16; omega)) ?_
        rintro ⟨plan2, x1, x2, x3⟩ _
        iterate 3 refine d3_unc ?_
        exact d3_ok trivial
      · exact d3_ok trivial
    · exact d3_ok trivial
  · exact d3_ok trivial

@[local step]
theorem d_plan_k_loop_spec (input : Slice Std.U8) (out : Slice Std.U32) (k) (n : Std.Usize) (plan rs lsym dtab)
    (passes pass : Std.Usize) :
    slot.d_plan_k_loop input out k n plan rs lsym dtab passes pass ⦃ fun r => r.2.length = out.length ⦄ := by
  rw [slot.d_plan_k_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, pass') => passes.val - pass'.val)
    (inv := fun (out', _, _) => out'.length = out.length)
  · rintro ⟨out', plan', pass'⟩ hinv'
    simp only [slot.d_plan_k_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · rfl

@[local step]
theorem d_plan_k_spec (input : Slice Std.U8) (out : Slice Std.U32) (k) :
    slot.d_plan_k input out k ⦃ fun r => r.2.length = out.length ⦄ := by
  have z8 : LeAll (Array.repeat 512#usize 0#u8).val 28 := dp_LeAll_repeat _ _ _ (by simp)
  rw [slot.d_plan_k]
  step*
  repeat' (split <;> step*)
  all_goals first
    | scalar_tac
    | (have hw := dp_wadd_self input.len (by rw [← i2_post]; scalar_tac)
       simpa using hw)

@[local step]
theorem d_plan_spec (input : Slice Std.U8) (out : Slice Std.U32) (dk : Std.Usize) :
    slot.d_plan input out dk ⦃ fun r => r.2.length = out.length ⦄ := by
  rw [slot.d_plan]
  step*

theorem a_ite_spec {α : Type} (c : Prop) [Decidable c] (a b : α) (P : α → Prop) (ha : P a) (hb : P b) :
    (if c then (ok a : Result α) else ok b) ⦃ P ⦄ := by
  split <;> simpa [Std.WP.spec_ok]

theorem a_ite_dspec {α : Type} (c : Prop) [Decidable c] (a b : α) (P : α → Prop) (ha : c → P a)
    (hb : ¬c → P b) : (if c then (ok a : Result α) else ok b) ⦃ P ⦄ := by
  split
  · simpa [Std.WP.spec_ok] using ha (by assumption)
  · simpa [Std.WP.spec_ok] using hb (by assumption)

@[irreducible] def a_word8 (input : Slice Std.U8) (p : Nat) : Nat :=
  (input.val[p]!).val * 2^56 + (input.val[p + 1]!).val * 2^48 + (input.val[p + 2]!).val * 2^40
    + (input.val[p + 3]!).val * 2^32 + (input.val[p + 4]!).val * 2^24
    + (input.val[p + 5]!).val * 2^16 + (input.val[p + 6]!).val * 2^8 + (input.val[p + 7]!).val

theorem a_u8_lt (x : Std.U8) : x.val < 256 := by (subst_vars; scalar_tac (simpAllMaxSteps := 0))

theorem a_word8_digit (input : Slice Std.U8) (p k : Nat) (hk : k < 8) :
    (input.val[p + k]!).val = a_word8 input p / 256 ^ (7 - k) % 256 := by
  have := a_u8_lt (input.val[p]!); have := a_u8_lt (input.val[p+1]!)
  have := a_u8_lt (input.val[p+2]!); have := a_u8_lt (input.val[p+3]!)
  have := a_u8_lt (input.val[p+4]!); have := a_u8_lt (input.val[p+5]!)
  have := a_u8_lt (input.val[p+6]!); have := a_u8_lt (input.val[p+7]!)
  simp only [a_word8]
  rcases (show k = 0 ∨ k = 1 ∨ k = 2 ∨ k = 3 ∨ k = 4 ∨ k = 5 ∨ k = 6 ∨ k = 7 by omega) with
    rfl | rfl | rfl | rfl | rfl | rfl | rfl | rfl <;> simp only [Nat.add_zero, Nat.pow_zero, Nat.pow_succ, Nat.one_mul,
    Nat.sub_self, Nat.reduceSub] <;> omega

theorem a_word8_prefix (input : Slice Std.U8) (a b d : Nat) (hd : d ≤ 8)
    (h : a_word8 input a / 2 ^ (64 - 8 * d) = a_word8 input b / 2 ^ (64 - 8 * d)) :
    ∀ k, k < d → input.val[b + k]! = input.val[a + k]! := by
  intro k hk
  have e : (256 : Nat) ^ (7 - k) = 2 ^ (64 - 8 * d) * 2 ^ (8 * (d - 1 - k)) := by
    rw [← pow_add, show (256 : Nat) = 2 ^ 8 by norm_num, ← pow_mul]
    congr 1; omega
  have key : a_word8 input a / 256 ^ (7 - k) = a_word8 input b / 256 ^ (7 - k) := by
    rw [e, ← Nat.div_div_eq_div_mul, ← Nat.div_div_eq_div_mul, h]
  have ha := a_word8_digit input a k (by omega)
  have hb := a_word8_digit input b k (by omega)
  rw [key] at ha
  (subst_vars; scalar_tac (simpAllMaxSteps := 0))

theorem Matches.a_add_prefix {input : Slice Std.U8} {a b l d : Nat} (h : Matches input a b l)
    (hd : d ≤ 8)
    (hw : a_word8 input (a + l) / 2 ^ (64 - 8 * d) = a_word8 input (b + l) / 2 ^ (64 - 8 * d)) :
    Matches input a b (l + d) := by
  intro k hk
  by_cases hkl : k < l
  · exact h k hkl
  · have := a_word8_prefix input (a + l) (b + l) d hd hw (k - l) (by omega)
    rw [show b + l + (k - l) = b + k by omega, show a + l + (k - l) = a + k by omega] at this
    exact this

theorem a_or_eq_add_of_mod {x t : Nat} (m : Nat) (hx : x % 2 ^ m = 0) (ht : t < 2 ^ m) :
    x ||| t = x + t := by
  have h := Nat.two_pow_add_eq_or_of_lt ht (x / 2 ^ m)
  have hx' : 2 ^ m * (x / 2 ^ m) = x := by
    have := Nat.div_add_mod x (2 ^ m); omega
  rw [hx'] at h
  exact h.symm

theorem a_shl_byte {x : Nat} (k : Nat) (hx : x < 256) (hk : k ≤ 56) :
    x <<< k % U64.size = x * 2 ^ k := by
  rw [Nat.shiftLeft_eq, U64.size_def]
  apply Nat.mod_eq_of_lt
  have : 2 ^ k ≤ 2 ^ 56 := Nat.pow_le_pow_right (by norm_num) hk
  have : x * 2 ^ k < 256 * 2 ^ 56 := by
    calc x * 2 ^ k < 256 * 2 ^ k := by
          apply Nat.mul_lt_mul_of_pos_right hx (Nat.two_pow_pos _)
      _ ≤ 256 * 2 ^ 56 := Nat.mul_le_mul_left _ this
  simp only [U64.numBits] at *
  omega

theorem a_be8_nat {a b c d e f g h : Nat} (ha : a < 256) (hb : b < 256) (hc : c < 256)
    (hd : d < 256) (he : e < 256) (hf : f < 256) (hg : g < 256) (hh : h < 256) :
    (a <<< 56 % U64.size ||| b <<< 48 % U64.size ||| c <<< 40 % U64.size |||
      d <<< 32 % U64.size ||| e <<< 24 % U64.size ||| f <<< 16 % U64.size |||
      g <<< 8 % U64.size ||| h) =
    a * 2^56 + b * 2^48 + c * 2^40 + d * 2^32 + e * 2^24 + f * 2^16 + g * 2^8 + h := by
  rw [a_shl_byte 56 ha (by norm_num), a_shl_byte 48 hb (by norm_num), a_shl_byte 40 hc (by norm_num),
    a_shl_byte 32 hd (by norm_num), a_shl_byte 24 he (by norm_num), a_shl_byte 16 hf (by norm_num),
    a_shl_byte 8 hg (by norm_num)]
  rw [a_or_eq_add_of_mod 56 (x := a * 2^56) (t := b * 2^48) (by omega) (by omega)]
  rw [a_or_eq_add_of_mod 48 (x := a * 2^56 + b * 2^48) (t := c * 2^40) (by omega) (by omega)]
  rw [a_or_eq_add_of_mod 40 (x := a * 2^56 + b * 2^48 + c * 2^40) (t := d * 2^32) (by omega)
    (by omega)]
  rw [a_or_eq_add_of_mod 32 (x := a * 2^56 + b * 2^48 + c * 2^40 + d * 2^32) (t := e * 2^24)
    (by omega) (by omega)]
  rw [a_or_eq_add_of_mod 24 (x := a * 2^56 + b * 2^48 + c * 2^40 + d * 2^32 + e * 2^24)
    (t := f * 2^16) (by omega) (by omega)]
  rw [a_or_eq_add_of_mod 16
    (x := a * 2^56 + b * 2^48 + c * 2^40 + d * 2^32 + e * 2^24 + f * 2^16)
    (t := g * 2^8) (by omega) (by omega)]
  rw [a_or_eq_add_of_mod 8
    (x := a * 2^56 + b * 2^48 + c * 2^40 + d * 2^32 + e * 2^24 + f * 2^16 + g * 2^8)
    (t := h) (by omega) (by omega)]

@[local step]
theorem a_be8_spec (s : Slice Std.U8) (i : Std.Usize) (h : i.val + 8 ≤ s.length) :
    slot.a_be8 s i ⦃ fun v => v.val = a_word8 s i.val ⦄ := by
  rw [slot.a_be8]
  step*
  simp only [← getElem!_pos] at *
  simp_all only [UScalar.val_or, U8.cast_U64_val_eq]
  rw [a_be8_nat (a_u8_lt _) (a_u8_lt _) (a_u8_lt _) (a_u8_lt _) (a_u8_lt _) (a_u8_lt _) (a_u8_lt _) (a_u8_lt _)]
  simp only [a_word8]

theorem a_nat_xor_eq_zero {a b : Nat} (h : a ^^^ b = 0) : a = b := by
  have : a ^^^ (a ^^^ b) = b := by rw [← Nat.xor_assoc, Nat.xor_self, Nat.zero_xor]
  rw [h, Nat.xor_zero] at this; exact this

theorem a_div_eq_of_xor_lt {x y m : Nat} (hz : x ^^^ y < 2 ^ m) : x / 2 ^ m = y / 2 ^ m := by
  have h : (x ^^^ y) >>> m = 0 := by rw [Nat.shiftRight_eq_div_pow]; exact Nat.div_eq_of_lt hz
  rw [Nat.shiftRight_xor_distrib] at h
  have := a_nat_xor_eq_zero h
  simpa [Nat.shiftRight_eq_div_pow] using this

theorem a_lt_pow_leadingZeros (z : BitVec 64) :
    z.toNat < 2 ^ (64 - 8 * (BitVec.leadingZeros z / 8)) := by
  unfold BitVec.leadingZeros
  split
  case isTrue h => subst h; simp
  case isFalse h =>
    have hz : z.toNat ≠ 0 := by
      intro h0; apply h; exact BitVec.eq_of_toNat_eq (by simpa using h0)
    have hlog : Nat.log 2 z.toNat < 64 := Nat.log_lt_of_lt_pow hz z.isLt
    have h1 : z.toNat < 2 ^ (Nat.log 2 z.toNat).succ := Nat.lt_pow_succ_log_self (by norm_num) _
    refine lt_of_lt_of_le h1 (Nat.pow_le_pow_right (by norm_num) ?_)
    omega

theorem a_leadingZeros_lt_of_ne (z : BitVec 64) (h : z ≠ 0) : BitVec.leadingZeros z < 64 := by
  unfold BitVec.leadingZeros
  simp only [h, if_false]
  omega

theorem a_lz_spec (x : Std.U64) :
    lift (core.num.U64.leading_zeros x) ⦃ fun r => r = core.num.U64.leading_zeros x ∧ r.val ≤ 64 ⦄ := by
  simp only [lift, Std.WP.spec_ok, true_and]
  have hle : BitVec.leadingZeros x.bv ≤ 64 := by unfold BitVec.leadingZeros; split <;> omega
  simp only [core.num.U64.leading_zeros, UScalar.val, UScalarTy.U32_numBits_eq,
    BitVec.natCast_eq_ofNat, BitVec.toNat_ofNat, Nat.reducePow]
  omega

theorem a_lz_val (x : Std.U64) :
    (core.num.U64.leading_zeros x).val = BitVec.leadingZeros x.bv := by
  have hle : BitVec.leadingZeros x.bv ≤ 64 := by unfold BitVec.leadingZeros; split <;> omega
  simp only [core.num.U64.leading_zeros, UScalar.val, UScalarTy.U32_numBits_eq,
    BitVec.natCast_eq_ofNat, BitVec.toNat_ofNat, Nat.reducePow]
  omega

theorem Matches.a_word_lz {input : Slice Std.U8} {a b k : Nat} {pa pb r k1 : Std.Usize}
    {x y z : Std.U64} {lz q : Std.U32}
    (h : Matches input a b k) (hpa : pa.val = a + k) (hpb : pb.val = b + k)
    (hx : x.val = a_word8 input pa.val) (hy : y.val = a_word8 input pb.val)
    (hz : z.val = (x ^^^ y).val) (hz0 : ¬z = 0#u64) (hlz : lz = core.num.U64.leading_zeros z)
    (hq : q.val = lz.val / 8) (hr : r = UScalar.cast .Usize q) (hk1 : k1.val = k + r.val) :
    Matches input a b k1.val ∧ k1.val < k + 8 := by
  have hbv : z.bv ≠ 0 := by
    intro h0; apply hz0; exact UScalar.eq_of_val_eq (by simp [UScalar.val, h0])
  have hlt : BitVec.leadingZeros z.bv < 64 := a_leadingZeros_lt_of_ne z.bv hbv
  have hrv : r.val = BitVec.leadingZeros z.bv / 8 := by
    rw [hr, U32.cast_Usize_val_eq, hq, hlz, a_lz_val]
  rw [hpa] at hx; rw [hpb] at hy
  refine ⟨?_, by omega⟩
  rw [hk1, hrv]
  have hle : BitVec.leadingZeros z.bv ≤ 64 := by unfold BitVec.leadingZeros; split <;> omega
  apply Matches.a_add_prefix h (by omega)
  rw [← hx, ← hy]
  apply a_div_eq_of_xor_lt
  rw [← UScalar.val_xor, ← hz]
  exact a_lt_pow_leadingZeros z.bv

theorem Matches.a_word_zero {input : Slice Std.U8} {a b k : Nat} {pa pb k1 : Std.Usize}
    {x y z : Std.U64}
    (h : Matches input a b k) (hpa : pa.val = a + k) (hpb : pb.val = b + k)
    (hx : x.val = a_word8 input pa.val) (hy : y.val = a_word8 input pb.val)
    (hz : z.val = (x ^^^ y).val) (hz0 : z = 0#u64) (hk1 : k1.val = k + 8) :
    Matches input a b k1.val := by
  have hxy : x.val = y.val := by
    apply a_nat_xor_eq_zero
    rw [← UScalar.val_xor, ← hz, hz0]; rfl
  rw [hpa] at hx; rw [hpb] at hy
  rw [hk1]
  apply Matches.a_add_prefix h (le_refl 8)
  rw [← hx, ← hy, hxy]

theorem Matches.a_byte' {input : Slice Std.U8} {a b l : Nat} {pa pb l1 : Std.Usize}
    {x y : Std.U8} (h : Matches input a b l) (hpa : pa.val = a + l) (hpb : pb.val = b + l)
    (hpa' : pa.val < input.val.length) (hpb' : pb.val < input.val.length)
    (hx : x = input.val[pa.val]) (hy : y = input.val[pb.val]) (hxy : x = y)
    (hl1 : l1.val = l + 1) : Matches input a b l1.val := by
  rw [hl1]
  apply LZ77.Matches.succ h
  rw [← hpa, ← hpb, getElem!_pos input.val pa.val hpa', getElem!_pos input.val pb.val hpb',
    ← hx, ← hy, hxy]

attribute [local step] a_lz_spec in
theorem a_common_loop0_spec (s : Slice Std.U8) (a b cap k : Std.Usize) (run : Std.U32)
    (ha : a.val + cap.val ≤ s.length) (hb : b.val + cap.val ≤ s.length) (hcap : cap.val ≤ 258)
    (hk : k.val ≤ cap.val) (hm : Matches s a.val b.val k.val) :
    slot.a_common_loop0 s a b cap k run ⦃ fun r =>
      r.1.val ≤ cap.val ∧ Matches s a.val b.val r.1.val ⦄ := by
  rw [slot.a_common_loop0]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  apply Std.loop.spec_decr_nat
    (measure := fun r => cap.val - r.1.val + r.2.val)
    (inv := fun r => r.1.val ≤ cap.val ∧ Matches s a.val b.val r.1.val)
  · rintro ⟨k, run⟩ ⟨hk, hm⟩
    simp only at hk hm
    simp only [slot.a_common_loop0.body]
    step*
    all_goals first
      | (subst_vars; scalar_tac (simpAllMaxSteps := 0))
      | (refine ⟨by (subst_vars; scalar_tac (simpAllMaxSteps := 0)), Matches.a_word_zero hm (by assumption) (by assumption)
          (by assumption) (by assumption) (by assumption) (by assumption) (by (subst_vars; scalar_tac (simpAllMaxSteps := 0))),
          by (subst_vars; scalar_tac (simpAllMaxSteps := 0))⟩)
      | (have hw := Matches.a_word_lz hm (by assumption) (by assumption) (by assumption)
          (by assumption) (by assumption) (by assumption) (by assumption) (by assumption)
          (by assumption) (by assumption)
         refine ⟨by (subst_vars; scalar_tac (simpAllMaxSteps := 0)), hw.1, by (subst_vars; scalar_tac (simpAllMaxSteps := 0))⟩)
  · exact ⟨hk, hm⟩

theorem a_common_loop1_spec (s : Slice Std.U8) (a b cap k : Std.Usize) (run : Std.U32)
    (ha : a.val + cap.val ≤ s.length) (hb : b.val + cap.val ≤ s.length)
    (hk : k.val ≤ cap.val) (hm : Matches s a.val b.val k.val) :
    slot.a_common_loop1 s a b cap k run ⦃ fun r =>
      r.val ≤ cap.val ∧ Matches s a.val b.val r.val ⦄ := by
  rw [slot.a_common_loop1]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  apply Std.loop.spec_decr_nat
    (measure := fun r => cap.val - r.1.val + r.2.val)
    (inv := fun r => r.1.val ≤ cap.val ∧ Matches s a.val b.val r.1.val)
  · rintro ⟨k, run⟩ ⟨hk, hm⟩
    simp only at hk hm
    simp only [slot.a_common_loop1.body]
    step*
    all_goals first
      | (subst_vars; scalar_tac (simpAllMaxSteps := 0))
      | exact ⟨hk, hm⟩
      | (refine ⟨by (subst_vars; scalar_tac (simpAllMaxSteps := 0)), Matches.a_byte' hm (by assumption) (by assumption) (by (subst_vars; scalar_tac (simpAllMaxSteps := 0)))
          (by (subst_vars; scalar_tac (simpAllMaxSteps := 0))) (by assumption) (by assumption) (by assumption) (by assumption),
          by (subst_vars; scalar_tac (simpAllMaxSteps := 0))⟩)
  · exact ⟨hk, hm⟩

@[local step]
theorem a_common_spec (s : Slice Std.U8) (a b cap : Std.Usize)
    (ha : a.val + cap.val ≤ s.length) (hb : b.val + cap.val ≤ s.length) (hcap : cap.val ≤ 258) :
    slot.a_common s a b cap ⦃ fun l => l.val ≤ cap.val ∧ Matches s a.val b.val l.val ⦄ := by
  rw [slot.a_common]
  apply Std.WP.spec_bind (a_common_loop0_spec s a b cap 0#usize 1#u32 ha hb hcap (by simp)
    (LZ77.Matches.zero s a.val b.val))
  rintro ⟨k, run⟩ ⟨hk, hm⟩
  exact a_common_loop1_spec s a b cap k run ha hb hk hm

theorem Matches.a_mono_eq {input : Slice Std.U8} {a b n m : Nat} (h : Matches input a b n)
    (hm : m = n) : Matches input a b m := by subst hm; exact h

theorem Matches.a_word_eq {input : Slice Std.U8} {a b k : Nat} {pa pb k1 : Std.Usize}
    {x y : Std.U64}
    (h : Matches input a b k) (hpa : pa.val = a + k) (hpb : pb.val = b + k)
    (hx : x.val = a_word8 input pa.val) (hy : y.val = a_word8 input pb.val)
    (hxy : x = y) (hk1 : k1.val = k + 8) :
    Matches input a b k1.val := by
  rw [hpa] at hx; rw [hpb] at hy
  rw [hk1]
  apply Matches.a_add_prefix h (le_refl 8)
  rw [← hx, ← hy, hxy]

theorem a_same_loop0_spec (s : Slice Std.U8) (a b len k ok : Std.Usize)
    (ha : a.val + len.val ≤ s.length) (hb : b.val + len.val ≤ s.length) (hlen : len.val ≤ 258)
    (hk : k.val ≤ len.val) (hm : Matches s a.val b.val k.val) :
    slot.a_same_loop0 s a b len k ok ⦃ fun r =>
      r.1.val ≤ len.val ∧ Matches s a.val b.val r.1.val ∧ (r.2.val = 1 → len.val < r.1.val + 8) ⦄ := by
  rw [slot.a_same_loop0]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  apply Std.loop.spec_decr_nat
    (measure := fun r => len.val - r.1.val + r.2.val)
    (inv := fun r => r.1.val ≤ len.val ∧ Matches s a.val b.val r.1.val)
  · rintro ⟨k, ok⟩ ⟨hk, hm⟩
    simp only at hk hm
    simp only [slot.a_same_loop0.body]
    step*
    all_goals first
      | (subst_vars; scalar_tac (simpAllMaxSteps := 0))
      | (refine ⟨by (subst_vars; scalar_tac (simpAllMaxSteps := 0)), Matches.a_word_eq hm (by assumption) (by assumption)
          (by assumption) (by assumption) (by assumption) (by (subst_vars; scalar_tac (simpAllMaxSteps := 0))), by (subst_vars; scalar_tac (simpAllMaxSteps := 0))⟩)
  · exact ⟨hk, hm⟩

@[local step]
theorem a_same_loop1_spec (s : Slice Std.U8) (a b len k ok : Std.Usize)
    (ha : a.val + len.val ≤ s.length) (hb : b.val + len.val ≤ s.length)
    (hk : k.val ≤ len.val) (hm : Matches s a.val b.val k.val) :
    slot.a_same_loop1 s a b len k ok ⦃ fun r => r.val = 1 → Matches s a.val b.val len.val ⦄ := by
  rw [slot.a_same_loop1]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  apply Std.loop.spec_decr_nat
    (measure := fun r => len.val - r.1.val + r.2.val)
    (inv := fun r => r.1.val ≤ len.val ∧ Matches s a.val b.val r.1.val)
  · rintro ⟨k, ok⟩ ⟨hk, hm⟩
    simp only at hk hm
    simp only [slot.a_same_loop1.body]
    step*
    all_goals first
      | (subst_vars; scalar_tac (simpAllMaxSteps := 0))
      | (refine ⟨by (subst_vars; scalar_tac (simpAllMaxSteps := 0)), Matches.a_byte' hm (by assumption) (by assumption) (by (subst_vars; scalar_tac (simpAllMaxSteps := 0)))
          (by (subst_vars; scalar_tac (simpAllMaxSteps := 0))) (by assumption) (by assumption) (by assumption) (by assumption),
          by (subst_vars; scalar_tac (simpAllMaxSteps := 0))⟩)
  · exact ⟨hk, hm⟩

@[local step]
theorem a_same_loop2_spec (s : Slice Std.U8) (a b len k ok : Std.Usize)
    (ha : a.val + len.val ≤ s.length) (hb : b.val + len.val ≤ s.length)
    (hk : k.val ≤ len.val) (hm : Matches s a.val b.val k.val) :
    slot.a_same_loop2 s a b len k ok ⦃ fun r => r.val = 1 → Matches s a.val b.val len.val ⦄ := by
  rw [slot.a_same_loop2]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  apply Std.loop.spec_decr_nat
    (measure := fun r => len.val - r.1.val + r.2.val)
    (inv := fun r => r.1.val ≤ len.val ∧ Matches s a.val b.val r.1.val)
  · rintro ⟨k, ok⟩ ⟨hk, hm⟩
    simp only at hk hm
    simp only [slot.a_same_loop2.body]
    step*
    all_goals first
      | (subst_vars; scalar_tac (simpAllMaxSteps := 0))
      | (refine ⟨by (subst_vars; scalar_tac (simpAllMaxSteps := 0)), Matches.a_byte' hm (by assumption) (by assumption) (by (subst_vars; scalar_tac (simpAllMaxSteps := 0)))
          (by (subst_vars; scalar_tac (simpAllMaxSteps := 0))) (by assumption) (by assumption) (by assumption) (by assumption),
          by (subst_vars; scalar_tac (simpAllMaxSteps := 0))⟩)
  · exact ⟨hk, hm⟩

theorem Matches.a_mask {input : Slice Std.U8} {a b k len : Nat} {pa pb : Std.Usize}
    {x y z w : Std.U64} {sh : Std.U32}
    (h : Matches input a b k) (hpa : pa.val = a + k) (hpb : pb.val = b + k)
    (hx : x.val = a_word8 input pa.val) (hy : y.val = a_word8 input pb.val)
    (hz : z.val = (x ^^^ y).val) (hw : w.val = z.val >>> sh.val) (hw0 : ¬(w != 0#u64) = true)
    (hsh : sh.val = 64 - 8 * (len - k)) (hk : k < len) (hlen : len < k + 8) :
    Matches input a b len := by
  have hw0 : w.val = 0 := by simpa using hw0
  rw [hpa] at hx; rw [hpb] at hy
  have := Matches.a_add_prefix (d := len - k) h (by omega) (by
    rw [← hx, ← hy, ← hsh]
    have h0 : (x.val ^^^ y.val) >>> sh.val = 0 := by rw [← UScalar.val_xor, ← hz, ← hw, hw0]
    rw [Nat.shiftRight_xor_distrib] at h0
    have := a_nat_xor_eq_zero h0
    simpa [Nat.shiftRight_eq_div_pow] using this)
  rw [show k + (len - k) = len by omega] at this
  exact this

@[local step]
theorem a_same_spec (s : Slice Std.U8) (a b len : Std.Usize)
    (ha : a.val + len.val ≤ s.length) (hb : b.val + len.val ≤ s.length) (hlen : len.val ≤ 258)
    (ha8 : a.val + len.val + 7 ≤ Std.Usize.max) (hb8 : b.val + len.val + 7 ≤ Std.Usize.max) :
    slot.a_same s a b len ⦃ fun r => r.val = 1 → Matches s a.val b.val len.val ⦄ := by
  rw [slot.a_same]
  apply Std.WP.spec_bind (a_same_loop0_spec s a b len 0#usize 1#usize ha hb hlen (by simp)
    (LZ77.Matches.zero s a.val b.val))
  rintro ⟨k, ok⟩ ⟨hk, hm, hok⟩
  simp only at hk hm hok
  step*

  intro _
  exact Matches.a_mask hm (by assumption) (by assumption) (by assumption) (by assumption)
    (by assumption) (by assumption) (by assumption) (by (subst_vars; scalar_tac (simpAllMaxSteps := 0))) (by (subst_vars; scalar_tac (simpAllMaxSteps := 0)))
    (by (subst_vars; scalar_tac (simpAllMaxSteps := 0)))

theorem a_lz32_le (x : Std.U32) (k : Nat) (hk : k < 32) (hx : 2 ^ k ≤ x.val) :
    (core.num.U32.leading_zeros x).val ≤ 31 - k := by
  have hne : x.bv ≠ 0 := by
    intro h0
    have : x.val = 0 := by simp [UScalar.val, h0]
    have : 0 < 2 ^ k := Nat.two_pow_pos k
    omega
  have hlog : k ≤ Nat.log 2 x.bv.toNat := by
    apply Nat.le_log_of_pow_le (by norm_num)
    have : x.val = x.bv.toNat := rfl
    omega
  have hle : BitVec.leadingZeros x.bv ≤ 32 := by unfold BitVec.leadingZeros; split <;> omega
  have hv : (core.num.U32.leading_zeros x).val = BitVec.leadingZeros x.bv := by
    simp only [core.num.U32.leading_zeros, UScalar.val, UScalarTy.U32_numBits_eq,
      BitVec.natCast_eq_ofNat, BitVec.toNat_ofNat, Nat.reducePow]
    omega
  rw [hv]
  unfold BitVec.leadingZeros
  simp only [hne, if_false]
  omega

theorem a_lz32_spec (x : Std.U32) :
    lift (core.num.U32.leading_zeros x) ⦃ fun r => r = core.num.U32.leading_zeros x ∧
      (4 ≤ x.val → r.val ≤ 29) ∧ (8 ≤ x.val → r.val ≤ 28) ⦄ := by
  simp only [lift, Std.WP.spec_ok, true_and]
  exact ⟨fun h => a_lz32_le x 2 (by norm_num) (by simpa using h),
    fun h => a_lz32_le x 3 (by norm_num) (by simpa using h)⟩

theorem a_hcast_I32_spec {ty : UScalarTy} (x : UScalar ty) (h : x.val ≤ 2147483647) :
    lift (UScalar.hcast .I32 x) ⦃ fun y => y.val = x.val ⦄ :=
  UScalar.hcast_inBounds_spec .I32 x (by simp [I32.max_def, I32.numBits]; omega)

theorem a_hcast_I32_val {ty : UScalarTy} (x : UScalar ty) (h : x.val ≤ 2147483647) :
    (UScalar.hcast .I32 x).val = x.val := by
  have := a_hcast_I32_spec x h
  simpa [lift] using this

theorem a_GBASE_bound : -500000000 ≤ slot.A_GBASE.val ∧ slot.A_GBASE.val ≤ 500000000 := by
  unfold slot.A_GBASE
  simp

theorem a_L2B_bound : -500000000 ≤ slot.A_L2B.val ∧ slot.A_L2B.val ≤ 500000000 := by
  unfold slot.A_L2B
  simp

theorem a_prod_bound {i hlit : Int} {l : Nat} (hi : i = (l : Int)) (hl : l ≤ 258) (h0 : 0 ≤ hlit)
    (h1 : hlit ≤ 1000000) : 0 ≤ i * hlit ∧ i * hlit ≤ 258000000 := by
  subst hi
  refine ⟨Int.mul_nonneg (by omega) h0, ?_⟩
  calc (l : Int) * hlit ≤ 258 * hlit := Int.mul_le_mul_of_nonneg_right (by omega) h0
    _ ≤ 258000000 := by omega

attribute [local step] a_lz32_spec a_hcast_I32_spec in
theorem a_gain_spec (l d : Std.Usize) (hlit : Std.I32) (hl : l.val ≤ 258) (hd : d.val ≤ 32768)
    (hh0 : 0 ≤ hlit.val) (hh1 : hlit.val ≤ 1000000) :
    slot.a_gain l d hlit ⦃ fun r => -1000000000 ≤ r.val ∧ r.val ≤ 1000000000 ⦄ := by
  rw [slot.a_gain]
  have ⟨hG0, hG1⟩ := a_GBASE_bound

  apply WP.spec_bind (Pₘ := fun (c : Std.I32) =>
    slot.A_GBASE.val ≤ c.val ∧ c.val ≤ slot.A_GBASE.val + 464)
  · repeat' (split <;> step*)
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  intro c hc
  apply WP.spec_bind (Pₘ := fun (c1 : Std.I32) =>
    slot.A_GBASE.val ≤ c1.val ∧ c1.val ≤ slot.A_GBASE.val + 944)
  · repeat' (split <;> step*)
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  intro c1 hc1
  step*
  all_goals first
    | (subst_vars; scalar_tac (simpAllMaxSteps := 0))
    | (have := a_prod_bound (by assumption) hl hh0 hh1; (subst_vars; scalar_tac (simpAllMaxSteps := 0)))

attribute [local step] a_gain_spec

def AHeadBound {N : Std.Usize} (head : Array Std.U32 N) (B : Nat) : Prop :=
  ∀ j : Nat, j < head.val.length → (head.val[j]!).val ≤ B

theorem AHeadBound.mono {N : Std.Usize} {head : Array Std.U32 N} {B B' : Nat}
    (h : AHeadBound head B) (hB : B ≤ B') : AHeadBound head B' := fun j hj => le_trans (h j hj) hB

theorem AHeadBound.init (N : Std.Usize) : AHeadBound (Std.Array.repeat N 0#u32) 0 := by
  intro j hj
  rw [Std.Array.repeat_val] at hj ⊢
  rw [List.getElem!_eq_getElem?_getD, List.getElem?_replicate_of_lt (by simpa using hj)]
  rfl

theorem AHeadBound.set {N : Std.Usize} {head : Array Std.U32 N} {B : Nat} (h : AHeadBound head B)
    (a : Std.Usize) (v : Std.U32) (hv : v.val ≤ B) : AHeadBound (head.set a v) B := by
  intro j hj
  rw [Std.Array.set_val_eq] at hj ⊢
  rw [List.length_set] at hj
  by_cases hja : a.val = j
  · subst hja
    rw [List.getElem!_eq_getElem?_getD, List.getElem?_set_self hj]
    exact hv
  · rw [List.getElem!_eq_getElem?_getD, List.getElem?_set_ne hja, ← List.getElem!_eq_getElem?_getD]
    exact h j hj

theorem AHeadBound.update {N : Std.Usize} {head head1 : Array Std.U32 N} {B : Nat}
    {a i : Std.Usize} {v : Std.U32} (h : AHeadBound head B) (hv : v = UScalar.cast .U32 i)
    (hi : i.val ≤ B) (h1 : head1 = head.set a v) : AHeadBound head1 B := by
  subst h1
  apply AHeadBound.set h a v
  rw [hv]
  have : (UScalar.cast .U32 i).val = i.val % 2 ^ 32 := by
    simp only [UScalar.cast_val_eq, UScalarTy.U32_numBits_eq]
  rw [this]
  exact le_trans (Nat.mod_le _ _) hi

theorem AHeadBound.get {N : Std.Usize} {head : Array Std.U32 N} {B : Nat} (h : AHeadBound head B)
    (a : Std.Usize) (x : Std.U32) (ha : a.val < head.val.length) (hx : x = head.val[a.val]) :
    x.val ≤ B := by
  have := h a.val ha
  rw [getElem!_pos head.val a.val ha, ← hx] at this
  exact this

theorem a_cast_usize_le {x : Std.U32} {y : Std.Usize} {B : Nat} (h : y = UScalar.cast .Usize x)
    (hx : x.val ≤ B) : y.val ≤ B := by
  rw [h, U32.cast_Usize_val_eq]; exact hx

@[local step]
theorem a_be4_spec (s : Slice Std.U8) (i : Std.Usize) (hi : i.val + 4 ≤ Std.Usize.max) :
    slot.a_be4 s i ⦃ fun _ => True ⦄ := by
  rw [slot.a_be4]
  step*

@[local step]
theorem a_insert_spec (s : Slice Std.U8) {H W : Std.Usize} (head : Array Std.U32 H)
    (prev : Array Std.U32 W) (i : Std.Usize) (mask : Std.U32) (B : Nat) (hB : AHeadBound head B)
    (hi : i.val < B + 1) (hi4 : i.val + 4 ≤ Std.Usize.max) (hH : 0 < H.val) (hW : 0 < W.val) :
    slot.a_insert s head prev i mask ⦃ fun r => r.1.val ≤ B ∧ AHeadBound r.2.1 B ⦄ := by
  rw [slot.a_insert]
  step*
  have hold : old.val ≤ B := AHeadBound.get hB a old (by (subst_vars; scalar_tac (simpAllMaxSteps := 0))) (by assumption)
  exact ⟨a_cast_usize_le (by assumption) hold,
    AHeadBound.update hB (by assumption) (by omega) (by assumption)⟩

@[local step]
theorem a_insert_dna_spec (s : Slice Std.U8) {H W : Std.Usize} (head : Array Std.U32 H)
    (prev : Array Std.U32 W) (i : Std.Usize) (mask : Std.U32) (B : Nat) (hB : AHeadBound head B)
    (hi : i.val < B + 1) (hi8 : i.val + 8 ≤ s.length) (hH : 0 < H.val) (hW : 0 < W.val) :
    slot.a_insert_dna s head prev i mask ⦃ fun r => r.1.val ≤ B ∧ AHeadBound r.2.1 B ⦄ := by
  rw [slot.a_insert_dna]
  step*
  have hold : old.val ≤ B := AHeadBound.get hB a old (by (subst_vars; scalar_tac (simpAllMaxSteps := 0))) (by assumption)
  exact ⟨a_cast_usize_le (by assumption) hold,
    AHeadBound.update hB (by assumption) (by omega) (by assumption)⟩

def ACand (s : Slice Std.U8) (p cap best bd : Nat) : Prop :=
  bd = 0 ∨ (1 ≤ bd ∧ bd ≤ 32768 ∧ bd ≤ p ∧ best ≤ cap ∧ Matches s (p - bd) p best)

theorem a_dist_of_wrapping {p c d i : Std.Usize} (hc : c.val ≤ p.val)
    (hd : d = core.num.Usize.wrapping_sub p c) (hi : i = core.num.Usize.wrapping_sub d 1#usize)
    (hlt : i < 32768#usize) : d.val = p.val - c.val ∧ 1 ≤ d.val ∧ d.val ≤ 32768 := by
  have hsz : 4294967296 ≤ Usize.size := by (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  have hpl : p.val < Usize.size := by (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  have hdv : d.val = p.val - c.val := by
    rw [hd, core.num.Usize.wrapping_sub_val_eq, UScalar.size_UScalarTyUsize]
    rw [show p.val + (Usize.size - c.val) = (p.val - c.val) + Usize.size by omega,
      Nat.add_mod_right, Nat.mod_eq_of_lt (by omega)]
  have hiv : i.val < 32768 := by (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  have hdl : d.val < Usize.size := by omega
  rw [hi, core.num.Usize.wrapping_sub_val_eq, UScalar.size_UScalarTyUsize] at hiv
  simp only [show (1#usize).val = 1 by simp] at hiv
  refine ⟨hdv, ?_, ?_⟩
  · by_contra h0
    have : d.val = 0 := by omega
    rw [this, Nat.zero_add, Nat.mod_eq_of_lt (by omega)] at hiv
    omega
  · by_cases h0 : d.val = 0
    · rw [h0, Nat.zero_add, Nat.mod_eq_of_lt (by omega)] at hiv
      omega
    · rw [show d.val + (Usize.size - 1) = (d.val - 1) + Usize.size by omega, Nat.add_mod_right,
        Nat.mod_eq_of_lt (by omega)] at hiv
      omega

theorem ACand.of_common {s : Slice Std.U8} {p c d i l cap : Std.Usize} (hc : c.val ≤ p.val)
    (hd : d = core.num.Usize.wrapping_sub p c) (hi : i = core.num.Usize.wrapping_sub d 1#usize)
    (hlt : i < 32768#usize) (hl : l.val ≤ cap.val) (hm : Matches s c.val p.val l.val) :
    ACand s p.val cap.val l.val d.val := by
  obtain ⟨hdv, hd1, hd2⟩ := a_dist_of_wrapping hc hd hi hlt
  refine Or.inr ⟨hd1, hd2, by omega, hl, ?_⟩
  rw [show p.val - d.val = c.val by omega]
  exact hm

theorem a_dist_of_wrapping2 {p c d i : Std.Usize} (hc : c.val ≤ p.val + 2)
    (hd : d = core.num.Usize.wrapping_sub p c) (hi : i = core.num.Usize.wrapping_sub d 1#usize)
    (hlt : i < 32768#usize) : c.val ≤ p.val := by
  by_contra hcp
  have hsz : 4294967296 ≤ Usize.size := by (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  have hcl : c.val < Usize.size := by (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  have hdv : d.val = Usize.size - (c.val - p.val) := by
    rw [hd, core.num.Usize.wrapping_sub_val_eq, UScalar.size_UScalarTyUsize]
    rw [show p.val + (Usize.size - c.val) = Usize.size - (c.val - p.val) by omega,
      Nat.mod_eq_of_lt (by omega)]
  have hiv : i.val < 32768 := by (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  rw [hi, core.num.Usize.wrapping_sub_val_eq, UScalar.size_UScalarTyUsize] at hiv
  simp only [show (1#usize).val = 1 by simp] at hiv
  rw [show d.val + (Usize.size - 1) = (d.val - 1) + Usize.size by omega, Nat.add_mod_right,
    Nat.mod_eq_of_lt (by omega)] at hiv
  omega

theorem a_walk_loop_spec (s : Slice Std.U8) {W : Std.Usize} (prev : Array Std.U32 W)
    (p cap gm : Std.Usize) (hlit : Std.I32) (n best bd : Std.Usize) (bg : Std.I32)
    (c k stop : Std.Usize) (pb : Std.U8)
    (hn : n.val = s.length) (hcap : p.val + cap.val ≤ s.length) (hcap258 : cap.val ≤ 258)
    (hc : c.val ≤ p.val + 2) (hbest : p.val + best.val ≤ s.length + 1)
    (hcand : ACand s p.val cap.val best.val bd.val) (hW : 0 < W.val)
    (hh0 : 0 ≤ hlit.val) (hh1 : hlit.val ≤ 1000000) :
    slot.a_walk_loop s prev p cap gm hlit n best bd bg c k stop pb ⦃ fun r =>
      p.val + r.1.val ≤ s.length + 1 ∧ ACand s p.val cap.val r.1.val r.2.val ⦄ := by
  rw [slot.a_walk_loop]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  apply Std.loop.spec_decr_nat
    (measure := fun r => r.2.2.2.2.1.val)
    (inv := fun r => r.2.2.2.1.val ≤ p.val + 2 ∧ p.val + r.1.val ≤ s.length + 1 ∧
      ACand s p.val cap.val r.1.val r.2.1.val)
  · rintro ⟨best, bd, bg, c, k, pb⟩ ⟨hc, hbest, hcand⟩
    simp only at hc hbest hcand
    simp only [slot.a_walk_loop.body]
    step*

    case hmax =>
      have hcp := a_dist_of_wrapping2 hc (by assumption) (by assumption) (by assumption)
      obtain ⟨hdv, hd1, hd2⟩ := a_dist_of_wrapping hcp (by assumption) (by assumption) (by assumption)
      (subst_vars; scalar_tac (simpAllMaxSteps := 0))
    have hcp := a_dist_of_wrapping2 hc (by assumption) (by assumption) (by assumption)
    obtain ⟨hdv, hd1, hd2⟩ := a_dist_of_wrapping hcp (by assumption) (by assumption) (by assumption)

    apply WP.spec_bind (Pₘ := fun (x : Std.Usize × Std.Usize × Std.I32 × Std.Usize × Std.U8) =>
      p.val + x.1.val ≤ s.length + 1 ∧ ACand s p.val cap.val x.1.val x.2.1.val ∧
      1 ≤ x.2.2.2.1.val ∧ x.2.2.2.1.val ≤ k.val)
    · split
      · step
        apply WP.spec_bind (Pₘ := fun (_ : Std.I32 × Std.Usize) => True)
        · repeat' (split <;> step*)
        · rintro ⟨bg2, take⟩ -
          apply WP.spec_bind (Pₘ := fun (x : Std.Usize × Std.Usize × Std.Usize × Std.U8) =>
            p.val + x.1.val ≤ s.length + 1 ∧ ACand s p.val cap.val x.1.val x.2.1.val ∧
            1 ≤ x.2.2.1.val ∧ x.2.2.1.val ≤ k.val)
          · split
            · repeat' (split <;> step*)
              all_goals (refine ⟨by (subst_vars; scalar_tac (simpAllMaxSteps := 0)), ACand.of_common hcp (by assumption)
                (by assumption) (by assumption) (by assumption) (by assumption), by (subst_vars; scalar_tac (simpAllMaxSteps := 0)),
                by (subst_vars; scalar_tac (simpAllMaxSteps := 0))⟩)
            · step*
          · rintro ⟨i3, i4, i5, i6⟩ h
            step*
      · step*
    · rintro ⟨best1, bd1, bg1, k1, pb1⟩ ⟨h1, h2, h3, h4⟩
      step*
  · exact ⟨hc, hbest, hcand⟩

@[local step]
theorem a_walk_spec (s : Slice Std.U8) {W : Std.Usize} (prev : Array Std.U32 W)
    (p start cap «have» depth nice gm : Std.Usize) (hlit : Std.I32)
    (hcap : p.val + cap.val ≤ s.length) (hcap258 : cap.val ≤ 258) (hst : start.val ≤ p.val + 2)
    (hhave : p.val + «have».val ≤ s.length + 1) (hW : 0 < W.val)
    (hh0 : 0 ≤ hlit.val) (hh1 : hlit.val ≤ 1000000) :
    slot.a_walk s prev p start cap «have» depth nice gm hlit ⦃ fun r =>
      p.val + r.1.val ≤ s.length + 1 ∧ ACand s p.val cap.val r.1.val r.2.val ⦄ := by
  rw [slot.a_walk]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  repeat' (split <;> step*)
  all_goals
    exact a_walk_loop_spec s prev p cap gm hlit (Std.Slice.len s) «have» 0#usize _ start depth _ _
      (by simp) hcap hcap258 hst hhave (Or.inl rfl) hW hh0 hh1

def AMatchAt (s : Slice Std.U8) (p l d : Nat) : Prop :=
  3 ≤ l ∧ l ≤ 258 ∧ p + l ≤ s.length ∧ 1 ≤ d ∧ d ≤ 32768 ∧ d ≤ p ∧ Matches s (p - d) p l

def AFoundAt (s : Slice Std.U8) (p l d : Nat) : Prop := l < 3 ∨ AMatchAt s p l d

theorem AFoundAt.of_cand {s : Slice Std.U8} {p cap : Nat} {l d : Std.Usize}
    (hc : ACand s p cap l.val d.val) (hd : ¬d = 0#usize) (hcap : cap ≤ 258)
    (hpc : p + cap ≤ s.length) : AFoundAt s p l.val d.val := by
  have hd' : d.val ≠ 0 := by intro h; apply hd; exact UScalar.eq_of_val_eq (by simp [h])
  rcases hc with h0 | ⟨hd1, hd2, hdp, hl, hm⟩
  · exact absurd h0 hd'
  · rcases Nat.lt_or_ge l.val 3 with h3 | h3
    · exact Or.inl h3
    · exact Or.inr ⟨h3, by omega, by omega, hd1, hd2, hdp, hm⟩

theorem ACand.len_le {s : Slice Std.U8} {p cap : Nat} {l d : Std.Usize}
    (hc : ACand s p cap l.val d.val) (hd : ¬d = 0#usize) (hcap : cap ≤ 258) : l.val ≤ 258 := by
  have hd' : d.val ≠ 0 := by intro h; apply hd; exact UScalar.eq_of_val_eq (by simp [h])
  rcases hc with h0 | ⟨_, _, _, hl, _⟩
  · exact absurd h0 hd'
  · omega

theorem ACand.dist_le {s : Slice Std.U8} {p cap l d : Nat} (hc : ACand s p cap l d) :
    d ≤ 32768 := by
  rcases hc with h0 | ⟨_, hd, _⟩ <;> omega

theorem AFoundAt.none (s : Slice Std.U8) (p : Nat) : AFoundAt s p (0#usize).val (0#usize).val :=
  Or.inl (by simp)

theorem AFoundAt.real {s : Slice Std.U8} {p l d : Nat} (hf : AFoundAt s p l d) (h3 : 3 ≤ l) :
    AMatchAt s p l d := by
  rcases hf with h | h
  · omega
  · exact h

@[local step]
theorem a_find_spec (s : Slice Std.U8) {W : Std.Usize} (prev : Array Std.U32 W)
    (p st «have» minl depth nice gm : Std.Usize) (hlit : Std.I32)
    (hp : p.val ≤ s.length) (hst : st.val ≤ p.val + 2) (hhave : p.val + «have».val ≤ s.length + 1)
    (hhave258 : «have».val ≤ 258) (hminl : 1 ≤ minl.val) (hminl' : p.val + minl.val ≤ s.length + 1)
    (hW : 0 < W.val) (hh0 : 0 ≤ hlit.val) (hh1 : hlit.val ≤ 1000000) :
    slot.a_find s prev p st «have» minl depth nice gm hlit ⦃ fun r => AFoundAt s p.val r.1.val r.2.val ∧
      r.1.val ≤ 258 ∧ r.2.val ≤ 32768 ⦄ := by
  rw [slot.a_find]
  step*
  repeat' (split <;> step*)
  all_goals first
    | exact ⟨AFoundAt.none s p.val, by simp, by simp⟩
    | exact ⟨AFoundAt.of_cand (by assumption) (by assumption) (by (subst_vars; scalar_tac (simpAllMaxSteps := 0))) (by (subst_vars; scalar_tac (simpAllMaxSteps := 0))),
        ACand.len_le (by assumption) (by assumption) (by (subst_vars; scalar_tac (simpAllMaxSteps := 0))),
        ACand.dist_le (by assumption)⟩

def ANear (s : Slice Std.U8) (p len r : Nat) : Prop :=
  r = 0 ∨ (1 ≤ r ∧ r ≤ 32768 ∧ r ≤ p ∧ Matches s (p - r) p len)

theorem ANear.none (s : Slice Std.U8) (p len : Nat) : ANear s p len (0#usize).val := Or.inl (by simp)

theorem ANear.found {s : Slice Std.U8} {p c d i len r : Std.Usize} (hc : c.val < p.val)
    (hd : d = core.num.Usize.wrapping_sub p c) (hi : i = core.num.Usize.wrapping_sub d 1#usize)
    (hlt : i < 32768#usize) (hsame : r.val = 1 → Matches s c.val p.val len.val)
    (hr : r = 1#usize) : ANear s p.val len.val d.val := by
  obtain ⟨hdv, hd1, hd2⟩ := a_dist_of_wrapping (le_of_lt hc) hd hi hlt
  refine Or.inr ⟨hd1, hd2, by omega, ?_⟩
  rw [show p.val - d.val = c.val by omega]
  exact hsame (by rw [hr]; rfl)

theorem a_closest_loop_spec (s : Slice Std.U8) {W : Std.Usize} (prev : Array Std.U32 W)
    (p len n c k res : Std.Usize) (hn : n.val = s.length) (hp : p.val + len.val + 8 ≤ s.length)
    (hlen : len.val ≤ 258) (hW : 0 < W.val) (hres : ANear s p.val len.val res.val) :
    slot.a_closest_loop s prev p len n c k res ⦃ fun r => ANear s p.val len.val r.val ⦄ := by
  rw [slot.a_closest_loop]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  apply Std.loop.spec_decr_nat
    (measure := fun r => r.2.1.val)
    (inv := fun r => ANear s p.val len.val r.2.2.val)
  · rintro ⟨c, k, res⟩ hres
    simp only at hres
    simp only [slot.a_closest_loop.body]
    step*
    all_goals first
      | exact ⟨hres, by (subst_vars; scalar_tac (simpAllMaxSteps := 0))⟩
      | exact hres
      | exact ⟨ANear.found (by assumption) (by assumption) (by assumption) (by assumption)
          (by assumption) (by assumption), by (subst_vars; scalar_tac (simpAllMaxSteps := 0))⟩
  · exact hres

@[local step]
theorem a_closest_spec (s : Slice Std.U8) {W : Std.Usize} (prev : Array Std.U32 W)
    (p start len depth : Std.Usize) (hp : p.val + len.val + 8 ≤ s.length) (hlen : len.val ≤ 258)
    (hW : 0 < W.val) :
    slot.a_closest s prev p start len depth ⦃ fun r => ANear s p.val len.val r.val ⦄ := by
  rw [slot.a_closest]
  exact a_closest_loop_spec s prev p len (Std.Slice.len s) start depth 0#usize (by simp) hp hlen hW
    (ANear.none s p.val len.val)

theorem a_copyN_take_prefix (acc : List Nat) (d : Nat) :
    ∀ n, (LZ77.copyN acc d n).take acc.length = acc := by
  intro n
  induction n with
  | zero => simp [LZ77.copyN]
  | succ m ih =>
    simp only [LZ77.copyN]
    rw [List.take_append_of_le_length (by simp)]
    exact ih

theorem a_foldlM_emit_length : ∀ (ts : List Nat) (init acc : List Nat),
    ts.foldlM LZ77.emit init = some acc → init.length + ts.length ≤ acc.length := by
  intro ts
  induction ts with
  | nil => intro init acc h; simp at h; subst h; simp
  | cons t ts ih =>
    intro init acc h
    simp only [List.foldlM_cons] at h
    cases he : LZ77.emit init t with
    | none => rw [he] at h; simp at h
    | some a =>
      rw [he] at h
      simp only [Option.bind_eq_bind, Option.bind_some] at h
      have h1 := ih a acc h
      have h2 : init.length + 1 ≤ a.length := by
        simp only [LZ77.emit] at he
        split at he
        · simp at he; subst he; simp
        · split at he
          · split at he
            · simp at he; subst he; rw [LZ77.copyN_length]; simp only [LZ77.tokLen]; omega
            · simp at he
          · simp at he
      simp only [List.length_cons]
      omega

theorem a_decode_length_le {ts acc : List Nat} (h : LZ77.decode ts = some acc) :
    ts.length ≤ acc.length := by
  have := a_foldlM_emit_length ts [] acc h
  simpa using this

theorem a_decode_pop_lit {ts : List Nat} {t : Nat} {inp : List Nat} {p : Nat}
    (hp : p ≤ inp.length) (hd : LZ77.decode (ts ++ [t]) = some (inp.take p)) (ht : t < 256) :
    1 ≤ p ∧ LZ77.decode ts = some (inp.take (p - 1)) := by
  rw [LZ77.decode_snoc] at hd
  cases hts : LZ77.decode ts with
  | none => rw [hts] at hd; simp at hd
  | some acc =>
    rw [hts] at hd
    simp only [Option.bind_some, LZ77.emit, if_pos ht] at hd
    have hacc : acc ++ [t] = inp.take p := Option.some.inj hd
    have hlen : acc.length + 1 = p := by
      have := congrArg List.length hacc
      simp [List.length_take] at this; omega
    refine ⟨by omega, ?_⟩
    apply congrArg some
    have := congrArg (List.take acc.length) hacc
    rw [List.take_append_of_le_length (le_refl _), List.take_length, List.take_take] at this
    rw [this, show min acc.length p = p - 1 by omega]

theorem a_decode_pop_match {ts : List Nat} {t : Nat} {inp : List Nat} {p : Nat}
    (hp : p ≤ inp.length) (hd : LZ77.decode (ts ++ [t]) = some (inp.take p)) (ht : 256 ≤ t) :
    LZ77.tokLen t ≤ p ∧ LZ77.decode ts = some (inp.take (p - LZ77.tokLen t)) := by
  rw [LZ77.decode_snoc] at hd
  cases hts : LZ77.decode ts with
  | none => rw [hts] at hd; simp at hd
  | some acc =>
    rw [hts] at hd
    simp only [Option.bind_some, LZ77.emit, if_neg (show ¬ t < 256 by omega)] at hd
    split at hd
    · split at hd
      · have hacc : LZ77.copyN acc (LZ77.tokDist t) (LZ77.tokLen t) = inp.take p := Option.some.inj hd
        have hlen : acc.length + LZ77.tokLen t = p := by
          have := congrArg List.length hacc
          simp [List.length_take] at this; omega
        refine ⟨by omega, ?_⟩
        apply congrArg some
        have := congrArg (List.take acc.length) hacc
        rw [a_copyN_take_prefix, List.take_take] at this
        rw [this, show min acc.length p = p - LZ77.tokLen t by omega]
      · simp at hd
    · simp at hd

theorem a_toks_pop (out : Slice Std.U32) (nt : Nat) (h0 : 0 < nt) (hle : nt ≤ out.length) :
    toks out nt = toks out (nt - 1) ++ [(out.val[nt - 1]!).val] := by
  have hlt : nt - 1 < out.val.length := by
    have : out.length = out.val.length := rfl
    omega
  simp only [toks]
  conv_lhs => rw [show nt = (nt - 1) + 1 by omega]
  rw [List.take_add_one, List.getElem?_eq_getElem hlt, Option.toList_some, List.map_append]
  simp [getElem!_pos out.val (nt - 1) hlt]

theorem a_toks_length (out : Slice Std.U32) (nt : Nat) (h : nt ≤ out.length) :
    (toks out nt).length = nt := by
  simp only [toks, List.length_map, List.length_take]
  have : out.length = out.val.length := rfl
  omega

def ADec (s : Slice Std.U8) (out : Slice Std.U32) (nt p : Nat) : Prop :=
  p ≤ s.length ∧ nt ≤ p ∧ s.length ≤ out.length ∧
    LZ77.decode (toks out nt) = some ((bytes s).take p)

theorem ADec.init (input : Slice Std.U8) (out : Slice Std.U32) (h : input.length ≤ out.length) :
    ADec input out (0#usize).val (0#usize).val :=
  ⟨by simp, by simp, h, by simp [toks, LZ77.decode]⟩

theorem ADec.lit {s : Slice Std.U8} {out : Slice Std.U32} {nt p : Nat} (h : ADec s out nt p)
    (hp : p < s.length) (ntU : Std.Usize) (hnt : ntU.val = nt) (v : Std.U32)
    (hv : v.val = (s.val[p]!).val) :
    ADec s (out.set ntU v) (nt + 1) (p + 1) := by
  obtain ⟨hps, hntp, hso, hde⟩ := h
  have hntl : ntU.val < out.length := by omega
  refine ⟨by omega, by omega, by rw [Std.Slice.set_length]; exact hso, ?_⟩
  rw [← hnt]
  refine emit_lit s out ntU p v (by rw [hnt]; exact hde) hp hntl ?_
  have hpl : p < s.val.length := hp
  rw [hv, bytes_getElem! s p hpl, getElem!_pos s.val p hpl]

theorem ADec.match {s : Slice Std.U8} {out : Slice Std.U32} {nt p l d : Nat} (h : ADec s out nt p)
    (hm : AMatchAt s p l d) (ntU : Std.Usize) (hnt : ntU.val = nt) (v : Std.U32)
    (hv : v.val = LZ77.mkMatch d l) :
    ADec s (out.set ntU v) (nt + 1) (p + l) := by
  obtain ⟨hps, hntp, hso, hde⟩ := h
  obtain ⟨h3, h258, hpl, hd1, hd32, hdp, hmm⟩ := hm
  have hntl : ntU.val < out.length := by omega
  refine ⟨by omega, by omega, by rw [Std.Slice.set_length]; exact hso, ?_⟩
  rw [← hnt]
  exact emit_match s out ntU p d l v (by rw [hnt]; exact hde) hntl hd1 hdp hd32 h3 h258 hpl hmm hv

theorem ADec.pop_lit {s : Slice Std.U8} {out : Slice Std.U32} {nt p : Nat} (h : ADec s out nt p)
    (h0 : 0 < nt) (hle : nt ≤ out.length) (ht : (out.val[nt - 1]!).val < 256) :
    1 ≤ p ∧ ADec s out (nt - 1) (p - 1) := by
  obtain ⟨hps, hntp, hso, hde⟩ := h
  rw [a_toks_pop out nt h0 hle] at hde
  obtain ⟨hp1, hde'⟩ := a_decode_pop_lit (by simpa using hps) hde ht
  exact ⟨hp1, by omega, by omega, hso, hde'⟩

theorem ADec.pop_match {s : Slice Std.U8} {out : Slice Std.U32} {nt p : Nat} (h : ADec s out nt p)
    (h0 : 0 < nt) (hle : nt ≤ out.length) (ht : 256 ≤ (out.val[nt - 1]!).val) :
    LZ77.tokLen (out.val[nt - 1]!).val ≤ p ∧
      ADec s out (nt - 1) (p - LZ77.tokLen (out.val[nt - 1]!).val) := by
  obtain ⟨hps, hntp, hso, hde⟩ := h
  rw [a_toks_pop out nt h0 hle] at hde
  obtain ⟨hw, hde'⟩ := a_decode_pop_match (by simpa using hps) hde ht
  have hlen := a_decode_length_le hde'
  rw [a_toks_length out (nt - 1) (by omega), List.length_take, LZ77.bytes_length] at hlen
  exact ⟨hw, by omega, by omega, hso, hde'⟩

theorem ADec.done {s : Slice Std.U8} {out : Slice Std.U32} {nt p : Nat} (h : ADec s out nt p)
    (hp : s.length ≤ p) : nt ≤ s.length ∧ LZ77.Valid (bytes s) (toks out nt) := by
  obtain ⟨hps, hntp, hso, hde⟩ := h
  refine ⟨by omega, ?_⟩
  unfold LZ77.Valid
  rw [hde, show p = s.length by omega, ← LZ77.bytes_length, List.take_length]

theorem ADec.lit_step {s : Slice Std.U8} {out out1 : Slice Std.U32} {ntU nt1 pU : Std.Usize}
    {b : Std.U8} {v : Std.U32} (h : ADec s out ntU.val pU.val) (hp : pU.val < s.val.length)
    (hb : b = s.val[pU.val]) (hv : v = UScalar.cast .U32 b) (hout1 : out1 = out.set ntU v)
    (hnt1 : nt1.val = ntU.val + 1) :
    nt1.val = ntU.val + 1 ∧ out1.length = out.length ∧ ADec s out1 nt1.val (pU.val + 1) := by
  subst hout1
  refine ⟨hnt1, Std.Slice.set_length .., ?_⟩
  rw [hnt1]
  exact ADec.lit h hp ntU rfl v (by rw [hv, U8.cast_U32_val_eq, hb, getElem!_pos s.val pU.val hp])

@[local step]
theorem a_put_lit_spec (s : Slice Std.U8) (out : Slice Std.U32) (nt p : Std.Usize)
    (hdec : ADec s out nt.val p.val) (hp : p.val < s.length) :
    slot.a_put_lit s out nt p ⦃ fun r => r.1.val = nt.val + 1 ∧ r.2.length = out.length ∧
      ADec s r.2 r.1.val (p.val + 1) ⦄ := by
  rw [slot.a_put_lit]
  step*
  exact ADec.lit_step hdec (by (subst_vars; scalar_tac (simpAllMaxSteps := 0))) (by assumption) (by assumption) (by assumption)
    (by assumption)

theorem ADec.match_step {s : Slice Std.U8} {out out1 : Slice Std.U32} {ntU nt1 pU dU lU e : Std.Usize}
    {v : Std.U32} (h : ADec s out ntU.val pU.val) (hm : AMatchAt s pU.val lU.val dU.val)
    (hout1 : out1 = out.set ntU v) (hv : v.val = LZ77.mkMatch dU.val lU.val)
    (hnt1 : nt1.val = ntU.val + 1) (he : e.val = pU.val + lU.val) :
    nt1.val = ntU.val + 1 ∧ e.val = pU.val + lU.val ∧ out1.length = out.length ∧
      ADec s out1 nt1.val e.val := by
  subst hout1
  refine ⟨hnt1, he, Std.Slice.set_length .., ?_⟩
  rw [hnt1, he]
  exact ADec.match h hm ntU rfl v hv

@[local step]
theorem a_put_match_spec (s : Slice Std.U8) (out : Slice Std.U32) (nt p d l : Std.Usize)
    (hdec : ADec s out nt.val p.val) (hm : AMatchAt s p.val l.val d.val) :
    slot.a_put_match s out nt p d l ⦃ fun r => r.1.1.val = nt.val + 1 ∧
      r.1.2.val = p.val + l.val ∧ r.2.length = out.length ∧ ADec s r.2 r.1.1.val r.1.2.val ⦄ := by
  rw [slot.a_put_match]
  have hm' := hm
  obtain ⟨h3, h258, hpl, hd1, hd32, hdp, _⟩ := hm'
  step*

  exact ADec.match_step hdec hm (by assumption)
    (by simp only [LZ77.mkMatch, LZ77.MATCH_BASE]; (subst_vars; scalar_tac (simpAllMaxSteps := 0))) (by assumption) (by assumption)

theorem AMatchAt.back_lit {s : Slice Std.U8} {p l d : Nat} (h : AMatchAt s p l d) (hl : l < 258)
    (hdp : d < p) (heq : s.val[p - 1]! = s.val[p - 1 - d]!) : AMatchAt s (p - 1) (l + 1) d := by
  obtain ⟨h3, h258, hpl, hd1, hd32, _, hm⟩ := h
  refine ⟨by omega, by omega, by omega, hd1, hd32, by omega, ?_⟩
  intro k hk
  rcases Nat.eq_zero_or_pos k with hk0 | hk0
  · subst hk0
    rw [Nat.add_zero, Nat.add_zero, show p - 1 - d = p - 1 - d by rfl]
    exact heq
  · have := hm (k - 1) (by omega)
    rw [show p - 1 + k = p + (k - 1) by omega, show p - 1 - d + k = p - d + (k - 1) by omega]
    exact this

theorem AMatchAt.back_match {s : Slice Std.U8} {p l d w : Nat} (h : AMatchAt s p l d)
    (hlw : l + w ≤ 258) (hw : w ≤ p) (hdw : d ≤ p - w) (hmw : Matches s (p - w - d) (p - w) w) :
    AMatchAt s (p - w) (l + w) d := by
  obtain ⟨h3, h258, hpl, hd1, hd32, _, hm⟩ := h
  refine ⟨by omega, by omega, by omega, hd1, hd32, hdw, ?_⟩
  intro k hk
  rcases Nat.lt_or_ge k w with hkw | hkw
  · have := hmw k hkw
    rw [show p - w - d = p - w - d by rfl] at this
    exact this
  · have := hm (k - w) (by omega)
    rw [show p - w + k = p + (k - w) by omega, show p - w - d + k = p - d + (k - w) by omega]
    exact this

def ABackInv (input : Slice Std.U8) (L d E P0 : Nat) (out : Slice Std.U32) (nt p l : Nat) : Prop :=
  ADec input out nt p ∧ out.length = L ∧ AMatchAt input p l d ∧ p + l = E ∧ p ≤ P0

theorem ABackInv.lit {input : Slice Std.U8} {out : Slice Std.U32} {L d E P0 : Nat}
    {nt p l i1 i2 i4 l1 : Std.Usize} {t : Std.U32} {x y : Std.U8}
    (h : ABackInv input L d E P0 out nt.val p.val l.val)
    (hi1 : i1.val = nt.val - 1) (hntl : nt.val ≤ out.length) (hnt0 : 1 ≤ nt.val)
    (hi1l : i1.val < out.val.length) (ht : t = out.val[i1.val]) (ht256 : t < 256#u32)
    (hi2 : i2.val = p.val - 1) (hi2l : i2.val < input.val.length) (hx : x = input.val[i2.val])
    (hxy : x = y) (hi4 : i4.val = i2.val - d) (hi4l : i4.val < input.val.length)
    (hy : y = input.val[i4.val]) (hl : l.val < 258) (hdp : d < p.val)
    (hl1 : l1.val = l.val + 1) :
    ABackInv input L d E P0 out i1.val i2.val l1.val := by
  obtain ⟨hdec, hL, hm, hE, hP⟩ := h
  have ht' : (out.val[nt.val - 1]!).val < 256 := by
    rw [← hi1, getElem!_pos out.val i1.val hi1l, ← ht]; (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  obtain ⟨hp1, hdec'⟩ := ADec.pop_lit hdec (by omega) hntl ht'
  have heq : input.val[p.val - 1]! = input.val[p.val - 1 - d]! := by
    rw [← hi2, getElem!_pos input.val i2.val hi2l, show i2.val - d = i4.val by omega,
      getElem!_pos input.val i4.val hi4l, ← hx, ← hy, hxy]
  have hm' := AMatchAt.back_lit hm hl hdp heq
  rw [hi1, hi2, hl1]
  exact ⟨hdec', hL, hm', by omega, by omega⟩

theorem ABackInv.match {input : Slice Std.U8} {out : Slice Std.U32} {L d E P0 : Nat}
    {nt p l i1 w i9 i10 i11 i12 : Std.Usize} {t : Std.U32}
    (h : ABackInv input L d E P0 out nt.val p.val l.val)
    (hi1 : i1.val = nt.val - 1) (hntl : nt.val ≤ out.length) (hnt0 : 1 ≤ nt.val)
    (hi1l : i1.val < out.val.length) (ht : t = out.val[i1.val])
    (hsame : i12.val = 1 → Matches input i11.val i10.val w.val) (hi12 : i12 = 1#usize)
    (ht24 : 16777216 ≤ t.val) (hwv : w.val = (t.val - 16777216) % 256 + 3)
    (hi9 : i9.val = l.val + w.val) (hi9' : i9.val ≤ 258) (hi10 : i10.val = p.val - w.val)
    (hwp : w.val ≤ p.val) (hdw : d ≤ i10.val) (hi11 : i11.val = i10.val - d) :
    ABackInv input L d E P0 out i1.val i10.val i9.val := by
  obtain ⟨hdec, hL, hm, hE, hP⟩ := h
  have htv : (out.val[nt.val - 1]!).val = t.val := by
    rw [← hi1, getElem!_pos out.val i1.val hi1l, ← ht]
  have hwv' : w.val = LZ77.tokLen (out.val[nt.val - 1]!).val := by
    rw [htv, hwv]
    simp only [LZ77.tokLen, LZ77.MATCH_BASE]
  obtain ⟨hwl, hdec'⟩ := ADec.pop_match hdec (by omega) hntl (by omega)
  rw [← hwv'] at hdec'
  have hmw : Matches input (p.val - w.val - d) (p.val - w.val) w.val := by
    have := hsame (by rw [hi12]; rfl)
    rw [hi11, hi10] at this
    exact this
  have hm' := AMatchAt.back_match hm (by omega) hwp (by omega) hmw
  rw [hi1, hi10, hi9]
  exact ⟨hdec', hL, hm', by omega, by omega⟩

theorem ABackInv.part {input : Slice Std.U8} {out out1 : Slice Std.U32} {L d E P0 : Nat}
    {nt p l : Nat} {p1 l1 : Std.Usize} (h : ABackInv input L d E P0 out nt p l)
    (hlen : out1.length = out.length) (hdec : ADec input out1 nt p1.val)
    (hm : AMatchAt input p1.val l1.val d) (hE : p1.val + l1.val = p + l) (hp : p1.val ≤ p) :
    ABackInv input L d E P0 out1 nt p1.val l1.val := by
  obtain ⟨_, hL, _, hE0, hP⟩ := h
  exact ⟨hdec, by rw [hlen, hL], hm, by omega, by omega⟩

theorem ABackInv.lit_step {input : Slice Std.U8} {out : Slice Std.U32} {L E P0 : Nat}
    {nt p l d back i1 i2 i4 l1 back1 : Std.Usize} {t : Std.U32} {x y : Std.U8}
    (h : ABackInv input L d.val E P0 out nt.val p.val l.val)
    (hbk : back < slot.A_BACKTOK) (hntl : nt ≤ Std.Slice.len out) (hl : l < 258#usize) (hdp : d < p)
    (hi1 : i1.val = nt.val - 1) (hnt0 : 1 ≤ nt.val) {hb1 : i1.val < out.val.length}
    (ht : t = out.val[i1.val]'hb1) (ht256 : t < 256#u32)
    (hi2 : i2.val = p.val - 1) {hb2 : i2.val < input.val.length} (hx : x = input.val[i2.val]'hb2)
    (hi4 : i4.val = i2.val - d.val) {hb4 : i4.val < input.val.length}
    (hy : y = input.val[i4.val]'hb4) (hxy : x = y)
    (hl1 : l1.val = l.val + 1) (hb1' : back1.val = back.val + 1) :
    ABackInv input L d.val E P0 out i1.val i2.val l1.val ∧
      slot.A_BACKTOK.val - back1.val < slot.A_BACKTOK.val - back.val :=
  ⟨ABackInv.lit h hi1 (by (subst_vars; scalar_tac (simpAllMaxSteps := 0))) hnt0 hb1 ht ht256 hi2 hb2 hx hxy hi4 hb4 hy
    (by (subst_vars; scalar_tac (simpAllMaxSteps := 0))) (by (subst_vars; scalar_tac (simpAllMaxSteps := 0))) hl1, by (subst_vars; scalar_tac (simpAllMaxSteps := 0))⟩

theorem ABackInv.match_step {input : Slice Std.U8} {out : Slice Std.U32} {L E P0 : Nat}
    {nt p l d back i1 w i9 i10 i11 i12 back1 : Std.Usize} {t i6 i7 i8 : Std.U32}
    (h : ABackInv input L d.val E P0 out nt.val p.val l.val)
    (hbk : back < slot.A_BACKTOK) (hntl : nt ≤ Std.Slice.len out)
    (hi1 : i1.val = nt.val - 1) (hnt0 : 1 ≤ nt.val) {hb1 : i1.val < out.val.length}
    (ht : t = out.val[i1.val]'hb1) (hi6 : i6.val = t.val - 16777216) (ht24 : 16777216 ≤ t.val)
    (hi7 : i7.val = i6.val % 256) (hi8 : i8.val = i7.val + 3) (hw : w = UScalar.cast .Usize i8)
    (hi9 : i9.val = l.val + w.val) (hi9' : i9 ≤ 258#usize) (hi10 : i10.val = p.val - w.val)
    (hwp : w.val ≤ p.val) (hdw : d ≤ i10) (hi11 : i11.val = i10.val - d.val)
    (hsame : i12.val = 1 → Matches input i11.val i10.val w.val) (hi12 : i12 = 1#usize)
    (hb1' : back1.val = back.val + 1) :
    ABackInv input L d.val E P0 out i1.val i10.val i9.val ∧
      slot.A_BACKTOK.val - back1.val < slot.A_BACKTOK.val - back.val := by
  have hwv : w.val = (t.val - 16777216) % 256 + 3 := by rw [hw]; scalar_tac
  exact ⟨ABackInv.match h hi1 (by scalar_tac) hnt0 hb1 ht hsame hi12 ht24 hwv hi9 (by scalar_tac)
    hi10 hwp (by scalar_tac) hi11, by scalar_tac⟩

theorem ABackInv.part_step {input : Slice Std.U8} {out out1 : Slice Std.U32} {L E P0 : Nat}
    {nt p l d back p1 l1 : Std.Usize} (h : ABackInv input L d.val E P0 out nt.val p.val l.val)
    (hbk : back < slot.A_BACKTOK) (hlen : out1.length = out.length)
    (hdec : ADec input out1 nt.val p1.val) (hm : AMatchAt input p1.val l1.val d.val)
    (hE : p1.val + l1.val = p.val + l.val) (hp : p1.val ≤ p.val) :
    ABackInv input L d.val E P0 out1 nt.val p1.val l1.val ∧
      slot.A_BACKTOK.val - slot.A_BACKTOK.val < slot.A_BACKTOK.val - back.val :=
  ⟨ABackInv.part h hlen hdec hm hE hp, by (subst_vars; scalar_tac (simpAllMaxSteps := 0))⟩

theorem Matches.a_cons {input : Slice Std.U8} {a b n : Nat} (h : Matches input (a + 1) (b + 1) n)
    (heq : input.val[b]! = input.val[a]!) : Matches input a b (n + 1) := by
  intro k hk
  rcases Nat.eq_zero_or_pos k with h0 | hk0
  · subst h0; simpa using heq
  · have := h (k - 1) (by omega)
    rw [show b + 1 + (k - 1) = b + k by omega, show a + 1 + (k - 1) = a + k by omega] at this
    exact this

theorem Matches.a_append {input : Slice Std.U8} {a b k l : Nat} (h1 : Matches input a b k)
    (h2 : Matches input (a + k) (b + k) l) : Matches input a b (k + l) := by
  intro j hj
  rcases Nat.lt_or_ge j k with hjk | hjk
  · exact h1 j hjk
  · have := h2 (j - k) (by omega)
    rw [show b + k + (j - k) = b + j by omega, show a + k + (j - k) = a + j by omega] at this
    exact this

theorem AMatchAt.back_part {s : Slice Std.U8} {p l d k : Nat} (h : AMatchAt s p l d)
    (hmk : Matches s (p - k - d) (p - k) k) (hlk : l + k ≤ 258) (hdk : d + k ≤ p) :
    AMatchAt s (p - k) (l + k) d := by
  obtain ⟨h3, h258, hpl, hd1, hd32, _, hm⟩ := h
  refine ⟨by omega, hlk, by omega, hd1, hd32, by omega, ?_⟩
  have hm' : Matches s (p - k - d + k) (p - k + k) l := by
    rw [show p - k - d + k = p - d by omega, show p - k + k = p by omega]; exact hm
  have := Matches.a_append hmk hm'
  rw [show k + l = l + k by omega] at this
  exact this

theorem Matches.a_back_step {input : Slice Std.U8} {p d k : Nat} {i4 i7 k1 : Std.Usize}
    {x y : Std.U8} (h : Matches input (p - k - d) (p - k) k) (hdk : d + k < p)
    (hi4 : i4.val = p - 1 - k) (hi4l : i4.val < input.val.length) (hx : x = input.val[i4.val])
    (hi7 : i7.val = p - 1 - k - d) (hi7l : i7.val < input.val.length)
    (hy : y = input.val[i7.val]) (hxy : x = y) (hk1 : k1.val = k + 1) :
    Matches input (p - k1.val - d) (p - k1.val) k1.val := by
  rw [hk1]
  apply Matches.a_cons
  · rw [show p - (k + 1) - d + 1 = p - k - d by omega, show p - (k + 1) + 1 = p - k by omega]
    exact h
  · rw [show p - (k + 1) - d = i7.val by omega, show p - (k + 1) = i4.val by omega,
      getElem!_pos input.val i4.val hi4l, getElem!_pos input.val i7.val hi7l, ← hx, ← hy, hxy]

theorem a_part_merge_loop_spec (input : Slice Std.U8) (p0 l0 d w k : Std.Usize)
    (hp0 : p0.val ≤ input.length) (hkw : k.val ≤ w.val) (hl0 : l0.val + k.val ≤ 258)
    (hdk : d.val + k.val ≤ p0.val)
    (hm : Matches input (p0.val - k.val - d.val) (p0.val - k.val) k.val) :
    slot.a_part_merge_loop input p0 l0 d w k ⦃ fun r =>
      r.val ≤ w.val ∧ l0.val + r.val ≤ 258 ∧ d.val + r.val ≤ p0.val ∧
      Matches input (p0.val - r.val - d.val) (p0.val - r.val) r.val ⦄ := by
  rw [slot.a_part_merge_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun r => w.val - r.val)
    (inv := fun r => r.val ≤ w.val ∧ l0.val + r.val ≤ 258 ∧ d.val + r.val ≤ p0.val ∧
      Matches input (p0.val - r.val - d.val) (p0.val - r.val) r.val)
  · rintro k ⟨hkw, hl0, hdk, hm⟩
    simp only [slot.a_part_merge_loop.body]
    step*
    all_goals first
      | exact ⟨hkw, hl0, hdk, hm⟩
      | (refine ⟨by (subst_vars; scalar_tac (simpAllMaxSteps := 0)), by (subst_vars; scalar_tac (simpAllMaxSteps := 0)), by (subst_vars; scalar_tac (simpAllMaxSteps := 0)),
          Matches.a_back_step (i4 := i4) (i7 := i7) (x := i5) (y := i8) hm (by (subst_vars; scalar_tac (simpAllMaxSteps := 0)))
            (by (subst_vars; scalar_tac (simpAllMaxSteps := 0))) (by (subst_vars; scalar_tac (simpAllMaxSteps := 0))) (by assumption) (by (subst_vars; scalar_tac (simpAllMaxSteps := 0))) (by (subst_vars; scalar_tac (simpAllMaxSteps := 0)))
            (by assumption) (by assumption) (by (subst_vars; scalar_tac (simpAllMaxSteps := 0))),
          by (subst_vars; scalar_tac (simpAllMaxSteps := 0))⟩)
  · exact ⟨hkw, hl0, hdk, hm⟩

@[local step]
theorem a_part_merge_loop_spec0 (input : Slice Std.U8) (p0 l0 d w : Std.Usize)
    (hp0 : p0.val ≤ input.length) (hl0 : l0.val ≤ 258) (hdk : d.val ≤ p0.val) :
    slot.a_part_merge_loop input p0 l0 d w 0#usize ⦃ fun r =>
      r.val ≤ w.val ∧ l0.val + r.val ≤ 258 ∧ d.val + r.val ≤ p0.val ∧
      Matches input (p0.val - r.val - d.val) (p0.val - r.val) r.val ⦄ :=
  a_part_merge_loop_spec input p0 l0 d w 0#usize hp0 (by simp) (by simpa using hl0)
    (by simpa using hdk) (by simpa using LZ77.Matches.zero input (p0.val - d.val) p0.val)

theorem a_part_post {input : Slice Std.U8} {out out1 : Slice Std.U32}
    {nt p l d w k c nl pp p1 l1 : Nat} {ntU : Std.Usize} {v : Std.U32}
    (hdec : ADec input out nt p) (hm : AMatchAt input p l d)
    (hnt0 : 1 ≤ nt) (hntl : nt ≤ out.length) (ht24 : 256 ≤ (out.val[nt - 1]!).val)
    (hw : w = LZ77.tokLen (out.val[nt - 1]!).val)
    (hmk : Matches input (p - k - d) (p - k) k) (hc : ANear input pp nl c)
    (hout1 : out1 = out.set ntU v)
    (hlk : l + k ≤ 258) (hdk : d + k ≤ p) (hk : k ≤ w) (hpp : pp = p - w) (hnl : nl = w - k)
    (hnl3 : 3 ≤ nl) (hnl258 : nl ≤ 258) (hc0 : 0 < c) (hcp : c ≤ pp)
    (hntU : ntU.val = nt - 1) (hv : v.val = LZ77.mkMatch c nl) (hp1 : p1 = p - k)
    (hl1 : l1 = l + k) :
    out1.length = out.length ∧ ADec input out1 nt p1 ∧ AMatchAt input p1 l1 d ∧
      p1 + l1 = p + l ∧ p1 ≤ p := by
  subst hp1 hl1 hpp
  obtain ⟨hwp, hdec'⟩ := ADec.pop_match hdec (by omega) hntl ht24
  rw [← hw] at hdec' hwp
  have hpn : p ≤ input.length := hdec.1
  have hmc : AMatchAt input (p - w) nl c := by
    rcases hc with h0 | ⟨hc1, hc32, _, hmm⟩
    · omega
    · exact ⟨hnl3, hnl258, by omega, hc1, hc32, hcp, hmm⟩
  have hd2 := ADec.match hdec' hmc ntU hntU v hv
  rw [show nt - 1 + 1 = nt by omega, show p - w + nl = p - k by omega, ← hout1] at hd2
  refine ⟨by rw [hout1, Std.Slice.set_length], hd2, AMatchAt.back_part hm hmk hlk hdk,
    by omega, by omega⟩

@[local step]
theorem a_part_merge_spec {W : Std.Usize} (input : Slice Std.U8) (out : Slice Std.U32)
    (prev : Array Std.U32 W) (nt p l d : Std.Usize) (t : Std.U32) (w «partial» : Std.Usize)
    (hdec : ADec input out nt.val p.val) (hm : AMatchAt input p.val l.val d.val)
    (hp8 : p.val + 8 ≤ input.length) (hnt0 : 1 ≤ nt.val) (hntl : nt.val ≤ out.length)
    (ht : (out.val[nt.val - 1]!).val = t.val) (ht24 : 16777216 ≤ t.val)
    (hw : w.val = (t.val - 16777216) % 256 + 3) (hW : 0 < W.val) :
    slot.a_part_merge input out prev nt p l d t w «partial» ⦃ fun r =>
      r.2.length = out.length ∧ ADec input r.2 nt.val r.1.1.val ∧
      AMatchAt input r.1.1.val r.1.2.val d.val ∧ r.1.1.val + r.1.2.val = p.val + l.val ∧
      r.1.1.val ≤ p.val ⦄ := by
  rw [slot.a_part_merge]
  have hm' := hm
  obtain ⟨h3, h258, hpl, hd1, hd32, hdp, _⟩ := hm'
  have hwt : w.val = LZ77.tokLen (out.val[nt.val - 1]!).val := by
    rw [ht, hw]; simp only [LZ77.tokLen, LZ77.MATCH_BASE]
  have ht256 : 256 ≤ (out.val[nt.val - 1]!).val := by rw [ht]; omega
  step*
  all_goals first
    | exact ⟨rfl, hdec, hm, rfl, le_refl _⟩
    | exact a_part_post hdec hm hnt0 hntl ht256 hwt (by assumption) (by assumption)
        (by assumption) (by omega) (by omega) (by omega) (by omega) (by omega) (by omega)
        (by scalar_tac) (by omega) (by scalar_tac) (by omega)
        (by simp only [LZ77.mkMatch, LZ77.MATCH_BASE]; scalar_tac) (by omega) (by omega)

def ALazyInv (input : Slice Std.U8) (L lim : Nat) (out : Slice Std.U32) (nt p : Nat)
    {N : Std.Usize} (head : Array Std.U32 N) (ins l d : Nat) : Prop :=
  ADec input out nt p ∧ out.length = L ∧ AMatchAt input p l d ∧ AHeadBound head (p + 2) ∧
    p < lim ∧ ins ≤ p + 3

theorem ALazyInv.accept {input : Slice Std.U8} {L lim p' B : Nat} {out1 : Slice Std.U32}
    {nt1 i ins1 l1 d1 minl : Std.Usize} {N : Std.Usize} {head1 : Array Std.U32 N}
    (hdec : ADec input out1 nt1.val p') (hi : i.val = p') (hlen : out1.length = L)
    (hf : AFoundAt input i.val l1.val d1.val) (hl1 : minl.val ≤ l1.val) (hminl : 3 ≤ minl.val)
    (hB : AHeadBound head1 B) (hBi : B ≤ i.val + 2) (hilim : i.val < lim)
    (hins : ins1.val ≤ i.val + 3) :
    ALazyInv input L lim out1 nt1.val i.val head1 ins1.val l1.val d1.val := by
  subst hi
  refine ⟨hdec, hlen, ?_, AHeadBound.mono hB hBi, hilim, hins⟩
  rcases hf with h | h
  · omega
  · exact h

theorem ALazyInv.reject {input : Slice Std.U8} {L lim : Nat} {out : Slice Std.U32}
    {nt p ins ins1 l d B : Nat} {N : Std.Usize} {head head1 : Array Std.U32 N}
    (h : ALazyInv input L lim out nt p head ins l d) (hB : AHeadBound head1 B) (hBp : B ≤ p + 2)
    (hins1 : ins1 ≤ p + 3) : ALazyInv input L lim out nt p head1 ins1 l d := by
  obtain ⟨hdec, hlen, hm, _, hplim, _⟩ := h
  exact ⟨hdec, hlen, hm, AHeadBound.mono hB hBp, hplim, hins1⟩

theorem ALazyInv.accept_step {input : Slice Std.U8} {L : Nat} {lim : Std.Usize}
    {out out1 : Slice Std.U32} {nt p ins l d nt1 i ins1 l1 d1 minl : Std.Usize} {B q : Nat}
    {N : Std.Usize} {head head1 : Array Std.U32 N}
    (h : ALazyInv input L lim.val out nt.val p.val head ins.val l.val d.val)
    (hminl : 3 ≤ minl.val) (hilim : i < lim) (hf : AFoundAt input i.val l1.val d1.val)
    (hl1 : l1 ≥ minl) (hB : AHeadBound head1 B) (hBi : B ≤ i.val + 2) (hpi : p.val < i.val)
    (hins1 : ins1.val ≤ i.val + 3) (hlen : out1.length = out.length)
    (hdec : ADec input out1 nt1.val q) (hq : q = i.val) :
    ALazyInv input L lim.val out1 nt1.val i.val head1 ins1.val l1.val d1.val ∧
      lim.val - i.val + (1#u32 : Std.U32).val < lim.val - p.val + (1#u32 : Std.U32).val := by
  obtain ⟨_, hL, _, _, _, _⟩ := h
  exact ⟨ALazyInv.accept hdec hq.symm (by rw [hlen, hL]) hf (by (subst_vars; scalar_tac (simpAllMaxSteps := 0))) hminl hB hBi
    (by (subst_vars; scalar_tac (simpAllMaxSteps := 0))) hins1, by (subst_vars; scalar_tac (simpAllMaxSteps := 0))⟩

theorem ALazyInv.reject_step {input : Slice Std.U8} {L : Nat} {lim : Std.Usize}
    {out : Slice Std.U32} {nt p ins l d ins1 : Std.Usize} {B : Nat}
    {N : Std.Usize} {head head1 : Array Std.U32 N}
    (h : ALazyInv input L lim.val out nt.val p.val head ins.val l.val d.val)
    (hB : AHeadBound head1 B) (hBp : B ≤ p.val + 2) (hins1 : ins1.val ≤ p.val + 3) :
    ALazyInv input L lim.val out nt.val p.val head1 ins1.val l.val d.val ∧
      lim.val - p.val + (0#u32 : Std.U32).val < lim.val - p.val + (1#u32 : Std.U32).val := by
  refine ⟨ALazyInv.reject h hB hBp hins1, by simp⟩

theorem ADec.cast {s : Slice Std.U8} {out : Slice Std.U32} {nt p p' : Nat} (h : ADec s out nt p)
    (hp : p' = p) : ADec s out nt p' := by
  subst hp; exact h

theorem a_lazy_loop_inv {H W : Std.Usize} (input : Slice Std.U8) (out : Slice Std.U32)
    (nt p : Std.Usize) (mask : Std.U32) (minl l2d lazy nice ldep : Std.Usize) (hlit : Std.I32)
    (head : Array Std.U32 H) (prev : Array Std.U32 W) (lim ins l d : Std.Usize) (go : Std.U32)
    (L : Nat) (hlim : lim.val + 8 = input.length)
    (hminl : 3 ≤ minl.val) (hminl8 : minl.val ≤ 8) (hH : 0 < H.val) (hW : 0 < W.val)
    (hh0 : 0 ≤ hlit.val) (hh1 : hlit.val ≤ 1000000)
    (hinv : ALazyInv input L lim.val out nt.val p.val head ins.val l.val d.val) :
    slot.a_run_loop0_loop1 input out nt p mask minl l2d lazy nice ldep hlit head prev lim ins l d go
      ⦃ fun r => ALazyInv input L lim.val r.1 r.2.1.val r.2.2.1.val r.2.2.2.1
        r.2.2.2.2.2.1.val r.2.2.2.2.2.2.1.val r.2.2.2.2.2.2.2.val ⦄ := by
  rw [slot.a_run_loop0_loop1]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  have ⟨hL0, hL1⟩ := a_L2B_bound
  apply Std.loop.spec_decr_nat
    (measure := fun r => lim.val - r.2.2.1.val + r.2.2.2.2.2.2.2.2.val)
    (inv := fun r => ALazyInv input L lim.val r.1 r.2.1.val r.2.2.1.val r.2.2.2.1
      r.2.2.2.2.2.1.val r.2.2.2.2.2.2.1.val r.2.2.2.2.2.2.2.1.val)
  · clear hinv
    rintro ⟨out, nt, p, head, prev, ins, l, d, go⟩ hinv
    simp only at hinv
    have hinv' := hinv
    obtain ⟨hdec, hL, hm, hB, hplim, hins⟩ := hinv'
    have hdec' := hdec
    have hm' := hm
    obtain ⟨hps, hntp, hso, -⟩ := hdec'
    obtain ⟨h3, h258, hpl, hd1, hd32, hdp, -⟩ := hm'
    simp only [slot.a_run_loop0_loop1.body]
    step*

    apply WP.spec_bind (Pₘ := fun (h : Std.Usize) => h.val + 1 ≤ l.val)
    · split
      · step*
      · simp only [Std.WP.spec_ok]; (subst_vars; scalar_tac (simpAllMaxSteps := 0))
    intro «have» hhave
    step*
    all_goals first
      | exact ALazyInv.reject_step hinv (by assumption) (by omega) (by omega)
      | exact ALazyInv.accept_step hinv hminl (by assumption) (by assumption) (by assumption)
          (by assumption) (by omega) (by omega) (by omega) (by omega) (by assumption) (by omega)
      | exact ADec.cast (by assumption) (by (subst_vars; scalar_tac (simpAllMaxSteps := 0)))
  · exact hinv

@[local step]
theorem a_lazy_loop_spec {H W : Std.Usize} (input : Slice Std.U8) (out : Slice Std.U32)
    (nt p : Std.Usize) (mask : Std.U32) (minl l2d lazy nice ldep : Std.Usize) (hlit : Std.I32)
    (head : Array Std.U32 H) (prev : Array Std.U32 W) (lim ins l d : Std.Usize) (go : Std.U32)
    (L : Nat) (hlim : lim.val + 8 = input.length)
    (hminl : 3 ≤ minl.val) (hminl8 : minl.val ≤ 8) (hH : 0 < H.val) (hW : 0 < W.val)
    (hh0 : 0 ≤ hlit.val) (hh1 : hlit.val ≤ 1000000)
    (hdec : ADec input out nt.val p.val) (hlen : out.length = L)
    (hm : AMatchAt input p.val l.val d.val) (hB : AHeadBound head (p.val + 2))
    (hplim : p.val < lim.val) (hins : ins.val ≤ p.val + 3) :
    slot.a_run_loop0_loop1 input out nt p mask minl l2d lazy nice ldep hlit head prev lim ins l d go
      ⦃ fun r =>
      ADec input r.1 r.2.1.val r.2.2.1.val ∧ r.1.length = L ∧
      AMatchAt input r.2.2.1.val r.2.2.2.2.2.2.1.val r.2.2.2.2.2.2.2.val ∧
      AHeadBound r.2.2.2.1 (r.2.2.1.val + r.2.2.2.2.2.2.1.val) ∧ r.2.2.1.val < lim.val ∧
      r.2.2.2.2.2.1.val ≤ r.2.2.1.val + 3 ∧ 3 ≤ r.2.2.2.2.2.2.1.val ⦄ := by
  apply Std.WP.spec_mono (a_lazy_loop_inv input out nt p mask minl l2d lazy nice ldep hlit head prev
    lim ins l d go L hlim hminl hminl8 hH hW hh0 hh1 ⟨hdec, hlen, hm, hB, hplim, hins⟩)
  rintro ⟨out', nt', p', head', prev', ins', l', d'⟩ ⟨hdec', hlen', hm', hB', hplim', hins'⟩
  exact ⟨hdec', hlen', hm', AHeadBound.mono hB' (by have := hm'.1; omega), hplim', hins', hm'.1⟩

theorem a_idx_bang {out : Slice Std.U32} {nt i1 : Std.Usize} {t : Std.U32}
    (hi1 : i1.val = nt.val - 1) (hl : i1.val < out.val.length) (ht : t = out.val[i1.val]) :
    (out.val[nt.val - 1]!).val = t.val := by
  rw [← hi1, getElem!_pos out.val i1.val hl, ← ht]

theorem a_idx_step {out : Slice Std.U32} {nt i1 : Std.Usize} {t : Std.U32}
    (hi1 : i1.val = nt.val - 1) {hb : i1.val < out.val.length} (ht : t = out.val[i1.val]'hb) :
    (out.val[nt.val - 1]!).val = t.val :=
  a_idx_bang hi1 hb ht

theorem a_back_loop_inv {W : Std.Usize} (input : Slice Std.U8) (out : Slice Std.U32)
    (nt p «partial» : Std.Usize) (prev : Array Std.U32 W) (l d back : Std.Usize) (L E P0 : Nat)
    (hP0 : P0 + 8 ≤ input.length) (hW : 0 < W.val)
    (hinv : ABackInv input L d.val E P0 out nt.val p.val l.val) :
    slot.a_run_loop0_loop2 input out nt p «partial» prev l d back ⦃ fun r =>
      ABackInv input L d.val E P0 r.1 r.2.1.val r.2.2.1.val r.2.2.2.val ⦄ := by
  rw [slot.a_run_loop0_loop2]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  apply Std.loop.spec_decr_nat
    (measure := fun r => slot.A_BACKTOK.val - r.2.2.2.2.val)
    (inv := fun r => ABackInv input L d.val E P0 r.1 r.2.1.val r.2.2.1.val r.2.2.2.1.val)
  · rintro ⟨out, nt, p, l, back⟩ hinv
    simp only at hinv
    have hinv' := hinv
    obtain ⟨hdec, hL, hm, hE, hp0⟩ := hinv'
    have hdec' := hdec
    have hm' := hm
    obtain ⟨hps, hntp, hso, _⟩ := hdec'
    obtain ⟨h3, h258, hpl, hd1, hd32, hdp, _⟩ := hm'
    simp only [slot.a_run_loop0_loop2.body]
    step*
    all_goals first
      | exact a_idx_step (by assumption) (by assumption)
      | exact ABackInv.part_step hinv (by assumption) (by assumption) (by assumption)
          (by assumption) (by assumption) (by assumption)
      | exact ABackInv.lit_step (t := t) (x := i3) (y := i5) (i4 := i4) hinv (by assumption)
          (by assumption) (by assumption) (by assumption) (by assumption) (by assumption)
          (by assumption) (by assumption) (by assumption) (by assumption) (by assumption)
          (by assumption) (by assumption) (by assumption) (by assumption)
      | exact ABackInv.match_step (t := t) (i6 := i6) (i7 := i7) (i8 := i8) (w := w) (i11 := i11)
          (i12 := i12) hinv (by assumption) (by assumption) (by assumption) (by assumption)
          (by assumption) (by assumption) (by assumption) (by assumption) (by assumption)
          (by assumption) (by assumption) (by assumption) (by assumption) (by assumption)
          (by assumption) (by assumption) (by assumption) (by assumption) (by assumption)
      | exact ⟨hinv, by (subst_vars; scalar_tac (simpAllMaxSteps := 0))⟩
      | (exfalso; (subst_vars; scalar_tac (simpAllMaxSteps := 0)))
  · exact hinv

@[local step]
theorem a_back_loop_spec {W : Std.Usize} (input : Slice Std.U8) (out : Slice Std.U32)
    (nt p «partial» : Std.Usize) (prev : Array Std.U32 W) (l d back : Std.Usize)
    (hp8 : p.val + 8 ≤ input.length) (hW : 0 < W.val) (hdec : ADec input out nt.val p.val)
    (hm : AMatchAt input p.val l.val d.val) :
    slot.a_run_loop0_loop2 input out nt p «partial» prev l d back ⦃ fun r =>
      ADec input r.1 r.2.1.val r.2.2.1.val ∧ r.1.length = out.length ∧
      AMatchAt input r.2.2.1.val r.2.2.2.val d.val ∧
      r.2.2.1.val + r.2.2.2.val = p.val + l.val ∧ r.2.2.1.val ≤ p.val ⦄ := by
  apply Std.WP.spec_mono (a_back_loop_inv input out nt p «partial» prev l d back out.length (p.val + l.val)
    p.val hp8 hW ⟨hdec, rfl, hm, rfl, le_refl _⟩)
  intro r h
  obtain ⟨h1, h2, h3, h4, h5⟩ := h
  exact ⟨h1, h2, h3, h4, h5⟩

theorem a_sat_add_val (x y : Std.Usize) :
    (core.num.Usize.saturating_add x y).val = min Std.Usize.max (x.val + y.val) := by
  have hsz : Std.Usize.max < 2 ^ UScalarTy.Usize.numBits := by
    rw [Std.Usize.max_def, Std.Usize.numBits]
    have : 0 < 2 ^ UScalarTy.Usize.numBits := Nat.two_pow_pos _
    omega
  show (BitVec.ofNat _ (min (UScalar.max UScalarTy.Usize) (x.val + y.val))).toNat = _
  rw [BitVec.toNat_ofNat, UScalar.max_USize_eq, Nat.mod_eq_of_lt (by omega)]

theorem a_sat_add_spec (x y : Std.Usize) :
    lift (core.num.Usize.saturating_add x y) ⦃ fun r =>
      r.val = x.val + y.val ∨ (r.val = Std.Usize.max ∧ Std.Usize.max < x.val + y.val) ⦄ := by
  simp only [lift, Std.WP.spec_ok]
  rw [a_sat_add_val]
  omega

theorem a_sat_sub_val (x y : Std.Usize) :
    (core.num.Usize.saturating_sub x y).val = x.val - y.val := by
  have hx := x.hBounds
  show (BitVec.ofNat _ (max 0 (x.val - y.val))).toNat = x.val - y.val
  rw [BitVec.toNat_ofNat, Nat.zero_max]
  exact Nat.mod_eq_of_lt (lt_of_le_of_lt (Nat.sub_le _ _) hx)

theorem a_sat_sub_spec (x y : Std.Usize) :
    lift (core.num.Usize.saturating_sub x y) ⦃ fun r => r.val = x.val - y.val ⦄ := by
  simp only [lift, Std.WP.spec_ok]
  exact a_sat_sub_val x y

theorem a_tail_sub_ok {ins e t i : Std.Usize} (hi : i = core.num.Usize.wrapping_add ins t)
    (hlt : i < e) (hie : ins.val ≤ e.val) (ht : t.val ≤ 2147483648) : t.val ≤ e.val := by
  have hsz : 4294967296 ≤ Usize.size := by (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  have hil : i.val < e.val := by (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  have hel : e.val < Usize.size := by (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  rw [hi, core.num.Usize.wrapping_add_val_eq, UScalar.size_UScalarTyUsize] at hil
  by_cases hw : ins.val + t.val < Usize.size
  · rw [Nat.mod_eq_of_lt hw] at hil; omega
  · omega

theorem a_tail_ite_spec {ins e t i : Std.Usize} (hi : i = core.num.Usize.wrapping_add ins t)
    (hie : ins.val ≤ e.val) (ht : t.val ≤ 2147483648) :
    (if i < e then e - t else ok ins) ⦃ fun _ => True ⦄ := by
  split
  · have := a_tail_sub_ok hi (by assumption) hie ht
    step*
  · simp only [Std.WP.spec_ok]

@[local step]
theorem a_ins_loop0_spec {H W : Std.Usize} (input : Slice Std.U8) (p : Std.Usize) (mask : Std.U32)
    (head : Array Std.U32 H) (prev : Array Std.U32 W) (ins : Std.Usize) (B : Nat)
    (hB : AHeadBound head B) (hpB : p.val < B + 1) (hp4 : p.val + 4 ≤ Std.Usize.max)
    (hH : 0 < H.val) (hW : 0 < W.val) :
    slot.a_run_loop0_loop0 input p mask head prev ins ⦃ fun r => AHeadBound r.1 B ⦄ := by
  rw [slot.a_run_loop0_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun r => p.val - r.2.2.val)
    (inv := fun r => AHeadBound r.1 B)
  · rintro ⟨head, prev, ins⟩ hB
    simp only at hB
    simp only [slot.a_run_loop0_loop0.body]
    step*
  · exact hB

@[local step]
theorem a_ins_loop3_spec {H W : Std.Usize} (input : Slice Std.U8) (mask : Std.U32)
    (head : Array Std.U32 H) (prev : Array Std.U32 W) (ins stop : Std.Usize) (B : Nat)
    (hB : AHeadBound head B) (hsB : stop.val < B + 1) (hs4 : stop.val + 4 ≤ Std.Usize.max)
    (hH : 0 < H.val) (hW : 0 < W.val) :
    slot.a_run_loop0_loop3 input mask head prev ins stop ⦃ fun r =>
      AHeadBound r.1 B ∧ (r.2.2.val ≤ ins.val ∨ r.2.2.val ≤ stop.val) ⦄ := by
  rw [slot.a_run_loop0_loop3]
  apply Std.loop.spec_decr_nat
    (measure := fun r => stop.val - r.2.2.val)
    (inv := fun r => AHeadBound r.1 B ∧ (r.2.2.val ≤ ins.val ∨ r.2.2.val ≤ stop.val))
  · rintro ⟨head, prev, ins'⟩ ⟨hB, hins⟩
    simp only at hB hins
    simp only [slot.a_run_loop0_loop3.body]
    step*
  · exact ⟨hB, Or.inl (le_refl _)⟩

@[local step]
theorem a_stride_loop_spec {H W : Std.Usize} (input : Slice Std.U8) (mask : Std.U32)
    (stride : Std.Usize) (head : Array Std.U32 H) (prev : Array Std.U32 W) (lim ins e2 : Std.Usize)
    (B : Nat) (hB : AHeadBound head B) (heB : e2.val < B + 1) (hl4 : lim.val + 4 ≤ Std.Usize.max)
    (hH : 0 < H.val) (hW : 0 < W.val) (hS : 0 < stride.val)
    (hS2 : e2.val + stride.val ≤ Std.Usize.max) :
    slot.a_run_loop0_loop4 input mask stride head prev lim ins e2 ⦃ fun r =>
      AHeadBound r.1 B ∧ (r.2.2.val ≤ ins.val ∨ (0 < e2.val ∧ r.2.2.val < e2.val + stride.val)) ⦄ := by
  rw [slot.a_run_loop0_loop4]
  apply Std.loop.spec_decr_nat
    (measure := fun r => e2.val - r.2.2.val)
    (inv := fun r => AHeadBound r.1 B ∧
      (r.2.2.val ≤ ins.val ∨ (0 < e2.val ∧ r.2.2.val < e2.val + stride.val)))
  · rintro ⟨head, prev, ins'⟩ ⟨hB, hins⟩
    simp only at hB hins
    simp only [slot.a_run_loop0_loop4.body]
    step*
    all_goals first
      | exact ⟨hB, hins⟩
      | exact ⟨by assumption, by (subst_vars; scalar_tac (simpAllMaxSteps := 0)), by (subst_vars; scalar_tac (simpAllMaxSteps := 0))⟩
  · exact ⟨hB, Or.inl (le_refl _)⟩

@[local step]
theorem a_ins_loop5_spec {H W : Std.Usize} (input : Slice Std.U8) (mask : Std.U32)
    (head : Array Std.U32 H) (prev : Array Std.U32 W) (lim ins «end» : Std.Usize) (B : Nat)
    (hB : AHeadBound head B) (heB : «end».val < B + 1) (hl4 : lim.val + 4 ≤ Std.Usize.max)
    (hH : 0 < H.val) (hW : 0 < W.val) :
    slot.a_run_loop0_loop5 input mask head prev lim ins «end» ⦃ fun r =>
      AHeadBound r.1 B ∧ (r.2.2.val ≤ ins.val ∨ r.2.2.val ≤ «end».val) ⦄ := by
  rw [slot.a_run_loop0_loop5]
  apply Std.loop.spec_decr_nat
    (measure := fun r => «end».val - r.2.2.val)
    (inv := fun r => AHeadBound r.1 B ∧ (r.2.2.val ≤ ins.val ∨ r.2.2.val ≤ «end».val))
  · rintro ⟨head, prev, ins'⟩ ⟨hB, hins⟩
    simp only at hB hins
    simp only [slot.a_run_loop0_loop5.body]
    step*
  · exact ⟨hB, Or.inl (le_refl _)⟩

@[local step]
theorem a_ins_loop6_spec {H W : Std.Usize} (input : Slice Std.U8) (mask : Std.U32)
    (head : Array Std.U32 H) (prev : Array Std.U32 W) (lim ins «end» : Std.Usize) (B : Nat)
    (hB : AHeadBound head B) (heB : «end».val < B + 1) (hl4 : lim.val + 4 ≤ Std.Usize.max)
    (hH : 0 < H.val) (hW : 0 < W.val) :
    slot.a_run_loop0_loop6 input mask head prev lim ins «end» ⦃ fun r =>
      AHeadBound r.1 B ∧ (r.2.2.val ≤ ins.val ∨ r.2.2.val ≤ «end».val) ⦄ := by
  rw [slot.a_run_loop0_loop6]
  apply Std.loop.spec_decr_nat
    (measure := fun r => «end».val - r.2.2.val)
    (inv := fun r => AHeadBound r.1 B ∧ (r.2.2.val ≤ ins.val ∨ r.2.2.val ≤ «end».val))
  · rintro ⟨head, prev, ins'⟩ ⟨hB, hins⟩
    simp only at hB hins
    simp only [slot.a_run_loop0_loop6.body]
    step*
  · exact ⟨hB, Or.inl (le_refl _)⟩

@[local step]
theorem a_skip_loop_spec (input : Slice Std.U8) (out : Slice Std.U32) (nt p lim step : Std.Usize)
    (hdec : ADec input out nt.val p.val) (hlim : lim.val ≤ input.length) :
    slot.a_run_loop0_loop7 input out nt p lim step ⦃ fun r =>
      ADec input r.1 r.2.1.val r.2.2.val ∧ r.1.length = out.length ∧ p.val ≤ r.2.2.val ⦄ := by
  rw [slot.a_run_loop0_loop7]
  apply Std.loop.spec_decr_nat
    (measure := fun r => r.2.2.2.val)
    (inv := fun r => ADec input r.1 r.2.1.val r.2.2.1.val ∧ r.1.length = out.length ∧
      p.val ≤ r.2.2.1.val)
  · rintro ⟨out', nt', p', step'⟩ ⟨hdec', hlen', hp'⟩
    simp only at hdec' hlen' hp'
    simp only [slot.a_run_loop0_loop7.body]
    step*
  · exact ⟨hdec, rfl, le_refl _⟩

@[local step]
theorem a_tail_loop1_spec (input : Slice Std.U8) (out : Slice Std.U32) (n nt p : Std.Usize)
    (hn : n.val = input.length) (hdec : ADec input out nt.val p.val) :
    slot.a_run_loop1 input out n nt p ⦃ fun r => r.1.val ≤ input.length ∧
      r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
  rw [slot.a_run_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun r => n.val - r.2.2.val)
    (inv := fun r => ADec input r.1 r.2.1.val r.2.2.val ∧ r.1.length = out.length)
  · rintro ⟨out', nt', p'⟩ ⟨hdec', hlen'⟩
    simp only at hdec' hlen'
    simp only [slot.a_run_loop1.body]
    step*
    have hd := ADec.done hdec' (by (subst_vars; scalar_tac (simpAllMaxSteps := 0)))
    exact ⟨hd.1, hlen', hd.2⟩
  · exact ⟨hdec, rfl⟩

@[local step]
theorem a_tail_loop2_spec (input : Slice Std.U8) (out : Slice Std.U32) (n nt p : Std.Usize)
    (hn : n.val = input.length) (hdec : ADec input out nt.val p.val) :
    slot.a_run_loop2 input out n nt p ⦃ fun r => r.1.val ≤ input.length ∧
      r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
  rw [slot.a_run_loop2]
  apply Std.loop.spec_decr_nat
    (measure := fun r => n.val - r.2.2.val)
    (inv := fun r => ADec input r.1 r.2.1.val r.2.2.val ∧ r.1.length = out.length)
  · rintro ⟨out', nt', p'⟩ ⟨hdec', hlen'⟩
    simp only at hdec' hlen'
    simp only [slot.a_run_loop2.body]
    step*
    have hd := ADec.done hdec' (by (subst_vars; scalar_tac (simpAllMaxSteps := 0)))
    exact ⟨hd.1, hlen', hd.2⟩
  · exact ⟨hdec, rfl⟩

@[local step]
theorem a_tail_loop3_spec (input : Slice Std.U8) (out : Slice Std.U32) (n nt p : Std.Usize)
    (hn : n.val = input.length) (hdec : ADec input out nt.val p.val) :
    slot.a_run_loop3 input out n nt p ⦃ fun r => r.1.val ≤ input.length ∧
      r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
  rw [slot.a_run_loop3]
  apply Std.loop.spec_decr_nat
    (measure := fun r => n.val - r.2.2.val)
    (inv := fun r => ADec input r.1 r.2.1.val r.2.2.val ∧ r.1.length = out.length)
  · rintro ⟨out', nt', p'⟩ ⟨hdec', hlen'⟩
    simp only at hdec' hlen'
    simp only [slot.a_run_loop3.body]
    step*
    have hd := ADec.done hdec' (by (subst_vars; scalar_tac (simpAllMaxSteps := 0)))
    exact ⟨hd.1, hlen', hd.2⟩
  · exact ⟨hdec, rfl⟩

def AMainInv (input : Slice Std.U8) (L : Nat) (out : Slice Std.U32) (nt p : Nat)
    {N : Std.Usize} (head : Array Std.U32 N) (miss : Nat) : Prop :=
  ADec input out nt p ∧ out.length = L ∧ AHeadBound head p ∧ miss ≤ p

theorem AMainInv.mk' {input : Slice Std.U8} {L : Nat} {out : Slice Std.U32} {nt p m B : Nat}
    {N : Std.Usize} {head : Array Std.U32 N} (hdec : ADec input out nt p) (hlen : out.length = L)
    (hB : AHeadBound head B) (hBp : B ≤ p) (hm : m ≤ p) : AMainInv input L out nt p head m :=
  ⟨hdec, hlen, AHeadBound.mono hB hBp, hm⟩

set_option maxHeartbeats 16000000 in
attribute [local step] a_sat_add_spec a_sat_sub_spec in
theorem a_main_loop_spec {H W : Std.Usize} (input : Slice Std.U8) (out : Slice Std.U32)
    (nt p : Std.Usize) (mask : Std.U32)
    (minl depth l2d «partial» lazy skip skcap nice ldep insm stride : Std.Usize) (hlit : Std.I32)
    (head : Array Std.U32 H) (prev : Array Std.U32 W) (lim ins miss fuel : Std.Usize) (L : Nat)
    (hlim : lim.val + 8 = input.length) (hminl : 3 ≤ minl.val)
    (hminl8 : minl.val ≤ 8) (hskip : skip.val < 32) (hH : 0 < H.val) (hW : 0 < W.val)
    (hh0 : 0 ≤ hlit.val) (hh1 : hlit.val ≤ 1000000)
    (hinv : AMainInv input L out nt.val p.val head miss.val) :
    slot.a_run_loop0 input out nt p mask minl depth l2d «partial» lazy skip skcap nice ldep insm stride hlit
      head prev lim ins miss fuel ⦃ fun r => ADec input r.1 r.2.1.val r.2.2.val ∧ r.1.length = L ⦄ := by
  rw [slot.a_run_loop0]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  apply Std.loop.spec_decr_nat
    (measure := fun r => r.2.2.2.2.2.2.2.val)
    (inv := fun r => AMainInv input L r.1 r.2.1.val r.2.2.1.val r.2.2.2.1 r.2.2.2.2.2.2.1.val)
  · rintro ⟨out, nt, p, head, prev, ins, miss, fuel⟩ hinv
    simp only at hinv
    have hinv' := hinv
    obtain ⟨hdec, hL, hB, hmiss⟩ := hinv'
    simp only [slot.a_run_loop0.body]
    step*
    case hm => exact AFoundAt.real (by assumption) (by (subst_vars; scalar_tac (simpAllMaxSteps := 0)))
    case hB => exact AHeadBound.mono (by assumption) (by omega)
    case hy => have := numBits_ge; (subst_vars; scalar_tac (simpAllMaxSteps := 0))
    ·
      apply WP.spec_bind (a_ite_dspec _ _ _ (fun (x : Std.Usize) => x.val ≤ «end».val)
        (fun h => by (subst_vars; scalar_tac (simpAllMaxSteps := 0))) (fun _ => le_refl _))
      intro stop hstop
      apply WP.spec_bind (a_ite_dspec _ _ _
        (fun (x : Std.Usize) => x.val ≤ «end».val ∧ x.val ≤ lim.val)
        (fun h => ⟨by (subst_vars; scalar_tac (simpAllMaxSteps := 0)), le_refl _⟩) (fun h => ⟨hstop, by (subst_vars; scalar_tac (simpAllMaxSteps := 0))⟩))
      intro stop1 hstop1
      step*
      case heB => (subst_vars; scalar_tac (simpAllMaxSteps := 0))
      case hS2 => (subst_vars; scalar_tac (simpAllMaxSteps := 0))
      all_goals
        apply WP.spec_bind (a_tail_ite_spec (by assumption) (by (subst_vars; scalar_tac (simpAllMaxSteps := 0))) (by (subst_vars; scalar_tac (simpAllMaxSteps := 0))))
        intro ins5 _
        step*
        all_goals (refine ⟨AMainInv.mk' (by assumption) (by omega) (by assumption) (by omega)
          (by simp), by omega⟩)
    ·
      apply WP.spec_bind (a_ite_spec _ _ _ (fun _ => True) trivial trivial)
      intro step1 _
      step*
      all_goals first
        | (refine ⟨AMainInv.mk' (by assumption) (by omega) (by assumption) (by omega)
            (by omega), by omega⟩)
        | exact ADec.cast (by assumption) (by omega)
  · exact hinv

@[local step]
theorem a_main_loop_spec' {H W : Std.Usize} (input : Slice Std.U8) (out : Slice Std.U32)
    (nt p : Std.Usize) (mask : Std.U32)
    (minl depth l2d «partial» lazy skip skcap nice ldep insm stride : Std.Usize) (hlit : Std.I32)
    (head : Array Std.U32 H) (prev : Array Std.U32 W) (lim ins miss fuel : Std.Usize)
    (hlim : lim.val + 8 = input.length) (hminl : 3 ≤ minl.val)
    (hminl8 : minl.val ≤ 8) (hskip : skip.val < 32) (hH : 0 < H.val) (hW : 0 < W.val)
    (hh0 : 0 ≤ hlit.val) (hh1 : hlit.val ≤ 1000000)
    (hdec : ADec input out nt.val p.val) (hB : AHeadBound head p.val) (hmiss : miss.val ≤ p.val) :
    slot.a_run_loop0 input out nt p mask minl depth l2d «partial» lazy skip skcap nice ldep insm stride hlit
      head prev lim ins miss fuel ⦃ fun r =>
        ADec input r.1 r.2.1.val r.2.2.val ∧ r.1.length = out.length ⦄ :=
  a_main_loop_spec input out nt p mask minl depth l2d «partial» lazy skip skcap nice ldep insm stride hlit head
    prev lim ins miss fuel out.length hlim hminl hminl8 hskip hH hW hh0 hh1
    ⟨hdec, rfl, hB, hmiss⟩

theorem a_lazy_dna_inv {H W : Std.Usize} (input : Slice Std.U8) (out : Slice Std.U32)
    (nt p minl lazy : Std.Usize) (hlit : Std.I32) (head : Array Std.U32 H)
    (prev : Array Std.U32 W) (lim ins l d : Std.Usize) (go : Std.U32) (L : Nat)
    (hlim : lim.val + 8 = input.length) (hminl : 3 ≤ minl.val) (hminl10 : minl.val ≤ 10)
    (hH : 0 < H.val) (hW : 0 < W.val) (hh0 : 0 ≤ hlit.val) (hh1 : hlit.val ≤ 1000000)
    (hinv : ALazyInv input L lim.val out nt.val p.val head ins.val l.val d.val) :
    slot.a_run_dna_loop0_loop1 input out nt p minl lazy hlit head prev lim ins l d go ⦃ fun r =>
      ALazyInv input L lim.val r.1 r.2.1.val r.2.2.1.val r.2.2.2.1 r.2.2.2.2.2.1.val
        r.2.2.2.2.2.2.1.val r.2.2.2.2.2.2.2.val ⦄ := by
  rw [slot.a_run_dna_loop0_loop1]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  apply Std.loop.spec_decr_nat
    (measure := fun r => lim.val - r.2.2.1.val + r.2.2.2.2.2.2.2.2.val)
    (inv := fun r => ALazyInv input L lim.val r.1 r.2.1.val r.2.2.1.val r.2.2.2.1
      r.2.2.2.2.2.1.val r.2.2.2.2.2.2.1.val r.2.2.2.2.2.2.2.1.val)
  · clear hinv
    rintro ⟨out, nt, p, head, prev, ins, l, d, go⟩ hinv
    simp only at hinv
    have hinv' := hinv
    obtain ⟨hdec, hL, hm, hB, hplim, hins⟩ := hinv'
    have hdec' := hdec
    have hm' := hm
    obtain ⟨hps, hntp, hso, -⟩ := hdec'
    obtain ⟨h3, h258, hpl, hd1, hd32, hdp, -⟩ := hm'
    simp only [slot.a_run_dna_loop0_loop1.body]
    step*

    apply WP.spec_bind (Pₘ := fun (h : Std.Usize) => h.val + 1 ≤ l.val)
    · split
      · step*
      · simp only [Std.WP.spec_ok]; (subst_vars; scalar_tac (simpAllMaxSteps := 0))
    intro «have» hhave
    step*
    all_goals first
      | exact ALazyInv.reject_step hinv (by assumption) (by omega) (by omega)
      | exact ALazyInv.accept_step hinv hminl (by assumption) (by assumption) (by assumption)
          (by assumption) (by omega) (by omega) (by omega) (by omega) (by assumption) (by omega)
  · exact hinv

@[local step]
theorem a_lazy_dna_spec {H W : Std.Usize} (input : Slice Std.U8) (out : Slice Std.U32)
    (nt p minl lazy : Std.Usize) (hlit : Std.I32) (head : Array Std.U32 H)
    (prev : Array Std.U32 W) (lim ins l d : Std.Usize) (go : Std.U32) (L : Nat)
    (hlim : lim.val + 8 = input.length) (hminl : 3 ≤ minl.val) (hminl10 : minl.val ≤ 10)
    (hH : 0 < H.val) (hW : 0 < W.val) (hh0 : 0 ≤ hlit.val) (hh1 : hlit.val ≤ 1000000)
    (hdec : ADec input out nt.val p.val) (hlen : out.length = L)
    (hm : AMatchAt input p.val l.val d.val) (hB : AHeadBound head (p.val + 2))
    (hplim : p.val < lim.val) (hins : ins.val ≤ p.val + 3) :
    slot.a_run_dna_loop0_loop1 input out nt p minl lazy hlit head prev lim ins l d go ⦃ fun r =>
      ADec input r.1 r.2.1.val r.2.2.1.val ∧ r.1.length = L ∧
      AMatchAt input r.2.2.1.val r.2.2.2.2.2.2.1.val r.2.2.2.2.2.2.2.val ∧
      AHeadBound r.2.2.2.1 (r.2.2.1.val + r.2.2.2.2.2.2.1.val) ∧ r.2.2.1.val < lim.val ∧
      r.2.2.2.2.2.1.val ≤ r.2.2.1.val + 3 ∧ 3 ≤ r.2.2.2.2.2.2.1.val ⦄ := by
  apply Std.WP.spec_mono (a_lazy_dna_inv input out nt p minl lazy hlit head prev lim ins l d go L
    hlim hminl hminl10 hH hW hh0 hh1 ⟨hdec, hlen, hm, hB, hplim, hins⟩)
  rintro ⟨out', nt', p', head', prev', ins', l', d'⟩ ⟨hdec', hlen', hm', hB', hplim', hins'⟩
  exact ⟨hdec', hlen', hm', AHeadBound.mono hB' (by have := hm'.1; omega), hplim', hins', hm'.1⟩

theorem a_back_dna_inv (input : Slice Std.U8) (out : Slice Std.U32) (nt p l d back : Std.Usize)
    (L E P0 : Nat) (hP0 : P0 + 8 ≤ input.length)
    (hinv : ABackInv input L d.val E P0 out nt.val p.val l.val) :
    slot.a_run_dna_loop0_loop2 input out nt p l d back ⦃ fun r =>
      ABackInv input L d.val E P0 out r.1.val r.2.1.val r.2.2.val ⦄ := by
  rw [slot.a_run_dna_loop0_loop2]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  apply Std.loop.spec_decr_nat
    (measure := fun r => slot.A_BACKTOK.val - r.2.2.2.val)
    (inv := fun r => ABackInv input L d.val E P0 out r.1.val r.2.1.val r.2.2.1.val)
  · rintro ⟨nt, p, l, back⟩ hinv
    simp only at hinv
    have hinv' := hinv
    obtain ⟨⟨hps, hntp, hso, _⟩, hL, ⟨h3, h258, hpl, hd1, hd32, hdp, _⟩, hE, hp0⟩ := hinv'
    simp only [slot.a_run_dna_loop0_loop2.body]
    step*
    all_goals first
      | exact ABackInv.lit_step (t := t) (x := i3) (y := i5) (i4 := i4) hinv (by assumption)
          (by assumption) (by assumption) (by assumption) (by assumption) (by assumption)
          (by assumption) (by assumption) (by assumption) (by assumption) (by assumption)
          (by assumption) (by assumption) (by assumption) (by assumption)
      | exact ABackInv.match_step (t := t) (i6 := i6) (i7 := i7) (i8 := i8) (w := w) (i11 := i11)
          (i12 := i12) hinv (by assumption) (by assumption) (by assumption) (by assumption)
          (by assumption) (by assumption) (by assumption) (by assumption) (by assumption)
          (by assumption) (by assumption) (by assumption) (by assumption) (by assumption)
          (by assumption) (by assumption) (by assumption) (by assumption) (by assumption)
  · exact hinv

@[local step]
theorem a_back_dna_spec (input : Slice Std.U8) (out : Slice Std.U32) (nt p l d back : Std.Usize)
    (hp8 : p.val + 8 ≤ input.length) (hdec : ADec input out nt.val p.val)
    (hm : AMatchAt input p.val l.val d.val) :
    slot.a_run_dna_loop0_loop2 input out nt p l d back ⦃ fun r =>
      ADec input out r.1.val r.2.1.val ∧ AMatchAt input r.2.1.val r.2.2.val d.val ∧
      r.2.1.val + r.2.2.val = p.val + l.val ∧ r.2.1.val ≤ p.val ⦄ := by
  apply Std.WP.spec_mono (a_back_dna_inv input out nt p l d back out.length (p.val + l.val) p.val hp8
    ⟨hdec, rfl, hm, rfl, le_refl _⟩)
  intro r h
  obtain ⟨h1, _, h3, h4, h5⟩ := h
  exact ⟨h1, h3, h4, h5⟩

@[local step]
theorem a_ins_dna0_spec {H W : Std.Usize} (input : Slice Std.U8) (p : Std.Usize)
    (head : Array Std.U32 H) (prev : Array Std.U32 W) (ins : Std.Usize) (B : Nat)
    (hB : AHeadBound head B) (hpB : p.val < B + 1) (hp8 : p.val + 8 ≤ input.length)
    (hH : 0 < H.val) (hW : 0 < W.val) :
    slot.a_run_dna_loop0_loop0 input p head prev ins ⦃ fun r => AHeadBound r.1 B ⦄ := by
  rw [slot.a_run_dna_loop0_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun r => p.val - r.2.2.val)
    (inv := fun r => AHeadBound r.1 B)
  · rintro ⟨head, prev, ins⟩ hB
    simp only at hB
    simp only [slot.a_run_dna_loop0_loop0.body]
    step*
  · exact hB

@[local step]
theorem a_ins_dna3_spec {H W : Std.Usize} (input : Slice Std.U8)
    (head : Array Std.U32 H) (prev : Array Std.U32 W) (ins stop : Std.Usize) (B : Nat)
    (hB : AHeadBound head B) (hsB : stop.val < B + 1) (hs8 : stop.val + 8 ≤ input.length)
    (hH : 0 < H.val) (hW : 0 < W.val) :
    slot.a_run_dna_loop0_loop3 input head prev ins stop ⦃ fun r =>
      AHeadBound r.1 B ∧ (r.2.2.val ≤ ins.val ∨ r.2.2.val ≤ stop.val) ⦄ := by
  rw [slot.a_run_dna_loop0_loop3]
  apply Std.loop.spec_decr_nat
    (measure := fun r => stop.val - r.2.2.val)
    (inv := fun r => AHeadBound r.1 B ∧ (r.2.2.val ≤ ins.val ∨ r.2.2.val ≤ stop.val))
  · rintro ⟨head, prev, ins'⟩ ⟨hB, hins⟩
    simp only at hB hins
    simp only [slot.a_run_dna_loop0_loop3.body]
    step*
  · exact ⟨hB, Or.inl (le_refl _)⟩

@[local step]
theorem a_stride_dna_spec {H W : Std.Usize} (input : Slice Std.U8)
    (head : Array Std.U32 H) (prev : Array Std.U32 W) (lim ins e2 : Std.Usize)
    (B : Nat) (hB : AHeadBound head B) (heB : e2.val < B + 1) (hl8 : lim.val + 8 = input.length)
    (hH : 0 < H.val) (hW : 0 < W.val) (hS : 0 < slot.A_STRIDE.val)
    (hS2 : e2.val + slot.A_STRIDE.val ≤ Std.Usize.max) :
    slot.a_run_dna_loop0_loop4 input head prev lim ins e2 ⦃ fun r =>
      AHeadBound r.1 B ∧
        (r.2.2.val ≤ ins.val ∨ (0 < e2.val ∧ r.2.2.val < e2.val + slot.A_STRIDE.val)) ⦄ := by
  rw [slot.a_run_dna_loop0_loop4]
  apply Std.loop.spec_decr_nat
    (measure := fun r => e2.val - r.2.2.val)
    (inv := fun r => AHeadBound r.1 B ∧
      (r.2.2.val ≤ ins.val ∨ (0 < e2.val ∧ r.2.2.val < e2.val + slot.A_STRIDE.val)))
  · rintro ⟨head, prev, ins'⟩ ⟨hB, hins⟩
    simp only at hB hins
    simp only [slot.a_run_dna_loop0_loop4.body]
    step*
    all_goals first
      | exact ⟨hB, hins⟩
      | exact ⟨by assumption, by (subst_vars; scalar_tac (simpAllMaxSteps := 0)), by (subst_vars; scalar_tac (simpAllMaxSteps := 0))⟩
  · exact ⟨hB, Or.inl (le_refl _)⟩

@[local step]
theorem a_ins_dna5_spec {H W : Std.Usize} (input : Slice Std.U8)
    (head : Array Std.U32 H) (prev : Array Std.U32 W) (lim ins «end» : Std.Usize) (B : Nat)
    (hB : AHeadBound head B) (heB : «end».val < B + 1) (hl8 : lim.val + 8 = input.length)
    (hH : 0 < H.val) (hW : 0 < W.val) :
    slot.a_run_dna_loop0_loop5 input head prev lim ins «end» ⦃ fun r =>
      AHeadBound r.1 B ∧ (r.2.2.val ≤ ins.val ∨ r.2.2.val ≤ «end».val) ⦄ := by
  rw [slot.a_run_dna_loop0_loop5]
  apply Std.loop.spec_decr_nat
    (measure := fun r => «end».val - r.2.2.val)
    (inv := fun r => AHeadBound r.1 B ∧ (r.2.2.val ≤ ins.val ∨ r.2.2.val ≤ «end».val))
  · rintro ⟨head, prev, ins'⟩ ⟨hB, hins⟩
    simp only at hB hins
    simp only [slot.a_run_dna_loop0_loop5.body]
    step*
  · exact ⟨hB, Or.inl (le_refl _)⟩

@[local step]
theorem a_ins_dna6_spec {H W : Std.Usize} (input : Slice Std.U8)
    (head : Array Std.U32 H) (prev : Array Std.U32 W) (lim ins «end» : Std.Usize) (B : Nat)
    (hB : AHeadBound head B) (heB : «end».val < B + 1) (hl8 : lim.val + 8 = input.length)
    (hH : 0 < H.val) (hW : 0 < W.val) :
    slot.a_run_dna_loop0_loop6 input head prev lim ins «end» ⦃ fun r =>
      AHeadBound r.1 B ∧ (r.2.2.val ≤ ins.val ∨ r.2.2.val ≤ «end».val) ⦄ := by
  rw [slot.a_run_dna_loop0_loop6]
  apply Std.loop.spec_decr_nat
    (measure := fun r => «end».val - r.2.2.val)
    (inv := fun r => AHeadBound r.1 B ∧ (r.2.2.val ≤ ins.val ∨ r.2.2.val ≤ «end».val))
  · rintro ⟨head, prev, ins'⟩ ⟨hB, hins⟩
    simp only at hB hins
    simp only [slot.a_run_dna_loop0_loop6.body]
    step*
  · exact ⟨hB, Or.inl (le_refl _)⟩

@[local step]
theorem a_skip_dna_spec (input : Slice Std.U8) (out : Slice Std.U32) (nt p lim step : Std.Usize)
    (hdec : ADec input out nt.val p.val) (hlim : lim.val ≤ input.length) :
    slot.a_run_dna_loop0_loop7 input out nt p lim step ⦃ fun r =>
      ADec input r.1 r.2.1.val r.2.2.val ∧ r.1.length = out.length ∧ p.val ≤ r.2.2.val ⦄ := by
  rw [slot.a_run_dna_loop0_loop7]
  apply Std.loop.spec_decr_nat
    (measure := fun r => r.2.2.2.val)
    (inv := fun r => ADec input r.1 r.2.1.val r.2.2.1.val ∧ r.1.length = out.length ∧
      p.val ≤ r.2.2.1.val)
  · rintro ⟨out', nt', p', step'⟩ ⟨hdec', hlen', hp'⟩
    simp only at hdec' hlen' hp'
    simp only [slot.a_run_dna_loop0_loop7.body]
    step*
  · exact ⟨hdec, rfl, le_refl _⟩

@[local step]
theorem a_tail_dna1_spec (input : Slice Std.U8) (out : Slice Std.U32) (n nt p : Std.Usize)
    (hn : n.val = input.length) (hdec : ADec input out nt.val p.val) :
    slot.a_run_dna_loop1 input out n nt p ⦃ fun r => r.1.val ≤ input.length ∧
      r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
  rw [slot.a_run_dna_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun r => n.val - r.2.2.val)
    (inv := fun r => ADec input r.1 r.2.1.val r.2.2.val ∧ r.1.length = out.length)
  · rintro ⟨out', nt', p'⟩ ⟨hdec', hlen'⟩
    simp only at hdec' hlen'
    simp only [slot.a_run_dna_loop1.body]
    step*
    have hd := ADec.done hdec' (by (subst_vars; scalar_tac (simpAllMaxSteps := 0)))
    exact ⟨hd.1, hlen', hd.2⟩
  · exact ⟨hdec, rfl⟩

@[local step]
theorem a_tail_dna2_spec (input : Slice Std.U8) (out : Slice Std.U32) (n nt p : Std.Usize)
    (hn : n.val = input.length) (hdec : ADec input out nt.val p.val) :
    slot.a_run_dna_loop2 input out n nt p ⦃ fun r => r.1.val ≤ input.length ∧
      r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
  rw [slot.a_run_dna_loop2]
  apply Std.loop.spec_decr_nat
    (measure := fun r => n.val - r.2.2.val)
    (inv := fun r => ADec input r.1 r.2.1.val r.2.2.val ∧ r.1.length = out.length)
  · rintro ⟨out', nt', p'⟩ ⟨hdec', hlen'⟩
    simp only at hdec' hlen'
    simp only [slot.a_run_dna_loop2.body]
    step*
    have hd := ADec.done hdec' (by (subst_vars; scalar_tac (simpAllMaxSteps := 0)))
    exact ⟨hd.1, hlen', hd.2⟩
  · exact ⟨hdec, rfl⟩

set_option maxHeartbeats 16000000 in
attribute [local step] a_sat_add_spec a_sat_sub_spec in
theorem a_main_dna_spec {H W : Std.Usize} (input : Slice Std.U8) (out : Slice Std.U32)
    (nt p minl depth lazy skip skcap : Std.Usize) (hlit : Std.I32)
    (head : Array Std.U32 H) (prev : Array Std.U32 W) (lim ins miss fuel : Std.Usize) (L : Nat)
    (hlim : lim.val + 8 = input.length) (hminl : 3 ≤ minl.val) (hminl10 : minl.val ≤ 10)
    (hskip : skip.val < 32) (hH : 0 < H.val) (hW : 0 < W.val)
    (hh0 : 0 ≤ hlit.val) (hh1 : hlit.val ≤ 1000000)
    (hinv : AMainInv input L out nt.val p.val head miss.val) :
    slot.a_run_dna_loop0 input out nt p minl depth lazy skip skcap hlit head prev lim ins miss fuel
      ⦃ fun r => ADec input r.1 r.2.1.val r.2.2.val ∧ r.1.length = L ⦄ := by
  rw [slot.a_run_dna_loop0]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  apply Std.loop.spec_decr_nat
    (measure := fun r => r.2.2.2.2.2.2.2.val)
    (inv := fun r => AMainInv input L r.1 r.2.1.val r.2.2.1.val r.2.2.2.1 r.2.2.2.2.2.2.1.val)
  · rintro ⟨out, nt, p, head, prev, ins, miss, fuel⟩ hinv
    simp only at hinv
    have hinv' := hinv
    obtain ⟨hdec, hL, hB, hmiss⟩ := hinv'
    simp only [slot.a_run_dna_loop0.body]
    step*
    case hm => exact AFoundAt.real (by assumption) (by (subst_vars; scalar_tac (simpAllMaxSteps := 0)))
    case hB => exact AHeadBound.mono (by assumption) (by omega)
    case hy => have := numBits_ge; (subst_vars; scalar_tac (simpAllMaxSteps := 0))
    ·
      apply WP.spec_bind (a_ite_dspec _ _ _ (fun (x : Std.Usize) => x.val ≤ «end».val)
        (fun h => by (subst_vars; scalar_tac (simpAllMaxSteps := 0))) (fun _ => le_refl _))
      intro stop hstop
      apply WP.spec_bind (a_ite_dspec _ _ _
        (fun (x : Std.Usize) => x.val ≤ «end».val ∧ x.val ≤ lim.val)
        (fun h => ⟨by (subst_vars; scalar_tac (simpAllMaxSteps := 0)), le_refl _⟩) (fun h => ⟨hstop, by (subst_vars; scalar_tac (simpAllMaxSteps := 0))⟩))
      intro stop1 hstop1
      step*
      all_goals first
        | (apply WP.spec_bind (a_tail_ite_spec (by assumption) (by (subst_vars; scalar_tac (simpAllMaxSteps := 0))) (by (subst_vars; scalar_tac (simpAllMaxSteps := 0))))
           intro ins5 _
           step*
           all_goals (refine ⟨AMainInv.mk' (by assumption) (by omega) (by assumption) (by omega)
             (by simp), by omega⟩))
        | (subst_vars; scalar_tac (simpAllMaxSteps := 0))
    ·
      apply WP.spec_bind (a_ite_spec _ _ _ (fun _ => True) trivial trivial)
      intro step1 _
      step*
      all_goals first
        | (refine ⟨AMainInv.mk' (by assumption) (by omega) (by assumption) (by omega)
            (by omega), by omega⟩)
        | exact ADec.cast (by assumption) (by omega)
  · exact hinv

@[local step]
theorem a_main_dna_spec' {H W : Std.Usize} (input : Slice Std.U8) (out : Slice Std.U32)
    (nt p minl depth lazy skip skcap : Std.Usize) (hlit : Std.I32)
    (head : Array Std.U32 H) (prev : Array Std.U32 W) (lim ins miss fuel : Std.Usize)
    (hlim : lim.val + 8 = input.length) (hminl : 3 ≤ minl.val) (hminl10 : minl.val ≤ 10)
    (hskip : skip.val < 32) (hH : 0 < H.val) (hW : 0 < W.val)
    (hh0 : 0 ≤ hlit.val) (hh1 : hlit.val ≤ 1000000)
    (hdec : ADec input out nt.val p.val) (hB : AHeadBound head p.val) (hmiss : miss.val ≤ p.val) :
    slot.a_run_dna_loop0 input out nt p minl depth lazy skip skcap hlit head prev lim ins miss fuel
      ⦃ fun r => ADec input r.1 r.2.1.val r.2.2.val ∧ r.1.length = out.length ⦄ :=
  a_main_dna_spec input out nt p minl depth lazy skip skcap hlit head prev lim ins miss fuel
    out.length hlim hminl hminl10 hskip hH hW hh0 hh1 ⟨hdec, rfl, hB, hmiss⟩

def ACntBound (cnt : Array Std.U32 256#usize) (T : Nat) : Prop :=
  ∀ j : Nat, j < 256 → (cnt.val[j]!).val ≤ T

theorem ACntBound.init : ACntBound (Std.Array.repeat 256#usize 0#u32) 0 := by
  intro j hj
  rw [Std.Array.repeat_val, List.getElem!_eq_getElem?_getD,
    List.getElem?_replicate_of_lt (by simpa using hj)]
  rfl

theorem ACntBound.get {cnt : Array Std.U32 256#usize} {T : Nat} (h : ACntBound cnt T)
    (a : Std.Usize) (x : Std.U32) (ha : a.val < cnt.val.length) (hx : x = cnt.val[a.val]) :
    x.val ≤ T := by
  have := h a.val (by simpa using ha)
  rw [getElem!_pos cnt.val a.val ha, ← hx] at this
  exact this

theorem a_cnt_index_spec (cnt : Array Std.U32 256#usize) (T : Nat) (h : ACntBound cnt T)
    (i : Std.Usize) (hi : i.val < 256) :
    Std.Array.index_usize cnt i ⦃ fun x => x = cnt.val[i.val]! ∧ x.val ≤ T ⦄ := by
  have hl : i.val < cnt.val.length := by simp; omega
  have := Std.Array.index_usize_spec cnt i (by simpa using hl)
  apply Std.WP.spec_mono this
  intro x hx
  refine ⟨by rw [getElem!_pos cnt.val i.val hl]; exact hx, ACntBound.get h i x hl hx⟩

theorem ACntBound.update {cnt : Array Std.U32 256#usize} {T : Nat} (h : ACntBound cnt T)
    (a : Std.Usize) (v : Std.U32) (hv : v.val ≤ T + 1) : ACntBound (cnt.set a v) (T + 1) := by
  intro j hj
  rw [Std.Array.set_val_eq]
  by_cases hja : a.val = j
  · subst hja
    have hlen : a.val < cnt.val.length := by simp; omega
    rw [List.getElem!_eq_getElem?_getD, List.getElem?_set_self hlen]
    exact hv
  · rw [List.getElem!_eq_getElem?_getD, List.getElem?_set_ne hja, ← List.getElem!_eq_getElem?_getD]
    exact le_trans (h j hj) (by omega)

theorem ACntBound.step {cnt a : Array Std.U32 256#usize} {T : Nat} {x : Std.Usize}
    {v tot1 : Std.U32} (hc : ACntBound cnt T) (ha : a = cnt.set x v) (hv : v.val ≤ T + 1)
    (ht1 : tot1.val = T + 1) : ACntBound a tot1.val := by
  rw [ha, ht1]
  exact ACntBound.update hc x v hv

theorem ACntBound.mono {cnt : Array Std.U32 256#usize} {T T' : Nat} (h : ACntBound cnt T)
    (hT : T ≤ T') : ACntBound cnt T' := fun j hj => le_trans (h j hj) hT

attribute [local step] a_cnt_index_spec in
theorem a_sniff_loop0_spec (s : Slice Std.U8) (n : Std.Usize) (cnt : Array Std.U32 256#usize)
    (step i : Std.Usize) (tot : Std.U32) (hn : n.val = s.length) (hc : ACntBound cnt tot.val)
    (ht : tot.val ≤ 4097) :
    slot.a_sniff_loop0 s n cnt step i tot ⦃ fun r => ACntBound r.1 r.2.val ∧ r.2.val ≤ 4097 ⦄ := by
  rw [slot.a_sniff_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun r => 4097 - r.2.2.val)
    (inv := fun r => ACntBound r.1 r.2.2.val ∧ r.2.2.val ≤ 4097)
  · rintro ⟨cnt, i, tot⟩ ⟨hc, ht⟩
    simp only at hc ht
    simp only [slot.a_sniff_loop0.body]
    step*
    all_goals first
      | exact ⟨hc, ht⟩
      | exact ⟨ACntBound.step hc (by assumption) (by (subst_vars; scalar_tac (simpAllMaxSteps := 0))) (by (subst_vars; scalar_tac (simpAllMaxSteps := 0))), by (subst_vars; scalar_tac (simpAllMaxSteps := 0)),
          by (subst_vars; scalar_tac (simpAllMaxSteps := 0))⟩
  · exact ⟨hc, ht⟩

attribute [local step] a_cnt_index_spec in
theorem a_sniff_loop1_spec (cnt : Array Std.U32 256#usize) (text high words : Std.U32) (b : Std.Usize)
    (hc : ACntBound cnt 4097) (htext : text.val ≤ (b.val + 3) * 4097)
    (hhigh : high.val ≤ b.val * 4097) (hwords : words.val ≤ (b.val + 1) * 4097)
    (hb : b.val ≤ 256) :
    slot.a_sniff_loop1 cnt text high words b ⦃ fun _ => True ⦄ := by
  rw [slot.a_sniff_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun r => 256 - r.2.2.2.val)
    (inv := fun r => r.1.val ≤ (r.2.2.2.val + 3) * 4097 ∧ r.2.1.val ≤ r.2.2.2.val * 4097 ∧
      r.2.2.1.val ≤ (r.2.2.2.val + 1) * 4097 ∧ r.2.2.2.val ≤ 256)
  · rintro ⟨text, high, words, b⟩ ⟨htext, hhigh, hwords, hb⟩
    simp only at htext hhigh hwords hb
    simp only [slot.a_sniff_loop1.body]
    split
    ·
      apply WP.spec_bind (Pₘ := fun (x : Std.U32) => x.val ≤ text.val + 4097)
      · split
        · step*
        · simp only [Std.WP.spec_ok]; omega
      intro text1 ht1
      apply WP.spec_bind (Pₘ := fun (x : Std.U32) => x.val ≤ high.val + 4097)
      · split
        · step*
        · simp only [Std.WP.spec_ok]; omega
      intro high1 hh1
      apply WP.spec_bind (Pₘ := fun (x : Std.U32) => x.val ≤ words.val + 4097)
      · repeat' (split <;> step*)
        all_goals (simp only [Std.WP.spec_ok]; omega)
      intro words1 hw1
      step*
      refine ⟨?_, ?_, ?_, ?_, ?_⟩ <;> (subst_vars; scalar_tac (simpAllMaxSteps := 0))
    · step*
  · exact ⟨htext, hhigh, hwords, hb⟩

attribute [local step] a_sniff_loop1_spec

attribute [local step] a_cnt_index_spec in

theorem a_sniff_loop2_spec (cnt : Array Std.U32 256#usize) (mx : Std.U32) (sq : Std.U64)
    (b2 : Std.Usize) (hc : ACntBound cnt 4097) (hb : b2.val ≤ 256) :
    slot.a_sniff_loop2 cnt mx sq b2 ⦃ fun _ => True ⦄ := by
  rw [slot.a_sniff_loop2]
  apply Std.loop.spec_decr_nat
    (measure := fun r => 256 - r.2.2.val)
    (inv := fun r => r.2.2.val ≤ 256)
  · rintro ⟨mx, sq, b2⟩ hb
    simp only at hb
    simp only [slot.a_sniff_loop2.body]
    step*
    repeat' (split <;> step*)
  · exact hb

attribute [local step] a_sniff_loop2_spec

attribute [local step] a_cnt_index_spec in

theorem a_sniff_loop3_spec (cnt : Array Std.U32 256#usize) (mx : Std.U32) (sq : Std.U64)
    (b2 : Std.Usize) (hc : ACntBound cnt 4097) (hb : b2.val ≤ 256) :
    slot.a_sniff_loop3 cnt mx sq b2 ⦃ fun _ => True ⦄ := by
  rw [slot.a_sniff_loop3]
  apply Std.loop.spec_decr_nat
    (measure := fun r => 256 - r.2.2.val)
    (inv := fun r => r.2.2.val ≤ 256)
  · rintro ⟨mx, sq, b2⟩ hb
    simp only at hb
    simp only [slot.a_sniff_loop3.body]
    step*
    repeat' (split <;> step*)
  · exact hb

attribute [local step] a_sniff_loop3_spec

attribute [local step] a_cnt_index_spec in

theorem a_sniff_loop4_spec (cnt : Array Std.U32 256#usize) (mx : Std.U32) (sq : Std.U64)
    (b2 : Std.Usize) (hc : ACntBound cnt 4097) (hb : b2.val ≤ 256) :
    slot.a_sniff_loop4 cnt mx sq b2 ⦃ fun _ => True ⦄ := by
  rw [slot.a_sniff_loop4]
  apply Std.loop.spec_decr_nat
    (measure := fun r => 256 - r.2.2.val)
    (inv := fun r => r.2.2.val ≤ 256)
  · rintro ⟨mx, sq, b2⟩ hb
    simp only at hb
    simp only [slot.a_sniff_loop4.body]
    step*
    repeat' (split <;> step*)
  · exact hb

attribute [local step] a_sniff_loop4_spec

attribute [local step] a_cnt_index_spec in

theorem a_sniff_loop5_spec (cnt : Array Std.U32 256#usize) (mx : Std.U32) (sq : Std.U64)
    (b2 : Std.Usize) (hc : ACntBound cnt 4097) (hb : b2.val ≤ 256) :
    slot.a_sniff_loop5 cnt mx sq b2 ⦃ fun _ => True ⦄ := by
  rw [slot.a_sniff_loop5]
  apply Std.loop.spec_decr_nat
    (measure := fun r => 256 - r.2.2.val)
    (inv := fun r => r.2.2.val ≤ 256)
  · rintro ⟨mx, sq, b2⟩ hb
    simp only at hb
    simp only [slot.a_sniff_loop5.body]
    step*
    repeat' (split <;> step*)
  · exact hb

attribute [local step] a_sniff_loop5_spec

@[local step]
theorem a_sniff_spec (s : Slice Std.U8) : slot.a_sniff s ⦃ fun _ => True ⦄ := by

  have hcnt := @a_cnt_index_spec
  rw [slot.a_sniff]
  step*
  apply Std.WP.spec_bind (a_sniff_loop0_spec s (Std.Slice.len s) _ step 0#usize 0#u32 (by simp)
    (by simpa using ACntBound.init) (by simp))
  rintro ⟨cnt1, tot⟩ ⟨hc, ht⟩
  simp only at hc ht
  have hc4 := ACntBound.mono hc ht
  clear hc
  step*
  repeat' (split <;> step*)

set_option maxHeartbeats 16000000 in
attribute [local step] a_hcast_I32_spec a_sat_add_spec in
theorem a_run_spec (H W : Std.Usize) (input : Slice Std.U8) (out : Slice Std.U32) (cls lvl : Std.Usize)
    (hlen : input.length ≤ out.length) (hH : 0 < H.val) (hW : 0 < W.val) :
    slot.a_run H W input out cls lvl ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧
      LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
  rw [slot.a_run]
  have hB : (UScalar.hcast .I32 slot.A_B_HLIT).val = slot.A_B_HLIT.val :=
    a_hcast_I32_val _ (by (subst_vars; scalar_tac (simpAllMaxSteps := 0)))

  apply WP.spec_bind (a_ite_spec _ _ _ (fun _ => True) trivial trivial); intro depth _
  apply WP.spec_bind (a_ite_spec _ _ _ (fun _ => True) trivial trivial); intro l2d _
  apply WP.spec_bind (a_ite_spec _ _ _ (fun _ => True) trivial trivial); intro «partial» _
  apply WP.spec_bind (a_ite_spec _ _ _ (fun _ => True) trivial trivial); intro insm _
  apply WP.spec_bind (a_ite_spec _ _ _ (fun _ => True) trivial trivial); intro stride _
  step
  apply WP.spec_bind (a_ite_spec _ _ _ (fun _ => True) trivial trivial)
  rintro ⟨depth1, lazy, nice, ldep, insm1, stride1⟩ -
  apply WP.spec_bind (a_ite_spec _ _ _
    (fun (x : Std.Usize × Std.Usize × Std.Usize × Std.Usize × Std.Usize × Std.Usize × Std.Usize) =>
      x.2.2.1.val < 32) (by (subst_vars; scalar_tac (simpAllMaxSteps := 0))) (by (subst_vars; scalar_tac (simpAllMaxSteps := 0))))
  rintro ⟨depth2, lazy1, skip, nice1, ldep1, insm2, stride2⟩ hskip
  simp only at hskip
  apply WP.spec_bind (Pₘ := fun (x : Std.Usize × Std.Usize × Std.Usize × Std.Usize × Std.Usize ×
      Std.Usize × Std.Usize × Std.Usize) => x.2.2.1.val < 32)
  · repeat' (split <;> step*)
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  rintro ⟨depth3, lazy2, skip1, skcap, nice2, ldep2, insm3, stride3⟩ hskip1
  simp only at hskip1
  apply WP.spec_bind (Pₘ := fun (h : Std.I32) => 0 ≤ h.val ∧ h.val ≤ 1000000)
  · repeat' split
    all_goals (simp only [Std.WP.spec_ok]; (subst_vars; scalar_tac (simpAllMaxSteps := 0)))
  intro hlit1 hhl
  apply WP.spec_bind (a_ite_spec _ _ _
    (fun (x : Std.U32 × Std.Usize × Std.Usize × Std.Usize × Std.Usize × Std.Usize × Std.Usize ×
      Std.Usize × Std.Usize) => 3 ≤ x.2.1.val ∧ x.2.1.val ≤ 8 ∧ x.2.2.2.2.1.val < 32)
    (by (subst_vars; scalar_tac (simpAllMaxSteps := 0))) (by simp only; (subst_vars; scalar_tac (simpAllMaxSteps := 0))))
  rintro ⟨mask, minl, depth4, lazy3, skip2, nice3, ldep3, insm4, stride4⟩ hms
  simp only at hms
  apply WP.spec_bind (a_ite_spec _ _ _
    (fun (x : Std.U32 × Std.Usize × Std.Usize × Std.Usize × Std.Usize × Std.Usize × Std.Usize ×
      Std.Usize × Std.Usize) => 3 ≤ x.2.1.val ∧ x.2.1.val ≤ 8 ∧ x.2.2.2.2.1.val < 32)
    (by (subst_vars; scalar_tac (simpAllMaxSteps := 0))) (by simp only; (subst_vars; scalar_tac (simpAllMaxSteps := 0))))
  rintro ⟨mask1, minl1, depth5, lazy4, skip3, nice4, ldep4, insm5, stride5⟩ hms1
  simp only at hms1
  step*
  all_goals first
    | exact ADec.init input out hlen
    | exact AHeadBound.init _

attribute [local step] a_run_spec

attribute [local step] a_hcast_I32_spec a_sat_add_spec in
theorem a_run_dna_spec (H W : Std.Usize) (input : Slice Std.U8) (out : Slice Std.U32)
    (cls : Std.Usize) (hlen : input.length ≤ out.length) (hH : 0 < H.val) (hW : 0 < W.val) :
    slot.a_run_dna H W input out cls ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧
      LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
  rw [slot.a_run_dna]
  step*
  repeat' (split <;> step*)
  all_goals first
    | exact ADec.init input out hlen
    | exact AHeadBound.init _

attribute [local step] a_run_dna_spec

theorem a_run_rest_spec (input : Slice Std.U8) (out : Slice Std.U32) (cls lvl : Std.Usize)
    (hlen : input.length ≤ out.length) :
    slot.a_run_rest input out cls lvl ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧
      LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
  rw [slot.a_run_rest]
  split
  · split
    · exact a_run_spec _ _ input out _ _ hlen (by simp) (by simp)
    · exact a_run_spec _ _ input out _ _ hlen (by simp) (by simp)
  · exact a_run_spec _ _ input out _ _ hlen (by simp) (by simp)

@[local step]
theorem a_parse_cls_spec (input : Slice Std.U8) (out : Slice Std.U32) (cls lvl : Std.Usize)
    (hlen : input.length ≤ out.length) :
    slot.a_parse_cls input out cls lvl ⦃ fun r =>
      r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
  rw [slot.a_parse_cls]
  repeat' ((try dsimp only); split)
  all_goals first
    | exact a_run_spec _ _ input out _ _ hlen (by simp) (by simp)
    | exact a_run_rest_spec input out _ _ hlen
    | exact a_run_dna_spec _ _ input out _ hlen (by simp) (by simp)

theorem dl_DLHN_pos : 0 < slot.DLHN.val := by simp [slot.DLHN]

@[local step] theorem dl_key_spec (s : Slice Std.U8) (p : Std.Usize) (h : p.val + 8 ≤ Std.Usize.max) :
    slot.dl_key s p ⦃ fun r => r.val < slot.DLHN.val ⦄ := by
  have := dl_DLHN_pos
  rw [slot.dl_key]
  step*

@[local step]
theorem dl_litsum_loop_spec (s : Slice Std.U8) (litc) (p l : Std.Usize) (acc : Std.U32) (q : Std.Usize)
    (hpl : p.val + l.val ≤ Std.Usize.max) :
    slot.dl_litsum_loop s litc p l acc q ⦃ fun _ => True ⦄ := by
  rw [slot.dl_litsum_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, q') => l.val - q'.val)
    (inv := fun _ => True)
  · rintro ⟨acc', q'⟩ _
    simp only [slot.dl_litsum_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · trivial

@[local step] theorem dl_litsum_spec (s : Slice Std.U8) (litc) (p l : Std.Usize)
    (hpl : p.val + l.val ≤ Std.Usize.max) :
    slot.dl_litsum s litc p l ⦃ fun _ => True ⦄ := by
  rw [slot.dl_litsum]
  step*

@[local step] theorem dl_mcost_spec (lsym dtab) (l d : Std.Usize) :
    slot.dl_mcost lsym dtab l d ⦃ fun _ => True ⦄ := by
  rw [slot.dl_mcost]
  step*

@[local step]
theorem dl_best_loop_spec (s : Slice Std.U8) (litc prev) (p : Std.Usize) (lsym dtab) (cap : Std.Usize)
    (bg : Std.U32) (bl bd c k : Std.Usize)
    (hpc : p.val + cap.val ≤ s.length) (hN : s.length + 8 ≤ Std.Usize.max) :
    slot.dl_best_loop s litc prev p lsym dtab cap bg bl bd c k ⦃ fun _ => True ⦄ := by
  have hwn := dp_WN_val
  rw [slot.dl_best_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, k') => k'.val)
    (inv := fun _ => True)
  · rintro ⟨bg', bl', bd', c', k'⟩ _
    simp only [slot.dl_best_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · trivial

@[local step] theorem dl_best_spec (s : Slice Std.U8) (litc prev) (start p : Std.Usize) (lsym dtab)
    (hp : p.val < s.length) (hN : s.length + 8 ≤ Std.Usize.max) :
    slot.dl_best s litc prev start p lsym dtab ⦃ fun _ => True ⦄ := by
  rw [slot.dl_best]
  step*
  repeat' (split <;> step*)
  all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))

@[local step]
theorem dl_flush_loop_spec (plan lim r) : slot.dl_flush_loop plan lim r ⦃ fun _ => True ⦄ := by
  rw [slot.dl_flush_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, r') => r'.val)
    (inv := fun _ => True)
  · rintro ⟨plan', r'⟩ _
    simp only [slot.dl_flush_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · trivial

@[local step] theorem dl_flush_spec (plan run lim) : slot.dl_flush plan run lim ⦃ fun _ => True ⦄ := by
  rw [slot.dl_flush]
  step*

@[local step]
theorem dl_insert_range_loop_spec (s : Slice Std.U8) (cheap head prev) (e q : Std.Usize)
    (hN : s.length + 8 ≤ Std.Usize.max) :
    slot.dl_insert_range_loop s cheap head prev e q ⦃ fun _ => True ⦄ := by
  have hwn := dp_WN_val
  have := dl_DLHN_pos
  rw [slot.dl_insert_range_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, q') => s.length - q'.val)
    (inv := fun _ => True)
  · rintro ⟨head', prev', q'⟩ _
    simp only [slot.dl_insert_range_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · trivial

@[local step] theorem dl_insert_range_spec (s : Slice Std.U8) (cheap head prev) (f e : Std.Usize)
    (hN : s.length + 8 ≤ Std.Usize.max) :
    slot.dl_insert_range s cheap head prev f e ⦃ fun _ => True ⦄ := by
  rw [slot.dl_insert_range]
  exact dl_insert_range_loop_spec s cheap head prev e f hN

attribute [local step] a_cnt_index_spec in

theorem dl_costs_loop0_spec (s : Slice Std.U8) (n : Std.Usize) (cnt : Array Std.U32 256#usize)
    (step i : Std.Usize) (tot : Std.U32) (hn : n.val = s.length) (hc : ACntBound cnt tot.val)
    (ht : tot.val ≤ 65600) :
    slot.dl_costs_loop0 s n cnt step i tot ⦃ fun r => r.2.val ≤ 65600 ⦄ := by
  rw [slot.dl_costs_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun r => 65600 - r.2.2.val)
    (inv := fun r => ACntBound r.1 r.2.2.val ∧ r.2.2.val ≤ 65600)
  · rintro ⟨cnt, i, tot⟩ ⟨hc, ht⟩
    simp only at hc ht
    simp only [slot.dl_costs_loop0.body]
    step*
    all_goals first
      | exact ht
      | exact ⟨ACntBound.step hc (by assumption) (by (subst_vars; scalar_tac (simpAllMaxSteps := 0))) (by (subst_vars; scalar_tac (simpAllMaxSteps := 0))), by (subst_vars; scalar_tac (simpAllMaxSteps := 0)),
          by (subst_vars; scalar_tac (simpAllMaxSteps := 0))⟩
  · exact ⟨hc, ht⟩

@[local step]
theorem dl_costs_loop1_spec (litc cheap cnt lt b) : slot.dl_costs_loop1 litc cheap cnt lt b ⦃ fun _ => True ⦄ := by
  rw [slot.dl_costs_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, b') => 256 - b'.val)
    (inv := fun _ => True)
  · rintro ⟨litc', cheap', b'⟩ _
    simp only [slot.dl_costs_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · trivial

@[local step] theorem dl_costs_spec (s : Slice Std.U8) (litc cheap) :
    slot.dl_costs s litc cheap ⦃ fun _ => True ⦄ := by
  rw [slot.dl_costs]
  step*
  apply Std.WP.spec_bind (dl_costs_loop0_spec s (Std.Slice.len s) _ step 0#usize 0#u32 (by simp)
    (by simpa using ACntBound.init) (by simp))
  rintro ⟨cnt1, tot⟩ ht
  simp only at ht
  step*

theorem dna_plan_loop_spec (input : Slice Std.U8) (n : Std.Usize) (plan lsym dtab litc cheap head prev)
    (lim p run : Std.Usize)
    (hn : n.val = input.length) (hlim : lim.val + 16 = n.val) (hN : input.length + 8 ≤ Std.Usize.max)
    (hrun : run.val ≤ p.val) :
    slot.dna_plan_loop input n plan lsym dtab litc cheap head prev lim p run
      ⦃ fun r => r.2.2.val ≤ r.2.1.val ⦄ := by
  have hwn := dp_WN_val
  have hh := dl_DLHN_pos
  rw [slot.dna_plan_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, p', _) => lim.val - p'.val)
    (inv := fun (_, _, _, p', run') => run'.val ≤ p'.val)
  · rintro ⟨plan', head', prev', p', run'⟩ hr
    simp only at hr
    simp only [slot.dna_plan_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · exact hrun

attribute [local step] dna_plan_loop_spec

@[local step] theorem dna_plan_spec (input : Slice Std.U8) : slot.dna_plan input ⦃ fun _ => True ⦄ := by
  have z8 : LeAll (Array.repeat 512#usize 0#u8).val 28 := dp_LeAll_repeat _ _ _ (by simp)
  rw [slot.dna_plan]
  step*

  all_goals
    have hw := dp_wadd_self input.len (by rw [← i2_post]; (subst_vars; scalar_tac (simpAllMaxSteps := 0)))
  repeat' (split <;> step*)
  all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))

@[local step]
theorem lazy_parse_spec (input : Slice Std.U8) (out : Slice Std.U32) (lvl : Std.Usize)
    (hlen : input.length ≤ out.length) :
    slot.lazy_parse input out lvl ⦃ fun r =>
      r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
  rw [slot.lazy_parse]
  step*

open LZ77 (Matches)

def sp_word8 (input : Slice Std.U8) (p : Nat) : Nat :=
  ((((((((input.val[p]!).val * 256 + (input.val[p + 1]!).val) * 256
    + (input.val[p + 2]!).val) * 256 + (input.val[p + 3]!).val) * 256
    + (input.val[p + 4]!).val) * 256 + (input.val[p + 5]!).val) * 256
    + (input.val[p + 6]!).val) * 256 + (input.val[p + 7]!).val)

theorem sp_u8_lt (x : Std.U8) : x.val < 256 := by (subst_vars; scalar_tac (simpAllMaxSteps := 0))

theorem sp_word8_digit (input : Slice Std.U8) (p k : Nat) (hk : k < 8) :
    (input.val[p + k]!).val = sp_word8 input p / 256 ^ (7 - k) % 256 := by
  have := sp_u8_lt (input.val[p]!); have := sp_u8_lt (input.val[p+1]!)
  have := sp_u8_lt (input.val[p+2]!); have := sp_u8_lt (input.val[p+3]!)
  have := sp_u8_lt (input.val[p+4]!); have := sp_u8_lt (input.val[p+5]!)
  have := sp_u8_lt (input.val[p+6]!); have := sp_u8_lt (input.val[p+7]!)
  simp only [sp_word8]
  rcases (show k = 0 ∨ k = 1 ∨ k = 2 ∨ k = 3 ∨ k = 4 ∨ k = 5 ∨ k = 6 ∨ k = 7 by omega) with
    rfl | rfl | rfl | rfl | rfl | rfl | rfl | rfl <;> simp only [Nat.add_zero, Nat.pow_zero,
    Nat.pow_succ, Nat.one_mul, Nat.sub_self, Nat.reduceSub] <;> omega

theorem sp_word8_prefix (input : Slice Std.U8) (a b d : Nat) (hd : d ≤ 8)
    (h : sp_word8 input a / 2 ^ (64 - 8 * d) = sp_word8 input b / 2 ^ (64 - 8 * d)) :
    ∀ k, k < d → input.val[b + k]! = input.val[a + k]! := by
  intro k hk
  have e : (256 : Nat) ^ (7 - k) = 2 ^ (64 - 8 * d) * 2 ^ (8 * (d - 1 - k)) := by
    rw [← pow_add, show (256 : Nat) = 2 ^ 8 by norm_num, ← pow_mul]
    congr 1; omega
  have key : sp_word8 input a / 256 ^ (7 - k) = sp_word8 input b / 256 ^ (7 - k) := by
    rw [e, ← Nat.div_div_eq_div_mul, ← Nat.div_div_eq_div_mul, h]
  have ha := sp_word8_digit input a k (by omega)
  have hb := sp_word8_digit input b k (by omega)
  rw [key] at ha
  (subst_vars; scalar_tac (simpAllMaxSteps := 0))

theorem Matches.sp_add_prefix {input : Slice Std.U8} {a b l d : Nat} (h : Matches input a b l)
    (hd : d ≤ 8)
    (hw : sp_word8 input (a + l) / 2 ^ (64 - 8 * d) = sp_word8 input (b + l) / 2 ^ (64 - 8 * d)) :
    Matches input a b (l + d) := by
  intro k hk
  by_cases hkl : k < l
  · exact h k hkl
  · have := sp_word8_prefix input (a + l) (b + l) d hd hw (k - l) (by omega)
    rw [show b + l + (k - l) = b + k by omega, show a + l + (k - l) = a + k by omega] at this
    exact this

theorem Matches.sp_word {input : Slice Std.U8} {a b l l' : Nat} {pa pb d : Std.Usize}
    {x y : Std.U64} (h : Matches input a b l) (hpa : pa.val = a + l) (hpb : pb.val = b + l)
    (hx : x.val = sp_word8 input pa.val) (hy : y.val = sp_word8 input pb.val)
    (hd8 : d.val ≤ 8) (hdiv : x.val / 2 ^ (64 - 8 * d.val) = y.val / 2 ^ (64 - 8 * d.val))
    (hl' : l' = l + d.val) : Matches input a b l' := by
  subst hl'
  rw [hx, hy, hpa, hpb] at hdiv
  exact Matches.sp_add_prefix h hd8 hdiv

theorem Matches.sp_word_eq {input : Slice Std.U8} {a b l l' : Nat} {pa pb : Std.Usize}
    {x y : Std.U64} (h : Matches input a b l) (hpa : pa.val = a + l) (hpb : pb.val = b + l)
    (hx : x.val = sp_word8 input pa.val) (hy : y.val = sp_word8 input pb.val)
    (hxy : ¬(x != y) = true) (hl' : l' = l + 8) : Matches input a b l' := by
  have hxy' : x.val = y.val := by simpa using hxy
  subst hl'
  apply Matches.sp_add_prefix h (le_refl 8)
  rw [← hpa, ← hpb, ← hx, ← hy, hxy']

theorem Matches.sp_byte {input : Slice Std.U8} {a b l l' : Nat} {pa pb : Std.Usize}
    {x y : Std.U8} (h : Matches input a b l) (hpa : pa.val = a + l) (hpb : pb.val = b + l)
    (hpa' : pa.val < input.val.length) (hpb' : pb.val < input.val.length)
    (hx : x = input.val[pa.val]) (hy : y = input.val[pb.val]) (hxy : x = y)
    (hl' : l' = l + 1) : Matches input a b l' := by
  subst hl' hxy
  apply LZ77.Matches.succ h
  rw [← hpa, ← hpb, getElem!_pos input.val pa.val hpa', getElem!_pos input.val pb.val hpb',
    ← hx, ← hy]

theorem sp_nat_xor_eq_zero {a b : Nat} (h : a ^^^ b = 0) : a = b := by
  have : a ^^^ (a ^^^ b) = b := by rw [← Nat.xor_assoc, Nat.xor_self, Nat.zero_xor]
  rw [h, Nat.xor_zero] at this; exact this

theorem sp_div_eq_of_xor_lt {x y m : Nat} (hz : x ^^^ y < 2 ^ m) : x / 2 ^ m = y / 2 ^ m := by
  have h : (x ^^^ y) >>> m = 0 := by rw [Nat.shiftRight_eq_div_pow]; exact Nat.div_eq_of_lt hz
  rw [Nat.shiftRight_xor_distrib] at h
  have := sp_nat_xor_eq_zero h
  simpa [Nat.shiftRight_eq_div_pow] using this

theorem sp_lt_pow_leadingZeros (z : BitVec 64) :
    z.toNat < 2 ^ (64 - 8 * (BitVec.leadingZeros z / 8)) := by
  unfold BitVec.leadingZeros
  split
  case isTrue h => subst h; simp
  case isFalse h =>
    have hz : z.toNat ≠ 0 := by
      intro h0; apply h; exact BitVec.eq_of_toNat_eq (by simpa using h0)
    have hlog : Nat.log 2 z.toNat < 64 := Nat.log_lt_of_lt_pow hz z.isLt
    have h1 : z.toNat < 2 ^ (Nat.log 2 z.toNat).succ := Nat.lt_pow_succ_log_self (by norm_num) _
    refine lt_of_lt_of_le h1 (Nat.pow_le_pow_right (by norm_num) ?_)
    omega

@[local step]
theorem load8_spec (input : Slice Std.U8) (p : Std.Usize) (hp : p.val + 8 ≤ input.length) :
    slot.load8 input p ⦃ fun v => v.val = sp_word8 input p.val ⦄ := by
  have hlift := @lift_spec
  rw [slot.load8]
  step*
  simp only [← getElem!_pos] at *
  simp only [sp_word8]
  simp_all only [U8.cast_U64_val_eq]

@[local step]
theorem first_diff_spec (x y : Std.U64) :
    slot.first_diff x y ⦃ fun d => d.val ≤ 8 ∧
      x.val / 2 ^ (64 - 8 * d.val) = y.val / 2 ^ (64 - 8 * d.val) ⦄ := by
  have hlift := @lift_spec
  rw [slot.first_diff]
  step*
  have hle : BitVec.leadingZeros z.bv ≤ 64 := by unfold BitVec.leadingZeros; split <;> omega
  have hlz : lz.val = BitVec.leadingZeros z.bv := by
    rw [lz_post]
    simp only [core.num.U64.leading_zeros, UScalar.val, UScalarTy.U32_numBits_eq,
      BitVec.natCast_eq_ofNat, BitVec.toNat_ofNat, Nat.reducePow]
    omega
  have hd : (UScalar.cast UScalarTy.Usize bytes).val = BitVec.leadingZeros z.bv / 8 := by
    simp only [U32.cast_Usize_val_eq, bytes_post, hlz]
  have hz : z.bv.toNat = x.val ^^^ y.val := by
    have : z.val = z.bv.toNat := rfl
    rw [← this, z_post, UScalar.val_xor]
  refine ⟨by rw [hd]; omega, ?_⟩
  rw [hd]
  apply sp_div_eq_of_xor_lt
  rw [← hz]
  exact sp_lt_pow_leadingZeros z.bv

@[local step]
theorem mlen_loop0_loop0_spec (input : Slice Std.U8) (a b cap l0 : Std.Usize)
    (ha : a.val + cap.val ≤ input.length) (hb : b.val + cap.val ≤ input.length)
    (hl0 : l0.val ≤ cap.val) (h0 : Matches input a.val b.val l0.val) :
    slot.mlen_loop0_loop0 input a b cap l0 ⦃ fun l => l.val ≤ cap.val ∧ Matches input a.val b.val l.val ⦄ := by
  rw [slot.mlen_loop0_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun l => cap.val - l.val)
    (inv := fun l => l.val ≤ cap.val ∧ Matches input a.val b.val l.val)
  · rintro l ⟨hle, hm⟩
    simp only [slot.mlen_loop0_loop0.body]
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    step*
    refine ⟨by (subst_vars; scalar_tac (simpAllMaxSteps := 0)), ?_, by (subst_vars; scalar_tac (simpAllMaxSteps := 0))⟩
    exact Matches.sp_byte hm (by assumption) (by assumption) (by (subst_vars; scalar_tac (simpAllMaxSteps := 0))) (by (subst_vars; scalar_tac (simpAllMaxSteps := 0)))
      (by assumption) (by assumption) (by assumption) (by (subst_vars; scalar_tac (simpAllMaxSteps := 0)))
  · exact ⟨hl0, h0⟩

@[local step]
theorem mlen_loop0_spec (input : Slice Std.U8) (a b cap l0 : Std.Usize)
    (ha : a.val + cap.val ≤ input.length) (hb : b.val + cap.val ≤ input.length)
    (hl0 : l0.val ≤ cap.val) (h0 : Matches input a.val b.val l0.val) :
    slot.mlen_loop0 input a b cap l0 ⦃ fun l => l.val ≤ cap.val ∧ Matches input a.val b.val l.val ⦄ := by
  rw [slot.mlen_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun l => cap.val - l.val)
    (inv := fun l => l.val ≤ cap.val ∧ Matches input a.val b.val l.val)
  · rintro l ⟨hle, hm⟩
    simp only [slot.mlen_loop0.body]
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input

    step*
    ·
      refine ⟨by (subst_vars; scalar_tac (simpAllMaxSteps := 0)), ?_⟩
      exact Matches.sp_word hm (by assumption) (by assumption) (by assumption) (by assumption)
        (by assumption) (by assumption) (by (subst_vars; scalar_tac (simpAllMaxSteps := 0)))
    ·
      refine ⟨by (subst_vars; scalar_tac (simpAllMaxSteps := 0)), ?_, by (subst_vars; scalar_tac (simpAllMaxSteps := 0))⟩
      exact Matches.sp_word_eq hm (by assumption) (by assumption) (by assumption) (by assumption)
        (by assumption) (by (subst_vars; scalar_tac (simpAllMaxSteps := 0)))
  · exact ⟨hl0, h0⟩

@[local step]
theorem mlen_spec (input : Slice Std.U8) (a b cap : Std.Usize)
    (ha : a.val + cap.val ≤ input.length) (hb : b.val + cap.val ≤ input.length) :
    slot.mlen input a b cap ⦃ fun l => l.val ≤ cap.val ∧ Matches input a.val b.val l.val ⦄ :=
  mlen_loop0_spec input a b cap 0#usize ha hb (by simp) (LZ77.Matches.zero input a.val b.val)

@[local step]
theorem check_spec (input : Slice Std.U8) (p len dist : Std.Usize) :
    slot.check input p len dist ⦃ fun valid => valid = true →
      3 ≤ len.val ∧ len.val ≤ 258 ∧ 1 ≤ dist.val ∧ dist.val ≤ 32768 ∧ dist.val ≤ p.val ∧
      p.val + len.val ≤ input.length ∧ Matches input (p.val - dist.val) p.val len.val ⦄ := by
  rw [slot.check]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  step*
  intro hvalid
  have hl : l = len := by simpa using hvalid
  subst hl
  refine ⟨by (subst_vars; scalar_tac (simpAllMaxSteps := 0)), by (subst_vars; scalar_tac (simpAllMaxSteps := 0)), by (subst_vars; scalar_tac (simpAllMaxSteps := 0)), by (subst_vars; scalar_tac (simpAllMaxSteps := 0)), by (subst_vars; scalar_tac (simpAllMaxSteps := 0)),
    by (subst_vars; scalar_tac (simpAllMaxSteps := 0)), ?_⟩
  rw [← src_post1]
  exact l_post2

@[local step]
theorem emit_loop_spec (input : Slice Std.U8) (plan out0 : Slice Std.U32)
    (n ntok0 k0 owed0 p0 : Std.Usize) (hn : n.val = input.length) (hout : input.length ≤ out0.length)
    (hp0 : p0.val ≤ n.val) (hntok0 : ntok0.val ≤ p0.val) (hk0 : k0.val ≤ p0.val)
    (hdec0 : LZ77.decode (toks out0 ntok0.val) = some ((bytes input).take p0.val)) :
    slot.emit_loop input plan out0 n ntok0 k0 owed0 p0 ⦃ fun r =>
      r.1.val ≤ input.length ∧ r.2.length = out0.length ∧
      LZ77.decode (toks r.2 r.1.val) = some (bytes input) ⦄ := by
  have hlift := @lift_spec
  rw [slot.emit_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, p) => n.val - p.val)
    (inv := fun (out, ntok, k, _, p) => p.val ≤ n.val ∧ ntok.val ≤ p.val ∧ k.val ≤ p.val ∧
      out.length = out0.length ∧
      LZ77.decode (toks out ntok.val) = some ((bytes input).take p.val))
  · rintro ⟨out, ntok, k, owed, p⟩ ⟨hp, hnt, hk, hlen, hde⟩
    simp only [slot.emit_loop.body]
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    split
    case isTrue hlt =>
      have hntok_lt : ntok.val < out.length := by (subst_vars; scalar_tac (simpAllMaxSteps := 0))
      step*
      ·
        have hlit : i1.val = (bytes input)[p.val]! := by
          rw [bytes_getElem! input p.val (by (subst_vars; scalar_tac (simpAllMaxSteps := 0)))]
          (subst_vars; scalar_tac (simpAllMaxSteps := 0))
        refine ⟨by (subst_vars; scalar_tac (simpAllMaxSteps := 0)), by (subst_vars; scalar_tac (simpAllMaxSteps := 0)), by (subst_vars; scalar_tac (simpAllMaxSteps := 0)), by rw [s_post]; simpa using hlen, ?_,
          by (subst_vars; scalar_tac (simpAllMaxSteps := 0))⟩
        rw [s_post, show ntok1.val = ntok.val + 1 by (subst_vars; scalar_tac (simpAllMaxSteps := 0)),
          show p1.val = p.val + 1 by (subst_vars; scalar_tac (simpAllMaxSteps := 0))]
        exact emit_lit input out ntok p.val i1 hde (by (subst_vars; scalar_tac (simpAllMaxSteps := 0))) hntok_lt hlit
      ·
        obtain ⟨h3, h258, hd1, hd32k, hdp, hend, hm⟩ := valid_post (by assumption)
        have htok : tok.val = LZ77.mkMatch dist.val len.val := by
          simp only [LZ77.mkMatch, LZ77.MATCH_BASE]
          (subst_vars; scalar_tac (simpAllMaxSteps := 0))
        refine ⟨by (subst_vars; scalar_tac (simpAllMaxSteps := 0)), by (subst_vars; scalar_tac (simpAllMaxSteps := 0)), by (subst_vars; scalar_tac (simpAllMaxSteps := 0)), by rw [s_post]; simpa using hlen, ?_,
          by (subst_vars; scalar_tac (simpAllMaxSteps := 0))⟩
        rw [s_post, show ntok1.val = ntok.val + 1 by (subst_vars; scalar_tac (simpAllMaxSteps := 0)),
          show p1.val = p.val + len.val by (subst_vars; scalar_tac (simpAllMaxSteps := 0))]
        exact emit_match input out ntok p.val dist.val len.val tok hde hntok_lt hd1 hdp hd32k
          h3 h258 hend hm htok
      all_goals

        have hlit : i3.val = (bytes input)[p.val]! := by
          rw [bytes_getElem! input p.val (by (subst_vars; scalar_tac (simpAllMaxSteps := 0)))]
          (subst_vars; scalar_tac (simpAllMaxSteps := 0))
        subst index_mut_back
        refine ⟨by (subst_vars; scalar_tac (simpAllMaxSteps := 0)), by (subst_vars; scalar_tac (simpAllMaxSteps := 0)), by (subst_vars; scalar_tac (simpAllMaxSteps := 0)), by simpa using hlen, ?_, by (subst_vars; scalar_tac (simpAllMaxSteps := 0))⟩
        rw [show ntok1.val = ntok.val + 1 by (subst_vars; scalar_tac (simpAllMaxSteps := 0)), show p1.val = p.val + 1 by (subst_vars; scalar_tac (simpAllMaxSteps := 0))]
        exact emit_lit input out ntok p.val i3 hde (by (subst_vars; scalar_tac (simpAllMaxSteps := 0))) hntok_lt hlit
    case isFalse hge =>
      have hpn : p.val = input.length := by (subst_vars; scalar_tac (simpAllMaxSteps := 0))
      refine ⟨by (subst_vars; scalar_tac (simpAllMaxSteps := 0)), hlen, ?_⟩
      rw [hde, hpn]
      simp
  · exact ⟨hp0, hntok0, hk0, rfl, hdec0⟩

@[local step]
theorem emit_spec (input : Slice Std.U8) (plan out : Slice Std.U32)
    (hout : input.length ≤ out.length) :
    slot.emit input plan out ⦃ fun r =>
      r.1.val ≤ input.length ∧ r.2.length = out.length ∧
      LZ77.decode (toks r.2 r.1.val) = some (bytes input) ⦄ := by
  rw [slot.emit]
  exact emit_loop_spec input plan out (Std.Slice.len input) 0#usize 0#usize 0#usize 0#usize
    (by simp) hout (by simp) (by simp) (by simp) (by simp [toks, LZ77.decode])

theorem emit_pos_loop_spec (input : Slice Std.U8) (plan out0 : Slice Std.U32)
    (n ntok0 p0 : Std.Usize) (hn : n.val = input.length) (hout : input.length ≤ out0.length)
    (hp0 : p0.val ≤ n.val) (hntok0 : ntok0.val ≤ p0.val)
    (hdec0 : LZ77.decode (toks out0 ntok0.val) = some ((bytes input).take p0.val)) :
    slot.emit_pos_loop input plan out0 n ntok0 p0 ⦃ fun r =>
      r.1.val ≤ input.length ∧ r.2.length = out0.length ∧
      LZ77.decode (toks r.2 r.1.val) = some (bytes input) ⦄ := by
  rw [slot.emit_pos_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, p) => n.val - p.val)
    (inv := fun (out, ntok, p) => p.val ≤ n.val ∧ ntok.val ≤ p.val ∧ out.length = out0.length ∧
      LZ77.decode (toks out ntok.val) = some ((bytes input).take p.val))
  · rintro ⟨out, ntok, p⟩ ⟨hp, hnt, hlen, hde⟩
    simp only [slot.emit_pos_loop.body]
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    split
    case isTrue hlt =>
      have hntok_lt : ntok.val < out.length := by (subst_vars; scalar_tac (simpAllMaxSteps := 0))
      step*
      ·
        obtain ⟨h3, h258, hd1, hd32k, hdp, hend, hm⟩ := valid_post (by assumption)
        have htok : tok.val = LZ77.mkMatch dist.val len.val := by
          simp only [LZ77.mkMatch, LZ77.MATCH_BASE]
          (subst_vars; scalar_tac (simpAllMaxSteps := 0))
        refine ⟨by (subst_vars; scalar_tac (simpAllMaxSteps := 0)), by (subst_vars; scalar_tac (simpAllMaxSteps := 0)), by rw [s_post]; simpa using hlen, ?_, by (subst_vars; scalar_tac (simpAllMaxSteps := 0))⟩
        rw [s_post, show ntok1.val = ntok.val + 1 by (subst_vars; scalar_tac (simpAllMaxSteps := 0)),
          show p1.val = p.val + len.val by (subst_vars; scalar_tac (simpAllMaxSteps := 0))]
        exact emit_match input out ntok p.val dist.val len.val tok hde hntok_lt hd1 hdp hd32k
          h3 h258 hend hm htok
      ·
        have hlit : lit.val = (bytes input)[p.val]! := by
          rw [bytes_getElem! input p.val (by (subst_vars; scalar_tac (simpAllMaxSteps := 0)))]
          (subst_vars; scalar_tac (simpAllMaxSteps := 0))
        refine ⟨by (subst_vars; scalar_tac (simpAllMaxSteps := 0)), by (subst_vars; scalar_tac (simpAllMaxSteps := 0)), by rw [s_post]; simpa using hlen, ?_, by (subst_vars; scalar_tac (simpAllMaxSteps := 0))⟩
        rw [s_post, show ntok1.val = ntok.val + 1 by (subst_vars; scalar_tac (simpAllMaxSteps := 0)),
          show p1.val = p.val + 1 by (subst_vars; scalar_tac (simpAllMaxSteps := 0))]
        exact emit_lit input out ntok p.val lit hde (by (subst_vars; scalar_tac (simpAllMaxSteps := 0))) hntok_lt hlit
    case isFalse hge =>
      have hpn : p.val = input.length := by (subst_vars; scalar_tac (simpAllMaxSteps := 0))
      refine ⟨by (subst_vars; scalar_tac (simpAllMaxSteps := 0)), hlen, ?_⟩
      rw [hde, hpn]
      simp
  · exact ⟨hp0, hntok0, rfl, hdec0⟩

@[local step]
theorem emit_pos_spec (input : Slice Std.U8) (plan out : Slice Std.U32)
    (hout : input.length ≤ out.length) :
    slot.emit_pos input plan out ⦃ fun r =>
      r.1.val ≤ input.length ∧ r.2.length = out.length ∧
      LZ77.decode (toks r.2 r.1.val) = some (bytes input) ⦄ := by
  rw [slot.emit_pos]
  exact emit_pos_loop_spec input plan out (Std.Slice.len input) 0#usize 0#usize (by simp) hout
    (by simp) (by simp) (by simp [toks, LZ77.decode])

@[local step]
theorem zeros_loop_spec (n : Std.Usize) (v0 : alloc.vec.Vec Std.U32) (i0 : Std.Usize)
    (hv : v0.length = i0.val) (hi : i0.val ≤ n.val) :
    slot.zeros_loop n v0 i0 ⦃ fun v => v.length = n.val ⦄ := by
  rw [slot.zeros_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, i) => n.val - i.val)
    (inv := fun (v, i) => v.length = i.val ∧ i.val ≤ n.val)
  · rintro ⟨v, i⟩ ⟨hvi, hin⟩
    simp only [slot.zeros_loop.body]
    step*
    have hlen : v1.length = v.length + 1 := by simp [v1_post]
    (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · exact ⟨hv, hi⟩

@[local step]
theorem zeros_spec (n : Std.Usize) : slot.zeros n ⦃ fun v => v.length = n.val ⦄ := by
  rw [slot.zeros]
  step*
  simp [alloc.vec.Vec.with_capacity]

@[local step]
theorem sample_counts_loop0_loop0_spec (s : Slice Std.U8) (f) (n e i : Std.Usize) (c : Nat)
    (hn : n.val ≤ s.length) (hc : c + (e.val - i.val) ≤ 2 ^ 31) (hf : LeAll f.val c) :
    slot.sample_counts_loop0_loop0 s f n e i ⦃ fun r => LeAll r.val (c + (e.val - i.val)) ⦄ := by
  rw [slot.sample_counts_loop0_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, i') => e.val - i'.val)
    (inv := fun (f', i') => i.val ≤ i'.val ∧ i'.val - i.val ≤ e.val - i.val ∧
      LeAll f'.val (c + (i'.val - i.val)))
  · rintro ⟨f', i'⟩ ⟨hi1, hi2, hf'⟩
    simp only [slot.sample_counts_loop0_loop0.body]
    step*
    all_goals try (exact LeAll_mono hf' (by omega))

    have h5 := LeAll_get hf' i4.val (by (subst_vars; scalar_tac (simpAllMaxSteps := 0)))
    rw [← i5_post] at h5
    have h6 : i6.val = i5.val + 1 := by
      simp only [i6_post, core.num.Usize.wrapping_add_val_eq, UScalar.size_UScalarTyUsize]
      rw [Nat.mod_eq_of_lt] <;> (subst_vars; scalar_tac (simpAllMaxSteps := 0))
    refine ⟨by (subst_vars; scalar_tac (simpAllMaxSteps := 0)), by (subst_vars; scalar_tac (simpAllMaxSteps := 0)), ?_, by (subst_vars; scalar_tac (simpAllMaxSteps := 0))⟩
    have heq : i7.val - i.val = (i'.val - i.val) + 1 := by (subst_vars; scalar_tac (simpAllMaxSteps := 0))
    rw [heq, ← Nat.add_assoc, a_post, Array.set_val_eq]
    exact LeAll_set_succ hf' _ _ (by (subst_vars; scalar_tac (simpAllMaxSteps := 0)))
  · exact ⟨le_refl _, by omega, by simpa using hf⟩

theorem spine_wrap1024 (a : Std.Usize) :
    (core.num.Usize.wrapping_add a 1024#usize).val - a.val ≤ 1024 := by
  rw [core.num.Usize.wrapping_add_val_eq, UScalar.size_UScalarTyUsize]
  have ha : a.val < Usize.size := by (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  have hs : 1024 < Usize.size := by (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  have h1 : (1024#usize).val = 1024 := by simp
  rw [h1]
  by_cases h : a.val + 1024 < Usize.size
  · rw [Nat.mod_eq_of_lt h]; omega
  · rw [Nat.mod_eq_sub_mod (by omega), Nat.mod_eq_of_lt (by omega)]; omega

@[local step]
theorem sample_counts_loop0_spec (s : Slice Std.U8) (f) (n nw step w : Std.Usize) (c : Nat)
    (hn : n.val ≤ s.length) (hnw : (nw.val = 1 ∧ n.val ≤ 32768) ∨ nw.val = 32)
    (hc : c ≤ 2 ^ 30) (hf : LeAll f.val c) :
    slot.sample_counts_loop0 s f n nw step w ⦃ fun r => LeAll r.val (c + (nw.val - w.val) * (32768 / nw.val)) ⦄ := by
  rw [slot.sample_counts_loop0]
  rcases hnw with ⟨h1, hn1⟩ | h32
  ·
    have hK : 32768 / nw.val = 32768 := by rw [h1]
    rw [hK]
    apply Std.loop.spec_decr_nat
      (measure := fun (_, w') => nw.val - w'.val)
      (inv := fun (f', w') => w.val ≤ w'.val ∧ w'.val - w.val ≤ nw.val - w.val ∧
        LeAll f'.val (c + (w'.val - w.val) * 32768))
    · rintro ⟨f', w'⟩ ⟨hw1, hw2, hf'⟩
      simp only [slot.sample_counts_loop0.body]
      step*
      repeat' (split <;> step*)
      all_goals try (exact LeAll_mono hf' (by (subst_vars; scalar_tac (simpAllMaxSteps := 0))))
      all_goals try (subst_vars; scalar_tac (simpAllMaxSteps := 0))
      refine ⟨by (subst_vars; scalar_tac (simpAllMaxSteps := 0)), by (subst_vars; scalar_tac (simpAllMaxSteps := 0)), LeAll_mono f1_post (by (subst_vars; scalar_tac (simpAllMaxSteps := 0))), by (subst_vars; scalar_tac (simpAllMaxSteps := 0))⟩
    · exact ⟨le_refl _, by omega, by simpa using hf⟩
  ·
    have hK : 32768 / nw.val = 1024 := by rw [h32]
    rw [hK]
    apply Std.loop.spec_decr_nat
      (measure := fun (_, w') => nw.val - w'.val)
      (inv := fun (f', w') => w.val ≤ w'.val ∧ w'.val - w.val ≤ nw.val - w.val ∧
        LeAll f'.val (c + (w'.val - w.val) * 1024))
    · rintro ⟨f', w'⟩ ⟨hw1, hw2, hf'⟩
      simp only [slot.sample_counts_loop0.body]
      step*
      repeat' (split <;> step*)
      all_goals try (exact LeAll_mono hf' (by (subst_vars; scalar_tac (simpAllMaxSteps := 0))))
      all_goals try (have := spine_wrap1024 a; (subst_vars; scalar_tac (simpAllMaxSteps := 0)))
      have := spine_wrap1024 a
      refine ⟨by (subst_vars; scalar_tac (simpAllMaxSteps := 0)), by (subst_vars; scalar_tac (simpAllMaxSteps := 0)), LeAll_mono f1_post (by (subst_vars; scalar_tac (simpAllMaxSteps := 0))), by (subst_vars; scalar_tac (simpAllMaxSteps := 0))⟩
    · exact ⟨le_refl _, by omega, by simpa using hf⟩

@[local step]
theorem sample_counts_spec (s) (f : Array Std.Usize 16#usize) (hf : LeAll f.val 0) :
    slot.sample_counts s f ⦃ fun r => LeAll r.val 32768 ⦄ := by
  rw [slot.sample_counts]
  step*
  repeat' (split <;> step*)
  all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))

@[local step]
theorem classify_loop0_spec (f tot k) :
    slot.classify_loop0 f tot k ⦃ fun _ => True ⦄ := by
  rw [slot.classify_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (tot_, k_) => 16 - k_.val)
    (inv := fun _ => True)
  · rintro ⟨tot_, k_⟩ _
    simp only [slot.classify_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · trivial

@[local step]
theorem classify_loop1_spec (f : Array Std.Usize 16#usize) (tot : Std.Usize) (k) (m : Array Std.Usize 16#usize)
    (htot : 0 < tot.val) (hf : LeAll f.val 32768) (hm : LeAll m.val 32768000) :
    slot.classify_loop1 f tot k m ⦃ fun r => LeAll r.val 32768000 ⦄ := by
  rw [slot.classify_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (k', _) => 16 - k'.val)
    (inv := fun (_, m') => LeAll m'.val 32768000)
  · rintro ⟨k', m'⟩ (hm' : LeAll m'.val 32768000)
    simp only [slot.classify_loop1.body]
    step*

    have h0 : i.val ≤ 32768 := by rw [i_post]; exact LeAll_get hf k'.val (by (subst_vars; scalar_tac (simpAllMaxSteps := 0)))
    have h1 : i1.val = i.val * 1000 := by
      simp only [i1_post, core.num.Usize.wrapping_mul_val_eq, UScalar.size_UScalarTyUsize]
      rw [Nat.mod_eq_of_lt] <;> (subst_vars; scalar_tac (simpAllMaxSteps := 0))
    have h2 : i2.val ≤ i1.val := by rw [i2_post]; exact Nat.div_le_self _ _
    refine ⟨?_, by (subst_vars; scalar_tac (simpAllMaxSteps := 0))⟩
    rw [a_post, Array.set_val_eq]
    exact LeAll_set hm' _ _ (by (subst_vars; scalar_tac (simpAllMaxSteps := 0)))
  · exact hm

theorem spine_LeAll_repeat0 (n : Std.Usize) (B : Nat) : LeAll (Array.repeat n 0#usize).val B := by
  rw [Array.repeat_val]; exact LeAll_replicate _ _ _ (by simp)

theorem spine_LeAll_read {ty : UScalarTy} {l : List (UScalar ty)} {B : Nat} (hl : LeAll l B)
    {x : UScalar ty} {j : Nat} {hj : j < l.length} (hx : x = l[j]) : x.val ≤ B := by
  subst hx; exact hl j hj

@[local step]
theorem classify_spec (s) : slot.classify s ⦃ fun _ => True ⦄ := by
  rw [slot.classify]
  have h0 := spine_LeAll_repeat0 16#usize 0
  have h1 := spine_LeAll_repeat0 16#usize 32768000
  step*

  all_goals
    try have hb1 := spine_LeAll_read m1_post nl_post
    try have hb3 := spine_LeAll_read m1_post dig_post
    try have hb4 := spine_LeAll_read m1_post lt_post
    try have hb5 := spine_LeAll_read m1_post q_post
    try have hb6 := spine_LeAll_read m1_post com_post
    try have hb7 := spine_LeAll_read m1_post hi_post
    try have hb8 := spine_LeAll_read m1_post zero_post
    try have hbi := spine_LeAll_read m1_post i_post
    try have hbi1 := spine_LeAll_read m1_post i1_post
    try have hbi2 := spine_LeAll_read m1_post i2_post
    try have hbi3 := spine_LeAll_read m1_post i3_post
    (subst_vars; scalar_tac (simpAllMaxSteps := 0))

@[local step]
theorem prose_like_loop_spec (s : Slice Std.U8) (n step : Std.Usize) (cnt) (tot i : Std.Usize)
    (hn : n.val ≤ s.length) :
    slot.prose_like_loop s n step cnt tot i ⦃ fun _ => True ⦄ := by
  rw [slot.prose_like_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, tot', _) => 4096 - tot'.val)
    (inv := fun _ => True)
  · rintro ⟨cnt', tot', i'⟩ _
    simp only [slot.prose_like_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · trivial

@[local step]
theorem prose_like_spec (s : Slice Std.U8) : slot.prose_like s ⦃ fun _ => True ⦄ := by
  rw [slot.prose_like]
  step*
  repeat' (split <;> step*)
  all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))

@[local step]
theorem route_class_spec (input : Slice Std.U8) : slot.route_class input ⦃ fun _ => True ⦄ := by
  rw [slot.route_class]
  step*
  repeat' (split <;> step*)

@[local step]
theorem dp_plan_spec (input : Slice Std.U8) (r : Std.Usize) :
    slot.dp_plan input r ⦃ fun _ => True ⦄ := by
  rw [slot.dp_plan]
  step*
  all_goals first
    | (subst_vars; scalar_tac (simpAllMaxSteps := 0))
    | (have hw := dp_wadd_self input.len (by rw [← i3_post]; (subst_vars; scalar_tac (simpAllMaxSteps := 0)))
       simpa using hw)

@[local step]
theorem C_GROUP_spec : slot.C_GROUP ⦃ fun x => x.val = 2147483648 ⦄ := by
  unfold slot.C_GROUP; step*

@[local step]
theorem C_LONG_ONLY_spec : slot.C_LONG_ONLY ⦃ fun x => x.val = 536870912 ⦄ := by
  unfold slot.C_LONG_ONLY; step*

theorem C_BLOCK_bounds : 8192 ≤ slot.C_BLOCK.val ∧ slot.C_BLOCK.val ≤ 1048576 := by simp [slot.C_BLOCK]

theorem C_WS_val : slot.C_WS.val = 32768 := by simp [slot.C_WS]

theorem C_KS_val : slot.C_KS.val = 65536 := by simp [slot.C_KS]

theorem C_HS_bounds : 2 ≤ slot.C_HS.val ∧ slot.C_HS.val ≤ 65536 := by simp [slot.C_HS]

theorem C_MS_val : slot.C_MS.val = 544 := by simp [slot.C_MS]

theorem C_PMASK_lt : slot.C_PMASK.val < 2 ^ 27 := by simp [slot.C_PMASK]

theorem C_KEEP_le : slot.C_KEEP.val ≤ 32 := by simp [slot.C_KEEP]

theorem C_SCALE_le : slot.C_SCALE.val ≤ 256 := by simp [slot.C_SCALE]

theorem C_UNUSED_LIT_le : slot.C_UNUSED_LIT.val ≤ 65536 := by simp [slot.C_UNUSED_LIT]

theorem C_UNUSED_LEN_le : slot.C_UNUSED_LEN.val ≤ 65536 := by simp [slot.C_UNUSED_LEN]

theorem C_UNUSED_DIST_le : slot.C_UNUSED_DIST.val ≤ 65536 := by simp [slot.C_UNUSED_DIST]

theorem C_UNUSED_LEN_W_le : slot.C_UNUSED_LEN_W.val ≤ 65536 := by simp [slot.C_UNUSED_LEN_W]

theorem C_UNUSED_DIST_W_le : slot.C_UNUSED_DIST_W.val ≤ 65536 := by simp [slot.C_UNUSED_DIST_W]

theorem C_TAX_W_le : slot.C_TAX_W.val ≤ 65536 := by simp [slot.C_TAX_W]

theorem C_TAX_C4_le : slot.C_TAX_C4.val ≤ 65536 := by simp [slot.C_TAX_C4]

theorem C_TAX_BT_le : slot.C_TAX_BT.val ≤ 65536 := by simp [slot.C_TAX_BT]

theorem C_TOKPEN_le : slot.C_TOKPEN.val ≤ 65536 := by simp [slot.C_TOKPEN]

theorem C_TOKPEN_W_le : slot.C_TOKPEN_W.val ≤ 65536 := by simp [slot.C_TOKPEN_W]

theorem C_TOKPEN_C4_le : slot.C_TOKPEN_C4.val ≤ 65536 := by simp [slot.C_TOKPEN_C4]

theorem C_TOKPEN_BT_le : slot.C_TOKPEN_BT.val ≤ 65536 := by simp [slot.C_TOKPEN_BT]

theorem C_CHAIN4_RATIO_le : slot.C_CHAIN4_RATIO.val ≤ 65535 := by simp [slot.C_CHAIN4_RATIO]

theorem C_STOP_DIV_pos : 0 < slot.C_STOP_DIV.val := by simp [slot.C_STOP_DIV]

theorem C_UP_MIN_ge : 1 ≤ slot.C_UP_MIN.val := by simp [slot.C_UP_MIN]

theorem C_REP_STEP_bounds : 1 ≤ slot.C_REP_STEP.val ∧ slot.C_REP_STEP.val ≤ 1048576 := by simp [slot.C_REP_STEP]

theorem C_REP6_MIN_le : slot.C_REP6_MIN.val ≤ 1048576 := by simp [slot.C_REP6_MIN]

theorem engC_LEXTRA_le (i : Nat) (h : i < 29) : (slot.C_LEXTRA.val[i]!).val ≤ 5 := by
  unfold slot.C_LEXTRA; simp only [Array.make]; revert i; decide

theorem engC_DEXTRA_le (i : Nat) (h : i < 30) : (slot.C_DEXTRA.val[i]!).val ≤ 13 := by
  unfold slot.C_DEXTRA; simp only [Array.make]; revert i; decide

@[local step]
theorem C_LEXTRA_index_spec (i : Std.Usize) (h : i.val < 29) :
    Array.index_usize slot.C_LEXTRA i ⦃ fun x => x.val ≤ 5 ⦄ := by
  have := engC_LEXTRA_le i.val h
  step*
  subst x_post
  rw [List.getElem!_eq_getElem?_getD, List.getElem?_eq_getElem (by (subst_vars; scalar_tac (simpAllMaxSteps := 0)))] at this
  exact this

@[local step]
theorem C_DEXTRA_index_spec (i : Std.Usize) (h : i.val < 30) :
    Array.index_usize slot.C_DEXTRA i ⦃ fun x => x.val ≤ 13 ⦄ := by
  have := engC_DEXTRA_le i.val h
  step*
  subst x_post
  rw [List.getElem!_eq_getElem?_getD, List.getElem?_eq_getElem (by (subst_vars; scalar_tac (simpAllMaxSteps := 0)))] at this
  exact this

@[local step]
theorem engC_wadd_usize_spec (x y : Std.Usize) :
    lift (core.num.Usize.wrapping_add x y) ⦃ fun z => z = core.num.Usize.wrapping_add x y ∧
      (x.val + y.val ≤ Usize.max → z.val = x.val + y.val) ⦄ := by
  simp only [lift, WP.spec_ok, true_and]
  intro h
  rw [core.num.Usize.wrapping_add_val_eq, UScalar.size_UScalarTyUsize]
  apply Nat.mod_eq_of_lt
  (subst_vars; scalar_tac (simpAllMaxSteps := 0))

@[local step]
theorem engC_wadd_u32_spec (x y : Std.U32) :
    lift (core.num.U32.wrapping_add x y) ⦃ fun z => z = core.num.U32.wrapping_add x y ∧
      (x.val + y.val ≤ U32.max → z.val = x.val + y.val) ⦄ := by
  simp only [lift, WP.spec_ok, true_and]
  intro h
  rw [core.num.U32.wrapping_add_val_eq]
  apply Nat.mod_eq_of_lt
  (subst_vars; scalar_tac (simpAllMaxSteps := 0))

@[local step]
theorem engC_mul_u64_spec (x y : Std.U64)
    (h : (x.val ≤ 4294967295 ∧ y.val ≤ 4294967295) ∨ x.val * y.val ≤ U64.max) :
    (x * y) ⦃ fun z => z.val = x.val * y.val ∧ (x.val ≤ 4294967295 → z.val ≤ 4294967295 * y.val) ⦄ := by
  have h' : x.val * y.val ≤ U64.max := by
    rcases h with ⟨hx, hy⟩ | h
    · have := Nat.mul_le_mul hx hy
      (subst_vars; scalar_tac (simpAllMaxSteps := 0))
    · exact h
  step*
  refine ⟨z_post, fun hx => ?_⟩
  rw [z_post]
  exact Nat.mul_le_mul_right _ hx

@[local step]
theorem engC_mul_u32_spec (x y : Std.U32)
    (h : (x.val ≤ 16777215 ∧ y.val ≤ 256) ∨ x.val * y.val ≤ U32.max) :
    (x * y) ⦃ fun z => z.val = x.val * y.val ∧ (y.val ≤ 256 → z.val ≤ 256 * x.val) ⦄ := by
  have h' : x.val * y.val ≤ U32.max := by
    rcases h with ⟨hx, hy⟩ | h
    · have := Nat.mul_le_mul hx hy
      (subst_vars; scalar_tac (simpAllMaxSteps := 0))
    · exact h
  step*
  refine ⟨z_post, fun hy => ?_⟩
  rw [z_post, Nat.mul_comm]
  exact Nat.mul_le_mul_right _ hy

@[local step]
theorem engC_div_u64_spec (x y : Std.U64) (h : y.val ≠ 0) :
    (x / y) ⦃ fun z => z.val = x.val / y.val ∧ (x.val ≤ 65536 * y.val → z.val ≤ 65536) ⦄ := by
  obtain ⟨z, hz, hv⟩ := UScalar.div_spec x h
  rw [hz]
  simp only [WP.spec_ok]
  refine ⟨hv, fun hx => ?_⟩
  rw [hv]
  exact Nat.div_le_of_le_mul (by rw [Nat.mul_comm]; exact hx)

@[local step]
theorem engC_cast_usize_u64_spec (x : Std.Usize) :
    lift (UScalar.cast .U64 x) ⦃ fun y => y = UScalar.cast .U64 x ∧ y.val = x.val ⦄ := by
  simp only [lift, WP.spec_ok, true_and]
  apply UScalar.cast_val_mod_pow_of_inBounds_eq
  have := x.hBounds
  have : 2 ^ UScalarTy.Usize.numBits ≤ 2 ^ UScalarTy.U64.numBits := by
    apply Nat.pow_le_pow_right (by decide)
    simp only [UScalarTy.numBits]
    cases System.Platform.numBits_eq <;> simp [*]
  omega

@[local step]
theorem engC_cast_u64_usize_spec (x : Std.U64) :
    lift (UScalar.cast .Usize x) ⦃ fun y => y = UScalar.cast .Usize x ∧ (x.val ≤ 4294967295 → y.val = x.val) ⦄ := by
  simp only [lift, WP.spec_ok, true_and]
  intro h
  apply UScalar.cast_val_mod_pow_of_inBounds_eq
  have : 2 ^ 32 ≤ 2 ^ UScalarTy.Usize.numBits := by
    apply Nat.pow_le_pow_right (by decide)
    simp only [UScalarTy.numBits]
    exact numBits_ge
  omega

@[local step]
theorem engC_push_spec {α : Type} (v : alloc.vec.Vec α) (x : α) (h : v.length < Usize.max) :
    alloc.vec.Vec.push v x ⦃ fun v1 => v1.val = v.val ++ [x] ∧ v1.length = v.length + 1 ⦄ := by
  step*
  exact ⟨v1_post, by simp [v1_post]⟩

theorem engC_LeAll_repeat {ty : UScalarTy} (n : Std.Usize) (x : UScalar ty) (B : Nat) (h : x.val ≤ B) :
    LeAll (Array.repeat n x).val B := by
  simp only [Array.repeat]
  exact LeAll_replicate _ _ _ h

theorem engC_with_capacity_length {α : Type} (n : Std.Usize) : (alloc.vec.Vec.with_capacity α n).length = 0 := rfl

theorem engC_ite_spec {α : Type} {c : Prop} [Decidable c] {A B : Result α} {P : α → Prop}
    (hA : c → A ⦃ P ⦄) (hB : ¬c → B ⦃ P ⦄) : (if c then A else B) ⦃ P ⦄ := by
  by_cases h : c
  · rw [if_pos h]; exact hA h
  · rw [if_neg h]; exact hB h

theorem engC_bind_ite_spec {α β : Type} {c : Prop} [Decidable c] {A B : Result α} {k : α → Result β}
    {P : β → Prop} (hA : c → (A >>= k) ⦃ P ⦄) (hB : ¬c → (B >>= k) ⦃ P ⦄) :
    ((if c then A else B) >>= k) ⦃ P ⦄ := by
  by_cases h : c
  · rw [if_pos h]; exact hA h
  · rw [if_neg h]; exact hB h

@[local step]
theorem c_rep_rates_loop_spec (s : Slice Std.U8) (n : Std.Usize) (head) (r4 r6 probes p : Std.Usize)
    (hn : n.val = s.length) (hn26 : n.val < 67108864) (hr4 : r4.val ≤ probes.val) (hr6 : r6.val ≤ probes.val)
    (hpr : probes.val ≤ p.val) (hp : p.val ≤ n.val + slot.C_REP_STEP.val) :
    slot.c_rep_rates_loop s n head r4 r6 probes p ⦃ fun r => r.1.val ≤ 65536 ∧ r.2.val ≤ 65536 ⦄ := by
  have f1 := C_REP_STEP_bounds
  have f2 := C_REP6_MIN_le
  have f3 := C_WS_val
  rw [slot.c_rep_rates_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, p') => n.val + slot.C_REP_STEP.val - p'.val)
    (inv := fun (_, r4', r6', pr', p') => r4'.val ≤ pr'.val ∧ r6'.val ≤ pr'.val ∧ pr'.val ≤ p'.val ∧
      p'.val ≤ n.val + slot.C_REP_STEP.val)
  · rintro ⟨h', r4', r6', pr', p'⟩ ⟨i1, i2, i3, i4⟩
    simp only [slot.c_rep_rates_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact ⟨hr4, hr6, hpr, hp⟩

@[local step]
theorem c_rep_rates_spec (s : Slice Std.U8) (hn26 : s.length < 67108864) :
    slot.c_rep_rates s ⦃ fun r => r.1.val ≤ 65536 ∧ r.2.val ≤ 65536 ⦄ := by
  rw [slot.c_rep_rates]
  step*
  repeat' (split <;> step*)
  all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))

@[local step]
theorem c_clear_span_loop_spec (plan e_nd p) :
    slot.c_clear_span_loop plan e_nd p ⦃ fun r => r.length = plan.length ⦄ := by
  rw [slot.c_clear_span_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, p') => e_nd.val - p'.val)
    (inv := fun (plan', _) => plan'.length = plan.length)
  · rintro ⟨plan', p'⟩ hinv
    simp only [slot.c_clear_span_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · rfl

@[local step]
theorem c_clear_span_spec (plan p0 e_nd) :
    slot.c_clear_span plan p0 e_nd ⦃ fun r => r.length = plan.length ⦄ := by
  rw [slot.c_clear_span]
  step*
  repeat' (split <;> step*)
  all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))

@[local step]
theorem c_dsym_spec (d) : slot.c_dsym d ⦃ fun r => r.val < 256 ⦄ := by
  rw [slot.c_dsym]
  step*
  repeat' (split <;> step*)
  all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))

@[local step]
theorem c_lsym_spec (len) : slot.c_lsym len ⦃ fun r => r.val < 256 ⦄ := by
  rw [slot.c_lsym]
  step*
  repeat' (split <;> step*)
  all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))

@[local step]
theorem c_path_block_loop0_spec (lf df) :
    slot.c_path_block_loop0 lf df 0#usize ⦃ fun r => LeAll r.1.val 0 ∧ LeAll r.2.val 0 ⦄ := by
  rw [slot.c_path_block_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, k) => 288 - k.val)
    (inv := fun (lf', df', k) => k.val ≤ 288 ∧
      (∀ j (hj : j < k.val) (hl : j < lf'.val.length), (lf'.val[j]).val = 0) ∧
      (∀ j (hj : j < k.val) (hl : j < df'.val.length), (df'.val[j]).val = 0))
  · rintro ⟨lf', df', k⟩ ⟨hk, hz1, hz2⟩
    simp only [slot.c_path_block_loop0.body]
    step*
    · refine ⟨by (subst_vars; scalar_tac (simpAllMaxSteps := 0)), ?_, ?_, by (subst_vars; scalar_tac (simpAllMaxSteps := 0))⟩
      · intro j hj hl
        subst a_post
        simp only [Array.set_val_eq, List.getElem_set]
        split
        · rfl
        · exact hz1 j (by (subst_vars; scalar_tac (simpAllMaxSteps := 0))) (by simpa using hl)
      · intro j hj hl
        subst a1_post
        simp only [Array.set_val_eq, List.getElem_set]
        split
        · rfl
        · exact hz2 j (by (subst_vars; scalar_tac (simpAllMaxSteps := 0))) (by simpa using hl)
    · have : k.val = 288 := by (subst_vars; scalar_tac (simpAllMaxSteps := 0))
      refine ⟨?_, ?_⟩
      · intro j hl
        have hl' : j < 288 := by simpa using hl
        rw [hz1 j (by omega) hl]
      · intro j hl
        have hl' : j < 288 := by simpa using hl
        rw [hz2 j (by omega) hl]
  · exact ⟨by simp, fun j hj => by simp at hj, fun j hj => by simp at hj⟩

@[local step]
theorem c_path_block_loop1_spec (s : Slice Std.U8) (choice) (lf df) (n p t : Std.Usize)
    (hn : n.val = s.length) (hlf : LeAll lf.val t.val) (hdf : LeAll df.val t.val) :
    slot.c_path_block_loop1 s choice lf df n p t ⦃ fun r => p.val ≤ r.2.2.val ∧ (p.val ≤ n.val → r.2.2.val ≤ n.val) ⦄ := by
  have hB := C_BLOCK_bounds
  rw [slot.c_path_block_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, t') => slot.C_BLOCK.val - t'.val)
    (inv := fun (lf', df', p', t') => LeAll lf'.val t'.val ∧ LeAll df'.val t'.val ∧ p.val ≤ p'.val ∧
      (p.val ≤ n.val → p'.val ≤ n.val))
  · rintro ⟨lf', df', p', t'⟩ ⟨hlf', hdf', hp1, hp2⟩
    simp only [slot.c_path_block_loop1.body]
    step*
    apply WP.spec_bind (Pₘ := fun (x : Std.Array Std.U32 288#usize × Std.Array Std.U32 288#usize × Std.Usize) =>
      LeAll x.1.val (t'.val + 1) ∧ LeAll x.2.1.val (t'.val + 1) ∧ p'.val < x.2.2.val ∧ x.2.2.val ≤ n.val)
    · split
      · step*
        ·
          have h6 := LeAll_get hlf' i5.val (by (subst_vars; scalar_tac (simpAllMaxSteps := 0)))
          have h12 := LeAll_get hdf' i11.val (by (subst_vars; scalar_tac (simpAllMaxSteps := 0)))
          refine ⟨?_, ?_, by (subst_vars; scalar_tac (simpAllMaxSteps := 0)), by (subst_vars; scalar_tac (simpAllMaxSteps := 0))⟩
          · rw [a_post, Array.set_val_eq]; exact LeAll_set_succ hlf' _ _ (by (subst_vars; scalar_tac (simpAllMaxSteps := 0)))
          · rw [a1_post, Array.set_val_eq]; exact LeAll_set_succ hdf' _ _ (by (subst_vars; scalar_tac (simpAllMaxSteps := 0)))
        ·
          have := LeAll_get hlf' i4.val (by (subst_vars; scalar_tac (simpAllMaxSteps := 0)))
          (subst_vars; scalar_tac (simpAllMaxSteps := 0))
        ·
          have := LeAll_get hlf' i4.val (by (subst_vars; scalar_tac (simpAllMaxSteps := 0)))
          refine ⟨?_, LeAll_mono hdf' (by omega), by (subst_vars; scalar_tac (simpAllMaxSteps := 0)), by (subst_vars; scalar_tac (simpAllMaxSteps := 0))⟩
          rw [a_post, Array.set_val_eq]; exact LeAll_set_succ hlf' _ _ (by (subst_vars; scalar_tac (simpAllMaxSteps := 0)))
      ·
        step*
        · have := LeAll_get hlf' i3.val (by (subst_vars; scalar_tac (simpAllMaxSteps := 0)))
          (subst_vars; scalar_tac (simpAllMaxSteps := 0))
        · have := LeAll_get hlf' i3.val (by (subst_vars; scalar_tac (simpAllMaxSteps := 0)))
          refine ⟨?_, LeAll_mono hdf' (by omega), by (subst_vars; scalar_tac (simpAllMaxSteps := 0)), by (subst_vars; scalar_tac (simpAllMaxSteps := 0))⟩
          rw [a_post, Array.set_val_eq]; exact LeAll_set_succ hlf' _ _ (by (subst_vars; scalar_tac (simpAllMaxSteps := 0)))
    · rintro ⟨lf1, df1, p1⟩ ⟨h1, h2, h3, h4⟩
      step*
  · exact ⟨hlf, hdf, le_refl _, fun h => h⟩

@[local step]
theorem c_path_block_spec (s choice p0 lf df) :
    slot.c_path_block s choice p0 lf df ⦃ fun r => p0.val ≤ r.1.val ∧ (p0.val ≤ s.length → r.1.val ≤ s.length) ⦄ := by
  rw [slot.c_path_block]
  step*

@[local step]
theorem c_fixed_bits_loop0_spec (lf) (bits : Std.U64) (i : Std.Usize) (hi : i.val ≤ 288)
    (hb : bits.val ≤ 3 + i.val * 2 ^ 40) :
    slot.c_fixed_bits_loop0 lf bits i ⦃ fun r => r.val ≤ 3 + 288 * 2 ^ 40 ⦄ := by
  rw [slot.c_fixed_bits_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, i') => 288 - i'.val)
    (inv := fun (bits', i') => i'.val ≤ 288 ∧ bits'.val ≤ 3 + i'.val * 2 ^ 40)
  · rintro ⟨bits', i'⟩ ⟨hi', hb'⟩
    simp only [slot.c_fixed_bits_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · exact ⟨hi, hb⟩

@[local step]
theorem c_fixed_bits_loop1_spec (df) (bits : Std.U64) (d : Std.Usize) (hd : d.val ≤ 30)
    (hb : bits.val ≤ 3 + 288 * 2 ^ 40 + d.val * 2 ^ 40) :
    slot.c_fixed_bits_loop1 df bits d ⦃ fun r => r.val ≤ 3 + 318 * 2 ^ 40 ⦄ := by
  rw [slot.c_fixed_bits_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, d') => 30 - d'.val)
    (inv := fun (bits', d') => d'.val ≤ 30 ∧ bits'.val ≤ 3 + 288 * 2 ^ 40 + d'.val * 2 ^ 40)
  · rintro ⟨bits', d'⟩ ⟨hd', hb'⟩
    simp only [slot.c_fixed_bits_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · exact ⟨hd, hb⟩

@[local step]
theorem c_fixed_bits_spec (lf df) :
    slot.c_fixed_bits lf df ⦃ fun _ => True ⦄ := by
  rw [slot.c_fixed_bits]
  step*
  repeat' (split <;> step*)
  all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))

@[local step]
theorem c_rle_run_loop0_spec (clf) (r : Std.Usize) (extra : Std.U64) (fuel : Std.Usize)
    (hx : extra.val + 7 * fuel.val ≤ 2 ^ 40) :
    slot.c_rle_run_loop0 clf r extra fuel ⦃ fun res => res.2.2.val ≤ extra.val + 7 * fuel.val ⦄ := by
  rw [slot.c_rle_run_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, f) => f.val)
    (inv := fun (_, _, e, f) => e.val + 7 * f.val ≤ extra.val + 7 * fuel.val)
  · rintro ⟨clf', r', e', f'⟩ hinv
    simp only [slot.c_rle_run_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · simp

@[local step]
theorem c_rle_run_loop1_spec (clf) (r : Std.Usize) (extra : Std.U64) (fuel : Std.Usize)
    (hx : extra.val + 2 * fuel.val ≤ 2 ^ 40) :
    slot.c_rle_run_loop1 clf r extra fuel ⦃ fun res => res.2.2.val ≤ extra.val + 2 * fuel.val ⦄ := by
  rw [slot.c_rle_run_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, f) => f.val)
    (inv := fun (_, _, e, f) => e.val + 2 * f.val ≤ extra.val + 2 * fuel.val)
  · rintro ⟨clf', r', e', f'⟩ hinv
    simp only [slot.c_rle_run_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · simp

@[local step]
theorem c_rle_run_spec (clf v) (r0 : Std.Usize) (hr0 : 1 ≤ r0.val ∧ r0.val ≤ 512) :
    slot.c_rle_run clf v r0 ⦃ fun r => r.1.val ≤ 7 * (r0.val + 1) ⦄ := by
  rw [slot.c_rle_run]
  step*
  repeat' (split <;> step*)
  all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))

@[local step]
theorem c_radix_pass_loop0_spec (sw) (k : Std.Usize) (shift : Std.U32) (hshift : shift.val < 32) :
    slot.c_radix_pass_loop0 sw k shift (Array.repeat 257#usize 0#usize) 0#usize ⦃ fun r => LeAll r.val 288 ⦄ := by
  rw [slot.c_radix_pass_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, i') => 288 - i'.val)
    (inv := fun (cnt', i') => i'.val ≤ 288 ∧ LeAll cnt'.val i'.val)
  · rintro ⟨cnt', i'⟩ ⟨hi', hc'⟩
    simp only [slot.c_radix_pass_loop0.body]
    step*
    all_goals first
      | (subst_vars; scalar_tac (simpAllMaxSteps := 0))
      | exact LeAll_mono hc' (by (subst_vars; scalar_tac (simpAllMaxSteps := 0)))
      | (refine ⟨by (subst_vars; scalar_tac (simpAllMaxSteps := 0)), ?_, by (subst_vars; scalar_tac (simpAllMaxSteps := 0))⟩
         rw [a_post, Array.set_val_eq, show i9.val = i'.val + 1 by (subst_vars; scalar_tac (simpAllMaxSteps := 0))]
         apply LeAll_set_succ hc'
         have := LeAll_get hc' i5.val (by (subst_vars; scalar_tac (simpAllMaxSteps := 0)))
         (subst_vars; scalar_tac (simpAllMaxSteps := 0)))
  · exact ⟨by simp, engC_LeAll_repeat _ _ _ (by simp)⟩

@[local step]
theorem c_radix_pass_loop1_spec (cnt) (hcnt : LeAll cnt.val 288) :
    slot.c_radix_pass_loop1 cnt 1#usize ⦃ fun r => LeAll r.val 74016 ⦄ := by
  rw [slot.c_radix_pass_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, c') => 257 - c'.val)
    (inv := fun (cnt', c') => 1 ≤ c'.val ∧ c'.val ≤ 257 ∧
      (∀ j (hj : j < cnt'.val.length), j < c'.val → (cnt'.val[j]).val ≤ 288 * c'.val) ∧
      (∀ j (hj : j < cnt'.val.length), c'.val ≤ j → (cnt'.val[j]).val ≤ 288))
  · rintro ⟨cnt', c'⟩ ⟨hc1, hc2, hlo, hhi⟩
    simp only [slot.c_radix_pass_loop1.body]
    step*
    · have hi : i.val ≤ 288 := by rw [i_post]; exact hhi _ _ (le_refl _)
      have hi2 : i2.val ≤ 288 * c'.val := by rw [i2_post]; exact hlo _ _ (by (subst_vars; scalar_tac (simpAllMaxSteps := 0)))
      refine ⟨by (subst_vars; scalar_tac (simpAllMaxSteps := 0)), by (subst_vars; scalar_tac (simpAllMaxSteps := 0)), ?_, ?_, by (subst_vars; scalar_tac (simpAllMaxSteps := 0))⟩
      · intro j hj hjc
        subst a_post
        simp only [Array.set_val_eq, List.getElem_set]
        split
        · (subst_vars; scalar_tac (simpAllMaxSteps := 0))
        · have hj' : j < (↑cnt' : List Std.Usize).length := by simpa using hj
          have := hlo j hj' (by (subst_vars; scalar_tac (simpAllMaxSteps := 0)))
          (subst_vars; scalar_tac (simpAllMaxSteps := 0))
      · intro j hj hjc
        subst a_post
        simp only [Array.set_val_eq, List.getElem_set]
        split
        · (subst_vars; scalar_tac (simpAllMaxSteps := 0))
        · exact hhi j (by simpa using hj) (by (subst_vars; scalar_tac (simpAllMaxSteps := 0)))
    · intro j hj
      have hj2 : j < 257 := by simpa using hj
      have := hlo j hj (by (subst_vars; scalar_tac (simpAllMaxSteps := 0)))
      (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · refine ⟨by simp, by simp, ?_, ?_⟩
    · intro j hj hj1
      have := hcnt j hj
      simp at hj1 ⊢
      omega
    · intro j hj _
      exact hcnt j hj

@[local step]
theorem c_radix_pass_loop2_spec (sw ss dw ds) (k : Std.Usize) (shift : Std.U32) (cnt) (hshift : shift.val < 32)
    (hcnt : LeAll cnt.val 74016) :
    slot.c_radix_pass_loop2 sw ss dw ds k shift cnt 0#usize ⦃ fun _ => True ⦄ := by
  rw [slot.c_radix_pass_loop2]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, j') => 288 - j'.val)
    (inv := fun (_, _, cnt', j') => j'.val ≤ 288 ∧ LeAll cnt'.val (74016 + j'.val))
  · rintro ⟨dw', ds', cnt', j'⟩ ⟨hj', hc'⟩
    simp only [slot.c_radix_pass_loop2.body]
    step*
    all_goals first
      | (subst_vars; scalar_tac (simpAllMaxSteps := 0))
      | (have := LeAll_get hc' i3.val (by (subst_vars; scalar_tac (simpAllMaxSteps := 0)))
         (subst_vars; scalar_tac (simpAllMaxSteps := 0)))
      | (refine ⟨by (subst_vars; scalar_tac (simpAllMaxSteps := 0)), ?_, by (subst_vars; scalar_tac (simpAllMaxSteps := 0))⟩
         rw [a2_post, Array.set_val_eq, show j1.val = j'.val + 1 by (subst_vars; scalar_tac (simpAllMaxSteps := 0)), ← Nat.add_assoc]
         apply LeAll_set_succ hc'
         have := LeAll_get hc' i3.val (by (subst_vars; scalar_tac (simpAllMaxSteps := 0)))
         (subst_vars; scalar_tac (simpAllMaxSteps := 0)))
  · exact ⟨by simp, by simpa using hcnt⟩

@[local step]
theorem c_radix_pass_spec (sw ss dw ds) (k : Std.Usize) (shift : Std.U32) (hshift : shift.val < 32) :
    slot.c_radix_pass sw ss dw ds k shift ⦃ fun _ => True ⦄ := by
  rw [slot.c_radix_pass]
  step*

@[local step]
theorem c_huff_lengths_loop0_spec (freq m lens aw asy) (k i : Std.Usize) (hk : k.val ≤ i.val) (hi : i.val ≤ 288) :
    slot.c_huff_lengths_loop0 freq m lens aw asy k i ⦃ fun r => r.2.2.2.val ≤ 288 ⦄ := by
  rw [slot.c_huff_lengths_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, i') => 288 - i'.val)
    (inv := fun (_, _, _, k', i') => k'.val ≤ i'.val ∧ i'.val ≤ 288)
  · rintro ⟨lens', aw', asy', k', i'⟩ ⟨hk', hi'⟩
    simp only [slot.c_huff_lengths_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · exact ⟨hk, hi⟩

@[local step]
theorem c_huff_lengths_loop1_loop0_spec (aw) (k : Std.Usize) (iw ipar lpar) (li ii ni : Std.Usize) (w2) (t : Std.Usize)
    (hii : ii.val ≤ 2 ^ 20) :
    slot.c_huff_lengths_loop1_loop0 aw k iw ipar lpar li ii ni w2 t ⦃ fun r => r.2.2.2.1.val ≤ ii.val + 2 ⦄ := by
  rw [slot.c_huff_lengths_loop1_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, _, t') => 2 - t'.val)
    (inv := fun (_, _, _, ii', _, t') => ii'.val + t.val ≤ ii.val + t'.val ∧ t.val ≤ t'.val ∧
      (t.val ≤ 2 → t'.val ≤ 2) ∧ (2 < t.val → t'.val = t.val))
  · rintro ⟨ipar', lpar', li', ii', w2', t'⟩ ⟨h1, h2, h3, h4⟩
    simp only [slot.c_huff_lengths_loop1_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · simp

@[local step]
theorem c_huff_lengths_loop1_spec (aw) (k : Std.Usize) (iw ipar lpar) (li ii ni : Std.Usize) (hii : ii.val ≤ 2 * ni.val)
    (hni : ni.val ≤ 287) (hk : k.val ≤ 288) :
    slot.c_huff_lengths_loop1 aw k iw ipar lpar li ii ni ⦃ fun r => ni.val ≤ r.2.2.val ∧ (ni.val + 1 < k.val → ni.val < r.2.2.val) ⦄ := by
  rw [slot.c_huff_lengths_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, _, ni') => 287 - ni'.val)
    (inv := fun (_, _, _, _, ii', ni') => ni.val ≤ ni'.val ∧ ni'.val ≤ 287 ∧ ii'.val ≤ 2 * ni'.val)
  · rintro ⟨iw', ipar', lpar', li', ii', ni'⟩ ⟨h1, h2, h3⟩
    simp only [slot.c_huff_lengths_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · exact ⟨le_refl _, hni, hii⟩

@[local step]
theorem c_huff_lengths_loop2_spec (ipar idep j) :
    slot.c_huff_lengths_loop2 ipar idep j ⦃ fun _ => True ⦄ := by
  rw [slot.c_huff_lengths_loop2]
  apply Std.loop.spec_decr_nat
    (measure := fun (idep_, j_) => j_.val)
    (inv := fun _ => True)
  · rintro ⟨idep_, j_⟩ _
    simp only [slot.c_huff_lengths_loop2.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · trivial

@[local step]
theorem c_huff_lengths_loop3_spec (lens asy k lpar idep x) :
    slot.c_huff_lengths_loop3 lens asy k lpar idep x ⦃ fun _ => True ⦄ := by
  rw [slot.c_huff_lengths_loop3]
  apply Std.loop.spec_decr_nat
    (measure := fun (lens_, x_) => k.val - x_.val)
    (inv := fun _ => True)
  · rintro ⟨lens_, x_⟩ _
    simp only [slot.c_huff_lengths_loop3.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · trivial

@[local step]
theorem c_huff_lengths_spec (freq m lens) : slot.c_huff_lengths freq m lens ⦃ fun _ => True ⦄ := by
  rw [slot.c_huff_lengths]
  step*
  repeat' (split <;> step*)
  all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))

@[local step]
theorem c_dyn_bits_loop0_spec (lf ll) (body : Std.U64) (hlit i : Std.Usize) (hi : i.val ≤ 286)
    (hb : body.val ≤ i.val * 2 ^ 41) :
    slot.c_dyn_bits_loop0 lf ll body hlit i ⦃ fun r => r.1.val ≤ 286 * 2 ^ 41 ∧ r.2.val ≤ max hlit.val 286 ⦄ := by
  rw [slot.c_dyn_bits_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, i') => 286 - i'.val)
    (inv := fun (b', h', i') => i'.val ≤ 286 ∧ b'.val ≤ i'.val * 2 ^ 41 ∧ h'.val ≤ max hlit.val 286)
  · rintro ⟨b', h', i'⟩ ⟨h1, h2, h3⟩
    simp only [slot.c_dyn_bits_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · exact ⟨hi, hb, by (subst_vars; scalar_tac (simpAllMaxSteps := 0))⟩

@[local step]
theorem c_dyn_bits_loop1_spec (df dl) (body : Std.U64) (hdist any : Std.Usize) (d : Std.Usize) (hd : d.val ≤ 30)
    (hb : body.val ≤ 286 * 2 ^ 41 + d.val * 2 ^ 41) :
    slot.c_dyn_bits_loop1 df dl body hdist any d ⦃ fun r => r.1.val ≤ 316 * 2 ^ 41 ∧ r.2.1.val ≤ max hdist.val 30 ⦄ := by
  rw [slot.c_dyn_bits_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, d') => 30 - d'.val)
    (inv := fun (b', h', _, d') => d'.val ≤ 30 ∧ b'.val ≤ 286 * 2 ^ 41 + d'.val * 2 ^ 41 ∧ h'.val ≤ max hdist.val 30)
  · rintro ⟨b', h', a', d'⟩ ⟨h1, h2, h3⟩
    simp only [slot.c_dyn_bits_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · exact ⟨hd, hb, by (subst_vars; scalar_tac (simpAllMaxSteps := 0))⟩

@[local step]
theorem c_dyn_bits_loop2_spec (ll dl hlit total seq i2) :
    slot.c_dyn_bits_loop2 ll dl hlit total seq i2 ⦃ fun _ => True ⦄ := by
  rw [slot.c_dyn_bits_loop2]
  apply Std.loop.spec_decr_nat
    (measure := fun (seq_, i2_) => total.val - i2_.val)
    (inv := fun _ => True)
  · rintro ⟨seq_, i2_⟩ _
    simp only [slot.c_dyn_bits_loop2.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · trivial

@[local step]
theorem c_dyn_bits_loop3_loop0_spec (total seq) (j r : Std.Usize) (v) (hj : j.val ≤ 512) (hr : r.val ≤ 512) :
    slot.c_dyn_bits_loop3_loop0 total seq j v r ⦃ fun res => r.val ≤ res.val ∧ res.val ≤ max r.val 512 ∧
      (j.val + r.val ≤ 512 → j.val + res.val ≤ 512) ⦄ := by
  rw [slot.c_dyn_bits_loop3_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun r' => 512 - r'.val)
    (inv := fun r' => r.val ≤ r'.val ∧ r'.val ≤ max r.val 512 ∧ (j.val + r.val ≤ 512 → j.val + r'.val ≤ 512))
  · rintro r' ⟨h1, h2, h3⟩
    simp only [slot.c_dyn_bits_loop3_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · exact ⟨le_refl _, by (subst_vars; scalar_tac (simpAllMaxSteps := 0)), fun h => h⟩

@[local step]
theorem c_dyn_bits_loop3_spec (clf) (extra : Std.U64) (total seq) (j : Std.Usize) (hj : j.val ≤ 512)
    (hx : extra.val ≤ j.val * 4096) :
    slot.c_dyn_bits_loop3 clf extra total seq j ⦃ fun r => r.2.val ≤ 513 * 4096 ⦄ := by
  rw [slot.c_dyn_bits_loop3]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, j') => 512 - j'.val)
    (inv := fun (_, e', j') => j'.val ≤ 512 ∧ e'.val ≤ j'.val * 4096)
  · rintro ⟨clf', e', j'⟩ ⟨h1, h2⟩
    simp only [slot.c_dyn_bits_loop3.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · exact ⟨hj, hx⟩

@[local step]
theorem c_dyn_bits_loop4_spec (cl hclen) :
    slot.c_dyn_bits_loop4 cl hclen ⦃ fun r => r.val ≤ hclen.val ⦄ := by
  rw [slot.c_dyn_bits_loop4]
  apply Std.loop.spec_decr_nat
    (measure := fun h' => h'.val)
    (inv := fun h' => h'.val ≤ hclen.val)
  · rintro h' h1
    simp only [slot.c_dyn_bits_loop4.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · exact le_refl _

@[local step]
theorem c_dyn_bits_loop5_spec (clf cl) (hdr : Std.U64) (c : Std.Usize) (hc : c.val ≤ 19)
    (hh : hdr.val ≤ 2 ^ 40 + c.val * 2 ^ 35) :
    slot.c_dyn_bits_loop5 clf cl hdr c ⦃ fun r => r.val ≤ 2 ^ 40 + 19 * 2 ^ 35 ⦄ := by
  rw [slot.c_dyn_bits_loop5]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, c') => 19 - c'.val)
    (inv := fun (h', c') => c'.val ≤ 19 ∧ h'.val ≤ 2 ^ 40 + c'.val * 2 ^ 35)
  · rintro ⟨h', c'⟩ ⟨h1, h2⟩
    simp only [slot.c_dyn_bits_loop5.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · exact ⟨hc, hh⟩

@[local step]
theorem c_dyn_bits_spec (lf df) : slot.c_dyn_bits lf df ⦃ fun _ => True ⦄ := by
  rw [slot.c_dyn_bits]
  step*
  repeat' (split <;> step*)
  all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))

@[local step]
theorem c_plan_blocks_loop0_loop0_spec (s : Slice Std.U8) (ec q : Std.Usize)
    (hec : ec.val ≤ s.length) (hn26 : s.length < 67108864) :
    slot.c_plan_blocks_loop0_loop0 s ec (Array.repeat 288#usize 0#u32) q ⦃ fun _ => True ⦄ := by
  rw [slot.c_plan_blocks_loop0_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, q') => ec.val - q'.val)
    (inv := fun (lb', q') => LeAll lb'.val q'.val)
  · rintro ⟨lb', q'⟩ hlb'
    simp only [slot.c_plan_blocks_loop0_loop0.body]
    step*
    all_goals first
      | (have := LeAll_get hlb' i1.val (by (subst_vars; scalar_tac (simpAllMaxSteps := 0)))
         (subst_vars; scalar_tac (simpAllMaxSteps := 0)))
      | (refine ⟨?_, by (subst_vars; scalar_tac (simpAllMaxSteps := 0))⟩
         rw [a_post, Array.set_val_eq, show q1.val = q'.val + 1 by (subst_vars; scalar_tac (simpAllMaxSteps := 0))]
         apply LeAll_set_succ hlb'
         have := LeAll_get hlb' i1.val (by (subst_vars; scalar_tac (simpAllMaxSteps := 0)))
         (subst_vars; scalar_tac (simpAllMaxSteps := 0)))
  · exact engC_LeAll_repeat _ _ _ (by simp)

@[local step]
theorem c_plan_blocks_loop0_spec (s : Slice Std.U8) (plan) (n : Std.Usize) (lf df p fuel) (hn : n.val = s.length)
    (hn26 : n.val < 67108864) :
    slot.c_plan_blocks_loop0 s plan n lf df p fuel ⦃ fun _ => True ⦄ := by
  have hB := C_BLOCK_bounds
  rw [slot.c_plan_blocks_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, f) => f.val)
    (inv := fun _ => True)
  · rintro ⟨plan', lf', df', p', f'⟩ _
    simp only [slot.c_plan_blocks_loop0.body]
    step*
    apply WP.spec_bind (Pₘ := fun _ => True)
    · split <;> step*
    rintro ca _
    step*
    apply WP.spec_bind (Pₘ := fun (x : Std.Usize) => p'.val ≤ x.val ∧ x.val ≤ n.val)
    · split <;> step*
      all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
    rintro eb ⟨heb1, heb2⟩
    apply WP.spec_bind (Pₘ := fun (x : Std.Usize) => p'.val ≤ x.val ∧ x.val ≤ n.val)
    · split <;> step*
      all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
    rintro ec ⟨hec1, hec2⟩
    step*
    apply WP.spec_bind (Pₘ := fun _ => True)
    · split <;> step*
    rintro cb _
    apply WP.spec_bind (Pₘ := fun _ => True)
    · split <;> step*
    rintro cb1 _
    step*
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · trivial

@[local step]
theorem c_plan_blocks_spec (s : Slice Std.U8) (plan) (hn26 : s.length < 67108864) :
    slot.c_plan_blocks s plan ⦃ fun _ => True ⦄ := by
  rw [slot.c_plan_blocks]
  step*
  repeat' (split <;> step*)
  all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))

@[local step]
theorem c_is_dna_loop_spec (s : Slice Std.U8) (n allow : Std.Usize) (bad i : Std.Usize) (hn : n.val ≤ s.length)
    (hbad : bad.val ≤ i.val) :
    slot.c_is_dna_loop s n allow bad i ⦃ fun _ => True ⦄ := by
  rw [slot.c_is_dna_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, i') => n.val - i'.val)
    (inv := fun (bad', i') => bad'.val ≤ i'.val)
  · rintro ⟨bad', i'⟩ hb'
    simp only [slot.c_is_dna_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · exact hbad

@[local step]
theorem c_is_dna_spec (s) :
    slot.c_is_dna s ⦃ fun _ => True ⦄ := by
  rw [slot.c_is_dna]
  step*
  repeat' (split <;> step*)
  all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))

@[local step]
theorem c_push_model_loop0_spec (lf df ll dl) (est : Std.U64) (q : Std.Usize) (hq : q.val ≤ 288)
    (he : est.val ≤ 70 + q.val * 2 ^ 42) :
    slot.c_push_model_loop0 lf df ll dl est q ⦃ fun r => r.val ≤ 70 + 288 * 2 ^ 42 ⦄ := by
  rw [slot.c_push_model_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, q') => 288 - q'.val)
    (inv := fun (e', q') => q'.val ≤ 288 ∧ e'.val ≤ 70 + q'.val * 2 ^ 42)
  · rintro ⟨e', q'⟩ ⟨h1, h2⟩
    simp only [slot.c_push_model_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · exact ⟨hq, he⟩

@[local step]
theorem c_push_model_loop1_spec (models) (tokpen : Std.U32) (ll) (i : Std.Usize) (htok : tokpen.val ≤ 65536)
    (hm : models.length + (256 - i.val) < 4294967295) :
    slot.c_push_model_loop1 models tokpen ll i ⦃ fun r => r.length = models.length + (256 - i.val) ⦄ := by
  have h1 := C_SCALE_le
  have h2 := C_UNUSED_LIT_le
  rw [slot.c_push_model_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, i') => 256 - i'.val)
    (inv := fun (m', i') => m'.length = models.length + (i'.val - i.val) ∧ i.val ≤ i'.val ∧ i'.val ≤ max i.val 256)
  · rintro ⟨m', i'⟩ ⟨h3, h4, h5⟩
    simp only [slot.c_push_model_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · exact ⟨by simp, le_refl _, by (subst_vars; scalar_tac (simpAllMaxSteps := 0))⟩

@[local step]
theorem c_push_model_loop2_spec (models) (tax ulen tokpen : Std.U32) (ll) (l : Std.Usize) (htax : tax.val ≤ 65536)
    (hulen : ulen.val ≤ 65536) (htok : tokpen.val ≤ 65536) (hl : 3 ≤ l.val)
    (hm : models.length + (259 - l.val) < 4294967295) :
    slot.c_push_model_loop2 models tax ulen tokpen ll l ⦃ fun r => r.length = models.length + (259 - l.val) ⦄ := by
  have h1 := C_SCALE_le
  rw [slot.c_push_model_loop2]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, l') => 259 - l'.val)
    (inv := fun (m', l') => m'.length = models.length + (l'.val - l.val) ∧ l.val ≤ l'.val ∧ l'.val ≤ max l.val 259)
  · rintro ⟨m', l'⟩ ⟨h3, h4, h5⟩
    simp only [slot.c_push_model_loop2.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · exact ⟨by simp, le_refl _, by (subst_vars; scalar_tac (simpAllMaxSteps := 0))⟩

@[local step]
theorem c_push_model_loop3_spec (models) (udist : Std.U32) (dl) (d : Std.Usize) (hud : udist.val ≤ 65536)
    (hm : models.length + (32 - d.val) < 4294967295) :
    slot.c_push_model_loop3 models udist dl d ⦃ fun r => r.length = models.length + (32 - d.val) ⦄ := by
  have h1 := C_SCALE_le
  rw [slot.c_push_model_loop3]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, d') => 32 - d'.val)
    (inv := fun (m', d') => m'.length = models.length + (d'.val - d.val) ∧ d.val ≤ d'.val ∧ d'.val ≤ max d.val 32)
  · rintro ⟨m', d'⟩ ⟨h3, h4, h5⟩
    simp only [slot.c_push_model_loop3.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · exact ⟨by simp, le_refl _, by (subst_vars; scalar_tac (simpAllMaxSteps := 0))⟩

@[local step]
theorem c_push_model_spec (models lf df) (tax ulen udist tokpen : Std.U32) (htax : tax.val ≤ 65536) (hulen : ulen.val ≤ 65536)
    (hud : udist.val ≤ 65536) (htok : tokpen.val ≤ 65536) (hm : models.length + 544 < 4294967295) :
    slot.c_push_model models lf df tax ulen udist tokpen ⦃ fun r => r.1.val ≤ 70 + 288 * 2 ^ 42 ∧ r.2.length = models.length + 544 ⦄ := by
  rw [slot.c_push_model]
  step*
  repeat' (split <;> step*)
  all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))

@[local step]
theorem c_restat_loop0_loop0_spec (s : Slice Std.U8) (choice) (n : Std.Usize) (lf df) (p t : Std.Usize)
    (hn : n.val ≤ s.length) (hnc : n.val ≤ choice.length) (hn26 : n.val < 67108864) :
    slot.c_restat_loop0_loop0 s choice n lf df p t ⦃ fun r => p.val ≤ r.2.2.val ∧
      r.2.2.val ≤ max p.val (n.val + 511) ∧
      (p.val < n.val → t.val < slot.C_BLOCK.val → p.val < r.2.2.val) ∧
      (r.2.2.val < n.val → p.val + (slot.C_BLOCK.val - t.val) ≤ r.2.2.val) ⦄ := by
  have hB := C_BLOCK_bounds
  rw [slot.c_restat_loop0_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, t') => slot.C_BLOCK.val - t'.val)
    (inv := fun (_, _, p', t') => p.val + (t'.val - t.val) ≤ p'.val ∧ t.val ≤ t'.val ∧
      p'.val ≤ max p.val (n.val + 511) ∧ t'.val ≤ max t.val slot.C_BLOCK.val)
  · rintro ⟨lf', df', p', t'⟩ ⟨h1, h2, h3, h4⟩
    simp only [slot.c_restat_loop0_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · exact ⟨by simp, le_refl _, by (subst_vars; scalar_tac (simpAllMaxSteps := 0)), by (subst_vars; scalar_tac (simpAllMaxSteps := 0))⟩

@[local step]
theorem c_restat_loop0_spec (s : Slice Std.U8) (choice models bstart) (tax ulen udist tokpen : Std.U32)
    (total : Std.U64) (n : Std.Usize) (lf df) (p : Std.Usize)
    (hn : n.val ≤ s.length) (hnc : n.val ≤ choice.length) (hn26 : n.val < 67108864)
    (htax : tax.val ≤ 65536) (hulen : ulen.val ≤ 65536) (hud : udist.val ≤ 65536) (htok : tokpen.val ≤ 65536)
    (hb : 544 * bstart.length ≤ models.length + 544)
    (ht : 544 * total.val ≤ models.length * (70 + 288 * 2 ^ 42))
    (hm : models.length * 8192 < 544 * (n.val + 8192))
    (hp : p.val < n.val → models.length * 8192 ≤ 544 * p.val) :
    slot.c_restat_loop0 s choice models bstart tax ulen udist tokpen total n lf df p ⦃ fun r =>
      544 * r.2.1.length ≤ r.1.length + 544 ∧ 544 * r.2.2.1.val ≤ r.1.length * (70 + 288 * 2 ^ 42) ∧
      r.1.length * 8192 < 544 * (n.val + 8192) ⦄ := by
  have hB := C_BLOCK_bounds
  rw [slot.c_restat_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, _, p') => n.val - p'.val)
    (inv := fun (m', b', t', _, _, p') => 544 * b'.length ≤ m'.length + 544 ∧
      544 * t'.val ≤ m'.length * (70 + 288 * 2 ^ 42) ∧ m'.length * 8192 < 544 * (n.val + 8192) ∧
      (p'.val < n.val → m'.length * 8192 ≤ 544 * p'.val))
  · rintro ⟨m', b', t', lf', df', p'⟩ ⟨h1, h2, h3, h4⟩
    simp only [slot.c_restat_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · exact ⟨hb, ht, hm, hp⟩

@[local step]
theorem c_restat_spec (s : Slice Std.U8) (choice models bstart) (tax ulen udist tokpen : Std.U32)
    (hn26 : s.length < 67108864) (htax : tax.val ≤ 65536) (hulen : ulen.val ≤ 65536) (hud : udist.val ≤ 65536)
    (htok : tokpen.val ≤ 65536) :
    slot.c_restat s choice models bstart tax ulen udist tokpen ⦃ fun r => r.2.2.length ≤ 1048576 ⦄ := by
  rw [slot.c_restat]
  step*
  repeat' (split <;> step*)
  all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))

@[local step]
theorem c_greedy_choice_loop0_spec (choice n p) :
    slot.c_greedy_choice_loop0 choice n p ⦃ fun _ => True ⦄ := by
  rw [slot.c_greedy_choice_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (choice_, p_) => n.val - p_.val)
    (inv := fun _ => True)
  · rintro ⟨choice_, p_⟩ _
    simp only [slot.c_greedy_choice_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · trivial

@[local step]
theorem c_greedy_choice_loop1_spec (clist choice n gmin) (m k : Std.Usize) (hm : m.val = clist.length) (hk : 1 ≤ k.val) :
    slot.c_greedy_choice_loop1 clist choice n gmin m k ⦃ fun _ => True ⦄ := by
  rw [slot.c_greedy_choice_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, k') => m.val - k'.val)
    (inv := fun (_, k') => 1 ≤ k'.val)
  · rintro ⟨choice', k'⟩ hk'
    simp only [slot.c_greedy_choice_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · exact hk

@[local step]
theorem c_greedy_choice_spec (clist choice n gmin) :
    slot.c_greedy_choice clist choice n gmin ⦃ fun _ => True ⦄ := by
  rw [slot.c_greedy_choice]
  step*
  repeat' (split <;> step*)
  all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))

@[local step]
theorem c_load_model_loop0_spec (models : alloc.vec.Vec Std.U32) (lit_c len_c) (base i : Std.Usize) (hb : base.val + slot.C_MS.val ≤ models.length) :
    slot.c_load_model_loop0 models lit_c len_c base i ⦃ fun _ => True ⦄ := by
  rw [slot.c_load_model_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (lit_c_, len_c_, i_) => 256 - i_.val)
    (inv := fun _ => True)
  · rintro ⟨lit_c_, len_c_, i_⟩ _
    simp only [slot.c_load_model_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · trivial

@[local step]
theorem c_load_model_loop1_spec (models : alloc.vec.Vec Std.U32) (dst_c) (base d : Std.Usize) (hb : base.val + slot.C_MS.val ≤ models.length) :
    slot.c_load_model_loop1 models dst_c base d ⦃ fun _ => True ⦄ := by
  rw [slot.c_load_model_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (dst_c_, d_) => 32 - d_.val)
    (inv := fun _ => True)
  · rintro ⟨dst_c_, d_⟩ _
    simp only [slot.c_load_model_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · trivial

@[local step]
theorem c_load_model_spec (models) (b : Std.Usize) (lit_c len_c dst_c) (hb : b.val ≤ 1048576) :
    slot.c_load_model models b lit_c len_c dst_c ⦃ fun _ => True ⦄ := by
  rw [slot.c_load_model]
  step*
  repeat' (split <;> step*)
  all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))

@[local step]
theorem c_group_start_spec (clist ge) :
    slot.c_group_start clist ge ⦃ fun r => r.val ≤ ge.val ⦄ := by
  rw [slot.c_group_start]
  step*
  repeat' (split <;> step*)
  all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))

@[local step]
theorem c_dp_pass_loop0_loop0_spec (bstart : alloc.vec.Vec Std.U32) (b q : Std.Usize) (hb : b.val < bstart.length) :
    slot.c_dp_pass_loop0_loop0 bstart b q ⦃ fun r => r.val ≤ b.val ⦄ := by
  rw [slot.c_dp_pass_loop0_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun b' => b'.val)
    (inv := fun b' => b'.val ≤ b.val)
  · rintro b' hb'
    simp only [slot.c_dp_pass_loop0_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · exact le_refl _

@[local step]
theorem c_dp_pass_loop0_loop1_spec (s : Slice Std.U8) (choice : Slice Std.U32) (ring lit_c next) (p lo : Std.Usize)
    (hp : p.val ≤ s.length) (hc : s.length ≤ choice.length) :
    slot.c_dp_pass_loop0_loop1 s choice ring lit_c next p lo ⦃ fun r => r.1.length = choice.length ∧ r.2.2.2.val ≤ p.val ⦄ := by
  rw [slot.c_dp_pass_loop0_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, p') => p'.val)
    (inv := fun (c', _, _, p') => c'.length = choice.length ∧ p'.val ≤ p.val)
  · rintro ⟨c', r', n', p'⟩ ⟨h1, h2⟩
    simp only [slot.c_dp_pass_loop0_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · exact ⟨rfl, le_refl _⟩

@[local step]
theorem c_dp_pass_loop0_loop2_loop0_spec (ring len_c) (p : Std.Usize) (best ch) (l : Std.Usize) (dc tag) (len : Std.Usize)
    (hp : p.val ≤ 2 ^ 30) (hl : l.val ≤ 511) (hlen : 3 ≤ len.val) :
    slot.c_dp_pass_loop0_loop2_loop0 ring len_c p best ch l dc tag len ⦃ fun _ => True ⦄ := by
  rw [slot.c_dp_pass_loop0_loop2_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, len') => l.val + 1 - len'.val)
    (inv := fun (_, _, len') => 3 ≤ len'.val)
  · rintro ⟨b', c', len'⟩ h1
    simp only [slot.c_dp_pass_loop0_loop2_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · exact hlen

@[local step]
theorem c_dp_pass_loop0_loop2_spec (clist ring len_c dst_c) (ge p : Std.Usize) (best ch) (prev room k : Std.Usize)
    (hp : p.val ≤ 2 ^ 30) (hprev : 2 ≤ prev.val ∧ prev.val ≤ 511)
    (hk : k.val ≤ clist.length) (hcl : clist.length < 4294967295) :
    slot.c_dp_pass_loop0_loop2 clist ring len_c dst_c ge p best ch prev room k ⦃ fun _ => True ⦄ := by
  rw [slot.c_dp_pass_loop0_loop2]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, k') => clist.length - k'.val)
    (inv := fun (_, _, prev', k') => 2 ≤ prev'.val ∧ prev'.val ≤ 511 ∧ k'.val ≤ clist.length)
  · rintro ⟨b', c', prev', k'⟩ ⟨h1, h2, h3⟩
    simp only [slot.c_dp_pass_loop0_loop2.body]
    step*
    apply WP.spec_bind (Pₘ := fun (x : Std.Usize) => 2 ≤ x.val ∧ x.val ≤ 511)
    · repeat' (split <;> step*)
      all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
    rintro prev1 ⟨hq1, hq2⟩
    step*
    apply WP.spec_bind (Pₘ := fun (x : Std.Usize) => x.val ≤ 511)
    · split <;> step*
      all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
    rintro l1 hl1
    step*
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · exact ⟨hprev.1, hprev.2, hk⟩

@[local step]
theorem c_dp_pass_loop0_spec (s : Slice Std.U8) (clist models : alloc.vec.Vec Std.U32) (bstart : alloc.vec.Vec Std.U32) (choice : Slice Std.U32)
    (n : Std.Usize) (ring lit_c len_c dst_c) (b loaded ge gs gp : Std.Usize) (next) (p fuel : Std.Usize)
    (hn : n.val = s.length) (hn26 : n.val < 67108864) (hc : n.val ≤ choice.length) (hb : b.val < bstart.length)
    (hnb : bstart.length ≤ 1048576) (hp : p.val ≤ n.val) (hgp : gp.val ≤ n.val ∨ gp.val < 2 ^ 27)
    (hcl : clist.length < 4294967295) (hgs : gs.val ≤ ge.val) (hge : ge.val ≤ clist.length) :
    slot.c_dp_pass_loop0 s clist models bstart choice n ring lit_c len_c dst_c b loaded ge gs gp next p fuel ⦃ fun _ => True ⦄ := by
  have hpm := C_PMASK_lt
  rw [slot.c_dp_pass_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, _, _, _, _, _, _, _, _, f) => f.val)
    (inv := fun (c', _, _, _, _, b', _, ge', gs', gp', _, p', _) => c'.length = choice.length ∧
      b'.val < bstart.length ∧ p'.val ≤ n.val ∧ (gp'.val ≤ n.val ∨ gp'.val < 2 ^ 27) ∧
      gs'.val ≤ ge'.val ∧ ge'.val ≤ clist.length)
  · rintro ⟨c', r', l1', l2', d', b', ld', ge', gs', gp', nx', p', f'⟩ ⟨h1, h2, h3, h4, h5, h6⟩
    simp only [slot.c_dp_pass_loop0.body]
    step*
    apply WP.spec_bind (Pₘ := fun _ => True)
    · split <;> step*
    rintro ⟨lit_c1, len_c1, dst_c1, loaded1⟩ _
    step*
    apply WP.spec_bind (Pₘ := fun _ => True)
    · repeat' (split <;> step*)
    rintro lo _
    step*
    apply WP.spec_bind (Pₘ := fun _ => True)
    · split <;> step*
    rintro ⟨best1, ch1⟩ _
    step*
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · exact ⟨rfl, hb, hp, hgp, hgs, hge⟩

@[local step]
theorem c_dp_pass_spec (s : Slice Std.U8) (clist models) (bstart : alloc.vec.Vec Std.U32) (choice)
    (hn26 : s.length < 67108864) (hnb : bstart.length ≤ 1048576) (hcl : clist.length < 4294967295) :
    slot.c_dp_pass s clist models bstart choice ⦃ fun _ => True ⦄ := by
  have hms := C_MS_val
  have hpm := C_PMASK_lt
  rw [slot.c_dp_pass]
  step*
  repeat' (split <;> step*)
  all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))

@[local step]
theorem c_pack_spec (len) (d : Std.Usize) (hd : 1 ≤ d.val) : slot.c_pack len d ⦃ fun _ => True ⦄ := by
  rw [slot.c_pack]
  step*
  repeat' (split <;> step*)
  all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))

@[local step]
theorem c_push_cands_loop_spec (clist : alloc.vec.Vec Std.U32) (ml md) (cnt : Std.Usize) (flag) (top : Std.Usize)
    (pushed : Std.U32) (i : Std.Usize)
    (hcl : clist.length + (cnt.val - i.val) < 4294967295) (hpu : pushed.val ≤ 1) :
    slot.c_push_cands_loop clist ml md cnt flag top pushed i ⦃ fun r =>
      r.1.length ≤ clist.length + (cnt.val - i.val) ∧ r.2.2.val ≤ pushed.val + (cnt.val - i.val) ∧
      (top.val ≤ 258 → r.2.1.val ≤ 258) ⦄ := by
  rw [slot.c_push_cands_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, i') => 64 - i'.val)
    (inv := fun (c', t', u', i') => c'.length + (cnt.val - i'.val) ≤ clist.length + (cnt.val - i.val) ∧
      u'.val + (cnt.val - i'.val) ≤ pushed.val + (cnt.val - i.val) ∧ i.val ≤ i'.val ∧
      (top.val ≤ 258 → t'.val ≤ 258))
  · rintro ⟨c', t', u', i'⟩ ⟨h1, h2, h3, h4⟩
    simp only [slot.c_push_cands_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · exact ⟨le_refl _, le_refl _, le_refl _, fun h => h⟩

@[local step]
theorem c_push_cands_spec (clist : alloc.vec.Vec Std.U32) (p ml md cnt r1 flag)
    (hcl : clist.length + slot.C_KEEP.val + 2 < 4294967295) :
    slot.c_push_cands clist p ml md cnt r1 flag ⦃ fun r => r.2.length ≤ clist.length + slot.C_KEEP.val + 2 ∧
      r.1.val ≤ 258 ⦄ := by
  rw [slot.c_push_cands]
  step*
  repeat' (split <;> step*)
  all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))

@[local step]
theorem c_nt_code_spec (b) :
    slot.c_nt_code b ⦃ fun _ => True ⦄ := by
  rw [slot.c_nt_code]
  step*
  repeat' (split <;> step*)
  all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))

@[local step]
theorem c_word_be_spec (s) (i : Std.Usize) (hi : i.val + 8 ≤ Usize.max) : slot.c_word_be s i ⦃ fun _ => True ⦄ := by
  rw [slot.c_word_be]
  step*
  repeat' (split <;> step*)
  all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))

@[local step]
theorem c_extend_loop0_loop0_spec (s : Slice Std.U8) (a b lim k : Std.Usize) (ha : a.val + lim.val ≤ s.length) (hb : b.val + lim.val ≤ s.length) :
    slot.c_extend_loop0_loop0 s a b lim k ⦃ fun _ => True ⦄ := by
  rw [slot.c_extend_loop0_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun k_ => lim.val - k_.val)
    (inv := fun _ => True)
  · rintro k_ _
    simp only [slot.c_extend_loop0_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · trivial

@[local step]
theorem c_extend_loop0_loop1_spec (s : Slice Std.U8) (a b lim k : Std.Usize) (ha : a.val + lim.val ≤ s.length) (hb : b.val + lim.val ≤ s.length) :
    slot.c_extend_loop0_loop1 s a b lim k ⦃ fun _ => True ⦄ := by
  rw [slot.c_extend_loop0_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun k_ => lim.val - k_.val)
    (inv := fun _ => True)
  · rintro k_ _
    simp only [slot.c_extend_loop0_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · trivial

@[local step]
theorem c_extend_loop0_spec (s : Slice Std.U8) (a b lim k fuel : Std.Usize) (ha : a.val + lim.val ≤ s.length)
    (hb : b.val + lim.val ≤ s.length) (hk : k.val ≤ 2 ^ 31) (hlim : lim.val ≤ 2 ^ 31) :
    slot.c_extend_loop0 s a b lim k fuel ⦃ fun _ => True ⦄ := by
  rw [slot.c_extend_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, f') => f'.val)
    (inv := fun (k', _) => k'.val ≤ 2 ^ 31)
  · rintro ⟨k', f'⟩ hk'
    simp only [slot.c_extend_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · exact hk

@[local step]
theorem c_extend_spec (s : Slice Std.U8) (a b k0 lim : Std.Usize) (ha : a.val + lim.val ≤ s.length) (hb : b.val + lim.val ≤ s.length)
    (hk0 : k0.val ≤ 2 ^ 31) (hlim : lim.val ≤ 2 ^ 31) :
    slot.c_extend s a b k0 lim ⦃ fun _ => True ⦄ := by
  rw [slot.c_extend]
  step*
  repeat' (split <;> step*)
  all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))

@[local step]
theorem c_chain_walk_loop_spec (s : Slice Std.U8) (p k0 depth : Std.Usize) (prev ml md) (lim cur best cnt steps : Std.Usize)
    (hp : p.val + lim.val ≤ s.length) (hlim : lim.val ≤ 258) (hk0 : k0.val ≤ 2 ^ 31) :
    slot.c_chain_walk_loop s p k0 depth prev ml md lim cur best cnt steps ⦃ fun _ => True ⦄ := by
  have hws := C_WS_val
  rw [slot.c_chain_walk_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, _, st) => depth.val - st.val)
    (inv := fun _ => True)
  · rintro ⟨ml', md', cur', best', cnt', st'⟩ _
    simp only [slot.c_chain_walk_loop.body]
    step*
    apply WP.spec_bind (Pₘ := fun _ => True)
    · repeat' (split <;> step*)
      all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
    rintro ⟨ml1, md1, best1, cnt1⟩ _
    step*
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · trivial

@[local step]
theorem c_chain_walk_spec (s : Slice Std.U8) (p key k0 best0 depth head prev ml md) (hp : p.val < s.length) (hk0 : k0.val ≤ 2 ^ 31) :
    slot.c_chain_walk s p key k0 best0 depth head prev ml md ⦃ fun _ => True ⦄ := by
  have hws := C_WS_val
  have hhs := C_HS_bounds
  rw [slot.c_chain_walk]
  step*
  repeat' (split <;> step*)
  all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))

@[local step]
theorem c_put_kid_spec (kids) (which : Std.Usize) (idx v) (hw : which.val ≤ 1) :
    slot.c_put_kid kids which idx v ⦃ fun _ => True ⦄ := by
  have hws := C_WS_val
  have hks := C_KS_val
  rw [slot.c_put_kid]
  step*
  repeat' (split <;> step*)
  all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))

@[local step]
theorem c_bt_find_loop_spec (back) (s : Slice Std.U8) (p depth kids ml md) (lim cur lw li gw gi llen glen : Std.Usize)
    (best cnt steps i)
    (hp : p.val + lim.val ≤ s.length) (hlim : lim.val ≤ 258) (hlw : lw.val ≤ 1) (hgw : gw.val ≤ 1)
    (hll : llen.val ≤ lim.val) (hgl : glen.val ≤ lim.val) :
    slot.c_bt_find_loop back s p depth kids ml md lim cur lw li gw gi llen glen best cnt steps i ⦃ fun _ => True ⦄ := by
  have hws := C_WS_val
  have hks := C_KS_val
  rw [slot.c_bt_find_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, _, _, _, _, _, _, _, _, st) => depth.val - st.val)
    (inv := fun (_, _, _, _, lw', _, gw', _, ll', gl', _, _, _) => lw'.val ≤ 1 ∧ gw'.val ≤ 1 ∧
      ll'.val ≤ lim.val ∧ gl'.val ≤ lim.val)
  · rintro ⟨kids', ml', md', cur', lw', li', gw', gi', ll', gl', best', cnt', st'⟩ ⟨h1, h2, h3, h4⟩
    simp only [slot.c_bt_find_loop.body]
    step*
    apply WP.spec_bind (Pₘ := fun (x : Std.Usize) => x.val ≤ lim.val)
    · split <;> step*
      all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
    rintro k0 hk0
    step*
    apply WP.spec_bind (Pₘ := fun _ => True)
    · repeat' (split <;> step*)
      all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
    rintro ⟨ml1, md1, best1, cnt1⟩ _
    step*
    apply WP.spec_bind (Pₘ := fun (x : Std.Array Std.U32 65536#usize × Std.Usize × Std.Usize × Std.Usize ×
        Std.Usize × Std.Usize × Std.Usize × Std.Usize) =>
      x.2.2.1.val ≤ 1 ∧ x.2.2.2.2.1.val ≤ 1 ∧ x.2.2.2.2.2.2.1.val ≤ lim.val ∧ x.2.2.2.2.2.2.2.val ≤ lim.val)
    · split <;> step*
      all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
    rintro ⟨kids1, cur1, lw1, li1, gw1, gi1, llen1, glen1⟩ ⟨h5, h6, h7, h8⟩
    step*
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · exact ⟨hlw, hgw, hll, hgl⟩

@[local step]
theorem c_bt_find_spec (s : Slice Std.U8) (p h depth head kids ml md) (hp : p.val < s.length) :
    slot.c_bt_find s p h depth head kids ml md ⦃ fun _ => True ⦄ := by
  have hws := C_WS_val
  have hhs := C_HS_bounds
  rw [slot.c_bt_find]
  step*
  repeat' (split <;> step*)
  all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))

@[local step]
theorem c_find_dna_loop0_spec (s : Slice Std.U8) (n key : Std.Usize) (run run2 q : Std.Usize) (hn : n.val = s.length)
    (hrun : run.val ≤ q.val) (hrun2 : run2.val ≤ q.val) (hq : q.val ≤ 7) :
    slot.c_find_dna_loop0 s n key run run2 q ⦃ fun r => r.2.1.val ≤ 7 ∧ r.2.2.val ≤ 7 ⦄ := by
  rw [slot.c_find_dna_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, q') => 7 - q'.val)
    (inv := fun (_, r1, r2, q') => r1.val ≤ q'.val ∧ r2.val ≤ q'.val ∧ q'.val ≤ 7)
  · rintro ⟨k', r1, r2, q'⟩ ⟨h1, h2, h3⟩
    simp only [slot.c_find_dna_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · exact ⟨hrun, hrun2, hq⟩

@[local step]
theorem c_find_dna_loop1_spec (s : Slice Std.U8) (clist) (depth_lo n : Std.Usize) (head8 prev8 head3 kids ml md)
    (key run run2 p skip_to : Std.Usize)
    (hn : n.val = s.length) (hn26 : n.val < 67108864) (hrun : run.val ≤ p.val + 7) (hrun2 : run2.val ≤ p.val + 7)
    (hp : p.val ≤ n.val) (hcl : clist.length ≤ 34 * p.val) :
    slot.c_find_dna_loop1 s clist depth_lo n head8 prev8 head3 kids ml md key run run2 p skip_to ⦃ fun r =>
      r.length ≤ 34 * n.val ⦄ := by
  have hws := C_WS_val
  have hhs := C_HS_bounds
  have hkp := C_KEEP_le
  have hup := C_UP_MIN_ge
  rw [slot.c_find_dna_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, _, _, _, _, _, _, p', _) => n.val - p'.val)
    (inv := fun (c', _, _, _, _, _, _, _, r1, r2, p', _) => r1.val ≤ p'.val + 7 ∧ r2.val ≤ p'.val + 7 ∧
      p'.val ≤ n.val ∧ c'.length ≤ 34 * p'.val)
  · rintro ⟨c', h8', pv8', h3', kids', ml', md', key', r1, r2, p', sk'⟩ ⟨h1, h2, h3, h4⟩
    unfold slot.c_find_dna_loop1.body
    step*

    apply WP.spec_bind (Pₘ := fun (x : Std.Usize × Std.Usize × Std.Usize) =>
      x.2.1.val ≤ p'.val + 8 ∧ x.2.2.val ≤ p'.val + 8)
    · repeat' (split <;> step*)
      all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
    rintro ⟨key1, run1, run21⟩ ⟨hr1, hr2⟩
    step*

    apply WP.spec_bind (Pₘ := fun (x : alloc.vec.Vec Std.U32 × Std.Array Std.U32 65536#usize ×
        Std.Array Std.U32 32768#usize × Std.Array Std.U32 65536#usize × Std.Array Std.U32 65536#usize ×
        Std.Array Std.U32 64#usize × Std.Array Std.U32 64#usize × Std.Usize) =>
      x.1.length ≤ c'.length + 34)
    · apply engC_ite_spec
      · intro hc
        step*
        ·
          apply WP.spec_bind (Pₘ := fun (x : alloc.vec.Vec Std.U32 × _) => x.1.length ≤ c'.length + 34)
          · apply engC_ite_spec
            · intro hs
              step*
              apply WP.spec_bind (Pₘ := fun (x : alloc.vec.Vec Std.U32 × _) => x.1.length ≤ c'.length + 34)
              · apply engC_ite_spec
                · intro hcnt
                  step*
                  apply engC_bind_ite_spec <;> intro _ <;> step*
                · intro hcnt
                  step*
              · rintro ⟨v2, a4, a5, i17⟩ hv2
                step*
            · intro hs
              step*
          · rintro ⟨v1, a, a1, a2, a3, i16⟩ hv1
            step*
        ·
          apply WP.spec_bind (Pₘ := fun (x : alloc.vec.Vec Std.U32 × _) => x.1.length ≤ c'.length + 34)
          · apply engC_ite_spec
            ·
              intro hr
              apply WP.spec_bind (Pₘ := fun (x : alloc.vec.Vec Std.U32 × _) => x.1.length ≤ c'.length + 34)
              · apply engC_ite_spec
                · intro hs
                  step*
                  apply WP.spec_bind (Pₘ := fun (x : alloc.vec.Vec Std.U32 × _) => x.1.length ≤ c'.length + 34)
                  · apply engC_ite_spec
                    · intro hcnt
                      step*
                      apply engC_bind_ite_spec <;> intro _ <;> step*
                    · intro hcnt
                      step*
                  · rintro ⟨v2, a9, a10, i5⟩ hv2
                    step*
                · intro hs
                  step*
              · rintro ⟨v1, a5, a6, a7, a8, i3⟩ hv1
                step*
            ·
              intro hr
              apply WP.spec_bind (Pₘ := fun (x : alloc.vec.Vec Std.U32 × _) => x.1.length ≤ c'.length + 34)
              · apply engC_ite_spec
                · intro hr2
                  step*
                  apply WP.spec_bind (Pₘ := fun (x : alloc.vec.Vec Std.U32 × _) => x.1.length ≤ c'.length + 34)
                  · apply engC_ite_spec
                    · intro hcnt
                      step*
                      apply engC_bind_ite_spec <;> intro _ <;> step*
                    · intro hcnt
                      step*
                  · rintro ⟨v2, a9, a10, i10⟩ hv2
                    step*
                · intro hr2
                  step*
              · rintro ⟨v1, a5, a6, a7, a8, i3⟩ hv1
                step*
          · rintro ⟨v, a, a1, a2, a3, a4, i2⟩ hv
            step*
        ·
          apply WP.spec_bind (Pₘ := fun (x : alloc.vec.Vec Std.U32 × _) => x.1.length ≤ c'.length + 34)
          · apply engC_ite_spec
            ·
              intro hr
              apply WP.spec_bind (Pₘ := fun (x : alloc.vec.Vec Std.U32 × _) => x.1.length ≤ c'.length + 34)
              · apply engC_ite_spec
                · intro hs
                  step*
                  apply WP.spec_bind (Pₘ := fun (x : alloc.vec.Vec Std.U32 × _) => x.1.length ≤ c'.length + 34)
                  · apply engC_ite_spec
                    · intro hcnt
                      step*
                      apply engC_bind_ite_spec <;> intro _ <;> step*
                    · intro hcnt
                      step*
                  · rintro ⟨v2, a9, a10, i5⟩ hv2
                    step*
                · intro hs
                  step*
              · rintro ⟨v1, a5, a6, a7, a8, i3⟩ hv1
                step*
            ·
              intro hr
              apply WP.spec_bind (Pₘ := fun (x : alloc.vec.Vec Std.U32 × _) => x.1.length ≤ c'.length + 34)
              · apply engC_ite_spec
                · intro hr2
                  step*
                  apply WP.spec_bind (Pₘ := fun (x : alloc.vec.Vec Std.U32 × _) => x.1.length ≤ c'.length + 34)
                  · apply engC_ite_spec
                    · intro hcnt
                      step*
                      apply engC_bind_ite_spec <;> intro _ <;> step*
                    · intro hcnt
                      step*
                  · rintro ⟨v2, a9, a10, i10⟩ hv2
                    step*
                · intro hr2
                  step*
              · rintro ⟨v1, a5, a6, a7, a8, i3⟩ hv1
                step*
          · rintro ⟨v, a, a1, a2, a3, a4, i2⟩ hv
            step*
      · intro hc
        step*
    rintro ⟨clist1, head81, prev81, head31, kids1, ml1, md1, skip_to1⟩ hc1
    step*
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · exact ⟨hrun, hrun2, hp, hcl⟩

@[local step]
theorem c_find_dna_spec (s : Slice Std.U8) (clist) (depth_lo) (hn26 : s.length < 67108864) (hcl : clist.length = 0) :
    slot.c_find_dna s clist depth_lo ⦃ fun r => r.length ≤ 34 * s.length ⦄ := by
  rw [slot.c_find_dna]
  step*

@[local step]
theorem c_run_len_spec (s : Slice Std.U8) (p : Std.Usize) (hp : p.val ≤ 2 ^ 31) : slot.c_run_len s p ⦃ fun _ => True ⦄ := by
  rw [slot.c_run_len]
  step*
  repeat' (split <;> step*)
  all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))

@[local step]
theorem c_find_bin_loop_spec (s : Slice Std.U8) (clist) (chain depth n : Std.Usize) (head lt kids ml md)
    (p skip_to pend : Std.Usize)
    (hn : n.val = s.length) (hn26 : n.val < 67108864) (hp : p.val ≤ n.val) (hcl : clist.length ≤ 34 * p.val) :
    slot.c_find_bin_loop s clist chain depth n head lt kids ml md p skip_to pend ⦃ fun r => r.length ≤ 34 * n.val ⦄ := by
  have hws := C_WS_val
  have hhs := C_HS_bounds
  have hkp := C_KEEP_le
  rw [slot.c_find_bin_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, _, _, p', _, _) => n.val - p'.val)
    (inv := fun (c', _, _, _, _, _, p', _, _) => p'.val ≤ n.val ∧ c'.length ≤ 34 * p'.val)
  · rintro ⟨c', hd', lt', kids', ml', md', p', sk', pe'⟩ ⟨h1, h2⟩
    unfold slot.c_find_bin_loop.body
    step*
    apply WP.spec_bind (Pₘ := fun _ => True)
    · split <;> step*
    rintro key _
    step*
    apply WP.spec_bind (Pₘ := fun (x : alloc.vec.Vec Std.U32 × Std.Array Std.U32 65536#usize ×
        Std.Array Std.U32 32768#usize × Std.Array Std.U32 65536#usize × Std.Array Std.U32 64#usize ×
        Std.Array Std.U32 64#usize × Std.Usize × Std.Usize) =>
      x.1.length ≤ c'.length + 34)
    · split
      ·
        step*
        apply WP.spec_bind (Pₘ := fun _ => True)
        · split <;> step*
        rintro ⟨head2, lt2, kids2, ml2, md2, cnt⟩ _
        step*
        apply WP.spec_bind (Pₘ := fun _ => True)
        · repeat' (split <;> step*)
        rintro r1 _
        step*
        apply WP.spec_bind (Pₘ := fun (x : alloc.vec.Vec Std.U32 × Std.Usize) =>
          x.1.length ≤ c'.length + 34 ∧ x.2.val ≤ 258)
        · repeat' (split <;> step*)
          all_goals scalar_tac
        rintro ⟨clist2, top⟩ ⟨hc2, htop⟩
        step*
        apply WP.spec_bind (Pₘ := fun _ => True)
        · repeat' (split <;> step*)
          all_goals scalar_tac
        rintro ⟨i19, i20⟩ _
        step*
      ·
        step*
        apply WP.spec_bind (Pₘ := fun _ => True)
        · split <;> step*
        rintro ⟨a, a1⟩ _
        step*
    rintro ⟨clist1, head1, lt1, kids1, ml1, md1, skip_to1, pend1⟩ hc1
    step*
    all_goals scalar_tac
  · exact ⟨hp, hcl⟩

@[local step]
theorem c_find_bin_spec (s : Slice Std.U8) (clist chain depth) (hn26 : s.length < 67108864) (hcl : clist.length = 0) :
    slot.c_find_bin s clist chain depth ⦃ fun r => r.length ≤ 34 * s.length ⦄ := by
  rw [slot.c_find_bin]
  step*

@[local step]
theorem c_engine_loop0_spec (input : Slice Std.U8) (out min_dna dna) (clist : alloc.vec.Vec Std.U32) (models)
    (bstart : alloc.vec.Vec Std.U32) (passes) (tax tokpen : Std.U32) (last_est pass)
    (hn26 : input.length < 67108864) (htax : tax.val ≤ 65536) (htok : tokpen.val ≤ 65536)
    (hnb : bstart.length ≤ 1048576) (hcl : clist.length < 4294967295) :
    slot.c_engine_loop0 input out min_dna dna clist models bstart passes tax tokpen last_est pass ⦃ fun _ => True ⦄ := by
  have h1 := C_UNUSED_LEN_le
  have h2 := C_UNUSED_DIST_le
  have h3 := C_STOP_DIV_pos
  rw [slot.c_engine_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, pass') => passes.val - pass'.val)
    (inv := fun (_, _, b', _, _) => b'.length ≤ 1048576)
  · rintro ⟨out', models', b', le', pass'⟩ hb'
    simp only [slot.c_engine_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · exact hnb

@[local step]
theorem c_engine_loop1_spec (input : Slice Std.U8) (out min_dna dna) (clist : alloc.vec.Vec Std.U32) (models)
    (bstart : alloc.vec.Vec Std.U32) (passes) (tax tokpen : Std.U32) (last_est pass)
    (hn26 : input.length < 67108864) (htax : tax.val ≤ 65536) (htok : tokpen.val ≤ 65536)
    (hnb : bstart.length ≤ 1048576) (hcl : clist.length < 4294967295) :
    slot.c_engine_loop1 input out min_dna dna clist models bstart passes tax tokpen last_est pass ⦃ fun _ => True ⦄ := by
  have h1 := C_UNUSED_LEN_le
  have h2 := C_UNUSED_DIST_le
  have h3 := C_STOP_DIV_pos
  rw [slot.c_engine_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, pass') => passes.val - pass'.val)
    (inv := fun (_, _, b', _, _) => b'.length ≤ 1048576)
  · rintro ⟨out', models', b', le', pass'⟩ hb'
    simp only [slot.c_engine_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · exact hnb

@[local step]
theorem c_engine_loop2_spec (input : Slice Std.U8) (out min_dna dna) (clist : alloc.vec.Vec Std.U32) (models)
    (bstart : alloc.vec.Vec Std.U32) (passes) (tax tokpen : Std.U32) (last_est pass)
    (hn26 : input.length < 67108864) (htax : tax.val ≤ 65536) (htok : tokpen.val ≤ 65536)
    (hnb : bstart.length ≤ 1048576) (hcl : clist.length < 4294967295) :
    slot.c_engine_loop2 input out min_dna dna clist models bstart passes tax tokpen last_est pass ⦃ fun _ => True ⦄ := by
  have h1 := C_UNUSED_LEN_le
  have h2 := C_UNUSED_DIST_le
  have h3 := C_STOP_DIV_pos
  rw [slot.c_engine_loop2]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, pass') => passes.val - pass'.val)
    (inv := fun (_, _, b', _, _) => b'.length ≤ 1048576)
  · rintro ⟨out', models', b', le', pass'⟩ hb'
    simp only [slot.c_engine_loop2.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · exact hnb

@[local step]
theorem c_engine_spec (input : Slice Std.U8) (out) (depth depth_lo wdp passes_w passes_bt passes_dna min_dna passes_c4 : Std.Usize)
    (hn : input.length < 67108864) (h1 : depth.val ≤ 65536) (h2 : depth_lo.val ≤ 65536) (h3 : wdp.val ≤ 65536)
    (h4 : passes_w.val ≤ 65536) (h5 : passes_bt.val ≤ 65536) (h6 : passes_dna.val ≤ 65536) (h7 : min_dna.val ≤ 65536)
    (h8 : passes_c4.val ≤ 65536) :
    slot.c_engine input out depth depth_lo wdp passes_w passes_bt passes_dna min_dna passes_c4 ⦃ fun _ => True ⦄ := by
  have f1 := C_TAX_W_le
  have f2 := C_TAX_C4_le
  have f3 := C_TAX_BT_le
  have f4 := C_UNUSED_LEN_W_le
  have f5 := C_UNUSED_DIST_W_le
  have f6 := C_TOKPEN_le
  have f7 := C_TOKPEN_W_le
  have f8 := C_TOKPEN_C4_le
  have f9 := C_TOKPEN_BT_le
  have f10 := C_UNUSED_LEN_le
  have f11 := C_UNUSED_DIST_le
  have f12 := C_CHAIN4_RATIO_le
  rw [slot.c_engine]
  step*

  all_goals
    first
      | apply WP.spec_bind (Pₘ := fun (x : alloc.vec.Vec Std.U32) => x.length ≤ 34 * input.length)
        · repeat' (split <;> step*)
          all_goals exact engC_with_capacity_length _
        rintro clist1 hc1
        apply WP.spec_bind (Pₘ := fun _ => True)
        · repeat' (split <;> step*)
        rintro passes _
        apply WP.spec_bind (Pₘ := fun (x : Std.U32) => x.val ≤ 65536)
        · repeat' (split <;> step*)
          all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
        rintro tax htax
        apply WP.spec_bind (Pₘ := fun (x : Std.U32) => x.val ≤ 65536)
        · repeat' (split <;> step*)
          all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
        rintro ulen hulen
        apply WP.spec_bind (Pₘ := fun (x : Std.U32) => x.val ≤ 65536)
        · repeat' (split <;> step*)
          all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
        rintro udist hudist
        apply WP.spec_bind (Pₘ := fun _ => True)
        · repeat' (split <;> step*)
        rintro gmin _
        step*
        apply WP.spec_bind (Pₘ := fun (x : alloc.vec.Vec Std.U32 × Std.U32) => x.2.val ≤ 65536)
        · repeat' (split <;> step*)
          all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
        rintro ⟨out1, tokpen⟩ htok
        step*
        repeat' (split <;> step*)
        all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
      | apply WP.spec_bind (Pₘ := fun _ => True)
        · repeat' (split <;> step*)
          all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
        rintro chain4 _
        step*
        apply WP.spec_bind (Pₘ := fun (x : alloc.vec.Vec Std.U32) => x.length ≤ 34 * input.length)
        · repeat' (split <;> step*)
          all_goals exact engC_with_capacity_length _
        rintro clist1 hc1
        apply WP.spec_bind (Pₘ := fun _ => True)
        · repeat' (split <;> step*)
        rintro passes _
        apply WP.spec_bind (Pₘ := fun (x : Std.U32) => x.val ≤ 65536)
        · repeat' (split <;> step*)
          all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
        rintro tax htax
        apply WP.spec_bind (Pₘ := fun (x : Std.U32) => x.val ≤ 65536)
        · repeat' (split <;> step*)
          all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
        rintro ulen hulen
        apply WP.spec_bind (Pₘ := fun (x : Std.U32) => x.val ≤ 65536)
        · repeat' (split <;> step*)
          all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
        rintro udist hudist
        apply WP.spec_bind (Pₘ := fun _ => True)
        · repeat' (split <;> step*)
        rintro gmin _
        step*
        apply WP.spec_bind (Pₘ := fun (x : alloc.vec.Vec Std.U32 × Std.U32) => x.2.val ≤ 65536)
        · repeat' (split <;> step*)
          all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
        rintro ⟨out1, tokpen⟩ htok
        step*
        repeat' (split <;> step*)
        all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))

theorem spine_CFG_le : ∀ r ∈ slot.CFG.val, ∀ x ∈ r.val, x.val ≤ 65536 := by
  unfold slot.CFG; decide

theorem spine_knob_le {m : Std.Usize} {r : Array Std.Usize m} (hr : ∀ x ∈ r.val, x.val ≤ 65536)
    {x : Std.Usize} {j : Nat} {hj : j < r.val.length} (hx : x = r.val[j]) : x.val ≤ 65536 := by
  subst hx; exact hr _ (List.getElem_mem _)

@[local step]
theorem plan_cfg_spec (input : Slice Std.U8) (k) (hn : input.length < 67108864) :
    slot.plan_cfg input k ⦃ fun _ => True ⦄ := by
  rw [slot.plan_cfg]
  step*

  all_goals
    have hc : c ∈ slot.CFG.val := by rw [c_post]; exact List.getElem_mem _
    exact spine_knob_le (spine_CFG_le c hc) (by assumption)

@[local step]
theorem s_plan_spec (input : Slice Std.U8) (k : Std.Usize) : slot.s_plan input k ⦃ fun _ => True ⦄ := by
  rw [slot.s_plan]
  step*

theorem parse_spec (input : Slice Std.U8) (out : Slice Std.U32)
    (hlen : input.length ≤ out.length) :
    slot.parse input out ⦃ fun r =>
      r.1.val ≤ input.length ∧
      r.2.length = out.length ∧
      LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
  rw [slot.parse]
  step*
  all_goals (first | assumption | (subst_vars; scalar_tac (simpAllMaxSteps := 0)) |
    (refine ⟨by assumption, by assumption, ?_⟩; unfold LZ77.Valid; assumption) |
    (refine ⟨by assumption, by (subst_vars; scalar_tac (simpAllMaxSteps := 0)), ?_⟩; unfold LZ77.Valid; assumption))

end Submission
