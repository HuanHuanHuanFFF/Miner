# Round 4 tiny-file symbol profile: fast3 vs. length6 and block512

## Provenance check before analysis

The diagnostic artifact is run **37523141792**, phase `screen`, commit `33c57dd15692ecd200e74cf75ed34b5c96c445e8`, official revision `a356bbff18b60c4527fbcc85d5a28ef9c20214e0`. `token-profile.json` reports `DIAGNOSTIC_OK`, 84 file records and no failures; `token-profile.jsonl` contains 1 provenance + 84 file + 924 block records (1,009 total). Its recorded `records_sha256` equals the file SHA-256 `eca0cc41b1ec2c09ecf5fde8d6f2de10db9b655640552e0f4c3559e9b90034f5`.

Before using the frequencies, I matched every profile file row to the official raw measurement JSONL for fast3, `r4-parse-symbol-len6`, and `r4-parse-symbol-block512`. All 84/84 token hashes, input hashes, token counts, parser source hashes, deterministic/decode statuses match. The 924 block rows reconcile with their file totals for token/block counts, literal/match bytes, match-token counts, and length/distance extra bits. The per-block full-frequency vectors also pass checks for literal/length/distance counts, active-symbol counts, one EOB per block, zero reserved symbols, and match-distance counts: 0 failures. Candidate parse/proof hashes in the profile match the local files. The pinned upstream Git blobs for `deflate.rs`, `token.rs`, and `record.rs` match the hashes in the profile; the checked-out copies have Windows CRLF conversion, so the Git blob hashes are the comparison.

The raw benchmark records use the same x86_64 AMD EPYC 7763 host identity, nightly toolchain, CPU affinity, benchmark engine and 11 measured repetitions per file. `time_s` is parser/LZ77 time, `encode_s` is the official encoder, and `total_s` is their per-repetition sum. Times below are medians of the 11 measured repetitions, in microseconds. Total medians are taken from `total_s` directly, not added from the two component medians.

## Files whose official compressed output changed

Only `tiny-app.log` and `tiny-config.json.txt` changed output and token hashes for either candidate; the other 26 files match fast3 in both hashes. Each tiny file remains one 16,384-token encoder block. In the symbol column, `L` is the RFC literal/length symbol index (257–285), `D` is the distance symbol index (0–29); `+` lists newly active symbols and no active symbols were removed. Literal active-symbol sets are unchanged. Extra-bit totals below count only the raw length/distance extra bits, not Huffman code bits, dynamic headers, or block-type cost.

| Variant / file | Output bytes; tokens; blocks | Literal bytes; match bytes; match tokens | Active literal / length / distance symbols | Extra bits Δ (length / distance / total) | Median µs fast3 → variant (parser / encoder / total) |
|---|---|---|---|---|---|
| len6 / tiny-app.log | 1,262→1,157 (−105); 1,043→855 (−188); 1→1 | 672→470; 27,328→27,530; 371→385 | 50/4/13→50/5/15; +L260, +D10,D28 | −24 / +96 / +72 | 33.703→34.354 (+0.651, +1.9%) / 170.742→175.691 (+4.949, +2.9%) / 203.814→209.766 (+5.952, +2.9%) |
| len6 / tiny-config.json.txt | 2,670→2,480 (−190); 3,393→2,887 (−506); 1→1 | 3,318→2,712; 8,682→9,288; 75→175 | 78/4/8→78/5/20; +L260, +D5,7,9,11,13–19,21 | +2 / +637 / +639 | 18.725→18.615 (−0.110, −0.6%) / 247.547→287.122 (+39.575, +16.0%) / 265.530→307.932 (+42.402, +16.0%) |
| block512 / tiny-app.log | 1,262→1,111 (−151); 1,043→827 (−216); 1→1 | 672→519; 27,328→27,481; 371→308 | 50/4/13→50/17/14; +L259,261,262,270,273,276–281,283,284; +D28 | −115 / −454 / −569 | 33.703→27.601 (−6.102, −18.1%) / 170.742→192.633 (+21.891, +12.8%) / 203.814→220.456 (+16.642, +8.2%) |
| block512 / tiny-config.json.txt | 2,670→2,268 (−402); 3,393→2,539 (−854); 1→1 | 3,318→2,381; 8,682→9,619; 75→158 | 78/4/8→78/27/21; +L258–268,270–274,276–277,279–281,283–284; +D5,7,9,11,13–19,21,23 | +12 / +423 / +435 | 18.725→17.082 (−1.643, −8.8%) / 247.547→316.746 (+69.199, +28.0%) / 265.530→334.610 (+69.080, +26.0%) |

## Interpretation and one falsifiable next hypothesis

The symbol expansion is real in the checked full-frequency blocks, but active-symbol count alone does not predict either size or runtime. `len6` adds only L260 on each file, yet tiny-config adds twelve distance symbols and its encoder median rises 16%. `block512` adds 23 length and 13 distance symbols on tiny-config; it saves 402 output bytes while its parser median falls 8.8% and encoder median rises 28%. Extra bits rise by 435 there, but output still shrinks because Huffman-coded symbols and block representation also affect size. These are measured outcomes, not a claim that symbol count caused the encoder slowdown.

A falsifiable next hypothesis is that the 512-token restricted-palette phase is too short for `tiny-config`: raising it to 1,024 will cut the newly active code set and reduce the encoder median penalty while preserving at least half of the current 402-byte saving. Test only if authorized; support it only if output remains at or below 2,469 bytes and the encoder median is at most 14% above fast3 on the same file. Otherwise reject the threshold hypothesis. No new candidate was generated for this review.

The profile is diagnostic evidence for public stage1 tokens and the official encoder runs in these raw records. It does not establish a fresh Lean proof, full gate acceptance, stage2 behavior, admission, frontier position, or reward.
