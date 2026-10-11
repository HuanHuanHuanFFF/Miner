# Tiny-config alternatives: source map and existing timing evidence

**The archived byte comparison is verified.** It records `tiny-config.json.txt` (12,000 raw bytes) as 2,155 bytes with public #584, 2,487 bytes with public #595 and `combo`, and 2,077 bytes with public #609. #595 and `combo` have identical token and output hashes on this file. Public #609 is the 2,077-byte row; that result does not belong to #595. Existing standard receipts measure #595 main/shadow and `combo` on the same runner; no standard JSONL contains public #584's source hash, so #584's same-run tiny-config time is **UNKNOWN**.

The R25 native original-encoder receipt for `r25-astra-tiny-tail` records 2,479 output bytes and 3,072 tokens, versus `combo` at 2,487 bytes and 3,094 tokens. This saves 8 bytes and 22 tokens on `tiny-config.json.txt`; the other 27 public files are unchanged. The equal-file aggregate change is only 0.00238095 percentage points. The receipt establishes bytes, not performance.

| Source | 12 KB dispatch | Engine and match path |
|---|---|---|
| Public #584 | `bulk_parse`: length 12,000 calls `p135_row3`; that row calls `pc_run1::<32769>(…, 6, 16, 1_000_000, 0xffffffff)`. | PC run-one uses four-byte keys and lazy lookahead. Its `pc_INS_MAX` is 8; `pc_put_match_h::<H>` selects `pc_put_match_checked` for odd `H=32769`. The `pc_slot_of_m` index formula for this `H` yields the same slot values as the 15-bit formula in the #595 PC family, but insertion and emission behavior differ. |
| Public #595 and `combo` | `route`: length 12,000 returns class 23; `bulk_parse` class 23 calls `p125_row12`, which calls `et_tiny(input, out, 302256384)`. | The actual 12 KB route is ETINY: a 4,096-slot one-way table keyed from four bytes, roughly eight-byte lookup stride, then allowed-length-piece emission. In the separate PC family, `pc_INS_MAX` is 2 and `pc_run1` directly calls the base `pc_put_match`; that family is not the selected 12 KB route. |
| R25 `tiny-tail` | Same route and `et_tiny` entry as `combo`. | Adds `et_piece_tail` to the coverage and emission selectors. When the greedy allowed piece would leave a remainder shorter than the minimum allowed length, it tries two allowed pieces and accepts them if they cover more bytes and their estimated match gain is higher. The search, route, and table stay the same. |

So the 8-byte repair is a match-segmentation component inside ETINY, not a route-constant change. Public #584's 332-byte advantage over `combo` comes from a different PC configuration, including its insertion bound and checked match emission; a route-only row substitution would not reproduce it. Its runtime and port/proof cost remain unknown. The archived source receipts retain #584 and #595 authorship and file hashes in `references/round18-public-584/` and `references/round21-public-595/`.

The R24 “tiny” negative concerns another mechanism. `r24-609-tiny-converge` tried to stop the `SFtinytokens` reassignment loop after a rejected trial while keeping improving trials. Its dispatch calls that path at 28,000 bytes; `tiny-config.json.txt` is 12,000 bytes. The R24 instrumented count receipt shows the target file made 0 rounds, while `tiny-app.log` made 2 rounds with 1 improvement and 0 rejected trials followed by a remaining round. R24 therefore found no early-stop work to remove on the public corpus. This does not test ETINY’s restricted-length tail splitting. The older R18 exact-price DP repeat check is another separate path.

For existing standard timing, I inspected `evidence/round25/38124524718/screen-a/gate/round1-*.jsonl` and `round2-*.jsonl`. Both rounds use AMD EPYC 9V45, the same host hash, engine hash, and template hash; each contains 11 measured repetitions for the same 12 KB input. The medians below pool the 22 measured repetitions, with `time_s` reported as parse time and `total_s` taken directly from the standard receipt.

| Same-run method | Source SHA-256 | Output bytes | Parse median | Encode median | Total median (range) |
|---|---|---:|---:|---:|---:|
| #595 main | `5295c241…75f4754` | 2,487 | 6.840 µs | 138.681 µs | 145.587 µs (141.440–154.759) |
| #595 shadow | `5295c241…75f4754` | 2,487 | 6.725 µs | 138.842 µs | 145.717 µs (142.862–164.514) |
| `combo` | `57a8fb4f…d037275` | 2,487 | 6.785 µs | 139.137 µs | 146.253 µs (141.611–164.815) |

The `rg --files evidence | rg -i 'public584.*jsonl'` search returned no named receipts, and searching `evidence/round*/**/*.jsonl` for public #584's exact source hash (`82297fe…10cf2`) found no match. The table therefore provides direct #595/`combo` same-run cost context only; it cannot estimate #584 or establish a cross-source speed ranking. No new timing run or implementation was done.

Evidence and hashes are collated in [tiny-alternatives.json](tiny-alternatives.json). The R25 selector model is finite-model evidence only; the candidate’s saved Lean hash matches `combo`, but this exact Rust/Lean pair has no new full-gate result.
