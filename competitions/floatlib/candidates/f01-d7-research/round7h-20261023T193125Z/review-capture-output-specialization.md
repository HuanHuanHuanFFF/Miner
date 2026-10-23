# R11 actual output-loop capture selection

Narrow repair performed 2026-10-23, starting22:04:21UTC. Only capture-codegen.py symbol constants, `_symbol_info`, `_symbol_sort_key` and selection selftests changed. No gate, adapter, candidate, old freeze, snapshot or runtime/tool budget was edited. Applied diagnosing-bugs, TDD and verification-before-completion. Ranked alternative hypotheses were skipped because911 already supplies the exact missing symbols and the selector boundary causing their omission.

The agreed regression seam is the helper's existing `_disassemble` selection selftest, with fake nm/objdump and literal real911 names. The first test was added before the fix and failed with `RuntimeError: 911 actual output specialized loops missing`. After the fix it passes. Replaying the new test against the exact frozen fc57703d source in memory also fails at that same assertion; the baseline bytes are preserved in the JSON report for reproduction. No real Linux tool or Lean compiler ran.

The fix recognizes the strict compiler encoding `lp_competition_Fin_foldl_loop___at___00Submission_<allowed>_spec__<digits>` and the corresponding private Fin.foldl form, with an optional exact `___redArg` suffix. Boxed names remain rejected before matching. The allowed output chains are RowStream.output, DirectContinuous.output/row, and BatchLocalPacked.output/batchStep/row/group. No substring search or general compiler-name parser was added. Ordinary DirectContinuous/BatchLocalPacked core/output/row/group/packBatch helpers join the lower output priority.

Actual output specializations retain priority0, but sort ahead of the other new hot loops and all standalone output helpers. Computational redArg specializations precede their argument wrappers. The original20-symbol global cap, omission/truncation metadata and deadline behavior remain. A new strict-encoding test rejects boxed, nearby namespace/function names, non-Fin folds, extra suffixes and malformed redArg names.

The full saved911 nm inventory independently demonstrates the result:

- Old fc helper:20 matches/20 selected, missing all three actual output loops.
- New helper:23 matches; first three selected are `lp_competition_Fin_foldl_loop___at___00Submission_RowStream_output_spec__0`, `__1`, `__2`.
- With the unchanged cap,20 are selected and the omitted symbols are old scalar add, mul and nativeMul. Their omission stays visible; the cap is not enlarged.

DirectContinuous and BatchLocalPacked fixtures are supported by the existing candidate declarations/Fin.foldl call sites and the exact911 compiler encoding. Their actual generated names, machine code and runtime capture remain **UNKNOWN/NOT_RUN** until a runner produces them. The report binds both inspected candidate source hashes; no new candidate was created or compiled. Strict unknown formats remain unselected rather than being guessed from a similar name.

Three red→green checks were observed: real911 specialized-loop selection, new source-backed output/fold coverage, then a private-prefix malformed `___redArgument` suffix that the legacy fallback initially accepted. The owned Fin-output family now rejects such malformed suffixes before entering that fallback. Final `python -B competitions/floatlib/candidates/f01-d7-research/capture-codegen.py --selftest` passes10 tests, including the original process/log/snapshot failure/timeout checks. The new tests preserve20 selected and explicit budget omissions; the existing deadline test still reports42 omitted and zero captured. This validates helper behavior with fake tools, not future actual assembly or performance.

The before/after byte comparison removes only the allowed constants/functions/selftest ranges, then requires the entire remainder to be identical. It passes. All13 other top-level functions, including `_snapshot`, `_bounded_tool`, `_disassemble`, `_kill_group`, `run_gate` and stage-log parsing, are byte-identical and have identical ASTs. Global cap and timeout constants, nm/objdump argv and tool limits are therefore unchanged; the JSON contains individual function hashes and the exact baseline source.

Old helper:44249B, SHA `fc57703dfe9393c37821ed8dc15bda135eb5439665a374647b12daa5358e7f11`.

New helper:51769B, SHA `a302982683d8104211bf74d89ff22ea032159d8b94059e2ae91c63dfa1242be8`.

Root can freeze this new helper for a later opt-in discovery. Existing906/911/912 receipts and freezes retain their original identities. No new timing/fullgate/independent confirmation or formal admission result is claimed, and capture overhead remains UNKNOWN.
