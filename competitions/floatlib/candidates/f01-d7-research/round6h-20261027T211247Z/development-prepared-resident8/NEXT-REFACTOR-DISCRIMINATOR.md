# Next matrix refactor: largest untouched route and minimum falsifier

**Current decision: no additional matrix kernel/CI.** The largest uncovered path is the actual DirectContinuous scalar-dot writer. There is no demonstrated next10% whole opportunity from merely increasing block width, repeating singleton/short-k/wide code, or deleting one row division. Private-suite shape and cost distribution remain UNKNOWN.

`route-partition.json` maps every timed case through exact622d's mutually exclusive shape router, then uses all8 seen control blocks per seed. This is after the outer data-dependent UnderflowZero guard only in source order; whether each generated case takes that zero branch has not been reconstructed, so the following times are loose whole-case touch bounds.

| Static route | seed2220001 whole | seed2220003 whole | Outside resident16 |
| --- | ---: | ---: | --- |
| DirectContinuous |10.06%–10.17%|5.79%–5.86%|9.12%–9.22% /5.79%–5.86% whole|
| R15PackedB2 |6.34%–6.46%|7.19%–7.28%|3.37%–3.42% /3.56%–3.61% whole, mainly p2/3|
| R14ThinBCache |3.13%–3.18%|1.17%–1.19%|All, currently p1|
| RowStream/F10 |0.71%–0.73%|1.36%–1.39%|All included by16's broad guard|

Large uncovered cases include `[batch,m,n,p]=[29411,2,1,3]`, `[8823,5,1,4]`, `[8823,2,2,5]`, `[8823,1,2,10]`, and `[1589,37,3,1]`. They are not all one route or one removable stage. No overlapping shape percentages are added.

Actual selected C shows direct writer's outer row loop computes `r*n` and `(r/m)*n*p`, then calls a specialized static column fold. Each column calls NativeFinal.dot; its inner loop performs two raw reads, two `lean_float32_of_bits` conversions, Nat index arithmetic, and one ordered mul/add. This repeats A conversion across columns and B conversion across rows. It has no packed input preparation to remove. The specialized output loop already pushes directly into one capacity-reserved array; the standalone row callback closure is not evidence of an active per-output closure. ThinB already decodes B once globally; B2 already shares prepared two-field B packets. Removing input work must be charged against those actual routes, not against a hypothetical naive baseline.

History blocks the easy retries:

- R9 d5e3512f changed both direct-dot decoders and measured BMM1.17313/whole1.04035 vs41: negative. R13 7086031b changed once-per-input packed preparation, BMM1.005952/whole1.003435; different scope, also negative.
- R19 f84ea2db changed indexed B2's A decoder and really removed warm-loop call/spill, yet full25 result whole0.995854643/BMM0.966864998/p05−0.006708170 failed adoption. It is not an untested mechanism.
- R10 d70 small-n unroll, ff34/995d singleton and f448/ce683 caches are existing complete-gate sources. R13 8661 actual unboxed row sharing gave whole0.997634/BMM0.993289. Reusing them under a new name would not change the cost premise.
- R11 ad323 batch→row direct writer is fully proved/compiled and removes one dynamic division per row, but lacked a same-scene2aaa causal comparison. This is an unresolved low-cost side test, not a new high-ceiling route; do not call it performance-negative or promote it from removed-division counts.

**One concrete next structural question, already screened before coding:** can four independent row instances, even when m<4, share one native A4 panel across all column groups, while each group's B8 packet holds the two columns for each row's own batch? This would delete actual direct-path repeated A decodes and expose eight native chains for low-row matrices. Unlike old CrossP12 (p2, joint A+B packets) it separates the once-per-four-rows A producer from the column-group B producer; unlike same-batch R16, it cannot share one B2 packet among the four rows. It adds A4/B8 records, arrays, conversion staging, output cache, cross-batch bases and destruction. B duplication when several rows share a batch remains charged. It is not a claim that old packet reads disappear.

The intrinsic first domain would be `0<m<4,n>1,p>=3`: it avoids the already repeated singleton route, targets shapes lacking four same-batch rows, and has at least two column pairs over which to reuse A. **Minimum discriminator is the read-only scope bound, before a prototype:** exact old controls place its entire case sum at3.417%–3.451% whole in seed1 and1.931%–1.955% in seed3. Even deleting every such case cannot produce10% whole, or3% on both groups. Therefore this question is **PARK for the current public main route**, without manufacturing a new kernel or timing seed. A broader G1/p1/2 reconstruction would need a genuinely new premise beyond old Cross/P12/A-panel negatives; none has been established here.

If a future independently justified distribution makes this domain material, the first implementation milestone should be only the exact low-row cross-batch caller: prove/address-check each row's raw batch base, inspect actual A conversion once before groups, native A4/B8 fields, no hot codec/state allocation, and include all preparation/tail/finish/RC in one complete cost. Stop on replicated A preparation, per-k container/call/spill or full-call regression. Current source/count evidence does not predict a gain and cannot constrain private distribution.
