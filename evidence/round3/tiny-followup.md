# Tiny planner followup hypotheses

Prepared 2026-10-06 UTC. Two single-factor experiments were generated at the main thread's request after this source analysis. No performance result is claimed for them.

## Cost evidence and actual route

**VERIFIED:** `probe3-cost-attribution.json` describes historical public CI 37451613962 block 1. The parser fractions are about 4.91% for sparse.bin, 12.15% for tiny-app.log, and 10.67% for tiny-config.json.txt. Their equal-file total-time-ratio contributions sum to 0.0754625766; the supplied parser diagnostic contributions sum to 0.0067532574. The 0.0687093192 remainder is a diagnostic estimate, not a separately scored encoder axis or an exact additive decomposition of medians. This supports looking for encoder savings rather than assuming that a cheaper parser alone can remove most of their cost.

**VERIFIED from the unchanged official encoder:** `validator/measure/src/deflate.rs` uses 16384 tokens per block. `write_block` runs package-merge for literal/length and distance alphabets, then a third code-length alphabet, before choosing dynamic, fixed, or stored representation. `package_merge` collects only symbols with positive frequency. Reducing active symbols can reduce table construction and dynamic-header cost, including work paid even when the final representation is fixed/stored. Fewer symbols do not automatically mean fewer output bytes: token count, distance/length extras, and newly exposed literal symbols can offset the saving.

**VERIFIED from probe3:** `tf_route` runs the planner only if `input.len() <= 65536` and either `tf_class=2` or (`TF_TEXT=1` and `tf_class < TF_TKIND`). Currently `TF_TKIND=1`, so kinds 0 and 2 enter, but kind 1 does not.

The sampled classifier uses stride `(n / 256) | 1`, with at most 65536 iterations. Kind 2 means a sampled zero byte or control count greater than `tot/32`; a control byte is below 9 or between 14 and 31. Otherwise kind 1 means sampled digit count at least `tot/6`; kind 0 is the remaining text. These are general input statistics, not filenames or exact lengths.

**VERIFIED historical trace:** `evidence/round2/37447673754/research.json` has 1023 regular-walk first visits for the 28000-byte tiny-app.log, and zero for sparse.bin and tiny-config.json.txt. Its `class` field comes from regular `sniff`, not `tf_class`; the two classifiers' numeric labels must not be conflated. **INFERRED:** given the unchanged TF route, the small structured log was the excluded `tf_class=1` branch. The regular class and positive-depth engines of the other two would execute the instrumented walk if selected; their zero visits therefore support the tiny path being active. Exact sampled `tf_class` values were not recorded, so that inference is not a fresh route trace.

This has an experimental consequence: the current `r3-tiny4` and `r3-tiny8` modifications to `TF_SDEPTH`/`TF_SLAZY` are inactive while `TF_TKIND=1`. Their text-depth changes can still affect the ordinary-text tiny path.

## Hypothesis 1 Extend thinning to small structured text

Single change: `TF_TKIND: 1 -> 2` in `round3-tiny-kind2`.

This sends every small kind-1 input through the already implemented structured planner: `TF_SDEPTH=1`, `TF_SLAZY=258`, `TF_SSKIP=3`, four-byte keys, minimum match 4, and text keep thresholds `TF_KL=TF_KD=5`. It activates an existing algorithm branch rather than adding a new selector.

**INFERRED mechanism:** recurring structured records can use many rare length/distance codes under the regular engine. The tiny planner counts codes, removes initially rare ones, merges same-distance spans, and rewrites matches using the kept codes. A smaller live alphabet can lower encoder cost while a shorter dynamic header offsets additional payload bits. This is a plausible simultaneous improvement, not a guaranteed one.

First falsification: verify the candidate's selected kind/route in a diagnostic run, then compare total time and compressed bytes for all changed files. Keep symbol counts per actual 16384-token block, token count, literal bytes, length-code count, distance-code count, and re-admitted codes if diagnostics are added. Unchanged files must retain their token/output hashes. If alphabet size does not shrink, any time change should not be attributed to alphabet thinning. If both bytes and total time worsen, reject this route change. Do not immediately combine it with deeper TF_SDEPTH before observing the single-factor result.

## Hypothesis 2 Prefer the previous distance before new chain distances

Single change: `TF_REP: 0 -> 1` in `round3-tiny-rep1`.

The route stays unchanged. `tf_find` tries distance 1, then the previous match distance, then its original hash chain. `tf_cand_rep` acts only when `rep > 1`, `rep <= p`, `rep <= 32768`, and the existing best length is below the cap. It accepts only a strictly longer match. Consequently, an equally long later chain candidate does not displace the repeated distance. A repeated-distance match at least `TF_NICE=64` can also avoid the chain walk entirely.

**INFERRED mechanism:** keeping the same distance across adjacent matches can concentrate the distance histogram and create longer same-distance spans for `tf_extend`, reducing both active distance codes and split tokens. It may also save distance extra bits, but the previous distance is not guaranteed to be numerically shorter. The result can improve compression and encoder work with one extra candidate comparison, without changing keep thresholds.

Current active scope is non-RLE tiny text. The binary planner has `TF_BDEPTH=0` and selects only distance 1, so the `rep > 1` guard prevents a new binary match search. Structured small text only becomes part of this hypothesis if a later, separately justified combination also enables kind 1; this candidate does not do so.

First falsification: compare the unchanged-route candidate against probe3. If token hashes are identical, there is no observed compression mechanism to credit. If repeated-distance selections increase, check that this reduces distinct distance codes or same-distance span splits at emission, rather than only changing intermediate search choices. Measure total parser+encoder time; an extra comparison can erase an encoder benefit. Keep this separate from `tinykeep`, which changes the allowed alphabet rather than the initial selection preference.

## Parameter and proof boundaries

**VERIFIED from the proof:** `tf_route_spec`, `tf_cfg_spec`, `tf_cand_rep_spec`, `tf_find_spec`, and `tf_plan_spec` prove totality without a decode claim for the planner; `emit_spec` rechecks planned matches and carries the decode invariant for any plan. Both modified constants are used only in comparisons: `TF_TKIND` in `kind < TF_TKIND`, and `TF_REP` in equality tests for modes 1/2. Neither theorem has an extra upper-bound premise on these constants. Both values are existing, in-range modes in the Rust implementation. Source/control-flow shapes, tables, and trusted emission are unchanged.

Keep the unrelated arithmetic requirements unchanged: `TF_SAMPLE` and `TF_SDIG` must be positive for division; `TF_HN` and `TF_WN` must be positive for indexing modulo; `1 <= TF_HB <= 64` keeps the hash shift defined. `TF_N <= 65536` is retained so u16 stored positions are exact; it is a representation/quality condition from the source, not a newly asserted universal formal theorem. Tiny skip shifts are handled by `tf_shr`, which returns zero at shifts >=32; do not transplant the regular engine's shift-bound requirement into this helper without checking its different implementation.

**INFERRED:** the unchanged complete proof has a low-risk reuse case for these two one-line edits. **UNKNOWN:** fresh official extraction, obligation, axiom check, and round trip. They must be validated for the exact hashes below before being called correct candidates.

## Delivered files and verification

Generator: `scripts/make-round3-tiny.py`; only these two single-factor directories are generated. Each contains the Rust file, exact probe3 proof, and a manifest retaining submission-261 attribution and the official pinned revision.

| Candidate | Rust SHA256 |
| --- | --- |
| `round3-tiny-kind2` | `366a2741f6528410fa4f315203b59f43ec1c2b8b4ece1fe1299415feed4bb724` |
| `round3-tiny-rep1` | `70803ad9cbf1548ae97605bba42a80974565c72c0dab8a00bfbfbe0b93409e6d` |

Both proof SHA256: `3906aeb259d83d315811629a54d796b514fc3953742063081451c47997b824b7`.

**VERIFIED:** generator and read-only `--check` exited 0; baseline hashes are pinned; only the declared constant is changed per candidate. **UNKNOWN:** performance, official correctness, private stage2, admission, ranking, and rewards. No CI, commit, push, or wallet operation was initiated.
