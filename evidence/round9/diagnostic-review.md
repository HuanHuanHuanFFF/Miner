# Round 9 phase diagnostic static review

Reviewed `scripts/research-round9-phases.py` against the actual `candidates/r7-mid361-block1/parse.rs` and round-9 workflow. This review changed no script, candidate, workflow, or Git state. Rust compilation and runtime results were not available to this reviewer at the time of review.

## Conclusion

No definite current-source compile blocker or normal-path token-check defect was found. The six named functions exist uniquely, their signatures allow the current insertion method, and removing the six inserted guards plus appended definitions exactly restores the original source. That reversible instrumentation check and Python syntax check passed locally.

The following evidence-handling issue matters if the diagnostic fails; it does not itself predict that this run will fail.

## P2: failure receipts remain PENDING and timeout output is lost

At script line 75, `phases.json` is initialized with status `PENDING`. Compiler failure at lines 80-83 or runtime/assertion failure at lines 85-89 exits without updating that receipt to failure or recording exit codes. More seriously, `subprocess.TimeoutExpired` is raised before the subsequent log write, so captured partial stdout/stderr and already printed per-file rows are not persisted to `build.log` / `runtime.log`.

Consequence: an uploaded PENDING receipt can represent work that actually ran and failed, and a timeout can erase the only per-file evidence completed before termination. Preserve the run's failure classification in the main report; do not describe such a receipt as proof that execution never began. For a later script repair, catch timeout/failure, write partial output, and save a stage-specific FAILED status with return code or timeout before re-raising. No repair or cancellation was performed by this review.

The workflow runs phase and finder diagnostics sequentially in one shell step before official screening. A phase failure therefore also prevents the finder call and later default-success screen/gate steps in that run. This is an observed control-flow consequence, not a claim that the diagnostic is contaminating the official timers.

## Interpretation limits that affect conclusions

**VERIFIED from the source call graph:** `d_plan_k` calls `d_parse`, then `d_tally`, `d_dp`, and `d_extract` sequentially. The six instrumented functions do not call one another. `emit` and `emit_pos` run at their parser's emission boundary. Thus this exact function selection does not double-count nested instrumented phases.

The guards measure each function's inclusive work, including its ordinary callees and local cleanup before guard destruction. `_r9_phase` is a named binding and is dropped at scope exit; it is not the immediately discarded `_` pattern. Relaxed atomics are adequate for this single-thread harness, and reset occurs before the one profiled parse in each repetition.

At lines 93-96, each phase and the overall instrumented time are independently summarized by their medians, then divided. Those fields are valid ratios of separately summarized observations, but are not a strictly additive partition of one execution. For example, three observations with phase triples `(6,6,0)`, `(6,0,6)`, `(0,6,6)` each total 12, but separate phase medians sum to 18. If a percentage breakdown is needed, first compute fractions and residual per raw record, then summarize those fractions while retaining the record-level totals.

These phases are also incomplete for the whole parser: routing, outer allocations/glue, other planners, and some cleanup lie outside the six functions. A zero D-phase count on a non-D route is expected. The unmeasured remainder is not automatically evidence of profiling failure or a single missing hotspot. Use files actually routed to engine D when deciding whether the backward-DP optimization target dominates runtime.

The first and third repetitions run reference then profiled; the second reverses them. The 2:1 order balance and absence of a dedicated warmup are acceptable for coarse attribution but insufficient for small speedup claims. The existing scope statement correctly warns that instrumentation can change generated code. Compare reference and instrumented totals to assess perturbation before turning a phase fraction into a CPU-saving hypothesis.

## Checks that are correctly present

- The enabled specification pins the source and includes the exact block1 entry.
- The public corpus count and total byte size are checked; per-file hashes are recorded.
- Every profiled parse is compared token-for-token with the untouched source, for 28 files times 3 repetitions.
- The process return code, total 84 rows, and every `(file_index, rep)` pair are checked before VERIFIED status.
- CPU affinity is fixed for the runtime process, and the official encoder/competition axes are explicitly outside this diagnostic's scope.

Token equality establishes that instrumentation preserved the reference's observed tokens on these files; it is not a new Lean proof or an independent decode test. These narrower checks are consistent with the stated attribution purpose.

## Pending evidence

Await actual build/runtime receipts before claiming that the diagnostic compiled, ran, preserved 84 token streams, or found a bottleneck. The main thread owns interpretation of the real finder/phase measurements and any subsequent implementation decision.
