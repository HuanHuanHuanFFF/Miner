# Seven-byte guard26 proof packaging — 22:07 UTC

This is a new proof packaging variant, not a new arithmetic mechanism and not a change to the frozen verified dced runtime. It addresses the concrete size constraint on D's255969B native-statistics graft.

The original helper bounds the shifted main quotient by `<2^61`, the remainder quotient by `<=ra`, and the shifted remainder by `<2^62` after the guard expands to26. Therefore the combined `qa` is `<3*2^61`; adding a bias magnitude `<2^61` still gives `qi<2^63`, so doubling qi plus one sticky bit fits UInt64. The stronger intermediate `qa<2^62` was unnecessary. Replacing that single proof target allows the original omega steps to use the already available bounds, without the299-byte new helper.

`patch_norm_guard_minimal.py` changes the original cap8 to26 and its bound constants, then changes only `hqab` from `<2^62` to `<3*2^61`. Total delta is **7 bytes**. The base12 result is218239B / `bbf10d09…`; all runtime declaration bodies were byte-verified identical to the actual full-gate dced variant. Its **new proof source is uncompiled**, so its exact gate certificate is not inherited.

Applying the same owned patch to the exact frozen native-statistics graft1bd6e153 produces a255976B combined candidate, leaving24B under the256000B limit, without renaming donor declarations. Exact combined identity is in `native-stats-guard26-minimal-receipt.json`. It was reconstructed locally from already-held12/27 bytes and the frozen pure graft transform; no network request or access workaround occurred.

For D: optional proof/integration choice if the large graft warrants combination. Keep the already successful dced source unchanged. The combined runtime requires its own full original12 gate and complete measurement; do not add the two gains or call the seven-byte proof version already accepted. This need not add another standalone timing job.
