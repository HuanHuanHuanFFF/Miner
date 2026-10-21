# Round 6 H16-small core candidates

**Core routes stopped after measurement.** Both frozen candidates preserved all tested tokens/output but were slower than H16-base in primary and both-order auxiliary measurements. No full proof/gate is pursued for either. See final closure below.

This line follows the user's new instruction to optimize H16-small before other hybrid variants. Two separate core-work hypotheses were generated; the parent and all earlier candidates stay frozen. This worker runs no CI/compiler, Git operation, formal submission or wallet action.

## Parent and evidence boundary

Parent is `candidates/r5-h16-small-proofopt`: Rust SHA256 `d9826bc92ba02f49cb6e552ed172a4fb82dc10fa8fb51aacf73e7947ed38a94d`, proof `d55744de52bb0469768f0bbfd73ffecbabf9899b63e0167469fd7bb79c6293c7`. The actual saved official verdict in `evidence/round5/37584216832/h16-proofopt-gate/gate/r5-h16-small-proofopt-gate.json` has `accepted=true`. Its generation-time manifest still says UNKNOWN; that historical text is not substituted for the actual gate receipt.

The inspected `evidence/round5/hybrid-review-25924/analysis.json` reports 5 independent H16-small jobs / 9 blocks, public mean time 7.175718805 and size 33.86321383735312%. Fixed427 projects a conditional geometric weight about 0.01635448, whereas matched299 projects zero and domination. Both are H/S transfer hypotheses, not observed formal hybrid performance. Public token/size preservation is the immediate requirement; only actual paired speed and refreshed official geometry can establish useful progress. Rewards are not assumed monotonic in speed.

The source search/memory observations below are **VERIFIED source facts**, not sampled CPU hotspots. Existing diagnostics do not measure H3-prefix reuse frequency, literal-table construction cost, memory bandwidth or hardware counters. Their actual contribution to total compression time remains UNKNOWN.

## 1. `r6-h16-core-h3prefix`

**Observed repetition:** `h_find_pos` first calls the original `h_ext_if` on the latest H3 source, comparing actual input bytes for up to `min(cap,H_H3CAP)` (H_H3CAP is 8). It then starts the binary-tree traversal. When that traversal visits the exact same historical source, `h_bt_walk` currently knows only its tree/previous-position prefix hint and can recompare the bytes just checked by H3.

**Minimal change:** pass `c3` and `l3` as two extra scalar arguments to `h_bt_walk`. For a tree node satisfying `cur == c3`, use `max(existing_prefix,l3)` as the comparison start. Every other node uses its original prefix. No hash value establishes equality: c3/cur are the same encoded byte position, and l3 came from the existing byte-comparison helper. Search depths, nice length, traversal order, strict record-improvement tests, same-slot replacement and all DP/pruning/iteration settings remain unchanged.

**Bound needed for equivalence:** if the H3 comparison runs, `ok3 == 1` implies `rec == 1`; the BT comparison limit is then `cap`, and `l3 <= min(cap,8) <= cap`. If rec is zero, `h_ext_if` takes the original zero default, so the new hint is zero and cannot advance the start. Original tree/historical hints are already clamped to the active limit. Thus the new start stays within the same limit. At an actual mismatch, the first differing byte and lexical direction remain the same. When length reaches `stop`, BT takes its existing terminal-child-copy branch and does not consume the lexical tie bit. The 40-word extension bound is not exhausted for the reachable <=258-byte comparisons, so skipping a proven prefix does not change truncation behavior.

**INFERRED benefit/risk:** fewer repeated word loads/comparisons at matching H3/tree source nodes. Two extra live parameters and a compare/select on every visited tree node may increase register pressure and instruction cost, and could outweigh the removed work. No speedup is claimed before native paired measurement.

**Proof:** NOT_ADAPTED. `h_bt_walk` and its generated loop gain scalar captures; `h_find_pos` has a changed call signature. The unchanged checked emitter remains the contract boundary, but new totality statements must match actual fresh Funs. Exact parser/token equivalence is a separate claim from satisfying the decode contract.

## 2. `r6-h16-core-lazy-t5`

**Observed unused work:** `h_optimize` always allocates and zero-fills a t5 table of `nbmax * H_TB` u32 entries. `h_literal_bits` constructs that table for every literal-model block. It is copied into the active model only with length `h_sel(hi, nbmax*H_TB, 0)`, while `hi = Boolean & i5`. When the low bit of i5 is zero, hi must be zero, so no t5 element can be read by that copy.

**Minimal change:** allocate an empty optional t5 when `(i5 & 1) == 0`, and skip `h_init5_table` when the t5 slice is empty. For a set low bit, retain the original allocation and every table-building operation. The guard uses the actual low bit; it does not confuse an arbitrary nonzero i5 with enabled selection. Literal bit evaluation, histogram accumulation, tlit and selected cost tables remain unchanged. The old init5 helper only reads fr and mutates t5, so skipping a call on an empty t5 exposes no different data to the caller.

**INFERRED benefit/risk:** avoids the optional allocation/zeroing and per-block 256-symbol entropy + length/distance table construction when unused. It adds one emptiness branch per literal-model block. This phase may be too small to affect the aggregate time axis, and changed allocation/code layout can regress time. The source supports eliminating unnecessary work, not a percentage estimate.

**Proof:** NOT_ADAPTED. `h_literal_bits` adds a conditional update and `h_optimize` changes the local scratch length. The old source-level interfaces remain, but the new extracted branch and its proof have not been checked. Do not select the copied proof as gate-ready.

## Frozen outputs and local checks

| Candidate | Rust SHA256 | Rust bytes |
| --- | --- | ---: |
| h3prefix | `d48a03aa05b8dd5149eb2dbfedd3849e16e183c5cafe8dc9895618b485294416` | 176640 |
| lazy-t5 | `9171ad2e5e159dc73f60bc5693322c6c0fe9a655d2338e768495cc252a12147f` | 176526 |

Both copied reference proofs are 264292 bytes, SHA256 `1e9c4d96dcd3eae1454182b32af83e4d925da5384bc9b67d7304befffc6db082`, headed with an explicit NOT_ADAPTED comment. No new axiom, sorry, weakened obligation or timeout setting was introduced.

**VERIFIED:** `python scripts/make-round6-h16-core.py --check` reproduces all source/proof/manifest bytes. Parent hashes are locked. All function declarations outside the two named functions for each candidate, every constant/custom type and the final small-input dispatcher are asserted text-identical to the parent. Both candidates remain below the per-file 524288-byte cap. The generator writes only its two named candidate directories.

**VERIFIED Python model only:** `--model-check` compares the inspected extension algorithm's observable clipped length and nonterminal lexical direction across 12000 fixed-seed cases, with 3133 cases actually advancing the starting prefix. It also checks 8196 i5/predicate combinations for the low-bit dataflow implication. Zero differences. This is neither actual Rust execution nor a full parser equivalence/proof result.

Attribution remains external submissions #299 and #402. Their frozen originals, ownership and endpoint receipts remain in `references/round4-public-299` and `references/round4-public-402`; no official source, encoder, gate or pin is changed.

## First CI and stop conditions

Use `h16-base` as the spec alias for the exact parent and `expected_equivalent_to=h16-base` for each candidate. First run the existing 444-input finite token/decode comparison, plus public per-file token and encoded-output hash comparison against the same parent. Native paired timing remains uninstrumented. If the 240-second finite diagnostic budget expires, classify it as diagnostic timeout rather than changed output or a formal verifier failure; the official per-step limit is untouched.

Any token/output mismatch must stop the supposed equivalence optimization until its cause is understood. Even with equal output, stop a candidate if paired timing is not usefully better or does not reproduce. Do not combine the two changes or adjust budgets before their independent results. If a candidate is clearly faster, capture its actual Funs and adapt the proof in a subsequent authorized stage before an official full gate. Public size equivalence and speed alone do not establish private behavior, formal admission, frontier position or payment.

**UNKNOWN at handoff:** Rust compilation, native finite equality/decode, public per-file equality, time/memory effect, actual new extraction shapes, Lean/axiom/full gate, private stage2 and formal submission results. No local Rust/Lean installation or execution was performed.

## Parent-proof review while the first R6 measurements run

Reviewed the actual frozen parent `Parse.lean` at SHA256 `d55744de52bb0469768f0bbfd73ffecbabf9899b63e0167469fd7bb79c6293c7`; this section contains a migration dependency map only. Core run 37594271466 and CPU run 37594267200 were dispatched by the root at commit 69e4c01. No new extraction shape or performance result is inferred from their dispatch.

### The relevant contract boundary

**VERIFIED from the parent proof:** all four changed core interfaces have postcondition `True` and no semantic precondition on search hints or optional table contents:

| Parent declaration | Parent line | Contract/role |
| --- | ---: | --- |
| `EH.bt_walk_loop_spec` | 4175 | Totality; invariant True; natural measure `maxd - depth` |
| `EH.bt_walk_spec` | 4189 | Totality for arbitrary scalar hints/cache values |
| `EH.find_pos_spec` | 4195 | Totality; composes checked indexing and search helpers |
| `EH.literal_bits_loop_spec` | 5114 | Totality; invariant True; natural measure `nblk - b` |
| `EH.literal_bits_spec` | 5128 | Totality for arbitrary fr/tlit/t5 slice lengths |
| `EH.optimize_spec` | 5463 | Totality; composes allocation, initialization and iteration |

The load-bearing decode proof remains in the unchanged `EH.match_len_loop_spec` / `match_len_spec` (3993/3999), `verified_spec` (4003), and `emit_all_loop_spec` / `emit_all_spec` (4016/4070). `verified_spec` supplies legal distance/length, bounds and actual byte equality to `emit_all_loop_spec`. That loop carries the decoded-prefix invariant and accepts any untrusted plan. `parse_mode_spec` (5637) uses this emitter result; final `Submission.parse_spec` (5660) composes the unchanged S/H dispatcher.

Consequently, satisfying the official LZ77 obligation does not require proving that the reused H3 prefix preserves the search cache, that t5 was unused, or that either candidate emits the parent's exact tokens. Those are the separate equivalence/performance claims under test. The correctness obligation still requires every new search/control path to terminate without a checked arithmetic/index failure; the True postconditions do not remove those requirements.

### Minimal h3prefix migration dependency

The initial repair surface is `bt_walk_loop_spec`, `bt_walk_spec`, then re-elaboration of `find_pos_spec`. The wrapper gains the two actual Rust scalar arguments; the loop captures must be taken from its forthcoming Funs, including their order and the real loop state. No candidate-specific tuple has been written or guessed.

Existing lower-level helpers remain available: `eq_spec`, `lt_spec`, `sel_spec`, `le64z_spec`, `ext_words_spec`, `push_slot_spec`, `setc_spec`, and the existing min/max/bit/arithmetic wrappers. Their postconditions are deliberately weak, sufficient for totality. In particular `le64z_spec` and `ext_words_spec` accept arbitrary offsets and prefix/limit values; safe reads, wrapping arithmetic and bounded helper loops protect the planner. The reused-prefix byte-validity/limit argument described above is needed for the **same-token claim**, not as a new precondition that must be threaded through all planner proofs.

The existing depth-decreasing argument should remain the right mathematical termination measure: the Rust body still increments depth once per iteration under `depth < maxd`. Confirm its actual extracted state projection rather than reusing a positional tuple projection blindly. The parent uses `T15!` for wrappers: unfold; simplify `lift`, `ite_ok`, Vec mutable deref and bind; `step*`; split residual branches; scalar arithmetic. Additional immutable captures may only require interface repair, but compiler acceptance is UNKNOWN until actual Funs and Lean are available.

Upstream `find_all_spec` -> `champ_spec` -> `optimize_spec`/`parse_mode_spec` and the final dispatcher should keep their existing exported statements. Re-elaborate them after repairing the changed local interface; do not redesign their contracts or the checked emitter merely to prove a planner heuristic.

### Minimal lazy-t5 migration dependency

The changed branch lives in `literal_bits_loop_spec`; its helper `init5_table_spec` (5111) is already total for any t5 slice, including empty. The loop's mathematical progress measure `nblk - b` does not depend on whether that optional helper runs. The else branch merely returns the current t5 slice. Existing `repeat (split <;> step*)` may already close the new branch after re-extraction, but this is a possibility, not a checked proof result.

`literal_bits_spec` has no t5-size assumption. `optimize_spec` allocates through `filled_spec` (3913), which supports arbitrary usize length and returns that length; a zero selected scratch size is covered by that same allocator theorem. The low-bit operation and selector are total. Therefore the smallest attempt after evidence arrives is to re-elaborate the unchanged parent proof against the new Slot, then repair only any changed branch/return binding in `literal_bits_loop_spec` and its wrappers. Do not introduce a semantic table-equality invariant merely because the optimization skips work.

The relevant distinction is precise: the official proof can accept any total model construction because the emitter rechecks the result; the equality claim additionally relies on `hi = Boolean & i5` being zero when the low bit is zero and on the optional table remaining unread. Finite token/output equality and eventual universal equivalence are separate from the gate obligation.

### Evidence needed before proof editing

For h3prefix, capture the new `h_bt_walk`, its loop/body and `h_find_pos` definitions. For lazy-t5, capture the new `h_literal_bits` loop/body and `h_optimize` definitions, including actual mutable-borrow return tuples. Check whether the old helper names and all unchanged semantic-emitter definitions remain identical before reuse. Only performance-supported candidates proceed to formal repair and a fresh full gate with unchanged limits.

This review appended notes only. Both Rust hashes and the common NOT_ADAPTED reference-proof hash were freshly re-read and remain exactly those in the frozen-output table. No candidate, manifest, generator, official source or CI file was changed during this review.

## Actual-extraction proof compatibility

The actual core-screen extraction from run 37594271466 has now been compared with the accepted parent's generated Slot. The exact minimal plan is in `evidence/round6/core-proof-plan.md`: h3prefix needs four localized argument-list/application replacements in two theorem interfaces; its 13-field loop state and return tuple are unchanged. lazy-t5 preserves every signature and loop tuple, so the first justified attempt is the original parent proof with zero edits. Its existing generic branch splitting appears to cover the new optional-table branch, but that proof has NOT_RUN and compatibility is not acceptance. No frozen source/proof/manifest/generator was edited for this review.


## Final core closure — both candidates stopped

**VERIFIED**, run 37594271466 / commit 69e4c010708d5c295836eb2b07c90b88ad091744, final receipts under `core-screen/gate`:

| Candidate | Primary block 1 | Primary block 2 | Primary mean | Auxiliary forward / reverse |
| --- | ---: | ---: | ---: | ---: |
| h3prefix | +1.468566% | +0.918819% | +1.193692% | +1.266385% / +1.272667% |
| lazy-t5 | +0.766484% | +0.237533% | +0.502008% | +0.231779% / +0.373164% |

All changes are total-time regressions relative to H16-base. The same-source shadow's primary mean is -0.068958%; its auxiliary forward/reverse values are +0.035752%/+0.051139%. Auxiliary results keep their separate same-process/order scope; they support stopping these two implementations rather than replacing the primary paired measurements.

Each candidate completed all 444 finite token/decode cases with zero differing or failed cases, harness return code 0. Fresh comparison of the primary raw JSONL confirms every public file's counted-token SHA, compressed-output SHA and encoded byte length matches H16-base in both blocks (28 files x 2). The public size axis stays 33.86321383735312%. Both actual extractions were accepted, but `state.json` has `gates={}` and candidate `gate=null`.

**Decision: stop both core routes and their proof migration.** Removing repeated source-level work did not yield a runtime gain in this experiment. Register pressure, added branches or layout effects remain possible explanations; no hardware-counter or profiler evidence is claimed to distinguish them. The recorded proof compatibility plan remains research documentation. Copied proofs stay NOT_ADAPTED; no full gate, formal submission, private result or payout exists for these candidates.
