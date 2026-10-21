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

## Token-profile format repair

**VERIFIED failure**: C run `37520076712` generated no valid token profiles (`files=[]`). All three selected harness compilations returned 1 with `invalid format string: unmatched '}'`: the block println ended its final `{:?}` placeholder with only one additional closing brace, rather than the pair needed for a literal JSON `}`. This affected optional diagnostics only; C's official performance measurement continued. D had already started with the same diagnostic script, so its profiles must also be treated as unavailable if the same compile failure is returned.

The script fixes that single format character and adds a lightweight generated-format guard. **VERIFIED local checks**: Python syntax passes; generating the harness as text checks all four ordinary `println!`/`format!` literals; removing the repaired brace reproduces a guard rejection. No Rust compiler is run locally. Repaired script SHA256 is `4f2e9f1dd2f3edd0d92976df49b13462fc6e2ce501d24321a56c8cbd04e71bb9`. **UNKNOWN**: actual Rust recompile and token-profile results in the next CI. Empty C profile files are not evidence about token distributions or costs.

## B refinement and next general mechanisms

Read `evidence/round4/37517466397/refine/analysis.json` and its raw per-file JSONL. **VERIFIED**: exact `flush` has about -0.058% mean total-axis change over four blocks; `endreload` about +0.114%. No useful general speed gain is established. Raw parser medians for `flush` on `bundle.min.js.txt` are consistently slower by +2.39%/+2.51%/+2.54%/+2.59%, despite the last block's total median decreasing by 2.61%; its encoder median in that block decreases by 4.03%. `endreload` helps raw parser medians on `binary.db.bin` (-3.66%/-3.74%/-3.99%/-5.24%) and `machine-code.bin` (-2.23%/-3.10%/-2.30%/-2.61%) but hurts `bundle.min.js.txt` (+3.08%/+3.38%/+2.44%/+3.23%). These raw process-to-process component deltas are diagnostics, not the official normalized two-axis computation. They do not justify combining or broadening the losing ablations.

The next match-emission mechanism is supported by actual fast3 assembly from the same B receipt: `11705-1172d` repeats `p<n`, `l<=n-p`, `3<=l<=258`, `1<=d<=32768`, and `d<=p` tests after search/backward folding; packing then starts at `11738`, with the store at `1174a`. The existing `put_match_spec` already requires `hm : MatchAt`, which contains all those facts and byte-match evidence. All its original higher-level call-site proofs remain in the candidate; a fresh all-path Lean obligation is required to verify those callers after changing emission, irrespective of public token identity.

`r4-cpu-directemit` replaces repeated fallback tests with `pack_match(d,l)` and safe indexed output plus count/position advance. Packing is `(d as u32).wrapping_mul(256).wrapping_add(l as u32).wrapping_add(16776957)`, equal to the contract's `16777216+(d-1)*256+(l-3)` on every legal length/distance. Maximum legal token is 25165823, so all these u32 intermediates fit. The proof adds two wrapping-u32 arithmetic specifications and `pack_match_spec`; `put_match_spec` and every main-loop caller continue to use `MatchAt`. Internal invalid-argument helper behavior changes, so the claim is about obligation-valid `parse` calls, not arbitrary direct calls to `put_match`. **UNKNOWN**: extraction shapes and tactic acceptance; repair must use the full new extraction/Lean log.

`r4-cpu-hash32` is a separate token-changing experiment: only regular `slot_of_m` changes from a 64-bit high-bit multiplicative hash to `k.wrapping_mul(0x9E37_79B9) >> (32-HB)`. Cardinality and dispatch stay fixed. The emitted old hash uses a 64-bit multiplier register, 64-bit `imul`, and high-bit shift; an immediate 32-bit multiply may lower register/instruction cost. It changes collisions and retained candidates, so `expected_equivalent=false` explicitly. The original `slot_of`/`insert` code used by small-text and chain routes remains as a control. Correctness still requires actual matches and bounded slot positions; the exact old proof is copied with fresh extraction status UNKNOWN.

| New candidate | Source SHA256 | Proof SHA256 | Expected token identity |
| --- | --- | --- | --- |
| `r4-cpu-directemit` | `023d3866d4ea46eac0a5837646484d6388f3c40d1af5f57f626d67d47d73e863` | `a420b275e7adee36074d4fb7393db811baa964d8243542a16e072e6512948537` | INFERRED under the parse obligation; actual UNKNOWN |
| `r4-cpu-hash32` | `12ec6bf664aa3a20052b197f8db0e324c39f241fd1a5749d18cda233dc451f40` | `e2c200cf084eca95eb70d26c0efb04e70d88f015315610d2a54d20b6adb7cf04` | NOT_EXPECTED; actual changes UNKNOWN |

Fresh generator `--check` reproduces all fifteen candidates and Python syntax passes. New outputs were generated with `--only`; prior thirteen bytes stay frozen. No performance result is claimed. No CI/commit/push/submission or wallet action was performed by this worker.

Minimum falsifiable next experiment: use fast3 and public432 in matched order blocks, plus the existing duplicate-fast3 negative control if available. For directemit, require public and boundary/generated token-prefix and DEFLATE hashes equal to fast3, independent byte validation, and emission assembly showing the repeated bounds/fallback branches removed. A useful signal then needs new extraction, Lean, axiom checks and complete gate before an independent runner replication. For hash32, do not assert equivalence; report per-file token/output changes, round trip and both compression axes, and check that the new immediate multiply actually replaces the original register multiply. If the total-axis gain does not approach 1% across matched blocks or a size loss moves the point behind fast3 after same-family calibration, stop the line. The roughly 7.4% parser reduction needed for a 1% fixed-token total-axis gain is a historical sensitivity, not a guarantee for these new candidates.

### Direct-emission call-site audit

There are exactly five source call sites for `put_match`, apart from its declaration. Their original proof contracts are retained:

| Source engine/call | Formal source of the required real match |
| --- | --- |
| `run` after search/lazy and `fold_w` | `find_spec` + `FoundAt.real`, lazy invariant, `fold_w_spec`; `main_loop_spec` carries Dec/MatchAt |
| `run_st` after `st_find` | `st_find_spec` returns FoundAt; `st_loop_spec` explicitly derives `FoundAt.real` in the taken-match branch |
| `run_dna` after `dn_find` | `dn_find_spec` and `dn_loop_spec` derive `FoundAt.real`; proof is retained even though current `DN_ON=0` |
| `e_pieces` for a permitted length piece | `LensBound`, remaining-match bytes and `MatchAt.piece`; `e_pieces_loop0_spec` derives a new MatchAt for every emitted piece |
| `run1` after `fold_w` | `probe_m_spec` + `FoundAt.real`, lazy invariant and backward-fold MatchAt; `main1_loop_spec` carries the current Dec state |

`run1t` and `run_z` use `e_pieces`, whose per-piece proof supplies the same precondition. The dormant planner emitter checks bytes separately and does not call `put_match`.

`Dec` gives `nt≤p` and `input.length≤out.length`; `MatchAt` gives `l≥3` and `p+l≤input.length`. Therefore `nt<out.length`, `nt+1≤usize::MAX`, and `p+l≤usize::MAX`. The candidate's `put_match_spec` now explicitly extracts these Dec bounds and the slice-length maximum before its steps, rather than relying on their discovery. No runtime check is substituted for missing match evidence, and no new axiom/assumption is added to the obligation. This is a source/proof dependency audit; the new all-call-site theorem acceptance remains UNKNOWN until actual extraction and Lean succeed. Public token identity alone cannot settle it.

Neither new candidate changes a main-loop acceptance condition or introduces another nested search loop. This avoids the particular B extraction failure reported by the parent (complex acceptance OR cloned the nested lazy loop), but does not prove the next extraction will succeed.

## D: outlining remains slower even with constants retained

Read `evidence/round4/37522012041/screen/` only; F inputs are frozen and unchanged. D total-axis changes versus fast3 are `fast3-shadow` +0.3151%/-0.2771% (mean about +0.019%), `flushzero` +0.2694%/+0.3919%, `run1tai` +0.7999%/+0.1222%, and `classoutline` +2.9604%/+3.4472%. A's small negative `run1tai` result did not independently reproduce as a total-axis improvement. No new CPU direction is selected from these data.

**VERIFIED classoutline code generation**: separate `run1_prose::<32768>` and `run1_text::<32768>` kernels each occupy `0x178a` bytes (6026). Prose's miss shift is the immediate `shr rax,0x5` at `efac`; text's is immediate `shr rax,0x3` at `11afc`. Their hash operations (`def7/defb` and `10a47/10a4b`) multiply and shift directly with no runtime km mask read. The kernels take only the input/output slice arguments, not skip/lazy/km settings; the `lazy=0` search loop is absent. The remaining variable `shr ...,cl` at `ed4b`/`1189b` is the backward-word mask, not the miss skip. The experiment therefore retained the settings that generic `run1ni` lost.

**VERIFIED structural costs**: `.text` is 323617 bytes, **6336 larger** than fast3, while main `parse` shrinks to `0x73a5` (29605). Main `parse` still probes/allocates a 128 KiB stack frame at `1217a-12198`; a taken outlined text/prose kernel probes/allocates another 128 KiB frame at `de9a-deb8` or `109ea-10a08`, and clears its head array. Fast3's corresponding parser uses one such main frame. Thus class outlining duplicated code/stack work rather than providing a general footprint reduction. Registers, code addresses and head-table stack placement also change. These are observed machine-code differences; without hardware counters their contributions to the full slowdown cannot be apportioned.

The regression is concentrated on the outlined routes: raw parser medians for `prose.txt` +38.36%/+38.22%, `bundle.min.js.txt` +33.69%/+33.10%, `source.py.txt` +35.45%/+35.26%, with near-unchanged encoder medians. Binary/database, machine-code, server-log and metrics examples remain near baseline. Consequently, constant loss is **not a sufficient explanation** for generic `run1ni`'s regression: a constant-preserving outline also regresses strongly. It is sound to report the generic kernel's extra runtime settings and the outline experiment's structural costs; it is not sound to assign the full +4.317% generic slowdown solely to runtime shifts, or to claim a measured I-cache/branch cause.

`flushzero` shows small raw parser decreases on some bins (-4.01%/-5.02% database and -4.45%/-4.26% machine-code), but its total axis is slower in both blocks. `run1tai` again shows faster raw parsers on several large files while encoder drift and the total axis do not establish a gain. The duplicate fast3 control changes sign across order blocks. Keep parser components as diagnostics and decide with matched official total ratios.

**VERIFIED finite checks**: `equivalence-research.json`, harness SHA256 `e51ddb9c7fb5de29b917fc5642711c6c376adde7911329bec375aaa5d53916e7`, returns 0 and reports 444 cases with zero different/failed cases for each of `flushzero`, `classoutline`, and `run1tai`. The harness is 28 public inputs plus 26 boundary lengths ×8 generated modes ×2 seeds (416 generated inputs), comparing counted tokens with fast3 and independently decoding them. Modes include source-like text, noisy text, prose, structured records, random bytes, parity data, zero-rich bytes and DNA-like bytes. A separate fresh local raw-file audit verifies public input, token/count, and DEFLATE output hash/length identity on 56 file/block records per CPU variant. These tests do not replace a full input-domain theorem or fresh obligation.

D's optional token-profile uses the old script SHA256 `0d722070...` and failed compilation on both selected parsers with the same unmatched JSON closing brace as C. `files=[]`, so D has no token-block distributions. The fixed `4f2e9f1d...` script is reserved for later runs; these failed profiles are not used as zero counts or cost evidence. D's perf capability remains denied. No candidate, generator, profiler or F frozen bytes were changed during this read-only attribution pass.

## D refinement: the flushzero mean reverses through normalization

Read all four blocks in `evidence/round4/37522012041/refine/`; no unfavorable file/block is removed. `flushzero`'s relative time-axis changes are **+0.26936%, +0.39191%, -2.72246%, -0.42319%**, mean about **-0.62110%**. The first screen's positive mean therefore flips mainly through block 3. Source and library identity do not change: fast3 source `bae80141...` / library `e3c97b3aef581e8e4a6e0f848cdd79427cdc9aa441d32c3110b73cc0508d3566`; flushzero source `ed565b50...` / library `a817dd0837b3884b67c138289d057142cfac1ac3a5ac9d6c54b1c445bdceb335` are fixed across four blocks. Engine/host hashes and reported AMD EPYC 7763 identity are also fixed. A fresh raw audit confirms candidate and incumbent input/token/output identities for all 112 file/block records.

To separate components without falsely adding independent medians, select the actual repetition at each method's median **total** time. Its parser and encoder sum to that total. For a file, with candidate total `C`, baseline total `B`, candidate-process incumbent median `I_C` and baseline-process incumbent median `I_B`, the exact ratio difference is:

`C/I_C - B/I_B = (P_C-P_B)/I_B + (E_C-E_B)/I_B + C*(1/I_C-1/I_B)`.

Average all 28 files and divide by the block's baseline axis. These terms are an arithmetic attribution, not proof of causal CPU/encoder/host effects:

| Block | Parser numerator | Encoder numerator | Incumbent normalizer | Full relative time-axis change |
| --- | ---: | ---: | ---: | ---: |
| 1 | -0.17223 | +0.24820 | +0.19339 | +0.26936 |
| 2 | -0.11694 | -0.29815 | +0.80699 | +0.39191 |
| 3 | -0.07035 | +0.11096 | **-2.76307** | **-2.72246** |
| 4 | -0.30071 | -1.19917 | +1.07669 | -0.42319 |

All cells are percentage-point contributions to the **relative time-axis percentage change**, not compression-size percentage points. Block 3's improvement is almost entirely due to a slower incumbent in the flushzero measurement process; the parser term is only -0.07035. Block 4 also includes sizable encoder and normalizer differences, despite identical encoded bytes.

Block 3 has several large normalizer differences rather than one discarded observation:

| File | Incumbent total median difference vs baseline process | Candidate own total difference | Contribution to relative time-axis change | Normalizer part |
| --- | ---: | ---: | ---: | ---: |
| `sparse.bin` | +16.860% | -0.579% | -0.9451 | -0.9085 |
| `binary.db.bin` | +9.075% | -1.467% | -0.3507 | -0.2975 |
| `catalog.xml.txt` | +12.507% | -0.218% | -0.3156 | -0.3095 |
| `tiny-config.json.txt` | +6.720% | +3.630% | -0.1569 | -0.3536 |
| `dump.sql.txt` | +8.444% | +0.588% | -0.1378 | -0.1490 |

The sparse incumbent parser median rises from **144.059 us to 268.451 us (+86.348%)** while its encoder median changes only -0.664%. Ten of its eleven measured parser repetitions are near 268-280 us, versus the baseline process's repetitions near 144-155 us. Thus this is not a single sample that median filtering removes. Database and catalog incumbent parsers rise +14.120% and +16.544%; SQL +9.651%, again affecting many repetitions. Their exact raw records remain in the receipt. These shifts could reflect execution interference or other runtime effects; perf/counter evidence is unavailable, so their cause is UNKNOWN.

The four-block mean is an observed public ratio and must be kept, but is **not sufficient evidence that zero-flush improves CPU speed or achieves a robust >=1% total gain**. A separate runner, with the exact source/library and incumbent provenance, matched forward/reverse blocks and the duplicate-fast3 control, is the minimum useful follow-up if the parent chooses to spend another CI run. It should retain all files and repetitions, report normalizer/component differences again, and resolve whether the effect persists before selecting this candidate. No code or frozen input was changed during this analysis.

## Optional shared-process relative diagnostic

`scripts/interleaved-round4.py` adds an optional experiment without changing `round4.py`, a workflow, or any official file. Read `ROUND4_SPEC`; absent/empty `interleaved_names` performs no build/output operations. Otherwise it accepts at most three distinct names already in that spec, always includes fast3 and the official incumbent, and checks both candidate file hashes against the spec before and after the experiment.

**VERIFIED API review**: the pinned `measure/src/main.rs` parses any vector of `name=crate-dir` arguments, loads every method, and iterates that vector in CLI order for each warmup/measured round. The driver intentionally calls the engine separately for each candidate, but its `_make_workspace`, `_generate`, `_build`, `_rustc_version`, `measure_sandbox` and `_cleanup` helpers can be used unchanged for this auxiliary call. Local AST review matches all six function signatures; the script also checks those signatures on the runner. The first implementation mistakenly used Windows CRLF working-copy hashes (`c17cb16c...` / `fe9ff7fc...`), which do not match Linux Git blob bytes. The parent caught this during review and corrected the hard locks by reading the fixed official Git objects: driver `8b29e832a5849c9e97649b390496dcda12c3ed081c39c0bf4a1c94d593f827e3`, engine main `ea4d6378fb0c03681488e4471a97ae001aa0dd3a61a30e9912606d5c4bd7adaa`. These corrected values are present in the shared script. A mismatch refuses the diagnostic rather than modifying official code.

The script uses the same official crate template, cargo release/offline build, fixed toolchain, encoder, 2048/4096-MB defaults, selected CPU, and read-only measurement sandbox as the parent round4 entry. One process uses `[incumbent, fast3, requested...]`; the second keeps incumbent first and reverses the entire non-incumbent group, placing fast3 at the opposite end. Each has one warmup and eleven measured repetitions per method/file. Every method's 28 public file records must have complete repetitions, round trips and deterministic hashes; raw `order_index` certifies actual method order. Cross-order token/output identities and loaded source/library hashes are checked. Any failure makes the optional report `AUXILIARY_DIAGNOSTIC_FAILED` even though the script returns zero to leave the primary experiment independent.

All complete engine stdout is preserved verbatim under `RUNNER_TEMP/round4-receipts/interleaved/`, with stderr, CLI/order metadata and a summary. The summary reports the equal-file total-time axis using the same process's incumbent per-file denominator, the axis ratio to fast3, separate unweighted candidate/fast3 file ratios, compression percentages and public hash equality. Independent parser/encoder medians are labeled as diagnostics, not added as though their medians necessarily sum. No admission, Pareto or reward calculation is made. This shares the reference observation rather than deleting a noisy record; order and cross-method execution interference can still affect times, so it does not replace the official per-candidate paired result.

Build libraries/toolchains are not uploaded. The pinned driver creates a unique child of `RUNNER_TEMP/round4-interleaved-build/`; resolved path/direct-child/non-symlink checks precede any cleanup. Only that exact child is deleted after confirmed success. Failed workspaces remain in the ephemeral runner until its disposal, with their path reported; neither the parent build directory nor the official checkout is removed. Engine, encoder, template, toolchain, incumbent and source/proof bytes are checked for changes.

**VERIFIED locally (first implementation)**: `py_compile` succeeds, the six AST signatures match, and a pure Python 28-file fixture accepts correct records while rejecting a roundtrip failure and wrong execution order. Its hash check matched the local CRLF files only; it did not verify Linux compatibility and was superseded by the parent's Git-blob correction above. **UNKNOWN**: actual runner build, sandbox invocation, multi-method results and timing behavior. No local Rust, CI dispatch, push or candidate edit was performed for this utility.

## F directemit: fewer predicates, no measured parser gain

Read `evidence/round4/37524045017/screen/`. **VERIFIED finite checks**: directemit's 444 cases return 0 with zero different/failed cases, harness hash `4ad5e34551a2c41178d131d5ed16d528390a74b86ebdef98703d05e063ae5f8f`. An independent raw audit confirms token count, token-prefix SHA256, output size/SHA256 against fast3 for all 56 public file/block records. This is not new Lean acceptance.

Using the exact total-median-repetition decomposition described above:

| Block | Parser numerator | Encoder numerator | Incumbent normalizer | Full relative time-axis change |
| --- | ---: | ---: | ---: | ---: |
| 1 | +0.40396 | +0.23673 | -0.09287 | +0.54782 |
| 2 | +0.23956 | -0.13733 | +0.52417 | +0.62640 |

There is no overall parser improvement hidden by the normalizer in these two blocks. Raw parser medians regress on `bundle.min.js.txt` +5.016%/+4.021%, `prose.txt` +3.197%/+6.413%, `machine-code.bin` +2.548%/+1.264%, and database +0.433%/+1.044%. Some files vary (metrics -0.552%/+2.191%, server +1.894%/-0.322%); all are retained. Repairing a failed all-path proof is not justified by an established speed signal in this version.

**VERIFIED assembly inventory** (static instruction counts include cold/panic blocks; they are not dynamic executed counts):

| Emitted function / source call-site coverage | Instructions base/direct | Conditional branches base/direct | Add-overflow panic call blocks base/direct |
| --- | ---: | ---: | ---: |
| `parse` / inlined `run1` instances | 8649 / 8697 | 1235 / 1176 | 19 / 19 |
| `run_rest` / regular `run` instances | 2645 / 2530 | 356 / 337 | 9 / 10 |
| `run_st` / stride writer | 303 / 283 | 37 / 34 | 2 / 2 |
| `run1t::<4096>` / `e_pieces` | 1256 / 1244 | 167 / 161 | 10 / 10 |
| `run_z` / `e_pieces` | 325 / 308 | 41 / 38 | 6 / 6 |

The fifth source call site, `run_dna`, is not emitted under the frozen `DN_ON=0`; its proof remains part of the candidate file. `pack_match` is inlined, so there is no new function-call cost. Pack construction remains a u32 shift/lea/add without a new packing overflow branch. The main `parse` size changes only `0x8d7b -> 0x8d71` (-10 bytes), and `.text` falls 720 bytes. Fewer guard branches do not make the loop uniformly smaller or faster: main parse has 48 more static instructions, while other writer bodies shrink.

There is direct evidence that removal loses at least some machine-level no-overflow information. The prose kernel is identified by its immediate miss shift `P_SKIP=5`: in fast3, pack at `12559` is followed by `12567 add rbx,rax`, then the record path at `126c2` without checking carry. In directemit, pack at `105c6` is followed by `105ce add r10,r9` and **`105d6 jb 17a9b`**; target `17aa2` calls `panic_const_add_overflow`. Thus an extra check on returning `p+l` is observed on this hot path. Some other base kernels already check that add (e.g. `1174d/1175d` and stride `18304/18307`), so the new effect is not claimed for every call. No extra `nt+1` or packing panic cost is established from the inspected sites.

A single separate return-wrapping variant is therefore falsifiable: use safe `wrapping_add` for `nt+1` and `p+l`, prove their natural values using the original Dec/MatchAt bounds, and compare the removed carry branch plus actual parser/total times with both fast3 and frozen directemit. It must not use unsafe or unchecked indexing. This candidate is justified by the emitted branch, not by a demonstrated speed gain; formal and runtime validation remain required. No F frozen byte is changed.

The repaired token-profile script now returns `DIAGNOSTIC_OK` in F for fast3, hash32, and alt299-halfpass. Its scope is untimed token/block statistics with independent byte validation, not encoder timing or proof; C/D's empty failed profiles remain unavailable.

## One follow-up: directemit wrapping returns

At the parent's explicit request after the carry-branch inspection, `r4-cpu-directemit-wrap` is generated as a separate candidate. It contains directemit's unchanged canonical packing and changes only the two returns to `nt.wrapping_add(1)` and `p.wrapping_add(l)`. It is not combined with zero-flush or another ablation. The machine-code evidence establishes a newly introduced **prose p+l carry check**; it does not establish that nt+1 gained a check or every path changed in the same way.

The `put_match_spec` statement, original Dec/MatchAt preconditions, canonical-token conclusion, and all-path caller proofs are retained. The new return proof applies the existing `wadd_val` theorem twice. Dec gives `nt≤p`; MatchAt gives `l≥3`, `p+l≤input.length`; the slice length is at most usize::MAX. Thus `nt+1` and `p+l` do not overflow in the function's specified domain and their wrapping values are the same sums. No axiom, weakened postcondition, unsafe block, or unchecked indexing is added. Actual extraction/Lean acceptance remains UNKNOWN, including the packing helper inherited from directemit.

- Source SHA256: `8589dc90cd895e84d02a11e850b9e753767c44338f7c4897511000ff1b2039c8`.
- Proof SHA256: `01c6b293c60336e8151ba94ec8b6869104f19c8784e196c016f86d06e7ce64b0`.
- Fresh `--check` reconstructs all sixteen candidates; Python syntax passes. Generation used `--only` for this new candidate. Frozen F directemit and hash32 source/proof hashes are unchanged.

The minimum test is fast3, frozen directemit, and this wrapping variant as distinct methods, with all public/generated token identities, public decoder checks, actual overflow-branch inventory and paired/same-process total measurements. If the new carry branch disappears but parser/total regression remains, the deleted check does not explain enough of the cost; stop rather than treating a smaller branch count as a win. If a useful signal appears, full extraction/Lean/axiom/gate and independent-runner verification still precede a correctness or front-position claim.

## Proof-only wrap v2 for two concrete F goals

Read the full goal contexts in `evidence/round4/37524045017/gate/r4-cpu-directemit-005-lake.log`. F reports two errors: `pack_match_spec` leaves the final total wrapping-add expression unbound, so its modular value is not discharged by the existing `step*`; `put_match_spec` has `i_post : i.val = LZ77.mkMatch d.val l.val` but its last tactic unfolds the target without using this equality. The errors are proof failures, not a new correctness result; F's native public token identity remains a separate finite observation.

`r4-cpu-directemit-wrap-v2` is the parent's requested **proof-only** derivative. Its Rust bytes are exactly the frozen wrap source, SHA256 `8589dc90cd895e84d02a11e850b9e753767c44338f7c4897511000ff1b2039c8`; the generator asserts both reference hash and byte identity. Proof SHA256 is `bcd69b587bd51a43658e517bf4fb6494c6e1ab453b3bd96e6dea78a99d324e13`.

Only two proof bodies change. The pack proof uses the existing cast-value/modulo lemmas to show `i.val=d.val`, `i2.val=l.val`; consumes the actual `i1_post2` and `i3_post2` implications to derive `i1.val=d.val*256≤8388608` and `i3.val=d.val*256+l.val≤8388866`; rewrites the final `core.num.U32.wrapping_add_val_eq` and removes its modulus with the established bound; then proves the unchanged canonical token formula. The writer's token-value argument becomes `simpa only [LZ77.mkMatch, LZ77.MATCH_BASE] using i_post`. Return-value wrapping proofs, function specifications, other caller proofs, imports, axioms and Rust code are unchanged. No sorry/admit/axiom is added.

**VERIFIED locally**: generator reconstruction and Python syntax pass, Rust byte equality holds, and the proof diff has only the two targeted hunks. **UNKNOWN**: v2 extraction/Lean/axiom/gate acceptance; no local Lean/Rust was run. The parent decides whether the weak H timing signal warrants a fresh gate. This repair creates no new CPU mechanism and cannot turn the native timing result into an improvement or a proof pass.

## CPU route disposition, reviewed 2026-10-06 22:51:33 UTC

**Decision: retain the frozen fast3 parser for the CPU route. No CPU derivative demonstrates a stable >=1% total-axis gain with reproducible evidence.** The native comparisons used the exact source hashes, public corpus, fixed encoder and pinned build. Complete public gate acceptance and timing benefit remain separate outcomes. This conclusion concerns the CPU family and the reviewed A/B/D/F/H receipts; it does not assert a global winner among the other round-4 research routes.

The route produced **17 candidate packages, 16 distinct Rust parsers**: all sixteen native variants were screened publicly; the seventeenth is proof-only `directemit-wrap-v2` with the same Rust bytes as wrap. Under the reviewed receipts, three distinct CPU candidates have complete public `accepted=true` gate reports: `run1tai`, `foldni`, and `flushzero`. There are four accepted CPU gate executions because run1tai was accepted again in D. F directemit and H wrap were rejected by Lean; wrap-v2 is **pending, not accepted**. Other unselected CPU candidates have no fresh complete-gate result in these reviewed runs.

| Family | Final reviewed paired result versus fast3 | Disposition |
| --- | --- | --- |
| `run1tai` | A four blocks -0.2773%; independent D four blocks +0.0774% | Correctness accepted; small timing result did not consistently reproduce |
| `foldni` | A four blocks -0.0023% | Correctness accepted; no total-time gain |
| `r1off/run1ni/commonni/stai` | A +1.782% / +4.317% / +0.823% / +0.265% | No gain; outlining/routing regressions discussed above |
| `flush/endreload` | B four blocks -0.0581% / +0.1144% | No robust benefit |
| `x2lazy/foldplain/slotonly` | B two blocks +0.792% / +1.081% / +1.135% | Slower initial screen; not upgraded |
| `flushzero` | D four blocks -0.6211%; H four blocks +0.2111% | Correctness accepted; D improvement depended heavily on the incumbent-normalizer event and did not reproduce |
| `classoutline` | D four blocks +3.0514% | Constant settings retained but text/prose kernels regress strongly |
| `directemit` | F two blocks +0.5871%; H four blocks +0.3390% | No overall parser/total gain; F Lean rejected |
| `directemit-wrap` | H four blocks +0.0986% | Removes a concretely observed check, but no stable measured gain; H Lean rejected |
| `hash32` | F final four blocks +0.5020% (two-block screen +0.3130%); size -0.006946 pp | Token-changing tradeoff, not a demonstrated CPU improvement; no fresh accepted CPU gate in reviewed receipts |
| `directemit-wrap-v2` | Same Rust as H wrap; no new independent timing result | Proof-only repair pending; never label accepted |

### H shared-process test and same-byte shadow

The independent local re-read of H's complete `forward-engine.jsonl` / `reverse-engine.jsonl` confirms 28 files, 11 measured repetitions per method, roundtrip/determinism success, and identical public token counts/hashes and DEFLATE output sizes/hashes for shadow, wrap and flushzero versus fast3. The summary reports `AUXILIARY_DIAGNOSTIC_OK`. The fast3 and shadow compiled libraries are exactly the same SHA256, `e3c97b3aef581e8e4a6e0f848cdd79427cdc9aa441d32c3110b73cc0508d3566`; all methods in a direction share its actual incumbent observation.

| Method | Forward shared-denominator axis delta | Reverse shared-denominator axis delta | Forward/reverse mean per-file total delta |
| --- | ---: | ---: | ---: |
| same-byte `fast3-shadow` | -0.3284% | +0.0287% | +0.0068% / +0.0311% |
| `directemit-wrap` | -0.4870% | +0.2205% | -0.1519% / +0.2209% |
| `flushzero` | -0.8005% | +0.7423% | -0.3714% / +0.4649% |

Forward order is `incumbent, fast3, shadow, wrap, flushzero`; reverse is `incumbent, flushzero, wrap, shadow, fast3`. This removes the separate-process denominator discrepancy for comparisons within each direction, but leaves execution-order and cross-method interference visible. Both proposed improvements reverse sign; the identical-byte control also varies. The small directional average is not evidence of a dependable gain or a private admission margin. All files, both directions and all repetitions remain in the receipts.

### Correctness coverage and exact receipt pointers

**VERIFIED finite identity**: A's six CPU candidates have public token/output identity checks. B's five, D's three, F's directemit, and H's directemit/flushzero/wrap also have successful 444-case token/decode checks (28 public inputs plus 416 fixed generated boundary cases). Repeated candidates reuse the same case family; these are not distinct new corpora each time. Hash32 deliberately changes tokens. No universal token-equivalence theorem is claimed from these tests.

**VERIFIED public gate acceptance**, at the exact parser/proof hashes in each gate state's spec:

- A `37515419910/gate/r4-cpu-run1tai-gate.json`, source `02690c07a5afd8bb13f25a6397680aa86128d7d65ae412e0591b3b8e166003aa`, proof `e2c200cf084eca95eb70d26c0efb04e70d88f015315610d2a54d20b6adb7cf04`.
- A `37515419910/gate/r4-cpu-foldni-gate.json`, source `5e61b341d942c0e8340607e10af8229cf450a4d432b76a3e7e7cec9989a4b699`, same proof `e2c200cf...`.
- D `37522012041/gate/r4-cpu-flushzero-gate.json`, source `ed565b50c03230c6f08027af5e3ac81691cce3f66917a34da09dce4bdbe056c3`, proof `2ec5a9f7471cc94d23822ecfa990a637215eeaede7c232616412cfce0efa312d`; D's separate `r4-cpu-run1tai-gate.json` also says accepted.

Each accepted report names only `corpus-stage1`, with 28 files / 15,930,000 raw bytes. Complete public acceptance does not observe private stage2, admission or rewards. Failed F/H proof reports are `37524045017/gate/state.json` plus `r4-cpu-directemit-005-lake.log`, and `37529887857/gate/state.json` plus `r4-cpu-directemit-wrap-005-lake.log`. H's final uploaded directory is named `gate/`, but its recorded `state.phase` is **`refine`**: the cancelled gate-stage upload preserved the completed refinement/interleaving evidence and an attempted wrap rejection, not a completed successful gate phase. The rejected versions are not repaired in place or presented as accepted.

All paths above are relative to `evidence/round4/`. The committed final receipt directories retain the earlier blocks and diagnostics: A `37515419910/gate/`, B `37517466397/gate/`, D `37522012041/gate/`, F `37524045017/gate/`, and H `37529887857/gate/`. Use each final directory's `analysis.json` and `round*-*.jsonl` for primary timing; earlier `screen/`/`refine/` pointers in the chronological notes describe the files read during execution. The archived shared-process evidence is H `37529887857/gate/interleaved/{summary.json,forward-engine.jsonl,reverse-engine.jsonl,forward-metadata.json,reverse-metadata.json}`. Earlier notes preserve the exact decomposition of D's normalizer-driven reversal and the emitted instruction evidence, including perf-counter denial.

Archive correction verified at 2026-10-06 23:02:05 UTC: F final `gate/analysis.json` has hash32 blocks `[1,2,3,4]`, relative time changes `[+0.134693%, +0.491315%, +0.480210%, +0.901843%]`, mean **+0.502015%**, size `36.59519315793334%` (delta `-0.006945948396840151` pp). The two-block `+0.313004%` figure is retained only as the earlier screen stage, not the final result. This update changes no raw record, candidate, script, ACL or run.

Fast3 retains source `bae8014121e4710f4a34ce63452578b4bf69121b4f695e1b1356780a019108ef` and proof `e2c200cf084eca95eb70d26c0efb04e70d88f015315610d2a54d20b6adb7cf04`, with its pre-existing complete public gate from `ROUND3.md` / `evidence/round3/selection.json`. The CPU exploration found no reproducible improvement sufficient to replace those frozen bytes. **UNKNOWN / pending** remain wrap-v2's fresh Lean/axiom/gate result; universal token equivalence beyond actual proofs; private stage2 transfer; official admission/ranking/payment; and the hardware cause of residual timing/order variation. No new submission, wallet, CI dispatch, candidate/script change, ACL adjustment or deletion is made in this evidence-only closeout.
