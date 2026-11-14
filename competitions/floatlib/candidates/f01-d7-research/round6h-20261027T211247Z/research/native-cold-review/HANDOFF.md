# R22 B: native cold ADD/MUL semantic review

Current follow-up: [public-add/HANDOFF.md](public-add/HANDOFF.md), exact **75da1c41 / 231000 B / 11 roots**, complete public ADD proof attempt **NOT_RUN**. Original review fragments below remain preserved.

Started **00:38:36 UTC**, ready **00:47:00 UTC**; requested bound **00:58:36**, shared cutoff **03:12:47** unchanged. Read-only D runtime review, no public source/CI/local Lean.

- Exact **e3b93d3a / 784 B MUL** accepts E64..191 pairs; exact **21cd9128 / 490 B ADD** accepts each signed zero or E24..254. Old B2 fallback preserves all excluded words and operand order. Hit inputs are finite; native overflow to Inf is valid. Removing only the hit-arm result NaN test has an existing proof route.
- `FastOKNativeBridges.lean.inc` **5607ee4a / 2038 B / 3 roots**, `PairDomain.lean.inc` **56811947 / 1172 B / 1 root**, all **NOT_RUN**. Use exact B2 table decode, raw classifier, R7Native Add/Mul, NotNaNProbe.roundtrip and original spec bridges. No new axiom/import or full public assembly.
- `boundary-witnesses.json`: **50 fixed source-word cases**, zero guarded differences. E23 cancellation `0b800001+8b800000=00400000` versus forced-table 0; raw qNaN `7fc00001+1` preserves payload versus unconditional-native canonical `7fc00000`; ±0, invalid operations and both overflow cases retained. Not native/Lean/performance evidence.
- `REVIEW.md` lists exact old roots and likely port pitfalls: B2 lacks old-parent `R2W01c.normal_finite`/`GuardBridge.finiteRoundtrip`; old R19 modular guard proof should use the magnitude's toNat bound as old R11 did if omega reports that gap. No actual compiler failure is asserted.
- `manifest.json` and `status.json` are current bindings. Next: actual selected caller/full cost or exact typing first error from D; no operation-count speed inference, no guard sweep or runtime edits.
