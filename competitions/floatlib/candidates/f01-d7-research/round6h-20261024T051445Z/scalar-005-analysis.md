# 005: converter discovery supports a clean full-gate follow-up

Exact59de passed the original complete25-round public-v2 gate in run40071334389, source `942de9af530fbde144769a3e855660932348db6c`. Current6c and frozen41 controls also passed. Original hashes, complete workload-weighted totals, all cell ratios and the2000-sample bootstrap are rechecked in `scalar-005-analysis.json` by the adjacent read-only script. No source, model or dashboard was changed.

| Whole-source metric | Value |
|---|---:|
|59de/reference divided by6c/reference|0.9340766499314178|
|Bootstrap gain p05|0.011459293030507856|
|Sample role|Observer discovery; ineligible cleanD|

| Operation | Workload-weighted normalized59de/6c |
|---|---:|
|add|0.9764174975|
|mul|0.8463138155|
|sum|1.0120845367|
|bmm|1.0116914976|

All7 mul cells improve in this sample, ratios0.8111–0.9147. These compare separate original paired candidate/reference gates, normalized through the corresponding6c/reference gate. They are not directly paired59de/6c sweeps. The numeric discovery threshold is met, but observer capture disqualifies this sample from cleanD and independent confirmation. No adoption is claimed.

The actual59de MainFull C is89004B, SHA `6a22c49cdabae2de3dc3996d993f7abc4acd97bd5d3cda41e078c01660d3377f`; actual object SHA is `9121950b944d8256d38dddfa33502caf23ea356740e58870aec716d4fb5815a3`. Capture is bound to exact compiled59de, original C/trace bytes were rehashed, selected asm hashes match, and private ELF copies were removed. Final linked binary bytes remain unretained/UNKNOWN. Public BENCH_PLAN still selects closed5→main lam3 boxed→lam3; lambda1 remains the legacy non-plan mul closure.

Actual public lam3 is1018B, up from current6c's870B. After the exsum gate, the two-converter numeric-hit path is0x26→0x1e5→0x20b→0x27c→0x2a5. It performs two UInt32 numeric casts and signed scale-table multiplies, then native multiplication/self-ucomiss. **This warm path executes neither input of_bits foreign call nor the float spill/reload.** The result to_bits tail remains at0x2be. Per-input window tests, table loads, extra scale multiplies, register saves and16B stack reservation also remain.

That conclusion is branch-specific. The complete function still has of_bits fallback relocations at0x4d and0x233; the second-input fallback retains the float store/reload at0x22c/0x237. It would be wrong to say all bitcasts or all stack use disappeared. The original exsum<128 LowScale branch is at0x24→0x59, before either new converter test. Its source definitions/tiny routing are preserved; prologue/register allocation changed, so identical source does not establish identical LowScale cost.

The unmodified add lam0 C body and selected asm body were independently compared with the exact original6c capture and are identical. Yet add is about2.36% faster after normalization in this run. That movement limits causal attribution: environment/reference variation or linked layout can still contribute, and the full6.59% whole improvement must not be assigned solely to the converter. The active warm-path mechanism is verified; stable net gain is not yet confirmed.

The next useful step is exact59de on the original complete gate with no observer, retaining current6c and41 controls, then frozen independent groups if the clean discovery qualifies. Do not alter this favorable candidate or start a converter grid. The R4 legacy negative remains preserved; the new LowScale domain and current public suite are the reasons for this one controlled revisit, not grounds to erase that history.
