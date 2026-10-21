# Round 9 first-batch diagnostic conclusions

Scope: completed public screen and diagnostics from run `37660750561`, batch `block-a`, source commit `895ca6f98ef60e0f8cf2c082d619d45e68a2e60a`. This review does not report a new candidate, proof result, private-corpus score, admission, or reward. No implementation or CI action was performed for this review.

## Decisions

1. **Stop the whole q9 cache-prepass transplant for the current balanced-frontier effort.** The finder discovers additional valid matches, but its construction alone costs more than the complete #361 parser on every tested public DP file. Retain the discovery evidence for a later, cheaper supplementary-search design.
2. **Do not expect backward-DP micro-optimization alone to recover block1's required time reduction.** Its raw phase share is approximately 20% of D-routed parser time; the encoder, other routes, and official equal-file normalization reduce the modeled competition-axis contribution to approximately 13.6%, even if the entire backward phase becomes free while preserving its output. The supplied conservative target is 17.25%.
3. **Prioritize understanding the forward D stage for subsequent CPU work.** It consumes approximately 73% of D-routed parser time. This stage includes candidate finding, recording, forward relaxation, and other work; the coarse profile does not establish that `d_walk` alone consumes that share.

## Phase evidence, corrected using raw records

**VERIFIED:** `phase-diagnostics/phases.json` contains 84 successful reference/profile token comparisons: 28 files times 3 repetitions. Eighteen files call `d_parse`. For each repetition, summing the same files' raw phase nanoseconds and dividing by their raw instrumented-parser nanoseconds gives:

| Phase | Rep 0 | Rep 1 | Rep 2 | Pooled raw observations |
|---|---:|---:|---:|---:|
| `d_parse` | 73.206% | 73.663% | 73.144% | 73.339% |
| `d_dp` | 20.370% | 19.997% | 20.470% | 20.277% |
| `d_tally` | 1.588% | 1.566% | 1.591% | 1.582% |
| `d_extract` | 1.208% | 1.175% | 1.200% | 1.194% |
| `emit` | 3.488% | 3.419% | 3.480% | 3.462% |
| Other / timer overhead | 0.140% | 0.180% | 0.116% | 0.146% |

This calculation avoids adding independently selected phase medians. An equal-file average of each file's median raw fraction gives 71.212% for `d_parse` and 20.985% for `d_dp`, so the qualitative attribution does not depend on duration weighting.

These are instrumented parser fractions, not official total-compression-axis fractions. The aggregate instrumented/reference parser difference over those D files is -3.093%, +1.952%, and -3.152% across the three repetitions. Code-generation perturbation and run order are therefore visible. Use the stable 73%/20% split for coarse prioritization; do not infer a sub-percent real speedup from this profile.

## Official-axis-aligned linear scenario

**INFERRED model, not a hard upper bound:** `phase-axis-model.json` applies the phase evidence to the actual public timing formula. For each file i:

```text
f_i = mean over the 3 raw phase records of d_dp_ns / instrumented_ns
p_i = median of the 11 measured candidate parser time_s values
t_i = median of the 11 measured candidate total_s values
b_i = median of the 11 measured incumbent total_s values

original axis = mean_i(t_i / b_i)
free-backward scenario = mean_i((t_i - p_i * f_i) / b_i)
```

Warmups are excluded. All 28 files are retained, including zero `d_dp` fractions for non-D routes. File hashes agree between the phase corpus and benchmark receipts. The original axes replay the saved `state.json` metrics within 1e-12. The model retains every per-file input, phase ratio, and timing median, plus input-file hashes.

| Public block | Original balanced axis | Hypothetical free `d_dp` axis | Modeled reduction | Shortfall against 17.25% |
|---|---:|---:|---:|---:|
| 1 | 1.430898976 | 1.236392873 | 13.59328% | 3.65672 pp |
| 2 | 1.438140141 | 1.242390912 | 13.61128% | 3.63872 pp |

Using each individual phase repetition instead of the mean produces 13.395–13.825% reduction in block 1 and 13.413–13.844% in block 2. Within this model, meeting 17.25% would require eliminating approximately 126.9% or 126.7% of the backward phase, which is impossible under the stated decomposition.

The scenario means executing the entire backward phase at zero cost while preserving its exact output; it does not mean deleting the phase and losing compression quality. It assumes measured phase fractions transfer linearly to the uninstrumented sandbox parser, with encoder cost, other phases, memory behavior, and output unchanged. Those assumptions and the visible profiler perturbation prevent treating 13.6% as a universal or rigorous speed limit. The 17.25% requirement is the main thread's supplied conservative-frontier screening target, not a newly recomputed frontier result in this review.

## Why the tested backward changes are limited

**VERIFIED public screen, relative to paired block1 parent:**

| Candidate | Block 1 time change | Block 2 time change | Size change versus parent |
|---|---:|---:|---:|
| `r9-block-scalar` | -0.4861% | -2.1530% | 0 pp |
| `r9-block-unroll4` | +0.0175% | -0.5684% | 0 pp |
| `r9-push-single` | +0.2266% | -0.1898% | +0.006498535 pp |

Scalar and unroll each passed 444 finite token/decode equivalence checks against the parent. Their shared public size is `33.934365747942536%`. Push-single produces `33.94086428303839%` and deliberately changes the parse; it is not an equivalence candidate.

**INFERRED:** Scalar improves one length-minimum computation inside `d_dp`; it does not accelerate all of that phase. Its positive first-screen direction is consistent with a small recoverable cost, while the magnitude varies between blocks. Unrolling has not demonstrated an additional useful gain. Register pressure, short ranges, branch/setup work, or compiler-generated code could explain the limited result, but this profile does not distinguish those causes.

Push-single removes a subset of backward propagation work, giving no clear paired speed gain while losing approximately 0.00650 pp of size quality. It sacrifices roughly 27% of block1's historical public size gain over #361 without recovering meaningful time in this screen. Whether the removed pushes are rare or simply cheap remains UNKNOWN because the coarse timers contain no per-push event counts.

## q9 discovery evidence and construction cost

**VERIFIED:** `finder-diagnostics/finder-diagnostics.json` reports successful build/runtime, valid cached matches, preserved #361 tokens, and correct decoding for all 34 inputs: 28 public plus 6 deterministic synthetic files. Thirteen public files use #361's DP engine and contribute to the actual-search-position comparison.

Across 4,542,412 searched positions in those public files:

- q9 has a longer maximum at 202,049 positions (4.448%); #361 has a longer maximum at 39,500 positions (0.870%).
- q9 adds 739,265 supported length choices and loses 136,914, against 23,819,343 baseline choices: +3.104%, -0.575%, net +2.529%.
- At common supported lengths, q9 offers a lower distance price 159,222 times and a higher price 594 times. The summed modeled savings/cost increases are 274,198.25 / 383.3125 bits over alternative edges, not the selected path.
- No searched position has more than 16 q9 records, so this particular comparison is not hiding a measured capacity-overflow problem.

These observations establish additional valid choices, not an encoded-size gain. Length counts overlap in position and are not unique bytes saved. The baseline parser's plan/output was deliberately unchanged.

**VERIFIED diagnostic construction times:** On the 13 public DP files, the equal-file mean q9-finder / complete-#361-parser ratio is 3.543x in one ordering and 3.673x in the other, averaging 3.608x. Ratios of summed times are 2.393x and 2.584x. Every individual public DP file's finder is slower than its complete baseline parser in both observations; individual ratios range from approximately 1.03x to 8.58x. The finder has not yet paid for any downstream new parser/encoder work.

All six synthetic inputs route through DP. They show extra supported lengths with no lost lengths, but construction costs are approximately 22.96x–36.86x their complete #361 parser. This is consistent with the source-level mismatch: #361 efficiently skips searches inside long repeated matches, whereas q9 still maintains its tree and cache at every position. The timings remain coarse diagnostics with two orderings, no warmup campaign, and different allocation scopes; they are strong screening evidence against this full-prepass shape, not replacement official axes.

The 13 public DP files cumulatively produce 17,103,155 q9 match records. Summed vector capacities over files are 220,800,768 bytes; this is not simultaneous peak memory. The largest one-file cache capacity is 32,000,096 bytes on `prose.txt`, excluding fixed finder tables and the harness's second cache used for repeat comparison. Allocation and cache-record traffic may contribute to the construction cost, but no current counters separate them from tree traversal or byte comparison.

## What to preserve for a later cheaper mechanism

**INFERRED research direction:** Preserve the evidence that alternative discovery finds matches missed by the current chains, while preserving #361's cheap insertion and search schedule. Do not port q9's all-position tree/cache maintenance unchanged.

The next attributable question would be whether a bounded supplemental lookup, backed by O(1) per-position state updates, captures a useful subset of these opportunities. Candidates include an exact-tag two-slot 4-byte side cache alongside the existing chains, or a small extra search paid only at already-searched positions using an independently justified trigger. Keep existing matches and continuation available, so the supplemental path can be evaluated without silently replacing good baseline coverage. These are proposed mechanisms, not implemented or tested solutions.

Before selecting a trigger, a later authorized diagnostic should attribute new q9 winners to the near-tag path versus tree traversal, candidate depth, and cheap features of the baseline state. The current receipt lacks that provenance, so it cannot establish that the inexpensive two-slot component explains the observed gains. Do not assume that calling a mutable tree only at searched positions preserves its cache: skipped insertions change future candidates and require a new validation experiment.

Public opportunities are also uneven: `multibyte.txt` supplies 37.25% of added length coverage and 42.42% of the net added coverage. That suggests checking mechanism/content dependence, not introducing file-name or exact-length routing. The existing six synthetic cases show that opportunity can persist while maintenance cost worsens dramatically.

A streaming tree would remove whole-file record storage but still incur all-position insertion work. Treat it as a separate unmeasured design with uncertain benefit, not a proven fix for the 3.608x prepass cost. No such implementation is authorized or started by this review.

## Evidence pointers

- Raw phase records: `evidence/round9/37660750561/block-a/screen/phase-diagnostics/phases.json`.
- Finder counts, timings, and validation: `evidence/round9/37660750561/block-a/screen/finder-diagnostics/finder-diagnostics.json`.
- Official paired screen: `middle-analysis.json`, `state.json`, and `round{1,2}-r7-mid361-block1.jsonl` in the same screen directory.
- Finite candidate equivalence: `equivalence-research.json` in that directory.
- Axis-aligned model with per-file values and source hashes: `evidence/round9/phase-axis-model.json`.

These results distinguish measured public evidence from model-based interpretation. Private behavior, admission, reward, and any future supplemental-finder performance remain UNKNOWN.
