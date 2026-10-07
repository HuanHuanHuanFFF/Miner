# R10 bounded supplemental finder

Status at 2026-10-08 04:01 +08:00: **Rust candidates generated; native build, extraction, paired performance and full gate UNKNOWN.**

## Question and changed mechanism

R9's full #454 q9 tree/cache prepass found extra valid matches, but construction alone cost 3.608 times the complete #361 parser on the public DP files. Those opportunities did not establish an encoded-size gain. This experiment pays no tree-maintenance or whole-input match-record prepass cost. It retains scalar's original chains and queried-node control flow, and performs one supplemental lookup after all original candidates and continuation have been assembled.

The two candidates have distinct failure modes:

| Candidate | Extra maintenance | Supplemental source | Fixed extra state |
|---|---|---|---:|
| `r10-finder-tag4` | two-tag MRU update in a four-byte bucket | nearest exact four-byte tag surviving a collision in the original shallow chain | 524,288 bytes |
| `r10-finder-hash5` | one latest-position store for a five-byte hash | five-byte repetition between the original four-byte/seven-byte keys | 262,144 bytes |

Tag4 adapts #454's `q9_cache4` two-distinct-key logic only. Original source and author are preserved through `references/round8-public-454/PROVENANCE.json` (source hash `382176623abda73f77a9a5323e8cb14c5cdd6c8221b018cbc8c51cf959448639`, author hotkey `5HYsKBJ49UnjNVXBN8hMynUp2Y9M3YqPrsmAqTJrhGnBa4r9`). It changes the table shape to 32,768 buckets with two entries; no tree traversal is copied. Hash5 uses #361's multiplicative hash family on a five-byte prefix. Both retain the underlying #361 author attribution via the scalar parent manifest.

## Frozen Rust and source audit

Parent: `candidates/r9-block-scalar/parse.rs`, SHA256 `faf1d7281678d12c3243002121feecdd0ea139633dea197dbc77d86fb6319257`.

- Tag4 Rust: `6ecc62c72c945b4ae4dee33d7e4e3eadf95e44d24190e3448cde4b8aa24a417f`.
- Hash5 Rust: `d26201a20f320bec13ff1b9890cfd2e9c7531279088bcfb5b9dccee01a1d2b96`.
- Both initial `Parse.lean` files: copied parent `aa21da6f74e81314297df07beecbfc98b15c848354437674bdb9347d8632f0af`; **UNADAPTED_PARENT_DRAFT**.

`python scripts/build-round10-finder.py --check` reconstructs the files, checks parent hashes and official per-file size boundaries, and reverses four exact replacements plus the new helper insertion to restore scalar bytes. Original knob tables, other engine implementations, cost tables, original search code, match recording, backward planning and checked emission remain byte-identical. The source changes occur only in `d_parse` and three uniquely prefixed helper functions.

Every original D insertion gets one O(1) cache update, including the positions inserted inside a taken long match. There is no supplemental byte comparison during insertion. At each visited original search branch, the query offers at most one extra `probe` call bounded by the existing cap (maximum 258 bytes). It appends only when the match is strictly longer than the existing best and the 16-slot candidate array has room. It never replaces or drops an original candidate.

This preserves the original candidate prefix **at each visited node**, rather than promising identical future search positions: a new longer match can change continuation, lazy behavior, long-match skipping, forward costs and the resulting parse. Those changes are intentional and must be measured on the actual integrated candidate.

## Minimum discrimination and stop conditions

1. Build the exact source on the pinned Linux runner, run finite decode/repeat checks and official extraction. A failure is an implementation/proof-interface result, not a conclusion that supplemental matching is impossible.
2. Use the paired fixed public corpus and official encoder to determine whether extra discovered lengths convert into smaller compressed output. Opportunity counts are alternative edges, not selected path/encoded savings.
3. Compare total time and size against scalar and the existing same-family anchor. Stop a variant if it does not improve size, or if its measured tradeoff remains dominated. A cache/table-size sweep is not warranted merely by positive opportunity counts.
4. If size improves materially but maintenance dominates, compare update/query counts and the before-best histogram before selecting a trigger; use content-independent parser state rather than file names, exact lengths or input hashes. Any triggered version is a new candidate requiring fresh validation.

The initial cost cap is fixed state initialization, one O(1) update per original inserted position, and one bounded probe per searched node. Actual elapsed overhead and official axes remain UNKNOWN until CI. There is no claimed upper bound on wall time from the operation count.

## Diagnostic invocation and evidence boundary

`scripts/research-round10-finder.py` runs only when the batch specification's `finder_diagnostics` is exactly `true`; otherwise it returns before accessing runner temporary directories. Enabled execution is restricted to this repository's Linux GitHub Actions runner. It writes source copies and binaries under `RUNNER_TEMP/round10-finder-build` and receipts/logs under `RUNNER_TEMP/round4-receipts/finder-diagnostics`, with 180-second compile and 360-second runtime process timeouts. It does not download, install dependencies, submit a candidate, or start CI.

For each included candidate it executes the 28 public inputs and 416 fixed synthetic cases (26 lengths x 8 modes x 2 seeds). It checks:

- Plain and observed candidate token equality, deterministic repetition, and complete decoding.
- Exact preservation of the original candidate prefix at every visited query node.
- Byte validity of every retained and supplemental match, strictly longer appended records and cap/slot bounds.
- Cache-update count, visited-query count, eligible extra probes, winning additions, added supported lengths, and before-best/winner histograms.

Counts follow each integrated candidate's evolving schedule. Cross-candidate comparisons do not hold the original baseline schedule fixed. The script contains no encoder or performance timer and makes no claim about official axes, private data, admission or rewards.

**VERIFIED locally:** Python syntax, generator reproducibility and source reverse audit, parent/candidate hashes, exactly one store/query observation callback per instrumented copy, exact callback reversal, repeated instrumentation rejection, full result-schema coverage and rejection of an incomplete receipt. **UNKNOWN:** native Rust compilation, actual 444-case outcomes, public paired axes, extraction and all proof/gate outcomes.

## Proof changes required

Scalar/#361 engine D is an untrusted planner: its final `emit` function rechecks planned matches. The original proof establishes planner totality and checked emission correctness; no parent theorem licenses the changed source automatically.

The new helpers require cache-index/overflow totality, a bounded range-loop proof, and a supplemental `probe` postcondition carrying `best0 <= best <= cap`. The cache can remain unconstrained in the D loop invariant: `r10_supplement` rejects absent/future positions using `old > 0 && old <= i`, then checks the distance before probing. The original head3/head4/head7 bounds must remain in the loop invariant.

Fresh extraction must determine the new helper return tuple order and the cache's position in `d_parse_loop`'s carried state. Port `d_parse_loop_spec`'s parameter list, state tuples, measure/invariant lambdas, changed helper binds, taken-match range bind and initial invocation from those actual interfaces. New array state changes these interfaces even though Rust `d_parse`'s public signature is unchanged. Helper proof drafts are preparation only. Acceptance still requires official re-extraction, the original `LZ77.Obligation`, allowed axioms and full public round trip bound to the exact Rust and Lean hashes.
