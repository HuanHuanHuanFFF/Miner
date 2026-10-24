# R11-W02 patch fragments (no runtime patch applied)

## Candidate row summary

```lean
inductive ZeroProductSummary
  | allFinite
  | firstNaN (k : Nat) (quietWord : UInt32)
  | firstInfinity (k : Nat)
```

For each A row, scan the original raw `UInt32` words in increasing k until the first exponent field `0xff`. Fraction zero means infinity; nonzero fraction means NaN. Quiet the NaN by setting bit 22, but prove the result equals the actual FloatLib `quietNaN` output, preserving all other bits. If the scan finds no exponent-255 word, return `allFinite`.

## Output construction

- `allFinite`: emit raw `0x00000000`.
- `firstNaN(_, w)`: emit `w`, not `ExecFloat.Binary.toFloat32` followed by re-import (native NaN canonicalization would lose payload/sign metadata).
- `firstInfinity`: emit actual binary32 `invalidResult` raw word `0x7fc00000`.

## Integration boundary

No changes are made to the uploaded Kernel or runtime definitions. The candidate should be gated only for columns proved all signed-zero. Reuse one row summary for all such columns in that row. Nonzero/general columns use the existing ordered kernel unchanged. For a single-nonzero column, do not integrate until the prefix/center/suffix theorem and raw output bridge are closed.

## Required proofs before patch integration

1. Raw classification is complete for every UInt32 and reports the least exponent-255 index.
2. The all-finite prefix's actual FloatLib ordered fold is +0.
3. NaN summary output equals actual `Spec.mul` selection/quieting; infinity summary equals actual invalid result.
4. Existing `mul32_not_snan` plus `add_mul_absorb` prove the suffix is absorbed.
5. The summary output uses the original raw word path.

The implementation above is a design fragment, not compiled code or an accepted patch.
