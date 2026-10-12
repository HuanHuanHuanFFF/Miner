/- C4 proof draft; not compiled. The unchanged match_len proof supplies every byte fact. -/
theorem c4_write_post {input : Slice Std.U8} {out out1 : Slice Std.U32}
    {pos d full ntok ntok1 end1 a : Std.Usize} {v : Std.U32}
    (hout : input.length ≤ out.length) (hntok : ntok.val ≤ pos.val)
    (hdec : LZ77.decode (toks out ntok.val) = some ((bytes input).take pos.val))
    (hf3 : 3 ≤ full.val) (hf258 : full.val ≤ 258)
    (hd1 : 1 ≤ d.val) (hd32 : d.val ≤ 32768) (hdpos : d.val ≤ pos.val)
    (hfull : pos.val + full.val ≤ input.length)
    (hm : Matches input a.val pos.val full.val) (ha : a.val = pos.val - d.val)
    (hout1 : out1 = out.set ntok v) (hv : v.val = LZ77.mkMatch d.val full.val)
    (hntok1 : ntok1.val = ntok.val + 1) (hend1 : end1.val = pos.val + full.val) :
    pos.val < end1.val ∧ end1.val ≤ input.length ∧ ntok1.val ≤ end1.val ∧
    out1.length = out.length ∧
    LZ77.decode (toks out1 ntok1.val) = some ((bytes input).take end1.val) := by
  have hidx : ntok.val < out.length := by omega
  have hm' : Matches input (pos.val - d.val) pos.val full.val := by
    rw [← ha]
    exact hm
  refine ⟨by omega, by omega, by omega, ?_, ?_⟩
  · rw [hout1]
    simp only [Std.Slice.set_length]
  · rw [hout1, hntok1, hend1]
    exact emit_match input out ntok pos.val d.val full.val v hdec hidx hd1 hdpos hd32
      hf3 hf258 hfull hm' hv

@[local step]
theorem c4_emit_step_spec (input : Slice Std.U8) (out : Slice Std.U32)
    (pos d l lits ntok : Std.Usize)
    (hout : input.length ≤ out.length) (hpos : pos.val < input.length)
    (hntok : ntok.val ≤ pos.val)
    (hdec : LZ77.decode (toks out ntok.val) = some ((bytes input).take pos.val)) :
    slot.c4_emit_step input out pos d l lits ntok ⦃ fun r =>
      pos.val < r.1.2.val ∧ r.1.2.val ≤ input.length ∧ r.1.1.val ≤ r.1.2.val ∧
      r.2.length = out.length ∧
      LZ77.decode (toks r.2 r.1.1.val) = some ((bytes input).take r.1.2.val) ⦄ := by
  rw [slot.c4_emit_step]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  step*
  all_goals first
    | (apply c4_write_post (input := input) (out := out) (pos := pos)
          (d := d) (full := full) (ntok := ntok)
       all_goals first | assumption | (simp only [LZ77.mkMatch, LZ77.MATCH_BASE]; scalar_tac))
    | (exact ⟨by scalar_tac, by scalar_tac, by scalar_tac,
          by assumption, by assumption⟩)
    | (apply Std.WP.spec_mono (emit_step_spec input out pos d l lits ntok
          hout hpos hntok hdec)
       intro r hr
       exact hr)
    | (apply Std.WP.spec_mono (emit_lits_spec input out pos lits ntok
          hout (by omega) hntok hdec)
       rintro ⟨⟨t, k⟩, o⟩ ⟨h1, h2, h3, h4, h5⟩
       exact ⟨by omega, h2, h3, h4, h5⟩)
