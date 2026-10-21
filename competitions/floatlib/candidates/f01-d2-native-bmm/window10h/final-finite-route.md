# D proposal: one final finite guard per ordered reduction

Observed gap: scalar guarded native calls still perform conversion and finite/raw checks every multiply/add. Current native sum is about4--6ns per element; champion stored sum is0.7--1.1ns and bmm0.2ns per multiply-add. Cross-run absolute figures are diagnostic only; champion CPU/source unknown.

Hypothesis: run the exact sequential Float32 multiply then add loop without per-step guards. Convert the final result back only if it is finite; otherwise recompute the original exact dot product. No FMA or reassociation. This changes the placement of validity checks, not numerical order.

Key proof route is backward, not an a priori bound on every intermediate:

1. `(a+b).isFinite=true` implies `a.isFinite=true` and `b.isFinite=true`. IEEE infinity/NaN cannot turn into a finite value under addition.
2. `(a*b).isFinite=true` implies both inputs finite. Infinity times zero yields NaN, not finite; any NaN operand remains nonfinite.
3. For the pure native dot loop, induct on remaining length to prove: finite final result implies finite initial accumulator AND exact equality with the ExecFloat ordered fold from ofFloat32(initial accumulator). The induction hypothesis gives finiteness of the next accumulator; (1) yields finite current accumulator/product; (2) yields finite converted A/B; `finiteRoundtrip` restores original binary32 operands, existing finite add/mul bridges close equality.
4. At n=0, the final result equals the initial accumulator. Starting at +0 proves the production fast path. A nonfinite final output always uses the existing exact fallback, preserving NaN payload/sign and overflow behavior.

This avoids having to prove all-native arithmetic equality for NaN/Inf results; only the finite-result preimage lemmas are needed. They must be checked against the actual Lean4.34 Float32 model, and the exact full candidate must pass policy/replay/axioms/checksums and full timing.

Request to R at next checkpoint: prioritize evaluating/proving these two finite-result preimage lemmas after current finiteRoundtrip compilation feedback. Return exact source and minimal compile request. D will implement the pure native loop after the key bridge is viable. Current guarded native-bmm remains the independent control.
