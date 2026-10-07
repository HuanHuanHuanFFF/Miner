# R10 forward planner research

Scope: work assigned to the forward-research child, starting 2026-10-08
03:50:52 +08:00. Original author and verified lineage are retained through
`candidates/r9-block-scalar/manifest.json` and the #361 provenance. No CI was
started by this child; the parent owns runner dispatch and final integration.

## Evidence and question

**VERIFIED by current source inspection:** the D search schedule depends on
`cl`, `best`, `anchor`, `alen`, `skip` and the search settings, but not on the
forward price ring or learned costs. The forward plan influences the subsequent
block cost tables. The same matchfinder and `d_record` calls can therefore be
retained while replacing only the first planning/statistics phase. Exact record
equality is a falsifiable prediction, not yet a measured result here.

R9's 73.34% forward share includes insertion, searching, recording, relaxation,
backtracking and updating costs; it does not isolate chain walking. R9's modeled
free-backward benefit of about 13.6% is below its historical 17.25% conservative
target. Those historical targets are not fresh frontier or private-corpus facts.
Sources: `docs/rounds/round09.md`, `evidence/round9/diagnostic-conclusions.md`.

R7 seed1/seed2 only changed `flen` to 3 and disabled initial backward extension
on six text classes. They retained the forward price ring and cost updates.
The present design removes all first-pass pricing machinery for D-routed data;
it is not another search-depth, NICE, lazy-position or update-interval sweep.

## Implemented candidates, not yet performance claims

| Candidate | Mechanism | Rust SHA-256 |
|---|---|---|
| `r10-forward-seed` | Original search/record stream, sparse interval map, greedy seed, original one backward pass | `0641cc845c21b684a7f27e202992279004b42b6f9cf2103211ced46749f7d489` |
| `r10-forward-lazyseed` | Same, plus one-byte seed lookahead from existing map | `9b7b78681517c6dbaf1e2788bb03cca26ba9517e0881d9eab54ea4d8cfad815d` |
| `r10-forward-seed2` | Same greedy seed as first row, two backward cost-refitting passes | `773ff3eca0815e9c1ad89347a5901e87632c6a76f8f09f38488a470b7da80037` |

All three initially contain the parent Lean bytes
`aa21da6f74e81314297df07beecbfc98b15c848354437674bdb9347d8632f0af`.
This is **UNVERIFIED_PARENT_ONLY**, with missing new-helper and changed-call
bridges; it is not an accepted proof. Original `d_parse` remains byte-identical
and callable to support exact `rs` differential checks. The active path calls
new `d_collect` and `d_seed`, then unchanged `d_tally`, scalar `d_dp`, `d_extract`
and checked emitters. Source generator: `scripts/build-round10-forward.py`.

The seed uses the existing output buffer as scratch. Each recorded match puts
its original and maximal backward-extension starts into a sparse map. A linear
sweep keeps the longest active interval and greedily consumes its suffix at
token boundaries. This preserves cheap coverage inside long spans skipped by
the searcher; merely visiting searched positions would lose that coverage.

**INFERRED opportunity:** omit forward `pa` and `tb` arrays, entropy-cost tables,
candidate-length relaxations, backward best-start scans, chunk backtracking and
model updates. Pay instead one sparse-record traversal and one linear seed
sweep. Since some old work survives as matchfinder/recording, the removed cost
must be measured, not inferred from the whole 73% share.

**Principal falsifier:** any changed `rs` word invalidates the claimed search
isolation. If `rs` agrees but compression worsens, compare greedy+2pass: recovered
size would implicate seed-cost bias; unrecovered size or excessive cost means
this particular seed is unsuitable. One-byte lookahead distinguishes a cheap
seed improvement from another expensive full refinement pass.

## Local checks and runner handoff

**VERIFIED locally:** generator and `--check` reproduce exact frozen source and
manifest bytes; Python AST parsing of generator and diagnostic succeeds. Local
environment has no `rustc`/`cargo`; no toolchain was installed. No Rust compile,
Lean gate or performance claim follows from the local checks.

`scripts/research-round10-forward.py`, enabled by `forward_diagnostics: true`,
expects scalar and seed entries. It checks original/new `rs` equality, every
seed match and complete seed coverage, and candidate token decoding on public
D-routed files and 66 fixed synthetic cases. It compares instrumented/original
scalar tokens for all 28 public files, three repetitions each.

Its helper timing is **sampled, inclusive and overlapping**: `d_walk` includes
`probe`; `d_record` includes `d_backext`. Two repetitions sample one in 1024
calls, one samples one in 64. Call-count and timer overhead can change codegen
and total time. Do not sum these estimates into 100%, use them as official axes,
or extrapolate them without paired uninstrumented total-compression results.
Compilation timeout is 180 seconds and execution timeout 420 seconds; failure
retains the log and writes `DIAGNOSTIC_FAILED` using the R9 receipt helper.

Parent reported first run `37679261323` at commit
`16d80788891d3ce7fece4fa990078eb1eee62dcb`. This is dispatch evidence only;
success, final measurements and extraction interfaces remain **UNKNOWN** until
the corresponding artifacts are inspected.

## Proof bridge and next work

The correctness boundary remains original `emit`/`emit_pos` match validation.
The new planner needs totality, bounds-safe arithmetic/indexing and preserved
output-slice length, not an optimality proof. `d_collect` needs the original
head-table `LeAll`, cap and index invariants plus strict progress of `i`.
`d_seed_map` has bounded zeroing, reverse record traversal and candidate loops;
`d_seed` increments its byte cursor and appends only under `plan.len() < n`.

Prepare proof only in `candidates/r10-forward-seed-proof/` and other explicitly
authorized proof variants, keeping measured first-batch source/proof bytes
unchanged. Actual Aeneas interfaces, original obligation, axiom whitelist and
public round trip remain required before any accepted-candidate statement.

## Fresh extraction interface reconciliation, 2026-10-08 04:29 +08:00

**VERIFIED:** run `37679261323` accepted extraction of the exact seed Rust above.
The extraction manifest and all three generated files were checked by SHA-256;
`Funs.lean` is
`a3de94523147dee324a52a6130abb6178ed276fd9a117c400010cfb3518aefe5`.

`candidates/r10-forward-seed-proof/` now contains the unchanged seed Rust and a
complete attempted totality bridge. Its current Lean SHA-256 is
`b41316b50ffee2a7f26ec3ec87e14cb65dbe777b00aadca628f69a5887cfcca2`.
`scripts/build-round10-forward-proof.py` checks the exact extraction and ten
function parameter lists, then writes `interface-audit.json`. The code corrects
the candidate-loop order to `(e, p, j)`, follows the collector's actual 15-value
state, and accounts for the compiler reusing the already calculated match end.
It also checks the `d_seed` `(out, plan)` result before the enclosing planner
returns `(plan, out)`.

Local audits confirm unchanged Rust bytes, matching manifest hashes, both files
under 524288 bytes, valid generator syntax, and no additional `sorry`, `admit`
or `axiom` tokens. **UNKNOWN:** Lean elaboration, proof runtime, original
obligation, axiom whitelist and public gate. Status is therefore
`INTERFACE_RECONCILED_UNCOMPILED`, not a verified proof. The next decisive check
is the original full gate on these exact bytes; source-interface agreement
alone cannot establish theorem correctness.
