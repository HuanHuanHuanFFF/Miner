# Cost discriminator for next norm runner

At2026-10-29 20:06 UTC, before investing in full reciprocal proof migration:

- If the next public12 normalization batch can reuse compiled target cheaply, record one existing official complete-call layer profile for normalized_mlp (same input identity, both b1/b8, normal/wide/sparse; one exploratory sample is enough for route selection). Separate dense vs RMS vs layernorm walltime, including stable-domain checks/preparation/fallback/output/destruction. This is a cost discriminator, not an extra champion/adoption measurement.
- For source12 `Ya7G` generated code, record machine-readable counts/call evidence for division and modulo, whether a q/r pair becomes one hardwaredivision, whether the same denominator work remains per output, and any emitted per-element boxing. Wholeunknown-license C/ASM stays runner-local; save hashes, function names and derivedcounts only.
- Norm-prep removes both first-moment accumulators only in RMS; if RMS statistics share is tiny, retain the exact small helper but do not spend the whole round proving more stats variants. Reciprocal replaces3q/r pairs in layernorm output, so layernormoutput cost fraction is the relevant ceiling. Keep UNKNOWN where emitted evidence is unavailable.

See `RECIPROCAL-ROUTE.md`, `CI-REQUEST-04.json`, `CI-REQUEST-05.json`. Dimpl does not dispatch or expand the shared queue independently.
