# R25 tiny sparse: native feedback and proof interface preaudit

Candidate `r25-astra-tiny-pc-sparse`, Rust `84ccbcbe88c56d8459c6df0d8bad5391b0ce95209d4e2f5fb4148369c9c294e5`; current copied Lean `3bd53694534c0114453a95c2f120d743fde3af233de88c00e1d5c30fe05ccdb8` is DRAFT for this Rust. This is a read-only preaudit, not a proof migration or gate claim.

## Source expectation versus M native

**VERIFIED:** original encoder run38132623194, raw receipt `quality-m-native/diagnostics/r13-encoder/encoder.json`, SHA `4cefa4e7b067ec134da1f00e27591a61d865c7a26ec5f21145aa99a1efda801e`. All28 input hashes match; all27 files outside tiny-config have both token SHA and encoded-output SHA identical between combo, I and sparse. The unchanged-route prediction therefore holds on the actual public corpus, beyond merely matching byte counts. Full per-file comparisons are in `tiny-sparse-native-feedback.json`.

| Quantity | combo | I tinyPC | fixed sparse |
|---|---:|---:|---:|
| tiny-config encoded bytes | 2487 | 2155 | 2441 |
| tiny-config tokens | 3094 | 2276 | 2954 |
| Total encoded bytes | 5332621 | 5332289 | 5332575 |
| Public balanced size percentage | 36.15990926474319 | 36.06109974093367 | 36.146218788552716 |

Sparse keeps46B, or13.8554% of I's332B quality gain, and140/818 of its token reduction. Compared with I, it adds286B and678 tokens. This is the actual aggregate cost of this fixed emission intervention, including its interaction with existing backward folding. It does **not** assign286B to a particular length, distance or individual rejected match, and does not prove that the matcher itself has only46B of latent value.

**INFERRED:** source limits emitted match length codes to the inherited five; the complete-end invariant preserves forward match positions despite possibly different backward token folding. No new trace has measured sparse's live distance symbols, lookup iterations or tree work. No claim that its distance tree returned to combo's7 symbols is justified. **UNKNOWN:** paired total time, current competitive share and complete gate acceptance. The native result gives a positive quality margin, so the planned original-protocol timing is informative even though most of I's byte gain was lost. No mask or distance variant has been added.

## Reusable verified interfaces

All locations refer to frozen `candidates/r25-astra-tiny-pc8-proof1/Parse.lean`, accepted by original gate38130996700 for I's distinct Rust.

- `Q4.LensBound` and `Q4.LensBound.init` (line1767 onward) describe bounded entries of the fixed260-element length array. `Q4.e_lens_spec` (line1826) preserves this bound through mask initialization; correctness needs bounds, not a theorem about the exact five selected codes.
- `Q4.e_pieces_spec` (line1936) consumes decoded prefix, full-match equality and distance/bounds assumptions, then returns decoded output, output-array length preservation and exact end `p+l`. Its internal termination proof already covers literal remainder and a span shorter than the first allowed match length.
- `PC.MatchAt` (line5348) contains precisely the length, end, distance and `LZ77.Matches` facts needed for that emitter. `PC.fold_w_spec` (line5462) returns a valid folded `MatchAt`, decoded prefix and equality of folded/new end with the original `p+l`.
- `PC.MainInv1` (line5742) only requires decoded prefix, array-length preservation and dictionary/prefetch bounds. It does not require that a successful iteration emits exactly one token. The old `put_match_spec` does expose `nt+1`; that postcondition must **not** be copied into the new emitter wrapper.

`PC.Dec` (line5378) and `Q4.Dec` (line1328) have identical explicit definitions. A small PC-local wrapper around `Q4.e_pieces_spec`, translating with `simpa only [PC.Dec, Q4.Dec]` and unpacking `PC.MatchAt`, should provide a local step rule with exact-end, array-length and `PC.Dec` postconditions. This avoids importing Q4's separate matcher/head invariants into the PC loop. The wrapper is a design, not yet checked Lean code.

## Expected minimal migration after real extraction

1. Confirm the only extracted changes from I are the run wrapper plus main-loop/body definitions with an immutable lens parameter; lazy and literal-tail loop definitions should remain unchanged. Exact names, argument order and tuple layout remain **UNKNOWN until fresh Funs**. There are no new Rust loops or helper functions, so large extraction growth is not expected, but this is not a measured extraction claim.
2. Add the PC-local sparse-emitter step wrapper above. Register `Q4.e_lens_spec` locally where the run proof needs it. Prove the zero lens initializer using `Q4.LensBound.init`.
3. Adapt `tiny_main1_loop_spec` and its step wrapper (line6040 onward) by adding the actual lens argument and `Q4.LensBound lens` hypothesis. The existing fuel measure and `PC.MainInv1` should stay unchanged. Reuse the source's unchanged `ahead_fix`; exact full-end allows the existing prefetch/dictionary bounds to close.
4. Replace `tiny_run1_spec`'s `C125102!` shorthand with its local explicit body plus lens-bound initialization, as in the already-verified Q4 sparse run proof. The frozen shared macro and all unrelated proofs remain untouched. Retain the original row12 theorem call and final parse obligation.
5. Preserve record8, lazy and tail proofs if real extraction confirms their interfaces unchanged. No new axiom, admitted goal or global timeout increase is proposed.

The likely changes are one bridge lemma and the three existing tiny main/run lemmas. The main remaining risks are elaboration of the extra loop argument, local step-rule selection across namespaces, and any prior tactic that accidentally relied on `nt+1` rather than the stronger decode-prefix invariant. These require a real extraction and original Lean execution; static source similarity and I's old gate do not settle them.

The source and Lean are within524288B (365435B /410352B); the expected small adapter fits comfortably, but the final exact file sizes must still be checked. Root is collecting actual extraction only as preparation. No full proof work or gate is started here before a useful total-time tradeoff is established.

## Later actual extraction and authorized draft

**VERIFIED, run38132862529:** comparison of actual I/M Funs finds1427 definitions in each, no additions/deletions, and only `r25_tiny_pc_run1`, its main loop and main-loop body changed. Lens is captured immediately after `km`, before `nt` in the loop and before `lim` in the body; it is not part of the mutable loop-state tuple. All1424 other definitions, including record8, lazy and literal-tail loops, remain equal after removal of source-location comments. The actual Funs SHA is `c658d0bab6cf28202a8fb5d9f251b98b4596af8e9175181cf24dc03eb8c5228b`.

At root's separate instruction, `scripts/build-round25-astra-sparse-proof.py` generated `candidates/r25-astra-tiny-pc-sparse-proof1`. Rust remains byte-identical to M (`84ccbcbe88c56d8459c6df0d8bad5391b0ce95209d4e2f5fb4148369c9c294e5`,365435B). Lean is `36cb54917d6d5b7a850a54d39d61c301342e40205fa2f73eb69ec5933e963663`,411750B. The draft adds the PC emitter bridge, adapts only the two main-loop lemmas and run lemma, and retains every option directive and the entire final bulk_parse/parse proof tail. The native candidate and accepted I proof were not edited. Audit and dispatch entry: `tiny-sparse-proof-build-audit.json` and `tiny-sparse-proof-entry.json`.

**UNKNOWN:** Lean elaboration, axiom scan and the new full gate. This is a reviewable uncompiled draft, prepared against actual interfaces; timing still determines whether root spends the full-gate budget.

## Offline replay counterexample retained

Root's `evidence/round25/sparse-offline-replay.json` reconstructs the same input from I's fixed final tokens and applies the same allowed-length splitting only after parsing. Its3010-token output decodes validly but differs from actual M's2954 tokens (`e8aa1ec3…` versus `d0da4eed…`). Thus final-token rewriting is concretely not the M parser. Interactions with later backward folding must remain in the actual native execution; offline emission results cannot substitute for that execution. The I final stream contains125 of210 matches shorter than11, making the short-match loss risk concrete, without quantifying their individual compressed-byte contribution or licensing an added mask variant.
