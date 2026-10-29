# Fixed-source final-cell reuse decision

Recorded 2026-10-29 00:09 UTC. Source-only investigation; no local Lean or new target implementation. Final source construction is paused for actual island3 repairs.

The fixed FloatLib revision is `0d91825727839f597fd06b22fdd038ea21480f0c`. All listed public files have FloatLib Team MIT source headers. A newer-branch file's existence does not imply fixed-version availability.

1. `DirectedSemantics/Rational/Logarithm.lean:327`, blob `88c6df468dcb07bcc68e78c998e74a6a9eb7fe01`, exposes `Model.floorLog2_scaleByPowerOfTwo` for nonzero numerator/denominator.
2. `DirectedSemantics/Rational/NearestEven.lean:201`, blob `796a22ce1c8601df415e600d3677b730b80c0a4e`, exposes `Model.roundQuotientEven_scaleByPowerOfTwo_add` for a nonzero denominator. Exact logical binary scaling composes before quotient rounding.
3. D already uses these in `development-scalar/quotient-boundary/RescaleNative32.lean.inc`, SHA `6d704ea38d73e8daadce7e6a2308dc2c25d550eba67e8de8c485b4629af25d90`, all-branch actual raw32 rescaling. Reuse the statement rather than reimplement. Current source status is NOT_RUN.
4. D broad `development-broad/ScaledCell.lean.inc` already contains `normalize_strict` and `native32_scaled_strict` for interior mantissa greater than 2^23, arbitrary source and target scales. It proves actual raw rational rounding using real cross-multiplied inequalities. Do not duplicate its ordinary case.
5. D PowerCell supplies binade-22/23 power and minnormal cells in normalized Nat coordinates. The only current B source contribution is the actual-error-driven v3 match repair; no new cell mathematics.

The missing combined interface is a single normal-q wrapper over exact magnitude S = (N/D)*2^E: mantissa M in [2^23,2^24), field Z in [1,253]; upper midpoint `(M+1/2)*2^(Z-150)`; ordinary/minnormal lower `(M-1/2)*2^(Z-150)`; power lower `(M-1/4)*2^(Z-150)` only when M=2^23 and Z>1. Strict inequalities reject ties. Logical normalization may use an arbitrarily wide Nat denominator; the runtime certificate does not need to materialize it. Negative results use a common exact sign and magnitude, not an unchecked proposal-sign assumption.

The direct dyadic connection remains an additional obligation. The public `IEEE754/Native/Integer/Rounding.lean:54`, fixed blob `0f79753745f67a8e29e539570b2c66139cc29313`, gives `roundRat_den_one_eq_roundDyadic` **only at exponent zero**. Its private integer-normalization lemma is not a public arbitrary-exponent theorem. Do not silently specialize it to an arbitrary dyadic exponent.

Public fallback interfaces are available: `Arithmetic/Finiteness.lean:210`, fixed blob `004b664c87925e80cfbad280ef77e34a109893d9`, proves dyadic round finiteness from `abs d.toReal <= toReal(posMaxFinite)`. Native `ofUInt32_roundDyadic` / `ofUInt32_roundRatScaled`, each in the fixed Narrow Agreement file (blob `f319e0d19a7aa8f421a169c0c4f8bf6d2497722a`), connect actual word functions to model rounding. Together with finite roundAt semantics and nonzero real-value injectivity, this may close the dyadic case, but the max-finite magnitude premise and target field decode must be proved rather than assumed circularly.

No source or interface here claims an optimization, new-track acceptance, per-profile hit rate, or overall score improvement. The scope remains old ContractTensor mathematical helpers.
