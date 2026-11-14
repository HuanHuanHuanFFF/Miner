# Raw midpoint/sign-OR independent static review

No concrete static blocker was found in RawMidpoint85a54ce3/8937B and NativeSignOr0ea8f879/2740B. Exact component/dependency/runtime hashes and public API prototypes were checked; Lean, replay and axiom acceptance remain unverified.

The raw32 sign/exponent/fraction getters match the actual PortableF64 expressions. Sign-OR is first connected to stored-word Model.neg under a proved sign-clear bound. Negative lower/upper words correctly swap positive upper/lower before negation. The minimum-normal lower spacing and maximum-finite overflow midpoint are covered, and the thin rational-rounder call preserves the existing NormalCell premises. No mathematical or source edit is recommended without actual typing evidence.

The remaining caller boundary is important: actual certify uses UInt64 orderKey, not Float.lt. Endpoint real equalities plus a separate native comparison theorem do not prove that Boolean checker. A finite-key strict-order lemma must exclude the pair of signed zeros, since key(-0)<key(+0) although both reals are0. Normal-q midpoint boundaries are nonzero, so their decode/geometry facts can discharge the exception; actual endpoint finiteness and the sum/radius enclosure still need composition.

The prototype was read, not rerun. Its finite cases are not proofs; its virtual2^128 max-finite neighbor is intentional. The JSON records source identities, precise scope and remaining obligations. No B source, Git or CI was changed.
