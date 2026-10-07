# Prefix-record mask RMQ review

Initial scope: source audit and finite Python model only, 2026-10-08. No Rust
candidate, CI, submission, or new formal proof was produced during that audit.
The separately authorized implementation checkpoint is recorded at the end.
Model receipt: `prefix-mask-review.json`.

**Verdict:** the proposed recurrence is mathematically sound under consecutive
final publication and immutable relevant endpoint costs. No counterexample was
found in the finite search. It is materially different from rmq8, but its total
compression benefit remains unknown and can be negative.

## Recurrence and ties

Let C[a] be the finalized upper32 endpoint cost. A mask at a has a set bit j
exactly when C[a+j] is a **strict** new prefix minimum while scanning rightward,
for j in 0..31. For a prefix of length L, the highest set bit among its low L
bits is the argmin. Strict records mean the earliest position wins equal costs.

When prepending q, shift the previous rolling mask left by one and truncate to
u32. Repeatedly inspect its least set bit and delete it while that old record's
cost is >=C[q]; stop on the first lower cost, then set bit0. Old record costs
strictly decrease in increasing-bit order. Deleting their dominated prefix is
therefore sufficient, and no old non-record can become newly minimal. A point
enters the rolling structure once and is popped or expires once. Across N
publications, successful pops are at most N; there is at most one unsuccessful
comparison per publication. This amortized claim concerns the rolling state,
not the number of appearances in immutable saved snapshots.

Necessary details:

- Pop on **>=**, not >. Costs [5,5] must produce mask1; retaining both bits makes
  the highest-bit query incorrectly choose the longer tie.
- Compare only `ring[index] >> 32`. Equal upper costs with lower choice words
  [900,0] still require the earlier endpoint; comparing whole u64 cells would
  introduce the wrong tie rule.
- For L=32, use all u32 bits explicitly. `(1u32 << 32)-1` is invalid Rust under
  the checked compilation settings. Validate 1<=L<=32 before other shifts.
- A zero masked result must take the scalar fallback before computing a highest
  bit. Leading-zeros=32 followed by 31-32 would otherwise underflow.

## Actual publication order and ring lifetime

The source has five publication sites counting initialization:

1. `ring[n % D_RING] = 0` initializes the terminal endpoint n. Start its mask as
   bit0 only, representing no nonexistent positions beyond n.
2. Each of the three finalized `ring[q] = v` writes in `d_gap` publishes q.
3. `ring[p] = best` after `d_node_best` in `d_dp` publishes a node p.

The ordinary reverse sweep processes gaps high-to-low, then their node, and
advances hi=p. With the retained node0, valid streams publish n,n-1,...,0 once
each. Do not publish from `d_init` or `d_push`: these are provisional earlier
cells. `st[1]` tracks initialization, not finalization, so it is not a substitute
for a published frontier.

`d_back` writes p-x for 1<=x<=255, and `d_init` writes positions strictly below
p. `d_best_len` accesses future endpoints at most p+258. A saved 32-position
snapshot starting at such an endpoint reaches at most p+289, and 289+255=544 is
less than D_RING=1024. Thus those earlier writes cannot alias the relevant final
endpoint range. Long gaps still finalize every intervening position before a
later query; the model crosses multiple 1024-cell ring wraps.

This argument does not authorize arbitrary cached queries up to 1023 positions
ahead: earlier writes can alias sufficiently distant old ring slots. Keep the
existing <=258 candidate endpoint bound, published-range/ownership invariants,
and an unchanged scalar fallback outside the valid fast-path domain. If a caller
ever publishes nonconsecutively, shifting the previous rolling mask is invalid;
disable the fast path or explicitly rebuild valid state rather than silently
treating a one-bit reset as a complete 32-position snapshot.

## Length prices and block transitions

Use the existing helper name `r10_price_ends` from
`scripts/build-round10-rmq.py`. It computes maximal runs of **equal actual lc
values**, not merely equal length-code symbols. Rebuild those ends after the
initial `d_load` in d_dp and after the `d_load` inside d_block on every actual
block change. The mask itself need not be invalidated on a price-block change:
it summarizes already finalized suffix costs, independent of the current lc.

Within one constant-price run, query fixed chunks of at most32 and add the same
length price to the selected endpoint. Across chunks/runs, compare packed
`(raw_cost << 9) | length` values, retaining the shortest global tie. Each sum
contains two u32 values, below2^33; legal lengths are below512, so this packing
does not overflow or mix the tie bits.

A stale run cache is a real counterexample: endpoint costs [0,1], old lc [0,0],
new lc [100,0]. Treating the new interval as the old constant run selects endpoint0
at100 instead of endpoint1 at1. Likewise, mutating a finalized cost after its
mask was built breaks correctness: [5,10] has mask1, but changing its second cost
to0 makes that mask stale. The actual publication discipline excludes that
mutation within the relevant window; it must not be assumed for arbitrary input
arrays passed to a standalone helper.

## Finite evidence and fallback scope

The model exhaustively checked all9840 cost sequences of lengths1..8 over
{0,1,2}: 317388 prefix queries, 73812 publications and 56286 pops. It also checked
four 2401-position patterns (equal, increasing, decreasing, mixed/random) using
a 1024-cell ring, full u32 cost values, 46416 provisional earlier writes, 260
length-price changes and 28776 split-run queries. All answers match scalar cost
plus shortest-length tie selection. That second model has 9600 publications,
7196 pops and 11536 cost comparisons.

Sixteen invalid-state guard-routing cases on 32/64-bit arithmetic cover empty
or reversed ranges, e>259, zero/unpublished masks, stale price generation and
position overflow. They select the unchanged scalar oracle, including its old
packed behavior for invalid intervals. This is **fallback-routing model evidence**,
not a test of a Rust implementation that does not yet exist.

## Cost and proof decision

Unlike rmq8, each arbitrary-alignment <=32 prefix query can use one mask read,
bit masking/highest-bit selection and one endpoint-cost read. There are no
unaligned scalar edge fragments. Publication instead occurs at **every byte**:
one four-byte mask store, shift/bit operations and amortized up to roughly two
future-cost comparisons/reads. The cache is 1024*u32 =4KiB, versus rmq8's 1KiB
summary array, plus the existing price-end array. Short or singleton lc runs
may save no endpoint reads while still paying all publication work. Nothing in
the failed rmq8 measurement or this operation count determines the new net time.

Proof changes would reach d_gap's three finalization branches, d_cand query
arguments, d_block price-end maintenance, the outer d_dp mask/frontier state and
new mask helpers. At minimum, prove bounded shift/index/loop totality and preserve
the original output-length/checked-emission obligation. Universal equality would
add prefix-minimum, finalization and snapshot-lifetime invariants; finite model
agreement alone does not provide them.

The mechanism is not rejected mathematically. Any implementation should first
show 444 finite token/decode equality and public same bytes, then paired total
compression. Count publications, successful pops, mask queries and avoided
scalar endpoint reads without microtimers to distinguish insufficient opportunity
from a defective cache. Prioritize the already running packed-record work; do not
expand a new algorithm and its proof simultaneously without a measured reason.

## Subsequent authorized implementation checkpoint

One fixed candidate was generated after the audit:
`candidates/r10-backward-prefixmask`, parent verified record-nonempty, Rust
SHA-256 `5a4b534b9966d21f06f8cde90fe0c5c6f5d6c4429c2c19c57a2a1e300c9993c1`.
Generator: `scripts/build-round10-backward-prefixmask.py`. Fourteen exact
replacement regions reverse to the parent bytes. The original forward parser,
record representation and checked emitters are unchanged.

The implementation uses getters (including existing d_cell) around array reads,
leading_zeros rather than a new trailing-zero intrinsic, explicit fuel32/259/9,
an exact singleton d_bcost path, a separate len32 mask case, and original scalar
fallbacks. State records the published frontier, rolling mask, enabled flag and
input end. A nonconsecutive publication disables caching. Publication occurs
only at the terminal endpoint, three finalized gap writes and finalized nodes;
the two original d_load sites refresh price-run ends.

A second model follows the actual helper control flow, including fuels and
fallbacks: five patterns, 11530 publications, 34545 queries, 192 scalar fallbacks,
11876 singleton queries, 15295 publication comparisons and 285 price-block
changes. It checks zero masks, invalid run ends, disabled/nonconsecutive state,
ring wrap and earlier provisional writes. Exact model outputs match the original
scalar oracle. Receipt: the candidate's `helper-model-check.json`.

This remains **model evidence**, not native Rust or performance evidence. The
copied record proof `86cfc36a...` is **UNADAPTED_PARENT_ONLY**. Minimum proof work
includes nine small/new helper specifications (four loop-bearing definitions),
cache-state/result plumbing through the three d_gap branches, d_cand, d_block and
d_dp, and the unchanged original obligation/axiom checks. Actual extraction is
the authority for those signatures. Full proof work is deferred until a major
measured performance signal. No further new algorithm is planned by this agent.
