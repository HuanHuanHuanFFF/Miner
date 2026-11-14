# Batch 3 dispatch review — 2026-10-29 20:54 UTC

## Dispatch identity

- Official run `40952423982` is recorded as `in_progress`, created `2026-10-29T20:49:21Z`, source commit `c6999b16ac9e24ddf64abc48ec040edcd3152b86`.
- The dispatch records `repository_public=true`, `allow_private=false`, candidate selector `__torchlean_r27__`, and seed `27102921`.
- I independently recomputed SHA-256 for every path in `evidence/dispatch-20261029T204919Z/dispatch.json`: all 17 of 17 frozen file hashes match the checkout, including runner, exact plan, all three candidate generators, helper sources, and profile adapter.
- The plan hash is `eac8158f55273dcbf6580b025e0a8461fe8d513f3d3ff3941302b072307e711b`; runner hash is `58b20a75732b133889ec20235268d66ee637810faad5cca90abb2f6d0e660782`. Both match the preflight record. No dispatch-frozen file drift was found.
- The shared development-status and CI-QUEUE snapshots still show their 20:45/20:00 pre-dispatch contents (`active_CI=[]` / batch 1). Treat the later `dispatch.json` run identity as the current execution evidence and refresh the parent status/queue when the runner reaches a new state.

## Champion and candidate boundary

- The saved official board snapshot still identifies normalized MLP promotion 24 / current submission 23, current source hash `1010c0744f0506974c64601e8ce7335bea56d0cb21b655543d390794df0665fe`, with `source_available=false`. No current champion source bytes were available in the saved responses.
- Submission 12, source hash `e2c1f1f1ba52e32563fb193ceea7e2a271b989fd3ba2eb16cff747987879b521`, is only the public predecessor/calibration carrier. The official report chain says current23 / #12 = `0.9575717364640264`. A future estimate is candidate/#12 divided by `0.9575717364640264`, and remains `INFERRED` unless directly paired with current23 under matched conditions.
- Frozen candidates are: native-layer-stats-v1-hb `1bd6e153…4463e8b` (255,969 bytes, `full_gate=false`); guard26-v2 `dced7848…bf1cb9` (218,583 bytes, `full_gate=true`); norm-prep-proof2 `40b17282…8a3a8e` (222,258 bytes, `full_gate=false`). Only the guard26-v2 row requests the complete original gate. Native-only status or a successful CI job does not establish `Correct`.
- The official report-chain auditor was rerun locally against saved bytes only: 6 boards, no failures; output hash stayed `8593d996072703e1b1b92324836f1ee8212fce9d6a5efe2ea59769cb72f96f0f`. No source endpoint or live API was queried.

## Result status and next review

At this checkpoint the run has only an in-progress dispatch record; there is no terminal CI result or candidate timing to score. The plan uses quick exploration seeds, not normalized-MLP current23 production report inputs, so any quick paired result is route-planning evidence only and must not be presented as a qualified champion comparison. The preflight profile-time budget risk remains: classify any gate cut off by the runner limit as incomplete/budget-limited, not as a proof failure.

At terminal, first reread parent status, requests, and saved public-board state. Then bind the terminal artifact manifest and raw hashes; check MainExact bytes, compiler/link/response flags, complete paired-row counts, all checksums, slow samples, CPU identity and alternation before reusing the pinned scorer. Keep current champion multiplier `UNKNOWN` unless the exact official report plan and scorer bindings pass.
