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
