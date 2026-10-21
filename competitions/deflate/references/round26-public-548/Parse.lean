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

set_option hygiene false in
local notation "SV0!" => (by subst_vars; scalar_tac (simpAllMaxSteps := 0))
local notation "SDN!" => Std.loop.spec_decr_nat
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

theorem BLOCK_TOKENS_bounds : 0 < slot.BLOCK_TOKENS.val ∧ slot.BLOCK_TOKENS.val ≤ 65536 := by
  simp [slot.BLOCK_TOKENS]

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
  have : c.val < 2 ^ 32 := by exact SV0!
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
  apply SDN!
    (measure := fun (k', run') => cap.val + 9 - k'.val + run'.val)
    (inv := fun (k', _) => k'.val ≤ cap.val)
  · rintro ⟨k', run'⟩ hk'
    simp only [slot.common_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals try (have := lz64_bound x)
    all_goals exact SV0!
  · exact hk

@[local step]
theorem common_loop1_spec (s : Slice Std.U8) (a b cap k : Std.Usize) (run : Std.U32)
    (ha : a.val + cap.val + 8 ≤ Std.Usize.max) (hb : b.val + cap.val + 8 ≤ Std.Usize.max) (hk : k.val ≤ cap.val) :
    slot.common_loop1 s a b cap k run ⦃ fun r => r.val ≤ cap.val ⦄ := by
  rw [slot.common_loop1]
  apply SDN!
    (measure := fun (k', run') => cap.val + 1 - k'.val + run'.val)
    (inv := fun (k', _) => k'.val ≤ cap.val)
  · rintro ⟨k', run'⟩ hk'
    simp only [slot.common_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals exact SV0!
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
  all_goals exact SV0!

@[local step]
theorem walk_loop_spec (s : Slice Std.U8) (prev) (i : Std.Usize) (b8 : Std.U64) (cap : Std.Usize)
    (cands) (nc best c k : Std.Usize)
    (hc : c.val ≤ i.val) (hcap : 9 ≤ cap.val) (hic : i.val + cap.val ≤ s.length)
    (hs8 : s.length + 8 ≤ Std.Usize.max) (hb : best.val ≤ cap.val) :
    slot.walk_loop s prev i b8 cap cands nc best c k ⦃ fun r => best.val ≤ r.2.2.val ∧ r.2.2.val ≤ cap.val ⦄ := by
  have hwn := dp_WN_val
  rw [slot.walk_loop]
  apply SDN!
    (measure := fun (_, _, _, _, k') => k'.val)
    (inv := fun (_, _, best', c', _) => c'.val ≤ i.val ∧ best.val ≤ best'.val ∧ best'.val ≤ cap.val)
  · rintro ⟨cands', nc', best', c', k'⟩ ⟨h1, h2, h3⟩
    simp only [slot.walk_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals exact SV0!
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
  all_goals exact SV0!

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
  apply SDN!
    (measure := fun (_, _, _, _, _, q') => e.val - q'.val)
    (inv := fun (h3', h4', _, h7', _, _) => LeAll h3'.val B ∧ LeAll h4'.val B ∧ LeAll h7'.val B)
  · rintro ⟨h3', h4', p4', h7', p7', q'⟩ ⟨i3, i4, i7⟩
    simp only [slot.insert_range_loop.body]
    split
    · step*
      all_goals exact SV0!
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
  apply SDN!
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
theorem back_best_loop_spec (input : Slice Std.U8) (pa lc) (i s len dd t bt : Std.Usize) (bv : Std.U32)
    (hi : i.val < input.length) (hlen : len.val < 512) (hdd : dd.val < 8388608)
    (hN : input.length + 2147483648 ≤ Std.Usize.max)
    (ht : t.val ≤ i.val) (hbt : bt.val ≤ t.val) (ht258 : t.val = 0 ∨ len.val + t.val ≤ 258) :
    slot.back_best_loop input pa lc i s len dd t bt bv ⦃ fun r =>
      r.1.val ≤ i.val ∧ (r.1.val = 0 ∨ len.val + r.1.val ≤ 258) ⦄ := by
  have := dp_RING_val
  rw [slot.back_best_loop]
  apply SDN!
    (measure := fun (t', _, _) => slot.TMAX.val - t'.val)
    (inv := fun (t', bt', _) => t'.val ≤ i.val ∧ bt'.val ≤ t'.val ∧ (t'.val = 0 ∨ len.val + t'.val ≤ 258))
  · rintro ⟨t', bt', bv'⟩ ⟨h1, h2, h3⟩
    simp only [slot.back_best_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals exact SV0!
  · exact ⟨ht, hbt, ht258⟩

@[local step] theorem back_best_spec (input : Slice Std.U8) (pa lc) (i s len dd : Std.Usize)
    (hi : i.val < input.length) (hlen : len.val < 512) (hdd : dd.val < 8388608)
    (hN : input.length + 2147483648 ≤ Std.Usize.max) :
    slot.back_best input pa lc i s len dd ⦃ fun r => r.1.val ≤ i.val ∧ (r.1.val = 0 ∨ len.val + r.1.val ≤ 258) ⦄ := by
  rw [slot.back_best]
  step*

@[local step] theorem dsym_spec (dtab) (d : Std.Usize) : slot.dsym dtab d ⦃ fun _ => True ⦄ := by
  rw [slot.dsym]
  step*
  repeat' (split <;> step*)
  all_goals exact SV0!

@[local step]
theorem relax_cands_loop_spec (input : Slice Std.U8) (pa cands nc lc) (nextl : Array Std.U16 512#usize)
    (dtab dcc) (i s : Std.Usize) (base : Std.U32) (pcd lo k : Std.Usize)
    (hnx : DpNextl nextl) (hi : i.val < input.length) (hN : input.length + 2147483648 ≤ Std.Usize.max) :
    slot.relax_cands_loop input pa cands nc lc nextl dtab dcc i s base pcd lo k ⦃ fun _ => True ⦄ := by
  have := dp_RING_val
  have := dp_BEXT_TOP_bound
  rw [slot.relax_cands_loop]
  apply SDN!
    (measure := fun (_, _, k') => 16 - k'.val)
    (inv := fun _ => True)
  · rintro ⟨pa', lo', k'⟩ _
    simp only [slot.relax_cands_loop.body]
    step*
    have := dp_shr9 c

    apply WP.spec_bind (Pₘ := fun _ => True)
    · repeat' (split <;> step*)
      all_goals exact SV0!
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
  apply SDN!
    (measure := fun nc' => nc'.val)
    (inv := fun _ => True)
  · rintro nc' _
    simp only [slot.drop_farther_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals exact SV0!
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
  apply SDN!
    (measure := fun t' => max.val - t'.val)
    (inv := fun t' => t'.val ≤ i.val - s.val)
  · rintro t' h1
    simp only [slot.ext_back_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals exact SV0!
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
  apply SDN!
    (measure := fun (_, u') => 259 - u'.val)
    (inv := fun _ => True)
  · rintro ⟨pa', u'⟩ _
    simp only [slot.open_chunk_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals exact SV0!
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
  apply SDN!
    (measure := fun (_, k') => k'.val)
    (inv := fun _ => True)
  · rintro ⟨plan', k'⟩ _
    simp only [slot.push_rev_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals exact SV0!
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
  apply SDN!
    (measure := fun (_, _, _, _, _, g') => g'.val)
    (inv := fun (_, _, _, j', nt', g') => s.val ≤ j'.val ∧ nt'.val + g'.val ≤ Std.Usize.max)
  · rintro ⟨lf', df', tb', j', nt', g'⟩ ⟨h1, h2⟩
    simp only [slot.backtrack_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals exact SV0!
  · exact ⟨hs, hg⟩

@[local step] theorem backtrack_spec (input : Slice Std.U8) (pa plan) (s e : Std.Usize) (lsym dtab lf df tb)
    (hse : s.val ≤ e.val) (he : e.val < Std.Usize.max) :
    slot.backtrack input pa plan s e lsym dtab lf df tb ⦃ fun _ => True ⦄ := by
  rw [slot.backtrack]
  step*

@[local step]
theorem halve_loop0_spec (lf s) : slot.halve_loop0 lf s ⦃ fun _ => True ⦄ := by
  rw [slot.halve_loop0]
  apply SDN!
    (measure := fun (_, s') => 286 - s'.val)
    (inv := fun _ => True)
  · rintro ⟨lf', s'⟩ _
    simp only [slot.halve_loop0.body]
    step*
    all_goals exact SV0!
  · trivial

@[local step]
theorem halve_loop1_spec (df k) : slot.halve_loop1 df k ⦃ fun _ => True ⦄ := by
  rw [slot.halve_loop1]
  apply SDN!
    (measure := fun (_, k') => 30 - k'.val)
    (inv := fun _ => True)
  · rintro ⟨df', k'⟩ _
    simp only [slot.halve_loop1.body]
    step*
    all_goals exact SV0!
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
    all_goals try (have := LeAll_get dp_FRAC_le i3.val (by exact SV0!))
    all_goals exact SV0!

@[local step]
theorem costs_from_loop0_spec (freq total s) : slot.costs_from_loop0 freq total s ⦃ fun _ => True ⦄ := by
  rw [slot.costs_from_loop0]
  apply SDN!
    (measure := fun (_, s') => freq.length - s'.val)
    (inv := fun _ => True)
  · rintro ⟨total', s'⟩ _
    simp only [slot.costs_from_loop0.body]
    step*
    all_goals exact SV0!
  · trivial

@[local step]
theorem costs_from_loop1_spec (freq out lt t) : slot.costs_from_loop1 freq out lt t ⦃ fun _ => True ⦄ := by
  rw [slot.costs_from_loop1]
  apply SDN!
    (measure := fun (_, t') => freq.length - t'.val)
    (inv := fun _ => True)
  · rintro ⟨out', t'⟩ _
    simp only [slot.costs_from_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals exact SV0!
  · trivial

@[local step] theorem costs_from_spec (freq out) : slot.costs_from freq out ⦃ fun _ => True ⦄ := by
  rw [slot.costs_from]
  step*

@[local step]
theorem huff_slot_loop_spec (freq : Slice Std.U32) (sym) (f : Std.U32) (j : Std.Usize) (hf : 0 < freq.length) :
    slot.huff_slot_loop freq sym f j ⦃ fun _ => True ⦄ := by
  rw [slot.huff_slot_loop]
  apply SDN!
    (measure := fun (_, j') => j'.val)
    (inv := fun _ => True)
  · rintro ⟨sym', j'⟩ _
    simp only [slot.huff_slot_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals exact SV0!
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
  apply SDN!
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
      all_goals exact SV0!
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
  all_goals exact SV0!

@[local step]
theorem huff_build_loop_spec (w par) (ns a b nx : Std.Usize) (hns : ns.val ≤ 320) (hnx : nx.val ≤ 639)
    (hab : a.val + b.val + ns.val = 2 * nx.val) :
    slot.huff_build_loop w par ns a b nx ⦃ fun _ => True ⦄ := by
  rw [slot.huff_build_loop]
  apply SDN!
    (measure := fun (_, _, _, _, nx') => 639 - nx'.val)
    (inv := fun (_, _, a', b', nx') => nx'.val ≤ 639 ∧ a'.val + b'.val + ns.val = 2 * nx'.val)
  · rintro ⟨w', par', a', b', nx'⟩ ⟨h1, h2⟩
    simp only [slot.huff_build_loop.body]
    step*
    rcases y with ⟨i7, a1, b1⟩
    step*
    all_goals exact SV0!
  · exact ⟨hnx, hab⟩

@[local step] theorem huff_build_spec (w par) (ns : Std.Usize) (hns : ns.val ≤ 320) :
    slot.huff_build w par ns ⦃ fun _ => True ⦄ := by
  rw [slot.huff_build]
  step*

@[local step]
theorem huff_depths_loop_spec (par depth ns mx q) : slot.huff_depths_loop par depth ns mx q ⦃ fun _ => True ⦄ := by
  rw [slot.huff_depths_loop]
  apply SDN!
    (measure := fun (_, _, q') => q'.val)
    (inv := fun _ => True)
  · rintro ⟨depth', mx', q'⟩ _
    simp only [slot.huff_depths_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals exact SV0!
  · trivial

@[local step] theorem huff_depths_spec (par depth nx ns) : slot.huff_depths par depth nx ns ⦃ fun _ => True ⦄ := by
  rw [slot.huff_depths]
  step*
  repeat' (split <;> step*)

@[local step]
theorem huff_costs_loop0_spec (freq : Slice Std.U32) (sym ns w k) (hf : 0 < freq.length) :
    slot.huff_costs_loop0 freq sym ns w k ⦃ fun _ => True ⦄ := by
  rw [slot.huff_costs_loop0]
  apply SDN!
    (measure := fun (_, k') => ns.val - k'.val)
    (inv := fun _ => True)
  · rintro ⟨w', k'⟩ _
    simp only [slot.huff_costs_loop0.body]
    step*
    all_goals exact SV0!
  · trivial

@[local step]
theorem huff_costs_loop1_spec (m out) (mx : Std.U32) (t : Std.Usize) (hmx : mx.val ≤ 15) :
    slot.huff_costs_loop1 m out mx t ⦃ fun _ => True ⦄ := by
  rw [slot.huff_costs_loop1]
  apply SDN!
    (measure := fun (_, t') => m.val - t'.val)
    (inv := fun _ => True)
  · rintro ⟨out', t'⟩ _
    simp only [slot.huff_costs_loop1.body]
    step*
    all_goals exact SV0!
  · trivial

@[local step]
theorem huff_costs_loop2_spec (out sym ns depth r) : slot.huff_costs_loop2 out sym ns depth r ⦃ fun _ => True ⦄ := by
  rw [slot.huff_costs_loop2]
  apply SDN!
    (measure := fun (_, r') => ns.val - r'.val)
    (inv := fun _ => True)
  · rintro ⟨out', r'⟩ _
    simp only [slot.huff_costs_loop2.body]
    step*
    repeat' (split <;> step*)
    all_goals exact SV0!
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
    all_goals exact SV0!

@[local step]
theorem make_costs_loop0_spec (litc llc b) : slot.make_costs_loop0 litc llc b ⦃ fun _ => True ⦄ := by
  rw [slot.make_costs_loop0]
  apply SDN!
    (measure := fun (_, b') => 256 - b'.val)
    (inv := fun _ => True)
  · rintro ⟨litc', b'⟩ _
    simp only [slot.make_costs_loop0.body]
    step*
    all_goals exact SV0!
  · trivial

@[local step]
theorem make_costs_loop1_spec (lsym : Array Std.U8 512#usize) (lc) (llc : Array Std.U32 286#usize) (l : Std.Usize)
    (hls : LeAll lsym.val 28) : slot.make_costs_loop1 lsym lc llc l ⦃ fun _ => True ⦄ := by
  rw [slot.make_costs_loop1]
  apply SDN!
    (measure := fun (_, l') => 259 - l'.val)
    (inv := fun _ => True)
  · rintro ⟨lc', l'⟩ _
    simp only [slot.make_costs_loop1.body]
    step*
    all_goals try (have := LeAll_get hls l'.val (by exact SV0!))
    all_goals exact SV0!
  · trivial

@[local step]
theorem make_costs_loop2_spec (dcc dc k) : slot.make_costs_loop2 dcc dc k ⦃ fun _ => True ⦄ := by
  rw [slot.make_costs_loop2]
  apply SDN!
    (measure := fun (_, k') => 30 - k'.val)
    (inv := fun _ => True)
  · rintro ⟨dcc', k'⟩ _
    simp only [slot.make_costs_loop2.body]
    step*
    all_goals exact SV0!
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
theorem update_costs_loop_spec (lf tot z) : slot.update_costs_loop lf tot z ⦃ fun _ => True ⦄ := by
  rw [slot.update_costs_loop]
  apply SDN!
    (measure := fun (_, z') => 286 - z'.val)
    (inv := fun _ => True)
  · rintro ⟨tot', z'⟩ _
    simp only [slot.update_costs_loop.body]
    step*
    all_goals exact SV0!
  · trivial

@[local step] theorem update_costs_spec (lf df) (lsym : Array Std.U8 512#usize) (litc lc dcc huff)
    (hls : LeAll lsym.val 28) : slot.update_costs lf df lsym litc lc dcc huff ⦃ fun _ => True ⦄ := by
  rw [slot.update_costs]
  step*
  repeat' (split <;> step*)

@[local step]
theorem init_counts_loop0_spec (input : Slice Std.U8) (lf) (n step i : Std.Usize)
    (hn : n.val = input.length) (hstep : 1 ≤ step.val) (hns : n.val + step.val ≤ Std.Usize.max) :
    slot.init_counts_loop0 input lf n step i ⦃ fun _ => True ⦄ := by
  rw [slot.init_counts_loop0]
  apply SDN!
    (measure := fun (_, i') => n.val - i'.val)
    (inv := fun _ => True)
  · rintro ⟨lf', i'⟩ _
    simp only [slot.init_counts_loop0.body]
    step*
    all_goals exact SV0!
  · trivial

@[local step]
theorem init_counts_loop1_spec (lf s) : slot.init_counts_loop1 lf s ⦃ fun _ => True ⦄ := by
  rw [slot.init_counts_loop1]
  apply SDN!
    (measure := fun (_, s') => 286 - s'.val)
    (inv := fun _ => True)
  · rintro ⟨lf', s'⟩ _
    simp only [slot.init_counts_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals exact SV0!
  · trivial

@[local step]
theorem init_counts_loop2_spec (df k) : slot.init_counts_loop2 df k ⦃ fun _ => True ⦄ := by
  rw [slot.init_counts_loop2]
  apply SDN!
    (measure := fun (_, k') => 30 - k'.val)
    (inv := fun _ => True)
  · rintro ⟨df', k'⟩ _
    simp only [slot.init_counts_loop2.body]
    step*
    repeat' (split <;> step*)
    all_goals exact SV0!
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
  apply SDN!
    (measure := fun (_, _, l') => 259 - l'.val)
    (inv := fun (ls', c', _) => c'.val ≤ 28 ∧ LeAll ls'.val 28)
  · rintro ⟨ls', c', l'⟩ ⟨h1, h2⟩
    simp only [slot.fill_tables_loop0.body]
    split
    · apply WP.spec_bind (Pₘ := fun (x : Std.Usize) => x.val ≤ 28)
      · repeat' (split <;> step*)
        all_goals exact SV0!
      · intro code1 hc1
        step*
        and_intros
        all_goals first
          | exact dp_LeAll_set_of_eq a_post h2 (by exact SV0!)
          | exact SV0!
    · step*
  · exact ⟨hc, hls⟩

@[local step]
theorem fill_tables_loop1_spec (dtab c j) : slot.fill_tables_loop1 dtab c j ⦃ fun _ => True ⦄ := by
  rw [slot.fill_tables_loop1]
  apply SDN!
    (measure := fun (_, _, j') => 256 - j'.val)
    (inv := fun _ => True)
  · rintro ⟨dtab', c', j'⟩ _
    simp only [slot.fill_tables_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals exact SV0!
  · trivial

@[local step]
theorem fill_tables_loop2_loop0_spec (c2 d) : slot.fill_tables_loop2_loop0 c2 d ⦃ fun _ => True ⦄ := by
  rw [slot.fill_tables_loop2_loop0]
  apply SDN!
    (measure := fun c2' => 29 - c2'.val)
    (inv := fun _ => True)
  · rintro c2' _
    simp only [slot.fill_tables_loop2_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals exact SV0!
  · trivial

@[local step]
theorem fill_tables_loop2_spec (dtab c2 k) : slot.fill_tables_loop2 dtab c2 k ⦃ fun _ => True ⦄ := by
  rw [slot.fill_tables_loop2]
  apply SDN!
    (measure := fun (_, _, k') => 256 - k'.val)
    (inv := fun _ => True)
  · rintro ⟨dtab', c2', k'⟩ _
    simp only [slot.fill_tables_loop2.body]
    step*
    all_goals exact SV0!
  · trivial

@[local step] theorem fill_tables_spec (lsym : Array Std.U8 512#usize) (dtab) (hls : LeAll lsym.val 28) :
    slot.fill_tables lsym dtab ⦃ fun r => LeAll r.1.val 28 ⦄ := by
  rw [slot.fill_tables]
  step*

@[local step]
theorem fill_nextl_loop0_loop0_spec (lsym) (l e : Std.Usize) (hl : l.val < 257) (he : e.val ≤ 258) :
    slot.fill_nextl_loop0_loop0 lsym l e ⦃ fun r => e.val ≤ r.val ∧ r.val ≤ 258 ⦄ := by
  rw [slot.fill_nextl_loop0_loop0]
  apply SDN!
    (measure := fun e' => 258 - e'.val)
    (inv := fun e' => e.val ≤ e'.val ∧ e'.val ≤ 258)
  · rintro e' ⟨h1, h2⟩
    simp only [slot.fill_nextl_loop0_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals exact SV0!
  · exact ⟨le_refl _, he⟩

@[local step]
theorem fill_nextl_loop0_spec (lsym) (nextl : Array Std.U16 512#usize) (l : Std.Usize)
    (hl : l.val ≤ 512) (hnx : ∀ j, j < l.val → j < (nextl.val[j]!).val) :
    slot.fill_nextl_loop0 lsym nextl l ⦃ fun r => DpNextl r ⦄ := by
  rw [slot.fill_nextl_loop0]
  apply SDN!
    (measure := fun (_, l') => 512 - l'.val)
    (inv := fun (nx', l') => l'.val ≤ 512 ∧ ∀ j, j < l'.val → j < (nx'.val[j]!).val)
  · rintro ⟨nx', l'⟩ ⟨h1, h2⟩
    simp only [slot.fill_nextl_loop0.body]
    split
    · step*
      repeat' (split <;> step*)
      all_goals
        and_intros
        all_goals first
          | exact SV0!
          | (intro j hj
             rw [a_post, Array.set_val_eq, dp_getElem!_set _ _ _ _ (by exact SV0!)]
             split
             · exact SV0!
             · exact h2 j (by exact SV0!))
    · step*
      intro j hj
      exact h2 j (by exact SV0!)
  · exact ⟨hl, hnx⟩

@[local step] theorem fill_nextl_spec (lsym) (nextl : Array Std.U16 512#usize) :
    slot.fill_nextl lsym nextl ⦃ fun r => DpNextl r ⦄ := by
  rw [slot.fill_nextl]
  apply fill_nextl_loop0_spec
  · exact SV0!
  · intro j hj; simp at hj

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

set_option maxHeartbeats 10000000 in
theorem dp_parse_loop_spec (input : Slice Std.U8) (plan) (ct lazyn d4 d7 skip h3d huff n : Std.Usize)
    (head3 : Array Std.U32 16384#usize) (head4 : Array Std.U32 65536#usize) (prev4)
    (head7 : Array Std.U32 65536#usize) (prev7 pa tb) (lsym : Array Std.U8 512#usize) (dtab)
    (nextl : Array Std.U16 512#usize) (lf df litc lc dcc) (lim : Std.Usize) (sh7 : Std.U32)
    (s next_upd : Std.Usize) (cands) (cl cd : Std.Usize) (cdc : Std.U32) (i anchor alen : Std.Usize)
    (hn : n.val = input.length) (hlim : lim.val + 8 = n.val)
    (hN : input.length + input.length ≤ Std.Usize.max)
    (hls : LeAll lsym.val 28) (hnx : DpNextl nextl)
    (hsi : s.val ≤ i.val) (hin : i.val ≤ n.val) (hcl : cl.val < 512)
    (h3 : LeAll head3.val i.val) (h4 : LeAll head4.val i.val) (h7 : LeAll head7.val i.val) :
    slot.dp_parse_loop input plan ct lazyn d4 d7 skip h3d huff n head3 head4 prev4 head7 prev7 pa tb
      lsym dtab nextl lf df litc lc dcc lim sh7 s next_upd cands cl cd cdc i anchor alen ⦃ fun _ => True ⦄ := by
  have hR := dp_RING_val
  have hU := dp_UPD_bound
  have hS := dp_size hN
  rw [slot.dp_parse_loop]
  apply SDN!
    (measure := fun (_, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, i', _, _) => lim.val - i'.val)
    (inv := fun (_, h3', h4', _, h7', _, _, _, _, _, _, _, _, s', _, _, cl', _, _, i', _, _) =>
       s'.val ≤ i'.val ∧ i'.val ≤ n.val ∧ cl'.val < 512 ∧ LeAll h3'.val i'.val ∧ LeAll h4'.val i'.val ∧
       LeAll h7'.val i'.val)
  · rintro ⟨plan', h3', h4', p4', h7', p7', pa', tb', lf', df', litc', lc', dcc', s', nu', cands', cl', cd', cdc',
      i', anc', alen'⟩ ⟨hs', hi', hcl', hh3, hh4, hh7⟩
    clear hsi hin hcl h3 h4 h7
    clear plan head3 head4 prev4 head7 prev7 pa tb lf df litc lc dcc s next_upd cands cl cd cdc i anchor alen
    simp only [slot.dp_parse_loop.body]
    apply dp_ite_spec
    · intro hlt
      apply WP.spec_bind (Pₘ := fun _ => True)
      · split <;> step*
        all_goals exact SV0!
      intro pa1 _
      step
      step with insert_pos_spec (B := i'.val) as ⟨hc, head31, head41, prev41, head71, prev71, hq1, hq2, hq3, hL3, hL4, hL7⟩
      step*
      apply WP.spec_bind (Pₘ := fun _ => True)
      · split <;> simp only [WP.spec_ok]
      intro lzn _
      step*
      apply WP.spec_bind (Pₘ := fun (x : alloc.vec.Vec Std.U32 × Array Std.U32 16384#usize × Array Std.U32 65536#usize ×
          Array Std.U32 32768#usize × Array Std.U32 65536#usize × Array Std.U32 32768#usize × Array Std.U64 8192#usize ×
          Array Std.U32 8192#usize × Array Std.U32 320#usize × Array Std.U32 32#usize × Std.Usize × Array Std.U32 16#usize ×
          Std.Usize × Std.Usize × Std.U32 × Std.Usize × Std.Usize × Std.Usize) =>
        match x with
        | (_, g3, g4, _, g7, _, _, _, _, _, s1, _, cl1, _, _, i12, _, _) =>
          s1.val ≤ i12.val ∧ i'.val < i12.val ∧ i12.val ≤ n.val ∧ cl1.val < 512 ∧
          LeAll g3.val i12.val ∧ LeAll g4.val i12.val ∧ LeAll g7.val i12.val)
      · apply dp_ite3_spec
        ·
          intro hct hc3 hlz
          clear * - hS hc3 hcl' hs' hi' hlt hlim hn hL3 hL4 hL7 i4_post
          step*
          exact ⟨by exact SV0!, by exact SV0!, by exact SV0!, by exact SV0!, LeAll_mono hL3 (by exact SV0!),
            LeAll_mono hL4 (by exact SV0!), LeAll_mono hL7 (by exact SV0!)⟩
        ·
          clear * - hn hlim hS hnx hs' hi' hlt hq1 hq2 hq3 hL3 hL4 hL7 i4_post
          step*
          apply WP.spec_bind (Pₘ := fun (x : Std.Usize) => 9 ≤ x.val ∧ i'.val + x.val ≤ n.val)
          · split <;> simp only [WP.spec_ok] <;> exact SV0!
          rintro cap1 ⟨hcap1, hcap2⟩
          rcases hc with ⟨c3, c4, c7⟩
          step*
          apply WP.spec_bind (Pₘ := fun (x : Array Std.U32 16#usize × Std.Usize × Std.Usize × Bool) =>
            2 ≤ x.2.2.1.val ∧ x.2.2.1.val ≤ cap1.val)
          · split
            · step*
              apply WP.spec_bind (Pₘ := fun (x : Array Std.U32 16#usize × Std.Usize × Std.Usize) =>
                2 ≤ x.2.2.val ∧ x.2.2.val ≤ cap1.val)
              · split <;> step*
                all_goals exact SV0!
              rintro ⟨a, i17, i18⟩ ⟨hb1, hb2⟩
              step*
            · simp only [WP.spec_ok]; exact SV0!
          rintro ⟨cands2, nc, best, p3⟩ ⟨hb1, hb2⟩
          clear * - hn hlim hS hnx hs' hi' hlt hq2 hq3 hL3 hL4 hL7 i4_post hcap1 hcap2 hb1 hb2
          apply WP.spec_bind (Pₘ := fun _ => True)
          · split <;> simp only [WP.spec_ok]
          intro b _
          step*
          apply WP.spec_bind (Pₘ := fun _ => True)
          · split
            · simp only [WP.spec_ok]
            · split <;> simp only [WP.spec_ok, bind_tc_ok]
          rintro ⟨cands4, dep7⟩ _
          apply WP.spec_bind (Pₘ := fun _ => True)
          · repeat' split
            all_goals simp only [WP.spec_ok]
          intro b1 _
          step*
          apply WP.spec_bind (Pₘ := fun (x : Array Std.U32 16#usize × Std.Usize × Std.Usize) =>
            2 ≤ x.2.2.val ∧ x.2.2.val ≤ cap1.val)
          · apply dp_ite2_spec
            · intro hgt hle
              step*
              apply WP.spec_bind (Pₘ := fun _ => True)
              · split <;> step*
              intro i26 _
              step*
              all_goals exact SV0!
            · simp only [WP.spec_ok]; exact SV0!
          rintro ⟨cands6, nc3, best3⟩ ⟨hb3, hb4⟩
          clear * - hn hlim hS hnx hs' hi' hlt hL3 hL4 hL7 i4_post hcap1 hcap2 hb3 hb4
          apply WP.spec_bind (Pₘ := fun _ => True)
          · split <;> simp only [WP.spec_ok]
          intro pcd _
          step*
          apply WP.spec_bind (Pₘ := fun (x : Std.Usize × Std.Usize × Std.U32) => x.1.val < 512)
          · split
            · step*
              all_goals
                have := dp_sat_sub_val i24 1#usize
                exact SV0!
            · simp only [WP.spec_ok]; exact SV0!
          rintro ⟨cl2, cd2, cdc2⟩ hcl2
          clear * - hn hlim hS hnx hs' hi' hlt hL3 hL4 hL7 i4_post hcap1 hcap2 hb3 hb4 hcl2
          apply WP.spec_bind (Pₘ := fun (x : alloc.vec.Vec Std.U32 × Array Std.U32 16384#usize ×
              Array Std.U32 65536#usize × Array Std.U32 32768#usize × Array Std.U32 65536#usize ×
              Array Std.U32 32768#usize × Array Std.U64 8192#usize × Array Std.U32 8192#usize ×
              Array Std.U32 320#usize × Array Std.U32 32#usize × Std.Usize × Std.Usize × Std.Usize) =>
            match x with
            | (_, g3, g4, _, g7, _, _, _, _, _, s1, cl1, i12) =>
              s1.val ≤ i12.val ∧ i'.val < i12.val ∧ i12.val ≤ n.val ∧ cl1.val < 512 ∧
              LeAll g3.val i12.val ∧ LeAll g4.val i12.val ∧ LeAll g7.val i12.val)
          · apply dp_ite2_spec
            ·
              intro hsk hnc
              have := dp_shr9
              step*
              apply WP.spec_bind (Pₘ := fun _ => True)
              · split <;> step*
                all_goals exact SV0!
              intro plan3 _
              step*
              apply WP.spec_bind (Pₘ := fun (x : Std.Usize) => x.val ≤ «end».val ∧ x.val ≤ lim.val)
              · split <;> simp only [WP.spec_ok] <;> exact SV0!
              rintro end1 ⟨he1, he2⟩
              have hE3 := LeAll_mono hL3 (show i'.val ≤ «end».val by exact SV0!)
              have hE4 := LeAll_mono hL4 (show i'.val ≤ «end».val by exact SV0!)
              have hE7 := LeAll_mono hL7 (show i'.val ≤ «end».val by exact SV0!)
              step with insert_range_spec (B := «end».val) as ⟨head33, head43, prev43, head73, prev73, hr3, hr4, hr7⟩
              step*
              exact ⟨le_refl _, by exact SV0!, by exact SV0!, by exact SV0!, hr3, hr4, hr7⟩
            ·
              step*
              exact ⟨by exact SV0!, by exact SV0!, by exact SV0!, by simpa using hcl2,
                LeAll_mono hL3 (by exact SV0!), LeAll_mono hL4 (by exact SV0!), LeAll_mono hL7 (by exact SV0!)⟩
          rintro ⟨v, a, a1, a2, a3, a4, a5, a6, a7, a8, i21, i22, i23⟩ ⟨hv1, hv2, hv3, hv4, hv5, hv6, hv7⟩
          step*
      rintro ⟨plan1, head32, head42, prev42, head72, prev72, pa3, tb1, lf1, df1, s1, cands1, cl1, cd1, cdc1, i12,
        anchor1, alen1⟩ ⟨hs1, hii, hin1, hcl1, hk3, hk4, hk7⟩
      clear * - hs1 hii hin1 hcl1 hk3 hk4 hk7 hlt hn hlim hS hls hU hR
      step*
      apply WP.spec_bind (Pₘ := fun (x : alloc.vec.Vec Std.U32 × Array Std.U64 8192#usize × Array Std.U32 8192#usize ×
          Array Std.U32 320#usize × Array Std.U32 32#usize × Std.Usize) => x.2.2.2.2.2.val ≤ i12.val)
      · split <;> step*
        all_goals exact SV0!
      rintro ⟨plan2, pa4, tb2, lf2, df2, s2⟩ hs2
      split <;> step*
      all_goals
        simp only at hs2
        exact ⟨hs2, hin1, hcl1, hk3, hk4, hk7, by exact SV0!⟩
    · intro _
      step*
  · exact ⟨hsi, hin, hcl, h3, h4, h7⟩

attribute [local step] dp_parse_loop_spec

@[local step] theorem dp_parse_spec (input : Slice Std.U8) (plan) (ct lazyn d4 d7 skip h3d huff : Std.Usize)
    (h16 : 16 ≤ input.length) (hN : input.length + input.length ≤ Std.Usize.max) :
    slot.dp_parse input plan ct lazyn d4 d7 skip h3d huff ⦃ fun _ => True ⦄ := by
  have hS := dp_size hN
  have hk := dp_KB7_bound
  have hU := dp_UPD_bound
  have z8 : LeAll (Array.repeat 512#usize 0#u8).val 28 := dp_LeAll_repeat _ _ _ (by simp)
  have z3 : LeAll (Array.repeat 16384#usize 0#u32).val (0#usize).val := dp_LeAll_repeat _ _ _ (by simp)
  have z4 : LeAll (Array.repeat 65536#usize 0#u32).val (0#usize).val := dp_LeAll_repeat _ _ _ (by simp)
  rw [slot.dp_parse]
  step*
  split <;> step*
  all_goals exact SV0!

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
  apply SDN! (measure := fun x => x.2.val) (inv := fun _ => True)
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
  apply SDN! (measure := fun x => 288 - x.2.2.2.val) (inv := fun _ => True)
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
  apply SDN! (measure := fun x => ns.val - x.2.val) (inv := fun _ => True)
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
  apply SDN! (measure := fun x => 575 - x.2.2.2.2.val) (inv := fun _ => True)
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
  apply SDN! (measure := fun x => x.2.val) (inv := fun _ => True)
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
  apply SDN! (measure := fun x => ns.val - x.2.1.val) (inv := fun _ => True)
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
  apply SDN! (measure := fun x => x.2.2.2.2.val) (inv := fun _ => True)
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
  apply SDN! (measure := fun x => 288 - x.2.val) (inv := fun _ => True)
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
  apply SDN! (measure := fun x => 288 - x.2.val) (inv := fun _ => True)
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
  apply SDN! (measure := fun x => 256 - x.2.val) (inv := fun _ => True)
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
  apply SDN! (measure := fun x => 264 - x.2.val) (inv := fun _ => True)
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
  apply SDN! (measure := fun x => 40 - x.2.val) (inv := fun _ => True)
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
  apply SDN! (measure := fun x => (Slice.len s).val - x.2.2.2.2.1.val) (inv := fun _ => True)
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
  apply SDN! (measure := fun x => 256 - x.2.val) (inv := fun _ => True)
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
  apply SDN! (measure := fun x => 512 - x.2.val) (inv := fun _ => True)
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
  apply SDN! (measure := fun x => 32 - x.2.val) (inv := fun _ => True)
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
  apply SDN! (measure := fun x => x.2.2.1.val) (inv := fun x => x.2.1.length = out.length)
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
  apply SDN! (measure := fun x => x.2.2.1.val) (inv := fun x => x.2.1.length = out.length)
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
  apply SDN! (measure := fun x => x.2.2.1.val) (inv := fun x => x.2.1.length = out.length)
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
theorem d_best_len_loop_spec (lc ring p e bv l) :
    slot.d_best_len_loop lc ring p e bv l ⦃ fun r => True ⦄ := by
  rw [slot.d_best_len_loop]
  apply SDN! (measure := fun x => e.val - x.2.val) (inv := fun _ => True)
  · rintro ⟨bv', l'⟩ _
    unfold slot.d_best_len_loop.body
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
theorem d_best_len_spec (lc ring p lo e) :
    slot.d_best_len lc ring p lo e ⦃ fun r => True ⦄ :=
  d_best_len_loop_spec lc ring p e _ lo

@[local step]
theorem d_push_loop_spec (lc ring p el t f chd x) :
    slot.d_push_loop lc ring p el t f chd x ⦃ fun r => True ⦄ := by
  rw [slot.d_push_loop]
  apply SDN! (measure := fun x => 259 - x.2.val) (inv := fun _ => True)
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
  apply SDN! (measure := fun x => top.val - x.2.val) (inv := fun _ => True)
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
  apply SDN! (measure := fun x => x.2.2.2.2.2.2.2.2.val) (inv := fun x => x.1.length = out.length)
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
  apply SDN! (measure := fun x => e2.val - x.2.2.2.val) (inv := fun _ => True)
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
  apply SDN! (measure := fun x => x.2.2.2.2.2.2.2.1.val) (inv := fun x => x.1.length = out.length)
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
  apply SDN! (measure := fun x => n.val - x.2.val) (inv := fun _ => True)
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
  apply SDN!
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
  apply SDN!
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
  apply SDN! (measure := fun (_, z') => 16 - z'.val) (inv := fun _ => True)
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
  apply SDN! (measure := fun (_, q', _) => 16 - q'.val) (inv := fun _ => True)
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
  simp only [lift, bind_tc_ok]
  refine d3_bind (d_record_loop_spec _ _ _ _ _ _ _ _ _ _ _ _ _ _) ?_; intro rs1 _
  refine d3_bind (d3_true (d_push32_spec ..)) ?_; intro rs2 _
  exact d3_true (d_push32_spec ..)

@[local step]
theorem d_fill_nextl_loop0_loop0_spec (lsym) (l e : Std.Usize) (hl : l.val < 257) (he : e.val ≤ 258) :
    slot.d_fill_nextl_loop0_loop0 lsym l e ⦃ fun r => e.val ≤ r.val ∧ r.val ≤ 258 ⦄ := by
  rw [slot.d_fill_nextl_loop0_loop0]
  apply SDN!
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
  apply SDN!
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
  apply SDN!
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
  apply SDN!
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
  apply SDN!
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
  apply SDN!
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
  apply SDN!
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

theorem r_run_loop_spec (input : Slice Std.U8) (p : Std.Usize) (c : Std.U8) (n : Std.Usize) (l0 : Std.Usize)
    (hn : n.val = input.length) (hl : l0.val ≤ 258) (hp : p.val + l0.val ≤ n.val) :
    slot.r_run_loop input p c n l0 ⦃ fun r => r.val ≤ 258 ∧ p.val + r.val ≤ n.val ⦄ := by
  rw [slot.r_run_loop]
  apply SDN!
    (measure := fun l => 258 - l.val)
    (inv := fun l => l.val ≤ 258 ∧ p.val + l.val ≤ n.val)
  · rintro l ⟨hl1, hl2⟩
    simp only [slot.r_run_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars; scalar_tac)
  · exact ⟨hl, hp⟩

@[local step]
theorem r_run_spec (input : Slice Std.U8) (p : Std.Usize) (c : Std.U8) (hp : p.val ≤ input.length) :
    slot.r_run input p c ⦃ fun r => r.val ≤ 258 ∧ p.val + r.val ≤ input.length ⦄ := by
  rw [slot.r_run]
  have := r_run_loop_spec input p c (Slice.len input) 0#usize (by simp) (by simp) (by simp; scalar_tac)
  simpa using this

theorem r_plan_loop_spec (input : Slice Std.U8) (n : Std.Usize) (plan : alloc.vec.Vec Std.U32) (p : Std.Usize)
    (hn : n.val = input.length) (hsz : n.val < 67108864) (hp : p.val ≤ n.val) :
    slot.r_plan_loop input n plan p ⦃ fun _ => True ⦄ := by
  rw [slot.r_plan_loop]
  apply SDN!
    (measure := fun (_, q) => n.val - q.val)
    (inv := fun (_, q) => q.val ≤ n.val)
  · rintro ⟨pl, q⟩ hq
    simp only [slot.r_plan_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars; scalar_tac)
  · exact hp

@[local step]
theorem r_plan_spec (input : Slice Std.U8) (hsz : input.length < 67108864) :
    slot.r_plan input ⦃ fun _ => True ⦄ := by
  rw [slot.r_plan]
  step*
  exact r_plan_loop_spec input _ _ 0#usize (by simp) (by simp; scalar_tac) (by simp)

@[local step]
theorem x_plan_spec (input : Slice Std.U8) (k : Std.Usize) :
    slot.x_plan input k ⦃ fun _ => True ⦄ := by
  rw [slot.x_plan]
  step*
  repeat' (split <;> step*)

open LZ77 (Matches)

def sp_word8 (input : Slice Std.U8) (p : Nat) : Nat :=
  ((((((((input.val[p]!).val * 256 + (input.val[p + 1]!).val) * 256
    + (input.val[p + 2]!).val) * 256 + (input.val[p + 3]!).val) * 256
    + (input.val[p + 4]!).val) * 256 + (input.val[p + 5]!).val) * 256
    + (input.val[p + 6]!).val) * 256 + (input.val[p + 7]!).val)

theorem sp_u8_lt (x : Std.U8) : x.val < 256 := by scalar_tac

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
  scalar_tac

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
  apply SDN!
    (measure := fun l => cap.val - l.val)
    (inv := fun l => l.val ≤ cap.val ∧ Matches input a.val b.val l.val)
  · rintro l ⟨hle, hm⟩
    simp only [slot.mlen_loop0_loop0.body]
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    step*
    refine ⟨by scalar_tac, ?_, by scalar_tac⟩
    exact Matches.sp_byte hm (by assumption) (by assumption) (by scalar_tac) (by scalar_tac)
      (by assumption) (by assumption) (by assumption) (by scalar_tac)
  · exact ⟨hl0, h0⟩

@[local step]
theorem mlen_loop0_spec (input : Slice Std.U8) (a b cap l0 : Std.Usize)
    (ha : a.val + cap.val ≤ input.length) (hb : b.val + cap.val ≤ input.length)
    (hl0 : l0.val ≤ cap.val) (h0 : Matches input a.val b.val l0.val) :
    slot.mlen_loop0 input a b cap l0 ⦃ fun l => l.val ≤ cap.val ∧ Matches input a.val b.val l.val ⦄ := by
  rw [slot.mlen_loop0]
  apply SDN!
    (measure := fun l => cap.val - l.val)
    (inv := fun l => l.val ≤ cap.val ∧ Matches input a.val b.val l.val)
  · rintro l ⟨hle, hm⟩
    simp only [slot.mlen_loop0.body]
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input

    step*
    ·
      refine ⟨by scalar_tac, ?_⟩
      exact Matches.sp_word hm (by assumption) (by assumption) (by assumption) (by assumption)
        (by assumption) (by assumption) (by scalar_tac)
    ·
      refine ⟨by scalar_tac, ?_, by scalar_tac⟩
      exact Matches.sp_word_eq hm (by assumption) (by assumption) (by assumption) (by assumption)
        (by assumption) (by scalar_tac)
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
  refine ⟨by scalar_tac, by scalar_tac, by scalar_tac, by scalar_tac, by scalar_tac,
    by scalar_tac, ?_⟩
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
  apply SDN!
    (measure := fun (_, _, _, _, p) => n.val - p.val)
    (inv := fun (out, ntok, k, _, p) => p.val ≤ n.val ∧ ntok.val ≤ p.val ∧ k.val ≤ p.val ∧
      out.length = out0.length ∧
      LZ77.decode (toks out ntok.val) = some ((bytes input).take p.val))
  · rintro ⟨out, ntok, k, owed, p⟩ ⟨hp, hnt, hk, hlen, hde⟩
    simp only [slot.emit_loop.body]
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    split
    case isTrue hlt =>
      have hntok_lt : ntok.val < out.length := by scalar_tac
      step*
      ·
        have hlit : i1.val = (bytes input)[p.val]! := by
          rw [bytes_getElem! input p.val (by scalar_tac)]
          scalar_tac
        refine ⟨by scalar_tac, by scalar_tac, by scalar_tac, by rw [s_post]; simpa using hlen, ?_,
          by scalar_tac⟩
        rw [s_post, show ntok1.val = ntok.val + 1 by scalar_tac,
          show p1.val = p.val + 1 by scalar_tac]
        exact emit_lit input out ntok p.val i1 hde (by scalar_tac) hntok_lt hlit
      ·
        obtain ⟨h3, h258, hd1, hd32k, hdp, hend, hm⟩ := valid_post (by assumption)
        have htok : tok.val = LZ77.mkMatch dist.val len.val := by
          simp only [LZ77.mkMatch, LZ77.MATCH_BASE]
          scalar_tac
        refine ⟨by scalar_tac, by scalar_tac, by scalar_tac, by rw [s_post]; simpa using hlen, ?_,
          by scalar_tac⟩
        rw [s_post, show ntok1.val = ntok.val + 1 by scalar_tac,
          show p1.val = p.val + len.val by scalar_tac]
        exact emit_match input out ntok p.val dist.val len.val tok hde hntok_lt hd1 hdp hd32k
          h3 h258 hend hm htok
      all_goals

        have hlit : i3.val = (bytes input)[p.val]! := by
          rw [bytes_getElem! input p.val (by scalar_tac)]
          scalar_tac
        subst index_mut_back
        refine ⟨by scalar_tac, by scalar_tac, by scalar_tac, by simpa using hlen, ?_, by scalar_tac⟩
        rw [show ntok1.val = ntok.val + 1 by scalar_tac, show p1.val = p.val + 1 by scalar_tac]
        exact emit_lit input out ntok p.val i3 hde (by scalar_tac) hntok_lt hlit
    case isFalse hge =>
      have hpn : p.val = input.length := by scalar_tac
      refine ⟨by scalar_tac, hlen, ?_⟩
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
  apply SDN!
    (measure := fun (_, _, p) => n.val - p.val)
    (inv := fun (out, ntok, p) => p.val ≤ n.val ∧ ntok.val ≤ p.val ∧ out.length = out0.length ∧
      LZ77.decode (toks out ntok.val) = some ((bytes input).take p.val))
  · rintro ⟨out, ntok, p⟩ ⟨hp, hnt, hlen, hde⟩
    simp only [slot.emit_pos_loop.body]
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    split
    case isTrue hlt =>
      have hntok_lt : ntok.val < out.length := by scalar_tac
      step*
      ·
        obtain ⟨h3, h258, hd1, hd32k, hdp, hend, hm⟩ := valid_post (by assumption)
        have htok : tok.val = LZ77.mkMatch dist.val len.val := by
          simp only [LZ77.mkMatch, LZ77.MATCH_BASE]
          scalar_tac
        refine ⟨by scalar_tac, by scalar_tac, by rw [s_post]; simpa using hlen, ?_, by scalar_tac⟩
        rw [s_post, show ntok1.val = ntok.val + 1 by scalar_tac,
          show p1.val = p.val + len.val by scalar_tac]
        exact emit_match input out ntok p.val dist.val len.val tok hde hntok_lt hd1 hdp hd32k
          h3 h258 hend hm htok
      ·
        have hlit : lit.val = (bytes input)[p.val]! := by
          rw [bytes_getElem! input p.val (by scalar_tac)]
          scalar_tac
        refine ⟨by scalar_tac, by scalar_tac, by rw [s_post]; simpa using hlen, ?_, by scalar_tac⟩
        rw [s_post, show ntok1.val = ntok.val + 1 by scalar_tac,
          show p1.val = p.val + 1 by scalar_tac]
        exact emit_lit input out ntok p.val lit hde (by scalar_tac) hntok_lt hlit
    case isFalse hge =>
      have hpn : p.val = input.length := by scalar_tac
      refine ⟨by scalar_tac, hlen, ?_⟩
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
  apply SDN!
    (measure := fun (_, i) => n.val - i.val)
    (inv := fun (v, i) => v.length = i.val ∧ i.val ≤ n.val)
  · rintro ⟨v, i⟩ ⟨hvi, hin⟩
    simp only [slot.zeros_loop.body]
    step*
    have hlen : v1.length = v.length + 1 := by simp [v1_post]
    scalar_tac
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
  apply SDN!
    (measure := fun (_, i') => e.val - i'.val)
    (inv := fun (f', i') => i.val ≤ i'.val ∧ i'.val - i.val ≤ e.val - i.val ∧
      LeAll f'.val (c + (i'.val - i.val)))
  · rintro ⟨f', i'⟩ ⟨hi1, hi2, hf'⟩
    simp only [slot.sample_counts_loop0_loop0.body]
    step*
    all_goals try (exact LeAll_mono hf' (by omega))

    have h5 := LeAll_get hf' i4.val (by exact SV0!)
    rw [← i5_post] at h5
    have h6 : i6.val = i5.val + 1 := by
      simp only [i6_post, core.num.Usize.wrapping_add_val_eq, UScalar.size_UScalarTyUsize]
      rw [Nat.mod_eq_of_lt] <;> exact SV0!
    refine ⟨by exact SV0!, by exact SV0!, ?_, by exact SV0!⟩
    have heq : i7.val - i.val = (i'.val - i.val) + 1 := by exact SV0!
    rw [heq, ← Nat.add_assoc, a_post, Array.set_val_eq]
    exact LeAll_set_succ hf' _ _ (by exact SV0!)
  · exact ⟨le_refl _, by omega, by simpa using hf⟩

theorem spine_wrap1024 (a : Std.Usize) :
    (core.num.Usize.wrapping_add a 1024#usize).val - a.val ≤ 1024 := by
  rw [core.num.Usize.wrapping_add_val_eq, UScalar.size_UScalarTyUsize]
  have ha : a.val < Usize.size := by exact SV0!
  have hs : 1024 < Usize.size := by exact SV0!
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
    apply SDN!
      (measure := fun (_, w') => nw.val - w'.val)
      (inv := fun (f', w') => w.val ≤ w'.val ∧ w'.val - w.val ≤ nw.val - w.val ∧
        LeAll f'.val (c + (w'.val - w.val) * 32768))
    · rintro ⟨f', w'⟩ ⟨hw1, hw2, hf'⟩
      simp only [slot.sample_counts_loop0.body]
      step*
      repeat' (split <;> step*)
      all_goals try (exact LeAll_mono hf' (by exact SV0!))
      all_goals try exact SV0!
      refine ⟨by exact SV0!, by exact SV0!, LeAll_mono f1_post (by exact SV0!), by exact SV0!⟩
    · exact ⟨le_refl _, by omega, by simpa using hf⟩
  ·
    have hK : 32768 / nw.val = 1024 := by rw [h32]
    rw [hK]
    apply SDN!
      (measure := fun (_, w') => nw.val - w'.val)
      (inv := fun (f', w') => w.val ≤ w'.val ∧ w'.val - w.val ≤ nw.val - w.val ∧
        LeAll f'.val (c + (w'.val - w.val) * 1024))
    · rintro ⟨f', w'⟩ ⟨hw1, hw2, hf'⟩
      simp only [slot.sample_counts_loop0.body]
      step*
      repeat' (split <;> step*)
      all_goals try (exact LeAll_mono hf' (by exact SV0!))
      all_goals try (have := spine_wrap1024 a; exact SV0!)
      have := spine_wrap1024 a
      refine ⟨by exact SV0!, by exact SV0!, LeAll_mono f1_post (by exact SV0!), by exact SV0!⟩
    · exact ⟨le_refl _, by omega, by simpa using hf⟩

@[local step]
theorem sample_counts_spec (s) (f : Array Std.Usize 16#usize) (hf : LeAll f.val 0) :
    slot.sample_counts s f ⦃ fun r => LeAll r.val 32768 ⦄ := by
  rw [slot.sample_counts]
  step*
  repeat' (split <;> step*)
  all_goals exact SV0!

@[local step]
theorem classify_loop0_spec (f tot k) :
    slot.classify_loop0 f tot k ⦃ fun _ => True ⦄ := by
  rw [slot.classify_loop0]
  apply SDN!
    (measure := fun (tot_, k_) => 16 - k_.val)
    (inv := fun _ => True)
  · rintro ⟨tot_, k_⟩ _
    simp only [slot.classify_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals exact SV0!
  · trivial

@[local step]
theorem classify_loop1_spec (f : Array Std.Usize 16#usize) (tot : Std.Usize) (k) (m : Array Std.Usize 16#usize)
    (htot : 0 < tot.val) (hf : LeAll f.val 32768) (hm : LeAll m.val 32768000) :
    slot.classify_loop1 f tot k m ⦃ fun r => LeAll r.val 32768000 ⦄ := by
  rw [slot.classify_loop1]
  apply SDN!
    (measure := fun (k', _) => 16 - k'.val)
    (inv := fun (_, m') => LeAll m'.val 32768000)
  · rintro ⟨k', m'⟩ (hm' : LeAll m'.val 32768000)
    simp only [slot.classify_loop1.body]
    step*

    have h0 : i.val ≤ 32768 := by rw [i_post]; exact LeAll_get hf k'.val (by exact SV0!)
    have h1 : i1.val = i.val * 1000 := by
      simp only [i1_post, core.num.Usize.wrapping_mul_val_eq, UScalar.size_UScalarTyUsize]
      rw [Nat.mod_eq_of_lt] <;> exact SV0!
    have h2 : i2.val ≤ i1.val := by rw [i2_post]; exact Nat.div_le_self _ _
    refine ⟨?_, by exact SV0!⟩
    rw [a_post, Array.set_val_eq]
    exact LeAll_set hm' _ _ (by exact SV0!)
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
    exact SV0!

@[local step]
theorem prose_like_loop_spec (s : Slice Std.U8) (n step : Std.Usize) (cnt) (tot i : Std.Usize)
    (hn : n.val ≤ s.length) :
    slot.prose_like_loop s n step cnt tot i ⦃ fun _ => True ⦄ := by
  rw [slot.prose_like_loop]
  apply SDN!
    (measure := fun (_, tot', _) => 4096 - tot'.val)
    (inv := fun _ => True)
  · rintro ⟨cnt', tot', i'⟩ _
    simp only [slot.prose_like_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals exact SV0!
  · trivial

@[local step]
theorem prose_like_spec (s : Slice Std.U8) : slot.prose_like s ⦃ fun _ => True ⦄ := by
  rw [slot.prose_like]
  step*
  repeat' (split <;> step*)
  all_goals exact SV0!

@[local step]
theorem route_class0_spec (input : Slice Std.U8) : slot.route_class0 input ⦃ fun _ => True ⦄ := by
  rw [slot.route_class0]
  step*
  repeat' (split <;> step*)

@[local step]
theorem route_class_spec (input : Slice Std.U8) : slot.route_class input ⦃ fun _ => True ⦄ := by
  rw [slot.route_class]
  have h0 := spine_LeAll_repeat0 16#usize 0
  step*
  repeat' (split <;> step*)

@[local step]
theorem dp_plan_spec (input : Slice Std.U8) (r : Std.Usize) :
    slot.dp_plan input r ⦃ fun _ => True ⦄ := by
  rw [slot.dp_plan]
  step*
  all_goals first
    | exact SV0!
    | (have hw := dp_wadd_self input.len (by rw [← i3_post]; exact SV0!)
       simpa using hw)

theorem A_LOG_FRAC_le : LeAll slot.A_LOG_FRAC.val 64 := by
  unfold slot.A_LOG_FRAC LeAll; simp only [Array.make]; decide

theorem A_SEG_bounds : 256 ≤ slot.A_SEG.val ∧ slot.A_SEG.val ≤ 65536 ∧
    slot.A_SEG.val + 512 ≤ slot.A_SEG.val * slot.A_SAMPLE.val ∧
    slot.A_SEG.val * slot.A_SAMPLE.val ≤ 1048576 := by
  simp

theorem A_HB_bounds : 1 ≤ slot.A_HB.val ∧ slot.A_HB.val ≤ 32 := by
  simp

theorem A_BLOCK_bounds : 0 < slot.BLOCK_TOKENS.val ∧ slot.BLOCK_TOKENS.val ≤ 16384 ∧
    slot.A_MARGIN.val ≤ 65536 ∧ slot.A_SLACK.val ≠ 0 := by
  simp

theorem engA_ite_ok {α : Type} (c : Prop) [Decidable c] (a b : α) :
    (if c then (ok a : Result α) else ok b) = ok (if c then a else b) := by
  split <;> rfl

theorem engA_sat_add_val (x y : Std.Usize) :
    (core.num.Usize.saturating_add x y).val = min Std.Usize.max (x.val + y.val) := by
  have hsz : Std.Usize.max < 2 ^ UScalarTy.Usize.numBits := by
    rw [Std.Usize.max_def, Std.Usize.numBits]
    have : 0 < 2 ^ UScalarTy.Usize.numBits := Nat.two_pow_pos _
    omega
  show (BitVec.ofNat _ (min (UScalar.max UScalarTy.Usize) (x.val + y.val))).toNat = _
  rw [BitVec.toNat_ofNat, UScalar.max_USize_eq, Nat.mod_eq_of_lt (by omega)]

@[local scalar_tac core.num.Usize.saturating_add x y]
theorem engA_sat_add_val' (x y : Std.Usize) :
    (core.num.Usize.saturating_add x y).val = min Std.Usize.max (x.val + y.val) := engA_sat_add_val x y

theorem engA_ite_pair {α β : Type} (c : Prop) [Decidable c] (a a' : α) (b b' : β) :
    (if c then (a, b) else (a', b')) = (if c then a else a', if c then b else b') := by
  split <;> rfl

theorem engA_LeAll_repeat {ty : UScalarTy} (n : Std.Usize) (x : UScalar ty) (B : Nat) (h : x.val ≤ B) :
    LeAll (Array.repeat n x).val B := by
  rw [Array.repeat_val]; exact LeAll_replicate _ _ _ h

theorem engA_LeAll_set_of_eq {n : Std.Usize} {a r : Array Std.U32 n} {i : Std.Usize} {v : Std.U32} {B : Nat}
    (hr : r = a.set i v) (ha : LeAll a.val B) (hv : v.val ≤ B) : LeAll r.val B := by
  rw [hr, Array.set_val_eq]; exact LeAll_set ha _ _ hv

@[local step]
theorem a_slot_of_spec (x) :
    slot.a_slot_of x ⦃ fun _ => True ⦄ := by
  rw [slot.a_slot_of]
  step*

@[local step]
theorem a_len_slot_spec (len) :
    slot.a_len_slot len ⦃ fun r => r.val ≤ 28 ⦄ := by
  rw [slot.a_len_slot]
  split
  · step*
  · split
    · step*
    · step*
      all_goals
        have hx : x.val = len.val - 3 := by
          rw [x_post, UScalar.cast_val_mod_pow_of_inBounds_eq _ _ (by exact SV0!)]; exact SV0!
        have h1 := lz32_le_of_pow_le x 3 (by exact SV0!)
        have h2 := lz32_ge_of_lt_pow x 8 (by exact SV0!)
        subst i1_post
        exact SV0!

@[local step]
theorem a_walk_loop0_spec (lf) :
    slot.a_walk_loop0 lf 0#usize ⦃ fun r => LeAll r.val 0 ⦄ := by
  rw [slot.a_walk_loop0]
  apply SDN!
    (measure := fun (_, k) => 512 - k.val)
    (inv := fun (lf', k) => k.val ≤ 512 ∧ ∀ j (hj : j < k.val) (hl : j < lf'.val.length), (lf'.val[j]).val = 0)
  · rintro ⟨lf', k⟩ ⟨hk, hz⟩
    simp only [slot.a_walk_loop0.body]
    step*
    ·
      refine ⟨by exact SV0!, ?_, by exact SV0!⟩
      intro j hj hl
      subst a_post
      simp only [Array.set_val_eq, List.getElem_set]
      split
      · rfl
      · exact hz j (by exact SV0!) (by simpa using hl)
    ·
      intro j hl
      have : k.val = 512 := by exact SV0!
      have hl' : j < 512 := by simpa using hl
      rw [hz j (by omega) hl]
  · exact ⟨by simp, fun j hj => by simp at hj⟩

@[local step]
theorem a_walk_loop1_spec (df) :
    slot.a_walk_loop1 df 0#usize ⦃ fun r => LeAll r.val 0 ⦄ := by
  rw [slot.a_walk_loop1]
  apply SDN!
    (measure := fun (_, k) => 32 - k.val)
    (inv := fun (df', k) => k.val ≤ 32 ∧ ∀ j (hj : j < k.val) (hl : j < df'.val.length), (df'.val[j]).val = 0)
  · rintro ⟨df', k⟩ ⟨hk, hz⟩
    simp only [slot.a_walk_loop1.body]
    step*
    · refine ⟨by exact SV0!, ?_, by exact SV0!⟩
      intro j hj hl
      subst a_post
      simp only [Array.set_val_eq, List.getElem_set]
      split
      · rfl
      · exact hz j (by exact SV0!) (by simpa using hl)
    · intro j hl
      have : k.val = 32 := by exact SV0!
      have hl' : j < 32 := by simpa using hl
      rw [hz j (by omega) hl]
  · exact ⟨by simp, fun j hj => by simp at hj⟩

@[local step]
theorem a_walk_loop2_spec (s : Slice Std.U8) (ch) (lim need : Std.Usize) (lf df) (i t : Std.Usize)
    (hlim : lim.val ≤ 2 ^ 31) (hls : lim.val ≤ s.length) (hneed : need.val ≤ 2 ^ 31)
    (hlf : LeAll lf.val t.val) (hdf : LeAll df.val t.val) :
    slot.a_walk_loop2 s ch lim need lf df i t ⦃ fun r => i.val ≤ r.2.2.1.val ∧ r.2.2.2.val ≤ max t.val need.val ∧
      r.2.2.1.val ≤ max i.val (lim.val + 511) ∧ r.2.2.1.val + 511 * t.val ≤ i.val + 511 * r.2.2.2.val ⦄ := by
  rw [slot.a_walk_loop2]
  apply SDN!
    (measure := fun (_, _, _, t') => need.val - t'.val)
    (inv := fun (lf', df', i', t') => LeAll lf'.val t'.val ∧ LeAll df'.val t'.val ∧
      i.val ≤ i'.val ∧ t'.val ≤ max t.val need.val ∧
      i'.val ≤ max i.val (lim.val + 511) ∧ i'.val + 511 * t.val ≤ i.val + 511 * t'.val)
  · rintro ⟨lf', df', i', t'⟩ ⟨hlf', hdf', hi', ht', hi2', hi3'⟩
    simp only [slot.a_walk_loop2.body]
    step*

    apply WP.spec_bind (Pₘ := fun (x : Std.Array Std.U32 512#usize × Std.Array Std.U32 32#usize × Std.Usize) =>
      LeAll x.1.val (t'.val + 1) ∧ LeAll x.2.1.val (t'.val + 1) ∧ i'.val < x.2.2.val ∧ x.2.2.val ≤ i'.val + 511)
    · split
      ·
        step*
        all_goals try (have := LeAll_get hlf' i6.val (by exact SV0!))
        all_goals try (have := LeAll_get hdf' i14.val (by exact SV0!))
        all_goals try exact SV0!
        refine ⟨?_, ?_, by exact SV0!, by exact SV0!⟩
        · rw [a_post, Array.set_val_eq]; exact LeAll_set_succ hlf' _ _ (by exact SV0!)
        · rw [a1_post, Array.set_val_eq]; exact LeAll_set_succ hdf' _ _ (by exact SV0!)
      ·
        step*
        all_goals try (have := LeAll_get hlf' i5.val (by exact SV0!))
        all_goals try exact SV0!
        refine ⟨?_, LeAll_mono hdf' (by omega), by exact SV0!, by exact SV0!⟩
        rw [a_post, Array.set_val_eq]; exact LeAll_set_succ hlf' _ _ (by exact SV0!)
    · rintro ⟨lf1, df1, i3⟩ ⟨h1, h2, h3, h4⟩
      step*
      refine ⟨?_, ?_, by exact SV0!, by exact SV0!, by exact SV0!, by exact SV0!, by exact SV0!⟩
      · rw [show t1.val = t'.val + 1 by exact SV0!]; exact h1
      · rw [show t1.val = t'.val + 1 by exact SV0!]; exact h2
  · exact ⟨hlf, hdf, le_refl _, by omega, by omega, by omega⟩

@[local step]
theorem a_walk_spec (s : Slice Std.U8) (ch) (p0 lim need : Std.Usize) (lf df)
    (hlim : lim.val ≤ 2 ^ 31) (hls : lim.val ≤ s.length) (hneed : need.val ≤ 2 ^ 31) :
    slot.a_walk s ch p0 lim need lf df ⦃ fun r => p0.val ≤ r.1.1.val ∧ r.1.2.val ≤ need.val ∧
      r.1.1.val ≤ max p0.val (lim.val + 511) ∧ r.1.1.val ≤ p0.val + 511 * r.1.2.val ⦄ := by
  rw [slot.a_walk]
  step*
  repeat' (split <;> step*)
  all_goals exact SV0!

@[local step]
theorem a_dp_pass_loop0_spec (pe : Std.Usize) (cost) (cl z : Std.Usize) (hpe : pe.val ≤ 2 ^ 31) (hcl : cl.val = cost.length) :
    slot.a_dp_pass_loop0 pe cost cl z ⦃ fun r => r.length = cost.length ⦄ := by
  rw [slot.a_dp_pass_loop0]
  apply SDN!
    (measure := fun (_, z_) => cl.val - z_.val)
    (inv := fun (cost_, _) => cost_.length = cost.length)
  · rintro ⟨cost_, z_⟩ hinv
    simp only [slot.a_dp_pass_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals exact SV0!
  · rfl

@[local step]
theorem a_dp_pass_loop1_loop0_loop0_spec (lc) (cost : alloc.vec.Vec Std.U32) (stop base mbest at0 l) (hstop : stop.val < cost.length) :
    slot.a_dp_pass_loop1_loop0_loop0 lc cost stop base mbest at0 l ⦃ fun _ => True ⦄ := by
  rw [slot.a_dp_pass_loop1_loop0_loop0]
  apply SDN!
    (measure := fun (mbest_, at0_, l_) => stop.val + 1 - at0_.val)
    (inv := fun _ => True)
  · rintro ⟨mbest_, at0_, l_⟩ _
    simp only [slot.a_dp_pass_loop1_loop0_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals exact SV0!
  · trivial

@[local step]
theorem a_dp_pass_loop1_loop0_loop1_spec (lc) (cost : alloc.vec.Vec Std.U32) (stop base mbest at0 l) (hstop : stop.val < cost.length) :
    slot.a_dp_pass_loop1_loop0_loop1 lc cost stop base mbest at0 l ⦃ fun _ => True ⦄ := by
  rw [slot.a_dp_pass_loop1_loop0_loop1]
  apply SDN!
    (measure := fun (mbest_, at0_, l_) => stop.val + 1 - at0_.val)
    (inv := fun _ => True)
  · rintro ⟨mbest_, at0_, l_⟩ _
    simp only [slot.a_dp_pass_loop1_loop0_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals exact SV0!
  · trivial

@[local step]
theorem a_dp_pass_loop1_loop0_spec (mb lc dc) (cost : alloc.vec.Vec Std.U32) (cl i : Std.Usize) (bias best bd) (prev pd : Std.Usize) (j top : Std.Usize)
    (hcl : cl.val = cost.length) (hi : i.val ≤ 2 ^ 31) (htop : top.val ≤ mb.length)
    (hprev : prev.val ≤ i.val + 258) (hpd : pd.val ≤ 32768) (hbd : bd.val ≤ 32767) :
    slot.a_dp_pass_loop1_loop0 mb lc dc cost cl i bias best bd prev pd j top ⦃ fun r =>
      prev.val ≤ r.2.2.1.val ∧ r.2.2.1.val ≤ i.val + 258 ∧ r.2.2.2.val ≤ 32768 ∧ r.2.1.val ≤ 32767 ⦄ := by
  rw [slot.a_dp_pass_loop1_loop0]
  apply SDN!
    (measure := fun (_, _, _, _, j_) => top.val - j_.val)
    (inv := fun (_, bd_, prev_, pd_, _) => prev.val ≤ prev_.val ∧ prev_.val ≤ i.val + 258 ∧
      pd_.val ≤ 32768 ∧ bd_.val ≤ 32767)
  · rintro ⟨best_, bd_, prev_, pd_, j_⟩ ⟨hp0, hp1, hpd_, hbd_⟩
    simp only [slot.a_dp_pass_loop1_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals exact SV0!
  · exact ⟨le_refl _, hprev, hpd, hbd⟩

@[local step]
theorem a_dp_pass_loop1_loop1_spec (lc) (cost : alloc.vec.Vec Std.U32) (stop base mbest at0 l) (hstop : stop.val < cost.length) :
    slot.a_dp_pass_loop1_loop1 lc cost stop base mbest at0 l ⦃ fun _ => True ⦄ := by
  rw [slot.a_dp_pass_loop1_loop1]
  apply SDN!
    (measure := fun (mbest_, at0_, l_) => stop.val + 1 - at0_.val)
    (inv := fun _ => True)
  · rintro ⟨mbest_, at0_, l_⟩ _
    simp only [slot.a_dp_pass_loop1_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals exact SV0!
  · trivial

set_option maxHeartbeats 4000000 in
@[local step]
theorem a_dp_pass_loop1_spec (s : Slice Std.U8) (mp mb : alloc.vec.Vec Std.U32) (p0 lit lc dc) (cost ch : alloc.vec.Vec Std.U32)
    (cl i e xl xd : Std.Usize)
    (hcl : cl.val = cost.length) (hi : i.val < cl.val) (hmp : i.val < mp.length) (hs : i.val ≤ s.length)
    (hch : i.val ≤ ch.length) (hi31 : i.val ≤ 2 ^ 31) (hxl : xl.val ≤ 258) (hxd : xd.val ≤ 32768) :
    slot.a_dp_pass_loop1 s mp mb p0 lit lc dc cost ch cl i e xl xd ⦃ fun _ => True ⦄ := by
  rw [slot.a_dp_pass_loop1]
  apply SDN!
    (measure := fun (_, _, i_, _, _, _) => i_.val)
    (inv := fun ((cost_ : alloc.vec.Vec Std.U32), (ch_ : alloc.vec.Vec Std.U32), (i_ : Std.Usize), _,
        (xl_ : Std.Usize), (xd_ : Std.Usize)) =>
      cost_.length = cl.val ∧ ch_.length = ch.length ∧ i_.val ≤ i.val ∧ xl_.val ≤ 258 ∧ xd_.val ≤ 32768)
  · rintro ⟨cost_, ch_, i_, e_, xl_, xd_⟩ ⟨hc_, hch_, hi_, hxl_, hxd_⟩
    simp only [slot.a_dp_pass_loop1.body]
    step*

    apply WP.spec_bind (Pₘ := fun (top : Std.Usize) => top.val ≤ mb.length)
    · split <;> step* <;> exact SV0!
    rintro top htop
    step*
    apply WP.spec_bind (Pₘ := fun (el : Std.Usize) => el.val ≤ 258)
    · split <;> step* <;> exact SV0!
    rintro el hel
    step*

    all_goals
      try (
        apply WP.spec_bind (Pₘ := fun (x : Std.U32 × Std.U32) => x.2.val ≤ 32767)
        · split <;> step* <;> exact SV0!
        rintro ⟨best2, bd1⟩ hbd1
        step*)
    all_goals
      apply WP.spec_bind (Pₘ := fun (x : alloc.vec.Vec Std.U32 × Std.U32) => x.1.length = cost_.length)
      · split <;> step* <;> exact SV0!
      rintro ⟨cost1, i23⟩ hc1
      step*
      exact SV0!
  · exact ⟨hcl.symm, rfl, le_refl _, hxl, hxd⟩

@[local step]
theorem a_dp_pass_spec (s : Slice Std.U8) (mp mb) (p0 pe : Std.Usize) (lit lc dc) (cost ch)
    (hpe : pe.val ≤ 2 ^ 31) :
    slot.a_dp_pass s mp mb p0 pe lit lc dc cost ch ⦃ fun _ => True ⦄ := by
  rw [slot.a_dp_pass]
  step*
  repeat' (split <;> step*)
  all_goals exact SV0!

@[local step]
theorem a_sample_pass_loop0_loop0_spec (lf zf b) :
    slot.a_sample_pass_loop0_loop0 lf zf b ⦃ fun _ => True ⦄ := by
  rw [slot.a_sample_pass_loop0_loop0]
  apply SDN!
    (measure := fun (zf_, b_) => 512 - b_.val)
    (inv := fun _ => True)
  · rintro ⟨zf_, b_⟩ _
    simp only [slot.a_sample_pass_loop0_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals exact SV0!
  · trivial

@[local step]
theorem a_sample_pass_loop0_loop1_spec (df zd b) :
    slot.a_sample_pass_loop0_loop1 df zd b ⦃ fun _ => True ⦄ := by
  rw [slot.a_sample_pass_loop0_loop1]
  apply SDN!
    (measure := fun (zd_, b_) => 32 - b_.val)
    (inv := fun _ => True)
  · rintro ⟨zd_, b_⟩ _
    simp only [slot.a_sample_pass_loop0_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals exact SV0!
  · trivial

@[local step]
theorem a_sample_pass_loop0_spec (s : Slice Std.U8) (mp mb) (pe : Std.Usize) (lit lc dc cost ch lf df zf zd) (sb st a : Std.Usize)
    (hpe : pe.val ≤ 2 ^ 30) (hps : pe.val ≤ s.length) (hsb : sb.val ≤ a.val) (hst : st.val ≤ a.val)
    (ha : a.val ≤ pe.val + slot.A_SEG.val * slot.A_SAMPLE.val) :
    slot.a_sample_pass_loop0 s mp mb pe lit lc dc cost ch lf df zf zd sb st a ⦃ fun _ => True ⦄ := by
  have hseg := A_SEG_bounds
  rw [slot.a_sample_pass_loop0]
  apply SDN!
    (measure := fun (_, _, _, _, _, _, _, _, a_) => pe.val - a_.val)
    (inv := fun (_, _, _, _, _, _, sb_, st_, a_) => sb_.val ≤ a_.val ∧ st_.val ≤ a_.val ∧
      a_.val ≤ pe.val + slot.A_SEG.val * slot.A_SAMPLE.val)
  · rintro ⟨cost_, ch_, lf_, df_, zf_, zd_, sb_, st_, a_⟩ ⟨hsb_, hst_, ha_⟩
    simp only [slot.a_sample_pass_loop0.body]
    step*

    cases ‹Std.Usize × Std.Usize›
    step*
    all_goals exact SV0!
  · exact ⟨hsb, hst, ha⟩

@[local step]
theorem a_sample_pass_loop1_spec (lf zf b) :
    slot.a_sample_pass_loop1 lf zf b ⦃ fun _ => True ⦄ := by
  rw [slot.a_sample_pass_loop1]
  apply SDN!
    (measure := fun (lf_, b_) => 512 - b_.val)
    (inv := fun _ => True)
  · rintro ⟨lf_, b_⟩ _
    simp only [slot.a_sample_pass_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals exact SV0!
  · trivial

@[local step]
theorem a_sample_pass_loop2_spec (df zd b) :
    slot.a_sample_pass_loop2 df zd b ⦃ fun _ => True ⦄ := by
  rw [slot.a_sample_pass_loop2]
  apply SDN!
    (measure := fun (df_, b_) => 32 - b_.val)
    (inv := fun _ => True)
  · rintro ⟨df_, b_⟩ _
    simp only [slot.a_sample_pass_loop2.body]
    step*
    repeat' (split <;> step*)
    all_goals exact SV0!
  · trivial

@[local step]
theorem a_sample_pass_spec (s : Slice Std.U8) (mp mb) (p0 pe : Std.Usize) (lit lc dc cost ch lf df)
    (hpe : pe.val ≤ 2 ^ 30) (hps : pe.val ≤ s.length) (hp0 : p0.val ≤ pe.val) :
    slot.a_sample_pass s mp mb p0 pe lit lc dc cost ch lf df ⦃ fun _ => True ⦄ := by
  have hseg := A_SEG_bounds
  rw [slot.a_sample_pass]
  step*
  repeat' (split <;> step*)
  all_goals exact SV0!

@[local step]
theorem a_add_counts_loop0_spec (dst a b k) :
    slot.a_add_counts_loop0 dst a b k ⦃ fun _ => True ⦄ := by
  rw [slot.a_add_counts_loop0]
  apply SDN!
    (measure := fun (dst_, k_) => 512 - k_.val)
    (inv := fun _ => True)
  · rintro ⟨dst_, k_⟩ _
    simp only [slot.a_add_counts_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals exact SV0!
  · trivial

@[local step]
theorem a_add_counts_loop1_spec (dd x y k) :
    slot.a_add_counts_loop1 dd x y k ⦃ fun _ => True ⦄ := by
  rw [slot.a_add_counts_loop1]
  apply SDN!
    (measure := fun (dd_, k_) => 32 - k_.val)
    (inv := fun _ => True)
  · rintro ⟨dd_, k_⟩ _
    simp only [slot.a_add_counts_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals exact SV0!
  · trivial

@[local step]
theorem a_add_counts_spec (dst a b dd x y) :
    slot.a_add_counts dst a b dd x y ⦃ fun _ => True ⦄ := by
  rw [slot.a_add_counts]
  step*
  repeat' (split <;> step*)
  all_goals exact SV0!

@[local step]
theorem a_lg64_spec (x) :
    slot.a_lg64 x ⦃ fun r => r.val ≤ 2048 ⦄ := by
  rw [slot.a_lg64]
  have hlz := lz32_bound x
  have htab := A_LOG_FRAC_le
  step*
  repeat' (split <;> step*)
  all_goals try (have := LeAll_get htab i3.val (by exact SV0!))
  all_goals exact SV0!

@[local step]
theorem a_sym_cost_spec (f : Std.U32) (g : Std.U32) (hg : g.val ≤ 65536) :
    slot.a_sym_cost f g ⦃ fun r => r.val ≤ 1152 ⦄ := by
  rw [slot.a_sym_cost]
  step*
  repeat' (split <;> step*)
  all_goals exact SV0!

@[local step]
theorem a_dist_extra_spec (slt : Std.Usize) :
    slot.a_dist_extra slt ⦃ fun r => r.val ≤ slt.val / 2 ⦄ := by
  rw [slot.a_dist_extra]
  step*
  repeat' (split <;> step*)
  all_goals exact SV0!

@[local step]
theorem a_len_extra_spec (slt) :
    slot.a_len_extra slt ⦃ fun r => r.val ≤ 5 ⦄ := by
  rw [slot.a_len_extra]
  step*
  repeat' (split <;> step*)
  all_goals exact SV0!

@[local step]
theorem a_set_costs_loop0_spec (lf tl i) :
    slot.a_set_costs_loop0 lf tl i ⦃ fun _ => True ⦄ := by
  rw [slot.a_set_costs_loop0]
  apply SDN!
    (measure := fun (tl_, i_) => 286 - i_.val)
    (inv := fun _ => True)
  · rintro ⟨tl_, i_⟩ _
    simp only [slot.a_set_costs_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals exact SV0!
  · trivial

@[local step]
theorem a_set_costs_loop1_spec (df i td) :
    slot.a_set_costs_loop1 df i td ⦃ fun _ => True ⦄ := by
  rw [slot.a_set_costs_loop1]
  apply SDN!
    (measure := fun (i_, td_) => 30 - i_.val)
    (inv := fun _ => True)
  · rintro ⟨i_, td_⟩ _
    simp only [slot.a_set_costs_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals exact SV0!
  · trivial

@[local step]
theorem a_set_costs_loop2_spec (lf lit i) (gl : Std.U32) (hgl : gl.val ≤ 65536) :
    slot.a_set_costs_loop2 lf lit i gl ⦃ fun _ => True ⦄ := by
  rw [slot.a_set_costs_loop2]
  apply SDN!
    (measure := fun (lit_, i_) => 256 - i_.val)
    (inv := fun _ => True)
  · rintro ⟨lit_, i_⟩ _
    simp only [slot.a_set_costs_loop2.body]
    step*
    repeat' (split <;> step*)
    all_goals exact SV0!
  · trivial

@[local step]
theorem a_set_costs_loop3_spec (lf lc i) (gl : Std.U32) (hgl : gl.val ≤ 65536) :
    slot.a_set_costs_loop3 lf lc i gl ⦃ fun _ => True ⦄ := by
  rw [slot.a_set_costs_loop3]
  apply SDN!
    (measure := fun (lc_, i_) => 258 + 1 - i_.val)
    (inv := fun _ => True)
  · rintro ⟨lc_, i_⟩ _
    simp only [slot.a_set_costs_loop3.body]
    step*
    repeat' (split <;> step*)
    all_goals exact SV0!
  · trivial

@[local step]
theorem a_set_costs_loop4_spec (df dc) (i : Std.Usize) (gd : Std.U32) (hgd : gd.val ≤ 65536) :
    slot.a_set_costs_loop4 df dc i gd ⦃ fun _ => True ⦄ := by
  rw [slot.a_set_costs_loop4]
  apply SDN!
    (measure := fun (dc_, i_) => 30 - i_.val)
    (inv := fun _ => True)
  · rintro ⟨dc_, i_⟩ _
    simp only [slot.a_set_costs_loop4.body]
    step*
    repeat' (split <;> step*)
    all_goals exact SV0!
  · trivial

@[local step]
theorem a_set_costs_spec (lf df lit lc dc) :
    slot.a_set_costs lf df lit lc dc ⦃ fun _ => True ⦄ := by
  rw [slot.a_set_costs]
  step*
  repeat' (split <;> step*)
  all_goals exact SV0!

@[local step]
theorem a_first_model_loop0_spec (s : Slice Std.U8) (lf) (m i : Std.Usize) (hm : m.val ≤ s.length) (hm2 : m.val ≤ 65536)
    (hlf : LeAll lf.val i.val) :
    slot.a_first_model_loop0 s lf m i ⦃ fun _ => True ⦄ := by
  rw [slot.a_first_model_loop0]
  apply SDN!
    (measure := fun (_, i_) => m.val - i_.val)
    (inv := fun (lf_, i_) => LeAll lf_.val i_.val)
  · rintro ⟨lf_, i_⟩ hlf_
    simp only [slot.a_first_model_loop0.body]
    step*
    all_goals try (have := LeAll_get hlf_ i2.val (by exact SV0!))
    all_goals try exact SV0!
    refine ⟨?_, by exact SV0!⟩
    rw [show i5.val = i_.val + 1 by exact SV0!, a_post, Array.set_val_eq]
    exact LeAll_set_succ hlf_ _ _ (by exact SV0!)
  · exact hlf

@[local step]
theorem a_first_model_loop1_spec (lf i) :
    slot.a_first_model_loop1 lf i ⦃ fun _ => True ⦄ := by
  rw [slot.a_first_model_loop1]
  apply SDN!
    (measure := fun (lf_, i_) => 29 - i_.val)
    (inv := fun _ => True)
  · rintro ⟨lf_, i_⟩ _
    simp only [slot.a_first_model_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals exact SV0!
  · trivial

@[local step]
theorem a_first_model_loop2_spec (df i) :
    slot.a_first_model_loop2 df i ⦃ fun _ => True ⦄ := by
  rw [slot.a_first_model_loop2]
  apply SDN!
    (measure := fun (df_, i_) => 30 - i_.val)
    (inv := fun _ => True)
  · rintro ⟨df_, i_⟩ _
    simp only [slot.a_first_model_loop2.body]
    step*
    repeat' (split <;> step*)
    all_goals exact SV0!
  · trivial

@[local step]
theorem a_first_model_spec (s lit lc dc) :
    slot.a_first_model s lit lc dc ⦃ fun _ => True ⦄ := by
  rw [slot.a_first_model]
  step*
  repeat' (split <;> step*)
  all_goals exact engA_LeAll_repeat _ _ _ (by simp)

@[local step]
theorem a_kraft_fix_loop_spec (sym m) (len : Array Std.U32 512#usize) (kraft q) (hlen : LeAll len.val 15) :
    slot.a_kraft_fix_loop sym m len kraft q ⦃ fun r => LeAll r.val 15 ⦄ := by
  rw [slot.a_kraft_fix_loop]
  apply SDN!
    (measure := fun ((len_ : Array Std.U32 512#usize), _, (q_ : Std.Usize)) =>
      (512 - q_.val) * 16 + (15 - (len_.val[(sym.val[q_.val]!).val % 512]!).val))
    (inv := fun (len_, _, _) => LeAll len_.val 15)
  · rintro ⟨len_, kraft_, q_⟩ hlen_
    dsimp only at hlen_
    simp only [slot.a_kraft_fix_loop.body]
    step*
    ·
      have hq : (sym.val[q_.val]!).val % 512 = s2.val := by
        rw [getElem!_pos sym.val q_.val (by exact SV0!), ← i_post]; exact SV0!
      have ha : a.val[s2.val]! = i5 := by
        rw [a_post, Array.set_val_eq, getElem!_pos _ _ (by simp; exact SV0!), List.getElem_set_self]
      have hl : len_.val[s2.val]! = i2 := by
        rw [getElem!_pos _ _ (by exact SV0!), ← i2_post]
      refine ⟨?_, ?_⟩
      · rw [a_post, Array.set_val_eq]; exact LeAll_set hlen_ _ _ (by exact SV0!)
      · rw [hq, ha, hl]; exact SV0!
    ·
      exact ⟨hlen_, by exact SV0!⟩
  · exact hlen

@[local step]
theorem a_kraft_fix_spec (sym m) (len : Array Std.U32 512#usize) (kraft0) (hlen : LeAll len.val 15) :
    slot.a_kraft_fix sym m len kraft0 ⦃ fun r => LeAll r.val 15 ⦄ := by
  unfold slot.a_kraft_fix
  step*

@[local step]
theorem a_lighter_spec (w a) (b : Std.Usize) (m k) (hb : b.val ≤ 4096) :
    slot.a_lighter w a b m k ⦃ fun r => r.2.1.val ≤ a.val + 1 ∧ r.2.2.val ≤ b.val + 1 ⦄ := by
  rw [slot.a_lighter]
  step*
  repeat' (split <;> step*)
  all_goals exact SV0!

@[local step]
theorem a_sorted_insert_loop_spec (sym freq fv) (j : Std.Usize) (hj : j.val < 512) :
    slot.a_sorted_insert_loop sym freq fv j ⦃ fun r => r.2.val < 512 ⦄ := by
  rw [slot.a_sorted_insert_loop]
  apply SDN!
    (measure := fun (_, j_) => j_.val)
    (inv := fun (_, j_) => j_.val < 512)
  · rintro ⟨sym_, j_⟩ hinv
    simp only [slot.a_sorted_insert_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals exact SV0!
  · exact hj

@[local step]
theorem a_sorted_insert_spec (sym freq m v) :
    slot.a_sorted_insert sym freq m v ⦃ fun _ => True ⦄ := by
  rw [slot.a_sorted_insert]
  step*
  repeat' (split <;> step*)
  all_goals exact SV0!

@[local step]
theorem a_huff_lengths_loop0_spec (freq n) (len : Array Std.U32 512#usize) (sym) (m i : Std.Usize)
    (hm : m.val ≤ i.val) (hi : i.val ≤ 512) (hlen : LeAll len.val 15) :
    slot.a_huff_lengths_loop0 freq n len sym m i ⦃ fun r => r.2.2.val ≤ 512 ∧ LeAll r.1.val 15 ⦄ := by
  rw [slot.a_huff_lengths_loop0]
  apply SDN!
    (measure := fun (_, _, _, i_) => 512 - i_.val)
    (inv := fun (len_, _, m_, i_) => m_.val ≤ i_.val ∧ i_.val ≤ 512 ∧ LeAll len_.val 15)
  · rintro ⟨len_, sym_, m_, i_⟩ ⟨hm_, hi_, hlen_⟩
    simp only [slot.a_huff_lengths_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals
      refine ⟨by exact SV0!, by exact SV0!, ?_, by exact SV0!⟩
      rw [a_post, Array.set_val_eq]; exact LeAll_set hlen_ _ _ (by exact SV0!)
  · exact ⟨hm, hi, hlen⟩

@[local step]
theorem a_huff_lengths_loop1_spec (freq sym m i w) :
    slot.a_huff_lengths_loop1 freq sym m i w ⦃ fun _ => True ⦄ := by
  rw [slot.a_huff_lengths_loop1]
  apply SDN!
    (measure := fun (i_, w_) => m.val - i_.val)
    (inv := fun _ => True)
  · rintro ⟨i_, w_⟩ _
    simp only [slot.a_huff_lengths_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals exact SV0!
  · trivial

@[local step]
theorem a_huff_lengths_loop2_spec (m : Std.Usize) (w par) (a b k : Std.Usize) (hm : m.val ≤ 512)
    (ha : a.val ≤ 2 * k.val) (hb : b.val ≤ 2 * k.val) (hk : k.val ≤ 1024) :
    slot.a_huff_lengths_loop2 m w par a b k ⦃ fun r => r.2.val ≤ 1024 ⦄ := by
  rw [slot.a_huff_lengths_loop2]
  apply SDN!
    (measure := fun (_, _, _, _, k_) => 1024 - k_.val)
    (inv := fun (_, _, a_, b_, k_) => a_.val ≤ 2 * k_.val ∧ b_.val ≤ 2 * k_.val ∧ k_.val ≤ 1024)
  · rintro ⟨w_, par_, a_, b_, k_⟩ ⟨ha_, hb_, hk_⟩
    simp only [slot.a_huff_lengths_loop2.body]
    step*
    repeat' (split <;> step*)
    all_goals exact SV0!
  · exact ⟨ha, hb, hk⟩

@[local step]
theorem a_huff_lengths_loop3_spec (par d j) :
    slot.a_huff_lengths_loop3 par d j ⦃ fun _ => True ⦄ := by
  rw [slot.a_huff_lengths_loop3]
  apply SDN!
    (measure := fun (d_, j_) => j_.val)
    (inv := fun _ => True)
  · rintro ⟨d_, j_⟩ _
    simp only [slot.a_huff_lengths_loop3.body]
    step*
    repeat' (split <;> step*)
    all_goals exact SV0!
  · trivial

@[local step]
theorem a_huff_lengths_loop4_spec (len : Array Std.U32 512#usize) (sym m i d kraft) (hlen : LeAll len.val 15) :
    slot.a_huff_lengths_loop4 len sym m i d kraft ⦃ fun r => LeAll r.1.val 15 ⦄ := by
  rw [slot.a_huff_lengths_loop4]
  apply SDN!
    (measure := fun (_, i_, _) => m.val - i_.val)
    (inv := fun (len_, _, _) => LeAll len_.val 15)
  · rintro ⟨len_, i_, kraft_⟩ hlen_
    dsimp only at hlen_
    simp only [slot.a_huff_lengths_loop4.body]
    step*
    repeat' (split <;> step*)
    all_goals try exact SV0!
    all_goals
      refine ⟨?_, by exact SV0!⟩
      rw [a_post, Array.set_val_eq]; exact LeAll_set hlen_ _ _ (by exact SV0!)
  · exact hlen

@[local step]
theorem a_huff_lengths_spec (freq n) (len : Array Std.U32 512#usize) (hlen : LeAll len.val 15) :
    slot.a_huff_lengths freq n len ⦃ fun r => LeAll r.val 15 ⦄ := by
  rw [slot.a_huff_lengths]
  step*
  repeat' (split <;> step*)
  all_goals try exact SV0!
  all_goals apply engA_LeAll_set_of_eq (by assumption) (by assumption) (by exact SV0!)

@[local step]
theorem a_set_costs_huff_loop0_spec (lf0 lf z) :
    slot.a_set_costs_huff_loop0 lf0 lf z ⦃ fun _ => True ⦄ := by
  rw [slot.a_set_costs_huff_loop0]
  apply SDN!
    (measure := fun (lf_, z_) => 286 - z_.val)
    (inv := fun _ => True)
  · rintro ⟨lf_, z_⟩ _
    simp only [slot.a_set_costs_huff_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals exact SV0!
  · trivial

@[local step]
theorem a_set_costs_huff_loop1_spec (df dd i) :
    slot.a_set_costs_huff_loop1 df dd i ⦃ fun _ => True ⦄ := by
  rw [slot.a_set_costs_huff_loop1]
  apply SDN!
    (measure := fun (dd_, i_) => 30 - i_.val)
    (inv := fun _ => True)
  · rintro ⟨dd_, i_⟩ _
    simp only [slot.a_set_costs_huff_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals exact SV0!
  · trivial

@[local step]
theorem a_set_costs_huff_loop2_spec (lf i tl) :
    slot.a_set_costs_huff_loop2 lf i tl ⦃ fun _ => True ⦄ := by
  rw [slot.a_set_costs_huff_loop2]
  apply SDN!
    (measure := fun (i_, tl_) => 286 - i_.val)
    (inv := fun _ => True)
  · rintro ⟨i_, tl_⟩ _
    simp only [slot.a_set_costs_huff_loop2.body]
    step*
    repeat' (split <;> step*)
    all_goals exact SV0!
  · trivial

@[local step]
theorem a_set_costs_huff_loop3_spec (df i td) :
    slot.a_set_costs_huff_loop3 df i td ⦃ fun _ => True ⦄ := by
  rw [slot.a_set_costs_huff_loop3]
  apply SDN!
    (measure := fun (i_, td_) => 30 - i_.val)
    (inv := fun _ => True)
  · rintro ⟨i_, td_⟩ _
    simp only [slot.a_set_costs_huff_loop3.body]
    step*
    repeat' (split <;> step*)
    all_goals exact SV0!
  · trivial

@[local step]
theorem a_set_costs_huff_loop4_spec (lit) (hl : Array Std.U32 512#usize) (i) (ul : Std.U32) (hhl : LeAll hl.val 15) :
    slot.a_set_costs_huff_loop4 lit hl i ul ⦃ fun _ => True ⦄ := by
  rw [slot.a_set_costs_huff_loop4]
  apply SDN!
    (measure := fun (_, i_) => 256 - i_.val)
    (inv := fun _ => True)
  · rintro ⟨lit_, i_⟩ _
    simp only [slot.a_set_costs_huff_loop4.body]
    step*
    repeat' (split <;> step*)
    all_goals try (have := LeAll_get hhl i_.val (by exact SV0!))
    all_goals exact SV0!
  · trivial

@[local step]
theorem a_set_costs_huff_loop5_spec (lc) (hl : Array Std.U32 512#usize) (i) (ul : Std.U32) (hhl : LeAll hl.val 15) (hul : ul.val ≤ 1152) :
    slot.a_set_costs_huff_loop5 lc hl i ul ⦃ fun _ => True ⦄ := by
  rw [slot.a_set_costs_huff_loop5]
  apply SDN!
    (measure := fun (_, i_) => 259 - i_.val)
    (inv := fun _ => True)
  · rintro ⟨lc_, i_⟩ _
    simp only [slot.a_set_costs_huff_loop5.body]
    step*
    repeat' (split <;> step*)
    all_goals try (have := LeAll_get hhl i2.val (by exact SV0!))
    all_goals exact SV0!
  · trivial

@[local step]
theorem a_set_costs_huff_loop6_spec (dc) (i : Std.Usize) (hd : Array Std.U32 512#usize) (ud : Std.U32) (hhd : LeAll hd.val 15) (hud : ud.val ≤ 1152) :
    slot.a_set_costs_huff_loop6 dc i hd ud ⦃ fun _ => True ⦄ := by
  rw [slot.a_set_costs_huff_loop6]
  apply SDN!
    (measure := fun (_, i_) => 30 - i_.val)
    (inv := fun _ => True)
  · rintro ⟨dc_, i_⟩ _
    simp only [slot.a_set_costs_huff_loop6.body]
    step*
    repeat' (split <;> step*)
    all_goals try (have := LeAll_get hhd i_.val (by exact SV0!))
    all_goals exact SV0!
  · trivial

@[local step]
theorem a_set_costs_huff_spec (lf0 df lit lc dc) :
    slot.a_set_costs_huff lf0 df lit lc dc ⦃ fun _ => True ⦄ := by
  rw [slot.a_set_costs_huff]
  step*
  all_goals exact engA_LeAll_repeat _ _ _ (by simp)

@[local step]
theorem a_shared_loop_spec (s : Slice Std.U8) (a b lim : Std.Usize) (k)
    (ha : a.val + lim.val ≤ s.length) (hb : b.val + lim.val ≤ s.length) :
    slot.a_shared_loop s a b lim k ⦃ fun _ => True ⦄ := by
  rw [slot.a_shared_loop]
  apply SDN!
    (measure := fun k_ => lim.val - k_.val)
    (inv := fun _ => True)
  · rintro k_ _
    simp only [slot.a_shared_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals exact SV0!
  · trivial

@[local step]
theorem a_shared_spec (s : Slice Std.U8) (a b lim : Std.Usize)
    (ha : a.val + lim.val ≤ s.length) (hb : b.val + lim.val ≤ s.length) :
    slot.a_shared s a b lim ⦃ fun _ => True ⦄ := by
  rw [slot.a_shared]
  step*
  repeat' (split <;> step*)
  all_goals exact SV0!

@[local step]
theorem a_word_at_spec (s) (i : Std.Usize) (hi : i.val ≤ 2 ^ 31) :
    slot.a_word_at s i ⦃ fun _ => True ⦄ := by
  rw [slot.a_word_at]
  step*
  repeat' (split <;> step*)
  all_goals exact SV0!

@[local step]
theorem a_word_pair_spec (s) (a b : Std.Usize) (ha : a.val ≤ 2 ^ 31) (hb : b.val ≤ 2 ^ 31) :
    slot.a_word_pair s a b ⦃ fun _ => True ⦄ := by
  rw [slot.a_word_pair]
  step*
  repeat' (split <;> step*)
  all_goals exact SV0!

@[local step]
theorem a_probe_loop_spec (s) (p q k : Std.Usize) (w) (hp : p.val ≤ 2 ^ 30) (hq : q.val ≤ 2 ^ 30) (hk : k.val ≤ 258) :
    slot.a_probe_loop s p q k w ⦃ fun r => r.1.val ≤ 258 ⦄ := by
  rw [slot.a_probe_loop]
  apply SDN!
    (measure := fun (k_, _) => 258 - k_.val)
    (inv := fun (k_, _) => k_.val ≤ 258)
  · rintro ⟨k_, ⟨w0, w1⟩⟩ hinv
    simp only [slot.a_probe_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals exact SV0!
  · exact hk

@[local step]
theorem a_probe_spec (s) (p q k : Std.Usize) (hp : p.val ≤ 2 ^ 30) (hq : q.val ≤ 2 ^ 30) (hk : k.val ≤ 258) :
    slot.a_probe s p q k ⦃ fun r => r.1.val ≤ 258 ⦄ := by
  rw [slot.a_probe]
  step*
  repeat' (split <;> step*)
  all_goals exact SV0!

@[local step]
theorem a_tree_insert_loop_spec (s : Slice Std.U8) (kid) (pos depth oldest : Std.Usize) (mb) (cur best lo_at hi_at lo_len hi_len steps : Std.Usize)
    (hpos : pos.val + 266 ≤ s.length) (hn26 : s.length < 67108864) (hlo : lo_len.val ≤ 258) (hhi : hi_len.val ≤ 258) (hbest : 2 ≤ best.val) :
    slot.a_tree_insert_loop s kid pos depth mb oldest cur best lo_at hi_at lo_len hi_len steps ⦃ fun _ => True ⦄ := by
  rw [slot.a_tree_insert_loop]
  apply SDN!
    (measure := fun (_, _, _, _, _, _, _, _, steps_) => depth.val - steps_.val)
    (inv := fun (_, _, _, best_, _, _, lo_len_, hi_len_, _) => lo_len_.val ≤ 258 ∧ hi_len_.val ≤ 258 ∧ 2 ≤ best_.val)
  · rintro ⟨kid_, mb_, cur_, best_, lo_at_, hi_at_, lo_len_, hi_len_, steps_⟩ ⟨hlo_, hhi_, hbest_⟩
    simp only [slot.a_tree_insert_loop.body, engA_ite_ok]
    step*
    · split <;> omega

    apply WP.spec_bind (Pₘ := fun (x : alloc.vec.Vec Std.U32 × Std.Usize) => 2 ≤ x.2.val)
    · split
      · step*
        repeat' (split <;> step*)
        all_goals exact SV0!
      · step*
    rintro ⟨mb1, best1⟩ hb1
    step*

    apply WP.spec_bind (Pₘ := fun (x : Std.Array Std.U32 65536#usize × Std.Usize × Std.Usize × Std.Usize ×
        Std.Usize × Std.Usize) => x.2.2.2.2.1.val ≤ 258 ∧ x.2.2.2.2.2.val ≤ 258)
    · repeat' (split <;> step*)
      all_goals exact SV0!
    rintro ⟨kid1, cur1, lo_at1, hi_at1, lo_len2, hi_len1⟩ ⟨hl2, hh1⟩
    step*
    all_goals exact SV0!
  · exact ⟨hlo, hhi, hbest⟩

@[local step]
theorem a_tree_insert_spec (s : Slice Std.U8) (head kid h3 rct) (pos : Std.Usize) (pre depth mb) (hpos : pos.val + 266 ≤ s.length)
    (hn26 : s.length < 67108864) :
    slot.a_tree_insert s head kid h3 rct pos pre depth mb ⦃ fun _ => True ⦄ := by
  obtain ⟨q, t, h, c3, cr, cur⟩ := pre
  rw [slot.a_tree_insert]

  apply WP.spec_bind (Pₘ := fun (_ : Std.Usize) => True)
  · split
    all_goals step*
  rintro oldest -
  step*

  apply WP.spec_bind (Pₘ := fun (x : alloc.vec.Vec Std.U32 × Std.Usize) => 2 ≤ x.2.val)
  · repeat' (split <;> step*)
    all_goals exact SV0!
  rintro ⟨mb1, best⟩ hb
  step*

  apply WP.spec_bind (Pₘ := fun (x : alloc.vec.Vec Std.U32 × Std.Usize) => 2 ≤ x.2.val)
  · repeat' (split <;> step*)
    all_goals exact SV0!
  rintro ⟨mb2, best1⟩ hb1
  step*
  repeat' (split <;> step*)
  all_goals exact SV0!

set_option maxHeartbeats 4000000 in
@[local step]
theorem a_find_all_loop_spec (i : Std.U32) (s : Slice Std.U8) (mp : alloc.vec.Vec Std.U32) (mb depth) (skip n : Std.Usize) (head kid h3 rct) (i1 cl cd : Std.Usize) (nq nt nh n3 nr nc)
    (hn : n.val = s.length) (hn26 : s.length < 67108864) (hi : i.val < 32) (hskip : 3 ≤ skip.val)
    (hmp : mp.length ≤ i1.val + 1) (hcd : 1 ≤ cd.val) :
    slot.a_find_all_loop i s mp mb depth skip n head kid h3 rct i1 cl cd nq nt nh n3 nr nc ⦃ fun _ => True ⦄ := by
  rw [slot.a_find_all_loop]
  apply SDN!
    (measure := fun (_, _, _, _, _, _, i1_, _, _, _, _, _, _, _, _) => n.val - i1_.val)
    (inv := fun ((mp_ : alloc.vec.Vec Std.U32), _, _, _, _, _, (i1_ : Std.Usize), _, (cd_ : Std.Usize), _, _, _, _, _, _) =>
      mp_.length ≤ i1_.val + 1 ∧ 1 ≤ cd_.val)
  · rintro ⟨mp_, mb_, head_, kid_, h3_, rct_, i1_, cl_, cd_, nq_, nt_, nh_, n3_, nr_, nc_⟩ ⟨hmp_, hcd_⟩
    unfold slot.a_find_all_loop.body
    simp only [engA_ite_ok, engA_ite_pair]
    step*

    apply WP.spec_bind (Pₘ := fun (x : alloc.vec.Vec Std.U32 × Std.Array Std.U32 65536#usize × Std.Array Std.U32 65536#usize ×
        Std.Array Std.U32 32768#usize × Std.Array Std.U32 65536#usize × Std.Usize × Std.Usize × Std.U64 × Std.Usize ×
        Std.Usize × Std.Usize × Std.Usize × Std.Usize) => 1 ≤ x.2.2.2.2.2.2.1.val)
    · split
      · step*
        ·
          apply WP.spec_bind (Pₘ := fun (y : alloc.vec.Vec Std.U32 × Std.Array Std.U32 65536#usize ×
              Std.Array Std.U32 65536#usize × Std.Array Std.U32 32768#usize × Std.Array Std.U32 65536#usize ×
              Std.Usize × Std.Usize × Std.Usize × Std.Usize × Std.Usize) => 1 ≤ y.2.2.2.2.2.2.1.val)
          · split
            ·
              step*
              split
              all_goals step*
              all_goals scalar_tac
            ·
              step*
              apply WP.spec_bind (Pₘ := fun (z : Std.Array Std.U32 65536#usize × Std.Array Std.U32 65536#usize ×
                  Std.Array Std.U32 32768#usize × Std.Array Std.U32 65536#usize × Std.Usize × Std.Usize) =>
                  1 ≤ z.2.2.2.2.2.val)
              · repeat' (split <;> step*)
                all_goals scalar_tac
              rintro ⟨head3, kid3, h33, rct3, cl2, cd2⟩ hcd2
              step*
          rintro ⟨v, a, a1, a2, a3, i17, i18, i19, i20, i21⟩ h18
          step*
        ·
          apply WP.spec_bind (Pₘ := fun (_ : alloc.vec.Vec Std.U32 × Std.Array Std.U32 32768#usize) => True)
          · repeat' (split <;> step*)
            all_goals scalar_tac
          rintro ⟨v, a⟩ -
          step*
      · step*
        apply WP.spec_bind (Pₘ := fun (_ : alloc.vec.Vec Std.U32 × Std.Array Std.U32 32768#usize) => True)
        · repeat' (split <;> step*)
          all_goals scalar_tac
        rintro ⟨v, a⟩ -
        step*
    rintro ⟨mb1, head1, kid1, h31, rct1, cl1, cd1, nq1, nt1, nh1, n31, nr1, nc1⟩ hcd1
    step*
    apply WP.spec_bind (Pₘ := fun (_ : Std.Usize) => True)
    · split
      all_goals step*
    rintro cl2 -
    step*
    simp only [alloc.vec.Vec.length, *, List.length_append, List.length_singleton]
    scalar_tac
  · exact ⟨hmp, hcd⟩

@[local step]
theorem a_find_all_spec (s : Slice Std.U8) (mp : alloc.vec.Vec Std.U32) (mb depth) (skip : Std.Usize)
    (hn26 : s.length < 67108864) (hskip : 3 ≤ skip.val) (hmp : mp.length = 0) :
    slot.a_find_all s mp mb depth skip ⦃ fun _ => True ⦄ := by
  have hhb := A_HB_bounds
  rw [slot.a_find_all]
  step*
  all_goals try simp only [alloc.vec.Vec.length, *, List.length_append, List.length_singleton]
  all_goals exact SV0!

@[local step]
theorem a_engine_loop0_spec (n : Std.Usize) (cost) (i : Std.Usize) (hn : n.val < 67108864) (hc : cost.length = i.val) :
    slot.a_engine_loop0 n cost i ⦃ fun _ => True ⦄ := by
  rw [slot.a_engine_loop0]
  apply SDN!
    (measure := fun (_, i_) => n.val + 1 - i_.val)
    (inv := fun (cost_, i_) => cost_.length = i_.val)
  · rintro ⟨cost_, i_⟩ hc_
    simp only [slot.a_engine_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals try simp only [alloc.vec.Vec.length, *, List.length_append, List.length_singleton]
    all_goals exact SV0!
  · exact hc

@[local step]
theorem a_engine_loop1_loop0_spec (input : Slice Std.U8) (ch) (n : Std.Usize) (mp mb cost lit lc dc lf df bl bd sl sd) (rot p0 need passes sampled pe k p1 t : Std.Usize)
    (hn : n.val = input.length) (hn26 : n.val < 67108864) (hp0 : p0.val < n.val) (hpe : p0.val ≤ pe.val ∧ pe.val ≤ n.val)
    (hpe' : pe.val = n.val ∨ p0.val + slot.A_MARGIN.val ≤ pe.val)
    (hneed : need.val ≤ 65536) (ht : t.val ≤ need.val) (hp1 : p0.val ≤ p1.val ∧ p1.val ≤ p0.val + 511 * t.val) :
    slot.a_engine_loop1_loop0 input ch n mp mb cost lit lc dc lf df bl bd sl sd rot p0 need passes sampled pe k p1 t ⦃ fun r =>
      r.2.2.2.2.2.2.2.2.2.2.val ≤ need.val ∧ p0.val ≤ r.2.2.2.2.2.2.2.2.2.1.val ∧
      r.2.2.2.2.2.2.2.2.2.1.val ≤ p0.val + 511 * r.2.2.2.2.2.2.2.2.2.2.val ⦄ := by
  have hbt := A_BLOCK_bounds
  have hseg := A_SEG_bounds
  rw [slot.a_engine_loop1_loop0]
  apply SDN!
    (measure := fun (_, _, _, _, _, _, _, _, _, _, k_, _, _) => passes.val - k_.val)
    (inv := fun (_, _, _, _, _, _, _, _, _, (pe_ : Std.Usize), _, (p1_ : Std.Usize), (t_ : Std.Usize)) =>
      p0.val ≤ pe_.val ∧ pe_.val ≤ n.val ∧ (pe_.val = n.val ∨ p0.val + slot.A_MARGIN.val ≤ pe_.val) ∧
      t_.val ≤ need.val ∧ p0.val ≤ p1_.val ∧ p1_.val ≤ p0.val + 511 * t_.val)
  · rintro ⟨ch_, cost_, lit_, lc_, dc_, lf_, df_, sl_, sd_, pe_, k_, p1_, t_⟩ ⟨hpe0, hpe1, hpe2, ht_, hp10, hp11⟩
    simp only [slot.a_engine_loop1_loop0.body]
    step*

    apply WP.spec_bind (Pₘ := fun (x : alloc.vec.Vec Std.U32 × alloc.vec.Vec Std.U32 × Std.Array Std.U32 512#usize ×
        Std.Array Std.U32 32#usize × Std.Usize × Std.Usize × Std.Usize) =>
        p0.val ≤ x.2.2.2.2.1.val ∧ x.2.2.2.2.1.val ≤ n.val ∧
        (x.2.2.2.2.1.val = n.val ∨ p0.val + slot.A_MARGIN.val ≤ x.2.2.2.2.1.val) ∧
        x.2.2.2.2.2.2.val ≤ need.val ∧ p0.val ≤ x.2.2.2.2.2.1.val ∧ x.2.2.2.2.2.1.val ≤ p0.val + 511 * x.2.2.2.2.2.2.val)
    · split
      · step*
        ·
          cases ‹Std.Usize × Std.Usize›
          step*
          apply WP.spec_bind (Pₘ := fun (z : alloc.vec.Vec Std.U32 × alloc.vec.Vec Std.U32 × Std.Array Std.U32 512#usize ×
              Std.Array Std.U32 32#usize × Std.Usize) => p0.val ≤ z.2.2.2.2.val ∧ z.2.2.2.2.val ≤ n.val ∧
              (z.2.2.2.2.val = n.val ∨ p0.val + slot.A_MARGIN.val ≤ z.2.2.2.2.val))
          · repeat' (split <;> step*)
            all_goals exact SV0!
          rintro ⟨v, v1, a, a1, i6⟩ hi6
          step*
          all_goals exact SV0!
        ·
          apply WP.spec_bind (Pₘ := fun (lim : Std.Usize) => lim.val ≤ pe_.val)
          · split
            all_goals step*
            all_goals exact SV0!
          rintro lim hlim
          step*
          cases ‹Std.Usize × Std.Usize›
          step*
          apply WP.spec_bind (Pₘ := fun (z : Std.Array Std.U32 512#usize × Std.Array Std.U32 32#usize × Std.Usize) =>
              p0.val ≤ z.2.2.val ∧ z.2.2.val ≤ n.val ∧ (z.2.2.val = n.val ∨ p0.val + slot.A_MARGIN.val ≤ z.2.2.val))
          · repeat' (split <;> step*)
            all_goals exact SV0!
          rintro ⟨a, a1, i4⟩ hi4
          step*
          all_goals exact SV0!
        ·
          apply WP.spec_bind (Pₘ := fun (lim : Std.Usize) => lim.val ≤ pe_.val)
          · split
            all_goals step*
            all_goals exact SV0!
          rintro lim hlim
          step*
          cases ‹Std.Usize × Std.Usize›
          step*
          apply WP.spec_bind (Pₘ := fun (z : Std.Array Std.U32 512#usize × Std.Array Std.U32 32#usize × Std.Usize) =>
              p0.val ≤ z.2.2.val ∧ z.2.2.val ≤ n.val ∧ (z.2.2.val = n.val ∨ p0.val + slot.A_MARGIN.val ≤ z.2.2.val))
          · repeat' (split <;> step*)
            all_goals exact SV0!
          rintro ⟨a, a1, i4⟩ hi4
          step*
          all_goals exact SV0!
      · step*
        ·
          apply WP.spec_bind (Pₘ := fun (lim : Std.Usize) => lim.val ≤ pe_.val)
          · split
            all_goals step*
            all_goals exact SV0!
          rintro lim hlim
          step*
          cases ‹Std.Usize × Std.Usize›
          step*
          apply WP.spec_bind (Pₘ := fun (z : Std.Array Std.U32 512#usize × Std.Array Std.U32 32#usize × Std.Usize) =>
              p0.val ≤ z.2.2.val ∧ z.2.2.val ≤ n.val ∧ (z.2.2.val = n.val ∨ p0.val + slot.A_MARGIN.val ≤ z.2.2.val))
          · repeat' (split <;> step*)
            all_goals exact SV0!
          rintro ⟨a, a1, i4⟩ hi4
          step*
          all_goals exact SV0!
    rintro ⟨ch1, cost1, lf1, df1, pe1, p11, t1⟩ ⟨hq0, hq1, hq2, hq3, hq4, hq5⟩
    step*
    repeat' (split <;> step*)
    all_goals exact SV0!
  · exact ⟨hpe.1, hpe.2, hpe', ht, hp1.1, hp1.2⟩

@[local step]
theorem a_engine_loop1_spec (input : Slice Std.U8) (ch first_passes fspass passes_k) (n : Std.Usize) (mp mb cost lit lc dc lf df bl bd sl sd zl zd) (rot spn p0 used bpt : Std.Usize)
    (hn : n.val = input.length) (hn26 : n.val < 67108864) (hused : used.val < slot.BLOCK_TOKENS.val) (hbpt : 256 ≤ bpt.val ∧ bpt.val ≤ 65536) :
    slot.a_engine_loop1 input ch first_passes fspass passes_k n mp mb cost lit lc dc lf df bl bd sl sd zl zd rot spn p0 used bpt ⦃ fun _ => True ⦄ := by
  have hbt := A_BLOCK_bounds
  rw [slot.a_engine_loop1]
  apply SDN!
    (measure := fun (_, _, _, _, _, _, _, _, _, _, _, p0_, _, _) => n.val - p0_.val)
    (inv := fun (_, _, _, _, _, _, _, _, _, _, _, _, used_, bpt_) => used_.val < slot.BLOCK_TOKENS.val ∧
      256 ≤ bpt_.val ∧ bpt_.val ≤ 130816)
  · rintro ⟨ch_, cost_, lit_, lc_, dc_, lf_, df_, bl_, bd_, sl_, sd_, p0_, used_, bpt_⟩ ⟨hused_, hbpt0, hbpt1⟩
    simp only [slot.a_engine_loop1.body, engA_ite_ok]
    step*
    ·
      have : need.val * bpt_.val ≤ 16384 * 130816 := Nat.mul_le_mul (by exact SV0!) hbpt1
      exact SV0!
    apply WP.spec_bind (Pₘ := fun (pe : Std.Usize) => p0_.val ≤ pe.val ∧ pe.val ≤ n.val ∧
      (pe.val = n.val ∨ p0_.val + slot.A_MARGIN.val ≤ pe.val))
    · split
      all_goals step*
      all_goals exact SV0!
    rintro pe hpe
    step*
    apply WP.spec_bind (Pₘ := fun (x : Std.Array Std.U32 512#usize × Std.Array Std.U32 32#usize × Std.Usize) =>
      x.2.2.val < slot.BLOCK_TOKENS.val)
    · split
      all_goals step*
      all_goals exact SV0!
    rintro ⟨bl1, bd1, used2⟩ hu2
    step*

    all_goals try (
      have hdiv : bpt1.val ≤ 130816 := by
        rw [bpt1_post]; apply Nat.div_le_of_le_mul; exact SV0!
      by_cases hb : bpt1 < 256#usize
      all_goals simp only [hb, ite_true, ite_false])
    all_goals exact SV0!
  ·
    exact ⟨hused, hbpt.1, by omega⟩

@[local step]
theorem a_engine_spec (input : Slice Std.U8) (ch) (depth skip first_passes fspass passes_k spass : Std.Usize)
    (hn : input.length < 67108864) (h1 : depth.val ≤ 65536) (h2 : skip.val ≤ 65536) (h2' : 3 ≤ skip.val)
    (h3 : first_passes.val ≤ 65536) (h4 : fspass.val ≤ 65536) (h5 : passes_k.val ≤ 65536) (h6 : spass.val ≤ 65536) :
    slot.a_engine input ch depth skip first_passes fspass passes_k spass ⦃ fun _ => True ⦄ := by
  have hbt := A_BLOCK_bounds
  rw [slot.a_engine]
  step*
  all_goals rfl

theorem spine_CFG_le : ∀ r ∈ slot.CFG.val, ∀ x ∈ r.val, x.val ≤ 65536 := by
  unfold slot.CFG; decide

theorem spine_CFG_skip : ∀ r ∈ slot.CFG.val, (r.val[0]!).val = 0 → 3 ≤ (r.val[2]!).val := by
  unfold slot.CFG; decide

theorem spine_knob_le {m : Std.Usize} {r : Array Std.Usize m} (hr : ∀ x ∈ r.val, x.val ≤ 65536)
    {x : Std.Usize} {j : Nat} {hj : j < r.val.length} (hx : x = r.val[j]) : x.val ≤ 65536 := by
  subst hx; exact hr _ (List.getElem_mem _)

theorem spine_knob_skip {m : Std.Usize} {r : Array Std.Usize m}
    (hs : (r.val[0]!).val = 0 → 3 ≤ (r.val[2]!).val)
    {x0 x2 : Std.Usize} {h0 : 0 < r.val.length} {h2 : 2 < r.val.length}
    (hx0 : x0 = r.val[0]) (hz : x0 = 0#usize) (hx2 : x2 = r.val[2]) : 3 ≤ x2.val := by
  rw [getElem!_pos r.val 0 h0, getElem!_pos r.val 2 h2, ← hx0, ← hx2, hz] at hs
  exact hs rfl

@[local step]
theorem plan_cfg_spec (input : Slice Std.U8) (k) (hn : input.length < 67108864) :
    slot.plan_cfg input k ⦃ fun _ => True ⦄ := by
  rw [slot.plan_cfg]
  step*

  all_goals
    have hc : c ∈ slot.CFG.val := by rw [c_post]; exact List.getElem_mem _
    first
    | exact spine_knob_le (spine_CFG_le c hc) (by assumption)
    | exact spine_knob_skip (spine_CFG_skip c hc) (by assumption) (by assumption) (by assumption)

@[local step]
theorem s_plan_spec (input : Slice Std.U8) (k : Std.Usize) : slot.s_plan input k ⦃ fun _ => True ⦄ := by
  rw [slot.s_plan]
  step*

namespace Z466
open Aeneas Aeneas.Std Result ControlFlow
open LZ77 (toks bytes)
set_option hygiene false in
local notation "Y112P0!" => (fun _ => True)
set_option hygiene false in
local notation "Y112P1!" => (fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val))
set_option hygiene false in
local notation "Y112P2!" => (fun r => r.1.val ≤ input.length ∧ r.2.length = out0.length ∧ LZ77.decode (toks r.2 r.1.val) = some (bytes input))
set_option hygiene false in
local notation "Y112P3!" => (fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.decode (toks r.2 r.1.val) = some (bytes input))
set_option hygiene false in
local notation "Y112P4!" => (fun r => r.2.2.2.2.2.2.2.2.2.2.val ≤ need.val ∧ p0.val ≤ r.2.2.2.2.2.2.2.2.2.1.val ∧ r.2.2.2.2.2.2.2.2.2.1.val ≤ p0.val + 511 * r.2.2.2.2.2.2.2.2.2.2.val)
set_option hygiene false in
local notation "Y112P5!" => (fun r => True)
set_option hygiene false in
local notation "Y112P6!" => (fun l => l.val ≤ cap.val ∧ Matches input a.val b.val l.val)
set_option hygiene false in
local notation "Y112P7!" => (fun r => prev.val ≤ r.2.2.1.val ∧ r.2.2.1.val ≤ i.val + 258 ∧ r.2.2.2.val ≤ 32768 ∧ r.2.1.val ≤ 32767)
set_option hygiene false in
local notation "Y112P8!" => (fun r => base.val + slot.Z64.val ≤ r.length ∧ bf.length ≤ r.length ∧ u455 r.val base.val 0)
local notation "U" => Slice Std.U32
local notation "I" => Slice Std.U8
local notation "O" => Std.Array Std.Usize
local notation "C" => Std.Array Std.U32
local notation "G" => Std.Array Std.U8
local notation "V" => List Std.U32
local notation "R" => Std.Usize
local notation "W" => Std.U32
set_option aeneas.step.nla false
set_option linter.unusedTactic false
set_option linter.unreachableTactic false

theorem dp_ite3_spec {α:Type} {a b c:Prop} [Decidable a] [Decidable b] [Decidable c]
    {X Y:Result α} {P:α → Prop} (hX:a → b → ¬c → X ⦃ P ⦄) (hY:Y ⦃ P ⦄) :
    (if a then (if b then (if c then Y else X) else Y) else Y) ⦃ P ⦄ := by
  by_cases ha:a
  · rw [if_pos ha]
    by_cases hb:b
    · rw [if_pos hb]
      by_cases hc:c
      · rw [if_pos hc];exact hY
      · rw [if_neg hc];exact hX ha hb hc
    · rw [if_neg hb];exact hY
  · rw [if_neg ha];exact hY

theorem dp_ite2_spec {α:Type} {a b:Prop} [Decidable a] [Decidable b]
    {X Y:Result α} {P:α → Prop} (hX:a → b → X ⦃ P ⦄) (hY:Y ⦃ P ⦄) :
    (if a then (if b then X else Y) else Y) ⦃ P ⦄ := by
  by_cases ha:a
  · rw [if_pos ha]
    by_cases hb:b
    · rw [if_pos hb];exact hX ha hb
    · rw [if_neg hb];exact hY
  · rw [if_neg ha];exact hY
theorem dp_ite_spec {α:Type} {c:Prop} [Decidable c] {A B:Result α} {P:α → Prop}
    (hA:c → A ⦃ P ⦄) (hB:¬c → B ⦃ P ⦄):(if c then A else B) ⦃ P ⦄ := by
  by_cases h:c
  · rw [if_pos h];exact hA h
  · rw [if_neg h];exact hB h
theorem dp_sat_sub_val (x y:R) :
    (core.num.Usize.saturating_sub x y).val = x.val - y.val := by
  have hx := x.hBounds
  show (BitVec.ofNat _ (max 0 (x.val - y.val))).toNat = x.val - y.val
  rw [BitVec.toNat_ofNat, Nat.zero_max]
  exact Nat.mod_eq_of_lt (lt_of_le_of_lt (Nat.sub_le _ _) hx)

set_option maxRecDepth 8192
set_option maxHeartbeats 4000000
set_option hygiene false in
local notation "Y122U1!" q0__:max => (by
  rw [q0__]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac)
set_option hygiene false in
local notation "Y122U2!" q0__:max => (by
  rw [q0__]
  have hmax:input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  step*
  intro hvalid
  have hl:l = len := by simpa using hvalid
  subst hl
  refine ⟨by scalar_tac, by scalar_tac, by scalar_tac, by scalar_tac, by scalar_tac,
    by scalar_tac, ?_⟩
  rw [← src_post1]
  exact l_post2)
set_option hygiene false in
local notation "Y122U3!" q0__:max q1__:max => (by
  rw [q0__]
  apply SDN!
    (measure := fun (_, _, p) => n.val - p.val)
    (inv := fun (out, ntok, p) => p.val ≤ n.val ∧ ntok.val ≤ p.val ∧ out.length = out0.length ∧
      LZ77.decode (toks out ntok.val) = some ((bytes input).take p.val))
  · rintro ⟨out, ntok, p⟩ ⟨hp, hnt, hlen, hde⟩
    simp only [q1__]
    have hmax:input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    split
    case isTrue hlt =>
      have hntok_lt:ntok.val < out.length := by scalar_tac
      step*
      ·
        obtain ⟨h3, h258, hd1, hd32k, hdp, hend, hm⟩ := valid_post (by assumption)
        have htok:tok.val = LZ77.mkMatch dist.val len.val := by
          simp only [LZ77.mkMatch, LZ77.MATCH_BASE]
          scalar_tac
        refine ⟨by scalar_tac, by scalar_tac, by rw [s_post];simpa using hlen, ?_, by scalar_tac⟩
        rw [s_post, show ntok1.val = ntok.val + 1 by scalar_tac,
          show p1.val = p.val + len.val by scalar_tac]
        exact emit_match input out ntok p.val dist.val len.val tok hde hntok_lt hd1 hdp hd32k
          h3 h258 hend hm htok
      ·
        have hlit:lit.val = (bytes input)[p.val]! := by
          rw [bytes_getElem! input p.val (by scalar_tac)]
          scalar_tac
        refine ⟨by scalar_tac, by scalar_tac, by rw [s_post];simpa using hlen, ?_, by scalar_tac⟩
        rw [s_post, show ntok1.val = ntok.val + 1 by scalar_tac,
          show p1.val = p.val + 1 by scalar_tac]
        exact emit_lit input out ntok p.val lit hde (by scalar_tac) hntok_lt hlit
    case isFalse hge =>
      have hpn:p.val = input.length := by scalar_tac
      refine ⟨by scalar_tac, hlen, ?_⟩
      rw [hde, hpn]
      simp
  · exact ⟨hp0, hntok0, rfl, hdec0⟩)
namespace EA
open Aeneas Aeneas.Std Result ControlFlow
set_option maxRecDepth 8192
set_option maxHeartbeats 1000000
set_option linter.unusedTactic false
set_option linter.unreachableTactic false
set_option linter.unusedSimpArgs false
set_option linter.unusedVariables false
open LZ77 (toks bytes bytes_getElem! Matches emit_lit emit_match)
@[step]
theorem u0 {α:Type} (x:α):lift x ⦃ fun y => y = x ⦄ := by
  simp [lift, WP.spec_ok]
@[step]
theorem u1 (v:U) (i:R):slot.Z230 v i ⦃ Y112P0! ⦄ := by
  rw [slot.Z230];split <;> step*
@[local scalar_tac x &&& y]
theorem u2 (x y:Nat):x &&& y ≤ y := Nat.and_le_right
@[local scalar_tac x >>> y]
theorem u3 (x y:Nat):x >>> y ≤ x := Nat.shiftRight_le x y
theorem u4:32 ≤ System.Platform.numBits := by
  cases System.Platform.numBits_eq <;> simp [*]
@[local scalar_tac System.Platform.numBits]
theorem u5:32 ≤ System.Platform.numBits := u4
theorem lz_le_w {w:Nat} (x:BitVec w):BitVec.leadingZeros x ≤ w := by
  unfold BitVec.leadingZeros;split <;> omega
theorem lz32_val (x:W) :
    (core.num.U32.leading_zeros x).val = BitVec.leadingZeros x.bv := by
  simp only [core.num.U32.leading_zeros, UScalar.val]
  have := lz_le_w x.bv
  apply Nat.mod_eq_of_lt
  simp at this ⊢
  omega
theorem lz32_eq (x:W) (h:x.val ≠ 0) :
    (core.num.U32.leading_zeros x).val = 31 - Nat.log 2 x.val := by
  rw [lz32_val]
  unfold BitVec.leadingZeros
  have hx:x.bv ≠ 0 := by
    intro h0;apply h;show x.bv.toNat = 0;rw [h0];rfl
  rw [if_neg hx, UScalar.bv_toNat]
  omega
theorem lz32_le (x:W):(core.num.U32.leading_zeros x).val ≤ 32 := by
  rw [lz32_val];exact lz_le_w x.bv
theorem u6 (x:W) (k:Nat) (h:2 ^ k ≤ x.val) :
    (core.num.U32.leading_zeros x).val + k ≤ 31 := by
  have hx:x.val ≠ 0 := by have := Nat.one_le_two_pow (n := k);omega
  rw [lz32_eq x hx]
  have hk:k ≤ Nat.log 2 x.val := Nat.le_log_of_pow_le (by norm_num) h
  have:x.val < 2 ^ 32 := by scalar_tac
  have hl:Nat.log 2 x.val < 32 := Nat.log_lt_of_lt_pow (by omega) this
  omega
theorem u7 (x:W) (k:Nat) (h:x.val < 2 ^ k) :
    32 - k ≤ (core.num.U32.leading_zeros x).val := by
  by_cases hx:x.val = 0
  · rw [lz32_val];unfold BitVec.leadingZeros
    have:x.bv = 0 := by
      apply BitVec.eq_of_toNat_eq;rw [UScalar.bv_toNat];simpa using hx
    rw [if_pos this];omega
  · rw [lz32_eq x hx]
    have hl:Nat.log 2 x.val < k := Nat.log_lt_of_lt_pow hx h
    omega
theorem u9 (x:Std.U64) :
    (core.num.U64.leading_zeros x).val = BitVec.leadingZeros x.bv := by
  simp only [core.num.U64.leading_zeros, UScalar.val]
  have := lz_le_w x.bv
  apply Nat.mod_eq_of_lt
  simp at this ⊢
  omega
theorem u10 (x:Std.U64):(core.num.U64.leading_zeros x).val ≤ 64 := by
  rw [u9];exact lz_le_w x.bv
@[local scalar_tac core.num.U32.leading_zeros x]
theorem u11 (x:W) :
    (core.num.U32.leading_zeros x).val ≤ 32 ∧
      (x.val = 0 ∨ (core.num.U32.leading_zeros x).val ≤ 31) := by
  refine ⟨lz32_le x, ?_⟩
  by_cases h:x.val = 0
  · exact Or.inl h
  · right;rw [lz32_eq x h];omega
@[local scalar_tac core.num.U64.leading_zeros x]
theorem u12 (x:Std.U64):(core.num.U64.leading_zeros x).val ≤ 64 := u10 x
def u13 {ty:UScalarTy} (l:List (UScalar ty)) (B:Nat):Prop :=
  ∀ j (h:j < l.length), (l[j]).val ≤ B
theorem u14 {ty:UScalarTy} {l:List (UScalar ty)} {B:Nat} (hl:u13 l B)
    (j:Nat) (hj:j < l.length):(l[j]).val ≤ B := hl j hj
theorem u23 {ty:UScalarTy} {l:List (UScalar ty)} {B B':Nat} (hl:u13 l B)
    (h:B ≤ B'):u13 l B' := fun j hj => Nat.le_trans (hl j hj) h
theorem LeAll_replicate {ty:UScalarTy} (n:Nat) (x:UScalar ty) (B:Nat) (h:x.val ≤ B) :
    u13 (List.replicate n x) B := by
  intro j hj;simp [List.getElem_replicate];exact h
theorem u24 {ty:UScalarTy} {l:List (UScalar ty)} {B:Nat} (hl:u13 l B)
    (i:Nat) (x:UScalar ty) (hx:x.val ≤ B):u13 (l.set i x) B := by
  intro j hj
  rw [List.getElem_set]
  split
  · exact hx
  · exact hl j (by simpa using hj)
theorem u26 {ty:UScalarTy} {l:List (UScalar ty)} {t:Nat} (hl:u13 l t)
    (i:Nat) (x:UScalar ty) (hx:x.val ≤ t + 1):u13 (l.set i x) (t + 1) :=
  u24 (u23 hl (Nat.le_succ t)) i x hx
theorem u28:0 < slot.Z45.val ∧ slot.Z45.val ≤ 65536 := by
  simp [slot.Z45]
theorem dp_WN_val:slot.Z62.val = 32768 := by simp [slot.Z62]
theorem u33:slot.Z45.val = 16384 := by simp [slot.Z45]
theorem u34:slot.Z47.val = 65536 := by simp [slot.Z47]
theorem u36:1 ≤ slot.Z46.val ∧ slot.Z46.val ≤ 32 := by simp [slot.Z46]
theorem u37:1 ≤ slot.Z46.val ∧ slot.Z46.val ≤ 64 := by simp [slot.Z46]
theorem u40:slot.Z59.val ≤ 1048576 := by simp [slot.Z59]
theorem u41:slot.Z4.val ≤ 1048576 := by simp [slot.Z4]
theorem u46 {ty:UScalarTy} (n:R) (x:UScalar ty) (B:Nat) (h:x.val ≤ B) :
    u13 (Array.repeat n x).val B := by
  rw [Array.repeat_val];exact LeAll_replicate _ _ _ h
theorem u119 {α:Type} {c:Prop} [Decidable c] {A B:Result α} {P:α → Prop}
    (hA:c → A ⦃ P ⦄) (hB:¬c → B ⦃ P ⦄):(if c then A else B) ⦃ P ⦄ := by
  by_cases h:c
  · rw [if_pos h];exact hA h
  · rw [if_neg h];exact hB h
theorem d1_ite_ok {α:Type} (c:Prop) [Decidable c] (a b:α) :
    (if c then (ok a:Result α) else ok b) = ok (if c then a else b) := by split <;> rfl
@[step]
theorem u293 (n:R) (v0:alloc.vec.Vec W) (i0:R)
    (hv:v0.length = i0.val) (hi:i0.val ≤ n.val) :
    slot.Z261_loop n v0 i0 ⦃ fun v => v.length = n.val ⦄ := by
  rw [slot.Z261_loop]
  apply SDN!
    (measure := fun (_, i) => n.val - i.val)
    (inv := fun (v, i) => v.length = i.val ∧ i.val ≤ n.val)
  · rintro ⟨v, i⟩ ⟨hvi, hin⟩
    simp only [slot.Z261_loop.body]
    step*
    all_goals have hlen:v1.length = v.length + 1 := by simp [v1_post]
    all_goals scalar_tac
  · exact ⟨hv, hi⟩
@[step]
theorem u294 (n:R):slot.Z261 n ⦃ fun v => v.length = n.val ⦄ := by
  rw [slot.Z261]
  step*
  simp [alloc.vec.Vec.with_capacity]
theorem u298:u13 slot.Z0.val 64 := by
  unfold slot.Z0 u13;simp only [Array.make];decide
theorem A_SEG_bounds:256 ≤ slot.Z8.val ∧ slot.Z8.val ≤ 65536 ∧
    slot.Z8.val + 512 ≤ slot.Z8.val * slot.Z3.val ∧
    slot.Z8.val * slot.Z3.val ≤ 1048576 := by
  simp
theorem A_BLOCK_bounds:0 < slot.Z45.val ∧ slot.Z45.val ≤ 16384 ∧
    slot.Z1.val ≤ 65536 ∧ slot.Z59.val ≠ 0 := by
  simp
theorem u299 (x y:R) :
    (core.num.Usize.saturating_add x y).val = min Std.Usize.max (x.val + y.val) := by
  have hsz:Std.Usize.max < 2 ^ UScalarTy.Usize.numBits := by
    rw [Std.Usize.max_def, Std.Usize.numBits]
    have:0 < 2 ^ UScalarTy.Usize.numBits := Nat.two_pow_pos _
    omega
  show (BitVec.ofNat _ (min (UScalar.max UScalarTy.Usize) (x.val + y.val))).toNat = _
  rw [BitVec.toNat_ofNat, UScalar.max_USize_eq, Nat.mod_eq_of_lt (by omega)]
@[local scalar_tac core.num.Usize.saturating_add x y]
theorem u300 (x y:R) :
    (core.num.Usize.saturating_add x y).val = min Std.Usize.max (x.val + y.val) := u299 x y
theorem u301 {α β:Type} (c:Prop) [Decidable c] (a a':α) (b b':β) :
    (if c then (a, b) else (a', b')) = (if c then a else a', if c then b else b') := by
  split <;> rfl
theorem u302 {n:R} {a r:C n} {i:R} {v:W} {B:Nat}
    (hr:r = a.set i v) (ha:u13 a.val B) (hv:v.val ≤ B):u13 r.val B := by
  rw [hr, Array.set_val_eq];exact u24 ha _ _ hv
@[step]
theorem u303 (x) :
    slot.Z166 x ⦃ Y112P0! ⦄ := by
  rw [slot.Z166]
  step*
@[step]
theorem u304 (len) :
    slot.Z158 len ⦃ fun r => r.val ≤ 28 ⦄ := by
  rw [slot.Z158]
  split
  · step*
  · split
    · step*
    · step*
      all_goals
        have hx:x.val = len.val - 3 := by
          rw [x_post, UScalar.cast_val_mod_pow_of_inBounds_eq _ _ (by exact SV0!)];exact SV0!
        have h1 := u6 x 3 (by exact SV0!)
        have h2 := u7 x 8 (by exact SV0!)
        subst i1_post
        exact SV0!
@[step]
theorem u305 (lf) :
    slot.Z170_loop0 lf 0#usize ⦃ fun r => u13 r.val 0 ⦄ := by
  rw [slot.Z170_loop0]
  apply SDN!
    (measure := fun (_, k) => 512 - k.val)
    (inv := fun (lf', k) => k.val ≤ 512 ∧ ∀ j (hj:j < k.val) (hl:j < lf'.val.length), (lf'.val[j]).val = 0)
  · rintro ⟨lf', k⟩ ⟨hk, hz⟩
    simp only [slot.Z170_loop0.body]
    step*
    ·
      refine ⟨by exact SV0!, ?_, by exact SV0!⟩
      intro j hj hl
      subst a_post
      simp only [Array.set_val_eq, List.getElem_set]
      split
      · rfl
      · exact hz j (by exact SV0!) (by simpa using hl)
    ·
      intro j hl
      have:k.val = 512 := by exact SV0!
      have hl':j < 512 := by simpa using hl
      rw [hz j (by omega) hl]
  · exact ⟨by simp, fun j hj => by simp at hj⟩
@[step]
theorem u306 (df) :
    slot.Z170_loop1 df 0#usize ⦃ fun r => u13 r.val 0 ⦄ := by
  rw [slot.Z170_loop1]
  apply SDN!
    (measure := fun (_, k) => 32 - k.val)
    (inv := fun (df', k) => k.val ≤ 32 ∧ ∀ j (hj:j < k.val) (hl:j < df'.val.length), (df'.val[j]).val = 0)
  · rintro ⟨df', k⟩ ⟨hk, hz⟩
    simp only [slot.Z170_loop1.body]
    step*
    · refine ⟨by exact SV0!, ?_, by exact SV0!⟩
      intro j hj hl
      subst a_post
      simp only [Array.set_val_eq, List.getElem_set]
      split
      · rfl
      · exact hz j (by exact SV0!) (by simpa using hl)
    · intro j hl
      have:k.val = 32 := by exact SV0!
      have hl':j < 32 := by simpa using hl
      rw [hz j (by omega) hl]
  · exact ⟨by simp, fun j hj => by simp at hj⟩
@[step]
theorem u307 (s:I) (ch) (lim need:R) (lf df) (i t:R)
    (hlim:lim.val ≤ 2 ^ 31) (hls:lim.val ≤ s.length) (hneed:need.val ≤ 2 ^ 31)
    (hlf:u13 lf.val t.val) (hdf:u13 df.val t.val) :
    slot.Z170_loop2 s ch lim need lf df i t ⦃ fun r => i.val ≤ r.2.2.1.val ∧ r.2.2.2.val ≤ max t.val need.val ∧
      r.2.2.1.val ≤ max i.val (lim.val + 511) ∧ r.2.2.1.val + 511 * t.val ≤ i.val + 511 * r.2.2.2.val ⦄ := by
  rw [slot.Z170_loop2]
  apply SDN!
    (measure := fun (_, _, _, t') => need.val - t'.val)
    (inv := fun (lf', df', i', t') => u13 lf'.val t'.val ∧ u13 df'.val t'.val ∧
      i.val ≤ i'.val ∧ t'.val ≤ max t.val need.val ∧
      i'.val ≤ max i.val (lim.val + 511) ∧ i'.val + 511 * t.val ≤ i.val + 511 * t'.val)
  · rintro ⟨lf', df', i', t'⟩ ⟨hlf', hdf', hi', ht', hi2', hi3'⟩
    simp only [slot.Z170_loop2.body]
    step*
    apply WP.spec_bind (Pₘ := fun (x:Std.Array W 512#usize × Std.Array W 32#usize × R) =>
      u13 x.1.val (t'.val + 1) ∧ u13 x.2.1.val (t'.val + 1) ∧ i'.val < x.2.2.val ∧ x.2.2.val ≤ i'.val + 511)
    · split
      ·
        step*
        all_goals try (have := u14 hlf' i6.val (by exact SV0!))
        all_goals try (have := u14 hdf' i14.val (by exact SV0!))
        all_goals try exact SV0!
        refine ⟨?_, ?_, by exact SV0!, by exact SV0!⟩
        · rw [a_post, Array.set_val_eq];exact u26 hlf' _ _ (by exact SV0!)
        · rw [a1_post, Array.set_val_eq];exact u26 hdf' _ _ (by exact SV0!)
      ·
        step*
        all_goals try (have := u14 hlf' i5.val (by exact SV0!))
        all_goals try exact SV0!
        refine ⟨?_, u23 hdf' (by omega), by exact SV0!, by exact SV0!⟩
        rw [a_post, Array.set_val_eq];exact u26 hlf' _ _ (by exact SV0!)
    · rintro ⟨lf1, df1, i3⟩ ⟨h1, h2, h3, h4⟩
      step*
      refine ⟨?_, ?_, by exact SV0!, by exact SV0!, by exact SV0!, by exact SV0!, by exact SV0!⟩
      · rw [show t1.val = t'.val + 1 by exact SV0!];exact h1
      · rw [show t1.val = t'.val + 1 by exact SV0!];exact h2
  · exact ⟨hlf, hdf, le_refl _, by omega, by omega, by omega⟩
set_option hygiene false in
local notation "Y122U4!" q0__:max => (by
  rw [q0__]
  step*
  repeat' (split <;> step*)
  all_goals exact SV0!)
@[step]
theorem u308 (s:I) (ch) (p0 lim need:R) (lf df)
    (hlim:lim.val ≤ 2 ^ 31) (hls:lim.val ≤ s.length) (hneed:need.val ≤ 2 ^ 31) :
    slot.Z170 s ch p0 lim need lf df ⦃ fun r => p0.val ≤ r.1.1.val ∧ r.1.2.val ≤ need.val ∧
      r.1.1.val ≤ max p0.val (lim.val + 511) ∧ r.1.1.val ≤ p0.val + 511 * r.1.2.val ⦄ := Y122U4! slot.Z170
set_option hygiene false in
local notation "Y122U5!" q0__:max q1__:max => (by
  rw [q0__]
  apply SDN!
    (measure := fun (mbest_, at0_, l_) => stop.val + 1 - at0_.val)
    (inv := fun _ => True)
  · rintro ⟨mbest_, at0_, l_⟩ _
    simp only [q1__]
    step*
    repeat' (split <;> step*)
    all_goals exact SV0!
  · trivial)
@[step]
theorem u322 (dst a b k) :
    slot.Z149_loop0 dst a b k ⦃ Y112P0! ⦄ := by
  rw [slot.Z149_loop0]
  apply SDN!
    (measure := fun (dst_, k_) => 512 - k_.val)
    (inv := fun _ => True)
  · rintro ⟨dst_, k_⟩ _
    simp only [slot.Z149_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals exact SV0!
  · trivial
@[step]
theorem u323 (dd x y k) :
    slot.Z149_loop1 dd x y k ⦃ Y112P0! ⦄ := by
  rw [slot.Z149_loop1]
  apply SDN!
    (measure := fun (dd_, k_) => 32 - k_.val)
    (inv := fun _ => True)
  · rintro ⟨dd_, k_⟩ _
    simp only [slot.Z149_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals exact SV0!
  · trivial
@[step]
theorem u324 (dst a b dd x y) :
    slot.Z149 dst a b dd x y ⦃ Y112P0! ⦄ := Y122U4! slot.Z149
@[step]
theorem u325 (x) :
    slot.Z159 x ⦃ fun r => r.val ≤ 2048 ⦄ := by
  rw [slot.Z159]
  have hlz := u11 x
  have htab := u298
  step*
  repeat' (split <;> step*)
  all_goals try (have := u14 htab i3.val (by exact SV0!))
  all_goals exact SV0!
@[step]
theorem u326 (f:W) (g:W) (hg:g.val ≤ 65536) :
    slot.Z168 f g ⦃ fun r => r.val ≤ 1152 ⦄ := Y122U4! slot.Z168
@[step]
theorem u327 (slt:R) :
    slot.Z150 slt ⦃ fun r => r.val ≤ slt.val / 2 ⦄ := Y122U4! slot.Z150
@[step]
theorem u328 (slt) :
    slot.Z157 slt ⦃ fun r => r.val ≤ 5 ⦄ := Y122U4! slot.Z157
@[step]
theorem u329 (lf tl i) :
    slot.Z163_loop0 lf tl i ⦃ Y112P0! ⦄ := by
  rw [slot.Z163_loop0]
  apply SDN!
    (measure := fun (tl_, i_) => 286 - i_.val)
    (inv := fun _ => True)
  · rintro ⟨tl_, i_⟩ _
    simp only [slot.Z163_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals exact SV0!
  · trivial
set_option hygiene false in
local notation "Y122U6!" q0__:max q1__:max => (by
  rw [q0__]
  apply SDN!
    (measure := fun (i_, td_) => 30 - i_.val)
    (inv := fun _ => True)
  · rintro ⟨i_, td_⟩ _
    simp only [q1__]
    step*
    repeat' (split <;> step*)
    all_goals exact SV0!
  · trivial)
@[step]
theorem u330 (df i td) :
    slot.Z163_loop1 df i td ⦃ Y112P0! ⦄ := Y122U6! slot.Z163_loop1 slot.Z163_loop1.body
@[step]
theorem u331 (lf lit i) (gl:W) (hgl:gl.val ≤ 65536) :
    slot.Z163_loop2 lf lit i gl ⦃ Y112P0! ⦄ := by
  rw [slot.Z163_loop2]
  apply SDN!
    (measure := fun (lit_, i_) => 256 - i_.val)
    (inv := fun _ => True)
  · rintro ⟨lit_, i_⟩ _
    simp only [slot.Z163_loop2.body]
    step*
    repeat' (split <;> step*)
    all_goals exact SV0!
  · trivial
@[step]
theorem u332 (lf lc i) (gl:W) (hgl:gl.val ≤ 65536) :
    slot.Z163_loop3 lf lc i gl ⦃ Y112P0! ⦄ := by
  rw [slot.Z163_loop3]
  apply SDN!
    (measure := fun (lc_, i_) => 258 + 1 - i_.val)
    (inv := fun _ => True)
  · rintro ⟨lc_, i_⟩ _
    simp only [slot.Z163_loop3.body]
    step*
    repeat' (split <;> step*)
    all_goals exact SV0!
  · trivial
@[step]
theorem u333 (df dc) (i:R) (gd:W) (hgd:gd.val ≤ 65536) :
    slot.Z163_loop4 df dc i gd ⦃ Y112P0! ⦄ := by
  rw [slot.Z163_loop4]
  apply SDN!
    (measure := fun (dc_, i_) => 30 - i_.val)
    (inv := fun _ => True)
  · rintro ⟨dc_, i_⟩ _
    simp only [slot.Z163_loop4.body]
    step*
    repeat' (split <;> step*)
    all_goals exact SV0!
  · trivial
@[step]
theorem u334 (lf df lit lc dc) :
    slot.Z163 lf df lit lc dc ⦃ Y112P0! ⦄ := Y122U4! slot.Z163
@[step]
theorem u335 (s:I) (lf) (m i:R) (hm:m.val ≤ s.length) (hm2:m.val ≤ 65536)
    (hlf:u13 lf.val i.val) :
    slot.Z154_loop0 s lf m i ⦃ Y112P0! ⦄ := by
  rw [slot.Z154_loop0]
  apply SDN!
    (measure := fun (_, i_) => m.val - i_.val)
    (inv := fun (lf_, i_) => u13 lf_.val i_.val)
  · rintro ⟨lf_, i_⟩ hlf_
    simp only [slot.Z154_loop0.body]
    step*
    all_goals try (have := u14 hlf_ i2.val (by exact SV0!))
    all_goals try exact SV0!
    refine ⟨?_, by exact SV0!⟩
    rw [show i5.val = i_.val + 1 by exact SV0!, a_post, Array.set_val_eq]
    exact u26 hlf_ _ _ (by exact SV0!)
  · exact hlf
@[step]
theorem u336 (lf i) :
    slot.Z154_loop1 lf i ⦃ Y112P0! ⦄ := by
  rw [slot.Z154_loop1]
  apply SDN!
    (measure := fun (lf_, i_) => 29 - i_.val)
    (inv := fun _ => True)
  · rintro ⟨lf_, i_⟩ _
    simp only [slot.Z154_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals exact SV0!
  · trivial
@[step]
theorem u337 (df i) :
    slot.Z154_loop2 df i ⦃ Y112P0! ⦄ := by
  rw [slot.Z154_loop2]
  apply SDN!
    (measure := fun (df_, i_) => 30 - i_.val)
    (inv := fun _ => True)
  · rintro ⟨df_, i_⟩ _
    simp only [slot.Z154_loop2.body]
    step*
    repeat' (split <;> step*)
    all_goals exact SV0!
  · trivial
@[step]
theorem u338 (s lit lc dc) :
    slot.Z154 s lit lc dc ⦃ Y112P0! ⦄ := by
  rw [slot.Z154]
  step*
  repeat' (split <;> step*)
  all_goals exact u46 _ _ _ (by simp)
@[step]
theorem u339 (sym m) (len:C 512#usize) (kraft q) (hlen:u13 len.val 15) :
    slot.Z156_loop sym m len kraft q ⦃ fun r => u13 r.val 15 ⦄ := by
  rw [slot.Z156_loop]
  apply SDN!
    (measure := fun ((len_:C 512#usize), _, (q_:R)) =>
      (512 - q_.val) * 16 + (15 - (len_.val[(sym.val[q_.val]!).val % 512]!).val))
    (inv := fun (len_, _, _) => u13 len_.val 15)
  · rintro ⟨len_, kraft_, q_⟩ hlen_
    dsimp only at hlen_
    simp only [slot.Z156_loop.body]
    step*
    ·
      have hq:(sym.val[q_.val]!).val % 512 = s2.val := by
        rw [getElem!_pos sym.val q_.val (by exact SV0!), ← i_post];exact SV0!
      have ha:a.val[s2.val]! = i5 := by
        rw [a_post, Array.set_val_eq, getElem!_pos _ _ (by simp;exact SV0!), List.getElem_set_self]
      have hl:len_.val[s2.val]! = i2 := by
        rw [getElem!_pos _ _ (by exact SV0!), ← i2_post]
      refine ⟨?_, ?_⟩
      · rw [a_post, Array.set_val_eq];exact u24 hlen_ _ _ (by exact SV0!)
      · rw [hq, ha, hl];exact SV0!
    ·
      exact ⟨hlen_, by exact SV0!⟩
  · exact hlen
@[step]
theorem u340 (sym m) (len:C 512#usize) (kraft0) (hlen:u13 len.val 15) :
    slot.Z156 sym m len kraft0 ⦃ fun r => u13 r.val 15 ⦄ := by
  unfold slot.Z156
  step*
@[step]
theorem u341 (w a) (b:R) (m k) (hb:b.val ≤ 4096) :
    slot.Z160 w a b m k ⦃ fun r => r.2.1.val ≤ a.val + 1 ∧ r.2.2.val ≤ b.val + 1 ⦄ := Y122U4! slot.Z160
@[step]
theorem u342 (sym freq fv) (j:R) (hj:j.val < 512) :
    slot.Z167_loop sym freq fv j ⦃ fun r => r.2.val < 512 ⦄ := by
  rw [slot.Z167_loop]
  apply SDN!
    (measure := fun (_, j_) => j_.val)
    (inv := fun (_, j_) => j_.val < 512)
  · rintro ⟨sym_, j_⟩ hinv
    simp only [slot.Z167_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals exact SV0!
  · exact hj
@[step]
theorem u343 (sym freq m v) :
    slot.Z167 sym freq m v ⦃ Y112P0! ⦄ := Y122U4! slot.Z167
@[step]
theorem u344 (freq n) (len:C 512#usize) (sym) (m i:R)
    (hm:m.val ≤ i.val) (hi:i.val ≤ 512) (hlen:u13 len.val 15) :
    slot.Z155_loop0 freq n len sym m i ⦃ fun r => r.2.2.val ≤ 512 ∧ u13 r.1.val 15 ⦄ := by
  rw [slot.Z155_loop0]
  apply SDN!
    (measure := fun (_, _, _, i_) => 512 - i_.val)
    (inv := fun (len_, _, m_, i_) => m_.val ≤ i_.val ∧ i_.val ≤ 512 ∧ u13 len_.val 15)
  · rintro ⟨len_, sym_, m_, i_⟩ ⟨hm_, hi_, hlen_⟩
    simp only [slot.Z155_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals
      refine ⟨by exact SV0!, by exact SV0!, ?_, by exact SV0!⟩
      rw [a_post, Array.set_val_eq];exact u24 hlen_ _ _ (by exact SV0!)
  · exact ⟨hm, hi, hlen⟩
@[step]
theorem u345 (freq sym m i w) :
    slot.Z155_loop1 freq sym m i w ⦃ Y112P0! ⦄ := by
  rw [slot.Z155_loop1]
  apply SDN!
    (measure := fun (i_, w_) => m.val - i_.val)
    (inv := fun _ => True)
  · rintro ⟨i_, w_⟩ _
    simp only [slot.Z155_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals exact SV0!
  · trivial
@[step]
theorem u346 (m:R) (w par) (a b k:R) (hm:m.val ≤ 512)
    (ha:a.val ≤ 2 * k.val) (hb:b.val ≤ 2 * k.val) (hk:k.val ≤ 1024) :
    slot.Z155_loop2 m w par a b k ⦃ fun r => r.2.val ≤ 1024 ⦄ := by
  rw [slot.Z155_loop2]
  apply SDN!
    (measure := fun (_, _, _, _, k_) => 1024 - k_.val)
    (inv := fun (_, _, a_, b_, k_) => a_.val ≤ 2 * k_.val ∧ b_.val ≤ 2 * k_.val ∧ k_.val ≤ 1024)
  · rintro ⟨w_, par_, a_, b_, k_⟩ ⟨ha_, hb_, hk_⟩
    simp only [slot.Z155_loop2.body]
    step*
    repeat' (split <;> step*)
    all_goals exact SV0!
  · exact ⟨ha, hb, hk⟩
@[step]
theorem u347 (par d j) :
    slot.Z155_loop3 par d j ⦃ Y112P0! ⦄ := by
  rw [slot.Z155_loop3]
  apply SDN!
    (measure := fun (d_, j_) => j_.val)
    (inv := fun _ => True)
  · rintro ⟨d_, j_⟩ _
    simp only [slot.Z155_loop3.body]
    step*
    repeat' (split <;> step*)
    all_goals exact SV0!
  · trivial
@[step]
theorem u348 (len:C 512#usize) (sym m i d kraft) (hlen:u13 len.val 15) :
    slot.Z155_loop4 len sym m i d kraft ⦃ fun r => u13 r.1.val 15 ⦄ := by
  rw [slot.Z155_loop4]
  apply SDN!
    (measure := fun (_, i_, _) => m.val - i_.val)
    (inv := fun (len_, _, _) => u13 len_.val 15)
  · rintro ⟨len_, i_, kraft_⟩ hlen_
    dsimp only at hlen_
    simp only [slot.Z155_loop4.body]
    step*
    repeat' (split <;> step*)
    all_goals try exact SV0!
    all_goals
      refine ⟨?_, by exact SV0!⟩
      rw [a_post, Array.set_val_eq];exact u24 hlen_ _ _ (by exact SV0!)
  · exact hlen
@[step]
theorem u349 (freq n) (len:C 512#usize) (hlen:u13 len.val 15) :
    slot.Z155 freq n len ⦃ fun r => u13 r.val 15 ⦄ := by
  rw [slot.Z155]
  step*
  repeat' (split <;> step*)
  all_goals try exact SV0!
  all_goals apply u302 (by assumption) (by assumption) (by exact SV0!)
@[step]
theorem u358 (s:I) (a b lim:R) (k)
    (ha:a.val + lim.val ≤ s.length) (hb:b.val + lim.val ≤ s.length) :
    slot.Z165_loop s a b lim k ⦃ Y112P0! ⦄ := by
  rw [slot.Z165_loop]
  apply SDN!
    (measure := fun k_ => lim.val - k_.val)
    (inv := fun _ => True)
  · rintro k_ _
    simp only [slot.Z165_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals exact SV0!
  · trivial
@[step]
theorem u359 (s:I) (a b lim:R)
    (ha:a.val + lim.val ≤ s.length) (hb:b.val + lim.val ≤ s.length) :
    slot.Z165 s a b lim ⦃ Y112P0! ⦄ := Y122U4! slot.Z165
@[step]
theorem u360 (s) (i:R) (hi:i.val ≤ 2 ^ 31) :
    slot.Z171 s i ⦃ Y112P0! ⦄ := Y122U4! slot.Z171
@[step]
theorem u361 (s) (a b:R) (ha:a.val ≤ 2 ^ 31) (hb:b.val ≤ 2 ^ 31) :
    slot.Z172 s a b ⦃ Y112P0! ⦄ := Y122U4! slot.Z172
@[step]
theorem u362 (s) (p q k:R) (w) (hp:p.val ≤ 2 ^ 30) (hq:q.val ≤ 2 ^ 30) (hk:k.val ≤ 258) :
    slot.Z161_loop s p q k w ⦃ fun r => r.1.val ≤ 258 ⦄ := by
  rw [slot.Z161_loop]
  apply SDN!
    (measure := fun (k_, _) => 258 - k_.val)
    (inv := fun (k_, _) => k_.val ≤ 258)
  · rintro ⟨k_, ⟨w0, w1⟩⟩ hinv
    simp only [slot.Z161_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals exact SV0!
  · exact hk
@[step]
theorem u363 (s) (p q k:R) (hp:p.val ≤ 2 ^ 30) (hq:q.val ≤ 2 ^ 30) (hk:k.val ≤ 258) :
    slot.Z161 s p q k ⦃ fun r => r.1.val ≤ 258 ⦄ := Y122U4! slot.Z161
@[step]
theorem u372:slot.Z16 ⦃ fun x => x.val = 2147483648 ⦄ := by
  unfold slot.Z16;step*
@[step]
theorem u373:slot.Z18 ⦃ fun x => x.val = 536870912 ⦄ := by
  unfold slot.Z18;step*
theorem u374:8192 ≤ slot.Z45.val ∧ slot.Z45.val ≤ 1048576 := by simp [slot.Z45]
theorem C_HS_bounds:2 ≤ slot.Z47.val ∧ slot.Z47.val ≤ 65536 := by simp [slot.Z47]
theorem u375:slot.Z20.val = 544 := by simp [slot.Z20]
theorem u376:slot.Z22.val < 2 ^ 27 := by simp [slot.Z22]
theorem u377:slot.Z3.val ≤ 32 := by simp [slot.Z3]
theorem u378:slot.Z46.val ≤ 256 := by simp [slot.Z46]
theorem C_UNUSED_LIT_le:slot.Z31.val ≤ 65536 := by simp [slot.Z31]
theorem C_UNUSED_DIST_le:slot.Z28.val ≤ 65536 := by simp [slot.Z28]
theorem u379:slot.Z30.val ≤ 65536 := by simp [slot.Z30]
theorem u380:slot.Z29.val ≤ 65536 := by simp [slot.Z29]
theorem u381:slot.Z46.val ≤ 65536 := by simp [slot.Z46]
theorem u382:slot.Z25.val ≤ 65536 := by simp [slot.Z25]
theorem u383:slot.Z26.val ≤ 65536 := by simp [slot.Z26]
theorem u384:slot.Z27.val ≤ 65536 := by simp [slot.Z27]
theorem u385:slot.Z11.val ≤ 65535 := by simp [slot.Z11]
theorem C_STOP_DIV_pos:0 < slot.Z24.val := by simp [slot.Z24]
theorem u386:1 ≤ slot.Z32.val := by simp [slot.Z32]
theorem u387:1 ≤ slot.Z4.val ∧ slot.Z4.val ≤ 1048576 := by simp [slot.Z4]
theorem u388:slot.Z23.val ≤ 1048576 := by simp [slot.Z23]
theorem u389 (i:Nat) (h:i < 29):(slot.Z17.val[i]!).val ≤ 5 := by
  unfold slot.Z17;simp only [Array.make];revert i;decide
theorem u390 (i:Nat) (h:i < 30):(slot.Z12.val[i]!).val ≤ 13 := by
  unfold slot.Z12;simp only [Array.make];revert i;decide
@[step]
theorem u391 (i:R) (h:i.val < 29) :
    Array.index_usize slot.Z17 i ⦃ fun x => x.val ≤ 5 ⦄ := by
  have := u389 i.val h
  step*
  subst x_post
  rw [List.getElem!_eq_getElem?_getD, List.getElem?_eq_getElem (by exact SV0!)] at this
  exact this
@[step]
theorem u392 (i:R) (h:i.val < 30) :
    Array.index_usize slot.Z12 i ⦃ fun x => x.val ≤ 13 ⦄ := by
  have := u390 i.val h
  step*
  subst x_post
  rw [List.getElem!_eq_getElem?_getD, List.getElem?_eq_getElem (by exact SV0!)] at this
  exact this
@[step]
theorem u393 (x y:R) :
    lift (core.num.Usize.wrapping_add x y) ⦃ fun z => z = core.num.Usize.wrapping_add x y ∧
      (x.val + y.val ≤ Usize.max → z.val = x.val + y.val) ⦄ := by
  simp only [lift, WP.spec_ok, true_and]
  intro h
  rw [core.num.Usize.wrapping_add_val_eq, UScalar.size_UScalarTyUsize]
  apply Nat.mod_eq_of_lt
  exact SV0!
@[step]
theorem u394 (x y:W) :
    lift (core.num.U32.wrapping_add x y) ⦃ fun z => z = core.num.U32.wrapping_add x y ∧
      (x.val + y.val ≤ U32.max → z.val = x.val + y.val) ⦄ := by
  simp only [lift, WP.spec_ok, true_and]
  intro h
  rw [core.num.U32.wrapping_add_val_eq]
  apply Nat.mod_eq_of_lt
  exact SV0!
@[step]
theorem u395 (x y:Std.U64)
    (h:(x.val ≤ 4294967295 ∧ y.val ≤ 4294967295) ∨ x.val * y.val ≤ U64.max) :
    (x * y) ⦃ fun z => z.val = x.val * y.val ∧ (x.val ≤ 4294967295 → z.val ≤ 4294967295 * y.val) ⦄ := by
  have h':x.val * y.val ≤ U64.max := by
    rcases h with ⟨hx, hy⟩ | h
    · have := Nat.mul_le_mul hx hy
      exact SV0!
    · exact h
  step*
  all_goals
    refine ⟨z_post, fun hx => ?_⟩
    rw [z_post]
    exact Nat.mul_le_mul_right _ hx
@[step]
theorem u396 (x y:W)
    (h:(x.val ≤ 16777215 ∧ y.val ≤ 256) ∨ x.val * y.val ≤ U32.max) :
    (x * y) ⦃ fun z => z.val = x.val * y.val ∧ (y.val ≤ 256 → z.val ≤ 256 * x.val) ⦄ := by
  have h':x.val * y.val ≤ U32.max := by
    rcases h with ⟨hx, hy⟩ | h
    · have := Nat.mul_le_mul hx hy
      exact SV0!
    · exact h
  step*
  all_goals
    refine ⟨z_post, fun hy => ?_⟩
    rw [z_post, Nat.mul_comm]
    exact Nat.mul_le_mul_right _ hy
@[step]
theorem u397 (x y:Std.U64) (h:y.val ≠ 0) :
    (x / y) ⦃ fun z => z.val = x.val / y.val ∧ (x.val ≤ 65536 * y.val → z.val ≤ 65536) ⦄ := by
  obtain ⟨z, hz, hv⟩ := UScalar.div_spec x h
  rw [hz]
  simp only [WP.spec_ok]
  refine ⟨hv, fun hx => ?_⟩
  rw [hv]
  exact Nat.div_le_of_le_mul (by rw [Nat.mul_comm];exact hx)
@[step]
theorem u398 (x:R) :
    lift (UScalar.cast .U64 x) ⦃ fun y => y = UScalar.cast .U64 x ∧ y.val = x.val ⦄ := by
  simp only [lift, WP.spec_ok, true_and]
  apply UScalar.cast_val_mod_pow_of_inBounds_eq
  have := x.hBounds
  have:2 ^ UScalarTy.Usize.numBits ≤ 2 ^ UScalarTy.U64.numBits := by
    apply Nat.pow_le_pow_right (by decide)
    simp only [UScalarTy.numBits]
    cases System.Platform.numBits_eq <;> simp [*]
  omega
@[step]
theorem u399 (x:Std.U64) :
    lift (UScalar.cast .Usize x) ⦃ fun y => y = UScalar.cast .Usize x ∧ (x.val ≤ 4294967295 → y.val = x.val) ⦄ := by
  simp only [lift, WP.spec_ok, true_and]
  intro h
  apply UScalar.cast_val_mod_pow_of_inBounds_eq
  have:2 ^ 32 ≤ 2 ^ UScalarTy.Usize.numBits := by
    apply Nat.pow_le_pow_right (by decide)
    simp only [UScalarTy.numBits]
    exact u4
  omega
@[step]
theorem u400 {α:Type} (v:alloc.vec.Vec α) (x:α) (h:v.length < Usize.max) :
    alloc.vec.Vec.push v x ⦃ fun v1 => v1.val = v.val ++ [x] ∧ v1.length = v.length + 1 ⦄ := by
  step*
  all_goals
    exact ⟨v1_post, by simp [v1_post]⟩
theorem u401 {α:Type} (n:R):(alloc.vec.Vec.with_capacity α n).length = 0 := rfl
theorem u402 {α β:Type} {c:Prop} [Decidable c] {A B:Result α} {k:α → Result β}
    {P:β → Prop} (hA:c → (A >>= k) ⦃ P ⦄) (hB:¬c → (B >>= k) ⦃ P ⦄) :
    ((if c then A else B) >>= k) ⦃ P ⦄ := by
  by_cases h:c
  · rw [if_pos h];exact hA h
  · rw [if_neg h];exact hB h
theorem spine_knob_le {m:R} {r:O m} (hr:∀ x ∈ r.val, x.val ≤ 65536)
    {x:R} {j:Nat} {hj:j < r.val.length} (hx:x = r.val[j]):x.val ≤ 65536 := by
  subst hx;exact hr _ (List.getElem_mem _)
theorem spine_knob_skip {m:R} {r:O m}
    (hs:(r.val[0]!).val = 0 → 3 ≤ (r.val[2]!).val)
    {x0 x2:R} {h0:0 < r.val.length} {h2:2 < r.val.length}
    (hx0:x0 = r.val[0]) (hz:x0 = 0#usize) (hx2:x2 = r.val[2]):3 ≤ x2.val := by
  rw [getElem!_pos r.val 0 h0, getElem!_pos r.val 2 h2, ← hx0, ← hx2, hz] at hs
  exact hs rfl
end EA
set_option hygiene false in
local notation "Y122U7!" => (by
  refine ⟨Submission.Z466.EA.lz32_le x, ?_⟩
  by_cases h:x.val = 0
  · exact Or.inl h
  · right;rw [Submission.Z466.EA.lz32_eq x h];omega)
set_option hygiene false in
local notation "Y122U8!" q0__:max q1__:max => (by
  rw [q0__]
  apply SDN!
    (measure := fun (l_, _) => hi.val + 1 - l_.val)
    (inv := fun _ => True)
  · rintro ⟨l_, best_⟩ _
    simp only [q1__]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial)
set_option hygiene false in
local notation "Y122U9!" q0__:max q1__:max => (by
  rw [q0__]
  apply SDN!
    (measure := fun (_, z_) => cl.val - z_.val)
    (inv := fun (cost_, _) => cost_.length = cost.length)
  · rintro ⟨cost_, z_⟩ hinv
    simp only [q1__]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · rfl)
set_option hygiene false in
local notation "Y122U10!" q0__:max q1__:max => (by
  rw [q0__]
  apply SDN!
    (measure := fun (_, _, _, _, j_) => top.val - j_.val)
    (inv := fun (_, bd_, prev_, pd_, _) => prev.val ≤ prev_.val ∧ prev_.val ≤ i.val + 258 ∧
      pd_.val ≤ 32768 ∧ bd_.val ≤ 32767)
  · rintro ⟨best_, bd_, prev_, pd_, j_⟩ ⟨hp0, hp1, hpd_, hbd_⟩
    simp only [q1__]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact ⟨le_refl _, hprev, hpd, hbd⟩)
set_option hygiene false in
local notation "Y122U11!" q0__:max q1__:max => (by
  rw [q0__]
  apply SDN!
    (measure := fun (_, _, i_, _, _, _) => i_.val)
    (inv := fun ((cost_:alloc.vec.Vec W), (ch_:alloc.vec.Vec W), (i_:R), _,
        (xl_:R), (xd_:R)) =>
      cost_.length = cl.val ∧ ch_.length = ch.length ∧ i_.val ≤ i.val ∧ xl_.val ≤ 258 ∧ xd_.val ≤ 32768)
  · rintro ⟨cost_, ch_, i_, e_, xl_, xd_⟩ ⟨hc_, hch_, hi_, hxl_, hxd_⟩
    simp only [q1__]
    step*
    apply WP.spec_bind (Pₘ := fun (top:R) => top.val ≤ mb.length)
    · split <;> step* <;> scalar_tac
    rintro top htop
    step*
    apply WP.spec_bind (Pₘ := fun (el:R) => el.val ≤ 258)
    · split <;> step* <;> scalar_tac
    rintro el hel
    step*
    apply WP.spec_bind (Pₘ := fun (x:R × R × W × W) =>
      x.1.val ≤ 258 ∧ x.2.1.val ≤ 32768 ∧ x.2.2.2.val ≤ 32767)
    · repeat' (split <;> step*)
      all_goals scalar_tac
    rintro ⟨xl1, xd1, best2, bd1⟩ ⟨hxl1, hxd1, hbd1⟩
    step*
    apply WP.spec_bind (Pₘ := fun (x:alloc.vec.Vec W × W) => x.1.length = cost_.length)
    · split <;> step* <;> scalar_tac
    rintro ⟨cost1, i23⟩ hc1
    step*
    scalar_tac
  · exact ⟨hcl.symm, rfl, le_refl _, hxl, hxd⟩)
set_option hygiene false in
local notation "Y122U12!" q0__:max q1__:max => (by
  rw [q0__]
  apply SDN!
    (measure := fun (zf_, b_) => 512 - b_.val)
    (inv := fun _ => True)
  · rintro ⟨zf_, b_⟩ _
    simp only [q1__]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial)
set_option hygiene false in
local notation "Y122U13!" q0__:max q1__:max => (by
  rw [q0__]
  apply SDN!
    (measure := fun (zd_, b_) => 32 - b_.val)
    (inv := fun _ => True)
  · rintro ⟨zd_, b_⟩ _
    simp only [q1__]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial)
set_option hygiene false in
local notation "Y122U14!" q0__:max q1__:max q2__:max q3__:max => (by
  have hseg := Submission.Z466.EA.A_SEG_bounds
  rw [q0__]
  apply SDN!
    (measure := fun (_, _, _, _, _, _, _, _, a_) => pe.val - a_.val)
    (inv := fun (_, _, _, _, _, _, sb_, st_, a_) => sb_.val ≤ a_.val ∧ st_.val ≤ a_.val ∧
      a_.val ≤ pe.val + q1__ * q2__)
  · rintro ⟨cost_, ch_, lf_, df_, zf_, zd_, sb_, st_, a_⟩ ⟨hsb_, hst_, ha_⟩
    simp only [q3__]
    step*
    cases ‹R × R›
    step*
    all_goals scalar_tac
  · exact ⟨hsb, hst, ha⟩)
set_option hygiene false in
local notation "Y122U15!" q0__:max q1__:max => (by
  rw [q0__]
  apply SDN!
    (measure := fun (lf_, b_) => 512 - b_.val)
    (inv := fun _ => True)
  · rintro ⟨lf_, b_⟩ _
    simp only [q1__]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial)
set_option hygiene false in
local notation "Y122U16!" q0__:max q1__:max => (by
  rw [q0__]
  apply SDN!
    (measure := fun (df_, b_) => 32 - b_.val)
    (inv := fun _ => True)
  · rintro ⟨df_, b_⟩ _
    simp only [q1__]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial)
set_option hygiene false in
local notation "Y122U17!" q0__:max q1__:max => (by
  rw [q0__]
  apply SDN!
    (measure := fun (_, i_) => n.val + 1 - i_.val)
    (inv := fun (cost_, i_) => cost_.length = i_.val)
  · rintro ⟨cost_, i_⟩ hc_
    simp only [q1__]
    step*
    repeat' (split <;> step*)
    all_goals try simp only [alloc.vec.Vec.length, *, List.length_append, List.length_singleton]
    all_goals scalar_tac
  · exact hc)
set_option hygiene false in
local notation "Y122U18!" q0__:max q1__:max q2__:max => (by
  have hbt := Submission.Z466.EA.A_BLOCK_bounds
  have hseg := Submission.Z466.EA.A_SEG_bounds
  rw [q0__]
  apply SDN!
    (measure := fun (_, _, _, _, _, _, _, _, _, _, k_, _, _) => passes.val - k_.val)
    (inv := fun (_, _, _, _, _, _, _, _, _, (pe_:R), _, (p1_:R), (t_:R)) =>
      p0.val ≤ pe_.val ∧ pe_.val ≤ n.val ∧ (pe_.val = n.val ∨ p0.val + q1__ ≤ pe_.val) ∧
      t_.val ≤ need.val ∧ p0.val ≤ p1_.val ∧ p1_.val ≤ p0.val + 511 * t_.val)
  · rintro ⟨ch_, cost_, lit_, lc_, dc_, lf_, df_, sl_, sd_, pe_, k_, p1_, t_⟩ ⟨hpe0, hpe1, hpe2, ht_, hp10, hp11⟩
    simp only [q2__, Submission.Z466.EA.d1_ite_ok]
    step*
    apply WP.spec_bind (Pₘ := fun (x:alloc.vec.Vec W × alloc.vec.Vec W × Std.Array W 512#usize ×
        Std.Array W 32#usize × R × R × R) =>
        p0.val ≤ x.2.2.2.2.1.val ∧ x.2.2.2.2.1.val ≤ n.val ∧
        (x.2.2.2.2.1.val = n.val ∨ p0.val + q1__ ≤ x.2.2.2.2.1.val) ∧
        x.2.2.2.2.2.2.val ≤ need.val ∧ p0.val ≤ x.2.2.2.2.2.1.val ∧ x.2.2.2.2.2.1.val ≤ p0.val + 511 * x.2.2.2.2.2.2.val)
    · split
      · step*
        ·
          cases ‹R × R›
          step*
          apply WP.spec_bind (Pₘ := fun (z:alloc.vec.Vec W × alloc.vec.Vec W × Std.Array W 512#usize ×
              Std.Array W 32#usize × R) => p0.val ≤ z.2.2.2.2.val ∧ z.2.2.2.2.val ≤ n.val ∧
              (z.2.2.2.2.val = n.val ∨ p0.val + q1__ ≤ z.2.2.2.2.val))
          · repeat' (split <;> step*)
            all_goals scalar_tac
          rintro ⟨v, v1, a, a1, i6⟩ hi6
          step*
          all_goals scalar_tac
        ·
          apply WP.spec_bind (Pₘ := fun (lim:R) => lim.val ≤ pe_.val)
          · split
            all_goals step*
            all_goals scalar_tac
          rintro lim hlim
          step*
          cases ‹R × R›
          step*
          apply WP.spec_bind (Pₘ := fun (z:Std.Array W 512#usize × Std.Array W 32#usize × R) =>
              p0.val ≤ z.2.2.val ∧ z.2.2.val ≤ n.val ∧ (z.2.2.val = n.val ∨ p0.val + q1__ ≤ z.2.2.val))
          · repeat' (split <;> step*)
            all_goals scalar_tac
          rintro ⟨a, a1, i4⟩ hi4
          step*
          all_goals scalar_tac
        ·
          apply WP.spec_bind (Pₘ := fun (lim:R) => lim.val ≤ pe_.val)
          · split
            all_goals step*
            all_goals scalar_tac
          rintro lim hlim
          step*
          cases ‹R × R›
          step*
          apply WP.spec_bind (Pₘ := fun (z:Std.Array W 512#usize × Std.Array W 32#usize × R) =>
              p0.val ≤ z.2.2.val ∧ z.2.2.val ≤ n.val ∧ (z.2.2.val = n.val ∨ p0.val + q1__ ≤ z.2.2.val))
          · repeat' (split <;> step*)
            all_goals scalar_tac
          rintro ⟨a, a1, i4⟩ hi4
          step*
          all_goals scalar_tac
      · step*
        ·
          apply WP.spec_bind (Pₘ := fun (lim:R) => lim.val ≤ pe_.val)
          · split
            all_goals step*
            all_goals scalar_tac
          rintro lim hlim
          step*
          cases ‹R × R›
          step*
          apply WP.spec_bind (Pₘ := fun (z:Std.Array W 512#usize × Std.Array W 32#usize × R) =>
              p0.val ≤ z.2.2.val ∧ z.2.2.val ≤ n.val ∧ (z.2.2.val = n.val ∨ p0.val + q1__ ≤ z.2.2.val))
          · repeat' (split <;> step*)
            all_goals scalar_tac
          rintro ⟨a, a1, i4⟩ hi4
          step*
          all_goals scalar_tac
    rintro ⟨ch1, cost1, lf1, df1, pe1, p11, t1⟩ ⟨hq0, hq1, hq2, hq3, hq4, hq5⟩
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact ⟨hpe.1, hpe.2, hpe', ht, hp1.1, hp1.2⟩)
set_option hygiene false in
local notation "Y122U19!" q0__:max q1__:max q2__:max q3__:max => (by
  have hbt := Submission.Z466.EA.A_BLOCK_bounds
  rw [q0__]
  apply SDN!
    (measure := fun (_, _, _, _, _, _, _, _, _, _, _, p0_, _, _) => n.val - p0_.val)
    (inv := fun (_, _, _, _, _, _, _, _, _, _, _, _, used_, bpt_) => used_.val < q1__ ∧
      256 ≤ bpt_.val ∧ bpt_.val ≤ 130816)
  · rintro ⟨ch_, cost_, lit_, lc_, dc_, lf_, df_, bl_, bd_, sl_, sd_, p0_, used_, bpt_⟩ ⟨hused_, hbpt0, hbpt1⟩
    simp only [q2__, Submission.Z466.EA.d1_ite_ok]
    step*
    ·
      have:need.val * bpt_.val ≤ 16384 * 130816 := Nat.mul_le_mul (by scalar_tac) hbpt1
      scalar_tac
    apply WP.spec_bind (Pₘ := fun (pe:R) => p0_.val ≤ pe.val ∧ pe.val ≤ n.val ∧
      (pe.val = n.val ∨ p0_.val + q3__ ≤ pe.val))
    · split
      all_goals step*
      all_goals scalar_tac
    rintro pe hpe
    step*
    apply WP.spec_bind (Pₘ := fun (x:Std.Array W 512#usize × Std.Array W 32#usize × R) =>
      x.2.2.val < q1__)
    · split
      all_goals step*
      all_goals scalar_tac
    rintro ⟨bl1, bd1, used2⟩ hu2
    step*
    all_goals try (
      have hdiv:bpt1.val ≤ 130816 := by
        rw [bpt1_post];apply Nat.div_le_of_le_mul;scalar_tac
      by_cases hb:bpt1 < 256#usize
      all_goals simp only [hb, ite_true, ite_false])
    all_goals scalar_tac
  ·
    exact ⟨hused, hbpt.1, by omega⟩)
set_option hygiene false in
local notation "Y122U24!" => (by
  have hc:(UScalar.cast UScalarTy.U32 cur).val = cur.val :=
    UScalar.cast_val_mod_pow_of_inBounds_eq _ _ (by scalar_tac)
  split
  · step*
    all_goals first
      | exact ⟨by assumption, by scalar_tac, hl, hrl⟩
      | scalar_tac
  · step*
    all_goals first
      | exact ⟨by assumption, by scalar_tac, hll, hl⟩
      | scalar_tac)
set_option hygiene false in
local notation "Y122U25!" => (by
  refine ⟨?_, ?_, ?_, ?_, ?_⟩ <;> simp only [Std.Array.repeat_val] <;>
    first | exact Submission.Z466.EA.LeAll_replicate _ _ _ (by simp) | simp)
set_option hygiene false in
local notation "Y122U26!" q0__:max q1__:max => (by
  rw [q0__]
  step*
  all_goals
    have hc:c ∈ q1__ := by rw [c_post];exact List.getElem_mem _
    first
    | exact Submission.Z466.EA.spine_knob_le (spine_CFG_le c hc) (by assumption)
    | exact Submission.Z466.EA.spine_knob_skip (spine_CFG_skip c hc) (by assumption) (by assumption) (by assumption))
namespace EB
open Aeneas Aeneas.Std Result ControlFlow
set_option maxRecDepth 8192
set_option maxHeartbeats 1000000
set_option linter.unusedTactic false
set_option linter.unreachableTactic false
set_option linter.unusedSimpArgs false
set_option linter.unusedVariables false
open LZ77 (toks bytes bytes_getElem! Matches emit_lit emit_match)
@[local scalar_tac x &&& y]
theorem u407 (x y:Nat):x &&& y ≤ y := Nat.and_le_right
@[local scalar_tac x >>> y]
theorem u408 (x y:Nat):x >>> y ≤ x := Nat.shiftRight_le x y
@[local scalar_tac System.Platform.numBits]
theorem u409:32 ≤ System.Platform.numBits := EA.u4
@[local scalar_tac core.num.U32.leading_zeros x]
theorem u410 (x:W) :
    (core.num.U32.leading_zeros x).val ≤ 32 ∧
      (x.val = 0 ∨ (core.num.U32.leading_zeros x).val ≤ 31) := Y122U7!
@[local scalar_tac core.num.U64.leading_zeros x]
theorem u411 (x:Std.U64):(core.num.U64.leading_zeros x).val ≤ 64 := EA.u10 x
theorem mlen_loop_spec (input:I) (a b cap l0:R)
    (ha:a.val + cap.val ≤ input.length) (hb:b.val + cap.val ≤ input.length)
    (hl0:l0.val ≤ cap.val) (h0:Matches input a.val b.val l0.val) :
    slot.Z295_loop input a b cap l0 ⦃ Y112P6! ⦄ := by
  rw [slot.Z295_loop]
  apply SDN!
    (measure := fun l => cap.val - l.val)
    (inv := fun l => l.val ≤ cap.val ∧ Matches input a.val b.val l.val)
  · rintro l ⟨hle, hinv⟩
    simp only [slot.Z295_loop.body]
    have hmax:input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    step*
    refine ⟨by scalar_tac, ?_, by scalar_tac⟩
    rw [show l1.val = l.val + 1 by scalar_tac]
    apply LZ77.Matches.succ hinv
    rw [getElem!_pos _ _ (by scalar_tac), getElem!_pos _ _ (by scalar_tac)]
    simp_all
  · exact ⟨hl0, h0⟩
@[step]
theorem u412 (input:I) (a b cap:R)
    (ha:a.val + cap.val ≤ input.length) (hb:b.val + cap.val ≤ input.length) :
    slot.Z295 input a b cap ⦃ Y112P6! ⦄ :=
  mlen_loop_spec input a b cap 0#usize ha hb (by scalar_tac) (LZ77.Matches.zero input a.val b.val)
@[step]
theorem u413 (input:I) (p len dist:R) :
    slot.Z291 input p len dist ⦃ fun valid => valid = true →
      3 ≤ len.val ∧ len.val ≤ 258 ∧ 1 ≤ dist.val ∧ dist.val ≤ 32768 ∧ dist.val ≤ p.val ∧
      p.val + len.val ≤ input.length ∧ Matches input (p.val - dist.val) p.val len.val ⦄ := Y122U2! slot.Z291
theorem u414 (input:I) (plan out0:U)
    (n ntok0 p0:R) (hn:n.val = input.length) (hout:input.length ≤ out0.length)
    (hp0:p0.val ≤ n.val) (hntok0:ntok0.val ≤ p0.val)
    (hdec0:LZ77.decode (toks out0 ntok0.val) = some ((bytes input).take p0.val)) :
    slot.Z292_loop input plan out0 n ntok0 p0 ⦃ Y112P2! ⦄ := Y122U3! slot.Z292_loop slot.Z292_loop.body
@[step]
theorem u415 (input:I) (plan out:U)
    (hout:input.length ≤ out.length) :
    slot.Z292 input plan out ⦃ Y112P3! ⦄ := by
  rw [slot.Z292]
  exact u414 input plan out (Std.Slice.len input) 0#usize 0#usize (by simp) hout
    (by simp) (by simp) (by simp [toks, LZ77.decode])

@[local scalar_tac core.num.Usize.saturating_add x y]
theorem u416 (x y:R) :
    (core.num.Usize.saturating_add x y).val = min Std.Usize.max (x.val + y.val) := EA.u299 x y

@[step]
theorem u429 (lf0 lf z) :
    slot.Z266_loop0 lf0 lf z ⦃ Y112P0! ⦄ := by
  rw [slot.Z266_loop0]
  apply SDN!
    (measure := fun (lf_, z_) => 286 - z_.val)
    (inv := fun _ => True)
  · rintro ⟨lf_, z_⟩ _
    simp only [slot.Z266_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial
@[step]
theorem u430 (df dd i) :
    slot.Z266_loop1 df dd i ⦃ Y112P0! ⦄ := by
  rw [slot.Z266_loop1]
  apply SDN!
    (measure := fun (dd_, i_) => 30 - i_.val)
    (inv := fun _ => True)
  · rintro ⟨dd_, i_⟩ _
    simp only [slot.Z266_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial
@[step]
theorem u431 (lf i tl) :
    slot.Z266_loop2 lf i tl ⦃ Y112P0! ⦄ := by
  rw [slot.Z266_loop2]
  apply SDN!
    (measure := fun (i_, tl_) => 286 - i_.val)
    (inv := fun _ => True)
  · rintro ⟨i_, tl_⟩ _
    simp only [slot.Z266_loop2.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial
@[step]
theorem u432 (df i td) :
    slot.Z266_loop3 df i td ⦃ Y112P0! ⦄ := by
  rw [slot.Z266_loop3]
  apply SDN!
    (measure := fun (i_, td_) => 30 - i_.val)
    (inv := fun _ => True)
  · rintro ⟨i_, td_⟩ _
    simp only [slot.Z266_loop3.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial
@[step]
theorem u433 (lit) (hl:C 512#usize) (i) (ul:W) (hhl:EA.u13 hl.val 15) :
    slot.Z266_loop4 lit hl i ul ⦃ Y112P0! ⦄ := by
  rw [slot.Z266_loop4]
  apply SDN!
    (measure := fun (_, i_) => 256 - i_.val)
    (inv := fun _ => True)
  · rintro ⟨lit_, i_⟩ _
    simp only [slot.Z266_loop4.body]
    step*
    repeat' (split <;> step*)
    all_goals try (have := EA.u14 hhl i_.val (by scalar_tac))
    all_goals scalar_tac
  · trivial
@[step]
theorem u434 (lc) (hl:C 512#usize) (i) (ul:W) (hhl:EA.u13 hl.val 15) (hul:ul.val ≤ 1152) :
    slot.Z266_loop5 lc hl i ul ⦃ Y112P0! ⦄ := by
  rw [slot.Z266_loop5]
  apply SDN!
    (measure := fun (_, i_) => 259 - i_.val)
    (inv := fun _ => True)
  · rintro ⟨lc_, i_⟩ _
    simp only [slot.Z266_loop5.body]
    step*
    repeat' (split <;> step*)
    all_goals try (have := EA.u14 hhl i2.val (by scalar_tac))
    all_goals scalar_tac
  · trivial
@[step]
theorem u435 (dc) (i:R) (hd:C 512#usize) (ud:W) (hhd:EA.u13 hd.val 15) (hud:ud.val ≤ 1152) :
    slot.Z266_loop6 dc i hd ud ⦃ Y112P0! ⦄ := by
  rw [slot.Z266_loop6]
  apply SDN!
    (measure := fun (_, i_) => 30 - i_.val)
    (inv := fun _ => True)
  · rintro ⟨dc_, i_⟩ _
    simp only [slot.Z266_loop6.body]
    step*
    repeat' (split <;> step*)
    all_goals try (have := EA.u14 hhd i_.val (by scalar_tac))
    all_goals scalar_tac
  · trivial
@[step]
theorem u436 (lf0 df lit lc dc) :
    slot.Z266 lf0 df lit lc dc ⦃ Y112P0! ⦄ := by
  rw [slot.Z266]
  step*
  all_goals exact EA.u46 _ _ _ (by simp)

@[step]
theorem u437 (s:I) (kid) (pos depth oldest:R) (mb) (cur best:R) (seen:W) (lo_at hi_at lo_len hi_len steps:R)
    (hpos:pos.val + 266 ≤ s.length) (hn26:s.length < 67108864) (hlo:lo_len.val ≤ 258) (hhi:hi_len.val ≤ 258) (hbest:2 ≤ best.val) :
    slot.Z268_loop s kid pos depth mb oldest cur best seen lo_at hi_at lo_len hi_len steps ⦃ Y112P0! ⦄ := by
  rw [slot.Z268_loop]
  apply SDN!
    (measure := fun (_, _, _, _, _, _, _, _, _, steps_) => depth.val - steps_.val)
    (inv := fun (_, _, _, best_, _, _, _, lo_len_, hi_len_, _) => lo_len_.val ≤ 258 ∧ hi_len_.val ≤ 258 ∧ 2 ≤ best_.val)
  · rintro ⟨kid_, mb_, cur_, best_, seen_, lo_at_, hi_at_, lo_len_, hi_len_, steps_⟩ ⟨hlo_, hhi_, hbest_⟩
    simp only [slot.Z268_loop.body, Submission.Z466.EA.d1_ite_ok]
    step*
    · split <;> omega
    apply WP.spec_bind (Pₘ := fun (x:alloc.vec.Vec W × R × W) => 2 ≤ x.2.1.val)
    · split
      · step*
        repeat' (split <;> step*)
        all_goals scalar_tac
      · step*
        repeat' (split <;> step*)
        all_goals scalar_tac
    rintro ⟨mb1, best1, seen1⟩ hb1
    step*
    apply WP.spec_bind (Pₘ := fun (x:Std.Array W 65536#usize × R × R × R ×
        R × R) => x.2.2.2.2.1.val ≤ 258 ∧ x.2.2.2.2.2.val ≤ 258)
    · repeat' (split <;> step*)
      all_goals scalar_tac
    rintro ⟨kid1, cur1, lo_at1, hi_at1, lo_len2, hi_len1⟩ ⟨hl2, hh1⟩
    step*
    all_goals scalar_tac
  · exact ⟨hlo, hhi, hbest⟩
@[step]
theorem u438 (s:I) (head kid h3 rct) (pos:R) (pre depth mb) (hpos:pos.val + 266 ≤ s.length)
    (hn26:s.length < 67108864) :
    slot.Z268 s head kid h3 rct pos pre depth mb ⦃ Y112P0! ⦄ := by
  obtain ⟨q, t, h, c3, cr, cur⟩ := pre
  rw [slot.Z268]
  apply WP.spec_bind (Pₘ := fun (_:R) => True)
  · split
    all_goals step*
  rintro oldest -
  step*
  apply WP.spec_bind (Pₘ := fun (x:alloc.vec.Vec W × R) => 2 ≤ x.2.val)
  · repeat' (split <;> step*)
    all_goals scalar_tac
  rintro ⟨mb1, best⟩ hb
  step*
  apply WP.spec_bind (Pₘ := fun (x:alloc.vec.Vec W × R) => 2 ≤ x.2.val)
  · repeat' (split <;> step*)
    all_goals scalar_tac
  rintro ⟨mb2, best1⟩ hb1
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac
set_option maxHeartbeats 4000000 in
@[step]
theorem u439 (i:W) (s:I) (mp:alloc.vec.Vec W) (mb depth) (skip n:R) (head kid h3 rct) (i1 cl cd:R) (nq nt nh n3 nr nc)
    (hn:n.val = s.length) (hn26:s.length < 67108864) (hi:i.val < 32) (hskip:3 ≤ skip.val)
    (hmp:mp.length ≤ i1.val + 1) (hcd:1 ≤ cd.val) :
    slot.Z264_loop i s mp mb depth skip n head kid h3 rct i1 cl cd nq nt nh n3 nr nc ⦃ Y112P0! ⦄ := by
  rw [slot.Z264_loop]
  apply SDN!
    (measure := fun (_, _, _, _, _, _, i1_, _, _, _, _, _, _, _, _) => n.val - i1_.val)
    (inv := fun ((mp_:alloc.vec.Vec W), _, _, _, _, _, (i1_:R), _, (cd_:R), _, _, _, _, _, _) =>
      mp_.length ≤ i1_.val + 1 ∧ 1 ≤ cd_.val)
  · rintro ⟨mp_, mb_, head_, kid_, h3_, rct_, i1_, cl_, cd_, nq_, nt_, nh_, n3_, nr_, nc_⟩ ⟨hmp_, hcd_⟩
    unfold slot.Z264_loop.body
    simp only [Submission.Z466.EA.d1_ite_ok, EA.u301]
    step*
    apply WP.spec_bind (Pₘ := fun (x:alloc.vec.Vec W × Std.Array W 65536#usize × Std.Array W 65536#usize ×
        Std.Array W 32768#usize × Std.Array W 65536#usize × R × R × Std.U64 × R ×
        R × R × R × R) => 1 ≤ x.2.2.2.2.2.2.1.val)
    · split
      · step*
        ·
          apply WP.spec_bind (Pₘ := fun (y:alloc.vec.Vec W × Std.Array W 65536#usize ×
              Std.Array W 65536#usize × Std.Array W 32768#usize × Std.Array W 65536#usize ×
              R × R × R × R × R) => 1 ≤ y.2.2.2.2.2.2.1.val)
          · split
            ·
              step*
              split
              all_goals step*
              all_goals scalar_tac
            ·
              step*
              apply WP.spec_bind (Pₘ := fun (z:Std.Array W 65536#usize × Std.Array W 65536#usize ×
                  Std.Array W 32768#usize × Std.Array W 65536#usize × R × R) =>
                  1 ≤ z.2.2.2.2.2.val)
              · repeat' (split <;> step*)
                all_goals scalar_tac
              rintro ⟨head3, kid3, h33, rct3, cl2, cd2⟩ hcd2
              step*
          rintro ⟨v, a, a1, a2, a3, i17, i18, i19, i20, i21⟩ h18
          step*
        ·
          apply WP.spec_bind (Pₘ := fun (_:alloc.vec.Vec W × Std.Array W 32768#usize) => True)
          · repeat' (split <;> step*)
            all_goals scalar_tac
          rintro ⟨v, a⟩ -
          step*
      · step*
        apply WP.spec_bind (Pₘ := fun (_:alloc.vec.Vec W × Std.Array W 32768#usize) => True)
        · repeat' (split <;> step*)
          all_goals scalar_tac
        rintro ⟨v, a⟩ -
        step*
    rintro ⟨mb1, head1, kid1, h31, rct1, cl1, cd1, nq1, nt1, nh1, n31, nr1, nc1⟩ hcd1
    step*
    apply WP.spec_bind (Pₘ := fun (_:R) => True)
    · split
      all_goals step*
    rintro cl2 -
    step*
    simp only [alloc.vec.Vec.length, *, List.length_append, List.length_singleton]
    scalar_tac
  · exact ⟨hmp, hcd⟩
@[step]
theorem u440 (s:I) (mp:alloc.vec.Vec W) (mb depth) (skip:R)
    (hn26:s.length < 67108864) (hskip:3 ≤ skip.val) (hmp:mp.length = 0) :
    slot.Z264 s mp mb depth skip ⦃ Y112P0! ⦄ := by
  have hhb := EA.u36
  rw [slot.Z264]
  step*
  all_goals try simp only [alloc.vec.Vec.length, *, List.length_append, List.length_singleton]
  all_goals scalar_tac
@[step]
theorem u442 (k passes tail final_tail):slot.Z267 k passes tail final_tail ⦃ Y112P0! ⦄ := by
  rw [slot.Z267]
  step*
  repeat' (split <;> step*)
@[local step]
theorem u446:slot.Z66 ⦃ Y112P0! ⦄ := by
  unfold slot.Z66
  have h := EA.u4
  step*
theorem u449 {n:R} (a:Std.Array W n) (j:R) (B:Nat)
    (h:EA.u13 a.val B) (hj:j.val < a.length) :
    a.index_usize j ⦃ fun x => x = a.val[j.val] ∧ x.val ≤ B ⦄ := by
  have := Std.Array.index_usize_spec a j hj
  apply WP.spec_mono this
  intro x hx
  exact ⟨hx, hx ▸ EA.u14 h j.val (by simpa using hj)⟩
theorem u450 {n:R} (a:Std.Array W n) (j:R) (x:W)
    (B:Nat) (h:EA.u13 a.val B) (hx:x.val < B + 1) (hj:j.val < a.length) :
    a.update j x ⦃ fun r => r = a.set j x ∧ EA.u13 r.val B ⦄ := by
  have := Std.Array.update_spec a j x hj
  apply WP.spec_mono this
  intro r hr
  exact ⟨hr, by rw [hr, Std.Array.set_val_eq];exact EA.u24 h _ _ (by omega)⟩
def u455 (l:V) (base K:Nat):Prop :=
  ∀ z, z < slot.Z64.val → ∀ x, l[base + z]? = some x → x.val ≤ K
def engB_Zero (l:V) (base n:Nat):Prop :=
  ∀ z, z < n → ∀ x, l[base + z]? = some x → x.val = 0
theorem u458 {l:V} {base K:Nat} (h:u455 l base K) {idx:Nat}
    {x:W} (h1:base ≤ idx) (h2:idx < base + slot.Z64.val) (hl:idx < l.length)
    (hx:x = l[idx]):x.val ≤ K := by
  have hx':l[base + (idx - base)]? = some x := by
    rw [show base + (idx - base) = idx by omega, hx];exact List.getElem?_eq_getElem hl
  exact h (idx - base) (by omega) _ hx'
theorem engB_Zero_zero (l:V) (base:Nat):engB_Zero l base 0 :=
  fun z hz => absurd hz (Nat.not_lt_zero z)
theorem engB_Zero_set {l:V} {base n:Nat} (h:engB_Zero l base n) (idx:Nat)
    (hidx:idx = base + n):engB_Zero (l.set idx 0#u32) base (n + 1) := by
  intro z hz x hx
  rw [List.getElem?_set] at hx
  split at hx
  · split at hx
    · cases hx;rfl
    · cases hx
  · exact h z (by omega) x hx
theorem engB_Zero_push {l:V} {base n:Nat} (h:engB_Zero l base n)
    (hlen:l.length = base + n):engB_Zero (l ++ [0#u32]) base (n + 1) := by
  intro z hz x hx
  by_cases hzn:z < n
  · rw [List.getElem?_append_left (by omega)] at hx
    exact h z hzn x hx
  · have:base + z = l.length := by omega
    rw [this, List.getElem?_concat_length] at hx
    cases hx;rfl
theorem engB_Zero_Blk {l:V} {base n:Nat} (h:engB_Zero l base n)
    (hn:slot.Z64.val ≤ n):u455 l base 0 :=
  fun z hz x hx => le_of_eq (h z (by omega) x hx)
set_option hygiene false in
local notation "Y122U20!" q0__:max q1__:max q2__:max => (by
  rw [q0__]
  apply SDN!
    (measure := fun (_, z') => q1__ - z'.val)
    (inv := fun (bf', z') => base.val + z'.val ≤ bf'.length ∧ bf.length ≤ bf'.length ∧
      engB_Zero bf'.val base.val z'.val)
  · rintro ⟨bf', z'⟩ ⟨h1, h2, h3⟩
    simp only [q2__]
    split
    · step*
      split
      · step*
        obtain ⟨x1, x2⟩ := x
        simp only at x_post1 x_post2 ⊢
        subst x_post2
        step*
        refine ⟨by simp;scalar_tac, by simp;scalar_tac, ?_, by scalar_tac⟩
        simp only [alloc.vec.Vec.set_val_eq]
        rw [show z1.val = z'.val + 1 by scalar_tac]
        exact engB_Zero_set h3 i.val (by scalar_tac)
      · step*
        have hl:bf1.length = bf'.length + 1 := by simp [bf1_post1]
        refine ⟨by scalar_tac, by scalar_tac, ?_, by scalar_tac⟩
        rw [bf1_post1, show z1.val = z'.val + 1 by scalar_tac]
        exact engB_Zero_push h3 (by scalar_tac)
    · simp only [WP.spec_ok]
      exact ⟨by scalar_tac, h2, engB_Zero_Blk h3 (by scalar_tac)⟩
  · exact ⟨by simpa using hz, le_refl _, engB_Zero_zero _ _⟩)
def u467 (n:Nat) (bf bs:alloc.vec.Vec W) (nb pos t:Nat):Prop :=
  (pos ≤ n ∧ t ≤ pos ∧ t ≤ nb * slot.Z45.val ∧ nb * slot.Z45.val < t + slot.Z45.val ∧
    nb * slot.Z64.val ≤ bf.length ∧ nb ≤ bs.length) ∧
    (0 < nb → u455 bf.val ((nb - 1) * slot.Z64.val) pos)
theorem engB_TPL.u468 {n:Nat} {bf bs:alloc.vec.Vec W} {nb pos t:Nat}
    (h1:pos ≤ n ∧ t ≤ pos ∧ t ≤ nb * slot.Z45.val ∧
      nb * slot.Z45.val < t + slot.Z45.val ∧ nb * slot.Z64.val ≤ bf.length ∧
      nb ≤ bs.length)
    (h2:0 < nb → u455 bf.val ((nb - 1) * slot.Z64.val) pos):u467 n bf bs nb pos t :=
  ⟨h1, h2⟩
def u474 (m:Nat) (bf bs:alloc.vec.Vec W) (nb inb j:Nat):Prop :=
  j ≤ m ∧ nb * slot.Z64.val ≤ bf.length ∧ nb ≤ bs.length ∧ (nb = 0 → inb = slot.Z45.val) ∧
    inb ≤ slot.Z45.val ∧ (0 < nb → (nb - 1) * slot.Z45.val + inb ≤ m - j)
def u475 (m L:Nat) (bf bs:alloc.vec.Vec W) (nb inb j:Nat):Prop :=
  (L ≤ bf.length ∧ u474 m bf bs nb inb j) ∧
    (0 < nb → u455 bf.val ((nb - 1) * slot.Z64.val) (m - j))
theorem engB_TSL.u476 {m L:Nat} {bf bs:alloc.vec.Vec W} {nb inb j:Nat}
    (h1:L ≤ bf.length ∧ j ≤ m ∧ nb * slot.Z64.val ≤ bf.length ∧ nb ≤ bs.length ∧
      (nb = 0 → inb = slot.Z45.val) ∧ inb ≤ slot.Z45.val ∧
      (0 < nb → (nb - 1) * slot.Z45.val + inb ≤ m - j))
    (h2:0 < nb → u455 bf.val ((nb - 1) * slot.Z64.val) (m - j)) :
    u475 m L bf bs nb inb j :=
  ⟨⟨h1.1, h1.2⟩, h2⟩
set_option hygiene false in
local notation "Y122U21!" q0__:max q1__:max => (by
  rw [q0__]
  apply SDN!
    (measure := fun (tl_, k_) => 286 - k_.val)
    (inv := fun _ => True)
  · rintro ⟨tl_, k_⟩ _
    simp only [q1__]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial)
set_option hygiene false in
local notation "Y122U22!" q0__:max q1__:max => (by
  rw [q0__]
  apply SDN!
    (measure := fun (k_, td_) => 30 - k_.val)
    (inv := fun _ => True)
  · rintro ⟨k_, td_⟩ _
    simp only [q1__]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial)
set_option hygiene false in
local notation "Y122U23!" q0__:max q1__:max => (by
  rw [q0__]
  apply SDN!
    (measure := fun (_, _, l') => ml.val + 1 - l'.val)
    (inv := fun _ => True)
  · rintro ⟨best', choice', l'⟩ _
    simp only [q1__]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial)
attribute [local step] u449 u450 in
theorem u511 (t:Std.Array W 65536#usize) (lt ls rs cs cur l ll rl:R) (i L:Nat)
    (hT:EA.u13 t.val i) (hcur:cur.val ≤ i) (hi:i < 67108864) (hcs:cs.val ≤ 65534)
    (hl:l.val ≤ L) (hll:ll.val ≤ L) (hrl:rl.val ≤ L) :
    (if lt = 1#usize then do
        let i16 ← ls % slot.Z47
        let i17 ← lift (UScalar.cast UScalarTy.U32 cur)
        let a5 ← t.update i16 i17
        let ls2 ← cs + 1#usize
        let i18 ← ls2 % slot.Z47
        let i19 ← a5.index_usize i18
        let cur2 ← lift (UScalar.cast UScalarTy.Usize i19)
        ok (a5, cur2, ls2, rs, l, rl)
      else do
        let i16 ← rs % slot.Z47
        let i17 ← lift (UScalar.cast UScalarTy.U32 cur)
        let a5 ← t.update i16 i17
        let i18 ← cs % slot.Z47
        let i19 ← a5.index_usize i18
        let cur2 ← lift (UScalar.cast UScalarTy.Usize i19)
        ok (a5, cur2, ls, cs, ll, l)) ⦃
      fun (x:Std.Array W 65536#usize × R × R × R × R × R) =>
      EA.u13 x.1.val i ∧ x.2.1.val ≤ i ∧ x.2.2.2.2.1.val ≤ L ∧ x.2.2.2.2.2.val ≤ L ⦄ := Y122U24!
def u512 (i:Nat) (tree:Std.Array W 65536#usize) (pn:Std.Array W 32#usize)
    (step cur ll rl fuel nr bl bd:Nat):Prop :=
  EA.u13 tree.val i ∧ EA.u13 pn.val i ∧ cur ≤ i ∧ ll ≤ 2 ^ 30 ∧ rl ≤ 2 ^ 30 ∧ step + fuel ≤ 2 ^ 20 ∧
    nr ≤ slot.Z39.val ∧ bl ≤ 2 ^ 30 ∧ bd ≤ i
theorem engB_DInv.u513 {i:Nat} {tree:Std.Array W 65536#usize} {pn:Std.Array W 32#usize}
    {step cur ll rl fuel nr bl bd:Nat} (h1:EA.u13 tree.val i) (h2:EA.u13 pn.val i)
    (h3:cur ≤ i ∧ ll ≤ 2 ^ 30 ∧ rl ≤ 2 ^ 30 ∧ step + fuel ≤ 2 ^ 20 ∧ nr ≤ slot.Z39.val ∧
      bl ≤ 2 ^ 30 ∧ bd ≤ i) :
    u512 i tree pn step cur ll rl fuel nr bl bd :=
  ⟨h1, h2, h3⟩
abbrev u514 := Std.Array W 65536#usize × Std.Array W 32#usize × Std.Array W 32#usize ×
  Std.Array W 32#usize × R × R × R × R × R × R × R ×
  R × R × R × R × R × R
abbrev u515 := Std.Array W 65536#usize × Std.Array W 32#usize × Std.Array W 32#usize ×
  Std.Array W 32#usize × R × R × R × R × R
def u516 (i fuel:Nat) (r:ControlFlow u514 u515):Prop :=
  match r with
  | .done y => EA.u13 y.1.val i ∧ EA.u13 y.2.1.val i ∧ y.2.2.2.2.2.1.val ≤ slot.Z39.val ∧
      y.2.2.2.2.2.2.2.1.val ≤ 2 ^ 30 ∧ y.2.2.2.2.2.2.2.2.val ≤ i
  | .cont x' => u512 i x'.1 x'.2.1 x'.2.2.2.2.1.val x'.2.2.2.2.2.1.val x'.2.2.2.2.2.2.2.2.1.val
      x'.2.2.2.2.2.2.2.2.2.1.val x'.2.2.2.2.2.2.2.2.2.2.1.val x'.2.2.2.2.2.2.2.2.2.2.2.2.2.1.val
      x'.2.2.2.2.2.2.2.2.2.2.2.2.2.2.2.1.val x'.2.2.2.2.2.2.2.2.2.2.2.2.2.2.2.2.val ∧
      x'.2.2.2.2.2.2.2.2.2.2.1.val < fuel
end EB
namespace EC
open Aeneas Aeneas.Std Result ControlFlow
open LZ77 (toks bytes)
set_option maxRecDepth 8192
set_option maxHeartbeats 4000000
set_option hygiene false in
local notation "T6!" => (by exact Submission.Z466.EA.u11 x)
namespace EA
open Aeneas Aeneas.Std Result ControlFlow
set_option maxRecDepth 8192
set_option maxHeartbeats 1000000
set_option linter.unusedTactic false
set_option linter.unreachableTactic false
set_option linter.unusedSimpArgs false
set_option linter.unusedVariables false
open LZ77 (toks bytes bytes_getElem! Matches emit_lit emit_match)
@[local scalar_tac x &&& y]
theorem u543 (x y:Nat):x &&& y ≤ y := Nat.and_le_right
@[local scalar_tac x >>> y]
theorem u544 (x y:Nat):x >>> y ≤ x := Nat.shiftRight_le x y
@[local scalar_tac System.Platform.numBits]
theorem u545:32 ≤ System.Platform.numBits := EA.u4
@[local scalar_tac core.num.U32.leading_zeros x]
theorem u546 (x:W) :
    (core.num.U32.leading_zeros x).val ≤ 32 ∧
      (x.val = 0 ∨ (core.num.U32.leading_zeros x).val ≤ 31) := T6!
@[local scalar_tac core.num.U64.leading_zeros x]
theorem u547 (x:Std.U64):(core.num.U64.leading_zeros x).val ≤ 64 := EA.u10 x
@[local scalar_tac core.num.Usize.saturating_add x y]
theorem u548 (x y:R) :
    (core.num.Usize.saturating_add x y).val = min Std.Usize.max (x.val + y.val) := EA.u299 x y
set_option hygiene false in
local notation "T9!" q0__:max q1__:max => (by
  rw [q0__]
  apply SDN!
    (measure := fun (_, z_) => cl.val - z_.val)
    (inv := fun (cost_, _) => cost_.length = cost.length)
  · rintro ⟨cost_, z_⟩ hinv
    simp only [q1__]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · rfl)
set_option hygiene false in
local notation "T10!" q0__:max q1__:max => (by
  rw [q0__]
  apply SDN!
    (measure := fun (mbest_, at0_, l_) => stop.val + 1 - at0_.val)
    (inv := fun _ => True)
  · rintro ⟨mbest_, at0_, l_⟩ _
    simp only [q1__]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial)

attribute [local step] EB.u446
set_option hygiene false in
local notation "T14!" q0__:max q1__:max q2__:max => (by
  rw [q0__]
  apply SDN!
    (measure := fun (_, z') => q1__ - z'.val)
    (inv := fun (bf', z') => base.val + z'.val ≤ bf'.length ∧ bf.length ≤ bf'.length ∧
      Submission.Z466.EB.engB_Zero bf'.val base.val z'.val)
  · rintro ⟨bf', z'⟩ ⟨h1, h2, h3⟩
    simp only [q2__]
    split
    · step*
      split
      · step*
        obtain ⟨x1, x2⟩ := x
        simp only at x_post1 x_post2 ⊢
        subst x_post2
        step*
        refine ⟨by simp;scalar_tac, by simp;scalar_tac, ?_, by scalar_tac⟩
        simp only [alloc.vec.Vec.set_val_eq]
        rw [show z1.val = z'.val + 1 by scalar_tac]
        exact Submission.Z466.EB.engB_Zero_set h3 i.val (by scalar_tac)
      · step*
        have hl:bf1.length = bf'.length + 1 := by simp [bf1_post1]
        refine ⟨by scalar_tac, by scalar_tac, ?_, by scalar_tac⟩
        rw [bf1_post1, show z1.val = z'.val + 1 by scalar_tac]
        exact Submission.Z466.EB.engB_Zero_push h3 (by scalar_tac)
    · simp only [WP.spec_ok]
      exact ⟨by scalar_tac, h2, Submission.Z466.EB.engB_Zero_Blk h3 (by scalar_tac)⟩
  · exact ⟨by simpa using hz, le_refl _, Submission.Z466.EB.engB_Zero_zero _ _⟩)
set_option hygiene false in
local notation "T15!" q0__:max q1__:max => (by
  rw [q0__]
  apply SDN!
    (measure := fun (tl_, k_) => 286 - k_.val)
    (inv := fun _ => True)
  · rintro ⟨tl_, k_⟩ _
    simp only [q1__]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial)
set_option hygiene false in
local notation "T16!" q0__:max q1__:max => (by
  rw [q0__]
  apply SDN!
    (measure := fun (k_, td_) => 30 - k_.val)
    (inv := fun _ => True)
  · rintro ⟨k_, td_⟩ _
    simp only [q1__]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial)
set_option hygiene false in
local notation "T17!" q0__:max q1__:max => (by
  rw [q0__]
  apply SDN!
    (measure := fun (_, _, l') => ml.val + 1 - l'.val)
    (inv := fun _ => True)
  · rintro ⟨best', choice', l'⟩ _
    simp only [q1__]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial)
def u550 (i:Nat) (tree:Std.Array W 131072#usize) (pn:Std.Array W 32#usize)
    (step cur ll rl fuel nr bl bd:Nat):Prop :=
  EA.u13 tree.val i ∧ EA.u13 pn.val i ∧ cur ≤ i ∧ ll ≤ 2 ^ 30 ∧ rl ≤ 2 ^ 30 ∧ step + fuel ≤ 2 ^ 20 ∧
    nr ≤ slot.Z39.val ∧ bl ≤ 2 ^ 30 ∧ bd ≤ i
theorem engB_DInv.u551 {i:Nat} {tree:Std.Array W 131072#usize} {pn:Std.Array W 32#usize}
    {step cur ll rl fuel nr bl bd:Nat} (h1:EA.u13 tree.val i) (h2:EA.u13 pn.val i)
    (h3:cur ≤ i ∧ ll ≤ 2 ^ 30 ∧ rl ≤ 2 ^ 30 ∧ step + fuel ≤ 2 ^ 20 ∧ nr ≤ slot.Z39.val ∧
      bl ≤ 2 ^ 30 ∧ bd ≤ i) :
    u550 i tree pn step cur ll rl fuel nr bl bd :=
  ⟨h1, h2, h3⟩
abbrev u552 := Std.Array W 131072#usize × Std.Array W 32#usize × Std.Array W 32#usize ×
  Std.Array W 32#usize × R × R × R × R × R × R × R ×
  R × R × R × R × R × R
abbrev u553 := Std.Array W 131072#usize × Std.Array W 32#usize × Std.Array W 32#usize ×
  Std.Array W 32#usize × R × R × R × R × R
def u554 (i fuel:Nat) (r:ControlFlow u552 u553):Prop :=
  match r with
  | .done y => EA.u13 y.1.val i ∧ EA.u13 y.2.1.val i ∧ y.2.2.2.2.2.1.val ≤ slot.Z39.val ∧
      y.2.2.2.2.2.2.2.1.val ≤ 2 ^ 30 ∧ y.2.2.2.2.2.2.2.2.val ≤ i
  | .cont x' => u550 i x'.1 x'.2.1 x'.2.2.2.2.1.val x'.2.2.2.2.2.1.val x'.2.2.2.2.2.2.2.2.1.val
      x'.2.2.2.2.2.2.2.2.2.1.val x'.2.2.2.2.2.2.2.2.2.2.1.val x'.2.2.2.2.2.2.2.2.2.2.2.2.2.1.val
      x'.2.2.2.2.2.2.2.2.2.2.2.2.2.2.2.1.val x'.2.2.2.2.2.2.2.2.2.2.2.2.2.2.2.2.val ∧
      x'.2.2.2.2.2.2.2.2.2.2.1.val < fuel
set_option hygiene false in
local notation "T19!" q0__:max q1__:max => (by
  have h1 := Submission.Z466.EA.C_UNUSED_LIT_le
  have h2 := Submission.Z466.EA.C_UNUSED_DIST_le
  have h3 := Submission.Z466.EA.C_STOP_DIV_pos
  rw [q0__]
  apply SDN!
    (measure := fun (_, _, _, _, pass') => passes.val - pass'.val)
    (inv := fun (_, _, b', _, _) => b'.length ≤ 1048576)
  · rintro ⟨out', models', b', le', pass'⟩ hb'
    simp only [q1__]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact hnb)
end EA
namespace EG
open Aeneas Aeneas.Std Result ControlFlow
set_option maxRecDepth 8192
set_option maxHeartbeats 1000000
set_option linter.unusedTactic false
set_option linter.unreachableTactic false
set_option linter.unusedSimpArgs false
set_option linter.unusedVariables false
open LZ77 (toks bytes bytes_getElem! Matches emit_lit emit_match)
@[local scalar_tac x &&& y]
theorem u563 (x y:Nat):x &&& y ≤ y := Nat.and_le_right
@[local scalar_tac x >>> y]
theorem u564 (x y:Nat):x >>> y ≤ x := Nat.shiftRight_le x y
@[local scalar_tac System.Platform.numBits]
theorem u565:32 ≤ System.Platform.numBits := EA.u4
@[local scalar_tac core.num.U32.leading_zeros x]
theorem u566 (x:W) :
    (core.num.U32.leading_zeros x).val ≤ 32 ∧
      (x.val = 0 ∨ (core.num.U32.leading_zeros x).val ≤ 31) := T6!
@[local scalar_tac core.num.U64.leading_zeros x]
theorem u567 (x:Std.U64):(core.num.U64.leading_zeros x).val ≤ 64 := EA.u10 x
theorem u568:1 ≤ slot.Z8.val := by simp [slot.Z8]
theorem u569:slot.Z55.val * slot.Z8.val < 4194304 := by
  simp [slot.Z55, slot.Z8]
end EG
namespace EL
set_option hygiene false in
local notation "T9!" q0__:max q1__:max => (by
  (
  rw [q0__]
  apply SDN!
    (measure := fun l => cap.val - l.val)
    (inv := fun l => l.val ≤ cap.val ∧ LZ77.Matches input a.val b.val l.val)
  · rintro l ⟨hle, hinv⟩
    simp only [q1__]
    split
    case isTrue hlt =>
      have hmax:input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
      step*
      all_goals first
        | scalar_tac
        | exact ⟨hle, hinv⟩
        | (refine ⟨by scalar_tac, ?_, by scalar_tac⟩
           rw [show l1.val = l.val + 1 by scalar_tac]
           apply LZ77.Matches.succ hinv
           rw [← i_post, ← i2_post, getElem!_pos _ _ (by scalar_tac),
             getElem!_pos _ _ (by scalar_tac), ← i1_post, ← i3_post]
           assumption)
    case isFalse => exact ⟨hle, hinv⟩
  · exact ⟨hl0, h0⟩))
set_option hygiene false in
local notation "T10!" => (by
  (
  exact Submission.Z466.EB.mlen_loop_spec input a b cap 0#usize ha hb (by scalar_tac)
    (LZ77.Matches.zero input a.val b.val)))
set_option hygiene false in
local notation "T14!" q0__:max => (by
  rw [q0__]
  try simp only [ite_ok]
  step*
  all_goals (repeat (split <;> step*))
  all_goals scalar_tac)

set_option hygiene false in
local notation "T15!" q0__:max => (by
  rw [q0__]
  simp only [lift, ite_ok, alloc.vec.Vec.deref_mut, bind_tc_ok]
  step*
  all_goals (repeat (split <;> step*))
  all_goals scalar_tac)
set_option hygiene false in
local notation "T16!" q0__:max q1__:max => (by
  rw [q0__]
  apply SDN!
    (measure := fun qq9 => 288 - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨cnt1, i1⟩ _
    simp only [q1__, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial)
set_option hygiene false in
local notation "T17!" q0__:max q1__:max => (by
  rw [q0__]
  apply SDN!
    (measure := fun qq9 => 318 - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨sc1, s1⟩ _
    simp only [q1__, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial)
set_option hygiene false in
local notation "T19!" q0__:max q1__:max => (by
  rw [q0__]
  apply SDN!
    (measure := fun qq9 => 259 - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨tbl1, len1⟩ _
    simp only [q1__, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial)
end EL
end EC
namespace ED
open Aeneas Aeneas.Std Result ControlFlow
set_option maxRecDepth 8192
set_option maxHeartbeats 1000000
set_option linter.unusedTactic false
set_option linter.unreachableTactic false
set_option linter.unusedSimpArgs false
set_option linter.unusedVariables false
open LZ77 (toks bytes bytes_getElem! Matches emit_lit emit_match)
@[local scalar_tac x &&& y]
theorem u793 (x y:Nat):x &&& y ≤ y := Nat.and_le_right
@[local scalar_tac x >>> y]
theorem u794 (x y:Nat):x >>> y ≤ x := Nat.shiftRight_le x y
@[local scalar_tac System.Platform.numBits]
theorem u795:32 ≤ System.Platform.numBits := EA.u4
@[local scalar_tac core.num.U32.leading_zeros x]
theorem u796 (x:W) :
    (core.num.U32.leading_zeros x).val ≤ 32 ∧
      (x.val = 0 ∨ (core.num.U32.leading_zeros x).val ≤ 31) := Y122U7!
@[local scalar_tac core.num.U64.leading_zeros x]
theorem u797 (x:Std.U64):(core.num.U64.leading_zeros x).val ≤ 64 := EA.u10 x

@[local scalar_tac core.num.Usize.saturating_add x y]
theorem u798 (x y:R) :
    (core.num.Usize.saturating_add x y).val = min Std.Usize.max (x.val + y.val) := EA.u299 x y

@[local step]
theorem u799 (cost:U) (lc) (i hi:R) (base best l)
    (hhi:hi.val < 512) (hc:i.val + hi.val < cost.length) :
    slot.Z480_loop cost lc i hi base l best ⦃ Y112P0! ⦄ := Y122U8! slot.Z480_loop slot.Z480_loop.body
@[local step]
theorem u800 (cost:U) (lc i lo hi base width) :
    slot.Z480 cost lc i lo hi base width ⦃ Y112P0! ⦄ := Y122U1! slot.Z480
@[local step]
theorem u801 (pe:R) (cost) (cl z:R) (hpe:pe.val ≤ 2 ^ 31) (hcl:cl.val = cost.length) :
    slot.Z443_loop0 pe cost cl z ⦃ fun r => r.length = cost.length ⦄ := Y122U9! slot.Z443_loop0 slot.Z443_loop0.body
@[local step]
theorem u802 (tail:R) (mb lc dc) (cost:alloc.vec.Vec W) (cl i:R) (bias best bd) (prev pd:R) (j top:R)
    (hcl:cl.val = cost.length) (hi:i.val ≤ 2 ^ 31) (htop:top.val ≤ mb.length)
    (hprev:prev.val ≤ i.val + 258) (hpv:i.val ≤ prev.val) (hpd:pd.val ≤ 32768) (hbd:bd.val ≤ 32767) :
    slot.Z443_loop1_loop0 mb lc dc cost tail cl i bias best bd prev pd j top ⦃ Y112P7! ⦄ := Y122U10! slot.Z443_loop1_loop0 slot.Z443_loop1_loop0.body
@[local step]
theorem u803 (tail:R) (s:I) (mp mb:alloc.vec.Vec W) (p0 lit lc dc) (cost ch:alloc.vec.Vec W)
    (cl i e xl xd:R)
    (hcl:cl.val = cost.length) (hi:i.val < cl.val) (hmp:i.val < mp.length) (hs:i.val ≤ s.length)
    (hch:i.val ≤ ch.length) (hi31:i.val ≤ 2 ^ 31) (hxl:xl.val ≤ 258) (hxd:xd.val ≤ 32768) :
    slot.Z443_loop1 s mp mb p0 lit lc dc cost ch tail cl i e xl xd ⦃ Y112P0! ⦄ := Y122U11! slot.Z443_loop1 slot.Z443_loop1.body
@[local step]
theorem u804 (tail:R) (s:I) (mp mb) (p0 pe:R) (lit lc dc) (cost ch)
    (hpe:pe.val ≤ 2 ^ 31) :
    slot.Z443 s mp mb p0 pe lit lc dc cost ch tail ⦃ Y112P0! ⦄ := Y122U1! slot.Z443
@[local step]
theorem u805 (lf zf b) :
    slot.Z445_loop0_loop0 lf zf b ⦃ Y112P0! ⦄ := Y122U12! slot.Z445_loop0_loop0 slot.Z445_loop0_loop0.body
@[local step]
theorem u806 (df zd b) :
    slot.Z445_loop0_loop1 df zd b ⦃ Y112P0! ⦄ := Y122U13! slot.Z445_loop0_loop1 slot.Z445_loop0_loop1.body
@[local step]
theorem u807 (tail:R) (s:I) (mp mb) (pe:R) (lit lc dc cost ch lf df zf zd) (sb st a:R)
    (hpe:pe.val ≤ 2 ^ 30) (hps:pe.val ≤ s.length) (hsb:sb.val ≤ a.val) (hst:st.val ≤ a.val)
    (ha:a.val ≤ pe.val + slot.Z8.val * slot.Z3.val) :
    slot.Z445_loop0 s mp mb pe lit lc dc cost ch lf df tail zf zd sb st a ⦃ Y112P0! ⦄ := Y122U14! slot.Z445_loop0 slot.Z8.val slot.Z3.val slot.Z445_loop0.body
@[local step]
theorem u808 (lf zf b) :
    slot.Z445_loop1 lf zf b ⦃ Y112P0! ⦄ := Y122U15! slot.Z445_loop1 slot.Z445_loop1.body
@[local step]
theorem u809 (df zd b) :
    slot.Z445_loop2 df zd b ⦃ Y112P0! ⦄ := Y122U16! slot.Z445_loop2 slot.Z445_loop2.body
@[local step]
theorem u810 (tail:R) (s:I) (mp mb) (p0 pe:R) (lit lc dc cost ch lf df)
    (hpe:pe.val ≤ 2 ^ 30) (hps:pe.val ≤ s.length) (hp0:p0.val ≤ pe.val) :
    slot.Z445 s mp mb p0 pe lit lc dc cost ch lf df tail ⦃ Y112P0! ⦄ := by
  have hseg := Submission.Z466.EA.A_SEG_bounds
  rw [slot.Z445]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

@[local step]
theorem u811 (n:R) (cost) (i:R) (hn:n.val < 67108864) (hc:cost.length = i.val) :
    slot.Z444_loop0 n cost i ⦃ Y112P0! ⦄ := Y122U17! slot.Z444_loop0 slot.Z444_loop0.body

set_option aeneas.step.nla true in
@[local step]
theorem u812 (tail final_tail:R) (input:I) (ch) (n:R) (mp mb cost lit lc dc lf df bl bd sl sd) (rot p0 need passes sampled pe k p1 t:R)
    (hn:n.val = input.length) (hn26:n.val < 67108864) (hp0:p0.val < n.val) (hpe:p0.val ≤ pe.val ∧ pe.val ≤ n.val)
    (hpe':pe.val = n.val ∨ p0.val + slot.Z1.val ≤ pe.val)
    (hneed:need.val ≤ 65536) (ht:t.val ≤ need.val) (hp1:p0.val ≤ p1.val ∧ p1.val ≤ p0.val + 511 * t.val) :
    slot.Z444_loop1_loop0 input ch tail final_tail n mp mb cost lit lc dc lf df bl bd sl sd rot p0 need passes sampled pe k p1 t ⦃ Y112P4! ⦄ := Y122U18! slot.Z444_loop1_loop0 slot.Z1.val slot.Z444_loop1_loop0.body
@[local step]
theorem u813 (tail final_tail:R) (input:I) (ch first_passes fspass passes_k) (n:R) (mp mb cost lit lc dc lf df bl bd sl sd zl zd) (rot spn p0 used bpt:R)
    (hn:n.val = input.length) (hn26:n.val < 67108864) (hused:used.val < slot.Z45.val) (hbpt:256 ≤ bpt.val ∧ bpt.val ≤ 65536) :
    slot.Z444_loop1 input ch first_passes fspass passes_k tail final_tail n mp mb cost lit lc dc lf df bl bd sl sd zl zd rot spn p0 used bpt ⦃ Y112P0! ⦄ := Y122U19! slot.Z444_loop1 slot.Z45.val slot.Z444_loop1.body slot.Z1.val
@[local step]
theorem u814 (tail final_tail:R) (input:I) (ch) (depth skip first_passes fspass passes_k spass:R)
    (hn:input.length < 67108864) (h1:depth.val ≤ 65536) (h2:skip.val ≤ 65536) (h2':3 ≤ skip.val)
    (h3:first_passes.val ≤ 65536) (h4:fspass.val ≤ 65536) (h5:passes_k.val ≤ 65536) (h6:spass.val ≤ 65536) :
    slot.Z444 input ch depth skip first_passes fspass passes_k spass tail final_tail ⦃ Y112P0! ⦄ := by
  have hbt := Submission.Z466.EA.A_BLOCK_bounds
  rw [slot.Z444]
  step*
  all_goals rfl

attribute [local step] EB.u446
attribute [local step] EB.u511
def u815 (mf:slot.Z145) (i:Nat):Prop :=
  EA.u13 mf.head.val i ∧ EA.u13 mf.head3.val i ∧ EA.u13 mf.tree.val i ∧ EA.u13 mf.pn.val i ∧
    mf.hl.val ≤ 2 ^ 30
theorem u816 (w:Std.Array Std.U64 32768#usize) (pf:Std.Array W 32#usize) (plen hn:R) :
    u815
      { head := Std.Array.repeat 65536#usize 0#u32, head3 := Std.Array.repeat 16384#usize 0#u32,
        tree := Std.Array.repeat 65536#usize 0#u32, w := w, pn := Std.Array.repeat 32#usize 0#u32, pf := pf,
        plen := plen, hn := hn, hl := 0#usize } (0#usize).val := Y122U25!
def u817 (b i:Nat)
    (r:ControlFlow (slot.Z145 × Std.Array W 32#usize × alloc.vec.Vec W × Std.U64 × R ×
      R × R) (slot.Z145 × Std.Array W 32#usize × alloc.vec.Vec W × Std.U64 ×
      R × R)):Prop :=
  match r with
  | .done y => u815 y.1 b ∧ y.2.2.2.2.2.val ≤ 33 * b ∧ y.2.2.2.2.2.val ≤ y.2.2.1.length
  | .cont x' => x'.2.2.2.2.2.2.val ≤ b ∧ x'.2.2.2.2.2.1.val ≤ 33 * x'.2.2.2.2.2.2.val ∧
      x'.2.2.2.2.2.1.val ≤ x'.2.2.1.length ∧ u815 x'.1 x'.2.2.2.2.2.2.val ∧
      b - x'.2.2.2.2.2.2.val < b - i

@[local step]
theorem u818 (s:I) (n:R) (head) (r4 r6 probes p:R)
    (hn:n.val = s.length) (hn26:n.val < 67108864) (hr4:r4.val ≤ probes.val) (hr6:r6.val ≤ probes.val)
    (hpr:probes.val ≤ p.val) (hp:p.val ≤ n.val + slot.Z4.val) :
    slot.Z471_loop s n head r4 r6 probes p ⦃ fun r => r.1.val ≤ 65536 ∧ r.2.val ≤ 65536 ⦄ := by
  have f1 := EA.u387
  have f2 := EA.u388
  have f3 := Submission.Z466.EA.dp_WN_val
  rw [slot.Z471_loop]
  apply SDN!
    (measure := fun (_, _, _, _, p') => n.val + slot.Z4.val - p'.val)
    (inv := fun (_, r4', r6', pr', p') => r4'.val ≤ pr'.val ∧ r6'.val ≤ pr'.val ∧ pr'.val ≤ p'.val ∧
      p'.val ≤ n.val + slot.Z4.val)
  · rintro ⟨h', r4', r6', pr', p'⟩ ⟨i1, i2, i3, i4⟩
    simp only [slot.Z471_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact ⟨hr4, hr6, hpr, hp⟩
@[local step]
theorem u819 (s:I) (hn26:s.length < 67108864) :
    slot.Z471 s ⦃ fun r => r.1.val ≤ 65536 ∧ r.2.val ≤ 65536 ⦄ := Y122U1! slot.Z471
@[local step]
theorem u820 (plan e_nd p) :
    slot.Z448_loop plan e_nd p ⦃ fun r => r.length = plan.length ⦄ := by
  rw [slot.Z448_loop]
  apply SDN!
    (measure := fun (_, p') => e_nd.val - p'.val)
    (inv := fun (plan', _) => plan'.length = plan.length)
  · rintro ⟨plan', p'⟩ hinv
    simp only [slot.Z448_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · rfl
@[local step]
theorem u821 (plan p0 e_nd) :
    slot.Z448 plan p0 e_nd ⦃ fun r => r.length = plan.length ⦄ := Y122U1! slot.Z448
@[local step]
theorem u822 (d):slot.Z450 d ⦃ fun r => r.val < 256 ⦄ := Y122U1! slot.Z450
@[local step]
theorem u823 (len):slot.Z462 len ⦃ fun r => r.val < 256 ⦄ := Y122U1! slot.Z462
@[local step]
theorem u824 (lf df) :
    slot.Z465_loop0 lf df 0#usize ⦃ fun r => EA.u13 r.1.val 0 ∧ EA.u13 r.2.val 0 ⦄ := by
  rw [slot.Z465_loop0]
  apply SDN!
    (measure := fun (_, _, k) => 288 - k.val)
    (inv := fun (lf', df', k) => k.val ≤ 288 ∧
      (∀ j (hj:j < k.val) (hl:j < lf'.val.length), (lf'.val[j]).val = 0) ∧
      (∀ j (hj:j < k.val) (hl:j < df'.val.length), (df'.val[j]).val = 0))
  · rintro ⟨lf', df', k⟩ ⟨hk, hz1, hz2⟩
    simp only [slot.Z465_loop0.body]
    step*
    · refine ⟨by scalar_tac, ?_, ?_, by scalar_tac⟩
      · intro j hj hl
        subst a_post
        simp only [Array.set_val_eq, List.getElem_set]
        split
        · rfl
        · exact hz1 j (by scalar_tac) (by simpa using hl)
      · intro j hj hl
        subst a1_post
        simp only [Array.set_val_eq, List.getElem_set]
        split
        · rfl
        · exact hz2 j (by scalar_tac) (by simpa using hl)
    · have:k.val = 288 := by scalar_tac
      refine ⟨?_, ?_⟩
      · intro j hl
        have hl':j < 288 := by simpa using hl
        rw [hz1 j (by omega) hl]
      · intro j hl
        have hl':j < 288 := by simpa using hl
        rw [hz2 j (by omega) hl]
  · exact ⟨by simp, fun j hj => by simp at hj, fun j hj => by simp at hj⟩
@[local step]
theorem u825 (s:I) (choice) (lf df) (n p t:R)
    (hn:n.val = s.length) (hlf:EA.u13 lf.val t.val) (hdf:EA.u13 df.val t.val) :
    slot.Z465_loop1 s choice lf df n p t ⦃ fun r => p.val ≤ r.2.2.val ∧ (p.val ≤ n.val → r.2.2.val ≤ n.val) ⦄ := by
  have hB := EA.u374
  rw [slot.Z465_loop1]
  apply SDN!
    (measure := fun (_, _, _, t') => slot.Z45.val - t'.val)
    (inv := fun (lf', df', p', t') => EA.u13 lf'.val t'.val ∧ EA.u13 df'.val t'.val ∧ p.val ≤ p'.val ∧
      (p.val ≤ n.val → p'.val ≤ n.val))
  · rintro ⟨lf', df', p', t'⟩ ⟨hlf', hdf', hp1, hp2⟩
    simp only [slot.Z465_loop1.body]
    step*
    apply WP.spec_bind (Pₘ := fun (x:Std.Array W 288#usize × Std.Array W 288#usize × R) =>
      EA.u13 x.1.val (t'.val + 1) ∧ EA.u13 x.2.1.val (t'.val + 1) ∧ p'.val < x.2.2.val ∧ x.2.2.val ≤ n.val)
    · split
      · step*
        ·
          have h6 := EA.u14 hlf' i5.val (by scalar_tac)
          have h12 := EA.u14 hdf' i11.val (by scalar_tac)
          refine ⟨?_, ?_, by scalar_tac, by scalar_tac⟩
          · rw [a_post, Array.set_val_eq];exact EA.u26 hlf' _ _ (by scalar_tac)
          · rw [a1_post, Array.set_val_eq];exact EA.u26 hdf' _ _ (by scalar_tac)
        ·
          have := EA.u14 hlf' i4.val (by scalar_tac)
          scalar_tac
        ·
          have := EA.u14 hlf' i4.val (by scalar_tac)
          refine ⟨?_, EA.u23 hdf' (by omega), by scalar_tac, by scalar_tac⟩
          rw [a_post, Array.set_val_eq];exact EA.u26 hlf' _ _ (by scalar_tac)
      ·
        step*
        · have := EA.u14 hlf' i3.val (by scalar_tac)
          scalar_tac
        · have := EA.u14 hlf' i3.val (by scalar_tac)
          refine ⟨?_, EA.u23 hdf' (by omega), by scalar_tac, by scalar_tac⟩
          rw [a_post, Array.set_val_eq];exact EA.u26 hlf' _ _ (by scalar_tac)
    · rintro ⟨lf1, df1, p1⟩ ⟨h1, h2, h3, h4⟩
      step*
  · exact ⟨hlf, hdf, le_refl _, fun h => h⟩
@[local step]
theorem u826 (s choice p0 lf df) :
    slot.Z465 s choice p0 lf df ⦃ fun r => p0.val ≤ r.1.val ∧ (p0.val ≤ s.length → r.1.val ≤ s.length) ⦄ := by
  rw [slot.Z465]
  step*
@[local step]
theorem u827 (lf) (bits:Std.U64) (i:R) (hi:i.val ≤ 288)
    (hb:bits.val ≤ 3 + i.val * 2 ^ 40) :
    slot.Z456_loop0 lf bits i ⦃ fun r => r.val ≤ 3 + 288 * 2 ^ 40 ⦄ := by
  rw [slot.Z456_loop0]
  apply SDN!
    (measure := fun (_, i') => 288 - i'.val)
    (inv := fun (bits', i') => i'.val ≤ 288 ∧ bits'.val ≤ 3 + i'.val * 2 ^ 40)
  · rintro ⟨bits', i'⟩ ⟨hi', hb'⟩
    simp only [slot.Z456_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact ⟨hi, hb⟩
@[local step]
theorem u828 (df) (bits:Std.U64) (d:R) (hd:d.val ≤ 30)
    (hb:bits.val ≤ 3 + 288 * 2 ^ 40 + d.val * 2 ^ 40) :
    slot.Z456_loop1 df bits d ⦃ fun r => r.val ≤ 3 + 318 * 2 ^ 40 ⦄ := by
  rw [slot.Z456_loop1]
  apply SDN!
    (measure := fun (_, d') => 30 - d'.val)
    (inv := fun (bits', d') => d'.val ≤ 30 ∧ bits'.val ≤ 3 + 288 * 2 ^ 40 + d'.val * 2 ^ 40)
  · rintro ⟨bits', d'⟩ ⟨hd', hb'⟩
    simp only [slot.Z456_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact ⟨hd, hb⟩
@[local step]
theorem u829 (lf df) :
    slot.Z456 lf df ⦃ Y112P0! ⦄ := Y122U1! slot.Z456
@[local step]
theorem u830 (clf) (r:R) (extra:Std.U64) (fuel:R)
    (hx:extra.val + 7 * fuel.val ≤ 2 ^ 40) :
    slot.Z473_loop0 clf r extra fuel ⦃ fun res => res.2.2.val ≤ extra.val + 7 * fuel.val ⦄ := by
  rw [slot.Z473_loop0]
  apply SDN!
    (measure := fun (_, _, _, f) => f.val)
    (inv := fun (_, _, e, f) => e.val + 7 * f.val ≤ extra.val + 7 * fuel.val)
  · rintro ⟨clf', r', e', f'⟩ hinv
    simp only [slot.Z473_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · simp
@[local step]
theorem u831 (clf) (r:R) (extra:Std.U64) (fuel:R)
    (hx:extra.val + 2 * fuel.val ≤ 2 ^ 40) :
    slot.Z473_loop1 clf r extra fuel ⦃ fun res => res.2.2.val ≤ extra.val + 2 * fuel.val ⦄ := by
  rw [slot.Z473_loop1]
  apply SDN!
    (measure := fun (_, _, _, f) => f.val)
    (inv := fun (_, _, e, f) => e.val + 2 * f.val ≤ extra.val + 2 * fuel.val)
  · rintro ⟨clf', r', e', f'⟩ hinv
    simp only [slot.Z473_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · simp
@[local step]
theorem u832 (clf v) (r0:R) (hr0:1 ≤ r0.val ∧ r0.val ≤ 512) :
    slot.Z473 clf v r0 ⦃ fun r => r.1.val ≤ 7 * (r0.val + 1) ⦄ := Y122U1! slot.Z473
@[local step]
theorem u833 (sw) (k:R) (shift:W) (hshift:shift.val < 32) :
    slot.Z470_loop0 sw k shift (Array.repeat 257#usize 0#usize) 0#usize ⦃ fun r => EA.u13 r.val 288 ⦄ := by
  rw [slot.Z470_loop0]
  apply SDN!
    (measure := fun (_, i') => 288 - i'.val)
    (inv := fun (cnt', i') => i'.val ≤ 288 ∧ EA.u13 cnt'.val i'.val)
  · rintro ⟨cnt', i'⟩ ⟨hi', hc'⟩
    simp only [slot.Z470_loop0.body]
    step*
    all_goals first
      | scalar_tac
      | exact EA.u23 hc' (by scalar_tac)
      | (refine ⟨by scalar_tac, ?_, by scalar_tac⟩
         rw [a_post, Array.set_val_eq, show i9.val = i'.val + 1 by scalar_tac]
         apply EA.u26 hc'
         have := EA.u14 hc' i5.val (by scalar_tac)
         scalar_tac)
  · exact ⟨by simp, EA.u46 _ _ _ (by simp)⟩
@[local step]
theorem u834 (cnt) (hcnt:EA.u13 cnt.val 288) :
    slot.Z470_loop1 cnt 1#usize ⦃ fun r => EA.u13 r.val 74016 ⦄ := by
  rw [slot.Z470_loop1]
  apply SDN!
    (measure := fun (_, c') => 257 - c'.val)
    (inv := fun (cnt', c') => 1 ≤ c'.val ∧ c'.val ≤ 257 ∧
      (∀ j (hj:j < cnt'.val.length), j < c'.val → (cnt'.val[j]).val ≤ 288 * c'.val) ∧
      (∀ j (hj:j < cnt'.val.length), c'.val ≤ j → (cnt'.val[j]).val ≤ 288))
  · rintro ⟨cnt', c'⟩ ⟨hc1, hc2, hlo, hhi⟩
    simp only [slot.Z470_loop1.body]
    step*
    · have hi:i.val ≤ 288 := by rw [i_post];exact hhi _ _ (le_refl _)
      have hi2:i2.val ≤ 288 * c'.val := by rw [i2_post];exact hlo _ _ (by scalar_tac)
      refine ⟨by scalar_tac, by scalar_tac, ?_, ?_, by scalar_tac⟩
      · intro j hj hjc
        subst a_post
        simp only [Array.set_val_eq, List.getElem_set]
        split
        · scalar_tac
        · have hj':j < (↑cnt':List R).length := by simpa using hj
          have := hlo j hj' (by scalar_tac)
          scalar_tac
      · intro j hj hjc
        subst a_post
        simp only [Array.set_val_eq, List.getElem_set]
        split
        · scalar_tac
        · exact hhi j (by simpa using hj) (by scalar_tac)
    · intro j hj
      have hj2:j < 257 := by simpa using hj
      have := hlo j hj (by scalar_tac)
      scalar_tac
  · refine ⟨by simp, by simp, ?_, ?_⟩
    · intro j hj hj1
      have := hcnt j hj
      simp at hj1 ⊢
      omega
    · intro j hj _
      exact hcnt j hj
@[local step]
theorem u835 (sw ss dw ds) (k:R) (shift:W) (cnt) (hshift:shift.val < 32)
    (hcnt:EA.u13 cnt.val 74016) :
    slot.Z470_loop2 sw ss dw ds k shift cnt 0#usize ⦃ Y112P0! ⦄ := by
  rw [slot.Z470_loop2]
  apply SDN!
    (measure := fun (_, _, _, j') => 288 - j'.val)
    (inv := fun (_, _, cnt', j') => j'.val ≤ 288 ∧ EA.u13 cnt'.val (74016 + j'.val))
  · rintro ⟨dw', ds', cnt', j'⟩ ⟨hj', hc'⟩
    simp only [slot.Z470_loop2.body]
    step*
    all_goals first
      | scalar_tac
      | (have := EA.u14 hc' i3.val (by scalar_tac)
         scalar_tac)
      | (refine ⟨by scalar_tac, ?_, by scalar_tac⟩
         rw [a2_post, Array.set_val_eq, show j1.val = j'.val + 1 by scalar_tac, ← Nat.add_assoc]
         apply EA.u26 hc'
         have := EA.u14 hc' i3.val (by scalar_tac)
         scalar_tac)
  · exact ⟨by simp, by simpa using hcnt⟩
@[local step]
theorem u836 (sw ss dw ds) (k:R) (shift:W) (hshift:shift.val < 32) :
    slot.Z470 sw ss dw ds k shift ⦃ Y112P0! ⦄ := by
  rw [slot.Z470]
  step*
@[local step]
theorem u837 (freq m lens aw asy) (k i:R) (hk:k.val ≤ i.val) (hi:i.val ≤ 288) :
    slot.Z459_loop0 freq m lens aw asy k i ⦃ fun r => r.2.2.2.val ≤ 288 ⦄ := by
  rw [slot.Z459_loop0]
  apply SDN!
    (measure := fun (_, _, _, _, i') => 288 - i'.val)
    (inv := fun (_, _, _, k', i') => k'.val ≤ i'.val ∧ i'.val ≤ 288)
  · rintro ⟨lens', aw', asy', k', i'⟩ ⟨hk', hi'⟩
    simp only [slot.Z459_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact ⟨hk, hi⟩
@[local step]
theorem u838 (aw) (k:R) (iw ipar lpar) (li ii ni:R) (w2) (t:R)
    (hii:ii.val ≤ 2 ^ 20) :
    slot.Z459_loop1_loop0 aw k iw ipar lpar li ii ni w2 t ⦃ fun r => r.2.2.2.1.val ≤ ii.val + 2 ⦄ := by
  rw [slot.Z459_loop1_loop0]
  apply SDN!
    (measure := fun (_, _, _, _, _, t') => 2 - t'.val)
    (inv := fun (_, _, _, ii', _, t') => ii'.val + t.val ≤ ii.val + t'.val ∧ t.val ≤ t'.val ∧
      (t.val ≤ 2 → t'.val ≤ 2) ∧ (2 < t.val → t'.val = t.val))
  · rintro ⟨ipar', lpar', li', ii', w2', t'⟩ ⟨h1, h2, h3, h4⟩
    simp only [slot.Z459_loop1_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · simp
@[local step]
theorem u839 (aw) (k:R) (iw ipar lpar) (li ii ni:R) (hii:ii.val ≤ 2 * ni.val)
    (hni:ni.val ≤ 287) (hk:k.val ≤ 288) :
    slot.Z459_loop1 aw k iw ipar lpar li ii ni ⦃ fun r => ni.val ≤ r.2.2.val ∧ (ni.val + 1 < k.val → ni.val < r.2.2.val) ⦄ := by
  rw [slot.Z459_loop1]
  apply SDN!
    (measure := fun (_, _, _, _, _, ni') => 287 - ni'.val)
    (inv := fun (_, _, _, _, ii', ni') => ni.val ≤ ni'.val ∧ ni'.val ≤ 287 ∧ ii'.val ≤ 2 * ni'.val)
  · rintro ⟨iw', ipar', lpar', li', ii', ni'⟩ ⟨h1, h2, h3⟩
    simp only [slot.Z459_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact ⟨le_refl _, hni, hii⟩
@[local step]
theorem u840 (ipar idep j) :
    slot.Z459_loop2 ipar idep j ⦃ Y112P0! ⦄ := by
  rw [slot.Z459_loop2]
  apply SDN!
    (measure := fun (idep_, j_) => j_.val)
    (inv := fun _ => True)
  · rintro ⟨idep_, j_⟩ _
    simp only [slot.Z459_loop2.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem u841 (lens asy k lpar idep x) :
    slot.Z459_loop3 lens asy k lpar idep x ⦃ Y112P0! ⦄ := by
  rw [slot.Z459_loop3]
  apply SDN!
    (measure := fun (lens_, x_) => k.val - x_.val)
    (inv := fun _ => True)
  · rintro ⟨lens_, x_⟩ _
    simp only [slot.Z459_loop3.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem u842 (freq m lens):slot.Z459 freq m lens ⦃ Y112P0! ⦄ := Y122U1! slot.Z459
@[local step]
theorem u843 (lf ll) (body:Std.U64) (hlit i:R) (hi:i.val ≤ 286)
    (hb:body.val ≤ i.val * 2 ^ 41) :
    slot.Z451_loop0 lf ll body hlit i ⦃ fun r => r.1.val ≤ 286 * 2 ^ 41 ∧ r.2.val ≤ max hlit.val 286 ⦄ := by
  rw [slot.Z451_loop0]
  apply SDN!
    (measure := fun (_, _, i') => 286 - i'.val)
    (inv := fun (b', h', i') => i'.val ≤ 286 ∧ b'.val ≤ i'.val * 2 ^ 41 ∧ h'.val ≤ max hlit.val 286)
  · rintro ⟨b', h', i'⟩ ⟨h1, h2, h3⟩
    simp only [slot.Z451_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact ⟨hi, hb, by scalar_tac⟩
@[local step]
theorem u844 (df dl) (body:Std.U64) (hdist any:R) (d:R) (hd:d.val ≤ 30)
    (hb:body.val ≤ 286 * 2 ^ 41 + d.val * 2 ^ 41) :
    slot.Z451_loop1 df dl body hdist any d ⦃ fun r => r.1.val ≤ 316 * 2 ^ 41 ∧ r.2.1.val ≤ max hdist.val 30 ⦄ := by
  rw [slot.Z451_loop1]
  apply SDN!
    (measure := fun (_, _, _, d') => 30 - d'.val)
    (inv := fun (b', h', _, d') => d'.val ≤ 30 ∧ b'.val ≤ 286 * 2 ^ 41 + d'.val * 2 ^ 41 ∧ h'.val ≤ max hdist.val 30)
  · rintro ⟨b', h', a', d'⟩ ⟨h1, h2, h3⟩
    simp only [slot.Z451_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact ⟨hd, hb, by scalar_tac⟩
@[local step]
theorem u845 (ll dl hlit total seq i2) :
    slot.Z451_loop2 ll dl hlit total seq i2 ⦃ Y112P0! ⦄ := by
  rw [slot.Z451_loop2]
  apply SDN!
    (measure := fun (seq_, i2_) => total.val - i2_.val)
    (inv := fun _ => True)
  · rintro ⟨seq_, i2_⟩ _
    simp only [slot.Z451_loop2.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem u846 (total seq) (j r:R) (v) (hj:j.val ≤ 512) (hr:r.val ≤ 512) :
    slot.Z451_loop3_loop0 total seq j v r ⦃ fun res => r.val ≤ res.val ∧ res.val ≤ max r.val 512 ∧
      (j.val + r.val ≤ 512 → j.val + res.val ≤ 512) ⦄ := by
  rw [slot.Z451_loop3_loop0]
  apply SDN!
    (measure := fun r' => 512 - r'.val)
    (inv := fun r' => r.val ≤ r'.val ∧ r'.val ≤ max r.val 512 ∧ (j.val + r.val ≤ 512 → j.val + r'.val ≤ 512))
  · rintro r' ⟨h1, h2, h3⟩
    simp only [slot.Z451_loop3_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact ⟨le_refl _, by scalar_tac, fun h => h⟩
@[local step]
theorem u847 (clf) (extra:Std.U64) (total seq) (j:R) (hj:j.val ≤ 512)
    (hx:extra.val ≤ j.val * 4096) :
    slot.Z451_loop3 clf extra total seq j ⦃ fun r => r.2.val ≤ 513 * 4096 ⦄ := by
  rw [slot.Z451_loop3]
  apply SDN!
    (measure := fun (_, _, j') => 512 - j'.val)
    (inv := fun (_, e', j') => j'.val ≤ 512 ∧ e'.val ≤ j'.val * 4096)
  · rintro ⟨clf', e', j'⟩ ⟨h1, h2⟩
    simp only [slot.Z451_loop3.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact ⟨hj, hx⟩
@[local step]
theorem u848 (cl hclen) :
    slot.Z451_loop4 cl hclen ⦃ fun r => r.val ≤ hclen.val ⦄ := by
  rw [slot.Z451_loop4]
  apply SDN!
    (measure := fun h' => h'.val)
    (inv := fun h' => h'.val ≤ hclen.val)
  · rintro h' h1
    simp only [slot.Z451_loop4.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact le_refl _
@[local step]
theorem u849 (clf cl) (hdr:Std.U64) (c:R) (hc:c.val ≤ 19)
    (hh:hdr.val ≤ 2 ^ 40 + c.val * 2 ^ 35) :
    slot.Z451_loop5 clf cl hdr c ⦃ fun r => r.val ≤ 2 ^ 40 + 19 * 2 ^ 35 ⦄ := by
  rw [slot.Z451_loop5]
  apply SDN!
    (measure := fun (_, c') => 19 - c'.val)
    (inv := fun (h', c') => c'.val ≤ 19 ∧ h'.val ≤ 2 ^ 40 + c'.val * 2 ^ 35)
  · rintro ⟨h', c'⟩ ⟨h1, h2⟩
    simp only [slot.Z451_loop5.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact ⟨hc, hh⟩
@[local step]
theorem u850 (lf df):slot.Z451 lf df ⦃ Y112P0! ⦄ := Y122U1! slot.Z451
@[local step]
theorem u851 (s:I) (ec q:R)
    (hec:ec.val ≤ s.length) (hn26:s.length < 67108864) :
    slot.Z466_loop0_loop0 s ec (Array.repeat 288#usize 0#u32) q ⦃ Y112P0! ⦄ := by
  rw [slot.Z466_loop0_loop0]
  apply SDN!
    (measure := fun (_, q') => ec.val - q'.val)
    (inv := fun (lb', q') => EA.u13 lb'.val q'.val)
  · rintro ⟨lb', q'⟩ hlb'
    simp only [slot.Z466_loop0_loop0.body]
    step*
    all_goals first
      | (have := EA.u14 hlb' i1.val (by scalar_tac)
         scalar_tac)
      | (refine ⟨?_, by scalar_tac⟩
         rw [a_post, Array.set_val_eq, show q1.val = q'.val + 1 by scalar_tac]
         apply EA.u26 hlb'
         have := EA.u14 hlb' i1.val (by scalar_tac)
         scalar_tac)
  · exact EA.u46 _ _ _ (by simp)
@[local step]
theorem u852 (s:I) (plan) (n:R) (lf df p fuel) (hn:n.val = s.length)
    (hn26:n.val < 67108864) :
    slot.Z466_loop0 s plan n lf df p fuel ⦃ Y112P0! ⦄ := by
  have hB := EA.u374
  rw [slot.Z466_loop0]
  apply SDN!
    (measure := fun (_, _, _, _, f) => f.val)
    (inv := fun _ => True)
  · rintro ⟨plan', lf', df', p', f'⟩ _
    simp only [slot.Z466_loop0.body]
    step*
    apply WP.spec_bind (Pₘ := fun _ => True)
    · split <;> step*
    rintro ca _
    step*
    apply WP.spec_bind (Pₘ := fun (x:R) => p'.val ≤ x.val ∧ x.val ≤ n.val)
    · split <;> step*
      all_goals scalar_tac
    rintro eb ⟨heb1, heb2⟩
    apply WP.spec_bind (Pₘ := fun (x:R) => p'.val ≤ x.val ∧ x.val ≤ n.val)
    · split <;> step*
      all_goals scalar_tac
    rintro ec ⟨hec1, hec2⟩
    step*
    apply WP.spec_bind (Pₘ := fun _ => True)
    · split <;> step*
    rintro cb _
    apply WP.spec_bind (Pₘ := fun _ => True)
    · split <;> step*
    rintro cb1 _
    step*
    all_goals scalar_tac
  · trivial
@[local step]
theorem u853 (s:I) (plan) (hn26:s.length < 67108864) :
    slot.Z466 s plan ⦃ Y112P0! ⦄ := Y122U1! slot.Z466
@[local step]
theorem u854 (s:I) (n allow:R) (bad i:R) (hn:n.val ≤ s.length)
    (hbad:bad.val ≤ i.val) :
    slot.Z460_loop s n allow bad i ⦃ Y112P0! ⦄ := by
  rw [slot.Z460_loop]
  apply SDN!
    (measure := fun (_, i') => n.val - i'.val)
    (inv := fun (bad', i') => bad'.val ≤ i'.val)
  · rintro ⟨bad', i'⟩ hb'
    simp only [slot.Z460_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact hbad
@[local step]
theorem u855 (s) :
    slot.Z460 s ⦃ Y112P0! ⦄ := Y122U1! slot.Z460
@[local step]
theorem u856 (lf df ll dl) (est:Std.U64) (q:R) (hq:q.val ≤ 288)
    (he:est.val ≤ 70 + q.val * 2 ^ 42) :
    slot.Z468_loop0 lf df ll dl est q ⦃ fun r => r.val ≤ 70 + 288 * 2 ^ 42 ⦄ := by
  rw [slot.Z468_loop0]
  apply SDN!
    (measure := fun (_, q') => 288 - q'.val)
    (inv := fun (e', q') => q'.val ≤ 288 ∧ e'.val ≤ 70 + q'.val * 2 ^ 42)
  · rintro ⟨e', q'⟩ ⟨h1, h2⟩
    simp only [slot.Z468_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact ⟨hq, he⟩
@[local step]
theorem u857 (models) (tokpen:W) (ll) (i:R) (htok:tokpen.val ≤ 65536)
    (hm:models.length + (256 - i.val) < 4294967295) :
    slot.Z468_loop1 models tokpen ll i ⦃ fun r => r.length = models.length + (256 - i.val) ⦄ := by
  have h1 := EA.u378
  have h2 := Submission.Z466.EA.C_UNUSED_LIT_le
  rw [slot.Z468_loop1]
  apply SDN!
    (measure := fun (_, i') => 256 - i'.val)
    (inv := fun (m', i') => m'.length = models.length + (i'.val - i.val) ∧ i.val ≤ i'.val ∧ i'.val ≤ max i.val 256)
  · rintro ⟨m', i'⟩ ⟨h3, h4, h5⟩
    simp only [slot.Z468_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact ⟨by simp, le_refl _, by scalar_tac⟩
@[local step]
theorem u858 (models) (tax ulen tokpen:W) (ll) (l:R) (htax:tax.val ≤ 65536)
    (hulen:ulen.val ≤ 65536) (htok:tokpen.val ≤ 65536) (hl:3 ≤ l.val)
    (hm:models.length + (259 - l.val) < 4294967295) :
    slot.Z468_loop2 models tax ulen tokpen ll l ⦃ fun r => r.length = models.length + (259 - l.val) ⦄ := by
  have h1 := EA.u378
  rw [slot.Z468_loop2]
  apply SDN!
    (measure := fun (_, l') => 259 - l'.val)
    (inv := fun (m', l') => m'.length = models.length + (l'.val - l.val) ∧ l.val ≤ l'.val ∧ l'.val ≤ max l.val 259)
  · rintro ⟨m', l'⟩ ⟨h3, h4, h5⟩
    simp only [slot.Z468_loop2.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact ⟨by simp, le_refl _, by scalar_tac⟩
@[local step]
theorem u859 (models) (udist:W) (dl) (d:R) (hud:udist.val ≤ 65536)
    (hm:models.length + (32 - d.val) < 4294967295) :
    slot.Z468_loop3 models udist dl d ⦃ fun r => r.length = models.length + (32 - d.val) ⦄ := by
  have h1 := EA.u378
  rw [slot.Z468_loop3]
  apply SDN!
    (measure := fun (_, d') => 32 - d'.val)
    (inv := fun (m', d') => m'.length = models.length + (d'.val - d.val) ∧ d.val ≤ d'.val ∧ d'.val ≤ max d.val 32)
  · rintro ⟨m', d'⟩ ⟨h3, h4, h5⟩
    simp only [slot.Z468_loop3.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact ⟨by simp, le_refl _, by scalar_tac⟩
@[local step]
theorem u860 (models lf df) (tax ulen udist tokpen:W) (htax:tax.val ≤ 65536) (hulen:ulen.val ≤ 65536)
    (hud:udist.val ≤ 65536) (htok:tokpen.val ≤ 65536) (hm:models.length + 544 < 4294967295) :
    slot.Z468 models lf df tax ulen udist tokpen ⦃ fun r => r.1.val ≤ 70 + 288 * 2 ^ 42 ∧ r.2.length = models.length + 544 ⦄ := Y122U1! slot.Z468
@[local step]
theorem u861 (s:I) (choice) (n:R) (lf df) (p t:R)
    (hn:n.val ≤ s.length) (hnc:n.val ≤ choice.length) (hn26:n.val < 67108864) :
    slot.Z472_loop0_loop0 s choice n lf df p t ⦃ fun r => p.val ≤ r.2.2.val ∧
      r.2.2.val ≤ max p.val (n.val + 511) ∧
      (p.val < n.val → t.val < slot.Z45.val → p.val < r.2.2.val) ∧
      (r.2.2.val < n.val → p.val + (slot.Z45.val - t.val) ≤ r.2.2.val) ⦄ := by
  have hB := EA.u374
  rw [slot.Z472_loop0_loop0]
  apply SDN!
    (measure := fun (_, _, _, t') => slot.Z45.val - t'.val)
    (inv := fun (_, _, p', t') => p.val + (t'.val - t.val) ≤ p'.val ∧ t.val ≤ t'.val ∧
      p'.val ≤ max p.val (n.val + 511) ∧ t'.val ≤ max t.val slot.Z45.val)
  · rintro ⟨lf', df', p', t'⟩ ⟨h1, h2, h3, h4⟩
    simp only [slot.Z472_loop0_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact ⟨by simp, le_refl _, by scalar_tac, by scalar_tac⟩
@[local step]
theorem u862 (s:I) (choice models bstart) (tax ulen udist tokpen:W)
    (total:Std.U64) (n:R) (lf df) (p:R)
    (hn:n.val ≤ s.length) (hnc:n.val ≤ choice.length) (hn26:n.val < 67108864)
    (htax:tax.val ≤ 65536) (hulen:ulen.val ≤ 65536) (hud:udist.val ≤ 65536) (htok:tokpen.val ≤ 65536)
    (hb:544 * bstart.length ≤ models.length + 544)
    (ht:544 * total.val ≤ models.length * (70 + 288 * 2 ^ 42))
    (hm:models.length * 8192 < 544 * (n.val + 8192))
    (hp:p.val < n.val → models.length * 8192 ≤ 544 * p.val) :
    slot.Z472_loop0 s choice models bstart tax ulen udist tokpen total n lf df p ⦃ fun r =>
      544 * r.2.1.length ≤ r.1.length + 544 ∧ 544 * r.2.2.1.val ≤ r.1.length * (70 + 288 * 2 ^ 42) ∧
      r.1.length * 8192 < 544 * (n.val + 8192) ⦄ := by
  have hB := EA.u374
  rw [slot.Z472_loop0]
  apply SDN!
    (measure := fun (_, _, _, _, _, p') => n.val - p'.val)
    (inv := fun (m', b', t', _, _, p') => 544 * b'.length ≤ m'.length + 544 ∧
      544 * t'.val ≤ m'.length * (70 + 288 * 2 ^ 42) ∧ m'.length * 8192 < 544 * (n.val + 8192) ∧
      (p'.val < n.val → m'.length * 8192 ≤ 544 * p'.val))
  · rintro ⟨m', b', t', lf', df', p'⟩ ⟨h1, h2, h3, h4⟩
    simp only [slot.Z472_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact ⟨hb, ht, hm, hp⟩
@[local step]
theorem u863 (s:I) (choice models bstart) (tax ulen udist tokpen:W)
    (hn26:s.length < 67108864) (htax:tax.val ≤ 65536) (hulen:ulen.val ≤ 65536) (hud:udist.val ≤ 65536)
    (htok:tokpen.val ≤ 65536) :
    slot.Z472 s choice models bstart tax ulen udist tokpen ⦃ fun r => r.2.2.length ≤ 1048576 ⦄ := Y122U1! slot.Z472
@[local step]
theorem u864 (choice n p) :
    slot.Z457_loop0 choice n p ⦃ Y112P0! ⦄ := by
  rw [slot.Z457_loop0]
  apply SDN!
    (measure := fun (choice_, p_) => n.val - p_.val)
    (inv := fun _ => True)
  · rintro ⟨choice_, p_⟩ _
    simp only [slot.Z457_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem u865 (clist choice n gmin) (m k:R) (hm:m.val = clist.length) (hk:1 ≤ k.val) :
    slot.Z457_loop1 clist choice n gmin m k ⦃ Y112P0! ⦄ := by
  rw [slot.Z457_loop1]
  apply SDN!
    (measure := fun (_, k') => m.val - k'.val)
    (inv := fun (_, k') => 1 ≤ k'.val)
  · rintro ⟨choice', k'⟩ hk'
    simp only [slot.Z457_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact hk
@[local step]
theorem u866 (clist choice n gmin) :
    slot.Z457 clist choice n gmin ⦃ Y112P0! ⦄ := Y122U1! slot.Z457
@[local step]
theorem u867 (models:alloc.vec.Vec W) (lit_c len_c) (base i:R) (hb:base.val + slot.Z20.val ≤ models.length) :
    slot.Z461_loop0 models lit_c len_c base i ⦃ Y112P0! ⦄ := by
  rw [slot.Z461_loop0]
  apply SDN!
    (measure := fun (lit_c_, len_c_, i_) => 256 - i_.val)
    (inv := fun _ => True)
  · rintro ⟨lit_c_, len_c_, i_⟩ _
    simp only [slot.Z461_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem u868 (models:alloc.vec.Vec W) (dst_c) (base d:R) (hb:base.val + slot.Z20.val ≤ models.length) :
    slot.Z461_loop1 models dst_c base d ⦃ Y112P0! ⦄ := by
  rw [slot.Z461_loop1]
  apply SDN!
    (measure := fun (dst_c_, d_) => 32 - d_.val)
    (inv := fun _ => True)
  · rintro ⟨dst_c_, d_⟩ _
    simp only [slot.Z461_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem u869 (models) (b:R) (lit_c len_c dst_c) (hb:b.val ≤ 1048576) :
    slot.Z461 models b lit_c len_c dst_c ⦃ Y112P0! ⦄ := Y122U1! slot.Z461
@[local step]
theorem u870 (clist ge) :
    slot.Z458 clist ge ⦃ fun r => r.val ≤ ge.val ⦄ := Y122U1! slot.Z458
@[local step]
theorem u871 (bstart:alloc.vec.Vec W) (b q:R) (hb:b.val < bstart.length) :
    slot.Z449_loop0_loop0 bstart b q ⦃ fun r => r.val ≤ b.val ⦄ := by
  rw [slot.Z449_loop0_loop0]
  apply SDN!
    (measure := fun b' => b'.val)
    (inv := fun b' => b'.val ≤ b.val)
  · rintro b' hb'
    simp only [slot.Z449_loop0_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact le_refl _
@[local step]
theorem u872 (s:I) (choice:U) (ring lit_c next) (p lo:R)
    (hp:p.val ≤ s.length) (hc:s.length ≤ choice.length) :
    slot.Z449_loop0_loop1 s choice ring lit_c next p lo ⦃ fun r => r.1.length = choice.length ∧ r.2.2.2.val ≤ p.val ⦄ := by
  rw [slot.Z449_loop0_loop1]
  apply SDN!
    (measure := fun (_, _, _, p') => p'.val)
    (inv := fun (c', _, _, p') => c'.length = choice.length ∧ p'.val ≤ p.val)
  · rintro ⟨c', r', n', p'⟩ ⟨h1, h2⟩
    simp only [slot.Z449_loop0_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact ⟨rfl, le_refl _⟩
@[local step]
theorem u873 (ring len_c) (p:R) (best ch) (l:R) (dc tag) (len:R)
    (hp:p.val ≤ 2 ^ 30) (hl:l.val ≤ 511) (hlen:3 ≤ len.val) :
    slot.Z449_loop0_loop2_loop0 ring len_c p best ch l dc tag len ⦃ Y112P0! ⦄ := by
  rw [slot.Z449_loop0_loop2_loop0]
  apply SDN!
    (measure := fun (_, _, len') => l.val + 1 - len'.val)
    (inv := fun (_, _, len') => 3 ≤ len'.val)
  · rintro ⟨b', c', len'⟩ h1
    simp only [slot.Z449_loop0_loop2_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact hlen
@[local step]
theorem u874 (clist ring len_c dst_c) (ge p:R) (best ch) (prev room k:R)
    (hp:p.val ≤ 2 ^ 30) (hprev:2 ≤ prev.val ∧ prev.val ≤ 511)
    (hk:k.val ≤ clist.length) (hcl:clist.length < 4294967295) :
    slot.Z449_loop0_loop2 clist ring len_c dst_c ge p best ch prev room k ⦃ Y112P0! ⦄ := by
  rw [slot.Z449_loop0_loop2]
  apply SDN!
    (measure := fun (_, _, _, k') => clist.length - k'.val)
    (inv := fun (_, _, prev', k') => 2 ≤ prev'.val ∧ prev'.val ≤ 511 ∧ k'.val ≤ clist.length)
  · rintro ⟨b', c', prev', k'⟩ ⟨h1, h2, h3⟩
    simp only [slot.Z449_loop0_loop2.body]
    step*
    apply WP.spec_bind (Pₘ := fun (x:R) => 2 ≤ x.val ∧ x.val ≤ 511)
    · repeat' (split <;> step*)
      all_goals scalar_tac
    rintro prev1 ⟨hq1, hq2⟩
    step*
    apply WP.spec_bind (Pₘ := fun (x:R) => x.val ≤ 511)
    · split <;> step*
      all_goals scalar_tac
    rintro l1 hl1
    step*
    all_goals scalar_tac
  · exact ⟨hprev.1, hprev.2, hk⟩
@[local step]
theorem u875 (s:I) (clist models:alloc.vec.Vec W) (bstart:alloc.vec.Vec W) (choice:U)
    (n:R) (ring lit_c len_c dst_c) (b loaded ge gs gp:R) (next) (p fuel:R)
    (hn:n.val = s.length) (hn26:n.val < 67108864) (hc:n.val ≤ choice.length) (hb:b.val < bstart.length)
    (hnb:bstart.length ≤ 1048576) (hp:p.val ≤ n.val) (hgp:gp.val ≤ n.val ∨ gp.val < 2 ^ 27)
    (hcl:clist.length < 4294967295) (hgs:gs.val ≤ ge.val) (hge:ge.val ≤ clist.length) :
    slot.Z449_loop0 s clist models bstart choice n ring lit_c len_c dst_c b loaded ge gs gp next p fuel ⦃ Y112P0! ⦄ := by
  have hpm := EA.u376
  rw [slot.Z449_loop0]
  apply SDN!
    (measure := fun (_, _, _, _, _, _, _, _, _, _, _, _, f) => f.val)
    (inv := fun (c', _, _, _, _, b', _, ge', gs', gp', _, p', _) => c'.length = choice.length ∧
      b'.val < bstart.length ∧ p'.val ≤ n.val ∧ (gp'.val ≤ n.val ∨ gp'.val < 2 ^ 27) ∧
      gs'.val ≤ ge'.val ∧ ge'.val ≤ clist.length)
  · rintro ⟨c', r', l1', l2', d', b', ld', ge', gs', gp', nx', p', f'⟩ ⟨h1, h2, h3, h4, h5, h6⟩
    simp only [slot.Z449_loop0.body]
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
    all_goals scalar_tac
  · exact ⟨rfl, hb, hp, hgp, hgs, hge⟩
@[local step]
theorem u876 (s:I) (clist models) (bstart:alloc.vec.Vec W) (choice)
    (hn26:s.length < 67108864) (hnb:bstart.length ≤ 1048576) (hcl:clist.length < 4294967295) :
    slot.Z449 s clist models bstart choice ⦃ Y112P0! ⦄ := by
  have hms := EA.u375
  have hpm := EA.u376
  rw [slot.Z449]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac
@[local step]
theorem u877 (len) (d:R) (hd:1 ≤ d.val):slot.Z464 len d ⦃ Y112P0! ⦄ := Y122U1! slot.Z464
@[local step]
theorem u878 (clist:alloc.vec.Vec W) (ml md) (cnt:R) (flag) (top:R)
    (pushed:W) (i:R)
    (hcl:clist.length + (cnt.val - i.val) < 4294967295) (hpu:pushed.val ≤ 1) :
    slot.Z467_loop clist ml md cnt flag top pushed i ⦃ fun r =>
      r.1.length ≤ clist.length + (cnt.val - i.val) ∧ r.2.2.val ≤ pushed.val + (cnt.val - i.val) ∧
      (top.val ≤ 258 → r.2.1.val ≤ 258) ⦄ := by
  rw [slot.Z467_loop]
  apply SDN!
    (measure := fun (_, _, _, i') => 64 - i'.val)
    (inv := fun (c', t', u', i') => c'.length + (cnt.val - i'.val) ≤ clist.length + (cnt.val - i.val) ∧
      u'.val + (cnt.val - i'.val) ≤ pushed.val + (cnt.val - i.val) ∧ i.val ≤ i'.val ∧
      (top.val ≤ 258 → t'.val ≤ 258))
  · rintro ⟨c', t', u', i'⟩ ⟨h1, h2, h3, h4⟩
    simp only [slot.Z467_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact ⟨le_refl _, le_refl _, le_refl _, fun h => h⟩
@[local step]
theorem u879 (clist:alloc.vec.Vec W) (p ml md cnt r1 flag)
    (hcl:clist.length + slot.Z3.val + 2 < 4294967295) :
    slot.Z467 clist p ml md cnt r1 flag ⦃ fun r => r.2.length ≤ clist.length + slot.Z3.val + 2 ∧
      r.1.val ≤ 258 ⦄ := Y122U1! slot.Z467
@[local step]
theorem u880 (b) :
    slot.Z463 b ⦃ Y112P0! ⦄ := Y122U1! slot.Z463
@[local step]
theorem u881 (s) (i:R) (hi:i.val + 8 ≤ Usize.max):slot.Z475 s i ⦃ Y112P0! ⦄ := Y122U1! slot.Z475
set_option hygiene false in
local notation "Y122U27!" q0__:max q1__:max => (by
  rw [q0__]
  apply SDN!
    (measure := fun k_ => lim.val - k_.val)
    (inv := fun _ => True)
  · rintro k_ _
    simp only [q1__]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial)
@[local step]
theorem u882 (s:I) (a b lim k:R) (ha:a.val + lim.val ≤ s.length) (hb:b.val + lim.val ≤ s.length) :
    slot.Z453_loop0_loop0 s a b lim k ⦃ Y112P0! ⦄ := Y122U27! slot.Z453_loop0_loop0 slot.Z453_loop0_loop0.body
@[local step]
theorem u883 (s:I) (a b lim k:R) (ha:a.val + lim.val ≤ s.length) (hb:b.val + lim.val ≤ s.length) :
    slot.Z453_loop0_loop1 s a b lim k ⦃ Y112P0! ⦄ := Y122U27! slot.Z453_loop0_loop1 slot.Z453_loop0_loop1.body
@[local step]
theorem u884 (s:I) (a b lim k fuel:R) (ha:a.val + lim.val ≤ s.length)
    (hb:b.val + lim.val ≤ s.length) (hk:k.val ≤ 2 ^ 31) (hlim:lim.val ≤ 2 ^ 31) :
    slot.Z453_loop0 s a b lim k fuel ⦃ Y112P0! ⦄ := by
  rw [slot.Z453_loop0]
  apply SDN!
    (measure := fun (_, f') => f'.val)
    (inv := fun (k', _) => k'.val ≤ 2 ^ 31)
  · rintro ⟨k', f'⟩ hk'
    simp only [slot.Z453_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact hk
@[local step]
theorem u885 (s:I) (a b k0 lim:R) (ha:a.val + lim.val ≤ s.length) (hb:b.val + lim.val ≤ s.length)
    (hk0:k0.val ≤ 2 ^ 31) (hlim:lim.val ≤ 2 ^ 31) :
    slot.Z453 s a b k0 lim ⦃ Y112P0! ⦄ := Y122U1! slot.Z453
@[local step]
theorem u886 (s:I) (p k0 depth:R) (prev ml md) (lim cur best cnt steps:R)
    (hp:p.val + lim.val ≤ s.length) (hlim:lim.val ≤ 258) (hk0:k0.val ≤ 2 ^ 31) :
    slot.Z447_loop s p k0 depth prev ml md lim cur best cnt steps ⦃ Y112P0! ⦄ := by
  have hws := Submission.Z466.EA.dp_WN_val
  rw [slot.Z447_loop]
  apply SDN!
    (measure := fun (_, _, _, _, _, st) => depth.val - st.val)
    (inv := fun _ => True)
  · rintro ⟨ml', md', cur', best', cnt', st'⟩ _
    simp only [slot.Z447_loop.body]
    step*
    apply WP.spec_bind (Pₘ := fun _ => True)
    · repeat' (split <;> step*)
      all_goals scalar_tac
    rintro ⟨ml1, md1, best1, cnt1⟩ _
    step*
    all_goals scalar_tac
  · trivial
set_option hygiene false in
local notation "Y122U28!" q0__:max => (by
  have hws := Submission.Z466.EA.dp_WN_val
  have hhs := Submission.Z466.EA.C_HS_bounds
  rw [q0__]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac)
@[local step]
theorem u887 (s:I) (p key k0 best0 depth head prev ml md) (hp:p.val < s.length) (hk0:k0.val ≤ 2 ^ 31) :
    slot.Z447 s p key k0 best0 depth head prev ml md ⦃ Y112P0! ⦄ := Y122U28! slot.Z447
@[local step]
theorem u888 (kids) (which:R) (idx v) (hw:which.val ≤ 1) :
    slot.Z469 kids which idx v ⦃ Y112P0! ⦄ := by
  have hws := Submission.Z466.EA.dp_WN_val
  have hks := EA.u34
  rw [slot.Z469]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac
@[local step]
theorem u889 (back) (s:I) (p depth kids ml md) (lim cur lw li gw gi llen glen:R)
    (best cnt steps i)
    (hp:p.val + lim.val ≤ s.length) (hlim:lim.val ≤ 258) (hlw:lw.val ≤ 1) (hgw:gw.val ≤ 1)
    (hll:llen.val ≤ lim.val) (hgl:glen.val ≤ lim.val) :
    slot.Z446_loop back s p depth kids ml md lim cur lw li gw gi llen glen best cnt steps i ⦃ Y112P0! ⦄ := by
  have hws := Submission.Z466.EA.dp_WN_val
  have hks := EA.u34
  rw [slot.Z446_loop]
  apply SDN!
    (measure := fun (_, _, _, _, _, _, _, _, _, _, _, _, st) => depth.val - st.val)
    (inv := fun (_, _, _, _, lw', _, gw', _, ll', gl', _, _, _) => lw'.val ≤ 1 ∧ gw'.val ≤ 1 ∧
      ll'.val ≤ lim.val ∧ gl'.val ≤ lim.val)
  · rintro ⟨kids', ml', md', cur', lw', li', gw', gi', ll', gl', best', cnt', st'⟩ ⟨h1, h2, h3, h4⟩
    simp only [slot.Z446_loop.body]
    step*
    apply WP.spec_bind (Pₘ := fun (x:R) => x.val ≤ lim.val)
    · split <;> step*
      all_goals scalar_tac
    rintro k0 hk0
    step*
    apply WP.spec_bind (Pₘ := fun _ => True)
    · repeat' (split <;> step*)
      all_goals scalar_tac
    rintro ⟨ml1, md1, best1, cnt1⟩ _
    step*
    apply WP.spec_bind (Pₘ := fun (x:Std.Array W 65536#usize × R × R × R ×
        R × R × R × R) =>
      x.2.2.1.val ≤ 1 ∧ x.2.2.2.2.1.val ≤ 1 ∧ x.2.2.2.2.2.2.1.val ≤ lim.val ∧ x.2.2.2.2.2.2.2.val ≤ lim.val)
    · split <;> step*
      all_goals scalar_tac
    rintro ⟨kids1, cur1, lw1, li1, gw1, gi1, llen1, glen1⟩ ⟨h5, h6, h7, h8⟩
    step*
    all_goals scalar_tac
  · exact ⟨hlw, hgw, hll, hgl⟩
@[local step]
theorem u890 (s:I) (p h depth head kids ml md) (hp:p.val < s.length) :
    slot.Z446 s p h depth head kids ml md ⦃ Y112P0! ⦄ := Y122U28! slot.Z446
@[local step]
theorem u891 (s:I) (n key:R) (run run2 q:R) (hn:n.val = s.length)
    (hrun:run.val ≤ q.val) (hrun2:run2.val ≤ q.val) (hq:q.val ≤ 7) :
    slot.Z455_loop0 s n key run run2 q ⦃ fun r => r.2.1.val ≤ 7 ∧ r.2.2.val ≤ 7 ⦄ := by
  rw [slot.Z455_loop0]
  apply SDN!
    (measure := fun (_, _, _, q') => 7 - q'.val)
    (inv := fun (_, r1, r2, q') => r1.val ≤ q'.val ∧ r2.val ≤ q'.val ∧ q'.val ≤ 7)
  · rintro ⟨k', r1, r2, q'⟩ ⟨h1, h2, h3⟩
    simp only [slot.Z455_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact ⟨hrun, hrun2, hq⟩
@[local step]
theorem u892 (s:I) (clist) (depth_lo n:R) (head8 prev8 head3 kids ml md)
    (key run run2 p skip_to:R)
    (hn:n.val = s.length) (hn26:n.val < 67108864) (hrun:run.val ≤ p.val + 7) (hrun2:run2.val ≤ p.val + 7)
    (hp:p.val ≤ n.val) (hcl:clist.length ≤ 34 * p.val) :
    slot.Z455_loop1 s clist depth_lo n head8 prev8 head3 kids ml md key run run2 p skip_to ⦃ fun r =>
      r.length ≤ 34 * n.val ⦄ := by
  have hws := Submission.Z466.EA.dp_WN_val
  have hhs := Submission.Z466.EA.C_HS_bounds
  have hkp := EA.u377
  have hup := EA.u386
  rw [slot.Z455_loop1]
  apply SDN!
    (measure := fun (_, _, _, _, _, _, _, _, _, _, p', _) => n.val - p'.val)
    (inv := fun (c', _, _, _, _, _, _, _, r1, r2, p', _) => r1.val ≤ p'.val + 7 ∧ r2.val ≤ p'.val + 7 ∧
      p'.val ≤ n.val ∧ c'.length ≤ 34 * p'.val)
  · rintro ⟨c', h8', pv8', h3', kids', ml', md', key', r1, r2, p', sk'⟩ ⟨h1, h2, h3, h4⟩
    unfold slot.Z455_loop1.body
    step*
    apply WP.spec_bind (Pₘ := fun (x:R × R × R) =>
      x.2.1.val ≤ p'.val + 8 ∧ x.2.2.val ≤ p'.val + 8)
    · repeat' (split <;> step*)
      all_goals scalar_tac
    rintro ⟨key1, run1, run21⟩ ⟨hr1, hr2⟩
    step*
    apply WP.spec_bind (Pₘ := fun (x:alloc.vec.Vec W × Std.Array W 65536#usize ×
        Std.Array W 32768#usize × Std.Array W 65536#usize × Std.Array W 65536#usize ×
        Std.Array W 64#usize × Std.Array W 64#usize × R) =>
      x.1.length ≤ c'.length + 34)
    · apply EA.u119
      · intro hc
        step*
        ·
          apply WP.spec_bind (Pₘ := fun (x:alloc.vec.Vec W × _) => x.1.length ≤ c'.length + 34)
          · apply EA.u119
            · intro hs
              step*
              apply WP.spec_bind (Pₘ := fun (x:alloc.vec.Vec W × _) => x.1.length ≤ c'.length + 34)
              · apply EA.u119
                · intro hcnt
                  step*
                  apply EA.u402 <;> intro _ <;> step*
                · intro hcnt
                  step*
              · rintro ⟨v2, a4, a5, i17⟩ hv2
                step*
            · intro hs
              step*
          · rintro ⟨v1, a, a1, a2, a3, i16⟩ hv1
            step*
        ·
          apply WP.spec_bind (Pₘ := fun (x:alloc.vec.Vec W × _) => x.1.length ≤ c'.length + 34)
          · apply EA.u119
            ·
              intro hr
              apply WP.spec_bind (Pₘ := fun (x:alloc.vec.Vec W × _) => x.1.length ≤ c'.length + 34)
              · apply EA.u119
                · intro hs
                  step*
                  apply WP.spec_bind (Pₘ := fun (x:alloc.vec.Vec W × _) => x.1.length ≤ c'.length + 34)
                  · apply EA.u119
                    · intro hcnt
                      step*
                      apply EA.u402 <;> intro _ <;> step*
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
              apply WP.spec_bind (Pₘ := fun (x:alloc.vec.Vec W × _) => x.1.length ≤ c'.length + 34)
              · apply EA.u119
                · intro hr2
                  step*
                  apply WP.spec_bind (Pₘ := fun (x:alloc.vec.Vec W × _) => x.1.length ≤ c'.length + 34)
                  · apply EA.u119
                    · intro hcnt
                      step*
                      apply EA.u402 <;> intro _ <;> step*
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
          apply WP.spec_bind (Pₘ := fun (x:alloc.vec.Vec W × _) => x.1.length ≤ c'.length + 34)
          · apply EA.u119
            ·
              intro hr
              apply WP.spec_bind (Pₘ := fun (x:alloc.vec.Vec W × _) => x.1.length ≤ c'.length + 34)
              · apply EA.u119
                · intro hs
                  step*
                  apply WP.spec_bind (Pₘ := fun (x:alloc.vec.Vec W × _) => x.1.length ≤ c'.length + 34)
                  · apply EA.u119
                    · intro hcnt
                      step*
                      apply EA.u402 <;> intro _ <;> step*
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
              apply WP.spec_bind (Pₘ := fun (x:alloc.vec.Vec W × _) => x.1.length ≤ c'.length + 34)
              · apply EA.u119
                · intro hr2
                  step*
                  apply WP.spec_bind (Pₘ := fun (x:alloc.vec.Vec W × _) => x.1.length ≤ c'.length + 34)
                  · apply EA.u119
                    · intro hcnt
                      step*
                      apply EA.u402 <;> intro _ <;> step*
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
    all_goals scalar_tac
  · exact ⟨hrun, hrun2, hp, hcl⟩
@[local step]
theorem u893 (s:I) (clist) (depth_lo) (hn26:s.length < 67108864) (hcl:clist.length = 0) :
    slot.Z455 s clist depth_lo ⦃ fun r => r.length ≤ 34 * s.length ⦄ := by
  rw [slot.Z455]
  step*
@[local step]
theorem u894 (s:I) (p:R) (hp:p.val ≤ 2 ^ 31):slot.Z474 s p ⦃ Y112P0! ⦄ := Y122U1! slot.Z474
@[local step]
theorem u895 (s:I) (clist) (chain depth n:R) (head lt kids ml md)
    (p skip_to pend:R)
    (hn:n.val = s.length) (hn26:n.val < 67108864) (hp:p.val ≤ n.val) (hcl:clist.length ≤ 34 * p.val) :
    slot.Z454_loop s clist chain depth n head lt kids ml md p skip_to pend ⦃ fun r => r.length ≤ 34 * n.val ⦄ := by
  have hws := Submission.Z466.EA.dp_WN_val
  have hhs := Submission.Z466.EA.C_HS_bounds
  have hkp := EA.u377
  rw [slot.Z454_loop]
  apply SDN!
    (measure := fun (_, _, _, _, _, _, p', _, _) => n.val - p'.val)
    (inv := fun (c', _, _, _, _, _, p', _, _) => p'.val ≤ n.val ∧ c'.length ≤ 34 * p'.val)
  · rintro ⟨c', hd', lt', kids', ml', md', p', sk', pe'⟩ ⟨h1, h2⟩
    unfold slot.Z454_loop.body
    step*
    apply WP.spec_bind (Pₘ := fun _ => True)
    · split <;> step*
    rintro key _
    step*
    apply WP.spec_bind (Pₘ := fun (x:alloc.vec.Vec W × Std.Array W 65536#usize ×
        Std.Array W 32768#usize × Std.Array W 65536#usize × Std.Array W 64#usize ×
        Std.Array W 64#usize × R × R) =>
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
        apply WP.spec_bind (Pₘ := fun (x:alloc.vec.Vec W × R) =>
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
theorem u896 (s:I) (clist chain depth) (hn26:s.length < 67108864) (hcl:clist.length = 0) :
    slot.Z454 s clist chain depth ⦃ fun r => r.length ≤ 34 * s.length ⦄ := by
  rw [slot.Z454]
  step*
set_option hygiene false in
local notation "Y122U29!" q0__:max q1__:max => (by
  have h1 := Submission.Z466.EA.C_UNUSED_LIT_le
  have h2 := Submission.Z466.EA.C_UNUSED_DIST_le
  have h3 := Submission.Z466.EA.C_STOP_DIV_pos
  rw [q0__]
  apply SDN!
    (measure := fun (_, _, _, _, pass') => passes.val - pass'.val)
    (inv := fun (_, _, b', _, _) => b'.length ≤ 1048576)
  · rintro ⟨out', models', b', le', pass'⟩ hb'
    simp only [q1__]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact hnb)
@[local step]
theorem u897 (input:I) (out min_dna dna) (clist:alloc.vec.Vec W) (models)
    (bstart:alloc.vec.Vec W) (passes) (tax tokpen:W) (last_est pass)
    (hn26:input.length < 67108864) (htax:tax.val ≤ 65536) (htok:tokpen.val ≤ 65536)
    (hnb:bstart.length ≤ 1048576) (hcl:clist.length < 4294967295) :
    slot.Z452_loop0 input out min_dna dna clist models bstart passes tax tokpen last_est pass ⦃ Y112P0! ⦄ := Y122U29! slot.Z452_loop0 slot.Z452_loop0.body
@[local step]
theorem u898 (input:I) (out min_dna dna) (clist:alloc.vec.Vec W) (models)
    (bstart:alloc.vec.Vec W) (passes) (tax tokpen:W) (last_est pass)
    (hn26:input.length < 67108864) (htax:tax.val ≤ 65536) (htok:tokpen.val ≤ 65536)
    (hnb:bstart.length ≤ 1048576) (hcl:clist.length < 4294967295) :
    slot.Z452_loop1 input out min_dna dna clist models bstart passes tax tokpen last_est pass ⦃ Y112P0! ⦄ := Y122U29! slot.Z452_loop1 slot.Z452_loop1.body
@[local step]
theorem u899 (input:I) (out min_dna dna) (clist:alloc.vec.Vec W) (models)
    (bstart:alloc.vec.Vec W) (passes) (tax tokpen:W) (last_est pass)
    (hn26:input.length < 67108864) (htax:tax.val ≤ 65536) (htok:tokpen.val ≤ 65536)
    (hnb:bstart.length ≤ 1048576) (hcl:clist.length < 4294967295) :
    slot.Z452_loop2 input out min_dna dna clist models bstart passes tax tokpen last_est pass ⦃ Y112P0! ⦄ := Y122U29! slot.Z452_loop2 slot.Z452_loop2.body
@[local step]
theorem u900 (input:I) (out) (depth depth_lo wdp passes_w passes_bt passes_dna min_dna passes_c4:R)
    (hn:input.length < 67108864) (h1:depth.val ≤ 65536) (h2:depth_lo.val ≤ 65536) (h3:wdp.val ≤ 65536)
    (h4:passes_w.val ≤ 65536) (h5:passes_bt.val ≤ 65536) (h6:passes_dna.val ≤ 65536) (h7:min_dna.val ≤ 65536)
    (h8:passes_c4.val ≤ 65536) :
    slot.Z452 input out depth depth_lo wdp passes_w passes_bt passes_dna min_dna passes_c4 ⦃ Y112P0! ⦄ := by
  have f1 := EA.u381
  have f2 := EA.u381
  have f3 := EA.u382
  have f4 := EA.u379
  have f5 := EA.u380
  have f6 := EA.u383
  have f7 := EA.u383
  have f8 := EA.u384
  have f9 := EA.u383
  have f10 := Submission.Z466.EA.C_UNUSED_LIT_le
  have f11 := Submission.Z466.EA.C_UNUSED_DIST_le
  have f12 := EA.u385
  rw [slot.Z452]
  step*
  ·
    apply WP.spec_bind (Pₘ := fun (x:alloc.vec.Vec W) => x.length ≤ 34 * input.length)
    · repeat' (split <;> step*)
      all_goals exact EA.u401 _
    rintro clist1 hc1
    apply WP.spec_bind (Pₘ := fun _ => True)
    · repeat' (split <;> step*)
    rintro passes _
    apply WP.spec_bind (Pₘ := fun (x:W) => x.val ≤ 65536)
    · repeat' (split <;> step*)
      all_goals scalar_tac
    rintro tax htax
    apply WP.spec_bind (Pₘ := fun (x:W) => x.val ≤ 65536)
    · repeat' (split <;> step*)
      all_goals scalar_tac
    rintro ulen hulen
    apply WP.spec_bind (Pₘ := fun (x:W) => x.val ≤ 65536)
    · repeat' (split <;> step*)
      all_goals scalar_tac
    rintro udist hudist
    apply WP.spec_bind (Pₘ := fun _ => True)
    · repeat' (split <;> step*)
    rintro gmin _
    step*
    apply WP.spec_bind (Pₘ := fun (x:alloc.vec.Vec W × W) => x.2.val ≤ 65536)
    · repeat' (split <;> step*)
      all_goals scalar_tac
    rintro ⟨out1, tokpen⟩ htok
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  ·
    apply WP.spec_bind (Pₘ := fun _ => True)
    · repeat' (split <;> step*)
      all_goals scalar_tac
    rintro chain4 _
    step*
    apply WP.spec_bind (Pₘ := fun (x:alloc.vec.Vec W) => x.length ≤ 34 * input.length)
    · repeat' (split <;> step*)
      all_goals exact EA.u401 _
    rintro clist1 hc1
    apply WP.spec_bind (Pₘ := fun _ => True)
    · repeat' (split <;> step*)
    rintro passes _
    apply WP.spec_bind (Pₘ := fun (x:W) => x.val ≤ 65536)
    · repeat' (split <;> step*)
      all_goals scalar_tac
    rintro tax htax
    apply WP.spec_bind (Pₘ := fun (x:W) => x.val ≤ 65536)
    · repeat' (split <;> step*)
      all_goals scalar_tac
    rintro ulen hulen
    apply WP.spec_bind (Pₘ := fun (x:W) => x.val ≤ 65536)
    · repeat' (split <;> step*)
      all_goals scalar_tac
    rintro udist hudist
    apply WP.spec_bind (Pₘ := fun _ => True)
    · repeat' (split <;> step*)
    rintro gmin _
    step*
    apply WP.spec_bind (Pₘ := fun (x:alloc.vec.Vec W × W) => x.2.val ≤ 65536)
    · repeat' (split <;> step*)
      all_goals scalar_tac
    rintro ⟨out1, tokpen⟩ htok
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  ·
    apply WP.spec_bind (Pₘ := fun (x:alloc.vec.Vec W) => x.length ≤ 34 * input.length)
    · repeat' (split <;> step*)
      all_goals exact EA.u401 _
    rintro clist1 hc1
    apply WP.spec_bind (Pₘ := fun _ => True)
    · repeat' (split <;> step*)
    rintro passes _
    apply WP.spec_bind (Pₘ := fun (x:W) => x.val ≤ 65536)
    · repeat' (split <;> step*)
      all_goals scalar_tac
    rintro tax htax
    apply WP.spec_bind (Pₘ := fun (x:W) => x.val ≤ 65536)
    · repeat' (split <;> step*)
      all_goals scalar_tac
    rintro ulen hulen
    apply WP.spec_bind (Pₘ := fun (x:W) => x.val ≤ 65536)
    · repeat' (split <;> step*)
      all_goals scalar_tac
    rintro udist hudist
    apply WP.spec_bind (Pₘ := fun _ => True)
    · repeat' (split <;> step*)
    rintro gmin _
    step*
    apply WP.spec_bind (Pₘ := fun (x:alloc.vec.Vec W × W) => x.2.val ≤ 65536)
    · repeat' (split <;> step*)
      all_goals scalar_tac
    rintro ⟨out1, tokpen⟩ htok
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
theorem spine_CFG_le:∀ r ∈ slot.Z146.val, ∀ x ∈ r.val, x.val ≤ 65536 := by
  unfold slot.Z146;decide
theorem spine_CFG_skip:∀ r ∈ slot.Z146.val, (r.val[0]!).val = 0 → 3 ≤ (r.val[2]!).val := by
  unfold slot.Z146;decide
@[local step]
theorem u901 (input:I) (k) (hn:input.length < 67108864) :
    slot.Z479 input k ⦃ Y112P0! ⦄ := Y122U26! slot.Z479 slot.Z146.val
@[local step]
theorem u902 (input) (k:R):slot.Z477 input k ⦃ Y112P0! ⦄ := by
  rw [slot.Z477]
  step*
@[step]
theorem u903 (input:I) (out:U) (k:R)
    (hlen:input.length ≤ out.length) :
    slot.Z476 input out k ⦃ Y112P1! ⦄ := by
  rw [slot.Z476]
  step*
  refine ⟨by assumption, by assumption, ?_⟩
  unfold LZ77.Valid
  assumption

@[local step]
theorem u904 (input:I) (out:U) (mode:R) (hlen:input.length ≤ out.length):slot.Z478 input out mode ⦃ Y112P1! ⦄ := by
 rw [slot.Z478]
 step*
 all_goals repeat' (split <;> step*)
end ED
end Z466

@[local step]
theorem z478_spec (input : Slice Std.U8) (out : Slice Std.U32) (mode : Std.Usize) (hlen : input.length ≤ out.length) :
    slot.Z478 input out mode ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧
      LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ :=
  Z466.ED.u904 input out mode hlen

namespace X32

set_option maxRecDepth 8192
set_option maxHeartbeats 2000000
set_option linter.unusedTactic false
set_option linter.unreachableTactic false
set_option linter.style.multiGoal false

open LZ77 (toks bytes bytes_length bytes_getElem! toks_update bytes_congr
  Matches Found Pending emitted emitted_ge emitted_lt pending_of_found emit_lit emit_match ite_ok)

theorem numBits_ge : 32 ≤ System.Platform.numBits := by
  rcases System.Platform.numBits_eq with h | h <;> omega

@[local step]
theorem load32_spec (input : Slice Std.U8) (p : Std.Usize) (h : p.val + 4 ≤ input.length) :
    slot.x32_load32 input p ⦃ fun _ => True ⦄ := by
  rw [slot.x32_load32]
  step*

@[local step]
theorem load64_spec (input : Slice Std.U8) (p : Std.Usize) (h : p.val + 8 ≤ input.length) :
    slot.x32_load64 input p ⦃ fun _ => True ⦄ := by
  rw [slot.x32_load64]
  step*

@[local step]
theorem h4_spec (x : Std.U32) : slot.x32_h4 x ⦃ fun r => r.val < 65536 ⦄ := by
  rw [slot.x32_h4]
  step*

@[local step]
theorem h3_spec (x : Std.U32) : slot.x32_h3 x ⦃ fun r => r.val < 32768 ⦄ := by
  rw [slot.x32_h3]
  step*

theorem ext_loop0_spec (input : Slice Std.U8) (a b cap n8 l0 : Std.Usize)
    (hab : a.val < b.val) (hn8 : n8.val ≤ input.length - 8) :
    slot.x32_ext_loop0 input a b cap n8 l0 ⦃ fun _ => True ⦄ := by
  rw [slot.x32_ext_loop0]
  apply Std.loop.spec_decr_nat (measure := fun l => cap.val - l.val) (inv := fun _ => True)
  · intro l _
    simp only [slot.x32_ext_loop0.body]
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    step*
    all_goals scalar_tac
  · trivial

theorem ext_loop1_spec (input : Slice Std.U8) (a b cap l0 : Std.Usize)
    (hab : a.val < b.val) (hb : b.val + cap.val ≤ input.length) :
    slot.x32_ext_loop1 input a b cap l0 ⦃ fun _ => True ⦄ := by
  rw [slot.x32_ext_loop1]
  apply Std.loop.spec_decr_nat (measure := fun l => cap.val - l.val) (inv := fun _ => True)
  · intro l _
    simp only [slot.x32_ext_loop1.body]
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    step*
  · trivial

@[local step]
theorem ext_spec (input : Slice Std.U8) (a b start cap : Std.Usize)
    (hab : a.val < b.val) (hb : b.val + cap.val ≤ input.length) :
    slot.x32_ext input a b start cap ⦃ fun _ => True ⦄ := by
  rw [slot.x32_ext]
  apply Std.WP.spec_bind (Pₘ := fun (n8 : Std.Usize) => n8.val ≤ input.length - 8)
  · split
    · step*
    · simp only [Std.WP.spec_ok]; scalar_tac
  · intro n8 hn8
    apply Std.WP.spec_bind (ext_loop0_spec input a b cap n8 start hab hn8)
    intro l _
    apply Std.WP.spec_bind (ext_loop1_spec input a b cap l hab hb)
    intro l1 _
    split <;> simp

theorem match_len_loop_spec (input : Slice Std.U8) (a b cap l0 : Std.Usize)
    (ha : a.val + cap.val ≤ input.length) (hb : b.val + cap.val ≤ input.length)
    (hl0 : l0.val ≤ cap.val) (h0 : Matches input a.val b.val l0.val) :
    slot.x32_match_len_loop input a b cap l0 ⦃ fun l =>
      l.val ≤ cap.val ∧ Matches input a.val b.val l.val ⦄ := by
  rw [slot.x32_match_len_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun l => cap.val - l.val)
    (inv := fun l => l.val ≤ cap.val ∧ LZ77.Matches input a.val b.val l.val)
  · rintro l ⟨hle, hinv⟩
    simp only [slot.x32_match_len_loop.body]
    split
    case isTrue hlt =>
      have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
      step*
      all_goals first
        | scalar_tac
        | exact ⟨hle, hinv⟩
        | (refine ⟨by scalar_tac, ?_, by scalar_tac⟩
           rw [show l1.val = l.val + 1 by scalar_tac]
           apply LZ77.Matches.succ hinv
           rw [← i_post, ← i2_post, getElem!_pos _ _ (by scalar_tac),
             getElem!_pos _ _ (by scalar_tac), ← i1_post, ← i3_post]
           assumption)
    case isFalse => exact ⟨hle, hinv⟩
  · exact ⟨hl0, h0⟩

@[local step]
theorem match_len_spec (input : Slice Std.U8) (a b cap : Std.Usize)
    (ha : a.val + cap.val ≤ input.length) (hb : b.val + cap.val ≤ input.length) :
    slot.x32_match_len input a b cap ⦃ fun l =>
      l.val ≤ cap.val ∧ Matches input a.val b.val l.val ⦄ := by
  prove_match_len

@[local step]
theorem len_slot_spec (len : Std.Usize) : slot.x32_len_slot len ⦃ fun _ => True ⦄ := by
  rw [slot.x32_len_slot]
  have := numBits_ge
  step*
  all_goals (try split) <;> step* <;> (try split) <;> step* <;> (try split) <;> step*

@[local step]
theorem len_extra_spec (len : Std.Usize) : slot.x32_len_extra len ⦃ fun _ => True ⦄ := by
  rw [slot.x32_len_extra]
  step*
  all_goals (try split) <;> step* <;> (try split) <;> step* <;> (try split) <;> step*

@[local step]
theorem dist_slot_spec (d : Std.Usize) : slot.x32_dist_slot d ⦃ fun r => r.val < 32 ⦄ := by
  rw [slot.x32_dist_slot]
  have := numBits_ge
  step*
  all_goals (try split) <;> step* <;> (try split) <;> step* <;> (try split) <;> step*

@[local step]
theorem dist_extra_spec (s : Std.Usize) : slot.x32_dist_extra s ⦃ fun _ => True ⦄ := by
  rw [slot.x32_dist_extra]
  step*

@[local step]
theorem log2x16_spec (x : Std.U32) : slot.x32_log2x16 x ⦃ fun _ => True ⦄ := by
  rw [slot.x32_log2x16]
  step*
  all_goals (try split) <;> step* <;> (try split) <;> step* <;> (try split) <;> step*

@[local step]
theorem cost_of_spec (f total nostat : Std.U32) : slot.x32_cost_of f total nostat ⦃ fun _ => True ⦄ := by
  rw [slot.x32_cost_of]
  step*

@[local step]
theorem probe3_spec (input : Slice Std.U8) (c3 pos : Std.Usize) (h : pos.val + 3 ≤ input.length) :
    slot.x32_probe3 input c3 pos ⦃ fun _ => True ⦄ := by
  rw [slot.x32_probe3]
  step*

theorem hc_walk_loop_spec (input : Slice Std.U8) (prev : Array Std.U32 65536#usize)
    (pos cap : Std.Usize) (ml md : Array Std.U16 262144#usize) (depth : Std.Usize) (seq : Std.U32)
    (nm d3 best_len first cur probes nice : Std.Usize)
    (hcap : pos.val + cap.val ≤ input.length) (h4 : pos.val + 4 ≤ input.length) :
    slot.x32_hc_walk_loop input prev pos cap ml md depth seq nm d3 best_len first cur probes nice
      ⦃ fun _ => True ⦄ := by
  rw [slot.x32_hc_walk_loop]
  apply Std.loop.spec_decr_nat (measure := fun s => depth.val - s.2.2.2.2.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨ml, md, nm, bl, fs, cur, probes⟩ _
    simp only [slot.x32_hc_walk_loop.body]
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    step*
    all_goals repeat' (first | (split <;> step*) | scalar_tac)
  · trivial

@[local step]
theorem hc_walk_spec (input : Slice Std.U8) (prev : Array Std.U32 65536#usize)
    (pos cap : Std.Usize) (ml md : Array Std.U16 262144#usize)
    (nm0 depth nice_c c4 c3 : Std.Usize) (seq : Std.U32)
    (hcap : pos.val + cap.val ≤ input.length) (h4 : pos.val + 4 ≤ input.length) :
    slot.x32_hc_walk input prev pos cap ml md nm0 depth nice_c c4 c3 seq ⦃ fun _ => True ⦄ := by
  rw [slot.x32_hc_walk]
  step*
  all_goals repeat' (first | (split <;> step*) | scalar_tac |
    (apply Std.WP.spec_bind (hc_walk_loop_spec _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ hcap h4)
     rintro ⟨_, _, _, _, _⟩ _
     step*))

@[local step]
theorem hc_find_spec (input : Slice Std.U8) (head4 head3 : Array Std.U32 65536#usize)
    (prev : Array Std.U32 65536#usize) (pos cap : Std.Usize) (ml md : Array Std.U16 262144#usize)
    (nm0 depth nice_c : Std.Usize)
    (hcap : pos.val + cap.val ≤ input.length) (h4 : pos.val + 4 ≤ input.length) :
    slot.x32_hc_find input head4 head3 prev pos cap ml md nm0 depth nice_c ⦃ fun _ => True ⦄ := by
  rw [slot.x32_hc_find]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  step*

@[local step]
theorem hc_insert_spec (input : Slice Std.U8) (head4 head3 : Array Std.U32 65536#usize)
    (prev : Array Std.U32 65536#usize) (k : Std.Usize) (h4 : k.val + 4 ≤ input.length) :
    slot.x32_hc_insert input head4 head3 prev k ⦃ fun _ => True ⦄ := by
  rw [slot.x32_hc_insert]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  step*

@[local step]
theorem bt_rec3_spec (input : Slice Std.U8) (c3a c3b pos : Std.Usize)
    (ml md : Array Std.U16 262144#usize) (nm0 : Std.Usize) (h : pos.val + 3 ≤ input.length) :
    slot.x32_bt_rec3 input c3a c3b pos ml md nm0 ⦃ fun _ => True ⦄ := by
  rw [slot.x32_bt_rec3]
  step*

theorem bt_walk_loop_spec (input : Slice Std.U8) (lr : Array Std.U32 65536#usize)
    (pos cap depth record : Std.Usize) (ml md : Array Std.U16 262144#usize)
    (nm cur lt_p gt_p best_lt best_gt len best_len nice probes : Std.Usize)
    (hcap : pos.val + cap.val ≤ input.length) (hnice : nice.val ≤ cap.val)
    (hinv : 1 ≤ cur.val ∧ cur.val ≤ pos.val ∧ len.val < cap.val ∧ best_lt.val < cap.val ∧
      best_gt.val < cap.val) :
    slot.x32_bt_walk_loop input lr pos cap depth record ml md nm cur lt_p gt_p
      best_lt best_gt len best_len nice probes ⦃ fun _ => True ⦄ := by
  rw [slot.x32_bt_walk_loop]
  apply Std.loop.spec_decr_nat (measure := fun s => depth.val - s.2.2.2.2.2.2.2.2.2.2.2.val)
    (inv := fun s => 1 ≤ s.2.2.2.2.1.val ∧ s.2.2.2.2.1.val ≤ pos.val ∧ s.2.2.2.2.2.2.2.2.2.1.val < cap.val ∧
      s.2.2.2.2.2.2.2.1.val < cap.val ∧ s.2.2.2.2.2.2.2.2.1.val < cap.val)
  · rintro ⟨lr, ml, md, nm, cur, ltp, gtp, blt, bgt, len, bl, probes⟩
      ⟨hc1, hc2, hlen, hblt, hbgt⟩
    simp only at hc1 hc2 hlen hblt hbgt
    simp only [slot.x32_bt_walk_loop.body]
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    step*
    all_goals repeat' (first | (split <;> step*) | scalar_tac)
  · exact hinv

@[local step]
theorem bt_walk_spec (input : Slice Std.U8) (lr : Array Std.U32 65536#usize)
    (pos cap depth record : Std.Usize) (ml md : Array Std.U16 262144#usize)
    (nm1 nm0 nice_c cur0 slt : Std.Usize)
    (hcap : pos.val + cap.val ≤ input.length) (hc4 : 4 ≤ cap.val)
    (hcur : 1 ≤ cur0.val ∧ cur0.val ≤ pos.val) :
    slot.x32_bt_walk input lr pos cap depth record ml md nm1 nm0 nice_c cur0 slt
      ⦃ fun _ => True ⦄ := by
  rw [slot.x32_bt_walk]
  step*
  apply Std.WP.spec_bind (Pₘ := fun (nice : Std.Usize) => nice.val ≤ cap.val)
  · split <;> simp only [Std.WP.spec_ok] <;> scalar_tac
  · intro nice hnice
    apply Std.WP.spec_bind (bt_walk_loop_spec input lr pos cap depth record ml md nm1 cur0
      _ _ 0#usize 0#usize 0#usize 3#usize nice 0#usize hcap hnice
      ⟨hcur.1, hcur.2, by scalar_tac, by scalar_tac, by scalar_tac⟩)
    rintro ⟨_, _, _, _, _⟩ _
    step*
    all_goals repeat' (first | (split <;> step*) | scalar_tac)

@[local step]
theorem bt_find_spec (input : Slice Std.U8) (head4 h3w lr : Array Std.U32 65536#usize)
    (pos cap depth record : Std.Usize)
    (ml md : Array Std.U16 262144#usize) (nm0 nice_c : Std.Usize)
    (hcap : pos.val + cap.val ≤ input.length) (h4 : pos.val + 4 ≤ input.length) :
    slot.x32_bt_find input head4 h3w lr pos cap depth record ml md nm0 nice_c
      ⦃ fun _ => True ⦄ := by
  rw [slot.x32_bt_find]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  step*
  all_goals repeat' (first | (split <;> step*) | scalar_tac | (casesm _ × _ <;> step*))

@[local step]
theorem find_seg_loop0_loop0_spec (input : Slice Std.U8) (head4 head3 prev : Array Std.U32 65536#usize)
    (ml md : Array Std.U16 262144#usize) (mstart : Array Std.U32 65536#usize)
    (pos0 slen depth nice n nm k0 skip0 : Std.Usize)
    (hn : n.val = input.length) (hseg : pos0.val + slen.val ≤ input.length) :
    slot.x32_find_seg_loop0_loop0 input head4 head3 prev ml md mstart pos0 slen depth nice n nm k0 skip0
      ⦃ fun r => k0.val ≤ r.2.2.2.2.2.2.val ⦄ := by
  rw [slot.x32_find_seg_loop0_loop0]
  apply Std.loop.spec_decr_nat (measure := fun s => s.2.2.2.2.2.2.2.val)
    (inv := fun s => k0.val ≤ s.2.2.2.2.2.2.1.val)
  · rintro ⟨h4, h3, pv, ml, md, ms, k, skip⟩ hk
    simp only at hk
    simp only [slot.x32_find_seg_loop0_loop0.body]
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    step*
    all_goals repeat' (first | (split <;> step*) | scalar_tac | (casesm _ × _ <;> step*))
  · simp

theorem find_seg_loop0_spec (input : Slice Std.U8) (head4 head3 prev : Array Std.U32 65536#usize)
    (ml md : Array Std.U16 262144#usize) (mstart : Array Std.U32 65536#usize)
    (pos0 slen depth nice n nm k0 : Std.Usize)
    (hn : n.val = input.length) (hseg : pos0.val + slen.val ≤ input.length) :
    slot.x32_find_seg_loop0 input head4 head3 prev ml md mstart pos0 slen depth nice n nm k0
      ⦃ fun _ => True ⦄ := by
  rw [slot.x32_find_seg_loop0]
  apply Std.loop.spec_decr_nat (measure := fun s => slen.val - s.2.2.2.2.2.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨h4, h3, pv, ml, md, ms, nm, k⟩ _
    simp only [slot.x32_find_seg_loop0.body]
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    step*
    all_goals repeat' (first | (split <;> step*) | scalar_tac | (casesm _ × _ <;> step*))
  · trivial

@[local step]
theorem find_seg_spec (input : Slice Std.U8) (head4 head3 prev : Array Std.U32 65536#usize)
    (ml md : Array Std.U16 262144#usize) (mstart : Array Std.U32 65536#usize)
    (pos0 slen depth nice : Std.Usize) (hseg : pos0.val + slen.val ≤ input.length) :
    slot.x32_find_seg input head4 head3 prev ml md mstart pos0 slen depth nice ⦃ fun _ => True ⦄ := by
  rw [slot.x32_find_seg]
  apply Std.WP.spec_bind (find_seg_loop0_spec input head4 head3 prev ml md mstart pos0 slen depth
    nice _ 0#usize 0#usize (by simp) hseg)
  rintro ⟨_, _, _, _, _, _, _⟩ _
  step*

@[local step]
theorem init_costs_spec (input : Slice Std.U8) (lit_cost : Array Std.U32 256#usize)
    (len_cost : Array Std.U32 512#usize) (dcost : Array Std.U32 32#usize) (pos0 slen : Std.Usize)
    (hseg : pos0.val + slen.val ≤ input.length) :
    slot.x32_init_costs input lit_cost len_cost dcost pos0 slen ⦃ fun _ => True ⦄ := by
  rw [slot.x32_init_costs]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  apply Std.WP.spec_bind (Pₘ := fun _ => True)
  · rw [slot.x32_init_costs_loop0]
    apply Std.loop.spec_decr_nat (measure := fun s => slen.val - s.2.val) (inv := fun _ => True)
    · rintro ⟨h, q⟩ _
      simp only [slot.x32_init_costs_loop0.body]
      step*
    · trivial
  · intro hist _
    apply Std.WP.spec_bind (Pₘ := fun _ => True)
    · rw [slot.x32_init_costs_loop1]
      apply Std.loop.spec_decr_nat (measure := fun s => 256 - s.2.val) (inv := fun _ => True)
      · rintro ⟨c, s⟩ _
        simp only [slot.x32_init_costs_loop1.body]
        step*
      · trivial
    · intro lc _
      apply Std.WP.spec_bind (Pₘ := fun _ => True)
      · rw [slot.x32_init_costs_loop2]
        apply Std.loop.spec_decr_nat (measure := fun s => 259 - s.2.val) (inv := fun _ => True)
        · rintro ⟨c, l⟩ _
          simp only [slot.x32_init_costs_loop2.body]
          step*
        · trivial
      · intro lnc _
        apply Std.WP.spec_bind (Pₘ := fun _ => True)
        · rw [slot.x32_init_costs_loop3]
          apply Std.loop.spec_decr_nat (measure := fun s => 30 - s.2.val) (inv := fun _ => True)
          · rintro ⟨c, s⟩ _
            simp only [slot.x32_init_costs_loop3.body]
            step*
          · trivial
        · intro dc _
          simp

theorem dp_inner_spec (cte : Array Std.U32 65536#usize) (len_cost : Array Std.U32 512#usize)
    (j : Std.Usize) (best : Std.U32) (bl bd l dd : Std.Usize) (dc : Std.U32) (top : Std.Usize)
    (hj : j.val < 65536) (htop : top.val < 65536) :
    slot.x32_dp_pass_loop0_loop0_loop0 cte len_cost j best bl bd l dd dc top ⦃ fun _ => True ⦄ := by
  rw [slot.x32_dp_pass_loop0_loop0_loop0]
  apply Std.loop.spec_decr_nat (measure := fun s => top.val + 1 - s.2.2.2.val) (inv := fun _ => True)
  · rintro ⟨b, bl, bd, l⟩ _
    simp only [slot.x32_dp_pass_loop0_loop0_loop0.body]
    step*
    all_goals repeat' (first | (split <;> step*) | scalar_tac)
  · trivial

theorem dp_mid_spec (ml md : Array Std.U16 262144#usize) (cte : Array Std.U32 65536#usize)
    (len_cost : Array Std.U32 512#usize) (dcost : Array Std.U32 32#usize)
    (j : Std.Usize) (best : Std.U32) (bl bd e lmax m l : Std.Usize) (hj : j.val < 65536) :
    slot.x32_dp_pass_loop0_loop0 ml md cte len_cost dcost j best bl bd e lmax m l ⦃ fun _ => True ⦄ := by
  rw [slot.x32_dp_pass_loop0_loop0]
  apply Std.loop.spec_decr_nat (measure := fun s => e.val - s.2.2.2.1.val) (inv := fun _ => True)
  · rintro ⟨b, bl, bd, m, l⟩ _
    simp only [slot.x32_dp_pass_loop0_loop0.body]
    step*
    all_goals repeat' (first | (split <;> step*) | scalar_tac |
      (apply Std.WP.spec_bind (dp_inner_spec _ _ _ _ _ _ _ _ _ _ hj (by scalar_tac))
       rintro ⟨_, _, _, _⟩ _
       step*))
  · trivial

@[local step]
theorem dp_pass_spec (input : Slice Std.U8) (ml md : Array Std.U16 262144#usize)
    (mstart cte : Array Std.U32 65536#usize) (chl chd : Array Std.U16 65536#usize)
    (lit_cost : Array Std.U32 256#usize) (len_cost : Array Std.U32 512#usize)
    (dcost : Array Std.U32 32#usize) (pos0 slen : Std.Usize)
    (hseg : pos0.val + slen.val ≤ input.length) (hslen : slen.val < 65536) :
    slot.x32_dp_pass input ml md mstart cte chl chd lit_cost len_cost dcost pos0 slen
      ⦃ fun _ => True ⦄ := by
  rw [slot.x32_dp_pass]
  step*
  rw [slot.x32_dp_pass_loop0]
  apply Std.loop.spec_decr_nat (measure := fun s => s.2.2.2.val) (inv := fun s => s.2.2.2.val ≤ slen.val)
  · rintro ⟨c, cl, cd, j⟩ hj
    simp only at hj
    simp only [slot.x32_dp_pass_loop0.body]
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    step*
    all_goals repeat' (first | (split <;> step*) | scalar_tac |
      (apply Std.WP.spec_bind (dp_mid_spec _ _ _ _ _ _ _ _ _ _ _ _ _ (by scalar_tac))
       rintro ⟨_, _, _⟩ _
       step*))
  · simp

@[local step]
theorem tally_spec (input : Slice Std.U8) (chl chd : Array Std.U16 65536#usize)
    (llf : Array Std.U32 286#usize) (df : Array Std.U32 32#usize) (pos0 slen : Std.Usize)
    (hseg : pos0.val + slen.val ≤ input.length) (hslen : slen.val < 65536) :
    slot.x32_tally input chl chd llf df pos0 slen ⦃ fun _ => True ⦄ := by
  rw [slot.x32_tally]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  apply Std.WP.spec_bind (Pₘ := fun _ => True)
  · rw [slot.x32_tally_loop0]
    apply Std.loop.spec_decr_nat (measure := fun s => 286 - s.2.val) (inv := fun _ => True)
    · rintro ⟨a, s⟩ _
      simp only [slot.x32_tally_loop0.body]
      step*
    · trivial
  · intro llf1 _
    apply Std.WP.spec_bind (Pₘ := fun _ => True)
    · rw [slot.x32_tally_loop1]
      apply Std.loop.spec_decr_nat (measure := fun s => 32 - s.2.val) (inv := fun _ => True)
      · rintro ⟨a, s⟩ _
        simp only [slot.x32_tally_loop1.body]
        step*
      · trivial
    · intro df1 _
      apply Std.WP.spec_bind (Pₘ := fun _ => True)
      · rw [slot.x32_tally_loop2]
        apply Std.loop.spec_decr_nat (measure := fun s => slen.val - s.2.2.val) (inv := fun _ => True)
        · rintro ⟨a, b, q⟩ _
          simp only [slot.x32_tally_loop2.body]
          step*
          all_goals repeat' (first | (split <;> step*) | scalar_tac)
        · trivial
      · rintro ⟨_, _⟩ _
        step*

@[local step]
theorem refresh_spec (llf : Array Std.U32 286#usize) (df : Array Std.U32 32#usize)
    (lit_cost : Array Std.U32 256#usize) (len_cost : Array Std.U32 512#usize)
    (dcost : Array Std.U32 32#usize) :
    slot.x32_refresh llf df lit_cost len_cost dcost ⦃ fun _ => True ⦄ := by
  rw [slot.x32_refresh]
  apply Std.WP.spec_bind (Pₘ := fun _ => True)
  · rw [slot.x32_refresh_loop0]
    apply Std.loop.spec_decr_nat (measure := fun s => 286 - s.2.val) (inv := fun _ => True)
    · rintro ⟨a, s⟩ _
      simp only [slot.x32_refresh_loop0.body]
      step*
    · trivial
  · intro lt _
    apply Std.WP.spec_bind (Pₘ := fun _ => True)
    · rw [slot.x32_refresh_loop1]
      apply Std.loop.spec_decr_nat (measure := fun s => 30 - s.1.val) (inv := fun _ => True)
      · rintro ⟨s, a⟩ _
        simp only [slot.x32_refresh_loop1.body]
        step*
      · trivial
    · intro dt _
      apply Std.WP.spec_bind (Pₘ := fun _ => True)
      · split <;> simp
      · intro dt1 _
        apply Std.WP.spec_bind (Pₘ := fun _ => True)
        · rw [slot.x32_refresh_loop2]
          apply Std.loop.spec_decr_nat (measure := fun s => 256 - s.2.val) (inv := fun _ => True)
          · rintro ⟨a, s⟩ _
            simp only [slot.x32_refresh_loop2.body]
            step*
          · trivial
        · intro lc _
          apply Std.WP.spec_bind (Pₘ := fun _ => True)
          · rw [slot.x32_refresh_loop3]
            apply Std.loop.spec_decr_nat (measure := fun s => 259 - s.2.val) (inv := fun _ => True)
            · rintro ⟨a, l⟩ _
              simp only [slot.x32_refresh_loop3.body]
              step*
            · trivial
          · intro lnc _
            apply Std.WP.spec_bind (Pₘ := fun _ => True)
            · rw [slot.x32_refresh_loop4]
              apply Std.loop.spec_decr_nat (measure := fun s => 30 - s.2.val) (inv := fun _ => True)
              · rintro ⟨a, s⟩ _
                simp only [slot.x32_refresh_loop4.body]
                step*
              · trivial
            · intro dc _
              simp

@[local step]
theorem run_passes_spec (input : Slice Std.U8) (ml md : Array Std.U16 262144#usize)
    (mstart cte : Array Std.U32 65536#usize) (chl chd : Array Std.U16 65536#usize)
    (lit_cost : Array Std.U32 256#usize) (len_cost : Array Std.U32 512#usize)
    (dcost : Array Std.U32 32#usize) (llf : Array Std.U32 286#usize) (df : Array Std.U32 32#usize)
    (pos0 slen np : Std.Usize)
    (hseg : pos0.val + slen.val ≤ input.length) (hslen : slen.val < 65536) :
    slot.x32_run_passes input ml md mstart cte chl chd lit_cost len_cost dcost llf df pos0 slen np
      ⦃ fun _ => True ⦄ := by
  rw [slot.x32_run_passes, slot.x32_run_passes_loop]
  apply Std.loop.spec_decr_nat (measure := fun s => np.val - s.2.2.2.2.2.2.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨c, cl, cd, lc, lnc, dc, lf, f, pass⟩ _
    simp only [slot.x32_run_passes_loop.body]
    step*
  · trivial

theorem verified_spec (input : Slice Std.U8) (pos d ch k blen : Std.Usize)
    (hlen : pos.val + (blen.val - k.val) ≤ input.length) (hk : k.val ≤ blen.val)
    (hb : blen.val < 65536) :
    slot.x32_verified input pos d ch k blen ⦃ fun b => b = true →
      3 ≤ ch.val ∧ ch.val ≤ 258 ∧ 1 ≤ d.val ∧ d.val ≤ 32768 ∧ d.val ≤ pos.val ∧
      k.val + ch.val ≤ blen.val ∧ Matches input (pos.val - d.val) pos.val ch.val ⦄ := by
  rw [slot.x32_verified]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  step*

theorem emit_seg_loop_spec (input : Slice Std.U8) (out0 : Slice Std.U32)
    (chl chd : Array Std.U16 65536#usize) (pos0 slen ntok0 q0 : Std.Usize)
    (hseg : pos0.val + slen.val ≤ input.length) (hslen : slen.val < 65536)
    (hout : input.length ≤ out0.length)
    (hq : q0.val ≤ slen.val) (hntok : ntok0.val ≤ pos0.val + q0.val)
    (hdec : LZ77.decode (toks out0 ntok0.val) = some ((bytes input).take (pos0.val + q0.val))) :
    slot.x32_emit_seg_loop input out0 chl chd pos0 slen ntok0 q0 ⦃ fun r =>
      r.1.val ≤ pos0.val + slen.val ∧ r.2.length = out0.length ∧
      LZ77.decode (toks r.2 r.1.val) = some ((bytes input).take (pos0.val + slen.val)) ⦄ := by
  rw [slot.x32_emit_seg_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => slen.val - s.2.2.val)
    (inv := fun s =>
      s.2.2.val ≤ slen.val ∧ s.2.1.val ≤ pos0.val + s.2.2.val ∧
      s.1.length = out0.length ∧
      LZ77.decode (toks s.1 s.2.1.val) = some ((bytes input).take (pos0.val + s.2.2.val)))
  · rintro ⟨out, ntok, q⟩ ⟨hqs, hnt, hlen, hde⟩
    simp only at hqs hnt hlen hde
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.x32_emit_seg_loop.body]
    split
    case isTrue hqlt =>
      have hntok_lt : ntok.val < out.length := by scalar_tac
      step*
      apply Std.WP.spec_bind (verified_spec input p d l q slen (by scalar_tac) (by scalar_tac) hslen)
      intro b hb
      split
      case isTrue hbt =>
        obtain ⟨hch3, hch258, hd1, hdmax, hdpos, hend, hmatch⟩ := hb hbt
        step*
        have htok : i10.val = LZ77.mkMatch d.val l.val := by
          simp only [LZ77.mkMatch, LZ77.MATCH_BASE, i10_post, i7_post, i5_post, i4_post1,
            i9_post, i8_post1, Std.UScalar.cast_val_eq]
          scalar_tac
        refine ⟨by scalar_tac, by scalar_tac,
          by rw [s_post]; simpa [Std.Slice.set_val_eq] using hlen, ?_, by scalar_tac⟩
        rw [s_post, show ntok1.val = ntok.val + 1 by scalar_tac,
          toks_update out ntok i10 hntok_lt, htok,
          show pos0.val + q1.val = p.val + l.val by scalar_tac]
        refine LZ77.valid_match (bytes input) (toks out ntok.val) p.val d.val l.val
          (by rw [show p.val = pos0.val + q.val by scalar_tac]; exact hde)
          hd1 hdpos (by simpa [LZ77.MAX_DIST] using hdmax) hch3
          (by simpa [LZ77.MAX_LEN] using hch258) (by rw [bytes_length]; scalar_tac) ?_
        intro j hj
        exact (bytes_congr input _ _ (by scalar_tac) (by scalar_tac) (hmatch j hj)).symm
      case isFalse hbf =>
        have hposlen : p.val < input.length := by scalar_tac
        step*
        have hval : i5.val = (bytes input)[p.val]! := by
          rw [bytes_getElem! input p.val hposlen, i5_post, Std.U8.cast_U32_val_eq, i4_post]
        refine ⟨by scalar_tac, by scalar_tac,
          by rw [s_post]; simpa [Std.Slice.set_val_eq] using hlen, ?_, by scalar_tac⟩
        rw [s_post, show ntok1.val = ntok.val + 1 by scalar_tac,
          toks_update out ntok i5 hntok_lt, hval,
          show pos0.val + q1.val = p.val + 1 by scalar_tac]
        exact LZ77.valid_lit (bytes input) (toks out ntok.val) p.val
          (by rw [show p.val = pos0.val + q.val by scalar_tac]; exact hde)
          (by rw [bytes_length]; scalar_tac) (by rw [← hval]; scalar_tac)
    case isFalse hge =>
      have hqe : q.val = slen.val := by scalar_tac
      refine ⟨by scalar_tac, hlen, ?_⟩
      rw [hde, hqe]
  · exact ⟨hq, hntok, rfl, hdec⟩

@[local step]
theorem g16_spec (v : Slice Std.U16) (i : Std.Usize) :
    slot.x32_g16 v i ⦃ fun r => r.val < 65536 ⦄ := by
  rw [slot.x32_g16]
  split
  · step*
  · step*

@[local step]
theorem g32_spec (v : Slice Std.U32) (i : Std.Usize) :
    slot.x32_g32 v i ⦃ fun _ => True ⦄ := by
  rw [slot.x32_g32]
  (try simp only [lift])
  (try step*)
  all_goals repeat' (first
    | trivial
    | scalar_tac
    | (split <;> try step*)
    | (simp only [Prod.forall]; intros; try step*)
    | (intro _ _; try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True) <;> try step*)
    | (cases ‹_ × _›; try step*))

@[local step]
theorem save_seg_loop0_spec (mstart : Array Std.U32 65536#usize) (chl chd : Array Std.U16 65536#usize) (slen : Std.Usize) (gms : alloc.vec.Vec Std.U32) (gchl gchd : alloc.vec.Vec Std.U16) (base : Std.U32) (k : Std.Usize) :
    slot.x32_save_seg_loop0 mstart chl chd slen gms gchl gchd base k ⦃ fun _ => True ⦄ := by
  rw [slot.x32_save_seg_loop0]
  apply Std.loop.spec_decr_nat (measure := fun s => slen.val - s.2.2.2.val) (inv := fun _ => True)
  · rintro ⟨gms, gchl, gchd, k⟩ _
    simp only [slot.x32_save_seg_loop0.body, lift]
    (try step*)
    all_goals repeat' (first
      | trivial
      | scalar_tac
      | (split <;> try step*)
      | (simp only [Prod.forall]; intros; try step*)
      | (intro _ _; try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True) <;> try step*)
      | (cases ‹_ × _›; try step*))
  · first | trivial | simp

@[local step]
theorem save_seg_loop1_spec (ml md : Array Std.U16 262144#usize) (gml gmd : alloc.vec.Vec Std.U16) (e m : Std.Usize) :
    slot.x32_save_seg_loop1 ml md gml gmd e m ⦃ fun _ => True ⦄ := by
  rw [slot.x32_save_seg_loop1]
  apply Std.loop.spec_decr_nat (measure := fun s => e.val - s.2.2.val) (inv := fun _ => True)
  · rintro ⟨gml, gmd, m⟩ _
    simp only [slot.x32_save_seg_loop1.body, lift]
    (try step*)
    all_goals repeat' (first
      | trivial
      | scalar_tac
      | (split <;> try step*)
      | (simp only [Prod.forall]; intros; try step*)
      | (intro _ _; try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True) <;> try step*)
      | (cases ‹_ × _›; try step*))
  · first | trivial | simp

@[local step]
theorem save_seg_spec (ml md : Array Std.U16 262144#usize) (mstart : Array Std.U32 65536#usize) (chl chd : Array Std.U16 65536#usize) (slen : Std.Usize) (gml gmd : alloc.vec.Vec Std.U16) (gms : alloc.vec.Vec Std.U32) (gchl gchd : alloc.vec.Vec Std.U16) :
    slot.x32_save_seg ml md mstart chl chd slen gml gmd gms gchl gchd ⦃ fun _ => True ⦄ := by
  rw [slot.x32_save_seg]
  (try simp only [lift])
  (try step*)
  all_goals repeat' (first
    | trivial
    | scalar_tac
    | (split <;> try step*)
    | (simp only [Prod.forall]; intros; try step*)
    | (intro _ _; try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True) <;> try step*)
    | (cases ‹_ × _›; try step*))

@[local step]
theorem sort_insert_loop_spec (f idx : Array Std.U32 512#usize) (fs : Std.U32) (j : Std.Usize) :
    slot.x32_sort_insert_loop f idx fs j ⦃ fun _ => True ⦄ := by
  rw [slot.x32_sort_insert_loop]
  apply Std.loop.spec_decr_nat (measure := fun s => s.2.val) (inv := fun _ => True)
  · rintro ⟨idx, j⟩ _
    simp only [slot.x32_sort_insert_loop.body, lift]
    (try step*)
    all_goals repeat' (first
      | trivial
      | scalar_tac
      | (split <;> try step*)
      | (simp only [Prod.forall]; intros; try step*)
      | (intro _ _; try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True) <;> try step*)
      | (cases ‹_ × _›; try step*))
  · first | trivial | simp

@[local step]
theorem sort_insert_spec (f idx : Array Std.U32 512#usize) (m s : Std.Usize) :
    slot.x32_sort_insert f idx m s ⦃ fun _ => True ⦄ := by
  rw [slot.x32_sort_insert]
  (try simp only [lift])
  (try step*)
  all_goals repeat' (first
    | trivial
    | scalar_tac
    | (split <;> try step*)
    | (simp only [Prod.forall]; intros; try step*)
    | (intro _ _; try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True) <;> try step*)
    | (cases ‹_ × _›; try step*))

@[local step]
theorem mk_phase1_loop_spec (a : Array Std.U32 512#usize) (m root leaf next : Std.Usize) (hm : 2 ≤ m.val) :
    slot.x32_mk_phase1_loop a m root leaf next ⦃ fun _ => True ⦄ := by
  rw [slot.x32_mk_phase1_loop]
  apply Std.loop.spec_decr_nat (measure := fun s => 512 - s.2.2.2.val) (inv := fun _ => True)
  · rintro ⟨a, root, leaf, next⟩ _
    simp only [slot.x32_mk_phase1_loop.body, lift]
    (try step*)
    all_goals repeat' (first
      | trivial
      | scalar_tac
      | (split <;> try step*)
      | (simp only [Prod.forall]; intros; try step*)
      | (intro _ _; try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True) <;> try step*)
      | (cases ‹_ × _›; try step*))
  · first | trivial | simp

@[local step]
theorem mk_phase1_spec (a : Array Std.U32 512#usize) (m : Std.Usize) (hm : 2 ≤ m.val) :
    slot.x32_mk_phase1 a m ⦃ fun _ => True ⦄ := by
  rw [slot.x32_mk_phase1]
  (try simp only [lift])
  (try step*)
  all_goals repeat' (first
    | trivial
    | scalar_tac
    | (split <;> try step*)
    | (simp only [Prod.forall]; intros; try step*)
    | (intro _ _; try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True) <;> try step*)
    | (cases ‹_ × _›; try step*))

@[local step]
theorem mk_phase2_loop_spec (a : Array Std.U32 512#usize) (next : Std.Usize) :
    slot.x32_mk_phase2_loop a next ⦃ fun _ => True ⦄ := by
  rw [slot.x32_mk_phase2_loop]
  apply Std.loop.spec_decr_nat (measure := fun s => s.2.val) (inv := fun _ => True)
  · rintro ⟨a, next⟩ _
    simp only [slot.x32_mk_phase2_loop.body, lift]
    (try step*)
    all_goals repeat' (first
      | trivial
      | scalar_tac
      | (split <;> try step*)
      | (simp only [Prod.forall]; intros; try step*)
      | (intro _ _; try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True) <;> try step*)
      | (cases ‹_ × _›; try step*))
  · first | trivial | simp

@[local step]
theorem mk_phase2_spec (a : Array Std.U32 512#usize) (m : Std.Usize) (hm : 2 ≤ m.val) :
    slot.x32_mk_phase2 a m ⦃ fun _ => True ⦄ := by
  rw [slot.x32_mk_phase2]
  (try simp only [lift])
  (try step*)
  all_goals repeat' (first
    | trivial
    | scalar_tac
    | (split <;> try step*)
    | (simp only [Prod.forall]; intros; try step*)
    | (intro _ _; try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True) <;> try step*)
    | (cases ‹_ × _›; try step*))

@[local step]
theorem mk_used_loop_spec (a : Array Std.U32 512#usize) (depth : Std.U32) (r used : Std.Usize) :
    slot.x32_mk_used_loop a depth r used ⦃ fun _ => True ⦄ := by
  rw [slot.x32_mk_used_loop]
  apply Std.loop.spec_decr_nat (measure := fun s => s.1.val) (inv := fun _ => True)
  · rintro ⟨r, used⟩ _
    simp only [slot.x32_mk_used_loop.body, lift]
    (try step*)
    all_goals repeat' (first
      | trivial
      | scalar_tac
      | (split <;> try step*)
      | (simp only [Prod.forall]; intros; try step*)
      | (intro _ _; try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True) <;> try step*)
      | (cases ‹_ × _›; try step*))
  · first | trivial | simp

@[local step]
theorem mk_used_spec (a : Array Std.U32 512#usize) (r0 : Std.Usize) (depth : Std.U32) :
    slot.x32_mk_used a r0 depth ⦃ fun _ => True ⦄ := by
  rw [slot.x32_mk_used]
  (try simp only [lift])
  (try step*)
  all_goals repeat' (first
    | trivial
    | scalar_tac
    | (split <;> try step*)
    | (simp only [Prod.forall]; intros; try step*)
    | (intro _ _; try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True) <;> try step*)
    | (cases ‹_ × _›; try step*))

@[local step]
theorem mk_assign_loop_spec (a : Array Std.U32 512#usize) (used : Std.Usize) (depth : Std.U32) (nx k : Std.Usize) :
    slot.x32_mk_assign_loop a used depth nx k ⦃ fun _ => True ⦄ := by
  rw [slot.x32_mk_assign_loop]
  apply Std.loop.spec_decr_nat (measure := fun s => s.2.2.val) (inv := fun _ => True)
  · rintro ⟨a, nx, k⟩ _
    simp only [slot.x32_mk_assign_loop.body, lift]
    (try step*)
    all_goals repeat' (first
      | trivial
      | scalar_tac
      | (split <;> try step*)
      | (simp only [Prod.forall]; intros; try step*)
      | (intro _ _; try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True) <;> try step*)
      | (cases ‹_ × _›; try step*))
  · first | trivial | simp

@[local step]
theorem mk_assign_spec (a : Array Std.U32 512#usize) (nx0 avbl used : Std.Usize) (depth : Std.U32) :
    slot.x32_mk_assign a nx0 avbl used depth ⦃ fun _ => True ⦄ := by
  rw [slot.x32_mk_assign]
  (try simp only [lift])
  (try step*)
  all_goals repeat' (first
    | trivial
    | scalar_tac
    | (split <;> try step*)
    | (simp only [Prod.forall]; intros; try step*)
    | (intro _ _; try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True) <;> try step*)
    | (cases ‹_ × _›; try step*))

@[local step]
theorem mk_phase3_loop_spec (a : Array Std.U32 512#usize) (avbl : Std.Usize) (depth : Std.U32) (r nx fuel : Std.Usize) :
    slot.x32_mk_phase3_loop a avbl depth r nx fuel ⦃ fun _ => True ⦄ := by
  rw [slot.x32_mk_phase3_loop]
  apply Std.loop.spec_decr_nat (measure := fun s => 64 - s.2.2.2.2.2.val) (inv := fun _ => True)
  · rintro ⟨a, avbl, depth, r, nx, fuel⟩ _
    simp only [slot.x32_mk_phase3_loop.body, lift]
    (try step*)
    all_goals repeat' (first
      | trivial
      | scalar_tac
      | (split <;> try step*)
      | (simp only [Prod.forall]; intros; try step*)
      | (intro _ _; try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True) <;> try step*)
      | (cases ‹_ × _›; try step*))
  · first | trivial | simp

@[local step]
theorem mk_phase3_spec (a : Array Std.U32 512#usize) (m : Std.Usize) (hm : 2 ≤ m.val) :
    slot.x32_mk_phase3 a m ⦃ fun _ => True ⦄ := by
  rw [slot.x32_mk_phase3]
  (try simp only [lift])
  (try step*)
  all_goals repeat' (first
    | trivial
    | scalar_tac
    | (split <;> try step*)
    | (simp only [Prod.forall]; intros; try step*)
    | (intro _ _; try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True) <;> try step*)
    | (cases ‹_ × _›; try step*))

@[local step]
theorem huff_loop0_spec (f : Array Std.U32 512#usize) (ns : Std.Usize) (lens idx : Array Std.U32 512#usize) (m s : Std.Usize) (hms : m.val ≤ s.val) :
    slot.x32_huff_loop0 f ns lens idx m s ⦃ fun _ => True ⦄ := by
  rw [slot.x32_huff_loop0]
  apply Std.loop.spec_decr_nat (measure := fun s => 512 - s.2.2.2.val) (inv := fun s => s.2.2.1.val ≤ s.2.2.2.val)
  · rintro ⟨lens, idx, m, s⟩ hms
    simp only at hms
    simp only [slot.x32_huff_loop0.body, lift]
    (try step*)
    all_goals repeat' (first
      | trivial
      | scalar_tac
      | (split <;> try step*)
      | (simp only [Prod.forall]; intros; try step*)
      | (intro _ _; try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True) <;> try step*)
      | (cases ‹_ × _›; try step*))
  · first | trivial | simp

@[local step]
theorem huff_loop1_spec (f idx a : Array Std.U32 512#usize) (m i : Std.Usize) :
    slot.x32_huff_loop1 f idx a m i ⦃ fun _ => True ⦄ := by
  rw [slot.x32_huff_loop1]
  apply Std.loop.spec_decr_nat (measure := fun s => m.val - s.2.val) (inv := fun _ => True)
  · rintro ⟨a, i⟩ _
    simp only [slot.x32_huff_loop1.body, lift]
    (try step*)
    all_goals repeat' (first
      | trivial
      | scalar_tac
      | (split <;> try step*)
      | (simp only [Prod.forall]; intros; try step*)
      | (intro _ _; try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True) <;> try step*)
      | (cases ‹_ × _›; try step*))
  · first | trivial | simp

@[local step]
theorem huff_loop2_spec (lens idx a : Array Std.U32 512#usize) (m i : Std.Usize) :
    slot.x32_huff_loop2 lens idx a m i ⦃ fun _ => True ⦄ := by
  rw [slot.x32_huff_loop2]
  apply Std.loop.spec_decr_nat (measure := fun s => m.val - s.2.val) (inv := fun _ => True)
  · rintro ⟨lens, i⟩ _
    simp only [slot.x32_huff_loop2.body, lift]
    (try step*)
    all_goals repeat' (first
      | trivial
      | scalar_tac
      | (split <;> try step*)
      | (simp only [Prod.forall]; intros; try step*)
      | (intro _ _; try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True) <;> try step*)
      | (cases ‹_ × _›; try step*))
  · first | trivial | simp

@[local step]
theorem huff_spec (f : Array Std.U32 512#usize) (ns : Std.Usize) (lens : Array Std.U32 512#usize) :
    slot.x32_huff f ns lens ⦃ fun _ => True ⦄ := by
  rw [slot.x32_huff]
  (try simp only [lift])
  (try step*)
  all_goals repeat' (first
    | trivial
    | scalar_tac
    | (split <;> try step*)
    | (simp only [Prod.forall]; intros; try step*)
    | (intro _ _; try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True) <;> try step*)
    | (cases ‹_ × _›; try step*))

@[local step]
theorem push_cost_spec (costs : alloc.vec.Vec Std.U32) (len unused extra : Std.U32) :
    slot.x32_push_cost costs len unused extra ⦃ fun _ => True ⦄ := by
  rw [slot.x32_push_cost]
  (try simp only [lift])
  (try step*)
  all_goals repeat' (first
    | trivial
    | scalar_tac
    | (split <;> try step*)
    | (simp only [Prod.forall]; intros; try step*)
    | (intro _ _; try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True) <;> try step*)
    | (cases ‹_ × _›; try step*))

@[local step]
theorem push_block_loop0_spec (costs : alloc.vec.Vec Std.U32) (ll : Array Std.U32 512#usize) (s : Std.Usize) :
    slot.x32_push_block_loop0 costs ll s ⦃ fun _ => True ⦄ := by
  rw [slot.x32_push_block_loop0]
  apply Std.loop.spec_decr_nat (measure := fun s => 256 - s.2.val) (inv := fun _ => True)
  · rintro ⟨costs, s⟩ _
    simp only [slot.x32_push_block_loop0.body, lift]
    (try step*)
    all_goals repeat' (first
      | trivial
      | scalar_tac
      | (split <;> try step*)
      | (simp only [Prod.forall]; intros; try step*)
      | (intro _ _; try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True) <;> try step*)
      | (cases ‹_ × _›; try step*))
  · first | trivial | simp

@[local step]
theorem push_block_loop1_spec (costs : alloc.vec.Vec Std.U32) (ll : Array Std.U32 512#usize) (s : Std.Usize) :
    slot.x32_push_block_loop1 costs ll s ⦃ fun _ => True ⦄ := by
  rw [slot.x32_push_block_loop1]
  apply Std.loop.spec_decr_nat (measure := fun s => 259 - s.2.val) (inv := fun _ => True)
  · rintro ⟨costs, s⟩ _
    simp only [slot.x32_push_block_loop1.body, lift]
    (try step*)
    all_goals repeat' (first
      | trivial
      | scalar_tac
      | (split <;> try step*)
      | (simp only [Prod.forall]; intros; try step*)
      | (intro _ _; try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True) <;> try step*)
      | (cases ‹_ × _›; try step*))
  · first | trivial | simp

@[local step]
theorem push_block_loop2_spec (costs : alloc.vec.Vec Std.U32) (dl : Array Std.U32 512#usize) (s : Std.Usize) :
    slot.x32_push_block_loop2 costs dl s ⦃ fun _ => True ⦄ := by
  rw [slot.x32_push_block_loop2]
  apply Std.loop.spec_decr_nat (measure := fun s => 30 - s.2.val) (inv := fun _ => True)
  · rintro ⟨costs, s⟩ _
    simp only [slot.x32_push_block_loop2.body, lift]
    (try step*)
    all_goals repeat' (first
      | trivial
      | scalar_tac
      | (split <;> try step*)
      | (simp only [Prod.forall]; intros; try step*)
      | (intro _ _; try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True) <;> try step*)
      | (cases ‹_ × _›; try step*))
  · first | trivial | simp

@[local step]
theorem push_block_loop3_spec (llf df : Array Std.U32 512#usize) (s : Std.Usize) :
    slot.x32_push_block_loop3 llf df s ⦃ fun _ => True ⦄ := by
  rw [slot.x32_push_block_loop3]
  apply Std.loop.spec_decr_nat (measure := fun s => 512 - s.2.2.val) (inv := fun _ => True)
  · rintro ⟨llf, df, s⟩ _
    simp only [slot.x32_push_block_loop3.body, lift]
    (try step*)
    all_goals repeat' (first
      | trivial
      | scalar_tac
      | (split <;> try step*)
      | (simp only [Prod.forall]; intros; try step*)
      | (intro _ _; try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True) <;> try step*)
      | (cases ‹_ × _›; try step*))
  · first | trivial | simp

@[local step]
theorem push_block_spec (llf df : Array Std.U32 512#usize) (bs : Std.Usize) (bstart costs : alloc.vec.Vec Std.U32) :
    slot.x32_push_block llf df bs bstart costs ⦃ fun _ => True ⦄ := by
  rw [slot.x32_push_block]
  (try simp only [lift])
  (try step*)
  all_goals repeat' (first
    | trivial
    | scalar_tac
    | (split <;> try step*)
    | (simp only [Prod.forall]; intros; try step*)
    | (intro _ _; try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True) <;> try step*)
    | (cases ‹_ × _›; try step*))

set_option maxHeartbeats 8000000 in
@[local step]
theorem blk_costs_loop_spec (input : Slice Std.U8) (gchl gchd : Slice Std.U16) (bstart costs : alloc.vec.Vec Std.U32) (n : Std.Usize) (llf df : Array Std.U32 512#usize) (q t bs : Std.Usize) (hn : n.val = input.length) :
    slot.x32_blk_costs_loop input gchl gchd bstart costs n llf df q t bs ⦃ fun _ => True ⦄ := by
  rw [slot.x32_blk_costs_loop]
  apply Std.loop.spec_decr_nat (measure := fun s => n.val - s.2.2.2.2.1.val) (inv := fun _ => True)
  · rintro ⟨bstart, costs, llf, df, q, t, bs⟩ _
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.x32_blk_costs_loop.body, lift]
    step*
    all_goals repeat' (first | (split <;> step*) | scalar_tac | (casesm _ × _ <;> step*))
  · trivial

@[local step]
theorem blk_costs_spec (input : Slice Std.U8) (gchl gchd : Slice Std.U16) (bstart costs : alloc.vec.Vec Std.U32) :
    slot.x32_blk_costs input gchl gchd bstart costs ⦃ fun _ => True ⦄ := by
  rw [slot.x32_blk_costs]
  (try simp only [lift])
  (try step*)
  all_goals repeat' (first
    | trivial
    | scalar_tac
    | (split <;> try step*)
    | (simp only [Prod.forall]; intros; try step*)
    | (intro _ _; try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True) <;> try step*)
    | (cases ‹_ × _›; try step*))

@[local step]
theorem find_blk_loop_spec (bstart : Slice Std.U32) (p b : Std.Usize) :
    slot.x32_find_blk_loop bstart p b ⦃ fun _ => True ⦄ := by
  rw [slot.x32_find_blk_loop]
  apply Std.loop.spec_decr_nat (measure := fun s => s.val) (inv := fun _ => True)
  · intro b _
    simp only [slot.x32_find_blk_loop.body, lift]
    (try step*)
    all_goals repeat' (first
      | trivial
      | scalar_tac
      | (split <;> try step*)
      | (simp only [Prod.forall]; intros; try step*)
      | (intro _ _; try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True) <;> try step*)
      | (cases ‹_ × _›; try step*))
  · trivial

@[local step]
theorem find_blk_spec (bstart : Slice Std.U32) (p : Std.Usize) :
    slot.x32_find_blk bstart p ⦃ fun _ => True ⦄ := by
  rw [slot.x32_find_blk]
  (try simp only [lift])
  (try step*)
  all_goals repeat' (first
    | trivial
    | scalar_tac
    | (split <;> try step*)
    | (simp only [Prod.forall]; intros; try step*)
    | (intro _ _; try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True) <;> try step*)
    | (cases ‹_ × _›; try step*))

theorem dp_blk_inner_spec (costs : Slice Std.U32) (cte : Array Std.U32 65536#usize)
    (j cb : Std.Usize) (best : Std.U32) (bl bd l dd : Std.Usize) (dc : Std.U32) (top : Std.Usize)
    (hj : j.val < 65536) (htop : top.val < 65536) :
    slot.x32_dp_blk_loop0_loop0_loop0 costs cte j cb best bl bd l dd dc top ⦃ fun _ => True ⦄ := by
  rw [slot.x32_dp_blk_loop0_loop0_loop0]
  apply Std.loop.spec_decr_nat (measure := fun s => top.val + 1 - s.2.2.2.val) (inv := fun _ => True)
  · rintro ⟨b, bl, bd, l⟩ _
    simp only [slot.x32_dp_blk_loop0_loop0_loop0.body, lift]
    step*
    all_goals repeat' (first | (split <;> step*) | scalar_tac)
  · trivial

theorem dp_blk_mid_spec (gml gmd : Slice Std.U16) (costs : Slice Std.U32)
    (cte : Array Std.U32 65536#usize) (j cb : Std.Usize) (best : Std.U32)
    (bl bd e lmax m l : Std.Usize) (hj : j.val < 65536) :
    slot.x32_dp_blk_loop0_loop0 gml gmd costs cte j cb best bl bd e lmax m l ⦃ fun _ => True ⦄ := by
  rw [slot.x32_dp_blk_loop0_loop0]
  apply Std.loop.spec_decr_nat (measure := fun s => e.val - s.2.2.2.1.val) (inv := fun _ => True)
  · rintro ⟨b, bl, bd, m, l⟩ _
    simp only [slot.x32_dp_blk_loop0_loop0.body, lift]
    step*
    all_goals repeat' (first | (split <;> step*) | scalar_tac |
      (apply Std.WP.spec_bind (dp_blk_inner_spec _ _ _ _ _ _ _ _ _ _ _ hj (by scalar_tac))
       rintro ⟨_, _, _, _⟩ _
       step*))
  · trivial

@[local step]
theorem dp_blk_spec (input : Slice Std.U8) (gml gmd : Slice Std.U16) (gms costs bstart : Slice Std.U32)
    (cte : Array Std.U32 65536#usize) (chl chd : Array Std.U16 65536#usize) (pos0 slen b0 : Std.Usize)
    (hseg : pos0.val + slen.val ≤ input.length) (hslen : slen.val < 65536) :
    slot.x32_dp_blk input gml gmd gms costs bstart cte chl chd pos0 slen b0 ⦃ fun _ => True ⦄ := by
  rw [slot.x32_dp_blk]
  step*
  rw [slot.x32_dp_blk_loop0]
  apply Std.loop.spec_decr_nat (measure := fun s => s.2.2.2.2.val) (inv := fun s => s.2.2.2.2.val ≤ slen.val)
  · rintro ⟨c, cl, cd, b, j⟩ hj
    simp only at hj
    simp only [slot.x32_dp_blk_loop0.body, lift]
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    step*
    all_goals repeat' (first | (split <;> step*) | scalar_tac |
      (apply Std.WP.spec_bind (dp_blk_mid_spec _ _ _ _ _ _ _ _ _ _ _ _ _ (by scalar_tac))
       rintro ⟨_, _, _⟩ _
       step*))
  · simp

@[local step]
theorem put_path_loop_spec (chl chd : Array Std.U16 65536#usize) (gchl gchd : Slice Std.U16) (pos0 slen k : Std.Usize) :
    slot.x32_put_path_loop chl chd gchl gchd pos0 slen k ⦃ fun _ => True ⦄ := by
  rw [slot.x32_put_path_loop]
  apply Std.loop.spec_decr_nat (measure := fun s => slen.val - s.2.2.val) (inv := fun _ => True)
  · rintro ⟨gchl, gchd, k⟩ _
    simp only [slot.x32_put_path_loop.body, lift]
    (try step*)
    all_goals repeat' (first
      | trivial
      | scalar_tac
      | (split <;> try step*)
      | (simp only [Prod.forall]; intros; try step*)
      | (intro _ _; try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True) <;> try step*)
      | (cases ‹_ × _›; try step*))
  · first | trivial | simp

@[local step]
theorem put_path_spec (chl chd : Array Std.U16 65536#usize) (gchl gchd : Slice Std.U16) (pos0 slen : Std.Usize) :
    slot.x32_put_path chl chd gchl gchd pos0 slen ⦃ fun _ => True ⦄ := by
  rw [slot.x32_put_path]
  (try simp only [lift])
  (try step*)
  all_goals repeat' (first
    | trivial
    | scalar_tac
    | (split <;> try step*)
    | (simp only [Prod.forall]; intros; try step*)
    | (intro _ _; try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True) <;> try step*)
    | (cases ‹_ × _›; try step*))

@[local step]
theorem get_path_loop_spec (gchl gchd : Slice Std.U16) (chl chd : Array Std.U16 65536#usize) (pos0 slen k : Std.Usize) :
    slot.x32_get_path_loop gchl gchd chl chd pos0 slen k ⦃ fun _ => True ⦄ := by
  rw [slot.x32_get_path_loop]
  apply Std.loop.spec_decr_nat (measure := fun s => slen.val - s.2.2.val) (inv := fun _ => True)
  · rintro ⟨chl, chd, k⟩ _
    simp only [slot.x32_get_path_loop.body, lift]
    (try step*)
    all_goals repeat' (first
      | trivial
      | scalar_tac
      | (split <;> try step*)
      | (simp only [Prod.forall]; intros; try step*)
      | (intro _ _; try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True) <;> try step*)
      | (cases ‹_ × _›; try step*))
  · first | trivial | simp

@[local step]
theorem get_path_spec (gchl gchd : Slice Std.U16) (chl chd : Array Std.U16 65536#usize) (pos0 slen : Std.Usize) :
    slot.x32_get_path gchl gchd chl chd pos0 slen ⦃ fun _ => True ⦄ := by
  rw [slot.x32_get_path]
  (try simp only [lift])
  (try step*)
  all_goals repeat' (first
    | trivial
    | scalar_tac
    | (split <;> try step*)
    | (simp only [Prod.forall]; intros; try step*)
    | (intro _ _; try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True) <;> try step*)
    | (cases ‹_ × _›; try step*))

theorem blk_pass_loop_spec (input : Slice Std.U8) (gml gmd : Slice Std.U16) (gms costs bstart : Slice Std.U32)
    (cte : Array Std.U32 65536#usize) (chl chd : Array Std.U16 65536#usize) (gchl gchd : Slice Std.U16)
    (seg n pos0 : Std.Usize) (hn : n.val = input.length) (hseg : 1 ≤ seg.val ∧ seg.val ≤ 32768) :
    slot.x32_blk_pass_loop input gml gmd gms costs bstart cte chl chd gchl gchd seg n pos0 ⦃ fun _ => True ⦄ := by
  rw [slot.x32_blk_pass_loop]
  apply Std.loop.spec_decr_nat (measure := fun s => n.val - s.2.2.2.2.2.val) (inv := fun _ => True)
  · rintro ⟨c, cl, cd, gl, gd, p0⟩ _
    simp only [slot.x32_blk_pass_loop.body, lift]
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    split
    case isTrue hlt =>
      step*
      apply Std.WP.spec_bind (Pₘ := fun (slen : Std.Usize) =>
        slen.val ≤ 32768 ∧ slen.val ≤ rest.val ∧ 1 ≤ slen.val)
      · split <;> simp only [Std.WP.spec_ok] <;> scalar_tac
      intro slen ⟨hb1, hb2, hb3⟩
      step*
      all_goals scalar_tac
    case isFalse hge => step*
  · trivial

@[local step]
theorem blk_pass_spec (input : Slice Std.U8) (gml gmd : Slice Std.U16) (gms costs bstart : Slice Std.U32)
    (cte : Array Std.U32 65536#usize) (chl chd : Array Std.U16 65536#usize) (gchl gchd : Slice Std.U16)
    (seg : Std.Usize) (hseg : 1 ≤ seg.val ∧ seg.val ≤ 32768) :
    slot.x32_blk_pass input gml gmd gms costs bstart cte chl chd gchl gchd seg ⦃ fun _ => True ⦄ := by
  rw [slot.x32_blk_pass]
  exact blk_pass_loop_spec input gml gmd gms costs bstart cte chl chd gchl gchd seg _ 0#usize (by simp) hseg

theorem xb_parse_loop0_spec (input : Slice Std.U8) (n : Std.Usize)
    (head4 head3 prev : Array Std.U32 65536#usize) (ml md : Array Std.U16 262144#usize)
    (mstart cte : Array Std.U32 65536#usize) (chl chd : Array Std.U16 65536#usize)
    (lit_cost : Array Std.U32 256#usize) (len_cost : Array Std.U32 512#usize)
    (dcost : Array Std.U32 32#usize) (llf : Array Std.U32 286#usize) (df : Array Std.U32 32#usize)
    (gml gmd : alloc.vec.Vec Std.U16) (gms : alloc.vec.Vec Std.U32) (gchl gchd : alloc.vec.Vec Std.U16)
    (seg pos00 : Std.Usize)
    (hn : n.val = input.length) (hseg : 1 ≤ seg.val ∧ seg.val ≤ 32768) :
    slot.x32b_parse_loop0 input n head4 head3 prev ml md mstart cte chl chd lit_cost len_cost dcost
        llf df gml gmd gms gchl gchd seg pos00 ⦃ fun _ => True ⦄ := by
  rw [slot.x32b_parse_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun s => n.val - s.2.2.2.2.2.2.2.2.2.2.2.2.2.2.2.2.2.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨h4, h3, pv, ml, md, ms, cte, chl, chd, lc, lnc, dc, llf, df, gml, gmd, gms, gchl, gchd, pos0⟩ _
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.x32b_parse_loop0.body, lift]
    split
    case isTrue hlt =>
      step*
      apply Std.WP.spec_bind (Pₘ := fun (slen : Std.Usize) =>
        slen.val ≤ 32768 ∧ slen.val ≤ rest.val ∧ 1 ≤ slen.val)
      · split <;> simp only [Std.WP.spec_ok] <;> scalar_tac
      intro slen ⟨hb1, hb2, hb3⟩
      apply Std.WP.spec_bind (find_seg_spec input h4 h3 pv ml md ms pos0 slen _ _ (by scalar_tac))
      rintro ⟨h41, h31, pv1, ml1, md1, ms1⟩ _
      apply Std.WP.spec_bind (Pₘ := fun _ => True)
      · split
        · exact Std.WP.spec_mono (init_costs_spec input lc lnc dc pos0 slen (by scalar_tac)) (by simp)
        · simp
      rintro ⟨lc1, lnc1, dc1⟩ _
      apply Std.WP.spec_bind (Pₘ := fun _ => True)
      · split <;> simp
      intro np _
      apply Std.WP.spec_bind (run_passes_spec input ml1 md1 ms1 cte chl chd lc1 lnc1 dc1 llf df pos0
        slen np (by scalar_tac) (by scalar_tac))
      rintro ⟨cte1, chl1, chd1, lc2, lnc2, dc2, llf1, df1⟩ _
      apply Std.WP.spec_bind (save_seg_spec ml1 md1 ms1 chl1 chd1 slen gml gmd gms gchl gchd)
      rintro ⟨gml1, gmd1, gms1, gchl1, gchd1⟩ _
      step*
      scalar_tac
    case isFalse hge => step*
  · trivial

theorem xb_parse_loop1_spec (input : Slice Std.U8) (cte : Array Std.U32 65536#usize)
    (chl chd : Array Std.U16 65536#usize) (gml gmd : alloc.vec.Vec Std.U16) (gms : alloc.vec.Vec Std.U32)
    (gchl gchd : alloc.vec.Vec Std.U16) (seg it : Std.Usize) (hseg : 1 ≤ seg.val ∧ seg.val ≤ 32768) :
    slot.x32b_parse_loop1 input cte chl chd gml gmd gms gchl gchd seg it ⦃ fun _ => True ⦄ := by
  rw [slot.x32b_parse_loop1]
  apply Std.loop.spec_decr_nat (measure := fun s => slot.XB_BLK.val - s.2.2.2.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨c, cl, cd, gl, gd, it⟩ _
    simp only [slot.x32b_parse_loop1.body, lift]
    split
    case isTrue hlt =>
      apply Std.WP.spec_bind (blk_costs_spec input _ _ _ _)
      rintro ⟨bstart, costs⟩ _
      step*
      apply Std.WP.spec_bind (blk_pass_spec input _ _ _ _ _ c cl cd _ _ seg hseg)
      rintro ⟨c1, cl1, cd1, s9, s10⟩ _
      step*
      try scalar_tac
    case isFalse hge => step*
  · trivial

theorem xb_parse_loop2_spec (input : Slice Std.U8) (out0 : Slice Std.U32) (n : Std.Usize)
    (chl chd : Array Std.U16 65536#usize) (gchl gchd : alloc.vec.Vec Std.U16)
    (seg pos00 ntok0 : Std.Usize)
    (hn : n.val = input.length) (hout : input.length ≤ out0.length)
    (hseg : 1 ≤ seg.val ∧ seg.val ≤ 32768)
    (hpos : pos00.val ≤ n.val) (hntok : ntok0.val ≤ pos00.val)
    (hdec : LZ77.decode (toks out0 ntok0.val) = some ((bytes input).take pos00.val)) :
    slot.x32b_parse_loop2 input out0 n chl chd gchl gchd seg pos00 ntok0
      ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out0.length ∧
        LZ77.decode (toks r.2 r.1.val) = some (bytes input) ⦄ := by
  rw [slot.x32b_parse_loop2]
  apply Std.loop.spec_decr_nat
    (measure := fun s => n.val - s.2.2.2.1.val)
    (inv := fun s =>
      s.2.2.2.1.val ≤ n.val ∧ s.2.2.2.2.val ≤ s.2.2.2.1.val ∧ s.1.length = out0.length ∧
      LZ77.decode (toks s.1 s.2.2.2.2.val) = some ((bytes input).take s.2.2.2.1.val))
  · rintro ⟨out, chl, chd, pos0, ntok⟩ ⟨hp, hnt, hlen, hde⟩
    simp only at hp hnt hlen hde
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.x32b_parse_loop2.body, lift]
    split
    case isTrue hlt =>
      step*
      apply Std.WP.spec_bind (Pₘ := fun (slen : Std.Usize) =>
        slen.val ≤ 32768 ∧ slen.val ≤ rest.val ∧ 1 ≤ slen.val)
      · split <;> simp only [Std.WP.spec_ok] <;> scalar_tac
      intro slen ⟨hb1, hb2, hb3⟩
      apply Std.WP.spec_bind (get_path_spec _ _ chl chd pos0 slen)
      rintro ⟨chl1, chd1⟩ _
      apply Std.WP.spec_bind (emit_seg_loop_spec input out chl1 chd1 pos0 slen ntok 0#usize
        (by scalar_tac) (by scalar_tac) (by scalar_tac) (by scalar_tac) (by scalar_tac)
        (by simpa using hde))
      rintro ⟨ntok1, out1⟩ ⟨hnt1, hlen1, hde1⟩
      simp only at hnt1 hlen1 hde1
      step*
      refine ⟨by scalar_tac, by scalar_tac, hlen1.trans hlen, ?_, by scalar_tac⟩
      rw [hde1, show pos01.val = pos0.val + slen.val by scalar_tac]
    case isFalse hge =>
      have hpn : pos0.val = n.val := by scalar_tac
      refine ⟨by scalar_tac, hlen, ?_⟩
      rw [hde, hpn, hn]
      simp
  · exact ⟨hpos, hntok, rfl, hdec⟩

theorem xb_parse_spec (input : Slice Std.U8) (out : Slice Std.U32)
    (hlen : input.length ≤ out.length) :
    slot.x32b_parse input out ⦃ fun r =>
      r.1.val ≤ input.length ∧
      r.2.length = out.length ∧
      LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
  rw [slot.x32b_parse]
  apply Std.WP.spec_bind (Pₘ := fun (seg : Std.Usize) => 1 ≤ seg.val ∧ seg.val ≤ 32768)
  · split
    · simp
    · split <;> simp only [Std.WP.spec_ok] <;> scalar_tac
  · intro seg hseg
    apply Std.WP.spec_bind (xb_parse_loop0_spec input (Std.Slice.len input) _ _ _ _ _ _ _ _ _ _ _ _ _ _
      _ _ _ _ _ seg 0#usize (by simp) hseg)
    rintro ⟨cte1, chl1, chd1, gml, gmd, gms, gchl, gchd⟩ _
    apply Std.WP.spec_bind (Pₘ := fun _ => True)
    · simp only [lift]
      split <;> step*
    · intro gms1 _
      apply Std.WP.spec_bind (xb_parse_loop1_spec input cte1 chl1 chd1 gml gmd gms1 gchl gchd seg 0#usize hseg)
      rintro ⟨chl2, chd2, gchl1, gchd1⟩ _
      exact xb_parse_loop2_spec input out (Std.Slice.len input) chl2 chd2 gchl1 gchd1 seg 0#usize 0#usize
        (by simp) hlen hseg (by scalar_tac) (by scalar_tac) (by simp [toks, LZ77.decode])

end X32

@[local step]
theorem x32b_parse_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) :
    slot.x32b_parse input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧
      LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ :=
  X32.xb_parse_spec input out hlen


/-! # sec_x239: engine E of submission 239 (numeric short-match block DP), its proof verbatim inside `X239` -/
namespace X239
open Aeneas Aeneas.Std Result ControlFlow
open LZ77 (toks bytes)
set_option maxRecDepth 8192
set_option maxHeartbeats 4000000
set_option hygiene false in
local notation "U1!" => (by
  by_cases h : c
  · rw [if_pos h]; exact ha h
  · rw [if_neg h]; exact hb h)
set_option hygiene false in
local notation "U4!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun s => n8.val - s.2.val)
    (inv := fun s => s.1.length = 8 * s.2.val ∧ s.2.val ≤ n8.val)
  · rintro ⟨v, i⟩ ⟨hv, hle⟩
    simp only at hv hle
    simp only [q1__]
    split
    case isTrue hlt =>
      step*
      all_goals (simp_all; scalar_tac)
    case isFalse hge =>
      simp only [Std.WP.spec_ok]
      scalar_tac
  · exact ⟨h0, hi⟩)
set_option hygiene false in
local notation "U5!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun s => n.val - s.2.val)
    (inv := fun s => s.1.length = s.2.val ∧ s.2.val ≤ n.val)
  · rintro ⟨v, j⟩ ⟨hv, hle⟩
    simp only at hv hle
    simp only [q1__]
    split
    case isTrue hlt =>
      step*
      simp_all
      scalar_tac
    case isFalse hge =>
      simp only [Std.WP.spec_ok]
      scalar_tac
  · exact ⟨h0, hj⟩)
set_option hygiene false in
local notation "U6!" q0__:max => (by
  rw [q0__]
  step*
  apply Std.WP.spec_bind (filled_loop0_spec x _ n8 0#usize (by scalar_tac)
    (by simp [alloc.vec.Vec.with_capacity]) (by scalar_tac))
  intro v1 hv1
  step*
  exact filled_loop1_spec n x v1 j (by scalar_tac) (by scalar_tac))
set_option hygiene false in
local notation "U8!" q0__:max q1__:max => (by
  (
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun l => cap.val - l.val)
    (inv := fun l => l.val ≤ cap.val ∧ LZ77.Matches input a.val b.val l.val)
  · rintro l ⟨hle, hinv⟩
    simp only [q1__]
    split
    case isTrue hlt =>
      have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
      step*
      all_goals first
        | scalar_tac
        | exact ⟨hle, hinv⟩
        | (refine ⟨by scalar_tac, ?_, by scalar_tac⟩
           rw [show l1.val = l.val + 1 by scalar_tac]
           apply LZ77.Matches.succ hinv
           rw [← i_post, ← i2_post, getElem!_pos _ _ (by scalar_tac),
             getElem!_pos _ _ (by scalar_tac), ← i1_post, ← i3_post]
           assumption)
    case isFalse => exact ⟨hle, hinv⟩
  · exact ⟨hl0, h0⟩))
set_option hygiene false in
local notation "U9!" => (by
  (
  exact match_len_loop_spec input a b cap 0#usize ha hb (by scalar_tac)
    (LZ77.Matches.zero input a.val b.val)))
set_option hygiene false in
local notation "U10!" q0__:max => (by
  rw [q0__]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  step*
  intro hv
  have hv' : ch.val ≤ v.val := by simpa using hv
  refine ⟨by scalar_tac, by scalar_tac, by scalar_tac, by scalar_tac, by scalar_tac,
    by scalar_tac, ?_⟩
  rw [show pos.val - d.val = i1.val by scalar_tac]
  exact Matches.mono v_post2 hv')
set_option hygiene false in
local notation "U11!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun s => n.val - s.2.1.val)
    (inv := fun s =>
      s.2.1.val ≤ n.val ∧ s.2.2.val ≤ s.2.1.val ∧ s.1.length = out0.length ∧
      LZ77.decode (toks s.1 s.2.2.val) = some ((bytes input).take s.2.1.val))
  · rintro ⟨out, k, ntok⟩ ⟨hkn, hnt, hlen, hde⟩
    simp only at hkn hnt hlen hde
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [q1__]
    split
    case isTrue hklt =>
      have hntok_lt : ntok.val < out.length := by scalar_tac
      step*
      apply Std.WP.spec_bind (verified_spec input k d ch)
      intro b hb
      split
      case isTrue hbt =>
        obtain ⟨hch3, hch258, hd1, hdmax, hdpos, hend, hmatch⟩ := hb hbt
        step*
        have htok : i7.val = LZ77.mkMatch d.val ch.val := by
          simp only [LZ77.mkMatch, LZ77.MATCH_BASE, i7_post, i4_post, i3_post]
          scalar_tac
        refine ⟨by scalar_tac, by scalar_tac,
          by rw [s_post]; simpa [Std.Slice.set_val_eq] using hlen, ?_, by scalar_tac⟩
        rw [s_post, show ntok1.val = ntok.val + 1 by scalar_tac,
          show k1.val = k.val + ch.val by scalar_tac]
        exact emit_match input out ntok k.val d.val ch.val i7 hde hntok_lt hd1 hdpos hdmax
          hch3 hch258 hend hmatch htok
      case isFalse hbf =>
        have hposlen : k.val < input.length := by scalar_tac
        step*
        have hval : i2.val = (bytes input)[k.val]! := by
          rw [bytes_getElem! input k.val hposlen, i2_post, Std.U8.cast_U32_val_eq, i1_post]
        refine ⟨by scalar_tac, by scalar_tac,
          by rw [s_post]; simpa [Std.Slice.set_val_eq] using hlen, ?_, by scalar_tac⟩
        rw [s_post, show ntok1.val = ntok.val + 1 by scalar_tac,
          show k1.val = k.val + 1 by scalar_tac]
        exact emit_lit input out ntok k.val i2 hde hposlen hntok_lt hval
    case isFalse hge =>
      have hkn' : k.val = input.length := by scalar_tac
      refine ⟨by scalar_tac, hlen, ?_⟩
      rw [hde, hkn']
      simp
  · exact ⟨hk, hntok, rfl, hdec⟩)
set_option hygiene false in
local notation "U12!" q0__:max => (by
  rw [q0__]
  exact emit_all_loop_spec input out plan _ 0#usize 0#usize
    (by simp) hout (by scalar_tac) (by scalar_tac) (by simp [toks, LZ77.decode]))
set_option hygiene false in
local notation "U14!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 300 - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨l1, it1⟩ _
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [q1__, lift]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial)
set_option hygiene false in
local notation "U36!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => b.val - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨v1, i1⟩ _
    simp only [q1__, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial)
set_option hygiene false in
local notation "U38!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨order1, j1⟩ _
    simp only [q1__, lift]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial)
set_option hygiene false in
local notation "U39!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 288 - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨cnt1, i1⟩ _
    simp only [q1__, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial)
set_option hygiene false in
local notation "U40!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 256 - qq9.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨cnt1, acc1, d1⟩ _
    simp only [q1__, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial)
set_option hygiene false in
local notation "U41!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 288 - qq9.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨dst1, cnt1, j1⟩ _
    simp only [q1__, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial)
set_option hygiene false in
local notation "U42!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => m.val - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨dst1, i1⟩ _
    simp only [q1__, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial)
set_option hygiene false in
local notation "U43!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 288 - qq9.2.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨tmp1, k1, big1, s1⟩ _
    simp only [q1__, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial)
set_option hygiene false in
local notation "U44!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 288 - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨order1, j1⟩ _
    simp only [q1__, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial)
set_option hygiene false in
local notation "U56!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 1000 - qq9.val)
    (inv := fun _ => True)
  · rintro r1 _
    simp only [q1__, lift]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial)
set_option hygiene false in
local notation "U57!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => m.val - qq9.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨clf1, extra1, i1⟩ _
    simp only [q1__, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial)
set_option hygiene false in
local notation "U58!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => m.val - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨s1, i1⟩ _
    simp only [q1__, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial)
set_option hygiene false in
local notation "U59!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 288 - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨s1, i1⟩ _
    simp only [q1__, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial)
set_option hygiene false in
local notation "U60!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => b.val - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨s1, i1⟩ _
    simp only [q1__, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial)
set_option hygiene false in
local notation "U61!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => qq9.val)
    (inv := fun _ => True)
  · rintro k1 _
    simp only [q1__, lift]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial)
set_option hygiene false in
local notation "U62!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => qq9.val)
    (inv := fun _ => True)
  · rintro h1 _
    simp only [q1__, lift]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial)
set_option hygiene false in
local notation "U63!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 318 - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨sc1, s1⟩ _
    simp only [q1__, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial)
set_option hygiene false in
local notation "U64!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 256 - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨tbl1, c1⟩ _
    simp only [q1__, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial)
set_option hygiene false in
local notation "U65!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 259 - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨tbl1, len1⟩ _
    simp only [q1__, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial)
set_option hygiene false in
local notation "U66!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 30 - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨tbl1, s1⟩ _
    simp only [q1__, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial)
set_option hygiene false in
local notation "U147!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun s => blen.val - s.2.2.val)
    (inv := fun s =>
      s.2.2.val ≤ blen.val ∧ s.2.1.val ≤ p0.val + s.2.2.val ∧
      s.1.length = out0.length ∧
      LZ77.decode (toks s.1 s.2.1.val) = some ((bytes input).take (p0.val + s.2.2.val)))
  · rintro ⟨out, ntok, k⟩ ⟨hkb, hnt, hlen, hde⟩
    simp only at hkb hnt hlen hde
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [q1__]
    split
    case isTrue hklt =>
      have hntok_lt : ntok.val < out.length := by scalar_tac
      step*
      apply Std.WP.spec_bind (verified_spec input pos d ch k blen (by scalar_tac) (by scalar_tac) hb)
      intro b hbv
      split
      case isTrue hbt =>
        obtain ⟨hch3, hch258, hd1, hdmax, hdpos, hend, hmatch⟩ := hbv hbt
        step*
        have htok : i9.val = LZ77.mkMatch d.val ch.val := by
          simp only [LZ77.mkMatch, LZ77.MATCH_BASE, i9_post, i6_post, i4_post,
            i3_post1, i8_post, i7_post1, Std.UScalar.cast_val_eq] at *
          scalar_tac
        refine ⟨by scalar_tac, by scalar_tac,
          by rw [s_post]; simpa [Std.Slice.set_val_eq] using hlen, ?_, by scalar_tac⟩
        rw [s_post, show ntok1.val = ntok.val + 1 by scalar_tac,
          toks_update out ntok i9 hntok_lt, htok,
          show p0.val + k1.val = pos.val + ch.val by scalar_tac]
        refine LZ77.valid_match (bytes input) (toks out ntok.val) pos.val d.val ch.val
          (by rw [show pos.val = p0.val + k.val by scalar_tac]; exact hde)
          hd1 hdpos (by simpa [LZ77.MAX_DIST] using hdmax) hch3
          (by simpa [LZ77.MAX_LEN] using hch258) (by rw [bytes_length]; scalar_tac) ?_
        intro j hj
        exact (bytes_congr input _ _ (by scalar_tac) (by scalar_tac) (hmatch j hj)).symm
      case isFalse hbf =>
        have hposlen : pos.val < input.length := by scalar_tac
        step*
        have hval : i4.val = (bytes input)[pos.val]! := by
          rw [bytes_getElem! input pos.val hposlen, i4_post, Std.U8.cast_U32_val_eq, i3_post]
        refine ⟨by scalar_tac, by scalar_tac,
          by rw [s_post]; simpa [Std.Slice.set_val_eq] using hlen, ?_, by scalar_tac⟩
        rw [s_post, show ntok1.val = ntok.val + 1 by scalar_tac,
          toks_update out ntok i4 hntok_lt, hval,
          show p0.val + k1.val = pos.val + 1 by scalar_tac]
        exact LZ77.valid_lit (bytes input) (toks out ntok.val) pos.val
          (by rw [show pos.val = p0.val + k.val by scalar_tac]; exact hde)
          (by rw [bytes_length]; scalar_tac) (by rw [← hval]; scalar_tac)
    case isFalse hge =>
      have hkb' : k.val = blen.val := by scalar_tac
      refine ⟨by scalar_tac, hlen, ?_⟩
      rw [hde, hkb']
  · exact ⟨hk, hntok, rfl, hdec⟩)
namespace EE
open Aeneas Aeneas.Std Result ControlFlow
set_option maxRecDepth 8192
set_option maxHeartbeats 4000000
open LZ77 (toks bytes bytes_length bytes_getElem! toks_update bytes_congr Matches ite_ok)
theorem match_len_loop_spec (input : Slice Std.U8) (a b cap l0 : Std.Usize)
    (ha : a.val + cap.val ≤ input.length) (hb : b.val + cap.val ≤ input.length)
    (hl0 : l0.val ≤ cap.val) (h0 : Matches input a.val b.val l0.val) :
    slot.e_match_len_loop input a b cap l0 ⦃ fun l =>
      l.val ≤ cap.val ∧ Matches input a.val b.val l.val ⦄ := U8! slot.e_match_len_loop slot.e_match_len_loop.body
@[local step]
theorem match_len_spec (input : Slice Std.U8) (a b cap : Std.Usize)
    (ha : a.val + cap.val ≤ input.length) (hb : b.val + cap.val ≤ input.length) :
    slot.e_match_len input a b cap ⦃ fun l =>
      l.val ≤ cap.val ∧ Matches input a.val b.val l.val ⦄ := U9!
set_option linter.unusedSimpArgs false
set_option linter.unusedTactic false
set_option linter.unreachableTactic false
theorem p25_0 {α : Type} (c : Prop) [Decidable c] (a b : Result α) (Q : α → Prop)
    (ha : c → a ⦃ Q ⦄) (hb : ¬c → b ⦃ Q ⦄) : (if c then a else b) ⦃ Q ⦄ := U1!
set_option hygiene false in
local notation "YA1!" q0__:max => (by
  rw [q0__]
  try simp only [lift, Array.to_slice_mut]
  try simp only [ite_ok]
  step*
  repeat (first
    | (step)
    | (simp only [ite_ok]; (first | done | step))
    | (intro hc; repeat (obtain ⟨_, hc⟩ : _ × _ := hc); (try step*))
    | (split <;> (try step*))
    | (rename_i heq; split at heq <;> simp_all)
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply p25_0 <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals scalar_tac)
@[local step]
theorem p25_1
(dlo : Array Std.U8 256#usize) (dhi : Array Std.U8 256#usize) (d : Std.Usize) :
    slot.e_dcode dlo dhi d ⦃ fun _ => True ⦄ := YA1! slot.e_dcode
@[local step]
theorem p25_2
(w : Array Std.U32 512#usize) (sym : Array Std.U16 512#usize) (x : Std.U32)
  (j : Std.Usize) :
    slot.e_hins_loop w sym x j ⦃ fun _ => True ⦄ := by
  rw [slot.e_hins_loop]
  apply Std.loop.spec_decr_nat (measure := fun s => s.2.2.val) (inv := fun _ => True)
  · rintro ⟨x0, x1, x2⟩ _
    simp only [slot.e_hins_loop.body, lift, Array.to_slice_mut]
    try simp only [ite_ok]
    step*
    repeat (first
      | (step)
      | (simp only [ite_ok]; (first | done | step))
      | (intro hc; repeat (obtain ⟨_, hc⟩ : _ × _ := hc); (try step*))
      | (split <;> (try step*))
      | (rename_i heq; split at heq <;> simp_all)
      | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply p25_0 <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals scalar_tac
  · trivial
@[local step]
theorem p25_3
(w : Array Std.U32 512#usize) (sym : Array Std.U16 512#usize) (m : Std.Usize)
  (x : Std.U32) (sy : Std.Usize) :
    slot.e_hins w sym m x sy ⦃ fun _ => True ⦄ := YA1! slot.e_hins
set_option hygiene false in
local notation "YA2!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat (measure := fun s => (512) - s.2.val) (inv := fun _ => True)
  · rintro ⟨x0, x1⟩ _
    simp only [q1__, lift, Array.to_slice_mut]
    try simp only [ite_ok]
    step*
    repeat (first
      | (step)
      | (simp only [ite_ok]; (first | done | step))
      | (intro hc; repeat (obtain ⟨_, hc⟩ : _ × _ := hc); (try step*))
      | (split <;> (try step*))
      | (rename_i heq; split at heq <;> simp_all)
      | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply p25_0 <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals scalar_tac
  · trivial)
@[local step]
theorem p25_4
(w : Array Std.U32 512#usize) (m : Std.Usize) (nw : Array Std.U32 1024#usize)
  (k : Std.Usize) :
    slot.e_hbuild_loop0 w m nw k ⦃ fun _ => True ⦄ := YA2! slot.e_hbuild_loop0 slot.e_hbuild_loop0.body
@[local step]
theorem p25_5
(m : Std.Usize) (nw : Array Std.U32 1024#usize) (i1 : Std.Usize)
  (i2 : Std.Usize) (top : Std.Usize) (pick1 : Std.Usize) (a : Std.Usize)
  (b : Std.Usize) :
    slot.e_hbuild_loop1_loop0 m nw i1 i2 top pick1 a b ⦃ fun _ => True ⦄ := by
  rw [slot.e_hbuild_loop1_loop0]
  apply Std.loop.spec_decr_nat (measure := fun s => (2) - s.2.2.1.val) (inv := fun _ => True)
  · rintro ⟨x0, x1, x2, x3, x4⟩ _
    simp only [slot.e_hbuild_loop1_loop0.body, lift, Array.to_slice_mut]
    try simp only [ite_ok]
    step*
    repeat (first
      | (step)
      | (simp only [ite_ok]; (first | done | step))
      | (intro hc; repeat (obtain ⟨_, hc⟩ : _ × _ := hc); (try step*))
      | (split <;> (try step*))
      | (rename_i heq; split at heq <;> simp_all)
      | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply p25_0 <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals scalar_tac
  · trivial
set_option hygiene false in
local notation "YA3!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat (measure := fun s => (512) - s.2.2.2.2.val) (inv := fun _ => True)
  · rintro ⟨x0, x1, x2, x3, x4⟩ _
    simp only [q1__, lift, Array.to_slice_mut]
    try simp only [ite_ok]
    step*
    repeat (first
      | (step)
      | (simp only [ite_ok]; (first | done | step))
      | (intro hc; repeat (obtain ⟨_, hc⟩ : _ × _ := hc); (try step*))
      | (split <;> (try step*))
      | (rename_i heq; split at heq <;> simp_all)
      | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply p25_0 <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals scalar_tac
  · trivial)
@[local step]
theorem p25_6
(m : Std.Usize) (nw : Array Std.U32 1024#usize)
  (par : Array Std.U16 1024#usize) (i1 : Std.Usize) (i2 : Std.Usize)
  (t : Std.Usize) :
    slot.e_hbuild_loop1 m nw par i1 i2 t ⦃ fun _ => True ⦄ := YA3! slot.e_hbuild_loop1 slot.e_hbuild_loop1.body
@[local step]
theorem p25_7
(par : Array Std.U16 1024#usize) (dep : Array Std.U32 1024#usize)
  (root : Std.Usize) (r : Std.Usize) :
    slot.e_hbuild_loop2 par dep root r ⦃ fun _ => True ⦄ := by
  rw [slot.e_hbuild_loop2]
  apply Std.loop.spec_decr_nat (measure := fun s => (root.val + 1) - s.2.val) (inv := fun _ => True)
  · rintro ⟨x0, x1⟩ _
    simp only [slot.e_hbuild_loop2.body, lift, Array.to_slice_mut]
    try simp only [ite_ok]
    step*
    repeat (first
      | (step)
      | (simp only [ite_ok]; (first | done | step))
      | (intro hc; repeat (obtain ⟨_, hc⟩ : _ × _ := hc); (try step*))
      | (split <;> (try step*))
      | (rename_i heq; split at heq <;> simp_all)
      | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply p25_0 <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals scalar_tac
  · trivial
@[local step]
theorem p25_8
(sym : Array Std.U16 512#usize) (m : Std.Usize)
  (out : Array Std.U32 512#usize) (dep : Array Std.U32 1024#usize)
  (k : Std.Usize) :
    slot.e_hbuild_loop3 sym m out dep k ⦃ fun _ => True ⦄ := YA2! slot.e_hbuild_loop3 slot.e_hbuild_loop3.body
@[local step]
theorem p25_9
(w : Array Std.U32 512#usize) (sym : Array Std.U16 512#usize) (m : Std.Usize)
  (out : Array Std.U32 512#usize) :
    slot.e_hbuild w sym m out ⦃ fun _ => True ⦄ := YA1! slot.e_hbuild
@[local step]
theorem p25_10
(f : Array Std.U32 512#usize) (ns : Std.Usize)
  (out : Array Std.U32 512#usize) (w : Array Std.U32 512#usize)
  (sym : Array Std.U16 512#usize) (m : Std.Usize) (s : Std.Usize) :
    slot.e_hlens_loop f ns out w sym m s ⦃ fun _ => True ⦄ := YA3! slot.e_hlens_loop slot.e_hlens_loop.body
@[local step]
theorem p25_11
(f : Array Std.U32 512#usize) (ns : Std.Usize)
  (out : Array Std.U32 512#usize) :
    slot.e_hlens f ns out ⦃ fun _ => True ⦄ := YA1! slot.e_hlens
@[local step]
theorem p25_12
(lbase : Array Std.U16 32#usize) (lext : Array Std.U8 32#usize)
  (lcode : Array Std.U8 512#usize) (lextra : Array Std.U8 512#usize)
  (bend : Array Std.U16 512#usize) (c : Std.Usize) (l : Std.Usize) :
    slot.e_len_tables_loop lbase lext lcode lextra bend c l ⦃ fun _ => True ⦄ := by
  rw [slot.e_len_tables_loop]
  apply Std.loop.spec_decr_nat (measure := fun s => (259) - s.2.2.2.2.val) (inv := fun _ => True)
  · rintro ⟨x0, x1, x2, x3, x4⟩ _
    simp only [slot.e_len_tables_loop.body, lift, Array.to_slice_mut]
    try simp only [ite_ok]
    step*
    repeat (first
      | (step)
      | (simp only [ite_ok]; (first | done | step))
      | (intro hc; repeat (obtain ⟨_, hc⟩ : _ × _ := hc); (try step*))
      | (split <;> (try step*))
      | (rename_i heq; split at heq <;> simp_all)
      | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply p25_0 <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals scalar_tac
  · trivial
@[local step]
theorem p25_13
(lbase : Array Std.U16 32#usize) (lext : Array Std.U8 32#usize)
  (lcode : Array Std.U8 512#usize) (lextra : Array Std.U8 512#usize)
  (bend : Array Std.U16 512#usize) :
    slot.e_len_tables lbase lext lcode lextra bend ⦃ fun _ => True ⦄ := YA1! slot.e_len_tables
@[local step]
theorem p25_14
(dbase : Array Std.U16 32#usize) (d : Std.Usize) (c : Std.Usize) :
    slot.e_code_from_loop dbase d c ⦃ fun _ => True ⦄ := by
  rw [slot.e_code_from_loop]
  apply Std.loop.spec_decr_nat (measure := fun s => (29) - s.val) (inv := fun _ => True)
  · rintro x0 _
    simp only [slot.e_code_from_loop.body, lift, Array.to_slice_mut]
    try simp only [ite_ok]
    step*
    repeat (first
      | (step)
      | (simp only [ite_ok]; (first | done | step))
      | (intro hc; repeat (obtain ⟨_, hc⟩ : _ × _ := hc); (try step*))
      | (split <;> (try step*))
      | (rename_i heq; split at heq <;> simp_all)
      | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply p25_0 <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals scalar_tac
  · trivial
@[local step]
theorem p25_15
(dbase : Array Std.U16 32#usize) (d : Std.Usize) (c0 : Std.Usize) :
    slot.e_code_from dbase d c0 ⦃ fun _ => True ⦄ := YA1! slot.e_code_from
@[local step]
theorem p25_16
(dbase : Array Std.U16 32#usize) (dlo : Array Std.U8 256#usize)
  (c : Std.Usize) (d : Std.Usize) :
    slot.e_dist_tables_loop0 dbase dlo c d ⦃ fun _ => True ⦄ := by
  rw [slot.e_dist_tables_loop0]
  apply Std.loop.spec_decr_nat (measure := fun s => (257) - s.2.2.val) (inv := fun _ => True)
  · rintro ⟨x0, x1, x2⟩ _
    simp only [slot.e_dist_tables_loop0.body, lift, Array.to_slice_mut]
    try simp only [ite_ok]
    step*
    repeat (first
      | (step)
      | (simp only [ite_ok]; (first | done | step))
      | (intro hc; repeat (obtain ⟨_, hc⟩ : _ × _ := hc); (try step*))
      | (split <;> (try step*))
      | (rename_i heq; split at heq <;> simp_all)
      | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply p25_0 <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals scalar_tac
  · trivial
@[local step]
theorem p25_17
(dbase : Array Std.U16 32#usize) (dhi : Array Std.U8 256#usize)
  (c : Std.Usize) (k : Std.Usize) :
    slot.e_dist_tables_loop1 dbase dhi c k ⦃ fun _ => True ⦄ := by
  rw [slot.e_dist_tables_loop1]
  apply Std.loop.spec_decr_nat (measure := fun s => (256) - s.2.2.val) (inv := fun _ => True)
  · rintro ⟨x0, x1, x2⟩ _
    simp only [slot.e_dist_tables_loop1.body, lift, Array.to_slice_mut]
    try simp only [ite_ok]
    step*
    repeat (first
      | (step)
      | (simp only [ite_ok]; (first | done | step))
      | (intro hc; repeat (obtain ⟨_, hc⟩ : _ × _ := hc); (try step*))
      | (split <;> (try step*))
      | (rename_i heq; split at heq <;> simp_all)
      | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply p25_0 <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals scalar_tac
  · trivial
@[local step]
theorem p25_18
(dbase : Array Std.U16 32#usize) (dlo : Array Std.U8 256#usize)
  (dhi : Array Std.U8 256#usize) :
    slot.e_dist_tables dbase dlo dhi ⦃ fun _ => True ⦄ := YA1! slot.e_dist_tables
@[local step]
theorem p25_19
(lcode : Array Std.U8 512#usize) (lextra : Array Std.U8 512#usize)
  (bend : Array Std.U16 512#usize) (dlo : Array Std.U8 256#usize)
  (dhi : Array Std.U8 256#usize) (dext : Array Std.U8 32#usize) :
    slot.e_tables lcode lextra bend dlo dhi dext ⦃ fun _ => True ⦄ := YA1! slot.e_tables
@[local step]
theorem p25_20
(input : Slice Std.U8) (p : Std.Usize) :
    slot.e_ld4 input p ⦃ fun _ => True ⦄ := by
  rw [slot.e_ld4]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  try simp only [lift, Array.to_slice_mut]
  try simp only [ite_ok]
  step*
  repeat (first
    | (step)
    | (simp only [ite_ok]; (first | done | step))
    | (intro hc; repeat (obtain ⟨_, hc⟩ : _ × _ := hc); (try step*))
    | (split <;> (try step*))
    | (rename_i heq; split at heq <;> simp_all)
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply p25_0 <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals scalar_tac
@[local step]
theorem p25_21
(input : Slice Std.U8) (p : Std.Usize) :
    slot.e_at input p ⦃ fun _ => True ⦄ := YA1! slot.e_at
@[local step]
theorem p25_22
(input : Slice Std.U8) (a : Std.Usize) (b : Std.Usize) (cap : Std.Usize)
  (l : Std.Usize) :
    slot.e_lcp_after_loop input a b cap l ⦃ fun _ => True ⦄ := by
  rw [slot.e_lcp_after_loop]
  apply Std.loop.spec_decr_nat (measure := fun s => (258) - s.val) (inv := fun _ => True)
  · rintro x0 _
    simp only [slot.e_lcp_after_loop.body, lift, Array.to_slice_mut]
    try simp only [ite_ok]
    step*
    repeat (first
      | (step)
      | (simp only [ite_ok]; (first | done | step))
      | (intro hc; repeat (obtain ⟨_, hc⟩ : _ × _ := hc); (try step*))
      | (split <;> (try step*))
      | (rename_i heq; split at heq <;> simp_all)
      | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply p25_0 <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals scalar_tac
  · trivial
@[local step]
theorem p25_23
(input : Slice Std.U8) (a : Std.Usize) (b : Std.Usize) (cap : Std.Usize)
  (start : Std.Usize) :
    slot.e_lcp_after input a b cap start ⦃ fun _ => True ⦄ := YA1! slot.e_lcp_after
@[local step]
theorem p25_24
(x : Std.U32) :
    slot.e_log16 x ⦃ fun _ => True ⦄ := YA1! slot.e_log16
@[local step]
theorem p25_25
(f : Std.U32) (total : Std.U32) :
    slot.e_cost16 f total ⦃ fun _ => True ⦄ := YA1! slot.e_cost16
set_option hygiene false in
local notation "YA4!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat (measure := fun s => (32) - s.2.val) (inv := fun _ => True)
  · rintro ⟨x0, x1⟩ _
    simp only [q1__, lift, Array.to_slice_mut]
    try simp only [ite_ok]
    step*
    repeat (first
      | (step)
      | (simp only [ite_ok]; (first | done | step))
      | (intro hc; repeat (obtain ⟨_, hc⟩ : _ × _ := hc); (try step*))
      | (split <;> (try step*))
      | (rename_i heq; split at heq <;> simp_all)
      | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply p25_0 <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals scalar_tac
  · trivial)
@[local step]
theorem p25_26
(df : Array Std.U32 32#usize) (tmp : Array Std.U32 512#usize) (i : Std.Usize) :
    slot.e_prices_loop0 df tmp i ⦃ fun _ => True ⦄ := YA4! slot.e_prices_loop0 slot.e_prices_loop0.body
@[local step]
theorem p25_27
(lf : Array Std.U32 512#usize) (i : Std.Usize) (total : Std.U32) :
    slot.e_prices_loop1 lf i total ⦃ fun _ => True ⦄ := by
  rw [slot.e_prices_loop1]
  apply Std.loop.spec_decr_nat (measure := fun s => (286) - s.1.val) (inv := fun _ => True)
  · rintro ⟨x0, x1⟩ _
    simp only [slot.e_prices_loop1.body, lift, Array.to_slice_mut]
    try simp only [ite_ok]
    step*
    repeat (first
      | (step)
      | (simp only [ite_ok]; (first | done | step))
      | (intro hc; repeat (obtain ⟨_, hc⟩ : _ × _ := hc); (try step*))
      | (split <;> (try step*))
      | (rename_i heq; split at heq <;> simp_all)
      | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply p25_0 <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals scalar_tac
  · trivial
set_option hygiene false in
local notation "YA5!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat (measure := fun s => (256) - s.2.val) (inv := fun _ => True)
  · rintro ⟨x0, x1⟩ _
    simp only [q1__, lift, Array.to_slice_mut]
    try simp only [ite_ok]
    step*
    repeat (first
      | (step)
      | (simp only [ite_ok]; (first | done | step))
      | (intro hc; repeat (obtain ⟨_, hc⟩ : _ × _ := hc); (try step*))
      | (split <;> (try step*))
      | (rename_i heq; split at heq <;> simp_all)
      | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply p25_0 <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals scalar_tac
  · trivial)
@[local step]
theorem p25_28
(lf : Array Std.U32 512#usize) (litc : Array Std.U32 256#usize)
  (hw : Std.U32) (hl : Array Std.U32 512#usize) (i : Std.Usize)
  (total : Std.U32) :
    slot.e_prices_loop2 lf litc hw hl i total ⦃ fun _ => True ⦄ := YA5! slot.e_prices_loop2 slot.e_prices_loop2.body
set_option hygiene false in
local notation "YA6!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat (measure := fun s => (259) - s.2.val) (inv := fun _ => True)
  · rintro ⟨x0, x1⟩ _
    simp only [q1__, lift, Array.to_slice_mut]
    try simp only [ite_ok]
    step*
    repeat (first
      | (step)
      | (simp only [ite_ok]; (first | done | step))
      | (intro hc; repeat (obtain ⟨_, hc⟩ : _ × _ := hc); (try step*))
      | (split <;> (try step*))
      | (rename_i heq; split at heq <;> simp_all)
      | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply p25_0 <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals scalar_tac
  · trivial)
@[local step]
theorem p25_29
(lf : Array Std.U32 512#usize) (lenc : Array Std.U32 512#usize)
  (lc : Array Std.U8 512#usize) (le : Array Std.U8 512#usize)
  (penalty : Std.U32) (hw : Std.U32) (hl : Array Std.U32 512#usize)
  (i : Std.Usize) (total : Std.U32) :
    slot.e_prices_loop3 lf lenc lc le penalty hw hl i total ⦃ fun _ => True ⦄ := YA6! slot.e_prices_loop3 slot.e_prices_loop3.body
@[local step]
theorem p25_30
(df : Array Std.U32 32#usize) (i : Std.Usize) (total : Std.U32) :
    slot.e_prices_loop4 df i total ⦃ fun _ => True ⦄ := by
  rw [slot.e_prices_loop4]
  apply Std.loop.spec_decr_nat (measure := fun s => (30) - s.1.val) (inv := fun _ => True)
  · rintro ⟨x0, x1⟩ _
    simp only [slot.e_prices_loop4.body, lift, Array.to_slice_mut]
    try simp only [ite_ok]
    step*
    repeat (first
      | (step)
      | (simp only [ite_ok]; (first | done | step))
      | (intro hc; repeat (obtain ⟨_, hc⟩ : _ × _ := hc); (try step*))
      | (split <;> (try step*))
      | (rename_i heq; split at heq <;> simp_all)
      | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply p25_0 <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals scalar_tac
  · trivial
set_option hygiene false in
local notation "YA7!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat (measure := fun s => (30) - s.2.val) (inv := fun _ => True)
  · rintro ⟨x0, x1⟩ _
    simp only [q1__, lift, Array.to_slice_mut]
    try simp only [ite_ok]
    step*
    repeat (first
      | (step)
      | (simp only [ite_ok]; (first | done | step))
      | (intro hc; repeat (obtain ⟨_, hc⟩ : _ × _ := hc); (try step*))
      | (split <;> (try step*))
      | (rename_i heq; split at heq <;> simp_all)
      | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply p25_0 <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals scalar_tac
  · trivial)
@[local step]
theorem p25_31
(df : Array Std.U32 32#usize) (dc : Array Std.U32 32#usize)
  (de : Array Std.U8 32#usize) (hw : Std.U32) (dh : Array Std.U32 512#usize)
  (i : Std.Usize) (total : Std.U32) :
    slot.e_prices_loop5 df dc de hw dh i total ⦃ fun _ => True ⦄ := YA7! slot.e_prices_loop5 slot.e_prices_loop5.body
@[local step]
theorem p25_32
(lf : Array Std.U32 512#usize) (df : Array Std.U32 32#usize)
  (litc : Array Std.U32 256#usize) (lenc : Array Std.U32 512#usize)
  (dc : Array Std.U32 32#usize) (lc : Array Std.U8 512#usize)
  (le : Array Std.U8 512#usize) (de : Array Std.U8 32#usize) (hw0 : Std.U32)
  (penalty : Std.U32) :
    slot.e_prices lf df litc lenc dc lc le de hw0 penalty ⦃ fun _ => True ⦄ := YA1! slot.e_prices
@[local step]
theorem p25_33
(xs : Array Std.U32 131072#usize) (k : Std.Usize) (s : Std.Usize)
  (v : Std.U32) :
    slot.e_put xs k s v ⦃ fun _ => True ⦄ := YA1! slot.e_put
@[local step]
theorem p25_34
(input : Slice Std.U8) (c : Std.Usize) (pos : Std.Usize) (cap : Std.Usize)
  (key : Std.U32) (max3 : Std.Usize) :
    slot.e_near_candidate input c pos cap key max3 ⦃ fun _ => True ⦄ := YA1! slot.e_near_candidate
@[local step]
theorem p25_35
(input : Slice Std.U8) (prev : Array Std.U32 32768#usize)
  (xs : Array Std.U32 131072#usize) (pos : Std.Usize) (k : Std.Usize)
  (cap : Std.Usize) (word : Std.U32) (cur : Std.Usize) (longest : Std.Usize)
  (s : Std.Usize) (it : Std.Usize) :
    slot.e_walk_four_loop input prev xs pos k cap word cur longest s it ⦃ fun _ => True ⦄ := by
  rw [slot.e_walk_four_loop]
  apply Std.loop.spec_decr_nat (measure := fun s => (slot.E_PROBES.val) - s.2.2.2.2.val) (inv := fun _ => True)
  · rintro ⟨x0, x1, x2, x3, x4⟩ _
    simp only [slot.e_walk_four_loop.body, lift, Array.to_slice_mut]
    try simp only [ite_ok]
    step*
    repeat (first
      | (step)
      | (simp only [ite_ok]; (first | done | step))
      | (intro hc; repeat (obtain ⟨_, hc⟩ : _ × _ := hc); (try step*))
      | (split <;> (try step*))
      | (rename_i heq; split at heq <;> simp_all)
      | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply p25_0 <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals scalar_tac
  · trivial
@[local step]
theorem p25_36
(input : Slice Std.U8) (prev : Array Std.U32 32768#usize)
  (xs : Array Std.U32 131072#usize) (pos : Std.Usize) (k : Std.Usize)
  (cap : Std.Usize) (word : Std.U32) (cur0 : Std.Usize) (longest0 : Std.Usize)
  (s0 : Std.Usize) :
    slot.e_walk_four input prev xs pos k cap word cur0 longest0 s0 ⦃ fun _ => True ⦄ := YA1! slot.e_walk_four
@[local step]
theorem p25_37
(input : Slice Std.U8) (c : Std.Usize) (pos : Std.Usize) (cap : Std.Usize)
  (word : Std.U32) :
    slot.e_exact4 input c pos cap word ⦃ fun _ => True ⦄ := YA1! slot.e_exact4
@[local step]
theorem p25_38
(input : Slice Std.U8) (c : Std.U32) (pos : Std.Usize) (cap : Std.Usize)
  (word : Std.U32) (tag : Std.U32) :
    slot.e_exact_bf input c pos cap word tag ⦃ fun _ => True ⦄ := YA1! slot.e_exact_bf
@[local step]
theorem p25_39
(xs : Array Std.U32 131072#usize) (k : Std.Usize) (v : Std.U32)
  (longest : Std.Usize) (s : Std.Usize) :
    slot.e_bf_choice xs k v longest s ⦃ fun _ => True ⦄ := YA1! slot.e_bf_choice
@[local step]
theorem p25_40
(input : Slice Std.U8) (near : Array Std.U32 65536#usize)
  (head : Array Std.U32 131072#usize) (xs : Array Std.U32 131072#usize)
  (pos : Std.Usize) (k : Std.Usize) (cap : Std.Usize) :
    slot.e_find_bf input near head xs pos k cap ⦃ fun _ => True ⦄ := YA1! slot.e_find_bf
@[local step]
theorem p25_41
(input : Slice Std.U8) (near : Array Std.U32 65536#usize)
  (head : Array Std.U32 131072#usize) (prev : Array Std.U32 32768#usize)
  (xs : Array Std.U32 131072#usize) (pos : Std.Usize) (k : Std.Usize)
  (cap : Std.Usize) (max3 : Std.Usize) (mode : Std.Usize) :
    slot.e_find_dual input near head prev xs pos k cap max3 mode ⦃ fun _ => True ⦄ := YA1! slot.e_find_dual
@[local step]
theorem p25_42
(xs : Array Std.U32 131072#usize) (k : Std.Usize) (s : Std.Usize) :
    slot.e_clear_pos_loop xs k s ⦃ fun _ => True ⦄ := by
  rw [slot.e_clear_pos_loop]
  apply Std.loop.spec_decr_nat (measure := fun s => (slot.E_NX.val) - s.2.val) (inv := fun _ => True)
  · rintro ⟨x0, x1⟩ _
    simp only [slot.e_clear_pos_loop.body, lift, Array.to_slice_mut]
    try simp only [ite_ok]
    step*
    repeat (first
      | (step)
      | (simp only [ite_ok]; (first | done | step))
      | (intro hc; repeat (obtain ⟨_, hc⟩ : _ × _ := hc); (try step*))
      | (split <;> (try step*))
      | (rename_i heq; split at heq <;> simp_all)
      | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply p25_0 <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals scalar_tac
  · trivial
@[local step]
theorem p25_43
(xs : Array Std.U32 131072#usize) (k : Std.Usize) :
    slot.e_clear_pos xs k ⦃ fun _ => True ⦄ := YA1! slot.e_clear_pos
@[local step]
theorem p25_44
(xs : Array Std.U32 131072#usize) (k : Std.Usize) (stride : Std.Usize)
  (i : Std.Usize) (flag : Std.Usize) :
    slot.e_long_at_loop xs k stride i flag ⦃ fun _ => True ⦄ := by
  rw [slot.e_long_at_loop]
  apply Std.loop.spec_decr_nat (measure := fun s => (slot.E_NX.val) - s.1.val) (inv := fun _ => True)
  · rintro ⟨x0, x1⟩ _
    simp only [slot.e_long_at_loop.body, lift, Array.to_slice_mut]
    try simp only [ite_ok]
    step*
    repeat (first
      | (step)
      | (simp only [ite_ok]; (first | done | step))
      | (intro hc; repeat (obtain ⟨_, hc⟩ : _ × _ := hc); (try step*))
      | (split <;> (try step*))
      | (rename_i heq; split at heq <;> simp_all)
      | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply p25_0 <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals scalar_tac
  · trivial
@[local step]
theorem p25_45
(xs : Array Std.U32 131072#usize) (k : Std.Usize) (stride : Std.Usize) :
    slot.e_long_at xs k stride ⦃ fun _ => True ⦄ := YA1! slot.e_long_at
@[local step]
theorem p25_46
(input : Slice Std.U8) (near : Array Std.U32 65536#usize)
  (head : Array Std.U32 131072#usize) (prev : Array Std.U32 32768#usize)
  (xs : Array Std.U32 131072#usize) (p0 : Std.Usize) (blen : Std.Usize)
  (max3 : Std.Usize) (mode : Std.Usize) (stride : Std.Usize) (n : Std.Usize)
  (k : Std.Usize) (flag : Std.Usize) :
    slot.e_candidates_loop input near head prev xs p0 blen max3 mode stride n k flag ⦃ fun _ => True ⦄ := by
  rw [slot.e_candidates_loop]
  apply Std.loop.spec_decr_nat (measure := fun s => (32768) - s.2.2.2.2.1.val) (inv := fun _ => True)
  · rintro ⟨x0, x1, x2, x3, x4, x5⟩ _
    simp only [slot.e_candidates_loop.body, lift, Array.to_slice_mut]
    try simp only [ite_ok]
    step*
    repeat (first
      | (step)
      | (simp only [ite_ok]; (first | done | step))
      | (intro hc; repeat (obtain ⟨_, hc⟩ : _ × _ := hc); (try step*))
      | (split <;> (try step*))
      | (rename_i heq; split at heq <;> simp_all)
      | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply p25_0 <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals scalar_tac
  · trivial
@[local step]
theorem p25_47
(input : Slice Std.U8) (near : Array Std.U32 65536#usize)
  (head : Array Std.U32 131072#usize) (prev : Array Std.U32 32768#usize)
  (xs : Array Std.U32 131072#usize) (p0 : Std.Usize) (blen : Std.Usize)
  (max3 : Std.Usize) (mode : Std.Usize) (stride : Std.Usize) :
    slot.e_candidates input near head prev xs p0 blen max3 mode stride ⦃ fun _ => True ⦄ := YA1! slot.e_candidates
set_option hygiene false in
local notation "YA8!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat (measure := fun s => (32768) - s.2.val) (inv := fun _ => True)
  · rintro ⟨x0, x1⟩ _
    simp only [q1__, lift, Array.to_slice_mut]
    try simp only [ite_ok]
    step*
    repeat (first
      | (step)
      | (simp only [ite_ok]; (first | done | step))
      | (intro hc; repeat (obtain ⟨_, hc⟩ : _ × _ := hc); (try step*))
      | (split <;> (try step*))
      | (rename_i heq; split at heq <;> simp_all)
      | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply p25_0 <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals scalar_tac
  · trivial)
@[local step]
theorem p25_48
(input : Slice Std.U8) (p0 : Std.Usize) (blen : Std.Usize) (n : Std.Usize)
  (hist : Array Std.U32 256#usize) (k : Std.Usize) :
    slot.e_boot_loop0 input p0 blen n hist k ⦃ fun _ => True ⦄ := YA8! slot.e_boot_loop0 slot.e_boot_loop0.body
@[local step]
theorem p25_49
(litc : Array Std.U32 256#usize) (blen : Std.Usize)
  (hist : Array Std.U32 256#usize) (k : Std.Usize) :
    slot.e_boot_loop1 litc blen hist k ⦃ fun _ => True ⦄ := YA5! slot.e_boot_loop1 slot.e_boot_loop1.body
@[local step]
theorem p25_50
(lenc : Array Std.U32 512#usize) (le : Array Std.U8 512#usize) (bc : Std.U32)
  (k : Std.Usize) :
    slot.e_boot_loop2 lenc le bc k ⦃ fun _ => True ⦄ := YA6! slot.e_boot_loop2 slot.e_boot_loop2.body
@[local step]
theorem p25_51
(dc : Array Std.U32 32#usize) (de : Array Std.U8 32#usize) (k : Std.Usize) :
    slot.e_boot_loop3 dc de k ⦃ fun _ => True ⦄ := YA7! slot.e_boot_loop3 slot.e_boot_loop3.body
@[local step]
theorem p25_52
(input : Slice Std.U8) (litc : Array Std.U32 256#usize)
  (lenc : Array Std.U32 512#usize) (dc : Array Std.U32 32#usize)
  (le : Array Std.U8 512#usize) (de : Array Std.U8 32#usize) (p0 : Std.Usize)
  (blen : Std.Usize) (bc : Std.U32) :
    slot.e_boot input litc lenc dc le de p0 blen bc ⦃ fun _ => True ⦄ := YA1! slot.e_boot
@[local step]
theorem p25_53
(cost : Array Std.U32 65536#usize) (lenc : Array Std.U32 512#usize)
  (k : Std.Usize) (best : Std.U32) (bl : Std.Usize) (bd : Std.Usize)
  (lm : Std.Usize) (d : Std.Usize) (dcs : Std.U32) (l : Std.Usize) :
    slot.e_backward_loop0_loop0_loop0 cost lenc k best bl bd lm d dcs l ⦃ fun _ => True ⦄ := by
  rw [slot.e_backward_loop0_loop0_loop0]
  apply Std.loop.spec_decr_nat (measure := fun s => (259) - s.2.2.2.val) (inv := fun _ => True)
  · rintro ⟨x0, x1, x2, x3⟩ _
    simp only [slot.e_backward_loop0_loop0_loop0.body, lift, Array.to_slice_mut]
    try simp only [ite_ok]
    step*
    repeat (first
      | (step)
      | (simp only [ite_ok]; (first | done | step))
      | (intro hc; repeat (obtain ⟨_, hc⟩ : _ × _ := hc); (try step*))
      | (split <;> (try step*))
      | (rename_i heq; split at heq <;> simp_all)
      | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply p25_0 <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals scalar_tac
  · trivial
@[local step]
theorem p25_54
(xs : Array Std.U32 131072#usize) (cost : Array Std.U32 65536#usize)
  (lenc : Array Std.U32 512#usize) (dc : Array Std.U32 32#usize)
  (dlo : Array Std.U8 256#usize) (dhi : Array Std.U8 256#usize)
  (blen : Std.Usize) (stride : Std.Usize) (k : Std.Usize) (best : Std.U32)
  (bl : Std.Usize) (bd : Std.Usize) (s : Std.Usize) (lo : Std.Usize) :
    slot.e_backward_loop0_loop0 xs cost lenc dc dlo dhi blen stride k best bl bd s lo ⦃ fun _ => True ⦄ := by
  rw [slot.e_backward_loop0_loop0]
  apply Std.loop.spec_decr_nat (measure := fun s => (slot.E_NX.val) - s.2.2.2.1.val) (inv := fun _ => True)
  · rintro ⟨x0, x1, x2, x3, x4⟩ _
    simp only [slot.e_backward_loop0_loop0.body, lift, Array.to_slice_mut]
    try simp only [ite_ok]
    step*
    repeat (first
      | (step)
      | (simp only [ite_ok]; (first | done | step))
      | (intro hc; repeat (obtain ⟨_, hc⟩ : _ × _ := hc); (try step*))
      | (split <;> (try step*))
      | (rename_i heq; split at heq <;> simp_all)
      | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply p25_0 <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals scalar_tac
  · trivial
@[local step]
theorem p25_55
(input : Slice Std.U8) (xs : Array Std.U32 131072#usize)
  (cost : Array Std.U32 65536#usize) (chl : Array Std.U16 32768#usize)
  (chd : Array Std.U16 32768#usize) (litc : Array Std.U32 256#usize)
  (lenc : Array Std.U32 512#usize) (dc : Array Std.U32 32#usize)
  (dlo : Array Std.U8 256#usize) (dhi : Array Std.U8 256#usize)
  (p0 : Std.Usize) (blen : Std.Usize) (stride : Std.Usize) (k : Std.Usize) :
    slot.e_backward_loop0 input xs cost chl chd litc lenc dc dlo dhi p0 blen stride k ⦃ fun _ => True ⦄ := by
  rw [slot.e_backward_loop0]
  apply Std.loop.spec_decr_nat (measure := fun s => s.2.2.2.val) (inv := fun _ => True)
  · rintro ⟨x0, x1, x2, x3⟩ _
    simp only [slot.e_backward_loop0.body, lift, Array.to_slice_mut]
    try simp only [ite_ok]
    step*
    repeat (first
      | (step)
      | (simp only [ite_ok]; (first | done | step))
      | (intro hc; repeat (obtain ⟨_, hc⟩ : _ × _ := hc); (try step*))
      | (split <;> (try step*))
      | (rename_i heq; split at heq <;> simp_all)
      | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply p25_0 <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals scalar_tac
  · trivial
@[local step]
theorem p25_56
(input : Slice Std.U8) (xs : Array Std.U32 131072#usize)
  (cost : Array Std.U32 65536#usize) (chl : Array Std.U16 32768#usize)
  (chd : Array Std.U16 32768#usize) (litc : Array Std.U32 256#usize)
  (lenc : Array Std.U32 512#usize) (dc : Array Std.U32 32#usize)
  (dlo : Array Std.U8 256#usize) (dhi : Array Std.U8 256#usize)
  (p0 : Std.Usize) (blen : Std.Usize) (stride : Std.Usize) :
    slot.e_backward input xs cost chl chd litc lenc dc dlo dhi p0 blen stride ⦃ fun _ => True ⦄ := YA1! slot.e_backward
@[local step]
theorem p25_57
(lf : Array Std.U32 512#usize) (i : Std.Usize) :
    slot.e_count_loop0 lf i ⦃ fun _ => True ⦄ := YA2! slot.e_count_loop0 slot.e_count_loop0.body
@[local step]
theorem p25_58
(df : Array Std.U32 32#usize) (i : Std.Usize) :
    slot.e_count_loop1 df i ⦃ fun _ => True ⦄ := YA4! slot.e_count_loop1 slot.e_count_loop1.body
@[local step]
theorem p25_59
(input : Slice Std.U8) (chl : Array Std.U16 32768#usize)
  (chd : Array Std.U16 32768#usize) (lf : Array Std.U32 512#usize)
  (df : Array Std.U32 32#usize) (lc : Array Std.U8 512#usize)
  (dlo : Array Std.U8 256#usize) (dhi : Array Std.U8 256#usize)
  (p0 : Std.Usize) (blen : Std.Usize) (n : Std.Usize) (k : Std.Usize) :
    slot.e_count_loop2 input chl chd lf df lc dlo dhi p0 blen n k ⦃ fun _ => True ⦄ := by
  rw [slot.e_count_loop2]
  apply Std.loop.spec_decr_nat (measure := fun s => (32768) - s.2.2.val) (inv := fun _ => True)
  · rintro ⟨x0, x1, x2⟩ _
    simp only [slot.e_count_loop2.body, lift, Array.to_slice_mut]
    try simp only [ite_ok]
    step*
    repeat (first
      | (step)
      | (simp only [ite_ok]; (first | done | step))
      | (intro hc; repeat (obtain ⟨_, hc⟩ : _ × _ := hc); (try step*))
      | (split <;> (try step*))
      | (rename_i heq; split at heq <;> simp_all)
      | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply p25_0 <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals scalar_tac
  · trivial
@[local step]
theorem p25_60
(input : Slice Std.U8) (chl : Array Std.U16 32768#usize)
  (chd : Array Std.U16 32768#usize) (lf : Array Std.U32 512#usize)
  (df : Array Std.U32 32#usize) (lc : Array Std.U8 512#usize)
  (dlo : Array Std.U8 256#usize) (dhi : Array Std.U8 256#usize)
  (p0 : Std.Usize) (blen : Std.Usize) :
    slot.e_count input chl chd lf df lc dlo dhi p0 blen ⦃ fun _ => True ⦄ := YA1! slot.e_count
@[local step]
theorem p25_61
(input : Slice Std.U8) (seen : Array Std.U8 2048#usize)
  (cnt : Array Std.Usize 8#usize) (i : Std.Usize) :
    slot.e_quality_loop0 input seen cnt i ⦃ fun _ => True ⦄ := by
  rw [slot.e_quality_loop0]
  apply Std.loop.spec_decr_nat (measure := fun s => (4096) - s.2.2.val) (inv := fun _ => True)
  · rintro ⟨x0, x1, x2⟩ _
    simp only [slot.e_quality_loop0.body, lift, Array.to_slice_mut]
    try simp only [ite_ok]
    step*
    repeat (first
      | (step)
      | (simp only [ite_ok]; (first | done | step))
      | (intro hc; repeat (obtain ⟨_, hc⟩ : _ × _ := hc); (try step*))
      | (split <;> (try step*))
      | (rename_i heq; split at heq <;> simp_all)
      | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply p25_0 <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals scalar_tac
  · trivial
@[local step]
theorem p25_62
(cnt : Array Std.Usize 8#usize) (i : Std.Usize) (m : Std.Usize) :
    slot.e_quality_loop1 cnt i m ⦃ fun _ => True ⦄ := by
  rw [slot.e_quality_loop1]
  apply Std.loop.spec_decr_nat (measure := fun s => (8) - s.1.val) (inv := fun _ => True)
  · rintro ⟨x0, x1⟩ _
    simp only [slot.e_quality_loop1.body, lift, Array.to_slice_mut]
    try simp only [ite_ok]
    step*
    repeat (first
      | (step)
      | (simp only [ite_ok]; (first | done | step))
      | (intro hc; repeat (obtain ⟨_, hc⟩ : _ × _ := hc); (try step*))
      | (split <;> (try step*))
      | (rename_i heq; split at heq <;> simp_all)
      | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply p25_0 <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals scalar_tac
  · trivial
@[local step]
theorem p25_63
(input : Slice Std.U8) :
    slot.e_quality input ⦃ fun _ => True ⦄ := YA1! slot.e_quality
@[local step]
theorem p25_64
(input : Slice Std.U8) (k : Std.Usize) (hi : Std.Usize) (a1 : Std.Usize)
  (a2 : Std.Usize) (a4 : Std.Usize) :
    slot.e_pick_loop input k hi a1 a2 a4 ⦃ fun _ => True ⦄ := by
  rw [slot.e_pick_loop]
  apply Std.loop.spec_decr_nat (measure := fun s => (4104) - s.1.val) (inv := fun _ => True)
  · rintro ⟨x0, x1, x2, x3, x4⟩ _
    simp only [slot.e_pick_loop.body, lift, Array.to_slice_mut]
    try simp only [ite_ok]
    step*
    repeat (first
      | (step)
      | (simp only [ite_ok]; (first | done | step))
      | (intro hc; repeat (obtain ⟨_, hc⟩ : _ × _ := hc); (try step*))
      | (split <;> (try step*))
      | (rename_i heq; split at heq <;> simp_all)
      | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply p25_0 <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals scalar_tac
  · trivial
@[local step]
theorem p25_65
(input : Slice Std.U8) :
    slot.e_pick input ⦃ fun _ => True ⦄ := YA1! slot.e_pick
@[local step]
theorem p25_66
(chl : Array Std.U16 32768#usize) (blen : Std.Usize) (k : Std.Usize) :
    slot.e_literal_plan_loop chl blen k ⦃ fun _ => True ⦄ := YA8! slot.e_literal_plan_loop slot.e_literal_plan_loop.body
@[local step]
theorem p25_67
(chl : Array Std.U16 32768#usize) (blen : Std.Usize) :
    slot.e_literal_plan chl blen ⦃ fun _ => True ⦄ := YA1! slot.e_literal_plan
@[local step]
theorem p25_68
(head : Array Std.U32 131072#usize) (h : Std.Usize) (x : Std.U32) :
    slot.e_head_put head h x ⦃ fun _ => True ⦄ := YA1! slot.e_head_put
@[local step]
theorem p25_69
(input : Slice Std.U8) (head : Array Std.U32 131072#usize)
  (chl : Array Std.U16 32768#usize) (chd : Array Std.U16 32768#usize)
  (p0 : Std.Usize) (blen : Std.Usize) (k : Std.Usize) :
    slot.e_fallback_loop input head chl chd p0 blen k ⦃ fun _ => True ⦄ := by
  rw [slot.e_fallback_loop]
  apply Std.loop.spec_decr_nat (measure := fun s => (32768) - s.2.2.2.val) (inv := fun _ => True)
  · rintro ⟨x0, x1, x2, x3⟩ _
    simp only [slot.e_fallback_loop.body, lift, Array.to_slice_mut]
    try simp only [ite_ok]
    step*
    repeat (first
      | (step)
      | (simp only [ite_ok]; (first | done | step))
      | (intro hc; repeat (obtain ⟨_, hc⟩ : _ × _ := hc); (try step*))
      | (split <;> (try step*))
      | (rename_i heq; split at heq <;> simp_all)
      | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply p25_0 <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals scalar_tac
  · trivial
@[local step]
theorem p25_70
(input : Slice Std.U8) (head : Array Std.U32 131072#usize)
  (chl : Array Std.U16 32768#usize) (chd : Array Std.U16 32768#usize)
  (p0 : Std.Usize) (blen : Std.Usize) :
    slot.e_fallback input head chl chd p0 blen ⦃ fun _ => True ⦄ := YA1! slot.e_fallback
@[local step]
theorem p25_71
(input : Slice Std.U8) (p0 : Std.Usize) (blen : Std.Usize) (k : Std.Usize)
  (z : Std.Usize) :
    slot.e_zeros_loop input p0 blen k z ⦃ fun _ => True ⦄ := by
  rw [slot.e_zeros_loop]
  apply Std.loop.spec_decr_nat (measure := fun s => (1024) - s.1.val) (inv := fun _ => True)
  · rintro ⟨x0, x1⟩ _
    simp only [slot.e_zeros_loop.body, lift, Array.to_slice_mut]
    try simp only [ite_ok]
    step*
    repeat (first
      | (step)
      | (simp only [ite_ok]; (first | done | step))
      | (intro hc; repeat (obtain ⟨_, hc⟩ : _ × _ := hc); (try step*))
      | (split <;> (try step*))
      | (rename_i heq; split at heq <;> simp_all)
      | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply p25_0 <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals scalar_tac
  · trivial
@[local step]
theorem p25_72
(input : Slice Std.U8) (p0 : Std.Usize) (blen : Std.Usize) :
    slot.e_zeros input p0 blen ⦃ fun _ => True ⦄ := YA1! slot.e_zeros
@[local step]
theorem p25_73
(input : Slice Std.U8) (xs : Array Std.U32 131072#usize)
  (cost : Array Std.U32 65536#usize) (chl : Array Std.U16 32768#usize)
  (chd : Array Std.U16 32768#usize) (lf : Array Std.U32 512#usize)
  (df : Array Std.U32 32#usize) (lc : Array Std.U8 512#usize)
  (le : Array Std.U8 512#usize) (de : Array Std.U8 32#usize)
  (dlo : Array Std.U8 256#usize) (dhi : Array Std.U8 256#usize)
  (p0 : Std.Usize) (blen : Std.Usize) (rounds : Std.Usize) (hw : Std.U32)
  (penalty : Std.U32) (stride : Std.Usize) (litc : Array Std.U32 256#usize)
  (lenc : Array Std.U32 512#usize) (dc : Array Std.U32 32#usize)
  (pass : Std.Usize) :
    slot.e_refine_loop input xs cost chl chd lf df lc le de dlo dhi p0 blen rounds hw penalty stride litc lenc dc pass ⦃ fun _ => True ⦄ := by
  rw [slot.e_refine_loop]
  apply Std.loop.spec_decr_nat (measure := fun s => (rounds.val) - s.2.2.2.2.2.2.2.2.val) (inv := fun _ => True)
  · rintro ⟨x0, x1, x2, x3, x4, x5, x6, x7, x8⟩ _
    simp only [slot.e_refine_loop.body, lift, Array.to_slice_mut]
    try simp only [ite_ok]
    step*
    repeat (first
      | (step)
      | (simp only [ite_ok]; (first | done | step))
      | (intro hc; repeat (obtain ⟨_, hc⟩ : _ × _ := hc); (try step*))
      | (split <;> (try step*))
      | (rename_i heq; split at heq <;> simp_all)
      | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply p25_0 <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals scalar_tac
  · trivial
@[local step]
theorem p25_74
(input : Slice Std.U8) (xs : Array Std.U32 131072#usize)
  (cost : Array Std.U32 65536#usize) (chl : Array Std.U16 32768#usize)
  (chd : Array Std.U16 32768#usize) (lf : Array Std.U32 512#usize)
  (df : Array Std.U32 32#usize) (lc : Array Std.U8 512#usize)
  (le : Array Std.U8 512#usize) (de : Array Std.U8 32#usize)
  (dlo : Array Std.U8 256#usize) (dhi : Array Std.U8 256#usize)
  (p0 : Std.Usize) (blen : Std.Usize) (rounds : Std.Usize) (hw : Std.U32)
  (penalty : Std.U32) (stride : Std.Usize) :
    slot.e_refine input xs cost chl chd lf df lc le de dlo dhi p0 blen rounds hw penalty stride ⦃ fun _ => True ⦄ := YA1! slot.e_refine
@[local step]
theorem p25_75
(mode : Std.Usize) :
    slot.e_settings mode ⦃ fun _ => True ⦄ := YA1! slot.e_settings
@[local step]
theorem p25_76
(input : Slice Std.U8) (head : Array Std.U32 131072#usize) (p0 : Std.Usize)
  (blen : Std.Usize) (i : Std.Usize) (flag : Std.Usize) :
    slot.e_probe_loop input head p0 blen i flag ⦃ fun _ => True ⦄ := by
  rw [slot.e_probe_loop]
  apply Std.loop.spec_decr_nat (measure := fun s => (32772) - s.2.1.val) (inv := fun _ => True)
  · rintro ⟨x0, x1, x2⟩ _
    simp only [slot.e_probe_loop.body, lift, Array.to_slice_mut]
    try simp only [ite_ok]
    step*
    repeat (first
      | (step)
      | (simp only [ite_ok]; (first | done | step))
      | (intro hc; repeat (obtain ⟨_, hc⟩ : _ × _ := hc); (try step*))
      | (split <;> (try step*))
      | (rename_i heq; split at heq <;> simp_all)
      | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply p25_0 <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals scalar_tac
  · trivial
@[local step]
theorem p25_77
(input : Slice Std.U8) (head : Array Std.U32 131072#usize) (p0 : Std.Usize)
  (blen : Std.Usize) :
    slot.e_probe input head p0 blen ⦃ fun _ => True ⦄ := YA1! slot.e_probe
@[local step]
theorem p25_78
(input : Slice Std.U8) (head : Array Std.U32 131072#usize)
  (chl : Array Std.U16 32768#usize) (chd : Array Std.U16 32768#usize)
  (p0 : Std.Usize) (blen : Std.Usize) :
    slot.e_literal_fast input head chl chd p0 blen ⦃ fun _ => True ⦄ := YA1! slot.e_literal_fast
@[local step]
theorem p25_79
(input : Slice Std.U8) (head : Array Std.U32 131072#usize)
  (xs : Array Std.U32 131072#usize) (cost : Array Std.U32 65536#usize)
  (chl : Array Std.U16 32768#usize) (chd : Array Std.U16 32768#usize)
  (lf : Array Std.U32 512#usize) (df : Array Std.U32 32#usize)
  (lc : Array Std.U8 512#usize) (le : Array Std.U8 512#usize)
  (de : Array Std.U8 32#usize) (dlo : Array Std.U8 256#usize)
  (dhi : Array Std.U8 256#usize) (p0 : Std.Usize) (blen : Std.Usize)
  (cfg : (Std.Usize × Std.U32 × Std.U32 × Std.Usize × Std.U32 ×
  Std.Usize)) (flag : Std.Usize) :
    slot.e_finish input head xs cost chl chd lf df lc le de dlo dhi p0 blen cfg flag ⦃ fun _ => True ⦄ := YA1! slot.e_finish
@[local step]
theorem p25_80
(input : Slice Std.U8) (near : Array Std.U32 65536#usize)
  (head : Array Std.U32 131072#usize) (prev : Array Std.U32 32768#usize)
  (xs : Array Std.U32 131072#usize) (cost : Array Std.U32 65536#usize)
  (chl : Array Std.U16 32768#usize) (chd : Array Std.U16 32768#usize)
  (lf : Array Std.U32 512#usize) (df : Array Std.U32 32#usize)
  (lc : Array Std.U8 512#usize) (le : Array Std.U8 512#usize)
  (de : Array Std.U8 32#usize) (dlo : Array Std.U8 256#usize)
  (dhi : Array Std.U8 256#usize) (mode : Std.Usize) (p0 : Std.Usize)
  (blen : Std.Usize) :
    slot.e_plan input near head prev xs cost chl chd lf df lc le de dlo dhi mode p0 blen ⦃ fun _ => True ⦄ := YA1! slot.e_plan
theorem verified_spec (input : Slice Std.U8) (pos d ch k blen : Std.Usize)
    (hlen : pos.val + (blen.val - k.val) ≤ input.length) (hk : k.val ≤ blen.val)
    (hb : blen.val ≤ 32768) :
    slot.e_verified input pos d ch k blen ⦃ fun b => b = true →
      3 ≤ ch.val ∧ ch.val ≤ 258 ∧ 1 ≤ d.val ∧ d.val ≤ 32768 ∧ d.val ≤ pos.val ∧
      k.val + ch.val ≤ blen.val ∧ Matches input (pos.val - d.val) pos.val ch.val ⦄ := by
  rw [slot.e_verified]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  step*
theorem emit_loop_spec (input : Slice Std.U8) (out0 : Slice Std.U32)
    (chl chd : Array Std.U16 32768#usize) (p0 blen ntok0 k0 : Std.Usize)
    (hblen : p0.val + blen.val ≤ input.length) (hb : blen.val ≤ 32768)
    (hout : input.length ≤ out0.length)
    (hk : k0.val ≤ blen.val) (hntok : ntok0.val ≤ p0.val + k0.val)
    (hdec : LZ77.decode (toks out0 ntok0.val) = some ((bytes input).take (p0.val + k0.val))) :
    slot.e_emit_loop input out0 chl chd p0 blen ntok0 k0 ⦃ fun r =>
      r.1.val ≤ p0.val + blen.val ∧ r.2.length = out0.length ∧
      LZ77.decode (toks r.2 r.1.val) = some ((bytes input).take (p0.val + blen.val)) ⦄ := U147! slot.e_emit_loop slot.e_emit_loop.body
@[local step]
theorem emit_spec (input : Slice Std.U8) (out : Slice Std.U32)
    (chl chd : Array Std.U16 32768#usize) (ntok p0 blen : Std.Usize)
    (hblen : p0.val + blen.val ≤ input.length) (hb : blen.val ≤ 32768)
    (hout : input.length ≤ out.length) (hntok : ntok.val ≤ p0.val)
    (hdec : LZ77.decode (toks out ntok.val) = some ((bytes input).take p0.val)) :
    slot.e_emit input out chl chd ntok p0 blen ⦃ fun r =>
      r.1.val ≤ p0.val + blen.val ∧ r.2.length = out.length ∧
      LZ77.decode (toks r.2 r.1.val) = some ((bytes input).take (p0.val + blen.val)) ⦄ := by
  rw [slot.e_emit]
  apply emit_loop_spec input out chl chd p0 blen ntok 0#usize hblen hb hout
    (by scalar_tac) (by simpa using hntok)
  simpa using hdec
@[local step]
theorem parse_loop_spec (input : Slice Std.U8) (out0 : Slice Std.U32) (n mode : Std.Usize)
    (lc le : Array Std.U8 512#usize) (dlo dhi : Array Std.U8 256#usize)
    (de : Array Std.U8 32#usize) (near : Array Std.U32 65536#usize) (head : Array Std.U32 131072#usize)
    (prev : Array Std.U32 32768#usize) (xs : Array Std.U32 131072#usize)
    (cost : Array Std.U32 65536#usize) (chl chd : Array Std.U16 32768#usize)
    (lf : Array Std.U32 512#usize) (df : Array Std.U32 32#usize) (ntok0 p00 : Std.Usize)
    (hn : n.val = input.length) (hout : input.length ≤ out0.length)
    (hpos : p00.val ≤ n.val) (hntok : ntok0.val ≤ p00.val)
    (hdec : LZ77.decode (toks out0 ntok0.val) = some ((bytes input).take p00.val)) :
    slot.e_parse_loop input out0 n mode lc le dlo dhi de near head prev xs cost chl chd lf df ntok0 p00
      ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out0.length ∧
      LZ77.decode (toks r.2 r.1.val) = some (bytes input) ⦄ := by
  rw [slot.e_parse_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => n.val - s.2.2.2.2.2.2.2.2.2.2.2.val)
    (inv := fun s =>
      s.2.2.2.2.2.2.2.2.2.2.2.val ≤ n.val ∧
      s.2.2.2.2.2.2.2.2.2.2.1.val ≤ s.2.2.2.2.2.2.2.2.2.2.2.val ∧
      s.1.length = out0.length ∧
      LZ77.decode (toks s.1 s.2.2.2.2.2.2.2.2.2.2.1.val) =
        some ((bytes input).take s.2.2.2.2.2.2.2.2.2.2.2.val))
  · rintro ⟨out, nr, hd, pv, xx, cs, cl, cd, ll, dd, ntok, p0⟩ ⟨hp, hnt, hlen, hde⟩
    simp only at hp hnt hlen hde
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.e_parse_loop.body]
    split
    case isTrue hlt =>
      step*
      simp only [ite_ok]
      have hbl : (if rest > slot.E_BLOCK then slot.E_BLOCK else rest).val ≤ 32768 ∧
          (if rest > slot.E_BLOCK then slot.E_BLOCK else rest).val ≤ rest.val ∧
          1 ≤ (if rest > slot.E_BLOCK then slot.E_BLOCK else rest).val := by
        split <;> scalar_tac
      generalize (if rest > slot.E_BLOCK then slot.E_BLOCK else rest) = blen at hbl ⊢
      obtain ⟨hb1, hb2, hb3⟩ := hbl
      step*
      refine ⟨by scalar_tac, by scalar_tac, ntok1_post2.trans hlen, ?_, by scalar_tac⟩
      rw [ntok1_post3, show p01.val = p0.val + blen.val by scalar_tac]
    case isFalse hge =>
      have hpn : p0.val = n.val := by scalar_tac
      refine ⟨by scalar_tac, hlen, ?_⟩
      rw [hde, hpn, hn]
      simp
  · exact ⟨hpos, hntok, rfl, hdec⟩
theorem parse_spec (input : Slice Std.U8) (out : Slice Std.U32)
    (hlen : input.length ≤ out.length) :
    slot.e_parse input out ⦃ fun r =>
      r.1.val ≤ input.length ∧ r.2.length = out.length ∧
      LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
  rw [slot.e_parse]
  simp only [ite_ok]
  step*
  all_goals simp_all [LZ77.Valid, toks, LZ77.decode]
end EE
end X239

@[local step]
theorem e_parse_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) :
    slot.e_parse input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧
      LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ :=
  X239.EE.parse_spec input out hlen



theorem parse_spec (input : Slice Std.U8) (out : Slice Std.U32)
    (hlen : input.length ≤ out.length) :
    slot.parse input out ⦃ fun r =>
      r.1.val ≤ input.length ∧
      r.2.length = out.length ∧
      LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
  rw [slot.parse]
  step*
  all_goals (first | assumption | exact SV0! |
    (refine ⟨by assumption, by assumption, ?_⟩; unfold LZ77.Valid; assumption) |
    (refine ⟨by assumption, by exact SV0!, ?_⟩; unfold LZ77.Valid; assumption))

end Submission
