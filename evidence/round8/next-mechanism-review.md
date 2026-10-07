# #454 binary-tree match finder: review for a later #361 experiment

Status: source review and proposed experiment only, 2026-10-08 Asia/Shanghai. No candidate, script, proof, CI, submission, or wallet action was performed for this review. The completed round-8 retained-candidate cost experiment had no public compression gain; see `algorithm-design.md` for the measured stop decision.

## Decision

**INFERRED:** `q9_bwalk` is worth one bounded, independent candidate-discovery diagnostic if a later research round is authorized. It is not ready to replace #361's finder. Its distinguishing mechanism is binary-tree traversal with reused common-prefix lengths, not a richer cost-aware retained-candidate set. Both finders still keep length records. A direct whole-cache transplant would change search coverage, insertion cost, memory use, planning direction, block costs, and routing together, preventing useful attribution.

The main risk is structural: #361 can insert a position into its chains without searching it; q9's binary-tree insertion itself walks and modifies the tree. Porting it would make continuation-only and skipped positions more expensive unless a separately justified insertion policy is developed.

## Verified source and routing boundary

The inspected files are `references/round8-public-454/parse.rs` (SHA256 `382176623abda73f77a9a5323e8cb14c5cdd6c8221b018cbc8c51cf959448639`) and `Parse.lean` (SHA256 `6bedea113a1c7d05e8964ff3d45cf06a0bac1527d9aeca262220ebead3b57225`). Their local hashes match `PROVENANCE.json`, which records official source and bundle-digest verification. This review did not repeat the network retrieval.

The provenance records formal #454 axes `1.6288336194269581 / 34.15239423636879%`; these belong to the complete submitted router and all its engines. In this source, `CLASS_TAB` has engine 5 only in row 24. `route_class` (`parse.rs:2399`) reaches row 24 from class 3 at exactly 300,000 bytes. `parse` (`:2139`) dispatches engine 5 to `q9_parse`; `q9_mode` (`:1204`) then selects the binary-tree `q9_hplan` only for its high-symbol-diversity mode. Thus the complete #454 coordinates do not establish q9 finder performance on #361's text routes, nor even isolate q9's contribution on the original corpus.

These exact-length branches are an observed attribution and generalization limitation. This review makes no claim that they violate official rules.

## What the mechanism actually changes

| Component | #361 DP finder | #454 q9 finder |
|---|---|---|
| Search structure | 3-byte nearest head plus 4-byte and 7/8-byte recency chains | Exact-tag two-slot caches for 3/4-byte keys, with a binary search tree under the 4-byte head |
| Traversal work | Cheap tail/best-length rejection; follow older chain links | Compute a common prefix, compare the next byte, rewrite child links, descend lexicographically |
| Prefix reuse | `probe` and `walk_t` reject using current best length | `q9_bwalk` carries `low/high` prefix bounds and starts comparison at their minimum |
| Retained matches | Only increasing lengths, maximum 15 before continuation | Only `l > best`; adjacent record matches in the same distance-symbol slot are merged |
| Position coverage | Search only when continuation/lazy policy asks; skipped positions still inserted cheaply | `q9_hfind` processes every position, building event, offset, and match vectors |
| Planning context | Forward DP and bounded backward extensions | Seed plus one block-cost backward planning iteration using the complete match cache |

Source anchors: #361 `probe:936`, `walk:962`, `walk_t:1313`, `dp_parse:1459`; #454 `q9_push_slot1:846`, `q9_bwalk:954`, `q9_cache3:976`, `q9_cache4:989`, `q9_hfind:997`, `q9_spick:1035`, `q9_hplan:1100`.

**VERIFIED:** `Q9_SLOTM=1`, so `q9_push_slot1` replaces the last candidate when its distance-symbol slot matches the incoming longer candidate's slot. That saves match-cache entries; it does not retain equal-length cheap alternatives. `q9_spick` already scans candidates backward while carrying the cheapest distance cost, then tries a bounded tail of the supported lengths. Its integrated result therefore combines a different finder, suffix-cost handling, length sampling, and block modeling.

**INFERRED:** Binary-tree traversal may find longer matches within a bounded number of visits, especially where repeated long prefixes make LCP reuse useful. Conversely, it must inspect mismatch locations even for nodes that do not beat the retained best, while #361 can reject many such nodes with its tail test. Thirty-two binary-tree visits and thirty-two hash-chain visits are not equal CPU work.

## Smallest falsifiable next experiment

Use one temporary CI diagnostic at q9's recorded depth 32; do not perform a depth sweep. Apply #361's existing content router, not #454's exact-length branches. Analyze all public files that #361 routes through its DP engine, plus deterministic text inputs with long shared prefixes and perturbed lengths/content.

1. Build q9's finder cache in a temporary harness, retaining its exact-tag cache and insertion semantics. Independently run the unchanged #361 parser in a diagnostic copy and inspect candidates only at the positions it actually searches. Compare the two match sets at those same positions under #361's current `lc/dcc`, without changing #361's plan, schedule, continuation, or output.
2. Record newly discovered longer matches, lost matches, interval-wise cost improvements, candidate counts, bytes compared, and node visits. Validate every reported q9 match's range and bytes in this diagnostic. Report any q9 result truncated to #361's 16-slot representation separately; do not silently attribute truncation losses to the tree.
3. In a separate uninstrumented process, measure the complete q9 finder prepass including tree insertion and vector allocation against the same files' complete #361 parser cost. Pair the measurements and include a repeated control. This is an implementation-cost bound for the proposed prepass approach, not an official two-axis candidate result.
4. Stop before integration if q9 discovers little useful coverage at the fixed #361 search positions, if its reported matches fail validation, or if full-position tree/cache construction consumes the available time budget without a plausible quality gain. If it does reveal substantial fresh matches at tolerable cost, authorize one later prototype that changes only candidate generation under the unchanged #361 router, prices, parser policy, and checked emitter; only that prototype can produce official paired size/time evidence.

The diagnostic separates a changed candidate-discovery mechanism from the failed round-8 reuse of already-retained matches. New match opportunities would be INFERRED potential, not proof of a smaller encoded output. Corpus-wide cached model savings can again overstate path savings, so they are a screen rather than an acceptance criterion.

## CPU, memory, and integration costs

**VERIFIED from declared arrays:** q9's finder tables occupy 1 MiB before dynamic match storage: 32,768 u64 4-byte tags, 65,536 u64 3-byte tags, and 65,536 u32 child entries. #361's five head/prev arrays total 832 KiB. q9's event/offset/match vector contents add approximately `8*E + 4*M + 4` bytes for E matching positions and M match records, excluding spare capacity. Whole `q9_hplan` adds further prefix, histogram, block-cost, and plan arrays; the minimal diagnostic does not need those planning passes.

**INFERRED:** A streaming replacement could avoid the whole-file match vectors, but cannot simply call `q9_bwalk` only at #361's searched positions: omitted insertions change later reachable matches. Maintaining full insertion semantics requires processing skipped positions too. Reusing only a two-slot tagged cache would be a separate mechanism and would not measure the binary tree's contribution.

Adapting q9 records into `cands[16]` also needs an explicit policy. Tree traversal is lexicographic rather than newest-first; distances need not increase with record length. If the candidate array fills, collecting records may stop while tree insertion continues. The parser's reported `best`, final stored candidate, and continuation must remain consistent. q9's tree must still close its child links correctly at the depth/cap boundary. These issues make it more than a local replacement of `walk_t`.

## Proof cost and evidence limits

**VERIFIED:** The supplied #454 proof has totality lemmas for `q9_bwalk_loop` and `q9_bwalk` (`Parse.lean:5870` onwards), terminating by `budget - it`, plus totality for tagged caches and `q9_hfind` (`:5890` onwards). Its checked emitter supplies final validity. Those lemmas do not prove matchfinder equivalence or compression quality.

**INFERRED:** An unchanged temporary diagnostic can reuse the source helpers without a competition proof because it is not a candidate. A later transplant needs fresh extraction and helper specifications for new array/tuple signatures, bounds for returned candidate count and longest length required by #361's caller, and adapted traversal/insertion loop proofs. The existing #361 emitter can keep the correctness boundary, but does not certify the performance or search-state assumptions. Compared with round 8's small `rc_seq` helper, this is a materially larger proof and implementation change.

**UNKNOWN:** Generic public performance, hidden-corpus behavior, which q9 submechanism contributes most, whether its full-position maintenance is affordable, and any frontier/admission/reward impact. None of the whole #454 coordinates are transferred to the hypothetical #361 hybrid. This document records the next falsifiable research question; it reports no new measured optimization.
