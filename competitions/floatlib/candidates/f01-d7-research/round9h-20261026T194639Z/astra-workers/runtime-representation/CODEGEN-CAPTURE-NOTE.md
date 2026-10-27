# MainFull capture gap affecting the classifier discriminator

Observed 2026-10-26 20:26 UTC in D-owned `competitions/floatlib/candidates/f01-word-tensors/ci-diagnostics.py`, SHA256 `ab39ab4f07ad4d7ffdff43a7e8adfb8c3852d3951c51fe63137400d43d2b8928`; this worker did not change it.

- The object loop accepts only file names containing `Submission`. The symbol filter then accepts only `lp_competition_Submission_…`. Consequently the selected MainFull ADD/MUL lambda bodies are not captured by this path. The stored MainFull C is useful, but optimized branch removal or identity between the old and eager classifier remains UNKNOWN without the selected object's ASM.
- The listed `lp_competition_Submission_R2W01b_fastOK/convert` names do not match retained C namespace `lp_competition_R2W01b_…`. Even correct standalone-helper capture would not substitute for the inlined selected MainFull caller.
- Current `objdump -d --no-show-raw-insn` drops relocation records and encoded bytes. That is enough for some opcode observations, but unresolved ET_REL call targets/constants and byte identity cannot be inferred from it. A bounded `-drwC -Mintel` capture would retain those details without recompiling or altering the gate.

For D's next already-needed diagnostic, include the original MainFull object and derive the selected closures from its C (for the retained94f69ed1 C: BENCH_PLAN selects lambda0 ADD and lambda3 MUL). Capture actual discovered unboxed lambda bodies and their raw object hash; do not assume future compiler lambda numbering. This is an evidence collection suggestion only. If the current job has started, let it reach its existing terminal condition; do not cancel it to change collection. No extra full performance run is justified by this gap.
