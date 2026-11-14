# Exact batch2 failure and v2 repair — 20:36 UTC

Run40948208583/source bfee4263 tested guard26 SHA5fcb3b89…/218531B. Original gate passed intake/policy and failed statement: first failure is `Submission.lean:2119:8`, exactly the added `nlinarith` line. The200000 heartbeat budget was exhausted; subsequent errors and unknown Ya7Ge are cascading. Raw log remains at `../../evidence/40948208583/download-12f49c520f4a40649df4b418915e9e2b/public12-guard26/full-gate-raw-statement.log`, SHA256 `276e4839409802f4b40eebd8599494480e6e6d651af471d5a96dded04913ee31`. Verdict stage statement=false; no native candidate measurement occurred.

The v2 proof replaces unbounded-context nonlinear search with the already available chain:
`ht : remainder*2^ks < D*2^ks`, `hu : D*2^ks <= D*2^26`, then `Nat.mul_comm D (2^26)`. It does not increase resource limits or change runtime code.

Reconstruct using standalone owned `patch_norm_guard_v2.py` (SHA256 `9fa6e555df8af97cb942b779bf7b9888fea662b4553914590f68ae5289cf0ad6`), same exact source12. Candidate is218583B / `dced7848655a50a136750c1837b46f084a25ec26d13df72fe907d4a162bf1cb9`; receipt `norm-guard26-v2-receipt.json`. It remains UNCOMPILED, not gate accepted. Old script/source/receipt and raw failure are preserved unchanged. Request original full gate again on this exact version, then actual complete normalized_mlp cost if accepted.
