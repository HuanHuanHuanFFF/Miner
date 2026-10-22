# R6 research source freeze, 2026-10-22 14:12 UTC

All R runtime mechanisms and mathematical artifacts are frozen; no additional direction or webpage job will start. Remaining R work is validation-feedback repair only if D needs it within the agreed window, exact receipt interpretation, and final handoff. D retains Git/CI/combination ownership and final independent confirmation reserve.

Preferred frozen sources:

| Mechanism | Exact candidate | SHA prefix | State at freeze |
|---|---|---|---|
| Two-compare scalar normal add | f01-r6-normal-add-proof1 |8a0e40fb8154| D706 pending |
| Low-mul proof-erased redundant guards | f01-r6-web-lowguards |75ddbcff076c| D706 pending |
| Normal product leading bit46/47 | f01-r6-normal-mul-proof1 |96865cbae714| NOT_RUN |
| Bias RN-even plus direct low packing | f01-r6-active-bias-proof1 |998747fae005| NOT_RUN |
| Exact finite-normal gap26 absorption | f01-r6-web-absorption26-proof1 |dcfe0c8e2686| NOT_RUN |

Full SHA/bytes in manifests and handoff-source-identity.json. Intermediate originals and failed704/705 versions remain untouched. Earlierfused-add-proof1 is retained as an optional ablation; normal-add-proof1 is preferred, with no demand to queue both. No R candidate has a claimed passing full gate yet.

Four R6 webpage ZIPs+four reports remain at E:/Download and have fresh SHA/CRC checks. Prior R2-R5 ZIPs were removed by documented12:20 maintenance after extraction; the current material manifest was followed and all376 historical members reverified. **Do not claim16 ZIPs still exist on E.** download-index-final.json lists four current pairs and points to the historical migration evidence. Original webpage NOT_RUN labels and conditional hypotheses remain unmodified.

Local root project check PASS: both tracks,136 FloatLib candidate hashes,11manual workflows,73root links. The extra attempted path competitions/floatlib/scripts/project.py does not exist and ran no check; root scripts/project.py already contains the FloatLib checks. This local PASS covers files/manifests/links/configuration only, not Lean, axioms, runtime behavior, performance, suite admission or champion replacement.

Official update during the window changes the performance question: old twelve-class exposure is legacy-only. Actual new public-v2 shares still pending D nested gate; private paid-suite case details remain unavailable. Champion goal unachieved. Source-level cost counts, finite oracles and abstract conditional NaN proofs are not substitutes for complete-cost actual validation.
