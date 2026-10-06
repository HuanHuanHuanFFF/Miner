# Round 4 CPU candidates

Generated 2026-10-06, first batch. This note covers files under `candidates/r4-cpu-*/` and the deterministic generator `scripts/make-round4-cpu.py`.

**VERIFIED (local file checks)**: the generator locks the base `candidates/r3-432-fast3/parse.rs` SHA256 to `bae8014121e4710f4a34ce63452578b4bf69121b4f695e1b1356780a019108ef` and proof SHA256 to `e2c200cf084eca95eb70d26c0efb04e70d88f015315610d2a54d20b6adb7cf04`. `python scripts/make-round4-cpu.py` followed by `python scripts/make-round4-cpu.py --check` exited 0. The latter reconstructs and compares every byte of `parse.rs`, `Parse.lean`, and `manifest.json`; it is not a Rust, extraction, Lean, or runtime check.

The public #432 attribution is retained in each manifest. Original source, metadata, and miner hotkey are recorded in `references/round3-public-432/PROVENANCE.md`. These are derivatives of external code. The baseline has prior public gate evidence in `ROUND3.md`; that evidence does not automatically apply to these exact changed hashes.

| Candidate | Single mechanism | Expected token relation | Source SHA256 |
| --- | --- | --- | --- |
| `r4-cpu-r1off` | `R1_ON` 1 to 0; existing chain `run` replaces regular `run1` routes | INFERRED upstream equivalence claim; finite comparison required | `150b7c04f456bab378ab3068de46a666f5df6d98ce4ad6aaf1714afb51869cad` |
| `r4-cpu-run1ni` | `run1` always-inline to never-inline | INFERRED identical bodies/constants | `e8d641c87bfbea1b9bcedd1aa7e745bab789a63adabde69abc3930d5b5d043d9` |
| `r4-cpu-run1tai` | `run1t` never-inline to always-inline | INFERRED identical bodies/constants | `02690c07a5afd8bb13f25a6397680aa86128d7d65ae412e0591b3b8e166003aa` |
| `r4-cpu-commonni` | longer match extension `common_from` always-inline to never-inline | INFERRED identical bodies/constants | `2d7d386e0aae5fbf35ef480b19869c8e38c6adc3f4102a3e46c51fcc4915a495` |
| `r4-cpu-foldni` | `fold` and `fold_bt` scans always-inline to never-inline; quick reject wrapper remains inline | INFERRED identical bodies/constants | `5e61b341d942c0e8340607e10af8229cf450a4d432b76a3e7e7cec9989a4b699` |
| `r4-cpu-stai` | `run_st` never-inline to always-inline | INFERRED identical bodies/constants | `00d9d8e04b5c01f259b020ae22aa7370ef45276aea92b2114618b93333afab06` |

For the five attribute-only variants, the generator checks exact equality of the Rust text after stripping inline attributes. All six proof files are byte-for-byte copies. **UNKNOWN** for every candidate: executed token identity, correctness under official new extraction, axiom audit, round trip, measured speed, private stage2, official admission, and reward. No local compilation or CI was invoked by this subthread.

## Mechanism and test interpretation

`R1_ON=0` is a deliberately broad CPU ablation: it restores the window table and immediate literal writes as well as disabling read-ahead. It does not isolate prefetch latency alone. `run1t` is still chosen by the earlier `e_kind` branch, and tiny/stride branches precede the regular engine. Compare token and DEFLATE hashes with fast3 on each public file and additional fixed/generated inputs. Any mismatch must be reported as observed non-equivalence, even if both parsers still round-trip.

The inlining variants test instruction footprint against call overhead and constant propagation. `run1` currently appears in multiple constant-class dispatch branches and has many inlined helpers. Outlining it may reduce code duplication but expose runtime `skip`, `lazy`, and `km`. `run1t` has a single dispatch call with constant arguments; inlining could expose those settings. `common_from` extends only after eight or sixteen equal bytes, while `fold` is reached through `fold_w`'s word reject. Outlining these bodies may reduce the hot loop footprint; neither source inspection nor a smaller binary establishes CPU gain. The stride path inlining variant tests a separate class-dependent body and must be inspected at file level before interpreting the mean.

Use the existing official paired total-compression measurement, preserve per-file raw repetitions and token/output hashes, and compare against fast3 in matching order blocks. Collect parser-only timing as a diagnostic; the competition objective is parser plus fixed encoder. The parent alone controls CI dispatch and publication. This subthread does not commit, push, dispatch CI, operate wallets, or send formal submissions.

Useful CI diagnostics before another source rewrite:

- Actual target CPU and Rust build flags, including target features and LTO. Do not assume SIMD or target-specific instructions are available.
- `.text` and symbol sizes from the same optimized binaries, plus disassembly for `parse`/`run1`/`run1t`/`common_from`/`fold`/`run_st`; compiler attributes do not guarantee the inferred layout.
- Matched per-file parser/total times, size, token count and hashes. Separate text, prose, structured text, stride-routed inputs, and tiny paths using the parser's existing content decisions or source-grounded read-only instrumentation.
- If runner permissions permit it, cycles/instructions/branches/branch misses and cache counters. Counter access is UNKNOWN on standard hosted runner; do not make it a gate prerequisite or treat missing counters as performance proof.

Stop a CPU-only line when it has no consistent paired total gain, or when gain is explained by changed token output rather than CPU behavior. A token-changing candidate may still be researched, but must be classified separately and revalidated.

## Second batch: individual speculative-work ablations

Generated after the first batch without changing its six candidate bytes. Fresh `--check` exits 0 for all ten candidates. These four change bodies rather than attributes; their expected token relation is a source-level inference, and every executed/gate/performance result remains UNKNOWN. Their proof is still copied exactly; automated `step*` compatibility with new extraction is not known until CI.

| Candidate | Single mechanism | Source SHA256 |
| --- | --- | --- |
| `r4-cpu-x2lazy` | Move `xor8(c+8,p+8)` into the `x==0` branch in `xlen16` | `fdf3de5641dd72c3f217f3faccc6c91741ae5c3f5e9a7a940c35c5b05dc94d21` |
| `r4-cpu-flush` | Regular `run1` uses exact-length `flush` instead of `flush4` | `c05b02660410b22d6039644148699d42bd4dd086d62db5bfacae7d660177265a` |
| `r4-cpu-foldplain` | Regular `run1` uses `fold` instead of its word-reject wrapper `fold_w` | `110116b57808cfa7a1cab185145af662980ee9b1126f32b0bcf6f82fbc7e0eca` |
| `r4-cpu-endreload` | Regular `run1` removes early match-end `ae` and reloads after recording instead of `ahead_fix_m` | `3e728f0d8eefa64d73cf549954eb90a2ad20b3a7e12e5a94c640415e456f8fc1` |

`flush` equivalence concerns only the counted token prefix; unused output-array words may differ. `foldplain` depends on the upstream quick-reject shortcut being valid. `endreload` recomputes the same post-recording head values that the cache validation keeps or reloads. Each isolates one source mechanism; no compound is selected before individual measurements.

The local official source copy's candidate Cargo release profile uses `opt-level=3`, `lto="fat"`, `codegen-units=1`, `debug-assertions=false`, and **`overflow-checks=true`** (`sources/conjectures-optimisation-deflate/validator/measure/candidate/Cargo.toml`). The measurement engine profile separately has `overflow-checks=false`; it is not the candidate profile. The bench driver invokes `cargo build --release --offline`. This is VERIFIED file content in the local pinned-source copy; live CI flags/target instructions still require that run's provenance.

## Baseline parser contribution

**VERIFIED (saved run, recalculated locally)**: using all four `round*-r3-432-fast3.jsonl` files under `evidence/round3/37493517227/`, assert the baseline source hash, exclude warmups, and take each file/block's medians. Let `p` be the sum of parser-time/incumbent-total-time ratios across files (then averaged across blocks), and `t` the same sum for candidate-total-time/incumbent-total-time. The ratio `p/t` is `0.13565493878268958`.

**INFERRED scenario**: if a CPU change preserves token output and reduces every parser median by 10% while encoder medians remain fixed, the official equal-file total time axis falls about **1.35655%**. A 1% time-axis improvement would require about 7.37% uniform parser reduction. This is a sensitivity calculation on one historical runner, not a forecast or independent replication.

The largest parser contributions to that time axis are `binary.db.bin`, `server.log`, `machine-code.bin`, `metrics.csv.txt`, `tiny-app.log`, `page.html.txt`, and `catalog.xml.txt`. `prose.txt` has the largest absolute parser time (about 5.688 ms) but a smaller normalized contribution (about 0.001783 axis units), so absolute milliseconds alone should not rank CPU directions. Each contribution uses the same incumbent normalization as the official objective. Route identities for these files are not inferred from filenames; exact route coverage requires input content or read-only CI diagnostics.

Current constants `TF_TEXT=0` and `TZ_ON=1` make the `tf_plan`/`emit` branch in `parse` unreachable: `tf_route` gives either 2 or 3; 2 goes to `run_z`. **INFERRED**: the fat-LTO compiler likely removes the branch. Inspect actual symbols before adding an explicit dead-branch-removal candidate; source file size is not executed instruction size.

## Third candidate: slot-only preparation after a non-lazy match

`r4-cpu-slotonly` uses the exact fast3 constants and dispatch. The source adds `ahead_slot_m`, which computes the p+1 hash slot and retains the supplied candidate/word. The main `run1` probe now executes before next-position preparation. If `lazy==0` and its match is at least three bytes, it calls the slot-only helper; otherwise it retains the full `ahead_if_m` candidate/word load. No other engine is changed.

**INFERRED token relation**: the successful `lazy=0` branch never searches p+1. It needs only its slot for `record3_m`'s first insertion. `pre_c/pre_w` keep describing a real word from an earlier candidate, which the correctness invariant permits; the next actual search obtains current match-end values through `ahead_fix_m`. The post-recording fallback at an in-range end reloads its values. A miss or an enabled lazy policy retains the original complete preparation. This reasoning is not a universal token-equivalence theorem or executed comparison.

The candidate proof adds one `@[local step]` theorem, `ahead_slot_m_spec`, giving a valid slot and preserving word identity with candidate position at most the requested next position `i`. The helper's precondition supplies `c ≤ i`, avoiding an extra proof-only bound variable that `step` would have to synthesize. It does not alter the main loop invariant, obligation, or axiom policy. Its `H` argument is explicit because the new Rust helper's const generic is not inferred from an array-typed parameter. **UNKNOWN**: the actual Charon/Aeneas signature, helper Lean acceptance, main-loop `step*` coverage, decoded output, executed token identity, and speed. Main probe decision now precedes next-position reads, so reduced loads may be offset by losing latency overlap on misses.

Files after fresh local `--check` and source/proof diff inspection:

- Source SHA256: `9a869cf7e0f7a1ff8aef8f50177288066cd5d559c908491bbeeba1eeedee13ac`.
- Proof SHA256: `3be9d11d3de31016c6149fd952f54f14abdf78bc2236827051859580cebc5a97`.
- Original ten CPU candidate bytes remain unchanged. The generator can reconstruct all eleven candidate files and manifests; it invokes no toolchain or CI.

The parent will measure token/DEFLATE prefix equivalence, round trip, and paired time in the next batch. A fresh official gate should follow only if the measurement provides a useful signal; any extraction/proof error should be repaired against its full log and exact extracted source, not guessed from source syntax.

## Untimed token-block diagnostic utility

`scripts/profile-round4-tokens.py` is a separate Linux-CI diagnostic. It reads `ROUND4_SPEC`, `DEFLATE_ROOT`, and `RUNNER_TEMP`; the selected spec may provide `profile_names` with at most two non-control candidates. It always includes `r3-432-fast3`; absent an explicit list, it selects the first two non-control spec entries. To study encoder-cost changes, select candidates that actually change tokens rather than two CPU-only equivalent variants.

The script reads the official `token.rs` as an unchanged Rust module and extracts `LEN_TABLE`, `DIST_TABLE`, and `BLOCK_TOKENS` directly from the unchanged official `deflate.rs`. It requires 16384 tokens per block. Each parser's exact source/proof hashes must match the spec. A standalone harness calls the actual `parse` function, checks every token's decoded bytes against the public input, and reports each token block's literal/length/distance active-symbol counts, token count, literal bytes, match bytes, match-token count, and length/distance extra bits. It records full 288-entry lit/len and 30-entry distance frequencies. EOB frequency is one per block; a required dummy distance code in a literal-only block is marked separately and does not inflate actual distance frequencies. Empty input has one empty token block, matching the official encoder's splitting rule.

`TOKEN_PROFILE` prefixes all script/harness stdout records. No timing is performed. This profiles token statistics, not dynamic-Huffman headers or the encoder's actual fixed/dynamic/stored block choice. The script compiles only the baseline plus two selected candidates with the installed official pinned nightly; it invokes no downloads and leaves compiled binaries under `RUNNER_TEMP/round4-token-profile-working/`, outside the parent's uploaded receipt folder. It uploads neither binaries nor complete token arrays.

The receipt is `round4-receipts/token-profile.json` (provenance, per-file totals, status and failures) plus `token-profile.jsonl` (provenance and per-block/full-frequency records). Compile/runtime diagnostics remain in `round4-receipts/token-profile-diagnostics/`. Input/source/proof/official-source/harness hashes and actual compiler/coreutils versions are recorded. Token hashes are SHA256 of the counted little-endian u32 prefix, matching the format in official `measure/src/record.rs`; coreutils receives token bytes on stdin without a token-array file. Source/proof and official file bytes are rechecked after execution. Only completed file profiles with matching input hashes and block accounting are retained.

Failures are explicitly `DIAGNOSTIC_FAILED` or `DIAGNOSTIC_PARTIAL` and return zero so optional diagnostics do not change the gate or measurement outcome. **VERIFIED locally**: Python `py_compile` exits zero. **UNKNOWN**: Rust harness compilation and execution, public-file byte validation, and profile results; no local compiler/CI was invoked. The parent controls whether to run and upload these optional receipts.

## First screen: actual code and file-level attribution

Read from `evidence/round4/37515419910/screen/`, commit `be00e5792c94f36e99855f665a5c6a18a2d09899`, two public order blocks. A fresh local audit of all six CPU variants' raw JSONL checked the source hash against their manifest and verified the input hash, token count, token-prefix SHA256, output length, and output SHA256 against fast3 for **56 file/block records per candidate**. This is finite public identity, not all-input equivalence.

| Candidate | Mean total time-axis change versus fast3 | Interpretation |
| --- | ---: | --- |
| `run1ni` | about +4.317% | Broad stable parser regression with visible loss of specialization |
| `r1off` | about +1.782% | Existing read-ahead/no-window engine is beneficial overall on this corpus |
| `commonni` | about +0.823% | No gain; outlining the extension helper is not selected |
| `stai` | about +0.265% | No gain established |
| `run1tai` | about -0.284% | Two blocks differ in sign; insufficient to attribute to its named small-text mechanism |
| `foldni` | about -0.152% | Mixed file effects and small overall delta; insufficient evidence of a CPU gain |

The raw parser medians make `run1ni`'s large regression directly falsifiable: `bundle.min.js.txt` +36.50%/+36.18%, `catalog.xml.txt` +42.27%/+41.69%, `docs.md.txt` +41.39%/+43.13%, `page.html.txt` +37.75%/+36.36%, and `source.rs.txt` +38.39%/+42.56%. Corresponding encoder medians stay roughly within a percent, with identical tokens. This is a parser effect rather than compression-output cost.

**VERIFIED assembly**: fast3 has `parse` of `0x8d7b` bytes (36219) and an outlined `run1t::<4096>` of `0x13bc` bytes (5052). `run1ni` has only two generic `run1` bodies, H=4096 (`0x10b1`) and H=32768 (`0x1faf`), and `.text` falls from 317281 to 296549 bytes. In the H=32768 body, instruction `ee8f` masks the key with runtime `km` from `[rsp+0x20108]`; `fdc0` compares length to runtime `lazy` from `[rsp+0x80]`; `fde9/fdec/fdee` moves runtime skip from `ebp` to `cl` then shifts. These are direct evidence of lost per-class constant specialization. A 20732-byte smaller `.text` did not make it faster.

`run1tai` removes the separate `run1t` symbol but grows `parse` to `0x9e09` (40457) while total `.text` falls only 952 bytes. Its two small text file parser deltas are **slower**: `tiny-app.log` +6.92%/+2.42%, `tiny-config.json.txt` +11.05%/+6.42%. Their raw lengths are 28000/12000; exact route identities still need content/route diagnostics. Conversely, many large files show parser decreases of roughly 1%-5%. Every public file above 65536 bytes cannot take `run1t` by the source guard. The main `parse` body changes globally, so code layout/register allocation and runner noise are possible explanations; the mean cannot be written as a proven `run1t` speedup. For `run_st`, `run_z`, `run_rest`, and `slot_parse`, fast3/run1tai instruction sequences are identical after normalizing relocation addresses and branch targets (303/325/2645/38 instructions respectively). Their location still changes; this normalization does not prove equal timing.

**VERIFIED perf limitation**: the availability probe returned 255 with `perf_event_paranoid=4`, denying performance counters. This run supplies no cycles, branch-miss, or cache-miss evidence. Do not attribute the small deltas to I-cache or branches as an observed fact.

Two source-level deletion points are present in emitted machine code, rather than merely predicted from Rust:

- In fast3, `1094a/1094f` load and XOR the second pair of words before `10959` tests the first XOR and `1095f` selects with `cmovne`. The already-running `r4-cpu-x2lazy` specifically tests avoiding these eager reads.
- Fast3's `flush4` short path at `fc9a` checks pending length <=4; `fcb6` loads four input bytes, `fcbb/fcbf` expand them, and `fcc8` stores sixteen bytes. There is no preceding zero-length short circuit in this path. `r4-cpu-flushzero` tests deleting that work only when pending length is zero, keeping the nonempty SIMD-friendly path.

## Two new candidates supported by this assembly

`r4-cpu-flushzero` adds `from==to -> nt0` to `flush4`. The proof adds a direct Dec-preserving return case to `flush4_spec`; unused output tail equality is not required. `r4-cpu-classoutline` adds separate noinline `run1_text` and `run1_prose` wrappers which call the always-inline `run1` with their original fixed constants, then changes only those four dispatch calls. Its proof adds two wrapper lemmas and two alternatives in `parse_spec`. It tests outlining while retaining specialization; the next assembly must show that skip/lazy/km are actually constants inside the new kernels.

Both are **INFERRED token-preserving experiments**. **UNKNOWN**: Rust compilation, extraction, Lean, runtime hashes, and speed for the new exact hashes. Fresh local generator `--check` and Python syntax checks pass. The generator now has `--only` so newly authorized variants can be written without rewriting frozen files; all original eleven candidate bytes remain unchanged. No third candidate or combination is added before batch B's `x2lazy`, `flush`, and `slotonly` measurements.

| New candidate | Source SHA256 | Proof SHA256 |
| --- | --- | --- |
| `r4-cpu-flushzero` | `ed565b50c03230c6f08027af5e3ac81691cce3f66917a34da09dce4bdbe056c3` | `2ec5a9f7471cc94d23822ecfa990a637215eeaede7c232616412cfce0efa312d` |
| `r4-cpu-classoutline` | `36697422c014c5a140a0953311509dd510b9ce3e6e0f4106231418fe8193c572` | `41afa5a114f50a7fe1b8d0a3d5dc98408f1f989b8925734b7eb00f8a04aaf781` |

Assembly receipts are capped at two million characters and marked truncated in their metadata. The parser functions and addresses cited above appear completely before that cutoff; no claim is made about the omitted library assembly. The fast3 library hash for this code-generation receipt is `e3c97b3aef581e8e4a6e0f848cdd79427cdc9aa441d32c3110b73cc0508d3566`; the runner reports AMD EPYC 7763 and the pinned nightly `rustc 1.100.0-nightly (8fa1c96cf 2026-08-17)`.
