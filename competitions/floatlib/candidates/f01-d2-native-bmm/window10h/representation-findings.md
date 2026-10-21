# Representation and index observations

Generated C from statement run39654101400 for native-bmm-proof1 has a float accumulator, but n/baseA/baseB/p/k are lean_object* Nat values. Each iteration calls lean_nat_add, lean_nat_mul, array_get_size, two Nat bounds tests and array_fget_borrowed. These are observed costs, not a measured attribution yet. Original C stays in the run artifact.

Pinned Lean4.34 source tree has FloatArray but no Float32Array. FloatArray stores unboxed Float64. ByteArray exposes byte loads; a packed32 read would need four byte loads plus proof of the encoding, though the C compiler might combine it (UNKNOWN).

Critical preflight: src/Init/Data/Float32.lean lines548/555 declare Float32.toFloat and Float.toFloat32 opaque; the source explicitly says they do not reduce in the kernel. Do not assume their numeric roundtrip can be proved by rfl from the new arithmetic model. An existing allowed theorem or another representation bridge would be needed.

Alternative hypothesis for FloatArray: store original UInt32 words inside Float64 bit patterns using Float.ofBits word.toUInt64, with no arithmetic on the stored doubles, then recover Float.toBits.toUInt32 and Float32.ofBits. All stored double words have zero exponent and are finite; bit roundtrip could be easier than opaque numeric conversion. Need verify actual native Float64 bit-model theorem and exact encoding proof, then include conversion/storage costs in full timing. This is a research hypothesis, not an accepted component.

D next index route: USize loop counter and addresses with proved no-wrap/bounds preconditions and Array.uget; fallback on the original generic loop when conditions do not hold. Pinned UInt/Lemmas.lean generates USize.toNat_add/mul/sub_of_le, toNat_lt_size and conversion lemmas; target a straight float loop with machine-word indices. R can focus on multi-output lanes and representation proof/layout, avoiding duplicate work on this D route. Each output preserves its k order and separately rounded multiplication/addition.
