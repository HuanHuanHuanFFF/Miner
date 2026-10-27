# R2-08 — all three first-wave web6 Pro packages delivered and reviewed

All originals are in E:/Download as requested. Separate Markdown downloads match the report bytes inside their ZIPs. Raw archives/reports remain unchanged. Receipts, exact extracts and independent reviews are in this research directory's web/R2-W01, web/R2-W02 and web/R2-W03; first-wave-report-downloads.json records the standalone reports.

| Route | Original ZIP | ZIP SHA-256 | Internal hashes |
|---|---|---|---:|
| W01 ordered-sum mathematics | E:/Download/FloatLib_R2-W01_research.zip | 4b3a37e8a0f55532dde53d062144c71b5acb8cf9001f9a49f1d1f087d9b4180f | 27 PASS |
| W02 four-output B packing | E:/Download/FloatLib_R2-W02_Packed4.zip | feafa24205fbd7f4a8eb6f79c2e6a8fbfd8650e6285964b341c7ec3d9b306ce7 | 24 PASS |
| W03 numeric native conversion | E:/Download/FloatLib-R2-W03.zip | 8f95ae0e11a52e606bca05bf1cf005c238a73122a535fb2f39cff806dddfe1ea | 23 PASS |

W01: retain the mathematical two-parity transition composition and prefix min/max certificates. Its positive odd-significand counterexample is independently reproduced: ordered [41000001,3f800003,3f800003] gives41200001; reordering or one final rounding gives41200002. Even the ReLU value domain cannot justify ordinary reassociation. The report's best fixed-anchor scalar C route is2.279x native-loop time across five rounds, so PARK that current implementation. C timings lack target Lean representation and are external diagnostic negatives, not an impossibility result. No Lean component compiled in that web run.

W02: retain A preconversion plus B `F4` objects in [batch][columnBlock][k] order, with four independent accumulator parameters and one terminal result object. This can share A/B object loads and pack four Float32 fields per B object. Its exact-integer finite layout diagnostic was independently rerun unchanged in a separate review directory:720 shapes,4860 outputs,10000 arbitrary-precision index checks match all original non-environment fields. Signed zero/subnormals are included; NaN payload/infinity behavior remains outside that diagnostic. The supplied4500-byte bmm draft lacks bmm_spec and the other scalar/sum obligations; it is not an accepted full package. Do not run its bench instructions as though they establish gate acceptance. Projection/ordered-fold lemmas are useful uncompiled starting points; packing and builder proof are open.

One important representation clarification from pinned runtime: on64-bit Lean, boxed UInt32 uses tagged immediates; preconverting it to Array Float32 introduces actual Float32 heap objects. B `F4` reduces those element objects but its Array still stores object pointers, not a globally contiguous float buffer. Inspect actual codegen and complete preparation/RC cost before claiming allocation or vectorization wins. This reinforces the controlled comparison among R2-04 Array Float32, R2-05 checked FloatArray, and a later Packed4 package.

W03 review and limitations are already recorded in R2-06. Its numeric decoder still lacks a compiled total conversion theorem; it remains a promising way to remove the sum loop's external per-input bit-conversion call, not a completed optimization.

Three focused follow-ups are now actually running, with original prompt hashes in research-status.json: W01b proves/tests a unified zero+normal table admission (two unsigned comparisons true on both domains, avoiding the explicit random-zero branch); W02b receives the exact public, full-gate-passed parent86312a37 and targets complete Packed4 bmm_spec; W03b targets the full signed-table conversion equality. Only public/self-contained material is sent. R keeps processing actual local/CI evidence while they run. Existing layouts are not expanded before the current four-way statement batch reports.

No new formal submission, wallet action, toolchain installation or D-owned edit occurs in this handoff. Candidate adoption still requires a new exact complete file, official gate and full-call timing; surrogate results and multiple reports agreeing do not replace these.
