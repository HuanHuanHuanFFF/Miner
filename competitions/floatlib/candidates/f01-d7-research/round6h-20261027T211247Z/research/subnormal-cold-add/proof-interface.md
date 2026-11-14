# E0 cold ADD: minimal original-model dependency map

Read-only follow-up started **02:52:08 UTC**, bounded to03:02:08; no extra candidate, Lean or CI. Runtime2292584c remains frozen.

The fixed FloatLib generic dyadic interface already has the exact nonzero arithmetic cases. In `FloatLib/Floats/ExecFloat/Backends/Generic/AddDyadic/Proof.lean`, use:

- `Model.addDyadic_sameSign_sameExponent` for same signs, both nonzero, exponent−149.
- `Model.addDyadic_oppositeSign_sameExponent_largeLeft` / `largeRight` for strict magnitude ordering; both magnitudes must be nonzero.
- `Model.addDyadic_oppositeSign_sameExponent_eq_zero` for equal nonzero magnitudes/opposite signs; it returns **false sign, zero significand, exponent0**.

**Typed zero boundary:** `Model.toDyadic?_ofFields_subnormal` requires nonzero fraction. For E0/nonzero f the decode is `⟨sign,f,−149⟩`, but a raw zero decodes as `⟨sign,0,0⟩`, not exponent−149. Split zero fractions first. The fixed `addDyadicImpl` zero branches return the nonzero other operand; two zeros use sign AND. Do not feed a zero into the nonzero same-exponent lemmas or reuse the left sign on opposite cancellation.

Existing R22 fragments provide a **NOT_RUN** reserve, not accepted proofs: `independent-frontier/SameExponentLow.lean.inc` has `low_lattice_round sign n (n<2^24)` and same-sign/nonzero `subnormal_fields_nonzero_add`; `SameExponentZero.lean.inc` has `zero_fields_decode`, `zero_round`, and same-sign/all-zero-case `subnormal_fields_add`. The mixed-sign branches are not closed by that last root. These fragments should only be ported after a new cost signal; the old low-lattice proof's log2 case distinction is proof work, not new runtime work.

Encoding obligations are small but still open. Same-sign f+g<2^24 permits E0 or E1, using quotient/remainder at2^23. Opposite-sign nonzero difference is<2^23 and remains E0. Prove UInt32 addition does not wrap, use `UInt32.toNat_sub_of_le` on the selected larger magnitude, and connect `mkBits sign (n/2^23) (n%2^23)` to the existing sign bit OR n. This explains why masking a same-sign sum back to23bits is wrong at minnormal crossing. Zero packing must preserve the sign-AND or positive-cancellation rule above.

Remaining public obligations: actual OR exponent-zero guard→E0 fields, word sign/fraction extraction, model/spec transport, and the two-layer fallback. The original fastOK/hot body remains exactly21cd and every other miss calls original coldAdd. No result here changes the domain, predicts time saved, or proves the807B runtime correct in Lean.

Reference sources were read from the existing FloatLib Team/MIT snapshot under `round8h-20261024T190259Z/astra-upstream/FloatLib/Floats/ExecFloat/Backends/Generic/AddDyadic/{Runtime,Proof}.lean`; their original license headers were retained in place. The source-level field/decode pointers above, rather than a new proof or execution, are this follow-up's output.
