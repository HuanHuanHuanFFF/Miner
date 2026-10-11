# End-4 CPU/state opportunity review

This review followed screen A's negative original total time. It preserves
end4's measured public quality and does not promote parser-only timing,
source load counts, assembly or finite models to a performance claim.

## What the existing receipts resolve

`end4-cpu-audit-a.json` reads the two original blocks, retains all raw input
hashes and decomposes their equal-file time-axis differences. It statically
classifies all possible original `route`/`format_id` outcomes at each file
length; an unchanged output alone never establishes an untouched path.

- Fifteen files are proved to invoke the changed PC-chain route by static
  routing or actual token differences. Their parser sample contribution is
  about **+0.637% / +0.602%** of the parent public time axis.
- Twelve files cannot invoke `pc_run1c` under any original routing branch.
  Their net differences account for approximately **33.3% / 16.5%** of the
  total observed time-axis regression. In block1 it is mostly encoder
  sample movement; in block2 it is mostly the paired incumbent denominator.
- `weights-f32.bin` has one unresolved routing branch with unchanged
  output. It is retained as UNKNOWN rather than assigned by its filename.

The parser/encoder numbers use four sample recompositions and an exact
Shapley split of their nonadditive median interaction. They sum back to
the observed public axis, but are numeric attribution, not causal hardware
profiling or adjusted performance. The complete original observations
remain **+0.924% / +0.720%** versus combo, with no qualifying current share.
The attribution supports targeting real PC parser work; it does not erase
the losses on other routes or excuse the negative total result.

## Selected local mechanism

Once the existing `end>=4 && ins<=end-4 && end-4<lim` insertion guard holds,
`ins+1<end`; therefore the original `TAIL=1` branch necessarily uses
`end-1`. The two four-byte keys at `end-4` and `end-1` are three bytes
apart. A single big-endian word at `end-4` contains both keys:

```text
end4 key = word >> 32
end1 key = (word >> 8) cast to u32
```

The approved `r25-sol-end4-wordtail` derivative hashes these local keys
with the exact masked multiply/shift/mod formula. It preserves both link
updates, in the original end4-before-end1 order; no chain node, insertion
guard or main-loop state is removed. A local cached slot below H is used
only for the eligible tail; otherwise the original slot load runs.

This differs from R12 wordhead's persistent word across hash/probe, R13
matched-ahead's skipped next-candidate load, and R24 prefix/range caches.
Those implementations' negative results remain relevant cautions about
live ranges, load overlap and maintenance cost. Here the overlap exists
because the new end4 parent introduced the adjacent key pair; the word
does not survive the recording helper call.

Current status: source reversal and finite key/index models passed;
**real Rust token/encoder/decode equality, total time and gate NOT RUN**
at preparation. One wider load plus shifts may be worse than two parallel
32-bit loads. Compiler elimination or lower instruction counts would only
support a mechanism diagnostic. First require exact end4 public parity,
then original paired total time versus end4 and combo; stop this exact
version if the tradeoff remains insufficient.

## Alternatives not implemented

- Removing the end4 store when its hash equals end1 would change
  `prev[end1]` from the added end4 node to an older node. That discards the
  mechanism's actual chain coverage; equal final head values are not
  sufficient to prove equivalent matching. Both updates stay.
- Zeroing the U32 predecessor array is a representation/runtime issue.
  Live hints often refer only to slots previously written, but a safe
  supported Rust array still initializes its elements. No sound cheap
  replacement for the initialized array was established in this audit.
  Replacing it with generation checks would add per-access work and a
  proof obligation, so it is not selected on source intuition.
- Compact predecessors and packed head layouts already have relevant
  R12/R13/R20/R22 counterexamples. End4 adds traffic, but its actual
  insertion frequency and hardware misses have not been measured; that
  alone does not justify another representation sweep.
- Carrying current input words out of `pc_probe_m` could reuse more head
  keys, but changes persistent main-loop live ranges and overlaps the
  failed R12/R13 work. The selected local two-key reuse is the smaller
  discriminator and introduces no such state.
