# Parent1939 overlap32: independent review

The signed and unsigned formulas are mathematically valid under the proposed
length bound. Let B=2^32, M=B² and use Euclidean decomposition p=Bq+r with
0<=r<B. Then S=BQ+R. Write Q=Bf+u with0<=u<B. Because R<M, the low word is
L=(Bu+R) mod M and its single carry is exactly the predicate L<Bu. Therefore
the high word is f plus that carry. For signed Q, f is arithmetic shift32;
for unsigned Q it is logical shift32. The loop need not compute that carry.

The n<2^32 assumption safely bounds both Q and R. It is sufficient, not the
sharpest general limit: signed inputs remain universally safe at n=2^32;
unsigned inputs remain universally safe through n=2^32+1. Current source36
n<2^20 is far inside either bound, so no runtime guard change is requested.
Two independent failure modes beyond the sufficient range are retained:
signed quotient-sum overflow with n=B+1 and p=-2^63, and residual-sum overflow
with n=B+2 and p=B-1. The parent's existing positive-length counterexample
shows the latter; a quotient range bound is also necessary.

`overlap32-review.json` compares704 signed/unsigned arrays against direct
integer sums and the original signed128 carry update. More concretely, the
arithmetic/logical-shift mixup has a valid source36 Float32 witness:
linear shape(2,1,1), X=[80000001,80000001], W=[00000001], bias=[00000000].
The original prepared domain has lo0, shift0 and span0, with each exact product
-1 in2^-298 units. Correct outputs are negative zero [80000000,80000000];
the wrong logical variant returns positive zero [00000000,00000000]. This is
a finite mathematical witness, not execution of a new Lean kernel.

The integration proof must change its state invariant. The old high-word
parameter h represents h*2^64+l; the new second register represents Q.
For example at k=n=4, h2/l0/P2^65 satisfies the old prefix mass range but
reinterpreting h as Q reconstructs2^64. Actual kernels start fromzero, so this
is not a counterexample to the algorithm or the old kernel. It is a counterexample
to blindly retaining the old generic accumulator invariant after changing
the register meaning. If both MD and MD2 change, their structural relation may
remain, but the numerical ZMD invariant still needs a new proof.

The actual product must first be the intended signed64 or unsigned64 integer;
low bits of an uncontrolled wider product are insufficient. Preserve the same
bias/zero finalizer. Keep register updates scalar and inspect actual codegen;
the old implementation may already use efficient ADC, so this review does not
establish a speedup or request another CI run.
