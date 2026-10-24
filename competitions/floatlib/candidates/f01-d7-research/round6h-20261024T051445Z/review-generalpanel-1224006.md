# GeneralPanel source / guard / size review

**Source-level review only.** The frozen GeneralPanel source is exactly 255,559 bytes, SHA-256 `a1ab536c…2e48abe`: 441 bytes below the 256,000-byte package cap. Its manifest, freeze, dispatch receipt and run HEAD `91c7a607…72baae6d` all bind that exact Kernel. The 1224006 plan is `STATEMENT_DIAGNOSTIC` and marks both candidates `statement-only`; run `40071679912` is still active and its artifact is not locally collected. No proof/full-gate or performance conclusion follows from this review.

## Declaration inventory and source identity

The candidate SHA matches its manifest, `decl-policy-review.json`, R12 freeze, dispatch receipt and commit-tree blob. The static declaration review records 17 removed and 18 added declarations; its six `WordFinite`/`FinalFinite` theorem bodies are listed as complete local dependency closures. The other removals are prior `R11WideRows4` helpers replaced by the new Panel4 implementation. Namespace context matters: the candidate contains `Submission.Panel4.wordLoop`; that is not a surviving `Submission.R11WideRows4.wordLoop`. The old `R11WideRows4` value layout/projection needed by callers remains.

The declaration inventory explicitly covers only `def`/`theorem`/`abbrev`. Its `static_policy=PASS` and “outside reference” review are source checks, not Lean acceptance. The candidate manifest still says `proof_status=NOT_RUN`, `full_gate=NOT_RUN`, and `performance=UNKNOWN`; the exact four-spec full gate remains required.

## Production entry and guard

Panel4 is connected to the actual `Submission.bmm` route in source, rather than existing only as an unused helper:

1. `bmm` retains the outer `UnderflowZero.small` short-circuit; otherwise it calls `bmmBeforeUnderflowZero`.
2. That wrapper enters `R11WideActual.core` only under `4 ≤ m`, `4 < n`, `2 < p`, `n < USize.size`, and `A.toArray.size < USize.size`; other shapes use the prior Cross/DirectContinuous fallbacks.
3. `R11WideActual.core → output → buildTiles → Panel4.block` is the source call chain. `Panel4.block` prepares `packA` once per four-row block; `R11WideLayout.writeBatch` binds the resulting tiles once before emitting the block. The remaining rows go through the local-tail/RowStream path. The only global packed input shown in this route is B.

The branch keeps the existing guard rather than widening dispatch. The predicate does not spell out a separate `B.toArray.size` term; proof that the full bound/semantics obligations hold remains for the official gate. The README's source-derived cost and finite-word reports are not runtime evidence.

## Budget and run status

The run-1224006 plan orders `f01-d12-scalar-cold-nan-select-proof2` (`3ff4eb8e…11f36221`) then `f01-r12-general-panel` and marks both `validation_mode=statement-only`. Its freeze and commit tree bind GeneralPanel at 255,559B and the second candidate at 247,897B. Run state reports 40071679912 on that commit, `allow_private=false`, currently in progress; no local terminal receipt exists. The separate 40071334389 full run is for `f01-d12-mul-existing-convert`, so it cannot establish GeneralPanel proof or performance.

The source supports the structural claims that Panel4 is on the guarded four-row path and that the old declaration set was pruned/replaced as inventoried. It does not establish exact proof closure, native-code entry behavior, the 25-round score, stable gain, or codegen/cost improvement. Full verification and a clean observer-free comparison remain necessary. File-level hashes and precise state are recorded in `review-generalpanel-1224006.json`.
