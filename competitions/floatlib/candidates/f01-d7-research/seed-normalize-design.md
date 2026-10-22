# Product seed normalization: minimal statement probe

The append-only probe is frozen at SHA-256 a1325da56ec17cbc73f83acc3fe8b4e9ea0b2edd379617b7b927514513249f4c (185720 bytes). Its first 174925 bytes equal the exact [97f direct/nonfinite parent](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-direct-nonfinite/Kernel.lean). The added block is 10793 bytes, SHA-256 c44c4afbbe117e97b857ac3541638f3cbee370ba86f837fc76be16c41d08ed26. The earlier 84c5/0903 preview is superseded solely by an explicit binary32 argument in the classifier proof; runtime code and bridge signatures did not change.

This is mathematical preparation. No original add/mul/sum/bmm definition changes; the one appended runtime helper is unused by all four exports. New Lean elaboration, replay, transitive axiom audit, generated C, current-suite checksums, full gate and performance are NOT_RUN/UNKNOWN. The original supplied W10/W10b successes do not certify this port.

## Exact runtime and theorem boundary

The normalizer copies W10b Core's declaration/body exactly, changing only its enclosing namespace. It selects a UInt32 first: raw negative zero selects literal 0, every other word selects its original raw value; ExecFloat.ofRaw wraps that selected word. The older full-carrier normalizer and its positive-zero once branch are absent from the new runtime helper. This is a source equality check, not a new codegen observation.

The concrete entry point for a later singleton integration is:

```lean
theorem D7SeedNormalize.normalize_submission_mul_eq_add
    (x y : Competition.Binary32) :
    D7SeedNormalize.normalizeProductSeedRaw (Submission.mul x y) =
      Submission.add Competition.posZero (Submission.mul x y)
```

The block also states actual ExecFloat full-carrier equality and explicit 32-bit conditional results. The general +0 add q identity keeps Model.isSNaN (ExecFloat.Binary.toModel q) = false. The product theorem has no input premise: it derives that fact from the base's existing actual multiply classification and actual carrier/model refinement.

Only negative-zero product becomes positive zero. All other complete product words, including quiet NaN sign/payload and invalid canonical NaN, remain unchanged. Multiplication still runs separately with its existing rounding and signaling-first NaN priority; this does not fuse operations or bypass its result semantics. The directed counterexample q=0xff800011 normalizes to itself, whereas +0 addition produces 0xffc00011. It prevents an invalid arbitrary-q rewrite.

## Small proof closure

Only model_toModel_isNaN and toFloat32_isNaN are copied from the W05 section embedded in supplied W10. Their widths are explicit BitVec 8/23; Model.toNat_neg_one_exponentBits is called with FloatFormat.binary32, matching its actual fixed-library signature at Model/Lean.lean:263.

The W10 NativeZero pack/unpack proof is retained. Its scoped Classical instance command is replaced by explicit proof-only @ite decisions in the two conditional theorem propositions, with classical inside those proofs. No new attribute, instance, options or dependency command is added. These explicit decisions still require actual elaboration; source inspection cannot certify them.

The nonNaN carrier bridge uses the base's Submission.R7Native.ofFloat32Add on native positive zero and toFloat32 q, plus Submission.NotNaNProbe.roundtrip. Native negative zero itself supplies the nonNaN premise for the negative-zero/raw bridge. Thus no complete W05 add homomorphism or extra output-roundtrip theorem is copied.

The quiet NaN branch uses existing R7W01.quietNaN32_eq_self and exec_toModel_add. The product classifier uses existing R7W01.mul32_not_snan and exec_toModel_mul. Final Submission corollaries use the original function equalities Submission.add_eq/mul_eq. All new proof text is NOT_RUN.

## Local checks

The deterministic builder's read-only --check passed. It binds parent/block/Core hashes, exact appended bytes, the one new runtime definition, original import, and the unchanged four-export prefix. It executes the unchanged fixed 4b7 gate policy/options AST bodies with the exact full-slot contract; no build, kernel, axioms or score stage is loaded. Result: PASS_STATIC_ONLY, gate source SHA-256 1eb74ef7479b0023c721e776cc5e4073af21c6662b4afffcf16a48a124d27194. Intake is below 256000 bytes.

The bounded --selftest passed 16 directed integer-model cases: signed zero, positive/negative underflow, min subnormal, 0*Inf invalid, signed Inf, quiet payload preservation, signaling/quiet and dual signaling priorities, and the arbitrary-sNaN counterexample. It loads only selected function ASTs from the frozen oracle; no oracle main or dependency install runs. Oracle SHA-256 3dfaeec2bde1364a4f06abd292f0ba265376da79e678d3827aa88bd33219ad72 was unchanged before/after. This finite Python model is neither Lean acceptance nor hardware/performance evidence.

## Sources and provenance

The following are LOCAL_ONLY original artifacts, recorded with full absolute paths and freshly rechecked hashes in seed-normalize-design.json. No private webpage prompt is reproduced.

| Original | SHA-256 | Used material |
| --- | --- | --- |
| R7-W10/R7W10.lean | c3f9965a7f4f55d13473e5364e95173a2a36b2c1e39bcb1f07f7dce2018432cc | W05 two classifiers, W10 proof context |
| R7-W10/proofs/NativeZero.lean | 004c968380cb23bc165dd1a4a05c8e0cf402187f75a3d41c6fca61695882d492 | Native zero proof, adapted Classical and roundtrip |
| R7-W10/proofs/General.lean | c6790e97e91474de559dc913f53c28f0bebccbeb3674fe93ee5bd94fcb5bbaaa | Quiet NaN/general non-sNaN proof |
| R7-W10b/Core.lean | 270c698a2dd2b96d21766d35339e090ca1455f71404145b3323cd1862301b67f | Exact runtime declaration/body |
| R7-W10b/Proofs.lean | 90a6e0461690f8220d7ecc1710d52a267eb6239ec18d50de9f164952eff6bcbd | Raw/extensional product identity |
| Fixed Model/Lean.lean | 24b1b98f7a24ce6e3c69f6c9278bfd9fe36d4a138a8231574edd620111dd6b48 | Actual classifier and width theorem API |

Fixed context: FloatLib 0d91825727839f597fd06b22fdd038ea21480f0c; Lean v4.34.0, commit 293d5d0c0c3f3dded4688b3ccd6a33939ac5102b. Selected original ordinary compile records/logs were rehashed against the preceding source review. They establish only their own supplied source executions, not this new ContractTensor-only proof port. Source notices and attribution in the parent remain intact.

## First falsification and later integration

The next useful test is an actual statement build of the exact a1325da5 probe under the unchanged current gate. First inspect any concrete target in the explicit BitVec/fmt rewrite, @ite decisions, native negative-zero bridge, and ofFloat32Add/roundtrip route. These are uncompiled adaptation surfaces, not known errors. Audit this exact theorem closure's transitive axioms and kernel replay before relying on it.

After that acceptance, D can separately replace only a singleton's initial +0 add by this normalizer on the same single computed product, closing the old pointwise proof with normalize_submission_mul_eq_add. Preserve the bmmDecodeC/getD addresses, empty-output behavior and every n!=1 path. This task does not create that runtime integration. Its actual codegen, complete current-suite timings and frozen independent confirmation remain separate future tests; no benefit is claimed here.

Builder SHA-256: 135e8e429d8bd484fe4ec364d83947bfe9ccefeb1f8d6a39771717860f9cdf69. Local work began 2026-10-22 23:04:29 UTC within a 60-minute bound. All source snapshots and negative evidence remain unchanged; no Git, CI, upload or local Lean/Linux toolchain operation was performed.
