# New decision evidence from completed samples

**Do not narrow the architecture to p=2 merely because its8-lane core is easiest.** In current622d's completed D/A/B, p=2,n>1,m>=4 occurs in2/1/7 scored shapes. With only class totals, its rigorous whole-time upper bounds are6.851%/2.818%/14.963%, and all lower bounds are0. Thus even free p=2 work cannot reach3% in the A sample. These are upper bounds for the complete touched classes; actual target work is strictly less unless the other shapes are free. Bounds overlap with other domains and must not be summed.

| Current622d completed sample | p=2 upper | p3..8 upper | p>8,n>4 upper |
|---|---:|---:|---:|
| D1526007 |6.851%|11.280%|16.142%|
| A1526101 |2.818%|17.149%|20.023%|
| B1526102 |14.963%|17.933%|8.596%|

No scored p>8,n2..4 shape appears in these three groups. This absence does not prove that broad domain unimportant. Exact target timing/actual underflow-miss frequency stays UNKNOWN.

Conditional request-size accounting, if all selected shapes enter and Array capacity equals length, gives extra major allocation requests versus old B2 full rows: p2 **+1,476,000/+705,600/+3,946,432 B** across D/A/B; p3..8 **+1,816,848/+2,292,128/+1,221,232 B**. These sum logical evaluation counts over the public plan once, not25 timing rounds or physical allocator bytes. They exclude closures/allocator classes/RC and rely on new A4/F8 direct-field codegen still to be checked. The exact formula per4-row block is32n+48−16G. At p2 it is32n+32B, unconditionally positive. One block's expected panel+tiles peak is32n+48G+48B, excluding input, globalB and output. This establishes a real added-work risk, not its time cost.

The older DF uninstrumented per-case diagnostic supplies a narrower, versioned bound: selected n>1,m>=4,p>=2 whole calls sum to8.079%/5.123%/9.814% of old whole across1224011/1224091/1224092. p2 alone is2.811%/1.935%/2.030%; p3..8 is3.839%/1.429%/4.913%. Those totals include original software replay/prepare/output and cannot be transferred to622d, whose routing and timings differ. They also cannot cap the *matrix representation family*, because they omit n=1,p=1 and low-row entry cases.

One concrete next coverage dependency is now identified from actual622d source: **n=1 still uses DirectContinuous/NativeFinal per output; there is no retained n=1 B cache in622d.** For n=1,p>=2,m>=4, the same proved A4B2 core is mathematically available without new arithmetic lemmas, and it would share B across rows in addition to sharing A across columns. The present5f53 dispatcher deliberately retains n>1 and remains unchanged while queued. Old R13 n1 row-prepared negative only shared A and still converted B per output; it does not test the new A4+B2 representation. p=1 would compute an unused second column with the current core, so removing the p>=2 guard blindly is not a cost argument; a true4x1 branch would need its own representation/caller evidence. Keep these as follow-on coverage questions, not a guard grid or a reason to change the queued source before feedback.

Exact raw-source identities, every shape/request row, current-class bounds and old per-case records are in `domain-cost.json`; calculation in `domain-cost.py` completed in0.018s under5s subprocess timeout. Actual new allocation, codegen, gate and speed remain UNKNOWN/NOT_RUN.
