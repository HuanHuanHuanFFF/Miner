# Round 4 family audit: public compression-side reference #299

## Selection and official evidence

This audit is pinned to official Pareto snapshot **24346**, computed at `2026-10-06T19:51:20.375061+00:00`, policy `compression-policy-c255effb7d5afeef`, `freshness=unknown`. The complete API pagination returned 439 items across five pages, with 71 scored frontier points. The current size endpoint is #305 at time ratio 8.318555305 and mean file compression 34.100976621%; #299 is a published, beaten point close to that side of the frontier.

The pinned official item for #299 reports `gate_status=passed`, all four detail pipeline stages (`static`, `lean`, `benchmark`, `aggregation`) passed, admission `not_required`, and `score.on_frontier=false`. Its hotkey is `5En8AugiKmLmnoaWzrGMz9oWMbQYvekaMvZSjViLTLhrrq4E`; official metrics are time ratio **9.176642755**, mean file compression **34.102373220%**, total compression **11.179767711 s**, LZ77 **10.686418672 s**, and byte-weighted compression **30.834196485%**. Relative to #305 it is 0.001396599 percentage points larger and 10.3% slower, so #305 dominates it at this snapshot. This is a useful near-size-end code reference, not current frontier membership or a reward claim.

The official source endpoint returned HTTP 200. The bytes are stored under `references/round4-public-299/`:

- `parse.rs`: 105,064 bytes, SHA-256 `71314c4da7ccd29331a360bce9be8697857109c66adc87d3480eeaa22930625d`.
- `Parse.lean`: 279,475 bytes, SHA-256 `9b77b3523cbf7044aaffa11b6fd9676b3615ca4bf148b43b3cb92da4073b3e3d`.
- Each file is below the official 524,288-byte per-file cap. The pinned detail endpoint reported a source hash matching `parse.rs` and a combined digest matching SHA-256 of the saved `parse.rs` bytes followed by `Parse.lean` bytes; both checks are recorded in `PROVENANCE.json` with UTC retrieval times.

## Actual parser path and routing boundary

The callable path is `parse` (line 75) → `make_plan` (line 252) → `classify` (line 169) → `plan_cfg` (line 237) → one of engines A/B/C → the shared `emit` (line 50). The code does not dispatch on an exact corpus file length, file name, sample name, or a fixed content hash. `classify` uses byte-class proportions from `sample_counts`: for inputs up to 32 KiB it scans the whole slice; larger inputs use 32 evenly spread 1 KiB windows. It selects broad content classes such as DNA, sparse data, high-byte binary, structured text, tables, logs, or default text.

There is one global resource guard: `make_plan` returns an empty plan for inputs at least 67,108,864 bytes (64 MiB). The shared emitter then treats absent plan entries as literals. The guard is broad and input-size based, not a corpus identity route; it avoids the `a_engine` allocation expression `n * 3 + 16` overflowing. It preserves the token decoding contract but makes very large inputs compress as literals, so a derivative must check all relevant corpus sizes before retaining it.

The top-level routing differs from the two excluded candidates. #413 is part of the `fastX` family used by #431/#432. #398 is a sibling of #402's exact-length portfolio route and has the exact same `Parse.lean` hash as #402. #304 also uses `parse → route` with many exact `n == ...` branches and a 493,870-byte proof; it is excluded from this family choice. #299 is a plan-based composite with content-class routing and no exact-length equality branches.

## Mechanism worth isolating

The source has three class-selected engines. A (`a_engine`, line 967) builds a whole-input match cache, runs backward dynamic programming over bounded ranges, gathers length/distance symbol counts, and revises its per-symbol costs over several passes. B (line 1630) searches structured text and runs segment/block dynamic programming with symbol tallies. C (line 2864) classifies DNA/binary by repeat statistics, chooses a bounded match search, then performs weighted DP passes and can clear blocks to literals when the block-cost estimate prefers them.

The smallest promising module is A's **Huffman-derived transition-cost model**, not the full three-engine portfolio or its router. `a_set_costs_huff` (line 685) is called from `a_engine` on later unsampled passes (lines 1036–1039). It derives length-limited Huffman code lengths from literal/length and distance histograms, assigns costs to literal, match-length, and distance choices, and adds DEFLATE extra-bit costs. `a_huff_lengths` and `a_kraft_fix` use fixed-size tables and cap code lengths at 15. A minimal experiment would keep the incumbent's broad content-independent match source and verified emitter, then use this table to price one additional DP pass. That tests whether cost-aware path choice helps size without importing the class router or all three engines.

This is an **INFERRED** transfer hypothesis. The public aggregate score cannot identify which class or engine produced #299's compression result; public per-file and per-engine results are unavailable. The model prices symbol codes but does not by itself establish exact compressed byte cost, including dynamic-tree/header tradeoffs, so compare its predictions with the official encoder and use paired end-to-end compression measurements before calling it beneficial.

## Proof shape and likely migration cost

`Parse.lean` imports `Lz77` and `Slot`. `check_spec` (line 231) establishes match bounds and byte equality. `emit_loop_spec` (line 248) carries the decode invariant: accepted suggestions become match tokens through `LZ77.emit_match`, while invalid or missing plan entries become literals through `LZ77.emit_lit`; `emit_spec` (line 295) closes that loop. `parse_spec` (line 6073) composes the extracted parser and proves `LZ77.Valid`. The search and plan builders need not prove that their suggestions are useful, but their loops, index arithmetic, and allocations still need Aeneas/Lean totality and safety proofs. The official snapshot reports the downloaded source's gate and all pipeline stages passed; this is not evidence for any derivative.

Keeping the existing `check`/`emit` boundary should limit token-correctness proof changes. The cost tables themselves are fixed-size and a narrow cost-helper port is likely easier to bound than moving `a_engine` wholesale. The larger DP port introduces loop variants, vector bounds, overflow-safe cost arithmetic, and the 64 MiB resource boundary; removing or raising that guard requires reworking the `n * 3 + 16` allocation and proving the replacement for every input. The proof file remains below the cap here, but it is not small enough to treat a full engine import as free.

## First falsifiable test and stop conditions

First compare the helper's per-symbol costs with the official encoder on a few fixed stage1 files, then run one paired public-corpus experiment with only one additional model-guided DP pass. Keep the search space and verified emitter fixed so the result can be attributed to the cost model. Stop if the chosen paths do not reduce end-to-end compressed size beyond measurement noise, if the extra pass pushes the time axis outside the available frontier margin, if the cost estimate repeatedly disagrees with encoded block costs, or if the isolated proof cannot retain the current all-input contract within the official file-size cap. Do not transfer per-file route conditions or the full A/B/C portfolio on the basis of this aggregate result.

## Evidence gaps

- **UNKNOWN:** contribution of engines A, B, and C to the published aggregate; no per-file public metrics identify it.
- **UNKNOWN:** behavior of a derivative on private stage2 or its online admission/frontier status.
- No local Rust/Lean tools or candidate CI were run in this audit.


## Follow-up: read-only review of the two CFG budget derivatives

`python scripts/make-round4-alt299.py --check` reproduced both candidate artifacts byte-for-byte. The candidate `parse.rs` files equal the pinned #299 source outside the single `CFG` table (after the generator's CRLF-to-LF normalization; the official source itself has no CRLF). Both `Parse.lean` files are byte-identical to the #299 proof. No candidate source was edited during this review.

The CFG layout is `[engine, depth, skip, first_passes, first_sampled, later_passes, spass, ...]`. `spass / 16` encodes the rotation bit(s), while `spass % 16` is the sampled count. The actual A loop samples a pass only when `k < sampled`, `k + 1 < passes`, and the current span exceeds `4 * A_SEG * A_SAMPLE`; otherwise it runs a full `a_dp_pass`. Thus actual full-pass count is at least `passes - min(sampled, passes - 1)`, and configured sample passes can still fall back to full work on short spans.

- `r4-alt299-halfpass` changes only A rows' first/later total pass budgets and sample counts. Total budgets use ceil-half; sample counts use ceil-half and are capped so at least one configured full pass remains. Rotation quotient is preserved. Depth and skip are unchanged. The budget cap and sample counts are small (no changed pass budget exceeds 8; the largest configured first-phase sample count is 5 and the largest later-phase sample count is 4). This does not guarantee half the elapsed time because of the short-span fallback.
- `r4-alt299-samplemore` keeps first/later total budgets unchanged and raises each sampling count toward `passes - 2`, retaining a larger original sample count when it already left fewer than two full passes. That exception occurs in row 7's first phase (9 passes, sampled value 9 means eight eligible sampled passes plus one mandatory full final pass) and row 8's later phase (5 passes, four sampled plus one full). All changed sample counts are representable in the low four bits; rotation quotients are unchanged. The greatest new sample count is 14 for a 16-pass budget, leaving two full passes.

The halfpass generator also updates CFG rows 13–15, whose `CLASS_CFG` entries are marked unused and which no class currently selects. That is harmless to current routing but unnecessary for a minimal diff; the samplemore variant leaves them unchanged. Both variants leave the classifier, class mapping, depths, match-finding settings, plan check, emitter, and size guard unchanged. Numeric CFG values remain within the source's existing table/index ranges, but the inherited Lean file is not fresh proof acceptance: new Charon/Aeneas extraction, `parse_spec`, axiom whitelist, and round trip remain required before a correctness claim.

## Follow-up: `a_set_costs_huff` versus the official encoder

The official encoder is `sources/conjectures-optimisation-deflate/validator/measure/src/deflate.rs`. The two implementations agree on the broad inputs to a token path cost: both use 16,384-token blocks, 15-bit literal/length and distance codes, and RFC length/distance extra-bit counts. An exhaustive table comparison checked all 256 legal lengths and 32,768 legal distances and found the symbol index and extra-bit count match exactly. #299's `a_walk` records an EOB count; the encoder adds EOB once when finalizing each block.

They do **not** use the same tree algorithm or exact bit objective. #299's `a_huff_lengths` builds a frequency-ordered ordinary Huffman tree, clamps depths over 15, then lengthens rare codes until its Kraft sum fits. The official encoder's `package_merge` constructs optimal code lengths under the 15-bit limit from only symbols with positive final frequency. `a_set_costs_huff` first adds one to every one of 286 literal/length frequencies and all 30 distance frequencies, including symbols absent from the current plan; the encoder uses actual per-block token frequencies (plus one EOB, and a distance-code-0 fallback only when there are no matches). The model then charges symbol-code bits plus length/distance extra bits, but omits the dynamic header and code-length RLE cost and the encoder's fixed/dynamic/stored choice. Its counts may also come from sampled or previous paths rather than the final block.

So this helper is a cost heuristic, not a reproduction of the encoder's bit count. It may rank paths differently, especially for sparse alphabets or deep/length-limited trees. A small test should compare predicted token-symbol cost changes with the actual encoded block/whole-file size before spending a full paired corpus run; no such experiment was run here.
