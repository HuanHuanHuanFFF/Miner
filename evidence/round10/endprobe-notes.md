# D long-jump tail supplement

Candidate: `candidates/r10-forward-endprobe`, parent
`candidates/r9-block-scalar`. Original #361 authorship remains in the inherited
manifest/provenance. Exact Rust SHA-256:
`474714b7007f73ac04d7ff7e2c5199385fd3d10e4b3fc323ad6fd3c58a7ba576`.

## Question, mechanism and distinction

Scalar inserts every byte of a taken long match, but does not query those
interior positions. This experiment adds one search at the **true** match end
minus two, only when that position occurs in the existing `insert_range` and
is below `lim`. It uses the existing `d4`, `d7`, `h3d` and `nice` budgets. There
is no new table, all-input prepass, depth sweep or position sweep.

The supplemental search runs immediately after `insert_pos` at that position,
using the heads returned by that insertion. Querying only after the whole
range was inserted would see future positions and would violate the intended
search state; that implementation was not used. Every original insertion still
occurs once in its original order. The search uses a local candidate array and
only appends `rs` when it found a candidate. Original `cands`, `pc`, `pn`,
`ppos`, prices, statistics, first plan and search-control variables are untouched.

The new record uses the ordinary backward-extension routine and `tbmax`.
Duplicate suppression is inactive for that new node: the old jump has only two
bytes of continuation left, and the previous original node is not adjacent to
this tail point under the selected configurations. No mutation is made to the
original duplicate-tracking state, so the next original record still sees the
same state it saw in scalar.

This covers a fixed unsearched long-jump tail. R7's `ct6` changed continuation
search/forward planning, and R10's tag/hash supplements ran at the millions of
existing search nodes. R9's whole-input q9 prepass paid for maintaining and
querying a separate finder. Those earlier costs do not measure this bounded
tail-only query using tables already maintained by the original parser.

## Coverage check from the source

**VERIFIED source fact:** `d_gap` sets its literal-only boundary to
`end.saturating_sub(2)`. For a longest match from `p` ending at `E`, the original
useful continuation starts are at most `E-3`. Inserting a node at `j=E-2` leaves
the old node's gap covering all positions `p+1..E-3`; the old match has fewer
than three bytes remaining at or above the new node.

Other candidates at the old node are no longer than its longest candidate.
Their useful continuation starts therefore cannot lie above that same cutoff.
The supplemental query may offer a new match ending beyond E, together with its
backward extensions. The old forward plan is deliberately preserved, keeping
the initial cost tables and block-start model the same.

This argument does **not** claim monotone final compressed size. Backward
pushes, ties, modeled versus actual block boundaries and encoder costs still
need measurement. The actual source/obligation, axiom whitelist and round trip
must be checked before any accepted-candidate claim.

## Implemented artifacts and checks

- `scripts/build-round10-forward-endprobe.py`: deterministically appends two
  helpers and replaces the one D range-insertion call. Reversing those changes
  restores parent Rust bytes exactly.
- `scripts/research-round10-endprobe.py`: optional runner diagnostic under
  `endprobe_diagnostics: true`; requires scalar and endprobe spec entries.
  It checks all 28 public files plus 84 fixed generated inputs.

For public D files and every forced-D synthetic case, the diagnostic compares
the first plan byte-for-byte, decodes both `rs` streams and requires every old
node position and candidate payload to remain in order. Extra nodes must be
nonempty and occur in the tail-position set derived independently from the
old stream's long-jump records. Every extra match and its recorded backward
extension is byte-checked using the reference validator. Both complete parsers
must decode to the original input; non-D routes must also retain exact tokens.
Final D token equality is deliberately not an acceptance condition.

The diagnostic reports eligible tails, nonempty extra nodes, added candidate
records and length coverage. Those are opportunity counts, not compressed-byte
benefits. Compilation has a 180-second bound and execution a 420-second bound;
failure retains logs and a `DIAGNOSTIC_FAILED` receipt.

**VERIFIED locally:** generator execution, exact parent-reversal assertion,
source/manifest hashes, file-size cap, and Python syntax. **UNKNOWN:** Rust
compilation, diagnostic result, actual added-match counts, official paired
time/size, extraction and complete proof gate. `Parse.lean` is the unchanged
parent at SHA-256 `aa21da6f74e81314297df07beecbfc98b15c848354437674bdb9347d8632f0af`
and is explicitly unadapted to the new helper calls.

## Decision checkpoint

First reject any changed initial plan, lost original node, invalid extra
position or byte mismatch. If coverage checks pass, use paired public total
compression and size to judge whether the added search has paid for itself.
No encoded-size improvement or an unfavorable time/size tradeoff stops this
single implementation; no position/depth expansion follows from opportunity
counts alone. Full proof work waits for a useful measured result.
