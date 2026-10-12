# D1: assign residual U118 search after comparing two shallow starts

Prepared in the fixed R26 extension90m window starting 2026-10-12 14:55:17 UTC. This candidate does not reset that budget. Parent thread owns cloud dispatch, scoring, gates and any Git operations.

## Gap and direct prior evidence

A21 identified that 658 row9 completes depth12 before testing the next start with depth1. It retained a conditional opportunity to change who consumes the residual budget. A8's 641 lazy-chain version instead added lazy work after full current work and was slower; its surviving deep winners are a negative prior. C4 removed O_A lazy and lost quality; D1 is confined to U118 row9, retains exact matching, original emission and continuous lazy. Existing A14/A18/A19 table/filter/CPU edits are not combined.

This is a mechanism test, not a depth sweep. Prior work and author provenance remain in `references/round26-public-658/source-receipt.json` and `evidence/round26/route-a/a21-next-route-review.md`.

## Fixed mechanism

1. At the current row9 start, inspect the original first chain source once.
2. If it is a legal short match eligible for original lazy, peek the original next-start head without inserting that start. Apply the original shallow lazy gain comparison.
3. When the next head wins, return the current shallow match and let the original lazy loop perform its insertion and choice. Otherwise continue the remaining 11 sources of the current chain without rereading its head.
4. A shallow lazy winner receives the remaining 11-source main budget after its normal insertion. Keep that deeper result only if its gain exceeds the original shallow winner. Then continue the original lazy loop, backward fold and emission.

The only U118 instantiations in the frozen source are row2 (L2=1, depth6, lazy32) and row9 (L2=0, depth12, lazy64). Row2 immediately takes the original helper path. All input routing, persistent tables, insertion policy, fold, encoder and emission stay original.

No cursor is held across insertion: the current continuation happens before next insertion, while lazy continuation happens after the original insertion. The next-head peek adds a hash and shallow check that the normal lazy step repeats; this cost is real. Continuous lazy may discard a newly deepened winner later; no work bound or speed gain is claimed.

## Smallest valid experiment and decisions

- Native compile plus existing finite decode suite, then all 28 public inputs through the original encoder, recording input/token/output SHA and decoded equality. Token equality to 658 is **not** expected and is not an acceptance condition.
- At least one original-protocol paired total-compression-time screen with exact public658, same-source controls and incumbent, preserving all measured reps and per-file sizes. It is mandatory for this selected mechanism before promotion or pause; counters alone cannot terminate it.
- Fresh official snapshot and exact official formula are owned by the parent thread. Until measured, D1 public X, public Y, projected share, formal admission and stable share are UNKNOWN.
- Invalid decode/build: retain the failure and repair only a concrete defect before scoring. Valid but slower/larger: compare actual coordinates and same-source variation; report the observed tradeoff, without claiming the whole mechanism impossible. Positive but variation-sensitive: require frozen independent runner confirmation before a stable positive-share claim. No local tuning based on a peak.

## Proof migration and cost boundary

The changed generic run retains the original main and lazy loop state tuples and existing FoundAt/MatchAt/Dec invariants. Three new local specifications are needed: `d1_continue`, `d1_current`, `d1_lazy`, returning FoundAt and the existing length/distance bounds. They call proven `u118_find`; no cross-query MatchAt cache or prev-snapshot equality obligation is introduced. Read-only next-head lookup has an explicit hq<=q runtime guard.

The migration is INFERRED moderate effort, not a verified proof. Exact extraction may change captures and must be inspected. Original Lean is only a scaffold; adding helper lemmas, actual extraction, original obligation, axiom whitelist, full gate and round trip remain required. Rust/Lean byte limits must be rechecked for the actual pair.

## Fixed source identity and known status

- Parent Rust: `1185749453a5abe100106f2e15082eca84521292b7233784a9c2f4562367f3ad`.
- Parent Lean: `354d56aa9f58536efdb410f3d5ecdf1945bded607965fe8a48161f96b035c494`.
- D1 Rust: `f6c7f97f9fb275d5a27ff4a52d02f065bb9c4cfd39e73e311c5a7f5a3ea8e0a8`.
- Author hotkey: `5G3YLL7PuDhRBoVoDBYKhAfTxFM4EouSDiYuFXeeWciNRzyK`.
- Candidate: `candidates/r26-d-658-selective-depth`; build recipe: `scripts/r26-d-build-selective-depth.py`.

VERIFIED here: source construction and hash binding only. INFERRED: mechanism, proof route and likely scope from the two existing calls. UNKNOWN: compilation, correctness gate, actual quality, actual total time, shares and independent confirmation.
