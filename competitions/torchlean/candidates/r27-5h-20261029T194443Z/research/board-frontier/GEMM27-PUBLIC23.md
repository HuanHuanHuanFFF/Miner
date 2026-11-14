23:10 CURRENT: coverage-repaired **6fe5feb6…/252719B**, recipebuild_gemm27_on_public23_v2.py. Usespositivek>=1 (originalGsnneedsjustk>0), preservesk0/nonfinitegemmWithYn. Originalthreshold20 donorYa3missingclosure7496B exceeds3280Bspace andwouldskiptypical/boundary; originalCDFbelow remainshistoricalunselected, not a secondqueue. Fullgate/coststillpending.

# Public27 GEMM schedule on public23 stronger linear

23:05 UTC: `CI-REQUEST-GEMM27-PUBLIC23.json` ready. Exactcandidate **cdf2ca27…/252720B**,3280Bfree. Drootonly CI/Git. No local Lean/native.

- Base23 1010c074…→frozen proof-onlyaliasfc7b1e9e; donor27 f92ee2c9. New ten-declaration closure Yos/Yqs/Yoc/Gsn/Gcg/Ya3Q/Xg/Fw/Zg2/Zc0Q. Newruntime onlyYa3Q; originalruntimeonlykernels.gemm binding changed.
- Shared Yo/Yq/Zy/Yn/Zi/Z5 are byte-identical inboth originalsources. ZcC23 has exactlysame `YaV=linearSpec` interface as27, but provesactualstrong23YaV. Allusedrenamingaliasesmatch exceptmissingCQ, replacedwithfullNat.pos_of_mul_pos_right.
- Fallback uses `gemmWith Yn` and existingZi, avoiding directgenericdotSpec; donorfirstbranchproof becomes simp[gemmSpec,Zi]. Actual kernels.dense.gemm and finalall12correct now useZc0Q. **NOT_COMPILED**, no proofinheritanceclaim; exact originalall12gate required.
- WholeMixercost necessary: #23 stillgenericaddRelu while27 hasnativeYbf; k<20fallbackdiffersfrom27Ya3. Include preparation, Btranspose, Aslices, nestedresultarrays and bothresidualadds. Dense1764Bversus683B isnot speed evidence.
- CurrenttargetMixer36; public27 onlycalibration. Existingreportfactor.9622181669992014 givesconditionalpointplanningline.9333516219892253, not directcurrentmeasurement orguarantee.

RecipeacceptsDsource27materializedpathunderTORCHLEAN_ROOT; no ownnetworkfetch. Wholethirdpartymergedsource onlyprivate/ephemeral; publishownedrecipe/receipts.
