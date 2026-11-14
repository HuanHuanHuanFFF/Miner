# CI3 terminal verification

## Run binding and evidence integrity

Run `41107618451` completed successfully on source commit `4494a73ee77ec96832e44e010b235197d8290eda`; frozen plan hash is `4349b33e08b826f21801278644bd9d61da4790589682ace4a2343a0f75e6e410`. The CI metadata says `completed/success`, dispatch receipt and summary bind the same run/commit, and run time is 1,324.412 s from 18:32:57.308 to 18:55:01.721 UTC.

The fixed R28 `audit-native.py` completed independently. Its output is byte-identical to root's `root-fixed-audit.json` (SHA-256 `dbdbe1588464c1a3f0f643a1b81196d8e9e4b4d581df5772024f02bf7c81620f`). It verifies all 136 outer files and 135 inner files with no missing/unexpected files, the exact frozen plan/dispatch, source preservation, unchanged `MainExact`, and pinned scorer hashes. It also rechecks raw round files against each aggregate measurement, request workload/seed/cell identity, each checksum and score under the pinned scorer, and compile/link/response flags after allowing only the expected target-name mapping.

All three candidates have two complete seeds, with 180 paired rows and 180 checksum pairs per seed. That is 1,080 paired rows and 1,080 matching checksum pairs total. Every run used the same CPU identity `2ce5abb0…`, machine `runnervm48cm3`, `x86_64`, affinity `0`.

## Original proof gates

The actual original verifier was run independently for the exact `public36-norm26` and `public36-pairlinear-v2` source hashes, with separate candidate gate directories. Both reached `axioms`, passed, were not exhausted, and had identical verifier fingerprints at start/end. Their raw logs show `Submission replays cleanly`, `VerifyExact replays cleanly`, then only the allowed axioms `Classical.choice`, `Quot.sound`, and `propext`. No proof was inherited from another candidate or run.

`public36-centered64-native-only` is correctly left `NOT_PROVED_NATIVE_ONLY`; it was not sent through a full proof gate. CI success does not change that boundary.

## Results against the current #56 Mixer

The measured internal comparison is against public #36; conversion to current #56 uses the saved promotion-chain ratio `0.8574912831` and remains inferred because #56 source was unavailable.

| Candidate | Full original gate | Local score vs #36 | Estimated time vs current #56 | Finding |
|---|---|---:|---:|---|
| centered64 NativeOnly | No | 1.119968; guard failed | 1.306099 | Negative; not proved |
| norm26 | Pass | 0.944437; guard passed | 1.101395 | 5.56% faster than #36, but estimated 10.14% slower than #56 |
| pairlinear-v2 | Pass | 1.044335; guard passed | 1.217896 | 4.43% slower than #36 and estimated 21.79% slower than #56 |

There is no current-champion win or official promotion. `norm26` is the best developed branch for further exploration, with fresh standard confirmation still pending if pursued.

## Profile boundary

The reference-only instrumented profile reports six cells, but covers only four kernel-entry calls. Across those six rows, the shares within those four profiled entries are: linear 43.11–61.71%, layernorm 22.03–45.50%, GEMM 8.24–12.08%, and add/ReLU 2.92–4.81%. The profile explicitly excludes work outside these calls and cannot be read as whole-model share or a promotion score. The complete paired model measurements already include preparation, bias, fallback, and remaining model work.

The run and original evidence remain in `evidence/41107618451/download-61071bff514a4286bc113fab65196ffd`; no terminal artifact was altered. This review does not claim current official promotion, performance adoption, or fresh confirmation.
