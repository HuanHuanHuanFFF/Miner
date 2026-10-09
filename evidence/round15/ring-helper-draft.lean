-- UNCOMPILED DRAFT. Insert before u592 in the preserved parent proof.
-- Signatures checked against official extraction 37915493157 / ring-s.
-- These are totality/bounds lemmas; final acceptance still requires the
-- original LZ77.Obligation, unchanged axioms check, and round trip.

@[local step]
theorem r15_min_ring_loop_spec
    (cost : Std.Array Std.U32 1024#usize) (lc : Std.Array Std.U32 512#usize)
    (offset hi : R) (base best l)
    (hhi : hi.val < 512) (hoffset : offset.val < 512) :
    slot.r15_min_ring_loop cost lc offset hi base l best ⦃ Y112P0! ⦄ :=
  Y127U3! slot.r15_min_ring_loop slot.r15_min_ring_loop.body

@[local step]
theorem r15_min_ring_spec
    (cost : Std.Array Std.U32 1024#usize) (lc : Std.Array Std.U32 512#usize)
    (offset lo hi : R) (base : W) (width : R) :
    slot.r15_min_ring cost lc offset lo hi base width ⦃ Y112P0! ⦄ :=
  Y127U12! slot.r15_min_ring

@[local step]
theorem r15_dp_ring_inner_spec
    (tail : R) (mb : alloc.vec.Vec W) (lc : Std.Array W 512#usize)
    (dc : Std.Array W 32#usize) (cl : R) (ring : Std.Array W 1024#usize)
    (i offset : R) (bias best bd : W) (prev pd j top : R)
    (hi : i.val ≤ 2 ^ 31) (htop : top.val ≤ mb.length)
    (hprev : prev.val ≤ i.val + 258) (hpv : i.val ≤ prev.val)
    (hpd : pd.val ≤ 32768) (hbd : bd.val ≤ 32767) :
    slot.r15_dp_ring_loop0_loop0 mb lc dc tail cl ring i offset bias best bd prev pd j top
      ⦃ Y112P7! ⦄ :=
  Y127U5! slot.r15_dp_ring_loop0_loop0 slot.r15_dp_ring_loop0_loop0.body

@[local step]
theorem r15_dp_ring_loop_spec
    (tail : R) (s : I) (mp mb : alloc.vec.Vec W)
    (p0 : R) (lit : Std.Array W 256#usize) (lc : Std.Array W 512#usize)
    (dc : Std.Array W 32#usize) (ch : alloc.vec.Vec W) (cl : R)
    (ring : Std.Array W 1024#usize) (i e xl xd : R)
    (hi : i.val < cl.val) (hmp : i.val < mp.length)
    (hs : i.val ≤ s.length) (hch : i.val ≤ ch.length)
    (hi31 : i.val ≤ 2 ^ 31) (hxl : xl.val ≤ 258) (hxd : xd.val ≤ 32768) :
    slot.r15_dp_ring_loop0 s mp mb p0 lit lc dc ch tail cl ring i e xl xd
      ⦃ Y112P0! ⦄ := by
  rw [slot.r15_dp_ring_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, i_, _, _, _) => i_.val)
    (inv := fun ((ch_ : alloc.vec.Vec W), (_ : Std.Array W 1024#usize),
        (i_ : R), _, (xl_ : R), (xd_ : R)) =>
      ch_.length = ch.length ∧ i_.val ≤ i.val ∧ xl_.val ≤ 258 ∧ xd_.val ≤ 32768)
  · rintro ⟨ch_, ring_, i_, e_, xl_, xd_⟩ ⟨hch_, hi_, hxl_, hxd_⟩
    simp only [slot.r15_dp_ring_loop0.body]
    step*
    apply WP.spec_bind (Pₘ := fun (top : R) => top.val ≤ mb.length)
    · split <;> step* <;> scalar_tac
    rintro top htop
    step*
    apply WP.spec_bind (Pₘ := fun (el : R) => el.val ≤ 258)
    · split <;> step* <;> scalar_tac
    rintro el hel
    step*
    apply WP.spec_bind (Pₘ := fun (x : R × R × W × W) =>
      x.1.val ≤ 258 ∧ x.2.1.val ≤ 32768 ∧ x.2.2.2.val ≤ 32767)
    · repeat' (split <;> step*)
      all_goals scalar_tac
    rintro ⟨xl1, xd1, best2, bd1⟩ ⟨hxl1, hxd1, hbd1⟩
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact ⟨rfl, le_refl _, hxl, hxd⟩

@[local step]
theorem r15_dp_ring_spec
    (tail : R) (s : I) (mp mb : alloc.vec.Vec W) (p0 pe : R)
    (lit : Std.Array W 256#usize) (lc : Std.Array W 512#usize)
    (dc : Std.Array W 32#usize) (cost ch : alloc.vec.Vec W)
    (hpe : pe.val ≤ 2 ^ 31) :
    slot.r15_dp_ring s mp mb p0 pe lit lc dc cost ch tail ⦃ Y112P0! ⦄ :=
  Y127U12! slot.r15_dp_ring
