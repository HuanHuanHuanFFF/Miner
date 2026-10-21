/- E1 proof draft, UNCOMPILED. The direct short branch includes len8.
   It uses the same word8_prefix theorem as the original masked tail. -/
theorem e1_mask_match {input : Slice Std.U8} {a b len : Std.Usize}
    {x y z w : Std.U64} {sh : Std.U32}
    (hd : len.val ≤ 8)
    (hx : x.val = word8 input a.val) (hy : y.val = word8 input b.val)
    (hz : z.val = (x ^^^ y).val) (hw : w.val = z.val >>> sh.val)
    (hw0 : w.val = 0) (hsh : sh.val = 64 - 8 * len.val) :
    Matches input a.val b.val len.val := by
  have h0 : (x.val ^^^ y.val) >>> sh.val = 0 := by
    rw [← UScalar.val_xor, ← hz, ← hw, hw0]
  rw [Nat.shiftRight_xor_distrib] at h0
  have heq := nat_xor_eq_zero h0
  apply word8_prefix input a.val b.val len.val hd
  rw [← hx, ← hy, ← hsh]
  simpa only [Nat.shiftRight_eq_div_pow] using heq

 := by
  rw [slot.u118_same]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  step*
  all_goals first
    | (intro hr; exfalso; scalar_tac)
    | (intro hr
       apply e1_mask_match (input := s) (a := a) (b := b) (len := len)
       all_goals first | assumption | scalar_tac)
    | (apply Std.WP.spec_bind (same_loop0_spec s a b len 0#usize 1#usize
         ha hb hlen (by simp) (LZ77.Matches.zero s a.val b.val))
       rintro ⟨k, ok⟩ ⟨hk, hm, hok⟩
       simp only at hk hm hok
       step*
       intro _
       exact Matches.mask hm (by assumption) (by assumption) (by assumption)
         (by assumption) (by assumption) (by assumption) (by assumption)
         (by scalar_tac) (by scalar_tac) (by scalar_tac))
