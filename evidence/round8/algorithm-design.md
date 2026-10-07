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
