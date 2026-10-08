# R11 final frontier capture review

The official-final capture is snapshot **28420**, computed at **2026-10-08 12:58:10 +08:00**. Its six Pareto pages contain 511 unique rows (100, 100, 100, 100, 100, 11); five leaderboard pages contain 485 rows (100, 100, 100, 100, 85). Both final cursors are null. All 13 raw HTTP response files and four derived files match their receipt byte counts and SHA-256 values; every raw page decodes exactly to its merged page. The API reports freshness `unknown`.

`weights/current` separately reports snapshot **28421** at 2026-10-08T04:58:40.101750+00:00; `weights_same_snapshot=false`. It was kept separate from the 28420 Pareto geometry. No chain state was queried.

Compared with official-start snapshot 28214, Pareto rows increased from 507 to 511. The only new IDs are **508–511**; no prior ID was removed and all 507 shared rows retain identical metrics. The frontier now has 79 rows (82 before); new frontier IDs are 509, 510, 511 and removed prior frontier IDs are 469, 476, 482, 492, 493, 505. The new rows' coordinates and API eligibility are in the JSON receipt.

#453 remains off frontier: `(time=0.437873458, size=36.999728557)`, `pareto_weight=0`, `payable_weight=0`, although its API row says `payment_eligible=true`. No submission for that hotkey survives on the current frontier. On snapshot 28420, keeping #453's size requires time **strictly below 0.434267784** (limit set by #507), a **0.82345%** time reduction. Keeping its time requires size **strictly below 36.664602629%** (set by #506), an improvement of **0.335126 pp**.

The R10 pipeline same-family projection remains `(time=1.403780310, size=34.185517190)`. It is not an official submission and remains dominated by #360, #418, #422. At fixed size it needs time **strictly below 1.333373452** (#418), about **5.01552%** faster. At fixed time, size must be **strictly below 34.177242463%** (#422), an improvement of **0.008275 pp**. Replaying the captured policy on snapshot 28420 gives zero geometric and conditional same-hotkey additional share for this point.

The exact raw and derived hashes, added rows, threshold calculations, and scorer replay are in [`frontier-final-review.json`](frontier-final-review.json). The pipeline transfer remains an inferred public-to-formal projection; admission, registration, bounty, deployed validator identity, actual chain acceptance/payment, and API freshness remain unknown. This review used no new API request or CI run.
