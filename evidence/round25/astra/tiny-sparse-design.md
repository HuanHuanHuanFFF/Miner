# Tiny-PC fixed sparse emission isolation

## Predeclaration

2026-10-11, after K2 and before candidate native execution. One candidate, `r25-astra-tiny-pc-sparse`, derived from exact I Rust `5c20b99cf52ac8e2f047b4e2e83be974b1f9b1f21b23d54ccccb25c58b891f00`. No mask or search parameter sweep is proposed.

**VERIFIED:** K2 receipt `evidence/round25/38132193695/counts-k2-native/diagnostics/r25-tiny-encoder/receipt.json` passed frozen token/history identity, original versus observer byte equality, independent zlib decode and unchanged tiny-app control. Both tiny-config streams choose one dynamic block, so a block-type change does not explain their difference.

| Tiny-config quantity | combo ETINY | I tinyPC |
|---|---:|---:|
| Encoded bytes | 2487 | 2155 |
| Tokens / matches | 3094 / 89 | 2276 / 210 |
| Live literal / length / distance symbols | 78 / 5 / 7 | 78 / 27 / 23 |
| LL logical symbol-vector clone calls | 3426 | 4328 |
| Distance logical clone calls | 265 | 923 |
| CL logical clone calls | 251 | 215 |
| Length plus distance lookup comparisons | 1891 | 7114 |
| Dynamic / fixed candidate bits | 19894 / 26105 | 17233 / 20685 |

The unchanged control has identical token/output hashes and all tree, block and lookup fields. These counts support broader alphabets and extra match lookups as actual new work. **UNKNOWN:** their elapsed-time contribution, allocator impact and recoverable total time. The CL tree is cheaper in I; no claim that every tree became more expensive is warranted. Distance contributes 658 additional logical clones versus LL's 902, so a length-only intervention may recover only part of the increment.

## One mechanism

Only `r25_tiny_pc_run1` changes. Initialize `lens=[0u16;260]` via inherited `q4_e_lens(...,302256384)`, then replace its existing `pc_put_match(input,out,b.0,b.1,d,b.2)` call with `q4_e_pieces(input,out,b.0,b.1,b.2,d,&lens)`. The mask is exactly the existing ETINY value: code indices 8,12,18,25,28, allowing lengths 11–12,19–22,51–58,163–194,258.

Routing, H32768, skip6, lazy16, probes, lazy gain, head operations, record8, prefetch/ahead_fix and backward fold are unchanged. The source attribution inherited from I remains present. No source from a new submission is introduced.

`q4_e_pieces` greedily emits an allowed piece when at least3 bytes are available, then emits any remainder as literals. For a valid match it returns the complete end `b.1+b.2`, equal to the prefetched `e=p+l` under the inherited fold invariant. A match shorter than11 becomes literals yet still consumes its whole span, so it cannot stall. Existing `ahead_fix` remains as-is; the caller uses returned `nt` and does not assume one emitted token. Changed earlier tokens can affect how many prior tokens fold consumes, which is part of the emission intervention. The dictionary/search control flow is intended to retain the same full-span positions; this statement is based on source/proof invariants, not a new measured trace claim.

## Risk, minimum test and stopping rule

**INFERRED:** the emitted length alphabet is bounded to the same5 codes, but some or all332B of I's quality advantage may come from the now-disallowed short matches. Greedy fragmentation may add literals or tokens. Literal alphabet and distance alphabet may change as a consequence of emission; there is no explicit distance filter. Table initialization and extra emission work add parser cost.

Root runs the existing original-encoder native harness on all28 inputs against frozen combo and I, retaining exact input/token/output hashes and decode. This gives the actual new trajectory and bytes; no finite Python emitter model can replace it. Only tiny-config should differ, since only the already-isolated row12 local function changes. Any other changed file requires route/source audit before promotion.

If output quality is no better than combo and therefore yields no useful quality margin, stop this exact isolation without a full proof/time gate. If meaningful quality survives, root can allocate paired original-protocol timing to decide the actual tradeoff. No automatic full proof, extra mask, distance gate or composition follows this experiment. Timing counts alone do not establish speedup or share.

## Proof interface

Copy exact gate-passed proof1 Lean `3bd53694534c0114453a95c2f120d743fde3af233de88c00e1d5c30fe05ccdb8` as a **DRAFT**. Its old local run proof is not valid for this changed Rust until adapted and rechecked. Parent `Q4.e_lens_spec` provides `LensBound`; `Q4.e_pieces_spec` consumes valid full-match hypotheses and returns `Dec`, output-size preservation and the complete end. New actual extraction must determine the extra lens argument in main-loop interfaces. Record8 and lazy/tail loops should remain reusable. The row12 final obligation and all original axiom restrictions remain unchanged. No proof acceptance is claimed for this candidate.
