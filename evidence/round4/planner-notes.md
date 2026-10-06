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
