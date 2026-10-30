# Word proof: public predecessor interface audit

Read 2026-10-29, source 27 SHA-256
`f92ee2c9a29de78dc434ad158b7141c0e4b5a67a5a198a353d59a4703481aa67`.
Source stays in D's ignored `competition-state/source-private/`; this file is
an original interface/cost analysis, not a republication. Current mixer is 36,
not 27. Fresh current/predecessor report chain is owned by D.

## Existing useful proof interfaces

- `Ybo` (line 464), `X7` (466): three scalar UInt64 words, signed 192-bit
  interpretation `YC`, fast native finish equal to original `finishWord`.
  This is the useful rounding endpoint for an independently proved new carrier.
- `YL` (517), `Zr` (528): per-product addition to three scalar words plus a
  deferred sign compensation counter, exact modulo 2^192. It already removes
  per-MAC big integer/limb-array updates. Do not call that our innovation.
- `YD` (535), `ZV` (537): apply the compensation counter once; exact-zero uses
  the 2^32 sentinel so the outer caller recomputes with the correct zero sign.
- `YL6` (610), `I7` (613): products whose alignment shift is at most 63.
- `YL16` (623), `C5` (635): alignment shift at most 16, with upper-word state
  reduced to a sign extension. `I6` (653) connects actual indexed loops.
- `Yc`/`Zp` (595/824) build and prove vector exponent-range metadata.
  `Yp`/`Yu` (603/605) include **bias** in common lower/upper exponents.
  `YaU` (660) rejects nonfinite, reversed and >122-wide ranges, enforces
  input bounds and n<2^20, and falls back on exact zero.
- `A9` (826) handles scaling plus sentinel fallback to the original result.
- `YS64` (714)/`Y64` (1265) compute four input rows with one shared weight
  load. `YS6c4` (766)/`Yc64` (1305) compute four output columns with one input
  load. The four-lane scheduling is already present.

## Consequences for this role

Our original 128-bit carrier can target `Ybo (signExtend hi) hi lo`; the signed
192-bit interpretation equals signed128 by a small integer-range proof, then
`X7` supplies the exact fast rounding endpoint. Rebuilding the large rational
rounding proof is unnecessary when extending this predecessor.

Block16 still has a distinct mechanism: prealignment removes mantissa/exponent
extraction and variable shift on each MAC, and replaces per-product carry with
one carry per block. It must beat the existing scalar four-lane implementation
including preparation and metadata. Existing q≤16 only bounds each product
below2^64; it does **not** imply the block16 guard ma*mb<2^59.

The two-Nat bucket route is a proof-cost alternative. Its MAC uses UInt64
multiplication of UInt32 magnitudes, conversion to Nat, and one of two Nat
additions. The product is exact for every pair of UInt32 words; a single
no-wrap lemma suffices. If each block's mass is below2^63, the pinned runtime
can represent the block sums as immediate Nat values. This is a source-cost
hypothesis, not emitted-C or timing evidence. Generic Nat multiplication has
an overflow division check and is deliberately avoided. Generic Int MAC was
rejected because the pinned small-Int limit is INT_MAX even on64bit.

## Next decision

Keep the first small runtime/modular compile. Do not expand the41KB old bridge
until that feedback. Compile the4.8KB Nat alternative only as a second small
root if capacity allows. In parallel, test coverage of the **actual** block
guard on frozen public fixtures and make a self-written 128→192 endpoint
extension against predecessor27; no source replay or acceptance claim until
the exact extension is compiled. Do not duplicate C's whole-model route.

All new helpers remain NOT_COMPILED; all12 gate and current-champion timing
for this role are UNKNOWN.

Size constraint: predecessor27 is255647B, leaving353B under256000B. The
endpoint extension alone exceeds that free space. A literal appended27 is a
helper diagnostic, not a valid candidate. Predecessor12 is218232B and exposes
the same `Ybo`/`X7` names at449/451; integrating there has space, but its actual
runtime/fullgate/per-board costs must be measured separately. A future27 patch
must replace or remove genuinely unused code with exact verification, not
silently raise the limit.

Policy discriminator: the pinned official policy splits each attribute string
and tests its **last token** against the whitelist (`sandbox.py`:407-413).
Thus named `@[specialize q]` / `@[specialize relu]` is rejected even though
Lean supports explicit specialization arguments. This does not affect the
currently frozen `@[inline]` patch. Do not use a grammar trick to bypass policy.

20:05 parent comparison correction processed: live board config hashes differ
from current-champion report hashes. The old .93335/.92884 targets are planning
points only; current-champion calibrated ratios stay UNKNOWN absent a valid
policy/configuration reconciliation. This does not alter internal mechanism
checks or source/proof facts.
