# Spatial source readiness supersedes the one-space fix

Pinned Lean4.34 `Parser/Term.lean` blob4e41c86c… defines function argument parsing with`checkWsBefore`; `Parser/Basic.lean` blob0e135176… checks actual trailing whitespace. The earlier own byte compaction removed spaces before/after parentheses, so8e5b27c0 and its one-bne-space derivativef59a9b41 are not valid ready sources. No actual compiler/native success was ever claimed.

Use only the new **spatial11-native-v3** recipe/hash in `spatial-parser-repair-receipt.json` for any future spatial dispatch. It starts from the preserved original spaced generator, repairs the bne token, preserves application spaces and instead shortens only fresh owned helper names. Same algorithm, guards, cache, B0−2 bias and CHW outputs. The old complete11source/proof still survives underR8K/R8P; the new entry isSubmission.rV and still has **no newcorrect**.

`build_spatial_parser_repair.py` lists exactly two pinned dependencies, including the owned original generator at its relativehistory path. Native-onlyflags remainfalse/false. Do not edit/cancel any already-running old job or queue multiple versions. The support repair00928141 is unaffected: its source never used the unsafe application-space compaction.
