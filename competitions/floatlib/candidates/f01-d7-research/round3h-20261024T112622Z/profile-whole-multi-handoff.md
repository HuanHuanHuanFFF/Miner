# Exposed-input whole diagnostic

CLI: `profile-whole-multi-entry.py --upstream --kernel --out --plan`. New module is `profile-whole-multi-current.py`; outputs use prefix `profile-whole-multi-`, with final `profile-whole-multi-result.json` and entry `diagnostic-only-whole-multi-verdict.json`.

Original intake/policy/statement builds exactDF once in the official4b7 layer. The entry's initial environment/plan stays seed1224016. The module independently draws official500000 plans for already exposed seeds1224011,1224091,1224092, and runs the same original benchFull binary twice for each. Every process explicitly overrides BENCH_PLAN, BENCH_SEED, BENCH_PAIRS and BENCH_INNER3. Six full-plan processes, no score, no C timers, no recompilation or relink. Module time remains300seconds; each process receives min(120seconds,remaining).

Each original plan/log and156case whole rows/checksums are retained. Checksums are compared only between the two processes of the same seed. Different-seed checksums are never compared. Timed rows retain the original fastest-of-three-sweeps measurement after checksum/warmup, including caller traversal and cleanup. Different process/cache/system context and one shared runner mean these measurements locate cost families, not independent formal performance confirmations.

Original Kernel/C, CPU/proc/config, requested affinity, official source hashes and original object/binary SHA/bytes are retained. Object, binary, C and official sources must remain unchanged through all six processes. No ELF/object bytes are exported. All old frozen scripts, candidates and official sources remain untouched.

Local tests passed on the previous actualDF uninstrumented156case log/plan. Nine negative cases cover missing/duplicate rows, missing plan case, fine/coarse timer contamination, checksum/coverage mismatch, timed flag and zero timed values. AST/interface checks bind the six-process structure and explicit per-process seed/plan override. Original stdout/stderr/exit and source SHA receipts are saved. This is local structure validation only; new Linux runtime is NOT_RUN until the standard runner receipt.
