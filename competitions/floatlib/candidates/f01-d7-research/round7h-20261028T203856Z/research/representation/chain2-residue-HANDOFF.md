# Minimal residue bridge, NOT_RUN / NOT_QUEUED

`TwoChain128Residue.lean.inc`:1747 B, SHA `76db9822a78f688405968e10efa920023ee9cf49a9cfb1040734812948d44a0b`. Phase first UTC02:05:02; first source02:07:19; original cutoff03:38:56 unchanged. Three roots only: `represents_canonical_residue`, `represents_unique`, `run2_terminal_of_represents`.

UInt128's public unsigned range and integer remainder laws show that two words representing the same Int modulo2^128 are identical. This needs no signed-range or no-overflow condition. Arbitrary terminal transport follows by `congrArg`; the new-loop representation comes from frozen word2's concrete merge and public `add128_toNat`. The old loop must still supply its modular invariant, not assumed word equality. No proof-reference runtime fold or D baseline was added.

First concrete original-interface obligation: prove `R24TwoChain128.high q = 0 - (q >>> 63)` for every UInt64 q, identify the actual QY6G getter/uget/USize sequence with `readSequence`, then induct its original scalar state into `Represents`. Preserve the existing B0, bias and sentinel in the terminal. This has not been proved or integrated here; no anonymous source was copied. Actual C/ASM/callback/boxing/cost remain UNKNOWN.

The full input/source IDs are in `chain2-residue-source-receipt.json`. All earlier chain/encoder/index fragments remain frozen. No local Lean, CI, benchmark, Kernel package or additional similar lemmas were created; tokens/cache UNKNOWN.
