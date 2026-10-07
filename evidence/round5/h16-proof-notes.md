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
