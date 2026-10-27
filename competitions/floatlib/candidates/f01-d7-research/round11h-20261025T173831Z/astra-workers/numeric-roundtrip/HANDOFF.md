# Public ADD: six-error proof-only repair ready

Updated UTC 2026-10-26T10:47:21.032728+00:00. Current window ends11:45:28UTC. No local Lean, Git or CI actions by this worker.

**New public source:** `public-add-v2/Kernel.lean`, **255148B**, SHA `93cc191a74b3b12a70770ffcce2eeb0c60519f5b5daec69e17100fa775d6be5e`, margin852B. The frozen7e source remains unchanged. `public-add-v2/proof-only-repair.patch` and `repair.py` give the exact replay; manifest binds original run40307208739 and full output SHA `a8acd20063c2b4fe185c26021f3bfe9a59631aaffb1411ba3c918772bb724250`.

**Four repair groups, six actual errors:**
- sameNoCarry/oppNoCarry: add the pinned method-to-notation `Nat.shiftRight_eq'` bridge before the existing division rewrite.
- sorted_spec twice: use `Bool.and_eq_true_iff.mp`, as independently checked by scalar-cost and relayed by root.
- oppWordShift: original full residual goal is `gap.toNat - UInt32.toNat1 = gap.toNat -1`; append reflexivity after the subtraction-toNat rewrite.
- addAligned: stop the rewrite list before halign; explicitly change to the canonical binary32 model equality, then finish with `(packModel ...).trans halign.symm`. This addresses the original semireducible format mismatch without changing any premise or arithmetic claim.

**Verified source boundaries:** exact reverse replacements recover7e; all declaration headers and all runtime definitions/abbrevs/structures/instances are byte-identical. Thus algorithm, guards, domain, fallback and public statements are unchanged. Original intake/policy/options PASS including comments; canonical LF. `HelperAudit.lean.inc` is byte-identical to v1:67 helper roots plus4 public specs. **Repair2 Lean/kernel/helper audit/full gate/performance NOT_RUN.** No old22-root result is promoted to this71-root version.

**Frontend provenance caveat:** root's checked fixed293d API report was used. The stated scalar-cost/add-frontend-repair folder was not visible in this worker's filesystem snapshot, so no local file hash is invented; root can attach its independent receipt. The exact changes are fully exposed in the patch.

**Next minimum action:** D can compile93cc when its active frozen-MUL full gate permits, then replay the complete module and all71 roots. Actual new errors take priority over source expansion. Prior frozen sources, initial failures, negative timing results and byte-pruning records remain preserved. Tokens UNKNOWN; worker CI0.
