# 914 BatchLocalPacked lifecycle

Read-only review starting2026-10-23 22:33:22UTC. All106 original artifact members match the saved size/SHA index; none was changed. Run40030638967, commit `26b892ee39467f268b00cc4f105840a5b72bf8f5`, seed914 contains five original full-gate PASS verdicts. This report concerns exact28af `f01-d11-bmm-batch-local-output-proof2`,254436B/SHA `28af18b4ba270203a44e2cda950967a51475fc592d92b5f026f5bca43498a8e1`.

**The intended per-batch packed lifetime is present in actual generated C. There is no evidence here that the whole packedB table survives across batches, or that output sharing forces copies.** This is C ownership-path evidence; actual allocator/RSS, specialized assembly and cost attribution remain UNKNOWN.

## Binding and actual entry

The captured compiled-Submission bytes match the indexed input and summary Kernel SHA. C is1447456B/SHA `1807cee367ddaabe255d6654ef392125847491a0b245287d7498c8f25ec7b9f3`; object metadata binds `d9a9330c88f078d264550e732183f87fe8aa899ed5338e1f504c9501936d41b2` (598944B). C/traces/nm/all20 selected asm bytes were cross-checked against metadata. This is the original gate statement object's capture, not a diagnostic recompilation. The trace records Lean4.34.0 clang, -O3 and -ffp-contract=off. The fixed original gate builds benchFull in statement, then uses that layer read-only for later stages. Final linked benchFull hash/link map is not retained, and private object copies were removed as recorded.

Actual C `Submission_bmm` at43672 dispatches to the new output only for `n>4`, `p>2`, and `batch*m>0` (43711). Empty outputs and other routes keep bmmBeforeBatchLocal. The new hot chain is:

`BatchLocalPacked.output`43603 → `Fin_foldl_loop___at___00Submission_BatchLocalPacked_output_spec__0___redArg`43561 (batch) → `BatchLocalPacked_batchStep___redArg`43511 → `...batchStep_spec__2`43460 (rows) → `...spec__1`43327 (groups) → `...spec__0`43117 (lanes).

This matters because standalone `BatchLocalPacked.group/row` also remain in C but are not the actual specialized emission chain. Do not infer their closure behavior onto the entry.

## Construction, borrowing and release

At43519, batchStep calls `packBatch___redArg` once. At43521 it runs all m rows with that same packed value. At43522 it calls `lean_dec_ref(packed)` immediately after the row fold returns, before returning the new output to the outer batch loop. The outer batch loop carries only output plus immutable inputs/nativeA; the next batch is constructed only on its next43581 call.

Group access is borrowed (`lean_array_fget_borrowed`43341); the result F10 is passed to lane emission and decremented at43399 after emission. The row/group/lane specialized loops do not increment or capture the packed table, return it, or store it in the output. Packed packet construction at38599–38610 creates a zero-object-field record holding ten floats, so these packets do not contain back-references to B or another packed table. The source-level packed tree can become unreachable at43522. This does **not** establish that mimalloc returns its storage to the OS or that peak RSS falls by any measured amount.

Raw B remains alive across batches (outer loop owns it for reads and exact NaN replay), and nativeA is still a whole-input map at43610, released after the complete outer fold at43618. Those retained input representations are distinct from retaining all packed batches. The lifetime change reduces the live packed representation from all batches to one batch; it does not remove raw B/nativeA or the full output array.

## Output ownership and closures

Output is allocated once with full capacity batch*m*p (43614). The actual specialized emission chain has no Array.ofFn row-index/row-output arrays, Array.append, dynamic closure allocation or lean_apply. The output parameter passes to the next specialized fold or push without an increment/capture; e.g. lane43293 consumes it and43304 carries the returned array onward. Static ownership supports exclusive growth; no copy/refcount/allocation counter was captured, so “zero runtime copies” is not measured.

Dynamic closures remain in **preparation**: packBatch42580 allocates a group constructor closure, and Packed10_packB's reused group constructor38632 allocates the k constructor closure before Array.ofFn. The total packet/conversion work across all batches is still proportional to batch*ceil(p/10)*n; only preparation scope/lifetime changes. Each row/group still computes its own runDot F10 and runs per-output finish, including original raw NaN replay. Actual emission keeps Nat index arithmetic, lane selection, native result classification and push. NaN payload repair and output order are not replaced by an approximate fast path.

## Assembly boundary

The oldfc capture has20 selected asm symbols and **zero BatchLocalPacked specialized bodies**. nm does contain actual batchStep_spec__0/1/2 and output_spec__0/its redArg body (lines33,35,37,39,41). Machine-code placement of the pack/decrement calls, closure lowering, specialized spills and output-copy behavior is therefore UNKNOWN. Old RowStream asm is not evidence about these bodies.

Read-only selection replay confirms the later a302 helper recognizes all five exact nm names at hot priority; no helper/tool was changed here and no new objdump ran. This establishes name coverage only, not a new capture or new machine-code result.

## Cost interpretation and disposition

Recomputed from the original complete26-cell work/times: target BMM54,162,942ns versus a06657,964,512ns, each normalized to its own same-run shipped reference, gives BMM0.934766171; whole ratio gives0.982730039. Target BMM is25.3065% of its scored whole total214,027,993ns. The modest whole change is arithmetically consistent with improvement confined to a roughly-quarter share of the complete cost; no hidden output-copy bug is needed to explain why a6.52% BMM difference does not produce3% whole improvement. This is whole-cell accounting, not a preparation/compute/replay profile.

Root's saved discovery result reports p05=0.0039872451601251635 and screen=false for this a066 comparison; bootstrap was not rerun in this C review. The a066-relative headline is above0.97. That is distinct from the fixed retained41 admission comparison and does not itself decide formal or three-group adoption against41. Capture is enabled, so this run cannot serve as clean D/independent confirmation regardless of its ratio.

914 includes21 timed cases taking the new guard:9 have batch1 and12 have multiple batches. For batch1, there is no multi-batch packed-retention saving; this is an opportunity boundary, not a timing share. For example the already-exposed sparse:1 shape(batch5347,m1,n11,p3) has source-level packed F10 value counts58817 across all batches versus11 live in one batch. That does not measure allocator calls or gains. Raw inputs, nativeA, all packet work, and global output still exist.

This candidate combines inherited continuous output with batch-local packing. 914 has no exact5b7d control, so its comparison to a066 cannot isolate the batch-local contribution. In particular, comparing this0.934766 to911 fused0.921393 across different seeds cannot establish a regression.

**PARK as a standalone incremental a066 upgrade for now.** The C verifies the intended lifetime and shows no corrective ownership bug to fix, while the incremental benefit beyond continuous output is unmeasured and the a066 whole comparison misses3%. The smallest next discriminating observation, if this route is revisited, is a same-plan comparison with exact fused-only control plus assembly of these actual specialized names; do not create another Kernel merely to remedy an alleged all-batch retention that this C does not show. No new experiment, tool change, candidate or CI was performed.
