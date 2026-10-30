# Actual caller obligations and costs

`WordBlockRuntime` and `NatBlockCore` are standalone helper sources. Neither
supplies12 kernels or a proved preparation caller. Compiler acceptance of a
helper does not close these obligations.

1. Bind prepared vector to its actual raw getter and index interval. Factor
   preparation must establish finite input, nonzero exponent at least the
   chosen base, and exact aligned magnitude fitting the selected factor
   representation. Signed UInt32 encoding permits magnitude2^31 only for the
   negative endpoint; the old helper's simpler preparation uses strict<2^31.
2. Cached maxima must be computed from the exact prepared vector. For any
   UInt32 ma,mb their widened UInt64 product is strictly<2^64; for actual
   signed32 magnitudes each is≤2^31, giving≤2^62. The guard product therefore
   cannot wrap. block16 needs the strict product<2^59, not merely factor32.
3. Each16-term mass is at most16*(2^59-1)<2^63. The remainder is shorter than16.
   This justifies decoding a signed64 block. Without this guard, interpreting
   a wrapped block as signed64 is unsound even if the final dot is small.
4. For the each-product fallback, signed32 products have mass≤2^62; with
   n≤2^20 the complete body mass≤2^82, well inside signed128. Neither branch
   can justify arbitrary large n without an outer size guard or a new proof.
5. Add finite bias before the **single** final rounding. Scaling requires
   baseA+baseB≤idxOf(bias)+149 for nonzero bias. Nat subtraction is not an
   acceptable replacement for this premise. The saved `1-1+minSubnormal`
   counterexample must return raw word1; clamping shift-103 to0 fails.
6. Bias may be much wider than the128-bit body. The current Int terminal is
   exact for arbitrary aligned bias; a direct native128 terminal additionally
   needs a total-range guard. Sufficient but conservative: biasShift≤102
   gives |bias|<2^126 and the body bound above keeps total inside signed128.
   Do not silently apply the128→192 endpoint after truncating a larger bias.
   An alternative is reuse predecessor `YL` once for the terminal bias and
   `YD/ZV`, with its real lower/upper exponent premises and signed192 bound.
7. Exact-zero recomputes through the original shipped/certified callback.
   Only nonzero totals may erase the negativeZero flag. This preserves -0
   for all-negative-zero terms and +0 for nonzero cancellation.

Cost boundary: the old literal preparedBody rescans two maxima per output.
The prospective cache caller must cache them at vector preparation and prove
that correspondence. UInt32 Array uses pointer-sized entries on64bit Lean;
there is no4-byte dense-layout claim. The new two-Nat route still needs the
actual getters compiled to determine whether sign and magnitude read each
word once. Full preparation, allocation, metadata, zero fallback, rounding
and output destruction belong to the measured call boundary.

For comparison, predecessor27 already has scalar signed192/128 MAC paths,
cached exponent ranges, bias-aware guard, fast word rounding and four-output
sharing. Every proposed gain is against that mechanism, then calibrated to
current champion36 through D's exact official report chain. No timing against
the original shipped implementation is requested by this role.

Additional cost unknown: the helper uses Nat fuel/index and higher-order
getters; public27 uses USize bounds-proved uget in its hot loops. Specialize
does not establish that Array.get! bounds checks or closure dispatch vanished.
The next ownedhelper codegen inspection should count actual per-MAC primitive
loads, tag checks and allocations. Do not attribute a wholemodel advantage
from the sourcelevel carry count alone.

Zero-bias exception: the bias lower-exponent guard may accept mantOf(bias)=0
without baseA+baseB<=idxBias+149. Its scaled value is mathematically zero for
any shift. Preserve zeroSafe fallback when the complete exacttotal is zero;
this covers negativezero bias. The nonzero minsubnormal counterexample still
requires rejecting a negative shift. StrongpredecessorYp/Yu already ignores
zero bias in exponent extrema, so an unconditional bias guard can unnecessarily
shrink the fastpath. No newcaller has yet been integrated or tested.
