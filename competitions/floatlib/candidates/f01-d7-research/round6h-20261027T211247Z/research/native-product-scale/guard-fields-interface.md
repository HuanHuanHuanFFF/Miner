# Actual normal guards to original-input fields

Started 2026-10-28 00:04:09 UTC; bounded to 00:14:09 UTC. One proof-only root, no runtime/probe edit, local Lean, CI or public proof assembly.

`GuardFields.lean.inc` adds `Submission.R22NativeProductGuard.guard_fields`. Its premises use exactly the runtime's two wrapping UInt32 tests: each extracted exponent minus 1 is at most 253, and their UInt32 sum minus 174 is at most 206. The conclusion gives the unwrapped sum equality, both original exponents in 1..254, and their Nat sum in 174..380. `rawExponent` is an abbreviation for the actual shift/mask; it adds no runtime guard.

The proof follows the accepted R17 exponent/guard arithmetic pattern, with 174/206 replacing 128/252. It explicitly exposes the UInt32 modulus 4294967296, so a wrapped subtraction below the lower bound cannot silently become Nat subtraction. This new root is **NOT_RUN**. It uses only existing B2 definitions and ordinary UInt32/Nat lemmas; it needs no R17 proof import, additional axiom, finite enumeration or new tactic import.

Dependency wiring:

```text
actual outer and inner guard hypotheses
  -> R22NativeProductGuard.guard_fields
  -> 1 <= ex,ey <= 254; S=ex+ey without UInt32 wrap; 174 <= S <= 380
  -> old R18.R14NatNormal.raw_normal_decode on each original raw input
  -> original-input Model.mul / rounded-mantissa bridge

synthetic scale and exact second multiplication -> A's separate bridge
```

The exact original-input decode is already in `f01-r17-dev-u64-public2/Kernel.lean`, SHA `00ab99c7ff16a8f0f58c5a0b6ad5c87c10c2407589ee17c5f9cba444b7cfd080`, lines 6999–7008, root `R18.R14NatNormal.raw_normal_decode`. Its only exponent hypotheses are `0 < wordExp u` and `wordExp u < 255`. Thus it includes E1..23. The relevant old full gate is run 40309310448; its retained terminal receipt and actual passed verdict are bound in `guard-fields-manifest.json`. The source declaration sits in a named **section**, not an additional namespace. No prefix `R18PublicMULBridgeProbe` belongs in the root name.

That old decode's 10-line declaration depends only on B2's `R2W01c.rawModel_eq_ofUInt32`, `raw32_eq_fields`, `R2W01c.mantissa_toNat`, `fields32_toDyadic` and `wordFrac_lt`. A later assembly can preserve this exact small declaration under the intended namespace; importing the entire old U64 public implementation is unnecessary. This note does not append a duplicate proof. In particular, do not use `R2W01c.target_raw_decode` for the original inputs: its `NormalBand` requires E>=24, which the actual new guard does not require.

The original e51a67d6 runtime and 92ff7182 probe remain byte-identical. Their previous seven-root audit remains unchanged; this separate root is not included there and not accepted by prior CI. The new full MUL specification, typing/replay and complete runtime cost remain open.
