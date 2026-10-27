# Current selected B2/DC path already has no row-closure site in exact saved C

New DeepSeek message `20261026T203000000Z-r19-relax-negative-loop-test.md` assigns the rowLoop/emitLoop experiment independently. This worker does not duplicate it. The reported experiment should finish; this note corrects its proposed causal mechanism, not its eventual measured result.

Freshly rehashed source from run **40168024176** is exact retained `622d8394…a58`; its generated Submission C is **0e3c1fc9ee2b91c326fffa847a60350031e7260bb860ed8a6f62df5f2eee7268**. This is an archived pinned statement/bench-build diagnostic, not the current timed executable. Script, exact source paths, function text hashes and excerpts are in `check_selected_closures.py`, `closure-evidence.json` and `closure-evidence/`.

| Active generated caller path | Original C lines | Closure allocations in these bodies |
| --- | --- | ---: |
| Public bmm → B2 dispatch → B2 output | 42953 → 42773 → 42696 | 0 |
| B2 output → specialized row fold → specialized group fold → specialized emitter | 42696 → 42652 → 42569 → 41854 | 0 |
| bmmBeforeR11Cross → DirectContinuous output → specialized row fold → specialized emitter | 40936 → 40886 → 40840 → 40798 | 0 |

By contrast, `Submission_DirectContinuous_row___redArg` at **40729** contains one six-capture closure followed by generic `Fin.foldl`. That generic wrapper is present in the translation unit but is not called by the selected DirectContinuous output chain above. The same distinction applies to inferring current B2 behavior from an older `RowOutput_row`. Source-level lambda syntax and a generic wrapper's allocator do not establish per-row allocation on the specialized production route.

Thus “new rowLoop has no alloc_closure” is not sufficient evidence that it removed an original per-row closure. The claimed 198000 rows × 30–100 ns cannot yet be an estimate of recoverable closure cost. A complete-cost win could still arise from changed address placement, fewer Nat operations, code layout or other generated behavior; only the actual old/new selected callers and complete measurement can distinguish these possibilities.

The original B2 preparation **does** still allocate closures/arrays in packB; this note does not say the whole BMM has no closures. It also does not remove the terminal F2 object or dynamic two-lane emitter, which remain the separate target of backup `764615ad`. No candidate, predicate, queue or official file was changed; active CI must be collected normally.
