# Fused prepared-B certificate: a distinct cost question, existing mathematics

Started **2026-10-27 21:54:09 UTC**, bounded to **22:19:09 UTC** for this low-cost check; shared R22 deadline remains **2026-10-28 03:12:47 UTC**. No local Lean, candidate assembly, CI, or changes to D's runtime.

**Mathematical answer: yes, already covered by T19/W12.** For the actual +0-start, increasing-k, separately rounded multiply-then-add dot, if all original values read from A and B are nonNaN, the exact raw answer equals `ofFloat32` of the actual native answer, including an invalid-generated NaN. The input condition allows Inf, signed zero, and subnormal values. This is not a claim that every intermediate remains nonNaN. Current B2/4e36 already contains `R7W12.ofFloat32_add/mul` and `rawNotNaN_eq_native_classifier`; importing the old 12.7 KB closure block again is unnecessary.

## Checked historical difference

| Exact inspected source / record | Actual mechanism | What it does not provide |
|---|---|---|
| 4792 canonical-dot-scan | Only after a native NaN endpoint, scan that output's exact A row and B column; true imports the endpoint, false uses original `replayEarly`. Actual-loop source has old NOT_RUN status. | No shared prepared-B summary; no fused global conversion/classification traversal. |
| bmm-scan-sharing-screen | Parked design analysis of eager row/column summaries and lazy Thunks. It explicitly says fusion into nativeA.map/packB was only a possibility with no generated C evidence. | No implemented fused map+summary loop in that record; old coverage counts are not current timing. |
| 2bd8 R14 row-nan-lazy | Scan each raw A row first; rows containing raw NaN use exact software replay. Thunks defer/share A conversion and B packing. | No prepared-B plus safety Bool. It redirects poisoned rows, rather than certifying image-safe native endpoints. |
| 9244 R9 native-event replay | In the replay path, check the next native accumulated result for NaN at each k, repair the first event, then use quiet absorption. Recorded full gate passed but BMM was 2.2% slower. | Not an input certificate. This event loop must not be re-run under the new proposal's name. |

The inspected non-CI Lean/inc search found no prepared-B plus nonNaN-summary implementation. That is a scoped history finding, not a universal novelty claim. Current `PreparedQuad` is `c7e66111`: it already maps the entire original B to Float32 once inside core, and retains raw B for `Packed10.finish`.

## Proposed minimal change in work

`FusedPreparedB.lean.inc` supplies a small **NOT_RUN prototype**, not a completed implementation:

1. Traverse B once. For each q, append `toFloat32 q` in exactly the old order and accumulate `good && R7W12.rawNotNaN q.raw.1`. The array conversion continues even after good becomes false.
2. Return one array plus one Bool. The proposed tail recursion keeps array and Bool as separate loop arguments and constructs the result structure only at exit; generated C must confirm this. Bool values themselves are immediate values, not per-element heap objects.
3. If B.safe is false, use the existing prepared output with the already prepared values; do not map B a second time and do not compute A certificates that cannot be used.
4. If B.safe is true, accumulate one A-safe Bool per four-row group at the four raw A loads already required by each k step. Do not put that Bool in every column Cell and do not rescan A for each output.
5. At group completion, a true combined certificate allows four direct `ofFloat32` row writers. The branch can be outside the emit loops, removing the existing endpoint classifier as well as any NaN replay in that group. A false certificate uses the exact old finish. Raw arrays stay available for that fallback.

This is distinct from 4792's repeated cold scans, R9's per-step endpoint event test, and the old full pre-scan/Thunk proposal. It adds classification to an already required B traversal and to A reads shared across columns. It still adds real work; one pass is not zero cost.

## Exact interfaces and remaining gaps

The proposed `Ready raw prepared` contract has two parts: `prepared.values = raw.map toFloat32` and `prepared.allNonNaN = raw.all rawSafe`. From an assumed Ready contract, the fragment derives getD equality, summary-true implies every getD input's native conversion is nonNaN, and exact import of each prepared read back to the original raw read. Out-of-bounds defaults remain +0.

**The prototype does not yet prove `Ready raw (prepare raw)`.** Its required invariant is: output values equal the converted prefix, output length equals i, and good equals the raw nonNaN conjunction on that prefix; at exit i=raw.size. This is the next structural proof, not a missing arithmetic axiom.

`DotImageInterface.lean.inc` separately adapts the existing W12 operation closure to the *current* `NativeFinal.dotLoop` with explicit nonNaN hypotheses on the exact A/B reads. Its `direct_import_eq_finish` endpoint removes the runtime endpoint classifier only under those hypotheses and the exact native-loop result equality. All new typing/replay is **NOT_RUN**; no public BMM/spec is assembled. Current quad lane proof provides the result-equality interface if its exact source is accepted later.

## Full cost and first falsifier

- B: retain every old decode, Float32 value/box and output slot; add raw mask/compare and Bool reduction, a new iterator/control path, and one result object. Replacing Array.map by a Nat/push loop may lose a better existing backend, retain more bounds/reference work, or fail to reuse storage. Preallocating capacity does not prove allocation identity.
- A: at most four raw classifications per k per four-row group, one carried group Bool. To truly share reads, raw loads/decodes must be hoisted outside the per-column updater once; a source rewrite that re-reads A adds cost.
- Finish: certificate-true removes per-output endpoint classification and quiet-stop replay, but still performs native import and output construction. Existing replay already stops at the first quiet NaN; do not count the discarded suffix as new savings.
- Coverage: a single unrelated B NaN rejects the global certificate, and one A NaN rejects its four-row group. Those conservative misses are correct but reduce benefit. No class names, benchmark identifiers, or fitted shape thresholds belong in the runtime.

For `g=floor(m/4)` and batch count b, all-safe full traversal adds at most `b*n*p + 4*b*g*n` raw classifications and can remove `4*b*g*p` endpoint classifications, before replay savings. The 0..3 tail rows retain the old path. This is only an operation-count screen: the two classifier types, loop control and memory access do not have equal costs. For example m=p=64 gives 512 added versus 4096 removable checks at n=4, but 8192 versus 4096 at n=64. These examples explain why complete cost can differ; they do not propose a new dispatch threshold or predict speed.

The first code-generation falsifier is an actual complete caller showing a second B traversal/map, a result-pair allocation per B entry, A checks inside the p-column loop, or repeated default/decoder work replacing the old map. Any of these invalidates the claimed amortization premise. If codegen preserves the intended work boundary, compare the complete prepared caller against the same prepared caller with this fusion, including preparation, A accumulation, both certificate outcomes, final writes, and fallback. Current PreparedQuad cost itself is still pending; no timing benefit or 10% whole-package opportunity is claimed.

**Decision: retain a new, narrowly specified cost experiment for D; do not reopen an old full-table scan and do not buy a large proof before the caller-cost premise survives.** The existing mathematical closure is reused, not rediscovered.

## Minimal boundary evidence

`witnesses.json` reuses the exact old source-word model on ten cases only. Inf*0, opposite infinities, and opposing overflow products produce `7fc00000` from safe raw inputs. Raw qNaN `ffc01234` and sNaN `ff800011` refute unconditional normalization (the latter quiets to `ffc00011`). Invalid occurring before a later signaling input still yields canonical NaN because each raw multiplication quiets its NaN before addition and the already quiet accumulator absorbs it. Raw payload first then invalid preserves that payload. An empty raw noncanonical seed is not a native-image seed; public +0 is. These are bounded model witnesses, not a new Lean/hardware run.
