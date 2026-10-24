# R11-W03 candidate note: bounded shared-B n=1/n=2 specialization

Status: **Lean NOT_RUN; target C/assembly NOT_RUN; full gate NOT_RUN; full-call timing UNKNOWN**. The exact uploaded Kernel was extracted without changing its LF bytes and matched the declared SHA. Source inspection and byte/patch checks are the evidence here. The original R11 source is itself not established to compile; this patch does not repair its unrelated proof-wiring obligations.

## Artifacts and actual budget

Base Kernel SHA256: `4bdd1e7db35cd85e17d06511721d5dbf7f654ec12e58633264b08a086ec54fa0`; 252609 bytes.

| Variant | Full file | UTF-8 bytes | Delta | Remaining at 256000 |
|---|---|---:|---:|---:|
| A: inline arithmetic in bounded loader | `Kernel.short-shared.lean` | 254458 | 1849 | 1542 |
| B: scalar-only worker calls | `Kernel.short-scalar-call.lean` | 254712 | 2103 | 1288 |

A SHA: `5645b861ce6eeaa00cbb80a791dcb225dca75463f1816ca051d52fe6b62ba910`.
B SHA: `4d778479f3c97c9793678b5f9e1d5742fe6190344d406ef3c9fef7b0ac86595e`.

Both unified patches target `Kernel.lean` at the existing `dot8` / `dot8_lane` block near original line 6609. The byte count is for this exact base plus this patch only. It does not reserve space for concurrent W01 proof repairs. Recount the actual combined final file.

The two alternatives are one bounded-specialization family with different compiler scheduling/ABI probes; they are not two new mathematical algorithms. Do not apply both patches together. The current source calls preparation `pack`/`packShared`/`packGeneral`; there is no declaration literally named `localP12`.

## Mechanism and scope

At `dot8`, use the specialization only if `(n=1 ∨ n=2) ∧ b1=b0 ∧ b2=b0 ∧ b3=b0`. This reuses the existing all-four-row shared-B condition exactly. Other shapes and every mixed-base group retain the existing packed path. The outer BMM dispatch, words/output writer, terminal finish8 and four specifications remain untouched.

`shortShared` takes actual raw arrays, raw A row bases, B base and p. For n=1 it obtains four A and two B native values. For n=2 it obtains eight A and four B native values. The second slice is decoded before constructing any partial accumulator. The two B offsets for the second slice are `b0+p` and `(b0+1)+p`, so the helper's proof works for arbitrary p, although this BMM route selects p=2.

Variant A has inline `read32` and `shortShared` helpers. It spells all native scalar values and all eight initial accumulator expressions as local bindings. There is no Vector P12, P12 constructor, array builder, closure argument, intermediate F8, or recursive inner loop in the selected branch. Only the terminal F8 is constructed. This is a source-level statement, not a guarantee about how Clang will schedule it.

Variant B moves only arithmetic into direct `shortArith1` and `shortArith2` calls marked Lean `@[noinline]`. The workers take only Float32 values, including +0. The n1 worker has seven float arguments; the n2 worker has thirteen. If a direct out-of-line x86-64 System V call survives, n1 fits eight scalar SSE argument registers and n2 needs five stack scalar arguments in addition to eight register arguments. That stack traffic is a real candidate cost. It is not a heap Vector and does not itself box every scalar. Its actual ABI must be checked on the target triple and actual generated C.

**Important compiler limit:** the pinned runtime audit found that Lean's `@[noinline]` controls Lean-level inlining but pinned LCNF `EmitC.emitDecl` emits `LEAN_EXPORT` with no native C noinline attribute. Clang may inline these workers at -O3. Therefore Variant B is not an enforceable machine-code barrier, and the conditional 7/13-argument ABI count cannot be asserted for the final assembly without inspecting it. A caller containing interleaved decode and arithmetic after native inlining is a failed conversion-free-region hypothesis, not a Lean semantic failure.

## Exact operations and proof reuse

For each row r and column j, n1 keeps `+0 + a[r,0]*b[0,j]`. It does not replace it with the product. The negative-zero case therefore retains the required initial addition. n2 keeps `( +0 + a[r,0]*b[0,j] ) + a[r,1]*b[1,j]` with two separate binary32 multiplications and two separate additions. No partial-sum tree, reassociation or FMA is introduced.

The helper returns columns in the original F8 order: s0..s3 are column0 rows0..3; s4..s7 are column1 rows0..3. Existing finish8 calls Packed10.finish in row-major `(s0,s4,s1,s5,s2,s6,s3,s7)` order. The existing non-NaN conversion, raw NaN replay, W8 UInt32 construction, rowWord extraction and exact ofBits32 reconstruction are reused byte-for-byte.

The included `shortShared_lane` proof draft has symbolic raw arrays and all symbolic raw words. It enumerates only sixteen control cases: two supported n values times eight lanes. Within each case it unfolds the actual `NativeFinal.dotLoop`, actual `read32` using `Array.getD` and `ExecFloat.Binary.toFloat32`, actual scalar arithmetic helper, and concrete lane/select4 definitions. This is a finite-control symbolic proof plan, not finite testing of floating inputs and not an abstract read premise.

The dot8_lane proof splits its actual runtime predicate. The positive branch destructs equal B bases and invokes shortShared_lane. The negative branch is the old `wordLoop_eq` → `natLoop_lane` proof unchanged. All downstream statements can then continue to reuse `dot8_lane`, `blockAt_word`, `blockRows_word`, `rowWord_eq`, `core_eq_rows` and the original bmm_spec chain.

No sorry, axiom, unsafe, extern, implemented_by, API replacement or changed option is added. This does not establish that Lean accepts the simplifier proof. The exact remaining new proof obligation is whether the listed simp definitions and `Nat.add_assoc` discharge the symbolic actual-dotLoop equations under pinned Lean. Any residual normalization target should be repaired as a concrete equation, not assumed. Existing base proof errors remain separate.

## Nat, machine and tail boundaries

The new branch has no USize indexing and uses the same total `Array.getD` reads as the original pack definition. It needs no extra machine-range premise. Existing `hn : n<USize.size` remains needed by the packed fallback and is unchanged. n=0 never takes the new branch; m=0, p=0, batch=0 or fewer than four rows cannot enter the current outer specialization. They retain the original dispatch behavior.

For p=2, n>0 and m>0, all B bases coincide exactly when the four flattened rows lie in the same batch: `floor((4g)/m) = floor((4g+3)/m)`. Thus m=1,2,3 produce no selected groups. Mixed batches are not aliased. Every incomplete final group has at least one row beyond the final batch boundary and stays in the original total-read fallback. The original arithmetic/read behavior for those unused rows is untouched.

Illustrative exact row-index counts, calculated by a Python integer enumeration and recorded in shape-coverage.json:

| batch | m | total groups | selected | fallback |
|---:|---:|---:|---:|---:|
| 4 | 1 | 1 | 0 | 1 |
| 2 | 2 | 1 | 0 | 1 |
| 4 | 3 | 3 | 0 | 3 |
| 4 | 4 | 4 | 4 | 0 |
| 4 | 5 | 5 | 2 | 3 |
| 2 | 6 | 3 | 2 | 1 |
| 2941 | 15 | 11029 | 8823 | 2206 |

These are counts of groups, not benchmark weights, allocation timing, or speedup predictions. In particular, 8823/11029 is not a recoverable fraction of the old 14.81% timing exposure.

## Smallest discriminating target checks

1. Check the exact base and one exact patched source under the pinned Lean and official options; do not trust this source inspection as compilation. The inherited R11 proof has to compile too.
2. Emit C for the full exact candidate. For the selected loader path verify no P12 constructor, no array construction, no generic closure call, and no `lean_box_float32` at worker arguments. Verify native add/mul compile to float primitives. The fallback still legitimately contains P12 allocation.
3. Compile that generated C using the exact official Clang22.1.4 invocation, -O3 and -ffp-contract=off, without -march=native or new native flags. Record exact triple, compiler identity and argv. Inspect both worker and callsite if B's workers survive.
4. For the actual n2 path locate every of_bits call and the two ordered mul/add stages. Check whether there is a conversion-free arithmetic region, whether workers survive as calls, how many argument stores/loads occur, and whether SIMD requires expensive packing/shuffles. Terminal F8/W8 allocation and output reconstruction must remain counted.
5. Run unchanged exact gates and complete paired full-call timing only after correctness. Measure preparation, every group including mixed/tail groups, destruction, finishing/replay and output. Include n1/n2 m4 as the mechanism-positive case; m1/m2/m3 and m5 tail/crossing as negative boundaries; longer n cases reveal added predicate overhead. Keep raw NaN replay and signed-zero cases in correctness checks.

The cheapest falsification is at stage2 or3: hidden per-scalar boxing, selected-branch P12 allocation, conversions between the two live-accumulator stages, or stack/shuffle traffic comparable to the removed preparation. A clean call-free SIMD body still is not adoption evidence: old 2x4/2x8 already demonstrated why complete-call cost governs.

## Costs that remain

The source branch removes the shared group's n P12 objects, the n-slot backing Array and corresponding preparation/consumption/destruction machinery. The Vector wrapper's proof erasure must not be double-counted as another allocation. Input conversions are not removed: they stay at6 per n1 shared group and12 per n2 shared group, excluding +0 constant setup and finishing. All original terminal isNaN/to_bits work, one F8 unless optimized away, one W8, output Vector, raw replay, batch/m division and tail work remain.

Every group now evaluates the small-n predicate. A mixed short group may also repeat all-same-base tests in the fallback pack. All long-n groups incur the new n predicate even though they cannot benefit. These effects require whole-call measurements. No measured gain is claimed.
