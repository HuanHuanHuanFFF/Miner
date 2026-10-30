# Raw-bit FloatArray carrier: separate logic from cost

This uses FloatArray only as contiguous64-bit storage. Encoded payloads below2^52 are zero/subnormal binary64 patterns with exponent0, so they avoid Lean Float's logical NaN canonicalization. The already accepted R27 native_ofBits finite-word root supplies the main model bridge; a small bits projection and public-push/getter wrapper remains to compile. No numerical Float arithmetic is needed, and it must not be introduced into the storage pipeline.

The cost premise is not automatic. The exact4.34 header makes UInt64 boxing allocate, but a52-bit payload also fits64-bit smallNat, whose Array elements are immediate words. Comparing against an unpacked two-cache layout would conflate packing with the FloatArray carrier. A same-payload packed ArrayNat control is required if the actual QP data is already Nat. B is checking that actual representation and its width; A does not assume it.

There is also a concrete call risk: Float.ofBits and Float.toBits are external runtime declarations rather than header inline functions. The old actual4.34 FloatArray+GRS assembly has a direct lean_float_to_bits call. This is not a claim about new codegen, but it prevents treating FloatArray extraction as a free integer load. A new proof-indexed get removes array checks; it does not by itself inline toBits.

The old R24 FloatArray experiment stored numerical scale constants and performed FP ADD/narrowing; its negative result is preserved but is not the same storage-only mechanism. The bounded repository search found no already accepted raw52-bit carrier wrapper. Source/API facts and exact hashes are in PRECHECK.json. No new candidate, large producer or CI queue is created.

Next decision: close one finite bit-roundtrip/array construction interface, obtain B's exact QP layout, and identify work eliminated against packed ArrayNat. If this saves only a tag shift while adding a bitcast call, do not launch a cost experiment. Any positive case still needs full preparation/access/destruction cost and exact final proof binding.
