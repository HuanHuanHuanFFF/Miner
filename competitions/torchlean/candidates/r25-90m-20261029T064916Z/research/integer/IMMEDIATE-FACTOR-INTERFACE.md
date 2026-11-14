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

The explicit candidate load is `u=(w.toUInt64 ^^^ 0x80000000)-0x80000000`.
For `w<2^31`, xor adds2^31 and the subtraction restores w. Otherwise xor removes
2^31 and subtraction produces `w−2^32 (mod2^64)`. Thus the resulting word is
the standard signed32 value encoded as signed64 for every UInt32 w. The cheap
representation check in `signextend32-probe.json` replays this exact expression
on194560 operand accesses for all160 retained narrow dots, with identical
once-rounded bias outputs and ReLU outputs; all160 meet both signed31 guards.
It also preserves12 fixed boundary words and all256 cases of an8-to16-bit
instance. The Lean word identity in `SignExtend32.lean` is a **NOT_COMPILED**
draft, including unverified `bv_decide` import availability.
The policy token list does not itself reject `bv_decide`; that is not evidence
that its default proof path avoids native-related additional axioms. This draft
must pass actual axiom inspection and independent kernel replay before adoption.
`SignExtend32Explicit.lean` is a separate Nat/UInt.toNat two-case proof draft,
using quotient/remainder xor identities and ordinary arithmetic tactics, with no
additional import. It too remains **NOT_COMPILED/AX_NOT_RUN**. The current
evidence is the paper identity and the original finite word replays.

Against the frozen contiguous-UInt64 C loop, the source adds **two xor and two
sub operations per MAC**, plus loading/unboxing two immediate-array entries.
This is an operation count, not an instruction or latency estimate. A compiler
may recognize sign extension, but no generated code has been observed. The
ungrouped wide path's93-bit rejection remains unchanged.

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
