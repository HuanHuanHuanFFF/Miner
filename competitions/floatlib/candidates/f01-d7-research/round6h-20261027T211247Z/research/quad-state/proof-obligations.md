# Exact four-lane refinement boundary

The proof fragment is tied to D's `e4bf6126` runtime. It is **NOT_RUN**. A performed one independent static interface review of the lane/address/order and finish hypotheses; no new gap was found. Further broad review is unnecessary unless the runtime changes, Lean reports an error, or new evidence exposes a risk.

`advance_get` is the representation obligation: `Array.mapIdx` at j reads the old Cell at j and writes the four explicit multiply/add results. B uses `baseB+k*p+j`; the original dot uses `baseB+j+k*p`. These Nat addresses are equal without any array-bound assumption. Out-of-range input accesses remain the same `getD` calls with `posZero`.

The four field projections expose separate recurrences. Lane i has A base `baseA+i*n`, B base `baseB+j`, B stride p, and current accumulator equal to the corresponding Cell field. The runtime shares a loaded B value across lanes but never combines or reassociates the four arithmetic chains.

`loop_eq_storage` matches the actual recursive function to the existing generic `storageLoop`. This is an all-k statement: when k≥n both recurrences immediately return the input state; when k<n each performs exactly one advance and recurs at k+1. The measure n-k decreases only in the latter branch.

`loop_view0` through `loop_view3` then instantiate `storageLoop_lane` with those *actual* field views. Their conclusions are equalities to the original `NativeFinal.dotLoop`, not an idealized real-number dot product. No commutativity, associativity, tolerance, or alternate accumulation order is used.

`initial_view*` retains explicit positive zero. `finish*` invokes `Packed10.finish_eq_dot` with the same raw A/B arrays, bases, stride and final native result. That retains the original replay behavior for NaN results and its raw bit semantics. Omitting the initial +0 is a distinct transformation and is not licensed by this proof; the old R21 first-sweep proposal kept it for precisely this reason.

`rows4_eq_control` eliminates only the four-lane state implementation. The RHS is the four original dot-row writers, in row0/row1/row2/row3 order, appended to the existing output. For p=0 both sides return that output; no loop state is demanded by this theorem. n=0 is covered by the general loop equations and the original finish.

Batch indices, group partitioning, 0..3 leftover rows, output prefix/size, public guarded dispatch, and the B2 fallback are A/D obligations. The scalar lane fragment neither assumes nor proves them. A's `quad-bridge-manifest.json` separately records that transport and the proposed source-capacity reduction.

The next valid state change is a source-bound pinned compile/replay/audit result, a changed D runtime requiring a new fragment hash, or the complete-call cost decision. The bounded symbolic schedule check does not substitute for any of those.
