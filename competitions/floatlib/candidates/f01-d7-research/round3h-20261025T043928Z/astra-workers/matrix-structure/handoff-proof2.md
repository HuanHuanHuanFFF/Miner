# 05:09 UTC proof-only alternative ready

`Kernel-pairs-proof2.lean`, SHA-256 `42788837cecff41f1a7c093c83d47fc6865ffcac481c20024e7d939e156462a7`,217369bytes. Original `Kernel-pairs.lean` remains frozen at `b9629b37f47ed8b5c169de213ccec2a67a2b3b2737803c5814e996c1a1cc16b3`.

Exactly two lines removed: the `dsimp only` immediately after `simp only [dif_pos hk]` in `loop_s0` and `loop_s1`. The following `simp only [Packed10.nativeA_getD]` already simplifies the let/projection forms needed by the recursive call. No runtime definition, signature, dispatcher, arithmetic order or other proof changed. `pairs-proof2.diff` is the complete diff; `pairs-proof2-receipt.json` records an exact inverse back to b962.

Status: NOT_COMPILED. D identified a potential redundant-tactic risk based on prior R14 experience; there is no observed Lean failure for b962 and no claim that the original proof necessarily fails. This is the same runtime's proof alternative, not a new discovery draw. No local compilation or CI was performed.
