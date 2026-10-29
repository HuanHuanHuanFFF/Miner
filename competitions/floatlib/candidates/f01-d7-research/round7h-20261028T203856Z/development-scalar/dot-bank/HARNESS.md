# Whole-bank harness protocol

UNPROVED/NOT_RUN until Root composes, compiles, checks native C/ASM and runs it.
No official matrix/BMM/kernel/score claim. There are only three full callers;
all primary row-cache preparation and output allocation are in each bank call.
Each pass calls a separate-module external raw-bank barrier, one concrete bank
function, then an explicit structural UInt32 sum of ALL returned output words.
The output array is consumed/released by this observer before the next pass.
No higher-order engine or Bool selects a hot dot. No cached rows are input.

Main imports BenchFull, BenchSuite, Submission and R24DotBarrier. Root must
compile the supplied R24DotBarrier.lean as a separate module/library without
LTO. It returns the original nested raw-bank pair except counter1000000007,
where second=first; allowed iterations≤2^24 never reach that sentinel.

Environment uses BENCH_DOT_FIXTURE (fixtures.json path), BENCH_DOT_MODE
verify|measure (default verify), BENCH_DOT_GROUP24282601|24282603,
BENCH_DOT_VARIANT exact|eager|lazy, optional BENCH_DOT_BOUNDARY=full only,
BENCH_DOT_MACS default131072 and≤2^24. Work=rows*cols*inner, not inner length.
Reps=max1 ceil(MACS/work). Input JSON conversion is outside the bank boundary;
the bank call, row caches/drop, output allocation, ALL-word observer/drop are
inside every measured pass. Resident raw inputs do not prepay row caches.

TAB-separated records:

`BANK_SAMPLE name group variant full trial work iters actualMACs ns sink expectedSink keepWord`

Exactly three raw samples, no fastest-only selection. expectedSink is
seed+iters*sumExpected mod2^32, seed2654435769+1664525*trial mod2^32.
sumExpected is computed once from the full golden array outside timing.
One actual full call+output observer warms each trial and another posttimer
call+observer verifies the same word. Every output word is checked separately
in verify mode, so the additive timing observer is not the sole correctness check.

`BANK_SETUP name group variant full 0 lifecycle_wall_ns 3 lastWitness`

The lifecycle wall includes warm/witness/clock/record overhead; not a pure
drop metric. No preparation/compute/output drop is moved outside the bank call.

`BANK_VERIFY name outputs expectedSum exactSum eagerSum lazySum true`

`BANK_VERIFY_DONE cases outputWords 3`

Verify runs all six banks and compares all464 full output words per backend
against the exact integer-dyadic oracle. Any mismatch throws and exits nonzero.

`BANK_MEASURE_DONE group variant full cases 3`

Each selected group has three banks and nine raw samples. Root's16process
paired order remains exact/eager/eager/exact/exact/lazy/lazy/exact per group.
Actual C audit must find external barrier and fixed twoargument ARRAY-return
bank function within each pass backedge, plus the full output traversal and
release. This is caller-amortization research, not a competition model benchmark.
