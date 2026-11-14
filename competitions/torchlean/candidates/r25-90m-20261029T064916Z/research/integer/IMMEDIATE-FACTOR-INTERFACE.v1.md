# Integer-factor storage: avoid assuming C uint64 arrays equal Lean arrays

The pinned Lean **v4.34.0** runtime header was fetched from the official repository,
saved byte-for-byte, and verified against Git blob `910ecae72a7d1c149d4ccc8111ee438c8b4551dd`.
See `sources/runtime-source-receipt.json`; the file header explicitly says Apache2.0.

Verified runtime facts:

- `lean.h:941–964`: an ordinary Array stores `lean_object*` entries, one pointer
  slot per element. On a 64-bit platform this is an 8-byte slot, not four bytes.
- `lean.h:2977–2984`: `lean_box_uint64` allocates a constructor with uint64 payload;
  unboxing reads that payload. A straightforward Array UInt64 cache therefore
  has a material representation risk absent from the frozen packed-C probe.
  The exact future generated code, allocation elimination and total size are
  still UNKNOWN until inspected.
- `lean.h:2955–2964`: UInt32 boxes as an immediate on a 64-bit platform. There
  need not be one heap constructor per cached UInt32 value.
- Nat's immediate bound is `SIZE_MAX>>1` (`1476`); Int's small range is only
  `INT_MIN..INT_MAX` on a 64-bit platform (`1686–1687`). Replacing a 39-bit UInt64
  cache by Int must not be assumed allocation-free.

The already observed primary factors fit a stronger interface. With a per-vector
exponent span at most7, an aligned magnitude is strictly below `2^(24+7)=2^31`.
Encode its signed value in standard 32-bit two's-complement. Cache those bits in
**Array UInt32**, then sign-extend the loaded UInt32 to a 64-bit scalar before
multiplication. No unsafe/custom-extern operation is proposed. A future version
must prove both the signed32 encode/decode identity and the exact getter mapping,
and inspect the actual compiler implementation of the widening operation.

For the retained typical first layer, X span5 and W span6 give magnitudes below
2^29 and2^30; all160 normal/sparse outputs satisfy the individual span≤7 guard.
For wide grouping of width4, X-group span≤3 and W span6 give magnitudes below
2^27 and2^30; the same interface applies. Thus the storage issue does not by
itself eliminate either measured-coverage route. It does add two sign-extensions
per MAC and an unbox operation per operand, and may affect vectorization.

Do not merely use the combined span≤11 guard for this representation: a split
of spans11+0 permits a 35-bit operand even though the product/block bound passes.
Require each span≤7, choose another proved representation, or fall back.
The current C source is left frozen and uses packed two's-complement uint64;
its future timing remains a mechanism discriminator, not a Lean-cost estimate.

The current D cache (`PatchCache.lean.inc`) stores `Array DecodedWord` records
with mant/idx/sign/exp, and its exact `cacheWords_get` lemma can anchor logical
decoding. It does not already provide a row minimum/span scan, aligned signed32
array, zero/special guard, or an allocation-free storage proof. Reuse that
semantic interface if adopted; do not assume its physical record cache can be
reinterpreted as packed factors. No D source was changed.
