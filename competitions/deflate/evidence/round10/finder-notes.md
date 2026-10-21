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

## Accepted extraction and independent proof ports

At 2026-10-08 04:31 +08:00, run `37679261323` / batch `explore-a`, source commit `16d80788891d3ce7fece4fa990078eb1eee62dcb`, has delivered the actual accepted extraction for both frozen Rust candidates. Extraction receipts are under `evidence/round10/37679261323/explore-a/extraction/`. This accepts extraction only; native Lean proof checking, original obligation and public round trip are not implied.

The actual interfaces confirm:

- Cache store returns `(old, updated_cache)`.
- Supplement returns `((nc, best), updated_candidates)`.
- Range insertion carries seven state components, with cache after `prev7`, and returns six arrays.
- D's main continuation carries 27 components, with cache after `prev7` and before `pa`; its final done value remains the original eight components.

`scripts/build-round10-finder-proof.py` assembles independent proof packages using those actual interfaces. Both preserve the exact measured Rust bytes and preserve the scalar parent proof suffix beginning at `d_plan_k_loop_spec`, including checked emission and the final parse-validity theorem. The only proof edits are four new helper specifications and the D `d_parse_loop_spec` / `d_parse_spec` bridge region; no new axiom or sorry is inserted.

| Independent package | Rust SHA256 | Lean SHA256 |
|---|---|---|
| `r10-finder-hash5-proof` | `d26201a20f320bec13ff1b9890cfd2e9c7531279088bcfb5b9dccee01a1d2b96` | `37cd9f66b76bbedb7f322da8f86496acb999b057d82ba2783ba03098868e6f75` |
| `r10-finder-tag4-proof` | `6ecc62c72c945b4ae4dee33d7e4e3eadf95e44d24190e3448cde4b8aa24a417f` | `16a19534e89420c7905d7b430f6565b8798b94b62263366d7fddef5bffd92e71` |

**VERIFIED local source/interface audit:** actual helper/cache types and returned tuple ordering, loop-state placement, generator syntax/reproducibility, unchanged measured Rust, unchanged final correctness proof suffix, and per-file size bounds (each Lean draft is 408,734 bytes). **UNKNOWN / NOT_RUN:** native Lean compilation, automated scalar arithmetic proof closure, original obligation, allowed-axiom gate and full public round trip. In particular, tag4's `a+1` array-index bound relies on proving the shifted U32 hash is at most 32,767; a native tactic failure here would require an isolated arithmetic lemma, rather than relaxing any axiom policy.

The main thread owns CI dispatch and chooses whether performance justifies compiling these drafts. The first-batch directories remain frozen and retain their explicitly unadapted parent proof.

## First screen decision and existing-chain key variants

The completed `explore-a` screen and finite diagnostic have now been read from `evidence/round10/37679261323/explore-a/screen/`. **VERIFIED:** both supplemental candidates passed the 444-case repeat/observed-token/decode checks; every visited query preserved its original candidate prefix and valid match bytes. Public tag4 added 10,424 strictly longer records, and hash5 added 97,744. Hash5's winner-before-length histogram is `[703, 4381, 92650, 8, 0, 2, 0, 0]` for bins `<3`, `3`, `4..7`, `8..15`, `16..31`, `32..63`, `64..127`, `128..258`: 94.8% of additions occurred after an existing 4..7-byte best.

The corresponding paired public time/size tradeoff remains poor: tag4 gains only about 0.001372 pp in size at about 6.1% extra total time, and hash5 gains about 0.005377 pp at about 4.5% extra total time. Saved `state.json` predicts zero geometry weight and domination for both. Those are public measurements and snapshot-based screening results; they do not establish private scores or formal admission. **Decision:** stop tag4, and preserve both independent proof drafts without spending a full gate on these dominated cache variants.

The evidence changes the next experiment: rather than paying an additional table update/query to find a five-byte repetition, reuse the existing D long chain with its key shortened from seven to five or six bytes. The parent code explicitly describes D's allowed key range as 5..8. A repository search of historical generator scripts, manifests, reports and existing candidate `pub const KB7` definitions found no previous D-global-five/six-byte trial. Existing per-row `DP_KNOBS` key lengths are a different interface, and the new candidates leave those rows unchanged.

`scripts/build-round10-finder-keys.py` creates:

| Candidate | Rust SHA256 | Proof SHA256 |
|---|---|---|
| `r10-finder-key5` | `ab392178a1a1e103fd5e33538afd1acf6e54b8573dcccff2696879c0c56ab6d4` | `aa21da6f74e81314297df07beecbfc98b15c848354437674bdb9347d8632f0af` |
| `r10-finder-key6` | `d33ae66a2973a4756d6c76c05d6f8feab898f6aad1539337805ab25571ae580a` | `aa21da6f74e81314297df07beecbfc98b15c848354437674bdb9347d8632f0af` |

Each differs from scalar by precisely one source byte (`KB7=7` becomes `5` or `6`), with no side cache, extra insertion/query, added state, changed chain depth/table size, route change or new helper. Original search-control code remains identical; actual subsequent queried positions can change when match lengths alter continuation and skipping.

This is a replacement rather than coverage-preserving supplementation. Shorter-key grouping can displace depth-limited seven-byte matches with nearer occurrences that agree for only five/six bytes. Therefore the hash5 cache opportunity counts motivate the test, but cannot predict a size gain from key replacement. The first discriminator is actual paired encoded size and total time. Stop a key whose lost original long-key coverage outweighs short-match gains, or whose two-axis tradeoff stays dominated.

**Proof review:** the unchanged parent Lean has one symbolic constant lemma, `dp_KB7_bound : slot.KB7.val <= 8 := by simp [slot.KB7]`, used only to bound `8*KB7` and make `64-8*KB7` safe in `d_parse_spec`. The new values 40/48 and shifts 24/16 satisfy those same arithmetic conditions. No theorem states exact `KB7=7`, and no extracted helper/loop interface changes. The complete parent proof is therefore a compatible draft for the new exact packages, rather than an already-passed gate. Fresh extraction, Lean compilation, the original obligation, allowed axioms and full public round trip remain mandatory.

**VERIFIED locally:** generator syntax/reproducibility, pinned scalar hashes, exact single-byte reversal, per-file size boundaries and the constant-lemma dependency audit. **UNKNOWN:** native build/decode outcomes, paired performance, fresh extraction and complete gate for key5/key6. The side-cache diagnostic only supports tag4/hash5 and must be disabled for a key-only batch; token equivalence to scalar is not expected.

## One independent dependency-order CPU experiment

At06:13 +08:00, existing side-cache/key/row and relative-position negative results provide no evidence that another depth, key-length or state-capacity sweep will recover the target. R9 tail filtering changed byte-comparison work without a useful large time gain. R7 walk outlining and ring-layout variants also failed. This next mechanism does not change any such budget/representation: move the existing immutable D next-link read earlier within one eligible chain iteration.

`r10-finder-linkearly` uses the currently verified `r10-record-nonempty` parent, Rust `7f1c661fd1ce29d12c69671f034ff5a713e284ed1fcba66ba404ff25479b55b7`, Lean `86cfc36adb009970bccbb5a9c543c5f559148d729e8c0f041934aab44e95592d`. Parent VERIFICATION binds those exact files to full public gate37684506856. Its earlier metadata's UNCOMPILED wording does not override that later hash-bound receipt.

The sole Rust change moves `let nx = prev[c % WN] as usize` from after probe/candidate processing to immediately before probe. No read/probe/candidate is added or removed. Immutable prev cannot be changed by probe or candidate-array writes; modulo bounds the read even for unusual chain values. For defined execution, chain visits, stopping, candidate sequence, tables, insertion/record code, costs, routes and output are expected identical. This is an equivalence inference awaiting444 native tests and all public token/output identities.

**Hypothesis:** the unchanged predecessor load can begin while the current input match is compared, reducing serial dependency latency. **Existing machine evidence:** the older R7 walk-outline ordinary walker reads the probe input word at0x1f670 and its next link at0x1f8e1, after probe/length processing. That proves a late-load instance in that older outlined function; it does not establish that current inline D is late. LLVM may already hoist it, or the longer next-value lifetime may add spills and become slower.

New Rust SHA256: `5be4838170b8eb45e2b7f11e53b54e7cd236bc572785fe595d3612c0da1cff8d`. New minimal Lean draft SHA256: `bd717cba95eb4ecc6c061169874621e80638b41e64ca46311831373c4b6d9224`. The proof changes only the existing modulo/index binding pair inside d_walk_loop_spec, moving it before probe_spec; its public signature,5-component loop state, depth measure and invariant are unchanged. No lemma/axiom/sorry is added. Actual extraction order and native proof checking are still UNKNOWN.

`scripts/build-round10-finder-linkearly.py --check` verifies accepted parent hashes, exact source/proof read-order reversals, unchanged byte lengths and per-file size limits. `source-proof-audit.json` records region hashes and moved bindings. Source/proof outside the single D walker region remain exact parent bytes. No new local mirrored-loop test is offered as evidence; the native finite framework and official paired measurement are the first effective behavioral/performance checks.

The main thread will retain actual benchmark release-code diagnostics for record and linkearly. `CODEGEN_AUDIT.md` defines the discriminator: compare role-specific predecessor-load and probe-load control/value dependencies in inlined D loops, accounting for spills. A different .so hash, renamed registers, shifted addresses or alignment alone cannot establish successful scheduling. Missing/truncated D code means UNKNOWN. Stop if the intended dependency change is absent, native output differs, or paired total time lacks a material positive signal. This is one candidate, not an instruction-order sweep; no6% gain is assumed from source inspection.

## Original DP insertion pipeline transferred to D

The source contains a second, distinct scheduling opportunity: original dp_parse lines1495-1509/1600-1609 already carry current bytes/hash/old heads across iterations, store current i using cached heads, and prepare i+1 immediately afterward. D still performs synchronous be8 and insert_pos at the start of each loop. Narrow searches of R7/R9 generator scripts, manifests and related reports did not find a previous D pipeline transfer. This is reuse of #361's existing mechanism, not an independent invention or another key/depth/state-capacity sweep.

`r10-finder-pipeline` is derived directly from verified record-nonempty, without linkearly. Rust SHA256 is `b74ae5fd9575101b6b34b9f2718d8835adca770c6765c30b33bb895878ba1adf`. Initial Lean remains `86cfc36adb009970bccbb5a9c543c5f559148d729e8c0f041934aab44e95592d`, explicitly **UNADAPTED_PARENT_DRAFT**. Reverse five exact D-region substitutions restores the record parent. Existing hashes/dp_store/dp_heads helpers and all matching/record/relax/backward/emit implementations, routes, keys and budgets remain original bytes.

After current stores, compute b8n/hn/pn1 for i+1. Ordinary and continuation branches reuse those values. A taken long match runs original insert_range, sets jumped, and prepares fresh state for the new i after those writes. Speculative pn1 is never reused after a long jump. Chunk/cost updates affect no head table.

The finite model compared cached versus synchronous insertion under48 fixed legal schedules at12 sizes and4 content/schedule modes, including tiny tails, constant/periodic/hash-colliding data, frequent/mixed long jumps and32768-byte ring boundaries. It compared actual b8/hash/old heads at every visited main/range position, predecessor writes and final arrays. All247949 main visits and936880 inserted positions agree;5827 long jumps include13 window crossings. Fresh jump heads differed from unused pn1 in5769 cases, demonstrating why refresh is essential. Receipt: `candidates/r10-finder-pipeline/pipeline-model-check.json`.

**VERIFIED local:** exact frozen parent hashes, generator/model binding, source reversal/reconstruction, unchanged parent Lean and per-file limits. **UNKNOWN:** native444 parser/record/token/decode equality, public output bytes, actual extraction interfaces, full proof, and paired time/code generation. The model treats schedules as independently fixed; it does not run the real DP planner or encoder.

Three conceptual pipeline states b8/hh/pre expand in the existing DP extraction to b8/x3/x4/x7/pre; anticipate five extra D function-state components and local jumped branch results, then adapt from actual Funs.lean. Reuse existing DP head/store contracts while retaining D's rs and invariants. Carry cached-head<=i bounds; do not weaken original obligation/axiom rules. No complete proof port is prepared before a performance signal.

The mechanism trades same ordinary-iteration insertion work for earlier overlap, but adds unused i+1 preparation on long jumps/final exit and lengthens cache live ranges across D's larger body. Existing DP use does not establish D speed. Actual release-code evidence must show lookahead head reads feeding the next iteration before current matching/record work, rather than just changed registers/addresses. Stop on cache/output mismatch, absent overlap, harmful spills or an unfavorable paired total-time result. One fixed pipeline transfer only.

## Actual release code and small same-output results

**Linkearly, run37695105461 / cpu-g:** native444 checks and all public token/byte identities match record-nonempty. Paired total time is +0.110205337% / +0.381367844%, mean +0.245786591%, with identical size. Stop this exact version without full gate or instruction-order variants; two small increases do not by themselves establish a statistically reliable slowdown.

Both saved objdump streams have a global2M-character cap, but complete candidate::parse::d_plan bodies and their following symbol headers are before that cutoff. The parent D function is16664 bytes and the candidate16693 bytes. The actual predecessor array roles are traced by current-index masking to0x7fff and the prev4/prev7 base offsets0x69c58/0xc9c58. Parent loads are0x21147/0x215cc at post-probe merges; candidate loads0x20f00/0x21334 occur before first-word comparison and extension decisions and feed later next-pointer comparisons0x21230/0x21652. This is a verified static dependency-order advance, rather than register/address renaming alone. Initial input word loads still precede the next-link reads, and dynamic CPU overlap is unmeasured.

The candidate also stores updated best length to[rsp+8] and reads it in loop guards, where the parent carries it in rcx. That storage change is observed; register pressure as the cause of absent speed benefit remains an inference without hardware counters. Digests, full target coverage, instruction excerpts, finite equality and timing are bound in `candidates/r10-finder-linkearly/codegen-result.json` and its readable `.md`. No independent binary rebuild or extra CI was used.

**Pipeline, run37695964878 / restore-h:** accepted extraction confirms31 D function-state components: the original26 plus current b8, three flattened hash indices and a three-head pre tuple. The public d_parse signature and8-component done result remain unchanged. Extracted hashes/dp_store/dp_heads definitions are exact parent bytes. Jumped paths fresh-read new i22 after range insertion; ordinary paths reuse b8n/i8/i9/i10/pn1. Frozen Rust/Lean were not edited; the new interface audit is `candidates/r10-finder-pipeline/interface-audit.json`.

Native444 token/decode and all public tokens/bytes match record. Paired total time is -0.222957519% / -0.412390392%, mean -0.317673956%, with identical size. This remains a small two-block signal; same-runner shadow drift reported by the main thread is on a similar scale, so do not call it robust confirmation or a new frontier. Preserve the source/interface without a complete proof port. Any later combination with a materially useful packing result must have its own exact-source verification and paired confirmation; its gains cannot be added arithmetically.

## One bounded confirmation proof preparation

At06:54 +08:00 the main thread explicitly changed allocation from waiting for a worthwhile improvement to one bounded confirmation preparation of the best currently unverified same-output source. The proof-bridge budget was20 minutes, with no unlimited repair cycle and no frontier-promotion claim. This implementation prepared the draft in about10 minutes; native compilation and confirmation are owned by the main thread.

Independent package: `candidates/r10-finder-pipeline-proof`. Rust remains exact frozen pipeline `b74ae5fd9575101b6b34b9f2718d8835adca770c6765c30b33bb895878ba1adf`. Lean draft is `e0ded4248a894e8c53bc1ce644c7c3f5c6681fe3c06eaab597caf10a5bf472db`,407432 bytes. The original frozen pipeline Rust/Lean pair remains untouched.

The port changes only d_parse_loop_spec and d_parse_spec. It adds actual31-component state handling and three cached-head<=i invariants, uses existing dp_store/dp_heads contracts for immediate lookahead, copies the proven original-DP fresh/cached jump selector pattern, and initializes the cache before calling the loop. Existing theorem names and all shared helper declarations stay unchanged; no lemma/axiom/sorry or verification-policy change is introduced. The final checked-emission/parse-validity proof suffix remains exact accepted-record bytes.

`scripts/build-round10-finder-pipeline-proof.py --check` reconstructs the independent package and checks frozen source, accepted actual Funs digest, state-interface evidence and file sizes. Additional local checks confirm31-element measure/invariant tuple patterns, declaration-name identity, unchanged Rust and proof prefix/final suffix. `proof-port-audit.json` and copied `interface-audit.json` distinguish these source/interface checks from native proof acceptance.

**Scope:** this is D planner totality with bounded probes and the retained original checked-emitter correctness theorem. It does not state universal token equivalence. New package metadata accurately records restore-h's444 finite same-token/decode cases and28 public token/output identities, and its small measured two-block time signal, while marking independent confirmation pending.

**Status: UNCOMPILED_ACTUAL31STATE_TOTALITY_BRIDGE.** Native Lean tactic closure, original obligation, allowed axioms and full public round trip for the new exact pair remain NOT_RUN. The main thread may freeze this version for one independent public comparison and complete gate; preparation does not itself establish an accepted faster program or a payable frontier position.
