# Exact-product relaxation: no available cheap native FMA bridge found

After the prefix-exact lattice screen, there is a distinct paper relaxation: if each original product is already exactly representable, fusing that multiplication with the following add would preserve that original add's rounding point even when prefixes need rounding. This does not permit arbitrary reassociation or dropping product rounding without the exact-product premise.

The first implementation prerequisite fails in the inspected fixed interfaces. Fresh search of pinned Lean4.34 `Float32.lean` (saved `profile-scalar-wide-lean-Float32.lean`,SHA2f4b7eb8…) and the exact runtime header293d5d0c/982c731a finds no Float32 FMA/fused-multiply-add primitive. The actual cost3 compile command explicitly has `-ffp-contract=off`; changing that compiler setting or adding an extern is outside the candidate surface. FloatLib's generic/word fused arithmetic is not evidence of a cheap native FMA API or performance.

This is a scoped API/source prerequisite result, not a proof that every future library interface is impossible. No new candidate, library modification, FMA benchmark, coefficient-coverage scan or proof was made. Keep this branch parked until an existing permitted native operation with an auditable semantic bridge is identified under the fixed contract.
