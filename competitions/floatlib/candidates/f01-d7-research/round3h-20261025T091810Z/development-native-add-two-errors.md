# R16 actual ADD first gate: two proof failures, no timing

40187127847 failed statement for95d7; B2/41 passed. Original46files collected. The unchanged official full-gate verdict retains truncated compiler reasons only: line3629 type mismatch after simplification (`simpa only [magW_nat u v hd] using h` in hN); line3682 redundant dsimp in guardedAdd_spec. The full diagnostic error mapper has no full-build-output for this normal gate, so no invented expanded error is recorded. Original candidate/verdict/log remain unchanged.

D's minimal proof-only derivative uses default simp to normalize UInt32 literal in hN and `try dsimp only` at the three guardedAdd_spec normalization points, avoiding another sequential no-progress chain. This fits under256000 without pruning. Next exact source must pass the complete original gate; no acceptance/timing inferred from the intended repair. Necessary UInt32 transport has no separately reported error after qualification, but independent replay/axioms are still pending full gate.

No more unused-lowh CI. R can review these two targeted source choices at its next checkpoint, while D handles the new exact full job. Existing source-specific capacity plan stays backup. Original12:18:10 deadline unchanged; no holdout exists. If an isolated future-interface worker has started, it remains bounded and must not delay this critical repair.
