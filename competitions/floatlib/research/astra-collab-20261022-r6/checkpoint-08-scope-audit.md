# R6 preferred exact web-integrated sources, 2026-10-22 14:06 UTC

After the actual705 missing-open failure, R audited every global web-proof splice. Closing/reopening Submission also drops its local `open FloatLib.Floats Competition`; this would affect later public Binary32 declarations. Two proactive corrections are now isolated under new names, with runtime expressions/proof bodies unchanged. Original drafts preserved.

- **Use f01-r6-active-bias-proof1**, SHA998747fae00514a8ac872d285ab05196d094e8e15264d268028ddb9b463d7906,180293bytes, in place of5dc09645.
- **Use f01-r6-web-absorption26-proof1**, SHAdcfe0c8e26866cf281d53bdbbcdb7df5e2ddc1244a9a2b4dfe0317f80f6996ed,161973bytes, in place of5c111672.

Both NOT_RUN; this is a source-scope audit, not fresh Lean acceptance. The full original and corrected paths remain recorded; builders are separate so no frozen source is silently overwritten. For normal-mul, checkpoint07's96865cba already contains the analogous fix. normal-add-proof1 and lowguards do not close/reopen Submission and are unaffected by this audit.

No new mechanism started. Final remaining R work is W03 original recovery/review and actual CI receipt reconciliation. Research freeze14:15 remains unchanged; D chooses which precise candidates fit the final validation budget.
