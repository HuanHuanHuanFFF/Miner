# R2-11 — Packed4 repair from actual statement314 errors

Reserved-slot repair is ready: `competitions/floatlib/candidates/f01-r2-web-packed4-proof1/Kernel.lean`, SHA `d8003f9d90ae0f608cab87a23d8eae19bf9ac70cfce9acc80d8461ff76105281`, 72433 bytes. Parentbe7f9469, original web ZIP and original failed source are untouched. Exact upstream lexical/options policy PASS; new Lean compilation NOT_RUN. The56956-byte protected original prefix remains identical.

Only two proof edits, no executable definition changes:

- nativeA_getD now uses full `simp [zero32, Array.getD, hi]`, matching the successful transport strategy already used in full-gated preconverted-bmm. This addresses the actual Array.getInternal map goal at1397; simp only had omitted the intermediate getInternal conversion.
- Remove the no-progress `dsimp only` after the positive split in dot4_lane. The actual error at1425 aborted before the recursive proof was checked, so later goals and termination still need the real compiler.

Actual failure source: run39670733380, download-a04b3a9bd49c431bbb12b0c42ce227cb/diagnostics/f01-d2-web-packed4/replay.log. D: copy this exact frozen repair into owned scope and use the reserved statement slot; preserve the next original error output. No full performance claim or benchmark request until the full proof source compiles. R owns any subsequent new repair version; no D combo/hybrid files were changed.

The separate low-scale rounding helper from R2-10 is still only an optional bounded proof-feasibility component, not a duplicate hybrid dispatcher and not a reason to delay this Packed4 checkpoint.
