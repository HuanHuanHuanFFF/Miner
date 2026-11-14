# Packed-support only: replace the unqueued v1 with v2

Pinned Lean runtime source inspection exposed an actual odd-cout boundary issue before any native run: v1 prepared `b[o+1]!` and `BW[o+1]!` even when that second output did not exist. The result was unused, but the extra out-of-bounds native lookup is unjustified. This is a static boundary finding, not an observed benchmark failure.

Use **v2 a498d9b70f9892a671943c6a726c36e2e745baae33fb986b899012ccf3f8b6c2 /252237B** if the conditional support native experiment is chosen. `build_packed_support.py` now accepts `variant="packed-support11-v2"`; own runtime and compactor hashes are in `packed-support11-v2-receipt.json`. It maps the unused second channel to `o` for these two reads. New actual second channels still use `o+1`; all source guards, arithmetic, cache and output logic are unchanged.

v1 full source remains private; exact own recipe/runtime/compactor/receipt and finite models are retained under `history/packed-v1/`. Do not schedule both versions. This is one implementation correction to the same mechanism, not another candidate family or independent trial. If any already-started v1 job exists, do not cancel it; retain its result with this boundary note.

Mandatory experiment labeling: `declares_correct=false`, `full_gate=false`, `proof_state=NOT_PROVED_NATIVE_ONLY`. The new kernels have no correctness theorem. First ResNet zero candidate remains **c6a4da97/252334B unchanged** and still has the existing full-obligation claim awaiting exact gate. No confirmation data was read to make this fix.
