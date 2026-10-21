/-
CLOSED — PERFORMANCE STOP.
The root retained original H16-small; no R6 candidate was promoted.
This copyfast proof draft remains NOT_COMPILED / NO_GATE. No Lean run or
proof-ready derivative is pursued. Retained research only, not a submission-
ready proof or candidate. Frozen candidate source/proof files are unchanged.
-/

import Lz77
import Slot

/-!
COPYFAST DRAFT -- NOT COMPILED / NOT A GATE RESULT.

Target source SHA256:
  d414c981b22a23cae40561173e6812e4846f3fb8ba500ad6dd5d4ef5582efb19
Actual Funs from run 37598783885, copy-screen/extraction:
  0b3b99dfd29d6e41a0b41524bd6b365566d5314d88b0cc9d27c2120e2b53137b

All Slot names, argument orders, state pairs and return types below were read
from that Funs. The exact primitive write is Slice.update, not an assumed
index_mut/backward function. These are complete tactic attempts without proof
escapes, but have not been executed by Lean.

Integration if performance warrants it: replace the parent's
EH.copy32_loop_spec and EH.copy32_spec block with these theorem declarations
inside its existing EH namespace. The imports/namespace/open lines below are
for viewing this fragment independently, not additional nested namespaces to
paste into the parent. All other parent declarations stay unchanged.
-/

namespace Submission.EH
open Aeneas Aeneas.Std Result ControlFlow
open LZ77 (ite_ok)

/-- Direct-loop safety. Nat range sums plus the slice length bound establish
both actual machine additions; the loop invariant preserves the destination
length needed by all later writes. -/
@[local step]
theorem copy32_loop0_spec
    (src : Slice Std.U32) (soff : Std.Usize) (dst : Slice Std.U32)
    (doff m i : Std.Usize)
    (hs : soff.val + m.val ≤ src.length)
    (hd : doff.val + m.val ≤ dst.length)
    (hi : i.val ≤ m.val) :
    slot.h_copy32_loop0 src soff dst doff m i ⦃ fun r =>
      r.length = dst.length ⦄ := by
  have hmaxs : src.length ≤ Std.Usize.max := Std.Slice.length_ineq src
  have hmaxd : dst.length ≤ Std.Usize.max := Std.Slice.length_ineq dst
  rw [slot.h_copy32_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, j) => m.val - j.val)
    (inv := fun (d, j) => d.length = dst.length ∧ j.val ≤ m.val)
  · rintro ⟨dst1, i1⟩ ⟨hlen, hle⟩
    simp only [slot.h_copy32_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact ⟨rfl, hi⟩

/-- Original safe fallback, strengthened only to retain slice length.
Unfold h_get/h_set locally so their existing weak True specs cannot discard
the Slice.update length postcondition. -/
@[local step]
theorem copy32_loop1_spec
    (src : Slice Std.U32) (soff : Std.Usize) (dst : Slice Std.U32)
    (doff m i : Std.Usize) :
    slot.h_copy32_loop1 src soff dst doff m i ⦃ fun r =>
      r.length = dst.length ⦄ := by
  rw [slot.h_copy32_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, j) => m.val - j.val)
    (inv := fun (d, _) => d.length = dst.length)
  · rintro ⟨dst1, i1⟩ hlen
    simp only [slot.h_copy32_loop1.body, slot.h_get, slot.h_set,
      lift, ite_ok]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · rfl

/-- Actual fallback clones are definitionally equal after unfolding their
respective loop/body declarations; no extra loop invariant is invented. -/
@[local step]
theorem copy32_loop2_spec
    (src : Slice Std.U32) (soff : Std.Usize) (dst : Slice Std.U32)
    (doff m i : Std.Usize) :
    slot.h_copy32_loop2 src soff dst doff m i ⦃ fun r =>
      r.length = dst.length ⦄ := by
  change slot.h_copy32_loop1 src soff dst doff m i ⦃ fun r =>
    r.length = dst.length ⦄
  exact copy32_loop1_spec src soff dst doff m i

@[local step]
theorem copy32_loop3_spec
    (src : Slice Std.U32) (soff : Std.Usize) (dst : Slice Std.U32)
    (doff m i : Std.Usize) :
    slot.h_copy32_loop3 src soff dst doff m i ⦃ fun r =>
      r.length = dst.length ⦄ := by
  change slot.h_copy32_loop1 src soff dst doff m i ⦃ fun r =>
    r.length = dst.length ⦄
  exact copy32_loop1_spec src soff dst doff m i

@[local step]
theorem copy32_loop4_spec
    (src : Slice Std.U32) (soff : Std.Usize) (dst : Slice Std.U32)
    (doff m i : Std.Usize) :
    slot.h_copy32_loop4 src soff dst doff m i ⦃ fun r =>
      r.length = dst.length ⦄ := by
  change slot.h_copy32_loop1 src soff dst doff m i ⦃ fun r =>
    r.length = dst.length ⦄
  exact copy32_loop1_spec src soff dst doff m i

/-- Preserve the parent's public helper postcondition True. The strong loop
length postconditions discharge internal bounds and are discarded here. The
actual wrapper short-circuits before its checked subtractions and selects one
of the five proven loop interfaces; the parse obligation is unchanged. -/
@[local step]
theorem copy32_spec
    (src : Slice Std.U32) (soff : Std.Usize) (dst : Slice Std.U32)
    (doff m : Std.Usize) :
    slot.h_copy32 src soff dst doff m ⦃ fun _ => True ⦄ := by
  have hmaxs : src.length ≤ Std.Usize.max := Std.Slice.length_ineq src
  have hmaxd : dst.length ≤ Std.Usize.max := Std.Slice.length_ineq dst
  rw [slot.h_copy32]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

end Submission.EH
