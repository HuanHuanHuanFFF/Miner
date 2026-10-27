# R19 BMM structure: first discrimination

Baseline is exact B2 `622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58`, verified from the current file. R19 owns this directory only; D owns Git and CI. No local Lean, new CI, holdout access, or nested agents.

The first concrete decision is to avoid an independent B2 USize implementation: D's `development-workers/structural-cost/indexed-b2.lean.inc` already addresses it. Its opportunity is real: the selected B2 C still contains Nat increment/address arithmetic and raw-A bounds checks. This fact does not establish elapsed cost.

The substantial route is **temporal B2 packing**. Four consecutive k positions, each with two B columns, become one record with eight native Float32 fields. The two output accumulation chains retain their exact order. The last zero to three k positions execute individually; no padding MAC is allowed. There is no A panel or result-tile cache. All B preparation, odd-column decoding, output import, NaN replay and destruction remain inside the complete call.

This continues the R18 uncompiled temporal core, which was parked without a full-entry measurement. The new milestone is an actual full-entry candidate and original bmm obligation, not another finite address model. First falsification: compile and audit the exact complete source, verify the selected C prepares one record per four k and still calls the intended BMM, then measure the whole call against B2. If it cannot reduce actual complete cost, keep the negative source and stop this implementation. No unseen confirmation data will inform its development.

Evidence checked before implementation:

- R15 exact B2 diagnostic `round3h-20261025T043928Z/astra-workers/matrix-structure/handoff-b2-C-audit-401680.md`: preparation is once per call but uses outer Array.ofFn plus one inner closure/array per tile; each k allocates one 8-byte-field F2 record. The numeric loop has one packet read, raw A decode, and final F2 object. The current output helper performs finish and push only, not a repeated dot computation.
- R16 `matrix-architecture/cost-review-401854.md`: A4B2's core transformation really happened; new panels/cache/closures cost `32n+160−16G` additional major requested bytes per four rows versus B2 under its explicit allocation model. Full discovery was whole 1.00785021 / BMM 1.04343738, so this is not revived as a no-inline fix.
- R18 `structural-frontier/TemporalCore.lean` and `OrderedBlocks.lean`: actual but uncompiled k-block core/proof starting points. The old source is not a complete candidate and supplies no elapsed-cost evidence.
- Exact Lean 4.34 FloatArray source and old full-gated `f01-d2-checked-floatarray`: FloatArray stores Float64, not Float32. Cross-width functions remain opaque; the existing legal storage route requires real per-input raw-word checks. It is not a free contiguous-storage replacement.
- Old n=1 cache and packed-width negative results remain valid for their exact scopes. They neither establish nor bound the broader temporal layout.

Conditional 64-bit runtime request accounting: four B2 objects plus four pointer slots request 96 bytes; one B2K4 object plus one slot requests 48 bytes. For full blocks this cuts packet allocations by four and pointer reads by four. This is a source/runtime layout model, **not allocator, RSS or time measurement**. A decoding, arithmetic and output import are unchanged. New packet preparation/control and tail handling can offset the savings.

Coverage begins with the exact retained B2 domain `2≤p≤8, n>1, m≥4`; it may later extend to other widths only with a new complete implementation and evidence. It is not claimed to reach 10% whole. Old completed R15 BMM whole shares were 16.14/20.02/19.06%; removing roughly half to three fifths of all BMM cost would be necessary for a 10% whole reduction, and this candidate does not touch all BMM. Current dynamic preparation/loop/output shares and the target-only time are UNKNOWN.

At first checkpoint: source provenance/call-path investigation VERIFIED; new Lean, helper audit, full gate and performance NOT_RUN. Tokens/cache UNKNOWN; CI occupancy 0. Next: full source plus exact lane/packing/writer proof, followed by D's chosen minimal real runner check.

## Deferred decoder interface screen after the checkpoint

No third source was created. Existing `R2W01c.convert_eq` makes an A-only inline table decoder legally reachable in the B2 loop, but this is not a new idea: `f01-r15-dev-shortn-inline-decode1` / `f65e4aa5...` already changes the cached-B loop's hot A decoder and was frozen as `COMPONENT_PROTOTYPE_NOT_SELECTED_STANDALONE`. No independent verdict for it was found in the bounded candidate/artifact lookup. R9 `d5e3512f...` changes both direct-dot operand decoders and had a full-gate negative result, BMM 1.17313 / whole 1.04035 versus 41; R13 `7086031b...` changes once-per-input wide-path preparation and was BMM 1.005952 / whole 1.003435 versus df5c. These results have distinct scopes, but both warn against assuming fewer foreign calls means lower cost. Only actual c70c code/cost evidence plus a concrete changed condition could justify revisiting the preserved R15 prototype, ideally coordinated with the runtime worker's compact-table investigation.
