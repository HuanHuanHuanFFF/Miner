# Actual benchmark code evidence

Capture the existing round4 CPU diagnostics from the actual paired release library, with candidate/source/library hashes and the pinned toolchain. Use nm to locate d_plan or the symbol containing the inlined D loop; source d_parse may not have its own machine-code symbol. Check that the target body is present in untruncated objdump text.

The intended structural change is current i head stores followed by i+1 input/hash/head reads before current matching/record/relaxation. Trace the hash-address register definitions to distinguish lookahead head reads from the current node's prev4/prev7 loads and from price-ring accesses. Compare control-flow and value dependencies, not .so digest, symbol addresses, register renaming or block listing order alone.

Confirm that the next position's prepared values feed the next ordinary/continuation iteration without redundant recalculation. The long-match branch must use fresh reads after insert_range, rather than the early pn1 values. Report live-range spills, duplicated lookahead work and compiler-eliminated/reordered loads separately. Extra unused lookahead on long jumps/final exit is part of this candidate's real cost.

The source already uses this pipeline in DP, but that does not establish it is faster in D's larger record/price loop. Same native tokens/public bytes and a material paired total-compression improvement are required before confirmation/gate investment; current assembly lacking useful overlap or added spill cost is a reason to stop this one fixed candidate.
