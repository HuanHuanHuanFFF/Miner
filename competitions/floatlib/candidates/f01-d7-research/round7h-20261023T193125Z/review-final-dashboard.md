# R11 final dashboard postcheck

**NO_BLOCKING_DISCREPANCY_FOUND.** All four operation rows point to the same exact candidate `f01-d11-bmm-combined-classifier/Kernel.lean`, SHA-256 `6c2d394dd34e8854d0d44d5d6605c194ecb27c152a1768d236481fc03fa4277d`. Only the two assigned review files were written.

## Same source, unchanged model and baseline

The numeric model SHA `da02d4370ddf4ff28419ceda1a86a2d1dde5a81838f09d2540e705b30fe3b1d1` is byte-for-byte the atomic-adoption after SHA. Displayed add/mul/sum/bmm estimates1.14/1.24/1.13/2.64 and whole1.39 match this model's two-decimal median rounding. There is no per-operation fastest-source splice. Champion#285 is the stored official receipt `competitions/floatlib/candidates/f01-d7-research/official-20261024T000558Z/receipts.json` (queried at `2026-10-24T00:06:00.904834+00:00`), digest `a1e99008577119824464154be5ec52dd390fc1e429b8f85b6ea73315e7103082`, with self baseline1.0. This check did not query a new live leaderboard.

Current anchor, estimator and renderer hashes match their frozen cohort entries. A pure in-memory replay called only the frozen estimator's select_pairs/estimate_from_anchor, re-read and checked original source evidence, and reproduced operations, whole, paired_updates, cell_relative_delta_median and samples exactly. No main/save/render entry ran. Whole timing follows the frozen sum-before-ratio projection; no operation receives a separate winning source.

The adoption input snapshot SHA `f55fc7442cd978df09c8e0d38becb46af832bd6d69fcda419d0ad0865501f9ba` equals both model.current_public_results_sha256 and model-input-index-receipt. Later936/937 live-index extensions cannot silently recalibrate this frozen model.

## All six measured source runs remain visible

|Seed|Run|Role|Observer|
|---|---|---|---|
|922|40039965234|DISCOVERY|yes|
|929|40044330511|DISCOVERY|yes|
|930|40044727137|DISCOVERY; selected D|no|
|933|40047321773|DISCOVERY; unselected|no|
|103391|40048911739|FROZEN_INDEPENDENT_CONFIRMATION; A|no|
|103392|40048972520|FROZEN_INDEPENDENT_CONFIRMATION; B|no|

All six exact6c measurements remain in paired_updates and state.all_source_samples. Observer and unused-discovery roles were not promoted to independent confirmation. The separate six model.samples are inherited41 frozen-anchor workload projections, not six additional6c measurements.

The three-group receipt SHA is `0231a6a14a66c4b0d9b309cea28161cfb0abf5c9adeefbdd64b165714ba04ff8`, accepted=true. The atomic-adoption receipt is accepted with adoption_performed=true. D/A/B whole ratios are0.91622356/0.91672920/0.90641201; gain p05 values are0.06467445/0.05223447/0.06496548. This supports local frozen adoption, **not official admission, formal submission or a new champion**.

## Presentation inverse and limits

The label-update receipt continuously binds the adopted view/state to the later presentation change. Restoring only the old presentation policy reproduces the exact adopted after-view SHA. Replacing the new BMM caption with the old caption and normalizing current Windows CRLF to the original LF reproduces the exact adopted after-dashboard SHA. The numeric model itself remains byte-identical. These are label/policy-time/platform-EOL changes, not numeric recalculation.

The earlier a066 research display BMM3.32 to2.64 and whole1.47 to1.39 is frozen-anchor estimate progress, not a same-run causal speed measurement. The model remains INFERRED; direct matched-suite champion comparison and official_admission remain UNKNOWN. Original preflight snapshots from before A/B completion remain unchanged. All exact evidence paths, sizes and SHAs are in the companion JSON.
