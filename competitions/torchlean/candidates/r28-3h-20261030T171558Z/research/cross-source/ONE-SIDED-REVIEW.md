# Parent1848 one-sided representation: independent scope review

Accepted as a paper specialization of the centered identity, not as a new
independent algorithm, compiled proof, or runtime result. No frozen candidate
or CI request is changed.

For actual nonnegative aligned factors `a_i` and signed weights `b_i`, with
`Q=2^(24+sw)` and `v_i=b_i+Q`, the body is exactly
`sum a_i*v_i - Q*sum a_i`. Neither a weight row sum nor the nQxQw term is needed.
`a_i<2^(24+sx)`, `v_i<2^(25+sw)`, `sx+sw<=15` imply a positive product strictly
below2^64. This corresponds to the existing draft `product_unsigned64` with
`ex=23+sx`, `ew=24+sw`. A product above2^63 must use unsigned carry, as the
parent's supplied raw-word counterexample shows. The unsigned128 step statement
in CenteredArithmetic.lean is unconditional in the UInt64 product word, but is
still uncompiled here.

The separate cache-sum premise is safe when the actual producer has
`n<2^20`, `sx<=15`: each a_i<2^39 and therefore sum a_i<2^59. The correction
Q*sum a_i has fewer than84 bits using the combined-span bound. This does not
permit silently replacing a larger producer domain with the consumer domain.

The claim `v_i<2^31` additionally uses the existing Mobile weight-span `sw<=6`.
The combined-span15 condition alone does not establish it. A span7 weight
still fits UInt32 because v_i<2^32, but that broader case requires its own
producer/guard proof rather than borrowing the31-bit statement.

Actual integration still needs: finite and nonnegative-input admission tied to
the exact cached row; whether negative zero is conservatively rejected or
allowed through a zero-mantissa case; the all-zero metadata sentinel; cache
sum/index equality; correct per-output Q; original body scale and bias context;
and original raw exact-zero replay. BN/ReLU provenance does not replace a
kernel-local guard. Existing sparse and negative/nonfinite paths must remain.

The current complete-cost candidates are frozen. This specialization may reduce
future arithmetic/preparation work, but its actual producer layout and native
cost must be distinguished from c5acf195 and the frozen Mobile pointwise source.
