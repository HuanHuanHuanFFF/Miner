# Round 9: exact tail-word rejection in D's forward search

Created 2026-10-08 as an independent candidate from verified
`candidates/r7-mid361-block1`. Earlier `r9-block-scalar` and `r9-block-unroll4`
files were not changed. No CI, commit, push, wallet action, or competition
submission was started by this implementation.

## Source evidence and patch

**VERIFIED**: parent Rust `d_walk`, lines 2383–2421, probes every eligible chain
node while `best < cap`, `best < nice`, and `nc < 15`. Both D chain searches use
that function. The forward DP's existing `walk_t`, lines 1313–1354, already uses
an eight-byte rejection filter for candidates that cannot beat `best`.

`r9-block-tail` copies that filter into `d_walk`:

- Initialize `tw = tailw(s, i, best)`.
- Probe a node only if `tailw(s, c, best) == tw`.
- Whenever a longer match updates `best`, refresh `tw` at position `i`.
- Preserve the original distance guard, `best < cap && best < nice`, candidate
  limit, chain traversal, depth decrement, and `probe(..., cap, best)` arguments.

The cap is never replaced by `nice`: a successful probe still returns the real
match length, and `nice` stops subsequent nodes as before. Search routes, knob
tables, record/back-extension construction, backward planning, and emitters are
unchanged. There is no additional matching pass.

**INFERRED equivalence argument**: below length eight, both `tailw` values are
zero, so every node still reaches probe. At `best >= 8`, a match longer than
`best` must agree in the eight bytes at offsets `best - 7 .. best`, inclusive.
If those bytes differ, the node cannot return a nonzero result from the original
probe when `b8` is the actual word at `i`, as supplied by D's finder. Tail mismatch
therefore removes only losing probes. It does not alter a winning candidate's
length, distance, order, or stopping behavior. Equal tails remain subject to the
original probe, so false positive word equality does not accept a match.

## Candidate identity and provenance

Generator: `scripts/make-round9-tail.py`; `--check` verifies deterministic output,
parent hashes, reversible one-region Rust/proof edits, and file-size bounds.
Parent author and verified gate pointers are preserved in the manifest; the
filter is explicitly attributed to #361's existing `walk_t` / `tailw`.

| File | SHA-256 |
|---|---|
| Parent Rust | `950eb21b3918adce71bad2737774f2e37531cfbcd45fb17afdd806ee0adc3ed5` |
| Parent proof | `f815bcb880d9da3c18d8fcb768f66ea2222a6348187646eb027c1cb020bb2fb0` |
| `candidates/r9-block-tail/parse.rs` | `5995eefc98d48964c9efd9267b12621754f9e485c6718d7725009c0a6ba69ec3` |
| `candidates/r9-block-tail/Parse.lean` | `2b2fab469bc1acf3fc87f424e323392c82e5c40fd778e4e12bcd94b259f387ba` |

## Proof draft

The public `d_walk` signature and `d_walk_spec` monotone/capped-best postcondition
remain the same. Its loop now carries `tw`. The draft copies the existing
`walk_t_loop_spec` and `walk_t_spec` proof shapes, inserts D's `nice` parameter,
and preserves their bound invariant and depth measure. The existing `tailw_spec`
already appears earlier in the proof.

**UNKNOWN until extraction**: the expected loop call is
`d_walk_loop s prev i b8 cap cands nice nc best tw c k`, with mutable state
`(cands, nc, best, tw, c, k)`. This is inferred from the existing extracted D
loop's argument order plus `walk_t`'s tail state. The original obligation, axiom
checks, and public round trip still determine acceptance; a source-preserving
proof adaptation is not an acceptance claim.

## Checks and performance question

**VERIFIED** local checks:

- Generator and `--check` completed with exact candidate bytes and declared
  hashes; reversing the changed regions restores the parent source/proof.
- A finite Python model compared the unfiltered and filtered finder across
  **20,000 cases with zero appended-candidate, count, or best-length differences**.
  Inputs included random bytes, repeated motifs with perturbations, constant
  data, low and high starting lengths, depth limits, candidate limits, and
  multiple nice thresholds. Chains in this check were valid descending chains.

**UNKNOWN**: actual Rust token/output equivalence (including the 444-case
framework), malformed-chain cases, fresh extraction, Lean compilation, original
gate, and total-compression performance. The local model is not a timing result.

The filter adds word loads but may avoid full common-prefix scans at losing
nodes. Its benefit depends on D search's share of total runtime and the frequency
of `best >= 8` losing nodes; stage timing can diagnose that share. Compare with
paired block1 to isolate the mechanism, with paired public #361 to evaluate the
overall size/time tradeoff, and repeat on a second runner before treating a
small gain as stable. Public acceptance or speed does not establish admission,
private stage2, rank, or rewards.
