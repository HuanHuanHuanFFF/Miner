# Independent fixed-source RNE32 cell/scale research

Read-only mathematics and proof-interface research, maximum two pages plus downloadable Markdown. No internal subagents, new target kernel, Lean execution, CI or blocked-API retry. Primary sources only, fixed FloatLib0d91825727839f597fd06b22fdd038ea21480f0c, Lean4.34. Do not claim source acceptance or performance.

The native64 error and midpoint geometry are separate components. The remaining bridge is to the actual public `Model.NativeBinary32.roundRatScaled sign N D t`. N,D are arbitrary mathematical Nat with N,D>0; t:Int. Runtime must NOT normalize N/D into64bit. Let raw32 normal proposal have field1<=e<=253,0<=f<2^23,m=2^23+f,z=e-150. Define ghost r=(N/D)*2^(t-z)>0.

Wanted exact word-cell theorem:

- f>0: 2m-1<2r<2m+1.
- f=0,e>1: 4m-1<4r and2r<2m+1 (the lower midpoint is m-1/4 in this quantum).
- f=0,e=1: 2m-1<2r<2m+1 (minimum normal has symmetric subnormal-side spacing).

Under the corresponding STRICT inequalities, conclude `roundRatScaled sign N D t = NativeBinary32.mkBits sign e f`. Negative proposals use the same positive ratio and sign; zero/ties rejected. A proof in Real/scaled words is acceptable, but the conclusion must be actual rounder bits, not only nearest-point existence.

One proposed route: for integer k, `(N',D')=RationalBinary.scaleByPowerOfTwo N D k`, establish exact representation invariance `roundRatScaled sign N' D' (t-k)=roundRatScaled sign N D t`. Then normalize logically toz and reuse already-written arbitrary-Nat strict quotient/power-cell proofs. Fixed source offers `floorLog2_scaleByPowerOfTwo` and `roundQuotientEven_scaleByPowerOfTwo_add`. The existing roundRat-den-one→roundDyadic bridge observed so far only has exponent0, so it must not be cited as arbitrary-exponent equality. Min-normal belowm enters the SUBNORMAL branch; non-minnormal power belowm enters previous normal binade, rounds mantissa with carry; these must not be conflated.

Inspect the exact source interfaces:

- https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/ExecFloat/Backends/Word/Narrow/Base/Runtime.lean
- https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/DirectedSemantics/Rational/Logarithm.lean
- https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/DirectedSemantics/Rational/NearestEven.lean

Find a real counterexample to the desired statement/scale route or give the shortest complete branch decomposition and exact public theorem signatures. Do not re-prove the native64 error bound, midpoint formula, generic integer quotient cell or power carry already covered; identify only the actual missing transport. Name additional hypotheses if truly necessary, preserving arbitrary Nat widths. Prefer a new imported interface that deletes proof work, but a source search miss is not an impossibility proof. No broad literature dump or new benchmark proposal.
