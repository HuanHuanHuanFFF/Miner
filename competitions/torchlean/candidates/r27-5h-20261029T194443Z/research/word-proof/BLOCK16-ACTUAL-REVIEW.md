# Actual prepared block16 review

The frozen source is D's 252115-byte `14ab9f4f...1beebc`, reconstructed by
the batch8 recipe. It uses existing public23 P/I caches and product callbacks.
It is not the earlier proposal that allocates new UInt32 factor arrays. The
new run begins at k=0, consumes floor(n/16) complete groups, then calls the
original QY6G for the remainder, bias and terminal. It changes rows1 only.

The new guard combines the actual row and column metadata spans with bound11.
The original C7/E2 interfaces provide per-input exponent bounds. C9 identifies
the signed UInt64 callback value with the exact dyadic product. Its internal
magnitude calculation can be retained at 2^(48+11), rather than weakened to
2^63. This gives each block mass strictly below 2^63.

The accepted WordMod v3 `block_exact` is not a direct fit: its arguments are
two sign-extended UInt32 factors. Here one prepared coefficient can have up to
35 magnitude bits when the combined span11 is concentrated on that operand.
The needed root is an arbitrary UInt64 term fold, using the already accepted
`signed64_represents`, `add_represents64` and `signed64_unique` pattern.

D8 plus Qsx prove the existing QhiS update modulo2^128. For a whole block,
sequential updates and a single update represent the same residue once the
signed64 block sum is exact. Equality of their two canonical UInt64 words
then lets all subsequent original computation remain literally unchanged.
This local equality avoids rebuilding the original bias/rounding proof.

Actual k arithmetic still needs its own bridge. The public wrapper calls run
at zero and original QPa limits n below2^20 (the source notation ށ expands to
1048576), so complete groups and their k+15 indices cannot wrap USize on the
pinned64-bit platform. Do not state the same run theorem for arbitrary initial
k without explicit range/no-wrap premises; counting only remaining complete
groups would give a simpler general interface.
The actual strict n<2^20 guard is slightly narrower than the earlier helper's
n<=2^20 guard. This correction follows direct expansion of the source prelude;
an earlier version of this review misidentified that notation as 2^31.

The original P cache, optional sparse I list, and bounds-proved getter links
remain essential. A guard over supplied metadata alone cannot prove they
describe the raw X/W inputs. Existing I9 supplies these links for the actual
cache construction; neither the finite generic model nor an abstract f root
is a replacement for that connection.

`block16-35bit-witness.json` gives concrete finite Float32 inputs with span11
on X and span0 on W. The positive prepared factor is 35 bits, and its 16-term
sum still lies below2^63. Truncating that factor to signed UInt32 changes the
positive product into a negative one. This is a counterexample to the proposed
factor32 proof transfer, not a failure of D's arbitrary-word product callback.

No mathematical defect was found in the frozen run under these actual caller
conditions. This is source/interface review only. D has independently recorded
the same smaller proof route in BLOCK16-PROOF-SIZE-ROUTE.md. Per the current
selection rule, no larger proof implementation is started until complete
native cost shows useful benefit. The current candidate has no new correct.
