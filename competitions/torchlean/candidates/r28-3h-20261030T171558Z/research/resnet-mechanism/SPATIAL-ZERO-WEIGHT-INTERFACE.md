# Zero-weight follow-on domain, no frozen source change

The current8e5b27c0 source deliberately retains the conservative nonzero-weight guard requested for the first cost prototype. The following is a mathematical/source interface for a later version, not a claim that the current source covers sparse cells and not a second CI request.

For a mixed row, existingYbg excludes nonfinite used weights and bounds the exponents of every nonzero weight; zero mantissas contribute exact aligned integer0. YW2 encodes either sign of floating zero as0x80000000, so the transformed row'szero terms are ordinary integerzeros. The transform/range arguments already permit them. Raw signs must still be retained through oldzW if the final numerator iszero.

For an entirely zero row, BW.min=511. ExistingYG returns`126+idx(bias)−xm`; existingYbg requires`xm≤126+idx(bias)`, so there is no unsigned underflow in that admitted case. ThereforeB0=xm+YG=126+idx(bias), regardless of the nominal weight scale. All decoded/transformed weights arezero, and all products/partial sums arezero. RebasedB0−2 remains≥124; a nonzero bias'snew shift is exactly2, hence safely within78. The result is the original bias with the original full zero-product sign rule, not an unconditional+0.

This does not admit0×Infinity: original input finite guards remain. It also does not justify skipping a NaN bias, extending beyond the original numerical guard, or treating all-zero raw weights as positivezero. For entirely zero input, the original narrow guard may fail; preserve that fallback rather than infer a new fast branch.

The current old-seed finite interpreter'sweight scale currently assumes a nonzero row because itsmatching guard rejectszero weights. A future extension must implement theactualYG zero-row branch above, use same raw signed-zero provenance, and separately freeze new source/hash/verification. Source11's old3×3 direct loop has no weight-support filter; the earlier18-product ideal baseline is not applicable to its runtime, as recorded inSPATIAL-SPARSE-COST-SCOPE.md.
