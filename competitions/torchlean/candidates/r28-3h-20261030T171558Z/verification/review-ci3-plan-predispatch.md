# CI3 Mixer plan/source/correctness-boundary review

Captured 2026-10-30 18:34 UTC. The root status and `CI-REQUEST.json` identify run `41107618451`, commit `4494a73ee77ec96832e44e010b235197d8290eda`, plan `4349b33e08b826f21801278644bd9d61da4790589682ace4a2343a0f75e6e410`. The run is already identified, so this is a frozen-plan audit, not a request to edit or restart it.

## Exact candidate and current-target bindings

Independent in-memory rebuilds match all three planned hashes and lengths using public #36 source SHA `595a90fa…c956e2b`; the pairlinear-v2 rebuild also matches the pinned public #27 donor hash `f92ee2c9…3481aa67`. No candidate source bytes were written by this audit.

- `public36-centered64-native-only`: `c5acf195…af8f642`, 235,376 bytes; `full_gate=false`, `declares_correct=false`. It is a cost-only source with no new `Submission.correct` proof.
- `public36-norm26`: `79615bd5…ad417d7`, 255,514 bytes; exact new original gate required.
- `public36-pairlinear-v2`: `7b6e0cba…2a06ae3`, 252,828 bytes; exact new original gate required. Its dispatch condition is the v2 `k<1` route; no v1 gate result is inherited.

The three candidates remain below 256,000 bytes. The fresh Mixer #56 response and boards publication hashes match the plan; current #56 source is unavailable. Public #36 is the calibration source, so any candidate/current multiplier remains inferred through the official chain, not a direct #56 timing pair.

## Profile and probe

The plan's `profile-mixer36.py` hash matches. It instruments four reference #36 entries (`YaVM`, `Ya3M`, `Ybf`, `YbcN`) and maps them to linear, GEMM, add/ReLU, and LayerNorm. It uses the 240-second global cap and 20-second per-call caps; the runner catches profile errors as diagnostic-only. The code probe hash also matches and emits derived counters only, without changing the scored binaries, flags, benchmark requests, or publishing generated C bodies.

## Gate-budget risk

The 1,800-second driver covers reference build/profile, the NativeOnly cost-first candidate, and two candidates with original gates each capped at 600 seconds. It does not reserve 600 seconds for each later gate after earlier native-cost work. The batch is already running; if an original gate is clipped by remaining time, label it `INCOMPLETE`, not a source counterexample. A successful quick screen would still need a fresh standard independent confirmation before adoption.

Exact source/proof flags, plan snapshot binding, dispatcher freeze hashes, and the formula rebuild are recorded in [audit-ci3-plan-sources.json](audit-ci3-plan-sources.json). No CI3 result has been reviewed yet.
