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

## First screen decision and compact-chain replacement

**VERIFIED from the two blocks in explore-a `state.json`:** relative to the
same-block scalar, seed averages -5.6071% time and +0.1351735 pp size; lazyseed
-5.1318% and +0.0926915 pp; seed2 +9.5445% and +0.0583781 pp. The original/new
candidate stream agrees on 18 public D files and 66 fixed synthetic cases, and
all 84 instrumented/reference comparisons agree. The recorded coarse
collect+seed/old-forward ratio is 0.90691, with seed approximately 19.90% of
that new frontend. Those coarse ratios have allocation and order differences.
Sampled tiny-helper timing can exceed the parent denominator and is not an
additive cost attribution.

**Decision:** stop further similar seed or pass-count variants. The proof run
already launched by the parent continues as a reusable correctness experiment;
the first screen provides no performance justification for more of this family.

The next independent mechanism is `r10-forward-delta16`, generated by
`scripts/build-round10-forward-delta16.py` from scalar. It keeps the original
forward plan, statistics, search parameters, record encoding, backward plan
and checked emitters. Only D's `prev4` and `prev7` change from absolute `u32`
positions to `u16` backward distances. Hash heads remain absolute `u32`.
Distances 1..32768 are stored exactly; zero terminates the chain. Larger
distances are replaced with zero because their targets are already too old.
The two arrays shrink from 262144 to 131072 bytes, saving 128 KiB of fixed state.
Encoding and decoding add arithmetic, so a speed gain remains **UNKNOWN**.

Rust SHA-256:
`1ddbe9f60a2a5dec38a67dcf80211dc2f43bd1160f4916074bb545128a967ee5`.
The screen directory retains the parent proof explicitly as unadapted; a
separate `r10-forward-delta16-proof` draft contains helper proofs and the four
explicit U16 predecessor-array types in the D loop's products. Its initial
Lean SHA-256 is
`732055386a474f0590cc1c5a17553262b3f1c2265ebb22f7c9332c55d774d9d7`.
Both real extraction and complete original gate remain pending.

### Boundary argument and its limits

- At a queried live node `c` with `0 < i-c < 32768`, its circular slot has not
  been overwritten since its insertion. A retained delta recovers the original
  predecessor. A discarded predecessor is older than the active window.
- At exactly `c=i-32768`, the current insertion may have overwritten the slot.
  The successor reconstructed by the two representations need not be identical,
  but every strictly older successor is already out of window. They therefore
  cannot differ in another in-window probe after visiting `c`.
- `skip_same` may read a stale start before the walk's distance guard. Both
  versions only follow a strictly smaller successor, so an out-of-window start
  cannot re-enter the current window.
- The decoder uses `c.wrapping_sub(delta)` followed by the original `nx<c`
  condition. Zero and underflow both fail that condition; no additional bounds
  branch is needed. This is a proposed equivalence argument, not a Lean proof of
  all compressor outputs.

**VERIFIED finite model:** `delta-model-check.json` covers 1050464 insertions,
153024 direct/skip_same visible-visit comparisons and 22849 exact-window-boundary
visits, using four hash histories, small windows and W=32768, from zero and
across the u32 position boundary. All compared visit sequences match. Large
window queries are sampled while insertions remain complete. This Python model
does not replace the requested 444 finite Rust token/decode comparisons,
identical public outputs, paired total-compression timing or fresh full gate.

**Next discriminating result:** if those Rust/public outputs differ, inspect the
first mismatch before claiming equivalence. If output agrees but paired timing
regresses, the saved state/initialization has not paid for distance encoding in
this implementation; do not automatically combine it with other CPU changes.

## Delta16 interface receipt and seed proof failure retention

Run `37684506856` accepted extraction for exact delta16 Rust
`1ddbe9f60a2a5dec38a67dcf80211dc2f43bd1160f4916074bb545128a967ee5`.
The proof draft's explicit `d16_walk_loop_spec` predecessor type was still U32;
it is now U16. The reconciled draft Lean SHA-256 is
`d07ba3aed243ca6cb340bcaa1f6a015f095a16fb0cba2e7e51b187b26646547b`.
The generator checks all extraction-file digests, eight interfaces, and the
predecessor-array types. Omitting generated Source comments and normalizing
whitespace, the extracted D loop body, loop wrapper and parser wrapper exactly
match their R9 counterparts after only the expected U16 type/zero-value and
helper-name substitutions. This is an interface/control-text audit, not a Lean
execution or full semantic equivalence proof. Actual gate and performance
remain pending; evidence is in the proof directory's `interface-audit.json`.

The seed proof at frozen SHA `b41316b5...` failed naturally in run `37682364860`.
The retained `r10-forward-seed-proof-005-lake.log` reports exactly four errors:
lines 3676, 3815, 3821 and 3945. Their omega counterexample descriptions retain
tuple projections for the current cursor instead of exposing the named `i4`,
`end` or `q1`; the other new helper proofs emitted no errors in that log. This
does not establish an accepted theorem or gate.

A bounded four-term repair was saved independently as
`candidates/r10-forward-seed-proof2/`, Lean SHA-256
`0926ce11166ba9e4bc11a985467945e42e952800647fb6e8dae7a2165d283545`.
Each repaired term gives omega an explicit arithmetic proposition for the
decreasing cursor, leaving tuple projection reduction to definitional equality.
Rust, declarations, loop invariants, original obligation and frozen failed
proof remain unchanged. `failure-repair-note.json` binds the exact error log.
Status is **UNTESTED_REPAIR_DRAFT_NO_CI**; no compilation or renewed seed gate
was requested. The measured size regression remains the reason to stop that
performance family.

## Whole-state relative positions: one new controlled experiment

The `struct-b` screen preserves delta16's public bytes but measures about
**+1.25%** total time versus scalar. Stop that implementation and do not spend a
full gate on it. Its finite equivalence and model artifacts remain useful.

The replacement `r10-forward-rebase16` changes a different cost structure:
encode the current position once, copy relative codes into predecessor links,
and periodically rebase every head/link array together. Its exact Rust SHA-256
is `8382914307102bb37f690180cf0ba0dbd605a6eecc136263766ec847884fb2fb`.
The parent proof is explicitly **UNADAPTED_PARENT_ONLY**. Generator and retained
source evidence are `scripts/build-round10-forward-rebase16.py` and the
candidate's `primary-source-reference.json`.

**Primary-source check:** fixed libdeflate commit
`92e6a0db9fa848d742f9eb286c92afc60f2c3dda` uses signed 16-bit matchfinder
positions, slides heads and links together, and handles sliding during skipped
byte insertion. `matchfinder_common.h` lines 118-157 describe saturating
rebasing and a portable loop; architecture-specific implementations are also
selected. `hc_matchfinder.h` slides at 32768 and rejects `cur_node <= cutoff`.
That strict cutoff excludes the exact 32768 endpoint, unlike the parent here;
the implementation is a reference mechanism, not an equivalent transplant.

Our unsigned encoding is `position-base+1`. Zero decodes to
`max(base-1,0)`: it is the original default position zero in the initial epoch,
and safely stale after rebasing. Before `q-base` reaches 65535, update
`base=q-32768` and saturating-subtract the shift from all five arrays. Normal
shift is **32767**, so the position exactly 32768 behind remains encoded as 1.
Each call in `insert_range` performs the same rebase check, so a skipped match
can cross an epoch without losing maintenance. Inputs above `u32::MAX` use the
unchanged parent D parser, preserving the parent's absolute-position truncation
semantics instead of silently changing behavior beyond 4 GiB.

Nominal finder state drops from **851968 bytes (832 KiB) to 425984 bytes
(416 KiB)**. This does not prove smaller generated stack frames or faster code.
The periodic scan touches 212992 u16 cells about every 32767 inserted bytes,
after the first 65535 bytes: roughly 26 bytes of sequential read/write traffic
per inserted byte. Normal head/link traffic halves from a nominal 32 to 16
bytes per insertion, excluding cache-line and write-allocation effects. The
rebase adds traffic while reducing random-access working state; source code
alone does not establish which effect wins. Ordinary safe loops use u16
saturating subtraction, with vectorization left to LLVM and not yet observed.

**VERIFIED locally:** deterministic generation/exact hashes, size limits,
Python syntax and absence of unsafe code. The finite rebase model performs
1050608 insertions, 201984 direct/skip_same visible-visit comparisons, 132 whole
state rebases and 46922 exact-window-boundary visits; all comparisons match.
Insertions are complete and large-window queries are sampled, with explicit
checks around rebases. This is **Python model evidence only**.

**Next falsifiers:** run 444 whole-parser token/decode equality cases plus
identical public outputs, paired total compression and extraction. Stop on an
unexplained mismatch or unfavorable measured cost. No parameter sweep, complex
proof or full gate is justified before a performance signal. This candidate
does not combine the failed RMQ or delta-distance implementations.

## Rebase result and the single static-cost seed revisit

**VERIFIED in run `37689247460`, `rebase-d`:** rebase16 retains public output
bytes but takes about +2% and +3.94% more total time in the two paired blocks,
approximately +2.97% on average. Stop this implementation and do not begin its
complex relative-coordinate proof. Its source, extraction and boundary model
remain archived; halved table state did not produce a measured speed gain here.

The next authorized seed revisit is a distinct, fixed mechanism:
`r10-forward-costseed`, directly derived from frozen `r10-forward-lazyseed`.
Rust SHA-256 is
`f397e8c9a4648551eaf363e2efa3663e27e1d65426e26ff0771cce004ff16242`.
Generator: `scripts/build-round10-forward-costseed.py`.

**Hypothesis, not a measured diagnosis:** a length-only seed can consume short,
distant matches whose length/distance symbols cost more than the corresponding
cheap literals, biasing its subsequent block statistics. This candidate tests
that explanation with the original static symbol model, rather than increasing
passes or adjusting a threshold.

Inside `d_seed`, call the original `fill_tables`, `init_counts` and
`make_costs(huff=0)` once. This preserves the original strided byte histogram
and match priors. At a token boundary that already passed the original sparse
map, longest-interval, range and one-byte-lookahead conditions, accept the match
only if `lc[length] + dcc[dsym(distance)]` is **strictly less** than the literal
cost of that same span. Prices retain their original 1/16-bit units and include
the length/distance extra bits. Equal prices select a literal.

Literal prices are nonnegative, so the helper can accept as soon as a partial
literal sum strictly exceeds the match cost. It otherwise examines at most 258
bytes. Comparisons use u64: two u32 match components total less than 2^33, and
258 u32 literal prices total less than 2^41, so the accumulation cannot wrap
under the explicit length guard. The model is never refit during the seed.

`d_collect`, exact rs stream, sparse map, one-byte lookahead, route table,
single backward pass and checked emitters remain unchanged. Only one helper
and `d_seed` initialization/acceptance change; reversing that region restores
lazyseed byte-for-byte. No speculative proof repair is attached: the candidate
copies the original proof and remains **UNADAPTED_PARENT_ONLY / UNKNOWN**.

Local checks confirm deterministic generation, source/manifest hashes, size
limits, Python syntax, unchanged proof bytes and the integer-sum bounds. The
existing forward diagnostic can validate record equality, every seed match,
complete coverage and final decoding after its candidate entry is selected by
the main thread. **Rust execution, two-axis performance and full gate remain
UNKNOWN.** Added histogram and literal-prefix work can erase any size recovery.
Do not invest in a gate merely because public size improves: continuation
requires the current projected tradeoff to improve on the verified record
baseline. This is one candidate with fixed settings, not a renewed seed sweep.

## Endprobe proof scope, after actual extraction

`selective-e`, run `37693029351`, accepted extraction of endprobe Rust
`474714b7007f73ac04d7ff7e2c5199385fd3d10e4b3fc323ad6fd3c58a7ba576`.
The extraction-file digests and four relevant signatures were checked against
`research.json`; `Funs.lean` SHA-256 is
`0aa6682c30b62ccc5eb8f25a48ceabc63f74494f77fbecc7003635274bfb085f`.
Machine-readable audit: `candidates/r10-forward-endprobe-audit/interface-audit.json`.

The remaining proof changes are bounded but nontrivial:

- `ep_search` returns only rs. Existing probe, skip, walk and record totality
  lemmas cover its work once the input-cap and pre-insertion-head bounds are
  established. It has no new traversal loop of its own.
- `ep_insert_range` carries `(head3, head4, prev4, head7, prev7, rs, q)` and
  returns the five tables followed by rs. Its old `to-q` measure and head-table
  bounds remain suitable; the added query reads the tables without modifying
  them.
- The outer D parser loop remains 26 elements. Only the inner long-jump result
  adds updated rs immediately after plan, requiring product/uncurry repairs
  around the range-helper call. External `d_parse`, checked emitters and the
  original obligation retain their interfaces.

This scope is larger than record-nonempty's single write guard, but narrower
than rebase16's relative-coordinate invariants. No formal proof was started
and no proof-runtime estimate is established. Performance must first justify
that work; accepted extraction is not accepted proof.

## Independent CPU simplification: dirty cost models

Source evidence identifies repeated pure cost-table construction: D checks its
model every `UPD=2048` positions, while ordinary token statistics are tallied at
`CHUNK=4096` boundaries or around directly accepted long matches. Some scheduled
updates therefore have unchanged inputs. R7 upd2/upd4 changed the schedule and
the resulting quality; this experiment retains every original update position.

`r10-forward-costcache` is based on the **verified** `r10-record-nonempty`
parent, as requested by the coordinator. Exact Rust SHA-256:
`157f16e6c2c589f58a34b8a6c92396fa932eb9ad08ca4b7a88099f8428eea961`.
It carries one Boolean marking whether frequency inputs changed. Initially it
is true because the initial price build is followed by two halvings. Both
in-loop backtracks set it true; the long-jump branch's direct match counts are
covered by that same mark. Every scheduled update still computes the original
wrapping total and performs the original `HALF_AT` test. A halving always forces
`make_costs`, even if the flag was false. Otherwise only unchanged-input builds
are skipped; each completed update clears the flag. The final tail backtrack
has no subsequent update and needs no mark.

This does not presume that a previous halving brought totals below the
threshold. The finite state model explicitly covers several successive halvings
without added counts, initial double halving, 113 long jumps crossing an update
boundary, and 32 CHUNK flushes. Across 697 scheduled updates it skipped 217 pure
rebuilds and performed four halvings while previously clean; baseline and cached
frequency arrays plus the complete pure-function argument fingerprints agree
after each update. These are **model counts, not workload performance estimates**.
The report is `candidates/r10-forward-costcache/dirty-model-check.json`.

Generator `scripts/build-round10-forward-costcache.py` checks the parent's
verified exact files. One helper and four local D substitutions reverse exactly
to that parent. All search, recording, model formulas, update times, halving,
backward planning and output checks remain unchanged in intent. The copied
record proof at `86cfc36a...` is explicitly unadapted to the new helper and
Boolean loop state. Require 444-case Rust token/decode equality, identical
public outputs, paired comparison to record and scalar, and fresh extraction.
No performance gain or complete gate is yet established.

The optional `scripts/research-round10-costcache.py` enables real opportunity
counts under `costcache_diagnostics: true`: scheduled updates, actual rebuilds,
skips and halvings. It compares frozen and instrumented parser tokens and
decoding once on each of the 28 public inputs, binds source and corpus hashes,
and uses no microfunction timer. Local syntax and insertion-point checks pass;
actual runner counts remain pending.

## Route model coupling and one precise restoration candidate

The R7 migration copied only DP_KNOBS's first six search settings into the new
D rows, plus D-specific fields. Source inspection confirms these model changes:

| Existing content class | D row | Original DP row | Original key / update / half | D prior to this experiment |
|---|---:|---:|---|---|
| 5 XML, 6 HTML | 5 | 0 | 8 / 8192 / 8000 | 7 / 2048 / 10000 |
| 10 JSON | 6 | 2 | 8 / 8192 / 8000 | 7 / 2048 / 10000 |
| 11 long lines | 7 | 3 | 8 / 4096 / 10000 | 7 / 2048 / 10000 |
| 12 text, 13 multibyte, 15 prose | 8 / 9 / 10 | 4 / 5 / 6 | 7 / 2048 / 10000 | same |

There is an additional substantive difference: DP uses `rc_seq` and tries every
length, whereas D with `fback=100` calls `relax_cands` using `nextl` constructed
at `flen16`. Both retain TMAX=64 and BTRUNC=1. The inherited first six search
parameters match, huff=0 matches, lz2max=258 matches, and the migrated D rows use
the same d7 for regular/lazy/end positions. D still uses direct insertion and
plain `d_walk`; DP uses pipelined head reads and a tail-word long walk. Those
latter differences are intended as CPU changes but their equivalence is not
promoted here to a universal theorem.

One authorized candidate, `r10-forward-routecfg`, restores only the original
three model settings, with no flen258 alternative and no unmeasured costcache
combination. It derives from verified record-nonempty. Rust SHA-256:
`917eee4fb794e0fa83ea92c131c0dfa97ad3f1b613a907d59e1f2c459b900979`.
Generator: `scripts/build-round10-forward-routecfg.py`; mapping evidence is
`source-audit.json` in the candidate. It hashes the original public361 source,
checks every migration row and search setting, preserves D_KNOBS and CLASS_TAB,
and verifies that reversing five changed regions restores the exact parent.

`D_MODEL` supplies [key bytes, update interval, halving threshold] per existing D
row. Initialization reuses `dp_sh7`, `dp_upd`, `dp_half`; updates use the existing
`update_costs_h` with that threshold. Native D retains [7,2048,10000]. The D loop
needs only two additional frozen parameters, not an additional evolving state.
The first pass remains sparse at flen16: **this is model-configuration
restoration, not complete restoration of the original DP plan**. Unlike R7's
global upd2/upd4 sweep, the values and affected rows come directly from the
pre-migration profiles and also restore the key/halving choices.

Local checks cover exact source reversal, mapping, 21 parameter-boundary cases
and both 32/64-bit guarded-input-plus-update bounds. The existing clamps ensure
shift 0..56, update <=1048576 and a u32 threshold. Actual Rust and Lean remain
untested. The copied record proof at `86cfc36a...` does not cover the changed
parser/glue signatures or new model table.

First falsifiers and proof boundary:

- Reject build/extraction failure or any round-trip failure. Unexpected public
  token changes in the unchanged-model/native routes require diagnosis.
- Use the four affected classes' per-file changes and the whole official
  time/size axes against record, scalar and public361. Original-author settings
  do not guarantee a better sparse-D/backward combination or private outcome.
- Only a useful current projection justifies proof work. That bridge can reuse
  the existing clamp and `update_costs_h` lemmas, adapt frozen updn/halfn loop
  arguments and glue-array accesses, and retain the original output obligation.
  There is no accepted proof or proof-runtime result for this version.
