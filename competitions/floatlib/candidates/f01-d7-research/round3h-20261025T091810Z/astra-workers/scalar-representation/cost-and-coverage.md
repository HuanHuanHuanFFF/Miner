# Native repack opportunity, 2026-10-25

Current draft is `c972fd72694d4d7db4660d2dbcd640d766d013d58bd9c9a27a6c68d47010b7ac`, 247533 B. `source-manifest.json` binds B2 and the reused full-gated R14 mathematical modules. Correctness/gain remain NOT_RUN until the original runner verifies this exact source.

## Mechanism and fixed native cost interface

The fixed Lean runtime implements UInt32→Float32, UInt64→Float32 and Int64→Float32 as `static inline` C casts; Float32 MUL and self comparison are inline. `Float32.toBits` is an external function performing a NaN check and bit cast. The candidate **retains** that boundary; it does not claim to eliminate bit conversion or make the loop a single instruction. Exponent/sign guards, field arithmetic, cold fallback and caller register pressure remain real costs.

The normal B2 MUL expression contains two exact mantissa casts, two borrowed scale-table reads, two exact scale multiplications and the final multiplication. The candidate keeps the two casts and final multiplication, then reuses its already-rounded exponent/fraction. The table reads do not allocate new Nat or Float32 objects in the fixed path; the benefit is removal of reads and arithmetic, not an unsupported allocation count claim. The fixed legal native-model bridge supplies semantics for the actual multiply. No Float64 narrowing bridge or new axiom is required.

Primary implementations read: Lean commit293d5d0c, `lean.h` lines3253–3271; `object.cpp` lines1987–2004; FloatLib0d918 Narrow Base/Runtime and Agreement, Model/Lean field lemmas. Original authors Microsoft/Leonardo de Moura (Apache2.0) and FloatLib Team (MIT); source receipts already preserved under R15 `public-source-runtime/source-index.json` and the original fixed-source directories. No external runtime implementation was copied into the candidate. Exact selected R16 caller machine code and dynamic costs are UNKNOWN.

Additional exact-baseline check: B2 diagnostic run40168024176 input SHA622d and both saved C hashes were rechecked. When `BENCH_PLAN` is present, `_lean_main` passes `closed__5` into `Bench.Suite.run`; that closure selects `lp_competition_main___lam__3___boxed`, then the unboxed `lam__3` body at original MainFull.c line2108. **Do not use lam__1 as the public-suite selected body** merely because it is another MUL wrapper. The selected lam__3 is42488B, SHA `df0bf6e3cc3388e145a292a9bb21526ae8d7b52045df4fb38354a48889935d0e`; its complete body has2 cast,2 table-read,3 MUL,1 self-beq and1 toBits sites, and0 explicit ctor-allocation or lean_apply_2 sites. `b2-caller-review.json` and unchanged extracted bodies retain the evidence. This establishes actual B2 diagnostic implementation/caller structure; it does not establish current R16 machine code, dynamic frequency, or timed ELF identity.

**A material cost distinction to check:** the B2 normal C arm assigns `toBits(result)` and immediately returns it, so the call is in tail position. c972 must do exponent/sign repacking *after* `toBits`; at least the original exponent sum and sign must survive that external call. Whether B2 actually tail-calls and whether c972 incurs additional saves/spills are currently UNKNOWN. The saved B2 object compilation uses fixed Clang `-O3 -ffp-contract=off` with no `-flto` in that command; `lean.h` declares toBits externally, so source-level reasoning must not assume it disappears. This is the first assembly distinction to inspect if the new arithmetic removal yields less benefit than expected.

The earlier two-multiply/one-table combined-scale form keeps final `toBits` in tail position and avoids live raw fields afterward, but retains an extra table read and multiply. It is a different cost tradeoff, **not currently built or queued**. Revisit it only if the exact c972 generated machine code and complete timing expose this call-boundary cost as a useful discriminator; do not start near-variant proof work merely on a hypothetical spill.

## Broad but conditional input exposure

`exposed-coverage.json` uses exactly three completed R14 public draws, 256 deterministic strata per timed MUL case, **32256 sampled pairs**. It never reads current R16 confirmation data. The worker had an enforced5s timeout and finished in0.319s. An initial30000-pair guard failed because the three plans each have42 rather than the presumed fewer cases; its source/stderr remain as attempt1. The second bound33000 follows the verified finite plan count, with no change of operands, seed or acceptance criteria.

| Already exposed run | Dense eligible | ML | Paired | Sparse | Old DF MUL share | Count-weighted whole proxy |
|---|---:|---:|---:|---:|---:|---:|
|40129155932|98.18%|100%|100%|51.24%|36.33%|26.48%|
|40152158687|94.73%|100%|100%|31.45%|38.71%|30.60%|
|40155753018|98.11%|100%|100%|36.33%|34.40%|26.22%|

These observations establish that the guard can cover broad ordinary scalar multiplication in these already-seen source-model draws. They are not cycles, exact B2 weighting, a formal generator agreement, or future hit probabilities. The final column multiplies old per-cell DF time by sampled eligibility and therefore assumes equal cost per pair within a cell. It is only a prioritization proxy: if eligible work cost fell40%, the corresponding proxy would suggest roughly10–12% whole improvement before additional guard overhead. Neither the40% decrease nor this cost model has been measured. A minimum3% whole adoption would need substantially less but still must pass original D/A/B.

## Distinct historical outcomes

R14 `native-exponent1` 913d715b did not compile. It has no performance verdict. Its modular whole-word proof and concrete native/model proof were removed from this candidate. R14 `mul-cache-rse2` 9038f8d6 full-gated different software-RSE runtime and was29.08% slower for MUL; R15 f529 software bit-flag variant was70.26% slower. Those records constrain the corresponding implementations. They supply checked mathematical components and warning against source-operation-count forecasts, not measured rejection of this native repack.

Remaining deciding evidence: actual Lean statement/helper dependency audit, full original gate/checksums, selected public caller C/asm, then complete paired D measurement with preparation/fallback included. Do not expand to native Int64 or aligned ADD merely because this draft exists; compile feedback and selected-caller evidence are the next discriminator.
