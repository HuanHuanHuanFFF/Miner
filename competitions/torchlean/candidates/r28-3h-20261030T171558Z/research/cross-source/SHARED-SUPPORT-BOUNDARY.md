# R2007 shared support: cross-representation boundary

The three pair classes are disjoint: both inputs nonzero, only row1 nonzero,
only row2 nonzero. Row1 sums the first two sets; row2 sums the first and third.
Within the original finite, exact signed-product128 domain, omitting arithmetic
zero and reordering these modular additions preserves the body. Bias is still
added once at the original terminal. The exact-zero callback must use the
original raw X/W/b arrays, because integer zero alone does not preserve -0.

The zero predicate and the representation must be matched. `MxA==2^62` is an
arithmetic-zero test under the old producer/consumer range, not a license to use
arbitrary wide/nonfinite prepared entries. Keep the original dispatch and fallback.

Do not apply this raw-input zero filter unchanged to an offset accumulator:

| Representation | Zero-input contribution | Required handling |
|---|---|---|
| Original signed MD/MD2 | 0 | May omit the product |
| Two-sided centered C5 | Qx·(b+Qw) | Adjust every relevant correction sum/count, or retain the term |
| Public54 product-centered QW | 2^55·2^shift | Adjust its cached sum-of-shifts when omitting the term |
| One-sided nonnegative-input offset | 0·(b+Qw)=0 | Omission preserves the input sum correction |

`shared-support-counterexamples.json` gives actual finite words X=[0,1],
W=[1,1], bias0. The correct result is1. Omitting X[0] but retaining old global
corrections changes two-sided centering to-5 and the held QW transfer to-127.
These are counterexamples to a future incorrect filter composition, not bugs
in the current frozen C5 or held QW source. Reordering the original exact
signed dot remains valid. No runtime candidate, CI, or performance claim is added.
