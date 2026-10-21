import Lz77
import Slot
open Aeneas Aeneas.Std Aeneas.Std.WP
#register_spec_info {
    spec_name := ``Std.WP.spec
    arity := 3
    program_index := 1
    post_index := 2
    mk_spec_mono := ``Std.WP.spec_mono'
    mk_spec_mono_skip_args := 2
    mk_spec_bind := ``Std.WP.spec_bind'
    mk_spec_bind_skip_args := 4
    uncurry_elim_tactics := #[
      ``Std.WP.qimp_spec_unit, ``Std.WP.qimp_unit,
      ``Std.WP.qimp_spec_exists, ``Std.WP.qimp_exists,
      ``forall_unit, ``true_imp_iff
    ]
    qimp_elim_tactics := #[
      ``Std.WP.qimp_spec_iff, ``Std.WP.qimp_iff,
      ``Std.WP.imp_and_iff, ``Std.uncurry_apply_pair,
      ``Std.WP.uncurry'_eq, ``Std.WP.uncurry'_pair,
      ``Std.WP.imp_exists_iff,
      ``forall_unit, ``true_imp_iff]
    to_mvcgen := .none
    liftings := #[]
  }

#register_spec_info {
    spec_name := ``Std.WP.dspec
    arity := 3
    program_index := 1
    post_index := 2
    mk_spec_mono := ``Std.WP.dspec_mono'
    mk_spec_mono_skip_args := 2
    mk_spec_bind := ``Std.WP.dspec_bind'
    mk_spec_bind_skip_args := 4
    uncurry_elim_tactics := #[
      ``Std.WP.qimp_dspec_unit, ``Std.WP.qimp_unit,
      ``Std.WP.qimp_dspec_exists, ``Std.WP.qimp_exists,
      ``forall_unit, ``true_imp_iff
    ]
    qimp_elim_tactics := #[
      ``Std.WP.qimp_dspec_iff, ``Std.WP.qimp_iff,
      ``Std.WP.imp_and_iff, ``Std.uncurry_apply_pair,
      ``Std.WP.uncurry'_eq, ``Std.WP.uncurry'_pair,
      ``Std.WP.imp_exists_iff,
      ``forall_unit, ``true_imp_iff]
    to_mvcgen := .none
    liftings := #[
      { from_statement := ``Std.WP.spec
        conversion_thm := ``Std.WP.spec_dspec
        conversion_thm_inferred_args := 3 }
    ]
  }

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
 (if c then A else B) ⦃ fun _ => True ⦄ := (by
 by_cases h : c
 · rw [if_pos h]; exact hA h
 · rw [if_neg h]; exact hB h)
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
    (ha : c → a ⦃ Q ⦄) (hb : ¬c → b ⦃ Q ⦄) : (if c then a else b) ⦃ Q ⦄ := (by
  by_cases h : c
  · rw [if_pos h]; exact ha h
  · rw [if_neg h]; exact hb h)
theorem ite_prod_spec {α β : Type} (c : Prop) [Decidable c] (A B : Result (α × β))
    (hA : c → A ⦃ fun _ => True ⦄) (hB : ¬c → B ⦃ fun _ => True ⦄) :
    (if c then A else B) ⦃ fun _ => True ⦄ := (by
  by_cases h : c
  · rw [if_pos h]; exact hA h
  · rw [if_neg h]; exact hB h)
theorem ite_true_spec {α : Type} (c : Prop) [Decidable c] (A B : Result α)
    (hA : c → A ⦃ fun _ => True ⦄) (hB : ¬c → B ⦃ fun _ => True ⦄) :
    (if c then A else B) ⦃ fun _ => True ⦄ := (by
  by_cases h : c
  · rw [if_pos h]; exact hA h
  · rw [if_neg h]; exact hB h)
set_option hygiene false in
local notation "C1259!" q0__:max => (by
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
section
attribute [local step] Submission.r70_ite_true_spec
theorem ld8_spec (input : Slice Std.U8) (p : Std.Usize) :
    slot.o_a_ld8 input p ⦃ fun _ => True ⦄ := C1259! slot.o_a_ld8
end
attribute [local step] ld8_spec
section
attribute [local step] Submission.r70_ite_true_spec
theorem first_diff_spec (x : Std.U64) :
    slot.o_a_first_diff x ⦃ fun _ => True ⦄ := C1259! slot.o_a_first_diff
end
attribute [local step] first_diff_spec
set_option hygiene false in
local notation "C12510!" q0__:max q1__:max => (by
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
section
attribute [local step] Submission.r70_ite_true_spec
theorem v7z (input : Slice Std.U8) (a : Std.Usize) (b : Std.Usize) (cap : Std.Usize) (l : Std.Usize) (go : Std.Usize) (it : Std.Usize)  :
    slot.o_a_fast_len_loop input a b cap l go it ⦃ fun _ => True ⦄ := C12510! slot.o_a_fast_len_loop slot.o_a_fast_len_loop.body
end
attribute [local step] v7z
set_option hygiene false in
local notation "C12511!" q0__:max => (by
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
section
attribute [local step] Submission.r70_ite_true_spec
theorem fast_len_spec (input : Slice Std.U8) (a : Std.Usize) (b : Std.Usize) (cap : Std.Usize) :
    slot.o_a_fast_len input a b cap ⦃ fun _ => True ⦄ := C12511! slot.o_a_fast_len
end
attribute [local step] fast_len_spec
section
attribute [local step] Submission.r70_ite_true_spec
theorem v5z (input : Slice Std.U8) (a : Std.Usize) (b : Std.Usize) (cap : Std.Usize) (l : Std.Usize) (go : Std.Usize) (it : Std.Usize)  :
    slot.o_a_fast_len2_loop input a b cap l go it ⦃ fun _ => True ⦄ := C12510! slot.o_a_fast_len2_loop slot.o_a_fast_len2_loop.body
end
attribute [local step] v5z
section
attribute [local step] Submission.r70_ite_true_spec
theorem fast_len2_spec (input : Slice Std.U8) (a : Std.Usize) (b : Std.Usize) (cap : Std.Usize) :
    slot.o_a_fast_len2 input a b cap ⦃ fun _ => True ⦄ := C12511! slot.o_a_fast_len2
end
attribute [local step] fast_len2_spec
section
attribute [local step] Submission.r70_ite_true_spec
theorem v6z (input : Slice Std.U8) (a : Std.Usize) (b : Std.Usize) (cap : Std.Usize) (l : Std.Usize) (go : Std.Usize) (it : Std.Usize)  :
    slot.o_a_fast_len3_loop input a b cap l go it ⦃ fun _ => True ⦄ := C12510! slot.o_a_fast_len3_loop slot.o_a_fast_len3_loop.body
end
attribute [local step] v6z
section
attribute [local step] Submission.r70_ite_true_spec
theorem fast_len3_spec (input : Slice Std.U8) (a : Std.Usize) (b : Std.Usize) (cap : Std.Usize) :
    slot.o_a_fast_len3 input a b cap ⦃ fun _ => True ⦄ := C12511! slot.o_a_fast_len3
end
attribute [local step] fast_len3_spec
@[local step]
theorem hashp_spec (input : Slice Std.U8) (p : Std.Usize) :
    slot.o_a_hashp input p ⦃ fun r => r.val < 65536 ⦄ := C1259! slot.o_a_hashp
@[local step]
theorem hashl_spec (input : Slice Std.U8) (p : Std.Usize) :
    slot.o_a_hashl input p ⦃ fun r => r.val < 65536 ⦄ := C1259! slot.o_a_hashl
set_option hygiene false in
local notation "C12512!" q0__:max => (by
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
    slot.o_a_eval input p cs cl ⦃ fun _ => True ⦄ := C12512! slot.o_a_eval
end
attribute [local step] eval_spec
section
attribute [local step] Submission.r70_ite_true_spec
theorem eval2_spec (input : Slice Std.U8) (p : Std.Usize) (cs : Std.Usize) (cl : Std.Usize) (floor : Std.Usize) :
    slot.o_a_eval2 input p cs cl floor ⦃ fun _ => True ⦄ := C12512! slot.o_a_eval2
end
attribute [local step] eval2_spec
section
attribute [local step] Submission.r70_ite_true_spec
theorem eval3_spec (input : Slice Std.U8) (p : Std.Usize) (cs : Std.Usize) (cl : Std.Usize) (floor : Std.Usize) :
    slot.o_a_eval3 input p cs cl floor ⦃ fun _ => True ⦄ := C12512! slot.o_a_eval3
end
attribute [local step] eval3_spec
section
attribute [local step] Submission.r70_ite_true_spec
theorem v14z (input : Slice Std.U8) (head : Array Std.U32 131072#usize) («to» : Std.Usize) (n : Std.Usize) (p : Std.Usize) (hn : n.val = input.length) :
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
attribute [local step] v14z
section
attribute [local step] Submission.r70_ite_true_spec
theorem v15z (input : Slice Std.U8) (head : Array Std.U32 131072#usize) («from» : Std.Usize) («to» : Std.Usize) :
    slot.o_a_insert_range input head «from» «to» ⦃ fun _ => True ⦄ := C12511! slot.o_a_insert_range
end
attribute [local step] v15z
section
attribute [local step] Submission.r70_ite_true_spec
theorem v12z (TS_ : Std.Usize) (input : Slice Std.U8) (head : Array Std.U32 131072#usize) («to» : Std.Usize) (n : Std.Usize) (p : Std.Usize) (c : Std.Usize) (hn : n.val = input.length) :
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
attribute [local step] v12z
section
attribute [local step] Submission.r70_ite_true_spec
theorem v13z (TS_ : Std.Usize) (input : Slice Std.U8) (head : Array Std.U32 131072#usize) («from» : Std.Usize) («to» : Std.Usize) :
    slot.o_a_insert_range2 TS_ input head «from» «to» ⦃ fun _ => True ⦄ := C12511! slot.o_a_insert_range2
end
attribute [local step] v13z
section
attribute [local step] Submission.r70_ite_true_spec
theorem v11z (IH_ : Std.Usize) (IT_ : Std.Usize) (TS_ : Std.Usize) (input : Slice Std.U8) (head : Array Std.U32 131072#usize) («from» : Std.Usize) («to» : Std.Usize) :
    slot.o_a_insert_match IH_ IT_ TS_ input head «from» «to» ⦃ fun _ => True ⦄ := C1259! slot.o_a_insert_match
end
attribute [local step] v11z
section
attribute [local step] Submission.r70_ite_true_spec
theorem run_len_spec (ACC_ : Std.U64) (k : Std.Usize) :
    slot.o_a_run_len ACC_ k ⦃ fun _ => True ⦄ := C1259! slot.o_a_run_len
end
attribute [local step] run_len_spec
section
attribute [local step] Submission.r70_ite_true_spec
theorem q8ok_spec (q : Std.Usize) (d : Std.Usize) :
    slot.o_a_q8ok q d ⦃ fun _ => True ⦄ := C1259! slot.o_a_q8ok
end
attribute [local step] q8ok_spec
section
attribute [local step] Submission.r70_ite_true_spec
theorem bext_loop_spec (input : Slice Std.U8) (p : Std.Usize) (d : Std.Usize) (lim : Std.Usize) (e : Std.Usize) (go : Std.Usize) (it : Std.Usize)  :
    slot.o_a_bext_loop input p d lim e go it ⦃ fun _ => True ⦄ := C12510! slot.o_a_bext_loop slot.o_a_bext_loop.body
end
attribute [local step] bext_loop_spec
section
attribute [local step] Submission.r70_ite_true_spec
theorem bext_spec (input : Slice Std.U8) (lo : Std.Usize) (p : Std.Usize) (d : Std.Usize) (l : Std.Usize) :
    slot.o_a_bext input lo p d l ⦃ fun _ => True ⦄ := C12511! slot.o_a_bext
end
attribute [local step] bext_spec
section
attribute [local step] Submission.r70_ite_true_spec
theorem back1_spec (input : Slice Std.U8) (q : Std.Usize) (d : Std.Usize) :
    slot.o_a_back1 input q d ⦃ fun _ => True ⦄ := C12511! slot.o_a_back1
end
attribute [local step] back1_spec
section
attribute [local step] Submission.r70_ite_true_spec
theorem tab_step_spec (head : Array Std.U32 131072#usize) (hs : Std.Usize) (hl : Std.Usize) (hs1 : Std.Usize) (hl1 : Std.Usize) (p : Std.Usize) :
    slot.o_a_tab_step head hs hl hs1 hl1 p ⦃ fun _ => True ⦄ := C1259! slot.o_a_tab_step
end
attribute [local step] tab_step_spec
section
attribute [local step] Submission.r70_ite_true_spec
theorem tab_step2_spec (head : Array Std.U32 131072#usize) (hs : Std.Usize) (hl : Std.Usize) (q : Std.Usize) :
    slot.o_a_tab_step2 head hs hl q ⦃ fun _ => True ⦄ := C1259! slot.o_a_tab_step2
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
    slot.o_a_scan ACC_ input head pos ⦃ fun _ => True ⦄ := C1259! slot.o_a_scan
end
attribute [local step] scan_spec
section
attribute [local step] Submission.r70_ite_true_spec
theorem lazy_step_spec (LZT_ : Std.Usize) (input : Slice Std.U8) (head : Array Std.U32 131072#usize) (m : Std.U64) :
    slot.o_a_lazy_step LZT_ input head m ⦃ fun _ => True ⦄ := C1259! slot.o_a_lazy_step
end
attribute [local step] lazy_step_spec
section
attribute [local step] Submission.r70_ite_true_spec
theorem v17z (LZT_ : Std.Usize) (input : Slice Std.U8) (head : Array Std.U32 131072#usize) (m : Std.U64) (go : Std.Usize) (it : Std.Usize)  :
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
attribute [local step] v17z
section
attribute [local step] Submission.r70_ite_true_spec
theorem find_spec (ACC_ : Std.U64) (LZT_ : Std.Usize) (input : Slice Std.U8) (head : Array Std.U32 131072#usize) (pos : Std.Usize) :
    slot.o_a_find ACC_ LZT_ input head pos ⦃ fun _ => True ⦄ := C12512! slot.o_a_find
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
    ∀ k, k < 8 → input.val[q + k]! = input.val[p + k]! := (by
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
    rfl | rfl | rfl | rfl | rfl | rfl | rfl | rfl <;> (try simp only [Nat.add_zero]) <;> omega)
theorem w4_bytes (input : Slice Std.U8) (p q : Nat) (h : w4 input p = w4 input q) :
    ∀ k, k < 4 → input.val[q + k]! = input.val[p + k]! := (by
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
    rfl | rfl | rfl | rfl <;> (try simp only [Nat.add_zero]) <;> omega)
theorem Matches.add8 {input : Slice Std.U8} {a b l : Nat} (h : Matches input a b l)
    (hw : w8 input (a + l) = w8 input (b + l)) : Matches input a b (l + 8) := (by
  have hb := w8_bytes input (a + l) (b + l) hw
  intro k hk
  by_cases hkl : k < l
  · exact h k hkl
  · have := hb (k - l) (by omega)
    rw [show b + k = b + l + (k - l) by omega, show a + k = a + l + (k - l) by omega]
    exact this)
theorem Matches.tail8 {input : Slice Std.U8} {a b l c : Nat} (h : Matches input a b l)
    (hc : 8 ≤ c) (hl : c ≤ l + 8)
    (hw : w8 input (a + (c - 8)) = w8 input (b + (c - 8))) : Matches input a b c := (by
  have hb := w8_bytes input (a + (c - 8)) (b + (c - 8)) hw
  intro k hk
  by_cases hkl : k < l
  · exact h k hkl
  · have := hb (k - (c - 8)) (by omega)
    rw [show b + k = b + (c - 8) + (k - (c - 8)) by omega,
      show a + k = a + (c - 8) + (k - (c - 8)) by omega]
    exact this)
theorem Matches.two4 {input : Slice Std.U8} {a b c : Nat}
    (hc : 4 ≤ c) (hc8 : c < 8) (hw0 : w4 input a = w4 input b)
    (hw1 : w4 input (a + (c - 4)) = w4 input (b + (c - 4))) : Matches input a b c := (by
  have h0 := w4_bytes input a b hw0
  have h1 := w4_bytes input (a + (c - 4)) (b + (c - 4)) hw1
  intro k hk
  by_cases hk4 : k < 4
  · exact h0 k hk4
  · have := h1 (k - (c - 4)) (by omega)
    rw [show b + k = b + (c - 4) + (k - (c - 4)) by omega,
      show a + k = a + (c - 4) + (k - (c - 4)) by omega]
    exact this)
@[local step]
theorem tw8_spec (input : Slice Std.U8) (p : Std.Usize) (h : p.val + 8 ≤ input.length) :
    slot.o_a_tw8 input p ⦃ fun r => r.val = w8 input p.val ⦄ := by
  rw [slot.o_a_tw8]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  step*
  unfold w8
  rw [getElem!_pos input.val p.val (by first | assumption | omega | scalar_tac), getElem!_pos input.val (p.val + 1) (by first | assumption | omega | scalar_tac),
    getElem!_pos input.val (p.val + 2) (by first | assumption | omega | scalar_tac), getElem!_pos input.val (p.val + 3) (by first | assumption | omega | scalar_tac),
    getElem!_pos input.val (p.val + 4) (by first | assumption | omega | scalar_tac), getElem!_pos input.val (p.val + 5) (by first | assumption | omega | scalar_tac),
    getElem!_pos input.val (p.val + 6) (by first | assumption | omega | scalar_tac), getElem!_pos input.val (p.val + 7) (by first | assumption | omega | scalar_tac)]
  scalar_tac
@[local step]
theorem tw4_spec (input : Slice Std.U8) (p : Std.Usize) (h : p.val + 4 ≤ input.length) :
    slot.o_a_tw4 input p ⦃ fun r => r.val = w4 input p.val ⦄ := by
  rw [slot.o_a_tw4]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  step*
  unfold w4
  rw [getElem!_pos input.val p.val (by first | assumption | omega | scalar_tac), getElem!_pos input.val (p.val + 1) (by first | assumption | omega | scalar_tac),
    getElem!_pos input.val (p.val + 2) (by first | assumption | omega | scalar_tac), getElem!_pos input.val (p.val + 3) (by first | assumption | omega | scalar_tac)]
  scalar_tac
theorem v34z (input : Slice Std.U8) (a b cap l0 : Std.Usize)
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
  apply Std.WP.spec_bind (v34z input a b cap 0#usize ha hb (by first | assumption | omega | scalar_tac)
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
           rw [← i_post, ← i2_post, getElem!_pos _ _ (by first | assumption | omega | scalar_tac),
             getElem!_pos _ _ (by first | assumption | omega | scalar_tac), ← i1_post, ← i3_post]
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
theorem v3z (input : Slice Std.U8) (out0 : Slice Std.U32)
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
  apply Std.WP.spec_bind (v3z input out _ cnt1 pos0 0#usize ntok0
    (by simp) hout (by first | assumption | omega | scalar_tac) hntok (by simp) hdec)
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
    apply Std.WP.spec_mono (emit_lits_spec input out pos lits ntok hout (by first | assumption | omega | scalar_tac) hntok hdec)
    rintro ⟨⟨t, k⟩, o⟩ ⟨h1, h2, h3, h4, h5⟩
    exact ⟨by scalar_tac, h2, h3, h4, h5⟩
section
attribute [local step] Submission.r70_ite_true_spec
end
section
attribute [local step] Submission.r70_ite_true_spec
end
section
attribute [local step] Submission.r70_ite_true_spec
end
section
attribute [local step] Submission.r70_ite_true_spec
end
section
attribute [local step] Submission.r70_ite_true_spec
end
section
attribute [local step] Submission.r70_ite_true_spec
end
section
attribute [local step] Submission.r70_ite_true_spec
end
section
attribute [local step] Submission.r70_ite_true_spec
end
section
attribute [local step] Submission.r70_ite_true_spec
end
section
attribute [local step] Submission.r70_ite_true_spec
end
section
@[local step]
theorem v30z (IH_ : Std.Usize) (IT_ : Std.Usize) (TS_ : Std.Usize) (ACC_ : Std.U64) (LZT_ : Std.Usize) (input : Slice Std.U8) (out0 : Slice Std.U32) (head0 : Array Std.U32 131072#usize) (n : Std.Usize) (pos0 : Std.Usize) (ntok0 : Std.Usize)
    (hn : n.val = input.length) (hout : input.length ≤ out0.length)
    (hp : pos0.val ≤ n.val) (hntok : ntok0.val ≤ pos0.val)
    (hdec : LZ77.decode (toks out0 ntok0.val) = some ((bytes input).take pos0.val)) :
    slot.o_a_run_greedy_loop IH_ IT_ TS_ ACC_ LZT_ input out0 head0 n pos0 ntok0 ⦃ fun r =>
      r.1.val ≤ input.length ∧ r.2.1.length = out0.length ∧
      LZ77.Valid (bytes input) (toks r.2.1 r.1.val) ⦄ := (by
  rw [slot.o_a_run_greedy_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => n.val - s.2.2.1.val)
    (inv := fun s =>
      s.2.2.1.val ≤ n.val ∧ s.2.2.2.val ≤ s.2.2.1.val ∧ s.1.length = out0.length ∧
      LZ77.decode (toks s.1 s.2.2.2.val) = some ((bytes input).take s.2.2.1.val))
  · rintro ⟨out, head, pos, ntok⟩ ⟨hpn, hnt, hlen, hde⟩
    simp only at hpn hnt hlen hde
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.o_a_run_greedy_loop.body, lift, Array.to_slice_mut, alloc.vec.Vec.deref_mut, bind_tc_ok]
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
end
attribute [local step] v30z
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
      LZ77.Valid (bytes input) (toks r.2.1 r.1.val) ⦄ := (by
  rw [slot.o_a_run_greedy]
  have h0 := decode_nil input out
  try simp only [lift, Array.to_slice_mut, alloc.vec.Vec.deref_mut, bind_tc_ok]
  step*
  all_goals (repeat (first
    | (refine ⟨by scalar_tac, by scalar_tac, valid_of_decode (by assumption) (by first | assumption | omega | scalar_tac)⟩)
    | (intro hc; (try step*))
    | (casesm* _ × _; (try simp only []); (try step*))
    | (split <;> (try step*))
    | (step <;> (try step*))))
  all_goals (try scalar_tac))
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
      LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := (by
  rw [slot.o_a_main_part]
  have h0 := decode_nil input out
  try simp only [lift, Array.to_slice_mut, alloc.vec.Vec.deref_mut, bind_tc_ok]
  step*
  all_goals (repeat (first
    | (refine ⟨by scalar_tac, by scalar_tac, valid_of_decode (by assumption) (by first | assumption | omega | scalar_tac)⟩)
    | (intro hc; (try step*))
    | (casesm* _ × _; (try simp only []); (try step*))
    | (split <;> (try step*))
    | (step <;> (try step*))))
  all_goals (try scalar_tac))
end
attribute [local step] main_part_spec
end EA
attribute [local step] EA.main_part_spec
set_option maxHeartbeats 1000000
end EO
set_option maxHeartbeats 1000000
namespace N70
open EO.EA
attribute [local step] EO.EA.ld8_spec EO.EA.first_diff_spec EO.EA.fast_len_spec EO.EA.emit_lits_spec EO.EA.emit_step_spec
theorem bits32 : 32 ≤ System.Platform.numBits := (by
  rcases System.Platform.numBits_eq with h | h <;> omega)
section
attribute [local step] EO.EA.ite_true_spec EO.EA.ite_prod_spec
set_option maxHeartbeats 4000000
@[local step]
theorem pure_ite_spec {α : Type} (c : Prop) [Decidable c] (a b : α) :
 (if c then ok a else ok b) ⦃ fun r => r = if c then a else b ⦄ := (by
 split <;> simp_all [Std.WP.spec_ok])
set_option hygiene false in
local notation "C12522!" q0__:max => (by
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
 slot.n_hash H K input p ⦃ fun _ => True ⦄ := C12522! slot.n_hash
@[local step]
theorem n_choose_spec (SLOT a b : Std.Usize) :
 slot.n_choose SLOT a b ⦃ fun _ => True ⦄ := C12522! slot.n_choose
@[local step]
theorem n_eval_spec (input : Slice Std.U8) (p c : Std.Usize) :
 slot.n_eval input p c ⦃ fun _ => True ⦄ := C12522! slot.n_eval
@[local step]
theorem v24z {H : Std.Usize} (REP SLOT : Std.Usize) (input : Slice Std.U8) (head : Array Std.U32 H) (p best j : Std.Usize) (hH : 8 < H.val) :
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
 slot.n_probe K REP LINE SLOT input head p ⦃ fun _ => True ⦄ := C12522! slot.n_probe
set_option hygiene false in
local notation "C12523!" q0__:max q1__:max => (by
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
theorem v20z {H : Std.Usize} (K LINE INS STRIDE1 : Std.Usize) (input : Slice Std.U8) (head : Array Std.U32 H) («from» «to» j : Std.Usize) (hH : 8 < H.val) :
 slot.n_insert_loop0 K LINE INS STRIDE1 input head «from» «to» j ⦃ fun _ => True ⦄ := C12523! slot.n_insert_loop0 slot.n_insert_loop0.body
@[local step]
theorem v21z {H : Std.Usize} (K LINE INS STRIDE1 : Std.Usize) (input : Slice Std.U8) (head : Array Std.U32 H) («from» «to» j : Std.Usize) (hH : 8 < H.val) :
 slot.n_insert_loop1 K LINE INS STRIDE1 input head «from» «to» j ⦃ fun _ => True ⦄ := C12523! slot.n_insert_loop1 slot.n_insert_loop1.body
@[local step]
theorem v22z {H : Std.Usize} (K LINE INS STRIDE1 : Std.Usize) (input : Slice Std.U8) (head : Array Std.U32 H) («from» «to» j : Std.Usize) (hH : 8 < H.val) :
 slot.n_insert_loop2 K LINE INS STRIDE1 input head «from» «to» j ⦃ fun _ => True ⦄ := C12523! slot.n_insert_loop2 slot.n_insert_loop2.body
@[local step]
theorem v23z {H : Std.Usize} (K LINE INS STRIDE1 : Std.Usize) (input : Slice Std.U8) (head : Array Std.U32 H) («from» «to» j : Std.Usize) (hH : 8 < H.val) :
 slot.n_insert_loop3 K LINE INS STRIDE1 input head «from» «to» j ⦃ fun _ => True ⦄ := C12523! slot.n_insert_loop3 slot.n_insert_loop3.body
@[local step]
theorem n_insert_spec {H : Std.Usize} (K REP LINE INS STRIDE1 : Std.Usize) (input : Slice Std.U8) (head : Array Std.U32 H) («from» «to» d : Std.Usize) :
 slot.n_insert K REP LINE INS STRIDE1 input head «from» «to» d ⦃ fun _ => True ⦄ := C12522! slot.n_insert
@[local step]
theorem v19z {H : Std.Usize} (K REP LINE SLOT ACC LAZY : Std.Usize) (input : Slice Std.U8) (head : Array Std.U32 H) (n p it go : Std.Usize) (found : Std.U64)  :
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
 slot.n_find K REP LINE SLOT ACC LAZY input head pos ⦃ fun _ => True ⦄ := C12522! slot.n_find
end
attribute [local step] n_find_spec n_insert_spec
@[local step]
theorem n_run_loop_spec {H : Std.Usize} (K REP LINE SLOT ACC LAZY INS STRIDE1 : Std.Usize) (input : Slice Std.U8) (out0 : Slice Std.U32) (head0 : Array Std.U32 H) (n : Std.Usize) (pos0 : Std.Usize) (ntok0 : Std.Usize)
    (hn : n.val = input.length) (hout : input.length ≤ out0.length)
    (hp : pos0.val ≤ n.val) (hntok : ntok0.val ≤ pos0.val)
    (hdec : LZ77.decode (toks out0 ntok0.val) = some ((bytes input).take pos0.val)) :
    slot.n_run_loop K REP LINE SLOT ACC LAZY INS STRIDE1 input out0 head0 n pos0 ntok0 ⦃ fun r =>
      r.1.val ≤ input.length ∧ r.2.length = out0.length ∧
      LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := (by
  rw [slot.n_run_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => n.val - s.2.2.1.val)
    (inv := fun s =>
      s.2.2.1.val ≤ n.val ∧ s.2.2.2.val ≤ s.2.2.1.val ∧ s.1.length = out0.length ∧
      LZ77.decode (toks s.1 s.2.2.2.val) = some ((bytes input).take s.2.2.1.val))
  · rintro ⟨out, head, pos, ntok⟩ ⟨hpn, hnt, hlen, hde⟩
    simp only at hpn hnt hlen hde
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.n_run_loop.body, lift, Array.to_slice_mut, alloc.vec.Vec.deref_mut, bind_tc_ok]
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
set_option hygiene false in
local notation "C12529!" => (by
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
local notation "C12546!" => (by
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
local notation "C12553!" => (by
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
local notation "C12560!" => (by
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
local notation "C12563!" => (by
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
local notation "C12577!" => (by
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
local notation "C12582!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun r => n.val - r.2.2.val)
    (inv := fun r => Dec input r.1 r.2.1.val r.2.2.val ∧ r.1.length = out.length)
  · rintro ⟨out', nt', p'⟩ ⟨hdec', hlen'⟩
    simp only at hdec' hlen'
    simp only [q1__]
    step*
    have hd := Dec.done hdec' (by first | assumption | omega | scalar_tac)
    exact ⟨hd.1, hlen', hd.2⟩
  · exact ⟨hdec, rfl⟩)
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
    (input.val[p + k]!).val = word8 input p / 256 ^ (7 - k) % 256 := (by
  have := u8_lt (input.val[p]!); have := u8_lt (input.val[p+1]!)
  have := u8_lt (input.val[p+2]!); have := u8_lt (input.val[p+3]!)
  have := u8_lt (input.val[p+4]!); have := u8_lt (input.val[p+5]!)
  have := u8_lt (input.val[p+6]!); have := u8_lt (input.val[p+7]!)
  simp only [word8]
  rcases (show k = 0 ∨ k = 1 ∨ k = 2 ∨ k = 3 ∨ k = 4 ∨ k = 5 ∨ k = 6 ∨ k = 7 by omega) with
    rfl | rfl | rfl | rfl | rfl | rfl | rfl | rfl <;> simp only [Nat.add_zero, Nat.pow_zero, Nat.pow_succ, Nat.one_mul,
    Nat.sub_self, Nat.reduceSub] <;> omega)
theorem word8_prefix (input : Slice Std.U8) (a b d : Nat) (hd : d ≤ 8)
    (h : word8 input a / 2 ^ (64 - 8 * d) = word8 input b / 2 ^ (64 - 8 * d)) :
    ∀ k, k < d → input.val[b + k]! = input.val[a + k]! := (by
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
theorem Matches.add_prefix {input : Slice Std.U8} {a b l d : Nat} (h : Matches input a b l)
    (hd : d ≤ 8)
    (hw : word8 input (a + l) / 2 ^ (64 - 8 * d) = word8 input (b + l) / 2 ^ (64 - 8 * d)) :
    Matches input a b (l + d) := (by
  intro k hk
  by_cases hkl : k < l
  · exact h k hkl
  · have := word8_prefix input (a + l) (b + l) d hd hw (k - l) (by omega)
    rw [show b + l + (k - l) = b + k by omega, show a + l + (k - l) = a + k by omega] at this
    exact this)
theorem or_eq_add_of_mod {x t : Nat} (m : Nat) (hx : x % 2 ^ m = 0) (ht : t < 2 ^ m) :
    x ||| t = x + t := (by
  have h := Nat.two_pow_add_eq_or_of_lt ht (x / 2 ^ m)
  have hx' : 2 ^ m * (x / 2 ^ m) = x := by
    have := Nat.div_add_mod x (2 ^ m); omega
  rw [hx'] at h
  exact h.symm)
theorem shl_byte {x : Nat} (k : Nat) (hx : x < 256) (hk : k ≤ 56) :
    x <<< k % U64.size = x * 2 ^ k := (by
  rw [Nat.shiftLeft_eq, U64.size_def]
  apply Nat.mod_eq_of_lt
  have : 2 ^ k ≤ 2 ^ 56 := Nat.pow_le_pow_right (by norm_num) hk
  have : x * 2 ^ k < 256 * 2 ^ 56 := by
    calc x * 2 ^ k < 256 * 2 ^ k := by
          apply Nat.mul_lt_mul_of_pos_right hx (Nat.two_pow_pos _)
      _ ≤ 256 * 2 ^ 56 := Nat.mul_le_mul_left _ this
  simp only [U64.numBits] at *
  omega)
theorem be8_nat {a b c d e f g h : Nat} (ha : a < 256) (hb : b < 256) (hc : c < 256)
    (hd : d < 256) (he : e < 256) (hf : f < 256) (hg : g < 256) (hh : h < 256) :
    (a <<< 56 % U64.size ||| b <<< 48 % U64.size ||| c <<< 40 % U64.size |||
      d <<< 32 % U64.size ||| e <<< 24 % U64.size ||| f <<< 16 % U64.size |||
      g <<< 8 % U64.size ||| h) =
    a * 2^56 + b * 2^48 + c * 2^40 + d * 2^32 + e * 2^24 + f * 2^16 + g * 2^8 + h := C12529!
@[local step]
theorem be8_spec (s : Slice Std.U8) (i : Std.Usize) (h : i.val + 8 ≤ s.length) :
    slot.fx0_be8 s i ⦃ fun v => v.val = word8 s i.val ⦄ := (by
  rw [slot.fx0_be8]
  step*
  simp only [← getElem!_pos] at *
  simp_all only [UScalar.val_or, U8.cast_U64_val_eq]
  rw [be8_nat (u8_lt _) (u8_lt _) (u8_lt _) (u8_lt _) (u8_lt _) (u8_lt _) (u8_lt _) (u8_lt _)]
  simp only [word8])
theorem nat_xor_eq_zero {a b : Nat} (h : a ^^^ b = 0) : a = b := (by
  have : a ^^^ (a ^^^ b) = b := by rw [← Nat.xor_assoc, Nat.xor_self, Nat.zero_xor]
  rw [h, Nat.xor_zero] at this; exact this)
theorem div_eq_of_xor_lt {x y m : Nat} (hz : x ^^^ y < 2 ^ m) : x / 2 ^ m = y / 2 ^ m := (by
  have h : (x ^^^ y) >>> m = 0 := by rw [Nat.shiftRight_eq_div_pow]; exact Nat.div_eq_of_lt hz
  rw [Nat.shiftRight_xor_distrib] at h
  have := nat_xor_eq_zero h
  simpa [Nat.shiftRight_eq_div_pow] using this)
theorem lt_pow_leadingZeros (z : BitVec 64) :
    z.toNat < 2 ^ (64 - 8 * (BitVec.leadingZeros z / 8)) := (by
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
theorem leadingZeros_lt_of_ne (z : BitVec 64) (h : z ≠ 0) : BitVec.leadingZeros z < 64 := (by
  unfold BitVec.leadingZeros
  simp only [h, if_false]
  omega)
@[local step]
theorem lz_spec (x : Std.U64) :
    lift (core.num.U64.leading_zeros x) ⦃ fun r => r = core.num.U64.leading_zeros x ∧ r.val ≤ 64 ⦄ := (by
  simp only [lift, Std.WP.spec_ok, true_and]
  have hle : BitVec.leadingZeros x.bv ≤ 64 := by unfold BitVec.leadingZeros; split <;> omega
  simp only [core.num.U64.leading_zeros, UScalar.val, UScalarTy.U32_numBits_eq,
    BitVec.natCast_eq_ofNat, BitVec.toNat_ofNat, Nat.reducePow]
  omega)
theorem lz_val (x : Std.U64) :
    (core.num.U64.leading_zeros x).val = BitVec.leadingZeros x.bv := (by
  have hle : BitVec.leadingZeros x.bv ≤ 64 := by unfold BitVec.leadingZeros; split <;> omega
  simp only [core.num.U64.leading_zeros, UScalar.val, UScalarTy.U32_numBits_eq,
    BitVec.natCast_eq_ofNat, BitVec.toNat_ofNat, Nat.reducePow]
  omega)
theorem Matches.word_lz {input : Slice Std.U8} {a b k : Nat} {pa pb r k1 : Std.Usize}
    {x y z : Std.U64} {lz q : Std.U32}
    (h : Matches input a b k) (hpa : pa.val = a + k) (hpb : pb.val = b + k)
    (hx : x.val = word8 input pa.val) (hy : y.val = word8 input pb.val)
    (hz : z.val = (x ^^^ y).val) (hz0 : ¬z = 0#u64) (hlz : lz = core.num.U64.leading_zeros z)
    (hq : q.val = lz.val / 8) (hr : r = UScalar.cast .Usize q) (hk1 : k1.val = k + r.val) :
    Matches input a b k1.val ∧ k1.val < k + 8 := (by
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
theorem Matches.word_zero {input : Slice Std.U8} {a b k : Nat} {pa pb k1 : Std.Usize}
    {x y z : Std.U64}
    (h : Matches input a b k) (hpa : pa.val = a + k) (hpb : pb.val = b + k)
    (hx : x.val = word8 input pa.val) (hy : y.val = word8 input pb.val)
    (hz : z.val = (x ^^^ y).val) (hz0 : z = 0#u64) (hk1 : k1.val = k + 8) :
    Matches input a b k1.val := (by
  have hxy : x.val = y.val := by
    apply nat_xor_eq_zero
    rw [← UScalar.val_xor, ← hz, hz0]; rfl
  rw [hpa] at hx; rw [hpb] at hy
  rw [hk1]
  apply Matches.add_prefix h (le_refl 8)
  rw [← hx, ← hy, hxy])
theorem Matches.byte' {input : Slice Std.U8} {a b l : Nat} {pa pb l1 : Std.Usize}
    {x y : Std.U8} (h : Matches input a b l) (hpa : pa.val = a + l) (hpb : pb.val = b + l)
    (hpa' : pa.val < input.val.length) (hpb' : pb.val < input.val.length)
    (hx : x = input.val[pa.val]) (hy : y = input.val[pb.val]) (hxy : x = y)
    (hl1 : l1.val = l + 1) : Matches input a b l1.val := (by
  rw [hl1]
  apply LZ77.Matches.succ h
  rw [← hpa, ← hpb, getElem!_pos input.val pa.val hpa', getElem!_pos input.val pb.val hpb',
    ← hx, ← hy, hxy])
theorem common_loop0_spec (s : Slice Std.U8) (a b cap k : Std.Usize) (run : Std.U32)
    (ha : a.val + cap.val ≤ s.length) (hb : b.val + cap.val ≤ s.length) (hcap : cap.val ≤ 258)
    (hk : k.val ≤ cap.val) (hm : Matches s a.val b.val k.val) :
    slot.fx0_common_loop0 s a b cap k run ⦃ fun r =>
      r.1.val ≤ cap.val ∧ Matches s a.val b.val r.1.val ⦄ := by
  rw [slot.fx0_common_loop0]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  apply Std.loop.spec_decr_nat
    (measure := fun r => cap.val - r.1.val + r.2.val)
    (inv := fun r => r.1.val ≤ cap.val ∧ Matches s a.val b.val r.1.val)
  · rintro ⟨k, run⟩ ⟨hk, hm⟩
    simp only at hk hm
    simp only [slot.fx0_common_loop0.body]
    step*
    all_goals first
      | scalar_tac
      | (refine ⟨by scalar_tac, Matches.word_zero hm (by assumption) (by assumption)
          (by assumption) (by assumption) (by assumption) (by assumption) (by first | assumption | omega | scalar_tac),
          by scalar_tac⟩)
      | (have hw := Matches.word_lz hm (by assumption) (by assumption) (by assumption)
          (by assumption) (by assumption) (by assumption) (by assumption) (by assumption)
          (by assumption) (by assumption)
         refine ⟨by scalar_tac, hw.1, by scalar_tac⟩)
  · exact ⟨hk, hm⟩
theorem common_loop1_spec (s : Slice Std.U8) (a b cap k : Std.Usize) (run : Std.U32)
    (ha : a.val + cap.val ≤ s.length) (hb : b.val + cap.val ≤ s.length)
    (hk : k.val ≤ cap.val) (hm : Matches s a.val b.val k.val) :
    slot.fx0_common_loop1 s a b cap k run ⦃ fun r =>
      r.val ≤ cap.val ∧ Matches s a.val b.val r.val ⦄ := (by
  rw [slot.fx0_common_loop1]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  apply Std.loop.spec_decr_nat
    (measure := fun r => cap.val - r.1.val + r.2.val)
    (inv := fun r => r.1.val ≤ cap.val ∧ Matches s a.val b.val r.1.val)
  · rintro ⟨k, run⟩ ⟨hk, hm⟩
    simp only at hk hm
    simp only [slot.fx0_common_loop1.body]
    step*
    all_goals first
      | scalar_tac
      | exact ⟨hk, hm⟩
      | (refine ⟨by scalar_tac, Matches.byte' hm (by assumption) (by assumption) (by first | assumption | omega | scalar_tac)
          (by first | assumption | omega | scalar_tac) (by assumption) (by assumption) (by assumption) (by assumption),
          by scalar_tac⟩)
  · exact ⟨hk, hm⟩)
@[local step]
theorem common_spec (s : Slice Std.U8) (a b cap : Std.Usize)
    (ha : a.val + cap.val ≤ s.length) (hb : b.val + cap.val ≤ s.length) (hcap : cap.val ≤ 258) :
    slot.fx0_common s a b cap ⦃ fun l => l.val ≤ cap.val ∧ Matches s a.val b.val l.val ⦄ := by
  rw [slot.fx0_common]
  apply Std.WP.spec_bind (common_loop0_spec s a b cap 0#usize 1#u32 ha hb hcap (by simp)
    (LZ77.Matches.zero s a.val b.val))
  rintro ⟨k, run⟩ ⟨hk, hm⟩
  exact common_loop1_spec s a b cap k run ha hb hk hm
theorem Matches.word_eq {input : Slice Std.U8} {a b k : Nat} {pa pb k1 : Std.Usize}
    {x y : Std.U64}
    (h : Matches input a b k) (hpa : pa.val = a + k) (hpb : pb.val = b + k)
    (hx : x.val = word8 input pa.val) (hy : y.val = word8 input pb.val)
    (hxy : x = y) (hk1 : k1.val = k + 8) :
    Matches input a b k1.val := (by
  rw [hpa] at hx; rw [hpb] at hy
  rw [hk1]
  apply Matches.add_prefix h (le_refl 8)
  rw [← hx, ← hy, hxy])
theorem same_loop0_spec (s : Slice Std.U8) (a b len k ok : Std.Usize)
    (ha : a.val + len.val ≤ s.length) (hb : b.val + len.val ≤ s.length) (hlen : len.val ≤ 258)
    (hk : k.val ≤ len.val) (hm : Matches s a.val b.val k.val) :
    slot.fx0_same_loop0 s a b len k ok ⦃ fun r =>
      r.1.val ≤ len.val ∧ Matches s a.val b.val r.1.val ∧ (r.2.val = 1 → len.val < r.1.val + 8) ⦄ := (by
  rw [slot.fx0_same_loop0]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  apply Std.loop.spec_decr_nat
    (measure := fun r => len.val - r.1.val + r.2.val)
    (inv := fun r => r.1.val ≤ len.val ∧ Matches s a.val b.val r.1.val)
  · rintro ⟨k, ok⟩ ⟨hk, hm⟩
    simp only at hk hm
    simp only [slot.fx0_same_loop0.body]
    step*
    all_goals first
      | scalar_tac
      | (refine ⟨by scalar_tac, Matches.word_eq hm (by assumption) (by assumption)
          (by assumption) (by assumption) (by assumption) (by first | assumption | omega | scalar_tac), by scalar_tac⟩)
  · exact ⟨hk, hm⟩)
@[local step]
theorem same_loop1_spec (s : Slice Std.U8) (a b len k ok : Std.Usize)
    (ha : a.val + len.val ≤ s.length) (hb : b.val + len.val ≤ s.length)
    (hk : k.val ≤ len.val) (hm : Matches s a.val b.val k.val) :
    slot.fx0_same_loop1 s a b len k ok ⦃ fun r => r.val = 1 → Matches s a.val b.val len.val ⦄ := (by
  rw [slot.fx0_same_loop1]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  apply Std.loop.spec_decr_nat
    (measure := fun r => len.val - r.1.val + r.2.val)
    (inv := fun r => r.1.val ≤ len.val ∧ Matches s a.val b.val r.1.val)
  · rintro ⟨k, ok⟩ ⟨hk, hm⟩
    simp only at hk hm
    simp only [slot.fx0_same_loop1.body]
    step*
    all_goals first
      | scalar_tac
      | (refine ⟨by scalar_tac, Matches.byte' hm (by assumption) (by assumption) (by first | assumption | omega | scalar_tac)
          (by first | assumption | omega | scalar_tac) (by assumption) (by assumption) (by assumption) (by assumption),
          by scalar_tac⟩)
  · exact ⟨hk, hm⟩)
@[local step]
theorem same_loop2_spec (s : Slice Std.U8) (a b len k ok : Std.Usize)
    (ha : a.val + len.val ≤ s.length) (hb : b.val + len.val ≤ s.length)
    (hk : k.val ≤ len.val) (hm : Matches s a.val b.val k.val) :
    slot.fx0_same_loop2 s a b len k ok ⦃ fun r => r.val = 1 → Matches s a.val b.val len.val ⦄ := (by
  rw [slot.fx0_same_loop2]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  apply Std.loop.spec_decr_nat
    (measure := fun r => len.val - r.1.val + r.2.val)
    (inv := fun r => r.1.val ≤ len.val ∧ Matches s a.val b.val r.1.val)
  · rintro ⟨k, ok⟩ ⟨hk, hm⟩
    simp only at hk hm
    simp only [slot.fx0_same_loop2.body]
    step*
    all_goals first
      | scalar_tac
      | (refine ⟨by scalar_tac, Matches.byte' hm (by assumption) (by assumption) (by first | assumption | omega | scalar_tac)
          (by first | assumption | omega | scalar_tac) (by assumption) (by assumption) (by assumption) (by assumption),
          by scalar_tac⟩)
  · exact ⟨hk, hm⟩)
theorem Matches.mask {input : Slice Std.U8} {a b k len : Nat} {pa pb : Std.Usize}
    {x y z w : Std.U64} {sh : Std.U32}
    (h : Matches input a b k) (hpa : pa.val = a + k) (hpb : pb.val = b + k)
    (hx : x.val = word8 input pa.val) (hy : y.val = word8 input pb.val)
    (hz : z.val = (x ^^^ y).val) (hw : w.val = z.val >>> sh.val) (hw0 : ¬(w != 0#u64) = true)
    (hsh : sh.val = 64 - 8 * (len - k)) (hk : k < len) (hlen : len < k + 8) :
    Matches input a b len := (by
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
@[local step]
theorem same_spec (s : Slice Std.U8) (a b len : Std.Usize)
    (ha : a.val + len.val ≤ s.length) (hb : b.val + len.val ≤ s.length) (hlen : len.val ≤ 258)
    (ha8 : a.val + len.val + 7 ≤ Std.Usize.max) (hb8 : b.val + len.val + 7 ≤ Std.Usize.max) :
    slot.fx0_same s a b len ⦃ fun r => r.val = 1 → Matches s a.val b.val len.val ⦄ := (by
  rw [slot.fx0_same]
  apply Std.WP.spec_bind (same_loop0_spec s a b len 0#usize 1#usize ha hb hlen (by simp)
    (LZ77.Matches.zero s a.val b.val))
  rintro ⟨k, ok⟩ ⟨hk, hm, hok⟩
  simp only at hk hm hok
  step*
  intro _
  exact Matches.mask hm (by assumption) (by assumption) (by assumption) (by assumption)
    (by assumption) (by assumption) (by assumption) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac)
    (by first | assumption | omega | scalar_tac))
theorem lz32_le (x : Std.U32) (k : Nat) (hk : k < 32) (hx : 2 ^ k ≤ x.val) :
    (core.num.U32.leading_zeros x).val ≤ 31 - k := C12546!
@[local step]
theorem lz32_spec (x : Std.U32) :
    lift (core.num.U32.leading_zeros x) ⦃ fun r => r = core.num.U32.leading_zeros x ∧
      (4 ≤ x.val → r.val ≤ 29) ∧ (8 ≤ x.val → r.val ≤ 28) ⦄ := (by
  simp only [lift, Std.WP.spec_ok, true_and]
  exact ⟨fun h => lz32_le x 2 (by norm_num) (by simpa using h),
    fun h => lz32_le x 3 (by norm_num) (by simpa using h)⟩)
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
theorem HeadBound.init (N : Std.Usize) : HeadBound (Std.Array.repeat N 0#u32) 0 := (by
  intro j hj
  rw [Std.Array.repeat_val] at hj ⊢
  rw [List.getElem!_eq_getElem?_getD, List.getElem?_replicate_of_lt (by simpa using hj)]
  rfl)
theorem HeadBound.set {N : Std.Usize} {head : Array Std.U32 N} {B : Nat} (h : HeadBound head B)
    (a : Std.Usize) (v : Std.U32) (hv : v.val ≤ B) : HeadBound (head.set a v) B := (by
  intro j hj
  rw [Std.Array.set_val_eq] at hj ⊢
  rw [List.length_set] at hj
  by_cases hja : a.val = j
  · subst hja
    rw [List.getElem!_eq_getElem?_getD, List.getElem?_set_self hj]
    exact hv
  · rw [List.getElem!_eq_getElem?_getD, List.getElem?_set_ne hja, ← List.getElem!_eq_getElem?_getD]
    exact h j hj)
theorem HeadBound.update {N : Std.Usize} {head head1 : Array Std.U32 N} {B : Nat}
    {a i : Std.Usize} {v : Std.U32} (h : HeadBound head B) (hv : v = UScalar.cast .U32 i)
    (hi : i.val ≤ B) (h1 : head1 = head.set a v) : HeadBound head1 B := (by
  subst h1
  apply HeadBound.set h a v
  rw [hv]
  have : (UScalar.cast .U32 i).val = i.val % 2 ^ 32 := by
    simp only [UScalar.cast_val_eq, UScalarTy.U32_numBits_eq]
  rw [this]
  exact le_trans (Nat.mod_le _ _) hi)
theorem HeadBound.get {N : Std.Usize} {head : Array Std.U32 N} {B : Nat} (h : HeadBound head B)
    (a : Std.Usize) (x : Std.U32) (ha : a.val < head.val.length) (hx : x = head.val[a.val]) :
    x.val ≤ B := (by
  have := h a.val ha
  rw [getElem!_pos head.val a.val ha, ← hx] at this
  exact this)
theorem cast_usize_le {x : Std.U32} {y : Std.Usize} {B : Nat} (h : y = UScalar.cast .Usize x)
    (hx : x.val ≤ B) : y.val ≤ B := (by
  rw [h, U32.cast_Usize_val_eq]; exact hx)
@[local step]
theorem be4_spec (s : Slice Std.U8) (i : Std.Usize) (hi : i.val + 4 ≤ Std.Usize.max) :
    slot.fx0_be4 s i ⦃ fun _ => True ⦄ := by
  rw [slot.fx0_be4]
  step*
@[local step]
theorem insert_spec (s : Slice Std.U8) {H W : Std.Usize} (head : Array Std.U32 H)
    (prev : Array Std.U32 W) (i : Std.Usize) (mask : Std.U32) (B : Nat) (hB : HeadBound head B)
    (hi : i.val < B + 1) (hi4 : i.val + 4 ≤ Std.Usize.max) (hH : 0 < H.val) (hW : 0 < W.val) :
    slot.fx0_insert s head prev i mask ⦃ fun r => r.1.val ≤ B ∧ HeadBound r.2.1 B ⦄ := by
  rw [slot.fx0_insert]
  step*
  have hold : old.val ≤ B := HeadBound.get hB a old (by first | assumption | omega | scalar_tac) (by assumption)
  exact ⟨cast_usize_le (by assumption) hold,
    HeadBound.update hB (by assumption) (by omega) (by assumption)⟩
def Cand (s : Slice Std.U8) (p cap best bd : Nat) : Prop :=
  bd = 0 ∨ (1 ≤ bd ∧ bd ≤ 32768 ∧ bd ≤ p ∧ best ≤ cap ∧ Matches s (p - bd) p best)
theorem dist_of_wrapping {p c d i : Std.Usize} (hc : c.val ≤ p.val)
    (hd : d = core.num.Usize.wrapping_sub p c) (hi : i = core.num.Usize.wrapping_sub d 1#usize)
    (hlt : i < 32768#usize) : d.val = p.val - c.val ∧ 1 ≤ d.val ∧ d.val ≤ 32768 := C12553!
theorem Cand.of_common {s : Slice Std.U8} {p c d i l cap : Std.Usize} (hc : c.val ≤ p.val)
    (hd : d = core.num.Usize.wrapping_sub p c) (hi : i = core.num.Usize.wrapping_sub d 1#usize)
    (hlt : i < 32768#usize) (hl : l.val ≤ cap.val) (hm : Matches s c.val p.val l.val) :
    Cand s p.val cap.val l.val d.val := (by
  obtain ⟨hdv, hd1, hd2⟩ := dist_of_wrapping hc hd hi hlt
  refine Or.inr ⟨hd1, hd2, by omega, hl, ?_⟩
  rw [show p.val - d.val = c.val by omega]
  exact hm)
theorem walk_loop_spec (s : Slice Std.U8) {W : Std.Usize} (prev : Array Std.U32 W)
    (p cap gm n best bd : Std.Usize) (bg : Std.I32) (c k stop : Std.Usize) (pb : Std.U8)
    (hn : n.val = s.length) (hcap : p.val + cap.val ≤ s.length) (hcap258 : cap.val ≤ 258)
    (hc : c.val ≤ p.val) (hbest : p.val + best.val ≤ s.length)
    (hcand : Cand s p.val cap.val best.val bd.val) (hW : 0 < W.val) :
    slot.fx0_walk_loop s prev p cap gm n best bd bg c k stop pb ⦃ fun r =>
      p.val + r.1.val ≤ s.length ∧ Cand s p.val cap.val r.1.val r.2.val ⦄ := by
  rw [slot.fx0_walk_loop]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  apply Std.loop.spec_decr_nat
    (measure := fun r => r.2.2.2.2.1.val)
    (inv := fun r => r.2.2.2.1.val ≤ p.val ∧ p.val + r.1.val ≤ s.length ∧
      Cand s p.val cap.val r.1.val r.2.1.val)
  · rintro ⟨best, bd, bg, c, k, pb⟩ ⟨hc, hbest, hcand⟩
    simp only at hc hbest hcand
    simp only [slot.fx0_walk_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals first
      | exact (dist_of_wrapping hc (by assumption) (by assumption) (by assumption)).2.2
      | (refine ⟨by scalar_tac, by scalar_tac, Cand.of_common hc (by assumption) (by assumption)
          (by assumption) (by assumption) (by assumption), by scalar_tac⟩)
  · exact ⟨hc, hbest, hcand⟩
@[local step]
theorem walk_spec (s : Slice Std.U8) {W : Std.Usize} (prev : Array Std.U32 W)
    (p start cap «have» depth gm : Std.Usize)
    (hcap : p.val + cap.val ≤ s.length) (hcap258 : cap.val ≤ 258) (hst : start.val ≤ p.val)
    (hhave : p.val + «have».val ≤ s.length) (hW : 0 < W.val) :
    slot.fx0_walk s prev p start cap «have» depth gm ⦃ fun r =>
      p.val + r.1.val ≤ s.length ∧ Cand s p.val cap.val r.1.val r.2.val ⦄ := by
  rw [slot.fx0_walk]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  repeat' (split <;> step*)
  all_goals
    exact walk_loop_spec s prev p cap gm (Std.Slice.len s) «have» 0#usize _ start depth _ _
      (by simp) hcap hcap258 hst hhave (Or.inl rfl) hW
def MatchAt (s : Slice Std.U8) (p l d : Nat) : Prop :=
  3 ≤ l ∧ l ≤ 258 ∧ p + l ≤ s.length ∧ 1 ≤ d ∧ d ≤ 32768 ∧ d ≤ p ∧ Matches s (p - d) p l
def FoundAt (s : Slice Std.U8) (p l d : Nat) : Prop := l < 3 ∨ MatchAt s p l d
theorem FoundAt.of_cand {s : Slice Std.U8} {p cap : Nat} {l d : Std.Usize}
    (hc : Cand s p cap l.val d.val) (hd : ¬d = 0#usize) (hcap : cap ≤ 258)
    (hpl : p + l.val ≤ s.length) : FoundAt s p l.val d.val := (by
  have hd' : d.val ≠ 0 := by intro h; apply hd; exact UScalar.eq_of_val_eq (by simp [h])
  rcases hc with h0 | ⟨hd1, hd2, hdp, hl, hm⟩
  · exact absurd h0 hd'
  · rcases Nat.lt_or_ge l.val 3 with h3 | h3
    · exact Or.inl h3
    · exact Or.inr ⟨h3, by omega, hpl, hd1, hd2, hdp, hm⟩)
theorem Cand.len_le {s : Slice Std.U8} {p cap : Nat} {l d : Std.Usize}
    (hc : Cand s p cap l.val d.val) (hd : ¬d = 0#usize) (hcap : cap ≤ 258) : l.val ≤ 258 := (by
  have hd' : d.val ≠ 0 := by intro h; apply hd; exact UScalar.eq_of_val_eq (by simp [h])
  rcases hc with h0 | ⟨_, _, _, hl, _⟩
  · exact absurd h0 hd'
  · omega)
theorem Cand.dist_le {s : Slice Std.U8} {p cap l d : Nat} (hc : Cand s p cap l d) :
    d ≤ 32768 := (by
  rcases hc with h0 | ⟨_, hd, _⟩ <;> omega)
theorem FoundAt.none (s : Slice Std.U8) (p : Nat) : FoundAt s p (0#usize).val (0#usize).val :=
  Or.inl (by simp)
theorem FoundAt.real {s : Slice Std.U8} {p l d : Nat} (hf : FoundAt s p l d) (h3 : 3 ≤ l) :
    MatchAt s p l d := (by
  rcases hf with h | h
  · omega
  · exact h)
@[local step]
theorem find_spec (s : Slice Std.U8) {W : Std.Usize} (prev : Array Std.U32 W)
    (p st «have» minl depth gm : Std.Usize)
    (hp : p.val ≤ s.length) (hst : st.val ≤ p.val) (hhave : p.val + «have».val ≤ s.length)
    (hhave258 : «have».val ≤ 258) (hminl : 1 ≤ minl.val) (hminl' : p.val + minl.val ≤ s.length + 1)
    (hW : 0 < W.val) :
    slot.fx0_find s prev p st «have» minl depth gm ⦃ fun r => FoundAt s p.val r.1.val r.2.val ∧
      r.1.val ≤ 258 ∧ r.2.val ≤ 32768 ⦄ := by
  rw [slot.fx0_find]
  step*
  repeat' (split <;> step*)
  all_goals first
    | exact ⟨FoundAt.none s p.val, by simp, by simp⟩
    | exact ⟨FoundAt.of_cand (by assumption) (by assumption) (by first | assumption | omega | scalar_tac) (by assumption),
        Cand.len_le (by assumption) (by assumption) (by first | assumption | omega | scalar_tac),
        Cand.dist_le (by assumption)⟩
theorem copyN_take_prefix (acc : List Nat) (d : Nat) :
    ∀ n, (copyN acc d n).take acc.length = acc := (by
  intro n
  induction n with
  | zero => simp [copyN]
  | succ m ih =>
    simp only [copyN]
    rw [List.take_append_of_le_length (by simp)]
    exact ih)
theorem foldlM_emit_length : ∀ (ts : List Nat) (init acc : List Nat),
    ts.foldlM emit init = some acc → init.length + ts.length ≤ acc.length := C12560!
theorem decode_length_le {ts acc : List Nat} (h : decode ts = some acc) :
    ts.length ≤ acc.length := (by
  have := foldlM_emit_length ts [] acc h
  simpa using this)
theorem decode_pop_lit {ts : List Nat} {t : Nat} {inp : List Nat} {p : Nat}
    (hp : p ≤ inp.length) (hd : decode (ts ++ [t]) = some (inp.take p)) (ht : t < 256) :
    1 ≤ p ∧ decode ts = some (inp.take (p - 1)) := (by
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
theorem decode_pop_match {ts : List Nat} {t : Nat} {inp : List Nat} {p : Nat}
    (hp : p ≤ inp.length) (hd : decode (ts ++ [t]) = some (inp.take p)) (ht : 256 ≤ t) :
    tokLen t ≤ p ∧ decode ts = some (inp.take (p - tokLen t)) := C12563!
theorem toks_pop (out : Slice Std.U32) (nt : Nat) (h0 : 0 < nt) (hle : nt ≤ out.length) :
    toks out nt = toks out (nt - 1) ++ [(out.val[nt - 1]!).val] := (by
  have hlt : nt - 1 < out.val.length := by
    have : out.length = out.val.length := rfl
    omega
  simp only [toks]
  conv_lhs => rw [show nt = (nt - 1) + 1 by omega]
  rw [List.take_add_one, List.getElem?_eq_getElem hlt, Option.toList_some, List.map_append]
  simp [getElem!_pos out.val (nt - 1) hlt])
theorem toks_length (out : Slice Std.U32) (nt : Nat) (h : nt ≤ out.length) :
    (toks out nt).length = nt := (by
  simp only [toks, List.length_map, List.length_take]
  have : out.length = out.val.length := rfl
  omega)
def Dec (s : Slice Std.U8) (out : Slice Std.U32) (nt p : Nat) : Prop :=
  p ≤ s.length ∧ nt ≤ p ∧ s.length ≤ out.length ∧
    decode (toks out nt) = some ((bytes s).take p)
theorem Dec.init (input : Slice Std.U8) (out : Slice Std.U32) (h : input.length ≤ out.length) :
    Dec input out (0#usize).val (0#usize).val :=
  ⟨by simp, by simp, h, by simp [toks, LZ77.decode]⟩
theorem Dec.lit {s : Slice Std.U8} {out : Slice Std.U32} {nt p : Nat} (h : Dec s out nt p)
    (hp : p < s.length) (ntU : Std.Usize) (hnt : ntU.val = nt) (v : Std.U32)
    (hv : v.val = (s.val[p]!).val) :
    Dec s (out.set ntU v) (nt + 1) (p + 1) := (by
  obtain ⟨hps, hntp, hso, hde⟩ := h
  have hntl : ntU.val < out.length := by omega
  refine ⟨by omega, by omega, by rw [Std.Slice.set_length]; exact hso, ?_⟩
  rw [← hnt]
  refine emit_lit s out ntU p v (by rw [hnt]; exact hde) hp hntl ?_
  have hpl : p < s.val.length := hp
  rw [hv, bytes_getElem! s p hpl, getElem!_pos s.val p hpl])
theorem Dec.match {s : Slice Std.U8} {out : Slice Std.U32} {nt p l d : Nat} (h : Dec s out nt p)
    (hm : MatchAt s p l d) (ntU : Std.Usize) (hnt : ntU.val = nt) (v : Std.U32)
    (hv : v.val = LZ77.mkMatch d l) :
    Dec s (out.set ntU v) (nt + 1) (p + l) := (by
  obtain ⟨hps, hntp, hso, hde⟩ := h
  obtain ⟨h3, h258, hpl, hd1, hd32, hdp, hmm⟩ := hm
  have hntl : ntU.val < out.length := by omega
  refine ⟨by omega, by omega, by rw [Std.Slice.set_length]; exact hso, ?_⟩
  rw [← hnt]
  exact emit_match s out ntU p d l v (by rw [hnt]; exact hde) hntl hd1 hdp hd32 h3 h258 hpl hmm hv)
theorem Dec.pop_lit {s : Slice Std.U8} {out : Slice Std.U32} {nt p : Nat} (h : Dec s out nt p)
    (h0 : 0 < nt) (hle : nt ≤ out.length) (ht : (out.val[nt - 1]!).val < 256) :
    1 ≤ p ∧ Dec s out (nt - 1) (p - 1) := (by
  obtain ⟨hps, hntp, hso, hde⟩ := h
  rw [toks_pop out nt h0 hle] at hde
  obtain ⟨hp1, hde'⟩ := decode_pop_lit (by simpa using hps) hde ht
  exact ⟨hp1, by omega, by omega, hso, hde'⟩)
theorem Dec.pop_match {s : Slice Std.U8} {out : Slice Std.U32} {nt p : Nat} (h : Dec s out nt p)
    (h0 : 0 < nt) (hle : nt ≤ out.length) (ht : 256 ≤ (out.val[nt - 1]!).val) :
    tokLen (out.val[nt - 1]!).val ≤ p ∧
      Dec s out (nt - 1) (p - tokLen (out.val[nt - 1]!).val) := (by
  obtain ⟨hps, hntp, hso, hde⟩ := h
  rw [toks_pop out nt h0 hle] at hde
  obtain ⟨hw, hde'⟩ := decode_pop_match (by simpa using hps) hde ht
  have hlen := decode_length_le hde'
  rw [toks_length out (nt - 1) (by omega), List.length_take, bytes_length] at hlen
  exact ⟨hw, by omega, by omega, hso, hde'⟩)
theorem Dec.done {s : Slice Std.U8} {out : Slice Std.U32} {nt p : Nat} (h : Dec s out nt p)
    (hp : s.length ≤ p) : nt ≤ s.length ∧ LZ77.Valid (bytes s) (toks out nt) := (by
  obtain ⟨hps, hntp, hso, hde⟩ := h
  refine ⟨by omega, ?_⟩
  unfold LZ77.Valid
  rw [hde, show p = s.length by omega, ← bytes_length, List.take_length])
theorem Dec.lit_step {s : Slice Std.U8} {out out1 : Slice Std.U32} {ntU nt1 pU : Std.Usize}
    {b : Std.U8} {v : Std.U32} (h : Dec s out ntU.val pU.val) (hp : pU.val < s.val.length)
    (hb : b = s.val[pU.val]) (hv : v = UScalar.cast .U32 b) (hout1 : out1 = out.set ntU v)
    (hnt1 : nt1.val = ntU.val + 1) :
    nt1.val = ntU.val + 1 ∧ out1.length = out.length ∧ Dec s out1 nt1.val (pU.val + 1) := (by
  subst hout1
  refine ⟨hnt1, Std.Slice.set_length .., ?_⟩
  rw [hnt1]
  exact Dec.lit h hp ntU rfl v (by rw [hv, U8.cast_U32_val_eq, hb, getElem!_pos s.val pU.val hp]))
@[local step]
theorem put_lit_spec (s : Slice Std.U8) (out : Slice Std.U32) (nt p : Std.Usize)
    (hdec : Dec s out nt.val p.val) (hp : p.val < s.length) :
    slot.fx0_put_lit s out nt p ⦃ fun r => r.1.val = nt.val + 1 ∧ r.2.length = out.length ∧
      Dec s r.2 r.1.val (p.val + 1) ⦄ := by
  rw [slot.fx0_put_lit]
  step*
  exact Dec.lit_step hdec (by first | assumption | omega | scalar_tac) (by assumption) (by assumption) (by assumption)
    (by assumption)
theorem Dec.match_step {s : Slice Std.U8} {out out1 : Slice Std.U32} {ntU nt1 pU dU lU e : Std.Usize}
    {v : Std.U32} (h : Dec s out ntU.val pU.val) (hm : MatchAt s pU.val lU.val dU.val)
    (hout1 : out1 = out.set ntU v) (hv : v.val = LZ77.mkMatch dU.val lU.val)
    (hnt1 : nt1.val = ntU.val + 1) (he : e.val = pU.val + lU.val) :
    nt1.val = ntU.val + 1 ∧ e.val = pU.val + lU.val ∧ out1.length = out.length ∧
      Dec s out1 nt1.val e.val := (by
  subst hout1
  refine ⟨hnt1, he, Std.Slice.set_length .., ?_⟩
  rw [hnt1, he]
  exact Dec.match h hm ntU rfl v hv)
@[local step]
theorem put_match_spec (s : Slice Std.U8) (out : Slice Std.U32) (nt p d l : Std.Usize)
    (hdec : Dec s out nt.val p.val) (hm : MatchAt s p.val l.val d.val) :
    slot.fx0_put_match s out nt p d l ⦃ fun r => r.1.1.val = nt.val + 1 ∧
      r.1.2.val = p.val + l.val ∧ r.2.length = out.length ∧ Dec s r.2 r.1.1.val r.1.2.val ⦄ := (by
  rw [slot.fx0_put_match]
  have hm' := hm
  obtain ⟨h3, h258, hpl, hd1, hd32, hdp, _⟩ := hm'
  step*
  exact Dec.match_step hdec hm (by assumption)
    (by simp only [LZ77.mkMatch, LZ77.MATCH_BASE]; simp_all; scalar_tac) (by assumption) (by assumption))
theorem MatchAt.back_lit {s : Slice Std.U8} {p l d : Nat} (h : MatchAt s p l d) (hl : l < 258)
    (hdp : d < p) (heq : s.val[p - 1]! = s.val[p - 1 - d]!) : MatchAt s (p - 1) (l + 1) d := (by
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
theorem MatchAt.back_match {s : Slice Std.U8} {p l d w : Nat} (h : MatchAt s p l d)
    (hlw : l + w ≤ 258) (hw : w ≤ p) (hdw : d ≤ p - w) (hmw : Matches s (p - w - d) (p - w) w) :
    MatchAt s (p - w) (l + w) d := (by
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
    BackInv input out d E P0 i1.val i2.val l1.val := (by
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
theorem BackInv.match {input : Slice Std.U8} {out : Slice Std.U32} {d E P0 : Nat}
    {nt p l i1 w i9 i10 i11 i12 : Std.Usize} {t : Std.U32}
    (h : BackInv input out d E P0 nt.val p.val l.val)
    (hi1 : i1.val = nt.val - 1) (hntl : nt.val ≤ out.length) (hnt0 : 1 ≤ nt.val)
    (hi1l : i1.val < out.val.length) (ht : t = out.val[i1.val])
    (hsame : i12.val = 1 → Matches input i11.val i10.val w.val) (hi12 : i12 = 1#usize)
    (ht24 : 16777216 ≤ t.val) (hwv : w.val = (t.val - 16777216) % 256 + 3)
    (hi9 : i9.val = l.val + w.val) (hi9' : i9.val ≤ 258) (hi10 : i10.val = p.val - w.val)
    (hwp : w.val ≤ p.val) (hdw : d ≤ i10.val) (hi11 : i11.val = i10.val - d) :
    BackInv input out d E P0 i1.val i10.val i9.val := C12577!
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
      | (refine ⟨BackInv.lit hinv (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac)
          (by assumption) (by assumption) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by assumption)
          (by assumption) (by assumption) (by first | assumption | omega | scalar_tac) (by assumption) (by first | assumption | omega | scalar_tac)
          (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac), by scalar_tac⟩)
      | (refine ⟨BackInv.match hinv (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac)
          (by assumption) (by assumption) (by assumption) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac)
          (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac)
          (by first | assumption | omega | scalar_tac), by scalar_tac⟩)
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
    LazyInv input L lim out1 nt1.val i.val head1 ins1.val l1.val d1.val := (by
  subst hi
  refine ⟨hdec, hlen, ?_, HeadBound.mono hB hBi, hilim, hins⟩
  rcases hf with h | h
  · omega
  · exact h)
theorem LazyInv.reject {input : Slice Std.U8} {L lim : Nat} {out : Slice Std.U32}
    {nt p ins ins1 l d B : Nat} {N : Std.Usize} {head head1 : Array Std.U32 N}
    (h : LazyInv input L lim out nt p head ins l d) (hB : HeadBound head1 B) (hBp : B ≤ p + 1)
    (hins1 : ins1 ≤ p + 2) : LazyInv input L lim out nt p head1 ins1 l d := (by
  obtain ⟨hdec, hlen, hm, _, hplim, _⟩ := h
  exact ⟨hdec, hlen, hm, HeadBound.mono hB hBp, hplim, hins1⟩)
theorem lazy_loop_inv {H W : Std.Usize} (input : Slice Std.U8) (out : Slice Std.U32)
    (cls nt p : Std.Usize) (mask : Std.U32) (minl lazy : Std.Usize) (head : Array Std.U32 H)
    (prev : Array Std.U32 W) (lim ins l d : Std.Usize) (go : Std.U32) (L : Nat)
    (hlim : lim.val + 8 = input.length) (hminl : 3 ≤ minl.val) (hminl8 : minl.val ≤ 8)
    (hH : 0 < H.val) (hW : 0 < W.val)
    (hinv : LazyInv input L lim.val out nt.val p.val head ins.val l.val d.val) :
    slot.fx0_run_loop0_loop1 input out cls nt p mask minl lazy head prev lim ins l d go ⦃ fun r =>
      LazyInv input L lim.val r.1 r.2.1.val r.2.2.1.val r.2.2.2.1 r.2.2.2.2.2.1.val
        r.2.2.2.2.2.2.1.val r.2.2.2.2.2.2.2.val ⦄ := by
  rw [slot.fx0_run_loop0_loop1]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  apply Std.loop.spec_decr_nat
    (measure := fun r => lim.val - r.2.2.1.val + r.2.2.2.2.2.2.2.2.val)
    (inv := fun r => LazyInv input L lim.val r.1 r.2.1.val r.2.2.1.val r.2.2.2.1
      r.2.2.2.2.2.1.val r.2.2.2.2.2.2.1.val r.2.2.2.2.2.2.2.1.val)
  · rintro ⟨out, nt, p, head, prev, ins, l, d, go⟩ hinv
    simp only at hinv
    have hinv' := hinv
    obtain ⟨⟨hps, hntp, hso, _⟩, hL, ⟨h3, h258, hpl, hd1, hd32, hdp, _⟩, hB, hplim, hins⟩ := hinv'
    simp only [slot.fx0_run_loop0_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals first
      | exact hinv.1
      | (refine ⟨LazyInv.accept (by assumption) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by assumption)
          (by first | assumption | omega | scalar_tac) hminl (by assumption) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac),
          by scalar_tac⟩)
      | (refine ⟨LazyInv.reject hinv (by assumption) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac),
          by scalar_tac⟩)
  · exact hinv
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
      r.2.2.2.2.2.1.val ≤ r.2.2.1.val + 2 ∧ 3 ≤ r.2.2.2.2.2.2.1.val ⦄ := by
  apply Std.WP.spec_mono (lazy_loop_inv input out cls nt p mask minl lazy head prev lim ins l d go L
    hlim hminl hminl8 hH hW ⟨hdec, hlen, hm, hB, hplim, hins⟩)
  rintro ⟨out', nt', p', head', prev', ins', l', d'⟩ ⟨hdec', hlen', hm', hB', hplim', hins'⟩
  exact ⟨hdec', hlen', hm', HeadBound.mono hB' (by have := hm'.1; omega), hplim', hins', hm'.1⟩
@[local step]
theorem ins_loop0_spec {H W : Std.Usize} (input : Slice Std.U8) (p : Std.Usize) (mask : Std.U32)
    (head : Array Std.U32 H) (prev : Array Std.U32 W) (ins : Std.Usize) (B : Nat)
    (hB : HeadBound head B) (hpB : p.val < B + 1) (hp4 : p.val + 4 ≤ Std.Usize.max)
    (hH : 0 < H.val) (hW : 0 < W.val) :
    slot.fx0_run_loop0_loop0 input p mask head prev ins ⦃ fun r => HeadBound r.1 B ⦄ := by
  rw [slot.fx0_run_loop0_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun r => p.val - r.2.2.val)
    (inv := fun r => HeadBound r.1 B)
  · rintro ⟨head, prev, ins⟩ hB
    simp only at hB
    simp only [slot.fx0_run_loop0_loop0.body]
    step*
  · exact hB
@[local step]
theorem ins_loop3_spec {H W : Std.Usize} (input : Slice Std.U8) (mask : Std.U32)
    (head : Array Std.U32 H) (prev : Array Std.U32 W) (ins stop : Std.Usize) (B : Nat)
    (hB : HeadBound head B) (hsB : stop.val < B + 1) (hs4 : stop.val + 4 ≤ Std.Usize.max)
    (hH : 0 < H.val) (hW : 0 < W.val) :
    slot.fx0_run_loop0_loop3 input mask head prev ins stop ⦃ fun r =>
      HeadBound r.1 B ∧ (r.2.2.val ≤ ins.val ∨ r.2.2.val ≤ stop.val) ⦄ := (by
  rw [slot.fx0_run_loop0_loop3]
  apply Std.loop.spec_decr_nat
    (measure := fun r => stop.val - r.2.2.val)
    (inv := fun r => HeadBound r.1 B ∧ (r.2.2.val ≤ ins.val ∨ r.2.2.val ≤ stop.val))
  · rintro ⟨head, prev, ins'⟩ ⟨hB, hins⟩
    simp only at hB hins
    simp only [slot.fx0_run_loop0_loop3.body]
    step*
  · exact ⟨hB, Or.inl (le_refl _)⟩)
@[local step]
theorem v31z {H W : Std.Usize} (input : Slice Std.U8) (mask : Std.U32)
    (head : Array Std.U32 H) (prev : Array Std.U32 W) (lim ins «end» : Std.Usize) (B : Nat)
    (hB : HeadBound head B) (heB : «end».val < B + 1) (hl4 : lim.val + 4 ≤ Std.Usize.max)
    (hH : 0 < H.val) (hW : 0 < W.val) (hS : 0 < slot.FX0_STRIDE.val)
    (hie : ins.val ≤ «end».val) :
    slot.fx0_run_loop0_loop4 input mask head prev lim ins «end» ⦃ fun r =>
      HeadBound r.1 B ∧ r.2.2.val ≤ «end».val ∧
        (r.2.2.val ≤ ins.val ∨ r.2.2.val + slot.FX0_TAIL.val < «end».val) ⦄ := by
  rw [slot.fx0_run_loop0_loop4]
  apply Std.loop.spec_decr_nat
    (measure := fun r => «end».val - r.2.2.val)
    (inv := fun r => HeadBound r.1 B ∧ r.2.2.val ≤ «end».val ∧
      (r.2.2.val ≤ ins.val ∨ r.2.2.val + slot.FX0_TAIL.val < «end».val))
  · rintro ⟨head, prev, ins'⟩ ⟨hB, hie', hins⟩
    simp only at hB hie' hins
    simp only [slot.fx0_run_loop0_loop4.body]
    step*
    all_goals first
      | exact ⟨hB, hie', hins⟩
      | exact ⟨by assumption, by scalar_tac, by scalar_tac, by scalar_tac⟩
  · exact ⟨hB, hie, Or.inl (le_refl _)⟩
@[local step]
theorem ins_loop5_spec {H W : Std.Usize} (input : Slice Std.U8) (mask : Std.U32)
    (head : Array Std.U32 H) (prev : Array Std.U32 W) (lim ins «end» : Std.Usize) (B : Nat)
    (hB : HeadBound head B) (heB : «end».val < B + 1) (hl4 : lim.val + 4 ≤ Std.Usize.max)
    (hH : 0 < H.val) (hW : 0 < W.val) :
    slot.fx0_run_loop0_loop5 input mask head prev lim ins «end» ⦃ fun r =>
      HeadBound r.1 B ∧ (r.2.2.val ≤ ins.val ∨ r.2.2.val ≤ «end».val) ⦄ := (by
  rw [slot.fx0_run_loop0_loop5]
  apply Std.loop.spec_decr_nat
    (measure := fun r => «end».val - r.2.2.val)
    (inv := fun r => HeadBound r.1 B ∧ (r.2.2.val ≤ ins.val ∨ r.2.2.val ≤ «end».val))
  · rintro ⟨head, prev, ins'⟩ ⟨hB, hins⟩
    simp only at hB hins
    simp only [slot.fx0_run_loop0_loop5.body]
    step*
  · exact ⟨hB, Or.inl (le_refl _)⟩)
@[local step]
theorem ins_loop6_spec {H W : Std.Usize} (input : Slice Std.U8) (mask : Std.U32)
    (head : Array Std.U32 H) (prev : Array Std.U32 W) (lim ins «end» : Std.Usize) (B : Nat)
    (hB : HeadBound head B) (heB : «end».val < B + 1) (hl4 : lim.val + 4 ≤ Std.Usize.max)
    (hH : 0 < H.val) (hW : 0 < W.val) :
    slot.fx0_run_loop0_loop6 input mask head prev lim ins «end» ⦃ fun r =>
      HeadBound r.1 B ∧ (r.2.2.val ≤ ins.val ∨ r.2.2.val ≤ «end».val) ⦄ := (by
  rw [slot.fx0_run_loop0_loop6]
  apply Std.loop.spec_decr_nat
    (measure := fun r => «end».val - r.2.2.val)
    (inv := fun r => HeadBound r.1 B ∧ (r.2.2.val ≤ ins.val ∨ r.2.2.val ≤ «end».val))
  · rintro ⟨head, prev, ins'⟩ ⟨hB, hins⟩
    simp only at hB hins
    simp only [slot.fx0_run_loop0_loop6.body]
    step*
  · exact ⟨hB, Or.inl (le_refl _)⟩)
@[local step]
theorem skip_loop_spec (input : Slice Std.U8) (out : Slice Std.U32) (nt p lim step : Std.Usize)
    (hdec : Dec input out nt.val p.val) (hlim : lim.val ≤ input.length) :
    slot.fx0_run_loop0_loop7 input out nt p lim step ⦃ fun r =>
      Dec input r.1 r.2.1.val r.2.2.val ∧ r.1.length = out.length ∧ p.val ≤ r.2.2.val ⦄ := by
  rw [slot.fx0_run_loop0_loop7]
  apply Std.loop.spec_decr_nat
    (measure := fun r => r.2.2.2.val)
    (inv := fun r => Dec input r.1 r.2.1.val r.2.2.1.val ∧ r.1.length = out.length ∧
      p.val ≤ r.2.2.1.val)
  · rintro ⟨out', nt', p', step'⟩ ⟨hdec', hlen', hp'⟩
    simp only at hdec' hlen' hp'
    simp only [slot.fx0_run_loop0_loop7.body]
    step*
  · exact ⟨hdec, rfl, le_refl _⟩
@[local step]
theorem tail_loop1_spec (input : Slice Std.U8) (out : Slice Std.U32) (n nt p : Std.Usize)
    (hn : n.val = input.length) (hdec : Dec input out nt.val p.val) :
    slot.fx0_run_loop1 input out n nt p ⦃ fun r => r.1.val ≤ input.length ∧
      r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := C12582! slot.fx0_run_loop1 slot.fx0_run_loop1.body
@[local step]
theorem tail_loop2_spec (input : Slice Std.U8) (out : Slice Std.U32) (n nt p : Std.Usize)
    (hn : n.val = input.length) (hdec : Dec input out nt.val p.val) :
    slot.fx0_run_loop2 input out n nt p ⦃ fun r => r.1.val ≤ input.length ∧
      r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := C12582! slot.fx0_run_loop2 slot.fx0_run_loop2.body
@[local step]
theorem tail_loop3_spec (input : Slice Std.U8) (out : Slice Std.U32) (n nt p : Std.Usize)
    (hn : n.val = input.length) (hdec : Dec input out nt.val p.val) :
    slot.fx0_run_loop3 input out n nt p ⦃ fun r => r.1.val ≤ input.length ∧
      r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := C12582! slot.fx0_run_loop3 slot.fx0_run_loop3.body
theorem numBits_ge : 32 ≤ System.Platform.numBits := (by
  rcases System.Platform.numBits_eq with h | h <;> omega)
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
      fuel ⦃ fun r => Dec input r.1 r.2.1.val r.2.2.val ∧ r.1.length = L ⦄ := by
  rw [slot.fx0_run_loop0]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  apply Std.loop.spec_decr_nat
    (measure := fun r => r.2.2.2.2.2.2.2.val)
    (inv := fun r => MainInv input L r.1 r.2.1.val r.2.2.1.val r.2.2.2.1 r.2.2.2.2.2.2.1.val)
  · rintro ⟨out, nt, p, head, prev, ins, miss, fuel⟩ hinv
    simp only at hinv
    have hinv' := hinv
    obtain ⟨hdec, hL, hB, hmiss⟩ := hinv'
    simp only [slot.fx0_run_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals first
      | exact FoundAt.real (by assumption) (by first | assumption | omega | scalar_tac)
      | exact HeadBound.mono (by assumption) (by first | assumption | omega | scalar_tac)
      | (refine ⟨MainInv.mk' (by assumption) (by first | assumption | omega | scalar_tac) (by assumption) (by first | assumption | omega | scalar_tac)
          (by first | assumption | omega | scalar_tac), by scalar_tac⟩)
      | (have := numBits_ge; scalar_tac)
  · exact hinv
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
theorem CntBound.init : CntBound (Std.Array.repeat 256#usize 0#u32) 0 := (by
  intro j hj
  rw [Std.Array.repeat_val, List.getElem!_eq_getElem?_getD,
    List.getElem?_replicate_of_lt (by simpa using hj)]
  rfl)
theorem CntBound.get {cnt : Array Std.U32 256#usize} {T : Nat} (h : CntBound cnt T)
    (a : Std.Usize) (x : Std.U32) (ha : a.val < cnt.val.length) (hx : x = cnt.val[a.val]) :
    x.val ≤ T := (by
  have := h a.val (by simpa using ha)
  rw [getElem!_pos cnt.val a.val ha, ← hx] at this
  exact this)
@[local step]
theorem cnt_index_spec (cnt : Array Std.U32 256#usize) (T : Nat) (h : CntBound cnt T)
    (i : Std.Usize) (hi : i.val < 256) :
    Std.Array.index_usize cnt i ⦃ fun x => x = cnt.val[i.val]! ∧ x.val ≤ T ⦄ := (by
  have hl : i.val < cnt.val.length := by simp; omega
  have := Std.Array.index_usize_spec cnt i (by simpa using hl)
  apply Std.WP.spec_mono this
  intro x hx
  refine ⟨by rw [getElem!_pos cnt.val i.val hl]; exact hx, CntBound.get h i x hl hx⟩)
theorem CntBound.update {cnt : Array Std.U32 256#usize} {T : Nat} (h : CntBound cnt T)
    (a : Std.Usize) (v : Std.U32) (hv : v.val ≤ T + 1) : CntBound (cnt.set a v) (T + 1) := (by
  intro j hj
  rw [Std.Array.set_val_eq]
  by_cases hja : a.val = j
  · subst hja
    have hlen : a.val < cnt.val.length := by simp; omega
    rw [List.getElem!_eq_getElem?_getD, List.getElem?_set_self hlen]
    exact hv
  · rw [List.getElem!_eq_getElem?_getD, List.getElem?_set_ne hja, ← List.getElem!_eq_getElem?_getD]
    exact le_trans (h j hj) (by omega))
theorem CntBound.step {cnt a : Array Std.U32 256#usize} {T : Nat} {x : Std.Usize}
    {v tot1 : Std.U32} (hc : CntBound cnt T) (ha : a = cnt.set x v) (hv : v.val ≤ T + 1)
    (ht1 : tot1.val = T + 1) : CntBound a tot1.val := (by
  rw [ha, ht1]
  exact CntBound.update hc x v hv)
theorem CntBound.mono {cnt : Array Std.U32 256#usize} {T T' : Nat} (h : CntBound cnt T)
    (hT : T ≤ T') : CntBound cnt T' := fun j hj => le_trans (h j hj) hT
@[local step]
theorem lift_spec {α : Type} (x : α) : lift x ⦃ fun y => y = x ⦄ := by
  simp [lift]
@[local step]
theorem run_spec (H W TD SL : Std.Usize) (input : Slice Std.U8) (out : Slice Std.U32) (cls : Std.Usize)
    (hlen : input.length ≤ out.length) (hH : 0 < H.val) (hW : 0 < W.val) :
    slot.fx0_run H W TD SL input out cls ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧
      LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
  rw [slot.fx0_run]
  step*
  repeat' (split <;> step*)
  all_goals first
    | exact Dec.init input out hlen
    | exact HeadBound.init _
end FX0
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
 · rw [getElem!_pos _ _ (by first | assumption | omega | scalar_tac), getElem!_pos _ _ (by first | assumption | omega | scalar_tac), ← i1_post, ← i_post]
   symm; assumption
 · rw [show b.val+1=i4.val by scalar_tac,show a.val+1=i2.val by scalar_tac]
   rw [getElem!_pos _ _ (by first | assumption | omega | scalar_tac), getElem!_pos _ _ (by first | assumption | omega | scalar_tac), ← i5_post, ← i3_post]
   symm; assumption
 · rw [show b.val+2=i8.val by scalar_tac,show a.val+2=i6.val by scalar_tac]
   rw [getElem!_pos _ _ (by first | assumption | omega | scalar_tac), getElem!_pos _ _ (by first | assumption | omega | scalar_tac), ← i9_post, ← i7_post]
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
   exact emit_match input out ntok pos.val d.val 3 i3 hdec (by first | assumption | omega | scalar_tac)
    hd1 hdpos hdmax (by decide) (by decide) hend hm htok
 · apply Std.WP.spec_mono (EO.EA.emit_lits_spec input out pos 2#usize ntok hout (by first | assumption | omega | scalar_tac) hntok hdec)
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
theorem v29z (input : Slice Std.U8) (out0 : Slice Std.U32) (nt0 pos0 : Std.Usize)
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
 exact v29z input out nt0 pos0 hlen hp hnt hd
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
set_option hygiene false in
local notation "C12598!" => (by
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
theorem tp_lift_spec {α : Type} (x : α) : lift x ⦃ fun y => y = x ⦄ := (by
  simp [lift, WP.spec_ok])
theorem tp_numBits_ge : 32 ≤ System.Platform.numBits := (by
  cases System.Platform.numBits_eq <;> simp [*])
@[local scalar_tac System.Platform.numBits]
theorem tp_numBits_ge' : 32 ≤ System.Platform.numBits := tp_numBits_ge
end TinyPath
@[irreducible] def word8 (input : Slice Std.U8) (p : Nat) : Nat :=
  (input.val[p]!).val * 2^56 + (input.val[p + 1]!).val * 2^48 + (input.val[p + 2]!).val * 2^40
    + (input.val[p + 3]!).val * 2^32 + (input.val[p + 4]!).val * 2^24
    + (input.val[p + 5]!).val * 2^16 + (input.val[p + 6]!).val * 2^8 + (input.val[p + 7]!).val
theorem u8_lt (x : Std.U8) : x.val < 256 := by scalar_tac
theorem word8_digit (input : Slice Std.U8) (p k : Nat) (hk : k < 8) :
    (input.val[p + k]!).val = word8 input p / 256 ^ (7 - k) % 256 := (by
  have := u8_lt (input.val[p]!); have := u8_lt (input.val[p+1]!)
  have := u8_lt (input.val[p+2]!); have := u8_lt (input.val[p+3]!)
  have := u8_lt (input.val[p+4]!); have := u8_lt (input.val[p+5]!)
  have := u8_lt (input.val[p+6]!); have := u8_lt (input.val[p+7]!)
  simp only [word8]
  rcases (show k = 0 ∨ k = 1 ∨ k = 2 ∨ k = 3 ∨ k = 4 ∨ k = 5 ∨ k = 6 ∨ k = 7 by omega) with
    rfl | rfl | rfl | rfl | rfl | rfl | rfl | rfl <;> simp only [Nat.add_zero, Nat.pow_zero, Nat.pow_succ, Nat.one_mul,
    Nat.sub_self, Nat.reduceSub] <;> omega)
theorem word8_prefix (input : Slice Std.U8) (a b d : Nat) (hd : d ≤ 8)
    (h : word8 input a / 2 ^ (64 - 8 * d) = word8 input b / 2 ^ (64 - 8 * d)) :
    ∀ k, k < d → input.val[b + k]! = input.val[a + k]! := (by
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
theorem Matches.add_prefix {input : Slice Std.U8} {a b l d : Nat} (h : Matches input a b l)
    (hd : d ≤ 8)
    (hw : word8 input (a + l) / 2 ^ (64 - 8 * d) = word8 input (b + l) / 2 ^ (64 - 8 * d)) :
    Matches input a b (l + d) := (by
  intro k hk
  by_cases hkl : k < l
  · exact h k hkl
  · have := word8_prefix input (a + l) (b + l) d hd hw (k - l) (by omega)
    rw [show b + l + (k - l) = b + k by omega, show a + l + (k - l) = a + k by omega] at this
    exact this)
theorem or_eq_add_of_mod {x t : Nat} (m : Nat) (hx : x % 2 ^ m = 0) (ht : t < 2 ^ m) :
    x ||| t = x + t := (by
  have h := Nat.two_pow_add_eq_or_of_lt ht (x / 2 ^ m)
  have hx' : 2 ^ m * (x / 2 ^ m) = x := by
    have := Nat.div_add_mod x (2 ^ m); omega
  rw [hx'] at h
  exact h.symm)
theorem shl_byte {x : Nat} (k : Nat) (hx : x < 256) (hk : k ≤ 56) :
    x <<< k % U64.size = x * 2 ^ k := (by
  rw [Nat.shiftLeft_eq, U64.size_def]
  apply Nat.mod_eq_of_lt
  have : 2 ^ k ≤ 2 ^ 56 := Nat.pow_le_pow_right (by norm_num) hk
  have : x * 2 ^ k < 256 * 2 ^ 56 := by
    calc x * 2 ^ k < 256 * 2 ^ k := by
          apply Nat.mul_lt_mul_of_pos_right hx (Nat.two_pow_pos _)
      _ ≤ 256 * 2 ^ 56 := Nat.mul_le_mul_left _ this
  simp only [U64.numBits] at *
  omega)
theorem be8_nat {a b c d e f g h : Nat} (ha : a < 256) (hb : b < 256) (hc : c < 256)
    (hd : d < 256) (he : e < 256) (hf : f < 256) (hg : g < 256) (hh : h < 256) :
    (a <<< 56 % U64.size ||| b <<< 48 % U64.size ||| c <<< 40 % U64.size |||
      d <<< 32 % U64.size ||| e <<< 24 % U64.size ||| f <<< 16 % U64.size |||
      g <<< 8 % U64.size ||| h) =
    a * 2^56 + b * 2^48 + c * 2^40 + d * 2^32 + e * 2^24 + f * 2^16 + g * 2^8 + h := C12529!
@[local step]
theorem be8_spec (s : Slice Std.U8) (i : Std.Usize) (h : i.val + 8 ≤ s.length) :
    slot.pc_be8 s i ⦃ fun v => v.val = word8 s i.val ⦄ := (by
  rw [slot.pc_be8]
  step*
  simp only [← getElem!_pos] at *
  simp_all only [UScalar.val_or, U8.cast_U64_val_eq]
  rw [be8_nat (u8_lt _) (u8_lt _) (u8_lt _) (u8_lt _) (u8_lt _) (u8_lt _) (u8_lt _) (u8_lt _)]
  simp only [word8])
theorem nat_xor_eq_zero {a b : Nat} (h : a ^^^ b = 0) : a = b := (by
  have : a ^^^ (a ^^^ b) = b := by rw [← Nat.xor_assoc, Nat.xor_self, Nat.zero_xor]
  rw [h, Nat.xor_zero] at this; exact this)
theorem div_eq_of_xor_lt {x y m : Nat} (hz : x ^^^ y < 2 ^ m) : x / 2 ^ m = y / 2 ^ m := (by
  have h : (x ^^^ y) >>> m = 0 := by rw [Nat.shiftRight_eq_div_pow]; exact Nat.div_eq_of_lt hz
  rw [Nat.shiftRight_xor_distrib] at h
  have := nat_xor_eq_zero h
  simpa [Nat.shiftRight_eq_div_pow] using this)
theorem lt_pow_leadingZeros (z : BitVec 64) :
    z.toNat < 2 ^ (64 - 8 * (BitVec.leadingZeros z / 8)) := (by
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
theorem leadingZeros_lt_of_ne (z : BitVec 64) (h : z ≠ 0) : BitVec.leadingZeros z < 64 := (by
  unfold BitVec.leadingZeros
  simp only [h, if_false]
  omega)
@[local step]
theorem lz_spec (x : Std.U64) :
    lift (core.num.U64.leading_zeros x) ⦃ fun r => r = core.num.U64.leading_zeros x ∧ r.val ≤ 64 ⦄ := (by
  simp only [lift, Std.WP.spec_ok, true_and]
  have hle : BitVec.leadingZeros x.bv ≤ 64 := by unfold BitVec.leadingZeros; split <;> omega
  simp only [core.num.U64.leading_zeros, UScalar.val, UScalarTy.U32_numBits_eq,
    BitVec.natCast_eq_ofNat, BitVec.toNat_ofNat, Nat.reducePow]
  omega)
theorem lz_val (x : Std.U64) :
    (core.num.U64.leading_zeros x).val = BitVec.leadingZeros x.bv := (by
  have hle : BitVec.leadingZeros x.bv ≤ 64 := by unfold BitVec.leadingZeros; split <;> omega
  simp only [core.num.U64.leading_zeros, UScalar.val, UScalarTy.U32_numBits_eq,
    BitVec.natCast_eq_ofNat, BitVec.toNat_ofNat, Nat.reducePow]
  omega)
theorem Matches.word_lz {input : Slice Std.U8} {a b k : Nat} {pa pb r k1 : Std.Usize}
    {x y z : Std.U64} {lz q : Std.U32}
    (h : Matches input a b k) (hpa : pa.val = a + k) (hpb : pb.val = b + k)
    (hx : x.val = word8 input pa.val) (hy : y.val = word8 input pb.val)
    (hz : z.val = (x ^^^ y).val) (hz0 : ¬z = 0#u64) (hlz : lz = core.num.U64.leading_zeros z)
    (hq : q.val = lz.val / 8) (hr : r = UScalar.cast .Usize q) (hk1 : k1.val = k + r.val) :
    Matches input a b k1.val ∧ k1.val < k + 8 := (by
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
theorem Matches.word_zero {input : Slice Std.U8} {a b k : Nat} {pa pb k1 : Std.Usize}
    {x y z : Std.U64}
    (h : Matches input a b k) (hpa : pa.val = a + k) (hpb : pb.val = b + k)
    (hx : x.val = word8 input pa.val) (hy : y.val = word8 input pb.val)
    (hz : z.val = (x ^^^ y).val) (hz0 : z = 0#u64) (hk1 : k1.val = k + 8) :
    Matches input a b k1.val := (by
  have hxy : x.val = y.val := by
    apply nat_xor_eq_zero
    rw [← UScalar.val_xor, ← hz, hz0]; rfl
  rw [hpa] at hx; rw [hpb] at hy
  rw [hk1]
  apply Matches.add_prefix h (le_refl 8)
  rw [← hx, ← hy, hxy])
theorem Matches.byte' {input : Slice Std.U8} {a b l : Nat} {pa pb l1 : Std.Usize}
    {x y : Std.U8} (h : Matches input a b l) (hpa : pa.val = a + l) (hpb : pb.val = b + l)
    (hpa' : pa.val < input.val.length) (hpb' : pb.val < input.val.length)
    (hx : x = input.val[pa.val]) (hy : y = input.val[pb.val]) (hxy : x = y)
    (hl1 : l1.val = l + 1) : Matches input a b l1.val := (by
  rw [hl1]
  apply LZ77.Matches.succ h
  rw [← hpa, ← hpb, getElem!_pos input.val pa.val hpa', getElem!_pos input.val pb.val hpb',
    ← hx, ← hy, hxy])
theorem wadd_val {x y z : Std.Usize} (hz : z = core.num.Usize.wrapping_add x y)
    (hb : x.val + y.val ≤ Std.Usize.max) : z.val = x.val + y.val := (by
  have hlt : x.val + y.val < Usize.size := by scalar_tac
  rw [hz, core.num.Usize.wrapping_add_val_eq, UScalar.size_UScalarTyUsize, Nat.mod_eq_of_lt hlt])
theorem wadd_le {x y z : Std.Usize} {m n : Nat} (hz : z = core.num.Usize.wrapping_add x y)
    (h : x.val + y.val + m ≤ n) (hn : n ≤ Std.Usize.max) : z.val + m ≤ n := (by
  rw [wadd_val hz (by omega)]; exact h)
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
    Matches input a b k1.val ∧ k1.val ≤ k + 8 := (by
  have hle : BitVec.leadingZeros z.bv ≤ 64 := by unfold BitVec.leadingZeros; split <;> omega
  have hrv : r.val = BitVec.leadingZeros z.bv / 8 := by
    rw [hr, U32.cast_Usize_val_eq, hq, hlz, lz_val]
  refine ⟨?_, by omega⟩
  rw [hk1, hrv]
  apply Matches.add_prefix h (by omega)
  apply div_eq_of_xor_lt
  rw [← hz]
  exact lt_pow_leadingZeros z.bv)
theorem Matches.xz {input : Slice Std.U8} {a b : Nat} {z : Std.U64}
    (hz : z.val = word8 input a ^^^ word8 input b) (hz0 : z = 0#u64) :
    Matches input a b 8 := (by
  have hv : word8 input a ^^^ word8 input b = 0 := by rw [← hz, hz0]; rfl
  have hab := nat_xor_eq_zero hv
  have := Matches.add_prefix (LZ77.Matches.zero input a b) (le_refl 8)
    (by simp only [Nat.add_zero]; rw [hab])
  simpa using this)
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
    Matches input a.val b.val k1.val ∧ k1.val ≤ k.val + 8 := (by
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  rw [wadd_val hpa (by omega), wadd_val hpb (by omega)] at hz
  exact Matches.lz_any h hz hlz hq hr hk1)
theorem Matches.xw_zero {input : Slice Std.U8} {a b k pa pb k1 : Std.Usize} {z : Std.U64}
    (h : Matches input a.val b.val k.val)
    (hpa : pa = core.num.Usize.wrapping_add a k) (hpb : pb = core.num.Usize.wrapping_add b k)
    (hab : a.val + k.val + 8 ≤ input.length ∧ b.val + k.val + 8 ≤ input.length)
    (hz : z.val = word8 input pa.val ^^^ word8 input pb.val) (hz0 : z = 0#u64)
    (hk1 : k1.val = k.val + 8) : Matches input a.val b.val k1.val := (by
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
theorem Matches.word_eq {input : Slice Std.U8} {a b k : Nat} {pa pb k1 : Std.Usize}
    {x y : Std.U64}
    (h : Matches input a b k) (hpa : pa.val = a + k) (hpb : pb.val = b + k)
    (hx : x.val = word8 input pa.val) (hy : y.val = word8 input pb.val)
    (hxy : x = y) (hk1 : k1.val = k + 8) :
    Matches input a b k1.val := (by
  rw [hpa] at hx; rw [hpb] at hy
  rw [hk1]
  apply Matches.add_prefix h (le_refl 8)
  rw [← hx, ← hy, hxy])
theorem same_loop0_spec (s : Slice Std.U8) (a b len k ok : Std.Usize)
    (ha : a.val + len.val ≤ s.length) (hb : b.val + len.val ≤ s.length) (hlen : len.val ≤ 258)
    (hk : k.val ≤ len.val) (hm : Matches s a.val b.val k.val) :
    slot.pc_same_loop0 s a b len k ok ⦃ fun r =>
      r.1.val ≤ len.val ∧ Matches s a.val b.val r.1.val ∧ (r.2.val = 1 → len.val < r.1.val + 8) ⦄ := (by
  rw [slot.pc_same_loop0]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  apply Std.loop.spec_decr_nat
    (measure := fun r => len.val - r.1.val + r.2.val)
    (inv := fun r => r.1.val ≤ len.val ∧ Matches s a.val b.val r.1.val)
  · rintro ⟨k, ok⟩ ⟨hk, hm⟩
    simp only at hk hm
    simp only [slot.pc_same_loop0.body]
    step*
    all_goals first
      | scalar_tac
      | (refine ⟨by scalar_tac, Matches.word_eq hm (by assumption) (by assumption)
          (by assumption) (by assumption) (by assumption) (by first | assumption | omega | scalar_tac), by scalar_tac⟩)
  · exact ⟨hk, hm⟩)
@[local step]
theorem same_loop1_spec (s : Slice Std.U8) (a b len k ok : Std.Usize)
    (ha : a.val + len.val ≤ s.length) (hb : b.val + len.val ≤ s.length)
    (hk : k.val ≤ len.val) (hm : Matches s a.val b.val k.val) :
    slot.pc_same_loop1 s a b len k ok ⦃ fun r => r.val = 1 → Matches s a.val b.val len.val ⦄ := (by
  rw [slot.pc_same_loop1]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  apply Std.loop.spec_decr_nat
    (measure := fun r => len.val - r.1.val + r.2.val)
    (inv := fun r => r.1.val ≤ len.val ∧ Matches s a.val b.val r.1.val)
  · rintro ⟨k, ok⟩ ⟨hk, hm⟩
    simp only at hk hm
    simp only [slot.pc_same_loop1.body]
    step*
    all_goals first
      | scalar_tac
      | (refine ⟨by scalar_tac, Matches.byte' hm (by assumption) (by assumption) (by first | assumption | omega | scalar_tac)
          (by first | assumption | omega | scalar_tac) (by assumption) (by assumption) (by assumption) (by assumption),
          by scalar_tac⟩)
  · exact ⟨hk, hm⟩)
@[local step]
theorem same_loop2_spec (s : Slice Std.U8) (a b len k ok : Std.Usize)
    (ha : a.val + len.val ≤ s.length) (hb : b.val + len.val ≤ s.length)
    (hk : k.val ≤ len.val) (hm : Matches s a.val b.val k.val) :
    slot.pc_same_loop2 s a b len k ok ⦃ fun r => r.val = 1 → Matches s a.val b.val len.val ⦄ := (by
  rw [slot.pc_same_loop2]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  apply Std.loop.spec_decr_nat
    (measure := fun r => len.val - r.1.val + r.2.val)
    (inv := fun r => r.1.val ≤ len.val ∧ Matches s a.val b.val r.1.val)
  · rintro ⟨k, ok⟩ ⟨hk, hm⟩
    simp only at hk hm
    simp only [slot.pc_same_loop2.body]
    step*
    all_goals first
      | scalar_tac
      | (refine ⟨by scalar_tac, Matches.byte' hm (by assumption) (by assumption) (by first | assumption | omega | scalar_tac)
          (by first | assumption | omega | scalar_tac) (by assumption) (by assumption) (by assumption) (by assumption),
          by scalar_tac⟩)
  · exact ⟨hk, hm⟩)
theorem Matches.mask {input : Slice Std.U8} {a b k len : Nat} {pa pb : Std.Usize}
    {x y z w : Std.U64} {sh : Std.U32}
    (h : Matches input a b k) (hpa : pa.val = a + k) (hpb : pb.val = b + k)
    (hx : x.val = word8 input pa.val) (hy : y.val = word8 input pb.val)
    (hz : z.val = (x ^^^ y).val) (hw : w.val = z.val >>> sh.val) (hw0 : ¬(w != 0#u64) = true)
    (hsh : sh.val = 64 - 8 * (len - k)) (hk : k < len) (hlen : len < k + 8) :
    Matches input a b len := (by
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
@[local step]
theorem same_spec (s : Slice Std.U8) (a b len : Std.Usize)
    (ha : a.val + len.val ≤ s.length) (hb : b.val + len.val ≤ s.length) (hlen : len.val ≤ 258)
    (ha8 : a.val + len.val + 7 ≤ Std.Usize.max) (hb8 : b.val + len.val + 7 ≤ Std.Usize.max) :
    slot.pc_same s a b len ⦃ fun r => r.val = 1 → Matches s a.val b.val len.val ⦄ := (by
  rw [slot.pc_same]
  apply Std.WP.spec_bind (same_loop0_spec s a b len 0#usize 1#usize ha hb hlen (by simp)
    (LZ77.Matches.zero s a.val b.val))
  rintro ⟨k, ok⟩ ⟨hk, hm, hok⟩
  simp only at hk hm hok
  step*
  intro _
  exact Matches.mask hm (by assumption) (by assumption) (by assumption) (by assumption)
    (by assumption) (by assumption) (by assumption) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac)
    (by first | assumption | omega | scalar_tac))
theorem lz32_le (x : Std.U32) (k : Nat) (hk : k < 32) (hx : 2 ^ k ≤ x.val) :
    (core.num.U32.leading_zeros x).val ≤ 31 - k := C12546!
@[local step]
theorem lz32_spec (x : Std.U32) :
    lift (core.num.U32.leading_zeros x) ⦃ fun r => r = core.num.U32.leading_zeros x ∧
      (4 ≤ x.val → r.val ≤ 29) ∧ (8 ≤ x.val → r.val ≤ 28) ⦄ := (by
  simp only [lift, Std.WP.spec_ok, true_and]
  exact ⟨fun h => lz32_le x 2 (by norm_num) (by simpa using h),
    fun h => lz32_le x 3 (by norm_num) (by simpa using h)⟩)
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
theorem HeadBound.init (N : Std.Usize) : HeadBound (Std.Array.repeat N 0#u32) 0 := (by
  intro j hj
  rw [Std.Array.repeat_val] at hj ⊢
  rw [List.getElem!_eq_getElem?_getD, List.getElem?_replicate_of_lt (by simpa using hj)]
  rfl)
theorem HeadBound.set {N : Std.Usize} {head : Array Std.U32 N} {B : Nat} (h : HeadBound head B)
    (a : Std.Usize) (v : Std.U32) (hv : v.val ≤ B) : HeadBound (head.set a v) B := (by
  intro j hj
  rw [Std.Array.set_val_eq] at hj ⊢
  rw [List.length_set] at hj
  by_cases hja : a.val = j
  · subst hja
    rw [List.getElem!_eq_getElem?_getD, List.getElem?_set_self hj]
    exact hv
  · rw [List.getElem!_eq_getElem?_getD, List.getElem?_set_ne hja, ← List.getElem!_eq_getElem?_getD]
    exact h j hj)
theorem HeadBound.update {N : Std.Usize} {head head1 : Array Std.U32 N} {B : Nat}
    {a i : Std.Usize} {v : Std.U32} (h : HeadBound head B) (hv : v = UScalar.cast .U32 i)
    (hi : i.val ≤ B) (h1 : head1 = head.set a v) : HeadBound head1 B := (by
  subst h1
  apply HeadBound.set h a v
  rw [hv]
  have : (UScalar.cast .U32 i).val = i.val % 2 ^ 32 := by
    simp only [UScalar.cast_val_eq, UScalarTy.U32_numBits_eq]
  rw [this]
  exact le_trans (Nat.mod_le _ _) hi)
theorem HeadBound.get {N : Std.Usize} {head : Array Std.U32 N} {B : Nat} (h : HeadBound head B)
    (a : Std.Usize) (x : Std.U32) (ha : a.val < head.val.length) (hx : x = head.val[a.val]) :
    x.val ≤ B := (by
  have := h a.val ha
  rw [getElem!_pos head.val a.val ha, ← hx] at this
  exact this)
theorem cast_usize_le {x : Std.U32} {y : Std.Usize} {B : Nat} (h : y = UScalar.cast .Usize x)
    (hx : x.val ≤ B) : y.val ≤ B := (by
  rw [h, U32.cast_Usize_val_eq]; exact hx)
@[local step]
theorem be4_spec (s : Slice Std.U8) (i : Std.Usize) (hi : i.val + 4 ≤ Std.Usize.max) :
    slot.pc_be4 s i ⦃ fun _ => True ⦄ := by
  rw [slot.pc_be4]
  step*
def Cand (s : Slice Std.U8) (p cap best bd : Nat) : Prop :=
  bd = 0 ∨ (1 ≤ bd ∧ bd ≤ 32768 ∧ bd ≤ p ∧ best ≤ cap ∧ Matches s (p - bd) p best)
theorem dist_of_wrapping {p c d i : Std.Usize} (hc : c.val ≤ p.val)
    (hd : d = core.num.Usize.wrapping_sub p c) (hi : i = core.num.Usize.wrapping_sub d 1#usize)
    (hlt : i < 32768#usize) : d.val = p.val - c.val ∧ 1 ≤ d.val ∧ d.val ≤ 32768 := C12553!
theorem Cand.of_common {s : Slice Std.U8} {p c d i l cap : Std.Usize} (hc : c.val ≤ p.val)
    (hd : d = core.num.Usize.wrapping_sub p c) (hi : i = core.num.Usize.wrapping_sub d 1#usize)
    (hlt : i < 32768#usize) (hl : l.val ≤ cap.val) (hm : Matches s c.val p.val l.val) :
    Cand s p.val cap.val l.val d.val := (by
  obtain ⟨hdv, hd1, hd2⟩ := dist_of_wrapping hc hd hi hlt
  refine Or.inr ⟨hd1, hd2, by omega, hl, ?_⟩
  rw [show p.val - d.val = c.val by omega]
  exact hm)
def MatchAt (s : Slice Std.U8) (p l d : Nat) : Prop :=
  3 ≤ l ∧ l ≤ 258 ∧ p + l ≤ s.length ∧ 1 ≤ d ∧ d ≤ 32768 ∧ d ≤ p ∧ Matches s (p - d) p l
def FoundAt (s : Slice Std.U8) (p l d : Nat) : Prop := l < 3 ∨ MatchAt s p l d
theorem FoundAt.of_cand {s : Slice Std.U8} {p cap : Nat} {l d : Std.Usize}
    (hc : Cand s p cap l.val d.val) (hd : ¬d = 0#usize) (hcap : cap ≤ 258)
    (hpl : p + l.val ≤ s.length) : FoundAt s p l.val d.val := (by
  have hd' : d.val ≠ 0 := by intro h; apply hd; exact UScalar.eq_of_val_eq (by simp [h])
  rcases hc with h0 | ⟨hd1, hd2, hdp, hl, hm⟩
  · exact absurd h0 hd'
  · rcases Nat.lt_or_ge l.val 3 with h3 | h3
    · exact Or.inl h3
    · exact Or.inr ⟨h3, by omega, hpl, hd1, hd2, hdp, hm⟩)
theorem Cand.len_le {s : Slice Std.U8} {p cap : Nat} {l d : Std.Usize}
    (hc : Cand s p cap l.val d.val) (hd : ¬d = 0#usize) (hcap : cap ≤ 258) : l.val ≤ 258 := (by
  have hd' : d.val ≠ 0 := by intro h; apply hd; exact UScalar.eq_of_val_eq (by simp [h])
  rcases hc with h0 | ⟨_, _, _, hl, _⟩
  · exact absurd h0 hd'
  · omega)
theorem Cand.dist_le {s : Slice Std.U8} {p cap l d : Nat} (hc : Cand s p cap l d) :
    d ≤ 32768 := (by
  rcases hc with h0 | ⟨_, hd, _⟩ <;> omega)
theorem FoundAt.none (s : Slice Std.U8) (p : Nat) : FoundAt s p (0#usize).val (0#usize).val :=
  Or.inl (by simp)
theorem FoundAt.real {s : Slice Std.U8} {p l d : Nat} (hf : FoundAt s p l d) (h3 : 3 ≤ l) :
    MatchAt s p l d := (by
  rcases hf with h | h
  · omega
  · exact h)
theorem copyN_take_prefix (acc : List Nat) (d : Nat) :
    ∀ n, (copyN acc d n).take acc.length = acc := (by
  intro n
  induction n with
  | zero => simp [copyN]
  | succ m ih =>
    simp only [copyN]
    rw [List.take_append_of_le_length (by simp)]
    exact ih)
theorem foldlM_emit_length : ∀ (ts : List Nat) (init acc : List Nat),
    ts.foldlM emit init = some acc → init.length + ts.length ≤ acc.length := C12560!
theorem decode_length_le {ts acc : List Nat} (h : decode ts = some acc) :
    ts.length ≤ acc.length := (by
  have := foldlM_emit_length ts [] acc h
  simpa using this)
theorem decode_pop_lit {ts : List Nat} {t : Nat} {inp : List Nat} {p : Nat}
    (hp : p ≤ inp.length) (hd : decode (ts ++ [t]) = some (inp.take p)) (ht : t < 256) :
    1 ≤ p ∧ decode ts = some (inp.take (p - 1)) := (by
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
theorem decode_pop_match {ts : List Nat} {t : Nat} {inp : List Nat} {p : Nat}
    (hp : p ≤ inp.length) (hd : decode (ts ++ [t]) = some (inp.take p)) (ht : 256 ≤ t) :
    tokLen t ≤ p ∧ decode ts = some (inp.take (p - tokLen t)) := C12563!
theorem toks_pop (out : Slice Std.U32) (nt : Nat) (h0 : 0 < nt) (hle : nt ≤ out.length) :
    toks out nt = toks out (nt - 1) ++ [(out.val[nt - 1]!).val] := (by
  have hlt : nt - 1 < out.val.length := by
    have : out.length = out.val.length := rfl
    omega
  simp only [toks]
  conv_lhs => rw [show nt = (nt - 1) + 1 by omega]
  rw [List.take_add_one, List.getElem?_eq_getElem hlt, Option.toList_some, List.map_append]
  simp [getElem!_pos out.val (nt - 1) hlt])
theorem toks_length (out : Slice Std.U32) (nt : Nat) (h : nt ≤ out.length) :
    (toks out nt).length = nt := (by
  simp only [toks, List.length_map, List.length_take]
  have : out.length = out.val.length := rfl
  omega)
def Dec (s : Slice Std.U8) (out : Slice Std.U32) (nt p : Nat) : Prop :=
  p ≤ s.length ∧ nt ≤ p ∧ s.length ≤ out.length ∧
    decode (toks out nt) = some ((bytes s).take p)
theorem Dec.init (input : Slice Std.U8) (out : Slice Std.U32) (h : input.length ≤ out.length) :
    Dec input out (0#usize).val (0#usize).val :=
  ⟨by simp, by simp, h, by simp [toks, LZ77.decode]⟩
theorem Dec.lit {s : Slice Std.U8} {out : Slice Std.U32} {nt p : Nat} (h : Dec s out nt p)
    (hp : p < s.length) (ntU : Std.Usize) (hnt : ntU.val = nt) (v : Std.U32)
    (hv : v.val = (s.val[p]!).val) :
    Dec s (out.set ntU v) (nt + 1) (p + 1) := (by
  obtain ⟨hps, hntp, hso, hde⟩ := h
  have hntl : ntU.val < out.length := by omega
  refine ⟨by omega, by omega, by rw [Std.Slice.set_length]; exact hso, ?_⟩
  rw [← hnt]
  refine emit_lit s out ntU p v (by rw [hnt]; exact hde) hp hntl ?_
  have hpl : p < s.val.length := hp
  rw [hv, bytes_getElem! s p hpl, getElem!_pos s.val p hpl])
theorem Dec.match {s : Slice Std.U8} {out : Slice Std.U32} {nt p l d : Nat} (h : Dec s out nt p)
    (hm : MatchAt s p l d) (ntU : Std.Usize) (hnt : ntU.val = nt) (v : Std.U32)
    (hv : v.val = LZ77.mkMatch d l) :
    Dec s (out.set ntU v) (nt + 1) (p + l) := (by
  obtain ⟨hps, hntp, hso, hde⟩ := h
  obtain ⟨h3, h258, hpl, hd1, hd32, hdp, hmm⟩ := hm
  have hntl : ntU.val < out.length := by omega
  refine ⟨by omega, by omega, by rw [Std.Slice.set_length]; exact hso, ?_⟩
  rw [← hnt]
  exact emit_match s out ntU p d l v (by rw [hnt]; exact hde) hntl hd1 hdp hd32 h3 h258 hpl hmm hv)
theorem Dec.pop_lit {s : Slice Std.U8} {out : Slice Std.U32} {nt p : Nat} (h : Dec s out nt p)
    (h0 : 0 < nt) (hle : nt ≤ out.length) (ht : (out.val[nt - 1]!).val < 256) :
    1 ≤ p ∧ Dec s out (nt - 1) (p - 1) := (by
  obtain ⟨hps, hntp, hso, hde⟩ := h
  rw [toks_pop out nt h0 hle] at hde
  obtain ⟨hp1, hde'⟩ := decode_pop_lit (by simpa using hps) hde ht
  exact ⟨hp1, by omega, by omega, hso, hde'⟩)
theorem Dec.pop_match {s : Slice Std.U8} {out : Slice Std.U32} {nt p : Nat} (h : Dec s out nt p)
    (h0 : 0 < nt) (hle : nt ≤ out.length) (ht : 256 ≤ (out.val[nt - 1]!).val) :
    tokLen (out.val[nt - 1]!).val ≤ p ∧
      Dec s out (nt - 1) (p - tokLen (out.val[nt - 1]!).val) := (by
  obtain ⟨hps, hntp, hso, hde⟩ := h
  rw [toks_pop out nt h0 hle] at hde
  obtain ⟨hw, hde'⟩ := decode_pop_match (by simpa using hps) hde ht
  have hlen := decode_length_le hde'
  rw [toks_length out (nt - 1) (by omega), List.length_take, bytes_length] at hlen
  exact ⟨hw, by omega, by omega, hso, hde'⟩)
theorem Dec.done {s : Slice Std.U8} {out : Slice Std.U32} {nt p : Nat} (h : Dec s out nt p)
    (hp : s.length ≤ p) : nt ≤ s.length ∧ LZ77.Valid (bytes s) (toks out nt) := (by
  obtain ⟨hps, hntp, hso, hde⟩ := h
  refine ⟨by omega, ?_⟩
  unfold LZ77.Valid
  rw [hde, show p = s.length by omega, ← bytes_length, List.take_length])
theorem Dec.lit_step {s : Slice Std.U8} {out out1 : Slice Std.U32} {ntU nt1 pU : Std.Usize}
    {b : Std.U8} {v : Std.U32} (h : Dec s out ntU.val pU.val) (hp : pU.val < s.val.length)
    (hb : b = s.val[pU.val]) (hv : v = UScalar.cast .U32 b) (hout1 : out1 = out.set ntU v)
    (hnt1 : nt1.val = ntU.val + 1) :
    nt1.val = ntU.val + 1 ∧ out1.length = out.length ∧ Dec s out1 nt1.val (pU.val + 1) := (by
  subst hout1
  refine ⟨hnt1, Std.Slice.set_length .., ?_⟩
  rw [hnt1]
  exact Dec.lit h hp ntU rfl v (by rw [hv, U8.cast_U32_val_eq, hb, getElem!_pos s.val pU.val hp]))
@[local step]
theorem put_lit_spec (s : Slice Std.U8) (out : Slice Std.U32) (nt p : Std.Usize)
    (hdec : Dec s out nt.val p.val) (hp : p.val < s.length) :
    slot.pc_put_lit s out nt p ⦃ fun r => r.1.val = nt.val + 1 ∧ r.2.length = out.length ∧
      Dec s r.2 r.1.val (p.val + 1) ⦄ := by
  rw [slot.pc_put_lit]
  step*
  exact Dec.lit_step hdec (by first | assumption | omega | scalar_tac) (by assumption) (by assumption) (by assumption)
    (by assumption)
theorem Dec.match_step {s : Slice Std.U8} {out out1 : Slice Std.U32} {ntU nt1 pU dU lU e : Std.Usize}
    {v : Std.U32} (h : Dec s out ntU.val pU.val) (hm : MatchAt s pU.val lU.val dU.val)
    (hout1 : out1 = out.set ntU v) (hv : v.val = LZ77.mkMatch dU.val lU.val)
    (hnt1 : nt1.val = ntU.val + 1) (he : e.val = pU.val + lU.val) :
    nt1.val = ntU.val + 1 ∧ e.val = pU.val + lU.val ∧ out1.length = out.length ∧
      Dec s out1 nt1.val e.val := (by
  subst hout1
  refine ⟨hnt1, he, Std.Slice.set_length .., ?_⟩
  rw [hnt1, he]
  exact Dec.match h hm ntU rfl v hv)
@[local step]
theorem put_match_spec (s : Slice Std.U8) (out : Slice Std.U32) (nt p d l : Std.Usize)
    (hdec : Dec s out nt.val p.val) (hm : MatchAt s p.val l.val d.val) :
    slot.pc_put_match s out nt p d l ⦃ fun r => r.1.1.val = nt.val + 1 ∧
      r.1.2.val = p.val + l.val ∧ r.2.length = out.length ∧ Dec s r.2 r.1.1.val r.1.2.val ⦄ := (by
  rw [slot.pc_put_match]
  have hm' := hm
  obtain ⟨h3, h258, hpl, hd1, hd32, hdp, _⟩ := hm'
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  have hsize : Std.Usize.max + 1 = Std.Usize.size := by
    simp only [Std.Usize.max, Std.Usize.size]
    have : 0 < (2 : Nat) ^ Std.Usize.numBits := by positivity
    omega
  have hntp := hdec.2.1
  have hntmax : nt.val + 1 ≤ Std.Usize.max := by omega
  have hemax : p.val + l.val ≤ Std.Usize.max := by omega
  have hdsub : (core.num.Usize.wrapping_sub d 1#usize).val = d.val - 1 := by
    simp only [core.num.Usize.wrapping_sub_val_eq]
    have hn : (1#usize).val = 1 := by scalar_tac
    rw [hn]
    have hb := d.hSize
    have hform : d.val + (UScalar.size .Usize - 1) = (d.val - 1) + UScalar.size .Usize := by omega
    rw [hform, Nat.add_mod, Nat.mod_self, Nat.add_zero, Nat.mod_mod]
    exact Nat.mod_eq_of_lt (by omega)
  have hlsub : (core.num.Usize.wrapping_sub l 3#usize).val = l.val - 3 := by
    simp only [core.num.Usize.wrapping_sub_val_eq]
    have hn : (3#usize).val = 3 := by scalar_tac
    rw [hn]
    have hb := l.hSize
    have hform : l.val + (UScalar.size .Usize - 3) = (l.val - 3) + UScalar.size .Usize := by omega
    rw [hform, Nat.add_mod, Nat.mod_self, Nat.add_zero, Nat.mod_mod]
    exact Nat.mod_eq_of_lt (by omega)
  step*
  exact Dec.match_step hdec hm (by assumption)
    (by simp only [LZ77.mkMatch, LZ77.MATCH_BASE]; simp_all; scalar_tac) (by simp_all) (by simp_all))
@[local step]
theorem put_match_checked_spec (s : Slice Std.U8) (out : Slice Std.U32) (nt p d l : Std.Usize)
    (hdec : Dec s out nt.val p.val) (hm : MatchAt s p.val l.val d.val) :
    slot.pc_put_match_checked s out nt p d l ⦃ fun r => r.1.1.val = nt.val + 1 ∧
      r.1.2.val = p.val + l.val ∧ r.2.length = out.length ∧ Dec s r.2 r.1.1.val r.1.2.val ⦄ := by
 rw [slot.pc_put_match_checked]
 have hm' := hm
 obtain ⟨h3, h258, hpl, hd1, hd32, hdp, _⟩ := hm'
 step*
 exact Dec.match_step hdec hm (by assumption)
  (by simp only [LZ77.mkMatch,LZ77.MATCH_BASE];simp_all;scalar_tac) (by assumption) (by assumption)
@[local step]
theorem put_match_wrapped_spec (s : Slice Std.U8) (out : Slice Std.U32) (nt p d l : Std.Usize)
    (hdec : Dec s out nt.val p.val) (hm : MatchAt s p.val l.val d.val) :
    slot.pc_put_match_wrapped s out nt p d l ⦃ fun r => r.1.1.val = nt.val + 1 ∧
      r.1.2.val = p.val + l.val ∧ r.2.length = out.length ∧ Dec s r.2 r.1.1.val r.1.2.val ⦄ := (by
  rw [slot.pc_put_match_wrapped]
  have hm' := hm
  obtain ⟨h3, h258, hpl, hd1, hd32, hdp, _⟩ := hm'
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  have hsize : Std.Usize.max + 1 = Std.Usize.size := by
    simp only [Std.Usize.max, Std.Usize.size]
    have : 0 < (2 : Nat) ^ Std.Usize.numBits := by positivity
    omega
  have hntp := hdec.2.1
  have hntmax : nt.val + 1 ≤ Std.Usize.max := by omega
  have hemax : p.val + l.val ≤ Std.Usize.max := by omega
  have hdsub : (core.num.Usize.wrapping_sub d 1#usize).val = d.val - 1 := by
    simp only [core.num.Usize.wrapping_sub_val_eq]
    have hn : (1#usize).val = 1 := by scalar_tac
    rw [hn]
    have hb := d.hSize
    have hform : d.val + (UScalar.size .Usize - 1) = (d.val - 1) + UScalar.size .Usize := by omega
    rw [hform, Nat.add_mod, Nat.mod_self, Nat.add_zero, Nat.mod_mod]
    exact Nat.mod_eq_of_lt (by omega)
  have hlsub : (core.num.Usize.wrapping_sub l 3#usize).val = l.val - 3 := by
    simp only [core.num.Usize.wrapping_sub_val_eq]
    have hn : (3#usize).val = 3 := by scalar_tac
    rw [hn]
    have hb := l.hSize
    have hform : l.val + (UScalar.size .Usize - 3) = (l.val - 3) + UScalar.size .Usize := by omega
    rw [hform, Nat.add_mod, Nat.mod_self, Nat.add_zero, Nat.mod_mod]
    exact Nat.mod_eq_of_lt (by omega)
  step*
  exact Dec.match_step hdec hm (by assumption)
    (by simp only [LZ77.mkMatch, LZ77.MATCH_BASE]; simp_all; scalar_tac) (by simp_all; exact Nat.mod_eq_of_lt (by omega)) (by simp_all; exact Nat.mod_eq_of_lt (by omega)))
@[local step]
theorem put_match_h_spec (H : Std.Usize) (s : Slice Std.U8) (out : Slice Std.U32) (nt p d l : Std.Usize)
    (hdec : Dec s out nt.val p.val) (hm : MatchAt s p.val l.val d.val) :
    slot.pc_put_match_h H s out nt p d l ⦃ fun r => r.1.1.val = nt.val + 1 ∧
      r.1.2.val = p.val + l.val ∧ r.2.length = out.length ∧ Dec s r.2 r.1.1.val r.1.2.val ⦄ := by
 rw [slot.pc_put_match_h]
 step*
 all_goals first
  | exact put_match_checked_spec s out nt p d l hdec hm
  | exact put_match_wrapped_spec s out nt p d l hdec hm
  | exact put_match_spec s out nt p d l hdec hm
  | (split <;> first | exact put_match_checked_spec s out nt p d l hdec hm | exact put_match_spec s out nt p d l hdec hm)
theorem MatchAt.back_lit {s : Slice Std.U8} {p l d : Nat} (h : MatchAt s p l d) (hl : l < 258)
    (hdp : d < p) (heq : s.val[p - 1]! = s.val[p - 1 - d]!) : MatchAt s (p - 1) (l + 1) d := (by
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
theorem MatchAt.back_match {s : Slice Std.U8} {p l d w : Nat} (h : MatchAt s p l d)
    (hlw : l + w ≤ 258) (hw : w ≤ p) (hdw : d ≤ p - w) (hmw : Matches s (p - w - d) (p - w) w) :
    MatchAt s (p - w) (l + w) d := (by
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
    BackInv input out d E P0 i1.val i2.val l1.val := (by
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
theorem BackInv.match {input : Slice Std.U8} {out : Slice Std.U32} {d E P0 : Nat}
    {nt p l i1 w i9 i10 i11 i12 : Std.Usize} {t : Std.U32}
    (h : BackInv input out d E P0 nt.val p.val l.val)
    (hi1 : i1.val = nt.val - 1) (hntl : nt.val ≤ out.length) (hnt0 : 1 ≤ nt.val)
    (hi1l : i1.val < out.val.length) (ht : t = out.val[i1.val])
    (hsame : i12.val = 1 → Matches input i11.val i10.val w.val) (hi12 : i12 = 1#usize)
    (ht24 : 16777216 ≤ t.val) (hwv : w.val = (t.val - 16777216) % 256 + 3)
    (hi9 : i9.val = l.val + w.val) (hi9' : i9.val ≤ 258) (hi10 : i10.val = p.val - w.val)
    (hwp : w.val ≤ p.val) (hdw : d ≤ i10.val) (hi11 : i11.val = i10.val - d) :
    BackInv input out d E P0 i1.val i10.val i9.val := C12577!
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
      | (refine ⟨BackInv.lit hinv (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac)
          (by assumption) (by assumption) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by assumption)
          (by assumption) (by assumption) (by first | assumption | omega | scalar_tac) (by assumption) (by first | assumption | omega | scalar_tac)
          (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac), by scalar_tac⟩)
      | (refine ⟨BackInv.match hinv (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac)
          (by assumption) (by assumption) (by assumption) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac)
          (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac)
          (by first | assumption | omega | scalar_tac), by scalar_tac⟩)
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
    LazyInv input L lim out1 nt1.val i.val head1 ins1.val l1.val d1.val := (by
  subst hi
  refine ⟨hdec, hlen, ?_, HeadBound.mono hB hBi, hilim, hins⟩
  rcases hf with h | h
  · omega
  · exact h)
theorem LazyInv.reject {input : Slice Std.U8} {L lim : Nat} {out : Slice Std.U32}
    {nt p ins ins1 l d B : Nat} {N : Std.Usize} {head head1 : Array Std.U32 N}
    (h : LazyInv input L lim out nt p head ins l d) (hB : HeadBound head1 B) (hBp : B ≤ p + 1)
    (hins1 : ins1 ≤ p + 2) : LazyInv input L lim out nt p head1 ins1 l d := (by
  obtain ⟨hdec, hlen, hm, _, hplim, _⟩ := h
  exact ⟨hdec, hlen, hm, HeadBound.mono hB hBp, hplim, hins1⟩)
theorem numBits_ge : 32 ≤ System.Platform.numBits := (by
  rcases System.Platform.numBits_eq with h | h <;> omega)
def MainInv (input : Slice Std.U8) (L : Nat) (out : Slice Std.U32) (nt p : Nat)
    {N : Std.Usize} (head : Array Std.U32 N) (miss : Nat) : Prop :=
  Dec input out nt p ∧ out.length = L ∧ HeadBound head p ∧ miss ≤ p
theorem MainInv.mk' {input : Slice Std.U8} {L : Nat} {out : Slice Std.U32} {nt p m B : Nat}
    {N : Std.Usize} {head : Array Std.U32 N} (hdec : Dec input out nt p) (hlen : out.length = L)
    (hB : HeadBound head B) (hBp : B ≤ p) (hm : m ≤ p) : MainInv input L out nt p head m :=
  ⟨hdec, hlen, HeadBound.mono hB hBp, hm⟩
def CntBound (cnt : Array Std.U32 256#usize) (T : Nat) : Prop :=
  ∀ j : Nat, j < 256 → (cnt.val[j]!).val ≤ T
theorem CntBound.init : CntBound (Std.Array.repeat 256#usize 0#u32) 0 := (by
  intro j hj
  rw [Std.Array.repeat_val, List.getElem!_eq_getElem?_getD,
    List.getElem?_replicate_of_lt (by simpa using hj)]
  rfl)
theorem CntBound.get {cnt : Array Std.U32 256#usize} {T : Nat} (h : CntBound cnt T)
    (a : Std.Usize) (x : Std.U32) (ha : a.val < cnt.val.length) (hx : x = cnt.val[a.val]) :
    x.val ≤ T := (by
  have := h a.val (by simpa using ha)
  rw [getElem!_pos cnt.val a.val ha, ← hx] at this
  exact this)
@[local step]
theorem cnt_index_spec (cnt : Array Std.U32 256#usize) (T : Nat) (h : CntBound cnt T)
    (i : Std.Usize) (hi : i.val < 256) :
    Std.Array.index_usize cnt i ⦃ fun x => x = cnt.val[i.val]! ∧ x.val ≤ T ⦄ := (by
  have hl : i.val < cnt.val.length := by simp; omega
  have := Std.Array.index_usize_spec cnt i (by simpa using hl)
  apply Std.WP.spec_mono this
  intro x hx
  refine ⟨by rw [getElem!_pos cnt.val i.val hl]; exact hx, CntBound.get h i x hl hx⟩)
theorem CntBound.update {cnt : Array Std.U32 256#usize} {T : Nat} (h : CntBound cnt T)
    (a : Std.Usize) (v : Std.U32) (hv : v.val ≤ T + 1) : CntBound (cnt.set a v) (T + 1) := (by
  intro j hj
  rw [Std.Array.set_val_eq]
  by_cases hja : a.val = j
  · subst hja
    have hlen : a.val < cnt.val.length := by simp; omega
    rw [List.getElem!_eq_getElem?_getD, List.getElem?_set_self hlen]
    exact hv
  · rw [List.getElem!_eq_getElem?_getD, List.getElem?_set_ne hja, ← List.getElem!_eq_getElem?_getD]
    exact le_trans (h j hj) (by omega))
theorem CntBound.step {cnt a : Array Std.U32 256#usize} {T : Nat} {x : Std.Usize}
    {v tot1 : Std.U32} (hc : CntBound cnt T) (ha : a = cnt.set x v) (hv : v.val ≤ T + 1)
    (ht1 : tot1.val = T + 1) : CntBound a tot1.val := (by
  rw [ha, ht1]
  exact CntBound.update hc x v hv)
theorem CntBound.mono {cnt : Array Std.U32 256#usize} {T T' : Nat} (h : CntBound cnt T)
    (hT : T ≤ T') : CntBound cnt T' := fun j hj => le_trans (h j hj) hT
@[local step]
theorem lift_spec {α : Type} (x : α) : lift x ⦃ fun y => y = x ⦄ := by
  simp [lift]
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
      r.1.val ≤ cap.val ∧ Matches s a.val b.val r.1.val ⦄ := by
  rw [slot.pc_common_from_loop0]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  apply Std.loop.spec_decr_nat
    (measure := fun r => cap.val - r.1.val + r.2.val)
    (inv := fun r => r.1.val ≤ cap.val ∧ Matches s a.val b.val r.1.val)
  · rintro ⟨k, run⟩ ⟨hk, hm⟩
    simp only at hk hm
    simp only [slot.pc_common_from_loop0.body]
    step*
    all_goals first
      | scalar_tac
      | exact ⟨hk, hm⟩
      | exact wadd_le (by assumption) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac)
      | (refine ⟨by scalar_tac, Matches.xw_zero hm (by assumption) (by assumption) (by first | assumption | omega | scalar_tac)
          (by assumption) (by assumption) (by first | assumption | omega | scalar_tac), by scalar_tac⟩)
      | (have hw := Matches.xw_step hm (by assumption) (by assumption) (by first | assumption | omega | scalar_tac)
          (by assumption) (by assumption) (by assumption) (by assumption) (by assumption)
         refine ⟨by scalar_tac, hw.1, by scalar_tac⟩)
  · exact ⟨hk, hm⟩
theorem common_from_loop1_spec (s : Slice Std.U8) (a b cap k : Std.Usize) (run : Std.U32)
    (ha : a.val + cap.val ≤ s.length) (hb : b.val + cap.val ≤ s.length)
    (hk : k.val ≤ cap.val) (hm : Matches s a.val b.val k.val) :
    slot.pc_common_from_loop1 s a b cap k run ⦃ fun r =>
      r.val ≤ cap.val ∧ Matches s a.val b.val r.val ⦄ := (by
  rw [slot.pc_common_from_loop1]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  apply Std.loop.spec_decr_nat
    (measure := fun r => cap.val - r.1.val + r.2.val)
    (inv := fun r => r.1.val ≤ cap.val ∧ Matches s a.val b.val r.1.val)
  · rintro ⟨k, run⟩ ⟨hk, hm⟩
    simp only at hk hm
    simp only [slot.pc_common_from_loop1.body]
    step*
    all_goals first
      | scalar_tac
      | exact ⟨hk, hm⟩
      | (refine ⟨by scalar_tac, Matches.byte' hm (by assumption) (by assumption) (by first | assumption | omega | scalar_tac)
          (by first | assumption | omega | scalar_tac) (by assumption) (by assumption) (by assumption) (by assumption),
          by scalar_tac⟩)
  · exact ⟨hk, hm⟩)
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
    (hm : m = UScalar.cast .Usize q) : Matches s c.val p.val m.val ∧ m.val < 8 := (by
  have hx0' : ¬x = 0#u64 := by simpa using hx0
  have h := Matches.word_lz (k := 0) (k1 := m) (pa := c) (pb := p)
    (LZ77.Matches.zero s c.val p.val) (by simp) (by simp) hcw hy hx hx0' hlz hq hm (by simp)
  simpa using h)
theorem Matches.xor_zero {s : Slice Std.U8} {c p : Std.Usize} {cw y x : Std.U64}
    (hcw : cw.val = word8 s c.val) (hy : y.val = word8 s p.val)
    (hx : x.val = (cw ^^^ y).val) (hx0 : ¬(x != 0#u64) = true) :
    Matches s c.val p.val (8#usize).val := (by
  have hv : x.val = 0 := by simpa using hx0
  have hx0' : x = 0#u64 := UScalar.eq_of_val_eq (by simp [hv])
  exact Matches.word_zero (k := 0) (k1 := 8#usize) (pa := c) (pb := p)
    (LZ77.Matches.zero s c.val p.val) (by simp) (by simp) hcw hy hx hx0' (by simp))
theorem FoundAt.of_matches {s : Slice Std.U8} {p c d i l : Std.Usize} (hc : c.val ≤ p.val)
    (hd : d = core.num.Usize.wrapping_sub p c) (hi : i = core.num.Usize.wrapping_sub d 1#usize)
    (hlt : i < 32768#usize) (hl : l.val ≤ 258) (hpl : p.val + l.val ≤ s.length)
    (hm : Matches s c.val p.val l.val) :
    FoundAt s p.val l.val d.val ∧ l.val ≤ 258 ∧ d.val ≤ 32768 := (by
  obtain ⟨hdv, hd1, hd2⟩ := dist_of_wrapping hc hd hi hlt
  refine ⟨?_, hl, hd2⟩
  rcases Nat.lt_or_ge l.val 3 with h3 | h3
  · exact Or.inl h3
  · refine Or.inr ⟨h3, hl, hpl, hd1, hd2, by omega, ?_⟩
    rw [show p.val - d.val = c.val by omega]
    exact hm)
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
    Matches s c.val p.val l.val ∧ l.val ≤ 16 := (by
  have h8 := Matches.xz hx hx0
  rw [hi1, hi2] at hx2
  have := Matches.lz_any (k := 8) (k1 := l) h8 hx2 hlz hq hr (by omega)
  exact ⟨this.1, by omega⟩)
theorem Matches.x16a' {s : Slice Std.U8} {c p i1 i2 r l : Std.Usize} {x x2 : Std.U64}
    {lz q : Std.U32} (hx : x.val = word8 s c.val ^^^ word8 s p.val) (hx0 : x = 0#u64)
    (hi1 : i1.val = c.val + 8) (hi2 : i2.val = p.val + 8)
    (hx2 : x2.val = word8 s i1.val ^^^ word8 s i2.val)
    (hlz : lz = core.num.U64.leading_zeros x2) (hq : q.val = lz.val / 8)
    (hr : r = UScalar.cast .Usize q) (hl : l.val = 8 + r.val) (hpn : p.val + 16 ≤ s.length) :
    l.val ≤ 258 ∧ p.val + l.val ≤ s.length ∧ Matches s c.val p.val l.val := (by
  have h := Matches.x16a hx hx0 hi1 hi2 hx2 hlz hq hr hl
  exact ⟨by omega, by omega, h.1⟩)
theorem Matches.x16b {s : Slice Std.U8} {c p r l : Std.Usize} {x : Std.U64}
    {lz q : Std.U32} (hx : x.val = word8 s c.val ^^^ word8 s p.val)
    (hlz : lz = core.num.U64.leading_zeros x) (hq : q.val = lz.val / 8)
    (hr : r = UScalar.cast .Usize q) (hl : l.val = 0 + r.val) (hpn : p.val + 8 ≤ s.length) :
    l.val ≤ 258 ∧ p.val + l.val ≤ s.length ∧ Matches s c.val p.val l.val := (by
  have := Matches.lz_any (k := 0) (k1 := l) (LZ77.Matches.zero s c.val p.val)
    (by simpa using hx) hlz hq hr (by omega)
  exact ⟨by omega, by omega, this.1⟩)
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
        (by first | assumption | omega | scalar_tac)
    | exact Matches.x16a' hxv (by assumption) (by assumption) (by assumption) (by assumption)
        (by assumption) (by assumption) (by assumption) (by assumption) (by first | assumption | omega | scalar_tac)
    | exact Matches.x16b hxv (by assumption) (by assumption) (by assumption) (by assumption)
        (by first | assumption | omega | scalar_tac)
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
  repeat' (split <;> step*)
@[local step]
theorem ahead_m_spec {H : Std.Usize} (s : Slice Std.U8) (head : Array Std.U32 H) (i : Std.Usize)
    (km : Std.U32) (B : Nat) (hB : HeadBound head B) (hBn : B + 8 ≤ s.length)
    (hi4 : i.val + 4 ≤ Std.Usize.max) (hH : 0 < H.val) :
    slot.pc_ahead_m s head i km ⦃ fun r => r.1.val < H.val ∧ r.2.1.val ≤ B ∧
      r.2.2.val = word8 s r.2.1.val ⦄ := by
  rw [slot.pc_ahead_m]
  step
  step
  have hi1 : i1.val ≤ B := HeadBound.get hB a i1 (by first | assumption | omega | scalar_tac) (by assumption)
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
    | (have hi1 := HeadBound.get hB a i1 (by first | assumption | omega | scalar_tac) (by assumption)
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
    (i : Std.Usize) (v : Std.U32) (hi : nt ≤ i.val) : Dec s (out.set i v) nt p := (by
  obtain ⟨hps, hntp, hso, hde⟩ := h
  refine ⟨hps, hntp, by rw [Std.Slice.set_length]; exact hso, ?_⟩
  have : toks (out.set i v) nt = toks out nt := by
    simp only [toks, Std.Slice.set_val_eq, List.take_set]
    rw [List.set_eq_of_length_le (by rw [List.length_take]; omega)]
  rw [this]; exact hde)
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
    Dec s out4 r.val e.val ∧ out4.length = out.length := C12598!
@[local step]
theorem flush4_spec (input : Slice Std.U8) (out : Slice Std.U32) (nt a e : Std.Usize)
    (hdec : Dec input out nt.val a.val) (he : e.val + 8 ≤ input.length) (ha : a.val ≤ e.val) :
    slot.pc_flush4 input out nt a e ⦃ fun r => Dec input r.2 r.1.val e.val ∧
      r.2.length = out.length ⦄ := by
  rw [slot.pc_flush4]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  step*
  all_goals first
    | (constructor; first | (convert hdec using 1 <;> scalar_tac) | rfl)
    | exact flush_spec input out nt a e hdec (by first | assumption | omega | scalar_tac) ha
    | (subst_vars; simp only [Std.Slice.set_length]; scalar_tac)
    | exact Dec.flush4_step hdec ha (by assumption) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac)
        (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by assumption) (by assumption) (by assumption)
        (by assumption) (by first | assumption | omega | scalar_tac) (by assumption) (by assumption) (by assumption)
        (by assumption) (by assumption) (by first | assumption | omega | scalar_tac) (by assumption) (by assumption)
        (by assumption) (by assumption) (by assumption) (by first | assumption | omega | scalar_tac) (by assumption)
        (by assumption) (by assumption) (by assumption) (by assumption)
@[local step]
theorem record3_m_loop0_spec {H : Std.Usize} (s : Slice Std.U8) (head : Array Std.U32 H)
    (km : Std.U32) (ins stop : Std.Usize) (B : Nat) (hB : HeadBound head B)
    (hsB : stop.val < B + 1) (hs4 : stop.val + 4 ≤ Std.Usize.max) (hH : 0 < H.val) :
    slot.pc_record3_m_loop0 s head km ins stop ⦃ fun r =>
      HeadBound r.1 B ∧ (r.2.val ≤ ins.val ∨ r.2.val ≤ stop.val) ⦄ := (by
  rw [slot.pc_record3_m_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun r => stop.val - r.2.val)
    (inv := fun r => HeadBound r.1 B ∧ (r.2.val ≤ ins.val ∨ r.2.val ≤ stop.val))
  · rintro ⟨head, ins'⟩ ⟨hB, hins⟩
    simp only at hB hins
    simp only [slot.pc_record3_m_loop0.body]
    step*
  · exact ⟨hB, Or.inl (le_refl _)⟩)
@[local step]
theorem record3_m_loop1_spec {H : Std.Usize} (s : Slice Std.U8) (head : Array Std.U32 H)
    («end» lim : Std.Usize) (km : Std.U32) (ins : Std.Usize) (B : Nat) (hB : HeadBound head B)
    (heB : «end».val < B + 1) (hl4 : lim.val + 4 ≤ Std.Usize.max) (hH : 0 < H.val) :
    slot.pc_record3_m_loop1 s head «end» lim km ins ⦃ fun r => HeadBound r B ⦄ := (by
  rw [slot.pc_record3_m_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun r => «end».val - r.2.val)
    (inv := fun r => HeadBound r.1 B)
  · rintro ⟨head, ins'⟩ hB
    simp only at hB
    simp only [slot.pc_record3_m_loop1.body]
    step*
  · exact hB)
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
    LazyInv1 input lim P0 p head1 ps1 pc1 pw1 l d ins1 := (by
  obtain ⟨hm, _, hplim, _, _, _, _, hP⟩ := h
  exact ⟨hm, HeadBound.mono hB hBp, hplim, hins1, hps, hpc, hpw, hP⟩)
theorem lazy1_loop_inv {H : Std.Usize} (input : Slice Std.U8) (lazy : Std.Usize) (km : Std.U32)
    (p : Std.Usize)
    (head : Array Std.U32 H) (lim pre_slot pre_c : Std.Usize) (pre_w : Std.U64)
    (l d ins : Std.Usize) (go : Std.U32) (P0 : Nat)
    (hlim : lim.val + 8 = input.length) (hH : 0 < H.val)
    (hinv : LazyInv1 input lim.val P0 p.val head pre_slot.val pre_c.val pre_w.val l.val d.val
      ins.val) :
    slot.pc_run1_loop0_loop0 input lazy km p head lim pre_slot pre_c pre_w l d ins go ⦃ fun r =>
      LazyInv1 input lim.val P0 r.1.val r.2.1 r.2.2.1.val r.2.2.2.1.val r.2.2.2.2.1.val
        r.2.2.2.2.2.1.val r.2.2.2.2.2.2.1.val r.2.2.2.2.2.2.2.val ⦄ := (by
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
      | (refine ⟨LazyInv1.accept (by assumption) (by first | assumption | omega | scalar_tac) (by assumption) (by first | assumption | omega | scalar_tac)
          (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by assumption)
          (by first | assumption | omega | scalar_tac), by scalar_tac⟩)
      | (refine ⟨LazyInv1.reject hinv (by assumption) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac)
          (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by assumption), by scalar_tac⟩)
  · exact hinv)
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
      r.2.2.2.2.1.val = word8 input r.2.2.2.1.val ∧ p.val ≤ r.1.val ⦄ := (by
  apply Std.WP.spec_mono (lazy1_loop_inv input lazy km p head lim pre_slot pre_c pre_w l d ins go
    p.val hlim hH ⟨hm, hB, hplim, hins, hps, hpc, hpw, le_refl _⟩)
  rintro ⟨p', head', ps', pc', pw', l', d', ins'⟩ ⟨hm', hB', hplim', hins', hps', hpc', hpw', hP'⟩
  exact ⟨hm', HeadBound.mono hB' (by have := hm'.1; omega), hplim', hins', hm'.1, hps', hpc',
    hpw', hP'⟩)
@[local step]
theorem tail1_loop1_spec (input : Slice Std.U8) (out : Slice Std.U32) (n nt p : Std.Usize)
    (hn : n.val = input.length) (hdec : Dec input out nt.val p.val) :
    slot.pc_run1_loop1 input out n nt p ⦃ fun r => r.1.val ≤ input.length ∧
      r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := C12582! slot.pc_run1_loop1 slot.pc_run1_loop1.body
@[local step]
theorem tail1_loop2_spec (input : Slice Std.U8) (out : Slice Std.U32) (n nt p : Std.Usize)
    (hn : n.val = input.length) (hdec : Dec input out nt.val p.val) :
    slot.pc_run1_loop2 input out n nt p ⦃ fun r => r.1.val ≤ input.length ∧
      r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := C12582! slot.pc_run1_loop2 slot.pc_run1_loop2.body
def MainInv1 (input : Slice Std.U8) (L : Nat) (out : Slice Std.U32) (nt ls p : Nat)
    {N : Std.Usize} (head : Array Std.U32 N) (miss ps pc pw : Nat) : Prop :=
  Dec input out nt ls ∧ out.length = L ∧ ls ≤ p ∧ HeadBound head p ∧ miss ≤ p ∧ ps < N.val ∧
    pc ≤ p ∧ pw = word8 input pc
theorem MainInv1.mk' {input : Slice Std.U8} {L : Nat} {out : Slice Std.U32}
    {nt ls ls' p m B ps pc pw : Nat} {N : Std.Usize} {head : Array Std.U32 N}
    (hdec : Dec input out nt ls') (hls : ls' = ls) (hlen : out.length = L) (hlsp : ls ≤ p)
    (hB : HeadBound head B) (hBp : B ≤ p) (hm : m ≤ p) (hps : ps < N.val) (hpc : pc ≤ p)
    (hpw : pw = word8 input pc) : MainInv1 input L out nt ls p head m ps pc pw := (by
  subst hls
  exact ⟨hdec, hlen, hlsp, HeadBound.mono hB hBp, hm, hps, hpc, hpw⟩)
set_option maxHeartbeats 16000000 in
theorem main1_loop_spec {H : Std.Usize} (input : Slice Std.U8) (out : Slice Std.U32)
    (skip lazy skcap : Std.Usize) (km : Std.U32) (nt ls p : Std.Usize) (head : Array Std.U32 H)
    (lim miss fuel pre_slot pre_c : Std.Usize) (pre_w : Std.U64) (L : Nat)
    (hlim : lim.val + 8 = input.length) (hskip : skip.val < 32) (hH : 0 < H.val)
    (hinv : MainInv1 input L out nt.val ls.val p.val head miss.val pre_slot.val pre_c.val
      pre_w.val) :
    slot.pc_run1_loop0 input out skip lazy skcap km nt ls p head lim miss fuel pre_slot pre_c pre_w
      ⦃ fun r => Dec input r.1 r.2.1.val r.2.2.val ∧ r.1.length = L ⦄ := (by
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
      | exact FoundAt.real (by assumption) (by first | assumption | omega | scalar_tac)
      | exact HeadBound.mono (by assumption) (by first | assumption | omega | scalar_tac)
      | (refine ⟨MainInv1.mk' (by assumption) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac)
          (by assumption) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac)
          (by assumption), by scalar_tac⟩)
  · exact hinv)
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
theorem run1_spec (H : Std.Usize) (input : Slice Std.U8) (out : Slice Std.U32)
    (skip lazy skcap : Std.Usize) (km : Std.U32) (hlen : input.length ≤ out.length) (hH : 0 < H.val)
    (hskip : skip.val < 32) :
    slot.pc_run1 H input out skip lazy skcap km ⦃ fun r => r.1.val ≤ input.length ∧
      r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := (by
  rw [slot.pc_run1]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  have hB0 : HeadBound (Std.Array.repeat H 0#u32) 0 := HeadBound.init H
  have hdec0 : Dec input out (0#usize).val (0#usize).val := Dec.init input out hlen
  step*)
@[local step]
theorem f_link_spec {H : Std.Usize} (head : Array Std.U32 H) (prev : Array Std.U32 32768#usize)
    (a i : Std.Usize) (B : Nat) (hB : HeadBound head B) (ha : a.val < H.val) (hi : i.val < B + 1) :
    slot.pc_f_link head prev a i ⦃ fun r => HeadBound r.1 B ⦄ := by
  rw [slot.pc_f_link]
  step*
  exact HeadBound.update hB (by assumption) (by omega) (by assumption)
theorem MatchAt.of_try {s : Slice Std.U8} {p c2 d2 i m : Std.Usize}
    (hd : d2 = core.num.Usize.wrapping_sub p c2) (hi : i = core.num.Usize.wrapping_sub d2 1#usize)
    (hlt : i < 32768#usize) (hmm : Matches s c2.val p.val m.val) (hc2 : c2.val ≤ p.val)
    (hm3 : 3 ≤ m.val) (hl : m.val ≤ 258) (hpl : p.val + m.val ≤ s.length) :
    MatchAt s p.val m.val d2.val := (by
  obtain ⟨hdv, hd1, hd2⟩ := dist_of_wrapping hc2 hd hi hlt
  refine ⟨hm3, hl, hpl, hd1, hd2, by omega, ?_⟩
  rw [show p.val - d2.val = c2.val by omega]
  exact hmm)
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
        (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac)
@[local step]
theorem f_deepen_spec (s : Slice Std.U8) (prev : Array Std.U32 32768#usize)
    (c c2 p l d dp minl : Std.Usize) (hc : c.val ≤ p.val) (hm : MatchAt s p.val l.val d.val) :
    slot.pc_f_deepen s prev c c2 p l d dp minl ⦃ fun r => MatchAt s p.val r.1.val r.2.val ⦄ := by
  rw [slot.pc_f_deepen]
  step*
  all_goals try (obtain ⟨g1, g2⟩ := g; dsimp only at *; step*)
@[local step]
theorem f_record3_loop0_spec {H : Std.Usize} (s : Slice Std.U8) (head : Array Std.U32 H)
    (prev : Array Std.U32 32768#usize) (km : Std.U32) (ins stop : Std.Usize) (B : Nat)
    (hB : HeadBound head B) (hsB : stop.val < B + 1) (hs4 : stop.val + 4 ≤ Std.Usize.max)
    (hH : 0 < H.val) :
    slot.pc_f_record3_loop0 s head prev km ins stop ⦃ fun r =>
      HeadBound r.1 B ∧ (r.2.2.val ≤ ins.val ∨ r.2.2.val ≤ stop.val) ⦄ := (by
  rw [slot.pc_f_record3_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun r => stop.val - r.2.2.val)
    (inv := fun r => HeadBound r.1 B ∧ (r.2.2.val ≤ ins.val ∨ r.2.2.val ≤ stop.val))
  · rintro ⟨head, prev, ins'⟩ ⟨hB, hins⟩
    simp only at hB hins
    simp only [slot.pc_f_record3_loop0.body]
    step*
  · exact ⟨hB, Or.inl (le_refl _)⟩)
@[local step]
theorem f_record3_loop1_spec {H : Std.Usize} (s : Slice Std.U8) (head : Array Std.U32 H)
    (prev : Array Std.U32 32768#usize) («end» lim : Std.Usize) (km : Std.U32) (ins : Std.Usize)
    (B : Nat) (hB : HeadBound head B) (heB : «end».val < B + 1)
    (hl4 : lim.val + 4 ≤ Std.Usize.max) (hH : 0 < H.val) :
    slot.pc_f_record3_loop1 s head prev «end» lim km ins ⦃ fun r => HeadBound r.1 B ⦄ := (by
  rw [slot.pc_f_record3_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun r => «end».val - r.2.2.val)
    (inv := fun r => HeadBound r.1 B)
  · rintro ⟨head, prev, ins'⟩ hB
    simp only at hB
    simp only [slot.pc_f_record3_loop1.body]
    step*
  · exact hB)
@[local step]
theorem f_record3_spec {H : Std.Usize} (s : Slice Std.U8) (head : Array Std.U32 H)
    (prev : Array Std.U32 32768#usize) (ins0 a0 «end» lim : Std.Usize) (km : Std.U32) (B : Nat)
    (hB : HeadBound head B) (heB : «end».val < B + 1) (hlim : lim.val + 8 = s.length)
    (hins : ins0.val ≤ lim.val + 1) (hH : 0 < H.val) :
    slot.pc_f_record3 s head prev ins0 a0 «end» lim km ⦃ fun r => HeadBound r.1 B ⦄ := (by
  rw [slot.pc_f_record3]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  step*
  repeat' (split <;> step*)
  all_goals try (obtain ⟨xh, xp⟩ := x; dsimp only at *)
  all_goals try step*
  repeat' (split <;> step*))
theorem lazy1c_loop_inv {H : Std.Usize} (input : Slice Std.U8) (lazy : Std.Usize) (km : Std.U32)
    (p : Std.Usize) (head : Array Std.U32 H) (prev : Array Std.U32 32768#usize)
    (lim pre_slot pre_c : Std.Usize) (pre_w : Std.U64)
    (l d ins : Std.Usize) (go : Std.U32) (P0 : Nat)
    (hlim : lim.val + 8 = input.length) (hH : 0 < H.val)
    (hinv : LazyInv1 input lim.val P0 p.val head pre_slot.val pre_c.val pre_w.val l.val d.val
      ins.val) :
    slot.pc_run1c_loop0_loop0 input lazy km p head prev lim pre_slot pre_c pre_w l d ins go ⦃ fun r =>
      LazyInv1 input lim.val P0 r.1.val r.2.1 r.2.2.2.1.val r.2.2.2.2.1.val r.2.2.2.2.2.1.val
        r.2.2.2.2.2.2.1.val r.2.2.2.2.2.2.2.1.val r.2.2.2.2.2.2.2.2.val ⦄ := (by
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
      | (refine ⟨LazyInv1.accept (by assumption) (by first | assumption | omega | scalar_tac) (by assumption) (by first | assumption | omega | scalar_tac)
          (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by assumption)
          (by first | assumption | omega | scalar_tac), by scalar_tac⟩)
      | (refine ⟨LazyInv1.reject hinv (by assumption) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac)
          (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by assumption), by scalar_tac⟩)
  · exact hinv)
@[local step]
theorem lazy1c_loop_spec {H : Std.Usize} (input : Slice Std.U8) (lazy : Std.Usize) (km : Std.U32)
    (p : Std.Usize) (head : Array Std.U32 H) (prev : Array Std.U32 32768#usize)
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
      r.2.2.2.2.2.1.val = word8 input r.2.2.2.2.1.val ∧ p.val ≤ r.1.val ⦄ := (by
  apply Std.WP.spec_mono (lazy1c_loop_inv input lazy km p head prev lim pre_slot pre_c pre_w l d
    ins go p.val hlim hH ⟨hm, hB, hplim, hins, hps, hpc, hpw, le_refl _⟩)
  rintro ⟨p', head', prev', ps', pc', pw', l', d', ins'⟩
    ⟨hm', hB', hplim', hins', hps', hpc', hpw', hP'⟩
  exact ⟨hm', HeadBound.mono hB' (by have := hm'.1; omega), hplim', hins', hm'.1, hps', hpc',
    hpw', hP'⟩)
@[local step]
theorem tail1c_loop1_spec (input : Slice Std.U8) (out : Slice Std.U32) (n nt p : Std.Usize)
    (hn : n.val = input.length) (hdec : Dec input out nt.val p.val) :
    slot.pc_run1c_loop1 input out n nt p ⦃ fun r => r.1.val ≤ input.length ∧
      r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := C12582! slot.pc_run1c_loop1 slot.pc_run1c_loop1.body
@[local step]
theorem tail1c_loop2_spec (input : Slice Std.U8) (out : Slice Std.U32) (n nt p : Std.Usize)
    (hn : n.val = input.length) (hdec : Dec input out nt.val p.val) :
    slot.pc_run1c_loop2 input out n nt p ⦃ fun r => r.1.val ≤ input.length ∧
      r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := C12582! slot.pc_run1c_loop2 slot.pc_run1c_loop2.body
set_option maxHeartbeats 16000000 in
theorem main1c_loop_spec {H : Std.Usize} (input : Slice Std.U8) (out : Slice Std.U32)
    (skip lazy skcap : Std.Usize) (km : Std.U32) (dp minl nt ls p : Std.Usize)
    (head : Array Std.U32 H) (prev : Array Std.U32 32768#usize)
    (lim miss fuel pre_slot pre_c : Std.Usize) (pre_w : Std.U64) (L : Nat)
    (hlim : lim.val + 8 = input.length) (hskip : skip.val < 32) (hH : 0 < H.val)
    (hinv : MainInv1 input L out nt.val ls.val p.val head miss.val pre_slot.val pre_c.val
      pre_w.val) :
    slot.pc_run1c_loop0 input out skip lazy skcap km dp minl nt ls p head prev lim miss fuel pre_slot
      pre_c pre_w ⦃ fun r => Dec input r.1 r.2.1.val r.2.2.val ∧ r.1.length = L ⦄ := (by
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
      | exact FoundAt.real (by assumption) (by first | assumption | omega | scalar_tac)
      | exact HeadBound.mono (by assumption) (by first | assumption | omega | scalar_tac)
      | (refine ⟨MainInv1.mk' (by assumption) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac)
          (by assumption) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac)
          (by assumption), by scalar_tac⟩)
  · exact hinv)
@[local step]
theorem main1c_loop_spec' {H : Std.Usize} (input : Slice Std.U8) (out : Slice Std.U32)
    (skip lazy skcap : Std.Usize) (km : Std.U32) (dp minl nt ls p : Std.Usize)
    (head : Array Std.U32 H) (prev : Array Std.U32 32768#usize)
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
      r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := (by
  rw [slot.pc_run1c]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  have hB0 : HeadBound (Std.Array.repeat H 0#u32) 0 := HeadBound.init H
  have hdec0 : Dec input out (0#usize).val (0#usize).val := Dec.init input out hlen
  step*)
end PC
namespace PI1
abbrev word8 (input : Slice Std.U8) (p : Nat) : Nat := _root_.Submission.PC.word8 input p
abbrev HeadBound {N : Std.Usize} (head : Array Std.U32 N) (B : Nat) : Prop := _root_.Submission.PC.HeadBound head B
abbrev Cand (s : Slice Std.U8) (p cap best bd : Nat) : Prop := _root_.Submission.PC.Cand s p cap best bd
abbrev MatchAt (s : Slice Std.U8) (p l d : Nat) : Prop := _root_.Submission.PC.MatchAt s p l d
abbrev FoundAt (s : Slice Std.U8) (p l d : Nat) : Prop := _root_.Submission.PC.FoundAt s p l d
abbrev Dec (s : Slice Std.U8) (out : Slice Std.U32) (nt p : Nat) : Prop := _root_.Submission.PC.Dec s out nt p
abbrev BackInv (input : Slice Std.U8) (out : Slice Std.U32) (d E P0 : Nat) (nt p l : Nat) : Prop := _root_.Submission.PC.BackInv input out d E P0 nt p l
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
theorem tp_lift_spec {α : Type} (x : α) : lift x ⦃ fun y => y = x ⦄ := (by
  simp [lift, WP.spec_ok])
theorem tp_numBits_ge : 32 ≤ System.Platform.numBits := (by
  cases System.Platform.numBits_eq <;> simp [*])
@[local scalar_tac System.Platform.numBits]
theorem tp_numBits_ge' : 32 ≤ System.Platform.numBits := tp_numBits_ge
end TinyPath
theorem u8_lt (x : Std.U8) : x.val < 256 := by scalar_tac
theorem word8_digit (input : Slice Std.U8) (p k : Nat) (hk : k < 8) :
    (input.val[p + k]!).val = _root_.Submission.PC.word8 input p / 256 ^ (7 - k) % 256 := (by
  have := u8_lt (input.val[p]!); have := u8_lt (input.val[p+1]!)
  have := u8_lt (input.val[p+2]!); have := u8_lt (input.val[p+3]!)
  have := u8_lt (input.val[p+4]!); have := u8_lt (input.val[p+5]!)
  have := u8_lt (input.val[p+6]!); have := u8_lt (input.val[p+7]!)
  simp only [_root_.Submission.PC.word8]
  rcases (show k = 0 ∨ k = 1 ∨ k = 2 ∨ k = 3 ∨ k = 4 ∨ k = 5 ∨ k = 6 ∨ k = 7 by omega) with
    rfl | rfl | rfl | rfl | rfl | rfl | rfl | rfl <;> simp only [Nat.add_zero, Nat.pow_zero, Nat.pow_succ, Nat.one_mul,
    Nat.sub_self, Nat.reduceSub] <;> omega)
theorem word8_prefix (input : Slice Std.U8) (a b d : Nat) (hd : d ≤ 8)
    (h : _root_.Submission.PC.word8 input a / 2 ^ (64 - 8 * d) = _root_.Submission.PC.word8 input b / 2 ^ (64 - 8 * d)) :
    ∀ k, k < d → input.val[b + k]! = input.val[a + k]! := (by
  intro k hk
  have e : (256 : Nat) ^ (7 - k) = 2 ^ (64 - 8 * d) * 2 ^ (8 * (d - 1 - k)) := by
    rw [← pow_add, show (256 : Nat) = 2 ^ 8 by norm_num, ← pow_mul]
    congr 1; omega
  have key : _root_.Submission.PC.word8 input a / 256 ^ (7 - k) = _root_.Submission.PC.word8 input b / 256 ^ (7 - k) := by
    rw [e, ← Nat.div_div_eq_div_mul, ← Nat.div_div_eq_div_mul, h]
  have ha := word8_digit input a k (by omega)
  have hb := word8_digit input b k (by omega)
  rw [key] at ha
  scalar_tac)
theorem Matches.add_prefix {input : Slice Std.U8} {a b l d : Nat} (h : Matches input a b l)
    (hd : d ≤ 8)
    (hw : _root_.Submission.PC.word8 input (a + l) / 2 ^ (64 - 8 * d) = _root_.Submission.PC.word8 input (b + l) / 2 ^ (64 - 8 * d)) :
    Matches input a b (l + d) := (by
  intro k hk
  by_cases hkl : k < l
  · exact h k hkl
  · have := word8_prefix input (a + l) (b + l) d hd hw (k - l) (by omega)
    rw [show b + l + (k - l) = b + k by omega, show a + l + (k - l) = a + k by omega] at this
    exact this)
theorem or_eq_add_of_mod {x t : Nat} (m : Nat) (hx : x % 2 ^ m = 0) (ht : t < 2 ^ m) :
    x ||| t = x + t := (by
  have h := Nat.two_pow_add_eq_or_of_lt ht (x / 2 ^ m)
  have hx' : 2 ^ m * (x / 2 ^ m) = x := by
    have := Nat.div_add_mod x (2 ^ m); omega
  rw [hx'] at h
  exact h.symm)
theorem shl_byte {x : Nat} (k : Nat) (hx : x < 256) (hk : k ≤ 56) :
    x <<< k % U64.size = x * 2 ^ k := (by
  rw [Nat.shiftLeft_eq, U64.size_def]
  apply Nat.mod_eq_of_lt
  have : 2 ^ k ≤ 2 ^ 56 := Nat.pow_le_pow_right (by norm_num) hk
  have : x * 2 ^ k < 256 * 2 ^ 56 := by
    calc x * 2 ^ k < 256 * 2 ^ k := by
          apply Nat.mul_lt_mul_of_pos_right hx (Nat.two_pow_pos _)
      _ ≤ 256 * 2 ^ 56 := Nat.mul_le_mul_left _ this
  simp only [U64.numBits] at *
  omega)
theorem be8_nat {a b c d e f g h : Nat} (ha : a < 256) (hb : b < 256) (hc : c < 256)
    (hd : d < 256) (he : e < 256) (hf : f < 256) (hg : g < 256) (hh : h < 256) :
    (a <<< 56 % U64.size ||| b <<< 48 % U64.size ||| c <<< 40 % U64.size |||
      d <<< 32 % U64.size ||| e <<< 24 % U64.size ||| f <<< 16 % U64.size |||
      g <<< 8 % U64.size ||| h) =
    a * 2^56 + b * 2^48 + c * 2^40 + d * 2^32 + e * 2^24 + f * 2^16 + g * 2^8 + h := C12529!
@[local step]
abbrev be8_spec := @_root_.Submission.PC.be8_spec
theorem nat_xor_eq_zero {a b : Nat} (h : a ^^^ b = 0) : a = b := (by
  have : a ^^^ (a ^^^ b) = b := by rw [← Nat.xor_assoc, Nat.xor_self, Nat.zero_xor]
  rw [h, Nat.xor_zero] at this; exact this)
theorem div_eq_of_xor_lt {x y m : Nat} (hz : x ^^^ y < 2 ^ m) : x / 2 ^ m = y / 2 ^ m := (by
  have h : (x ^^^ y) >>> m = 0 := by rw [Nat.shiftRight_eq_div_pow]; exact Nat.div_eq_of_lt hz
  rw [Nat.shiftRight_xor_distrib] at h
  have := nat_xor_eq_zero h
  simpa [Nat.shiftRight_eq_div_pow] using this)
theorem lt_pow_leadingZeros (z : BitVec 64) :
    z.toNat < 2 ^ (64 - 8 * (BitVec.leadingZeros z / 8)) := (by
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
theorem leadingZeros_lt_of_ne (z : BitVec 64) (h : z ≠ 0) : BitVec.leadingZeros z < 64 := (by
  unfold BitVec.leadingZeros
  simp only [h, if_false]
  omega)
@[local step]
theorem lz_spec (x : Std.U64) :
    lift (core.num.U64.leading_zeros x) ⦃ fun r => r = core.num.U64.leading_zeros x ∧ r.val ≤ 64 ⦄ := (by
  simp only [lift, Std.WP.spec_ok, true_and]
  have hle : BitVec.leadingZeros x.bv ≤ 64 := by unfold BitVec.leadingZeros; split <;> omega
  simp only [core.num.U64.leading_zeros, UScalar.val, UScalarTy.U32_numBits_eq,
    BitVec.natCast_eq_ofNat, BitVec.toNat_ofNat, Nat.reducePow]
  omega)
theorem lz_val (x : Std.U64) :
    (core.num.U64.leading_zeros x).val = BitVec.leadingZeros x.bv := (by
  have hle : BitVec.leadingZeros x.bv ≤ 64 := by unfold BitVec.leadingZeros; split <;> omega
  simp only [core.num.U64.leading_zeros, UScalar.val, UScalarTy.U32_numBits_eq,
    BitVec.natCast_eq_ofNat, BitVec.toNat_ofNat, Nat.reducePow]
  omega)
theorem Matches.word_lz {input : Slice Std.U8} {a b k : Nat} {pa pb r k1 : Std.Usize}
    {x y z : Std.U64} {lz q : Std.U32}
    (h : Matches input a b k) (hpa : pa.val = a + k) (hpb : pb.val = b + k)
    (hx : x.val = _root_.Submission.PC.word8 input pa.val) (hy : y.val = _root_.Submission.PC.word8 input pb.val)
    (hz : z.val = (x ^^^ y).val) (hz0 : ¬z = 0#u64) (hlz : lz = core.num.U64.leading_zeros z)
    (hq : q.val = lz.val / 8) (hr : r = UScalar.cast .Usize q) (hk1 : k1.val = k + r.val) :
    Matches input a b k1.val ∧ k1.val < k + 8 := (by
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
theorem Matches.word_zero {input : Slice Std.U8} {a b k : Nat} {pa pb k1 : Std.Usize}
    {x y z : Std.U64}
    (h : Matches input a b k) (hpa : pa.val = a + k) (hpb : pb.val = b + k)
    (hx : x.val = _root_.Submission.PC.word8 input pa.val) (hy : y.val = _root_.Submission.PC.word8 input pb.val)
    (hz : z.val = (x ^^^ y).val) (hz0 : z = 0#u64) (hk1 : k1.val = k + 8) :
    Matches input a b k1.val := (by
  have hxy : x.val = y.val := by
    apply nat_xor_eq_zero
    rw [← UScalar.val_xor, ← hz, hz0]; rfl
  rw [hpa] at hx; rw [hpb] at hy
  rw [hk1]
  apply Matches.add_prefix h (le_refl 8)
  rw [← hx, ← hy, hxy])
theorem Matches.byte' {input : Slice Std.U8} {a b l : Nat} {pa pb l1 : Std.Usize}
    {x y : Std.U8} (h : Matches input a b l) (hpa : pa.val = a + l) (hpb : pb.val = b + l)
    (hpa' : pa.val < input.val.length) (hpb' : pb.val < input.val.length)
    (hx : x = input.val[pa.val]) (hy : y = input.val[pb.val]) (hxy : x = y)
    (hl1 : l1.val = l + 1) : Matches input a b l1.val := (by
  rw [hl1]
  apply LZ77.Matches.succ h
  rw [← hpa, ← hpb, getElem!_pos input.val pa.val hpa', getElem!_pos input.val pb.val hpb',
    ← hx, ← hy, hxy])
theorem wadd_val {x y z : Std.Usize} (hz : z = core.num.Usize.wrapping_add x y)
    (hb : x.val + y.val ≤ Std.Usize.max) : z.val = x.val + y.val := (by
  have hlt : x.val + y.val < Usize.size := by scalar_tac
  rw [hz, core.num.Usize.wrapping_add_val_eq, UScalar.size_UScalarTyUsize, Nat.mod_eq_of_lt hlt])
theorem wadd_le {x y z : Std.Usize} {m n : Nat} (hz : z = core.num.Usize.wrapping_add x y)
    (h : x.val + y.val + m ≤ n) (hn : n ≤ Std.Usize.max) : z.val + m ≤ n := (by
  rw [wadd_val hz (by omega)]; exact h)
@[local step]
abbrev xor8_spec := @_root_.Submission.PC.xor8_spec
theorem Matches.lz_any {input : Slice Std.U8} {a b k : Nat} {r k1 : Std.Usize} {z : Std.U64}
    {lz q : Std.U32} (h : Matches input a b k)
    (hz : z.val = _root_.Submission.PC.word8 input (a + k) ^^^ _root_.Submission.PC.word8 input (b + k))
    (hlz : lz = core.num.U64.leading_zeros z) (hq : q.val = lz.val / 8)
    (hr : r = UScalar.cast .Usize q) (hk1 : k1.val = k + r.val) :
    Matches input a b k1.val ∧ k1.val ≤ k + 8 := (by
  have hle : BitVec.leadingZeros z.bv ≤ 64 := by unfold BitVec.leadingZeros; split <;> omega
  have hrv : r.val = BitVec.leadingZeros z.bv / 8 := by
    rw [hr, U32.cast_Usize_val_eq, hq, hlz, lz_val]
  refine ⟨?_, by omega⟩
  rw [hk1, hrv]
  apply Matches.add_prefix h (by omega)
  apply div_eq_of_xor_lt
  rw [← hz]
  exact lt_pow_leadingZeros z.bv)
theorem Matches.xz {input : Slice Std.U8} {a b : Nat} {z : Std.U64}
    (hz : z.val = _root_.Submission.PC.word8 input a ^^^ _root_.Submission.PC.word8 input b) (hz0 : z = 0#u64) :
    Matches input a b 8 := (by
  have hv : _root_.Submission.PC.word8 input a ^^^ _root_.Submission.PC.word8 input b = 0 := by rw [← hz, hz0]; rfl
  have hab := nat_xor_eq_zero hv
  have := Matches.add_prefix (LZ77.Matches.zero input a b) (le_refl 8)
    (by simp only [Nat.add_zero]; rw [hab])
  simpa using this)
theorem xval_of {x cw y : Std.U64} {A B : Nat} (hx : x.val = (cw ^^^ y).val) (hcw : cw.val = A)
    (hy : y.val = B) : x.val = A ^^^ B := by
  rw [hx, UScalar.val_xor, hcw, hy]
theorem Matches.xw_step {input : Slice Std.U8} {a b k pa pb k1 r : Std.Usize} {z : Std.U64}
    {lz q : Std.U32} (h : Matches input a.val b.val k.val)
    (hpa : pa = core.num.Usize.wrapping_add a k) (hpb : pb = core.num.Usize.wrapping_add b k)
    (hab : a.val + k.val + 8 ≤ input.length ∧ b.val + k.val + 8 ≤ input.length)
    (hz : z.val = _root_.Submission.PC.word8 input pa.val ^^^ _root_.Submission.PC.word8 input pb.val)
    (hlz : lz = core.num.U64.leading_zeros z) (hq : q.val = lz.val / 8)
    (hr : r = UScalar.cast .Usize q) (hk1 : k1.val = k.val + r.val) :
    Matches input a.val b.val k1.val ∧ k1.val ≤ k.val + 8 := (by
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  rw [wadd_val hpa (by omega), wadd_val hpb (by omega)] at hz
  exact Matches.lz_any h hz hlz hq hr hk1)
theorem Matches.xw_zero {input : Slice Std.U8} {a b k pa pb k1 : Std.Usize} {z : Std.U64}
    (h : Matches input a.val b.val k.val)
    (hpa : pa = core.num.Usize.wrapping_add a k) (hpb : pb = core.num.Usize.wrapping_add b k)
    (hab : a.val + k.val + 8 ≤ input.length ∧ b.val + k.val + 8 ≤ input.length)
    (hz : z.val = _root_.Submission.PC.word8 input pa.val ^^^ _root_.Submission.PC.word8 input pb.val) (hz0 : z = 0#u64)
    (hk1 : k1.val = k.val + 8) : Matches input a.val b.val k1.val := (by
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
theorem Matches.word_eq {input : Slice Std.U8} {a b k : Nat} {pa pb k1 : Std.Usize}
    {x y : Std.U64}
    (h : Matches input a b k) (hpa : pa.val = a + k) (hpb : pb.val = b + k)
    (hx : x.val = _root_.Submission.PC.word8 input pa.val) (hy : y.val = _root_.Submission.PC.word8 input pb.val)
    (hxy : x = y) (hk1 : k1.val = k + 8) :
    Matches input a b k1.val := (by
  rw [hpa] at hx; rw [hpb] at hy
  rw [hk1]
  apply Matches.add_prefix h (le_refl 8)
  rw [← hx, ← hy, hxy])
abbrev same_loop0_spec := @_root_.Submission.PC.same_loop0_spec
@[local step]
abbrev same_loop1_spec := @_root_.Submission.PC.same_loop1_spec
@[local step]
abbrev same_loop2_spec := @_root_.Submission.PC.same_loop2_spec
theorem Matches.mask {input : Slice Std.U8} {a b k len : Nat} {pa pb : Std.Usize}
    {x y z w : Std.U64} {sh : Std.U32}
    (h : Matches input a b k) (hpa : pa.val = a + k) (hpb : pb.val = b + k)
    (hx : x.val = _root_.Submission.PC.word8 input pa.val) (hy : y.val = _root_.Submission.PC.word8 input pb.val)
    (hz : z.val = (x ^^^ y).val) (hw : w.val = z.val >>> sh.val) (hw0 : ¬(w != 0#u64) = true)
    (hsh : sh.val = 64 - 8 * (len - k)) (hk : k < len) (hlen : len < k + 8) :
    Matches input a b len := (by
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
@[local step]
abbrev same_spec := @_root_.Submission.PC.same_spec
theorem lz32_le (x : Std.U32) (k : Nat) (hk : k < 32) (hx : 2 ^ k ≤ x.val) :
    (core.num.U32.leading_zeros x).val ≤ 31 - k := C12546!
@[local step]
theorem lz32_spec (x : Std.U32) :
    lift (core.num.U32.leading_zeros x) ⦃ fun r => r = core.num.U32.leading_zeros x ∧
      (4 ≤ x.val → r.val ≤ 29) ∧ (8 ≤ x.val → r.val ≤ 28) ⦄ := (by
  simp only [lift, Std.WP.spec_ok, true_and]
  exact ⟨fun h => lz32_le x 2 (by norm_num) (by simpa using h),
    fun h => lz32_le x 3 (by norm_num) (by simpa using h)⟩)
@[local step]
theorem hcast_I32_spec {ty : UScalarTy} (x : UScalar ty) (h : x.val ≤ 2147483647) :
    lift (UScalar.hcast .I32 x) ⦃ fun y => y.val = x.val ⦄ :=
  UScalar.hcast_inBounds_spec .I32 x (by simp [I32.max_def, I32.numBits]; omega)
theorem GBASE_bound : -1000000000 ≤ slot.pi1_GBASE.val ∧ slot.pi1_GBASE.val ≤ 1000000000 := by
  unfold slot.pi1_GBASE
  simp
@[local step]
abbrev gain_spec := @_root_.Submission.PC.gain_spec
theorem HeadBound.mono {N : Std.Usize} {head : Array Std.U32 N} {B B' : Nat}
    (h : _root_.Submission.PC.HeadBound head B) (hB : B ≤ B') : _root_.Submission.PC.HeadBound head B' := fun j hj => le_trans (h j hj) hB
theorem HeadBound.init (N : Std.Usize) : _root_.Submission.PC.HeadBound (Std.Array.repeat N 0#u32) 0 := (by
  intro j hj
  rw [Std.Array.repeat_val] at hj ⊢
  rw [List.getElem!_eq_getElem?_getD, List.getElem?_replicate_of_lt (by simpa using hj)]
  rfl)
theorem HeadBound.set {N : Std.Usize} {head : Array Std.U32 N} {B : Nat} (h : _root_.Submission.PC.HeadBound head B)
    (a : Std.Usize) (v : Std.U32) (hv : v.val ≤ B) : _root_.Submission.PC.HeadBound (head.set a v) B := (by
  intro j hj
  rw [Std.Array.set_val_eq] at hj ⊢
  rw [List.length_set] at hj
  by_cases hja : a.val = j
  · subst hja
    rw [List.getElem!_eq_getElem?_getD, List.getElem?_set_self hj]
    exact hv
  · rw [List.getElem!_eq_getElem?_getD, List.getElem?_set_ne hja, ← List.getElem!_eq_getElem?_getD]
    exact h j hj)
theorem HeadBound.update {N : Std.Usize} {head head1 : Array Std.U32 N} {B : Nat}
    {a i : Std.Usize} {v : Std.U32} (h : _root_.Submission.PC.HeadBound head B) (hv : v = UScalar.cast .U32 i)
    (hi : i.val ≤ B) (h1 : head1 = head.set a v) : _root_.Submission.PC.HeadBound head1 B := (by
  subst h1
  apply HeadBound.set h a v
  rw [hv]
  have : (UScalar.cast .U32 i).val = i.val % 2 ^ 32 := by
    simp only [UScalar.cast_val_eq, UScalarTy.U32_numBits_eq]
  rw [this]
  exact le_trans (Nat.mod_le _ _) hi)
theorem HeadBound.get {N : Std.Usize} {head : Array Std.U32 N} {B : Nat} (h : _root_.Submission.PC.HeadBound head B)
    (a : Std.Usize) (x : Std.U32) (ha : a.val < head.val.length) (hx : x = head.val[a.val]) :
    x.val ≤ B := (by
  have := h a.val ha
  rw [getElem!_pos head.val a.val ha, ← hx] at this
  exact this)
theorem cast_usize_le {x : Std.U32} {y : Std.Usize} {B : Nat} (h : y = UScalar.cast .Usize x)
    (hx : x.val ≤ B) : y.val ≤ B := (by
  rw [h, U32.cast_Usize_val_eq]; exact hx)
@[local step]
abbrev be4_spec := @_root_.Submission.PC.be4_spec
theorem dist_of_wrapping {p c d i : Std.Usize} (hc : c.val ≤ p.val)
    (hd : d = core.num.Usize.wrapping_sub p c) (hi : i = core.num.Usize.wrapping_sub d 1#usize)
    (hlt : i < 32768#usize) : d.val = p.val - c.val ∧ 1 ≤ d.val ∧ d.val ≤ 32768 := C12553!
theorem Cand.of_common {s : Slice Std.U8} {p c d i l cap : Std.Usize} (hc : c.val ≤ p.val)
    (hd : d = core.num.Usize.wrapping_sub p c) (hi : i = core.num.Usize.wrapping_sub d 1#usize)
    (hlt : i < 32768#usize) (hl : l.val ≤ cap.val) (hm : Matches s c.val p.val l.val) :
    _root_.Submission.PC.Cand s p.val cap.val l.val d.val := (by
  obtain ⟨hdv, hd1, hd2⟩ := dist_of_wrapping hc hd hi hlt
  refine Or.inr ⟨hd1, hd2, by omega, hl, ?_⟩
  rw [show p.val - d.val = c.val by omega]
  exact hm)
theorem FoundAt.of_cand {s : Slice Std.U8} {p cap : Nat} {l d : Std.Usize}
    (hc : _root_.Submission.PC.Cand s p cap l.val d.val) (hd : ¬d = 0#usize) (hcap : cap ≤ 258)
    (hpl : p + l.val ≤ s.length) : _root_.Submission.PC.FoundAt s p l.val d.val := (by
  have hd' : d.val ≠ 0 := by intro h; apply hd; exact UScalar.eq_of_val_eq (by simp [h])
  rcases hc with h0 | ⟨hd1, hd2, hdp, hl, hm⟩
  · exact absurd h0 hd'
  · rcases Nat.lt_or_ge l.val 3 with h3 | h3
    · exact Or.inl h3
    · exact Or.inr ⟨h3, by omega, hpl, hd1, hd2, hdp, hm⟩)
theorem Cand.len_le {s : Slice Std.U8} {p cap : Nat} {l d : Std.Usize}
    (hc : _root_.Submission.PC.Cand s p cap l.val d.val) (hd : ¬d = 0#usize) (hcap : cap ≤ 258) : l.val ≤ 258 := (by
  have hd' : d.val ≠ 0 := by intro h; apply hd; exact UScalar.eq_of_val_eq (by simp [h])
  rcases hc with h0 | ⟨_, _, _, hl, _⟩
  · exact absurd h0 hd'
  · omega)
theorem Cand.dist_le {s : Slice Std.U8} {p cap l d : Nat} (hc : _root_.Submission.PC.Cand s p cap l d) :
    d ≤ 32768 := (by
  rcases hc with h0 | ⟨_, hd, _⟩ <;> omega)
theorem FoundAt.none (s : Slice Std.U8) (p : Nat) : _root_.Submission.PC.FoundAt s p (0#usize).val (0#usize).val :=
  Or.inl (by simp)
theorem FoundAt.real {s : Slice Std.U8} {p l d : Nat} (hf : _root_.Submission.PC.FoundAt s p l d) (h3 : 3 ≤ l) :
    _root_.Submission.PC.MatchAt s p l d := (by
  rcases hf with h | h
  · omega
  · exact h)
theorem copyN_take_prefix (acc : List Nat) (d : Nat) :
    ∀ n, (copyN acc d n).take acc.length = acc := (by
  intro n
  induction n with
  | zero => simp [copyN]
  | succ m ih =>
    simp only [copyN]
    rw [List.take_append_of_le_length (by simp)]
    exact ih)
theorem foldlM_emit_length : ∀ (ts : List Nat) (init acc : List Nat),
    ts.foldlM emit init = some acc → init.length + ts.length ≤ acc.length := C12560!
theorem decode_length_le {ts acc : List Nat} (h : decode ts = some acc) :
    ts.length ≤ acc.length := (by
  have := foldlM_emit_length ts [] acc h
  simpa using this)
theorem decode_pop_lit {ts : List Nat} {t : Nat} {inp : List Nat} {p : Nat}
    (hp : p ≤ inp.length) (hd : decode (ts ++ [t]) = some (inp.take p)) (ht : t < 256) :
    1 ≤ p ∧ decode ts = some (inp.take (p - 1)) := (by
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
theorem decode_pop_match {ts : List Nat} {t : Nat} {inp : List Nat} {p : Nat}
    (hp : p ≤ inp.length) (hd : decode (ts ++ [t]) = some (inp.take p)) (ht : 256 ≤ t) :
    tokLen t ≤ p ∧ decode ts = some (inp.take (p - tokLen t)) := C12563!
theorem toks_pop (out : Slice Std.U32) (nt : Nat) (h0 : 0 < nt) (hle : nt ≤ out.length) :
    toks out nt = toks out (nt - 1) ++ [(out.val[nt - 1]!).val] := (by
  have hlt : nt - 1 < out.val.length := by
    have : out.length = out.val.length := rfl
    omega
  simp only [toks]
  conv_lhs => rw [show nt = (nt - 1) + 1 by omega]
  rw [List.take_add_one, List.getElem?_eq_getElem hlt, Option.toList_some, List.map_append]
  simp [getElem!_pos out.val (nt - 1) hlt])
theorem toks_length (out : Slice Std.U32) (nt : Nat) (h : nt ≤ out.length) :
    (toks out nt).length = nt := (by
  simp only [toks, List.length_map, List.length_take]
  have : out.length = out.val.length := rfl
  omega)
theorem Dec.init (input : Slice Std.U8) (out : Slice Std.U32) (h : input.length ≤ out.length) :
    _root_.Submission.PC.Dec input out (0#usize).val (0#usize).val :=
  ⟨by simp, by simp, h, by simp [toks, LZ77.decode]⟩
theorem Dec.lit {s : Slice Std.U8} {out : Slice Std.U32} {nt p : Nat} (h : _root_.Submission.PC.Dec s out nt p)
    (hp : p < s.length) (ntU : Std.Usize) (hnt : ntU.val = nt) (v : Std.U32)
    (hv : v.val = (s.val[p]!).val) :
    _root_.Submission.PC.Dec s (out.set ntU v) (nt + 1) (p + 1) := (by
  obtain ⟨hps, hntp, hso, hde⟩ := h
  have hntl : ntU.val < out.length := by omega
  refine ⟨by omega, by omega, by rw [Std.Slice.set_length]; exact hso, ?_⟩
  rw [← hnt]
  refine emit_lit s out ntU p v (by rw [hnt]; exact hde) hp hntl ?_
  have hpl : p < s.val.length := hp
  rw [hv, bytes_getElem! s p hpl, getElem!_pos s.val p hpl])
theorem Dec.match {s : Slice Std.U8} {out : Slice Std.U32} {nt p l d : Nat} (h : _root_.Submission.PC.Dec s out nt p)
    (hm : _root_.Submission.PC.MatchAt s p l d) (ntU : Std.Usize) (hnt : ntU.val = nt) (v : Std.U32)
    (hv : v.val = LZ77.mkMatch d l) :
    _root_.Submission.PC.Dec s (out.set ntU v) (nt + 1) (p + l) := (by
  obtain ⟨hps, hntp, hso, hde⟩ := h
  obtain ⟨h3, h258, hpl, hd1, hd32, hdp, hmm⟩ := hm
  have hntl : ntU.val < out.length := by omega
  refine ⟨by omega, by omega, by rw [Std.Slice.set_length]; exact hso, ?_⟩
  rw [← hnt]
  exact emit_match s out ntU p d l v (by rw [hnt]; exact hde) hntl hd1 hdp hd32 h3 h258 hpl hmm hv)
theorem Dec.pop_lit {s : Slice Std.U8} {out : Slice Std.U32} {nt p : Nat} (h : _root_.Submission.PC.Dec s out nt p)
    (h0 : 0 < nt) (hle : nt ≤ out.length) (ht : (out.val[nt - 1]!).val < 256) :
    1 ≤ p ∧ _root_.Submission.PC.Dec s out (nt - 1) (p - 1) := (by
  obtain ⟨hps, hntp, hso, hde⟩ := h
  rw [toks_pop out nt h0 hle] at hde
  obtain ⟨hp1, hde'⟩ := decode_pop_lit (by simpa using hps) hde ht
  exact ⟨hp1, by omega, by omega, hso, hde'⟩)
theorem Dec.pop_match {s : Slice Std.U8} {out : Slice Std.U32} {nt p : Nat} (h : _root_.Submission.PC.Dec s out nt p)
    (h0 : 0 < nt) (hle : nt ≤ out.length) (ht : 256 ≤ (out.val[nt - 1]!).val) :
    tokLen (out.val[nt - 1]!).val ≤ p ∧
      _root_.Submission.PC.Dec s out (nt - 1) (p - tokLen (out.val[nt - 1]!).val) := (by
  obtain ⟨hps, hntp, hso, hde⟩ := h
  rw [toks_pop out nt h0 hle] at hde
  obtain ⟨hw, hde'⟩ := decode_pop_match (by simpa using hps) hde ht
  have hlen := decode_length_le hde'
  rw [toks_length out (nt - 1) (by omega), List.length_take, bytes_length] at hlen
  exact ⟨hw, by omega, by omega, hso, hde'⟩)
theorem Dec.done {s : Slice Std.U8} {out : Slice Std.U32} {nt p : Nat} (h : _root_.Submission.PC.Dec s out nt p)
    (hp : s.length ≤ p) : nt ≤ s.length ∧ LZ77.Valid (bytes s) (toks out nt) := (by
  obtain ⟨hps, hntp, hso, hde⟩ := h
  refine ⟨by omega, ?_⟩
  unfold LZ77.Valid
  rw [hde, show p = s.length by omega, ← bytes_length, List.take_length])
theorem Dec.lit_step {s : Slice Std.U8} {out out1 : Slice Std.U32} {ntU nt1 pU : Std.Usize}
    {b : Std.U8} {v : Std.U32} (h : _root_.Submission.PC.Dec s out ntU.val pU.val) (hp : pU.val < s.val.length)
    (hb : b = s.val[pU.val]) (hv : v = UScalar.cast .U32 b) (hout1 : out1 = out.set ntU v)
    (hnt1 : nt1.val = ntU.val + 1) :
    nt1.val = ntU.val + 1 ∧ out1.length = out.length ∧ _root_.Submission.PC.Dec s out1 nt1.val (pU.val + 1) := (by
  subst hout1
  refine ⟨hnt1, Std.Slice.set_length .., ?_⟩
  rw [hnt1]
  exact Dec.lit h hp ntU rfl v (by rw [hv, U8.cast_U32_val_eq, hb, getElem!_pos s.val pU.val hp]))
@[local step]
abbrev put_lit_spec := @_root_.Submission.PC.put_lit_spec
theorem Dec.match_step {s : Slice Std.U8} {out out1 : Slice Std.U32} {ntU nt1 pU dU lU e : Std.Usize}
    {v : Std.U32} (h : _root_.Submission.PC.Dec s out ntU.val pU.val) (hm : _root_.Submission.PC.MatchAt s pU.val lU.val dU.val)
    (hout1 : out1 = out.set ntU v) (hv : v.val = LZ77.mkMatch dU.val lU.val)
    (hnt1 : nt1.val = ntU.val + 1) (he : e.val = pU.val + lU.val) :
    nt1.val = ntU.val + 1 ∧ e.val = pU.val + lU.val ∧ out1.length = out.length ∧
      _root_.Submission.PC.Dec s out1 nt1.val e.val := (by
  subst hout1
  refine ⟨hnt1, he, Std.Slice.set_length .., ?_⟩
  rw [hnt1, he]
  exact Dec.match h hm ntU rfl v hv)
@[local step]
abbrev put_match_spec := @_root_.Submission.PC.put_match_spec
@[local step]
abbrev put_match_checked_spec := @_root_.Submission.PC.put_match_checked_spec
@[local step]
abbrev put_match_wrapped_spec := @_root_.Submission.PC.put_match_wrapped_spec
@[local step]
abbrev put_match_h_spec := @_root_.Submission.PC.put_match_h_spec
theorem MatchAt.back_lit {s : Slice Std.U8} {p l d : Nat} (h : _root_.Submission.PC.MatchAt s p l d) (hl : l < 258)
    (hdp : d < p) (heq : s.val[p - 1]! = s.val[p - 1 - d]!) : _root_.Submission.PC.MatchAt s (p - 1) (l + 1) d := (by
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
theorem MatchAt.back_match {s : Slice Std.U8} {p l d w : Nat} (h : _root_.Submission.PC.MatchAt s p l d)
    (hlw : l + w ≤ 258) (hw : w ≤ p) (hdw : d ≤ p - w) (hmw : Matches s (p - w - d) (p - w) w) :
    _root_.Submission.PC.MatchAt s (p - w) (l + w) d := (by
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
theorem BackInv.lit {input : Slice Std.U8} {out : Slice Std.U32} {d E P0 : Nat}
    {nt p l i1 i2 i4 l1 : Std.Usize} {t : Std.U32} {x y : Std.U8}
    (h : _root_.Submission.PC.BackInv input out d E P0 nt.val p.val l.val)
    (hi1 : i1.val = nt.val - 1) (hntl : nt.val ≤ out.length) (hnt0 : 1 ≤ nt.val)
    (hi1l : i1.val < out.val.length) (ht : t = out.val[i1.val]) (ht256 : t < 256#u32)
    (hi2 : i2.val = p.val - 1) (hi2l : i2.val < input.val.length) (hx : x = input.val[i2.val])
    (hxy : x = y) (hi4 : i4.val = i2.val - d) (hi4l : i4.val < input.val.length)
    (hy : y = input.val[i4.val]) (hl : l.val < 258) (hdp : d < p.val)
    (hl1 : l1.val = l.val + 1) :
    _root_.Submission.PC.BackInv input out d E P0 i1.val i2.val l1.val := (by
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
theorem BackInv.match {input : Slice Std.U8} {out : Slice Std.U32} {d E P0 : Nat}
    {nt p l i1 w i9 i10 i11 i12 : Std.Usize} {t : Std.U32}
    (h : _root_.Submission.PC.BackInv input out d E P0 nt.val p.val l.val)
    (hi1 : i1.val = nt.val - 1) (hntl : nt.val ≤ out.length) (hnt0 : 1 ≤ nt.val)
    (hi1l : i1.val < out.val.length) (ht : t = out.val[i1.val])
    (hsame : i12.val = 1 → Matches input i11.val i10.val w.val) (hi12 : i12 = 1#usize)
    (ht24 : 16777216 ≤ t.val) (hwv : w.val = (t.val - 16777216) % 256 + 3)
    (hi9 : i9.val = l.val + w.val) (hi9' : i9.val ≤ 258) (hi10 : i10.val = p.val - w.val)
    (hwp : w.val ≤ p.val) (hdw : d ≤ i10.val) (hi11 : i11.val = i10.val - d) :
    _root_.Submission.PC.BackInv input out d E P0 i1.val i10.val i9.val := C12577!
abbrev fold_loop_inv := @_root_.Submission.PC.fold_loop_inv
@[local step]
abbrev fold_spec := @_root_.Submission.PC.fold_spec
@[local step]
abbrev fold_w_spec := @_root_.Submission.PC.fold_w_spec
def LazyInv (input : Slice Std.U8) (L lim : Nat) (out : Slice Std.U32) (nt p : Nat)
    {N : Std.Usize} (head : Array Std.U32 N) (ins l d : Nat) : Prop :=
  _root_.Submission.PC.Dec input out nt p ∧ out.length = L ∧ _root_.Submission.PC.MatchAt input p l d ∧ _root_.Submission.PC.HeadBound head (p + 1) ∧
    p < lim ∧ ins ≤ p + 2
theorem LazyInv.accept {input : Slice Std.U8} {L lim p' B : Nat} {out1 : Slice Std.U32}
    {nt1 i ins1 l1 d1 minl : Std.Usize} {N : Std.Usize} {head1 : Array Std.U32 N}
    (hdec : _root_.Submission.PC.Dec input out1 nt1.val p') (hi : i.val = p') (hlen : out1.length = L)
    (hf : _root_.Submission.PC.FoundAt input i.val l1.val d1.val) (hl1 : minl.val ≤ l1.val) (hminl : 3 ≤ minl.val)
    (hB : _root_.Submission.PC.HeadBound head1 B) (hBi : B ≤ i.val + 1) (hilim : i.val < lim)
    (hins : ins1.val ≤ i.val + 2) :
    LazyInv input L lim out1 nt1.val i.val head1 ins1.val l1.val d1.val := (by
  subst hi
  refine ⟨hdec, hlen, ?_, HeadBound.mono hB hBi, hilim, hins⟩
  rcases hf with h | h
  · omega
  · exact h)
theorem LazyInv.reject {input : Slice Std.U8} {L lim : Nat} {out : Slice Std.U32}
    {nt p ins ins1 l d B : Nat} {N : Std.Usize} {head head1 : Array Std.U32 N}
    (h : LazyInv input L lim out nt p head ins l d) (hB : _root_.Submission.PC.HeadBound head1 B) (hBp : B ≤ p + 1)
    (hins1 : ins1 ≤ p + 2) : LazyInv input L lim out nt p head1 ins1 l d := (by
  obtain ⟨hdec, hlen, hm, _, hplim, _⟩ := h
  exact ⟨hdec, hlen, hm, HeadBound.mono hB hBp, hplim, hins1⟩)
theorem numBits_ge : 32 ≤ System.Platform.numBits := (by
  rcases System.Platform.numBits_eq with h | h <;> omega)
def MainInv (input : Slice Std.U8) (L : Nat) (out : Slice Std.U32) (nt p : Nat)
    {N : Std.Usize} (head : Array Std.U32 N) (miss : Nat) : Prop :=
  _root_.Submission.PC.Dec input out nt p ∧ out.length = L ∧ _root_.Submission.PC.HeadBound head p ∧ miss ≤ p
theorem MainInv.mk' {input : Slice Std.U8} {L : Nat} {out : Slice Std.U32} {nt p m B : Nat}
    {N : Std.Usize} {head : Array Std.U32 N} (hdec : _root_.Submission.PC.Dec input out nt p) (hlen : out.length = L)
    (hB : _root_.Submission.PC.HeadBound head B) (hBp : B ≤ p) (hm : m ≤ p) : MainInv input L out nt p head m :=
  ⟨hdec, hlen, HeadBound.mono hB hBp, hm⟩
def CntBound (cnt : Array Std.U32 256#usize) (T : Nat) : Prop :=
  ∀ j : Nat, j < 256 → (cnt.val[j]!).val ≤ T
theorem CntBound.init : CntBound (Std.Array.repeat 256#usize 0#u32) 0 := (by
  intro j hj
  rw [Std.Array.repeat_val, List.getElem!_eq_getElem?_getD,
    List.getElem?_replicate_of_lt (by simpa using hj)]
  rfl)
theorem CntBound.get {cnt : Array Std.U32 256#usize} {T : Nat} (h : CntBound cnt T)
    (a : Std.Usize) (x : Std.U32) (ha : a.val < cnt.val.length) (hx : x = cnt.val[a.val]) :
    x.val ≤ T := (by
  have := h a.val (by simpa using ha)
  rw [getElem!_pos cnt.val a.val ha, ← hx] at this
  exact this)
@[local step]
theorem cnt_index_spec (cnt : Array Std.U32 256#usize) (T : Nat) (h : CntBound cnt T)
    (i : Std.Usize) (hi : i.val < 256) :
    Std.Array.index_usize cnt i ⦃ fun x => x = cnt.val[i.val]! ∧ x.val ≤ T ⦄ := (by
  have hl : i.val < cnt.val.length := by simp; omega
  have := Std.Array.index_usize_spec cnt i (by simpa using hl)
  apply Std.WP.spec_mono this
  intro x hx
  refine ⟨by rw [getElem!_pos cnt.val i.val hl]; exact hx, CntBound.get h i x hl hx⟩)
theorem CntBound.update {cnt : Array Std.U32 256#usize} {T : Nat} (h : CntBound cnt T)
    (a : Std.Usize) (v : Std.U32) (hv : v.val ≤ T + 1) : CntBound (cnt.set a v) (T + 1) := (by
  intro j hj
  rw [Std.Array.set_val_eq]
  by_cases hja : a.val = j
  · subst hja
    have hlen : a.val < cnt.val.length := by simp; omega
    rw [List.getElem!_eq_getElem?_getD, List.getElem?_set_self hlen]
    exact hv
  · rw [List.getElem!_eq_getElem?_getD, List.getElem?_set_ne hja, ← List.getElem!_eq_getElem?_getD]
    exact le_trans (h j hj) (by omega))
theorem CntBound.step {cnt a : Array Std.U32 256#usize} {T : Nat} {x : Std.Usize}
    {v tot1 : Std.U32} (hc : CntBound cnt T) (ha : a = cnt.set x v) (hv : v.val ≤ T + 1)
    (ht1 : tot1.val = T + 1) : CntBound a tot1.val := (by
  rw [ha, ht1]
  exact CntBound.update hc x v hv)
theorem CntBound.mono {cnt : Array Std.U32 256#usize} {T T' : Nat} (h : CntBound cnt T)
    (hT : T ≤ T') : CntBound cnt T' := fun j hj => le_trans (h j hj) hT
@[local step]
theorem lift_spec {α : Type} (x : α) : lift x ⦃ fun y => y = x ⦄ := by
  simp [lift]
theorem Dec.cast {s : Slice Std.U8} {out : Slice Std.U32} {nt p p' : Nat} (h : _root_.Submission.PC.Dec s out nt p)
    (hp : p = p') : _root_.Submission.PC.Dec s out nt p' := hp ▸ h
@[local step]
theorem head_set_spec {H : Std.Usize} (head : Array Std.U32 H) (a i : Std.Usize) (B : Nat)
    (hB : _root_.Submission.PC.HeadBound head B) (ha : a.val < H.val) (hi : i.val < B + 1) :
    slot.pc_head_set head a i ⦃ fun r => _root_.Submission.PC.HeadBound r B ⦄ := by
  exact _root_.Submission.PC.head_set_spec head a i B hB ha hi
abbrev common_from_loop0_spec := @_root_.Submission.PC.common_from_loop0_spec
abbrev common_from_loop1_spec := @_root_.Submission.PC.common_from_loop1_spec
@[local step]
abbrev common_from_spec := @_root_.Submission.PC.common_from_spec
theorem Matches.xor_lz {s : Slice Std.U8} {c p m : Std.Usize} {cw y x : Std.U64}
    {lz q : Std.U32} (hcw : cw.val = _root_.Submission.PC.word8 s c.val) (hy : y.val = _root_.Submission.PC.word8 s p.val)
    (hx : x.val = (cw ^^^ y).val) (hx0 : (x != 0#u64) = true)
    (hlz : lz = core.num.U64.leading_zeros x) (hq : q.val = lz.val / 8)
    (hm : m = UScalar.cast .Usize q) : Matches s c.val p.val m.val ∧ m.val < 8 := (by
  have hx0' : ¬x = 0#u64 := by simpa using hx0
  have h := Matches.word_lz (k := 0) (k1 := m) (pa := c) (pb := p)
    (LZ77.Matches.zero s c.val p.val) (by simp) (by simp) hcw hy hx hx0' hlz hq hm (by simp)
  simpa using h)
theorem Matches.xor_zero {s : Slice Std.U8} {c p : Std.Usize} {cw y x : Std.U64}
    (hcw : cw.val = _root_.Submission.PC.word8 s c.val) (hy : y.val = _root_.Submission.PC.word8 s p.val)
    (hx : x.val = (cw ^^^ y).val) (hx0 : ¬(x != 0#u64) = true) :
    Matches s c.val p.val (8#usize).val := (by
  have hv : x.val = 0 := by simpa using hx0
  have hx0' : x = 0#u64 := UScalar.eq_of_val_eq (by simp [hv])
  exact Matches.word_zero (k := 0) (k1 := 8#usize) (pa := c) (pb := p)
    (LZ77.Matches.zero s c.val p.val) (by simp) (by simp) hcw hy hx hx0' (by simp))
theorem FoundAt.of_matches {s : Slice Std.U8} {p c d i l : Std.Usize} (hc : c.val ≤ p.val)
    (hd : d = core.num.Usize.wrapping_sub p c) (hi : i = core.num.Usize.wrapping_sub d 1#usize)
    (hlt : i < 32768#usize) (hl : l.val ≤ 258) (hpl : p.val + l.val ≤ s.length)
    (hm : Matches s c.val p.val l.val) :
    _root_.Submission.PC.FoundAt s p.val l.val d.val ∧ l.val ≤ 258 ∧ d.val ≤ 32768 := (by
  obtain ⟨hdv, hd1, hd2⟩ := dist_of_wrapping hc hd hi hlt
  refine ⟨?_, hl, hd2⟩
  rcases Nat.lt_or_ge l.val 3 with h3 | h3
  · exact Or.inl h3
  · refine Or.inr ⟨h3, hl, hpl, hd1, hd2, by omega, ?_⟩
    rw [show p.val - d.val = c.val by omega]
    exact hm)
theorem FoundAt.none' (s : Slice Std.U8) (p : Nat) :
    _root_.Submission.PC.FoundAt s p (0#usize).val (0#usize).val ∧ (0#usize).val ≤ 258 ∧ (0#usize).val ≤ 32768 :=
  ⟨FoundAt.none s p, by simp, by simp⟩
@[local step]
abbrev xlen_spec := @_root_.Submission.PC.xlen_spec
theorem Matches.x16a {s : Slice Std.U8} {c p i1 i2 r l : Std.Usize} {x x2 : Std.U64}
    {lz q : Std.U32} (hx : x.val = _root_.Submission.PC.word8 s c.val ^^^ _root_.Submission.PC.word8 s p.val) (hx0 : x = 0#u64)
    (hi1 : i1.val = c.val + 8) (hi2 : i2.val = p.val + 8)
    (hx2 : x2.val = _root_.Submission.PC.word8 s i1.val ^^^ _root_.Submission.PC.word8 s i2.val)
    (hlz : lz = core.num.U64.leading_zeros x2) (hq : q.val = lz.val / 8)
    (hr : r = UScalar.cast .Usize q) (hl : l.val = 8 + r.val) :
    Matches s c.val p.val l.val ∧ l.val ≤ 16 := (by
  have h8 := Matches.xz hx hx0
  rw [hi1, hi2] at hx2
  have := Matches.lz_any (k := 8) (k1 := l) h8 hx2 hlz hq hr (by omega)
  exact ⟨this.1, by omega⟩)
theorem Matches.x16a' {s : Slice Std.U8} {c p i1 i2 r l : Std.Usize} {x x2 : Std.U64}
    {lz q : Std.U32} (hx : x.val = _root_.Submission.PC.word8 s c.val ^^^ _root_.Submission.PC.word8 s p.val) (hx0 : x = 0#u64)
    (hi1 : i1.val = c.val + 8) (hi2 : i2.val = p.val + 8)
    (hx2 : x2.val = _root_.Submission.PC.word8 s i1.val ^^^ _root_.Submission.PC.word8 s i2.val)
    (hlz : lz = core.num.U64.leading_zeros x2) (hq : q.val = lz.val / 8)
    (hr : r = UScalar.cast .Usize q) (hl : l.val = 8 + r.val) (hpn : p.val + 16 ≤ s.length) :
    l.val ≤ 258 ∧ p.val + l.val ≤ s.length ∧ Matches s c.val p.val l.val := (by
  have h := Matches.x16a hx hx0 hi1 hi2 hx2 hlz hq hr hl
  exact ⟨by omega, by omega, h.1⟩)
theorem Matches.x16b {s : Slice Std.U8} {c p r l : Std.Usize} {x : Std.U64}
    {lz q : Std.U32} (hx : x.val = _root_.Submission.PC.word8 s c.val ^^^ _root_.Submission.PC.word8 s p.val)
    (hlz : lz = core.num.U64.leading_zeros x) (hq : q.val = lz.val / 8)
    (hr : r = UScalar.cast .Usize q) (hl : l.val = 0 + r.val) (hpn : p.val + 8 ≤ s.length) :
    l.val ≤ 258 ∧ p.val + l.val ≤ s.length ∧ Matches s c.val p.val l.val := (by
  have := Matches.lz_any (k := 0) (k1 := l) (LZ77.Matches.zero s c.val p.val)
    (by simpa using hx) hlz hq hr (by omega)
  exact ⟨by omega, by omega, this.1⟩)
@[local step]
abbrev xlen16_spec := @_root_.Submission.PC.xlen16_spec
@[local step]
abbrev lazy_lo_spec := @_root_.Submission.PC.lazy_lo_spec
@[local step]
abbrev probe_lazy_spec := @_root_.Submission.PC.probe_lazy_spec
@[local step]
abbrev skip_len_spec := @_root_.Submission.PC.skip_len_spec
@[local step]
abbrev skip_to_spec := @_root_.Submission.PC.skip_to_spec
@[local step]
abbrev slot_of_m_spec := @_root_.Submission.PC.slot_of_m_spec
@[local step]
theorem ahead_m_spec {H : Std.Usize} (s : Slice Std.U8) (head : Array Std.U32 H) (i : Std.Usize)
    (km : Std.U32) (B : Nat) (hB : _root_.Submission.PC.HeadBound head B) (hBn : B + 8 ≤ s.length)
    (hi4 : i.val + 4 ≤ Std.Usize.max) (hH : 0 < H.val) :
    slot.pc_ahead_m s head i km ⦃ fun r => r.1.val < H.val ∧ r.2.1.val ≤ B ∧
      r.2.2.val = _root_.Submission.PC.word8 s r.2.1.val ⦄ := by
  exact _root_.Submission.PC.ahead_m_spec s head i km B hB hBn hi4 hH
@[local step]
theorem ahead_if_m_spec {H : Std.Usize} (s : Slice Std.U8) (head : Array Std.U32 H)
    (i lim a c : Std.Usize) (w : Std.U64) (km : Std.U32) (B : Nat) (hB : _root_.Submission.PC.HeadBound head B)
    (hBi : B < i.val + 1) (hlim : lim.val + 8 = s.length) (ha : a.val < H.val)
    (hc : c.val < B + 1) (hw : w.val = _root_.Submission.PC.word8 s c.val) (hH : 0 < H.val) :
    slot.pc_ahead_if_m s head i lim a c w km ⦃ fun r => r.1.val < H.val ∧ r.2.1.val ≤ B ∧
      r.2.2.val = _root_.Submission.PC.word8 s r.2.1.val ⦄ := by
  exact _root_.Submission.PC.ahead_if_m_spec s head i lim a c w km B hB hBi hlim ha hc hw hH
@[local step]
theorem ahead_fix_m_spec {H : Std.Usize} (s : Slice Std.U8) (head : Array Std.U32 H)
    (i lim e a c : Std.Usize) (w : Std.U64) (a0 c0 : Std.Usize) (w0 : Std.U64) (km : Std.U32)
    (B : Nat) (hB : _root_.Submission.PC.HeadBound head B) (hBi : B < i.val + 1) (hlim : lim.val + 8 = s.length)
    (hw : w.val = _root_.Submission.PC.word8 s c.val) (ha0 : a0.val < H.val) (hc0 : c0.val < B + 1)
    (hw0 : w0.val = _root_.Submission.PC.word8 s c0.val) (hH : 0 < H.val) :
    slot.pc_ahead_fix_m s head i lim e a c w a0 c0 w0 km ⦃ fun r => r.1.val < H.val ∧
      r.2.1.val ≤ B ∧ r.2.2.val = _root_.Submission.PC.word8 s r.2.1.val ⦄ := by
  exact _root_.Submission.PC.ahead_fix_m_spec s head i lim e a c w a0 c0 w0 km B hB hBi hlim hw ha0 hc0 hw0 hH
@[local step]
abbrev probe_m_spec := @_root_.Submission.PC.probe_m_spec
abbrev flush_loop_spec := @_root_.Submission.PC.flush_loop_spec
@[local step]
abbrev flush_spec := @_root_.Submission.PC.flush_spec
theorem Dec.set_beyond {s : Slice Std.U8} {out : Slice Std.U32} {nt p : Nat} (h : _root_.Submission.PC.Dec s out nt p)
    (i : Std.Usize) (v : Std.U32) (hi : nt ≤ i.val) : _root_.Submission.PC.Dec s (out.set i v) nt p := (by
  obtain ⟨hps, hntp, hso, hde⟩ := h
  refine ⟨hps, hntp, by rw [Std.Slice.set_length]; exact hso, ?_⟩
  have : toks (out.set i v) nt = toks out nt := by
    simp only [toks, Std.Slice.set_val_eq, List.take_set]
    rw [List.set_eq_of_length_le (by rw [List.length_take]; omega)]
  rw [this]; exact hde)
theorem Dec.flush4_step {s : Slice Std.U8} {out out1 out2 out3 out4 : Slice Std.U32}
    {nt a e j r i7 i9 i11 i13 i15 i17 : Std.Usize} {b0 b1 b2 b3 : Std.U8}
    {v0 v1 v2 v3 : Std.U32}
    (h : _root_.Submission.PC.Dec s out nt.val a.val) (hae : a.val ≤ e.val) (hj : j.val = e.val - a.val)
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
    _root_.Submission.PC.Dec s out4 r.val e.val ∧ out4.length = out.length := C12598!
@[local step]
abbrev flush4_spec := @_root_.Submission.PC.flush4_spec
@[local step]
theorem record3_m_loop0_spec {H : Std.Usize} (s : Slice Std.U8) (head : Array Std.U32 H)
    (km : Std.U32) (ins stop : Std.Usize) (B : Nat) (hB : _root_.Submission.PC.HeadBound head B)
    (hsB : stop.val < B + 1) (hs4 : stop.val + 4 ≤ Std.Usize.max) (hH : 0 < H.val) :
    slot.pi1_record3_m_loop0 s head km ins stop ⦃ fun r =>
      _root_.Submission.PC.HeadBound r.1 B ∧ (r.2.val ≤ ins.val ∨ r.2.val ≤ stop.val) ⦄ := (by
  rw [slot.pi1_record3_m_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun r => stop.val - r.2.val)
    (inv := fun r => _root_.Submission.PC.HeadBound r.1 B ∧ (r.2.val ≤ ins.val ∨ r.2.val ≤ stop.val))
  · rintro ⟨head, ins'⟩ ⟨hB, hins⟩
    simp only at hB hins
    simp only [slot.pi1_record3_m_loop0.body]
    step*
  · exact ⟨hB, Or.inl (le_refl _)⟩)
@[local step]
theorem record3_m_loop1_spec {H : Std.Usize} (s : Slice Std.U8) (head : Array Std.U32 H)
    («end» lim : Std.Usize) (km : Std.U32) (ins : Std.Usize) (B : Nat) (hB : _root_.Submission.PC.HeadBound head B)
    (heB : «end».val < B + 1) (hl4 : lim.val + 4 ≤ Std.Usize.max) (hH : 0 < H.val) :
    slot.pi1_record3_m_loop1 s head «end» lim km ins ⦃ fun r => _root_.Submission.PC.HeadBound r B ⦄ := (by
  rw [slot.pi1_record3_m_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun r => «end».val - r.2.val)
    (inv := fun r => _root_.Submission.PC.HeadBound r.1 B)
  · rintro ⟨head, ins'⟩ hB
    simp only at hB
    simp only [slot.pi1_record3_m_loop1.body]
    step*
  · exact hB)
@[local step]
theorem record3_m_spec {H : Std.Usize} (s : Slice Std.U8) (head : Array Std.U32 H)
    (ins0 a0 «end» lim : Std.Usize) (km : Std.U32) (B : Nat) (hB : _root_.Submission.PC.HeadBound head B)
    (heB : «end».val < B + 1) (hlim : lim.val + 8 = s.length) (hins : ins0.val ≤ lim.val + 1)
    (hH : 0 < H.val) :
    slot.pi1_record3_m s head ins0 a0 «end» lim km ⦃ fun r => _root_.Submission.PC.HeadBound r B ⦄ := by
  rw [slot.pi1_record3_m]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  step*
  repeat' (split <;> step*)
def LazyInv1 (input : Slice Std.U8) (lim P0 : Nat) (p : Nat) {N : Std.Usize}
    (head : Array Std.U32 N) (ps pc pw l d ins : Nat) : Prop :=
  _root_.Submission.PC.MatchAt input p l d ∧ _root_.Submission.PC.HeadBound head (p + 1) ∧ p < lim ∧ ins ≤ p + 2 ∧ ps < N.val ∧
    pc ≤ p + 1 ∧ pw = _root_.Submission.PC.word8 input pc ∧ P0 ≤ p
theorem LazyInv1.accept {input : Slice Std.U8} {lim P0 B : Nat}
    {i ins1 l1 d1 ps pc : Std.Usize} {pw : Std.U64} {N : Std.Usize} {head1 : Array Std.U32 N}
    (hf : _root_.Submission.PC.FoundAt input i.val l1.val d1.val) (hl1 : 3 ≤ l1.val)
    (hB : _root_.Submission.PC.HeadBound head1 B) (hBi : B ≤ i.val + 1) (hilim : i.val < lim)
    (hins : ins1.val ≤ i.val + 2) (hps : ps.val < N.val) (hpc : pc.val ≤ i.val + 1)
    (hpw : pw.val = _root_.Submission.PC.word8 input pc.val) (hP : P0 ≤ i.val) :
    LazyInv1 input lim P0 i.val head1 ps.val pc.val pw.val l1.val d1.val ins1.val :=
  ⟨FoundAt.real hf hl1, HeadBound.mono hB hBi, hilim, hins, hps, hpc, hpw, hP⟩
theorem LazyInv1.reject {input : Slice Std.U8} {lim P0 : Nat}
    {p ps pc pw l d ins B ps1 pc1 pw1 ins1 : Nat} {N : Std.Usize}
    {head head1 : Array Std.U32 N}
    (h : LazyInv1 input lim P0 p head ps pc pw l d ins) (hB : _root_.Submission.PC.HeadBound head1 B)
    (hBp : B ≤ p + 1) (hins1 : ins1 ≤ p + 2) (hps : ps1 < N.val) (hpc : pc1 ≤ p + 1)
    (hpw : pw1 = _root_.Submission.PC.word8 input pc1) :
    LazyInv1 input lim P0 p head1 ps1 pc1 pw1 l d ins1 := (by
  obtain ⟨hm, _, hplim, _, _, _, _, hP⟩ := h
  exact ⟨hm, HeadBound.mono hB hBp, hplim, hins1, hps, hpc, hpw, hP⟩)
theorem lazy1_loop_inv {H : Std.Usize} (input : Slice Std.U8) (lazy : Std.Usize) (km : Std.U32)
    (p : Std.Usize)
    (head : Array Std.U32 H) (lim pre_slot pre_c : Std.Usize) (pre_w : Std.U64)
    (l d ins : Std.Usize) (go : Std.U32) (P0 : Nat)
    (hlim : lim.val + 8 = input.length) (hH : 0 < H.val)
    (hinv : LazyInv1 input lim.val P0 p.val head pre_slot.val pre_c.val pre_w.val l.val d.val
      ins.val) :
    slot.pi1_run1_loop0_loop0 input lazy km p head lim pre_slot pre_c pre_w l d ins go ⦃ fun r =>
      LazyInv1 input lim.val P0 r.1.val r.2.1 r.2.2.1.val r.2.2.2.1.val r.2.2.2.2.1.val
        r.2.2.2.2.2.1.val r.2.2.2.2.2.2.1.val r.2.2.2.2.2.2.2.val ⦄ := (by
  rw [slot.pi1_run1_loop0_loop0]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  apply Std.loop.spec_decr_nat
    (measure := fun r => lim.val - r.1.val + r.2.2.2.2.2.2.2.2.val)
    (inv := fun r => LazyInv1 input lim.val P0 r.1.val r.2.1 r.2.2.1.val r.2.2.2.1.val
      r.2.2.2.2.1.val r.2.2.2.2.2.1.val r.2.2.2.2.2.2.1.val r.2.2.2.2.2.2.2.1.val)
  · rintro ⟨p, head, pre_slot, pre_c, pre_w, l, d, ins, go⟩ hinv
    simp only at hinv
    have hinv' := hinv
    obtain ⟨⟨h3, h258, hpl, hd1, hd32, hdp, _⟩, hB, hplim, hins, hslot, hpc, hpw, hP⟩ := hinv'
    simp only [slot.pi1_run1_loop0_loop0.body]
    step*
    all_goals first
      | (refine ⟨LazyInv1.accept (by assumption) (by first | assumption | omega | scalar_tac) (by assumption) (by first | assumption | omega | scalar_tac)
          (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by assumption)
          (by first | assumption | omega | scalar_tac), by scalar_tac⟩)
      | (refine ⟨LazyInv1.reject hinv (by assumption) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac)
          (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by assumption), by scalar_tac⟩)
  · exact hinv)
@[local step]
theorem lazy1_loop_spec {H : Std.Usize} (input : Slice Std.U8) (lazy : Std.Usize) (km : Std.U32)
    (p : Std.Usize)
    (head : Array Std.U32 H) (lim pre_slot pre_c : Std.Usize) (pre_w : Std.U64)
    (l d ins : Std.Usize) (go : Std.U32)
    (hlim : lim.val + 8 = input.length) (hH : 0 < H.val)
    (hm : _root_.Submission.PC.MatchAt input p.val l.val d.val)
    (hB : _root_.Submission.PC.HeadBound head (p.val + 1)) (hplim : p.val < lim.val) (hins : ins.val ≤ p.val + 2)
    (hps : pre_slot.val < H.val) (hpc : pre_c.val ≤ p.val + 1)
    (hpw : pre_w.val = _root_.Submission.PC.word8 input pre_c.val) :
    slot.pi1_run1_loop0_loop0 input lazy km p head lim pre_slot pre_c pre_w l d ins go ⦃ fun r =>
      _root_.Submission.PC.MatchAt input r.1.val r.2.2.2.2.2.1.val r.2.2.2.2.2.2.1.val ∧
      _root_.Submission.PC.HeadBound r.2.1 (r.1.val + r.2.2.2.2.2.1.val) ∧ r.1.val < lim.val ∧
      r.2.2.2.2.2.2.2.val ≤ r.1.val + 2 ∧ 3 ≤ r.2.2.2.2.2.1.val ∧
      r.2.2.1.val < H.val ∧ r.2.2.2.1.val ≤ r.1.val + 1 ∧
      r.2.2.2.2.1.val = _root_.Submission.PC.word8 input r.2.2.2.1.val ∧ p.val ≤ r.1.val ⦄ := (by
  apply Std.WP.spec_mono (lazy1_loop_inv input lazy km p head lim pre_slot pre_c pre_w l d ins go
    p.val hlim hH ⟨hm, hB, hplim, hins, hps, hpc, hpw, le_refl _⟩)
  rintro ⟨p', head', ps', pc', pw', l', d', ins'⟩ ⟨hm', hB', hplim', hins', hps', hpc', hpw', hP'⟩
  exact ⟨hm', HeadBound.mono hB' (by have := hm'.1; omega), hplim', hins', hm'.1, hps', hpc',
    hpw', hP'⟩)
@[local step]
theorem tail1_loop1_spec (input : Slice Std.U8) (out : Slice Std.U32) (n nt p : Std.Usize)
    (hn : n.val = input.length) (hdec : _root_.Submission.PC.Dec input out nt.val p.val) :
    slot.pi1_run1_loop1 input out n nt p ⦃ fun r => r.1.val ≤ input.length ∧
      r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := C12582! slot.pi1_run1_loop1 slot.pi1_run1_loop1.body
@[local step]
theorem tail1_loop2_spec (input : Slice Std.U8) (out : Slice Std.U32) (n nt p : Std.Usize)
    (hn : n.val = input.length) (hdec : _root_.Submission.PC.Dec input out nt.val p.val) :
    slot.pi1_run1_loop2 input out n nt p ⦃ fun r => r.1.val ≤ input.length ∧
      r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := C12582! slot.pi1_run1_loop2 slot.pi1_run1_loop2.body
def MainInv1 (input : Slice Std.U8) (L : Nat) (out : Slice Std.U32) (nt ls p : Nat)
    {N : Std.Usize} (head : Array Std.U32 N) (miss ps pc pw : Nat) : Prop :=
  _root_.Submission.PC.Dec input out nt ls ∧ out.length = L ∧ ls ≤ p ∧ _root_.Submission.PC.HeadBound head p ∧ miss ≤ p ∧ ps < N.val ∧
    pc ≤ p ∧ pw = _root_.Submission.PC.word8 input pc
theorem MainInv1.mk' {input : Slice Std.U8} {L : Nat} {out : Slice Std.U32}
    {nt ls ls' p m B ps pc pw : Nat} {N : Std.Usize} {head : Array Std.U32 N}
    (hdec : _root_.Submission.PC.Dec input out nt ls') (hls : ls' = ls) (hlen : out.length = L) (hlsp : ls ≤ p)
    (hB : _root_.Submission.PC.HeadBound head B) (hBp : B ≤ p) (hm : m ≤ p) (hps : ps < N.val) (hpc : pc ≤ p)
    (hpw : pw = _root_.Submission.PC.word8 input pc) : MainInv1 input L out nt ls p head m ps pc pw := (by
  subst hls
  exact ⟨hdec, hlen, hlsp, HeadBound.mono hB hBp, hm, hps, hpc, hpw⟩)
set_option maxHeartbeats 16000000 in
theorem main1_loop_spec {H : Std.Usize} (input : Slice Std.U8) (out : Slice Std.U32)
    (skip lazy skcap : Std.Usize) (km : Std.U32) (nt ls p : Std.Usize) (head : Array Std.U32 H)
    (lim miss fuel pre_slot pre_c : Std.Usize) (pre_w : Std.U64) (L : Nat)
    (hlim : lim.val + 8 = input.length) (hskip : skip.val < 32) (hH : 0 < H.val)
    (hinv : MainInv1 input L out nt.val ls.val p.val head miss.val pre_slot.val pre_c.val
      pre_w.val) :
    slot.pi1_run1_loop0 input out skip lazy skcap km nt ls p head lim miss fuel pre_slot pre_c pre_w
      ⦃ fun r => _root_.Submission.PC.Dec input r.1 r.2.1.val r.2.2.val ∧ r.1.length = L ⦄ := (by
  rw [slot.pi1_run1_loop0]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  apply Std.loop.spec_decr_nat
    (measure := fun r => r.2.2.2.2.2.2.1.val)
    (inv := fun r => MainInv1 input L r.1 r.2.1.val r.2.2.1.val r.2.2.2.1.val r.2.2.2.2.1
      r.2.2.2.2.2.1.val r.2.2.2.2.2.2.2.1.val r.2.2.2.2.2.2.2.2.1.val r.2.2.2.2.2.2.2.2.2.val)
  · rintro ⟨out, nt, ls, p, head, miss, fuel, pre_slot, pre_c, pre_w⟩ hinv
    simp only at hinv
    have hinv' := hinv
    obtain ⟨hdec, hL, hlsp, hB, hmiss, hps, hpc, hpw⟩ := hinv'
    simp only [slot.pi1_run1_loop0.body]
    step*
    all_goals try (obtain ⟨i4, i5, i6⟩ := ae; dsimp only at *; step*)
    all_goals first
      | exact FoundAt.real (by assumption) (by first | assumption | omega | scalar_tac)
      | exact HeadBound.mono (by assumption) (by first | assumption | omega | scalar_tac)
      | (refine ⟨MainInv1.mk' (by assumption) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac)
          (by assumption) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac)
          (by assumption), by scalar_tac⟩)
  · exact hinv)
@[local step]
theorem main1_loop_spec' {H : Std.Usize} (input : Slice Std.U8) (out : Slice Std.U32)
    (skip lazy skcap : Std.Usize) (km : Std.U32) (nt ls p : Std.Usize) (head : Array Std.U32 H)
    (lim miss fuel pre_slot pre_c : Std.Usize) (pre_w : Std.U64)
    (hlim : lim.val + 8 = input.length) (hskip : skip.val < 32) (hH : 0 < H.val)
    (hdec : _root_.Submission.PC.Dec input out nt.val ls.val) (hlsp : ls.val ≤ p.val) (hB : _root_.Submission.PC.HeadBound head p.val)
    (hmiss : miss.val ≤ p.val) (hps : pre_slot.val < H.val) (hpc : pre_c.val ≤ p.val)
    (hpw : pre_w.val = _root_.Submission.PC.word8 input pre_c.val) :
    slot.pi1_run1_loop0 input out skip lazy skcap km nt ls p head lim miss fuel pre_slot pre_c pre_w
      ⦃ fun r => _root_.Submission.PC.Dec input r.1 r.2.1.val r.2.2.val ∧ r.1.length = out.length ⦄ :=
  main1_loop_spec input out skip lazy skcap km nt ls p head lim miss fuel pre_slot pre_c pre_w
    out.length hlim hskip hH ⟨hdec, rfl, hlsp, hB, hmiss, hps, hpc, hpw⟩
theorem run1_spec (H : Std.Usize) (input : Slice Std.U8) (out : Slice Std.U32)
    (skip lazy skcap : Std.Usize) (km : Std.U32) (hlen : input.length ≤ out.length) (hH : 0 < H.val)
    (hskip : skip.val < 32) :
    slot.pi1_run1 H input out skip lazy skcap km ⦃ fun r => r.1.val ≤ input.length ∧
      r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := (by
  rw [slot.pi1_run1]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  have hB0 : _root_.Submission.PC.HeadBound (Std.Array.repeat H 0#u32) 0 := HeadBound.init H
  have hdec0 : _root_.Submission.PC.Dec input out (0#usize).val (0#usize).val := Dec.init input out hlen
  step*)
@[local step]
abbrev f_link_spec := @_root_.Submission.PC.f_link_spec
theorem MatchAt.of_try {s : Slice Std.U8} {p c2 d2 i m : Std.Usize}
    (hd : d2 = core.num.Usize.wrapping_sub p c2) (hi : i = core.num.Usize.wrapping_sub d2 1#usize)
    (hlt : i < 32768#usize) (hmm : Matches s c2.val p.val m.val) (hc2 : c2.val ≤ p.val)
    (hm3 : 3 ≤ m.val) (hl : m.val ≤ 258) (hpl : p.val + m.val ≤ s.length) :
    _root_.Submission.PC.MatchAt s p.val m.val d2.val := (by
  obtain ⟨hdv, hd1, hd2⟩ := dist_of_wrapping hc2 hd hi hlt
  refine ⟨hm3, hl, hpl, hd1, hd2, by omega, ?_⟩
  rw [show p.val - d2.val = c2.val by omega]
  exact hmm)
@[local step]
abbrev f_try_spec := @_root_.Submission.PC.f_try_spec
@[local step]
abbrev f_deepen_spec := @_root_.Submission.PC.f_deepen_spec
end PI1
namespace PIM
abbrev word8 (input : Slice Std.U8) (p : Nat) : Nat := _root_.Submission.PC.word8 input p
abbrev HeadBound {N : Std.Usize} (head : Array Std.U32 N) (B : Nat) : Prop := _root_.Submission.PC.HeadBound head B
abbrev Cand (s : Slice Std.U8) (p cap best bd : Nat) : Prop := _root_.Submission.PC.Cand s p cap best bd
abbrev MatchAt (s : Slice Std.U8) (p l d : Nat) : Prop := _root_.Submission.PC.MatchAt s p l d
abbrev FoundAt (s : Slice Std.U8) (p l d : Nat) : Prop := _root_.Submission.PC.FoundAt s p l d
abbrev Dec (s : Slice Std.U8) (out : Slice Std.U32) (nt p : Nat) : Prop := _root_.Submission.PC.Dec s out nt p
abbrev BackInv (input : Slice Std.U8) (out : Slice Std.U32) (d E P0 : Nat) (nt p l : Nat) : Prop := _root_.Submission.PC.BackInv input out d E P0 nt p l
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
theorem tp_lift_spec {α : Type} (x : α) : lift x ⦃ fun y => y = x ⦄ := (by
  simp [lift, WP.spec_ok])
theorem tp_numBits_ge : 32 ≤ System.Platform.numBits := (by
  cases System.Platform.numBits_eq <;> simp [*])
@[local scalar_tac System.Platform.numBits]
theorem tp_numBits_ge' : 32 ≤ System.Platform.numBits := tp_numBits_ge
end TinyPath
theorem u8_lt (x : Std.U8) : x.val < 256 := by scalar_tac
theorem word8_digit (input : Slice Std.U8) (p k : Nat) (hk : k < 8) :
    (input.val[p + k]!).val = _root_.Submission.PC.word8 input p / 256 ^ (7 - k) % 256 := (by
  have := u8_lt (input.val[p]!); have := u8_lt (input.val[p+1]!)
  have := u8_lt (input.val[p+2]!); have := u8_lt (input.val[p+3]!)
  have := u8_lt (input.val[p+4]!); have := u8_lt (input.val[p+5]!)
  have := u8_lt (input.val[p+6]!); have := u8_lt (input.val[p+7]!)
  simp only [_root_.Submission.PC.word8]
  rcases (show k = 0 ∨ k = 1 ∨ k = 2 ∨ k = 3 ∨ k = 4 ∨ k = 5 ∨ k = 6 ∨ k = 7 by omega) with
    rfl | rfl | rfl | rfl | rfl | rfl | rfl | rfl <;> simp only [Nat.add_zero, Nat.pow_zero, Nat.pow_succ, Nat.one_mul,
    Nat.sub_self, Nat.reduceSub] <;> omega)
theorem word8_prefix (input : Slice Std.U8) (a b d : Nat) (hd : d ≤ 8)
    (h : _root_.Submission.PC.word8 input a / 2 ^ (64 - 8 * d) = _root_.Submission.PC.word8 input b / 2 ^ (64 - 8 * d)) :
    ∀ k, k < d → input.val[b + k]! = input.val[a + k]! := (by
  intro k hk
  have e : (256 : Nat) ^ (7 - k) = 2 ^ (64 - 8 * d) * 2 ^ (8 * (d - 1 - k)) := by
    rw [← pow_add, show (256 : Nat) = 2 ^ 8 by norm_num, ← pow_mul]
    congr 1; omega
  have key : _root_.Submission.PC.word8 input a / 256 ^ (7 - k) = _root_.Submission.PC.word8 input b / 256 ^ (7 - k) := by
    rw [e, ← Nat.div_div_eq_div_mul, ← Nat.div_div_eq_div_mul, h]
  have ha := word8_digit input a k (by omega)
  have hb := word8_digit input b k (by omega)
  rw [key] at ha
  scalar_tac)
theorem Matches.add_prefix {input : Slice Std.U8} {a b l d : Nat} (h : Matches input a b l)
    (hd : d ≤ 8)
    (hw : _root_.Submission.PC.word8 input (a + l) / 2 ^ (64 - 8 * d) = _root_.Submission.PC.word8 input (b + l) / 2 ^ (64 - 8 * d)) :
    Matches input a b (l + d) := (by
  intro k hk
  by_cases hkl : k < l
  · exact h k hkl
  · have := word8_prefix input (a + l) (b + l) d hd hw (k - l) (by omega)
    rw [show b + l + (k - l) = b + k by omega, show a + l + (k - l) = a + k by omega] at this
    exact this)
theorem or_eq_add_of_mod {x t : Nat} (m : Nat) (hx : x % 2 ^ m = 0) (ht : t < 2 ^ m) :
    x ||| t = x + t := (by
  have h := Nat.two_pow_add_eq_or_of_lt ht (x / 2 ^ m)
  have hx' : 2 ^ m * (x / 2 ^ m) = x := by
    have := Nat.div_add_mod x (2 ^ m); omega
  rw [hx'] at h
  exact h.symm)
theorem shl_byte {x : Nat} (k : Nat) (hx : x < 256) (hk : k ≤ 56) :
    x <<< k % U64.size = x * 2 ^ k := (by
  rw [Nat.shiftLeft_eq, U64.size_def]
  apply Nat.mod_eq_of_lt
  have : 2 ^ k ≤ 2 ^ 56 := Nat.pow_le_pow_right (by norm_num) hk
  have : x * 2 ^ k < 256 * 2 ^ 56 := by
    calc x * 2 ^ k < 256 * 2 ^ k := by
          apply Nat.mul_lt_mul_of_pos_right hx (Nat.two_pow_pos _)
      _ ≤ 256 * 2 ^ 56 := Nat.mul_le_mul_left _ this
  simp only [U64.numBits] at *
  omega)
theorem be8_nat {a b c d e f g h : Nat} (ha : a < 256) (hb : b < 256) (hc : c < 256)
    (hd : d < 256) (he : e < 256) (hf : f < 256) (hg : g < 256) (hh : h < 256) :
    (a <<< 56 % U64.size ||| b <<< 48 % U64.size ||| c <<< 40 % U64.size |||
      d <<< 32 % U64.size ||| e <<< 24 % U64.size ||| f <<< 16 % U64.size |||
      g <<< 8 % U64.size ||| h) =
    a * 2^56 + b * 2^48 + c * 2^40 + d * 2^32 + e * 2^24 + f * 2^16 + g * 2^8 + h := C12529!
@[local step]
abbrev be8_spec := @_root_.Submission.PC.be8_spec
theorem nat_xor_eq_zero {a b : Nat} (h : a ^^^ b = 0) : a = b := (by
  have : a ^^^ (a ^^^ b) = b := by rw [← Nat.xor_assoc, Nat.xor_self, Nat.zero_xor]
  rw [h, Nat.xor_zero] at this; exact this)
theorem div_eq_of_xor_lt {x y m : Nat} (hz : x ^^^ y < 2 ^ m) : x / 2 ^ m = y / 2 ^ m := (by
  have h : (x ^^^ y) >>> m = 0 := by rw [Nat.shiftRight_eq_div_pow]; exact Nat.div_eq_of_lt hz
  rw [Nat.shiftRight_xor_distrib] at h
  have := nat_xor_eq_zero h
  simpa [Nat.shiftRight_eq_div_pow] using this)
theorem lt_pow_leadingZeros (z : BitVec 64) :
    z.toNat < 2 ^ (64 - 8 * (BitVec.leadingZeros z / 8)) := (by
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
theorem leadingZeros_lt_of_ne (z : BitVec 64) (h : z ≠ 0) : BitVec.leadingZeros z < 64 := (by
  unfold BitVec.leadingZeros
  simp only [h, if_false]
  omega)
@[local step]
theorem lz_spec (x : Std.U64) :
    lift (core.num.U64.leading_zeros x) ⦃ fun r => r = core.num.U64.leading_zeros x ∧ r.val ≤ 64 ⦄ := (by
  simp only [lift, Std.WP.spec_ok, true_and]
  have hle : BitVec.leadingZeros x.bv ≤ 64 := by unfold BitVec.leadingZeros; split <;> omega
  simp only [core.num.U64.leading_zeros, UScalar.val, UScalarTy.U32_numBits_eq,
    BitVec.natCast_eq_ofNat, BitVec.toNat_ofNat, Nat.reducePow]
  omega)
theorem lz_val (x : Std.U64) :
    (core.num.U64.leading_zeros x).val = BitVec.leadingZeros x.bv := (by
  have hle : BitVec.leadingZeros x.bv ≤ 64 := by unfold BitVec.leadingZeros; split <;> omega
  simp only [core.num.U64.leading_zeros, UScalar.val, UScalarTy.U32_numBits_eq,
    BitVec.natCast_eq_ofNat, BitVec.toNat_ofNat, Nat.reducePow]
  omega)
theorem Matches.word_lz {input : Slice Std.U8} {a b k : Nat} {pa pb r k1 : Std.Usize}
    {x y z : Std.U64} {lz q : Std.U32}
    (h : Matches input a b k) (hpa : pa.val = a + k) (hpb : pb.val = b + k)
    (hx : x.val = _root_.Submission.PC.word8 input pa.val) (hy : y.val = _root_.Submission.PC.word8 input pb.val)
    (hz : z.val = (x ^^^ y).val) (hz0 : ¬z = 0#u64) (hlz : lz = core.num.U64.leading_zeros z)
    (hq : q.val = lz.val / 8) (hr : r = UScalar.cast .Usize q) (hk1 : k1.val = k + r.val) :
    Matches input a b k1.val ∧ k1.val < k + 8 := (by
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
theorem Matches.word_zero {input : Slice Std.U8} {a b k : Nat} {pa pb k1 : Std.Usize}
    {x y z : Std.U64}
    (h : Matches input a b k) (hpa : pa.val = a + k) (hpb : pb.val = b + k)
    (hx : x.val = _root_.Submission.PC.word8 input pa.val) (hy : y.val = _root_.Submission.PC.word8 input pb.val)
    (hz : z.val = (x ^^^ y).val) (hz0 : z = 0#u64) (hk1 : k1.val = k + 8) :
    Matches input a b k1.val := (by
  have hxy : x.val = y.val := by
    apply nat_xor_eq_zero
    rw [← UScalar.val_xor, ← hz, hz0]; rfl
  rw [hpa] at hx; rw [hpb] at hy
  rw [hk1]
  apply Matches.add_prefix h (le_refl 8)
  rw [← hx, ← hy, hxy])
theorem Matches.byte' {input : Slice Std.U8} {a b l : Nat} {pa pb l1 : Std.Usize}
    {x y : Std.U8} (h : Matches input a b l) (hpa : pa.val = a + l) (hpb : pb.val = b + l)
    (hpa' : pa.val < input.val.length) (hpb' : pb.val < input.val.length)
    (hx : x = input.val[pa.val]) (hy : y = input.val[pb.val]) (hxy : x = y)
    (hl1 : l1.val = l + 1) : Matches input a b l1.val := (by
  rw [hl1]
  apply LZ77.Matches.succ h
  rw [← hpa, ← hpb, getElem!_pos input.val pa.val hpa', getElem!_pos input.val pb.val hpb',
    ← hx, ← hy, hxy])
theorem wadd_val {x y z : Std.Usize} (hz : z = core.num.Usize.wrapping_add x y)
    (hb : x.val + y.val ≤ Std.Usize.max) : z.val = x.val + y.val := (by
  have hlt : x.val + y.val < Usize.size := by scalar_tac
  rw [hz, core.num.Usize.wrapping_add_val_eq, UScalar.size_UScalarTyUsize, Nat.mod_eq_of_lt hlt])
theorem wadd_le {x y z : Std.Usize} {m n : Nat} (hz : z = core.num.Usize.wrapping_add x y)
    (h : x.val + y.val + m ≤ n) (hn : n ≤ Std.Usize.max) : z.val + m ≤ n := (by
  rw [wadd_val hz (by omega)]; exact h)
@[local step]
abbrev xor8_spec := @_root_.Submission.PC.xor8_spec
theorem Matches.lz_any {input : Slice Std.U8} {a b k : Nat} {r k1 : Std.Usize} {z : Std.U64}
    {lz q : Std.U32} (h : Matches input a b k)
    (hz : z.val = _root_.Submission.PC.word8 input (a + k) ^^^ _root_.Submission.PC.word8 input (b + k))
    (hlz : lz = core.num.U64.leading_zeros z) (hq : q.val = lz.val / 8)
    (hr : r = UScalar.cast .Usize q) (hk1 : k1.val = k + r.val) :
    Matches input a b k1.val ∧ k1.val ≤ k + 8 := (by
  have hle : BitVec.leadingZeros z.bv ≤ 64 := by unfold BitVec.leadingZeros; split <;> omega
  have hrv : r.val = BitVec.leadingZeros z.bv / 8 := by
    rw [hr, U32.cast_Usize_val_eq, hq, hlz, lz_val]
  refine ⟨?_, by omega⟩
  rw [hk1, hrv]
  apply Matches.add_prefix h (by omega)
  apply div_eq_of_xor_lt
  rw [← hz]
  exact lt_pow_leadingZeros z.bv)
theorem Matches.xz {input : Slice Std.U8} {a b : Nat} {z : Std.U64}
    (hz : z.val = _root_.Submission.PC.word8 input a ^^^ _root_.Submission.PC.word8 input b) (hz0 : z = 0#u64) :
    Matches input a b 8 := (by
  have hv : _root_.Submission.PC.word8 input a ^^^ _root_.Submission.PC.word8 input b = 0 := by rw [← hz, hz0]; rfl
  have hab := nat_xor_eq_zero hv
  have := Matches.add_prefix (LZ77.Matches.zero input a b) (le_refl 8)
    (by simp only [Nat.add_zero]; rw [hab])
  simpa using this)
theorem xval_of {x cw y : Std.U64} {A B : Nat} (hx : x.val = (cw ^^^ y).val) (hcw : cw.val = A)
    (hy : y.val = B) : x.val = A ^^^ B := by
  rw [hx, UScalar.val_xor, hcw, hy]
theorem Matches.xw_step {input : Slice Std.U8} {a b k pa pb k1 r : Std.Usize} {z : Std.U64}
    {lz q : Std.U32} (h : Matches input a.val b.val k.val)
    (hpa : pa = core.num.Usize.wrapping_add a k) (hpb : pb = core.num.Usize.wrapping_add b k)
    (hab : a.val + k.val + 8 ≤ input.length ∧ b.val + k.val + 8 ≤ input.length)
    (hz : z.val = _root_.Submission.PC.word8 input pa.val ^^^ _root_.Submission.PC.word8 input pb.val)
    (hlz : lz = core.num.U64.leading_zeros z) (hq : q.val = lz.val / 8)
    (hr : r = UScalar.cast .Usize q) (hk1 : k1.val = k.val + r.val) :
    Matches input a.val b.val k1.val ∧ k1.val ≤ k.val + 8 := (by
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  rw [wadd_val hpa (by omega), wadd_val hpb (by omega)] at hz
  exact Matches.lz_any h hz hlz hq hr hk1)
theorem Matches.xw_zero {input : Slice Std.U8} {a b k pa pb k1 : Std.Usize} {z : Std.U64}
    (h : Matches input a.val b.val k.val)
    (hpa : pa = core.num.Usize.wrapping_add a k) (hpb : pb = core.num.Usize.wrapping_add b k)
    (hab : a.val + k.val + 8 ≤ input.length ∧ b.val + k.val + 8 ≤ input.length)
    (hz : z.val = _root_.Submission.PC.word8 input pa.val ^^^ _root_.Submission.PC.word8 input pb.val) (hz0 : z = 0#u64)
    (hk1 : k1.val = k.val + 8) : Matches input a.val b.val k1.val := (by
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
theorem Matches.word_eq {input : Slice Std.U8} {a b k : Nat} {pa pb k1 : Std.Usize}
    {x y : Std.U64}
    (h : Matches input a b k) (hpa : pa.val = a + k) (hpb : pb.val = b + k)
    (hx : x.val = _root_.Submission.PC.word8 input pa.val) (hy : y.val = _root_.Submission.PC.word8 input pb.val)
    (hxy : x = y) (hk1 : k1.val = k + 8) :
    Matches input a b k1.val := (by
  rw [hpa] at hx; rw [hpb] at hy
  rw [hk1]
  apply Matches.add_prefix h (le_refl 8)
  rw [← hx, ← hy, hxy])
abbrev same_loop0_spec := @_root_.Submission.PC.same_loop0_spec
@[local step]
abbrev same_loop1_spec := @_root_.Submission.PC.same_loop1_spec
@[local step]
abbrev same_loop2_spec := @_root_.Submission.PC.same_loop2_spec
theorem Matches.mask {input : Slice Std.U8} {a b k len : Nat} {pa pb : Std.Usize}
    {x y z w : Std.U64} {sh : Std.U32}
    (h : Matches input a b k) (hpa : pa.val = a + k) (hpb : pb.val = b + k)
    (hx : x.val = _root_.Submission.PC.word8 input pa.val) (hy : y.val = _root_.Submission.PC.word8 input pb.val)
    (hz : z.val = (x ^^^ y).val) (hw : w.val = z.val >>> sh.val) (hw0 : ¬(w != 0#u64) = true)
    (hsh : sh.val = 64 - 8 * (len - k)) (hk : k < len) (hlen : len < k + 8) :
    Matches input a b len := (by
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
@[local step]
abbrev same_spec := @_root_.Submission.PC.same_spec
theorem lz32_le (x : Std.U32) (k : Nat) (hk : k < 32) (hx : 2 ^ k ≤ x.val) :
    (core.num.U32.leading_zeros x).val ≤ 31 - k := C12546!
@[local step]
theorem lz32_spec (x : Std.U32) :
    lift (core.num.U32.leading_zeros x) ⦃ fun r => r = core.num.U32.leading_zeros x ∧
      (4 ≤ x.val → r.val ≤ 29) ∧ (8 ≤ x.val → r.val ≤ 28) ⦄ := (by
  simp only [lift, Std.WP.spec_ok, true_and]
  exact ⟨fun h => lz32_le x 2 (by norm_num) (by simpa using h),
    fun h => lz32_le x 3 (by norm_num) (by simpa using h)⟩)
@[local step]
theorem hcast_I32_spec {ty : UScalarTy} (x : UScalar ty) (h : x.val ≤ 2147483647) :
    lift (UScalar.hcast .I32 x) ⦃ fun y => y.val = x.val ⦄ :=
  UScalar.hcast_inBounds_spec .I32 x (by simp [I32.max_def, I32.numBits]; omega)
theorem GBASE_bound : -1000000000 ≤ slot.pim_GBASE.val ∧ slot.pim_GBASE.val ≤ 1000000000 := by
  unfold slot.pim_GBASE
  simp
@[local step]
abbrev gain_spec := @_root_.Submission.PC.gain_spec
theorem HeadBound.mono {N : Std.Usize} {head : Array Std.U32 N} {B B' : Nat}
    (h : _root_.Submission.PC.HeadBound head B) (hB : B ≤ B') : _root_.Submission.PC.HeadBound head B' := fun j hj => le_trans (h j hj) hB
theorem HeadBound.init (N : Std.Usize) : _root_.Submission.PC.HeadBound (Std.Array.repeat N 0#u32) 0 := (by
  intro j hj
  rw [Std.Array.repeat_val] at hj ⊢
  rw [List.getElem!_eq_getElem?_getD, List.getElem?_replicate_of_lt (by simpa using hj)]
  rfl)
theorem HeadBound.set {N : Std.Usize} {head : Array Std.U32 N} {B : Nat} (h : _root_.Submission.PC.HeadBound head B)
    (a : Std.Usize) (v : Std.U32) (hv : v.val ≤ B) : _root_.Submission.PC.HeadBound (head.set a v) B := (by
  intro j hj
  rw [Std.Array.set_val_eq] at hj ⊢
  rw [List.length_set] at hj
  by_cases hja : a.val = j
  · subst hja
    rw [List.getElem!_eq_getElem?_getD, List.getElem?_set_self hj]
    exact hv
  · rw [List.getElem!_eq_getElem?_getD, List.getElem?_set_ne hja, ← List.getElem!_eq_getElem?_getD]
    exact h j hj)
theorem HeadBound.update {N : Std.Usize} {head head1 : Array Std.U32 N} {B : Nat}
    {a i : Std.Usize} {v : Std.U32} (h : _root_.Submission.PC.HeadBound head B) (hv : v = UScalar.cast .U32 i)
    (hi : i.val ≤ B) (h1 : head1 = head.set a v) : _root_.Submission.PC.HeadBound head1 B := (by
  subst h1
  apply HeadBound.set h a v
  rw [hv]
  have : (UScalar.cast .U32 i).val = i.val % 2 ^ 32 := by
    simp only [UScalar.cast_val_eq, UScalarTy.U32_numBits_eq]
  rw [this]
  exact le_trans (Nat.mod_le _ _) hi)
theorem HeadBound.get {N : Std.Usize} {head : Array Std.U32 N} {B : Nat} (h : _root_.Submission.PC.HeadBound head B)
    (a : Std.Usize) (x : Std.U32) (ha : a.val < head.val.length) (hx : x = head.val[a.val]) :
    x.val ≤ B := (by
  have := h a.val ha
  rw [getElem!_pos head.val a.val ha, ← hx] at this
  exact this)
theorem cast_usize_le {x : Std.U32} {y : Std.Usize} {B : Nat} (h : y = UScalar.cast .Usize x)
    (hx : x.val ≤ B) : y.val ≤ B := (by
  rw [h, U32.cast_Usize_val_eq]; exact hx)
@[local step]
abbrev be4_spec := @_root_.Submission.PC.be4_spec
theorem dist_of_wrapping {p c d i : Std.Usize} (hc : c.val ≤ p.val)
    (hd : d = core.num.Usize.wrapping_sub p c) (hi : i = core.num.Usize.wrapping_sub d 1#usize)
    (hlt : i < 32768#usize) : d.val = p.val - c.val ∧ 1 ≤ d.val ∧ d.val ≤ 32768 := C12553!
theorem Cand.of_common {s : Slice Std.U8} {p c d i l cap : Std.Usize} (hc : c.val ≤ p.val)
    (hd : d = core.num.Usize.wrapping_sub p c) (hi : i = core.num.Usize.wrapping_sub d 1#usize)
    (hlt : i < 32768#usize) (hl : l.val ≤ cap.val) (hm : Matches s c.val p.val l.val) :
    _root_.Submission.PC.Cand s p.val cap.val l.val d.val := (by
  obtain ⟨hdv, hd1, hd2⟩ := dist_of_wrapping hc hd hi hlt
  refine Or.inr ⟨hd1, hd2, by omega, hl, ?_⟩
  rw [show p.val - d.val = c.val by omega]
  exact hm)
theorem FoundAt.of_cand {s : Slice Std.U8} {p cap : Nat} {l d : Std.Usize}
    (hc : _root_.Submission.PC.Cand s p cap l.val d.val) (hd : ¬d = 0#usize) (hcap : cap ≤ 258)
    (hpl : p + l.val ≤ s.length) : _root_.Submission.PC.FoundAt s p l.val d.val := (by
  have hd' : d.val ≠ 0 := by intro h; apply hd; exact UScalar.eq_of_val_eq (by simp [h])
  rcases hc with h0 | ⟨hd1, hd2, hdp, hl, hm⟩
  · exact absurd h0 hd'
  · rcases Nat.lt_or_ge l.val 3 with h3 | h3
    · exact Or.inl h3
    · exact Or.inr ⟨h3, by omega, hpl, hd1, hd2, hdp, hm⟩)
theorem Cand.len_le {s : Slice Std.U8} {p cap : Nat} {l d : Std.Usize}
    (hc : _root_.Submission.PC.Cand s p cap l.val d.val) (hd : ¬d = 0#usize) (hcap : cap ≤ 258) : l.val ≤ 258 := (by
  have hd' : d.val ≠ 0 := by intro h; apply hd; exact UScalar.eq_of_val_eq (by simp [h])
  rcases hc with h0 | ⟨_, _, _, hl, _⟩
  · exact absurd h0 hd'
  · omega)
theorem Cand.dist_le {s : Slice Std.U8} {p cap l d : Nat} (hc : _root_.Submission.PC.Cand s p cap l d) :
    d ≤ 32768 := (by
  rcases hc with h0 | ⟨_, hd, _⟩ <;> omega)
theorem FoundAt.none (s : Slice Std.U8) (p : Nat) : _root_.Submission.PC.FoundAt s p (0#usize).val (0#usize).val :=
  Or.inl (by simp)
theorem FoundAt.real {s : Slice Std.U8} {p l d : Nat} (hf : _root_.Submission.PC.FoundAt s p l d) (h3 : 3 ≤ l) :
    _root_.Submission.PC.MatchAt s p l d := (by
  rcases hf with h | h
  · omega
  · exact h)
theorem copyN_take_prefix (acc : List Nat) (d : Nat) :
    ∀ n, (copyN acc d n).take acc.length = acc := (by
  intro n
  induction n with
  | zero => simp [copyN]
  | succ m ih =>
    simp only [copyN]
    rw [List.take_append_of_le_length (by simp)]
    exact ih)
theorem foldlM_emit_length : ∀ (ts : List Nat) (init acc : List Nat),
    ts.foldlM emit init = some acc → init.length + ts.length ≤ acc.length := C12560!
theorem decode_length_le {ts acc : List Nat} (h : decode ts = some acc) :
    ts.length ≤ acc.length := (by
  have := foldlM_emit_length ts [] acc h
  simpa using this)
theorem decode_pop_lit {ts : List Nat} {t : Nat} {inp : List Nat} {p : Nat}
    (hp : p ≤ inp.length) (hd : decode (ts ++ [t]) = some (inp.take p)) (ht : t < 256) :
    1 ≤ p ∧ decode ts = some (inp.take (p - 1)) := (by
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
theorem decode_pop_match {ts : List Nat} {t : Nat} {inp : List Nat} {p : Nat}
    (hp : p ≤ inp.length) (hd : decode (ts ++ [t]) = some (inp.take p)) (ht : 256 ≤ t) :
    tokLen t ≤ p ∧ decode ts = some (inp.take (p - tokLen t)) := C12563!
theorem toks_pop (out : Slice Std.U32) (nt : Nat) (h0 : 0 < nt) (hle : nt ≤ out.length) :
    toks out nt = toks out (nt - 1) ++ [(out.val[nt - 1]!).val] := (by
  have hlt : nt - 1 < out.val.length := by
    have : out.length = out.val.length := rfl
    omega
  simp only [toks]
  conv_lhs => rw [show nt = (nt - 1) + 1 by omega]
  rw [List.take_add_one, List.getElem?_eq_getElem hlt, Option.toList_some, List.map_append]
  simp [getElem!_pos out.val (nt - 1) hlt])
theorem toks_length (out : Slice Std.U32) (nt : Nat) (h : nt ≤ out.length) :
    (toks out nt).length = nt := (by
  simp only [toks, List.length_map, List.length_take]
  have : out.length = out.val.length := rfl
  omega)
theorem Dec.init (input : Slice Std.U8) (out : Slice Std.U32) (h : input.length ≤ out.length) :
    _root_.Submission.PC.Dec input out (0#usize).val (0#usize).val :=
  ⟨by simp, by simp, h, by simp [toks, LZ77.decode]⟩
theorem Dec.lit {s : Slice Std.U8} {out : Slice Std.U32} {nt p : Nat} (h : _root_.Submission.PC.Dec s out nt p)
    (hp : p < s.length) (ntU : Std.Usize) (hnt : ntU.val = nt) (v : Std.U32)
    (hv : v.val = (s.val[p]!).val) :
    _root_.Submission.PC.Dec s (out.set ntU v) (nt + 1) (p + 1) := (by
  obtain ⟨hps, hntp, hso, hde⟩ := h
  have hntl : ntU.val < out.length := by omega
  refine ⟨by omega, by omega, by rw [Std.Slice.set_length]; exact hso, ?_⟩
  rw [← hnt]
  refine emit_lit s out ntU p v (by rw [hnt]; exact hde) hp hntl ?_
  have hpl : p < s.val.length := hp
  rw [hv, bytes_getElem! s p hpl, getElem!_pos s.val p hpl])
theorem Dec.match {s : Slice Std.U8} {out : Slice Std.U32} {nt p l d : Nat} (h : _root_.Submission.PC.Dec s out nt p)
    (hm : _root_.Submission.PC.MatchAt s p l d) (ntU : Std.Usize) (hnt : ntU.val = nt) (v : Std.U32)
    (hv : v.val = LZ77.mkMatch d l) :
    _root_.Submission.PC.Dec s (out.set ntU v) (nt + 1) (p + l) := (by
  obtain ⟨hps, hntp, hso, hde⟩ := h
  obtain ⟨h3, h258, hpl, hd1, hd32, hdp, hmm⟩ := hm
  have hntl : ntU.val < out.length := by omega
  refine ⟨by omega, by omega, by rw [Std.Slice.set_length]; exact hso, ?_⟩
  rw [← hnt]
  exact emit_match s out ntU p d l v (by rw [hnt]; exact hde) hntl hd1 hdp hd32 h3 h258 hpl hmm hv)
theorem Dec.pop_lit {s : Slice Std.U8} {out : Slice Std.U32} {nt p : Nat} (h : _root_.Submission.PC.Dec s out nt p)
    (h0 : 0 < nt) (hle : nt ≤ out.length) (ht : (out.val[nt - 1]!).val < 256) :
    1 ≤ p ∧ _root_.Submission.PC.Dec s out (nt - 1) (p - 1) := (by
  obtain ⟨hps, hntp, hso, hde⟩ := h
  rw [toks_pop out nt h0 hle] at hde
  obtain ⟨hp1, hde'⟩ := decode_pop_lit (by simpa using hps) hde ht
  exact ⟨hp1, by omega, by omega, hso, hde'⟩)
theorem Dec.pop_match {s : Slice Std.U8} {out : Slice Std.U32} {nt p : Nat} (h : _root_.Submission.PC.Dec s out nt p)
    (h0 : 0 < nt) (hle : nt ≤ out.length) (ht : 256 ≤ (out.val[nt - 1]!).val) :
    tokLen (out.val[nt - 1]!).val ≤ p ∧
      _root_.Submission.PC.Dec s out (nt - 1) (p - tokLen (out.val[nt - 1]!).val) := (by
  obtain ⟨hps, hntp, hso, hde⟩ := h
  rw [toks_pop out nt h0 hle] at hde
  obtain ⟨hw, hde'⟩ := decode_pop_match (by simpa using hps) hde ht
  have hlen := decode_length_le hde'
  rw [toks_length out (nt - 1) (by omega), List.length_take, bytes_length] at hlen
  exact ⟨hw, by omega, by omega, hso, hde'⟩)
theorem Dec.done {s : Slice Std.U8} {out : Slice Std.U32} {nt p : Nat} (h : _root_.Submission.PC.Dec s out nt p)
    (hp : s.length ≤ p) : nt ≤ s.length ∧ LZ77.Valid (bytes s) (toks out nt) := (by
  obtain ⟨hps, hntp, hso, hde⟩ := h
  refine ⟨by omega, ?_⟩
  unfold LZ77.Valid
  rw [hde, show p = s.length by omega, ← bytes_length, List.take_length])
theorem Dec.lit_step {s : Slice Std.U8} {out out1 : Slice Std.U32} {ntU nt1 pU : Std.Usize}
    {b : Std.U8} {v : Std.U32} (h : _root_.Submission.PC.Dec s out ntU.val pU.val) (hp : pU.val < s.val.length)
    (hb : b = s.val[pU.val]) (hv : v = UScalar.cast .U32 b) (hout1 : out1 = out.set ntU v)
    (hnt1 : nt1.val = ntU.val + 1) :
    nt1.val = ntU.val + 1 ∧ out1.length = out.length ∧ _root_.Submission.PC.Dec s out1 nt1.val (pU.val + 1) := (by
  subst hout1
  refine ⟨hnt1, Std.Slice.set_length .., ?_⟩
  rw [hnt1]
  exact Dec.lit h hp ntU rfl v (by rw [hv, U8.cast_U32_val_eq, hb, getElem!_pos s.val pU.val hp]))
@[local step]
abbrev put_lit_spec := @_root_.Submission.PC.put_lit_spec
theorem Dec.match_step {s : Slice Std.U8} {out out1 : Slice Std.U32} {ntU nt1 pU dU lU e : Std.Usize}
    {v : Std.U32} (h : _root_.Submission.PC.Dec s out ntU.val pU.val) (hm : _root_.Submission.PC.MatchAt s pU.val lU.val dU.val)
    (hout1 : out1 = out.set ntU v) (hv : v.val = LZ77.mkMatch dU.val lU.val)
    (hnt1 : nt1.val = ntU.val + 1) (he : e.val = pU.val + lU.val) :
    nt1.val = ntU.val + 1 ∧ e.val = pU.val + lU.val ∧ out1.length = out.length ∧
      _root_.Submission.PC.Dec s out1 nt1.val e.val := (by
  subst hout1
  refine ⟨hnt1, he, Std.Slice.set_length .., ?_⟩
  rw [hnt1, he]
  exact Dec.match h hm ntU rfl v hv)
@[local step]
abbrev put_match_spec := @_root_.Submission.PC.put_match_spec
@[local step]
abbrev put_match_checked_spec := @_root_.Submission.PC.put_match_checked_spec
@[local step]
abbrev put_match_wrapped_spec := @_root_.Submission.PC.put_match_wrapped_spec
@[local step]
abbrev put_match_h_spec := @_root_.Submission.PC.put_match_h_spec
theorem MatchAt.back_lit {s : Slice Std.U8} {p l d : Nat} (h : _root_.Submission.PC.MatchAt s p l d) (hl : l < 258)
    (hdp : d < p) (heq : s.val[p - 1]! = s.val[p - 1 - d]!) : _root_.Submission.PC.MatchAt s (p - 1) (l + 1) d := (by
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
theorem MatchAt.back_match {s : Slice Std.U8} {p l d w : Nat} (h : _root_.Submission.PC.MatchAt s p l d)
    (hlw : l + w ≤ 258) (hw : w ≤ p) (hdw : d ≤ p - w) (hmw : Matches s (p - w - d) (p - w) w) :
    _root_.Submission.PC.MatchAt s (p - w) (l + w) d := (by
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
theorem BackInv.lit {input : Slice Std.U8} {out : Slice Std.U32} {d E P0 : Nat}
    {nt p l i1 i2 i4 l1 : Std.Usize} {t : Std.U32} {x y : Std.U8}
    (h : _root_.Submission.PC.BackInv input out d E P0 nt.val p.val l.val)
    (hi1 : i1.val = nt.val - 1) (hntl : nt.val ≤ out.length) (hnt0 : 1 ≤ nt.val)
    (hi1l : i1.val < out.val.length) (ht : t = out.val[i1.val]) (ht256 : t < 256#u32)
    (hi2 : i2.val = p.val - 1) (hi2l : i2.val < input.val.length) (hx : x = input.val[i2.val])
    (hxy : x = y) (hi4 : i4.val = i2.val - d) (hi4l : i4.val < input.val.length)
    (hy : y = input.val[i4.val]) (hl : l.val < 258) (hdp : d < p.val)
    (hl1 : l1.val = l.val + 1) :
    _root_.Submission.PC.BackInv input out d E P0 i1.val i2.val l1.val := (by
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
theorem BackInv.match {input : Slice Std.U8} {out : Slice Std.U32} {d E P0 : Nat}
    {nt p l i1 w i9 i10 i11 i12 : Std.Usize} {t : Std.U32}
    (h : _root_.Submission.PC.BackInv input out d E P0 nt.val p.val l.val)
    (hi1 : i1.val = nt.val - 1) (hntl : nt.val ≤ out.length) (hnt0 : 1 ≤ nt.val)
    (hi1l : i1.val < out.val.length) (ht : t = out.val[i1.val])
    (hsame : i12.val = 1 → Matches input i11.val i10.val w.val) (hi12 : i12 = 1#usize)
    (ht24 : 16777216 ≤ t.val) (hwv : w.val = (t.val - 16777216) % 256 + 3)
    (hi9 : i9.val = l.val + w.val) (hi9' : i9.val ≤ 258) (hi10 : i10.val = p.val - w.val)
    (hwp : w.val ≤ p.val) (hdw : d ≤ i10.val) (hi11 : i11.val = i10.val - d) :
    _root_.Submission.PC.BackInv input out d E P0 i1.val i10.val i9.val := C12577!
abbrev fold_loop_inv := @_root_.Submission.PC.fold_loop_inv
@[local step]
abbrev fold_spec := @_root_.Submission.PC.fold_spec
@[local step]
abbrev fold_w_spec := @_root_.Submission.PC.fold_w_spec
def LazyInv (input : Slice Std.U8) (L lim : Nat) (out : Slice Std.U32) (nt p : Nat)
    {N : Std.Usize} (head : Array Std.U32 N) (ins l d : Nat) : Prop :=
  _root_.Submission.PC.Dec input out nt p ∧ out.length = L ∧ _root_.Submission.PC.MatchAt input p l d ∧ _root_.Submission.PC.HeadBound head (p + 1) ∧
    p < lim ∧ ins ≤ p + 2
theorem LazyInv.accept {input : Slice Std.U8} {L lim p' B : Nat} {out1 : Slice Std.U32}
    {nt1 i ins1 l1 d1 minl : Std.Usize} {N : Std.Usize} {head1 : Array Std.U32 N}
    (hdec : _root_.Submission.PC.Dec input out1 nt1.val p') (hi : i.val = p') (hlen : out1.length = L)
    (hf : _root_.Submission.PC.FoundAt input i.val l1.val d1.val) (hl1 : minl.val ≤ l1.val) (hminl : 3 ≤ minl.val)
    (hB : _root_.Submission.PC.HeadBound head1 B) (hBi : B ≤ i.val + 1) (hilim : i.val < lim)
    (hins : ins1.val ≤ i.val + 2) :
    LazyInv input L lim out1 nt1.val i.val head1 ins1.val l1.val d1.val := (by
  subst hi
  refine ⟨hdec, hlen, ?_, HeadBound.mono hB hBi, hilim, hins⟩
  rcases hf with h | h
  · omega
  · exact h)
theorem LazyInv.reject {input : Slice Std.U8} {L lim : Nat} {out : Slice Std.U32}
    {nt p ins ins1 l d B : Nat} {N : Std.Usize} {head head1 : Array Std.U32 N}
    (h : LazyInv input L lim out nt p head ins l d) (hB : _root_.Submission.PC.HeadBound head1 B) (hBp : B ≤ p + 1)
    (hins1 : ins1 ≤ p + 2) : LazyInv input L lim out nt p head1 ins1 l d := (by
  obtain ⟨hdec, hlen, hm, _, hplim, _⟩ := h
  exact ⟨hdec, hlen, hm, HeadBound.mono hB hBp, hplim, hins1⟩)
theorem numBits_ge : 32 ≤ System.Platform.numBits := (by
  rcases System.Platform.numBits_eq with h | h <;> omega)
def MainInv (input : Slice Std.U8) (L : Nat) (out : Slice Std.U32) (nt p : Nat)
    {N : Std.Usize} (head : Array Std.U32 N) (miss : Nat) : Prop :=
  _root_.Submission.PC.Dec input out nt p ∧ out.length = L ∧ _root_.Submission.PC.HeadBound head p ∧ miss ≤ p
theorem MainInv.mk' {input : Slice Std.U8} {L : Nat} {out : Slice Std.U32} {nt p m B : Nat}
    {N : Std.Usize} {head : Array Std.U32 N} (hdec : _root_.Submission.PC.Dec input out nt p) (hlen : out.length = L)
    (hB : _root_.Submission.PC.HeadBound head B) (hBp : B ≤ p) (hm : m ≤ p) : MainInv input L out nt p head m :=
  ⟨hdec, hlen, HeadBound.mono hB hBp, hm⟩
def CntBound (cnt : Array Std.U32 256#usize) (T : Nat) : Prop :=
  ∀ j : Nat, j < 256 → (cnt.val[j]!).val ≤ T
theorem CntBound.init : CntBound (Std.Array.repeat 256#usize 0#u32) 0 := (by
  intro j hj
  rw [Std.Array.repeat_val, List.getElem!_eq_getElem?_getD,
    List.getElem?_replicate_of_lt (by simpa using hj)]
  rfl)
theorem CntBound.get {cnt : Array Std.U32 256#usize} {T : Nat} (h : CntBound cnt T)
    (a : Std.Usize) (x : Std.U32) (ha : a.val < cnt.val.length) (hx : x = cnt.val[a.val]) :
    x.val ≤ T := (by
  have := h a.val (by simpa using ha)
  rw [getElem!_pos cnt.val a.val ha, ← hx] at this
  exact this)
@[local step]
theorem cnt_index_spec (cnt : Array Std.U32 256#usize) (T : Nat) (h : CntBound cnt T)
    (i : Std.Usize) (hi : i.val < 256) :
    Std.Array.index_usize cnt i ⦃ fun x => x = cnt.val[i.val]! ∧ x.val ≤ T ⦄ := (by
  have hl : i.val < cnt.val.length := by simp; omega
  have := Std.Array.index_usize_spec cnt i (by simpa using hl)
  apply Std.WP.spec_mono this
  intro x hx
  refine ⟨by rw [getElem!_pos cnt.val i.val hl]; exact hx, CntBound.get h i x hl hx⟩)
theorem CntBound.update {cnt : Array Std.U32 256#usize} {T : Nat} (h : CntBound cnt T)
    (a : Std.Usize) (v : Std.U32) (hv : v.val ≤ T + 1) : CntBound (cnt.set a v) (T + 1) := (by
  intro j hj
  rw [Std.Array.set_val_eq]
  by_cases hja : a.val = j
  · subst hja
    have hlen : a.val < cnt.val.length := by simp; omega
    rw [List.getElem!_eq_getElem?_getD, List.getElem?_set_self hlen]
    exact hv
  · rw [List.getElem!_eq_getElem?_getD, List.getElem?_set_ne hja, ← List.getElem!_eq_getElem?_getD]
    exact le_trans (h j hj) (by omega))
theorem CntBound.step {cnt a : Array Std.U32 256#usize} {T : Nat} {x : Std.Usize}
    {v tot1 : Std.U32} (hc : CntBound cnt T) (ha : a = cnt.set x v) (hv : v.val ≤ T + 1)
    (ht1 : tot1.val = T + 1) : CntBound a tot1.val := (by
  rw [ha, ht1]
  exact CntBound.update hc x v hv)
theorem CntBound.mono {cnt : Array Std.U32 256#usize} {T T' : Nat} (h : CntBound cnt T)
    (hT : T ≤ T') : CntBound cnt T' := fun j hj => le_trans (h j hj) hT
@[local step]
theorem lift_spec {α : Type} (x : α) : lift x ⦃ fun y => y = x ⦄ := by
  simp [lift]
theorem Dec.cast {s : Slice Std.U8} {out : Slice Std.U32} {nt p p' : Nat} (h : _root_.Submission.PC.Dec s out nt p)
    (hp : p = p') : _root_.Submission.PC.Dec s out nt p' := hp ▸ h
@[local step]
theorem head_set_spec {H : Std.Usize} (head : Array Std.U32 H) (a i : Std.Usize) (B : Nat)
    (hB : _root_.Submission.PC.HeadBound head B) (ha : a.val < H.val) (hi : i.val < B + 1) :
    slot.pc_head_set head a i ⦃ fun r => _root_.Submission.PC.HeadBound r B ⦄ := by
  exact _root_.Submission.PC.head_set_spec head a i B hB ha hi
abbrev common_from_loop0_spec := @_root_.Submission.PC.common_from_loop0_spec
abbrev common_from_loop1_spec := @_root_.Submission.PC.common_from_loop1_spec
@[local step]
abbrev common_from_spec := @_root_.Submission.PC.common_from_spec
theorem Matches.xor_lz {s : Slice Std.U8} {c p m : Std.Usize} {cw y x : Std.U64}
    {lz q : Std.U32} (hcw : cw.val = _root_.Submission.PC.word8 s c.val) (hy : y.val = _root_.Submission.PC.word8 s p.val)
    (hx : x.val = (cw ^^^ y).val) (hx0 : (x != 0#u64) = true)
    (hlz : lz = core.num.U64.leading_zeros x) (hq : q.val = lz.val / 8)
    (hm : m = UScalar.cast .Usize q) : Matches s c.val p.val m.val ∧ m.val < 8 := (by
  have hx0' : ¬x = 0#u64 := by simpa using hx0
  have h := Matches.word_lz (k := 0) (k1 := m) (pa := c) (pb := p)
    (LZ77.Matches.zero s c.val p.val) (by simp) (by simp) hcw hy hx hx0' hlz hq hm (by simp)
  simpa using h)
theorem Matches.xor_zero {s : Slice Std.U8} {c p : Std.Usize} {cw y x : Std.U64}
    (hcw : cw.val = _root_.Submission.PC.word8 s c.val) (hy : y.val = _root_.Submission.PC.word8 s p.val)
    (hx : x.val = (cw ^^^ y).val) (hx0 : ¬(x != 0#u64) = true) :
    Matches s c.val p.val (8#usize).val := (by
  have hv : x.val = 0 := by simpa using hx0
  have hx0' : x = 0#u64 := UScalar.eq_of_val_eq (by simp [hv])
  exact Matches.word_zero (k := 0) (k1 := 8#usize) (pa := c) (pb := p)
    (LZ77.Matches.zero s c.val p.val) (by simp) (by simp) hcw hy hx hx0' (by simp))
theorem FoundAt.of_matches {s : Slice Std.U8} {p c d i l : Std.Usize} (hc : c.val ≤ p.val)
    (hd : d = core.num.Usize.wrapping_sub p c) (hi : i = core.num.Usize.wrapping_sub d 1#usize)
    (hlt : i < 32768#usize) (hl : l.val ≤ 258) (hpl : p.val + l.val ≤ s.length)
    (hm : Matches s c.val p.val l.val) :
    _root_.Submission.PC.FoundAt s p.val l.val d.val ∧ l.val ≤ 258 ∧ d.val ≤ 32768 := (by
  obtain ⟨hdv, hd1, hd2⟩ := dist_of_wrapping hc hd hi hlt
  refine ⟨?_, hl, hd2⟩
  rcases Nat.lt_or_ge l.val 3 with h3 | h3
  · exact Or.inl h3
  · refine Or.inr ⟨h3, hl, hpl, hd1, hd2, by omega, ?_⟩
    rw [show p.val - d.val = c.val by omega]
    exact hm)
theorem FoundAt.none' (s : Slice Std.U8) (p : Nat) :
    _root_.Submission.PC.FoundAt s p (0#usize).val (0#usize).val ∧ (0#usize).val ≤ 258 ∧ (0#usize).val ≤ 32768 :=
  ⟨FoundAt.none s p, by simp, by simp⟩
@[local step]
abbrev xlen_spec := @_root_.Submission.PC.xlen_spec
theorem Matches.x16a {s : Slice Std.U8} {c p i1 i2 r l : Std.Usize} {x x2 : Std.U64}
    {lz q : Std.U32} (hx : x.val = _root_.Submission.PC.word8 s c.val ^^^ _root_.Submission.PC.word8 s p.val) (hx0 : x = 0#u64)
    (hi1 : i1.val = c.val + 8) (hi2 : i2.val = p.val + 8)
    (hx2 : x2.val = _root_.Submission.PC.word8 s i1.val ^^^ _root_.Submission.PC.word8 s i2.val)
    (hlz : lz = core.num.U64.leading_zeros x2) (hq : q.val = lz.val / 8)
    (hr : r = UScalar.cast .Usize q) (hl : l.val = 8 + r.val) :
    Matches s c.val p.val l.val ∧ l.val ≤ 16 := (by
  have h8 := Matches.xz hx hx0
  rw [hi1, hi2] at hx2
  have := Matches.lz_any (k := 8) (k1 := l) h8 hx2 hlz hq hr (by omega)
  exact ⟨this.1, by omega⟩)
theorem Matches.x16a' {s : Slice Std.U8} {c p i1 i2 r l : Std.Usize} {x x2 : Std.U64}
    {lz q : Std.U32} (hx : x.val = _root_.Submission.PC.word8 s c.val ^^^ _root_.Submission.PC.word8 s p.val) (hx0 : x = 0#u64)
    (hi1 : i1.val = c.val + 8) (hi2 : i2.val = p.val + 8)
    (hx2 : x2.val = _root_.Submission.PC.word8 s i1.val ^^^ _root_.Submission.PC.word8 s i2.val)
    (hlz : lz = core.num.U64.leading_zeros x2) (hq : q.val = lz.val / 8)
    (hr : r = UScalar.cast .Usize q) (hl : l.val = 8 + r.val) (hpn : p.val + 16 ≤ s.length) :
    l.val ≤ 258 ∧ p.val + l.val ≤ s.length ∧ Matches s c.val p.val l.val := (by
  have h := Matches.x16a hx hx0 hi1 hi2 hx2 hlz hq hr hl
  exact ⟨by omega, by omega, h.1⟩)
theorem Matches.x16b {s : Slice Std.U8} {c p r l : Std.Usize} {x : Std.U64}
    {lz q : Std.U32} (hx : x.val = _root_.Submission.PC.word8 s c.val ^^^ _root_.Submission.PC.word8 s p.val)
    (hlz : lz = core.num.U64.leading_zeros x) (hq : q.val = lz.val / 8)
    (hr : r = UScalar.cast .Usize q) (hl : l.val = 0 + r.val) (hpn : p.val + 8 ≤ s.length) :
    l.val ≤ 258 ∧ p.val + l.val ≤ s.length ∧ Matches s c.val p.val l.val := (by
  have := Matches.lz_any (k := 0) (k1 := l) (LZ77.Matches.zero s c.val p.val)
    (by simpa using hx) hlz hq hr (by omega)
  exact ⟨by omega, by omega, this.1⟩)
@[local step]
abbrev xlen16_spec := @_root_.Submission.PC.xlen16_spec
@[local step]
abbrev lazy_lo_spec := @_root_.Submission.PC.lazy_lo_spec
@[local step]
abbrev probe_lazy_spec := @_root_.Submission.PC.probe_lazy_spec
@[local step]
abbrev skip_len_spec := @_root_.Submission.PC.skip_len_spec
@[local step]
abbrev skip_to_spec := @_root_.Submission.PC.skip_to_spec
@[local step]
abbrev slot_of_m_spec := @_root_.Submission.PC.slot_of_m_spec
@[local step]
theorem ahead_m_spec {H : Std.Usize} (s : Slice Std.U8) (head : Array Std.U32 H) (i : Std.Usize)
    (km : Std.U32) (B : Nat) (hB : _root_.Submission.PC.HeadBound head B) (hBn : B + 8 ≤ s.length)
    (hi4 : i.val + 4 ≤ Std.Usize.max) (hH : 0 < H.val) :
    slot.pc_ahead_m s head i km ⦃ fun r => r.1.val < H.val ∧ r.2.1.val ≤ B ∧
      r.2.2.val = _root_.Submission.PC.word8 s r.2.1.val ⦄ := by
  exact _root_.Submission.PC.ahead_m_spec s head i km B hB hBn hi4 hH
@[local step]
theorem ahead_if_m_spec {H : Std.Usize} (s : Slice Std.U8) (head : Array Std.U32 H)
    (i lim a c : Std.Usize) (w : Std.U64) (km : Std.U32) (B : Nat) (hB : _root_.Submission.PC.HeadBound head B)
    (hBi : B < i.val + 1) (hlim : lim.val + 8 = s.length) (ha : a.val < H.val)
    (hc : c.val < B + 1) (hw : w.val = _root_.Submission.PC.word8 s c.val) (hH : 0 < H.val) :
    slot.pc_ahead_if_m s head i lim a c w km ⦃ fun r => r.1.val < H.val ∧ r.2.1.val ≤ B ∧
      r.2.2.val = _root_.Submission.PC.word8 s r.2.1.val ⦄ := by
  exact _root_.Submission.PC.ahead_if_m_spec s head i lim a c w km B hB hBi hlim ha hc hw hH
@[local step]
theorem ahead_fix_m_spec {H : Std.Usize} (s : Slice Std.U8) (head : Array Std.U32 H)
    (i lim e a c : Std.Usize) (w : Std.U64) (a0 c0 : Std.Usize) (w0 : Std.U64) (km : Std.U32)
    (B : Nat) (hB : _root_.Submission.PC.HeadBound head B) (hBi : B < i.val + 1) (hlim : lim.val + 8 = s.length)
    (hw : w.val = _root_.Submission.PC.word8 s c.val) (ha0 : a0.val < H.val) (hc0 : c0.val < B + 1)
    (hw0 : w0.val = _root_.Submission.PC.word8 s c0.val) (hH : 0 < H.val) :
    slot.pc_ahead_fix_m s head i lim e a c w a0 c0 w0 km ⦃ fun r => r.1.val < H.val ∧
      r.2.1.val ≤ B ∧ r.2.2.val = _root_.Submission.PC.word8 s r.2.1.val ⦄ := by
  exact _root_.Submission.PC.ahead_fix_m_spec s head i lim e a c w a0 c0 w0 km B hB hBi hlim hw ha0 hc0 hw0 hH
@[local step]
abbrev probe_m_spec := @_root_.Submission.PC.probe_m_spec
abbrev flush_loop_spec := @_root_.Submission.PC.flush_loop_spec
@[local step]
abbrev flush_spec := @_root_.Submission.PC.flush_spec
theorem Dec.set_beyond {s : Slice Std.U8} {out : Slice Std.U32} {nt p : Nat} (h : _root_.Submission.PC.Dec s out nt p)
    (i : Std.Usize) (v : Std.U32) (hi : nt ≤ i.val) : _root_.Submission.PC.Dec s (out.set i v) nt p := (by
  obtain ⟨hps, hntp, hso, hde⟩ := h
  refine ⟨hps, hntp, by rw [Std.Slice.set_length]; exact hso, ?_⟩
  have : toks (out.set i v) nt = toks out nt := by
    simp only [toks, Std.Slice.set_val_eq, List.take_set]
    rw [List.set_eq_of_length_le (by rw [List.length_take]; omega)]
  rw [this]; exact hde)
theorem Dec.flush4_step {s : Slice Std.U8} {out out1 out2 out3 out4 : Slice Std.U32}
    {nt a e j r i7 i9 i11 i13 i15 i17 : Std.Usize} {b0 b1 b2 b3 : Std.U8}
    {v0 v1 v2 v3 : Std.U32}
    (h : _root_.Submission.PC.Dec s out nt.val a.val) (hae : a.val ≤ e.val) (hj : j.val = e.val - a.val)
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
    _root_.Submission.PC.Dec s out4 r.val e.val ∧ out4.length = out.length := C12598!
@[local step]
abbrev flush4_spec := @_root_.Submission.PC.flush4_spec
def LazyInv1 (input : Slice Std.U8) (lim P0 : Nat) (p : Nat) {N : Std.Usize}
    (head : Array Std.U32 N) (ps pc pw l d ins : Nat) : Prop :=
  _root_.Submission.PC.MatchAt input p l d ∧ _root_.Submission.PC.HeadBound head (p + 1) ∧ p < lim ∧ ins ≤ p + 2 ∧ ps < N.val ∧
    pc ≤ p + 1 ∧ pw = _root_.Submission.PC.word8 input pc ∧ P0 ≤ p
theorem LazyInv1.accept {input : Slice Std.U8} {lim P0 B : Nat}
    {i ins1 l1 d1 ps pc : Std.Usize} {pw : Std.U64} {N : Std.Usize} {head1 : Array Std.U32 N}
    (hf : _root_.Submission.PC.FoundAt input i.val l1.val d1.val) (hl1 : 3 ≤ l1.val)
    (hB : _root_.Submission.PC.HeadBound head1 B) (hBi : B ≤ i.val + 1) (hilim : i.val < lim)
    (hins : ins1.val ≤ i.val + 2) (hps : ps.val < N.val) (hpc : pc.val ≤ i.val + 1)
    (hpw : pw.val = _root_.Submission.PC.word8 input pc.val) (hP : P0 ≤ i.val) :
    LazyInv1 input lim P0 i.val head1 ps.val pc.val pw.val l1.val d1.val ins1.val :=
  ⟨FoundAt.real hf hl1, HeadBound.mono hB hBi, hilim, hins, hps, hpc, hpw, hP⟩
theorem LazyInv1.reject {input : Slice Std.U8} {lim P0 : Nat}
    {p ps pc pw l d ins B ps1 pc1 pw1 ins1 : Nat} {N : Std.Usize}
    {head head1 : Array Std.U32 N}
    (h : LazyInv1 input lim P0 p head ps pc pw l d ins) (hB : _root_.Submission.PC.HeadBound head1 B)
    (hBp : B ≤ p + 1) (hins1 : ins1 ≤ p + 2) (hps : ps1 < N.val) (hpc : pc1 ≤ p + 1)
    (hpw : pw1 = _root_.Submission.PC.word8 input pc1) :
    LazyInv1 input lim P0 p head1 ps1 pc1 pw1 l d ins1 := (by
  obtain ⟨hm, _, hplim, _, _, _, _, hP⟩ := h
  exact ⟨hm, HeadBound.mono hB hBp, hplim, hins1, hps, hpc, hpw, hP⟩)
def MainInv1 (input : Slice Std.U8) (L : Nat) (out : Slice Std.U32) (nt ls p : Nat)
    {N : Std.Usize} (head : Array Std.U32 N) (miss ps pc pw : Nat) : Prop :=
  _root_.Submission.PC.Dec input out nt ls ∧ out.length = L ∧ ls ≤ p ∧ _root_.Submission.PC.HeadBound head p ∧ miss ≤ p ∧ ps < N.val ∧
    pc ≤ p ∧ pw = _root_.Submission.PC.word8 input pc
theorem MainInv1.mk' {input : Slice Std.U8} {L : Nat} {out : Slice Std.U32}
    {nt ls ls' p m B ps pc pw : Nat} {N : Std.Usize} {head : Array Std.U32 N}
    (hdec : _root_.Submission.PC.Dec input out nt ls') (hls : ls' = ls) (hlen : out.length = L) (hlsp : ls ≤ p)
    (hB : _root_.Submission.PC.HeadBound head B) (hBp : B ≤ p) (hm : m ≤ p) (hps : ps < N.val) (hpc : pc ≤ p)
    (hpw : pw = _root_.Submission.PC.word8 input pc) : MainInv1 input L out nt ls p head m ps pc pw := (by
  subst hls
  exact ⟨hdec, hlen, hlsp, HeadBound.mono hB hBp, hm, hps, hpc, hpw⟩)
@[local step]
abbrev f_link_spec := @_root_.Submission.PC.f_link_spec
theorem MatchAt.of_try {s : Slice Std.U8} {p c2 d2 i m : Std.Usize}
    (hd : d2 = core.num.Usize.wrapping_sub p c2) (hi : i = core.num.Usize.wrapping_sub d2 1#usize)
    (hlt : i < 32768#usize) (hmm : Matches s c2.val p.val m.val) (hc2 : c2.val ≤ p.val)
    (hm3 : 3 ≤ m.val) (hl : m.val ≤ 258) (hpl : p.val + m.val ≤ s.length) :
    _root_.Submission.PC.MatchAt s p.val m.val d2.val := (by
  obtain ⟨hdv, hd1, hd2⟩ := dist_of_wrapping hc2 hd hi hlt
  refine ⟨hm3, hl, hpl, hd1, hd2, by omega, ?_⟩
  rw [show p.val - d2.val = c2.val by omega]
  exact hmm)
@[local step]
abbrev f_try_spec := @_root_.Submission.PC.f_try_spec
@[local step]
abbrev f_deepen_spec := @_root_.Submission.PC.f_deepen_spec
@[local step]
theorem f_record3_loop0_spec {H : Std.Usize} (s : Slice Std.U8) (head : Array Std.U32 H)
    (prev : Array Std.U32 32768#usize) (km : Std.U32) (ins stop : Std.Usize) (B : Nat)
    (hB : _root_.Submission.PC.HeadBound head B) (hsB : stop.val < B + 1) (hs4 : stop.val + 4 ≤ Std.Usize.max)
    (hH : 0 < H.val) :
    slot.pim_f_record3_loop0 s head prev km ins stop ⦃ fun r =>
      _root_.Submission.PC.HeadBound r.1 B ∧ (r.2.2.val ≤ ins.val ∨ r.2.2.val ≤ stop.val) ⦄ := (by
  rw [slot.pim_f_record3_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun r => stop.val - r.2.2.val)
    (inv := fun r => _root_.Submission.PC.HeadBound r.1 B ∧ (r.2.2.val ≤ ins.val ∨ r.2.2.val ≤ stop.val))
  · rintro ⟨head, prev, ins'⟩ ⟨hB, hins⟩
    simp only at hB hins
    simp only [slot.pim_f_record3_loop0.body]
    step*
  · exact ⟨hB, Or.inl (le_refl _)⟩)
@[local step]
theorem f_record3_loop1_spec {H : Std.Usize} (s : Slice Std.U8) (head : Array Std.U32 H)
    (prev : Array Std.U32 32768#usize) («end» lim : Std.Usize) (km : Std.U32) (ins : Std.Usize)
    (B : Nat) (hB : _root_.Submission.PC.HeadBound head B) (heB : «end».val < B + 1)
    (hl4 : lim.val + 4 ≤ Std.Usize.max) (hH : 0 < H.val) :
    slot.pim_f_record3_loop1 s head prev «end» lim km ins ⦃ fun r => _root_.Submission.PC.HeadBound r.1 B ⦄ := (by
  rw [slot.pim_f_record3_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun r => «end».val - r.2.2.val)
    (inv := fun r => _root_.Submission.PC.HeadBound r.1 B)
  · rintro ⟨head, prev, ins'⟩ hB
    simp only at hB
    simp only [slot.pim_f_record3_loop1.body]
    step*
  · exact hB)
@[local step]
theorem f_record3_spec {H : Std.Usize} (s : Slice Std.U8) (head : Array Std.U32 H)
    (prev : Array Std.U32 32768#usize) (ins0 a0 «end» lim : Std.Usize) (km : Std.U32) (B : Nat)
    (hB : _root_.Submission.PC.HeadBound head B) (heB : «end».val < B + 1) (hlim : lim.val + 8 = s.length)
    (hins : ins0.val ≤ lim.val + 1) (hH : 0 < H.val) :
    slot.pim_f_record3 s head prev ins0 a0 «end» lim km ⦃ fun r => _root_.Submission.PC.HeadBound r.1 B ⦄ := (by
  rw [slot.pim_f_record3]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  step*
  repeat' (split <;> step*)
  all_goals try (obtain ⟨xh, xp⟩ := x; dsimp only at *)
  all_goals try step*
  repeat' (split <;> step*))
theorem lazy1c_loop_inv {H : Std.Usize} (input : Slice Std.U8) (lazy : Std.Usize) (km : Std.U32)
    (p : Std.Usize) (head : Array Std.U32 H) (prev : Array Std.U32 32768#usize)
    (lim pre_slot pre_c : Std.Usize) (pre_w : Std.U64)
    (l d ins : Std.Usize) (go : Std.U32) (P0 : Nat)
    (hlim : lim.val + 8 = input.length) (hH : 0 < H.val)
    (hinv : LazyInv1 input lim.val P0 p.val head pre_slot.val pre_c.val pre_w.val l.val d.val
      ins.val) :
    slot.pim_run1c_loop0_loop0 input lazy km p head prev lim pre_slot pre_c pre_w l d ins go ⦃ fun r =>
      LazyInv1 input lim.val P0 r.1.val r.2.1 r.2.2.2.1.val r.2.2.2.2.1.val r.2.2.2.2.2.1.val
        r.2.2.2.2.2.2.1.val r.2.2.2.2.2.2.2.1.val r.2.2.2.2.2.2.2.2.val ⦄ := (by
  rw [slot.pim_run1c_loop0_loop0]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  apply Std.loop.spec_decr_nat
    (measure := fun r => lim.val - r.1.val + r.2.2.2.2.2.2.2.2.2.val)
    (inv := fun r => LazyInv1 input lim.val P0 r.1.val r.2.1 r.2.2.2.1.val r.2.2.2.2.1.val
      r.2.2.2.2.2.1.val r.2.2.2.2.2.2.1.val r.2.2.2.2.2.2.2.1.val r.2.2.2.2.2.2.2.2.1.val)
  · rintro ⟨p, head, prev, pre_slot, pre_c, pre_w, l, d, ins, go⟩ hinv
    simp only at hinv
    have hinv' := hinv
    obtain ⟨⟨h3, h258, hpl, hd1, hd32, hdp, _⟩, hB, hplim, hins, hslot, hpc, hpw, hP⟩ := hinv'
    simp only [slot.pim_run1c_loop0_loop0.body]
    step*
    all_goals first
      | (refine ⟨LazyInv1.accept (by assumption) (by first | assumption | omega | scalar_tac) (by assumption) (by first | assumption | omega | scalar_tac)
          (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by assumption)
          (by first | assumption | omega | scalar_tac), by scalar_tac⟩)
      | (refine ⟨LazyInv1.reject hinv (by assumption) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac)
          (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by assumption), by scalar_tac⟩)
  · exact hinv)
@[local step]
theorem lazy1c_loop_spec {H : Std.Usize} (input : Slice Std.U8) (lazy : Std.Usize) (km : Std.U32)
    (p : Std.Usize) (head : Array Std.U32 H) (prev : Array Std.U32 32768#usize)
    (lim pre_slot pre_c : Std.Usize) (pre_w : Std.U64)
    (l d ins : Std.Usize) (go : Std.U32)
    (hlim : lim.val + 8 = input.length) (hH : 0 < H.val)
    (hm : _root_.Submission.PC.MatchAt input p.val l.val d.val)
    (hB : _root_.Submission.PC.HeadBound head (p.val + 1)) (hplim : p.val < lim.val) (hins : ins.val ≤ p.val + 2)
    (hps : pre_slot.val < H.val) (hpc : pre_c.val ≤ p.val + 1)
    (hpw : pre_w.val = _root_.Submission.PC.word8 input pre_c.val) :
    slot.pim_run1c_loop0_loop0 input lazy km p head prev lim pre_slot pre_c pre_w l d ins go ⦃ fun r =>
      _root_.Submission.PC.MatchAt input r.1.val r.2.2.2.2.2.2.1.val r.2.2.2.2.2.2.2.1.val ∧
      _root_.Submission.PC.HeadBound r.2.1 (r.1.val + r.2.2.2.2.2.2.1.val) ∧ r.1.val < lim.val ∧
      r.2.2.2.2.2.2.2.2.val ≤ r.1.val + 2 ∧ 3 ≤ r.2.2.2.2.2.2.1.val ∧
      r.2.2.2.1.val < H.val ∧ r.2.2.2.2.1.val ≤ r.1.val + 1 ∧
      r.2.2.2.2.2.1.val = _root_.Submission.PC.word8 input r.2.2.2.2.1.val ∧ p.val ≤ r.1.val ⦄ := (by
  apply Std.WP.spec_mono (lazy1c_loop_inv input lazy km p head prev lim pre_slot pre_c pre_w l d
    ins go p.val hlim hH ⟨hm, hB, hplim, hins, hps, hpc, hpw, le_refl _⟩)
  rintro ⟨p', head', prev', ps', pc', pw', l', d', ins'⟩
    ⟨hm', hB', hplim', hins', hps', hpc', hpw', hP'⟩
  exact ⟨hm', HeadBound.mono hB' (by have := hm'.1; omega), hplim', hins', hm'.1, hps', hpc',
    hpw', hP'⟩)
@[local step]
theorem tail1c_loop1_spec (input : Slice Std.U8) (out : Slice Std.U32) (n nt p : Std.Usize)
    (hn : n.val = input.length) (hdec : _root_.Submission.PC.Dec input out nt.val p.val) :
    slot.pim_run1c_loop1 input out n nt p ⦃ fun r => r.1.val ≤ input.length ∧
      r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := C12582! slot.pim_run1c_loop1 slot.pim_run1c_loop1.body
@[local step]
theorem tail1c_loop2_spec (input : Slice Std.U8) (out : Slice Std.U32) (n nt p : Std.Usize)
    (hn : n.val = input.length) (hdec : _root_.Submission.PC.Dec input out nt.val p.val) :
    slot.pim_run1c_loop2 input out n nt p ⦃ fun r => r.1.val ≤ input.length ∧
      r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := C12582! slot.pim_run1c_loop2 slot.pim_run1c_loop2.body
set_option maxHeartbeats 16000000 in
theorem main1c_loop_spec {H : Std.Usize} (input : Slice Std.U8) (out : Slice Std.U32)
    (skip lazy skcap : Std.Usize) (km : Std.U32) (dp minl nt ls p : Std.Usize)
    (head : Array Std.U32 H) (prev : Array Std.U32 32768#usize)
    (lim miss fuel pre_slot pre_c : Std.Usize) (pre_w : Std.U64) (L : Nat)
    (hlim : lim.val + 8 = input.length) (hskip : skip.val < 32) (hH : 0 < H.val)
    (hinv : MainInv1 input L out nt.val ls.val p.val head miss.val pre_slot.val pre_c.val
      pre_w.val) :
    slot.pim_run1c_loop0 input out skip lazy skcap km dp minl nt ls p head prev lim miss fuel pre_slot
      pre_c pre_w ⦃ fun r => _root_.Submission.PC.Dec input r.1 r.2.1.val r.2.2.val ∧ r.1.length = L ⦄ := (by
  rw [slot.pim_run1c_loop0]
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
    simp only [slot.pim_run1c_loop0.body]
    step*
    all_goals try (obtain ⟨i8, i9, i10⟩ := ae; dsimp only at *; step*)
    all_goals first
      | exact FoundAt.real (by assumption) (by first | assumption | omega | scalar_tac)
      | exact HeadBound.mono (by assumption) (by first | assumption | omega | scalar_tac)
      | (refine ⟨MainInv1.mk' (by assumption) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac)
          (by assumption) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac)
          (by assumption), by scalar_tac⟩)
  · exact hinv)
@[local step]
theorem main1c_loop_spec' {H : Std.Usize} (input : Slice Std.U8) (out : Slice Std.U32)
    (skip lazy skcap : Std.Usize) (km : Std.U32) (dp minl nt ls p : Std.Usize)
    (head : Array Std.U32 H) (prev : Array Std.U32 32768#usize)
    (lim miss fuel pre_slot pre_c : Std.Usize) (pre_w : Std.U64)
    (hlim : lim.val + 8 = input.length) (hskip : skip.val < 32) (hH : 0 < H.val)
    (hdec : _root_.Submission.PC.Dec input out nt.val ls.val) (hlsp : ls.val ≤ p.val) (hB : _root_.Submission.PC.HeadBound head p.val)
    (hmiss : miss.val ≤ p.val) (hps : pre_slot.val < H.val) (hpc : pre_c.val ≤ p.val)
    (hpw : pre_w.val = _root_.Submission.PC.word8 input pre_c.val) :
    slot.pim_run1c_loop0 input out skip lazy skcap km dp minl nt ls p head prev lim miss fuel pre_slot
      pre_c pre_w ⦃ fun r => _root_.Submission.PC.Dec input r.1 r.2.1.val r.2.2.val ∧ r.1.length = out.length ⦄ :=
  main1c_loop_spec input out skip lazy skcap km dp minl nt ls p head prev lim miss fuel pre_slot
    pre_c pre_w out.length hlim hskip hH ⟨hdec, rfl, hlsp, hB, hmiss, hps, hpc, hpw⟩
theorem run1c_spec (H : Std.Usize) (input : Slice Std.U8) (out : Slice Std.U32)
    (skip lazy skcap : Std.Usize) (km : Std.U32) (dp minl : Std.Usize)
    (hlen : input.length ≤ out.length) (hH : 0 < H.val) (hskip : skip.val < 32) :
    slot.pim_run1c H input out skip lazy skcap km dp minl ⦃ fun r => r.1.val ≤ input.length ∧
      r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := (by
  rw [slot.pim_run1c]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  have hB0 : _root_.Submission.PC.HeadBound (Std.Array.repeat H 0#u32) 0 := HeadBound.init H
  have hdec0 : _root_.Submission.PC.Dec input out (0#usize).val (0#usize).val := Dec.init input out hlen
  step*)
end PIM
open Aeneas Aeneas.Std Result ControlFlow
open LZ77 (toks bytes)
set_option maxRecDepth 8192
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
theorem tp_lift_spec {α : Type} (x : α) : lift x ⦃ fun y => y = x ⦄ := (by
  simp [lift, WP.spec_ok])
theorem tp_numBits_ge : 32 ≤ System.Platform.numBits := (by
  cases System.Platform.numBits_eq <;> simp [*])
@[local scalar_tac System.Platform.numBits]
theorem tp_numBits_ge' : 32 ≤ System.Platform.numBits := tp_numBits_ge
end TinyPath
@[irreducible] def word8 (input : Slice Std.U8) (p : Nat) : Nat :=
  (input.val[p]!).val * 2^56 + (input.val[p + 1]!).val * 2^48 + (input.val[p + 2]!).val * 2^40
    + (input.val[p + 3]!).val * 2^32 + (input.val[p + 4]!).val * 2^24
    + (input.val[p + 5]!).val * 2^16 + (input.val[p + 6]!).val * 2^8 + (input.val[p + 7]!).val
theorem u8_lt (x : Std.U8) : x.val < 256 := by scalar_tac
theorem word8_digit (input : Slice Std.U8) (p k : Nat) (hk : k < 8) :
    (input.val[p + k]!).val = word8 input p / 256 ^ (7 - k) % 256 := (by
  have := u8_lt (input.val[p]!); have := u8_lt (input.val[p+1]!)
  have := u8_lt (input.val[p+2]!); have := u8_lt (input.val[p+3]!)
  have := u8_lt (input.val[p+4]!); have := u8_lt (input.val[p+5]!)
  have := u8_lt (input.val[p+6]!); have := u8_lt (input.val[p+7]!)
  simp only [word8]
  rcases (show k = 0 ∨ k = 1 ∨ k = 2 ∨ k = 3 ∨ k = 4 ∨ k = 5 ∨ k = 6 ∨ k = 7 by omega) with
    rfl | rfl | rfl | rfl | rfl | rfl | rfl | rfl <;> simp only [Nat.add_zero, Nat.pow_zero, Nat.pow_succ, Nat.one_mul,
    Nat.sub_self, Nat.reduceSub] <;> omega)
theorem word8_prefix (input : Slice Std.U8) (a b d : Nat) (hd : d ≤ 8)
    (h : word8 input a / 2 ^ (64 - 8 * d) = word8 input b / 2 ^ (64 - 8 * d)) :
    ∀ k, k < d → input.val[b + k]! = input.val[a + k]! := (by
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
theorem Matches.add_prefix {input : Slice Std.U8} {a b l d : Nat} (h : Matches input a b l)
    (hd : d ≤ 8)
    (hw : word8 input (a + l) / 2 ^ (64 - 8 * d) = word8 input (b + l) / 2 ^ (64 - 8 * d)) :
    Matches input a b (l + d) := (by
  intro k hk
  by_cases hkl : k < l
  · exact h k hkl
  · have := word8_prefix input (a + l) (b + l) d hd hw (k - l) (by omega)
    rw [show b + l + (k - l) = b + k by omega, show a + l + (k - l) = a + k by omega] at this
    exact this)
theorem or_eq_add_of_mod {x t : Nat} (m : Nat) (hx : x % 2 ^ m = 0) (ht : t < 2 ^ m) :
    x ||| t = x + t := (by
  have h := Nat.two_pow_add_eq_or_of_lt ht (x / 2 ^ m)
  have hx' : 2 ^ m * (x / 2 ^ m) = x := by
    have := Nat.div_add_mod x (2 ^ m); omega
  rw [hx'] at h
  exact h.symm)
theorem shl_byte {x : Nat} (k : Nat) (hx : x < 256) (hk : k ≤ 56) :
    x <<< k % U64.size = x * 2 ^ k := (by
  rw [Nat.shiftLeft_eq, U64.size_def]
  apply Nat.mod_eq_of_lt
  have : 2 ^ k ≤ 2 ^ 56 := Nat.pow_le_pow_right (by norm_num) hk
  have : x * 2 ^ k < 256 * 2 ^ 56 := by
    calc x * 2 ^ k < 256 * 2 ^ k := by
          apply Nat.mul_lt_mul_of_pos_right hx (Nat.two_pow_pos _)
      _ ≤ 256 * 2 ^ 56 := Nat.mul_le_mul_left _ this
  simp only [U64.numBits] at *
  omega)
theorem be8_nat {a b c d e f g h : Nat} (ha : a < 256) (hb : b < 256) (hc : c < 256)
    (hd : d < 256) (he : e < 256) (hf : f < 256) (hg : g < 256) (hh : h < 256) :
    (a <<< 56 % U64.size ||| b <<< 48 % U64.size ||| c <<< 40 % U64.size |||
      d <<< 32 % U64.size ||| e <<< 24 % U64.size ||| f <<< 16 % U64.size |||
      g <<< 8 % U64.size ||| h) =
    a * 2^56 + b * 2^48 + c * 2^40 + d * 2^32 + e * 2^24 + f * 2^16 + g * 2^8 + h := (by
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
@[local step]
theorem be8_spec (s : Slice Std.U8) (i : Std.Usize) (h : i.val + 8 ≤ s.length) :
    slot.q4_be8 s i ⦃ fun v => v.val = word8 s i.val ⦄ := (by
  rw [slot.q4_be8]
  step*
  simp only [← getElem!_pos] at *
  simp_all only [UScalar.val_or, U8.cast_U64_val_eq]
  rw [be8_nat (u8_lt _) (u8_lt _) (u8_lt _) (u8_lt _) (u8_lt _) (u8_lt _) (u8_lt _) (u8_lt _)]
  simp only [word8])
theorem nat_xor_eq_zero {a b : Nat} (h : a ^^^ b = 0) : a = b := (by
  have : a ^^^ (a ^^^ b) = b := by rw [← Nat.xor_assoc, Nat.xor_self, Nat.zero_xor]
  rw [h, Nat.xor_zero] at this; exact this)
theorem div_eq_of_xor_lt {x y m : Nat} (hz : x ^^^ y < 2 ^ m) : x / 2 ^ m = y / 2 ^ m := (by
  have h : (x ^^^ y) >>> m = 0 := by rw [Nat.shiftRight_eq_div_pow]; exact Nat.div_eq_of_lt hz
  rw [Nat.shiftRight_xor_distrib] at h
  have := nat_xor_eq_zero h
  simpa [Nat.shiftRight_eq_div_pow] using this)
theorem lt_pow_leadingZeros (z : BitVec 64) :
    z.toNat < 2 ^ (64 - 8 * (BitVec.leadingZeros z / 8)) := (by
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
theorem leadingZeros_lt_of_ne (z : BitVec 64) (h : z ≠ 0) : BitVec.leadingZeros z < 64 := (by
  unfold BitVec.leadingZeros
  simp only [h, if_false]
  omega)
@[local step]
theorem lz_spec (x : Std.U64) :
    lift (core.num.U64.leading_zeros x) ⦃ fun r => r = core.num.U64.leading_zeros x ∧ r.val ≤ 64 ⦄ := (by
  simp only [lift, Std.WP.spec_ok, true_and]
  have hle : BitVec.leadingZeros x.bv ≤ 64 := by unfold BitVec.leadingZeros; split <;> omega
  simp only [core.num.U64.leading_zeros, UScalar.val, UScalarTy.U32_numBits_eq,
    BitVec.natCast_eq_ofNat, BitVec.toNat_ofNat, Nat.reducePow]
  omega)
theorem lz_val (x : Std.U64) :
    (core.num.U64.leading_zeros x).val = BitVec.leadingZeros x.bv := (by
  have hle : BitVec.leadingZeros x.bv ≤ 64 := by unfold BitVec.leadingZeros; split <;> omega
  simp only [core.num.U64.leading_zeros, UScalar.val, UScalarTy.U32_numBits_eq,
    BitVec.natCast_eq_ofNat, BitVec.toNat_ofNat, Nat.reducePow]
  omega)
theorem Matches.word_lz {input : Slice Std.U8} {a b k : Nat} {pa pb r k1 : Std.Usize}
    {x y z : Std.U64} {lz q : Std.U32}
    (h : Matches input a b k) (hpa : pa.val = a + k) (hpb : pb.val = b + k)
    (hx : x.val = word8 input pa.val) (hy : y.val = word8 input pb.val)
    (hz : z.val = (x ^^^ y).val) (hz0 : ¬z = 0#u64) (hlz : lz = core.num.U64.leading_zeros z)
    (hq : q.val = lz.val / 8) (hr : r = UScalar.cast .Usize q) (hk1 : k1.val = k + r.val) :
    Matches input a b k1.val ∧ k1.val < k + 8 := (by
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
theorem Matches.word_zero {input : Slice Std.U8} {a b k : Nat} {pa pb k1 : Std.Usize}
    {x y z : Std.U64}
    (h : Matches input a b k) (hpa : pa.val = a + k) (hpb : pb.val = b + k)
    (hx : x.val = word8 input pa.val) (hy : y.val = word8 input pb.val)
    (hz : z.val = (x ^^^ y).val) (hz0 : z = 0#u64) (hk1 : k1.val = k + 8) :
    Matches input a b k1.val := (by
  have hxy : x.val = y.val := by
    apply nat_xor_eq_zero
    rw [← UScalar.val_xor, ← hz, hz0]; rfl
  rw [hpa] at hx; rw [hpb] at hy
  rw [hk1]
  apply Matches.add_prefix h (le_refl 8)
  rw [← hx, ← hy, hxy])
theorem Matches.byte' {input : Slice Std.U8} {a b l : Nat} {pa pb l1 : Std.Usize}
    {x y : Std.U8} (h : Matches input a b l) (hpa : pa.val = a + l) (hpb : pb.val = b + l)
    (hpa' : pa.val < input.val.length) (hpb' : pb.val < input.val.length)
    (hx : x = input.val[pa.val]) (hy : y = input.val[pb.val]) (hxy : x = y)
    (hl1 : l1.val = l + 1) : Matches input a b l1.val := (by
  rw [hl1]
  apply LZ77.Matches.succ h
  rw [← hpa, ← hpb, getElem!_pos input.val pa.val hpa', getElem!_pos input.val pb.val hpb',
    ← hx, ← hy, hxy])
theorem wadd_val {x y z : Std.Usize} (hz : z = core.num.Usize.wrapping_add x y)
    (hb : x.val + y.val ≤ Std.Usize.max) : z.val = x.val + y.val := (by
  have hlt : x.val + y.val < Usize.size := by scalar_tac
  rw [hz, core.num.Usize.wrapping_add_val_eq, UScalar.size_UScalarTyUsize, Nat.mod_eq_of_lt hlt])
theorem wadd_le {x y z : Std.Usize} {m n : Nat} (hz : z = core.num.Usize.wrapping_add x y)
    (h : x.val + y.val + m ≤ n) (hn : n ≤ Std.Usize.max) : z.val + m ≤ n := (by
  rw [wadd_val hz (by omega)]; exact h)
@[local step]
theorem xor8_spec (s : Slice Std.U8) (a b : Std.Usize) (ha : a.val + 8 ≤ s.length)
    (hb : b.val + 8 ≤ s.length) :
    slot.q4_xor8 s a b ⦃ fun v => v.val = word8 s a.val ^^^ word8 s b.val ⦄ := (by
  rw [slot.q4_xor8]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  step*
  simp only [← getElem!_pos] at *
  simp_all only [UScalar.val_or, UScalar.val_xor, U8.cast_U64_val_eq]
  rw [be8_nat (u8_lt _) (u8_lt _) (u8_lt _) (u8_lt _) (u8_lt _) (u8_lt _) (u8_lt _) (u8_lt _),
    be8_nat (u8_lt _) (u8_lt _) (u8_lt _) (u8_lt _) (u8_lt _) (u8_lt _) (u8_lt _) (u8_lt _)]
  simp only [word8])
theorem Matches.lz_any {input : Slice Std.U8} {a b k : Nat} {r k1 : Std.Usize} {z : Std.U64}
    {lz q : Std.U32} (h : Matches input a b k)
    (hz : z.val = word8 input (a + k) ^^^ word8 input (b + k))
    (hlz : lz = core.num.U64.leading_zeros z) (hq : q.val = lz.val / 8)
    (hr : r = UScalar.cast .Usize q) (hk1 : k1.val = k + r.val) :
    Matches input a b k1.val ∧ k1.val ≤ k + 8 := (by
  have hle : BitVec.leadingZeros z.bv ≤ 64 := by unfold BitVec.leadingZeros; split <;> omega
  have hrv : r.val = BitVec.leadingZeros z.bv / 8 := by
    rw [hr, U32.cast_Usize_val_eq, hq, hlz, lz_val]
  refine ⟨?_, by omega⟩
  rw [hk1, hrv]
  apply Matches.add_prefix h (by omega)
  apply div_eq_of_xor_lt
  rw [← hz]
  exact lt_pow_leadingZeros z.bv)
theorem Matches.xz {input : Slice Std.U8} {a b : Nat} {z : Std.U64}
    (hz : z.val = word8 input a ^^^ word8 input b) (hz0 : z = 0#u64) :
    Matches input a b 8 := (by
  have hv : word8 input a ^^^ word8 input b = 0 := by rw [← hz, hz0]; rfl
  have hab := nat_xor_eq_zero hv
  have := Matches.add_prefix (LZ77.Matches.zero input a b) (le_refl 8)
    (by simp only [Nat.add_zero]; rw [hab])
  simpa using this)
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
    Matches input a.val b.val k1.val ∧ k1.val ≤ k.val + 8 := (by
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  rw [wadd_val hpa (by omega), wadd_val hpb (by omega)] at hz
  exact Matches.lz_any h hz hlz hq hr hk1)
theorem Matches.xw_zero {input : Slice Std.U8} {a b k pa pb k1 : Std.Usize} {z : Std.U64}
    (h : Matches input a.val b.val k.val)
    (hpa : pa = core.num.Usize.wrapping_add a k) (hpb : pb = core.num.Usize.wrapping_add b k)
    (hab : a.val + k.val + 8 ≤ input.length ∧ b.val + k.val + 8 ≤ input.length)
    (hz : z.val = word8 input pa.val ^^^ word8 input pb.val) (hz0 : z = 0#u64)
    (hk1 : k1.val = k.val + 8) : Matches input a.val b.val k1.val := (by
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
theorem Matches.word_eq {input : Slice Std.U8} {a b k : Nat} {pa pb k1 : Std.Usize}
    {x y : Std.U64}
    (h : Matches input a b k) (hpa : pa.val = a + k) (hpb : pb.val = b + k)
    (hx : x.val = word8 input pa.val) (hy : y.val = word8 input pb.val)
    (hxy : x = y) (hk1 : k1.val = k + 8) :
    Matches input a b k1.val := (by
  rw [hpa] at hx; rw [hpb] at hy
  rw [hk1]
  apply Matches.add_prefix h (le_refl 8)
  rw [← hx, ← hy, hxy])
theorem same_loop0_spec (s : Slice Std.U8) (a b len k ok : Std.Usize)
    (ha : a.val + len.val ≤ s.length) (hb : b.val + len.val ≤ s.length) (hlen : len.val ≤ 258)
    (hk : k.val ≤ len.val) (hm : Matches s a.val b.val k.val) :
    slot.q4_same_loop0 s a b len k ok ⦃ fun r =>
      r.1.val ≤ len.val ∧ Matches s a.val b.val r.1.val ∧ (r.2.val = 1 → len.val < r.1.val + 8) ⦄ := (by
  rw [slot.q4_same_loop0]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  apply Std.loop.spec_decr_nat
    (measure := fun r => len.val - r.1.val + r.2.val)
    (inv := fun r => r.1.val ≤ len.val ∧ Matches s a.val b.val r.1.val)
  · rintro ⟨k, ok⟩ ⟨hk, hm⟩
    simp only at hk hm
    simp only [slot.q4_same_loop0.body]
    step*
    all_goals first
      | scalar_tac
      | (refine ⟨by scalar_tac, Matches.word_eq hm (by assumption) (by assumption)
          (by assumption) (by assumption) (by assumption) (by first | assumption | omega | scalar_tac), by scalar_tac⟩)
  · exact ⟨hk, hm⟩)
@[local step]
theorem same_loop1_spec (s : Slice Std.U8) (a b len k ok : Std.Usize)
    (ha : a.val + len.val ≤ s.length) (hb : b.val + len.val ≤ s.length)
    (hk : k.val ≤ len.val) (hm : Matches s a.val b.val k.val) :
    slot.q4_same_loop1 s a b len k ok ⦃ fun r => r.val = 1 → Matches s a.val b.val len.val ⦄ := (by
  rw [slot.q4_same_loop1]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  apply Std.loop.spec_decr_nat
    (measure := fun r => len.val - r.1.val + r.2.val)
    (inv := fun r => r.1.val ≤ len.val ∧ Matches s a.val b.val r.1.val)
  · rintro ⟨k, ok⟩ ⟨hk, hm⟩
    simp only at hk hm
    simp only [slot.q4_same_loop1.body]
    step*
    all_goals first
      | scalar_tac
      | (refine ⟨by scalar_tac, Matches.byte' hm (by assumption) (by assumption) (by first | assumption | omega | scalar_tac)
          (by first | assumption | omega | scalar_tac) (by assumption) (by assumption) (by assumption) (by assumption),
          by scalar_tac⟩)
  · exact ⟨hk, hm⟩)
@[local step]
theorem same_loop2_spec (s : Slice Std.U8) (a b len k ok : Std.Usize)
    (ha : a.val + len.val ≤ s.length) (hb : b.val + len.val ≤ s.length)
    (hk : k.val ≤ len.val) (hm : Matches s a.val b.val k.val) :
    slot.q4_same_loop2 s a b len k ok ⦃ fun r => r.val = 1 → Matches s a.val b.val len.val ⦄ := (by
  rw [slot.q4_same_loop2]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  apply Std.loop.spec_decr_nat
    (measure := fun r => len.val - r.1.val + r.2.val)
    (inv := fun r => r.1.val ≤ len.val ∧ Matches s a.val b.val r.1.val)
  · rintro ⟨k, ok⟩ ⟨hk, hm⟩
    simp only at hk hm
    simp only [slot.q4_same_loop2.body]
    step*
    all_goals first
      | scalar_tac
      | (refine ⟨by scalar_tac, Matches.byte' hm (by assumption) (by assumption) (by first | assumption | omega | scalar_tac)
          (by first | assumption | omega | scalar_tac) (by assumption) (by assumption) (by assumption) (by assumption),
          by scalar_tac⟩)
  · exact ⟨hk, hm⟩)
theorem Matches.mask {input : Slice Std.U8} {a b k len : Nat} {pa pb : Std.Usize}
    {x y z w : Std.U64} {sh : Std.U32}
    (h : Matches input a b k) (hpa : pa.val = a + k) (hpb : pb.val = b + k)
    (hx : x.val = word8 input pa.val) (hy : y.val = word8 input pb.val)
    (hz : z.val = (x ^^^ y).val) (hw : w.val = z.val >>> sh.val) (hw0 : ¬(w != 0#u64) = true)
    (hsh : sh.val = 64 - 8 * (len - k)) (hk : k < len) (hlen : len < k + 8) :
    Matches input a b len := (by
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
@[local step]
theorem same_spec (s : Slice Std.U8) (a b len : Std.Usize)
    (ha : a.val + len.val ≤ s.length) (hb : b.val + len.val ≤ s.length) (hlen : len.val ≤ 258)
    (ha8 : a.val + len.val + 7 ≤ Std.Usize.max) (hb8 : b.val + len.val + 7 ≤ Std.Usize.max) :
    slot.q4_same s a b len ⦃ fun r => r.val = 1 → Matches s a.val b.val len.val ⦄ := (by
  rw [slot.q4_same]
  apply Std.WP.spec_bind (same_loop0_spec s a b len 0#usize 1#usize ha hb hlen (by simp)
    (LZ77.Matches.zero s a.val b.val))
  rintro ⟨k, ok⟩ ⟨hk, hm, hok⟩
  simp only at hk hm hok
  step*
  intro _
  exact Matches.mask hm (by assumption) (by assumption) (by assumption) (by assumption)
    (by assumption) (by assumption) (by assumption) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac)
    (by first | assumption | omega | scalar_tac))
theorem lz32_le (x : Std.U32) (k : Nat) (hk : k < 32) (hx : 2 ^ k ≤ x.val) :
    (core.num.U32.leading_zeros x).val ≤ 31 - k := (by
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
@[local step]
theorem lz32_spec (x : Std.U32) :
    lift (core.num.U32.leading_zeros x) ⦃ fun r => r = core.num.U32.leading_zeros x ∧
      (4 ≤ x.val → r.val ≤ 29) ∧ (8 ≤ x.val → r.val ≤ 28) ⦄ := (by
  simp only [lift, Std.WP.spec_ok, true_and]
  exact ⟨fun h => lz32_le x 2 (by norm_num) (by simpa using h),
    fun h => lz32_le x 3 (by norm_num) (by simpa using h)⟩)
@[local step]
theorem hcast_I32_spec {ty : UScalarTy} (x : UScalar ty) (h : x.val ≤ 2147483647) :
    lift (UScalar.hcast .I32 x) ⦃ fun y => y.val = x.val ⦄ :=
  UScalar.hcast_inBounds_spec .I32 x (by simp [I32.max_def, I32.numBits]; omega)
theorem GBASE_bound : -1000000000 ≤ slot.q4_GBASE.val ∧ slot.q4_GBASE.val ≤ 1000000000 := by
  unfold slot.q4_GBASE
  simp
@[local step]
theorem gain_spec (l d : Std.Usize) (hl : l.val ≤ 258) (hd : d.val ≤ 32768) :
    slot.q4_gain l d ⦃ fun _ => True ⦄ := (by
  rw [slot.q4_gain]
  have ⟨hG0, hG1⟩ := GBASE_bound
  repeat' (split <;> step*))
def HeadBound {N : Std.Usize} (head : Array Std.U32 N) (B : Nat) : Prop :=
  ∀ j : Nat, j < head.val.length → (head.val[j]!).val ≤ B
theorem HeadBound.mono {N : Std.Usize} {head : Array Std.U32 N} {B B' : Nat}
    (h : HeadBound head B) (hB : B ≤ B') : HeadBound head B' := fun j hj => le_trans (h j hj) hB
theorem HeadBound.init (N : Std.Usize) : HeadBound (Std.Array.repeat N 0#u32) 0 := (by
  intro j hj
  rw [Std.Array.repeat_val] at hj ⊢
  rw [List.getElem!_eq_getElem?_getD, List.getElem?_replicate_of_lt (by simpa using hj)]
  rfl)
theorem HeadBound.set {N : Std.Usize} {head : Array Std.U32 N} {B : Nat} (h : HeadBound head B)
    (a : Std.Usize) (v : Std.U32) (hv : v.val ≤ B) : HeadBound (head.set a v) B := (by
  intro j hj
  rw [Std.Array.set_val_eq] at hj ⊢
  rw [List.length_set] at hj
  by_cases hja : a.val = j
  · subst hja
    rw [List.getElem!_eq_getElem?_getD, List.getElem?_set_self hj]
    exact hv
  · rw [List.getElem!_eq_getElem?_getD, List.getElem?_set_ne hja, ← List.getElem!_eq_getElem?_getD]
    exact h j hj)
theorem HeadBound.update {N : Std.Usize} {head head1 : Array Std.U32 N} {B : Nat}
    {a i : Std.Usize} {v : Std.U32} (h : HeadBound head B) (hv : v = UScalar.cast .U32 i)
    (hi : i.val ≤ B) (h1 : head1 = head.set a v) : HeadBound head1 B := (by
  subst h1
  apply HeadBound.set h a v
  rw [hv]
  have : (UScalar.cast .U32 i).val = i.val % 2 ^ 32 := by
    simp only [UScalar.cast_val_eq, UScalarTy.U32_numBits_eq]
  rw [this]
  exact le_trans (Nat.mod_le _ _) hi)
theorem HeadBound.get {N : Std.Usize} {head : Array Std.U32 N} {B : Nat} (h : HeadBound head B)
    (a : Std.Usize) (x : Std.U32) (ha : a.val < head.val.length) (hx : x = head.val[a.val]) :
    x.val ≤ B := (by
  have := h a.val ha
  rw [getElem!_pos head.val a.val ha, ← hx] at this
  exact this)
@[local step]
theorem be4_spec (s : Slice Std.U8) (i : Std.Usize) (hi : i.val + 4 ≤ Std.Usize.max) :
    slot.q4_be4 s i ⦃ fun _ => True ⦄ := by
  rw [slot.q4_be4]
  step*
theorem dist_of_wrapping {p c d i : Std.Usize} (hc : c.val ≤ p.val)
    (hd : d = core.num.Usize.wrapping_sub p c) (hi : i = core.num.Usize.wrapping_sub d 1#usize)
    (hlt : i < 32768#usize) : d.val = p.val - c.val ∧ 1 ≤ d.val ∧ d.val ≤ 32768 := (by
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
def MatchAt (s : Slice Std.U8) (p l d : Nat) : Prop :=
  3 ≤ l ∧ l ≤ 258 ∧ p + l ≤ s.length ∧ 1 ≤ d ∧ d ≤ 32768 ∧ d ≤ p ∧ Matches s (p - d) p l
def FoundAt (s : Slice Std.U8) (p l d : Nat) : Prop := l < 3 ∨ MatchAt s p l d
theorem FoundAt.none (s : Slice Std.U8) (p : Nat) : FoundAt s p (0#usize).val (0#usize).val :=
  Or.inl (by simp)
theorem FoundAt.real {s : Slice Std.U8} {p l d : Nat} (hf : FoundAt s p l d) (h3 : 3 ≤ l) :
    MatchAt s p l d := (by
  rcases hf with h | h
  · omega
  · exact h)
theorem copyN_take_prefix (acc : List Nat) (d : Nat) :
    ∀ n, (copyN acc d n).take acc.length = acc := (by
  intro n
  induction n with
  | zero => simp [copyN]
  | succ m ih =>
    simp only [copyN]
    rw [List.take_append_of_le_length (by simp)]
    exact ih)
theorem foldlM_emit_length : ∀ (ts : List Nat) (init acc : List Nat),
    ts.foldlM emit init = some acc → init.length + ts.length ≤ acc.length := (by
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
theorem decode_length_le {ts acc : List Nat} (h : decode ts = some acc) :
    ts.length ≤ acc.length := (by
  have := foldlM_emit_length ts [] acc h
  simpa using this)
theorem decode_pop_lit {ts : List Nat} {t : Nat} {inp : List Nat} {p : Nat}
    (hp : p ≤ inp.length) (hd : decode (ts ++ [t]) = some (inp.take p)) (ht : t < 256) :
    1 ≤ p ∧ decode ts = some (inp.take (p - 1)) := (by
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
theorem decode_pop_match {ts : List Nat} {t : Nat} {inp : List Nat} {p : Nat}
    (hp : p ≤ inp.length) (hd : decode (ts ++ [t]) = some (inp.take p)) (ht : 256 ≤ t) :
    tokLen t ≤ p ∧ decode ts = some (inp.take (p - tokLen t)) := (by
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
theorem toks_pop (out : Slice Std.U32) (nt : Nat) (h0 : 0 < nt) (hle : nt ≤ out.length) :
    toks out nt = toks out (nt - 1) ++ [(out.val[nt - 1]!).val] := (by
  have hlt : nt - 1 < out.val.length := by
    have : out.length = out.val.length := rfl
    omega
  simp only [toks]
  conv_lhs => rw [show nt = (nt - 1) + 1 by omega]
  rw [List.take_add_one, List.getElem?_eq_getElem hlt, Option.toList_some, List.map_append]
  simp [getElem!_pos out.val (nt - 1) hlt])
theorem toks_length (out : Slice Std.U32) (nt : Nat) (h : nt ≤ out.length) :
    (toks out nt).length = nt := (by
  simp only [toks, List.length_map, List.length_take]
  have : out.length = out.val.length := rfl
  omega)
def Dec (s : Slice Std.U8) (out : Slice Std.U32) (nt p : Nat) : Prop :=
  p ≤ s.length ∧ nt ≤ p ∧ s.length ≤ out.length ∧
    decode (toks out nt) = some ((bytes s).take p)
theorem Dec.init (input : Slice Std.U8) (out : Slice Std.U32) (h : input.length ≤ out.length) :
    Dec input out (0#usize).val (0#usize).val :=
  ⟨by simp, by simp, h, by simp [toks, LZ77.decode]⟩
theorem Dec.lit {s : Slice Std.U8} {out : Slice Std.U32} {nt p : Nat} (h : Dec s out nt p)
    (hp : p < s.length) (ntU : Std.Usize) (hnt : ntU.val = nt) (v : Std.U32)
    (hv : v.val = (s.val[p]!).val) :
    Dec s (out.set ntU v) (nt + 1) (p + 1) := (by
  obtain ⟨hps, hntp, hso, hde⟩ := h
  have hntl : ntU.val < out.length := by omega
  refine ⟨by omega, by omega, by rw [Std.Slice.set_length]; exact hso, ?_⟩
  rw [← hnt]
  refine emit_lit s out ntU p v (by rw [hnt]; exact hde) hp hntl ?_
  have hpl : p < s.val.length := hp
  rw [hv, bytes_getElem! s p hpl, getElem!_pos s.val p hpl])
theorem Dec.match {s : Slice Std.U8} {out : Slice Std.U32} {nt p l d : Nat} (h : Dec s out nt p)
    (hm : MatchAt s p l d) (ntU : Std.Usize) (hnt : ntU.val = nt) (v : Std.U32)
    (hv : v.val = LZ77.mkMatch d l) :
    Dec s (out.set ntU v) (nt + 1) (p + l) := (by
  obtain ⟨hps, hntp, hso, hde⟩ := h
  obtain ⟨h3, h258, hpl, hd1, hd32, hdp, hmm⟩ := hm
  have hntl : ntU.val < out.length := by omega
  refine ⟨by omega, by omega, by rw [Std.Slice.set_length]; exact hso, ?_⟩
  rw [← hnt]
  exact emit_match s out ntU p d l v (by rw [hnt]; exact hde) hntl hd1 hdp hd32 h3 h258 hpl hmm hv)
theorem Dec.pop_lit {s : Slice Std.U8} {out : Slice Std.U32} {nt p : Nat} (h : Dec s out nt p)
    (h0 : 0 < nt) (hle : nt ≤ out.length) (ht : (out.val[nt - 1]!).val < 256) :
    1 ≤ p ∧ Dec s out (nt - 1) (p - 1) := (by
  obtain ⟨hps, hntp, hso, hde⟩ := h
  rw [toks_pop out nt h0 hle] at hde
  obtain ⟨hp1, hde'⟩ := decode_pop_lit (by simpa using hps) hde ht
  exact ⟨hp1, by omega, by omega, hso, hde'⟩)
theorem Dec.pop_match {s : Slice Std.U8} {out : Slice Std.U32} {nt p : Nat} (h : Dec s out nt p)
    (h0 : 0 < nt) (hle : nt ≤ out.length) (ht : 256 ≤ (out.val[nt - 1]!).val) :
    tokLen (out.val[nt - 1]!).val ≤ p ∧
      Dec s out (nt - 1) (p - tokLen (out.val[nt - 1]!).val) := (by
  obtain ⟨hps, hntp, hso, hde⟩ := h
  rw [toks_pop out nt h0 hle] at hde
  obtain ⟨hw, hde'⟩ := decode_pop_match (by simpa using hps) hde ht
  have hlen := decode_length_le hde'
  rw [toks_length out (nt - 1) (by omega), List.length_take, bytes_length] at hlen
  exact ⟨hw, by omega, by omega, hso, hde'⟩)
theorem Dec.done {s : Slice Std.U8} {out : Slice Std.U32} {nt p : Nat} (h : Dec s out nt p)
    (hp : s.length ≤ p) : nt ≤ s.length ∧ LZ77.Valid (bytes s) (toks out nt) := (by
  obtain ⟨hps, hntp, hso, hde⟩ := h
  refine ⟨by omega, ?_⟩
  unfold LZ77.Valid
  rw [hde, show p = s.length by omega, ← bytes_length, List.take_length])
theorem Dec.lit_step {s : Slice Std.U8} {out out1 : Slice Std.U32} {ntU nt1 pU : Std.Usize}
    {b : Std.U8} {v : Std.U32} (h : Dec s out ntU.val pU.val) (hp : pU.val < s.val.length)
    (hb : b = s.val[pU.val]) (hv : v = UScalar.cast .U32 b) (hout1 : out1 = out.set ntU v)
    (hnt1 : nt1.val = ntU.val + 1) :
    nt1.val = ntU.val + 1 ∧ out1.length = out.length ∧ Dec s out1 nt1.val (pU.val + 1) := (by
  subst hout1
  refine ⟨hnt1, Std.Slice.set_length .., ?_⟩
  rw [hnt1]
  exact Dec.lit h hp ntU rfl v (by rw [hv, U8.cast_U32_val_eq, hb, getElem!_pos s.val pU.val hp]))
@[local step]
theorem put_lit_spec (s : Slice Std.U8) (out : Slice Std.U32) (nt p : Std.Usize)
    (hdec : Dec s out nt.val p.val) (hp : p.val < s.length) :
    slot.q4_put_lit s out nt p ⦃ fun r => r.1.val = nt.val + 1 ∧ r.2.length = out.length ∧
      Dec s r.2 r.1.val (p.val + 1) ⦄ := (by
  rw [slot.q4_put_lit]
  step*
  exact Dec.lit_step hdec (by first | assumption | omega | scalar_tac) (by assumption) (by assumption) (by assumption)
    (by assumption))
theorem Dec.match_step {s : Slice Std.U8} {out out1 : Slice Std.U32} {ntU nt1 pU dU lU e : Std.Usize}
    {v : Std.U32} (h : Dec s out ntU.val pU.val) (hm : MatchAt s pU.val lU.val dU.val)
    (hout1 : out1 = out.set ntU v) (hv : v.val = LZ77.mkMatch dU.val lU.val)
    (hnt1 : nt1.val = ntU.val + 1) (he : e.val = pU.val + lU.val) :
    nt1.val = ntU.val + 1 ∧ e.val = pU.val + lU.val ∧ out1.length = out.length ∧
      Dec s out1 nt1.val e.val := (by
  subst hout1
  refine ⟨hnt1, he, Std.Slice.set_length .., ?_⟩
  rw [hnt1, he]
  exact Dec.match h hm ntU rfl v hv)
@[local step]
theorem put_match_spec (s : Slice Std.U8) (out : Slice Std.U32) (nt p d l : Std.Usize)
    (hdec : Dec s out nt.val p.val) (hm : MatchAt s p.val l.val d.val) :
    slot.q4_put_match s out nt p d l ⦃ fun r => r.1.1.val = nt.val + 1 ∧
      r.1.2.val = p.val + l.val ∧ r.2.length = out.length ∧ Dec s r.2 r.1.1.val r.1.2.val ⦄ := (by
  rw [slot.q4_put_match]
  have hm' := hm
  obtain ⟨h3, h258, hpl, hd1, hd32, hdp, _⟩ := hm'
  step*
  exact Dec.match_step hdec hm (by assumption)
    (by simp only [LZ77.mkMatch, LZ77.MATCH_BASE]; simp_all; scalar_tac) (by assumption) (by assumption))
theorem MatchAt.back_lit {s : Slice Std.U8} {p l d : Nat} (h : MatchAt s p l d) (hl : l < 258)
    (hdp : d < p) (heq : s.val[p - 1]! = s.val[p - 1 - d]!) : MatchAt s (p - 1) (l + 1) d := (by
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
theorem MatchAt.back_match {s : Slice Std.U8} {p l d w : Nat} (h : MatchAt s p l d)
    (hlw : l + w ≤ 258) (hw : w ≤ p) (hdw : d ≤ p - w) (hmw : Matches s (p - w - d) (p - w) w) :
    MatchAt s (p - w) (l + w) d := (by
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
    BackInv input out d E P0 i1.val i2.val l1.val := (by
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
theorem BackInv.match {input : Slice Std.U8} {out : Slice Std.U32} {d E P0 : Nat}
    {nt p l i1 w i9 i10 i11 i12 : Std.Usize} {t : Std.U32}
    (h : BackInv input out d E P0 nt.val p.val l.val)
    (hi1 : i1.val = nt.val - 1) (hntl : nt.val ≤ out.length) (hnt0 : 1 ≤ nt.val)
    (hi1l : i1.val < out.val.length) (ht : t = out.val[i1.val])
    (hsame : i12.val = 1 → Matches input i11.val i10.val w.val) (hi12 : i12 = 1#usize)
    (ht24 : 16777216 ≤ t.val) (hwv : w.val = (t.val - 16777216) % 256 + 3)
    (hi9 : i9.val = l.val + w.val) (hi9' : i9.val ≤ 258) (hi10 : i10.val = p.val - w.val)
    (hwp : w.val ≤ p.val) (hdw : d ≤ i10.val) (hi11 : i11.val = i10.val - d) :
    BackInv input out d E P0 i1.val i10.val i9.val := (by
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
theorem fold_loop_inv (input : Slice Std.U8) (out : Slice Std.U32) (nt p l d back : Std.Usize)
    (E P0 : Nat) (hP0 : P0 + 8 ≤ input.length)
    (hinv : BackInv input out d.val E P0 nt.val p.val l.val) :
    slot.q4_fold_loop input out d nt p l back ⦃ fun r =>
      BackInv input out d.val E P0 r.1.val r.2.1.val r.2.2.val ⦄ := (by
  rw [slot.q4_fold_loop]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  apply Std.loop.spec_decr_nat
    (measure := fun r => slot.q4_BACKTOK.val - r.2.2.2.val)
    (inv := fun r => BackInv input out d.val E P0 r.1.val r.2.1.val r.2.2.1.val)
  · rintro ⟨nt, p, l, back⟩ hinv
    simp only at hinv
    have hinv' := hinv
    obtain ⟨⟨hps, hntp, hso, _⟩, ⟨h3, h258, hpl, hd1, hd32, hdp, _⟩, hE, hp0⟩ := hinv'
    simp only [slot.q4_fold_loop.body]
    step*
    all_goals first
      | (refine ⟨hinv, by scalar_tac⟩)
      | (refine ⟨BackInv.lit hinv (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac)
          (by assumption) (by assumption) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by assumption)
          (by assumption) (by assumption) (by first | assumption | omega | scalar_tac) (by assumption) (by first | assumption | omega | scalar_tac)
          (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac), by scalar_tac⟩)
      | (refine ⟨BackInv.match hinv (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac)
          (by assumption) (by assumption) (by assumption) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac)
          (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac)
          (by first | assumption | omega | scalar_tac), by scalar_tac⟩)
  · exact hinv)
@[local step]
theorem fold_spec (input : Slice Std.U8) (out : Slice Std.U32) (nt p l d : Std.Usize)
    (hp8 : p.val + 8 ≤ input.length) (hdec : Dec input out nt.val p.val)
    (hm : MatchAt input p.val l.val d.val) :
    slot.q4_fold input out nt p l d ⦃ fun r =>
      Dec input out r.1.val r.2.1.val ∧ MatchAt input r.2.1.val r.2.2.val d.val ∧
      r.2.1.val + r.2.2.val = p.val + l.val ∧ r.2.1.val ≤ p.val ⦄ := (by
  apply Std.WP.spec_mono (fold_loop_inv input out nt p l d 0#usize (p.val + l.val) p.val hp8
    ⟨hdec, hm, rfl, le_refl _⟩)
  intro r h
  exact h)
@[local step]
theorem fold_w_spec (input : Slice Std.U8) (out : Slice Std.U32) (nt p l d : Std.Usize)
    (hp8 : p.val + 8 ≤ input.length) (hdec : Dec input out nt.val p.val)
    (hm : MatchAt input p.val l.val d.val) :
    slot.q4_fold_w input out nt p l d ⦃ fun r =>
      Dec input out r.1.val r.2.1.val ∧ MatchAt input r.2.1.val r.2.2.val d.val ∧
      r.2.1.val + r.2.2.val = p.val + l.val ∧ r.2.1.val ≤ p.val ⦄ := (by
  rw [slot.q4_fold_w]
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
    LazyInv input L lim out1 nt1.val i.val head1 ins1.val l1.val d1.val := (by
  subst hi
  refine ⟨hdec, hlen, ?_, HeadBound.mono hB hBi, hilim, hins⟩
  rcases hf with h | h
  · omega
  · exact h)
theorem LazyInv.reject {input : Slice Std.U8} {L lim : Nat} {out : Slice Std.U32}
    {nt p ins ins1 l d B : Nat} {N : Std.Usize} {head head1 : Array Std.U32 N}
    (h : LazyInv input L lim out nt p head ins l d) (hB : HeadBound head1 B) (hBp : B ≤ p + 1)
    (hins1 : ins1 ≤ p + 2) : LazyInv input L lim out nt p head1 ins1 l d := (by
  obtain ⟨hdec, hlen, hm, _, hplim, _⟩ := h
  exact ⟨hdec, hlen, hm, HeadBound.mono hB hBp, hplim, hins1⟩)
theorem numBits_ge : 32 ≤ System.Platform.numBits := (by
  rcases System.Platform.numBits_eq with h | h <;> omega)
def MainInv (input : Slice Std.U8) (L : Nat) (out : Slice Std.U32) (nt p : Nat)
    {N : Std.Usize} (head : Array Std.U32 N) (miss : Nat) : Prop :=
  Dec input out nt p ∧ out.length = L ∧ HeadBound head p ∧ miss ≤ p
theorem MainInv.mk' {input : Slice Std.U8} {L : Nat} {out : Slice Std.U32} {nt p m B : Nat}
    {N : Std.Usize} {head : Array Std.U32 N} (hdec : Dec input out nt p) (hlen : out.length = L)
    (hB : HeadBound head B) (hBp : B ≤ p) (hm : m ≤ p) : MainInv input L out nt p head m :=
  ⟨hdec, hlen, HeadBound.mono hB hBp, hm⟩
def CntBound (cnt : Array Std.U32 256#usize) (T : Nat) : Prop :=
  ∀ j : Nat, j < 256 → (cnt.val[j]!).val ≤ T
theorem CntBound.init : CntBound (Std.Array.repeat 256#usize 0#u32) 0 := (by
  intro j hj
  rw [Std.Array.repeat_val, List.getElem!_eq_getElem?_getD,
    List.getElem?_replicate_of_lt (by simpa using hj)]
  rfl)
theorem CntBound.get {cnt : Array Std.U32 256#usize} {T : Nat} (h : CntBound cnt T)
    (a : Std.Usize) (x : Std.U32) (ha : a.val < cnt.val.length) (hx : x = cnt.val[a.val]) :
    x.val ≤ T := (by
  have := h a.val (by simpa using ha)
  rw [getElem!_pos cnt.val a.val ha, ← hx] at this
  exact this)
@[local step]
theorem cnt_index_spec (cnt : Array Std.U32 256#usize) (T : Nat) (h : CntBound cnt T)
    (i : Std.Usize) (hi : i.val < 256) :
    Std.Array.index_usize cnt i ⦃ fun x => x = cnt.val[i.val]! ∧ x.val ≤ T ⦄ := (by
  have hl : i.val < cnt.val.length := by simp; omega
  have := Std.Array.index_usize_spec cnt i (by simpa using hl)
  apply Std.WP.spec_mono this
  intro x hx
  refine ⟨by rw [getElem!_pos cnt.val i.val hl]; exact hx, CntBound.get h i x hl hx⟩)
theorem CntBound.update {cnt : Array Std.U32 256#usize} {T : Nat} (h : CntBound cnt T)
    (a : Std.Usize) (v : Std.U32) (hv : v.val ≤ T + 1) : CntBound (cnt.set a v) (T + 1) := (by
  intro j hj
  rw [Std.Array.set_val_eq]
  by_cases hja : a.val = j
  · subst hja
    have hlen : a.val < cnt.val.length := by simp; omega
    rw [List.getElem!_eq_getElem?_getD, List.getElem?_set_self hlen]
    exact hv
  · rw [List.getElem!_eq_getElem?_getD, List.getElem?_set_ne hja, ← List.getElem!_eq_getElem?_getD]
    exact le_trans (h j hj) (by omega))
theorem CntBound.step {cnt a : Array Std.U32 256#usize} {T : Nat} {x : Std.Usize}
    {v tot1 : Std.U32} (hc : CntBound cnt T) (ha : a = cnt.set x v) (hv : v.val ≤ T + 1)
    (ht1 : tot1.val = T + 1) : CntBound a tot1.val := (by
  rw [ha, ht1]
  exact CntBound.update hc x v hv)
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
    slot.q4_head_set head a i ⦃ fun r => HeadBound r B ⦄ := (by
  rw [slot.q4_head_set]
  step*
  exact HeadBound.update hB (by assumption) (by omega) (by assumption))
@[local step]
theorem ahead_spec {H : Std.Usize} (s : Slice Std.U8) (head : Array Std.U32 H) (i : Std.Usize)
    (B : Nat) (hB : HeadBound head B) (hBn : B + 8 ≤ s.length)
    (hi4 : i.val + 4 ≤ Std.Usize.max) (hH : 0 < H.val) :
    slot.q4_ahead s head i ⦃ fun r => r.1.val < H.val ∧ r.2.1.val ≤ B ∧
      r.2.2.val = word8 s r.2.1.val ⦄ := (by
  rw [slot.q4_ahead]
  step
  step
  have hi1 : i1.val ≤ B := HeadBound.get hB a i1 (by first | assumption | omega | scalar_tac) (by assumption)
  step*)
@[local step]
theorem ahead_if_spec {H : Std.Usize} (s : Slice Std.U8) (head : Array Std.U32 H)
    (i lim a c : Std.Usize) (w : Std.U64) (B : Nat) (hB : HeadBound head B)
    (hBi : B < i.val + 1) (hlim : lim.val + 8 = s.length) (ha : a.val < H.val)
    (hc : c.val < B + 1) (hw : w.val = word8 s c.val) (hH : 0 < H.val) :
    slot.q4_ahead_if s head i lim a c w ⦃ fun r => r.1.val < H.val ∧ r.2.1.val ≤ B ∧
      r.2.2.val = word8 s r.2.1.val ⦄ := (by
  rw [slot.q4_ahead_if]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  step*)
theorem common_from_loop0_spec (s : Slice Std.U8) (a b cap k : Std.Usize) (run : Std.U32)
    (ha : a.val + cap.val ≤ s.length) (hb : b.val + cap.val ≤ s.length) (hcap : cap.val ≤ 258)
    (hk : k.val ≤ cap.val) (hm : Matches s a.val b.val k.val) :
    slot.q4_common_from_loop0 s a b cap k run ⦃ fun r =>
      r.1.val ≤ cap.val ∧ Matches s a.val b.val r.1.val ⦄ := (by
  rw [slot.q4_common_from_loop0]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  apply Std.loop.spec_decr_nat
    (measure := fun r => cap.val - r.1.val + r.2.val)
    (inv := fun r => r.1.val ≤ cap.val ∧ Matches s a.val b.val r.1.val)
  · rintro ⟨k, run⟩ ⟨hk, hm⟩
    simp only at hk hm
    simp only [slot.q4_common_from_loop0.body]
    step*
    all_goals first
      | scalar_tac
      | exact ⟨hk, hm⟩
      | exact wadd_le (by assumption) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac)
      | (refine ⟨by scalar_tac, Matches.xw_zero hm (by assumption) (by assumption) (by first | assumption | omega | scalar_tac)
          (by assumption) (by assumption) (by first | assumption | omega | scalar_tac), by scalar_tac⟩)
      | (have hw := Matches.xw_step hm (by assumption) (by assumption) (by first | assumption | omega | scalar_tac)
          (by assumption) (by assumption) (by assumption) (by assumption) (by assumption)
         refine ⟨by scalar_tac, hw.1, by scalar_tac⟩)
  · exact ⟨hk, hm⟩)
theorem common_from_loop1_spec (s : Slice Std.U8) (a b cap k : Std.Usize) (run : Std.U32)
    (ha : a.val + cap.val ≤ s.length) (hb : b.val + cap.val ≤ s.length)
    (hk : k.val ≤ cap.val) (hm : Matches s a.val b.val k.val) :
    slot.q4_common_from_loop1 s a b cap k run ⦃ fun r =>
      r.val ≤ cap.val ∧ Matches s a.val b.val r.val ⦄ := (by
  rw [slot.q4_common_from_loop1]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  apply Std.loop.spec_decr_nat
    (measure := fun r => cap.val - r.1.val + r.2.val)
    (inv := fun r => r.1.val ≤ cap.val ∧ Matches s a.val b.val r.1.val)
  · rintro ⟨k, run⟩ ⟨hk, hm⟩
    simp only at hk hm
    simp only [slot.q4_common_from_loop1.body]
    step*
    all_goals first
      | scalar_tac
      | exact ⟨hk, hm⟩
      | (refine ⟨by scalar_tac, Matches.byte' hm (by assumption) (by assumption) (by first | assumption | omega | scalar_tac)
          (by first | assumption | omega | scalar_tac) (by assumption) (by assumption) (by assumption) (by assumption),
          by scalar_tac⟩)
  · exact ⟨hk, hm⟩)
@[local step]
theorem common_from_spec (s : Slice Std.U8) (a b cap k0 : Std.Usize)
    (ha : a.val + cap.val ≤ s.length) (hb : b.val + cap.val ≤ s.length) (hcap : cap.val ≤ 258)
    (hk0 : k0.val ≤ cap.val) (hm : Matches s a.val b.val k0.val) :
    slot.q4_common_from s a b cap k0 ⦃ fun l => l.val ≤ cap.val ∧ Matches s a.val b.val l.val ⦄ := (by
  rw [slot.q4_common_from]
  apply Std.WP.spec_bind (common_from_loop0_spec s a b cap k0 1#u32 ha hb hcap hk0 hm)
  rintro ⟨k, run⟩ ⟨hk, hm'⟩
  exact common_from_loop1_spec s a b cap k run ha hb hk hm')
theorem Matches.xor_lz {s : Slice Std.U8} {c p m : Std.Usize} {cw y x : Std.U64}
    {lz q : Std.U32} (hcw : cw.val = word8 s c.val) (hy : y.val = word8 s p.val)
    (hx : x.val = (cw ^^^ y).val) (hx0 : (x != 0#u64) = true)
    (hlz : lz = core.num.U64.leading_zeros x) (hq : q.val = lz.val / 8)
    (hm : m = UScalar.cast .Usize q) : Matches s c.val p.val m.val ∧ m.val < 8 := (by
  have hx0' : ¬x = 0#u64 := by simpa using hx0
  have h := Matches.word_lz (k := 0) (k1 := m) (pa := c) (pb := p)
    (LZ77.Matches.zero s c.val p.val) (by simp) (by simp) hcw hy hx hx0' hlz hq hm (by simp)
  simpa using h)
theorem Matches.xor_zero {s : Slice Std.U8} {c p : Std.Usize} {cw y x : Std.U64}
    (hcw : cw.val = word8 s c.val) (hy : y.val = word8 s p.val)
    (hx : x.val = (cw ^^^ y).val) (hx0 : ¬(x != 0#u64) = true) :
    Matches s c.val p.val (8#usize).val := (by
  have hv : x.val = 0 := by simpa using hx0
  have hx0' : x = 0#u64 := UScalar.eq_of_val_eq (by simp [hv])
  exact Matches.word_zero (k := 0) (k1 := 8#usize) (pa := c) (pb := p)
    (LZ77.Matches.zero s c.val p.val) (by simp) (by simp) hcw hy hx hx0' (by simp))
theorem FoundAt.of_matches {s : Slice Std.U8} {p c d i l : Std.Usize} (hc : c.val ≤ p.val)
    (hd : d = core.num.Usize.wrapping_sub p c) (hi : i = core.num.Usize.wrapping_sub d 1#usize)
    (hlt : i < 32768#usize) (hl : l.val ≤ 258) (hpl : p.val + l.val ≤ s.length)
    (hm : Matches s c.val p.val l.val) :
    FoundAt s p.val l.val d.val ∧ l.val ≤ 258 ∧ d.val ≤ 32768 := (by
  obtain ⟨hdv, hd1, hd2⟩ := dist_of_wrapping hc hd hi hlt
  refine ⟨?_, hl, hd2⟩
  rcases Nat.lt_or_ge l.val 3 with h3 | h3
  · exact Or.inl h3
  · refine Or.inr ⟨h3, hl, hpl, hd1, hd2, by omega, ?_⟩
    rw [show p.val - d.val = c.val by omega]
    exact hm)
theorem FoundAt.none' (s : Slice Std.U8) (p : Nat) :
    FoundAt s p (0#usize).val (0#usize).val ∧ (0#usize).val ≤ 258 ∧ (0#usize).val ≤ 32768 :=
  ⟨FoundAt.none s p, by simp, by simp⟩
@[local step]
theorem xlen_spec (s : Slice Std.U8) (c p : Std.Usize) (x cw y : Std.U64)
    (hx : x.val = (cw ^^^ y).val) (hcw : cw.val = word8 s c.val) (hy : y.val = word8 s p.val)
    (hc : c.val ≤ p.val) (hp : p.val + 8 ≤ s.length) :
    slot.q4_xlen s c p x ⦃ fun r => r.val ≤ 258 ∧ p.val + r.val ≤ s.length ∧
      Matches s c.val p.val r.val ⦄ := (by
  rw [slot.q4_xlen]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  step*
  repeat' (split <;> step*)
  all_goals first
    | exact Matches.xor_zero hcw hy hx (by assumption)
    | (have hw := Matches.xor_lz (m := UScalar.cast .Usize i1) hcw hy hx (by assumption)
        (by assumption) (by assumption) rfl
       exact ⟨by scalar_tac, by scalar_tac, hw.1⟩))
theorem Matches.x16a {s : Slice Std.U8} {c p i1 i2 r l : Std.Usize} {x x2 : Std.U64}
    {lz q : Std.U32} (hx : x.val = word8 s c.val ^^^ word8 s p.val) (hx0 : x = 0#u64)
    (hi1 : i1.val = c.val + 8) (hi2 : i2.val = p.val + 8)
    (hx2 : x2.val = word8 s i1.val ^^^ word8 s i2.val)
    (hlz : lz = core.num.U64.leading_zeros x2) (hq : q.val = lz.val / 8)
    (hr : r = UScalar.cast .Usize q) (hl : l.val = 8 + r.val) :
    Matches s c.val p.val l.val ∧ l.val ≤ 16 := (by
  have h8 := Matches.xz hx hx0
  rw [hi1, hi2] at hx2
  have := Matches.lz_any (k := 8) (k1 := l) h8 hx2 hlz hq hr (by omega)
  exact ⟨this.1, by omega⟩)
theorem Matches.x16a' {s : Slice Std.U8} {c p i1 i2 r l : Std.Usize} {x x2 : Std.U64}
    {lz q : Std.U32} (hx : x.val = word8 s c.val ^^^ word8 s p.val) (hx0 : x = 0#u64)
    (hi1 : i1.val = c.val + 8) (hi2 : i2.val = p.val + 8)
    (hx2 : x2.val = word8 s i1.val ^^^ word8 s i2.val)
    (hlz : lz = core.num.U64.leading_zeros x2) (hq : q.val = lz.val / 8)
    (hr : r = UScalar.cast .Usize q) (hl : l.val = 8 + r.val) (hpn : p.val + 16 ≤ s.length) :
    l.val ≤ 258 ∧ p.val + l.val ≤ s.length ∧ Matches s c.val p.val l.val := (by
  have h := Matches.x16a hx hx0 hi1 hi2 hx2 hlz hq hr hl
  exact ⟨by omega, by omega, h.1⟩)
theorem Matches.x16b {s : Slice Std.U8} {c p r l : Std.Usize} {x : Std.U64}
    {lz q : Std.U32} (hx : x.val = word8 s c.val ^^^ word8 s p.val)
    (hlz : lz = core.num.U64.leading_zeros x) (hq : q.val = lz.val / 8)
    (hr : r = UScalar.cast .Usize q) (hl : l.val = 0 + r.val) (hpn : p.val + 8 ≤ s.length) :
    l.val ≤ 258 ∧ p.val + l.val ≤ s.length ∧ Matches s c.val p.val l.val := (by
  have := Matches.lz_any (k := 0) (k1 := l) (LZ77.Matches.zero s c.val p.val)
    (by simpa using hx) hlz hq hr (by omega)
  exact ⟨by omega, by omega, this.1⟩)
@[local step]
theorem xlen16_spec (s : Slice Std.U8) (c p : Std.Usize) (x cw y : Std.U64)
    (hx : x.val = (cw ^^^ y).val) (hcw : cw.val = word8 s c.val) (hy : y.val = word8 s p.val)
    (hc : c.val ≤ p.val) (hp : p.val + 8 ≤ s.length) :
    slot.q4_xlen16 s c p x ⦃ fun r => r.val ≤ 258 ∧ p.val + r.val ≤ s.length ∧
      Matches s c.val p.val r.val ⦄ := (by
  rw [slot.q4_xlen16]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  have hxv := xval_of hx hcw hy
  step*
  repeat' (split <;> step*)
  all_goals first
    | exact Matches.mono (Matches.x16a hxv (by assumption) (by assumption) (by assumption)
        (by assumption) (by assumption) (by assumption) (by assumption) (by assumption)).1
        (by first | assumption | omega | scalar_tac)
    | exact Matches.x16a' hxv (by assumption) (by assumption) (by assumption) (by assumption)
        (by assumption) (by assumption) (by assumption) (by assumption) (by first | assumption | omega | scalar_tac)
    | exact Matches.x16b hxv (by assumption) (by assumption) (by assumption) (by assumption)
        (by first | assumption | omega | scalar_tac))
@[local step]
theorem probe_spec (s : Slice Std.U8) (c : Std.Usize) (cw : Std.U64) (p : Std.Usize)
    (hc : c.val ≤ p.val) (hcw : cw.val = word8 s c.val) (hp : p.val + 8 ≤ s.length) :
    slot.q4_probe s c cw p ⦃ fun r => FoundAt s p.val r.1.val r.2.val ∧ r.1.val ≤ 258 ∧
      r.2.val ≤ 32768 ⦄ := (by
  rw [slot.q4_probe]
  step*
  all_goals first
    | exact FoundAt.none' s p.val
    | exact FoundAt.of_matches hc (by assumption) (by assumption) (by assumption)
        (by assumption) (by assumption) (by assumption))
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
      r.2.val ≤ 32768 ⦄ := (by
  rw [slot.q4_probe_lazy]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  have hL : 1 ≤ slot.q4_LSLACK.val := by scalar_tac
  step
  have hlo : q.val + lo.val ≤ s.length := by
    rcases lo_post with h | ⟨_, h⟩ <;> omega
  step*
  all_goals first
    | exact FoundAt.none' s q.val
    | exact FoundAt.of_matches hc (by assumption) (by assumption) (by assumption)
        (by assumption) (by assumption) (by assumption))
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
      r.2.2.val = word8 s r.2.1.val ⦄ := (by
  rw [slot.q4_ahead_m]
  step
  step
  have hi1 : i1.val ≤ B := HeadBound.get hB a i1 (by first | assumption | omega | scalar_tac) (by assumption)
  step*)
@[local step]
theorem ahead_if_m_spec {H : Std.Usize} (s : Slice Std.U8) (head : Array Std.U32 H)
    (i lim a c : Std.Usize) (w : Std.U64) (km : Std.U32) (B : Nat) (hB : HeadBound head B)
    (hBi : B < i.val + 1) (hlim : lim.val + 8 = s.length) (ha : a.val < H.val)
    (hc : c.val < B + 1) (hw : w.val = word8 s c.val) (hH : 0 < H.val) :
    slot.q4_ahead_if_m s head i lim a c w km ⦃ fun r => r.1.val < H.val ∧ r.2.1.val ≤ B ∧
      r.2.2.val = word8 s r.2.1.val ⦄ := (by
  rw [slot.q4_ahead_if_m]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  step*)
@[local step]
theorem ahead_fix_m_spec {H : Std.Usize} (s : Slice Std.U8) (head : Array Std.U32 H)
    (i lim e a c : Std.Usize) (w : Std.U64) (a0 c0 : Std.Usize) (w0 : Std.U64) (km : Std.U32)
    (B : Nat) (hB : HeadBound head B) (hBi : B < i.val + 1) (hlim : lim.val + 8 = s.length)
    (hw : w.val = word8 s c.val) (ha0 : a0.val < H.val) (hc0 : c0.val < B + 1)
    (hw0 : w0.val = word8 s c0.val) (hH : 0 < H.val) :
    slot.q4_ahead_fix_m s head i lim e a c w a0 c0 w0 km ⦃ fun r => r.1.val < H.val ∧
      r.2.1.val ≤ B ∧ r.2.2.val = word8 s r.2.1.val ⦄ := (by
  rw [slot.q4_ahead_fix_m]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  step*
  all_goals first
    | (have hi1 := HeadBound.get hB a i1 (by first | assumption | omega | scalar_tac) (by assumption)
       exact ⟨by scalar_tac, by scalar_tac, hw⟩))
@[local step]
theorem probe_m_spec (s : Slice Std.U8) (c : Std.Usize) (cw : Std.U64) (p : Std.Usize)
    (km : Std.U32) (hc : c.val ≤ p.val) (hcw : cw.val = word8 s c.val)
    (hp : p.val + 8 ≤ s.length) :
    slot.q4_probe_m s c cw p km ⦃ fun r => FoundAt s p.val r.1.val r.2.val ∧ r.1.val ≤ 258 ∧
      r.2.val ≤ 32768 ⦄ := (by
  rw [slot.q4_probe_m]
  step*
  all_goals first
    | exact FoundAt.none' s p.val
    | exact FoundAt.of_matches hc (by assumption) (by assumption) (by assumption)
        (by assumption) (by assumption) (by assumption))
theorem flush_loop_spec (input : Slice Std.U8) (out : Slice Std.U32) (e nt j : Std.Usize)
    (hdec : Dec input out nt.val j.val) (he : e.val ≤ input.length) (hj : j.val ≤ e.val) :
    slot.q4_flush_loop input out e nt j ⦃ fun r => Dec input r.2 r.1.val e.val ∧
      r.2.length = out.length ⦄ := (by
  rw [slot.q4_flush_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun r => e.val - r.2.2.val)
    (inv := fun r => Dec input r.1 r.2.1.val r.2.2.val ∧ r.1.length = out.length ∧
      r.2.2.val ≤ e.val)
  · rintro ⟨out', nt', j'⟩ ⟨hdec', hlen', hj'⟩
    simp only at hdec' hlen' hj'
    simp only [slot.q4_flush_loop.body]
    step*
  · exact ⟨hdec, rfl, hj⟩)
@[local step]
theorem flush_spec (input : Slice Std.U8) (out : Slice Std.U32) (nt a e : Std.Usize)
    (hdec : Dec input out nt.val a.val) (he : e.val ≤ input.length) (ha : a.val ≤ e.val) :
    slot.q4_flush input out nt a e ⦃ fun r => Dec input r.2 r.1.val e.val ∧
      r.2.length = out.length ⦄ :=
  flush_loop_spec input out e nt a hdec he ha
@[local step]
theorem v27z {H : Std.Usize} (s : Slice Std.U8) (head : Array Std.U32 H)
    (ins stop : Std.Usize) (B : Nat) (hB : HeadBound head B) (hsB : stop.val < B + 1)
    (hs4 : stop.val + 4 ≤ Std.Usize.max) (hH : 0 < H.val) :
    slot.q4_record_loop0 s head ins stop ⦃ fun r =>
      HeadBound r.1 B ∧ (r.2.val ≤ ins.val ∨ r.2.val ≤ stop.val) ⦄ := (by
  rw [slot.q4_record_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun r => stop.val - r.2.val)
    (inv := fun r => HeadBound r.1 B ∧ (r.2.val ≤ ins.val ∨ r.2.val ≤ stop.val))
  · rintro ⟨head, ins'⟩ ⟨hB, hins⟩
    simp only at hB hins
    simp only [slot.q4_record_loop0.body]
    step*
  · exact ⟨hB, Or.inl (le_refl _)⟩)
@[local step]
theorem v28z {H : Std.Usize} (s : Slice Std.U8) (head : Array Std.U32 H)
    («end» lim ins : Std.Usize) (B : Nat) (hB : HeadBound head B) (heB : «end».val < B + 1)
    (hl4 : lim.val + 4 ≤ Std.Usize.max) (hH : 0 < H.val) :
    slot.q4_record_loop1 s head «end» lim ins ⦃ fun r => HeadBound r B ⦄ := (by
  rw [slot.q4_record_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun r => «end».val - r.2.val)
    (inv := fun r => HeadBound r.1 B)
  · rintro ⟨head, ins'⟩ hB
    simp only at hB
    simp only [slot.q4_record_loop1.body]
    step*
  · exact hB)
@[local step]
theorem record_spec {H : Std.Usize} (s : Slice Std.U8) (head : Array Std.U32 H)
    (ins0 «end» lim : Std.Usize) (B : Nat) (hB : HeadBound head B) (heB : «end».val < B + 1)
    (hlim : lim.val + 8 = s.length) (hins : ins0.val ≤ lim.val + 1) (hH : 0 < H.val) :
    slot.q4_record s head ins0 «end» lim ⦃ fun r => HeadBound r B ⦄ := (by
  rw [slot.q4_record]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  step*
  repeat' (split <;> step*))
theorem Dec.set_beyond {s : Slice Std.U8} {out : Slice Std.U32} {nt p : Nat} (h : Dec s out nt p)
    (i : Std.Usize) (v : Std.U32) (hi : nt ≤ i.val) : Dec s (out.set i v) nt p := (by
  obtain ⟨hps, hntp, hso, hde⟩ := h
  refine ⟨hps, hntp, by rw [Std.Slice.set_length]; exact hso, ?_⟩
  have : toks (out.set i v) nt = toks out nt := by
    simp only [toks, Std.Slice.set_val_eq, List.take_set]
    rw [List.set_eq_of_length_le (by rw [List.length_take]; omega)]
  rw [this]; exact hde)
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
    Dec s out4 r.val e.val ∧ out4.length = out.length := (by
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
@[local step]
theorem flush4_spec (input : Slice Std.U8) (out : Slice Std.U32) (nt a e : Std.Usize)
    (hdec : Dec input out nt.val a.val) (he : e.val + 8 ≤ input.length) (ha : a.val ≤ e.val) :
    slot.q4_flush4 input out nt a e ⦃ fun r => Dec input r.2 r.1.val e.val ∧
      r.2.length = out.length ⦄ := (by
  rw [slot.q4_flush4]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  step*
  all_goals first
    | (constructor; first | (convert hdec using 1 <;> scalar_tac) | rfl)
    | exact flush_spec input out nt a e hdec (by first | assumption | omega | scalar_tac) ha
    | (subst_vars; simp only [Std.Slice.set_length]; scalar_tac)
    | exact Dec.flush4_step hdec ha (by assumption) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac)
        (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by assumption) (by assumption) (by assumption)
        (by assumption) (by first | assumption | omega | scalar_tac) (by assumption) (by assumption) (by assumption)
        (by assumption) (by assumption) (by first | assumption | omega | scalar_tac) (by assumption) (by assumption)
        (by assumption) (by assumption) (by assumption) (by first | assumption | omega | scalar_tac) (by assumption)
        (by assumption) (by assumption) (by assumption) (by assumption))
@[local step]
theorem record3_m_loop0_spec {H : Std.Usize} (s : Slice Std.U8) (head : Array Std.U32 H)
    (km : Std.U32) (ins stop : Std.Usize) (B : Nat) (hB : HeadBound head B)
    (hsB : stop.val < B + 1) (hs4 : stop.val + 4 ≤ Std.Usize.max) (hH : 0 < H.val) :
    slot.q4_record3_m_loop0 s head km ins stop ⦃ fun r =>
      HeadBound r.1 B ∧ (r.2.val ≤ ins.val ∨ r.2.val ≤ stop.val) ⦄ := (by
  rw [slot.q4_record3_m_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun r => stop.val - r.2.val)
    (inv := fun r => HeadBound r.1 B ∧ (r.2.val ≤ ins.val ∨ r.2.val ≤ stop.val))
  · rintro ⟨head, ins'⟩ ⟨hB, hins⟩
    simp only at hB hins
    simp only [slot.q4_record3_m_loop0.body]
    step*
  · exact ⟨hB, Or.inl (le_refl _)⟩)
@[local step]
theorem record3_m_loop1_spec {H : Std.Usize} (s : Slice Std.U8) (head : Array Std.U32 H)
    («end» lim : Std.Usize) (km : Std.U32) (ins : Std.Usize) (B : Nat) (hB : HeadBound head B)
    (heB : «end».val < B + 1) (hl4 : lim.val + 4 ≤ Std.Usize.max) (hH : 0 < H.val) :
    slot.q4_record3_m_loop1 s head «end» lim km ins ⦃ fun r => HeadBound r B ⦄ := (by
  rw [slot.q4_record3_m_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun r => «end».val - r.2.val)
    (inv := fun r => HeadBound r.1 B)
  · rintro ⟨head, ins'⟩ hB
    simp only at hB
    simp only [slot.q4_record3_m_loop1.body]
    step*
  · exact hB)
@[local step]
theorem record3_m_spec {H : Std.Usize} (s : Slice Std.U8) (head : Array Std.U32 H)
    (ins0 a0 «end» lim : Std.Usize) (km : Std.U32) (B : Nat) (hB : HeadBound head B)
    (heB : «end».val < B + 1) (hlim : lim.val + 8 = s.length) (hins : ins0.val ≤ lim.val + 1)
    (hH : 0 < H.val) :
    slot.q4_record3_m s head ins0 a0 «end» lim km ⦃ fun r => HeadBound r B ⦄ := (by
  rw [slot.q4_record3_m]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  step*
  repeat' (split <;> step*))
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
    LazyInv1 input lim P0 p head1 ps1 pc1 pw1 l d ins1 := (by
  obtain ⟨hm, _, hplim, _, _, _, _, hP⟩ := h
  exact ⟨hm, HeadBound.mono hB hBp, hplim, hins1, hps, hpc, hpw, hP⟩)
theorem lazy1_loop_inv {H : Std.Usize} (input : Slice Std.U8) (lazy : Std.Usize) (km : Std.U32)
    (p : Std.Usize)
    (head : Array Std.U32 H) (lim pre_slot pre_c : Std.Usize) (pre_w : Std.U64)
    (l d ins : Std.Usize) (go : Std.U32) (P0 : Nat)
    (hlim : lim.val + 8 = input.length) (hH : 0 < H.val)
    (hinv : LazyInv1 input lim.val P0 p.val head pre_slot.val pre_c.val pre_w.val l.val d.val
      ins.val) :
    slot.q4_run1_loop0_loop0 input lazy km p head lim pre_slot pre_c pre_w l d ins go ⦃ fun r =>
      LazyInv1 input lim.val P0 r.1.val r.2.1 r.2.2.1.val r.2.2.2.1.val r.2.2.2.2.1.val
        r.2.2.2.2.2.1.val r.2.2.2.2.2.2.1.val r.2.2.2.2.2.2.2.val ⦄ := (by
  rw [slot.q4_run1_loop0_loop0]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  apply Std.loop.spec_decr_nat
    (measure := fun r => lim.val - r.1.val + r.2.2.2.2.2.2.2.2.val)
    (inv := fun r => LazyInv1 input lim.val P0 r.1.val r.2.1 r.2.2.1.val r.2.2.2.1.val
      r.2.2.2.2.1.val r.2.2.2.2.2.1.val r.2.2.2.2.2.2.1.val r.2.2.2.2.2.2.2.1.val)
  · rintro ⟨p, head, pre_slot, pre_c, pre_w, l, d, ins, go⟩ hinv
    simp only at hinv
    have hinv' := hinv
    obtain ⟨⟨h3, h258, hpl, hd1, hd32, hdp, _⟩, hB, hplim, hins, hslot, hpc, hpw, hP⟩ := hinv'
    simp only [slot.q4_run1_loop0_loop0.body]
    step*
    all_goals first
      | (refine ⟨LazyInv1.accept (by assumption) (by first | assumption | omega | scalar_tac) (by assumption) (by first | assumption | omega | scalar_tac)
          (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by assumption)
          (by first | assumption | omega | scalar_tac), by scalar_tac⟩)
      | (refine ⟨LazyInv1.reject hinv (by assumption) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac)
          (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by assumption), by scalar_tac⟩)
  · exact hinv)
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
      r.2.2.2.2.1.val = word8 input r.2.2.2.1.val ∧ p.val ≤ r.1.val ⦄ := (by
  apply Std.WP.spec_mono (lazy1_loop_inv input lazy km p head lim pre_slot pre_c pre_w l d ins go
    p.val hlim hH ⟨hm, hB, hplim, hins, hps, hpc, hpw, le_refl _⟩)
  rintro ⟨p', head', ps', pc', pw', l', d', ins'⟩ ⟨hm', hB', hplim', hins', hps', hpc', hpw', hP'⟩
  exact ⟨hm', HeadBound.mono hB' (by have := hm'.1; omega), hplim', hins', hm'.1, hps', hpc',
    hpw', hP'⟩)
@[local step]
theorem tail1_loop1_spec (input : Slice Std.U8) (out : Slice Std.U32) (n nt p : Std.Usize)
    (hn : n.val = input.length) (hdec : Dec input out nt.val p.val) :
    slot.q4_run1_loop1 input out n nt p ⦃ fun r => r.1.val ≤ input.length ∧
      r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := (by
  rw [slot.q4_run1_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun r => n.val - r.2.2.val)
    (inv := fun r => Dec input r.1 r.2.1.val r.2.2.val ∧ r.1.length = out.length)
  · rintro ⟨out', nt', p'⟩ ⟨hdec', hlen'⟩
    simp only at hdec' hlen'
    simp only [slot.q4_run1_loop1.body]
    step*
    have hd := Dec.done hdec' (by first | assumption | omega | scalar_tac)
    exact ⟨hd.1, hlen', hd.2⟩
  · exact ⟨hdec, rfl⟩)
@[local step]
theorem tail1_loop2_spec (input : Slice Std.U8) (out : Slice Std.U32) (n nt p : Std.Usize)
    (hn : n.val = input.length) (hdec : Dec input out nt.val p.val) :
    slot.q4_run1_loop2 input out n nt p ⦃ fun r => r.1.val ≤ input.length ∧
      r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := (by
  rw [slot.q4_run1_loop2]
  apply Std.loop.spec_decr_nat
    (measure := fun r => n.val - r.2.2.val)
    (inv := fun r => Dec input r.1 r.2.1.val r.2.2.val ∧ r.1.length = out.length)
  · rintro ⟨out', nt', p'⟩ ⟨hdec', hlen'⟩
    simp only at hdec' hlen'
    simp only [slot.q4_run1_loop2.body]
    step*
    have hd := Dec.done hdec' (by first | assumption | omega | scalar_tac)
    exact ⟨hd.1, hlen', hd.2⟩
  · exact ⟨hdec, rfl⟩)
def MainInv1 (input : Slice Std.U8) (L : Nat) (out : Slice Std.U32) (nt ls p : Nat)
    {N : Std.Usize} (head : Array Std.U32 N) (miss ps pc pw : Nat) : Prop :=
  Dec input out nt ls ∧ out.length = L ∧ ls ≤ p ∧ HeadBound head p ∧ miss ≤ p ∧ ps < N.val ∧
    pc ≤ p ∧ pw = word8 input pc
theorem MainInv1.mk' {input : Slice Std.U8} {L : Nat} {out : Slice Std.U32}
    {nt ls ls' p m B ps pc pw : Nat} {N : Std.Usize} {head : Array Std.U32 N}
    (hdec : Dec input out nt ls') (hls : ls' = ls) (hlen : out.length = L) (hlsp : ls ≤ p)
    (hB : HeadBound head B) (hBp : B ≤ p) (hm : m ≤ p) (hps : ps < N.val) (hpc : pc ≤ p)
    (hpw : pw = word8 input pc) : MainInv1 input L out nt ls p head m ps pc pw := (by
  subst hls
  exact ⟨hdec, hlen, hlsp, HeadBound.mono hB hBp, hm, hps, hpc, hpw⟩)
set_option maxHeartbeats 16000000 in
theorem main1_loop_spec {H : Std.Usize} (input : Slice Std.U8) (out : Slice Std.U32)
    (skip lazy skcap : Std.Usize) (km : Std.U32) (nt ls p : Std.Usize) (head : Array Std.U32 H)
    (lim miss fuel pre_slot pre_c : Std.Usize) (pre_w : Std.U64) (L : Nat)
    (hlim : lim.val + 8 = input.length) (hskip : skip.val < 32) (hH : 0 < H.val)
    (hinv : MainInv1 input L out nt.val ls.val p.val head miss.val pre_slot.val pre_c.val
      pre_w.val) :
    slot.q4_run1_loop0 input out skip lazy skcap km nt ls p head lim miss fuel pre_slot pre_c pre_w
      ⦃ fun r => Dec input r.1 r.2.1.val r.2.2.val ∧ r.1.length = L ⦄ := (by
  rw [slot.q4_run1_loop0]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  apply Std.loop.spec_decr_nat
    (measure := fun r => r.2.2.2.2.2.2.1.val)
    (inv := fun r => MainInv1 input L r.1 r.2.1.val r.2.2.1.val r.2.2.2.1.val r.2.2.2.2.1
      r.2.2.2.2.2.1.val r.2.2.2.2.2.2.2.1.val r.2.2.2.2.2.2.2.2.1.val r.2.2.2.2.2.2.2.2.2.val)
  · rintro ⟨out, nt, ls, p, head, miss, fuel, pre_slot, pre_c, pre_w⟩ hinv
    simp only at hinv
    have hinv' := hinv
    obtain ⟨hdec, hL, hlsp, hB, hmiss, hps, hpc, hpw⟩ := hinv'
    simp only [slot.q4_run1_loop0.body]
    step*
    all_goals try (obtain ⟨i4, i5, i6⟩ := ae; dsimp only at *; step*)
    all_goals first
      | exact FoundAt.real (by assumption) (by first | assumption | omega | scalar_tac)
      | exact HeadBound.mono (by assumption) (by first | assumption | omega | scalar_tac)
      | (refine ⟨MainInv1.mk' (by assumption) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac)
          (by assumption) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac)
          (by assumption), by scalar_tac⟩)
  · exact hinv)
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
      r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := (by
  rw [slot.q4_run1]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  have hB0 : HeadBound (Std.Array.repeat H 0#u32) 0 := HeadBound.init H
  have hdec0 : Dec input out (0#usize).val (0#usize).val := Dec.init input out hlen
  step*)
def LensBound (lens : Array Std.U16 260#usize) : Prop :=
  ∀ j : Nat, j < lens.val.length → (lens.val[j]!).val ≤ 258
theorem LensBound.init : LensBound (Std.Array.repeat 260#usize 0#u16) := (by
  intro j hj
  rw [Std.Array.repeat_val] at hj ⊢
  rw [List.getElem!_eq_getElem?_getD, List.getElem?_replicate_of_lt (by simpa using hj)]
  simp)
theorem LensBound.update {lens lens1 : Array Std.U16 260#usize} (h : LensBound lens)
    {a : Std.Usize} {v : Std.U16} (hv : v.val ≤ 258) (h1 : lens1 = lens.set a v) :
    LensBound lens1 := (by
  subst h1
  intro j hj
  rw [Std.Array.set_val_eq] at hj ⊢
  rw [List.length_set] at hj
  by_cases hja : a.val = j
  · subst hja
    rw [List.getElem!_eq_getElem?_getD, List.getElem?_set_self hj]
    exact hv
  · rw [List.getElem!_eq_getElem?_getD, List.getElem?_set_ne hja, ← List.getElem!_eq_getElem?_getD]
    exact h j hj)
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
theorem v0z (lens : Array Std.U16 260#usize) (m : Std.U32) (cur : Std.U16)
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
      | (refine ⟨LensBound.update_cast hl (by assumption) (by first | assumption | omega | scalar_tac),
          cast_u16_le' (by first | assumption | omega | scalar_tac), by scalar_tac⟩)
      | (refine ⟨LensBound.update hl hc (by assumption), hc, by scalar_tac⟩)
  · exact ⟨hl, hc⟩
@[local step]
theorem e_lens_spec (lens : Array Std.U16 260#usize) (m : Std.U32) (hl : LensBound lens) :
    slot.q4_e_lens lens m ⦃ fun r => LensBound r ⦄ :=
  v0z lens m 0#u16 3#usize hl (by simp)
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
theorem v8z (input : Slice Std.U8) (out : Slice Std.U32) (d bt nt p l back : Std.Usize)
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
      | (refine ⟨BackInv.lit hinv (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac)
          (by assumption) (by assumption) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by assumption)
          (by assumption) (by assumption) (by first | assumption | omega | scalar_tac) (by assumption) (by first | assumption | omega | scalar_tac)
          (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac), by scalar_tac⟩)
      | (refine ⟨BackInv.match hinv (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac)
          (by assumption) (by assumption) (by assumption) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac)
          (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac)
          (by first | assumption | omega | scalar_tac), by scalar_tac⟩)
  · exact hinv
@[local step]
theorem fold_bt_spec (input : Slice Std.U8) (out : Slice Std.U32) (nt p l d bt : Std.Usize)
    (hp8 : p.val + 8 ≤ input.length) (hdec : Dec input out nt.val p.val)
    (hm : MatchAt input p.val l.val d.val) :
    slot.q4_fold_bt input out nt p l d bt ⦃ fun r =>
      Dec input out r.1.val r.2.1.val ∧ MatchAt input r.2.1.val r.2.2.val d.val ∧
      r.2.1.val + r.2.2.val = p.val + l.val ∧ r.2.1.val ≤ p.val ⦄ := by
  apply Std.WP.spec_mono (v8z input out d bt nt p l 0#usize (p.val + l.val) p.val hp8
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
theorem v1z (input : Slice Std.U8) (out : Slice Std.U32) (d : Std.Usize)
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
      | exact MatchAt.piece hm' hd1 hd32 hdq' hen (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac)
      | (refine ⟨by assumption, by scalar_tac, by scalar_tac, by scalar_tac,
          Matches.after_piece hm' (by assumption) hdq' (by first | assumption | omega | scalar_tac), by scalar_tac⟩)
  · exact ⟨hdec, rfl, hqe, hdq, hm⟩
@[local step]
theorem v2z (input : Slice Std.U8) (out : Slice Std.U32) (nt q «end» : Std.Usize)
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
    | exact Matches.mono hm (by first | assumption | omega | scalar_tac)
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
        r.2.2.2.2.2.1.val r.2.2.2.2.2.2.1.val r.2.2.2.2.2.2.2.val ⦄ := (by
  rw [slot.q4_run1t_loop0_loop0]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  apply Std.loop.spec_decr_nat
    (measure := fun r => lim.val - r.1.val + r.2.2.2.2.2.2.2.2.val)
    (inv := fun r => LazyInv1 input lim.val P0 r.1.val r.2.1 r.2.2.1.val r.2.2.2.1.val
      r.2.2.2.2.1.val r.2.2.2.2.2.1.val r.2.2.2.2.2.2.1.val r.2.2.2.2.2.2.2.1.val)
  · rintro ⟨p, head, pre_slot, pre_c, pre_w, l, d, ins, go⟩ hinv
    simp only at hinv
    have hinv' := hinv
    obtain ⟨⟨h3, h258, hpl, hd1, hd32, hdp, _⟩, hB, hplim, hins, hslot, hpc, hpw, hP⟩ := hinv'
    simp only [slot.q4_run1t_loop0_loop0.body]
    step*
    all_goals first
      | (refine ⟨LazyInv1.accept (by assumption) (by first | assumption | omega | scalar_tac) (by assumption) (by first | assumption | omega | scalar_tac)
          (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by assumption)
          (by first | assumption | omega | scalar_tac), by scalar_tac⟩)
      | (refine ⟨LazyInv1.reject hinv (by assumption) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac)
          (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by assumption), by scalar_tac⟩)
  · exact hinv)
@[local step]
theorem v16z {H : Std.Usize} (input : Slice Std.U8) (lazy p : Std.Usize)
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
theorem v32z (input : Slice Std.U8) (out : Slice Std.U32) (n nt p : Std.Usize)
    (hn : n.val = input.length) (hdec : Dec input out nt.val p.val) :
    slot.q4_run1t_loop1 input out n nt p ⦃ fun r => r.1.val ≤ input.length ∧
      r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := (by
  rw [slot.q4_run1t_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun r => n.val - r.2.2.val)
    (inv := fun r => Dec input r.1 r.2.1.val r.2.2.val ∧ r.1.length = out.length)
  · rintro ⟨out', nt', p'⟩ ⟨hdec', hlen'⟩
    simp only at hdec' hlen'
    simp only [slot.q4_run1t_loop1.body]
    step*
    have hd := Dec.done hdec' (by first | assumption | omega | scalar_tac)
    exact ⟨hd.1, hlen', hd.2⟩
  · exact ⟨hdec, rfl⟩)
@[local step]
theorem v33z (input : Slice Std.U8) (out : Slice Std.U32) (n nt p : Std.Usize)
    (hn : n.val = input.length) (hdec : Dec input out nt.val p.val) :
    slot.q4_run1t_loop2 input out n nt p ⦃ fun r => r.1.val ≤ input.length ∧
      r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := (by
  rw [slot.q4_run1t_loop2]
  apply Std.loop.spec_decr_nat
    (measure := fun r => n.val - r.2.2.val)
    (inv := fun r => Dec input r.1 r.2.1.val r.2.2.val ∧ r.1.length = out.length)
  · rintro ⟨out', nt', p'⟩ ⟨hdec', hlen'⟩
    simp only at hdec' hlen'
    simp only [slot.q4_run1t_loop2.body]
    step*
    have hd := Dec.done hdec' (by first | assumption | omega | scalar_tac)
    exact ⟨hd.1, hlen', hd.2⟩
  · exact ⟨hdec, rfl⟩)
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
      | exact FoundAt.real (by assumption) (by first | assumption | omega | scalar_tac)
      | exact HeadBound.mono (by assumption) (by first | assumption | omega | scalar_tac)
      | (refine ⟨MainInv1.mk' (by assumption) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac)
          (by assumption) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac)
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
@[local step]
theorem v18z (input : Slice Std.U8) (out : Slice Std.U32) (n nt p : Std.Usize)
    (hn : n.val = input.length) (hdec : Dec input out nt.val p.val) :
    slot.q4_lit_all_loop input out n nt p ⦃ fun r => r.1.val ≤ input.length ∧
      r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := (by
  rw [slot.q4_lit_all_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun r => n.val - r.2.2.val)
    (inv := fun r => Dec input r.1 r.2.1.val r.2.2.val ∧ r.1.length = out.length)
  · rintro ⟨out', nt', p'⟩ ⟨hdec', hlen'⟩
    simp only at hdec' hlen'
    simp only [slot.q4_lit_all_loop.body]
    step*
    have hd := Dec.done hdec' (by first | assumption | omega | scalar_tac)
    exact ⟨hd.1, hlen', hd.2⟩
  · exact ⟨hdec, rfl⟩)
@[local step]
theorem lit_all_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) :
 slot.q4_lit_all input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.q4_lit_all]
 have hd : Dec input out (0#usize).val (0#usize).val := Dec.init input out hlen
 step*
end Q4
set_option linter.unusedSimpArgs false
set_option linter.unusedVariables false
set_option linter.unusedTactic false
set_option linter.unreachableTactic false
namespace P12
open Aeneas Aeneas.Std Result ControlFlow
open LZ77 (toks bytes)
set_option maxRecDepth 8192
theorem r70_ite_true_spec {α : Type} (c : Prop) [Decidable c] (A B : Result α)
 (hA : c → A ⦃ fun _ => True ⦄) (hB : ¬c → B ⦃ fun _ => True ⦄) :
 (if c then A else B) ⦃ fun _ => True ⦄ := (by
 by_cases h : c
 · rw [if_pos h]; exact hA h
 · rw [if_neg h]; exact hB h)
namespace EF32
open Aeneas Aeneas.Std Result ControlFlow
open LZ77 (toks bytes Matches)
set_option maxRecDepth 8192
set_option maxHeartbeats 4000000
set_option linter.unusedVariables false
theorem numBits_ge : 32 ≤ System.Platform.numBits := (by
  cases System.Platform.numBits_eq <;> simp [*])
@[local scalar_tac System.Platform.numBits]
theorem numBits_ge' : 32 ≤ System.Platform.numBits := numBits_ge
@[local step]
theorem lift_spec {α : Type} (x : α) : lift x ⦃ fun y => y = x ⦄ := (by
  simp [lift, WP.spec_ok])
@[local step]
theorem v26z (input : Slice Std.U8) (out : Slice Std.U32) (tt nt j : Std.Usize)
    (hto : tt.val ≤ input.length) (hj : j.val ≤ tt.val) (hdec : Q4.Dec input out nt.val j.val) :
    slot.p12_ef32_put_lits_loop input out tt nt j ⦃ fun r => r.2.length = out.length ∧
      Q4.Dec input r.2 r.1.val tt.val ⦄ := by
  rw [slot.p12_ef32_put_lits_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun r => tt.val - r.2.2.val)
    (inv := fun r => Q4.Dec input r.1 r.2.1.val r.2.2.val ∧ r.1.length = out.length ∧
      r.2.2.val ≤ tt.val)
  · rintro ⟨out', nt', j'⟩ ⟨hdec', hlen', hj'⟩
    simp only at hdec' hlen' hj'
    simp only [slot.p12_ef32_put_lits_loop.body]
    step*
    have hs := Q4.Dec.lit_step hdec' (by first | assumption | omega | scalar_tac) i_post i1_post s_post nt1_post
    refine ⟨by rw [j1_post]; exact hs.2.2, by rw [hs.2.1, hlen'], by scalar_tac, by scalar_tac⟩
  · exact ⟨hdec, rfl, hj⟩
@[local step]
theorem put_lits_spec (input : Slice Std.U8) (out : Slice Std.U32) (nt fr tt : Std.Usize)
    (hto : tt.val ≤ input.length) (hj : fr.val ≤ tt.val) (hdec : Q4.Dec input out nt.val fr.val) :
    slot.p12_ef32_put_lits input out nt fr tt ⦃ fun r => r.2.length = out.length ∧
      Q4.Dec input r.2 r.1.val tt.val ⦄ := by
  rw [slot.p12_ef32_put_lits]
  exact v26z input out tt nt fr hto hj hdec
@[local step]
theorem match_len_loop_spec (input : Slice Std.U8) (a b cap l : Std.Usize)
    (hab : a.val < b.val) (hcap : b.val + cap.val ≤ input.length) (hl : l.val ≤ cap.val)
    (hm : Matches input a.val b.val l.val) :
    slot.p12_ef32_match_len_loop input a b cap l ⦃ fun r => r.val ≤ cap.val ∧
      Matches input a.val b.val r.val ⦄ := by
  rw [slot.p12_ef32_match_len_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun r => cap.val - r.val)
    (inv := fun r => r.val ≤ cap.val ∧ Matches input a.val b.val r.val)
  · rintro l' ⟨hl', hm'⟩
    simp only [slot.p12_ef32_match_len_loop.body]
    step*
    rename_i hxy
    exact ⟨by scalar_tac, Q4.Matches.byte' hm' i_post i2_post (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac)
      i1_post i3_post hxy l1_post, by scalar_tac⟩
  · exact ⟨hl, hm⟩
@[local step]
theorem match_len_spec (input : Slice Std.U8) (a b cap : Std.Usize)
    (hab : a.val < b.val) (hcap : b.val + cap.val ≤ input.length) :
    slot.p12_ef32_match_len input a b cap ⦃ fun r => r.val ≤ cap.val ∧
      Matches input a.val b.val r.val ⦄ := by
  rw [slot.p12_ef32_match_len]
  exact match_len_loop_spec input a b cap 0#usize hab hcap (by simp) (LZ77.Matches.zero _ _ _)
@[local step]
theorem hash_spec (input : Slice Std.U8) (p : Std.Usize) (hp : p.val + 3 ≤ input.length) :
    slot.p12_ef32_hash input p ⦃ fun h => h.val < 16384 ⦄ := by
  rw [slot.p12_ef32_hash]
  step*
@[local step]
theorem probe_spec (input : Slice Std.U8) (c p : Std.Usize) (hp : p.val < input.length) :
    slot.p12_ef32_probe input c p ⦃ fun l => l.val ≤ 258 ∧ (3 ≤ l.val → c.val < p.val) ∧
      (3 ≤ l.val → p.val - c.val ≤ 32768) ∧ (3 ≤ l.val → p.val + l.val ≤ input.length) ∧
      (3 ≤ l.val → Matches input c.val p.val l.val) ⦄ := by
  rw [slot.p12_ef32_probe]
  split
  · step*
    split <;> step*
  · simp
@[local step]
theorem tok_spec (dist l : Std.Usize) (hd1 : 1 ≤ dist.val) (hd : dist.val ≤ 32768)
    (hl3 : 3 ≤ l.val) (hl : l.val ≤ 258) :
    slot.p12_ef32_tok dist l ⦃ fun v => v.val = LZ77.mkMatch dist.val l.val ⦄ := by
  rw [slot.p12_ef32_tok]
  step*
  simp only [LZ77.mkMatch, LZ77.MATCH_BASE]
  scalar_tac
@[local step]
theorem align3_spec (e : Std.Usize) (he : e.val < 2147483648) :
    slot.p12_ef32_align3 e ⦃ fun r => e.val ≤ r.val ∧ r.val ≤ e.val + 3 ⦄ := by
  rw [slot.p12_ef32_align3]
  step*
  omega
@[local step]
theorem skip_spec (miss : Std.Usize) (hm : miss.val < 2147483648) :
    slot.p12_ef32_skip miss ⦃ fun r => 4 ≤ r.val ∧ r.val ≤ 256 ⦄ := by
  rw [slot.p12_ef32_skip]
  step*
  · have := numBits_ge; simp; omega
  · have : i.val ≤ miss.val := by rw [i_post1]; exact Nat.shiftRight_le _ _
    scalar_tac
  · split
    · step*
    · step*
      scalar_tac
def Inv (input : Slice Std.U8) (L : Nat) (out : Slice Std.U32) (nt ls p miss : Nat) : Prop :=
  Q4.Dec input out nt ls ∧ out.length = L ∧ ls ≤ p ∧ miss ≤ p
theorem run_loop_spec (input : Slice Std.U8) (out : Slice Std.U32) (nt ls : Std.Usize)
    (head : Array Std.U32 16384#usize) (lim p miss fuel : Std.Usize)
    (hlim : lim.val + 8 = input.length) (hsmall : input.length < 2147483648)
    (hinv : Inv input out.length out nt.val ls.val p.val miss.val) :
    slot.p12_ef32_run_loop input out nt ls head lim p miss fuel ⦃ fun r =>
      Q4.Dec input r.1 r.2.1.val r.2.2.val ∧ r.1.length = out.length ⦄ := by
  rw [slot.p12_ef32_run_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun r => r.2.2.2.2.2.2.val)
    (inv := fun r => Inv input out.length r.1 r.2.1.val r.2.2.1.val r.2.2.2.2.1.val
      r.2.2.2.2.2.1.val)
  · rintro ⟨out', nt', ls', head', p', miss', fuel'⟩ ⟨hdec', hlen', hlsp', hmiss'⟩
    simp only at hdec' hlen' hlsp' hmiss'
    simp only [slot.p12_ef32_run_loop.body]
    step*
    · have hl3 : 3 ≤ l.val := by scalar_tac
      have hc := l_post2 hl3
      have hma : Q4.MatchAt input p'.val l.val i2.val :=
        ⟨hl3, l_post1, l_post4 hl3, by omega, by have := l_post3 hl3; omega, by omega,
          by rw [show p'.val - i2.val = c.val by omega]; exact l_post5 hl3⟩
      have hs := Q4.Dec.match_step nt1_post2 hma s_post i3_post nt2_post e_post
      exact ⟨⟨hs.2.2.2, by rw [hs.2.2.1, nt1_post1, hlen'], p1_post1, by simp⟩, by omega⟩
    · exact ⟨⟨hdec', hlen', by omega, by omega⟩, by omega⟩
  · exact hinv
theorem run_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) :
    slot.p12_ef32_run input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧
      LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
  rw [slot.p12_ef32_run]
  have hdec0 : Q4.Dec input out (0#usize).val (0#usize).val := Q4.Dec.init input out hlen
  step*
  · apply Std.WP.spec_bind (run_loop_spec input out 0#usize 0#usize _ lim 3#usize 0#usize
      input.len (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) ⟨hdec0, rfl, by simp, by simp⟩)
    rintro ⟨out1, nt, ls⟩ ⟨hd, hl⟩
    step*
    have hd2 := Q4.Dec.done r_post2 (by simp)
    exact ⟨hd2.1, by rw [r_post1]; exact hl, hd2.2⟩
  all_goals (have hd := Q4.Dec.done r_post2 (by simp); exact ⟨hd.1, r_post1, hd.2⟩)
end EF32
namespace ETINY
open Aeneas Aeneas.Std Result ControlFlow
set_option maxRecDepth 8192
set_option maxHeartbeats 4000000
set_option linter.unusedVariables false
open LZ77 (toks bytes bytes_length Matches decode tokLen MATCH_BASE)
open Q4 (Dec MatchAt word8 u8_lt LensBound)
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
attribute [local step] Q4.lift_spec Q4.e_piece_spec Q4.e_lens_spec Q4.same_spec Q4.be8_spec
  Q4.lz_spec Q4.lz32_spec Q4.put_match_spec sat_add_spec
@[irreducible] def w4 (s : Slice Std.U8) (p : Nat) : Nat :=
  (s.val[p + 3]!).val * 16777216 + (s.val[p + 2]!).val * 65536 + (s.val[p + 1]!).val * 256
    + (s.val[p]!).val
@[irreducible] def wle8 (s : Slice Std.U8) (p : Nat) : Nat :=
  (s.val[p + 7]!).val * 2^56 + (s.val[p + 6]!).val * 2^48 + (s.val[p + 5]!).val * 2^40
    + (s.val[p + 4]!).val * 2^32 + (s.val[p + 3]!).val * 2^24
    + (s.val[p + 2]!).val * 2^16 + (s.val[p + 1]!).val * 2^8 + (s.val[p]!).val
theorem shl_byte32 {x : Nat} (k : Nat) (hx : x < 256) (hk : k ≤ 24) :
    x <<< k % U32.size = x * 2 ^ k := by
  rw [Nat.shiftLeft_eq, U32.size_def]
  apply Nat.mod_eq_of_lt
  have : 2 ^ k ≤ 2 ^ 24 := Nat.pow_le_pow_right (by norm_num) hk
  have : x * 2 ^ k < 256 * 2 ^ 24 := by
    calc x * 2 ^ k < 256 * 2 ^ k := by
          apply Nat.mul_lt_mul_of_pos_right hx (Nat.two_pow_pos _)
      _ ≤ 256 * 2 ^ 24 := Nat.mul_le_mul_left _ this
  simp only [U32.numBits] at *
  omega
theorem le4_nat {a b c d : Nat} (ha : a < 256) (hb : b < 256) (hc : c < 256) (hd : d < 256) :
    (a <<< 24 % U32.size ||| b <<< 16 % U32.size ||| c <<< 8 % U32.size ||| d) =
    a * 16777216 + b * 65536 + c * 256 + d := by
  rw [shl_byte32 24 ha (by norm_num), shl_byte32 16 hb (by norm_num), shl_byte32 8 hc (by norm_num)]
  rw [Q4.or_eq_add_of_mod 24 (x := a * 2^24) (t := b * 2^16) (by omega) (by omega)]
  rw [Q4.or_eq_add_of_mod 16 (x := a * 2^24 + b * 2^16) (t := c * 2^8) (by omega) (by omega)]
  rw [Q4.or_eq_add_of_mod 8 (x := a * 2^24 + b * 2^16 + c * 2^8) (t := d) (by omega) (by omega)]
  norm_num
@[local step]
theorem rd4_spec (s : Slice Std.U8) (i : Std.Usize) (h : i.val + 4 ≤ s.length) :
    slot.p12_et_rd4 s i ⦃ fun v => v.val = w4 s i.val ⦄ := by
  rw [slot.p12_et_rd4]
  step*
  simp only [← getElem!_pos] at *
  simp_all only [UScalar.val_or, U8.cast_U32_val_eq]
  rw [le4_nat (u8_lt _) (u8_lt _) (u8_lt _) (u8_lt _)]
  simp only [w4]
theorem w4_matches (s : Slice Std.U8) (a b : Nat) (h : w4 s a = w4 s b) : Matches s a b 4 := by
  have := u8_lt (s.val[a]!); have := u8_lt (s.val[a + 1]!)
  have := u8_lt (s.val[a + 2]!); have := u8_lt (s.val[a + 3]!)
  have := u8_lt (s.val[b]!); have := u8_lt (s.val[b + 1]!)
  have := u8_lt (s.val[b + 2]!); have := u8_lt (s.val[b + 3]!)
  simp only [w4] at h
  intro k hk
  apply UScalar.eq_of_val_eq
  rcases (show k = 0 ∨ k = 1 ∨ k = 2 ∨ k = 3 by omega) with rfl | rfl | rfl | rfl
  · simp only [Nat.add_zero]; omega
  · omega
  · omega
  · omega
@[local step]
theorem le8_spec (s : Slice Std.U8) (i : Std.Usize) (h : i.val + 8 ≤ s.length) :
    slot.p12_et_le8 s i ⦃ fun v => v.val = wle8 s i.val ⦄ := by
  rw [slot.p12_et_le8]
  step*
  simp only [← getElem!_pos] at *
  simp_all only [UScalar.val_or, U8.cast_U64_val_eq]
  rw [Q4.be8_nat (u8_lt _) (u8_lt _) (u8_lt _) (u8_lt _) (u8_lt _) (u8_lt _) (u8_lt _) (u8_lt _)]
  simp only [wle8]
theorem wle8_digit (s : Slice Std.U8) (p k : Nat) (hk : k < 8) :
    (s.val[p + k]!).val = wle8 s p / 256 ^ k % 256 := by
  have := u8_lt (s.val[p]!); have := u8_lt (s.val[p+1]!)
  have := u8_lt (s.val[p+2]!); have := u8_lt (s.val[p+3]!)
  have := u8_lt (s.val[p+4]!); have := u8_lt (s.val[p+5]!)
  have := u8_lt (s.val[p+6]!); have := u8_lt (s.val[p+7]!)
  simp only [wle8]
  rcases (show k = 0 ∨ k = 1 ∨ k = 2 ∨ k = 3 ∨ k = 4 ∨ k = 5 ∨ k = 6 ∨ k = 7 by omega) with
    rfl | rfl | rfl | rfl | rfl | rfl | rfl | rfl <;> simp only [Nat.add_zero, Nat.pow_zero,
    Nat.pow_succ, Nat.one_mul, Nat.reducePow] <;> omega
theorem wle8_top (s : Slice Std.U8) (a b d : Nat) (hd : d ≤ 8)
    (h : wle8 s a / 2 ^ (64 - 8 * d) = wle8 s b / 2 ^ (64 - 8 * d)) :
    ∀ k, k < d → s.val[b + (8 - d) + k]! = s.val[a + (8 - d) + k]! := by
  intro k hk
  have e : (256 : Nat) ^ (8 - d + k) = 2 ^ (64 - 8 * d) * 256 ^ k := by
    rw [show (256 : Nat) = 2 ^ 8 by norm_num, ← pow_mul, ← pow_mul, ← pow_add]
    congr 1; omega
  have key : wle8 s a / 256 ^ (8 - d + k) = wle8 s b / 256 ^ (8 - d + k) := by
    rw [e, ← Nat.div_div_eq_div_mul, ← Nat.div_div_eq_div_mul, h]
  have ha := wle8_digit s a (8 - d + k) (by omega)
  have hb := wle8_digit s b (8 - d + k) (by omega)
  rw [key] at ha
  apply UScalar.eq_of_val_eq
  rw [show b + (8 - d) + k = b + (8 - d + k) by omega, show a + (8 - d) + k = a + (8 - d + k) by omega]
  omega
theorem Matches.append {s : Slice Std.U8} {a b l1 l2 : Nat} (h1 : Matches s a b l1)
    (h2 : Matches s (a + l1) (b + l1) l2) : Matches s a b (l1 + l2) := by
  intro k hk
  by_cases hk1 : k < l1
  · exact h1 k hk1
  · have := h2 (k - l1) (by omega)
    rw [show b + l1 + (k - l1) = b + k by omega, show a + l1 + (k - l1) = a + k by omega] at this
    exact this
theorem Matches.cast {s : Slice Std.U8} {a b l a' b' l' : Nat} (h : Matches s a b l)
    (ha : a' = a) (hb : b' = b) (hl : l' = l) : Matches s a' b' l' := by
  subst ha hb hl; exact h
theorem Matches.back_lz {s : Slice Std.U8} {a b k : Nat} {pa pb r k1 : Std.Usize}
    {x y z : Std.U64} {lz q : Std.U32}
    (h : Matches s (a - k) (b - k) k)
    (hx : x.val = wle8 s pa.val) (hy : y.val = wle8 s pb.val) (hz : z.val = (x ^^^ y).val)
    (hz0 : ¬z = 0#u64) (hlz : lz = core.num.U64.leading_zeros z) (hq : q.val = lz.val / 8)
    (hr : r = UScalar.cast .Usize q) (hk1 : k1.val = k + r.val)
    (hka : k + 8 ≤ a) (hkb : k + 8 ≤ b)
    (hpa : pa.val = a - k - 8) (hpb : pb.val = b - k - 8) :
    Matches s (a - k1.val) (b - k1.val) k1.val ∧ k1.val < k + 8 := by
  have hbv : z.bv ≠ 0 := by
    intro h0; apply hz0; exact UScalar.eq_of_val_eq (by simp [UScalar.val, h0])
  have hlt : BitVec.leadingZeros z.bv < 64 := Q4.leadingZeros_lt_of_ne z.bv hbv
  have hrv : r.val = BitVec.leadingZeros z.bv / 8 := by
    rw [hr, U32.cast_Usize_val_eq, hq, hlz, Q4.lz_val]
  have hr8 : r.val < 8 := by omega
  refine ⟨?_, by omega⟩
  have htop : wle8 s pa.val / 2 ^ (64 - 8 * r.val) = wle8 s pb.val / 2 ^ (64 - 8 * r.val) := by
    rw [← hx, ← hy, hrv]
    apply Q4.div_eq_of_xor_lt
    rw [← UScalar.val_xor, ← hz]
    exact Q4.lt_pow_leadingZeros z.bv
  have hw := wle8_top s pa.val pb.val r.val (by omega) htop
  have hnew : Matches s (a - k - r.val) (b - k - r.val) r.val := by
    intro j hj
    have := hw j hj
    rw [hpa, hpb, show b - k - 8 + (8 - r.val) + j = b - k - r.val + j by omega,
      show a - k - 8 + (8 - r.val) + j = a - k - r.val + j by omega] at this
    exact this
  have h2 : Matches s (a - k - r.val + r.val) (b - k - r.val + r.val) k :=
    Matches.cast h (by omega) (by omega) rfl
  have := Matches.append hnew h2
  exact Matches.cast this (by omega) (by omega) (by omega)
theorem Matches.back_zero {s : Slice Std.U8} {a b k : Nat} {pa pb k1 : Std.Usize}
    {x y z : Std.U64}
    (h : Matches s (a - k) (b - k) k)
    (hx : x.val = wle8 s pa.val) (hy : y.val = wle8 s pb.val) (hz : z.val = (x ^^^ y).val)
    (hz0 : z = 0#u64) (hk1 : k1.val = k + 8)
    (hka : k + 8 ≤ a) (hkb : k + 8 ≤ b)
    (hpa : pa.val = a - k - 8) (hpb : pb.val = b - k - 8) :
    Matches s (a - k1.val) (b - k1.val) k1.val := by
  have hxy : x.val = y.val := by
    apply Q4.nat_xor_eq_zero
    rw [← UScalar.val_xor, ← hz, hz0]; rfl
  have htop : wle8 s pa.val / 2 ^ (64 - 8 * 8) = wle8 s pb.val / 2 ^ (64 - 8 * 8) := by
    rw [← hx, ← hy, hxy]
  have hw := wle8_top s pa.val pb.val 8 (le_refl 8) htop
  have hnew : Matches s (a - k - 8) (b - k - 8) 8 := by
    intro j hj
    have := hw j hj
    rw [hpa, hpb, show b - k - 8 + (8 - 8) + j = b - k - 8 + j by omega,
      show a - k - 8 + (8 - 8) + j = a - k - 8 + j by omega] at this
    exact this
  have h2 : Matches s (a - k - 8 + 8) (b - k - 8 + 8) k :=
    Matches.cast h (by omega) (by omega) rfl
  have := Matches.append hnew h2
  exact Matches.cast this (by omega) (by omega) (by omega)
theorem Matches.back_byte {s : Slice Std.U8} {a b k : Nat} {i1 i4 k1 : Std.Usize}
    {x y : Std.U8}
    (h : Matches s (a - k) (b - k) k) (hka : k < a) (hkb : k < b)
    (hi1 : i1.val = a - 1 - k) (hi4 : i4.val = b - 1 - k)
    (hi1l : i1.val < s.val.length) (hi4l : i4.val < s.val.length)
    (hx : x = s.val[i1.val]) (hy : y = s.val[i4.val]) (hxy : x = y) (hk1 : k1.val = k + 1) :
    Matches s (a - k1.val) (b - k1.val) k1.val := by
  have heq : s.val[b - 1 - k]! = s.val[a - 1 - k]! := by
    rw [← hi1, ← hi4, getElem!_pos s.val i1.val hi1l, getElem!_pos s.val i4.val hi4l, ← hx, ← hy,
      hxy]
  have hnew : Matches s (a - 1 - k) (b - 1 - k) 1 := by
    intro j hj
    rw [show j = 0 by omega, Nat.add_zero, Nat.add_zero]
    exact heq
  have h2 : Matches s (a - 1 - k + 1) (b - 1 - k + 1) k :=
    Matches.cast h (by omega) (by omega) rfl
  have := Matches.append hnew h2
  exact Matches.cast this (by omega) (by omega) (by omega)
@[local step]
theorem hash_spec (w : Std.U32) : slot.p12_et_hash w ⦃ fun r => r.val < 4096 ⦄ := by
  rw [slot.p12_et_hash]
  step*
@[local step]
theorem dcode_spec (d : Std.Usize) (hd : 1 ≤ d.val) : slot.p12_et_dcode d ⦃ fun _ => True ⦄ := by
  rw [slot.p12_et_dcode]
  step*
@[local step]
theorem minl_spec (lens : Array Std.U16 260#usize) :
    slot.p12_et_minl lens ⦃ fun r => r.val ≤ 258 ⦄ := by
  rw [slot.p12_et_minl, slot.p12_et_minl_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun r => r.2.val)
    (inv := fun r => r.1.val ≤ 258 ∧ r.2.val ≤ 258)
  · rintro ⟨minl, x⟩ ⟨hm, hx⟩
    simp only at hm hx
    simp only [slot.p12_et_minl_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · simp
@[local step]
theorem cover_spec (lens : Array Std.U16 260#usize) (l : Std.Usize) (hl : LensBound lens) :
    slot.p12_et_cover lens l ⦃ fun c => c.val ≤ l.val ⦄ := by
  rw [slot.p12_et_cover, slot.p12_et_cover_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun r => r.1.val + r.2.2.val)
    (inv := fun r => r.1.val + r.2.1.val = l.val ∧ r.2.2.val ≤ 1)
  · rintro ⟨r, c, go⟩ ⟨hrc, hgo⟩
    simp only at hrc hgo
    simp only [slot.p12_et_cover_loop.body]
    step*
    all_goals scalar_tac
  · simp
theorem ne_of_bne {x y : Std.U64} (h : (x != y) = true) : ¬ x = y := by
  intro he; subst he; simp at h
theorem eq_of_not_bne {x y : Std.U64} (h : ¬(x != y) = true) : x = y := by
  by_contra hne; exact h (by simp [hne])
@[local step]
theorem fwd_loop1_spec (s : Slice Std.U8) (a b cap k : Std.Usize)
    (ha : a.val + cap.val ≤ s.length) (hb : b.val + cap.val ≤ s.length)
    (hk : k.val ≤ cap.val) (hm : Matches s a.val b.val k.val) :
    slot.p12_et_fwd_loop0_loop0 s a b cap k ⦃ fun r => r.val ≤ cap.val ∧ Matches s a.val b.val r.val ⦄ := by
  rw [slot.p12_et_fwd_loop0_loop0]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  apply Std.loop.spec_decr_nat
    (measure := fun r => cap.val - r.val)
    (inv := fun r => r.val ≤ cap.val ∧ Matches s a.val b.val r.val)
  · rintro k ⟨hk, hm⟩
    simp only [slot.p12_et_fwd_loop0_loop0.body]
    step*
    all_goals first
      | exact ⟨hk, hm⟩
      | (refine ⟨by scalar_tac, Q4.Matches.byte' hm (by assumption) (by assumption) (by first | assumption | omega | scalar_tac)
          (by first | assumption | omega | scalar_tac) (by assumption) (by assumption) (by assumption) (by assumption),
          by scalar_tac⟩)
  · exact ⟨hk, hm⟩
theorem fwd_loop0_spec (s : Slice Std.U8) (a b cap k : Std.Usize)
    (ha : a.val + cap.val ≤ s.length) (hb : b.val + cap.val ≤ s.length)
    (hcap : cap.val + 8 ≤ Std.Usize.max)
    (hk : k.val ≤ cap.val) (hm : Matches s a.val b.val k.val) :
    slot.p12_et_fwd_loop0 s a b cap k ⦃ fun r => r.val ≤ cap.val ∧ Matches s a.val b.val r.val ⦄ := by
  rw [slot.p12_et_fwd_loop0]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  apply Std.loop.spec_decr_nat
    (measure := fun r => cap.val - r.val)
    (inv := fun r => r.val ≤ cap.val ∧ Matches s a.val b.val r.val)
  · rintro k ⟨hk, hm⟩
    simp only [slot.p12_et_fwd_loop0.body]
    step*
    all_goals first
      | (have hw := Q4.Matches.word_lz hm (by assumption) (by assumption) (by assumption)
          (by assumption) (by assumption) (ne_of_bne (by assumption)) (by assumption)
          (by assumption) (by assumption) (by assumption)
         exact ⟨by scalar_tac, hw.1⟩)
      | (refine ⟨by scalar_tac, Q4.Matches.word_zero hm (by assumption) (by assumption)
          (by assumption) (by assumption) (by assumption) (eq_of_not_bne (by assumption))
          (by first | assumption | omega | scalar_tac), by scalar_tac⟩)
  · exact ⟨hk, hm⟩
@[local step]
theorem fwd_spec (s : Slice Std.U8) (a b cap : Std.Usize)
    (ha : a.val + cap.val ≤ s.length) (hb : b.val + cap.val ≤ s.length)
    (hcap : cap.val + 8 ≤ Std.Usize.max) :
    slot.p12_et_fwd s a b cap ⦃ fun r => r.val ≤ cap.val ∧ Matches s a.val b.val r.val ⦄ :=
  fwd_loop0_spec s a b cap 0#usize ha hb hcap (by simp) (LZ77.Matches.zero s a.val b.val)
theorem back_loop0_spec (s : Slice Std.U8) (a b maxb k : Std.Usize) (run : Std.U32)
    (hma : maxb.val ≤ a.val) (hab : a.val ≤ b.val) (hb : b.val ≤ s.length) (hm258 : maxb.val ≤ 258)
    (hk : k.val ≤ maxb.val) (hm : Matches s (a.val - k.val) (b.val - k.val) k.val) :
    slot.p12_et_back_loop0 s a b maxb k run ⦃ fun r => r.1.val ≤ maxb.val ∧
      Matches s (a.val - r.1.val) (b.val - r.1.val) r.1.val ⦄ := by
  rw [slot.p12_et_back_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun r => maxb.val - r.1.val + r.2.val)
    (inv := fun r => r.1.val ≤ maxb.val ∧ Matches s (a.val - r.1.val) (b.val - r.1.val) r.1.val)
  · rintro ⟨k, run⟩ ⟨hk, hm⟩
    simp only at hk hm
    simp only [slot.p12_et_back_loop0.body]
    step*
    all_goals first
      | exact ⟨hk, hm⟩
      | (refine ⟨by scalar_tac, Matches.back_zero hm i3_post i6_post x_post1 (by assumption)
          i_post (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac), by scalar_tac⟩)
      | (have hw := Matches.back_lz hm i3_post i6_post x_post1 (by assumption) i7_post1 i8_post
          i9_post k1_post (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac)
         refine ⟨by scalar_tac, hw.1, by scalar_tac⟩)
  · exact ⟨hk, hm⟩
theorem back_loop1_spec (s : Slice Std.U8) (a b maxb k : Std.Usize) (run : Std.U32)
    (hma : maxb.val ≤ a.val) (hab : a.val ≤ b.val) (hb : b.val ≤ s.length)
    (hk : k.val ≤ maxb.val) (hm : Matches s (a.val - k.val) (b.val - k.val) k.val) :
    slot.p12_et_back_loop1 s a b maxb k run ⦃ fun r => r.val ≤ maxb.val ∧
      Matches s (a.val - r.val) (b.val - r.val) r.val ⦄ := by
  rw [slot.p12_et_back_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun r => maxb.val - r.1.val + r.2.val)
    (inv := fun r => r.1.val ≤ maxb.val ∧ Matches s (a.val - r.1.val) (b.val - r.1.val) r.1.val)
  · rintro ⟨k, run⟩ ⟨hk, hm⟩
    simp only at hk hm
    simp only [slot.p12_et_back_loop1.body]
    step*
    all_goals first
      | exact ⟨hk, hm⟩
      | (refine ⟨by scalar_tac, Matches.back_byte (i1 := i1) (i4 := i4) hm (by first | assumption | omega | scalar_tac)
          (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac)
          (by assumption) (by assumption) (by assumption) (by first | assumption | omega | scalar_tac), by scalar_tac⟩)
  · exact ⟨hk, hm⟩
@[local step]
theorem back_spec (s : Slice Std.U8) (a b maxb : Std.Usize)
    (hma : maxb.val ≤ a.val) (hab : a.val ≤ b.val) (hb : b.val ≤ s.length) (hm258 : maxb.val ≤ 258) :
    slot.p12_et_back s a b maxb ⦃ fun r => r.val ≤ maxb.val ∧
      Matches s (a.val - r.val) (b.val - r.val) r.val ⦄ := by
  rw [slot.p12_et_back]
  apply Std.WP.spec_bind (back_loop0_spec s a b maxb 0#usize 1#u32 hma hab hb hm258 (by simp)
    (LZ77.Matches.zero s _ _))
  rintro ⟨k, run⟩ ⟨hk, hm⟩
  exact back_loop1_spec s a b maxb k run hma hab hb hk hm
@[local step]
theorem ins_to_spec (s : Slice Std.U8) (head : Array Std.U32 4096#usize) (ins0 stop : Std.Usize)
    (hs : stop.val + 4 ≤ s.length) :
    slot.p12_et_ins_to s head ins0 stop ⦃ fun r => r.1.val = max ins0.val stop.val ⦄ := by
  rw [slot.p12_et_ins_to, slot.p12_et_ins_to_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun r => stop.val - r.2.val)
    (inv := fun r => ins0.val ≤ r.2.val ∧ r.2.val ≤ max ins0.val stop.val)
  · rintro ⟨head, ins⟩ ⟨h0, h1⟩
    simp only at h0 h1
    simp only [slot.p12_et_ins_to_loop.body]
    step*
    all_goals scalar_tac
  · simp
@[local step]
theorem ins_after_spec (s : Slice Std.U8) (head : Array Std.U32 4096#usize) (ins0 ls lim : Std.Usize)
    (hlim : lim.val + 8 = s.length) (hins : ins0.val ≤ lim.val) (hls : ls.val ≤ s.length) :
    slot.p12_et_ins_after s head ins0 ls lim ⦃ fun r => r.1.val ≤ max ins0.val ls.val ⦄ := by
  rw [slot.p12_et_ins_after]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac
def CandOk (s : Slice Std.U8) (ls bs bd bcov bend : Nat) : Prop :=
  ls ≤ bs ∧ 1 ≤ bd ∧ bd ≤ 32768 ∧ bd ≤ bs ∧ bs + bcov ≤ bend ∧ bend ≤ s.length ∧
    Matches s (bs - bd) bs (bend - bs)
theorem CandOk.mk {s : Slice Std.U8} {ls q cp bk f d bs bend cv : Nat}
    (hlsq : ls ≤ q) (hcp : cp < q) (hd : d = q - cp) (hd32 : d ≤ 32768)
    (hm4 : Matches s cp q 4) (hf : Matches s (cp + 4) (q + 4) f) (hqf : q + 4 + f ≤ s.length)
    (hbk : Matches s (cp - bk) (q - bk) bk) (hbkcp : bk ≤ cp) (hbkq : bk ≤ q - ls)
    (hbs : bs = q - bk) (hbend : bend = q + (4 + f)) (hcv : cv ≤ bk + (4 + f)) :
    CandOk s ls bs d cv bend := by
  have h1 : Matches s cp q (4 + f) := Matches.append hm4 hf
  have h2 : Matches s (cp - bk) (q - bk) (bk + (4 + f)) :=
    Matches.append hbk (Matches.cast h1 (by omega) (by omega) rfl)
  refine ⟨by omega, by omega, hd32, by omega, by omega, by omega, ?_⟩
  exact Matches.cast h2 (by omega) hbs (by omega)
@[local step]
theorem maxb_spec (q ls cp : Std.Usize) (hls : ls.val ≤ q.val) :
    slot.p12_et_maxb q ls cp ⦃ fun r => r.val ≤ q.val - ls.val ∧ r.val ≤ cp.val ∧ r.val ≤ 258 ⦄ := by
  rw [slot.p12_et_maxb]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac
@[local step]
theorem take_spec (cv minl : Std.Usize) (used : Std.U32) (d : Std.Usize) (hd : 1 ≤ d.val)
    (hm : minl.val ≤ 258) :
    slot.p12_et_take cv minl used d ⦃ fun r => r = true → minl.val ≤ cv.val ⦄ := by
  rw [slot.p12_et_take]
  step*
  all_goals (intro h; scalar_tac)
@[local step]
theorem cand_spec (s : Slice Std.U8) (head : Array Std.U32 4096#usize) (q ls : Std.Usize)
    (lens : Array Std.U16 260#usize) (minl : Std.Usize) (used : Std.U32)
    (hq : q.val + 8 < s.length) (hq7 : 7 ≤ q.val) (hls : ls.val ≤ q.val) (hl : LensBound lens)
    (hminl : minl.val ≤ 258) :
    slot.p12_et_cand s head q ls lens minl used ⦃ fun r => r.2.2.1.val = 0 ∨
      (minl.val ≤ r.2.2.1.val ∧ r.1.val ≤ q.val ∧
        CandOk s ls.val r.1.val r.2.1.val r.2.2.1.val r.2.2.2.val) ⦄ := by
  rw [slot.p12_et_cand]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  step*
  all_goals first
    | (left; rfl)
    | (right
       have hmc := b_post ‹b = true›
       refine ⟨hmc, by scalar_tac, ?_⟩
       have hw : w4 s i2.val = w4 s q.val := by rw [← i4_post, ← w_post, ‹i4 = w›]
       exact CandOk.mk (q := q.val) (cp := i2.val) (bk := bk.val) (f := i9.val) (by first | assumption | omega | scalar_tac)
         (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (w4_matches s _ _ hw)
         (Matches.cast i9_post2 (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) rfl) (by first | assumption | omega | scalar_tac) bk_post2
         (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac))
def FoldInv (s : Slice Std.U8) (out : Slice Std.U32) (d S0 : Nat) (nt st : Nat) : Prop :=
  Dec s out nt st ∧ st ≤ S0 ∧ d ≤ st ∧ Matches s (st - d) st (S0 - st)
theorem FoldInv.lit {s : Slice Std.U8} {out : Slice Std.U32} {d S0 : Nat}
    {nt st i1 i2 i4 : Std.Usize} {t : Std.U32} {x y : Std.U8}
    (h : FoldInv s out d S0 nt.val st.val)
    (hi1 : i1.val = nt.val - 1) (hntl : nt.val ≤ out.length) (hnt0 : 1 ≤ nt.val)
    (hi1l : i1.val < out.val.length) (ht : t = out.val[i1.val]) (ht256 : t < 256#u32)
    (hi2 : i2.val = st.val - 1) (hi2l : i2.val < s.val.length) (hx : x = s.val[i2.val])
    (hxy : x = y) (hi4 : i4.val = i2.val - d) (hi4l : i4.val < s.val.length)
    (hy : y = s.val[i4.val]) (hdp : d < st.val) :
    FoldInv s out d S0 i1.val i2.val := by
  obtain ⟨hdec, hS0, hdst, hm⟩ := h
  have ht' : (out.val[nt.val - 1]!).val < 256 := by
    rw [← hi1, getElem!_pos out.val i1.val hi1l, ← ht]; scalar_tac
  obtain ⟨hp1, hdec'⟩ := Q4.Dec.pop_lit hdec (by omega) hntl ht'
  have heq : s.val[st.val - 1]! = s.val[st.val - 1 - d]! := by
    rw [← hi2, getElem!_pos s.val i2.val hi2l, show i2.val - d = i4.val by omega,
      getElem!_pos s.val i4.val hi4l, ← hx, ← hy, hxy]
  have h1 : Matches s (st.val - 1 - d) (st.val - 1) 1 := by
    intro j hj
    rw [show j = 0 by omega, Nat.add_zero, Nat.add_zero]
    exact heq
  have h2 : Matches s (st.val - 1 - d + 1) (st.val - 1 + 1) (S0 - st.val) :=
    Matches.cast hm (by omega) (by omega) rfl
  have h3 := Matches.append h1 h2
  rw [hi1, hi2]
  exact ⟨hdec', by omega, by omega, Matches.cast h3 (by omega) rfl (by omega)⟩
theorem FoldInv.match {s : Slice Std.U8} {out : Slice Std.U32} {d S0 : Nat}
    {nt st i1 wl i5 i6 i7 : Std.Usize} {t : Std.U32}
    (h : FoldInv s out d S0 nt.val st.val)
    (hi1 : i1.val = nt.val - 1) (hntl : nt.val ≤ out.length) (hnt0 : 1 ≤ nt.val)
    (hi1l : i1.val < out.val.length) (ht : t = out.val[i1.val])
    (hsame : i7.val = 1 → Matches s i6.val i5.val wl.val) (hi7 : i7 = 1#usize)
    (ht24 : 16777216 ≤ t.val) (hwv : wl.val = (t.val - 16777216) % 256 + 3)
    (hi5 : i5.val = st.val - wl.val) (hwp : wl.val ≤ st.val) (hdw : d ≤ i5.val)
    (hi6 : i6.val = i5.val - d) :
    FoldInv s out d S0 i1.val i5.val := by
  obtain ⟨hdec, hS0, hdst, hm⟩ := h
  have htv : (out.val[nt.val - 1]!).val = t.val := by
    rw [← hi1, getElem!_pos out.val i1.val hi1l, ← ht]
  have hwv' : wl.val = tokLen (out.val[nt.val - 1]!).val := by
    rw [htv, hwv]
    simp only [tokLen, MATCH_BASE]
  obtain ⟨hwl, hdec'⟩ := Q4.Dec.pop_match hdec (by omega) hntl (by omega)
  rw [← hwv'] at hdec'
  have hmw : Matches s (st.val - wl.val - d) (st.val - wl.val) wl.val := by
    have := hsame (by rw [hi7]; rfl)
    rw [hi6, hi5] at this
    exact this
  have h2 : Matches s (st.val - wl.val - d + wl.val) (st.val - wl.val + wl.val) (S0 - st.val) :=
    Matches.cast hm (by omega) (by omega) rfl
  have h3 := Matches.append hmw h2
  rw [hi1, hi5]
  exact ⟨hdec', by omega, by omega, Matches.cast h3 rfl rfl (by omega)⟩
theorem fold_loop_spec (s : Slice Std.U8) (out : Slice Std.U32) (d nt st back_n : Std.Usize)
    (S0 : Nat) (hS8 : S0 + 8 ≤ s.length) (hinv : FoldInv s out d.val S0 nt.val st.val) :
    slot.p12_et_fold_loop s out d nt st back_n ⦃ fun r => FoldInv s out d.val S0 r.1.val r.2.val ⦄ := by
  rw [slot.p12_et_fold_loop]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  apply Std.loop.spec_decr_nat
    (measure := fun r => 16 - r.2.2.val)
    (inv := fun r => FoldInv s out d.val S0 r.1.val r.2.1.val)
  · rintro ⟨nt, st, back_n⟩ hinv
    simp only at hinv
    have hinv' := hinv
    obtain ⟨⟨hps, hntp, hso, _⟩, hS0, hdst, _⟩ := hinv'
    simp only [slot.p12_et_fold_loop.body]
    step*
    all_goals first
      | (refine ⟨hinv, by scalar_tac⟩)
      | exact hinv
      | (refine ⟨FoldInv.lit hinv i1_post1 (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) t_post
          (by assumption) i2_post1 (by first | assumption | omega | scalar_tac) i3_post ‹i3 = i5› i4_post1 (by first | assumption | omega | scalar_tac)
          i5_post (by first | assumption | omega | scalar_tac), by scalar_tac⟩)
      | (refine ⟨FoldInv.match hinv i1_post1 (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) t_post
          i7_post ‹i7 = 1#usize› (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) i5_post1 (by first | assumption | omega | scalar_tac)
          (by first | assumption | omega | scalar_tac) i6_post1, by scalar_tac⟩)
  · exact hinv
@[local step]
theorem fold_spec (s : Slice Std.U8) (out : Slice Std.U32) (nt0 st0 d : Std.Usize)
    (hS8 : st0.val + 8 ≤ s.length) (hdec : Dec s out nt0.val st0.val) (hd : d.val ≤ st0.val) :
    slot.p12_et_fold s out nt0 st0 d ⦃ fun r => Dec s out r.1.val r.2.val ∧ r.2.val ≤ st0.val ∧
      d.val ≤ r.2.val ∧ Matches s (r.2.val - d.val) r.2.val (st0.val - r.2.val) ⦄ := by
  rw [slot.p12_et_fold]
  apply Std.WP.spec_mono (fold_loop_spec s out d nt0 st0 0#usize st0.val hS8
    ⟨hdec, le_refl _, hd, by simpa using LZ77.Matches.zero s (st0.val - d.val) st0.val⟩)
  rintro ⟨nt, st⟩ h
  exact h
@[local step]
theorem v25z (s : Slice Std.U8) (out : Slice Std.U32) («end» d : Std.Usize)
    (lens : Array Std.U16 260#usize) (nt x : Std.Usize) (go : Std.U32)
    (hl : LensBound lens) (hdec : Dec s out nt.val x.val) (hxe : x.val ≤ «end».val)
    (hen : «end».val ≤ s.length) (hd1 : 1 ≤ d.val) (hd32 : d.val ≤ 32768)
    (hdx : d.val ≤ x.val) (hm : Matches s (x.val - d.val) x.val («end».val - x.val)) :
    slot.p12_et_pieces_loop s out «end» d lens nt x go ⦃ fun r =>
      Dec s r.1 r.2.1.val r.2.2.val ∧ r.1.length = out.length ∧ r.2.2.val ≤ «end».val ⦄ := by
  rw [slot.p12_et_pieces_loop]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  apply Std.loop.spec_decr_nat
    (measure := fun r => «end».val - r.2.2.1.val + r.2.2.2.val)
    (inv := fun r => Dec s r.1 r.2.1.val r.2.2.1.val ∧ r.1.length = out.length ∧
      r.2.2.1.val ≤ «end».val ∧ d.val ≤ r.2.2.1.val ∧
      Matches s (r.2.2.1.val - d.val) r.2.2.1.val («end».val - r.2.2.1.val))
  · rintro ⟨out', nt', x', go'⟩ ⟨hdec', hlen', hxe', hdx', hm'⟩
    simp only at hdec' hlen' hxe' hdx' hm'
    simp only [slot.p12_et_pieces_loop.body]
    step*
    all_goals first
      | exact ⟨hdec', hlen', hxe'⟩
      | (refine ⟨hdec', hlen', hxe', hdx', hm', by scalar_tac⟩)
      | exact Q4.MatchAt.piece hm' hd1 hd32 hdx' hen (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac)
      | (refine ⟨by assumption, by scalar_tac, by scalar_tac, by scalar_tac,
          Q4.Matches.after_piece hm' (by assumption) hdx' (by first | assumption | omega | scalar_tac), by scalar_tac⟩)
  · exact ⟨hdec, rfl, hxe, hdx, hm⟩
@[local step]
theorem pieces_spec (s : Slice Std.U8) (out : Slice Std.U32) (nt0 x0 «end» d : Std.Usize)
    (lens : Array Std.U16 260#usize)
    (hl : LensBound lens) (hdec : Dec s out nt0.val x0.val) (hxe : x0.val ≤ «end».val)
    (hen : «end».val ≤ s.length) (hd1 : 1 ≤ d.val) (hd32 : d.val ≤ 32768)
    (hdx : d.val ≤ x0.val) (hm : Matches s (x0.val - d.val) x0.val («end».val - x0.val)) :
    slot.p12_et_pieces s out nt0 x0 «end» d lens ⦃ fun r =>
      Dec s r.2 r.1.1.val r.1.2.val ∧ r.2.length = out.length ⦄ := by
  rw [slot.p12_et_pieces]
  step*
theorem v4z {s : Slice Std.U8} {st bs0 bd bend e : Nat}
    (hf : Matches s (st - bd) st (bs0 - st)) (hc : Matches s (bs0 - bd) bs0 (bend - bs0))
    (hst : st ≤ bs0) (hbd : bd ≤ st) (hb : bs0 ≤ bend) (he : st ≤ e) (heb : e ≤ bend) :
    Matches s (st - bd) st (e - st) := by
  have h2 : Matches s (st - bd + (bs0 - st)) (st + (bs0 - st)) (bend - bs0) :=
    Matches.cast hc (by omega) (by omega) rfl
  have := Matches.append hf h2
  exact LZ77.Matches.mono this (by omega)
section EmitSec
attribute [local step] Q4.flush_spec
@[local step]
theorem emit_spec (s : Slice Std.U8) (out : Slice Std.U32) (nt0 ls bs0 bd bcov bend : Std.Usize)
    (lens : Array Std.U16 260#usize) (hl : LensBound lens) (hdec : Dec s out nt0.val ls.val)
    (hc : CandOk s ls.val bs0.val bd.val bcov.val bend.val) (hbs8 : bs0.val + 8 ≤ s.length) :
    slot.p12_et_emit s out nt0 ls bs0 bd bcov bend lens ⦃ fun r =>
      Dec s r.2 r.1.1.val r.1.2.val ∧ r.2.length = out.length ∧ r.1.2.val ≤ s.length ⦄ := by
  rw [slot.p12_et_emit]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  obtain ⟨hlsb, hd1, hd32, hdb, hbc, hbe, hm⟩ := hc
  step*
  split
  all_goals step*
  all_goals first
    | exact v4z i_post4 hm (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac)
        (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac)
    | exact LZ77.Matches.mono hm (by first | assumption | omega | scalar_tac)
    | exact Q4.Dec.cast i_post1 (by first | assumption | omega | scalar_tac)
    | scalar_tac
    | (refine ⟨by assumption, by scalar_tac, (by assumption : Dec _ _ _ _).1⟩)
end EmitSec
attribute [local step] emit_spec
def MInv (s : Slice Std.U8) (L : Nat) (out : Slice Std.U32) (nt ls ins q : Nat) : Prop :=
  Dec s out nt ls ∧ out.length = L ∧ ls ≤ q ∧ ins ≤ q ∧ 7 ≤ q
theorem cand_some {x m b q : Nat} {P : Prop} (h : x = 0 ∨ (m ≤ x ∧ b ≤ q ∧ P)) (hx : m ≤ x)
    (hm : 3 ≤ m) : b ≤ q ∧ P := by
  rcases h with h | h
  · omega
  · exact h.2
theorem main_loop_spec (s : Slice Std.U8) (out : Slice Std.U32) (lens : Array Std.U16 260#usize)
    (minl nt ls : Std.Usize) (head : Array Std.U32 4096#usize) (lim ins q fuel : Std.Usize)
    (used : Std.U32) (L : Nat)
    (hlim : lim.val + 8 = s.length) (hl : LensBound lens) (hm3 : 3 ≤ minl.val)
    (hm258 : minl.val ≤ 258) (hinv : MInv s L out nt.val ls.val ins.val q.val) :
    slot.p12_et_tiny_loop s out lens minl nt ls head lim ins q fuel used ⦃ fun r =>
      Dec s r.1 r.2.1.val r.2.2.val ∧ r.1.length = L ⦄ := by
  rw [slot.p12_et_tiny_loop]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  apply Std.loop.spec_decr_nat
    (measure := fun r => r.2.2.2.2.2.2.1.val)
    (inv := fun r => MInv s L r.1 r.2.1.val r.2.2.1.val r.2.2.2.2.1.val r.2.2.2.2.2.1.val)
  · rintro ⟨out, nt, ls, head, ins, q, fuel, used⟩ hinv
    simp only at hinv
    have hinv' := hinv
    obtain ⟨hdec, hL, hlsq, hinsq, hq7⟩ := hinv'
    simp only [slot.p12_et_tiny_loop.body]
    step*
    all_goals first
      | (refine ⟨⟨hdec, hL, by scalar_tac, by scalar_tac, by scalar_tac⟩, by scalar_tac⟩)
      | exact ⟨hdec, hL⟩
      | (obtain ⟨hiq, hc⟩ := cand_some i_post (by first | assumption | omega | scalar_tac) hm3
         have hc' := hc
         obtain ⟨hc1, hc2, hc3, hc4, hc5, hc6, _⟩ := hc'
         step*
         all_goals first
           | scalar_tac
           | (refine ⟨⟨by assumption, by scalar_tac, ?_, ?_, ?_⟩, by scalar_tac⟩ <;>
               rcases nq_post with h | h <;> scalar_tac))
  · exact hinv
theorem main_loop_spec' (s : Slice Std.U8) (out : Slice Std.U32) (lens : Array Std.U16 260#usize)
    (minl nt ls : Std.Usize) (head : Array Std.U32 4096#usize) (lim ins q fuel : Std.Usize)
    (used : Std.U32)
    (hlim : lim.val + 8 = s.length) (hl : LensBound lens) (hm3 : 3 ≤ minl.val)
    (hm258 : minl.val ≤ 258) (hdec : Dec s out nt.val ls.val) (hlsq : ls.val ≤ q.val)
    (hinsq : ins.val ≤ q.val) (hq7 : 7 ≤ q.val) :
    slot.p12_et_tiny_loop s out lens minl nt ls head lim ins q fuel used ⦃ fun r =>
      Dec s r.1 r.2.1.val r.2.2.val ∧ r.1.length = out.length ⦄ :=
  main_loop_spec s out lens minl nt ls head lim ins q fuel used out.length hlim hl hm3 hm258
    ⟨hdec, rfl, hlsq, hinsq, hq7⟩
theorem flush_done_spec (s : Slice Std.U8) (out : Slice Std.U32) (nt a e : Std.Usize)
    (hdec : Dec s out nt.val a.val) (he : e.val = s.length) (ha : a.val ≤ e.val) :
    slot.q4_flush s out nt a e ⦃ fun r => r.1.val ≤ s.length ∧ r.2.length = out.length ∧
      LZ77.Valid (bytes s) (toks r.2 r.1.val) ⦄ := by
  apply Std.WP.spec_mono (Q4.flush_spec s out nt a e hdec (by omega) ha)
  rintro ⟨nt1, out1⟩ ⟨hd, hl⟩
  have := Q4.Dec.done hd (by omega)
  exact ⟨this.1, hl, this.2⟩
section TinySec
attribute [local step] flush_done_spec main_loop_spec'
theorem tiny_spec (s : Slice Std.U8) (out : Slice Std.U32) (lm : Std.U32)
    (hlen : s.length ≤ out.length) :
    slot.p12_et_tiny s out lm ⦃ fun r => r.1.val ≤ s.length ∧ r.2.length = out.length ∧
      LZ77.Valid (bytes s) (toks r.2 r.1.val) ⦄ := by
  rw [slot.p12_et_tiny]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  have hL0 : LensBound (Std.Array.repeat 260#usize 0#u16) := Q4.LensBound.init
  have hdec0 : Dec s out (0#usize).val (0#usize).val := Q4.Dec.init s out hlen
  step*
end TinySec
end ETINY
namespace ESPARSE
open Aeneas Aeneas.Std Result ControlFlow
set_option maxRecDepth 8192
set_option maxHeartbeats 4000000
set_option linter.unusedVariables false
open LZ77 (toks bytes Matches)
open Q4 (Dec LensBound word8)
attribute [local step] Q4.be8_spec Q4.lz_spec Q4.put_lit_spec Q4.e_pieces_spec Q4.e_lens_spec
def Run (s : Slice Std.U8) (b : Nat) (v : Std.U8) (k : Nat) : Prop :=
  ∀ j, j < k → s.val[b + j]! = v
theorem divmod_aux (v n Q m : Nat) (hv : v < 256) (hlo : v * Q * n ≤ m)
    (hhi : m < (v * Q + 1) * n) (hQ : Q % 256 = 1) : m / n % 256 = v := by
  rw [Nat.div_eq_of_lt_le hlo hhi, Nat.mul_mod, hQ, Nat.mul_one, Nat.mod_mod, Nat.mod_eq_of_lt hv]
theorem bcast_digit (v : Nat) (hv : v < 256) (j : Nat) (hj : j < 8) :
    v * 72340172838076673 / 256 ^ (7 - j) % 256 = v := by
  rcases (show j = 0 ∨ j = 1 ∨ j = 2 ∨ j = 3 ∨ j = 4 ∨ j = 5 ∨ j = 6 ∨ j = 7 by omega) with
    rfl | rfl | rfl | rfl | rfl | rfl | rfl | rfl <;> simp only [Nat.reduceSub, Nat.reducePow]
  · exact divmod_aux v _ 1 _ hv (by omega) (by omega) (by norm_num)
  · exact divmod_aux v _ 257 _ hv (by omega) (by omega) (by norm_num)
  · exact divmod_aux v _ 65793 _ hv (by omega) (by omega) (by norm_num)
  · exact divmod_aux v _ 16843009 _ hv (by omega) (by omega) (by norm_num)
  · exact divmod_aux v _ 4311810305 _ hv (by omega) (by omega) (by norm_num)
  · exact divmod_aux v _ 1103823438081 _ hv (by omega) (by omega) (by norm_num)
  · exact divmod_aux v _ 282578800148737 _ hv (by omega) (by omega) (by norm_num)
  · exact divmod_aux v _ 72340172838076673 _ hv (by omega) (by omega) (by norm_num)
theorem word8_bcast (s : Slice Std.U8) (i v d : Nat) (hv : v < 256) (hd : d ≤ 8)
    (h : word8 s i / 2 ^ (64 - 8 * d) = v * 72340172838076673 / 2 ^ (64 - 8 * d)) :
    ∀ j, j < d → (s.val[i + j]!).val = v := by
  intro j hj
  have e : (256 : Nat) ^ (7 - j) = 2 ^ (64 - 8 * d) * 2 ^ (8 * (d - 1 - j)) := by
    rw [← pow_add, show (256 : Nat) = 2 ^ 8 by norm_num, ← pow_mul]
    congr 1; omega
  have key : word8 s i / 256 ^ (7 - j) = v * 72340172838076673 / 256 ^ (7 - j) := by
    rw [e, ← Nat.div_div_eq_div_mul, ← Nat.div_div_eq_div_mul, h]
  rw [Q4.word8_digit s i j (by omega), key]
  exact bcast_digit v hv j (by omega)
theorem Run.add_word {s : Slice Std.U8} {b k d : Nat} {v : Std.U8} (h : Run s b v k) (hd : d ≤ 8)
    (hw : word8 s (b + k) / 2 ^ (64 - 8 * d) = v.val * 72340172838076673 / 2 ^ (64 - 8 * d)) :
    Run s b v (k + d) := by
  intro j hj
  by_cases hjk : j < k
  · exact h j hjk
  · have := word8_bcast s (b + k) v.val d (Q4.u8_lt v) hd hw (j - k) (by omega)
    rw [show b + k + (j - k) = b + j by omega] at this
    exact UScalar.eq_of_val_eq this
theorem Run.lz_step {s : Slice Std.U8} {b k : Nat} {v : Std.U8} {pa k1 r : Std.Usize}
    {y w x : Std.U64} {lz q : Std.U32}
    (h : Run s b v k) (hpa : pa.val = b + k) (hy : y.val = word8 s pa.val)
    (hw : w.val = v.val * 72340172838076673) (hx : x.val = (y ^^^ w).val)
    (hlz : lz = core.num.U64.leading_zeros x) (hq : q.val = lz.val / 8)
    (hr : r = UScalar.cast .Usize q) (hk1 : k1.val = k + r.val) :
    Run s b v k1.val ∧ k1.val ≤ k + 8 := by
  have hle : BitVec.leadingZeros x.bv ≤ 64 := by unfold BitVec.leadingZeros; split <;> omega
  have hrv : r.val = BitVec.leadingZeros x.bv / 8 := by
    rw [hr, U32.cast_Usize_val_eq, hq, hlz, Q4.lz_val]
  refine ⟨?_, by omega⟩
  rw [hk1, hrv]
  apply Run.add_word h (by omega)
  rw [← hpa, ← hy, ← hw]
  apply Q4.div_eq_of_xor_lt
  have hxv : x.val = y.val ^^^ w.val := by rw [hx, UScalar.val_xor]
  rw [← hxv]
  exact Q4.lt_pow_leadingZeros x.bv
theorem Run.zero_step {s : Slice Std.U8} {b k : Nat} {v : Std.U8} {pa k1 : Std.Usize}
    {y w x : Std.U64}
    (h : Run s b v k) (hpa : pa.val = b + k) (hy : y.val = word8 s pa.val)
    (hw : w.val = v.val * 72340172838076673) (hx : x.val = (y ^^^ w).val) (hx0 : x = 0#u64)
    (hk1 : k1.val = k + 8) : Run s b v k1.val := by
  rw [hk1]
  apply Run.add_word h (le_refl 8)
  have h0 : y.val ^^^ w.val = 0 := by rw [← UScalar.val_xor, ← hx, hx0]; rfl
  have hyw := Q4.nat_xor_eq_zero h0
  rw [← hpa, ← hy, ← hw, hyw]
theorem Run.byte {s : Slice Std.U8} {b k : Nat} {v x : Std.U8} {i k1 : Std.Usize}
    (h : Run s b v k) (hi : i.val = b + k) (hil : i.val < s.val.length) (hx : x = s.val[i.val])
    (hxv : x = v) (hk1 : k1.val = k + 1) : Run s b v k1.val := by
  intro j hj
  by_cases hjk : j < k
  · exact h j hjk
  · have hjk' : j = k := by omega
    subst hjk'
    rw [← hi, getElem!_pos s.val i.val hil, ← hx, hxv]
theorem w_val {v : Std.U8} {i w : Std.U64} (hi : i = UScalar.cast .U64 v)
    (hw : w = core.num.U64.wrapping_mul i 72340172838076673#u64) :
    w.val = v.val * 72340172838076673 := by
  have hv : v.val < 256 := Q4.u8_lt v
  rw [hw, core.num.U64.wrapping_mul_val_eq, hi, U8.cast_U64_val_eq]
  simp only [UScalar.size, UScalarTy.U64_numBits_eq]
  have h1 : (72340172838076673#u64).val = 72340172838076673 := by rfl
  rw [h1]
  apply Nat.mod_eq_of_lt
  omega
theorem run_loop0_spec (s : Slice Std.U8) (b cap : Std.Usize) (v : Std.U8) (w : Std.U64)
    (k : Std.Usize) (go : Std.U32) (K : Nat)
    (hb : b.val + cap.val ≤ s.length) (hw : w.val = v.val * 72340172838076673)
    (hk : k.val ≤ cap.val) (hK : K ≤ k.val) (hm : Run s b.val v k.val) :
    slot.p12_esparse_run_loop0 s b cap w k go ⦃ fun r =>
      K ≤ r.1.val ∧ r.1.val ≤ cap.val ∧ Run s b.val v r.1.val ⦄ := by
  rw [slot.p12_esparse_run_loop0]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  apply Std.loop.spec_decr_nat
    (measure := fun r => cap.val - r.1.val + r.2.val)
    (inv := fun r => K ≤ r.1.val ∧ r.1.val ≤ cap.val ∧ Run s b.val v r.1.val)
  · rintro ⟨k, go⟩ ⟨hK, hk, hm⟩
    simp only at hK hk hm
    simp only [slot.p12_esparse_run_loop0.body]
    step*
    all_goals first
      | scalar_tac
      | exact ⟨hK, hk, hm⟩
      | (refine ⟨by scalar_tac, by scalar_tac, Run.zero_step hm (by assumption) (by assumption)
          hw (by assumption) (by assumption) (by first | assumption | omega | scalar_tac), by scalar_tac⟩)
      | (obtain ⟨hw1, hw2⟩ := Run.lz_step hm (by assumption) (by assumption) hw (by assumption)
          (by assumption) (by assumption) (by assumption) (by assumption)
         refine ⟨by scalar_tac, by scalar_tac, hw1, by scalar_tac⟩)
  · exact ⟨hK, hk, hm⟩
theorem run_loop1_spec (s : Slice Std.U8) (b : Std.Usize) (v : Std.U8) (cap k : Std.Usize)
    (go : Std.U32) (K : Nat)
    (hb : b.val + cap.val ≤ s.length)
    (hk : k.val ≤ cap.val) (hK : K ≤ k.val) (hm : Run s b.val v k.val) :
    slot.p12_esparse_run_loop1 s b v cap k go ⦃ fun r =>
      K ≤ r.val ∧ r.val ≤ cap.val ∧ Run s b.val v r.val ⦄ := by
  rw [slot.p12_esparse_run_loop1]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  apply Std.loop.spec_decr_nat
    (measure := fun r => cap.val - r.1.val + r.2.val)
    (inv := fun r => K ≤ r.1.val ∧ r.1.val ≤ cap.val ∧ Run s b.val v r.1.val)
  · rintro ⟨k, go⟩ ⟨hK, hk, hm⟩
    simp only at hK hk hm
    simp only [slot.p12_esparse_run_loop1.body]
    step*
    all_goals first
      | scalar_tac
      | exact ⟨hK, hk, hm⟩
      | (refine ⟨by scalar_tac, by scalar_tac, Run.byte hm (by assumption) (by first | assumption | omega | scalar_tac)
          (by assumption) (by assumption) (by first | assumption | omega | scalar_tac), by scalar_tac⟩)
  · exact ⟨hK, hk, hm⟩
@[local step]
theorem run_spec (s : Slice Std.U8) (b : Std.Usize) (v : Std.U8) (cap k0 : Std.Usize)
    (hb : b.val + cap.val ≤ s.length) (hk0 : k0.val ≤ cap.val) (hm : Run s b.val v k0.val) :
    slot.p12_esparse_run s b v cap k0 ⦃ fun r =>
      k0.val ≤ r.val ∧ r.val ≤ cap.val ∧ Run s b.val v r.val ⦄ := by
  rw [slot.p12_esparse_run]
  step*
  apply Std.WP.spec_bind (run_loop0_spec s b cap v w k0 1#u32 k0.val hb
    (w_val (by assumption) (by assumption)) hk0 (le_refl _) hm)
  rintro ⟨k, go⟩ ⟨hK, hk, hm'⟩
  exact run_loop1_spec s b v cap k go k0.val hb hk hK hm'
theorem run1 {s : Slice Std.U8} {p : Std.Usize} {x v : Std.U8}
    (hp : p.val < s.val.length) (hx : x = s.val[p.val]) (hxv : x = v) :
    Run s p.val v (1#usize).val := by
  intro j hj
  have hj0 : j = 0 := by simp at hj; omega
  subst hj0
  rw [Nat.add_zero, getElem!_pos s.val p.val hp, ← hx, hxv]
theorem Run.matches {s : Slice Std.U8} {p i : Std.Usize} {v : Std.U8} {r : Nat} {A : Nat}
    (h : Run s p.val v r) (hi : i.val = p.val - 1) (hil : i.val < s.val.length)
    (hv : v = s.val[i.val]) (hA : A = p.val - 1) (hp1 : 1 ≤ p.val) :
    Matches s A p.val r := by
  intro k hk
  rw [h k hk]
  rcases Nat.eq_zero_or_pos k with h0 | h0
  · subst h0
    rw [Nat.add_zero, hA, ← hi, getElem!_pos s.val i.val hil, hv]
  · have := h (k - 1) (by omega)
    rw [show A + k = p.val + (k - 1) by omega, this]
theorem dec_eq {s : Slice Std.U8} {out : Slice Std.U32} {nt p q : Nat}
    (h : Dec s out nt p) (hq : q = p) : Dec s out nt q := by
  rw [hq]; exact h
@[local step]
theorem rle_loop_spec (s : Slice Std.U8) (out : Slice Std.U32) (n nt : Std.Usize)
    (lens : Array Std.U16 260#usize) (p : Std.Usize) (hn : n.val = s.length)
    (hl : LensBound lens) (hdec : Dec s out nt.val p.val) (hp1 : 1 ≤ p.val) :
    slot.p12_esparse_rle_loop s out n nt lens p ⦃ fun r => r.1.val ≤ s.length ∧
      r.2.length = out.length ∧ LZ77.Valid (bytes s) (toks r.2 r.1.val) ⦄ := by
  rw [slot.p12_esparse_rle_loop]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  apply Std.loop.spec_decr_nat
    (measure := fun r => n.val - r.2.2.val)
    (inv := fun r => Dec s r.1 r.2.1.val r.2.2.val ∧ r.1.length = out.length ∧ 1 ≤ r.2.2.val)
  · rintro ⟨out', nt', p'⟩ ⟨hdec', hlen', hp'⟩
    simp only at hdec' hlen' hp'
    simp only [slot.p12_esparse_rle_loop.body]
    step*
    all_goals first
      | (have hd := Q4.Dec.done hdec' (by first | assumption | omega | scalar_tac)
         exact ⟨hd.1, hlen', hd.2⟩)
      | exact run1 (by first | assumption | omega | scalar_tac) (by assumption) (by assumption)
      | exact Run.matches (by assumption) (by assumption) (by first | assumption | omega | scalar_tac) (by assumption)
          (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac)
      | scalar_tac
      | (refine ⟨dec_eq (by assumption) (by first | assumption | omega | scalar_tac), by scalar_tac, by scalar_tac,
          by scalar_tac⟩)
  · exact ⟨hdec, rfl, hp1⟩
theorem rle_spec (s : Slice Std.U8) (out : Slice Std.U32) (lm : Std.U32)
    (hlen : s.length ≤ out.length) :
    slot.p12_esparse_rle s out lm ⦃ fun r => r.1.val ≤ s.length ∧
      r.2.length = out.length ∧ LZ77.Valid (bytes s) (toks r.2 r.1.val) ⦄ := by
  rw [slot.p12_esparse_rle]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  have hL0 : LensBound (Std.Array.repeat 260#usize 0#u16) := Q4.LensBound.init
  have hdec0 : Dec s out (0#usize).val (0#usize).val := Q4.Dec.init s out hlen
  step*
  all_goals exact Q4.Dec.done hdec0 (by first | assumption | omega | scalar_tac)
end ESPARSE
@[local step]
theorem p125_row10_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.p12_p125_row10 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.p12_p125_row10]
 exact ESPARSE.rle_spec input out _ hlen
@[local step]
theorem p125_row12_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.p12_p125_row12 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.p12_p125_row12]
 exact ETINY.tiny_spec input out _ hlen
@[local step]
theorem p125_row15_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.p12_p125_row15 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.p12_p125_row15]
 exact EF32.run_spec input out hlen
end P12
set_option linter.unusedSimpArgs false
set_option linter.unusedVariables false
set_option linter.unusedTactic false
set_option linter.unreachableTactic false
namespace PR
open Aeneas Aeneas.Std Result ControlFlow
open LZ77 (toks bytes)
set_option maxRecDepth 8192
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
theorem CntBound.init : CntBound (Std.Array.repeat 256#usize 0#u32) 0 := (by
  intro j hj
  rw [Std.Array.repeat_val, List.getElem!_eq_getElem?_getD,
    List.getElem?_replicate_of_lt (by simpa using hj)]
  rfl)
theorem CntBound.get {cnt : Array Std.U32 256#usize} {T : Nat} (h : CntBound cnt T)
    (a : Std.Usize) (x : Std.U32) (ha : a.val < cnt.val.length) (hx : x = cnt.val[a.val]) :
    x.val ≤ T := (by
  have := h a.val (by simpa using ha)
  rw [getElem!_pos cnt.val a.val ha, ← hx] at this
  exact this)
@[local step]
theorem cnt_index_spec (cnt : Array Std.U32 256#usize) (T : Nat) (h : CntBound cnt T)
    (i : Std.Usize) (hi : i.val < 256) :
    Std.Array.index_usize cnt i ⦃ fun x => x = cnt.val[i.val]! ∧ x.val ≤ T ⦄ := (by
  have hl : i.val < cnt.val.length := by simp; omega
  have := Std.Array.index_usize_spec cnt i (by simpa using hl)
  apply Std.WP.spec_mono this
  intro x hx
  refine ⟨by rw [getElem!_pos cnt.val i.val hl]; exact hx, CntBound.get h i x hl hx⟩)
theorem CntBound.update {cnt : Array Std.U32 256#usize} {T : Nat} (h : CntBound cnt T)
    (a : Std.Usize) (v : Std.U32) (hv : v.val ≤ T + 1) : CntBound (cnt.set a v) (T + 1) := (by
  intro j hj
  rw [Std.Array.set_val_eq]
  by_cases hja : a.val = j
  · subst hja
    have hlen : a.val < cnt.val.length := by simp; omega
    rw [List.getElem!_eq_getElem?_getD, List.getElem?_set_self hlen]
    exact hv
  · rw [List.getElem!_eq_getElem?_getD, List.getElem?_set_ne hja, ← List.getElem!_eq_getElem?_getD]
    exact le_trans (h j hj) (by omega))
theorem CntBound.step {cnt a : Array Std.U32 256#usize} {T : Nat} {x : Std.Usize}
    {v tot1 : Std.U32} (hc : CntBound cnt T) (ha : a = cnt.set x v) (hv : v.val ≤ T + 1)
    (ht1 : tot1.val = T + 1) : CntBound a tot1.val := (by
  rw [ha, ht1]
  exact CntBound.update hc x v hv)
theorem CntBound.mono {cnt : Array Std.U32 256#usize} {T T' : Nat} (h : CntBound cnt T)
    (hT : T ≤ T') : CntBound cnt T' := fun j hj => le_trans (h j hj) hT
@[local step]
theorem lift_spec {α : Type} (x : α) : lift x ⦃ fun y => y = x ⦄ := by
  simp [lift]
theorem v9z (s : Slice Std.U8) (n : Std.Usize) (cnt : Array Std.U32 256#usize)
    (step i : Std.Usize) (tot : Std.U32) (hn : n.val = s.length) (hc : CntBound cnt tot.val)
    (ht : tot.val ≤ 4097) :
    slot.pr_format_id_loop s n cnt step i tot ⦃ fun r => CntBound r.1 r.2.val ∧ r.2.val ≤ 4097 ⦄ := by
  rw [slot.pr_format_id_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun r => 4097 - r.2.2.val)
    (inv := fun r => CntBound r.1 r.2.2.val ∧ r.2.2.val ≤ 4097)
  · rintro ⟨cnt, i, tot⟩ ⟨hc, ht⟩
    simp only at hc ht
    simp only [slot.pr_format_id_loop.body]
    step*
    all_goals first
      | exact ⟨hc, ht⟩
      | exact ⟨CntBound.step hc (by assumption) (by first | assumption | omega | scalar_tac) (by first | assumption | omega | scalar_tac), by scalar_tac,
          by scalar_tac⟩
  · exact ⟨hc, ht⟩
@[local step]
theorem format_id_spec (s : Slice Std.U8) : slot.pr_format_id s ⦃ fun _ => True ⦄ := by
  rw [slot.pr_format_id]
  step*
  apply Std.WP.spec_bind (v9z s (Std.Slice.len s) _ step 0#usize 0#u32 (by simp)
    (by simpa using CntBound.init) (by simp))
  rintro ⟨cnt1, tot⟩ ⟨hc, ht⟩
  simp only at hc ht
  have hc4 := CntBound.mono hc ht
  clear hc
  step*
  repeat' (split <;> step*)
end E_M
attribute [local step] E_M.format_id_spec
set_option maxHeartbeats 1000000
@[local step]
theorem route_spec (input : Slice Std.U8) : slot.pr_route input ⦃ fun _ => True ⦄ := by
 rw [slot.pr_route]
 step*
 all_goals repeat' (first | (split <;> step*) | scalar_tac)
end PR
namespace PM
section
end
section
set_option linter.unusedSimpArgs false
set_option linter.unusedVariables false
set_option linter.unusedTactic false
set_option linter.unreachableTactic false
end
namespace Submission
open Aeneas Aeneas.Std Result ControlFlow
open LZ77 (toks bytes)
set_option maxRecDepth 8192
set_option maxHeartbeats 4000000
theorem v10z (input : Slice Std.U8) (st k : Std.Usize) (lo hi : Std.U8) (n c i p : Std.Usize)
    (hn : n.val ≤ input.length) (hi0 : i.val ≤ 1024) :
    slot.pm_hy_rng_loop input st k lo hi n c i p ⦃ fun _ => True ⦄ := by
  rw [slot.pm_hy_rng_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => 1024 - s.2.1.val)
    (inv := fun s => s.2.1.val ≤ 1024)
  · rintro ⟨c, i, p⟩ hinv
    simp only [slot.pm_hy_rng_loop.body]
    step*
    all_goals (repeat' (first | split | step*))
    all_goals (first | omega | scalar_tac | skip)
  · exact hi0
theorem hy_rng_spec (input : Slice Std.U8) (st k : Std.Usize) (lo hi : Std.U8) :
    slot.pm_hy_rng input st k lo hi ⦃ fun _ => True ⦄ := by
  rw [slot.pm_hy_rng]
  have hlenv := Slice.len_val input
  exact v10z input st k lo hi _ _ _ _ (by first | assumption | omega | scalar_tac) (by simp)
theorem hy_d2_loop_spec (input : Slice Std.U8) (k n c i : Std.Usize)
    (hn : n.val ≤ input.length) (h2 : 2 ≤ i.val) (hi0 : i.val ≤ 4096) :
    slot.pm_hy_d2_loop input k n c i ⦃ fun _ => True ⦄ := by
  rw [slot.pm_hy_d2_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => 4096 - s.2.val)
    (inv := fun s => 2 ≤ s.2.val ∧ s.2.val ≤ 4096)
  · rintro ⟨c, i⟩ ⟨h2, hinv⟩
    simp only [slot.pm_hy_d2_loop.body]
    step*
    all_goals (repeat' (first | split | step*))
    all_goals (first | omega | scalar_tac | skip)
  · exact ⟨h2, hi0⟩
theorem hy_d2_spec (input : Slice Std.U8) (k : Std.Usize) :
    slot.pm_hy_d2 input k ⦃ fun _ => True ⦄ := by
  rw [slot.pm_hy_d2]
  have hlenv := Slice.len_val input
  exact hy_d2_loop_spec input k _ _ _ (by first | assumption | omega | scalar_tac) (by simp) (by simp)
theorem hy_qc_loop_spec (input : Slice Std.U8) (k n c i : Std.Usize)
    (hn : n.val ≤ input.length) (hi0 : i.val ≤ 4096) :
    slot.pm_hy_qc_loop input k n c i ⦃ fun _ => True ⦄ := by
  rw [slot.pm_hy_qc_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => 4096 - s.2.val)
    (inv := fun s => s.2.val ≤ 4096)
  · rintro ⟨c, i⟩ hinv
    simp only [slot.pm_hy_qc_loop.body]
    step*
    all_goals (repeat' (first | split | step*))
    all_goals (first | omega | scalar_tac | skip)
  · exact hi0
theorem hy_qc_spec (input : Slice Std.U8) (k : Std.Usize) :
    slot.pm_hy_qc input k ⦃ fun _ => True ⦄ := by
  rw [slot.pm_hy_qc]
  have hlenv := Slice.len_val input
  exact hy_qc_loop_spec input k _ _ _ (by first | assumption | omega | scalar_tac) (by simp)
section
attribute [local step] hy_rng_spec hy_d2_spec hy_qc_spec
theorem hy_ty_spec (input : Slice Std.U8) : slot.pm_hy_ty input ⦃ fun _ => True ⦄ := by
  rw [slot.pm_hy_ty]
  have hlenv := Slice.len_val input
  repeat' ((try dsimp only); split)
  all_goals (try step*)
end
section
attribute [local step] hy_ty_spec
end
end Submission
end PM
attribute [local step] PM.Submission.hy_ty_spec
@[local step]
theorem p135_row0_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.p135_row0 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := (by
 rw [slot.p135_row0]
 exact PC.run1c_spec _ input out _ _ _ _ _ _ hlen (by simp) (by simp))
@[local step]
theorem p135_row1_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.p135_row1 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.p135_row1]
 step*
@[local step]
theorem p135_row2_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.p135_row2 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.p135_row2]
 exact N70.n_run_spec _ _ _ _ _ _ _ _ _ input out hlen
@[local step]
theorem p135_row3_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.p135_row3 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.p135_row3]
 exact P12.p125_row12_spec input out hlen
@[local step]
theorem p135_row4_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.p135_row4 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.p135_row4]
 exact P12.p125_row15_spec input out hlen
@[local step]
theorem p135_row5_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.p135_row5 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.p135_row5]
 exact N70.n_run_spec _ _ _ _ _ _ _ _ _ input out hlen
@[local step]
theorem p135_row6_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.p135_row6 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.p135_row6]
 exact PI1.run1_spec _ input out _ _ _ _ hlen (by simp) (by simp)
@[local step]
theorem p135_row7_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.p135_row7 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.p135_row7]
 exact PIM.run1c_spec _ input out _ _ _ _ _ _ hlen (by simp) (by simp)
@[local step]
theorem p135_row8_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.p135_row8 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.p135_row8]
 exact FX0.run_spec _ _ _ _ input out _ hlen (by simp) (by simp)
@[local step]
theorem p135_row9_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.p135_row9 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.p135_row9]
 exact P12.p125_row10_spec input out hlen
@[local step]
theorem p135_row10_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.p135_row10 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := (by
 rw [slot.p135_row10]
 exact PC.run1c_spec _ input out _ _ _ _ _ _ hlen (by simp) (by simp))
@[local step]
theorem p135_row11_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.p135_row11 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.p135_row11]
 apply Std.WP.spec_bind (PR.route_spec input)
 intro k _
 split
 · exact PC.run1_spec _ input out _ _ _ _ hlen (by simp) (by simp)
 · split
   · exact Q4.run1t_spec _ input out _ _ _ _ hlen (by simp) (by simp)
   · exact Q4.run1_spec _ input out _ _ _ _ hlen (by simp) (by simp)
@[local step]
theorem p135_row12_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.p135_row12 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.p135_row12]
 exact PC.run1_spec _ input out _ _ _ _ hlen (by simp) (by simp)
@[local step]
theorem p135_row13_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.p135_row13 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.p135_row13]
 apply Std.WP.spec_bind (PR.route_spec input)
 intro k _
 split
 · exact PC.run1_spec _ input out _ _ _ _ hlen (by simp) (by simp)
 · split
   · exact PC.run1_spec _ input out _ _ _ _ hlen (by simp) (by simp)
   · exact PC.run1_spec _ input out _ _ _ _ hlen (by simp) (by simp)
@[local step]
theorem p135_row14_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.p135_row14 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := (by
 rw [slot.p135_row14]
 exact PC.run1c_spec _ input out _ _ _ _ _ _ hlen (by simp) (by simp))
@[local step]
theorem p135_row15_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.p135_row15 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.p135_row15]
 exact EO.EA.main_part_spec _ _ _ _ _ input out _ _ _ hlen (by simp) (by simp) (by simp [LZ77.toks, LZ77.decode])
@[local step]
theorem p135_row16_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.p135_row16 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := (by
 rw [slot.p135_row16]
 exact PC.run1c_spec _ input out _ _ _ _ _ _ hlen (by simp) (by simp))
@[local step]
theorem p135_row17_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.p135_row17 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.p135_row17]
 exact Q4.run1t_spec _ input out _ _ _ _ hlen (by simp) (by simp)
@[local step]
theorem p135_row18_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.p135_row18 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := (by
 rw [slot.p135_row18]
 exact PC.run1c_spec _ input out _ _ _ _ _ _ hlen (by simp) (by simp))
@[local step]
theorem p135_row19_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.p135_row19 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := (by
 rw [slot.p135_row19]
 exact PC.run1c_spec _ input out _ _ _ _ _ _ hlen (by simp) (by simp))
@[local step]
theorem fallback_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.fallback input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.fallback]
 exact Q4.lit_all_spec input out hlen
@[local step]
theorem bulk_parse_fallback_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.bulk_parse_fallback input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.bulk_parse_fallback]
 step*
 repeat' (split <;> step*)

@[local step]
theorem bulk_parse_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.bulk_parse input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.bulk_parse]
 step*
 repeat' (split <;> step*)
theorem parse_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.parse input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.parse]
 exact bulk_parse_spec input out hlen
end Submission

