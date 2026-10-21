/-
UNVERIFIED helper draft for insertion into Submission, immediately before
d_parse_loop_spec in the scalar parent proof. Actual Aeneas interfaces and a
fresh original obligation/axiom gate are still required. No sorry/axiom added.
The range-loop signature/state order below is inferred from insert_range;
replace it from the actual extraction if needed.
-/

@[local step]
theorem r10_cache_store_spec (cache : Array Std.U64 65536#usize)
    (b8 : Std.U64) (p : Std.Usize) :
    slot.r10_cache_store cache b8 p ⦃ fun _ => True ⦄ := by
  rw [slot.r10_cache_store]
  step*
  repeat' (split <;> step*)
  all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))

@[local step]
theorem r10_supplement_spec (input : Slice Std.U8) (old i : Std.Usize)
    (b8 : Std.U64) (cap : Std.Usize) (cands : Array Std.U32 16#usize)
    (nc0 best0 : Std.Usize) (hcap : 9 ≤ cap.val)
    (hic : i.val + cap.val ≤ input.length)
    (hs8 : input.length + 8 ≤ Std.Usize.max) (hb : best0.val ≤ cap.val) :
    slot.r10_supplement input old i b8 cap cands nc0 best0
      ⦃ fun r => best0.val ≤ r.1.2.val ∧ r.1.2.val ≤ cap.val ⦄ := by
  rw [slot.r10_supplement]
  step*
  repeat' (split <;> step*)
  all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))

@[local step]
theorem r10_insert_range_loop_spec (input : Slice Std.U8)
    (head3 : Array Std.U32 16384#usize) (head4 : Array Std.U32 65536#usize)
    (prev4) (head7 : Array Std.U32 65536#usize) (prev7)
    (cache : Array Std.U64 65536#usize) (e : Std.Usize) (sh7 : Std.U32)
    (q : Std.Usize) (B : Nat)
    (h3 : LeAll head3.val B) (h4 : LeAll head4.val B) (h7 : LeAll head7.val B)
    (he : e.val ≤ B + 1) (he8 : e.val + 8 ≤ Std.Usize.max) :
    slot.r10_insert_range_loop input head3 head4 prev4 head7 prev7 cache e sh7 q
      ⦃ fun r => LeAll r.1.val B ∧ LeAll r.2.1.val B ∧ LeAll r.2.2.2.1.val B ⦄ := by
  rw [slot.r10_insert_range_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, _, _, q') => e.val - q'.val)
    (inv := fun (h3', h4', _, h7', _, _, _) =>
      LeAll h3'.val B ∧ LeAll h4'.val B ∧ LeAll h7'.val B)
  · rintro ⟨h3', h4', p4', h7', p7', cache', q'⟩ ⟨i3, i4, i7⟩
    simp only [slot.r10_insert_range_loop.body]
    split
    · step*
      all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
    · step*
  · exact ⟨h3, h4, h7⟩

@[local step]
theorem r10_insert_range_spec (input : Slice Std.U8)
    (head3 : Array Std.U32 16384#usize) (head4 : Array Std.U32 65536#usize)
    (prev4) (head7 : Array Std.U32 65536#usize) (prev7)
    (cache : Array Std.U64 65536#usize) (f e : Std.Usize) (sh7 : Std.U32)
    (B : Nat) (h3 : LeAll head3.val B) (h4 : LeAll head4.val B)
    (h7 : LeAll head7.val B) (he : e.val ≤ B + 1)
    (he8 : e.val + 8 ≤ Std.Usize.max) :
    slot.r10_insert_range input head3 head4 prev4 head7 prev7 cache f e sh7
      ⦃ fun r => LeAll r.1.val B ∧ LeAll r.2.1.val B ∧ LeAll r.2.2.2.1.val B ⦄ := by
  rw [slot.r10_insert_range]
  exact r10_insert_range_loop_spec input head3 head4 prev4 head7 prev7 cache e sh7 f B h3 h4 h7 he he8
