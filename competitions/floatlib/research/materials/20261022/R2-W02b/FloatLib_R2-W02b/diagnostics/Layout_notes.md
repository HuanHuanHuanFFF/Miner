# Layout module

Status: **NOT_RUN**. The supplied environment has no Lean or Lake executable. No compiler, kernel, or runtime result is claimed.

## Scope and integration

`Layout.lean` is a concatenation fragment. Insert it while the parent `Submission` namespace is open; its local `namespace Packed4` places declarations under `Submission.Packed4`. It imports nothing and preserves the parent's `FloatLib.Floats` and `Competition` opens.

The only cache layout is `Vector (Vector (Vector F4 n) (groups p)) batch`, logically indexed `[b][g][k]`. Each `F4` has four `Float32` fields. The dimensions are batch, groups of four output columns, and reduction length. `groups p` is `(p + 3) / 4`. The caller selects the batch and group before entering the reduction loop; the loop receives only its length-`n` packet stream.

Every stored packet uses a separate column guard for each lane. A valid column is converted from `B.toArray.getD ((b * n + k) * p + j) posZero`; a padded column stores `zero32`, defined as `Float32.ofBits 0`. No flattened cache, index clamping, or integer division occurs in the reduction-stream access.

## Interfaces

- `update (acc : F4) (a : Float32) (v : F4) : F4` applies `acc.si + a * v.si` separately to each field.
- `lane_packet (read : Nat → Float32) (col : Nat) (l : Fin 4)` states `lane (packet read col) l = read (col + l.val)`.
- `lane_zero4 (l : Fin 4)` and its alias `lane_zero` state `lane zero4 l = zero32`.
- `lane_update (acc : F4) (a : Float32) (v : F4) (l : Fin 4)` states `lane (update acc a v) l = lane acc l + a * lane v l`.
- `groups_pos_of_col (p j : Nat) (hj : j < p)` proves `j / 4 < groups p`.
- `column_decomposition (j : Nat)` proves `4 * (j / 4) + j % 4 = j`.
- `packB_lane` parameters are `(batch n p) B b g k l hcol`, in that order. The conclusion reads the original B address `((b.val * n + k.val) * p + (4 * g.val + l.val))`.

The pointwise packet theorems use finite case analysis and definitional equality. They do not use associativity, commutativity, or distributivity of floating-point operations. The two column-arithmetic facts use the existing `omega` tactic with the constant divisor four.

## Source checks

The checked public parent is `public/parent/Kernel.lean`, SHA-256 `86312a3759286cb207f946af9db95546777fdb16f1bd147f7892c0f9e1d79217`.

The fixed Lean 4.34.0 source provides `Vector.getElem_ofFn` in `public/lean/src__Init__Data__Vector__OfFn.lean`, lines 27–29. It states that indexing `Vector.ofFn f` at a bounded natural index gives `f` at the corresponding finite index. `Vector.get` and the natural-index `GetElem` instance are defined in `public/lean/src__Init__Data__Vector__Basic.lean`, lines 100–108. The module's `vector_get_ofFn` converts between these two access spellings by definitional equality and applies that checked theorem. `packB_get` then rewrites all three vector layers; `packB_lane` applies `lane_packet` and its explicit valid-column hypothesis.

Source inspection and text inspection are the available evidence. Lean elaboration, proof acceptance, and execution remain **NOT_RUN** and must be checked by the downstream official environment.
