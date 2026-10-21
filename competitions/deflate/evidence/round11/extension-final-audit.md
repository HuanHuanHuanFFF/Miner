# R11 extension final audit

The reviewed Pareto snapshots are 28420, 28462, 28529, and **28635**. Each has 511 unique Pareto rows, 79 frontier rows, and 485 leaderboard ranks. All captured pages match their raw responses, terminal cursors are null, and every raw/derived byte count and SHA-256 matches its receipt. Across snapshots, row IDs and shared metrics are unchanged.

Latest snapshot 28635 was computed at `2026-10-08T06:43:15.356923+00:00`. API freshness is **unknown**. `weights/current` separately reports snapshot **28636** (`weights_same_snapshot=False`); it was not combined with the 28635 Pareto geometry.

#453 remains off frontier with `pareto_weight=0` and `payable_weight=0`; the API row says `payment_eligible=true`, and no same-hotkey frontier point survives. At fixed #453 size, time must be strictly below **0.434267784** (#507), a **0.82345%** reduction. At fixed time, size must be strictly below **36.664602629%** (#506), an improvement of **0.335126 pp**. These limits are unchanged in all four captures.

There are **8 distinct Rust candidates**, **14 CI attempts** (4 failures, including the two same-source-path preflight rejections), and **9 successful public performance jobs** totaling **132 paired processes**. All nine gate state maps are empty; no new full gate was accepted. The two-run groups confirmation excludes groups-e as selection data and averages only confirm-h/i; it is slower than pipeline by **0.389509%** on the equal-run mean, with 444 finite cases and zero differences.

Fast-l is **0.2569776% slower** than its parent, with no size change. Its 444 finite cases report zero differences, but this is not a full gate. The native Huffman job is a separate read-only diagnostic (28 inputs, 130 cost blocks, 260 tables) with no benchmark state or timing JSONL; it is excluded from performance counts.

The JSON audit records each capture's raw/derived hashes and pagination, snapshot comparisons, CI/run inventory, candidate evidence, and limitations. No chain state was checked, so validator acceptance and actual income remain unknown.
