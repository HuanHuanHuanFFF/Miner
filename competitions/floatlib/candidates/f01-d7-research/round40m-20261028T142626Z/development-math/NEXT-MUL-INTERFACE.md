# Next-round interface: native band + proved integer normal MUL

**Decision:** retain exact f90d proof as a reusable component. Native and integer domains complement one another mainly when native is checked first and integer replaces part of its cold fallback. Integer-first adds only three native-only exponent pairs and intercepts almost the entire current native hot domain. No aggregate speedups can be added.

Exact sources: native F7=`f7ba2ddb…` (233664B, 40615975642 full gate25, ratio0.9555001521, p05−0.0041730576, not adopted); integer=`f90d42e3…` (253978B, 40708758777 original statement + both replay modules +49 AX passed81.5s, runtime timing UNKNOWN). `compare_mul_domains.py` / `mul-domain-crossing.json` bind both sources and the new MainFull evidence. Frozen F7 is not a new seed candidate.

| Exponent field domain | Pair count | Meaning for native-first→integer→B2 |
|---|---:|---|
| Both |16381|Same native hot operation; no second arithmetic saving to add|
| Integer only |31878|Possible replacement of B2 fallback, after paying integer guard|
| Native only |3|(190,191),(191,190),(191,191); native already serves these|
| Neither |17274|Additional integer guard followed by unchanged B2; potential regression|

Native's exact guard is eu,ev∈64..191. Integer's is eu,ev∈1..254 and128≤eu+ev≤380. Native-only is the three high-sum pairs above. These are complete exponent-field combination counts, **not input probabilities or CPU shares**; fractions do not create guard holes (the pairOR guard is exactly two magnitude intervals). Concrete integer-only inputs include raw0x00800000×0x3f800000 (min-normal×1) and0x7f000000×0x00800000 (large×small).

**Do not widen the integer sum guard to381/382 without a new overflow proof/branch.** Fresh exact-integer emulation of current normalCore gives:

- 0x5f7fffff×0x5fffffff, sum381: current core would emit0x7ffffffe (NaN), while exact product exceeds the RNE overflow threshold2^128−2^103 and must give0x7f800000.
- 0x5fffffff×0x5fffffff, sum382: current core would emit0x807ffffe (negative subnormal), again versus0x7f800000.

These counterexamples only concern the hypothetical widened guard. Current f90d correctly sends both to its proved fallback. Native handles the three extra high-sum field pairs, including finite/overflow distinctions at sum381. Repairing overflow would broaden a theorem; the current generic fallback composition needs no such domain expansion.

The retained source itself independently explains the expected infinity: `FastMul.roundP` tests `normalizedPosition>425` and returns sign-selected infinity. These two maximal-mantissa products have leading47/no carry and normalized positions426/427, respectively. This source check agrees with the exact integer overflow-threshold comparison.

**Minimum proof interface.** `R19BiasBase.R19DirectBias.guardedMul_spec fallback hf` accepts any fallback satisfying `∀x y, fallback x y=ExecFloat.Spec.mul x y`. It can specialize to an independently proved native MUL. Native-first needs the existing native pairOK proof plus an analogous fallback-parametric wrapper, with integer guardedMul as fallback. Assemble once against a shared B2 base; cap is UNKNOWN until exact deduplication (f90d has2022B headroom). Public sum/BMM remain old aliases; a new public MUL does not enter their inner loops automatically.

**New actual f90d caller evidence.** CI40708758777's generated MainFull C selects static closed2→`main___lam__1___boxed` as Suite MUL. Its typed body is45 integer instructions, with no push/pop/call; its three misses relocate to retainedMul. The boxed wrapper still performs2 unbox,2 reference-count decrements,a typed call,and1 output box. Actual assembly SHA `b423a001…`, MainFull object `4369cfa6…` are diagnostic-build evidence, not the cleaned-up timing object. Historical native-cold diagnostic had a28-instruction typed body with FP/table work and no frame; instruction counts are not cycles and that predecessor object is not an F7 timing result. The common wrapper boundary exists, but its elapsed-cost share and whether it is a bottleneck are UNKNOWN; 64-bit scalar boxing/RC may be lightweight. Swapping arithmetic alone leaves this wrapper in the call graph.

**Benefit ceiling and smallest next experiment.** In old integer discovery the changed exposed MUL represented36.7–38.8% of that diagnostic's total. Its3.3–6.1% MUL improvement corresponded to whole ratios0.9676..1.0021, including a slowdown. Even an ideal additive fixed-cost model would need roughly26–27% local MUL reduction for10% whole reduction at that historical share; new f90d workload shares/costs remain UNKNOWN. F7's unchanged SUM/BMM timing variation (including BMM1.0108) cannot be called implementation gain. Any irreducible wrapper cost belongs in the fixed-cost floor, but its size must be measured rather than inferred from instruction presence.

Next round, compare B2/native/integer/native-first/integer-first through the **same actual caller and ABI** in one bounded discovery diagnostic; classify all cases by the four domains and retain all miss cases and whole boundaries. Compare complete routes, including branch/layout, retained fallback, boxes, input/output preparation and cleanup. Only a material whole result should buy a frozen new-source full gate and new independent confirmation. If the goal is a large BMM gain, reuse the proved integer word semantics in a directly typed inner loop/ABI experiment and prove that new caller; do not expect the public scalar wrapper to change retained BMM.
