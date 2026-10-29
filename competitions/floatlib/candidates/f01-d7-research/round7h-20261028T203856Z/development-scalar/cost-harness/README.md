# Dot primitive cost harness

Root owns composition, driver, CI and selected C/ASM. This Main is a diagnostic,
with six concrete noinline pass loops and six typed IO benches. It imports the
separate `R24DotBarrier` module; compile/link without LTO. Each iteration calls
one changing-counter external barrier and then one fixed Probe adapter. The
barrier returns its input except at counter1000000007, outside the allowed
maximum repeat count2^24. No runtime function argument or Bool selects a pass.
All prepared variants receive two independent operand caches and one outer pair,
including eager's `EagerOperand` pair; no precombined eager context prepays ABI work.

Environment: `BENCH_DOT_FIXTURE` is the exact merged JSON path (absolute or
relative to the process cwd); `BENCH_DOT_MODE=verify|measure` (default verify).
Measure requires `BENCH_DOT_GROUP=24282403|24282405`,
`BENCH_DOT_VARIANT=exact|eager|lazy`,
`BENCH_DOT_BOUNDARY=full|prepared`; optional `BENCH_DOT_MACS` defaults131072,
must be≤2^24. It measures that group plus directed cases, only when timed,
finite, matched and nonempty. Reps=max1 ceil(MACS/max1n).

All output records are TAB-separated, with ASCII prefix and no header:

`DOT_SAMPLE name group variant boundary trial n iters macs ns sink expectedSink keepWord`

Exactly three raw samples are retained. Each seed is1664525*trial+2654435769
mod2^32; expectedSink=seed+iters*expectedWord mod2^32 in O(1).
The macs sample column is actual n*iters, including ceil-rounding of the target.
A real one-call warm-up and one posttimer wrapper witness must match the expected word. The
witness keeps prepared data live across each measured pass; final cache release
is outside pass timing. Full adapters include their own prepare/miss/drop.

`DOT_SETUP name group variant boundary prep_ns lifecycle_wall_ns trials lastWitness`

Full prep_ns=0: its treatment preparation is already inside each wrapper call.
Prepared prep_ns measures its actual treatment cache construction. The lifecycle
wall encloses preparation, warm-ups, measured passes, posttimer witnesses,
clock/record orchestration and final cache release, with no printing inside.
It is an auxiliary wall boundary, not a pure cache-drop estimate. Sample ns
excludes input JSON parsing/conversion, output formatting and prepared-cache prep/drop.

`DOT_VERIFY name expected fastCold fastPrepared exactFull eagerFull lazyFull exactPrepared eagerPrepared lazyPrepared baseline128 reference ok`

`DOT_ROUND id expected actual ok`

`DOT_VERIFY_DONE dots rounds accepts unknownFast`

Verify checks every dot, all six complete Probe adapters, both FP attempts
(against fast_result when known, otherwise zero or expected), the frozen128
baseline and finite exact replay; then all round128 fixtures. Any mismatch
throws and exits nonzero. Source typing, native execution and cost remain
NOT_RUN until root CI. `R24DotBarrier` must be a distinct compiled module, not
text appended into Main. Actual C/ASM must confirm barriers/callbacks remain.
