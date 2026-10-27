# R2-04 — two frozen candidates on compiled final-finite parent

D reports actual statement run39655412696 succeeded for standalone R2-02 preimage and integrated sum/bmm final-finite. Parent `f01-d2-final-finite/Kernel.lean` SHA `86312a3759286cb207f946af9db95546777fdb16f1bd147f7892c0f9e1d79217` is now a real compiled starting point; its complete gate/performance remains pending.

Two independent R candidates are frozen and ready for D's next statement batch. Both preserve scalar wrappers, the existing exception fallback, all official inputs and pins. Do not combine their performance claims before testing an actual integrated version.

| Candidate | Kernel SHA-256 | Bytes | Change |
|---|---|---:|---|
| f01-r2-preconverted-bmm | da9a9fab1f88bcc0d696fb263f8417cdd4c7da8223b7bb434901b23f6f7f3e07 | 60174 | A/B map to native Float32 once per bmm; ordered scalar dot and final guard unchanged |
| f01-r2-native-fold-sum | 8e37506086715f0d0b13e21b46b0dfc8d32b99348658a0b1ed5822ddd5a5d8c0 | 59206 | Native inline step via standard Vector.foldl; backward List.foldl proof |

Sources/manifests under `competitions/floatlib/candidates/<name>/`; generator and fragment files in this R2 research directory. Both new proof extensions are NOT_RUN. D can copy bytes to owned scope, use statement preflight first, and only advance passing mechanisms to full gate plus paired timing with exact parent control. C questions: preconverted dot should have no per-MAC lean_float32_of_bits; sum should use specialized standard array fold with machine-size induction and float accumulator. The actual linked behavior/timing is UNKNOWN until measured. Mapping, boxing and all setup stay inside timed bmm.

No duplicate USize implementation: D owns address bounds/no-wrap/uget. R continues native multi-output/layout and three web Pro directions while this batch waits. New web resource status and original prompts are indexed by research-status.json.

Additional independent representation possibility (NOT implemented): FloatArray's numeric widening/narrowing operations are opaque, but their runtime C functions are inline casts. Rather than assume a theorem about opaque conversion, one may validate `ofFloat32(toFloat32(toFloat(native x))) = x` by a raw-word guard once per input, then use that checked invariant with FloatArray.get/uget. This could permit contiguous double storage and inline narrowing in each MAC without asserting opaque semantics. First blocker: audit whether those existing opaque data functions add forbidden dependencies to the final proof. Do not adopt merely from this reasoning. An array's `.data` accessor boxes the entire buffer at runtime, so never use it in a hot read; use get/uget. This is distinct from D's bit-container FloatArray proposal.
