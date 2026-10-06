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
