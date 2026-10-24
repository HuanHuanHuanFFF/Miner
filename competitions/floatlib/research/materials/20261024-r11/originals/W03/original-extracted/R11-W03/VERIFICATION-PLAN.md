# R11-W03: smallest target falsification, then full acceptance

All target commands in this file are **NOT_RUN**. Do not change the gate,
its inputs, compiler flags, comparison, aggregation, or retained control.

## 1. Prepare only one diagnostic build at a time

Use an isolated copy of the official competition environment, pinned to:

- Lean 4.34.0, commit `293d5d0c0c3f3dded4688b3ccd6a33939ac5102b`.
- FloatLib `0d91825727839f597fd06b22fdd038ea21480f0c`.
- Competition `4b7e83841cc0c32c6529f533923c73d33b5ecf97`.
- Clang 22.1.4, original `-O3 -ffp-contract=off`, no `-march=native`.

Copy **one** exact complete Kernel from this bundle to `Kernel.lean` in that
isolated build; preserve/check SHA256 before elaboration. First attempt the
unmodified R11 source. Its new namespace is not known to compile. If it fails,
save the log and apply any independently verified parent proof repair equally
to the control and both candidates; give each new combination a new SHA. Do
not treat a broken control as a valid baseline or silently fix it in this bundle.

Run the existing official Lean invocation with exactly its explicit options.
Keep autoImplicit and relaxedAutoImplicit explicitly false if that is the
official argv. Do not raise any supplied limit beyond maxRecDepth8192,
maxHeartbeats4000000, synthPendingDepth400000. Capture the actual registered
option name and argv from the official environment rather than guessing a new
option spelling here. Emitting C uses Lean's `-c <output.c>` option in the same
configured `lake env lean` context; preserve all official options when adding
only that diagnostic output. An import of Kernel in the separate probe module
requires the matching Kernel.olean; never reuse one from a different candidate.

Record actual executable paths, versions and SHA256 for lean and clang; target
triple and full argv (`clang -###`); source/header/runtime library SHA256;
actual dynamic/static link and LTO status. Merely recording the intended pins
does not establish the executable identities. Stop with NOT_RUN if unavailable.

## 2. Smallest codegen decision

Start with the inline short-shared candidate and the four functions in
`probes/R11W03Probe.lean`. They reach the actual public bmm and keep its entire
output construction. Shared n1/n2, mixed n2, and tail n2 cover the new branch
and two relevant fallbacks. They are codegen roots, not timed benchmark inputs.

Inspect the actual entry/call graph in emitted C. Old P12 functions can remain
as unused definitions, so whole-file string presence does not show hot-path use.
On the new shared n1/n2 branch require:

1. No temporary packet Array / Vector construction, no P12 constructors.
2. No `lean_box_float32`, `lean_alloc_closure`, `lean_apply_*`, or boxed worker
   bridge in the arithmetic path. Remaining terminal F8/W8/output allocations
   are classified separately, not counted as failure of packet elimination.
3. Eight independent `+0 -> multiply/add -> [multiply/add]` chains, using
   Float32 C `float`; no Float64 accumulation or cross-k partial reduction.
4. Actual raw input conversion calls are located relative to each first
   multiply/add and each lane's partial value. Source let order alone is not
   the scheduling evidence.
5. Existing isNaN/toBits/replay and row-major W8 order are still reachable.

Compile that exact generated C through the original Clang driver/link route.
Keep an assembly/object copy and inspect relocations plus final disassembly.
Optional remarks in a separate diagnostic build:
`-Rpass=slp-vectorizer -Rpass-missed=slp-vectorizer
-Rpass-analysis=slp-vectorizer -fsave-optimization-record`.
Remarks explain decisions; they do not replace assembly or the original build.

Count/read these categories independently: runtime of_bits calls; first and
last arithmetic op for each chain; actual calls between two updates; stack
argument stores; predecoded input saves; accumulator spills; terminal result
saves; allocator fast/slow path; F8 and W8 construction; output reconstruction.
No conversion of counts into predicted nanoseconds is justified.

If inline staging exposes conversion calls between updates, compile the
scalar-call variant once. It has 7 and 13 Float32 arguments including +0.
If an ordinary SysV call survives, at n2 five arguments occupy 8-byte stack
argument slots (40 bytes, excluding alignment/frame/other storage). Lean's
noinline attribute does not emit C noinline in this compiler; Clang may inline
the helper or produce the same machine code as the first variant. If they
converge, record that result and do not count them as independent successes.

## 3. Minimal data falsifiers

Use raw words in the original comparison, including:

- n1 -0 times +1; required output +0, not bare-product -0.
- n2 A=[bf800000,3f800001], B column=[3f800000,3f7ffffe].
  Ordered result00000000; second-step FMA resulta8800000.
- Distinct quiet-NaN payloads and signs, signaling NaNs, a NaN introduced at
  k1, Inf times zero, and finite overflow followed by opposite-sign Inf.
  Expected payloads must come from the exact original Spec/replay.
- Smallest subnormal, cancellation to signed zero, ordinary finite values.
- Shared/full `(batch,m)=(1,4)`; partial crossing `(2,3)`; two and four
  batches/group `(3,2),(4,1)`; tails R=5,6,7; m/batch/p/n=0 fallbacks;
  n>2 and p!=2 dispatch controls.

The bundled Python rational witness runner verifies only the first two
finite mathematical counterexamples. It is not the candidate or gate.
Finite dimensions/words cannot discharge arbitrary-Nat or IEEE proofs.

## 4. Stop or run the unchanged full-cost experiment

Stop the allocation-elimination claim if P12/packet Arrays remain on the new
branch. Stop the contiguous arithmetic claim if target code interleaves raw
conversion calls with live partial accumulators. Stack traffic alone is not an
automatic failure: the tradeoff is fixed stack transport against allocation.
If a correctness/spec/axiom gate fails, do not time/adopt the candidate as valid.

The first useful development timing must time the complete BMM call, including
preparation and destruction, raw-array lifetime, terminal checks/replay, F8/W8,
tail rows, final Vector.ofFn, and exactly the output consumption/lifetime the
unchanged harness includes. A predecoded arithmetic-only benchmark does not
answer this question. Also include long-n/mixed paths: the added dispatch has
a cost even where the original pack is retained.

Freeze the candidate and unchanged controls before the original four specs,
statement build, kernel replay, permitted-axiom audit, checksum tests and
**25 paired full timing rounds**. Retain raw per-case/per-round records,
pair order, environment and the original uncertainty/aggregation rule.
Use the retained accepted control in addition to an actually compiled R11
control. Do not use the old14.81% exposure as a weight or expected saving.
If intervals or full-call regressions fail the established acceptance rule,
park the candidate with evidence; no gate or benchmark redesign is part of W03.
