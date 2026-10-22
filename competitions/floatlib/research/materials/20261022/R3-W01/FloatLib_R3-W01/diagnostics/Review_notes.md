# R3-W01 independent boundary review

Status: **NOT_RUN** for Lean elaboration, kernel replay, generated code and runtime measurements. No toolchain was installed or invoked. Review scope is the current request and the fixed public parent only.

## Public parent inspected

The parent at commit `9fa0c60d8d5589d58b3152202adac2df444ec5e2`, path `competitions/floatlib/candidates/f01-d2-web-packed4-proof1/Kernel.lean`, has the expected structure:

- `Packed4.tileResults` at lines 1559–1566 constructs exactly one `dot4` result per `b/i/g` with three `Vector.ofFn` layers.
- `tileResults_get` and `tile_finish` at lines 1568–1591 expose the selected block and connect it to the scalar parent dot.
- `outputFromTiles` at lines 1593–1605 retains the original `Binary32` A/B and calls `finish` after extracting the selected cached lane.
- `Packed4.core` at lines 1635–1641 maps A once, builds B packets once, constructs tiles once, then constructs the output.
- `Submission.bmm` at lines 1663–1667 sends empty output or `n = 0` to `referenceBmm` before calling the packed core.

Source: https://github.com/HuanHuanHuanFFF/Miner/blob/9fa0c60d8d5589d58b3152202adac2df444ec5e2/competitions/floatlib/candidates/f01-d2-web-packed4-proof1/Kernel.lean

## Required edge condition: an inhabited row

For any machine bound `W > 0`, choose `batch = 0`, `m = 1`, `n = W`. Then input length is zero, so `nativeA.size = 0 < W`, but `n < W` is false. The same issue occurs with `batch = 1`, `m = 0`.

Consequently the whole-call size check alone does not justify unconditionally converting an arbitrary shape's `n` to a word. A valid implementation derives the bound inside the body that has `b : Fin batch` and `i : Fin m`, or derives positive batch and row dimensions from the already established nonempty-output branch. Empty shapes must retain the reference branch. A ghost proof of an impossible row is not a runtime row that may be manufactured after truncation.

At `n = 0`, the proposed span condition becomes `baseA < A.size`, while the shape forces `A.size = 0` and every `baseA = 0`. The existing `n = 0` reference branch is therefore essential for this interface. The wrapper may take `0 < n` internally because the outer branch discharges it; it must not add that condition to the final public specification.

## Erasure and branch placement

The whole-call condition should appear exactly once as a computational `if hAS : nativeA.size < USize.size`. Its proof is passed to row/tile construction. The derived `hn`, `ha`, `hA`, and length equality are propositions, so Lean proof erasure removes their construction from the runtime computation. Their source proofs may mention shape multiplication and ordering without introducing runtime comparisons.

The new tile builder should have no computational `if`, `decide`, or new checked `runDot` call. Each leaf should call the provided `within` directly with its four evidence arguments. Proof theorems that contain case splits have no runtime role.

Keep `nativeA` and `packedB` in outer lets, then select the tile builder. Calling the whole original `core` on admission failure would be correct mathematically but may repeat conversions and packing; using the original `tileResults` on those same prepared buffers avoids that duplication.

## Two different fallback events

The global machine-size admission failure chooses the original Nat-indexed `Packed4.tileResults` / `dot4` on the prepared native buffers. Separately, a nonfinite final scalar result is handled by the original `finish`, which reads original `Binary32` A/B and performs the exact fold. These are not the same event and should not be described as a single raw-input fallback.

Keeping `outputFromTiles ... A B tiles` unchanged preserves the original raw-input path. No buffer-to-raw reconstruction is justified or needed.

## Minimal equality bridge

Prove the whole equality `tileResultsWithin ... = tileResults ...` under three `Vector.ofFn` congruences and `funext b`, `funext i`, `funext g`; the leaf goal is exactly the supplied `within_eq` interface. Then the block read and finished-lane bridges can rewrite this equality and invoke the unchanged `tileResults_get` and `tile_finish` respectively.

The same whole-tile equality lets the new core rewrite to the old core before using `core_eq_reference`. There is no need to reproduce `dot4_lane`, the numerical finite proof, `packB_lane`, or the final output index proof.

A source-level reduction in admission comparisons is not a measured speedup. The USize loop and its equivalence bridge are user-supplied work that this review did not execute or reimplement.

## Final review of the written WholeCall fragment

The actual `work/WholeCall.inc.lean` was subsequently read in full. No definite static blocker was found. This conclusion does not replace Lean elaboration.

- `tileResultsWithin` has exactly the parent's three nested `Vector.ofFn` layers. It constructs row evidence after obtaining `b : Fin batch` and `i : Fin m`, then directly calls `Submission.Packed4.within` once per `g`. It does not use a checked tile dispatcher or add a local computational branch.
- `tileResultsWithin_eq` uses the correct function domains and codomains for the three congruences: `Fin batch → Vector (Vector F4 (groups p)) m`, `Fin m → Vector F4 (groups p)`, and `Fin (groups p) → F4`. Reducing the row-local let leaves the supplied `within_eq` equality as the leaf goal. This depends on the actual supplied bridge having the stated signature and direction.
- `tileResultsWithin_get`, `tileResultsWithin_lane`, and `tileResultsWithin_finish` rewrite the whole block equality or its read corollary. Their old-side terms match the actual public parent's accessor and finished-lane theorem parameters and address expressions.
- `selectTiles` contains the only new computational admission condition, `A.size < USize.size`. Its false branch calls the parent's `tileResults` with the same A/B prepared buffers. Its equality theorem uses branch elimination solely in a proof.
- `coreOnce` contains one A map, one B packing call, and one selected tile builder call. It passes the original A/B to the unchanged `outputFromTiles`; no new dot is called during output selection. Its length evidence is the concrete `MatrixBounds.nativeA_size` theorem.
- `coreOnce_eq_core` unfolds only the two core definitions, reduces their lets, and rewrites `selectTiles_eq`. The remaining terms are the same parent's output construction.
- `bmmOnce` preserves both original reference branches. Its positive-n evidence is constructed only in the `n ≠ 0` branch. The equality proof treats ordinary and dependent if reductions, and uses `coreOnce_eq_core` only in the final branch.
- `bmmOnce_spec` has exactly the original dimensions and input-vector parameters. It rewrites `bmmOnce_eq` and invokes the parent's `bmm_spec`; there is no final positive-size or machine-bound premise.

The fragment names the supplied implementation and bridge only at the direct leaf call and the corresponding theorem application. Those two qualified names need alignment if the developer's actual declarations live in a different namespace. The fragment does not define a replacement word loop or supply an unproved stand-in.

The fragment deliberately defines the alternate `bmmOnce` and its unconditional specification without rewriting the public parent's existing `bmm`. Integrating it as the chosen entry is a developer-side wiring step; this review does not claim that the old entry already invokes the new path.
