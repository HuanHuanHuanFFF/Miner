# Independent SubnormalWiden review

Reviewed 2026-10-29 03:08:43 UTC; exact source `62380963…` /12003B and actual PortableF64 runtime `dd775683…`.

The nonzero-subnormal mathematics matches the runtime: `1 <= f < 2^23`, `ell <= 22`, shift `52-ell` is30..52, and `E64=ell+874` is874..896. Subtraction and shifts do not wrap. Decoded `f*2^(52-ell) * 2^(ell-201)` is exactly signed `f*2^-149`. Both sign and finite-native conversion are grounded in the stored word and pinned Float.ofBits model. No mathematical counterexample found; **Lean/replay/AX NOT_RUN**.

- **Predicted typing risk, line71:** after line70's `rw`, the count equality is definitionally reflexive; the separate `rfl` may run with no goals. Delete that one line or use the direct `simpa only [lead_nat] using UInt64.toNat_sub_of_le …` form. This is a static prediction, not a compiler result.
- **Carrier requirement, line228:** include retained `R2W01c.modelCanonicalOfFinite/modelCanonical_of_decode`. The shipped prefix alone lacks them; exact support exists in `PortableNativeMulBridge-v2.lean.inc` (`2c823b1a…`) and island6. FastMul and its equality theorem are already present in the shipped carrier.
- Large-coefficient `omega` remains a resource risk. Change only the first real failing goal if observed; line151's pure distributivity can use `ring`. Do not raise limits or infer another failure without a compiler receipt.

Full source/API hashes, bounds and three edge-value calculations are in `subnormal-widen-independent-review.json`. No source, runtime, Git, CI or external submission was changed.

