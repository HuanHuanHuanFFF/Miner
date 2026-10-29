# Next discriminator: share the exact root and numerator

Source: pinned `ExactToolkit/StableNorm.lean`, definitions `sqrtAccuracy` and `sqrtModel`, read from the R24 fixed source copy. No candidate or CI queue entry is added here.

`sqrtModel q` calls `sqrtLower (sqrtNumerator q) q.den` as the rounding significand, then calls `sqrtAccuracy (sqrtNumerator q) q.den`, whose first binding computes the same `sqrtLower` again. `sqrtNumerator` and `sqrtShift` are also repeated across these calls. Their actual native sharing is UNKNOWN: source duplication alone is not a measured duplicate call.

A new owned `sqrtModelShared` can let-bind shift, numerator, denominator and root once, compute the original `sqrtAccuracy` cases from that root, and call the unchanged `roundWithAccuracy`. Expanding the pinned definitions makes `sqrtModelShared q = sqrtModel q` definitionally true; a corresponding `sqrtRationalShared` keeps the original nonpositive branch. No approximate root, new certificate assumption, finite-domain restriction or output-rounding change is needed.

First discriminator after the current proof/measurement group: inspect the original generated C/assembly for actual repeated Nat.sqrt/num construction on the normalization caller. If the compiler already shares them, stop this route. If two expensive calls remain and normalization is material in overall profiles, build the exact sharing wrapper in a fresh candidate path, prove its direct equality and run the original complete gate/model boundary. Keep cache and integer-moment attribution separate.

Maximum root-computation saving is one of the two source calls; overall saving is UNKNOWN and must be weighted by observed source/caller costs. Public former2 already has accelerated normalization/root paths, so this is an independent shipped-reference opportunity rather than a current-champion advantage claim.
