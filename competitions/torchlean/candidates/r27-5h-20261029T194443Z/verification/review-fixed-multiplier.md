# Fixed champion multiplier review — 2026-10-29

The R25 pinned scorer remains the only source of candidate/reference time ratios. `champion-multiplier.py` is a narrow postprocessor: it does not read benchmark rows or calculate the raw score. It binds the candidate/reference hashes, pinned scorer sources, current champion promotion/source/response/report hashes, official seed/workload/timing/cell contract, and either the direct current source or the exact official report-chain anchor.

I tightened one input boundary after reviewing the official current reports. They each contain both `prod-amd64` and `prod-arm64` runs with distinct machine identities. The postprocessor now requires the ratio input to carry a completed `benchmark_runs` list whose environment, identity, seed, state, attempt count, repetition count and round count exactly match every run in the saved current report. Missing rows or a single-environment result become `UNKNOWN_CURRENT_REPORT_ENVIRONMENT_MISMATCH`; this prevents an amd64-only/local quick ratio from being accepted by copying the report config hash. R27's quick CI route estimate remains separately labeled INFERRED and does not use this strict converter.

The current snapshot binding also fails closed unless the champion source, response, report and live config SHA-256 values are all present and valid.

For an unavailable current source, the chain conversion remains:

`candidate time / current champion time = (candidate time / available anchor time) / (current champion time / available anchor time)`

The result is still `INFERRED`; a CI pass or a multiplier below 1 does not establish candidate correctness or official promotion. The exact report input contract, source snapshot and run-environment bindings must be independently audited before this converter is given a ratio.

Changed script: `champion-multiplier.py`. No scorer code, official files, candidate source, benchmark data, or current champion bytes were changed or fetched.
