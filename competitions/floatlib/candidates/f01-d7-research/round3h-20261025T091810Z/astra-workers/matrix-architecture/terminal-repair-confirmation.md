# e49 terminal branch: delete all three trailing tactics

Confirmed against error-map40182931528 and exact e49cbc90 source. The compiler reports `No goals to be solved` atL6676, immediately after theL6675 rewrite, so that rewrite has already closed this terminal-branch goal. Delete **all** ofL6676–6678; deleting only the first `rcases` would leave the following `have` against an empty goal state. The branch should end exactly as follows:

```lean
  · rename_i hk
    have hkn : ¬ k.toNat<n := by
      rw [←hn]
      simpa only [USize.lt_iff_toNat_lt] using hk
    rw [R15PackedB2.loop, dif_neg hkn]
termination_by count.toNat-k.toNat
decreasing_by all_goals exact Packed10Index.next_decreases (by assumption)
```

Anchor the deletion on the preceding `rw [R15PackedB2.loop, dif_neg hkn]` and the following `termination_by`; similar four-row case splits elsewhere remain necessary. This removes the complete now-unreachable tactic tail, leaves no further terminal tactic after the witnessed closing rewrite, and changes no runtime or statement. New whole-source acceptance still needs recompilation. The original5f53 and e49 sources are retained; D alone owns the next candidate. No competing source was created.
