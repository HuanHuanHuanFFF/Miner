# Sparse mask follow-on: discriminator only

This uses only the pre-freeze public23 P/I design and six old seed27051001
formula cells. No new Lean kernel or CI request was created.

`overlap-census.json` compares the intersection of nonzero input/weight indices
with nominal existing product visits after source23's input pruning and guards.
The sparse batch1/batch8 counts fall to **43.7% /47.7%** of that nominal work.
Normal and wide cells offer little additional reduction. The old formula still
computes outputs; its matching hashes bind fixtures, not a new kernel.

This is a possible large MAC reduction in sparse cells, not a speed result.
Preparation, mask enumeration, extra arrays and lost sharing can consume it.
Generating masks in a second weight pass is especially unattractive for batch1;
a single metadata/mask pass has not been implemented or proved. Do not compare
against dense n alone: many input zeros were already skipped by P/I.

`word-index-model.json` independently constructs a32-slot one-hot lookup using
UInt32 multiply/shift. All32 one-hot values, all65536 low16-bit masks and5008
directed/random32-bit masks enumerate correctly. This avoids assuming that
Nat.log2 is one hardware instruction. The general least-set-bit identity,
actual mask construction, n/tail bounds and getters still need a formal link.
The lookup and finite tests are not Lean acceptance or a native cost measure.

First useful future experiment: keep all non-sparse paths identical, include
metadata/mask generation and complete output costs, and compare the actual
whole model against the strong source. A simple zero-weight skip control can
distinguish branch cost from bitset enumeration. Reuse original QFL/I9 cache
and zero-product reasoning; do not start a new float rounding proof. Only
useful complete-model cost warrants the actual mask/getter refinement.
