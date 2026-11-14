# R24 generic quotient/RNE helper probe

**Ready for D's old-scope validation, not yet compiled.** Kernel SHA256 `dd1f130159a727f63c1f91382e36ebd35956347fc73d69e44b0cc71b3ea291c2`,231094B. The first226829B are byte-identical to retained B2/`622d8394…`; all four public endpoints remain unchanged. `Quotient.lean.inc` SHA256 `66372bfd57840ec2a78b0f3fa924a33ade598dfbe8e2498bb7ba974f9aec1f79`.

Two actual roots only:

- `Submission.R24QuotientCertificate.checker_sound`: check=true for arbitrary UInt64 n/d/q proves q.toNat=n.toNat/d.toNat and the actual word subtraction is the natural remainder. The checker bounds n<2^49,0<d<2^25,q<2^25, proves the product fits before interpreting the two inequalities, and uses `Nat.div_mod_unique`.
- `Submission.R24QuotientCertificate.rounded_toNat`: the checked quotient/remainder rewrite the actual runtime RNE expression to public `FixedWord.roundQuotientEven`; its existing `_toNat` theorem supplies exact nearest-even semantics. No native proposal accuracy is assumed, and no correction is implemented.

`manifest.json` binds the existing helper-audit-v8 relative path/hash, both roots, source hash and180s statement-only diagnostic budget. Requested checks are original statement, required replay and explicit two-root axiom audit under the unchanged old ContractTensor environment. D alone owns Git/CI; no local Lean/native build was run. A failed run must retain original source/logs before any repair.

Local fixed-word emulation: `model-result.json`,870 boundary cases/56 accepted, both tie parities and a product-wrap weakened-guard falsifier; zero observed mismatches. This is finite arithmetic emulation, not the all-input proof or runtime evidence. `build.py` binds the source prefix and recreates the exact Kernel; `check_model.py` does not run tools or CI.

Missing: Binary32 rational/scaling transport, any RMS/LayerNorm implementation, actual selected caller/ASM/cost, full original gate/adoption. New TorchLean target remains pending; this portable mathematical component does not change its scope. Common deadline03:38:56UTC remains unchanged.
