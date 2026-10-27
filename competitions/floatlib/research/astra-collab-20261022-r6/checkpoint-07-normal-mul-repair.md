# R6 normal-mul repair, 2026-10-22 14:03 UTC

Read D r6-feedback-06 and actual705 full-build-output. The only concrete pre-build-failed errors are Binary32/ExecFloat names in the new namespace; leading_eq/roundP_eq/core_eq have no reported error, but the failed full file is not an accepted proof artifact.

**f01-r6-normal-mul-proof1**, SHA96865cbae7141a4d5df5fe40b0e860e65402e829a3288da38ed6b403845edba8,143688bytes, NOT_RUN. Sole edit adds `open FloatLib.Floats Competition` inside R6NormalMul. Originalf6acc4bc and full failure retained. No runtime expressions, proof bodies or assumptions changed. repair-normal-mul.py reproduces it.

D's706 includes normal-add-proof1 and web-lowguards; R waits those actualresults. Active-bias5dc09645 (checkpoint06) and repaired normal-mul are available for D's bounded scheduling choice. New-suite cases and final whole-entry confirmation take precedence over filling the old-class candidate queue.

NaN fallback route: an immediate low-risk implementation shape, once the missing arithmetic lemma is accepted, is to guard each old fallback fold step before reading/multiplying: if accumulator is quiet NaN, return it; else execute exactly the old mul-then-add. Pointwise equality for arbitrary accumulator would avoid a new fold invariant, because the guard excludes signaling accumulator. This still iterates the tail but skips its memory reads and arithmetic. A true early-exit recursive loop would be a second implementation, with an extra loop-equivalence proof and separate timing. Current status is mathematical route/proof gap, not implemented or accepted.

Neither shortcut applies unchanged to sum: a later raw signaling NaN must be selected and quieted, preserving that later sign/payload. FMA is also distinct from separate mul-then-add because its ternary NaN selection sees the original signaling operands.
