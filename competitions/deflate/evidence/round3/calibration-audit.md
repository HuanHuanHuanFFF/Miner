# Round 3 independent calibration audit

Read-only evidence audit at 2026-10-06 16:15 UTC. No network request, CI dispatch, script/candidate edit, commit, push, or new worker. Numerical checks below were recomputed from saved JSONL, rather than inferred from author summary labels.

## Evidence and score calculation

**VERIFIED**: runs `37488520058` (A) and `37488526325` (B) completed successfully on the same source commit `0873650e477acd9c4c0459547eebebe29bbad4e5`. Each raw block contains 28 stage1 files, 15930000 input bytes, one warmup and eleven measured repetitions per method. The time axis is the equal-file mean of `median(candidate total_s) / median(paired incumbent total_s)`. `total_s` includes parser and encoder. The size axis is the equal-file mean compressed percentage. Summing per-file medians is telemetry and is not that time axis.

`scripts/collect-round3.py` implements that calculation and verifies deterministic output, measured-repetition counts, file count, input byte count, reported source hash, and across-block output/token hashes. My independent JSONL recomputation of the bucket/probe2 time axes matched saved `analysis.json` to less than `1e-12`. Existing analyses retain snapshot 23753; `ranking-23817.json` reranks the same saved measurements against the later frozen snapshot. Neither constitutes online admission.

## Bucket2 versus probe2

**VERIFIED (raw output checks)**: for all 224 file/block pairs across A and B, `bucket2` and `probe2` have identical input hashes, output byte counts, DEFLATE SHA256, and token SHA256. Each has size axis **36.03572190230405%**, total output **5315736 bytes**. This is finite stage1 equivalence, not an all-input equivalence proof. The runs' `fresh_gate` entries for these controls are null; their prior gate acceptance must retain its historical source rather than be relabeled a new gate in A/B.

Time differences below are `100 * (bucket2_axis / probe2_axis − 1)` within each block; positive means bucket2 is slower:

| Run | Block 1 | Block 2 | Block 3 | Block 4 | Mean paired change |
|---|---:|---:|---:|---:|---:|
| A / 37488520058 | −0.0283% | +0.4813% | +1.3773% | +0.6205% | **+0.6127%** |
| B / 37488526325 | +0.6875% | +0.0677% | +0.2904% | −0.5582% | **+0.1219%** |

Run means of the absolute public time axis are A: bucket2 `0.4614946430573097`, probe2 `0.4586876626133317`; B: bucket2 `0.448604678148362`, probe2 `0.4480613195938966`. Equal-weighting the two runners' paired percentage changes yields **+0.3673%**, not a speed gain. Saying “about 0.6% slower” accurately describes A only; B is about 0.12% slower and has a different block sign pattern.

As a separate telemetry check, summed per-file candidate `total_s` medians range from 0.275370 to 0.288686 seconds for bucket2 and 0.278992 to 0.288201 seconds for probe2. Their per-block telemetry percentage differences are A `[+0.5350, +0.3312, +1.8482, −0.4306]` and B `[+2.5714, +0.1393, +2.0401, −1.8506]`. The discrepancy with the official equal-file time axis is expected from different file weights and incumbent normalization; do not use these summed seconds to claim a competition speed benefit.

**INFERRED (decision)**: these runs do not support adopting bucket2 for a speed benefit. They show identical stage1 output and a small average slowdown with order/runner variability. No formal statistical uncertainty model or private-stage2 result was estimated, so this is not a proof of a universal slowdown or a statement about every bucket layout.

## #407-dt900: inherited baseline versus new change

**VERIFIED (measurement counts)**: B measured `public407` only in blocks 1 and 2, while dt900 was measured in blocks 1–4. Comparing their full available means gives dt900 `0.43263362681115497` against public407 `0.4327801569497762`, or **−0.0338579%**. That mixes four candidate blocks with two control blocks and is not a balanced paired speed improvement.

Restricting to common blocks gives:

| Block | public407 axis | dt900 axis | dt900 change |
|---|---:|---:|---:|
| 1 | 0.431861059987777 | 0.4348063063055835 | **+0.6819893%** |
| 2 | 0.43369925391177533 | 0.43305520239949574 | **−0.1485019%** |

The mean paired change is **+0.2667437%**. This sign reverses the four-versus-two aggregate. The available data does not establish a dt900 speed benefit against its own original parser.

**VERIFIED (size)**: public407 size is `36.228761134302204%`; dt900 size is `36.304994127499484%`, worsening by **0.07623299319728005 percentage points**. Only two stage1 outputs change: `tiny-app.log` +82 bytes and `tiny-config.json.txt` +221 bytes. This finite observation matches the intended small-input symbol-thinning scope; it does not establish private-corpus behavior.

**VERIFIED (fresh public gate)**: B's dt900 gate recorded `accepted=true`, `corpora=["corpus-stage1"]`, fresh Charon/Aeneas extraction, statement acceptance, the three whitelisted axioms `Classical.choice`, `Quot.sound`, `propext`, and stage1 benchmark/round-trip acceptance. The intake proof prefix is `ed37de55387d9a98`, matching its preserved original proof hash; the raw benchmark source hash is `0b82a5c3df5cb88b7c650310f5b213b05263eef9ffdbc62f86052fc8cc0da42c`, matching the candidate manifest. Gate acceptance establishes the recorded public check, not a performance gain, private stage2, admission, or rewards.

The cross-family #427 calculations are numerically reproducible: dt900 maps to `(0.43886480188947563, 36.56013831177236%)` under fixed factors, or `(0.44462527551571995, 36.56013831177236%)` under the same-run probe3 anchor. These points can occupy geometry in the old snapshot. But the unchanged public407 control itself maps to `(0.4390134424857483, 36.48336956845774%)` under fixed #427 factors, although its actual formal point is `(0.4499838311061295, 36.499576583188635%)` and is dominated. That is direct evidence that apparent cross-family space is not the amount newly created by dt900.

Using the actual formal #407 coordinates and the two matched public blocks instead:

```text
X_own = X407_formal * mean_b(X_dt900,b / X_public407,b)
      = 0.4511841347398746
Y_own = Y407_formal * (Y_dt900_public / Y_public407_public)
      = 36.57637942949781%
```

**VERIFIED (geometry calculation)**: frozen snapshot 23817 has #425 `(0.4446803290713755, 36.31663049678496%)`, which dominates that own-family estimate on both axes. Even the unbalanced estimate in `family-calibration.json`, `(0.4498314761700483, 36.57637942949781%)`, is dominated by #425. Thus correcting the block mismatch does not rescue the frontier claim; it makes the measured new speed change less favorable.

**INFERRED (transfer limitation)**: the own-family mapping is a more relevant local-change estimate than borrowing #427's offsets, because it measures the modification against its actual ancestor. It still assumes public relative deltas transfer to the formal scoring corpus. That transfer, current online admission, and payout remain **UNKNOWN**. The majority of dt900's advantage over probe3 comes from the third-party #407 baseline, not the new 600→900 threshold.

## C/D and #432 calibration

**VERIFIED (configuration only)**: batch-c and batch-d mark `public432` as `control=true`. `scripts/round3.py` includes such controls in both screen and refine blocks, so a successful complete C/D run is configured to measure public432 in all four blocks. Actual C/D raw measurements were not present among the files inspected during this audit; their block counts, source hashes, determinism, gates, and axes remain **UNKNOWN** until collected.

For every actual run and common block, anchor a #432 derivative to its own original source:

```text
X_family,run = mean_common_blocks(
    0.4413850574969763 * X_variant,block / X_public432,block)
Y_family,run = mean_common_blocks(
    36.91273515631194 * Y_variant,block / Y_public432,block)
```

Use only common measured blocks. If two independent runners measure the same derivative, give the runner-level estimates equal weight rather than weighting by two versus four blocks. Retain per-block relative deltas/ranges and fresh-gate evidence. Verify exact public432 reference hashes, all 28 fixed file hashes, and the official paired incumbent provenance before interpreting changes. The public432 control's own-family estimate must equal its existing formal point exactly; it is a reference observation and cannot be reported as a new contribution.

**VERIFIED (latest script inspection)**: the current `scripts/rank-round3.py` has an `own_family_anchor` for #407 and #432. It intersects candidate/control block numbers, applies each family's formal coordinates, and averages within run then across runners. Its geometry wrapper divides by the #427 constants before the helper remultiplies them, so it does not apply both calibrations. Its #407 dt900 result matches the independent paired estimate above. The top-level displayed `conditional_geometry_share_if_admitted` still represents the probe3 anchor; it must not override an own-family dominated result when reporting a borrowed-family candidate.

**VERIFIED (reference geometry)**: #432's existing formal point is already dominated by #433 `(0.44020889517865036, 36.60395615892045%)` in frozen snapshot 23817. A variant must create enough real relative improvement to escape the full current frontier, not merely look good after a #427 remapping. Passing a new public gate on unchanged public432 does not create a new algorithmic gain. Original public source/author attribution must remain attached to any derivative.

## Reporting outcome

Report bucket2 as output-equivalent on stage1 with no observed speed gain. Report dt900 as a fresh-public-gate accepted #407 derivative whose size worsened and whose own-family paired estimate is dominated. Keep #427 fixed/probe3-anchor coordinates as calibration sensitivity diagnostics, not the deciding evidence of new contribution. For C/D, wait for the actual four-block public432 control, then prioritize own-family relative changes and current-frontier geometry. Public improvements, proof acceptance, formal admission/rank, and paid rewards remain separate claims.

Audited sources: A/B `ci-run.json`, `analysis.json`, saved `roundN-{bucket2,probe2,public407,round3-speed-407-dt900}.jsonl`, B gate JSON/full log, B `family-calibration.json`, `ranking-23817.json`, snapshot-23817 frontier, #407/#432 source receipts, batch-c/d manifests, and the current collector/ranker/measurement scripts. Only this audit document was written by this worker.
