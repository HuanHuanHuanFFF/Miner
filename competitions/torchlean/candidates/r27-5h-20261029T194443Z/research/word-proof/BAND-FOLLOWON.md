# Exponent-band follow-on, before the 23:20 freeze

This extends the R26 `WideBandRuntime.lean` idea. It does not introduce exponent
bands as a new mechanism, and it does not enter the current frozen CI queue.

The new discriminator is `band-full-model-census-v3.json`: six already-seen
seed 27051001 typical cells, all three dense calls, 8,910 dots and 3,598,560
logical MACs. Every dot met the stated outer range and finite guards. Literal
UInt64 block accumulation, signed carry into two words, and the R26 pair-shift
cases were replayed against arbitrary-precision integer sums. Rebased bias is
added before one final formula rounding. These new dense outputs feed the
later formula layers and match all six prior output hashes. This remains
finite Python evidence; no Lean/native candidate was compiled or timed.

For comparison, the earlier narrow-factor census covered about 85% of logical
MACs on normal/sparse cells and almost none on wide cells. The band replay also
covers the later layers whose input exponent span exceeded seven. In the wide
batch-8 cell it uses 22,150 block merges and 21,440 band shifts for 988,720 MACs
after input-zero omission. These are work counts, not cycle savings.

Each input is placed in one four-exponent band. Its local signed factor has
magnitude below 2^27. With weight span at most six, the aligned weight factor
has magnitude below 2^30. Thus any 64-product block has mass strictly below
2^63, matching the accepted modular block theorem's exact premise. A band
sum is accumulated in two words and shifted only once before merging.

The terminal base includes nonzero bias using the original Yp convention:
`min(bodyBase, idxBias + 126)`. The range guard includes the corresponding
maximum. With range at most 58 and n at most 2^20, body mass is below 2^126,
bias mass below 2^105, and their sum fits signed128. This deliberately includes
the 23-bit distinction between YL's oneW*bias term and the separate integer
bias expression. Exact zero must call the original callback; the six current
cells happened to have no exact-zero total, so they do not validate that branch.
`band-guard-counterexamples.json` separately records nine directed cases. The
minsubnormal cancellation takes the outer fallback and returns word1; the
1+2^-10 case takes the rebased fast path and returns 0x3f802000. Exact-zero
and nonfinite tests verify callback identity, including a supplied -0 result.
They do not independently prove FloatLib's special-value semantics. Removing
the zero-shift arm changes the pair (3,5) into (3,7), so that arm is retained.

The next useful experiment is a complete native call with preparation,
metadata, output allocation/destruction and the strong public23 comparator.
Preparation must create each weight factor once per call and each input's
index partition once per row. A four-column consumer can share one index and
input load across its lanes. It does not retain the original four-row sharing:
different rows generally have different band orders. Gathered weight access,
extra weight preparation and that lost sharing may erase the arithmetic gain.
UInt32 arrays still use pointer-sized slots on this runtime.

Proof work should start only after that cost discriminator is useful. The
remaining actual obligations are finite metadata, exact factors, a bijective
partition of nonzero input indices, array getters, per-block mass, the complete
carry/shift chain, bias rebase, and the original single-round/zero endpoint.
The accepted 7,658-byte modular module closes only block arithmetic under its
mass premise. A finite successful partition is not the general getter proof.
