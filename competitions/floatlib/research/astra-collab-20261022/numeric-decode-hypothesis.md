# Numeric reconstruction as an inline conversion candidate

This is R's independent mathematical candidate while web R2-W03 investigates the proof and practical cost. It is not a Lean-checked theorem or measured optimization.

For finite raw binary32 fields (sign S, exponent E<255, fraction F): set M=F when E=0 and M=2^23+F otherwise. The exact value is (-1)^S M 2^-149 when E=0 and (-1)^S M 2^(E-150) otherwise. M is an integer in [0,2^24-1], so native UInt32.toFloat32 represents it exactly. Every scale is representable: E=0 uses raw1; 1<=E<24 uses raw(1<<(E-1)); 24<=E<255 uses raw((E-23)<<23). Set the sign bit of the scale to S. The exact product is precisely the original representable finite value. Correct nearest-even multiplication therefore leaves it unchanged, including subnormals; M=0 yields the original signed zero by IEEE multiplication sign. This argument requires the actual fixed native logical model and signed-zero lemma before a candidate is accepted.

A pure constant table of512 Float32 signed scales could move all of_bits calls to ordinary constant initialization. The hot decoder would extract M and the 9-bit sign/exponent index, load the scale, use inline integer-to-float conversion and inline multiply. Nonfinite inputs use the original conversion. A narrower E>=24 normal fast path avoids subnormal scale multiplication and makes the first proof smaller; it includes all three timed tensor input classes. The full function must still handle all other inputs correctly.

This could be worse than the external bit-conversion call: table loads, boxing, bounds checks, UInt32 arithmetic and extra multiply may dominate, and table initialization/allocation must follow ordinary compiler/benchmark semantics. No performance claim follows from replacing one call. Also inspect actual linked code before assuming the call remains uninlined.

`decode-model-probe.py` exercises every finite exponent and both signs over boundary fractions plus65536 seeded random finite raw words. The output records exact input/output trace hash and negative findings. It tests table indexing and bit formulas only; even zero mismatches do not prove all2^32 cases or Lean acceptance. E255 is deliberately outside this fast-path diagnostic, rather than silently canonicalizing NaN payloads.

Next decision: read web R2-W03's independent proof feasibility, compare against public fixed integer-conversion/rounding lemmas, and only build a gate candidate if the proof and full-cost runtime opportunity justify it. Do not change imports, official dependencies, externs or compiler flags.
