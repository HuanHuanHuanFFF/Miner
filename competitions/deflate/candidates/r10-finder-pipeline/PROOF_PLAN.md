# D insertion pipeline proof preparation

Status: UNADAPTED_PARENT_DRAFT. Current Parse.lean is the verified record parent's unchanged file; it does not match new D loop state. Native extraction, proof compilation and full original gate are not implied by the finite cache model.

Reuse source helpers and contracts already in the parent: hashes, dp_heads_spec and dp_store_spec. Original DP has the same pipeline and provides the proof pattern. Do not transplant its entire statement to D without accounting for D's rs/record/price/branch state.

Carry current b8, hash tuple hh, and old-head tuple pre. Existing DP extraction flattens hh into x3/x4/x7, with b8 and the three-component pre tuple as separate arguments. This suggests five extra function-state components, but actual new D Funs.lean determines order and result shape. The loop's per-iteration jumped flag is local, though it changes inner branch tuple results.

Required invariant additions: pre.1<=i, pre.2.1<=i and pre.2.2<=i, alongside original head3/head4/head7 LeAll and position/continuation bounds. Cached-word/hash truth is needed for exact-output equivalence, but engine D totality can treat search words as untrusted; original checked emission still owns final byte correctness.

Current dp_store writes the same head/prev values as insert_pos because the old heads were read at the same effective table state and the three head arrays are distinct. Immediately after store, prepare b8n/hn/pn1 for i+1. Ordinary and continuation branches mutate prices/records/counts but no head table, so pn1 remains available for the next i.

Long-match branches run original insert_range, then set jumped. Read fresh b8/hh/pre at the new i after all inserted-range writes. Do not reuse pn1 there: the finite model found5769 jumps where fresh heads differ from pn1. Chunk backtracking/cost updates after cache selection do not mutate matchfinder tables.

Initialization uses be8(0), hashes and dp_heads on zero tables. Final speculative lookahead can be unused, but all reads are total and table indices remain bounded. Existing DP proof handles be8/loop heads and wrapped i+1 arithmetic; retain the actual D input-size assumptions when adapting it.

Preserve original LZ77.Obligation, allowed axioms and final parse-validity statement. Native444 token/decode and public same-output/record checks discriminate cache-scheduling mistakes; they do not establish universal token equivalence. Full proof work waits for a worthwhile encoder-inclusive time signal.
