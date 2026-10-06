import Lz77
import Slot
namespace Submission
open Aeneas Aeneas.Std Result ControlFlow
open LZ77 (toks bytes)
set_option maxRecDepth 8192
set_option maxHeartbeats 4000000
set_option hygiene false in
local notation "T9!" q0__:max q1__:max => (by
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
local notation "T10!" => (by
  (
  exact match_len_loop_spec input a b cap 0#usize ha hb (by scalar_tac)
    (LZ77.Matches.zero input a.val b.val)))
namespace EH
open Aeneas Aeneas.Std Result ControlFlow
set_option maxRecDepth 8192
set_option maxHeartbeats 4000000
set_option linter.unusedTactic false
set_option linter.unreachableTactic false
set_option linter.unusedSimpArgs false
open LZ77 (toks bytes bytes_length bytes_getElem! Matches emit_lit emit_match ite_ok)
theorem spec_ite_cut {α : Type} (c : Prop) [Decidable c] (a b : Result α) (Q : α → Prop)
    (ha : c → a ⦃ Q ⦄) (hb : ¬c → b ⦃ Q ⦄) : (if c then a else b) ⦃ Q ⦄ := by
  by_cases h : c
  · rw [if_pos h]; exact ha h
  · rw [if_neg h]; exact hb h
set_option hygiene false in
local notation "T14!" q0__:max => (by
  rw [q0__]
  try simp only [ite_ok]
  step*
  all_goals (repeat (split <;> step*))
  all_goals scalar_tac)
@[local step]
theorem get_spec (v : Slice Std.U32) (i : Std.Usize) :
    slot.h_get v i ⦃ fun _ => True ⦄ := T14! slot.h_get
@[local step]
theorem set_spec (v : Slice Std.U32) (i : Std.Usize) (x : Std.U32) :
    slot.h_set v i x ⦃ fun _ => True ⦄ := T14! slot.h_set
set_option hygiene false in
local notation "T15!" q0__:max => (by
  rw [q0__]
  simp only [lift, ite_ok, alloc.vec.Vec.deref_mut, bind_tc_ok]
  step*
  all_goals (repeat (split <;> step*))
  all_goals scalar_tac)
@[local step]
theorem bump_spec (v : Slice Std.U32) (i : Std.Usize) (by0 : Std.U32) :
    slot.h_bump v i by0 ⦃ fun _ => True ⦄ := T15! slot.h_bump
@[local step]
theorem set64_spec (v : Slice Std.U64) (i : Std.Usize) (x : Std.U64) :
    slot.h_set64 v i x ⦃ fun _ => True ⦄ := T14! slot.h_set64
@[local step]
theorem get8_spec (v : Slice Std.U8) (i : Std.Usize) :
    slot.h_get8 v i ⦃ fun _ => True ⦄ := T14! slot.h_get8
@[local step]
theorem byte_at_spec (input : Slice Std.U8) (i : Std.Usize) :
    slot.h_byte_at input i ⦃ fun _ => True ⦄ := T14! slot.h_byte_at
@[local step]
theorem setc_spec (a : Array Std.U32 65536#usize) (i : Std.Usize) (x : Std.U32) :
    slot.h_setc a i x ⦃ fun _ => True ⦄ := T14! slot.h_setc
theorem filled_loop0_spec (x : Std.U32) (v0 : alloc.vec.Vec Std.U32) (n8 i0 : Std.Usize)
    (hn8 : 8 * n8.val ≤ Std.Usize.max) (h0 : v0.length = 8 * i0.val) (hi : i0.val ≤ n8.val) :
    slot.h_filled_loop0 x v0 n8 i0 ⦃ fun r => r.length = 8 * n8.val ⦄ := by
  rw [slot.h_filled_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun s => n8.val - s.2.val)
    (inv := fun s => s.1.length = 8 * s.2.val ∧ s.2.val ≤ n8.val)
  · rintro ⟨v, i⟩ ⟨hv, hle⟩
    simp only at hv hle
    simp only [slot.h_filled_loop0.body]
    split
    case isTrue hlt =>
      step*
      all_goals (simp_all; scalar_tac)
    case isFalse hge =>
      simp only [Std.WP.spec_ok]
      scalar_tac
  · exact ⟨h0, hi⟩
theorem filled_loop1_spec (n : Std.Usize) (x : Std.U32) (v0 : alloc.vec.Vec Std.U32)
    (j0 : Std.Usize) (h0 : v0.length = j0.val) (hj : j0.val ≤ n.val) :
    slot.h_filled_loop1 n x v0 j0 ⦃ fun r => r.length = n.val ⦄ := by
  rw [slot.h_filled_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun s => n.val - s.2.val)
    (inv := fun s => s.1.length = s.2.val ∧ s.2.val ≤ n.val)
  · rintro ⟨v, j⟩ ⟨hv, hle⟩
    simp only at hv hle
    simp only [slot.h_filled_loop1.body]
    split
    case isTrue hlt =>
      step*
      simp_all
      scalar_tac
    case isFalse hge =>
      simp only [Std.WP.spec_ok]
      scalar_tac
  · exact ⟨h0, hj⟩
@[local step]
theorem filled_spec (n : Std.Usize) (x : Std.U32) :
    slot.h_filled n x ⦃ fun r => r.length = n.val ⦄ := by
  rw [slot.h_filled]
  step*
  apply Std.WP.spec_bind (filled_loop0_spec x _ n8 0#usize (by scalar_tac)
    (by simp [alloc.vec.Vec.with_capacity]) (by scalar_tac))
  intro v1 hv1
  step*
  exact filled_loop1_spec n x v1 j (by scalar_tac) (by scalar_tac)
@[local step]
theorem push_guarded_spec (v : alloc.vec.Vec Std.U32) (x : Std.U32) :
    slot.h_push_guarded v x ⦃ fun _ => True ⦄ := T14! slot.h_push_guarded
@[local step]
theorem sel_spec (f : Std.Usize) (a : Std.Usize) (b : Std.Usize) :
    slot.h_sel f a b ⦃ fun _ => True ⦄ := T14! slot.h_sel
@[local step]
theorem sel32_spec (f : Std.Usize) (a : Std.U32) (b : Std.U32) :
    slot.h_sel32 f a b ⦃ fun _ => True ⦄ := T14! slot.h_sel32
@[local step]
theorem sel64_spec (f : Std.Usize) (a : Std.U64) (b : Std.U64) :
    slot.h_sel64 f a b ⦃ fun _ => True ⦄ := T14! slot.h_sel64
@[local step]
theorem ge_spec (a : Std.Usize) (b : Std.Usize) :
    slot.h_ge a b ⦃ fun _ => True ⦄ := T14! slot.h_ge
@[local step]
theorem lt_spec (a : Std.Usize) (b : Std.Usize) :
    slot.h_lt a b ⦃ fun _ => True ⦄ := T14! slot.h_lt
@[local step]
theorem eq_spec (a : Std.Usize) (b : Std.Usize) :
    slot.h_eq a b ⦃ fun _ => True ⦄ := T14! slot.h_eq
@[local step]
theorem lt32_spec (a : Std.U32) (b : Std.U32) :
    slot.h_lt32 a b ⦃ fun _ => True ⦄ := T14! slot.h_lt32
@[local step]
theorem lt64_spec (a : Std.U64) (b : Std.U64) :
    slot.h_lt64 a b ⦃ fun _ => True ⦄ := T14! slot.h_lt64
@[local step]
theorem umin_spec (a : Std.Usize) (b : Std.Usize) :
    slot.h_umin a b ⦃ fun _ => True ⦄ := T14! slot.h_umin
@[local step]
theorem umax_spec (a : Std.Usize) (b : Std.Usize) :
    slot.h_umax a b ⦃ fun _ => True ⦄ := T14! slot.h_umax
@[local step]
theorem eq64_spec (a : Std.U64) (b : Std.U64) :
    slot.h_eq64 a b ⦃ fun _ => True ⦄ := T14! slot.h_eq64
@[local step]
theorem umin64_spec (a : Std.U64) (b : Std.U64) :
    slot.h_umin64 a b ⦃ fun _ => True ⦄ := T14! slot.h_umin64
@[local step]
theorem push_if_spec (v : alloc.vec.Vec Std.U32) (f : Std.Usize) (x : Std.U32) :
    slot.h_push_if v f x ⦃ fun _ => True ⦄ := T14! slot.h_push_if
@[local step]
theorem dslot_spec (d : Std.Usize) :
    slot.h_dslot d ⦃ fun _ => True ⦄ := T15! slot.h_dslot
@[local step]
theorem pack_m_spec (len : Std.Usize) (d : Std.Usize) :
    slot.h_pack_m len d ⦃ fun _ => True ⦄ := T15! slot.h_pack_m
@[local step]
theorem push_m_spec (v : alloc.vec.Vec Std.U32) (f : Std.Usize) (len : Std.Usize) (d : Std.Usize) :
    slot.h_push_m v f len d ⦃ fun _ => True ⦄ := T14! slot.h_push_m
@[local step]
theorem push_slot1_spec (mc : alloc.vec.Vec Std.U32) (m0 : Std.Usize) (len : Std.Usize) (d : Std.Usize) :
    slot.h_push_slot1 mc m0 len d ⦃ fun _ => True ⦄ := T15! slot.h_push_slot1
@[local step]
theorem push_slot_spec (mc : alloc.vec.Vec Std.U32) (m0 : Std.Usize) (f : Std.Usize) (len : Std.Usize) (d : Std.Usize) :
    slot.h_push_slot mc m0 f len d ⦃ fun _ => True ⦄ := T14! slot.h_push_slot
@[local step]
theorem clamp_step_spec (l room : Std.Usize) :
    slot.h_clamp_step l room ⦃ fun r => 1 ≤ r.val ∧ (r.val = 1 ∨ r.val ≤ room.val) ⦄ := by
  rw [slot.h_clamp_step]
  step*
@[local step]
theorem clamp1_spec (l room : Std.Usize) :
    slot.h_clamp1 l room ⦃ fun r => 1 ≤ r.val ∧ (r.val = 1 ∨ r.val ≤ room.val) ⦄ := by
  rw [slot.h_clamp1]
  step*
@[local step]
theorem nz64_spec (x : Std.U64) : slot.h_nz64 x ⦃ fun r => 0 < r.val ⦄ := by
  rw [slot.h_nz64]
  step*
theorem match_len_loop_spec (input : Slice Std.U8) (a b cap l0 : Std.Usize)
    (ha : a.val + cap.val ≤ input.length) (hb : b.val + cap.val ≤ input.length)
    (hl0 : l0.val ≤ cap.val) (h0 : Matches input a.val b.val l0.val) :
    slot.h_match_len_loop input a b cap l0 ⦃ fun l =>
      l.val ≤ cap.val ∧ Matches input a.val b.val l.val ⦄ := T9! slot.h_match_len_loop slot.h_match_len_loop.body
@[local step]
theorem match_len_spec (input : Slice Std.U8) (a b cap : Std.Usize)
    (ha : a.val + cap.val ≤ input.length) (hb : b.val + cap.val ≤ input.length) :
    slot.h_match_len input a b cap ⦃ fun l =>
      l.val ≤ cap.val ∧ Matches input a.val b.val l.val ⦄ := T10!
theorem verified_spec (input : Slice Std.U8) (pos d ch : Std.Usize) :
    slot.h_verified input pos d ch ⦃ fun b => b = true →
      3 ≤ ch.val ∧ ch.val ≤ 258 ∧ 1 ≤ d.val ∧ d.val ≤ 32768 ∧ d.val ≤ pos.val ∧
      pos.val + ch.val ≤ input.length ∧ Matches input (pos.val - d.val) pos.val ch.val ⦄ := by
  rw [slot.h_verified]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  step*
  intro hv
  have hv' : ch.val ≤ v.val := by simpa using hv
  refine ⟨by scalar_tac, by scalar_tac, by scalar_tac, by scalar_tac, by scalar_tac,
    by scalar_tac, ?_⟩
  rw [show pos.val - d.val = i1.val by scalar_tac]
  exact Matches.mono v_post2 hv'
theorem emit_all_loop_spec (input : Slice Std.U8) (out0 : Slice Std.U32)
    (plan : Slice Std.U32) (n k0 ntok0 : Std.Usize)
    (hn : n.val = input.length) (hout : input.length ≤ out0.length)
    (hk : k0.val ≤ n.val) (hntok : ntok0.val ≤ k0.val)
    (hdec : LZ77.decode (toks out0 ntok0.val) = some ((bytes input).take k0.val)) :
    slot.h_emit_all_loop input out0 plan n k0 ntok0 ⦃ fun r =>
      r.1.val ≤ input.length ∧ r.2.length = out0.length ∧
      LZ77.decode (toks r.2 r.1.val) = some (bytes input) ⦄ := by
  rw [slot.h_emit_all_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => n.val - s.2.1.val)
    (inv := fun s =>
      s.2.1.val ≤ n.val ∧ s.2.2.val ≤ s.2.1.val ∧ s.1.length = out0.length ∧
      LZ77.decode (toks s.1 s.2.2.val) = some ((bytes input).take s.2.1.val))
  · rintro ⟨out, k, ntok⟩ ⟨hkn, hnt, hlen, hde⟩
    simp only at hkn hnt hlen hde
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.h_emit_all_loop.body]
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
  · exact ⟨hk, hntok, rfl, hdec⟩
@[local step]
theorem emit_all_spec (input : Slice Std.U8) (out : Slice Std.U32)
    (plan : Slice Std.U32) (hout : input.length ≤ out.length) :
    slot.h_emit_all input out plan ⦃ fun r =>
      r.1.val ≤ input.length ∧ r.2.length = out.length ∧
      LZ77.decode (toks r.2 r.1.val) = some (bytes input) ⦄ := by
  rw [slot.h_emit_all]
  exact emit_all_loop_spec input out plan _ 0#usize 0#usize
    (by simp) hout (by scalar_tac) (by scalar_tac) (by simp [toks, LZ77.decode])
@[local step]
theorem le64_spec (input : Slice Std.U8) (p : Std.Usize) :
    slot.h_le64 input p ⦃ fun _ => True ⦄ := T15! slot.h_le64
@[local step]
theorem first_diff_spec (x : Std.U64) (y : Std.U64) :
    slot.h_first_diff x y ⦃ fun _ => True ⦄ := T15! slot.h_first_diff
@[local step]
theorem hash4_spec (input : Slice Std.U8) (p : Std.Usize) :
    slot.h_hash4 input p ⦃ fun _ => True ⦄ := T15! slot.h_hash4
@[local step]
theorem hash3_spec (input : Slice Std.U8) (p : Std.Usize) :
    slot.h_hash3 input p ⦃ fun _ => True ⦄ := T15! slot.h_hash3
@[local step]
theorem dextra_spec (s : Std.Usize) :
    slot.h_dextra s ⦃ fun _ => True ⦄ := T15! slot.h_dextra
@[local step]
theorem lcode_spec (l : Std.Usize) :
    slot.h_lcode l ⦃ fun r => r.val ≤ 28 ⦄ := by
  rw [slot.h_lcode]
  simp only [lift, ite_ok, alloc.vec.Vec.deref_mut, bind_tc_ok]
  step*
  all_goals (repeat (split <;> try step*))
  all_goals (try split_ifs)
  all_goals first
    | scalar_tac
    | (simp only [core.num.Usize.wrapping_sub_val_eq, UScalar.size, UScalarTy.numBits]
       cases System.Platform.numBits_eq <;> simp_all <;> scalar_tac)
@[local step]
theorem lextra_spec (c : Std.Usize) :
    slot.h_lextra c ⦃ fun _ => True ⦄ := T15! slot.h_lextra
@[local step]
theorem fixed_len_spec (s : Std.Usize) :
    slot.h_fixed_len s ⦃ fun _ => True ⦄ := T14! slot.h_fixed_len
@[local step]
theorem ext_len_loop_spec (input : Slice Std.U8) (a : Std.Usize) (b : Std.Usize) (lim : Std.Usize) (l : Std.Usize) (it : Std.Usize) :
    slot.h_ext_len_loop input a b lim l it ⦃ fun _ => True ⦄ := by
  rw [slot.h_ext_len_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 300 - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨l1, it1⟩ _
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.h_ext_len_loop.body, lift]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem ext_len_spec (input : Slice Std.U8) (a : Std.Usize) (b : Std.Usize) (from0 : Std.Usize) (cap : Std.Usize) :
    slot.h_ext_len input a b from0 cap ⦃ fun _ => True ⦄ := T15! slot.h_ext_len
@[local step]
theorem ext_if_spec (input : Slice Std.U8) (f : Std.Usize) (a : Std.Usize) (b : Std.Usize) (from0 : Std.Usize) (cap : Std.Usize) (dflt : Std.Usize) :
    slot.h_ext_if input f a b from0 cap dflt ⦃ fun _ => True ⦄ := T14! slot.h_ext_if
@[local step]
theorem le64_tail_loop_spec (input : Slice Std.U8) (p : Std.Usize) (x : Std.U64) (j : Std.Usize) :
    slot.h_le64_tail_loop input p x j ⦃ fun _ => True ⦄ := by
  rw [slot.h_le64_tail_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 8 - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨x1, j1⟩ _
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.h_le64_tail_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem le64_tail_spec (input : Slice Std.U8) (p : Std.Usize) :
    slot.h_le64_tail input p ⦃ fun _ => True ⦄ := T14! slot.h_le64_tail
@[local step]
theorem le64z_spec (input : Slice Std.U8) (p : Std.Usize) :
    slot.h_le64z input p ⦃ fun _ => True ⦄ := T14! slot.h_le64z
@[local step]
theorem byte_lt_spec (x : Std.U64) (y : Std.U64) (k : Std.Usize) :
    slot.h_byte_lt x y k ⦃ fun _ => True ⦄ := T15! slot.h_byte_lt
@[local step]
theorem lcp_words_loop_spec (input : Slice Std.U8) (a : Std.Usize) (b : Std.Usize) (lim : Std.Usize) (l : Std.Usize) (it : Std.Usize) (z : Std.U64) (x : Std.U64) :
    slot.h_lcp_words_loop input a b lim l it z x ⦃ fun _ => True ⦄ := by
  rw [slot.h_lcp_words_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 40 - qq9.2.1.val)
    (inv := fun _ => True)
  · rintro ⟨l1, it1, z1, x1⟩ _
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.h_lcp_words_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem lcp_words_spec (input : Slice Std.U8) (a : Std.Usize) (b : Std.Usize) (l0 : Std.Usize) (lim : Std.Usize) :
    slot.h_lcp_words input a b l0 lim ⦃ fun _ => True ⦄ := T15! slot.h_lcp_words
@[local step]
theorem ext_words_spec (input : Slice Std.U8) (same : Std.Usize) (a : Std.Usize) (b : Std.Usize) (l0 : Std.Usize) (x : Std.U64) (y : Std.U64) (lim : Std.Usize) :
    slot.h_ext_words input same a b l0 x y lim ⦃ fun _ => True ⦄ := T15! slot.h_ext_words
@[local step]
theorem bt_walk_loop_spec (input : Slice Std.U8) (child : Array Std.U32 65536#usize) (pos : Std.Usize) (rec : Std.Usize) (maxd : Std.Usize) (mc : alloc.vec.Vec Std.U32) (m0 : Std.Usize) (plt : Std.Usize) (pgt : Std.Usize) (cur : Std.Usize) (ltl : Std.Usize) (gtl : Std.Usize) (len : Std.Usize) (best : Std.Usize) (wl : Std.Usize) (wd : Std.Usize) (depth : Std.Usize) (go : Std.Usize) (lim : Std.Usize) (stop : Std.Usize) (kcur : Std.Usize) (kl : Std.Usize) :
    slot.h_bt_walk_loop input child pos rec maxd mc m0 plt pgt cur ltl gtl len best wl wd depth go lim stop kcur kl ⦃ fun _ => True ⦄ := by
  rw [slot.h_bt_walk_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => maxd.val - qq9.2.2.2.2.2.2.2.2.2.2.2.1.val)
    (inv := fun _ => True)
  · rintro ⟨child1, mc1, plt1, pgt1, cur1, ltl1, gtl1, len1, best1, wl1, wd1, depth1, go1⟩ _
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.h_bt_walk_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem bt_walk_spec (input : Slice Std.U8) (child : Array Std.U32 65536#usize) (root : Std.Usize) (pos : Std.Usize) (cap : Std.Usize) (best0 : Std.Usize) (rec : Std.Usize) (maxd : Std.Usize) (hint : Std.Usize) (mc : alloc.vec.Vec Std.U32) (m0 : Std.Usize) :
    slot.h_bt_walk input child root pos cap best0 rec maxd hint mc m0 ⦃ fun _ => True ⦄ := T15! slot.h_bt_walk
@[local step]
theorem sks_rec_spec (gap : Std.Usize) :
    slot.h_sks_rec gap ⦃ fun _ => True ⦄ := T15! slot.h_sks_rec
@[local step]
theorem find_pos_spec (input : Slice Std.U8) (h4 : Array Std.U32 65536#usize) (h3 : Array Std.U32 131072#usize) (child : Array Std.U32 65536#usize) (mc : alloc.vec.Vec Std.U32) (st : Array Std.Usize 4#usize) (pos : Std.Usize) (maxd : Std.Usize) :
    slot.h_find_pos input h4 h3 child mc st pos maxd ⦃ fun _ => True ⦄ := T15! slot.h_find_pos
@[local step]
theorem find_all_loop_spec (input : Slice Std.U8) (mstart : alloc.vec.Vec Std.U32) (mc : alloc.vec.Vec Std.U32) (maxd : Std.Usize) (n : Std.Usize) (h4 : Array Std.U32 65536#usize) (h3 : Array Std.U32 131072#usize) (child : Array Std.U32 65536#usize) (st : Array Std.Usize 4#usize) (pos : Std.Usize) :
    slot.h_find_all_loop input mstart mc maxd n h4 h3 child st pos ⦃ fun _ => True ⦄ := by
  rw [slot.h_find_all_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => n.val - qq9.2.2.2.2.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨mstart1, mc1, h41, h31, child1, st1, pos1⟩ _
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.h_find_all_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem find_all_spec (input : Slice Std.U8) (mstart : alloc.vec.Vec Std.U32) (mc : alloc.vec.Vec Std.U32) (maxd : Std.Usize) :
    slot.h_find_all input mstart mc maxd ⦃ fun _ => True ⦄ := T15! slot.h_find_all
@[local step]
theorem find_spare_spec (input : Slice Std.U8) (f : Std.Usize) :
    slot.h_find_spare input f ⦃ fun _ => True ⦄ := T14! slot.h_find_spare
@[local step]
theorem bucket_end_spec (l : Std.Usize) :
    slot.h_bucket_end l ⦃ fun _ => True ⦄ := T15! slot.h_bucket_end
@[local step]
theorem build_bend_loop_spec (bend : Array Std.U32 512#usize) (l : Std.Usize) :
    slot.h_build_bend_loop bend l ⦃ fun _ => True ⦄ := by
  rw [slot.h_build_bend_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 259 - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨bend1, l1⟩ _
    simp only [slot.h_build_bend_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem build_bend_spec (bend : Array Std.U32 512#usize) :
    slot.h_build_bend bend ⦃ fun _ => True ⦄ := T14! slot.h_build_bend
@[local step]
theorem lg5_spec (w : Std.Usize) :
    slot.h_lg5 w ⦃ fun _ => True ⦄ := T15! slot.h_lg5
@[local step]
theorem load_ct_loop0_spec (tbl : Slice Std.U32) (toff : Std.Usize) (ct : Array Std.U32 1024#usize) (lam : Std.U32) (x : Std.Usize) :
    slot.h_load_ct_loop0 tbl toff ct lam x ⦃ fun _ => True ⦄ := by
  rw [slot.h_load_ct_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 259 - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨ct1, x1⟩ _
    simp only [slot.h_load_ct_loop0.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem load_ct_loop1_spec (tbl : Slice Std.U32) (toff : Std.Usize) (ct : Array Std.U32 1024#usize) (s : Std.Usize) :
    slot.h_load_ct_loop1 tbl toff ct s ⦃ fun _ => True ⦄ := by
  rw [slot.h_load_ct_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 30 - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨ct1, s1⟩ _
    simp only [slot.h_load_ct_loop1.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem load_ct_loop2_spec (tbl : Slice Std.U32) (toff : Std.Usize) (ct : Array Std.U32 1024#usize) (lam : Std.U32) (c : Std.Usize) :
    slot.h_load_ct_loop2 tbl toff ct lam c ⦃ fun _ => True ⦄ := by
  rw [slot.h_load_ct_loop2]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 256 - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨ct1, c1⟩ _
    simp only [slot.h_load_ct_loop2.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem load_ct_spec (tbl : Slice Std.U32) (toff : Std.Usize) (ct : Array Std.U32 1024#usize) (lam : Std.U32) :
    slot.h_load_ct tbl toff ct lam ⦃ fun _ => True ⦄ := T14! slot.h_load_ct
@[local step]
theorem rm_update_spec (rm : Array Std.U64 4096#usize) (i : Std.Usize) (c : Std.U64) :
    slot.h_rm_update rm i c ⦃ fun _ => True ⦄ := T15! slot.h_rm_update
@[local step]
theorem rm_update3_spec (rm : Array Std.U64 4096#usize) (i : Std.Usize) (c : Std.U64) :
    slot.h_rm_update3 rm i c ⦃ fun _ => True ⦄ := T15! slot.h_rm_update3
@[local step]
theorem rm_upd_spec (f : Std.Usize) (rm : Array Std.U64 4096#usize) (i : Std.Usize) (c : Std.U64) :
    slot.h_rm_upd f rm i c ⦃ fun _ => True ⦄ := T14! slot.h_rm_upd
@[local step]
theorem bkt_val_spec (rm : Array Std.U64 4096#usize) (ct : Array Std.U32 1024#usize) (i : Std.Usize) (x : Std.Usize) (e : Std.Usize) (dcs : Std.U64) :
    slot.h_bkt_val rm ct i x e dcs ⦃ fun _ => True ⦄ := T15! slot.h_bkt_val
@[local step]
theorem query_spec (x : Std.Usize) (y : Std.Usize) (k : Std.Usize) (slot0 : Std.Usize) :
    slot.h_query x y k slot0 ⦃ fun _ => True ⦄ := T15! slot.h_query
@[local step]
theorem prune_short_loop_spec (rm : Array Std.U64 4096#usize) (ct : Array Std.U32 1024#usize) (i : Std.Usize) (hi : Std.Usize) (dcs : Std.U64) (slot0 : Std.Usize) (keep : Std.Usize) (items : alloc.vec.Vec Std.U32) (best : Std.U64) (x : Std.Usize) :
    slot.h_prune_short_loop rm ct i hi dcs slot0 keep items best x ⦃ fun _ => True ⦄ := by
  rw [slot.h_prune_short_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 11 - qq9.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨items1, best1, x1⟩ _
    simp only [slot.h_prune_short_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem prune_short_spec (rm : Array Std.U64 4096#usize) (ct : Array Std.U32 1024#usize) (i : Std.Usize) (lo : Std.Usize) (hi : Std.Usize) (dcs : Std.U64) (slot0 : Std.Usize) (best0 : Std.U64) (keep : Std.Usize) (items : alloc.vec.Vec Std.U32) :
    slot.h_prune_short rm ct i lo hi dcs slot0 best0 keep items ⦃ fun _ => True ⦄ := T14! slot.h_prune_short
@[local step]
theorem prune_bkt_loop_spec (rm : Array Std.U64 4096#usize) (ct : Array Std.U32 1024#usize) (bend : Array Std.U32 512#usize) (i : Std.Usize) (hi : Std.Usize) (dcs : Std.U64) (slot0 : Std.Usize) (keep : Std.Usize) (items : alloc.vec.Vec Std.U32) (best : Std.U64) (x : Std.Usize) (it : Std.Usize) :
    slot.h_prune_bkt_loop rm ct bend i hi dcs slot0 keep items best x it ⦃ fun _ => True ⦄ := by
  rw [slot.h_prune_bkt_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 32 - qq9.2.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨items1, best1, x1, it1⟩ _
    simp only [slot.h_prune_bkt_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem prune_bkt_spec (rm : Array Std.U64 4096#usize) (ct : Array Std.U32 1024#usize) (bend : Array Std.U32 512#usize) (i : Std.Usize) (lo : Std.Usize) (hi : Std.Usize) (dcs : Std.U64) (slot0 : Std.Usize) (best0 : Std.U64) (keep : Std.Usize) (items : alloc.vec.Vec Std.U32) :
    slot.h_prune_bkt rm ct bend i lo hi dcs slot0 best0 keep items ⦃ fun _ => True ⦄ := T14! slot.h_prune_bkt
@[local step]
theorem prune_pos_loop_spec (rm : Array Std.U64 4096#usize) (ct : Array Std.U32 1024#usize) (bend : Array Std.U32 512#usize) (mc : Slice Std.U32) (me : Std.Usize) (i : Std.Usize) (chw : Std.Usize) (msub : Std.U32) (keep : Std.Usize) (items : alloc.vec.Vec Std.U32) (best : Std.U64) (k : Std.Usize) (lo : Std.Usize) :
    slot.h_prune_pos_loop rm ct bend mc me i chw msub keep items best k lo ⦃ fun _ => True ⦄ := by
  rw [slot.h_prune_pos_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => me.val - qq9.2.2.1.val)
    (inv := fun _ => True)
  · rintro ⟨items1, best1, k1, lo1⟩ _
    simp only [slot.h_prune_pos_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem prune_pos_spec (rm : Array Std.U64 4096#usize) (ct : Array Std.U32 1024#usize) (bend : Array Std.U32 512#usize) (mc : Slice Std.U32) (ms : Std.Usize) (me : Std.Usize) (i : Std.Usize) (lit : Std.U64) (chw : Std.Usize) (msub : Std.U32) (keep : Std.Usize) (items : alloc.vec.Vec Std.U32) :
    slot.h_prune_pos rm ct bend mc ms me i lit chw msub keep items ⦃ fun _ => True ⦄ := T15! slot.h_prune_pos
@[local step]
theorem relax_short_loop_spec (rm : Array Std.U64 4096#usize) (ct : Array Std.U32 1024#usize) (i : Std.Usize) (hi : Std.Usize) (dcs : Std.U64) (best : Std.U64) (x : Std.Usize) :
    slot.h_relax_short_loop rm ct i hi dcs best x ⦃ fun _ => True ⦄ := by
  rw [slot.h_relax_short_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 11 - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨best1, x1⟩ _
    simp only [slot.h_relax_short_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem relax_short_spec (rm : Array Std.U64 4096#usize) (ct : Array Std.U32 1024#usize) (i : Std.Usize) (lo : Std.Usize) (hi : Std.Usize) (dcs : Std.U64) (best0 : Std.U64) :
    slot.h_relax_short rm ct i lo hi dcs best0 ⦃ fun _ => True ⦄ := T14! slot.h_relax_short
@[local step]
theorem relax_bkt_loop_spec (rm : Array Std.U64 4096#usize) (ct : Array Std.U32 1024#usize) (bend : Array Std.U32 512#usize) (i : Std.Usize) (hi : Std.Usize) (dcs : Std.U64) (best : Std.U64) (x : Std.Usize) (it : Std.Usize) :
    slot.h_relax_bkt_loop rm ct bend i hi dcs best x it ⦃ fun _ => True ⦄ := by
  rw [slot.h_relax_bkt_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 32 - qq9.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨best1, x1, it1⟩ _
    simp only [slot.h_relax_bkt_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem relax_bkt_spec (rm : Array Std.U64 4096#usize) (ct : Array Std.U32 1024#usize) (bend : Array Std.U32 512#usize) (i : Std.Usize) (lo : Std.Usize) (hi : Std.Usize) (dcs : Std.U64) (best0 : Std.U64) :
    slot.h_relax_bkt rm ct bend i lo hi dcs best0 ⦃ fun _ => True ⦄ := T14! slot.h_relax_bkt
@[local step]
theorem relax_pos_loop_spec (rm : Array Std.U64 4096#usize) (ct : Array Std.U32 1024#usize) (bend : Array Std.U32 512#usize) (mc : Slice Std.U32) (me : Std.Usize) (i : Std.Usize) (chw : Std.Usize) (msub : Std.U32) (best : Std.U64) (k : Std.Usize) (lo : Std.Usize) :
    slot.h_relax_pos_loop rm ct bend mc me i chw msub best k lo ⦃ fun _ => True ⦄ := by
  rw [slot.h_relax_pos_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => me.val - qq9.2.1.val)
    (inv := fun _ => True)
  · rintro ⟨best1, k1, lo1⟩ _
    simp only [slot.h_relax_pos_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem relax_pos_spec (rm : Array Std.U64 4096#usize) (ct : Array Std.U32 1024#usize) (bend : Array Std.U32 512#usize) (mc : Slice Std.U32) (ms : Std.Usize) (me : Std.Usize) (i : Std.Usize) (lit : Std.U64) (chw : Std.Usize) (msub : Std.U32) :
    slot.h_relax_pos rm ct bend mc ms me i lit chw msub ⦃ fun _ => True ⦄ := T14! slot.h_relax_pos
@[local step]
theorem prune_or_relax_spec (rm : Array Std.U64 4096#usize) (ct : Array Std.U32 1024#usize) (bend : Array Std.U32 512#usize) (mc : Slice Std.U32) (ms : Std.Usize) (me : Std.Usize) (i : Std.Usize) (lit : Std.U64) (chw : Std.Usize) (msub : Std.U32) (keep : Std.Usize) (items : alloc.vec.Vec Std.U32) :
    slot.h_prune_or_relax rm ct bend mc ms me i lit chw msub keep items ⦃ fun _ => True ⦄ := T14! slot.h_prune_or_relax
@[local step]
theorem relax_items_loop_spec (rm : Array Std.U64 4096#usize) (ct : Array Std.U32 1024#usize) (items : Slice Std.U32) (e : Std.Usize) (i : Std.Usize) (best : Std.U64) (t : Std.Usize) :
    slot.h_relax_items_loop rm ct items e i best t ⦃ fun _ => True ⦄ := by
  rw [slot.h_relax_items_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => e.val - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨best1, t1⟩ _
    simp only [slot.h_relax_items_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem relax_items_spec (rm : Array Std.U64 4096#usize) (ct : Array Std.U32 1024#usize) (items : Slice Std.U32) (s : Std.Usize) (e : Std.Usize) (i : Std.Usize) (lit : Std.U64) :
    slot.h_relax_items rm ct items s e i lit ⦃ fun _ => True ⦄ := T14! slot.h_relax_items
@[local step]
theorem dp_prune_loop_spec (input : Slice Std.U8) (rm : Array Std.U64 4096#usize) (ct : Array Std.U32 1024#usize) (bend : Array Std.U32 512#usize) (mstart : Slice Std.U32) (mc : Slice Std.U32) (choice : Slice Std.U32) (chw : Std.Usize) (msub : Std.U32) (keep : Std.Usize) (items : alloc.vec.Vec Std.U32) (istart : alloc.vec.Vec Std.U32) (lo : Std.Usize) (l4 : Std.Usize) (co : Std.Usize) (i : Std.Usize) :
    slot.h_dp_prune_loop input rm ct bend mstart mc choice chw msub keep items istart lo l4 co i ⦃ fun _ => True ⦄ := by
  rw [slot.h_dp_prune_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => qq9.2.2.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨rm1, choice1, items1, istart1, i1⟩ _
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.h_dp_prune_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem dp_prune_spec (input : Slice Std.U8) (rm : Array Std.U64 4096#usize) (ct : Array Std.U32 1024#usize) (bend : Array Std.U32 512#usize) (mstart : Slice Std.U32) (mc : Slice Std.U32) (choice : Slice Std.U32) (chw : Std.Usize) (msub : Std.U32) (keep : Std.Usize) (items : alloc.vec.Vec Std.U32) (istart : alloc.vec.Vec Std.U32) (lo : Std.Usize) (hi : Std.Usize) (l4 : Std.Usize) (co : Std.Usize) :
    slot.h_dp_prune input rm ct bend mstart mc choice chw msub keep items istart lo hi l4 co ⦃ fun _ => True ⦄ := T14! slot.h_dp_prune
@[local step]
theorem blk_lo_spec (bpos : Slice Std.U32) (b : Std.Usize) (hi : Std.Usize) :
    slot.h_blk_lo bpos b hi ⦃ fun _ => True ⦄ := T15! slot.h_blk_lo
@[local step]
theorem pass_prune_loop_spec (input : Slice Std.U8) (mstart : Slice Std.U32) (mc : Slice Std.U32) (tbl : Slice Std.U32) (bend : Array Std.U32 512#usize) (bpos : Slice Std.U32) (nb : Std.Usize) (choice : Slice Std.U32) (chw : Std.Usize) (msub : Std.U32) (keep : Std.Usize) (items : alloc.vec.Vec Std.U32) (istart : alloc.vec.Vec Std.U32) (co : Std.Usize) (lam : Std.U32) (rm : Array Std.U64 4096#usize) (ct : Array Std.U32 1024#usize) (hi : Std.Usize) (k : Std.Usize) :
    slot.h_pass_prune_loop input mstart mc tbl bend bpos nb choice chw msub keep items istart co lam rm ct hi k ⦃ fun _ => True ⦄ := by
  rw [slot.h_pass_prune_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => nb.val - qq9.2.2.2.2.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨choice1, items1, istart1, rm1, ct1, hi1, k1⟩ _
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.h_pass_prune_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem pass_prune_spec (input : Slice Std.U8) (mstart : Slice Std.U32) (mc : Slice Std.U32) (tbl : Slice Std.U32) (bend : Array Std.U32 512#usize) (bpos : Slice Std.U32) (nb : Std.Usize) (choice : Slice Std.U32) (chw : Std.Usize) (msub : Std.U32) (keep : Std.Usize) (items : alloc.vec.Vec Std.U32) (istart : alloc.vec.Vec Std.U32) (co : Std.Usize) (lam : Std.U32) :
    slot.h_pass_prune input mstart mc tbl bend bpos nb choice chw msub keep items istart co lam ⦃ fun _ => True ⦄ := T15! slot.h_pass_prune
@[local step]
theorem dp_items_loop_spec (input : Slice Std.U8) (rm : Array Std.U64 4096#usize) (ct : Array Std.U32 1024#usize) (choice : Slice Std.U32) (items : Slice Std.U32) (istart : Slice Std.U32) (lo : Std.Usize) (l4 : Std.Usize) (co : Std.Usize) (n : Std.Usize) (e : Std.Usize) (i : Std.Usize) :
    slot.h_dp_items_loop input rm ct choice items istart lo l4 co n e i ⦃ fun _ => True ⦄ := by
  rw [slot.h_dp_items_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => qq9.2.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨rm1, choice1, e1, i1⟩ _
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.h_dp_items_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem dp_items_spec (input : Slice Std.U8) (rm : Array Std.U64 4096#usize) (ct : Array Std.U32 1024#usize) (choice : Slice Std.U32) (items : Slice Std.U32) (istart : Slice Std.U32) (lo : Std.Usize) (hi : Std.Usize) (l4 : Std.Usize) (co : Std.Usize) :
    slot.h_dp_items input rm ct choice items istart lo hi l4 co ⦃ fun _ => True ⦄ := T15! slot.h_dp_items
@[local step]
theorem pass_items_loop_spec (input : Slice Std.U8) (tbl : Slice Std.U32) (bpos : Slice Std.U32) (nb : Std.Usize) (choice : Slice Std.U32) (items : Slice Std.U32) (istart : Slice Std.U32) (l4 : Std.Usize) (co : Std.Usize) (lam : Std.U32) (rm : Array Std.U64 4096#usize) (ct : Array Std.U32 1024#usize) (hi : Std.Usize) (k : Std.Usize) :
    slot.h_pass_items_loop input tbl bpos nb choice items istart l4 co lam rm ct hi k ⦃ fun _ => True ⦄ := by
  rw [slot.h_pass_items_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => nb.val - qq9.2.2.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨choice1, rm1, ct1, hi1, k1⟩ _
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.h_pass_items_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem pass_items_spec (input : Slice Std.U8) (tbl : Slice Std.U32) (bpos : Slice Std.U32) (nb : Std.Usize) (choice : Slice Std.U32) (items : Slice Std.U32) (istart : Slice Std.U32) (l4 : Std.Usize) (co : Std.Usize) (lam : Std.U32) :
    slot.h_pass_items input tbl bpos nb choice items istart l4 co lam ⦃ fun _ => True ⦄ := T15! slot.h_pass_items
@[local step]
theorem find_dist_loop_spec (mc : Slice Std.U32) (l : Std.Usize) (me : Std.Usize) (d : Std.Usize) (k : Std.Usize) :
    slot.h_find_dist_loop mc l me d k ⦃ fun _ => True ⦄ := by
  rw [slot.h_find_dist_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => me.val - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨d1, k1⟩ _
    simp only [slot.h_find_dist_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem find_dist_spec (mstart : Slice Std.U32) (mc : Slice Std.U32) (p : Std.Usize) (l : Std.Usize) :
    slot.h_find_dist mstart mc p l ⦃ fun _ => True ⦄ := T15! slot.h_find_dist
@[local step]
theorem clear_loop_spec (v : Slice Std.U32) (b : Std.Usize) (i : Std.Usize) :
    slot.h_clear_loop v b i ⦃ fun _ => True ⦄ := by
  rw [slot.h_clear_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => b.val - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨v1, i1⟩ _
    simp only [slot.h_clear_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem clear_spec (v : Slice Std.U32) (a : Std.Usize) (b : Std.Usize) :
    slot.h_clear v a b ⦃ fun _ => True ⦄ := T14! slot.h_clear
@[local step]
theorem dist_of_spec (mstart : Slice Std.U32) (mc : Slice Std.U32) (pos : Std.Usize) (len : Std.Usize) (d0 : Std.Usize) :
    slot.h_dist_of mstart mc pos len d0 ⦃ fun _ => True ⦄ := T14! slot.h_dist_of
@[local step]
theorem walk_bump_spec (fr : Slice Std.U32) (off : Std.Usize) (st : Std.Usize) (d : Std.Usize) (b : Std.Usize) :
    slot.h_walk_bump fr off st d b ⦃ fun _ => True ⦄ := T15! slot.h_walk_bump
@[local step]
theorem walk_loop_spec (input : Slice Std.U8) (mstart : Slice Std.U32) (mc : Slice Std.U32) (choice : Slice Std.U32) (co : Std.Usize) (fr : Slice Std.U32) (bpos : Slice Std.U32) (n : Std.Usize) (pos : Std.Usize) (b : Std.Usize) (t : Std.Usize) :
    slot.h_walk_loop input mstart mc choice co fr bpos n pos b t ⦃ fun _ => True ⦄ := by
  rw [slot.h_walk_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => n.val - qq9.2.2.2.1.val)
    (inv := fun _ => True)
  · rintro ⟨choice1, fr1, bpos1, pos1, b1, t1⟩ _
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.h_walk_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem walk_spec (input : Slice Std.U8) (mstart : Slice Std.U32) (mc : Slice Std.U32) (choice : Slice Std.U32) (co : Std.Usize) (fr : Slice Std.U32) (bpos : Slice Std.U32) :
    slot.h_walk input mstart mc choice co fr bpos ⦃ fun _ => True ⦄ := T15! slot.h_walk
@[local step]
theorem insert_sorted_loop_spec (order : Slice Std.U32) (freq : Slice Std.U32) (off : Std.Usize) (fs : Std.U32) (j : Std.Usize) :
    slot.h_insert_sorted_loop order freq off fs j ⦃ fun _ => True ⦄ := by
  rw [slot.h_insert_sorted_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨order1, j1⟩ _
    simp only [slot.h_insert_sorted_loop.body, lift]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem insert_sorted_spec (order : Slice Std.U32) (k : Std.Usize) (s : Std.Usize) (freq : Slice Std.U32) (off : Std.Usize) :
    slot.h_insert_sorted order k s freq off ⦃ fun _ => True ⦄ := T15! slot.h_insert_sorted
set_option hygiene false in
local notation "T16!" q0__:max q1__:max => (by
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
@[local step]
theorem radix_pass_loop0_spec (freq : Slice Std.U32) (off : Std.Usize) (src : Slice Std.U32) (k : Std.Usize) (sh : Std.U32) (cnt : Array Std.U32 256#usize) (i : Std.Usize) :
    slot.h_radix_pass_loop0 freq off src k sh cnt i ⦃ fun _ => True ⦄ := T16! slot.h_radix_pass_loop0 slot.h_radix_pass_loop0.body
@[local step]
theorem radix_pass_loop1_spec (cnt : Array Std.U32 256#usize) (acc : Std.U32) (d : Std.Usize) :
    slot.h_radix_pass_loop1 cnt acc d ⦃ fun _ => True ⦄ := by
  rw [slot.h_radix_pass_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 256 - qq9.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨cnt1, acc1, d1⟩ _
    simp only [slot.h_radix_pass_loop1.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem radix_pass_loop2_spec (freq : Slice Std.U32) (off : Std.Usize) (src : Slice Std.U32) (dst : Slice Std.U32) (k : Std.Usize) (sh : Std.U32) (cnt : Array Std.U32 256#usize) (j : Std.Usize) :
    slot.h_radix_pass_loop2 freq off src dst k sh cnt j ⦃ fun _ => True ⦄ := by
  rw [slot.h_radix_pass_loop2]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 288 - qq9.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨dst1, cnt1, j1⟩ _
    simp only [slot.h_radix_pass_loop2.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem radix_pass_spec (freq : Slice Std.U32) (off : Std.Usize) (src : Slice Std.U32) (dst : Slice Std.U32) (k : Std.Usize) (sh : Std.U32) :
    slot.h_radix_pass freq off src dst k sh ⦃ fun _ => True ⦄ := T14! slot.h_radix_pass
@[local step]
theorem copy32_loop_spec (src : Slice Std.U32) (soff : Std.Usize) (dst : Slice Std.U32) (doff : Std.Usize) (m : Std.Usize) (i : Std.Usize) :
    slot.h_copy32_loop src soff dst doff m i ⦃ fun _ => True ⦄ := by
  rw [slot.h_copy32_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => m.val - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨dst1, i1⟩ _
    simp only [slot.h_copy32_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem copy32_spec (src : Slice Std.U32) (soff : Std.Usize) (dst : Slice Std.U32) (doff : Std.Usize) (m : Std.Usize) :
    slot.h_copy32 src soff dst doff m ⦃ fun _ => True ⦄ := T14! slot.h_copy32
@[local step]
theorem sort_live_loop0_spec (freq : Slice Std.U32) (off : Std.Usize) (nsym : Std.Usize) (tmp : Array Std.U32 288#usize) (k : Std.Usize) (big : Std.Usize) (s : Std.Usize) :
    slot.h_sort_live_loop0 freq off nsym tmp k big s ⦃ fun _ => True ⦄ := by
  rw [slot.h_sort_live_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 288 - qq9.2.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨tmp1, k1, big1, s1⟩ _
    simp only [slot.h_sort_live_loop0.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem sort_live_loop1_spec (freq : Slice Std.U32) (off : Std.Usize) (order : Slice Std.U32) (tmp : Array Std.U32 288#usize) (kb : Std.Usize) (j : Std.Usize) :
    slot.h_sort_live_loop1 freq off order tmp kb j ⦃ fun _ => True ⦄ := by
  rw [slot.h_sort_live_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 288 - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨order1, j1⟩ _
    simp only [slot.h_sort_live_loop1.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem sort_live_spec (freq : Slice Std.U32) (off : Std.Usize) (nsym : Std.Usize) (order : Slice Std.U32) :
    slot.h_sort_live freq off nsym order ⦃ fun _ => True ⦄ := T14! slot.h_sort_live
@[local step]
theorem load_w_loop_spec (freq : Slice Std.U32) (off : Std.Usize) (order : Slice Std.U32) (k : Std.Usize) (wa : Slice Std.U64) (i : Std.Usize) :
    slot.h_load_w_loop freq off order k wa i ⦃ fun _ => True ⦄ := by
  rw [slot.h_load_w_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 288 - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨wa1, i1⟩ _
    simp only [slot.h_load_w_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem load_w_spec (freq : Slice Std.U32) (off : Std.Usize) (order : Slice Std.U32) (k : Std.Usize) (wa : Slice Std.U64) :
    slot.h_load_w freq off order k wa ⦃ fun _ => True ⦄ := T14! slot.h_load_w
@[local step]
theorem pm_level_loop_spec (lw : Array Std.U64 288#usize) (k : Std.Usize) (w : Array Std.U64 1152#usize) (src : Std.Usize) (dst : Std.Usize) (flags : Array Std.U8 9216#usize) (foff : Std.Usize) (npk : Std.Usize) (total : Std.Usize) (a : Std.Usize) (p : Std.Usize) (t : Std.Usize) :
    slot.h_pm_level_loop lw k w src dst flags foff npk total a p t ⦃ fun _ => True ⦄ := by
  rw [slot.h_pm_level_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 576 - qq9.2.2.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨w1, flags1, a1, p1, t1⟩ _
    simp only [slot.h_pm_level_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem pm_level_spec (lw : Array Std.U64 288#usize) (k : Std.Usize) (w : Array Std.U64 1152#usize) (src : Std.Usize) (curlen : Std.Usize) (dst : Std.Usize) (flags : Array Std.U8 9216#usize) (foff : Std.Usize) :
    slot.h_pm_level lw k w src curlen dst flags foff ⦃ fun _ => True ⦄ := T15! slot.h_pm_level
@[local step]
theorem pm_levels_loop_spec (lw : Array Std.U64 288#usize) (k : Std.Usize) (w : Array Std.U64 1152#usize) (flags : Array Std.U8 9216#usize) (maxbits : Std.Usize) (curlen : Std.Usize) (lev : Std.Usize) :
    slot.h_pm_levels_loop lw k w flags maxbits curlen lev ⦃ fun _ => True ⦄ := by
  rw [slot.h_pm_levels_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 16 - qq9.2.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨w1, flags1, curlen1, lev1⟩ _
    simp only [slot.h_pm_levels_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem pm_levels_spec (lw : Array Std.U64 288#usize) (k : Std.Usize) (w : Array Std.U64 1152#usize) (flags : Array Std.U8 9216#usize) (maxbits : Std.Usize) :
    slot.h_pm_levels lw k w flags maxbits ⦃ fun _ => True ⦄ := T14! slot.h_pm_levels
@[local step]
theorem count_leaves_loop_spec (flags : Slice Std.U8) (foff : Std.Usize) (s : Std.Usize) (c : Std.Usize) (i : Std.Usize) :
    slot.h_count_leaves_loop flags foff s c i ⦃ fun _ => True ⦄ := by
  rw [slot.h_count_leaves_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 576 - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨c1, i1⟩ _
    simp only [slot.h_count_leaves_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem count_leaves_spec (flags : Slice Std.U8) (foff : Std.Usize) (s : Std.Usize) :
    slot.h_count_leaves flags foff s ⦃ fun _ => True ⦄ := T14! slot.h_count_leaves
@[local step]
theorem inc_prefix_loop_spec (cnt : Slice Std.U32) (m : Std.Usize) (i : Std.Usize) :
    slot.h_inc_prefix_loop cnt m i ⦃ fun _ => True ⦄ := T16! slot.h_inc_prefix_loop slot.h_inc_prefix_loop.body
@[local step]
theorem inc_prefix_spec (cnt : Slice Std.U32) (m : Std.Usize) :
    slot.h_inc_prefix cnt m ⦃ fun _ => True ⦄ := T14! slot.h_inc_prefix
@[local step]
theorem count_back_loop_spec (flags : Slice Std.U8) (cnt : Slice Std.U32) (s : Std.Usize) (lv : Std.Usize) :
    slot.h_count_back_loop flags cnt s lv ⦃ fun _ => True ⦄ := by
  rw [slot.h_count_back_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => qq9.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨cnt1, s1, lv1⟩ _
    simp only [slot.h_count_back_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem count_back_spec (flags : Slice Std.U8) (cnt : Slice Std.U32) (k : Std.Usize) (maxbits : Std.Usize) :
    slot.h_count_back flags cnt k maxbits ⦃ fun _ => True ⦄ := T15! slot.h_count_back
@[local step]
theorem assign_lens_loop_spec (order : Slice Std.U32) (cnt : Slice Std.U32) (k : Std.Usize) (lens : Slice Std.U32) (loff : Std.Usize) (r : Std.Usize) :
    slot.h_assign_lens_loop order cnt k lens loff r ⦃ fun _ => True ⦄ := by
  rw [slot.h_assign_lens_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 288 - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨lens1, r1⟩ _
    simp only [slot.h_assign_lens_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem assign_lens_spec (order : Slice Std.U32) (cnt : Slice Std.U32) (k : Std.Usize) (lens : Slice Std.U32) (loff : Std.Usize) :
    slot.h_assign_lens order cnt k lens loff ⦃ fun _ => True ⦄ := T14! slot.h_assign_lens
@[local step]
theorem pkg_merge_pm_spec (freq : Slice Std.U32) (off : Std.Usize) (nsym : Std.Usize) (maxbits : Std.Usize) (lens : Slice Std.U32) (loff : Std.Usize) :
    slot.h_pkg_merge_pm freq off nsym maxbits lens loff ⦃ fun _ => True ⦄ := T14! slot.h_pkg_merge_pm
@[local step]
theorem pkg_merge_loop0_spec (freq : Slice Std.U32) (off : Std.Usize) (order : Array Std.U32 288#usize) (k : Std.Usize) (weights : Array Std.U64 576#usize) (i : Std.Usize) :
    slot.h_pkg_merge_loop0 freq off order k weights i ⦃ fun _ => True ⦄ := by
  rw [slot.h_pkg_merge_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 288 - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨weights1, i1⟩ _
    simp only [slot.h_pkg_merge_loop0.body]
    try simp only [lift, ite_ok, alloc.vec.Vec.deref_mut, bind_tc_ok]
    step*
    all_goals repeat (first
      | (split <;> (try step*))
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply spec_ite_cut <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals scalar_tac
  · trivial
@[local step]
theorem pkg_merge_loop1_loop0_spec (k : Std.Usize) (weights : Array Std.U64 576#usize) (parent : Array Std.U32 576#usize) (leaf : Std.Usize) (pair : Std.Usize) (next : Std.Usize) (sum : Std.U64) (j : Std.Usize) :
    slot.h_pkg_merge_loop1_loop0 k weights parent leaf pair next sum j ⦃ fun _ => True ⦄ := by
  rw [slot.h_pkg_merge_loop1_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 2 - qq9.2.2.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨parent1, leaf1, pair1, sum1, j1⟩ _
    simp only [slot.h_pkg_merge_loop1_loop0.body]
    try simp only [lift, ite_ok, alloc.vec.Vec.deref_mut, bind_tc_ok]
    step*
    all_goals repeat (first
      | (split <;> (try step*))
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply spec_ite_cut <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals scalar_tac
  · trivial
@[local step]
theorem pkg_merge_loop1_spec (k : Std.Usize) (weights : Array Std.U64 576#usize) (parent : Array Std.U32 576#usize) (leaf : Std.Usize) (pair : Std.Usize) (next : Std.Usize) :
    slot.h_pkg_merge_loop1 k weights parent leaf pair next ⦃ fun _ => True ⦄ := by
  rw [slot.h_pkg_merge_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 575 - qq9.2.2.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨weights1, parent1, leaf1, pair1, next1⟩ _
    simp only [slot.h_pkg_merge_loop1.body]
    try simp only [lift, ite_ok, alloc.vec.Vec.deref_mut, bind_tc_ok]
    step*
    all_goals repeat (first
      | (split <;> (try step*))
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply spec_ite_cut <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals scalar_tac
  · trivial
@[local step]
theorem pkg_merge_loop2_spec (parent : Array Std.U32 576#usize) (depth : Array Std.U32 576#usize) (mx : Std.Usize) (node : Std.Usize) :
    slot.h_pkg_merge_loop2 parent depth mx node ⦃ fun _ => True ⦄ := by
  rw [slot.h_pkg_merge_loop2]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => qq9.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨depth1, mx1, node1⟩ _
    simp only [slot.h_pkg_merge_loop2.body]
    try simp only [lift, ite_ok, alloc.vec.Vec.deref_mut, bind_tc_ok]
    step*
    all_goals repeat (first
      | (split <;> (try step*))
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply spec_ite_cut <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals scalar_tac
  · trivial
@[local step]
theorem pkg_merge_loop3_spec (lens : Slice Std.U32) (loff : Std.Usize) (order : Array Std.U32 288#usize) (k : Std.Usize) (depth : Array Std.U32 576#usize) (r : Std.Usize) :
    slot.h_pkg_merge_loop3 lens loff order k depth r ⦃ fun _ => True ⦄ := by
  rw [slot.h_pkg_merge_loop3]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 288 - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨lens1, r1⟩ _
    simp only [slot.h_pkg_merge_loop3.body]
    try simp only [lift, ite_ok, alloc.vec.Vec.deref_mut, bind_tc_ok]
    step*
    all_goals repeat (first
      | (split <;> (try step*))
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply spec_ite_cut <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals scalar_tac
  · trivial
@[local step]
theorem pkg_merge_spec (freq : Slice Std.U32) (off : Std.Usize) (nsym : Std.Usize) (maxbits : Std.Usize) (lens : Slice Std.U32) (loff : Std.Usize) :
    slot.h_pkg_merge freq off nsym maxbits lens loff ⦃ fun _ => True ⦄ := by
  rw [slot.h_pkg_merge]
  step*
  simp only [lift, bind_tc_ok]
  step*
  all_goals (repeat (split <;> try step*))
  all_goals scalar_tac
@[local step]
theorem run_len_loop_spec (all : Slice Std.U32) (i : Std.Usize) (m : Std.Usize) (v : Std.U32) (r : Std.Usize) :
    slot.h_run_len_loop all i m v r ⦃ fun _ => True ⦄ := by
  rw [slot.h_run_len_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 1000 - qq9.val)
    (inv := fun _ => True)
  · rintro r1 _
    simp only [slot.h_run_len_loop.body, lift]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem run_len_spec (all : Slice Std.U32) (i : Std.Usize) (m : Std.Usize) :
    slot.h_run_len all i m ⦃ fun _ => True ⦄ := T14! slot.h_run_len
@[local step]
theorem rle_stats_loop_spec (all : Slice Std.U32) (m : Std.Usize) (clf : Slice Std.U32) (extra : Std.U64) (i : Std.Usize) :
    slot.h_rle_stats_loop all m clf extra i ⦃ fun _ => True ⦄ := by
  rw [slot.h_rle_stats_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => m.val - qq9.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨clf1, extra1, i1⟩ _
    simp only [slot.h_rle_stats_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem rle_stats_spec (all : Slice Std.U32) (m : Std.Usize) (clf : Slice Std.U32) :
    slot.h_rle_stats all m clf ⦃ fun _ => True ⦄ := T14! slot.h_rle_stats
@[local step]
theorem dot_loop_spec (f : Slice Std.U32) (foff : Std.Usize) (l : Slice Std.U32) (loff : Std.Usize) (m : Std.Usize) (s : Std.U64) (i : Std.Usize) :
    slot.h_dot_loop f foff l loff m s i ⦃ fun _ => True ⦄ := by
  rw [slot.h_dot_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => m.val - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨s1, i1⟩ _
    simp only [slot.h_dot_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem dot_spec (f : Slice Std.U32) (foff : Std.Usize) (l : Slice Std.U32) (loff : Std.Usize) (m : Std.Usize) :
    slot.h_dot f foff l loff m ⦃ fun _ => True ⦄ := T14! slot.h_dot
@[local step]
theorem fixed_dot_loop_spec (f : Slice Std.U32) (foff : Std.Usize) (s : Std.U64) (i : Std.Usize) :
    slot.h_fixed_dot_loop f foff s i ⦃ fun _ => True ⦄ := by
  rw [slot.h_fixed_dot_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 288 - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨s1, i1⟩ _
    simp only [slot.h_fixed_dot_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem fixed_dot_spec (f : Slice Std.U32) (foff : Std.Usize) :
    slot.h_fixed_dot f foff ⦃ fun _ => True ⦄ := T14! slot.h_fixed_dot
@[local step]
theorem sum_range_loop_spec (f : Slice Std.U32) (b : Std.Usize) (s : Std.U64) (i : Std.Usize) :
    slot.h_sum_range_loop f b s i ⦃ fun _ => True ⦄ := by
  rw [slot.h_sum_range_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => b.val - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨s1, i1⟩ _
    simp only [slot.h_sum_range_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem sum_range_spec (f : Slice Std.U32) (a : Std.Usize) (b : Std.Usize) :
    slot.h_sum_range f a b ⦃ fun _ => True ⦄ := T14! slot.h_sum_range
@[local step]
theorem last_nz_loop_spec (l : Slice Std.U32) (off : Std.Usize) (lo : Std.Usize) (k : Std.Usize) :
    slot.h_last_nz_loop l off lo k ⦃ fun _ => True ⦄ := by
  rw [slot.h_last_nz_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => qq9.val)
    (inv := fun _ => True)
  · rintro k1 _
    simp only [slot.h_last_nz_loop.body, lift]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem last_nz_spec (l : Slice Std.U32) (off : Std.Usize) (m : Std.Usize) (lo : Std.Usize) :
    slot.h_last_nz l off m lo ⦃ fun _ => True ⦄ := T14! slot.h_last_nz
@[local step]
theorem hclen_of_loop_spec (cl : Slice Std.U32) (h : Std.Usize) :
    slot.h_hclen_of_loop cl h ⦃ fun _ => True ⦄ := by
  rw [slot.h_hclen_of_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => qq9.val)
    (inv := fun _ => True)
  · rintro h1 _
    simp only [slot.h_hclen_of_loop.body, lift]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem hclen_of_spec (cl : Slice Std.U32) :
    slot.h_hclen_of cl ⦃ fun _ => True ⦄ := T14! slot.h_hclen_of
@[local step]
theorem block_bits_spec (fr : Slice Std.U32) (off : Std.Usize) (lens : Slice Std.U32) :
    slot.h_block_bits fr off lens ⦃ fun _ => True ⦄ := T14! slot.h_block_bits
@[local step]
theorem log2x16_spec (x : Std.U64) :
    slot.h_log2x16 x ⦃ fun _ => True ⦄ := T15! slot.h_log2x16
set_option hygiene false in
local notation "T17!" q0__:max q1__:max => (by
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
@[local step]
theorem sym_costs_loop_spec (fr : Slice Std.U32) (off : Std.Usize) (lens : Slice Std.U32) (kind : Std.U32) (sc : Slice Std.U32) (lt1 : Std.U32) (ld : Std.U32) (s : Std.Usize) :
    slot.h_sym_costs_loop fr off lens kind sc lt1 ld s ⦃ fun _ => True ⦄ := T17! slot.h_sym_costs_loop slot.h_sym_costs_loop.body
@[local step]
theorem sym_costs_spec (fr : Slice Std.U32) (off : Std.Usize) (lens : Slice Std.U32) (kind : Std.U32) (sc : Slice Std.U32) :
    slot.h_sym_costs fr off lens kind sc ⦃ fun _ => True ⦄ := T15! slot.h_sym_costs
@[local step]
theorem mode_ov_spec (damp : Std.U32) : slot.h_mode_ov damp ⦃ fun _ => True ⦄ := by
  rw [slot.h_mode_ov]; repeat (first | (split <;> step*) | scalar_tac)
@[local step]
theorem blend_spec (old : Std.U32) (new : Std.U32) (damp : Std.U32) :
    slot.h_blend old new damp ⦃ fun _ => True ⦄ := T15! slot.h_blend
set_option hygiene false in
local notation "T18!" q0__:max q1__:max => (by
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
@[local step]
theorem fill_table_loop0_spec (sc : Slice Std.U32) (tbl : Slice Std.U32) (toff : Std.Usize) (damp : Std.U32) (c : Std.Usize) :
    slot.h_fill_table_loop0 sc tbl toff damp c ⦃ fun _ => True ⦄ := T18! slot.h_fill_table_loop0 slot.h_fill_table_loop0.body
set_option hygiene false in
local notation "T19!" q0__:max q1__:max => (by
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
@[local step]
theorem fill_table_loop1_spec (sc : Slice Std.U32) (tbl : Slice Std.U32) (toff : Std.Usize) (damp : Std.U32) (len : Std.Usize) :
    slot.h_fill_table_loop1 sc tbl toff damp len ⦃ fun _ => True ⦄ := T19! slot.h_fill_table_loop1 slot.h_fill_table_loop1.body
set_option hygiene false in
local notation "T20!" q0__:max q1__:max => (by
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
@[local step]
theorem fill_table_loop2_spec (sc : Slice Std.U32) (tbl : Slice Std.U32) (toff : Std.Usize) (damp : Std.U32) (s : Std.Usize) :
    slot.h_fill_table_loop2 sc tbl toff damp s ⦃ fun _ => True ⦄ := T20! slot.h_fill_table_loop2 slot.h_fill_table_loop2.body
@[local step]
theorem fill_table_spec (sc : Slice Std.U32) (tbl : Slice Std.U32) (toff : Std.Usize) (damp : Std.U32) :
    slot.h_fill_table sc tbl toff damp ⦃ fun _ => True ⦄ := T14! slot.h_fill_table
@[local step]
theorem longest_spec (mstart : Slice Std.U32) (mc : Slice Std.U32) (p : Std.Usize) :
    slot.h_longest mstart mc p ⦃ fun _ => True ⦄ := T15! slot.h_longest
@[local step]
theorem block_hist_loop_spec (input : Slice Std.U8) (b : Std.Usize) (fr : Slice Std.U32) (i : Std.Usize) :
    slot.h_block_hist_loop input b fr i ⦃ fun _ => True ⦄ := by
  rw [slot.h_block_hist_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => b.val - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨fr1, i1⟩ _
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.h_block_hist_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem block_hist_spec (input : Slice Std.U8) (a : Std.Usize) (b : Std.Usize) (fr : Slice Std.U32) :
    slot.h_block_hist input a b fr ⦃ fun _ => True ⦄ := T14! slot.h_block_hist
@[local step]
theorem add_hist_loop_spec (fr : Slice Std.U32) (hist : Array Std.U32 256#usize) (c : Std.Usize) :
    slot.h_add_hist_loop fr hist c ⦃ fun _ => True ⦄ := by
  rw [slot.h_add_hist_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 256 - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨hist1, c1⟩ _
    simp only [slot.h_add_hist_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem add_hist_spec (fr : Slice Std.U32) (hist : Array Std.U32 256#usize) :
    slot.h_add_hist fr hist ⦃ fun _ => True ⦄ := T14! slot.h_add_hist
@[local step]
theorem block_bits_if_spec (fr : Slice Std.U32) (lens : Slice Std.U32) (f : Std.Usize) :
    slot.h_block_bits_if fr lens f ⦃ fun _ => True ⦄ := T14! slot.h_block_bits_if
@[local step]
theorem st5len_spec (len : Std.Usize) :
    slot.h_st5len len ⦃ fun _ => True ⦄ := T15! slot.h_st5len
@[local step]
theorem ent5_spec (lt1 : Std.U32) (f : Std.U64) :
    slot.h_ent5 lt1 f ⦃ fun _ => True ⦄ := T14! slot.h_ent5
@[local step]
theorem init5_table_loop0_spec (fr : Slice Std.U32) (tbl : Slice Std.U32) (toff : Std.Usize) (lt1 : Std.U32) (c : Std.Usize) :
    slot.h_init5_table_loop0 fr tbl toff lt1 c ⦃ fun _ => True ⦄ := T18! slot.h_init5_table_loop0 slot.h_init5_table_loop0.body
@[local step]
theorem init5_table_loop1_spec (tbl : Slice Std.U32) (toff : Std.Usize) (len : Std.Usize) :
    slot.h_init5_table_loop1 tbl toff len ⦃ fun _ => True ⦄ := T19! slot.h_init5_table_loop1 slot.h_init5_table_loop1.body
@[local step]
theorem init5_table_loop2_spec (tbl : Slice Std.U32) (toff : Std.Usize) (s : Std.Usize) :
    slot.h_init5_table_loop2 tbl toff s ⦃ fun _ => True ⦄ := T20! slot.h_init5_table_loop2 slot.h_init5_table_loop2.body
@[local step]
theorem init5_table_spec (fr : Slice Std.U32) (tbl : Slice Std.U32) (toff : Std.Usize) :
    slot.h_init5_table fr tbl toff ⦃ fun _ => True ⦄ := T15! slot.h_init5_table
@[local step]
theorem literal_bits_loop_spec (input : Slice Std.U8) (fr : Slice Std.U32) (hist : Array Std.U32 256#usize) (tlit : Slice Std.U32) (t5 : Slice Std.U32) (n : Std.Usize) (lens : Array Std.U32 320#usize) (sc : Array Std.U32 320#usize) (total : Std.U64) (nblk : Std.Usize) (b : Std.Usize) :
    slot.h_literal_bits_loop input fr hist tlit t5 n lens sc total nblk b ⦃ fun _ => True ⦄ := by
  rw [slot.h_literal_bits_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => nblk.val - qq9.2.2.2.2.2.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨fr1, hist1, tlit1, t51, lens1, sc1, total1, b1⟩ _
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.h_literal_bits_loop.body, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem literal_bits_spec (input : Slice Std.U8) (fr : Slice Std.U32) (hist : Array Std.U32 256#usize) (tlit : Slice Std.U32) (t5 : Slice Std.U32) :
    slot.h_literal_bits input fr hist tlit t5 ⦃ fun _ => True ⦄ := T14! slot.h_literal_bits
@[local step]
theorem avg_lit16_h_spec (hist : Array Std.U32 256#usize) (n : Std.Usize) :
    slot.h_avg_lit16_h hist n ⦃ fun _ => True ⦄ := T14! slot.h_avg_lit16_h
@[local step]
theorem est_match16_spec (l : Std.Usize) (d : Std.Usize) :
    slot.h_est_match16 l d ⦃ fun _ => True ⦄ := T15! slot.h_est_match16
@[local step]
theorem est_if_spec (f : Std.Usize) (l : Std.Usize) (d : Std.Usize) :
    slot.h_est_if f l d ⦃ fun _ => True ⦄ := T14! slot.h_est_if
@[local step]
theorem next_longest_spec (mstart : Slice Std.U32) (mc : Slice Std.U32) (pos : Std.Usize) (st : Std.Usize) (b : Std.Usize) :
    slot.h_next_longest mstart mc pos st b ⦃ fun _ => True ⦄ := T15! slot.h_next_longest
@[local step]
theorem lazy_cost_init_loop_spec (mstart : Slice Std.U32) (mc : Slice Std.U32) (h16 : Std.U32) (choice : Slice Std.U32) (n : Std.Usize) (pos : Std.Usize) (nxt : Std.Usize) (ec : Std.U32) (hv : Std.Usize) :
    slot.h_lazy_cost_init_loop mstart mc h16 choice n pos nxt ec hv ⦃ fun _ => True ⦄ := by
  rw [slot.h_lazy_cost_init_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => n.val - qq9.2.1.val)
    (inv := fun _ => True)
  · rintro ⟨choice1, pos1, nxt1, ec1, hv1⟩ _
    simp only [slot.h_lazy_cost_init_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem lazy_cost_init_spec (input : Slice Std.U8) (mstart : Slice Std.U32) (mc : Slice Std.U32) (h16 : Std.U32) (choice : Slice Std.U32) :
    slot.h_lazy_cost_init input mstart mc h16 choice ⦃ fun _ => True ⦄ := T14! slot.h_lazy_cost_init
@[local step]
theorem forbid_block_loop_spec (tbl : Slice Std.U32) (toff : Std.Usize) (len : Std.Usize) :
    slot.h_forbid_block_loop tbl toff len ⦃ fun _ => True ⦄ := T19! slot.h_forbid_block_loop slot.h_forbid_block_loop.body
@[local step]
theorem forbid_block_spec (tbl : Slice Std.U32) (toff : Std.Usize) :
    slot.h_forbid_block tbl toff ⦃ fun _ => True ⦄ := T14! slot.h_forbid_block
@[local step]
theorem forbid_if_spec (tbl : Slice Std.U32) (toff : Std.Usize) (f : Std.Usize) :
    slot.h_forbid_if tbl toff f ⦃ fun _ => True ⦄ := T14! slot.h_forbid_if
set_option hygiene false in
local notation "T21!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => lim.val - qq9.2.2.2.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨fr1, tbl1, lens1, sc1, total1, b1⟩ _
    simp only [q1__, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial)
@[local step]
theorem eval_blocks_loop_spec (fr : Slice Std.U32) (tbl : Slice Std.U32) (damp : Std.U32) (lens : Array Std.U32 320#usize) (sc : Array Std.U32 320#usize) (total : Std.U64) (lim : Std.Usize) (b : Std.Usize) :
    slot.h_eval_blocks_loop fr tbl damp lens sc total lim b ⦃ fun _ => True ⦄ := T21! slot.h_eval_blocks_loop slot.h_eval_blocks_loop.body
@[local step]
theorem eval_blocks_spec (fr : Slice Std.U32) (tbl : Slice Std.U32) (nb2 : Std.Usize) (nbmax : Std.Usize) (damp : Std.U32) :
    slot.h_eval_blocks fr tbl nb2 nbmax damp ⦃ fun _ => True ⦄ := T14! slot.h_eval_blocks
@[local step]
theorem dp_pass_spec (input : Slice Std.U8) (mstart : Slice Std.U32) (mc : Slice Std.U32) (tbl : Slice Std.U32) (bend : Array Std.U32 512#usize) (bpos : Slice Std.U32) (nb : Std.Usize) (choice : Slice Std.U32) (chw : Std.Usize) (keep : Std.Usize) (items : alloc.vec.Vec Std.U32) (istart : alloc.vec.Vec Std.U32) (pr : Std.Usize) (msub : Std.U32) (co : Std.Usize) (lam : Std.U32) :
    slot.h_dp_pass input mstart mc tbl bend bpos nb choice chw keep items istart pr msub co lam ⦃ fun _ => True ⦄ := T14! slot.h_dp_pass
@[local step]
theorem stop_rule_spec (prev : Std.U64) (r : Std.U64) (n : Std.Usize) (it1 : Std.Usize) (gk : Std.U64) (minp : Std.Usize) :
    slot.h_stop_rule prev r n it1 gk minp ⦃ fun _ => True ⦄ := T15! slot.h_stop_rule
@[local step]
theorem one_pass_spec (prev : Std.U64) (n : Std.Usize) (gk : Std.U64) :
    slot.h_one_pass prev n gk ⦃ fun _ => True ⦄ := T15! slot.h_one_pass
@[local step]
theorem mode_damp_spec (mode : Std.Usize) (damp : Std.U32) : slot.h_mode_damp mode damp ⦃ fun _ => True ⦄ := by
  rw [slot.h_mode_damp]; repeat (first | (split <;> step*) | scalar_tac)
@[local step]
theorem eval_mode_spec (mode : Std.Usize) (fr tbl : Slice Std.U32) (nb nbmax : Std.Usize) (damp ew : Std.U32) :
    slot.h_eval_mode mode fr tbl nb nbmax damp ew ⦃ fun _ => True ⦄ := by
  rw [slot.h_eval_mode]
  step*
@[local step]
theorem lg8_spec (x : Std.U32) :
    slot.h_lg8 x ⦃ fun _ => True ⦄ := T15! slot.h_lg8
@[local step]
theorem entropy256_loop_spec (h : Array Std.U32 256#usize) (tot : Std.U64) (acc : Std.U64) (i : Std.Usize) :
    slot.h_entropy256_loop h tot acc i ⦃ fun _ => True ⦄ := by
  rw [slot.h_entropy256_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 256 - qq9.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨tot1, acc1, i1⟩ _
    simp only [slot.h_entropy256_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem entropy256_spec (h : Array Std.U32 256#usize) :
    slot.h_entropy256 h ⦃ fun _ => True ⦄ := T14! slot.h_entropy256
@[local step]
theorem hash12_spec (input : Slice Std.U8) (p : Std.Usize) :
    slot.h_hash12 input p ⦃ fun _ => True ⦄ := T15! slot.h_hash12
@[local step]
theorem probe_win_loop_spec (input : Slice Std.U8) (ht : Array Std.U32 4096#usize) (s : Std.Usize) (e : Std.Usize) (n : Std.Usize) (i : Std.Usize) (cov : Std.U64) (nm : Std.U64) (it : Std.Usize) :
    slot.h_probe_win_loop input ht s e n i cov nm it ⦃ fun _ => True ⦄ := by
  rw [slot.h_probe_win_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => slot.H_PR_W.val - qq9.2.2.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨ht1, i1, cov1, nm1, it1⟩ _
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.h_probe_win_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem probe_win_spec (input : Slice Std.U8) (ht : Array Std.U32 4096#usize) (s : Std.Usize) (e : Std.Usize) :
    slot.h_probe_win input ht s e ⦃ fun _ => True ⦄ := T15! slot.h_probe_win
@[local step]
theorem probe_all_loop_spec (input : Slice Std.U8) (ht : Array Std.U32 4096#usize) (span : Std.Usize) (acc : Std.U64) (k : Std.Usize) :
    slot.h_probe_all_loop input ht span acc k ⦃ fun _ => True ⦄ := by
  rw [slot.h_probe_all_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => slot.H_PR_N.val - qq9.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨ht1, acc1, k1⟩ _
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.h_probe_all_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem probe_all_spec (input : Slice Std.U8) :
    slot.h_probe_all input ⦃ fun _ => True ⦄ := T15! slot.h_probe_all
@[local step]
theorem probe_if_spec (input : Slice Std.U8) (f : Std.Usize) :
    slot.h_probe_if input f ⦃ fun _ => True ⦄ := T14! slot.h_probe_if
@[local step]
theorem odd_sample_loop_spec (input : Slice Std.U8) (h : Array Std.U32 256#usize) (n : Std.Usize) (st : Std.Usize) (k : Std.Usize) (c : Std.Usize) :
    slot.h_odd_sample_loop input h n st k c ⦃ fun _ => True ⦄ := by
  rw [slot.h_odd_sample_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 8192 - qq9.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨h1, k1, c1⟩ _
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.h_odd_sample_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem odd_sample_spec (input : Slice Std.U8) (h : Array Std.U32 256#usize) :
    slot.h_odd_sample input h ⦃ fun _ => True ⦄ := T15! slot.h_odd_sample
@[local step]
theorem ge64_spec (a : Std.U64) (b : Std.U64) :
    slot.h_ge64 a b ⦃ fun _ => True ⦄ := T14! slot.h_ge64
@[local step]
theorem byte_classes_loop_spec (h : Array Std.U32 256#usize) (tot : Std.U64) (ctl : Std.U64) (hib : Std.U64) (i : Std.Usize) :
    slot.h_byte_classes_loop h tot ctl hib i ⦃ fun _ => True ⦄ := by
  rw [slot.h_byte_classes_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 256 - qq9.2.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨tot1, ctl1, hib1, i1⟩ _
    simp only [slot.h_byte_classes_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem byte_classes_spec (h : Array Std.U32 256#usize) :
    slot.h_byte_classes h ⦃ fun _ => True ⦄ := T15! slot.h_byte_classes
@[local step]
theorem byte_classes2_loop_spec (h : Array Std.U32 256#usize) (z0 : Std.U64) (dig : Std.U64) (nz : Std.U64) (i : Std.Usize) :
    slot.h_byte_classes2_loop h z0 dig nz i ⦃ fun _ => True ⦄ := by
  rw [slot.h_byte_classes2_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 256 - qq9.2.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨z01, dig1, nz1, i1⟩ _
    simp only [slot.h_byte_classes2_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem byte_classes2_spec (h : Array Std.U32 256#usize) :
    slot.h_byte_classes2 h ⦃ fun _ => True ⦄ := T15! slot.h_byte_classes2
@[local step]
theorem classify_spec (input : Slice Std.U8) :
    slot.h_classify input ⦃ fun _ => True ⦄ := T15! slot.h_classify
@[local step]
theorem cx_jitter_loop0_loop0_spec (tbl : Slice Std.U32) (seed : Std.U32) (amp : Std.U32) (off : Std.Usize) (s : Std.Usize) (hamp : amp.val < 33) :
    slot.h_cx_jitter_loop0_loop0 tbl seed amp off s ⦃ fun _ => True ⦄ := by
  rw [slot.h_cx_jitter_loop0_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 545 - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨tbl1, s1⟩ _
    simp only [slot.h_cx_jitter_loop0_loop0.body]
    try simp only [lift, ite_ok, alloc.vec.Vec.deref_mut, bind_tc_ok]
    step*
    all_goals repeat (first
      | (split <;> (try step*))
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply spec_ite_cut <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals scalar_tac
  · trivial
@[local step]
theorem cx_jitter_loop0_spec (tbl : Slice Std.U32) (nb : Std.Usize) (seed : Std.U32) (amp : Std.U32) (b : Std.Usize) (hamp : amp.val < 33) :
    slot.h_cx_jitter_loop0 tbl nb seed amp b ⦃ fun _ => True ⦄ := by
  rw [slot.h_cx_jitter_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => nb.val - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨tbl1, b1⟩ _
    simp only [slot.h_cx_jitter_loop0.body]
    try simp only [lift, ite_ok, alloc.vec.Vec.deref_mut, bind_tc_ok]
    step*
    all_goals repeat (first
      | (split <;> (try step*))
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply spec_ite_cut <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals scalar_tac
  · trivial
set_option hygiene false in
local notation "T22!" q0__:max => (by
  rw [q0__]
  try simp only [lift, ite_ok, alloc.vec.Vec.deref_mut, bind_tc_ok]
  step*
  all_goals repeat (first
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals scalar_tac)
@[local step]
theorem cx_jitter_spec (tbl : Slice Std.U32) (nb : Std.Usize) (seed : Std.U32) (amplitude : Std.U32) :
    slot.h_cx_jitter tbl nb seed amplitude ⦃ fun _ => True ⦄ := T22! slot.h_cx_jitter
@[local step]
theorem cx_restarts_loop0_loop0_spec (input : Slice Std.U8) (mstart : Slice Std.U32) (mc : Slice Std.U32)
  (tbl : Slice Std.U32) (fr : Slice Std.U32) (bpos : Slice Std.U32)
  (bend : Array Std.U32 512#usize) (choice : Slice Std.U32)
  (plan : Slice Std.U32) (nbmax : Std.Usize) (lamh : Std.U32)
  (items : alloc.vec.Vec Std.U32) (istart : alloc.vec.Vec Std.U32)
  (pr : Std.Usize) (chw : Std.Usize) (n : Std.Usize) (nbc : Std.Usize)
  (bestp : Std.U64) (step : Std.Usize) :
    slot.h_cx_restarts_loop0_loop0 input mstart mc tbl fr bpos bend choice plan nbmax lamh items istart pr chw n nbc bestp step ⦃ fun _ => True ⦄ := by
  rw [slot.h_cx_restarts_loop0_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun s => 3 - s.2.2.2.2.2.2.2.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨tbl1, fr1, bpos1, choice1, plan1, items1, istart1, nbc1, bestp1, step1⟩ _
    simp only [slot.h_cx_restarts_loop0_loop0.body, lift, ite_ok]
    step*
    all_goals (repeat (split <;> step*))
    all_goals scalar_tac
  · trivial
@[local step]
theorem cx_restarts_loop0_spec (input : Slice Std.U8) (mstart : Slice Std.U32) (mc : Slice Std.U32)
  (tbl : Slice Std.U32) (fr : Slice Std.U32) (bpos : Slice Std.U32)
  (bend : Array Std.U32 512#usize) (choice : Slice Std.U32)
  (plan : Slice Std.U32) (nbmax : Std.Usize) (lamh : Std.U32)
  (items : alloc.vec.Vec Std.U32) (istart : alloc.vec.Vec Std.U32)
  (pr : Std.Usize) (chw : Std.Usize) (restarts : Std.Usize) (n : Std.Usize)
  (jitteron : Std.Usize) (restart : Std.Usize) :
    slot.h_cx_restarts_loop0 input mstart mc tbl fr bpos bend choice plan nbmax lamh items istart pr chw restarts n jitteron restart ⦃ fun _ => True ⦄ := by
  rw [slot.h_cx_restarts_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun s => restarts.val - s.2.2.2.2.2.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨tbl1, fr1, bpos1, choice1, plan1, items1, istart1, restart1⟩ _
    simp only [slot.h_cx_restarts_loop0.body, lift, ite_ok]
    step*
    all_goals (repeat (split <;> step*))
    all_goals scalar_tac
  · trivial
@[local step]
theorem cx_restarts_spec (input : Slice Std.U8) (mstart : Slice Std.U32) (mc : Slice Std.U32)
  (tbl : Slice Std.U32) (fr : Slice Std.U32) (bpos : Slice Std.U32)
  (bend : Array Std.U32 512#usize) (choice : Slice Std.U32)
  (plan : Slice Std.U32) (nbmax : Std.Usize) (lamh : Std.U32)
  (items : alloc.vec.Vec Std.U32) (istart : alloc.vec.Vec Std.U32)
  (pr : Std.Usize) (chw : Std.Usize) (restarts : Std.Usize) :
    slot.h_cx_restarts input mstart mc tbl fr bpos bend choice plan nbmax lamh items istart pr chw restarts ⦃ fun _ => True ⦄ := by
  rw [slot.h_cx_restarts]
  try simp only [lift, ite_ok, alloc.vec.Vec.deref_mut, bind_tc_ok]
  step*
  all_goals (repeat (split <;> step*))
  all_goals scalar_tac
@[local step]
theorem iterate_loop_spec (mode : Std.Usize) (input : Slice Std.U8) (mstart : Slice Std.U32) (mc : Slice Std.U32) (tbl : Slice Std.U32) (fr : Slice Std.U32) (bpos : Slice Std.U32) (bend : Array Std.U32 512#usize) (choice : Slice Std.U32) (nbmax : Std.Usize) (gk : Std.U64) (lamh : Std.U32) (minp : Std.Usize) (ew : Std.U32) (n : Std.Usize) (nb : Std.Usize) (best : Std.U64) (prev : Std.U64) (stop : Std.Usize) (it : Std.Usize) (items : alloc.vec.Vec Std.U32) (istart : alloc.vec.Vec Std.U32) (kp0 : Std.Usize) (pr : Std.Usize) (wh : Std.Usize) (bh : Std.Usize) (chw : Std.Usize) :
    slot.h_iterate_loop mode input mstart mc tbl fr bpos bend choice nbmax gk lamh minp ew n nb best prev stop it items istart kp0 pr wh bh chw ⦃ fun _ => True ⦄ := by
  rw [slot.h_iterate_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => slot.H_ITERS.val - qq9.2.2.2.2.2.2.2.2.1.val)
    (inv := fun _ => True)
  · rintro ⟨tbl1, fr1, bpos1, choice1, nb1, best1, prev1, stop1, it1, items1, istart1, pr1, wh1, bh1⟩ _
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.h_iterate_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem iterate_spec (mode : Std.Usize) (input : Slice Std.U8) (mstart : Slice Std.U32) (mc : Slice Std.U32) (tbl : Slice Std.U32) (fr : Slice Std.U32) (bpos : Slice Std.U32) (bend : Array Std.U32 512#usize) (choice : Slice Std.U32) (plan : Slice Std.U32) (nbmax : Std.Usize) (nb0 : Std.Usize) (best0 : Std.U64) (prev0 : Std.U64) (gk : Std.U64) (lamh : Std.U32) (minp : Std.Usize) (ew : Std.U32) :
    slot.h_iterate mode input mstart mc tbl fr bpos bend choice plan nbmax nb0 best0 prev0 gk lamh minp ew ⦃ fun _ => True ⦄ := T15! slot.h_iterate
@[local step]
theorem lit_bpos_loop_spec (bpos : Slice Std.U32) (m : Std.Usize) (b : Std.Usize) :
    slot.h_lit_bpos_loop bpos m b ⦃ fun _ => True ⦄ := by
  rw [slot.h_lit_bpos_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => m.val - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨bpos1, b1⟩ _
    simp only [slot.h_lit_bpos_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem lit_bpos_spec (bpos : Slice Std.U32) (m : Std.Usize) :
    slot.h_lit_bpos bpos m ⦃ fun _ => True ⦄ := T14! slot.h_lit_bpos
@[local step]
theorem optimize_spec (mode : Std.Usize) (input : Slice Std.U8) (mstart : Slice Std.U32) (mc : Slice Std.U32) (tbl : Slice Std.U32) (fr : Slice Std.U32) (bpos : Slice Std.U32) (bend : Array Std.U32 512#usize) (choice : Slice Std.U32) (plan : Slice Std.U32) (nbmax : Std.Usize) (gk : Std.U64) (i5 : Std.Usize) :
    slot.h_optimize mode input mstart mc tbl fr bpos bend choice plan nbmax gk i5 ⦃ fun _ => True ⦄ := T15! slot.h_optimize
set_option hygiene false in
local notation "T23!" q0__:max => (by
  rw [q0__]
  try simp only [ite_ok]
  step*
  repeat (first
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals scalar_tac)
set_option hygiene false in
local notation "T24!" q0__:max => (by
  rw [q0__]
  simp only [lift, ite_ok, alloc.vec.Vec.deref_mut, bind_tc_ok]
  step*
  repeat (first
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals scalar_tac)
set_option hygiene false in
local notation "T25!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 512 - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨dst1, i1⟩ _
    simp only [q1__, lift, ite_ok]
    step*
    repeat (first
      | (split <;> (try step*))
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
local notation "T26!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 32 - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨dst1, i1⟩ _
    simp only [q1__, lift, ite_ok]
    step*
    repeat (first
      | (split <;> (try step*))
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
local notation "T27!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => nb.val - qq9.val)
    (inv := fun b => b.val < Std.Usize.max)
  · rintro b1 hb1
    simp only [q1__]
    try simp only [lift, ite_ok, alloc.vec.Vec.deref_mut, bind_tc_ok]
    step*
    all_goals repeat (first
      | (split <;> (try step*))
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply spec_ite_cut <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals (split_ifs at * <;> simp_all <;> scalar_tac)
  · exact hb)
set_option hygiene false in
local notation "T28!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 32768 - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨ed1, e1⟩ _
    simp only [q1__]
    try simp only [lift, ite_ok, alloc.vec.Vec.deref_mut, bind_tc_ok]
    step*
    all_goals repeat (first
      | (split <;> (try step*))
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
local notation "T29!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => starts.length - qq9.2.2.2.2.2.2.2.2.2.1.val)
    (inv := fun s => s.2.2.2.2.2.2.2.2.2.2.val < Std.Usize.max)
  · rintro ⟨cand1, arr1, ed1, llf1, df1, litc1, lcost1, dcs1, dcb1, j1, b1⟩ hb1
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    have hstarts : starts.length ≤ Std.Usize.max := Std.Slice.length_ineq starts
    simp only [q1__]
    try simp only [lift, ite_ok, alloc.vec.Vec.deref_mut, bind_tc_ok]
    step*
    all_goals repeat (first
      | (split <;> (try step*))
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply spec_ite_cut <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals scalar_tac
  · exact hb)
set_option hygiene false in
local notation "T30!" q0__:max q1__:max q2__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => q1__ - qq9.2.2.2.2.2.2.2.2.2.2.2.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨plan1, tbl1, fr1, bpos1, cand1, arr1, ed1, llf1, df1, litc1, lcost1, dcs1, dcb1, pi1⟩ _
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    have hstarts : starts.length ≤ Std.Usize.max := Std.Slice.length_ineq starts
    simp only [q2__]
    try simp only [lift, ite_ok, alloc.vec.Vec.deref_mut, bind_tc_ok]
    step*
    all_goals repeat (first
      | (split <;> (try step*))
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply spec_ite_cut <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals scalar_tac
  · trivial)
@[local step]
theorem mode_gk_spec (mode : Std.Usize) (base : Std.U64) :
    slot.h_mode_gk mode base ⦃ fun _ => True ⦄ := by
  rw [slot.h_mode_gk]
  step*
  all_goals (repeat (split <;> step*))
  all_goals scalar_tac
@[local step]
theorem champ_spec (mode : Std.Usize) (input : Slice Std.U8) (plan : Slice Std.U32) (gk : Std.U64) (i5 : Std.Usize) :
    slot.h_champ mode input plan gk i5 ⦃ fun _ => True ⦄ := T15! slot.h_champ
@[local step]
theorem champ_if_spec (mode : Std.Usize) (input : Slice Std.U8) (plan : Slice Std.U32) (on : Std.Usize) (gk : Std.U64) (i5 : Std.Usize) :
    slot.h_champ_if mode input plan on gk i5 ⦃ fun _ => True ⦄ := T14! slot.h_champ_if
@[local step]
theorem parse_mode_spec (input : Slice Std.U8) (out : Slice Std.U32) (mode : Std.Usize)
    (hlen : input.length ≤ out.length) :
    slot.h_parse_mode input out mode ⦃ fun r =>
      r.1.val ≤ input.length ∧
      r.2.length = out.length ∧
      LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
  rw [slot.h_parse_mode]
  simp only [lift, alloc.vec.Vec.deref_mut, bind_tc_ok]
  step*
  exact ⟨r_post1, r_post2, r_post3⟩
end EH

theorem parse_spec (input : Slice Std.U8) (out : Slice Std.U32)
    (hlen : input.length ≤ out.length) :
    slot.parse input out ⦃ fun r =>
      r.1.val ≤ input.length ∧
      r.2.length = out.length ∧
      LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
  rw [slot.parse]
  exact EH.parse_mode_spec input out 3#usize hlen
end Submission
