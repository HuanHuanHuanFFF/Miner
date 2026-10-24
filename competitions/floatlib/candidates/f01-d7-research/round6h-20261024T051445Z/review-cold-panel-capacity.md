# Cold + GeneralPanel capacity review

**Read-only static review.** I independently checked the capacity receipt’s 42 byte ranges against the frozen GeneralPanel source and recomputed its textual reference closure. The ranges match their recorded bytes, lengths and SHA-256 values, do not overlap, and total 11,840 bytes. All 42 selected names map to unique qualified declarations in the Panel inventory and are unique in the source declaration scan. This is not a Lean dependency proof or a full-gate result.

## Confirmed source and static arithmetic

The reviewed GeneralPanel is 255,559 bytes (`a1ab536c…2e48abe`). The cold proof2 source is 247,897 bytes (`3ff4eb8e…11f36221`). Its exact cold insertion is present in that source. The converter candidate’s Kernel and manifest both match `59de0e17…7005ce4`; the raw 901-byte `after` fragment in its inverse receipt is present in that Kernel.

The capacity script’s arithmetic is internally consistent: GeneralPanel plus the cold delta is 264,315 bytes; the estimated converter addition brings that to 264,562. Removing all 42 listed bodies would yield 252,722 bytes and 3,278 bytes of headroom. These are source-size estimates only; no combined source was generated or compiled.

## Corrections before using the 42-body pool

The range for `Submission.R7W05.repairDotStep_eq_original` starts at the theorem, while its immediately preceding 87-byte documentation comment is outside the range. The comment says the product is recomputed from both original raw words. Deleting only the 329-byte theorem leaves that comment attached to the next declaration, `repairSumStep_isNaN_eq`, which is misleading. Retain this theorem with its comment, or explicitly preserve and reattach the comment before applying any deletion set. Retaining the theorem leaves 41 bodies / 11,511 proposed bytes removable; the static three-mechanism estimate becomes 253,051 bytes with 2,949 bytes of headroom. The theorem body has no reference to another member of the proposed 42-body pool.

The script constructs its future converter root from `f01-d12-mul-existing-convert/exact-inverse.json`, but does not pin that candidate’s Kernel SHA or assert that the raw inverse fragment is present in the candidate Kernel. I independently verified the current source and fragment as noted above. Before reusing the capacity script, bind the expected converter Kernel/manifest SHA and assert the fragment against that exact Kernel; otherwise later receipt changes can silently change the assumed future root.

The recomputed closure reproduces 254 candidate theorem nodes, 212 retained nodes and the same 42 removable names. On the script’s textual name-reference graph, the removable set has no references outside itself, no retained caller points into it, and the constructed cold/converter roots do not mention a removable name. This confirms only the script’s static graph result. Five selected bodies use `simp` and five use `decide`; the empty `implicit_search_tokens` list only reflects the script’s narrow regex and does not establish elaborator, simplifier, typeclass or tactic dependency closure. The exact combined candidate still needs the complete original Lean gate, with its final source and tool versions bound to the run.

## Evidence boundary

No candidate, capacity script, tool, state, Git or CI file was changed. No test, Lean build, official gate or timing run was performed for this review. The 010 Panel result remains the evidence needed before deciding whether to pursue a combined candidate; this static estimate does not establish benefit or acceptance.

File hashes and the detailed audit record are in [review-cold-panel-capacity.json](review-cold-panel-capacity.json).
