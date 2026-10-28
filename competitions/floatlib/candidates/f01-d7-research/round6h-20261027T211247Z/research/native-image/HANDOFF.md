# R22 B: fused input certificate feasibility

**Current decision: interface reserve, no full implementation or CI queue.** Active corrected predicate is per-batch/per-column B flags plus a four-bit A-row mask. The earlier global-B Bool is parked for conservatism; details and exact costs are in `column-row-feasibility.md`.

Start **21:54:09 UTC**, low-cost check bound **22:19:09 UTC**, shared deadline unchanged **2026-10-28 03:12:47 UTC**. No Git/CI/local Lean or full candidate. Frozen quad proof `257d` unchanged.

Low-cost check closed at **22:15:13 UTC** after **21m04s**, preserving the interface without further implementation. B returns to the shared quad/cost-feedback task; this is not the end of the six-hour window.

- **T19 answer already YES** for +0-start ordered dot with all actual raw inputs nonNaN, including Inf/±0/subnormals and invalid-generated canonical NaN. Current B2/4e36 already has all-native `R7W12.ofFloat32_add/mul` and raw classifier transport; no new closure proof or 12.7 KB import needed.
- **Actual cost difference identified:** 4792 scans each NaN output's row/column; old summary fusion was a proposal; R14 row-NaN Thunks route poisoned rows to software; R9 per-step event replay is already negative. Scoped source search found no implemented preparedB+Bool fusion. Current PreparedQuad already traverses all B once, so a shared summary can be accumulated there, with one A Bool per four-row group at its shared raw loads.
- `FusedPreparedB.lean.inc` **c4b98dc7 / 2361 B**, **NOT_RUN**: a one-pass prototype, plus explicit `Ready` contract and four conditional getD/roundtrip roots. **prepare_spec remains missing.** False summary must not stop value preparation.
- `DotImageInterface.lean.inc` **0bb87f92 / 2761 B**, **NOT_RUN**: 3 actual-loop roots reuse existing W12; `direct_import_eq_finish` permits group-level direct import with exact read certificates/result equality, so endpoint classification can be skipped too. No public BMM assembled.
- `witnesses.json`: 10 old-model directed cases, including Inf*0, opposite Inf, sNaN/qNaN payload, first-invalid ordering, +0 and empty seed. Full overhead, old-source identities, exact missing interfaces and first codegen/caller-cost falsifier are in `feasibility.md` / `manifest.json`.

- Corrected minimal sketch `ColumnRowSummary.lean.inc`: **14e59b3f / 3978 B / 4 conditional roots / NOT_RUN**, exact `Ready` and `RowMaskReady` contracts, one-pass B iteration and UInt8 mask step. **Neither builder→Ready nor loop→RowMaskReady is proved.** A valid quad-domain counterexample shows global B rejects four locally certifiable outputs; a separate batch-index mutation is caught in 355 tiny structural cases.
- Controller's two already-seen seed check sampled 155 outputs; locally certified NaN samples were 4 / 1, touching whole-case shares 0.4468% / 0.1557%. No extra positive from replacing global with local B was seen in that sample. This is not full exposure, removable time, or a 10% gain basis. Preserve the mathematical interface; do not enlarge the sample or reopen proof work to justify it.

**Next decision belongs to D:** only after quad/prepared has a substantial signal, consider a low-marginal-cost complete-caller comparison including flag writes/AND, A mask, COW, per-output certificate loads, finish and quiet-stop fallback. Current cost3 takes priority. Main quad sources remain frozen and ready for real feedback.
