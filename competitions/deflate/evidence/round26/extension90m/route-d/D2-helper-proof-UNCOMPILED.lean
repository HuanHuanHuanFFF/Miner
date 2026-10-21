-- D2: expected same loop tuples; go2 budget is consumed togo1 on first attempt.
-- Triple current result adds an untrusted strategy flag, not a correctness premise.
-- UNCOMPILED: insert inside U118_MAIN immediately after its original find_spec.
-- Exact extracted signatures/captures must be checked before a gate attempt.
-- This draft claims no all-input algorithm equivalence or performance result.

theorem d2_found_end {s : Slice Std.U8} {p l d : Nat}
    (hf : FoundAt s p l d) (hp : p + 3 ≤ s.length) : p + l ≤ s.length := by
  rcases hf with h | h
  · omega
  · exact h.2.2.1

-- Expose the match-end fact directly so arithmetic preconditions for the next
-- start need not unfold FoundAt or accidentally assume the shallow match exists.
attribute [-step] find_spec
@[local step]
theorem d2_find_bounded_spec (s : Slice Std.U8) {W : Std.Usize} (prev : Array Std.U32 W)
    (p st «have» minl depth nice gm : Std.Usize) (hlit : Std.I32)
    (hp : p.val + 3 ≤ s.length) (hst : st.val ≤ p.val + 2)
    (hhave : p.val + «have».val ≤ s.length) (hhave258 : «have».val ≤ 258)
    (hminl : 1 ≤ minl.val) (hminl' : p.val + minl.val ≤ s.length + 1)
    (hW : 0 < W.val) (hh0 : 0 ≤ hlit.val) (hh1 : hlit.val ≤ 1000000) :
    slot.u118_find s prev p st «have» minl depth nice gm hlit ⦃ fun r =>
      FoundAt s p.val r.1.val r.2.val ∧ r.1.val ≤ 258 ∧ r.2.val ≤ 32768 ∧
      p.val + r.1.val ≤ s.length ⦄ := by
  apply Std.WP.spec_mono (find_spec s prev p st «have» minl depth nice gm hlit
    (by omega) hst hhave hhave258 hminl hminl' hW hh0 hh1)
  rintro ⟨l, d⟩ ⟨hf, hl, hd⟩
  exact ⟨hf, hl, hd, d2_found_end hf hp⟩

@[local step]
theorem d2_continue_spec (s : Slice Std.U8) {W : Std.Usize} (prev : Array Std.U32 W)
    (p st l d minl depth nice : Std.Usize) (hlit : Std.I32)
    (hp : p.val + 8 ≤ s.length) (hst : st.val ≤ p.val + 2)
    (hf : FoundAt s p.val l.val d.val) (hl : l.val ≤ 258) (hd : d.val ≤ 32768)
    (hminl : 3 ≤ minl.val) (hminl8 : minl.val ≤ 8)
    (hW : 0 < W.val) (hh0 : 0 ≤ hlit.val) (hh1 : hlit.val ≤ 1000000) :
    slot.d2_continue s prev p st l d minl depth nice hlit ⦃ fun r =>
      FoundAt s p.val r.1.val r.2.val ∧ r.1.val ≤ 258 ∧ r.2.val ≤ 32768 ∧
      p.val + r.1.val ≤ s.length ⦄ := by
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  have hpl := d2_found_end hf (by omega)
  rw [slot.d2_continue]
  step*
  repeat' (split <;> step*)
  all_goals first
    | exact ⟨hf, hl, hd, hpl⟩
    | exact ⟨by assumption, by scalar_tac, by scalar_tac, by scalar_tac⟩
    | scalar_tac

@[local step]
theorem d2_current_spec (s : Slice Std.U8) {H W : Std.Usize}
    (head : Array Std.U32 H) (prev : Array Std.U32 W) (p st : Std.Usize) (mask : Std.U32)
    (minl depth lazy nice : Std.Usize) (hlit : Std.I32) (mode : Std.Usize)
    (hp : p.val + 8 ≤ s.length) (hst : st.val ≤ p.val + 2)
    (hminl : 3 ≤ minl.val) (hminl8 : minl.val ≤ 8)
    (hH : 0 < H.val) (hW : 0 < W.val)
    (hh0 : 0 ≤ hlit.val) (hh1 : hlit.val ≤ 1000000) :
    slot.d2_current s head prev p st mask minl depth lazy nice hlit mode ⦃ fun r =>
      FoundAt s p.val r.1.val r.2.1.val ∧ r.1.val ≤ 258 ∧ r.2.1.val ≤ 32768 ∧
      p.val + r.1.val ≤ s.length ⦄ := by
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  rw [slot.d2_current]
  step*
  repeat' (split <;> step*)
  all_goals first
    | exact ⟨by assumption, by scalar_tac, by scalar_tac, by scalar_tac⟩
    | scalar_tac

@[local step]
theorem d2_lazy_spec (s : Slice Std.U8) {W : Std.Usize} (prev : Array Std.U32 W)
    (q st «have» minl ldep nice : Std.Usize) (hlit : Std.I32)
    (l d lazy mode : Std.Usize) (budget : Std.U32)
    (hq : q.val + 8 ≤ s.length) (hst : st.val ≤ q.val + 2)
    (hhave : q.val + «have».val ≤ s.length) (hhave258 : «have».val ≤ 258)
    (hminl : 3 ≤ minl.val) (hminl8 : minl.val ≤ 8)
    (hl : l.val ≤ 258) (hd : d.val ≤ 32768)
    (hW : 0 < W.val) (hh0 : 0 ≤ hlit.val) (hh1 : hlit.val ≤ 1000000) :
    slot.d2_lazy s prev q st «have» minl ldep nice hlit l d lazy mode budget ⦃ fun r =>
      FoundAt s q.val r.1.val r.2.val ∧ r.1.val ≤ 258 ∧ r.2.val ≤ 32768 ∧
      q.val + r.1.val ≤ s.length ⦄ := by
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  rw [slot.d2_lazy]
  step*
  repeat' (split <;> step*)
  all_goals first
    | exact ⟨by assumption, by scalar_tac, by scalar_tac, by scalar_tac⟩
    | scalar_tac

-- New helpers were checked using the stronger result; restore the existing
-- search specification for all unchanged downstream proof scripts.
attribute [-step] d2_find_bounded_spec
attribute [local step] find_spec
