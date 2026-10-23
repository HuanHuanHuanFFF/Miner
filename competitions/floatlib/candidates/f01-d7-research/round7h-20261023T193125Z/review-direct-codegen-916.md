# 916 DirectContinuous actual code generation

Read-only audit starting2026-10-23 23:01:05UTC. Run40032766690, commit `123dcd0d7a8da0d089af13d8e736c0709d362fdf`, seed916. All106 original artifact members match their collection size/SHA index. No source/tool/original/Git/CI/agent was changed or started.

**The selected DirectContinuous loops are the actual entry path. The row/index arrays, append and emission closures have disappeared from that path in both C and object assembly. One quotient calculation per row remains in real machine code.** This supports the intended representation change; it does not establish a final adoption or a measured cost share for any instruction.

## Exact binding and coverage

Direct source is248566B/SHA `2aaa5d9e84c758a23a8c6dc1f77d800950fbaa5769aec7a38d299741c17a5f56`; copied input and captured compiled-Submission match. C is1402865B/SHA `e7c209c11aab68734dbaaefa115ef984a535dc6755b1062bc285ec86961c4324`. Snapshot/disassembly metadata bind the same actual statement object,571904B/SHA `53997fdc317e5891aed9f37ebb3239e68fbb0f17ef6be6f913c44a7570ab94f1`. C, traces, nm and selected assembly hashes agree. The original statement builds/links benchFull; later score reads that layer. This is not a diagnostic recompilation. Final linked-image hash/link map is not retained; object copies were removed, so final image inspection/re-hashing remains unavailable.

The exact a302 capture helper selected20 of30 matching symbols. Crucially its first two are:

| Actual specialized body | C lines | Assembly | nm size |
|---|---|---|---|
|`Fin_foldl_loop___at___00Submission_DirectContinuous_output_spec__0`|42617–42643|asm-0-0.txt,689–824|463B|
|`Fin_foldl_loop___at___00Submission_DirectContinuous_output_spec__1`|42659–42690|asm-0-1.txt,693–1012|1104B|

`DirectContinuous.output` C42705 allocates the output then calls spec__1 at42714; spec__1 calls spec__0 at42679. Final bmm dispatch42755–42788 calls this output for n≤4,p>2 and keeps bmmBeforeDirectRows otherwise. Thus these loops are not guessed from a similarly named standalone helper. Standalone row/group bodies were also selected but are not used to infer the actual path.

## Allocations, closure removal and calls

The actual output wrapper reserves batch*m*p capacity once (C42711). Its asm11 normal path calls lean_alloc_object at0xcb, initializes reference count1 and length0/capacity, then calls spec__1 at0xfe. Actual spec__1/spec__0 contain no row-index Array.ofFn, row-output Array.ofFn, Array.append, lean_alloc_closure or lean_apply. No per-row constructor allocation appears in their normal immediate-Nat path.

Inner spec__0 computes baseB+j, calls unchanged NativeFinal.dot once per output (C42631; asm0 offset0x9c), immediate-tags the returned UInt32 with `lea [rax*2+1]` (0xbe), and calls lean_array_push (0xc9). This is not a fresh UInt32 heap box. It passes the sole output accumulator onward without incrementing/capturing it. Fresh reference count1 plus no output alias escaping supports exclusive growth, but runtime copy/reallocation counters and the linked array_push implementation were not captured; do not claim a measured zero-copy result.

The new short path does not map nativeA or pack B. The old5b short DirectRows path also did neither, so their absence is not an additional conversion/preparation saving caused by DirectContinuous. NativeFinal.dot stays a separate object-level call; its inner MAC/NaN-replay machine body is omitted by this20-symbol capture. No new claim about its SIMD, foreign-call count or spill cost is made.

## Division: reduced source work, not eliminated machine work

Spec__0's output-lane loop has no division/modulo instruction. The row loop still computes baseA=r*n and baseB=(r/m)*n*p (C42672–42676). Actual asm1 contains a quotient in the ordinary immediate path: `div r14` at0x129 **or** `div r14d` at0x1a2 depending on operand width, and lean_nat_big_div as the large-Nat alternative. These are alternatives for the same row operation, not two divisions executed per row. The loop back-edge at0x28a returns before this quotient logic, so it was not hoisted out of the row loop. Nat tag/overflow branches and row/column counter arithmetic also remain.

The same-run5b source calls DirectRows for this guard (line6572); DirectContinuous calls its new core (6636). DirectRows previously used quotient and remainder, reconstructed baseA, and created a row Vector/append. The retained DirectRows C body at42389–42439 shows div/mod at42398–42399, closure at42414, row Array.ofFn42421 and append42422. Source DirectRows is byte-identical between916's exact5b and Direct inputs (1191B/SHA `0872645cb4f9ae545b641dd217ea0de263b00ae32f51017b79c6034544c61e13`); NativeFinal is also identical (4114B/SHA `8cdfc6f1885316ae1509f5cddd27694a570258ea667bb3a902cec2a955f20de5`). The new actual path does not call that retained old helper.

**Comparison boundary:**916 did not capture5b's separate object. The old helper retained in the Direct object is a source-backed structural before image, not independent same-run5b machine-code execution evidence. The exact5b control nevertheless has its original same-run full-gate verdict and input source, so the timing comparison is real. Do not assume old div+mod produced two hardware divides, or that old append copied the entire accumulator every row; its same-run machine implementation is UNKNOWN. The long packed RowStream source is unchanged between these sources (10277B/SHA `ac9d1697a62fd34b191ec3cf4907bc3fcfdb6d24cc15b7599c076deb51d8de47`).

## Remaining structural opportunity and falsification

One narrow next representation is **nested batch/row enumeration with the existing column emitter and NativeFinal.dot unchanged**. Carry explicit b and i, compute b*n*p once per batch, and use `(b*m+i)*n` or a row-base increment. This can remove r/m without introducing a new arithmetic kernel or changing NaN repair. Preserve lexicographic b/i/j order, empty dimensions and full Nat behavior; any machine-width fast path would need explicit bounds and the complete Nat fallback.

The first falsification is concrete: original gate statement/proof obligations, then actual entry C/assembly must show no quotient in the row loop and no reintroduced row arrays/append/closure. If quotient remains, or a closure/extra allocation replaces it, the intended structural change has failed. Only a complete same-plan cost comparison can decide whether removing it matters. Do not estimate a speedup from the instruction count.

The already-exposed916 plan has3 timed guarded cases: ml:0(batch3267,m9,n2,p3), sparse:1(batch14705,m2,n2,p3), extremes:0(batch300,m2,n1,p6). They contain59413 logical rows per set of matrices. This shows real row-indexing exposure, not actual process/call counts or timing share; benchmark repetitions and other cells remain part of the complete gate. Empty/big-Nat correctness still requires the original proof/full gate.

Recomputed same-run normalized costs agree with Root: Direct BMM20,329,859ns; versus a06624,936,885ns gives BMM0.815550339/whole0.963487756; versus5b22,883,095ns gives BMM0.891787963/whole0.974986115. These are complete workload-weighted cells relative to each entry's same-run shipped reference, not instruction-level attribution or direct candidate-candidate paired timing. Direct's capture is enabled while5b has no capture; observer perturbation is UNKNOWN. All five public full gates passed, but this single discovery group is not final independent adoption, formal admission or a gain guarantee.
