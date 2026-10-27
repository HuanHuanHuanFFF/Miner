# ADD UInt32 follow-on handoff — 10:36 deadline

**Decision: worth one small proof probe; no complete ADD candidate yet.** This is R14's old native-conversion idea, not the software-RSE ADD that measured1.56213. No native aligned-ADD timing was found in the checked old records/candidate sources. No active40183711165 data was read.

- Legal interface: B2 full-gated `R2W01c.uint32_model_eq_roundDyadic` covers every UInt32. New59-line/2934B fragment transports it to actual `toBits` and field projections; no opaque Float64/Int64 bridge or new axiom.
- Minimal probe **41241a33… /253667B** appends that fragment plus3198B low-h normalization to exact c972 statement-PASS parent; original public runtime stays unchanged. Full SHA and append identities: `probe-manifest.json`. **NOT_COMPILED**. Explicit helper audit is required because old public specs do not use appended helpers.
- Correct fast domain: both inputs normal, gap<=7; exact unsigned magnitude N<=2164260735; determine actual sign after magnitude comparison; N=0 must return+0 *before* conversion/postguard. For N>0, require full E=em+emin−150 in1..254 before masking. Counterexamples for missing zero branch, subnormal cancellation, gap8 wrap and overflow are preserved.
- Finite model:12828 pairs,11064 initial-guard,10610 accepted,0 mismatch;32256 coverage pairs on completed R15 B2 draws. Actual ADD whole share36.40–36.86%; no eligible-subset timing inferred.
- Full proposed coverage: ML91.65–97.85%, paired60.40–87.45%, dense32.29–56.12%. If low-h checking stalls, **one** N>=2^23 fallback simplification retains ML77.05–81.88%, paired30.76–66.06%, dense27.34–48.57%. Loss is only opposite-sign gap0/1, including zero. `high-only-coverage.json` reuses existing counts; no guard grid.

`decision.md` has exact quantifiers, source ownership, failures, cost limits and remaining public ADD obligations. `manifest.json` binds original files; `screen.json` has models and old measured class costs kept separate. No Git/CI/local Lean/nested agent; tokens UNKNOWN. Current c972 performance remains UNKNOWN to this investigation.
