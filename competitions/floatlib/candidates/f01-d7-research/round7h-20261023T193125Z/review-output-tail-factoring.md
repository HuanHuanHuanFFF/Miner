# Local-tail proof factoring

The new asset is **6165 B**, SHA256 `9d7bcb60b483b1b1994836c679e8b466d3cac1c17bc0532875aaf69cbdb2d486`. The old 935 tail proof2 asset was 9283 B; the standalone appended asset is 3118 B smaller. This is not net GeneralPanel capacity savings: the old tail proof family remains required. Appended to the exact ea102/244990 B diagnostic parent, the new source is **251155 B**, SHA256 `1b4722989e4352b7f6a80337d545ff0a97d2890f95ccac5788a095da30b1aaa8`, leaving 4845 B. The builder is `37b602a98cd5a3e4ffb3ce9e68697b89dfd0ace7657be1fd1e5f37f03da8166d`.

This exact source has **statementPASS939 only** (initial status was NOT_RUN). It does not change a main entry or the frozen final cohort. The candidate is `f01-d11-panel4-tail-factored-proof`; its manifest, source copy and exact inverse are complete. All parent source bytes and four specs are unchanged.

The mechanism is exact function equality rather than another output-prefix proof:

1. Reuse the exact 3154 B helper prefix from the actual 6e99/935 accepted source: prepare_read, arbitrary-10-accumulator dot10_shift, runDot_shift and runDot_prepared.
2. New group computes the local r*n dot once and finishes from the original raw (b*m+first+r)*n address. group_eq rewrites that dot to the original RowStream.group; its only additional address fact is (b*m+(first+r))/m=b for a valid tail row.
3. row_eq transports equal group callbacks through Fin.foldl. tail_eq transports equal row callbacks to the original R11WideLayout.emitTail.
4. tail_prefix rewrites by tail_eq and directly applies the existing emitTail_prefix. There is no new foldl_inv, group_prefix or row_prefix proof.

The nativeA map occurs only in equality/proof references. New runtime prepare/group/row/tail definitions have no global map. Tail preparation is outside both row and column folds and reads exactly (m-first)*n raw words; each column group computes one F10 and emits min10 valid lanes. Both input conversion and local Array lifetime remain part of any future complete call cost.

The proposed equalities use total getD reads and unconditional Packed10Index.runDot_eq, so they do not introduce a machine-size precondition. n=0/p=0 and empty row domains remain in the same function statements; arbitrary Nat dimensions follow the original machine/Nat fallback proof. The prefix wrapper requires first<=m exactly as the old theorem. These are source-level proof obligations pending Lean acceptance, not a new accepted all-dimension theorem.

The accepted helper prefix is evidence of its original statement acceptance only. The callback equalities combined with ea102 were accepted by statement939; kernel replay, axiom audit, checksum and full gate remain NOT_RUN. No actual GeneralPanel Projects/output/tail dispatcher, huge-Nat entry fallback, active caller lifetime or performance is accepted here. The full future GeneralPanel source size is UNKNOWN until Astra/Root reconcile all dependencies. Future integration replaces the old 9283 B namespace with this 6165 B namespace; appending both is invalid.

Static checks passed: exact parent/donor pins, 13 unique new Panel4Tail declarations, exact inverse to ea102, unchanged original policy/options/notices, no new Prefix fold induction, and no global map in the four new runtime definitions. Statement939 is now collected; no long full CI is requested by this asset.


## 939 exact acceptance and capacity correction

Run40051933922 / seed939 accepted exact Kernel **1b4722989e4352b7f6a80337d545ff0a97d2890f95ccac5788a095da30b1aaa8 / 251155 B** by **statement only**. Verdict SHA256 is **c7b6a78e12bbff00d8743a7f7f958fb74c4ef5ec2df02fc82b80cf7eda233432**. Original receipt directory: `ci-runs/40051933922/download-ecb6c1975dc349ffb4416b91586fba11/diagnostics/f01-d7-public-suite/public-suite/`. Its input Kernel equals the frozen local source byte for byte. The initial manifest remains NOT_RUN; no source is rewritten.

Accepted scope: the concrete local preparation helper chain, group/row/tail exact callback equalities to the old writer, and reuse of its Prefix theorem. There is no new active matrix entry. No new kernel replay, axiom audit, checksum, full gate, GeneralPanel producer/output/tail dispatcher, huge-Nat entry integration, lifecycle or performance result is accepted.

**Capacity correction:** tail_eq and tail_prefix still depend on `R11WideLayout.rowIndex`, `R11WideLayout.emitTail` and `R11WideLayout.emitTail_prefix`; the latter also keeps its original RowStream.row/row_prefix dependency chain. The old tail family budgeted as **2031 B** in the earlier pruning plan is therefore live and cannot be deleted as unused on this route. The **3118 B** reduction is the difference between the two standalone appended assets only; it is **not** a demonstrated 3118 B net reduction of a GeneralPanel combination. A plan that both credits that reduction and removes the old tail family double-counts capacity. The complete Panel producer/new flow/dependency closure still has **UNKNOWN** total size. The earlier old-tail deletion proposal is superseded for this factored route.

This experiment stops here. No new source, CI or final-cohort mutation follows this report update.
