/- R10 helper totality draft. Loop signatures reconciled with run 37679261323
   extraction; proof elaboration and the original gate are still untested. -/

@[local step]
theorem d_seed_put_spec (out : Slice Std.U32) (p len dist : Std.Usize) :
    slot.d_seed_put out p len dist ⦃ fun r => r.length = out.length ⦄ := by
  rw [slot.d_seed_put]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

@[local step]
theorem d_seed_map_loop0_spec (out : Slice Std.U32) (n q : Std.Usize) :
    slot.d_seed_map_loop0 out n q ⦃ fun r => r.length = out.length ⦄ := by
  rw [slot.d_seed_map_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, q') => n.val - q'.val)
    (inv := fun (out', _) => out'.length = out.length)
  · rintro ⟨out', q'⟩ hout
    simp only [slot.d_seed_map_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · rfl

@[local step]
theorem d_seed_map_loop1_loop0_spec (rs : Slice Std.U32) (out : Slice Std.U32)
    (e p j : Std.Usize) (he : 2 ≤ e.val) :
    slot.d_seed_map_loop1_loop0 rs out e p j ⦃ fun r => r.length = out.length ⦄ := by
  rw [slot.d_seed_map_loop1_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, j') => e.val - j'.val)
    (inv := fun (out', _) => out'.length = out.length)
  · rintro ⟨out', j'⟩ hout
    simp only [slot.d_seed_map_loop1_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · rfl

@[local step]
theorem d_seed_map_loop1_spec (rs : Slice Std.U32) (out : Slice Std.U32) (e : Std.Usize) :
    slot.d_seed_map_loop1 rs out e ⦃ fun r => r.length = out.length ⦄ := by
  rw [slot.d_seed_map_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, e') => e'.val)
    (inv := fun (out', _) => out'.length = out.length)
  · rintro ⟨out', e'⟩ hout
    simp only [slot.d_seed_map_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · rfl

@[local step]
theorem d_seed_map_spec (rs : Slice Std.U32) (out : Slice Std.U32) (n : Std.Usize) :
    slot.d_seed_map rs out n ⦃ fun r => r.length = out.length ⦄ := by
  rw [slot.d_seed_map]
  step*

@[local step]
theorem d_seed_loop_spec (out : Slice Std.U32) (plan : alloc.vec.Vec Std.U32)
    (n q «end» dist next : Std.Usize) :
    slot.d_seed_loop out plan n q «end» dist next ⦃ fun _ => True ⦄ := by
  rw [slot.d_seed_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, q', _, _, _) => n.val - q'.val)
    (inv := fun _ => True)
  · rintro ⟨plan', q', end', dist', next'⟩ _
    simp only [slot.d_seed_loop.body, lift, bind_tc_ok]
    apply dp_ite_spec <;> intro hq
    swap
    · exact d3_ok trivial
    have hq' : q'.val < n.val := (UScalar.lt_equiv _ _).mp hq
    apply dp_ite_spec <;> intro ho
    swap
    · exact d3_ok trivial
    have ho' : q'.val < out.length := by
      have := (UScalar.lt_equiv _ _).mp ho
      have hl := Slice.len_val out
      omega
    refine d3_sidx ho' ?_; intro c
    refine d3_rem (b := 512) rfl (by decide) ?_; intro i1 _
    refine d3_shr (n := 9) (by decide) rfl ?_; intro i2 _
    refine d3_bind (Q := fun _ => True) ?_ ?_
    · step*
      repeat' (split <;> step*)
      all_goals scalar_tac
    rintro ⟨end1, dist1⟩ _
    refine d3_unc ?_
    refine d3_bind (Q := fun _ => True) ?_ ?_
    · step*
      repeat' (split <;> step*)
      all_goals scalar_tac
    rintro ⟨plan1, next1⟩ _
    refine d3_unc ?_
    refine d3_add (b := 1) rfl rfl (by have := d3_le_max n; omega) ?_; intro q1 hq1
    exact d3_ok ⟨trivial, (by clear * - hq' hq1; omega)⟩
  · trivial

@[local step]
theorem d_seed_spec (input : Slice Std.U8) (rs : Slice Std.U32) (out : Slice Std.U32)
    (plan : alloc.vec.Vec Std.U32) :
    slot.d_seed input rs out plan ⦃ fun r => r.1.length = out.length ⦄ := by
  rw [slot.d_seed]
  step*
