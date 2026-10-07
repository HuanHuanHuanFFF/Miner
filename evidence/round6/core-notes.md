# Round 6 H16-small core candidates

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
