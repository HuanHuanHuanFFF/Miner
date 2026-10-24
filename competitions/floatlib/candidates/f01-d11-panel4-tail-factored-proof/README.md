# Factored local-tail statement diagnostic

Parent is exact `ea10235659e5c3eef3ed1bd0e32920a0f479dd04d4188d22083e0ab8aee1a1d7` / 244990 B, accepted by statement925. The full parent prefix and original four entry/spec bodies remain byte-identical. Removing the appended 6165 B asset recovers that parent exactly.

The first 3154 B of the asset are copied verbatim from the tail proof2 helper prefix in 6e99, accepted by statement935: prepare/read, arbitrary-accumulator dot10 shift and runDot_prepared. This diagnostic appends new runtime group/row/tail helpers and exact function equalities to the original RowStream.group/row and R11WideLayout.emitTail. The final Prefix theorem directly reuses emitTail_prefix. No new Prefix fold induction is duplicated.

Runtime prepares only (m-first)*n local words once before tail rows/groups. Numeric base r*n and raw NaN-finish base (b*m+first+r)*n remain separate. Each column group computes one F10 before emitting valid lanes. No new runtime helper executes a global nativeA map. The map in equality statements is a proof reference.

New Kernel is `1b4722989e4352b7f6a80337d545ff0a97d2890f95ccac5788a095da30b1aaa8` / 251155 B. The asset is `9d7bcb60b483b1b1994836c679e8b466d3cac1c17bc0532875aaf69cbdb2d486` / 6165 B, saving 3118 B relative to the old 9283 B full-tail asset. A future integration must replace that namespace, not append both duplicate namespaces. The total concrete GeneralPanel source still needs a separate dependency/capacity audit.

All new statement, kernel replay, axiom audit, checksum and full gate checks are **NOT_RUN**. There is no active Panel/Tail entry or performance claim. Root owns any short statement run. No old source, donor, final cohort, Git or CI files are changed.

`python build.py --verify` checks exact pins, inverse, namespace/declaration uniqueness, the original policy, absence of runtime global map and absence of new Prefix fold induction. It does not compile Lean. Default is dry run; `--write` refuses existing outputs.
