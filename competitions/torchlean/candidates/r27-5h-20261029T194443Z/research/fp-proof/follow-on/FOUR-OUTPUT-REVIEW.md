# Four-output interleaving takes priority over per-dot reassociation

Parent `research/fp-cost/FourFloatScalarEq.lean` keeps four independent left-fold operation sequences and exposes a specialized continuation. This is a lower proof-cost next optimization than this role's per-dot four-lane summation: exact scalar equality can reuse the existing numerical producer/checker chain, while a per-dot reassociation needs the separate four-chain error theorem. Both remain NOT_RUN and need actual native cost/ASM before selection.

One caller detail must stay explicit. Parent sumFour(a0,a1,a2,a3,b) preserves scalar(a_j,b). It naturally processes four left rows with one shared right vector. For four output columns sharing the original left activation row, the original scalar product is input*weight. `SharedLeftFourFloat.lean` preserves scalar(a,b_j) directly, including multiplication operand order; it does not ask for floating-point commutativity. Either orientation is valid when its actual caller agrees with the stated scalar interface.

The continuation avoids requiring an intermediate four-Float tuple in the source. The generated specialization and any final boxing/allocation must still be inspected; no allocation-free or speed claim is made. Shape/tail handling, per-output peak/radius/checker, lazy strong fallback and the final array still need an exact actual-caller connection.

Keep per-dot FourChain-v2 and its108oldcell finite replay as an alternative, not the next primary proof or a queued experiment. Both directions use only frozen-beforehand/old exploratory inputs here, never confirmation data.
