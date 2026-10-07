# R10 scalar tagged-row long-chain replacement

Prepared 2026-10-08 05:14 +08:00. **Rust source and finite layout model prepared; native build, extraction, byte decoding, performance and full gate UNKNOWN.** This is one fixed row shape, not a depth/table-size sweep.

## Mechanism and primary source

The row/tag/ring concept is taken from the official [Zstandard v1.5.7 zstd_lazy.c](https://github.com/facebook/zstd/blob/v1.5.7/lib/compress/zstd_lazy.c), particularly `ZSTD_row_nextIndex`, `ZSTD_row_update_internalImpl` and the design comment at lines1124-1138. The official [v1.5.0 release explanation](https://github.com/facebook/zstd/releases/tag/v1.5.0) establishes the motivation: replacing dependency-heavy chains with row-local lookup. It also limits transfer: its largest reported gains use SSE2. This ordinary-array scalar experiment does not inherit those performance figures.

The reviewed source is stored byte-for-byte at `candidates/r10-finder-row16/provenance/zstd_lazy.c`, SHA256 `dd6ccf357165dc8cb574ea56a34ff1db57b7b31728b32103d0c6b72319fd45b1`. Its source URL, retrieval time and dual BSD/GPL license copies are retained there. The Rust is a scalar adaptation of the layout concept, without the SIMD/SWAR implementation, external module, unsafe code or prefetch operation. The #361/scalar author attribution remains in the manifest.

R2's bucket2 stored two recent positions for shallow probe1/probe2 paths using separate arrays. Here the replaced D long-chain search normally has deeper budgets and records candidates for later backward planning. The changed structure and depth make this a distinct trial; the historical bucket result neither establishes nor excludes a gain.

## Fixed shape and maintenance

`r10-finder-row16` replaces D's H7 `head7[65536]` plus `prev7[32768]` with:

| State | Shape | Bytes |
|---|---|---:|
| positions | 4096 rows x16 entries, U32 position-plus-one | 262144 |
| packed tags | two four-bit tags per U8 | 32768 |
| cursor | one U8 per row | 4096 |
| total | | **299008** |

The previous H7 arrays occupy393216 bytes; the replacement saves94208 bytes (92KiB). This is a fixed-state byte comparison, not elapsed-time evidence. H3/H4 tables and insertion statements remain unchanged.

The original16-bit H7 hash splits into upper12 bits selecting a row and lower4 bits selecting a tag. Each originally inserted position, including taken-match ranges, gets one O(1) ring update. It writes a position, one packed tag byte and cursor instead of the original H7 head/previous-pointer writes. Packing adds read/modify/write arithmetic; actual maintenance cost is unmeasured.

Original D code inserts the current position before querying. The helper therefore captures the overwritten position and tag, and the row walker substitutes that victim at the overwritten slot. The current query can see all16 entries existing before insertion, rather than silently reducing usable capacity to15. Afterward the table contains the latest16 entries as usual.

## Query and loss boundary

The query scans at most16 row slots newest first. Row selection plus exact4-bit tag equality reconstructs the complete original16-bit hash. Only valid matching tags consume unchanged dep7; already-probed H3/H4 heads consume that budget but avoid a duplicate byte probe. Existing cap, nice and candidate-count guards remain, and original probe validates compared bytes before appending a strictly longer candidate.

Only16 entries sharing a12-bit row survive. Other4-bit tags may evict a match retained by the deeper original H7 chain. This does not preserve long-chain coverage or token equivalence. A larger d7 cannot search beyond the fixed retained row; no parameter sweep is part of this design. Search-control code, routes and other depths remain unchanged, while changed matches can alter later continuation/skipping and forward statistics.

The replacement removes pointer-dependent traversal and reduces fixed state, while adding scalar tag tests and packed-tag updates. It can improve locality, lose quality, or move cost. A time/size result needs the fixed public corpus, same-runner paired scalar/incumbent measurements and official encoder. It cannot follow from fewer state bytes or Zstandard's release results.

## Version and source audit

- Parent Rust: `faf1d7281678d12c3243002121feecdd0ea139633dea197dbc77d86fb6319257`.
- Row16 Rust: `ffe31d6253f851fd3e843a991c05e12564cbab289f117c41618653e9913dcc73`.
- Initial Lean: copied parent `aa21da6f74e81314297df07beecbfc98b15c848354437674bdb9347d8632f0af`, **UNADAPTED_PARENT_DRAFT**.

`scripts/build-round10-finder-row.py --check` verifies parent/source hashes, reproduces the package and reverses4 exact substitutions plus5 helper insertions to restore scalar bytes. Original shared insertion/walk functions, other engines/routes/knobs, H3/H4 statements and downstream record/forward/backward/checked-emission functions remain exact parent bytes.

## First low-cost check and next discriminator

`--check --model-check` completed a finite Python row-layout comparison against an independent per-row deque oracle. Five scenarios cover one repeated hash, all tags in a row, adjacent packed-tag updates, inclusive32768-byte window boundaries and deterministic mixed rows. Across10617 positions it checked newest-first history, exact hash filtering, unaffected adjacent nibbles and query budgets. In975 queries the victim mechanism preserved an otherwise overwritten valid oldest slot. Receipt: `candidates/r10-finder-row16/layout-model-check.json`.

The model verifies proposed packing/ring traversal only in that finite scope. It is not native Rust, match-byte checking, extraction, formal totality, encoded size or performance. The first effective native check remains the main thread's screen and actual extraction. Stop or repair native build/decode/extraction failures; stop this shape if size loss from old-chain eviction outweighs measured encoder-inclusive time gains.

## Proof migration cost

Five helpers need totality: packed tag reading, ring store, H3/H4 wrapper, inserted-range loop and row walk. Tag shifts are0 or4, row/slot arithmetic is bounded by4096/65536, and row walking terminates by16-step. Preserve best0<=best<=cap using existing guarded probe_spec.

Original H3/H4 LeAll bounds remain necessary. Row positions/tags/cursors can remain untrusted: query checks nonzero encoded position, decoded position before the current node, distance<=32768 and match bytes. Ring-order correctness itself is a quality property rather than an extra trusted axiom for checked-emitter correctness.

D extraction changes: remove2 H7 arrays and their head bound, add positions/tags/cursor, and update helper/branch tuple binds from actual Funs.lean. Initial parent Lean does not match. Native acceptance must preserve original LZ77.Obligation and allowed axioms, with fresh extraction/full public round trip bound to exact hashes. Source review and the layout model close none of those gates.

## Actual row16 extraction and negative paired screen

Run37688325585 / row-c completed naturally. Its extraction accepted the exact row16 Rust; an interface audit was saved separately at `candidates/r10-finder-row16-proof/interface-audit.json`. The actual row-walk/range/D carried states contain5/7/27 components, respectively. D's final done value remains8 components. The audit does not compile or complete a proof.

The public paired screen in `evidence/round10/37688325585/row-c/gate/` reports row16 about10.9% slower than scalar and size worse by0.00795585pp; it is dominated. This rejects the tested implementation as a frontier candidate. It does not isolate whether nibble scanning, ring maintenance, discarded deep matches or other code-generation changes cause the loss. No capacity/depth expansion or complete proof port follows this result.

## One same-output mask discriminator

The last bounded row variant is `r10-finder-row16-mask`, final Rust SHA256 `b1dc5a6e50362c830d0ea02690c045ac20e1b85441feea34fd9ec71396d76152`. Initial Lean remains the explicitly unadapted parent hash `aa21da6f74e81314297df07beecbfc98b15c848354437674bdb9347d8632f0af`. Before CI freeze, the unsubmitted initial Rust draft `787dccc2647e493b7edda7bfcdabc9dbd70066f8d7e3377aef047925b88d3eee` was replaced to preserve the original no-work-query cost boundary: depth0 or an already reached cap/nice/nc limit returns before loading tags. Its first model receipt is retained as `query-model-check-v1.json`.

Only tag-query work changes. It reads the row's8 packed-tag bytes into an ordinary little-endian U64, XORs the repeated wanted tag, and computes exact equal-nibble high bits:

```text
v = word XOR (wanted * 0x1111111111111111)
hits = NOT(((v AND 0x7777777777777777) + 0x7777777777777777) OR v)
       AND 0x8888888888888888
```

Each low3-bit nibble plus7 is at most14, so the addition has no inter-nibble carry. A zero nibble alone leaves its high bit clear before inversion. This is an exact tag equality mask, not a less-than comparison mask with borrow-related false positives.

The written slot's hit bit is replaced by the exact `victim_tag == wanted` result, restoring the pre-insertion slot's semantics. This direct equality also prevents an arbitrary victim tag>=16 from being truncated into a false hit. The physical bitmap is rotated by the cursor using ordinary shifts; leading_zeros selects the newest matching nibble, and one explicit bit clear advances. A fixed fuel16 counter establishes bounded loop progress independently of popcount or complex bit-pop termination reasoning.

The position validity, window distance, duplicate-head, dep7, nice, cap and nc checks remain the same. All insertion/maintenance code, row capacity/history, D parse and downstream record/planning/checked-emission functions remain exact frozen row16 bytes. The source generator reverses the single changed walk region plus mask helper to restore row16 exactly. No unsafe/SIMD/foreign module or new rotate intrinsic is introduced; leading_zeros already occurs in the accepted parent source. New helper arithmetic and loop interfaces still need actual extraction/totality work.

**VERIFIED finite model:** before generating the Rust package, `scripts/build-round10-finder-row-mask.py --model-only` compared the mask with the original scalar query model on202608 ordered tag-slot cases and30000 simulated ordered-probe/record/final-nc/best/dep7-budget cases. It covers all nibble values, adjacent packed pairs, every cursor, invalid victim tags, inconsistent written-slot metadata, empty/future/out-of-window positions, duplicates and stopping thresholds. The receipt at `candidates/r10-finder-row16-mask/query-model-check.json` binds the exact generator hash. This is a finite Python mechanism check, not native equivalence.

**Next effective check:** main-thread CI must run444 native Rust token/decode comparisons against frozen row16, compare public compressed bytes, measure encoder-inclusive paired time against both scalar and row16, and extract the exact new source. A native difference is a failed equivalence candidate requiring repair or rejection. Same tokens without meaningful time recovery closes this row implementation; the experiment does not authorize further parameter sweeps. Full proof expenditure continues to wait for performance.
