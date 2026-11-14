# Count-binned error bound and the 2720-unit witness

Status: paper derivation plus exact finite traces, not a Lean-accepted producer. This is independent follow-on mathematics. The frozen radius720 and all cost candidates remain unchanged. Current FP23 cost was negative; this is not a performance argument for reviving its proof queue.

Let each exact finite binary32 product be a representable binary64 term p_i with |p_i|<P=2^k, where -250<=k<=256. Let n<=N=2^L<=2^30. As in SUM3, the representable endpoints iP and RN64 monotonicity give |a_i|<=iP for the actual rounded accumulator. Therefore the input to step i satisfies |a_(i-1)+p_i|<iP.

The existing library half-ULP theorem used inside SUM3 yields a local absolute error at most2^(k+j-54) whenever2^(j-1)<i<=2^j. This remains a global absolute bound near zero/subnormal values; it does not assume every cancellation result has a normal binary32 magnitude. The first addition is exact because it adds an already representable product to zero.

There are2^(j-1) steps in each full group j=1..L. Summing the local bounds gives

    total_error <= sum(j=1..L) 2^(j-1) * 2^(k+j-54)
                = 2^(k-53) * (4^L-1) / 3
                = (R - 2^(k-53)) / 3 < R/3,

where R=2^(k+2L-53) is the existing radius720. This is a finite geometric sum of explicit absolute-ULP bounds, not a gamma_n recurrence or a bound involving the unknown accumulated error. For n=1 it is zero. For2^(L-1)<n<=2^L, the tighter count-specific form is

    2^(k-53) * ((4^(L-1)-1)/3 + (n-2^(L-1))*2^(L-1)).

The universal one-third bound does not require a common product exponent or a claim that the first32 additions are exact. Actual native Float operations, widening, cache/getter origin and official dsum still need the same producer connections as before; this paper calculation does not fill them.

As an exact representable conservative radius,3R/8 lies above R/3 and below R/2. Algebraically it can be encoded by exponent field H+2L+718 and fraction2^51, with k=H-250. This is only an unimplemented option; neither this encoding nor any smaller radius is substituted into the frozen source. The existing +718 *power-only* radius is R/4 and is refuted by the preserved512-term witness. Together with the R/3 upper bound, this explains why+719 is the smallest safe power-of-two uniform-error-bound choice in this mathematical loop model, while a non-power radius need not be as large as+719.

For the parent's pre-freeze512-term all-normal witness, every product has integer units2^-46 and magnitude below4, so k=2. Their common product grid gives an extra fact unavailable for arbitrary mixed exponents: the first32 additions are exact because their integer magnitudes stay below2^53. The later groups have the following maximal half-ULP errors in those units:

| Step indices | Count | Maximum local error | Observed contribution |
|---|---:|---:|---:|
| 1..32 | 32 | exact on this common grid | 0 |
| 33..64 | 32 | 1 | 32 |
| 65..128 | 64 | 2 | 128 |
| 129..256 | 128 | 4 | 512 |
| 257..512 | 256 | 8 | 2048 |

The independent exact53-bit trace confirms every local error attains the indicated positive bound, totaling2720. The universal binned bound is87381/32=2730.65625units. Removing the first32 exact additions subtracts341/32=10.65625units and leaves exactly2720. Thus this particular witness saturates the stronger common-grid bound; its total is not merely an unexplained greedy near miss.

The simple block construction extends to other lengths, but its first failed saturation is already n=1024: observed10880 versus the common-grid upper bound10912. The negative result is retained in BINADE-ERROR-TRACE.json. At larger tested lengths it stays close to the bound; this finite family is not promoted to a theorem of exact saturation or an asymptotic result. The generic one-third upper bound comes from the mathematical grouping argument, not from those samples.

Evidence: trace_binade_error.py reproduces the512-term per-step trace and a structured family through65536terms. It reads the arithmetic counterexample created23:11:31UTC, before the23:20 freeze; it does not use any held-out confirmation input or FP23 performance result to construct the family. No new CI, candidate or compiler invocation is involved.

A later independent construction in WRONG-ACCEPT-718.md replaces two terms and reaches an accepted wrong adjacent word under718; unlike the original2720 trace, it checks the actual cell decision as well. Frozen720 and719 both reject it. This remains finite model/host evidence, not a Lean-evaluated candidate.
