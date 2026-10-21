# Backward tie: interface and obligation audit

Status: **DRAFT / NOT COMPILED**. This note is source inspection, not a fresh
extraction, Lean acceptance, public gate, performance or formal result.

Frozen candidate `r25-sol-backtie`:

- Rust SHA-256 `043eed530748eafe81e0c2f8c8177c7b6caf03cb79f5aa065233c8689ce81dd8`.
- Lean SHA-256 `c4e8ba55389520e3822a2215a0e0ba6b2c0951545a1d1c0c1ec75bd6eabbb9c4`.
- Exact parent `r22-595-chain-halfhead`, Rust
  `57a8fb4feffa52d6b966899c4a56bc4754f6fc967a05cf52d5b02a574d037275`, Lean
  `4ff09d168269ae8d9c93e602496b01078d2d0ec80f27d6cd16041d91a76c70a6`.

## Verified source scope

`scripts/build-round25-sol-backtie.py --check` reconstructed the frozen pair
and compared bytes. Reversing five Rust substitutions restores the complete
parent source; reversing four Lean interface substitutions restores the
complete parent proof. All routes, parameters, tables, recording, fold,
emission, original obligation and existing axiom policy remain inherited.
This is a claim about the diff only; it does not transfer the parent's gate.

The changed Rust functions take the existing pending-literal start `ls` as
an additional scalar argument:

```text
pc_f_try(s, c, c2, p, l, d, minl, ls)
pc_f_deepen(s, prev, c, c2, p, l, d, dp, minl, ls)
```

`pc_run1c` already captures `ls` in its loop. Its signature and state fields
are unchanged, and only the call to `pc_f_deepen` adds that argument. Unlike
the R24 owned-price array migration, this edit introduces no new array,
borrow or loop. Actual extracted loop parameter ordering must still be read.

## Intended proof bridge

The existing `PC.f_try_spec` assumes `c <= p` and a valid `MatchAt` at
`(p,l,d)`, and returns the same `MatchAt` postcondition. The interface draft
adds an arbitrary `ls` argument without a new premise. It is used only in
the guarded comparison `ls < p`; no array access uses `ls` as an index.

Every old strictly-longer success remains accepted. A new success has
`m == l`, so `l >= 3` from the original match suffices for the existing
`MatchAt.of_try` construction. The original full `pc_common_from(...,0)`
proves the actual forward bytes for both old and new successes. No
backward byte is assumed by the returned `MatchAt`; the existing fold
routine rechecks its bytes separately.

For the additional reads, the source guards supply these intended bounds:

- `c2 < c <= p` and `p+l < n` bound `c2+l`, `p+l` and their minus-one indices.
- `c2 > 0` bounds `c2-1`.
- `ls < p` implies `p > 0`.
- `d < p` bounds `p-1-d`.
- The original `MatchAt` supplies `3 <= l <= 258`, valid distance, and
  `p+l <= n`; the new tie additionally requires `l < 258`.

`PC.f_deepen_spec` can compose the same `MatchAt` interface for its one or
two existing calls, forwarding `ls`. Its postcondition and array type are
unchanged. The main loop continues to receive the original `MatchAt`
property, so no geometric backward-saving claim is required for safety.

## Unclosed work and ordering

The current `f_try_spec` body is inherited. Its `step*`, branch splitting,
`Matches.zero` and `MatchAt.of_try` calls have not been checked against the
new extracted conditionals. Failures may require local branch proof or
arithmetic repair. Any changed extracted binder order must be reflected
before claiming acceptance; a source argument audit is not enough.

If the native byte/token change offers a useful two-axis opportunity,
perform exact fresh extraction, inspect these two helper signatures plus
`pc_run1c_loop0`, then run the original full gate with its existing
obligation, whitelist and roundtrip. Freeze the passing exact pair before
new independent performance confirmation. No source-hash update or proof
success is inferred from the native checker.

## Bounded native discrimination material

`scripts/build-round25-sol-helper-check.py` extracts the exact parent and
candidate `pc_be8`, `pc_xor8`, `pc_common_from`, and `pc_f_try` into
`native-helper-check.rs`. The prepared checker validates real selected
bytes, preservation of old longer successes and the scope of every new
delta. Its cases include minimum3/4, length258, exact32768 windows,
source0/future links, the input endpoint, and overlapping periodic input.
The checker has **not been compiled or executed** locally. It does not
verify full parsing, real corpus coverage, Lean, encoded savings or speed.
