# Round 3 compression research

Prepared 2026-10-06 UTC. Scope: four reproducible research candidates for the main thread's CI. No CI, commit, push, formal submission, registration, or wallet action was performed by this subtask.

**VERIFIED:** the files below exist, were rebuilt by `python scripts/make-round3-size.py`, and pass its exact-byte `--check`. **UNKNOWN:** compilation, official extraction, Lean obligation, axiom audit, round trip, measured compression, and measured speed for these new files. Copying a previously accepted proof does not accept a changed parser.

## Evidence and target

The base is `candidates/probe3/`, derived from the miner's public submission 261. Attribution remains in `references/submission-261/PROVENANCE.md`; the original source and proof remain unchanged. No additional external implementation was incorporated.

Base source SHA256: `e20ea5a7d2e77821008592faef393855077b9b8ceee244f390a85ac0257e047d`.

Base proof SHA256: `3906aeb259d83d315811629a54d796b514fc3953742063081451c47997b824b7`.

Official verifier revision for subsequent validation: `a356bbff18b60c4527fbcc85d5a28ef9c20214e0`, using the unchanged entrypoints/pins described in `ENVIRONMENT.md` and the round 2 scripts.

**VERIFIED:** `ROUND2.md` and `evidence/round2/37454635334/analysis.json` record probe3 public size 35.9208377148%, a 0.1148841875 pp reduction against probe2, with 15 smaller files, 2 larger, 11 unchanged. The improvement concentrates in text, prose, source, and multibyte inputs. The archived `round1-probe3.jsonl` records all 28 public files and raw measurements; the three inputs no larger than 65536 bytes are sparse.bin, tiny-app.log, and tiny-config.json.txt. These candidates leave the tiny planner and its routing unchanged.

**VERIFIED:** `frontier-targets.json` records snapshot 23753, computed at 2026-10-06 15:15:37.582609 UTC, with freshness `unknown`. It supplies the following public-coordinate thresholds after dividing the recorded official frontier coordinates by the #427 calibration factors. The factors are an empirical proxy, not a stage2 prediction bound.

| Recorded point | Public time threshold | Public size threshold |
| --- | ---: | ---: |
| 369 | 0.4541725196 | 35.8603509955% |
| 346 | 0.4623226020 | 35.5656938375% |
| 350 | 0.4701552734 | 35.2970712533% |
| 383 | 0.4845202791 | 35.0128918626% |

**INFERRED:** merely saving a few hundredths of a percentage point while becoming slower may remain dominated. Each measured candidate must be compared against the entire recorded frontier after multiplying time by 1.014402891250616 and size by 1.0070277985275755. Recheck the current frontier before interpreting any later decision. No ranking or reward claim follows from these thresholds.

## Candidates and falsifiable hypotheses

| Candidate | Change from probe3 | Hypothesis and first failure signal |
| --- | --- | --- |
| `round3-size-hash3` | In regular classes 1, 5, and 6, set the hash mask to `0xFFFF_FF00` and minimum match length to 3. | Newly visible three-byte repeats outweigh weaker hash discrimination. Reject the direction if size worsens or any improvement is dominated after calibrated time. |
| `round3-size-hash3-near` | Same text key/minimum change, but accept a main text match of length 3 only when its distance is at most 128. Class 3 keeps the original binary rule. | Long-distance short tokens were consuming more bits than literals. Compare directly with hash3: if near is worse, this cutoff does not fit the measured encoder costs. |
| `round3-size-gain` | Main `find` call changes `gm=0` to `gm=1`, using the already implemented gain estimate. | Some longer, farther matches lose more distance bits than their extra bytes save. If output is unchanged across files, the mechanism has no observed compression value at depth 3. |
| `round3-size-insert6` | `INS_MAX` 2 to 6; all search depths stay 3. | More dictionary entries from a match head improve future search without the cost of deeper walks. Extra entries can also hide a useful older entry at depth 3, so improvement is not assumed monotone. |

The distance-128 cutoff is predeclared before any new measurement. At the existing gain proxy (`HLIT=80`, `GBASE=168`, measured in sixteenths of a bit), a length-3 match approaches break-even near this distance. The actual shared encoder uses stream-dependent codes; the cutoff is not an exact DEFLATE cost rule. The near variant rejects at the existing match/literal branch rather than adding loops or table state. For lazy search, equal-length candidates farther away cannot beat a nearer length-3 candidate under the existing gain function; a longer accepted lazy candidate remains valid independently of this heuristic.

The gain candidate is not a full optimal parser or unrestricted best-bit search: `walk` still only considers candidates longer than the current best, uses its original quick rejection, and stops at NICE. It only changes which length increases are accepted. It does not compare a shorter candidate after accepting a longer one.

## Proof reuse analysis

All four `Parse.lean` files are byte-for-byte the base proof above. There are no added imports, axioms, or declarations.

**VERIFIED from source:** `find_spec` and `walk_spec` quantify over `gm`, `depth`, and `minl`; their correctness postconditions concern legal ranges and matching bytes, not longest-match optimality. `main_loop_spec` accepts minimum length in 3..8. `run_spec` is for every class and every positive table size. The original proof documentation allows changing INS_MAX and other insertion constants. Hash `mask` is a parameter of the insertion bookkeeping proof, which retains head bounds rather than assuming a unique hash key. None of the candidate changes alters byte comparison, token encoding, backward merging, output allocation, or the fixed encoder.

**INFERRED:** the unchanged proof has a strong reuse case. Hash3 changes only setup before the existing loops; gain changes a parameter already covered by the theorem; insert6 changes a documented free constant. Hash3-near adds a boolean guard inside the main loop, so its tactic/extraction compatibility is the riskiest of these four even though a rejected match simply follows the existing literal branch. Official re-extraction and checking remain required for all four.

**UNKNOWN:** whether Aeneas keeps all generated loop signatures and whether the existing `step*`/`split` automation closes the changed hash3-near branch. A failure there would establish a proof-script incompatibility until its exact goal is inspected, not a demonstrated parser correctness bug.

## File hashes and checks

| Candidate | parse.rs SHA256 |
| --- | --- |
| `round3-size-hash3` | `b5a8ca3f32026b8f13e4c57d1b730f82262e20ef7613c8f72ebc036cc92dfca9` |
| `round3-size-hash3-near` | `7d982885599fc3f48cead3b4655791c0bf12ed2988e23e12051f8c50ae1f7a19` |
| `round3-size-gain` | `17dc46646922a19d5586fb2f78c92745a6259947cb245d7a3e548fdfdc571d5f` |
| `round3-size-insert6` | `91664046e61c99a2d1c7565a683d44a4a5dfa2ae472cfa824acafd78c50acdbe` |

Every proof SHA256 is `3906aeb259d83d315811629a54d796b514fc3953742063081451c47997b824b7`. Each candidate has a `manifest.json` with its full description, source/proof/base hashes, upstream revision, attribution pointer, and explicit unverified state. All Rust and Lean files are below the 524288-byte intake limit. Source inspection confirmed only the listed changes. The generator locks the base hashes and offers a read-only exact-byte check; it does not touch other candidates or official files.

**VERIFIED local checks:** generation exited 0; exact-byte regeneration check exited 0; direct diffs match the declared changes; proof identity and intake file sizes were checked. A repository-wide `git diff --check` exited 0, but untracked candidate contents are established by the explicit byte check, not that Git command.

Recommended first CI falsification: run the same public paired benchmark and dual-decoder round trip on probe3 plus these four sources, retaining every raw repetition and token/output hash. Those are research measurements until the chosen exact source/proof pair also passes official extraction, obligation, axioms, and the full public gate. Compare equal-file time and size, not total seconds or total bytes; disqualify calibration-dominated candidates before spending further gate/retest time. For a promising candidate, require a second order/runner check before calling a small timing gain robust.

No local Linux toolchain was installed or used. Private stage2, online admission, payable frontier position, and actual rewards remain **UNKNOWN**.
