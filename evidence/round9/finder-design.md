# Round 9 q9 finder diagnostic

Status: script prepared; Rust build and corpus execution have not been run by this implementation task. This is the bounded discovery experiment proposed in `evidence/round8/next-mechanism-review.md`, following the negative retained-candidate-cost result in round 8.

## Invocation and output

After the existing CI job prepares the pinned Linux Rust toolchain and public corpus, run:

```sh
"$DEFLATE_ROOT/.venv/bin/python" scripts/research-round9-finder.py
```

The script requires this repository's Linux GitHub Actions environment and an active `ROUND4_SPEC` with `finder_diagnostics` set to exactly `true`. A missing specification label or missing/false flag prints `ROUND9_FINDER_DIAGNOSTIC_NOT_REQUESTED` and returns before accessing temporary directories. Enabled runs require `RUNNER_TEMP` / `DEFLATE_ROOT`. The script does not install dependencies, fetch data, call the submission client, or start another CI job. All generated Rust, binaries, and synthetic inputs remain under `RUNNER_TEMP/round9-finder-build`. Only JSON and text logs are written to `RUNNER_TEMP/round4-receipts/finder-diagnostics`:

- `finder-diagnostics.json`: source/input hashes, process results, per-file counters, diagnostic times, and totals by public/synthetic input.
- `build.log`: standalone harness compiler output.
- `runtime.log`: input-start markers and completed per-input records; useful if a later assertion or timeout stops the harness.

Compiler timeout is 180 seconds and runtime timeout is 360 seconds. These are bounds, not a prediction that the script takes nine minutes. Toolchain setup, runner queueing, and artifact publication are outside those bounds and owned by the main workflow.

## Source and observation boundary

The script pins the already retrieved source bytes:

- #361: `f426f7cec777ef2ca74616eb62205d54ae0bf6938799835a1fe6024ed59b5c45`.
- #454: `382176623abda73f77a9a5323e8cb14c5cdd6c8221b018cbc8c51cf959448639`.

It compiles complete copies of both modules, plus a second #361 copy with one read-only callback. An exact function boundary and exact local string anchor restrict that callback to `dp_parse`, after original candidate/continuation assembly and before subsequent planner updates. The similar code in the D engine is not instrumented. Removing the callback restores the original normalized #361 source exactly. Both original source hashes are checked again after runtime.

The harness calls #361's original `parse`, preserving its route classifier and engine configuration. It never invokes #454's exact-length router: the only tested #454 entry point is `q9_hfind` at its recorded depth 32. Each input's original route class and engine are included in the receipt. Primary discovery conclusions concern `engine == 1`; other public files are still parsed and checked but have zero DP callback positions.

## Measurements

For each of 28 public files and six deterministic synthetic text files, the harness:

1. Builds the complete q9 event/offset/match cache, including allocation and all-position tree insertion. It measures two builds, with original #361 parses between them in opposite order: q9 / #361 / #361 / q9. Cache contents and #361 token outputs must repeat exactly.
2. Checks every cached q9 match for increasing record lengths, distance in 1..32768, source position before the match, length in 3..258, input bounds, and byte equality. This is performed outside the finder timer. It counts validated records and their matched bytes.
3. Runs the observer copy of #361. At only its real DP search positions, it checks #361's retained candidates and compares them with q9's cached candidates for that position, including the continuation record already selected by #361.
4. Requires the observer's complete token stream to equal the untouched #361 stream, then decodes that stream and compares all input bytes. Callback computation never changes the plan or output.

The comparison reports positions where either finder has a longer maximum, extra/lost supported lengths, new or uncovered distance records, and cheaper/costlier common-length edges under #361's current distance prices. Baseline and q9 prices for each common length are both the minimum over all retained supporting distances. This compares candidate discovery without crediting q9 for the retained-cost-selection blind spot already tested in round 8. Length prices cancel for equal lengths; newly supported lengths are counted, not assigned a claimed compression benefit.

All q9 records are considered without truncation to #361's 16-slot array. Positions with more than 16 q9 records are counted, so any future integration must account for candidate-capacity loss. Internal tree-node visits and actual comparison bytes are not instrumented in this simplified version; validated match bytes are a different quantity.

The full finder construction timings are diagnostic and include cache allocation; #361 parse timings exclude allocation of its output buffer. Neither includes the official encoder. There is no warmup campaign or statistical confidence claim. These values can reject an obviously unaffordable cache prepass; they cannot establish an official speed axis, candidate improvement, or reward eligibility.

## Synthetic inputs and interpretation

The six fixed inputs contain source-like text, prose, or markup at 65,537 and 131,073 bytes, with deterministic local mutations every 257 bytes. Names, sizes, and SHA256 hashes are saved. They exercise repeated-prefix behavior at lengths different from the reference router's exact-length branches; they do not establish hidden-corpus generalization.

Stop before implementing a candidate if new coverage is negligible, lost coverage materially offsets new coverage, matches fail validation, or full-cache construction is too expensive for the available time/size frontier tradeoff. A positive match/cost diagnostic is only a reason to consider one controlled candidate; selected-path effects and encoded output still require actual integration and paired official measurements. No extra depth settings are swept here.

## Verification status

**VERIFIED locally:** Python syntax; both pinned source hashes; exactly one callback within the DP function; exact source restoration after callback removal; rejection of duplicate/missing anchors and repeated insertion; deterministic generation of six inputs; result-parser coverage/histogram checks and a rejected inconsistent-counter case.

**UNKNOWN / NOT RUN:** Standalone Rust compilation, actual q9 cache validity, observer token equality, input decode checks, diagnostic counts, and finder construction times. The script records verified status only after those runtime checks complete successfully on every requested input. No candidate/proof/source-reference edits, CI dispatch, Git action, or wallet action were performed by this implementation task.
