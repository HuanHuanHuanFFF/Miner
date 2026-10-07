# Round 5 independent algorithm candidates

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
