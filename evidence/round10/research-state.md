# Round 10: balanced-frontier research

Execution rules: [AGENTS.md](../../AGENTS.md). This record is evidence and scheduling state, not an authority source.

- Actual start: **2026-10-08 03:50:52 +08:00** (2026-10-07 19:50:52 UTC).
- Five-hour deadline: **2026-10-08 08:50:52 +08:00**.
- Initial confirmation reserve: 70 minutes; stop adding exploratory candidates by 07:40:52 unless a revised allocation preserves adequate confirmation time. Running CI must finish naturally or reach its configured timeout.
- Initial checkout: clean `main`, `4ce98ccfe48ced871a501a016518076baf8a81d9`, one worktree. Work proceeds on `codex/round10-balanced`.
- Goal: a credible candidate near the balanced paid Pareto frontier. Public improvements, exact public gate, hypothetical geometry, formal admission, and rewards remain separate claims. No formal upload, registration, signing, or payment is authorized this round.

## Restored starting point

`r9-block-scalar` has an exact full public gate and a small paired CPU signal, but was dominated under R9 same-family and adverse transfer models. `r7-mid361-block1` is its structural parent. R9's 73% forward share includes search, insertion, candidate recording and initial planning; it does not identify chain search alone. Entire backward-free linear modeling gave only about 13.6% of official total-time benefit, below the old conservative target. Full q9 precomputation is too costly in the measured form, though it discovers extra matches. Source: [Round 9](../../docs/rounds/round09.md), [diagnostic conclusions](../round9/diagnostic-conclusions.md).

## Initial resource allocation and falsifiers

1. **Forward structure:** separate match discovery/recording from the first cost-based plan. Search scheduling appears independent of forward cost state; test a cheap seed plus unchanged backward planner. Minimal operation: exact extraction, paired public screen, decode and record/schedule comparison where claimed. Reject or revise if size loss consumes recovered time; preserve better tradeoffs. First implementation checkpoint: 35 minutes.
2. **Supplementary finder:** retain original matching work, add constant-time maintained small caches queried at real search positions. Minimal operation: two different key/cache variants with paired public axes; do not equate extra coverage with output savings. Reject full-prepass migration; stop variants whose encoded size does not improve enough for their cost. First implementation checkpoint: 35 minutes.
3. **Official frontier:** capture complete pinned pagination and primary scoring source; replay current weights before setting thresholds. Same-family #361 transfer plus adverse time/size/noise scenarios is a hypothesis, not a private-set guarantee. Initial checkpoint: 15 minutes.
4. **Main integration:** create round10 namespace, preserve pinned official entrypoint, stage exact source/proof hashes, and arrange early extraction artifacts so proof work can overlap measurements. Evaluate an independent alternative once first feedback arrives.

The first two implementation agents own disjoint candidate and generator paths; the third owns frontier analysis. No nested dispatch. They do not start CI or commit/push. The main thread integrates and verifies their outputs.

## Decision log

- 03:50:52: budget starts; restoration, reading, tool setup and coordination all count toward the five hours.
- 03:53: initial independent routes selected. No new candidate measurement, proof, admission or reward is established yet.
- 04:04:24: `explore-a` dispatched as run `37679261323`, frozen commit `16d80788891d3ce7fece4fa990078eb1eee62dcb`. Five candidates, seven controls, two public blocks; extraction requested for seed/tag4/hash5, no full gates on unadapted proof files. Native finite diagnostics will check the claimed rs preservation and supplementary record validity.
- 04:16: the current frontier replay confirms a 6.074% further same-family scalar speed target at fixed size, or 16.654% against the declared adverse scenario. Snapshot `27331`, 491 Pareto rows; freshness unknown. The local scorer reproduces published weights within 6.94e-18.
- 04:16: a separate `rmq-a` screen is prepared to test eight-endpoint cached minima inside actual constant-price runs. This changes how neighboring nodes reuse endpoint prices, rather than rescanning supposedly duplicated intervals. Independent bounded arithmetic/ring model found no counterexample, but no Rust output/Lean/performance result exists yet. Cap: one two-block screen with finite output comparison and extraction, then stop unless a useful total-time signal supports combination. Existing forward/finder proof drafts remain untested pending real extraction.
- 04:22: official extraction accepted seed, tag4 and hash5; original extraction bodies and SHA-256 inventory downloaded. Full proof remains UNKNOWN. Both implementation threads now use the actual generated signatures.
- 04:30: seed proof interfaces reconciled to real extraction (`b41316b5…`), still uncompiled. Prepare `prove-a` with two independent public blocks for seed/seed2 and one original full gate for seed. Starting proof feedback before performance selection buys time for actual Lean failures and preserves a frozen cross-run comparison. This does not claim the seed has crossed the frontier. `rmq-a` is run `37680712729`, commit `ee34ad9c7f09679dcddbb2b1f6e0285eed5d938e`.

## First completed feedback and changed allocation

`explore-a` and `rmq-a` completed successfully: six new Rust versions and 40 paired public processes. Their `gate` artifacts contain **no completed Lean gates** (`gates={}`); the artifact stage name is not a proof verdict. Exact recomputation: [first-loop-summary.json](first-loop-summary.json). All six have zero conditional share under the current same-family and conservative scenarios.

- Seed: -5.6071% total time versus same-run scalar, +0.1351735 pp size. Lazyseed: -5.1318%, +0.0926915 pp. Seed2: +9.5445%, +0.0583781 pp. The original/new recorded stream matched on 18 public and 66 synthetic inputs, so the quality loss comes after discovery. Greedy block statistics are inadequate; restoring native D routes alone leaves substantial general-text loss. Stop added passes and this cheap-seed family. The already-started `prove-a` run `37682364860` (created 04:29:20, commit `ec27065574472e9da7610635eaac50864ee70c3b`) will still finish; its proof work remains a reusable totality bridge.
- Tag4: +6.0713% time for -0.0013716 pp size. Stop. Hash5: +4.4842% time for -0.0053775 pp; new matching helps, but the additional table's cost is excessive. 92,650 of its 97,744 public winning additions occur when the old best is in 4..7. Next replace the existing long-chain key with five/six bytes, rather than paying for another maintained table; this may lose long-key search coverage and must be measured.
- RMQ8: exact public output and 444 finite equivalence checks, but +5.1328% total time. Stop without spending a full gate; summary maintenance and query overhead outweigh savings in this implementation. This does not refute every range-minimum implementation.
- Coarse uninstrumented frontend diagnostic: collect+seed costs about 0.907x old forward work across D files, and seed is about 19.9% of the new frontend. Allocation/order differ, so these are diagnostic only. Sampled tiny-function timing gives inflated and overlapping estimates (including probe estimates above 100%); do not use it as a percentage decomposition.
- `struct-b`: preserve the original quality-producing plan; compare 16-bit window-distance chains, key5, key6, and omission of zero-candidate records while retaining node zero. Require finite whole-parser equivalence for delta16/empty-record claims. Extract delta16 and run an original full gate for the minimal empty-record change. Models and source arguments guide the tests but do not replace them.

## Second completed feedback and changed allocation

`prove-a` ended **failure**, with four new `omega` termination-measure obligations left open in the seed proof (Parse invocation 497.6 seconds, not a timeout). Repeated Rust measurements reproduce the size loss. No more CI is allocated to this seed; an explicitly untested repair is retained separately. Two actual extracted Funs files differ only in Source comment workspace paths after a narrowly defined normalization; see [seed-extraction-comparison.json](seed-extraction-comparison.json).

`struct-b` ended **success**. Delta16 is +1.2501% at identical output; key5 is +4.7821% / -0.0005412 pp, key6 +2.2458% / -0.0031119 pp. Stop these implementations and key sweeps. Record-nonempty is **-1.2342% at identical output** and passed a fresh complete public gate, including original obligation, allowed axioms and round trip. It has 444 finite equivalence cases and eight additional fixed inputs. Its exact accepted pair is recorded in [VERIFICATION.json](../../candidates/r10-record-nonempty/VERIFICATION.json); the small first-run signal is still awaiting independent confirmation. All ten measured Rust programs remain geometrically dominated. Full recomputation: [second-loop-summary.json](second-loop-summary.json).

New allocation:

- `row-c`, run `37688325585`, commit `5eb06c1ac9db3151ebaeef49e5220d5d8a1c45a0`: replace H7 pointer chains with one fixed row/tag/ring representation; do not add another finder table. Source-backed by Zstandard's design, but its SIMD speed results do not transfer to ordinary extractable Rust. One two-block screen and extraction; stop if coverage loss or maintenance cost negates the benefit. The same job independently repeats the frozen record-nonempty program.
- `rebase-d`, run `37689247460`, commit `95c7ecff5bd827292bae1b5b3038dd0836d09bbc`: halve all five head/link tables using relative u16 positions and periodic whole-table rebasing. This removes the per-insert delta encoding of the slower delta16 trial, but pays roughly 26 sequential bytes of slide traffic per input byte. Inclusive distance 32768 is preserved rather than copying libdeflate's strict cutoff. One finite whole-parser equivalence screen, paired blocks and extraction; no proof investment until the time signal justifies it.

## Payability constraint discovered and refreshed

Official docs and `validator/scoring/combine.py` select only the oldest surviving frontier submission per hotkey for Pareto payout. A fresh full capture at snapshot **27460, 04:57:46 +08:00** still has known submission #453 on the payable frontier. Thus a new balanced point that leaves #453 on the frontier has zero *additional new-point share on that hotkey*, even if it has positive geometric weight. Other admission/registration/bounty conditions remain separate.

[Payability analysis](payability-recheck.json) and [source note](payability-notes.md) distinguish geometry, same-hotkey new-point share, and the conditional share of a legally eligible distinct hotkey. No new identity, registration, signature, payment or official upload is performed. The separately requested weights endpoint advanced to snapshot 27461 during capture; it is not conflated with the pinned 27460 pages. Final ranking and this ownership condition will be refreshed again.

## Third feedback and selective probes

Six completed runs now contain 114 paired public processes and twelve distinct new Rust sources, recomputed in [third-loop-summary.json](third-loop-summary.json). Row16 is approximately 10.9% slower with +0.0079558 pp size; rebase16 is +2.9653% with identical output. Stop both implementations. Record-nonempty independently repeats at about -1.17%; two jobs/four blocks now support a small same-output signal, still geometrically dominated.

- 05:57:53: `selective-e`, run `37693029351`, commit `0ac30937edf8df516a857485cb5a1dc48e965e47`. Endprobe adds one exact match-tail query; row16-mask keeps row16 maintenance and candidate ordering but changes packed-tag screening. Finite native diagnostics and extraction precede any proof investment. A speedup only against the slower row16 is insufficient.
- 06:05:15: `cost-f`, run `37693861172`, commit `4f1b4169df1c2ece9f0b759ad28d2d57e0fd2108`. Test static match-versus-literal profitability in the lazy seed. This is one mechanism-specific response to seed quality loss, not another pass/depth sweep. Stop unless it improves the current verified starting point's projected tradeoff.
- 06:12: selective-e extraction accepts both exact sources; paired measurements are still running. Extraction is not full proof acceptance.
- 06:15: independent [measurement audit](measurement-audit.md) reproduces all 114 metrics and checks 279 raw-artifact entries. Record's four paired changes are -0.7796%, -1.6888%, -1.1137%, -1.2355% (equal-run mean -1.2044%); all public token/output hashes equal scalar.
- A deliberately optimistic [public-file oracle](public-oracle-third-loop.json) allows free independent choice among fourteen measured programs, including controls. Whole-program coordinates reproduce the declared family transfer within 7.2e-15. Its best sampled supporting vertex is 1.1632703 / 34.2057848 with 0.591141% geometric share, still 0 additional new-point share on the known hotkey. This is fitted to public timings, includes noise-selected CPU choices, has no implementable feature rule or switching cost, and is not a private-set bound or candidate. It only shows that the tested per-file tradeoffs are uneven; it does not justify filename-based routing or claim the maximum along convex-hull edges.
- Next bounded CPU probes preserve record-nonempty as parent: skip rebuilding a cost table only while its inputs remain unchanged, and move an already-required immutable next-link read before the current match probe. Both must preserve finite tokens and exact public bytes. Retain actual benchmark-library assembly for same-run comparison; no machine-code change or no useful paired gain closes the corresponding probe.

## Fourth completed loop and source-backed restoration

`selective-e` and `cost-f` both completed naturally with no measurement failures. Eight finished runs now have 152 public paired processes and fifteen distinct new Rust sources. [Fourth-loop recomputation](fourth-loop-summary.json) uses fresh full snapshot27641 (06:26:41 +08:00), 494 rows/76 frontier points. #453 survives and the same-hotkey limitation remains; weights/current belongs to a different snapshot.

- Endprobe: +0.07335% total time versus scalar (blocks +0.4368%/-0.2901%), -0.00177651pp, 319 total bytes saved across16 files and zero public size regressions. 112 finite coverage/plan/decode cases pass. Retain this small quality option, no tail-position/depth expansion or full proof allocation yet.
- Row16-mask: -4.28885% versus the same-output row16, but +7.06406% versus scalar and +0.00795585pp. Its444 native comparisons and public tokens agree with row16. Close the row implementation without full proof.
- Costseed: -3.09882% versus scalar but +0.06561168pp. The price filter recovers about29% of lazyseed's size loss, at extra time. Same rs in18 public D and66 generated inputs. Close this seed-statistics route rather than adding cost knobs or passes.
- `cpu-g`, run37695105461, commitc7150e907aaf6f44945e1e48cd15ed6b6aa2e29b, started06:16:26. Dirty cost caching and next-chain read scheduling are independent children of verified record. Count actual skipped/rebuilt model calls and retain actual benchmark-library assembly.
- `restore-h`, run37695964878, commitf918b7f77be7bbac197b0f0af3d2cbbffd387d86, started06:24:19. One child ports the original DP insertion pipeline into D with cached-head refresh after jumps. The other restores original per-class key/update/halving settings while retaining D's sparse flen16 first pass. Neither includes the unmeasured CPU-g changes.
- Nearby frontier source requests #375/#418/#422/#443/#489 return official403 SOURCE_WITHHELD. [Audit](public-neighbor-audit.md) preserves the body and known request times. Their metrics cannot identify implementation differences or justify an inaccessible new baseline.

## Evidence index

- Latest complete frontier capture: `official-late-research/`; prior complete captures: `official-mid-payability/`, `official-start/`.
- Forward mechanism and candidates: `forward-notes.md`.
- Supplemental finder: `finder-notes.md`, `row-finder-notes.md`.
- CI receipts: each run retained under its numeric run ID and batch, with original bytes and hashes.
