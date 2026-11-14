# A-only inline decoding: tested history and the new F8 discriminator

Started **2026-10-27 22:18:35 UTC**, bounded to **22:33:35 UTC**. Current D runtime is read only; no candidate, CI or local Lean. New proof-only fragment: `DecoderNormalization.lean.inc`.

**The A-only idea has already reached a complete measured implementation.** The R19 direction note points to the earlier f65 component, but its later f84 continuation must also be considered. `history-binding.json` freshly binds exact local/archived input bytes, three original full-gate verdicts and the old selected ASM. The ASM was archived out of the worktree; its exact bytes were read in memory from the documented Git blob and matched `a764e2c6`. No original evidence path or Git state was changed.

| Source | Exact scope and observed state | Interpretation for new F8 |
|---|---|---|
| f65e4aa5, 209479 B | R14ThinBCache single accumulator, Nat/getD, Array Float32 B cache; only A decoding changes. Frozen as COMPONENT_PROTOTYPE_NOT_SELECTED_STANDALONE; no standalone full test in checked R15 freeze/receipts. | Not a measured F8 implementation. It is an existing prototype, not a new mechanism. |
| cb7f1099 | Includes the same f65 B1 conversion, expanded short-n eligibility and scalar MUL cutoff84. Full 25-round run40165220696 failed the adoption screen (whole0.98042/BMM0.85627 vsDF, p05<0). | The combined result does not isolate A decoding or compare against current B2. |
| d5e3512f, 235524 B | R9 changes both operands in the single-output direct Nat dotLoop; packed path unchanged. Original run39961709177 full25 gate passed; reported BMM1.173127/whole1.040345 versus old41. | Strong negative evidence against retrying the same two-sided direct decoder; not a test of four-row F8 with packed B. |
| **f84ea2db, 234290 B** | Only A conversion changes relative to indexed/USize B2 parent9f7. 40404258098 statement/replay/15 roots and selected decoder mechanism pass. **40407333869 / seed1927005 full25 gate passed, whole0.995854643, BMM0.966864998, p05−0.006708170; no adoption.** | The call/spill removal mechanism was real yet did not meet the whole-package screen. This later evidence supersedes the old draft's NOT_RUN wording for exact f84. |

F84's full comparison is against retained B2 `622d`, not an isolated same-run f84-versus9f7 decoder pair. Its complete implementation includes the indexed parent route, so do not attribute the whole/BMM ratio solely to conversion. The same mathematical converter's effect in a new F8 context remains unknown; the negative adoption result is not erased.

## What the old machine evidence actually established

Fixed Lean header `982c731a` declares `lean_float32_of_bits` as LEAN_EXPORT, and UInt32-to-Float32 as static inline C cast. The f84 selected statement `Indexed.wordLoop___redArg` uses the actual public BMM call graph. The eligible loop path (0x40..0xb2) has **30 instructions, zero calls, zero rsp references**, freshly checked from original bytes. Old9f7's recorded loop had an ofBits call and vector saves/reloads; f84 domain failures still call ofBits and save/reload the accumulator. This was a diagnostic object, not the new F8 timed binary.

The accepted mathematical converter includes ±0 and biased exponent24..254; nonzero subnormals, exponent1..23, Inf and NaN retain original ofBits fallback. It adds eligibility tests, a mantissa mask/or, a UInt32 numeric cast, a shared-table lookup, and an exact Float32 scale multiplication. These costs remain even when calls disappear. The compiler can keep spills at a shared merge point, so an inline branch alone does not prove their removal.

## The only justified changed condition

D's intended new structure has four A values feeding eight ordered accumulators with packed F2 B inputs and no A panel. That changes the live-value and sharing context relative to old single-output f65/R9 and two-lane f84. It does **not** change conversion mathematics, accepted input range, fallback, or table cost.

Whether all eight accumulators are actually live across an A conversion call must be established from the exact generated caller. If A decoding occurs outside a per-column Cell loop, the state may still reside in Cells while only earlier A temporaries span later calls; calling it “eight accumulator spills” would be false. Conversely a direct F8 dot loop may carry two SIMD vectors and decoded operands across those calls. Current new F8 source/selected machine route was not available in this bounded check, so that distinction remains **UNKNOWN**.

## Minimal actual-C/ASM discriminator

1. Bind exact F8 input/manifest to generated source and the **actual timed callback selected by Main/Bench.Suite.run**. Follow its chosen BMM/shape route to the concrete F8 loop. Do not substitute an exported helper or generic wrapper.
2. Compare same F8 layout with original A ofBits versus A-only convert. Preserve B preparation, F2 packet reads, state layout, scalar functions, shape/fallback, raw inputs for NaN replay and all eight separate mul/add chains. No A map/panel, hidden preprocessing or change to `-ffp-contract=off`.
3. Locate all four actual A raw reads and call sites relative to state loads. On the eligible path, inspect whether the decoder is inlined, the shared table is reused, and the path back to the loop head has calls, stack traffic, extra object/RC work, or Nat-index artifacts. Preserve and count the rejected branches and merge-point spills. A smaller number of C sites is not a dynamic count or speed measurement.
4. If the intended call removal does not occur, or the relevant shared spill remains without another demonstrated saving, retain the negative codegen result rather than paying for a full proof. If it occurs, the old f84 result shows that complete cost is still the decisive test.
5. Measure the complete same-F8 pair including eligibility/table/fallback/preparation/destruction/output. Then any candidate considered for adoption needs its exact full gate and fixed confirmation policy. Do not reseed old f84, infer new gain from its3.3% BMM discovery figure, or claim this source is already tested.

## Proof-only normalization

`DecoderNormalization.lean.inc` has four **NOT_RUN** roots: `carrier_decode`, `array_getD_decode`, `replace_four_A`, and `normalize_A4B2_step`. They reuse existing all-input `R2W01c.convert_eq`; there are no finite/nonNaN/domain hypotheses. The latter theorem leaves both packed B values, arbitrary state and update function untouched while replacing exactly four A decoder results.

For a concrete new loop proof, unfold its actual decoder-bearing step and normalize those four values before applying the old lane recurrence. Do not expect a `change` that contains native `toFloat32` to reduce a new `convert` expression by definition; rewrite `convert_eq` first. Raw A/B arrays and finish remain the original objects, so native NaN canonicalization is not mistaken for recovering arbitrary raw NaN payloads.

**Decision:** a new F8 caller can justify one targeted codegen/complete-cost discriminator because its actual live-state geometry may differ. It cannot justify claiming A-only conversion was previously untested. No new runtime or queue is created by this investigation.
