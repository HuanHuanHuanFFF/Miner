# F4 narrow-column opportunity review

**Bounded read-only review.** I used only the completed R12 public-drawn plans for seeds 1224001, 1224003, 1224005, 1224007, 1224009 and 1224010. Each has 34 timed BMM cases; all six share the pinned public-v2 suite and generator hashes, and their BMM `work` sums match `public-cell-work.json`. No future holdout was read, and no candidate was generated.

## What the observed shapes say

The counters below are shape-volume proxies, **not time shares**. For each timed BMM case I count `work = batch*m*n*p` as MACs, `batch*m*p` outputs, `batch*m*n` A elements and `batch*n*p` B elements. Packed10 padding is counted from its ten-column groups: padded B fields are `batch*n*(ceil(p/10)*10-p)`; padded lane-MAC units multiply that by `m`.

| Shape set | Cases | MAC share | Output share | A-element share | B-element share | Packed10 padded B-field share | Packed10 padded lane-MAC share |
|---|---:|---:|---:|---:|---:|---:|---:|
| All `p=3 or 4` | 36 | 20.94% | 28.04% | 21.87% | 21.76% | 13.06% | 19.53% |
| All `p=3..8` | 75 | 40.60% | 56.95% | 32.66% | 44.33% | 17.40% | 24.99% |
| `p=3 or 4`, `n>4` | 26 | 14.46% | 3.83% | 15.07% | 14.63% | 8.84% | 13.45% |

The last row is the relevant dispatch slice for a narrow Packed10 replacement. In the current `f01-d11-bmm-combined-classifier` source, `p=3/4,n>4` falls through to `RowStream`/Packed10 unless the outer data-dependent underflow-zero branch returns early. The ten `p=3/4,n<=4` cases instead use DirectContinuous, so counting them as Packed10 savings would overstate this opportunity. The p=2 CrossRows guard is separate.

On the 26 Packed10-shaped `p=3/4` cases, the source model contains 2,116,027 padded B fields and 7,937,297 padded lane-MAC units. A four-column F4 model would have 266,893 padded B fields and 884,753 padded lane-MAC units, saving 87.39% of the modeled B padding and 88.85% of modeled padding-lane updates. For `p=3`, F4 leaves one of four lanes padded; for `p=4`, none. These are source-level counts: compiler elimination and elapsed-time impact remain unknown.

The `p=3..8` figures are context only. The candidate hypothesis is a single `p=3/4` F4 branch, not a width grid. A generic F4 loop at `p=50` adds two padded columns per four-column block and the archived R2-W02 model counts 520,000 rather than 500,000 MACs (+4%); that is a static count, not a measured slowdown.

## Historical source and evidence

There is already explicit four-output-column source. `f01-d2-web-packed4-proof1` and `f01-d3-word-packed4` define F4, `groups=(p+3)/4`, B packing by column block, and four separate accumulators for one row. The D3 exact Kernel (`fac8d334…34fceb`) has full-gate PASS rows for runs 39723695793 and 39726342678. Its archived legacy-suite `bmm` candidate/shipped ratios were 0.02816 and 0.03060, and whole-package ratios were 0.26800 and 0.26491. Those historical aggregate measurements were positive on that old suite, but they are not p-stratified and do not predict this R12 public-v2 slice.

The earlier R2-W02 package has a readable `NativePacked4.lean` implementation, but its own status says Lean elaboration, generated C, official gate and full-call timing were not run. Its Python shape/RN32 checks are synthetic and do not establish FloatLib conformance. R3-W01 adds outer matrix-bound and whole-call wrapper proofs, but it depends on `Packed4.within`/`within_eq` supplied outside that public parent; elaboration and timing are NOT_RUN. R4’s 2x4 tile source also records proof and performance as NOT_RUN.

The R11 `CrossRows` mechanism is not a four-column replacement. Its P12 packet holds four A rows and two B columns (eight outputs), and its dispatcher is guarded by `p=2`; the current classifier uses it only on that p=2 route. Current p=3/4 with `n>4` remains the ten-lane Packed10 path.

## Reuse, cost and first falsifier

The D3 full-gate source is a strong proof starting point: it already connects four F4 lane recurrences to the ordered scalar BMM result, with tail-column masking and the exact final-finite fallback. For the current source, the proof still needs rebinding to its current dispatcher, machine-size guards, output writer and exact fallback; the older pass does not certify a port. The reusable current interfaces are the Packed10 path’s per-lane finalizer and the `NativeFinal` ordered-dot/reference bridge. A narrow p=3/4 path needs the F4 `packB` lane theorem, four-lane recurrence projection, row/column address bounds and output-prefix connection, while preserving raw-input fallback.

The historical D2 full-gate Kernel is 72,452 bytes over a 56,956-byte protected parent prefix, a 15,496-byte source increase. The current accepted 6c source is 254,654 bytes, leaving 1,346 bytes under the 256,000-byte cap. Copying that generic payload wholesale cannot fit; a narrow branch’s source/proof size has not been established.

The first cheap falsifier, after separate authorization, is to inspect generated C for one current `p=3/4,n>4` case and determine whether the six/seven unused Packed10 lanes actually survive optimization. If the existing compiler already removes them, stop. If they survive, test only the `p=3/4,n>4` F4 branch with complete conversion, packing, output, fallback and full-call timing against a same-run current baseline. Stop if the complete call does not show repeatable improvement or if proof/source cost cannot fit the package. No such codegen or timing experiment was run here.

Run identities, exact plan hashes, metric totals, historical evidence hashes and limitations are in [review-f4-public-plan-opportunity.json](review-f4-public-plan-opportunity.json).
