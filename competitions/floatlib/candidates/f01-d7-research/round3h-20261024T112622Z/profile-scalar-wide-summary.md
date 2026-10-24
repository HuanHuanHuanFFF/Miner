# Scalar48bit product through Float64: BLOCKED

The first trust prerequisite fails in the verified fixed interfaces. Lean4.34 declares native `Float.toFloat32` opaque at line555, and `Float32.toFloat` opaque at line548. IEEE-correct C casts do not supply a Lean equation for these constants. The original gate permits only propext, Classical.choice and Quot.sound and forbids adding axioms or custom native replacements.

The official pinned FloatLib0d918 source does provide model-aware binary64 adapters and an exact native-Float decoder. These are useful existing assets, but same-width ofFloat/toFloat representation bridges and a generic decode/map/quantize conversion are different from a proof of native Float.toFloat32 rounding. They do not close the proposed final hardware narrowing step. This scoped audit did not verify a permissible native cross-width RNE theorem; it is not a universal impossibility claim about every conceivable formalization.

The mechanism would form the exact24×24→48bit product, convert it to Float64, scale by an exact power of two and narrow once to Float32, retaining existing exceptional and signed-zero behavior. Because the native narrowing bridge is missing, mantissa bounds, scale-range safety, single-rounding equivalence and end-to-end cold composition were deliberately not pursued. No numerical prototype or candidate can substitute for this first missing link. Proof feasibility and speed remain UNKNOWN.

R11 `astra-design.md` line25 already recorded this opaque widening/narrowing barrier for FloatArray storage. The storage review repeats it. No exact48bit-product/F64-scaling performance failure was found; older UInt64→Float32 wide64 decoder timings are a different mechanism and are not evidence against this one.

The smallest valid next step is to identify an existing theorem available under the actual ContractTensor import that relates native Float.toFloat32 to binary32 model rounding, and audit its complete axioms in the pinned runner. No such theorem was identified here, so no CI is justified for an implementation. A later toolchain/library change would need separate authorization and a fresh fixed-environment decision.

Four fresh official sources were saved with URL, exact ref, fetch interval, Git blob verification and SHA256:

- [Lean4.34 Float32 source](https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Float/Float32.lean), SHA `2f4b7eb845c03bd5581d70921f891798cc193f5c8c1372302a3e6064a34f7319`.
- [Pinned FloatLib IEEE754 package](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/IEEE754.lean), SHA `0827d025ed3c50546bdf1e4d838d25845223ef2a2c6b309be4b07e5225754afe`.
- [Pinned native adapters](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/IEEE754/Native.lean), SHA `b6da171304380025f556bfc93a88d4b4b7b6c7ee8fd9e07581db90878c3ec35d`.
- [Pinned generic conversion runtime](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/ExecFloat/Conversion/Runtime.lean), SHA `87e67701992da028f5b931ccc44de7e4e291de47b20532cfc826a7c84720dd61`.

Audit JSON SHA `01265fb33d5ff4ce28bdf0d7a300c9f0ffc9b6bae811e242865aab306e3b0b44`. The read-only audit exited0. No Lean/build/benchmark, candidate, official-file modification or CI was performed.
