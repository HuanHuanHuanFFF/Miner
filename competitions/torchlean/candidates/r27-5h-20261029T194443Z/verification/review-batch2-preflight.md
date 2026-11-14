# Batch 2 narrow preflight review

Read the 20:19 development-status and BATCH2-READY request, plus the public board at the same checkpoint. No Batch 2 CI was active at that checkpoint. This review is read-only and scoped to the requested full-gate branch and source/interface hashes.

## Identity checks: PASS

- Plan SHA-256 459f2e3ccb8a3ba256d8dbeaff97c54e66fc385ece40f127591922b9986e87ff matches BATCH2-READY; runner SHA-256 21a3fbd512eec60f9db627464d00bbc91e2158e0b5055e795f2f47a95d611a35 matches.
- Official reference is retired submission 12, source SHA e2c1f1f1ba52e32563fb193ceea7e2a271b989fd3ba2eb16cff747987879b521. It is the report-chain anchor for current normalized_mlp #24/submission 23, whose source is unavailable; current champion source hash is 1010c0744f0506974c64601e8ce7335bea56d0cb21b655543d390794df0665fe and current/chosen-anchor report ratio is 0.9575717364640264.
- Guard26 receipt matches the plan exactly: candidate SHA 5fcb3b893600993c1109de8df5849e8765c9562c2e57eeb2c9f052e21cae2b25, 218531 B, patch script hash 2fe330a77dbb7e5d28023ced2a731500cf0e496763e74955305f076b8d3dd4ac.
- Norm-prep receipt matches SHA 61b98cc582a48723c0f184e49420fe97b449731a145d47d1920d3b871e2e76aa, 222252 B.
- The adapter, RealStrict helper and WordModular64 helper file hashes match the plan. The batch2 patch scripts and loop fragments are all present.

## Full-gate branch: PASS statically, terminal result pending

For candidates with full_gate=true, the runner materializes the exact planned source, copies those exact bytes into a dedicated full-gate directory, and invokes the official pinned checkout's Python module command: python -m verification <candidate_dir> --verdict <verdict_file>. It records the original verdict, requires exit code 0, passed=true, stage=axioms and unchanged start/end verifier fingerprints before native build. A rejection triggers a separate bounded VerifyExact diagnostic log and stops that candidate's native path.

Only public12-guard26 has full_gate=true. Public12-norm-prep remains NativeOnly. The RealStrict and WordModular64 helpers are standalone elaboration and named-axiom diagnostics; they do not replace the original gate.

## Required plan metadata correction before dispatch

The plan's board and champion object say normalized_mlp/current submission 23, but human_performance_target says current mixer champion36. Also, the top-level scope says NATIVE_EXPLORATION_NO_FULL_GATE_REPLAY while guard26.full_gate is true. These labels conflict with the frozen candidate-specific fields and could misreport the result. Before dispatch, change human_performance_target to normalized_mlp/current23 and make the scope explicitly mixed: full gate for guard26, NativeOnly exploration for norm-prep. Refresh the plan hash and BATCH2-READY receipt after those edits.

The runner's native path uses quick settings and roots 27102911/27102913. The current normalized_mlp report uses root seed 3542272469, six official sub-seeds, 11 rounds x inner 3 x 50 ms and two production environments. Quick measurements are route-planning evidence only; do not convert them to an eligible current-champion score or reuse the old report hash as an exact production config.

The reference source 12 receipt is marked LOCAL_ONLY. The runner fetches it into an ephemeral public hosted runner, while the plan/workflow omit the full source from Git and artifact outputs. Source-use policy remains UNKNOWN pending the separate license review.

## Result

Static source and helper identities pass. The full-gate implementation is bound to the exact candidate and official verifier; no result exists yet. Fix the two plan labels before dispatch. After terminal collection, audit the full-gate verdict and fingerprint, then raw benchmark hashes and counts, flags, MainExact, and separate per-candidate proof status.

## Post-dispatch correction

The follow-up dispatch receipt shows batch2 was already frozen at 2026-10-29T20:20:54Z as run 40948208583 before this review completed. Both ci-plan.json and ci-plan-batch2.json are byte-identical at SHA-256 459f2e3ccb8a3ba256d8dbeaff97c54e66fc385ece40f127591922b9986e87ff, and every frozen file still matches the dispatch receipt. Do not edit or reinterpret the in-flight plan.

The two label inconsistencies remain in this frozen run: top-level scope says no full gate replay although guard26.full_gate=true, and human_performance_target names mixer36 despite board/current_champion being normalized_mlp23. The runner's per-candidate full_gate flag controls execution; post-run review must read full_gates[public12-guard26] and each candidate proof_state separately. Use the normalized_mlp #23 report-chain estimate only for that board. Correct those labels in any later batch before dispatch.

## Batch 2 dispatch identity and gate branch

The post-review dispatch receipt confirms run 40948208583 is in progress on source commit bfee42632fd7622375292e98318f5ea16284c3fe. ci-plan.json and ci-plan-batch2.json are byte-identical at SHA-256 459f2e3ccb8a3ba256d8dbeaff97c54e66fc385ece40f127591922b9986e87ff; the dispatch receipt's entire frozen_files list matches current workspace bytes.

The runner's per-candidate guard26 branch passes the exact materialized candidate path to the official pinned Python verifier, saves the full verdict, and requires passed=true, stage=axioms and equal verifier start/end fingerprints. On failure it saves the official VerifyExact raw diagnostic and aborts that candidate's native path. The norm-prep variant has full_gate=false, so it remains NativeOnly. The runner's global scope string and plan scope are stale and should not be treated as a result; use the per-candidate full_gates and proof_state fields.

No candidate measurement can be called a direct comparison to current normalized_mlp #23: its source is unavailable. A quick candidate/#12 run may only be an INFERRED route-planning ratio using the fresh #23/#12 report factor 0.9575717364640264. Standard report settings and the full gate remain necessary before adoption.

At the 20:27 checkpoint I independently re-hashed all 11 files in dispatch-20261029T202051Z/dispatch.json; none differ from its frozen list. The run is still in progress.

The owned guard26 transformation is bounded by exact source SHA and asserts each intended replacement is unique. It widens the shifted-remainder guard 8→26, updates the quotient-bound proof, and leaves the final rounding/entry structure for the original full gate to verify. The generator explicitly labels its receipt GENERATED_NOT_COMPILED_NOT_GATE_PASSED; no semantic acceptance is claimed before the official verifier verdict.

The two requested helper interfaces are present under the frozen hashes: RealStrict has all five named roots, WordBlockModular64 has all three named roots. A bounded scan found no sorry/admit/axiom/unsafe markers. This is source-level interface presence only; elaboration and printed-axiom logs remain pending terminal results.
