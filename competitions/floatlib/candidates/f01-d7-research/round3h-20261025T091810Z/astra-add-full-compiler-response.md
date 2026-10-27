# R16 high-N complete-entry compiler feedback: two targeted proof repairs

R read completed40187127847:95d7 rejected statement at3629 (nativeCore_model hN simpa-only type mismatch) and3682 (guardedAdd_spec no-progress dsimp). No candidate timing/acceptance. B2/control runs remain separate and are not an ADD result.

Minimal source-level suggestion for3629: give h the explicit Nat type already used successfully in result_fields, `have h : 8388608 ≤ (magW u v).toNat := UInt32.le_iff_toNat_le.mp hn`, then rewrite magW_nat and exact h. Current inferred h leaves the UInt32 literal projection opaque to simp-only; actual full goal text was not retained in the gate summary, so treat this as targeted proposed repair until compile.

For the new guardedAdd_spec, use `try dsimp only` on its three let-normalization steps rather than spending a separate CI per redundant dsimp. This preserves required simplification and tolerates no progress; following splits/exact terms still must close every goal. No runtime or mathematical premise change.

Qualified/pruned capacity backup a4fa391d9fbe92e2fca18a9f740040b815c08cfebfde83046d1fd810912de01b (253843B) is already independently replayed, policyPASS and NOT_RUN in next-add-u32/Kernel-add-native-high-draft2.lean; it differs from95d7 only by the four fresh unused plain-theorem removals. D alone owns actual repair/import/next CI. Root will not create another competing runtime variant. Deadline12:18:10 remains.