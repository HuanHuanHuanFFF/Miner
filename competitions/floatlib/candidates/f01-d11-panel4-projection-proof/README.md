# Panel4 projection statement diagnostic

Frozen parent is exact `9a40118eae28c92c1abeca7f6a141fb0fbfe963cbf40321681b8013782f9f7ac` / 229218 B. Only 6048 B of unused definitions and proof assets are appended. All original runtime definitions, four entry/spec declarations, options, and author notices remain byte-identical. Removing the appended suffix recovers exact 9a; `exact-inverse.json` also records the sole proof simplification relative to the pinned Astra donors.

This tests the actual `Vector Panel4.F4 n` loop rather than reusing the old Array-Float32 projection theorem. `packA_read` closes the read premise from real `packA`; `wordLoop_row` quantifies all forty starting accumulators and preserves each original multiply then add. `runDot_row` connects zero-start `Panel4.runDot` to `Packed10Index.runDot`, and `block_row` connects the actual per-column helper. The global A map appears only in theorem statements/proofs, with no additional executable global map or row array on the Panel loop.

The two original NOT_RUN source assets were authored by Astra and remain unchanged. The required `projectRow` definition is explicitly included. Only `block_row` proof syntax is normalized to a single `simp only`, avoiding an unnecessary standalone `dsimp`; no numerical definition changes.

All new Lean statement, kernel replay, axiom audit, checksum and full gate checks are **NOT_RUN** at creation. This is **STATEMENT_DIAGNOSTIC** only. There is no active Panel BMM entry, concrete `Projects` instance, output/tail/huge-Nat dispatch integration, lifetime acceptance or new algorithm performance result. Root owns any CI run.

`python build.py --verify` performs lightweight source, exact inverse, declaration uniqueness and pinned original policy checks without Lean. The default command is a dry run; `--write` refuses existing output files.
