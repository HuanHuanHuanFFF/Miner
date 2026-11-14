# B11 terminal native-build review

Review time: 2026-10-30 00:04 UTC. Parent status, the newest request, and the saved current board were reread before raw review. The B11 run is terminal: `40975355668`, workflow conclusion `failure`, source commit `6435029b784069762d61e333ccf51405c61b844f`.

## Identity and artifact integrity

- Plan SHA-256 `c5773dbb1a9cd1288515b2a933eedeb8fb5436c13cd4eda4b11ab33e415b868e`; the plan at the run commit, dispatch record, and downloaded artifact all match. The current workspace `ci-plan.json` has since moved to a different plan, so the audit binds the run to its immutable source commit rather than the current worktree file.
- Candidate `public23-band64-weightcache`, SHA-256 `4a9cb398cb45df02c977604e7968648716250af5e0a0dfa99a8068e8b00b8f9b`, 252,675 bytes. The saved public submission 23 source and the in-memory transform reproduce its exact source and candidate hashes. Runner, prepare script, helper, and owned recipe hashes match the dispatch commit.
- Repository was public and `allow_private=false`. The run summary reports setup and setup-check complete and `originals_unchanged=true`.
- Artifact 12942506756 has archive digest `sha256:6e498ab970f7c7ab7665862002f3bac693cc1eab6de045650ef85323ca9473a6`. Independent manifests pass: 20/20 outer files and 19/19 runner files, with no missing or unexpected entries.

## Failure and evidence boundary

The `calibration` reference built, and its compile/link/response flag check passed. The candidate build failed before candidate flags or measurements were produced. The candidate build log records two Lean errors in generated `work/Submission.lean`:

- line 2973:49: failed to synthesize an `HSub` instance;
- line 3055:69: type mismatch involving `Yk (bv >>> 16)`.

The runner summary is `complete=false`, elapsed 188.22 seconds, with candidate error `Ownednativebuildfailed:public23-band64-weightcache`. No candidate result entry, full gate, correct declaration, timing rows, checksums, alternating order, or paired CPU evidence exists. This is a native build failure, not a benchmark timeout.

The plan had `full_gate=false` and `declares_correct=false`, so the candidate remains **NativeOnly**. Candidate performance versus current normalized MLP #43 is **UNKNOWN**; no score or multiplier is inferred from the partial build. Submission 23 is only the report-chain anchor, and is not the current champion. No `CI-RESULTS-BATCH11.json` was present at this audit.

The independent audit is [audit-native-run-40975355668.json](audit-native-run-40975355668.json), status `PASS_ARTIFACTS_AND_CANDIDATE_BUILD_FAILURE_AUDITED_NO_TIMING`, zero audit failures. It checks only frozen run identity, artifact integrity, exact candidate reconstruction, and the recorded failure; it does not compile or score locally.
