# R27 candidate/runner preflight checklist

This is a static review checklist for the first candidate/CI handoff. Current status for every unchecked item is PENDING; absence is UNKNOWN, never pass.

## Source identity and pinned target

- [ ] Candidate file is UTF-8 Kernel.lean, <=256000 bytes, exact SHA-256 recorded in frozen R27 plan and runner manifest.
- [ ] Reference bytes/hash match the chosen report-chain anchor in champion-only-record.json. Current champion source bytes are unavailable; do not substitute a retired champion and call it current.
- [ ] Candidate and reference target the same board and same report config hash in official-report-chain.json. Every report config hash differs from current boards.raw config, so a live-board-config run cannot inherit the old report factor.
- [ ] Official source pin is accb82b6e2adeda1b41a57a260d68fb3879c427e, Lean 4.34.0; Kernel.lean imports only ContractExact.
- [ ] Source and benchmark config inputs are hash-bound; contracts, gate, benchmark and pins remain unmodified.
- [ ] Source publication policy for any retrieved predecessor is resolved before sending its bytes to a runner. Current receipts mark source bytes LOCAL_ONLY.

## MainExact, target and flags

- [ ] Original MainExact.lean bytes are identified from the pinned official checkout and SHA-256 recorded. R26 audit baseline: b324bad32bc4ce449eb69be00e252163b77de4a0295736debe4081b53c4681ab; verify again for the R27 checkout.
- [ ] One added target is built from those exact bytes; record the full Lake/build argv and target mapping.
- [ ] Compare original and candidate target compile arguments, link arguments and response-file arguments after only target-name normalization. Record raw argv and response file hashes.
- [ ] Same target builder and build path are used for candidate and reference; record CPU identity, architecture and affinity.

## Official winner-report input contract

Use the exact report_config_hash and one seed for the selected board from official-report-chain.json. Production reports have 11 rounds, inner 3, 50 ms/cell, with workloads wide/normal/sparse. Each official current row contains amd64 and arm64 runs.

| Board | Seed | Cells | Repetition entries per environment | Benchmark seconds |
|---|---:|---:|---:|---:|
| overall | 2327529241 | 30 | 180 | 1200 |
| mlp | 2777525764 | 6 | 36 | 360 |
| mixer | 1593160531 | 6 | 36 | 360 |
| resnet | 1198852529 | 6 | 36 | 360 |
| mobilenet | 1208908567 | 6 | 36 | 360 |
| normalized_mlp | 3542272469 | 6 | 36 | 360 |

- [ ] Frozen request uses the selected board's current report seed, complete cells and three workloads; no missing row becomes zero.
- [ ] Compare candidate and chosen reference under the same seed, timing, environment and alternating order. Record the exact per-run environment actually available; an amd64-only candidate result multiplied by the mixed amd64/arm64 official report remains INFERRED.
- [ ] Preserve all raw timing/checksum rows and CPU provenance; validate full pair count and checksums before the original pinned scorer runs.
- [ ] R26's 5-round/2-ms quick plan is not this contract. R26 used two unrelated local seeds and compared against retained bcb817; do not score it as a current champion result.

## Correctness boundary

- [ ] Candidate full original gate covers intake, policy, statement, kernel and axioms for all twelve obligations, with only propext, Classical.choice and Quot.sound allowed.
- [ ] Native compilation, checksums, reference proof replay, finite diagnostics and report-derived score are independent evidence; none substitutes for candidate proof.
- [ ] Until the candidate passes its exact full gate, label it UNPROVED_NATIVE_RESEARCH_ONLY or equivalent and do not claim it is correct or officially promoted.

## Reused scorer identity

- [ ] Verify pinned R25 source before import: config.py blob 6743c5c0060b7babab5155ffe1e0dc94dbf8a742; multiseed.py blob 299b2e77db596a2720db3d54c2df46b3e5d2c3b3; scoring.py blob f5e1b500bc3976764eea0451c500907e08e17dda.
- [ ] Reuse R26's small source/hash and runner checks plus the original scorer functions. Do not copy the R25 proof-gated analyzer or claim its saved-reference score is a current-champion pair.
