# Round 5 — H16 hybrid proof audit

Static audit at `2026-10-07T06:10:30Z`, checkout `35364becd33d611f2d590d664113365dc9452b81`. This note covers the two frozen H16 hybrids and their proof relationship to the accepted Round 4 H3R hybrid. It does not report a fresh H16 gate result.

## Conclusion and next decision

**VERIFIED:** Both H16 pairs reproduce their declared composition exactly. There is no static evidence of a missing engine spec, duplicate top-level obligation, altered parent engine body, or leaked local step rule. `r4-hybrid-h16-smallc299/Parse.lean` is byte-identical to the proof used by the accepted H3R hybrid. The appropriate first check is each frozen pair's own official re-extraction and complete gate.

**INFERRED:** The existing proofs are plausible candidates for acceptance without repair. The accepted H3R proof took **725.4 seconds in its individual Proof/Parse.lean call**, not 889.7 seconds. Its observed margin to the unchanged 900-second per-call timeout was 174.6 seconds, equivalent to about 24.1% additional elapsed time. This is one runner's historical margin, not a fresh H16 runtime guarantee.

**UNKNOWN:** Both H16 hybrids' own full-gate acceptance and elapsed time; any private stage2 result, admission, rank, or reward. Round 4's two public paired blocks and round trips do not fill the proof-gate gap. Await the root thread's original-byte gate logs before creating a repair candidate.

## Frozen pairs and exact composition

| Candidate | Rust SHA256 | Lean SHA256 | Rust / Lean bytes |
|---|---|---|---:|
| `r4-hybrid-h16-small299` | `d9826bc92ba02f49cb6e552ed172a4fb82dc10fa8fb51aacf73e7947ed38a94d` | `ac2d894b3a4ccacb30ce4ed654a3dd3d3b3c167183eb8df008168772109215fa` | 176326 / 375539 |
| `r4-hybrid-h16-smallc299` | `39c82b4673440faaa7cf9f14ccbeb9367128a7f50a8ca8472880dc35ed24b83e` | `eec49d582853cddf843c33b950f444520561bbb40ef0197ee64ce9acfbb92791` | 176423 / 375553 |
| accepted `r4-hybrid-h3r-smallc299` | `6814b45429d9dbbb66a94a2a18abca39bd23790756490e8acbb62e79306d18d9` | `eec49d582853cddf843c33b950f444520561bbb40ef0197ee64ce9acfbb92791` | 176422 / 375553 |

The fresh read-only audit independently reconstructed each Rust and Lean file from the actual parents plus the entry strings in its `composition-audit.json`, and compared complete bytes and manifest hashes. It did not execute a candidate generator or any Rust/Lean toolchain.

**VERIFIED proof composition:**

- #299's complete proof segment is 279481 bytes after the only renames: `parse_spec` to `s_parse_spec`, and its two `slot.parse` references to `slot.s_parse`.
- The H segment is 95536 bytes after removing its duplicate imports and uniform top-level `parse_spec`. Its complete `EH` namespace and shared `T9!`/`T10!` macros are retained.
- Three separately closed/reopened `Submission` scopes isolate the original #299 local rules, the original H local rules, and the new entry rules. The final scope registers `s_parse_spec` and `EH.parse_mode_spec`; content-routing variants additionally register the original `classify_spec`.
- There is exactly one final `Submission.parse_spec` with the original length bound, unchanged output length, and `LZ77.Valid` postcondition. No `axiom`, `sorry`, or `admit` declaration was found by the static declaration check. The official axiom query remains mandatory.
- All parent functions, constants, and custom types are preserved by exact text reconstruction, except the #299 `parse` rename and removal of H's obsolete uniform wrapper. The Rust function count is 233.

The independent syntactic call graph from `parse` reaches **232 of 233** functions. The sole unreachable declaration is #299's 133-byte test entry `parse_cfg` at Rust lines 261–264; no `slot.parse_cfg` reference appears in either combined proof. This is a small source-only pruning possibility, not a demonstrated solution to a Lean timeout. The graph includes calls in dynamically untaken branches; it does not prove every mode-dependent H branch executes.

Sources: `scripts/make-round4-hybrid.py`; both H16 `composition-audit.json` and `manifest.json`; `references/round4-public-299`; `candidates/r4-parse-h16d64-core`; `candidates/r4-parse-hmode-3-i8`.

## Differences from the accepted H3R combination

**VERIFIED:** `h16-smallc299` and `h3r-smallc299` have identical complete Lean files. Their Rust files differ at exactly these six locations; all other bytes are equal:

| Rust location in H16C | H16C | H3R |
|---|---:|---:|
| line 2936, `H_BTD` | 64 | 32 |
| line 2938, `H_BTDS` | 32 | 16 |
| line 2964, `H_ITERS` | 16 | 8 |
| line 4892, `H_BTDMC` | 64 | 32 |
| line 4900, `H_BTDX` | 64 | 32 |
| line 5214, final `h_parse_mode` argument | 0 | 3 |

The H spec is quantified over `mode`; it does not assume mode 3. The changed search/iteration constants and extracted entry still require re-extraction and fresh elaboration. Proof-byte equality alone is insufficient for acceptance against different extracted definitions.

**VERIFIED:** `h16-small299` and `h16-smallc299` use the same parent engines and constants. Their entry differs only by the original #299 classifier override after the `<65536` small-input branch. Their Lean files differ only at line 7952: `classify_spec` is added to the final local step registration for the override variant. Both use H mode 0.

## Correct 900-second risk accounting

Accepted H3R receipt: `evidence/round4/37544346810/gate/r4-hybrid-h3r-smallc299-gate.log`, CI `37544346810`, commit `5d8fa14eeff8d1558068fdd2a1b94ab06fea0270`.

| Call/interval | Observed seconds | Evidence |
|---|---:|---|
| extraction prepass | 1.4 | gate log line 5 |
| Charon/Aeneas extraction | 90.2 | gate log line 6 |
| Lean version preflight | 2.7 | gate log line 8 |
| trusted libraries / extracted Slot build | 62.0 | gate log line 9 |
| `Proof/Parse.lean` elaboration | **725.4** | gate log line 10 |
| `Verify/Obligation.lean` elaboration | 4.1 | gate log line 11 |
| dedicated axiom query | 2.2 | gate log lines 12–13 |
| intake through end of axiom stage | **889.7** | gate log line 14 |

The call names are mapped from the unchanged sequential `stage_build` and `stage_axioms` implementation in `sources/conjectures-optimisation-deflate/validator/verifier/verify.py`. `LEAN_TIMEOUT` defaults to 900 at line 94; the Proof/Parse call and Obligation call each receive their own timeout (lines 385–410), and the axiom query receives a separate timeout at line 422. The 889.7-second log records `time.monotonic() - t0` for the whole validation interval at line 703. It is not a single shared 900-second budget.

**INFERRED:** H16C has essentially the same proof burden as H3R, but values in extracted constants can change simplification cost. Doubling a Rust execution budget does not establish doubled Lean elaboration time: the inherited loop specs prove totality by induction rather than running the compression loop. A direct runtime forecast remains unsupported.

The #299 proof accounts for about 74.4% of combined Lean file bytes, but no per-theorem or per-engine timing exists in the accepted receipt. File size does not establish where 725.4 seconds were spent. The earlier large-H timeout and successful H-only core reduction recorded in `ROUND4.md` explain why dependency trimming matters; the current H portion is already that 95KB core.

## Repair branches after the fresh logs arrive

1. **Both original pairs pass:** Preserve frozen bytes and record each source/proof hash, re-extraction hashes, statement/obligation/axiom status, raw call times, public round trip and generated-input checks. A repair candidate is unnecessary.
2. **Named elaboration error:** Use the actual extracted call/name and error location. Create a suffixed `candidates/r5-h16-*` pair and adapt only the named proof/spec or its registration. Preserve the parent engine declarations unless the error demands a source change. Re-run the complete official gate; a local text check is not acceptance.
3. **Proof/Parse reaches 900 seconds:** First establish the failed individual call and its log, then identify the slow theorem/section using a CI-only diagnostic run with the frozen pair. A suffix proof-only refactor can replace a measured slow tactic block with an equivalent explicit derivation. The unchanged obligation and axiom checks must pass. Do not infer that the final 520/534-byte entry theorem consumed the whole timeout.
4. **Substantial mode-dependent trimming is justified:** A possible new `r5-h16-small299-mode0core` / `r5-h16-smallc299-mode0core` family would specialize the H mode argument consistently through `h_parse_mode`, `h_champ[_if]`, `h_optimize`, `h_iterate`, `h_eval_mode`, `h_mode_gk`, and `h_mode_damp`, then recalculate Rust and Lean dependency closures. Known mode-2/3/5/6 restart branches and mode-4/6 branches become removable. This changes extracted function bodies and therefore requires adapted proofs, official extraction, complete gate, finite token/output equivalence and paired performance. It is a proposal, not a generated or accepted candidate.

**VERIFIED limit of simple pruning:** The only current syntactically dead function is `parse_cfg`, which has no proof block. Removing it cannot remove either large proof namespace. Mode-0 branch specialization may remove meaningful H proof work, but its amount and migration cost are **UNKNOWN**. The original small route can still select all #299 A/B/C engines by generic input features, so there is no static justification to discard an entire #299 engine merely because large default inputs use H.

This audit writes only this note. Frozen candidates, official `sources/`, gate, pins, workflows and main orchestration scripts are unchanged by this proof line. CI dispatch, Git actions and external submissions remain with the root thread.

## Update — H16C gate and complete per-file route analysis

Evidence reviewed on `2026-10-07T06:42:24Z`. This update supersedes the earlier H16C gate-UNKNOWN status; the small-only pair's gate was still running when the root supplied this update.

**VERIFIED: H16C needs no proof repair.** CI `37580365335`, commit `8cddb52db662f2c45d8de42e412a140ea6640e59`, accepted the unchanged source/proof pair. The new gate log records extraction 69.0 seconds, trusted-library/Slot build 48.8 seconds, `Proof/Parse.lean` 557.5 seconds, Obligation 2.7 seconds, and axiom query 1.9 seconds. Intake through axioms was 684.2 seconds. Static policy, official re-extraction, unchanged 900-second statement limits, the three permitted axioms, all 28 public files, and eight fixed generated inputs in both blocks passed. This is public gate evidence, not stage2/admission/reward evidence. The different runner prevents interpreting its shorter elapsed time versus old H3R as a proof optimization.

Receipts: `evidence/round5/37580365335/gate/{gate-summary.json,state.json,r4-hybrid-h16-smallc299-gate.log}`. Actual official extraction is preserved under `extracted-r4-hybrid-h16-smallc299/`: `Funs.lean` SHA256 `6f6fcb54815afc8f5e085e885157f174c7b713b652ac86849df67e6760e9a72c`, `Types.lean` `8fa2e327496215fc5176c37a70cf333d7afcb6c6febbcc7ce81bf06254025b28`, and `Constants.lean` `65c8f96c5ecfc64349d7941042cb6144a4fe6fb467cbb21d7ed350c8107f9a67`. The actual extracted entry at Funs lines 18574–18588 is a size split, one total `classify` call, and branches calling only `s_parse` or `h_parse_mode ... 0`.

### Provenance and route matrix

The Round 5 measurements are from `37580297956/refine` (AMD EPYC 7763, small-only H16) and `37580365335/refine` (Intel Xeon 6973P-C, H16C), both at commit `8cddb52db662f2c45d8de42e412a140ea6640e59`. Each has two blocks with one warmup and eleven measured repetitions per method/file. All 28 file hashes match between the respective candidate and its same-run `public299`; each candidate and #299 has identical output/token hashes in its two blocks. Old H3R's two blocks also have identical output/token hashes, and all 28 input hashes match Round 5. Only output/token bytes are compared to old H3R across runners; its timing is not used as a paired speed comparison here.

All 28 official public inputs were read into memory from [corpus commit 0260078125ab5576ca85e17dfecb8bf25ec25ee8](https://github.com/conjectures-io/conjectures-compression-corpus-1/tree/0260078125ab5576ca85e17dfecb8bf25ec25ee8/corpus), with exact length/SHA256 checked against the JSONL receipts. No corpus files or toolchains were saved locally. The original `BYTE_CLASS`, 32 evenly spaced 1KiB sampling windows, integer per-mille calculation, branch order and thresholds were reproduced directly from #299's frozen Rust to obtain these classes. File names below identify evidence rows only; they are not proposed dispatch conditions.

`S` means the unmodified #299 portfolio, `H` means H16 mode 0. All byte counts are final official-encoder outputs. ΔC/S and ΔC/H3R are H16C minus the indicated parent/reference.

| File | Class | small / C route | #299 bytes | H16 small bytes | H16C bytes | H3R bytes | ΔC/S | ΔC/H3R |
|---|---:|---|---:|---:|---:|---:|---:|---:|
| binary.db.bin | 4 | H / H | 70957 | 71258 | 71258 | 71321 | +301 | -63 |
| bundle.min.js.txt | 11 | H / H | 287432 | 287541 | 287541 | 287503 | +109 | +38 |
| catalog.xml.txt | 5 | H / H | 58085 | 58414 | 58414 | 58414 | +329 | 0 |
| compressed.bin | 3 | H / S | 299566 | 299569 | 299566 | 299566 | 0 | 0 |
| config.yaml.txt | 12 | H / H | 81033 | 81121 | 81121 | 81095 | +88 | +26 |
| docs.md.txt | 12 | H / H | 215548 | 216052 | 216052 | 215595 | +504 | +457 |
| dump.sql.txt | 8 | H / H | 16397 | 16439 | 16439 | 16440 | +42 | -1 |
| genome.fasta | 1 | H / S | 256489 | 256729 | 256489 | 256489 | 0 | 0 |
| images.bin | 3 | H / S | 223464 | 223489 | 223464 | 223464 | 0 | 0 |
| lean.txt | 12 | H / H | 222969 | 223067 | 223067 | 222941 | +98 | +126 |
| machine-code.bin | 4 | H / H | 159287 | 159658 | 159658 | 159542 | +371 | +116 |
| metrics.csv.txt | 7 | H / H | 251759 | 252057 | 252057 | 252090 | +298 | -33 |
| multibyte.txt | 12 | H / H | 254418 | 254423 | 254423 | 254388 | +5 | +35 |
| page.html.txt | 6 | H / H | 98951 | 99002 | 99002 | 99001 | +51 | +1 |
| prose.txt | 12 | H / H | 541121 | 541386 | 541386 | 541154 | +265 | +232 |
| records.json.txt | 10 | H / H | 69102 | 69227 | 69227 | 69232 | +125 | -5 |
| server.log | 9 | H / H | 25947 | 26025 | 26025 | 26033 | +78 | -8 |
| source.c.txt | 12 | H / H | 333235 | 333421 | 333421 | 333365 | +186 | +56 |
| source.py.txt | 12 | H / H | 125183 | 125270 | 125270 | 125187 | +87 | +83 |
| source.rs.txt | 12 | H / H | 126017 | 126285 | 126285 | 126134 | +268 | +151 |
| sourcemap.map.txt | 11 | H / H | 64464 | 64459 | 64459 | 64433 | -5 | +26 |
| sparse.bin | 2 | S / S | 1193 | 1193 | 1193 | 1193 | 0 | 0 |
| tiny-app.log | 0 | S / S | 835 | 835 | 835 | 835 | 0 | 0 |
| tiny-config.json.txt | 0 | S / S | 2076 | 2076 | 2076 | 2076 | 0 | 0 |
| weights-bf16.bin | 3 | H / S | 353965 | 354028 | 353965 | 353965 | 0 | 0 |
| weights-f16.bin | 3 | H / S | 212660 | 212660 | 212660 | 212660 | 0 | 0 |
| weights-f32.bin | 3 | H / S | 279059 | 279107 | 279059 | 279059 | 0 | 0 |
| weights-q8.bin | 3 | H / S | 235572 | 235572 | 235572 | 235572 | 0 | 0 |

**VERIFIED diagnosis:** The three `<65536` files contribute zero output or token differences versus #299/H3R. All size losses are on larger inputs. The existing classes 1–3 override recovers 379 output bytes and 0.002335034013600 percentage points from the small-only hybrid; these changes are on seven larger files. H16C then routes ten public files to #299 and eighteen to H16. All ten #299-routed files have identical #299 token/output hashes. H16C's remaining loss versus #299 is 3200 bytes and **0.018047755221 percentage points** on the mean-file-size axis. Its loss versus H3R is 1237 bytes and **0.005326846071 percentage points**; the eight class-12 files account for 1166 bytes and **0.004795651670 percentage points**. This locates the remaining difference in large-input parsing, not the small-input cutoff.

The new token/block diagnostic did not execute: both Round 5 `token-profile.json` receipts say `DIAGNOSTIC_FAILED` because their batch paths were absent at the diagnostic step. The official JSONL token/output identities above remain available. These receipts do not establish a lower-level DP or block-cost cause for the large-text loss.

### Restoring a #299 class cannot reach the stated size line

Use the actual equal-file formula, `y = mean(100 * output_bytes / raw_bytes)`, rather than total compressed bytes. The requested comparison line **33.8423685%** is a parent-supplied conditional #299 mapping target; this audit does not verify an admission guarantee or transfer it from #453 to H.

Current public `y` is 33.863213837353% for small-only H16 and 33.860878803340% for H16C. The latter needs a further 0.018510303340 percentage-point improvement to fall below that line. The following numbers replace only an entire existing class with its frozen #299 output; they are exact finite-corpus portfolio calculations, not measured new candidates.

| Additional class restored in H16C | Files | y improvement (pp) | Resulting y (%) | Below 33.8423685? |
|---|---:|---:|---:|---|
| 4: structured binary | 2 | 0.004800000000 | 33.856078803340 | No |
| 5: markup, many lines | 1 | 0.002350000000 | 33.858528803340 | No |
| 6: markup, few lines | 1 | 0.000303571429 | 33.860575231911 | No |
| 7: quoted numeric tables | 1 | 0.000818681319 | 33.860060122021 | No |
| 8: numeric rows with commas | 1 | 0.001000000000 | 33.859878803340 | No |
| 9: numeric lines | 1 | 0.000928571429 | 33.859950231911 | No |
| 10: quoted text | 1 | 0.001116071429 | 33.859762731911 | No |
| 11: long lines | 2 | 0.000338265306 | 33.860540538033 | No |
| 12: default text | 8 | 0.006392594310 | 33.854486209029 | No |
| 7 and 8 together | 2 | 0.001818681319 | 33.859060122021 | No |
| All classes: original #299 | 28 | 0.018047755221 | 33.842831048119 | No |

Classes 0–3 have zero further restoration benefit in H16C. The same class-7/8 restoration yields 33.861395156034% for small-only H16. **Even an unrestricted per-file oracle choosing the smaller current #299/H16 output** yields only **33.842780027710%**, still **0.000411527710 pp above** the line. Its only benefit over full #299 is retaining H16's five-byte smaller source-map output. Therefore, with these fixed public inputs and encoder, no choice of existing H16/#299 routes can reach the requested size line. A new parser/encoder-output improvement is required; this finite-corpus bound is not a statement about hidden stage2 data.

### One minimal supported route improvement, with a stop condition

If a later new mechanism creates enough size margin to make a small speed/size cleanup useful, the smallest supported route change is to extend H16C's original override with **`c == 8`**, while retaining the existing `<65536` and classes 1–3 routes. This reuses #299's numeric-row class and its original A-engine configuration. It introduces no new classifier threshold, pass budget, filename, hash, or exact-file-length condition. The source delta is one additional generic predicate in the final wrapper; both engine bodies stay frozen.

**VERIFIED predicate evidence:** Only `dump.sql.txt` is class 8 in this fixed public corpus. Its sample shares are digits 312 per mille, commas 94, quotes 0, and newlines 37; earlier DNA/binary/markup tests are false. #299 is 42 encoded bytes smaller than H16 and uses fewer milliseconds in all four runner-block comparisons. Its measured total time relative to H16 is reduced by 36.415%, 35.713%, 24.712%, and 33.964%, respectively. These are raw per-file observations within the same runner, not a calibrated online axis.

| Current hybrid baseline / block | Measured baseline x | class-8 portfolio prediction x | Change relative to same hybrid |
|---|---:|---:|---:|
| small H16, AMD block 1 | 7.275320991 | 7.165127327 | -1.515% |
| small H16, AMD block 2 | 7.262389853 | 7.150236879 | -1.544% |
| H16C, Intel block 1 | 6.633440635 | 6.533929738 | -1.500% |
| H16C, Intel block 2 | 6.747979085 | 6.653173946 | -1.405% |

**INFERRED speed scope:** Each prediction retains that hybrid's measured paired-incumbent per-file ratios and replaces the one class-8 ratio with the same runner/block's measured #299/incumbent ratio, then recomputes the equal-file mean. The comparisons are to the current H16 hybrid family; no #453 or cross-family formal speed coefficient is applied. Extra wrapper code and changed compiler layout are unmeasured, so these are portfolio predictions, not realized candidate speedups. Class 7 is not automatically added: its #299 output is 298 bytes smaller, but its raw total-time advantage is not uniform (H16C's Intel block 2 is about 0.457% faster than #299 on that file). Restoring both numeric classes would predict a 1.765%–1.895% x reduction and 0.001818681319 pp y reduction, but it is a larger experiment than the selected one-class change.

**INFERRED proof cost:** Actual Funs lines 18574–18588 show no generated inner loops in this wrapper. The existing total `classify_spec`, `s_parse_spec` and universally quantified `EH.parse_mode_spec` already cover every leaf. Adding `c == 8` should change only the extracted top-level Boolean branches; the three existing final local-step registrations and the original obligation statement suffice structurally. A new suffix still requires official re-extraction, full Lean/axiom gate, round trip and measured performance; no new suffix or proof acceptance is claimed here.

**Decision:** Do not run a route-only third candidate to pursue the 33.8423685% line: even its unrestricted finite-corpus oracle cannot reach it. Keep this class-8 cleanup as an optional follow-on to a genuinely new measured mechanism. This update adds only evidence and a conditional proposal; it creates no candidate, CI run, submission or transaction.

**Threshold qualification:** The 33.8423685% comparison line is limited to the root's current working snapshot (the downloaded Round 5 analysis records snapshot `25678`), comparable times in the relevant frontier segment, and the stated #299 public-to-formal size-factor hypothesis. A changed frontier, a different time position, or a different migration factor can change the necessary line. The oracle excludes only pure selection between these fixed public #299/H16 outputs under that conditional target. It does not prove a private-stage2 impossibility, actual rejection, or inability to earn a reward. Per the root's decision, the class-8 proposal remains unimplemented while new mechanisms are compared.

## Update — small-only timeout and proof-only candidate

**VERIFIED original failure:** CI `37580297956` at commit `8cddb52db662f2c45d8de42e412a140ea6640e59` re-extracted the frozen small-only pair, built the extracted Slot in 77.3 seconds, then rejected stage 4 because `Proof/Parse.lean` did not finish within 900 seconds. The log contains no per-theorem profile and does not identify the slow theorem. This failure must remain a failure in the original candidate's record. Source: `evidence/round5/37580297956/gate/r4-hybrid-h16-small299-gate.log`; actual Funs SHA256 is `a7462b3a8e73f687beecf9b459f3435ff4958322475d7db0dfb91b7d45c16061`. The two original H16 proofs differ only in the final classifier-step registration, so the accepted Intel H16C result does not prove that the small-only pair fits the limit on AMD.

**Correction to the earlier semantic claim:** The initial 232-function graph was purely syntactic and included `b_engine` through a branch in `plan_cfg`. Contrary to the earlier statement that all A/B/C engines could be selected, every one of the **sixteen frozen CFG rows has engine ID 0 or 2**; none has engine ID 1. Thus every possible configuration index, including `k >= 16` reduced by `% 16`, excludes B. This table fact supplies a substantial proof-only pruning route that the earlier syntactic graph did not detect. No A or C engine can be removed by this argument.

The actual extracted `slot.plan_cfg` at Funs lines 11266–11300 confirms the only B call lies under `i1 = 1#usize`, where `i1` is the index-0 read from `CFG[k % 16]`. The source and official extraction remain unchanged.

**VERIFIED new artifact generation:** `scripts/make-round5-h16.py` generates only `candidates/r5-h16-small-proofopt/{parse.rs,Parse.lean,manifest.json,proof-audit.json}`. Its generator SHA256 is `094d98274891706df53b0087a8d8704b091dd5e460aed3ae45657b7a7284a1a4`. Generation and the explicit no-write `--check` mode both completed with exit 0; an independent read-only check compared the entire Rust file and final public obligation scope to the frozen parent.

| Artifact | SHA256 | Bytes |
|---|---|---:|
| new Rust = frozen small-only Rust | `d9826bc92ba02f49cb6e552ed172a4fb82dc10fa8fb51aacf73e7947ed38a94d` | 176326 |
| new Lean | `d55744de52bb0469768f0bbfd73ffecbabf9899b63e0167469fd7bb79c6293c7` | 264194 |
| removed B proof segment | `12798ca2cea0faaecf3f34f4e2d8263d9eeca95d51f171f3ccb52e5ddd34c5a5` | 112452 |
| added table/branch/leaf lemmas | `fa11b2b194013bda06901dd975ed1aa73c5afbe3efc4009c5c1f9c67b2db3b0b` | recorded in generator |
| revised `plan_cfg_spec` discharge | `be8b3c674a5632441b2fa7104391da8bedde3bb4170a26004ecb5bfeb9e80b32` | recorded in generator |
| preserved final public scope | `e4ee1b51b33c94082b961a69ff36ea72be3b44ef74d914b75e43074d0cd8e9ed` | unchanged |

The Lean file decreases by **111345 bytes**. Original B lines 1842–4159 are removed, comprising **104 declarations**. All A/C/H proofs, shared spine/emission proofs, `s_parse_spec`, and final `Submission.parse_spec` remain byte-preserved except the narrowly specified `plan_cfg_spec` discharge. Reverse substitutions plus restoration of the B block reproduce the original complete proof exactly. Rust equality gives no compression-policy change; no performance-axis gain is claimed.

The replacement is deliberately conditional at the internal B leaf:

1. `spine_CFG_noB` proves the actual frozen table's first-column property by `unfold slot.CFG; decide`.
2. `spine_knob_notB` combines that property with the actual `Array.index_usize` read equality and the actual branch hypothesis `x0 = 1#usize` to derive `False`.
3. `spine_b_engine_unreachable_spec` has a `False` premise, proved by `False.elim`; it is a local step rule so `step*` leaves the premise as an obligation rather than elaborating the entire B engine.
4. The revised `plan_cfg_spec` explicitly discharges that premise with steps 1–2 and real row membership. The public entry assumes only its original output-length bound, never `False`.

This does not establish a general B-engine totality theorem. It establishes why the frozen parser's B branch is impossible for every actual configuration. The original all-input `LZ77.Valid` obligation, imported libraries, axiom whitelist, official source, and 900-second limit are unchanged.

### Removed-declaration dependency audit

The complete removed-name list and all registration targets are in `candidates/r5-h16-small-proofopt/proof-audit.json`.

- **Explicit dependencies:** After masking nested block comments and line comments, none of the 104 removed declaration names occurs outside the B segment. This includes theorem bodies and attribute references. Comments mentioning historical B exports are not proof dependencies.
- **Automatic step dependencies:** All **56 globally active local-step rules** from the removed segment target only `slot.b_*` functions or `slot.B_*` constants. The only retained inferred call to such a function is `slot.plan_cfg`'s impossible B branch, now covered by the new conditional leaf rule.
- **Generic rules:** B's Array/Vec helpers are not globally registered. The seven `attribute [local step] ... in` groups occur only inside B theorem declarations: `engB_arr_index_le engB_arr_update_le`; `engB_arr_index_le_d engB_arr_update_le_d`; `engB_arr_index_mut_spec`; `engB_arr_index_mut_spec_b`; `engB_arr_index_le_g engB_arr_update_le_g engB_arr_index_mut_spec_c`; `engB_arr_index_le_f`; and `engB_arr_index_le_e`. Those registrations end with their B theorem scopes and are removed with them. No B `simp` or `scalar_tac` registration is removed.
- **Preserved scope:** The complete final public theorem scope has the same hash as the parent. The three original closed/reopened `Submission` scopes still occur exactly once each. Static checks find no added `axiom`, `sorry`, or `admit` declaration.

**INFERRED optimization hypothesis:** Skipping the 104 unused B declarations and their tactic/mvcgen work can reduce elaboration cost. The actual time saved is unmeasured; the original log has no per-theorem timings, and proof-file size is not a runtime estimate.

**UNKNOWN until the root runs the complete official gate:** New Lean elaboration, automatic rule selection, axiom acceptance and finishing under 900 seconds. The local Python checks verify generation and dependency/text properties only. The original failure is not reported as repaired. The root owns CI dispatch, subsequent error logs and the final acceptance verdict; no local Lean/Rust toolchain, CI run, Git action or transaction was performed by this proof line.

## Update — C timeout on another runner and matched C proof candidate

**VERIFIED additional failure evidence:** CI `37581080647`, commit `c47efca9476f375d0e801610ea90c6367530aff2`, rejected both frozen H16 pairs at stage 4 for the unchanged 900-second proof timeout. Receipts are `evidence/round5/37581080647/{h16-small-gate,h16-smallc-gate}/gate/`. Small-only extraction was 104.9 seconds and Slot build 76.7 seconds; C extraction was 105.6 seconds and Slot build 83.1 seconds. The original H16C retains its successful 557.5-second proof/gate receipt on runner `37580365335`, alongside this later timeout; neither result overwrites the other. The cause of the elapsed-time difference is still UNKNOWN, but one success is insufficient evidence of a stable timeout margin across runners.

At `2026-10-07T07:00:48Z`, the generator was extended to a second explicitly selected recipe, `--only r5-h16-smallc-proofopt`. Its default still selects the original small-only recipe. It now hard-locks all four existing small-only outputs and skips writing byte-identical existing files. A check of the small-only pair ran before C generation; a combined check and independent comparison ran afterward. **All four existing small-only files remained EXACT bytes**, including metadata:

| Existing small-only file | Preserved SHA256 |
|---|---|
| parse.rs | `d9826bc92ba02f49cb6e552ed172a4fb82dc10fa8fb51aacf73e7947ed38a94d` |
| Parse.lean | `d55744de52bb0469768f0bbfd73ffecbabf9899b63e0167469fd7bb79c6293c7` |
| manifest.json | `1d96b09a4305f9bdc88c57cb51efc951d507bc98c6b98d7d88d271a0e866d68e` |
| proof-audit.json | `37badcccfb3f9551dcc326f5fd8785123c997544fc9a8258c715eac73261486d` |

The current generator SHA256 is `0823f1cf72afacf2d767405f013505acd5632d94cb523d6341e7c02b29b5a376`; the earlier generator hash above identifies its original one-recipe version.

**VERIFIED new C artifacts:**

| `candidates/r5-h16-smallc-proofopt/` file | SHA256 | Bytes where relevant |
|---|---|---:|
| parse.rs = frozen H16C Rust | `39c82b4673440faaa7cf9f14ccbeb9367128a7f50a8ca8472880dc35ed24b83e` | 176423 |
| Parse.lean | `c186520fff7d078e0911f92d1b1aeeb3798cfc5292d1ec2415db4610690ca0d1` | 264208 |
| manifest.json | `d896f2fcc606fed122618a69465d86d8c04e8fc467909a59e1143ceecd3547f8` | — |
| proof-audit.json | `3d737af3676803122a3d55ad46cdb0c1029f991448147af7ea4d69039b920d7a` | — |

The C recipe removes the same 112452-byte B proof block with SHA256 `12798ca2cea0faaecf3f34f4e2d8263d9eeca95d51f171f3ccb52e5ddd34c5a5`, the same 104 declarations, and the same explicit/automatic dependency checks. Its new Lean differs from the existing small-only proofopt file only by the preserved final `classify_spec` local registration. Its complete original C public scope is byte-identical to the frozen C parent, SHA256 `ca36f036d076df78dc8a5e4dce2951380e0f8844f0f540542aa433cda46742ff`. C's route, constants, engines and output policy are unmodified.

Both `--check` recipes completed with exit 0, and the independent read-only comparison confirmed C Rust equality, C public scope equality, the single C/small proof difference, and all small-only four-file locks. **UNKNOWN:** New C Lean acceptance, axiom query and runtime under 900 seconds. The C suffix is ready for the root's separate full gate; it is not yet a verified timeout repair. No candidate input was changed after its gate dispatch by this proof line.

## Final update — both proof-only suffixes accepted

Evidence independently reviewed at `2026-10-07T07:29:48Z`. This section supersedes the creation-time Lean/gate-UNKNOWN entries for the two suffixes. Their candidate files and generator remain frozen; this finalization changes only this note.

**VERIFIED:** Both suffixes passed the complete official public gate: static policy, official Charon/Aeneas re-extraction, original `LZ77.Obligation slot.parse`, dedicated permitted-axiom query with extraction integrity check, and public 28-file scoring/round trip. The whitelist remains `Classical.choice`, `Quot.sound`, `propext`. The original **900-second per-call** limit and source bytes were retained.

| Suffix | CI / fixed commit | Reported CPU | Parse proof (s) | Obligation (s) | Axioms (s) | Whole verification interval (s) | Parse margin to 900s |
|---|---|---|---:|---:|---:|---:|---:|
| `r5-h16-small-proofopt` | `37584216832` / `3d9494eb4370e20e8c76ed243a2093d6c8b2ec60` | Intel Xeon Platinum 8370C @ 2.80GHz | **591.5** | 3.0 | 2.3 | 783.3 | **308.5s** |
| `r5-h16-smallc-proofopt` | `37584736974` / `24ac5d89d7930378524d0045bb537f8b8ea76762` | AMD EPYC 7763 | **646.3** | 3.2 | 2.6 | 838.4 | **253.7s** |

Raw evidence: `evidence/round5/37584216832/h16-proofopt-gate/gate/{r5-h16-small-proofopt-gate.log,gate-summary.json,state.json,round1-r5-h16-small-proofopt.jsonl}` and the corresponding `evidence/round5/37584736974/h16c-proofopt-gate/gate/` files. Both gate summaries report `accepted=true` and empty failure lists. CPU identity comes from each measured-process meta row, not an assumed runner model.

**VERIFIED output preservation:** For each suffix, the single public screen block's entire set of 28 input SHA256 values, output byte counts, output SHA256 values and token SHA256 values matches its own frozen parent's original Round 5 measurement. The independent comparison used small-only parent `37580297956/refine/round1-r4-hybrid-h16-small299.jsonl` and C parent `37580365335/refine/round1-r4-hybrid-h16-smallc299.jsonl`. Source SHA256 remains `d9826bc92ba02f49cb6e552ed172a4fb82dc10fa8fb51aacf73e7947ed38a94d` / `39c82b4673440faaa7cf9f14ccbeb9367128a7f50a8ca8472880dc35ed24b83e`, respectively. Proofs remain `d55744de52bb0469768f0bbfd73ffecbabf9899b63e0167469fd7bb79c6293c7` / `c186520fff7d078e0911f92d1b1aeeb3798cfc5292d1ec2415db4610690ca0d1`.

The new gate states contain **no synthetic-validation run**. The earlier eight-input/two-block generated-input receipt belongs to the original accepted H16C pair; it is not described as coverage performed by these two new suffix CIs.

### Preserve every original result

The original frozen source/proof pairs were each checked three times this round. Independent log/summary review gives these records:

| Original pair | CI | CPU | Complete public gate |
|---|---|---|---|
| small-only | `37580297956` | AMD EPYC 7763 | stage-4 900s timeout |
| small-only | `37581080647`, `h16-small-gate` | AMD EPYC 7763 | stage-4 900s timeout |
| small-only | `37582138961`, `h16-small-gate` | AMD EPYC 9V74 | accepted |
| C route | `37580365335` | Intel Xeon 6973P-C | accepted |
| C route | `37581080647`, `h16-smallc-gate` | AMD EPYC 7763 | stage-4 900s timeout |
| C route | `37582138961`, `h16-smallc-gate` | AMD EPYC 9V74 | accepted |

Original totals are small-only **1 pass / 2 timeouts**, C **2 passes / 1 timeout**. Each new proofopt suffix currently has **1 pass / 0 observed timeouts**. The original failures remain failures, and the original successes remain successes. The original C run `37582138961` accepted after a 988.1-second whole verification interval, again showing that 900 seconds applies to individual calls rather than the summed interval.

**Supported conclusion:** The 104-declaration B-proof elimination is now accepted by the official obligation and axiom checks, with 308.5/253.7 seconds of observed proof-call margin on the two recorded runners. The C suffix also passed on the reported CPU model where original pairs had timed out. Those runs do not establish the same physical CPU, equal load, or controlled before/after runtime experiment; no causal percentage speedup is claimed. One passing suffix run each does not guarantee all environments will fit 900 seconds. Proof-only work changes no compression algorithm, frontier coordinate, private-stage2 conclusion, admission status or reward claim.

The requested two H16 proof-gate gaps have concrete accepted suffix pairs, unchanged Rust and complete audit trails. No additional candidate, generator change or CI was created during this final notes update.
