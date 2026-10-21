import Lz77
import Slot
import Mathlib.Data.Nat.Log
import Mathlib.Tactic.IntervalCases
import Mathlib.Tactic.FailIfNoProgress

attribute [local irreducible] slot.g_match slot.g_eval slot.g3_eval slot.gh_eval slot.g_lazy_eval slot.g3_lazy_eval slot.g_choose slot.g_plain_choose slot.g_scan slot.g3_scan slot.gh_scan slot.g_lazy slot.g3_lazy slot.gh_lazy slot.g_scan_loop slot.g3_scan_loop slot.gh_scan_loop slot.g_scan_loop.body slot.g3_scan_loop.body slot.gh_scan_loop.body slot.public_emit_join slot.emit_lits slot.emit_lits_loop slot.emit_lits_loop.body slot.main_parse_a_loop.body slot.main_parse_b_loop.body slot.main_parse_high_loop.body


namespace A2FastPureChoice
open Aeneas Aeneas.Std Result
@[scoped step]
theorem choose_ok {α : Type} (c : Prop) [Decidable c] (a b : α) :
    (if c then ok a else ok b) ⦃ fun _ => True ⦄ := by
  split <;> simp only [Std.WP.spec_ok]
end A2FastPureChoice

set_option linter.unusedTactic false
set_option linter.unreachableTactic false
set_option linter.unusedVariables false
set_option linter.unusedSimpArgs false
set_option linter.unusedTactic false
set_option linter.unreachableTactic false
set_option linter.unusedVariables false
set_option linter.unusedSimpArgs false

/- Completed development module: BackLemmas -/
namespace Submission
open Aeneas Aeneas.Std Result ControlFlow
open LZ77 (toks bytes bytes_length bytes_getElem! toks_update bytes_congr Matches emit_lit emit_match ite_ok)
set_option maxRecDepth 8192
set_option maxHeartbeats 10000000

def AMatchAt (s : Slice Std.U8) (p l d : Nat) : Prop :=
  3 ≤ l ∧ l ≤ 258 ∧ p + l ≤ s.length ∧ 1 ≤ d ∧ d ≤ 32768 ∧ d ≤ p ∧ Matches s (p - d) p l

theorem a_copyN_take_prefix (acc : List Nat) (d : Nat) :
    ∀ n, (LZ77.copyN acc d n).take acc.length = acc := by
  intro n
  induction n with
  | zero => simp [LZ77.copyN]
  | succ m ih =>
    simp only [LZ77.copyN]
    rw [List.take_append_of_le_length (by simp)]
    exact ih

/-- Every token decodes to at least one byte, so a stream is never longer than its output. -/
theorem a_foldlM_emit_length : ∀ (ts : List Nat) (init acc : List Nat),
    ts.foldlM LZ77.emit init = some acc → init.length + ts.length ≤ acc.length := by
  intro ts
  induction ts with
  | nil => intro init acc h; simp at h; subst h; simp
  | cons t ts ih =>
    intro init acc h
    simp only [List.foldlM_cons] at h
    cases he : LZ77.emit init t with
    | none => rw [he] at h; simp at h
    | some a =>
      rw [he] at h
      simp only [Option.bind_eq_bind, Option.bind_some] at h
      have h1 := ih a acc h
      have h2 : init.length + 1 ≤ a.length := by
        simp only [LZ77.emit] at he
        split at he
        · simp at he; subst he; simp
        · split at he
          · split at he
            · simp at he; subst he; rw [LZ77.copyN_length]; simp only [LZ77.tokLen]; omega
            · simp at he
          · simp at he
      simp only [List.length_cons]
      omega

theorem a_decode_length_le {ts acc : List Nat} (h : LZ77.decode ts = some acc) :
    ts.length ≤ acc.length := by
  have := a_foldlM_emit_length ts [] acc h
  simpa using this

/-- Dropping a literal from the end of a stream that decodes to a prefix. -/
theorem a_decode_pop_lit {ts : List Nat} {t : Nat} {inp : List Nat} {p : Nat}
    (hp : p ≤ inp.length) (hd : LZ77.decode (ts ++ [t]) = some (inp.take p)) (ht : t < 256) :
    1 ≤ p ∧ LZ77.decode ts = some (inp.take (p - 1)) := by
  rw [LZ77.decode_snoc] at hd
  cases hts : LZ77.decode ts with
  | none => rw [hts] at hd; simp at hd
  | some acc =>
    rw [hts] at hd
    simp only [Option.bind_some, LZ77.emit, if_pos ht] at hd
    have hacc : acc ++ [t] = inp.take p := Option.some.inj hd
    have hlen : acc.length + 1 = p := by
      have := congrArg List.length hacc
      simp [List.length_take] at this; omega
    refine ⟨by omega, ?_⟩
    apply congrArg some
    have := congrArg (List.take acc.length) hacc
    rw [List.take_append_of_le_length (le_refl _), List.take_length, List.take_take] at this
    rw [this, show min acc.length p = p - 1 by omega]

/-- Dropping a match token from the end of a stream that decodes to a prefix. -/
theorem a_decode_pop_match {ts : List Nat} {t : Nat} {inp : List Nat} {p : Nat}
    (hp : p ≤ inp.length) (hd : LZ77.decode (ts ++ [t]) = some (inp.take p)) (ht : 256 ≤ t) :
    LZ77.tokLen t ≤ p ∧ LZ77.decode ts = some (inp.take (p - LZ77.tokLen t)) := by
  rw [LZ77.decode_snoc] at hd
  cases hts : LZ77.decode ts with
  | none => rw [hts] at hd; simp at hd
  | some acc =>
    rw [hts] at hd
    simp only [Option.bind_some, LZ77.emit, if_neg (show ¬ t < 256 by omega)] at hd
    split at hd
    · split at hd
      · have hacc : LZ77.copyN acc (LZ77.tokDist t) (LZ77.tokLen t) = inp.take p := Option.some.inj hd
        have hlen : acc.length + LZ77.tokLen t = p := by
          have := congrArg List.length hacc
          simp [List.length_take] at this; omega
        refine ⟨by omega, ?_⟩
        apply congrArg some
        have := congrArg (List.take acc.length) hacc
        rw [a_copyN_take_prefix, List.take_take] at this
        rw [this, show min acc.length p = p - LZ77.tokLen t by omega]
      · simp at hd
    · simp at hd

/-- The first `nt` tokens are the first `nt - 1` and token `nt - 1`. -/
theorem a_toks_pop (out : Slice Std.U32) (nt : Nat) (h0 : 0 < nt) (hle : nt ≤ out.length) :
    toks out nt = toks out (nt - 1) ++ [(out.val[nt - 1]!).val] := by
  have hlt : nt - 1 < out.val.length := by
    have : out.length = out.val.length := rfl
    omega
  simp only [toks]
  conv_lhs => rw [show nt = (nt - 1) + 1 by omega]
  rw [List.take_add_one, List.getElem?_eq_getElem hlt, Option.toList_some, List.map_append]
  simp [getElem!_pos out.val (nt - 1) hlt]

theorem a_toks_length (out : Slice Std.U32) (nt : Nat) (h : nt ≤ out.length) :
    (toks out nt).length = nt := by
  simp only [toks, List.length_map, List.length_take]
  have : out.length = out.val.length := rfl
  omega

/-! ## 8. The decoding invariant `ADec` and the two token writers

`ADec s out nt p`: `p ≤ n`, `nt ≤ p`, `n ≤ out.length`, and the first `nt` tokens decode to the
first `p` bytes. Every loop carries it (with `out.length` fixed); each write steps it
(`ADec.lit`, `ADec.match`), each popped token retracts it (`ADec.pop_lit`, `ADec.pop_match`),
and `ADec.done` is the obligation once `p = n`. The `_step` forms take exactly the facts
`step*` leaves after `put_lit`/`put_match`. -/

/-- `nt` tokens written into `out` decode to the first `p` input bytes (`out` long enough). -/
def ADec (s : Slice Std.U8) (out : Slice Std.U32) (nt p : Nat) : Prop :=
  p ≤ s.length ∧ nt ≤ p ∧ s.length ≤ out.length ∧
    LZ77.decode (toks out nt) = some ((bytes s).take p)

theorem ADec.init (input : Slice Std.U8) (out : Slice Std.U32) (h : input.length ≤ out.length) :
    ADec input out (0#usize).val (0#usize).val :=
  ⟨by simp, by simp, h, by simp [toks, LZ77.decode]⟩

/-- Writing the literal `s[p]` at `out[nt]`. -/
theorem ADec.lit {s : Slice Std.U8} {out : Slice Std.U32} {nt p : Nat} (h : ADec s out nt p)
    (hp : p < s.length) (ntU : Std.Usize) (hnt : ntU.val = nt) (v : Std.U32)
    (hv : v.val = (s.val[p]!).val) :
    ADec s (out.set ntU v) (nt + 1) (p + 1) := by
  obtain ⟨hps, hntp, hso, hde⟩ := h
  have hntl : ntU.val < out.length := by omega
  refine ⟨by omega, by omega, by rw [Std.Slice.set_length]; exact hso, ?_⟩
  rw [← hnt]
  refine emit_lit s out ntU p v (by rw [hnt]; exact hde) hp hntl ?_
  have hpl : p < s.val.length := hp
  rw [hv, bytes_getElem! s p hpl, getElem!_pos s.val p hpl]

/-- Writing the match token `(d, l)` at `out[nt]`. -/
theorem ADec.match {s : Slice Std.U8} {out : Slice Std.U32} {nt p l d : Nat} (h : ADec s out nt p)
    (hm : AMatchAt s p l d) (ntU : Std.Usize) (hnt : ntU.val = nt) (v : Std.U32)
    (hv : v.val = LZ77.mkMatch d l) :
    ADec s (out.set ntU v) (nt + 1) (p + l) := by
  obtain ⟨hps, hntp, hso, hde⟩ := h
  obtain ⟨h3, h258, hpl, hd1, hd32, hdp, hmm⟩ := hm
  have hntl : ntU.val < out.length := by omega
  refine ⟨by omega, by omega, by rw [Std.Slice.set_length]; exact hso, ?_⟩
  rw [← hnt]
  exact emit_match s out ntU p d l v (by rw [hnt]; exact hde) hntl hd1 hdp hd32 h3 h258 hpl hmm hv

/-- Retracting a trailing literal. -/
theorem ADec.pop_lit {s : Slice Std.U8} {out : Slice Std.U32} {nt p : Nat} (h : ADec s out nt p)
    (h0 : 0 < nt) (hle : nt ≤ out.length) (ht : (out.val[nt - 1]!).val < 256) :
    1 ≤ p ∧ ADec s out (nt - 1) (p - 1) := by
  obtain ⟨hps, hntp, hso, hde⟩ := h
  rw [a_toks_pop out nt h0 hle] at hde
  obtain ⟨hp1, hde'⟩ := a_decode_pop_lit (by simpa using hps) hde ht
  exact ⟨hp1, by omega, by omega, hso, hde'⟩

/-- Retracting a trailing match token (of length `tokLen t`). -/
theorem ADec.pop_match {s : Slice Std.U8} {out : Slice Std.U32} {nt p : Nat} (h : ADec s out nt p)
    (h0 : 0 < nt) (hle : nt ≤ out.length) (ht : 256 ≤ (out.val[nt - 1]!).val) :
    LZ77.tokLen (out.val[nt - 1]!).val ≤ p ∧
      ADec s out (nt - 1) (p - LZ77.tokLen (out.val[nt - 1]!).val) := by
  obtain ⟨hps, hntp, hso, hde⟩ := h
  rw [a_toks_pop out nt h0 hle] at hde
  obtain ⟨hw, hde'⟩ := a_decode_pop_match (by simpa using hps) hde ht
  have hlen := a_decode_length_le hde'
  rw [a_toks_length out (nt - 1) (by omega), List.length_take, LZ77.bytes_length] at hlen
  exact ⟨hw, by omega, by omega, hso, hde'⟩

/-- All `n` bytes consumed: the stream is valid. -/
theorem ADec.done {s : Slice Std.U8} {out : Slice Std.U32} {nt p : Nat} (h : ADec s out nt p)
    (hp : s.length ≤ p) : nt ≤ s.length ∧ LZ77.Valid (bytes s) (toks out nt) := by
  obtain ⟨hps, hntp, hso, hde⟩ := h
  refine ⟨by omega, ?_⟩
  unfold LZ77.Valid
  rw [hde, show p = s.length by omega, ← LZ77.bytes_length, List.take_length]

theorem AMatchAt.back_lit {s : Slice Std.U8} {p l d : Nat} (h : AMatchAt s p l d) (hl : l < 258)
    (hdp : d < p) (heq : s.val[p - 1]! = s.val[p - 1 - d]!) : AMatchAt s (p - 1) (l + 1) d := by
  obtain ⟨h3, h258, hpl, hd1, hd32, _, hm⟩ := h
  refine ⟨by omega, by omega, by omega, hd1, hd32, by omega, ?_⟩
  intro k hk
  rcases Nat.eq_zero_or_pos k with hk0 | hk0
  · subst hk0
    rw [Nat.add_zero, Nat.add_zero, show p - 1 - d = p - 1 - d by rfl]
    exact heq
  · have := hm (k - 1) (by omega)
    rw [show p - 1 + k = p + (k - 1) by omega, show p - 1 - d + k = p - d + (k - 1) by omega]
    exact this

/-- A whole earlier match of `w` bytes whose bytes also match at distance `d`. -/
theorem AMatchAt.back_match {s : Slice Std.U8} {p l d w : Nat} (h : AMatchAt s p l d)
    (hlw : l + w ≤ 258) (hw : w ≤ p) (hdw : d ≤ p - w) (hmw : Matches s (p - w - d) (p - w) w) :
    AMatchAt s (p - w) (l + w) d := by
  obtain ⟨h3, h258, hpl, hd1, hd32, _, hm⟩ := h
  refine ⟨by omega, by omega, by omega, hd1, hd32, hdw, ?_⟩
  intro k hk
  rcases Nat.lt_or_ge k w with hkw | hkw
  · have := hmw k hkw
    rw [show p - w - d = p - w - d by rfl] at this
    exact this
  · have := hm (k - w) (by omega)
    rw [show p - w + k = p + (k - w) by omega, show p - w - d + k = p - d + (k - w) by omega]
    exact this

/-- The state of the backward merge: `nt` tokens decode to `p` bytes, `out` keeps its length
    `L`, the pending match `(l, d)` at `p` is real and ends at `E`, and `p` never grew past `P0`. -/
def ABackInv (input : Slice Std.U8) (L d E P0 : Nat) (out : Slice Std.U32) (nt p l : Nat) : Prop :=
  ADec input out nt p ∧ out.length = L ∧ AMatchAt input p l d ∧ p + l = E ∧ p ≤ P0

/-- Absorbing the literal `out[nt-1]` whose byte also matches at distance `d`. The hypotheses
    are ordered for `step*`'s facts: the new state `(i1, i2, l1)` is fixed by the goal, `t`, `x`,
    `y`, `i4` by `assumption`, everything else by `(first | omega | scalar_tac)`. -/
theorem ABackInv.lit {input : Slice Std.U8} {out : Slice Std.U32} {L d E P0 : Nat}
    {nt p l i1 i2 i4 l1 : Std.Usize} {t : Std.U32} {x y : Std.U8}
    (h : ABackInv input L d E P0 out nt.val p.val l.val)
    (hi1 : i1.val = nt.val - 1) (hntl : nt.val ≤ out.length) (hnt0 : 1 ≤ nt.val)
    (hi1l : i1.val < out.val.length) (ht : t = out.val[i1.val]) (ht256 : t < 256#u32)
    (hi2 : i2.val = p.val - 1) (hi2l : i2.val < input.val.length) (hx : x = input.val[i2.val])
    (hxy : x = y) (hi4 : i4.val = i2.val - d) (hi4l : i4.val < input.val.length)
    (hy : y = input.val[i4.val]) (hl : l.val < 258) (hdp : d < p.val)
    (hl1 : l1.val = l.val + 1) :
    ABackInv input L d E P0 out i1.val i2.val l1.val := by
  obtain ⟨hdec, hL, hm, hE, hP⟩ := h
  have ht' : (out.val[nt.val - 1]!).val < 256 := by
    rw [← hi1, getElem!_pos out.val i1.val hi1l, ← ht]; (first | omega | scalar_tac)
  obtain ⟨hp1, hdec'⟩ := ADec.pop_lit hdec (by omega) hntl ht'
  have heq : input.val[p.val - 1]! = input.val[p.val - 1 - d]! := by
    rw [← hi2, getElem!_pos input.val i2.val hi2l, show i2.val - d = i4.val by omega,
      getElem!_pos input.val i4.val hi4l, ← hx, ← hy, hxy]
  have hm' := AMatchAt.back_lit hm hl hdp heq
  rw [hi1, hi2, hl1]
  exact ⟨hdec', hL, hm', by omega, by omega⟩

/-- Absorbing the whole match token `t = out[nt-1]` (length `w`) whose bytes also match at `d`.
    The new state `(i1, i10, i9)` is fixed by the goal; `t`, and `(i12, i11, w)` through
    `same`'s postcondition, by `assumption`; the rest by `(first | omega | scalar_tac)`. -/
theorem ABackInv.match {input : Slice Std.U8} {out : Slice Std.U32} {L d E P0 : Nat}
    {nt p l i1 w i9 i10 i11 i12 : Std.Usize} {t : Std.U32}
    (h : ABackInv input L d E P0 out nt.val p.val l.val)
    (hi1 : i1.val = nt.val - 1) (hntl : nt.val ≤ out.length) (hnt0 : 1 ≤ nt.val)
    (hi1l : i1.val < out.val.length) (ht : t = out.val[i1.val])
    (hsame : i12.val = 1 → Matches input i11.val i10.val w.val) (hi12 : i12 = 1#usize)
    (ht24 : 16777216 ≤ t.val) (hwv : w.val = (t.val - 16777216) % 256 + 3)
    (hi9 : i9.val = l.val + w.val) (hi9' : i9.val ≤ 258) (hi10 : i10.val = p.val - w.val)
    (hwp : w.val ≤ p.val) (hdw : d ≤ i10.val) (hi11 : i11.val = i10.val - d) :
    ABackInv input L d E P0 out i1.val i10.val i9.val := by
  obtain ⟨hdec, hL, hm, hE, hP⟩ := h
  have htv : (out.val[nt.val - 1]!).val = t.val := by
    rw [← hi1, getElem!_pos out.val i1.val hi1l, ← ht]
  have hwv' : w.val = LZ77.tokLen (out.val[nt.val - 1]!).val := by
    rw [htv, hwv]
    simp only [LZ77.tokLen, LZ77.MATCH_BASE]
  obtain ⟨hwl, hdec'⟩ := ADec.pop_match hdec (by omega) hntl (by omega)
  rw [← hwv'] at hdec'
  have hmw : Matches input (p.val - w.val - d) (p.val - w.val) w.val := by
    have := hsame (by rw [hi12]; rfl)
    rw [hi11, hi10] at this
    exact this
  have hm' := AMatchAt.back_match hm (by omega) hwp (by omega) hmw
  rw [hi1, hi10, hi9]
  exact ⟨hdec', hL, hm', by omega, by omega⟩

/-- The state after `part_merge` (a shortened earlier token, a longer pending match). -/
theorem ABackInv.part {input : Slice Std.U8} {out out1 : Slice Std.U32} {L d E P0 : Nat}
    {nt nt1 p l : Nat} {p1 l1 : Std.Usize} (h : ABackInv input L d E P0 out nt p l)
    (hlen : out1.length = out.length) (hdec : ADec input out1 nt1 p1.val)
    (hm : AMatchAt input p1.val l1.val d) (hE : p1.val + l1.val = p + l) (hp : p1.val ≤ p) :
    ABackInv input L d E P0 out1 nt1 p1.val l1.val := by
  obtain ⟨_, hL, _, hE0, hP⟩ := h
  exact ⟨hdec, by rw [hlen, hL], hm, by omega, by omega⟩

theorem Matches.a_cons {input : Slice Std.U8} {a b n : Nat} (h : Matches input (a + 1) (b + 1) n)
    (heq : input.val[b]! = input.val[a]!) : Matches input a b (n + 1) := by
  intro k hk
  rcases Nat.eq_zero_or_pos k with h0 | hk0
  · subst h0; simpa using heq
  · have := h (k - 1) (by omega)
    rw [show b + 1 + (k - 1) = b + k by omega, show a + 1 + (k - 1) = a + k by omega] at this
    exact this

/-- Two adjacent matches at the same distance are one match. -/
theorem Matches.a_append {input : Slice Std.U8} {a b k l : Nat} (h1 : Matches input a b k)
    (h2 : Matches input (a + k) (b + k) l) : Matches input a b (k + l) := by
  intro j hj
  rcases Nat.lt_or_ge j k with hjk | hjk
  · exact h1 j hjk
  · have := h2 (j - k) (by omega)
    rw [show b + k + (j - k) = b + j by omega, show a + k + (j - k) = a + j by omega] at this
    exact this

/-- The `k` bytes before `p` also match at distance `d`: the match starts `k` bytes earlier. -/
theorem AMatchAt.back_part {s : Slice Std.U8} {p l d k : Nat} (h : AMatchAt s p l d)
    (hmk : Matches s (p - k - d) (p - k) k) (hlk : l + k ≤ 258) (hdk : d + k ≤ p) :
    AMatchAt s (p - k) (l + k) d := by
  obtain ⟨h3, h258, hpl, hd1, hd32, _, hm⟩ := h
  refine ⟨by omega, hlk, by omega, hd1, hd32, by omega, ?_⟩
  have hm' : Matches s (p - k - d + k) (p - k + k) l := by
    rw [show p - k - d + k = p - d by omega, show p - k + k = p by omega]; exact hm
  have := Matches.a_append hmk hm'
  rw [show k + l = l + k by omega] at this
  exact this

/-- One step of the counting loop: the byte at `p - 1 - k` matches at distance `d`. -/
theorem Matches.a_back_step {input : Slice Std.U8} {p d k : Nat} {i4 i7 k1 : Std.Usize}
    {x y : Std.U8} (h : Matches input (p - k - d) (p - k) k) (hdk : d + k < p)
    (hi4 : i4.val = p - 1 - k) (hi4l : i4.val < input.val.length) (hx : x = input.val[i4.val])
    (hi7 : i7.val = p - 1 - k - d) (hi7l : i7.val < input.val.length)
    (hy : y = input.val[i7.val]) (hxy : x = y) (hk1 : k1.val = k + 1) :
    Matches input (p - k1.val - d) (p - k1.val) k1.val := by
  rw [hk1]
  apply Matches.a_cons
  · rw [show p - (k + 1) - d + 1 = p - k - d by omega, show p - (k + 1) + 1 = p - k by omega]
    exact h
  · rw [show p - (k + 1) - d = i7.val by omega, show p - (k + 1) = i4.val by omega,
      getElem!_pos input.val i4.val hi4l, getElem!_pos input.val i7.val hi7l, ← hx, ← hy, hxy]



/-! New lemmas: successful backward decoding recovers the old match equality. -/

theorem copyN_periodic (acc : List Nat) (d : Nat) (hd1 : 1 ≤ d) (hdp : d ≤ acc.length) :
    ∀ n k, k < n →
      (LZ77.copyN acc d n)[acc.length + k]! =
        (LZ77.copyN acc d n)[acc.length + k - d]! := by
  intro n
  induction n with
  | zero => intro k hk; omega
  | succ n ih =>
    intro k hk
    rw [LZ77.copyN]
    have hlen : (LZ77.copyN acc d n).length = acc.length + n := LZ77.copyN_length ..
    rcases Nat.lt_or_ge k n with hkn | hkn
    · rw [List.getElem!_append_left _ _ _ (by omega),
        List.getElem!_append_left _ _ _ (by omega)]
      exact ih k hkn
    · have hke : k = n := by omega
      subst k
      rw [List.getElem!_append_right _ _ _ (by omega),
        List.getElem!_append_left _ _ _ (by omega)]
      simp [hlen]

theorem getElemBang_take (inp : List Nat) (p k : Nat)
    (hk : k < p) (hp : p ≤ inp.length) : (inp.take p)[k]! = inp[k]! := by
  rw [getElem!_pos _ _ (by simp; omega), getElem!_pos _ _ (by omega), List.getElem_take]

theorem decode_pop_match_semantics {ts : List Nat} {t : Nat} {inp : List Nat} {p : Nat}
    (hp : p ≤ inp.length) (hd : LZ77.decode (ts ++ [t]) = some (inp.take p)) (ht : 256 ≤ t) :
    LZ77.tokLen t ≤ p ∧
      LZ77.decode ts = some (inp.take (p - LZ77.tokLen t)) ∧
      1 ≤ LZ77.tokDist t ∧ LZ77.tokDist t ≤ 32768 ∧
      LZ77.tokDist t ≤ p - LZ77.tokLen t ∧
      ∀ k < LZ77.tokLen t,
        inp[p - LZ77.tokLen t + k]! = inp[p - LZ77.tokLen t - LZ77.tokDist t + k]! := by
  obtain ⟨hlp, hprev⟩ := a_decode_pop_match hp hd ht
  refine ⟨hlp, hprev, ?_⟩
  rw [LZ77.decode_snoc, hprev] at hd
  simp only [Option.bind_some, LZ77.emit, if_neg (show ¬ t < 256 by omega)] at hd
  split at hd
  · rename_i htlegal
    split at hd
    · rename_i hdpos
      have hcopy : LZ77.copyN (inp.take (p - LZ77.tokLen t)) (LZ77.tokDist t)
          (LZ77.tokLen t) = inp.take p := Option.some.inj hd
      have hdist1 : 1 ≤ LZ77.tokDist t := by unfold LZ77.tokDist; omega
      have hdist32 : LZ77.tokDist t ≤ 32768 := by
        simp only [LZ77.MATCH_BASE, LZ77.TOK_LIMIT] at htlegal
        unfold LZ77.tokDist LZ77.MATCH_BASE
        omega
      have hlen : (inp.take (p - LZ77.tokLen t)).length = p - LZ77.tokLen t := by
        simp only [List.length_take]; omega
      refine ⟨hdist1, hdist32, by simpa [hlen] using hdpos, ?_⟩
      intro k hk
      have heq := copyN_periodic (inp.take (p - LZ77.tokLen t)) (LZ77.tokDist t)
        hdist1 hdpos (LZ77.tokLen t) k hk
      rw [hlen, hcopy, getElemBang_take inp p _ (by omega) hp,
        getElemBang_take inp p _ (by omega) hp] at heq
      rw [show p - LZ77.tokLen t + k - LZ77.tokDist t =
        p - LZ77.tokLen t - LZ77.tokDist t + k by omega] at heq
      exact heq
    · simp at hd
  · simp at hd

theorem ADec.pop_match_full {s : Slice Std.U8} {out : Slice Std.U32} {nt p : Nat}
    (h : ADec s out nt p) (h0 : 0 < nt) (hle : nt ≤ out.length)
    (ht : 256 ≤ (out.val[nt - 1]!).val) :
    ADec s out (nt - 1) (p - LZ77.tokLen (out.val[nt - 1]!).val) ∧
      AMatchAt s (p - LZ77.tokLen (out.val[nt - 1]!).val)
        (LZ77.tokLen (out.val[nt - 1]!).val) (LZ77.tokDist (out.val[nt - 1]!).val) := by
  have hde := h.2.2.2
  rw [a_toks_pop out nt h0 hle] at hde
  obtain ⟨hw, _, hd1, hd32, hdp, hm⟩ := decode_pop_match_semantics
    (by simpa using h.1) hde ht
  have hp : p ≤ s.length := h.1
  have hpsum : p - LZ77.tokLen (out.val[nt - 1]!).val +
      LZ77.tokLen (out.val[nt - 1]!).val = p := by omega
  refine ⟨(ADec.pop_match h h0 hle ht).2, ?_⟩
  have hl3 : 3 ≤ LZ77.tokLen (out.val[nt - 1]!).val := by
    unfold LZ77.tokLen; omega
  have hl258 : LZ77.tokLen (out.val[nt - 1]!).val ≤ 258 := by
    unfold LZ77.tokLen; omega
  refine ⟨hl3, hl258, by omega, hd1, hd32, hdp, ?_⟩
  intro k hk
  have heq := hm k hk
  rw [LZ77.bytes_getElem! s _ (by omega), LZ77.bytes_getElem! s _ (by omega)] at heq
  rw [getElem!_pos s.val (p - LZ77.tokLen (out.val[nt - 1]!).val + k) (by simpa using (show
      p - LZ77.tokLen (out.val[nt - 1]!).val + k < s.length by omega)),
    getElem!_pos s.val (p - LZ77.tokLen (out.val[nt - 1]!).val - LZ77.tokDist (out.val[nt - 1]!).val + k)
      (by simpa using (show p - LZ77.tokLen (out.val[nt - 1]!).val -
        LZ77.tokDist (out.val[nt - 1]!).val + k < s.length by omega))]
  exact UScalar.eq_of_val_eq heq

theorem AMatchAt.prefix {s : Slice Std.U8} {p l d nl : Nat}
    (h : AMatchAt s p l d) (hnl3 : 3 ≤ nl) (hnl : nl ≤ l) :
    AMatchAt s p nl d := by
  obtain ⟨h3, h258, hpl, hd1, hd32, hdp, hm⟩ := h
  exact ⟨hnl3, by omega, by omega, hd1, hd32, hdp, Matches.mono hm hnl⟩

def NearPrefix (input : Slice Std.U8) (p l d : Nat) : Prop :=
  d = 0 ∨ AMatchAt input p l d

theorem old_prefix_near {input : Slice Std.U8} {out : Slice Std.U32} {nt p w nl oldd : Nat}
    (hdec : ADec input out nt p) (h0 : 0 < nt) (hle : nt ≤ out.length)
    (ht : 256 ≤ (out.val[nt - 1]!).val)
    (hw : w = LZ77.tokLen (out.val[nt - 1]!).val)
    (hd : oldd = LZ77.tokDist (out.val[nt - 1]!).val)
    (hnl3 : 3 ≤ nl) (hnl : nl ≤ w) : NearPrefix input (p - w) nl oldd := by
  have hm := (ADec.pop_match_full hdec h0 hle ht).2
  rw [← hw, ← hd] at hm
  exact Or.inr (AMatchAt.prefix hm hnl3 hnl)

theorem fold_part_post {input : Slice Std.U8} {out out1 : Slice Std.U32}
    {nt p l d w k c nl pp p1 l1 : Nat} {ntU : Std.Usize} {v : Std.U32}
    (hdec : ADec input out nt p) (hm : AMatchAt input p l d)
    (h0 : 1 ≤ nt) (hntl : nt ≤ out.length) (ht : 256 ≤ (out.val[nt - 1]!).val)
    (hw : w = LZ77.tokLen (out.val[nt - 1]!).val)
    (hmk : Matches input (p - k - d) (p - k) k) (hc : NearPrefix input pp nl c)
    (hout1 : out1 = out.set ntU v)
    (hlk : l + k ≤ 258) (hdk : d + k ≤ p) (hk : k ≤ w) (hpp : pp = p - w) (hnl : nl = w - k)
    (hc0 : 0 < c) (hntU : ntU.val = nt - 1) (hv : v.val = LZ77.mkMatch c nl)
    (hp1 : p1 = p - k) (hl1 : l1 = l + k) :
    out1.length = out.length ∧ ADec input out1 nt p1 ∧ AMatchAt input p1 l1 d ∧
      p1 + l1 = p + l ∧ p1 ≤ p := by
  subst hp1 hl1 hpp
  obtain ⟨hwp, hdec'⟩ := ADec.pop_match hdec (by omega) hntl ht
  rw [← hw] at hdec' hwp
  have hmc : AMatchAt input (p - w) nl c := by
    rcases hc with hc | hc
    · omega
    · exact hc
  have hd2 := ADec.match hdec' hmc ntU hntU v hv
  rw [show nt - 1 + 1 = nt by omega, show p - w + nl = p - k by omega, ← hout1] at hd2
  refine ⟨by rw [hout1, Std.Slice.set_length], hd2, AMatchAt.back_part hm hmk hlk hdk,
    by omega, by omega⟩


/-- Any shorter suffix of the bytes immediately before p remains checked. -/
theorem Matches.back_trim {input : Slice Std.U8} {p d k c : Nat}
    (h : Matches input (p - k - d) (p - k) k) (hc : c ≤ k) (hd : d + k ≤ p) :
    Matches input (p - c - d) (p - c) c := by
  intro j hj
  have he := h (k - c + j) (by omega)
  rw [show p - k + (k - c + j) = p - c + j by omega,
    show p - k - d + (k - c + j) = p - c - d + j by omega] at he
  exact he

/-- Replacing the last decoded match by one literal preserves its decoded prefix. -/
theorem absorb_one_dec {input : Slice Std.U8} {out out1 : Slice Std.U32}
    {nt p w : Nat} {idx : Std.Usize} {v : Std.U32}
    (hdec : ADec input out nt p) (h0 : 0 < nt) (hntl : nt ≤ out.length)
    (ht : 256 ≤ (out.val[nt - 1]!).val)
    (hw : w = LZ77.tokLen (out.val[nt - 1]!).val)
    (hw3 : 3 ≤ w) (hp : p < input.length)
    (hi : idx.val = nt - 1) (hv : v.val = (input.val[p-w]!).val)
    (ho : out1 = out.set idx v) :
    ADec input out1 nt (p-w+1) := by
  obtain ⟨hwp,hpre⟩ := ADec.pop_match hdec h0 hntl ht
  rw [←hw] at hwp hpre
  have hnext := ADec.lit hpre (by omega) idx hi v hv
  rw [show nt - 1 + 1 = nt by omega, ←ho] at hnext
  exact hnext

/-- Prefix literals plus a checked backwards suffix preserve the endpoint. -/
theorem absorb_match_post {input : Slice Std.U8} {out out1 : Slice Std.U32}
    {nt p l d w k keep nt1 p1 l1 : Nat}
    (hm : AMatchAt input p l d)
    (hdec : ADec input out1 nt1 (p-w+keep))
    (hL : out1.length = out.length)
    (hs : Matches input (p-k-d) (p-k) k)
    (hwp : w ≤ p) (hkeep : keep ≤ w) (hchecked : w-keep ≤ k)
    (hlk : l+k ≤ 258) (hdk : d+k ≤ p)
    (hp1 : p1 = p-w+keep) (hl1 : l1 = l+w-keep) :
    out1.length = out.length ∧ ADec input out1 nt1 p1 ∧
      AMatchAt input p1 l1 d ∧ p1+l1=p+l ∧ p1≤p := by
  subst hp1 hl1
  have heq : p-w+keep = p-(w-keep) := by omega
  have hlen : l+w-keep = l+(w-keep) := by omega
  have hcheck := Matches.back_trim hs hchecked hdk
  have hmatch := AMatchAt.back_part hm hcheck (by omega) (by omega)
  rw [←heq,←hlen] at hmatch
  exact ⟨hL,hdec,hmatch,by omega,by omega⟩


/-- Replace the last decoded match by its first two literal bytes. The rest of
    the old match is left for a subsequent enlarged pending match. -/
theorem absorb_two_dec {input : Slice Std.U8} {out out1 out2 : Slice Std.U32}
    {nt p w pp : Nat} {nt0 nt1 : Std.Usize} {v0 v1 : Std.U32}
    (hdec : ADec input out nt p) (h0 : 0 < nt) (hntl : nt ≤ out.length)
    (ht : 256 ≤ (out.val[nt - 1]!).val)
    (hw : w = LZ77.tokLen (out.val[nt - 1]!).val) (hw3 : 3 ≤ w)
    (hpp : pp = p - w)
    (hnt0 : nt0.val = nt - 1) (hnt1 : nt1.val = nt)
    (hv0 : v0.val = (input.val[pp]!).val)
    (hv1 : v1.val = (input.val[pp + 1]!).val)
    (hout1 : out1 = out.set nt0 v0) (hout2 : out2 = out1.set nt1 v1) :
    out2.length = out.length ∧ ADec input out2 (nt + 1) (p - w + 2) := by
  subst pp
  obtain ⟨hwp, hd0⟩ := ADec.pop_match hdec h0 hntl ht
  rw [← hw] at hwp hd0
  have hp : p ≤ input.length := hdec.1
  have hd1 := ADec.lit hd0 (by omega) nt0 hnt0 v0 hv0
  have hi1 : nt1.val = nt - 1 + 1 := by omega
  have hd2 := ADec.lit hd1 (by omega) nt1 hi1 v1 hv1
  rw [← hout1, ← hout2] at hd2
  rw [show nt - 1 + 1 + 1 = nt + 1 by omega,
    show p - w + 1 + 1 = p - w + 2 by omega] at hd2
  exact ⟨by rw [hout2, Std.Slice.set_length, hout1, Std.Slice.set_length], hd2⟩


end Submission

/- Completed development module: FoldCore -/

/-!
jprover (cand/J-fast): proof of a fast greedy/lazy LZ77 parser (hash chains, word compares,
cost-aware lazy choices). All search code is untrusted: every lemma about it has postcondition
`True` and proves only termination and the absence of panics (one uniform recipe per loop).
Emission happens inside the main loop through trusted helpers that re-verify every match with the
byte-wise `match_len`, so the main loop's invariant is the template's.
-/

namespace Submission
open Aeneas Aeneas.Std Result ControlFlow

set_option maxRecDepth 8192
set_option maxHeartbeats 4000000

open LZ77 (toks bytes bytes_length bytes_getElem! Matches emit_lit emit_match ite_ok)

theorem decode_nil (input : Slice Std.U8) (out : Slice Std.U32) :
    LZ77.decode (toks out (0#usize).val) = some ((bytes input).take (0#usize).val) := by
  simp [toks, LZ77.decode]

/-- A parse that reached the input end is valid. -/
theorem valid_of_decode {input : Slice Std.U8} {o : Slice Std.U32} {t p : Std.Usize}
    (hde : LZ77.decode (toks o t.val) = some ((bytes input).take p.val)) (hp : p.val = input.length) :
    LZ77.Valid (bytes input) (toks o t.val) := by
  unfold LZ77.Valid
  rw [hde, hp]
  simp

/-- Case split on an `if` without `split`. -/
theorem spec_ite_cut {α : Type} (c : Prop) [Decidable c] (a b : Result α) (Q : α → Prop)
    (ha : c → a ⦃ Q ⦄) (hb : ¬c → b ⦃ Q ⦄) : (if c then a else b) ⦃ Q ⦄ := by
  by_cases h : c
  · rw [if_pos h]; exact ha h
  · rw [if_neg h]; exact hb h


/-- Search-state updates in the main loop (tuple-valued `if`s) are kept opaque. -/
theorem ite_prod_spec {α β : Type} (c : Prop) [Decidable c] (A B : Result (α × β))
    (hA : c → A ⦃ fun _ => True ⦄) (hB : ¬c → B ⦃ fun _ => True ⦄) :
    (if c then A else B) ⦃ fun _ => True ⦄ := by
  by_cases h : c
  · rw [if_pos h]; exact hA h
  · rw [if_neg h]; exact hB h


/-- Every bind-position `if` of the (untrusted) main-loop state computation is kept opaque. -/
theorem ite_true_spec {α : Type} (c : Prop) [Decidable c] (A B : Result α)
    (hA : c → A ⦃ fun _ => True ⦄) (hB : ¬c → B ⦃ fun _ => True ⦄) :
    (if c then A else B) ⦃ fun _ => True ⦄ := by
  by_cases h : c
  · rw [if_pos h]; exact hA h
  · rw [if_neg h]; exact hB h


namespace A2FastCut
@[scoped step]
theorem ite_total {α : Type} (c : Prop) [Decidable c] (A B : Result α)
    (hA : c → A ⦃ fun _ => True ⦄) (hB : ¬c → B ⦃ fun _ => True ⦄) :
    (if c then A else B) ⦃ fun _ => True ⦄ := by
  split
  · exact hA (by assumption)
  · exact hB (by assumption)
end A2FastCut

namespace A2StepScope1
@[scoped step]
theorem _root_.Submission.ld8_spec (input : Slice Std.U8) (p : Std.Usize) :
    slot.ld8 input p ⦃ fun _ => True ⦄ := by
  rw [slot.ld8]
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)

end A2StepScope1
open scoped Submission.A2StepScope1
theorem dextra_spec (d : Std.Usize) :
    slot.dextra d ⦃ fun _ => True ⦄ := by
  rw [slot.dextra]
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)

theorem lextra_spec (l : Std.Usize) :
    slot.lextra l ⦃ fun _ => True ⦄ := by
  rw [slot.lextra]
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)

namespace A2StepScope2
@[scoped step]
theorem _root_.Submission.lg8_spec (x : Std.U32) :
    slot.lg8 x ⦃ fun _ => True ⦄ := by
  rw [slot.lg8]
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)

end A2StepScope2
open scoped Submission.A2StepScope2
namespace A2StepScope3
open scoped A2FastCut A2FastPureChoice in
@[scoped step]
theorem _root_.Submission.entropy256_loop_spec (h : Array Std.U32 256#usize) (tot : Std.U64) (acc : Std.U64) (i : Std.Usize)  :
    slot.entropy256_loop h tot acc i ⦃ fun _ => True ⦄ := by
  rw [slot.entropy256_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => 256 - s.2.2.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1, x2⟩ _
    simp only [slot.entropy256_loop.body, lift, Array.to_slice_mut]
    step*
    repeat (first
      | (intro hc; (try step*))
      | (split <;> (try step*))
      | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply spec_ite_cut <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals (first | omega | scalar_tac)
  · trivial

end A2StepScope3
open scoped Submission.A2StepScope3
theorem entropy256_spec (h : Array Std.U32 256#usize) :
    slot.entropy256 h ⦃ fun _ => True ⦄ := by
  rw [slot.entropy256]
  step*
  repeat (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)

namespace A2StepScope4
open scoped A2FastCut A2FastPureChoice in
@[scoped step]
theorem _root_.Submission.share_loop_spec (h : Array Std.U32 256#usize) (lo : Std.Usize) (hi : Std.Usize) (t : Std.Usize) (s : Std.Usize) (i : Std.Usize)  :
    slot.share_loop h lo hi t s i ⦃ fun _ => True ⦄ := by
  rw [slot.share_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => 256 - s.2.2.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1, x2⟩ _
    simp only [slot.share_loop.body, lift, Array.to_slice_mut]
    step*
    repeat (first
      | (intro hc; (try step*))
      | (split <;> (try step*))
      | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply spec_ite_cut <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals (first | omega | scalar_tac)
  · trivial

end A2StepScope4
open scoped Submission.A2StepScope4
theorem share_spec (h : Array Std.U32 256#usize) (lo : Std.Usize) (hi : Std.Usize) :
    slot.share h lo hi ⦃ fun _ => True ⦄ := by
  rw [slot.share]
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)

theorem low_mode_spec (e : Std.Usize) :
    slot.low_mode e ⦃ fun _ => True ⦄ := by
  rw [slot.low_mode]
  step*
  repeat (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)

def w8 (input : Slice Std.U8) (p : Nat) : Nat :=
  (input.val[p]!).val + (input.val[p + 1]!).val * 256 + (input.val[p + 2]!).val * 65536 +
  (input.val[p + 3]!).val * 16777216 + (input.val[p + 4]!).val * 4294967296 +
  (input.val[p + 5]!).val * 1099511627776 + (input.val[p + 6]!).val * 281474976710656 +
  (input.val[p + 7]!).val * 72057594037927936

/-- The little-endian value of the 4 bytes at `p`. -/
def w4 (input : Slice Std.U8) (p : Nat) : Nat :=
  (input.val[p]!).val + (input.val[p + 1]!).val * 256 + (input.val[p + 2]!).val * 65536 +
  (input.val[p + 3]!).val * 16777216

theorem w8_bytes (input : Slice Std.U8) (p q : Nat) (h : w8 input p = w8 input q) :
    ∀ k, k < 8 → input.val[q + k]! = input.val[p + k]! := by
  unfold w8 at h
  have b0 := (input.val[p]!).hBounds
  have b1 := (input.val[p + 1]!).hBounds
  have b2 := (input.val[p + 2]!).hBounds
  have b3 := (input.val[p + 3]!).hBounds
  have b4 := (input.val[p + 4]!).hBounds
  have b5 := (input.val[p + 5]!).hBounds
  have b6 := (input.val[p + 6]!).hBounds
  have b7 := (input.val[p + 7]!).hBounds
  have c0 := (input.val[q]!).hBounds
  have c1 := (input.val[q + 1]!).hBounds
  have c2 := (input.val[q + 2]!).hBounds
  have c3 := (input.val[q + 3]!).hBounds
  have c4 := (input.val[q + 4]!).hBounds
  have c5 := (input.val[q + 5]!).hBounds
  have c6 := (input.val[q + 6]!).hBounds
  have c7 := (input.val[q + 7]!).hBounds
  simp only [Std.UScalarTy.numBits] at *
  intro k hk
  apply UScalar.eq_imp
  rcases (by omega : k = 0 ∨ k = 1 ∨ k = 2 ∨ k = 3 ∨ k = 4 ∨ k = 5 ∨ k = 6 ∨ k = 7) with
    rfl | rfl | rfl | rfl | rfl | rfl | rfl | rfl <;> (try simp only [Nat.add_zero]) <;> omega

theorem w4_bytes (input : Slice Std.U8) (p q : Nat) (h : w4 input p = w4 input q) :
    ∀ k, k < 4 → input.val[q + k]! = input.val[p + k]! := by
  unfold w4 at h
  have b0 := (input.val[p]!).hBounds
  have b1 := (input.val[p + 1]!).hBounds
  have b2 := (input.val[p + 2]!).hBounds
  have b3 := (input.val[p + 3]!).hBounds
  have c0 := (input.val[q]!).hBounds
  have c1 := (input.val[q + 1]!).hBounds
  have c2 := (input.val[q + 2]!).hBounds
  have c3 := (input.val[q + 3]!).hBounds
  simp only [Std.UScalarTy.numBits] at *
  intro k hk
  apply UScalar.eq_imp
  rcases (by omega : k = 0 ∨ k = 1 ∨ k = 2 ∨ k = 3) with
    rfl | rfl | rfl | rfl <;> (try simp only [Nat.add_zero]) <;> omega

/-- An 8-byte word equality extends a match by 8. -/
theorem Matches.add8 {input : Slice Std.U8} {a b l : Nat} (h : Matches input a b l)
    (hw : w8 input (a + l) = w8 input (b + l)) : Matches input a b (l + 8) := by
  have hb := w8_bytes input (a + l) (b + l) hw
  intro k hk
  by_cases hkl : k < l
  · exact h k hkl
  · have := hb (k - l) (by omega)
    rw [show b + k = b + l + (k - l) by omega, show a + k = a + l + (k - l) by omega]
    exact this

/-- A match of length `l >= c - 8` plus an equal 8-byte word at `c - 8` is a match of length `c`. -/
theorem Matches.tail8 {input : Slice Std.U8} {a b l c : Nat} (h : Matches input a b l)
    (hc : 8 ≤ c) (hl : c ≤ l + 8)
    (hw : w8 input (a + (c - 8)) = w8 input (b + (c - 8))) : Matches input a b c := by
  have hb := w8_bytes input (a + (c - 8)) (b + (c - 8)) hw
  intro k hk
  by_cases hkl : k < l
  · exact h k hkl
  · have := hb (k - (c - 8)) (by omega)
    rw [show b + k = b + (c - 8) + (k - (c - 8)) by omega,
      show a + k = a + (c - 8) + (k - (c - 8)) by omega]
    exact this

/-- Two equal 4-byte words at 0 and `c - 4` (4 <= c < 8) are a match of length `c`. -/
theorem Matches.two4 {input : Slice Std.U8} {a b c : Nat}
    (hc : 4 ≤ c) (hc8 : c < 8) (hw0 : w4 input a = w4 input b)
    (hw1 : w4 input (a + (c - 4)) = w4 input (b + (c - 4))) : Matches input a b c := by
  have h0 := w4_bytes input a b hw0
  have h1 := w4_bytes input (a + (c - 4)) (b + (c - 4)) hw1
  intro k hk
  by_cases hk4 : k < 4
  · exact h0 k hk4
  · have := h1 (k - (c - 4)) (by omega)
    rw [show b + k = b + (c - 4) + (k - (c - 4)) by omega,
      show a + k = a + (c - 4) + (k - (c - 4)) by omega]
    exact this


/-- Endpoint word checks cover a short match, including overlapping words. -/
theorem Matches.two8 {input : Slice Std.U8} {a b c : Nat}
    (hc : 8 ≤ c) (hc16 : c ≤ 16) (hw0 : w8 input a = w8 input b)
    (hw1 : w8 input (a + (c - 8)) = w8 input (b + (c - 8))) : Matches input a b c := by
  have h0 := w8_bytes input a b hw0
  have h1 := w8_bytes input (a + (c - 8)) (b + (c - 8)) hw1
  intro k hk
  by_cases hk8 : k < 8
  · exact h0 k hk8
  · have := h1 (k - (c - 8)) (by omega)
    rw [show b + k = b + (c - 8) + (k - (c - 8)) by omega,
      show a + k = a + (c - 8) + (k - (c - 8)) by omega]
    exact this


theorem tw8_spec (input : Slice Std.U8) (p : Std.Usize) (h : p.val + 8 ≤ input.length) :
    slot.tw8 input p ⦃ fun r => r.val = w8 input p.val ⦄ := by
  change p.val + 8 ≤ input.val.length at h
  rw [slot.tw8]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  step*
  unfold w8
  rw [getElem!_pos input.val p.val (by (first | omega | scalar_tac)), getElem!_pos input.val (p.val + 1) (by (first | omega | scalar_tac)),
    getElem!_pos input.val (p.val + 2) (by (first | omega | scalar_tac)), getElem!_pos input.val (p.val + 3) (by (first | omega | scalar_tac)),
    getElem!_pos input.val (p.val + 4) (by (first | omega | scalar_tac)), getElem!_pos input.val (p.val + 5) (by (first | omega | scalar_tac)),
    getElem!_pos input.val (p.val + 6) (by (first | omega | scalar_tac)), getElem!_pos input.val (p.val + 7) (by (first | omega | scalar_tac))]
  (first | omega | scalar_tac)

namespace A2StepScope5
@[scoped step]
theorem _root_.Submission.fl_tw8_spec (input : Slice Std.U8) (p : Std.Usize) (h : p.val + 8 ≤ input.length) :
    slot.fl_tw8 input p ⦃ fun r => r.val = w8 input p.val ⦄ := by
  exact tw8_spec input p h


end A2StepScope5
open scoped Submission.A2StepScope5
namespace A2StepScope6
@[scoped step]
theorem _root_.Submission.fl_tw4_spec (input : Slice Std.U8) (p : Std.Usize) (h : p.val + 4 ≤ input.length) :
    slot.fl_tw4 input p ⦃ fun r => r.val = w4 input p.val ⦄ := by
  change p.val + 4 ≤ input.val.length at h
  rw [slot.fl_tw4]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  step*
  unfold w4
  rw [getElem!_pos input.val p.val (by (first | omega | scalar_tac)), getElem!_pos input.val (p.val + 1) (by (first | omega | scalar_tac)),
    getElem!_pos input.val (p.val + 2) (by (first | omega | scalar_tac)), getElem!_pos input.val (p.val + 3) (by (first | omega | scalar_tac))]
  (first | omega | scalar_tac)

end A2StepScope6
open scoped Submission.A2StepScope6

/- E2 (engine round 5, lane E2): word-compare helpers of the trusted fold. -/
namespace E2Scope
@[scoped step]
theorem _root_.Submission.E2_tw4_spec (input : Slice Std.U8) (p : Std.Usize) (h : p.val + 4 ≤ input.length) :
    slot.tw4 input p ⦃ fun r => r.val = w4 input p.val ⦄ := by
  change p.val + 4 ≤ input.val.length at h
  rw [slot.tw4]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  step*
  unfold w4
  rw [getElem!_pos input.val p.val (by (first | omega | scalar_tac)), getElem!_pos input.val (p.val + 1) (by (first | omega | scalar_tac)),
    getElem!_pos input.val (p.val + 2) (by (first | omega | scalar_tac)), getElem!_pos input.val (p.val + 3) (by (first | omega | scalar_tac))]
  (first | omega | scalar_tac)
attribute [scoped step] Submission.tw8_spec
end E2Scope
open scoped Submission.E2Scope

theorem E2_w4_top (input : Slice Std.U8) (q : Nat) :
    w4 input q >>> 24 = (input.val[q + 3]!).val := by
  unfold w4
  have b0 := (input.val[q]!).hBounds
  have b1 := (input.val[q + 1]!).hBounds
  have b2 := (input.val[q + 2]!).hBounds
  have b3 := (input.val[q + 3]!).hBounds
  simp only [Std.UScalarTy.numBits] at *
  rw [Nat.shiftRight_eq_div_pow]
  omega

theorem E2_gate2_spec (input : Slice Std.U8) (p d : Std.Usize)
    (hd : d.val ≤ 32768) (hp : p.val ≤ input.length) :
    slot.public_gate2 input p d ⦃ fun _ => True ⦄ := by
  rw [slot.public_gate2]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  step*

namespace E2LitScope
@[scoped step]
theorem _root_.Submission.E2_lit_ok_spec (input : Slice Std.U8) (p d : Std.Usize)
    (hd : d.val ≤ 32768) (hp : p.val ≤ input.length) :
    slot.public_lit_ok input p d ⦃ fun r => r = true →
      d.val < p.val ∧ input.val[p.val - 1]! = input.val[p.val - 1 - d.val]! ⦄ := by
  rw [slot.public_lit_ok]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  step*
  intro h6
  have h6' : i6 = 0#u32 := by simpa using h6
  have hv : i6.val = 0 := by rw [h6']; rfl
  rw [i6_post1, i5_post1, UScalar.val_xor, i2_post, i4_post, Nat.shiftRight_xor_distrib] at hv
  have he := Nat.eq_of_xor_eq_zero hv
  rw [E2_w4_top, E2_w4_top] at he
  refine ⟨by omega, ?_⟩
  apply UScalar.eq_imp
  rw [show p.val - 1 - d.val = i3.val + 3 by omega, show p.val - 1 = i1.val + 3 by omega]
  exact he

end E2LitScope

theorem E2_w8_byte (input : Slice Std.U8) (a j : Nat) (hj : j < 8) :
    (w8 input a / 2^(8*j)) % 256 = (input.val[a + j]!).val := by
  unfold w8
  have b0 := (input.val[a]!).hBounds
  have b1 := (input.val[a + 1]!).hBounds
  have b2 := (input.val[a + 2]!).hBounds
  have b3 := (input.val[a + 3]!).hBounds
  have b4 := (input.val[a + 4]!).hBounds
  have b5 := (input.val[a + 5]!).hBounds
  have b6 := (input.val[a + 6]!).hBounds
  have b7 := (input.val[a + 7]!).hBounds
  simp only [Std.UScalarTy.numBits] at b0 b1 b2 b3 b4 b5 b6 b7
  interval_cases j <;> simp only [Nat.mul_zero, Nat.reduceMul, Nat.reducePow, Nat.add_zero] <;> omega

theorem E2_w8_top (input : Slice Std.U8) (a b r : Nat) (hr : r ≤ 8)
    (h : w8 input a / 2^(64 - 8*r) = w8 input b / 2^(64 - 8*r)) :
    Matches input (a + (8 - r)) (b + (8 - r)) r := by
  intro k hk
  apply UScalar.eq_imp
  have hj : 8 - r + k < 8 := by omega
  rw [Nat.add_assoc, Nat.add_assoc, ← E2_w8_byte input b (8-r+k) hj, ← E2_w8_byte input a (8-r+k) hj,
    show 8*(8-r+k) = (64-8*r) + 8*k by omega, Nat.pow_add, ← Nat.div_div_eq_div_mul,
    ← Nat.div_div_eq_div_mul, h]

theorem E2_matches_suffix {input : Slice Std.U8} {P z d c : Nat}
    (h : Matches input (P - z - d) (P - z) z) (hc : c ≤ z) (hz : z + d ≤ P) :
    Matches input (P - c - d) (P - c) c := by
  intro k hk
  have := h (z - c + k) (by omega)
  rwa [show P - z + (z - c + k) = P - c + k by omega, show P - z - d + (z - c + k) = P - c - d + k by omega] at this

namespace E2W2Scope
@[scoped step]
theorem _root_.Submission.E2_suffix_w2_spec (input : Slice Std.U8) (p d cap : Std.Usize)
    (hp : p.val ≤ input.length) (hd : d.val+cap.val ≤ p.val) :
    slot.public_suffix_w2 input p d cap ⦃ fun r =>
      r.1.val ≤ cap.val ∧ Matches input (p.val-r.1.val-d.val) (p.val-r.1.val) r.1.val ⦄ := by
  rw [slot.public_suffix_w2]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  step*
  all_goals first
    | (exact ⟨by simp, Matches.zero _ _ _⟩)
    | (have hx0' : x ≠ 0#u64 := by simpa using ‹(x != 0#u64) = true›
       have hxb : x.bv ≠ 0 := by
         intro h; apply hx0'; exact (U64.eq_equiv_bv_eq x 0#u64).mpr h
       have hlog : Nat.log 2 x.val < 64 := Nat.log_lt_of_lt_pow' (by decide) x.bv.isLt
       have hi5 : i5.val = 64 - Nat.log 2 x.val - 1 := by
         rw [i5_post]
         simp only [core.num.U64.leading_zeros,BitVec.leadingZeros,if_neg hxb]
         change (64 - Nat.log 2 x.val - 1) % 2^32 = _
         omega
       have hz : z.val = (64 - Nat.log 2 x.val - 1) / 8 := by
         rw [z_post, U32.cast_Usize_val_eq, i6_post, hi5]
       have hxlt : x.val < 2^(64 - 8 * z.val) := by
         have h1 := Nat.lt_pow_succ_log_self (by decide : 1 < 2) x.val
         have h2 : (Nat.log 2 x.val).succ ≤ 64 - 8 * z.val := by rw [hz]; omega
         exact lt_of_lt_of_le h1 (Nat.pow_le_pow_right (by decide) h2)
       have hnat : (i2.val ^^^ i4.val) >>> (64 - 8 * z.val) = 0 := by
         have hxv : x.val = i2.val ^^^ i4.val := by rw [x_post1, UScalar.val_xor]
         rw [← hxv, Nat.shiftRight_eq_div_pow]
         exact Nat.div_eq_of_lt hxlt
       rw [Nat.shiftRight_xor_distrib] at hnat
       have he := Nat.eq_of_xor_eq_zero hnat
       rw [i2_post, i4_post, Nat.shiftRight_eq_div_pow, Nat.shiftRight_eq_div_pow] at he
       have hm := E2_w8_top input i3.val i1.val z.val (by omega) he.symm
       have hzm : Matches input (p.val - z.val - d.val) (p.val - z.val) z.val := by
         rw [show p.val - z.val - d.val = i3.val + (8 - z.val) by omega,
           show p.val - z.val = i1.val + (8 - z.val) by omega]
         exact hm
       first
         | exact ⟨by scalar_tac, hzm⟩
         | exact ⟨le_refl _, E2_matches_suffix hzm (by scalar_tac) (by omega)⟩)
    | (have hxz : x.val = 0 := by simpa using ‹¬(x != 0#u64) = true›
       have hxv : (i2 ^^^ i4).val = 0 := by rw [← x_post1]; exact hxz
       have hnat : i2.val ^^^ i4.val = 0 := by simpa only [UScalar.val_xor] using hxv
       have he := Nat.eq_of_xor_eq_zero hnat
       rw [i2_post, i4_post] at he
       have hm8 : Matches input (p.val - 8 - d.val) (p.val - 8) 8 := by
         rw [show p.val - 8 - d.val = i3.val by omega, show p.val - 8 = i1.val by omega]
         exact w8_bytes input i3.val i1.val he.symm
       first
         | exact ⟨by scalar_tac, by simpa using hm8⟩
         | exact ⟨le_refl _, E2_matches_suffix hm8 (by scalar_tac) (by omega)⟩)
end E2W2Scope

theorem ABackInv.lit2 {input : Slice Std.U8} {out : Slice Std.U32} {L d E P0 : Nat}
    {nt p l i1 i2 l1 : Std.Usize} {t : Std.U32}
    (h : ABackInv input L d E P0 out nt.val p.val l.val)
    (hi1 : i1.val = nt.val - 1) (hntl : nt.val ≤ out.length) (hnt0 : 1 ≤ nt.val)
    (hi1l : i1.val < out.val.length) (ht : t = out.val[i1.val]) (ht256 : t < 256#u32)
    (hi2 : i2.val = p.val - 1) (heq : input.val[p.val - 1]! = input.val[p.val - 1 - d]!)
    (hl : l.val < 258) (hdp : d < p.val) (hl1 : l1.val = l.val + 1) :
    ABackInv input L d E P0 out i1.val i2.val l1.val := by
  obtain ⟨hdec, hL, hm, hE, hP⟩ := h
  have ht' : (out.val[nt.val - 1]!).val < 256 := by
    rw [← hi1, getElem!_pos out.val i1.val hi1l, ← ht]; (first | omega | scalar_tac)
  obtain ⟨hp1, hdec'⟩ := ADec.pop_lit hdec (by omega) hntl ht'
  have hm' := AMatchAt.back_lit hm hl hdp heq
  rw [hi1, hi2, hl1]
  exact ⟨hdec', hL, hm', by omega, by omega⟩

theorem fl_words_eq_loop_spec (input : Slice Std.U8) (a b cap l0 : Std.Usize)
    (ha : a.val + cap.val ≤ input.length) (hb : b.val + cap.val ≤ input.length)
    (hl0 : l0.val ≤ cap.val) (h0 : Matches input a.val b.val l0.val) :
    slot.fl_words_eq_loop input a b cap l0 ⦃ fun l =>
      l.val ≤ cap.val ∧ Matches input a.val b.val l.val ⦄ := by
  rw [slot.fl_words_eq_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun l => cap.val - l.val)
    (inv := fun l => l.val ≤ cap.val ∧ Matches input a.val b.val l.val)
  · rintro l ⟨hle, hinv⟩
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.fl_words_eq_loop.body]
    step*
    all_goals first
      | exact ⟨hle, hinv⟩
      | (refine ⟨by (first | omega | scalar_tac), ?_, by (first | omega | scalar_tac)⟩
         rw [show l1.val = l.val + 8 by (first | omega | scalar_tac)]
         apply Matches.add8 hinv
         rw [show a.val + l.val = i1.val by (first | omega | scalar_tac), show b.val + l.val = i3.val by (first | omega | scalar_tac),
           ← i2_post, ← i4_post, ‹i2 = i4›])
  · exact ⟨hl0, h0⟩

namespace A2StepScope7
@[scoped step]
theorem _root_.Submission.fl_tail_eq_spec (input : Slice Std.U8) (a b cap l : Std.Usize)
    (ha : a.val + cap.val ≤ input.length) (hb : b.val + cap.val ≤ input.length) (hl : l.val ≤ cap.val) :
    slot.fl_tail_eq input a b cap l ⦃ fun r => r.val = 1 →
      8 ≤ cap.val ∧ cap.val ≤ l.val + 8 ∧
      w8 input (a.val + (cap.val - 8)) = w8 input (b.val + (cap.val - 8)) ⦄ := by
  rw [slot.fl_tail_eq]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  step*
  all_goals first
    | (intro h; simp at h)
    | (intro _
       refine ⟨by (first | omega | scalar_tac), by (first | omega | scalar_tac), ?_⟩
       rw [show a.val + (cap.val - 8) = i2.val by (first | omega | scalar_tac),
         show b.val + (cap.val - 8) = i4.val by (first | omega | scalar_tac), ← i3_post, ← i5_post, ‹i3 = i5›])
    | (refine ⟨by (first | omega | scalar_tac), by (first | omega | scalar_tac), ?_⟩
       rw [show a.val + (cap.val - 8) = i2.val by (first | omega | scalar_tac),
         show b.val + (cap.val - 8) = i4.val by (first | omega | scalar_tac), ← i3_post, ← i5_post, ‹i3 = i5›])

end A2StepScope7
open scoped Submission.A2StepScope7
namespace A2StepScope8
@[scoped step]
theorem _root_.Submission.fl_short_eq_spec (input : Slice Std.U8) (a b cap : Std.Usize)
    (ha : a.val + cap.val ≤ input.length) (hb : b.val + cap.val ≤ input.length) :
    slot.fl_short_eq input a b cap ⦃ fun r => r.val = 1 →
      4 ≤ cap.val ∧ cap.val < 8 ∧ w4 input a.val = w4 input b.val ∧
      w4 input (a.val + (cap.val - 4)) = w4 input (b.val + (cap.val - 4)) ⦄ := by
  rw [slot.fl_short_eq]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  step*
  all_goals first
    | (intro h; simp at h)
    | (intro _
       refine ⟨by (first | omega | scalar_tac), by (first | omega | scalar_tac), ?_, ?_⟩
       · rw [← i_post, ← i1_post]
         simp_all
       · rw [show a.val + (cap.val - 4) = i3.val by (first | omega | scalar_tac),
           show b.val + (cap.val - 4) = i5.val by (first | omega | scalar_tac), ← i4_post, ← i6_post, ‹i4 = i6›])
    | (refine ⟨by (first | omega | scalar_tac), by (first | omega | scalar_tac), ?_, ?_⟩
       · rw [← i_post, ← i1_post]
         simp_all
       · rw [show a.val + (cap.val - 4) = i3.val by (first | omega | scalar_tac),
           show b.val + (cap.val - 4) = i5.val by (first | omega | scalar_tac), ← i4_post, ← i6_post, ‹i4 = i6›])

end A2StepScope8
open scoped Submission.A2StepScope8
namespace A2StepScope9
@[scoped step]
theorem _root_.Submission.fl_words_eq_spec (input : Slice Std.U8) (a b cap : Std.Usize)
    (ha : a.val + cap.val ≤ input.length) (hb : b.val + cap.val ≤ input.length) :
    slot.fl_words_eq input a b cap ⦃ fun l =>
      l.val ≤ cap.val ∧ Matches input a.val b.val l.val ⦄ := by
  rw [slot.fl_words_eq]
  apply Std.WP.spec_bind (fl_words_eq_loop_spec input a b cap 0#usize ha hb (by (first | omega | scalar_tac))
    (LZ77.Matches.zero input a.val b.val))
  rintro l ⟨hle, hm⟩
  apply Std.WP.spec_bind (fl_tail_eq_spec input a b cap l ha hb hle)
  rintro big hbig
  apply Std.WP.spec_bind (fl_short_eq_spec input a b cap ha hb)
  rintro small hsmall
  split
  · have h1 : big.val = 1 := by (first | omega | scalar_tac)
    obtain ⟨h8, hcl, hw⟩ := hbig h1
    simp only [Std.WP.spec_ok]
    exact ⟨le_refl _, Matches.tail8 hm h8 hcl hw⟩
  · split
    · have h1 : small.val = 1 := by (first | omega | scalar_tac)
      obtain ⟨h4, h8, hw0, hw1⟩ := hsmall h1
      simp only [Std.WP.spec_ok]
      exact ⟨le_refl _, Matches.two4 h4 h8 hw0 hw1⟩
    · simp only [Std.WP.spec_ok]
      exact ⟨hle, hm⟩

end A2StepScope9
open scoped Submission.A2StepScope9
theorem fl_match_len_loop_spec (input : Slice Std.U8) (a b cap l0 : Std.Usize)
    (ha : a.val + cap.val ≤ input.length) (hb : b.val + cap.val ≤ input.length)
    (hl0 : l0.val ≤ cap.val) (h0 : Matches input a.val b.val l0.val) :
    slot.fl_match_len_loop input a b cap l0 ⦃ fun l =>
      l.val ≤ cap.val ∧ Matches input a.val b.val l.val ⦄ := by
  rw [slot.fl_match_len_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun l => cap.val - l.val)
    (inv := fun l => l.val ≤ cap.val ∧ LZ77.Matches input a.val b.val l.val)
  · rintro l ⟨hle, hinv⟩
    simp only [slot.fl_match_len_loop.body]
    split
    case isTrue hlt =>
      have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
      step*
      all_goals first
        | (first | omega | scalar_tac)
        | exact ⟨hle, hinv⟩
        | (refine ⟨by (first | omega | scalar_tac), ?_, by (first | omega | scalar_tac)⟩
           rw [show l1.val = l.val + 1 by (first | omega | scalar_tac)]
           apply LZ77.Matches.succ hinv
           rw [← i_post, ← i2_post, getElem!_pos _ _ (by (first | omega | scalar_tac)),
             getElem!_pos _ _ (by (first | omega | scalar_tac)), ← i1_post, ← i3_post]
           assumption)
    case isFalse => exact ⟨hle, hinv⟩
  · exact ⟨hl0, h0⟩

namespace A2StepScope10
@[scoped step]
theorem _root_.Submission.fl_match_len_spec (input : Slice Std.U8) (a b cap : Std.Usize)
    (ha : a.val + cap.val ≤ input.length) (hb : b.val + cap.val ≤ input.length) :
    slot.fl_match_len input a b cap ⦃ fun l =>
      l.val ≤ cap.val ∧ Matches input a.val b.val l.val ⦄ := by
  rw [slot.fl_match_len]
  apply Std.WP.spec_bind (fl_words_eq_spec input a b cap ha hb)
  rintro l0 ⟨hle, hm⟩
  exact fl_match_len_loop_spec input a b cap l0 ha hb hle hm


end A2StepScope10
open scoped Submission.A2StepScope10
theorem fl_verified_spec (input : Slice Std.U8) (pos d ch : Std.Usize) :
    slot.fl_verified input pos d ch ⦃ fun b => b = true →
      3 ≤ ch.val ∧ ch.val ≤ 258 ∧ 1 ≤ d.val ∧ d.val ≤ 32768 ∧ d.val ≤ pos.val ∧
      pos.val + ch.val ≤ input.length ∧ Matches input (pos.val - d.val) pos.val ch.val ⦄ := by
  rw [slot.fl_verified]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  step*
  intro hv
  have hv' : ch.val ≤ v.val := by simpa using hv
  refine ⟨by (first | omega | scalar_tac), by (first | omega | scalar_tac), by (first | omega | scalar_tac), by (first | omega | scalar_tac), by (first | omega | scalar_tac),
    by (first | omega | scalar_tac), ?_⟩
  rw [show pos.val - d.val = i1.val by (first | omega | scalar_tac)]
  exact Matches.mono v_post2 hv'

theorem fl_emit_lits_loop_spec (input : Slice Std.U8) (out0 : Slice Std.U32)
    (n cnt1 k0 c0 ntok0 : Std.Usize)
    (hn : n.val = input.length) (hout : input.length ≤ out0.length)
    (hk : k0.val ≤ n.val) (hntok : ntok0.val ≤ k0.val) (hc0 : c0.val = 0)
    (hdec : LZ77.decode (toks out0 ntok0.val) = some ((bytes input).take k0.val)) :
    slot.fl_emit_lits_loop input out0 n cnt1 k0 c0 ntok0 ⦃ fun r =>
      r.2.1.val ≤ n.val ∧ (k0.val < r.2.1.val ∨ cnt1.val = 0 ∨ k0.val = n.val) ∧
      r.2.2.val ≤ r.2.1.val ∧ r.1.length = out0.length ∧
      LZ77.decode (toks r.1 r.2.2.val) = some ((bytes input).take r.2.1.val) ⦄ := by
  rw [slot.fl_emit_lits_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => n.val - s.2.1.val)
    (inv := fun s =>
      s.2.1.val ≤ n.val ∧ s.2.1.val = k0.val + s.2.2.1.val ∧ s.2.2.2.val ≤ s.2.1.val ∧
      s.1.length = out0.length ∧
      LZ77.decode (toks s.1 s.2.2.2.val) = some ((bytes input).take s.2.1.val))
  · rintro ⟨out, k, c, ntok⟩ ⟨hkn, hkc, hnt, hlen, hde⟩
    simp only at hkn hkc hnt hlen hde
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.fl_emit_lits_loop.body]
    split
    case isTrue hklt =>
      split
      case isTrue hc =>
        have hntok_lt : ntok.val < out.length := by (first | omega | scalar_tac)
        have hposlen : k.val < input.length := by (first | omega | scalar_tac)
        step*
        have hval : i1.val = (bytes input)[k.val]! := by
          rw [bytes_getElem! input k.val hposlen, i1_post, Std.U8.cast_U32_val_eq, i_post]
        refine ⟨by (first | omega | scalar_tac), by (first | omega | scalar_tac), by (first | omega | scalar_tac),
          by rw [s_post]; simpa [Std.Slice.set_val_eq] using hlen, ?_, by (first | omega | scalar_tac)⟩
        rw [s_post, show ntok1.val = ntok.val + 1 by (first | omega | scalar_tac),
          show k1.val = k.val + 1 by (first | omega | scalar_tac)]
        exact emit_lit input out ntok k.val i1 hde hposlen hntok_lt hval
      case isFalse hc =>
        exact ⟨hkn, by (first | omega | scalar_tac), hnt, hlen, hde⟩
    case isFalse hge =>
      exact ⟨hkn, by (first | omega | scalar_tac), hnt, hlen, hde⟩
  · exact ⟨hk, by (first | omega | scalar_tac), hntok, rfl, hdec⟩

namespace A2StepScope11
@[scoped step]
theorem _root_.Submission.fl_emit_lits_spec (input : Slice Std.U8) (out : Slice Std.U32) (pos0 cnt ntok0 : Std.Usize)
    (hout : input.length ≤ out.length) (hpos : pos0.val ≤ input.length)
    (hntok : ntok0.val ≤ pos0.val)
    (hdec : LZ77.decode (toks out ntok0.val) = some ((bytes input).take pos0.val)) :
    slot.fl_emit_lits input out pos0 cnt ntok0 ⦃ fun r =>
      (pos0.val < r.1.2.val ∨ pos0.val = input.length) ∧ r.1.2.val ≤ input.length ∧ r.1.1.val ≤ r.1.2.val ∧
      r.2.length = out.length ∧
      LZ77.decode (toks r.2 r.1.1.val) = some ((bytes input).take r.1.2.val) ⦄ := by
  rw [slot.fl_emit_lits]
  apply Std.WP.spec_bind (Pₘ := fun (c : Std.Usize) => 1 ≤ c.val)
  · split <;> simp only [Std.WP.spec_ok] <;> (first | omega | scalar_tac)
  intro cnt1 hc1
  apply Std.WP.spec_bind (fl_emit_lits_loop_spec input out _ cnt1 pos0 0#usize ntok0
    (by simp) hout (by (first | omega | scalar_tac)) hntok (by simp) hdec)
  rintro ⟨out1, k, ntok⟩ ⟨h1, h2, h3, h4, h5⟩
  simp only at h1 h2 h3 h4 h5
  step*
  all_goals exact ⟨by (first | omega | scalar_tac), by (first | omega | scalar_tac), h3, h4, h5⟩

end A2StepScope11
open scoped Submission.A2StepScope11
namespace A2StepScope12
@[scoped step]
theorem _root_.Submission.fl_emit_step_spec (input : Slice Std.U8) (out : Slice Std.U32) (pos d l lits ntok : Std.Usize)
    (hout : input.length ≤ out.length) (hpos : pos.val < input.length)
    (hntok : ntok.val ≤ pos.val)
    (hdec : LZ77.decode (toks out ntok.val) = some ((bytes input).take pos.val)) :
    slot.fl_emit_step input out pos d l lits ntok ⦃ fun r =>
      pos.val < r.1.2.val ∧ r.1.2.val ≤ input.length ∧ r.1.1.val ≤ r.1.2.val ∧
      r.2.length = out.length ∧
      LZ77.decode (toks r.2 r.1.1.val) = some ((bytes input).take r.1.2.val) ⦄ := by
  rw [slot.fl_emit_step]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  apply Std.WP.spec_bind (fl_verified_spec input pos d l)
  intro b hb
  split
  case isTrue hbt =>
    obtain ⟨hl3, hl258, hd1, hdmax, hdpos, hend, hmatch⟩ := hb hbt
    have hntok_lt : ntok.val < out.length := by (first | omega | scalar_tac)
    step*
    have htok : i6.val = LZ77.mkMatch d.val l.val := by
      simp only [LZ77.mkMatch, LZ77.MATCH_BASE, i6_post, i3_post, i2_post]
      (first | omega | scalar_tac)
    refine ⟨by (first | omega | scalar_tac), by (first | omega | scalar_tac), by (first | omega | scalar_tac),
      by rw [out1_post]; simp [Std.Slice.set_val_eq], ?_⟩
    rw [out1_post, show i7.val = ntok.val + 1 by (first | omega | scalar_tac),
      show i8.val = pos.val + l.val by (first | omega | scalar_tac)]
    exact emit_match input out ntok pos.val d.val l.val i6 hdec hntok_lt hd1 hdpos hdmax
      hl3 hl258 hend hmatch htok
  case isFalse hbf =>
    apply Std.WP.spec_mono (fl_emit_lits_spec input out pos lits ntok hout (by (first | omega | scalar_tac)) hntok hdec)
    rintro ⟨⟨t, k⟩, o⟩ ⟨h1, h2, h3, h4, h5⟩
    exact ⟨by (first | omega | scalar_tac), h2, h3, h4, h5⟩


end A2StepScope12
open scoped Submission.A2StepScope12
namespace A2StepScope13
@[scoped step]
theorem _root_.Submission.fl_byte_spec (input : Slice Std.U8) (i : Std.Usize) :
    slot.fl_byte input i ⦃ fun _ => True ⦄ := by
  rw [slot.fl_byte]
  step*
  repeat (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)

end A2StepScope13
open scoped Submission.A2StepScope13
namespace A2StepScope14
@[scoped step]
theorem _root_.Submission.fl_ld4_spec (input : Slice Std.U8) (p : Std.Usize) :
    slot.fl_ld4 input p ⦃ fun _ => True ⦄ := by
  rw [slot.fl_ld4]
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)

end A2StepScope14
open scoped Submission.A2StepScope14
namespace A2StepScope15
@[scoped step]
theorem _root_.Submission.fl_ld8_spec (input : Slice Std.U8) (p : Std.Usize) :
    slot.fl_ld8 input p ⦃ fun _ => True ⦄ := by
  exact ld8_spec input p


end A2StepScope15
open scoped Submission.A2StepScope15
namespace A2StepScope16
@[scoped step]
theorem _root_.Submission.fl_len_loop_spec (input : Slice Std.U8) (a : Std.Usize) (b : Std.Usize) (cap : Std.Usize) (l : Std.Usize) (go : Std.Usize) (it : Std.Usize)  :
    slot.fl_len_loop input a b cap l go it ⦃ fun _ => True ⦄ := by
  rw [slot.fl_len_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => 40 - s.2.2.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1, x2⟩ _
    simp only [slot.fl_len_loop.body, lift, Array.to_slice_mut]
    step*
    repeat (first
      | (intro hc; (try step*))
      | (split <;> (try step*))
      | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply spec_ite_cut <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals (first | omega | scalar_tac)
  · trivial

end A2StepScope16
open scoped Submission.A2StepScope16
namespace A2StepScope17
@[scoped step]
theorem _root_.Submission.fl_len_spec (input : Slice Std.U8) (a : Std.Usize) (b : Std.Usize) (cap : Std.Usize) :
    slot.fl_len input a b cap ⦃ fun _ => True ⦄ := by
  rw [slot.fl_len]
  step*
  repeat (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)

end A2StepScope17
open scoped Submission.A2StepScope17
namespace A2StepScope18
@[scoped step]
theorem _root_.Submission.fl_hashp_spec (input : Slice Std.U8) (p : Std.Usize) (hsh : Std.U64) :
    slot.fl_hashp input p hsh ⦃ fun r => r.val < 65536 ⦄ := by
  rw [slot.fl_hashp]
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)

end A2StepScope18
open scoped Submission.A2StepScope18
namespace A2StepScope19
@[scoped step]
theorem _root_.Submission.fl_log16_spec (f : Std.U32) :
    slot.fl_log16 f ⦃ fun _ => True ⦄ := by
  rw [slot.fl_log16]
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)

end A2StepScope19
open scoped Submission.A2StepScope19
namespace A2StepScope20
@[scoped step]
theorem _root_.Submission.fl_sample_loop_spec (input : Slice Std.U8) (h : Array Std.U32 256#usize) (n : Std.Usize) (st : Std.Usize) (k : Std.Usize) (c : Std.Usize) (hn : n.val = input.length) :
    slot.fl_sample_loop input h n st k c ⦃ fun _ => True ⦄ := by
  rw [slot.fl_sample_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => 8192 - s.2.2.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1, x2⟩ _
    simp only [slot.fl_sample_loop.body, lift, Array.to_slice_mut]
    step*
    repeat (first
      | (intro hc; (try step*))
      | (split <;> (try step*))
      | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply spec_ite_cut <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals (first | omega | scalar_tac)
  · trivial

end A2StepScope20
open scoped Submission.A2StepScope20
theorem fl_sample_spec (input : Slice Std.U8) (h : Array Std.U32 256#usize) :
    slot.fl_sample input h ⦃ fun _ => True ⦄ := by
  rw [slot.fl_sample]
  step*
  repeat (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)

namespace A2StepScope21
@[scoped step]
theorem _root_.Submission.fl_costs_loop0_spec (h : Array Std.U32 256#usize) (t : Std.U32) (i : Std.Usize)  :
    slot.fl_costs_loop0 h t i ⦃ fun _ => True ⦄ := by
  rw [slot.fl_costs_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun s => 256 - s.2.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1⟩ _
    simp only [slot.fl_costs_loop0.body, lift, Array.to_slice_mut]
    step*
    repeat (first
      | (intro hc; (try step*))
      | (split <;> (try step*))
      | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply spec_ite_cut <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals (first | omega | scalar_tac)
  · trivial

end A2StepScope21
open scoped Submission.A2StepScope21
namespace A2StepScope22
@[scoped step]
theorem _root_.Submission.fl_costs_loop1_spec (h : Array Std.U32 256#usize) (cost : Array Std.U32 256#usize) (lt : Std.U32) (j : Std.Usize)  :
    slot.fl_costs_loop1 h cost lt j ⦃ fun _ => True ⦄ := by
  rw [slot.fl_costs_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun s => 256 - s.2.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1⟩ _
    simp only [slot.fl_costs_loop1.body, lift, Array.to_slice_mut]
    step*
    repeat (first
      | (intro hc; (try step*))
      | (split <;> (try step*))
      | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply spec_ite_cut <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals (first | omega | scalar_tac)
  · trivial

end A2StepScope22
open scoped Submission.A2StepScope22
namespace A2StepScope23
@[scoped step]
theorem _root_.Submission.fl_costs_spec (h : Array Std.U32 256#usize) (cost : Array Std.U32 256#usize) :
    slot.fl_costs h cost ⦃ fun _ => True ⦄ := by
  rw [slot.fl_costs]
  step*
  repeat (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)

end A2StepScope23
open scoped Submission.A2StepScope23
namespace A2StepScope24
@[scoped step]
theorem _root_.Submission.fl_ent_loop0_spec (h : Array Std.U32 1024#usize) (base : Std.Usize) (t : Std.U32) (i : Std.Usize)  :
    slot.fl_ent_loop0 h base t i ⦃ fun _ => True ⦄ := by
  rw [slot.fl_ent_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun s => 256 - s.2.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1⟩ _
    simp only [slot.fl_ent_loop0.body, lift, Array.to_slice_mut]
    step*
    repeat (first
      | (intro hc; (try step*))
      | (split <;> (try step*))
      | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply spec_ite_cut <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals (first | omega | scalar_tac)
  · trivial

end A2StepScope24
open scoped Submission.A2StepScope24
namespace A2StepScope25
@[scoped step]
theorem _root_.Submission.fl_ent_loop1_spec (h : Array Std.U32 1024#usize) (base : Std.Usize) (lt : Std.U32) (bits : Std.Usize) (j : Std.Usize)  :
    slot.fl_ent_loop1 h base lt bits j ⦃ fun _ => True ⦄ := by
  rw [slot.fl_ent_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun s => 256 - s.2.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1⟩ _
    simp only [slot.fl_ent_loop1.body, lift, Array.to_slice_mut]
    step*
    repeat (first
      | (intro hc; (try step*))
      | (split <;> (try step*))
      | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply spec_ite_cut <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals (first | omega | scalar_tac)
  · trivial

end A2StepScope25
open scoped Submission.A2StepScope25
namespace A2StepScope26
@[scoped step]
theorem _root_.Submission.fl_ent_spec (h : Array Std.U32 1024#usize) (base : Std.Usize) :
    slot.fl_ent h base ⦃ fun _ => True ⦄ := by
  rw [slot.fl_ent]
  step*
  repeat (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)

end A2StepScope26
open scoped Submission.A2StepScope26
namespace A2StepScope27
open scoped A2FastCut A2FastPureChoice in
@[scoped step]
theorem _root_.Submission.fl_stats_loop0_spec (h : Array Std.U32 256#usize) (t : Std.U32) (i : Std.Usize)  :
    slot.fl_stats_loop0 h t i ⦃ fun _ => True ⦄ := by
  rw [slot.fl_stats_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun s => 256 - s.2.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1⟩ _
    simp only [slot.fl_stats_loop0.body, lift, Array.to_slice_mut]
    step*
    repeat (first
      | (intro hc; (try step*))
      | (split <;> (try step*))
      | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply spec_ite_cut <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals (first | omega | scalar_tac)
  · trivial

end A2StepScope27
open scoped Submission.A2StepScope27
namespace A2StepScope28
open scoped A2FastPureChoice in
@[scoped step]
theorem _root_.Submission.fl_stats_loop1_spec (h : Array Std.U32 256#usize) (t : Std.U32) (lt : Std.U32) (bits : Std.Usize) (top : Std.U32) (np : Std.Usize) (big : Std.Usize) (bigsum : Std.Usize) (j : Std.Usize)  :
    slot.fl_stats_loop1 h t lt bits top np big bigsum j ⦃ fun _ => True ⦄ := by
  rw [slot.fl_stats_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun s => 256 - s.2.2.2.2.2.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1, x2, x3, x4, x5⟩ _
    simp only [slot.fl_stats_loop1.body, lift, Array.to_slice_mut]
    step*
    repeat (first
      | (intro hc; (try step*))
      | (split <;> (try step*))
      | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply spec_ite_cut <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals (first | omega | scalar_tac)
  · trivial

end A2StepScope28
open scoped Submission.A2StepScope28
theorem fl_stats_spec (h : Array Std.U32 256#usize) :
    slot.fl_stats h ⦃ fun _ => True ⦄ := by
  rw [slot.fl_stats]
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)

namespace A2StepScope29
open scoped A2FastPureChoice in
@[scoped step]
theorem _root_.Submission.fl_probe_chunk_loop_spec (input : Slice Std.U8) (tab : Array Std.U32 4096#usize) (ph : Array Std.U32 1024#usize) (s : Std.Usize) (p : Std.Usize) (k : Std.Usize) (c4 : Std.Usize)  :
    slot.fl_probe_chunk_loop input tab ph s p k c4 ⦃ fun _ => True ⦄ := by
  rw [slot.fl_probe_chunk_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => slot.FL_PCH.val - s.2.2.2.1.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1, x2, x3, x4⟩ _
    simp only [slot.fl_probe_chunk_loop.body, lift, Array.to_slice_mut]
    step*
    repeat (first
      | (intro hc; (try step*))
      | (split <;> (try step*))
      | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply spec_ite_cut <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals (first | omega | scalar_tac)
  · trivial

end A2StepScope29
open scoped Submission.A2StepScope29
namespace A2StepScope30
open scoped A2FastCut A2FastPureChoice in
@[scoped step]
theorem _root_.Submission.fl_weights_loop_spec (input : Slice Std.U8) (tab : Array Std.U32 4096#usize) (ph : Array Std.U32 1024#usize) (span : Std.Usize) (c4 : Std.Usize) (i : Std.Usize)  :
    slot.fl_weights_loop input tab ph span c4 i ⦃ fun _ => True ⦄ := by
  rw [slot.fl_weights_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => slot.FL_PNC.val - s.2.2.2.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1, x2, x3⟩ _
    simp only [slot.fl_weights_loop.body, lift, Array.to_slice_mut]
    step*
    repeat (first
      | (intro hc; (try step*))
      | (split <;> (try step*))
      | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply spec_ite_cut <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals (first | omega | scalar_tac)
  · trivial

end A2StepScope30
open scoped Submission.A2StepScope30
namespace A2StepScope31
-- (fl_weights_spec regenerated below)
end A2StepScope31
open scoped Submission.A2StepScope31
-- (fl_mode_spec regenerated below)
namespace A2StepScope32
open scoped A2FastCut A2FastPureChoice in
@[scoped step]
theorem _root_.Submission.fl_config_spec («class» : Std.Usize) (cf : Array Std.Usize 8#usize) :
    slot.fl_config «class» cf ⦃ fun _ => True ⦄ := by
  rw [slot.fl_config]
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)

end A2StepScope32
open scoped Submission.A2StepScope32
section
namespace A2StepScope33
attribute [scoped step] Submission.ite_true_spec
end A2StepScope33
open scoped Submission.A2StepScope33

namespace A2StepScope34
@[scoped step]
theorem _root_.Submission.fl_lit_parse_spec (input : Slice Std.U8) (out : Slice Std.U32)
    (hlen : input.length ≤ out.length) :
    slot.fl_lit_parse input out ⦃ fun r =>
      r.1.2.val ≤ input.length ∧ r.1.1.val ≤ r.1.2.val ∧ r.2.length = out.length ∧
      LZ77.decode (toks r.2 r.1.1.val) = some ((bytes input).take r.1.2.val) ⦄ := by
  rw [slot.fl_lit_parse]
  have h0 := decode_nil input out
  try simp only [lift, Array.to_slice_mut, alloc.vec.Vec.deref_mut, bind_tc_ok]
  step*
  all_goals (repeat (first
    | (refine ⟨by (first | omega | scalar_tac), by (first | omega | scalar_tac), by (first | omega | scalar_tac), by assumption⟩)
    | (intro hc; (try step*))
    | (casesm* _ × _; (try simp only []); (try step*))
    | (split <;> (try step*))
    | (step <;> (try step*))))
  all_goals (try (first | omega | scalar_tac))

end A2StepScope34
open scoped Submission.A2StepScope34
end
open scoped Submission.A2StepScope34

section
open scoped Submission.A2StepScope33

namespace A2StepScope35
-- (fl_rle_parse_loop_spec regenerated below)
end A2StepScope35
open scoped Submission.A2StepScope35
end
open scoped Submission.A2StepScope35

section
open scoped Submission.A2StepScope33

namespace A2StepScope36
-- (fl_rle_parse_spec regenerated below)
end A2StepScope36
open scoped Submission.A2StepScope36
end
open scoped Submission.A2StepScope36

namespace A2StepScope37
@[scoped step]
theorem _root_.Submission.fl_cheap_run_loop_spec (input : Slice Std.U8) (cost : Array Std.U32 256#usize) (n : Std.Usize) (k : Std.Usize) (hn : n.val = input.length) :
    slot.fl_cheap_run_loop input cost n k ⦃ fun _ => True ⦄ := by
  rw [slot.fl_cheap_run_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => n.val - s.val)
    (inv := fun s => True)
  · rintro x0 _
    simp only [slot.fl_cheap_run_loop.body, lift, Array.to_slice_mut]
    step*
    repeat (first
      | (intro hc; (try step*))
      | (split <;> (try step*))
      | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply spec_ite_cut <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals (first | omega | scalar_tac)
  · trivial

end A2StepScope37
open scoped Submission.A2StepScope37
namespace A2StepScope38
@[scoped step]
theorem _root_.Submission.fl_cheap_run_spec (input : Slice Std.U8) (cost : Array Std.U32 256#usize) (pos : Std.Usize) :
    slot.fl_cheap_run input cost pos ⦃ fun _ => True ⦄ := by
  rw [slot.fl_cheap_run]
  step*
  repeat (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)

end A2StepScope38
open scoped Submission.A2StepScope38
namespace A2StepScope39
@[scoped step]
theorem _root_.Submission.fl_span_cost_loop_spec (input : Slice Std.U8) (cost : Array Std.U32 256#usize) (pos : Std.Usize) (l : Std.Usize) (s : Std.Usize) (i : Std.Usize)  :
    slot.fl_span_cost_loop input cost pos l s i ⦃ fun _ => True ⦄ := by
  rw [slot.fl_span_cost_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => l.val - s.2.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1⟩ _
    simp only [slot.fl_span_cost_loop.body, lift, Array.to_slice_mut]
    step*
    repeat (first
      | (intro hc; (try step*))
      | (split <;> (try step*))
      | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply spec_ite_cut <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals (first | omega | scalar_tac)
  · trivial

end A2StepScope39
open scoped Submission.A2StepScope39
namespace A2StepScope40
@[scoped step]
theorem _root_.Submission.fl_dextra_spec (d : Std.Usize) :
    slot.fl_dextra d ⦃ fun _ => True ⦄ := by
  rw [slot.fl_dextra]
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)

end A2StepScope40
open scoped Submission.A2StepScope40
namespace A2StepScope41
@[scoped step]
theorem _root_.Submission.fl_lextra_spec (l : Std.Usize) :
    slot.fl_lextra l ⦃ fun _ => True ⦄ := by
  rw [slot.fl_lextra]
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)

end A2StepScope41
open scoped Submission.A2StepScope41
namespace A2StepScope42
@[scoped step]
theorem _root_.Submission.fl_dna_ok_spec (input : Slice Std.U8) (cost : Array Std.U32 256#usize) (pos : Std.Usize) (l : Std.Usize) (d : Std.Usize) :
    slot.fl_dna_ok input cost pos l d ⦃ fun _ => True ⦄ := by
  rw [slot.fl_dna_ok]
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)

end A2StepScope42
open scoped Submission.A2StepScope42
namespace A2StepScope43
@[scoped step]
theorem _root_.Submission.fl_dwalk_loop_spec (input : Slice Std.U8) (prev : Array Std.U32 32768#usize) (pos : Std.Usize) (cap : Std.Usize) (depth : Std.Usize) (bl : Std.Usize) (bd : Std.Usize) (cur : Std.Usize) (k : Std.Usize)  :
    slot.fl_dwalk_loop input prev pos cap depth bl bd cur k ⦃ fun _ => True ⦄ := by
  rw [slot.fl_dwalk_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => depth.val - s.2.2.2.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1, x2, x3⟩ _
    simp only [slot.fl_dwalk_loop.body, lift, Array.to_slice_mut]
    step*
    repeat (first
      | (intro hc; (try step*))
      | (split <;> (try step*))
      | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply spec_ite_cut <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals (first | omega | scalar_tac)
  · trivial

end A2StepScope43
open scoped Submission.A2StepScope43
namespace A2StepScope44
@[scoped step]
theorem _root_.Submission.fl_dwalk_spec (input : Slice Std.U8) (prev : Array Std.U32 32768#usize) (pos : Std.Usize) (start : Std.Usize) (cap : Std.Usize) (depth : Std.Usize) :
    slot.fl_dwalk input prev pos start cap depth ⦃ fun _ => True ⦄ := by
  rw [slot.fl_dwalk]
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)

end A2StepScope44
open scoped Submission.A2StepScope44
namespace A2StepScope45
@[scoped step]
theorem _root_.Submission.fl_dsearch_spec (input : Slice Std.U8) (head : Array Std.U32 65536#usize) (prev : Array Std.U32 32768#usize) (p : Std.Usize) (depth : Std.Usize) :
    slot.fl_dsearch input head prev p depth ⦃ fun _ => True ⦄ := by
  rw [slot.fl_dsearch]
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)

end A2StepScope45
open scoped Submission.A2StepScope45
namespace A2StepScope46
@[scoped step]
theorem _root_.Submission.fl_tinsert_loop_spec (input : Slice Std.U8) (head : Array Std.U16 16384#usize) (prev : Array Std.U16 32768#usize) («to» : Std.Usize) (hsh : Std.U64) (lim : Std.Usize) (p : Std.Usize)  :
    slot.fl_tinsert_loop input head prev «to» hsh lim p ⦃ fun _ => True ⦄ := by
  rw [slot.fl_tinsert_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => «to».val - s.2.2.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1, x2⟩ _
    simp only [slot.fl_tinsert_loop.body, lift, Array.to_slice_mut]
    step*
    repeat (first
      | (intro hc; (try step*))
      | (split <;> (try step*))
      | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply spec_ite_cut <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals (first | omega | scalar_tac)
  · trivial

end A2StepScope46
open scoped Submission.A2StepScope46
namespace A2StepScope47
@[scoped step]
theorem _root_.Submission.fl_tinsert_spec (input : Slice Std.U8) (head : Array Std.U16 16384#usize) (prev : Array Std.U16 32768#usize) («from» : Std.Usize) («to» : Std.Usize) (hsh : Std.U64) :
    slot.fl_tinsert input head prev «from» «to» hsh ⦃ fun _ => True ⦄ := by
  rw [slot.fl_tinsert]
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)

end A2StepScope47
open scoped Submission.A2StepScope47
namespace A2StepScope48
@[scoped step]
theorem _root_.Submission.fl_insert_loop_spec (input : Slice Std.U8) (head : Array Std.U32 65536#usize) (prev : Array Std.U32 32768#usize) («to» : Std.Usize) (hsh : Std.U64) (lim : Std.Usize) (p : Std.Usize)  :
    slot.fl_insert_loop input head prev «to» hsh lim p ⦃ fun _ => True ⦄ := by
  rw [slot.fl_insert_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => «to».val - s.2.2.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1, x2⟩ _
    simp only [slot.fl_insert_loop.body, lift, Array.to_slice_mut]
    step*
    repeat (first
      | (intro hc; (try step*))
      | (split <;> (try step*))
      | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply spec_ite_cut <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals (first | omega | scalar_tac)
  · trivial

end A2StepScope48
open scoped Submission.A2StepScope48
namespace A2StepScope49
@[scoped step]
theorem _root_.Submission.fl_insert_spec (input : Slice Std.U8) (head : Array Std.U32 65536#usize) (prev : Array Std.U32 32768#usize) («from» : Std.Usize) («to» : Std.Usize) (hsh : Std.U64) :
    slot.fl_insert input head prev «from» «to» hsh ⦃ fun _ => True ⦄ := by
  rw [slot.fl_insert]
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)

end A2StepScope49
open scoped Submission.A2StepScope49
section
open scoped Submission.A2StepScope33

namespace A2StepScope50
@[scoped step]
theorem _root_.Submission.fl_dna_parse_loop_spec (input : Slice Std.U8) (out0 : Slice Std.U32) (cost : Array Std.U32 256#usize) (n : Std.Usize) (head0 : Array Std.U32 65536#usize) (prev0 : Array Std.U32 32768#usize) (pos0 : Std.Usize) (ntok0 : Std.Usize)
    (hn : n.val = input.length) (hout : input.length ≤ out0.length)
    (hp : pos0.val ≤ n.val) (hntok : ntok0.val ≤ pos0.val)
    (hdec : LZ77.decode (toks out0 ntok0.val) = some ((bytes input).take pos0.val)) :
    slot.fl_dna_parse_loop input out0 cost n head0 prev0 pos0 ntok0 ⦃ fun r =>
      r.2.1.val ≤ n.val ∧ r.2.2.val ≤ r.2.1.val ∧ r.1.length = out0.length ∧
      LZ77.decode (toks r.1 r.2.2.val) = some ((bytes input).take r.2.1.val) ⦄ := by
  rw [slot.fl_dna_parse_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => n.val - s.2.2.2.1.val)
    (inv := fun s =>
      s.2.2.2.1.val ≤ n.val ∧ s.2.2.2.2.val ≤ s.2.2.2.1.val ∧ s.1.length = out0.length ∧
      LZ77.decode (toks s.1 s.2.2.2.2.val) = some ((bytes input).take s.2.2.2.1.val))
  · rintro ⟨out, head, prev, pos, ntok⟩ ⟨hpn, hnt, hlen, hde⟩
    simp only at hpn hnt hlen hde
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.fl_dna_parse_loop.body, lift, Array.to_slice_mut, alloc.vec.Vec.deref_mut, bind_tc_ok]
    split
    case isTrue hlt =>
      step*
      all_goals (repeat (first
        | (refine ⟨by (first | omega | scalar_tac), by (first | omega | scalar_tac), by assumption, by assumption, by (first | omega | scalar_tac)⟩)
        | (intro hc; (try step*))
        | (casesm* _ × _; (try simp only []); (try step*))
        | (split <;> (try step*))
        | (step <;> (try step*))))
      all_goals (try (first | omega | scalar_tac))
    case isFalse hge =>
      exact ⟨hpn, hnt, hlen, hde⟩
  · exact ⟨hp, hntok, rfl, hdec⟩

end A2StepScope50
open scoped Submission.A2StepScope50
end
open scoped Submission.A2StepScope50

section
open scoped Submission.A2StepScope33

namespace A2StepScope51
@[scoped step]
theorem _root_.Submission.fl_dna_parse_spec (input : Slice Std.U8) (out : Slice Std.U32) (cost : Array Std.U32 256#usize)
    (hlen : input.length ≤ out.length) :
    slot.fl_dna_parse input out cost ⦃ fun r =>
      r.1.2.val ≤ input.length ∧ r.1.1.val ≤ r.1.2.val ∧ r.2.length = out.length ∧
      LZ77.decode (toks r.2 r.1.1.val) = some ((bytes input).take r.1.2.val) ⦄ := by
  rw [slot.fl_dna_parse]
  have h0 := decode_nil input out
  try simp only [lift, Array.to_slice_mut, alloc.vec.Vec.deref_mut, bind_tc_ok]
  step*
  all_goals (repeat (first
    | (refine ⟨by (first | omega | scalar_tac), by (first | omega | scalar_tac), by (first | omega | scalar_tac), by assumption⟩)
    | (intro hc; (try step*))
    | (casesm* _ × _; (try simp only []); (try step*))
    | (split <;> (try step*))
    | (step <;> (try step*))))
  all_goals (try (first | omega | scalar_tac))

end A2StepScope51
open scoped Submission.A2StepScope51
end
open scoped Submission.A2StepScope51

namespace A2StepScope52
@[scoped step]
theorem _root_.Submission.fl_score_spec (l : Std.Usize) (d : Std.Usize) (litq : Std.Usize) :
    slot.fl_score l d litq ⦃ fun _ => True ⦄ := by
  rw [slot.fl_score]
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)

end A2StepScope52
open scoped Submission.A2StepScope52
namespace A2StepScope53
@[scoped step]
theorem _root_.Submission.fl_lg8_spec (x : Std.U32) :
    slot.fl_lg8 x ⦃ fun _ => True ⦄ := by
  rw [slot.fl_lg8]
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)

end A2StepScope53
open scoped Submission.A2StepScope53
namespace A2StepScope54
@[scoped step]
theorem _root_.Submission.fl_entropy256_loop_spec (h : Array Std.U32 256#usize) (tot : Std.U64) (acc : Std.U64) (i : Std.Usize)  :
    slot.fl_entropy256_loop h tot acc i ⦃ fun _ => True ⦄ := by
  rw [slot.fl_entropy256_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => 256 - s.2.2.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1, x2⟩ _
    simp only [slot.fl_entropy256_loop.body, lift, Array.to_slice_mut]
    step*
    repeat (first
      | (intro hc; (try step*))
      | (split <;> (try step*))
      | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply spec_ite_cut <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals (first | omega | scalar_tac)
  · trivial

end A2StepScope54
open scoped Submission.A2StepScope54
namespace A2StepScope55
@[scoped step]
theorem _root_.Submission.fl_entropy256_spec (h : Array Std.U32 256#usize) :
    slot.fl_entropy256 h ⦃ fun _ => True ⦄ := by
  rw [slot.fl_entropy256]
  step*
  repeat (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)

end A2StepScope55
open scoped Submission.A2StepScope55
namespace A2StepScope56
@[scoped step]
theorem _root_.Submission.fl_lit_cost_spec (h0 : Std.Usize) :
    slot.fl_lit_cost h0 ⦃ fun _ => True ⦄ := by
  rw [slot.fl_lit_cost]
  step*
  repeat (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)

end A2StepScope56
open scoped Submission.A2StepScope56
namespace A2StepScope57
open scoped A2FastPureChoice in
@[scoped step]
theorem _root_.Submission.fl_walk_loop_spec (input : Slice Std.U8) (prev : Array Std.U16 32768#usize) (pos : Std.Usize) (cap : Std.Usize) (depth : Std.Usize) (litq : Std.Usize) (nice : Std.Usize) (bl : Std.Usize) (bd : Std.Usize) (bs : Std.Usize) (cur : Std.Usize) (k : Std.Usize) (off : Std.Usize) (want : Std.U32)  :
    slot.fl_walk_loop input prev pos cap depth litq nice bl bd bs cur k off want ⦃ fun _ => True ⦄ := by
  rw [slot.fl_walk_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => depth.val - s.2.2.2.2.1.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1, x2, x3, x4, x5, x6⟩ _
    simp only [slot.fl_walk_loop.body, lift, Array.to_slice_mut]
    step*
    repeat (first
      | (intro hc; (try step*))
      | (split <;> (try step*))
      | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply spec_ite_cut <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals (first | omega | scalar_tac)
  · trivial

end A2StepScope57
open scoped Submission.A2StepScope57
namespace A2StepScope58
@[scoped step]
theorem _root_.Submission.fl_walk_spec (input : Slice Std.U8) (prev : Array Std.U16 32768#usize) (pos : Std.Usize) (start : Std.Usize) (cap : Std.Usize) (depth : Std.Usize) (bl0 : Std.Usize) (bs0 : Std.Usize) (litq : Std.Usize) (nice : Std.Usize) :
    slot.fl_walk input prev pos start cap depth bl0 bs0 litq nice ⦃ fun _ => True ⦄ := by
  rw [slot.fl_walk]
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)

end A2StepScope58
open scoped Submission.A2StepScope58
namespace A2StepScope59
@[scoped step]
theorem _root_.Submission.fl_search_spec (input : Slice Std.U8) (head : Array Std.U16 16384#usize) (prev : Array Std.U16 32768#usize) (pos : Std.Usize) (depth : Std.Usize) (ins : Std.Usize) (bl0 : Std.Usize) (bs0 : Std.Usize) (litq : Std.Usize) (hsh : Std.U64) (nice : Std.Usize) :
    slot.fl_search input head prev pos depth ins bl0 bs0 litq hsh nice ⦃ fun _ => True ⦄ := by
  rw [slot.fl_search]
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)

end A2StepScope59
open scoped Submission.A2StepScope59
namespace A2StepScope60
@[scoped step]
theorem _root_.Submission.fl_insert_match_spec (input : Slice Std.U8) (head : Array Std.U16 16384#usize) (prev : Array Std.U16 32768#usize) («from» : Std.Usize) («to» : Std.Usize) (hsh : Std.U64) (ih : Std.Usize) (it : Std.Usize) :
    slot.fl_insert_match input head prev «from» «to» hsh ih it ⦃ fun _ => True ⦄ := by
  rw [slot.fl_insert_match]
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)

end A2StepScope60
open scoped Submission.A2StepScope60
namespace A2StepScope61
@[scoped step]
theorem _root_.Submission.fl_lits_spec (miss : Std.Usize) (acc : Std.Usize) :
    slot.fl_lits miss acc ⦃ fun _ => True ⦄ := by
  rw [slot.fl_lits]
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)

end A2StepScope61
open scoped Submission.A2StepScope61
namespace A2StepScope62
@[scoped step]
theorem _root_.Submission.fl_litq_spec (h0 : Std.Usize) :
    slot.fl_litq h0 ⦃ fun _ => True ⦄ := by
  rw [slot.fl_litq]
  step*
  repeat (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)

end A2StepScope62
open scoped Submission.A2StepScope62
namespace A2StepScope63
@[scoped step]
theorem _root_.Submission.fl_hsh_spec (h0 : Std.Usize) :
    slot.fl_hsh h0 ⦃ fun _ => True ⦄ := by
  rw [slot.fl_hsh]
  step*
  repeat (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)

end A2StepScope63
open scoped Submission.A2StepScope63
section
open scoped Submission.A2StepScope33

namespace A2StepScope64
@[scoped step]
theorem _root_.Submission.fl_lazy_parse_loop_spec (input : Slice Std.U8) (out0 : Slice Std.U32) (n : Std.Usize) (depth : Std.Usize) (depth2 : Std.Usize) (lazy : Std.Usize) (nice : Std.Usize) (ih : Std.Usize) (it : Std.Usize) (acc : Std.Usize) (litq : Std.Usize) (hsh : Std.U64) (head0 : Array Std.U16 16384#usize) (prev0 : Array Std.U16 32768#usize) (pos0 : Std.Usize) (ntok0 : Std.Usize) (carry0 : Std.Usize) (miss0 : Std.Usize)
    (hn : n.val = input.length) (hout : input.length ≤ out0.length)
    (hp : pos0.val ≤ n.val) (hntok : ntok0.val ≤ pos0.val)
    (hdec : LZ77.decode (toks out0 ntok0.val) = some ((bytes input).take pos0.val)) :
    slot.fl_lazy_parse_loop input out0 n depth depth2 lazy nice ih it acc litq hsh head0 prev0 pos0 ntok0 carry0 miss0 ⦃ fun r =>
      r.2.1.val ≤ n.val ∧ r.2.2.val ≤ r.2.1.val ∧ r.1.length = out0.length ∧
      LZ77.decode (toks r.1 r.2.2.val) = some ((bytes input).take r.2.1.val) ⦄ := by
  rw [slot.fl_lazy_parse_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => n.val - s.2.2.2.1.val)
    (inv := fun s =>
      s.2.2.2.1.val ≤ n.val ∧ s.2.2.2.2.1.val ≤ s.2.2.2.1.val ∧ s.1.length = out0.length ∧
      LZ77.decode (toks s.1 s.2.2.2.2.1.val) = some ((bytes input).take s.2.2.2.1.val))
  · rintro ⟨out, head, prev, pos, ntok, carry, miss⟩ ⟨hpn, hnt, hlen, hde⟩
    simp only at hpn hnt hlen hde
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.fl_lazy_parse_loop.body, lift, Array.to_slice_mut, alloc.vec.Vec.deref_mut, bind_tc_ok]
    split
    case isTrue hlt =>
      step*
      all_goals (repeat (first
        | (refine ⟨by (first | omega | scalar_tac), by (first | omega | scalar_tac), by assumption, by assumption, by (first | omega | scalar_tac)⟩)
        | (intro hc; (try step*))
        | (casesm* _ × _; (try simp only []); (try step*))
        | (split <;> (try step*))
        | (step <;> (try step*))))
      all_goals (try (first | omega | scalar_tac))
    case isFalse hge =>
      exact ⟨hpn, hnt, hlen, hde⟩
  · exact ⟨hp, hntok, rfl, hdec⟩

end A2StepScope64
open scoped Submission.A2StepScope64
end
open scoped Submission.A2StepScope64

section
open scoped Submission.A2StepScope33

namespace A2StepScope65
@[scoped step]
theorem _root_.Submission.fl_lazy_parse_spec (input : Slice Std.U8) (out : Slice Std.U32) (lh : Array Std.U32 256#usize) (cf : Array Std.Usize 8#usize)
    (hlen : input.length ≤ out.length) :
    slot.fl_lazy_parse input out lh cf ⦃ fun r =>
      r.1.2.val ≤ input.length ∧ r.1.1.val ≤ r.1.2.val ∧ r.2.length = out.length ∧
      LZ77.decode (toks r.2 r.1.1.val) = some ((bytes input).take r.1.2.val) ⦄ := by
  rw [slot.fl_lazy_parse]
  have h0 := decode_nil input out
  try simp only [lift, Array.to_slice_mut, alloc.vec.Vec.deref_mut, bind_tc_ok]
  step*
  all_goals (repeat (first
    | (refine ⟨by (first | omega | scalar_tac), by (first | omega | scalar_tac), by (first | omega | scalar_tac), by assumption⟩)
    | (intro hc; (try step*))
    | (casesm* _ × _; (try simp only []); (try step*))
    | (split <;> (try step*))
    | (step <;> (try step*))))
  all_goals (try (first | omega | scalar_tac))

end A2StepScope65
open scoped Submission.A2StepScope65
end
open scoped Submission.A2StepScope65

section
open scoped Submission.A2StepScope33

namespace A2StepScope66
-- (fl_part_spec regenerated below)
end A2StepScope66
open scoped Submission.A2StepScope66
end
open scoped Submission.A2StepScope66

-- The batched search remains untrusted: only termination and no panic.
end Submission

/- Round-8 additions generated by p0/mkparse2.py (--base full): new functions on top of cand25's complete proof. -/
namespace Submission
open Aeneas Aeneas.Std Result ControlFlow
open LZ77 (toks bytes bytes_length bytes_getElem! toks_update bytes_congr Matches emit_lit emit_match ite_ok)
set_option maxRecDepth 8192
set_option maxHeartbeats 4000000
set_option linter.unusedTactic false
set_option linter.unreachableTactic false
set_option linter.unusedVariables false
set_option linter.unusedSimpArgs false
open scoped Submission.A2StepScope1 Submission.A2StepScope2 Submission.A2StepScope3 Submission.A2StepScope4 Submission.A2StepScope5 Submission.A2StepScope6 Submission.E2Scope Submission.A2StepScope7 Submission.A2StepScope8 Submission.A2StepScope9 Submission.A2StepScope10 Submission.A2StepScope11 Submission.A2StepScope12 Submission.A2StepScope13 Submission.A2StepScope14 Submission.A2StepScope15 Submission.A2StepScope16 Submission.A2StepScope17 Submission.A2StepScope18 Submission.A2StepScope19 Submission.A2StepScope20 Submission.A2StepScope21 Submission.A2StepScope22 Submission.A2StepScope23 Submission.A2StepScope24 Submission.A2StepScope25 Submission.A2StepScope26 Submission.A2StepScope27 Submission.A2StepScope28 Submission.A2StepScope29 Submission.A2StepScope30 Submission.A2StepScope31 Submission.A2StepScope32 Submission.A2StepScope34 Submission.A2StepScope35 Submission.A2StepScope36 Submission.A2StepScope37 Submission.A2StepScope38 Submission.A2StepScope39 Submission.A2StepScope40 Submission.A2StepScope41 Submission.A2StepScope42 Submission.A2StepScope43 Submission.A2StepScope44 Submission.A2StepScope45 Submission.A2StepScope46 Submission.A2StepScope47 Submission.A2StepScope48 Submission.A2StepScope49 Submission.A2StepScope50 Submission.A2StepScope51 Submission.A2StepScope52 Submission.A2StepScope53 Submission.A2StepScope54 Submission.A2StepScope55 Submission.A2StepScope56 Submission.A2StepScope57 Submission.A2StepScope58 Submission.A2StepScope59 Submission.A2StepScope60 Submission.A2StepScope61 Submission.A2StepScope62 Submission.A2StepScope63 Submission.A2StepScope64 Submission.A2StepScope65 Submission.A2StepScope66


/-- `n.saturating_sub k` has the truncated-subtraction value (Aeneas defines it through `BitVec.ofNat`). -/
@[simp, scalar_tac_simps]
theorem Usize_saturating_sub_val (x y : Std.Usize) : (core.num.Usize.saturating_sub x y).val = x.val - y.val := by
  simp only [core.num.Usize.saturating_sub, UScalar.saturating_sub, Nat.zero_max]
  simp only [UScalar.val, BitVec.toNat_ofNat]
  exact Nat.mod_eq_of_lt (by have := x.hBounds; omega)

/-- A `Valid` phase result read back as the decode invariant at `input.len()`. -/
theorem decode_of_valid {input : Slice Std.U8} {o : Slice Std.U32} {t : Std.Usize}
    (h : LZ77.Valid (bytes input) (toks o t.val)) :
    LZ77.decode (toks o t.val) = some ((bytes input).take (Slice.len input).val) := by
  unfold LZ77.Valid at h
  rw [h, Slice.len_val, ← bytes_length input, List.take_length]

/- Base trusted kit: verbatim from cand9 (same Rust bodies as cand25's, checked on the extraction). -/
theorem words_eq_loop_spec (input : Slice Std.U8) (a b cap l0 : Std.Usize)
    (ha : a.val + cap.val ≤ input.length) (hb : b.val + cap.val ≤ input.length)
    (hl0 : l0.val ≤ cap.val) (h0 : Matches input a.val b.val l0.val) :
    slot.words_eq_loop input a b cap l0 ⦃ fun l =>
      l.val ≤ cap.val ∧ Matches input a.val b.val l.val ⦄ := by
  rw [slot.words_eq_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun l => cap.val - l.val)
    (inv := fun l => l.val ≤ cap.val ∧ Matches input a.val b.val l.val)
  · rintro l ⟨hle, hinv⟩
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.words_eq_loop.body]
    step*
    all_goals first
      | exact ⟨hle, hinv⟩
      | (refine ⟨by scalar_tac, ?_, by scalar_tac⟩
         rw [show l1.val = l.val + 8 by scalar_tac]
         apply Matches.add8 hinv
         rw [show a.val + l.val = i1.val by scalar_tac, show b.val + l.val = i3.val by scalar_tac,
           ← i2_post, ← i4_post, ‹i2 = i4›])
  · exact ⟨hl0, h0⟩

@[local step]
theorem tail_eq_spec (input : Slice Std.U8) (a b cap l : Std.Usize)
    (ha : a.val + cap.val ≤ input.length) (hb : b.val + cap.val ≤ input.length) (hl : l.val ≤ cap.val) :
    slot.tail_eq input a b cap l ⦃ fun r => r.val = 1 →
      8 ≤ cap.val ∧ cap.val ≤ l.val + 8 ∧
      w8 input (a.val + (cap.val - 8)) = w8 input (b.val + (cap.val - 8)) ⦄ := by
  rw [slot.tail_eq]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  step*
  all_goals first
    | (intro h; simp at h)
    | (intro _
       refine ⟨by scalar_tac, by scalar_tac, ?_⟩
       rw [show a.val + (cap.val - 8) = i2.val by scalar_tac,
         show b.val + (cap.val - 8) = i4.val by scalar_tac, ← i3_post, ← i5_post, ‹i3 = i5›])
    | (refine ⟨by scalar_tac, by scalar_tac, ?_⟩
       rw [show a.val + (cap.val - 8) = i2.val by scalar_tac,
         show b.val + (cap.val - 8) = i4.val by scalar_tac, ← i3_post, ← i5_post, ‹i3 = i5›])

@[local step]
theorem short_eq_spec (input : Slice Std.U8) (a b cap : Std.Usize)
    (ha : a.val + cap.val ≤ input.length) (hb : b.val + cap.val ≤ input.length) :
    slot.short_eq input a b cap ⦃ fun r => r.val = 1 →
      4 ≤ cap.val ∧ cap.val < 8 ∧ w4 input a.val = w4 input b.val ∧
      w4 input (a.val + (cap.val - 4)) = w4 input (b.val + (cap.val - 4)) ⦄ := by
  rw [slot.short_eq]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  step*
  all_goals first
    | (intro h; simp at h)
    | (intro _
       refine ⟨by scalar_tac, by scalar_tac, ?_, ?_⟩
       · rw [← i_post, ← i1_post]
         simp_all
       · rw [show a.val + (cap.val - 4) = i3.val by scalar_tac,
           show b.val + (cap.val - 4) = i5.val by scalar_tac, ← i4_post, ← i6_post, ‹i4 = i6›])
    | (refine ⟨by scalar_tac, by scalar_tac, ?_, ?_⟩
       · rw [← i_post, ← i1_post]
         simp_all
       · rw [show a.val + (cap.val - 4) = i3.val by scalar_tac,
           show b.val + (cap.val - 4) = i5.val by scalar_tac, ← i4_post, ← i6_post, ‹i4 = i6›])

@[local step]
theorem words_eq_spec (input : Slice Std.U8) (a b cap : Std.Usize)
    (ha : a.val + cap.val ≤ input.length) (hb : b.val + cap.val ≤ input.length) :
    slot.words_eq input a b cap ⦃ fun l =>
      l.val ≤ cap.val ∧ Matches input a.val b.val l.val ⦄ := by
  rw [slot.words_eq]
  apply Std.WP.spec_bind (words_eq_loop_spec input a b cap 0#usize ha hb (by scalar_tac)
    (LZ77.Matches.zero input a.val b.val))
  rintro l ⟨hle, hm⟩
  apply Std.WP.spec_bind (tail_eq_spec input a b cap l ha hb hle)
  rintro big hbig
  apply Std.WP.spec_bind (short_eq_spec input a b cap ha hb)
  rintro small hsmall
  split
  · have h1 : big.val = 1 := by scalar_tac
    obtain ⟨h8, hcl, hw⟩ := hbig h1
    simp only [Std.WP.spec_ok]
    exact ⟨le_refl _, Matches.tail8 hm h8 hcl hw⟩
  · split
    · have h1 : small.val = 1 := by scalar_tac
      obtain ⟨h4, h8, hw0, hw1⟩ := hsmall h1
      simp only [Std.WP.spec_ok]
      exact ⟨le_refl _, Matches.two4 h4 h8 hw0 hw1⟩
    · simp only [Std.WP.spec_ok]
      exact ⟨hle, hm⟩

theorem match_len_loop_spec (input : Slice Std.U8) (a b cap l0 : Std.Usize)
    (ha : a.val + cap.val ≤ input.length) (hb : b.val + cap.val ≤ input.length)
    (hl0 : l0.val ≤ cap.val) (h0 : Matches input a.val b.val l0.val) :
    slot.match_len_loop input a b cap l0 ⦃ fun l =>
      l.val ≤ cap.val ∧ Matches input a.val b.val l.val ⦄ := by
  prove_match_len_loop

@[local step]
theorem match_len_spec (input : Slice Std.U8) (a b cap : Std.Usize)
    (ha : a.val + cap.val ≤ input.length) (hb : b.val + cap.val ≤ input.length) :
    slot.match_len input a b cap ⦃ fun l =>
      l.val ≤ cap.val ∧ Matches input a.val b.val l.val ⦄ := by
  rw [slot.match_len]
  apply Std.WP.spec_bind (words_eq_spec input a b cap ha hb)
  rintro l0 ⟨hle, hm⟩
  exact match_len_loop_spec input a b cap l0 ha hb hle hm


theorem verified_spec (input : Slice Std.U8) (pos d ch : Std.Usize) :
    slot.verified input pos d ch ⦃ fun b => b = true →
      3 ≤ ch.val ∧ ch.val ≤ 258 ∧ 1 ≤ d.val ∧ d.val ≤ 32768 ∧ d.val ≤ pos.val ∧
      pos.val + ch.val ≤ input.length ∧ Matches input (pos.val - d.val) pos.val ch.val ⦄ := by
  rw [slot.verified]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  step*
  all_goals intro hv
  all_goals try simp at hv
  all_goals refine ⟨by scalar_tac, by scalar_tac, by scalar_tac, by scalar_tac,
    by scalar_tac, by scalar_tac, ?_⟩
  all_goals rw [← a_post1]
  all_goals first
    | exact Matches.mono i1_post2 hv
    | (refine Matches.two8 (by scalar_tac) (by scalar_tac) ?_ ?_
       · rw [← i1_post, ← i2_post, ‹i1 = i2›]
       · rw [show a.val + (ch.val - 8) = i4.val by scalar_tac,
           show pos.val + (ch.val - 8) = i7.val by scalar_tac,
           ← i5_post, ← i8_post, hv])
    | (refine Matches.two4 (by scalar_tac) (by scalar_tac) ?_ ?_
       · rw [← i1_post, ← i2_post, ‹i1 = i2›]
       · rw [show a.val + (ch.val - 4) = i4.val by scalar_tac,
           show pos.val + (ch.val - 4) = i7.val by scalar_tac,
           ← i5_post, ← i8_post, hv])
    | (intro k hk
       rcases (by scalar_tac : k = 0 ∨ k = 1 ∨ k = 2) with rfl | rfl | rfl
       · simp only [Nat.add_zero]
         rw [getElem!_pos input.val pos.val (by scalar_tac),
           getElem!_pos input.val a.val (by scalar_tac), ← i1_post, ← i2_post, ‹i1 = i2›]
       · rw [show pos.val + 1 = i5.val by scalar_tac,
           show a.val + 1 = i3.val by scalar_tac,
           getElem!_pos input.val i5.val (by scalar_tac),
           getElem!_pos input.val i3.val (by scalar_tac), ← i4_post, ← i6_post, ‹i4 = i6›]
       · rw [show pos.val + 2 = i9.val by scalar_tac,
           show a.val + 2 = i7.val by scalar_tac,
           getElem!_pos input.val i9.val (by scalar_tac),
           getElem!_pos input.val i7.val (by scalar_tac), ← i8_post, ← i10_post, hv])

theorem emit_lits_loop_spec (input : Slice Std.U8) (out0 : Slice Std.U32)
    (n cnt1 k0 c0 ntok0 : Std.Usize)
    (hn : n.val = input.length) (hout : input.length ≤ out0.length)
    (hk : k0.val ≤ n.val) (hntok : ntok0.val ≤ k0.val) (hc0 : c0.val = 0)
    (hdec : LZ77.decode (toks out0 ntok0.val) = some ((bytes input).take k0.val)) :
    slot.emit_lits_loop input out0 n cnt1 k0 c0 ntok0 ⦃ fun r =>
      r.2.1.val ≤ n.val ∧ (k0.val < r.2.1.val ∨ cnt1.val = 0 ∨ k0.val = n.val) ∧
      r.2.2.val ≤ r.2.1.val ∧ r.1.length = out0.length ∧
      LZ77.decode (toks r.1 r.2.2.val) = some ((bytes input).take r.2.1.val) ⦄ := by
  rw [slot.emit_lits_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => n.val - s.2.1.val)
    (inv := fun s =>
      s.2.1.val ≤ n.val ∧ s.2.1.val = k0.val + s.2.2.1.val ∧ s.2.2.2.val ≤ s.2.1.val ∧
      s.1.length = out0.length ∧
      LZ77.decode (toks s.1 s.2.2.2.val) = some ((bytes input).take s.2.1.val))
  · rintro ⟨out, k, c, ntok⟩ ⟨hkn, hkc, hnt, hlen, hde⟩
    simp only at hkn hkc hnt hlen hde
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.emit_lits_loop.body]
    split
    case isTrue hklt =>
      split
      case isTrue hc =>
        have hntok_lt : ntok.val < out.length := by scalar_tac
        have hposlen : k.val < input.length := by scalar_tac
        step*
        have hval : i1.val = (bytes input)[k.val]! := by
          rw [bytes_getElem! input k.val hposlen, i1_post, Std.U8.cast_U32_val_eq, i_post]
        refine ⟨by scalar_tac, by scalar_tac, by scalar_tac,
          by rw [s_post]; simpa [Std.Slice.set_val_eq] using hlen, ?_, by scalar_tac⟩
        rw [s_post, show ntok1.val = ntok.val + 1 by scalar_tac,
          show k1.val = k.val + 1 by scalar_tac]
        exact emit_lit input out ntok k.val i1 hde hposlen hntok_lt hval
      case isFalse hc =>
        exact ⟨hkn, by scalar_tac, hnt, hlen, hde⟩
    case isFalse hge =>
      exact ⟨hkn, by scalar_tac, hnt, hlen, hde⟩
  · exact ⟨hk, by scalar_tac, hntok, rfl, hdec⟩

@[local step]
theorem emit_lits_spec (input : Slice Std.U8) (out : Slice Std.U32) (pos0 cnt ntok0 : Std.Usize)
    (hout : input.length ≤ out.length) (hpos : pos0.val ≤ input.length)
    (hntok : ntok0.val ≤ pos0.val)
    (hdec : LZ77.decode (toks out ntok0.val) = some ((bytes input).take pos0.val)) :
    slot.emit_lits input out pos0 cnt ntok0 ⦃ fun r =>
      (pos0.val < r.1.2.val ∨ pos0.val = input.length) ∧ r.1.2.val ≤ input.length ∧ r.1.1.val ≤ r.1.2.val ∧
      r.2.length = out.length ∧
      LZ77.decode (toks r.2 r.1.1.val) = some ((bytes input).take r.1.2.val) ⦄ := by
  rw [slot.emit_lits]
  apply Std.WP.spec_bind (Pₘ := fun (c : Std.Usize) => 1 ≤ c.val)
  · split <;> simp only [Std.WP.spec_ok] <;> scalar_tac
  intro cnt1 hc1
  apply Std.WP.spec_bind (emit_lits_loop_spec input out _ cnt1 pos0 0#usize ntok0
    (by simp) hout (by scalar_tac) hntok (by simp) hdec)
  rintro ⟨out1, k, ntok⟩ ⟨h1, h2, h3, h4, h5⟩
  simp only at h1 h2 h3 h4 h5
  step*
  all_goals exact ⟨by scalar_tac, by scalar_tac, h3, h4, h5⟩

@[local step]
theorem emit_step_spec (input : Slice Std.U8) (out : Slice Std.U32) (pos d l lits ntok : Std.Usize)
    (hout : input.length ≤ out.length) (hpos : pos.val < input.length)
    (hntok : ntok.val ≤ pos.val)
    (hdec : LZ77.decode (toks out ntok.val) = some ((bytes input).take pos.val)) :
    slot.emit_step input out pos d l lits ntok ⦃ fun r =>
      pos.val < r.1.2.val ∧ r.1.2.val ≤ input.length ∧ r.1.1.val ≤ r.1.2.val ∧
      r.2.length = out.length ∧
      LZ77.decode (toks r.2 r.1.1.val) = some ((bytes input).take r.1.2.val) ⦄ := by
  rw [slot.emit_step]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  apply Std.WP.spec_bind (verified_spec input pos d l)
  intro b hb
  split
  case isTrue hbt =>
    obtain ⟨hl3, hl258, hd1, hdmax, hdpos, hend, hmatch⟩ := hb hbt
    have hntok_lt : ntok.val < out.length := by scalar_tac
    step*
    have htok : i6.val = LZ77.mkMatch d.val l.val := by
      simp only [LZ77.mkMatch, LZ77.MATCH_BASE, i6_post, i3_post, i2_post]
      scalar_tac
    refine ⟨by scalar_tac, by scalar_tac, by scalar_tac,
      by rw [out1_post]; simp [Std.Slice.set_val_eq], ?_⟩
    rw [out1_post, show i7.val = ntok.val + 1 by scalar_tac,
      show i8.val = pos.val + l.val by scalar_tac]
    exact emit_match input out ntok pos.val d.val l.val i6 hdec hntok_lt hd1 hdpos hdmax
      hl3 hl258 hend hmatch htok
  case isFalse hbf =>
    apply Std.WP.spec_mono (emit_lits_spec input out pos lits ntok hout (by scalar_tac) hntok hdec)
    rintro ⟨⟨t, k⟩, o⟩ ⟨h1, h2, h3, h4, h5⟩
    exact ⟨by scalar_tac, h2, h3, h4, h5⟩



/- Kit copy `g3_*`: cand9's base-kit proofs renamed (extraction identical to the base kit). -/
namespace G3Kit
@[scoped step]
theorem _root_.Submission.g3_tw8_spec (input : Slice Std.U8) (p : Std.Usize) (h : p.val + 8 ≤ input.length) :
    slot.g3_tw8 input p ⦃ fun r => r.val = w8 input p.val ⦄ := by
  exact tw8_spec input p h
@[scoped step]
theorem _root_.Submission.g3_tw4_spec (input : Slice Std.U8) (p : Std.Usize) (h : p.val + 4 ≤ input.length) :
    slot.g3_tw4 input p ⦃ fun r => r.val = w4 input p.val ⦄ := by
  exact E2_tw4_spec input p h
end G3Kit
open scoped Submission.G3Kit
theorem g3_words_eq_loop_spec (input : Slice Std.U8) (a b cap l0 : Std.Usize)
    (ha : a.val + cap.val ≤ input.length) (hb : b.val + cap.val ≤ input.length)
    (hl0 : l0.val ≤ cap.val) (h0 : Matches input a.val b.val l0.val) :
    slot.g3_words_eq_loop input a b cap l0 ⦃ fun l =>
      l.val ≤ cap.val ∧ Matches input a.val b.val l.val ⦄ := by
  rw [slot.g3_words_eq_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun l => cap.val - l.val)
    (inv := fun l => l.val ≤ cap.val ∧ Matches input a.val b.val l.val)
  · rintro l ⟨hle, hinv⟩
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.g3_words_eq_loop.body]
    step*
    all_goals first
      | exact ⟨hle, hinv⟩
      | (refine ⟨by scalar_tac, ?_, by scalar_tac⟩
         rw [show l1.val = l.val + 8 by scalar_tac]
         apply Matches.add8 hinv
         rw [show a.val + l.val = i1.val by scalar_tac, show b.val + l.val = i3.val by scalar_tac,
           ← i2_post, ← i4_post, ‹i2 = i4›])
  · exact ⟨hl0, h0⟩

@[local step]
theorem g3_tail_eq_spec (input : Slice Std.U8) (a b cap l : Std.Usize)
    (ha : a.val + cap.val ≤ input.length) (hb : b.val + cap.val ≤ input.length) (hl : l.val ≤ cap.val) :
    slot.g3_tail_eq input a b cap l ⦃ fun r => r.val = 1 →
      8 ≤ cap.val ∧ cap.val ≤ l.val + 8 ∧
      w8 input (a.val + (cap.val - 8)) = w8 input (b.val + (cap.val - 8)) ⦄ := by
  rw [slot.g3_tail_eq]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  step*
  all_goals first
    | (intro h; simp at h)
    | (intro _
       refine ⟨by scalar_tac, by scalar_tac, ?_⟩
       rw [show a.val + (cap.val - 8) = i2.val by scalar_tac,
         show b.val + (cap.val - 8) = i4.val by scalar_tac, ← i3_post, ← i5_post, ‹i3 = i5›])
    | (refine ⟨by scalar_tac, by scalar_tac, ?_⟩
       rw [show a.val + (cap.val - 8) = i2.val by scalar_tac,
         show b.val + (cap.val - 8) = i4.val by scalar_tac, ← i3_post, ← i5_post, ‹i3 = i5›])

@[local step]
theorem g3_short_eq_spec (input : Slice Std.U8) (a b cap : Std.Usize)
    (ha : a.val + cap.val ≤ input.length) (hb : b.val + cap.val ≤ input.length) :
    slot.g3_short_eq input a b cap ⦃ fun r => r.val = 1 →
      4 ≤ cap.val ∧ cap.val < 8 ∧ w4 input a.val = w4 input b.val ∧
      w4 input (a.val + (cap.val - 4)) = w4 input (b.val + (cap.val - 4)) ⦄ := by
  rw [slot.g3_short_eq]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  step*
  all_goals first
    | (intro h; simp at h)
    | (intro _
       refine ⟨by scalar_tac, by scalar_tac, ?_, ?_⟩
       · rw [← i_post, ← i1_post]
         simp_all
       · rw [show a.val + (cap.val - 4) = i3.val by scalar_tac,
           show b.val + (cap.val - 4) = i5.val by scalar_tac, ← i4_post, ← i6_post, ‹i4 = i6›])
    | (refine ⟨by scalar_tac, by scalar_tac, ?_, ?_⟩
       · rw [← i_post, ← i1_post]
         simp_all
       · rw [show a.val + (cap.val - 4) = i3.val by scalar_tac,
           show b.val + (cap.val - 4) = i5.val by scalar_tac, ← i4_post, ← i6_post, ‹i4 = i6›])

@[local step]
theorem g3_words_eq_spec (input : Slice Std.U8) (a b cap : Std.Usize)
    (ha : a.val + cap.val ≤ input.length) (hb : b.val + cap.val ≤ input.length) :
    slot.g3_words_eq input a b cap ⦃ fun l =>
      l.val ≤ cap.val ∧ Matches input a.val b.val l.val ⦄ := by
  rw [slot.g3_words_eq]
  apply Std.WP.spec_bind (g3_words_eq_loop_spec input a b cap 0#usize ha hb (by scalar_tac)
    (LZ77.Matches.zero input a.val b.val))
  rintro l ⟨hle, hm⟩
  apply Std.WP.spec_bind (g3_tail_eq_spec input a b cap l ha hb hle)
  rintro big hbig
  apply Std.WP.spec_bind (g3_short_eq_spec input a b cap ha hb)
  rintro small hsmall
  split
  · have h1 : big.val = 1 := by scalar_tac
    obtain ⟨h8, hcl, hw⟩ := hbig h1
    simp only [Std.WP.spec_ok]
    exact ⟨le_refl _, Matches.tail8 hm h8 hcl hw⟩
  · split
    · have h1 : small.val = 1 := by scalar_tac
      obtain ⟨h4, h8, hw0, hw1⟩ := hsmall h1
      simp only [Std.WP.spec_ok]
      exact ⟨le_refl _, Matches.two4 h4 h8 hw0 hw1⟩
    · simp only [Std.WP.spec_ok]
      exact ⟨hle, hm⟩

theorem g3_match_len_loop_spec (input : Slice Std.U8) (a b cap l0 : Std.Usize)
    (ha : a.val + cap.val ≤ input.length) (hb : b.val + cap.val ≤ input.length)
    (hl0 : l0.val ≤ cap.val) (h0 : Matches input a.val b.val l0.val) :
    slot.g3_match_len_loop input a b cap l0 ⦃ fun l =>
      l.val ≤ cap.val ∧ Matches input a.val b.val l.val ⦄ := by
  rw [slot.g3_match_len_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun l => cap.val - l.val)
    (inv := fun l => l.val ≤ cap.val ∧ LZ77.Matches input a.val b.val l.val)
  · rintro l ⟨hle, hinv⟩
    simp only [slot.g3_match_len_loop.body]
    split
    case isTrue hlt =>
      have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
      step*
      all_goals first
        | (first | omega | scalar_tac)
        | exact ⟨hle, hinv⟩
        | (refine ⟨by (first | omega | scalar_tac), ?_, by (first | omega | scalar_tac)⟩
           rw [show l1.val = l.val + 1 by (first | omega | scalar_tac)]
           apply LZ77.Matches.succ hinv
           rw [← i_post, ← i2_post, getElem!_pos _ _ (by (first | omega | scalar_tac)),
             getElem!_pos _ _ (by (first | omega | scalar_tac)), ← i1_post, ← i3_post]
           assumption)
    case isFalse => exact ⟨hle, hinv⟩
  · exact ⟨hl0, h0⟩

@[local step]
theorem g3_match_len_spec (input : Slice Std.U8) (a b cap : Std.Usize)
    (ha : a.val + cap.val ≤ input.length) (hb : b.val + cap.val ≤ input.length) :
    slot.g3_match_len input a b cap ⦃ fun l =>
      l.val ≤ cap.val ∧ Matches input a.val b.val l.val ⦄ := by
  rw [slot.g3_match_len]
  apply Std.WP.spec_bind (g3_words_eq_spec input a b cap ha hb)
  rintro l0 ⟨hle, hm⟩
  exact g3_match_len_loop_spec input a b cap l0 ha hb hle hm


theorem g3_verified_spec (input : Slice Std.U8) (pos d ch : Std.Usize) :
    slot.g3_verified input pos d ch ⦃ fun b => b = true →
      3 ≤ ch.val ∧ ch.val ≤ 258 ∧ 1 ≤ d.val ∧ d.val ≤ 32768 ∧ d.val ≤ pos.val ∧
      pos.val + ch.val ≤ input.length ∧ Matches input (pos.val - d.val) pos.val ch.val ⦄ := by
  rw [slot.g3_verified]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  step*
  all_goals intro hv
  all_goals try simp at hv
  all_goals refine ⟨by scalar_tac, by scalar_tac, by scalar_tac, by scalar_tac,
    by scalar_tac, by scalar_tac, ?_⟩
  all_goals rw [← a_post1]
  all_goals first
    | exact Matches.mono i1_post2 hv
    | (refine Matches.two8 (by scalar_tac) (by scalar_tac) ?_ ?_
       · rw [← i1_post, ← i2_post, ‹i1 = i2›]
       · rw [show a.val + (ch.val - 8) = i4.val by scalar_tac,
           show pos.val + (ch.val - 8) = i7.val by scalar_tac,
           ← i5_post, ← i8_post, hv])
    | (refine Matches.two4 (by scalar_tac) (by scalar_tac) ?_ ?_
       · rw [← i1_post, ← i2_post, ‹i1 = i2›]
       · rw [show a.val + (ch.val - 4) = i4.val by scalar_tac,
           show pos.val + (ch.val - 4) = i7.val by scalar_tac,
           ← i5_post, ← i8_post, hv])
    | (intro k hk
       rcases (by scalar_tac : k = 0 ∨ k = 1 ∨ k = 2) with rfl | rfl | rfl
       · simp only [Nat.add_zero]
         rw [getElem!_pos input.val pos.val (by scalar_tac),
           getElem!_pos input.val a.val (by scalar_tac), ← i1_post, ← i2_post, ‹i1 = i2›]
       · rw [show pos.val + 1 = i5.val by scalar_tac,
           show a.val + 1 = i3.val by scalar_tac,
           getElem!_pos input.val i5.val (by scalar_tac),
           getElem!_pos input.val i3.val (by scalar_tac), ← i4_post, ← i6_post, ‹i4 = i6›]
       · rw [show pos.val + 2 = i9.val by scalar_tac,
           show a.val + 2 = i7.val by scalar_tac,
           getElem!_pos input.val i9.val (by scalar_tac),
           getElem!_pos input.val i7.val (by scalar_tac), ← i8_post, ← i10_post, hv])

theorem g3_emit_lits_loop_spec (input : Slice Std.U8) (out0 : Slice Std.U32)
    (n cnt1 k0 c0 ntok0 : Std.Usize)
    (hn : n.val = input.length) (hout : input.length ≤ out0.length)
    (hk : k0.val ≤ n.val) (hntok : ntok0.val ≤ k0.val) (hc0 : c0.val = 0)
    (hdec : LZ77.decode (toks out0 ntok0.val) = some ((bytes input).take k0.val)) :
    slot.g3_emit_lits_loop input out0 n cnt1 k0 c0 ntok0 ⦃ fun r =>
      r.2.1.val ≤ n.val ∧ (k0.val < r.2.1.val ∨ cnt1.val = 0 ∨ k0.val = n.val) ∧
      r.2.2.val ≤ r.2.1.val ∧ r.1.length = out0.length ∧
      LZ77.decode (toks r.1 r.2.2.val) = some ((bytes input).take r.2.1.val) ⦄ := by
  rw [slot.g3_emit_lits_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => n.val - s.2.1.val)
    (inv := fun s =>
      s.2.1.val ≤ n.val ∧ s.2.1.val = k0.val + s.2.2.1.val ∧ s.2.2.2.val ≤ s.2.1.val ∧
      s.1.length = out0.length ∧
      LZ77.decode (toks s.1 s.2.2.2.val) = some ((bytes input).take s.2.1.val))
  · rintro ⟨out, k, c, ntok⟩ ⟨hkn, hkc, hnt, hlen, hde⟩
    simp only at hkn hkc hnt hlen hde
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.g3_emit_lits_loop.body]
    split
    case isTrue hklt =>
      split
      case isTrue hc =>
        have hntok_lt : ntok.val < out.length := by scalar_tac
        have hposlen : k.val < input.length := by scalar_tac
        step*
        have hval : i1.val = (bytes input)[k.val]! := by
          rw [bytes_getElem! input k.val hposlen, i1_post, Std.U8.cast_U32_val_eq, i_post]
        refine ⟨by scalar_tac, by scalar_tac, by scalar_tac,
          by rw [s_post]; simpa [Std.Slice.set_val_eq] using hlen, ?_, by scalar_tac⟩
        rw [s_post, show ntok1.val = ntok.val + 1 by scalar_tac,
          show k1.val = k.val + 1 by scalar_tac]
        exact emit_lit input out ntok k.val i1 hde hposlen hntok_lt hval
      case isFalse hc =>
        exact ⟨hkn, by scalar_tac, hnt, hlen, hde⟩
    case isFalse hge =>
      exact ⟨hkn, by scalar_tac, hnt, hlen, hde⟩
  · exact ⟨hk, by scalar_tac, hntok, rfl, hdec⟩

@[local step]
theorem g3_emit_lits_spec (input : Slice Std.U8) (out : Slice Std.U32) (pos0 cnt ntok0 : Std.Usize)
    (hout : input.length ≤ out.length) (hpos : pos0.val ≤ input.length)
    (hntok : ntok0.val ≤ pos0.val)
    (hdec : LZ77.decode (toks out ntok0.val) = some ((bytes input).take pos0.val)) :
    slot.g3_emit_lits input out pos0 cnt ntok0 ⦃ fun r =>
      (pos0.val < r.1.2.val ∨ pos0.val = input.length) ∧ r.1.2.val ≤ input.length ∧ r.1.1.val ≤ r.1.2.val ∧
      r.2.length = out.length ∧
      LZ77.decode (toks r.2 r.1.1.val) = some ((bytes input).take r.1.2.val) ⦄ := by
  rw [slot.g3_emit_lits]
  apply Std.WP.spec_bind (Pₘ := fun (c : Std.Usize) => 1 ≤ c.val)
  · split <;> simp only [Std.WP.spec_ok] <;> scalar_tac
  intro cnt1 hc1
  apply Std.WP.spec_bind (g3_emit_lits_loop_spec input out _ cnt1 pos0 0#usize ntok0
    (by simp) hout (by scalar_tac) hntok (by simp) hdec)
  rintro ⟨out1, k, ntok⟩ ⟨h1, h2, h3, h4, h5⟩
  simp only at h1 h2 h3 h4 h5
  step*
  all_goals exact ⟨by scalar_tac, by scalar_tac, h3, h4, h5⟩

@[local step]
theorem g3_emit_step_spec (input : Slice Std.U8) (out : Slice Std.U32) (pos d l lits ntok : Std.Usize)
    (hout : input.length ≤ out.length) (hpos : pos.val < input.length)
    (hntok : ntok.val ≤ pos.val)
    (hdec : LZ77.decode (toks out ntok.val) = some ((bytes input).take pos.val)) :
    slot.g3_emit_step input out pos d l lits ntok ⦃ fun r =>
      pos.val < r.1.2.val ∧ r.1.2.val ≤ input.length ∧ r.1.1.val ≤ r.1.2.val ∧
      r.2.length = out.length ∧
      LZ77.decode (toks r.2 r.1.1.val) = some ((bytes input).take r.1.2.val) ⦄ := by
  rw [slot.g3_emit_step]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  apply Std.WP.spec_bind (g3_verified_spec input pos d l)
  intro b hb
  split
  case isTrue hbt =>
    obtain ⟨hl3, hl258, hd1, hdmax, hdpos, hend, hmatch⟩ := hb hbt
    have hntok_lt : ntok.val < out.length := by scalar_tac
    step*
    have htok : i6.val = LZ77.mkMatch d.val l.val := by
      simp only [LZ77.mkMatch, LZ77.MATCH_BASE, i6_post, i3_post, i2_post]
      scalar_tac
    refine ⟨by scalar_tac, by scalar_tac, by scalar_tac,
      by rw [out1_post]; simp [Std.Slice.set_val_eq], ?_⟩
    rw [out1_post, show i7.val = ntok.val + 1 by scalar_tac,
      show i8.val = pos.val + l.val by scalar_tac]
    exact emit_match input out ntok pos.val d.val l.val i6 hdec hntok_lt hd1 hdpos hdmax
      hl3 hl258 hend hmatch htok
  case isFalse hbf =>
    apply Std.WP.spec_mono (g3_emit_lits_spec input out pos lits ntok hout (by scalar_tac) hntok hdec)
    rintro ⟨⟨t, k⟩, o⟩ ⟨h1, h2, h3, h4, h5⟩
    exact ⟨by scalar_tac, h2, h3, h4, h5⟩



namespace P0Scope1
@[scoped step]
theorem _root_.Submission.ld4_spec (input : Slice Std.U8) (p : Std.Usize) :
    slot.ld4 input p ⦃ fun _ => True ⦄ := by
  rw [slot.ld4]
  have hlenv := Slice.len_val input
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat' (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)
end P0Scope1
open scoped Submission.P0Scope1

namespace P0Scope2
@[scoped step]
theorem _root_.Submission.first_diff_spec (x : Std.U64) :
    slot.first_diff x ⦃ fun _ => True ⦄ := by
  rw [slot.first_diff]
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat' (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)
end P0Scope2
open scoped Submission.P0Scope2

namespace P0Scope3
@[scoped step]
theorem _root_.Submission.fast_len_loop_spec (input : Slice Std.U8) (a : Std.Usize) (b : Std.Usize) (cap : Std.Usize) (l : Std.Usize) (go : Std.Usize) (it : Std.Usize) :
    slot.fast_len_loop input a b cap l go it ⦃ fun _ => True ⦄ := by
  rw [slot.fast_len_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => (40 : Nat) - s.2.2.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1, x2⟩ _
    have hlenv := Slice.len_val input
    simp only [slot.fast_len_loop.body, lift, Array.to_slice_mut]
    step*
    repeat' (first
      | (intro hc; (try step*))
      | (split <;> (try step*))
      | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply spec_ite_cut <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals (first | omega | scalar_tac)
  · trivial
end P0Scope3
open scoped Submission.P0Scope3

namespace P0Scope4
@[scoped step]
theorem _root_.Submission.fast_len_spec (input : Slice Std.U8) (a : Std.Usize) (b : Std.Usize) (cap : Std.Usize) :
    slot.fast_len input a b cap ⦃ fun _ => True ⦄ := by
  rw [slot.fast_len]
  have hlenv := Slice.len_val input
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat' (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)
end P0Scope4
open scoped Submission.P0Scope4

namespace P0Scope5
open scoped A2FastPureChoice A2FastCut in
@[scoped step]
theorem _root_.Submission.fl_weights_spec (input : Slice Std.U8) :
    slot.fl_weights input ⦃ fun _ => True ⦄ := by
  rw [slot.fl_weights]
  have hlenv := Slice.len_val input
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat' (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)
end P0Scope5
open scoped Submission.P0Scope5

namespace P0Scope6
open scoped A2FastPureChoice A2FastCut in
@[scoped step]
theorem _root_.Submission.fl_mode_spec (input : Slice Std.U8) (st : Std.U64) :
    slot.fl_mode input st ⦃ fun _ => True ⦄ := by
  rw [slot.fl_mode]
  have hlenv := Slice.len_val input
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat' (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)
end P0Scope6
open scoped Submission.P0Scope6

section
open scoped Submission.A2StepScope33
namespace P0Scope7
@[scoped step]
theorem _root_.Submission.fl_rle_parse_loop_spec (input : Slice Std.U8) (out : Slice Std.U32) (n : Std.Usize) (pos : Std.Usize) (ntok : Std.Usize)
    (hn : n.val = input.length) (hout : input.length ≤ out.length)
    (hp : pos.val ≤ n.val) (hntok : ntok.val ≤ pos.val)
    (hdec : LZ77.decode (toks out ntok.val) = some ((bytes input).take pos.val)) :
    slot.fl_rle_parse_loop input out n pos ntok ⦃ fun r =>
      r.2.1.val = n.val ∧ r.2.2.val ≤ r.2.1.val ∧ r.1.length = out.length ∧
      LZ77.decode (toks r.1 r.2.2.val) = some ((bytes input).take r.2.1.val) ∧
      LZ77.Valid (bytes input) (toks r.1 r.2.2.val) ⦄ := by
  rw [slot.fl_rle_parse_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => n.val - s.2.1.val)
    (inv := fun s =>
      s.2.1.val ≤ n.val ∧ s.2.2.val ≤ s.2.1.val ∧ s.1.length = out.length ∧
      LZ77.decode (toks s.1 s.2.2.val) = some ((bytes input).take s.2.1.val))
  · rintro ⟨out1_, pos1_, ntok1_⟩ ⟨hpn, hnt, hlen, hde⟩
    simp only at hpn hnt hlen hde
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.fl_rle_parse_loop.body, lift, Array.to_slice_mut, alloc.vec.Vec.deref_mut, bind_tc_ok]
    (try step*)
    all_goals (try split)
    all_goals (try step*)
    all_goals (repeat (first
      | (refine ⟨by (first | omega | scalar_tac), by (first | omega | scalar_tac), by assumption, by assumption, by (first | omega | scalar_tac)⟩)
      | (exact ⟨hpn, hnt, hlen, hde⟩)
      | (refine ⟨by (first | omega | scalar_tac), hlen, ?_⟩
         unfold LZ77.Valid
         rw [hde, show pos1_.val = input.length by (first | omega | scalar_tac)]
         simp)
      | (refine ⟨by (first | omega | scalar_tac), by (first | omega | scalar_tac), hlen, hde, ?_⟩
         unfold LZ77.Valid
         rw [hde, show pos1_.val = input.length by (first | omega | scalar_tac)]
         simp)
      | (intro hc; (try step*))
      | (casesm* _ × _; (try simp only [] at *); (try step*))
      | (split <;> (try step*))
      | (step <;> (try step*))))
    all_goals (try (first | omega | scalar_tac))
  · exact ⟨hp, hntok, rfl, hdec⟩
end P0Scope7
open scoped Submission.P0Scope7
end
open scoped Submission.P0Scope7

section
open scoped Submission.A2StepScope33
namespace P0Scope8
@[scoped step]
theorem _root_.Submission.fl_rle_parse_spec (input : Slice Std.U8) (out : Slice Std.U32)
    (hlen : input.length ≤ out.length) :
    slot.fl_rle_parse input out ⦃ fun r =>
      r.1.2.val ≤ input.length ∧ r.1.1.val ≤ r.1.2.val ∧ r.2.length = out.length ∧
      LZ77.decode (toks r.2 r.1.1.val) = some ((bytes input).take r.1.2.val) ⦄ := by
  rw [slot.fl_rle_parse]
  have h0 := decode_nil input out
  have hlenv := Slice.len_val input
  try simp only [lift, Array.to_slice_mut, alloc.vec.Vec.deref_mut, bind_tc_ok]
  step*
  all_goals (repeat (first
    | (refine ⟨by (first | omega | scalar_tac), by (first | omega | scalar_tac), by (first | omega | scalar_tac), by assumption⟩)
    | (refine ⟨by (first | omega | scalar_tac), by (first | omega | scalar_tac), by (first | omega | scalar_tac), decode_of_valid (by assumption)⟩)
    | (intro hc; (try step*))
    | (casesm* _ × _; (try simp only [] at *); (try step*))
    | (split <;> (try step*))
    | (step <;> (try step*))))
  all_goals (try (first | omega | scalar_tac))
end P0Scope8
open scoped Submission.P0Scope8
end
open scoped Submission.P0Scope8

namespace P0Scope9
@[scoped step]
theorem _root_.Submission.fl_g3_hash_spec (input : Slice Std.U8) (p : Std.Usize) :
    slot.fl_g3_hash input p ⦃ fun _ => True ⦄ := by
  rw [slot.fl_g3_hash]
  have hlenv := Slice.len_val input
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat' (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)
end P0Scope9
open scoped Submission.P0Scope9

namespace P0Scope10
@[scoped step]
theorem _root_.Submission.fl_g3_probe_spec (tab : Array Std.U32 65536#usize) (h : Std.Usize) (p : Std.Usize) :
    slot.fl_g3_probe tab h p ⦃ fun _ => True ⦄ := by
  rw [slot.fl_g3_probe]
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat' (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)
end P0Scope10
open scoped Submission.P0Scope10

namespace P0Scope11
@[scoped step]
theorem _root_.Submission.fl_g3_len_spec (input : Slice Std.U8) (p : Std.Usize) (d : Std.Usize) :
    slot.fl_g3_len input p d ⦃ fun _ => True ⦄ := by
  rw [slot.fl_g3_len]
  have hlenv := Slice.len_val input
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat' (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)
end P0Scope11
open scoped Submission.P0Scope11

section
open scoped Submission.A2StepScope33
namespace P0Scope12
@[scoped step]
theorem _root_.Submission.g3_lits_spec (input : Slice Std.U8) (out : Slice Std.U32) (pos : Std.Usize) (s : Std.Usize) (ntok : Std.Usize)
    (hlen : input.length ≤ out.length)
    (hp : pos.val ≤ input.length) (hntok : ntok.val ≤ pos.val)
    (hdec : LZ77.decode (toks out ntok.val) = some ((bytes input).take pos.val)) :
    slot.g3_lits input out pos s ntok ⦃ fun r =>
      r.1.2.val ≤ input.length ∧ r.1.1.val ≤ r.1.2.val ∧ r.2.length = out.length ∧
      LZ77.decode (toks r.2 r.1.1.val) = some ((bytes input).take r.1.2.val) ∧
      (pos.val < input.length → pos.val ≤ r.1.2.val) ⦄ := by
  rw [slot.g3_lits]
  have h0 := decode_nil input out
  have hlenv := Slice.len_val input
  try simp only [lift, Array.to_slice_mut, alloc.vec.Vec.deref_mut, bind_tc_ok]
  step*
  all_goals (repeat (first
    | (refine ⟨by (first | omega | scalar_tac), by (first | omega | scalar_tac), by (first | omega | scalar_tac), by assumption, by (first | omega | scalar_tac)⟩)
    | (refine ⟨by (first | omega | scalar_tac), by (first | omega | scalar_tac), by (first | omega | scalar_tac), decode_of_valid (by assumption), by (first | omega | scalar_tac)⟩)
    | (intro hc; (try step*))
    | (casesm* _ × _; (try simp only [] at *); (try step*))
    | (split <;> (try step*))
    | (step <;> (try step*))))
  all_goals (try (first | omega | scalar_tac))
end P0Scope12
open scoped Submission.P0Scope12
end
open scoped Submission.P0Scope12

section
open scoped Submission.A2StepScope33
namespace P0Scope13
@[scoped step]
theorem _root_.Submission.fl_g3_parse_loop_spec (input : Slice Std.U8) (out : Slice Std.U32) (tab : Array Std.U32 65536#usize) (lim : Std.Usize) (pos : Std.Usize) (ntok : Std.Usize)
    (hout : input.length ≤ out.length)
    (hp : pos.val ≤ input.length) (hntok : ntok.val ≤ pos.val)
    (hdec : LZ77.decode (toks out ntok.val) = some ((bytes input).take pos.val)) (hlim : lim.val ≤ input.length ∧ (lim.val = 0 ∨ lim.val + 8 = input.length)) :
    slot.fl_g3_parse_loop input out tab lim pos ntok ⦃ fun r =>
      r.2.1.val ≤ input.length ∧ r.2.2.val ≤ r.2.1.val ∧ r.1.length = out.length ∧
      LZ77.decode (toks r.1 r.2.2.val) = some ((bytes input).take r.2.1.val) ⦄ := by
  rw [slot.fl_g3_parse_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => lim.val - s.2.2.1.val)
    (inv := fun s =>
      s.2.2.1.val ≤ input.length ∧ s.2.2.2.val ≤ s.2.2.1.val ∧ s.1.length = out.length ∧
      LZ77.decode (toks s.1 s.2.2.2.val) = some ((bytes input).take s.2.2.1.val))
  · rintro ⟨out1_, tab1_, pos1_, ntok1_⟩ ⟨hpn, hnt, hlen, hde⟩
    simp only at hpn hnt hlen hde
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.fl_g3_parse_loop.body, lift, Array.to_slice_mut, alloc.vec.Vec.deref_mut, bind_tc_ok]
    (try step*)
    all_goals (try split)
    all_goals (try step*)
    all_goals (repeat (first
      | (refine ⟨by (first | omega | scalar_tac), by (first | omega | scalar_tac), by assumption, by assumption, by (first | omega | scalar_tac)⟩)
      | (exact ⟨hpn, hnt, hlen, hde⟩)
      | (refine ⟨by (first | omega | scalar_tac), hlen, ?_⟩
         unfold LZ77.Valid
         rw [hde, show pos1_.val = input.length by (first | omega | scalar_tac)]
         simp)
      | (refine ⟨by (first | omega | scalar_tac), by (first | omega | scalar_tac), hlen, hde, ?_⟩
         unfold LZ77.Valid
         rw [hde, show pos1_.val = input.length by (first | omega | scalar_tac)]
         simp)
      | (intro hc; (try step*))
      | (casesm* _ × _; (try simp only [] at *); (try step*))
      | (split <;> (try step*))
      | (step <;> (try step*))))
    all_goals (try (first | omega | scalar_tac))
  · exact ⟨hp, hntok, rfl, hdec⟩
end P0Scope13
open scoped Submission.P0Scope13
end
open scoped Submission.P0Scope13

section
open scoped Submission.A2StepScope33
namespace P0Scope14
@[scoped step]
theorem _root_.Submission.fl_g3_parse_spec (input : Slice Std.U8) (out : Slice Std.U32) (pos0 : Std.Usize) (ntok0 : Std.Usize)
    (hlen : input.length ≤ out.length)
    (hp : pos0.val ≤ input.length) (hntok : ntok0.val ≤ pos0.val)
    (hdec : LZ77.decode (toks out ntok0.val) = some ((bytes input).take pos0.val)) :
    slot.fl_g3_parse input out pos0 ntok0 ⦃ fun r =>
      r.1.2.val ≤ input.length ∧ r.1.1.val ≤ r.1.2.val ∧ r.2.length = out.length ∧
      LZ77.decode (toks r.2 r.1.1.val) = some ((bytes input).take r.1.2.val) ⦄ := by
  rw [slot.fl_g3_parse]
  have h0 := decode_nil input out
  have hlenv := Slice.len_val input
  try simp only [lift, Array.to_slice_mut, alloc.vec.Vec.deref_mut, bind_tc_ok]
  step*
  all_goals (repeat (first
    | (refine ⟨by (first | omega | scalar_tac), by (first | omega | scalar_tac), by (first | omega | scalar_tac), by assumption⟩)
    | (refine ⟨by (first | omega | scalar_tac), by (first | omega | scalar_tac), by (first | omega | scalar_tac), decode_of_valid (by assumption)⟩)
    | (intro hc; (try step*))
    | (casesm* _ × _; (try simp only [] at *); (try step*))
    | (split <;> (try step*))
    | (step <;> (try step*))))
  all_goals (try (first | omega | scalar_tac))
end P0Scope14
open scoped Submission.P0Scope14
end
open scoped Submission.P0Scope14

namespace P0Scope15
@[scoped step]
theorem _root_.Submission.fl_bf_key_spec (input : Slice Std.U8) (p : Std.Usize) :
    slot.fl_bf_key input p ⦃ fun _ => True ⦄ := by
  rw [slot.fl_bf_key]
  have hlenv := Slice.len_val input
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat' (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)
end P0Scope15
open scoped Submission.P0Scope15

namespace P0Scope16
@[scoped step]
theorem _root_.Submission.fl_bf_guess_spec (tab : Array Std.U32 65536#usize) (h : Std.Usize) (p : Std.Usize) :
    slot.fl_bf_guess tab h p ⦃ fun _ => True ⦄ := by
  rw [slot.fl_bf_guess]
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat' (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)
end P0Scope16
open scoped Submission.P0Scope16

section
open scoped Submission.A2StepScope33
namespace P0Scope17
@[scoped step]
theorem _root_.Submission.fl_bf_parse_loop_spec (input : Slice Std.U8) (out : Slice Std.U32) (n : Std.Usize) (tab : Array Std.U32 65536#usize) (lim : Std.Usize) (pos : Std.Usize) (ntok : Std.Usize)
    (hn : n.val = input.length) (hout : input.length ≤ out.length)
    (hp : pos.val ≤ n.val) (hntok : ntok.val ≤ pos.val)
    (hdec : LZ77.decode (toks out ntok.val) = some ((bytes input).take pos.val)) (hlim : lim.val ≤ input.length ∧ (lim.val = 0 ∨ lim.val + 8 = input.length)) :
    slot.fl_bf_parse_loop input out n tab lim pos ntok ⦃ fun r =>
      r.2.1.val ≤ n.val ∧ r.2.2.val ≤ r.2.1.val ∧ r.1.length = out.length ∧
      LZ77.decode (toks r.1 r.2.2.val) = some ((bytes input).take r.2.1.val) ⦄ := by
  rw [slot.fl_bf_parse_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => lim.val - s.2.2.1.val)
    (inv := fun s =>
      s.2.2.1.val ≤ n.val ∧ s.2.2.2.val ≤ s.2.2.1.val ∧ s.1.length = out.length ∧
      LZ77.decode (toks s.1 s.2.2.2.val) = some ((bytes input).take s.2.2.1.val))
  · rintro ⟨out1_, tab1_, pos1_, ntok1_⟩ ⟨hpn, hnt, hlen, hde⟩
    simp only at hpn hnt hlen hde
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.fl_bf_parse_loop.body, lift, Array.to_slice_mut, alloc.vec.Vec.deref_mut, bind_tc_ok]
    (try step*)
    all_goals (try split)
    all_goals (try step*)
    all_goals (repeat (first
      | (refine ⟨by (first | omega | scalar_tac), by (first | omega | scalar_tac), by assumption, by assumption, by (first | omega | scalar_tac)⟩)
      | (exact ⟨hpn, hnt, hlen, hde⟩)
      | (refine ⟨by (first | omega | scalar_tac), hlen, ?_⟩
         unfold LZ77.Valid
         rw [hde, show pos1_.val = input.length by (first | omega | scalar_tac)]
         simp)
      | (refine ⟨by (first | omega | scalar_tac), by (first | omega | scalar_tac), hlen, hde, ?_⟩
         unfold LZ77.Valid
         rw [hde, show pos1_.val = input.length by (first | omega | scalar_tac)]
         simp)
      | (intro hc; (try step*))
      | (casesm* _ × _; (try simp only [] at *); (try step*))
      | (split <;> (try step*))
      | (step <;> (try step*))))
    all_goals (try (first | omega | scalar_tac))
  · exact ⟨hp, hntok, rfl, hdec⟩
end P0Scope17
open scoped Submission.P0Scope17
end
open scoped Submission.P0Scope17

section
open scoped Submission.A2StepScope33
namespace P0Scope18
@[scoped step]
theorem _root_.Submission.fl_bf_parse_spec (input : Slice Std.U8) (out : Slice Std.U32) (pos0 : Std.Usize) (ntok0 : Std.Usize)
    (hlen : input.length ≤ out.length)
    (hp : pos0.val ≤ input.length) (hntok : ntok0.val ≤ pos0.val)
    (hdec : LZ77.decode (toks out ntok0.val) = some ((bytes input).take pos0.val)) :
    slot.fl_bf_parse input out pos0 ntok0 ⦃ fun r =>
      r.1.2.val ≤ input.length ∧ r.1.1.val ≤ r.1.2.val ∧ r.2.length = out.length ∧
      LZ77.decode (toks r.2 r.1.1.val) = some ((bytes input).take r.1.2.val) ⦄ := by
  rw [slot.fl_bf_parse]
  have h0 := decode_nil input out
  have hlenv := Slice.len_val input
  try simp only [lift, Array.to_slice_mut, alloc.vec.Vec.deref_mut, bind_tc_ok]
  step*
  all_goals (repeat (first
    | (refine ⟨by (first | omega | scalar_tac), by (first | omega | scalar_tac), by (first | omega | scalar_tac), by assumption⟩)
    | (refine ⟨by (first | omega | scalar_tac), by (first | omega | scalar_tac), by (first | omega | scalar_tac), decode_of_valid (by assumption)⟩)
    | (intro hc; (try step*))
    | (casesm* _ × _; (try simp only [] at *); (try step*))
    | (split <;> (try step*))
    | (step <;> (try step*))))
  all_goals (try (first | omega | scalar_tac))
end P0Scope18
open scoped Submission.P0Scope18
end
open scoped Submission.P0Scope18

namespace P0Scope19
@[scoped step]
theorem _root_.Submission.fl_im_hash_spec (input : Slice Std.U8) (p : Std.Usize) :
    slot.fl_im_hash input p ⦃ fun _ => True ⦄ := by
  rw [slot.fl_im_hash]
  have hlenv := Slice.len_val input
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat' (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)
end P0Scope19
open scoped Submission.P0Scope19

namespace P0Scope20
@[scoped step]
theorem _root_.Submission.fl_im_step_spec (tab : Array Std.U32 8192#usize) (h : Std.U32) (p : Std.Usize) :
    slot.fl_im_step tab h p ⦃ fun _ => True ⦄ := by
  rw [slot.fl_im_step]
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat' (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)
end P0Scope20
open scoped Submission.P0Scope20

namespace P0Scope21
@[scoped step]
theorem _root_.Submission.fl_im_dist_spec (c : Std.U32) (h : Std.U32) (p : Std.Usize) :
    slot.fl_im_dist c h p ⦃ fun _ => True ⦄ := by
  rw [slot.fl_im_dist]
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat' (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)
end P0Scope21
open scoped Submission.P0Scope21

namespace P0Scope22
@[scoped step]
theorem _root_.Submission.fl_im_back_loop_spec (input : Slice Std.U8) (p : Std.Usize) (d : Std.Usize) (back : Std.Usize) (b : Std.Usize) (hp : p.val ≤ input.length) :
    slot.fl_im_back_loop input p d back b ⦃ fun _ => True ⦄ := by
  rw [slot.fl_im_back_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => back.val - s.val)
    (inv := fun s => True)
  · rintro ⟨x0⟩ _
    have hlenv := Slice.len_val input
    simp only [slot.fl_im_back_loop.body, lift, Array.to_slice_mut]
    step*
    repeat' (first
      | (intro hc; (try step*))
      | (split <;> (try step*))
      | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply spec_ite_cut <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals (first | omega | scalar_tac)
  · trivial
end P0Scope22
open scoped Submission.P0Scope22

namespace P0Scope23
@[scoped step]
theorem _root_.Submission.fl_im_back_spec (input : Slice Std.U8) (p : Std.Usize) (d : Std.Usize) (back : Std.Usize) (hp : p.val ≤ input.length) :
    slot.fl_im_back input p d back ⦃ fun _ => True ⦄ := by
  rw [slot.fl_im_back]
  have hlenv := Slice.len_val input
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat' (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)
end P0Scope23
open scoped Submission.P0Scope23

namespace P0Scope24
@[scoped step]
theorem _root_.Submission.fl_im_next_spec (p : Std.Usize) (base : Std.Usize) :
    slot.fl_im_next p base ⦃ fun _ => True ⦄ := by
  rw [slot.fl_im_next]
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat' (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)
end P0Scope24
open scoped Submission.P0Scope24

section
-- (bind-position ifs are split in this loop: the measure counter is updated by them)
namespace P0Scope25
@[scoped step]
theorem _root_.Submission.fl_im_parse_loop_spec (input : Slice Std.U8) (out : Slice Std.U32) (n : Std.Usize) (tab : Array Std.U32 8192#usize) (lim : Std.Usize) (pos : Std.Usize) (ntok : Std.Usize) (p : Std.Usize) (probes : Std.Usize) (found : Std.Usize) (sleep : Std.Usize)
    (hn : n.val = input.length) (hout : input.length ≤ out.length)
    (hp : pos.val ≤ n.val) (hntok : ntok.val ≤ pos.val)
    (hdec : LZ77.decode (toks out ntok.val) = some ((bytes input).take pos.val)) (hlim : lim.val ≤ n.val ∧ (lim.val = 0 ∨ lim.val + 8 = n.val)) :
    slot.fl_im_parse_loop input out n tab lim pos ntok p probes found sleep ⦃ fun r =>
      r.2.1.val ≤ n.val ∧ r.2.2.val ≤ r.2.1.val ∧ r.1.length = out.length ∧
      LZ77.decode (toks r.1 r.2.2.val) = some ((bytes input).take r.2.1.val) ⦄ := by
  rw [slot.fl_im_parse_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => lim.val - s.2.2.2.2.1.val)
    (inv := fun s =>
      s.2.2.1.val ≤ n.val ∧ s.2.2.2.1.val ≤ s.2.2.1.val ∧ s.1.length = out.length ∧
      LZ77.decode (toks s.1 s.2.2.2.1.val) = some ((bytes input).take s.2.2.1.val))
  · rintro ⟨out1_, tab1_, pos1_, ntok1_, p1_, probes1_, found1_, sleep1_⟩ ⟨hpn, hnt, hlen, hde⟩
    simp only at hpn hnt hlen hde
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.fl_im_parse_loop.body, lift, Array.to_slice_mut, alloc.vec.Vec.deref_mut, bind_tc_ok]
    (try step*)
    all_goals (try split)
    all_goals (try step*)
    all_goals (repeat' (first
      | (refine ⟨by (first | omega | scalar_tac), by (first | omega | scalar_tac), by assumption, by assumption, by (first | omega | scalar_tac)⟩)
      | (exact ⟨hpn, hnt, hlen, hde⟩)
      | (refine ⟨by (first | omega | scalar_tac), hlen, ?_⟩
         unfold LZ77.Valid
         rw [hde, show pos1_.val = input.length by (first | omega | scalar_tac)]
         simp)
      | (refine ⟨by (first | omega | scalar_tac), by (first | omega | scalar_tac), hlen, hde, ?_⟩
         unfold LZ77.Valid
         rw [hde, show pos1_.val = input.length by (first | omega | scalar_tac)]
         simp)
      | (intro hc; (try step*))
      | (casesm* _ × _; (try simp only [] at *); (try step*))
      | (split <;> (try step*))
      | (step <;> (try step*))))
    all_goals (try (first | omega | scalar_tac))
  · exact ⟨hp, hntok, rfl, hdec⟩
end P0Scope25
open scoped Submission.P0Scope25
end
open scoped Submission.P0Scope25

section
open scoped Submission.A2StepScope33
namespace P0Scope26
@[scoped step]
theorem _root_.Submission.fl_im_parse_spec (input : Slice Std.U8) (out : Slice Std.U32) (pos0 : Std.Usize) (ntok0 : Std.Usize)
    (hlen : input.length ≤ out.length)
    (hp : pos0.val ≤ input.length) (hntok : ntok0.val ≤ pos0.val)
    (hdec : LZ77.decode (toks out ntok0.val) = some ((bytes input).take pos0.val)) :
    slot.fl_im_parse input out pos0 ntok0 ⦃ fun r =>
      r.1.2.val ≤ input.length ∧ r.1.1.val ≤ r.1.2.val ∧ r.2.length = out.length ∧
      LZ77.decode (toks r.2 r.1.1.val) = some ((bytes input).take r.1.2.val) ⦄ := by
  rw [slot.fl_im_parse]
  have h0 := decode_nil input out
  have hlenv := Slice.len_val input
  try simp only [lift, Array.to_slice_mut, alloc.vec.Vec.deref_mut, bind_tc_ok]
  step*
  all_goals (repeat (first
    | (refine ⟨by (first | omega | scalar_tac), by (first | omega | scalar_tac), by (first | omega | scalar_tac), by assumption⟩)
    | (refine ⟨by (first | omega | scalar_tac), by (first | omega | scalar_tac), by (first | omega | scalar_tac), decode_of_valid (by assumption)⟩)
    | (intro hc; (try step*))
    | (casesm* _ × _; (try simp only [] at *); (try step*))
    | (split <;> (try step*))
    | (step <;> (try step*))))
  all_goals (try (first | omega | scalar_tac))
end P0Scope26
open scoped Submission.P0Scope26
end
open scoped Submission.P0Scope26

namespace P0Scope27
@[scoped step]
theorem _root_.Submission.fl_dna8_hash_spec (input : Slice Std.U8) (p : Std.Usize) :
    slot.fl_dna8_hash input p ⦃ fun _ => True ⦄ := by
  rw [slot.fl_dna8_hash]
  have hlenv := Slice.len_val input
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat' (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)
end P0Scope27
open scoped Submission.P0Scope27

namespace P0Scope28
@[scoped step]
theorem _root_.Submission.fl_dna8_step_spec (tab : Array Std.U32 65536#usize) (h : Std.Usize) (p : Std.Usize) :
    slot.fl_dna8_step tab h p ⦃ fun _ => True ⦄ := by
  rw [slot.fl_dna8_step]
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat' (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)
end P0Scope28
open scoped Submission.P0Scope28

section
-- (bind-position ifs are split in this loop: the measure counter is updated by them)
namespace P0Scope29
@[scoped step]
theorem _root_.Submission.fl_dna8_parse_loop_spec (input : Slice Std.U8) (out : Slice Std.U32) (n : Std.Usize) (tab : Array Std.U32 65536#usize) (lim : Std.Usize) (pos : Std.Usize) (ntok : Std.Usize) (p : Std.Usize)
    (hn : n.val = input.length) (hout : input.length ≤ out.length)
    (hp : pos.val ≤ n.val) (hntok : ntok.val ≤ pos.val)
    (hdec : LZ77.decode (toks out ntok.val) = some ((bytes input).take pos.val)) (hlim : lim.val ≤ n.val ∧ (lim.val = 0 ∨ lim.val + 16 = n.val)) :
    slot.fl_dna8_parse_loop input out n tab lim pos ntok p ⦃ fun r =>
      r.2.1.val ≤ n.val ∧ r.2.2.val ≤ r.2.1.val ∧ r.1.length = out.length ∧
      LZ77.decode (toks r.1 r.2.2.val) = some ((bytes input).take r.2.1.val) ⦄ := by
  rw [slot.fl_dna8_parse_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => lim.val - s.2.2.2.2.val)
    (inv := fun s =>
      s.2.2.1.val ≤ n.val ∧ s.2.2.2.1.val ≤ s.2.2.1.val ∧ s.1.length = out.length ∧
      LZ77.decode (toks s.1 s.2.2.2.1.val) = some ((bytes input).take s.2.2.1.val))
  · rintro ⟨out1_, tab1_, pos1_, ntok1_, p1_⟩ ⟨hpn, hnt, hlen, hde⟩
    simp only at hpn hnt hlen hde
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.fl_dna8_parse_loop.body, lift, Array.to_slice_mut, alloc.vec.Vec.deref_mut, bind_tc_ok]
    (try step*)
    all_goals (try split)
    all_goals (try step*)
    all_goals (repeat' (first
      | (refine ⟨by (first | omega | scalar_tac), by (first | omega | scalar_tac), by assumption, by assumption, by (first | omega | scalar_tac)⟩)
      | (exact ⟨hpn, hnt, hlen, hde⟩)
      | (refine ⟨by (first | omega | scalar_tac), hlen, ?_⟩
         unfold LZ77.Valid
         rw [hde, show pos1_.val = input.length by (first | omega | scalar_tac)]
         simp)
      | (refine ⟨by (first | omega | scalar_tac), by (first | omega | scalar_tac), hlen, hde, ?_⟩
         unfold LZ77.Valid
         rw [hde, show pos1_.val = input.length by (first | omega | scalar_tac)]
         simp)
      | (intro hc; (try step*))
      | (casesm* _ × _; (try simp only [] at *); (try step*))
      | (split <;> (try step*))
      | (step <;> (try step*))))
    all_goals (try (first | omega | scalar_tac))
  · exact ⟨hp, hntok, rfl, hdec⟩
end P0Scope29
open scoped Submission.P0Scope29
end
open scoped Submission.P0Scope29

section
open scoped Submission.A2StepScope33
namespace P0Scope30
@[scoped step]
theorem _root_.Submission.fl_dna8_parse_spec (input : Slice Std.U8) (out : Slice Std.U32) (pos0 : Std.Usize) (ntok0 : Std.Usize)
    (hlen : input.length ≤ out.length)
    (hp : pos0.val ≤ input.length) (hntok : ntok0.val ≤ pos0.val)
    (hdec : LZ77.decode (toks out ntok0.val) = some ((bytes input).take pos0.val)) :
    slot.fl_dna8_parse input out pos0 ntok0 ⦃ fun r =>
      r.1.2.val ≤ input.length ∧ r.1.1.val ≤ r.1.2.val ∧ r.2.length = out.length ∧
      LZ77.decode (toks r.2 r.1.1.val) = some ((bytes input).take r.1.2.val) ⦄ := by
  rw [slot.fl_dna8_parse]
  have h0 := decode_nil input out
  have hlenv := Slice.len_val input
  try simp only [lift, Array.to_slice_mut, alloc.vec.Vec.deref_mut, bind_tc_ok]
  step*
  all_goals (repeat (first
    | (refine ⟨by (first | omega | scalar_tac), by (first | omega | scalar_tac), by (first | omega | scalar_tac), by assumption⟩)
    | (refine ⟨by (first | omega | scalar_tac), by (first | omega | scalar_tac), by (first | omega | scalar_tac), decode_of_valid (by assumption)⟩)
    | (intro hc; (try step*))
    | (casesm* _ × _; (try simp only [] at *); (try step*))
    | (split <;> (try step*))
    | (step <;> (try step*))))
  all_goals (try (first | omega | scalar_tac))
end P0Scope30
open scoped Submission.P0Scope30
end
open scoped Submission.P0Scope30

namespace P0Scope31
@[scoped step]
theorem _root_.Submission.fl_sm_lc_spec (l : Std.Usize) :
    slot.fl_sm_lc l ⦃ fun _ => True ⦄ := by
  rw [slot.fl_sm_lc]
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat' (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)
end P0Scope31
open scoped Submission.P0Scope31

namespace P0Scope32
@[scoped step]
theorem _root_.Submission.fl_sm_dc_spec (d : Std.Usize) :
    slot.fl_sm_dc d ⦃ fun _ => True ⦄ := by
  rw [slot.fl_sm_dc]
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat' (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)
end P0Scope32
open scoped Submission.P0Scope32

namespace P0Scope33
@[scoped step]
theorem _root_.Submission.fl_sm_hash_spec (input : Slice Std.U8) (p : Std.Usize) :
    slot.fl_sm_hash input p ⦃ fun _ => True ⦄ := by
  rw [slot.fl_sm_hash]
  have hlenv := Slice.len_val input
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat' (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)
end P0Scope33
open scoped Submission.P0Scope33

namespace P0Scope34
@[scoped step]
theorem _root_.Submission.fl_sm_step_spec (tab : Array Std.U16 8192#usize) (h : Std.Usize) (p : Std.Usize) :
    slot.fl_sm_step tab h p ⦃ fun _ => True ⦄ := by
  rw [slot.fl_sm_step]
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat' (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)
end P0Scope34
open scoped Submission.P0Scope34

namespace P0Scope35
@[scoped step]
theorem _root_.Submission.fl_sm_insert_loop_spec (input : Slice Std.U8) (tab : Array Std.U16 8192#usize) («to» : Std.Usize) (lim : Std.Usize) (p : Std.Usize) :
    slot.fl_sm_insert_loop input tab «to» lim p ⦃ fun _ => True ⦄ := by
  rw [slot.fl_sm_insert_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => «to».val - s.2.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1⟩ _
    have hlenv := Slice.len_val input
    simp only [slot.fl_sm_insert_loop.body, lift, Array.to_slice_mut]
    step*
    repeat' (first
      | (intro hc; (try step*))
      | (split <;> (try step*))
      | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply spec_ite_cut <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals (first | omega | scalar_tac)
  · trivial
end P0Scope35
open scoped Submission.P0Scope35

namespace P0Scope36
@[scoped step]
theorem _root_.Submission.fl_sm_insert_spec (input : Slice Std.U8) (tab : Array Std.U16 8192#usize) («from» : Std.Usize) («to» : Std.Usize) :
    slot.fl_sm_insert input tab «from» «to» ⦃ fun _ => True ⦄ := by
  rw [slot.fl_sm_insert]
  have hlenv := Slice.len_val input
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat' (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)
end P0Scope36
open scoped Submission.P0Scope36

namespace P0Scope37
@[scoped step]
theorem _root_.Submission.fl_sm_add_spec (st : Array Std.U32 128#usize) (l : Std.Usize) (d : Std.Usize) :
    slot.fl_sm_add st l d ⦃ fun _ => True ⦄ := by
  rw [slot.fl_sm_add]
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat' (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)
end P0Scope37
open scoped Submission.P0Scope37

namespace P0Scope38
@[scoped step]
theorem _root_.Submission.fl_sm_find_spec (input : Slice Std.U8) (tab : Array Std.U16 8192#usize) (p : Std.Usize) (hp : p.val ≤ input.length) :
    slot.fl_sm_find input tab p ⦃ fun _ => True ⦄ := by
  rw [slot.fl_sm_find]
  have hlenv := Slice.len_val input
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat' (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)
end P0Scope38
open scoped Submission.P0Scope38

namespace P0Scope39
@[scoped step]
theorem _root_.Submission.fl_sm_scan_loop_spec (input : Slice Std.U8) (cache : Array Std.U32 16384#usize) (st : Array Std.U32 128#usize) (tab : Array Std.U16 8192#usize) (n : Std.Usize) (lim : Std.Usize) (pos : Std.Usize) (k : Std.Usize) (run : Std.Usize) (hlim : lim.val ≤ n.val ∧ (lim.val = 0 ∨ lim.val + 8 = n.val)) (hn : n.val = input.length) :
    slot.fl_sm_scan_loop input cache st tab n lim pos k run ⦃ fun _ => True ⦄ := by
  rw [slot.fl_sm_scan_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => lim.val - s.2.2.2.1.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1, x2, x3, x4, x5⟩ _
    have hlenv := Slice.len_val input
    simp only [slot.fl_sm_scan_loop.body, lift, Array.to_slice_mut]
    step*
    repeat' (first
      | (intro hc; (try step*))
      | (split <;> (try step*))
      | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply spec_ite_cut <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals (first | omega | scalar_tac)
  · trivial
end P0Scope39
open scoped Submission.P0Scope39

namespace P0Scope40
@[scoped step]
theorem _root_.Submission.fl_sm_scan_spec (input : Slice Std.U8) (cache : Array Std.U32 16384#usize) (st : Array Std.U32 128#usize) (tab : Array Std.U16 8192#usize) :
    slot.fl_sm_scan input cache st tab ⦃ fun _ => True ⦄ := by
  rw [slot.fl_sm_scan]
  have hlenv := Slice.len_val input
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat' (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)
end P0Scope40
open scoped Submission.P0Scope40

namespace P0Scope41
@[scoped step]
theorem _root_.Submission.fl_sm_rle_scan_loop_spec (input : Slice Std.U8) (cache : Array Std.U32 16384#usize) (st : Array Std.U32 128#usize) (n : Std.Usize) (pos : Std.Usize) (k : Std.Usize) (run : Std.Usize) :
    slot.fl_sm_rle_scan_loop input cache st n pos k run ⦃ fun _ => True ⦄ := by
  rw [slot.fl_sm_rle_scan_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => n.val - s.2.2.1.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1, x2, x3, x4⟩ _
    have hlenv := Slice.len_val input
    simp only [slot.fl_sm_rle_scan_loop.body, lift, Array.to_slice_mut]
    step*
    repeat' (first
      | (intro hc; (try step*))
      | (split <;> (try step*))
      | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply spec_ite_cut <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals (first | omega | scalar_tac)
  · trivial
end P0Scope41
open scoped Submission.P0Scope41

namespace P0Scope42
@[scoped step]
theorem _root_.Submission.fl_sm_rle_scan_spec (input : Slice Std.U8) (cache : Array Std.U32 16384#usize) (st : Array Std.U32 128#usize) :
    slot.fl_sm_rle_scan input cache st ⦃ fun _ => True ⦄ := by
  rw [slot.fl_sm_rle_scan]
  have hlenv := Slice.len_val input
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat' (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)
end P0Scope42
open scoped Submission.P0Scope42

namespace P0Scope43
@[scoped step]
theorem _root_.Submission.fl_sm_rules_loop0_spec (st : Array Std.U32 128#usize) (q : Array Std.U16 320#usize) (thin : Std.Usize) (dt : Std.Usize) (j : Std.Usize) :
    slot.fl_sm_rules_loop0 st q thin dt j ⦃ fun _ => True ⦄ := by
  rw [slot.fl_sm_rules_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun s => (30 : Nat) - s.2.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1⟩ _
    simp only [slot.fl_sm_rules_loop0.body, lift, Array.to_slice_mut]
    step*
    repeat' (first
      | (intro hc; (try step*))
      | (split <;> (try step*))
      | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply spec_ite_cut <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals (first | omega | scalar_tac)
  · trivial
end P0Scope43
open scoped Submission.P0Scope43

namespace P0Scope44
@[scoped step]
theorem _root_.Submission.fl_sm_rules_loop1_loop0_spec (q : Array Std.U16 320#usize) (top : Std.Usize) (l : Std.Usize) (keep : Std.Usize) («end» : Std.Usize) :
    slot.fl_sm_rules_loop1_loop0 q top l keep «end» ⦃ fun _ => True ⦄ := by
  rw [slot.fl_sm_rules_loop1_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun s => («end».val + 1) - s.2.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1⟩ _
    simp only [slot.fl_sm_rules_loop1_loop0.body, lift, Array.to_slice_mut]
    step*
    repeat' (first
      | (intro hc; (try step*))
      | (split <;> (try step*))
      | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply spec_ite_cut <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals (first | omega | scalar_tac)
  · trivial
end P0Scope44
open scoped Submission.P0Scope44

namespace P0Scope45
@[scoped step]
theorem _root_.Submission.fl_sm_rules_loop1_spec (st : Array Std.U32 128#usize) (q : Array Std.U16 320#usize) (thin : Std.Usize) (dt : Std.Usize) (top : Std.Usize) (i : Std.Usize) (l : Std.Usize) :
    slot.fl_sm_rules_loop1 st q thin dt top i l ⦃ fun _ => True ⦄ := by
  rw [slot.fl_sm_rules_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun s => (29 : Nat) - s.2.2.1.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1, x2, x3⟩ _
    simp only [slot.fl_sm_rules_loop1.body, lift, Array.to_slice_mut]
    step*
    repeat' (first
      | (intro hc; (try step*))
      | (split <;> (try step*))
      | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply spec_ite_cut <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals (first | omega | scalar_tac)
  · trivial
end P0Scope45
open scoped Submission.P0Scope45

namespace P0Scope46
@[scoped step]
theorem _root_.Submission.fl_sm_rules_spec (st : Array Std.U32 128#usize) (q : Array Std.U16 320#usize) (thin : Std.Usize) (dt : Std.Usize) :
    slot.fl_sm_rules st q thin dt ⦃ fun _ => True ⦄ := by
  rw [slot.fl_sm_rules]
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat' (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)
end P0Scope46
open scoped Submission.P0Scope46

section
open scoped Submission.A2StepScope33
namespace P0Scope47
@[scoped step]
theorem _root_.Submission.fl_sm_span_loop_spec (input : Slice Std.U8) (out : Slice Std.U32) (d : Std.Usize) (q : Array Std.U16 320#usize) (n : Std.Usize) (rem : Std.Usize) (pos : Std.Usize) (ntok : Std.Usize)
    (hn : n.val = input.length) (hout : input.length ≤ out.length)
    (hp : pos.val ≤ n.val) (hntok : ntok.val ≤ pos.val)
    (hdec : LZ77.decode (toks out ntok.val) = some ((bytes input).take pos.val)) :
    slot.fl_sm_span_loop input out d q n rem pos ntok ⦃ fun r =>
      r.2.1.val ≤ n.val ∧ r.2.2.val ≤ r.2.1.val ∧ r.1.length = out.length ∧
      LZ77.decode (toks r.1 r.2.2.val) = some ((bytes input).take r.2.1.val) ⦄ := by
  rw [slot.fl_sm_span_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => n.val - s.2.2.1.val)
    (inv := fun s =>
      s.2.2.1.val ≤ n.val ∧ s.2.2.2.val ≤ s.2.2.1.val ∧ s.1.length = out.length ∧
      LZ77.decode (toks s.1 s.2.2.2.val) = some ((bytes input).take s.2.2.1.val))
  · rintro ⟨out1_, rem1_, pos1_, ntok1_⟩ ⟨hpn, hnt, hlen, hde⟩
    simp only at hpn hnt hlen hde
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.fl_sm_span_loop.body, lift, Array.to_slice_mut, alloc.vec.Vec.deref_mut, bind_tc_ok]
    (try step*)
    all_goals (try split)
    all_goals (try step*)
    all_goals (repeat (first
      | (refine ⟨by (first | omega | scalar_tac), by (first | omega | scalar_tac), by assumption, by assumption, by (first | omega | scalar_tac)⟩)
      | (exact ⟨hpn, hnt, hlen, hde⟩)
      | (refine ⟨by (first | omega | scalar_tac), hlen, ?_⟩
         unfold LZ77.Valid
         rw [hde, show pos1_.val = input.length by (first | omega | scalar_tac)]
         simp)
      | (refine ⟨by (first | omega | scalar_tac), by (first | omega | scalar_tac), hlen, hde, ?_⟩
         unfold LZ77.Valid
         rw [hde, show pos1_.val = input.length by (first | omega | scalar_tac)]
         simp)
      | (intro hc; (try step*))
      | (casesm* _ × _; (try simp only [] at *); (try step*))
      | (split <;> (try step*))
      | (step <;> (try step*))))
    all_goals (try (first | omega | scalar_tac))
  · exact ⟨hp, hntok, rfl, hdec⟩
end P0Scope47
open scoped Submission.P0Scope47
end
open scoped Submission.P0Scope47

section
open scoped Submission.A2StepScope33
namespace P0Scope48
@[scoped step]
theorem _root_.Submission.fl_sm_span_spec (input : Slice Std.U8) (out : Slice Std.U32) (pos0 : Std.Usize) (l0 : Std.Usize) (d : Std.Usize) (q : Array Std.U16 320#usize) (ntok0 : Std.Usize)
    (hlen : input.length ≤ out.length)
    (hp : pos0.val ≤ input.length) (hntok : ntok0.val ≤ pos0.val)
    (hdec : LZ77.decode (toks out ntok0.val) = some ((bytes input).take pos0.val)) :
    slot.fl_sm_span input out pos0 l0 d q ntok0 ⦃ fun r =>
      r.1.2.val ≤ input.length ∧ r.1.1.val ≤ r.1.2.val ∧ r.2.length = out.length ∧
      LZ77.decode (toks r.2 r.1.1.val) = some ((bytes input).take r.1.2.val) ⦄ := by
  rw [slot.fl_sm_span]
  have h0 := decode_nil input out
  have hlenv := Slice.len_val input
  try simp only [lift, Array.to_slice_mut, alloc.vec.Vec.deref_mut, bind_tc_ok]
  step*
  all_goals (repeat (first
    | (refine ⟨by (first | omega | scalar_tac), by (first | omega | scalar_tac), by (first | omega | scalar_tac), by assumption⟩)
    | (refine ⟨by (first | omega | scalar_tac), by (first | omega | scalar_tac), by (first | omega | scalar_tac), decode_of_valid (by assumption)⟩)
    | (intro hc; (try step*))
    | (casesm* _ × _; (try simp only [] at *); (try step*))
    | (split <;> (try step*))
    | (step <;> (try step*))))
  all_goals (try (first | omega | scalar_tac))
end P0Scope48
open scoped Submission.P0Scope48
end
open scoped Submission.P0Scope48

section
-- (bind-position ifs are split in this loop: the measure counter is updated by them)
namespace P0Scope49
@[scoped step]
theorem _root_.Submission.fl_sm_replay_loop_spec (input : Slice Std.U8) (out : Slice Std.U32) (cache : Array Std.U32 16384#usize) (k : Std.Usize) (q : Array Std.U16 320#usize) (n : Std.Usize) (pos : Std.Usize) (ntok : Std.Usize) (i : Std.Usize)
    (hn : n.val = input.length) (hout : input.length ≤ out.length)
    (hp : pos.val ≤ n.val) (hntok : ntok.val ≤ pos.val)
    (hdec : LZ77.decode (toks out ntok.val) = some ((bytes input).take pos.val)) :
    slot.fl_sm_replay_loop input out cache k q n pos ntok i ⦃ fun r =>
      r.2.1.val ≤ n.val ∧ r.2.2.val ≤ r.2.1.val ∧ r.1.length = out.length ∧
      LZ77.decode (toks r.1 r.2.2.val) = some ((bytes input).take r.2.1.val) ⦄ := by
  rw [slot.fl_sm_replay_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => k.val - s.2.2.2.val)
    (inv := fun s =>
      s.2.1.val ≤ n.val ∧ s.2.2.1.val ≤ s.2.1.val ∧ s.1.length = out.length ∧
      LZ77.decode (toks s.1 s.2.2.1.val) = some ((bytes input).take s.2.1.val))
  · rintro ⟨out1_, pos1_, ntok1_, i1_⟩ ⟨hpn, hnt, hlen, hde⟩
    simp only at hpn hnt hlen hde
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.fl_sm_replay_loop.body, lift, Array.to_slice_mut, alloc.vec.Vec.deref_mut, bind_tc_ok]
    (try step*)
    all_goals (try split)
    all_goals (try step*)
    all_goals (repeat' (first
      | (refine ⟨by (first | omega | scalar_tac), by (first | omega | scalar_tac), by assumption, by assumption, by (first | omega | scalar_tac)⟩)
      | (exact ⟨hpn, hnt, hlen, hde⟩)
      | (refine ⟨by (first | omega | scalar_tac), hlen, ?_⟩
         unfold LZ77.Valid
         rw [hde, show pos1_.val = input.length by (first | omega | scalar_tac)]
         simp)
      | (refine ⟨by (first | omega | scalar_tac), by (first | omega | scalar_tac), hlen, hde, ?_⟩
         unfold LZ77.Valid
         rw [hde, show pos1_.val = input.length by (first | omega | scalar_tac)]
         simp)
      | (intro hc; (try step*))
      | (casesm* _ × _; (try simp only [] at *); (try step*))
      | (split <;> (try step*))
      | (step <;> (try step*))))
    all_goals (try (first | omega | scalar_tac))
  · exact ⟨hp, hntok, rfl, hdec⟩
end P0Scope49
open scoped Submission.P0Scope49
end
open scoped Submission.P0Scope49

section
open scoped Submission.A2StepScope33
namespace P0Scope50
@[scoped step]
theorem _root_.Submission.fl_sm_replay_spec (input : Slice Std.U8) (out : Slice Std.U32) (cache : Array Std.U32 16384#usize) (k : Std.Usize) (q : Array Std.U16 320#usize)
    (hlen : input.length ≤ out.length) :
    slot.fl_sm_replay input out cache k q ⦃ fun r =>
      r.1.2.val ≤ input.length ∧ r.1.1.val ≤ r.1.2.val ∧ r.2.length = out.length ∧
      LZ77.decode (toks r.2 r.1.1.val) = some ((bytes input).take r.1.2.val) ⦄ := by
  rw [slot.fl_sm_replay]
  have h0 := decode_nil input out
  have hlenv := Slice.len_val input
  try simp only [lift, Array.to_slice_mut, alloc.vec.Vec.deref_mut, bind_tc_ok]
  step*
  all_goals (repeat (first
    | (refine ⟨by (first | omega | scalar_tac), by (first | omega | scalar_tac), by (first | omega | scalar_tac), by assumption⟩)
    | (refine ⟨by (first | omega | scalar_tac), by (first | omega | scalar_tac), by (first | omega | scalar_tac), decode_of_valid (by assumption)⟩)
    | (intro hc; (try step*))
    | (casesm* _ × _; (try simp only [] at *); (try step*))
    | (split <;> (try step*))
    | (step <;> (try step*))))
  all_goals (try (first | omega | scalar_tac))
end P0Scope50
open scoped Submission.P0Scope50
end
open scoped Submission.P0Scope50

section
open scoped Submission.A2StepScope33
namespace P0Scope51
@[scoped step]
theorem _root_.Submission.fl_sm_rest_loop_spec (input : Slice Std.U8) (out : Slice Std.U32) (tab : Array Std.U16 8192#usize) (lim : Std.Usize) (pos : Std.Usize) (ntok : Std.Usize)
    (hout : input.length ≤ out.length)
    (hp : pos.val ≤ input.length) (hntok : ntok.val ≤ pos.val)
    (hdec : LZ77.decode (toks out ntok.val) = some ((bytes input).take pos.val)) (hlim : lim.val ≤ input.length ∧ (lim.val = 0 ∨ lim.val + 8 = input.length)) :
    slot.fl_sm_rest_loop input out tab lim pos ntok ⦃ fun r =>
      r.2.2.1.val ≤ input.length ∧ r.2.2.2.val ≤ r.2.2.1.val ∧ r.1.length = out.length ∧
      LZ77.decode (toks r.1 r.2.2.2.val) = some ((bytes input).take r.2.2.1.val) ⦄ := by
  rw [slot.fl_sm_rest_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => lim.val - s.2.2.1.val)
    (inv := fun s =>
      s.2.2.1.val ≤ input.length ∧ s.2.2.2.val ≤ s.2.2.1.val ∧ s.1.length = out.length ∧
      LZ77.decode (toks s.1 s.2.2.2.val) = some ((bytes input).take s.2.2.1.val))
  · rintro ⟨out1_, tab1_, pos1_, ntok1_⟩ ⟨hpn, hnt, hlen, hde⟩
    simp only at hpn hnt hlen hde
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.fl_sm_rest_loop.body, lift, Array.to_slice_mut, alloc.vec.Vec.deref_mut, bind_tc_ok]
    (try step*)
    all_goals (try split)
    all_goals (try step*)
    all_goals (repeat (first
      | (refine ⟨by (first | omega | scalar_tac), by (first | omega | scalar_tac), by assumption, by assumption, by (first | omega | scalar_tac)⟩)
      | (exact ⟨hpn, hnt, hlen, hde⟩)
      | (refine ⟨by (first | omega | scalar_tac), hlen, ?_⟩
         unfold LZ77.Valid
         rw [hde, show pos1_.val = input.length by (first | omega | scalar_tac)]
         simp)
      | (refine ⟨by (first | omega | scalar_tac), by (first | omega | scalar_tac), hlen, hde, ?_⟩
         unfold LZ77.Valid
         rw [hde, show pos1_.val = input.length by (first | omega | scalar_tac)]
         simp)
      | (intro hc; (try step*))
      | (casesm* _ × _; (try simp only [] at *); (try step*))
      | (split <;> (try step*))
      | (step <;> (try step*))))
    all_goals (try (first | omega | scalar_tac))
  · exact ⟨hp, hntok, rfl, hdec⟩
end P0Scope51
open scoped Submission.P0Scope51
end
open scoped Submission.P0Scope51

section
open scoped Submission.A2StepScope33
namespace P0Scope52
@[scoped step]
theorem _root_.Submission.fl_sm_rest_spec (input : Slice Std.U8) (out : Slice Std.U32) (tab : Array Std.U16 8192#usize) (pos0 : Std.Usize) (ntok0 : Std.Usize)
    (hlen : input.length ≤ out.length)
    (hp : pos0.val ≤ input.length) (hntok : ntok0.val ≤ pos0.val)
    (hdec : LZ77.decode (toks out ntok0.val) = some ((bytes input).take pos0.val)) :
    slot.fl_sm_rest input out tab pos0 ntok0 ⦃ fun r =>
      r.1.2.val ≤ input.length ∧ r.1.1.val ≤ r.1.2.val ∧ r.2.1.length = out.length ∧
      LZ77.decode (toks r.2.1 r.1.1.val) = some ((bytes input).take r.1.2.val) ⦄ := by
  rw [slot.fl_sm_rest]
  have h0 := decode_nil input out
  have hlenv := Slice.len_val input
  try simp only [lift, Array.to_slice_mut, alloc.vec.Vec.deref_mut, bind_tc_ok]
  step*
  all_goals (repeat (first
    | (refine ⟨by (first | omega | scalar_tac), by (first | omega | scalar_tac), by (first | omega | scalar_tac), by assumption⟩)
    | (refine ⟨by (first | omega | scalar_tac), by (first | omega | scalar_tac), by (first | omega | scalar_tac), decode_of_valid (by assumption)⟩)
    | (intro hc; (try step*))
    | (casesm* _ × _; (try simp only [] at *); (try step*))
    | (split <;> (try step*))
    | (step <;> (try step*))))
  all_goals (try (first | omega | scalar_tac))
end P0Scope52
open scoped Submission.P0Scope52
end
open scoped Submission.P0Scope52

section
open scoped Submission.A2StepScope33
namespace P0Scope53
@[scoped step]
theorem _root_.Submission.fl_sm_parse_spec (input : Slice Std.U8) (out : Slice Std.U32)
    (hlen : input.length ≤ out.length) :
    slot.fl_sm_parse input out ⦃ fun r =>
      r.1.2.val ≤ input.length ∧ r.1.1.val ≤ r.1.2.val ∧ r.2.length = out.length ∧
      LZ77.decode (toks r.2 r.1.1.val) = some ((bytes input).take r.1.2.val) ⦄ := by
  rw [slot.fl_sm_parse]
  have h0 := decode_nil input out
  have hlenv := Slice.len_val input
  try simp only [lift, Array.to_slice_mut, alloc.vec.Vec.deref_mut, bind_tc_ok]
  step*
  all_goals (repeat (first
    | (refine ⟨by (first | omega | scalar_tac), by (first | omega | scalar_tac), by (first | omega | scalar_tac), by assumption⟩)
    | (refine ⟨by (first | omega | scalar_tac), by (first | omega | scalar_tac), by (first | omega | scalar_tac), decode_of_valid (by assumption)⟩)
    | (intro hc; (try step*))
    | (casesm* _ × _; (try simp only [] at *); (try step*))
    | (split <;> (try step*))
    | (step <;> (try step*))))
  all_goals (try (first | omega | scalar_tac))
end P0Scope53
open scoped Submission.P0Scope53
end
open scoped Submission.P0Scope53

section
open scoped Submission.A2StepScope33
namespace P0Scope54
@[scoped step]
theorem _root_.Submission.fl_sm_rle_spec (input : Slice Std.U8) (out : Slice Std.U32)
    (hlen : input.length ≤ out.length) :
    slot.fl_sm_rle input out ⦃ fun r =>
      r.1.2.val ≤ input.length ∧ r.1.1.val ≤ r.1.2.val ∧ r.2.length = out.length ∧
      LZ77.decode (toks r.2 r.1.1.val) = some ((bytes input).take r.1.2.val) ⦄ := by
  rw [slot.fl_sm_rle]
  have h0 := decode_nil input out
  have hlenv := Slice.len_val input
  try simp only [lift, Array.to_slice_mut, alloc.vec.Vec.deref_mut, bind_tc_ok]
  step*
  all_goals (repeat (first
    | (refine ⟨by (first | omega | scalar_tac), by (first | omega | scalar_tac), by (first | omega | scalar_tac), by assumption⟩)
    | (refine ⟨by (first | omega | scalar_tac), by (first | omega | scalar_tac), by (first | omega | scalar_tac), decode_of_valid (by assumption)⟩)
    | (intro hc; (try step*))
    | (casesm* _ × _; (try simp only [] at *); (try step*))
    | (split <;> (try step*))
    | (step <;> (try step*))))
  all_goals (try (first | omega | scalar_tac))
end P0Scope54
open scoped Submission.P0Scope54
end
open scoped Submission.P0Scope54

namespace P0Scope55
@[scoped step]
theorem _root_.Submission.fl_mc_hash_spec (input : Slice Std.U8) (p : Std.Usize) :
    slot.fl_mc_hash input p ⦃ fun _ => True ⦄ := by
  rw [slot.fl_mc_hash]
  have hlenv := Slice.len_val input
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat' (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)
end P0Scope55
open scoped Submission.P0Scope55

namespace P0Scope56
@[scoped step]
theorem _root_.Submission.fl_mc_step_spec (tab : Array Std.U32 65536#usize) (h : Std.Usize) (p : Std.Usize) :
    slot.fl_mc_step tab h p ⦃ fun _ => True ⦄ := by
  rw [slot.fl_mc_step]
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat' (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)
end P0Scope56
open scoped Submission.P0Scope56

namespace P0Scope57
@[scoped step]
theorem _root_.Submission.fl_mc_insert_loop_spec (input : Slice Std.U8) (tab : Array Std.U32 65536#usize) («to» : Std.Usize) (lim : Std.Usize) (p : Std.Usize) :
    slot.fl_mc_insert_loop input tab «to» lim p ⦃ fun _ => True ⦄ := by
  rw [slot.fl_mc_insert_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => «to».val - s.2.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1⟩ _
    have hlenv := Slice.len_val input
    simp only [slot.fl_mc_insert_loop.body, lift, Array.to_slice_mut]
    step*
    repeat' (first
      | (intro hc; (try step*))
      | (split <;> (try step*))
      | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply spec_ite_cut <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals (first | omega | scalar_tac)
  · trivial
end P0Scope57
open scoped Submission.P0Scope57

namespace P0Scope58
@[scoped step]
theorem _root_.Submission.fl_mc_insert_spec (input : Slice Std.U8) (tab : Array Std.U32 65536#usize) («from» : Std.Usize) («to» : Std.Usize) :
    slot.fl_mc_insert input tab «from» «to» ⦃ fun _ => True ⦄ := by
  rw [slot.fl_mc_insert]
  have hlenv := Slice.len_val input
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat' (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)
end P0Scope58
open scoped Submission.P0Scope58

section
-- (bind-position ifs are split in this loop: the measure counter is updated by them)
namespace P0Scope59
@[scoped step]
theorem _root_.Submission.fl_mc_parse_loop_spec (input : Slice Std.U8) (out : Slice Std.U32) (n : Std.Usize) (tab : Array Std.U32 65536#usize) (lim : Std.Usize) (pos : Std.Usize) (ntok : Std.Usize) (p : Std.Usize)
    (hn : n.val = input.length) (hout : input.length ≤ out.length)
    (hp : pos.val ≤ n.val) (hntok : ntok.val ≤ pos.val)
    (hdec : LZ77.decode (toks out ntok.val) = some ((bytes input).take pos.val)) (hlim : lim.val ≤ n.val ∧ (lim.val = 0 ∨ lim.val + 8 = n.val)) :
    slot.fl_mc_parse_loop input out n tab lim pos ntok p ⦃ fun r =>
      r.2.1.val ≤ n.val ∧ r.2.2.val ≤ r.2.1.val ∧ r.1.length = out.length ∧
      LZ77.decode (toks r.1 r.2.2.val) = some ((bytes input).take r.2.1.val) ⦄ := by
  rw [slot.fl_mc_parse_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => lim.val - s.2.2.2.2.val)
    (inv := fun s =>
      s.2.2.1.val ≤ n.val ∧ s.2.2.2.1.val ≤ s.2.2.1.val ∧ s.1.length = out.length ∧
      LZ77.decode (toks s.1 s.2.2.2.1.val) = some ((bytes input).take s.2.2.1.val))
  · rintro ⟨out1_, tab1_, pos1_, ntok1_, p1_⟩ ⟨hpn, hnt, hlen, hde⟩
    simp only at hpn hnt hlen hde
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.fl_mc_parse_loop.body, lift, Array.to_slice_mut, alloc.vec.Vec.deref_mut, bind_tc_ok]
    (try step*)
    all_goals (try split)
    all_goals (try step*)
    all_goals (repeat' (first
      | (refine ⟨by (first | omega | scalar_tac), by (first | omega | scalar_tac), by assumption, by assumption, by (first | omega | scalar_tac)⟩)
      | (exact ⟨hpn, hnt, hlen, hde⟩)
      | (refine ⟨by (first | omega | scalar_tac), hlen, ?_⟩
         unfold LZ77.Valid
         rw [hde, show pos1_.val = input.length by (first | omega | scalar_tac)]
         simp)
      | (refine ⟨by (first | omega | scalar_tac), by (first | omega | scalar_tac), hlen, hde, ?_⟩
         unfold LZ77.Valid
         rw [hde, show pos1_.val = input.length by (first | omega | scalar_tac)]
         simp)
      | (intro hc; (try step*))
      | (casesm* _ × _; (try simp only [] at *); (try step*))
      | (split <;> (try step*))
      | (step <;> (try step*))))
    all_goals (try (first | omega | scalar_tac))
  · exact ⟨hp, hntok, rfl, hdec⟩
end P0Scope59
open scoped Submission.P0Scope59
end
open scoped Submission.P0Scope59

section
open scoped Submission.A2StepScope33
namespace P0Scope60
@[scoped step]
theorem _root_.Submission.fl_mc_parse_spec (input : Slice Std.U8) (out : Slice Std.U32) (pos0 : Std.Usize) (ntok0 : Std.Usize)
    (hlen : input.length ≤ out.length)
    (hp : pos0.val ≤ input.length) (hntok : ntok0.val ≤ pos0.val)
    (hdec : LZ77.decode (toks out ntok0.val) = some ((bytes input).take pos0.val)) :
    slot.fl_mc_parse input out pos0 ntok0 ⦃ fun r =>
      r.1.2.val ≤ input.length ∧ r.1.1.val ≤ r.1.2.val ∧ r.2.length = out.length ∧
      LZ77.decode (toks r.2 r.1.1.val) = some ((bytes input).take r.1.2.val) ⦄ := by
  rw [slot.fl_mc_parse]
  have h0 := decode_nil input out
  have hlenv := Slice.len_val input
  try simp only [lift, Array.to_slice_mut, alloc.vec.Vec.deref_mut, bind_tc_ok]
  step*
  all_goals (repeat (first
    | (refine ⟨by (first | omega | scalar_tac), by (first | omega | scalar_tac), by (first | omega | scalar_tac), by assumption⟩)
    | (refine ⟨by (first | omega | scalar_tac), by (first | omega | scalar_tac), by (first | omega | scalar_tac), decode_of_valid (by assumption)⟩)
    | (intro hc; (try step*))
    | (casesm* _ × _; (try simp only [] at *); (try step*))
    | (split <;> (try step*))
    | (step <;> (try step*))))
  all_goals (try (first | omega | scalar_tac))
end P0Scope60
open scoped Submission.P0Scope60
end
open scoped Submission.P0Scope60

namespace P0Scope61
@[scoped step]
theorem _root_.Submission.lg_hs_spec (v : Std.U64) (ks : Std.Usize) :
    slot.lg_hs v ks ⦃ fun _ => True ⦄ := by
  rw [slot.lg_hs]
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat' (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)
end P0Scope61
open scoped Submission.P0Scope61

namespace P0Scope62
@[scoped step]
theorem _root_.Submission.lg_h8_spec (v : Std.U64) :
    slot.lg_h8 v ⦃ fun _ => True ⦄ := by
  rw [slot.lg_h8]
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat' (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)
end P0Scope62
open scoped Submission.P0Scope62

namespace P0Scope63
@[scoped step]
theorem _root_.Submission.lg_tab_spec (head : Array Std.U32 32768#usize) (h : Std.Usize) :
    slot.lg_tab head h ⦃ fun _ => True ⦄ := by
  rw [slot.lg_tab]
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat' (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)
end P0Scope63
open scoped Submission.P0Scope63

namespace P0Scope64
@[scoped step]
theorem _root_.Submission.lg_put_spec (head : Array Std.U32 32768#usize) (h : Std.Usize) (p : Std.Usize) :
    slot.lg_put head h p ⦃ fun _ => True ⦄ := by
  rw [slot.lg_put]
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat' (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)
end P0Scope64
open scoped Submission.P0Scope64

namespace P0Scope65
@[scoped step]
theorem _root_.Submission.lg_ent_spec (h4 : Std.Usize) (p : Std.Usize) :
    slot.lg_ent h4 p ⦃ fun _ => True ⦄ := by
  rw [slot.lg_ent]
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat' (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)
end P0Scope65
open scoped Submission.P0Scope65

namespace P0Scope66
@[scoped step]
theorem _root_.Submission.lg_dec_spec (h4 : Std.Usize) (e : Std.U32) :
    slot.lg_dec h4 e ⦃ fun _ => True ⦄ := by
  rw [slot.lg_dec]
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat' (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)
end P0Scope66
open scoped Submission.P0Scope66

namespace P0Scope67
@[scoped step]
theorem _root_.Submission.lg_ins_spec (head : Array Std.U32 32768#usize) (long : Array Std.U32 32768#usize) (v : Std.U64) (p : Std.Usize) (h4 : Std.Usize) (lo : Std.Usize) :
    slot.lg_ins head long v p h4 lo ⦃ fun _ => True ⦄ := by
  rw [slot.lg_ins]
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat' (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)
end P0Scope67
open scoped Submission.P0Scope67

namespace P0Scope68
@[scoped step]
theorem _root_.Submission.lg_fin_spec (input : Slice Std.U8) (p : Std.Usize) (c : Std.Usize) (x : Std.U64) (cap : Std.Usize) :
    slot.lg_fin input p c x cap ⦃ fun _ => True ⦄ := by
  rw [slot.lg_fin]
  have hlenv := Slice.len_val input
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat' (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)
end P0Scope68
open scoped Submission.P0Scope68

namespace P0Scope69
open scoped A2FastPureChoice A2FastCut in
@[scoped step]
theorem _root_.Submission.lg_eval_spec (input : Slice Std.U8) (p : Std.Usize) (v : Std.U64) (c4 : Std.Usize) (c8 : Std.Usize) (cap : Std.Usize) (lo : Std.Usize) :
    slot.lg_eval input p v c4 c8 cap lo ⦃ fun _ => True ⦄ := by
  rw [slot.lg_eval]
  have hlenv := Slice.len_val input
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat' (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)
end P0Scope69
open scoped Submission.P0Scope69

namespace P0Scope70
@[scoped step]
theorem _root_.Submission.lg_scan_loop_spec (input : Slice Std.U8) (head : Array Std.U32 32768#usize) (long : Array Std.U32 32768#usize) (ks : Std.Usize) (lo : Std.Usize) (acc : Std.U64) (amax : Std.Usize) (n : Std.Usize) (p : Std.Usize) (k : Std.Usize) (m : Std.Usize) (v : Std.U64) (h4 : Std.Usize) (h8 : Std.Usize) (c4 : Std.Usize) (e8 : Std.U32) (hn16 : 16 ≤ n.val) :
    slot.lg_scan_loop input head long ks lo acc amax n p k m v h4 h8 c4 e8 ⦃ fun _ => True ⦄ := by
  rw [slot.lg_scan_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => n.val - s.2.2.2.1.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1, x2, x3, x4, x5, x6, x7, x8, x9⟩ _
    have hlenv := Slice.len_val input
    simp only [slot.lg_scan_loop.body, lift, Array.to_slice_mut]
    step*
    repeat' (first
      | (intro hc; (try step*))
      | (split <;> (try step*))
      | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply spec_ite_cut <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals (first | omega | scalar_tac)
  · trivial
end P0Scope70
open scoped Submission.P0Scope70

namespace P0Scope71
@[scoped step]
theorem _root_.Submission.lg_scan_spec (input : Slice Std.U8) (head : Array Std.U32 32768#usize) (long : Array Std.U32 32768#usize) (pos : Std.Usize) (ks : Std.Usize) (lo : Std.Usize) (acc : Std.U64) (amax : Std.Usize) :
    slot.lg_scan input head long pos ks lo acc amax ⦃ fun _ => True ⦄ := by
  rw [slot.lg_scan]
  have hlenv := Slice.len_val input
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat' (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)
end P0Scope71
open scoped Submission.P0Scope71

namespace P0Scope72
@[scoped step]
theorem _root_.Submission.lg_bext_loop_spec (input : Slice Std.U8) (q : Std.Usize) (d : Std.Usize) (lim : Std.Usize) (e : Std.Usize) (hq : q.val ≤ input.length) (hd : d.val ≤ q.val) (hl : lim.val + d.val ≤ q.val) :
    slot.lg_bext_loop input q d lim e ⦃ fun _ => True ⦄ := by
  rw [slot.lg_bext_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => lim.val - s.val)
    (inv := fun s => True)
  · rintro ⟨x0⟩ _
    have hlenv := Slice.len_val input
    simp only [slot.lg_bext_loop.body, lift, Array.to_slice_mut]
    step*
    repeat' (first
      | (intro hc; (try step*))
      | (split <;> (try step*))
      | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply spec_ite_cut <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals (first | omega | scalar_tac)
  · trivial
end P0Scope72
open scoped Submission.P0Scope72

namespace P0Scope73
@[scoped step]
theorem _root_.Submission.lg_bext_spec (input : Slice Std.U8) (q : Std.Usize) (d : Std.Usize) (lim : Std.Usize) :
    slot.lg_bext input q d lim ⦃ fun _ => True ⦄ := by
  rw [slot.lg_bext]
  have hlenv := Slice.len_val input
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat' (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)
end P0Scope73
open scoped Submission.P0Scope73

namespace P0Scope74
@[scoped step]
theorem _root_.Submission.lg_insert_loop_spec (input : Slice Std.U8) (head : Array Std.U32 32768#usize) (long : Array Std.U32 32768#usize) (ks : Std.Usize) (lo : Std.Usize) (n : Std.Usize) (e : Std.Usize) (p : Std.Usize) :
    slot.lg_insert_loop input head long ks lo n e p ⦃ fun _ => True ⦄ := by
  rw [slot.lg_insert_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => e.val - s.2.2.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1, x2⟩ _
    have hlenv := Slice.len_val input
    simp only [slot.lg_insert_loop.body, lift, Array.to_slice_mut]
    step*
    repeat' (first
      | (intro hc; (try step*))
      | (split <;> (try step*))
      | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply spec_ite_cut <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals (first | omega | scalar_tac)
  · trivial
end P0Scope74
open scoped Submission.P0Scope74

namespace P0Scope75
@[scoped step]
theorem _root_.Submission.lg_insert_spec (input : Slice Std.U8) (head : Array Std.U32 32768#usize) (long : Array Std.U32 32768#usize) («from» : Std.Usize) («to» : Std.Usize) (ks : Std.Usize) (lo : Std.Usize) (ih : Std.Usize) :
    slot.lg_insert input head long «from» «to» ks lo ih ⦃ fun _ => True ⦄ := by
  rw [slot.lg_insert]
  have hlenv := Slice.len_val input
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat' (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)
end P0Scope75
open scoped Submission.P0Scope75

namespace P0Scope76
@[scoped step]
theorem _root_.Submission.lg_min_spec (a : Std.Usize) (b : Std.Usize) :
    slot.lg_min a b ⦃ fun _ => True ⦄ := by
  rw [slot.lg_min]
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat' (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)
end P0Scope76
open scoped Submission.P0Scope76

section
open scoped Submission.A2StepScope33
namespace P0Scope77
@[scoped step]
theorem _root_.Submission.lg_lits_spec (input : Slice Std.U8) (out : Slice Std.U32) (pos : Std.Usize) (s : Std.Usize) (ntok : Std.Usize)
    (hlen : input.length ≤ out.length)
    (hp : pos.val ≤ input.length) (hntok : ntok.val ≤ pos.val)
    (hdec : LZ77.decode (toks out ntok.val) = some ((bytes input).take pos.val)) :
    slot.lg_lits input out pos s ntok ⦃ fun r =>
      r.1.2.val ≤ input.length ∧ r.1.1.val ≤ r.1.2.val ∧ r.2.length = out.length ∧
      LZ77.decode (toks r.2 r.1.1.val) = some ((bytes input).take r.1.2.val) ∧
      (pos.val < input.length → pos.val ≤ r.1.2.val) ⦄ := by
  rw [slot.lg_lits]
  have h0 := decode_nil input out
  have hlenv := Slice.len_val input
  try simp only [lift, Array.to_slice_mut, alloc.vec.Vec.deref_mut, bind_tc_ok]
  step*
  all_goals (repeat (first
    | (refine ⟨by (first | omega | scalar_tac), by (first | omega | scalar_tac), by (first | omega | scalar_tac), by assumption, by (first | omega | scalar_tac)⟩)
    | (refine ⟨by (first | omega | scalar_tac), by (first | omega | scalar_tac), by (first | omega | scalar_tac), decode_of_valid (by assumption), by (first | omega | scalar_tac)⟩)
    | (intro hc; (try step*))
    | (casesm* _ × _; (try simp only [] at *); (try step*))
    | (split <;> (try step*))
    | (step <;> (try step*))))
  all_goals (try (first | omega | scalar_tac))
end P0Scope77
open scoped Submission.P0Scope77
end
open scoped Submission.P0Scope77

section
open scoped Submission.A2StepScope33
namespace P0Scope78
@[scoped step]
theorem _root_.Submission.lg_finish_loop_spec (input : Slice Std.U8) (out : Slice Std.U32) (n : Std.Usize) (pos : Std.Usize) (ntok : Std.Usize)
    (hn : n.val = input.length) (hout : input.length ≤ out.length)
    (hp : pos.val ≤ n.val) (hntok : ntok.val ≤ pos.val)
    (hdec : LZ77.decode (toks out ntok.val) = some ((bytes input).take pos.val)) :
    slot.lg_finish_loop input out n pos ntok ⦃ fun r =>
      r.1.val ≤ input.length ∧ r.2.length = out.length ∧
      LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
  rw [slot.lg_finish_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => n.val - s.2.1.val)
    (inv := fun s =>
      s.2.1.val ≤ n.val ∧ s.2.2.val ≤ s.2.1.val ∧ s.1.length = out.length ∧
      LZ77.decode (toks s.1 s.2.2.val) = some ((bytes input).take s.2.1.val))
  · rintro ⟨out1_, pos1_, ntok1_⟩ ⟨hpn, hnt, hlen, hde⟩
    simp only at hpn hnt hlen hde
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.lg_finish_loop.body, lift, Array.to_slice_mut, alloc.vec.Vec.deref_mut, bind_tc_ok]
    (try step*)
    all_goals (try split)
    all_goals (try step*)
    all_goals (repeat (first
      | (refine ⟨by (first | omega | scalar_tac), by (first | omega | scalar_tac), by assumption, by assumption, by (first | omega | scalar_tac)⟩)
      | (exact ⟨hpn, hnt, hlen, hde⟩)
      | (refine ⟨by (first | omega | scalar_tac), hlen, ?_⟩
         unfold LZ77.Valid
         rw [hde, show pos1_.val = input.length by (first | omega | scalar_tac)]
         simp)
      | (refine ⟨by (first | omega | scalar_tac), by (first | omega | scalar_tac), hlen, hde, ?_⟩
         unfold LZ77.Valid
         rw [hde, show pos1_.val = input.length by (first | omega | scalar_tac)]
         simp)
      | (intro hc; (try step*))
      | (casesm* _ × _; (try simp only [] at *); (try step*))
      | (split <;> (try step*))
      | (step <;> (try step*))))
    all_goals (try (first | omega | scalar_tac))
  · exact ⟨hp, hntok, rfl, hdec⟩
end P0Scope78
open scoped Submission.P0Scope78
end
open scoped Submission.P0Scope78

section
open scoped Submission.A2StepScope33
namespace P0Scope79
@[scoped step]
theorem _root_.Submission.lg_finish_spec (input : Slice Std.U8) (out : Slice Std.U32) (pos0 : Std.Usize) (ntok0 : Std.Usize)
    (hlen : input.length ≤ out.length)
    (hp : pos0.val ≤ input.length) (hntok : ntok0.val ≤ pos0.val)
    (hdec : LZ77.decode (toks out ntok0.val) = some ((bytes input).take pos0.val)) :
    slot.lg_finish input out pos0 ntok0 ⦃ fun r =>
      r.1.val ≤ input.length ∧
      r.2.length = out.length ∧
      LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
  rw [slot.lg_finish]
  have h0 := decode_nil input out
  have hlenv := Slice.len_val input
  try simp only [lift, Array.to_slice_mut, alloc.vec.Vec.deref_mut, bind_tc_ok]
  step*
  all_goals (repeat (first
    | (refine ⟨by (first | omega | scalar_tac), by (first | omega | scalar_tac), valid_of_decode (by assumption) (by (first | omega | scalar_tac))⟩)
    | (refine ⟨by (first | omega | scalar_tac), by (first | omega | scalar_tac), by assumption⟩)
    | (intro hc; (try step*))
    | (casesm* _ × _; (try simp only [] at *); (try step*))
    | (split <;> (try step*))
    | (step <;> (try step*))))
  all_goals (try (first | omega | scalar_tac))
end P0Scope79
open scoped Submission.P0Scope79
end
open scoped Submission.P0Scope79

section
open scoped Submission.A2StepScope33
namespace P0Scope80
@[scoped step]
theorem _root_.Submission.lg_core_loop_spec (input : Slice Std.U8) (out : Slice Std.U32) (ks : Std.Usize) (lo : Std.Usize) (ih : Std.Usize) (acc : Std.U64) (amax : Std.Usize) (n : Std.Usize) (head : Array Std.U32 32768#usize) (long : Array Std.U32 32768#usize) (pos : Std.Usize) (ntok : Std.Usize)
    (hn : n.val = input.length) (hout : input.length ≤ out.length)
    (hp : pos.val ≤ n.val) (hntok : ntok.val ≤ pos.val)
    (hdec : LZ77.decode (toks out ntok.val) = some ((bytes input).take pos.val)) :
    slot.lg_core_loop input out ks lo ih acc amax n head long pos ntok ⦃ fun r =>
      r.1.val ≤ input.length ∧ r.2.length = out.length ∧
      LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
  rw [slot.lg_core_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => n.val - s.2.2.2.1.val)
    (inv := fun s =>
      s.2.2.2.1.val ≤ n.val ∧ s.2.2.2.2.val ≤ s.2.2.2.1.val ∧ s.1.length = out.length ∧
      LZ77.decode (toks s.1 s.2.2.2.2.val) = some ((bytes input).take s.2.2.2.1.val))
  · rintro ⟨out1_, head1_, long1_, pos1_, ntok1_⟩ ⟨hpn, hnt, hlen, hde⟩
    simp only at hpn hnt hlen hde
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.lg_core_loop.body, lift, Array.to_slice_mut, alloc.vec.Vec.deref_mut, bind_tc_ok]
    (try step*)
    all_goals (try split)
    all_goals (try step*)
    all_goals (repeat (first
      | (refine ⟨by (first | omega | scalar_tac), by (first | omega | scalar_tac), by assumption, by assumption, by (first | omega | scalar_tac)⟩)
      | (exact ⟨hpn, hnt, hlen, hde⟩)
      | (refine ⟨by (first | omega | scalar_tac), hlen, ?_⟩
         unfold LZ77.Valid
         rw [hde, show pos1_.val = input.length by (first | omega | scalar_tac)]
         simp)
      | (refine ⟨by (first | omega | scalar_tac), by (first | omega | scalar_tac), hlen, hde, ?_⟩
         unfold LZ77.Valid
         rw [hde, show pos1_.val = input.length by (first | omega | scalar_tac)]
         simp)
      | (intro hc; (try step*))
      | (casesm* _ × _; (try simp only [] at *); (try step*))
      | (split <;> (try step*))
      | (step <;> (try step*))))
    all_goals (try (first | omega | scalar_tac))
  · exact ⟨hp, hntok, rfl, hdec⟩
end P0Scope80
open scoped Submission.P0Scope80
end
open scoped Submission.P0Scope80

section
open scoped Submission.A2StepScope33
namespace P0Scope81
@[scoped step]
theorem _root_.Submission.lg_core_spec (input : Slice Std.U8) (out : Slice Std.U32) (pos0 : Std.Usize) (ntok0 : Std.Usize) (ks : Std.Usize) (lo : Std.Usize) (ih : Std.Usize) (acc : Std.U64) (amax : Std.Usize)
    (hlen : input.length ≤ out.length)
    (hp : pos0.val ≤ input.length) (hntok : ntok0.val ≤ pos0.val)
    (hdec : LZ77.decode (toks out ntok0.val) = some ((bytes input).take pos0.val)) :
    slot.lg_core input out pos0 ntok0 ks lo ih acc amax ⦃ fun r =>
      r.1.val ≤ input.length ∧
      r.2.length = out.length ∧
      LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
  rw [slot.lg_core]
  have h0 := decode_nil input out
  have hlenv := Slice.len_val input
  try simp only [lift, Array.to_slice_mut, alloc.vec.Vec.deref_mut, bind_tc_ok]
  step*
  all_goals (repeat (first
    | (refine ⟨by (first | omega | scalar_tac), by (first | omega | scalar_tac), valid_of_decode (by assumption) (by (first | omega | scalar_tac))⟩)
    | (refine ⟨by (first | omega | scalar_tac), by (first | omega | scalar_tac), by assumption⟩)
    | (intro hc; (try step*))
    | (casesm* _ × _; (try simp only [] at *); (try step*))
    | (split <;> (try step*))
    | (step <;> (try step*))))
  all_goals (try (first | omega | scalar_tac))
end P0Scope81
open scoped Submission.P0Scope81
end
open scoped Submission.P0Scope81

section
open scoped Submission.A2StepScope33
namespace P0Scope82
@[scoped step]
theorem _root_.Submission.lg_parse_d_spec (input : Slice Std.U8) (out : Slice Std.U32)
    (hlen : input.length ≤ out.length) :
    slot.lg_parse_d input out ⦃ fun r =>
      r.1.val ≤ input.length ∧
      r.2.length = out.length ∧
      LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
  rw [slot.lg_parse_d]
  have h0 := decode_nil input out
  have hlenv := Slice.len_val input
  try simp only [lift, Array.to_slice_mut, alloc.vec.Vec.deref_mut, bind_tc_ok]
  step*
  all_goals (repeat (first
    | (refine ⟨by (first | omega | scalar_tac), by (first | omega | scalar_tac), valid_of_decode (by assumption) (by (first | omega | scalar_tac))⟩)
    | (refine ⟨by (first | omega | scalar_tac), by (first | omega | scalar_tac), by assumption⟩)
    | (intro hc; (try step*))
    | (casesm* _ × _; (try simp only [] at *); (try step*))
    | (split <;> (try step*))
    | (step <;> (try step*))))
  all_goals (try (first | omega | scalar_tac))
end P0Scope82
open scoped Submission.P0Scope82
end
open scoped Submission.P0Scope82

section
open scoped Submission.A2StepScope33
namespace P0Scope83
@[scoped step]
theorem _root_.Submission.lg_parse_h_spec (input : Slice Std.U8) (out : Slice Std.U32)
    (hlen : input.length ≤ out.length) :
    slot.lg_parse_h input out ⦃ fun r =>
      r.1.val ≤ input.length ∧
      r.2.length = out.length ∧
      LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
  rw [slot.lg_parse_h]
  have h0 := decode_nil input out
  have hlenv := Slice.len_val input
  try simp only [lift, Array.to_slice_mut, alloc.vec.Vec.deref_mut, bind_tc_ok]
  step*
  all_goals (repeat (first
    | (refine ⟨by (first | omega | scalar_tac), by (first | omega | scalar_tac), valid_of_decode (by assumption) (by (first | omega | scalar_tac))⟩)
    | (refine ⟨by (first | omega | scalar_tac), by (first | omega | scalar_tac), by assumption⟩)
    | (intro hc; (try step*))
    | (casesm* _ × _; (try simp only [] at *); (try step*))
    | (split <;> (try step*))
    | (step <;> (try step*))))
  all_goals (try (first | omega | scalar_tac))
end P0Scope83
open scoped Submission.P0Scope83
end
open scoped Submission.P0Scope83

section
open scoped Submission.A2StepScope33
namespace P0Scope84
@[scoped step]
theorem _root_.Submission.fl_part_spec (input : Slice Std.U8) (out : Slice Std.U32) (mc : Std.Usize) (fh : Array Std.U32 256#usize)
    (hlen : input.length ≤ out.length) :
    slot.fl_part input out mc fh ⦃ fun r =>
      r.1.2.val ≤ input.length ∧ r.1.1.val ≤ r.1.2.val ∧ r.2.length = out.length ∧
      LZ77.decode (toks r.2 r.1.1.val) = some ((bytes input).take r.1.2.val) ⦄ := by
  rw [slot.fl_part]
  have h0 := decode_nil input out
  have hlenv := Slice.len_val input
  try simp only [lift, Array.to_slice_mut, alloc.vec.Vec.deref_mut, bind_tc_ok]
  step*
  all_goals (repeat (first
    | (refine ⟨by (first | omega | scalar_tac), by (first | omega | scalar_tac), by (first | omega | scalar_tac), by assumption⟩)
    | (refine ⟨by (first | omega | scalar_tac), by (first | omega | scalar_tac), by (first | omega | scalar_tac), decode_of_valid (by assumption)⟩)
    | (intro hc; (try step*))
    | (casesm* _ × _; (try simp only [] at *); (try step*))
    | (split <;> (try step*))
    | (step <;> (try step*))))
  all_goals (try (first | omega | scalar_tac))
end P0Scope84
open scoped Submission.P0Scope84
end
open scoped Submission.P0Scope84

namespace P0Scope85
@[scoped step]
theorem _root_.Submission.g_match_spec (input : Slice Std.U8) (p : Std.Usize) (cc : Std.Usize) (cap : Std.Usize) :
    slot.g_match input p cc cap ⦃ fun _ => True ⦄ := by
  rw [slot.g_match]
  have hlenv := Slice.len_val input
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat' (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)
end P0Scope85
open scoped Submission.P0Scope85

namespace P0Scope86
@[scoped step]
theorem _root_.Submission.g_eval_spec (input : Slice Std.U8) (p : Std.Usize) (v : Std.U64) (c8 : Std.Usize) (c4 : Std.Usize) (cap : Std.Usize) :
    slot.g_eval input p v c8 c4 cap ⦃ fun _ => True ⦄ := by
  rw [slot.g_eval]
  have hlenv := Slice.len_val input
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat' (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)
end P0Scope86
open scoped Submission.P0Scope86

section
open scoped Submission.A2StepScope33
namespace P0Scope87
@[scoped step]
theorem _root_.Submission.gr_lits_spec (input : Slice Std.U8) (out : Slice Std.U32) (pos : Std.Usize) (s : Std.Usize) (ntok : Std.Usize)
    (hlen : input.length ≤ out.length)
    (hp : pos.val ≤ input.length) (hntok : ntok.val ≤ pos.val)
    (hdec : LZ77.decode (toks out ntok.val) = some ((bytes input).take pos.val)) :
    slot.gr_lits input out pos s ntok ⦃ fun r =>
      r.1.2.val ≤ input.length ∧ r.1.1.val ≤ r.1.2.val ∧ r.2.length = out.length ∧
      LZ77.decode (toks r.2 r.1.1.val) = some ((bytes input).take r.1.2.val) ∧
      (pos.val < input.length → pos.val ≤ r.1.2.val) ⦄ := by
  rw [slot.gr_lits]
  have h0 := decode_nil input out
  have hlenv := Slice.len_val input
  try simp only [lift, Array.to_slice_mut, alloc.vec.Vec.deref_mut, bind_tc_ok]
  step*
  all_goals (repeat (first
    | (refine ⟨by (first | omega | scalar_tac), by (first | omega | scalar_tac), by (first | omega | scalar_tac), by assumption, by (first | omega | scalar_tac)⟩)
    | (refine ⟨by (first | omega | scalar_tac), by (first | omega | scalar_tac), by (first | omega | scalar_tac), decode_of_valid (by assumption), by (first | omega | scalar_tac)⟩)
    | (intro hc; (try step*))
    | (casesm* _ × _; (try simp only [] at *); (try step*))
    | (split <;> (try step*))
    | (step <;> (try step*))))
  all_goals (try (first | omega | scalar_tac))
end P0Scope87
open scoped Submission.P0Scope87
end
open scoped Submission.P0Scope87

namespace P0Scope88
@[scoped step]
theorem _root_.Submission.fl_qrle_loop0_spec (input : Slice Std.U8) (n : Std.Usize) (h : Array Std.U32 256#usize) (st : Std.Usize) (k : Std.Usize) (c : Std.Usize) :
    slot.fl_qrle_loop0 input n h st k c ⦃ fun _ => True ⦄ := by
  rw [slot.fl_qrle_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun s => 1024 - s.2.2.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1, x2⟩ _
    have hlenv := Slice.len_val input
    simp only [slot.fl_qrle_loop0.body, lift, Array.to_slice_mut]
    step*
    repeat' (first
      | (intro hc; (try step*))
      | (split <;> (try step*))
      | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply spec_ite_cut <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals (first | omega | scalar_tac)
  · trivial
end P0Scope88
open scoped Submission.P0Scope88

namespace P0Scope89
@[scoped step]
theorem _root_.Submission.fl_qrle_loop1_spec (h : Array Std.U32 256#usize) (top : Std.U32) (i : Std.Usize) :
    slot.fl_qrle_loop1 h top i ⦃ fun _ => True ⦄ := by
  rw [slot.fl_qrle_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun s => (256 : Nat) - s.2.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1⟩ _
    simp only [slot.fl_qrle_loop1.body, lift, Array.to_slice_mut]
    step*
    repeat' (first
      | (intro hc; (try step*))
      | (split <;> (try step*))
      | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply spec_ite_cut <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals (first | omega | scalar_tac)
  · trivial
end P0Scope89
open scoped Submission.P0Scope89

namespace P0Scope90
@[scoped step]
theorem _root_.Submission.fl_qrle_spec (input : Slice Std.U8) :
    slot.fl_qrle input ⦃ fun _ => True ⦄ := by
  rw [slot.fl_qrle]
  have hlenv := Slice.len_val input
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat' (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)
end P0Scope90
open scoped Submission.P0Scope90

end Submission
/- Completed development module: Folding -/

namespace Submission
open Aeneas Aeneas.Std Result ControlFlow
open LZ77 (toks bytes bytes_length bytes_getElem! toks_update bytes_congr Matches emit_lit
  emit_match ite_ok)
set_option maxRecDepth 8192
set_option maxHeartbeats 20000000

namespace A2StepScope67
attribute [scoped step] Submission.lextra_spec
end A2StepScope67
namespace A2StepScope68
attribute [scoped step] Submission.dextra_spec
end A2StepScope68
open scoped Submission.A2StepScope67 Submission.A2StepScope68

namespace A2StepScope69
@[scoped step]
theorem _root_.Submission.public_cap_spec (p l d w : Std.Usize)
    (hw : 1 ≤ w.val) (hl : l.val ≤ 258) (hd : d.val ≤ p.val) :
    slot.public_cap p l d w ⦃ fun cap =>
      cap.val + 1 ≤ w.val ∧ l.val + cap.val ≤ 258 ∧ d.val + cap.val ≤ p.val ⦄ := by
  rw [slot.public_cap]
  step*
  all_goals (split <;> step* <;> (first | omega | scalar_tac))

end A2StepScope69
open scoped Submission.A2StepScope69
theorem Matches.back8 {input : Slice Std.U8} {p d k : Nat}
    (hm : Matches input (p-k-d) (p-k) k) (hd : d+k+8 ≤ p)
    (hw : w8 input (p-k-8) = w8 input (p-k-8-d)) :
    Matches input (p-(k+8)-d) (p-(k+8)) (k+8) := by
  have h8 : Matches input (p-k-8-d) (p-k-8) 8 :=
    w8_bytes input _ _ hw.symm
  have hr : Matches input (p-k-8-d+8) (p-k-8+8) k := by
    convert hm using 1 <;> omega
  have ha := Matches.a_append h8 hr
  convert ha using 1 <;> omega

namespace A2StepScope70
attribute [scoped step] Submission.tw8_spec
end A2StepScope70
open scoped Submission.A2StepScope70

theorem public_suffix_loop0_spec (input : Slice Std.U8) (p d cap k : Std.Usize)
    (hp : p.val ≤ input.length) (hd : d.val+cap.val ≤ p.val)
    (hk : k.val ≤ cap.val)
    (hm : Matches input (p.val-k.val-d.val) (p.val-k.val) k.val) :
    slot.public_suffix_loop0 input p d cap k ⦃ fun r =>
      r.val ≤ cap.val ∧ Matches input (p.val-r.val-d.val) (p.val-r.val) r.val ⦄ := by
  rw [slot.public_suffix_loop0]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  apply Std.loop.spec_decr_nat
    (measure := fun r => cap.val-r.val)
    (inv := fun r => r.val ≤ cap.val ∧ Matches input (p.val-r.val-d.val) (p.val-r.val) r.val)
  · rintro k ⟨hk,hm⟩
    simp only [slot.public_suffix_loop0.body]
    step*
    all_goals first
      | exact ⟨hk,hm⟩
      | (refine ⟨by (first | omega | scalar_tac),?_,by (first | omega | scalar_tac)⟩
         rw [show k1.val=k.val+8 by (first | omega | scalar_tac)]
         apply Matches.back8 hm (by (first | omega | scalar_tac))
         rw [show p.val-k.val-8-d.val=i5.val by (first | omega | scalar_tac),
           show p.val-k.val-8=i2.val by (first | omega | scalar_tac),←i3_post,←i6_post,‹i3=i6›])
  · exact ⟨hk,hm⟩

theorem public_suffix_loop1_spec (input : Slice Std.U8) (p d cap k : Std.Usize)
    (hp : p.val ≤ input.length) (hd : d.val+cap.val ≤ p.val)
    (hk : k.val ≤ cap.val)
    (hm : Matches input (p.val-k.val-d.val) (p.val-k.val) k.val) :
    slot.public_suffix_loop1 input p d cap k ⦃ fun r =>
      r.val ≤ cap.val ∧ Matches input (p.val-r.val-d.val) (p.val-r.val) r.val ⦄ := by
  rw [slot.public_suffix_loop1]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  apply Std.loop.spec_decr_nat
    (measure := fun r => cap.val-r.val)
    (inv := fun r => r.val ≤ cap.val ∧ Matches input (p.val-r.val-d.val) (p.val-r.val) r.val)
  · rintro k ⟨hk,hm⟩
    simp only [slot.public_suffix_loop1.body]
    step*
    all_goals first
      | exact ⟨hk,hm⟩
      | (refine ⟨by (first | omega | scalar_tac),
          Matches.a_back_step (i4:=i1) (i7:=i4) (x:=i2) (y:=i5) hm (by (first | omega | scalar_tac))
            (by (first | omega | scalar_tac)) (by (first | omega | scalar_tac)) (by assumption) (by (first | omega | scalar_tac)) (by (first | omega | scalar_tac))
            (by assumption) (by assumption) (by (first | omega | scalar_tac)),by (first | omega | scalar_tac)⟩)
  · exact ⟨hk,hm⟩

namespace A2StepScope71
@[scoped step]
theorem _root_.Submission.public_suffix_head_spec (input : Slice Std.U8) (p d cap k : Std.Usize)
    (hp : p.val ≤ input.length) (hd : d.val+cap.val ≤ p.val) (hk : k.val ≤ cap.val)
    (hm : Matches input (p.val-k.val-d.val) (p.val-k.val) k.val) :
    slot.public_suffix_head input p d cap k ⦃ fun r =>
      r.1.val ≤ cap.val ∧ Matches input (p.val-r.1.val-d.val) (p.val-r.1.val) r.1.val ⦄ := by
  rw [slot.public_suffix_head]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  step*
  all_goals first
    | exact ⟨hk,hm⟩
    | (refine ⟨by (first | omega | scalar_tac), ?_⟩
       exact Matches.a_back_step (i4:=i1) (i7:=i4) (x:=i2) (y:=i5) hm
         (by (first | omega | scalar_tac)) (by (first | omega | scalar_tac)) (by (first | omega | scalar_tac)) (by assumption)
         (by (first | omega | scalar_tac)) (by (first | omega | scalar_tac)) (by assumption) (by apply UScalar.eq_of_val_eq; simp_all) (by (first | omega | scalar_tac)))

end A2StepScope71
open scoped Submission.A2StepScope71
namespace A2StepScope72
attribute [scoped step] Submission.public_suffix_loop0_spec
end A2StepScope72
namespace A2StepScope73
attribute [scoped step] Submission.public_suffix_loop1_spec
end A2StepScope73
open scoped Submission.A2StepScope72 Submission.A2StepScope73

namespace A2StepScope74
open scoped Submission.E2W2Scope in
@[scoped step]
theorem _root_.Submission.public_suffix_spec (input : Slice Std.U8) (p d cap : Std.Usize)
    (hp : p.val ≤ input.length) (hd : d.val+cap.val ≤ p.val) :
    slot.public_suffix input p d cap ⦃ fun r =>
      r.val ≤ cap.val ∧ Matches input (p.val-r.val-d.val) (p.val-r.val) r.val ⦄ := by
  rw [slot.public_suffix]
  have hz : Matches input (p.val-0-d.val) (p.val-0) 0 := Matches.zero input (p.val-d.val) p.val
  step*
  all_goals (repeat (first
    | (casesm* _ × _; try step*)
    | (split <;> try step*)
    | (step <;> try step*)))
  all_goals exact ⟨by assumption, by assumption⟩

end A2StepScope74
open scoped Submission.A2StepScope74
namespace A2StepScope75
@[scoped step]
theorem _root_.Submission.public_back_suffix_spec0 (input : Slice Std.U8) (p l d w cap : Std.Usize)
    (hp : p.val ≤ input.length) (hw : w.val ≤ 258)
    (hcw : cap.val+1 ≤ w.val) (hcl : l.val+cap.val ≤ 258) (hcd : d.val+cap.val ≤ p.val) :
    slot.public_suffix input p d cap ⦃ fun r =>
      r.val+1 ≤ w.val ∧ l.val+r.val ≤ 258 ∧ d.val+r.val ≤ p.val ∧
      Matches input (p.val-r.val-d.val) (p.val-r.val) r.val ⦄ := by
  apply Std.WP.spec_mono (public_suffix_spec input p d cap hp hcd)
  intro r ⟨hr,hmr⟩
  exact ⟨by omega,by omega,by omega,hmr⟩

end A2StepScope75
open scoped Submission.A2StepScope75
namespace A2StepScope76
@[scoped step]
theorem _root_.Submission.nearer_prefix_spec (input : Slice Std.U8) 
    (pp nl oldd : Std.Usize) :
    slot.nearer_prefix input pp nl oldd ⦃ fun r => NearPrefix input pp.val nl.val r.val ⦄ := by
  rw [slot.nearer_prefix]
  simp only [Std.WP.spec_ok, NearPrefix]
  left
  simp


end A2StepScope76
open scoped Submission.A2StepScope76
namespace A2StepScope77
@[scoped step]
theorem _root_.Submission.public_span_better_loop_spec (input : Slice Std.U8) (costs : Array Std.U32 256#usize)
    (pos l2 aa bb tail j : Std.Usize) (hpos : pos.val + l2.val < input.length)
    (hl2 : l2.val ≤ 258) (hj : j.val ≤ l2.val + 1) :
    slot.public_span_better_loop input costs pos l2 aa bb tail j ⦃ fun r => r.val ≤ 1 ⦄ := by
  rw [slot.public_span_better_loop]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  apply Std.loop.spec_decr_nat
    (measure := fun r => l2.val + 1 - r.2.val)
    (inv := fun r => r.2.val ≤ l2.val + 1)
  · rintro ⟨tail, j⟩ hj
    simp only [slot.public_span_better_loop.body]
    step*
    all_goals first
      | (first | omega | scalar_tac)
      | exact ⟨by (first | omega | scalar_tac), by (first | omega | scalar_tac)⟩
  · exact hj

end A2StepScope77
open scoped Submission.A2StepScope77
namespace A2StepScope78
@[scoped step]
theorem _root_.Submission.public_span_better_spec (input : Slice Std.U8) (costs : Array Std.U32 256#usize)
    (pos l1 d1 l2 d2 ex : Std.Usize) (hex : ex.val ≤ 1) :
    slot.public_span_better input costs pos l1 d1 l2 d2 ex ⦃ fun r => r.val ≤ 1 ⦄ := by
  rw [slot.public_span_better]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  step*
  all_goals first
    | (first | omega | scalar_tac)
    | (split <;> step* <;> (first | omega | scalar_tac))


end A2StepScope78
open scoped Submission.A2StepScope78
/-- The bounded scalar price chooser either declines or keeps one/two prefix literals. -/
theorem public_keep_loop_spec (l w remain keep lc best chosen : Std.Usize)
    (hlw : l.val + w.val ≤ Std.Usize.max)
    (hk : 1 ≤ keep.val ∧ keep.val ≤ 3)
    (hchosen : chosen.val = 0 ∨ 1 ≤ chosen.val ∧ chosen.val ≤ 2 ∧ remain.val ≤ chosen.val) :
    slot.public_partial_loop l w remain keep lc best chosen ⦃ fun r =>
      r.val = 0 ∨ 1 ≤ r.val ∧ r.val ≤ 2 ∧ remain.val ≤ r.val ⦄ := by
  rw [slot.public_partial_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun r => 3-r.1.val)
    (inv := fun r => (1 ≤ r.1.val ∧ r.1.val ≤ 3) ∧
      (r.2.2.2.val = 0 ∨ 1 ≤ r.2.2.2.val ∧ r.2.2.2.val ≤ 2 ∧ remain.val ≤ r.2.2.2.val))
  · rintro ⟨keep,lc,best,chosen⟩ ⟨hk,hchosen⟩
    simp only [slot.public_partial_loop.body]
    step*
    all_goals first
      | exact hchosen
      | (apply Std.WP.spec_bind (Pₘ := fun bc =>
            bc.2.val=0 ∨ 1≤bc.2.val ∧ bc.2.val≤2 ∧ remain.val≤bc.2.val)
         · split <;> step*
           all_goals first | exact hchosen | (right; (first | omega | scalar_tac))
         · rintro ⟨best1,chosen1⟩ hchosen1
           step*
           exact ⟨by (first | omega | scalar_tac),by (first | omega | scalar_tac),hchosen1,by (first | omega | scalar_tac)⟩)
  · exact ⟨hk,hchosen⟩

namespace A2StepScope79
@[scoped step]
theorem _root_.Submission.public_keep_spec (l w remain oldcost : Std.Usize)
    (hlw : l.val + w.val ≤ Std.Usize.max) :
    slot.public_partial_loop l w remain 1#usize 0#usize oldcost 0#usize ⦃ fun r =>
      r.val = 0 ∨ 1 ≤ r.val ∧ r.val ≤ 2 ∧ remain.val ≤ r.val ⦄ :=
  public_keep_loop_spec l w remain 1#usize 0#usize oldcost 0#usize hlw
    (by (first | omega | scalar_tac)) (by simp)

end A2StepScope79
open scoped Submission.A2StepScope79
end Submission


namespace Submission
open Aeneas Aeneas.Std Result ControlFlow
set_option maxRecDepth 8192
set_option maxHeartbeats 20000000
open scoped Submission.A2StepScope67
namespace C3PriceScope
@[scoped step]
theorem _root_.Submission.public_price_spec (w l k nl : Std.Usize)
    (hlk : l.val+k.val ≤ Std.Usize.max) :
    slot.public_price w l k nl ⦃ fun _ => True ⦄ := by
  rw [slot.public_price]
  step*
  all_goals trivial
end C3PriceScope
end Submission

/- Completed development module: Partial -/

namespace Submission
open Aeneas Aeneas.Std Result ControlFlow
open LZ77 (toks bytes bytes_length bytes_getElem! Matches emit_lit emit_match ite_ok)
set_option maxRecDepth 8192
set_option maxHeartbeats 20000000
open scoped Submission.A2StepScope69 Submission.A2StepScope75 Submission.A2StepScope76 Submission.A2StepScope67 Submission.A2StepScope68 Submission.A2StepScope79 Submission.C3PriceScope

theorem public_partial_spec (input : Slice Std.U8) (out : Slice Std.U32)
     (nt p l d : Std.Usize) (t : Std.U32) (w k : Std.Usize)
    (costs : Array Std.U32 256#usize)
    (hdec : ADec input out nt.val p.val) (hm : AMatchAt input p.val l.val d.val)
    (h0 : 0 < nt.val) (hntl : nt.val ≤ out.length)
    (ht : (out.val[nt.val - 1]!).val = t.val) (ht24 : 16777216 ≤ t.val)
    (hw : w.val = (t.val - 16777216) % 256 + 3)
    (hkw : k.val+1 ≤ w.val) (hlk : l.val+k.val ≤ 258) (hdk : d.val+k.val ≤ p.val)
    (hchecked : Matches input (p.val-k.val-d.val) (p.val-k.val) k.val) :
    slot.public_partial input out nt p l d t w k costs ⦃ fun r =>
      r.2.length = out.length ∧ ADec input r.2 r.1.1.val r.1.2.1.val ∧
      AMatchAt input r.1.2.1.val r.1.2.2.val d.val ∧
      r.1.2.1.val + r.1.2.2.val = p.val + l.val ∧ r.1.2.1.val ≤ p.val ⦄ := by
  have hinputlen : input.val.length = input.length := rfl
  have houtlen : out.val.length = out.length := rfl
  rw [slot.public_partial]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  have hm' := hm
  obtain ⟨h3, h258, hpl, hd1, hd32, hdp, hmm⟩ := hm'
  have hdec' := hdec
  obtain ⟨hps, hntp, hso, hde⟩ := hdec'
  have hwt : w.val = LZ77.tokLen (out.val[nt.val - 1]!).val := by
    rw [ht, hw]; simp only [LZ77.tokLen, LZ77.MATCH_BASE]
  have ht256 : 256 ≤ (out.val[nt.val - 1]!).val := by rw [ht]; omega
  have hw3 : 3 ≤ w.val := by (first | omega | scalar_tac)
  have hw258 : w.val ≤ 258 := by (first | omega | scalar_tac)
  obtain ⟨hwp,hpre⟩ := ADec.pop_match hdec h0 hntl ht256
  rw [←hwt] at hwp hpre
  have hntpre : nt.val-1 ≤ p.val-w.val := hpre.2.1
  have hpin : p.val < input.length := by omega
  step*
  all_goals try exact ⟨rfl,hdec,hm,rfl,le_refl _⟩
  focus
       have hkeep : 1≤chosen.val ∧ chosen.val≤2 ∧ remain.val≤chosen.val := by
         rcases chosen_post with hz | hz
         · exfalso; (first | omega | scalar_tac)
         · exact hz
       have hbyte0 : i11.val = (input.val[pp.val]!).val := by
         rw [getElem!_pos input.val pp.val (by (first | omega | scalar_tac)),←i9_post,i11_post,
           Std.U8.cast_U32_val_eq]
       have hfirst := absorb_one_dec (out1:=index_mut_back i11) (idx:=i10) (v:=i11) hdec h0 hntl ht256 hwt hw3 hpin i10_post1
         (by simpa only [pp_post1] using hbyte0) (by rw [__post2])
       have hfirstlen : (index_mut_back i11).length=out.length := by
         rw [__post2,Std.Slice.set_length]
       apply Std.WP.spec_bind (Pₘ := fun out1 => out1.length=out.length ∧
           ADec input out1 (nt.val-1+chosen.val) (pp.val+chosen.val))
       · split
         case isTrue htwo =>
           step*
           have hbyte1 : i14.val=(input.val[pp.val+1]!).val := by
             rw [show pp.val+1=i12.val by (first | omega | scalar_tac),
               getElem!_pos input.val i12.val (by (first | omega | scalar_tac)),←i13_post,i14_post,
               Std.U8.cast_U32_val_eq]
           have htwoDec := absorb_two_dec (out1:=index_mut_back i11) (out2:=out1) (nt0:=i10) (nt1:=nt) (v0:=i11) (v1:=i14) hdec h0 hntl ht256 hwt hw3 pp_post1
             i10_post1 rfl hbyte0 hbyte1 (by rw [__post2]) out1_post
           refine ⟨htwoDec.1,?_⟩
           rw [show nt.val-1+chosen.val=nt.val+1 by (first | omega | scalar_tac),
             show pp.val+chosen.val=p.val-w.val+2 by (first | omega | scalar_tac)]
           exact htwoDec.2
         case isFalse hone =>
           step*
       · rintro out1 ⟨hlen,hnewdec⟩
         step*
         apply absorb_match_post (nt:=nt.val) (keep:=chosen.val) hm
           (by simpa only [pp_post1,i12_post,i10_post1] using hnewdec) hlen hchecked pp_post2
           (by (first | omega | scalar_tac)) (by (first | omega | scalar_tac)) hlk hdk
           (by (first | omega | scalar_tac)) (by (first | omega | scalar_tac))

end Submission


namespace Submission
open Aeneas Aeneas.Std Result ControlFlow
open LZ77 (toks bytes bytes_getElem! Matches)
set_option maxRecDepth 8192
set_option maxHeartbeats 20000000
open scoped Submission.C3PriceScope
namespace C3OneScope
@[scoped step]
theorem _root_.Submission.public_one_spec (input : Slice Std.U8) (out : Slice Std.U32)
    (nt p l d : Std.Usize) (t : Std.U32) (w k : Std.Usize)
    (hdec : ADec input out nt.val p.val) (hm : AMatchAt input p.val l.val d.val)
    (h0 : 0 < nt.val) (hntl : nt.val ≤ out.length)
    (ht : (out.val[nt.val-1]!).val=t.val) (ht24 : 16777216≤t.val)
    (hw : w.val=(t.val-16777216)%256+3) (hw4 : 4<w.val) (hk : k.val=1)
    (hlk : l.val+k.val≤258) (hdk : d.val+k.val≤p.val)
    (hchecked : Matches input (p.val-k.val-d.val) (p.val-k.val) k.val) :
    slot.public_one input out nt p l d t w k ⦃ fun r =>
      r.2.length=out.length ∧ ADec input r.2 r.1.1.val r.1.2.1.val ∧
      AMatchAt input r.1.2.1.val r.1.2.2.val d.val ∧
      r.1.2.1.val+r.1.2.2.val=p.val+l.val ∧ r.1.2.1.val≤p.val ⦄ := by
  rw [slot.public_one]
  have hmax : input.length≤Std.Usize.max := Std.Slice.length_ineq input
  have hwt : w.val=LZ77.tokLen (out.val[nt.val-1]!).val := by
    rw [ht,hw];simp only [LZ77.tokLen,LZ77.MATCH_BASE]
  have ht256 : 256≤(out.val[nt.val-1]!).val := by rw [ht];omega
  have hchecked1 : Matches input (p.val-1-d.val) (p.val-1) 1 := by
    simpa only [hk] using hchecked
  have hold : NearPrefix input (p.val-w.val) (w.val-1) ((t.val-16777216)/256+1) := by
    apply old_prefix_near hdec h0 hntl ht256 hwt
    · simp only [LZ77.tokDist,LZ77.MATCH_BASE];rw [ht]
    · omega
    · omega
  rcases hold with hzero | hold
  · omega
  · step*
    all_goals first
      | exact ⟨rfl,hdec,hm,rfl,le_refl _⟩
      | (apply fold_part_post (w:=w.val) (k:=1) (c:=((t.val-16777216)/256+1))
          (nl:=w.val-1) (pp:=p.val-w.val) hdec hm (by omega) hntl ht256 hwt hchecked1 (Or.inr hold)
         all_goals first | assumption | scalar_tac | (simp only [LZ77.mkMatch,LZ77.MATCH_BASE];omega))
end C3OneScope
end Submission

/- Completed development module: Back -/

namespace Submission
open Aeneas Aeneas.Std Result ControlFlow
open LZ77 (toks bytes bytes_length bytes_getElem! toks_update bytes_congr Matches emit_lit
  emit_match ite_ok)
set_option maxRecDepth 8192
set_option maxHeartbeats 20000000
namespace A2StepScope80
attribute [scoped step] Submission.public_partial_spec
end A2StepScope80
open scoped Submission.A2StepScope69 Submission.A2StepScope74 Submission.A2StepScope80 Submission.C3OneScope

open scoped Submission.E2LitScope in
theorem public_back_step_spec (input : Slice Std.U8) (out : Slice Std.U32)
     (costs : Array Std.U32 256#usize)
    (nt p l d back : Std.Usize)
    (L E P0 : Nat) (hinv : ABackInv input L d.val E P0 out nt.val p.val l.val)
    (hnt0 : 0 < nt.val) (hntl : nt.val ≤ out.length) (hdp : d.val < p.val)
    (hl : l.val < 258) (hback : back.val < 16) :
    slot.public_back_step input out nt p l d back costs ⦃ fun r =>
      ABackInv input L d.val E P0 r.2 r.1.1.val r.1.2.1.val r.1.2.2.1.val ∧
      16 - r.1.2.2.2.val < 16 - back.val ⦄ := by
  rw [slot.public_back_step]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  have hinv' := hinv
  obtain ⟨hdec, hL, hm, hE, hP⟩ := hinv'
  have hm' := hm
  obtain ⟨h3, h258, hpl, hd1, hd32, hdp', hmm⟩ := hm'
  have hps : p.val ≤ input.length := hdec.1
  step*
  all_goals first
    | exact ⟨hinv,by scalar_tac⟩
    | (rw [← i_post1, getElem!_pos out.val i.val (by (first | omega | scalar_tac)), ← t_post])
    | (refine ⟨ABackInv.lit2 (t := t) hinv
          i_post1 hntl (by omega) (by (first | omega | scalar_tac)) t_post (by assumption)
          (by (first | omega | scalar_tac)) (b_post (by assumption)).2 hl hdp
          (by (first | omega | scalar_tac)), by (first | omega | scalar_tac)⟩)
    | (refine ⟨ABackInv.part hinv (by assumption) (by assumption) (by assumption)
          (by assumption) (by assumption), by (first | omega | scalar_tac)⟩)
    | (have htv : (out.val[nt.val - 1]!).val = t.val := by
         rw [← i_post1, getElem!_pos out.val i.val (by (first | omega | scalar_tac)), ← t_post]
       have hwv : w.val = LZ77.tokLen (out.val[nt.val - 1]!).val := by
         rw [htv]; simp only [LZ77.tokLen,LZ77.MATCH_BASE]; (first | omega | scalar_tac)
       obtain ⟨hwl,hdec'⟩ := ADec.pop_match hdec hnt0 hntl (by rw [htv]; (first | omega | scalar_tac))
       rw [←hwv] at hdec'
       have hmw : Matches input (p.val-w.val-d.val) (p.val-w.val) w.val := by
         convert k_post2 using 1 <;> (first | omega | scalar_tac)
       have hm' := AMatchAt.back_match hm (by (first | omega | scalar_tac)) (by (first | omega | scalar_tac)) (by (first | omega | scalar_tac)) hmw
       refine ⟨⟨?_,hL,?_,by (first | omega | scalar_tac),by (first | omega | scalar_tac)⟩,by (first | omega | scalar_tac)⟩
       · convert hdec' using 1 <;> (first | omega | scalar_tac)
       · convert hm' using 1 <;> (first | omega | scalar_tac))


namespace A2StepScope81
attribute [scoped step] Submission.public_back_step_spec
end A2StepScope81
open scoped Submission.A2StepScope81

theorem public_back_loop_spec (input : Slice Std.U8) (out : Slice Std.U32)
     (costs : Array Std.U32 256#usize)
    (d nt p l back : Std.Usize)
    (L E P0 : Nat) (hinv : ABackInv input L d.val E P0 out nt.val p.val l.val)
    :
    slot.public_back_loop input out d costs nt p l back ⦃ fun r =>
      ABackInv input L d.val E P0 r.1 r.2.1.val r.2.2.1.val r.2.2.2.val ⦄ := by
  rw [slot.public_back_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun r => 16 - r.2.2.2.2.val)
    (inv := fun r => ABackInv input L d.val E P0 r.1 r.2.1.val r.2.2.1.val
      r.2.2.2.1.val)
  · rintro ⟨out, nt, p, l, back⟩ hinv
    simp only [slot.public_back_loop.body]
    step*
  · exact hinv

namespace A2StepScope82
attribute [scoped step] Submission.public_back_loop_spec
end A2StepScope82
open scoped Submission.A2StepScope82

namespace A2StepScope83
@[scoped step]
theorem _root_.Submission.public_back_spec (input : Slice Std.U8) (out : Slice Std.U32)
     (costs : Array Std.U32 256#usize)
    (nt p l d : Std.Usize)
    (hdec : ADec input out nt.val p.val) (hm : AMatchAt input p.val l.val d.val) :
    slot.public_back input out nt p l d costs ⦃ fun r =>
      ABackInv input out.length d.val (p.val + l.val) p.val
        r.2 r.1.1.val r.1.2.1.val r.1.2.2.val ⦄ := by
  rw [slot.public_back]
  have hinv : ABackInv input out.length d.val (p.val + l.val) p.val
      out nt.val p.val l.val := ⟨hdec, rfl, hm, rfl, le_refl _⟩
  apply Std.WP.spec_bind (public_back_loop_spec input out costs d nt p l 0#usize
    out.length (p.val + l.val) p.val hinv)
  rintro ⟨out1, nt1, p1, l1⟩ h
  exact h

end A2StepScope83
open scoped Submission.A2StepScope83
namespace A2StepScope84
@[scoped step]
theorem _root_.Submission.public_back_gate_spec (input : Slice Std.U8) (out : Slice Std.U32)
     (costs : Array Std.U32 256#usize)
    (nt p l d : Std.Usize)
    (hdec : ADec input out nt.val p.val) (hm : AMatchAt input p.val l.val d.val) :
    slot.public_back_gate input out nt p l d costs ⦃ fun r =>
      ABackInv input out.length d.val (p.val + l.val) p.val
        r.2 r.1.1.val r.1.2.1.val r.1.2.2.val ⦄ := by
  rw [slot.public_back_gate]
  have hinv : ABackInv input out.length d.val (p.val + l.val) p.val
      out nt.val p.val l.val := ⟨hdec, rfl, hm, rfl, le_refl _⟩
  have hm' := hm
  obtain ⟨h3, h258, hpl, hd1, hd32, hdp, hmm⟩ := hm'
  apply Std.WP.spec_bind (E2_gate2_spec input p d hd32 (by omega))
  intro b _
  split
  case isTrue hgt =>
    step*
  case isFalse hle =>
    simpa using hinv

end A2StepScope84
open scoped Submission.A2StepScope84
end Submission


/- Completed development module: Main (engine G) -/

namespace Submission
open Aeneas Aeneas.Std Result ControlFlow
open LZ77 (toks bytes bytes_getElem! Matches emit_lit emit_match)
set_option maxRecDepth 8192
set_option maxHeartbeats 4000000
set_option linter.unusedTactic false
set_option linter.unreachableTactic false
set_option linter.unusedVariables false
set_option linter.unusedSimpArgs false

namespace A2StepScope85
attribute [scoped step] Submission.entropy256_spec
end A2StepScope85
namespace A2StepScope86
attribute [scoped step] Submission.share_spec
end A2StepScope86
namespace A2StepScope87
attribute [scoped step] Submission.low_mode_spec
end A2StepScope87
namespace A2StepScope88
attribute [scoped step] Submission.fl_sample_spec
end A2StepScope88
namespace A2StepScope89
attribute [scoped step] Submission.fl_stats_spec
end A2StepScope89
namespace A2StepScope90
attribute [scoped step] Submission.fl_mode_spec
end A2StepScope90
open scoped Submission.A2StepScope1 Submission.A2StepScope68 Submission.A2StepScope67 Submission.A2StepScope2 Submission.A2StepScope3 Submission.A2StepScope85 Submission.A2StepScope4 Submission.A2StepScope86 Submission.A2StepScope87 Submission.A2StepScope70 Submission.A2StepScope5 Submission.A2StepScope6 Submission.A2StepScope7 Submission.A2StepScope8 Submission.A2StepScope9 Submission.A2StepScope10 Submission.A2StepScope11 Submission.A2StepScope12 Submission.A2StepScope13 Submission.A2StepScope14 Submission.A2StepScope15 Submission.A2StepScope16 Submission.A2StepScope17 Submission.A2StepScope18 Submission.A2StepScope19 Submission.A2StepScope20 Submission.A2StepScope88 Submission.A2StepScope21 Submission.A2StepScope22 Submission.A2StepScope23 Submission.A2StepScope24 Submission.A2StepScope25 Submission.A2StepScope26 Submission.A2StepScope27 Submission.A2StepScope28 Submission.A2StepScope89 Submission.A2StepScope29 Submission.A2StepScope30 Submission.A2StepScope31 Submission.A2StepScope90 Submission.A2StepScope32 Submission.A2StepScope34 Submission.A2StepScope35 Submission.A2StepScope36 Submission.A2StepScope37 Submission.A2StepScope38 Submission.A2StepScope39 Submission.A2StepScope40 Submission.A2StepScope41 Submission.A2StepScope42 Submission.A2StepScope43 Submission.A2StepScope44 Submission.A2StepScope45 Submission.A2StepScope46 Submission.A2StepScope47 Submission.A2StepScope48 Submission.A2StepScope49 Submission.A2StepScope50 Submission.A2StepScope51 Submission.A2StepScope52 Submission.A2StepScope53 Submission.A2StepScope54 Submission.A2StepScope55 Submission.A2StepScope56 Submission.A2StepScope57 Submission.A2StepScope58 Submission.A2StepScope59 Submission.A2StepScope60 Submission.A2StepScope61 Submission.A2StepScope62 Submission.A2StepScope63 Submission.A2StepScope64 Submission.A2StepScope65 Submission.A2StepScope66 Submission.A2StepScope33
open scoped Submission.A2StepScope78
attribute [-step] ite_true_spec

namespace A2StepScope91
@[scoped step]
theorem _root_.Submission.g_step_ite_spec (ts : Std.Usize) :
    (if ts = 0#usize then ok 1#usize else if ts > 16#usize then ok 1#usize else ok ts) ⦃ fun r => 1 ≤ r.val ∧ r.val ≤ 16 ⦄ := by
  split
  · simp only [Std.WP.spec_ok]; (first | omega | scalar_tac)
  · split <;> simp only [Std.WP.spec_ok] <;> (first | omega | scalar_tac)

end A2StepScope91
open scoped Submission.A2StepScope91
namespace A2StepScope92
@[scoped step]
theorem _root_.Submission.g_ite_ok_spec {α : Type} (c : Prop) [Decidable c] (a b : α) :
    (if c then ok a else ok b) ⦃ fun _ => True ⦄ := by
  split <;> simp only [Std.WP.spec_ok]

end A2StepScope92
open scoped Submission.A2StepScope92
namespace A2StepScope93
@[scoped step]
theorem _root_.Submission.g_acc_ite_spec (over : Std.Usize) :
    (if over < slot.G_AMAX then over + 1#usize else ok slot.G_AMAX) ⦃ fun r => 1 ≤ r.val ∧ r.val ≤ 16 ⦄ := by
  split
  · step*
  · simp only [Std.WP.spec_ok]; (first | omega | scalar_tac)

end A2StepScope93
open scoped Submission.A2StepScope93
namespace A2StepScope94
@[scoped step]
theorem _root_.Submission.g_ld8_ite_spec (c : Prop) [Decidable c] (input : Slice Std.U8) (q : Std.Usize) :
    (if c then slot.ld8 input q else ok 0#u64) ⦃ fun _ => True ⦄ := by
  split
  · step*
  · simp only [Std.WP.spec_ok]

end A2StepScope94
open scoped Submission.A2StepScope94
namespace A2StepScope95
@[scoped step]
theorem _root_.Submission.g_h4_spec (v : Std.U64) :
    slot.g_h4 v ⦃ fun _ => True ⦄ := by
  rw [slot.g_h4]
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (casesm* _ × _; (try simp only []); (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)

end A2StepScope95
open scoped Submission.A2StepScope95
namespace A2StepScope96
@[scoped step]
theorem _root_.Submission.g_h8_spec (v : Std.U64) :
    slot.g_h8 v ⦃ fun _ => True ⦄ := by
  rw [slot.g_h8]
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (casesm* _ × _; (try simp only []); (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)

end A2StepScope96
open scoped Submission.A2StepScope96
namespace A2StepScope97
@[scoped step]
theorem _root_.Submission.g_ent_spec (h4 : Std.Usize) (p : Std.Usize) :
    slot.g_ent h4 p ⦃ fun _ => True ⦄ := by
  rw [slot.g_ent]
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (casesm* _ × _; (try simp only []); (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)

end A2StepScope97
open scoped Submission.A2StepScope97
namespace A2StepScope98
@[scoped step]
theorem _root_.Submission.g_dec_spec (h4 : Std.Usize) (e : Std.U32) :
    slot.g_dec h4 e ⦃ fun _ => True ⦄ := by
  rw [slot.g_dec]
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (casesm* _ × _; (try simp only []); (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)

end A2StepScope98
open scoped Submission.A2StepScope98
namespace A2StepScope99
@[scoped step]
theorem _root_.Submission.g_tab_spec (t4 : Array Std.U32 65536#usize) (t8 : Array Std.U32 65536#usize) (h4 : Std.Usize) (h8 : Std.Usize) :
    slot.g_tab t4 t8 h4 h8 ⦃ fun _ => True ⦄ := by
  rw [slot.g_tab]
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (casesm* _ × _; (try simp only []); (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)

end A2StepScope99
open scoped Submission.A2StepScope99
namespace A2StepScope100
@[scoped step]
theorem _root_.Submission.g_put_spec (t4 : Array Std.U32 65536#usize) (t8 : Array Std.U32 65536#usize) (h4 : Std.Usize) (h8 : Std.Usize) (p : Std.Usize) :
    slot.g_put t4 t8 h4 h8 p ⦃ fun _ => True ⦄ := by
  rw [slot.g_put]
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (casesm* _ × _; (try simp only []); (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)

end A2StepScope100
open scoped Submission.A2StepScope100
namespace A2StepScope101
@[scoped step]
theorem _root_.Submission.g_insert_stride_loop_spec (input : Slice Std.U8) (t4 : Array Std.U32 65536#usize) (t8 : Array Std.U32 65536#usize) («to» : Std.Usize) (ts : Std.Usize) (n : Std.Usize) (p : Std.Usize) :
    slot.g_insert_stride_loop input t4 t8 «to» ts n p ⦃ fun _ => True ⦄ := by
  rw [slot.g_insert_stride_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => «to».val - s.2.2.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1, x2⟩ _
    simp only [slot.g_insert_stride_loop.body, lift, Array.to_slice_mut]
    step*
    repeat (first
      | (intro hc; (try step*))
      | (split <;> (try step*))
      | (casesm* _ × _; (try simp only []); (try step*))
      | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply spec_ite_cut <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals (try (first | omega | scalar_tac))
  · trivial

end A2StepScope101
open scoped Submission.A2StepScope101
namespace A2StepScope102
@[scoped step]
theorem _root_.Submission.g_insert_stride_spec (input : Slice Std.U8) (t4 : Array Std.U32 65536#usize) (t8 : Array Std.U32 65536#usize) («from» : Std.Usize) («to» : Std.Usize) (ts : Std.Usize) :
    slot.g_insert_stride input t4 t8 «from» «to» ts ⦃ fun _ => True ⦄ := by
  rw [slot.g_insert_stride]
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (casesm* _ × _; (try simp only []); (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)

end A2StepScope102
open scoped Submission.A2StepScope102
namespace F1StepScope1
@[scoped step]
theorem _root_.Submission.g_ins1_spec (input : Slice Std.U8) (t4 : Array Std.U32 65536#usize) (t8 : Array Std.U32 65536#usize) (p : Std.Usize) :
    slot.g_ins1 input t4 t8 p ⦃ fun _ => True ⦄ := by
  rw [slot.g_ins1]
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (casesm* _ × _; (try simp only []); (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)

end F1StepScope1
open scoped Submission.F1StepScope1
namespace F1StepScope2
@[scoped step]
theorem _root_.Submission.g_ins_if_spec (input : Slice Std.U8) (t4 : Array Std.U32 65536#usize) (t8 : Array Std.U32 65536#usize) (p : Std.Usize) (e : Std.Usize) :
    slot.g_ins_if input t4 t8 p e ⦃ fun _ => True ⦄ := by
  rw [slot.g_ins_if]
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (casesm* _ × _; (try simp only []); (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)

end F1StepScope2
open scoped Submission.F1StepScope2
namespace A2StepScope103
@[scoped step]
theorem _root_.Submission.g_insert_match_spec (input : Slice Std.U8) (t4 : Array Std.U32 65536#usize) (t8 : Array Std.U32 65536#usize) («from» : Std.Usize) («to» : Std.Usize) (skip : Std.Usize) :
    slot.g_insert_match input t4 t8 «from» «to» skip ⦃ fun _ => True ⦄ := by
  rw [slot.g_insert_match]
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (casesm* _ × _; (try simp only []); (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)

end A2StepScope103
open scoped Submission.A2StepScope103
namespace A2StepScope104
@[scoped step]
theorem _root_.Submission.g3_h3_spec (v : Std.U64) :
    slot.g3_h3 v ⦃ fun _ => True ⦄ := by
  rw [slot.g3_h3]
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (casesm* _ × _; (try simp only []); (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)

end A2StepScope104
open scoped Submission.A2StepScope104
namespace A2StepScope105
@[scoped step]
theorem _root_.Submission.g3_put3_spec (t3 : Array Std.U32 65536#usize) (h3 : Std.Usize) (p : Std.Usize) :
    slot.g3_put3 t3 h3 p ⦃ fun _ => True ⦄ := by
  rw [slot.g3_put3]
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (casesm* _ × _; (try simp only []); (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)

end A2StepScope105
open scoped Submission.A2StepScope105
namespace A2StepScope106
@[scoped step]
theorem _root_.Submission.g3_insert_stride_loop_spec (input : Slice Std.U8) (t4 : Array Std.U32 65536#usize) (t8 : Array Std.U32 65536#usize) (t3 : Array Std.U32 65536#usize) («to» : Std.Usize) (ts : Std.Usize) (m3 : Std.Usize) (n : Std.Usize) (p : Std.Usize) :
    slot.g3_insert_stride_loop input t4 t8 t3 «to» ts m3 n p ⦃ fun _ => True ⦄ := by
  rw [slot.g3_insert_stride_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => «to».val - s.2.2.2.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1, x2, x3⟩ _
    simp only [slot.g3_insert_stride_loop.body, lift, Array.to_slice_mut]
    step*
    repeat (first
      | (intro hc; (try step*))
      | (split <;> (try step*))
      | (casesm* _ × _; (try simp only []); (try step*))
      | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply spec_ite_cut <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals (try (first | omega | scalar_tac))
  · trivial

end A2StepScope106
open scoped Submission.A2StepScope106
namespace A2StepScope107
@[scoped step]
theorem _root_.Submission.g3_insert_stride_spec (input : Slice Std.U8) (t4 : Array Std.U32 65536#usize) (t8 : Array Std.U32 65536#usize) (t3 : Array Std.U32 65536#usize) («from» : Std.Usize) («to» : Std.Usize) (ts : Std.Usize) (m3 : Std.Usize) :
    slot.g3_insert_stride input t4 t8 t3 «from» «to» ts m3 ⦃ fun _ => True ⦄ := by
  rw [slot.g3_insert_stride]
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (casesm* _ × _; (try simp only []); (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)

end A2StepScope107
open scoped Submission.A2StepScope107
namespace A2StepScope108
@[scoped step]
theorem _root_.Submission.g3_insert_match_spec (input : Slice Std.U8) (t4 : Array Std.U32 65536#usize) (t8 : Array Std.U32 65536#usize) (t3 : Array Std.U32 65536#usize) («from» : Std.Usize) («to» : Std.Usize) (m3 : Std.Usize) (skip : Std.Usize) :
    slot.g3_insert_match input t4 t8 t3 «from» «to» m3 skip ⦃ fun _ => True ⦄ := by
  rw [slot.g3_insert_match]
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (casesm* _ × _; (try simp only []); (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)

end A2StepScope108
open scoped Submission.A2StepScope108
namespace A2StepScope109
@[scoped step]
theorem _root_.Submission.gh_h4_spec (v : Std.U64) :
    slot.gh_h4 v ⦃ fun _ => True ⦄ := by
  rw [slot.gh_h4]
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (casesm* _ × _; (try simp only []); (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)

end A2StepScope109
open scoped Submission.A2StepScope109
namespace A2StepScope110
@[scoped step]
theorem _root_.Submission.gh_h8_spec (v : Std.U64) :
    slot.gh_h8 v ⦃ fun _ => True ⦄ := by
  rw [slot.gh_h8]
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (casesm* _ × _; (try simp only []); (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)

end A2StepScope110
open scoped Submission.A2StepScope110
namespace A2StepScope111
@[scoped step]
theorem _root_.Submission.gh_tab_spec (t4 : Array Std.U32 65536#usize) (t8 : Array Std.U32 65536#usize) (h4 : Std.Usize) (h8 : Std.Usize) :
    slot.gh_tab t4 t8 h4 h8 ⦃ fun _ => True ⦄ := by
  rw [slot.gh_tab]
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (casesm* _ × _; (try simp only []); (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)

end A2StepScope111
open scoped Submission.A2StepScope111
namespace A2StepScope112
@[scoped step]
theorem _root_.Submission.gh_put_spec (t4 : Array Std.U32 65536#usize) (t8 : Array Std.U32 65536#usize) (h4 : Std.Usize) (h8 : Std.Usize) (p : Std.Usize) :
    slot.gh_put t4 t8 h4 h8 p ⦃ fun _ => True ⦄ := by
  rw [slot.gh_put]
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (casesm* _ × _; (try simp only []); (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)

end A2StepScope112
open scoped Submission.A2StepScope112
namespace A2StepScope113
@[scoped step]
theorem _root_.Submission.gh_insert_stride_loop_spec (input : Slice Std.U8) (t4 : Array Std.U32 65536#usize) (t8 : Array Std.U32 65536#usize) («to» : Std.Usize) (ts : Std.Usize) (n : Std.Usize) (p : Std.Usize) :
    slot.gh_insert_stride_loop input t4 t8 «to» ts n p ⦃ fun _ => True ⦄ := by
  rw [slot.gh_insert_stride_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => «to».val - s.2.2.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1, x2⟩ _
    simp only [slot.gh_insert_stride_loop.body, lift, Array.to_slice_mut]
    step*
    repeat (first
      | (intro hc; (try step*))
      | (split <;> (try step*))
      | (casesm* _ × _; (try simp only []); (try step*))
      | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply spec_ite_cut <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals (try (first | omega | scalar_tac))
  · trivial

end A2StepScope113
open scoped Submission.A2StepScope113
namespace A2StepScope114
@[scoped step]
theorem _root_.Submission.gh_insert_stride_spec (input : Slice Std.U8) (t4 : Array Std.U32 65536#usize) (t8 : Array Std.U32 65536#usize) («from» : Std.Usize) («to» : Std.Usize) (ts : Std.Usize) :
    slot.gh_insert_stride input t4 t8 «from» «to» ts ⦃ fun _ => True ⦄ := by
  rw [slot.gh_insert_stride]
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (casesm* _ × _; (try simp only []); (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)

end A2StepScope114
open scoped Submission.A2StepScope114
namespace A2StepScope115
@[scoped step]
theorem _root_.Submission.gh_insert_match_spec (input : Slice Std.U8) (t4 : Array Std.U32 65536#usize) (t8 : Array Std.U32 65536#usize) («from» : Std.Usize) («to» : Std.Usize) :
    slot.gh_insert_match input t4 t8 «from» «to» ⦃ fun _ => True ⦄ := by
  rw [slot.gh_insert_match]
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (casesm* _ × _; (try simp only []); (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5, r6⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)


end A2StepScope115
open scoped Submission.A2StepScope115
end Submission

open Aeneas Aeneas.Std Result ControlFlow
open Submission
set_option maxHeartbeats 10000000
set_option maxRecDepth 8192
namespace A2Research

theorem pack_step (a : BitVec w) (b : BitVec w) (i : Nat)
    (hb : b.toNat < 2^i) (ha : a.toNat*2^i < 2^w) :
    ((a <<< i) ||| b).toNat = a.toNat*2^i+b.toNat := by
  rw [BitVec.toNat_or, BitVec.toNat_shiftLeft, Nat.shiftLeft_eq,
    Nat.mod_eq_of_lt ha, Nat.mul_comm, ← Nat.two_pow_add_eq_or_of_lt hb]

theorem pack4_value (a b c d : BitVec 8) :
    ((d.setWidth 32 <<< 24) ||| (c.setWidth 32 <<< 16) ||| (b.setWidth 32 <<< 8) ||| a.setWidth 32).toNat =
      a.toNat+b.toNat*256+c.toNat*65536+d.toNat*16777216 := by
  have he : ((d.setWidth 32 <<< 24) ||| (c.setWidth 32 <<< 16) ||| (b.setWidth 32 <<< 8) ||| a.setWidth 32) =
      (((((d.setWidth 32 <<< 8) ||| c.setWidth 32) <<< 8) ||| b.setWidth 32) <<< 8) ||| a.setWidth 32 := by
    simp only [BitVec.shiftLeft_or_distrib, ← BitVec.shiftLeft_add]
  rw [he]
  have ha:=a.isLt;have hb:=b.isLt;have hc:=c.isLt;have hd:=d.isLt
  have ha' : (a.setWidth 32).toNat = a.toNat := by simp; omega
  have hb' : (b.setWidth 32).toNat = b.toNat := by simp; omega
  have hc' : (c.setWidth 32).toNat = c.toNat := by simp; omega
  have hd' : (d.setWidth 32).toNat = d.toNat := by simp; omega
  have hdc : ((d.setWidth 32 <<< 8) ||| c.setWidth 32).toNat = d.toNat*256+c.toNat := by
    rw [pack_step _ _ 8 (by rw [hc']; exact hc) (by rw [hd']; omega),hd',hc']
    rfl
  have hdcb : (((((d.setWidth 32 <<< 8) ||| c.setWidth 32) <<< 8) ||| b.setWidth 32)).toNat =
      (d.toNat*256+c.toNat)*256+b.toNat := by
    rw [pack_step _ _ 8 (by rw [hb']; exact hb) (by rw [hdc]; omega),hdc,hb']
    rfl
  rw [pack_step _ _ 8 (by rw [ha']; exact ha) (by rw [hdcb]; omega),hdcb,ha']
  omega

theorem pack2_value (hi lo : BitVec 32) :
    ((hi.setWidth 64 <<< 32) ||| lo.setWidth 64).toNat = lo.toNat+hi.toNat*4294967296 := by
  have hh:=hi.isLt;have hl:=lo.isLt
  have hh' : (hi.setWidth 64).toNat = hi.toNat := by simp; omega
  have hl' : (lo.setWidth 64).toNat = lo.toNat := by simp; omega
  rw [pack_step _ _ 32 (by rw [hl']; exact hl) (by rw [hh']; omega),hh',hl']
  omega
theorem ld8_value (input : Slice U8) (p : Usize) (hp : p.val+8 ≤ input.length) :
    slot.ld8 input p ⦃ fun r => r.val = w8 input p.val ⦄ := by
  change p.val + 8 ≤ input.val.length at hp
  rw [slot.ld8]
  have hmax := Slice.length_ineq input
  step*
  have hh : hi.bv = ((i2.bv.setWidth 32 <<< 24) ||| (i6.bv.setWidth 32 <<< 16) |||
      (i11.bv.setWidth 32 <<< 8) ||| i16.bv.setWidth 32) := by
    simp only [i14_post2,i9_post2,i4_post2,i8_post2,i13_post2] at hi_post2
    simpa only [i3_post,i7_post,i12_post,i17_post, UScalar.cast_bv_eq,BitVec.truncate_eq_setWidth,UScalarTy.numBits] using hi_post2
  have hl : lo.bv = ((i19.bv.setWidth 32 <<< 24) ||| (i23.bv.setWidth 32 <<< 16) |||
      (i28.bv.setWidth 32 <<< 8) ||| i32.bv.setWidth 32) := by
    simp only [i31_post2,i26_post2,i21_post2,i25_post2,i30_post2] at lo_post2
    simpa only [i20_post,i24_post,i29_post,i33_post, UScalar.cast_bv_eq,BitVec.truncate_eq_setWidth,UScalarTy.numBits] using lo_post2
  have hhval : hi.val=i16.val+i11.val*256+i6.val*65536+i2.val*16777216 := by
    change hi.bv.toNat = _
    rw [hh]
    exact pack4_value _ _ _ _
  have hlval : lo.val=i32.val+i28.val*256+i23.val*65536+i19.val*16777216 := by
    change lo.bv.toNat = _
    rw [hl]
    exact pack4_value _ _ _ _
  have h35 : i35.bv = hi.bv.setWidth 64 <<< 32 := by
    simpa only [i34_post,UScalar.cast_bv_eq,BitVec.truncate_eq_setWidth,UScalarTy.numBits] using i35_post2
  have h36 : i36.bv = lo.bv.setWidth 64 := by
    simpa only [UScalar.cast_bv_eq,BitVec.truncate_eq_setWidth,UScalarTy.numBits] using congrArg UScalar.bv i36_post
  have hv : (i35 ||| i36).val=lo.val+hi.val*4294967296 := by
    have h := pack2_value hi.bv lo.bv
    change (hi.bv.setWidth 64 <<< 32 ||| lo.bv.setWidth 64).toNat = _ at h
    change (i35.bv ||| i36.bv).toNat = _
    convert h using 1
    · exact congrArg BitVec.toNat (congrArg₂ (fun a b => a ||| b) h35 h36)
    · rfl
  rw [hv,hhval,hlval]
  unfold w8
  rw [getElem!_pos input.val p.val (by (first | omega | scalar_tac)),
    getElem!_pos input.val (p.val+1) (by (first | omega | scalar_tac)),getElem!_pos input.val (p.val+2) (by (first | omega | scalar_tac)),
    getElem!_pos input.val (p.val+3) (by (first | omega | scalar_tac)),getElem!_pos input.val (p.val+4) (by (first | omega | scalar_tac)),
    getElem!_pos input.val (p.val+5) (by (first | omega | scalar_tac)),getElem!_pos input.val (p.val+6) (by (first | omega | scalar_tac)),
    getElem!_pos input.val (p.val+7) (by (first | omega | scalar_tac))]
  (first | omega | scalar_tac)



theorem w8_prefix (input : Slice U8) (p q k : Nat) (hk : k ≤ 8)
    (h : w8 input p % 256^k = w8 input q % 256^k) :
    ∀ j, j < k → input.val[q+j]! = input.val[p+j]! := by
  unfold w8 at h
  have b0 := (input.val[p]!).hBounds
  have b1 := (input.val[p + 1]!).hBounds
  have b2 := (input.val[p + 2]!).hBounds
  have b3 := (input.val[p + 3]!).hBounds
  have b4 := (input.val[p + 4]!).hBounds
  have b5 := (input.val[p + 5]!).hBounds
  have b6 := (input.val[p + 6]!).hBounds
  have b7 := (input.val[p + 7]!).hBounds
  have c0 := (input.val[q]!).hBounds
  have c1 := (input.val[q + 1]!).hBounds
  have c2 := (input.val[q + 2]!).hBounds
  have c3 := (input.val[q + 3]!).hBounds
  have c4 := (input.val[q + 4]!).hBounds
  have c5 := (input.val[q + 5]!).hBounds
  have c6 := (input.val[q + 6]!).hBounds
  have c7 := (input.val[q + 7]!).hBounds
  simp only [Std.UScalarTy.numBits] at b0 b1 b2 b3 b4 b5 b6 b7 c0 c1 c2 c3 c4 c5 c6 c7
  interval_cases k <;> intro j hj
  all_goals apply UScalar.eq_imp
  all_goals interval_cases j
  all_goals try simp only [Nat.add_zero]
  all_goals omega

theorem lowbit_value (x : BitVec 64) (hx : x ≠ 0) :
    (x &&& -x).toNat = 2 ^ x.ctz.toNat := by
  have ht : x.ctz.toNat < 64 := by
    have h := (BitVec.ctz_lt_iff_ne_zero (x := x)).mpr hx
    simpa [BitVec.lt_def] using h
  have htrue := BitVec.getLsbD_true_ctz_of_ne_zero hx
  apply Nat.eq_of_testBit_eq
  intro i
  change (x &&& -x).getLsbD i = (2 ^ x.ctz.toNat).testBit i
  rw [BitVec.getLsbD_and, BitVec.getLsbD_neg, Nat.testBit_two_pow]
  by_cases hlt : i < x.ctz.toNat
  · have hf := BitVec.getLsbD_false_of_lt_ctz hlt
    simp [hf, show x.ctz.toNat ≠ i by omega]
  · by_cases he : i = x.ctz.toNat
    · subst i
      have hnone : ¬ ∃ j < x.ctz.toNat, x.getLsbD j = true := by
        rintro ⟨j,hj,hv⟩
        have hf := BitVec.getLsbD_false_of_lt_ctz hj
        simp [hf] at hv
      simp [htrue,ht,hnone]
    · have hex : ∃ j < i, x.getLsbD j = true := ⟨x.ctz.toNat,by omega,htrue⟩
      by_cases hi : i < 64
      · simp [hi,hex,show x.ctz.toNat ≠ i by omega]
      · have hf : x.getLsbD i = false := by simp [show 64 ≤ i by omega]
        simp [hf,show x.ctz.toNat ≠ i by omega]

theorem lowbit_nonzero (x : BitVec 64) (hx : x ≠ 0) : x &&& -x ≠ 0 := by
  intro h
  have hv := lowbit_value x hx
  rw [h] at hv
  change 0 = 2 ^ x.ctz.toNat at hv
  have hp : 0 < 2 ^ x.ctz.toNat := Nat.two_pow_pos _
  omega

theorem prefix_zero (x : BitVec 64) (b : Nat) (hb : b ≤ x.ctz.toNat) :
    x.toNat % 2^b = 0 := by
  apply Nat.eq_of_testBit_eq
  intro i
  rw [Nat.testBit_mod_two_pow]
  by_cases hi : i < b
  · have hf := BitVec.getLsbD_false_of_lt_ctz (x := x) (show i < x.ctz.toNat by omega)
    change x.toNat.testBit i = false at hf
    simpa [hi] using hf
  · simp [hi]

theorem fd_prefix (x : U64) (hx : x ≠ 0#u64) :
    slot.first_diff x ⦃ fun k => k.val ≤ 7 ∧ x.val % (256^k.val) = 0 ⦄ := by
  rw [slot.first_diff]
  step*
  have hilo : low.bv = x.bv &&& -x.bv := by
    have hi : i.bv = -x.bv := by
      rw [i_post]
      simp only [core.num.U64.wrapping_sub_bv_eq]
      exact BitVec.zero_sub _
    exact low_post2.trans (congrArg (fun v => x.bv &&& v) hi)
  have hxb : x.bv ≠ 0 := by
    intro h;apply hx;exact (U64.eq_equiv_bv_eq x 0#u64).mpr h
  have hln : low.bv ≠ 0 := by rw [hilo]; exact lowbit_nonzero x.bv hxb
  have hlnv : low.val ≠ 0 := by
    intro h;apply hln;apply BitVec.eq_of_toNat_eq;exact h
  have hlog : Nat.log 2 low.val < 64 :=
    Nat.log_lt_of_lt_pow' (by decide) low.bv.isLt
  have hi1v : i1.val = 64 - Nat.log 2 low.val - 1 := by
    rw [i1_post]
    simp only [core.num.U64.leading_zeros,BitVec.leadingZeros,if_neg hln]
    change (64 - Nat.log 2 low.val - 1) % 2^32 = _
    omega
  have hi2v : i2.val = Nat.log 2 low.val := by
    rw [i2_post]
    simp only [core.num.U32.wrapping_sub_val_eq]
    (first | omega | scalar_tac)
  have hk : (UScalar.cast UScalarTy.Usize i3).val = Nat.log 2 low.val / 8 := by
    rw [U32.cast_Usize_val_eq,i3_post,hi2v]
  rw [hk]
  have hbound : Nat.log 2 low.val / 8 ≤ 7 := by omega
  refine ⟨hbound,?_⟩
  have hv := lowbit_value x.bv hxb
  rw [← hilo] at hv
  change low.val = 2 ^ x.bv.ctz.toNat at hv
  have hlog_ctz : Nat.log 2 low.val = x.bv.ctz.toNat := by
    rw [hv]
    exact Nat.log_pow (by decide) _
  have hdiv : 8 * (Nat.log 2 low.val / 8) ≤ x.bv.ctz.toNat := by
    rw [hlog_ctz]
    exact Nat.mul_div_le _ _
  rw [show 256 = 2^8 by norm_num,← Nat.pow_mul]
  exact prefix_zero x.bv _ hdiv

theorem xor_word_prefix (input : Slice U8) (a b k : Nat) (x y : U64)
    (hx : x.val = w8 input a) (hy : y.val = w8 input b) (hk : k ≤ 8)
    (h : (x ^^^ y).val % 256^k = 0) : LZ77.Matches input a b k := by
  have hnat : (x.val ^^^ y.val) % 256^k = 0 := by
    simpa only [UScalar.val_xor] using h
  rw [hx,hy,show 256 = 2^8 by norm_num,←Nat.pow_mul,Nat.xor_mod_two_pow] at hnat
  have he := congrArg (fun z => z ^^^ (w8 input b % 2^(8*k))) hnat
  simp only [Nat.xor_assoc,Nat.xor_self,Nat.xor_zero,Nat.zero_xor] at he
  apply w8_prefix input a b k hk
  simpa only [show 256 = 2^8 by norm_num,←Nat.pow_mul] using he

end A2Research

open Aeneas Aeneas.Std Result ControlFlow Submission
open LZ77 (Matches)
set_option maxHeartbeats 10000000
set_option maxRecDepth 8192
namespace A2Research
namespace A2StepScope116
attribute [scoped step] A2Research.ld8_value
end A2StepScope116
namespace A2StepScope117
attribute [scoped step] A2Research.fd_prefix
end A2StepScope117
open scoped A2Research.A2StepScope116 A2Research.A2StepScope117

namespace A2StepScope118
@[scoped step]
theorem _root_.A2Research.fast_len_checked_loop (input : Slice U8) (a b cap l go it : Usize)
    (hab : a.val ≤ b.val) (hcap : b.val + cap.val + 8 ≤ input.length)
    (hl : l.val ≤ cap.val + 7) (hm : Matches input a.val b.val l.val)
    (hit : it.val ≤ 40) :
    slot.fast_len_loop input a b cap l go it ⦃ fun r => r.val ≤ cap.val+7 ∧ Matches input a.val b.val r.val ⦄ := by
  rw [slot.fast_len_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => 40 - s.2.2.val)
    (inv := fun s => s.1.val ≤ cap.val+7 ∧ Matches input a.val b.val s.1.val ∧ s.2.2.val ≤ 40)
  · rintro ⟨l,go,it⟩ ⟨hl,hm,hit⟩
    have hmax := Slice.length_ineq input
    have hsize : input.length < UScalar.size UScalarTy.Usize := by
      have hs : Usize.max + 1 = UScalar.size UScalarTy.Usize := by
        simp only [Usize.max,UScalar.size,UScalarTy.numBits,Usize.numBits]
        have hp : 0 < 2^System.Platform.numBits := Nat.two_pow_pos _
        omega
      change input.length ≤ Usize.max at hmax
      omega
    simp only [slot.fast_len_loop.body, lift, Array.to_slice_mut]
    step*
    all_goals try (first | omega | scalar_tac)
    by_cases hc : l < cap
    · have haddr1 : (core.num.Usize.wrapping_add a l).val = a.val+l.val := by
        rw [core.num.Usize.wrapping_add_val_eq]
        apply Nat.mod_eq_of_lt
        (first | omega | scalar_tac)
      have haddr2 : (core.num.Usize.wrapping_add b l).val = b.val+l.val := by
        rw [core.num.Usize.wrapping_add_val_eq]
        apply Nat.mod_eq_of_lt
        (first | omega | scalar_tac)
      simp only [if_pos hc]
      step with ld8_value as ⟨xa,hxa⟩
      all_goals try (rw [haddr1]; (first | omega | scalar_tac))
      step with ld8_value as ⟨xb,hxb⟩
      all_goals try (rw [haddr2]; (first | omega | scalar_tac))
      rw [haddr1] at hxa
      rw [haddr2] at hxb
      by_cases hx : xa ^^^ xb = 0#u64
      · simp only [if_pos hx]
        step*
        have hchunk : Matches input (a.val+l.val) (b.val+l.val) 8 :=
          xor_word_prefix input _ _ 8 xa xb hxa hxb (by omega) (by simp [hx])
        have hwr : (core.num.Usize.wrapping_add l 8#usize).val = l.val+8 := by
          rw [core.num.Usize.wrapping_add_val_eq]
          apply Nat.mod_eq_of_lt
          (first | omega | scalar_tac)
        rw [hwr]
        refine ⟨?_,Matches.a_append hm hchunk,?_,?_⟩ <;> (first | omega | scalar_tac)
      · simp only [if_neg hx]
        step with fd_prefix as ⟨k,hk,hmod⟩
        step*
        have hchunk : Matches input (a.val+l.val) (b.val+l.val) k.val :=
          xor_word_prefix input _ _ k.val xa xb hxa hxb (by omega) hmod
        have hwr : (core.num.Usize.wrapping_add l k).val = l.val+k.val := by
          rw [core.num.Usize.wrapping_add_val_eq]
          apply Nat.mod_eq_of_lt
          (first | omega | scalar_tac)
        rw [hwr]
        refine ⟨?_,Matches.a_append hm hchunk,?_,?_⟩ <;> (first | omega | scalar_tac)
    · simp only [if_neg hc]
      step*
  · exact ⟨hl,hm,hit⟩

end A2StepScope118
open scoped A2Research.A2StepScope118
namespace A2StepScope119
@[scoped step]
theorem _root_.A2Research.fast_len_checked (input : Slice U8) (a b cap : Usize)
    (hab : a.val ≤ b.val) (hcap : b.val + cap.val + 8 ≤ input.length) :
    slot.fast_len input a b cap ⦃ fun r => r.val ≤ cap.val ∧ Matches input a.val b.val r.val ⦄ := by
  rw [slot.fast_len]
  step with fast_len_checked_loop as ⟨l,hl,hm⟩
  all_goals try (first | omega | scalar_tac)
  all_goals try exact Matches.zero input a.val b.val
  step*
  all_goals refine ⟨by (first | omega | scalar_tac),Matches.mono hm (by (first | omega | scalar_tac))⟩

end A2StepScope119
open scoped A2Research.A2StepScope119
end A2Research

set_option maxHeartbeats 10000000
set_option maxRecDepth 8192
namespace A2Research

theorem usize_size_big : 2^32 ≤ UScalar.size UScalarTy.Usize := by
  simp only [UScalar.size,UScalarTy.numBits,Usize.numBits]
  rcases System.Platform.numBits_eq with h | h <;> rw [h] <;> decide

theorem usize_sub_nowrap (p c : Usize) (hc : c.val ≤ p.val) :
    (core.num.Usize.wrapping_sub p c).val = p.val-c.val := by
  rw [core.num.Usize.wrapping_sub_val_eq]
  have hp : p.val < UScalar.size UScalarTy.Usize := by
    simpa only [UScalar.size,UScalarTy.numBits] using p.hBounds
  have hh : c.val < UScalar.size UScalarTy.Usize := by omega
  have he : p.val+(UScalar.size UScalarTy.Usize-c.val) =
      UScalar.size UScalarTy.Usize+(p.val-c.val) := by omega
  rw [he]
  simp only [Nat.add_mod,Nat.mod_self,Nat.zero_add,Nat.mod_mod]
  exact Nat.mod_eq_of_lt (by omega)

theorem usize_pack (l d : Usize) (hl : l.val < 512) (hd : d.val ≤ 32768) :
    (l ||| core.num.Usize.wrapping_mul d 512#usize).val = l.val+512*d.val := by
  have hsize := usize_size_big
  have hmul : (core.num.Usize.wrapping_mul d 512#usize).val = d.val*512 := by
    rw [core.num.Usize.wrapping_mul_val_eq]
    apply Nat.mod_eq_of_lt
    (first | omega | scalar_tac)
  rw [UScalar.val_or,hmul,Nat.or_comm]
  have hor := Nat.two_pow_add_eq_or_of_lt (i := 9) (b := l.val) (by omega) d.val
  change 512*d.val+l.val = 512*d.val ||| l.val at hor
  rw [show d.val*512=512*d.val by omega,←hor]
  omega

def GoodEncoded (input : Slice U8) (p m : Nat) : Prop :=
  m=0 ∨ ∃ l d, m=l+512*d ∧ AMatchAt input p l d

 theorem GoodEncoded.zero (input : Slice U8) (p : Nat) : GoodEncoded input p 0 := Or.inl rfl

 theorem GoodEncoded.decode {input : Slice U8} {p m : Nat} (h : GoodEncoded input p m)
    (hm : m ≠ 0) : AMatchAt input p (m%512) ((m/512)%65536) := by
  rcases h with h | ⟨l,d,he,ha⟩
  · exact False.elim (hm h)
  · have hl : l<512 := by have h:=ha.2.1;omega
    have hd : d<65536 := by have h:=ha.2.2.2.2.1;omega
    have hlen : m%512=l := by rw [he];omega
    have hdist : (m/512)%65536=d := by rw [he];omega
    simpa only [hlen,hdist] using ha

theorem usize_add_one_safe (p n : Usize) (hp : p.val < n.val) :
    (core.num.Usize.wrapping_add p 1#usize).val = p.val+1 := by
  rw [core.num.Usize.wrapping_add_val_eq]
  apply Nat.mod_eq_of_lt
  have hn : n.val < UScalar.size UScalarTy.Usize := by
    simpa only [UScalar.size,UScalarTy.numBits] using n.hBounds
  (first | omega | scalar_tac)

theorem GoodEncoded.decode_parts {input : Slice U8} {p : Nat} {m l i d : Usize}
    (hg : GoodEncoded input p m.val) (hnonzero : m.val ≠ 0)
    (hl : l.val=m.val%512) (hi : i.val=m.val/512) (hd : d.val=i.val%65536) :
    AMatchAt input p l.val d.val := by
  have hm := GoodEncoded.decode hg hnonzero
  simpa only [hl,hd,hi] using hm

theorem GoodEncoded.wrapping_next {input : Slice U8} {p : Nat} (m : Usize)
    (hg : GoodEncoded input (p+1) m.val)
    (hx : AMatchAt input p (m.val%512+1) ((m.val/512)%65536)) :
    GoodEncoded input p (core.num.Usize.wrapping_add m 1#usize).val := by
  rcases hg with hz | ⟨l,d,he,hm⟩
  · have hh := hx.2.2.2.1
    rw [hz] at hh
    norm_num at hh
  · have hl : l<512 := by have hh:=hm.2.1;omega
    have hd : d<65536 := by have hh:=hm.2.2.2.2.1;omega
    have hml : m.val%512=l := by rw [he];omega
    have hmd : (m.val/512)%65536=d := by rw [he];omega
    have hsize := usize_size_big
    have hsum : m.val+1 < UScalar.size UScalarTy.Usize := by
      have hh:=hm.2.2.2.2.1
      omega
    have hnext : (core.num.Usize.wrapping_add m 1#usize).val=m.val+1 := by
      rw [core.num.Usize.wrapping_add_val_eq]
      change (m.val+1)%UScalar.size UScalarTy.Usize=m.val+1
      exact Nat.mod_eq_of_lt hsum
    refine Or.inr ⟨l+1,d,?_,?_⟩
    · rw [hnext,he];omega
    · simpa only [hml,hmd] using hx
theorem wrapping_one_match (input : Slice U8) (p : Nat) (l d : Usize)
    (hm : AMatchAt input p (l.val+1) d.val) :
    AMatchAt input p (core.num.Usize.wrapping_add l 1#usize).val d.val := by
  have hl : l.val+1 ≤ 258 := hm.2.1
  have hadd : (core.num.Usize.wrapping_add l 1#usize).val=l.val+1 := by
    rw [core.num.Usize.wrapping_add_val_eq]
    apply Nat.mod_eq_of_lt
    have hsize := usize_size_big
    (first | omega | scalar_tac)
  simpa only [hadd] using hm

attribute [irreducible] GoodEncoded

end A2Research

open Lean Elab Tactic
set_option maxHeartbeats 10000000
set_option maxRecDepth 8192
namespace A2Research
open scoped Submission.A2StepScope1 A2Research.A2StepScope119

theorem g_match_checked (input : Slice U8) (p : Usize) (cc cap : Usize)
    (hcap : cap.val ≤ 258) (hmargin : p.val+cap.val+8 ≤ input.length) :
    slot.g_match input p cc cap ⦃ fun r => GoodEncoded input p.val r.val ⦄ := by
  rw [slot.g_match]
  simp only [slot.G_M3,slot.G_WIN,slot.G_MAX3,ite_true]
  have hmax := Slice.length_ineq input
  step*
  all_goals repeat' (first
    | (exact GoodEncoded.zero input p.val)
    | (
        guard_target = GoodEncoded _ _ _
        guard_hyp d : Usize
        unfold GoodEncoded
        have hD : d.val = p.val-cc.val := by
          rw [d_post]
          exact usize_sub_nowrap p cc (by (first | omega | scalar_tac))
        have hA : p.val-d.val = cc.val := by (first | omega | scalar_tac)
        have hmat : AMatchAt input p.val l0.val d.val :=
          ⟨by (first | omega | scalar_tac),by (first | omega | scalar_tac),by (first | omega | scalar_tac),by (first | omega | scalar_tac),
           by (first | omega | scalar_tac),by (first | omega | scalar_tac),by simpa only [hA] using l0_post2⟩
        refine Or.inr ⟨l0.val,d.val,?_,hmat⟩
        have hp := usize_pack l0 d (by (first | omega | scalar_tac)) (by (first | omega | scalar_tac))
        first
        | (first
            | (simpa only [i_post] using hp)
            | (
                have he : l0=3#usize := by (first | omega | scalar_tac)
                simpa only [i_post,he] using hp))
        | (first
            | (simpa only [i_post] using hp)
            | (
                have he : l0=3#usize := by (first | omega | scalar_tac)
                simpa only [i_post,he] using hp)))
    | (intro hc; try step*)
    | (split <;> try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))


end A2Research

set_option maxHeartbeats 10000000
set_option maxRecDepth 8192
namespace A2Research
namespace A2StepScope120
attribute [scoped step] A2Research.g_match_checked
end A2StepScope120
open scoped Submission.A2StepScope1 A2Research.A2StepScope120

theorem g_eval_checked (input : Slice U8) (p : Usize) (v : U64) (c8 c4 cap : Usize)
    (hcap : cap.val ≤ 258) (hmargin : p.val+cap.val+8 ≤ input.length) :
    slot.g_eval input p v c8 c4 cap ⦃ fun r => GoodEncoded input p.val r.val ⦄ := by
  rw [slot.g_eval]
  simp only [slot.G_M3,slot.G_WIN,slot.G_MAX3,ite_true]
  have hmax := Slice.length_ineq input
  step* -grind -threadGrindState +scalarTac
  all_goals repeat' (first
    | assumption
    | (exact GoodEncoded.zero input p.val)
    | (exfalso; (first | omega | scalar_tac))
    | (intro hc; try step* -grind -threadGrindState +scalarTac)
    | (split <;> try step* -grind -threadGrindState +scalarTac)
    | (fail_if_no_progress (casesm* _ × _; try simp only []; try step* -grind -threadGrindState +scalarTac))
    | (apply spec_ite_cut <;> intro hc <;> try step* -grind -threadGrindState +scalarTac)
    | (step -grind -threadGrindState +scalarTac <;> try step* -grind -threadGrindState +scalarTac)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step* -grind -threadGrindState +scalarTac))
end A2Research

set_option maxHeartbeats 10000000
set_option maxRecDepth 8192
namespace A2Research
open scoped Submission.A2StepScope1 A2Research.A2StepScope119

theorem usize_prev (c p : Usize) (h : (core.num.Usize.wrapping_sub c 1#usize).val < p.val) :
    c.val = (core.num.Usize.wrapping_sub c 1#usize).val+1 := by
  by_cases hc : c.val=0
  · have hsize := usize_size_big
    have hp : p.val < UScalar.size UScalarTy.Usize := by
      simpa only [UScalar.size,UScalarTy.numBits] using p.hBounds
    rw [core.num.Usize.wrapping_sub_val_eq] at h
    have hone : (1#usize).val=1 := by (first | omega | scalar_tac)
    simp only [hc, Nat.zero_add, hone] at h
    have hh : UScalar.size UScalarTy.Usize-1 < UScalar.size UScalarTy.Usize := by omega
    rw [Nat.mod_eq_of_lt hh] at h
    omega
  · rw [usize_sub_nowrap c 1#usize (by (first | omega | scalar_tac))]
    (first | omega | scalar_tac)

theorem g3_cand3_checked (input : Slice U8) (p : Usize) (v : U64) (c3 : Usize)
    (hmargin : p.val+11 ≤ input.length) :
    slot.g3_cand3 input p v c3 ⦃ fun r => GoodEncoded input p.val r.val ⦄ := by
  rw [slot.g3_cand3]
  simp only [slot.G_MAX3]
  have hmax := Slice.length_ineq input
  step*
  repeat (first
    | (intro hc; try step*)
    | (split <;> try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals try exact GoodEncoded.zero input p.val
  all_goals
  unfold GoodEncoded
  have hcc : c3.val = cc.val+1 := by
    rw [cc_post]
    exact usize_prev c3 p (by (first | omega | scalar_tac))
  have hC : c3.val ≤ p.val := by (first | omega | scalar_tac)
  have hI : i.val = p.val-c3.val := by
    rw [i_post]
    exact usize_sub_nowrap p c3 hC
  have hD : i4.val = p.val-cc.val := by
    rw [i4_post]
    exact usize_sub_nowrap p cc (by (first | omega | scalar_tac))
  have hA : p.val-i4.val = cc.val := by (first | omega | scalar_tac)
  have hE : i3.val = 3 := by (first | omega | scalar_tac)
  have hmat : AMatchAt input p.val 3 i4.val :=
    ⟨by (first | omega | scalar_tac),by (first | omega | scalar_tac),by (first | omega | scalar_tac),by (first | omega | scalar_tac),
     by (first | omega | scalar_tac),by (first | omega | scalar_tac),by simpa only [hA,hE] using i3_post2⟩
  refine Or.inr ⟨3,i4.val,?_,hmat⟩
  have hp := usize_pack 3#usize i4 (by (first | omega | scalar_tac)) (by (first | omega | scalar_tac))
  simpa only [i5_post,show (3#usize).val=3 by (first | omega | scalar_tac)] using hp

end A2Research

set_option maxHeartbeats 10000000
set_option maxRecDepth 8192
namespace A2Research
namespace A2StepScope121
attribute [scoped step] A2Research.g3_cand3_checked
end A2StepScope121
open scoped Submission.A2StepScope1 A2Research.A2StepScope120 A2Research.A2StepScope121

theorem g3_eval_checked (input : Slice U8) (p : Usize) (v : U64) (c8 c4 c3 cap : Usize)
    (h3 : p.val+11 ≤ input.length) (hcap : cap.val ≤ 258) (hmargin : p.val+cap.val+8 ≤ input.length) :
    slot.g3_eval input p v c8 c4 c3 cap ⦃ fun r => GoodEncoded input p.val r.val ⦄ := by
  rw [slot.g3_eval]
  simp only [slot.G_M3,slot.G_WIN,slot.G_MAX3,ite_true]
  have hmax := Slice.length_ineq input
  step*
  all_goals repeat' (first
    | assumption
    | (exact GoodEncoded.zero input p.val)
    | (exfalso; (first | omega | scalar_tac))
    | (intro hc; try step*)
    | (split <;> try step*)
    | (casesm* _ × _; try simp only []; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (step <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))

end A2Research

set_option maxHeartbeats 10000000
set_option maxRecDepth 8192
namespace A2Research
open scoped Submission.A2StepScope1 A2Research.A2StepScope120

open scoped A2FastCut in
theorem g_lazy_eval_checked (input : Slice U8) (p : Usize) (v : U64) (c8 c4 cap min : Usize)
    (hcap : cap.val ≤ 258) (hmargin : p.val+cap.val+8 ≤ input.length) :
    slot.g_lazy_eval input p v c8 c4 cap min ⦃ fun r => GoodEncoded input p.val r.val ⦄ := by
  rw [slot.g_lazy_eval]
  simp only [slot.G_M3,slot.G_WIN,slot.G_MAX3,ite_true]
  have hmax := Slice.length_ineq input
  step* -grind -threadGrindState +scalarTac
  all_goals repeat' (first
    | assumption
    | (exact GoodEncoded.zero input p.val)
    | (exfalso; (first | omega | scalar_tac))
    | (intro hc; try step* -grind -threadGrindState +scalarTac)
    | (split <;> try step* -grind -threadGrindState +scalarTac)
    | (fail_if_no_progress (casesm* _ × _; try simp only []; try step* -grind -threadGrindState +scalarTac))
    | (apply spec_ite_cut <;> intro hc <;> try step* -grind -threadGrindState +scalarTac)
    | (step -grind -threadGrindState +scalarTac <;> try step* -grind -threadGrindState +scalarTac)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step* -grind -threadGrindState +scalarTac))
end A2Research

set_option maxHeartbeats 10000000
set_option maxRecDepth 8192
namespace A2Research
open scoped Submission.A2StepScope1 A2Research.A2StepScope120 A2Research.A2StepScope121

open scoped A2FastCut in
theorem g3_lazy_eval_checked (input : Slice U8) (p : Usize) (v : U64) (c8 c4 c3 cap min : Usize)
    (h3 : p.val+11 ≤ input.length) (hcap : cap.val ≤ 258) (hmargin : p.val+cap.val+8 ≤ input.length) :
    slot.g3_lazy_eval input p v c8 c4 c3 cap min ⦃ fun r => GoodEncoded input p.val r.val ⦄ := by
  rw [slot.g3_lazy_eval]
  simp only [slot.G_M3,slot.G_WIN,slot.G_MAX3,ite_true]
  have hmax := Slice.length_ineq input
  step* -grind -threadGrindState +scalarTac
  all_goals repeat' (first
    | assumption
    | (exact GoodEncoded.zero input p.val)
    | (exfalso; (first | omega | scalar_tac))
    | (intro hc; try step* -grind -threadGrindState +scalarTac)
    | (split <;> try step* -grind -threadGrindState +scalarTac)
    | (fail_if_no_progress (casesm* _ × _; try simp only []; try step* -grind -threadGrindState +scalarTac))
    | (apply spec_ite_cut <;> intro hc <;> try step* -grind -threadGrindState +scalarTac)
    | (step -grind -threadGrindState +scalarTac <;> try step* -grind -threadGrindState +scalarTac)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step* -grind -threadGrindState +scalarTac))
end A2Research

set_option maxHeartbeats 10000000
set_option maxRecDepth 8192
namespace A2Research
open scoped Submission.A2StepScope1 A2Research.A2StepScope120

open scoped A2FastCut in
theorem gh_eval_checked (input : Slice U8) (p : Usize) (v : U64) (c8 c4 cap : Usize)
    (hcap : cap.val ≤ 258) (hmargin : p.val+cap.val+8 ≤ input.length) :
    slot.gh_eval input p v c8 c4 cap ⦃ fun r => GoodEncoded input p.val r.val ⦄ := by
  rw [slot.gh_eval]
  simp only [slot.G_M3,slot.G_WIN,slot.G_MAX3,ite_true]
  have hmax := Slice.length_ineq input
  step*
  all_goals repeat' (first
    | assumption
    | (exact GoodEncoded.zero input p.val)
    | (exfalso; (first | omega | scalar_tac))
    | (intro hc; try step*)
    | (split <;> try step*)
    | (casesm* _ × _; try simp only []; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (step <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))

end A2Research

set_option maxHeartbeats 10000000
set_option maxRecDepth 8192
namespace A2Research
namespace A2StepScope122
attribute [scoped step] A2Research.g_eval_checked
end A2StepScope122
namespace A2StepScope123
attribute [scoped step] A2Research.g_lazy_eval_checked
end A2StepScope123
open scoped Submission.A2StepScope1 A2Research.A2StepScope122 A2Research.A2StepScope123 Submission.A2StepScope95 Submission.A2StepScope96 Submission.A2StepScope97 Submission.A2StepScope98 Submission.A2StepScope99 Submission.A2StepScope100

namespace A2StepScope124
@[scoped step]
theorem _root_.A2Research.cap_ite_checked (rem : Usize) :
    (if rem < 258#usize then ok rem else ok 258#usize) ⦃ fun r => r.val ≤ 258 ∧ r.val ≤ rem.val ⦄ := by
  split <;> simp only [Std.WP.spec_ok] <;> constructor <;> (first | omega | scalar_tac)

end A2StepScope124
open scoped A2Research.A2StepScope124
theorem g_probe_checked (input : Slice U8) (t4 t8 : Array U32 65536#usize) (p : Usize) :
    slot.g_probe input t4 t8 p ⦃ fun r => GoodEncoded input p.val r.1.val ⦄ := by
  rw [slot.g_probe]
  have hmax := Slice.length_ineq input
  step* -grind -threadGrindState +scalarTac
  all_goals repeat (first
    | (fail_if_no_progress (casesm* _ × _; try simp only []; try step* -grind -threadGrindState +scalarTac))
    | assumption
    | (exact GoodEncoded.zero input p.val)
    | (intro hc; try step* -grind -threadGrindState +scalarTac)
    | (split <;> try step* -grind -threadGrindState +scalarTac)
    | (apply spec_ite_cut <;> intro hc <;> try step* -grind -threadGrindState +scalarTac)
    | (step -grind -threadGrindState +scalarTac <;> try step* -grind -threadGrindState +scalarTac)
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step* -grind -threadGrindState +scalarTac))

namespace A2StepScope125
attribute [scoped step] A2Research.g_probe_checked
end A2StepScope125
open scoped A2Research.A2StepScope125

theorem g_lazy_checked (input : Slice U8) (t4 t8 : Array U32 65536#usize) (q pre want min : Usize) :
    slot.g_lazy input t4 t8 q pre want min ⦃ fun r => GoodEncoded input q.val r.1.val ⦄ := by
  rw [slot.g_lazy]
  have hmax := Slice.length_ineq input
  step* -grind -threadGrindState +scalarTac
  all_goals repeat (first
    | (fail_if_no_progress (casesm* _ × _; try simp only []; try step* -grind -threadGrindState +scalarTac))
    | assumption
    | (exact GoodEncoded.zero input q.val)
    | (intro hc; try step* -grind -threadGrindState +scalarTac)
    | (split <;> try step* -grind -threadGrindState +scalarTac)
    | (apply spec_ite_cut <;> intro hc <;> try step* -grind -threadGrindState +scalarTac)
    | (step -grind -threadGrindState +scalarTac <;> try step* -grind -threadGrindState +scalarTac)
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step* -grind -threadGrindState +scalarTac))
end A2Research

set_option maxHeartbeats 10000000
set_option maxRecDepth 8192
namespace A2Research
open scoped Submission.A2StepScope1 A2Research.A2StepScope122 Submission.A2StepScope95 Submission.A2StepScope96 Submission.A2StepScope97 Submission.A2StepScope98 Submission.A2StepScope99 Submission.A2StepScope100 Submission.A2StepScope93 Submission.A2StepScope94 A2Research.A2StepScope124

theorem g_scan_loop_checked (input : Slice U8) (t4 t8 : Array U32 65536#usize)
    (acc : U64) (n p k m : Usize) (v : U64) (e : Usize × Usize)
    (p0 : Nat) (hn : n.val=input.length) (hn16 : 16 ≤ n.val)
    (hk : k.val ≤ p.val) (hp0 : p0 ≤ p.val) (hp : p.val ≤ n.val)
    (hm : GoodEncoded input p.val m.val) :
    slot.g_scan_loop input t4 t8 acc n p k m v e ⦃ fun r =>
      p0 ≤ r.2.2.1.val ∧ r.2.2.1.val ≤ n.val ∧ GoodEncoded input r.2.2.1.val r.2.2.2.1.val ⦄ := by
  rw [slot.g_scan_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => n.val-s.2.2.1.val)
    (inv := fun s => s.2.2.2.1.val ≤ s.2.2.1.val ∧ p0 ≤ s.2.2.1.val ∧
      s.2.2.1.val ≤ n.val ∧ GoodEncoded input s.2.2.1.val s.2.2.2.2.1.val)
  · rintro ⟨t4,t8,p,k,m,v,e⟩ ⟨hk,hp0,hp,hm⟩
    simp only at hk hp0 hp hm
    have hmax := Slice.length_ineq input
    simp only [slot.g_scan_loop.body, lift, Array.to_slice_mut]
    step* -grind -threadGrindState +scalarTac
    all_goals repeat (first
      | (fail_if_no_progress (casesm* _ × _; try simp only []; try step* -grind -threadGrindState +scalarTac))
      | (intro hc; try step* -grind -threadGrindState +scalarTac)
      | (split <;> try step* -grind -threadGrindState +scalarTac)
      | (apply spec_ite_cut <;> intro hc <;> try step* -grind -threadGrindState +scalarTac)
      | (step -grind -threadGrindState +scalarTac <;> try step* -grind -threadGrindState +scalarTac)
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step* -grind -threadGrindState +scalarTac))
    all_goals try exact ⟨hp0,hp,hm⟩
    all_goals try exact ⟨hp0,hp,by assumption⟩
    all_goals try (
      refine ⟨by (first | omega | scalar_tac),by (first | omega | scalar_tac),by (first | omega | scalar_tac),?_,by (first | omega | scalar_tac)⟩
      have he : m1.val=0 := by (first | omega | scalar_tac)
      rw [he]
      exact GoodEncoded.zero input _)
  · exact ⟨hk,hp0,hp,hm⟩


namespace A2StepScope126
@[scoped step]
theorem _root_.A2Research.g_scan_loop_start_checked (input : Slice U8) (t4 t8 : Array U32 65536#usize)
    (acc : U64) (n p k m : Usize) (v : U64) (e : Usize × Usize)
    (hn : n.val=input.length) (hn16 : 16 ≤ n.val)
    (hk : k.val ≤ p.val) (hp : p.val ≤ n.val)
    (hm : GoodEncoded input p.val m.val) :
    slot.g_scan_loop input t4 t8 acc n p k m v e ⦃ fun r =>
      p.val ≤ r.2.2.1.val ∧ r.2.2.1.val ≤ n.val ∧ GoodEncoded input r.2.2.1.val r.2.2.2.1.val ⦄ := by
  exact g_scan_loop_checked input t4 t8 acc n p k m v e p.val hn hn16 hk (le_refl _) hp hm

end A2StepScope126
open scoped A2Research.A2StepScope126
theorem g_scan_checked (input : Slice U8) (t4 t8 : Array U32 65536#usize)
    (pos : Usize) (acc : U64) (carry cpre : Usize)
    (hp : pos.val ≤ input.length) (hc : GoodEncoded input pos.val carry.val) :
    slot.g_scan input t4 t8 pos acc carry cpre ⦃ fun r =>
      pos.val ≤ r.1.1.val ∧ r.1.1.val ≤ input.length ∧ GoodEncoded input r.1.1.val r.1.2.1.val ⦄ := by
  rw [slot.g_scan]
  have hmax := Slice.length_ineq input
  step* -grind -threadGrindState +scalarTac
  all_goals repeat (first
    | (fail_if_no_progress (casesm* _ × _; try simp only []; try step* -grind -threadGrindState +scalarTac))
    | (intro h; try step* -grind -threadGrindState +scalarTac)
    | (split <;> try step* -grind -threadGrindState +scalarTac)
    | (apply spec_ite_cut <;> intro h <;> try step* -grind -threadGrindState +scalarTac)
    | (step -grind -threadGrindState +scalarTac <;> try step* -grind -threadGrindState +scalarTac)
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step* -grind -threadGrindState +scalarTac))
  all_goals try exact GoodEncoded.zero input _
  all_goals try exact ⟨by (first | omega | scalar_tac),by (first | omega | scalar_tac),hc⟩
  all_goals try exact ⟨by (first | omega | scalar_tac),by (first | omega | scalar_tac),GoodEncoded.zero input _⟩
  all_goals try exact ⟨by (first | omega | scalar_tac),by (first | omega | scalar_tac),by assumption⟩
end A2Research

set_option maxHeartbeats 10000000
set_option maxRecDepth 8192
namespace A2Research
namespace A2StepScope127
attribute [scoped step] A2Research.g3_eval_checked
end A2StepScope127
namespace A2StepScope128
attribute [scoped step] A2Research.g3_lazy_eval_checked
end A2StepScope128
open scoped Submission.A2StepScope1 A2Research.A2StepScope127 A2Research.A2StepScope128 A2Research.A2StepScope124 Submission.A2StepScope95 Submission.A2StepScope96 Submission.A2StepScope99 Submission.A2StepScope100 Submission.A2StepScope104 Submission.A2StepScope105

theorem g3_probe_checked (input : Slice U8) (t4 t8 t3 : Array U32 65536#usize) (p m3 : Usize) :
    slot.g3_probe input t4 t8 t3 p m3 ⦃ fun r => GoodEncoded input p.val r.1.val ⦄ := by
  rw [slot.g3_probe]
  have hmax := Slice.length_ineq input
  step* -grind -threadGrindState +scalarTac
  all_goals repeat (first
    | (fail_if_no_progress (casesm* _ × _; try simp only []; try step* -grind -threadGrindState +scalarTac))
    | assumption
    | (exact GoodEncoded.zero input p.val)
    | (intro hc; try step* -grind -threadGrindState +scalarTac)
    | (split <;> try step* -grind -threadGrindState +scalarTac)
    | (apply spec_ite_cut <;> intro hc <;> try step* -grind -threadGrindState +scalarTac)
    | (step -grind -threadGrindState +scalarTac <;> try step* -grind -threadGrindState +scalarTac)
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step* -grind -threadGrindState +scalarTac))

namespace A2StepScope129
attribute [scoped step] A2Research.g3_probe_checked
end A2StepScope129
open scoped A2Research.A2StepScope129

theorem g3_lazy_checked (input : Slice U8) (t4 t8 t3 : Array U32 65536#usize) (q pre m3 want min : Usize) :
    slot.g3_lazy input t4 t8 t3 q pre m3 want min ⦃ fun r => GoodEncoded input q.val r.1.val ⦄ := by
  rw [slot.g3_lazy]
  have hmax := Slice.length_ineq input
  step* -grind -threadGrindState +scalarTac
  all_goals repeat (first
    | (fail_if_no_progress (casesm* _ × _; try simp only []; try step* -grind -threadGrindState +scalarTac))
    | assumption
    | (exact GoodEncoded.zero input q.val)
    | (intro hc; try step* -grind -threadGrindState +scalarTac)
    | (split <;> try step* -grind -threadGrindState +scalarTac)
    | (apply spec_ite_cut <;> intro hc <;> try step* -grind -threadGrindState +scalarTac)
    | (step -grind -threadGrindState +scalarTac <;> try step* -grind -threadGrindState +scalarTac)
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step* -grind -threadGrindState +scalarTac))
end A2Research

set_option maxHeartbeats 10000000
set_option maxRecDepth 8192
namespace A2Research
open scoped Submission.A2StepScope1 A2Research.A2StepScope127 Submission.A2StepScope95 Submission.A2StepScope96 Submission.A2StepScope97 Submission.A2StepScope98 Submission.A2StepScope99 Submission.A2StepScope100 Submission.A2StepScope104 Submission.A2StepScope105 Submission.A2StepScope93 Submission.A2StepScope94 A2Research.A2StepScope124

namespace A2StepScope130
@[scoped step]
theorem _root_.A2Research.g3_cache_checked (t3 : Array U32 65536#usize) (v : U64) (p m3 : Usize) :
    (if m3 = 1#usize then do
      let h ← slot.g3_h3 v
      let (c,t) ← slot.g3_put3 t3 h p
      ok (t,c)
    else ok (t3,0#usize)) ⦃ fun _ => True ⦄ := by
  split <;> step*

end A2StepScope130
open scoped A2Research.A2StepScope130
theorem g3_scan_loop_checked (input : Slice U8) (t4 t8 t3 : Array U32 65536#usize)
    (acc : U64) (m3 n p k m : Usize) (v : U64) (h4 h8 : Usize) (e : Usize × Usize) (pre : Usize)
    (p0 : Nat) (hn : n.val=input.length) (hn16 : 16 ≤ n.val)
    (hk : k.val ≤ p.val) (hp0 : p0 ≤ p.val) (hp : p.val ≤ n.val)
    (hm : GoodEncoded input p.val m.val) :
    slot.g3_scan_loop input t4 t8 t3 acc m3 n p k m v h4 h8 e pre ⦃ fun r =>
      p0 ≤ r.2.2.2.1.val ∧ r.2.2.2.1.val ≤ n.val ∧ GoodEncoded input r.2.2.2.1.val r.2.2.2.2.1.val ⦄ := by
  rw [slot.g3_scan_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => n.val-s.2.2.2.1.val)
    (inv := fun s => s.2.2.2.2.1.val ≤ s.2.2.2.1.val ∧ p0 ≤ s.2.2.2.1.val ∧
      s.2.2.2.1.val ≤ n.val ∧ GoodEncoded input s.2.2.2.1.val s.2.2.2.2.2.1.val)
  · rintro ⟨t4,t8,t3,p,k,m,v,h4,h8,e,pre⟩ ⟨hk,hp0,hp,hm⟩
    simp only at hk hp0 hp hm
    have hmax := Slice.length_ineq input
    simp only [slot.g3_scan_loop.body, lift, Array.to_slice_mut]
    step* -grind -threadGrindState +scalarTac
    all_goals repeat (first
      | (fail_if_no_progress (casesm* _ × _; try simp only []; try step* -grind -threadGrindState +scalarTac))
      | (intro hc; try step* -grind -threadGrindState +scalarTac)
      | (split <;> try step* -grind -threadGrindState +scalarTac)
      | (apply spec_ite_cut <;> intro hc <;> try step* -grind -threadGrindState +scalarTac)
      | (step -grind -threadGrindState +scalarTac <;> try step* -grind -threadGrindState +scalarTac)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step* -grind -threadGrindState +scalarTac))
    all_goals try exact ⟨hp0,hp,hm⟩
    all_goals try exact ⟨hp0,hp,by assumption⟩
    all_goals try (
      refine ⟨by (first | omega | scalar_tac),by (first | omega | scalar_tac),by (first | omega | scalar_tac),?_,by (first | omega | scalar_tac)⟩
      have he : m1.val=0 := by (first | omega | scalar_tac)
      rw [he]
      exact GoodEncoded.zero input _)
  · exact ⟨hk,hp0,hp,hm⟩


namespace A2StepScope131
@[scoped step]
theorem _root_.A2Research.g3_scan_loop_start_checked (input : Slice U8) (t4 t8 t3 : Array U32 65536#usize)
    (acc : U64) (m3 n p k m : Usize) (v : U64) (h4 h8 : Usize) (e : Usize × Usize) (pre : Usize)
    (hn : n.val=input.length) (hn16 : 16 ≤ n.val)
    (hk : k.val ≤ p.val) (hp : p.val ≤ n.val)
    (hm : GoodEncoded input p.val m.val) :
    slot.g3_scan_loop input t4 t8 t3 acc m3 n p k m v h4 h8 e pre ⦃ fun r =>
      p.val ≤ r.2.2.2.1.val ∧ r.2.2.2.1.val ≤ n.val ∧ GoodEncoded input r.2.2.2.1.val r.2.2.2.2.1.val ⦄ := by
  exact g3_scan_loop_checked input t4 t8 t3 acc m3 n p k m v h4 h8 e pre p.val hn hn16 hk (le_refl _) hp hm

end A2StepScope131
open scoped A2Research.A2StepScope131
theorem g3_scan_checked (input : Slice U8) (t4 t8 t3 : Array U32 65536#usize)
    (pos : Usize) (acc : U64) (m3 carry cpre : Usize)
    (hp : pos.val ≤ input.length) (hc : GoodEncoded input pos.val carry.val) :
    slot.g3_scan input t4 t8 t3 pos acc m3 carry cpre ⦃ fun r =>
      pos.val ≤ r.1.1.val ∧ r.1.1.val ≤ input.length ∧ GoodEncoded input r.1.1.val r.1.2.1.val ⦄ := by
  rw [slot.g3_scan]
  have hmax := Slice.length_ineq input
  step* -grind -threadGrindState +scalarTac
  all_goals repeat (first
    | (fail_if_no_progress (casesm* _ × _; try simp only []; try step* -grind -threadGrindState +scalarTac))
    | (intro h; try step* -grind -threadGrindState +scalarTac)
    | (split <;> try step* -grind -threadGrindState +scalarTac)
    | (apply spec_ite_cut <;> intro h <;> try step* -grind -threadGrindState +scalarTac)
    | (step -grind -threadGrindState +scalarTac <;> try step* -grind -threadGrindState +scalarTac)
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step* -grind -threadGrindState +scalarTac))
  all_goals try exact GoodEncoded.zero input _
  all_goals try exact ⟨by (first | omega | scalar_tac),by (first | omega | scalar_tac),hc⟩
  all_goals try exact ⟨by (first | omega | scalar_tac),by (first | omega | scalar_tac),GoodEncoded.zero input _⟩
  all_goals try exact ⟨by (first | omega | scalar_tac),by (first | omega | scalar_tac),by assumption⟩
end A2Research

set_option maxHeartbeats 10000000
set_option maxRecDepth 8192
namespace A2Research
namespace A2StepScope132
attribute [scoped step] A2Research.gh_eval_checked
end A2StepScope132
open scoped Submission.A2StepScope1 A2Research.A2StepScope132 Submission.A2StepScope109 Submission.A2StepScope110 Submission.A2StepScope111 Submission.A2StepScope112

theorem gh_probe_checked (input : Slice U8) (t4 t8 : Array U32 65536#usize) (p : Usize) :
    slot.gh_probe input t4 t8 p ⦃ fun r => GoodEncoded input p.val r.1.val ⦄ := by
  rw [slot.gh_probe]
  have hmax := Slice.length_ineq input
  step* -grind -threadGrindState +scalarTac
  all_goals repeat (first
    | (fail_if_no_progress (casesm* _ × _; try simp only []; try step* -grind -threadGrindState +scalarTac))
    | assumption
    | (exact GoodEncoded.zero input p.val)
    | (intro hc; try step* -grind -threadGrindState +scalarTac)
    | (split <;> try step* -grind -threadGrindState +scalarTac)
    | (apply spec_ite_cut <;> intro hc <;> try step* -grind -threadGrindState +scalarTac)
    | (step -grind -threadGrindState +scalarTac <;> try step* -grind -threadGrindState +scalarTac)
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step* -grind -threadGrindState +scalarTac))

namespace A2StepScope133
attribute [scoped step] A2Research.gh_probe_checked
end A2StepScope133
open scoped A2Research.A2StepScope133

theorem gh_lazy_checked (input : Slice U8) (t4 t8 : Array U32 65536#usize) (q pre want : Usize) :
    slot.gh_lazy input t4 t8 q pre want ⦃ fun r => GoodEncoded input q.val r.1.val ⦄ := by
  rw [slot.gh_lazy]
  have hmax := Slice.length_ineq input
  step* -grind -threadGrindState +scalarTac
  all_goals repeat (first
    | (fail_if_no_progress (casesm* _ × _; try simp only []; try step* -grind -threadGrindState +scalarTac))
    | assumption
    | (exact GoodEncoded.zero input q.val)
    | (intro hc; try step* -grind -threadGrindState +scalarTac)
    | (split <;> try step* -grind -threadGrindState +scalarTac)
    | (apply spec_ite_cut <;> intro hc <;> try step* -grind -threadGrindState +scalarTac)
    | (step -grind -threadGrindState +scalarTac <;> try step* -grind -threadGrindState +scalarTac)
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step* -grind -threadGrindState +scalarTac))
end A2Research

set_option maxHeartbeats 10000000
set_option maxRecDepth 8192
namespace A2Research
open scoped Submission.A2StepScope1 A2Research.A2StepScope132 Submission.A2StepScope109 Submission.A2StepScope110 Submission.A2StepScope111 Submission.A2StepScope112 Submission.A2StepScope93 Submission.A2StepScope94 A2Research.A2StepScope124

theorem gh_scan_loop_checked (input : Slice U8) (t4 t8 : Array U32 65536#usize)
    (acc : U64) (n p k m : Usize) (v : U64) (h4 h8 : Usize) (e : Usize × Usize) (pre : Usize)
    (p0 : Nat) (hn : n.val=input.length) (hn16 : 16 ≤ n.val)
    (hk : k.val ≤ p.val) (hp0 : p0 ≤ p.val) (hp : p.val ≤ n.val)
    (hm : GoodEncoded input p.val m.val) :
    slot.gh_scan_loop input t4 t8 acc n p k m v h4 h8 e pre ⦃ fun r =>
      p0 ≤ r.2.2.1.val ∧ r.2.2.1.val ≤ n.val ∧ GoodEncoded input r.2.2.1.val r.2.2.2.1.val ⦄ := by
  rw [slot.gh_scan_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => n.val-s.2.2.1.val)
    (inv := fun s => s.2.2.2.1.val ≤ s.2.2.1.val ∧ p0 ≤ s.2.2.1.val ∧
      s.2.2.1.val ≤ n.val ∧ GoodEncoded input s.2.2.1.val s.2.2.2.2.1.val)
  · rintro ⟨t4,t8,p,k,m,v,h4,h8,e,pre⟩ ⟨hk,hp0,hp,hm⟩
    simp only at hk hp0 hp hm
    have hmax := Slice.length_ineq input
    simp only [slot.gh_scan_loop.body, lift, Array.to_slice_mut]
    step* -grind -threadGrindState +scalarTac
    all_goals repeat (first
      | (fail_if_no_progress (casesm* _ × _; try simp only []; try step* -grind -threadGrindState +scalarTac))
      | (intro hc; try step* -grind -threadGrindState +scalarTac)
      | (split <;> try step* -grind -threadGrindState +scalarTac)
      | (apply spec_ite_cut <;> intro hc <;> try step* -grind -threadGrindState +scalarTac)
      | (step -grind -threadGrindState +scalarTac <;> try step* -grind -threadGrindState +scalarTac)
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step* -grind -threadGrindState +scalarTac))
    all_goals try exact ⟨hp0,hp,hm⟩
    all_goals try exact ⟨hp0,hp,by assumption⟩
    all_goals try (
      refine ⟨by (first | omega | scalar_tac),by (first | omega | scalar_tac),by (first | omega | scalar_tac),?_,by (first | omega | scalar_tac)⟩
      have he : m1.val=0 := by (first | omega | scalar_tac)
      rw [he]
      exact GoodEncoded.zero input _)
  · exact ⟨hk,hp0,hp,hm⟩


namespace A2StepScope134
@[scoped step]
theorem _root_.A2Research.gh_scan_loop_start_checked (input : Slice U8) (t4 t8 : Array U32 65536#usize)
    (acc : U64) (n p k m : Usize) (v : U64) (h4 h8 : Usize) (e : Usize × Usize) (pre : Usize)
    (hn : n.val=input.length) (hn16 : 16 ≤ n.val)
    (hk : k.val ≤ p.val) (hp : p.val ≤ n.val)
    (hm : GoodEncoded input p.val m.val) :
    slot.gh_scan_loop input t4 t8 acc n p k m v h4 h8 e pre ⦃ fun r =>
      p.val ≤ r.2.2.1.val ∧ r.2.2.1.val ≤ n.val ∧ GoodEncoded input r.2.2.1.val r.2.2.2.1.val ⦄ := by
  exact gh_scan_loop_checked input t4 t8 acc n p k m v h4 h8 e pre p.val hn hn16 hk (le_refl _) hp hm

end A2StepScope134
open scoped A2Research.A2StepScope134
theorem gh_scan_checked (input : Slice U8) (t4 t8 : Array U32 65536#usize)
    (pos : Usize) (acc : U64) (carry cpre : Usize)
    (hp : pos.val ≤ input.length) (hc : GoodEncoded input pos.val carry.val) :
    slot.gh_scan input t4 t8 pos acc carry cpre ⦃ fun r =>
      pos.val ≤ r.1.1.val ∧ r.1.1.val ≤ input.length ∧ GoodEncoded input r.1.1.val r.1.2.1.val ⦄ := by
  rw [slot.gh_scan]
  have hmax := Slice.length_ineq input
  step* -grind -threadGrindState +scalarTac
  all_goals repeat (first
    | (fail_if_no_progress (casesm* _ × _; try simp only []; try step* -grind -threadGrindState +scalarTac))
    | (intro h; try step* -grind -threadGrindState +scalarTac)
    | (split <;> try step* -grind -threadGrindState +scalarTac)
    | (apply spec_ite_cut <;> intro h <;> try step* -grind -threadGrindState +scalarTac)
    | (step -grind -threadGrindState +scalarTac <;> try step* -grind -threadGrindState +scalarTac)
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step* -grind -threadGrindState +scalarTac))
  all_goals try exact GoodEncoded.zero input _
  all_goals try exact ⟨by (first | omega | scalar_tac),by (first | omega | scalar_tac),hc⟩
  all_goals try exact ⟨by (first | omega | scalar_tac),by (first | omega | scalar_tac),GoodEncoded.zero input _⟩
  all_goals try exact ⟨by (first | omega | scalar_tac),by (first | omega | scalar_tac),by assumption⟩
end A2Research

open LZ77 (toks bytes bytes_getElem! Matches emit_lit emit_match)
set_option maxHeartbeats 10000000
set_option maxRecDepth 8192
namespace A2Research
theorem emit_lits_loop_precise (input : Slice Std.U8) (out0 : Slice Std.U32)
    (n cnt1 k0 c0 ntok0 : Std.Usize)
    (hn : n.val = input.length) (hout : input.length ≤ out0.length)
    (hk : k0.val ≤ n.val) (hntok : ntok0.val ≤ k0.val) (hc0 : c0.val = 0)
    (hdec : LZ77.decode (toks out0 ntok0.val) = some ((bytes input).take k0.val)) :
    slot.emit_lits_loop input out0 n cnt1 k0 c0 ntok0 ⦃ fun r =>
      r.2.1.val = min n.val (k0.val+cnt1.val) ∧ r.2.1.val ≤ n.val ∧ (k0.val < r.2.1.val ∨ cnt1.val = 0 ∨ k0.val = n.val) ∧
      r.2.2.val ≤ r.2.1.val ∧ r.1.length = out0.length ∧
      LZ77.decode (toks r.1 r.2.2.val) = some ((bytes input).take r.2.1.val) ⦄ := by
  rw [slot.emit_lits_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => n.val - s.2.1.val)
    (inv := fun s =>
      s.2.2.1.val ≤ cnt1.val ∧ s.2.1.val ≤ n.val ∧ s.2.1.val = k0.val + s.2.2.1.val ∧ s.2.2.2.val ≤ s.2.1.val ∧
      s.1.length = out0.length ∧
      LZ77.decode (toks s.1 s.2.2.2.val) = some ((bytes input).take s.2.1.val))
  · rintro ⟨out, k, c, ntok⟩ ⟨hcBound,hkn, hkc, hnt, hlen, hde⟩
    simp only at hcBound hkn hkc hnt hlen hde
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.emit_lits_loop.body]
    split
    case isTrue hklt =>
      split
      case isTrue hc =>
        have hntok_lt : ntok.val < out.length := by (first | omega | scalar_tac)
        have hposlen : k.val < input.length := by (first | omega | scalar_tac)
        step*
        have hval : i1.val = (bytes input)[k.val]! := by
          rw [bytes_getElem! input k.val hposlen, i1_post, Std.U8.cast_U32_val_eq, i_post]
        refine ⟨by (first | omega | scalar_tac), by (first | omega | scalar_tac), by (first | omega | scalar_tac), by (first | omega | scalar_tac),
          by rw [s_post]; simpa [Std.Slice.set_val_eq] using hlen, ?_, by (first | omega | scalar_tac)⟩
        rw [s_post, show ntok1.val = ntok.val + 1 by (first | omega | scalar_tac),
          show k1.val = k.val + 1 by (first | omega | scalar_tac)]
        exact emit_lit input out ntok k.val i1 hde hposlen hntok_lt hval
      case isFalse hc =>
        exact ⟨by dsimp only; simp only [Nat.min_def]; split <;> (first | omega | scalar_tac),hkn, by (first | omega | scalar_tac), hnt, hlen, hde⟩
    case isFalse hge =>
      exact ⟨by dsimp only; simp only [Nat.min_def]; split <;> (first | omega | scalar_tac),hkn, by (first | omega | scalar_tac), hnt, hlen, hde⟩
  · exact ⟨by (first | omega | scalar_tac),hk, by (first | omega | scalar_tac), hntok, rfl, hdec⟩

namespace A2StepScope135
@[scoped step]
theorem _root_.A2Research.emit_lits_precise (input : Slice Std.U8) (out : Slice Std.U32) (pos0 cnt ntok0 : Std.Usize)
    (hout : input.length ≤ out.length) (hpos : pos0.val ≤ input.length)
    (hntok : ntok0.val ≤ pos0.val)
    (hdec : LZ77.decode (toks out ntok0.val) = some ((bytes input).take pos0.val)) :
    slot.emit_lits input out pos0 cnt ntok0 ⦃ fun r =>
      r.1.2.val = min input.length (pos0.val+max 1 cnt.val) ∧
      (pos0.val < r.1.2.val ∨ pos0.val = input.length) ∧ r.1.2.val ≤ input.length ∧ r.1.1.val ≤ r.1.2.val ∧
      r.2.length = out.length ∧
      LZ77.decode (toks r.2 r.1.1.val) = some ((bytes input).take r.1.2.val) ⦄ := by
  rw [slot.emit_lits]
  apply Std.WP.spec_bind (Pₘ := fun (c : Std.Usize) => 1 ≤ c.val ∧ c.val=max 1 cnt.val)
  · split <;> simp only [Std.WP.spec_ok] <;> constructor <;> (first | omega | scalar_tac)
  intro cnt1 ⟨hc1,hcnt⟩
  apply Std.WP.spec_bind (emit_lits_loop_precise input out _ cnt1 pos0 0#usize ntok0
    (by simp) hout (by (first | omega | scalar_tac)) hntok (by simp) hdec)
  rintro ⟨out1, k, ntok⟩ ⟨he,h1, h2, h3, h4, h5⟩
  simp only at he h1 h2 h3 h4 h5
  step*
  all_goals exact ⟨by simpa only [hcnt] using he,by (first | omega | scalar_tac), by (first | omega | scalar_tac), h3, h4, h5⟩

end A2StepScope135
open scoped A2Research.A2StepScope135
theorem public_emit_join_checked (input : Slice Std.U8) (out : Slice Std.U32)
     (pos d l ntok : Std.Usize)
    (costs : Array Std.U32 256#usize)
    (hout : input.length ≤ out.length) (hpos : pos.val < input.length)
    (hntok : ntok.val ≤ pos.val)
    (hcandidate : 3 ≤ l.val → AMatchAt input pos.val l.val d.val)
    (hdec : LZ77.decode (toks out ntok.val) = some ((bytes input).take pos.val)) :
    slot.public_emit_join input out pos d l ntok costs ⦃ fun r =>
      pos.val < r.1.2.val ∧ r.1.2.val ≤ input.length ∧ r.1.1.val ≤ r.1.2.val ∧
      r.2.length = out.length ∧
      LZ77.decode (toks r.2 r.1.1.val) = some ((bytes input).take r.1.2.val) ∧
      (l.val<3 → r.1.2.val=pos.val+1) ⦄ := by
  rw [slot.public_emit_join]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  by_cases hgood : 3 ≤ l.val
  · have hm := hcandidate hgood
    have hm' := hm
    obtain ⟨hl3,hl258,hend,hd1,hdmax,hdpos,hmatch⟩ := hm'
    have hg1 : l >= 3#usize := by (first | omega | scalar_tac)
    have hg2 : l <= 258#usize := by (first | omega | scalar_tac)
    have hg3 : d >= 1#usize := by (first | omega | scalar_tac)
    have hg4 : d <= 32768#usize := by (first | omega | scalar_tac)
    have hg5 : d <= pos := by (first | omega | scalar_tac)
    have hg6 : pos < input.len := by (first | omega | scalar_tac)
    simp only [if_pos hg1,if_pos hg2,if_pos hg3,if_pos hg4,if_pos hg5,if_pos hg6]
    step with Std.Usize.sub_spec as ⟨rem,hrem,hposn⟩
    have hg7 : l <= rem := by (first | omega | scalar_tac)
    simp only [if_pos hg7]
    have ha : ADec input out ntok.val pos.val := ⟨by omega, hntok, hout, hdec⟩
    apply Std.WP.spec_bind (public_back_gate_spec input out costs ntok pos l d ha hm)
    rintro ⟨⟨nt1, p1, l1⟩, out1⟩ hinv
    obtain ⟨hdec1, hL, hm1, hE, hP⟩ := hinv
    have hm1' := hm1
    obtain ⟨h3, h258, hpl, hd1, hd32, hdp, hmm⟩ := hm1'
    have hdec1' := hdec1
    obtain ⟨hps, hntp, hso, hde⟩ := hdec1'
    step*
    have htok : i12.val = LZ77.mkMatch d.val l1.val := by
      simp only [LZ77.mkMatch, LZ77.MATCH_BASE, i12_post, i6_post, i5_post]
      (first | omega | scalar_tac)
    have hdec2 := ADec.match hdec1 hm1 nt1 rfl i12 htok
    rw [← out2_post] at hdec2
    obtain ⟨hpos2, hntpos2, hout2, hdecode2⟩ := hdec2
    refine ⟨by (first | omega | scalar_tac), by (first | omega | scalar_tac), by (first | omega | scalar_tac), ?_, ?_,by omega⟩
    · rw [out2_post, Std.Slice.set_length]; exact hL
    · rw [i13_post, i14_post]
      exact hdecode2
  · have hbad : ¬l >= 3#usize := by (first | omega | scalar_tac)
    simp only [if_neg hbad]
    apply Std.WP.spec_mono (emit_lits_precise input out pos 1#usize ntok hout (by omega) hntok hdec)
    rintro ⟨⟨t,k⟩,o⟩ ⟨he,h1,h2,h3,h4,h5⟩
    exact ⟨by (first | omega | scalar_tac),h2,h3,h4,h5,by
      intro _
      have hmin : min input.length (pos.val+1)=pos.val+1 := Nat.min_eq_right (by omega)
      simpa only [show max 1 (1#usize).val=1 by (first | omega | scalar_tac),hmin] using he⟩

end A2Research

set_option maxHeartbeats 10000000
set_option maxRecDepth 8192
namespace A2Research

theorem ext_ok_checked (input : Slice U8) (pos l2 d2 : Usize)
    (hm : AMatchAt input (pos.val+1) l2.val d2.val) :
    slot.ext_ok input pos l2 d2 ⦃ fun r => r.val ≤ 1 ∧
      (r=1#usize → AMatchAt input pos.val (l2.val+1) d2.val) ⦄ := by
  rw [slot.ext_ok]
  have hmax := Slice.length_ineq input
  obtain ⟨hl3,hl258,hend,hd1,hdmax,hdpos,hmatch⟩ := hm
  step*
  all_goals repeat' (first
    | (intro hc; try step*)
    | (split <;> try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals try exact ⟨by (first | omega | scalar_tac),by intro h; exfalso; (first | omega | scalar_tac)⟩
  all_goals
    refine ⟨by (first | omega | scalar_tac),?_⟩
    intro _
    refine ⟨by (first | omega | scalar_tac),by (first | omega | scalar_tac),by (first | omega | scalar_tac),hd1,hdmax,by (first | omega | scalar_tac),?_⟩
    apply Matches.a_cons
    · simpa only [show pos.val+1-d2.val=pos.val-d2.val+1 by (first | omega | scalar_tac)] using hmatch
    · rw [getElem!_pos input.val pos.val (by (first | omega | scalar_tac)),
          getElem!_pos input.val (pos.val-d2.val) (by (first | omega | scalar_tac))]
      have hi : i=i2 := by assumption
      simpa only [i_post,i2_post,i1_post1] using hi
theorem ext_ok_if_checked (input : Slice U8) (pos l2 d2 : Usize) (cond : Prop) [Decidable cond]
    (hm : cond → AMatchAt input (pos.val+1) l2.val d2.val) :
    (if cond then slot.ext_ok input pos l2 d2 else ok 0#usize) ⦃ fun r => r.val ≤ 1 ∧
      (r=1#usize → AMatchAt input pos.val (l2.val+1) d2.val) ⦄ := by
  split
  · exact ext_ok_checked input pos l2 d2 (hm (by assumption))
  · simp only [Std.WP.spec_ok]
    exact ⟨by (first | omega | scalar_tac),by intro h; exfalso; (first | omega | scalar_tac)⟩
end A2Research

set_option maxHeartbeats 20000000
set_option maxRecDepth 8192
namespace A2Research
theorem choose_tail_checked (input : Slice U8) (p : Nat) (m1 s2 ex : Usize)
    (c : Prop) [Decidable c]
    (hg1 : GoodEncoded input p m1.val) (hg2 : GoodEncoded input (p+1) s2.val)
    (hx : ex=1#usize → AMatchAt input p (s2.val%512+1) ((s2.val/512)%65536)) :
    (if c then ok (m1,0#usize) else
      if ex=1#usize then do
        let v ← lift (core.num.Usize.wrapping_add s2 1#usize)
        ok (v,0#usize)
      else ok (0#usize,s2)) ⦃ fun r =>
        GoodEncoded input p r.1.val ∧ GoodEncoded input (p+1) r.2.val ∧
        (r.2.val ≠ 0 → r.1.val=0) ⦄ := by
  split
  · simp only [Std.WP.spec_ok]
    exact ⟨hg1,GoodEncoded.zero input _,by intro h; exact (h rfl).elim⟩
  · split
    · simp only [lift,bind_tc_ok,Std.WP.spec_ok]
      exact ⟨GoodEncoded.wrapping_next s2 hg2 (hx (by assumption)),GoodEncoded.zero input _,by intro h; exact (h rfl).elim⟩
    · simp only [Std.WP.spec_ok]
      exact ⟨GoodEncoded.zero input _,hg2,by intro _; rfl⟩

theorem g_choose_checked (input : Slice U8) (costs : Array U32 256#usize)
    (pos m1 s2 : Usize) (hp : pos.val < input.length)
    (hg1 : GoodEncoded input pos.val m1.val)
    (hg2 : GoodEncoded input (pos.val+1) s2.val) :
    slot.g_choose input costs pos m1 s2 ⦃ fun r =>
      GoodEncoded input pos.val r.1.val ∧ GoodEncoded input (pos.val+1) r.2.val ∧
      (r.2.val ≠ 0 → r.1.val = 0) ⦄ := by
  rw [slot.g_choose]
  apply Std.WP.spec_bind (Usize.rem_spec m1 (y:=512#usize) (by decide))
  intro l1 l1_post
  change l1.val=m1.val%512 at l1_post
  apply Std.WP.spec_bind (Usize.rem_spec s2 (y:=512#usize) (by decide))
  intro l2 l2_post
  change l2.val=s2.val%512 at l2_post
  split
  · simp only [Std.WP.spec_ok]
    exact ⟨hg1,GoodEncoded.zero input _,by intro h; exact (h rfl).elim⟩
  · split
    · simp only [Std.WP.spec_ok]
      exact ⟨hg1,GoodEncoded.zero input _,by intro h; exact (h rfl).elim⟩
    ·
      apply Std.WP.spec_bind (Usize.div_spec m1 (y:=512#usize) (by decide))
      intro i i_post
      change i.val=m1.val/512 at i_post
      apply Std.WP.spec_bind (Usize.rem_spec i (y:=65536#usize) (by decide))
      intro d1 d1_post
      change d1.val=i.val%65536 at d1_post
      apply Std.WP.spec_bind (Usize.div_spec s2 (y:=512#usize) (by decide))
      intro i1 i1_post
      change i1.val=s2.val/512 at i1_post
      apply Std.WP.spec_bind (Usize.rem_spec i1 (y:=65536#usize) (by decide))
      intro d2 d2_post
      change d2.val=i1.val%65536 at d2_post
      apply Std.WP.spec_bind (ext_ok_checked input pos l2 d2
        (GoodEncoded.decode_parts (m:=s2) (l:=l2) (i:=i1) (d:=d2) hg2 (by scalar_tac) l2_post i1_post d2_post))
      rintro ex ⟨hex,hx⟩
      simp only [lift,bind_tc_ok]
      apply Std.WP.spec_bind (Pₘ := fun (_ : Usize) => True)
      · apply ite_true_spec
        · intro _; simp only [Std.WP.spec_ok]
        · intro _
          apply Std.WP.spec_mono (public_span_better_spec input costs pos l1 d1 l2 d2 ex hex)
          intro _ _; trivial
      · intro take _
        apply choose_tail_checked input pos.val m1 s2 ex (take=0#usize) hg1 hg2
        intro he
        simpa only [l2_post,d2_post,i1_post] using hx he


theorem g_plain_choose_checked (input : Slice U8) (costs : Array U32 256#usize)
    (pos m1 s2 : Usize) (hp : pos.val < input.length)
    (hg1 : GoodEncoded input pos.val m1.val)
    (hg2 : GoodEncoded input (pos.val+1) s2.val) :
    slot.g_plain_choose input costs pos m1 s2 ⦃ fun r =>
      GoodEncoded input pos.val r.1.val ∧ GoodEncoded input (pos.val+1) r.2.val ∧
      (r.2.val ≠ 0 → r.1.val = 0) ⦄ := by
  rw [slot.g_plain_choose]
  apply Std.WP.spec_bind (Usize.rem_spec m1 (y:=512#usize) (by decide))
  intro l1 l1_post
  change l1.val=m1.val%512 at l1_post
  apply Std.WP.spec_bind (Usize.div_spec m1 (y:=512#usize) (by decide))
  intro i i_post
  change i.val=m1.val/512 at i_post
  apply Std.WP.spec_bind (Usize.rem_spec i (y:=65536#usize) (by decide))
  intro d1 d1_post
  change d1.val=i.val%65536 at d1_post
  apply Std.WP.spec_bind (Usize.rem_spec s2 (y:=512#usize) (by decide))
  intro l2 l2_post
  change l2.val=s2.val%512 at l2_post
  apply Std.WP.spec_bind (Usize.div_spec s2 (y:=512#usize) (by decide))
  intro i1 i1_post
  change i1.val=s2.val/512 at i1_post
  apply Std.WP.spec_bind (Usize.rem_spec i1 (y:=65536#usize) (by decide))
  intro d2 d2_post
  change d2.val=i1.val%65536 at d2_post
  apply Std.WP.spec_bind (ext_ok_if_checked input pos l2 d2 (s2 != 0#usize)
    (fun _ => GoodEncoded.decode_parts (m:=s2) (l:=l2) (i:=i1) (d:=d2) hg2 (by scalar_tac) l2_post i1_post d2_post))
  rintro ex ⟨hex,hx⟩
  apply Std.WP.spec_bind (Pₘ := fun (_ : Usize) => True)
  · apply ite_true_spec
    · intro _
      apply Std.WP.spec_mono (public_span_better_spec input costs pos l1 d1 l2 d2 ex hex)
      intro _ _; trivial
    · intro _; simp only [Std.WP.spec_ok]
  · intro take _
    have ht := choose_tail_checked input pos.val m1 s2 ex (take≠1#usize) hg1 hg2 (by
      intro he
      simpa only [l2_post,d2_post,i1_post] using hx he)
    simpa only [ite_not] using ht

end A2Research


set_option maxHeartbeats 20000000
set_option maxRecDepth 8192
namespace A2Research
section


def MainCoreInv (input : Slice U8) (L n : Nat) (out : Slice U32) (p nt carry : Nat) : Prop :=
  p ≤ n ∧ nt ≤ p ∧ out.length = L ∧
  LZ77.decode (toks out nt) = some ((bytes input).take p) ∧ GoodEncoded input p carry

def MainCertPost {S : Type} (input : Slice U8) (L n p0 : Nat)
    (view : S → Slice U32 × Usize × Usize × Usize)
    (r : ControlFlow S (Usize × Slice U32)) : Prop :=
  match r with
  | .done y => y.1.val ≤ input.length ∧ y.2.length = L ∧ LZ77.Valid (bytes input) (toks y.2 y.1.val)
  | .cont s =>
    let v := view s
    MainCoreInv input L n v.1 v.2.1.val v.2.2.1.val v.2.2.2.val ∧ n - v.2.1.val < n - p0

abbrev MainAState := Slice U32 × Array U32 65536#usize × Array U32 65536#usize × Usize × Usize × Usize × Usize
abbrev MainBState := Slice U32 × Array U32 65536#usize × Array U32 65536#usize × Array U32 65536#usize × Usize × Usize × Usize × Usize

def mainAView (s : MainAState) : Slice U32 × Usize × Usize × Usize :=
  (s.1,s.2.2.2.1,s.2.2.2.2.1,s.2.2.2.2.2.1)
def mainBView (s : MainBState) : Slice U32 × Usize × Usize × Usize :=
  (s.1,s.2.2.2.2.1,s.2.2.2.2.2.1,s.2.2.2.2.2.2.1)
attribute [irreducible] MainCoreInv MainCertPost

theorem prod_cases {A B C : Type} (p : A × B) (f : A → B → C) :
    (match p with | (a,b) => f a b) = f p.1 p.2 := by cases p; rfl

def genericMain {T S : Type}
    (pack : Slice U32 → T → Usize → Usize → Usize → Usize → S)
    (input : Slice U8) (n : Usize) (costs : Array U32 256#usize)
    (out : Slice U32) (pos ntok cpre : Usize)
    (scan : Result ((Usize × Usize × Usize) × T))
    (prepare : Usize → Result (Usize × Usize))
    (lazyFn : T → Usize → Usize → Usize → Usize → Result (Usize × T))
    (chooseFn : Usize → Usize → Result (Usize × Usize))
    (insertFn : T → Usize → Usize → Usize → Result T) :
    Result (ControlFlow S (Usize × Slice U32)) := do
  if pos < n then
    let ((q,m1,pre),tab) ← scan
    if q > pos then
      let cnt ← q-pos
      let ((nt,np),o) ← slot.emit_lits input out pos cnt ntok
      if q < n then ok (.cont (pack o tab np nt m1 pre))
      else ok (.cont (pack o tab np nt 0#usize pre))
    else if m1 != 0#usize then
      let (l1,want) ← prepare m1
      let (s2,tab2) ← lazyFn tab (core.num.Usize.wrapping_add pos 1#usize) pre want l1
      let (mm,cc) ← chooseFn m1 s2
      let l ← mm % 512#usize
      let ii ← mm / 512#usize
      let d ← ii % 65536#usize
      let ((nt,np),o) ← slot.public_emit_join input out pos d l ntok costs
      let tab3 ← insertFn tab2 (core.num.Usize.wrapping_add pos 1#usize) np want
      ok (.cont (pack o tab3 np nt cc 0#usize))
    else
      let ((nt,np),o) ← slot.emit_lits input out pos 1#usize ntok
      ok (.cont (pack o tab np nt 0#usize cpre))
  else ok (.done (ntok,out))

theorem genericMain_checked {T S : Type}
    (pack : Slice U32 → T → Usize → Usize → Usize → Usize → S)
    (view : S → Slice U32 × Usize × Usize × Usize)
    (hview : ∀ o t p nt c pre, view (pack o t p nt c pre) = (o,p,nt,c))
    (input : Slice U8) (n : Usize) (span_costs : Array U32 256#usize)
    (out : Slice U32) (pos ntok cpre : Usize)
    (scan : Result ((Usize × Usize × Usize) × T))
    (prepare : Usize → Result (Usize × Usize))
    (lazyFn : T → Usize → Usize → Usize → Usize → Result (Usize × T))
    (chooseFn : Usize → Usize → Result (Usize × Usize))
    (insertFn : T → Usize → Usize → Usize → Result T)
    (hscan : pos.val ≤ input.length → scan ⦃ fun r => pos.val ≤ r.1.1.val ∧ r.1.1.val ≤ input.length ∧ GoodEncoded input r.1.1.val r.1.2.1.val ⦄)
    (hprepare : ∀ m, prepare m ⦃ fun _ => True ⦄)
    (hlazy : ∀ t q pre want min, lazyFn t q pre want min ⦃ fun r => GoodEncoded input q.val r.1.val ⦄)
    (hchoose : pos.val < input.length → ∀ m s, GoodEncoded input pos.val m.val → GoodEncoded input (pos.val+1) s.val → chooseFn m s ⦃ fun r => GoodEncoded input pos.val r.1.val ∧ GoodEncoded input (pos.val+1) r.2.val ∧ (r.2.val ≠ 0 → r.1.val=0) ⦄)
    (hinsert : ∀ t p np want, insertFn t p np want ⦃ fun _ => True ⦄)
    (L : Nat) (hn : n.val=input.length) (hout : input.length ≤ L)
    (hpn : pos.val ≤ n.val) (hnt : ntok.val ≤ pos.val)
    (hde : LZ77.decode (toks out ntok.val) = some ((bytes input).take pos.val))
    (hlen : out.length=L) :
    genericMain pack input n span_costs out pos ntok cpre scan prepare lazyFn chooseFn insertFn ⦃ fun r => MainCertPost input L n.val pos.val view r ⦄ := by
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  rw [genericMain]
  split
  case isTrue hlt =>
    have hltNat : pos.val < n.val := (UScalar.lt_equiv pos n).mp hlt
    have hAddPos := usize_add_one_safe pos n hltNat
    apply Std.WP.spec_bind (hscan (by omega))
    rintro ⟨⟨q,m1,pre⟩,tab⟩ ⟨hqpos,hqn,hgood⟩
    simp only at hqpos hqn hgood
    try simp only []
    simp only [step_simps]
    spec_split
    case h1 hskip =>
      have hskipN : pos.val<q.val := (UScalar.lt_equiv pos q).mp hskip
      apply Std.WP.spec_bind (Usize.sub_spec (x:=q) (y:=pos) hqpos)
      rintro cnt ⟨hcnt,hsub⟩
      change cnt.val=q.val-pos.val at hcnt
      apply Std.WP.spec_bind (emit_lits_precise input out pos cnt ntok (by omega) (by omega) hnt hde)
      rintro ⟨⟨nt,np⟩,o⟩ ⟨he,hadv,hbound,hnt1,hlen1,hdec1⟩
      simp only [Prod.fst,Prod.snd] at he hadv hbound hnt1 hlen1 hdec1
      have hc : max 1 cnt.val=cnt.val := max_eq_right (by omega)
      have hpq : np.val=q.val := by rw [he,hc,show pos.val+cnt.val=q.val by omega,Nat.min_eq_right hqn]
      split <;> (set_option backward.isDefEq.respectTransparency false in simp only [step_simps]) <;> unfold MainCertPost MainCoreInv <;> simp only [and_assoc,hview,Prod.fst,Prod.snd]
      · exact ⟨by omega,hnt1,by omega,hdec1,by
          change GoodEncoded input np.val m1.val
          exact hpq.symm ▸ hgood,by omega⟩
      · exact ⟨by omega,hnt1,by omega,hdec1,GoodEncoded.zero input _,by omega⟩
    case h2 hskip =>
      have hqp : q.val=pos.val := by
        have hnq : ¬pos.val<q.val := fun h => hskip ((UScalar.lt_equiv pos q).mpr h)
        omega
      have hgm : GoodEncoded input pos.val m1.val := by simpa only [hqp] using hgood
      split
      case isFalse hnom =>
        apply Std.WP.spec_bind (emit_lits_precise input out pos 1#usize ntok (by omega) (by omega) hnt hde)
        rintro ⟨⟨nt,np⟩,o⟩ ⟨he,hadv,hbound,hnt1,hlen1,hdec1⟩
        simp only [Prod.fst,Prod.snd] at he hadv hbound hnt1 hlen1 hdec1
        set_option backward.isDefEq.respectTransparency false in
          simp only [step_simps]
        unfold MainCertPost MainCoreInv
        simp only [and_assoc,hview,Prod.fst,Prod.snd]
        exact ⟨by omega,hnt1,by omega,hdec1,GoodEncoded.zero input _,by omega⟩
      case isTrue hmatch =>
        apply Std.WP.spec_bind (hprepare m1)
        rintro ⟨l1,want⟩ _
        let pp := core.num.Usize.wrapping_add pos 1#usize
        have hpp : pp.val=pos.val+1 := hAddPos
        apply Std.WP.spec_bind (hlazy tab pp pre want l1)
        rintro ⟨s2,tab2⟩ hs2
        have hg2 : GoodEncoded input (pos.val+1) s2.val := by simpa only [hpp] using hs2
        apply Std.WP.spec_bind (hchoose (by omega) m1 s2 hgm hg2)
        rintro ⟨mm,cc⟩ ⟨hg1,hg2,hzero⟩
        simp only [step_simps]
        apply Std.WP.spec_bind (Usize.rem_spec mm (y:=512#usize) (by decide))
        intro l hl
        change l.val=mm.val%512 at hl
        apply Std.WP.spec_bind (Usize.div_spec mm (y:=512#usize) (by decide))
        intro ii1 hii1
        change ii1.val=mm.val/512 at hii1
        apply Std.WP.spec_bind (Usize.rem_spec ii1 (y:=65536#usize) (by decide))
        intro d hd
        change d.val=ii1.val%65536 at hd
        apply Std.WP.spec_bind (public_emit_join_checked input out pos d l ntok span_costs (by omega) (by omega) hnt
          (fun hh => GoodEncoded.decode_parts (m:=mm) (l:=l) (i:=ii1) (d:=d) hg1 (by omega) hl hii1 hd) hde)
        rintro ⟨⟨nt,np⟩,o⟩ ⟨hadv,hbound,hnt1,hlen1,hdec1,hlit⟩
        simp only [Prod.fst,Prod.snd] at hadv hbound hnt1 hlen1 hdec1 hlit
        let pp1 := core.num.Usize.wrapping_add pos 1#usize
        apply Std.WP.spec_bind (hinsert tab2 pp1 np want)
        intro tab3 _
        set_option backward.isDefEq.respectTransparency false in
          simp only [step_simps]
        unfold MainCertPost MainCoreInv
        simp only [and_assoc,hview,Prod.fst,Prod.snd]
        refine ⟨by omega,hnt1,by omega,hdec1,?_,by omega⟩
        by_cases hz : cc.val=0
        · rw [hz]; exact GoodEncoded.zero input _
        · have hm : mm.val=0 := hzero hz
          have hp : np.val=pos.val+1 := hlit (by omega)
          simpa only [hp] using hg2
  case isFalse hge =>
    unfold MainCertPost
    have hpn' : pos.val = input.length := by (first | omega | scalar_tac)
    refine ⟨by (first | omega | scalar_tac), hlen, ?_⟩
    unfold LZ77.Valid
    rw [hde, hpn']
    simp


def packA (o : Slice U32) (t : Array U32 65536#usize × Array U32 65536#usize) (p nt c pre : Usize) : MainAState := (o,t.1,t.2,p,nt,c,pre)
def prepA (m : Usize) : Result (Usize × Usize) := do
  let l1 ← m % 512#usize
  let i ← m / 512#usize
  let _ ← i % 65536#usize
  let want ← if l1 < slot.G_LZT then ok 1#usize else ok 0#usize
  ok (l1,want)
theorem prepA_spec (m : Usize) : prepA m ⦃ fun _ => True ⦄ := by
  rw [prepA]
  apply Std.WP.spec_bind (Usize.rem_spec m (y:=512#usize) (by decide))
  intro l hl
  apply Std.WP.spec_bind (Usize.div_spec m (y:=512#usize) (by decide))
  intro i hi
  apply Std.WP.spec_bind (Usize.rem_spec i (y:=65536#usize) (by decide))
  intro d hd
  apply Std.WP.spec_bind (Pₘ := fun (_ : Usize) => True)
  · split <;> simp only [Std.WP.spec_ok]
  · intro want _; simp only [Std.WP.spec_ok]

theorem main_parse_a_body_checked (input : Slice Std.U8) (out : Slice Std.U32) (n : Std.Usize) (t4 : Array Std.U32 65536#usize) (t8 : Array Std.U32 65536#usize) (span_costs : Array Std.U32 256#usize) (acc : Std.U64) (pos : Std.Usize) (ntok : Std.Usize) (carry : Std.Usize) (cpre : Std.Usize)
    (L : Nat) (hn : n.val = input.length) (hout : input.length ≤ L)
    (hpn : pos.val ≤ n.val) (hnt : ntok.val ≤ pos.val)
    (hcarry : GoodEncoded input pos.val carry.val)
    (hde : LZ77.decode (toks out ntok.val) = some ((bytes input).take pos.val))
    (hlen : out.length = L) :
    slot.main_parse_a_loop.body input n span_costs acc out t4 t8 pos ntok carry cpre ⦃ fun r => MainCertPost input L n.val pos.val mainAView r ⦄ := by
  have hsem : slot.main_parse_a_loop.body input n span_costs acc out t4 t8 pos ntok carry cpre =
      genericMain packA input n span_costs out pos ntok cpre
      (slot.g_scan input t4 t8 pos acc carry cpre) prepA (fun t q pre want l1 => slot.g_lazy input t.1 t.2 q pre want l1) (slot.g_choose input span_costs pos) (fun t p np want => slot.g_insert_match input t.1 t.2 p np want) := by
    set_option backward.isDefEq.respectTransparency false in
      simp only [slot.main_parse_a_loop.body,genericMain,packA,prepA,bind_assoc_eq,bind_tc_ok,lift,prod_cases]
    try rfl
  rw [hsem]
  exact genericMain_checked packA mainAView (by intros; rfl)
    input n span_costs out pos ntok cpre
    (slot.g_scan input t4 t8 pos acc carry cpre) prepA (fun t q pre want l1 => slot.g_lazy input t.1 t.2 q pre want l1) (slot.g_choose input span_costs pos) (fun t p np want => slot.g_insert_match input t.1 t.2 p np want)
    (fun hp => g_scan_checked input t4 t8 pos acc carry cpre hp hcarry)
    prepA_spec
    (fun t q pre want min => g_lazy_checked input t.1 t.2 q pre want min)
    (fun hp m z hm hz => g_choose_checked input span_costs pos m z hp hm hz)
    (fun t p np want => g_insert_match_spec input t.1 t.2 p np want)
    L
    hn
    hout
    hpn
    hnt
    hde
    hlen


theorem main_parse_a_loop_checked (input : Slice Std.U8) (out : Slice Std.U32) (n : Std.Usize) (t4 : Array Std.U32 65536#usize) (t8 : Array Std.U32 65536#usize) (span_costs : Array Std.U32 256#usize) (acc : Std.U64) (pos : Std.Usize) (ntok : Std.Usize) (carry : Std.Usize) (cpre : Std.Usize)
    (hn : n.val = input.length) (hout : input.length ≤ out.length)
    (hp : pos.val ≤ n.val) (hntok : ntok.val ≤ pos.val)
    (hcarry : GoodEncoded input pos.val carry.val)
    (hdec : LZ77.decode (toks out ntok.val) = some ((bytes input).take pos.val)) :
    slot.main_parse_a_loop input out n t4 t8 span_costs acc pos ntok carry cpre ⦃ fun r =>
      r.1.val ≤ input.length ∧ r.2.length = out.length ∧
      LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
  rw [slot.main_parse_a_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => n.val - s.2.2.2.1.val)
    (inv := fun s =>
      s.2.2.2.1.val ≤ n.val ∧ s.2.2.2.2.1.val ≤ s.2.2.2.1.val ∧ s.1.length = out.length ∧
      LZ77.decode (toks s.1 s.2.2.2.2.1.val) = some ((bytes input).take s.2.2.2.1.val) ∧
      GoodEncoded input s.2.2.2.1.val s.2.2.2.2.2.1.val)
  · rintro ⟨out1, t4, t8, pos1, ntok1, carry1, cpre1⟩ ⟨hpn, hnt, hlen, hde, hcarry⟩
    apply Std.WP.spec_mono (main_parse_a_body_checked input out1 n t4 t8 span_costs acc pos1 ntok1 carry1 cpre1
      out.length hn hout hpn hnt hcarry hde hlen)
    intro r hr
    cases r with
    | done y => simpa only [MainCertPost] using hr
    | cont x =>
      try simp only [MainCertPost, MainCoreInv, mainAView] at hr
      exact ⟨hr.1, by simpa only [Prod.fst, Prod.snd] using hr.2⟩

  · exact ⟨hp, hntok, rfl, hdec,hcarry⟩

end

end A2Research

set_option maxHeartbeats 20000000
set_option maxRecDepth 8192
namespace A2Research
section

def packB (o : Slice U32) (t : Array U32 65536#usize × Array U32 65536#usize × Array U32 65536#usize) (p nt c pre : Usize) : MainBState := (o,t.1,t.2.1,t.2.2,p,nt,c,pre)
def prepB (m : Usize) : Result (Usize × Usize) := do
  let l1 ← m % 512#usize
  let want ← if l1 < 8#usize then ok 1#usize else ok 0#usize
  ok (l1,want)
theorem prepB_spec (m : Usize) : prepB m ⦃ fun _ => True ⦄ := by
  rw [prepB]
  apply Std.WP.spec_bind (Usize.rem_spec m (y:=512#usize) (by decide))
  intro l hl
  apply Std.WP.spec_bind (Pₘ := fun (_ : Usize) => True)
  · split <;> simp only [Std.WP.spec_ok]
  · intro want _; simp only [Std.WP.spec_ok]

theorem main_parse_b_body_checked (input : Slice Std.U8) (out : Slice Std.U32) (n : Std.Usize) (t4 : Array Std.U32 65536#usize) (t8 : Array Std.U32 65536#usize) (t3 : Array Std.U32 65536#usize) (span_costs : Array Std.U32 256#usize) (acc : Std.U64) (pos : Std.Usize) (ntok : Std.Usize) (carry : Std.Usize) (cpre : Std.Usize)
    (L : Nat) (hn : n.val = input.length) (hout : input.length ≤ L)
    (hpn : pos.val ≤ n.val) (hnt : ntok.val ≤ pos.val)
    (hcarry : GoodEncoded input pos.val carry.val)
    (hde : LZ77.decode (toks out ntok.val) = some ((bytes input).take pos.val))
    (hlen : out.length = L) :
    slot.main_parse_b_loop.body input n span_costs acc out t4 t8 t3 pos ntok carry cpre ⦃ fun r => MainCertPost input L n.val pos.val mainBView r ⦄ := by
  have hsem : slot.main_parse_b_loop.body input n span_costs acc out t4 t8 t3 pos ntok carry cpre =
      genericMain packB input n span_costs out pos ntok cpre
      (slot.g3_scan input t4 t8 t3 pos acc 1#usize carry cpre) prepB (fun t q pre want l1 => slot.g3_lazy input t.1 t.2.1 t.2.2 q pre 1#usize want l1) (slot.g_plain_choose input span_costs pos) (fun t p np want => slot.g3_insert_match input t.1 t.2.1 t.2.2 p np 1#usize want) := by
    set_option backward.isDefEq.respectTransparency false in
      simp only [slot.main_parse_b_loop.body,genericMain,packB,prepB,bind_assoc_eq,bind_tc_ok,lift,prod_cases]
    try rfl
  rw [hsem]
  exact genericMain_checked packB mainBView (by intros; rfl)
    input n span_costs out pos ntok cpre
    (slot.g3_scan input t4 t8 t3 pos acc 1#usize carry cpre) prepB (fun t q pre want l1 => slot.g3_lazy input t.1 t.2.1 t.2.2 q pre 1#usize want l1) (slot.g_plain_choose input span_costs pos) (fun t p np want => slot.g3_insert_match input t.1 t.2.1 t.2.2 p np 1#usize want)
    (fun hp => g3_scan_checked input t4 t8 t3 pos acc 1#usize carry cpre hp hcarry)
    prepB_spec
    (fun t q pre want min => g3_lazy_checked input t.1 t.2.1 t.2.2 q pre 1#usize want min)
    (fun hp m z hm hz => g_plain_choose_checked input span_costs pos m z hp hm hz)
    (fun t p np want => g3_insert_match_spec input t.1 t.2.1 t.2.2 p np 1#usize want)
    L
    hn
    hout
    hpn
    hnt
    hde
    hlen


theorem main_parse_b_loop_checked (input : Slice Std.U8) (out : Slice Std.U32) (n : Std.Usize) (t4 : Array Std.U32 65536#usize) (t8 : Array Std.U32 65536#usize) (t3 : Array Std.U32 65536#usize) (span_costs : Array Std.U32 256#usize) (acc : Std.U64) (pos : Std.Usize) (ntok : Std.Usize) (carry : Std.Usize) (cpre : Std.Usize)
    (hn : n.val = input.length) (hout : input.length ≤ out.length)
    (hp : pos.val ≤ n.val) (hntok : ntok.val ≤ pos.val)
    (hcarry : GoodEncoded input pos.val carry.val)
    (hdec : LZ77.decode (toks out ntok.val) = some ((bytes input).take pos.val)) :
    slot.main_parse_b_loop input out n t4 t8 t3 span_costs acc pos ntok carry cpre ⦃ fun r =>
      r.1.val ≤ input.length ∧ r.2.length = out.length ∧
      LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
  rw [slot.main_parse_b_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => n.val - s.2.2.2.2.1.val)
    (inv := fun s =>
      s.2.2.2.2.1.val ≤ n.val ∧ s.2.2.2.2.2.1.val ≤ s.2.2.2.2.1.val ∧ s.1.length = out.length ∧
      LZ77.decode (toks s.1 s.2.2.2.2.2.1.val) = some ((bytes input).take s.2.2.2.2.1.val) ∧
      GoodEncoded input s.2.2.2.2.1.val s.2.2.2.2.2.2.1.val)
  · rintro ⟨out1, t4, t8, t3, pos1, ntok1, carry1, cpre1⟩ ⟨hpn, hnt, hlen, hde, hcarry⟩
    apply Std.WP.spec_mono (main_parse_b_body_checked input out1 n t4 t8 t3 span_costs acc pos1 ntok1 carry1 cpre1
      out.length hn hout hpn hnt hcarry hde hlen)
    intro r hr
    cases r with
    | done y => simpa only [MainCertPost] using hr
    | cont x =>
      try simp only [MainCertPost, MainCoreInv, mainBView] at hr
      exact ⟨hr.1, by simpa only [Prod.fst, Prod.snd] using hr.2⟩

  · exact ⟨hp, hntok, rfl, hdec,hcarry⟩

end

end A2Research

set_option maxHeartbeats 20000000
set_option maxRecDepth 8192
namespace A2Research
section

def prepHigh (m : Usize) : Result (Usize × Usize) := do
  let l1 ← m % 512#usize
  let want ← if l1 < 0#usize then ok 1#usize else ok 0#usize
  ok (l1,want)
theorem prepHigh_spec (m : Usize) : prepHigh m ⦃ fun _ => True ⦄ := by
  rw [prepHigh]
  apply Std.WP.spec_bind (Usize.rem_spec m (y:=512#usize) (by decide))
  intro l hl
  apply Std.WP.spec_bind (Pₘ := fun (_ : Usize) => True)
  · split <;> simp only [Std.WP.spec_ok]
  · intro want _; simp only [Std.WP.spec_ok]

theorem main_parse_high_body_checked (input : Slice Std.U8) (out : Slice Std.U32) (n : Std.Usize) (t4 : Array Std.U32 65536#usize) (t8 : Array Std.U32 65536#usize) (span_costs : Array Std.U32 256#usize) (acc : Std.U64) (pos : Std.Usize) (ntok : Std.Usize) (carry : Std.Usize) (cpre : Std.Usize)
    (L : Nat) (hn : n.val = input.length) (hout : input.length ≤ L)
    (hpn : pos.val ≤ n.val) (hnt : ntok.val ≤ pos.val)
    (hcarry : GoodEncoded input pos.val carry.val)
    (hde : LZ77.decode (toks out ntok.val) = some ((bytes input).take pos.val))
    (hlen : out.length = L) :
    slot.main_parse_high_loop.body input n span_costs acc out t4 t8 pos ntok carry cpre ⦃ fun r => MainCertPost input L n.val pos.val mainAView r ⦄ := by
  have hsem : slot.main_parse_high_loop.body input n span_costs acc out t4 t8 pos ntok carry cpre =
      genericMain packA input n span_costs out pos ntok cpre
      (slot.gh_scan input t4 t8 pos acc carry cpre) prepHigh (fun t q pre want l1 => slot.gh_lazy input t.1 t.2 q pre want) (slot.g_plain_choose input span_costs pos) (fun t p np want => slot.gh_insert_match input t.1 t.2 p np) := by
    set_option backward.isDefEq.respectTransparency false in
      simp only [slot.main_parse_high_loop.body,genericMain,packA,prepHigh,bind_assoc_eq,bind_tc_ok,lift,prod_cases]
    try rfl
  rw [hsem]
  exact genericMain_checked packA mainAView (by intros; rfl)
    input n span_costs out pos ntok cpre
    (slot.gh_scan input t4 t8 pos acc carry cpre) prepHigh (fun t q pre want l1 => slot.gh_lazy input t.1 t.2 q pre want) (slot.g_plain_choose input span_costs pos) (fun t p np want => slot.gh_insert_match input t.1 t.2 p np)
    (fun hp => gh_scan_checked input t4 t8 pos acc carry cpre hp hcarry)
    prepHigh_spec
    (fun t q pre want min => gh_lazy_checked input t.1 t.2 q pre want)
    (fun hp m z hm hz => g_plain_choose_checked input span_costs pos m z hp hm hz)
    (fun t p np want => gh_insert_match_spec input t.1 t.2 p np)
    L
    hn
    hout
    hpn
    hnt
    hde
    hlen


theorem main_parse_high_loop_checked (input : Slice Std.U8) (out : Slice Std.U32) (n : Std.Usize) (t4 : Array Std.U32 65536#usize) (t8 : Array Std.U32 65536#usize) (span_costs : Array Std.U32 256#usize) (acc : Std.U64) (pos : Std.Usize) (ntok : Std.Usize) (carry : Std.Usize) (cpre : Std.Usize)
    (hn : n.val = input.length) (hout : input.length ≤ out.length)
    (hp : pos.val ≤ n.val) (hntok : ntok.val ≤ pos.val)
    (hcarry : GoodEncoded input pos.val carry.val)
    (hdec : LZ77.decode (toks out ntok.val) = some ((bytes input).take pos.val)) :
    slot.main_parse_high_loop input out n t4 t8 span_costs acc pos ntok carry cpre ⦃ fun r =>
      r.1.val ≤ input.length ∧ r.2.length = out.length ∧
      LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
  rw [slot.main_parse_high_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => n.val - s.2.2.2.1.val)
    (inv := fun s =>
      s.2.2.2.1.val ≤ n.val ∧ s.2.2.2.2.1.val ≤ s.2.2.2.1.val ∧ s.1.length = out.length ∧
      LZ77.decode (toks s.1 s.2.2.2.2.1.val) = some ((bytes input).take s.2.2.2.1.val) ∧
      GoodEncoded input s.2.2.2.1.val s.2.2.2.2.2.1.val)
  · rintro ⟨out1, t4, t8, pos1, ntok1, carry1, cpre1⟩ ⟨hpn, hnt, hlen, hde, hcarry⟩
    apply Std.WP.spec_mono (main_parse_high_body_checked input out1 n t4 t8 span_costs acc pos1 ntok1 carry1 cpre1
      out.length hn hout hpn hnt hcarry hde hlen)
    intro r hr
    cases r with
    | done y => simpa only [MainCertPost] using hr
    | cont x =>
      try simp only [MainCertPost, MainCoreInv, mainAView] at hr
      exact ⟨hr.1, by simpa only [Prod.fst, Prod.snd] using hr.2⟩

  · exact ⟨hp, hntok, rfl, hdec,hcarry⟩

end

end A2Research

/- Round-9 lane P2: R1's text loop `gr_text` (n2a). G's scan with the caller's first table entries (`gr_scan`) and its
   helpers; `gr_scan_loop_checked` = cand25's `g_scan_loop_checked` with the loop output `(t4, t8, p, m)` (no `pre`). -/
set_option maxHeartbeats 10000000
set_option maxRecDepth 8192
namespace A2Research
open scoped Submission.A2StepScope1 A2Research.A2StepScope122 Submission.A2StepScope95 Submission.A2StepScope96 Submission.A2StepScope97 Submission.A2StepScope98 Submission.A2StepScope99 Submission.A2StepScope100 Submission.A2StepScope93 Submission.A2StepScope94 A2Research.A2StepScope124

theorem GoodEncoded.of_val_zero {input : Slice U8} {p : Nat} {m : Usize} (h : m.val = 0) :
    GoodEncoded input p m.val := by
  rw [h]; exact GoodEncoded.zero input p

theorem gr_scan_loop_checked (input : Slice U8) (t4 t8 : Array U32 65536#usize)
    (acc : U64) (n p k m : Usize) (v : U64) (e : Usize × Usize)
    (p0 : Nat) (hn : n.val=input.length) (hn16 : 16 ≤ n.val)
    (hk : k.val ≤ p.val) (hp0 : p0 ≤ p.val) (hp : p.val ≤ n.val)
    (hm : GoodEncoded input p.val m.val) :
    slot.gr_scan_loop input t4 t8 acc n p k m v e ⦃ fun r =>
      p0 ≤ r.2.2.1.val ∧ r.2.2.1.val ≤ n.val ∧ GoodEncoded input r.2.2.1.val r.2.2.2.val ⦄ := by
  rw [slot.gr_scan_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => n.val-s.2.2.1.val)
    (inv := fun s => s.2.2.2.1.val ≤ s.2.2.1.val ∧ p0 ≤ s.2.2.1.val ∧
      s.2.2.1.val ≤ n.val ∧ GoodEncoded input s.2.2.1.val s.2.2.2.2.1.val)
  · rintro ⟨t4,t8,p,k,m,v,e⟩ ⟨hk,hp0,hp,hm⟩
    simp only at hk hp0 hp hm
    have hmax := Slice.length_ineq input
    simp only [slot.gr_scan_loop.body, lift, Array.to_slice_mut]
    step* -grind -threadGrindState +scalarTac
    all_goals repeat (first
      | (fail_if_no_progress (casesm* _ × _; try simp only []; try step* -grind -threadGrindState +scalarTac))
      | (intro hc; try step* -grind -threadGrindState +scalarTac)
      | (split <;> try step* -grind -threadGrindState +scalarTac)
      | (apply spec_ite_cut <;> intro hc <;> try step* -grind -threadGrindState +scalarTac)
      | (step -grind -threadGrindState +scalarTac <;> try step* -grind -threadGrindState +scalarTac)
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step* -grind -threadGrindState +scalarTac))
    all_goals try exact ⟨hp0,hp,hm⟩
    all_goals try exact ⟨hp0,hp,by assumption⟩
    all_goals try (
      refine ⟨by (first | omega | scalar_tac),by (first | omega | scalar_tac),by (first | omega | scalar_tac),?_,by (first | omega | scalar_tac)⟩
      apply GoodEncoded.of_val_zero
      (first | omega | scalar_tac))
  · exact ⟨hk,hp0,hp,hm⟩

namespace P2Scope1
@[scoped step]
theorem _root_.A2Research.gr_scan_loop_start_checked (input : Slice U8) (t4 t8 : Array U32 65536#usize)
    (acc : U64) (n p k m : Usize) (v : U64) (e : Usize × Usize)
    (hn : n.val=input.length) (hn16 : 16 ≤ n.val)
    (hk : k.val ≤ p.val) (hp : p.val ≤ n.val)
    (hm : GoodEncoded input p.val m.val) :
    slot.gr_scan_loop input t4 t8 acc n p k m v e ⦃ fun r =>
      p.val ≤ r.2.2.1.val ∧ r.2.2.1.val ≤ n.val ∧ GoodEncoded input r.2.2.1.val r.2.2.2.val ⦄ := by
  exact gr_scan_loop_checked input t4 t8 acc n p k m v e p.val hn hn16 hk (le_refl _) hp hm

end P2Scope1
open scoped A2Research.P2Scope1
theorem gr_scan_checked (input : Slice U8) (t4 t8 : Array U32 65536#usize)
    (pos : Usize) (acc : U64) (c4 c8 : Usize)
    (hp : pos.val ≤ input.length) :
    slot.gr_scan input t4 t8 pos acc c4 c8 ⦃ fun r =>
      pos.val ≤ r.1.1.val ∧ r.1.1.val ≤ input.length ∧ GoodEncoded input r.1.1.val r.1.2.val ⦄ := by
  rw [slot.gr_scan]
  have hmax := Slice.length_ineq input
  step* -grind -threadGrindState +scalarTac
  all_goals repeat (first
    | (fail_if_no_progress (casesm* _ × _; try simp only []; try step* -grind -threadGrindState +scalarTac))
    | (intro h; try step* -grind -threadGrindState +scalarTac)
    | (split <;> try step* -grind -threadGrindState +scalarTac)
    | (apply spec_ite_cut <;> intro h <;> try step* -grind -threadGrindState +scalarTac)
    | (step -grind -threadGrindState +scalarTac <;> try step* -grind -threadGrindState +scalarTac)
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step* -grind -threadGrindState +scalarTac))
  all_goals try exact GoodEncoded.zero input _
  all_goals try exact ⟨by (first | omega | scalar_tac),by (first | omega | scalar_tac),GoodEncoded.zero input _⟩
  all_goals try exact ⟨by (first | omega | scalar_tac),by (first | omega | scalar_tac),by assumption⟩
end A2Research

set_option maxHeartbeats 10000000
set_option maxRecDepth 8192
namespace Submission
open scoped Submission.A2StepScope1 Submission.A2StepScope95 Submission.A2StepScope96 Submission.A2StepScope99 Submission.F1StepScope1 A2FastPureChoice

theorem gr_insert_match_spec (input : Slice Std.U8) (t4 : Array Std.U32 65536#usize) (t8 : Array Std.U32 65536#usize) («from» : Std.Usize) («to» : Std.Usize) :
    slot.gr_insert_match input t4 t8 «from» «to» ⦃ fun _ => True ⦄ := by
  rw [slot.gr_insert_match]
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat (first
    | (intro hc; (try step*))
    | (split <;> (try step*))
    | (casesm* _ × _; (try simp only []); (try step*))
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals (first | omega | scalar_tac)

theorem gr_ahead_spec (input : Slice Std.U8) (t4 : Array Std.U32 65536#usize) (t8 : Array Std.U32 65536#usize) (p : Std.Usize) :
    slot.gr_ahead input t4 t8 p ⦃ fun _ => True ⦄ := by
  rw [slot.gr_ahead]
  step*
end Submission

/- Completed development module: Main (engine G) -/

namespace Submission
open Aeneas Aeneas.Std Result ControlFlow A2Research
open LZ77 (toks bytes bytes_getElem! Matches emit_lit emit_match)
set_option maxRecDepth 8192
set_option maxHeartbeats 4000000
set_option linter.unusedTactic false
set_option linter.unreachableTactic false
set_option linter.unusedVariables false
set_option linter.unusedSimpArgs false

open scoped Submission.A2StepScope1 Submission.A2StepScope68 Submission.A2StepScope67 Submission.A2StepScope2 Submission.A2StepScope3 Submission.A2StepScope85 Submission.A2StepScope4 Submission.A2StepScope86 Submission.A2StepScope87 Submission.A2StepScope70 Submission.A2StepScope5 Submission.A2StepScope6 Submission.A2StepScope7 Submission.A2StepScope8 Submission.A2StepScope9 Submission.A2StepScope10 Submission.A2StepScope11 Submission.A2StepScope12 Submission.A2StepScope13 Submission.A2StepScope14 Submission.A2StepScope15 Submission.A2StepScope16 Submission.A2StepScope17 Submission.A2StepScope18 Submission.A2StepScope19 Submission.A2StepScope20 Submission.A2StepScope88 Submission.A2StepScope21 Submission.A2StepScope22 Submission.A2StepScope23 Submission.A2StepScope24 Submission.A2StepScope25 Submission.A2StepScope26 Submission.A2StepScope27 Submission.A2StepScope28 Submission.A2StepScope89 Submission.A2StepScope29 Submission.A2StepScope30 Submission.A2StepScope31 Submission.A2StepScope90 Submission.A2StepScope32 Submission.A2StepScope34 Submission.A2StepScope35 Submission.A2StepScope36 Submission.A2StepScope37 Submission.A2StepScope38 Submission.A2StepScope39 Submission.A2StepScope40 Submission.A2StepScope41 Submission.A2StepScope42 Submission.A2StepScope43 Submission.A2StepScope44 Submission.A2StepScope45 Submission.A2StepScope46 Submission.A2StepScope47 Submission.A2StepScope48 Submission.A2StepScope49 Submission.A2StepScope50 Submission.A2StepScope51 Submission.A2StepScope52 Submission.A2StepScope53 Submission.A2StepScope54 Submission.A2StepScope55 Submission.A2StepScope56 Submission.A2StepScope57 Submission.A2StepScope58 Submission.A2StepScope59 Submission.A2StepScope60 Submission.A2StepScope61 Submission.A2StepScope62 Submission.A2StepScope63 Submission.A2StepScope64 Submission.A2StepScope65 Submission.A2StepScope66 Submission.A2StepScope33
open scoped Submission.A2StepScope78
attribute [-step] ite_true_spec

section

theorem main_parse_high_spec (input : Slice Std.U8) (out : Slice Std.U32) (pos0 : Std.Usize) (ntok0 : Std.Usize) (hist : Array Std.U32 256#usize) (e : Std.Usize) (low : Std.Usize)
    (hlen : input.length ≤ out.length)
    (hp : pos0.val ≤ input.length) (hntok : ntok0.val ≤ pos0.val)
    (hdec : LZ77.decode (toks out ntok0.val) = some ((bytes input).take pos0.val)) :
    slot.main_parse_high input out pos0 ntok0 hist e low ⦃ fun r =>
      r.1.val ≤ input.length ∧
      r.2.length = out.length ∧
      LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
  rw [slot.main_parse_high]
  apply Std.WP.spec_bind (fl_costs_spec hist (Array.repeat 256#usize 0#u32))
  intro costs _
  apply Std.WP.spec_bind (Pₘ := fun (_ : Std.U64) => True)
  · split <;> simp only [Std.WP.spec_ok] <;> trivial
  · intro acc _
    exact main_parse_high_loop_checked input out _ _ _ costs acc pos0 ntok0 0#usize 0#usize
      (Slice.len_val input) hlen (by simpa only [Slice.len_val] using hp) hntok
      (GoodEncoded.zero input _) hdec

end

section

theorem main_parse_a_spec (input : Slice Std.U8) (out : Slice Std.U32) (pos0 : Std.Usize) (ntok0 : Std.Usize) (hist : Array Std.U32 256#usize) (e : Std.Usize) (low : Std.Usize)
    (hlen : input.length ≤ out.length)
    (hp : pos0.val ≤ input.length) (hntok : ntok0.val ≤ pos0.val)
    (hdec : LZ77.decode (toks out ntok0.val) = some ((bytes input).take pos0.val)) :
    slot.main_parse_a input out pos0 ntok0 hist e low ⦃ fun r =>
      r.1.val ≤ input.length ∧
      r.2.length = out.length ∧
      LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
  rw [slot.main_parse_a]
  apply Std.WP.spec_bind (fl_costs_spec hist (Array.repeat 256#usize 0#u32))
  intro costs _
  apply Std.WP.spec_bind (Pₘ := fun (_ : Std.U64) => True)
  · split <;> simp only [Std.WP.spec_ok] <;> trivial
  · intro acc _
    exact main_parse_a_loop_checked input out _ _ _ costs acc pos0 ntok0 0#usize 0#usize
      (Slice.len_val input) hlen (by simpa only [Slice.len_val] using hp) hntok
      (GoodEncoded.zero input _) hdec

end

section

theorem main_parse_b_spec (input : Slice Std.U8) (out : Slice Std.U32) (pos0 : Std.Usize) (ntok0 : Std.Usize) (hist : Array Std.U32 256#usize) (e : Std.Usize) (low : Std.Usize)
    (hlen : input.length ≤ out.length)
    (hp : pos0.val ≤ input.length) (hntok : ntok0.val ≤ pos0.val)
    (hdec : LZ77.decode (toks out ntok0.val) = some ((bytes input).take pos0.val)) :
    slot.main_parse_b input out pos0 ntok0 hist e low ⦃ fun r =>
      r.1.val ≤ input.length ∧
      r.2.length = out.length ∧
      LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
  rw [slot.main_parse_b]
  apply Std.WP.spec_bind (fl_costs_spec hist (Array.repeat 256#usize 0#u32))
  intro costs _
  apply Std.WP.spec_bind (Pₘ := fun (_ : Std.U64) => True)
  · split <;> simp only [Std.WP.spec_ok] <;> trivial
  · intro acc _
    exact main_parse_b_loop_checked input out _ _ _ _ costs acc pos0 ntok0 0#usize 0#usize
      (Slice.len_val input) hlen (by simpa only [Slice.len_val] using hp) hntok
      (GoodEncoded.zero input _) hdec

end

section

-- (main_parse_spec regenerated below)
end

open scoped Submission.P0Scope1 Submission.P0Scope2 Submission.P0Scope3 Submission.P0Scope4 Submission.P0Scope5 Submission.P0Scope6 Submission.P0Scope7 Submission.P0Scope8 Submission.P0Scope9 Submission.P0Scope10 Submission.P0Scope11 Submission.P0Scope12 Submission.P0Scope13 Submission.P0Scope14 Submission.P0Scope15 Submission.P0Scope16 Submission.P0Scope17 Submission.P0Scope18 Submission.P0Scope19 Submission.P0Scope20 Submission.P0Scope21 Submission.P0Scope22 Submission.P0Scope23 Submission.P0Scope24 Submission.P0Scope25 Submission.P0Scope26 Submission.P0Scope27 Submission.P0Scope28 Submission.P0Scope29 Submission.P0Scope30 Submission.P0Scope31 Submission.P0Scope32 Submission.P0Scope33 Submission.P0Scope34 Submission.P0Scope35 Submission.P0Scope36 Submission.P0Scope37 Submission.P0Scope38 Submission.P0Scope39 Submission.P0Scope40 Submission.P0Scope41 Submission.P0Scope42 Submission.P0Scope43 Submission.P0Scope44 Submission.P0Scope45 Submission.P0Scope46 Submission.P0Scope47 Submission.P0Scope48 Submission.P0Scope49 Submission.P0Scope50 Submission.P0Scope51 Submission.P0Scope52 Submission.P0Scope53 Submission.P0Scope54 Submission.P0Scope55 Submission.P0Scope56 Submission.P0Scope57 Submission.P0Scope58 Submission.P0Scope59 Submission.P0Scope60 Submission.P0Scope61 Submission.P0Scope62 Submission.P0Scope63 Submission.P0Scope64 Submission.P0Scope65 Submission.P0Scope66 Submission.P0Scope67 Submission.P0Scope68 Submission.P0Scope69 Submission.P0Scope70 Submission.P0Scope71 Submission.P0Scope72 Submission.P0Scope73 Submission.P0Scope74 Submission.P0Scope75 Submission.P0Scope76 Submission.P0Scope77 Submission.P0Scope78 Submission.P0Scope79 Submission.P0Scope80 Submission.P0Scope81 Submission.P0Scope82 Submission.P0Scope83 Submission.P0Scope84 Submission.P0Scope85 Submission.P0Scope86 Submission.P0Scope87 Submission.P0Scope88 Submission.P0Scope89 Submission.P0Scope90
namespace P0Scope91
end P0Scope91
open scoped Submission.P0Scope91

namespace P0Scope92
end P0Scope92
open scoped Submission.P0Scope92

namespace P0Scope93
end P0Scope93
open scoped Submission.P0Scope93

namespace P0Scope94
end P0Scope94
open scoped Submission.P0Scope94

namespace P0Scope95
end P0Scope95
open scoped Submission.P0Scope95

namespace P0Scope96
end P0Scope96
open scoped Submission.P0Scope96

namespace P0Scope97
end P0Scope97
open scoped Submission.P0Scope97

/- Round-9 lane P2: R1's text loop. Per iteration: scan (proven GoodEncoded result at q), untrusted inserts and
   look-ahead, literals pos..q (`gr_lits`, exact end q), then one checked `public_emit_join` at q when q < n. -/
theorem gr_lits_precise (input : Slice Std.U8) (out : Slice Std.U32) (pos s ntok : Std.Usize)
    (hout : input.length ≤ out.length) (hpos : pos.val ≤ s.val) (hs : s.val ≤ input.length)
    (hntok : ntok.val ≤ pos.val)
    (hdec : LZ77.decode (toks out ntok.val) = some ((bytes input).take pos.val)) :
    slot.gr_lits input out pos s ntok ⦃ fun r =>
      r.1.2.val = s.val ∧ r.1.1.val ≤ r.1.2.val ∧ r.2.length = out.length ∧
      LZ77.decode (toks r.2 r.1.1.val) = some ((bytes input).take r.1.2.val) ⦄ := by
  rw [slot.gr_lits]
  split
  case isTrue hlt =>
    have hltN : pos.val < s.val := (UScalar.lt_equiv pos s).mp hlt
    apply Std.WP.spec_bind (Usize.sub_spec (x:=s) (y:=pos) hpos)
    rintro cnt ⟨hcnt,hsub⟩
    change cnt.val=s.val-pos.val at hcnt
    apply Std.WP.spec_mono (emit_lits_precise input out pos cnt ntok hout (by omega) hntok hdec)
    rintro ⟨⟨nt,np⟩,o⟩ ⟨he,hadv,hbound,hnt1,hlen1,hdec1⟩
    simp only [Prod.fst,Prod.snd] at he hadv hbound hnt1 hlen1 hdec1
    have hc : max 1 cnt.val=cnt.val := max_eq_right (by omega)
    have hpq : np.val=s.val := by rw [he,hc,show pos.val+cnt.val=s.val by omega,Nat.min_eq_right hs]
    exact ⟨hpq,hnt1,hlen1,hdec1⟩
  case isFalse hge =>
    have hnlt : ¬pos.val < s.val := fun h => hge ((UScalar.lt_equiv pos s).mpr h)
    simp only [Std.WP.spec_ok]
    exact ⟨by omega,hntok,by first | rfl | trivial,hdec⟩

theorem gr_text_loop_checked (input : Slice Std.U8) (out : Slice Std.U32) (n : Std.Usize)
    (t4 t8 : Array Std.U32 65536#usize) (span_costs : Array Std.U32 256#usize) (acc : Std.U64)
    (pos ntok : Std.Usize) (e : Std.Usize × Std.Usize)
    (hn : n.val = input.length) (hout : input.length ≤ out.length)
    (hp : pos.val ≤ n.val) (hntok : ntok.val ≤ pos.val)
    (hdec : LZ77.decode (toks out ntok.val) = some ((bytes input).take pos.val)) :
    slot.gr_text_loop input out n t4 t8 span_costs acc pos ntok e ⦃ fun r =>
      r.1.val ≤ input.length ∧ r.2.length = out.length ∧
      LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  rw [slot.gr_text_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => n.val - s.2.2.2.1.val)
    (inv := fun s =>
      s.2.2.2.1.val ≤ n.val ∧ s.2.2.2.2.1.val ≤ s.2.2.2.1.val ∧ s.1.length = out.length ∧
      LZ77.decode (toks s.1 s.2.2.2.2.1.val) = some ((bytes input).take s.2.2.2.1.val))
  · rintro ⟨out1, t4, t8, pos1, ntok1, c4, c8⟩ ⟨hpn, hnt, hlen, hde⟩
    simp only at hpn hnt hlen hde
    simp only [slot.gr_text_loop.body, lift, bind_tc_ok]
    split
    case isTrue hlt =>
      have hltN : pos1.val < n.val := (UScalar.lt_equiv pos1 n).mp hlt
      apply Std.WP.spec_bind (gr_scan_checked input t4 t8 pos1 acc c4 c8 (by omega))
      rintro ⟨⟨q, m⟩, t41, t81⟩ ⟨hqpos, hqn, hgood⟩
      simp only at hqpos hqn hgood
      simp only [step_simps]
      apply Std.WP.spec_bind (Usize.rem_spec m (y:=512#usize) (by decide))
      intro l hl
      change l.val=m.val%512 at hl
      apply Std.WP.spec_bind (Usize.div_spec m (y:=512#usize) (by decide))
      intro ii1 hii1
      change ii1.val=m.val/512 at hii1
      apply Std.WP.spec_bind (Usize.rem_spec ii1 (y:=65536#usize) (by decide))
      intro d hd
      change d.val=ii1.val%65536 at hd
      apply Std.WP.spec_bind (gr_insert_match_spec input t41 t81 _ _)
      rintro ⟨t42, t82⟩ _
      try simp only [step_simps]
      apply Std.WP.spec_bind (gr_ahead_spec input t42 t82 _)
      intro e1 _
      apply Std.WP.spec_bind (gr_lits_precise input out1 pos1 q ntok1 (by omega) hqpos hqn hnt hde)
      rintro ⟨⟨ntok2, pos2⟩, out2⟩ ⟨hp2, hnt2, hlen2, hdec2⟩
      simp only at hp2 hnt2 hlen2 hdec2
      try simp only [step_simps]
      split
      case isTrue hlt2 =>
        have hlt2N : pos2.val < n.val := (UScalar.lt_equiv pos2 n).mp hlt2
        apply Std.WP.spec_bind (public_emit_join_checked input out2 pos2 d l ntok2 span_costs (by omega) (by omega) hnt2
          (fun hh => by
            rw [hp2]
            exact GoodEncoded.decode_parts (m:=m) (l:=l) (i:=ii1) (d:=d) hgood (by omega) hl hii1 hd) hdec2)
        rintro ⟨⟨ntok3, pos3⟩, out3⟩ ⟨hadv, hbound, hnt3, hlen3, hdec3, _⟩
        simp only at hadv hbound hnt3 hlen3 hdec3
        try simp only [step_simps]
        try simp only [Std.WP.spec_ok]
        try simp only [and_assoc]
        refine ⟨?_, ?_, ?_, ?_, ?_⟩ <;> first | omega | assumption | scalar_tac
      case isFalse hge2 =>
        have hge2N : ¬pos2.val < n.val := fun h => hge2 ((UScalar.lt_equiv pos2 n).mpr h)
        try simp only [step_simps]
        try simp only [Std.WP.spec_ok]
        try simp only [and_assoc]
        refine ⟨?_, ?_, ?_, ?_, ?_⟩ <;> first | omega | assumption | scalar_tac
    case isFalse hge =>
      have hgeN : ¬pos1.val < n.val := fun h => hge ((UScalar.lt_equiv pos1 n).mpr h)
      simp only [Std.WP.spec_ok]
      have hpn' : pos1.val = input.length := by omega
      refine ⟨by omega, hlen, ?_⟩
      unfold LZ77.Valid
      rw [hde, hpn']
      simp
  · exact ⟨hp, hntok, rfl, hdec⟩

theorem gr_text_spec (input : Slice Std.U8) (out : Slice Std.U32) (pos0 : Std.Usize) (ntok0 : Std.Usize) (hist : Array Std.U32 256#usize) (low : Std.Usize)
    (hlen : input.length ≤ out.length)
    (hp : pos0.val ≤ input.length) (hntok : ntok0.val ≤ pos0.val)
    (hdec : LZ77.decode (toks out ntok0.val) = some ((bytes input).take pos0.val)) :
    slot.gr_text input out pos0 ntok0 hist low ⦃ fun r =>
      r.1.val ≤ input.length ∧
      r.2.length = out.length ∧
      LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
  rw [slot.gr_text]
  apply Std.WP.spec_bind (fl_costs_spec hist (Array.repeat 256#usize 0#u32))
  intro costs _
  apply Std.WP.spec_bind (Pₘ := fun (_ : Std.U64) => True)
  · split <;> simp only [Std.WP.spec_ok] <;> trivial
  · intro acc _
    apply Std.WP.spec_bind (gr_ahead_spec input _ _ pos0)
    intro e _
    exact gr_text_loop_checked input out _ _ _ costs acc pos0 ntok0 e
      (Slice.len_val input) hlen (by simpa only [Slice.len_val] using hp) hntok hdec

section
open scoped Submission.A2StepScope33
attribute [local step] Submission.entropy256_spec
attribute [local step] Submission.share_spec
attribute [local step] Submission.low_mode_spec
attribute [local step] Submission.main_parse_a_spec
attribute [local step] Submission.main_parse_high_spec
attribute [local step] Submission.main_parse_b_spec
attribute [local step] Submission.gr_text_spec
namespace P0Scope98
@[scoped step]
theorem _root_.Submission.main_parse_spec (input : Slice Std.U8) (out : Slice Std.U32) (pos0 : Std.Usize) (ntok0 : Std.Usize) (hist : Array Std.U32 256#usize)
    (hlen : input.length ≤ out.length)
    (hp : pos0.val ≤ input.length) (hntok : ntok0.val ≤ pos0.val)
    (hdec : LZ77.decode (toks out ntok0.val) = some ((bytes input).take pos0.val)) :
    slot.main_parse input out pos0 ntok0 hist ⦃ fun r =>
      r.1.val ≤ input.length ∧
      r.2.length = out.length ∧
      LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
  rw [slot.main_parse]
  have h0 := decode_nil input out
  have hlenv := Slice.len_val input
  try simp only [lift, Array.to_slice_mut, alloc.vec.Vec.deref_mut, bind_tc_ok]
  step*
  all_goals (repeat (first
    | (refine ⟨by (first | omega | scalar_tac), by (first | omega | scalar_tac), valid_of_decode (by assumption) (by (first | omega | scalar_tac))⟩)
    | (refine ⟨by (first | omega | scalar_tac), by (first | omega | scalar_tac), by assumption⟩)
    | (intro hc; (try step*))
    | (casesm* _ × _; (try simp only [] at *); (try step*))
    | (split <;> (try step*))
    | (step <;> (try step*))))
  all_goals (try (first | omega | scalar_tac))
end P0Scope98
open scoped Submission.P0Scope98
end
open scoped Submission.P0Scope98

section
open scoped Submission.A2StepScope33
attribute [local step] Submission.entropy256_spec
attribute [local step] Submission.fl_sample_spec
attribute [local step] Submission.fl_stats_spec
namespace P0Scope99
@[scoped step]
theorem _root_.Submission.parse_spec (input : Slice Std.U8) (out : Slice Std.U32)
    (hlen : input.length ≤ out.length) :
    slot.parse input out ⦃ fun r =>
      r.1.val ≤ input.length ∧
      r.2.length = out.length ∧
      LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
  rw [slot.parse]
  have h0 := decode_nil input out
  have hlenv := Slice.len_val input
  try simp only [lift, Array.to_slice_mut, alloc.vec.Vec.deref_mut, bind_tc_ok]
  step*
  all_goals (repeat (first
    | (refine ⟨by (first | omega | scalar_tac), by (first | omega | scalar_tac), valid_of_decode (by assumption) (by (first | omega | scalar_tac))⟩)
    | (refine ⟨by (first | omega | scalar_tac), by (first | omega | scalar_tac), by assumption⟩)
    | (intro hc; (try step*))
    | (casesm* _ × _; (try simp only [] at *); (try step*))
    | (split <;> (try step*))
    | (step <;> (try step*))))
  all_goals (try (first | omega | scalar_tac))
end P0Scope99
open scoped Submission.P0Scope99
end
open scoped Submission.P0Scope99

end Submission
