# R15 public-source/runtime preliminary

Official public main and validator main are unchanged from R11. The actual FloatLib router still offers metadata, health, leaderboard, champions, submission detail and report, but no source download route. Recovering its public incumbent is recovery of the old reference, not champion source. No new public winner package is verified.

DF scalar add/nativeMul/mul have unboxed UInt32 C signatures. Their boxed adapters are separate definitions and do not prove the selected bench uses boxing. Native Float32 add/mul are C static inline operations; ofBits/toBits are exported runtime functions that canonicalize NaN. Pure raw reinterpretation or arbitrary payload roundtrip is not a legal proof shortcut.

Initial decision: no CI allocation to a repeated decoder, blanket inlining, or hypothetical boxed-call fix. Finish the exact DF callee audit and hashes, then publish the proof interface/first falsifier. Performance remains UNKNOWN/NOT_RUN.
