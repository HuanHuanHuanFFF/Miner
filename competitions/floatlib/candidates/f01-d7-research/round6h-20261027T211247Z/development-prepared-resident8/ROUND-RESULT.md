# Resident implementation and proof migration

Final closeout at 2026-10-28T03:13:03Z; shared deadline remains 03:12:47Z. Final closeout: the shared deadline has now been reached; no new task is started. Worker first tool was 23:48:25Z. D owns Git, CI and adoption; this worker used no local Lean/native compilation or new CI.

## Decision and measured boundary

Flat global A4×B2 remains PARK. Exact old R16 already borrowed its selected A/B arrays before the inner loop and retained only one four-row result cache. Flattening did not remove those hot reads and would lengthen A-cache lifetime. The negative old exact implementation and full-call boundary were checked in source and C.

Resident16 source `d17053ac` was measured inside `fd4e5b51`, CI40607316341. BMM ratios were 0.995805/0.999984/0.959830/0.959165; all four whole ratios exceeded1. No adoption. Actual C established16 independent native accumulator arguments, borrowed input records and no hot allocation/codec; the captured native tile showed stack arguments and output cost. Its inner wordLoop ASM was not captured, so SIMD/register claims remain UNKNOWN.

Frozen indexed8 runtime is `KernelIndexed8Cost.lean`, SHA256 `8e27baf70ce7e3f10b669cc9f59d66d5fffaa17ee3dc6df934f3229139a5b0dd`,250041B. Its only algorithmic representation change was machine-word fit/address/cursor handling, with original same-cache Nat fallback. CI40611570030 BMM/B2 ratios were0.885144/0.943890/0.946705/0.928235; whole0.968528/0.992196/0.993392/0.985039. All326 originals/36,892,038B were independently rehashed. Untouched-operation/control anomalies and slow cases remain in the record; these samples are diagnostic, not a full acceptance or independent confirmation.

Actual timed object `85dbf986` and C `e0979bb1` show the indexed loop removed Nat helper calls and reduced the frame280→120B. True2mulps+2addps remain. The accumulator still performs64B explicit stack loads/stores per k, with four conditional codec calls. The intended register target was not achieved. See `INDEXED8-ACTUAL-REVIEW.md`.

## Correctness migration

Accepted evidence: `Nat8Projection-v1.lean.inc`, SHA `79574fb1`,4601B. CI40619267183 exact source `f7b19b9e` passed statement, Submission/VerifyFull kernel replay and the allowed three axioms for all four selected roots. All152 originals/8,197,132B were independently rehashed. This proves a generic conditional row/lane projection to retained R15PackedB2 and NativeFinal.dotLoop. It does not establish the producer or full public BMM.

Current repair: `Indexed8LoopEq-v2.lean.inc`, SHA `ccee65d4`,5755B; proof-only exact-runtime composition `KernelIndexed8LoopProbe-v2.lean`, SHA `7981b04c`,255797B. It only replaces the observed failing cache.uget→getD rewrite with a concrete fully applied equality retaining hcursor. CI40621932164 passed statement, Submission/VerifyFull replay and allowed3AX for the three selected uget/wordLoop_eq/within_eq roots. All238 originals/22,090,569B were independently rehashed. The two auxiliary wrappers typed and module-replayed but were not separately selected for axiom audit. Frozen8e and accepted795 are unchanged.

Reusable pending leaves now cover actual valid pack selection→projection hread (`41e6dbec`), diagonal/base facts (`c63fdfeb`), retained finish (`1cde7134`), original Words selection (`5277ada5`), word-loop equality→whole Nat output (`3adbd313`), and exact wrapper/guard equality (`9da6f3f9`). They are NOT_COMPILED/NOT_RUN; no composed full candidate was emitted. `proof-leaf-index.json` binds every full hash, exact root, dependency and receipt. The valid-column premise is retained; finite address/word models are not Float32 or Lean proofs.

Reader parity/field/raw-word reconstruction has a further independent a8cf1655/1404B draft (three roots,8320 finite checks; NOT_RUN). Conditional pointwise reader→NativeFinal.dot has an independent65101d8d/1796B draft (one root, NOT_RUN), retaining actual hread as a premise. The first remaining unassembled public argument is the concrete RowStream Prefix composition for four consecutive rows, blocks, remainder rows and batches. Existing generic four-row and flat-tail writer interfaces were found and bound in NAT8-PREFIX-INTEGRATION.md; no duplicate writer was made. Raw Nat8→public reference still needs closure. Public roots in8e continue to bind B2. Full new BMM equivalence, full gate, private distribution and adoption are UNKNOWN/NOT_RUN.

## Resource and next decision

No new seed, threshold, runtime algorithm, toolchain or benchmark was selected after the frozen cost sample. The actual v2 result is accepted; no v3 or repeated experiment is needed. The pending outer congruence and raw Nat proof leaves offer a small proof path; they do not authorize claiming full correctness or speed acceptance.

Indexed8 measured inner resource receipt records7.511486s build,16 benchmark processes totaling28.801328s,74.751966s diagnostic stage, on AMD EPYC9V74. Shared queue/setup/job walltime allocation is UNKNOWN. Tokens, cached input and reasoning/output allocation are UNKNOWN. This worker's actual end time will be recorded at the common deadline.

Capacity closeout: parent reported “Selected model is at capacity” and requested recovery. Its raw start/end timestamps are UNKNOWN to this worker. A successful recovery tool was observed03:09:44Z. The first/last tool span must not be described as continuous active duration or six hours of worker execution. Final actual end will be recorded at the fixed deadline. Last pre-notice draft378765ff/1097B actual-pack selectedread→dot remains NOT_RUN; no new source/Kernel/CI after recovery instruction.

Final successful closeout tool: 2026-10-28T03:13:03Z. Worker first tool23:48:25Z; first-to-last span is not actual active duration. Capacity interruption start/end and total active duration remain UNKNOWN. All7 selected roots remain verified,2auxiliary wrappers only module-replayed,22 draft roots NOT_RUN. Frozen8e SHA remains unchanged. No new Kernel/CI or full-public correctness claim.
