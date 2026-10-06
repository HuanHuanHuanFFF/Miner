# Round4: bounded lookahead on fast3

## Initial batch

**VERIFIED (local source checks only):** `scripts/make-round4-parse.py` locks the fast3 source and proof SHA256 values, generates four candidates, and `--check` reproduces all files byte-for-byte. Every parser/proof is below the submission file limit. No Rust or Lean toolchain was invoked locally.

Base: `candidates/r3-432-fast3`, source `bae8014121e4710f4a34ce63452578b4bf69121b4f695e1b1356780a019108ef`, proof `e2c200cf084eca95eb70d26c0efb04e70d88f015315610d2a54d20b6adb7cf04`. This is a derivative of public submission 432; the original attribution remains in `references/round3-public-432/PROVENANCE.md`.

| Candidate | Change | Source SHA256 |
| --- | --- | --- |
| `r4-parse-lazy6` | P_LAZY 0 -> 6: inspect the existing prefetched p+1 candidate only after lengths 4 or 5 | `e893251c1d4cea433381b660d4c715763eb70178b9b78c605843243a48b7b6a6` |
| `r4-parse-lazy9` | P_LAZY 0 -> 9: inspect p+1 after lengths 4..8 | `8cd52a2fe43e56e6d08895efa4cab6ccad5f78fa3e971646f9b15d6234909775` |
| `r4-parse-lazy9-one` | As lazy9; after accepting one next-position match, stop that lazy loop | `906cd139db1681927d8d6b6507e67558e19d684a182906cfc875b260f8a9cae7` |
| `r4-parse-lazy9-cost` | As lazy9; probe only when length < 6 or distance > 1024 | `6bf403fdaba3f4ab0eb49a673de8443cba32f55a801ab7cdf2678725c4e23e0c` |

**INFERRED mechanism:** fast3 already preloads the next position's candidate before deciding the current match. Spending that available candidate only at short matches may recover some compression without the window-table traffic and deeper chains that hurt previous variants. All four retain the existing gain comparison. The distance cutoff is a declared proxy for marginal matches, not a claim about actual dynamic Huffman cost.

The two restricted policies recognize the prose-specific lazy threshold 9. The existing structured-text threshold is 258 and other enabled read-ahead classes use 0; their conditions retain their original behavior. Tiny-text `run1t` uses `TM_LAZY`, not `P_LAZY`. No corpus names, exact input lengths, hashes, or benchmark-specific routes are added.

**Proof change:** none in this initial batch. The exact fast3 proof is copied, which is not a proof result for these new parsers. The `lazy1_loop_inv` state and measure do not add fields; acceptance still advances p and rejection sets go to zero. This supports a hypothesis of inexpensive proof adaptation, but extraction and Lean checking are still required.

**UNKNOWN:** Rust compilation, official re-extraction, new Lean obligation, axiom whitelist, public round trip and performance, private stage2, online admission, ranking and payment. The primary comparison must use paired fast3 and public432 on the same runner and same block order; the earlier #427 multiplier is only a secondary calibration hypothesis.

Stop or narrow this family if the gain is smaller than timing noise or all variants move behind fast3 after same-family calibration. No CI dispatch, commits, pushes, submission or wallet actions are performed by this worker.

## Next falsifiable mechanism, pending first-batch data

**VERIFIED (source observation):** the pinned public encoder `validator/measure/src/deflate.rs` uses `BLOCK_TOKENS = 16384`, builds dynamic length/distance alphabets from token frequencies, and includes the full encoder execution in the measured time. `run1` currently takes every valid length >= 3 reported by `probe_m`, irrespective of the existing `gain` estimate.

**INFERRED:** prose length-4 matches with distance > 2048 are negative in the parser's existing cost proxy: four literals are valued at 20 bits, while its match base is 10.5 bits and the distance has at least 10 extra bits. Refusing that narrow class needs no additional probe or table traffic and may save both distance-symbol cost and a bad greedy choice. It may also increase literal tokens and slow the encoder or miss useful backward folding. This is therefore a candidate for a later small batch, not a demonstrated optimization. Actual dynamic Huffman costs depend on each token block, so the proxy alone cannot establish an output-size gain.
