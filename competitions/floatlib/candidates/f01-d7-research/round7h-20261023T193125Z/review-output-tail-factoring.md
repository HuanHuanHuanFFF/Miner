# Local-tail proof factoring

The new asset is **6165 B**, SHA256 `9d7bcb60b483b1b1994836c679e8b466d3cac1c17bc0532875aaf69cbdb2d486`. The old 935 tail proof2 asset was 9283 B; this removes 3118 B of source. Appended to the exact ea102/244990 B diagnostic parent, the new source is **251155 B**, SHA256 `1b4722989e4352b7f6a80337d545ff0a97d2890f95ccac5788a095da30b1aaa8`, leaving 4845 B. The builder is `37b602a98cd5a3e4ffb3ce9e68697b89dfd0ace7657be1fd1e5f37f03da8166d`.

This is a complete proposed statement asset, **Lean NOT_RUN**. It does not change a main entry or the frozen final cohort. The candidate is `f01-d11-panel4-tail-factored-proof`; its manifest, source copy and exact inverse are complete. All parent source bytes and four specs are unchanged.

The mechanism is exact function equality rather than another output-prefix proof:

1. Reuse the exact 3154 B helper prefix from the actual 6e99/935 accepted source: prepare_read, arbitrary-10-accumulator dot10_shift, runDot_shift and runDot_prepared.
2. New group computes the local r*n dot once and finishes from the original raw (b*m+first+r)*n address. group_eq rewrites that dot to the original RowStream.group; its only additional address fact is (b*m+(first+r))/m=b for a valid tail row.
3. row_eq transports equal group callbacks through Fin.foldl. tail_eq transports equal row callbacks to the original R11WideLayout.emitTail.
4. tail_prefix rewrites by tail_eq and directly applies the existing emitTail_prefix. There is no new foldl_inv, group_prefix or row_prefix proof.

The nativeA map occurs only in equality/proof references. New runtime prepare/group/row/tail definitions have no global map. Tail preparation is outside both row and column folds and reads exactly (m-first)*n raw words; each column group computes one F10 and emits min10 valid lanes. Both input conversion and local Array lifetime remain part of any future complete call cost.

The proposed equalities use total getD reads and unconditional Packed10Index.runDot_eq, so they do not introduce a machine-size precondition. n=0/p=0 and empty row domains remain in the same function statements; arbitrary Nat dimensions follow the original machine/Nat fallback proof. The prefix wrapper requires first<=m exactly as the old theorem. These are source-level proof obligations pending Lean acceptance, not a new accepted all-dimension theorem.

The accepted helper prefix is evidence of its original statement acceptance only. All new callback equalities, their combination with the ea102 parent, kernel replay, axiom audit, checksum and full gate remain NOT_RUN. No actual GeneralPanel Projects/output/tail dispatcher, huge-Nat entry fallback, active caller lifetime or performance is accepted here. The full future GeneralPanel source size is UNKNOWN until Astra/Root reconcile all dependencies. Future integration replaces the old 9283 B namespace with this 6165 B namespace; appending both is invalid.

Static checks passed: exact parent/donor pins, 13 unique new Panel4Tail declarations, exact inverse to ea102, unchanged original policy/options/notices, no new Prefix fold induction, and no global map in the four new runtime definitions. A short statement run is the next falsifiable check; no long full CI is requested by this asset.
