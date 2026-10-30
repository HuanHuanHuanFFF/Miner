# Affine positive rows: exact dot representation

Status: original paper derivation, word-level finite model and a complete-runtime
cost candidate. No new Lean correctness theorem or original all12 gate exists.
This is distinct from exponent-band grouping, FP certificates, and balanced
multi-output big-integer packing. It preserves index order and the original
scalar/paired fallback loops; it moves signed decoding and scale correction
from each MAC into preparation and one terminal correction.

For one row let the existing public36 metadata give a lower exponent `mx` and
upper exponent `hx`. The signed aligned factors are `a_i = sv(x_i) 2^(idx_i-mx)`.
For a nonzero finite row, `|a_i| < 2^(24+hx-mx)`; for an all-zero row use offset1.
Let `Qx=2^ex`, `Qw=2^ew`, each exponent at most39, and `n<2^20`. Prepare

`u_i=a_i+Qx`, `v_i=b_i+Qw`, `Ux=sum u_i`, `Vw=sum v_i`.

The exact all-integer identity is

`sum a_i*b_i = sum u_i*v_i - Qw*Ux - Qx*Vw + n*Qx*Qw`.

It follows by expanding each `(a_i+Qx)(b_i+Qw)` and collecting the two row
sums. It does not depend on cancellation, signs, sparsity, or observed inputs.
The offset products are powers of two, so the terminal correction needs shifts,
two subtractions and an addition, rather than a wide integer multiplication.

With `ex+ew<=61`, `0<=u_i<2Qx`, `0<=v_i<2Qw` imply each positive product is
strictly below `2^(ex+ew+2)<=2^63`. Thus the hot UInt64 low multiplication is
exact, and its signed-extension word is always zero. Unsigned128 accumulation
uses only low addition plus one carry into the high word. The initial cache
representation is ordinary small Nat: every `u_i<2^40<2^63`. Also
`Ux,Vw<2^(20+40)=2^60`; an independent per-row bound is necessary. A finite
negative control with ex61/ew0/n128 shows that the combined product-width bound
alone does not keep a cached row sum in UInt64.

Each terminal shift of a UInt64 row sum by at most39 is represented in two
words; the n-term shift is at most61. Addition and subtraction are done modulo
2^128 with explicit carry/borrow. Hence the corrected two words encode the
signed body modulo2^128, even if an intermediate subtraction is negative.
The source's old exact span guard implies each actual signed shifted product
has magnitude below2^63. With n<2^20, the body has magnitude below2^83; the
included bias term has magnitude below2^63. The true total therefore fits
signed128 comfortably. This is the bound needed to recover its signed value
from the modular pair; a modular identity alone is not enough.

The old terminal scale is `lo=Yp bx bw bias`; the body correction uses
`d=mx+mw-lo`. The new branch separately checks d<64 and shifts the *complete*
corrected pair once. The d=0 branch is explicit because UInt64 shifts mask64
to0. Then the original `YL lo oneW bias ... YD ... (lo-298)` adds bias before
the original single rounding. A zero sentinel still calls original `Yai` or
`Ya2`; the cached positive rows do not preserve negative-zero history by
themselves. NaN/infinity, malformed bounds, rejected spans and small/odd paths
continue through the original runtime.

`centered_dot_model.py` checks literal 64-bit carry/borrow/shift operations,
1944 directed/random cases, the missing-carry and zero-shift negative controls,
and18 old seen complete Mixer outputs against saved native checksums. In this
cohort, the actual paired-linear branch covers272894 MACs and scalar GEMM
80961 MACs among857004 dot MACs; extra positive preparation touches84348
items. These are work counts, not elapsed shares or a speed prediction.

`build_centered36_cost.py` keeps original runtime definitions and adds positive
alternatives. It removes only obsolete prepared-engine proofs (while preserving
cross-region proof dependencies) plus the final `correct` theorem for diagnostic
byte budget. Therefore **the candidate is not admissible or adoptable**.

If complete cost is useful, the remaining Lean bridge is: exact metadata bounds
including the all-zero sentinel; cache getters and cached-sum bound; unsigned128
loop invariant; three affine corrections and final pair shift; equivalence to
the original signed MD/MD2 result; caller guards, fallback and all12. The existing
generic carry and original metadata proofs are reusable only with their exact
premises. A production byte budget must be demonstrated for that complete new
proof source, potentially sharing the linear/GEMM proof and removing unused old
driver proofs. The current native-only file size is not that demonstration.

A same-mechanism refinement uses ex+ew<=62: positive products remain strictly below2^64, so the unsigned carry-only loop is still exact, including products above2^63. Cached sums remain<2^60 and the positive aggregate<2^84. This requires the unrestricted unsigned128 step lemma, not the old signed63 Z128 premise. The original61 diagnostic is preserved. unsigned64-extension.json matches18 oldnative outputs, raises actual paired/GEMM eligible MACs353855→466862, and gives an actual raw-word counterexample excluding63. The preferred native-only candidate is c5acf195; no full proof/adoption claim follows.
