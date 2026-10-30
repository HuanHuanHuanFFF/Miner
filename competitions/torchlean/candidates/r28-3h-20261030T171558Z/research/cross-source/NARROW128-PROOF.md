# No-cache128 fallback: proof boundary

This is an isolated successor question, not a new full candidate or a CI request.
It targets only the contiguous `YaU/YS6` fallback in exact public36. Existing
prepared MD/MD2 paths, scalar GEMM and all current frozen sources remain intact.

Original `YL6` adds each signed product in one's-complement form to192 bits and
defers one unit per negative term in the separate counter c. The lower two
words and c evolve independently of the top accumulator word. Therefore a loop
that keeps only those three fields has the same low128 state after every prefix.

For finite terms admitted by the existing span63 condition, each absolute
product is strictly below2^111. With n<=65536, the exact body sum has absolute
value strictly below2^127 (n=0 is separate and trivial). Fold c into the low/high
pair with carry, then sign-extend the corrected high word into192 bits. This
recovers the same signed body that the original192-bit accumulator represents.
Bias is then added with the **original192-bit YL/YD terminal**, before one final
rounding. The final body-plus-bias need not fit signed128; moving bias into the
truncated pair would require a new bound and is not this proposal.

A low-cost implementation can call existing inline YL6 with top word0 and a
continuation that discards its top-word result. Whether the compiler removes
the top carry comparisons/or/add must be inspected in generated code; no native
saving is asserted from source shape alone.

`narrow128-fallback-model.json` checks2000 sequences plus18 old complete Mixer
outputs against saved native checksums. All153422 modeled YaU MACs here meet
the proposed bound, including64500 classifier MACs. These are operation counts,
not elapsed shares. The model compares normalized192-bit words, not merely
rounded outputs.

Two required conditions have concrete negative controls. Without the count
bound, n65538 and the recorded finite raw vectors pass source36's old span63
gate but flip the mathematical output6200007f to e1ffff02 after signed128
truncation. This shows a count bound is necessary, not that65536 is optimal.
Without c, the real dot(-1*1)+bias1 changes from+0 to negative2^-46, worda8800000.
Exact-zero/signed-zero replay remains the original callback.

The universal paper argument is separate from source-bound Lean acceptance.
The required new bridge is the actual recursive low-state invariant, metadata
mass bound, c normalization, and original terminal equality. No complete proof,
new Submission.correct, native cost, or adoption has been established.
