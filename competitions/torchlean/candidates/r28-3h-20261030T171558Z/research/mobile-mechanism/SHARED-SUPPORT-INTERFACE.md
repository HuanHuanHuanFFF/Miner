# Shared-support follow-on: index/offset descriptors without factor repacking

This records Root's2007 next-round direction using only old material. It is **not a new Kernel, CI request, or independent success chance**, and it uses no CI6 inputs/results.

For a pair of input rows/pixels, partition original indices into both-nonzero, row0-only, row1-only. Build those groups once and reuse them across output channels. A both group loads one weight and updates both rows; one-sided groups update one row. Two independent row lists perform the same nonzero arithmetic but duplicate weight reads on the intersection. Three-way grouping adds preparation, allocation and dispatch cost; that tradeoff needs a complete-model experiment, not zero-density arithmetic alone.

A useful compact descriptor keeps **index and already-prepared offset**, while leaving values in the existing P2 buffer:

`code = t·2^32 + off[t].toNat`.

With original k<4096 and t<k, code<2^44. In the narrow k<256 domain it is<2^40. Thus it fits a small Nat on the pinned64-bit target without imposing a new factor-magnitude restriction. Decode through UInt64 as `t=code>>>32`, `offset=code.toUInt32`; this removes another off-array lookup and avoids recomputing channel-stride multiplication. It does not copy factors or transpose the input. Actual storage/instruction cost remains unmeasured; UInt64 arrays must not be treated as unboxed by analogy.

**Zero is a valid descriptor.** t=0,offset=0 gives code0 even when that input is nonzero. Use group lengths, not code0 as an absent-entry sentinel. The concrete false-sentinel example is input1.0/weight1.0/bias+0: dropping descriptor0 changes the exact dot from1.0 to+0. Prepared arithmetic zero remains the separate input representation2^57 in original53 narrow mode; weight-zero's2^31 sentinel is different again.

Exactness interface: prove every group element comes from original0≤t<k and has the actual off[t]; prove disjointness and that the union covers precisely the kept terms; then use integer sum commutativity/zero elimination within the existing bounded exact-dot domain. Prefix split-limb bounds remain valid because each row has at most k terms and every term has the same absolute bound, regardless of permutation. Preserve raw zW/Ybz for exact-zero signs and all nonfinite/wide/odd-row/shape fallbacks. Reordering sequentially rounded floating additions would not follow from this argument.

The original output layout is CHW. A pixel-pair-outer implementation needs unique-reference set/uset at o·hw+p rather than appending NHWC order. Include initial output allocation, index construction, weight gather, three loop entries, reference-count work and destruction in the first cost experiment. Sparse weight and dense support fallbacks must stay measured against their real existing implementations. The≤1 support shortcut remains too narrow in our old census; this descriptor instead supports the full multi-element sparse rows.
