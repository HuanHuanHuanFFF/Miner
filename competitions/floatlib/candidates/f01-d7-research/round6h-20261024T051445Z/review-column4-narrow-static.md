# Column4 narrow candidate static review

**Independent read-only review; no static blocker found in the requested scope.** The frozen candidate is 255,439 bytes, SHA-256 `da09fb59…30c38c4`, leaving 561 bytes under the 256,000-byte cap. I reconstructed the three assembly/dispatch/spec edits and 27 proof deletions from parent `df5c61a0…b27fb172` using the saved exact-inverse operations; the resulting bytes match the frozen Kernel exactly.

## Proof-prune audit

All 27 removed ranges are unchanged theorem bodies from the parent. Their recorded byte lengths and SHA-256 values match their exact pre-prune slices; ranges are pairwise non-overlapping and total 7,387 bytes. Every removed name is globally unique in the pre-prune declaration inventory, every body is a theorem with no attributes, comments, instances or declaration wrappers, and none has an attached leading doc comment. A scan of the complete final source finds no remaining references to any removed name. The F4 assets and writer were present in the pre-prune source and contain no reference to a removed theorem.

The 87-byte doc comment for `Submission.R7W05.repairDotStep_eq_original` remains byte-identical with its theorem. The theorem is not in the deletion set. All eight public declaration headers are byte-identical to the parent; none is deleted. The only deletion operations target theorem bodies. Parent `R11CrossRows`, `DirectContinuous`, `UnderflowZero`, and its final 1,039 bytes are exact byte matches in the candidate. The original p=2 Cross dispatcher prefix is also unchanged.

## New path

The dispatcher tests the existing p=2 Cross route first. The added branch requires `(p=3 ∨ p=4) ∧ 4<n ∧ n<USize.size ∧ A.toArray.size<USize.size`; all other shapes reach the prior `bmmBeforeR11Cross` route. Each selected row runs one four-lane dot and emits its valid p outputs through `RowStream.emit` into the existing Array-backed writer. A and B are prepared once outside the row fold. `Packed4Index.runDot` carries the same per-row USize/address/Array-size fast-path bounds as `Packed10Index.runDot`, with the original Nat dot fallback.

The F4 finalizer calls the existing `Packed10.finish` unchanged. That keeps the current nonNaN fast path and quiet-NaN raw replay; no old `isFinite`/full-replay finalizer was copied into the new route. The original eight API headers and proof chain remain in place.

## Evidence boundary

The 27-node dependency check is a textual source graph, not Lean elaboration. New Lean, full gate, actual C/assembly, runtime performance and formal submission are all still NOT_RUN/UNKNOWN. The 561-byte package margin is valid but tight. Details, exact byte ranges and hashes are in [review-column4-narrow-static.json](review-column4-narrow-static.json).
