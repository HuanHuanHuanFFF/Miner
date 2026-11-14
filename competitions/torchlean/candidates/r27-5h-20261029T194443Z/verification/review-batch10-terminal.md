# B10 terminal acceptance review

Review time: 2026-10-30 00:22 UTC. Before raw review, the parent status, newest requests, public collaboration status, and saved board bytes were reread. Run `40977309820` is terminal with workflow conclusion `success`; source commit `e0019e9ce2a5000ec882a963c51e55fbec1b08ae`.

## Correctness and frozen source

- Candidate `public23-gemm27-native-add-qualified`, SHA-256 `f60551d55be31d2d2d4a59ba2646c8769d1cb8e31538176041070a0477881bea`, 255,666 bytes. Reconstructing from saved public submissions 23 and 27 reproduces the exact hash and byte count.
- The exact candidate passed the full original gate: exit 0, `axioms` stage, stable verifier fingerprint `3a69968c7210ab18b325047e518ddfa942e642e21268a241e8693b075377bee6`, not exhausted. This is correctness-gate PASS for the exact source hash. CI success alone is not the proof evidence.
- `MainExact` hash is `b324bad32bc4ce449eb69be00e252163b77de4a0295736debe4081b53c4681ab`; runner copy assertion and root audit agree. Compile, link, and response-file argument traces match the original after target-name mapping: 22 compile args, 4 link args, and 10,080 response args per side.
- The run uses the frozen B10 plan and all owned-source hashes match dispatch. The run commit remains authoritative for plan/hash verification even if the shared `ci-plan.json` later moves.

## Standard Mixer measurements

This is the Mixer single-board cohort: six Mixer cells × six official seeded workloads = 36 cell/workload pairs per round. Each of two roots has 11 rounds, three inner repetitions, and 50 ms per cell, producing 396 paired rows and 792 reported nanosecond values per root. The two roots have 792 matched checksum pairs total; none mismatch. Alternation is reference-first on even rounds and candidate-first on odd rounds. Both roots use the same x86_64 runner `runnervm48cm3`, affinity 0, with identical candidate/reference binary hashes.

The slowest raw candidate sample in root `2860084832` is round 1, `s5|mixer:b1:normal`, 122,237,347 ns; in root `3164475393` it is round 5, `s2|mixer:b1:sparse`, 72,955,377 ns. Both corresponding checksums match. All original slow rows remain in the artifact.

Independent replay with the pinned R25 scorer agrees with the root audit. The comparison target is current Mixer submission 36, whose source is unavailable. Submission 27 is only the historical report calibration carrier, not the current champion. The result is **1.2342594908× current Mixer #36 time** (`INFERRED`, slower; pinned performance guard failed). The #36 report config differs from the live board config and the local standard runs do not match the production environments/seeds, so the strict converter remains **UNKNOWN**. This does not establish a promotion or champion win.

## Integrity and delivery state

- Artifact 12943658031 has digest `sha256:153edf92219a7e7f4b5225fc93ee67c6ecf738aa3b0d0966483035aec73ed1b8`. Manifests pass: 79/79 outer files and 78/78 inner files, no missing or unexpected entries.
- Independent result is [audit-native-run-40977309820.json](audit-native-run-40977309820.json), status `PASS_B10_GATE_AND_NATIVE_ACCEPTANCE_AUDITED_NO_PROMOTION`, zero failures. It checks the fixed scorer, source and dispatch hashes, exact gate, row counts, checksums, order, CPU, and root score.
- `CI-RESULTS-BATCH10.json` appeared at 00:26:51 UTC, after the independent audit capture. It matches the candidate hash and gate, both 396-row cohorts, checksum counts, and the independently reconstructed current #36 multiplier; file SHA-256 `4989d6b593b26d3e141d8b971c13792ab7f245996f7058c1503392a2bd5b3011`. Droot owns the integrated result and Git.

Conclusion: the NativeAdd composition passes the original correctness gate and the complete standard data is auditable, but the candidate is slower than current Mixer #36. No promotion is established.
