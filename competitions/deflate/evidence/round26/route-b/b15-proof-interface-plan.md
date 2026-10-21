# B15 early proof interface plan, no proof/extraction run

Exact production pair: Rust `8974acb8e1c1087d1b4560fd2dc451d8d19c6e3e6f81905b81e9df9a3be4ecdf`, parent Lean `51b5ea83cbad026c044b5c7812c9189231f5273cc0902342c850af02a1c0b592`. Lean465766B leaves58522B policy margin. It is DRAFT, and all extracted signatures/names/time/size are UNKNOWN until a valuable native candidate warrants root's extraction.

VERIFIED inspected original interfaces: `a_tree_insert` and its tree loop have totality specifications; `a_find_all_loop_spec` additionally assumes input length<67108864, skip≥3 and guards its indexing; A DP keeps cost/ch vector lengths, input/position bounds, XL≤258, XD≤32768, old record prev≤i+258/pd≤32768/bd≤32767. `a_walk`, emission/check and the public obligation chain remain original source. DP optimality is not the contract proved by these original specifications.

INFERRED compositional plan if worthwhile: first prove `r26_a_discard_offer` code%32 bounds and bounded touched-count update; then `r26_a_discard_finish` loops with k<count&&k<32/n<32, returning n≤32; then the pure controlled consumer with result bd≤32767 and original vector lengths unchanged. Its record loops retain i+2≤prev≤i+258, while l≤hi≤stop-i and stop<cost.length establish each cost index. Ordinary U32 arithmetic stays wrapping; no fresh nonwrap or packed-optimality theorem is needed for totality.

The changed tree returns `(original_best,new_count)` and mutates only new scratch/pending in addition to original state. Its exact extracted return tuple will likely change the old WP continuations; adapt from the actual interface rather than guessing tuple ordering. The finder append loop must prove pending index<32 and leave original CD read before append. Its graph semantic preservation is checked by the finite actual native graph observer, not silently inferred from a totality proof.

The new DP suffix-strip loop can use decreasing end and invariant end≤top≤mb.length; guard end>j0 implies end≥1 for mb[end-1]. Original record loop receives the stripped end bound. Keep the original XL/XD/store-choice proofs, adding only new helper call/bd bound. Do not broaden simplification to the whole generated loop or extend the original global gate timeout in advance.

Proof and performance decisions remain conditional on B15 actual quality and complete-cost feedback. No Lean source edited, no official extraction/obligation/gate/native result claimed here. New helpers still need fresh extraction, exact original obligation, axiom whitelist and round trip before any accepted pair exists.
