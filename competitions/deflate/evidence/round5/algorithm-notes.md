# Round 5 independent algorithm candidates

**Final disposition: STOPPED for insufficient measured benefit.** The same-endpoint correction removed the observed boundary/size regressions on the public corpus, but saved only 6 bytes and remained outside snapshot 25803 under the matched299 calibration. No full proof/gate or further candidate is pursued. See the final run closure below.

Prepared 2026-10-07 06:16 UTC. Scope: two new research candidates; no local Rust/Lean installation, CI dispatch, Git commit/push, formal submission or wallet action by this worker. Parent sources and the official encoder remain unchanged.

## Source findings

**VERIFIED (current local source):** public299 `a_engine` at `references/round4-public-299/parse.rs:967` repeatedly overwrites `ch` during sampled/full passes and advances from the last full pass's `p1`/`t`. It does not retain the cheapest earlier plan. Its full-pass endpoint changes with the estimated bytes per token, so comparing each pass's unnormalized total bit count would favor shorter coverage rather than establish better compression.

H already retains its preferred plan, so adding a second best-plan cache to H is not the proposed change. The previous RMQ, livehuff/EOB and depth/iteration directions are not repeated.

## Candidates

1. `r5-opt-small-select`: retain the frozen h3r-smallc299 routing at input sizes >=65536. For smaller inputs, run original public299 and H mode3, then select the token stream with the smaller complete encoded-byte cost model. Equal costs retain public299. The cutoff bounds additional work and comes from the parent hybrid; it does not identify a file. No filename, content hash or exact-length equality is inspected. The two existing emitters remain unchanged; the selected alternate's token prefix is copied using the existing H safe-copy helper. Extra parsing, scoring and copying may outweigh size benefits.

2. `r5-opt-a-best299`: use original public299 routing and budgets for the whole input, changing only A's plan retention. Each full DP pass combines its counts with the existing partial encoder-block prefix, scores a single encoder block, and compares bits per decoded byte by cross multiplication. Sampled passes never compete. The best prefix, endpoint and token count are saved, restored after the loop, and walked again to rebuild both frequency carry and the model used for the next round. `r5_block_start` follows encoder token-block boundaries. The original checked emitter still verifies every suggested match. B/C, classification, settings, search and transition costs remain unchanged.

**INFERRED:** the ratio objective is preferable to comparing raw bits when endpoints differ, but it does not guarantee minimum complete-file size. A pass ending earlier can alter future block boundaries and matches. It may regress; paired encoded size is the decision, not the internal score. Saving an n-element plan costs roughly 4*n bytes in addition to the existing A allocations, and each saved prefix adds a copy. This resource/time cost must be measured.

Both candidates derive from `r4-hybrid-h3r-smallc299` as a convenient exact union of public299 and the H proof/helper core. The A candidate's exported entry uses only S parsing plus the cost helpers; the H parser declarations are retained as unused reference/proof material. They are not an added second parse on the A route.

## Cost model

New `r5_block_bits` copies H's block evaluator, with all three tree calls forced to its package-merge implementation, avoiding H's faster ordinary-Huffman shortcut and potential equal-weight tree-shape differences. The evaluator includes dynamic header/RLE, extra bits, and fixed/dynamic/stored choice. New `r5_token_bytes` follows the official 16384-token boundaries and adds stored-block alignment and final byte padding. A's histogram scorer explicitly removes accumulated EOB pseudo-counts before the evaluator adds one EOB; this affects only the new selection objective, not A's unchanged DP model.

**VERIFIED (source audit):** fixed-size leaf/package bounds, stable symbol-order frequency sorting, leaf-before-package equal-weight ordering and the H RLE policy correspond to the inspected official encoder's algorithm. This is not yet a Rust runtime equality result or all-input equivalence proof.

**VERIFIED (fresh local Python model check):** `python scripts/make-round5-opt.py --model-check` compares a flags/backtracking package-merge model with an independent explicit-package-symbol-list model modeled on the official encoder. 192 distributions cover 19/30/288 symbols, zero/single/full alphabets, equal weights, skew and values above 65535; zero mismatches. An independent imperative/closed-form RLE comparison covers all run lengths 1..320 and all code lengths 0..15: 5120 cases, zero mismatches. These tests execute Python models only.

The generator can print an actual Rust differential driver:

```sh
python scripts/make-round5-opt.py --diagnostic-source "$DEFLATE_ROOT" > "$RUNNER_TEMP/r5-cost-check.rs"
rustc +nightly-2026-08-18 --edition=2021 -O -C overflow-checks=yes "$RUNNER_TEMP/r5-cost-check.rs" -o "$RUNNER_TEMP/r5-cost-check"
"$RUNNER_TEMP/r5-cost-check"
```

The driver imports the unmodified official token/encoder sources and new candidate cost scorer. It compares byte counts on 383 fixed token streams, including empty input, block boundaries, stored padding, every legal match length, and distance-code boundaries. This driver has been generated but **not compiled or run locally**. It does not prove the candidate parser decodes correctly; ordinary public and generated-input round trips remain necessary.

## Reproduction and hashes

`python scripts/make-round5-opt.py --check` freshly reproduced both source/proof/manifest sets byte-for-byte. Parent hashes are locked. Every parent function except `parse` (both candidates) and `a_engine` (best299 only), every constant and every custom type is asserted byte-identical. No parent directory or official source is written.

| Candidate | Rust SHA256 | Rust bytes |
| --- | --- | ---: |
| small-select | `a3bb941f057036a94313f640f485258a80d335f69641d43e5d2eb6c74a6c7935` | 180750 |
| a-best299 | `1b53310c78882d2439acc7bc972e6a5f451eb717a8deaa0ca26622b46ef73188` | 181590 |

Both `Parse.lean` files are 375647 bytes, SHA256 `a1b00aed62e68c8e57d65b91aa23facdd8dd430f2afc4837cfa0c6407cede184`. They contain an explicit research-only comment followed by the frozen parent proof. All files fit 524288 bytes.

Attribution remains public submissions #299 and #402; original metadata/ownership is retained under `references/round4-public-299/PROVENANCE.json` and `references/round4-public-402/PROVENANCE.json`.

## Proof boundary and next gate

**NOT_ADAPTED:** these files are reference proof material, not proof of the new parser. Do not select them as ready-for-gate or formally submit them. No axiom, sorry, weakened obligation or time-limit change was added.

Request actual Charon/Aeneas `Types.lean`, `Constants.lean` and `Funs.lean` before changing any loop statements. An explicitly diagnostic extraction/expected-failing proof run is distinct from selecting a supposedly ready candidate gate.

For small-select, the new token-cost loop needs a totality/bounds spec, and the selected copy needs a token-prefix preservation lemma composing the two existing complete parser specs. `h_copy32` only has the existing weak safety interface; its Rust body being copied is not a proof of LZ77.Valid preservation. For a-best299, the added saved vector and ratio variables change the extracted nested `a_engine` loop tuple/signature. Preserve the original `n<67108864`, vector lengths, cost array, p0/p1/t and progress invariants; add block-start and chosen-prefix bounds. Only totality is needed for the scoring heuristic, while the unchanged checked emitter carries token correctness. Do not fabricate tuple layouts from Rust variable order.

## First decision and stop conditions

- Compare small-select against the frozen h3r-smallc299, and best299 against original public299, using paired official public compression time/size and all round trips. Run the token-cost/official-encoder differential before interpreting selection cost as exact.
- Stop a candidate if its compressed output does not improve the size axis sufficiently for its measured extra time, if cost differential fails, if any decode/bounds check fails, or if proof migration cannot meet unchanged per-file/time limits. A ratio score improvement alone is insufficient.
- Avoid further cutoff, iteration or depth sweeps until these mechanisms return evidence.

**UNKNOWN:** actual Rust compilation, actual cost/encoder equality, generated-input and public decode, extraction shape, fresh Lean/axiom acceptance, runtime, public two-axis effects, private stage2, admission and payment. The only completed checks in this handoff are source/generator audits and Python arithmetic-model comparisons.

## Frozen-source follow-up: concrete proof and cost limits

After handoff the two Rust hashes above remain frozen; no third candidate was added.

**VERIFIED (additional source/proof audit):** `a_walk_spec` at the original proof's line 684 guarantees an endpoint up to `max(p0, lim + 511)`, not `p1 <= input.length`. Its current precondition requires `lim <= input.length`. Therefore feeding saved `r5_best_end` back as `lim` cannot be justified by simply reusing the old spec, even though actual valid DP plans are expected to stay inside the input. This is a real proof-interface gap, not an observed runtime counterexample.

A narrower migration avoids proving DP match semantics: prove an additional totality version of the unchanged `a_walk` using `ch.length <= input.length` for literal-read safety. The source loop already requires `i < ch.len()`. With `input.length < 2^26`, increments of at most 511 fit usize, and the previous token-count/progress inequalities still suffice. Allow `lim` through `input.length + 511`; retain `need <= 2^31` and counter bounds. Fresh extraction is needed to track the Vec/slice reborrow and retain the plan length through safe copies.

The combined proof currently proves the S/A engine before the H namespace. New A calls into H-based scoring cannot reference later declarations. The two engines' proof scopes are independent: the likely clean migration is to place the complete existing H proof scope before S, then add R5 scorer/length-preservation lemmas, then adapt S's A-loop proofs. Preserve closed/reopened scopes so H and S's numerous local step rules do not leak into each other. This is a plan, not an attempted or accepted reordering.

For small-select, the shortest semantic addition is a zero-offset specialization of `h_copy32`: under `m <= src.length` and `m <= dst.length`, preserve dst length and establish `LZ77.toks dst_result m = LZ77.toks src m`. An invariant equating the copied token prefix after `i` steps can use the official `LZ77.toks_update`/`take_set_succ` lemmas (`validator/lean/Lz77/Interface.lean`). Existing `EH.get_spec`, `EH.set_spec` and `EH.copy32_spec` all have only `True` postconditions; unfold the actual safe get/set functions or prove stronger local versions. Do not claim parser validity solely from their existing totality theorems.

**Cost limitation clarified:** a full DP pass can still yield fewer than the remaining 16384 tokens when `a_walk` reaches its byte limit. Thus `r5_hist_bits` sometimes scores a hypothetical finalized partial encoder block, including a header that the actual continuing block will not yet emit. The bits-per-byte objective both normalizes varying endpoints and remains a heuristic about future block completion. Only `r5_token_bytes` has a complete token stream and explicitly tracks stored alignment/final padding. A's score deliberately omits position-dependent stored alignment and final-file padding; it is not advertised as exact final output bytes.

The cost driver tests the complete-token scorer against the unmodified official encoder, while public paired measurements decide whether the A heuristic is useful. A passing cost driver does not validate A's ratio objective or prove either parser's contract.

## Actual extraction and cost differential received

**VERIFIED (CI run 37582348267, git b94837db0ccb2ae5a8a4c3d36cd9a718b8fb50aa):** `evidence/round5/37582348267/new-mechanisms-a/extraction/research.json` records both exact Rust hashes accepted by official extract-only, exit 0. This is extraction acceptance, not a completed Lean obligation. small-select Funs is 734247 bytes, SHA256 `a14d5f5d32e7f031aba3d37d6398fbc475adb226a9248d90f8d55af81b2a56e4`; best299 Funs is 743987 bytes, SHA256 `6c3ab0d2d921045f91db24a1194bd8b4a83bc5421fc63a5c513a429c03af43fc`. The receipt retains each Types/Constants hash and original extraction logs.

**VERIFIED:** the actual Rust cost driver compiled with exit 0 and ran with exit 0, printing `COST_DIFFERENTIAL_OK 383`. These 383 fixed token streams agreed with the unmodified official encoder's output byte lengths. This supersedes the earlier UNKNOWN status for that finite Rust differential only. It does not prove universal cost equivalence, either parser's decode contract, public performance, or A's ratio objective.

The independent `small-select-proof-draft.lean` now follows the actual signatures. The scorer adds one loop with state `(fr, lens, bits, i, used)` and returns `(fr, lens, bits)`; block scoring returns `(score, frequency slice, lens slice)`. The final parser's mutable Vec borrow and copied slice are explicit. Existing get/set/copy forms agree with the anticipated interfaces. No extra hidden control state or A-engine migration is needed for small-select.

The minimum integration is three cost-totality lemmas (block, token loop, token wrapper), a semantic safe-get/set boundary and zero-offset copy loop/wrapper, plus the final parser composition. The scorer needs only totality; the copied-prefix loop is the sole new semantic invariant. New `r5_hist_bits` and its two loops are unreachable from small-select's entry and need no theorem for that obligation. Parent S/EH scopes can remain in their original order.

Remaining concrete issues are tactic acceptance for the strong copy loop, the Vec deref/backward reborrow representation equality, checked-counter bounds in the token scanner, and complete proof elaboration within the unchanged limit. The parent proof is 375553 bytes against a 524288-byte cap; this narrow addition has substantial file-size room, while runtime remains unmeasured. The draft's six pure interface lemmas and three observed-definition adapter lemmas remain NOT_COMPILED; no proof has been promoted into frozen candidates.

## Failed mechanisms: measured outcome and one bounded correction

**VERIFIED (run 37582348267, two public blocks):** small-select time axis 8.126776 versus h3r-smallc299 7.508665; both size axes are exactly 33.855551957%. All 28 files have equal counted-token SHA256, not merely equal compressed length. This mechanism and its proof work are stopped.

**VERIFIED:** a-best299 time axis 9.457209 versus public299 9.147551 (about +3.39%). Size is 33.853277993% versus 33.842831048%, a regression of 0.010446945 percentage points / 2139 output bytes. Replaying `round1-*` raw records reproduces the same deterministic size difference as the second block. Thirteen files are larger, one is smaller, fourteen have equal byte lengths. The changed token streams span sixteen files. The one byte saving is source.c (-9 bytes); this is insufficient to compensate the losses.

| File (evidence label only) | Extra compressed bytes | Axis regression pp | Token-count change |
| --- | ---: | ---: | ---: |
| docs.md.txt | 884 | 0.003946429 | +2351 |
| machine-code.bin | 289 | 0.002064286 | -455 |
| bundle.min.js.txt | 340 | 0.001214286 | -1462 |
| metrics.csv.txt | 296 | 0.000813187 | -1343 |
| records.json.txt | 85 | 0.000758929 | +41 |

The original public299 was not separately profiled in this batch. To avoid guessing its histogram, the review matched all 28 input hashes and counted-token hashes of `evidence/round4/37535056448/gate/token-profile.jsonl` candidate `r4-alt299-tinydepth32` against this batch's actual public299 raw records. All 28 match. Its historical block profile is therefore a token-identical comparator for these fixed files; its historical timing is not used.

**VERIFIED (endpoint evidence):** docs changes from 8 blocks to 9, from 129437 to 131788 tokens, with 3341 extra literal bytes and 990 fewer match tokens. Parent block ends are `[79715,186651,293396,393233,471217,571372,656228,800000]`; failed candidate ends are `[70436,158129,273344,378263,460414,559317,646667,794011,800000]`. Machine-code has the same first end 61398 but second end changes 125848 ->125996 and subsequent boundaries move. Bundle retains the first five ends but its sixth changes 512380 ->515457 and subsequent ends move. Fewer total tokens on machine-code/bundle does not imply fewer output bits: their distance extra bits increase 2784/7690, respectively.

**VERIFIED (independent cost replay):** a Python implementation of the official explicit-package-symbol-list package-merge, code-length RLE, fixed/dynamic/stored decision and byte alignment was applied to the actual token-profile block histograms for both new candidates. It reproduced every official byte length: 56 file records / 558 blocks, zero discrepancies. Combined with the earlier actual 383-case Rust differential, this provides no evidence that an encoder-cost arithmetic error caused these file regressions.

**INFERRED mechanism:** the old ratio compared paths ending at different bytes and then fed the selected earlier counts/endpoint into later rounds. The profile directly verifies resulting boundary drift; it cannot distinguish exactly how much damage comes from immediate ratio ranking versus subsequent model feedback because no per-pass trace was recorded. Both are parts of an invalid interchangeable-plan assumption. The correction below makes the substitution genuinely interchangeable at the next round boundary rather than trying another ratio, budget or cutoff.

### Sole follow-up: `r5-opt-a-sameend299`

New Rust SHA256 `2ce6bee2d1c94896bfa4f1f87bd2ae22ebfab53c15df5d705ce82b0ba223e0d3`, 182094 bytes. Proof stays **NOT_ADAPTED**, SHA256 `a1b00aed62e68c8e57d65b91aa23facdd8dd430f2afc4837cfa0c6407cede184`, 375647 bytes. The same generator has one explicit new recipe; fresh `--check` reproduces all three candidates and leaves the two failed candidates' source/proof/manifests exact.

The new recipe starts from the original unmodified A engine, not from a progressively mutated failing parser. It replaces only completed, same-endpoint output segments:

- A pass is eligible only when `t == need` or `p1 == n`, where the original `need = BLOCK_TOKENS - used` includes the existing token carry. Intermediate partial blocks do not participate.
- Costs include original prefix counts `bl/bd`, plus this pass's `lf/df`, with one EOB. Earlier candidates are discarded when the byte endpoint changes.
- The block must contain at least one match. Both current and saved candidates therefore use dynamic/fixed encoding, whose bit length does not depend on incoming alignment; no hidden stored-block padding is compared.
- A saved plan replaces the final plan only at the same byte endpoint and with strictly fewer bits. Non-EOF replacement explicitly also requires equal token count. At EOF differing token counts are permitted because both alternatives finish the same last block and input.
- The original final-pass `p1`, `t`, frequencies, next cost model, `used`, and `bpt` are never replaced. There is no chosen-plan rewalk. The next search follows the original299 trajectory; only an already completed output segment changes. The original classifier, budgets, match search and DP transitions remain untouched.

**INFERRED checkable consequence:** encoder block raw-end arrays and block count should remain identical to public299 on every test input. With validated plans and correct histogram costing, completed match-bearing substitutions reduce packed bits, while any unchanged later stored block aligns monotonically with incoming bit count. This is a source argument, not an all-input equivalence/size theorem or a measured result. It deliberately misses cheaper plans whose endpoints do not equal the final pass; that restriction is the cost of avoiding the demonstrated failure mode.

The strongest first validation is same-run public299 + oldbest + sameend: compare every full `raw_end` array and block count, per-file compressed bytes, decode, and paired time. Profiling public299 directly in the new batch is preferable; the token-identical historical proxy was needed only for this diagnosis. Any moved full-block boundary, more encoded bytes, cost disagreement or decode failure falsifies the correction's intended isolation and stops it. If outputs remain equal or savings do not justify measured overhead, stop the mechanism; do not follow with another same-family budget/ratio sweep. New native build, extraction, performance and proof remain **UNKNOWN** at generation.

## Read-only selection audit script

`scripts/analyze-round5-selection.py` reads a supplied gate receipt directory and prints JSON to stdout. It does not write files, invoke dependencies, contact the network or launch CI. Default candidate is sameend; baseline is the historical tinydepth32 profile at `37535056448/gate`, rebound on every invocation to the supplied run's actual public299 input/token/output hashes and counts. Both historical public299 and historical tinydepth32 native outputs must equal current public299 before their block profile is accepted.

The script recomputes parser-source SHA256 from local frozen files and profile-JSONL SHA256 from saved bytes, binds profile source/proof metadata to run specs/native source metadata, checks all 28 stage1 files and histogram/contiguity/full-block/decode fields, and cross-checks native input/token/output hashes across every available round. A different engine/token/encoder version rejects the comparison. It reports both full raw-end arrays, block counts, block token counts, byte/token changes, public time and absolute public size axes. It also records all consumed receipt hashes.

Content-hash limit is explicit: the saved histograms contain no original token or compressed byte streams. Their token/output content hashes can be cross-checked against independent native receipts but cannot be recomputed from a histogram. The script does not claim otherwise.

Usage for the pending run:

```sh
python scripts/analyze-round5-selection.py evidence/round5/37585987361/sameend-mechanism/gate
```

Use the actual downloaded batch-directory label if it differs. Exit 1 means missing/inconsistent evidence. Exit 2 means a mechanism stop (boundary/block-count moved, any file grew, or no public size-axis gain). Exit 0 means only that these stop conditions were absent and fresh time/size/frontier review is appropriate; it is not formal gate/admission acceptance. No historical size threshold is hardcoded: a time coordinate near 9.5 must use its own freshly scored frontier, not the earlier 6.5 region's threshold.

**VERIFIED (fresh negative replay):** running with `evidence/round5/37582348267/new-mechanisms-a/gate --candidate r5-opt-a-best299` returns exit 2 / STOP. It rebinds 28 baseline files, catches 14 files with changed endpoints, 13 files with larger encoded size, docs 8->9 blocks and +884 bytes, total +2139 bytes / +0.010446945316588173 percentage points, and time-axis +3.3851470326612842%.

**VERIFIED (control replay):** running the same checker on historical `37535056448/gate --candidate r4-alt299-tinydepth32` produces no boundary/size false positives, zero changed bytes, and correctly returns STOP solely for no size gain. Both runs read the existing evidence unchanged. New sameend results remain pending; this script does not manufacture them.


## Final run closure — stop the same-endpoint route

**Decision: STOPPED.** `r5-opt-a-sameend299` fixes the observed boundary/size regression mechanism of oldbest on the tested public inputs, but its compression gain is too small for useful frontier progress. Do not adapt a full proof or continue this family with additional budget/ratio variants. Frozen candidates, scripts and manifests remain unchanged at this closure.

**VERIFIED (run 37585987361, commit 9791449538e20bd1eb6e71bcfdb952b64a20a35d):** a fresh read-only audit of `evidence/round5/37585987361/sameend-mechanism/gate` returns exit 0 for the structural checks. All 28 files retain public299's complete encoder-block raw-end arrays and block counts; no file grows. Only config.yaml saves 4 bytes, metrics.csv 1 byte and multibyte 1 byte, for 6 bytes total. That exit code means the intended substitution constraints held in this finite test, not that the candidate has adequate performance or passed a formal gate.

| Same runner, two public blocks | Time axis | Size axis |
| --- | ---: | ---: |
| Original public299 | 9.482091132402893 | 33.84283104811855% |
| sameend299 | 9.50581725635131 | 33.84278933982684% |
| Change | +0.2502203745684328% time | -0.00004170829170829171 percentage points |

The earlier -9-byte isolated oldbest file was not treated as sufficient evidence of competitive benefit. This final correction's aggregate -6 bytes is the complete observed public saving.

**INFERRED, matched299 calibration:** `analysis-snapshot-25803.json` maps sameend to `(9.199596907093085, 34.102331191383946%)`. At snapshot 25803, computed 2026-10-07 15:09:58.649118 +08:00 with API freshness reported unknown, #305 and #316 dominate it. The size gap is 0.0013545707823254816 percentage points and conditional geometric weight is zero. This is a public-to-formal calibration estimate at the observed time coordinate, not a new formal score or reward observation. A different-family #427 projection is not used to override this result.

**VERIFIED validation scope:** the unchanged Rust source `2ce6bee2d1c94896bfa4f1f87bd2ae22ebfab53c15df5d705ce82b0ba223e0d3` compiled and passed official extract-only. Actual Funs SHA256 is `7d96af125eeb489ee2a94e7d844aac253e6dcae400ee9a772bf5cba1fc5df4e6`. Public native records and independent token profiles passed finite decode checks. Eight fixed synthetic inputs completed both measurement blocks; the raw CI records contain all 16 sameend file results, deterministic=true and no errors, with matching input/token/output hashes across the two blocks. This is finite public/synthetic validation only.

**NO_FULL_GATE:** `state.json` has an empty `gates` map; extract-only `proof_status` is `NOT_RUN`. The copied proof remains NOT_ADAPTED. No fresh Lean obligation, axiom whitelist, private stage2, formal admission, on-chain action or reward is claimed for this candidate. The useful result retained from this route is the diagnosed failure and verified finite correction, not a competition-ready improvement.
