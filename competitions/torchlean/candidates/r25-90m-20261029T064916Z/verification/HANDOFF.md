# R25 verification handoff

**Final acceptance · READY** · verification scope only; no CI, Git, or Lean was started here. Official source ref: `accb82b6e2adeda1b41a57a260d68fb3879c427e`.

- **Batch 3 · [Actions run 40840742077](https://github.com/HuanHuanHuanFFF/Miner/actions/runs/40840742077)** · source `b0bfeb0eab19f4b7a6be884f06bfdb94edfce23c` · SUCCESS. Candidate `norm-cache-proof1` (`bcb81723…ca1ea7`) passed the full original proof gate; its source hash matches the frozen plan.
- Original artifact hashes **19/19** and runner manifest **18/18** match. Artifact metadata matches; ZIP bytes were unavailable for digest recomputation.
- Both request seeds passed. Each has 5 rounds × 180 workload-cells: **1,800 paired rows**, **3,600 reported ns values**, **1,800 matching checksum pairs**, no invalid timing values.
- Pinned scorer result vs shipped reference: ratio **0.9280847016842393**, lower gain **0.06529584264404953**, guard passed. This exploratory two-seed score is **not** a current-champion comparison or official promotion result.
- [Batch 3 analysis](analysis-batch3.json) · [Short acceptance receipt](analysis-batch3-acceptance.json). Batch 1/2 records remain in [analysis-batch1.json](analysis-batch1.json) and [analysis-batch2.json](analysis-batch2.json).
- The first analyzer attempt hit Windows `WinError 5` on the default temp directory; retry succeeded using the approved `.local-maintenance/r25-analysis-temp`, with analyzer source unchanged.

**Next decision:** root can use this receipt for the round closeout; preserve the analysis boundary and do not infer current champion status from the shipped-reference score.
