# R11-W01 independent audit: machine loop and exact finish

## Status and edit recommendation

- Inspected exact `Kernel.original.lean`, SHA256 `4bdd1e7db35cd85e17d06511721d5dbf7f654ec12e58633264b08a086ec54fa0`, 252609 bytes.
- Scope: `R11CrossRows.wordLoop` / `wordLoop_eq` / `dot8_lane` / `finish8_word` / `blockAt_word`, with actual `NativeFinal.dotLoop`, `Packed10.finish_eq_dot`, and `Packed10Index.stepNat`/`next_decreases`.
- **Lean compiler: NOT_RUN.** No Lean execution or acceptance claim is made.
- **Smallest edit for these owned declarations: no edit.** Their statements, argument order, runtime state correspondence, and recursive measure line up with the existing concrete parent declarations. No demonstrated type error or semantic counterexample was found in these declarations. Do not replace them merely to make an uncompiled proof look different.

## Concrete machine-read equality

`wordLoop` converts `hk : k < count` through the actual `USize.lt_iff_toNat_lt` and `hn : count.toNat = n` into `hkn : k.toNat < n`. The packet read is

```lean
v.toArray.uget k (by simpa only [v.size_toArray] using hkn)
```

The local `hread` identifies it with the actual packet

```lean
v.get ⟨k.toNat, hkn⟩
```

by `rfl`. This is the same definitional equality already used by `Packed10Index.ugetB_get` in this source. Proof irrelevance reconciles the two proof arguments. There is no `∀ k, read ... = ...` assumption replacing the concrete read.

## No-wrap and recursion

The guarded call advances from `k` to `k+1` only under `k<count`. Source theorem `Packed10Index.stepNat` proves

```lean
(k + 1).toNat = k.toNat + 1
```

using `k.toNat < count.toNat` and `count.toNat < USize.size`, hence `k.toNat+1 < USize.size`. `Packed10Index.next_decreases hk` then proves exactly the measure required by both `wordLoop` and `wordLoop_eq`:

```lean
count.toNat - (k + 1).toNat < count.toNat - k.toNat
```

The loop stops at `k=count`; it never increments the maximum representable index as an active iteration. The proof covers arbitrary representable `k`, including `k≥count`, whose machine and Nat loops both return their accumulator unchanged.

`dot8` establishes the real initial count premise using `USize.toNat_ofNat_of_lt' hn` with `hn : n<USize.size`. The input/output-array size guards do not replace this premise, and are not needed for this particular packet read: its vector has length `n` by construction.

## Eight exact finishing routes

Let `r∈{0,1,2,3}` and `j∈{0,1}`. `laneIndex r j = r+4*j` selects a column-major accumulator. `finish8` stores a row-major word:

| r | j | F8 lane | W8 field | A base | B base |
|---:|---:|---|---|---|---|
| 0 | 0 | s0 | w0 | a0 | b0 |
| 0 | 1 | s4 | w1 | a0 | b0+1 |
| 1 | 0 | s1 | w2 | a1 | b1 |
| 1 | 1 | s5 | w3 | a1 | b1+1 |
| 2 | 0 | s2 | w4 | a2 | b2 |
| 2 | 1 | s6 | w5 | a2 | b2+1 |
| 3 | 0 | s3 | w6 | a3 | b3 |
| 3 | 1 | s7 | w7 | a3 | b3+1 |

`finish8_word` is eight definitional projection cases followed by the existing exact all-word round trip

```lean
ExecFloat.Binary.ofBits32 q.raw.1 = q
```

(`rebuild`, proved by `ExecFloat.Binary.ofBits32_toBits32`). It does not assert native NaN payload preservation.

`blockAt_word` applies the actual `Packed10.finish_eq_dot`, whose sole new premise is the exact accumulator equality

```lean
result = NativeFinal.dotLoop n baseA baseB p A B 0 Packed10.zero32
```

`dot8_lane` supplies that premise. Its modulo/division indices reduce to `r` and `j` after the eight finite lane cases. The original `Packed10.finish` performs the native non-NaN conversion or the original `R7NaNReplay.replayEarly` on the original `A,B`, with the individual output's exact bases. Thus the NaN branch and raw-payload/sign choice are inherited from the source theorem; no substitute fallback is introduced.

## Zero length

For `n=0`, `dot8` has `count=0`; no `uget` occurs, and all eight lanes stay `Float32.ofBits 0`. `natLoop_lane`, `wordLoop_eq`, and `dot8_lane` still have the correct statements. `finish8` invokes the existing exact finish on each zero accumulator. This analysis is about the generic declarations: the submission's route guard separately rejects `n=0` and uses the retained parent path.

## Remaining compiler-only checks

The following remain explicit NOT_RUN obligations, even though the source matches its concrete dependencies:

1. Elaborate `wordLoop_eq` under both `-DautoImplicit=false` and `-DrelaxedAutoImplicit=false`, including the recursive theorem application in `rw` and proof-irrelevant `uget` rewrites.
2. Confirm `decreasing_by all_goals exact Packed10Index.next_decreases (by assumption)` discharges the generated recursive theorem context without a tactic-context mismatch.
3. Elaborate `dot8_lane`'s `simpa only [lane_zero]` through definitional `zero8` equality.
4. Elaborate the eight `finish8_word` cases and `blockAt_word`'s `simpa [laneIndex, select4, Packed10.zero32]` against the pinned simplifier.

These are compiler validation obligations, not newly assumed mathematical hypotheses and not evidence of failure. No finite float tests were run or used as acceptance.
