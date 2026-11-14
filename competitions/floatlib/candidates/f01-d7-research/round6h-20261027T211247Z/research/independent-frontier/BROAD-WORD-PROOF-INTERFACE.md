# Frozen broad-word ADD: existing jam interface

This is a source and receipt audit, not a new proof, candidate, or performance claim. Frozen runtime5655df5c and probe02747632 remain unchanged. Parent's55300 fixed host cases passed; neither that check nor the old theorem closes this public ADD.

The R19 source `grs-jam-math/low-state-repair1/Probe-jam-variable-repair1.lean`, SHA b3724bc5cb19a85fdae25187d8700bb43233ab4098a9c0a92b97a36d0eaac496, was accepted by40435830288 in diagnostic-statement-only mode. Original statement/replay/helper receipt and all7 indexed files were rehashed here. Root `R19JamVariableProbe.rne_jam` is in the15-root allowed-axiom audit, with exact interface:

```lean
theorem rne_jam (p d k : Nat) (hk : k=2 ∨ k=3 ∨ k=4) :
  roundShiftRightEven (jamDiv p (2^d)) k =
    roundShiftRightEven p (d+k)
```

`jamDiv p D = p/D + (if p%D=0 then 0 else 1-(p/D)%2)`. The theorem covers every natural p,d, including d=0. It is a Nat rounding theorem; no machine bounds, ADD fields, or public transport follow automatically. The old source header still says NOT_RUN; that immutable header predates the indexed acceptance receipt.

For the frozen UInt32 runtime's gap d<=24, let a,b be the two24-bit significands, X=8*a, Y=8*b, D=2^d, and P=X*D+Y=8*(a*2^d+b). Paper alignment identity:

`T = X + jamDiv Y D = jamDiv P D`.

This needs only even translation, since X%2=0. Historical `JamTranslate.lean.inc` c9e0cfb3b59f7eb45f8c5cdc281eb54b4598b080c2c43aae100e04df12237542 states `jam_add_even (D X m) (hD:0<D) (hX:X%2=0)`. **That translation fragment is still NOT_RUN**: it is absent from b372 and its helper roots. `TRANSLATE-ACCEPTED.md` has an accepted heading, but its body and the later ACCEPTED-HANDOFF explicitly retain NOT_RUN. Treat it as a small proof sketch only.

Once this identity and typed conversion are established, both branches use the accepted interface directly:

- No leading carry: `RNE_3(T) = RNE_(d+3)(P)` by `rne_jam P d 3`.
- Leading carry: runtime U=(T>>1)|(T&1) is `jamDiv T 2`. First `rne_jam T 1 3` yields `RNE_3(U)=RNE_4(T)`; then `rne_jam P d 4` yields `RNE_4(T)=RNE_(d+4)(P)`.

Thus no general jam-composition theorem is needed. Do not try to instantiate the accepted theorem at final k=1: its interface permits only2/3/4.

The same15-root audit already includes `lowJam_ge(v,r):v≤lowJam v r` and `lowJam_lt_even(v,r,H)(v<H)(H%2=0):lowJam v r<H`. For q=P/D,r=P%D and H=2^27, these give `T<H iff q<H`, hence the leading-carry decision agrees with `P<H*D` when D>0. This avoids a new general threshold lemma. Applying these roots to the new typed runtime still remains uncompiled.

Paper machine bounds: both extended significands are at most2^27−8; right-jam never increases a positive integer beyond its unshifted value, so T≤2^28−16 and the extracted carry is0/1. After the optional jam-by1, the retained quantity is below2^27, so adding bias≤4 stays below2^32 and yields rounded mantissa≤2^24. With1≤e≤254, `(e−1)*2^23+m≤255*2^23<2^31`; this includes the second carry into infinity without overflowing the word or touching its sign. These are paper inequalities, not new Lean theorems.

Remaining interfaces before public correctness: UInt32 masks/shifts are the Nat jam with no wrap; T<2^28 and carry0/1; bias3+quotient-parity realizes RNE_3; significand range/possible rounded carry; exact direct-overflow behavior; add-based exponent packing; d>=25 same-sign absorption; signed normal Model.add bridge and Binary32 payload-safe fallback. These remain NOT_PROVED for this runtime. Stop at this map while full guarded machine cost is unknown; no larger proof or CI requested.
