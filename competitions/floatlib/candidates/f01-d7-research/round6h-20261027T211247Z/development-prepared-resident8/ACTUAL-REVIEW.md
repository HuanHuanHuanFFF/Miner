# Actual16-lane diagnostic: mechanism partly realized; runtime PARK

Exact combined source fd4e5b5144d00f3413b0b367a748e9be8f55d51017b4a8aaa5be53d404b1d6c1,242358B, run40607316341. `resident16-actual-review.json` binds every input, all16 control blocks,156 checksum cases per pair, selected C and captured native tile. No new kernel/build/CI/seed was run by this worker.

**The C layout premise is realized.** Actual selected Submission C63e1d08f matches the prepared timed dependency; measured linked Submission.o7dbe4419 matches the captured native object and remains unchanged after timing. `wordLoop___redArg` has16 native float parameters, two borrowed array reads,16 native multiplies and16 adds. Its nonterminal backedge has no codec, Float32 box, container allocation, dynamic apply or Nat arithmetic; the terminal arm allocates one64-byte scalar-payload Acc. This is actual C evidence, not a final-register/SIMD conclusion.

Actual tile ASM calls wordLoop out of line, passes the additional8 FP arguments through64 bytes of stack, uses184 bytes of local frame, loads/saves16 terminal floats and finishes real lanes separately. The requested wordLoop/runDot ASM functions were omitted from capture; therefore actual SIMD width and hot-loop spill remain **UNKNOWN**, not zero. Tile stack costs are terminal/ABI work and cannot be called per-k spill. Words construction has an exclusive-reuse branch for the returned Acc plus allocation fallbacks; two static allocation sites do not imply two dynamic allocations. Reuse frequency was not instrumented. A/B records have direct native Float32 fields; packA and B-group conversion calls remain in preparation.

Actual caller prepares B once per complete call and A once before each current four-row group's column closure. It still allocates cold closures for packA, B-group construction and Vector.ofFn tiles; none is in wordLoop. Four output folds use the small Words cache. Raw tail dots, per-lane finish/replay, padding, output/RC and destruction remain charged. A miss calls retained public bmm after the new outer UnderflowZero check, so that scan can repeat; current miss costs are near1 and do not establish a large loss from it.

| Seen pair | BMM | Static eligible case sum | Static miss sum | Whole |
| --- | ---: | ---: | ---: | ---: |
| seed2220001,12→13 |0.995805|0.991297|0.997191|1.028642|
| seed2220001,15→14 |0.999984|0.989180|1.003324|1.027560|
| seed2220003,12→13 |0.959830|0.882424|0.997500|1.015458|
| seed2220003,15→14 |0.959165|0.880943|0.997354|1.008056|

Seed1 p9 dense0 is1.380/1.356 and sparse2 is1.104/1.110, offsetting gains including p4 n118/145. Their retained baselines differ: p9,n8 is old packed/F10; p9,n3 is direct. Seed3 has gains in p4/7/8, while p60 sparse5 is1.500/1.478. This does not isolate padding, tail, closure or ABI causality. p5 dense2 improves despite extra padding, so padding alone cannot explain all variation. All cases and slow samples remain in JSON.

All8 control blocks per seed are retained: BMM max/min1.01207/1.01368; ADD1.03674/1.05603, MUL1.04026/1.02659, SUM1.05889/1.02796. Untouched operations change, so whole regressions cannot be assigned wholly to BMM; replacing them with hypothetical equal times would be a counterfactual, not a measured score. Current public full-gate/adoption and private-suite distribution remain UNKNOWN/NOT_RUN. Decision: retain exact source/interfaces and negative full-cost evidence; no width/threshold/seed retry or large proof port.
