# Round 3 speed direction — bucket footprint

Prepared 2026-10-06 15:20 UTC. Scope: two candidates for the current 90-minute research batch; no CI dispatch, commit, push, competition submission, or wallet action by this worker. Base checkout observed at `84e8978e5ef69e5e8f8ef6c4b18c27d93c8e5251`.

## Delivered candidates and mechanism

**VERIFIED (source inspection / generation)**: `round3-speed-bucket16k` and `round3-speed-bucket8k` each change exactly four Rust lines from accepted `bucket2`: the bucket hash keeps 14/13 high bits rather than 15, and its three large-input text/prose/structured-text dispatches instantiate both arrays with 16384/8192 entries. Every public constant, ordinary `run`/`run_rest` path, tiny planner, match search, insertion timing, backward fold, and emission body remains byte-identical. `Parse.lean` is copied byte-for-byte.

| Candidate | Two-slot table payload | Change from bucket2 | `parse.rs` SHA256 |
|---|---:|---:|---|
| `round3-speed-bucket16k` | 131072 bytes | −50% | `e28fa488c7f8cbc8bafed179b56dac681c22ec2b79bcc50895900d6c6527a99e` |
| `round3-speed-bucket8k` | 65536 bytes | −75% | `6250f73f72c142cce078942a6967b08edc2388ebcdc764be33caba8a2e6bef1b` |

Shared proof SHA256: `421c58d4695b80d25b3b17eb53d065fa5764185352491f4c1b17d32fff26a7c1`. The frozen source SHA256 of `bucket2` is `38bb6c7d4df093e6cedbad9651d5ee4377d75fa995106d70dce5c08585cac4db`; the generator fails on base drift.

**INFERRED (performance hypothesis)**: shorter arrays reduce clearing traffic and the working set of two hash-indexed slots. Unlike reducing the search depth, they keep both available probes. Added collisions can evict useful same-key candidates, so size may worsen; changed collision order can also change search work. No speed or size improvement is claimed without paired measurement. The 16K version is the more conservative tradeoff; 8K tests whether the second footprint reduction outweighs its collision cost.

**VERIFIED (proof structure)**: `Submission.Bucket2.run_spec` and `Submission.parse_spec` quantify table dimensions and require only positive `H` and `W`, not 32768-entry tables or full-window token equivalence. `bucket_insert` only proves the first head position bound; the second-slot contents require no invariant because the existing verified `find`/`walk` checks each candidate and decreasing links. Thus the planned proof source modification is zero lines. The new hash shift is a fixed safe `u64` shift of 50/51 bits, replacing the previous fixed 49-bit shift.

**UNKNOWN (fresh correctness)**: the copied proof has not been checked against either new official extraction. Aeneas extraction, Lean obligation, axiom audit, and official 28-file DEFLATE round trips must all pass independently. Historical acceptance of the base proof is not acceptance of these changed sources. Small buckets deliberately do not promise token equivalence with `probe2` or `bucket2`.

## Why this direction

**VERIFIED (source)**: `bucket_find` already builds a one-entry virtual chain and is marked `#[inline(always)]`; its inner `find` and `walk` are also always-inlined with window size one. Hand-writing another two-candidate search would require new proof work and might reproduce the compiler's current scalar code. Actual generated machine code has not been inspected, so its elimination of the virtual array remains **UNKNOWN**. The footprint candidates offer a concrete changed memory volume while reusing the accepted proof structure.

True adjacent AoS slots or a packed 64-bit bucket remain unimplemented. They would require a new data-structure bound, extraction-aware insertion proof, and changes to duplicated engine loops. They were not added during this scoped batch because the two small-footprint candidates provide an earlier falsifiable experiment.

Historical attribution at `evidence/round2/37480653625/research.json` confirms that regular text searches are exercised in prose, C/Lean/Rust/Python/source files, JSON/XML/HTML/YAML, multibyte text, and the structured CSV/log route. Those counts are lookup diagnostics, not timing evidence. Binary paths and tiny routed inputs should be the unchanged controls in per-file comparisons.

## Frontier test and rejection conditions

Use `evidence/round3/frontier-targets.json` fetched at 2026-10-06 15:16:24 UTC, snapshot 23753, and the parent's fresh paired equal-file measurements. The calibration from #427 is time × `1.014402891250616`, size × `1.0070277985275755`; it is a heuristic transfer between public and official scores, not stage2 evidence.

| Target | Public time cutoff | Public size cutoff |
|---|---:|---:|
| #432 | 0.43511809883823444 | 36.655130285662274% |
| #425 | 0.4383665828506731 | 36.06318569346872% |
| #403 | 0.44648677815639365 | 36.0536137517627% |

These cutoffs describe matching a selected point's two coordinates. Full Pareto-space checks must compare each calibrated candidate against every current frontier point; merely crossing one row does not establish admission. For scale, historical rounded `probe2` size 36.035722% has only about 0.02746 percentage points of public size room to #425 and 0.01789 to #403. It has much more size room to #432, whose time requirement is tighter. This makes the collision penalty a material test rather than an incidental regression.

First falsifiable test: compile and time the two candidates beside `bucket2`, `probe2`, `probe3`, and the same official incumbent on the same runner and fixed corpus. Report per-file output bytes/hashes, paired time coordinates, order blocks, and raw repetitions. Reject a candidate if its measured size/time point is dominated by another measured candidate or fails its fresh correctness gate. A stable text-route speed benefit accompanied by size losses must be reported as a tradeoff. If unchanged-route files show large apparent improvements, inspect host/order drift before attributing them to the smaller buckets.

## Local checks completed

**VERIFIED**: `python scripts/make-round3-speed.py` generated both candidates and hash manifests; `python scripts/make-round3-speed.py --check` then reconstructed and compared every output byte without writing. The generator checked frozen base hashes, exactly four changed source lines, identical constant declarations, and identical proof bytes. Read-only Git diff confirmed no change to existing `bucket2`, `probe2`, official sources, or the round2 generator by this worker.

No local Rust or Lean toolchain was installed or run. Fresh official correctness, public paired performance, private stage2, online admission/rank, and rewards remain **UNKNOWN** at this handoff. The parent will run the authorized temporary Linux CI and attach its evidence separately.

## Public #407 follow-up — active paths, 2026-10-06 15:27 UTC

**VERIFIED (preserved official source)**: a later task added three independent single-constant derivatives of `references/round3-public-407/`. The official source endpoint is `https://conjectures.io/v1/competitions/deflate/submissions/407/source`, retrieved at 2026-10-06T15:21:20.348Z. The available original author attribution is public miner hotkey `5G4QE3WeVrjCo2VQaBYttFWrHexzuPFAibGjGDgi6mR8eX8F`. The original source SHA256 is `64945bab5fa675ed724748b3097bf02477ba3677afc9fa4478a394ccc0996a40`; original proof SHA256 is `ed37de55387d9a984afa841b83aac1edd4ea4517cfb5831967884b6783fa98a8`. Each candidate includes these values and original attribution in its manifest and `PROVENANCE.md`.

The call chain was inspected from the actual `pub fn parse`, not inferred from its opening comments:

- `parse` first does the existing quick RLE sample where enabled, otherwise full sample/statistics; `fl_mode` selects the floor lane and `fl_part` invokes it.
- In `fl_mode`, existing small inputs (`FL_SM_N=65536`) take mode 6 after the RLE check and before DNA/high/base classification. `fl_sm_parse` runs greedy scan → `fl_sm_rules(..., FL_SM_DT)` → replay. Increasing `FL_SM_DT` is active here. It does not change `fl_sm_rle`, which uses the separate unchanged `FL_SM_RLE_DT=500`.
- Base text and the zero-rich machine-code class invoke `main_parse` → `gr_text` because `R1_TEXT=1` and `R1_MC=1`. `gr_text` uses `G_ACC=4` unless `low=1`, when it uses 63. `gr_scan` grows probe stride as `(miss_count >> (acc % 64)) + 1`, capped by unchanged `G_AMAX=12`. Changing `G_ACC` to 3 makes stride grow sooner across nonmatching stretches; possible losses in match coverage are the intended tradeoff.
- The actual `gr_insert_match` body fixes first-two-plus-last insertion. `G_IH` and `G_IT` are not read by that active R1 function. The old `FT_DEPTH`/`FT_DEPTH2` lazy settings are also not the regular small-input mode 6 search. `main_parse_high` uses its own fixed acceleration value 8, while `lg_parse_h` and `lg_parse_d` use separate `LG_H_ACC`/`LG_D_ACC`; none are changed here.

| Candidate | Only changed constant | Source SHA256 |
|---|---|---|
| `round3-speed-407-dt900` | `FL_SM_DT: 600 → 900` | `0b82a5c3df5cb88b7c650310f5b213b05263eef9ffdbc62f86052fc8cc0da42c` |
| `round3-speed-407-dt1200` | `FL_SM_DT: 600 → 1200` | `e56f77efbb6e7493de44102ef57a4d926c93414e0da15938408c9a567508d73c` |
| `round3-speed-407-acc3` | `G_ACC: 4 → 3` | `2abe362474f04a273a48e4d9b0a7b5f0674cdb0074f9ce6312cda4fcaa5aca3c` |

**INFERRED (general mechanism)**: raising the assumed per-live-symbol cost removes more rarely used distance/length symbols from a small block's cached plan. That can reduce encoder alphabet/package-merge work, especially where per-block setup is a large part of elapsed time, at the expense of more literals or split matches. The threshold operation itself still executes the same fixed loops; it saves work through the resulting token stream and encoder. This is why parser-only speed is an insufficient test. No corpus filename check, new length rule, or route exception was added.

**VERIFIED (static proof reuse basis)**: `fl_sm_rules_spec` quantifies an arbitrary `dt`, and `gr_scan_checked`/`gr_text_loop_checked` quantify an arbitrary acceleration argument. The existing `g_acc_ite_spec` bound depends on unchanged `G_AMAX=12` fitting its `≤16` result; changing only `G_ACC` leaves that bound untouched. Every candidate retains all function bodies and all proof bytes exactly. Fresh extraction/Lean acceptance still remains **UNKNOWN**.

**INFERRED (frontier target scale, not a forecast)**: the official #407 snapshot time 0.4499838311061295 and size 36.499576583188635% are not a fresh local measurement. A 2% time reduction at that coordinate would be 0.4409841544840069, slightly faster than #432's 0.4413850574969763, with approximately 0.41316 percentage points of official size room to #432. A 3% reduction would be 0.4364843161729456. The parent must use fresh public paired equal-file time and size, apply the supplied calibration factors, and compare with every frontier point. For the two threshold candidates, the total encoder-plus-parser time over all 28 equally weighted files is the decision quantity, not byte-weighted totals or tiny-file anecdotes.

**VERIFIED (local reconstruction)**: `python scripts/make-round3-speed407.py` generated all three candidates, then `--check` reconstructed and compared the entire Rust, proof, manifest, and provenance bytes. Each candidate changes exactly one numeric constant declaration; all helper and `parse` bodies are unchanged. The original two files retain their precise hashes. No Rust/Lean tools, gate, CI dispatch, commit, push, competition submission, wallet access, or new worker was used by this worker. Fresh correctness, public paired performance, stage2, admission, rank, and rewards remain **UNKNOWN**.
