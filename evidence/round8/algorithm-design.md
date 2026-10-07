# Round 8: cost-aware reuse of #361's existing candidates

Status: design only, 2026-10-08 Asia/Shanghai. No candidate source, proof, CI, submission, or wallet action was performed by this analysis task.

## Decision

**INFERRED:** Test the existing-candidate cost blind spot before collecting new candidates. The mechanism is distinct from round 7's depth, lazy, cost-update, and extra-pass sweeps. All three proposed variants preserve `walk`, `walk_t`, candidate capacity/order, continuation selection, and search budgets. They change only forward relaxation inside `rc_seq`.

**VERIFIED:** At repository HEAD `782cd10b830765bc971c04a0bb8f38280afd1a99`, `references/round7-public-361/parse.rs` has SHA256 `f426f7cec777ef2ca74616eb62205d54ae0bf6938799835a1fe6024ed59b5c45`. Its proof SHA256 is `f815bcb880d9da3c18d8fcb768f66ea2222a6348187646eb027c1cb020bb2fb0`. The inspected block1 source SHA256 is `950eb21b3918adce71bad2737774f2e37531cfbcd45fb17afdd806ee0adc3ed5`.

The round 7 recorded result is 17 candidates with zero predicted share under its saved frontier snapshot. `block1` bought approximately 0.02426 pp public size improvement for 23.4% more paired total time; `lazy1` saved approximately 6% time while losing 0.03841 pp. These are historical public measurements and snapshot projections, not current admission or reward evidence. See `OPTIMIZATION_METHODS.md:35`, `:104`, and `evidence/round7/final-summary.json`.

## Why the existing representation loses cost choices

**VERIFIED from source:**

- `probe` (`parse.rs:936`), `walk` (`:962`), and `walk_t` (`:1313`) retain length records. A shorter or equal match is not retained by those chain walks.
- `rc_seq` (`:1412`) treats the retained lengths as increasing breakpoints. For candidate k it relaxes `previous_length + 1 .. current_length`, starting at 3. It chooses only candidate k's distance for that interval.
- A later candidate j has sufficient match length to cover all of candidate k's interval. If its distance cost is lower, the current relaxation misses that lower-cost edge.
- `dcc` includes distance-symbol cost plus extra bits (`make_costs`, `:819` onwards). It is learned from counts and does not have an invariant requiring cost to increase with distance. Combining different hash chains also does not promise monotonically increasing retained distances.
- Backward extension uses the original candidate's exact distance and length (`:1436`). It must continue to do so after forward-distance selection changes.

For example, retained candidates `(length=6, distance=100)` and `(length=12, distance=200)` with respective distance costs 100 and 80 currently give lengths 3..6 the costlier distance. The second match supports those lengths and saves 20 cost units. This is an illustrative state, not a measured occurrence in the corpus.

**UNKNOWN:** The frequency and aggregate value of those states. There is no evidence yet that this blind spot explains a useful part of the frontier gap. The prices are approximate learned costs, so locally cheaper edges do not guarantee a smaller encoded file after changed symbol statistics and block boundaries.

## Three controlled variants

All variants start from the public #361 reference, not the block1 extra-pass routing. Leave `lo = len + 1`, the outer loop, and all backward-extension code intact. The original `c`, `len`, `dd`, `ds`, and distance cost remain the variables used by `back_best` and its subsequent relaxations.

### A: all lengths, diagnostic reference

Replace only:

```rust
relax_seq(pa, lc, i, lo, len, bd, c & !511u32);
```

with:

```rust
relax_seq(pa, lc, i, 3, len, bd, c & !511u32);
```

This considers every retained distance for every supported length. It adds no chain search or candidate storage, but repeats price-ring updates for overlapping ranges. It is a quality reference for the retained set, not an expected speed winner. It is not an upper bound on final compression quality: later learned prices can change with the chosen path.

### B: current versus longest distance

Before the forward call, compare the original candidate with `cands[nc - 1]` (in the real caller `1 <= nc <= 16`). Choose the lower `dcc[dsym(dtab, distance) % 32]`; if costs tie, choose the smaller `candidate & !511u32`, matching `relax_seq`'s packed-choice tie break. Then call:

```rust
let fd = (forward_c >> 9) as usize;
let fds = dsym(dtab, fd) % 32;
relax_seq(pa, lc, i, lo, len,
          base.wrapping_add(dcc[fds]), forward_c & !511u32);
```

The longest candidate covers every original length interval, so this is semantically valid without changing the breakpoints. Keep its length out of the call: `hi` is still the original `len`. Cache the longest candidate and its distance cost outside the loop if the compiler does not already hoist them.

**INFERRED:** B has a small comparison cost and catches long-chain distances that are cheap relative to earlier records. It misses a cheap intermediate candidate when the final one is expensive.

### C: minimum distance cost in the suffix

For original candidate k, select the cheapest distance among candidates k..nc. Each member of this suffix covers the complete original interval `lo..len`. Use the same tie break as B.

Recommended first implementation: an independent helper, keeping `rc_seq`'s loop state shape close to the existing proof. This is deliberately bounded O(nc squared); the maximum meaningful comparisons across 16 candidates is 120, plus the repeated self-comparisons shown below. Actual candidate-count distribution remains UNKNOWN.

```rust
#[inline(always)]
pub fn cheapest_suffix(
    cands: &[u32; 16], nc: usize, k: usize,
    dtab: &[u8; 512], dcc: &[u32; 32],
) -> u32 {
    let mut chosen = cands[k % 16];
    let mut price = dcc[dsym(dtab, (chosen >> 9) as usize) % 32];
    let mut j = k;
    while j < nc && j < 16 {
        let q = cands[j % 16];
        let p = dcc[dsym(dtab, (q >> 9) as usize) % 32];
        if p < price || (p == price && (q & !511u32) < (chosen & !511u32)) {
            chosen = q;
            price = p;
        }
        j += 1;
    }
    chosen
}
```

Call `cheapest_suffix` only to produce `forward_c` for the B call shape. Do not assign its return to the original `c` variable; doing so would accidentally change backward extension and continuation-related distance exclusion.

If C has useful compression but unacceptable overhead, the next CPU version is an O(nc) reverse sweep producing `suffix_choice: [u32; 16]`, followed by the existing forward loop. It adds 64 bytes of temporary storage and one bounded loop, but changes the extracted loop's environment and requires corresponding proof work. That optimization is conditional on first finding a useful quality signal; it is not needed for this three-variant comparison.

## Semantics and comparison checks

**INFERRED, directly checkable:** With fixed arriving costs and fixed `lc/dcc`, ordered candidate lengths, and no wrapping overflow in the price sum, A and C produce the same minimum forward transitions. C enumerates the lower envelope of exactly the distances A considers for each length. The tie break on packed distance is necessary for equal-cost token equivalence.

The backward-extension code reads arriving costs at `i - t`, while these forward relaxations write positions at least `i + 3`. Lengths/backward extensions are at most 258 and the ring is 8192, so these operations do not alias the earlier arriving slots in the ordinary valid DP state. This supports A/C token-equivalence testing; it is not a completed formal equivalence proof.

Run a finite token/decode comparison of A against C on the public corpus and generated inputs. An A/C mismatch is a diagnostic to resolve, not performance noise. Possible causes include tie-breaking, selecting `hi` from the replacement, modifying original backward-extension distance, incorrect suffix bounds, or price-wrap behavior. B need not equal either.

## Proof impact

**VERIFIED:** This #361 planner is untrusted search followed by checked emission. Unlike older probe2's fully verified matchfinder path, the relevant `rc_seq_loop_spec` and `rc_seq_spec` conclude totality (`True`), at `Parse.lean:1106` and `:1127`. The unchanged checked `emit` establishes valid output. The parent proof cannot simply be declared applicable to changed extracted code.

- A: expected minimal proof change; forward relaxation's low endpoint changes while the helper already has an unrestricted totality lemma.
- B: add totality support for any helper/comparison and update extracted bindings. The original backward arithmetic facts should still apply if original `c` remains unchanged.
- C: add a totality lemma for the bounded helper loop, measure `16 - j.val`, using `dsym_spec`; register its helper spec before the existing `rc_seq` proof. Preserve original variables to avoid disturbing the existing `dp_shr9 c` fact used for backward-extension bounds.

**UNKNOWN:** Actual extraction shape, Lean repair effort, and gate result until the exact candidate files are extracted and checked. Acceptance still requires official extraction, original obligation, axiom audit, and public round trip for the selected exact hashes.

## Minimal falsification and advancement

1. Measure baseline/A/B/C with the same public inputs, official encoder, paired processes, runner identity, and raw per-file results. Keep timers free of instrumentation. A is primarily a diagnostic reference; compare A/C tokens as well as sizes.
2. Independently count `nc`, positions with a cheaper suffix, lengths whose selected distance changes, and minimum-model-cost savings if affordable. These counters explain an outcome; they are not performance evidence.
3. If A/C do not improve public size, and B also does not produce a viable time/size tradeoff, downgrade existing-candidate distance selection rather than starting another cost-table or depth sweep. If A is smaller but C differs, first resolve the semantic discrepancy.
4. If B or C improves size, compare paired total time with shadow/noise and re-evaluate the current frontier using #361's family anchor. A tiny compression change accompanied by measurable slowdown is not sufficient just because the local model is more complete.
5. Only a surviving exact candidate proceeds to its full gate and independent runner repeat. Public improvement, gate acceptance, projected frontier membership, online admission, and reward remain separate results.

No predicted online benefit or payment claim is made here. Formal #361 anchor `1.1608686942402877 / 34.209957755736326%` and public reference `33.95862675598211%` are the supplied historical calibration values, not newly fetched live state.

## Diagnostic implementation prepared for CI

`scripts/research-round8.py` generates an instrumented Rust copy and standalone harness only under `RUNNER_TEMP/round8-cost-diagnostic-build`. It writes JSON and text logs under `RUNNER_TEMP/round4-receipts/cost-diagnostics`; no Rust source or executable is placed in the receipt directory. With a batch specification present, the script returns immediately unless `cost_diagnostics` is exactly `true`. An enabled batch must uniquely contain the parser SHA256 pinned by the original suffix candidate's manifest; this permits the byte-identical `r8-mid361-cost-suffix-proof` source used in cost-b and records its actual path and name.

The harness parses each of the 28 public files once, separately validates token decoding, and records atomic counters: candidate-count histogram at `rc_seq` calls, cheaper-distance and equal-price/nearer-distance replacements, covered forward lengths, total modeled edge-price differences in 1/16-bit units, and actual suffix-helper iteration counts. It does not execute the encoder or time parsing. Summing alternative edge-price differences does not measure selected-path savings or compressed bits. Histogram coverage excludes continuation-only and take-as-is positions that do not enter `rc_seq`.

**VERIFIED locally:** Python syntax, three exact source insertion points, source-drift and repeated-instrumentation rejection, positive/negative counter-schema checks, cost-b selection by exact Rust hash, rejection of missing/duplicate matching entries, and disabled-spec return before validation or temporary-directory access. The inspected source hash is `e95295f269b59d9ea5ff813bee4914de2604dea45e4070d54b3e47fcd5bd4f21`; those local checks did not change the candidate.

**UNKNOWN / NOT RUN by this analysis task:** Rust compilation of the diagnostic, public-corpus diagnostic counts, and their relationship to measured performance or compression. No diagnostic CI was started by this task. The main agent owns workflow integration and execution.

## Conditional CPU follow-up: one suffix sweep and a single-candidate path

This is a design awaiting the cost-a/cost-b measurements, not a new candidate or implementation decision.

**VERIFIED from actual extraction:** `evidence/round8/37651940395/cost-a/extraction/r8-mid361-cost-suffix/Funs.lean:7368` extracts the selector loop with mutable state `(chosen, price, k)`. At `:7462` / `:7539`, `rc_seq_loop` keeps only `(pa, lo, k)` in its mutable state; candidate arrays and price tables are fixed environment parameters. At `:7482`, every interval calls the selector, then performs another `dsym` lookup for the selected distance. A precomputed cache can therefore be a fixed parameter of the relaxation loop rather than a new mutable loop invariant. This is an observation about the recorded extraction; a changed source still needs fresh extraction.

Preferred structure if suffix selection proves useful but its repeated scanning costs time:

```rust
// Conceptual structure; not added to any candidate.
pub fn rc_seq(/* existing arguments */) {
    if nc == 0 {
        return;
    }
    if nc == 1 {
        rc_seq_one(/* existing arguments, c = cands[0] */);
        return;
    }
    let prices = rc_suffix_prices(cands, nc, dtab, dcc);
    rc_seq_cached(/* existing arguments */, &prices);
}

pub fn rc_suffix_prices(
    cands: &[u32; 16], nc: usize,
    dtab: &[u8; 512], dcc: &[u32; 32],
) -> [u64; 16] {
    let mut result = [0u64; 16];
    let mut k = if nc < 16 { nc } else { 16 };
    let mut best = u64::MAX;
    while k > 0 {
        k -= 1;
        let c = cands[k];
        let ds = dsym(dtab, (c >> 9) as usize) % 32;
        let key = ((dcc[ds] as u64) << 32) | ((c & !511u32) as u64);
        if key < best { best = key; }
        result[k] = best;
    }
    result
}
```

The key stores the unmodified distance price in the high 32 bits and `distance << 9` in the low 32 bits. Unsigned comparison implements price then nearer-distance ordering; the length bits are zero. Unlike comparing already-added DP prices, this key introduces no dependence on the arrival price or length price. Equal keys need no special index tie break because their forward distance and price are identical.

`rc_seq_cached` retains the original forward order, `lo`, original `c`, `len`, `dd`, and `ds`. Only replace the selected-distance computation and forward call:

```rust
let key = prices[k];
let forward_price = (key >> 32) as u32;
let forward_distance_pack = key as u32;
relax_seq(pa, lc, i, lo, len,
          base.wrapping_add(forward_price), forward_distance_pack);
lo = len + 1;
// The entire original backward-extension block follows, using original c/dd/ds.
```

The 128-byte `[u64; 16]` cache stores prices as well as distances, eliminating the selected-distance `dsym` lookup during relaxation. A 64-byte `[u32; 16]` candidate-only cache is a fallback if the packed form creates extraction or code-generation trouble; it has the same O(nc) selection work but retains a forward price lookup. Neither layout's speed is established from its size or operation count.

`rc_seq_one` performs the original single iteration: compute original `c/len/dd/ds`, relax `3..len` using `dcc[ds]`, then execute its backward-extension block with the original values. The original eligibility condition `k + BEXT_TOP >= nc` becomes `BEXT_TOP >= 1` for `k=0,nc=1`; retain that condition rather than assuming the currently recorded constant 2 forever. Its `BTRUNC` branch stays byte-for-byte equivalent in meaning. This path constructs no cache, performs no suffix scan, and does not duplicate the distance-symbol lookup for the chosen candidate. Dispatch occurs before the cache declaration, so source-level initialization of the cache is absent on this path; generated machine code still needs inspection if timing is surprising.

### Proof migration

- `rc_suffix_prices_loop`: termination measure `k.val`; invariant `k.val <= 16`. The guarded subtraction establishes the next index below 16. Array reads/writes, shifts, casts, and `dsym_spec` establish totality; the public obligation does not require proving suffix optimality.
- `rc_seq_cached_loop`: retain the existing measure `16 - k.val` and trivial invariant. Add the immutable price-cache parameter and its bounded read. The original `dp_shr9 c` fact and backward arithmetic remain applicable because original `c` is retained.
- `rc_seq_one`: a straight-line totality lemma using the existing `relax_seq`, `back_best`, and `relax_one` lemmas, with the same input-length assumptions as `rc_seq_spec`.
- `rc_seq_spec`: keep the existing external signature/postcondition; split the two small-count branches and call the new helper specifications. Callers such as `dp_parse_loop_spec` should then need no semantic expansion, although generated binding changes must be checked.

The exact generated definitions and all proof compilation outcomes remain UNKNOWN. Require byte-identical token output against the original suffix candidate on the existing finite suite and public files, followed by the fresh gate for any promoted exact source/proof pair. Packed caching should preserve suffix choices even when DP addition wraps, since it chooses using the same raw `dcc` and tie ordering; the separate A-versus-C equivalence argument still has its stated price-wrap caveat.

**VERIFIED finite model check:** 1,700 generated candidate/price lists covering counts 0..16, price ties, and `u32::MAX` agreed between repeated suffix selection and the reverse packed-key minimum. This checks the isolated key selection model only; it is neither a Rust execution nor a token-equivalence result.

### Use the diagnostic to decide, then stop when warranted

For histogram H[n], the current exact helper performs `sum(H[n] * n*(n+1)/2)` loop iterations, including self-comparisons. A cache restricted to n >= 2 performs `sum(H[n] * n)` iterations over those entries; the single-candidate branch performs none. The source currently has approximately `n*(n+1)/2 + 3*n` distance-symbol lookups per nonempty `rc_seq` call before compiler common-subexpression elimination: one initial lookup per selector call, its loop lookups, and the original/selected lookups in the outer loop. The packed-cache multi-candidate path has 2*n such source lookups if original `ds` computation stays in place; the single-candidate path has one. These are source-operation counts, not a CPU-time prediction.

Advance only after A/C output agreement is checked, the quality gain survives cost-b, and the observed slowdown is larger than the shadow/run-order noise or leaves a meaningful current-frontier gap to recover. If H[1] dominates and larger counts are rare, the single-candidate fast path is the first attributable change; if larger counts contribute materially, add the reverse cache in the same mechanism-focused follow-up or as a separate comparison. If top-only already gives a better measured size/time result, prefer that simpler surviving choice over optimizing suffix merely for completeness.

Stop this CPU follow-up if existing-candidate cost selection has no useful compression gain; if token equivalence fails; if cache setup/copies/extra branching erase the saved work; or if paired improvement is indistinguishable from shadow variation. A reduction in diagnostic comparisons alone is insufficient. Evaluate the best achieved time at the measured size against the current frontier before spending another runner on this mechanism.

## Measured negative result and stop decision

**VERIFIED:** Public screens from runs `37651940395` (cost-a) and `37653054884` (cost-b) returned the same size for A/full, B/top, and C/suffix: `33.958678263403264%`, which is **0.000051507421 pp worse** than the paired #361 reference. A/C also passed 444 finite token/decode equivalence cases with zero differences in each run. These are two repetitions of the same finite suite, not 888 distinct cases.

| Variant | cost-a paired time changes | cost-b paired time changes |
|---|---|---|
| A/full | +0.2637%, -0.3019% | -0.2440%, -0.3533% |
| B/top | +0.9982%, +0.5259% | +0.4056%, +0.7980% |
| C/suffix | +2.5768%, +2.2942% | +2.8440%, +2.2832% |

The first run's same-byte shadow varied from +0.1729% to -0.5753%. A's small apparent timing changes therefore do not establish a stable optimization. B/C have the same slightly worse output while adding measured time, especially C. The first per-file diagnosis records token changes on 13 files, but the aggregate encoded output grows by only 10 bytes; token changes alone did not yield compression improvement.

**VERIFIED diagnostic:** `cost-b/screen/cost-diagnostics/cost-diagnostics.json` reports successful Rust compilation, runtime, and decoding for all 28 files. Across 4,529,710 `rc_seq` calls it sees 5,988,653 candidate segments and 22,169,195 supported lengths. A cheaper distance replaces 36,818 segments (**0.614796%**) covering 84,301 lengths (**0.380262%**). Equal-price nearer replacements are zero. The suffix helper runs 9,267,822 loop iterations. Empty candidate lists account for 19.5722% of calls; one-candidate lists account for 42.2565%.

The summed edge-price difference is 734,283 units, or 45,892.6875 model bits. It sums alternative transitions and does not count only the final chosen path; actual encoded output did not improve. The diagnostic confirms that the source-level cost blind spot occurs, while the paired result falsifies its usefulness for this tested #361/public configuration.

**Decision:** Stop the existing-candidate cost-selection direction for this round. Do not implement the suffix cache or single-candidate CPU variant described above. Those changes could remove C's extra overhead, but no measured quality gain remains to justify that work, and A already provides the same quality at roughly baseline time. This conclusion does not establish that all cost-aware candidate generation is useless; it rules out promotion of these exact retained-candidate mechanisms on the available public evidence.

Evidence: both runs' `screen/middle-analysis.json` and `screen/equivalence-research.json`, `evidence/round8/first-screen-file-changes.json`, and `evidence/round8/37653054884/cost-b/screen/cost-diagnostics/cost-diagnostics.json`. All formal transfers remain INFERRED. This stop decision creates no candidate, submission, chain action, or CI cancellation.
