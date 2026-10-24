# R12 adopter scoring-pair fixtures

**Scoring and estimator comparators are now exercised separately.** The 6c2d rows feed the adoption score; the same-run 41 rows feed only `estimate_champion_time` through the estimator-pair path. The fixture deliberately gives those sources different normalized ratios so accidental reuse is visible.

The disposable index contains candidate, retained 6c2d, and 41 control rows for each source run. Candidate and 6c rows share run, seed, suite, official commit, runner execution, drawn plan, provenance, reference fingerprint, and cell work. New cases reject a missing 6c row, wrong 6c SHA, incomplete 6c gate, same-run baseline from another artifact directory, and same-run baseline from another runner. The estimator mock independently requires one exact full-gate 41 record paired to each candidate run, with matching seed/suite/runner. Separate assertions verify score pairs use 6c and estimator pairs use 41.

Adoption fixtures carry the prior `retained_numeric_model_freeze` in both the comparison view and current state; successful adoption asserts it is removed from both new-source views. Existing write/rollback/resource tests remain.

**Verification:** `test_adopt_three_confirmed.py` ran 31 tests; all passed. The log is [adopter-scoring-pairs-extended.txt](/D:/CodingProject/Bitget/.runtime/floatlib-r12-6h/adopter-scoring-pairs-extended.txt). This uses synthetic gate rows and the frozen estimator seam; it does not rerun CI or authenticate real run artifacts. Exact file hashes are in `review-adopter-scoring-pairs.json`.
