# One-sided unsigned follow-on: actual pixel producer check

Accepted parent's ONE-SIDED-POSITIVE-DOT boundary: for actual nonnegative finite aligned inputs, `Wpos=W+Q`, `Q=2^(24+sw)`, so the original body is `ΣX·Wpos−Q·ΣX`. This is a future refinement only. **No frozen5ecf/474eff/85eb source, guard, threshold or CI queue was changed.** It is the same local-scale family, not an independent success chance.

`positive_pixel_model.py` replays the existing18 complete old formula models through their real pointwise arrays and local minima. All24 dense narrow pointwise calls are nonnegative; that is observed input coverage, not an allowed caller assumption. An eventual kernel must still test finite/sign conditions, permit or fall back on negative zero correctly, and preserve excluded-input paths.

The exact unsigned carry plus terminal subtraction reproduces **38026 fast outputs /254982 products**, with **4398 shared row sums /29614 sum additions**, no mismatch. Every row sum remains<2^63 and every positive-centered weight fitsUInt32. Bias stays in the same full dot through the original qCtx2 scale/context; raw exact-zero replay is retained as an obligation.

The carry distinction is present in real prepared inputs, not only a contrived edge: **697 products are≥2^63 while<2^64**. Deliberately reusing the signed-product carry would corrupt **688 outputs** in this finite set. This does **not** identify a bug in frozen5ecf: that source multiplies X·W, which its≤15 guard bounds strictly within signed64. The larger one-sided product X·(W+Q) requires the unsigned carry and the terminal correction.

This follow-on removes per-term representation subtractions/sign extension at the cost of one pixel-row-sum cache and terminal correction. No timing is available and source/proof size is OPEN. Wait for the already-planned complete Mobile cost signal before building a new variant or spending full proof budget.

`UnsignedCorrection.lean.fragment` is an uncompiled draft of the unsigned carry using actual C9 and the exact two-word shift split for q∈(0,64). Actual q=24+sw lies in[24,30]; existing Y5b supplies terminal subtraction. A low-word-only correction is insufficient when Q·ΣX exceeds2^64. After n<256 terms, positive sum<2^72 and correction<2^71 give a final signed128 range. This is a small proof interface, not accepted roots, a complete producer proof, or a new CI request.
