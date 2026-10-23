# R11 four-row × ten-column opportunity

Read-only calculation starting2026-10-23 23:07:15UTC. Only completed901/902/904/914/916 were read; no918/919, future input, generator, candidate, Git, CI or new agent was used. The reproducible sibling script fixes those five run IDs and verifies their395 indexed artifact members, exact public4b7/suite/generator, drawn-plan→cell-work sums and original full-gate source/verdicts. All five have156 total cases,152 timed, including34 timed BMM and1 raw BMM. Raw cases are retained separately and excluded from opportunity/ROI totals.

**There is enough observed shape coverage to justify completing the already-started probe/codegen check. There is no measured gain estimate.** Full four-row tiles cover32.65%–52.23% of timed BMM MAC; p≥10 alone covers12.77%–33.35%. True case/group time and actual SIMD/spills remain UNKNOWN.

## Exact arithmetic and existing paths

For each timed matrix, the new candidate domain is batch>0,m≥4,p>2,n>4. Only complete groups **inside each batch** count:

`covered MAC = batch * (4 * floor(m/4)) * n * p`.

The remaining `batch*(m%4)` rows are excluded. Columns use ceil(p/10) groups: full-column valid MAC is coveredRows*n*(10*floor(p/10)); tail valid MAC is coveredRows*n*(p%10). Their sum is covered MAC. Logical scheduled ten-column MAC lanes are coveredRows*n*(10*ceil(p/10)); these are not machine instructions or measured work. Every selected case's official work equals its true batch*m*n*p in these five artifacts; total timed BMM work also equals true MAC here. This equality is verified, not assumed for future plans or n=0 cases.

The exact current Cross implementations5c5e/7cad have the same dispatcher: p=2,4≤batch*m,positive n and the stated64-bit USize/array/output bounds. Their `groups(rows)=(rows+3)/4` also computes the padded final row tile; **Cross covers all valid rows**, not just floor(rows/4) groups. Script output separately records complete-group and tail MAC. DirectContinuous2aaa and a066 DirectRows use n≤4,p>2. The two p2 variants are alternatives with the same shape guard, not additive coverage.

All actual intersections between the new wide domain and p2 Cross, between wide and short Direct, and between these actual p2/Direct dispatch guards are0 cases/0 MAC. Cross itself includes short n: its n≤4 shares of total timed BMM MAC are0%,4.1391%,10.0178%,7.8396%,4.1664% for the five seeds. This is already Cross coverage, not additional short-Direct coverage. Value-dependent underflow/NaN guards and future dispatch precedence are outside this shape-only calculation.

| Seed | Timed BMM MAC | Wide cases(p≥10/p<10) | Complete-row wide MAC | Wide share | p≥10 share | p<10 share | p2 Cross share | Short Direct share |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
|901|4,072,096|16(11/5)|2,126,916|52.2315%|33.3459%|18.8856%|12.5566%|22.6175%|
|902|4,263,309|11(6/5)|1,391,896|32.6483%|18.4959%|14.1524%|8.7038%|4.1386%|
|904|4,248,185|15(6/9)|1,439,992|33.8966%|12.7667%|21.1300%|26.0099%|4.1539%|
|914|4,493,433|17(13/4)|1,711,336|38.0853%|29.8524%|8.2329%|23.5185%|8.4082%|
|916|4,235,168|16(11/5)|1,686,048|39.8107%|26.1000%|13.7106%|12.4946%|8.4171%|

These percentages are MAC exposure only. They are not time shares, success probabilities, or samples of unseen confirmation inputs.

## Column tails and padding

| Seed | Logical padded10/valid MAC, all wide | p≥10 | p<10 | Valid wide MAC in column tails |
|---|---:|---:|---:|---:|
|901|1.4584|1.1125|2.0691|920,276|
|902|1.5128|1.1592|1.9749|737,576|
|904|1.8600|1.1303|2.3008|955,992|
|914|1.3958|1.1706|2.2125|589,976|
|916|1.5070|1.1358|2.2137|699,168|

p<10 is entirely a partial column group and is substantial in several plans. p≥10 can still have a final partial group; its valid tail MAC is separately available per run/case in JSON. The baseline Packed10 path already uses ten-column packets, so this padding ratio is **not an incremental penalty of the proposed4×10 kernel**. It only describes useful lane occupancy. It also excludes any extra SSE padding chosen by LLVM. Padded zero B lanes can produce NaN when multiplied by infinite A; unused lanes must not drive a blanket valid-output replay decision. Actual per-valid-lane finish/NaN repair behavior and its cost require the real implementation/proof/codegen.

## Cell-time bounds, without a MAC→time allocation

The common control is exact a066 in all five runs. For each category the script finds every BMM cell containing at least one qualifying case, then sums **the entire cell's original scored cost**. That includes unrelated cases, row tails, preparation, emission and replay. This is a loose upper bound on recoverable cost if changes are confined to the selected domain. It is not the elapsed time of qualifying cases. Subcategory cell sets overlap and their bounds must not be added.

| Seed | All-wide touched-cell upper bound, %whole | p≥10 bound | p<10 bound |
|---|---:|---:|---:|
|901|25.3087%|16.7747%|21.0203%|
|902|18.1138%|17.4478%|15.1026%|
|904|21.2235%|12.1861%|21.2235%|
|914|21.3788%|21.3788%|12.1457%|
|916|22.2541%|17.8681%|11.8283%|

For916's newer exact DirectContinuous control, the corresponding bounds are18.8061%/15.7723%/9.4002%. All-wide touches all six BMM cells there, so that bound is the whole BMM cost despite covering39.81% of MAC. Multiplying its MAC share by BMM time would not locate the unknown guard time.

On that observed Direct operating point, saving3% of the whole would require removing at least15.95% of the all-wide **loose cell budget**, or19.02% of the p≥10 budget if using only that category. Those are optimistic necessary fractions, not predicted gains; the true affected kernel fraction can be much smaller. Even the p≥10 upper bounds exceed3% in all five plans, so this screen does not rule out a useful result. It also cannot show that one is attainable. No bootstrap/performance model was rerun or changed.

## Register model and first falsification

The proposed layout hypothesis is concrete:

- Column-major field index4*c+r makes each four-row accumulator column contiguous: ten SSE accumulator vectors plus one four-A vector and one B broadcast/temp ≈12 live vector registers.
- Row-major field index10*r+c usually needs three accumulator vectors per row:12 accumulators plus3 B vectors and1 A broadcast ≈16.

This12-versus16 budget is **INFERRED**, not actual generated SIMD. LLVM may use a different SLP width, partially scalarize, retain struct memory, spill at a helper call or choose different temporaries. ABI argument/return marshalling and any out-of-line helper can introduce stack traffic even below the nominal register count. Lowering40 fields to a heap object per k would invalidate the intended register-loop design regardless of the shape coverage.

The first discriminating observation is the already-planned exact-source C/nm/assembly: actual hot loop should keep per-output k order, show the intended grouping/broadcast reuse, and reveal whether allocation occurs only at group exit or per k, whether calls remain in k, and whether accumulators spill on each back-edge. Preserve the output/NaN/tail proof obligations. If the actual loop does not realize the layout, stop claiming register headroom and use that concrete codegen failure. If it does, only the complete original cost boundary against the frozen current control can establish benefit; cell bounds alone cannot justify adoption.

## Reproduction

Run `python -B competitions/floatlib/candidates/f01-d7-research/round7h-20261023T193125Z/review-wide-opportunity.py` to regenerate only its sibling JSON, or add `--stdout` for no report write. A fresh stdout run matched the saved data exactly after removing the generation timestamp. No generator or new run/seed argument exists. The script binds the three existing guard-source hashes and all original evidence; raw case entries and individual `case_time_ns: UNKNOWN` are retained.

Disposition: finish the current bounded probe/codegen check; no new Kernel or additional variant is requested by this review. Actual SIMD, spills, case costs, incremental complete gain and final independent adoption remain UNKNOWN.
