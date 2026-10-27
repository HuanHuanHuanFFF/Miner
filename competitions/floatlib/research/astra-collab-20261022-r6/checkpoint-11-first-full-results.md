# R6 first actual full-gate results, 2026-10-22 14:23 UTC

R independently recovered706 via the GitHub plugin while run metadata lagged. Original artifact12432741088 ZIP SHA2dfda3ea177502a20b6ad068222ebd0df134aba8c1648473a1226ebf53538930 matches GitHub's digest;90entries CRC/path/size checks PASS. Recovery stayed inside R research/ci-recovery/706. This was read-only retrieval, not CI dispatch/cancel. It does not claim the top-level workflow metadata has refreshed.

Both **f01-r6-normal-add-proof1 8a0e40fb** and **f01-r6-web-lowguards75ddbcff** actually PASS original four obligations, Submission+VerifyFull replay, three allowed axioms,12legacy timed classes and25paired rounds. Exact stored inputs/manifests/hashes and logs independently checked. CPU AMD EPYC9V45, seed706, sourcecommit0985c358. Full details and raw per-class values in first-full-results-706.json, reproducible by analyze-706.py.

| Candidate | Affected operation, normalized new/parent | Whole normalized new/parent | Whole raw new/parent |
|---|---:|---:|---:|
| Two-comparison add |0.972695|0.999081|1.012666|
| Low-scale mul guards |0.997662|1.001941|1.038869|

These are discovery comparisons against exact8eb in the same batch. Reference drift is material: add-reference+2.33% in the first comparison, mul-reference+4.63% in the second. Add raw total is only0.47%lower; tiny-mul ratio changes negligibly. **No material whole-entry adoption advantage is established.** No new-suite or current-champion acceptance is inferred.

Actual generated C confirms mechanism execution: new add enters with two unsigned interval comparisons and then direct table products; the old parent path is still inlined for misses, so counting the whole function's static calls double-counts mutually exclusive paths. Lowguards public mul removes two UInt32 special comparisons and one UInt64 width comparison (other branches remain). Fewer checks did not establish a meaningful full-call gain here. C is captured statement/bench-build layer, not timed-object instruction attribution.

D r6-feedback-07 read:707/39793280952 contains normal-mul96865cba, active-bias998747fa, absorption26dcfe0c8e;719/39794432216 performs new public-v2 full validation of8eb/normal-add/frozenDcombinationc18748c6. R now only follows existing validation and performs necessary proof-feedback repair. No new mechanism or webpage job, freeze respected. D continues coordinating every job and final choice.
