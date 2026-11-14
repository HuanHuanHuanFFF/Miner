# Depthwise-only Winograd interface: the inverse can stay in signed64 split limbs

This is a conditional paper/finite-model follow-on, **no new Kernel or CI request**. It uses the parent/A spatial matrices and their corrected per-product bound; it is not a second independent confirmation of those shared facts. The additional observation is specific to one independent depthwise channel: inverse outputs contain at most9 signed transformed products, so the whole inverse can remain in two signed64 split accumulators and normalize to128 only once per output.

Let `M=2^24−1`, input aligned range `|X|≤M·2^sx`, weight range `|W|≤M·2^sw`, with original narrow `sx+sw≤31`, `sw≤6`. B's2D input transform has L1≤4 and G′'s2D weight transform L1≤9. Split every transformed V by Euclidean division at2^25:

`V = (V mod 2^25) + 2^25·floor(V/2^25)`.

The low product magnitude is at most
`L=(2^25−1)·9M·2^6 =324259144179647040`.
The high product magnitude is at most parent's
`H=9M²·2^8 =648518269031942400`.
For sx<23, the negative-floor ceiling is2^(sx+1); combined with sw≤6 this stays below that same H. For sx≥23, the exact aligned quotient gives H directly. No unjustified strict floor bound is used.

Each inverse output has9 coefficients±1, so **9L<2^62 and9H<2^63**, including every sequential prefix. Intermediate inverse rows contain at most3 terms:3L<2^60,3H<2^61. They can therefore be cached as small Nat with center2^61; final low/high words remain in registers. Apply original qCtx4-style split reconstruction only after the inverse, instead of doing128-bit carry at every inverse add/subtract. The exact scaled body isT=4S; use B0−2 with a newly prepared bias context (guard B0≥2), retaining original raw-zero replay. No bias can be rounded or shifted independently of that context.

`depthwise-winograd-model.json` checks all203 admissible span pairs on3045 directed/random integer tiles,12180 outputs, no mismatch or signed64 inverse-prefix overflow. Random integers cover a superset of aligned word values; this is not observed producer coverage, Lean acceptance or native speed.

Cost caution specific to **public53**, distinct from ResNet11: four dense narrow depthwise outputs use72 split UInt64 multiplies; transform uses32 before setup/inverse/finish. But public53's **am actually compacts sparse weights**. At about half support its old work is about36 multiplies, so transformed filling gives almost no arithmetic room and adds work. Retain the existing sparse path. Input transformation also has no cross-output-channel amortization in depthwise, unlike ordinary convolution. The actual Mobile stage share and complete prepare/cache/drop cost must decide whether this beats the already-selected pointwise route. No complete latency bound or ≥7.26% gain is claimed.
