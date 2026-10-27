# R19 runtime representation: first actual-path decision

2026-10-26 20:04 UTC. Retained B2 SHA256 `622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58`; Lean 4.34.0 / `293d5d0c0c3f3dded4688b3ccd6a33939ac5102b`. Only this worker directory changed; no local Lean/compiler, Git/index, CI or nested agents.

**Decision: reject a boxing/refcount premise; transfer B2 word-index work to the already active D owner, and prepare one scalar classifier discriminator.** There is still no measured 10% whole-package opportunity from runtime representation alone.

`runtime-audit.json` freshly hashes the archived run 40168024176 input, Submission C and MainFull C, and records ten real function bodies. MainFull with `BENCH_PLAN` selects ADD lambda0 and MUL lambda3 (not legacy lambda1), plus the original sum and bmm wrappers. This is successful statement/bench-build diagnostic C; it is not the cleaned timed gate object.

- B2 carries native float accumulators, borrowed A/B reads and one terminal F2 allocation per pair. It does not allocate a float box per k. B preparation is already outside the row fold. Remaining k work includes two Nat adds, Nat comparison, A getD/default check and external `lean_float32_of_bits`. D's `development-workers/structural-cost/indexed-b2.lean.inc` owns the word-index replacement; no duplicate was emitted here.
- ADD/MUL bodies are inlined into the actual selected MainFull callbacks. On fixed x86_64, UInt32 ABI boxes are tagged immediate values; removing `___boxed` names would not remove heap allocation. Current table indexes use small Nat and borrowed reads. Prior noinline-LowScale and normal-band/fused-classifier investigations remain prior work; no same-route timing restart is requested.
- SUM already uses USize and a fused manual per-input classifier, retaining an unboxed Float32 accumulator and original NaN suffix repair. Its cold Float32 conversions and serial sum dependency remain; there is no new representation candidate just from renaming its loop.

The new bounded discriminator changes only `fastOK` from short-circuit Boolean AND to Boolean equality. The lower rejection domain is `1 ≤ a < 0x0c000000`; throughout it the upper test `a < 0x7f800000` is true. Hence the tests can never both be false, and equality exactly equals conjunction for all UInt32 values. Accepted input domains, arithmetic, table operations, output codec and fallback remain identical. This is distinct from historical narrower normal-band front doors.

Complete source: `Kernel-eager-classifier.lean`, **228099 bytes**, SHA256 **cc9268820d3c9b3c4e664d6a659a12ef259c7c8443db61980a686cad974ea5a5**. `classifier-manifest.json` binds baseline, 100015 Boolean model samples, three proof attempts, and inverse-splice recovery of the exact baseline. All Lean/full-gate/timing status is **NOT_RUN**. Model samples are not a Lean proof or floating-point validation.

Minimal D action: use the normal statement/helper audit and capture exact selected MainFull ADD/MUL accepted paths. Check that both comparisons are eagerly evaluated and that a short-circuit edge is actually removed after optimization. The compiler may already produce equivalent machine code; if so park. If a real path difference remains, one complete D measurement may decide value, retaining all original preparation, fallback, codecs and benchmark costs. Speed and changed branch layout are UNKNOWN. Original full gate and independent D+A+B remain required for adoption.

Resources: CI occupancy 0; local scripts <1 second each; token/output/cache counts UNKNOWN. First rejected direction was duplicate B2 USize; the next allocation tests a distinct scalar control/representation mechanism rather than re-running A4B2, width grids, n=1 cache or R18 U64 arithmetic.
