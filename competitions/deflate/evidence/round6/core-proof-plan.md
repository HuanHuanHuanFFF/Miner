# R6 core proof migration plan from actual extraction

This is a read-only compatibility assessment. Candidate Rust, proofs, manifests and generator remain frozen. Performance decides whether a separate proof-ready derivative is created; none is created here. No new Lean code has been compiled in this review.

## Bound evidence

Parent proof: `candidates/r5-h16-small-proofopt/Parse.lean`, SHA256 `d55744de52bb0469768f0bbfd73ffecbabf9899b63e0167469fd7bb79c6293c7`.

Parent actual Funs: `evidence/round5/37584216832/h16-proofopt-gate/gate/extracted-r5-h16-small-proofopt/Funs.lean`, SHA256 `57a6f6f1d8a9369252273a5c4cc96c63eeccb9c69eaabf570ebe08dae16e5c55`.

New actual extraction is under `evidence/round6/37594271466/core-screen/extraction/`, run commit `69e4c010708d5c295836eb2b07c90b88ad091744`:

| Candidate | Funs SHA256 | Recorded result |
| --- | --- | --- |
| h3prefix | `280c1c03149d9528c9b827a5a832d5def971f6b4535cb3d6fab9b02de705e273` | extract accepted, exit 0, proof NOT_RUN |
| lazy-t5 | `189be7dcd17f00f903443f62be4b9540a0a47cd72cdeef43c74e57c37240d7b4` | extract accepted, exit 0, proof NOT_RUN |

**VERIFIED:** comparing actual `def` declarations after separating source-provenance comments finds no added or removed function definitions. h3prefix changes only `h_bt_walk_loop.body`, `h_bt_walk_loop`, `h_bt_walk`, `h_find_pos`. lazy-t5 changes only `h_literal_bits_loop.body` and `h_optimize`. Constants.lean is byte-identical for all three versions, SHA256 `65c8f96c5ecfc64349d7941042cb6144a4fe6fb467cbb21d7ed350c8107f9a67`; Types.lean differs only in source-provenance comments and becomes identical when those comments are removed. All checked-emitter definitions remain unchanged.

## H3prefix: four localized text replacements in two theorem interfaces

The actual new function has argument order:

```text
h_bt_walk input child root pos cap best0 rec maxd hint
          known_pos known_len mc m0
```

The actual new loop wrapper has argument order:

```text
h_bt_walk_loop input child pos rec maxd known_pos known_len mc m0
               plt pgt cur ltl gtl len best wl wd depth go lim stop kcur kl
```

Its body receives immutable captures in this order before the mutable state:

```text
input pos rec maxd known_pos known_len m0 lim stop kcur kl
```

The loop state is **unchanged**, exactly:

```text
(child, mc, plt, pgt, cur, ltl, gtl, len, best, wl, wd, depth, go)
```

The loop's final returned tuple is also unchanged: `(child, mc, plt, pgt, best, wl, wd, go)`. These shapes were read from the actual new Funs; they are not predictions from Rust local ordering.

Apply the following only inside the identified theorem block of the parent proof:

| Parent theorem | Exact old fragment | Replacement |
| --- | --- | --- |
| `EH.bt_walk_loop_spec`, line 4175, declaration | `(maxd : Std.Usize) (mc : alloc.vec.Vec Std.U32)` | `(maxd : Std.Usize) (known_pos : Std.Usize) (known_len : Std.Usize) (mc : alloc.vec.Vec Std.U32)` |
| Same theorem, specification application | `slot.h_bt_walk_loop input child pos rec maxd mc m0` | `slot.h_bt_walk_loop input child pos rec maxd known_pos known_len mc m0` |
| `EH.bt_walk_spec`, line 4189, declaration | `(hint : Std.Usize) (mc : alloc.vec.Vec Std.U32)` | `(hint : Std.Usize) (known_pos : Std.Usize) (known_len : Std.Usize) (mc : alloc.vec.Vec Std.U32)` |
| Same theorem, specification application | `slot.h_bt_walk input child root pos cap best0 rec maxd hint mc m0` | `slot.h_bt_walk input child root pos cap best0 rec maxd hint known_pos known_len mc m0` |

Keep both existing tactic bodies unchanged for the first compile attempt. The loop's depth projection in its `maxd - depth` measure and its 13-variable `rintro` match the unchanged actual loop state. Added `h_eq`, `h_lt`, bitwise-and and `h_sel` calls already have totality specs. The proof body uses generic `step*`/branch splitting rather than generated temporary identifiers, so renumbering temporaries is not itself a required patch.

`EH.find_pos_spec` (4195) keeps its statement and `T15! slot.h_find_pos` body: new Funs only adds `c3 l3` to its `h_bt_walk` call, which the repaired generic wrapper spec accepts. `find_all_spec`, `champ_spec`, `optimize_spec`, `parse_mode_spec`, the S namespace and final dispatcher retain their statements and bodies. Any further patch must follow an actual Lean diagnostic, not speculative tuple changes.

**Status:** these four edits are a precise arity repair justified by actual extraction. Whether the unchanged tactics close the extended body has not been compiled and remains UNKNOWN. The byte-prefix semantic argument is relevant to token equivalence; it is not an extra precondition needed by the planner's True-postcondition totality proof.

## Lazy-t5: zero-edit parent proof is the first justified attempt

**VERIFIED structural compatibility:** every signature, loop wrapper, loop-state tuple and return type remains unchanged. `h_literal_bits_loop.body` inserts only:

```lean
let i12 := Slice.len t5
let t51 ←
  if i12 > 0#usize
  then do
    let i13 ← lift (core.num.Usize.wrapping_mul b H_TB)
    h_init5_table fr4 t5 i13
  else ok t5
```

The same old increment and continuation follow. `EH.literal_bits_loop_spec` (5114) already has invariant True and measure `nblk - b`, unfolds that body, runs `step*`, then `repeat (split <;> step*)`. Its callee `init5_table_spec` accepts any slice length. The added else branch is a successful identity result, so there is no missing semantic table invariant or new loop-progress condition in the specification.

The actual `h_optimize` delta is only the allocation input:

```lean
let i2 ← lift (i5 &&& 1#usize)
let i3 ← lift (core.num.Usize.wrapping_mul nbmax H_TB)
let i4 ← h_sel i2 i3 0#usize
let t5 ← h_filled i4 0#u32
```

Its downstream tuple form remains the same. `EH.optimize_spec` (5463) uses `T15!`; existing bit operations, `sel_spec`, and `filled_spec` cover an arbitrary selected usize including zero. `literal_bits_spec` has no assumption that t5 is nonempty or equals tlit's length. Renamed generated temporaries are not hardcoded in these proof bodies.

Therefore the exact minimum proposed patch is **empty**: first compile the original parent proof bytes against the lazy-t5 Slot. If the tactic engine stops at the new conditional bind, make a local branch split in `literal_bits_loop_spec` at that bind and prove its two cases with existing helper specs, preserving its public statement and progress invariant. Such a fallback is conditional on an actual error; it has not been applied.

**Do not equate structural compatibility with acceptance:** extract-only did not run this parent proof. “No proof edit appears necessary” is INFERRED from the actual definitions and existing tactic structure; only a new successful Lean obligation and axiom check can establish it. The currently frozen candidate proof remains marked NOT_ADAPTED until that evidence exists, even if its content ultimately needs no theorem edits.

## Release boundary

Both candidates retain the original checked-emitter semantics. A performance win plus finite token/output equality is the prerequisite for spending time on a separate proof-ready derivative. Then perform the smallest patch above, re-extract the exact Rust, compile the obligation, check the three-axiom whitelist and complete the unchanged official gate. Extract-only success, an empty patch or a successful compilation of individual helper lemmas is not a full gate result.
