# Dynamic square-accumulator certificate — 20:14 UTC

The #27 source's `rsU`/`rsV` computes row sum and square sum with two 64-bit words, then marks the statistics unusable unless every nonzero input's exponent spread is at most36 and row length<256. On rejection, `Y8f` reconstructs broad exact limb sums. The guard is conservative, not an overflow observation.

`mixer-frontier-result.json` executes the pinned complete finite Mixer formulas on27 cells/3 roots.82 of816 norm rows have spread37–39 and fail this guard; every sampled square sum needs at most127 bits. `norm-dynamic-result.json` replays408 initial norm rows with explicit carry checks: all408 are accepted, including all82 static rejects.2000 further constructed rows exercise zero, narrow, broad and overflow cases. These are finite formula evidence, not native results.

**Do not merely raise36 to40.** A concrete legal255-element row (`0x00000001`, followed by254 copies of `0x147fffff`) has spread39 and a134-bit square sum. It overflows the old128-bit accumulator. The dynamic two-add carry predicate correctly rejects it. The original source's `n<256` combined with span36 is a sufficient theorem, not a fact that can be relaxed by changing literals.

The candidate mechanism adds two checked high-word additions for each square: first add the low carry to the old high word, then add the square's high word. Require both results to be >=their first operand. Permit per-term spread<=40, so each24-bit square shifted by at most80 still fits128 bits, and require the cumulative checks to remain true. Positive/negative linear sums still fit128 bits for n<256 since each aligned factor is<2^64. All failing paths retain the original exact fallback. `CheckedCarry128.lean` is a small UNCOMPILED certificate for the actual pair-add step; no all-input norm/runtime theorem is claimed.

Before integrating this new statistics loop, obtain the waiting packed-linear and norm-guard26 native evidence. The next discriminating native measurement, if available, should include the entire #27 `Y8f` call and existing root/output stages on normal/wide/sparse rows; branch-only timing omits the relevant broad fallback. Full Mixer impact is UNKNOWN because no current per-layer profile has been observed. This is separate from D's dot-product word-block scheduling, but shares reusable exact-carry mathematics.

License/source boundary: only self-authored model, small proof carrier and this mechanism description are public. The original #27 remains ignored/private. Original gate/contracts are unchanged.
