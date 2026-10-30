# Batch 4 helper-only terminal review — run 40964374666

The run completed successfully at 22:20:12 UTC from source commit `8537d5133bbd04c8b709b4ef2233696b0a7fabfb`, using official head `27fb1d19c712ead50ad34b4ad0d4ba597161e616`. It processed four standalone helper diagnostics only. The plan and runner hashes were frozen in the dispatch receipt; the run head matches that receipt, and the artifact `plan.json` matches the frozen plan hash. The current checkout's `ci-plan.json` now contains batch 5 and differs, but the saved batch4 plan copy and artifact remain bound to the run.

The independent manifest audit passes 11/11 outer artifact files and 10/10 inner files. No source-shaped files were uploaded. The run reports proof identity `3a69968c…77bee6` and current benchmark identity `6df065ba…f3faa5cd` under the new official head. It has no candidates, no full-gate entries and no candidate or reference timings. `complete=true` means all requested diagnostics were collected; the overall CI success is not a candidate correctness result.

Helper results from the saved raw logs:

- `prepareagreementcontractonly`: exit 0, five roots, only the allowed axioms.
- `word_modular64_v3`: exit 0, four roots, only the allowed axioms.
- `reciprocal_u64_v3`: exit 1, nine elaboration errors; `sorryAx` appears in three of four printed root axiom sets.
- `guardednonzerocontractonly`: exit 1, a type mismatch at line 505; `sorryAx` appears in four of six printed root axiom sets.

These are standalone helper results, not the full twelve-obligation gate. The plan references public #12 for helper context, so this batch does not validate compact-reciprocal integration on current public #23 or change the current #43 performance estimate. The source-level failures and axiom sets are preserved in the helper logs and [audit-helper-run-40964374666.json](audit-helper-run-40964374666.json).
