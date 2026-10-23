# R11 cohort binding review

Read-only review, 2026-10-23 21:46:52–21:57:29 UTC. No candidate, runtime tool, historical receipt, Git, CI, or future input was changed/read. This review identifies evidence-binding gaps; it does not establish a wrong adoption or any new gate/performance result.

The final primary-source and statistical checks are substantially stronger than the cohort execution-file binding. Before freezing a final cohort, bind the actual runtime files in every D/A/B commit, rather than only the current local helper files. Keep the unchanged D7 adapter.

## Definite gaps requiring a small R11 patch

1. **Runtime/workflow versions are outside the cohort contract.** `freeze-cohort.py:57–58` lists local round/audit files and sources, but omits the outer helper, workflow and runner chain. `verify-three-groups.py:74–75` requires only six local files; additional supplied files are checked, but these execution files need not be supplied. `adoption-guard.py:132–161` checks the run HEAD tree's plan, adapter and primary Kernels, not the outer helper or workflow. Adding local hashes alone therefore would not prove that all three runs executed the frozen harness.

   This evidence is **not absent from the dispatch layer**: `f01-mul-log2-proof1/ci.py:64–80` already reads/checks and records workflow, pins, CI scripts, outer helper, wrapper and candidate files against each dispatch commit. The missing link is that the final cohort verifier does not require those recorded versions to equal one frozen execution set across D/A/B.

2. **A script executed during adoption is not frozen.** `adopt-three-confirmed.py:202` loads `scripts/render_dashboard.py`; the explicit checks near line208 and the cohort list omit it. The renderer is downstream of statistical admission, but it can change the resulting dashboard/state presentation. Include it in the required local audit files and check before writes.

Minimal execution-file set: `.github/workflows/deflate-baseline.yml`; `competitions/floatlib/pins.json`; `scripts/{ci-prepare.sh,ci-setup.sh,ci-validate.sh,run-gates.py}` under that track; `candidates/f01-word-tensors/ci-diagnostics.py`; `candidates/f01-d7-public-suite/{Kernel.lean,manifest.json}`. Freeze the local dispatch `candidates/f01-mul-log2-proof1/ci.py` separately as a coordinator tool. Preserve the already-frozen D7 adapter and all existing primary source bindings. If extra controls are included in the frozen measurement orders, bind their exact sources/manifests too.

Use a single explicit R11 `execution_files` mapping, require every fixed key, and compare its hashes to `guard.read_tree_blob(root, packet['evidence']['source_commit'], path)` for each of D/A/B. The clean D commit provides the execution baseline; current working execution files must match before creating the cohort. Keep local verifier/display-tool hashes separate: those tools can be finalized after D but before the two held-out groups. Do not require new local audit files to exist in historical D commits. This can stay at the R11 layer, preserving historical811 loader behavior and avoiding a D7 adapter change.

## Protections confirmed

- `freeze-cohort.py:35–36` requires a DISCOVERY packet without codegen/profile; `adoption-guard.validate_packets:62–64` rejects capture flags, actual codegen metadata and profiling for the final D+A/D+B checks. Failed/UNKNOWN capture still has its flag and is rejected. A captured discovery cannot serve as clean D. The fixed outer8eb diagnostic collector still runs; “clean” refers to the nested candidate observers, not absence of all outer diagnostics.
- Primary Kernel and baseline bytes are checked against the actual run HEAD tree, indexed copied input and frozen/current sources. D7 `public-suite.py` remains exact `86084d93c52022f4f4a5cfb7969e2b4a035b9a4a4f1f8c6c7e74bd412eafca24`.
- The final verifier independently runs the existing guard for D+A and D+B, requires three distinct runs/jobs/seeds and exact candidate/baseline, fixed policy, 25 paired positive rounds, headline ratio ≤0.97 and gain p05 >0. It compares actual drawn case shape/work and generation vectors, not only hashes. A/B plans bind the external cohort digest, role, order and prior D. Adoption reruns verification and rejects diagnostic-only receipts/cohorts. These are local selection checks, not formal competition admission.

## Small read-only falsification replays

Used the existing `test_verify_three_groups.py` freeze fixture in memory, mocking only the digest reader. Actual `verify_freeze` accepted a schema-complete fixture omitting outer/workflow/renderer, and never read those paths even when the mock would return changed bytes. This proves the missing required-file check; it does not forge or validate a real gate packet. Separately, actual guard validation rejected D capture flags and D codegen metadata with `Observer must be disabled`. No files/Git/CI were used by these replays.

## Nonblocking display issue

`audit-suites.py` retains codegen metadata, while the adopter aggregates all exact-source full-gate rows for public ranges/estimates and its serialized `all_source_samples` loses that observer label. A captured historical discovery can therefore enter an INFERRED display range even though it cannot enter the three-group admission. Preserve observer/role labels and distinguish clean confirmation summaries. Do not discard raw or slow rows. Filtering only in the adopter would also conflict with the estimator's deliberate all-eligible-source requirement; any estimate partition needs an explicit policy. This is not evidence of incorrect final D/A/B statistical acceptance.

## Minimum patch/check order for Root

1. Add the fixed execution mapping, workflow identity and required local renderer; reject missing keys. No official gate or D7 adapter edit.
2. At cohort creation/preparation and final verification, compare D/A/B actual HEAD blobs to that mapping. Require the current outer hash `519a1898fd95b4c2482ab8ff5fbbfe1fd131e47a02f10706ec02dad3bb165904` for this new cohort only. Freeze the actual workflow hash `c0925ea63a1cce2172c38e11dda1962c9a725c0da64b15965f2abbd725c81b13`.
3. Add targeted regressions: omitted runtime key; local hashes match but one run HEAD runtime blob differs; renderer changed before adoption; explicit workflow mismatch; observer UNKNOWN/failed still rejected; unchanged historical811 control remains readable. Mock only the tree-read seam for mismatch cases.
4. Run the existing 21-test `test_verify_three_groups.py`, 17-test `test_adopt_three_confirmed.py`, and 16-test `tests/test_adoption_guard.py`. The latter uses actual historical811 and Git tree reads, so it was not run under this review's no-Git scope. The existing 10-test `test_outer_diagnostic_capture.py` can confirm the fixed outer boundary; its earlier PASS is not a new test run here.

## Immutable912 and boundary

912 is `STATEMENT_DIAGNOSTIC`, with three `statement-only` candidates. It cannot be clean full D. Its original freeze, supplemental outer-helper receipt and plan were rehashed unchanged at final review. Dispatch evidence identifies run40029166371, commit669e1e437b1592192de45adb8899ed2a33b4ee03, workflow `deflate-baseline.yml` and outer519a. Preserve the original freeze and supplement; do not retrofit a new cohort into them.

No `cohort-freeze.json` existed at the observed checkpoint. All recommended runtime/schema fixes and their new tests are NOT_RUN/NOT_IMPLEMENTED by this review. Hosted runtime behavior, final new cohort validation and final source performance remain UNKNOWN. Exact inspected source/receipt hashes and the replay outputs are in the sibling JSON.
