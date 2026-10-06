# Round4: uniform cost planning from public submission 402

## Scope and provenance

Source evidence: `references/round4-public-402/PROVENANCE.json`, retrieved `2026-10-06T18:58:39.763905+00:00` from the official published-source endpoint. Original source SHA256 `0be90fc1b0f8e751012d259cda70a84a160b812dcc134b4c7e96071797166dca`; proof SHA256 `e470d3d09d56b275556c36c5892ee68781a594cb7d6237255f009a62e18bce1d`. External miner attribution and original files remain in the reference directory, and each candidate manifest records the public hotkey, endpoint, receipt time and metadata digest.

**VERIFIED (source observation):** the original `route` contains exact-input-length cases. Also, A's internal `a_a_engine` calls `a_p_for`, which selects preset models using exact length plus configuration parameters. Merely bypassing the top-level route does not remove that second dependency. Neither first candidate uses any A-engine function.

The new entrypoints select one engine for every input. D's own first-32KiB histogram can vary costs and search budget by entropy. H's own odd-stride histogram and fixed-size-window repeat probes vary cost and stopping parameters. These are general input-content measurements; no new identity or exact-size routes are introduced.

## Two predeclared candidates

| Candidate | Entry | Mechanism and bounded budget |
| --- | --- | --- |
| `r4-parse-plan-d8` | `d_parse(input, out)` | 32KiB blocks; lazy search caches a main candidate, second candidate and up to three improving distance-code alternatives; learned literal/length/distance costs feed backward DP; checked emission. Main chain 512 -> 8, low-entropy 64 -> 4, lazy 128 -> 4, miss 32 -> 2, inner 24 -> 2. Inner search limited to matches <=8; exhaustive short-length relaxation 24 -> 8, main/second spans 16/8 -> 8/4. Original cost-learning schedule and first-four-block refinement remain. |
| `r4-parse-plan-h2` | `h_parse_mode(input, out, 0)` | Whole-input Pareto match cache; compares literal and lazy warm starts, then at most two learned-cost DP passes; checked emission. Tree depths 8 for larger inputs and 4 for small inputs; length relaxation tail 8/16. Mode 0 does not run the restart branch. |

`d_tables` constructs length/distance symbol and extra-bit tables; `d_seed` initializes literal costs from input byte frequencies; `d_lazy` records alternatives; `d_backward` prices candidate lengths and literal edges. This is a different parsing mechanism from fast3's single next-position gain comparison.

H builds a whole-file match cache, evaluates per-encoder-token-block models, and retains the lowest estimated encoded-cost plan across passes. Lowering H_ITERS bounds the normal iterative stage, while preserving its content-dependent early stop. The conservative static closure includes helper branches unreachable in fixed mode 0; the claim of no restart follows from `h_iterate`'s explicit mode guard, not from pretending those functions disappeared.

## Proof and routing audit

The generator locks both original file hashes, replaces only the exported Rust entry and the listed constants, and replaces only the final `Submission.parse_spec` proof body:

- D: `rw [slot.parse]; exact ED.parse_spec input out hlen`.
- H: `rw [slot.parse]; exact EH.parse_mode_spec input out 0#usize hlen`.

All engine proof text is retained. These edits are **not** a fresh proof result.

**VERIFIED (local generator checks):** `scripts/make-round4-planner.py --check` exactly reconstructs every source, proof and manifest. Source/proof sizes are below 524288 bytes each. A conservative direct-call closure from `parse` contains 37 functions for D and 148 for H. It excludes `route`, `parse_c0`, `parse_c1`, `parse_c2`, `a_p_for`, and every `a_*` function. Complete closure lists are in each manifest. The generator also rejects active comparisons of input length / `n` to large exact numeric sizes. This lexical audit is not official extraction or evidence about deployment.

| Candidate | Source SHA256 | Proof SHA256 | Source/proof bytes |
| --- | --- | --- | --- |
| `r4-parse-plan-d8` | `c31807dadd8b0a459e759e0fe63656c35aee84251b3dc242c627f8748f357ab9` | `945c24e54b9bf479e2f83eac67c2dd59d0689835425c3685e8eb2053d02d9621` | 271215 / 405919 |
| `r4-parse-plan-h2` | `76cd23e457013c66d2502cc8f46966134013db6e64e8450162843f7a36d5ea68` | `f14e3c7b8a5c89d84dcffdb5ffc43e4963a043538c42dd39e228cd351145ffaf` | 271228 / 405932 |

## Expected tradeoff and stop conditions

**INFERRED:** both candidates may reduce compressed size by giving the planner alternatives and symbol costs that fast3 ignores. They necessarily perform additional scans, state writes and match verification, so low search/iteration budgets do not establish acceptable speed. D aims at the cheaper end of the cost-planning family; H tests whether two whole-file cost passes provide a larger size reduction.

Screen both against fast3 with the fixed public paired benchmark, and inspect synthetic input behavior if either is useful. Stop this initial family if size fails to improve or the new time/size pair is clearly dominated; do not launch additional parameter variations before the two candidates return evidence.

**UNKNOWN:** Rust build, official extraction, Lean obligation, axiom whitelist, round trip, public paired time/size, synthetic behavior, private stage2, admission and payout. Original #402's mixed exact-length portfolio score is not a matched same-engine anchor for either uniform candidate. Its formal-to-public transfer is **UNKNOWN**; the #427 multiplier is at most a heuristic, not validation.

No local Rust/Lean tools, CI dispatch, commits, pushes, submission or wallet operations were performed by this worker.

## C-screen evidence and two independent H-budget steps

**VERIFIED (public screen, 2026-10-06):** `evidence/round4/37520076712/screen/analysis.json` and raw JSONL repetitions give H2 `(time 4.324145365, size 34.065519888%)` and D8 `(1.279206855, 34.254324750%)`. These are public paired coordinates, not formal results. H2 saves another 0.188805 percentage points of the size axis over D8 at approximately 3.045 additional time-axis units.

Per-file output-size differences, independently recomputed from block 1, show H2's largest extra size savings over D8 at dump.sql.txt (-0.032857 axis pp), prose.txt (-0.022905), sourcemap.map.txt (-0.020071), binary.db.bin (-0.015650), and metrics.csv.txt (-0.014192). H2 is worse on weights-f32.bin (+0.029765 axis pp) and slightly worse on both tiny text files. File names locate evidence only; the new parsers never inspect them.

The current logs do not report actual H iteration counts, cache-candidate counts, search-depth exhaustion, or the contribution of omitted short lengths. Two candidate-generation budgets can therefore be separated without asserting an unmeasured bottleneck:

| Candidate | Delta from H2 | Mechanism and limitation |
| --- | --- | --- |
| `r4-parse-plan-h4` | H_ITERS 2 -> 4 only | Permit additional learned-cost DP passes over the same cached matches. `h_stop_rule` and minimum-pass settings remain unchanged, so the candidate can still stop before four passes. Identical output would not establish that four passes were executed. |
| `r4-parse-plan-h2-deep16` | Larger-input tree depths 8 -> 16; small-input depth 4 -> 8 | Same two-pass cap and length relaxation; search for additional length/distance alternatives before building the cache. Pricing iterations cannot recover alternatives omitted during search, so this tests a separate possible bottleneck. |

**INFERRED target:** a public size near 33.86% is a screening hypothesis derived from the #427 multiplier, not a validated transfer for the H family. The new timing is also unknown; increasing a cap is not a guarantee of staying under the formal time bound. Both policies retain the uniform mode-0 entry, checked emission, and no-restart mode. A future content-based H/D choice may be worth investigating if these budgets are expensive, but no such router is implemented here.

**VERIFIED (local source checks):** `make-round4-planner.py --check` reconstructs both frozen initial planners plus the two additions. The generator now has repeatable `--only`, used to create just these additions. The three symbol candidates also pass their own `--check`; no frozen candidate file has a Git content diff. New parsers remain below the per-file size limit, use the same 148-function static H closure, and exclude the original exact-length routes and all A functions.

- H4 source SHA256: `a9a525afb91ea0163d7b785c751264c3d27926359e3e67357aea43a32eb54298`.
- H2-deep16 source SHA256: `2fcc954ee157dae033cc560d370e5aa553709ce684d90e0c1a329aafeb64786c`.
- Both proof SHA256: `f14e3c7b8a5c89d84dcffdb5ffc43e4963a043538c42dd39e228cd351145ffaf`, retaining the direct `EH.parse_mode_spec` entry proof. This is not a new gate result.

**UNKNOWN:** new public time/size, actual iterations/cache changes, extraction/Lean/axiom acceptance, private stage2, online admission, and payment. No further budget combinations are generated before these two measured comparisons return.

## E-screen evidence and combined H staircase

**VERIFIED (public screening):** `37523141792/screen/analysis.json` records H2-deep16 at `(4.674739, 33.974638%)` and H4 at `(4.811351, 33.998955%)`. Relative to H2's deterministic public output size, these reduce the size axis by about 0.090882 and 0.066565 percentage points, respectively. H2 came from a different runner, so these cross-run time coordinates do not by themselves give a precise causal incremental timing cost.

The E token profile has `status=DIAGNOSTIC_OK`, 84 file records and no failures. An independent read matched all three profiled candidates' 28 token hashes against their official benchmark records and checked every `decode_checked` flag. Its candidates are fast3, symbol-len6 and symbol-block512. It does not report H iteration counts or H match-cache coverage, so no such profile evidence is assumed.

The independently measured search and iteration steps justify exactly three further constant-only points, all with unchanged length relaxation (`H_CHW=8`, `H_CHWS=16`), mode 0 and the existing early-stop rule:

| Candidate | Iteration cap | Larger/small tree depth | Question |
| --- | --- | --- | --- |
| `r4-parse-plan-h4-deep16` | 4 | 16 / 8 | Do the two measured improvements combine? |
| `r4-parse-plan-h4-deep32` | 4 | 32 / 16 | Does another search-depth step provide useful alternatives? |
| `r4-parse-plan-h8-deep32` | 8 | 32 / 16 | Does more model refinement help once that larger cache is available? |

**INFERRED:** a size axis at or below roughly 33.86% and time at or below roughly 9 are current screening targets. The #427 transfer behind that target remains a cross-family hypothesis, and neither target is a gate/admission/payment result. The iteration cap still permits rather than forces passes. Higher depth and extra passes can interact, so the two earlier size gains must not simply be added as a prediction.

All seven planner variants pass their generator's byte-for-byte `--check`; the four already measured planner directories retain exact bytes. Static entry closure and the direct EH proof interface remain the same. Each new parser still needs a fresh gate at its own exact source hash.

- H4-deep16 source: `950cef398fe8e5f7bf96cba97c6a3702d7d2e1ef065f6bdfaddb5ad3fda0ba4a`.
- H4-deep32 source: `4b15ae9dee3ead2f5b7450dcca08c9651fa45ef2bd2d0b0c332079196402e523`.
- H8-deep32 source: `a7115baa44afa81dc761cb7435872db264e6dea6a3013acec3fb9d768e81f83c`.
- Shared proof: `f14e3c7b8a5c89d84dcffdb5ffc43e4963a043538c42dd39e228cd351145ffaf`.

**UNKNOWN:** new time/size, actual H passes and cache changes, fresh gate, private stage2, online admission, and rewards.

## Read-only H search/cost audit and two prepared variants

Source anchor throughout this section: frozen `candidates/r4-parse-plan-h4-deep32/parse.rs`, source SHA256 `4b15ae9dee3ead2f5b7450dcca08c9651fa45ef2bd2d0b0c332079196402e523`. Its G measurement was still running when the following hypotheses were prepared; no parent benefit is presumed.

### What the length window removes

**VERIFIED (source):** `h_prune_pos` and `h_relax_pos` process an ordinary cached maximum length `h` with lower bound `lo`: eligible lengths up to 10 are considered explicitly, while lengths >=11 start at `max(lo, 11, h-chw)`. Thus CHW=8 can leave only the final nine lengths of a long interval, not every shorter length. For a sole ordinary cached length 100, it tries 3..10 and 92..100, omitting 11..91. Inherited entries carrying the +512 flag try only their full length. Lengths within one DEFLATE length-code bucket use a range-minimum query; they are not all separate scalar relaxations.

`h_push_slot1` with `H_SLOTM=1` replaces a shorter entry by a later longer entry when both have the same distance code. With unrestricted truncation, the longer match can represent every shorter prefix at the same distance-code cost. With CHW narrowing, deleting the shorter entry can also delete a useful length anchor: replacing length 20 by 100 removes the 12..20 interval that the shorter entry would have offered. This is a concrete interaction between two approximations. It does not establish how often the case occurs in the public corpus.

The first query-recording pass also prunes alternatives farther than `H_PM=128` cost units (8 bits) from the running best, with an initial `H_MDEL=24` (1.5-bit) match discount. Later passes replay only the retained queries (`h_dp_pass` chooses `h_pass_items` once `pr!=0`). Extra pricing iterations therefore cannot recover lengths absent from either the match cache or this first retained-query set.

### Cost model versus official encoding

**VERIFIED (source and bounded formula checks):** `h_walk` re-counts exactly H_BT=16384 tokens per block, matching the official encoder's block criterion. Its length and distance code/extra-bit formulas were independently translated and checked against every official legal length (3..258) and distance (1..32768). Its RLE frequency/extra-bit formulas matched the official greedy RLE for all code-length values 0..15 and runs 1..318. These are local arithmetic checks, not execution of the candidate Rust or a full encoder-equivalence proof.

The search costs still differ deliberately from emitted bits. `h_sym_costs` uses 25% approximate entropy and 75% Huffman-length cost for dynamic blocks (`H_EW=2` out of 8). Missing symbols use H_UNUSED=12 and an entropy prior. Starting with pass 2, H_OV=3 overrelaxes cost changes beyond the newly fitted value. DP uses raw block boundaries from the previous walk; its new path is then re-counted into actual 16384-token blocks, so the pricing boundary can lag by one pass. Header costs are included when a completed path is evaluated, but are not charged as per-symbol activation costs during the DP.

`h_block_bits` includes dynamic header/RLE costs, fixed costs, and stored eligibility. It sums bit costs and omits actual stream alignment/final byte padding; stored writing can pay alignment dependent on the preceding stream. The dynamic tree builder has an ordinary-Huffman fast path with package-merge fallback, while the official encoder always uses package-merge. Its comments calling the result exact are not a proof that all tie cases or whole-stream byte counts agree. No measured mismatch is asserted here. The bounded table/RLE checks do not cover that question.

### Best plan and early stop

**VERIFIED (source):** `h_iterate` keeps the best evaluated plan using two choice buffers. `r = h_eval_mode(...)` is the sum of per-block `h_block_bits/4`; only `r < best` updates `bh`, and the final copy uses the `bh` buffer. If no pass improves, `bh=2` leaves the initial best literal/lazy plan. It does not blindly return the last pass.

The stopping rule compares previous-pass `prev` with current `r`, not global best. Under H_RALPHA=2 it computes `((gain*r)/n*r)/n`, where `gain=max(prev-r,0)` and the source performs integer division after each product, multiplies the first-pass threshold by H_F1=8, and respects the minimum-pass count. A regression has zero gain and can stop once the minimum is reached; the best buffer remains protected, but further nonmonotonic cost fitting is not explored. Current receipts do not report these per-pass estimates or actual pass counts.

### Prepared minimal experiments

At the main thread's request, exactly two constant-only derivatives of the frozen H4-deep32 parent are prepared:

| Candidate | Exact delta from parent | Expected distinction |
| --- | --- | --- |
| `r4-parse-plan-h4-deep32-wide` | H_CHW 8 -> 16; H_CHWS 16 -> 32 | Restore additional middle lengths without changing the search cache. This also enables the level-4 range-minimum update on larger inputs, adding work per DP position. |
| `r4-parse-plan-h4-deep32-noslot` | H_SLOTM 1 -> 0 | Preserve shorter same-distance-code cache entries as length anchors, retaining the original narrow length windows. More cache entries and queries may increase time/memory. |

Neither adds search depth, iterations, routing, loops, or proof state. The existing totality proofs and verified emitter are retained; they establish no optimality or performance property. A fresh official gate is required for each exact source. A roughly 0.05 percentage-point size improvement is a hypothesis to test, not a prediction from this audit.

**VERIFIED (local generation):** all nine planner variants pass `make-round4-planner.py --check`. Each new manifest contains the parent source/proof SHA256, parent path and exact delta; generation checks the parent hashes. All earlier candidates retain exact bytes.

- wide source: `3787e8f8f5fc9fa9674e21462b0600c9f3fdc86c175f40d673f0c3c3cf25a6e3`.
- noslot source: `3a6aa5f4514a02526fbe1043b29e4e75aeea2e32eebf35a0984328c516f584d3`.
- Shared proof: `f14e3c7b8a5c89d84dcffdb5ffc43e4963a043538c42dd39e228cd351145ffaf`.

Both are prepared only, awaiting the main thread's decision after G results. Build, gate, performance, stage2 and online outcomes remain **UNKNOWN**.

## H-only core after the E elaboration timeout

**VERIFIED (failure receipt):** the E H4 gate in `evidence/round4/37523141792/gate/r4-parse-plan-h4-gate.log` passed intake, source policy/static checks and fresh Charon/Aeneas extraction. Extraction took 174.8 seconds, followed by successful lake calls of 2.8 and 111.4 seconds. Statement elaboration then timed out at the unchanged official 900-second limit. The captured lake log contains the timeout, not an earlier Lean logic error; it does not establish that elaboration would eventually succeed. The logs were read with read-only elevation because the downloaded directory was inaccessible to the sandbox. No ACL was modified.

**VERIFIED (G public screening):** the receipt reports H8-deep32 `(5.718398003, 33.875400384%)`, H4-deep32 `(5.309592262, 33.893514202%)`, and H4-deep16 `(5.154002353, 33.903047006%)`. These still lack the fresh H-family gate. The next action is therefore proof/extraction minimization, not a relaxation of the verifier or a correctness claim from benchmark round trips.

One new candidate, `candidates/r4-parse-h8d32-core`, is generated from frozen H8-deep32 source `a7115baa44afa81dc761cb7435872db264e6dea6a3013acec3fb9d768e81f83c` and proof `f14e3c7b8a5c89d84dcffdb5ffc43e4963a043538c42dd39e228cd351145ffaf`.

| Retained dependency | Static evidence |
| --- | --- |
| Rust `parse` plus all 147 `h_*` functions | Direct-call closure is exactly 148 functions; each declaration, adjacent attribute and body is copied verbatim from the frozen parent. |
| 85 Rust constants | Transitive identifiers from the retained functions and proof references; each complete constant declaration is copied verbatim. |
| Original `Submission` header | Imports `Lz77` and `Slot`, opens the same namespaces, and preserves existing options. |
| Shared `T9!` / `T10!` proof macros | Defined between the original EA and ED namespaces and used by EH's `h_match_len` proofs. Both are copied verbatim; omitting them would leave missing proof dependencies. |
| Complete `namespace EH` | 1821-line block retained verbatim, including verified-emitter correctness and H totality/loop proofs. All 225 `slot.h_*` references including generated loop references map to retained Rust function owners. |
| Original final `Submission.parse_spec` | Exact statement and `EH.parse_mode_spec input out 0#usize hlen` body retained. |

Removed: Rust A/D engines, the old exact-length portfolio, their unused constants/types, EA/ED proof namespaces, and outer router proofs. No custom decode invariant from A or D is imported into EH; EH carries its own `Matches`/emit lemmas and uses the public `LZ77` library.

The complete retained/removed function and constant lists, proof block SHA256 values and source line ranges, plus extracted-reference-to-function-owner mapping are in `dependency-audit.json` beside the new candidate. Additional read-only checks found no omitted Submission-level `attribute`, `open` or declaration between the removed namespaces: only the retained T9/T10 macros occur there. Retained references to known Rust function names are direct calls or explicitly shadowed local identifiers; no implicit function-value dependency was found.

An additional attribute audit over the entire removed proof prefix found no non-local `@[...]` registrations. The explicit `attribute` commands there are also `local ... in` declarations. Thus no omitted global simplification/step registration was found that EH would silently inherit from the removed engines. This remains a source audit; Lean elaboration is the decisive check.

`scripts/make-round4-hcore.py` defaults to generating only the H8/depth32 core. It also contains fixed-SHA recipes for the prepared H4/depth32 wide and noslot parents; both recipes were evaluated and audited in memory without creating their candidate directories. Existing frozen parser/proof files are unchanged.

| File | Parent bytes | Core bytes / lines | Core SHA256 |
| --- | --- | --- | --- |
| parse.rs | 271232 | 71184 / 2275 | `916f3a0b5f64b17919c7e4871f878ef2827530a9e3bf577020d8865e61b26953` |
| Parse.lean | 405932 | 95901 / 1867 | `13f23fc46a6d18283aeb339f949cca102761133d6e1ff9b3a1007cd8b7926a46` |

**VERIFIED locally:** generation and exact `--check` pass; retained source/proof text and declared dependency coverage are checked. No `sorry`, `admit` or new axiom is present. The official obligation wrapper and axiom whitelist remain external and unchanged; neither the 900-second limit nor any official file is modified.

**INFERRED:** removing roughly three quarters of the proof text and non-H extracted program should reduce work. Byte/line reduction is not a measured proportional time reduction. Retaining the same H bodies/constants is strong static evidence for unchanged algorithm policy, but compiled layout and runtime may change.

**UNKNOWN until fresh CI:** extracted names/signatures, Lean dependency completeness, `LZ77.Obligation` and axiom acceptance, elaboration within 900 seconds, round trip, finite-corpus token/output equivalence with the parent, timing, private stage2, admission and reward. The original timeout is not marked fixed yet.

## Three H-core budget candidates

Prepared from the frozen H8/depth32 core while its first official gate is running. Each candidate retains the same 95901-byte proof and H-only dependency structure, with no return to the full 402 proof. `scripts/make-round4-hcore-tune.py` SHA-locks the ancestor source/proof, records the direct parent, and verifies that reversing only the declared constant substitutions restores that parent's source byte-for-byte.

| Candidate | Direct parent | Exact change |
| --- | --- | --- |
| `r4-parse-h16d32-core` | `r4-parse-h8d32-core` | H_ITERS 8 -> 16 |
| `r4-parse-h16d64-core` | `r4-parse-h16d32-core` | H_BTD/H_BTDMC/H_BTDX 32 -> 64; H_BTDS 16 -> 32 |
| `r4-parse-h16d32-pm256-core` | `r4-parse-h16d32-core` | H_PM 128 -> 256 |

**VERIFIED (source review):** all listed constants affect the live H mode-0 path. H_ITERS is the iteration cap; its proof measure refers to that constant. The tree-walk totality theorem is generic in `maxd`, without a 32-depth premise. H_PM appears in guarded/wrapping first-pass query-retention arithmetic, not in an allocation-size or fixed-array-bound assumption; doubling it changes an eight-bit modeled cost margin to sixteen bits. On inputs stopping after one pass without retained queries it may have no effect. No hard-coded old-value restriction was found in these proof statements, but this is not fresh Lean acceptance.

**INFERRED:** sixteen permitted passes may recover remaining model-refit gains, deeper search may supply additional match alternatives, and a larger retained-query margin may let later models reconsider first-pass alternatives. Existing early stopping and the first-pass candidate set remain important limits; increasing the cap alone need not execute more iterations. Larger depth/query sets may consume additional time and memory. Public time <10 is a required measured target, not a proven runtime bound or a promise.

**VERIFIED locally:** all three tune candidates and the unchanged H8 core pass their respective generator `--check`; the original core has no content diff. Source hashes:

- H16/depth32: `c1f9ea4621178e0f815066e43e5a577ec8262b9e188dfd703877f54d66905206`.
- H16/depth64: `ba3c16422a5fc9432c41d80c0ad0ab5657605c1e020d14b7e1135e430ce3a7ee`.
- H16/depth32/PM256: `b115f09b2c3c445b90054de5305131d498e5ad869157afa6bb168a9d1b5f2920`.
- Shared proof: `13f23fc46a6d18283aeb339f949cca102761133d6e1ff9b3a1007cd8b7926a46`.

Each parser is 71185 bytes. New official extraction, proof/axiom checks, public performance, stage2 and online outcomes remain **UNKNOWN**. No CI, push, submission or wallet operation was performed by this worker.

## Uniform H modes and restart experiments

**VERIFIED (H-core source):** mode is reduced modulo 8 inside `h_parse_mode`, but the exported entry can select one fixed mode for every input. Modes 1, 2 and 3 halve the per-content `gk` through `h_mode_gk`, affecting both predicted one-pass behavior and the normal early-stop threshold. They retain the same literal/lazy initial-plan comparison and high-entropy seed logic. Although `h_optimize` computes a mode-dependent `ew`, this source's `h_eval_mode` ignores that parameter and calls `h_eval_blocks` directly; it is not evidence of a changed initial or entropy model.

| Mode | Normal stage | Additional stage |
| --- | --- | --- |
| 1 | Existing iteration cap, smaller stopping threshold | No restart |
| 2 | Same smaller stopping threshold | At most one qualified restart |
| 3 | Same smaller stopping threshold | At most two qualified restarts |

A restart is qualified only when the existing `h_classify(input) % 4 == 0`. This classifier uses general fixed-window repeat coverage, a strided byte histogram/entropy, and a general small-input threshold; no removed exact-length portfolio or filename routing is involved. Each restart re-counts the current best plan, fits its tables, perturbs symbol costs deterministically by up to +/-16 units (one modeled bit), and performs exactly three DP/walk/evaluate steps. Each step copies its plan only if its evaluated cost improves. The match cache is reused; when the normal stage retained queries, the restart also reuses that pruned query set, so it does not rediscover deleted alternatives. It adds another classification pass and repeated DP/statistics/table work, not another tree search.

Exactly two candidates are generated from frozen `r4-parse-h8d32-core`:

| Candidate | Entry mode / normal cap | Purpose |
| --- | --- | --- |
| `r4-parse-hmode-1-i8` | 1 / 8 | Isolate the smaller stopping threshold with the same eight-pass cap; no restart. |
| `r4-parse-hmode-2-i4` | 2 / 4 | Budget at most four normal passes plus three restart steps on qualified inputs. This combines the smaller stopping threshold, restart and lower normal cap; it is not a pure one-factor restart attribution. |

Mode 3 is not generated in this batch: up to six added DP steps would have a larger unmeasured time cost. A public time axis below 10 and an additional size improvement of roughly 0.01--0.03 percentage points are hypotheses, not predictions or formal eligibility claims.

`scripts/make-round4-hcore-modes.py` updates the exported Rust mode and final Lean `exact EH.parse_mode_spec input out <mode>#usize hlen` together. Reverse substitutions restore all parent source/proof bytes; all engine bodies, emission proofs and the 148-function closure are retained. The original core and tune candidates have no content changes. Generation and `--check` pass, but fresh extraction/gates remain required.

- mode1/i8 source: `87550e2af37eb409f6d23f5ee23ca70b6fc55ace6b28bca1b85db38929d99a79`.
- mode1/i8 proof: `ea44caf8730aa9dab5508cd49f8c3c9cf7277cfbba2c7084fe419670c723edc2`.
- mode2/i4 source: `38171d3302345e1cb3eac22bebda1787a0cf956e5da35d00cca76bd9158dd4c7`.
- mode2/i4 proof: `7b33e0f50428d2629af0f93151f9fff3110409b57b8add5fcc06c6d61f9d216b`.

Each parser/proof is 71184/95901 bytes. Actual normal/restart pass counts, public time/size, fresh gate, private stage2 and online outcomes remain **UNKNOWN**.

## Confirmed H-core gate success

**VERIFIED:** CI `37532140321` completed successfully. Its gate input files were independently compared byte-for-byte with current `r4-parse-h8d32-core`: source `916f3a0b5f64b17919c7e4871f878ef2827530a9e3bf577020d8865e61b26953`, proof `13f23fc46a6d18283aeb339f949cca102761133d6e1ff9b3a1007cd8b7926a46`.

Fresh extraction took 12.6 seconds; the statement/elaboration lake call took 94.9 seconds. Verification through the axiom stage was accepted in 150.2 seconds under the unchanged 900-second limit. `LZ77.Obligation slot.parse` typechecked, and `accepted` depended only on `Classical.choice`, `Quot.sound`, and `propext`. The subsequent complete 28-file public gate reported `accepted=true`, with 15930000 input bytes and 4870697 output bytes. Evidence: `evidence/round4/37532140321/gate/r4-parse-h8d32-core-gate.log` and its gate JSON.

The finite equivalence diagnostic reports 444 core-versus-parent cases, zero differences/failures, and return code 0 (`equivalence-research.json`). The run also records eight fixed generated inputs, two core measurement blocks, and no recorded failures in the synthetic validation. These checks do not establish all-input token equivalence or observe private stage2.

The paired public analysis records core time 5.447409947 and size 33.875400384%; the full parent has the same size with time about 5.4282. Removing unreachable code/proof solved the observed elaboration-time failure for this exact core. No algorithm speed improvement is claimed from the small timing difference, which can include layout and measurement variation.

This current exact-hash receipt supersedes the initial core manifest's generation-time UNKNOWN status; frozen manifests remain untouched. It does not certify different H16 constants or mode-entry variants: each still requires its own fresh gate. Private stage2, formal admission/ranking and reward for the core remain **UNKNOWN**.

## One public299 EOB model-count experiment

**VERIFIED (source):** in `references/round4-public-299/parse.rs`, `a_walk` sets `lf[256]=1` after every walk. `a_sample_pass` scales every entry 0..511, including 256, by A_SAMPLE and sums across sampled segments. `a_engine` then computes `sl=bl+lf`; when the encoder block is still partial it carries `sl` back into `bl`. Therefore the observed model count for EOB can exceed one within a single 16384-token block, whereas the official encoder adds one EOB per block.

The single requested candidate, `r4-parse-299-eob1`, inserts only `sl[256]=1` immediately after the unique `a_add_counts(&mut sl, &bl, &lf, &mut sd, &bd, &df)` call in `a_engine`. All public299 classifier/configuration, depths, passes, other counts and emitter code remain unchanged. Root/Luna's alt299 candidates and scripts are not modified.

**Model limit:** `a_set_costs_huff` subsequently adds one pseudocount to each of the 286 litlen symbols, including EOB. This candidate therefore normalizes the observed EOB component; it intentionally retains the existing smoothing policy, whose Huffman working count for EOB becomes two. It is not a claim that the full cost model now equals the official encoder. The previous accumulated count may have served useful regularization, so an output-size improvement is not assumed.

**Proof review:** `a_engine_loop1_loop0_spec` carries bounds for the planned window, end position and token count, but no invariant fixing `sl` frequencies. The new statement is a fixed in-range write to index 256 of a 512-element array. It adds no loop, branch or loop-state field, and is after the theorem's sampled/full-pass cut, where the existing proof continues with `step*`. The complete original 279475-byte proof is copied; fresh extraction and gate are still necessary.

`scripts/make-round4-eob.py --check` passes, locks the original public299 source/proof SHA256 values, and verifies that removing the one inserted line restores the original source exactly. New source SHA256 `f22c4fc3fff60f4640a9d1fb3d54a2be94a4415c914262514c4548b58215582f` (105089 bytes); proof SHA256 `9b77b3523cbf7044aaffa11b6fd9676b3615ca4bf148b43b3cb92da4073b3e3d` (279475 bytes). Attribution and the source endpoint remain linked from its manifest.

**UNKNOWN:** compilation, extraction, proof/axiom acceptance, public time/size and online outcomes of eob1. No further count/model variants are generated in this batch.

## Final two restart configurations

**VERIFIED (K public screen):** `evidence/round4/37537479001/screen/analysis.json` gives mode2/i4 `(5.710209048, 33.882881080%)`, versus same-run H4/depth32 `(5.106794290, 33.893514202%)`: the mode2 configuration saves 0.010633 percentage points for roughly 0.603415 additional time-axis units. It includes the halved stopping threshold as well as restart, so the exact share attributable to restart alone is not isolated by this pair. Mode1/i8 gives `(5.621726124, 33.874432867%)`, compared with H8 core `(5.463136440, 33.875400384%)`.

At the main thread's request, the last two new H configurations are prepared from the same frozen H8/depth32 core:

- `r4-parse-hmode-2-i8`: mode 2, eight normal passes permitted, at most one qualified three-step restart.
- `r4-parse-hmode-3-i8`: mode 3, eight normal passes permitted, at most two qualified three-step restarts with distinct deterministic seeds.

Tree depth, PM, length windows and every engine body remain unchanged. Only the global Rust entry mode and corresponding Lean theorem literal change from the H8 core. Both normal early stopping and the existing content condition for restart remain active. The measured K increment is a budget reference, not a guarantee that either new configuration stays below time 10 or improves size.

`make-round4-hcore-modes.py` now supports repeatable `--only`, which was used to write just these two candidates. All four mode variants pass exact `--check`; both old mode candidates and the core have no content diff. Source/proof hashes:

- mode2/i8: `ca06c01a8099cc78b215236df5477b8a849f09e7c447ca7bdf5edc0546254f23` / `7b33e0f50428d2629af0f93151f9fff3110409b57b8add5fcc06c6d61f9d216b`.
- mode3/i8: `1c94d7dec959a9862fa79dd862df673abec80556d2f139924094e0a6a78ed840` / `edab13f3296ddd86cb2db928baa1050f5fdb532fc0facc671a4236478995b34e`.

Each source/proof is 71184/95901 bytes. Fresh gate, independent public performance, private stage2, formal admission and payout remain **UNKNOWN**. No further new H proposals are generated after this final pair.

## Time-bounded public299 DP/RMQ research attempt

At the main thread's request, one structural planner experiment was prepared before the `2026-10-06 22:50 UTC` cutoff. This is deliberately a **research-only Rust candidate with an unadapted reference proof**, not a gate-ready submission.

**VERIFIED (source):** `a_dp_pass` compares each candidate length using unsigned packed values
`(cost[at].wrapping_add(lc[len]).wrapping_add(base) << 9) | len`.
Only the low 23 cost bits survive the shift. A plain unsigned minimum of original costs is therefore insufficient: adding the shared bias can rotate modular order. Equal packed costs prefer shorter length because length occupies the low nine bits; the surrounding strict `<` keeps the existing candidate/distance on a full tie.

The sole candidate `r4-dp299-rmq` maintains a backward-built 512-position ring with six min/max levels (widths 1,2,4,8,16,32). Each key is `(cost mod 2^23, absolute position)`. A complete length-code bucket of width at least four uses its cached minimum only if the minimum and maximum remain in order after adding the current length/distance/bias value modulo 2^23. Crossing that cut falls back to the original scalar expression. Partial buckets and nonuniform `lc` buckets also fall back; `lc` uniformity is explicitly checked once per DP call, rather than assumed from the cost model. Fixed/sentinel candidates remain scalar.

The final normal length bucket is 227..257 (31 values), since length 258 has its own code. It is queried as two overlapping width-16 ranges, covering exactly those 31 positions. The cache is initialized in reverse over the same zeroed future-cost span and updated after each completed DP position. All existing routing/configuration, outer strict comparisons, token encoding, checked emitter, and official encoder remain unchanged.

**VERIFIED (local arithmetic model only):** deterministic Python checks with seed 429966 covered 347600 range queries including width 31, 4000 mixed partial/nonuniform whole queries, and 168955 modular-wrap fallbacks with zero mismatches. Equal-cost cases and ring reuse beyond 512 positions are included. An intermediate model incorrectly treated the 31-value bucket as a single 16-range; the expanded check exposed that mismatch. Both final Rust logic and the model now explicitly combine two width-16 ranges. These checks do not compile or execute the Rust and cannot establish public or all-input token equivalence.

Final source, frozen at `22:38 UTC`: `f14f364e2383b55a8b5c6fd180101a272c87ee9f681f042f5da1c8351a3b99dd`, 109316 bytes. The earlier preliminary c40a source is superseded and must not be confused with this final hash. `scripts/make-round4-dp.py --check` passes and `--model-check` reproduces the arithmetic checks.

**Proof status — NOT_ADAPTED:** `Parse.lean` is copied from public299 solely as the migration reference, SHA256 `9b77b3523cbf7044aaffa11b6fd9676b3615ca4bf148b43b3cb92da4073b3e3d` (279475 bytes). It is not a proof for the new parser. Required work includes totality of the new cache helpers, query-loop progress and array/vector bounds, adapting `a_dp_pass` to the additional min/max state and uniform-mask capture, and replacing references to removed scalar inner loops. No sorry, axiom, weakened obligation or verifier change is introduced to conceal this gap. Research CI must keep `gate_candidates=[]` until proof migration is completed.

**INFERRED performance tradeoff:** full long buckets replace many repeated packed-cost comparisons with cached extrema checks, but every DP position now pays cache updates and memory traffic, and each pass checks the length-cost buckets. Short-match or frequent-wrap cases can regress. No speedup or unchanged output is claimed before CI Rust compilation and finite token/decode equivalence against original public299, followed by the paired public benchmark. Source/code-layout effects and exact input coverage must be recorded at the final source hash.

**UNKNOWN:** actual Rust compilation, extracted signatures, finite token equivalence, speed/size, a completed proof, official gate, private stage2, admission and rewards. The staged research variant is the only candidate in this direction; no further H parameters or official files were changed.

## Final static counterexample audit of the frozen RMQ source

Audit target: source `f14f364e2383b55a8b5c6fd180101a272c87ee9f681f042f5da1c8351a3b99dd`, submitted by the main thread to research CI `37542714311` at commit `4e22f24` with no gate candidates. This audit changes only these notes. It does not report CI compilation/equivalence results and does not reinterpret the Python model as Rust execution.

**Finding:** no concrete counterexample was found under the exported `parse` path's actual preconditions. The argument below is a source-level audit, not a completed Lean equivalence theorem.

1. **Initialization and order.** Original `a_dp_pass` zeros cost indices `pe..min(cl-1,pe+258)`. `r4_rmq_init` fills the same positions in descending order, allowing every valid higher-level interval to be assembled from already initialized later positions. Intervals extending beyond that initialized end may contain meaningless cells, but no valid query uses them: every query ends at `stop < cl` and `stop <= i+258`, with the first DP position `i=pe-1`. During the backward walk, each new `cost[i]` is cached only after its final assignment. Future costs queried at `i+3..i+258` are already fixed and do not change later within this DP call. A fresh cache is created for every call, including each sample/full pass.
2. **Ring reuse.** Rewriting the physical slot of position `i` discards information for `i+512`. Queries need at most `i+258`, and all RMQ intervals are constrained to their complete length bucket within that range. A cached future interval needed by the current query therefore cannot have its start slot overwritten. Stored interval values are keys, not live pointers to lower cache levels, so later lower-level updates do not mutate an already computed interval.
3. **31-value boundary.** The exceptional final ordinary bucket 227..257 uses `[at,at+15]` and `[at+15,at+30]`. Their union contains exactly 31 positions; overlap is harmless for min/max. Length 258 is never included and follows its own scalar one-value bucket. All other accelerated widths are 4,8,16 or 32.
4. **Modular order and ties.** Let M=2^23 and r_j=cost[j] mod M. In a uniform bucket the old comparison is `(((r_j+C) mod M)<<9) | (j-i)` for the shared C. Adding C has at most one order cut. If that cut lies between the minimum and maximum residues, the transformed minimum is strictly greater than the transformed maximum, forcing scalar fallback. Otherwise order is preserved, and the cached minimum is sufficient. Equal residues have equal translated costs even if the original u32 values differed in discarded high bits; the key's lower position field chooses smaller j and hence shorter length. Original outer strict `<` comparisons, including literal-versus-match and equal-length/distance-candidate ties, remain untouched.
5. **Position tags and large inputs.** The unchanged `make_plan` returns an empty plan for `input.len() >= 67108864`. All reachable A-planner cache positions are therefore at most n<2^26 and fit u32 exactly. Larger inputs, including n>u32::MAX on a 64-bit target, follow the original literal-emission path without entering RMQ. This reasoning applies to the official exported `parse`; no general promise is made for directly invoking auxiliary `parse_cfg`, `a_dp_pass` or helpers on arbitrary unbounded arguments/cache contents. The old DP spec also carries a bound on pe that must be retained during proof migration.
6. **Nonuniform costs and partial buckets.** The uniform mask scans every cost entry in each bucket once per DP call. `lc` is borrowed read-only throughout the call, so a later model update cannot invalidate the mask mid-pass. A query starting inside a bucket or ending before its upper bound uses the original expression one length at a time. An empty original interval returns the same all-ones sentinel. The new out-of-range early returns are unreachable for nonempty intervals produced by the original A-planner loops: those loops produce lengths 3..258, enforce stop<cl and keep prev>=i+2.
7. **Planner-window end.** A candidate may query the original zeroed future-cost suffix beyond pe; this was already allowed by the original code. Initializing that entire suffix preserves that behavior, rather than incorrectly forcing every match to end at pe. The final checked emitter still verifies actual match bytes and input bounds.

### Shortest proof-migration route if measured performance warrants it

The official correctness obligation requires the planner to be total and the original checked emitter to decode correctly. It does not require proving that RMQ chooses an optimal or token-identical plan. Therefore the first migration should reuse the existing `emit/check/mlen` proof unchanged and focus on these narrow totality obligations:

- `r4_rmq_update`: bounded six-level loop; an invariant tying `half` to `level` (or finite cases for levels 1..6) proves ordinary arithmetic safe. Array reads/writes are bounded/modulo 3072.
- `r4_rmq_init`: remaining count decreases; retain `pe+left <= cl` / usize-bound information from the guarded initialization span.
- `r4_uniform_buckets`: code<29 and inner length<259 give bounded array accesses and progress. Keep fixed-table bounds available to the later query proof.
- `r4_rmq_best`: after guards, `i <= at <= stop+1` and stop<cost.length; scalar fallback increments at, accelerated selection sets at to end+1 with end>=at and end<=stop. Use measure `stop+1-at`. The constant start/end table needs a small finite lemma establishing low<=high<=258. No cache-value semantic invariant is needed for totality.
- Re-extract first, then adapt the old `a_dp_pass` loop statements to the actual new array/capture parameter order and replace removed scalar-loop spec references by the helper spec. Preserve the old cost/ch length and pe/position bounds. Do not guess tuple layouts from Rust variable order.

Potential proof obstacles are extraction-generated loop numbering/state tuples, table-value bounds through constant-array indexing, and symbolic arithmetic for `half *= 2`; they are concrete remaining work. A separate RMQ semantic invariant would be needed to upgrade finite token equivalence into an all-input equality theorem, which this audit does not claim. No proof is written speculatively before the research timing/equivalence result.

## Final three general-route hybrid candidates

Prepared by `23:01:51 UTC` at the main thread's request, using original public299 and frozen H cores. These combine measured complementary engines; they do not add a file-name/hash lookup, exact-file-length identity, or another effort sweep.

| Candidate | Original public299 branch | H branch |
| --- | --- | --- |
| `r4-hybrid-h16-small299` | input length <65536 | H16/depth64 core, mode 0 |
| `r4-hybrid-h16-smallc299` | input length <65536, or original `classify` returns any value in the inclusive interval 1..3 | H16/depth64 core, mode 0 |
| `r4-hybrid-h3r-smallc299` | Same small-input and content conditions | H mode3/i8 core, with its original depth32/16 and restart policy |

The original classifier's classes 1..3 are explicit general features: nucleotide/newline sample share >=95%, zero share >=50%, or zero/control share >=2% together with high-byte share >=35%. Original CLASS_CFG/CFG maps these classes to C-engine configurations. The current CFG uses only A and C, but the original `plan_cfg` source and full proof retain the B branch; it was left intact to preserve engine declarations and existing proof structure rather than undertake another pruning rewrite under the deadline. Calling original S after the hybrid's content classifier may repeat classification; no timing saving is assumed from source alone.

**VERIFIED locally:** `scripts/make-round4-hybrid.py --check` reconstructs all three candidates exactly. The two Rust bases share only the function name `parse`; public299's definition becomes `s_parse`, the old H-only parse wrapper is removed, and a new small/content dispatcher is added. All 233 resulting functions, except these specified entry-wrapper changes, all constants, and custom types were checked against their respective parents' exact declaration text. Only top-level `//!` markers are converted to ordinary `//` when concatenating Rust source, preventing invalid inner documentation after declarations. No official source or frozen parent is edited.

The combined Lean file uses three separately closed/reopened `Submission` scopes. The original S proof changes only its final theorem name to `s_parse_spec` and the two corresponding `slot.parse` references to `slot.s_parse`. The H proof keeps its complete EH namespace and T9/T10 macros, removes duplicate imports and its old final parse wrapper theorem. The final fresh scope locally registers the two complete engine specs, plus original `classify_spec` for content variants, and proves the new dispatcher with `step*`. S's old local step/scalar rules therefore do not remain active while elaborating EH. No axiom, sorry, weakened obligation, official check or time-limit change is introduced.

The two content variants have the same proof file hash because the final proof applies the generic `EH.parse_mode_spec`; the actual H mode (0 or 3) is determined by the freshly extracted dispatcher. The Rust entry is separately recorded and audited. This equality is not a claim that their parser behavior is the same.

| Candidate | Rust SHA256 | Lean SHA256 | Rust / Lean bytes |
| --- | --- | --- | --- |
| h16-small299 | `d9826bc92ba02f49cb6e552ed172a4fb82dc10fa8fb51aacf73e7947ed38a94d` | `ac2d894b3a4ccacb30ce4ed654a3dd3d3b3c167183eb8df008168772109215fa` | 176326 / 375539 |
| h16-smallc299 | `39c82b4673440faaa7cf9f14ccbeb9367128a7f50a8ca8472880dc35ed24b83e` | `eec49d582853cddf843c33b950f444520561bbb40ef0197ee64ce9acfbb92791` | 176423 / 375553 |
| h3r-smallc299 | `6814b45429d9dbbb66a94a2a18abca39bd23790756490e8acbb62e79306d18d9` | `eec49d582853cddf843c33b950f444520561bbb40ef0197ee64ce9acfbb92791` | 176422 / 375553 |

Each candidate contains `composition-audit.json` with both parent hashes, conflict checks, retained declaration lists and the actual Rust/Lean entry text. All files fit the per-file 524288-byte limit.

**INFERRED:** parent measurements suggest that the small-input route can recover the tiny-input size disadvantage and that original C specializes usefully on DNA/zero-rich/high-byte binary inputs. Adding the two engines changes extraction/compilation workload and binary layout. The roughly 375.5KB combined proof may take substantially longer than the 95KB H core; only a new gate can establish completion within 900 seconds. Parent-coordinate arithmetic is a screening hypothesis, and the hybrids have no reliable formal same-family anchor.

**UNKNOWN:** new Rust compilation, exact extracted entry shape, final dispatcher proof/axiom checks, elaboration runtime, public paired time/size, private stage2, admission and rewards. These are the final three requested hybrids; no additional direction or candidate is generated.

## Completed M/N outcomes, verified 23:07 UTC

M (`37541614789/gate/`) completed 16 paired public measurement processes. Mode3/i8 scored (6.942604, 33.868489%) and passed a fresh full official gate, axiom whitelist and eight fixed generated inputs in both orders. Verification through axioms took 157.5 seconds. Its fixed-427 size projection is 34.106509949%, still 0.004602849 pp above the current slow frontier at that time coordinate. Mode2/i8 scored (6.402373, 33.870505%); it was measured but not selected for a fresh gate.

N (`37542714311/gate/`) compiled the final RMQ source and completed 444 finite token/decode checks against original public299, with zero differing or failed cases. Both public blocks also produced identical tokens and DEFLATE output. However, public time axes were 22.119259 / 22.067124 versus original299's 9.474225 / 9.445378: relative regressions 133.4678% / 133.6288%, mean 133.5483%. This implementation is stopped. Its copied proof remains NOT_ADAPTED; no candidate Lean gate was run, and workflow success only reflects the explicitly restricted research checks. The earlier Python/static audit is superseded by these actual Rust observations for the tested finite inputs, not by an all-input equivalence claim.


## Final hybrid verification

O completed successfully at 2026-10-06T23:46:23Z after the fixed research window; no new experiment was launched after the window. The selected h3r-smallc299 source/proof pair passed fresh extraction, LZ77.Obligation, the three allowed axioms, full public gate and eight generated inputs in both orders. Through-axiom verification took 889.7 seconds in total; this is not a statement-only duration. Public axes are 7.403035728639496 and 33.85555195726892%. Fixed427 projects to 7.509660847163516 / 34.093481955464476 (snapshot24830 geometric frontier); substituting only the299 size factor gives34.11519168590491, which is dominated at that time. Full gate acceptance and this calibration disagreement are both retained. Neither private admission nor payment was observed.
