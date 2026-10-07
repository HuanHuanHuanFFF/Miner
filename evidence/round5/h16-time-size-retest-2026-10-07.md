# H16 time/size and official-gate retests — 2026-10-07

## Scope

This record covers the two frozen original H16 hybrids across workflow runs 37580297956–37582138961. It does not cover the later proof-only repair candidates listed in run-ledger.json, private Stage 2, competition admission, ranking, or reward.

Frozen candidate hashes:

| Candidate | parse.rs SHA256 | Parse.lean SHA256 |
| --- | --- | --- |
| r4-hybrid-h16-small299 | d9826bc92ba02f49cb6e552ed172a4fb82dc10fa8fb51aacf73e7947ed38a94d | ac2d894b3a4ccacb30ce4ed654a3dd3d3b3c167183eb8df008168772109215fa |
| r4-hybrid-h16-smallc299 | 39c82b4673440faaa7cf9f14ccbeb9367128a7f50a8ca8472880dc35ed24b83e | eec49d582853cddf843c33b950f444520561bbb40ef0197ee64ce9acfbb92791 |

The tested Rust and proof bytes stayed unchanged across these runs. Commits c47efca and 25856c5 changed the workflow/profiler support, not these candidate pairs.

## Public time/size screen

Latest paired screen: run 37582138961, commit 25856c53becab60215e801610ea90c6367530aff2.

The reported time metric is unitless: mean per-file candidate total_s divided by incumbent total_s. Lower is faster. It is not seconds.

| Candidate | Time index | public299 time index | Relative time change | Output bytes | size_pct | Output delta vs public299 |
| --- | ---: | ---: | ---: | ---: | ---: | ---: |
| r4-hybrid-h16-smallc299 | 6.6249978 | 9.1537097 | 27.62% lower | 4,869,984 | 33.860879% | +3,200 bytes (+0.018048 pp) |
| r4-hybrid-h16-small299 | 7.0255128 | 9.1662223 | 23.35% lower | 4,870,363 | 33.863214% | +3,579 bytes (+0.020383 pp) |

Against fast3, the H16 candidates are still much slower: approximately 15.44x for smallc and 16.27x for small. Their size_pct is about 2.74 percentage points lower (better compression) than fast3. Thus these are compression-oriented tradeoffs, not general speed wins.

## Latest official Stage 1 gates

Both jobs in run 37582138961 completed successfully on the latest tested commit.

| Candidate | Gate | Candidate output | Incumbent output | Relative slowdown | Proof/Parse lake call | Total verifier |
| --- | --- | ---: | ---: | ---: | ---: | ---: |
| r4-hybrid-h16-smallc299 | accepted | 4,869,984 bytes | 5,130,834 bytes | 4.2432x | 808.5 s | 988.1 s |
| r4-hybrid-h16-small299 | accepted | 4,870,363 bytes | 5,130,834 bytes | 4.8117x | 666.9 s | 817.9 s |

Both outputs are smaller than the Stage 1 incumbent: 5.084% for smallc and 5.077% for small. The verifier gives each isolated lake call a 900-second limit; total verifier time also includes preparation and post-checks, so the total can exceed 900 seconds when the main proof call remains within its limit.

## Retest history and stability

| Workflow run | Commit | Candidate(s) | Result |
| --- | --- | --- | --- |
| [37580297956](https://github.com/HuanHuanHuanFFF/Miner/actions/runs/37580297956) | 8cddb52 | small | Rejected at statement elaboration: proof did not finish within 900 s. |
| [37580365335](https://github.com/HuanHuanHuanFFF/Miner/actions/runs/37580365335) | 8cddb52 | smallc | Accepted; Proof/Parse lake call 557.5 s, total verifier 684.2 s. |
| [37581080647](https://github.com/HuanHuanHuanFFF/Miner/actions/runs/37581080647) | c47efca | small and smallc | Both exceeded the 900 s statement-elaboration limit. |
| [37582138961](https://github.com/HuanHuanHuanFFF/Miner/actions/runs/37582138961) | 25856c5 | small and smallc | Both accepted; timings shown above. |

Across these three attempts per frozen candidate, small passed once and timed out twice; smallc passed twice and timed out once. The latest branch-triggered run is green, but the earlier timeouts show that proof elaboration is sensitive to runner conditions and has limited headroom. Do not treat one green run as evidence of stable proof timing.

The token profiler fix was also verified in run 37582138961: both specs reported DIAGNOSTIC_OK, 28 file records, and zero diagnostic failures. This is untimed token/block-cost evidence, not an official gate result.

The branch-push workflow is configured in .github/workflows/deflate-round5.yml. This report is outside its watched paths and does not trigger another benchmark run.