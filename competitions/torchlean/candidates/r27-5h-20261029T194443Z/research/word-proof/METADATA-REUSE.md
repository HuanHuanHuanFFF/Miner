# Reusing the strong predecessor's existing exponent metadata

Source27 f92ee2c9…: `Yc`/`Zp`, `Zb`, `Yk`, `Yp`/`Yu` and `ZQ`.
This is a paper-level sufficient-condition derivation and exact interface
analysis. No new candidate caller or Lean acceptance is claimed.

For each vector, suppose its already-computed metadata gives a lower index
L and upper index H for every nonzero finite word, with L≤H. Set s=H-L.
The existing metadata proof, rather than a new maximum scan, can supply this
per-word premise. Source27's packed extrema are not literally idx min/max:
decode them with its `Yk`/`Zp` interface before applying the conditions below.

For a raw word, m=mantOf(word)<2^24 and aligned magnitude is m*2^(idx-L).
Thus:

- sA≤7 and sB≤7 imply each aligned magnitude<2^31. Their signs fit the old
  strict signed32 encoder without needing the negative-endpoint exception.
- sA+sB≤11 implies each product magnitude<2^(48+sA+sB)≤2^59.
  Any16-term block has mass<2^63; every shorter tail does too.
- n≤2^20 gives the global signed128 body bound already used by the carrier.

These conditions are conservative but use O(1) per-vector/pair metadata that
the strong caller already has. They avoid the literal `preparedBody`'s2n
maximum reads per output. The actual cost question still includes preparing
aligned factors and extra arrays; for rows1, each weight is used only once,
and source27 already shares the input across4outputs. Cache wins cannot be
assumed from the scalar MAC count. Wide/nonfinite/reversed metadata can reject
before allocating prepared factors and immediately use the strong fallback.

## The bias's23-bit distinction

Raw `oneW` has mantissa2^23 and idx126. The original terminal `YL lo oneW bias`
requires `lo≤126+idxBias` for a nonzero bias product. By contrast, adding a
separate integer bias at bodybase=LA+LB needs only
`bodybase≤149+idxBias`, since the2^23 factor has been absorbed algebraically.

For example, bodybase252 and bias idx116 satisfy the integer shift13, but
violate the original YL lower-index condition242≥252. This can occur for
ordinary small biases, not only minsubnormal. Therefore:

1. Keep the separate Int bias terminal unless an actual native merge is proved;
   or add a direct shifted-bias128/192 primitive under a real range guard.
2. Reusing YL once is valid only with its stricter raw-index premise, or after
   rebasing the body and rechecking factor/product bounds. Simply invoking
   its existing theorem at bodybase is not justified.
3. The existing `Yp` includes bias by lowering its shared base. Replacing it
   with LA+LB silently changes this proof premise. Keep the two bases explicit.
4. A zero bias can ignore either exponent lower bound; exacttotal0 still
   recomputes through the original signedzero callback.

The source27 `Ybo/X7` final rounding endpoint itself accepts a signed192-bit
value and arbitrary exponent; the problem above is the arithmetic step that
constructs that value, not its final rounding theorem.

Finite applicability check (`bias-interface-coverage.json`): all160 previously
seen seed42 normal/sparse firstlayer dots have integerbias shifts24..29, so
YL at bodybase needs raw shifts1..6 and its lower-index premise holds there.
This does not eliminate the legalcounterexample. Public12 exposes the same
YL/Zr/YD/ZV interfaces (lines502/512/519/521); once the body carrier is
accepted, signextend128to192 then one existingbias step is a concrete minimal
terminal route for guardedinputs. Out-of-guard uses the original exactcaller.

## Whole-formula applicability and native next boundary

`word-model-coverage.json` replays6previouslyseen27051001/typical cells,
normal/wide/sparse atrows1/8. Normal/sparse eligiblelogicalMAC fraction is
about85percent, primarily the first472→240 layer. Wide is0 or0.0075percent.
All6 originalformula hashes match; this observer does not replace the kernel.
The bound is not a latency fraction or speed prediction.

For firstlayerrows8,906240eligibleMACs need117056preparedvector entries,
about0.129prepared entries perMAC. Rows1 cannot amortize each weight's
preparation across input rows. Any firstnativecaller should preserve the
strong4row/4column sharing and include all preparation in timing; a4-times
scalar wrapper is not the existing4-lane baseline.

The fallback must reuse BX/BV already computed inside the strong YaV. An
outer wrapper that computes Yc to choose a path then calls oldYaV on rejection
will scan metadata twice. That can regress wide/rows1 even if no fastdot runs.
Likewise, FactorInt32's simple Intvalue/power constructor is a proof interface,
not evidence of cheap nativepreparation. A cost-facing implementation should
use bounded native mantissa/exponent shifts and prove equality to that value;
Int/Nat powers or duplicate validity scans must be counted if retained.

Next minimal source after carrier acceptance: one actualprepared-array caller
inside the existing metadata/scheduling boundary, with a concrete four-lane
consumer. Keep wider/unsupported inputs on the certified strong per-dot/group
fallback without duplicate preparation. Inspect its exactC and then measure
wholecall against the strong report-bound anchor. Do not repeat huge41KB draft
closure or claim MAC-count savings equal model speed.
