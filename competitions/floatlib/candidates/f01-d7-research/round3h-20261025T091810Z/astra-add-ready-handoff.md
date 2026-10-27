# R16 high-N ADD entry ready for next compile

Actual source: astra-workers/scalar-representation/next-add-u32/Kernel-add-native-high-draft1.lean, SHA2f998811caa348ad7c0e66026b0d049c6ce0720549dd12622345777d24a1e13e,255913B. public-add-draft1-manifest.json binds source/components and unchanged B2 MUL+suffix. Worker ran the original fixed gate intake/policy/options functions including comments: public-add-draft1-policy.json PASS. NOT_COMPILED.

Root checked the new actual guardedAdd: normal eligible alignment, N>=2^23, one explicitly bound mid/native conversion, full exponent1..254 guard, original fallback for all misses. Opposite equal-exponent cancellation is excluded before unsigned subtraction; it is wholly low-N. New public ADD proof reaches new helpers; no unused-lowh-module dependency. Entire original four-operation gate still required because SUM/BMM replay may use ADD.

Compile exact2f998 first if suitable; only87B margin. Fresh current-source capacity plan in astra-workers/source-budget/add-specific/ recovers2142B from four plain unreferenced theorems, leaves2229B. Do not blindly reuse old36 cuts; no replacement Kernel has been created. If repair requires room, exact byte plan/replay are ready, new source still needs full gate.

Matrix actual-C review is complete: intended numeric loop has no Nat/conversion/alloc/RC, no output recomputation/Float32 boxing bug found. Extra panel/tiles/two closures remain, conditional requested-byte delta32n+160−16G per4rows; timed cause UNKNOWN, new ASM missing. Decision STOP current A4B2 promotion, retain proof; no speculative variant/CI. Full review: astra-workers/matrix-architecture/cost-review-401854.md. Prior full-cost results independently recomputed in astra-first-cost-check.json.

Only ADD is now an active breakthrough candidate. Do not postpone it for unused lowh probing; already-started runs continue. Original12:18:10 deadline unchanged.