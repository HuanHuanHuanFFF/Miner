# Numeric representation after the minimal bridge

This is a mechanism and proof-cost decision document, not a new runtime candidate. The next runtime step waits for the pinned compiler response to `repair1-manifest.json`. No local Lean, compiler, benchmark or current confirmation inputs were used.

## Actual cost boundary

The archived f7f accepted ADD arm has one `lean_uint32_to_float32` and one external `lean_float32_to_bits`, with repeated exponent/order extraction and original words kept live across the external call. `final-C-cost.json` in the R16 scalar-representation directory binds the exact selected C body SHA `4e21dc0bc54b8bc1a9badfde27ee604c0bff323c49b8db1f0d6cc1670939fd89`; it does not bind scalar assembly because none was captured.

The pinned Lean 293d5d0c header, read again here, makes `lean_float32_to_uint32` an inline three-way expression:

```c
return 0. <= a ? (a < 4294967296. ? (uint32_t)a : UINT32_MAX) : 0;
```

Therefore numeric roundtrip changes the accepted arithmetic chain from one int-to-float conversion plus external bit extraction to two dependent numerical conversions, potentially two clamp comparisons, and integer reconstruction. There is no verified cycle advantage yet. Inlining removes an ABI call boundary but does not prove removal of comparisons, spills or conversion latency.

The smallest useful runtime discriminator is **one actual sorted accepted callback**, after the scalar bridge compiles, whose C and assembly show:

1. Each input exponent, sign and mantissa is extracted once and the high/low order is chosen once.
2. There is no `toBits` call on the accepted branch and no new allocation/Nat/closure path.
3. The exact remaining numeric conversion instructions, clamp branches and input lifetimes are visible in the selected bench callback.
4. The complete ADD path is timed against B2 only after its exact public proof/gate passes. Isolated helper timing or C operation counts cannot replace this.

This discriminates call-boundary cost from sorting/field cost. Merely replacing `toBits` in the old repeated-selection source leaves an unresolved cause of the 1.87392 ADD negative. Re-running the unchanged f7f is not proposed.

## Repacking can avoid a general log2 and the late lower-exponent guard

Let sorted normal inputs have fields `ehi >= elo >= 1`, `d=ehi-elo<=7`, mantissas `a,b in [2^23,2^24)`, and high sign `s`. For same signs put `N=a*2^d+b`; for opposite signs require `d>=1` and put `N=a*2^d-b`. Retain the original `N>=2^23` fast-arm guard. The repaired bridge returns the rounded integer `R=RN_binary32(N)`, with `R<2^32`.

The proposed full-domain mathematical formulas are:

| Input signs | Carry selector from R | Normalization shift | Output exponent field |
| --- | --- | --- | --- |
| Same | `c = [R >= 2^(24+d)]` | `d+c` | `ehi+c` |
| Opposite, d>=1 | `c = [R >= 2^(23+d)]` | `d-1+c` | `ehi-1+c` |

The mantissa is `R >> shift`, and the fraction is its low 23 bits. The same-sign upper exponent 255 must become signed infinity, with fraction **zero**; packing exponent 255 together with the computed nonzero fraction would make a NaN. The opposite-sign exponent cannot underflow: `ehi>=d+1>=2`, so `ehi-1+c>=1`. Same-sign output is also >=1. Thus the lower-exponent fallback guard is redundant under the original input premises; the only new exceptional result is same-sign overflow.

The interval proof is short on paper. Same-sign `R` lies in `[2^(23+d),2^(25+d))`: for d=0, `N<=2^25-2`, itself representable; for d>=1, `N<3*2^(23+d)<2^(25+d)` and the middle endpoint is representable. Opposite-sign `R` lies in `[2^(22+d),2^(24+d))`: the high-N guard gives the d=1 lower endpoint, and d>=2 gives `N>=2^(23+d)-2^24+1>2^(22+d)`; the upper bound is below the representable endpoint `2^(24+d)-2^23`. RNE cannot cross a representable endpoint outside the input interval. In either interval, the threshold in the table selects the leading exponent of R, hence exact normalization and the output exponent formulas.

This is **paper reasoning, not a Lean theorem**. The remaining formal steps are an interval/rounding lemma, shift divisibility for the rounded integer, UInt32 shift/mask correspondence, and connection to the existing `raw_add_dyadic` statement. Existing R16 sorted-alignment lemmas can be reused; no extra domain hypothesis may remain on the final public spec. No full formula is integrated before actual interface feedback.

## New finite discriminator and a concrete trap

`check-threshold-repack.py` uses only constructed mantissa/rounding-boundary inputs, under a real 5-second subprocess timeout. `threshold-repack-check.json` records **54112** accepted cases, including **1808** shift=8 cases and **4196** same-sign overflows. The formula agrees with direct conversion of the exact scaled integer to host binary32 in that finite set. It is not exhaustive, a Lean proof, or performance evidence.

There are **320** tested cases where using N rather than R for the threshold chooses the wrong normalization. One explicit case is `a=8388608`, `b=16777215`, `d=1`, same signs: `N=33554431`, `R=33554432`; the correct shift is 2. A shift=8 example is `a=16711679`, `b=8388672`, `d=7`: `N=2147483584`, `R=2147483648`. These are exact integer counterexamples to the tempting N-threshold shortcut and cannot be discarded as timing noise.

## Budget and adoption decision

The complete scalar bridge has 17885 bytes of remaining file budget before any ADD wiring. Existing R16 ADD support contains further alignment and bit-repack proofs; reuse must be costed by exact dependency extraction rather than appending all of it. After the scalar bridge is accepted, first choose between a small explicit sorted callback discriminator and completing these threshold lemmas, based on D's compile queue and actual available bytes. There is no quantitative whole-package gain estimate yet.

The UInt64 MUL analogue is a separate possible route: 24x24-bit products fit below 2^48 and the analogous native numeric model is available, but `Float32.toUInt64` may have more expensive unsigned conversion lowering. It should not receive a full proof port before its actual callback code and cost show a reason to proceed.
