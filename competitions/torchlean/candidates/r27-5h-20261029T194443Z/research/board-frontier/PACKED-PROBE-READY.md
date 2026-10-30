# Concrete packed native probe — 20:55 UTC

The earlier instruction to append3085B to the255647B predecessor would exceed the original intake cap. This is now resolved **for a native diagnostic only**, without changing the official gate, benchmark or runtime flags.

`build_packed_probe.py` takes exact private source27 (SHA f92ee2c9…), deletes `correct` and then recursively removes plain lemma/theorem declarations whose names have no other lexical occurrence, while verifying all160 existing runtime declaration bodies remain byte-identical. Directly named bound/termination dependencies remain; native Lean compilation must still check dependency completeness, including any name resolution a lexical scan does not establish. The new file has **no Submission.correct**. It appends the self-authored packed runtime and the exact two-channel-linear binding. Whole reconstructed source remains private.

- Packed source:63760B / `e07d5ab39ec725b7d2fc22b8cd262d9f2a6c076afe4eaf1a62345ce5ac9fcea7`.
- Owned builder: `build_packed_probe.py`, SHA `4938fa3d3981d70207074fd5507e35701f809d502183ce6dfa9875eaa835cf63`; dependencies `PackedLinearRuntime.lean` SHA2a416a23… and `PackedBinding.lean.inc` (full hashes in `packed-native-v1-receipt.json`).
- Optional pruning control:60003B / `c42cc4f0a0cd07096b0478c3b568b9ccec080730313ee607400c687aee542891`, from `build_pruned_control.py` plus the builder dependency. It changes no runtime declaration bytes and also has no `correct`. Compare it with exact original27 to diagnose any compiler/layout effect before interpreting the packed result.
- Both are **UNCOMPILED / UNPROVED_NATIVE_ONLY**. Original intake/policy should be run as usual; no full statement/gate success is possible or claimed. This is not an accepted submission and does not remove the eventual actual12 proof requirement.

The existing owned runner supports one Submission module, so the builder emits one file with only `import ContractExact`, within256000B. Keep original MainExact and flags. The packed entry is `Submission.kernels`; rows>=8 channel linears use tile16, rows1 classifier and lexical Ya3Q/GEMM remain original27. Include complete Mixer samples and all slow/small profile shapes.

Pinned official source check: `lean/bench/MainExact.lean` at accb82b6 has Git blob `3dd87bc460c888280cdd2e2d2f51b83c447a954b`; it imports ExactSuite/Submission and invokes `Submission.kernels`, with no correct/Verify reference. `validator/sandbox.py` blob `13c4f7b71e678a27d024613e5198e0d75667de4e` separates static intake/policy from the statement check. These are source observations supporting the diagnostic interface, not a claim that this new file has compiled or passed the original static functions.

**Required metadata correction in D-owned harness:** its current `info.proof_state` labels every fetched-and-patched entry `DECLARED_CORRECT_TYPECHECKED_NO_FULL_ORIGINAL_REPLAY`. That would be false for these two files. Respect an explicit `UNPROVED_NATIVE_ONLY_NO_CORRECT` override or record this actual absence explicitly; do not attach retained correctness to the new runtime.

Candidate/strong-predecessor ratios are internal mechanism measurements. Current36 qualification remains UNKNOWN pending the live/report config reconciliation and direct current source is withheld. No source whole-file or generated C/ASM publication; owned builders, identities, flags, raw timing and failures are sufficient.
