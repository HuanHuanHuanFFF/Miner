# Copyfast proof preparation before actual extraction

**CLOSED — PERFORMANCE STOP.** The root retained the original H16-small baseline after all six R6 candidates failed to establish useful, stable improvement. No copyfast proof-ready suffix or new proof run is pursued. `copy-proof-draft.lean` remains **NOT_COMPILED / NO_GATE**, retained as research material only; it is not a submission-ready proof or candidate. This closure changes no frozen parser, candidate proof, manifest or generator.

Candidate read only: `candidates/r6-h16-cpu-copyfast/parse.rs`, SHA256 `d414c981b22a23cae40561173e6812e4846f3fb8ba500ad6dd5d4ef5582efb19`. Parent proof is `candidates/r5-h16-small-proofopt/Parse.lean`, SHA256 `d55744de52bb0469768f0bbfd73ffecbabf9899b63e0167469fd7bb79c6293c7`. Sol owns this candidate/generator. This preparation edits neither, creates no proof-ready derivative, and runs no compiler/CI. Run 37598783885 at a25dee2 is pending; dispatch is not proof or performance evidence.

## Observed Rust and parent proof

The only changed helper is `h_copy32`. It first checks `soff <= src.len()`, `doff <= dst.len()`, `m <= src.len()-soff`, and `m <= dst.len()-doff`. That branch copies by ordinary indices `src[soff+i]` / `dst[doff+i]` while i<m, then returns. Every invalid range uses the exact previous safe-get/safe-set loop with wrapping offset addition.

The parent `EH.copy32_loop_spec` (line 4598) proves the old guarded loop total with invariant True and measure `m-i`. `EH.copy32_spec` (4611) retains the generic signature and postcondition True. Existing downstream H planner proofs use that weak helper contract; the final byte-checking emitter supplies decoding correctness. A stronger copy-value theorem is not required to discharge that existing LZ77 obligation.

Actual new loop names, capture order, mutable-return shape and loop-state tuple are **UNKNOWN**. Do not assume the direct loop takes the old name or assign numbered names to the fallback before reading Funs. No declaration against a guessed Slot interface is written here.

## Direct-loop invariant and arithmetic

Let S=src.length and D=the initial destination length. The fast branch guard gives the natural-number facts:

- soff <= S and doff <= D;
- m <= S-soff and m <= D-doff;
- hence soff+m <= S and doff+m <= D.

Use these as fixed hypotheses for the direct-loop theorem. The minimum mutable invariant is `i <= m` and `dst.length = D`; measure is `m-i`. No prefix-value invariant is needed for totality. During an iteration i<m:

1. `soff+i < soff+m <= S`, so the source index is valid.
2. `doff+i < doff+m <= D = dst.length`, so the destination index is valid.
3. Slice lengths are at most `Usize.max`, from the existing `Std.Slice.length_ineq` lemma. The two actual index additions therefore fit usize. Express `soff+m` and `doff+m` as Nat inequalities rather than introducing new checked Rust additions.
4. `i+1 <= m <= Usize.max`, so the increment is safe and the natural measure strictly decreases.
5. The indexed write preserves destination length. Use the actual extracted update operation's postcondition and `Std.Slice.set_val_eq`/list-set length simplification as appropriate; determine whether extraction uses update or an index_mut/backward function before writing the tactic step.

At loop exit return `dst_result.length = D` (and, if convenient, i=m inside the loop proof). The outer helper can weaken that result to its original True postcondition. The length fact is needed inside the new direct loop so subsequent destination bounds remain valid, even though callers require only totality.

## Wrapper and fallback

The source guard is short-circuiting. During wrapper proof, split the actual generated guards in their evaluation order: the subtractions `src.len()-soff` and `dst.len()-doff` are evaluated only after the corresponding offset bounds have succeeded. This is necessary for checked subtraction safety, not just for entering the direct-loop theorem.

On the valid branch instantiate the direct-loop theorem at i=0 with length reflexivity and the guard inequalities. On any invalid branch use the old safe fallback's totality argument, adapted only to its actual new extracted identifier/signature. The fallback still needs no bound on soff/doff/m because h_get/h_set handle out-of-range access and arithmetic remains wrapping. Its counter safety follows from i<m, as before.

Retain the public `EH.copy32_spec` statement with postcondition True to avoid changing every caller. Proving wrapper-level destination-length preservation would require strengthening the fallback's h_set/loop result too; that is optional scope and not part of the minimum gate repair. The existing downstream parser, table-model and checked-emitter proof statements can remain intact.

## Edge cases to keep covered

- m=0, empty slices, and offsets exactly at their ends: the valid branch performs no indexed access.
- Either offset beyond the slice end: short-circuit directly to the safe old fallback; no underflowing guard subtraction.
- Maximal representable m: in the legal branch the slice-length bounds still prove every increment; no arbitrary small-input bound is introduced.
- Source data is borrowed immutably and the destination mutably by the safe Rust interface. The proof can keep the source slice fixed. Do not introduce an aliasing model or unsafe-copy assumption absent from the source.
- The optimized equality claim is separate: within the legal range, ordinary and wrapping offset sums coincide and both old guards accept every access; outside it the old body is preserved. Finite token/output equality tests this execution claim but is not a universal copy theorem or a completed gate.

## Next evidence and minimal repair order

Read the actual helper wrapper and both loop/body definitions from fresh Funs, then bind each to direct-copy or fallback by its body rather than guessed numbering. Confirm the unchanged H helpers and semantic emitter definitions are still identical. Prepare the direct-loop totality/length theorem, reuse the fallback theorem with its actual name, then repair only the wrapper composition. Attempt a full proof-ready derivative only if the performance result warrants it, under a separately assigned directory. Actual extraction, Lean/axiom acceptance and gate duration remain UNKNOWN here.

## Actual extraction: precise loops and draft patch

Official extract-only in run 37598783885 accepted the frozen source above, exit 0; proof status is **NOT_RUN**. Funs SHA256 is `0b3b99dfd29d6e41a0b41524bd6b365566d5314d88b0cc9d27c2120e2b53137b`, saved at `evidence/round6/37598783885/copy-screen/extraction/r6-h16-cpu-copyfast/Funs.lean`.

**VERIFIED actual structure:** the extractor generated five loops, not just a direct/fallback pair. `h_copy32_loop0` (line 14924) is the legal direct-copy loop. Its body (14905) uses checked `soff+i`, `Slice.index_usize`, checked `doff+i`, `Slice.update`, and checked `i+1`, in that order. The loop state is `(dst,i)` and its return type is `Result (Slice U32)`.

`h_copy32_loop1`, `loop2`, `loop3`, and `loop4` (14956/14988/15020/15052) are four extracted copies of the original safe fallback. Their signatures, bodies and states are identical apart from their own definition names. Wrapper `h_copy32` (15064) calls loop1 when the final destination-room condition fails, loop2 when source-room fails, loop3 when destination offset is out of range, and loop4 when source offset is out of range. Every one needs a registered spec even though their implementations are duplicate fallbacks.

The exact wrapper remains short-circuiting: source offset check, destination offset check, source subtraction/room check, destination subtraction/room check, direct loop. Consequently both checked subtractions occur only after their corresponding offset bound is established.

`evidence/round6/copy-proof-draft.lean` now contains only six new/replacement theorem attempts, based on those actual interfaces:

1. `copy32_loop0_spec`: range-sum hypotheses `soff+m <= src.length`, `doff+m <= dst.length` and `i<=m`; invariant `(dst.length=initial length, i<=m)`; post preserves destination length.
2. `copy32_loop1_spec`: old safe fallback termination argument, strengthened with destination-length preservation. h_get/h_set are unfolded locally so the actual Slice.update post is retained instead of applying their weak True specs.
3. `copy32_loop2_spec`, `copy32_loop3_spec`, `copy32_loop4_spec`: reuse loop1 by definitional equality of the actual cloned definitions, keeping the same length post.
4. `copy32_spec`: compose the actual five branches with the parent's exact True postcondition. The loop specs retain destination length for internal safety; the wrapper discards that extra fact. All caller and public parse statements stay unchanged.

The inequality required by the direct loop is **offset + i**, not i+m: at i<m, offset+i < offset+m <= slice.length <= Usize.max. The increment obeys i+1<=m<=Usize.max. The range sums in the theorem are Nat expressions, so they do not create a new checked machine addition. No upper bound on input size or arbitrary small m is introduced.

**NOT_COMPILED:** these are complete tactic drafts without escapes, not accepted lemmas. The actual shapes justify the statements, but the simplifier/scalar tactic handling and cloned-loop definitional-equality `change` still need Lean execution. If transparency prevents `change`, explicitly unfold the two actual loop and loop.body definitions, then reuse loop1; their normalized bodies have been compared. If step automation does not retain the slice length after an update, use the concrete update equality and `Std.Slice.set_val_eq` rather than dropping the invariant. The old `copy32_loop_spec` references a name absent from the new Slot and must be replaced, not left alongside the new patch.

No candidate or generator was changed. A proof-ready derivative still awaits a useful performance result and a separately assigned output path.
