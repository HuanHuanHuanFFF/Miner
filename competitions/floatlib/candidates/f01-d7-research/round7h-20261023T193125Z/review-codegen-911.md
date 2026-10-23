# 911 actual code generation review

Read-only review of run40027315361, commit `a283b365ff71d981a124d6793eeeddd0102188ab`, seed911. The 103 downloaded artifact members were rehashed against the original collection index: all match. No original, candidate, helper, Git or CI was changed. Exact paths/hashes are in the sibling JSON.

The useful distinction is now visible: **5b7d removes the packed path's output intermediates in its actual entry C, while c477 removes the guarded A map but adds a real call and spills inside each k iteration.** Their discovery timings cannot be added, and neither is an independent clean confirmation.

## Source, object and timing boundary

All four original nested verdicts report `passed=true`, stage `score`, empty reason and seed911, with25 rounds and fixed public-v2. The two captures' compiled-Submission bytes equal their indexed input Kernels: fused `5b7d926cf628c2d87042386834f7c1581b9a6aa7441af196453984b395534ba2` (245841B), rawA `c477e8078eef66255f1c750b46575fc987144717eb1bffc943cf58a514755a6a` (244077B). The summary's `statement_pass=false` field is not a rejecting statement verdict for these full-gate entries; the original full verdict and stage logs establish success.

The capture is from the original gate's actual statement build, not a separate diagnostic recompilation. Captured C, both build traces, nm and selected asm bytes match their metadata/index. Snapshot and disassembly metadata bind the same object SHA: fused `37d22aa81027b94b350eeca9d522c8baa69684d7b04b684e9a89a20aae32ddd5`; rawA `04746ef716b7c7a9db23047eb81f97bd64f1b9c72405af194e4f2a9543b7d1bc`. The C→object trace records Lean4.34.0 clang, `-O3`, `-ffp-contract=off`, x86_64. Objects were removed after analysis, as recorded; they cannot be independently rehashed now.

The saved original4b7 gate hashes to the capture's exact gate SHA `1eb74ef7479b0023c721e776cc5e4073af21c6662b4afffcf16a48a124d27194`. Its statement builds VerifyFull then benchFull before emitting statement success (lines552–566). Kernel/axioms are read-only checks (569–588), and score executes the already-built `BUILD/bin/benchFull` with a read-only build (629–647); it does not recompile. This binds the object/C observation to the original timed gate's build path. **A separately saved final benchFull binary/hash/link map is absent**, so exact final linked-image instruction/address correspondence remains UNKNOWN; do not label these standalone profile objects or claim a retained final binary inspection.

Capture overhead remains UNKNOWN. Both records say snapshot finished before reader-observed score, but original axioms emission timezone/timing is UNKNOWN. Even a preceding copy can perturb caches. These are discovery observations only.

## 5b7d: real output entry is specialized, not the retained generic helpers

Fused C `file-0-Submission.c:41622` core calls output. Output at41583 maps nativeA, packs B, allocates one `Array.mkEmpty(batch*m*p)` (41599), then calls three specialized loops:

`Fin_foldl_loop___at___00Submission_RowStream_output_spec__2` (41537, rows) → `...spec__1` (41401, groups) → `...spec__0` (41191, output lanes).

The actual output-emission loop chain passes a single output accumulator forward. Excluding unchanged A/B preparation, it has no row-index Array, rowTiles Array, per-row output Array, Array.append, closure allocation or lean_apply. The group loop calls runDot's inlined fast guard and exactly one `Packed10Index_loop___redArg` (41461), or the complete Nat fallback `Packed10_dot10` (41513), then emits lanes from that result. The output accumulator is not captured/incremented along this C chain; it is consumed by push and replaced by its result. This supports exclusive growth in ordinary execution, but no runtime refcount/allocation counter was captured, so absence of all copy-on-write/reallocation events is not measured.

The remaining costs are concrete. Actual lane loop41191 performs Nat base/j arithmetic, a lane selector, Packed10.finish and push (e.g.41255–41261). The shared finish at38770 tests result NaN, returns native bits when nonNaN, otherwise calls the original raw NaN replay. NativeA map and packedB allocation remain (41590,41595), and one F10 result object remains per runDot. Signed zero, exceptional payload repair and each output's dot order are not replaced by scalar fast-path assumptions.

**Assembly coverage caveat:** nm has all three real specialized loops: sizes0x673,0x99b,0x24e at nm lines35,37,39. None is disassembled by this capture's selected set. `COMPLETE_SELECTED_SYMBOLS` means all matched symbols, not all hot symbols. The selected standalone `RowStream.group/row` still allocate closures (group asm0, row asm7), but output's actual specialized entry does not call them. Their closure asm therefore cannot establish closure overhead on this timed output path. The actual output asm6 confirms nativeA map, B construction, output allocation and a call to `...output_spec__2` at offset0x1d2. Lane helper asm1 confirms native isnan/to_bits or NaN replay, raw UInt32 immediate tagging (`lea [rax*2+1]`) and tailcall array_push for that retained helper; do not mistake `lean_box_uint32` in C for a per-output heap box on this x86_64 target.

Compared with a066's old RowStream, the old namespace in the captured c477 source is byte-identical to the911 a066 input (1578B, SHA `1d39a2484a942db60d25ba2c9e50f71a1abfcdbcaa823b5a4c980d0dbcc38f5c`). Its actual C retains row indices, rowTiles/ofFn, RowOutput.row and append. This is a valid source-lineage comparison;911 did not separately capture a066's machine object.

## c477: real RawIndex SIMD, conversion and spills

The final dispatch uses rawA only for `n>4` and `2<p≤10` (C42363–42401). Its guarded core has no unconditional global nativeA map: core42276 packs B; the fast per-group path42166–42174 passes raw A directly into RawIndex. The complete Nat/oversize fallback still maps A and calls Packed10.dot10 (42179–42190). It must remain part of all-input semantics.

RawIndex C41812–41887 loads raw A once per k, calls `lean_float32_of_bits` once (41850), and performs ten native mul/add updates. The **actual RawIndex** asm0, lines645–725, confirms:

- Three packed `mulps`/`addps` updates across10 meaningful lanes (two padding lanes in the last vector); no fused multiply-add, matching the compile flag. It is not scalar-only and this evidence is not borrowed from Packed10.
- Inside its0x50–0xc1 k loop, one real PLT call to `lean_float32_of_bits` at0x89. Before it, three accumulator vectors and three B vectors are stored to stack; after it, they are loaded for the updates (lines669–695). The conversion has not been inlined/eliminated in this object.
- No MAC-loop heap allocation, closure, div/mod, or scalar Submission.add/mul call. After the loop, heartbeat plus one48-byte allocation returns F10 (0xd6–0x10d). Input raw words are immediate-tag unboxed (`shr`), not freshly boxed per MAC.

For comparison only, the same capture set contains the old real Packed10Index loop (fused asm9, lines469–523). Its0x40–0x77 loop is also packed SIMD but reads A's nativeFloat object directly and has no in-loop external call or stack spill; allocation occurs at exit. This is the observed preparation-versus-loop tradeoff, not evidence that one wins at every shape.

c477 still retains the old output representation: row div/mod, per-row closure, rowTiles Array.ofFn, RowOutput.row and Array.append (C42208–42244). Guarded A-map removal is therefore distinct from fused output removal. There is no evidence that their two gains compose additively.

## Smallest next representation decision

Prioritize an isolated **DirectContinuous output** check over combining every mechanism immediately. In5b7d, the actual short-dot DirectRows branch (`n≤4`, `p>2`) still creates a per-row closure (C42400), row Array.ofFn (42407), and Array.append (42408), then calls unchanged NativeFinal.dot per output (42354). A continuous output accumulator can target this remaining structural cost while preserving exactly that dot/NaN replay and its arithmetic order. It avoids simultaneously introducing RawIndex's inner conversion/spill tradeoff. This is a concrete opportunity, not a measured gain.

The first discriminating code-generation check would require the new direct output entry to show no row-index/row-output arrays or append and unchanged NativeFinal.dot calls; then use a complete fixed public discovery with observers disabled and held-out confirmation. For packed fused follow-up, the minimal missing observation is assembly of the three actual `RowStream_output_spec__0/1/2` symbols rather than retained generic group/row; no need to enlarge symbol budgets. No helper change or CI was performed here.

For context, recomputation from911 whole/cell totals agrees with Root: fused vs a066 normalized BMM0.921392868/whole0.984803908; rawA0.924388137/0.985416578. Fused BMM scored cost37,781,848ns, rawA37,886,388ns, a06640,949,954ns. Capture makes these discovery results, not clean confirmation. They do not locate costs within a cell, justify performance shares from call counts, or establish new formal ranking/admission.
