import Lz77
import Slot
set_option linter.unusedSimpArgs false
set_option linter.unusedVariables false
set_option linter.unusedTactic false
set_option linter.unreachableTactic false
namespace Submission
open Aeneas Aeneas.Std Result ControlFlow
open LZ77 (toks bytes)
set_option maxRecDepth 8192
theorem r70_ite_true_spec {α : Type} (c : Prop) [Decidable c] (A B : Result α)
 (hA : c → A ⦃ fun _ => True ⦄) (hB : ¬c → B ⦃ fun _ => True ⦄) :
 (if c then A else B) ⦃ fun _ => True ⦄ := by
 by_cases h : c
 · rw [if_pos h]; exact hA h
 · rw [if_neg h]; exact hB h
set_option hygiene false in
local notation "C1251!" => (by
  intro j hj
  rw [Std.Array.repeat_val, List.getElem!_eq_getElem?_getD,
    List.getElem?_replicate_of_lt (by simpa using hj)]
  rfl)
set_option hygiene false in
local notation "C1252!" => (by
  have := h a.val (by simpa using ha)
  rw [getElem!_pos cnt.val a.val ha, ← hx] at this
  exact this)
set_option hygiene false in
local notation "C1253!" => (by
  have hl : i.val < cnt.val.length := by simp; omega
  have := Std.Array.index_usize_spec cnt i (by simpa using hl)
  apply Std.WP.spec_mono this
  intro x hx
  refine ⟨by rw [getElem!_pos cnt.val i.val hl]; exact hx, CntBound.get h i x hl hx⟩)
set_option hygiene false in
local notation "C1254!" => (by
  intro j hj
  rw [Std.Array.set_val_eq]
  by_cases hja : a.val = j
  · subst hja
    have hlen : a.val < cnt.val.length := by simp; omega
    rw [List.getElem!_eq_getElem?_getD, List.getElem?_set_self hlen]
    exact hv
  · rw [List.getElem!_eq_getElem?_getD, List.getElem?_set_ne hja, ← List.getElem!_eq_getElem?_getD]
    exact le_trans (h j hj) (by omega))
set_option hygiene false in
local notation "C1255!" => (by
  rw [ha, ht1]
  exact CntBound.update hc x v hv)
namespace E_M
open Aeneas Aeneas.Std Result ControlFlow
set_option maxRecDepth 8192
set_option maxHeartbeats 4000000
set_option linter.unusedVariables false
open LZ77 (toks bytes bytes_length bytes_getElem! toks_update bytes_congr
  Matches Found emit_lit emit_match ite_ok)
open LZ77 (decode emit copyN tokLen tokDist MATCH_BASE TOK_LIMIT decode_snoc copyN_length)
def CntBound (cnt : Array Std.U32 256#usize) (T : Nat) : Prop :=
  ∀ j : Nat, j < 256 → (cnt.val[j]!).val ≤ T
theorem CntBound.init : CntBound (Std.Array.repeat 256#usize 0#u32) 0 := C1251!
theorem CntBound.get {cnt : Array Std.U32 256#usize} {T : Nat} (h : CntBound cnt T)
    (a : Std.Usize) (x : Std.U32) (ha : a.val < cnt.val.length) (hx : x = cnt.val[a.val]) :
    x.val ≤ T := C1252!
@[local step]
theorem cnt_index_spec (cnt : Array Std.U32 256#usize) (T : Nat) (h : CntBound cnt T)
    (i : Std.Usize) (hi : i.val < 256) :
    Std.Array.index_usize cnt i ⦃ fun x => x = cnt.val[i.val]! ∧ x.val ≤ T ⦄ := C1253!
theorem CntBound.update {cnt : Array Std.U32 256#usize} {T : Nat} (h : CntBound cnt T)
    (a : Std.Usize) (v : Std.U32) (hv : v.val ≤ T + 1) : CntBound (cnt.set a v) (T + 1) := C1254!
theorem CntBound.step {cnt a : Array Std.U32 256#usize} {T : Nat} {x : Std.Usize}
    {v tot1 : Std.U32} (hc : CntBound cnt T) (ha : a = cnt.set x v) (hv : v.val ≤ T + 1)
    (ht1 : tot1.val = T + 1) : CntBound a tot1.val := C1255!
theorem CntBound.mono {cnt : Array Std.U32 256#usize} {T T' : Nat} (h : CntBound cnt T)
    (hT : T ≤ T') : CntBound cnt T' := fun j hj => le_trans (h j hj) hT
@[local step]
theorem lift_spec {α : Type} (x : α) : lift x ⦃ fun y => y = x ⦄ := by
  simp [lift]
theorem format_id_loop_spec (s : Slice Std.U8) (n : Std.Usize) (cnt : Array Std.U32 256#usize)
    (step i : Std.Usize) (tot : Std.U32) (hn : n.val = s.length) (hc : CntBound cnt tot.val)
    (ht : tot.val ≤ 4097) :
    slot.format_id_loop s n cnt step i tot ⦃ fun r => CntBound r.1 r.2.val ∧ r.2.val ≤ 4097 ⦄ := by
  rw [slot.format_id_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun r => 4097 - r.2.2.val)
    (inv := fun r => CntBound r.1 r.2.2.val ∧ r.2.2.val ≤ 4097)
  · rintro ⟨cnt, i, tot⟩ ⟨hc, ht⟩
    simp only at hc ht
    simp only [slot.format_id_loop.body]
    step*
    all_goals first
      | exact ⟨hc, ht⟩
      | exact ⟨CntBound.step hc (by assumption) (by scalar_tac) (by scalar_tac), by scalar_tac,
          by scalar_tac⟩
  · exact ⟨hc, ht⟩
@[local step]
theorem format_id_spec (s : Slice Std.U8) : slot.format_id s ⦃ fun _ => True ⦄ := by
  rw [slot.format_id]
  step*
  apply Std.WP.spec_bind (format_id_loop_spec s (Std.Slice.len s) _ step 0#usize 0#u32 (by simp)
    (by simpa using CntBound.init) (by simp))
  rintro ⟨cnt1, tot⟩ ⟨hc, ht⟩
  simp only at hc ht
  have hc4 := CntBound.mono hc ht
  clear hc
  step*
  repeat' (split <;> step*)
end E_M
attribute [local step] E_M.format_id_spec
set_option hygiene false in
local notation "C1256!" => (by
  by_cases h : c
  · rw [if_pos h]; exact ha h
  · rw [if_neg h]; exact hb h)
set_option hygiene false in
local notation "C1257!" => (by
  by_cases h : c
  · rw [if_pos h]; exact hA h
  · rw [if_neg h]; exact hB h)
set_option hygiene false in
local notation "C1258!" q0__:max => (by
  rw [q0__]
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals scalar_tac)
set_option hygiene false in
local notation "C1259!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun s => 40 - s.2.2.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1, x2⟩ _
    simp only [q1__, lift, Array.to_slice_mut]
    step*
    repeat (first
      | (intro hc; (try step*))
      | (split <;> (try step*))
      | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply spec_ite_cut <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals scalar_tac
  · trivial)
set_option hygiene false in
local notation "C12510!" q0__:max => (by
  rw [q0__]
  step*
  repeat (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals scalar_tac)
set_option hygiene false in
local notation "C12512!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun s => 29 - s.2.2.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1, x2⟩ _
    simp only [q1__, lift, Array.to_slice_mut]
    step*
    repeat (first
      | (intro hc; (try step*))
      | (split <;> (try step*))
      | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply spec_ite_cut <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals scalar_tac
  · trivial)
set_option hygiene false in
local notation "C12513!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun s => 30 - s.2.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1⟩ _
    simp only [q1__, lift, Array.to_slice_mut]
    step*
    repeat (first
      | (intro hc; (try step*))
      | (split <;> (try step*))
      | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply spec_ite_cut <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals scalar_tac
  · trivial)
set_option hygiene false in
local notation "C12514!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun s => n.val - s.2.2.1.val)
    (inv := fun s =>
      s.2.2.1.val ≤ n.val ∧ s.2.2.2.val ≤ s.2.2.1.val ∧ s.1.length = out0.length ∧
      LZ77.decode (toks s.1 s.2.2.2.val) = some ((bytes input).take s.2.2.1.val))
  · rintro ⟨out, head, pos, ntok⟩ ⟨hpn, hnt, hlen, hde⟩
    simp only at hpn hnt hlen hde
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [q1__, lift, Array.to_slice_mut, alloc.vec.Vec.deref_mut, bind_tc_ok]
    split
    case isTrue hlt =>
      step*
      all_goals (repeat (first
        | (refine ⟨by scalar_tac, by scalar_tac, by assumption, by assumption, by scalar_tac⟩)
        | (intro hc; (try step*))
        | (casesm* _ × _; (try simp only []); (try step*))
        | (split <;> (try step*))
        | (step <;> (try step*))))
      all_goals (try scalar_tac)
    case isFalse hge =>
      have hpn' : pos.val = input.length := by scalar_tac
      refine ⟨by scalar_tac, hlen, ?_⟩
      unfold LZ77.Valid
      rw [hde, hpn']
      simp
  · exact ⟨hp, hntok, rfl, hdec⟩)
namespace EO
open Aeneas Aeneas.Std Result ControlFlow
open LZ77 (toks bytes)
set_option maxRecDepth 8192
set_option maxHeartbeats 4000000
namespace EA
open Aeneas Aeneas.Std Result ControlFlow
set_option maxRecDepth 8192
set_option maxHeartbeats 4000000
open LZ77 (toks bytes bytes_length bytes_getElem! Matches emit_lit emit_match ite_ok)
theorem decode_nil (input : Slice Std.U8) (out : Slice Std.U32) :
    LZ77.decode (toks out (0#usize).val) = some ((bytes input).take (0#usize).val) := by
  simp [toks, LZ77.decode]
theorem valid_of_decode {input : Slice Std.U8} {o : Slice Std.U32} {t p : Std.Usize}
    (hde : LZ77.decode (toks o t.val) = some ((bytes input).take p.val)) (hp : p.val = input.length) :
    LZ77.Valid (bytes input) (toks o t.val) := by
  unfold LZ77.Valid
  rw [hde, hp]
  simp
theorem spec_ite_cut {α : Type} (c : Prop) [Decidable c] (a b : Result α) (Q : α → Prop)
    (ha : c → a ⦃ Q ⦄) (hb : ¬c → b ⦃ Q ⦄) : (if c then a else b) ⦃ Q ⦄ := C1256!
theorem ite_prod_spec {α β : Type} (c : Prop) [Decidable c] (A B : Result (α × β))
    (hA : c → A ⦃ fun _ => True ⦄) (hB : ¬c → B ⦃ fun _ => True ⦄) :
    (if c then A else B) ⦃ fun _ => True ⦄ := C1257!
theorem ite_true_spec {α : Type} (c : Prop) [Decidable c] (A B : Result α)
    (hA : c → A ⦃ fun _ => True ⦄) (hB : ¬c → B ⦃ fun _ => True ⦄) :
    (if c then A else B) ⦃ fun _ => True ⦄ := C1257!
section
attribute [local step] Submission.r70_ite_true_spec
theorem ld8_spec (input : Slice Std.U8) (p : Std.Usize) :
    slot.o_a_ld8 input p ⦃ fun _ => True ⦄ := C1258! slot.o_a_ld8
end
attribute [local step] ld8_spec
section
attribute [local step] Submission.r70_ite_true_spec
theorem first_diff_spec (x : Std.U64) :
    slot.o_a_first_diff x ⦃ fun _ => True ⦄ := C1258! slot.o_a_first_diff
end
attribute [local step] first_diff_spec
section
attribute [local step] Submission.r70_ite_true_spec
theorem fast_len_loop_spec (input : Slice Std.U8) (a : Std.Usize) (b : Std.Usize) (cap : Std.Usize) (l : Std.Usize) (go : Std.Usize) (it : Std.Usize)  :
    slot.o_a_fast_len_loop input a b cap l go it ⦃ fun _ => True ⦄ := C1259! slot.o_a_fast_len_loop slot.o_a_fast_len_loop.body
end
attribute [local step] fast_len_loop_spec
section
attribute [local step] Submission.r70_ite_true_spec
theorem fast_len_spec (input : Slice Std.U8) (a : Std.Usize) (b : Std.Usize) (cap : Std.Usize) :
    slot.o_a_fast_len input a b cap ⦃ fun _ => True ⦄ := C12510! slot.o_a_fast_len
end
attribute [local step] fast_len_spec
section
attribute [local step] Submission.r70_ite_true_spec
theorem fast_len2_loop_spec (input : Slice Std.U8) (a : Std.Usize) (b : Std.Usize) (cap : Std.Usize) (l : Std.Usize) (go : Std.Usize) (it : Std.Usize)  :
    slot.o_a_fast_len2_loop input a b cap l go it ⦃ fun _ => True ⦄ := C1259! slot.o_a_fast_len2_loop slot.o_a_fast_len2_loop.body
end
attribute [local step] fast_len2_loop_spec
section
attribute [local step] Submission.r70_ite_true_spec
theorem fast_len2_spec (input : Slice Std.U8) (a : Std.Usize) (b : Std.Usize) (cap : Std.Usize) :
    slot.o_a_fast_len2 input a b cap ⦃ fun _ => True ⦄ := C12510! slot.o_a_fast_len2
end
attribute [local step] fast_len2_spec
section
attribute [local step] Submission.r70_ite_true_spec
theorem fast_len3_loop_spec (input : Slice Std.U8) (a : Std.Usize) (b : Std.Usize) (cap : Std.Usize) (l : Std.Usize) (go : Std.Usize) (it : Std.Usize)  :
    slot.o_a_fast_len3_loop input a b cap l go it ⦃ fun _ => True ⦄ := C1259! slot.o_a_fast_len3_loop slot.o_a_fast_len3_loop.body
end
attribute [local step] fast_len3_loop_spec
section
attribute [local step] Submission.r70_ite_true_spec
theorem fast_len3_spec (input : Slice Std.U8) (a : Std.Usize) (b : Std.Usize) (cap : Std.Usize) :
    slot.o_a_fast_len3 input a b cap ⦃ fun _ => True ⦄ := C12510! slot.o_a_fast_len3
end
attribute [local step] fast_len3_spec
@[local step]
theorem hashp_spec (input : Slice Std.U8) (p : Std.Usize) :
    slot.o_a_hashp input p ⦃ fun r => r.val < 65536 ⦄ := C1258! slot.o_a_hashp
@[local step]
theorem hashl_spec (input : Slice Std.U8) (p : Std.Usize) :
    slot.o_a_hashl input p ⦃ fun r => r.val < 65536 ⦄ := C1258! slot.o_a_hashl
set_option hygiene false in
local notation "C12511!" q0__:max => (by
  rw [q0__]
  try simp only [lift, Array.to_slice_mut, ite_ok]
  step*
  repeat (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals scalar_tac)
section
attribute [local step] Submission.r70_ite_true_spec
theorem eval_spec (input : Slice Std.U8) (p : Std.Usize) (cs : Std.Usize) (cl : Std.Usize) :
    slot.o_a_eval input p cs cl ⦃ fun _ => True ⦄ := C12511! slot.o_a_eval
end
attribute [local step] eval_spec
section
attribute [local step] Submission.r70_ite_true_spec
theorem eval2_spec (input : Slice Std.U8) (p : Std.Usize) (cs : Std.Usize) (cl : Std.Usize) (floor : Std.Usize) :
    slot.o_a_eval2 input p cs cl floor ⦃ fun _ => True ⦄ := C12511! slot.o_a_eval2
end
attribute [local step] eval2_spec
section
attribute [local step] Submission.r70_ite_true_spec
theorem eval3_spec (input : Slice Std.U8) (p : Std.Usize) (cs : Std.Usize) (cl : Std.Usize) (floor : Std.Usize) :
    slot.o_a_eval3 input p cs cl floor ⦃ fun _ => True ⦄ := C12511! slot.o_a_eval3
end
attribute [local step] eval3_spec
section
attribute [local step] Submission.r70_ite_true_spec
theorem insert_range_loop_spec (input : Slice Std.U8) (head : Array Std.U32 131072#usize) («to» : Std.Usize) (n : Std.Usize) (p : Std.Usize) (hn : n.val = input.length) :
    slot.o_a_insert_range_loop input head «to» n p ⦃ fun _ => True ⦄ := by
  rw [slot.o_a_insert_range_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => «to».val - s.2.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1⟩ _
    simp only [slot.o_a_insert_range_loop.body, lift, Array.to_slice_mut]
    step*
    repeat (first
      | (intro hc; (try step*))
      | (split <;> (try step*))
      | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply spec_ite_cut <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals scalar_tac
  · trivial
end
attribute [local step] insert_range_loop_spec
section
attribute [local step] Submission.r70_ite_true_spec
theorem insert_range_spec (input : Slice Std.U8) (head : Array Std.U32 131072#usize) («from» : Std.Usize) («to» : Std.Usize) :
    slot.o_a_insert_range input head «from» «to» ⦃ fun _ => True ⦄ := C12510! slot.o_a_insert_range
end
attribute [local step] insert_range_spec
section
attribute [local step] Submission.r70_ite_true_spec
theorem insert_range2_loop_spec (TS_ : Std.Usize) (input : Slice Std.U8) (head : Array Std.U32 131072#usize) («to» : Std.Usize) (n : Std.Usize) (p : Std.Usize) (c : Std.Usize) (hn : n.val = input.length) :
    slot.o_a_insert_range2_loop TS_ input head «to» n p c ⦃ fun _ => True ⦄ := by
  rw [slot.o_a_insert_range2_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => «to».val - s.2.2.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1, x2⟩ _
    simp only [slot.o_a_insert_range2_loop.body, lift, Array.to_slice_mut]
    step*
    repeat (first
      | (intro hc; (try step*))
      | (split <;> (try step*))
      | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply spec_ite_cut <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals scalar_tac
  · trivial
end
attribute [local step] insert_range2_loop_spec
section
attribute [local step] Submission.r70_ite_true_spec
theorem insert_range2_spec (TS_ : Std.Usize) (input : Slice Std.U8) (head : Array Std.U32 131072#usize) («from» : Std.Usize) («to» : Std.Usize) :
    slot.o_a_insert_range2 TS_ input head «from» «to» ⦃ fun _ => True ⦄ := C12510! slot.o_a_insert_range2
end
attribute [local step] insert_range2_spec
section
attribute [local step] Submission.r70_ite_true_spec
theorem insert_match_spec (IH_ : Std.Usize) (IT_ : Std.Usize) (TS_ : Std.Usize) (input : Slice Std.U8) (head : Array Std.U32 131072#usize) («from» : Std.Usize) («to» : Std.Usize) :
    slot.o_a_insert_match IH_ IT_ TS_ input head «from» «to» ⦃ fun _ => True ⦄ := C1258! slot.o_a_insert_match
end
attribute [local step] insert_match_spec
section
attribute [local step] Submission.r70_ite_true_spec
theorem run_len_spec (ACC_ : Std.U64) (k : Std.Usize) :
    slot.o_a_run_len ACC_ k ⦃ fun _ => True ⦄ := C1258! slot.o_a_run_len
end
attribute [local step] run_len_spec
section
attribute [local step] Submission.r70_ite_true_spec
theorem q8ok_spec (q : Std.Usize) (d : Std.Usize) :
    slot.o_a_q8ok q d ⦃ fun _ => True ⦄ := C1258! slot.o_a_q8ok
end
attribute [local step] q8ok_spec
section
attribute [local step] Submission.r70_ite_true_spec
theorem bext_loop_spec (input : Slice Std.U8) (p : Std.Usize) (d : Std.Usize) (lim : Std.Usize) (e : Std.Usize) (go : Std.Usize) (it : Std.Usize)  :
    slot.o_a_bext_loop input p d lim e go it ⦃ fun _ => True ⦄ := C1259! slot.o_a_bext_loop slot.o_a_bext_loop.body
end
attribute [local step] bext_loop_spec
section
attribute [local step] Submission.r70_ite_true_spec
theorem bext_spec (input : Slice Std.U8) (lo : Std.Usize) (p : Std.Usize) (d : Std.Usize) (l : Std.Usize) :
    slot.o_a_bext input lo p d l ⦃ fun _ => True ⦄ := C12510! slot.o_a_bext
end
attribute [local step] bext_spec
section
attribute [local step] Submission.r70_ite_true_spec
theorem back1_spec (input : Slice Std.U8) (q : Std.Usize) (d : Std.Usize) :
    slot.o_a_back1 input q d ⦃ fun _ => True ⦄ := C12510! slot.o_a_back1
end
attribute [local step] back1_spec
section
attribute [local step] Submission.r70_ite_true_spec
theorem tab_step_spec (head : Array Std.U32 131072#usize) (hs : Std.Usize) (hl : Std.Usize) (hs1 : Std.Usize) (hl1 : Std.Usize) (p : Std.Usize) :
    slot.o_a_tab_step head hs hl hs1 hl1 p ⦃ fun _ => True ⦄ := C1258! slot.o_a_tab_step
end
attribute [local step] tab_step_spec
section
attribute [local step] Submission.r70_ite_true_spec
theorem tab_step2_spec (head : Array Std.U32 131072#usize) (hs : Std.Usize) (hl : Std.Usize) (q : Std.Usize) :
    slot.o_a_tab_step2 head hs hl q ⦃ fun _ => True ⦄ := C1258! slot.o_a_tab_step2
end
attribute [local step] tab_step2_spec
section
attribute [local step] Submission.r70_ite_true_spec
theorem scan_loop_spec (ACC_ : Std.U64) (input : Slice Std.U8) (head : Array Std.U32 131072#usize) (n : Std.Usize) (p : Std.Usize) (res : Std.Usize) (it : Std.Usize) (hs : Std.Usize) (hl : Std.Usize) (cs : Std.Usize) (cl : Std.Usize) (hn : n.val = input.length) :
    slot.o_a_scan_loop ACC_ input head n p res it hs hl cs cl ⦃ fun _ => True ⦄ := by
  rw [slot.o_a_scan_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => n.val - s.2.2.2.1.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1, x2, x3, x4, x5, x6, x7⟩ _
    simp only [slot.o_a_scan_loop.body, lift, Array.to_slice_mut]
    step*
    repeat (first
      | (intro hc; (try step*))
      | (split <;> (try step*))
      | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply spec_ite_cut <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals scalar_tac
  · trivial
end
attribute [local step] scan_loop_spec
section
attribute [local step] Submission.r70_ite_true_spec
theorem scan_spec (ACC_ : Std.U64) (input : Slice Std.U8) (head : Array Std.U32 131072#usize) (pos : Std.Usize) :
    slot.o_a_scan ACC_ input head pos ⦃ fun _ => True ⦄ := C1258! slot.o_a_scan
end
attribute [local step] scan_spec
section
attribute [local step] Submission.r70_ite_true_spec
theorem lazy_step_spec (LZT_ : Std.Usize) (input : Slice Std.U8) (head : Array Std.U32 131072#usize) (m : Std.U64) :
    slot.o_a_lazy_step LZT_ input head m ⦃ fun _ => True ⦄ := C1258! slot.o_a_lazy_step
end
attribute [local step] lazy_step_spec
section
attribute [local step] Submission.r70_ite_true_spec
theorem lazy_more_loop_spec (LZT_ : Std.Usize) (input : Slice Std.U8) (head : Array Std.U32 131072#usize) (m : Std.U64) (go : Std.Usize) (it : Std.Usize)  :
    slot.o_a_lazy_more_loop LZT_ input head m go it ⦃ fun _ => True ⦄ := by
  rw [slot.o_a_lazy_more_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => slot.O_A_LZN.val - s.2.2.2.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1, x2, x3⟩ _
    simp only [slot.o_a_lazy_more_loop.body, lift, Array.to_slice_mut]
    step*
    repeat (first
      | (intro hc; (try step*))
      | (split <;> (try step*))
      | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply spec_ite_cut <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals scalar_tac
  · trivial
end
attribute [local step] lazy_more_loop_spec
section
attribute [local step] Submission.r70_ite_true_spec
theorem find_spec (ACC_ : Std.U64) (LZT_ : Std.Usize) (input : Slice Std.U8) (head : Array Std.U32 131072#usize) (pos : Std.Usize) :
    slot.o_a_find ACC_ LZT_ input head pos ⦃ fun _ => True ⦄ := C12511! slot.o_a_find
end
attribute [local step] find_spec
def w8 (input : Slice Std.U8) (p : Nat) : Nat :=
  (input.val[p]!).val + (input.val[p + 1]!).val * 256 + (input.val[p + 2]!).val * 65536 +
  (input.val[p + 3]!).val * 16777216 + (input.val[p + 4]!).val * 4294967296 +
  (input.val[p + 5]!).val * 1099511627776 + (input.val[p + 6]!).val * 281474976710656 +
  (input.val[p + 7]!).val * 72057594037927936
def w4 (input : Slice Std.U8) (p : Nat) : Nat :=
  (input.val[p]!).val + (input.val[p + 1]!).val * 256 + (input.val[p + 2]!).val * 65536 +
  (input.val[p + 3]!).val * 16777216
theorem w8_bytes (input : Slice Std.U8) (p q : Nat) (h : w8 input p = w8 input q) :
    ∀ k, k < 8 → input.val[q + k]! = input.val[p + k]! := by
  unfold w8 at h
  have b0 := (input.val[p]!).hBounds
  have b1 := (input.val[p + 1]!).hBounds
  have b2 := (input.val[p + 2]!).hBounds
  have b3 := (input.val[p + 3]!).hBounds
  have b4 := (input.val[p + 4]!).hBounds
  have b5 := (input.val[p + 5]!).hBounds
  have b6 := (input.val[p + 6]!).hBounds
  have b7 := (input.val[p + 7]!).hBounds
  have c0 := (input.val[q]!).hBounds
  have c1 := (input.val[q + 1]!).hBounds
  have c2 := (input.val[q + 2]!).hBounds
  have c3 := (input.val[q + 3]!).hBounds
  have c4 := (input.val[q + 4]!).hBounds
  have c5 := (input.val[q + 5]!).hBounds
  have c6 := (input.val[q + 6]!).hBounds
  have c7 := (input.val[q + 7]!).hBounds
  simp only [Std.UScalarTy.numBits] at *
  intro k hk
  apply UScalar.eq_imp
  rcases (by omega : k = 0 ∨ k = 1 ∨ k = 2 ∨ k = 3 ∨ k = 4 ∨ k = 5 ∨ k = 6 ∨ k = 7) with
    rfl | rfl | rfl | rfl | rfl | rfl | rfl | rfl <;> (try simp only [Nat.add_zero]) <;> omega
theorem w4_bytes (input : Slice Std.U8) (p q : Nat) (h : w4 input p = w4 input q) :
    ∀ k, k < 4 → input.val[q + k]! = input.val[p + k]! := by
  unfold w4 at h
  have b0 := (input.val[p]!).hBounds
  have b1 := (input.val[p + 1]!).hBounds
  have b2 := (input.val[p + 2]!).hBounds
  have b3 := (input.val[p + 3]!).hBounds
  have c0 := (input.val[q]!).hBounds
  have c1 := (input.val[q + 1]!).hBounds
  have c2 := (input.val[q + 2]!).hBounds
  have c3 := (input.val[q + 3]!).hBounds
  simp only [Std.UScalarTy.numBits] at *
  intro k hk
  apply UScalar.eq_imp
  rcases (by omega : k = 0 ∨ k = 1 ∨ k = 2 ∨ k = 3) with
    rfl | rfl | rfl | rfl <;> (try simp only [Nat.add_zero]) <;> omega
theorem Matches.add8 {input : Slice Std.U8} {a b l : Nat} (h : Matches input a b l)
    (hw : w8 input (a + l) = w8 input (b + l)) : Matches input a b (l + 8) := by
  have hb := w8_bytes input (a + l) (b + l) hw
  intro k hk
  by_cases hkl : k < l
  · exact h k hkl
  · have := hb (k - l) (by omega)
    rw [show b + k = b + l + (k - l) by omega, show a + k = a + l + (k - l) by omega]
    exact this
theorem Matches.tail8 {input : Slice Std.U8} {a b l c : Nat} (h : Matches input a b l)
    (hc : 8 ≤ c) (hl : c ≤ l + 8)
    (hw : w8 input (a + (c - 8)) = w8 input (b + (c - 8))) : Matches input a b c := by
  have hb := w8_bytes input (a + (c - 8)) (b + (c - 8)) hw
  intro k hk
  by_cases hkl : k < l
  · exact h k hkl
  · have := hb (k - (c - 8)) (by omega)
    rw [show b + k = b + (c - 8) + (k - (c - 8)) by omega,
      show a + k = a + (c - 8) + (k - (c - 8)) by omega]
    exact this
theorem Matches.two4 {input : Slice Std.U8} {a b c : Nat}
    (hc : 4 ≤ c) (hc8 : c < 8) (hw0 : w4 input a = w4 input b)
    (hw1 : w4 input (a + (c - 4)) = w4 input (b + (c - 4))) : Matches input a b c := by
  have h0 := w4_bytes input a b hw0
  have h1 := w4_bytes input (a + (c - 4)) (b + (c - 4)) hw1
  intro k hk
  by_cases hk4 : k < 4
  · exact h0 k hk4
  · have := h1 (k - (c - 4)) (by omega)
    rw [show b + k = b + (c - 4) + (k - (c - 4)) by omega,
      show a + k = a + (c - 4) + (k - (c - 4)) by omega]
    exact this
@[local step]
theorem tw8_spec (input : Slice Std.U8) (p : Std.Usize) (h : p.val + 8 ≤ input.length) :
    slot.o_a_tw8 input p ⦃ fun r => r.val = w8 input p.val ⦄ := by
  rw [slot.o_a_tw8]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  step*
  unfold w8
  rw [getElem!_pos input.val p.val (by scalar_tac), getElem!_pos input.val (p.val + 1) (by scalar_tac),
    getElem!_pos input.val (p.val + 2) (by scalar_tac), getElem!_pos input.val (p.val + 3) (by scalar_tac),
    getElem!_pos input.val (p.val + 4) (by scalar_tac), getElem!_pos input.val (p.val + 5) (by scalar_tac),
    getElem!_pos input.val (p.val + 6) (by scalar_tac), getElem!_pos input.val (p.val + 7) (by scalar_tac)]
  scalar_tac
@[local step]
theorem tw4_spec (input : Slice Std.U8) (p : Std.Usize) (h : p.val + 4 ≤ input.length) :
    slot.o_a_tw4 input p ⦃ fun r => r.val = w4 input p.val ⦄ := by
  rw [slot.o_a_tw4]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  step*
  unfold w4
  rw [getElem!_pos input.val p.val (by scalar_tac), getElem!_pos input.val (p.val + 1) (by scalar_tac),
    getElem!_pos input.val (p.val + 2) (by scalar_tac), getElem!_pos input.val (p.val + 3) (by scalar_tac)]
  scalar_tac
theorem words_eq_loop_spec (input : Slice Std.U8) (a b cap l0 : Std.Usize)
    (ha : a.val + cap.val ≤ input.length) (hb : b.val + cap.val ≤ input.length)
    (hl0 : l0.val ≤ cap.val) (h0 : Matches input a.val b.val l0.val) :
    slot.o_a_words_eq_loop input a b cap l0 ⦃ fun l =>
      l.val ≤ cap.val ∧ Matches input a.val b.val l.val ⦄ := by
  rw [slot.o_a_words_eq_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun l => cap.val - l.val)
    (inv := fun l => l.val ≤ cap.val ∧ Matches input a.val b.val l.val)
  · rintro l ⟨hle, hinv⟩
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.o_a_words_eq_loop.body]
    step*
    all_goals first
      | exact ⟨hle, hinv⟩
      | (refine ⟨by scalar_tac, ?_, by scalar_tac⟩
         rw [show l1.val = l.val + 8 by scalar_tac]
         apply Matches.add8 hinv
         rw [show a.val + l.val = i1.val by scalar_tac, show b.val + l.val = i3.val by scalar_tac,
           ← i2_post, ← i4_post, ‹i2 = i4›])
  · exact ⟨hl0, h0⟩
@[local step]
theorem tail_eq_spec (input : Slice Std.U8) (a b cap l : Std.Usize)
    (ha : a.val + cap.val ≤ input.length) (hb : b.val + cap.val ≤ input.length) (hl : l.val ≤ cap.val) :
    slot.o_a_tail_eq input a b cap l ⦃ fun r => r.val = 1 →
      8 ≤ cap.val ∧ cap.val ≤ l.val + 8 ∧
      w8 input (a.val + (cap.val - 8)) = w8 input (b.val + (cap.val - 8)) ⦄ := by
  rw [slot.o_a_tail_eq]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  step*
  all_goals first
    | (intro h; simp at h)
    | (intro _
       refine ⟨by scalar_tac, by scalar_tac, ?_⟩
       rw [show a.val + (cap.val - 8) = i2.val by scalar_tac,
         show b.val + (cap.val - 8) = i4.val by scalar_tac, ← i3_post, ← i5_post, ‹i3 = i5›])
    | (refine ⟨by scalar_tac, by scalar_tac, ?_⟩
       rw [show a.val + (cap.val - 8) = i2.val by scalar_tac,
         show b.val + (cap.val - 8) = i4.val by scalar_tac, ← i3_post, ← i5_post, ‹i3 = i5›])
@[local step]
theorem short_eq_spec (input : Slice Std.U8) (a b cap : Std.Usize)
    (ha : a.val + cap.val ≤ input.length) (hb : b.val + cap.val ≤ input.length) :
    slot.o_a_short_eq input a b cap ⦃ fun r => r.val = 1 →
      4 ≤ cap.val ∧ cap.val < 8 ∧ w4 input a.val = w4 input b.val ∧
      w4 input (a.val + (cap.val - 4)) = w4 input (b.val + (cap.val - 4)) ⦄ := by
  rw [slot.o_a_short_eq]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  step*
  all_goals first
    | (intro h; simp at h)
    | (intro _
       refine ⟨by scalar_tac, by scalar_tac, ?_, ?_⟩
       · rw [← i_post, ← i1_post]
         simp_all
       · rw [show a.val + (cap.val - 4) = i3.val by scalar_tac,
           show b.val + (cap.val - 4) = i5.val by scalar_tac, ← i4_post, ← i6_post, ‹i4 = i6›])
    | (refine ⟨by scalar_tac, by scalar_tac, ?_, ?_⟩
       · rw [← i_post, ← i1_post]
         simp_all
       · rw [show a.val + (cap.val - 4) = i3.val by scalar_tac,
           show b.val + (cap.val - 4) = i5.val by scalar_tac, ← i4_post, ← i6_post, ‹i4 = i6›])
@[local step]
theorem words_eq_spec (input : Slice Std.U8) (a b cap : Std.Usize)
    (ha : a.val + cap.val ≤ input.length) (hb : b.val + cap.val ≤ input.length) :
    slot.o_a_words_eq input a b cap ⦃ fun l =>
      l.val ≤ cap.val ∧ Matches input a.val b.val l.val ⦄ := by
  rw [slot.o_a_words_eq]
  apply Std.WP.spec_bind (words_eq_loop_spec input a b cap 0#usize ha hb (by scalar_tac)
    (LZ77.Matches.zero input a.val b.val))
  rintro l ⟨hle, hm⟩
  apply Std.WP.spec_bind (tail_eq_spec input a b cap l ha hb hle)
  rintro big hbig
  apply Std.WP.spec_bind (short_eq_spec input a b cap ha hb)
  rintro small hsmall
  split
  · have h1 : big.val = 1 := by scalar_tac
    obtain ⟨h8, hcl, hw⟩ := hbig h1
    simp only [Std.WP.spec_ok]
    exact ⟨le_refl _, Matches.tail8 hm h8 hcl hw⟩
  · split
    · have h1 : small.val = 1 := by scalar_tac
      obtain ⟨h4, h8, hw0, hw1⟩ := hsmall h1
      simp only [Std.WP.spec_ok]
      exact ⟨le_refl _, Matches.two4 h4 h8 hw0 hw1⟩
    · simp only [Std.WP.spec_ok]
      exact ⟨hle, hm⟩
theorem match_len_loop_spec (input : Slice Std.U8) (a b cap l0 : Std.Usize)
    (ha : a.val + cap.val ≤ input.length) (hb : b.val + cap.val ≤ input.length)
    (hl0 : l0.val ≤ cap.val) (h0 : Matches input a.val b.val l0.val) :
    slot.o_a_match_len_loop input a b cap l0 ⦃ fun l =>
      l.val ≤ cap.val ∧ Matches input a.val b.val l.val ⦄ := by
  (
  rw [slot.o_a_match_len_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun l => cap.val - l.val)
    (inv := fun l => l.val ≤ cap.val ∧ LZ77.Matches input a.val b.val l.val)
  · rintro l ⟨hle, hinv⟩
    simp only [slot.o_a_match_len_loop.body]
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
  · exact ⟨hl0, h0⟩)
@[local step]
theorem match_len_spec (input : Slice Std.U8) (a b cap : Std.Usize)
    (ha : a.val + cap.val ≤ input.length) (hb : b.val + cap.val ≤ input.length) :
    slot.o_a_match_len input a b cap ⦃ fun l =>
      l.val ≤ cap.val ∧ Matches input a.val b.val l.val ⦄ := by
  rw [slot.o_a_match_len]
  apply Std.WP.spec_bind (words_eq_spec input a b cap ha hb)
  rintro l0 ⟨hle, hm⟩
  exact match_len_loop_spec input a b cap l0 ha hb hle hm
theorem verified_spec (input : Slice Std.U8) (pos d ch : Std.Usize) :
    slot.o_a_verified input pos d ch ⦃ fun b => b = true →
      3 ≤ ch.val ∧ ch.val ≤ 258 ∧ 1 ≤ d.val ∧ d.val ≤ 32768 ∧ d.val ≤ pos.val ∧
      pos.val + ch.val ≤ input.length ∧ Matches input (pos.val - d.val) pos.val ch.val ⦄ := by
  rw [slot.o_a_verified]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  step*
  intro hv
  have hv' : ch.val ≤ v.val := by simpa using hv
  refine ⟨by scalar_tac, by scalar_tac, by scalar_tac, by scalar_tac, by scalar_tac,
    by scalar_tac, ?_⟩
  rw [show pos.val - d.val = i1.val by scalar_tac]
  exact Matches.mono v_post2 hv'
theorem emit_lits_loop_spec (input : Slice Std.U8) (out0 : Slice Std.U32)
    (n cnt1 k0 c0 ntok0 : Std.Usize)
    (hn : n.val = input.length) (hout : input.length ≤ out0.length)
    (hk : k0.val ≤ n.val) (hntok : ntok0.val ≤ k0.val) (hc0 : c0.val = 0)
    (hdec : LZ77.decode (toks out0 ntok0.val) = some ((bytes input).take k0.val)) :
    slot.o_a_emit_lits_loop input out0 n cnt1 k0 c0 ntok0 ⦃ fun r =>
      r.2.1.val ≤ n.val ∧ (k0.val < r.2.1.val ∨ cnt1.val = 0 ∨ k0.val = n.val) ∧
      r.2.2.val ≤ r.2.1.val ∧ r.1.length = out0.length ∧
      LZ77.decode (toks r.1 r.2.2.val) = some ((bytes input).take r.2.1.val) ⦄ := by
  rw [slot.o_a_emit_lits_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => n.val - s.2.1.val)
    (inv := fun s =>
      s.2.1.val ≤ n.val ∧ s.2.1.val = k0.val + s.2.2.1.val ∧ s.2.2.2.val ≤ s.2.1.val ∧
      s.1.length = out0.length ∧
      LZ77.decode (toks s.1 s.2.2.2.val) = some ((bytes input).take s.2.1.val))
  · rintro ⟨out, k, c, ntok⟩ ⟨hkn, hkc, hnt, hlen, hde⟩
    simp only at hkn hkc hnt hlen hde
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.o_a_emit_lits_loop.body]
    split
    case isTrue hklt =>
      split
      case isTrue hc =>
        have hntok_lt : ntok.val < out.length := by scalar_tac
        have hposlen : k.val < input.length := by scalar_tac
        step*
        have hval : i1.val = (bytes input)[k.val]! := by
          rw [bytes_getElem! input k.val hposlen, i1_post, Std.U8.cast_U32_val_eq, i_post]
        refine ⟨by scalar_tac, by scalar_tac, by scalar_tac,
          by rw [s_post]; simpa [Std.Slice.set_val_eq] using hlen, ?_, by scalar_tac⟩
        rw [s_post, show ntok1.val = ntok.val + 1 by scalar_tac,
          show k1.val = k.val + 1 by scalar_tac]
        exact emit_lit input out ntok k.val i1 hde hposlen hntok_lt hval
      case isFalse hc =>
        exact ⟨hkn, by scalar_tac, hnt, hlen, hde⟩
    case isFalse hge =>
      exact ⟨hkn, by scalar_tac, hnt, hlen, hde⟩
  · exact ⟨hk, by scalar_tac, hntok, rfl, hdec⟩
@[local step]
theorem emit_lits_spec (input : Slice Std.U8) (out : Slice Std.U32) (pos0 cnt ntok0 : Std.Usize)
    (hout : input.length ≤ out.length) (hpos : pos0.val ≤ input.length)
    (hntok : ntok0.val ≤ pos0.val)
    (hdec : LZ77.decode (toks out ntok0.val) = some ((bytes input).take pos0.val)) :
    slot.o_a_emit_lits input out pos0 cnt ntok0 ⦃ fun r =>
      (pos0.val < r.1.2.val ∨ pos0.val = input.length) ∧ r.1.2.val ≤ input.length ∧ r.1.1.val ≤ r.1.2.val ∧
      r.2.length = out.length ∧
      LZ77.decode (toks r.2 r.1.1.val) = some ((bytes input).take r.1.2.val) ⦄ := by
  rw [slot.o_a_emit_lits]
  apply Std.WP.spec_bind (Pₘ := fun (c : Std.Usize) => 1 ≤ c.val)
  · split <;> simp only [Std.WP.spec_ok] <;> scalar_tac
  intro cnt1 hc1
  apply Std.WP.spec_bind (emit_lits_loop_spec input out _ cnt1 pos0 0#usize ntok0
    (by simp) hout (by scalar_tac) hntok (by simp) hdec)
  rintro ⟨out1, k, ntok⟩ ⟨h1, h2, h3, h4, h5⟩
  simp only at h1 h2 h3 h4 h5
  step*
  all_goals exact ⟨by scalar_tac, by scalar_tac, h3, h4, h5⟩
@[local step]
theorem emit_step_spec (input : Slice Std.U8) (out : Slice Std.U32) (pos d l lits ntok : Std.Usize)
    (hout : input.length ≤ out.length) (hpos : pos.val < input.length)
    (hntok : ntok.val ≤ pos.val)
    (hdec : LZ77.decode (toks out ntok.val) = some ((bytes input).take pos.val)) :
    slot.o_a_emit_step input out pos d l lits ntok ⦃ fun r =>
      pos.val < r.1.2.val ∧ r.1.2.val ≤ input.length ∧ r.1.1.val ≤ r.1.2.val ∧
      r.2.length = out.length ∧
      LZ77.decode (toks r.2 r.1.1.val) = some ((bytes input).take r.1.2.val) ⦄ := by
  rw [slot.o_a_emit_step]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  apply Std.WP.spec_bind (verified_spec input pos d l)
  intro b hb
  split
  case isTrue hbt =>
    obtain ⟨hl3, hl258, hd1, hdmax, hdpos, hend, hmatch⟩ := hb hbt
    have hntok_lt : ntok.val < out.length := by scalar_tac
    step*
    have htok : i6.val = LZ77.mkMatch d.val l.val := by
      simp only [LZ77.mkMatch, LZ77.MATCH_BASE, i6_post, i3_post, i2_post]
      scalar_tac
    refine ⟨by scalar_tac, by scalar_tac, by scalar_tac,
      by rw [out1_post]; simp [Std.Slice.set_val_eq], ?_⟩
    rw [out1_post, show i7.val = ntok.val + 1 by scalar_tac,
      show i8.val = pos.val + l.val by scalar_tac]
    exact emit_match input out ntok pos.val d.val l.val i6 hdec hntok_lt hd1 hdpos hdmax
      hl3 hl258 hend hmatch htok
  case isFalse hbf =>
    apply Std.WP.spec_mono (emit_lits_spec input out pos lits ntok hout (by scalar_tac) hntok hdec)
    rintro ⟨⟨t, k⟩, o⟩ ⟨h1, h2, h3, h4, h5⟩
    exact ⟨by scalar_tac, h2, h3, h4, h5⟩
@[local step]
theorem fl_tw8_spec (input : Slice Std.U8) (p : Std.Usize) (h : p.val + 8 ≤ input.length) :
    slot.o_a_fl_tw8 input p ⦃ fun r => r.val = w8 input p.val ⦄ := by
  exact @tw8_spec input p h
@[local step]
theorem fl_tw4_spec (input : Slice Std.U8) (p : Std.Usize) (h : p.val + 4 ≤ input.length) :
    slot.o_a_fl_tw4 input p ⦃ fun r => r.val = w4 input p.val ⦄ := by
  exact @tw4_spec input p h
@[local step]
theorem fl_tail_eq_spec (input : Slice Std.U8) (a b cap l : Std.Usize)
    (ha : a.val + cap.val ≤ input.length) (hb : b.val + cap.val ≤ input.length) (hl : l.val ≤ cap.val) :
    slot.o_a_fl_tail_eq input a b cap l ⦃ fun r => r.val = 1 →
      8 ≤ cap.val ∧ cap.val ≤ l.val + 8 ∧
      w8 input (a.val + (cap.val - 8)) = w8 input (b.val + (cap.val - 8)) ⦄ := by
  exact @tail_eq_spec input a b cap l ha hb hl
@[local step]
theorem fl_short_eq_spec (input : Slice Std.U8) (a b cap : Std.Usize)
    (ha : a.val + cap.val ≤ input.length) (hb : b.val + cap.val ≤ input.length) :
    slot.o_a_fl_short_eq input a b cap ⦃ fun r => r.val = 1 →
      4 ≤ cap.val ∧ cap.val < 8 ∧ w4 input a.val = w4 input b.val ∧
      w4 input (a.val + (cap.val - 4)) = w4 input (b.val + (cap.val - 4)) ⦄ := by
  exact @short_eq_spec input a b cap ha hb
@[local step]
theorem fl_words_eq_spec (input : Slice Std.U8) (a b cap : Std.Usize)
    (ha : a.val + cap.val ≤ input.length) (hb : b.val + cap.val ≤ input.length) :
    slot.o_a_fl_words_eq input a b cap ⦃ fun l =>
      l.val ≤ cap.val ∧ Matches input a.val b.val l.val ⦄ := by
  exact @words_eq_spec input a b cap ha hb
@[local step]
theorem fl_match_len_spec (input : Slice Std.U8) (a b cap : Std.Usize)
    (ha : a.val + cap.val ≤ input.length) (hb : b.val + cap.val ≤ input.length) :
    slot.o_a_fl_match_len input a b cap ⦃ fun l =>
      l.val ≤ cap.val ∧ Matches input a.val b.val l.val ⦄ := by
  exact @match_len_spec input a b cap ha hb
@[local step]
theorem fl_emit_lits_spec (input : Slice Std.U8) (out : Slice Std.U32) (pos0 cnt ntok0 : Std.Usize)
    (hout : input.length ≤ out.length) (hpos : pos0.val ≤ input.length)
    (hntok : ntok0.val ≤ pos0.val)
    (hdec : LZ77.decode (toks out ntok0.val) = some ((bytes input).take pos0.val)) :
    slot.o_a_fl_emit_lits input out pos0 cnt ntok0 ⦃ fun r =>
      (pos0.val < r.1.2.val ∨ pos0.val = input.length) ∧ r.1.2.val ≤ input.length ∧ r.1.1.val ≤ r.1.2.val ∧
      r.2.length = out.length ∧
      LZ77.decode (toks r.2 r.1.1.val) = some ((bytes input).take r.1.2.val) ⦄ := by
  exact @emit_lits_spec input out pos0 cnt ntok0 hout hpos hntok hdec
@[local step]
theorem fl_emit_step_spec (input : Slice Std.U8) (out : Slice Std.U32) (pos d l lits ntok : Std.Usize)
    (hout : input.length ≤ out.length) (hpos : pos.val < input.length)
    (hntok : ntok.val ≤ pos.val)
    (hdec : LZ77.decode (toks out ntok.val) = some ((bytes input).take pos.val)) :
    slot.o_a_fl_emit_step input out pos d l lits ntok ⦃ fun r =>
      pos.val < r.1.2.val ∧ r.1.2.val ≤ input.length ∧ r.1.1.val ≤ r.1.2.val ∧
      r.2.length = out.length ∧
      LZ77.decode (toks r.2 r.1.1.val) = some ((bytes input).take r.1.2.val) ⦄ := by
  exact @emit_step_spec input out pos d l lits ntok hout hpos hntok hdec
section
attribute [local step] Submission.r70_ite_true_spec
theorem sh_lc_spec (l : Std.Usize) :
    slot.o_a_sh_lc l ⦃ fun _ => True ⦄ := C1258! slot.o_a_sh_lc
end
attribute [local step] sh_lc_spec
section
attribute [local step] Submission.r70_ite_true_spec
theorem sh_dc_spec (d : Std.Usize) :
    slot.o_a_sh_dc d ⦃ fun _ => True ⦄ := C1258! slot.o_a_sh_dc
end
attribute [local step] sh_dc_spec
section
attribute [local step] Submission.r70_ite_true_spec
theorem sh_add_spec (stats : Array Std.U32 128#usize) (l : Std.Usize) (d : Std.Usize) :
    slot.o_a_sh_add stats l d ⦃ fun _ => True ⦄ := C1258! slot.o_a_sh_add
end
attribute [local step] sh_add_spec
section
attribute [local step] Submission.r70_ite_true_spec
theorem sh_fill_loop_spec (q : Array Std.Usize 320#usize) (end0 best keep l : Std.Usize) :
    slot.o_a_sh_fill_loop q end0 best keep l ⦃ fun _ => True ⦄ := by
  rw [slot.o_a_sh_fill_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => 259 - s.2.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1⟩ _
    simp only [slot.o_a_sh_fill_loop.body, lift, Array.to_slice_mut]
    step*
    repeat (first
      | (intro hc; (try step*))
      | (split <;> (try step*))
      | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply spec_ite_cut <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals scalar_tac
  · trivial
end
attribute [local step] sh_fill_loop_spec
section
attribute [local step] Submission.r70_ite_true_spec
theorem sh_fill_spec (q : Array Std.Usize 320#usize) (begin0 end0 best keep : Std.Usize) :
    slot.o_a_sh_fill q begin0 end0 best keep ⦃ fun _ => True ⦄ := C1258! slot.o_a_sh_fill
end
attribute [local step] sh_fill_spec
section
attribute [local step] Submission.r70_ite_true_spec
theorem sh_table_loop0_spec (SH_L_ : Std.U32) (SH_BUDGET_ : Std.Usize) (stats : Array Std.U32 128#usize) (q : Array Std.Usize 320#usize)
  (lb : Array Std.Usize 29#usize) (best : Std.Usize) (c : Std.Usize) :
    slot.o_a_sh_table_loop0 SH_L_ SH_BUDGET_ stats q lb best c ⦃ fun _ => True ⦄ := C12512! slot.o_a_sh_table_loop0 slot.o_a_sh_table_loop0.body
end
attribute [local step] sh_table_loop0_spec
section
attribute [local step] Submission.r70_ite_true_spec
theorem sh_table_loop1_spec (SH_D_ : Std.U32) (SH_DM_ : Std.U32) (stats : Array Std.U32 128#usize) (q : Array Std.Usize 320#usize)
  (c : Std.Usize) :
    slot.o_a_sh_table_loop1 SH_D_ SH_DM_ stats q c ⦃ fun _ => True ⦄ := C12513! slot.o_a_sh_table_loop1 slot.o_a_sh_table_loop1.body
end
attribute [local step] sh_table_loop1_spec
section
attribute [local step] Submission.r70_ite_true_spec
theorem sh_table_spec (SH_L_ : Std.U32) (SH_D_ : Std.U32) (SH_BUDGET_ : Std.Usize) (SH_DM_ : Std.U32) (stats : Array Std.U32 128#usize) (q : Array Std.Usize 320#usize) :
    slot.o_a_sh_table SH_L_ SH_D_ SH_BUDGET_ SH_DM_ stats q ⦃ fun _ => True ⦄ := C1258! slot.o_a_sh_table
end
attribute [local step] sh_table_spec
section
attribute [local step] Submission.r70_ite_true_spec
theorem sh_litrun_loop_spec (cache : Array Std.U32 4096#usize) (ix : Std.Usize) (sum : Std.Usize)
  (k : Std.Usize) :
    slot.o_a_sh_litrun_loop cache ix sum k ⦃ fun _ => True ⦄ := by
  rw [slot.o_a_sh_litrun_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => 4096 - s.2.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1⟩ _
    simp only [slot.o_a_sh_litrun_loop.body, lift, Array.to_slice_mut]
    step*
    repeat (first
      | (intro hc; (try step*))
      | (split <;> (try step*))
      | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply spec_ite_cut <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals scalar_tac
  · trivial
end
attribute [local step] sh_litrun_loop_spec
section
attribute [local step] Submission.r70_ite_true_spec
theorem sh_litrun_spec (cache : Array Std.U32 4096#usize) (ix : Std.Usize) :
    slot.o_a_sh_litrun cache ix ⦃ fun _ => True ⦄ := C1258! slot.o_a_sh_litrun
end
attribute [local step] sh_litrun_spec
section
@[local step]
theorem run_greedy_loop_spec (IH_ : Std.Usize) (IT_ : Std.Usize) (TS_ : Std.Usize) (ACC_ : Std.U64) (LZT_ : Std.Usize) (input : Slice Std.U8) (out0 : Slice Std.U32) (head0 : Array Std.U32 131072#usize) (n : Std.Usize) (pos0 : Std.Usize) (ntok0 : Std.Usize)
    (hn : n.val = input.length) (hout : input.length ≤ out0.length)
    (hp : pos0.val ≤ n.val) (hntok : ntok0.val ≤ pos0.val)
    (hdec : LZ77.decode (toks out0 ntok0.val) = some ((bytes input).take pos0.val)) :
    slot.o_a_run_greedy_loop IH_ IT_ TS_ ACC_ LZT_ input out0 head0 n pos0 ntok0 ⦃ fun r =>
      r.1.val ≤ input.length ∧ r.2.1.length = out0.length ∧
      LZ77.Valid (bytes input) (toks r.2.1 r.1.val) ⦄ := C12514! slot.o_a_run_greedy_loop slot.o_a_run_greedy_loop.body
end
attribute [local step] run_greedy_loop_spec
set_option hygiene false in
local notation "C12515!" q0__:max => (by
  rw [q0__]
  have h0 := decode_nil input out
  try simp only [lift, Array.to_slice_mut, alloc.vec.Vec.deref_mut, bind_tc_ok]
  step*
  all_goals (repeat (first
    | (refine ⟨by scalar_tac, by scalar_tac, valid_of_decode (by assumption) (by scalar_tac)⟩)
    | (intro hc; (try step*))
    | (casesm* _ × _; (try simp only []); (try step*))
    | (split <;> (try step*))
    | (step <;> (try step*))))
  all_goals (try scalar_tac))
section
attribute [local step] ite_true_spec
@[local step]
theorem run_greedy_spec (IH_ : Std.Usize) (IT_ : Std.Usize) (TS_ : Std.Usize) (ACC_ : Std.U64) (LZT_ : Std.Usize) (input : Slice Std.U8) (out : Slice Std.U32) (head : Array Std.U32 131072#usize) (pos0 : Std.Usize) (ntok0 : Std.Usize)
    (hlen : input.length ≤ out.length)
    (hp : pos0.val ≤ input.length) (hntok : ntok0.val ≤ pos0.val)
    (hdec : LZ77.decode (toks out ntok0.val) = some ((bytes input).take pos0.val)) :
    slot.o_a_run_greedy IH_ IT_ TS_ ACC_ LZT_ input out head pos0 ntok0 ⦃ fun r =>
      r.1.val ≤ input.length ∧
      r.2.1.length = out.length ∧
      LZ77.Valid (bytes input) (toks r.2.1 r.1.val) ⦄ := C12515! slot.o_a_run_greedy
end
attribute [local step] run_greedy_spec
section
attribute [local step] ite_true_spec
@[local step]
theorem main_part_spec (IH_ : Std.Usize) (IT_ : Std.Usize) (TS_ : Std.Usize) (ACC_ : Std.U64) (LZT_ : Std.Usize) (input : Slice Std.U8) (out : Slice Std.U32) (m : Std.Usize) (pos0 : Std.Usize) (ntok0 : Std.Usize)
    (hlen : input.length ≤ out.length)
    (hp : pos0.val ≤ input.length) (hntok : ntok0.val ≤ pos0.val)
    (hdec : LZ77.decode (toks out ntok0.val) = some ((bytes input).take pos0.val)) :
    slot.o_a_main_part IH_ IT_ TS_ ACC_ LZT_ input out m pos0 ntok0 ⦃ fun r =>
      r.1.val ≤ input.length ∧
      r.2.length = out.length ∧
      LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := C12515! slot.o_a_main_part
end
attribute [local step] main_part_spec
end EA
attribute [local step] EA.main_part_spec
set_option maxHeartbeats 1000000
end EO
set_option hygiene false in
local notation "C12516!" q0__:max => (by
  rw [q0__]
  have h0 := decode_nil input out
  try simp only [lift, Array.to_slice_mut, alloc.vec.Vec.deref_mut, bind_tc_ok]
  step*
  all_goals (repeat (first
    | (refine ⟨by scalar_tac, by scalar_tac, by scalar_tac, by assumption⟩)
    | (intro hc; (try step*))
    | (casesm* _ × _; (try simp only []); (try step*))
    | (split <;> (try step*))
    | (step <;> (try step*))))
  all_goals (try scalar_tac))
set_option hygiene false in
local notation "C12517!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun s => n.val - s.2.1.val)
    (inv := fun s =>
      s.2.1.val ≤ n.val ∧ s.2.2.1.val ≤ s.2.1.val ∧ s.1.length = out0.length ∧
      LZ77.decode (toks s.1 s.2.2.1.val) = some ((bytes input).take s.2.1.val))
  · rintro ⟨out, pos, ntok, ix, rem, dist⟩ ⟨hpn, hnt, hlen, hde⟩
    simp only at hpn hnt hlen hde
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [q1__, lift, Array.to_slice_mut, alloc.vec.Vec.deref_mut, bind_tc_ok]
    split
    case isTrue hlt =>
      step*
      all_goals (repeat (first
        | (refine ⟨by scalar_tac, by scalar_tac, by assumption, by assumption, by scalar_tac⟩)
        | (intro hc; (try step*))
        | (casesm* _ × _; (try simp only []); (try step*))
        | (split <;> (try step*))
        | (step <;> (try step*))))
      all_goals (try scalar_tac)
    case isFalse hge =>
      exact ⟨hpn, hnt, hlen, hde⟩
  · exact ⟨hp, hntok, rfl, hdec⟩)
set_option hygiene false in
local notation "C12518!" => (by
  intro n
  induction n with
  | zero => simp [copyN]
  | succ m ih =>
    simp only [copyN]
    rw [List.take_append_of_le_length (by simp)]
    exact ih)
set_option hygiene false in
local notation "C12519!" => (by
  intro ts
  induction ts with
  | nil => intro init acc h; simp at h; subst h; simp
  | cons t ts ih =>
    intro init acc h
    simp only [List.foldlM_cons] at h
    cases he : emit init t with
    | none => rw [he] at h; simp at h
    | some a =>
      rw [he] at h
      simp only [Option.bind_eq_bind, Option.bind_some] at h
      have h1 := ih a acc h
      have h2 : init.length + 1 ≤ a.length := by
        simp only [emit] at he
        split at he
        · simp at he; subst he; simp
        · split at he
          · split at he
            · simp at he; subst he; rw [copyN_length]; simp only [tokLen]; omega
            · simp at he
          · simp at he
      simp only [List.length_cons]
      omega)
set_option hygiene false in
local notation "C12520!" => (by
  have := foldlM_emit_length ts [] acc h
  simpa using this)
set_option hygiene false in
local notation "C12521!" => (by
  rw [decode_snoc] at hd
  cases hts : decode ts with
  | none => rw [hts] at hd; simp at hd
  | some acc =>
    rw [hts] at hd
    simp only [Option.bind_some, emit, if_pos ht] at hd
    have hacc : acc ++ [t] = inp.take p := Option.some.inj hd
    have hlen : acc.length + 1 = p := by
      have := congrArg List.length hacc
      simp [List.length_take] at this; omega
    refine ⟨by omega, ?_⟩
    apply congrArg some
    have := congrArg (List.take acc.length) hacc
    rw [List.take_append_of_le_length (le_refl _), List.take_length, List.take_take] at this
    rw [this, show min acc.length p = p - 1 by omega])
set_option hygiene false in
local notation "C12522!" => (by
  rw [decode_snoc] at hd
  cases hts : decode ts with
  | none => rw [hts] at hd; simp at hd
  | some acc =>
    rw [hts] at hd
    simp only [Option.bind_some, emit, if_neg (show ¬ t < 256 by omega)] at hd
    split at hd
    · split at hd
      · have hacc : copyN acc (tokDist t) (tokLen t) = inp.take p := Option.some.inj hd
        have hlen : acc.length + tokLen t = p := by
          have := congrArg List.length hacc
          simp [List.length_take] at this; omega
        refine ⟨by omega, ?_⟩
        apply congrArg some
        have := congrArg (List.take acc.length) hacc
        rw [copyN_take_prefix, List.take_take] at this
        rw [this, show min acc.length p = p - tokLen t by omega]
      · simp at hd
    · simp at hd)
set_option hygiene false in
local notation "C12523!" => (by
  have hlt : nt - 1 < out.val.length := by
    have : out.length = out.val.length := rfl
    omega
  simp only [toks]
  conv_lhs => rw [show nt = (nt - 1) + 1 by omega]
  rw [List.take_add_one, List.getElem?_eq_getElem hlt, Option.toList_some, List.map_append]
  simp [getElem!_pos out.val (nt - 1) hlt])
set_option hygiene false in
local notation "C12524!" => (by
  simp only [toks, List.length_map, List.length_take]
  have : out.length = out.val.length := rfl
  omega)
set_option hygiene false in
local notation "C12525!" => (by
  obtain ⟨hps, hntp, hso, hde⟩ := h
  rw [toks_pop out nt h0 hle] at hde
  obtain ⟨hp1, hde'⟩ := decode_pop_lit (by simpa using hps) hde ht
  exact ⟨hp1, by omega, by omega, hso, hde'⟩)
set_option hygiene false in
local notation "C12526!" => (by
  obtain ⟨hps, hntp, hso, hde⟩ := h
  rw [toks_pop out nt h0 hle] at hde
  obtain ⟨hw, hde'⟩ := decode_pop_match (by simpa using hps) hde ht
  have hlen := decode_length_le hde'
  rw [toks_length out (nt - 1) (by omega), List.length_take, bytes_length] at hlen
  exact ⟨hw, by omega, by omega, hso, hde'⟩)
namespace EY
open Aeneas Aeneas.Std Result ControlFlow
open LZ77 (toks bytes)
set_option maxRecDepth 8192
set_option maxHeartbeats 4000000
namespace EA
open Aeneas Aeneas.Std Result ControlFlow
set_option maxRecDepth 8192
set_option maxHeartbeats 4000000
open LZ77 (toks bytes bytes_length bytes_getElem! Matches emit_lit emit_match ite_ok)
theorem decode_nil (input : Slice Std.U8) (out : Slice Std.U32) :
    LZ77.decode (toks out (0#usize).val) = some ((bytes input).take (0#usize).val) := by
  simp [toks, LZ77.decode]
theorem valid_of_decode {input : Slice Std.U8} {o : Slice Std.U32} {t p : Std.Usize}
    (hde : LZ77.decode (toks o t.val) = some ((bytes input).take p.val)) (hp : p.val = input.length) :
    LZ77.Valid (bytes input) (toks o t.val) := by
  unfold LZ77.Valid
  rw [hde, hp]
  simp
theorem spec_ite_cut {α : Type} (c : Prop) [Decidable c] (a b : Result α) (Q : α → Prop)
    (ha : c → a ⦃ Q ⦄) (hb : ¬c → b ⦃ Q ⦄) : (if c then a else b) ⦃ Q ⦄ := C1256!
theorem ite_prod_spec {α β : Type} (c : Prop) [Decidable c] (A B : Result (α × β))
    (hA : c → A ⦃ fun _ => True ⦄) (hB : ¬c → B ⦃ fun _ => True ⦄) :
    (if c then A else B) ⦃ fun _ => True ⦄ := C1257!
theorem ite_true_spec {α : Type} (c : Prop) [Decidable c] (A B : Result α)
    (hA : c → A ⦃ fun _ => True ⦄) (hB : ¬c → B ⦃ fun _ => True ⦄) :
    (if c then A else B) ⦃ fun _ => True ⦄ := C1257!
@[local step]
abbrev tw8_spec := EO.EA.tw8_spec
@[local step]
abbrev tw4_spec := EO.EA.tw4_spec
abbrev words_eq_loop_spec := EO.EA.words_eq_loop_spec
@[local step]
abbrev tail_eq_spec := EO.EA.tail_eq_spec
@[local step]
abbrev short_eq_spec := EO.EA.short_eq_spec
@[local step]
abbrev words_eq_spec := EO.EA.words_eq_spec
abbrev match_len_loop_spec := EO.EA.match_len_loop_spec
@[local step]
abbrev match_len_spec := EO.EA.match_len_spec
abbrev verified_spec := EO.EA.verified_spec
abbrev emit_lits_loop_spec := EO.EA.emit_lits_loop_spec
@[local step]
abbrev emit_lits_spec := EO.EA.emit_lits_spec
@[local step]
abbrev emit_step_spec := EO.EA.emit_step_spec
@[local step]
theorem lane_emit_spec (input : Slice Std.U8) (out : Slice Std.U32) (pos d l lits ntok : Std.Usize)
    (hout : input.length ≤ out.length) (hpos : pos.val < input.length)
    (hntok : ntok.val ≤ pos.val)
    (hdec : LZ77.decode (toks out ntok.val) = some ((bytes input).take pos.val)) :
    slot.y_a_lane_emit input out pos d l lits ntok ⦃ fun r =>
      pos.val < r.1.2.val ∧ r.1.2.val ≤ input.length ∧ r.1.1.val ≤ r.1.2.val ∧
      r.2.length = out.length ∧
      LZ77.decode (toks r.2 r.1.1.val) = some ((bytes input).take r.1.2.val) ⦄ := by
  rw [slot.y_a_lane_emit]
  exact emit_step_spec input out pos d l lits ntok hout hpos hntok hdec
@[local step]
abbrev fl_ld8_spec := EO.EA.ld8_spec
section
attribute [local step] Submission.r70_ite_true_spec
theorem fl_len_loop_spec (input : Slice Std.U8) (a : Std.Usize) (b : Std.Usize) (cap : Std.Usize) (l : Std.Usize) (go : Std.Usize) (it : Std.Usize)  :
    slot.y_a_fl_len_loop input a b cap l go it ⦃ fun _ => True ⦄ := C1259! slot.y_a_fl_len_loop slot.y_a_fl_len_loop.body
end
attribute [local step] fl_len_loop_spec
section
attribute [local step] Submission.r70_ite_true_spec
theorem fl_len_spec (input : Slice Std.U8) (a : Std.Usize) (b : Std.Usize) (cap : Std.Usize) :
    slot.y_a_fl_len input a b cap ⦃ fun _ => True ⦄ := C12510! slot.y_a_fl_len
end
attribute [local step] fl_len_spec
section
attribute [local step] ite_true_spec
@[local step]
theorem fl_rle_parse_loop_spec (input : Slice Std.U8) (out0 : Slice Std.U32) (n : Std.Usize) (pos0 : Std.Usize) (ntok0 : Std.Usize)
    (hn : n.val = input.length) (hout : input.length ≤ out0.length)
    (hp : pos0.val ≤ n.val) (hntok : ntok0.val ≤ pos0.val)
    (hdec : LZ77.decode (toks out0 ntok0.val) = some ((bytes input).take pos0.val)) :
    slot.y_a_fl_rle_parse_loop input out0 n pos0 ntok0 ⦃ fun r =>
      r.2.1.val ≤ n.val ∧ r.2.2.val ≤ r.2.1.val ∧ r.1.length = out0.length ∧
      LZ77.decode (toks r.1 r.2.2.val) = some ((bytes input).take r.2.1.val) ⦄ := by
  rw [slot.y_a_fl_rle_parse_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => n.val - s.2.1.val)
    (inv := fun s =>
      s.2.1.val ≤ n.val ∧ s.2.2.val ≤ s.2.1.val ∧ s.1.length = out0.length ∧
      LZ77.decode (toks s.1 s.2.2.val) = some ((bytes input).take s.2.1.val))
  · rintro ⟨out, pos, ntok⟩ ⟨hpn, hnt, hlen, hde⟩
    simp only at hpn hnt hlen hde
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.y_a_fl_rle_parse_loop.body, lift, Array.to_slice_mut, alloc.vec.Vec.deref_mut, bind_tc_ok]
    split
    case isTrue hlt =>
      step*
      all_goals (repeat (first
        | (refine ⟨by scalar_tac, by scalar_tac, by assumption, by assumption, by scalar_tac⟩)
        | (intro hc; (try step*))
        | (casesm* _ × _; (try simp only []); (try step*))
        | (split <;> (try step*))
        | (step <;> (try step*))))
      all_goals (try scalar_tac)
    case isFalse hge =>
      exact ⟨hpn, hnt, hlen, hde⟩
  · exact ⟨hp, hntok, rfl, hdec⟩
end
attribute [local step] fl_rle_parse_loop_spec
section
attribute [local step] ite_true_spec
@[local step]
theorem fl_rle_parse_spec (input : Slice Std.U8) (out : Slice Std.U32)
    (hlen : input.length ≤ out.length) :
    slot.y_a_fl_rle_parse input out ⦃ fun r =>
      r.1.2.val ≤ input.length ∧ r.1.1.val ≤ r.1.2.val ∧ r.2.length = out.length ∧
      LZ77.decode (toks r.2 r.1.1.val) = some ((bytes input).take r.1.2.val) ⦄ := C12516! slot.y_a_fl_rle_parse
end
attribute [local step] fl_rle_parse_spec
@[local step]
abbrev h3_tab_step2_spec := EO.EA.tab_step2_spec
@[local step]
abbrev h3_back1_spec := EO.EA.back1_spec
@[local step]
abbrev h3_first_diff_spec := EO.EA.first_diff_spec
@[local step]
abbrev h3_ld8_spec := EO.EA.ld8_spec
@[local step]
abbrev h3_fast_len3_loop_spec := EO.EA.fast_len_loop_spec
@[local step]
abbrev h3_fast_len3_spec := EO.EA.fast_len_spec
@[local step]
abbrev h3_hashl_spec := EO.EA.hashl_spec
@[local step]
abbrev h3_tab_step_spec := EO.EA.tab_step_spec
@[local step]
abbrev h3_run_len_spec := EO.EA.run_len_spec
@[local step]
abbrev h3_fast_len_loop_spec := EO.EA.fast_len_loop_spec
@[local step]
abbrev h3_fast_len_spec := EO.EA.fast_len_spec
@[local step]
abbrev h3_q8ok_spec := EO.EA.q8ok_spec
@[local step]
abbrev h3_bext_loop_spec := EO.EA.bext_loop_spec
@[local step]
abbrev h3_bext_spec := EO.EA.bext_spec
@[local step]
abbrev h3_fast_len2_loop_spec := EO.EA.fast_len_loop_spec
@[local step]
abbrev h3_fast_len2_spec := EO.EA.fast_len_spec
@[local step]
abbrev sh_lc_spec := EO.EA.sh_lc_spec
@[local step]
abbrev sh_dc_spec := EO.EA.sh_dc_spec
@[local step]
abbrev sh_add_spec := EO.EA.sh_add_spec
@[local step]
abbrev sh_fill_loop_spec := EO.EA.sh_fill_loop_spec
@[local step]
abbrev sh_fill_spec := EO.EA.sh_fill_spec
@[local step]
abbrev sh_table_loop0_spec := EO.EA.sh_table_loop0_spec
@[local step]
abbrev sh_table_loop1_spec := EO.EA.sh_table_loop1_spec
@[local step]
abbrev sh_table_spec := EO.EA.sh_table_spec
section
attribute [local step] Submission.r70_ite_true_spec
theorem sh_rle_probe_loop_spec (input : Slice Std.U8) (cache : Array Std.U32 4096#usize)
  (stats : Array Std.U32 128#usize) (n : Std.Usize) (pos : Std.Usize)
  (ntok : Std.Usize) :
    slot.y_a_sh_rle_probe_loop input cache stats n pos ntok ⦃ fun _ => True ⦄ := by
  rw [slot.y_a_sh_rle_probe_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => 4096 - s.2.2.2.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1, x2, x3⟩ _
    simp only [slot.y_a_sh_rle_probe_loop.body, lift, Array.to_slice_mut]
    step*
    repeat (first
      | (intro hc; (try step*))
      | (split <;> (try step*))
      | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply spec_ite_cut <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals scalar_tac
  · trivial
end
attribute [local step] sh_rle_probe_loop_spec
section
attribute [local step] Submission.r70_ite_true_spec
theorem sh_rle_probe_spec (input : Slice Std.U8) (cache : Array Std.U32 4096#usize)
  (stats : Array Std.U32 128#usize) :
    slot.y_a_sh_rle_probe input cache stats ⦃ fun _ => True ⦄ := C1258! slot.y_a_sh_rle_probe
end
attribute [local step] sh_rle_probe_spec
@[local step]
abbrev sh_litrun_loop_spec := EO.EA.sh_litrun_loop_spec
@[local step]
abbrev sh_litrun_spec := EO.EA.sh_litrun_spec
section
attribute [local step] ite_true_spec
theorem sh_replay_loop_spec (input : Slice Std.U8) (out0 : Slice Std.U32) (cache : Array Std.U32 4096#usize) (q : Array Std.Usize 320#usize)
    (n pos0 ntok0 ix0 rem0 dist0 : Std.Usize)
    (hn : n.val = input.length) (hout : input.length ≤ out0.length)
    (hp : pos0.val ≤ n.val) (hntok : ntok0.val ≤ pos0.val)
    (hdec : LZ77.decode (toks out0 ntok0.val) = some ((bytes input).take pos0.val)) :
    slot.y_a_sh_replay_loop input out0 cache q n pos0 ntok0 ix0 rem0 dist0 ⦃ fun r =>
      r.2.1.val ≤ n.val ∧ r.2.2.val ≤ r.2.1.val ∧ r.1.length = out0.length ∧
      LZ77.decode (toks r.1 r.2.2.val) = some ((bytes input).take r.2.1.val) ⦄ := C12517! slot.y_a_sh_replay_loop slot.y_a_sh_replay_loop.body
end
section
attribute [local step] ite_true_spec
@[local step]
theorem sh_replay_spec (input : Slice Std.U8) (out : Slice Std.U32) (cache : Array Std.U32 4096#usize) (q : Array Std.Usize 320#usize)
    (hlen : input.length ≤ out.length) :
    slot.y_a_sh_replay input out cache q ⦃ fun r =>
      r.1.2.val ≤ input.length ∧ r.1.1.val ≤ r.1.2.val ∧ r.2.length = out.length ∧
      LZ77.decode (toks r.2 r.1.1.val) = some ((bytes input).take r.1.2.val) ⦄ := by
  rw [slot.y_a_sh_replay]
  have h0 := decode_nil input out
  try simp only [lift, Array.to_slice_mut, alloc.vec.Vec.deref_mut, bind_tc_ok]
  step*
  all_goals (try (step with sh_replay_loop_spec <;> try step*))
  all_goals (repeat (first
    | (refine ⟨by scalar_tac, by scalar_tac, by scalar_tac, by assumption⟩)
    | (intro hc; (try step*))
    | (casesm* _ × _; (try simp only []); (try step*))
    | (split <;> (try step*))
    | (step <;> (try step*))))
  all_goals (try scalar_tac)
end
attribute [local step] sh_replay_spec
section
attribute [local step] ite_true_spec
@[local step]
theorem sh_rle_phase_spec (SH_L_ : Std.U32) (SH_D_ : Std.U32) (SH_BUDGET_ : Std.Usize) (SH_DM_ : Std.U32) (input : Slice Std.U8) (out : Slice Std.U32)
    (hlen : input.length ≤ out.length) :
    slot.y_a_sh_rle_phase SH_L_ SH_D_ SH_BUDGET_ SH_DM_ input out ⦃ fun r =>
      r.1.2.val ≤ input.length ∧ r.1.1.val ≤ r.1.2.val ∧ r.2.length = out.length ∧
      LZ77.decode (toks r.2 r.1.1.val) = some ((bytes input).take r.1.2.val) ⦄ := C12516! slot.y_a_sh_rle_phase
end
attribute [local step] sh_rle_phase_spec
end EA
namespace EB
open EA
attribute [local step] EA.match_len_spec EA.verified_spec EA.emit_lits_spec EA.emit_step_spec EA.lane_emit_spec
open Aeneas Aeneas.Std Result ControlFlow
set_option maxRecDepth 8192
set_option maxHeartbeats 4000000
open LZ77 (toks bytes bytes_length bytes_getElem! Matches emit_lit emit_match ite_ok)
theorem decode_nil (input : Slice Std.U8) (out : Slice Std.U32) :
    LZ77.decode (toks out (0#usize).val) = some ((bytes input).take (0#usize).val) := by
  simp [toks, LZ77.decode]
theorem valid_of_decode {input : Slice Std.U8} {o : Slice Std.U32} {t p : Std.Usize}
    (hde : LZ77.decode (toks o t.val) = some ((bytes input).take p.val)) (hp : p.val = input.length) :
    LZ77.Valid (bytes input) (toks o t.val) := by
  unfold LZ77.Valid
  rw [hde, hp]
  simp
theorem spec_ite_cut {α : Type} (c : Prop) [Decidable c] (a b : Result α) (Q : α → Prop)
    (ha : c → a ⦃ Q ⦄) (hb : ¬c → b ⦃ Q ⦄) : (if c then a else b) ⦃ Q ⦄ := C1256!
theorem ite_prod_spec {α β : Type} (c : Prop) [Decidable c] (A B : Result (α × β))
    (hA : c → A ⦃ fun _ => True ⦄) (hB : ¬c → B ⦃ fun _ => True ⦄) :
    (if c then A else B) ⦃ fun _ => True ⦄ := C1257!
theorem ite_true_spec {α : Type} (c : Prop) [Decidable c] (A B : Result α)
    (hA : c → A ⦃ fun _ => True ⦄) (hB : ¬c → B ⦃ fun _ => True ⦄) :
    (if c then A else B) ⦃ fun _ => True ⦄ := C1257!
open LZ77
theorem copyN_take_prefix (acc : List Nat) (d : Nat) :
    ∀ n, (copyN acc d n).take acc.length = acc := C12518!
theorem foldlM_emit_length : ∀ (ts : List Nat) (init acc : List Nat),
    ts.foldlM emit init = some acc → init.length + ts.length ≤ acc.length := C12519!
theorem decode_length_le {ts acc : List Nat} (h : decode ts = some acc) :
    ts.length ≤ acc.length := C12520!
theorem decode_pop_lit {ts : List Nat} {t : Nat} {inp : List Nat} {p : Nat}
    (hp : p ≤ inp.length) (hd : decode (ts ++ [t]) = some (inp.take p)) (ht : t < 256) :
    1 ≤ p ∧ decode ts = some (inp.take (p - 1)) := C12521!
theorem decode_pop_match {ts : List Nat} {t : Nat} {inp : List Nat} {p : Nat}
    (hp : p ≤ inp.length) (hd : decode (ts ++ [t]) = some (inp.take p)) (ht : 256 ≤ t) :
    tokLen t ≤ p ∧ decode ts = some (inp.take (p - tokLen t)) := C12522!
theorem toks_pop (out : Slice Std.U32) (nt : Nat) (h0 : 0 < nt) (hle : nt ≤ out.length) :
    toks out nt = toks out (nt - 1) ++ [(out.val[nt - 1]!).val] := C12523!
theorem toks_length (out : Slice Std.U32) (nt : Nat) (h : nt ≤ out.length) :
    (toks out nt).length = nt := C12524!
def BackDec (input : Slice Std.U8) (out : Slice Std.U32) (nt p : Nat) : Prop :=
  p ≤ input.length ∧ nt ≤ p ∧ input.length ≤ out.length ∧
    LZ77.decode (toks out nt) = some ((bytes input).take p)
theorem BackDec.pop_lit {s : Slice Std.U8} {out : Slice Std.U32} {nt p : Nat} (h : BackDec s out nt p)
    (h0 : 0 < nt) (hle : nt ≤ out.length) (ht : (out.val[nt - 1]!).val < 256) :
    1 ≤ p ∧ BackDec s out (nt - 1) (p - 1) := C12525!
theorem BackDec.pop_match {s : Slice Std.U8} {out : Slice Std.U32} {nt p : Nat} (h : BackDec s out nt p)
    (h0 : 0 < nt) (hle : nt ≤ out.length) (ht : 256 ≤ (out.val[nt - 1]!).val) :
    tokLen (out.val[nt - 1]!).val ≤ p ∧
      BackDec s out (nt - 1) (p - tokLen (out.val[nt - 1]!).val) := C12526!
@[local step]
theorem merge_good_spec (l : Std.Usize) :
    (if l >= 3#usize then ok (decide (l <= 258#usize)) else ok false) ⦃ fun b =>
      b = true → 3 ≤ l.val ∧ l.val ≤ 258 ⦄ := by
  split <;> simp only [Std.WP.spec_ok]
  · intro h; constructor <;> scalar_tac
  · simp
end EB
set_option maxHeartbeats 1000000
@[local step]
theorem restart_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.y_restart input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.y_restart]
 exact EO.EA.main_part_spec _ _ _ _ _ input out 0#usize 0#usize 0#usize hlen (by simp) (by simp) (EO.EA.decode_nil input out)
@[local step]
theorem sparse_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) :
 slot.y_sparse input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.y_sparse]
 apply Std.WP.spec_bind (EA.sh_rle_phase_spec _ _ _ _ input out hlen)
 rintro ⟨⟨nt, p⟩, out'⟩ ⟨hp, ht, ho, hd⟩
 have hout : input.length ≤ out'.length := by rw [ho]; exact hlen
 simp only
 step*
 repeat' (split <;> step*)
 all_goals first
  | exact ⟨by scalar_tac, ho, EA.valid_of_decode hd (by scalar_tac)⟩
end EY
set_option maxHeartbeats 1000000
set_option hygiene false in
local notation "C12527!" => (by
  rcases System.Platform.numBits_eq with h | h <;> omega)
namespace N70
open EO.EA
attribute [local step] EO.EA.ld8_spec EO.EA.first_diff_spec EO.EA.fast_len_spec EO.EA.emit_lits_spec EO.EA.emit_step_spec
theorem bits32 : 32 ≤ System.Platform.numBits := C12527!
section
attribute [local step] EO.EA.ite_true_spec EO.EA.ite_prod_spec
set_option maxHeartbeats 4000000
@[local step]
theorem pure_ite_spec {α : Type} (c : Prop) [Decidable c] (a b : α) :
 (if c then ok a else ok b) ⦃ fun r => r = if c then a else b ⦄ := by
 split <;> simp_all [Std.WP.spec_ok]
set_option hygiene false in
local notation "C12528!" q0__:max => (by
  rw [q0__]
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (have := bits32; scalar_tac))
@[local step]
theorem n_hash_spec (H K : Std.Usize) (input : Slice Std.U8) (p : Std.Usize) :
 slot.n_hash H K input p ⦃ fun _ => True ⦄ := C12528! slot.n_hash
@[local step]
theorem n_choose_spec (SLOT a b : Std.Usize) :
 slot.n_choose SLOT a b ⦃ fun _ => True ⦄ := C12528! slot.n_choose
@[local step]
theorem n_eval_spec (input : Slice Std.U8) (p c : Std.Usize) :
 slot.n_eval input p c ⦃ fun _ => True ⦄ := C12528! slot.n_eval
@[local step]
theorem n_probe_loop_spec {H : Std.Usize} (REP SLOT : Std.Usize) (input : Slice Std.U8) (head : Array Std.U32 H) (p best j : Std.Usize) (hH : 8 < H.val) :
 slot.n_probe_loop REP SLOT input head p best j ⦃ fun _ => True ⦄ := by
  rw [slot.n_probe_loop]
  apply Std.loop.spec_decr_nat (measure := fun s => 4 - s.2.val) (inv := fun s => True)
  · rintro ⟨best, j⟩ _
    simp only [slot.n_probe_loop.body, lift, Array.to_slice_mut]
    step*
    all_goals (repeat (first
      | (intro hc; (try step*))
      | (split <;> (try step*))
      | (casesm* _ × _; (try simp only []); (try step*))
      | (apply spec_ite_cut <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*)))
    all_goals (try (have := bits32; scalar_tac))
    all_goals (try (simp only [ite_ok] at *; split at * <;> have := bits32 <;> scalar_tac))
    all_goals (try (have hmod : ∀ a b : Nat, a % b ≤ a := Nat.mod_le; have hshift : ∀ a b : Nat, a >>> b ≤ a := Nat.shiftRight_le; have := bits32; scalar_tac))
    all_goals (try (split at i5_post <;> scalar_tac))
    all_goals (try (
      have ht : i2.val ≤ it.val := by
        rw [i2_post1]
        exact Nat.shiftRight_le _ _
      have hb : 2000000 < Std.Usize.max := by
        rcases System.Platform.numBits_eq with h | h <;> norm_num [Std.Usize.max_def, Std.Usize.numBits, h]
      scalar_tac))
  · trivial
@[local step]
theorem n_probe_spec {H : Std.Usize} (K REP LINE SLOT : Std.Usize) (input : Slice Std.U8) (head : Array Std.U32 H) (p : Std.Usize) :
 slot.n_probe K REP LINE SLOT input head p ⦃ fun _ => True ⦄ := C12528! slot.n_probe
set_option hygiene false in
local notation "C12529!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat (measure := fun s => 258 - s.2.val) (inv := fun s => True)
  · rintro ⟨head, j⟩ _
    simp only [q1__, lift, Array.to_slice_mut]
    step*
    all_goals (repeat (first
      | (intro hc; (try step*))
      | (split <;> (try step*))
      | (casesm* _ × _; (try simp only []); (try step*))
      | (apply spec_ite_cut <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*)))
    all_goals (try (have := bits32; scalar_tac))
    all_goals (try (simp only [ite_ok] at *; split at * <;> have := bits32 <;> scalar_tac))
    all_goals (try (have hmod : ∀ a b : Nat, a % b ≤ a := Nat.mod_le; have hshift : ∀ a b : Nat, a >>> b ≤ a := Nat.shiftRight_le; have := bits32; scalar_tac))
    all_goals (try (split at i5_post <;> scalar_tac))
    all_goals (try (
      have ht : i2.val ≤ it.val := by
        rw [i2_post1]
        exact Nat.shiftRight_le _ _
      have hb : 2000000 < Std.Usize.max := by
        rcases System.Platform.numBits_eq with h | h <;> norm_num [Std.Usize.max_def, Std.Usize.numBits, h]
      scalar_tac))
  · trivial)
@[local step]
theorem n_insert_loop0_spec {H : Std.Usize} (K LINE INS STRIDE1 : Std.Usize) (input : Slice Std.U8) (head : Array Std.U32 H) («from» «to» j : Std.Usize) (hH : 8 < H.val) :
 slot.n_insert_loop0 K LINE INS STRIDE1 input head «from» «to» j ⦃ fun _ => True ⦄ := C12529! slot.n_insert_loop0 slot.n_insert_loop0.body
@[local step]
theorem n_insert_loop1_spec {H : Std.Usize} (K LINE INS STRIDE1 : Std.Usize) (input : Slice Std.U8) (head : Array Std.U32 H) («from» «to» j : Std.Usize) (hH : 8 < H.val) :
 slot.n_insert_loop1 K LINE INS STRIDE1 input head «from» «to» j ⦃ fun _ => True ⦄ := C12529! slot.n_insert_loop1 slot.n_insert_loop1.body
@[local step]
theorem n_insert_loop2_spec {H : Std.Usize} (K LINE INS STRIDE1 : Std.Usize) (input : Slice Std.U8) (head : Array Std.U32 H) («from» «to» j : Std.Usize) (hH : 8 < H.val) :
 slot.n_insert_loop2 K LINE INS STRIDE1 input head «from» «to» j ⦃ fun _ => True ⦄ := C12529! slot.n_insert_loop2 slot.n_insert_loop2.body
@[local step]
theorem n_insert_loop3_spec {H : Std.Usize} (K LINE INS STRIDE1 : Std.Usize) (input : Slice Std.U8) (head : Array Std.U32 H) («from» «to» j : Std.Usize) (hH : 8 < H.val) :
 slot.n_insert_loop3 K LINE INS STRIDE1 input head «from» «to» j ⦃ fun _ => True ⦄ := C12529! slot.n_insert_loop3 slot.n_insert_loop3.body
@[local step]
theorem n_insert_spec {H : Std.Usize} (K REP LINE INS STRIDE1 : Std.Usize) (input : Slice Std.U8) (head : Array Std.U32 H) («from» «to» d : Std.Usize) :
 slot.n_insert K REP LINE INS STRIDE1 input head «from» «to» d ⦃ fun _ => True ⦄ := C12528! slot.n_insert
@[local step]
theorem n_find_loop_spec {H : Std.Usize} (K REP LINE SLOT ACC LAZY : Std.Usize) (input : Slice Std.U8) (head : Array Std.U32 H) (n p it go : Std.Usize) (found : Std.U64)  :
 slot.n_find_loop K REP LINE SLOT ACC LAZY input head n p it go found ⦃ fun _ => True ⦄ := by
  rw [slot.n_find_loop]
  apply Std.loop.spec_decr_nat (measure := fun s => 2000000 - s.2.2.1.val) (inv := fun s => True)
  · rintro ⟨head, p, it, go, found⟩ _
    simp only [slot.n_find_loop.body, lift, Array.to_slice_mut]
    step*
    all_goals (repeat (first
      | (intro hc; (try step*))
      | (split <;> (try step*))
      | (casesm* _ × _; (try simp only []); (try step*))
      | (apply spec_ite_cut <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*)))
    all_goals (try (cases x <;> simp only [] <;> step*))
    all_goals (repeat (first | (split <;> try step*) | (step <;> try step*) | (casesm* _ × _ <;> try step*)))
    all_goals (try (have := bits32; scalar_tac))
    all_goals (try (simp only [ite_ok] at *; split at * <;> have := bits32 <;> scalar_tac))
    all_goals (try (have hmod : ∀ a b : Nat, a % b ≤ a := Nat.mod_le; have hshift : ∀ a b : Nat, a >>> b ≤ a := Nat.shiftRight_le; have := bits32; scalar_tac))
    all_goals (try (split at i5_post <;> scalar_tac))
    all_goals (try (
      have ht : i2.val ≤ it.val := by
        rw [i2_post1]
        exact Nat.shiftRight_le _ _
      have hb : 2000000 < Std.Usize.max := by
        rcases System.Platform.numBits_eq with h | h <;> norm_num [Std.Usize.max_def, Std.Usize.numBits, h]
      scalar_tac))
  · trivial
@[local step]
theorem n_find_spec {H : Std.Usize} (K REP LINE SLOT ACC LAZY : Std.Usize) (input : Slice Std.U8) (head : Array Std.U32 H) (pos : Std.Usize) :
 slot.n_find K REP LINE SLOT ACC LAZY input head pos ⦃ fun _ => True ⦄ := C12528! slot.n_find
end
attribute [local step] n_find_spec n_insert_spec
@[local step]
theorem n_run_loop_spec {H : Std.Usize} (K REP LINE SLOT ACC LAZY INS STRIDE1 : Std.Usize) (input : Slice Std.U8) (out0 : Slice Std.U32) (head0 : Array Std.U32 H) (n : Std.Usize) (pos0 : Std.Usize) (ntok0 : Std.Usize)
    (hn : n.val = input.length) (hout : input.length ≤ out0.length)
    (hp : pos0.val ≤ n.val) (hntok : ntok0.val ≤ pos0.val)
    (hdec : LZ77.decode (toks out0 ntok0.val) = some ((bytes input).take pos0.val)) :
    slot.n_run_loop K REP LINE SLOT ACC LAZY INS STRIDE1 input out0 head0 n pos0 ntok0 ⦃ fun r =>
      r.1.val ≤ input.length ∧ r.2.length = out0.length ∧
      LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := C12514! slot.n_run_loop slot.n_run_loop.body
attribute [local step] n_run_loop_spec
@[local step]
theorem n_run_spec (H K REP LINE SLOT ACC LAZY INS STRIDE1 : Std.Usize)
 (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) :
 slot.n_run H K REP LINE SLOT ACC LAZY INS STRIDE1 input out
 ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.n_run]
 exact n_run_loop_spec _ _ _ _ _ _ _ _ input out (Array.repeat H 0#u32) (Slice.len input) 0#usize 0#usize (by simp) hlen (by simp) (by simp) (EO.EA.decode_nil input out)
end N70
attribute [local step] N70.n_run_spec
namespace D70
open EO.EA
attribute [local step] EO.EA.ld8_spec EO.EA.first_diff_spec EO.EA.fast_len_spec EO.EA.fast_len2_spec EO.EA.fast_len3_spec EO.EA.emit_lits_spec EO.EA.emit_step_spec
section
attribute [local step] EO.EA.ite_true_spec EO.EA.ite_prod_spec
set_option maxHeartbeats 2000000
end
end D70
set_option hygiene false in
local notation "C12530!" => (by
  have := u8_lt (input.val[p]!); have := u8_lt (input.val[p+1]!)
  have := u8_lt (input.val[p+2]!); have := u8_lt (input.val[p+3]!)
  have := u8_lt (input.val[p+4]!); have := u8_lt (input.val[p+5]!)
  have := u8_lt (input.val[p+6]!); have := u8_lt (input.val[p+7]!)
  simp only [word8]
  rcases (show k = 0 ∨ k = 1 ∨ k = 2 ∨ k = 3 ∨ k = 4 ∨ k = 5 ∨ k = 6 ∨ k = 7 by omega) with
    rfl | rfl | rfl | rfl | rfl | rfl | rfl | rfl <;> simp only [Nat.add_zero, Nat.pow_zero, Nat.pow_succ, Nat.one_mul,
    Nat.sub_self, Nat.reduceSub] <;> omega)
set_option hygiene false in
local notation "C12531!" => (by
  intro k hk
  have e : (256 : Nat) ^ (7 - k) = 2 ^ (64 - 8 * d) * 2 ^ (8 * (d - 1 - k)) := by
    rw [← pow_add, show (256 : Nat) = 2 ^ 8 by norm_num, ← pow_mul]
    congr 1; omega
  have key : word8 input a / 256 ^ (7 - k) = word8 input b / 256 ^ (7 - k) := by
    rw [e, ← Nat.div_div_eq_div_mul, ← Nat.div_div_eq_div_mul, h]
  have ha := word8_digit input a k (by omega)
  have hb := word8_digit input b k (by omega)
  rw [key] at ha
  scalar_tac)
set_option hygiene false in
local notation "C12532!" => (by
  intro k hk
  by_cases hkl : k < l
  · exact h k hkl
  · have := word8_prefix input (a + l) (b + l) d hd hw (k - l) (by omega)
    rw [show b + l + (k - l) = b + k by omega, show a + l + (k - l) = a + k by omega] at this
    exact this)
set_option hygiene false in
local notation "C12533!" => (by
  have h := Nat.two_pow_add_eq_or_of_lt ht (x / 2 ^ m)
  have hx' : 2 ^ m * (x / 2 ^ m) = x := by
    have := Nat.div_add_mod x (2 ^ m); omega
  rw [hx'] at h
  exact h.symm)
set_option hygiene false in
local notation "C12534!" => (by
  rw [Nat.shiftLeft_eq, U64.size_def]
  apply Nat.mod_eq_of_lt
  have : 2 ^ k ≤ 2 ^ 56 := Nat.pow_le_pow_right (by norm_num) hk
  have : x * 2 ^ k < 256 * 2 ^ 56 := by
    calc x * 2 ^ k < 256 * 2 ^ k := by
          apply Nat.mul_lt_mul_of_pos_right hx (Nat.two_pow_pos _)
      _ ≤ 256 * 2 ^ 56 := Nat.mul_le_mul_left _ this
  simp only [U64.numBits] at *
  omega)
set_option hygiene false in
local notation "C12535!" => (by
  rw [shl_byte 56 ha (by norm_num), shl_byte 48 hb (by norm_num), shl_byte 40 hc (by norm_num),
    shl_byte 32 hd (by norm_num), shl_byte 24 he (by norm_num), shl_byte 16 hf (by norm_num),
    shl_byte 8 hg (by norm_num)]
  rw [or_eq_add_of_mod 56 (x := a * 2^56) (t := b * 2^48) (by omega) (by omega)]
  rw [or_eq_add_of_mod 48 (x := a * 2^56 + b * 2^48) (t := c * 2^40) (by omega) (by omega)]
  rw [or_eq_add_of_mod 40 (x := a * 2^56 + b * 2^48 + c * 2^40) (t := d * 2^32) (by omega)
    (by omega)]
  rw [or_eq_add_of_mod 32 (x := a * 2^56 + b * 2^48 + c * 2^40 + d * 2^32) (t := e * 2^24)
    (by omega) (by omega)]
  rw [or_eq_add_of_mod 24 (x := a * 2^56 + b * 2^48 + c * 2^40 + d * 2^32 + e * 2^24)
    (t := f * 2^16) (by omega) (by omega)]
  rw [or_eq_add_of_mod 16
    (x := a * 2^56 + b * 2^48 + c * 2^40 + d * 2^32 + e * 2^24 + f * 2^16)
    (t := g * 2^8) (by omega) (by omega)]
  rw [or_eq_add_of_mod 8
    (x := a * 2^56 + b * 2^48 + c * 2^40 + d * 2^32 + e * 2^24 + f * 2^16 + g * 2^8)
    (t := h) (by omega) (by omega)])
set_option hygiene false in
local notation "C12536!" q0__:max => (by
  rw [q0__]
  step*
  simp only [← getElem!_pos] at *
  simp_all only [UScalar.val_or, U8.cast_U64_val_eq]
  rw [be8_nat (u8_lt _) (u8_lt _) (u8_lt _) (u8_lt _) (u8_lt _) (u8_lt _) (u8_lt _) (u8_lt _)]
  simp only [word8])
set_option hygiene false in
local notation "C12537!" => (by
  have : a ^^^ (a ^^^ b) = b := by rw [← Nat.xor_assoc, Nat.xor_self, Nat.zero_xor]
  rw [h, Nat.xor_zero] at this; exact this)
set_option hygiene false in
local notation "C12538!" => (by
  have h : (x ^^^ y) >>> m = 0 := by rw [Nat.shiftRight_eq_div_pow]; exact Nat.div_eq_of_lt hz
  rw [Nat.shiftRight_xor_distrib] at h
  have := nat_xor_eq_zero h
  simpa [Nat.shiftRight_eq_div_pow] using this)
set_option hygiene false in
local notation "C12539!" => (by
  unfold BitVec.leadingZeros
  split
  case isTrue h => subst h; simp
  case isFalse h =>
    have hz : z.toNat ≠ 0 := by
      intro h0; apply h; exact BitVec.eq_of_toNat_eq (by simpa using h0)
    have hlog : Nat.log 2 z.toNat < 64 := Nat.log_lt_of_lt_pow hz z.isLt
    have h1 : z.toNat < 2 ^ (Nat.log 2 z.toNat).succ := Nat.lt_pow_succ_log_self (by norm_num) _
    refine lt_of_lt_of_le h1 (Nat.pow_le_pow_right (by norm_num) ?_)
    omega)
set_option hygiene false in
local notation "C12540!" => (by
  unfold BitVec.leadingZeros
  simp only [h, if_false]
  omega)
set_option hygiene false in
local notation "C12541!" => (by
  simp only [lift, Std.WP.spec_ok, true_and]
  have hle : BitVec.leadingZeros x.bv ≤ 64 := by unfold BitVec.leadingZeros; split <;> omega
  simp only [core.num.U64.leading_zeros, UScalar.val, UScalarTy.U32_numBits_eq,
    BitVec.natCast_eq_ofNat, BitVec.toNat_ofNat, Nat.reducePow]
  omega)
set_option hygiene false in
local notation "C12542!" => (by
  have hle : BitVec.leadingZeros x.bv ≤ 64 := by unfold BitVec.leadingZeros; split <;> omega
  simp only [core.num.U64.leading_zeros, UScalar.val, UScalarTy.U32_numBits_eq,
    BitVec.natCast_eq_ofNat, BitVec.toNat_ofNat, Nat.reducePow]
  omega)
set_option hygiene false in
local notation "C12543!" => (by
  have hbv : z.bv ≠ 0 := by
    intro h0; apply hz0; exact UScalar.eq_of_val_eq (by simp [UScalar.val, h0])
  have hlt : BitVec.leadingZeros z.bv < 64 := leadingZeros_lt_of_ne z.bv hbv
  have hrv : r.val = BitVec.leadingZeros z.bv / 8 := by
    rw [hr, U32.cast_Usize_val_eq, hq, hlz, lz_val]
  rw [hpa] at hx; rw [hpb] at hy
  refine ⟨?_, by omega⟩
  rw [hk1, hrv]
  have hle : BitVec.leadingZeros z.bv ≤ 64 := by unfold BitVec.leadingZeros; split <;> omega
  apply Matches.add_prefix h (by omega)
  rw [← hx, ← hy]
  apply div_eq_of_xor_lt
  rw [← UScalar.val_xor, ← hz]
  exact lt_pow_leadingZeros z.bv)
set_option hygiene false in
local notation "C12544!" => (by
  have hxy : x.val = y.val := by
    apply nat_xor_eq_zero
    rw [← UScalar.val_xor, ← hz, hz0]; rfl
  rw [hpa] at hx; rw [hpb] at hy
  rw [hk1]
  apply Matches.add_prefix h (le_refl 8)
  rw [← hx, ← hy, hxy])
set_option hygiene false in
local notation "C12545!" => (by
  rw [hl1]
  apply LZ77.Matches.succ h
  rw [← hpa, ← hpb, getElem!_pos input.val pa.val hpa', getElem!_pos input.val pb.val hpb',
    ← hx, ← hy, hxy])
set_option hygiene false in
local notation "C12546!" q0__:max q1__:max => (by
  rw [q0__]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  apply Std.loop.spec_decr_nat
    (measure := fun r => cap.val - r.1.val + r.2.val)
    (inv := fun r => r.1.val ≤ cap.val ∧ Matches s a.val b.val r.1.val)
  · rintro ⟨k, run⟩ ⟨hk, hm⟩
    simp only at hk hm
    simp only [q1__]
    step*
    all_goals first
      | scalar_tac
      | (refine ⟨by scalar_tac, Matches.word_zero hm (by assumption) (by assumption)
          (by assumption) (by assumption) (by assumption) (by assumption) (by scalar_tac),
          by scalar_tac⟩)
      | (have hw := Matches.word_lz hm (by assumption) (by assumption) (by assumption)
          (by assumption) (by assumption) (by assumption) (by assumption) (by assumption)
          (by assumption) (by assumption)
         refine ⟨by scalar_tac, hw.1, by scalar_tac⟩)
  · exact ⟨hk, hm⟩)
set_option hygiene false in
local notation "C12547!" q0__:max q1__:max => (by
  rw [q0__]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  apply Std.loop.spec_decr_nat
    (measure := fun r => cap.val - r.1.val + r.2.val)
    (inv := fun r => r.1.val ≤ cap.val ∧ Matches s a.val b.val r.1.val)
  · rintro ⟨k, run⟩ ⟨hk, hm⟩
    simp only at hk hm
    simp only [q1__]
    step*
    all_goals first
      | scalar_tac
      | exact ⟨hk, hm⟩
      | (refine ⟨by scalar_tac, Matches.byte' hm (by assumption) (by assumption) (by scalar_tac)
          (by scalar_tac) (by assumption) (by assumption) (by assumption) (by assumption),
          by scalar_tac⟩)
  · exact ⟨hk, hm⟩)
set_option hygiene false in
local notation "C12548!" q0__:max => (by
  rw [q0__]
  apply Std.WP.spec_bind (common_loop0_spec s a b cap 0#usize 1#u32 ha hb hcap (by simp)
    (LZ77.Matches.zero s a.val b.val))
  rintro ⟨k, run⟩ ⟨hk, hm⟩
  exact common_loop1_spec s a b cap k run ha hb hk hm)
set_option hygiene false in
local notation "C12549!" => (by
  rw [hpa] at hx; rw [hpb] at hy
  rw [hk1]
  apply Matches.add_prefix h (le_refl 8)
  rw [← hx, ← hy, hxy])
set_option hygiene false in
local notation "C12550!" q0__:max q1__:max => (by
  rw [q0__]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  apply Std.loop.spec_decr_nat
    (measure := fun r => len.val - r.1.val + r.2.val)
    (inv := fun r => r.1.val ≤ len.val ∧ Matches s a.val b.val r.1.val)
  · rintro ⟨k, ok⟩ ⟨hk, hm⟩
    simp only at hk hm
    simp only [q1__]
    step*
    all_goals first
      | scalar_tac
      | (refine ⟨by scalar_tac, Matches.word_eq hm (by assumption) (by assumption)
          (by assumption) (by assumption) (by assumption) (by scalar_tac), by scalar_tac⟩)
  · exact ⟨hk, hm⟩)
set_option hygiene false in
local notation "C12551!" q0__:max q1__:max => (by
  rw [q0__]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  apply Std.loop.spec_decr_nat
    (measure := fun r => len.val - r.1.val + r.2.val)
    (inv := fun r => r.1.val ≤ len.val ∧ Matches s a.val b.val r.1.val)
  · rintro ⟨k, ok⟩ ⟨hk, hm⟩
    simp only at hk hm
    simp only [q1__]
    step*
    all_goals first
      | scalar_tac
      | (refine ⟨by scalar_tac, Matches.byte' hm (by assumption) (by assumption) (by scalar_tac)
          (by scalar_tac) (by assumption) (by assumption) (by assumption) (by assumption),
          by scalar_tac⟩)
  · exact ⟨hk, hm⟩)
set_option hygiene false in
local notation "C12552!" => (by
  have hw0 : w.val = 0 := by simpa using hw0
  rw [hpa] at hx; rw [hpb] at hy
  have := Matches.add_prefix (d := len - k) h (by omega) (by
    rw [← hx, ← hy, ← hsh]
    have h0 : (x.val ^^^ y.val) >>> sh.val = 0 := by rw [← UScalar.val_xor, ← hz, ← hw, hw0]
    rw [Nat.shiftRight_xor_distrib] at h0
    have := nat_xor_eq_zero h0
    simpa [Nat.shiftRight_eq_div_pow] using this)
  rw [show k + (len - k) = len by omega] at this
  exact this)
set_option hygiene false in
local notation "C12553!" q0__:max => (by
  rw [q0__]
  apply Std.WP.spec_bind (same_loop0_spec s a b len 0#usize 1#usize ha hb hlen (by simp)
    (LZ77.Matches.zero s a.val b.val))
  rintro ⟨k, ok⟩ ⟨hk, hm, hok⟩
  simp only at hk hm hok
  step*
  intro _
  exact Matches.mask hm (by assumption) (by assumption) (by assumption) (by assumption)
    (by assumption) (by assumption) (by assumption) (by scalar_tac) (by scalar_tac)
    (by scalar_tac))
set_option hygiene false in
local notation "C12554!" => (by
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
  omega)
set_option hygiene false in
local notation "C12555!" => (by
  simp only [lift, Std.WP.spec_ok, true_and]
  exact ⟨fun h => lz32_le x 2 (by norm_num) (by simpa using h),
    fun h => lz32_le x 3 (by norm_num) (by simpa using h)⟩)
set_option hygiene false in
local notation "C12556!" => (by
  intro j hj
  rw [Std.Array.repeat_val] at hj ⊢
  rw [List.getElem!_eq_getElem?_getD, List.getElem?_replicate_of_lt (by simpa using hj)]
  rfl)
set_option hygiene false in
local notation "C12557!" => (by
  intro j hj
  rw [Std.Array.set_val_eq] at hj ⊢
  rw [List.length_set] at hj
  by_cases hja : a.val = j
  · subst hja
    rw [List.getElem!_eq_getElem?_getD, List.getElem?_set_self hj]
    exact hv
  · rw [List.getElem!_eq_getElem?_getD, List.getElem?_set_ne hja, ← List.getElem!_eq_getElem?_getD]
    exact h j hj)
set_option hygiene false in
local notation "C12558!" => (by
  subst h1
  apply HeadBound.set h a v
  rw [hv]
  have : (UScalar.cast .U32 i).val = i.val % 2 ^ 32 := by
    simp only [UScalar.cast_val_eq, UScalarTy.U32_numBits_eq]
  rw [this]
  exact le_trans (Nat.mod_le _ _) hi)
set_option hygiene false in
local notation "C12559!" => (by
  have := h a.val ha
  rw [getElem!_pos head.val a.val ha, ← hx] at this
  exact this)
set_option hygiene false in
local notation "C12560!" q0__:max => (by
  rw [q0__]
  step*
  have hold : old.val ≤ B := HeadBound.get hB a old (by scalar_tac) (by assumption)
  exact ⟨cast_usize_le (by assumption) hold,
    HeadBound.update hB (by assumption) (by omega) (by assumption)⟩)
set_option hygiene false in
local notation "C12561!" => (by
  have hsz : 4294967296 ≤ Usize.size := by scalar_tac
  have hpl : p.val < Usize.size := by scalar_tac
  have hdv : d.val = p.val - c.val := by
    rw [hd, core.num.Usize.wrapping_sub_val_eq, UScalar.size_UScalarTyUsize]
    rw [show p.val + (Usize.size - c.val) = (p.val - c.val) + Usize.size by omega,
      Nat.add_mod_right, Nat.mod_eq_of_lt (by omega)]
  have hiv : i.val < 32768 := by scalar_tac
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
      omega)
set_option hygiene false in
local notation "C12562!" => (by
  obtain ⟨hdv, hd1, hd2⟩ := dist_of_wrapping hc hd hi hlt
  refine Or.inr ⟨hd1, hd2, by omega, hl, ?_⟩
  rw [show p.val - d.val = c.val by omega]
  exact hm)
set_option hygiene false in
local notation "C12563!" q0__:max q1__:max => (by
  rw [q0__]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  apply Std.loop.spec_decr_nat
    (measure := fun r => r.2.2.2.2.1.val)
    (inv := fun r => r.2.2.2.1.val ≤ p.val ∧ p.val + r.1.val ≤ s.length ∧
      Cand s p.val cap.val r.1.val r.2.1.val)
  · rintro ⟨best, bd, bg, c, k, pb⟩ ⟨hc, hbest, hcand⟩
    simp only at hc hbest hcand
    simp only [q1__]
    step*
    repeat' (split <;> step*)
    all_goals first
      | exact (dist_of_wrapping hc (by assumption) (by assumption) (by assumption)).2.2
      | (refine ⟨by scalar_tac, by scalar_tac, Cand.of_common hc (by assumption) (by assumption)
          (by assumption) (by assumption) (by assumption), by scalar_tac⟩)
  · exact ⟨hc, hbest, hcand⟩)
set_option hygiene false in
local notation "C12564!" q0__:max => (by
  rw [q0__]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  repeat' (split <;> step*)
  all_goals
    exact walk_loop_spec s prev p cap gm (Std.Slice.len s) «have» 0#usize _ start depth _ _
      (by simp) hcap hcap258 hst hhave (Or.inl rfl) hW)
set_option hygiene false in
local notation "C12565!" => (by
  have hd' : d.val ≠ 0 := by intro h; apply hd; exact UScalar.eq_of_val_eq (by simp [h])
  rcases hc with h0 | ⟨hd1, hd2, hdp, hl, hm⟩
  · exact absurd h0 hd'
  · rcases Nat.lt_or_ge l.val 3 with h3 | h3
    · exact Or.inl h3
    · exact Or.inr ⟨h3, by omega, hpl, hd1, hd2, hdp, hm⟩)
set_option hygiene false in
local notation "C12566!" => (by
  have hd' : d.val ≠ 0 := by intro h; apply hd; exact UScalar.eq_of_val_eq (by simp [h])
  rcases hc with h0 | ⟨_, _, _, hl, _⟩
  · exact absurd h0 hd'
  · omega)
set_option hygiene false in
local notation "C12567!" => (by
  rcases hc with h0 | ⟨_, hd, _⟩ <;> omega)
set_option hygiene false in
local notation "C12568!" => (by
  rcases hf with h | h
  · omega
  · exact h)
set_option hygiene false in
local notation "C12569!" q0__:max => (by
  rw [q0__]
  step*
  repeat' (split <;> step*)
  all_goals first
    | exact ⟨FoundAt.none s p.val, by simp, by simp⟩
    | exact ⟨FoundAt.of_cand (by assumption) (by assumption) (by scalar_tac) (by assumption),
        Cand.len_le (by assumption) (by assumption) (by scalar_tac),
        Cand.dist_le (by assumption)⟩)
set_option hygiene false in
local notation "C12570!" => (by
  obtain ⟨hps, hntp, hso, hde⟩ := h
  have hntl : ntU.val < out.length := by omega
  refine ⟨by omega, by omega, by rw [Std.Slice.set_length]; exact hso, ?_⟩
  rw [← hnt]
  refine emit_lit s out ntU p v (by rw [hnt]; exact hde) hp hntl ?_
  have hpl : p < s.val.length := hp
  rw [hv, bytes_getElem! s p hpl, getElem!_pos s.val p hpl])
set_option hygiene false in
local notation "C12571!" => (by
  obtain ⟨hps, hntp, hso, hde⟩ := h
  obtain ⟨h3, h258, hpl, hd1, hd32, hdp, hmm⟩ := hm
  have hntl : ntU.val < out.length := by omega
  refine ⟨by omega, by omega, by rw [Std.Slice.set_length]; exact hso, ?_⟩
  rw [← hnt]
  exact emit_match s out ntU p d l v (by rw [hnt]; exact hde) hntl hd1 hdp hd32 h3 h258 hpl hmm hv)
set_option hygiene false in
local notation "C12572!" => (by
  obtain ⟨hps, hntp, hso, hde⟩ := h
  refine ⟨by omega, ?_⟩
  unfold LZ77.Valid
  rw [hde, show p = s.length by omega, ← bytes_length, List.take_length])
set_option hygiene false in
local notation "C12573!" => (by
  subst hout1
  refine ⟨hnt1, Std.Slice.set_length .., ?_⟩
  rw [hnt1]
  exact Dec.lit h hp ntU rfl v (by rw [hv, U8.cast_U32_val_eq, hb, getElem!_pos s.val pU.val hp]))
set_option hygiene false in
local notation "C12574!" q0__:max => (by
  rw [q0__]
  step*
  exact Dec.lit_step hdec (by scalar_tac) (by assumption) (by assumption) (by assumption)
    (by assumption))
set_option hygiene false in
local notation "C12575!" => (by
  subst hout1
  refine ⟨hnt1, he, Std.Slice.set_length .., ?_⟩
  rw [hnt1, he]
  exact Dec.match h hm ntU rfl v hv)
set_option hygiene false in
local notation "C12576!" q0__:max => (by
  rw [q0__]
  have hm' := hm
  obtain ⟨h3, h258, hpl, hd1, hd32, hdp, _⟩ := hm'
  step*
  exact Dec.match_step hdec hm (by assumption)
    (by simp only [LZ77.mkMatch, LZ77.MATCH_BASE]; scalar_tac) (by assumption) (by assumption))
set_option hygiene false in
local notation "C12577!" => (by
  obtain ⟨h3, h258, hpl, hd1, hd32, _, hm⟩ := h
  refine ⟨by omega, by omega, by omega, hd1, hd32, by omega, ?_⟩
  intro k hk
  rcases Nat.eq_zero_or_pos k with hk0 | hk0
  · subst hk0
    rw [Nat.add_zero, Nat.add_zero, show p - 1 - d = p - 1 - d by rfl]
    exact heq
  · have := hm (k - 1) (by omega)
    rw [show p - 1 + k = p + (k - 1) by omega, show p - 1 - d + k = p - d + (k - 1) by omega]
    exact this)
set_option hygiene false in
local notation "C12578!" => (by
  obtain ⟨h3, h258, hpl, hd1, hd32, _, hm⟩ := h
  refine ⟨by omega, by omega, by omega, hd1, hd32, hdw, ?_⟩
  intro k hk
  rcases Nat.lt_or_ge k w with hkw | hkw
  · have := hmw k hkw
    rw [show p - w - d = p - w - d by rfl] at this
    exact this
  · have := hm (k - w) (by omega)
    rw [show p - w + k = p + (k - w) by omega, show p - w - d + k = p - d + (k - w) by omega]
    exact this)
set_option hygiene false in
local notation "C12579!" => (by
  obtain ⟨hdec, hm, hE, hP⟩ := h
  have ht' : (out.val[nt.val - 1]!).val < 256 := by
    rw [← hi1, getElem!_pos out.val i1.val hi1l, ← ht]; scalar_tac
  obtain ⟨hp1, hdec'⟩ := Dec.pop_lit hdec (by omega) hntl ht'
  have heq : input.val[p.val - 1]! = input.val[p.val - 1 - d]! := by
    rw [← hi2, getElem!_pos input.val i2.val hi2l, show i2.val - d = i4.val by omega,
      getElem!_pos input.val i4.val hi4l, ← hx, ← hy, hxy]
  have hm' := MatchAt.back_lit hm hl hdp heq
  rw [hi1, hi2, hl1]
  exact ⟨hdec', hm', by omega, by omega⟩)
set_option hygiene false in
local notation "C12580!" => (by
  obtain ⟨hdec, hm, hE, hP⟩ := h
  have htv : (out.val[nt.val - 1]!).val = t.val := by
    rw [← hi1, getElem!_pos out.val i1.val hi1l, ← ht]
  have hwv' : w.val = tokLen (out.val[nt.val - 1]!).val := by
    rw [htv, hwv]
    simp only [tokLen, MATCH_BASE]
  obtain ⟨hwl, hdec'⟩ := Dec.pop_match hdec (by omega) hntl (by omega)
  rw [← hwv'] at hdec'
  have hmw : Matches input (p.val - w.val - d) (p.val - w.val) w.val := by
    have := hsame (by rw [hi12]; rfl)
    rw [hi11, hi10] at this
    exact this
  have hm' := MatchAt.back_match hm (by omega) hwp (by omega) hmw
  rw [hi1, hi10, hi9]
  exact ⟨hdec', hm', by omega, by omega⟩)
set_option hygiene false in
local notation "C12581!" => (by
  subst hi
  refine ⟨hdec, hlen, ?_, HeadBound.mono hB hBi, hilim, hins⟩
  rcases hf with h | h
  · omega
  · exact h)
set_option hygiene false in
local notation "C12582!" => (by
  obtain ⟨hdec, hlen, hm, _, hplim, _⟩ := h
  exact ⟨hdec, hlen, hm, HeadBound.mono hB hBp, hplim, hins1⟩)
set_option hygiene false in
local notation "C12583!" q0__:max q1__:max => (by
  rw [q0__]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  apply Std.loop.spec_decr_nat
    (measure := fun r => lim.val - r.2.2.1.val + r.2.2.2.2.2.2.2.2.val)
    (inv := fun r => LazyInv input L lim.val r.1 r.2.1.val r.2.2.1.val r.2.2.2.1
      r.2.2.2.2.2.1.val r.2.2.2.2.2.2.1.val r.2.2.2.2.2.2.2.1.val)
  · rintro ⟨out, nt, p, head, prev, ins, l, d, go⟩ hinv
    simp only at hinv
    have hinv' := hinv
    obtain ⟨⟨hps, hntp, hso, _⟩, hL, ⟨h3, h258, hpl, hd1, hd32, hdp, _⟩, hB, hplim, hins⟩ := hinv'
    simp only [q1__]
    step*
    repeat' (split <;> step*)
    all_goals first
      | exact hinv.1
      | (refine ⟨LazyInv.accept (by assumption) (by scalar_tac) (by scalar_tac) (by assumption)
          (by scalar_tac) hminl (by assumption) (by scalar_tac) (by scalar_tac) (by scalar_tac),
          by scalar_tac⟩)
      | (refine ⟨LazyInv.reject hinv (by assumption) (by scalar_tac) (by scalar_tac),
          by scalar_tac⟩)
  · exact hinv)
set_option hygiene false in
local notation "C12584!" => (by
  apply Std.WP.spec_mono (lazy_loop_inv input out cls nt p mask minl lazy head prev lim ins l d go L
    hlim hminl hminl8 hH hW ⟨hdec, hlen, hm, hB, hplim, hins⟩)
  rintro ⟨out', nt', p', head', prev', ins', l', d'⟩ ⟨hdec', hlen', hm', hB', hplim', hins'⟩
  exact ⟨hdec', hlen', hm', HeadBound.mono hB' (by have := hm'.1; omega), hplim', hins', hm'.1⟩)
set_option hygiene false in
local notation "C12585!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun r => p.val - r.2.2.val)
    (inv := fun r => HeadBound r.1 B)
  · rintro ⟨head, prev, ins⟩ hB
    simp only at hB
    simp only [q1__]
    step*
  · exact hB)
set_option hygiene false in
local notation "C12586!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun r => stop.val - r.2.2.val)
    (inv := fun r => HeadBound r.1 B ∧ (r.2.2.val ≤ ins.val ∨ r.2.2.val ≤ stop.val))
  · rintro ⟨head, prev, ins'⟩ ⟨hB, hins⟩
    simp only at hB hins
    simp only [q1__]
    step*
  · exact ⟨hB, Or.inl (le_refl _)⟩)
set_option hygiene false in
local notation "C12587!" q0__:max q1__:max q2__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun r => «end».val - r.2.2.val)
    (inv := fun r => HeadBound r.1 B ∧ r.2.2.val ≤ «end».val ∧
      (r.2.2.val ≤ ins.val ∨ r.2.2.val + q1__ < «end».val))
  · rintro ⟨head, prev, ins'⟩ ⟨hB, hie', hins⟩
    simp only at hB hie' hins
    simp only [q2__]
    step*
    all_goals first
      | exact ⟨hB, hie', hins⟩
      | exact ⟨by assumption, by scalar_tac, by scalar_tac, by scalar_tac⟩
  · exact ⟨hB, hie, Or.inl (le_refl _)⟩)
set_option hygiene false in
local notation "C12588!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun r => «end».val - r.2.2.val)
    (inv := fun r => HeadBound r.1 B ∧ (r.2.2.val ≤ ins.val ∨ r.2.2.val ≤ «end».val))
  · rintro ⟨head, prev, ins'⟩ ⟨hB, hins⟩
    simp only at hB hins
    simp only [q1__]
    step*
  · exact ⟨hB, Or.inl (le_refl _)⟩)
set_option hygiene false in
local notation "C12589!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun r => r.2.2.2.val)
    (inv := fun r => Dec input r.1 r.2.1.val r.2.2.1.val ∧ r.1.length = out.length ∧
      p.val ≤ r.2.2.1.val)
  · rintro ⟨out', nt', p', step'⟩ ⟨hdec', hlen', hp'⟩
    simp only at hdec' hlen' hp'
    simp only [q1__]
    step*
  · exact ⟨hdec, rfl, le_refl _⟩)
set_option hygiene false in
local notation "C12590!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun r => n.val - r.2.2.val)
    (inv := fun r => Dec input r.1 r.2.1.val r.2.2.val ∧ r.1.length = out.length)
  · rintro ⟨out', nt', p'⟩ ⟨hdec', hlen'⟩
    simp only at hdec' hlen'
    simp only [q1__]
    step*
    have hd := Dec.done hdec' (by scalar_tac)
    exact ⟨hd.1, hlen', hd.2⟩
  · exact ⟨hdec, rfl⟩)
set_option hygiene false in
local notation "C12591!" q0__:max q1__:max => (by
  rw [q0__]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  apply Std.loop.spec_decr_nat
    (measure := fun r => r.2.2.2.2.2.2.2.val)
    (inv := fun r => MainInv input L r.1 r.2.1.val r.2.2.1.val r.2.2.2.1 r.2.2.2.2.2.2.1.val)
  · rintro ⟨out, nt, p, head, prev, ins, miss, fuel⟩ hinv
    simp only at hinv
    have hinv' := hinv
    obtain ⟨hdec, hL, hB, hmiss⟩ := hinv'
    simp only [q1__]
    step*
    repeat' (split <;> step*)
    all_goals first
      | exact FoundAt.real (by assumption) (by scalar_tac)
      | exact HeadBound.mono (by assumption) (by scalar_tac)
      | (refine ⟨MainInv.mk' (by assumption) (by scalar_tac) (by assumption) (by scalar_tac)
          (by scalar_tac), by scalar_tac⟩)
      | (have := numBits_ge; scalar_tac)
  · exact hinv)
set_option hygiene false in
local notation "C12592!" q0__:max => (by
  rw [q0__]
  step*
  repeat' (split <;> step*)
  all_goals first
    | exact Dec.init input out hlen
    | exact HeadBound.init _)
namespace FX0
open Aeneas Aeneas.Std Result ControlFlow
set_option maxRecDepth 8192
set_option maxHeartbeats 4000000
set_option linter.unusedVariables false
open LZ77 (toks bytes bytes_length bytes_getElem! toks_update bytes_congr
  Matches Found emit_lit emit_match ite_ok)
open LZ77 (decode emit copyN tokLen tokDist MATCH_BASE TOK_LIMIT decode_snoc copyN_length)
@[irreducible] def word8 (input : Slice Std.U8) (p : Nat) : Nat :=
  (input.val[p]!).val * 2^56 + (input.val[p + 1]!).val * 2^48 + (input.val[p + 2]!).val * 2^40
    + (input.val[p + 3]!).val * 2^32 + (input.val[p + 4]!).val * 2^24
    + (input.val[p + 5]!).val * 2^16 + (input.val[p + 6]!).val * 2^8 + (input.val[p + 7]!).val
theorem u8_lt (x : Std.U8) : x.val < 256 := by scalar_tac
theorem word8_digit (input : Slice Std.U8) (p k : Nat) (hk : k < 8) :
    (input.val[p + k]!).val = word8 input p / 256 ^ (7 - k) % 256 := C12530!
theorem word8_prefix (input : Slice Std.U8) (a b d : Nat) (hd : d ≤ 8)
    (h : word8 input a / 2 ^ (64 - 8 * d) = word8 input b / 2 ^ (64 - 8 * d)) :
    ∀ k, k < d → input.val[b + k]! = input.val[a + k]! := C12531!
theorem Matches.add_prefix {input : Slice Std.U8} {a b l d : Nat} (h : Matches input a b l)
    (hd : d ≤ 8)
    (hw : word8 input (a + l) / 2 ^ (64 - 8 * d) = word8 input (b + l) / 2 ^ (64 - 8 * d)) :
    Matches input a b (l + d) := C12532!
theorem or_eq_add_of_mod {x t : Nat} (m : Nat) (hx : x % 2 ^ m = 0) (ht : t < 2 ^ m) :
    x ||| t = x + t := C12533!
theorem shl_byte {x : Nat} (k : Nat) (hx : x < 256) (hk : k ≤ 56) :
    x <<< k % U64.size = x * 2 ^ k := C12534!
theorem be8_nat {a b c d e f g h : Nat} (ha : a < 256) (hb : b < 256) (hc : c < 256)
    (hd : d < 256) (he : e < 256) (hf : f < 256) (hg : g < 256) (hh : h < 256) :
    (a <<< 56 % U64.size ||| b <<< 48 % U64.size ||| c <<< 40 % U64.size |||
      d <<< 32 % U64.size ||| e <<< 24 % U64.size ||| f <<< 16 % U64.size |||
      g <<< 8 % U64.size ||| h) =
    a * 2^56 + b * 2^48 + c * 2^40 + d * 2^32 + e * 2^24 + f * 2^16 + g * 2^8 + h := C12535!
@[local step]
theorem be8_spec (s : Slice Std.U8) (i : Std.Usize) (h : i.val + 8 ≤ s.length) :
    slot.fx0_be8 s i ⦃ fun v => v.val = word8 s i.val ⦄ := C12536! slot.fx0_be8
theorem nat_xor_eq_zero {a b : Nat} (h : a ^^^ b = 0) : a = b := C12537!
theorem div_eq_of_xor_lt {x y m : Nat} (hz : x ^^^ y < 2 ^ m) : x / 2 ^ m = y / 2 ^ m := C12538!
theorem lt_pow_leadingZeros (z : BitVec 64) :
    z.toNat < 2 ^ (64 - 8 * (BitVec.leadingZeros z / 8)) := C12539!
theorem leadingZeros_lt_of_ne (z : BitVec 64) (h : z ≠ 0) : BitVec.leadingZeros z < 64 := C12540!
@[local step]
theorem lz_spec (x : Std.U64) :
    lift (core.num.U64.leading_zeros x) ⦃ fun r => r = core.num.U64.leading_zeros x ∧ r.val ≤ 64 ⦄ := C12541!
theorem lz_val (x : Std.U64) :
    (core.num.U64.leading_zeros x).val = BitVec.leadingZeros x.bv := C12542!
theorem Matches.word_lz {input : Slice Std.U8} {a b k : Nat} {pa pb r k1 : Std.Usize}
    {x y z : Std.U64} {lz q : Std.U32}
    (h : Matches input a b k) (hpa : pa.val = a + k) (hpb : pb.val = b + k)
    (hx : x.val = word8 input pa.val) (hy : y.val = word8 input pb.val)
    (hz : z.val = (x ^^^ y).val) (hz0 : ¬z = 0#u64) (hlz : lz = core.num.U64.leading_zeros z)
    (hq : q.val = lz.val / 8) (hr : r = UScalar.cast .Usize q) (hk1 : k1.val = k + r.val) :
    Matches input a b k1.val ∧ k1.val < k + 8 := C12543!
theorem Matches.word_zero {input : Slice Std.U8} {a b k : Nat} {pa pb k1 : Std.Usize}
    {x y z : Std.U64}
    (h : Matches input a b k) (hpa : pa.val = a + k) (hpb : pb.val = b + k)
    (hx : x.val = word8 input pa.val) (hy : y.val = word8 input pb.val)
    (hz : z.val = (x ^^^ y).val) (hz0 : z = 0#u64) (hk1 : k1.val = k + 8) :
    Matches input a b k1.val := C12544!
theorem Matches.byte' {input : Slice Std.U8} {a b l : Nat} {pa pb l1 : Std.Usize}
    {x y : Std.U8} (h : Matches input a b l) (hpa : pa.val = a + l) (hpb : pb.val = b + l)
    (hpa' : pa.val < input.val.length) (hpb' : pb.val < input.val.length)
    (hx : x = input.val[pa.val]) (hy : y = input.val[pb.val]) (hxy : x = y)
    (hl1 : l1.val = l + 1) : Matches input a b l1.val := C12545!
theorem common_loop0_spec (s : Slice Std.U8) (a b cap k : Std.Usize) (run : Std.U32)
    (ha : a.val + cap.val ≤ s.length) (hb : b.val + cap.val ≤ s.length) (hcap : cap.val ≤ 258)
    (hk : k.val ≤ cap.val) (hm : Matches s a.val b.val k.val) :
    slot.fx0_common_loop0 s a b cap k run ⦃ fun r =>
      r.1.val ≤ cap.val ∧ Matches s a.val b.val r.1.val ⦄ := C12546! slot.fx0_common_loop0 slot.fx0_common_loop0.body
theorem common_loop1_spec (s : Slice Std.U8) (a b cap k : Std.Usize) (run : Std.U32)
    (ha : a.val + cap.val ≤ s.length) (hb : b.val + cap.val ≤ s.length)
    (hk : k.val ≤ cap.val) (hm : Matches s a.val b.val k.val) :
    slot.fx0_common_loop1 s a b cap k run ⦃ fun r =>
      r.val ≤ cap.val ∧ Matches s a.val b.val r.val ⦄ := C12547! slot.fx0_common_loop1 slot.fx0_common_loop1.body
@[local step]
theorem common_spec (s : Slice Std.U8) (a b cap : Std.Usize)
    (ha : a.val + cap.val ≤ s.length) (hb : b.val + cap.val ≤ s.length) (hcap : cap.val ≤ 258) :
    slot.fx0_common s a b cap ⦃ fun l => l.val ≤ cap.val ∧ Matches s a.val b.val l.val ⦄ := C12548! slot.fx0_common
theorem Matches.word_eq {input : Slice Std.U8} {a b k : Nat} {pa pb k1 : Std.Usize}
    {x y : Std.U64}
    (h : Matches input a b k) (hpa : pa.val = a + k) (hpb : pb.val = b + k)
    (hx : x.val = word8 input pa.val) (hy : y.val = word8 input pb.val)
    (hxy : x = y) (hk1 : k1.val = k + 8) :
    Matches input a b k1.val := C12549!
theorem same_loop0_spec (s : Slice Std.U8) (a b len k ok : Std.Usize)
    (ha : a.val + len.val ≤ s.length) (hb : b.val + len.val ≤ s.length) (hlen : len.val ≤ 258)
    (hk : k.val ≤ len.val) (hm : Matches s a.val b.val k.val) :
    slot.fx0_same_loop0 s a b len k ok ⦃ fun r =>
      r.1.val ≤ len.val ∧ Matches s a.val b.val r.1.val ∧ (r.2.val = 1 → len.val < r.1.val + 8) ⦄ := C12550! slot.fx0_same_loop0 slot.fx0_same_loop0.body
@[local step]
theorem same_loop1_spec (s : Slice Std.U8) (a b len k ok : Std.Usize)
    (ha : a.val + len.val ≤ s.length) (hb : b.val + len.val ≤ s.length)
    (hk : k.val ≤ len.val) (hm : Matches s a.val b.val k.val) :
    slot.fx0_same_loop1 s a b len k ok ⦃ fun r => r.val = 1 → Matches s a.val b.val len.val ⦄ := C12551! slot.fx0_same_loop1 slot.fx0_same_loop1.body
@[local step]
theorem same_loop2_spec (s : Slice Std.U8) (a b len k ok : Std.Usize)
    (ha : a.val + len.val ≤ s.length) (hb : b.val + len.val ≤ s.length)
    (hk : k.val ≤ len.val) (hm : Matches s a.val b.val k.val) :
    slot.fx0_same_loop2 s a b len k ok ⦃ fun r => r.val = 1 → Matches s a.val b.val len.val ⦄ := C12551! slot.fx0_same_loop2 slot.fx0_same_loop2.body
theorem Matches.mask {input : Slice Std.U8} {a b k len : Nat} {pa pb : Std.Usize}
    {x y z w : Std.U64} {sh : Std.U32}
    (h : Matches input a b k) (hpa : pa.val = a + k) (hpb : pb.val = b + k)
    (hx : x.val = word8 input pa.val) (hy : y.val = word8 input pb.val)
    (hz : z.val = (x ^^^ y).val) (hw : w.val = z.val >>> sh.val) (hw0 : ¬(w != 0#u64) = true)
    (hsh : sh.val = 64 - 8 * (len - k)) (hk : k < len) (hlen : len < k + 8) :
    Matches input a b len := C12552!
@[local step]
theorem same_spec (s : Slice Std.U8) (a b len : Std.Usize)
    (ha : a.val + len.val ≤ s.length) (hb : b.val + len.val ≤ s.length) (hlen : len.val ≤ 258)
    (ha8 : a.val + len.val + 7 ≤ Std.Usize.max) (hb8 : b.val + len.val + 7 ≤ Std.Usize.max) :
    slot.fx0_same s a b len ⦃ fun r => r.val = 1 → Matches s a.val b.val len.val ⦄ := C12553! slot.fx0_same
theorem lz32_le (x : Std.U32) (k : Nat) (hk : k < 32) (hx : 2 ^ k ≤ x.val) :
    (core.num.U32.leading_zeros x).val ≤ 31 - k := C12554!
@[local step]
theorem lz32_spec (x : Std.U32) :
    lift (core.num.U32.leading_zeros x) ⦃ fun r => r = core.num.U32.leading_zeros x ∧
      (4 ≤ x.val → r.val ≤ 29) ∧ (8 ≤ x.val → r.val ≤ 28) ⦄ := C12555!
@[local step]
theorem hcast_I32_spec {ty : UScalarTy} (x : UScalar ty) (h : x.val ≤ 2147483647) :
    lift (UScalar.hcast .I32 x) ⦃ fun y => y.val = x.val ⦄ :=
  UScalar.hcast_inBounds_spec .I32 x (by simp [I32.max_def, I32.numBits]; omega)
theorem GBASE_bound : -1000000000 ≤ slot.FX0_GBASE.val ∧ slot.FX0_GBASE.val ≤ 1000000000 := by
  unfold slot.FX0_GBASE
  simp
@[local step]
theorem gain_spec (l d : Std.Usize) (hl : l.val ≤ 258) (hd : d.val ≤ 32768) :
    slot.fx0_gain l d ⦃ fun _ => True ⦄ := by
  rw [slot.fx0_gain]
  have ⟨hG0, hG1⟩ := GBASE_bound
  repeat' (split <;> step*)
def HeadBound {N : Std.Usize} (head : Array Std.U32 N) (B : Nat) : Prop :=
  ∀ j : Nat, j < head.val.length → (head.val[j]!).val ≤ B
theorem HeadBound.mono {N : Std.Usize} {head : Array Std.U32 N} {B B' : Nat}
    (h : HeadBound head B) (hB : B ≤ B') : HeadBound head B' := fun j hj => le_trans (h j hj) hB
theorem HeadBound.init (N : Std.Usize) : HeadBound (Std.Array.repeat N 0#u32) 0 := C12556!
theorem HeadBound.set {N : Std.Usize} {head : Array Std.U32 N} {B : Nat} (h : HeadBound head B)
    (a : Std.Usize) (v : Std.U32) (hv : v.val ≤ B) : HeadBound (head.set a v) B := C12557!
theorem HeadBound.update {N : Std.Usize} {head head1 : Array Std.U32 N} {B : Nat}
    {a i : Std.Usize} {v : Std.U32} (h : HeadBound head B) (hv : v = UScalar.cast .U32 i)
    (hi : i.val ≤ B) (h1 : head1 = head.set a v) : HeadBound head1 B := C12558!
theorem HeadBound.get {N : Std.Usize} {head : Array Std.U32 N} {B : Nat} (h : HeadBound head B)
    (a : Std.Usize) (x : Std.U32) (ha : a.val < head.val.length) (hx : x = head.val[a.val]) :
    x.val ≤ B := C12559!
theorem cast_usize_le {x : Std.U32} {y : Std.Usize} {B : Nat} (h : y = UScalar.cast .Usize x)
    (hx : x.val ≤ B) : y.val ≤ B := by
  rw [h, U32.cast_Usize_val_eq]; exact hx
@[local step]
theorem be4_spec (s : Slice Std.U8) (i : Std.Usize) (hi : i.val + 4 ≤ Std.Usize.max) :
    slot.fx0_be4 s i ⦃ fun _ => True ⦄ := by
  rw [slot.fx0_be4]
  step*
@[local step]
theorem insert_spec (s : Slice Std.U8) {H W : Std.Usize} (head : Array Std.U32 H)
    (prev : Array Std.U32 W) (i : Std.Usize) (mask : Std.U32) (B : Nat) (hB : HeadBound head B)
    (hi : i.val < B + 1) (hi4 : i.val + 4 ≤ Std.Usize.max) (hH : 0 < H.val) (hW : 0 < W.val) :
    slot.fx0_insert s head prev i mask ⦃ fun r => r.1.val ≤ B ∧ HeadBound r.2.1 B ⦄ := C12560! slot.fx0_insert
def Cand (s : Slice Std.U8) (p cap best bd : Nat) : Prop :=
  bd = 0 ∨ (1 ≤ bd ∧ bd ≤ 32768 ∧ bd ≤ p ∧ best ≤ cap ∧ Matches s (p - bd) p best)
theorem dist_of_wrapping {p c d i : Std.Usize} (hc : c.val ≤ p.val)
    (hd : d = core.num.Usize.wrapping_sub p c) (hi : i = core.num.Usize.wrapping_sub d 1#usize)
    (hlt : i < 32768#usize) : d.val = p.val - c.val ∧ 1 ≤ d.val ∧ d.val ≤ 32768 := C12561!
theorem Cand.of_common {s : Slice Std.U8} {p c d i l cap : Std.Usize} (hc : c.val ≤ p.val)
    (hd : d = core.num.Usize.wrapping_sub p c) (hi : i = core.num.Usize.wrapping_sub d 1#usize)
    (hlt : i < 32768#usize) (hl : l.val ≤ cap.val) (hm : Matches s c.val p.val l.val) :
    Cand s p.val cap.val l.val d.val := C12562!
theorem walk_loop_spec (s : Slice Std.U8) {W : Std.Usize} (prev : Array Std.U32 W)
    (p cap gm n best bd : Std.Usize) (bg : Std.I32) (c k stop : Std.Usize) (pb : Std.U8)
    (hn : n.val = s.length) (hcap : p.val + cap.val ≤ s.length) (hcap258 : cap.val ≤ 258)
    (hc : c.val ≤ p.val) (hbest : p.val + best.val ≤ s.length)
    (hcand : Cand s p.val cap.val best.val bd.val) (hW : 0 < W.val) :
    slot.fx0_walk_loop s prev p cap gm n best bd bg c k stop pb ⦃ fun r =>
      p.val + r.1.val ≤ s.length ∧ Cand s p.val cap.val r.1.val r.2.val ⦄ := C12563! slot.fx0_walk_loop slot.fx0_walk_loop.body
@[local step]
theorem walk_spec (s : Slice Std.U8) {W : Std.Usize} (prev : Array Std.U32 W)
    (p start cap «have» depth gm : Std.Usize)
    (hcap : p.val + cap.val ≤ s.length) (hcap258 : cap.val ≤ 258) (hst : start.val ≤ p.val)
    (hhave : p.val + «have».val ≤ s.length) (hW : 0 < W.val) :
    slot.fx0_walk s prev p start cap «have» depth gm ⦃ fun r =>
      p.val + r.1.val ≤ s.length ∧ Cand s p.val cap.val r.1.val r.2.val ⦄ := C12564! slot.fx0_walk
def MatchAt (s : Slice Std.U8) (p l d : Nat) : Prop :=
  3 ≤ l ∧ l ≤ 258 ∧ p + l ≤ s.length ∧ 1 ≤ d ∧ d ≤ 32768 ∧ d ≤ p ∧ Matches s (p - d) p l
def FoundAt (s : Slice Std.U8) (p l d : Nat) : Prop := l < 3 ∨ MatchAt s p l d
theorem FoundAt.of_cand {s : Slice Std.U8} {p cap : Nat} {l d : Std.Usize}
    (hc : Cand s p cap l.val d.val) (hd : ¬d = 0#usize) (hcap : cap ≤ 258)
    (hpl : p + l.val ≤ s.length) : FoundAt s p l.val d.val := C12565!
theorem Cand.len_le {s : Slice Std.U8} {p cap : Nat} {l d : Std.Usize}
    (hc : Cand s p cap l.val d.val) (hd : ¬d = 0#usize) (hcap : cap ≤ 258) : l.val ≤ 258 := C12566!
theorem Cand.dist_le {s : Slice Std.U8} {p cap l d : Nat} (hc : Cand s p cap l d) :
    d ≤ 32768 := C12567!
theorem FoundAt.none (s : Slice Std.U8) (p : Nat) : FoundAt s p (0#usize).val (0#usize).val :=
  Or.inl (by simp)
theorem FoundAt.real {s : Slice Std.U8} {p l d : Nat} (hf : FoundAt s p l d) (h3 : 3 ≤ l) :
    MatchAt s p l d := C12568!
@[local step]
theorem find_spec (s : Slice Std.U8) {W : Std.Usize} (prev : Array Std.U32 W)
    (p st «have» minl depth gm : Std.Usize)
    (hp : p.val ≤ s.length) (hst : st.val ≤ p.val) (hhave : p.val + «have».val ≤ s.length)
    (hhave258 : «have».val ≤ 258) (hminl : 1 ≤ minl.val) (hminl' : p.val + minl.val ≤ s.length + 1)
    (hW : 0 < W.val) :
    slot.fx0_find s prev p st «have» minl depth gm ⦃ fun r => FoundAt s p.val r.1.val r.2.val ∧
      r.1.val ≤ 258 ∧ r.2.val ≤ 32768 ⦄ := C12569! slot.fx0_find
theorem copyN_take_prefix (acc : List Nat) (d : Nat) :
    ∀ n, (copyN acc d n).take acc.length = acc := C12518!
theorem foldlM_emit_length : ∀ (ts : List Nat) (init acc : List Nat),
    ts.foldlM emit init = some acc → init.length + ts.length ≤ acc.length := C12519!
theorem decode_length_le {ts acc : List Nat} (h : decode ts = some acc) :
    ts.length ≤ acc.length := C12520!
theorem decode_pop_lit {ts : List Nat} {t : Nat} {inp : List Nat} {p : Nat}
    (hp : p ≤ inp.length) (hd : decode (ts ++ [t]) = some (inp.take p)) (ht : t < 256) :
    1 ≤ p ∧ decode ts = some (inp.take (p - 1)) := C12521!
theorem decode_pop_match {ts : List Nat} {t : Nat} {inp : List Nat} {p : Nat}
    (hp : p ≤ inp.length) (hd : decode (ts ++ [t]) = some (inp.take p)) (ht : 256 ≤ t) :
    tokLen t ≤ p ∧ decode ts = some (inp.take (p - tokLen t)) := C12522!
theorem toks_pop (out : Slice Std.U32) (nt : Nat) (h0 : 0 < nt) (hle : nt ≤ out.length) :
    toks out nt = toks out (nt - 1) ++ [(out.val[nt - 1]!).val] := C12523!
theorem toks_length (out : Slice Std.U32) (nt : Nat) (h : nt ≤ out.length) :
    (toks out nt).length = nt := C12524!
def Dec (s : Slice Std.U8) (out : Slice Std.U32) (nt p : Nat) : Prop :=
  p ≤ s.length ∧ nt ≤ p ∧ s.length ≤ out.length ∧
    decode (toks out nt) = some ((bytes s).take p)
theorem Dec.init (input : Slice Std.U8) (out : Slice Std.U32) (h : input.length ≤ out.length) :
    Dec input out (0#usize).val (0#usize).val :=
  ⟨by simp, by simp, h, by simp [toks, LZ77.decode]⟩
theorem Dec.lit {s : Slice Std.U8} {out : Slice Std.U32} {nt p : Nat} (h : Dec s out nt p)
    (hp : p < s.length) (ntU : Std.Usize) (hnt : ntU.val = nt) (v : Std.U32)
    (hv : v.val = (s.val[p]!).val) :
    Dec s (out.set ntU v) (nt + 1) (p + 1) := C12570!
theorem Dec.match {s : Slice Std.U8} {out : Slice Std.U32} {nt p l d : Nat} (h : Dec s out nt p)
    (hm : MatchAt s p l d) (ntU : Std.Usize) (hnt : ntU.val = nt) (v : Std.U32)
    (hv : v.val = LZ77.mkMatch d l) :
    Dec s (out.set ntU v) (nt + 1) (p + l) := C12571!
theorem Dec.pop_lit {s : Slice Std.U8} {out : Slice Std.U32} {nt p : Nat} (h : Dec s out nt p)
    (h0 : 0 < nt) (hle : nt ≤ out.length) (ht : (out.val[nt - 1]!).val < 256) :
    1 ≤ p ∧ Dec s out (nt - 1) (p - 1) := C12525!
theorem Dec.pop_match {s : Slice Std.U8} {out : Slice Std.U32} {nt p : Nat} (h : Dec s out nt p)
    (h0 : 0 < nt) (hle : nt ≤ out.length) (ht : 256 ≤ (out.val[nt - 1]!).val) :
    tokLen (out.val[nt - 1]!).val ≤ p ∧
      Dec s out (nt - 1) (p - tokLen (out.val[nt - 1]!).val) := C12526!
theorem Dec.done {s : Slice Std.U8} {out : Slice Std.U32} {nt p : Nat} (h : Dec s out nt p)
    (hp : s.length ≤ p) : nt ≤ s.length ∧ LZ77.Valid (bytes s) (toks out nt) := C12572!
theorem Dec.lit_step {s : Slice Std.U8} {out out1 : Slice Std.U32} {ntU nt1 pU : Std.Usize}
    {b : Std.U8} {v : Std.U32} (h : Dec s out ntU.val pU.val) (hp : pU.val < s.val.length)
    (hb : b = s.val[pU.val]) (hv : v = UScalar.cast .U32 b) (hout1 : out1 = out.set ntU v)
    (hnt1 : nt1.val = ntU.val + 1) :
    nt1.val = ntU.val + 1 ∧ out1.length = out.length ∧ Dec s out1 nt1.val (pU.val + 1) := C12573!
@[local step]
theorem put_lit_spec (s : Slice Std.U8) (out : Slice Std.U32) (nt p : Std.Usize)
    (hdec : Dec s out nt.val p.val) (hp : p.val < s.length) :
    slot.fx0_put_lit s out nt p ⦃ fun r => r.1.val = nt.val + 1 ∧ r.2.length = out.length ∧
      Dec s r.2 r.1.val (p.val + 1) ⦄ := C12574! slot.fx0_put_lit
theorem Dec.match_step {s : Slice Std.U8} {out out1 : Slice Std.U32} {ntU nt1 pU dU lU e : Std.Usize}
    {v : Std.U32} (h : Dec s out ntU.val pU.val) (hm : MatchAt s pU.val lU.val dU.val)
    (hout1 : out1 = out.set ntU v) (hv : v.val = LZ77.mkMatch dU.val lU.val)
    (hnt1 : nt1.val = ntU.val + 1) (he : e.val = pU.val + lU.val) :
    nt1.val = ntU.val + 1 ∧ e.val = pU.val + lU.val ∧ out1.length = out.length ∧
      Dec s out1 nt1.val e.val := C12575!
@[local step]
theorem put_match_spec (s : Slice Std.U8) (out : Slice Std.U32) (nt p d l : Std.Usize)
    (hdec : Dec s out nt.val p.val) (hm : MatchAt s p.val l.val d.val) :
    slot.fx0_put_match s out nt p d l ⦃ fun r => r.1.1.val = nt.val + 1 ∧
      r.1.2.val = p.val + l.val ∧ r.2.length = out.length ∧ Dec s r.2 r.1.1.val r.1.2.val ⦄ := C12576! slot.fx0_put_match
theorem MatchAt.back_lit {s : Slice Std.U8} {p l d : Nat} (h : MatchAt s p l d) (hl : l < 258)
    (hdp : d < p) (heq : s.val[p - 1]! = s.val[p - 1 - d]!) : MatchAt s (p - 1) (l + 1) d := C12577!
theorem MatchAt.back_match {s : Slice Std.U8} {p l d w : Nat} (h : MatchAt s p l d)
    (hlw : l + w ≤ 258) (hw : w ≤ p) (hdw : d ≤ p - w) (hmw : Matches s (p - w - d) (p - w) w) :
    MatchAt s (p - w) (l + w) d := C12578!
def BackInv (input : Slice Std.U8) (out : Slice Std.U32) (d E P0 : Nat) (nt p l : Nat) : Prop :=
  Dec input out nt p ∧ MatchAt input p l d ∧ p + l = E ∧ p ≤ P0
theorem BackInv.lit {input : Slice Std.U8} {out : Slice Std.U32} {d E P0 : Nat}
    {nt p l i1 i2 i4 l1 : Std.Usize} {t : Std.U32} {x y : Std.U8}
    (h : BackInv input out d E P0 nt.val p.val l.val)
    (hi1 : i1.val = nt.val - 1) (hntl : nt.val ≤ out.length) (hnt0 : 1 ≤ nt.val)
    (hi1l : i1.val < out.val.length) (ht : t = out.val[i1.val]) (ht256 : t < 256#u32)
    (hi2 : i2.val = p.val - 1) (hi2l : i2.val < input.val.length) (hx : x = input.val[i2.val])
    (hxy : x = y) (hi4 : i4.val = i2.val - d) (hi4l : i4.val < input.val.length)
    (hy : y = input.val[i4.val]) (hl : l.val < 258) (hdp : d < p.val)
    (hl1 : l1.val = l.val + 1) :
    BackInv input out d E P0 i1.val i2.val l1.val := C12579!
theorem BackInv.match {input : Slice Std.U8} {out : Slice Std.U32} {d E P0 : Nat}
    {nt p l i1 w i9 i10 i11 i12 : Std.Usize} {t : Std.U32}
    (h : BackInv input out d E P0 nt.val p.val l.val)
    (hi1 : i1.val = nt.val - 1) (hntl : nt.val ≤ out.length) (hnt0 : 1 ≤ nt.val)
    (hi1l : i1.val < out.val.length) (ht : t = out.val[i1.val])
    (hsame : i12.val = 1 → Matches input i11.val i10.val w.val) (hi12 : i12 = 1#usize)
    (ht24 : 16777216 ≤ t.val) (hwv : w.val = (t.val - 16777216) % 256 + 3)
    (hi9 : i9.val = l.val + w.val) (hi9' : i9.val ≤ 258) (hi10 : i10.val = p.val - w.val)
    (hwp : w.val ≤ p.val) (hdw : d ≤ i10.val) (hi11 : i11.val = i10.val - d) :
    BackInv input out d E P0 i1.val i10.val i9.val := C12580!
theorem back_loop_inv (input : Slice Std.U8) (out : Slice Std.U32) (nt p l d back : Std.Usize)
    (E P0 : Nat) (hP0 : P0 + 8 ≤ input.length)
    (hinv : BackInv input out d.val E P0 nt.val p.val l.val) :
    slot.fx0_run_loop0_loop2 input out nt p l d back ⦃ fun r =>
      BackInv input out d.val E P0 r.1.val r.2.1.val r.2.2.val ⦄ := by
  rw [slot.fx0_run_loop0_loop2]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  apply Std.loop.spec_decr_nat
    (measure := fun r => slot.FX0_BACKTOK.val - r.2.2.2.val)
    (inv := fun r => BackInv input out d.val E P0 r.1.val r.2.1.val r.2.2.1.val)
  · rintro ⟨nt, p, l, back⟩ hinv
    simp only at hinv
    have hinv' := hinv
    obtain ⟨⟨hps, hntp, hso, _⟩, ⟨h3, h258, hpl, hd1, hd32, hdp, _⟩, hE, hp0⟩ := hinv'
    simp only [slot.fx0_run_loop0_loop2.body]
    step*
    all_goals first
      | (refine ⟨BackInv.lit hinv (by scalar_tac) (by scalar_tac) (by scalar_tac) (by scalar_tac)
          (by assumption) (by assumption) (by scalar_tac) (by scalar_tac) (by assumption)
          (by assumption) (by assumption) (by scalar_tac) (by assumption) (by scalar_tac)
          (by scalar_tac) (by scalar_tac), by scalar_tac⟩)
      | (refine ⟨BackInv.match hinv (by scalar_tac) (by scalar_tac) (by scalar_tac) (by scalar_tac)
          (by assumption) (by assumption) (by assumption) (by scalar_tac) (by scalar_tac)
          (by scalar_tac) (by scalar_tac) (by scalar_tac) (by scalar_tac) (by scalar_tac)
          (by scalar_tac), by scalar_tac⟩)
  · exact hinv
@[local step]
theorem back_loop_spec (input : Slice Std.U8) (out : Slice Std.U32) (nt p l d back : Std.Usize)
    (hp8 : p.val + 8 ≤ input.length) (hdec : Dec input out nt.val p.val)
    (hm : MatchAt input p.val l.val d.val) :
    slot.fx0_run_loop0_loop2 input out nt p l d back ⦃ fun r =>
      Dec input out r.1.val r.2.1.val ∧ MatchAt input r.2.1.val r.2.2.val d.val ∧
      r.2.1.val + r.2.2.val = p.val + l.val ∧ r.2.1.val ≤ p.val ⦄ := by
  apply Std.WP.spec_mono (back_loop_inv input out nt p l d back (p.val + l.val) p.val hp8
    ⟨hdec, hm, rfl, le_refl _⟩)
  intro r h
  exact h
def LazyInv (input : Slice Std.U8) (L lim : Nat) (out : Slice Std.U32) (nt p : Nat)
    {N : Std.Usize} (head : Array Std.U32 N) (ins l d : Nat) : Prop :=
  Dec input out nt p ∧ out.length = L ∧ MatchAt input p l d ∧ HeadBound head (p + 1) ∧
    p < lim ∧ ins ≤ p + 2
theorem LazyInv.accept {input : Slice Std.U8} {L lim p' B : Nat} {out1 : Slice Std.U32}
    {nt1 i ins1 l1 d1 minl : Std.Usize} {N : Std.Usize} {head1 : Array Std.U32 N}
    (hdec : Dec input out1 nt1.val p') (hi : i.val = p') (hlen : out1.length = L)
    (hf : FoundAt input i.val l1.val d1.val) (hl1 : minl.val ≤ l1.val) (hminl : 3 ≤ minl.val)
    (hB : HeadBound head1 B) (hBi : B ≤ i.val + 1) (hilim : i.val < lim)
    (hins : ins1.val ≤ i.val + 2) :
    LazyInv input L lim out1 nt1.val i.val head1 ins1.val l1.val d1.val := C12581!
theorem LazyInv.reject {input : Slice Std.U8} {L lim : Nat} {out : Slice Std.U32}
    {nt p ins ins1 l d B : Nat} {N : Std.Usize} {head head1 : Array Std.U32 N}
    (h : LazyInv input L lim out nt p head ins l d) (hB : HeadBound head1 B) (hBp : B ≤ p + 1)
    (hins1 : ins1 ≤ p + 2) : LazyInv input L lim out nt p head1 ins1 l d := C12582!
theorem lazy_loop_inv {H W : Std.Usize} (input : Slice Std.U8) (out : Slice Std.U32)
    (cls nt p : Std.Usize) (mask : Std.U32) (minl lazy : Std.Usize) (head : Array Std.U32 H)
    (prev : Array Std.U32 W) (lim ins l d : Std.Usize) (go : Std.U32) (L : Nat)
    (hlim : lim.val + 8 = input.length) (hminl : 3 ≤ minl.val) (hminl8 : minl.val ≤ 8)
    (hH : 0 < H.val) (hW : 0 < W.val)
    (hinv : LazyInv input L lim.val out nt.val p.val head ins.val l.val d.val) :
    slot.fx0_run_loop0_loop1 input out cls nt p mask minl lazy head prev lim ins l d go ⦃ fun r =>
      LazyInv input L lim.val r.1 r.2.1.val r.2.2.1.val r.2.2.2.1 r.2.2.2.2.2.1.val
        r.2.2.2.2.2.2.1.val r.2.2.2.2.2.2.2.val ⦄ := C12583! slot.fx0_run_loop0_loop1 slot.fx0_run_loop0_loop1.body
@[local step]
theorem lazy_loop_spec {H W : Std.Usize} (input : Slice Std.U8) (out : Slice Std.U32)
    (cls nt p : Std.Usize) (mask : Std.U32) (minl lazy : Std.Usize) (head : Array Std.U32 H)
    (prev : Array Std.U32 W) (lim ins l d : Std.Usize) (go : Std.U32) (L : Nat)
    (hlim : lim.val + 8 = input.length) (hminl : 3 ≤ minl.val) (hminl8 : minl.val ≤ 8)
    (hH : 0 < H.val) (hW : 0 < W.val)
    (hdec : Dec input out nt.val p.val) (hlen : out.length = L)
    (hm : MatchAt input p.val l.val d.val) (hB : HeadBound head (p.val + 1))
    (hplim : p.val < lim.val) (hins : ins.val ≤ p.val + 2) :
    slot.fx0_run_loop0_loop1 input out cls nt p mask minl lazy head prev lim ins l d go ⦃ fun r =>
      Dec input r.1 r.2.1.val r.2.2.1.val ∧ r.1.length = L ∧
      MatchAt input r.2.2.1.val r.2.2.2.2.2.2.1.val r.2.2.2.2.2.2.2.val ∧
      HeadBound r.2.2.2.1 (r.2.2.1.val + r.2.2.2.2.2.2.1.val) ∧ r.2.2.1.val < lim.val ∧
      r.2.2.2.2.2.1.val ≤ r.2.2.1.val + 2 ∧ 3 ≤ r.2.2.2.2.2.2.1.val ⦄ := C12584!
@[local step]
theorem ins_loop0_spec {H W : Std.Usize} (input : Slice Std.U8) (p : Std.Usize) (mask : Std.U32)
    (head : Array Std.U32 H) (prev : Array Std.U32 W) (ins : Std.Usize) (B : Nat)
    (hB : HeadBound head B) (hpB : p.val < B + 1) (hp4 : p.val + 4 ≤ Std.Usize.max)
    (hH : 0 < H.val) (hW : 0 < W.val) :
    slot.fx0_run_loop0_loop0 input p mask head prev ins ⦃ fun r => HeadBound r.1 B ⦄ := C12585! slot.fx0_run_loop0_loop0 slot.fx0_run_loop0_loop0.body
@[local step]
theorem ins_loop3_spec {H W : Std.Usize} (input : Slice Std.U8) (mask : Std.U32)
    (head : Array Std.U32 H) (prev : Array Std.U32 W) (ins stop : Std.Usize) (B : Nat)
    (hB : HeadBound head B) (hsB : stop.val < B + 1) (hs4 : stop.val + 4 ≤ Std.Usize.max)
    (hH : 0 < H.val) (hW : 0 < W.val) :
    slot.fx0_run_loop0_loop3 input mask head prev ins stop ⦃ fun r =>
      HeadBound r.1 B ∧ (r.2.2.val ≤ ins.val ∨ r.2.2.val ≤ stop.val) ⦄ := C12586! slot.fx0_run_loop0_loop3 slot.fx0_run_loop0_loop3.body
@[local step]
theorem stride_loop_spec {H W : Std.Usize} (input : Slice Std.U8) (mask : Std.U32)
    (head : Array Std.U32 H) (prev : Array Std.U32 W) (lim ins «end» : Std.Usize) (B : Nat)
    (hB : HeadBound head B) (heB : «end».val < B + 1) (hl4 : lim.val + 4 ≤ Std.Usize.max)
    (hH : 0 < H.val) (hW : 0 < W.val) (hS : 0 < slot.FX0_STRIDE.val)
    (hie : ins.val ≤ «end».val) :
    slot.fx0_run_loop0_loop4 input mask head prev lim ins «end» ⦃ fun r =>
      HeadBound r.1 B ∧ r.2.2.val ≤ «end».val ∧
        (r.2.2.val ≤ ins.val ∨ r.2.2.val + slot.FX0_TAIL.val < «end».val) ⦄ := C12587! slot.fx0_run_loop0_loop4 slot.FX0_TAIL.val slot.fx0_run_loop0_loop4.body
@[local step]
theorem ins_loop5_spec {H W : Std.Usize} (input : Slice Std.U8) (mask : Std.U32)
    (head : Array Std.U32 H) (prev : Array Std.U32 W) (lim ins «end» : Std.Usize) (B : Nat)
    (hB : HeadBound head B) (heB : «end».val < B + 1) (hl4 : lim.val + 4 ≤ Std.Usize.max)
    (hH : 0 < H.val) (hW : 0 < W.val) :
    slot.fx0_run_loop0_loop5 input mask head prev lim ins «end» ⦃ fun r =>
      HeadBound r.1 B ∧ (r.2.2.val ≤ ins.val ∨ r.2.2.val ≤ «end».val) ⦄ := C12588! slot.fx0_run_loop0_loop5 slot.fx0_run_loop0_loop5.body
@[local step]
theorem ins_loop6_spec {H W : Std.Usize} (input : Slice Std.U8) (mask : Std.U32)
    (head : Array Std.U32 H) (prev : Array Std.U32 W) (lim ins «end» : Std.Usize) (B : Nat)
    (hB : HeadBound head B) (heB : «end».val < B + 1) (hl4 : lim.val + 4 ≤ Std.Usize.max)
    (hH : 0 < H.val) (hW : 0 < W.val) :
    slot.fx0_run_loop0_loop6 input mask head prev lim ins «end» ⦃ fun r =>
      HeadBound r.1 B ∧ (r.2.2.val ≤ ins.val ∨ r.2.2.val ≤ «end».val) ⦄ := C12588! slot.fx0_run_loop0_loop6 slot.fx0_run_loop0_loop6.body
@[local step]
theorem skip_loop_spec (input : Slice Std.U8) (out : Slice Std.U32) (nt p lim step : Std.Usize)
    (hdec : Dec input out nt.val p.val) (hlim : lim.val ≤ input.length) :
    slot.fx0_run_loop0_loop7 input out nt p lim step ⦃ fun r =>
      Dec input r.1 r.2.1.val r.2.2.val ∧ r.1.length = out.length ∧ p.val ≤ r.2.2.val ⦄ := C12589! slot.fx0_run_loop0_loop7 slot.fx0_run_loop0_loop7.body
@[local step]
theorem tail_loop1_spec (input : Slice Std.U8) (out : Slice Std.U32) (n nt p : Std.Usize)
    (hn : n.val = input.length) (hdec : Dec input out nt.val p.val) :
    slot.fx0_run_loop1 input out n nt p ⦃ fun r => r.1.val ≤ input.length ∧
      r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := C12590! slot.fx0_run_loop1 slot.fx0_run_loop1.body
@[local step]
theorem tail_loop2_spec (input : Slice Std.U8) (out : Slice Std.U32) (n nt p : Std.Usize)
    (hn : n.val = input.length) (hdec : Dec input out nt.val p.val) :
    slot.fx0_run_loop2 input out n nt p ⦃ fun r => r.1.val ≤ input.length ∧
      r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := C12590! slot.fx0_run_loop2 slot.fx0_run_loop2.body
@[local step]
theorem tail_loop3_spec (input : Slice Std.U8) (out : Slice Std.U32) (n nt p : Std.Usize)
    (hn : n.val = input.length) (hdec : Dec input out nt.val p.val) :
    slot.fx0_run_loop3 input out n nt p ⦃ fun r => r.1.val ≤ input.length ∧
      r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := C12590! slot.fx0_run_loop3 slot.fx0_run_loop3.body
theorem numBits_ge : 32 ≤ System.Platform.numBits := C12527!
def MainInv (input : Slice Std.U8) (L : Nat) (out : Slice Std.U32) (nt p : Nat)
    {N : Std.Usize} (head : Array Std.U32 N) (miss : Nat) : Prop :=
  Dec input out nt p ∧ out.length = L ∧ HeadBound head p ∧ miss ≤ p
theorem MainInv.mk' {input : Slice Std.U8} {L : Nat} {out : Slice Std.U32} {nt p m B : Nat}
    {N : Std.Usize} {head : Array Std.U32 N} (hdec : Dec input out nt p) (hlen : out.length = L)
    (hB : HeadBound head B) (hBp : B ≤ p) (hm : m ≤ p) : MainInv input L out nt p head m :=
  ⟨hdec, hlen, HeadBound.mono hB hBp, hm⟩
set_option maxHeartbeats 16000000 in
theorem main_loop_spec {H W : Std.Usize} (input : Slice Std.U8) (out : Slice Std.U32)
    (cls nt p : Std.Usize) (mask : Std.U32) (minl depth lazy skip skcap : Std.Usize)
    (head : Array Std.U32 H) (prev : Array Std.U32 W)
    (lim ins miss fuel : Std.Usize) (L : Nat)
    (hlim : lim.val + 8 = input.length) (hminl : 3 ≤ minl.val) (hminl8 : minl.val ≤ 8)
    (hskip : skip.val < 32) (hH : 0 < H.val) (hW : 0 < W.val)
    (hinv : MainInv input L out nt.val p.val head miss.val) :
    slot.fx0_run_loop0 input out cls nt p mask minl depth lazy skip skcap head prev lim ins miss
      fuel ⦃ fun r => Dec input r.1 r.2.1.val r.2.2.val ∧ r.1.length = L ⦄ := C12591! slot.fx0_run_loop0 slot.fx0_run_loop0.body
@[local step]
theorem main_loop_spec' {H W : Std.Usize} (input : Slice Std.U8) (out : Slice Std.U32)
    (cls nt p : Std.Usize) (mask : Std.U32) (minl depth lazy skip skcap : Std.Usize)
    (head : Array Std.U32 H) (prev : Array Std.U32 W)
    (lim ins miss fuel : Std.Usize)
    (hlim : lim.val + 8 = input.length) (hminl : 3 ≤ minl.val) (hminl8 : minl.val ≤ 8)
    (hskip : skip.val < 32) (hH : 0 < H.val) (hW : 0 < W.val)
    (hdec : Dec input out nt.val p.val) (hB : HeadBound head p.val)
    (hmiss : miss.val ≤ p.val) :
    slot.fx0_run_loop0 input out cls nt p mask minl depth lazy skip skcap head prev lim ins miss
      fuel ⦃ fun r => Dec input r.1 r.2.1.val r.2.2.val ∧ r.1.length = out.length ⦄ :=
  main_loop_spec input out cls nt p mask minl depth lazy skip skcap head prev lim ins miss fuel
    out.length hlim hminl hminl8 hskip hH hW ⟨hdec, rfl, hB, hmiss⟩
def CntBound (cnt : Array Std.U32 256#usize) (T : Nat) : Prop :=
  ∀ j : Nat, j < 256 → (cnt.val[j]!).val ≤ T
theorem CntBound.init : CntBound (Std.Array.repeat 256#usize 0#u32) 0 := C1251!
theorem CntBound.get {cnt : Array Std.U32 256#usize} {T : Nat} (h : CntBound cnt T)
    (a : Std.Usize) (x : Std.U32) (ha : a.val < cnt.val.length) (hx : x = cnt.val[a.val]) :
    x.val ≤ T := C1252!
@[local step]
theorem cnt_index_spec (cnt : Array Std.U32 256#usize) (T : Nat) (h : CntBound cnt T)
    (i : Std.Usize) (hi : i.val < 256) :
    Std.Array.index_usize cnt i ⦃ fun x => x = cnt.val[i.val]! ∧ x.val ≤ T ⦄ := C1253!
theorem CntBound.update {cnt : Array Std.U32 256#usize} {T : Nat} (h : CntBound cnt T)
    (a : Std.Usize) (v : Std.U32) (hv : v.val ≤ T + 1) : CntBound (cnt.set a v) (T + 1) := C1254!
theorem CntBound.step {cnt a : Array Std.U32 256#usize} {T : Nat} {x : Std.Usize}
    {v tot1 : Std.U32} (hc : CntBound cnt T) (ha : a = cnt.set x v) (hv : v.val ≤ T + 1)
    (ht1 : tot1.val = T + 1) : CntBound a tot1.val := C1255!
theorem CntBound.mono {cnt : Array Std.U32 256#usize} {T T' : Nat} (h : CntBound cnt T)
    (hT : T ≤ T') : CntBound cnt T' := fun j hj => le_trans (h j hj) hT
@[local step]
theorem lift_spec {α : Type} (x : α) : lift x ⦃ fun y => y = x ⦄ := by
  simp [lift]
@[local step]
theorem run_spec (H W TD SL : Std.Usize) (input : Slice Std.U8) (out : Slice Std.U32) (cls : Std.Usize)
    (hlen : input.length ≤ out.length) (hH : 0 < H.val) (hW : 0 < W.val) :
    slot.fx0_run H W TD SL input out cls ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧
      LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := C12592! slot.fx0_run
end FX0
set_option hygiene false in
local notation "C12593!" q0__:max => (by
 rw [q0__]
 exact FX0.run_spec _ _ _ _ input out _ hlen (by simp) (by simp))
@[local step]
theorem fallback_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.fallback input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := C12593! slot.fallback
@[local step]
theorem route_spec (input : Slice Std.U8) : slot.route input ⦃ fun _ => True ⦄ := by
 rw [slot.route]
 step*
 all_goals repeat' (first | (split <;> step*) | scalar_tac)
namespace S70
open EO.EA
attribute [local step] EO.EA.sh_add_spec EO.EA.sh_table_spec
section
attribute [local step] EO.EA.ite_prod_spec
@[local step]
theorem pure_ite_spec {α : Type} (c : Prop) [Decidable c] (a b : α) :
 (if c then ok a else ok b) ⦃ fun r => r = if c then a else b ⦄ := by
 split <;> simp_all [Std.WP.spec_ok]
set_option maxHeartbeats 1000000
end
end S70
attribute [local step] EY.sparse_spec
namespace EQ3
open EO.EA
set_option maxHeartbeats 4000000
attribute [local step] EO.EA.ld8_spec EO.EA.first_diff_spec EO.EA.fast_len_spec EO.EA.fast_len2_spec EO.EA.fast_len3_spec EO.EA.hashl_spec EO.EA.emit_lits_spec EO.EA.emit_step_spec EO.EA.ite_true_spec EO.EA.ite_prod_spec
attribute [-step] EO.EA.ite_true_spec EO.EA.ite_prod_spec
end EQ3
namespace NN
open EO.EA
attribute [local step] EO.EA.ld8_spec EO.EA.first_diff_spec EO.EA.fast_len_spec EO.EA.emit_lits_spec EO.EA.emit_step_spec
theorem bits32 : 32 ≤ System.Platform.numBits := C12527!
section
attribute [local step] EO.EA.ite_true_spec EO.EA.ite_prod_spec
set_option maxHeartbeats 4000000
@[local step]
theorem pure_ite_spec {α : Type} (c : Prop) [Decidable c] (a b : α) :
 (if c then ok a else ok b) ⦃ fun r => r = if c then a else b ⦄ := by
 split <;> simp_all [Std.WP.spec_ok]
end
end NN
namespace DT
open EO.EA
attribute [local step] EO.EA.ld8_spec EO.EA.first_diff_spec EO.EA.fast_len_spec EO.EA.emit_lits_spec EO.EA.emit_step_spec
theorem bits32 : 32 ≤ System.Platform.numBits := C12527!
section
attribute [local step] EO.EA.ite_true_spec EO.EA.ite_prod_spec
set_option maxHeartbeats 4000000
@[local step]
theorem pure_ite_spec {α : Type} (c : Prop) [Decidable c] (a b : α) :
 (if c then ok a else ok b) ⦃ fun r => r = if c then a else b ⦄ := by
 split <;> simp_all [Std.WP.spec_ok]
end
end DT
namespace APP
open EO.EA
attribute [local step] FX0.run_spec
end APP
namespace FV
open Aeneas Aeneas.Std Result ControlFlow
set_option maxRecDepth 8192
set_option maxHeartbeats 4000000
set_option linter.unusedVariables false
open LZ77 (toks bytes bytes_length bytes_getElem! toks_update bytes_congr
  Matches Found emit_lit emit_match ite_ok)
open LZ77 (decode emit copyN tokLen tokDist MATCH_BASE TOK_LIMIT decode_snoc copyN_length)
@[irreducible] def word8 (input : Slice Std.U8) (p : Nat) : Nat :=
  (input.val[p]!).val * 2^56 + (input.val[p + 1]!).val * 2^48 + (input.val[p + 2]!).val * 2^40
    + (input.val[p + 3]!).val * 2^32 + (input.val[p + 4]!).val * 2^24
    + (input.val[p + 5]!).val * 2^16 + (input.val[p + 6]!).val * 2^8 + (input.val[p + 7]!).val
theorem u8_lt (x : Std.U8) : x.val < 256 := by
 simpa only [FV.word8, FX0.word8] using (@FX0.u8_lt x)
theorem word8_digit (input : Slice Std.U8) (p k : Nat) (hk : k < 8) :
    (input.val[p + k]!).val = word8 input p / 256 ^ (7 - k) % 256 := C12530!
theorem word8_prefix (input : Slice Std.U8) (a b d : Nat) (hd : d ≤ 8)
    (h : word8 input a / 2 ^ (64 - 8 * d) = word8 input b / 2 ^ (64 - 8 * d)) :
    ∀ k, k < d → input.val[b + k]! = input.val[a + k]! := C12531!
theorem Matches.add_prefix {input : Slice Std.U8} {a b l d : Nat} (h : Matches input a b l)
    (hd : d ≤ 8)
    (hw : word8 input (a + l) / 2 ^ (64 - 8 * d) = word8 input (b + l) / 2 ^ (64 - 8 * d)) :
    Matches input a b (l + d) := C12532!
theorem or_eq_add_of_mod {x t : Nat} (m : Nat) (hx : x % 2 ^ m = 0) (ht : t < 2 ^ m) :
    x ||| t = x + t := by
 simpa only [FV.word8, FX0.word8] using (@FX0.or_eq_add_of_mod x t m hx ht)
theorem shl_byte {x : Nat} (k : Nat) (hx : x < 256) (hk : k ≤ 56) :
    x <<< k % U64.size = x * 2 ^ k := by
 simpa only [FV.word8, FX0.word8] using (@FX0.shl_byte x k hx hk)
theorem be8_nat {a b c d e f g h : Nat} (ha : a < 256) (hb : b < 256) (hc : c < 256)
    (hd : d < 256) (he : e < 256) (hf : f < 256) (hg : g < 256) (hh : h < 256) :
    (a <<< 56 % U64.size ||| b <<< 48 % U64.size ||| c <<< 40 % U64.size |||
      d <<< 32 % U64.size ||| e <<< 24 % U64.size ||| f <<< 16 % U64.size |||
      g <<< 8 % U64.size ||| h) =
    a * 2^56 + b * 2^48 + c * 2^40 + d * 2^32 + e * 2^24 + f * 2^16 + g * 2^8 + h := by
 simpa only [FV.word8, FX0.word8] using (@FX0.be8_nat a b c d e f g h ha hb hc hd he hf hg hh)
theorem nat_xor_eq_zero {a b : Nat} (h : a ^^^ b = 0) : a = b := by
 simpa only [FV.word8, FX0.word8] using (@FX0.nat_xor_eq_zero a b h)
theorem div_eq_of_xor_lt {x y m : Nat} (hz : x ^^^ y < 2 ^ m) : x / 2 ^ m = y / 2 ^ m := by
 simpa only [FV.word8, FX0.word8] using (@FX0.div_eq_of_xor_lt x y m hz)
theorem lt_pow_leadingZeros (z : BitVec 64) :
    z.toNat < 2 ^ (64 - 8 * (BitVec.leadingZeros z / 8)) := by
 simpa only [FV.word8, FX0.word8] using (@FX0.lt_pow_leadingZeros z)
theorem leadingZeros_lt_of_ne (z : BitVec 64) (h : z ≠ 0) : BitVec.leadingZeros z < 64 := by
 simpa only [FV.word8, FX0.word8] using (@FX0.leadingZeros_lt_of_ne z h)
@[local step]
theorem lz_spec (x : Std.U64) :
    lift (core.num.U64.leading_zeros x) ⦃ fun r => r = core.num.U64.leading_zeros x ∧ r.val ≤ 64 ⦄ := by
 simpa only [FV.word8, FX0.word8] using (@FX0.lz_spec x)
theorem lz_val (x : Std.U64) :
    (core.num.U64.leading_zeros x).val = BitVec.leadingZeros x.bv := by
 simpa only [FV.word8, FX0.word8] using (@FX0.lz_val x)
theorem Matches.word_lz {input : Slice Std.U8} {a b k : Nat} {pa pb r k1 : Std.Usize}
    {x y z : Std.U64} {lz q : Std.U32}
    (h : Matches input a b k) (hpa : pa.val = a + k) (hpb : pb.val = b + k)
    (hx : x.val = word8 input pa.val) (hy : y.val = word8 input pb.val)
    (hz : z.val = (x ^^^ y).val) (hz0 : ¬z = 0#u64) (hlz : lz = core.num.U64.leading_zeros z)
    (hq : q.val = lz.val / 8) (hr : r = UScalar.cast .Usize q) (hk1 : k1.val = k + r.val) :
    Matches input a b k1.val ∧ k1.val < k + 8 := C12543!
theorem Matches.word_zero {input : Slice Std.U8} {a b k : Nat} {pa pb k1 : Std.Usize}
    {x y z : Std.U64}
    (h : Matches input a b k) (hpa : pa.val = a + k) (hpb : pb.val = b + k)
    (hx : x.val = word8 input pa.val) (hy : y.val = word8 input pb.val)
    (hz : z.val = (x ^^^ y).val) (hz0 : z = 0#u64) (hk1 : k1.val = k + 8) :
    Matches input a b k1.val := C12544!
theorem Matches.byte' {input : Slice Std.U8} {a b l : Nat} {pa pb l1 : Std.Usize}
    {x y : Std.U8} (h : Matches input a b l) (hpa : pa.val = a + l) (hpb : pb.val = b + l)
    (hpa' : pa.val < input.val.length) (hpb' : pb.val < input.val.length)
    (hx : x = input.val[pa.val]) (hy : y = input.val[pb.val]) (hxy : x = y)
    (hl1 : l1.val = l + 1) : Matches input a b l1.val := C12545!
theorem Matches.word_eq {input : Slice Std.U8} {a b k : Nat} {pa pb k1 : Std.Usize}
    {x y : Std.U64}
    (h : Matches input a b k) (hpa : pa.val = a + k) (hpb : pb.val = b + k)
    (hx : x.val = word8 input pa.val) (hy : y.val = word8 input pb.val)
    (hxy : x = y) (hk1 : k1.val = k + 8) :
    Matches input a b k1.val := C12549!
theorem Matches.mask {input : Slice Std.U8} {a b k len : Nat} {pa pb : Std.Usize}
    {x y z w : Std.U64} {sh : Std.U32}
    (h : Matches input a b k) (hpa : pa.val = a + k) (hpb : pb.val = b + k)
    (hx : x.val = word8 input pa.val) (hy : y.val = word8 input pb.val)
    (hz : z.val = (x ^^^ y).val) (hw : w.val = z.val >>> sh.val) (hw0 : ¬(w != 0#u64) = true)
    (hsh : sh.val = 64 - 8 * (len - k)) (hk : k < len) (hlen : len < k + 8) :
    Matches input a b len := C12552!
theorem lz32_le (x : Std.U32) (k : Nat) (hk : k < 32) (hx : 2 ^ k ≤ x.val) :
    (core.num.U32.leading_zeros x).val ≤ 31 - k := by
 simpa only [FV.word8, FX0.word8] using (@FX0.lz32_le x k hk hx)
@[local step]
theorem lz32_spec (x : Std.U32) :
    lift (core.num.U32.leading_zeros x) ⦃ fun r => r = core.num.U32.leading_zeros x ∧
      (4 ≤ x.val → r.val ≤ 29) ∧ (8 ≤ x.val → r.val ≤ 28) ⦄ := by
 simpa only [FV.word8, FX0.word8] using (@FX0.lz32_spec x)
@[local step]
theorem hcast_I32_spec {ty : UScalarTy} (x : UScalar ty) (h : x.val ≤ 2147483647) :
    lift (UScalar.hcast .I32 x) ⦃ fun y => y.val = x.val ⦄ :=
  UScalar.hcast_inBounds_spec .I32 x (by simp [I32.max_def, I32.numBits]; omega)
theorem GBASE_bound : -1000000000 ≤ slot.FX0_GBASE.val ∧ slot.FX0_GBASE.val ≤ 1000000000 := by
  unfold slot.FX0_GBASE
  simp
def HeadBound {N : Std.Usize} (head : Array Std.U32 N) (B : Nat) : Prop :=
  ∀ j : Nat, j < head.val.length → (head.val[j]!).val ≤ B
theorem HeadBound.mono {N : Std.Usize} {head : Array Std.U32 N} {B B' : Nat}
    (h : HeadBound head B) (hB : B ≤ B') : HeadBound head B' := fun j hj => le_trans (h j hj) hB
theorem HeadBound.init (N : Std.Usize) : HeadBound (Std.Array.repeat N 0#u32) 0 := by
 simpa only [FV.word8, FX0.word8, FV.HeadBound, FX0.HeadBound] using (@FX0.HeadBound.init N)
theorem HeadBound.set {N : Std.Usize} {head : Array Std.U32 N} {B : Nat} (h : HeadBound head B)
    (a : Std.Usize) (v : Std.U32) (hv : v.val ≤ B) : HeadBound (head.set a v) B := by
 simpa only [FV.word8, FX0.word8, FV.HeadBound, FX0.HeadBound] using (@FX0.HeadBound.set N head B h a v hv)
theorem HeadBound.update {N : Std.Usize} {head head1 : Array Std.U32 N} {B : Nat}
    {a i : Std.Usize} {v : Std.U32} (h : HeadBound head B) (hv : v = UScalar.cast .U32 i)
    (hi : i.val ≤ B) (h1 : head1 = head.set a v) : HeadBound head1 B := by
 simpa only [FV.word8, FX0.word8, FV.HeadBound, FX0.HeadBound] using (@FX0.HeadBound.update N head head1 B a i v h hv hi h1)
theorem HeadBound.get {N : Std.Usize} {head : Array Std.U32 N} {B : Nat} (h : HeadBound head B)
    (a : Std.Usize) (x : Std.U32) (ha : a.val < head.val.length) (hx : x = head.val[a.val]) :
    x.val ≤ B := C12559!
theorem cast_usize_le {x : Std.U32} {y : Std.Usize} {B : Nat} (h : y = UScalar.cast .Usize x)
    (hx : x.val ≤ B) : y.val ≤ B := by
 simpa only [FV.word8, FX0.word8, FV.HeadBound, FX0.HeadBound] using (@FX0.cast_usize_le x y B h hx)
def Cand (s : Slice Std.U8) (p cap best bd : Nat) : Prop :=
  bd = 0 ∨ (1 ≤ bd ∧ bd ≤ 32768 ∧ bd ≤ p ∧ best ≤ cap ∧ Matches s (p - bd) p best)
theorem dist_of_wrapping {p c d i : Std.Usize} (hc : c.val ≤ p.val)
    (hd : d = core.num.Usize.wrapping_sub p c) (hi : i = core.num.Usize.wrapping_sub d 1#usize)
    (hlt : i < 32768#usize) : d.val = p.val - c.val ∧ 1 ≤ d.val ∧ d.val ≤ 32768 := by
 simpa only [FV.word8, FX0.word8, FV.HeadBound, FX0.HeadBound, FV.Cand, FX0.Cand] using (@FX0.dist_of_wrapping p c d i hc hd hi hlt)
theorem Cand.of_common {s : Slice Std.U8} {p c d i l cap : Std.Usize} (hc : c.val ≤ p.val)
    (hd : d = core.num.Usize.wrapping_sub p c) (hi : i = core.num.Usize.wrapping_sub d 1#usize)
    (hlt : i < 32768#usize) (hl : l.val ≤ cap.val) (hm : Matches s c.val p.val l.val) :
    Cand s p.val cap.val l.val d.val := by
 simpa only [FV.word8, FX0.word8, FV.HeadBound, FX0.HeadBound, FV.Cand, FX0.Cand] using (@FX0.Cand.of_common s p c d i l cap hc hd hi hlt hl hm)
def MatchAt (s : Slice Std.U8) (p l d : Nat) : Prop :=
  3 ≤ l ∧ l ≤ 258 ∧ p + l ≤ s.length ∧ 1 ≤ d ∧ d ≤ 32768 ∧ d ≤ p ∧ Matches s (p - d) p l
def FoundAt (s : Slice Std.U8) (p l d : Nat) : Prop := l < 3 ∨ MatchAt s p l d
theorem FoundAt.of_cand {s : Slice Std.U8} {p cap : Nat} {l d : Std.Usize}
    (hc : Cand s p cap l.val d.val) (hd : ¬d = 0#usize) (hcap : cap ≤ 258)
    (hpl : p + l.val ≤ s.length) : FoundAt s p l.val d.val := by
 simpa only [FV.word8, FX0.word8, FV.HeadBound, FX0.HeadBound, FV.Cand, FX0.Cand, FV.MatchAt, FX0.MatchAt, FV.FoundAt, FX0.FoundAt] using (@FX0.FoundAt.of_cand s p cap l d hc hd hcap hpl)
theorem Cand.len_le {s : Slice Std.U8} {p cap : Nat} {l d : Std.Usize}
    (hc : Cand s p cap l.val d.val) (hd : ¬d = 0#usize) (hcap : cap ≤ 258) : l.val ≤ 258 := by
 simpa only [FV.word8, FX0.word8, FV.HeadBound, FX0.HeadBound, FV.Cand, FX0.Cand, FV.MatchAt, FX0.MatchAt, FV.FoundAt, FX0.FoundAt] using (@FX0.Cand.len_le s p cap l d hc hd hcap)
theorem Cand.dist_le {s : Slice Std.U8} {p cap l d : Nat} (hc : Cand s p cap l d) :
    d ≤ 32768 := by
 simpa only [FV.word8, FX0.word8, FV.HeadBound, FX0.HeadBound, FV.Cand, FX0.Cand, FV.MatchAt, FX0.MatchAt, FV.FoundAt, FX0.FoundAt] using (@FX0.Cand.dist_le s p cap l d hc)
theorem FoundAt.none (s : Slice Std.U8) (p : Nat) : FoundAt s p (0#usize).val (0#usize).val :=
  Or.inl (by simp)
theorem FoundAt.real {s : Slice Std.U8} {p l d : Nat} (hf : FoundAt s p l d) (h3 : 3 ≤ l) :
    MatchAt s p l d := by
 simpa only [FV.word8, FX0.word8, FV.HeadBound, FX0.HeadBound, FV.Cand, FX0.Cand, FV.MatchAt, FX0.MatchAt, FV.FoundAt, FX0.FoundAt] using (@FX0.FoundAt.real s p l d hf h3)
theorem copyN_take_prefix (acc : List Nat) (d : Nat) :
    ∀ n, (copyN acc d n).take acc.length = acc := by
 simpa only [FV.word8, FX0.word8, FV.HeadBound, FX0.HeadBound, FV.Cand, FX0.Cand, FV.MatchAt, FX0.MatchAt, FV.FoundAt, FX0.FoundAt] using (@FX0.copyN_take_prefix acc d)
theorem foldlM_emit_length : ∀ (ts : List Nat) (init acc : List Nat),
    ts.foldlM emit init = some acc → init.length + ts.length ≤ acc.length := by
 simpa only [FV.word8, FX0.word8, FV.HeadBound, FX0.HeadBound, FV.Cand, FX0.Cand, FV.MatchAt, FX0.MatchAt, FV.FoundAt, FX0.FoundAt] using (@FX0.foldlM_emit_length )
theorem decode_length_le {ts acc : List Nat} (h : decode ts = some acc) :
    ts.length ≤ acc.length := by
 simpa only [FV.word8, FX0.word8, FV.HeadBound, FX0.HeadBound, FV.Cand, FX0.Cand, FV.MatchAt, FX0.MatchAt, FV.FoundAt, FX0.FoundAt] using (@FX0.decode_length_le ts acc h)
theorem decode_pop_lit {ts : List Nat} {t : Nat} {inp : List Nat} {p : Nat}
    (hp : p ≤ inp.length) (hd : decode (ts ++ [t]) = some (inp.take p)) (ht : t < 256) :
    1 ≤ p ∧ decode ts = some (inp.take (p - 1)) := C12521!
theorem decode_pop_match {ts : List Nat} {t : Nat} {inp : List Nat} {p : Nat}
    (hp : p ≤ inp.length) (hd : decode (ts ++ [t]) = some (inp.take p)) (ht : 256 ≤ t) :
    tokLen t ≤ p ∧ decode ts = some (inp.take (p - tokLen t)) := C12522!
theorem toks_pop (out : Slice Std.U32) (nt : Nat) (h0 : 0 < nt) (hle : nt ≤ out.length) :
    toks out nt = toks out (nt - 1) ++ [(out.val[nt - 1]!).val] := C12523!
theorem toks_length (out : Slice Std.U32) (nt : Nat) (h : nt ≤ out.length) :
    (toks out nt).length = nt := by
 simpa only [FV.word8, FX0.word8, FV.HeadBound, FX0.HeadBound, FV.Cand, FX0.Cand, FV.MatchAt, FX0.MatchAt, FV.FoundAt, FX0.FoundAt] using (@FX0.toks_length out nt h)
def Dec (s : Slice Std.U8) (out : Slice Std.U32) (nt p : Nat) : Prop :=
  p ≤ s.length ∧ nt ≤ p ∧ s.length ≤ out.length ∧
    decode (toks out nt) = some ((bytes s).take p)
theorem Dec.init (input : Slice Std.U8) (out : Slice Std.U32) (h : input.length ≤ out.length) :
    Dec input out (0#usize).val (0#usize).val :=
  ⟨by simp, by simp, h, by simp [toks, LZ77.decode]⟩
theorem Dec.lit {s : Slice Std.U8} {out : Slice Std.U32} {nt p : Nat} (h : Dec s out nt p)
    (hp : p < s.length) (ntU : Std.Usize) (hnt : ntU.val = nt) (v : Std.U32)
    (hv : v.val = (s.val[p]!).val) :
    Dec s (out.set ntU v) (nt + 1) (p + 1) := C12570!
theorem Dec.match {s : Slice Std.U8} {out : Slice Std.U32} {nt p l d : Nat} (h : Dec s out nt p)
    (hm : MatchAt s p l d) (ntU : Std.Usize) (hnt : ntU.val = nt) (v : Std.U32)
    (hv : v.val = LZ77.mkMatch d l) :
    Dec s (out.set ntU v) (nt + 1) (p + l) := by
 simpa only [FV.word8, FX0.word8, FV.HeadBound, FX0.HeadBound, FV.Cand, FX0.Cand, FV.MatchAt, FX0.MatchAt, FV.FoundAt, FX0.FoundAt, FV.Dec, FX0.Dec] using (@FX0.Dec.match s out nt p l d h hm ntU hnt v hv)
theorem Dec.pop_lit {s : Slice Std.U8} {out : Slice Std.U32} {nt p : Nat} (h : Dec s out nt p)
    (h0 : 0 < nt) (hle : nt ≤ out.length) (ht : (out.val[nt - 1]!).val < 256) :
    1 ≤ p ∧ Dec s out (nt - 1) (p - 1) := C12525!
theorem Dec.pop_match {s : Slice Std.U8} {out : Slice Std.U32} {nt p : Nat} (h : Dec s out nt p)
    (h0 : 0 < nt) (hle : nt ≤ out.length) (ht : 256 ≤ (out.val[nt - 1]!).val) :
    tokLen (out.val[nt - 1]!).val ≤ p ∧
      Dec s out (nt - 1) (p - tokLen (out.val[nt - 1]!).val) := C12526!
theorem Dec.done {s : Slice Std.U8} {out : Slice Std.U32} {nt p : Nat} (h : Dec s out nt p)
    (hp : s.length ≤ p) : nt ≤ s.length ∧ LZ77.Valid (bytes s) (toks out nt) := by
 simpa only [FV.word8, FX0.word8, FV.HeadBound, FX0.HeadBound, FV.Cand, FX0.Cand, FV.MatchAt, FX0.MatchAt, FV.FoundAt, FX0.FoundAt, FV.Dec, FX0.Dec] using (@FX0.Dec.done s out nt p h hp)
theorem Dec.lit_step {s : Slice Std.U8} {out out1 : Slice Std.U32} {ntU nt1 pU : Std.Usize}
    {b : Std.U8} {v : Std.U32} (h : Dec s out ntU.val pU.val) (hp : pU.val < s.val.length)
    (hb : b = s.val[pU.val]) (hv : v = UScalar.cast .U32 b) (hout1 : out1 = out.set ntU v)
    (hnt1 : nt1.val = ntU.val + 1) :
    nt1.val = ntU.val + 1 ∧ out1.length = out.length ∧ Dec s out1 nt1.val (pU.val + 1) := C12573!
theorem Dec.match_step {s : Slice Std.U8} {out out1 : Slice Std.U32} {ntU nt1 pU dU lU e : Std.Usize}
    {v : Std.U32} (h : Dec s out ntU.val pU.val) (hm : MatchAt s pU.val lU.val dU.val)
    (hout1 : out1 = out.set ntU v) (hv : v.val = LZ77.mkMatch dU.val lU.val)
    (hnt1 : nt1.val = ntU.val + 1) (he : e.val = pU.val + lU.val) :
    nt1.val = ntU.val + 1 ∧ e.val = pU.val + lU.val ∧ out1.length = out.length ∧
      Dec s out1 nt1.val e.val := by
 simpa only [FV.word8, FX0.word8, FV.HeadBound, FX0.HeadBound, FV.Cand, FX0.Cand, FV.MatchAt, FX0.MatchAt, FV.FoundAt, FX0.FoundAt, FV.Dec, FX0.Dec] using (@FX0.Dec.match_step s out out1 ntU nt1 pU dU lU e v h hm hout1 hv hnt1 he)
theorem MatchAt.back_lit {s : Slice Std.U8} {p l d : Nat} (h : MatchAt s p l d) (hl : l < 258)
    (hdp : d < p) (heq : s.val[p - 1]! = s.val[p - 1 - d]!) : MatchAt s (p - 1) (l + 1) d := C12577!
theorem MatchAt.back_match {s : Slice Std.U8} {p l d w : Nat} (h : MatchAt s p l d)
    (hlw : l + w ≤ 258) (hw : w ≤ p) (hdw : d ≤ p - w) (hmw : Matches s (p - w - d) (p - w) w) :
    MatchAt s (p - w) (l + w) d := by
 simpa only [FV.word8, FX0.word8, FV.HeadBound, FX0.HeadBound, FV.Cand, FX0.Cand, FV.MatchAt, FX0.MatchAt, FV.FoundAt, FX0.FoundAt, FV.Dec, FX0.Dec] using (@FX0.MatchAt.back_match s p l d w h hlw hw hdw hmw)
def BackInv (input : Slice Std.U8) (out : Slice Std.U32) (d E P0 : Nat) (nt p l : Nat) : Prop :=
  Dec input out nt p ∧ MatchAt input p l d ∧ p + l = E ∧ p ≤ P0
theorem BackInv.lit {input : Slice Std.U8} {out : Slice Std.U32} {d E P0 : Nat}
    {nt p l i1 i2 i4 l1 : Std.Usize} {t : Std.U32} {x y : Std.U8}
    (h : BackInv input out d E P0 nt.val p.val l.val)
    (hi1 : i1.val = nt.val - 1) (hntl : nt.val ≤ out.length) (hnt0 : 1 ≤ nt.val)
    (hi1l : i1.val < out.val.length) (ht : t = out.val[i1.val]) (ht256 : t < 256#u32)
    (hi2 : i2.val = p.val - 1) (hi2l : i2.val < input.val.length) (hx : x = input.val[i2.val])
    (hxy : x = y) (hi4 : i4.val = i2.val - d) (hi4l : i4.val < input.val.length)
    (hy : y = input.val[i4.val]) (hl : l.val < 258) (hdp : d < p.val)
    (hl1 : l1.val = l.val + 1) :
    BackInv input out d E P0 i1.val i2.val l1.val := C12579!
theorem BackInv.match {input : Slice Std.U8} {out : Slice Std.U32} {d E P0 : Nat}
    {nt p l i1 w i9 i10 i11 i12 : Std.Usize} {t : Std.U32}
    (h : BackInv input out d E P0 nt.val p.val l.val)
    (hi1 : i1.val = nt.val - 1) (hntl : nt.val ≤ out.length) (hnt0 : 1 ≤ nt.val)
    (hi1l : i1.val < out.val.length) (ht : t = out.val[i1.val])
    (hsame : i12.val = 1 → Matches input i11.val i10.val w.val) (hi12 : i12 = 1#usize)
    (ht24 : 16777216 ≤ t.val) (hwv : w.val = (t.val - 16777216) % 256 + 3)
    (hi9 : i9.val = l.val + w.val) (hi9' : i9.val ≤ 258) (hi10 : i10.val = p.val - w.val)
    (hwp : w.val ≤ p.val) (hdw : d ≤ i10.val) (hi11 : i11.val = i10.val - d) :
    BackInv input out d E P0 i1.val i10.val i9.val := C12580!
def LazyInv (input : Slice Std.U8) (L lim : Nat) (out : Slice Std.U32) (nt p : Nat)
    {N : Std.Usize} (head : Array Std.U32 N) (ins l d : Nat) : Prop :=
  Dec input out nt p ∧ out.length = L ∧ MatchAt input p l d ∧ HeadBound head (p + 1) ∧
    p < lim ∧ ins ≤ p + 2
theorem LazyInv.accept {input : Slice Std.U8} {L lim p' B : Nat} {out1 : Slice Std.U32}
    {nt1 i ins1 l1 d1 minl : Std.Usize} {N : Std.Usize} {head1 : Array Std.U32 N}
    (hdec : Dec input out1 nt1.val p') (hi : i.val = p') (hlen : out1.length = L)
    (hf : FoundAt input i.val l1.val d1.val) (hl1 : minl.val ≤ l1.val) (hminl : 3 ≤ minl.val)
    (hB : HeadBound head1 B) (hBi : B ≤ i.val + 1) (hilim : i.val < lim)
    (hins : ins1.val ≤ i.val + 2) :
    LazyInv input L lim out1 nt1.val i.val head1 ins1.val l1.val d1.val := by
 simpa only [FV.word8, FX0.word8, FV.HeadBound, FX0.HeadBound, FV.Cand, FX0.Cand, FV.MatchAt, FX0.MatchAt, FV.FoundAt, FX0.FoundAt, FV.Dec, FX0.Dec, FV.BackInv, FX0.BackInv, FV.LazyInv, FX0.LazyInv] using (@FX0.LazyInv.accept input L lim p' B out1 nt1 i ins1 l1 d1 minl N head1 hdec hi hlen hf hl1 hminl hB hBi hilim hins)
theorem LazyInv.reject {input : Slice Std.U8} {L lim : Nat} {out : Slice Std.U32}
    {nt p ins ins1 l d B : Nat} {N : Std.Usize} {head head1 : Array Std.U32 N}
    (h : LazyInv input L lim out nt p head ins l d) (hB : HeadBound head1 B) (hBp : B ≤ p + 1)
    (hins1 : ins1 ≤ p + 2) : LazyInv input L lim out nt p head1 ins1 l d := by
 simpa only [FV.word8, FX0.word8, FV.HeadBound, FX0.HeadBound, FV.Cand, FX0.Cand, FV.MatchAt, FX0.MatchAt, FV.FoundAt, FX0.FoundAt, FV.Dec, FX0.Dec, FV.BackInv, FX0.BackInv, FV.LazyInv, FX0.LazyInv] using (@FX0.LazyInv.reject input L lim out nt p ins ins1 l d B N head head1 h hB hBp hins1)
theorem numBits_ge : 32 ≤ System.Platform.numBits := by
 simpa only [FV.word8, FX0.word8, FV.HeadBound, FX0.HeadBound, FV.Cand, FX0.Cand, FV.MatchAt, FX0.MatchAt, FV.FoundAt, FX0.FoundAt, FV.Dec, FX0.Dec, FV.BackInv, FX0.BackInv, FV.LazyInv, FX0.LazyInv] using (@FX0.numBits_ge )
def MainInv (input : Slice Std.U8) (L : Nat) (out : Slice Std.U32) (nt p : Nat)
    {N : Std.Usize} (head : Array Std.U32 N) (miss : Nat) : Prop :=
  Dec input out nt p ∧ out.length = L ∧ HeadBound head p ∧ miss ≤ p
theorem MainInv.mk' {input : Slice Std.U8} {L : Nat} {out : Slice Std.U32} {nt p m B : Nat}
    {N : Std.Usize} {head : Array Std.U32 N} (hdec : Dec input out nt p) (hlen : out.length = L)
    (hB : HeadBound head B) (hBp : B ≤ p) (hm : m ≤ p) : MainInv input L out nt p head m :=
  ⟨hdec, hlen, HeadBound.mono hB hBp, hm⟩
def CntBound (cnt : Array Std.U32 256#usize) (T : Nat) : Prop :=
  ∀ j : Nat, j < 256 → (cnt.val[j]!).val ≤ T
theorem CntBound.init : CntBound (Std.Array.repeat 256#usize 0#u32) 0 := by
 simpa only [FV.word8, FX0.word8, FV.HeadBound, FX0.HeadBound, FV.Cand, FX0.Cand, FV.MatchAt, FX0.MatchAt, FV.FoundAt, FX0.FoundAt, FV.Dec, FX0.Dec, FV.BackInv, FX0.BackInv, FV.LazyInv, FX0.LazyInv, FV.MainInv, FX0.MainInv, FV.CntBound, FX0.CntBound] using (@FX0.CntBound.init )
theorem CntBound.get {cnt : Array Std.U32 256#usize} {T : Nat} (h : CntBound cnt T)
    (a : Std.Usize) (x : Std.U32) (ha : a.val < cnt.val.length) (hx : x = cnt.val[a.val]) :
    x.val ≤ T := C1252!
@[local step]
theorem cnt_index_spec (cnt : Array Std.U32 256#usize) (T : Nat) (h : CntBound cnt T)
    (i : Std.Usize) (hi : i.val < 256) :
    Std.Array.index_usize cnt i ⦃ fun x => x = cnt.val[i.val]! ∧ x.val ≤ T ⦄ := C1253!
theorem CntBound.update {cnt : Array Std.U32 256#usize} {T : Nat} (h : CntBound cnt T)
    (a : Std.Usize) (v : Std.U32) (hv : v.val ≤ T + 1) : CntBound (cnt.set a v) (T + 1) := by
 simpa only [FV.word8, FX0.word8, FV.HeadBound, FX0.HeadBound, FV.Cand, FX0.Cand, FV.MatchAt, FX0.MatchAt, FV.FoundAt, FX0.FoundAt, FV.Dec, FX0.Dec, FV.BackInv, FX0.BackInv, FV.LazyInv, FX0.LazyInv, FV.MainInv, FX0.MainInv, FV.CntBound, FX0.CntBound] using (@FX0.CntBound.update cnt T h a v hv)
theorem CntBound.step {cnt a : Array Std.U32 256#usize} {T : Nat} {x : Std.Usize}
    {v tot1 : Std.U32} (hc : CntBound cnt T) (ha : a = cnt.set x v) (hv : v.val ≤ T + 1)
    (ht1 : tot1.val = T + 1) : CntBound a tot1.val := by
 simpa only [FV.word8, FX0.word8, FV.HeadBound, FX0.HeadBound, FV.Cand, FX0.Cand, FV.MatchAt, FX0.MatchAt, FV.FoundAt, FX0.FoundAt, FV.Dec, FX0.Dec, FV.BackInv, FX0.BackInv, FV.LazyInv, FX0.LazyInv, FV.MainInv, FX0.MainInv, FV.CntBound, FX0.CntBound] using (@FX0.CntBound.step cnt a T x v tot1 hc ha hv ht1)
theorem CntBound.mono {cnt : Array Std.U32 256#usize} {T T' : Nat} (h : CntBound cnt T)
    (hT : T ≤ T') : CntBound cnt T' := fun j hj => le_trans (h j hj) hT
@[local step]
theorem lift_spec {α : Type} (x : α) : lift x ⦃ fun y => y = x ⦄ := by
 simpa only [FV.word8, FX0.word8, FV.HeadBound, FX0.HeadBound, FV.Cand, FX0.Cand, FV.MatchAt, FX0.MatchAt, FV.FoundAt, FX0.FoundAt, FV.Dec, FX0.Dec, FV.BackInv, FX0.BackInv, FV.LazyInv, FX0.LazyInv, FV.MainInv, FX0.MainInv, FV.CntBound, FX0.CntBound] using (@FX0.lift_spec α x)
end FV
namespace R109
open LZ77
attribute [local step] EO.EA.emit_lits_spec
@[local step]
theorem eq3_spec (s : Slice Std.U8) (a b : Std.Usize)
 (ha : a.val+3 ≤ s.length) (hb : b.val+3 ≤ s.length) :
 slot.r109_eq3 s a b ⦃ fun v => v = true → Matches s a.val b.val 3 ⦄ := by
 rw [slot.r109_eq3]
 have hmax := Std.Slice.length_ineq s
 step*
 intro hv
 have hh : i7 = i9 := by simpa using hv
 intro k hk
 have hx : k = 0 ∨ k = 1 ∨ k = 2 := by omega
 rcases hx with h | h | h <;> subst k
 all_goals try simp only [Nat.add_zero]
 · rw [getElem!_pos _ _ (by scalar_tac), getElem!_pos _ _ (by scalar_tac), ← i1_post, ← i_post]
   symm; assumption
 · rw [show b.val+1=i4.val by scalar_tac,show a.val+1=i2.val by scalar_tac]
   rw [getElem!_pos _ _ (by scalar_tac), getElem!_pos _ _ (by scalar_tac), ← i5_post, ← i3_post]
   symm; assumption
 · rw [show b.val+2=i8.val by scalar_tac,show a.val+2=i6.val by scalar_tac]
   rw [getElem!_pos _ _ (by scalar_tac), getElem!_pos _ _ (by scalar_tac), ← i9_post, ← i7_post]
   exact hh.symm
@[local step]
theorem v3_spec (s : Slice Std.U8) (p d : Std.Usize) :
 slot.r109_v3 s p d ⦃ fun b => b = true →
 1 ≤ d.val ∧ d.val ≤ 32768 ∧ d.val ≤ p.val ∧ p.val+3 ≤ s.length ∧
 Matches s (p.val-d.val) p.val 3 ⦄ := by
 rw [slot.r109_v3]
 have hmax := Std.Slice.length_ineq s
 step*
 refine ⟨by scalar_tac,by scalar_tac,by scalar_tac,by scalar_tac,?_⟩
 rw [show p.val-d.val=i3.val by scalar_tac]
 exact b_post1 b_post2
@[local step]
theorem step3_spec (input : Slice Std.U8) (out : Slice Std.U32) (pos d ntok : Std.Usize)
 (hout : input.length ≤ out.length) (hpos : pos.val < input.length)
 (hntok : ntok.val ≤ pos.val)
 (hdec : decode (toks out ntok.val) = some ((bytes input).take pos.val)) :
 slot.r109_step3 input out pos d ntok ⦃ fun r =>
 pos.val < r.1.2.val ∧ r.1.2.val ≤ input.length ∧ r.1.1.val ≤ r.1.2.val ∧
 r.2.length = out.length ∧
 decode (toks r.2 r.1.1.val) = some ((bytes input).take r.1.2.val) ⦄ := by
 rw [slot.r109_step3]
 have hmax := Std.Slice.length_ineq input
 apply Std.WP.spec_bind (v3_spec input pos d)
 intro b hb
 split
 · obtain ⟨hd1,hdmax,hdpos,hend,hm⟩ := hb (by assumption)
   step*
   have htok : i3.val = mkMatch d.val 3 := by
     simp only [mkMatch,MATCH_BASE,i3_post,i2_post,i1_post];scalar_tac
   refine ⟨by scalar_tac,by scalar_tac,by scalar_tac,
    by rw [out1_post];simp [Std.Slice.set_val_eq],?_⟩
   rw [out1_post,show i4.val=ntok.val+1 by scalar_tac,show i5.val=pos.val+3 by scalar_tac]
   exact emit_match input out ntok pos.val d.val 3 i3 hdec (by scalar_tac)
    hd1 hdpos hdmax (by decide) (by decide) hend hm htok
 · apply Std.WP.spec_mono (EO.EA.emit_lits_spec input out pos 2#usize ntok hout (by scalar_tac) hntok hdec)
   rintro ⟨⟨t,k⟩,o⟩ ⟨h1,h2,h3,h4,h5⟩
   exact ⟨by scalar_tac,h2,h3,h4,h5⟩
@[local step]
theorem scan_loop_spec (H : Std.Usize) (input : Slice Std.U8) (out0 : Slice Std.U32)
 (head : Array Std.U32 H) (p half : Std.Usize)
 (hlen : input.length ≤ out0.length) (hH : 0 < H.val)
 (hn : 3 ≤ input.length) (hh : half.val=(input.length-1)/2) :
 slot.r109_rawscan_loop input out0 head p half ⦃ fun r => r.length=out0.length ⦄ := by
 rw [slot.r109_rawscan_loop]
 apply Std.loop.spec_decr_nat
  (measure := fun s => input.length-s.2.2.val)
  (inv := fun s => s.1.length=out0.length)
 · rintro ⟨out,head,p⟩ ho
   simp only at ho
   have hout : input.length ≤ out.length := by rw [ho];exact hlen
   have hmax := Std.Slice.length_ineq input
   simp only [slot.r109_rawscan_loop.body]
   step*
   repeat (first
    | (intro hc;try step*)
    | (casesm* _ × _;try step*)
    | (split <;>try step*))
   all_goals first
    | (refine ⟨?_,by scalar_tac⟩;rw [s1_post];simpa [Std.Slice.set_val_eq] using ho)
    | exact ho
    | scalar_tac
 · rfl
@[local step]
theorem scan_spec (H MODE : Std.Usize) (input : Slice Std.U8) (out : Slice Std.U32)
 (hlen : input.length ≤ out.length) (hH : 0 < H.val) :
 slot.r109_rawscan H MODE input out ⦃ fun r => r.length=out.length ⦄ := by
 rw [slot.r109_rawscan]
 step*
 repeat' (split <;> step*)
 all_goals scalar_tac
@[local step]
theorem replay_loop_spec (input : Slice Std.U8) (out0 : Slice Std.U32) (nt0 pos0 : Std.Usize)
 (hlen : input.length ≤ out0.length)
 (hp : pos0.val ≤ input.length) (hnt : nt0.val ≤ pos0.val)
 (hd : decode (toks out0 nt0.val) = some ((bytes input).take pos0.val)) :
 slot.r109_replay_loop input out0 nt0 pos0 ⦃ fun r =>
 r.1.val ≤ input.length ∧ r.2.length = out0.length ∧ Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.r109_replay_loop]
 apply Std.loop.spec_decr_nat
  (measure := fun s => input.length-s.2.2.val)
  (inv := fun s => s.2.2.val ≤ input.length ∧ s.2.1.val ≤ s.2.2.val ∧
   s.1.length=out0.length ∧ decode (toks s.1 s.2.1.val)=some ((bytes input).take s.2.2.val))
 · rintro ⟨out,nt,pos⟩ ⟨hp,ht,ho,hd⟩
   simp only at hp ht ho hd
   have hout : input.length ≤ out.length := by rw [ho];exact hlen
   simp only [slot.r109_replay_loop.body]
   split
   · step*
     repeat (first
      | (intro hc;try step*)
      | (casesm* _ × _;try step*)
      | (split <;>try step*)
      | (refine ⟨by scalar_tac,by scalar_tac,by assumption,by assumption,by scalar_tac⟩))
     all_goals try (have hout1 : input.length ≤ o1.length := by scalar_tac; step*)
     all_goals first | (refine ⟨by scalar_tac,by scalar_tac,by assumption,by assumption,by scalar_tac⟩) | scalar_tac
   · exact ⟨by scalar_tac,ho,by
      have he : pos.val=input.length := by scalar_tac
      have htake : (bytes input).take input.length=bytes input := by rw [← bytes_length input];exact List.take_length
      change decode (toks out nt.val)=some (bytes input)
      rw [he,htake] at hd;exact hd⟩
 · exact ⟨hp,hnt,rfl,hd⟩
@[local step]
theorem replay_spec (input : Slice Std.U8) (out : Slice Std.U32) (nt0 pos0 : Std.Usize)
 (hlen : input.length ≤ out.length)
 (hp : pos0.val ≤ input.length) (hnt : nt0.val ≤ pos0.val)
 (hd : decode (toks out nt0.val) = some ((bytes input).take pos0.val)) :
 slot.r109_replay input out nt0 pos0 ⦃ fun r =>
 r.1.val ≤ input.length ∧ r.2.length = out.length ∧ Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.r109_replay]
 exact replay_loop_spec input out nt0 pos0 hlen hp hnt hd
@[local step]
theorem bfraw_spec (H MODE : Std.Usize) (input : Slice Std.U8) (out : Slice Std.U32)
 (hlen : input.length ≤ out.length) (hH : 0 < H.val) :
 slot.r109_bfraw H MODE input out ⦃ fun r =>
 r.1.val ≤ input.length ∧ r.2.length=out.length ∧ Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.r109_bfraw]
 apply Std.WP.spec_bind (scan_spec H MODE input out hlen hH)
 intro out1 ho
 have hout : input.length ≤ out1.length := by rw [ho];exact hlen
 have hd : decode (toks out1 0)=some ((bytes input).take 0) := by simp [toks,LZ77.decode]
 step*
 all_goals first | (refine ⟨by assumption,?_,by assumption⟩;scalar_tac) | scalar_tac
end R109
attribute [local step] R109.bfraw_spec
namespace U118_MAIN
open Aeneas Aeneas.Std Result ControlFlow
set_option maxRecDepth 8192
set_option maxHeartbeats 4000000
set_option linter.unusedVariables false
open LZ77 (toks bytes bytes_length bytes_getElem! toks_update bytes_congr
  Matches Found emit_lit emit_match ite_ok)
open LZ77 (decode emit copyN tokLen tokDist MATCH_BASE TOK_LIMIT decode_snoc copyN_length)
@[irreducible] def word8 (input : Slice Std.U8) (p : Nat) : Nat :=
  (input.val[p]!).val * 2^56 + (input.val[p + 1]!).val * 2^48 + (input.val[p + 2]!).val * 2^40
    + (input.val[p + 3]!).val * 2^32 + (input.val[p + 4]!).val * 2^24
    + (input.val[p + 5]!).val * 2^16 + (input.val[p + 6]!).val * 2^8 + (input.val[p + 7]!).val
theorem u8_lt (x : Std.U8) : x.val < 256 := by scalar_tac
theorem word8_digit (input : Slice Std.U8) (p k : Nat) (hk : k < 8) :
    (input.val[p + k]!).val = word8 input p / 256 ^ (7 - k) % 256 := C12530!
theorem word8_prefix (input : Slice Std.U8) (a b d : Nat) (hd : d ≤ 8)
    (h : word8 input a / 2 ^ (64 - 8 * d) = word8 input b / 2 ^ (64 - 8 * d)) :
    ∀ k, k < d → input.val[b + k]! = input.val[a + k]! := C12531!
theorem Matches.add_prefix {input : Slice Std.U8} {a b l d : Nat} (h : Matches input a b l)
    (hd : d ≤ 8)
    (hw : word8 input (a + l) / 2 ^ (64 - 8 * d) = word8 input (b + l) / 2 ^ (64 - 8 * d)) :
    Matches input a b (l + d) := C12532!
theorem or_eq_add_of_mod {x t : Nat} (m : Nat) (hx : x % 2 ^ m = 0) (ht : t < 2 ^ m) :
    x ||| t = x + t := C12533!
theorem shl_byte {x : Nat} (k : Nat) (hx : x < 256) (hk : k ≤ 56) :
    x <<< k % U64.size = x * 2 ^ k := C12534!
theorem be8_nat {a b c d e f g h : Nat} (ha : a < 256) (hb : b < 256) (hc : c < 256)
    (hd : d < 256) (he : e < 256) (hf : f < 256) (hg : g < 256) (hh : h < 256) :
    (a <<< 56 % U64.size ||| b <<< 48 % U64.size ||| c <<< 40 % U64.size |||
      d <<< 32 % U64.size ||| e <<< 24 % U64.size ||| f <<< 16 % U64.size |||
      g <<< 8 % U64.size ||| h) =
    a * 2^56 + b * 2^48 + c * 2^40 + d * 2^32 + e * 2^24 + f * 2^16 + g * 2^8 + h := C12535!
@[local step]
theorem be8_spec (s : Slice Std.U8) (i : Std.Usize) (h : i.val + 8 ≤ s.length) :
    slot.u118_be8 s i ⦃ fun v => v.val = word8 s i.val ⦄ := C12536! slot.u118_be8
theorem nat_xor_eq_zero {a b : Nat} (h : a ^^^ b = 0) : a = b := C12537!
theorem div_eq_of_xor_lt {x y m : Nat} (hz : x ^^^ y < 2 ^ m) : x / 2 ^ m = y / 2 ^ m := C12538!
theorem lt_pow_leadingZeros (z : BitVec 64) :
    z.toNat < 2 ^ (64 - 8 * (BitVec.leadingZeros z / 8)) := C12539!
theorem leadingZeros_lt_of_ne (z : BitVec 64) (h : z ≠ 0) : BitVec.leadingZeros z < 64 := C12540!
@[local step]
theorem lz_spec (x : Std.U64) :
    lift (core.num.U64.leading_zeros x) ⦃ fun r => r = core.num.U64.leading_zeros x ∧ r.val ≤ 64 ⦄ := C12541!
theorem lz_val (x : Std.U64) :
    (core.num.U64.leading_zeros x).val = BitVec.leadingZeros x.bv := C12542!
theorem Matches.word_lz {input : Slice Std.U8} {a b k : Nat} {pa pb r k1 : Std.Usize}
    {x y z : Std.U64} {lz q : Std.U32}
    (h : Matches input a b k) (hpa : pa.val = a + k) (hpb : pb.val = b + k)
    (hx : x.val = word8 input pa.val) (hy : y.val = word8 input pb.val)
    (hz : z.val = (x ^^^ y).val) (hz0 : ¬z = 0#u64) (hlz : lz = core.num.U64.leading_zeros z)
    (hq : q.val = lz.val / 8) (hr : r = UScalar.cast .Usize q) (hk1 : k1.val = k + r.val) :
    Matches input a b k1.val ∧ k1.val < k + 8 := C12543!
theorem Matches.word_zero {input : Slice Std.U8} {a b k : Nat} {pa pb k1 : Std.Usize}
    {x y z : Std.U64}
    (h : Matches input a b k) (hpa : pa.val = a + k) (hpb : pb.val = b + k)
    (hx : x.val = word8 input pa.val) (hy : y.val = word8 input pb.val)
    (hz : z.val = (x ^^^ y).val) (hz0 : z = 0#u64) (hk1 : k1.val = k + 8) :
    Matches input a b k1.val := C12544!
theorem Matches.byte' {input : Slice Std.U8} {a b l : Nat} {pa pb l1 : Std.Usize}
    {x y : Std.U8} (h : Matches input a b l) (hpa : pa.val = a + l) (hpb : pb.val = b + l)
    (hpa' : pa.val < input.val.length) (hpb' : pb.val < input.val.length)
    (hx : x = input.val[pa.val]) (hy : y = input.val[pb.val]) (hxy : x = y)
    (hl1 : l1.val = l + 1) : Matches input a b l1.val := C12545!
theorem common_loop0_spec (s : Slice Std.U8) (a b cap k : Std.Usize) (run : Std.U32)
    (ha : a.val + cap.val ≤ s.length) (hb : b.val + cap.val ≤ s.length) (hcap : cap.val ≤ 258)
    (hk : k.val ≤ cap.val) (hm : Matches s a.val b.val k.val) :
    slot.u118_common_loop0 s a b cap k run ⦃ fun r =>
      r.1.val ≤ cap.val ∧ Matches s a.val b.val r.1.val ⦄ := C12546! slot.u118_common_loop0 slot.u118_common_loop0.body
theorem common_loop1_spec (s : Slice Std.U8) (a b cap k : Std.Usize) (run : Std.U32)
    (ha : a.val + cap.val ≤ s.length) (hb : b.val + cap.val ≤ s.length)
    (hk : k.val ≤ cap.val) (hm : Matches s a.val b.val k.val) :
    slot.u118_common_loop1 s a b cap k run ⦃ fun r =>
      r.val ≤ cap.val ∧ Matches s a.val b.val r.val ⦄ := C12547! slot.u118_common_loop1 slot.u118_common_loop1.body
@[local step]
theorem common_spec (s : Slice Std.U8) (a b cap : Std.Usize)
    (ha : a.val + cap.val ≤ s.length) (hb : b.val + cap.val ≤ s.length) (hcap : cap.val ≤ 258) :
    slot.u118_common s a b cap ⦃ fun l => l.val ≤ cap.val ∧ Matches s a.val b.val l.val ⦄ := C12548! slot.u118_common
theorem Matches.word_eq {input : Slice Std.U8} {a b k : Nat} {pa pb k1 : Std.Usize}
    {x y : Std.U64}
    (h : Matches input a b k) (hpa : pa.val = a + k) (hpb : pb.val = b + k)
    (hx : x.val = word8 input pa.val) (hy : y.val = word8 input pb.val)
    (hxy : x = y) (hk1 : k1.val = k + 8) :
    Matches input a b k1.val := C12549!
theorem same_loop0_spec (s : Slice Std.U8) (a b len k ok : Std.Usize)
    (ha : a.val + len.val ≤ s.length) (hb : b.val + len.val ≤ s.length) (hlen : len.val ≤ 258)
    (hk : k.val ≤ len.val) (hm : Matches s a.val b.val k.val) :
    slot.u118_same_loop0 s a b len k ok ⦃ fun r =>
      r.1.val ≤ len.val ∧ Matches s a.val b.val r.1.val ∧ (r.2.val = 1 → len.val < r.1.val + 8) ⦄ := C12550! slot.u118_same_loop0 slot.u118_same_loop0.body
@[local step]
theorem same_loop1_spec (s : Slice Std.U8) (a b len k ok : Std.Usize)
    (ha : a.val + len.val ≤ s.length) (hb : b.val + len.val ≤ s.length)
    (hk : k.val ≤ len.val) (hm : Matches s a.val b.val k.val) :
    slot.u118_same_loop1 s a b len k ok ⦃ fun r => r.val = 1 → Matches s a.val b.val len.val ⦄ := C12551! slot.u118_same_loop1 slot.u118_same_loop1.body
@[local step]
theorem same_loop2_spec (s : Slice Std.U8) (a b len k ok : Std.Usize)
    (ha : a.val + len.val ≤ s.length) (hb : b.val + len.val ≤ s.length)
    (hk : k.val ≤ len.val) (hm : Matches s a.val b.val k.val) :
    slot.u118_same_loop2 s a b len k ok ⦃ fun r => r.val = 1 → Matches s a.val b.val len.val ⦄ := C12551! slot.u118_same_loop2 slot.u118_same_loop2.body
theorem Matches.mask {input : Slice Std.U8} {a b k len : Nat} {pa pb : Std.Usize}
    {x y z w : Std.U64} {sh : Std.U32}
    (h : Matches input a b k) (hpa : pa.val = a + k) (hpb : pb.val = b + k)
    (hx : x.val = word8 input pa.val) (hy : y.val = word8 input pb.val)
    (hz : z.val = (x ^^^ y).val) (hw : w.val = z.val >>> sh.val) (hw0 : ¬(w != 0#u64) = true)
    (hsh : sh.val = 64 - 8 * (len - k)) (hk : k < len) (hlen : len < k + 8) :
    Matches input a b len := C12552!
@[local step]
theorem same_spec (s : Slice Std.U8) (a b len : Std.Usize)
    (ha : a.val + len.val ≤ s.length) (hb : b.val + len.val ≤ s.length) (hlen : len.val ≤ 258)
    (ha8 : a.val + len.val + 7 ≤ Std.Usize.max) (hb8 : b.val + len.val + 7 ≤ Std.Usize.max) :
    slot.u118_same s a b len ⦃ fun r => r.val = 1 → Matches s a.val b.val len.val ⦄ := C12553! slot.u118_same
theorem lz32_le (x : Std.U32) (k : Nat) (hk : k < 32) (hx : 2 ^ k ≤ x.val) :
    (core.num.U32.leading_zeros x).val ≤ 31 - k := C12554!
@[local step]
theorem lz32_spec (x : Std.U32) :
    lift (core.num.U32.leading_zeros x) ⦃ fun r => r = core.num.U32.leading_zeros x ∧
      (4 ≤ x.val → r.val ≤ 29) ∧ (8 ≤ x.val → r.val ≤ 28) ⦄ := C12555!
@[local step]
theorem hcast_I32_spec {ty : UScalarTy} (x : UScalar ty) (h : x.val ≤ 2147483647) :
    lift (UScalar.hcast .I32 x) ⦃ fun y => y.val = x.val ⦄ :=
  UScalar.hcast_inBounds_spec .I32 x (by simp [I32.max_def, I32.numBits]; omega)
theorem GBASE_bound : -500000000 ≤ slot.u118_GBASE.val ∧ slot.u118_GBASE.val ≤ 500000000 := by
  unfold slot.u118_GBASE
  simp
theorem L2B_bound : -500000000 ≤ slot.u118_L2B.val ∧ slot.u118_L2B.val ≤ 500000000 := by
  unfold slot.u118_L2B
  simp
theorem prod_bound {i hlit : Int} {l : Nat} (hi : i = (l : Int)) (hl : l ≤ 258) (h0 : 0 ≤ hlit)
    (h1 : hlit ≤ 1000000) : 0 ≤ i * hlit ∧ i * hlit ≤ 258000000 := by
  subst hi
  refine ⟨Int.mul_nonneg (by omega) h0, ?_⟩
  calc (l : Int) * hlit ≤ 258 * hlit := Int.mul_le_mul_of_nonneg_right (by omega) h0
    _ ≤ 258000000 := by omega
@[local step]
theorem gain_spec (l d : Std.Usize) (hlit : Std.I32) (hl : l.val ≤ 258) (hd : d.val ≤ 32768)
    (hh0 : 0 ≤ hlit.val) (hh1 : hlit.val ≤ 1000000) :
    slot.u118_gain l d hlit ⦃ fun r => -1000000000 ≤ r.val ∧ r.val ≤ 1000000000 ⦄ := by
  rw [slot.u118_gain]
  have ⟨hG0, hG1⟩ := GBASE_bound
  repeat' (split <;> step*)
  all_goals first
    | scalar_tac
    | (have := prod_bound (by assumption) hl hh0 hh1; scalar_tac)
def HeadBound {N : Std.Usize} (head : Array Std.U32 N) (B : Nat) : Prop :=
  ∀ j : Nat, j < head.val.length → (head.val[j]!).val ≤ B
theorem HeadBound.mono {N : Std.Usize} {head : Array Std.U32 N} {B B' : Nat}
    (h : HeadBound head B) (hB : B ≤ B') : HeadBound head B' := fun j hj => le_trans (h j hj) hB
theorem HeadBound.init (N : Std.Usize) : HeadBound (Std.Array.repeat N 0#u32) 0 := C12556!
theorem HeadBound.set {N : Std.Usize} {head : Array Std.U32 N} {B : Nat} (h : HeadBound head B)
    (a : Std.Usize) (v : Std.U32) (hv : v.val ≤ B) : HeadBound (head.set a v) B := C12557!
theorem HeadBound.update {N : Std.Usize} {head head1 : Array Std.U32 N} {B : Nat}
    {a i : Std.Usize} {v : Std.U32} (h : HeadBound head B) (hv : v = UScalar.cast .U32 i)
    (hi : i.val ≤ B) (h1 : head1 = head.set a v) : HeadBound head1 B := C12558!
theorem HeadBound.get {N : Std.Usize} {head : Array Std.U32 N} {B : Nat} (h : HeadBound head B)
    (a : Std.Usize) (x : Std.U32) (ha : a.val < head.val.length) (hx : x = head.val[a.val]) :
    x.val ≤ B := C12559!
theorem cast_usize_le {x : Std.U32} {y : Std.Usize} {B : Nat} (h : y = UScalar.cast .Usize x)
    (hx : x.val ≤ B) : y.val ≤ B := by
  rw [h, U32.cast_Usize_val_eq]; exact hx
@[local step]
theorem be4_spec (s : Slice Std.U8) (i : Std.Usize) (hi : i.val + 4 ≤ Std.Usize.max) :
    slot.u118_be4 s i ⦃ fun _ => True ⦄ := by
  rw [slot.u118_be4]
  step*
@[local step]
theorem insert_spec (s : Slice Std.U8) {H W : Std.Usize} (head : Array Std.U32 H)
    (prev : Array Std.U32 W) (i : Std.Usize) (mask : Std.U32) (B : Nat) (hB : HeadBound head B)
    (hi : i.val < B + 1) (hi4 : i.val + 4 ≤ Std.Usize.max) (hH : 0 < H.val) (hW : 0 < W.val) :
    slot.u118_insert s head prev i mask ⦃ fun r => r.1.val ≤ B ∧ HeadBound r.2.1 B ⦄ := C12560! slot.u118_insert
def Cand (s : Slice Std.U8) (p cap best bd : Nat) : Prop :=
  bd = 0 ∨ (1 ≤ bd ∧ bd ≤ 32768 ∧ bd ≤ p ∧ best ≤ cap ∧ Matches s (p - bd) p best)
theorem dist_of_wrapping {p c d i : Std.Usize} (hc : c.val ≤ p.val)
    (hd : d = core.num.Usize.wrapping_sub p c) (hi : i = core.num.Usize.wrapping_sub d 1#usize)
    (hlt : i < 32768#usize) : d.val = p.val - c.val ∧ 1 ≤ d.val ∧ d.val ≤ 32768 := C12561!
theorem Cand.of_common {s : Slice Std.U8} {p c d i l cap : Std.Usize} (hc : c.val ≤ p.val)
    (hd : d = core.num.Usize.wrapping_sub p c) (hi : i = core.num.Usize.wrapping_sub d 1#usize)
    (hlt : i < 32768#usize) (hl : l.val ≤ cap.val) (hm : Matches s c.val p.val l.val) :
    Cand s p.val cap.val l.val d.val := C12562!
theorem dist_of_wrapping2 {p c d i : Std.Usize} (hc : c.val ≤ p.val + 2)
    (hd : d = core.num.Usize.wrapping_sub p c) (hi : i = core.num.Usize.wrapping_sub d 1#usize)
    (hlt : i < 32768#usize) : c.val ≤ p.val := by
  by_contra hcp
  have hsz : 4294967296 ≤ Usize.size := by scalar_tac
  have hcl : c.val < Usize.size := by scalar_tac
  have hdv : d.val = Usize.size - (c.val - p.val) := by
    rw [hd, core.num.Usize.wrapping_sub_val_eq, UScalar.size_UScalarTyUsize]
    rw [show p.val + (Usize.size - c.val) = Usize.size - (c.val - p.val) by omega,
      Nat.mod_eq_of_lt (by omega)]
  have hiv : i.val < 32768 := by scalar_tac
  rw [hi, core.num.Usize.wrapping_sub_val_eq, UScalar.size_UScalarTyUsize] at hiv
  simp only [show (1#usize).val = 1 by simp] at hiv
  rw [show d.val + (Usize.size - 1) = (d.val - 1) + Usize.size by omega, Nat.add_mod_right,
    Nat.mod_eq_of_lt (by omega)] at hiv
  omega
theorem walk_loop_spec (s : Slice Std.U8) {W : Std.Usize} (prev : Array Std.U32 W)
    (p cap gm : Std.Usize) (hlit : Std.I32) (n best bd : Std.Usize) (bg : Std.I32)
    (c k stop : Std.Usize) (pb : Std.U8)
    (hn : n.val = s.length) (hcap : p.val + cap.val ≤ s.length) (hcap258 : cap.val ≤ 258)
    (hc : c.val ≤ p.val + 2) (hbest : p.val + best.val ≤ s.length)
    (hcand : Cand s p.val cap.val best.val bd.val) (hW : 0 < W.val)
    (hh0 : 0 ≤ hlit.val) (hh1 : hlit.val ≤ 1000000) :
    slot.u118_walk_loop s prev p cap gm hlit n best bd bg c k stop pb ⦃ fun r =>
      p.val + r.1.val ≤ s.length ∧ Cand s p.val cap.val r.1.val r.2.val ⦄ := by
  rw [slot.u118_walk_loop]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  apply Std.loop.spec_decr_nat
    (measure := fun r => r.2.2.2.2.1.val)
    (inv := fun r => r.2.2.2.1.val ≤ p.val + 2 ∧ p.val + r.1.val ≤ s.length ∧
      Cand s p.val cap.val r.1.val r.2.1.val)
  · rintro ⟨best, bd, bg, c, k, pb⟩ ⟨hc, hbest, hcand⟩
    simp only at hc hbest hcand
    simp only [slot.u118_walk_loop.body]
    split
    · step
      step
      split
      · have hcp := dist_of_wrapping2 hc (by assumption) (by assumption) (by assumption)
        step*
        repeat' (split <;> step*)
        all_goals first
          | exact (dist_of_wrapping hcp (by assumption) (by assumption) (by assumption)).2.2
          | (refine ⟨by scalar_tac, by scalar_tac, Cand.of_common hcp (by assumption)
              (by assumption) (by assumption) (by assumption) (by assumption), by scalar_tac⟩)
      · step*
    · step*
  · exact ⟨hc, hbest, hcand⟩
@[local step]
theorem walk_spec (s : Slice Std.U8) {W : Std.Usize} (prev : Array Std.U32 W)
    (p start cap «have» depth nice gm : Std.Usize) (hlit : Std.I32)
    (hcap : p.val + cap.val ≤ s.length) (hcap258 : cap.val ≤ 258) (hst : start.val ≤ p.val + 2)
    (hhave : p.val + «have».val ≤ s.length) (hW : 0 < W.val)
    (hh0 : 0 ≤ hlit.val) (hh1 : hlit.val ≤ 1000000) :
    slot.u118_walk s prev p start cap «have» depth nice gm hlit ⦃ fun r =>
      p.val + r.1.val ≤ s.length ∧ Cand s p.val cap.val r.1.val r.2.val ⦄ := by
  rw [slot.u118_walk]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  repeat' (split <;> step*)
  all_goals
    exact walk_loop_spec s prev p cap gm hlit (Std.Slice.len s) «have» 0#usize _ start depth _ _
      (by simp) hcap hcap258 hst hhave (Or.inl rfl) hW hh0 hh1
def MatchAt (s : Slice Std.U8) (p l d : Nat) : Prop :=
  3 ≤ l ∧ l ≤ 258 ∧ p + l ≤ s.length ∧ 1 ≤ d ∧ d ≤ 32768 ∧ d ≤ p ∧ Matches s (p - d) p l
def FoundAt (s : Slice Std.U8) (p l d : Nat) : Prop := l < 3 ∨ MatchAt s p l d
theorem FoundAt.of_cand {s : Slice Std.U8} {p cap : Nat} {l d : Std.Usize}
    (hc : Cand s p cap l.val d.val) (hd : ¬d = 0#usize) (hcap : cap ≤ 258)
    (hpl : p + l.val ≤ s.length) : FoundAt s p l.val d.val := C12565!
theorem Cand.len_le {s : Slice Std.U8} {p cap : Nat} {l d : Std.Usize}
    (hc : Cand s p cap l.val d.val) (hd : ¬d = 0#usize) (hcap : cap ≤ 258) : l.val ≤ 258 := C12566!
theorem Cand.dist_le {s : Slice Std.U8} {p cap l d : Nat} (hc : Cand s p cap l d) :
    d ≤ 32768 := C12567!
theorem FoundAt.none (s : Slice Std.U8) (p : Nat) : FoundAt s p (0#usize).val (0#usize).val :=
  Or.inl (by simp)
theorem FoundAt.real {s : Slice Std.U8} {p l d : Nat} (hf : FoundAt s p l d) (h3 : 3 ≤ l) :
    MatchAt s p l d := C12568!
@[local step]
theorem find_spec (s : Slice Std.U8) {W : Std.Usize} (prev : Array Std.U32 W)
    (p st «have» minl depth nice gm : Std.Usize) (hlit : Std.I32)
    (hp : p.val ≤ s.length) (hst : st.val ≤ p.val + 2) (hhave : p.val + «have».val ≤ s.length)
    (hhave258 : «have».val ≤ 258) (hminl : 1 ≤ minl.val) (hminl' : p.val + minl.val ≤ s.length + 1)
    (hW : 0 < W.val) (hh0 : 0 ≤ hlit.val) (hh1 : hlit.val ≤ 1000000) :
    slot.u118_find s prev p st «have» minl depth nice gm hlit ⦃ fun r => FoundAt s p.val r.1.val r.2.val ∧
      r.1.val ≤ 258 ∧ r.2.val ≤ 32768 ⦄ := C12569! slot.u118_find
def Near (s : Slice Std.U8) (p len r : Nat) : Prop :=
  r = 0 ∨ (1 ≤ r ∧ r ≤ 32768 ∧ r ≤ p ∧ Matches s (p - r) p len)
theorem Near.none (s : Slice Std.U8) (p len : Nat) : Near s p len (0#usize).val := Or.inl (by simp)
theorem Near.found {s : Slice Std.U8} {p c d i len r : Std.Usize} (hc : c.val < p.val)
    (hd : d = core.num.Usize.wrapping_sub p c) (hi : i = core.num.Usize.wrapping_sub d 1#usize)
    (hlt : i < 32768#usize) (hsame : r.val = 1 → Matches s c.val p.val len.val)
    (hr : r = 1#usize) : Near s p.val len.val d.val := by
  obtain ⟨hdv, hd1, hd2⟩ := dist_of_wrapping (le_of_lt hc) hd hi hlt
  refine Or.inr ⟨hd1, hd2, by omega, ?_⟩
  rw [show p.val - d.val = c.val by omega]
  exact hsame (by rw [hr]; rfl)
theorem closest_loop_spec (s : Slice Std.U8) {W : Std.Usize} (prev : Array Std.U32 W)
    (p len n c k res : Std.Usize) (hn : n.val = s.length) (hp : p.val + len.val + 8 ≤ s.length)
    (hlen : len.val ≤ 258) (hW : 0 < W.val) (hres : Near s p.val len.val res.val) :
    slot.u118_closest_loop s prev p len n c k res ⦃ fun r => Near s p.val len.val r.val ⦄ := by
  rw [slot.u118_closest_loop]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  apply Std.loop.spec_decr_nat
    (measure := fun r => r.2.1.val)
    (inv := fun r => Near s p.val len.val r.2.2.val)
  · rintro ⟨c, k, res⟩ hres
    simp only at hres
    simp only [slot.u118_closest_loop.body]
    step*
    all_goals first
      | exact ⟨hres, by scalar_tac⟩
      | exact hres
      | exact ⟨Near.found (by assumption) (by assumption) (by assumption) (by assumption)
          (by assumption) (by assumption), by scalar_tac⟩
  · exact hres
@[local step]
theorem closest_spec (s : Slice Std.U8) {W : Std.Usize} (prev : Array Std.U32 W)
    (p start len depth : Std.Usize) (hp : p.val + len.val + 8 ≤ s.length) (hlen : len.val ≤ 258)
    (hW : 0 < W.val) :
    slot.u118_closest s prev p start len depth ⦃ fun r => Near s p.val len.val r.val ⦄ := by
  rw [slot.u118_closest]
  exact closest_loop_spec s prev p len (Std.Slice.len s) start depth 0#usize (by simp) hp hlen hW
    (Near.none s p.val len.val)
theorem copyN_take_prefix (acc : List Nat) (d : Nat) :
    ∀ n, (copyN acc d n).take acc.length = acc := C12518!
theorem foldlM_emit_length : ∀ (ts : List Nat) (init acc : List Nat),
    ts.foldlM emit init = some acc → init.length + ts.length ≤ acc.length := C12519!
theorem decode_length_le {ts acc : List Nat} (h : decode ts = some acc) :
    ts.length ≤ acc.length := C12520!
theorem decode_pop_lit {ts : List Nat} {t : Nat} {inp : List Nat} {p : Nat}
    (hp : p ≤ inp.length) (hd : decode (ts ++ [t]) = some (inp.take p)) (ht : t < 256) :
    1 ≤ p ∧ decode ts = some (inp.take (p - 1)) := C12521!
theorem decode_pop_match {ts : List Nat} {t : Nat} {inp : List Nat} {p : Nat}
    (hp : p ≤ inp.length) (hd : decode (ts ++ [t]) = some (inp.take p)) (ht : 256 ≤ t) :
    tokLen t ≤ p ∧ decode ts = some (inp.take (p - tokLen t)) := C12522!
theorem toks_pop (out : Slice Std.U32) (nt : Nat) (h0 : 0 < nt) (hle : nt ≤ out.length) :
    toks out nt = toks out (nt - 1) ++ [(out.val[nt - 1]!).val] := C12523!
theorem toks_length (out : Slice Std.U32) (nt : Nat) (h : nt ≤ out.length) :
    (toks out nt).length = nt := C12524!
def Dec (s : Slice Std.U8) (out : Slice Std.U32) (nt p : Nat) : Prop :=
  p ≤ s.length ∧ nt ≤ p ∧ s.length ≤ out.length ∧
    decode (toks out nt) = some ((bytes s).take p)
theorem Dec.init (input : Slice Std.U8) (out : Slice Std.U32) (h : input.length ≤ out.length) :
    Dec input out (0#usize).val (0#usize).val :=
  ⟨by simp, by simp, h, by simp [toks, LZ77.decode]⟩
theorem Dec.lit {s : Slice Std.U8} {out : Slice Std.U32} {nt p : Nat} (h : Dec s out nt p)
    (hp : p < s.length) (ntU : Std.Usize) (hnt : ntU.val = nt) (v : Std.U32)
    (hv : v.val = (s.val[p]!).val) :
    Dec s (out.set ntU v) (nt + 1) (p + 1) := C12570!
theorem Dec.match {s : Slice Std.U8} {out : Slice Std.U32} {nt p l d : Nat} (h : Dec s out nt p)
    (hm : MatchAt s p l d) (ntU : Std.Usize) (hnt : ntU.val = nt) (v : Std.U32)
    (hv : v.val = LZ77.mkMatch d l) :
    Dec s (out.set ntU v) (nt + 1) (p + l) := C12571!
theorem Dec.pop_lit {s : Slice Std.U8} {out : Slice Std.U32} {nt p : Nat} (h : Dec s out nt p)
    (h0 : 0 < nt) (hle : nt ≤ out.length) (ht : (out.val[nt - 1]!).val < 256) :
    1 ≤ p ∧ Dec s out (nt - 1) (p - 1) := C12525!
theorem Dec.pop_match {s : Slice Std.U8} {out : Slice Std.U32} {nt p : Nat} (h : Dec s out nt p)
    (h0 : 0 < nt) (hle : nt ≤ out.length) (ht : 256 ≤ (out.val[nt - 1]!).val) :
    tokLen (out.val[nt - 1]!).val ≤ p ∧
      Dec s out (nt - 1) (p - tokLen (out.val[nt - 1]!).val) := C12526!
theorem Dec.done {s : Slice Std.U8} {out : Slice Std.U32} {nt p : Nat} (h : Dec s out nt p)
    (hp : s.length ≤ p) : nt ≤ s.length ∧ LZ77.Valid (bytes s) (toks out nt) := C12572!
theorem Dec.lit_step {s : Slice Std.U8} {out out1 : Slice Std.U32} {ntU nt1 pU : Std.Usize}
    {b : Std.U8} {v : Std.U32} (h : Dec s out ntU.val pU.val) (hp : pU.val < s.val.length)
    (hb : b = s.val[pU.val]) (hv : v = UScalar.cast .U32 b) (hout1 : out1 = out.set ntU v)
    (hnt1 : nt1.val = ntU.val + 1) :
    nt1.val = ntU.val + 1 ∧ out1.length = out.length ∧ Dec s out1 nt1.val (pU.val + 1) := C12573!
@[local step]
theorem put_lit_spec (s : Slice Std.U8) (out : Slice Std.U32) (nt p : Std.Usize)
    (hdec : Dec s out nt.val p.val) (hp : p.val < s.length) :
    slot.u118_put_lit s out nt p ⦃ fun r => r.1.val = nt.val + 1 ∧ r.2.length = out.length ∧
      Dec s r.2 r.1.val (p.val + 1) ⦄ := C12574! slot.u118_put_lit
theorem Dec.match_step {s : Slice Std.U8} {out out1 : Slice Std.U32} {ntU nt1 pU dU lU e : Std.Usize}
    {v : Std.U32} (h : Dec s out ntU.val pU.val) (hm : MatchAt s pU.val lU.val dU.val)
    (hout1 : out1 = out.set ntU v) (hv : v.val = LZ77.mkMatch dU.val lU.val)
    (hnt1 : nt1.val = ntU.val + 1) (he : e.val = pU.val + lU.val) :
    nt1.val = ntU.val + 1 ∧ e.val = pU.val + lU.val ∧ out1.length = out.length ∧
      Dec s out1 nt1.val e.val := C12575!
@[local step]
theorem put_match_spec (s : Slice Std.U8) (out : Slice Std.U32) (nt p d l : Std.Usize)
    (hdec : Dec s out nt.val p.val) (hm : MatchAt s p.val l.val d.val) :
    slot.u118_put_match s out nt p d l ⦃ fun r => r.1.1.val = nt.val + 1 ∧
      r.1.2.val = p.val + l.val ∧ r.2.length = out.length ∧ Dec s r.2 r.1.1.val r.1.2.val ⦄ := C12576! slot.u118_put_match
theorem MatchAt.back_lit {s : Slice Std.U8} {p l d : Nat} (h : MatchAt s p l d) (hl : l < 258)
    (hdp : d < p) (heq : s.val[p - 1]! = s.val[p - 1 - d]!) : MatchAt s (p - 1) (l + 1) d := C12577!
theorem MatchAt.back_match {s : Slice Std.U8} {p l d w : Nat} (h : MatchAt s p l d)
    (hlw : l + w ≤ 258) (hw : w ≤ p) (hdw : d ≤ p - w) (hmw : Matches s (p - w - d) (p - w) w) :
    MatchAt s (p - w) (l + w) d := C12578!
def BackInv (input : Slice Std.U8) (L d E P0 : Nat) (out : Slice Std.U32) (nt p l : Nat) : Prop :=
  Dec input out nt p ∧ out.length = L ∧ MatchAt input p l d ∧ p + l = E ∧ p ≤ P0
theorem BackInv.lit {input : Slice Std.U8} {out : Slice Std.U32} {L d E P0 : Nat}
    {nt p l i1 i2 i4 l1 : Std.Usize} {t : Std.U32} {x y : Std.U8}
    (h : BackInv input L d E P0 out nt.val p.val l.val)
    (hi1 : i1.val = nt.val - 1) (hntl : nt.val ≤ out.length) (hnt0 : 1 ≤ nt.val)
    (hi1l : i1.val < out.val.length) (ht : t = out.val[i1.val]) (ht256 : t < 256#u32)
    (hi2 : i2.val = p.val - 1) (hi2l : i2.val < input.val.length) (hx : x = input.val[i2.val])
    (hxy : x = y) (hi4 : i4.val = i2.val - d) (hi4l : i4.val < input.val.length)
    (hy : y = input.val[i4.val]) (hl : l.val < 258) (hdp : d < p.val)
    (hl1 : l1.val = l.val + 1) :
    BackInv input L d E P0 out i1.val i2.val l1.val := by
  obtain ⟨hdec, hL, hm, hE, hP⟩ := h
  have ht' : (out.val[nt.val - 1]!).val < 256 := by
    rw [← hi1, getElem!_pos out.val i1.val hi1l, ← ht]; scalar_tac
  obtain ⟨hp1, hdec'⟩ := Dec.pop_lit hdec (by omega) hntl ht'
  have heq : input.val[p.val - 1]! = input.val[p.val - 1 - d]! := by
    rw [← hi2, getElem!_pos input.val i2.val hi2l, show i2.val - d = i4.val by omega,
      getElem!_pos input.val i4.val hi4l, ← hx, ← hy, hxy]
  have hm' := MatchAt.back_lit hm hl hdp heq
  rw [hi1, hi2, hl1]
  exact ⟨hdec', hL, hm', by omega, by omega⟩
theorem BackInv.match {input : Slice Std.U8} {out : Slice Std.U32} {L d E P0 : Nat}
    {nt p l i1 w i9 i10 i11 i12 : Std.Usize} {t : Std.U32}
    (h : BackInv input L d E P0 out nt.val p.val l.val)
    (hi1 : i1.val = nt.val - 1) (hntl : nt.val ≤ out.length) (hnt0 : 1 ≤ nt.val)
    (hi1l : i1.val < out.val.length) (ht : t = out.val[i1.val])
    (hsame : i12.val = 1 → Matches input i11.val i10.val w.val) (hi12 : i12 = 1#usize)
    (ht24 : 16777216 ≤ t.val) (hwv : w.val = (t.val - 16777216) % 256 + 3)
    (hi9 : i9.val = l.val + w.val) (hi9' : i9.val ≤ 258) (hi10 : i10.val = p.val - w.val)
    (hwp : w.val ≤ p.val) (hdw : d ≤ i10.val) (hi11 : i11.val = i10.val - d) :
    BackInv input L d E P0 out i1.val i10.val i9.val := by
  obtain ⟨hdec, hL, hm, hE, hP⟩ := h
  have htv : (out.val[nt.val - 1]!).val = t.val := by
    rw [← hi1, getElem!_pos out.val i1.val hi1l, ← ht]
  have hwv' : w.val = tokLen (out.val[nt.val - 1]!).val := by
    rw [htv, hwv]
    simp only [tokLen, MATCH_BASE]
  obtain ⟨hwl, hdec'⟩ := Dec.pop_match hdec (by omega) hntl (by omega)
  rw [← hwv'] at hdec'
  have hmw : Matches input (p.val - w.val - d) (p.val - w.val) w.val := by
    have := hsame (by rw [hi12]; rfl)
    rw [hi11, hi10] at this
    exact this
  have hm' := MatchAt.back_match hm (by omega) hwp (by omega) hmw
  rw [hi1, hi10, hi9]
  exact ⟨hdec', hL, hm', by omega, by omega⟩
theorem BackInv.part {input : Slice Std.U8} {out out1 : Slice Std.U32} {L d E P0 : Nat}
    {nt p l : Nat} {p1 l1 : Std.Usize} (h : BackInv input L d E P0 out nt p l)
    (hlen : out1.length = out.length) (hdec : Dec input out1 nt p1.val)
    (hm : MatchAt input p1.val l1.val d) (hE : p1.val + l1.val = p + l) (hp : p1.val ≤ p) :
    BackInv input L d E P0 out1 nt p1.val l1.val := by
  obtain ⟨_, hL, _, hE0, hP⟩ := h
  exact ⟨hdec, by rw [hlen, hL], hm, by omega, by omega⟩
theorem Matches.cons {input : Slice Std.U8} {a b n : Nat} (h : Matches input (a + 1) (b + 1) n)
    (heq : input.val[b]! = input.val[a]!) : Matches input a b (n + 1) := by
  intro k hk
  rcases Nat.eq_zero_or_pos k with h0 | hk0
  · subst h0; simpa using heq
  · have := h (k - 1) (by omega)
    rw [show b + 1 + (k - 1) = b + k by omega, show a + 1 + (k - 1) = a + k by omega] at this
    exact this
theorem Matches.append {input : Slice Std.U8} {a b k l : Nat} (h1 : Matches input a b k)
    (h2 : Matches input (a + k) (b + k) l) : Matches input a b (k + l) := by
  intro j hj
  rcases Nat.lt_or_ge j k with hjk | hjk
  · exact h1 j hjk
  · have := h2 (j - k) (by omega)
    rw [show b + k + (j - k) = b + j by omega, show a + k + (j - k) = a + j by omega] at this
    exact this
theorem MatchAt.back_part {s : Slice Std.U8} {p l d k : Nat} (h : MatchAt s p l d)
    (hmk : Matches s (p - k - d) (p - k) k) (hlk : l + k ≤ 258) (hdk : d + k ≤ p) :
    MatchAt s (p - k) (l + k) d := by
  obtain ⟨h3, h258, hpl, hd1, hd32, _, hm⟩ := h
  refine ⟨by omega, hlk, by omega, hd1, hd32, by omega, ?_⟩
  have hm' : Matches s (p - k - d + k) (p - k + k) l := by
    rw [show p - k - d + k = p - d by omega, show p - k + k = p by omega]; exact hm
  have := Matches.append hmk hm'
  rw [show k + l = l + k by omega] at this
  exact this
theorem Matches.back_step {input : Slice Std.U8} {p d k : Nat} {i4 i7 k1 : Std.Usize}
    {x y : Std.U8} (h : Matches input (p - k - d) (p - k) k) (hdk : d + k < p)
    (hi4 : i4.val = p - 1 - k) (hi4l : i4.val < input.val.length) (hx : x = input.val[i4.val])
    (hi7 : i7.val = p - 1 - k - d) (hi7l : i7.val < input.val.length)
    (hy : y = input.val[i7.val]) (hxy : x = y) (hk1 : k1.val = k + 1) :
    Matches input (p - k1.val - d) (p - k1.val) k1.val := by
  rw [hk1]
  apply Matches.cons
  · rw [show p - (k + 1) - d + 1 = p - k - d by omega, show p - (k + 1) + 1 = p - k by omega]
    exact h
  · rw [show p - (k + 1) - d = i7.val by omega, show p - (k + 1) = i4.val by omega,
      getElem!_pos input.val i4.val hi4l, getElem!_pos input.val i7.val hi7l, ← hx, ← hy, hxy]
theorem part_merge_loop_spec (input : Slice Std.U8) (p0 l0 d w k : Std.Usize)
    (hp0 : p0.val ≤ input.length) (hkw : k.val ≤ w.val) (hl0 : l0.val + k.val ≤ 258)
    (hdk : d.val + k.val ≤ p0.val)
    (hm : Matches input (p0.val - k.val - d.val) (p0.val - k.val) k.val) :
    slot.u118_part_merge_loop input p0 l0 d w k ⦃ fun r =>
      r.val ≤ w.val ∧ l0.val + r.val ≤ 258 ∧ d.val + r.val ≤ p0.val ∧
      Matches input (p0.val - r.val - d.val) (p0.val - r.val) r.val ⦄ := by
  rw [slot.u118_part_merge_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun r => w.val - r.val)
    (inv := fun r => r.val ≤ w.val ∧ l0.val + r.val ≤ 258 ∧ d.val + r.val ≤ p0.val ∧
      Matches input (p0.val - r.val - d.val) (p0.val - r.val) r.val)
  · rintro k ⟨hkw, hl0, hdk, hm⟩
    simp only [slot.u118_part_merge_loop.body]
    step*
    all_goals first
      | exact ⟨hkw, hl0, hdk, hm⟩
      | (refine ⟨by scalar_tac, by scalar_tac, by scalar_tac,
          Matches.back_step (i4 := i4) (i7 := i7) (x := i5) (y := i8) hm (by scalar_tac)
            (by scalar_tac) (by scalar_tac) (by assumption) (by scalar_tac) (by scalar_tac)
            (by assumption) (by assumption) (by scalar_tac),
          by scalar_tac⟩)
  · exact ⟨hkw, hl0, hdk, hm⟩
@[local step]
theorem part_merge_loop_spec0 (input : Slice Std.U8) (p0 l0 d w : Std.Usize)
    (hp0 : p0.val ≤ input.length) (hl0 : l0.val ≤ 258) (hdk : d.val ≤ p0.val) :
    slot.u118_part_merge_loop input p0 l0 d w 0#usize ⦃ fun r =>
      r.val ≤ w.val ∧ l0.val + r.val ≤ 258 ∧ d.val + r.val ≤ p0.val ∧
      Matches input (p0.val - r.val - d.val) (p0.val - r.val) r.val ⦄ :=
  part_merge_loop_spec input p0 l0 d w 0#usize hp0 (by simp) (by simpa using hl0)
    (by simpa using hdk) (by simpa using LZ77.Matches.zero input (p0.val - d.val) p0.val)
theorem part_post {input : Slice Std.U8} {out out1 : Slice Std.U32}
    {nt p l d w k c nl pp p1 l1 : Nat} {ntU : Std.Usize} {v : Std.U32}
    (hdec : Dec input out nt p) (hm : MatchAt input p l d)
    (hnt0 : 1 ≤ nt) (hntl : nt ≤ out.length) (ht24 : 256 ≤ (out.val[nt - 1]!).val)
    (hw : w = tokLen (out.val[nt - 1]!).val)
    (hmk : Matches input (p - k - d) (p - k) k) (hc : Near input pp nl c)
    (hout1 : out1 = out.set ntU v)
    (hlk : l + k ≤ 258) (hdk : d + k ≤ p) (hk : k ≤ w) (hpp : pp = p - w) (hnl : nl = w - k)
    (hnl3 : 3 ≤ nl) (hnl258 : nl ≤ 258) (hc0 : 0 < c) (hcp : c ≤ pp)
    (hntU : ntU.val = nt - 1) (hv : v.val = LZ77.mkMatch c nl) (hp1 : p1 = p - k)
    (hl1 : l1 = l + k) :
    out1.length = out.length ∧ Dec input out1 nt p1 ∧ MatchAt input p1 l1 d ∧
      p1 + l1 = p + l ∧ p1 ≤ p := by
  subst hp1 hl1 hpp
  obtain ⟨hwp, hdec'⟩ := Dec.pop_match hdec (by omega) hntl ht24
  rw [← hw] at hdec' hwp
  have hpn : p ≤ input.length := hdec.1
  have hmc : MatchAt input (p - w) nl c := by
    rcases hc with h0 | ⟨hc1, hc32, _, hmm⟩
    · omega
    · exact ⟨hnl3, hnl258, by omega, hc1, hc32, hcp, hmm⟩
  have hd2 := Dec.match hdec' hmc ntU hntU v hv
  rw [show nt - 1 + 1 = nt by omega, show p - w + nl = p - k by omega, ← hout1] at hd2
  refine ⟨by rw [hout1, Std.Slice.set_length], hd2, MatchAt.back_part hm hmk hlk hdk,
    by omega, by omega⟩
@[local step]
theorem part_merge_spec {W : Std.Usize} (input : Slice Std.U8) (out : Slice Std.U32)
    (prev : Array Std.U32 W) (nt p l d : Std.Usize) (t : Std.U32) (w : Std.Usize)
    (hdec : Dec input out nt.val p.val) (hm : MatchAt input p.val l.val d.val)
    (hp8 : p.val + 8 ≤ input.length) (hnt0 : 1 ≤ nt.val) (hntl : nt.val ≤ out.length)
    (ht : (out.val[nt.val - 1]!).val = t.val) (ht24 : 16777216 ≤ t.val)
    (hw : w.val = (t.val - 16777216) % 256 + 3) (hW : 0 < W.val) :
    slot.u118_part_merge input out prev nt p l d t w ⦃ fun r =>
      r.2.length = out.length ∧ Dec input r.2 nt.val r.1.1.val ∧
      MatchAt input r.1.1.val r.1.2.val d.val ∧ r.1.1.val + r.1.2.val = p.val + l.val ∧
      r.1.1.val ≤ p.val ⦄ := by
  rw [slot.u118_part_merge]
  have hm' := hm
  obtain ⟨h3, h258, hpl, hd1, hd32, hdp, _⟩ := hm'
  have hwt : w.val = tokLen (out.val[nt.val - 1]!).val := by
    rw [ht, hw]; simp only [tokLen, MATCH_BASE]
  have ht256 : 256 ≤ (out.val[nt.val - 1]!).val := by rw [ht]; omega
  step*
  all_goals first
    | exact ⟨rfl, hdec, hm, rfl, le_refl _⟩
    | exact part_post hdec hm hnt0 hntl ht256 hwt (by assumption) (by assumption)
        (by assumption) (by scalar_tac) (by scalar_tac) (by scalar_tac) (by scalar_tac)
        (by scalar_tac) (by scalar_tac) (by scalar_tac) (by scalar_tac) (by scalar_tac)
        (by scalar_tac) (by simp only [LZ77.mkMatch, LZ77.MATCH_BASE]; scalar_tac)
        (by scalar_tac) (by scalar_tac)
def LazyInv (input : Slice Std.U8) (L lim : Nat) (out : Slice Std.U32) (nt p : Nat)
    {N : Std.Usize} (head : Array Std.U32 N) (ins l d : Nat) : Prop :=
  Dec input out nt p ∧ out.length = L ∧ MatchAt input p l d ∧ HeadBound head (p + 2) ∧
    p < lim ∧ ins ≤ p + 3
theorem LazyInv.accept {input : Slice Std.U8} {L lim p' B : Nat} {out1 : Slice Std.U32}
    {nt1 i ins1 l1 d1 minl : Std.Usize} {N : Std.Usize} {head1 : Array Std.U32 N}
    (hdec : Dec input out1 nt1.val p') (hi : i.val = p') (hlen : out1.length = L)
    (hf : FoundAt input i.val l1.val d1.val) (hl1 : minl.val ≤ l1.val) (hminl : 3 ≤ minl.val)
    (hB : HeadBound head1 B) (hBi : B ≤ i.val + 2) (hilim : i.val < lim)
    (hins : ins1.val ≤ i.val + 3) :
    LazyInv input L lim out1 nt1.val i.val head1 ins1.val l1.val d1.val := C12581!
theorem LazyInv.reject {input : Slice Std.U8} {L lim : Nat} {out : Slice Std.U32}
    {nt p ins ins1 l d B : Nat} {N : Std.Usize} {head head1 : Array Std.U32 N}
    (h : LazyInv input L lim out nt p head ins l d) (hB : HeadBound head1 B) (hBp : B ≤ p + 2)
    (hins1 : ins1 ≤ p + 3) : LazyInv input L lim out nt p head1 ins1 l d := C12582!
theorem Dec.cast {s : Slice Std.U8} {out : Slice Std.U32} {nt p p' : Nat} (h : Dec s out nt p)
    (hp : p' = p) : Dec s out nt p' := by
  subst hp; exact h
theorem lazy_loop_inv {H W : Std.Usize} (L2 : Std.Usize) (input : Slice Std.U8) (out : Slice Std.U32)
    (n nt p : Std.Usize) (mask : Std.U32) (minl lazy nice ldep : Std.Usize) (hlit : Std.I32)
    (head : Array Std.U32 H) (prev : Array Std.U32 W) (lim ins l d : Std.Usize) (go : Std.U32)
    (L : Nat) (hn : n.val = input.length) (hlim : lim.val + 8 = input.length)
    (hminl : 3 ≤ minl.val) (hminl8 : minl.val ≤ 8) (hH : 0 < H.val) (hW : 0 < W.val)
    (hh0 : 0 ≤ hlit.val) (hh1 : hlit.val ≤ 1000000)
    (hinv : LazyInv input L lim.val out nt.val p.val head ins.val l.val d.val) :
    slot.u118_run_loop0_loop1 L2 input out n nt p mask minl lazy nice ldep hlit head prev lim ins l d go
      ⦃ fun r => LazyInv input L lim.val r.1 r.2.1.val r.2.2.1.val r.2.2.2.1
        r.2.2.2.2.2.1.val r.2.2.2.2.2.2.1.val r.2.2.2.2.2.2.2.val ⦄ := by
  rw [slot.u118_run_loop0_loop1]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  have ⟨hL0, hL1⟩ := L2B_bound
  apply Std.loop.spec_decr_nat
    (measure := fun r => lim.val - r.2.2.1.val + r.2.2.2.2.2.2.2.2.val)
    (inv := fun r => LazyInv input L lim.val r.1 r.2.1.val r.2.2.1.val r.2.2.2.1
      r.2.2.2.2.2.1.val r.2.2.2.2.2.2.1.val r.2.2.2.2.2.2.2.1.val)
  · rintro ⟨out, nt, p, head, prev, ins, l, d, go⟩ hinv
    simp only at hinv
    have hinv' := hinv
    obtain ⟨hdec, hL, hm, hB, hplim, hins⟩ := hinv'
    have hdec' := hdec
    have hm' := hm
    obtain ⟨hps, hntp, hso, _⟩ := hdec'
    obtain ⟨h3, h258, hpl, hd1, hd32, hdp, _⟩ := hm'
    simp only [slot.u118_run_loop0_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals first
      | (refine ⟨LazyInv.accept (by assumption) (by scalar_tac) (by scalar_tac) (by assumption)
          (by scalar_tac) hminl (by assumption) (by scalar_tac) (by scalar_tac) (by scalar_tac),
          by scalar_tac⟩)
      | (refine ⟨LazyInv.reject hinv (by assumption) (by scalar_tac) (by scalar_tac),
          by scalar_tac⟩)
      | exact Dec.cast (by assumption) (by scalar_tac)
  · exact hinv
@[local step]
theorem lazy_loop_spec {H W : Std.Usize} (L2 : Std.Usize) (input : Slice Std.U8) (out : Slice Std.U32)
    (n nt p : Std.Usize) (mask : Std.U32) (minl lazy nice ldep : Std.Usize) (hlit : Std.I32)
    (head : Array Std.U32 H) (prev : Array Std.U32 W) (lim ins l d : Std.Usize) (go : Std.U32)
    (L : Nat) (hn : n.val = input.length) (hlim : lim.val + 8 = input.length)
    (hminl : 3 ≤ minl.val) (hminl8 : minl.val ≤ 8) (hH : 0 < H.val) (hW : 0 < W.val)
    (hh0 : 0 ≤ hlit.val) (hh1 : hlit.val ≤ 1000000)
    (hdec : Dec input out nt.val p.val) (hlen : out.length = L)
    (hm : MatchAt input p.val l.val d.val) (hB : HeadBound head (p.val + 2))
    (hplim : p.val < lim.val) (hins : ins.val ≤ p.val + 3) :
    slot.u118_run_loop0_loop1 L2 input out n nt p mask minl lazy nice ldep hlit head prev lim ins l d go
      ⦃ fun r =>
      Dec input r.1 r.2.1.val r.2.2.1.val ∧ r.1.length = L ∧
      MatchAt input r.2.2.1.val r.2.2.2.2.2.2.1.val r.2.2.2.2.2.2.2.val ∧
      HeadBound r.2.2.2.1 (r.2.2.1.val + r.2.2.2.2.2.2.1.val) ∧ r.2.2.1.val < lim.val ∧
      r.2.2.2.2.2.1.val ≤ r.2.2.1.val + 3 ∧ 3 ≤ r.2.2.2.2.2.2.1.val ⦄ := by
  apply Std.WP.spec_mono (lazy_loop_inv L2 input out n nt p mask minl lazy nice ldep hlit head prev
    lim ins l d go L hn hlim hminl hminl8 hH hW hh0 hh1 ⟨hdec, hlen, hm, hB, hplim, hins⟩)
  rintro ⟨out', nt', p', head', prev', ins', l', d'⟩ ⟨hdec', hlen', hm', hB', hplim', hins'⟩
  exact ⟨hdec', hlen', hm', HeadBound.mono hB' (by have := hm'.1; omega), hplim', hins', hm'.1⟩
theorem idx_bang {out : Slice Std.U32} {nt i1 : Std.Usize} {t : Std.U32}
    (hi1 : i1.val = nt.val - 1) (hl : i1.val < out.val.length) (ht : t = out.val[i1.val]) :
    (out.val[nt.val - 1]!).val = t.val := by
  rw [← hi1, getElem!_pos out.val i1.val hl, ← ht]
theorem back_loop_inv {W : Std.Usize} (input : Slice Std.U8) (out : Slice Std.U32)
    (nt p : Std.Usize) (prev : Array Std.U32 W) (l d back : Std.Usize) (L E P0 : Nat)
    (hP0 : P0 + 8 ≤ input.length) (hW : 0 < W.val)
    (hinv : BackInv input L d.val E P0 out nt.val p.val l.val) :
    slot.u118_run_loop0_loop2 input out nt p prev l d back ⦃ fun r =>
      BackInv input L d.val E P0 r.1 r.2.1.val r.2.2.1.val r.2.2.2.val ⦄ := by
  rw [slot.u118_run_loop0_loop2]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  apply Std.loop.spec_decr_nat
    (measure := fun r => slot.u118_BACKTOK.val - r.2.2.2.2.val)
    (inv := fun r => BackInv input L d.val E P0 r.1 r.2.1.val r.2.2.1.val r.2.2.2.1.val)
  · rintro ⟨out, nt, p, l, back⟩ hinv
    simp only at hinv
    have hinv' := hinv
    obtain ⟨hdec, hL, hm, hE, hp0⟩ := hinv'
    have hdec' := hdec
    have hm' := hm
    obtain ⟨hps, hntp, hso, _⟩ := hdec'
    obtain ⟨h3, h258, hpl, hd1, hd32, hdp, _⟩ := hm'
    simp only [slot.u118_run_loop0_loop2.body]
    step*
    all_goals first
      | (refine ⟨BackInv.lit hinv (by scalar_tac) (by scalar_tac) (by scalar_tac) (by scalar_tac)
          (by assumption) (by assumption) (by scalar_tac) (by scalar_tac) (by assumption)
          (by assumption) (by assumption) (by scalar_tac) (by assumption) (by scalar_tac)
          (by scalar_tac) (by scalar_tac), by scalar_tac⟩)
      | (refine ⟨BackInv.match hinv (by scalar_tac) (by scalar_tac) (by scalar_tac) (by scalar_tac)
          (by assumption) (by assumption) (by assumption) (by scalar_tac) (by scalar_tac)
          (by scalar_tac) (by scalar_tac) (by scalar_tac) (by scalar_tac) (by scalar_tac)
          (by scalar_tac), by scalar_tac⟩)
      | (refine ⟨BackInv.part hinv (by assumption) (by assumption) (by assumption)
          (by scalar_tac) (by scalar_tac), by scalar_tac⟩)
      | exact ⟨hinv, by scalar_tac⟩
      | exact idx_bang (i1 := i1) (by scalar_tac) (by scalar_tac) (by assumption)
      | (exfalso; scalar_tac)
  · exact hinv
@[local step]
theorem back_loop_spec {W : Std.Usize} (input : Slice Std.U8) (out : Slice Std.U32)
    (nt p : Std.Usize) (prev : Array Std.U32 W) (l d back : Std.Usize)
    (hp8 : p.val + 8 ≤ input.length) (hW : 0 < W.val) (hdec : Dec input out nt.val p.val)
    (hm : MatchAt input p.val l.val d.val) :
    slot.u118_run_loop0_loop2 input out nt p prev l d back ⦃ fun r =>
      Dec input r.1 r.2.1.val r.2.2.1.val ∧ r.1.length = out.length ∧
      MatchAt input r.2.2.1.val r.2.2.2.val d.val ∧
      r.2.2.1.val + r.2.2.2.val = p.val + l.val ∧ r.2.2.1.val ≤ p.val ⦄ := by
  apply Std.WP.spec_mono (back_loop_inv input out nt p prev l d back out.length (p.val + l.val)
    p.val hp8 hW ⟨hdec, rfl, hm, rfl, le_refl _⟩)
  intro r h
  obtain ⟨h1, h2, h3, h4, h5⟩ := h
  exact ⟨h1, h2, h3, h4, h5⟩
theorem sat_add_val (x y : Std.Usize) :
    (core.num.Usize.saturating_add x y).val = min Std.Usize.max (x.val + y.val) := by
  have hsz : Std.Usize.max < 2 ^ UScalarTy.Usize.numBits := by
    rw [Std.Usize.max_def, Std.Usize.numBits]
    have : 0 < 2 ^ UScalarTy.Usize.numBits := Nat.two_pow_pos _
    omega
  show (BitVec.ofNat _ (min (UScalar.max UScalarTy.Usize) (x.val + y.val))).toNat = _
  rw [BitVec.toNat_ofNat, UScalar.max_USize_eq, Nat.mod_eq_of_lt (by omega)]
@[local step]
theorem sat_add_spec (x y : Std.Usize) :
    lift (core.num.Usize.saturating_add x y) ⦃ fun r =>
      r.val = x.val + y.val ∨ (r.val = Std.Usize.max ∧ Std.Usize.max < x.val + y.val) ⦄ := by
  simp only [lift, Std.WP.spec_ok]
  rw [sat_add_val]
  omega
theorem sat_sub_val (x y : Std.Usize) :
    (core.num.Usize.saturating_sub x y).val = x.val - y.val := by
  have hx := x.hBounds
  show (BitVec.ofNat _ (max 0 (x.val - y.val))).toNat = x.val - y.val
  rw [BitVec.toNat_ofNat, Nat.zero_max]
  exact Nat.mod_eq_of_lt (lt_of_le_of_lt (Nat.sub_le _ _) hx)
@[local step]
theorem sat_sub_spec (x y : Std.Usize) :
    lift (core.num.Usize.saturating_sub x y) ⦃ fun r => r.val = x.val - y.val ⦄ := by
  simp only [lift, Std.WP.spec_ok]
  exact sat_sub_val x y
theorem tail_sub_ok {ins e t i : Std.Usize} (hi : i = core.num.Usize.wrapping_add ins t)
    (hlt : i < e) (hie : ins.val ≤ e.val) (ht : t.val ≤ 2147483648) : t.val ≤ e.val := by
  have hsz : 4294967296 ≤ Usize.size := by scalar_tac
  have hil : i.val < e.val := by scalar_tac
  have hel : e.val < Usize.size := by scalar_tac
  rw [hi, core.num.Usize.wrapping_add_val_eq, UScalar.size_UScalarTyUsize] at hil
  by_cases hw : ins.val + t.val < Usize.size
  · rw [Nat.mod_eq_of_lt hw] at hil; omega
  · omega
@[local step]
theorem ins_loop0_spec {H W : Std.Usize} (input : Slice Std.U8) (p : Std.Usize) (mask : Std.U32)
    (head : Array Std.U32 H) (prev : Array Std.U32 W) (ins : Std.Usize) (B : Nat)
    (hB : HeadBound head B) (hpB : p.val < B + 1) (hp4 : p.val + 4 ≤ Std.Usize.max)
    (hH : 0 < H.val) (hW : 0 < W.val) :
    slot.u118_run_loop0_loop0 input p mask head prev ins ⦃ fun r => HeadBound r.1 B ⦄ := C12585! slot.u118_run_loop0_loop0 slot.u118_run_loop0_loop0.body
@[local step]
theorem ins_loop3_spec {H W : Std.Usize} (input : Slice Std.U8) (mask : Std.U32)
    (head : Array Std.U32 H) (prev : Array Std.U32 W) (ins stop : Std.Usize) (B : Nat)
    (hB : HeadBound head B) (hsB : stop.val < B + 1) (hs4 : stop.val + 4 ≤ Std.Usize.max)
    (hH : 0 < H.val) (hW : 0 < W.val) :
    slot.u118_run_loop0_loop3 input mask head prev ins stop ⦃ fun r =>
      HeadBound r.1 B ∧ (r.2.2.val ≤ ins.val ∨ r.2.2.val ≤ stop.val) ⦄ := C12586! slot.u118_run_loop0_loop3 slot.u118_run_loop0_loop3.body
@[local step]
theorem stride_loop_spec {H W : Std.Usize} (input : Slice Std.U8) (mask : Std.U32)
    (stride : Std.Usize) (head : Array Std.U32 H) (prev : Array Std.U32 W) (lim ins e2 : Std.Usize)
    (B : Nat) (hB : HeadBound head B) (heB : e2.val < B + 1) (hl4 : lim.val + 4 ≤ Std.Usize.max)
    (hH : 0 < H.val) (hW : 0 < W.val) (hS : 0 < stride.val)
    (hS2 : e2.val + stride.val ≤ Std.Usize.max) :
    slot.u118_run_loop0_loop4 input mask stride head prev lim ins e2 ⦃ fun r =>
      HeadBound r.1 B ∧ (r.2.2.val ≤ ins.val ∨ (0 < e2.val ∧ r.2.2.val < e2.val + stride.val)) ⦄ := by
  rw [slot.u118_run_loop0_loop4]
  apply Std.loop.spec_decr_nat
    (measure := fun r => e2.val - r.2.2.val)
    (inv := fun r => HeadBound r.1 B ∧
      (r.2.2.val ≤ ins.val ∨ (0 < e2.val ∧ r.2.2.val < e2.val + stride.val)))
  · rintro ⟨head, prev, ins'⟩ ⟨hB, hins⟩
    simp only at hB hins
    simp only [slot.u118_run_loop0_loop4.body]
    step*
    all_goals first
      | exact ⟨hB, hins⟩
      | exact ⟨by assumption, by scalar_tac, by scalar_tac⟩
  · exact ⟨hB, Or.inl (le_refl _)⟩
@[local step]
theorem ins_loop5_spec {H W : Std.Usize} (input : Slice Std.U8) (mask : Std.U32)
    (head : Array Std.U32 H) (prev : Array Std.U32 W) (lim ins «end» : Std.Usize) (B : Nat)
    (hB : HeadBound head B) (heB : «end».val < B + 1) (hl4 : lim.val + 4 ≤ Std.Usize.max)
    (hH : 0 < H.val) (hW : 0 < W.val) :
    slot.u118_run_loop0_loop5 input mask head prev lim ins «end» ⦃ fun r =>
      HeadBound r.1 B ∧ (r.2.2.val ≤ ins.val ∨ r.2.2.val ≤ «end».val) ⦄ := C12588! slot.u118_run_loop0_loop5 slot.u118_run_loop0_loop5.body
@[local step]
theorem ins_loop6_spec {H W : Std.Usize} (input : Slice Std.U8) (mask : Std.U32)
    (head : Array Std.U32 H) (prev : Array Std.U32 W) (lim ins «end» : Std.Usize) (B : Nat)
    (hB : HeadBound head B) (heB : «end».val < B + 1) (hl4 : lim.val + 4 ≤ Std.Usize.max)
    (hH : 0 < H.val) (hW : 0 < W.val) :
    slot.u118_run_loop0_loop6 input mask head prev lim ins «end» ⦃ fun r =>
      HeadBound r.1 B ∧ (r.2.2.val ≤ ins.val ∨ r.2.2.val ≤ «end».val) ⦄ := C12588! slot.u118_run_loop0_loop6 slot.u118_run_loop0_loop6.body
@[local step]
theorem skip_loop_spec (input : Slice Std.U8) (out : Slice Std.U32) (nt p lim step : Std.Usize)
    (hdec : Dec input out nt.val p.val) (hlim : lim.val ≤ input.length) :
    slot.u118_run_loop0_loop7 input out nt p lim step ⦃ fun r =>
      Dec input r.1 r.2.1.val r.2.2.val ∧ r.1.length = out.length ∧ p.val ≤ r.2.2.val ⦄ := C12589! slot.u118_run_loop0_loop7 slot.u118_run_loop0_loop7.body
@[local step]
theorem tail_loop1_spec (input : Slice Std.U8) (out : Slice Std.U32) (n nt p : Std.Usize)
    (hn : n.val = input.length) (hdec : Dec input out nt.val p.val) :
    slot.u118_run_loop1 input out n nt p ⦃ fun r => r.1.val ≤ input.length ∧
      r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := C12590! slot.u118_run_loop1 slot.u118_run_loop1.body
@[local step]
theorem tail_loop2_spec (input : Slice Std.U8) (out : Slice Std.U32) (n nt p : Std.Usize)
    (hn : n.val = input.length) (hdec : Dec input out nt.val p.val) :
    slot.u118_run_loop2 input out n nt p ⦃ fun r => r.1.val ≤ input.length ∧
      r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := C12590! slot.u118_run_loop2 slot.u118_run_loop2.body
theorem numBits_ge : 32 ≤ System.Platform.numBits := C12527!
def MainInv (input : Slice Std.U8) (L : Nat) (out : Slice Std.U32) (nt p : Nat)
    {N : Std.Usize} (head : Array Std.U32 N) (miss : Nat) : Prop :=
  Dec input out nt p ∧ out.length = L ∧ HeadBound head p ∧ miss ≤ p
theorem MainInv.mk' {input : Slice Std.U8} {L : Nat} {out : Slice Std.U32} {nt p m B : Nat}
    {N : Std.Usize} {head : Array Std.U32 N} (hdec : Dec input out nt p) (hlen : out.length = L)
    (hB : HeadBound head B) (hBp : B ≤ p) (hm : m ≤ p) : MainInv input L out nt p head m :=
  ⟨hdec, hlen, HeadBound.mono hB hBp, hm⟩
set_option maxHeartbeats 16000000 in
theorem main_loop_spec {H W : Std.Usize} (L2 : Std.Usize) (input : Slice Std.U8) (out : Slice Std.U32)
    (n nt p : Std.Usize) (mask : Std.U32)
    (minl depth lazy skip skcap nice ldep insm stride : Std.Usize) (hlit : Std.I32)
    (head : Array Std.U32 H) (prev : Array Std.U32 W) (lim ins miss fuel : Std.Usize) (L : Nat)
    (hn : n.val = input.length) (hlim : lim.val + 8 = input.length) (hminl : 3 ≤ minl.val)
    (hminl8 : minl.val ≤ 8) (hskip : skip.val < 32) (hH : 0 < H.val) (hW : 0 < W.val)
    (hh0 : 0 ≤ hlit.val) (hh1 : hlit.val ≤ 1000000)
    (hinv : MainInv input L out nt.val p.val head miss.val) :
    slot.u118_run_loop0 L2 input out n nt p mask minl depth lazy skip skcap nice ldep insm stride hlit
      head prev lim ins miss fuel ⦃ fun r => Dec input r.1 r.2.1.val r.2.2.val ∧ r.1.length = L ⦄ := by
  rw [slot.u118_run_loop0]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  apply Std.loop.spec_decr_nat
    (measure := fun r => r.2.2.2.2.2.2.2.val)
    (inv := fun r => MainInv input L r.1 r.2.1.val r.2.2.1.val r.2.2.2.1 r.2.2.2.2.2.2.1.val)
  · rintro ⟨out, nt, p, head, prev, ins, miss, fuel⟩ hinv
    simp only at hinv
    have hinv' := hinv
    obtain ⟨hdec, hL, hB, hmiss⟩ := hinv'
    simp only [slot.u118_run_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals first
      | (refine ⟨MainInv.mk' (by assumption) (by omega) (by assumption) (by omega)
          (by first | omega | simp), by omega⟩)
      | exact FoundAt.real (by assumption) (by scalar_tac)
      | exact HeadBound.mono (by assumption) (by omega)
      | exact tail_sub_ok (by assumption) (by assumption) (by scalar_tac) (by scalar_tac)
      | exact Dec.cast (by assumption) (by omega)
      | omega
      | (have := numBits_ge; scalar_tac)
  · exact hinv
@[local step]
theorem main_loop_spec' {H W : Std.Usize} (L2 : Std.Usize) (input : Slice Std.U8) (out : Slice Std.U32)
    (n nt p : Std.Usize) (mask : Std.U32)
    (minl depth lazy skip skcap nice ldep insm stride : Std.Usize) (hlit : Std.I32)
    (head : Array Std.U32 H) (prev : Array Std.U32 W) (lim ins miss fuel : Std.Usize)
    (hn : n.val = input.length) (hlim : lim.val + 8 = input.length) (hminl : 3 ≤ minl.val)
    (hminl8 : minl.val ≤ 8) (hskip : skip.val < 32) (hH : 0 < H.val) (hW : 0 < W.val)
    (hh0 : 0 ≤ hlit.val) (hh1 : hlit.val ≤ 1000000)
    (hdec : Dec input out nt.val p.val) (hB : HeadBound head p.val) (hmiss : miss.val ≤ p.val) :
    slot.u118_run_loop0 L2 input out n nt p mask minl depth lazy skip skcap nice ldep insm stride hlit
      head prev lim ins miss fuel ⦃ fun r =>
        Dec input r.1 r.2.1.val r.2.2.val ∧ r.1.length = out.length ⦄ :=
  main_loop_spec L2 input out n nt p mask minl depth lazy skip skcap nice ldep insm stride hlit head
    prev lim ins miss fuel out.length hn hlim hminl hminl8 hskip hH hW hh0 hh1
    ⟨hdec, rfl, hB, hmiss⟩
set_option maxHeartbeats 16000000 in
def CntBound (cnt : Array Std.U32 256#usize) (T : Nat) : Prop :=
  ∀ j : Nat, j < 256 → (cnt.val[j]!).val ≤ T
theorem CntBound.init : CntBound (Std.Array.repeat 256#usize 0#u32) 0 := C1251!
theorem CntBound.get {cnt : Array Std.U32 256#usize} {T : Nat} (h : CntBound cnt T)
    (a : Std.Usize) (x : Std.U32) (ha : a.val < cnt.val.length) (hx : x = cnt.val[a.val]) :
    x.val ≤ T := C1252!
@[local step]
theorem cnt_index_spec (cnt : Array Std.U32 256#usize) (T : Nat) (h : CntBound cnt T)
    (i : Std.Usize) (hi : i.val < 256) :
    Std.Array.index_usize cnt i ⦃ fun x => x = cnt.val[i.val]! ∧ x.val ≤ T ⦄ := C1253!
theorem CntBound.update {cnt : Array Std.U32 256#usize} {T : Nat} (h : CntBound cnt T)
    (a : Std.Usize) (v : Std.U32) (hv : v.val ≤ T + 1) : CntBound (cnt.set a v) (T + 1) := C1254!
theorem CntBound.step {cnt a : Array Std.U32 256#usize} {T : Nat} {x : Std.Usize}
    {v tot1 : Std.U32} (hc : CntBound cnt T) (ha : a = cnt.set x v) (hv : v.val ≤ T + 1)
    (ht1 : tot1.val = T + 1) : CntBound a tot1.val := C1255!
theorem CntBound.mono {cnt : Array Std.U32 256#usize} {T T' : Nat} (h : CntBound cnt T)
    (hT : T ≤ T') : CntBound cnt T' := fun j hj => le_trans (h j hj) hT
@[local step]
theorem lift_spec {α : Type} (x : α) : lift x ⦃ fun y => y = x ⦄ := by
  simp [lift]
@[local step]
theorem run_spec (H W : Std.Usize) (MASK : Std.U32)
    (MINL DEPTH LAZY SKIP CAP STOP LD INS STR : Std.Usize) (LIT : Std.I32) (L2 : Std.Usize)
    (input : Slice Std.U8) (out : Slice Std.U32)
    (hlen : input.length ≤ out.length) (hH : 0 < H.val) (hW : 0 < W.val)
    (hmin : 3 ≤ MINL.val) (hmax : MINL.val ≤ 8) (hs : SKIP.val < 32)
    (hl0 : 0 ≤ LIT.val) (hl1 : LIT.val ≤ 1000000) :
    slot.u118_run H W MASK MINL DEPTH LAZY SKIP CAP STOP LD INS STR LIT L2 input out
      ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧
      LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := C12592! slot.u118_run
end U118_MAIN
namespace R107
open Aeneas Aeneas.Std Result ControlFlow
open LZ77 (toks bytes)
set_option maxRecDepth 8192
set_option maxHeartbeats 4000000
attribute [local step] EO.EA.match_len_spec EO.EA.emit_step_spec
end R107
namespace C107
open Aeneas Aeneas.Std Result ControlFlow
open EO.EA LZ77
set_option maxHeartbeats 4000000
set_option maxRecDepth 8192
attribute [local step] EO.EA.sh_lc_spec EO.EA.sh_dc_spec EO.EA.sh_fill_spec EO.EA.fl_emit_step_spec
@[local step]
theorem c_add_spec (stats : Array Std.U32 128#usize) (l d : Std.Usize) :
 slot.r107_c_add stats l d ⦃ fun _ => True ⦄ := by
 rw [slot.r107_c_add]
 step*
 all_goals scalar_tac
section
attribute [local step] Submission.r70_ite_true_spec
theorem sh_table_loop0_spec (B : Std.Usize) (stats : Array Std.U32 128#usize) (q : Array Std.Usize 320#usize)
  (lb : Array Std.Usize 29#usize) (best : Std.Usize) (c : Std.Usize) :
    slot.r107_c_table_loop0 B stats q lb best c ⦃ fun _ => True ⦄ := C12512! slot.r107_c_table_loop0 slot.r107_c_table_loop0.body
end
attribute [local step] sh_table_loop0_spec
section
attribute [local step] Submission.r70_ite_true_spec
theorem sh_table_loop1_spec (DB : Std.U32) (stats : Array Std.U32 128#usize) (q : Array Std.Usize 320#usize)
  (c : Std.Usize) :
    slot.r107_c_table_loop1 DB stats q c ⦃ fun _ => True ⦄ := C12513! slot.r107_c_table_loop1 slot.r107_c_table_loop1.body
end
attribute [local step] sh_table_loop1_spec
section
attribute [local step] Submission.r70_ite_true_spec
theorem sh_table_spec (B : Std.Usize) (DB : Std.U32) (stats : Array Std.U32 128#usize) (q : Array Std.Usize 320#usize) :
    slot.r107_c_table B DB stats q ⦃ fun _ => True ⦄ := C1258! slot.r107_c_table
end
attribute [local step] sh_table_spec
section
attribute [local step] Submission.r70_ite_true_spec
theorem sh_litrun_loop_spec (cache : Array Std.U32 8192#usize) (ix : Std.Usize) (sum : Std.Usize)
  (k : Std.Usize) :
    slot.r107_c_litrun_loop cache ix sum k ⦃ fun _ => True ⦄ := by
  rw [slot.r107_c_litrun_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => 8192 - s.2.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1⟩ _
    simp only [slot.r107_c_litrun_loop.body, lift, Array.to_slice_mut]
    step*
    repeat (first
      | (intro hc; (try step*))
      | (split <;> (try step*))
      | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply spec_ite_cut <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals scalar_tac
  · trivial
end
attribute [local step] sh_litrun_loop_spec
section
attribute [local step] Submission.r70_ite_true_spec
theorem sh_litrun_spec (cache : Array Std.U32 8192#usize) (ix : Std.Usize) :
    slot.r107_c_litrun cache ix ⦃ fun _ => True ⦄ := C1258! slot.r107_c_litrun
end
attribute [local step] sh_litrun_spec
section
attribute [local step] ite_true_spec
@[local step]
theorem sh_replay_loop_spec (input : Slice Std.U8) (out0 : Slice Std.U32) (cache : Array Std.U32 8192#usize) (q : Array Std.Usize 320#usize)
    (n pos0 ntok0 ix0 rem0 dist0 : Std.Usize)
    (hn : n.val = input.length) (hout : input.length ≤ out0.length)
    (hp : pos0.val ≤ n.val) (hntok : ntok0.val ≤ pos0.val)
    (hdec : LZ77.decode (toks out0 ntok0.val) = some ((bytes input).take pos0.val)) :
    slot.r107_c_replay_loop input out0 cache q n pos0 ntok0 ix0 rem0 dist0 ⦃ fun r =>
      r.2.1.val ≤ n.val ∧ r.2.2.val ≤ r.2.1.val ∧ r.1.length = out0.length ∧
      LZ77.decode (toks r.1 r.2.2.val) = some ((bytes input).take r.2.1.val) ⦄ := C12517! slot.r107_c_replay_loop slot.r107_c_replay_loop.body
end
attribute [local step] sh_replay_loop_spec
section
attribute [local step] ite_true_spec
@[local step]
theorem sh_replay_spec (input : Slice Std.U8) (out : Slice Std.U32) (cache : Array Std.U32 8192#usize) (q : Array Std.Usize 320#usize)
    (hlen : input.length ≤ out.length) :
    slot.r107_c_replay input out cache q ⦃ fun r =>
      r.1.2.val ≤ input.length ∧ r.1.1.val ≤ r.1.2.val ∧ r.2.length = out.length ∧
      LZ77.decode (toks r.2 r.1.1.val) = some ((bytes input).take r.1.2.val) ⦄ := C12516! slot.r107_c_replay
end
attribute [local step] sh_replay_spec
open EO.EA
section
attribute [local step] c_add_spec Submission.r70_ite_true_spec
@[local step]
theorem probe_loop_spec
 (cache : Array Std.U32 8192#usize) (stats : Array Std.U32 128#usize)
 (temp : Array Std.U32 32768#usize) (nt i : Std.Usize) :
 slot.r107_c_probe_loop cache stats temp nt i ⦃ fun _ => True ⦄ := by
 rw [slot.r107_c_probe_loop]
 apply Std.loop.spec_decr_nat (measure := fun s => 8192 - s.2.2.val) (inv := fun _ => True)
 · rintro ⟨cache, stats, i⟩ _
   simp only [slot.r107_c_probe_loop.body, lift]
   step*
   all_goals (repeat (first
     | (intro hc; try step*)
     | (split <;> try step*)
     | (guard_hyp x :~ _ × _; obtain ⟨a,b⟩ := x; try step*)
     | (apply EO.EA.spec_ite_cut <;> intro hc <;> try step*)
     | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
     | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*)))
   all_goals scalar_tac
 · trivial
end
attribute [local step] probe_loop_spec FX0.run_spec
theorem probe_spec (input : Slice Std.U8)
 (cache : Array Std.U32 8192#usize) (stats : Array Std.U32 128#usize) :
 slot.r107_c_probe input cache stats ⦃ fun _ => True ⦄ := by
 rw [slot.r107_c_probe]
 apply EO.EA.spec_ite_cut
 all_goals intro hc
 · step*
 · have hi : input.length ≤ 32768 := by scalar_tac
   simp only [lift, Array.to_slice_mut]
   step*
   all_goals (rw [Std.Array.length_to_slice]; exact hi)
@[local step]
theorem cached_spec (B : Std.Usize) (DB : Std.U32) (input : Slice Std.U8) (out : Slice Std.U32)
 (hlen : input.length ≤ out.length) :
 slot.r107_cached B DB input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧
 LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.r107_cached]
 apply Std.WP.spec_bind (probe_spec input _ _)
 rintro ⟨p, cache, stats⟩ _
 apply EO.EA.spec_ite_cut
 all_goals intro hc
 · apply Std.WP.spec_bind (sh_table_spec _ _ stats _)
   intro q _
   apply Std.WP.spec_bind (sh_replay_spec input out cache q hlen)
   rintro ⟨⟨nt, pos⟩, out'⟩ ⟨hp, ht, ho, hd⟩
   have hout : input.length ≤ out'.length := by rw [ho]; exact hlen
   apply EO.EA.spec_ite_cut
   all_goals intro hc
   · apply Std.WP.spec_mono (fallback_spec input out' hout)
     rintro ⟨nt', out''⟩ ⟨hnt, hlen', hv⟩
     exact ⟨hnt, hlen'.trans ho, hv⟩
   · step*
     have he : pos.val = input.length := by scalar_tac
     refine ⟨by scalar_tac, ho, ?_⟩
     have htake : (bytes input).take input.length = bytes input := by
       rw [← LZ77.bytes_length input]; exact List.take_length
     change LZ77.decode (toks out' nt.val) = some (bytes input)
     rw [he, htake] at hd; exact hd
 · exact fallback_spec input out hlen
end C107
set_option hygiene false in
local notation "C12594!" => (by
  have hx0' : ¬x = 0#u64 := by simpa using hx0
  have h := Matches.word_lz (k := 0) (k1 := m) (pa := c) (pb := p)
    (LZ77.Matches.zero s c.val p.val) (by simp) (by simp) hcw hy hx hx0' hlz hq hm (by simp)
  simpa using h)
set_option hygiene false in
local notation "C12595!" => (by
  have hv : x.val = 0 := by simpa using hx0
  have hx0' : x = 0#u64 := UScalar.eq_of_val_eq (by simp [hv])
  exact Matches.word_zero (k := 0) (k1 := 8#usize) (pa := c) (pb := p)
    (LZ77.Matches.zero s c.val p.val) (by simp) (by simp) hcw hy hx hx0' (by simp))
set_option hygiene false in
local notation "C12596!" => (by
  obtain ⟨hdv, hd1, hd2⟩ := dist_of_wrapping hc hd hi hlt
  refine ⟨?_, hl, hd2⟩
  rcases Nat.lt_or_ge l.val 3 with h3 | h3
  · exact Or.inl h3
  · refine Or.inr ⟨h3, hl, hpl, hd1, hd2, by omega, ?_⟩
    rw [show p.val - d.val = c.val by omega]
    exact hm)
set_option hygiene false in
local notation "C12597!" => (by
  obtain ⟨hm, _, hplim, _, _, _, _, hP⟩ := h
  exact ⟨hm, HeadBound.mono hB hBp, hplim, hins1, hps, hpc, hpw, hP⟩)
namespace PX
open Aeneas Aeneas.Std Result ControlFlow
set_option maxRecDepth 8192
set_option maxHeartbeats 4000000
set_option linter.unusedVariables false
open LZ77 (toks bytes bytes_length bytes_getElem! toks_update bytes_congr
  Matches Found emit_lit emit_match ite_ok)
open LZ77 (decode emit copyN tokLen tokDist MATCH_BASE TOK_LIMIT decode_snoc copyN_length)
section TinyPath
set_option linter.unusedTactic false
set_option linter.unreachableTactic false
@[local step]
theorem tp_lift_spec {α : Type} (x : α) : lift x ⦃ fun y => y = x ⦄ := by
  simp [lift, WP.spec_ok]
theorem tp_numBits_ge : 32 ≤ System.Platform.numBits := by
  cases System.Platform.numBits_eq <;> simp [*]
@[local scalar_tac System.Platform.numBits]
theorem tp_numBits_ge' : 32 ≤ System.Platform.numBits := tp_numBits_ge
end TinyPath
@[irreducible] def word8 (input : Slice Std.U8) (p : Nat) : Nat :=
  (input.val[p]!).val * 2^56 + (input.val[p + 1]!).val * 2^48 + (input.val[p + 2]!).val * 2^40
    + (input.val[p + 3]!).val * 2^32 + (input.val[p + 4]!).val * 2^24
    + (input.val[p + 5]!).val * 2^16 + (input.val[p + 6]!).val * 2^8 + (input.val[p + 7]!).val
theorem u8_lt (x : Std.U8) : x.val < 256 := by scalar_tac
theorem word8_digit (input : Slice Std.U8) (p k : Nat) (hk : k < 8) :
    (input.val[p + k]!).val = word8 input p / 256 ^ (7 - k) % 256 := C12530!
theorem word8_prefix (input : Slice Std.U8) (a b d : Nat) (hd : d ≤ 8)
    (h : word8 input a / 2 ^ (64 - 8 * d) = word8 input b / 2 ^ (64 - 8 * d)) :
    ∀ k, k < d → input.val[b + k]! = input.val[a + k]! := C12531!
theorem Matches.add_prefix {input : Slice Std.U8} {a b l d : Nat} (h : Matches input a b l)
    (hd : d ≤ 8)
    (hw : word8 input (a + l) / 2 ^ (64 - 8 * d) = word8 input (b + l) / 2 ^ (64 - 8 * d)) :
    Matches input a b (l + d) := C12532!
theorem or_eq_add_of_mod {x t : Nat} (m : Nat) (hx : x % 2 ^ m = 0) (ht : t < 2 ^ m) :
    x ||| t = x + t := C12533!
theorem shl_byte {x : Nat} (k : Nat) (hx : x < 256) (hk : k ≤ 56) :
    x <<< k % U64.size = x * 2 ^ k := C12534!
theorem be8_nat {a b c d e f g h : Nat} (ha : a < 256) (hb : b < 256) (hc : c < 256)
    (hd : d < 256) (he : e < 256) (hf : f < 256) (hg : g < 256) (hh : h < 256) :
    (a <<< 56 % U64.size ||| b <<< 48 % U64.size ||| c <<< 40 % U64.size |||
      d <<< 32 % U64.size ||| e <<< 24 % U64.size ||| f <<< 16 % U64.size |||
      g <<< 8 % U64.size ||| h) =
    a * 2^56 + b * 2^48 + c * 2^40 + d * 2^32 + e * 2^24 + f * 2^16 + g * 2^8 + h := C12535!
theorem nat_xor_eq_zero {a b : Nat} (h : a ^^^ b = 0) : a = b := C12537!
theorem div_eq_of_xor_lt {x y m : Nat} (hz : x ^^^ y < 2 ^ m) : x / 2 ^ m = y / 2 ^ m := C12538!
theorem lt_pow_leadingZeros (z : BitVec 64) :
    z.toNat < 2 ^ (64 - 8 * (BitVec.leadingZeros z / 8)) := C12539!
theorem leadingZeros_lt_of_ne (z : BitVec 64) (h : z ≠ 0) : BitVec.leadingZeros z < 64 := C12540!
@[local step]
theorem lz_spec (x : Std.U64) :
    lift (core.num.U64.leading_zeros x) ⦃ fun r => r = core.num.U64.leading_zeros x ∧ r.val ≤ 64 ⦄ := C12541!
theorem lz_val (x : Std.U64) :
    (core.num.U64.leading_zeros x).val = BitVec.leadingZeros x.bv := C12542!
theorem Matches.word_lz {input : Slice Std.U8} {a b k : Nat} {pa pb r k1 : Std.Usize}
    {x y z : Std.U64} {lz q : Std.U32}
    (h : Matches input a b k) (hpa : pa.val = a + k) (hpb : pb.val = b + k)
    (hx : x.val = word8 input pa.val) (hy : y.val = word8 input pb.val)
    (hz : z.val = (x ^^^ y).val) (hz0 : ¬z = 0#u64) (hlz : lz = core.num.U64.leading_zeros z)
    (hq : q.val = lz.val / 8) (hr : r = UScalar.cast .Usize q) (hk1 : k1.val = k + r.val) :
    Matches input a b k1.val ∧ k1.val < k + 8 := C12543!
theorem Matches.word_zero {input : Slice Std.U8} {a b k : Nat} {pa pb k1 : Std.Usize}
    {x y z : Std.U64}
    (h : Matches input a b k) (hpa : pa.val = a + k) (hpb : pb.val = b + k)
    (hx : x.val = word8 input pa.val) (hy : y.val = word8 input pb.val)
    (hz : z.val = (x ^^^ y).val) (hz0 : z = 0#u64) (hk1 : k1.val = k + 8) :
    Matches input a b k1.val := C12544!
theorem Matches.byte' {input : Slice Std.U8} {a b l : Nat} {pa pb l1 : Std.Usize}
    {x y : Std.U8} (h : Matches input a b l) (hpa : pa.val = a + l) (hpb : pb.val = b + l)
    (hpa' : pa.val < input.val.length) (hpb' : pb.val < input.val.length)
    (hx : x = input.val[pa.val]) (hy : y = input.val[pb.val]) (hxy : x = y)
    (hl1 : l1.val = l + 1) : Matches input a b l1.val := C12545!
theorem Matches.word_eq {input : Slice Std.U8} {a b k : Nat} {pa pb k1 : Std.Usize}
    {x y : Std.U64}
    (h : Matches input a b k) (hpa : pa.val = a + k) (hpb : pb.val = b + k)
    (hx : x.val = word8 input pa.val) (hy : y.val = word8 input pb.val)
    (hxy : x = y) (hk1 : k1.val = k + 8) :
    Matches input a b k1.val := C12549!
theorem Matches.mask {input : Slice Std.U8} {a b k len : Nat} {pa pb : Std.Usize}
    {x y z w : Std.U64} {sh : Std.U32}
    (h : Matches input a b k) (hpa : pa.val = a + k) (hpb : pb.val = b + k)
    (hx : x.val = word8 input pa.val) (hy : y.val = word8 input pb.val)
    (hz : z.val = (x ^^^ y).val) (hw : w.val = z.val >>> sh.val) (hw0 : ¬(w != 0#u64) = true)
    (hsh : sh.val = 64 - 8 * (len - k)) (hk : k < len) (hlen : len < k + 8) :
    Matches input a b len := C12552!
theorem lz32_le (x : Std.U32) (k : Nat) (hk : k < 32) (hx : 2 ^ k ≤ x.val) :
    (core.num.U32.leading_zeros x).val ≤ 31 - k := C12554!
@[local step]
theorem lz32_spec (x : Std.U32) :
    lift (core.num.U32.leading_zeros x) ⦃ fun r => r = core.num.U32.leading_zeros x ∧
      (4 ≤ x.val → r.val ≤ 29) ∧ (8 ≤ x.val → r.val ≤ 28) ⦄ := C12555!
@[local step]
theorem hcast_I32_spec {ty : UScalarTy} (x : UScalar ty) (h : x.val ≤ 2147483647) :
    lift (UScalar.hcast .I32 x) ⦃ fun y => y.val = x.val ⦄ :=
  UScalar.hcast_inBounds_spec .I32 x (by simp [I32.max_def, I32.numBits]; omega)
theorem GBASE_bound : -1000000000 ≤ slot.x_GBASE.val ∧ slot.x_GBASE.val ≤ 1000000000 := by
  unfold slot.x_GBASE
  simp
def HeadBound {N : Std.Usize} (head : Array Std.U32 N) (B : Nat) : Prop :=
  ∀ j : Nat, j < head.val.length → (head.val[j]!).val ≤ B
theorem HeadBound.mono {N : Std.Usize} {head : Array Std.U32 N} {B B' : Nat}
    (h : HeadBound head B) (hB : B ≤ B') : HeadBound head B' := fun j hj => le_trans (h j hj) hB
theorem HeadBound.init (N : Std.Usize) : HeadBound (Std.Array.repeat N 0#u32) 0 := C12556!
theorem HeadBound.set {N : Std.Usize} {head : Array Std.U32 N} {B : Nat} (h : HeadBound head B)
    (a : Std.Usize) (v : Std.U32) (hv : v.val ≤ B) : HeadBound (head.set a v) B := C12557!
theorem HeadBound.update {N : Std.Usize} {head head1 : Array Std.U32 N} {B : Nat}
    {a i : Std.Usize} {v : Std.U32} (h : HeadBound head B) (hv : v = UScalar.cast .U32 i)
    (hi : i.val ≤ B) (h1 : head1 = head.set a v) : HeadBound head1 B := C12558!
theorem HeadBound.get {N : Std.Usize} {head : Array Std.U32 N} {B : Nat} (h : HeadBound head B)
    (a : Std.Usize) (x : Std.U32) (ha : a.val < head.val.length) (hx : x = head.val[a.val]) :
    x.val ≤ B := C12559!
theorem cast_usize_le {x : Std.U32} {y : Std.Usize} {B : Nat} (h : y = UScalar.cast .Usize x)
    (hx : x.val ≤ B) : y.val ≤ B := by
  rw [h, U32.cast_Usize_val_eq]; exact hx
def Cand (s : Slice Std.U8) (p cap best bd : Nat) : Prop :=
  bd = 0 ∨ (1 ≤ bd ∧ bd ≤ 32768 ∧ bd ≤ p ∧ best ≤ cap ∧ Matches s (p - bd) p best)
theorem dist_of_wrapping {p c d i : Std.Usize} (hc : c.val ≤ p.val)
    (hd : d = core.num.Usize.wrapping_sub p c) (hi : i = core.num.Usize.wrapping_sub d 1#usize)
    (hlt : i < 32768#usize) : d.val = p.val - c.val ∧ 1 ≤ d.val ∧ d.val ≤ 32768 := C12561!
theorem Cand.of_common {s : Slice Std.U8} {p c d i l cap : Std.Usize} (hc : c.val ≤ p.val)
    (hd : d = core.num.Usize.wrapping_sub p c) (hi : i = core.num.Usize.wrapping_sub d 1#usize)
    (hlt : i < 32768#usize) (hl : l.val ≤ cap.val) (hm : Matches s c.val p.val l.val) :
    Cand s p.val cap.val l.val d.val := C12562!
def MatchAt (s : Slice Std.U8) (p l d : Nat) : Prop :=
  3 ≤ l ∧ l ≤ 258 ∧ p + l ≤ s.length ∧ 1 ≤ d ∧ d ≤ 32768 ∧ d ≤ p ∧ Matches s (p - d) p l
def FoundAt (s : Slice Std.U8) (p l d : Nat) : Prop := l < 3 ∨ MatchAt s p l d
theorem FoundAt.of_cand {s : Slice Std.U8} {p cap : Nat} {l d : Std.Usize}
    (hc : Cand s p cap l.val d.val) (hd : ¬d = 0#usize) (hcap : cap ≤ 258)
    (hpl : p + l.val ≤ s.length) : FoundAt s p l.val d.val := C12565!
theorem Cand.len_le {s : Slice Std.U8} {p cap : Nat} {l d : Std.Usize}
    (hc : Cand s p cap l.val d.val) (hd : ¬d = 0#usize) (hcap : cap ≤ 258) : l.val ≤ 258 := C12566!
theorem Cand.dist_le {s : Slice Std.U8} {p cap l d : Nat} (hc : Cand s p cap l d) :
    d ≤ 32768 := C12567!
theorem FoundAt.none (s : Slice Std.U8) (p : Nat) : FoundAt s p (0#usize).val (0#usize).val :=
  Or.inl (by simp)
theorem FoundAt.real {s : Slice Std.U8} {p l d : Nat} (hf : FoundAt s p l d) (h3 : 3 ≤ l) :
    MatchAt s p l d := C12568!
theorem copyN_take_prefix (acc : List Nat) (d : Nat) :
    ∀ n, (copyN acc d n).take acc.length = acc := C12518!
theorem foldlM_emit_length : ∀ (ts : List Nat) (init acc : List Nat),
    ts.foldlM emit init = some acc → init.length + ts.length ≤ acc.length := C12519!
theorem decode_length_le {ts acc : List Nat} (h : decode ts = some acc) :
    ts.length ≤ acc.length := C12520!
theorem decode_pop_lit {ts : List Nat} {t : Nat} {inp : List Nat} {p : Nat}
    (hp : p ≤ inp.length) (hd : decode (ts ++ [t]) = some (inp.take p)) (ht : t < 256) :
    1 ≤ p ∧ decode ts = some (inp.take (p - 1)) := C12521!
theorem decode_pop_match {ts : List Nat} {t : Nat} {inp : List Nat} {p : Nat}
    (hp : p ≤ inp.length) (hd : decode (ts ++ [t]) = some (inp.take p)) (ht : 256 ≤ t) :
    tokLen t ≤ p ∧ decode ts = some (inp.take (p - tokLen t)) := C12522!
theorem toks_pop (out : Slice Std.U32) (nt : Nat) (h0 : 0 < nt) (hle : nt ≤ out.length) :
    toks out nt = toks out (nt - 1) ++ [(out.val[nt - 1]!).val] := C12523!
theorem toks_length (out : Slice Std.U32) (nt : Nat) (h : nt ≤ out.length) :
    (toks out nt).length = nt := C12524!
def Dec (s : Slice Std.U8) (out : Slice Std.U32) (nt p : Nat) : Prop :=
  p ≤ s.length ∧ nt ≤ p ∧ s.length ≤ out.length ∧
    decode (toks out nt) = some ((bytes s).take p)
theorem Dec.init (input : Slice Std.U8) (out : Slice Std.U32) (h : input.length ≤ out.length) :
    Dec input out (0#usize).val (0#usize).val :=
  ⟨by simp, by simp, h, by simp [toks, LZ77.decode]⟩
theorem Dec.lit {s : Slice Std.U8} {out : Slice Std.U32} {nt p : Nat} (h : Dec s out nt p)
    (hp : p < s.length) (ntU : Std.Usize) (hnt : ntU.val = nt) (v : Std.U32)
    (hv : v.val = (s.val[p]!).val) :
    Dec s (out.set ntU v) (nt + 1) (p + 1) := C12570!
theorem Dec.match {s : Slice Std.U8} {out : Slice Std.U32} {nt p l d : Nat} (h : Dec s out nt p)
    (hm : MatchAt s p l d) (ntU : Std.Usize) (hnt : ntU.val = nt) (v : Std.U32)
    (hv : v.val = LZ77.mkMatch d l) :
    Dec s (out.set ntU v) (nt + 1) (p + l) := C12571!
theorem Dec.pop_lit {s : Slice Std.U8} {out : Slice Std.U32} {nt p : Nat} (h : Dec s out nt p)
    (h0 : 0 < nt) (hle : nt ≤ out.length) (ht : (out.val[nt - 1]!).val < 256) :
    1 ≤ p ∧ Dec s out (nt - 1) (p - 1) := C12525!
theorem Dec.pop_match {s : Slice Std.U8} {out : Slice Std.U32} {nt p : Nat} (h : Dec s out nt p)
    (h0 : 0 < nt) (hle : nt ≤ out.length) (ht : 256 ≤ (out.val[nt - 1]!).val) :
    tokLen (out.val[nt - 1]!).val ≤ p ∧
      Dec s out (nt - 1) (p - tokLen (out.val[nt - 1]!).val) := C12526!
theorem Dec.done {s : Slice Std.U8} {out : Slice Std.U32} {nt p : Nat} (h : Dec s out nt p)
    (hp : s.length ≤ p) : nt ≤ s.length ∧ LZ77.Valid (bytes s) (toks out nt) := C12572!
theorem Dec.lit_step {s : Slice Std.U8} {out out1 : Slice Std.U32} {ntU nt1 pU : Std.Usize}
    {b : Std.U8} {v : Std.U32} (h : Dec s out ntU.val pU.val) (hp : pU.val < s.val.length)
    (hb : b = s.val[pU.val]) (hv : v = UScalar.cast .U32 b) (hout1 : out1 = out.set ntU v)
    (hnt1 : nt1.val = ntU.val + 1) :
    nt1.val = ntU.val + 1 ∧ out1.length = out.length ∧ Dec s out1 nt1.val (pU.val + 1) := C12573!
theorem Dec.match_step {s : Slice Std.U8} {out out1 : Slice Std.U32} {ntU nt1 pU dU lU e : Std.Usize}
    {v : Std.U32} (h : Dec s out ntU.val pU.val) (hm : MatchAt s pU.val lU.val dU.val)
    (hout1 : out1 = out.set ntU v) (hv : v.val = LZ77.mkMatch dU.val lU.val)
    (hnt1 : nt1.val = ntU.val + 1) (he : e.val = pU.val + lU.val) :
    nt1.val = ntU.val + 1 ∧ e.val = pU.val + lU.val ∧ out1.length = out.length ∧
      Dec s out1 nt1.val e.val := C12575!
theorem MatchAt.back_lit {s : Slice Std.U8} {p l d : Nat} (h : MatchAt s p l d) (hl : l < 258)
    (hdp : d < p) (heq : s.val[p - 1]! = s.val[p - 1 - d]!) : MatchAt s (p - 1) (l + 1) d := C12577!
theorem MatchAt.back_match {s : Slice Std.U8} {p l d w : Nat} (h : MatchAt s p l d)
    (hlw : l + w ≤ 258) (hw : w ≤ p) (hdw : d ≤ p - w) (hmw : Matches s (p - w - d) (p - w) w) :
    MatchAt s (p - w) (l + w) d := C12578!
def BackInv (input : Slice Std.U8) (out : Slice Std.U32) (d E P0 : Nat) (nt p l : Nat) : Prop :=
  Dec input out nt p ∧ MatchAt input p l d ∧ p + l = E ∧ p ≤ P0
theorem BackInv.lit {input : Slice Std.U8} {out : Slice Std.U32} {d E P0 : Nat}
    {nt p l i1 i2 i4 l1 : Std.Usize} {t : Std.U32} {x y : Std.U8}
    (h : BackInv input out d E P0 nt.val p.val l.val)
    (hi1 : i1.val = nt.val - 1) (hntl : nt.val ≤ out.length) (hnt0 : 1 ≤ nt.val)
    (hi1l : i1.val < out.val.length) (ht : t = out.val[i1.val]) (ht256 : t < 256#u32)
    (hi2 : i2.val = p.val - 1) (hi2l : i2.val < input.val.length) (hx : x = input.val[i2.val])
    (hxy : x = y) (hi4 : i4.val = i2.val - d) (hi4l : i4.val < input.val.length)
    (hy : y = input.val[i4.val]) (hl : l.val < 258) (hdp : d < p.val)
    (hl1 : l1.val = l.val + 1) :
    BackInv input out d E P0 i1.val i2.val l1.val := C12579!
theorem BackInv.match {input : Slice Std.U8} {out : Slice Std.U32} {d E P0 : Nat}
    {nt p l i1 w i9 i10 i11 i12 : Std.Usize} {t : Std.U32}
    (h : BackInv input out d E P0 nt.val p.val l.val)
    (hi1 : i1.val = nt.val - 1) (hntl : nt.val ≤ out.length) (hnt0 : 1 ≤ nt.val)
    (hi1l : i1.val < out.val.length) (ht : t = out.val[i1.val])
    (hsame : i12.val = 1 → Matches input i11.val i10.val w.val) (hi12 : i12 = 1#usize)
    (ht24 : 16777216 ≤ t.val) (hwv : w.val = (t.val - 16777216) % 256 + 3)
    (hi9 : i9.val = l.val + w.val) (hi9' : i9.val ≤ 258) (hi10 : i10.val = p.val - w.val)
    (hwp : w.val ≤ p.val) (hdw : d ≤ i10.val) (hi11 : i11.val = i10.val - d) :
    BackInv input out d E P0 i1.val i10.val i9.val := C12580!
def LazyInv (input : Slice Std.U8) (L lim : Nat) (out : Slice Std.U32) (nt p : Nat)
    {N : Std.Usize} (head : Array Std.U32 N) (ins l d : Nat) : Prop :=
  Dec input out nt p ∧ out.length = L ∧ MatchAt input p l d ∧ HeadBound head (p + 1) ∧
    p < lim ∧ ins ≤ p + 2
theorem LazyInv.accept {input : Slice Std.U8} {L lim p' B : Nat} {out1 : Slice Std.U32}
    {nt1 i ins1 l1 d1 minl : Std.Usize} {N : Std.Usize} {head1 : Array Std.U32 N}
    (hdec : Dec input out1 nt1.val p') (hi : i.val = p') (hlen : out1.length = L)
    (hf : FoundAt input i.val l1.val d1.val) (hl1 : minl.val ≤ l1.val) (hminl : 3 ≤ minl.val)
    (hB : HeadBound head1 B) (hBi : B ≤ i.val + 1) (hilim : i.val < lim)
    (hins : ins1.val ≤ i.val + 2) :
    LazyInv input L lim out1 nt1.val i.val head1 ins1.val l1.val d1.val := C12581!
theorem LazyInv.reject {input : Slice Std.U8} {L lim : Nat} {out : Slice Std.U32}
    {nt p ins ins1 l d B : Nat} {N : Std.Usize} {head head1 : Array Std.U32 N}
    (h : LazyInv input L lim out nt p head ins l d) (hB : HeadBound head1 B) (hBp : B ≤ p + 1)
    (hins1 : ins1 ≤ p + 2) : LazyInv input L lim out nt p head1 ins1 l d := C12582!
theorem numBits_ge : 32 ≤ System.Platform.numBits := C12527!
def MainInv (input : Slice Std.U8) (L : Nat) (out : Slice Std.U32) (nt p : Nat)
    {N : Std.Usize} (head : Array Std.U32 N) (miss : Nat) : Prop :=
  Dec input out nt p ∧ out.length = L ∧ HeadBound head p ∧ miss ≤ p
theorem MainInv.mk' {input : Slice Std.U8} {L : Nat} {out : Slice Std.U32} {nt p m B : Nat}
    {N : Std.Usize} {head : Array Std.U32 N} (hdec : Dec input out nt p) (hlen : out.length = L)
    (hB : HeadBound head B) (hBp : B ≤ p) (hm : m ≤ p) : MainInv input L out nt p head m :=
  ⟨hdec, hlen, HeadBound.mono hB hBp, hm⟩
def CntBound (cnt : Array Std.U32 256#usize) (T : Nat) : Prop :=
  ∀ j : Nat, j < 256 → (cnt.val[j]!).val ≤ T
theorem CntBound.init : CntBound (Std.Array.repeat 256#usize 0#u32) 0 := C1251!
theorem CntBound.get {cnt : Array Std.U32 256#usize} {T : Nat} (h : CntBound cnt T)
    (a : Std.Usize) (x : Std.U32) (ha : a.val < cnt.val.length) (hx : x = cnt.val[a.val]) :
    x.val ≤ T := C1252!
@[local step]
theorem cnt_index_spec (cnt : Array Std.U32 256#usize) (T : Nat) (h : CntBound cnt T)
    (i : Std.Usize) (hi : i.val < 256) :
    Std.Array.index_usize cnt i ⦃ fun x => x = cnt.val[i.val]! ∧ x.val ≤ T ⦄ := C1253!
theorem CntBound.update {cnt : Array Std.U32 256#usize} {T : Nat} (h : CntBound cnt T)
    (a : Std.Usize) (v : Std.U32) (hv : v.val ≤ T + 1) : CntBound (cnt.set a v) (T + 1) := C1254!
theorem CntBound.step {cnt a : Array Std.U32 256#usize} {T : Nat} {x : Std.Usize}
    {v tot1 : Std.U32} (hc : CntBound cnt T) (ha : a = cnt.set x v) (hv : v.val ≤ T + 1)
    (ht1 : tot1.val = T + 1) : CntBound a tot1.val := C1255!
theorem CntBound.mono {cnt : Array Std.U32 256#usize} {T T' : Nat} (h : CntBound cnt T)
    (hT : T ≤ T') : CntBound cnt T' := fun j hj => le_trans (h j hj) hT
@[local step]
theorem lift_spec {α : Type} (x : α) : lift x ⦃ fun y => y = x ⦄ := by
  simp [lift]
theorem Dec.cast {s : Slice Std.U8} {out : Slice Std.U32} {nt p p' : Nat} (h : Dec s out nt p)
    (hp : p = p') : Dec s out nt p' := hp ▸ h
theorem Matches.xor_lz {s : Slice Std.U8} {c p m : Std.Usize} {cw y x : Std.U64}
    {lz q : Std.U32} (hcw : cw.val = word8 s c.val) (hy : y.val = word8 s p.val)
    (hx : x.val = (cw ^^^ y).val) (hx0 : (x != 0#u64) = true)
    (hlz : lz = core.num.U64.leading_zeros x) (hq : q.val = lz.val / 8)
    (hm : m = UScalar.cast .Usize q) : Matches s c.val p.val m.val ∧ m.val < 8 := C12594!
theorem Matches.xor_zero {s : Slice Std.U8} {c p : Std.Usize} {cw y x : Std.U64}
    (hcw : cw.val = word8 s c.val) (hy : y.val = word8 s p.val)
    (hx : x.val = (cw ^^^ y).val) (hx0 : ¬(x != 0#u64) = true) :
    Matches s c.val p.val (8#usize).val := C12595!
theorem FoundAt.of_matches {s : Slice Std.U8} {p c d i l : Std.Usize} (hc : c.val ≤ p.val)
    (hd : d = core.num.Usize.wrapping_sub p c) (hi : i = core.num.Usize.wrapping_sub d 1#usize)
    (hlt : i < 32768#usize) (hl : l.val ≤ 258) (hpl : p.val + l.val ≤ s.length)
    (hm : Matches s c.val p.val l.val) :
    FoundAt s p.val l.val d.val ∧ l.val ≤ 258 ∧ d.val ≤ 32768 := C12596!
theorem FoundAt.none' (s : Slice Std.U8) (p : Nat) :
    FoundAt s p (0#usize).val (0#usize).val ∧ (0#usize).val ≤ 258 ∧ (0#usize).val ≤ 32768 :=
  ⟨FoundAt.none s p, by simp, by simp⟩
def LazyInv1 (input : Slice Std.U8) (lim P0 : Nat) (p : Nat) {N : Std.Usize}
    (head : Array Std.U32 N) (ps pc pw l d ins : Nat) : Prop :=
  MatchAt input p l d ∧ HeadBound head (p + 1) ∧ p < lim ∧ ins ≤ p + 2 ∧ ps < N.val ∧
    pc ≤ p + 1 ∧ pw = word8 input pc ∧ P0 ≤ p
theorem LazyInv1.accept {input : Slice Std.U8} {lim P0 B : Nat}
    {i ins1 l1 d1 ps pc : Std.Usize} {pw : Std.U64} {N : Std.Usize} {head1 : Array Std.U32 N}
    (hf : FoundAt input i.val l1.val d1.val) (hl1 : 3 ≤ l1.val)
    (hB : HeadBound head1 B) (hBi : B ≤ i.val + 1) (hilim : i.val < lim)
    (hins : ins1.val ≤ i.val + 2) (hps : ps.val < N.val) (hpc : pc.val ≤ i.val + 1)
    (hpw : pw.val = word8 input pc.val) (hP : P0 ≤ i.val) :
    LazyInv1 input lim P0 i.val head1 ps.val pc.val pw.val l1.val d1.val ins1.val :=
  ⟨FoundAt.real hf hl1, HeadBound.mono hB hBi, hilim, hins, hps, hpc, hpw, hP⟩
theorem LazyInv1.reject {input : Slice Std.U8} {lim P0 : Nat}
    {p ps pc pw l d ins B ps1 pc1 pw1 ins1 : Nat} {N : Std.Usize}
    {head head1 : Array Std.U32 N}
    (h : LazyInv1 input lim P0 p head ps pc pw l d ins) (hB : HeadBound head1 B)
    (hBp : B ≤ p + 1) (hins1 : ins1 ≤ p + 2) (hps : ps1 < N.val) (hpc : pc1 ≤ p + 1)
    (hpw : pw1 = word8 input pc1) :
    LazyInv1 input lim P0 p head1 ps1 pc1 pw1 l d ins1 := C12597!
def MainInv1 (input : Slice Std.U8) (L : Nat) (out : Slice Std.U32) (nt ls p : Nat)
    {N : Std.Usize} (head : Array Std.U32 N) (miss ps pc pw : Nat) : Prop :=
  Dec input out nt ls ∧ out.length = L ∧ ls ≤ p ∧ HeadBound head p ∧ miss ≤ p ∧ ps < N.val ∧
    pc ≤ p ∧ pw = word8 input pc
theorem MainInv1.mk' {input : Slice Std.U8} {L : Nat} {out : Slice Std.U32}
    {nt ls ls' p m B ps pc pw : Nat} {N : Std.Usize} {head : Array Std.U32 N}
    (hdec : Dec input out nt ls') (hls : ls' = ls) (hlen : out.length = L) (hlsp : ls ≤ p)
    (hB : HeadBound head B) (hBp : B ≤ p) (hm : m ≤ p) (hps : ps < N.val) (hpc : pc ≤ p)
    (hpw : pw = word8 input pc) : MainInv1 input L out nt ls p head m ps pc pw := by
  subst hls
  exact ⟨hdec, hlen, hlsp, HeadBound.mono hB hBp, hm, hps, hpc, hpw⟩
end PX
namespace PC
open Aeneas Aeneas.Std Result ControlFlow
set_option maxRecDepth 8192
set_option maxHeartbeats 4000000
set_option linter.unusedVariables false
open LZ77 (toks bytes bytes_length bytes_getElem! toks_update bytes_congr
  Matches Found emit_lit emit_match ite_ok)
open LZ77 (decode emit copyN tokLen tokDist MATCH_BASE TOK_LIMIT decode_snoc copyN_length)
section TinyPath
set_option linter.unusedTactic false
set_option linter.unreachableTactic false
@[local step]
theorem tp_lift_spec {α : Type} (x : α) : lift x ⦃ fun y => y = x ⦄ := by
  simp [lift, WP.spec_ok]
theorem tp_numBits_ge : 32 ≤ System.Platform.numBits := by
  cases System.Platform.numBits_eq <;> simp [*]
@[local scalar_tac System.Platform.numBits]
theorem tp_numBits_ge' : 32 ≤ System.Platform.numBits := tp_numBits_ge
end TinyPath
@[irreducible] def word8 (input : Slice Std.U8) (p : Nat) : Nat :=
  (input.val[p]!).val * 2^56 + (input.val[p + 1]!).val * 2^48 + (input.val[p + 2]!).val * 2^40
    + (input.val[p + 3]!).val * 2^32 + (input.val[p + 4]!).val * 2^24
    + (input.val[p + 5]!).val * 2^16 + (input.val[p + 6]!).val * 2^8 + (input.val[p + 7]!).val
theorem u8_lt (x : Std.U8) : x.val < 256 := by scalar_tac
theorem word8_digit (input : Slice Std.U8) (p k : Nat) (hk : k < 8) :
    (input.val[p + k]!).val = word8 input p / 256 ^ (7 - k) % 256 := C12530!
theorem word8_prefix (input : Slice Std.U8) (a b d : Nat) (hd : d ≤ 8)
    (h : word8 input a / 2 ^ (64 - 8 * d) = word8 input b / 2 ^ (64 - 8 * d)) :
    ∀ k, k < d → input.val[b + k]! = input.val[a + k]! := C12531!
theorem Matches.add_prefix {input : Slice Std.U8} {a b l d : Nat} (h : Matches input a b l)
    (hd : d ≤ 8)
    (hw : word8 input (a + l) / 2 ^ (64 - 8 * d) = word8 input (b + l) / 2 ^ (64 - 8 * d)) :
    Matches input a b (l + d) := C12532!
theorem or_eq_add_of_mod {x t : Nat} (m : Nat) (hx : x % 2 ^ m = 0) (ht : t < 2 ^ m) :
    x ||| t = x + t := C12533!
theorem shl_byte {x : Nat} (k : Nat) (hx : x < 256) (hk : k ≤ 56) :
    x <<< k % U64.size = x * 2 ^ k := C12534!
theorem be8_nat {a b c d e f g h : Nat} (ha : a < 256) (hb : b < 256) (hc : c < 256)
    (hd : d < 256) (he : e < 256) (hf : f < 256) (hg : g < 256) (hh : h < 256) :
    (a <<< 56 % U64.size ||| b <<< 48 % U64.size ||| c <<< 40 % U64.size |||
      d <<< 32 % U64.size ||| e <<< 24 % U64.size ||| f <<< 16 % U64.size |||
      g <<< 8 % U64.size ||| h) =
    a * 2^56 + b * 2^48 + c * 2^40 + d * 2^32 + e * 2^24 + f * 2^16 + g * 2^8 + h := C12535!
@[local step]
theorem be8_spec (s : Slice Std.U8) (i : Std.Usize) (h : i.val + 8 ≤ s.length) :
    slot.pc_be8 s i ⦃ fun v => v.val = word8 s i.val ⦄ := C12536! slot.pc_be8
theorem nat_xor_eq_zero {a b : Nat} (h : a ^^^ b = 0) : a = b := C12537!
theorem div_eq_of_xor_lt {x y m : Nat} (hz : x ^^^ y < 2 ^ m) : x / 2 ^ m = y / 2 ^ m := C12538!
theorem lt_pow_leadingZeros (z : BitVec 64) :
    z.toNat < 2 ^ (64 - 8 * (BitVec.leadingZeros z / 8)) := C12539!
theorem leadingZeros_lt_of_ne (z : BitVec 64) (h : z ≠ 0) : BitVec.leadingZeros z < 64 := C12540!
@[local step]
theorem lz_spec (x : Std.U64) :
    lift (core.num.U64.leading_zeros x) ⦃ fun r => r = core.num.U64.leading_zeros x ∧ r.val ≤ 64 ⦄ := C12541!
theorem lz_val (x : Std.U64) :
    (core.num.U64.leading_zeros x).val = BitVec.leadingZeros x.bv := C12542!
theorem Matches.word_lz {input : Slice Std.U8} {a b k : Nat} {pa pb r k1 : Std.Usize}
    {x y z : Std.U64} {lz q : Std.U32}
    (h : Matches input a b k) (hpa : pa.val = a + k) (hpb : pb.val = b + k)
    (hx : x.val = word8 input pa.val) (hy : y.val = word8 input pb.val)
    (hz : z.val = (x ^^^ y).val) (hz0 : ¬z = 0#u64) (hlz : lz = core.num.U64.leading_zeros z)
    (hq : q.val = lz.val / 8) (hr : r = UScalar.cast .Usize q) (hk1 : k1.val = k + r.val) :
    Matches input a b k1.val ∧ k1.val < k + 8 := C12543!
theorem Matches.word_zero {input : Slice Std.U8} {a b k : Nat} {pa pb k1 : Std.Usize}
    {x y z : Std.U64}
    (h : Matches input a b k) (hpa : pa.val = a + k) (hpb : pb.val = b + k)
    (hx : x.val = word8 input pa.val) (hy : y.val = word8 input pb.val)
    (hz : z.val = (x ^^^ y).val) (hz0 : z = 0#u64) (hk1 : k1.val = k + 8) :
    Matches input a b k1.val := C12544!
theorem Matches.byte' {input : Slice Std.U8} {a b l : Nat} {pa pb l1 : Std.Usize}
    {x y : Std.U8} (h : Matches input a b l) (hpa : pa.val = a + l) (hpb : pb.val = b + l)
    (hpa' : pa.val < input.val.length) (hpb' : pb.val < input.val.length)
    (hx : x = input.val[pa.val]) (hy : y = input.val[pb.val]) (hxy : x = y)
    (hl1 : l1.val = l + 1) : Matches input a b l1.val := C12545!
theorem wadd_val {x y z : Std.Usize} (hz : z = core.num.Usize.wrapping_add x y)
    (hb : x.val + y.val ≤ Std.Usize.max) : z.val = x.val + y.val := by
  have hlt : x.val + y.val < Usize.size := by scalar_tac
  rw [hz, core.num.Usize.wrapping_add_val_eq, UScalar.size_UScalarTyUsize, Nat.mod_eq_of_lt hlt]
theorem wadd_le {x y z : Std.Usize} {m n : Nat} (hz : z = core.num.Usize.wrapping_add x y)
    (h : x.val + y.val + m ≤ n) (hn : n ≤ Std.Usize.max) : z.val + m ≤ n := by
  rw [wadd_val hz (by omega)]; exact h
@[local step]
theorem xor8_spec (s : Slice Std.U8) (a b : Std.Usize) (ha : a.val + 8 ≤ s.length)
    (hb : b.val + 8 ≤ s.length) :
    slot.pc_xor8 s a b ⦃ fun v => v.val = word8 s a.val ^^^ word8 s b.val ⦄ := by
  rw [slot.pc_xor8]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  step*
  simp only [← getElem!_pos] at *
  simp_all only [UScalar.val_or, UScalar.val_xor, U8.cast_U64_val_eq]
  rw [be8_nat (u8_lt _) (u8_lt _) (u8_lt _) (u8_lt _) (u8_lt _) (u8_lt _) (u8_lt _) (u8_lt _),
    be8_nat (u8_lt _) (u8_lt _) (u8_lt _) (u8_lt _) (u8_lt _) (u8_lt _) (u8_lt _) (u8_lt _)]
  simp only [word8]
theorem Matches.lz_any {input : Slice Std.U8} {a b k : Nat} {r k1 : Std.Usize} {z : Std.U64}
    {lz q : Std.U32} (h : Matches input a b k)
    (hz : z.val = word8 input (a + k) ^^^ word8 input (b + k))
    (hlz : lz = core.num.U64.leading_zeros z) (hq : q.val = lz.val / 8)
    (hr : r = UScalar.cast .Usize q) (hk1 : k1.val = k + r.val) :
    Matches input a b k1.val ∧ k1.val ≤ k + 8 := by
  have hle : BitVec.leadingZeros z.bv ≤ 64 := by unfold BitVec.leadingZeros; split <;> omega
  have hrv : r.val = BitVec.leadingZeros z.bv / 8 := by
    rw [hr, U32.cast_Usize_val_eq, hq, hlz, lz_val]
  refine ⟨?_, by omega⟩
  rw [hk1, hrv]
  apply Matches.add_prefix h (by omega)
  apply div_eq_of_xor_lt
  rw [← hz]
  exact lt_pow_leadingZeros z.bv
theorem Matches.xz {input : Slice Std.U8} {a b : Nat} {z : Std.U64}
    (hz : z.val = word8 input a ^^^ word8 input b) (hz0 : z = 0#u64) :
    Matches input a b 8 := by
  have hv : word8 input a ^^^ word8 input b = 0 := by rw [← hz, hz0]; rfl
  have hab := nat_xor_eq_zero hv
  have := Matches.add_prefix (LZ77.Matches.zero input a b) (le_refl 8)
    (by simp only [Nat.add_zero]; rw [hab])
  simpa using this
theorem xval_of {x cw y : Std.U64} {A B : Nat} (hx : x.val = (cw ^^^ y).val) (hcw : cw.val = A)
    (hy : y.val = B) : x.val = A ^^^ B := by
  rw [hx, UScalar.val_xor, hcw, hy]
theorem Matches.xw_step {input : Slice Std.U8} {a b k pa pb k1 r : Std.Usize} {z : Std.U64}
    {lz q : Std.U32} (h : Matches input a.val b.val k.val)
    (hpa : pa = core.num.Usize.wrapping_add a k) (hpb : pb = core.num.Usize.wrapping_add b k)
    (hab : a.val + k.val + 8 ≤ input.length ∧ b.val + k.val + 8 ≤ input.length)
    (hz : z.val = word8 input pa.val ^^^ word8 input pb.val)
    (hlz : lz = core.num.U64.leading_zeros z) (hq : q.val = lz.val / 8)
    (hr : r = UScalar.cast .Usize q) (hk1 : k1.val = k.val + r.val) :
    Matches input a.val b.val k1.val ∧ k1.val ≤ k.val + 8 := by
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  rw [wadd_val hpa (by omega), wadd_val hpb (by omega)] at hz
  exact Matches.lz_any h hz hlz hq hr hk1
theorem Matches.xw_zero {input : Slice Std.U8} {a b k pa pb k1 : Std.Usize} {z : Std.U64}
    (h : Matches input a.val b.val k.val)
    (hpa : pa = core.num.Usize.wrapping_add a k) (hpb : pb = core.num.Usize.wrapping_add b k)
    (hab : a.val + k.val + 8 ≤ input.length ∧ b.val + k.val + 8 ≤ input.length)
    (hz : z.val = word8 input pa.val ^^^ word8 input pb.val) (hz0 : z = 0#u64)
    (hk1 : k1.val = k.val + 8) : Matches input a.val b.val k1.val := by
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  rw [wadd_val hpa (by omega), wadd_val hpb (by omega)] at hz
  have h8 := Matches.xz hz hz0
  rw [hk1]
  intro i hi
  by_cases hik : i < k.val
  · exact h i hik
  · have := h8 (i - k.val) (by omega)
    rw [show b.val + k.val + (i - k.val) = b.val + i by omega,
      show a.val + k.val + (i - k.val) = a.val + i by omega] at this
    exact this
set_option hygiene false in
local notation "C12598!" q0__:max q1__:max => (by
  rw [q0__]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  apply Std.loop.spec_decr_nat
    (measure := fun r => cap.val - r.1.val + r.2.val)
    (inv := fun r => r.1.val ≤ cap.val ∧ Matches s a.val b.val r.1.val)
  · rintro ⟨k, run⟩ ⟨hk, hm⟩
    simp only at hk hm
    simp only [q1__]
    step*
    all_goals first
      | scalar_tac
      | exact ⟨hk, hm⟩
      | exact wadd_le (by assumption) (by scalar_tac) (by scalar_tac)
      | (refine ⟨by scalar_tac, Matches.xw_zero hm (by assumption) (by assumption) (by scalar_tac)
          (by assumption) (by assumption) (by scalar_tac), by scalar_tac⟩)
      | (have hw := Matches.xw_step hm (by assumption) (by assumption) (by scalar_tac)
          (by assumption) (by assumption) (by assumption) (by assumption) (by assumption)
         refine ⟨by scalar_tac, hw.1, by scalar_tac⟩)
  · exact ⟨hk, hm⟩)
theorem common_loop0_spec (s : Slice Std.U8) (a b cap k : Std.Usize) (run : Std.U32)
    (ha : a.val + cap.val ≤ s.length) (hb : b.val + cap.val ≤ s.length) (hcap : cap.val ≤ 258)
    (hk : k.val ≤ cap.val) (hm : Matches s a.val b.val k.val) :
    slot.pc_common_loop0 s a b cap k run ⦃ fun r =>
      r.1.val ≤ cap.val ∧ Matches s a.val b.val r.1.val ⦄ := C12598! slot.pc_common_loop0 slot.pc_common_loop0.body
theorem common_loop1_spec (s : Slice Std.U8) (a b cap k : Std.Usize) (run : Std.U32)
    (ha : a.val + cap.val ≤ s.length) (hb : b.val + cap.val ≤ s.length)
    (hk : k.val ≤ cap.val) (hm : Matches s a.val b.val k.val) :
    slot.pc_common_loop1 s a b cap k run ⦃ fun r =>
      r.val ≤ cap.val ∧ Matches s a.val b.val r.val ⦄ := C12547! slot.pc_common_loop1 slot.pc_common_loop1.body
@[local step]
theorem common_spec (s : Slice Std.U8) (a b cap : Std.Usize)
    (ha : a.val + cap.val ≤ s.length) (hb : b.val + cap.val ≤ s.length) (hcap : cap.val ≤ 258) :
    slot.pc_common s a b cap ⦃ fun l => l.val ≤ cap.val ∧ Matches s a.val b.val l.val ⦄ := C12548! slot.pc_common
theorem Matches.word_eq {input : Slice Std.U8} {a b k : Nat} {pa pb k1 : Std.Usize}
    {x y : Std.U64}
    (h : Matches input a b k) (hpa : pa.val = a + k) (hpb : pb.val = b + k)
    (hx : x.val = word8 input pa.val) (hy : y.val = word8 input pb.val)
    (hxy : x = y) (hk1 : k1.val = k + 8) :
    Matches input a b k1.val := C12549!
theorem same_loop0_spec (s : Slice Std.U8) (a b len k ok : Std.Usize)
    (ha : a.val + len.val ≤ s.length) (hb : b.val + len.val ≤ s.length) (hlen : len.val ≤ 258)
    (hk : k.val ≤ len.val) (hm : Matches s a.val b.val k.val) :
    slot.pc_same_loop0 s a b len k ok ⦃ fun r =>
      r.1.val ≤ len.val ∧ Matches s a.val b.val r.1.val ∧ (r.2.val = 1 → len.val < r.1.val + 8) ⦄ := C12550! slot.pc_same_loop0 slot.pc_same_loop0.body
@[local step]
theorem same_loop1_spec (s : Slice Std.U8) (a b len k ok : Std.Usize)
    (ha : a.val + len.val ≤ s.length) (hb : b.val + len.val ≤ s.length)
    (hk : k.val ≤ len.val) (hm : Matches s a.val b.val k.val) :
    slot.pc_same_loop1 s a b len k ok ⦃ fun r => r.val = 1 → Matches s a.val b.val len.val ⦄ := C12551! slot.pc_same_loop1 slot.pc_same_loop1.body
@[local step]
theorem same_loop2_spec (s : Slice Std.U8) (a b len k ok : Std.Usize)
    (ha : a.val + len.val ≤ s.length) (hb : b.val + len.val ≤ s.length)
    (hk : k.val ≤ len.val) (hm : Matches s a.val b.val k.val) :
    slot.pc_same_loop2 s a b len k ok ⦃ fun r => r.val = 1 → Matches s a.val b.val len.val ⦄ := C12551! slot.pc_same_loop2 slot.pc_same_loop2.body
theorem Matches.mask {input : Slice Std.U8} {a b k len : Nat} {pa pb : Std.Usize}
    {x y z w : Std.U64} {sh : Std.U32}
    (h : Matches input a b k) (hpa : pa.val = a + k) (hpb : pb.val = b + k)
    (hx : x.val = word8 input pa.val) (hy : y.val = word8 input pb.val)
    (hz : z.val = (x ^^^ y).val) (hw : w.val = z.val >>> sh.val) (hw0 : ¬(w != 0#u64) = true)
    (hsh : sh.val = 64 - 8 * (len - k)) (hk : k < len) (hlen : len < k + 8) :
    Matches input a b len := C12552!
@[local step]
theorem same_spec (s : Slice Std.U8) (a b len : Std.Usize)
    (ha : a.val + len.val ≤ s.length) (hb : b.val + len.val ≤ s.length) (hlen : len.val ≤ 258)
    (ha8 : a.val + len.val + 7 ≤ Std.Usize.max) (hb8 : b.val + len.val + 7 ≤ Std.Usize.max) :
    slot.pc_same s a b len ⦃ fun r => r.val = 1 → Matches s a.val b.val len.val ⦄ := C12553! slot.pc_same
theorem lz32_le (x : Std.U32) (k : Nat) (hk : k < 32) (hx : 2 ^ k ≤ x.val) :
    (core.num.U32.leading_zeros x).val ≤ 31 - k := C12554!
@[local step]
theorem lz32_spec (x : Std.U32) :
    lift (core.num.U32.leading_zeros x) ⦃ fun r => r = core.num.U32.leading_zeros x ∧
      (4 ≤ x.val → r.val ≤ 29) ∧ (8 ≤ x.val → r.val ≤ 28) ⦄ := C12555!
@[local step]
theorem hcast_I32_spec {ty : UScalarTy} (x : UScalar ty) (h : x.val ≤ 2147483647) :
    lift (UScalar.hcast .I32 x) ⦃ fun y => y.val = x.val ⦄ :=
  UScalar.hcast_inBounds_spec .I32 x (by simp [I32.max_def, I32.numBits]; omega)
theorem GBASE_bound : -1000000000 ≤ slot.pc_GBASE.val ∧ slot.pc_GBASE.val ≤ 1000000000 := by
  unfold slot.pc_GBASE
  simp
@[local step]
theorem gain_spec (l d : Std.Usize) (hl : l.val ≤ 258) (hd : d.val ≤ 32768) :
    slot.pc_gain l d ⦃ fun _ => True ⦄ := by
  rw [slot.pc_gain]
  have ⟨hG0, hG1⟩ := GBASE_bound
  repeat' (split <;> step*)
def HeadBound {N : Std.Usize} (head : Array Std.U32 N) (B : Nat) : Prop :=
  ∀ j : Nat, j < head.val.length → (head.val[j]!).val ≤ B
theorem HeadBound.mono {N : Std.Usize} {head : Array Std.U32 N} {B B' : Nat}
    (h : HeadBound head B) (hB : B ≤ B') : HeadBound head B' := fun j hj => le_trans (h j hj) hB
theorem HeadBound.init (N : Std.Usize) : HeadBound (Std.Array.repeat N 0#u32) 0 := C12556!
theorem HeadBound.set {N : Std.Usize} {head : Array Std.U32 N} {B : Nat} (h : HeadBound head B)
    (a : Std.Usize) (v : Std.U32) (hv : v.val ≤ B) : HeadBound (head.set a v) B := C12557!
theorem HeadBound.update {N : Std.Usize} {head head1 : Array Std.U32 N} {B : Nat}
    {a i : Std.Usize} {v : Std.U32} (h : HeadBound head B) (hv : v = UScalar.cast .U32 i)
    (hi : i.val ≤ B) (h1 : head1 = head.set a v) : HeadBound head1 B := C12558!
theorem HeadBound.get {N : Std.Usize} {head : Array Std.U32 N} {B : Nat} (h : HeadBound head B)
    (a : Std.Usize) (x : Std.U32) (ha : a.val < head.val.length) (hx : x = head.val[a.val]) :
    x.val ≤ B := C12559!
theorem cast_usize_le {x : Std.U32} {y : Std.Usize} {B : Nat} (h : y = UScalar.cast .Usize x)
    (hx : x.val ≤ B) : y.val ≤ B := by
  rw [h, U32.cast_Usize_val_eq]; exact hx
@[local step]
theorem be4_spec (s : Slice Std.U8) (i : Std.Usize) (hi : i.val + 4 ≤ Std.Usize.max) :
    slot.pc_be4 s i ⦃ fun _ => True ⦄ := by
  rw [slot.pc_be4]
  step*
@[local step]
theorem insert_spec (s : Slice Std.U8) {H W : Std.Usize} (head : Array Std.U32 H)
    (prev : Array Std.U32 W) (i : Std.Usize) (mask : Std.U32) (B : Nat) (hB : HeadBound head B)
    (hi : i.val < B + 1) (hi4 : i.val + 4 ≤ Std.Usize.max) (hH : 0 < H.val) (hW : 0 < W.val) :
    slot.pc_insert s head prev i mask ⦃ fun r => r.1.val ≤ B ∧ HeadBound r.2.1 B ⦄ := C12560! slot.pc_insert
def Cand (s : Slice Std.U8) (p cap best bd : Nat) : Prop :=
  bd = 0 ∨ (1 ≤ bd ∧ bd ≤ 32768 ∧ bd ≤ p ∧ best ≤ cap ∧ Matches s (p - bd) p best)
theorem dist_of_wrapping {p c d i : Std.Usize} (hc : c.val ≤ p.val)
    (hd : d = core.num.Usize.wrapping_sub p c) (hi : i = core.num.Usize.wrapping_sub d 1#usize)
    (hlt : i < 32768#usize) : d.val = p.val - c.val ∧ 1 ≤ d.val ∧ d.val ≤ 32768 := C12561!
theorem Cand.of_common {s : Slice Std.U8} {p c d i l cap : Std.Usize} (hc : c.val ≤ p.val)
    (hd : d = core.num.Usize.wrapping_sub p c) (hi : i = core.num.Usize.wrapping_sub d 1#usize)
    (hlt : i < 32768#usize) (hl : l.val ≤ cap.val) (hm : Matches s c.val p.val l.val) :
    Cand s p.val cap.val l.val d.val := C12562!
theorem walk_loop_spec (s : Slice Std.U8) {W : Std.Usize} (prev : Array Std.U32 W)
    (p cap gm n best bd : Std.Usize) (bg : Std.I32) (c k stop : Std.Usize) (pb : Std.U8)
    (hn : n.val = s.length) (hcap : p.val + cap.val ≤ s.length) (hcap258 : cap.val ≤ 258)
    (hc : c.val ≤ p.val) (hbest : p.val + best.val ≤ s.length)
    (hcand : Cand s p.val cap.val best.val bd.val) (hW : 0 < W.val) :
    slot.pc_walk_loop s prev p cap gm n best bd bg c k stop pb ⦃ fun r =>
      p.val + r.1.val ≤ s.length ∧ Cand s p.val cap.val r.1.val r.2.val ⦄ := C12563! slot.pc_walk_loop slot.pc_walk_loop.body
@[local step]
theorem walk_spec (s : Slice Std.U8) {W : Std.Usize} (prev : Array Std.U32 W)
    (p start cap «have» depth gm : Std.Usize)
    (hcap : p.val + cap.val ≤ s.length) (hcap258 : cap.val ≤ 258) (hst : start.val ≤ p.val)
    (hhave : p.val + «have».val ≤ s.length) (hW : 0 < W.val) :
    slot.pc_walk s prev p start cap «have» depth gm ⦃ fun r =>
      p.val + r.1.val ≤ s.length ∧ Cand s p.val cap.val r.1.val r.2.val ⦄ := C12564! slot.pc_walk
def MatchAt (s : Slice Std.U8) (p l d : Nat) : Prop :=
  3 ≤ l ∧ l ≤ 258 ∧ p + l ≤ s.length ∧ 1 ≤ d ∧ d ≤ 32768 ∧ d ≤ p ∧ Matches s (p - d) p l
def FoundAt (s : Slice Std.U8) (p l d : Nat) : Prop := l < 3 ∨ MatchAt s p l d
theorem FoundAt.of_cand {s : Slice Std.U8} {p cap : Nat} {l d : Std.Usize}
    (hc : Cand s p cap l.val d.val) (hd : ¬d = 0#usize) (hcap : cap ≤ 258)
    (hpl : p + l.val ≤ s.length) : FoundAt s p l.val d.val := C12565!
theorem Cand.len_le {s : Slice Std.U8} {p cap : Nat} {l d : Std.Usize}
    (hc : Cand s p cap l.val d.val) (hd : ¬d = 0#usize) (hcap : cap ≤ 258) : l.val ≤ 258 := C12566!
theorem Cand.dist_le {s : Slice Std.U8} {p cap l d : Nat} (hc : Cand s p cap l d) :
    d ≤ 32768 := C12567!
theorem FoundAt.none (s : Slice Std.U8) (p : Nat) : FoundAt s p (0#usize).val (0#usize).val :=
  Or.inl (by simp)
theorem FoundAt.real {s : Slice Std.U8} {p l d : Nat} (hf : FoundAt s p l d) (h3 : 3 ≤ l) :
    MatchAt s p l d := C12568!
@[local step]
theorem find_spec (s : Slice Std.U8) {W : Std.Usize} (prev : Array Std.U32 W)
    (p st «have» minl depth gm : Std.Usize)
    (hp : p.val ≤ s.length) (hst : st.val ≤ p.val) (hhave : p.val + «have».val ≤ s.length)
    (hhave258 : «have».val ≤ 258) (hminl : 1 ≤ minl.val) (hminl' : p.val + minl.val ≤ s.length + 1)
    (hW : 0 < W.val) :
    slot.pc_find s prev p st «have» minl depth gm ⦃ fun r => FoundAt s p.val r.1.val r.2.val ∧
      r.1.val ≤ 258 ∧ r.2.val ≤ 32768 ⦄ := C12569! slot.pc_find
theorem copyN_take_prefix (acc : List Nat) (d : Nat) :
    ∀ n, (copyN acc d n).take acc.length = acc := C12518!
theorem foldlM_emit_length : ∀ (ts : List Nat) (init acc : List Nat),
    ts.foldlM emit init = some acc → init.length + ts.length ≤ acc.length := C12519!
theorem decode_length_le {ts acc : List Nat} (h : decode ts = some acc) :
    ts.length ≤ acc.length := C12520!
theorem decode_pop_lit {ts : List Nat} {t : Nat} {inp : List Nat} {p : Nat}
    (hp : p ≤ inp.length) (hd : decode (ts ++ [t]) = some (inp.take p)) (ht : t < 256) :
    1 ≤ p ∧ decode ts = some (inp.take (p - 1)) := C12521!
theorem decode_pop_match {ts : List Nat} {t : Nat} {inp : List Nat} {p : Nat}
    (hp : p ≤ inp.length) (hd : decode (ts ++ [t]) = some (inp.take p)) (ht : 256 ≤ t) :
    tokLen t ≤ p ∧ decode ts = some (inp.take (p - tokLen t)) := C12522!
theorem toks_pop (out : Slice Std.U32) (nt : Nat) (h0 : 0 < nt) (hle : nt ≤ out.length) :
    toks out nt = toks out (nt - 1) ++ [(out.val[nt - 1]!).val] := C12523!
theorem toks_length (out : Slice Std.U32) (nt : Nat) (h : nt ≤ out.length) :
    (toks out nt).length = nt := C12524!
def Dec (s : Slice Std.U8) (out : Slice Std.U32) (nt p : Nat) : Prop :=
  p ≤ s.length ∧ nt ≤ p ∧ s.length ≤ out.length ∧
    decode (toks out nt) = some ((bytes s).take p)
theorem Dec.init (input : Slice Std.U8) (out : Slice Std.U32) (h : input.length ≤ out.length) :
    Dec input out (0#usize).val (0#usize).val :=
  ⟨by simp, by simp, h, by simp [toks, LZ77.decode]⟩
theorem Dec.lit {s : Slice Std.U8} {out : Slice Std.U32} {nt p : Nat} (h : Dec s out nt p)
    (hp : p < s.length) (ntU : Std.Usize) (hnt : ntU.val = nt) (v : Std.U32)
    (hv : v.val = (s.val[p]!).val) :
    Dec s (out.set ntU v) (nt + 1) (p + 1) := C12570!
theorem Dec.match {s : Slice Std.U8} {out : Slice Std.U32} {nt p l d : Nat} (h : Dec s out nt p)
    (hm : MatchAt s p l d) (ntU : Std.Usize) (hnt : ntU.val = nt) (v : Std.U32)
    (hv : v.val = LZ77.mkMatch d l) :
    Dec s (out.set ntU v) (nt + 1) (p + l) := C12571!
theorem Dec.pop_lit {s : Slice Std.U8} {out : Slice Std.U32} {nt p : Nat} (h : Dec s out nt p)
    (h0 : 0 < nt) (hle : nt ≤ out.length) (ht : (out.val[nt - 1]!).val < 256) :
    1 ≤ p ∧ Dec s out (nt - 1) (p - 1) := C12525!
theorem Dec.pop_match {s : Slice Std.U8} {out : Slice Std.U32} {nt p : Nat} (h : Dec s out nt p)
    (h0 : 0 < nt) (hle : nt ≤ out.length) (ht : 256 ≤ (out.val[nt - 1]!).val) :
    tokLen (out.val[nt - 1]!).val ≤ p ∧
      Dec s out (nt - 1) (p - tokLen (out.val[nt - 1]!).val) := C12526!
theorem Dec.done {s : Slice Std.U8} {out : Slice Std.U32} {nt p : Nat} (h : Dec s out nt p)
    (hp : s.length ≤ p) : nt ≤ s.length ∧ LZ77.Valid (bytes s) (toks out nt) := C12572!
theorem Dec.lit_step {s : Slice Std.U8} {out out1 : Slice Std.U32} {ntU nt1 pU : Std.Usize}
    {b : Std.U8} {v : Std.U32} (h : Dec s out ntU.val pU.val) (hp : pU.val < s.val.length)
    (hb : b = s.val[pU.val]) (hv : v = UScalar.cast .U32 b) (hout1 : out1 = out.set ntU v)
    (hnt1 : nt1.val = ntU.val + 1) :
    nt1.val = ntU.val + 1 ∧ out1.length = out.length ∧ Dec s out1 nt1.val (pU.val + 1) := C12573!
@[local step]
theorem put_lit_spec (s : Slice Std.U8) (out : Slice Std.U32) (nt p : Std.Usize)
    (hdec : Dec s out nt.val p.val) (hp : p.val < s.length) :
    slot.pc_put_lit s out nt p ⦃ fun r => r.1.val = nt.val + 1 ∧ r.2.length = out.length ∧
      Dec s r.2 r.1.val (p.val + 1) ⦄ := C12574! slot.pc_put_lit
theorem Dec.match_step {s : Slice Std.U8} {out out1 : Slice Std.U32} {ntU nt1 pU dU lU e : Std.Usize}
    {v : Std.U32} (h : Dec s out ntU.val pU.val) (hm : MatchAt s pU.val lU.val dU.val)
    (hout1 : out1 = out.set ntU v) (hv : v.val = LZ77.mkMatch dU.val lU.val)
    (hnt1 : nt1.val = ntU.val + 1) (he : e.val = pU.val + lU.val) :
    nt1.val = ntU.val + 1 ∧ e.val = pU.val + lU.val ∧ out1.length = out.length ∧
      Dec s out1 nt1.val e.val := C12575!
@[local step]
theorem put_match_spec (s : Slice Std.U8) (out : Slice Std.U32) (nt p d l : Std.Usize)
    (hdec : Dec s out nt.val p.val) (hm : MatchAt s p.val l.val d.val) :
    slot.pc_put_match s out nt p d l ⦃ fun r => r.1.1.val = nt.val + 1 ∧
      r.1.2.val = p.val + l.val ∧ r.2.length = out.length ∧ Dec s r.2 r.1.1.val r.1.2.val ⦄ := C12576! slot.pc_put_match
theorem MatchAt.back_lit {s : Slice Std.U8} {p l d : Nat} (h : MatchAt s p l d) (hl : l < 258)
    (hdp : d < p) (heq : s.val[p - 1]! = s.val[p - 1 - d]!) : MatchAt s (p - 1) (l + 1) d := C12577!
theorem MatchAt.back_match {s : Slice Std.U8} {p l d w : Nat} (h : MatchAt s p l d)
    (hlw : l + w ≤ 258) (hw : w ≤ p) (hdw : d ≤ p - w) (hmw : Matches s (p - w - d) (p - w) w) :
    MatchAt s (p - w) (l + w) d := C12578!
def BackInv (input : Slice Std.U8) (out : Slice Std.U32) (d E P0 : Nat) (nt p l : Nat) : Prop :=
  Dec input out nt p ∧ MatchAt input p l d ∧ p + l = E ∧ p ≤ P0
theorem BackInv.lit {input : Slice Std.U8} {out : Slice Std.U32} {d E P0 : Nat}
    {nt p l i1 i2 i4 l1 : Std.Usize} {t : Std.U32} {x y : Std.U8}
    (h : BackInv input out d E P0 nt.val p.val l.val)
    (hi1 : i1.val = nt.val - 1) (hntl : nt.val ≤ out.length) (hnt0 : 1 ≤ nt.val)
    (hi1l : i1.val < out.val.length) (ht : t = out.val[i1.val]) (ht256 : t < 256#u32)
    (hi2 : i2.val = p.val - 1) (hi2l : i2.val < input.val.length) (hx : x = input.val[i2.val])
    (hxy : x = y) (hi4 : i4.val = i2.val - d) (hi4l : i4.val < input.val.length)
    (hy : y = input.val[i4.val]) (hl : l.val < 258) (hdp : d < p.val)
    (hl1 : l1.val = l.val + 1) :
    BackInv input out d E P0 i1.val i2.val l1.val := C12579!
theorem BackInv.match {input : Slice Std.U8} {out : Slice Std.U32} {d E P0 : Nat}
    {nt p l i1 w i9 i10 i11 i12 : Std.Usize} {t : Std.U32}
    (h : BackInv input out d E P0 nt.val p.val l.val)
    (hi1 : i1.val = nt.val - 1) (hntl : nt.val ≤ out.length) (hnt0 : 1 ≤ nt.val)
    (hi1l : i1.val < out.val.length) (ht : t = out.val[i1.val])
    (hsame : i12.val = 1 → Matches input i11.val i10.val w.val) (hi12 : i12 = 1#usize)
    (ht24 : 16777216 ≤ t.val) (hwv : w.val = (t.val - 16777216) % 256 + 3)
    (hi9 : i9.val = l.val + w.val) (hi9' : i9.val ≤ 258) (hi10 : i10.val = p.val - w.val)
    (hwp : w.val ≤ p.val) (hdw : d ≤ i10.val) (hi11 : i11.val = i10.val - d) :
    BackInv input out d E P0 i1.val i10.val i9.val := C12580!
theorem fold_loop_inv (input : Slice Std.U8) (out : Slice Std.U32) (nt p l d back : Std.Usize)
    (E P0 : Nat) (hP0 : P0 + 8 ≤ input.length)
    (hinv : BackInv input out d.val E P0 nt.val p.val l.val) :
    slot.pc_fold_loop input out d nt p l back ⦃ fun r =>
      BackInv input out d.val E P0 r.1.val r.2.1.val r.2.2.val ⦄ := by
  rw [slot.pc_fold_loop]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  apply Std.loop.spec_decr_nat
    (measure := fun r => slot.pc_BACKTOK.val - r.2.2.2.val)
    (inv := fun r => BackInv input out d.val E P0 r.1.val r.2.1.val r.2.2.1.val)
  · rintro ⟨nt, p, l, back⟩ hinv
    simp only at hinv
    have hinv' := hinv
    obtain ⟨⟨hps, hntp, hso, _⟩, ⟨h3, h258, hpl, hd1, hd32, hdp, _⟩, hE, hp0⟩ := hinv'
    simp only [slot.pc_fold_loop.body]
    step*
    all_goals first
      | (refine ⟨hinv, by scalar_tac⟩)
      | (refine ⟨BackInv.lit hinv (by scalar_tac) (by scalar_tac) (by scalar_tac) (by scalar_tac)
          (by assumption) (by assumption) (by scalar_tac) (by scalar_tac) (by assumption)
          (by assumption) (by assumption) (by scalar_tac) (by assumption) (by scalar_tac)
          (by scalar_tac) (by scalar_tac), by scalar_tac⟩)
      | (refine ⟨BackInv.match hinv (by scalar_tac) (by scalar_tac) (by scalar_tac) (by scalar_tac)
          (by assumption) (by assumption) (by assumption) (by scalar_tac) (by scalar_tac)
          (by scalar_tac) (by scalar_tac) (by scalar_tac) (by scalar_tac) (by scalar_tac)
          (by scalar_tac), by scalar_tac⟩)
  · exact hinv
@[local step]
theorem fold_spec (input : Slice Std.U8) (out : Slice Std.U32) (nt p l d : Std.Usize)
    (hp8 : p.val + 8 ≤ input.length) (hdec : Dec input out nt.val p.val)
    (hm : MatchAt input p.val l.val d.val) :
    slot.pc_fold input out nt p l d ⦃ fun r =>
      Dec input out r.1.val r.2.1.val ∧ MatchAt input r.2.1.val r.2.2.val d.val ∧
      r.2.1.val + r.2.2.val = p.val + l.val ∧ r.2.1.val ≤ p.val ⦄ := by
  apply Std.WP.spec_mono (fold_loop_inv input out nt p l d 0#usize (p.val + l.val) p.val hp8
    ⟨hdec, hm, rfl, le_refl _⟩)
  intro r h
  exact h
@[local step]
theorem fold_w_spec (input : Slice Std.U8) (out : Slice Std.U32) (nt p l d : Std.Usize)
    (hp8 : p.val + 8 ≤ input.length) (hdec : Dec input out nt.val p.val)
    (hm : MatchAt input p.val l.val d.val) :
    slot.pc_fold_w input out nt p l d ⦃ fun r =>
      Dec input out r.1.val r.2.1.val ∧ MatchAt input r.2.1.val r.2.2.val d.val ∧
      r.2.1.val + r.2.2.val = p.val + l.val ∧ r.2.1.val ≤ p.val ⦄ := by
  rw [slot.pc_fold_w]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  apply Std.WP.spec_bind (Pₘ := fun m : Std.U32 => 1 ≤ m.val ∧ m.val ≤ 8)
  · split
    · dsimp only
      split
      · step*
      · simp
    · simp
  · intro m ⟨hm1, hm8⟩
    apply Std.WP.spec_bind (Pₘ := fun _ : Std.U64 => True)
    · split
      · step*
      · simp
    · intro x _
      step*
      all_goals first
        | exact ⟨hdec, hm, rfl, le_refl _⟩
        | scalar_tac
def LazyInv (input : Slice Std.U8) (L lim : Nat) (out : Slice Std.U32) (nt p : Nat)
    {N : Std.Usize} (head : Array Std.U32 N) (ins l d : Nat) : Prop :=
  Dec input out nt p ∧ out.length = L ∧ MatchAt input p l d ∧ HeadBound head (p + 1) ∧
    p < lim ∧ ins ≤ p + 2
theorem LazyInv.accept {input : Slice Std.U8} {L lim p' B : Nat} {out1 : Slice Std.U32}
    {nt1 i ins1 l1 d1 minl : Std.Usize} {N : Std.Usize} {head1 : Array Std.U32 N}
    (hdec : Dec input out1 nt1.val p') (hi : i.val = p') (hlen : out1.length = L)
    (hf : FoundAt input i.val l1.val d1.val) (hl1 : minl.val ≤ l1.val) (hminl : 3 ≤ minl.val)
    (hB : HeadBound head1 B) (hBi : B ≤ i.val + 1) (hilim : i.val < lim)
    (hins : ins1.val ≤ i.val + 2) :
    LazyInv input L lim out1 nt1.val i.val head1 ins1.val l1.val d1.val := C12581!
theorem LazyInv.reject {input : Slice Std.U8} {L lim : Nat} {out : Slice Std.U32}
    {nt p ins ins1 l d B : Nat} {N : Std.Usize} {head head1 : Array Std.U32 N}
    (h : LazyInv input L lim out nt p head ins l d) (hB : HeadBound head1 B) (hBp : B ≤ p + 1)
    (hins1 : ins1 ≤ p + 2) : LazyInv input L lim out nt p head1 ins1 l d := C12582!
theorem lazy_loop_inv {H W : Std.Usize} (input : Slice Std.U8) (out : Slice Std.U32)
    (cls nt p : Std.Usize) (mask : Std.U32) (minl lazy : Std.Usize) (head : Array Std.U32 H)
    (prev : Array Std.U32 W) (lim ins l d : Std.Usize) (go : Std.U32) (L : Nat)
    (hlim : lim.val + 8 = input.length) (hminl : 3 ≤ minl.val) (hminl8 : minl.val ≤ 8)
    (hH : 0 < H.val) (hW : 0 < W.val)
    (hinv : LazyInv input L lim.val out nt.val p.val head ins.val l.val d.val) :
    slot.pc_run_loop0_loop1 input out cls nt p mask minl lazy head prev lim ins l d go ⦃ fun r =>
      LazyInv input L lim.val r.1 r.2.1.val r.2.2.1.val r.2.2.2.1 r.2.2.2.2.2.1.val
        r.2.2.2.2.2.2.1.val r.2.2.2.2.2.2.2.val ⦄ := C12583! slot.pc_run_loop0_loop1 slot.pc_run_loop0_loop1.body
@[local step]
theorem lazy_loop_spec {H W : Std.Usize} (input : Slice Std.U8) (out : Slice Std.U32)
    (cls nt p : Std.Usize) (mask : Std.U32) (minl lazy : Std.Usize) (head : Array Std.U32 H)
    (prev : Array Std.U32 W) (lim ins l d : Std.Usize) (go : Std.U32) (L : Nat)
    (hlim : lim.val + 8 = input.length) (hminl : 3 ≤ minl.val) (hminl8 : minl.val ≤ 8)
    (hH : 0 < H.val) (hW : 0 < W.val)
    (hdec : Dec input out nt.val p.val) (hlen : out.length = L)
    (hm : MatchAt input p.val l.val d.val) (hB : HeadBound head (p.val + 1))
    (hplim : p.val < lim.val) (hins : ins.val ≤ p.val + 2) :
    slot.pc_run_loop0_loop1 input out cls nt p mask minl lazy head prev lim ins l d go ⦃ fun r =>
      Dec input r.1 r.2.1.val r.2.2.1.val ∧ r.1.length = L ∧
      MatchAt input r.2.2.1.val r.2.2.2.2.2.2.1.val r.2.2.2.2.2.2.2.val ∧
      HeadBound r.2.2.2.1 (r.2.2.1.val + r.2.2.2.2.2.2.1.val) ∧ r.2.2.1.val < lim.val ∧
      r.2.2.2.2.2.1.val ≤ r.2.2.1.val + 2 ∧ 3 ≤ r.2.2.2.2.2.2.1.val ⦄ := C12584!
@[local step]
theorem ins_loop0_spec {H W : Std.Usize} (input : Slice Std.U8) (p : Std.Usize) (mask : Std.U32)
    (head : Array Std.U32 H) (prev : Array Std.U32 W) (ins : Std.Usize) (B : Nat)
    (hB : HeadBound head B) (hpB : p.val < B + 1) (hp4 : p.val + 4 ≤ Std.Usize.max)
    (hH : 0 < H.val) (hW : 0 < W.val) :
    slot.pc_run_loop0_loop0 input p mask head prev ins ⦃ fun r => HeadBound r.1 B ⦄ := C12585! slot.pc_run_loop0_loop0 slot.pc_run_loop0_loop0.body
@[local step]
theorem ins_loop3_spec {H W : Std.Usize} (input : Slice Std.U8) (mask : Std.U32)
    (head : Array Std.U32 H) (prev : Array Std.U32 W) (ins stop : Std.Usize) (B : Nat)
    (hB : HeadBound head B) (hsB : stop.val < B + 1) (hs4 : stop.val + 4 ≤ Std.Usize.max)
    (hH : 0 < H.val) (hW : 0 < W.val) :
    slot.pc_run_loop0_loop2 input mask head prev ins stop ⦃ fun r =>
      HeadBound r.1 B ∧ (r.2.2.val ≤ ins.val ∨ r.2.2.val ≤ stop.val) ⦄ := C12586! slot.pc_run_loop0_loop2 slot.pc_run_loop0_loop2.body
@[local step]
theorem stride_loop_spec {H W : Std.Usize} (input : Slice Std.U8) (mask : Std.U32)
    (head : Array Std.U32 H) (prev : Array Std.U32 W) (lim ins «end» : Std.Usize) (B : Nat)
    (hB : HeadBound head B) (heB : «end».val < B + 1) (hl4 : lim.val + 4 ≤ Std.Usize.max)
    (hH : 0 < H.val) (hW : 0 < W.val) (hS : 0 < slot.pc_STRIDE.val)
    (hie : ins.val ≤ «end».val) :
    slot.pc_run_loop0_loop3 input mask head prev lim ins «end» ⦃ fun r =>
      HeadBound r.1 B ∧ r.2.2.val ≤ «end».val ∧
        (r.2.2.val ≤ ins.val ∨ r.2.2.val + slot.pc_TAIL.val < «end».val) ⦄ := C12587! slot.pc_run_loop0_loop3 slot.pc_TAIL.val slot.pc_run_loop0_loop3.body
@[local step]
theorem ins_loop5_spec {H W : Std.Usize} (input : Slice Std.U8) (mask : Std.U32)
    (head : Array Std.U32 H) (prev : Array Std.U32 W) (lim ins «end» : Std.Usize) (B : Nat)
    (hB : HeadBound head B) (heB : «end».val < B + 1) (hl4 : lim.val + 4 ≤ Std.Usize.max)
    (hH : 0 < H.val) (hW : 0 < W.val) :
    slot.pc_run_loop0_loop4 input mask head prev lim ins «end» ⦃ fun r =>
      HeadBound r.1 B ∧ (r.2.2.val ≤ ins.val ∨ r.2.2.val ≤ «end».val) ⦄ := C12588! slot.pc_run_loop0_loop4 slot.pc_run_loop0_loop4.body
@[local step]
theorem ins_loop6_spec {H W : Std.Usize} (input : Slice Std.U8) (mask : Std.U32)
    (head : Array Std.U32 H) (prev : Array Std.U32 W) (lim ins «end» : Std.Usize) (B : Nat)
    (hB : HeadBound head B) (heB : «end».val < B + 1) (hl4 : lim.val + 4 ≤ Std.Usize.max)
    (hH : 0 < H.val) (hW : 0 < W.val) :
    slot.pc_run_loop0_loop5 input mask head prev lim ins «end» ⦃ fun r =>
      HeadBound r.1 B ∧ (r.2.2.val ≤ ins.val ∨ r.2.2.val ≤ «end».val) ⦄ := C12588! slot.pc_run_loop0_loop5 slot.pc_run_loop0_loop5.body
@[local step]
theorem skip_loop_spec (input : Slice Std.U8) (out : Slice Std.U32) (nt p lim step : Std.Usize)
    (hdec : Dec input out nt.val p.val) (hlim : lim.val ≤ input.length) :
    slot.pc_run_loop0_loop6 input out nt p lim step ⦃ fun r =>
      Dec input r.1 r.2.1.val r.2.2.val ∧ r.1.length = out.length ∧ p.val ≤ r.2.2.val ⦄ := C12589! slot.pc_run_loop0_loop6 slot.pc_run_loop0_loop6.body
@[local step]
theorem tail_loop1_spec (input : Slice Std.U8) (out : Slice Std.U32) (n nt p : Std.Usize)
    (hn : n.val = input.length) (hdec : Dec input out nt.val p.val) :
    slot.pc_run_loop1 input out n nt p ⦃ fun r => r.1.val ≤ input.length ∧
      r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := C12590! slot.pc_run_loop1 slot.pc_run_loop1.body
@[local step]
theorem tail_loop2_spec (input : Slice Std.U8) (out : Slice Std.U32) (n nt p : Std.Usize)
    (hn : n.val = input.length) (hdec : Dec input out nt.val p.val) :
    slot.pc_run_loop2 input out n nt p ⦃ fun r => r.1.val ≤ input.length ∧
      r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := C12590! slot.pc_run_loop2 slot.pc_run_loop2.body
@[local step]
theorem tail_loop3_spec (input : Slice Std.U8) (out : Slice Std.U32) (n nt p : Std.Usize)
    (hn : n.val = input.length) (hdec : Dec input out nt.val p.val) :
    slot.pc_run_loop3 input out n nt p ⦃ fun r => r.1.val ≤ input.length ∧
      r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := C12590! slot.pc_run_loop3 slot.pc_run_loop3.body
theorem numBits_ge : 32 ≤ System.Platform.numBits := C12527!
def MainInv (input : Slice Std.U8) (L : Nat) (out : Slice Std.U32) (nt p : Nat)
    {N : Std.Usize} (head : Array Std.U32 N) (miss : Nat) : Prop :=
  Dec input out nt p ∧ out.length = L ∧ HeadBound head p ∧ miss ≤ p
theorem MainInv.mk' {input : Slice Std.U8} {L : Nat} {out : Slice Std.U32} {nt p m B : Nat}
    {N : Std.Usize} {head : Array Std.U32 N} (hdec : Dec input out nt p) (hlen : out.length = L)
    (hB : HeadBound head B) (hBp : B ≤ p) (hm : m ≤ p) : MainInv input L out nt p head m :=
  ⟨hdec, hlen, HeadBound.mono hB hBp, hm⟩
set_option maxHeartbeats 16000000 in
theorem main_loop_spec {H W : Std.Usize} (input : Slice Std.U8) (out : Slice Std.U32)
    (cls nt p : Std.Usize) (mask : Std.U32) (minl depth lazy skip skcap : Std.Usize)
    (head : Array Std.U32 H) (prev : Array Std.U32 W)
    (lim ins miss fuel : Std.Usize) (L : Nat)
    (hlim : lim.val + 8 = input.length) (hminl : 3 ≤ minl.val) (hminl8 : minl.val ≤ 8)
    (hskip : skip.val < 32) (hH : 0 < H.val) (hW : 0 < W.val)
    (hinv : MainInv input L out nt.val p.val head miss.val) :
    slot.pc_run_loop0 input out cls nt p mask minl depth lazy skip skcap head prev lim ins miss
      fuel ⦃ fun r => Dec input r.1 r.2.1.val r.2.2.val ∧ r.1.length = L ⦄ := C12591! slot.pc_run_loop0 slot.pc_run_loop0.body
@[local step]
theorem main_loop_spec' {H W : Std.Usize} (input : Slice Std.U8) (out : Slice Std.U32)
    (cls nt p : Std.Usize) (mask : Std.U32) (minl depth lazy skip skcap : Std.Usize)
    (head : Array Std.U32 H) (prev : Array Std.U32 W)
    (lim ins miss fuel : Std.Usize)
    (hlim : lim.val + 8 = input.length) (hminl : 3 ≤ minl.val) (hminl8 : minl.val ≤ 8)
    (hskip : skip.val < 32) (hH : 0 < H.val) (hW : 0 < W.val)
    (hdec : Dec input out nt.val p.val) (hB : HeadBound head p.val)
    (hmiss : miss.val ≤ p.val) :
    slot.pc_run_loop0 input out cls nt p mask minl depth lazy skip skcap head prev lim ins miss
      fuel ⦃ fun r => Dec input r.1 r.2.1.val r.2.2.val ∧ r.1.length = out.length ⦄ :=
  main_loop_spec input out cls nt p mask minl depth lazy skip skcap head prev lim ins miss fuel
    out.length hlim hminl hminl8 hskip hH hW ⟨hdec, rfl, hB, hmiss⟩
def CntBound (cnt : Array Std.U32 256#usize) (T : Nat) : Prop :=
  ∀ j : Nat, j < 256 → (cnt.val[j]!).val ≤ T
theorem CntBound.init : CntBound (Std.Array.repeat 256#usize 0#u32) 0 := C1251!
theorem CntBound.get {cnt : Array Std.U32 256#usize} {T : Nat} (h : CntBound cnt T)
    (a : Std.Usize) (x : Std.U32) (ha : a.val < cnt.val.length) (hx : x = cnt.val[a.val]) :
    x.val ≤ T := C1252!
@[local step]
theorem cnt_index_spec (cnt : Array Std.U32 256#usize) (T : Nat) (h : CntBound cnt T)
    (i : Std.Usize) (hi : i.val < 256) :
    Std.Array.index_usize cnt i ⦃ fun x => x = cnt.val[i.val]! ∧ x.val ≤ T ⦄ := C1253!
theorem CntBound.update {cnt : Array Std.U32 256#usize} {T : Nat} (h : CntBound cnt T)
    (a : Std.Usize) (v : Std.U32) (hv : v.val ≤ T + 1) : CntBound (cnt.set a v) (T + 1) := C1254!
theorem CntBound.step {cnt a : Array Std.U32 256#usize} {T : Nat} {x : Std.Usize}
    {v tot1 : Std.U32} (hc : CntBound cnt T) (ha : a = cnt.set x v) (hv : v.val ≤ T + 1)
    (ht1 : tot1.val = T + 1) : CntBound a tot1.val := C1255!
theorem CntBound.mono {cnt : Array Std.U32 256#usize} {T T' : Nat} (h : CntBound cnt T)
    (hT : T ≤ T') : CntBound cnt T' := fun j hj => le_trans (h j hj) hT
@[local step]
theorem lift_spec {α : Type} (x : α) : lift x ⦃ fun y => y = x ⦄ := by
  simp [lift]
@[local step]
theorem run_spec (H W : Std.Usize) (input : Slice Std.U8) (out : Slice Std.U32) (cls : Std.Usize)
    (hlen : input.length ≤ out.length) (hH : 0 < H.val) (hW : 0 < W.val) :
    slot.pc_run H W input out cls ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧
      LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := C12592! slot.pc_run
theorem Dec.cast {s : Slice Std.U8} {out : Slice Std.U32} {nt p p' : Nat} (h : Dec s out nt p)
    (hp : p = p') : Dec s out nt p' := hp ▸ h
@[local step]
theorem head_set_spec {H : Std.Usize} (head : Array Std.U32 H) (a i : Std.Usize) (B : Nat)
    (hB : HeadBound head B) (ha : a.val < H.val) (hi : i.val < B + 1) :
    slot.pc_head_set head a i ⦃ fun r => HeadBound r B ⦄ := by
  rw [slot.pc_head_set]
  step*
  exact HeadBound.update hB (by assumption) (by omega) (by assumption)
theorem common_from_loop0_spec (s : Slice Std.U8) (a b cap k : Std.Usize) (run : Std.U32)
    (ha : a.val + cap.val ≤ s.length) (hb : b.val + cap.val ≤ s.length) (hcap : cap.val ≤ 258)
    (hk : k.val ≤ cap.val) (hm : Matches s a.val b.val k.val) :
    slot.pc_common_from_loop0 s a b cap k run ⦃ fun r =>
      r.1.val ≤ cap.val ∧ Matches s a.val b.val r.1.val ⦄ := C12598! slot.pc_common_from_loop0 slot.pc_common_from_loop0.body
theorem common_from_loop1_spec (s : Slice Std.U8) (a b cap k : Std.Usize) (run : Std.U32)
    (ha : a.val + cap.val ≤ s.length) (hb : b.val + cap.val ≤ s.length)
    (hk : k.val ≤ cap.val) (hm : Matches s a.val b.val k.val) :
    slot.pc_common_from_loop1 s a b cap k run ⦃ fun r =>
      r.val ≤ cap.val ∧ Matches s a.val b.val r.val ⦄ := C12547! slot.pc_common_from_loop1 slot.pc_common_from_loop1.body
@[local step]
theorem common_from_spec (s : Slice Std.U8) (a b cap k0 : Std.Usize)
    (ha : a.val + cap.val ≤ s.length) (hb : b.val + cap.val ≤ s.length) (hcap : cap.val ≤ 258)
    (hk0 : k0.val ≤ cap.val) (hm : Matches s a.val b.val k0.val) :
    slot.pc_common_from s a b cap k0 ⦃ fun l => l.val ≤ cap.val ∧ Matches s a.val b.val l.val ⦄ := by
  rw [slot.pc_common_from]
  apply Std.WP.spec_bind (common_from_loop0_spec s a b cap k0 1#u32 ha hb hcap hk0 hm)
  rintro ⟨k, run⟩ ⟨hk, hm'⟩
  exact common_from_loop1_spec s a b cap k run ha hb hk hm'
theorem Matches.xor_lz {s : Slice Std.U8} {c p m : Std.Usize} {cw y x : Std.U64}
    {lz q : Std.U32} (hcw : cw.val = word8 s c.val) (hy : y.val = word8 s p.val)
    (hx : x.val = (cw ^^^ y).val) (hx0 : (x != 0#u64) = true)
    (hlz : lz = core.num.U64.leading_zeros x) (hq : q.val = lz.val / 8)
    (hm : m = UScalar.cast .Usize q) : Matches s c.val p.val m.val ∧ m.val < 8 := C12594!
theorem Matches.xor_zero {s : Slice Std.U8} {c p : Std.Usize} {cw y x : Std.U64}
    (hcw : cw.val = word8 s c.val) (hy : y.val = word8 s p.val)
    (hx : x.val = (cw ^^^ y).val) (hx0 : ¬(x != 0#u64) = true) :
    Matches s c.val p.val (8#usize).val := C12595!
theorem FoundAt.of_matches {s : Slice Std.U8} {p c d i l : Std.Usize} (hc : c.val ≤ p.val)
    (hd : d = core.num.Usize.wrapping_sub p c) (hi : i = core.num.Usize.wrapping_sub d 1#usize)
    (hlt : i < 32768#usize) (hl : l.val ≤ 258) (hpl : p.val + l.val ≤ s.length)
    (hm : Matches s c.val p.val l.val) :
    FoundAt s p.val l.val d.val ∧ l.val ≤ 258 ∧ d.val ≤ 32768 := C12596!
theorem FoundAt.none' (s : Slice Std.U8) (p : Nat) :
    FoundAt s p (0#usize).val (0#usize).val ∧ (0#usize).val ≤ 258 ∧ (0#usize).val ≤ 32768 :=
  ⟨FoundAt.none s p, by simp, by simp⟩
@[local step]
theorem xlen_spec (s : Slice Std.U8) (c p : Std.Usize) (x cw y : Std.U64)
    (hx : x.val = (cw ^^^ y).val) (hcw : cw.val = word8 s c.val) (hy : y.val = word8 s p.val)
    (hc : c.val ≤ p.val) (hp : p.val + 8 ≤ s.length) :
    slot.pc_xlen s c p x ⦃ fun r => r.val ≤ 258 ∧ p.val + r.val ≤ s.length ∧
      Matches s c.val p.val r.val ⦄ := by
  rw [slot.pc_xlen]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  step*
  repeat' (split <;> step*)
  all_goals first
    | exact Matches.xor_zero hcw hy hx (by assumption)
    | (have hw := Matches.xor_lz (m := UScalar.cast .Usize i1) hcw hy hx (by assumption)
        (by assumption) (by assumption) rfl
       exact ⟨by scalar_tac, by scalar_tac, hw.1⟩)
theorem Matches.x16a {s : Slice Std.U8} {c p i1 i2 r l : Std.Usize} {x x2 : Std.U64}
    {lz q : Std.U32} (hx : x.val = word8 s c.val ^^^ word8 s p.val) (hx0 : x = 0#u64)
    (hi1 : i1.val = c.val + 8) (hi2 : i2.val = p.val + 8)
    (hx2 : x2.val = word8 s i1.val ^^^ word8 s i2.val)
    (hlz : lz = core.num.U64.leading_zeros x2) (hq : q.val = lz.val / 8)
    (hr : r = UScalar.cast .Usize q) (hl : l.val = 8 + r.val) :
    Matches s c.val p.val l.val ∧ l.val ≤ 16 := by
  have h8 := Matches.xz hx hx0
  rw [hi1, hi2] at hx2
  have := Matches.lz_any (k := 8) (k1 := l) h8 hx2 hlz hq hr (by omega)
  exact ⟨this.1, by omega⟩
theorem Matches.x16a' {s : Slice Std.U8} {c p i1 i2 r l : Std.Usize} {x x2 : Std.U64}
    {lz q : Std.U32} (hx : x.val = word8 s c.val ^^^ word8 s p.val) (hx0 : x = 0#u64)
    (hi1 : i1.val = c.val + 8) (hi2 : i2.val = p.val + 8)
    (hx2 : x2.val = word8 s i1.val ^^^ word8 s i2.val)
    (hlz : lz = core.num.U64.leading_zeros x2) (hq : q.val = lz.val / 8)
    (hr : r = UScalar.cast .Usize q) (hl : l.val = 8 + r.val) (hpn : p.val + 16 ≤ s.length) :
    l.val ≤ 258 ∧ p.val + l.val ≤ s.length ∧ Matches s c.val p.val l.val := by
  have h := Matches.x16a hx hx0 hi1 hi2 hx2 hlz hq hr hl
  exact ⟨by omega, by omega, h.1⟩
theorem Matches.x16b {s : Slice Std.U8} {c p r l : Std.Usize} {x : Std.U64}
    {lz q : Std.U32} (hx : x.val = word8 s c.val ^^^ word8 s p.val)
    (hlz : lz = core.num.U64.leading_zeros x) (hq : q.val = lz.val / 8)
    (hr : r = UScalar.cast .Usize q) (hl : l.val = 0 + r.val) (hpn : p.val + 8 ≤ s.length) :
    l.val ≤ 258 ∧ p.val + l.val ≤ s.length ∧ Matches s c.val p.val l.val := by
  have := Matches.lz_any (k := 0) (k1 := l) (LZ77.Matches.zero s c.val p.val)
    (by simpa using hx) hlz hq hr (by omega)
  exact ⟨by omega, by omega, this.1⟩
@[local step]
theorem xlen16_spec (s : Slice Std.U8) (c p : Std.Usize) (x cw y : Std.U64)
    (hx : x.val = (cw ^^^ y).val) (hcw : cw.val = word8 s c.val) (hy : y.val = word8 s p.val)
    (hc : c.val ≤ p.val) (hp : p.val + 8 ≤ s.length) :
    slot.pc_xlen16 s c p x ⦃ fun r => r.val ≤ 258 ∧ p.val + r.val ≤ s.length ∧
      Matches s c.val p.val r.val ⦄ := by
  rw [slot.pc_xlen16]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  have hxv := xval_of hx hcw hy
  step*
  repeat' (split <;> step*)
  all_goals first
    | exact Matches.mono (Matches.x16a hxv (by assumption) (by assumption) (by assumption)
        (by assumption) (by assumption) (by assumption) (by assumption) (by assumption)).1
        (by scalar_tac)
    | exact Matches.x16a' hxv (by assumption) (by assumption) (by assumption) (by assumption)
        (by assumption) (by assumption) (by assumption) (by assumption) (by scalar_tac)
    | exact Matches.x16b hxv (by assumption) (by assumption) (by assumption) (by assumption)
        (by scalar_tac)
@[local step]
theorem lazy_lo_spec (l : Std.Usize) :
    slot.pc_lazy_lo l ⦃ fun r => r.val = 3 ∨ (3 < r.val ∧ r.val + slot.pc_LSLACK.val = l.val) ⦄ := by
  rw [slot.pc_lazy_lo]
  step*
@[local step]
theorem probe_lazy_spec (s : Slice Std.U8) (c : Std.Usize) (cw : Std.U64) (q l : Std.Usize)
    (hc : c.val ≤ q.val) (hcw : cw.val = word8 s c.val) (hq : q.val + 8 ≤ s.length)
    (hl : q.val + l.val ≤ s.length + 1) :
    slot.pc_probe_lazy s c cw q l ⦃ fun r => FoundAt s q.val r.1.val r.2.val ∧ r.1.val ≤ 258 ∧
      r.2.val ≤ 32768 ⦄ := by
  rw [slot.pc_probe_lazy]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  have hL : 1 ≤ slot.pc_LSLACK.val := by scalar_tac
  step
  have hlo : q.val + lo.val ≤ s.length := by
    rcases lo_post with h | ⟨_, h⟩ <;> omega
  step*
  all_goals first
    | exact FoundAt.none' s q.val
    | exact FoundAt.of_matches hc (by assumption) (by assumption) (by assumption)
        (by assumption) (by assumption) (by assumption)
@[local step]
theorem skip_len_spec (miss skip skcap : Std.Usize) (hskip : skip.val < 32) :
    slot.pc_skip_len miss skip skcap ⦃ fun _ => True ⦄ := by
  rw [slot.pc_skip_len]
  have := numBits_ge
  step*
@[local step]
theorem skip_to_spec (p step lim : Std.Usize) (hp : p.val ≤ lim.val) :
    slot.pc_skip_to p step lim ⦃ fun r => p.val ≤ r.val ∧ r.val ≤ lim.val ⦄ := by
  rw [slot.pc_skip_to]
  step*
  exact ⟨by scalar_tac, by scalar_tac⟩
@[local step]
theorem slot_of_m_spec (H : Std.Usize) (s : Slice Std.U8) (i : Std.Usize) (km : Std.U32)
    (hi4 : i.val + 4 ≤ Std.Usize.max) (hH : 0 < H.val) :
    slot.pc_slot_of_m H s i km ⦃ fun r => r.val < H.val ⦄ := by
  rw [slot.pc_slot_of_m]
  step*
@[local step]
theorem ahead_m_spec {H : Std.Usize} (s : Slice Std.U8) (head : Array Std.U32 H) (i : Std.Usize)
    (km : Std.U32) (B : Nat) (hB : HeadBound head B) (hBn : B + 8 ≤ s.length)
    (hi4 : i.val + 4 ≤ Std.Usize.max) (hH : 0 < H.val) :
    slot.pc_ahead_m s head i km ⦃ fun r => r.1.val < H.val ∧ r.2.1.val ≤ B ∧
      r.2.2.val = word8 s r.2.1.val ⦄ := by
  rw [slot.pc_ahead_m]
  step
  step
  have hi1 : i1.val ≤ B := HeadBound.get hB a i1 (by scalar_tac) (by assumption)
  step*
@[local step]
theorem ahead_if_m_spec {H : Std.Usize} (s : Slice Std.U8) (head : Array Std.U32 H)
    (i lim a c : Std.Usize) (w : Std.U64) (km : Std.U32) (B : Nat) (hB : HeadBound head B)
    (hBi : B < i.val + 1) (hlim : lim.val + 8 = s.length) (ha : a.val < H.val)
    (hc : c.val < B + 1) (hw : w.val = word8 s c.val) (hH : 0 < H.val) :
    slot.pc_ahead_if_m s head i lim a c w km ⦃ fun r => r.1.val < H.val ∧ r.2.1.val ≤ B ∧
      r.2.2.val = word8 s r.2.1.val ⦄ := by
  rw [slot.pc_ahead_if_m]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  step*
@[local step]
theorem ahead_fix_m_spec {H : Std.Usize} (s : Slice Std.U8) (head : Array Std.U32 H)
    (i lim e a c : Std.Usize) (w : Std.U64) (a0 c0 : Std.Usize) (w0 : Std.U64) (km : Std.U32)
    (B : Nat) (hB : HeadBound head B) (hBi : B < i.val + 1) (hlim : lim.val + 8 = s.length)
    (hw : w.val = word8 s c.val) (ha0 : a0.val < H.val) (hc0 : c0.val < B + 1)
    (hw0 : w0.val = word8 s c0.val) (hH : 0 < H.val) :
    slot.pc_ahead_fix_m s head i lim e a c w a0 c0 w0 km ⦃ fun r => r.1.val < H.val ∧
      r.2.1.val ≤ B ∧ r.2.2.val = word8 s r.2.1.val ⦄ := by
  rw [slot.pc_ahead_fix_m]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  step*
  all_goals first
    | (have hi1 := HeadBound.get hB a i1 (by scalar_tac) (by assumption)
       exact ⟨by scalar_tac, by scalar_tac, hw⟩)
@[local step]
theorem probe_m_spec (s : Slice Std.U8) (c : Std.Usize) (cw : Std.U64) (p : Std.Usize)
    (km : Std.U32) (hc : c.val ≤ p.val) (hcw : cw.val = word8 s c.val)
    (hp : p.val + 8 ≤ s.length) :
    slot.pc_probe_m s c cw p km ⦃ fun r => FoundAt s p.val r.1.val r.2.val ∧ r.1.val ≤ 258 ∧
      r.2.val ≤ 32768 ⦄ := by
  rw [slot.pc_probe_m]
  step*
  all_goals first
    | exact FoundAt.none' s p.val
    | exact FoundAt.of_matches hc (by assumption) (by assumption) (by assumption)
        (by assumption) (by assumption) (by assumption)
theorem flush_loop_spec (input : Slice Std.U8) (out : Slice Std.U32) (e nt j : Std.Usize)
    (hdec : Dec input out nt.val j.val) (he : e.val ≤ input.length) (hj : j.val ≤ e.val) :
    slot.pc_flush_loop input out e nt j ⦃ fun r => Dec input r.2 r.1.val e.val ∧
      r.2.length = out.length ⦄ := by
  rw [slot.pc_flush_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun r => e.val - r.2.2.val)
    (inv := fun r => Dec input r.1 r.2.1.val r.2.2.val ∧ r.1.length = out.length ∧
      r.2.2.val ≤ e.val)
  · rintro ⟨out', nt', j'⟩ ⟨hdec', hlen', hj'⟩
    simp only at hdec' hlen' hj'
    simp only [slot.pc_flush_loop.body]
    step*
  · exact ⟨hdec, rfl, hj⟩
@[local step]
theorem flush_spec (input : Slice Std.U8) (out : Slice Std.U32) (nt a e : Std.Usize)
    (hdec : Dec input out nt.val a.val) (he : e.val ≤ input.length) (ha : a.val ≤ e.val) :
    slot.pc_flush input out nt a e ⦃ fun r => Dec input r.2 r.1.val e.val ∧
      r.2.length = out.length ⦄ :=
  flush_loop_spec input out e nt a hdec he ha
theorem Dec.set_beyond {s : Slice Std.U8} {out : Slice Std.U32} {nt p : Nat} (h : Dec s out nt p)
    (i : Std.Usize) (v : Std.U32) (hi : nt ≤ i.val) : Dec s (out.set i v) nt p := by
  obtain ⟨hps, hntp, hso, hde⟩ := h
  refine ⟨hps, hntp, by rw [Std.Slice.set_length]; exact hso, ?_⟩
  have : toks (out.set i v) nt = toks out nt := by
    simp only [toks, Std.Slice.set_val_eq, List.take_set]
    rw [List.set_eq_of_length_le (by rw [List.length_take]; omega)]
  rw [this]; exact hde
theorem Dec.flush4_step {s : Slice Std.U8} {out out1 out2 out3 out4 : Slice Std.U32}
    {nt a e j r i7 i9 i11 i13 i15 i17 : Std.Usize} {b0 b1 b2 b3 : Std.U8}
    {v0 v1 v2 v3 : Std.U32}
    (h : Dec s out nt.val a.val) (hae : a.val ≤ e.val) (hj : j.val = e.val - a.val)
    (hj4 : j.val ≤ 4) (ha4 : a.val + 4 ≤ s.length) (hnt4 : nt.val + 4 ≤ out.length)
    (ha0 : a.val < s.val.length) (hb0 : b0 = s.val[a.val]) (hv0 : v0 = UScalar.cast .U32 b0)
    (ho1 : out1 = out.set nt v0)
    (hi7 : i7.val = a.val + 1) (ha1 : i7.val < s.val.length) (hb1 : b1 = s.val[i7.val])
    (hi9 : i9.val = nt.val + 1) (hv1 : v1 = UScalar.cast .U32 b1) (ho2 : out2 = out1.set i9 v1)
    (hi11 : i11.val = a.val + 2) (ha2 : i11.val < s.val.length) (hb2 : b2 = s.val[i11.val])
    (hi13 : i13.val = nt.val + 2) (hv2 : v2 = UScalar.cast .U32 b2) (ho3 : out3 = out2.set i13 v2)
    (hi15 : i15.val = a.val + 3) (ha3 : i15.val < s.val.length) (hb3 : b3 = s.val[i15.val])
    (hi17 : i17.val = nt.val + 3) (hv3 : v3 = UScalar.cast .U32 b3) (ho4 : out4 = out3.set i17 v3)
    (hr : r.val = nt.val + j.val) :
    Dec s out4 r.val e.val ∧ out4.length = out.length := by
  have hv0' : v0.val = (s.val[a.val]!).val := by
    rw [hv0, U8.cast_U32_val_eq, hb0, getElem!_pos s.val a.val ha0]
  have hv1' : v1.val = (s.val[a.val + 1]!).val := by
    rw [hv1, U8.cast_U32_val_eq, hb1, show a.val + 1 = i7.val by omega,
      getElem!_pos s.val i7.val ha1]
  have hv2' : v2.val = (s.val[a.val + 1 + 1]!).val := by
    rw [hv2, U8.cast_U32_val_eq, hb2, show a.val + 1 + 1 = i11.val by omega,
      getElem!_pos s.val i11.val ha2]
  have hv3' : v3.val = (s.val[a.val + 1 + 1 + 1]!).val := by
    rw [hv3, U8.cast_U32_val_eq, hb3, show a.val + 1 + 1 + 1 = i15.val by omega,
      getElem!_pos s.val i15.val ha3]
  have hlen : out4.length = out.length := by
    rw [ho4, Std.Slice.set_length, ho3, Std.Slice.set_length, ho2, Std.Slice.set_length, ho1,
      Std.Slice.set_length]
  refine ⟨?_, hlen⟩
  have D1 : Dec s out1 (nt.val + 1) (a.val + 1) := by
    rw [ho1]; exact Dec.lit h (by omega) nt rfl v0 hv0'
  have D2 : Dec s out2 (nt.val + 1 + 1) (a.val + 1 + 1) := by
    rw [ho2]; exact Dec.lit D1 (by omega) i9 hi9 v1 hv1'
  have D3 : Dec s out3 (nt.val + 1 + 1 + 1) (a.val + 1 + 1 + 1) := by
    rw [ho3]; exact Dec.lit D2 (by omega) i13 (by omega) v2 hv2'
  have D4 : Dec s out4 (nt.val + 1 + 1 + 1 + 1) (a.val + 1 + 1 + 1 + 1) := by
    rw [ho4]; exact Dec.lit D3 (by omega) i17 (by omega) v3 hv3'
  rcases (show j.val = 0 ∨ j.val = 1 ∨ j.val = 2 ∨ j.val = 3 ∨ j.val = 4 by omega) with
    h0 | h1 | h2 | h3 | h4
  · have E : Dec s out4 nt.val a.val := by
      rw [ho4]; apply Dec.set_beyond _ _ _ (by omega)
      rw [ho3]; apply Dec.set_beyond _ _ _ (by omega)
      rw [ho2]; apply Dec.set_beyond _ _ _ (by omega)
      rw [ho1]; apply Dec.set_beyond _ _ _ (by omega)
      exact h
    rw [show r.val = nt.val by omega, show e.val = a.val by omega]; exact E
  · have E : Dec s out4 (nt.val + 1) (a.val + 1) := by
      rw [ho4]; apply Dec.set_beyond _ _ _ (by omega)
      rw [ho3]; apply Dec.set_beyond _ _ _ (by omega)
      rw [ho2]; apply Dec.set_beyond _ _ _ (by omega)
      exact D1
    rw [show r.val = nt.val + 1 by omega, show e.val = a.val + 1 by omega]; exact E
  · have E : Dec s out4 (nt.val + 1 + 1) (a.val + 1 + 1) := by
      rw [ho4]; apply Dec.set_beyond _ _ _ (by omega)
      rw [ho3]; apply Dec.set_beyond _ _ _ (by omega)
      exact D2
    rw [show r.val = nt.val + 1 + 1 by omega, show e.val = a.val + 1 + 1 by omega]; exact E
  · have E : Dec s out4 (nt.val + 1 + 1 + 1) (a.val + 1 + 1 + 1) := by
      rw [ho4]; apply Dec.set_beyond _ _ _ (by omega)
      exact D3
    rw [show r.val = nt.val + 1 + 1 + 1 by omega, show e.val = a.val + 1 + 1 + 1 by omega]
    exact E
  · rw [show r.val = nt.val + 1 + 1 + 1 + 1 by omega, show e.val = a.val + 1 + 1 + 1 + 1 by omega]
    exact D4
@[local step]
theorem flush4_spec (input : Slice Std.U8) (out : Slice Std.U32) (nt a e : Std.Usize)
    (hdec : Dec input out nt.val a.val) (he : e.val + 8 ≤ input.length) (ha : a.val ≤ e.val) :
    slot.pc_flush4 input out nt a e ⦃ fun r => Dec input r.2 r.1.val e.val ∧
      r.2.length = out.length ⦄ := by
  rw [slot.pc_flush4]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  step*
  all_goals first
    | exact flush_spec input out nt a e hdec (by scalar_tac) ha
    | (subst_vars; simp only [Std.Slice.set_length]; scalar_tac)
    | exact Dec.flush4_step hdec ha (by assumption) (by scalar_tac) (by scalar_tac)
        (by scalar_tac) (by scalar_tac) (by assumption) (by assumption) (by assumption)
        (by assumption) (by scalar_tac) (by assumption) (by assumption) (by assumption)
        (by assumption) (by assumption) (by scalar_tac) (by assumption) (by assumption)
        (by assumption) (by assumption) (by assumption) (by scalar_tac) (by assumption)
        (by assumption) (by assumption) (by assumption) (by assumption)
@[local step]
theorem record3_m_loop0_spec {H : Std.Usize} (s : Slice Std.U8) (head : Array Std.U32 H)
    (km : Std.U32) (ins stop : Std.Usize) (B : Nat) (hB : HeadBound head B)
    (hsB : stop.val < B + 1) (hs4 : stop.val + 4 ≤ Std.Usize.max) (hH : 0 < H.val) :
    slot.pc_record3_m_loop0 s head km ins stop ⦃ fun r =>
      HeadBound r.1 B ∧ (r.2.val ≤ ins.val ∨ r.2.val ≤ stop.val) ⦄ := by
  rw [slot.pc_record3_m_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun r => stop.val - r.2.val)
    (inv := fun r => HeadBound r.1 B ∧ (r.2.val ≤ ins.val ∨ r.2.val ≤ stop.val))
  · rintro ⟨head, ins'⟩ ⟨hB, hins⟩
    simp only at hB hins
    simp only [slot.pc_record3_m_loop0.body]
    step*
  · exact ⟨hB, Or.inl (le_refl _)⟩
@[local step]
theorem record3_m_loop1_spec {H : Std.Usize} (s : Slice Std.U8) (head : Array Std.U32 H)
    («end» lim : Std.Usize) (km : Std.U32) (ins : Std.Usize) (B : Nat) (hB : HeadBound head B)
    (heB : «end».val < B + 1) (hl4 : lim.val + 4 ≤ Std.Usize.max) (hH : 0 < H.val) :
    slot.pc_record3_m_loop1 s head «end» lim km ins ⦃ fun r => HeadBound r B ⦄ := by
  rw [slot.pc_record3_m_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun r => «end».val - r.2.val)
    (inv := fun r => HeadBound r.1 B)
  · rintro ⟨head, ins'⟩ hB
    simp only at hB
    simp only [slot.pc_record3_m_loop1.body]
    step*
  · exact hB
@[local step]
theorem record3_m_spec {H : Std.Usize} (s : Slice Std.U8) (head : Array Std.U32 H)
    (ins0 a0 «end» lim : Std.Usize) (km : Std.U32) (B : Nat) (hB : HeadBound head B)
    (heB : «end».val < B + 1) (hlim : lim.val + 8 = s.length) (hins : ins0.val ≤ lim.val + 1)
    (hH : 0 < H.val) :
    slot.pc_record3_m s head ins0 a0 «end» lim km ⦃ fun r => HeadBound r B ⦄ := by
  rw [slot.pc_record3_m]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  step*
  repeat' (split <;> step*)
def LazyInv1 (input : Slice Std.U8) (lim P0 : Nat) (p : Nat) {N : Std.Usize}
    (head : Array Std.U32 N) (ps pc pw l d ins : Nat) : Prop :=
  MatchAt input p l d ∧ HeadBound head (p + 1) ∧ p < lim ∧ ins ≤ p + 2 ∧ ps < N.val ∧
    pc ≤ p + 1 ∧ pw = word8 input pc ∧ P0 ≤ p
theorem LazyInv1.accept {input : Slice Std.U8} {lim P0 B : Nat}
    {i ins1 l1 d1 ps pc : Std.Usize} {pw : Std.U64} {N : Std.Usize} {head1 : Array Std.U32 N}
    (hf : FoundAt input i.val l1.val d1.val) (hl1 : 3 ≤ l1.val)
    (hB : HeadBound head1 B) (hBi : B ≤ i.val + 1) (hilim : i.val < lim)
    (hins : ins1.val ≤ i.val + 2) (hps : ps.val < N.val) (hpc : pc.val ≤ i.val + 1)
    (hpw : pw.val = word8 input pc.val) (hP : P0 ≤ i.val) :
    LazyInv1 input lim P0 i.val head1 ps.val pc.val pw.val l1.val d1.val ins1.val :=
  ⟨FoundAt.real hf hl1, HeadBound.mono hB hBi, hilim, hins, hps, hpc, hpw, hP⟩
theorem LazyInv1.reject {input : Slice Std.U8} {lim P0 : Nat}
    {p ps pc pw l d ins B ps1 pc1 pw1 ins1 : Nat} {N : Std.Usize}
    {head head1 : Array Std.U32 N}
    (h : LazyInv1 input lim P0 p head ps pc pw l d ins) (hB : HeadBound head1 B)
    (hBp : B ≤ p + 1) (hins1 : ins1 ≤ p + 2) (hps : ps1 < N.val) (hpc : pc1 ≤ p + 1)
    (hpw : pw1 = word8 input pc1) :
    LazyInv1 input lim P0 p head1 ps1 pc1 pw1 l d ins1 := C12597!
theorem lazy1_loop_inv {H : Std.Usize} (input : Slice Std.U8) (lazy : Std.Usize) (km : Std.U32)
    (p : Std.Usize)
    (head : Array Std.U32 H) (lim pre_slot pre_c : Std.Usize) (pre_w : Std.U64)
    (l d ins : Std.Usize) (go : Std.U32) (P0 : Nat)
    (hlim : lim.val + 8 = input.length) (hH : 0 < H.val)
    (hinv : LazyInv1 input lim.val P0 p.val head pre_slot.val pre_c.val pre_w.val l.val d.val
      ins.val) :
    slot.pc_run1_loop0_loop0 input lazy km p head lim pre_slot pre_c pre_w l d ins go ⦃ fun r =>
      LazyInv1 input lim.val P0 r.1.val r.2.1 r.2.2.1.val r.2.2.2.1.val r.2.2.2.2.1.val
        r.2.2.2.2.2.1.val r.2.2.2.2.2.2.1.val r.2.2.2.2.2.2.2.val ⦄ := by
  rw [slot.pc_run1_loop0_loop0]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  apply Std.loop.spec_decr_nat
    (measure := fun r => lim.val - r.1.val + r.2.2.2.2.2.2.2.2.val)
    (inv := fun r => LazyInv1 input lim.val P0 r.1.val r.2.1 r.2.2.1.val r.2.2.2.1.val
      r.2.2.2.2.1.val r.2.2.2.2.2.1.val r.2.2.2.2.2.2.1.val r.2.2.2.2.2.2.2.1.val)
  · rintro ⟨p, head, pre_slot, pre_c, pre_w, l, d, ins, go⟩ hinv
    simp only at hinv
    have hinv' := hinv
    obtain ⟨⟨h3, h258, hpl, hd1, hd32, hdp, _⟩, hB, hplim, hins, hslot, hpc, hpw, hP⟩ := hinv'
    simp only [slot.pc_run1_loop0_loop0.body]
    step*
    all_goals first
      | (refine ⟨LazyInv1.accept (by assumption) (by scalar_tac) (by assumption) (by scalar_tac)
          (by scalar_tac) (by scalar_tac) (by scalar_tac) (by scalar_tac) (by assumption)
          (by scalar_tac), by scalar_tac⟩)
      | (refine ⟨LazyInv1.reject hinv (by assumption) (by scalar_tac) (by scalar_tac)
          (by scalar_tac) (by scalar_tac) (by assumption), by scalar_tac⟩)
  · exact hinv
@[local step]
theorem lazy1_loop_spec {H : Std.Usize} (input : Slice Std.U8) (lazy : Std.Usize) (km : Std.U32)
    (p : Std.Usize)
    (head : Array Std.U32 H) (lim pre_slot pre_c : Std.Usize) (pre_w : Std.U64)
    (l d ins : Std.Usize) (go : Std.U32)
    (hlim : lim.val + 8 = input.length) (hH : 0 < H.val)
    (hm : MatchAt input p.val l.val d.val)
    (hB : HeadBound head (p.val + 1)) (hplim : p.val < lim.val) (hins : ins.val ≤ p.val + 2)
    (hps : pre_slot.val < H.val) (hpc : pre_c.val ≤ p.val + 1)
    (hpw : pre_w.val = word8 input pre_c.val) :
    slot.pc_run1_loop0_loop0 input lazy km p head lim pre_slot pre_c pre_w l d ins go ⦃ fun r =>
      MatchAt input r.1.val r.2.2.2.2.2.1.val r.2.2.2.2.2.2.1.val ∧
      HeadBound r.2.1 (r.1.val + r.2.2.2.2.2.1.val) ∧ r.1.val < lim.val ∧
      r.2.2.2.2.2.2.2.val ≤ r.1.val + 2 ∧ 3 ≤ r.2.2.2.2.2.1.val ∧
      r.2.2.1.val < H.val ∧ r.2.2.2.1.val ≤ r.1.val + 1 ∧
      r.2.2.2.2.1.val = word8 input r.2.2.2.1.val ∧ p.val ≤ r.1.val ⦄ := by
  apply Std.WP.spec_mono (lazy1_loop_inv input lazy km p head lim pre_slot pre_c pre_w l d ins go
    p.val hlim hH ⟨hm, hB, hplim, hins, hps, hpc, hpw, le_refl _⟩)
  rintro ⟨p', head', ps', pc', pw', l', d', ins'⟩ ⟨hm', hB', hplim', hins', hps', hpc', hpw', hP'⟩
  exact ⟨hm', HeadBound.mono hB' (by have := hm'.1; omega), hplim', hins', hm'.1, hps', hpc',
    hpw', hP'⟩
@[local step]
theorem tail1_loop1_spec (input : Slice Std.U8) (out : Slice Std.U32) (n nt p : Std.Usize)
    (hn : n.val = input.length) (hdec : Dec input out nt.val p.val) :
    slot.pc_run1_loop1 input out n nt p ⦃ fun r => r.1.val ≤ input.length ∧
      r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := C12590! slot.pc_run1_loop1 slot.pc_run1_loop1.body
@[local step]
theorem tail1_loop2_spec (input : Slice Std.U8) (out : Slice Std.U32) (n nt p : Std.Usize)
    (hn : n.val = input.length) (hdec : Dec input out nt.val p.val) :
    slot.pc_run1_loop2 input out n nt p ⦃ fun r => r.1.val ≤ input.length ∧
      r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := C12590! slot.pc_run1_loop2 slot.pc_run1_loop2.body
def MainInv1 (input : Slice Std.U8) (L : Nat) (out : Slice Std.U32) (nt ls p : Nat)
    {N : Std.Usize} (head : Array Std.U32 N) (miss ps pc pw : Nat) : Prop :=
  Dec input out nt ls ∧ out.length = L ∧ ls ≤ p ∧ HeadBound head p ∧ miss ≤ p ∧ ps < N.val ∧
    pc ≤ p ∧ pw = word8 input pc
theorem MainInv1.mk' {input : Slice Std.U8} {L : Nat} {out : Slice Std.U32}
    {nt ls ls' p m B ps pc pw : Nat} {N : Std.Usize} {head : Array Std.U32 N}
    (hdec : Dec input out nt ls') (hls : ls' = ls) (hlen : out.length = L) (hlsp : ls ≤ p)
    (hB : HeadBound head B) (hBp : B ≤ p) (hm : m ≤ p) (hps : ps < N.val) (hpc : pc ≤ p)
    (hpw : pw = word8 input pc) : MainInv1 input L out nt ls p head m ps pc pw := by
  subst hls
  exact ⟨hdec, hlen, hlsp, HeadBound.mono hB hBp, hm, hps, hpc, hpw⟩
set_option maxHeartbeats 16000000 in
theorem main1_loop_spec {H : Std.Usize} (input : Slice Std.U8) (out : Slice Std.U32)
    (skip lazy skcap : Std.Usize) (km : Std.U32) (nt ls p : Std.Usize) (head : Array Std.U32 H)
    (lim miss fuel pre_slot pre_c : Std.Usize) (pre_w : Std.U64) (L : Nat)
    (hlim : lim.val + 8 = input.length) (hskip : skip.val < 32) (hH : 0 < H.val)
    (hinv : MainInv1 input L out nt.val ls.val p.val head miss.val pre_slot.val pre_c.val
      pre_w.val) :
    slot.pc_run1_loop0 input out skip lazy skcap km nt ls p head lim miss fuel pre_slot pre_c pre_w
      ⦃ fun r => Dec input r.1 r.2.1.val r.2.2.val ∧ r.1.length = L ⦄ := by
  rw [slot.pc_run1_loop0]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  apply Std.loop.spec_decr_nat
    (measure := fun r => r.2.2.2.2.2.2.1.val)
    (inv := fun r => MainInv1 input L r.1 r.2.1.val r.2.2.1.val r.2.2.2.1.val r.2.2.2.2.1
      r.2.2.2.2.2.1.val r.2.2.2.2.2.2.2.1.val r.2.2.2.2.2.2.2.2.1.val r.2.2.2.2.2.2.2.2.2.val)
  · rintro ⟨out, nt, ls, p, head, miss, fuel, pre_slot, pre_c, pre_w⟩ hinv
    simp only at hinv
    have hinv' := hinv
    obtain ⟨hdec, hL, hlsp, hB, hmiss, hps, hpc, hpw⟩ := hinv'
    simp only [slot.pc_run1_loop0.body]
    step*
    all_goals try (obtain ⟨i4, i5, i6⟩ := ae; dsimp only at *; step*)
    all_goals first
      | exact FoundAt.real (by assumption) (by scalar_tac)
      | exact HeadBound.mono (by assumption) (by scalar_tac)
      | (refine ⟨MainInv1.mk' (by assumption) (by scalar_tac) (by scalar_tac) (by scalar_tac)
          (by assumption) (by scalar_tac) (by scalar_tac) (by scalar_tac) (by scalar_tac)
          (by assumption), by scalar_tac⟩)
  · exact hinv
@[local step]
theorem main1_loop_spec' {H : Std.Usize} (input : Slice Std.U8) (out : Slice Std.U32)
    (skip lazy skcap : Std.Usize) (km : Std.U32) (nt ls p : Std.Usize) (head : Array Std.U32 H)
    (lim miss fuel pre_slot pre_c : Std.Usize) (pre_w : Std.U64)
    (hlim : lim.val + 8 = input.length) (hskip : skip.val < 32) (hH : 0 < H.val)
    (hdec : Dec input out nt.val ls.val) (hlsp : ls.val ≤ p.val) (hB : HeadBound head p.val)
    (hmiss : miss.val ≤ p.val) (hps : pre_slot.val < H.val) (hpc : pre_c.val ≤ p.val)
    (hpw : pre_w.val = word8 input pre_c.val) :
    slot.pc_run1_loop0 input out skip lazy skcap km nt ls p head lim miss fuel pre_slot pre_c pre_w
      ⦃ fun r => Dec input r.1 r.2.1.val r.2.2.val ∧ r.1.length = out.length ⦄ :=
  main1_loop_spec input out skip lazy skcap km nt ls p head lim miss fuel pre_slot pre_c pre_w
    out.length hlim hskip hH ⟨hdec, rfl, hlsp, hB, hmiss, hps, hpc, hpw⟩
set_option hygiene false in
local notation "C12599!" q0__:max => (by
  rw [q0__]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  have hB0 : HeadBound (Std.Array.repeat H 0#u32) 0 := HeadBound.init H
  have hdec0 : Dec input out (0#usize).val (0#usize).val := Dec.init input out hlen
  step*)
theorem run1_spec (H : Std.Usize) (input : Slice Std.U8) (out : Slice Std.U32)
    (skip lazy skcap : Std.Usize) (km : Std.U32) (hlen : input.length ≤ out.length) (hH : 0 < H.val)
    (hskip : skip.val < 32) :
    slot.pc_run1 H input out skip lazy skcap km ⦃ fun r => r.1.val ≤ input.length ∧
      r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := C12599! slot.pc_run1
@[local step]
theorem f_link_spec {H : Std.Usize} (head : Array Std.U32 H) (prev : Array Std.U16 32768#usize)
    (a i : Std.Usize) (B : Nat) (hB : HeadBound head B) (ha : a.val < H.val) (hi : i.val < B + 1) :
    slot.pc_f_link head prev a i ⦃ fun r => HeadBound r.1 B ⦄ := by
  rw [slot.pc_f_link]
  step*
  repeat' (split <;> step*)
  all_goals first
    | exact HeadBound.update hB (by assumption) (by omega) (by assumption)
    | scalar_tac
theorem MatchAt.of_try {s : Slice Std.U8} {p c2 d2 i m : Std.Usize}
    (hd : d2 = core.num.Usize.wrapping_sub p c2) (hi : i = core.num.Usize.wrapping_sub d2 1#usize)
    (hlt : i < 32768#usize) (hmm : Matches s c2.val p.val m.val) (hc2 : c2.val ≤ p.val)
    (hm3 : 3 ≤ m.val) (hl : m.val ≤ 258) (hpl : p.val + m.val ≤ s.length) :
    MatchAt s p.val m.val d2.val := by
  obtain ⟨hdv, hd1, hd2⟩ := dist_of_wrapping hc2 hd hi hlt
  refine ⟨hm3, hl, hpl, hd1, hd2, by omega, ?_⟩
  rw [show p.val - d2.val = c2.val by omega]
  exact hmm
@[local step]
theorem f_try_spec (s : Slice Std.U8) (c c2 p l d minl : Std.Usize) (hc : c.val ≤ p.val)
    (hm : MatchAt s p.val l.val d.val) :
    slot.pc_f_try s c c2 p l d minl ⦃ fun r => MatchAt s p.val r.1.val r.2.val ⦄ := by
  rw [slot.pc_f_try]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  have hm' := hm
  obtain ⟨h3, h258, hpl, hd1, hd32, hdp, _⟩ := hm'
  step*
  repeat' (split <;> step*)
  all_goals first
    | exact hm
    | exact LZ77.Matches.zero _ _ _
    | exact MatchAt.of_try (by assumption) (by assumption) (by assumption) (by assumption)
        (by scalar_tac) (by scalar_tac) (by scalar_tac) (by scalar_tac)
@[local step]
theorem f_deepen_spec (s : Slice Std.U8) (prev : Array Std.U16 32768#usize)
    (c c2 p l d dp minl : Std.Usize) (hc : c.val ≤ p.val) (hm : MatchAt s p.val l.val d.val) :
    slot.pc_f_deepen s prev c c2 p l d dp minl ⦃ fun r => MatchAt s p.val r.1.val r.2.val ⦄ := by
  rw [slot.pc_f_deepen]
  step*
  all_goals try (obtain ⟨g1, g2⟩ := g; dsimp only at *; step*)
@[local step]
theorem f_record3_loop0_spec {H : Std.Usize} (s : Slice Std.U8) (head : Array Std.U32 H)
    (prev : Array Std.U16 32768#usize) (km : Std.U32) (ins stop : Std.Usize) (B : Nat)
    (hB : HeadBound head B) (hsB : stop.val < B + 1) (hs4 : stop.val + 4 ≤ Std.Usize.max)
    (hH : 0 < H.val) :
    slot.pc_f_record3_loop0 s head prev km ins stop ⦃ fun r =>
      HeadBound r.1 B ∧ (r.2.2.val ≤ ins.val ∨ r.2.2.val ≤ stop.val) ⦄ := C12586! slot.pc_f_record3_loop0 slot.pc_f_record3_loop0.body
@[local step]
theorem f_record3_loop1_spec {H : Std.Usize} (s : Slice Std.U8) (head : Array Std.U32 H)
    (prev : Array Std.U16 32768#usize) («end» lim : Std.Usize) (km : Std.U32) (ins : Std.Usize)
    (B : Nat) (hB : HeadBound head B) (heB : «end».val < B + 1)
    (hl4 : lim.val + 4 ≤ Std.Usize.max) (hH : 0 < H.val) :
    slot.pc_f_record3_loop1 s head prev «end» lim km ins ⦃ fun r => HeadBound r.1 B ⦄ := by
  rw [slot.pc_f_record3_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun r => «end».val - r.2.2.val)
    (inv := fun r => HeadBound r.1 B)
  · rintro ⟨head, prev, ins'⟩ hB
    simp only at hB
    simp only [slot.pc_f_record3_loop1.body]
    step*
  · exact hB
@[local step]
theorem f_record3_spec {H : Std.Usize} (s : Slice Std.U8) (head : Array Std.U32 H)
    (prev : Array Std.U16 32768#usize) (ins0 a0 «end» lim : Std.Usize) (km : Std.U32) (B : Nat)
    (hB : HeadBound head B) (heB : «end».val < B + 1) (hlim : lim.val + 8 = s.length)
    (hins : ins0.val ≤ lim.val + 1) (hH : 0 < H.val) :
    slot.pc_f_record3 s head prev ins0 a0 «end» lim km ⦃ fun r => HeadBound r.1 B ⦄ := by
  rw [slot.pc_f_record3]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  step*
  repeat' (split <;> step*)
  all_goals try (obtain ⟨xh, xp⟩ := x; dsimp only at *)
  all_goals try step*
  repeat' (split <;> step*)
theorem lazy1c_loop_inv {H : Std.Usize} (input : Slice Std.U8) (lazy : Std.Usize) (km : Std.U32)
    (p : Std.Usize) (head : Array Std.U32 H) (prev : Array Std.U16 32768#usize)
    (lim pre_slot pre_c : Std.Usize) (pre_w : Std.U64)
    (l d ins : Std.Usize) (go : Std.U32) (P0 : Nat)
    (hlim : lim.val + 8 = input.length) (hH : 0 < H.val)
    (hinv : LazyInv1 input lim.val P0 p.val head pre_slot.val pre_c.val pre_w.val l.val d.val
      ins.val) :
    slot.pc_run1c_loop0_loop0 input lazy km p head prev lim pre_slot pre_c pre_w l d ins go ⦃ fun r =>
      LazyInv1 input lim.val P0 r.1.val r.2.1 r.2.2.2.1.val r.2.2.2.2.1.val r.2.2.2.2.2.1.val
        r.2.2.2.2.2.2.1.val r.2.2.2.2.2.2.2.1.val r.2.2.2.2.2.2.2.2.val ⦄ := by
  rw [slot.pc_run1c_loop0_loop0]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  apply Std.loop.spec_decr_nat
    (measure := fun r => lim.val - r.1.val + r.2.2.2.2.2.2.2.2.2.val)
    (inv := fun r => LazyInv1 input lim.val P0 r.1.val r.2.1 r.2.2.2.1.val r.2.2.2.2.1.val
      r.2.2.2.2.2.1.val r.2.2.2.2.2.2.1.val r.2.2.2.2.2.2.2.1.val r.2.2.2.2.2.2.2.2.1.val)
  · rintro ⟨p, head, prev, pre_slot, pre_c, pre_w, l, d, ins, go⟩ hinv
    simp only at hinv
    have hinv' := hinv
    obtain ⟨⟨h3, h258, hpl, hd1, hd32, hdp, _⟩, hB, hplim, hins, hslot, hpc, hpw, hP⟩ := hinv'
    simp only [slot.pc_run1c_loop0_loop0.body]
    step*
    all_goals first
      | (refine ⟨LazyInv1.accept (by assumption) (by scalar_tac) (by assumption) (by scalar_tac)
          (by scalar_tac) (by scalar_tac) (by scalar_tac) (by scalar_tac) (by assumption)
          (by scalar_tac), by scalar_tac⟩)
      | (refine ⟨LazyInv1.reject hinv (by assumption) (by scalar_tac) (by scalar_tac)
          (by scalar_tac) (by scalar_tac) (by assumption), by scalar_tac⟩)
  · exact hinv
@[local step]
theorem lazy1c_loop_spec {H : Std.Usize} (input : Slice Std.U8) (lazy : Std.Usize) (km : Std.U32)
    (p : Std.Usize) (head : Array Std.U32 H) (prev : Array Std.U16 32768#usize)
    (lim pre_slot pre_c : Std.Usize) (pre_w : Std.U64)
    (l d ins : Std.Usize) (go : Std.U32)
    (hlim : lim.val + 8 = input.length) (hH : 0 < H.val)
    (hm : MatchAt input p.val l.val d.val)
    (hB : HeadBound head (p.val + 1)) (hplim : p.val < lim.val) (hins : ins.val ≤ p.val + 2)
    (hps : pre_slot.val < H.val) (hpc : pre_c.val ≤ p.val + 1)
    (hpw : pre_w.val = word8 input pre_c.val) :
    slot.pc_run1c_loop0_loop0 input lazy km p head prev lim pre_slot pre_c pre_w l d ins go ⦃ fun r =>
      MatchAt input r.1.val r.2.2.2.2.2.2.1.val r.2.2.2.2.2.2.2.1.val ∧
      HeadBound r.2.1 (r.1.val + r.2.2.2.2.2.2.1.val) ∧ r.1.val < lim.val ∧
      r.2.2.2.2.2.2.2.2.val ≤ r.1.val + 2 ∧ 3 ≤ r.2.2.2.2.2.2.1.val ∧
      r.2.2.2.1.val < H.val ∧ r.2.2.2.2.1.val ≤ r.1.val + 1 ∧
      r.2.2.2.2.2.1.val = word8 input r.2.2.2.2.1.val ∧ p.val ≤ r.1.val ⦄ := by
  apply Std.WP.spec_mono (lazy1c_loop_inv input lazy km p head prev lim pre_slot pre_c pre_w l d
    ins go p.val hlim hH ⟨hm, hB, hplim, hins, hps, hpc, hpw, le_refl _⟩)
  rintro ⟨p', head', prev', ps', pc', pw', l', d', ins'⟩
    ⟨hm', hB', hplim', hins', hps', hpc', hpw', hP'⟩
  exact ⟨hm', HeadBound.mono hB' (by have := hm'.1; omega), hplim', hins', hm'.1, hps', hpc',
    hpw', hP'⟩
@[local step]
theorem tail1c_loop1_spec (input : Slice Std.U8) (out : Slice Std.U32) (n nt p : Std.Usize)
    (hn : n.val = input.length) (hdec : Dec input out nt.val p.val) :
    slot.pc_run1c_loop1 input out n nt p ⦃ fun r => r.1.val ≤ input.length ∧
      r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := C12590! slot.pc_run1c_loop1 slot.pc_run1c_loop1.body
@[local step]
theorem tail1c_loop2_spec (input : Slice Std.U8) (out : Slice Std.U32) (n nt p : Std.Usize)
    (hn : n.val = input.length) (hdec : Dec input out nt.val p.val) :
    slot.pc_run1c_loop2 input out n nt p ⦃ fun r => r.1.val ≤ input.length ∧
      r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := C12590! slot.pc_run1c_loop2 slot.pc_run1c_loop2.body
set_option maxHeartbeats 16000000 in
theorem main1c_loop_spec {H : Std.Usize} (input : Slice Std.U8) (out : Slice Std.U32)
    (skip lazy skcap : Std.Usize) (km : Std.U32) (dp minl nt ls p : Std.Usize)
    (head : Array Std.U32 H) (prev : Array Std.U16 32768#usize)
    (lim miss fuel pre_slot pre_c : Std.Usize) (pre_w : Std.U64) (L : Nat)
    (hlim : lim.val + 8 = input.length) (hskip : skip.val < 32) (hH : 0 < H.val)
    (hinv : MainInv1 input L out nt.val ls.val p.val head miss.val pre_slot.val pre_c.val
      pre_w.val) :
    slot.pc_run1c_loop0 input out skip lazy skcap km dp minl nt ls p head prev lim miss fuel pre_slot
      pre_c pre_w ⦃ fun r => Dec input r.1 r.2.1.val r.2.2.val ∧ r.1.length = L ⦄ := by
  rw [slot.pc_run1c_loop0]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  apply Std.loop.spec_decr_nat
    (measure := fun r => r.2.2.2.2.2.2.2.1.val)
    (inv := fun r => MainInv1 input L r.1 r.2.1.val r.2.2.1.val r.2.2.2.1.val r.2.2.2.2.1
      r.2.2.2.2.2.2.1.val r.2.2.2.2.2.2.2.2.1.val r.2.2.2.2.2.2.2.2.2.1.val
      r.2.2.2.2.2.2.2.2.2.2.val)
  · rintro ⟨out, nt, ls, p, head, prev, miss, fuel, pre_slot, pre_c, pre_w⟩ hinv
    simp only at hinv
    have hinv' := hinv
    obtain ⟨hdec, hL, hlsp, hB, hmiss, hps, hpc, hpw⟩ := hinv'
    simp only [slot.pc_run1c_loop0.body]
    step*
    all_goals try (obtain ⟨i8, i9, i10⟩ := ae; dsimp only at *; step*)
    all_goals first
      | exact FoundAt.real (by assumption) (by scalar_tac)
      | exact HeadBound.mono (by assumption) (by scalar_tac)
      | (refine ⟨MainInv1.mk' (by assumption) (by scalar_tac) (by scalar_tac) (by scalar_tac)
          (by assumption) (by scalar_tac) (by scalar_tac) (by scalar_tac) (by scalar_tac)
          (by assumption), by scalar_tac⟩)
  · exact hinv
@[local step]
theorem main1c_loop_spec' {H : Std.Usize} (input : Slice Std.U8) (out : Slice Std.U32)
    (skip lazy skcap : Std.Usize) (km : Std.U32) (dp minl nt ls p : Std.Usize)
    (head : Array Std.U32 H) (prev : Array Std.U16 32768#usize)
    (lim miss fuel pre_slot pre_c : Std.Usize) (pre_w : Std.U64)
    (hlim : lim.val + 8 = input.length) (hskip : skip.val < 32) (hH : 0 < H.val)
    (hdec : Dec input out nt.val ls.val) (hlsp : ls.val ≤ p.val) (hB : HeadBound head p.val)
    (hmiss : miss.val ≤ p.val) (hps : pre_slot.val < H.val) (hpc : pre_c.val ≤ p.val)
    (hpw : pre_w.val = word8 input pre_c.val) :
    slot.pc_run1c_loop0 input out skip lazy skcap km dp minl nt ls p head prev lim miss fuel pre_slot
      pre_c pre_w ⦃ fun r => Dec input r.1 r.2.1.val r.2.2.val ∧ r.1.length = out.length ⦄ :=
  main1c_loop_spec input out skip lazy skcap km dp minl nt ls p head prev lim miss fuel pre_slot
    pre_c pre_w out.length hlim hskip hH ⟨hdec, rfl, hlsp, hB, hmiss, hps, hpc, hpw⟩
theorem run1c_spec (H : Std.Usize) (input : Slice Std.U8) (out : Slice Std.U32)
    (skip lazy skcap : Std.Usize) (km : Std.U32) (dp minl : Std.Usize)
    (hlen : input.length ≤ out.length) (hH : 0 < H.val) (hskip : skip.val < 32) :
    slot.pc_run1c H input out skip lazy skcap km dp minl ⦃ fun r => r.1.val ≤ input.length ∧
      r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := C12599! slot.pc_run1c
end PC
@[local step]
theorem p125_row0_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.p125_row0 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.p125_row0]
 exact EO.EA.main_part_spec _ _ _ _ _ input out _ _ _ hlen (by simp) (by simp) (by simp [LZ77.toks, LZ77.decode])
@[local step]
theorem p125_row1_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.p125_row1 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.p125_row1]
 exact U118_MAIN.run_spec _ _ _ _ _ _ _ _ _ _ _ _ _ _ input out hlen (by simp) (by simp) (by simp) (by simp) (by simp) (by simp) (by simp)
@[local step]
theorem p125_row2_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.p125_row2 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.p125_row2]
 step*
@[local step]
theorem p125_row3_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.p125_row3 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.p125_row3]
 exact PC.run1c_spec _ input out _ _ _ _ _ _ hlen (by simp) (by simp)
@[local step]
theorem p125_row4_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.p125_row4 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.p125_row4]
 exact PC.run1c_spec _ input out _ _ _ _ _ _ hlen (by simp) (by simp)
@[local step]
theorem p125_row5_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.p125_row5 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := C12593! slot.p125_row5
@[local step]
theorem p125_row6_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.p125_row6 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.p125_row6]
 exact PC.run1_spec _ input out _ _ _ _ hlen (by simp) (by simp)
@[local step]
theorem p125_row7_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.p125_row7 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.p125_row7]
 exact C107.cached_spec _ _ input out hlen
@[local step]
theorem p125_row8_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.p125_row8 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.p125_row8]
 exact N70.n_run_spec _ _ _ _ _ _ _ _ _ input out hlen
@[local step]
theorem p125_row9_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.p125_row9 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.p125_row9]
 step*
@[local step]
theorem p125_row10_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.p125_row10 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := C12593! slot.p125_row10
@[local step]
theorem p125_row11_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.p125_row11 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.p125_row11]
 exact N70.n_run_spec _ _ _ _ _ _ _ _ _ input out hlen
@[local step]
theorem p125_row12_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.p125_row12 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := C12593! slot.p125_row12
@[local step]
theorem p125_row13_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.p125_row13 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := C12593! slot.p125_row13
@[local step]
theorem p125_row14_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.p125_row14 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.p125_row14]
 exact N70.n_run_spec _ _ _ _ _ _ _ _ _ input out hlen
@[local step]
theorem p125_row15_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.p125_row15 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.p125_row15]
 exact PC.run1c_spec _ input out _ _ _ _ _ _ hlen (by simp) (by simp)
@[local step]
theorem p125_row16_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.p125_row16 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.p125_row16]
 exact PC.run1c_spec _ input out _ _ _ _ _ _ hlen (by simp) (by simp)
@[local step]
theorem p125_row17_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.p125_row17 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.p125_row17]
 exact PC.run1c_spec _ input out _ _ _ _ _ _ hlen (by simp) (by simp)
@[local step]
theorem p125_row18_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.p125_row18 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.p125_row18]
 exact PC.run1c_spec _ input out _ _ _ _ _ _ hlen (by simp) (by simp)
@[local step]
theorem p125_row19_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.p125_row19 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.p125_row19]
 exact PC.run1c_spec _ input out _ _ _ _ _ _ hlen (by simp) (by simp)
@[local step]
theorem p125_row20_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.p125_row20 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.p125_row20]
 exact PC.run1c_spec _ input out _ _ _ _ _ _ hlen (by simp) (by simp)
@[local step]
theorem p125_row21_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.p125_row21 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.p125_row21]
 exact PC.run1c_spec _ input out _ _ _ _ _ _ hlen (by simp) (by simp)
@[local step]
theorem p125_row22_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.p125_row22 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.p125_row22]
 exact PC.run1c_spec _ input out _ _ _ _ _ _ hlen (by simp) (by simp)
@[local step]
theorem p125_row23_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.p125_row23 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.p125_row23]
 exact PC.run1c_spec _ input out _ _ _ _ _ _ hlen (by simp) (by simp)
@[local step]
theorem p125_row24_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.p125_row24 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.p125_row24]
 exact PC.run1c_spec _ input out _ _ _ _ _ _ hlen (by simp) (by simp)
@[local step]
theorem p125_row25_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.p125_row25 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.p125_row25]
 exact PC.run1c_spec _ input out _ _ _ _ _ _ hlen (by simp) (by simp)
@[local step]
theorem p125_row26_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.p125_row26 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.p125_row26]
 exact PC.run1c_spec _ input out _ _ _ _ _ _ hlen (by simp) (by simp)
@[local step]
theorem p125_row27_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.p125_row27 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.p125_row27]
 exact EO.EA.main_part_spec _ _ _ _ _ input out _ _ _ hlen (by simp) (by simp) (by simp [LZ77.toks, LZ77.decode])
@[local step]
theorem p125_row28_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.p125_row28 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.p125_row28]
 exact EO.EA.main_part_spec _ _ _ _ _ input out _ _ _ hlen (by simp) (by simp) (by simp [LZ77.toks, LZ77.decode])
@[local step]
theorem p125_row29_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.p125_row29 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.p125_row29]
 exact EO.EA.main_part_spec _ _ _ _ _ input out _ _ _ hlen (by simp) (by simp) (by simp [LZ77.toks, LZ77.decode])
@[local step]
theorem p125_row30_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.p125_row30 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.p125_row30]
 exact EO.EA.main_part_spec _ _ _ _ _ input out _ _ _ hlen (by simp) (by simp) (by simp [LZ77.toks, LZ77.decode])
@[local step]
theorem p125_row31_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.p125_row31 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.p125_row31]
 exact EO.EA.main_part_spec _ _ _ _ _ input out _ _ _ hlen (by simp) (by simp) (by simp [LZ77.toks, LZ77.decode])
@[local step]
theorem p125_row32_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.p125_row32 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.p125_row32]
 exact EO.EA.main_part_spec _ _ _ _ _ input out _ _ _ hlen (by simp) (by simp) (by simp [LZ77.toks, LZ77.decode])
@[local step]
theorem p125_row33_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.p125_row33 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.p125_row33]
 exact EO.EA.main_part_spec _ _ _ _ _ input out _ _ _ hlen (by simp) (by simp) (by simp [LZ77.toks, LZ77.decode])
@[local step]
theorem p125_row34_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.p125_row34 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.p125_row34]
 exact EO.EA.main_part_spec _ _ _ _ _ input out _ _ _ hlen (by simp) (by simp) (by simp [LZ77.toks, LZ77.decode])
@[local step]
theorem p125_row35_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.p125_row35 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.p125_row35]
 exact EO.EA.main_part_spec _ _ _ _ _ input out _ _ _ hlen (by simp) (by simp) (by simp [LZ77.toks, LZ77.decode])
@[local step]
theorem p125_row36_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.p125_row36 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.p125_row36]
 exact EO.EA.main_part_spec _ _ _ _ _ input out _ _ _ hlen (by simp) (by simp) (by simp [LZ77.toks, LZ77.decode])
@[local step]
theorem p125_row37_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.p125_row37 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.p125_row37]
 exact EO.EA.main_part_spec _ _ _ _ _ input out _ _ _ hlen (by simp) (by simp) (by simp [LZ77.toks, LZ77.decode])
@[local step]
theorem p125_row38_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.p125_row38 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.p125_row38]
 exact EO.EA.main_part_spec _ _ _ _ _ input out _ _ _ hlen (by simp) (by simp) (by simp [LZ77.toks, LZ77.decode])
@[local step]
theorem p125_row39_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.p125_row39 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.p125_row39]
 exact PC.run1_spec _ input out _ _ _ _ hlen (by simp) (by simp)
@[local step]
theorem p125_row40_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.p125_row40 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.p125_row40]
 exact PC.run1_spec _ input out _ _ _ _ hlen (by simp) (by simp)
@[local step]
theorem p125_row41_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.p125_row41 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.p125_row41]
 exact PC.run1_spec _ input out _ _ _ _ hlen (by simp) (by simp)
@[local step]
theorem p125_row42_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.p125_row42 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.p125_row42]
 exact PC.run1_spec _ input out _ _ _ _ hlen (by simp) (by simp)
@[local step]
theorem p125_row43_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.p125_row43 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.p125_row43]
 exact PC.run1_spec _ input out _ _ _ _ hlen (by simp) (by simp)
@[local step]
theorem p125_row44_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.p125_row44 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.p125_row44]
 exact PC.run1_spec _ input out _ _ _ _ hlen (by simp) (by simp)
@[local step]
theorem p125_row45_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.p125_row45 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.p125_row45]
 exact PC.run1_spec _ input out _ _ _ _ hlen (by simp) (by simp)
@[local step]
theorem p125_row46_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.p125_row46 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.p125_row46]
 exact PC.run1_spec _ input out _ _ _ _ hlen (by simp) (by simp)
@[local step]
theorem p125_row47_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.p125_row47 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.p125_row47]
 exact PC.run1_spec _ input out _ _ _ _ hlen (by simp) (by simp)
@[local step]
theorem p125_row48_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.p125_row48 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.p125_row48]
 exact PC.run1_spec _ input out _ _ _ _ hlen (by simp) (by simp)
@[local step]
theorem p125_row49_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.p125_row49 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.p125_row49]
 exact PC.run1_spec _ input out _ _ _ _ hlen (by simp) (by simp)
@[local step]
theorem p125_row50_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.p125_row50 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.p125_row50]
 exact PC.run1_spec _ input out _ _ _ _ hlen (by simp) (by simp)
@[local step]
theorem p125_row51_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.p125_row51 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.p125_row51]
 exact PC.run1_spec _ input out _ _ _ _ hlen (by simp) (by simp)
set_option hygiene false in
local notation "Q496M1!" => (by
  intro j hj
  rw [Std.Array.repeat_val, List.getElem!_eq_getElem?_getD,
    List.getElem?_replicate_of_lt (by simpa using hj)]
  rfl)
set_option hygiene false in
local notation "Q496M2!" => (by
  have := h a.val (by simpa using ha)
  rw [getElem!_pos cnt.val a.val ha, ← hx] at this
  exact this)
set_option hygiene false in
local notation "Q496M3!" => (by
  have hl : i.val < cnt.val.length := by simp; omega
  have := Std.Array.index_usize_spec cnt i (by simpa using hl)
  apply Std.WP.spec_mono this
  intro x hx
  refine ⟨by rw [getElem!_pos cnt.val i.val hl]; exact hx, CntBound.get h i x hl hx⟩)
set_option hygiene false in
local notation "Q496M4!" => (by
  intro j hj
  rw [Std.Array.set_val_eq]
  by_cases hja : a.val = j
  · subst hja
    have hlen : a.val < cnt.val.length := by simp; omega
    rw [List.getElem!_eq_getElem?_getD, List.getElem?_set_self hlen]
    exact hv
  · rw [List.getElem!_eq_getElem?_getD, List.getElem?_set_ne hja, ← List.getElem!_eq_getElem?_getD]
    exact le_trans (h j hj) (by omega))
set_option hygiene false in
local notation "Q496M5!" => (by
  rw [ha, ht1]
  exact CntBound.update hc x v hv)
set_option hygiene false in
local notation "Q496M6!" => (by
  have := u8_lt (input.val[p]!); have := u8_lt (input.val[p+1]!)
  have := u8_lt (input.val[p+2]!); have := u8_lt (input.val[p+3]!)
  have := u8_lt (input.val[p+4]!); have := u8_lt (input.val[p+5]!)
  have := u8_lt (input.val[p+6]!); have := u8_lt (input.val[p+7]!)
  simp only [word8]
  rcases (show k = 0 ∨ k = 1 ∨ k = 2 ∨ k = 3 ∨ k = 4 ∨ k = 5 ∨ k = 6 ∨ k = 7 by omega) with
    rfl | rfl | rfl | rfl | rfl | rfl | rfl | rfl <;> simp only [Nat.add_zero, Nat.pow_zero, Nat.pow_succ, Nat.one_mul,
    Nat.sub_self, Nat.reduceSub] <;> omega)
set_option hygiene false in
local notation "Q496M7!" => (by
  intro k hk
  have e : (256 : Nat) ^ (7 - k) = 2 ^ (64 - 8 * d) * 2 ^ (8 * (d - 1 - k)) := by
    rw [← pow_add, show (256 : Nat) = 2 ^ 8 by norm_num, ← pow_mul]
    congr 1; omega
  have key : word8 input a / 256 ^ (7 - k) = word8 input b / 256 ^ (7 - k) := by
    rw [e, ← Nat.div_div_eq_div_mul, ← Nat.div_div_eq_div_mul, h]
  have ha := word8_digit input a k (by omega)
  have hb := word8_digit input b k (by omega)
  rw [key] at ha
  scalar_tac)
set_option hygiene false in
local notation "Q496M8!" => (by
  intro k hk
  by_cases hkl : k < l
  · exact h k hkl
  · have := word8_prefix input (a + l) (b + l) d hd hw (k - l) (by omega)
    rw [show b + l + (k - l) = b + k by omega, show a + l + (k - l) = a + k by omega] at this
    exact this)
set_option hygiene false in
local notation "Q496M9!" => (by
  have h := Nat.two_pow_add_eq_or_of_lt ht (x / 2 ^ m)
  have hx' : 2 ^ m * (x / 2 ^ m) = x := by
    have := Nat.div_add_mod x (2 ^ m); omega
  rw [hx'] at h
  exact h.symm)
set_option hygiene false in
local notation "Q496M10!" => (by
  rw [Nat.shiftLeft_eq, U64.size_def]
  apply Nat.mod_eq_of_lt
  have : 2 ^ k ≤ 2 ^ 56 := Nat.pow_le_pow_right (by norm_num) hk
  have : x * 2 ^ k < 256 * 2 ^ 56 := by
    calc x * 2 ^ k < 256 * 2 ^ k := by
          apply Nat.mul_lt_mul_of_pos_right hx (Nat.two_pow_pos _)
      _ ≤ 256 * 2 ^ 56 := Nat.mul_le_mul_left _ this
  simp only [U64.numBits] at *
  omega)
set_option hygiene false in
local notation "Q496M11!" => (by
  rw [shl_byte 56 ha (by norm_num), shl_byte 48 hb (by norm_num), shl_byte 40 hc (by norm_num),
    shl_byte 32 hd (by norm_num), shl_byte 24 he (by norm_num), shl_byte 16 hf (by norm_num),
    shl_byte 8 hg (by norm_num)]
  rw [or_eq_add_of_mod 56 (x := a * 2^56) (t := b * 2^48) (by omega) (by omega)]
  rw [or_eq_add_of_mod 48 (x := a * 2^56 + b * 2^48) (t := c * 2^40) (by omega) (by omega)]
  rw [or_eq_add_of_mod 40 (x := a * 2^56 + b * 2^48 + c * 2^40) (t := d * 2^32) (by omega)
    (by omega)]
  rw [or_eq_add_of_mod 32 (x := a * 2^56 + b * 2^48 + c * 2^40 + d * 2^32) (t := e * 2^24)
    (by omega) (by omega)]
  rw [or_eq_add_of_mod 24 (x := a * 2^56 + b * 2^48 + c * 2^40 + d * 2^32 + e * 2^24)
    (t := f * 2^16) (by omega) (by omega)]
  rw [or_eq_add_of_mod 16
    (x := a * 2^56 + b * 2^48 + c * 2^40 + d * 2^32 + e * 2^24 + f * 2^16)
    (t := g * 2^8) (by omega) (by omega)]
  rw [or_eq_add_of_mod 8
    (x := a * 2^56 + b * 2^48 + c * 2^40 + d * 2^32 + e * 2^24 + f * 2^16 + g * 2^8)
    (t := h) (by omega) (by omega)])
set_option hygiene false in
local notation "Q496M12!" q0__:max => (by
  rw [q0__]
  step*
  simp only [← getElem!_pos] at *
  simp_all only [UScalar.val_or, U8.cast_U64_val_eq]
  rw [be8_nat (u8_lt _) (u8_lt _) (u8_lt _) (u8_lt _) (u8_lt _) (u8_lt _) (u8_lt _) (u8_lt _)]
  simp only [word8])
set_option hygiene false in
local notation "Q496M13!" => (by
  have : a ^^^ (a ^^^ b) = b := by rw [← Nat.xor_assoc, Nat.xor_self, Nat.zero_xor]
  rw [h, Nat.xor_zero] at this; exact this)
set_option hygiene false in
local notation "Q496M14!" => (by
  have h : (x ^^^ y) >>> m = 0 := by rw [Nat.shiftRight_eq_div_pow]; exact Nat.div_eq_of_lt hz
  rw [Nat.shiftRight_xor_distrib] at h
  have := nat_xor_eq_zero h
  simpa [Nat.shiftRight_eq_div_pow] using this)
set_option hygiene false in
local notation "Q496M15!" => (by
  unfold BitVec.leadingZeros
  split
  case isTrue h => subst h; simp
  case isFalse h =>
    have hz : z.toNat ≠ 0 := by
      intro h0; apply h; exact BitVec.eq_of_toNat_eq (by simpa using h0)
    have hlog : Nat.log 2 z.toNat < 64 := Nat.log_lt_of_lt_pow hz z.isLt
    have h1 : z.toNat < 2 ^ (Nat.log 2 z.toNat).succ := Nat.lt_pow_succ_log_self (by norm_num) _
    refine lt_of_lt_of_le h1 (Nat.pow_le_pow_right (by norm_num) ?_)
    omega)
set_option hygiene false in
local notation "Q496M16!" => (by
  unfold BitVec.leadingZeros
  simp only [h, if_false]
  omega)
set_option hygiene false in
local notation "Q496M17!" => (by
  simp only [lift, Std.WP.spec_ok, true_and]
  have hle : BitVec.leadingZeros x.bv ≤ 64 := by unfold BitVec.leadingZeros; split <;> omega
  simp only [core.num.U64.leading_zeros, UScalar.val, UScalarTy.U32_numBits_eq,
    BitVec.natCast_eq_ofNat, BitVec.toNat_ofNat, Nat.reducePow]
  omega)
set_option hygiene false in
local notation "Q496M18!" => (by
  have hle : BitVec.leadingZeros x.bv ≤ 64 := by unfold BitVec.leadingZeros; split <;> omega
  simp only [core.num.U64.leading_zeros, UScalar.val, UScalarTy.U32_numBits_eq,
    BitVec.natCast_eq_ofNat, BitVec.toNat_ofNat, Nat.reducePow]
  omega)
set_option hygiene false in
local notation "Q496M19!" => (by
  have hbv : z.bv ≠ 0 := by
    intro h0; apply hz0; exact UScalar.eq_of_val_eq (by simp [UScalar.val, h0])
  have hlt : BitVec.leadingZeros z.bv < 64 := leadingZeros_lt_of_ne z.bv hbv
  have hrv : r.val = BitVec.leadingZeros z.bv / 8 := by
    rw [hr, U32.cast_Usize_val_eq, hq, hlz, lz_val]
  rw [hpa] at hx; rw [hpb] at hy
  refine ⟨?_, by omega⟩
  rw [hk1, hrv]
  have hle : BitVec.leadingZeros z.bv ≤ 64 := by unfold BitVec.leadingZeros; split <;> omega
  apply Matches.add_prefix h (by omega)
  rw [← hx, ← hy]
  apply div_eq_of_xor_lt
  rw [← UScalar.val_xor, ← hz]
  exact lt_pow_leadingZeros z.bv)
set_option hygiene false in
local notation "Q496M20!" => (by
  have hxy : x.val = y.val := by
    apply nat_xor_eq_zero
    rw [← UScalar.val_xor, ← hz, hz0]; rfl
  rw [hpa] at hx; rw [hpb] at hy
  rw [hk1]
  apply Matches.add_prefix h (le_refl 8)
  rw [← hx, ← hy, hxy])
set_option hygiene false in
local notation "Q496M21!" => (by
  rw [hl1]
  apply LZ77.Matches.succ h
  rw [← hpa, ← hpb, getElem!_pos input.val pa.val hpa', getElem!_pos input.val pb.val hpb',
    ← hx, ← hy, hxy])
set_option hygiene false in
local notation "Q496M22!" => (by
  have hlt : x.val + y.val < Usize.size := by scalar_tac
  rw [hz, core.num.Usize.wrapping_add_val_eq, UScalar.size_UScalarTyUsize, Nat.mod_eq_of_lt hlt])
set_option hygiene false in
local notation "Q496M23!" q0__:max => (by
  rw [q0__]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  step*
  simp only [← getElem!_pos] at *
  simp_all only [UScalar.val_or, UScalar.val_xor, U8.cast_U64_val_eq]
  rw [be8_nat (u8_lt _) (u8_lt _) (u8_lt _) (u8_lt _) (u8_lt _) (u8_lt _) (u8_lt _) (u8_lt _),
    be8_nat (u8_lt _) (u8_lt _) (u8_lt _) (u8_lt _) (u8_lt _) (u8_lt _) (u8_lt _) (u8_lt _)]
  simp only [word8])
set_option hygiene false in
local notation "Q496M24!" => (by
  have hle : BitVec.leadingZeros z.bv ≤ 64 := by unfold BitVec.leadingZeros; split <;> omega
  have hrv : r.val = BitVec.leadingZeros z.bv / 8 := by
    rw [hr, U32.cast_Usize_val_eq, hq, hlz, lz_val]
  refine ⟨?_, by omega⟩
  rw [hk1, hrv]
  apply Matches.add_prefix h (by omega)
  apply div_eq_of_xor_lt
  rw [← hz]
  exact lt_pow_leadingZeros z.bv)
set_option hygiene false in
local notation "Q496M25!" => (by
  have hv : word8 input a ^^^ word8 input b = 0 := by rw [← hz, hz0]; rfl
  have hab := nat_xor_eq_zero hv
  have := Matches.add_prefix (LZ77.Matches.zero input a b) (le_refl 8)
    (by simp only [Nat.add_zero]; rw [hab])
  simpa using this)
set_option hygiene false in
local notation "Q496M26!" => (by
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  rw [wadd_val hpa (by omega), wadd_val hpb (by omega)] at hz
  exact Matches.lz_any h hz hlz hq hr hk1)
set_option hygiene false in
local notation "Q496M27!" => (by
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  rw [wadd_val hpa (by omega), wadd_val hpb (by omega)] at hz
  have h8 := Matches.xz hz hz0
  rw [hk1]
  intro i hi
  by_cases hik : i < k.val
  · exact h i hik
  · have := h8 (i - k.val) (by omega)
    rw [show b.val + k.val + (i - k.val) = b.val + i by omega,
      show a.val + k.val + (i - k.val) = a.val + i by omega] at this
    exact this)
set_option hygiene false in
local notation "Q496M28!" => (by
  rw [hpa] at hx; rw [hpb] at hy
  rw [hk1]
  apply Matches.add_prefix h (le_refl 8)
  rw [← hx, ← hy, hxy])
set_option hygiene false in
local notation "Q496M29!" q0__:max q1__:max => (by
  rw [q0__]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  apply Std.loop.spec_decr_nat
    (measure := fun r => len.val - r.1.val + r.2.val)
    (inv := fun r => r.1.val ≤ len.val ∧ Matches s a.val b.val r.1.val)
  · rintro ⟨k, ok⟩ ⟨hk, hm⟩
    simp only at hk hm
    simp only [q1__]
    step*
    all_goals first
      | scalar_tac
      | (refine ⟨by scalar_tac, Matches.word_eq hm (by assumption) (by assumption)
          (by assumption) (by assumption) (by assumption) (by scalar_tac), by scalar_tac⟩)
  · exact ⟨hk, hm⟩)
set_option hygiene false in
local notation "Q496M30!" q0__:max q1__:max => (by
  rw [q0__]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  apply Std.loop.spec_decr_nat
    (measure := fun r => len.val - r.1.val + r.2.val)
    (inv := fun r => r.1.val ≤ len.val ∧ Matches s a.val b.val r.1.val)
  · rintro ⟨k, ok⟩ ⟨hk, hm⟩
    simp only at hk hm
    simp only [q1__]
    step*
    all_goals first
      | scalar_tac
      | (refine ⟨by scalar_tac, Matches.byte' hm (by assumption) (by assumption) (by scalar_tac)
          (by scalar_tac) (by assumption) (by assumption) (by assumption) (by assumption),
          by scalar_tac⟩)
  · exact ⟨hk, hm⟩)
set_option hygiene false in
local notation "Q496M31!" => (by
  have hw0 : w.val = 0 := by simpa using hw0
  rw [hpa] at hx; rw [hpb] at hy
  have := Matches.add_prefix (d := len - k) h (by omega) (by
    rw [← hx, ← hy, ← hsh]
    have h0 : (x.val ^^^ y.val) >>> sh.val = 0 := by rw [← UScalar.val_xor, ← hz, ← hw, hw0]
    rw [Nat.shiftRight_xor_distrib] at h0
    have := nat_xor_eq_zero h0
    simpa [Nat.shiftRight_eq_div_pow] using this)
  rw [show k + (len - k) = len by omega] at this
  exact this)
set_option hygiene false in
local notation "Q496M32!" q0__:max => (by
  rw [q0__]
  apply Std.WP.spec_bind (same_loop0_spec s a b len 0#usize 1#usize ha hb hlen (by simp)
    (LZ77.Matches.zero s a.val b.val))
  rintro ⟨k, ok⟩ ⟨hk, hm, hok⟩
  simp only at hk hm hok
  step*
  intro _
  exact Matches.mask hm (by assumption) (by assumption) (by assumption) (by assumption)
    (by assumption) (by assumption) (by assumption) (by scalar_tac) (by scalar_tac)
    (by scalar_tac))
set_option hygiene false in
local notation "Q496M33!" => (by
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
  omega)
set_option hygiene false in
local notation "Q496M34!" => (by
  simp only [lift, Std.WP.spec_ok, true_and]
  exact ⟨fun h => lz32_le x 2 (by norm_num) (by simpa using h),
    fun h => lz32_le x 3 (by norm_num) (by simpa using h)⟩)
set_option hygiene false in
local notation "Q496M35!" q0__:max => (by
  rw [q0__]
  have ⟨hG0, hG1⟩ := GBASE_bound
  repeat' (split <;> step*))
set_option hygiene false in
local notation "Q496M36!" => (by
  intro j hj
  rw [Std.Array.repeat_val] at hj ⊢
  rw [List.getElem!_eq_getElem?_getD, List.getElem?_replicate_of_lt (by simpa using hj)]
  rfl)
set_option hygiene false in
local notation "Q496M37!" => (by
  intro j hj
  rw [Std.Array.set_val_eq] at hj ⊢
  rw [List.length_set] at hj
  by_cases hja : a.val = j
  · subst hja
    rw [List.getElem!_eq_getElem?_getD, List.getElem?_set_self hj]
    exact hv
  · rw [List.getElem!_eq_getElem?_getD, List.getElem?_set_ne hja, ← List.getElem!_eq_getElem?_getD]
    exact h j hj)
set_option hygiene false in
local notation "Q496M38!" => (by
  subst h1
  apply HeadBound.set h a v
  rw [hv]
  have : (UScalar.cast .U32 i).val = i.val % 2 ^ 32 := by
    simp only [UScalar.cast_val_eq, UScalarTy.U32_numBits_eq]
  rw [this]
  exact le_trans (Nat.mod_le _ _) hi)
set_option hygiene false in
local notation "Q496M39!" => (by
  have := h a.val ha
  rw [getElem!_pos head.val a.val ha, ← hx] at this
  exact this)
set_option hygiene false in
local notation "Q496M40!" => (by
  rw [h, U32.cast_Usize_val_eq]; exact hx)
set_option hygiene false in
local notation "Q496M41!" => (by
  have hsz : 4294967296 ≤ Usize.size := by scalar_tac
  have hpl : p.val < Usize.size := by scalar_tac
  have hdv : d.val = p.val - c.val := by
    rw [hd, core.num.Usize.wrapping_sub_val_eq, UScalar.size_UScalarTyUsize]
    rw [show p.val + (Usize.size - c.val) = (p.val - c.val) + Usize.size by omega,
      Nat.add_mod_right, Nat.mod_eq_of_lt (by omega)]
  have hiv : i.val < 32768 := by scalar_tac
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
      omega)
set_option hygiene false in
local notation "Q496M42!" => (by
  obtain ⟨hdv, hd1, hd2⟩ := dist_of_wrapping hc hd hi hlt
  refine Or.inr ⟨hd1, hd2, by omega, hl, ?_⟩
  rw [show p.val - d.val = c.val by omega]
  exact hm)
set_option hygiene false in
local notation "Q496M43!" => (by
  have hd' : d.val ≠ 0 := by intro h; apply hd; exact UScalar.eq_of_val_eq (by simp [h])
  rcases hc with h0 | ⟨hd1, hd2, hdp, hl, hm⟩
  · exact absurd h0 hd'
  · rcases Nat.lt_or_ge l.val 3 with h3 | h3
    · exact Or.inl h3
    · exact Or.inr ⟨h3, by omega, hpl, hd1, hd2, hdp, hm⟩)
set_option hygiene false in
local notation "Q496M44!" => (by
  have hd' : d.val ≠ 0 := by intro h; apply hd; exact UScalar.eq_of_val_eq (by simp [h])
  rcases hc with h0 | ⟨_, _, _, hl, _⟩
  · exact absurd h0 hd'
  · omega)
set_option hygiene false in
local notation "Q496M45!" => (by
  rcases hc with h0 | ⟨_, hd, _⟩ <;> omega)
set_option hygiene false in
local notation "Q496M46!" => (by
  rcases hf with h | h
  · omega
  · exact h)
set_option hygiene false in
local notation "Q496M47!" => (by
  intro n
  induction n with
  | zero => simp [copyN]
  | succ m ih =>
    simp only [copyN]
    rw [List.take_append_of_le_length (by simp)]
    exact ih)
set_option hygiene false in
local notation "Q496M48!" => (by
  intro ts
  induction ts with
  | nil => intro init acc h; simp at h; subst h; simp
  | cons t ts ih =>
    intro init acc h
    simp only [List.foldlM_cons] at h
    cases he : emit init t with
    | none => rw [he] at h; simp at h
    | some a =>
      rw [he] at h
      simp only [Option.bind_eq_bind, Option.bind_some] at h
      have h1 := ih a acc h
      have h2 : init.length + 1 ≤ a.length := by
        simp only [emit] at he
        split at he
        · simp at he; subst he; simp
        · split at he
          · split at he
            · simp at he; subst he; rw [copyN_length]; simp only [tokLen]; omega
            · simp at he
          · simp at he
      simp only [List.length_cons]
      omega)
set_option hygiene false in
local notation "Q496M49!" => (by
  have := foldlM_emit_length ts [] acc h
  simpa using this)
set_option hygiene false in
local notation "Q496M50!" => (by
  rw [decode_snoc] at hd
  cases hts : decode ts with
  | none => rw [hts] at hd; simp at hd
  | some acc =>
    rw [hts] at hd
    simp only [Option.bind_some, emit, if_pos ht] at hd
    have hacc : acc ++ [t] = inp.take p := Option.some.inj hd
    have hlen : acc.length + 1 = p := by
      have := congrArg List.length hacc
      simp [List.length_take] at this; omega
    refine ⟨by omega, ?_⟩
    apply congrArg some
    have := congrArg (List.take acc.length) hacc
    rw [List.take_append_of_le_length (le_refl _), List.take_length, List.take_take] at this
    rw [this, show min acc.length p = p - 1 by omega])
set_option hygiene false in
local notation "Q496M51!" => (by
  rw [decode_snoc] at hd
  cases hts : decode ts with
  | none => rw [hts] at hd; simp at hd
  | some acc =>
    rw [hts] at hd
    simp only [Option.bind_some, emit, if_neg (show ¬ t < 256 by omega)] at hd
    split at hd
    · split at hd
      · have hacc : copyN acc (tokDist t) (tokLen t) = inp.take p := Option.some.inj hd
        have hlen : acc.length + tokLen t = p := by
          have := congrArg List.length hacc
          simp [List.length_take] at this; omega
        refine ⟨by omega, ?_⟩
        apply congrArg some
        have := congrArg (List.take acc.length) hacc
        rw [copyN_take_prefix, List.take_take] at this
        rw [this, show min acc.length p = p - tokLen t by omega]
      · simp at hd
    · simp at hd)
set_option hygiene false in
local notation "Q496M52!" => (by
  have hlt : nt - 1 < out.val.length := by
    have : out.length = out.val.length := rfl
    omega
  simp only [toks]
  conv_lhs => rw [show nt = (nt - 1) + 1 by omega]
  rw [List.take_add_one, List.getElem?_eq_getElem hlt, Option.toList_some, List.map_append]
  simp [getElem!_pos out.val (nt - 1) hlt])
set_option hygiene false in
local notation "Q496M53!" => (by
  simp only [toks, List.length_map, List.length_take]
  have : out.length = out.val.length := rfl
  omega)
set_option hygiene false in
local notation "Q496M54!" => (by
  obtain ⟨hps, hntp, hso, hde⟩ := h
  have hntl : ntU.val < out.length := by omega
  refine ⟨by omega, by omega, by rw [Std.Slice.set_length]; exact hso, ?_⟩
  rw [← hnt]
  refine emit_lit s out ntU p v (by rw [hnt]; exact hde) hp hntl ?_
  have hpl : p < s.val.length := hp
  rw [hv, bytes_getElem! s p hpl, getElem!_pos s.val p hpl])
set_option hygiene false in
local notation "Q496M55!" => (by
  obtain ⟨hps, hntp, hso, hde⟩ := h
  obtain ⟨h3, h258, hpl, hd1, hd32, hdp, hmm⟩ := hm
  have hntl : ntU.val < out.length := by omega
  refine ⟨by omega, by omega, by rw [Std.Slice.set_length]; exact hso, ?_⟩
  rw [← hnt]
  exact emit_match s out ntU p d l v (by rw [hnt]; exact hde) hntl hd1 hdp hd32 h3 h258 hpl hmm hv)
set_option hygiene false in
local notation "Q496M56!" => (by
  obtain ⟨hps, hntp, hso, hde⟩ := h
  rw [toks_pop out nt h0 hle] at hde
  obtain ⟨hp1, hde'⟩ := decode_pop_lit (by simpa using hps) hde ht
  exact ⟨hp1, by omega, by omega, hso, hde'⟩)
set_option hygiene false in
local notation "Q496M57!" => (by
  obtain ⟨hps, hntp, hso, hde⟩ := h
  rw [toks_pop out nt h0 hle] at hde
  obtain ⟨hw, hde'⟩ := decode_pop_match (by simpa using hps) hde ht
  have hlen := decode_length_le hde'
  rw [toks_length out (nt - 1) (by omega), List.length_take, bytes_length] at hlen
  exact ⟨hw, by omega, by omega, hso, hde'⟩)
set_option hygiene false in
local notation "Q496M58!" => (by
  obtain ⟨hps, hntp, hso, hde⟩ := h
  refine ⟨by omega, ?_⟩
  unfold LZ77.Valid
  rw [hde, show p = s.length by omega, ← bytes_length, List.take_length])
set_option hygiene false in
local notation "Q496M59!" => (by
  subst hout1
  refine ⟨hnt1, Std.Slice.set_length .., ?_⟩
  rw [hnt1]
  exact Dec.lit h hp ntU rfl v (by rw [hv, U8.cast_U32_val_eq, hb, getElem!_pos s.val pU.val hp]))
set_option hygiene false in
local notation "Q496M60!" q0__:max => (by
  rw [q0__]
  step*
  exact Dec.lit_step hdec (by scalar_tac) (by assumption) (by assumption) (by assumption)
    (by assumption))
set_option hygiene false in
local notation "Q496M61!" => (by
  subst hout1
  refine ⟨hnt1, he, Std.Slice.set_length .., ?_⟩
  rw [hnt1, he]
  exact Dec.match h hm ntU rfl v hv)
set_option hygiene false in
local notation "Q496M62!" q0__:max => (by
  rw [q0__]
  have hm' := hm
  obtain ⟨h3, h258, hpl, hd1, hd32, hdp, _⟩ := hm'
  step*
  exact Dec.match_step hdec hm (by assumption)
    (by simp only [LZ77.mkMatch, LZ77.MATCH_BASE]; scalar_tac) (by assumption) (by assumption))
set_option hygiene false in
local notation "Q496M63!" => (by
  obtain ⟨h3, h258, hpl, hd1, hd32, _, hm⟩ := h
  refine ⟨by omega, by omega, by omega, hd1, hd32, by omega, ?_⟩
  intro k hk
  rcases Nat.eq_zero_or_pos k with hk0 | hk0
  · subst hk0
    rw [Nat.add_zero, Nat.add_zero, show p - 1 - d = p - 1 - d by rfl]
    exact heq
  · have := hm (k - 1) (by omega)
    rw [show p - 1 + k = p + (k - 1) by omega, show p - 1 - d + k = p - d + (k - 1) by omega]
    exact this)
set_option hygiene false in
local notation "Q496M64!" => (by
  obtain ⟨h3, h258, hpl, hd1, hd32, _, hm⟩ := h
  refine ⟨by omega, by omega, by omega, hd1, hd32, hdw, ?_⟩
  intro k hk
  rcases Nat.lt_or_ge k w with hkw | hkw
  · have := hmw k hkw
    rw [show p - w - d = p - w - d by rfl] at this
    exact this
  · have := hm (k - w) (by omega)
    rw [show p - w + k = p + (k - w) by omega, show p - w - d + k = p - d + (k - w) by omega]
    exact this)
set_option hygiene false in
local notation "Q496M65!" => (by
  obtain ⟨hdec, hm, hE, hP⟩ := h
  have ht' : (out.val[nt.val - 1]!).val < 256 := by
    rw [← hi1, getElem!_pos out.val i1.val hi1l, ← ht]; scalar_tac
  obtain ⟨hp1, hdec'⟩ := Dec.pop_lit hdec (by omega) hntl ht'
  have heq : input.val[p.val - 1]! = input.val[p.val - 1 - d]! := by
    rw [← hi2, getElem!_pos input.val i2.val hi2l, show i2.val - d = i4.val by omega,
      getElem!_pos input.val i4.val hi4l, ← hx, ← hy, hxy]
  have hm' := MatchAt.back_lit hm hl hdp heq
  rw [hi1, hi2, hl1]
  exact ⟨hdec', hm', by omega, by omega⟩)
set_option hygiene false in
local notation "Q496M66!" => (by
  obtain ⟨hdec, hm, hE, hP⟩ := h
  have htv : (out.val[nt.val - 1]!).val = t.val := by
    rw [← hi1, getElem!_pos out.val i1.val hi1l, ← ht]
  have hwv' : w.val = tokLen (out.val[nt.val - 1]!).val := by
    rw [htv, hwv]
    simp only [tokLen, MATCH_BASE]
  obtain ⟨hwl, hdec'⟩ := Dec.pop_match hdec (by omega) hntl (by omega)
  rw [← hwv'] at hdec'
  have hmw : Matches input (p.val - w.val - d) (p.val - w.val) w.val := by
    have := hsame (by rw [hi12]; rfl)
    rw [hi11, hi10] at this
    exact this
  have hm' := MatchAt.back_match hm (by omega) hwp (by omega) hmw
  rw [hi1, hi10, hi9]
  exact ⟨hdec', hm', by omega, by omega⟩)
set_option hygiene false in
local notation "Q496M67!" q0__:max q1__:max q2__:max => (by
  rw [q0__]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  apply Std.loop.spec_decr_nat
    (measure := fun r => q1__ - r.2.2.2.val)
    (inv := fun r => BackInv input out d.val E P0 r.1.val r.2.1.val r.2.2.1.val)
  · rintro ⟨nt, p, l, back⟩ hinv
    simp only at hinv
    have hinv' := hinv
    obtain ⟨⟨hps, hntp, hso, _⟩, ⟨h3, h258, hpl, hd1, hd32, hdp, _⟩, hE, hp0⟩ := hinv'
    simp only [q2__]
    step*
    all_goals first
      | (refine ⟨hinv, by scalar_tac⟩)
      | (refine ⟨BackInv.lit hinv (by scalar_tac) (by scalar_tac) (by scalar_tac) (by scalar_tac)
          (by assumption) (by assumption) (by scalar_tac) (by scalar_tac) (by assumption)
          (by assumption) (by assumption) (by scalar_tac) (by assumption) (by scalar_tac)
          (by scalar_tac) (by scalar_tac), by scalar_tac⟩)
      | (refine ⟨BackInv.match hinv (by scalar_tac) (by scalar_tac) (by scalar_tac) (by scalar_tac)
          (by assumption) (by assumption) (by assumption) (by scalar_tac) (by scalar_tac)
          (by scalar_tac) (by scalar_tac) (by scalar_tac) (by scalar_tac) (by scalar_tac)
          (by scalar_tac), by scalar_tac⟩)
  · exact hinv)
set_option hygiene false in
local notation "Q496M68!" => (by
  apply Std.WP.spec_mono (fold_loop_inv input out nt p l d 0#usize (p.val + l.val) p.val hp8
    ⟨hdec, hm, rfl, le_refl _⟩)
  intro r h
  exact h)
set_option hygiene false in
local notation "Q496M69!" q0__:max => (by
  rw [q0__]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  apply Std.WP.spec_bind (Pₘ := fun m : Std.U32 => 1 ≤ m.val ∧ m.val ≤ 8)
  · split
    · dsimp only
      split
      · step*
      · simp
    · simp
  · intro m ⟨hm1, hm8⟩
    apply Std.WP.spec_bind (Pₘ := fun _ : Std.U64 => True)
    · split
      · step*
      · simp
    · intro x _
      step*
      all_goals first
        | exact ⟨hdec, hm, rfl, le_refl _⟩
        | scalar_tac)
set_option hygiene false in
local notation "Q496M70!" => (by
  subst hi
  refine ⟨hdec, hlen, ?_, HeadBound.mono hB hBi, hilim, hins⟩
  rcases hf with h | h
  · omega
  · exact h)
set_option hygiene false in
local notation "Q496M71!" => (by
  obtain ⟨hdec, hlen, hm, _, hplim, _⟩ := h
  exact ⟨hdec, hlen, hm, HeadBound.mono hB hBp, hplim, hins1⟩)
set_option hygiene false in
local notation "Q496M72!" => (by
  rcases System.Platform.numBits_eq with h | h <;> omega)
set_option hygiene false in
local notation "Q496M73!" q0__:max => (by
  rw [q0__]
  step*
  exact HeadBound.update hB (by assumption) (by omega) (by assumption))
set_option hygiene false in
local notation "Q496M74!" q0__:max => (by
  rw [q0__]
  step
  step
  have hi1 : i1.val ≤ B := HeadBound.get hB a i1 (by scalar_tac) (by assumption)
  step*)
set_option hygiene false in
local notation "Q496M75!" q0__:max => (by
  rw [q0__]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  step*)
set_option hygiene false in
local notation "Q496M76!" q0__:max q1__:max => (by
  rw [q0__]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  apply Std.loop.spec_decr_nat
    (measure := fun r => cap.val - r.1.val + r.2.val)
    (inv := fun r => r.1.val ≤ cap.val ∧ Matches s a.val b.val r.1.val)
  · rintro ⟨k, run⟩ ⟨hk, hm⟩
    simp only at hk hm
    simp only [q1__]
    step*
    all_goals first
      | scalar_tac
      | exact ⟨hk, hm⟩
      | exact wadd_le (by assumption) (by scalar_tac) (by scalar_tac)
      | (refine ⟨by scalar_tac, Matches.xw_zero hm (by assumption) (by assumption) (by scalar_tac)
          (by assumption) (by assumption) (by scalar_tac), by scalar_tac⟩)
      | (have hw := Matches.xw_step hm (by assumption) (by assumption) (by scalar_tac)
          (by assumption) (by assumption) (by assumption) (by assumption) (by assumption)
         refine ⟨by scalar_tac, hw.1, by scalar_tac⟩)
  · exact ⟨hk, hm⟩)
set_option hygiene false in
local notation "Q496M77!" q0__:max q1__:max => (by
  rw [q0__]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  apply Std.loop.spec_decr_nat
    (measure := fun r => cap.val - r.1.val + r.2.val)
    (inv := fun r => r.1.val ≤ cap.val ∧ Matches s a.val b.val r.1.val)
  · rintro ⟨k, run⟩ ⟨hk, hm⟩
    simp only at hk hm
    simp only [q1__]
    step*
    all_goals first
      | scalar_tac
      | exact ⟨hk, hm⟩
      | (refine ⟨by scalar_tac, Matches.byte' hm (by assumption) (by assumption) (by scalar_tac)
          (by scalar_tac) (by assumption) (by assumption) (by assumption) (by assumption),
          by scalar_tac⟩)
  · exact ⟨hk, hm⟩)
set_option hygiene false in
local notation "Q496M78!" q0__:max => (by
  rw [q0__]
  apply Std.WP.spec_bind (common_from_loop0_spec s a b cap k0 1#u32 ha hb hcap hk0 hm)
  rintro ⟨k, run⟩ ⟨hk, hm'⟩
  exact common_from_loop1_spec s a b cap k run ha hb hk hm')
set_option hygiene false in
local notation "Q496M79!" => (by
  have hx0' : ¬x = 0#u64 := by simpa using hx0
  have h := Matches.word_lz (k := 0) (k1 := m) (pa := c) (pb := p)
    (LZ77.Matches.zero s c.val p.val) (by simp) (by simp) hcw hy hx hx0' hlz hq hm (by simp)
  simpa using h)
set_option hygiene false in
local notation "Q496M80!" => (by
  have hv : x.val = 0 := by simpa using hx0
  have hx0' : x = 0#u64 := UScalar.eq_of_val_eq (by simp [hv])
  exact Matches.word_zero (k := 0) (k1 := 8#usize) (pa := c) (pb := p)
    (LZ77.Matches.zero s c.val p.val) (by simp) (by simp) hcw hy hx hx0' (by simp))
set_option hygiene false in
local notation "Q496M81!" => (by
  obtain ⟨hdv, hd1, hd2⟩ := dist_of_wrapping hc hd hi hlt
  refine ⟨?_, hl, hd2⟩
  rcases Nat.lt_or_ge l.val 3 with h3 | h3
  · exact Or.inl h3
  · refine Or.inr ⟨h3, hl, hpl, hd1, hd2, by omega, ?_⟩
    rw [show p.val - d.val = c.val by omega]
    exact hm)
set_option hygiene false in
local notation "Q496M82!" q0__:max => (by
  rw [q0__]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  step*
  repeat' (split <;> step*)
  all_goals first
    | exact Matches.xor_zero hcw hy hx (by assumption)
    | (have hw := Matches.xor_lz (m := UScalar.cast .Usize i1) hcw hy hx (by assumption)
        (by assumption) (by assumption) rfl
       exact ⟨by scalar_tac, by scalar_tac, hw.1⟩))
set_option hygiene false in
local notation "Q496M83!" => (by
  have h8 := Matches.xz hx hx0
  rw [hi1, hi2] at hx2
  have := Matches.lz_any (k := 8) (k1 := l) h8 hx2 hlz hq hr (by omega)
  exact ⟨this.1, by omega⟩)
set_option hygiene false in
local notation "Q496M84!" => (by
  have := Matches.lz_any (k := 0) (k1 := l) (LZ77.Matches.zero s c.val p.val)
    (by simpa using hx) hlz hq hr (by omega)
  exact ⟨by omega, by omega, this.1⟩)
set_option hygiene false in
local notation "Q496M85!" q0__:max => (by
  rw [q0__]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  have hxv := xval_of hx hcw hy
  step*
  repeat' (split <;> step*)
  all_goals first
    | exact Matches.mono (Matches.x16a hxv (by assumption) (by assumption) (by assumption)
        (by assumption) (by assumption) (by assumption) (by assumption) (by assumption)).1
        (by scalar_tac)
    | exact Matches.x16a' hxv (by assumption) (by assumption) (by assumption) (by assumption)
        (by assumption) (by assumption) (by assumption) (by assumption) (by scalar_tac)
    | exact Matches.x16b hxv (by assumption) (by assumption) (by assumption) (by assumption)
        (by scalar_tac))
set_option hygiene false in
local notation "Q496M86!" q0__:max => (by
  rw [q0__]
  step*
  all_goals first
    | exact FoundAt.none' s p.val
    | exact FoundAt.of_matches hc (by assumption) (by assumption) (by assumption)
        (by assumption) (by assumption) (by assumption))
set_option hygiene false in
local notation "Q496M87!" q0__:max q1__:max => (by
  rw [q0__]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  have hL : 1 ≤ q1__ := by scalar_tac
  step
  have hlo : q.val + lo.val ≤ s.length := by
    rcases lo_post with h | ⟨_, h⟩ <;> omega
  step*
  all_goals first
    | exact FoundAt.none' s q.val
    | exact FoundAt.of_matches hc (by assumption) (by assumption) (by assumption)
        (by assumption) (by assumption) (by assumption))
set_option hygiene false in
local notation "Q496M88!" q0__:max => (by
  rw [q0__]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  step*
  all_goals first
    | (have hi1 := HeadBound.get hB a i1 (by scalar_tac) (by assumption)
       exact ⟨by scalar_tac, by scalar_tac, hw⟩))
set_option hygiene false in
local notation "Q496M89!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun r => e.val - r.2.2.val)
    (inv := fun r => Dec input r.1 r.2.1.val r.2.2.val ∧ r.1.length = out.length ∧
      r.2.2.val ≤ e.val)
  · rintro ⟨out', nt', j'⟩ ⟨hdec', hlen', hj'⟩
    simp only at hdec' hlen' hj'
    simp only [q1__]
    step*
  · exact ⟨hdec, rfl, hj⟩)
set_option hygiene false in
local notation "Q496M90!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun r => stop.val - r.2.val)
    (inv := fun r => HeadBound r.1 B ∧ (r.2.val ≤ ins.val ∨ r.2.val ≤ stop.val))
  · rintro ⟨head, ins'⟩ ⟨hB, hins⟩
    simp only at hB hins
    simp only [q1__]
    step*
  · exact ⟨hB, Or.inl (le_refl _)⟩)
set_option hygiene false in
local notation "Q496M91!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun r => «end».val - r.2.val)
    (inv := fun r => HeadBound r.1 B)
  · rintro ⟨head, ins'⟩ hB
    simp only at hB
    simp only [q1__]
    step*
  · exact hB)
set_option hygiene false in
local notation "Q496M92!" q0__:max => (by
  rw [q0__]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  step*
  repeat' (split <;> step*))
set_option hygiene false in
local notation "Q496M93!" => (by
  obtain ⟨hps, hntp, hso, hde⟩ := h
  refine ⟨hps, hntp, by rw [Std.Slice.set_length]; exact hso, ?_⟩
  have : toks (out.set i v) nt = toks out nt := by
    simp only [toks, Std.Slice.set_val_eq, List.take_set]
    rw [List.set_eq_of_length_le (by rw [List.length_take]; omega)]
  rw [this]; exact hde)
set_option hygiene false in
local notation "Q496M94!" => (by
  have hv0' : v0.val = (s.val[a.val]!).val := by
    rw [hv0, U8.cast_U32_val_eq, hb0, getElem!_pos s.val a.val ha0]
  have hv1' : v1.val = (s.val[a.val + 1]!).val := by
    rw [hv1, U8.cast_U32_val_eq, hb1, show a.val + 1 = i7.val by omega,
      getElem!_pos s.val i7.val ha1]
  have hv2' : v2.val = (s.val[a.val + 1 + 1]!).val := by
    rw [hv2, U8.cast_U32_val_eq, hb2, show a.val + 1 + 1 = i11.val by omega,
      getElem!_pos s.val i11.val ha2]
  have hv3' : v3.val = (s.val[a.val + 1 + 1 + 1]!).val := by
    rw [hv3, U8.cast_U32_val_eq, hb3, show a.val + 1 + 1 + 1 = i15.val by omega,
      getElem!_pos s.val i15.val ha3]
  have hlen : out4.length = out.length := by
    rw [ho4, Std.Slice.set_length, ho3, Std.Slice.set_length, ho2, Std.Slice.set_length, ho1,
      Std.Slice.set_length]
  refine ⟨?_, hlen⟩
  have D1 : Dec s out1 (nt.val + 1) (a.val + 1) := by
    rw [ho1]; exact Dec.lit h (by omega) nt rfl v0 hv0'
  have D2 : Dec s out2 (nt.val + 1 + 1) (a.val + 1 + 1) := by
    rw [ho2]; exact Dec.lit D1 (by omega) i9 hi9 v1 hv1'
  have D3 : Dec s out3 (nt.val + 1 + 1 + 1) (a.val + 1 + 1 + 1) := by
    rw [ho3]; exact Dec.lit D2 (by omega) i13 (by omega) v2 hv2'
  have D4 : Dec s out4 (nt.val + 1 + 1 + 1 + 1) (a.val + 1 + 1 + 1 + 1) := by
    rw [ho4]; exact Dec.lit D3 (by omega) i17 (by omega) v3 hv3'
  rcases (show j.val = 0 ∨ j.val = 1 ∨ j.val = 2 ∨ j.val = 3 ∨ j.val = 4 by omega) with
    h0 | h1 | h2 | h3 | h4
  · have E : Dec s out4 nt.val a.val := by
      rw [ho4]; apply Dec.set_beyond _ _ _ (by omega)
      rw [ho3]; apply Dec.set_beyond _ _ _ (by omega)
      rw [ho2]; apply Dec.set_beyond _ _ _ (by omega)
      rw [ho1]; apply Dec.set_beyond _ _ _ (by omega)
      exact h
    rw [show r.val = nt.val by omega, show e.val = a.val by omega]; exact E
  · have E : Dec s out4 (nt.val + 1) (a.val + 1) := by
      rw [ho4]; apply Dec.set_beyond _ _ _ (by omega)
      rw [ho3]; apply Dec.set_beyond _ _ _ (by omega)
      rw [ho2]; apply Dec.set_beyond _ _ _ (by omega)
      exact D1
    rw [show r.val = nt.val + 1 by omega, show e.val = a.val + 1 by omega]; exact E
  · have E : Dec s out4 (nt.val + 1 + 1) (a.val + 1 + 1) := by
      rw [ho4]; apply Dec.set_beyond _ _ _ (by omega)
      rw [ho3]; apply Dec.set_beyond _ _ _ (by omega)
      exact D2
    rw [show r.val = nt.val + 1 + 1 by omega, show e.val = a.val + 1 + 1 by omega]; exact E
  · have E : Dec s out4 (nt.val + 1 + 1 + 1) (a.val + 1 + 1 + 1) := by
      rw [ho4]; apply Dec.set_beyond _ _ _ (by omega)
      exact D3
    rw [show r.val = nt.val + 1 + 1 + 1 by omega, show e.val = a.val + 1 + 1 + 1 by omega]
    exact E
  · rw [show r.val = nt.val + 1 + 1 + 1 + 1 by omega, show e.val = a.val + 1 + 1 + 1 + 1 by omega]
    exact D4)
set_option hygiene false in
local notation "Q496M95!" q0__:max => (by
  rw [q0__]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  step*
  all_goals first
    | exact flush_spec input out nt a e hdec (by scalar_tac) ha
    | (subst_vars; simp only [Std.Slice.set_length]; scalar_tac)
    | exact Dec.flush4_step hdec ha (by assumption) (by scalar_tac) (by scalar_tac)
        (by scalar_tac) (by scalar_tac) (by assumption) (by assumption) (by assumption)
        (by assumption) (by scalar_tac) (by assumption) (by assumption) (by assumption)
        (by assumption) (by assumption) (by scalar_tac) (by assumption) (by assumption)
        (by assumption) (by assumption) (by assumption) (by scalar_tac) (by assumption)
        (by assumption) (by assumption) (by assumption) (by assumption))
set_option hygiene false in
local notation "Q496M96!" => (by
  obtain ⟨hm, _, hplim, _, _, _, _, hP⟩ := h
  exact ⟨hm, HeadBound.mono hB hBp, hplim, hins1, hps, hpc, hpw, hP⟩)
set_option hygiene false in
local notation "Q496M97!" q0__:max q1__:max => (by
  rw [q0__]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  apply Std.loop.spec_decr_nat
    (measure := fun r => lim.val - r.1.val + r.2.2.2.2.2.2.2.2.val)
    (inv := fun r => LazyInv1 input lim.val P0 r.1.val r.2.1 r.2.2.1.val r.2.2.2.1.val
      r.2.2.2.2.1.val r.2.2.2.2.2.1.val r.2.2.2.2.2.2.1.val r.2.2.2.2.2.2.2.1.val)
  · rintro ⟨p, head, pre_slot, pre_c, pre_w, l, d, ins, go⟩ hinv
    simp only at hinv
    have hinv' := hinv
    obtain ⟨⟨h3, h258, hpl, hd1, hd32, hdp, _⟩, hB, hplim, hins, hslot, hpc, hpw, hP⟩ := hinv'
    simp only [q1__]
    step*
    all_goals first
      | (refine ⟨LazyInv1.accept (by assumption) (by scalar_tac) (by assumption) (by scalar_tac)
          (by scalar_tac) (by scalar_tac) (by scalar_tac) (by scalar_tac) (by assumption)
          (by scalar_tac), by scalar_tac⟩)
      | (refine ⟨LazyInv1.reject hinv (by assumption) (by scalar_tac) (by scalar_tac)
          (by scalar_tac) (by scalar_tac) (by assumption), by scalar_tac⟩)
  · exact hinv)
set_option hygiene false in
local notation "Q496M98!" => (by
  apply Std.WP.spec_mono (lazy1_loop_inv input lazy km p head lim pre_slot pre_c pre_w l d ins go
    p.val hlim hH ⟨hm, hB, hplim, hins, hps, hpc, hpw, le_refl _⟩)
  rintro ⟨p', head', ps', pc', pw', l', d', ins'⟩ ⟨hm', hB', hplim', hins', hps', hpc', hpw', hP'⟩
  exact ⟨hm', HeadBound.mono hB' (by have := hm'.1; omega), hplim', hins', hm'.1, hps', hpc',
    hpw', hP'⟩)
set_option hygiene false in
local notation "Q496M99!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun r => n.val - r.2.2.val)
    (inv := fun r => Dec input r.1 r.2.1.val r.2.2.val ∧ r.1.length = out.length)
  · rintro ⟨out', nt', p'⟩ ⟨hdec', hlen'⟩
    simp only at hdec' hlen'
    simp only [q1__]
    step*
    have hd := Dec.done hdec' (by scalar_tac)
    exact ⟨hd.1, hlen', hd.2⟩
  · exact ⟨hdec, rfl⟩)
set_option hygiene false in
local notation "Q496M100!" => (by
  subst hls
  exact ⟨hdec, hlen, hlsp, HeadBound.mono hB hBp, hm, hps, hpc, hpw⟩)
set_option hygiene false in
local notation "Q496M101!" q0__:max q1__:max => (by
  rw [q0__]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  apply Std.loop.spec_decr_nat
    (measure := fun r => r.2.2.2.2.2.2.1.val)
    (inv := fun r => MainInv1 input L r.1 r.2.1.val r.2.2.1.val r.2.2.2.1.val r.2.2.2.2.1
      r.2.2.2.2.2.1.val r.2.2.2.2.2.2.2.1.val r.2.2.2.2.2.2.2.2.1.val r.2.2.2.2.2.2.2.2.2.val)
  · rintro ⟨out, nt, ls, p, head, miss, fuel, pre_slot, pre_c, pre_w⟩ hinv
    simp only at hinv
    have hinv' := hinv
    obtain ⟨hdec, hL, hlsp, hB, hmiss, hps, hpc, hpw⟩ := hinv'
    simp only [q1__]
    step*
    all_goals try (obtain ⟨i4, i5, i6⟩ := ae; dsimp only at *; step*)
    all_goals first
      | exact FoundAt.real (by assumption) (by scalar_tac)
      | exact HeadBound.mono (by assumption) (by scalar_tac)
      | (refine ⟨MainInv1.mk' (by assumption) (by scalar_tac) (by scalar_tac) (by scalar_tac)
          (by assumption) (by scalar_tac) (by scalar_tac) (by scalar_tac) (by scalar_tac)
          (by assumption), by scalar_tac⟩)
  · exact hinv)
set_option hygiene false in
local notation "Q496M102!" q0__:max => (by
  rw [q0__]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  have hB0 : HeadBound (Std.Array.repeat H 0#u32) 0 := HeadBound.init H
  have hdec0 : Dec input out (0#usize).val (0#usize).val := Dec.init input out hlen
  step*)
set_option hygiene false in
local notation "Q496M103!" => (by
  have m1 := Matches.byte' (l1 := 1#usize) (pa := c) (pb := p) (LZ77.Matches.zero s c.val p.val)
    (by simp) (by simp) hcl hpl hx0 hy0 h0 (by simp)
  have m2 := Matches.byte' (l1 := 2#usize) (pa := c1) (pb := p1) m1 (by simpa using hc1)
    (by simpa using hp1) hc1l hp1l hx1 hy1 h1 (by simp)
  exact Matches.byte' (l1 := 3#usize) (pa := c2) (pb := p2) m2 (by simpa using hc2)
    (by simpa using hp2) hc2l hp2l hx2 hy2 h2 (by simp))
set_option hygiene false in
local notation "Q496M104!" => (by
  refine ⟨?_, hl, hd32⟩
  rcases Nat.lt_or_ge l.val 3 with h3 | h3
  · exact Or.inl h3
  · refine Or.inr ⟨h3, hl, hpl, by omega, hd32, by omega, ?_⟩
    rw [show p.val - d.val = c.val by omega]
    exact hm)
namespace Q4
open Aeneas Aeneas.Std Result ControlFlow
set_option maxRecDepth 8192
set_option maxHeartbeats 4000000
set_option linter.unusedVariables false
open LZ77 (toks bytes bytes_length bytes_getElem! toks_update bytes_congr
  Matches Found emit_lit emit_match ite_ok)
open LZ77 (decode emit copyN tokLen tokDist MATCH_BASE TOK_LIMIT decode_snoc copyN_length)
section TinyPath
set_option linter.unusedTactic false
set_option linter.unreachableTactic false
@[local step]
theorem tp_lift_spec {α : Type} (x : α) : lift x ⦃ fun y => y = x ⦄ := by
  simp [lift, WP.spec_ok]
theorem tp_numBits_ge : 32 ≤ System.Platform.numBits := by
  cases System.Platform.numBits_eq <;> simp [*]
@[local scalar_tac System.Platform.numBits]
theorem tp_numBits_ge' : 32 ≤ System.Platform.numBits := tp_numBits_ge
end TinyPath
@[irreducible] def word8 (input : Slice Std.U8) (p : Nat) : Nat :=
  (input.val[p]!).val * 2^56 + (input.val[p + 1]!).val * 2^48 + (input.val[p + 2]!).val * 2^40
    + (input.val[p + 3]!).val * 2^32 + (input.val[p + 4]!).val * 2^24
    + (input.val[p + 5]!).val * 2^16 + (input.val[p + 6]!).val * 2^8 + (input.val[p + 7]!).val
theorem u8_lt (x : Std.U8) : x.val < 256 := by scalar_tac
theorem word8_digit (input : Slice Std.U8) (p k : Nat) (hk : k < 8) :
    (input.val[p + k]!).val = word8 input p / 256 ^ (7 - k) % 256 := Q496M6!
theorem word8_prefix (input : Slice Std.U8) (a b d : Nat) (hd : d ≤ 8)
    (h : word8 input a / 2 ^ (64 - 8 * d) = word8 input b / 2 ^ (64 - 8 * d)) :
    ∀ k, k < d → input.val[b + k]! = input.val[a + k]! := Q496M7!
theorem Matches.add_prefix {input : Slice Std.U8} {a b l d : Nat} (h : Matches input a b l)
    (hd : d ≤ 8)
    (hw : word8 input (a + l) / 2 ^ (64 - 8 * d) = word8 input (b + l) / 2 ^ (64 - 8 * d)) :
    Matches input a b (l + d) := Q496M8!
theorem or_eq_add_of_mod {x t : Nat} (m : Nat) (hx : x % 2 ^ m = 0) (ht : t < 2 ^ m) :
    x ||| t = x + t := Q496M9!
theorem shl_byte {x : Nat} (k : Nat) (hx : x < 256) (hk : k ≤ 56) :
    x <<< k % U64.size = x * 2 ^ k := Q496M10!
theorem be8_nat {a b c d e f g h : Nat} (ha : a < 256) (hb : b < 256) (hc : c < 256)
    (hd : d < 256) (he : e < 256) (hf : f < 256) (hg : g < 256) (hh : h < 256) :
    (a <<< 56 % U64.size ||| b <<< 48 % U64.size ||| c <<< 40 % U64.size |||
      d <<< 32 % U64.size ||| e <<< 24 % U64.size ||| f <<< 16 % U64.size |||
      g <<< 8 % U64.size ||| h) =
    a * 2^56 + b * 2^48 + c * 2^40 + d * 2^32 + e * 2^24 + f * 2^16 + g * 2^8 + h := Q496M11!
@[local step]
theorem be8_spec (s : Slice Std.U8) (i : Std.Usize) (h : i.val + 8 ≤ s.length) :
    slot.q4_be8 s i ⦃ fun v => v.val = word8 s i.val ⦄ := Q496M12! slot.q4_be8
theorem nat_xor_eq_zero {a b : Nat} (h : a ^^^ b = 0) : a = b := Q496M13!
theorem div_eq_of_xor_lt {x y m : Nat} (hz : x ^^^ y < 2 ^ m) : x / 2 ^ m = y / 2 ^ m := Q496M14!
theorem lt_pow_leadingZeros (z : BitVec 64) :
    z.toNat < 2 ^ (64 - 8 * (BitVec.leadingZeros z / 8)) := Q496M15!
theorem leadingZeros_lt_of_ne (z : BitVec 64) (h : z ≠ 0) : BitVec.leadingZeros z < 64 := Q496M16!
@[local step]
theorem lz_spec (x : Std.U64) :
    lift (core.num.U64.leading_zeros x) ⦃ fun r => r = core.num.U64.leading_zeros x ∧ r.val ≤ 64 ⦄ := Q496M17!
theorem lz_val (x : Std.U64) :
    (core.num.U64.leading_zeros x).val = BitVec.leadingZeros x.bv := Q496M18!
theorem Matches.word_lz {input : Slice Std.U8} {a b k : Nat} {pa pb r k1 : Std.Usize}
    {x y z : Std.U64} {lz q : Std.U32}
    (h : Matches input a b k) (hpa : pa.val = a + k) (hpb : pb.val = b + k)
    (hx : x.val = word8 input pa.val) (hy : y.val = word8 input pb.val)
    (hz : z.val = (x ^^^ y).val) (hz0 : ¬z = 0#u64) (hlz : lz = core.num.U64.leading_zeros z)
    (hq : q.val = lz.val / 8) (hr : r = UScalar.cast .Usize q) (hk1 : k1.val = k + r.val) :
    Matches input a b k1.val ∧ k1.val < k + 8 := Q496M19!
theorem Matches.word_zero {input : Slice Std.U8} {a b k : Nat} {pa pb k1 : Std.Usize}
    {x y z : Std.U64}
    (h : Matches input a b k) (hpa : pa.val = a + k) (hpb : pb.val = b + k)
    (hx : x.val = word8 input pa.val) (hy : y.val = word8 input pb.val)
    (hz : z.val = (x ^^^ y).val) (hz0 : z = 0#u64) (hk1 : k1.val = k + 8) :
    Matches input a b k1.val := Q496M20!
theorem Matches.byte' {input : Slice Std.U8} {a b l : Nat} {pa pb l1 : Std.Usize}
    {x y : Std.U8} (h : Matches input a b l) (hpa : pa.val = a + l) (hpb : pb.val = b + l)
    (hpa' : pa.val < input.val.length) (hpb' : pb.val < input.val.length)
    (hx : x = input.val[pa.val]) (hy : y = input.val[pb.val]) (hxy : x = y)
    (hl1 : l1.val = l + 1) : Matches input a b l1.val := Q496M21!
theorem wadd_val {x y z : Std.Usize} (hz : z = core.num.Usize.wrapping_add x y)
    (hb : x.val + y.val ≤ Std.Usize.max) : z.val = x.val + y.val := Q496M22!
theorem wadd_le {x y z : Std.Usize} {m n : Nat} (hz : z = core.num.Usize.wrapping_add x y)
    (h : x.val + y.val + m ≤ n) (hn : n ≤ Std.Usize.max) : z.val + m ≤ n := by
  rw [wadd_val hz (by omega)]; exact h
@[local step]
theorem xor8_spec (s : Slice Std.U8) (a b : Std.Usize) (ha : a.val + 8 ≤ s.length)
    (hb : b.val + 8 ≤ s.length) :
    slot.q4_xor8 s a b ⦃ fun v => v.val = word8 s a.val ^^^ word8 s b.val ⦄ := Q496M23! slot.q4_xor8
theorem Matches.lz_any {input : Slice Std.U8} {a b k : Nat} {r k1 : Std.Usize} {z : Std.U64}
    {lz q : Std.U32} (h : Matches input a b k)
    (hz : z.val = word8 input (a + k) ^^^ word8 input (b + k))
    (hlz : lz = core.num.U64.leading_zeros z) (hq : q.val = lz.val / 8)
    (hr : r = UScalar.cast .Usize q) (hk1 : k1.val = k + r.val) :
    Matches input a b k1.val ∧ k1.val ≤ k + 8 := Q496M24!
theorem Matches.xz {input : Slice Std.U8} {a b : Nat} {z : Std.U64}
    (hz : z.val = word8 input a ^^^ word8 input b) (hz0 : z = 0#u64) :
    Matches input a b 8 := Q496M25!
theorem xval_of {x cw y : Std.U64} {A B : Nat} (hx : x.val = (cw ^^^ y).val) (hcw : cw.val = A)
    (hy : y.val = B) : x.val = A ^^^ B := by
  rw [hx, UScalar.val_xor, hcw, hy]
theorem Matches.xw_step {input : Slice Std.U8} {a b k pa pb k1 r : Std.Usize} {z : Std.U64}
    {lz q : Std.U32} (h : Matches input a.val b.val k.val)
    (hpa : pa = core.num.Usize.wrapping_add a k) (hpb : pb = core.num.Usize.wrapping_add b k)
    (hab : a.val + k.val + 8 ≤ input.length ∧ b.val + k.val + 8 ≤ input.length)
    (hz : z.val = word8 input pa.val ^^^ word8 input pb.val)
    (hlz : lz = core.num.U64.leading_zeros z) (hq : q.val = lz.val / 8)
    (hr : r = UScalar.cast .Usize q) (hk1 : k1.val = k.val + r.val) :
    Matches input a.val b.val k1.val ∧ k1.val ≤ k.val + 8 := Q496M26!
theorem Matches.xw_zero {input : Slice Std.U8} {a b k pa pb k1 : Std.Usize} {z : Std.U64}
    (h : Matches input a.val b.val k.val)
    (hpa : pa = core.num.Usize.wrapping_add a k) (hpb : pb = core.num.Usize.wrapping_add b k)
    (hab : a.val + k.val + 8 ≤ input.length ∧ b.val + k.val + 8 ≤ input.length)
    (hz : z.val = word8 input pa.val ^^^ word8 input pb.val) (hz0 : z = 0#u64)
    (hk1 : k1.val = k.val + 8) : Matches input a.val b.val k1.val := Q496M27!
theorem Matches.word_eq {input : Slice Std.U8} {a b k : Nat} {pa pb k1 : Std.Usize}
    {x y : Std.U64}
    (h : Matches input a b k) (hpa : pa.val = a + k) (hpb : pb.val = b + k)
    (hx : x.val = word8 input pa.val) (hy : y.val = word8 input pb.val)
    (hxy : x = y) (hk1 : k1.val = k + 8) :
    Matches input a b k1.val := Q496M28!
theorem same_loop0_spec (s : Slice Std.U8) (a b len k ok : Std.Usize)
    (ha : a.val + len.val ≤ s.length) (hb : b.val + len.val ≤ s.length) (hlen : len.val ≤ 258)
    (hk : k.val ≤ len.val) (hm : Matches s a.val b.val k.val) :
    slot.q4_same_loop0 s a b len k ok ⦃ fun r =>
      r.1.val ≤ len.val ∧ Matches s a.val b.val r.1.val ∧ (r.2.val = 1 → len.val < r.1.val + 8) ⦄ := Q496M29! slot.q4_same_loop0 slot.q4_same_loop0.body
@[local step]
theorem same_loop1_spec (s : Slice Std.U8) (a b len k ok : Std.Usize)
    (ha : a.val + len.val ≤ s.length) (hb : b.val + len.val ≤ s.length)
    (hk : k.val ≤ len.val) (hm : Matches s a.val b.val k.val) :
    slot.q4_same_loop1 s a b len k ok ⦃ fun r => r.val = 1 → Matches s a.val b.val len.val ⦄ := Q496M30! slot.q4_same_loop1 slot.q4_same_loop1.body
@[local step]
theorem same_loop2_spec (s : Slice Std.U8) (a b len k ok : Std.Usize)
    (ha : a.val + len.val ≤ s.length) (hb : b.val + len.val ≤ s.length)
    (hk : k.val ≤ len.val) (hm : Matches s a.val b.val k.val) :
    slot.q4_same_loop2 s a b len k ok ⦃ fun r => r.val = 1 → Matches s a.val b.val len.val ⦄ := Q496M30! slot.q4_same_loop2 slot.q4_same_loop2.body
theorem Matches.mask {input : Slice Std.U8} {a b k len : Nat} {pa pb : Std.Usize}
    {x y z w : Std.U64} {sh : Std.U32}
    (h : Matches input a b k) (hpa : pa.val = a + k) (hpb : pb.val = b + k)
    (hx : x.val = word8 input pa.val) (hy : y.val = word8 input pb.val)
    (hz : z.val = (x ^^^ y).val) (hw : w.val = z.val >>> sh.val) (hw0 : ¬(w != 0#u64) = true)
    (hsh : sh.val = 64 - 8 * (len - k)) (hk : k < len) (hlen : len < k + 8) :
    Matches input a b len := Q496M31!
@[local step]
theorem same_spec (s : Slice Std.U8) (a b len : Std.Usize)
    (ha : a.val + len.val ≤ s.length) (hb : b.val + len.val ≤ s.length) (hlen : len.val ≤ 258)
    (ha8 : a.val + len.val + 7 ≤ Std.Usize.max) (hb8 : b.val + len.val + 7 ≤ Std.Usize.max) :
    slot.q4_same s a b len ⦃ fun r => r.val = 1 → Matches s a.val b.val len.val ⦄ := Q496M32! slot.q4_same
theorem lz32_le (x : Std.U32) (k : Nat) (hk : k < 32) (hx : 2 ^ k ≤ x.val) :
    (core.num.U32.leading_zeros x).val ≤ 31 - k := Q496M33!
@[local step]
theorem lz32_spec (x : Std.U32) :
    lift (core.num.U32.leading_zeros x) ⦃ fun r => r = core.num.U32.leading_zeros x ∧
      (4 ≤ x.val → r.val ≤ 29) ∧ (8 ≤ x.val → r.val ≤ 28) ⦄ := Q496M34!
@[local step]
theorem hcast_I32_spec {ty : UScalarTy} (x : UScalar ty) (h : x.val ≤ 2147483647) :
    lift (UScalar.hcast .I32 x) ⦃ fun y => y.val = x.val ⦄ :=
  UScalar.hcast_inBounds_spec .I32 x (by simp [I32.max_def, I32.numBits]; omega)
theorem GBASE_bound : -1000000000 ≤ slot.q4_GBASE.val ∧ slot.q4_GBASE.val ≤ 1000000000 := by
  unfold slot.q4_GBASE
  simp
@[local step]
theorem gain_spec (l d : Std.Usize) (hl : l.val ≤ 258) (hd : d.val ≤ 32768) :
    slot.q4_gain l d ⦃ fun _ => True ⦄ := Q496M35! slot.q4_gain
def HeadBound {N : Std.Usize} (head : Array Std.U32 N) (B : Nat) : Prop :=
  ∀ j : Nat, j < head.val.length → (head.val[j]!).val ≤ B
theorem HeadBound.mono {N : Std.Usize} {head : Array Std.U32 N} {B B' : Nat}
    (h : HeadBound head B) (hB : B ≤ B') : HeadBound head B' := fun j hj => le_trans (h j hj) hB
theorem HeadBound.init (N : Std.Usize) : HeadBound (Std.Array.repeat N 0#u32) 0 := Q496M36!
theorem HeadBound.set {N : Std.Usize} {head : Array Std.U32 N} {B : Nat} (h : HeadBound head B)
    (a : Std.Usize) (v : Std.U32) (hv : v.val ≤ B) : HeadBound (head.set a v) B := Q496M37!
theorem HeadBound.update {N : Std.Usize} {head head1 : Array Std.U32 N} {B : Nat}
    {a i : Std.Usize} {v : Std.U32} (h : HeadBound head B) (hv : v = UScalar.cast .U32 i)
    (hi : i.val ≤ B) (h1 : head1 = head.set a v) : HeadBound head1 B := Q496M38!
theorem HeadBound.get {N : Std.Usize} {head : Array Std.U32 N} {B : Nat} (h : HeadBound head B)
    (a : Std.Usize) (x : Std.U32) (ha : a.val < head.val.length) (hx : x = head.val[a.val]) :
    x.val ≤ B := Q496M39!
theorem cast_usize_le {x : Std.U32} {y : Std.Usize} {B : Nat} (h : y = UScalar.cast .Usize x)
    (hx : x.val ≤ B) : y.val ≤ B := Q496M40!
@[local step]
theorem be4_spec (s : Slice Std.U8) (i : Std.Usize) (hi : i.val + 4 ≤ Std.Usize.max) :
    slot.q4_be4 s i ⦃ fun _ => True ⦄ := by
  rw [slot.q4_be4]
  step*
def Cand (s : Slice Std.U8) (p cap best bd : Nat) : Prop :=
  bd = 0 ∨ (1 ≤ bd ∧ bd ≤ 32768 ∧ bd ≤ p ∧ best ≤ cap ∧ Matches s (p - bd) p best)
theorem dist_of_wrapping {p c d i : Std.Usize} (hc : c.val ≤ p.val)
    (hd : d = core.num.Usize.wrapping_sub p c) (hi : i = core.num.Usize.wrapping_sub d 1#usize)
    (hlt : i < 32768#usize) : d.val = p.val - c.val ∧ 1 ≤ d.val ∧ d.val ≤ 32768 := Q496M41!
theorem Cand.of_common {s : Slice Std.U8} {p c d i l cap : Std.Usize} (hc : c.val ≤ p.val)
    (hd : d = core.num.Usize.wrapping_sub p c) (hi : i = core.num.Usize.wrapping_sub d 1#usize)
    (hlt : i < 32768#usize) (hl : l.val ≤ cap.val) (hm : Matches s c.val p.val l.val) :
    Cand s p.val cap.val l.val d.val := Q496M42!
def MatchAt (s : Slice Std.U8) (p l d : Nat) : Prop :=
  3 ≤ l ∧ l ≤ 258 ∧ p + l ≤ s.length ∧ 1 ≤ d ∧ d ≤ 32768 ∧ d ≤ p ∧ Matches s (p - d) p l
def FoundAt (s : Slice Std.U8) (p l d : Nat) : Prop := l < 3 ∨ MatchAt s p l d
theorem FoundAt.of_cand {s : Slice Std.U8} {p cap : Nat} {l d : Std.Usize}
    (hc : Cand s p cap l.val d.val) (hd : ¬d = 0#usize) (hcap : cap ≤ 258)
    (hpl : p + l.val ≤ s.length) : FoundAt s p l.val d.val := Q496M43!
theorem Cand.len_le {s : Slice Std.U8} {p cap : Nat} {l d : Std.Usize}
    (hc : Cand s p cap l.val d.val) (hd : ¬d = 0#usize) (hcap : cap ≤ 258) : l.val ≤ 258 := Q496M44!
theorem Cand.dist_le {s : Slice Std.U8} {p cap l d : Nat} (hc : Cand s p cap l d) :
    d ≤ 32768 := Q496M45!
theorem FoundAt.none (s : Slice Std.U8) (p : Nat) : FoundAt s p (0#usize).val (0#usize).val :=
  Or.inl (by simp)
theorem FoundAt.real {s : Slice Std.U8} {p l d : Nat} (hf : FoundAt s p l d) (h3 : 3 ≤ l) :
    MatchAt s p l d := Q496M46!
theorem copyN_take_prefix (acc : List Nat) (d : Nat) :
    ∀ n, (copyN acc d n).take acc.length = acc := Q496M47!
theorem foldlM_emit_length : ∀ (ts : List Nat) (init acc : List Nat),
    ts.foldlM emit init = some acc → init.length + ts.length ≤ acc.length := Q496M48!
theorem decode_length_le {ts acc : List Nat} (h : decode ts = some acc) :
    ts.length ≤ acc.length := Q496M49!
theorem decode_pop_lit {ts : List Nat} {t : Nat} {inp : List Nat} {p : Nat}
    (hp : p ≤ inp.length) (hd : decode (ts ++ [t]) = some (inp.take p)) (ht : t < 256) :
    1 ≤ p ∧ decode ts = some (inp.take (p - 1)) := Q496M50!
theorem decode_pop_match {ts : List Nat} {t : Nat} {inp : List Nat} {p : Nat}
    (hp : p ≤ inp.length) (hd : decode (ts ++ [t]) = some (inp.take p)) (ht : 256 ≤ t) :
    tokLen t ≤ p ∧ decode ts = some (inp.take (p - tokLen t)) := Q496M51!
theorem toks_pop (out : Slice Std.U32) (nt : Nat) (h0 : 0 < nt) (hle : nt ≤ out.length) :
    toks out nt = toks out (nt - 1) ++ [(out.val[nt - 1]!).val] := Q496M52!
theorem toks_length (out : Slice Std.U32) (nt : Nat) (h : nt ≤ out.length) :
    (toks out nt).length = nt := Q496M53!
def Dec (s : Slice Std.U8) (out : Slice Std.U32) (nt p : Nat) : Prop :=
  p ≤ s.length ∧ nt ≤ p ∧ s.length ≤ out.length ∧
    decode (toks out nt) = some ((bytes s).take p)
theorem Dec.init (input : Slice Std.U8) (out : Slice Std.U32) (h : input.length ≤ out.length) :
    Dec input out (0#usize).val (0#usize).val :=
  ⟨by simp, by simp, h, by simp [toks, LZ77.decode]⟩
theorem Dec.lit {s : Slice Std.U8} {out : Slice Std.U32} {nt p : Nat} (h : Dec s out nt p)
    (hp : p < s.length) (ntU : Std.Usize) (hnt : ntU.val = nt) (v : Std.U32)
    (hv : v.val = (s.val[p]!).val) :
    Dec s (out.set ntU v) (nt + 1) (p + 1) := Q496M54!
theorem Dec.match {s : Slice Std.U8} {out : Slice Std.U32} {nt p l d : Nat} (h : Dec s out nt p)
    (hm : MatchAt s p l d) (ntU : Std.Usize) (hnt : ntU.val = nt) (v : Std.U32)
    (hv : v.val = LZ77.mkMatch d l) :
    Dec s (out.set ntU v) (nt + 1) (p + l) := Q496M55!
theorem Dec.pop_lit {s : Slice Std.U8} {out : Slice Std.U32} {nt p : Nat} (h : Dec s out nt p)
    (h0 : 0 < nt) (hle : nt ≤ out.length) (ht : (out.val[nt - 1]!).val < 256) :
    1 ≤ p ∧ Dec s out (nt - 1) (p - 1) := Q496M56!
theorem Dec.pop_match {s : Slice Std.U8} {out : Slice Std.U32} {nt p : Nat} (h : Dec s out nt p)
    (h0 : 0 < nt) (hle : nt ≤ out.length) (ht : 256 ≤ (out.val[nt - 1]!).val) :
    tokLen (out.val[nt - 1]!).val ≤ p ∧
      Dec s out (nt - 1) (p - tokLen (out.val[nt - 1]!).val) := Q496M57!
theorem Dec.done {s : Slice Std.U8} {out : Slice Std.U32} {nt p : Nat} (h : Dec s out nt p)
    (hp : s.length ≤ p) : nt ≤ s.length ∧ LZ77.Valid (bytes s) (toks out nt) := Q496M58!
theorem Dec.lit_step {s : Slice Std.U8} {out out1 : Slice Std.U32} {ntU nt1 pU : Std.Usize}
    {b : Std.U8} {v : Std.U32} (h : Dec s out ntU.val pU.val) (hp : pU.val < s.val.length)
    (hb : b = s.val[pU.val]) (hv : v = UScalar.cast .U32 b) (hout1 : out1 = out.set ntU v)
    (hnt1 : nt1.val = ntU.val + 1) :
    nt1.val = ntU.val + 1 ∧ out1.length = out.length ∧ Dec s out1 nt1.val (pU.val + 1) := Q496M59!
@[local step]
theorem put_lit_spec (s : Slice Std.U8) (out : Slice Std.U32) (nt p : Std.Usize)
    (hdec : Dec s out nt.val p.val) (hp : p.val < s.length) :
    slot.q4_put_lit s out nt p ⦃ fun r => r.1.val = nt.val + 1 ∧ r.2.length = out.length ∧
      Dec s r.2 r.1.val (p.val + 1) ⦄ := Q496M60! slot.q4_put_lit
theorem Dec.match_step {s : Slice Std.U8} {out out1 : Slice Std.U32} {ntU nt1 pU dU lU e : Std.Usize}
    {v : Std.U32} (h : Dec s out ntU.val pU.val) (hm : MatchAt s pU.val lU.val dU.val)
    (hout1 : out1 = out.set ntU v) (hv : v.val = LZ77.mkMatch dU.val lU.val)
    (hnt1 : nt1.val = ntU.val + 1) (he : e.val = pU.val + lU.val) :
    nt1.val = ntU.val + 1 ∧ e.val = pU.val + lU.val ∧ out1.length = out.length ∧
      Dec s out1 nt1.val e.val := Q496M61!
@[local step]
theorem put_match_spec (s : Slice Std.U8) (out : Slice Std.U32) (nt p d l : Std.Usize)
    (hdec : Dec s out nt.val p.val) (hm : MatchAt s p.val l.val d.val) :
    slot.q4_put_match s out nt p d l ⦃ fun r => r.1.1.val = nt.val + 1 ∧
      r.1.2.val = p.val + l.val ∧ r.2.length = out.length ∧ Dec s r.2 r.1.1.val r.1.2.val ⦄ := Q496M62! slot.q4_put_match
theorem MatchAt.back_lit {s : Slice Std.U8} {p l d : Nat} (h : MatchAt s p l d) (hl : l < 258)
    (hdp : d < p) (heq : s.val[p - 1]! = s.val[p - 1 - d]!) : MatchAt s (p - 1) (l + 1) d := Q496M63!
theorem MatchAt.back_match {s : Slice Std.U8} {p l d w : Nat} (h : MatchAt s p l d)
    (hlw : l + w ≤ 258) (hw : w ≤ p) (hdw : d ≤ p - w) (hmw : Matches s (p - w - d) (p - w) w) :
    MatchAt s (p - w) (l + w) d := Q496M64!
def BackInv (input : Slice Std.U8) (out : Slice Std.U32) (d E P0 : Nat) (nt p l : Nat) : Prop :=
  Dec input out nt p ∧ MatchAt input p l d ∧ p + l = E ∧ p ≤ P0
theorem BackInv.lit {input : Slice Std.U8} {out : Slice Std.U32} {d E P0 : Nat}
    {nt p l i1 i2 i4 l1 : Std.Usize} {t : Std.U32} {x y : Std.U8}
    (h : BackInv input out d E P0 nt.val p.val l.val)
    (hi1 : i1.val = nt.val - 1) (hntl : nt.val ≤ out.length) (hnt0 : 1 ≤ nt.val)
    (hi1l : i1.val < out.val.length) (ht : t = out.val[i1.val]) (ht256 : t < 256#u32)
    (hi2 : i2.val = p.val - 1) (hi2l : i2.val < input.val.length) (hx : x = input.val[i2.val])
    (hxy : x = y) (hi4 : i4.val = i2.val - d) (hi4l : i4.val < input.val.length)
    (hy : y = input.val[i4.val]) (hl : l.val < 258) (hdp : d < p.val)
    (hl1 : l1.val = l.val + 1) :
    BackInv input out d E P0 i1.val i2.val l1.val := Q496M65!
theorem BackInv.match {input : Slice Std.U8} {out : Slice Std.U32} {d E P0 : Nat}
    {nt p l i1 w i9 i10 i11 i12 : Std.Usize} {t : Std.U32}
    (h : BackInv input out d E P0 nt.val p.val l.val)
    (hi1 : i1.val = nt.val - 1) (hntl : nt.val ≤ out.length) (hnt0 : 1 ≤ nt.val)
    (hi1l : i1.val < out.val.length) (ht : t = out.val[i1.val])
    (hsame : i12.val = 1 → Matches input i11.val i10.val w.val) (hi12 : i12 = 1#usize)
    (ht24 : 16777216 ≤ t.val) (hwv : w.val = (t.val - 16777216) % 256 + 3)
    (hi9 : i9.val = l.val + w.val) (hi9' : i9.val ≤ 258) (hi10 : i10.val = p.val - w.val)
    (hwp : w.val ≤ p.val) (hdw : d ≤ i10.val) (hi11 : i11.val = i10.val - d) :
    BackInv input out d E P0 i1.val i10.val i9.val := Q496M66!
theorem fold_loop_inv (input : Slice Std.U8) (out : Slice Std.U32) (nt p l d back : Std.Usize)
    (E P0 : Nat) (hP0 : P0 + 8 ≤ input.length)
    (hinv : BackInv input out d.val E P0 nt.val p.val l.val) :
    slot.q4_fold_loop input out d nt p l back ⦃ fun r =>
      BackInv input out d.val E P0 r.1.val r.2.1.val r.2.2.val ⦄ := Q496M67! slot.q4_fold_loop slot.q4_BACKTOK.val slot.q4_fold_loop.body
@[local step]
theorem fold_spec (input : Slice Std.U8) (out : Slice Std.U32) (nt p l d : Std.Usize)
    (hp8 : p.val + 8 ≤ input.length) (hdec : Dec input out nt.val p.val)
    (hm : MatchAt input p.val l.val d.val) :
    slot.q4_fold input out nt p l d ⦃ fun r =>
      Dec input out r.1.val r.2.1.val ∧ MatchAt input r.2.1.val r.2.2.val d.val ∧
      r.2.1.val + r.2.2.val = p.val + l.val ∧ r.2.1.val ≤ p.val ⦄ := Q496M68!
@[local step]
theorem fold_w_spec (input : Slice Std.U8) (out : Slice Std.U32) (nt p l d : Std.Usize)
    (hp8 : p.val + 8 ≤ input.length) (hdec : Dec input out nt.val p.val)
    (hm : MatchAt input p.val l.val d.val) :
    slot.q4_fold_w input out nt p l d ⦃ fun r =>
      Dec input out r.1.val r.2.1.val ∧ MatchAt input r.2.1.val r.2.2.val d.val ∧
      r.2.1.val + r.2.2.val = p.val + l.val ∧ r.2.1.val ≤ p.val ⦄ := Q496M69! slot.q4_fold_w
def LazyInv (input : Slice Std.U8) (L lim : Nat) (out : Slice Std.U32) (nt p : Nat)
    {N : Std.Usize} (head : Array Std.U32 N) (ins l d : Nat) : Prop :=
  Dec input out nt p ∧ out.length = L ∧ MatchAt input p l d ∧ HeadBound head (p + 1) ∧
    p < lim ∧ ins ≤ p + 2
theorem LazyInv.accept {input : Slice Std.U8} {L lim p' B : Nat} {out1 : Slice Std.U32}
    {nt1 i ins1 l1 d1 minl : Std.Usize} {N : Std.Usize} {head1 : Array Std.U32 N}
    (hdec : Dec input out1 nt1.val p') (hi : i.val = p') (hlen : out1.length = L)
    (hf : FoundAt input i.val l1.val d1.val) (hl1 : minl.val ≤ l1.val) (hminl : 3 ≤ minl.val)
    (hB : HeadBound head1 B) (hBi : B ≤ i.val + 1) (hilim : i.val < lim)
    (hins : ins1.val ≤ i.val + 2) :
    LazyInv input L lim out1 nt1.val i.val head1 ins1.val l1.val d1.val := Q496M70!
theorem LazyInv.reject {input : Slice Std.U8} {L lim : Nat} {out : Slice Std.U32}
    {nt p ins ins1 l d B : Nat} {N : Std.Usize} {head head1 : Array Std.U32 N}
    (h : LazyInv input L lim out nt p head ins l d) (hB : HeadBound head1 B) (hBp : B ≤ p + 1)
    (hins1 : ins1 ≤ p + 2) : LazyInv input L lim out nt p head1 ins1 l d := Q496M71!
theorem numBits_ge : 32 ≤ System.Platform.numBits := Q496M72!
def MainInv (input : Slice Std.U8) (L : Nat) (out : Slice Std.U32) (nt p : Nat)
    {N : Std.Usize} (head : Array Std.U32 N) (miss : Nat) : Prop :=
  Dec input out nt p ∧ out.length = L ∧ HeadBound head p ∧ miss ≤ p
theorem MainInv.mk' {input : Slice Std.U8} {L : Nat} {out : Slice Std.U32} {nt p m B : Nat}
    {N : Std.Usize} {head : Array Std.U32 N} (hdec : Dec input out nt p) (hlen : out.length = L)
    (hB : HeadBound head B) (hBp : B ≤ p) (hm : m ≤ p) : MainInv input L out nt p head m :=
  ⟨hdec, hlen, HeadBound.mono hB hBp, hm⟩
def CntBound (cnt : Array Std.U32 256#usize) (T : Nat) : Prop :=
  ∀ j : Nat, j < 256 → (cnt.val[j]!).val ≤ T
theorem CntBound.init : CntBound (Std.Array.repeat 256#usize 0#u32) 0 := Q496M1!
theorem CntBound.get {cnt : Array Std.U32 256#usize} {T : Nat} (h : CntBound cnt T)
    (a : Std.Usize) (x : Std.U32) (ha : a.val < cnt.val.length) (hx : x = cnt.val[a.val]) :
    x.val ≤ T := Q496M2!
@[local step]
theorem cnt_index_spec (cnt : Array Std.U32 256#usize) (T : Nat) (h : CntBound cnt T)
    (i : Std.Usize) (hi : i.val < 256) :
    Std.Array.index_usize cnt i ⦃ fun x => x = cnt.val[i.val]! ∧ x.val ≤ T ⦄ := Q496M3!
theorem CntBound.update {cnt : Array Std.U32 256#usize} {T : Nat} (h : CntBound cnt T)
    (a : Std.Usize) (v : Std.U32) (hv : v.val ≤ T + 1) : CntBound (cnt.set a v) (T + 1) := Q496M4!
theorem CntBound.step {cnt a : Array Std.U32 256#usize} {T : Nat} {x : Std.Usize}
    {v tot1 : Std.U32} (hc : CntBound cnt T) (ha : a = cnt.set x v) (hv : v.val ≤ T + 1)
    (ht1 : tot1.val = T + 1) : CntBound a tot1.val := Q496M5!
theorem CntBound.mono {cnt : Array Std.U32 256#usize} {T T' : Nat} (h : CntBound cnt T)
    (hT : T ≤ T') : CntBound cnt T' := fun j hj => le_trans (h j hj) hT
@[local step]
theorem lift_spec {α : Type} (x : α) : lift x ⦃ fun y => y = x ⦄ := by
  simp [lift]
theorem Dec.cast {s : Slice Std.U8} {out : Slice Std.U32} {nt p p' : Nat} (h : Dec s out nt p)
    (hp : p = p') : Dec s out nt p' := hp ▸ h
@[local step]
theorem slot_of_spec (H : Std.Usize) (s : Slice Std.U8) (i : Std.Usize)
    (hi4 : i.val + 4 ≤ Std.Usize.max) (hH : 0 < H.val) :
    slot.q4_slot_of H s i ⦃ fun r => r.val < H.val ⦄ := by
  rw [slot.q4_slot_of]
  step*
@[local step]
theorem head_set_spec {H : Std.Usize} (head : Array Std.U32 H) (a i : Std.Usize) (B : Nat)
    (hB : HeadBound head B) (ha : a.val < H.val) (hi : i.val < B + 1) :
    slot.q4_head_set head a i ⦃ fun r => HeadBound r B ⦄ := Q496M73! slot.q4_head_set
@[local step]
theorem ahead_spec {H : Std.Usize} (s : Slice Std.U8) (head : Array Std.U32 H) (i : Std.Usize)
    (B : Nat) (hB : HeadBound head B) (hBn : B + 8 ≤ s.length)
    (hi4 : i.val + 4 ≤ Std.Usize.max) (hH : 0 < H.val) :
    slot.q4_ahead s head i ⦃ fun r => r.1.val < H.val ∧ r.2.1.val ≤ B ∧
      r.2.2.val = word8 s r.2.1.val ⦄ := Q496M74! slot.q4_ahead
@[local step]
theorem ahead_if_spec {H : Std.Usize} (s : Slice Std.U8) (head : Array Std.U32 H)
    (i lim a c : Std.Usize) (w : Std.U64) (B : Nat) (hB : HeadBound head B)
    (hBi : B < i.val + 1) (hlim : lim.val + 8 = s.length) (ha : a.val < H.val)
    (hc : c.val < B + 1) (hw : w.val = word8 s c.val) (hH : 0 < H.val) :
    slot.q4_ahead_if s head i lim a c w ⦃ fun r => r.1.val < H.val ∧ r.2.1.val ≤ B ∧
      r.2.2.val = word8 s r.2.1.val ⦄ := Q496M75! slot.q4_ahead_if
theorem common_from_loop0_spec (s : Slice Std.U8) (a b cap k : Std.Usize) (run : Std.U32)
    (ha : a.val + cap.val ≤ s.length) (hb : b.val + cap.val ≤ s.length) (hcap : cap.val ≤ 258)
    (hk : k.val ≤ cap.val) (hm : Matches s a.val b.val k.val) :
    slot.q4_common_from_loop0 s a b cap k run ⦃ fun r =>
      r.1.val ≤ cap.val ∧ Matches s a.val b.val r.1.val ⦄ := Q496M76! slot.q4_common_from_loop0 slot.q4_common_from_loop0.body
theorem common_from_loop1_spec (s : Slice Std.U8) (a b cap k : Std.Usize) (run : Std.U32)
    (ha : a.val + cap.val ≤ s.length) (hb : b.val + cap.val ≤ s.length)
    (hk : k.val ≤ cap.val) (hm : Matches s a.val b.val k.val) :
    slot.q4_common_from_loop1 s a b cap k run ⦃ fun r =>
      r.val ≤ cap.val ∧ Matches s a.val b.val r.val ⦄ := Q496M77! slot.q4_common_from_loop1 slot.q4_common_from_loop1.body
@[local step]
theorem common_from_spec (s : Slice Std.U8) (a b cap k0 : Std.Usize)
    (ha : a.val + cap.val ≤ s.length) (hb : b.val + cap.val ≤ s.length) (hcap : cap.val ≤ 258)
    (hk0 : k0.val ≤ cap.val) (hm : Matches s a.val b.val k0.val) :
    slot.q4_common_from s a b cap k0 ⦃ fun l => l.val ≤ cap.val ∧ Matches s a.val b.val l.val ⦄ := Q496M78! slot.q4_common_from
theorem Matches.xor_lz {s : Slice Std.U8} {c p m : Std.Usize} {cw y x : Std.U64}
    {lz q : Std.U32} (hcw : cw.val = word8 s c.val) (hy : y.val = word8 s p.val)
    (hx : x.val = (cw ^^^ y).val) (hx0 : (x != 0#u64) = true)
    (hlz : lz = core.num.U64.leading_zeros x) (hq : q.val = lz.val / 8)
    (hm : m = UScalar.cast .Usize q) : Matches s c.val p.val m.val ∧ m.val < 8 := Q496M79!
theorem Matches.xor_zero {s : Slice Std.U8} {c p : Std.Usize} {cw y x : Std.U64}
    (hcw : cw.val = word8 s c.val) (hy : y.val = word8 s p.val)
    (hx : x.val = (cw ^^^ y).val) (hx0 : ¬(x != 0#u64) = true) :
    Matches s c.val p.val (8#usize).val := Q496M80!
theorem FoundAt.of_matches {s : Slice Std.U8} {p c d i l : Std.Usize} (hc : c.val ≤ p.val)
    (hd : d = core.num.Usize.wrapping_sub p c) (hi : i = core.num.Usize.wrapping_sub d 1#usize)
    (hlt : i < 32768#usize) (hl : l.val ≤ 258) (hpl : p.val + l.val ≤ s.length)
    (hm : Matches s c.val p.val l.val) :
    FoundAt s p.val l.val d.val ∧ l.val ≤ 258 ∧ d.val ≤ 32768 := Q496M81!
theorem FoundAt.none' (s : Slice Std.U8) (p : Nat) :
    FoundAt s p (0#usize).val (0#usize).val ∧ (0#usize).val ≤ 258 ∧ (0#usize).val ≤ 32768 :=
  ⟨FoundAt.none s p, by simp, by simp⟩
@[local step]
theorem xlen_spec (s : Slice Std.U8) (c p : Std.Usize) (x cw y : Std.U64)
    (hx : x.val = (cw ^^^ y).val) (hcw : cw.val = word8 s c.val) (hy : y.val = word8 s p.val)
    (hc : c.val ≤ p.val) (hp : p.val + 8 ≤ s.length) :
    slot.q4_xlen s c p x ⦃ fun r => r.val ≤ 258 ∧ p.val + r.val ≤ s.length ∧
      Matches s c.val p.val r.val ⦄ := Q496M82! slot.q4_xlen
theorem Matches.x16a {s : Slice Std.U8} {c p i1 i2 r l : Std.Usize} {x x2 : Std.U64}
    {lz q : Std.U32} (hx : x.val = word8 s c.val ^^^ word8 s p.val) (hx0 : x = 0#u64)
    (hi1 : i1.val = c.val + 8) (hi2 : i2.val = p.val + 8)
    (hx2 : x2.val = word8 s i1.val ^^^ word8 s i2.val)
    (hlz : lz = core.num.U64.leading_zeros x2) (hq : q.val = lz.val / 8)
    (hr : r = UScalar.cast .Usize q) (hl : l.val = 8 + r.val) :
    Matches s c.val p.val l.val ∧ l.val ≤ 16 := Q496M83!
theorem Matches.x16a' {s : Slice Std.U8} {c p i1 i2 r l : Std.Usize} {x x2 : Std.U64}
    {lz q : Std.U32} (hx : x.val = word8 s c.val ^^^ word8 s p.val) (hx0 : x = 0#u64)
    (hi1 : i1.val = c.val + 8) (hi2 : i2.val = p.val + 8)
    (hx2 : x2.val = word8 s i1.val ^^^ word8 s i2.val)
    (hlz : lz = core.num.U64.leading_zeros x2) (hq : q.val = lz.val / 8)
    (hr : r = UScalar.cast .Usize q) (hl : l.val = 8 + r.val) (hpn : p.val + 16 ≤ s.length) :
    l.val ≤ 258 ∧ p.val + l.val ≤ s.length ∧ Matches s c.val p.val l.val := by
  have h := Matches.x16a hx hx0 hi1 hi2 hx2 hlz hq hr hl
  exact ⟨by omega, by omega, h.1⟩
theorem Matches.x16b {s : Slice Std.U8} {c p r l : Std.Usize} {x : Std.U64}
    {lz q : Std.U32} (hx : x.val = word8 s c.val ^^^ word8 s p.val)
    (hlz : lz = core.num.U64.leading_zeros x) (hq : q.val = lz.val / 8)
    (hr : r = UScalar.cast .Usize q) (hl : l.val = 0 + r.val) (hpn : p.val + 8 ≤ s.length) :
    l.val ≤ 258 ∧ p.val + l.val ≤ s.length ∧ Matches s c.val p.val l.val := Q496M84!
@[local step]
theorem xlen16_spec (s : Slice Std.U8) (c p : Std.Usize) (x cw y : Std.U64)
    (hx : x.val = (cw ^^^ y).val) (hcw : cw.val = word8 s c.val) (hy : y.val = word8 s p.val)
    (hc : c.val ≤ p.val) (hp : p.val + 8 ≤ s.length) :
    slot.q4_xlen16 s c p x ⦃ fun r => r.val ≤ 258 ∧ p.val + r.val ≤ s.length ∧
      Matches s c.val p.val r.val ⦄ := Q496M85! slot.q4_xlen16
@[local step]
theorem probe_spec (s : Slice Std.U8) (c : Std.Usize) (cw : Std.U64) (p : Std.Usize)
    (hc : c.val ≤ p.val) (hcw : cw.val = word8 s c.val) (hp : p.val + 8 ≤ s.length) :
    slot.q4_probe s c cw p ⦃ fun r => FoundAt s p.val r.1.val r.2.val ∧ r.1.val ≤ 258 ∧
      r.2.val ≤ 32768 ⦄ := Q496M86! slot.q4_probe
@[local step]
theorem lazy_lo_spec (l : Std.Usize) :
    slot.q4_lazy_lo l ⦃ fun r => r.val = 3 ∨ (3 < r.val ∧ r.val + slot.q4_LSLACK.val = l.val) ⦄ := by
  rw [slot.q4_lazy_lo]
  step*
@[local step]
theorem probe_lazy_spec (s : Slice Std.U8) (c : Std.Usize) (cw : Std.U64) (q l : Std.Usize)
    (hc : c.val ≤ q.val) (hcw : cw.val = word8 s c.val) (hq : q.val + 8 ≤ s.length)
    (hl : q.val + l.val ≤ s.length + 1) :
    slot.q4_probe_lazy s c cw q l ⦃ fun r => FoundAt s q.val r.1.val r.2.val ∧ r.1.val ≤ 258 ∧
      r.2.val ≤ 32768 ⦄ := Q496M87! slot.q4_probe_lazy slot.q4_LSLACK.val
@[local step]
theorem skip_len_spec (miss skip skcap : Std.Usize) (hskip : skip.val < 32) :
    slot.q4_skip_len miss skip skcap ⦃ fun _ => True ⦄ := by
  rw [slot.q4_skip_len]
  have := numBits_ge
  step*
@[local step]
theorem skip_to_spec (p step lim : Std.Usize) (hp : p.val ≤ lim.val) :
    slot.q4_skip_to p step lim ⦃ fun r => p.val ≤ r.val ∧ r.val ≤ lim.val ⦄ := by
  rw [slot.q4_skip_to]
  step*
  exact ⟨by scalar_tac, by scalar_tac⟩
@[local step]
theorem slot_of_m_spec (H : Std.Usize) (s : Slice Std.U8) (i : Std.Usize) (km : Std.U32)
    (hi4 : i.val + 4 ≤ Std.Usize.max) (hH : 0 < H.val) :
    slot.q4_slot_of_m H s i km ⦃ fun r => r.val < H.val ⦄ := by
  rw [slot.q4_slot_of_m]
  step*
@[local step]
theorem ahead_m_spec {H : Std.Usize} (s : Slice Std.U8) (head : Array Std.U32 H) (i : Std.Usize)
    (km : Std.U32) (B : Nat) (hB : HeadBound head B) (hBn : B + 8 ≤ s.length)
    (hi4 : i.val + 4 ≤ Std.Usize.max) (hH : 0 < H.val) :
    slot.q4_ahead_m s head i km ⦃ fun r => r.1.val < H.val ∧ r.2.1.val ≤ B ∧
      r.2.2.val = word8 s r.2.1.val ⦄ := Q496M74! slot.q4_ahead_m
@[local step]
theorem ahead_if_m_spec {H : Std.Usize} (s : Slice Std.U8) (head : Array Std.U32 H)
    (i lim a c : Std.Usize) (w : Std.U64) (km : Std.U32) (B : Nat) (hB : HeadBound head B)
    (hBi : B < i.val + 1) (hlim : lim.val + 8 = s.length) (ha : a.val < H.val)
    (hc : c.val < B + 1) (hw : w.val = word8 s c.val) (hH : 0 < H.val) :
    slot.q4_ahead_if_m s head i lim a c w km ⦃ fun r => r.1.val < H.val ∧ r.2.1.val ≤ B ∧
      r.2.2.val = word8 s r.2.1.val ⦄ := Q496M75! slot.q4_ahead_if_m
@[local step]
theorem ahead_fix_m_spec {H : Std.Usize} (s : Slice Std.U8) (head : Array Std.U32 H)
    (i lim e a c : Std.Usize) (w : Std.U64) (a0 c0 : Std.Usize) (w0 : Std.U64) (km : Std.U32)
    (B : Nat) (hB : HeadBound head B) (hBi : B < i.val + 1) (hlim : lim.val + 8 = s.length)
    (hw : w.val = word8 s c.val) (ha0 : a0.val < H.val) (hc0 : c0.val < B + 1)
    (hw0 : w0.val = word8 s c0.val) (hH : 0 < H.val) :
    slot.q4_ahead_fix_m s head i lim e a c w a0 c0 w0 km ⦃ fun r => r.1.val < H.val ∧
      r.2.1.val ≤ B ∧ r.2.2.val = word8 s r.2.1.val ⦄ := Q496M88! slot.q4_ahead_fix_m
@[local step]
theorem probe_m_spec (s : Slice Std.U8) (c : Std.Usize) (cw : Std.U64) (p : Std.Usize)
    (km : Std.U32) (hc : c.val ≤ p.val) (hcw : cw.val = word8 s c.val)
    (hp : p.val + 8 ≤ s.length) :
    slot.q4_probe_m s c cw p km ⦃ fun r => FoundAt s p.val r.1.val r.2.val ∧ r.1.val ≤ 258 ∧
      r.2.val ≤ 32768 ⦄ := Q496M86! slot.q4_probe_m
theorem flush_loop_spec (input : Slice Std.U8) (out : Slice Std.U32) (e nt j : Std.Usize)
    (hdec : Dec input out nt.val j.val) (he : e.val ≤ input.length) (hj : j.val ≤ e.val) :
    slot.q4_flush_loop input out e nt j ⦃ fun r => Dec input r.2 r.1.val e.val ∧
      r.2.length = out.length ⦄ := Q496M89! slot.q4_flush_loop slot.q4_flush_loop.body
@[local step]
theorem flush_spec (input : Slice Std.U8) (out : Slice Std.U32) (nt a e : Std.Usize)
    (hdec : Dec input out nt.val a.val) (he : e.val ≤ input.length) (ha : a.val ≤ e.val) :
    slot.q4_flush input out nt a e ⦃ fun r => Dec input r.2 r.1.val e.val ∧
      r.2.length = out.length ⦄ :=
  flush_loop_spec input out e nt a hdec he ha
@[local step]
theorem record_loop0_spec {H : Std.Usize} (s : Slice Std.U8) (head : Array Std.U32 H)
    (ins stop : Std.Usize) (B : Nat) (hB : HeadBound head B) (hsB : stop.val < B + 1)
    (hs4 : stop.val + 4 ≤ Std.Usize.max) (hH : 0 < H.val) :
    slot.q4_record_loop0 s head ins stop ⦃ fun r =>
      HeadBound r.1 B ∧ (r.2.val ≤ ins.val ∨ r.2.val ≤ stop.val) ⦄ := Q496M90! slot.q4_record_loop0 slot.q4_record_loop0.body
@[local step]
theorem record_loop1_spec {H : Std.Usize} (s : Slice Std.U8) (head : Array Std.U32 H)
    («end» lim ins : Std.Usize) (B : Nat) (hB : HeadBound head B) (heB : «end».val < B + 1)
    (hl4 : lim.val + 4 ≤ Std.Usize.max) (hH : 0 < H.val) :
    slot.q4_record_loop1 s head «end» lim ins ⦃ fun r => HeadBound r B ⦄ := Q496M91! slot.q4_record_loop1 slot.q4_record_loop1.body
@[local step]
theorem record_spec {H : Std.Usize} (s : Slice Std.U8) (head : Array Std.U32 H)
    (ins0 «end» lim : Std.Usize) (B : Nat) (hB : HeadBound head B) (heB : «end».val < B + 1)
    (hlim : lim.val + 8 = s.length) (hins : ins0.val ≤ lim.val + 1) (hH : 0 < H.val) :
    slot.q4_record s head ins0 «end» lim ⦃ fun r => HeadBound r B ⦄ := Q496M92! slot.q4_record
theorem Dec.set_beyond {s : Slice Std.U8} {out : Slice Std.U32} {nt p : Nat} (h : Dec s out nt p)
    (i : Std.Usize) (v : Std.U32) (hi : nt ≤ i.val) : Dec s (out.set i v) nt p := Q496M93!
theorem Dec.flush4_step {s : Slice Std.U8} {out out1 out2 out3 out4 : Slice Std.U32}
    {nt a e j r i7 i9 i11 i13 i15 i17 : Std.Usize} {b0 b1 b2 b3 : Std.U8}
    {v0 v1 v2 v3 : Std.U32}
    (h : Dec s out nt.val a.val) (hae : a.val ≤ e.val) (hj : j.val = e.val - a.val)
    (hj4 : j.val ≤ 4) (ha4 : a.val + 4 ≤ s.length) (hnt4 : nt.val + 4 ≤ out.length)
    (ha0 : a.val < s.val.length) (hb0 : b0 = s.val[a.val]) (hv0 : v0 = UScalar.cast .U32 b0)
    (ho1 : out1 = out.set nt v0)
    (hi7 : i7.val = a.val + 1) (ha1 : i7.val < s.val.length) (hb1 : b1 = s.val[i7.val])
    (hi9 : i9.val = nt.val + 1) (hv1 : v1 = UScalar.cast .U32 b1) (ho2 : out2 = out1.set i9 v1)
    (hi11 : i11.val = a.val + 2) (ha2 : i11.val < s.val.length) (hb2 : b2 = s.val[i11.val])
    (hi13 : i13.val = nt.val + 2) (hv2 : v2 = UScalar.cast .U32 b2) (ho3 : out3 = out2.set i13 v2)
    (hi15 : i15.val = a.val + 3) (ha3 : i15.val < s.val.length) (hb3 : b3 = s.val[i15.val])
    (hi17 : i17.val = nt.val + 3) (hv3 : v3 = UScalar.cast .U32 b3) (ho4 : out4 = out3.set i17 v3)
    (hr : r.val = nt.val + j.val) :
    Dec s out4 r.val e.val ∧ out4.length = out.length := Q496M94!
@[local step]
theorem flush4_spec (input : Slice Std.U8) (out : Slice Std.U32) (nt a e : Std.Usize)
    (hdec : Dec input out nt.val a.val) (he : e.val + 8 ≤ input.length) (ha : a.val ≤ e.val) :
    slot.q4_flush4 input out nt a e ⦃ fun r => Dec input r.2 r.1.val e.val ∧
      r.2.length = out.length ⦄ := Q496M95! slot.q4_flush4
@[local step]
theorem record3_m_loop0_spec {H : Std.Usize} (s : Slice Std.U8) (head : Array Std.U32 H)
    (km : Std.U32) (ins stop : Std.Usize) (B : Nat) (hB : HeadBound head B)
    (hsB : stop.val < B + 1) (hs4 : stop.val + 4 ≤ Std.Usize.max) (hH : 0 < H.val) :
    slot.q4_record3_m_loop0 s head km ins stop ⦃ fun r =>
      HeadBound r.1 B ∧ (r.2.val ≤ ins.val ∨ r.2.val ≤ stop.val) ⦄ := Q496M90! slot.q4_record3_m_loop0 slot.q4_record3_m_loop0.body
@[local step]
theorem record3_m_loop1_spec {H : Std.Usize} (s : Slice Std.U8) (head : Array Std.U32 H)
    («end» lim : Std.Usize) (km : Std.U32) (ins : Std.Usize) (B : Nat) (hB : HeadBound head B)
    (heB : «end».val < B + 1) (hl4 : lim.val + 4 ≤ Std.Usize.max) (hH : 0 < H.val) :
    slot.q4_record3_m_loop1 s head «end» lim km ins ⦃ fun r => HeadBound r B ⦄ := Q496M91! slot.q4_record3_m_loop1 slot.q4_record3_m_loop1.body
@[local step]
theorem record3_m_spec {H : Std.Usize} (s : Slice Std.U8) (head : Array Std.U32 H)
    (ins0 a0 «end» lim : Std.Usize) (km : Std.U32) (B : Nat) (hB : HeadBound head B)
    (heB : «end».val < B + 1) (hlim : lim.val + 8 = s.length) (hins : ins0.val ≤ lim.val + 1)
    (hH : 0 < H.val) :
    slot.q4_record3_m s head ins0 a0 «end» lim km ⦃ fun r => HeadBound r B ⦄ := Q496M92! slot.q4_record3_m
def LazyInv1 (input : Slice Std.U8) (lim P0 : Nat) (p : Nat) {N : Std.Usize}
    (head : Array Std.U32 N) (ps pc pw l d ins : Nat) : Prop :=
  MatchAt input p l d ∧ HeadBound head (p + 1) ∧ p < lim ∧ ins ≤ p + 2 ∧ ps < N.val ∧
    pc ≤ p + 1 ∧ pw = word8 input pc ∧ P0 ≤ p
theorem LazyInv1.accept {input : Slice Std.U8} {lim P0 B : Nat}
    {i ins1 l1 d1 ps pc : Std.Usize} {pw : Std.U64} {N : Std.Usize} {head1 : Array Std.U32 N}
    (hf : FoundAt input i.val l1.val d1.val) (hl1 : 3 ≤ l1.val)
    (hB : HeadBound head1 B) (hBi : B ≤ i.val + 1) (hilim : i.val < lim)
    (hins : ins1.val ≤ i.val + 2) (hps : ps.val < N.val) (hpc : pc.val ≤ i.val + 1)
    (hpw : pw.val = word8 input pc.val) (hP : P0 ≤ i.val) :
    LazyInv1 input lim P0 i.val head1 ps.val pc.val pw.val l1.val d1.val ins1.val :=
  ⟨FoundAt.real hf hl1, HeadBound.mono hB hBi, hilim, hins, hps, hpc, hpw, hP⟩
theorem LazyInv1.reject {input : Slice Std.U8} {lim P0 : Nat}
    {p ps pc pw l d ins B ps1 pc1 pw1 ins1 : Nat} {N : Std.Usize}
    {head head1 : Array Std.U32 N}
    (h : LazyInv1 input lim P0 p head ps pc pw l d ins) (hB : HeadBound head1 B)
    (hBp : B ≤ p + 1) (hins1 : ins1 ≤ p + 2) (hps : ps1 < N.val) (hpc : pc1 ≤ p + 1)
    (hpw : pw1 = word8 input pc1) :
    LazyInv1 input lim P0 p head1 ps1 pc1 pw1 l d ins1 := Q496M96!
theorem lazy1_loop_inv {H : Std.Usize} (input : Slice Std.U8) (lazy : Std.Usize) (km : Std.U32)
    (p : Std.Usize)
    (head : Array Std.U32 H) (lim pre_slot pre_c : Std.Usize) (pre_w : Std.U64)
    (l d ins : Std.Usize) (go : Std.U32) (P0 : Nat)
    (hlim : lim.val + 8 = input.length) (hH : 0 < H.val)
    (hinv : LazyInv1 input lim.val P0 p.val head pre_slot.val pre_c.val pre_w.val l.val d.val
      ins.val) :
    slot.q4_run1_loop0_loop0 input lazy km p head lim pre_slot pre_c pre_w l d ins go ⦃ fun r =>
      LazyInv1 input lim.val P0 r.1.val r.2.1 r.2.2.1.val r.2.2.2.1.val r.2.2.2.2.1.val
        r.2.2.2.2.2.1.val r.2.2.2.2.2.2.1.val r.2.2.2.2.2.2.2.val ⦄ := Q496M97! slot.q4_run1_loop0_loop0 slot.q4_run1_loop0_loop0.body
@[local step]
theorem lazy1_loop_spec {H : Std.Usize} (input : Slice Std.U8) (lazy : Std.Usize) (km : Std.U32)
    (p : Std.Usize)
    (head : Array Std.U32 H) (lim pre_slot pre_c : Std.Usize) (pre_w : Std.U64)
    (l d ins : Std.Usize) (go : Std.U32)
    (hlim : lim.val + 8 = input.length) (hH : 0 < H.val)
    (hm : MatchAt input p.val l.val d.val)
    (hB : HeadBound head (p.val + 1)) (hplim : p.val < lim.val) (hins : ins.val ≤ p.val + 2)
    (hps : pre_slot.val < H.val) (hpc : pre_c.val ≤ p.val + 1)
    (hpw : pre_w.val = word8 input pre_c.val) :
    slot.q4_run1_loop0_loop0 input lazy km p head lim pre_slot pre_c pre_w l d ins go ⦃ fun r =>
      MatchAt input r.1.val r.2.2.2.2.2.1.val r.2.2.2.2.2.2.1.val ∧
      HeadBound r.2.1 (r.1.val + r.2.2.2.2.2.1.val) ∧ r.1.val < lim.val ∧
      r.2.2.2.2.2.2.2.val ≤ r.1.val + 2 ∧ 3 ≤ r.2.2.2.2.2.1.val ∧
      r.2.2.1.val < H.val ∧ r.2.2.2.1.val ≤ r.1.val + 1 ∧
      r.2.2.2.2.1.val = word8 input r.2.2.2.1.val ∧ p.val ≤ r.1.val ⦄ := Q496M98!
@[local step]
theorem tail1_loop1_spec (input : Slice Std.U8) (out : Slice Std.U32) (n nt p : Std.Usize)
    (hn : n.val = input.length) (hdec : Dec input out nt.val p.val) :
    slot.q4_run1_loop1 input out n nt p ⦃ fun r => r.1.val ≤ input.length ∧
      r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := Q496M99! slot.q4_run1_loop1 slot.q4_run1_loop1.body
@[local step]
theorem tail1_loop2_spec (input : Slice Std.U8) (out : Slice Std.U32) (n nt p : Std.Usize)
    (hn : n.val = input.length) (hdec : Dec input out nt.val p.val) :
    slot.q4_run1_loop2 input out n nt p ⦃ fun r => r.1.val ≤ input.length ∧
      r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := Q496M99! slot.q4_run1_loop2 slot.q4_run1_loop2.body
def MainInv1 (input : Slice Std.U8) (L : Nat) (out : Slice Std.U32) (nt ls p : Nat)
    {N : Std.Usize} (head : Array Std.U32 N) (miss ps pc pw : Nat) : Prop :=
  Dec input out nt ls ∧ out.length = L ∧ ls ≤ p ∧ HeadBound head p ∧ miss ≤ p ∧ ps < N.val ∧
    pc ≤ p ∧ pw = word8 input pc
theorem MainInv1.mk' {input : Slice Std.U8} {L : Nat} {out : Slice Std.U32}
    {nt ls ls' p m B ps pc pw : Nat} {N : Std.Usize} {head : Array Std.U32 N}
    (hdec : Dec input out nt ls') (hls : ls' = ls) (hlen : out.length = L) (hlsp : ls ≤ p)
    (hB : HeadBound head B) (hBp : B ≤ p) (hm : m ≤ p) (hps : ps < N.val) (hpc : pc ≤ p)
    (hpw : pw = word8 input pc) : MainInv1 input L out nt ls p head m ps pc pw := Q496M100!
set_option maxHeartbeats 16000000 in
theorem main1_loop_spec {H : Std.Usize} (input : Slice Std.U8) (out : Slice Std.U32)
    (skip lazy skcap : Std.Usize) (km : Std.U32) (nt ls p : Std.Usize) (head : Array Std.U32 H)
    (lim miss fuel pre_slot pre_c : Std.Usize) (pre_w : Std.U64) (L : Nat)
    (hlim : lim.val + 8 = input.length) (hskip : skip.val < 32) (hH : 0 < H.val)
    (hinv : MainInv1 input L out nt.val ls.val p.val head miss.val pre_slot.val pre_c.val
      pre_w.val) :
    slot.q4_run1_loop0 input out skip lazy skcap km nt ls p head lim miss fuel pre_slot pre_c pre_w
      ⦃ fun r => Dec input r.1 r.2.1.val r.2.2.val ∧ r.1.length = L ⦄ := Q496M101! slot.q4_run1_loop0 slot.q4_run1_loop0.body
@[local step]
theorem main1_loop_spec' {H : Std.Usize} (input : Slice Std.U8) (out : Slice Std.U32)
    (skip lazy skcap : Std.Usize) (km : Std.U32) (nt ls p : Std.Usize) (head : Array Std.U32 H)
    (lim miss fuel pre_slot pre_c : Std.Usize) (pre_w : Std.U64)
    (hlim : lim.val + 8 = input.length) (hskip : skip.val < 32) (hH : 0 < H.val)
    (hdec : Dec input out nt.val ls.val) (hlsp : ls.val ≤ p.val) (hB : HeadBound head p.val)
    (hmiss : miss.val ≤ p.val) (hps : pre_slot.val < H.val) (hpc : pre_c.val ≤ p.val)
    (hpw : pre_w.val = word8 input pre_c.val) :
    slot.q4_run1_loop0 input out skip lazy skcap km nt ls p head lim miss fuel pre_slot pre_c pre_w
      ⦃ fun r => Dec input r.1 r.2.1.val r.2.2.val ∧ r.1.length = out.length ⦄ :=
  main1_loop_spec input out skip lazy skcap km nt ls p head lim miss fuel pre_slot pre_c pre_w
    out.length hlim hskip hH ⟨hdec, rfl, hlsp, hB, hmiss, hps, hpc, hpw⟩
theorem run1_spec (H : Std.Usize) (input : Slice Std.U8) (out : Slice Std.U32)
    (skip lazy skcap : Std.Usize) (km : Std.U32) (hlen : input.length ≤ out.length) (hH : 0 < H.val)
    (hskip : skip.val < 32) :
    slot.q4_run1 H input out skip lazy skcap km ⦃ fun r => r.1.val ≤ input.length ∧
      r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := Q496M102! slot.q4_run1
def LensBound (lens : Array Std.U16 260#usize) : Prop :=
  ∀ j : Nat, j < lens.val.length → (lens.val[j]!).val ≤ 258
theorem LensBound.init : LensBound (Std.Array.repeat 260#usize 0#u16) := by
  intro j hj
  rw [Std.Array.repeat_val] at hj ⊢
  rw [List.getElem!_eq_getElem?_getD, List.getElem?_replicate_of_lt (by simpa using hj)]
  simp
theorem LensBound.update {lens lens1 : Array Std.U16 260#usize} (h : LensBound lens)
    {a : Std.Usize} {v : Std.U16} (hv : v.val ≤ 258) (h1 : lens1 = lens.set a v) :
    LensBound lens1 := by
  subst h1
  intro j hj
  rw [Std.Array.set_val_eq] at hj ⊢
  rw [List.length_set] at hj
  by_cases hja : a.val = j
  · subst hja
    rw [List.getElem!_eq_getElem?_getD, List.getElem?_set_self hj]
    exact hv
  · rw [List.getElem!_eq_getElem?_getD, List.getElem?_set_ne hja, ← List.getElem!_eq_getElem?_getD]
    exact h j hj
theorem LensBound.update_cast {lens lens1 : Array Std.U16 260#usize} (h : LensBound lens)
    {a x : Std.Usize} (h1 : lens1 = lens.set a (UScalar.cast .U16 x)) (hx : x.val < 259) :
    LensBound lens1 := by
  apply LensBound.update h _ h1
  rw [UScalar.cast_val_eq, UScalarTy.U16_numBits_eq, Nat.mod_eq_of_lt (by omega)]
  omega
theorem LensBound.get {lens : Array Std.U16 260#usize} (h : LensBound lens) (a : Std.Usize)
    (x : Std.U16) (ha : a.val < lens.val.length) (hx : x = lens.val[a.val]) : x.val ≤ 258 := by
  have := h a.val ha
  rw [getElem!_pos lens.val a.val ha, ← hx] at this
  exact this
theorem LensBound.get2 {lens : Array Std.U16 260#usize} (h : LensBound lens) {i : Std.U16} {j : Nat}
    {hj : j < lens.val.length} (hi : i = lens.val[j]'hj) : i.val ≤ 258 := by
  have := h j hj
  rw [getElem!_pos lens.val j hj, ← hi] at this
  exact this
theorem cast_u16_le' {x : Std.Usize} (hx : x.val < 259) : (UScalar.cast .U16 x).val ≤ 258 := by
  rw [UScalar.cast_val_eq, UScalarTy.U16_numBits_eq, Nat.mod_eq_of_lt (by omega)]
  omega
@[local step]
theorem e_lens_loop_spec (lens : Array Std.U16 260#usize) (m : Std.U32) (cur : Std.U16)
    (x : Std.Usize) (hl : LensBound lens) (hc : cur.val ≤ 258) :
    slot.q4_e_lens_loop lens m cur x ⦃ fun r => LensBound r ⦄ := by
  rw [slot.q4_e_lens_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun r => 259 - r.2.2.val)
    (inv := fun r => LensBound r.1 ∧ r.2.1.val ≤ 258)
  · rintro ⟨lens, cur, x⟩ ⟨hl, hc⟩
    simp only at hl hc
    simp only [slot.q4_e_lens_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals first
      | exact hl
      | (refine ⟨LensBound.update_cast hl (by assumption) (by scalar_tac),
          cast_u16_le' (by scalar_tac), by scalar_tac⟩)
      | (refine ⟨LensBound.update hl hc (by assumption), hc, by scalar_tac⟩)
  · exact ⟨hl, hc⟩
@[local step]
theorem e_lens_spec (lens : Array Std.U16 260#usize) (m : Std.U32) (hl : LensBound lens) :
    slot.q4_e_lens lens m ⦃ fun r => LensBound r ⦄ :=
  e_lens_loop_spec lens m 0#u16 3#usize hl (by simp)
@[local step]
theorem e_piece_spec (lens : Array Std.U16 260#usize) (rem : Std.Usize) (hl : LensBound lens) :
    slot.q4_e_piece lens rem ⦃ fun x => x.val < 3 ∨ (x.val ≤ rem.val ∧ x.val ≤ 258) ⦄ := by
  rw [slot.q4_e_piece]
  step*
  repeat' (split <;> step*)
  all_goals first
    | (left; scalar_tac)
    | (right
       have := LensBound.get2 hl (by assumption)
       refine ⟨by scalar_tac, by scalar_tac⟩)
theorem fold_bt_loop_inv (input : Slice Std.U8) (out : Slice Std.U32) (d bt nt p l back : Std.Usize)
    (E P0 : Nat) (hP0 : P0 + 8 ≤ input.length)
    (hinv : BackInv input out d.val E P0 nt.val p.val l.val) :
    slot.q4_fold_bt_loop input out d bt nt p l back ⦃ fun r =>
      BackInv input out d.val E P0 r.1.val r.2.1.val r.2.2.val ⦄ := by
  rw [slot.q4_fold_bt_loop]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  apply Std.loop.spec_decr_nat
    (measure := fun r => bt.val - r.2.2.2.val)
    (inv := fun r => BackInv input out d.val E P0 r.1.val r.2.1.val r.2.2.1.val)
  · rintro ⟨nt, p, l, back⟩ hinv
    simp only at hinv
    have hinv' := hinv
    obtain ⟨⟨hps, hntp, hso, _⟩, ⟨h3, h258, hpl, hd1, hd32, hdp, _⟩, hE, hp0⟩ := hinv'
    simp only [slot.q4_fold_bt_loop.body]
    step*
    all_goals first
      | (refine ⟨hinv, by scalar_tac⟩)
      | (refine ⟨BackInv.lit hinv (by scalar_tac) (by scalar_tac) (by scalar_tac) (by scalar_tac)
          (by assumption) (by assumption) (by scalar_tac) (by scalar_tac) (by assumption)
          (by assumption) (by assumption) (by scalar_tac) (by assumption) (by scalar_tac)
          (by scalar_tac) (by scalar_tac), by scalar_tac⟩)
      | (refine ⟨BackInv.match hinv (by scalar_tac) (by scalar_tac) (by scalar_tac) (by scalar_tac)
          (by assumption) (by assumption) (by assumption) (by scalar_tac) (by scalar_tac)
          (by scalar_tac) (by scalar_tac) (by scalar_tac) (by scalar_tac) (by scalar_tac)
          (by scalar_tac), by scalar_tac⟩)
  · exact hinv
@[local step]
theorem fold_bt_spec (input : Slice Std.U8) (out : Slice Std.U32) (nt p l d bt : Std.Usize)
    (hp8 : p.val + 8 ≤ input.length) (hdec : Dec input out nt.val p.val)
    (hm : MatchAt input p.val l.val d.val) :
    slot.q4_fold_bt input out nt p l d bt ⦃ fun r =>
      Dec input out r.1.val r.2.1.val ∧ MatchAt input r.2.1.val r.2.2.val d.val ∧
      r.2.1.val + r.2.2.val = p.val + l.val ∧ r.2.1.val ≤ p.val ⦄ := by
  apply Std.WP.spec_mono (fold_bt_loop_inv input out d bt nt p l 0#usize (p.val + l.val) p.val hp8
    ⟨hdec, hm, rfl, le_refl _⟩)
  intro r h
  exact h
theorem Matches.suffix {s : Slice Std.U8} {a b l x : Nat} (h : Matches s a b l) (hx : x ≤ l) :
    Matches s (a + x) (b + x) (l - x) := by
  intro k hk
  have := h (x + k) (by omega)
  rw [show b + x + k = b + (x + k) by omega, show a + x + k = a + (x + k) by omega]
  exact this
theorem MatchAt.piece {s : Slice Std.U8} {q d x e : Nat} (hm : Matches s (q - d) q (e - q))
    (hd1 : 1 ≤ d) (hd32 : d ≤ 32768) (hdq : d ≤ q) (hen : e ≤ s.length) (hx3 : 3 ≤ x)
    (hx : x ≤ e - q) (hx258 : x ≤ 258) : MatchAt s q x d :=
  ⟨hx3, hx258, by omega, hd1, hd32, hdq, Matches.mono hm hx⟩
theorem Matches.after_piece {s : Slice Std.U8} {q d x e q1 : Nat} (hm : Matches s (q - d) q (e - q))
    (hq1 : q1 = q + x) (hdq : d ≤ q) (hx : x ≤ e - q) : Matches s (q1 - d) q1 (e - q1) := by
  have := Matches.suffix hm hx
  rw [show q - d + x = q1 - d by omega, show q + x = q1 by omega,
    show e - q - x = e - q1 by omega] at this
  exact this
@[local step]
theorem e_pieces_loop0_spec (input : Slice Std.U8) (out : Slice Std.U32) (d : Std.Usize)
    (lens : Array Std.U16 260#usize) (nt q «end» : Std.Usize) (go : Std.U32)
    (hl : LensBound lens) (hdec : Dec input out nt.val q.val) (hqe : q.val ≤ «end».val)
    (hen : «end».val ≤ input.length) (hd1 : 1 ≤ d.val) (hd32 : d.val ≤ 32768)
    (hdq : d.val ≤ q.val) (hm : Matches input (q.val - d.val) q.val («end».val - q.val)) :
    slot.q4_e_pieces_loop0 input out d lens nt q «end» go ⦃ fun r =>
      Dec input r.1 r.2.1.val r.2.2.val ∧ r.1.length = out.length ∧ r.2.2.val ≤ «end».val ⦄ := by
  rw [slot.q4_e_pieces_loop0]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  apply Std.loop.spec_decr_nat
    (measure := fun r => «end».val - r.2.2.1.val + r.2.2.2.val)
    (inv := fun r => Dec input r.1 r.2.1.val r.2.2.1.val ∧ r.1.length = out.length ∧
      r.2.2.1.val ≤ «end».val ∧ d.val ≤ r.2.2.1.val ∧
      Matches input (r.2.2.1.val - d.val) r.2.2.1.val («end».val - r.2.2.1.val))
  · rintro ⟨out', nt', q', go'⟩ ⟨hdec', hlen', hqe', hdq', hm'⟩
    simp only at hdec' hlen' hqe' hdq' hm'
    simp only [slot.q4_e_pieces_loop0.body]
    step*
    all_goals first
      | exact ⟨hdec', hlen', hqe'⟩
      | (refine ⟨hdec', hlen', hqe', hdq', hm', by scalar_tac⟩)
      | exact MatchAt.piece hm' hd1 hd32 hdq' hen (by scalar_tac) (by scalar_tac) (by scalar_tac)
      | (refine ⟨by assumption, by scalar_tac, by scalar_tac, by scalar_tac,
          Matches.after_piece hm' (by assumption) hdq' (by scalar_tac), by scalar_tac⟩)
  · exact ⟨hdec, rfl, hqe, hdq, hm⟩
@[local step]
theorem e_pieces_loop1_spec (input : Slice Std.U8) (out : Slice Std.U32) (nt q «end» : Std.Usize)
    (hdec : Dec input out nt.val q.val) (hqe : q.val ≤ «end».val) (hen : «end».val ≤ input.length) :
    slot.q4_e_pieces_loop1 input out nt q «end» ⦃ fun r =>
      Dec input r.1 r.2.1.val r.2.2.val ∧ r.1.length = out.length ∧ r.2.2.val = «end».val ⦄ := by
  rw [slot.q4_e_pieces_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun r => «end».val - r.2.2.val)
    (inv := fun r => Dec input r.1 r.2.1.val r.2.2.val ∧ r.1.length = out.length ∧
      r.2.2.val ≤ «end».val)
  · rintro ⟨out', nt', q'⟩ ⟨hdec', hlen', hqe'⟩
    simp only at hdec' hlen' hqe'
    simp only [slot.q4_e_pieces_loop1.body]
    step*
  · exact ⟨hdec, rfl, hqe⟩
@[local step]
theorem e_pieces_spec (input : Slice Std.U8) (out : Slice Std.U32) (nt p l d : Std.Usize)
    (lens : Array Std.U16 260#usize) (hl : LensBound lens) (hdec : Dec input out nt.val p.val)
    (hpl : p.val + l.val ≤ input.length) (hd1 : 1 ≤ d.val) (hd32 : d.val ≤ 32768)
    (hdp : d.val ≤ p.val) (hm : Matches input (p.val - d.val) p.val l.val) :
    slot.q4_e_pieces input out nt p l d lens ⦃ fun r =>
      Dec input r.2 r.1.1.val r.1.2.val ∧ r.1.2.val = p.val + l.val ∧ r.2.length = out.length ⦄ := by
  rw [slot.q4_e_pieces]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  step*
  repeat' (split <;> step*)
  all_goals first
    | exact Matches.mono hm (by scalar_tac)
    | scalar_tac
    | (refine ⟨by assumption, by scalar_tac, by scalar_tac⟩)
theorem lazy1t_loop_inv {H : Std.Usize} (input : Slice Std.U8) (lazy p : Std.Usize)
    (head : Array Std.U32 H) (lim pre_slot pre_c : Std.Usize) (pre_w : Std.U64)
    (l d ins : Std.Usize) (go : Std.U32) (P0 : Nat)
    (hlim : lim.val + 8 = input.length) (hH : 0 < H.val)
    (hinv : LazyInv1 input lim.val P0 p.val head pre_slot.val pre_c.val pre_w.val l.val d.val
      ins.val) :
    slot.q4_run1t_loop0_loop0 input lazy p head lim pre_slot pre_c pre_w l d ins go ⦃ fun r =>
      LazyInv1 input lim.val P0 r.1.val r.2.1 r.2.2.1.val r.2.2.2.1.val r.2.2.2.2.1.val
        r.2.2.2.2.2.1.val r.2.2.2.2.2.2.1.val r.2.2.2.2.2.2.2.val ⦄ := Q496M97! slot.q4_run1t_loop0_loop0 slot.q4_run1t_loop0_loop0.body
@[local step]
theorem lazy1t_loop_spec {H : Std.Usize} (input : Slice Std.U8) (lazy p : Std.Usize)
    (head : Array Std.U32 H) (lim pre_slot pre_c : Std.Usize) (pre_w : Std.U64)
    (l d ins : Std.Usize) (go : Std.U32)
    (hlim : lim.val + 8 = input.length) (hH : 0 < H.val)
    (hm : MatchAt input p.val l.val d.val)
    (hB : HeadBound head (p.val + 1)) (hplim : p.val < lim.val) (hins : ins.val ≤ p.val + 2)
    (hps : pre_slot.val < H.val) (hpc : pre_c.val ≤ p.val + 1)
    (hpw : pre_w.val = word8 input pre_c.val) :
    slot.q4_run1t_loop0_loop0 input lazy p head lim pre_slot pre_c pre_w l d ins go ⦃ fun r =>
      MatchAt input r.1.val r.2.2.2.2.2.1.val r.2.2.2.2.2.2.1.val ∧
      HeadBound r.2.1 (r.1.val + r.2.2.2.2.2.1.val) ∧ r.1.val < lim.val ∧
      r.2.2.2.2.2.2.2.val ≤ r.1.val + 2 ∧ 3 ≤ r.2.2.2.2.2.1.val ∧
      r.2.2.1.val < H.val ∧ r.2.2.2.1.val ≤ r.1.val + 1 ∧
      r.2.2.2.2.1.val = word8 input r.2.2.2.1.val ∧ p.val ≤ r.1.val ⦄ := by
  apply Std.WP.spec_mono (lazy1t_loop_inv input lazy p head lim pre_slot pre_c pre_w l d ins go
    p.val hlim hH ⟨hm, hB, hplim, hins, hps, hpc, hpw, le_refl _⟩)
  rintro ⟨p', head', ps', pc', pw', l', d', ins'⟩ ⟨hm', hB', hplim', hins', hps', hpc', hpw', hP'⟩
  exact ⟨hm', HeadBound.mono hB' (by have := hm'.1; omega), hplim', hins', hm'.1, hps', hpc',
    hpw', hP'⟩
@[local step]
theorem tail1t_loop1_spec (input : Slice Std.U8) (out : Slice Std.U32) (n nt p : Std.Usize)
    (hn : n.val = input.length) (hdec : Dec input out nt.val p.val) :
    slot.q4_run1t_loop1 input out n nt p ⦃ fun r => r.1.val ≤ input.length ∧
      r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := Q496M99! slot.q4_run1t_loop1 slot.q4_run1t_loop1.body
@[local step]
theorem tail1t_loop2_spec (input : Slice Std.U8) (out : Slice Std.U32) (n nt p : Std.Usize)
    (hn : n.val = input.length) (hdec : Dec input out nt.val p.val) :
    slot.q4_run1t_loop2 input out n nt p ⦃ fun r => r.1.val ≤ input.length ∧
      r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := Q496M99! slot.q4_run1t_loop2 slot.q4_run1t_loop2.body
set_option maxHeartbeats 16000000 in
theorem main1t_loop_spec {H : Std.Usize} (input : Slice Std.U8) (out : Slice Std.U32)
    (skip lazy skcap : Std.Usize) (lens : Array Std.U16 260#usize) (nt ls p : Std.Usize)
    (head : Array Std.U32 H) (lim miss fuel pre_slot pre_c : Std.Usize) (pre_w : Std.U64)
    (L : Nat) (hlim : lim.val + 8 = input.length) (hskip : skip.val < 32) (hH : 0 < H.val)
    (hl : LensBound lens)
    (hinv : MainInv1 input L out nt.val ls.val p.val head miss.val pre_slot.val pre_c.val
      pre_w.val) :
    slot.q4_run1t_loop0 input out skip lazy skcap lens nt ls p head lim miss fuel pre_slot pre_c pre_w
      ⦃ fun r => Dec input r.1 r.2.1.val r.2.2.val ∧ r.1.length = L ⦄ := by
  rw [slot.q4_run1t_loop0]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  apply Std.loop.spec_decr_nat
    (measure := fun r => r.2.2.2.2.2.2.1.val)
    (inv := fun r => MainInv1 input L r.1 r.2.1.val r.2.2.1.val r.2.2.2.1.val r.2.2.2.2.1
      r.2.2.2.2.2.1.val r.2.2.2.2.2.2.2.1.val r.2.2.2.2.2.2.2.2.1.val r.2.2.2.2.2.2.2.2.2.val)
  · rintro ⟨out, nt, ls, p, head, miss, fuel, pre_slot, pre_c, pre_w⟩ hinv
    simp only at hinv
    have hinv' := hinv
    obtain ⟨hdec, hL, hlsp, hB, hmiss, hps, hpc, hpw⟩ := hinv'
    simp only [slot.q4_run1t_loop0.body]
    step*
    all_goals first
      | exact FoundAt.real (by assumption) (by scalar_tac)
      | exact HeadBound.mono (by assumption) (by scalar_tac)
      | (refine ⟨MainInv1.mk' (by assumption) (by scalar_tac) (by scalar_tac) (by scalar_tac)
          (by assumption) (by scalar_tac) (by scalar_tac) (by scalar_tac) (by scalar_tac)
          (by assumption), by scalar_tac⟩)
  · exact hinv
@[local step]
theorem main1t_loop_spec' {H : Std.Usize} (input : Slice Std.U8) (out : Slice Std.U32)
    (skip lazy skcap : Std.Usize) (lens : Array Std.U16 260#usize) (nt ls p : Std.Usize)
    (head : Array Std.U32 H) (lim miss fuel pre_slot pre_c : Std.Usize) (pre_w : Std.U64)
    (hlim : lim.val + 8 = input.length) (hskip : skip.val < 32) (hH : 0 < H.val)
    (hl : LensBound lens)
    (hdec : Dec input out nt.val ls.val) (hlsp : ls.val ≤ p.val) (hB : HeadBound head p.val)
    (hmiss : miss.val ≤ p.val) (hps : pre_slot.val < H.val) (hpc : pre_c.val ≤ p.val)
    (hpw : pre_w.val = word8 input pre_c.val) :
    slot.q4_run1t_loop0 input out skip lazy skcap lens nt ls p head lim miss fuel pre_slot pre_c pre_w
      ⦃ fun r => Dec input r.1 r.2.1.val r.2.2.val ∧ r.1.length = out.length ⦄ :=
  main1t_loop_spec input out skip lazy skcap lens nt ls p head lim miss fuel pre_slot pre_c pre_w
    out.length hlim hskip hH hl ⟨hdec, rfl, hlsp, hB, hmiss, hps, hpc, hpw⟩
theorem run1t_spec (H : Std.Usize) (input : Slice Std.U8) (out : Slice Std.U32)
    (skip lazy skcap : Std.Usize) (lm : Std.U32) (hlen : input.length ≤ out.length)
    (hH : 0 < H.val) (hskip : skip.val < 32) :
    slot.q4_run1t H input out skip lazy skcap lm ⦃ fun r => r.1.val ≤ input.length ∧
      r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
  rw [slot.q4_run1t]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  have hB0 : HeadBound (Std.Array.repeat H 0#u32) 0 := HeadBound.init H
  have hL0 : LensBound (Std.Array.repeat 260#usize 0#u16) := LensBound.init
  have hdec0 : Dec input out (0#usize).val (0#usize).val := Dec.init input out hlen
  step*
theorem Matches.three {s : Slice Std.U8} {c p c1 p1 c2 p2 : Std.Usize}
    {x0 y0 x1 y1 x2 y2 : Std.U8}
    (hcl : c.val < s.val.length) (hpl : p.val < s.val.length)
    (hx0 : x0 = s.val[c.val]) (hy0 : y0 = s.val[p.val]) (h0 : x0 = y0)
    (hc1 : c1.val = c.val + 1) (hp1 : p1.val = p.val + 1)
    (hc1l : c1.val < s.val.length) (hp1l : p1.val < s.val.length)
    (hx1 : x1 = s.val[c1.val]) (hy1 : y1 = s.val[p1.val]) (h1 : x1 = y1)
    (hc2 : c2.val = c.val + 2) (hp2 : p2.val = p.val + 2)
    (hc2l : c2.val < s.val.length) (hp2l : p2.val < s.val.length)
    (hx2 : x2 = s.val[c2.val]) (hy2 : y2 = s.val[p2.val]) (h2 : x2 = y2) :
    Matches s c.val p.val (3#usize).val := Q496M103!
theorem FoundAt.of_dist {s : Slice Std.U8} {p c d l : Std.Usize}
    (hm : Matches s c.val p.val l.val) (hcp : c.val < p.val)
    (hd : d.val = p.val - c.val) (hd32 : d.val ≤ 32768) (hl : l.val ≤ 258)
    (hpl : p.val + l.val ≤ s.length) :
    FoundAt s p.val l.val d.val ∧ l.val ≤ 258 ∧ d.val ≤ 32768 := Q496M104!
@[local step]
theorem dn_slot_spec (s : Slice Std.U8) (p : Std.Usize) (hp : p.val + 2 < s.length) :
    slot.q4_dn_slot s p ⦃ fun r => r.val < slot.q4_DN_HN.val ⦄ := by
  rw [slot.q4_dn_slot]
  step*
@[local step]
theorem dn_swap_spec (tab) (a p : Std.Usize) (ha : a.val < slot.q4_DN_HN.val) :
    slot.q4_dn_swap tab a p ⦃ fun _ => True ⦄ := by
  rw [slot.q4_dn_swap]
  step*
@[local step]
theorem dn_find_loop_spec (s : Slice Std.U8) (c p cap l : Std.Usize) (hcp : c.val ≤ p.val)
    (hp : p.val + cap.val ≤ s.length) (hl : l.val ≤ cap.val) (hm : Matches s c.val p.val l.val) :
    slot.q4_dn_find_loop s c p cap l ⦃ fun r => r.val ≤ cap.val ∧ Matches s c.val p.val r.val ⦄ := by
  rw [slot.q4_dn_find_loop]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  apply Std.loop.spec_decr_nat
    (measure := fun r => cap.val - r.val)
    (inv := fun r => r.val ≤ cap.val ∧ Matches s c.val p.val r.val)
  · rintro l ⟨hl, hm⟩
    simp only [slot.q4_dn_find_loop.body]
    step*
    all_goals first
      | exact ⟨hl, hm⟩
      | (refine ⟨by scalar_tac, Matches.byte' hm (by assumption) (by assumption) (by scalar_tac)
          (by scalar_tac) (by assumption) (by assumption) (by assumption) (by assumption),
          by scalar_tac⟩)
  · exact ⟨hl, hm⟩
@[local step]
theorem dn_find_spec (s : Slice Std.U8) (c p : Std.Usize) (hp : p.val + 8 ≤ s.length) :
    slot.q4_dn_find s c p ⦃ fun r => FoundAt s p.val r.1.val r.2.val ∧ r.1.val ≤ 258 ∧
      r.2.val ≤ 32768 ⦄ := by
  rw [slot.q4_dn_find]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  step*
  repeat' (split <;> step*)
  all_goals first
    | exact FoundAt.none' s p.val
    | exact Matches.three (by scalar_tac) (by scalar_tac) (by assumption) (by assumption)
        (by assumption) (by assumption) (by assumption) (by scalar_tac) (by scalar_tac)
        (by assumption) (by assumption) (by assumption) (by assumption) (by assumption)
        (by scalar_tac) (by scalar_tac) (by assumption) (by assumption) (by assumption)
    | exact FoundAt.of_dist (by assumption) (by scalar_tac) (by scalar_tac) (by scalar_tac)
        (by scalar_tac) (by scalar_tac)
@[local step]
theorem dn_loop_spec (input : Slice Std.U8) (out : Slice Std.U32) (nt p : Std.Usize) (tab)
    (lim : Std.Usize) (hlim : lim.val + 8 = input.length) (hdec : Dec input out nt.val p.val) :
    slot.q4_run_dna_loop0 input out nt p tab lim ⦃ fun r =>
      Dec input r.1 r.2.1.val r.2.2.val ∧ r.1.length = out.length ⦄ := by
  rw [slot.q4_run_dna_loop0]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  apply Std.loop.spec_decr_nat
    (measure := fun r => input.length - r.2.2.1.val)
    (inv := fun r => Dec input r.1 r.2.1.val r.2.2.1.val ∧ r.1.length = out.length)
  · rintro ⟨out', nt', p', tab'⟩ ⟨hdec', hlen'⟩
    simp only at hdec' hlen'
    simp only [slot.q4_run_dna_loop0.body]
    step*
    all_goals first
      | exact FoundAt.real (by assumption) (by scalar_tac)
      | exact Dec.cast (by assumption) (by scalar_tac)
      | exact ⟨Dec.cast (by assumption) (by scalar_tac), by scalar_tac, by scalar_tac⟩
  · exact ⟨hdec, rfl⟩
@[local step]
theorem dn_tail1_spec (input : Slice Std.U8) (out : Slice Std.U32) (n nt p : Std.Usize)
    (hn : n.val = input.length) (hdec : Dec input out nt.val p.val) :
    slot.q4_run_dna_loop1 input out n nt p ⦃ fun r => r.1.val ≤ input.length ∧
      r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := Q496M99! slot.q4_run_dna_loop1 slot.q4_run_dna_loop1.body
@[local step]
theorem dn_tail2_spec (input : Slice Std.U8) (out : Slice Std.U32) (n nt p : Std.Usize)
    (hn : n.val = input.length) (hdec : Dec input out nt.val p.val) :
    slot.q4_run_dna_loop2 input out n nt p ⦃ fun r => r.1.val ≤ input.length ∧
      r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := Q496M99! slot.q4_run_dna_loop2 slot.q4_run_dna_loop2.body
theorem run_dna_spec (input : Slice Std.U8) (out : Slice Std.U32)
    (hlen : input.length ≤ out.length) :
    slot.q4_run_dna input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧
      LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
  rw [slot.q4_run_dna]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  have hdec0 : Dec input out (0#usize).val (0#usize).val := Dec.init input out hlen
  step*
@[local step]
theorem lit_all_loop_spec (input : Slice Std.U8) (out : Slice Std.U32) (n nt p : Std.Usize)
    (hn : n.val = input.length) (hdec : Dec input out nt.val p.val) :
    slot.q4_lit_all_loop input out n nt p ⦃ fun r => r.1.val ≤ input.length ∧
      r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := Q496M99! slot.q4_lit_all_loop slot.q4_lit_all_loop.body
@[local step]
theorem lit_all_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) :
 slot.q4_lit_all input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.q4_lit_all]
 have hd : Dec input out (0#usize).val (0#usize).val := Dec.init input out hlen
 step*
end Q4
@[local step]
theorem p125_row52_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.p125_row52 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.p125_row52]
 exact Q4.run1t_spec _ input out _ _ _ _ hlen (by simp) (by simp)

@[local step]
theorem bulk_parse_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.bulk_parse input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.bulk_parse]
 step*
 repeat' (split <;> step*)
theorem parse_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.parse input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.parse]
 exact bulk_parse_spec input out hlen
end Submission

