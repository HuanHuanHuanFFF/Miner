# Next diagnostic, no job requested after R26 cutoff

Use the existing public pinned TorchLean runner after official setup and within
D's authorized queue. Current batch1 does not include the fallback source.
No local Lean/native compile was attempted.

1. Copy `WordBlockRuntime.lean` into an owned temporary module under `lean/work/`.
   Directly compile with the runner's pinned `lake env lean` and retain complete
   stdout/stderr. Do not run official VerifyExact on this helper: it deliberately
   supplies no12-kernel Submission declaration. This first3287B source resolves
   basic elaboration and can emit C, without waiting for arithmetic proofs.
2. If the runtime compiles, compile `WordBlockCarrier.lean` (18821B,33746c38…)
   as a helper module. First failures should be repaired against full goal text,
   not guessed from sandbox's seven-line summary. Replay the actual helper roots
   only after it builds. `probe-plan.json` names those roots.
3. `WordBlockCostMain.lean` (8999B,3152bdda…) needs a separate executable root.
   Copy it as `work/R26WordCostMain.lean`. Make an **owned copy** of original
   lakefile and append a target named `r26WordProbe`, `srcDir := "work"`,
   `root := \`R26WordCostMain`. Build with that config under the existing isolated
   runner build layer. Original lakefile/contracts/bench/gate stay unchanged.
   Retain generated C, compiler/link traces and the executable hash. Verify
   optimization/link flags against the original target with only root/path
   mapping accounted for. Run once per retained text fixture.

The driver prints `R26_WORD_VERIFY` before44 trial rows per fixture:11 trials×
four variants, three calls per row. A missing/partial stream, shape rejection,
checksum error or build failure is not a speed result. Keep every row. The
prepared/full boundary is defined in `cost-probe-receipt.json`; output cleanup
is not fully timed, no minimum duration is calibrated, and no shipped-model
comparison is included. Treat it as mechanism screening only.

The later41343B `WordBlockStaticV2.lean` is a proof-chain draft tied to original
body+bias dotOf and zero-safe shipped fallback. It is not the first diagnostic:
resolve the smaller actual runtime/modular layer before investing in the whole
chain. Production adoption still needs exact preparation guard/getter metadata,
compiled arithmetic/zero bridge, complete12 obligations, and paired fullmodel
measurement with all preparation/fallback costs.
