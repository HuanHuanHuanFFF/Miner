# Written typing and termination obligations

Source remains Borrowed-tail-ABI.lean.inc, 1400B / 680ca1b3. This is a manual interface review, not Lean acceptance. Do not modify the frozen probe speculatively; use the first actual compiler diagnostic to decide whether a repair is needed.

Write r = n.toNat - k.toNat and r' = n.toNat - (k+1).toNat. Existing B2 Packed10Index.next_decreases supplies r' < r under h : k < n. Its proof uses the no-wrap stepNat fact, so the argument does not assume unbounded USize addition.

| Source edge | Caller measure | Callee measure | Required fact |
| --- | --- | --- | --- |
| hot(k) to hot(k+1) | 2r+1 | 2r'+1 | r' < r |
| hot(k) to cold(k) | 2r+1 | 2r | Nat arithmetic |
| cold(k) to hot(k+1) | 2r | 2r'+1 | r' < r |

Every edge is inside the h branch, including hot to cold, so the written tactic's call to next_decreases has a source hypothesis even when that arithmetic fact is unnecessary for the phase-only edge. All three inequalities follow in Nat arithmetic. Whether the mutual elaborator exposes exactly those simplified goals to the written tactic remains NOT_RUN; this table is the repair target if a real diagnostic later identifies a goal-shape issue.

Both Array.getD calls have Nat index zero and UInt32 default zero. Their XOR is UInt32 and the bit-mask literal is explicitly UInt32. The branch-local numeric cast is the existing UInt32.toFloat32. All operands of the cold arithmetic sum are USize, and USize.toUInt32 exists in pinned upstream-UInt-Basic.lean:929. R15ThinPairs.F2 is the existing two-Float32 structure at B2:6168; the eight arbitrary input floats are consumed by the terminal expression, not stored in a new transition tuple.

There is no runtime Nat fuel or phase parameter. The phase appears only in termination_by, and common input/cursor fields remain in both direct signatures. This probe intentionally does not preserve any public SUM/BMM semantics: terminal grouping and toy updates only force the ABI to carry eight floats. It cannot be adopted as a numerical candidate even if the codegen prerequisite succeeds.
