# CI6 isolated standard group terminal audit

CI6 run `41119180001` completed on commit `c68fb4c752cff8d937ef5960dcced2a0a64e3108`. The independent runner-terminal receipt passed `terminal-evidence.py` for that exact run/commit. The fixed R28 `audit-native.py` was then run independently; its output matches `root-fixed-audit.json` byte for byte, SHA-256 `579b708ef93c227961aa76ac93f2a266b404ac4c257dde3e1e417f8f09a0b829`.

## Integrity and standard group

- All 133 outer and 132 inner artifact files match their original manifests. Source preservation, `MainExact`, compile/link/response flags, and the pinned scorer pass.
- Both candidates have 792 paired rows and matching checksum pairs each, across the two fresh roots in the frozen standard 11-round / 3-inner / 50 ms group. All roots use the same CPU identity `282afe1f…`, x86_64, affinity 0.
- The official platform metadata still reports `in_progress` with no conclusion. The runner finished at 20:13:38 UTC; the artifact finalized and post-job/orphan cleanup completed. Those original platform bytes are preserved.
- The group is complete. Its seeds and per-seed inputs/results remain in the audit/raw evidence; after the 20:20 root release they are no longer held under the pre-completion isolation rule.

## Source-specific proof binding and results

- Norm26 is exactly `79615bd5…417d7`, the same source that passed CI3's original all12 gate through `axioms`. The binder receipt [exact-source-proof-confirmation-binding.json](../evidence/41119180001/exact-source-proof-confirmation-binding.json) verifies the exact prior summary/verdict hashes, stable verifier fingerprint, and both complete standard roots. CI6 itself did not rerun the full proof.
- Norm26 standard score against public #36 is `0.951740`; the internal retired-control scorer passes its guard. Against the fresh 20:12:37 #56 Mixer snapshot ratio, the candidate's inferred estimate is `1.109913×` current—about 11% slower than the champion. It does not win or establish promotion.
- `norm26-input-zero-native-experiment` is `29e71174…7653eae`, `NOT_PROVED_NATIVE_ONLY`. It scores `0.970509` against #36, above the `.97` bar, and is estimated `1.131801×` current #56. It remains experiment-only; the binder confirms no proof transfer.

The fresh six-board snapshot matches all raw response receipts: overall #59, MLP #33, Mixer #56, ResNet #64, MobileNet #57, normalized MLP #51. Current source stays unavailable and the current-champion multipliers are inferred from the official ratios. No formal submission, funds, signing, or official promotion occurred.
