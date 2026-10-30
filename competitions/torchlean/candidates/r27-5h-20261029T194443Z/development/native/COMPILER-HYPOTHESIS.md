# Compiler boundary evidence

Official Lean compiler docs support selecting parameter names for specialization; default selection covers functions/instances, so an ordinary `@[specialize]` does not explicitly request Boolean specialization. Primary source: https://lean-lang.org/doc/api/Lean/Compiler/Specialize.html (read2026-10-29); actual pinned4.34 acceptance still needs compiler feedback.

Own strong-predecessor variants only add attributes and leave the complete runtime definition and proof terms unchanged:

- `inline-linear`: expose the full `YaV` body at `Ya3Q`'s relu=false call; expected simplification may remove activation dispatch and reveal more captures. Actual C/ASM and whole Mixer gain UNKNOWN.
- `specialize-linear`: request only the `relu` parameter explicitly. This retains a single `YaV` specialization for gemm's constant false call, while the general dense field remains dynamic. It offers a smaller compiler-boundary change than wholesale source-body rewriting. Compile/Lean policy and performance UNKNOWN until runner.

These are one mechanism family; do not count the two flags as independent research routes. The second structural route remains native stats/sqrt composition and/or raw full-range accumulator. Only source versions and measurements decide which candidate survives.

19:55 preflight: **specialize-linear REJECTED_BY_ORIGINAL_POLICY**: `attribute 'specialize relu' is not allowed`. This is a source-policy limitation, not compiler rejection or measured performance. Preserve `public27-specialize-linear-receipt.json`; do not queue it. Parameterized attribute variants cannot be used without altering the protected policy, which is out of scope. Plain inline-linear remains intake/policy PASS.
