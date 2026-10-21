-- STOPPED: public small-select produced identical tokens on all 28 files with extra time.
-- Retained research draft only; no further proof integration is authorized absent new evidence.
import Lz77
import Slot

/-!
RESEARCH DRAFT -- NOT COMPILED, NOT A SUBMISSION PROOF.

Target frozen parser:
  candidates/r5-opt-small-select/parse.rs
  sha256 a3bb941f057036a94313f640f485258a80d335f69641d43e5d2eb6c74a6c7935

This file changes no candidate bytes. Fresh Slot evidence is now available:
  evidence/round5/37582348267/new-mechanisms-a/extraction/
    r5-opt-small-select/Funs.lean
  sha256 a14d5f5d32e7f031aba3d37d6398fbc475adb226a9248d90f8d55af81b2a56e4
Official extract-only accepted this Rust hash; proof_status remains NOT_RUN.
The six semantic lemmas use the published Slice/toks/Valid interface. The
three final definitional adapter lemmas use actual observed Slot bodies.
No new loop state or returned-borrow ordering is guessed.

Pure lemma tactic scripts below remain UNCHECKED until the CI Lean compiler
accepts them. They contain no proof escape and make no completed-gate claim.
-/

namespace Submission.R5SmallDraft

open Aeneas Aeneas.Std Result ControlFlow
open LZ77 (toks bytes)

/-- The published token view extends by the value of the next source cell. -/
theorem toks_succ_of_lt (src : Slice Std.U32) (i : Nat)
    (hi : i < src.length) :
    toks src (i + 1) = toks src i ++ [(src.val[i]).val] := by
  unfold toks
  rw [List.take_add_one, List.getElem?_eq_getElem hi]
  simp only [List.map_append, List.map_cons, List.map_nil]

/-- Copying the next source cell extends an already equal token prefix.
This is the semantic step needed by zero-offset h_copy32. -/
theorem copied_prefix_step (src dst : Slice Std.U32) (i : Std.Usize)
    (hs : i.val < src.length) (hd : i.val < dst.length)
    (hp : toks dst i.val = toks src i.val) :
    toks (dst.set i src.val[i.val]) (i.val + 1) =
      toks src (i.val + 1) := by
  rw [LZ77.toks_update dst i src.val[i.val] hd,
      toks_succ_of_lt src i.val hs, hp]

/-- Safe in-bounds set preserves the destination buffer length. -/
theorem copied_cell_preserves_length (src dst : Slice Std.U32) (i : Std.Usize)
    (hs : i.val < src.length) :
    (dst.set i src.val[i.val]).length = dst.length := by
  simp [Std.Slice.set_val_eq]

/-- The semantic invariant starts with the empty prefix. -/
theorem copied_prefix_zero (src dst : Slice Std.U32) :
    toks dst 0 = toks src 0 := by
  simp [toks]

/-- An equal token prefix transports the existing parser's decode guarantee. -/
theorem valid_of_copied_prefix (input : Slice Std.U8) (src dst : Slice Std.U32)
    (n : Nat) (hp : toks dst n = toks src n)
    (hv : LZ77.Valid (bytes input) (toks src n)) :
    LZ77.Valid (bytes input) (toks dst n) := by
  rw [hp]
  exact hv

/-- Close precisely the published obligation for a selected copied result. -/
theorem copied_result_valid (input : Slice Std.U8) (out0 src dst : Slice Std.U32)
    (count : Std.Usize)
    (hc : count.val ≤ input.length)
    (hl : dst.length = out0.length)
    (hp : toks dst count.val = toks src count.val)
    (hv : LZ77.Valid (bytes input) (toks src count.val)) :
    count.val ≤ input.length ∧ dst.length = out0.length ∧
      LZ77.Valid (bytes input) (toks dst count.val) := by
  exact ⟨hc, hl, valid_of_copied_prefix input src dst count.val hp hv⟩

/-- Actual Funs.lean:11903 safe-read definition, independent of any weak spec. -/
theorem h_get_definition (v : Slice Std.U32) (i : Std.Usize) :
    slot.h_get v i =
      (if i < Slice.len v then Slice.index_usize v i else ok 0#u32) := by
  rfl

/-- Actual Funs.lean:11912 safe-write definition. -/
theorem h_set_definition (v : Slice Std.U32) (i : Std.Usize) (x : Std.U32) :
    slot.h_set v i x =
      (if i < Slice.len v then Slice.update v i x else ok v) := by
  rfl

/-- Actual Funs.lean:14937 zero-offset wrapper, ready for the strong loop spec. -/
theorem copy_zero_entry (src dst : Slice Std.U32) (m : Std.Usize) :
    slot.h_copy32 src 0#usize dst 0#usize m =
      slot.h_copy32_loop src 0#usize dst 0#usize m 0#usize := by
  rfl

end Submission.R5SmallDraft

/-!
MINIMAL INTEGRATION PLAN USING ACTUAL EXTRACTION

1. Keep the complete S and EH proof scopes in their existing order for
   small-select. Unlike a-best299, this parser does not change the A engine
   and requires no H-before-S reordering. Add a fresh scope after both parent
   scopes but before the final Submission.parse_spec.

2. Prove only totality for r5_block_bits and r5_token_bytes. Parser correctness
   does not require showing cost equality with the encoder or that the chosen
   stream is smaller. The two pre-existing parser specs already establish the
   complete output contract independently of the comparison.

   r5_block_bits direct helper proof interfaces observed in the existing EH
   source (names are verified, not invented):
     EH.bump_spec, EH.pkg_merge_pm_spec, EH.sum_range_spec, EH.get_spec,
     EH.set_spec, EH.last_nz_spec, EH.copy32_spec, EH.rle_stats_spec,
     EH.hclen_of_spec, EH.dot_spec, EH.fixed_dot_spec, EH.lt64_spec,
     EH.sel64_spec.
   r5_token_bytes additionally uses EH.walk_bump_spec and EH.clear_spec.
   Locally register the needed weak helper specs inside the scorer scope.
   The existing helpers use safe indexing/wrapping arithmetic; the new scorer
   still needs bounds on ordinary additions and loop progress.

   Token-scorer loop mathematical invariant, to map onto the actual extracted
   state tuple (fr, lens, bits, i, used), now verified in Funs:
     i <= end <= tokens.length;
     used <= 16384;
     i < end -> used < 16384.
   Measure end - i. A nonfinal full 16384-token block resets used to zero.
   The last iteration may leave used = 16384 only when i = end. Each legal
   branch expression len = value % 256 + 3 is <=258; dist = value /256+1 is
   at most 16777216 for a u32. No legality of the input tokens is needed for
   the scorer's safety spec. Final bits and score additions are wrapping.

3. Strengthen zero-offset copying only in the new final proof scope. Existing
   EH.get_spec, EH.set_spec and EH.copy32_spec have postcondition True, so
   letting step consume them loses required information. Either unfold safe
   get/set at their call sites or add local in-bounds semantic specs first.

   Callable argument lists verified against this run's actual Funs:
     slot.h_get (v : Slice Std.U32) (i : Std.Usize)
     slot.h_set (v : Slice Std.U32) (i : Std.Usize) (x : Std.U32)
     slot.h_copy32_loop (src : Slice Std.U32) (soff : Std.Usize)
       (dst : Slice Std.U32) (doff : Std.Usize) (m : Std.Usize) (i : Std.Usize)
     slot.h_copy32 (src : Slice Std.U32) (soff : Std.Usize)
       (dst : Slice Std.U32) (doff : Std.Usize) (m : Std.Usize)
   Actual wrapper return type is Result (Slice Std.U32). Actual loop state
   is (dst1, i1), with measure m.val - i1.val. The loop.body argument order
   differs from the wrapper: src, soff, doff, m, dst, i. Both offsets are zero
   for this entry, so wrapping_add produces i; proving that scalar identity
   remains a tactic/API task, not a signature uncertainty.

   Proposed zero-offset loop invariant:
     i.val <= m.val;
     m.val <= src.length and m.val <= dst0.length;
     dst.length = dst0.length;
     toks dst i.val = toks src i.val.
   The desired post is destination length preservation plus
     toks dst_result m.val = toks src m.val.
   copied_prefix_step, copied_cell_preserves_length and copied_prefix_zero
   above supply the pure semantic parts. Starting at i=0 requires no initial
   relationship between the S output and H output. Original S bytes beyond
   the chosen H token count need no preservation theorem.

4. Final entry composition follows actual extracted borrow/backward-function
   boundaries. Register Submission.zeros_spec, s_parse_spec,
   EH.parse_mode_spec, classify_spec and the new scorer spec. Use the strong
   copy spec explicitly so the weak EH.copy32_spec is not chosen accidentally.

   Small-input branch:
     zeros(n) gives alternate buffer length n;
     S gives s_count<=n, length(s_out)=length(out), Valid(input,S-prefix);
     H gives h_count<=n, length(h_out)=n, Valid(input,H-prefix);
     the read-only scorer calls do not mutate either output;
     if H costs less, h_count<=n supplies both copy range preconditions,
       and copied_result_valid closes the return;
     otherwise return the existing S result unchanged.
   Large-input branches use the unchanged original classifier/S/H composition.
   A score can be inaccurate or equal without affecting correctness.

ACTUAL INTERFACES AND REMAINING GAPS

Observed in the frozen Funs hash above:

- r5_block_bits (fr : Slice U32) (off : Usize) (lens : Slice U32)
    : Result (U64 x Slice U32 x Slice U32).
  Return order is score, mutated frequencies, mutated lens. It has no new loop
  and calls the already proved EH helpers. Its body differs from h_block_bits
  only by choosing h_pkg_merge_pm for all three alphabets. A True postcondition
  is sufficient here. Include EH.sel32_spec too: actual Funs names the fallback
  distance-length selector explicitly (the earlier helper list omitted it).

- r5_token_bytes_loop tokens end fr lens bits i used
    : Result (Array U32 320 x Array U32 320 x U64).
  Captures: tokens, end. State: (fr, lens, bits, i, used). Done returns only
  (fr, lens, bits). Thus one new loop spec and one wrapper spec suffice.
  Actual padding branch contains checked subtraction 8 - (x % 8); its safety
  follows from the modulo bound. Ordinary i+1 and used+1 use the invariants
  already listed. Result values need no numeric score postcondition.

- r5_token_bytes tokens count : Result U64. No mutable external borrow is
  returned: both the S and H token buffers survive the scorer unchanged.

- parse's small branch creates other via zeros, runs S to (s_count,out1), then
  deref_mut(other) to (s,deref_mut_back), then H to (h_count,s1). It compares
  r5_token_bytes out1 s_count with r5_token_bytes (Vec.deref other1) h_count,
  where other1 = deref_mut_back s1. H selection copies from that same immutable
  Vec view to out1 and returns (h_count,out2); otherwise it returns
  (s_count,out1). The only representation bridge left is showing that
  Vec.deref (deref_mut_back s1) retains the slice token view and length proved
  for s1. Existing parser proofs already simplify alloc.vec.Vec.deref_mut;
  observe the library reduction in CI rather than add an arbitrary equality.

- h_get : Result U32; h_set/h_copy32_loop/h_copy32 : Result (Slice U32).
  The h_copy32_loop.body returns ControlFlow (Slice U32 x Usize) (Slice U32).
  Its body is the expected safe-read/safe-write sequence and has no hidden
  extra state. All new needed loop shapes are now known.

r5_hist_bits and its two loops are unreachable from small-select's parse.
Do not spend proof work on them for this obligation: their extracted presence
alone does not require a spec, and no old retained theorem refers to them.

MINIMUM ADAPTATION SCOPE (IMPLEMENTATION ESTIMATE, NOT ACCEPTANCE)

Preserve the unchanged parent S/EH proofs and exported contracts. Add:
  (a) a totality spec for r5_block_bits;
  (b) a totality loop + wrapper spec for r5_token_bytes;
  (c) semantic in-bounds get/set adapters and one zero-offset copy loop +
      wrapper spec, using the pure prefix lemmas above;
  (d) replace only final parse_spec with composition at the observed bindings.
No A-loop migration, matching invariant, optimality theorem or encoder equality
proof is needed for small-select. The copied-prefix loop is the sole new
semantic loop. Source-level effort appears bounded; actual Lean tactic work,
proof-file size and unchanged 900-second step limit remain unmeasured. The
parent's 375553-byte proof leaves 148735 bytes under the per-file cap, so size
is not the evident first obstacle. Elaborating all parent engine proofs again
may still dominate verification time; original h3r-smallc299 took 889.7 seconds
through axiom checks, which is not the duration of the single statement step.

The pure/definitional lemma scripts in this file are still NOT_COMPILED. No
strong copy theorem, new scorer-loop theorem or final parse_spec has been
claimed complete. Follow the measured performance decision before investing
in full integration and a gate attempt.
-/
