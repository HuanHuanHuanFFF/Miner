# Quotient2 — precise repair of the real UInt64 elaboration error

Kernel **231285B / SHA256 `28d0f2436791668ca16fa4c9b40c0a3e73cf42eebed4b0123795b058aba440bb`**; fragment `5733f2e317b9ce71e3b213ad4283148ff8870276e4dd7d327874096a090fd541`. Retained B2 prefix226829B and its four public endpoints are byte-identical.

CI40779515020 on head6d98f9ae reported only the line6672 UInt64 `Preorder`/LT mismatch from generic `ne_of_gt`; original full log SHA493efe30… and original quotient1/dd1f remain unchanged. The sole repair converts the actual word inequality and the hypothetical d=0 equality to Nat, then closes their contradiction with omega. No runtime, theorem statement, guard, root name or imported library changed. `repair-receipt.json` checks reverse repair, exact runtime identity and all bindings.

The same two roots remain `Submission.R24QuotientCertificate.checker_sound` and `.rounded_toNat`. Manifest uses statement-only, timeout180 and the same exact v8 helper relative path/hash. New Lean, replay and AX are **NOT_RUN**. D alone performs Git/CI. Existing870-case finite evidence is retained through exact runtime-byte identity, not rebranded as a new formal pass.

No Binary32/RMS transport or new-track runtime is included. Next bridge selection will reuse D's cell2/power work after actual receipts, rather than duplicate it. Resumed first tool23:02:50UTC still belongs to the original R24 window20:38:56–03:38:56UTC. R/D checked the source message and corrected the apparent3.5h instruction as historical2026-10-26; no new round or budget extension. The original provisional repair receipt remains unchanged, with a separate deadline-correction receipt.
