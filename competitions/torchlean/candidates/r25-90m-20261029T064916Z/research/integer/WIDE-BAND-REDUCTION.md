# Wide input: band the input exponent, retain an indexed weight read

Next-route derivation only; the narrow cost candidate remains frozen separately.
`band_pair_probe.py` checks one public **typical** profile, seed42, wide MLP
first layer `608→80`. All 80 outputs agree with the independent rational dot
and one exact bias-inclusive binary32 rounding for each of four fixed grouping
widths. This is not native cost, Lean acceptance or hidden-workload coverage.

The global prealignment has `spanX=39`, `spanY=6`: factors individually fit
64 bits, but their product needs up to 93 bits. Group nonzero X indices by
four consecutive exponent values. Each group has `spanX_group≤3`; align X
relative to that group's minimum, and keep Y at its common minimum. Then the
signed product fits strictly below `2^(48+3+6)=2^57`. A 64-term block therefore
has absolute sum below `2^63`, so its UInt64 modular fold is exact when decoded
as signed64. Accumulate block results into a signed128 group total, shift that
total by `groupBase−globalXBase`, and merge it into the global signed128 total.

The exact integer argument is distribution-independent once these guards hold:

1. Each original nonzero X index occurs in exactly one group, with its original
   matching Y index. Zero products contribute zero. The indexed getter and
   partition/coverage proof are necessary; sorting by value alone is not enough.
2. Low-word multiplication represents the exact signed product, from the local
   factor bounds. `Block64Fold.lean` drafts the actual word-fold/decoding proof.
3. Shifting each group result back by its exact base difference restores every
   original term. A total guard `48+spanX+spanY+ceilLog2(n)≤127` suffices for
   signed128 reconstruction; local64 fit alone does not suffice.
4. Add the bias exactly before the only rounding. Check special values before
   dropping zeros; fallback on exact zero can retain the full signed-zero policy
   without assuming that a skipped term had positive zero sign.

For this fixture, width4 has 10 groups, 14 within-group wide additions and
10 shift/add merges per dot, replacing a proposed global-aligned baseline's
608 wide product/add operations. It retains all 608 low64 multiplies and adds
608 index reads. Width1/2/8 yield respectively40+40,20+20,154+5 block/group
merges. These counts **do not rank runtime**. The JSON's `input_extra_index_bytes`
means a planned packed UInt32 payload (2432 B at n608); UInt64 indices need
4864 B, and actual Lean array allocation/boxing remains UNKNOWN.

New work is not free: count/prefix/scatter X grouping, index storage, indirect
Y reads, group boundaries and final shifts replace contiguous hot reads. Y can
stay cached in original order across input rows; permuting Y for each X row
instead would add row-dependent preparation and storage. The first native
discriminator should compare the indexed version to a complete aligned
signed64×signed64→signed128 loop, including per-call preparation. Do not infer
speed from fewer operations or from the narrower route's eventual result.

`route-falsifiers.json` preserves exact failures for a too-large block, missing
group shift, unsigned extension of a negative block, lost negative-zero policy,
and locally valid bands whose full sum needs554 bits. The latter must reject
before a UInt128 shift; the public wide fixture's global bound is only103 bits.
Actual partition/getter proof, codegen, full-call timing and official obligation
remain open. No new native job has been started for this route.
