import Lz77
import Slot
namespace Submission
open Aeneas Aeneas.Std Result ControlFlow
open LZ77 (toks bytes)
set_option hygiene false in
local notation "Y112P0!" => (fun _ => True)
set_option hygiene false in
local notation "Y112P1!" => (fun r => r.1.val  ≤  input.length  ∧  r.2.length = out.length  ∧  LZ77.Valid (bytes input) (toks r.2 r.1.val))
set_option hygiene false in
local notation "Y112P2!" => (fun r => r.1.val  ≤  input.length  ∧  r.2.length = out0.length  ∧  LZ77.decode (toks r.2 r.1.val) = some (bytes input))
set_option hygiene false in
local notation "Y112P3!" => (fun r => r.1.val  ≤  input.length  ∧  r.2.length = out.length  ∧  LZ77.decode (toks r.2 r.1.val) = some (bytes input))
set_option hygiene false in
local notation "Y112P4!" => (fun r => r.2.2.2.2.2.2.2.2.2.2.val  ≤  need.val  ∧  p0.val  ≤  r.2.2.2.2.2.2.2.2.2.1.val  ∧  r.2.2.2.2.2.2.2.2.2.1.val  ≤  p0.val + 511 * r.2.2.2.2.2.2.2.2.2.2.val)
set_option hygiene false in
local notation "Y112P5!" => (fun r => True)
set_option hygiene false in
local notation "Y112P6!" => (fun l => l.val  ≤  cap.val  ∧  Matches input a.val b.val l.val)
set_option hygiene false in
local notation "Y112P7!" => (fun r => prev.val  ≤  r.2.2.1.val  ∧  r.2.2.1.val  ≤  i.val + 258  ∧  r.2.2.2.val  ≤  32768  ∧  r.2.1.val  ≤  32767)
local notation "U" => Slice Std.U32
local notation "I" => Slice Std.U8
local notation "O" => Std.Array Std.Usize
local notation "C" => Std.Array Std.U32
local notation "G" => Std.Array Std.U8
local notation "V" => List Std.U32
local notation "R" => Std.Usize
local notation "W" => Std.U32
set_option aeneas.step.nla false
set_option linter.unusedTactic false
set_option linter.unreachableTactic false

theorem dp_ite3_spec {α:Type} {a b c:Prop} [Decidable a] [Decidable b] [Decidable c]
    {X Y:Result α} {P:α  →  Prop} (hX:a  →  b  →  ¬c  →  X ⦃ P ⦄) (hY:Y ⦃ P ⦄) :
    (if a then (if b then (if c then Y else X) else Y) else Y) ⦃ P ⦄ := by
  by_cases ha:a
  · rw [if_pos ha]
    by_cases hb:b
    · rw [if_pos hb]
      by_cases hc:c
      · rw [if_pos hc];exact hY
      · rw [if_neg hc];exact hX ha hb hc
    · rw [if_neg hb];exact hY
  · rw [if_neg ha];exact hY

theorem dp_ite2_spec {α:Type} {a b:Prop} [Decidable a] [Decidable b]
    {X Y:Result α} {P:α  →  Prop} (hX:a  →  b  →  X ⦃ P ⦄) (hY:Y ⦃ P ⦄) :
    (if a then (if b then X else Y) else Y) ⦃ P ⦄ := by
  by_cases ha:a
  · rw [if_pos ha]
    by_cases hb:b
    · rw [if_pos hb];exact hX ha hb
    · rw [if_neg hb];exact hY
  · rw [if_neg ha];exact hY
theorem dp_ite_spec {α:Type} {c:Prop} [Decidable c] {A B:Result α} {P:α  →  Prop}
    (hA:c  →  A ⦃ P ⦄) (hB:¬c  →  B ⦃ P ⦄):(if c then A else B) ⦃ P ⦄ := by
  by_cases h:c
  · rw [if_pos h];exact hA h
  · rw [if_neg h];exact hB h
theorem dp_sat_sub_val (x y:R) :
    (core.num.Usize.saturating_sub x y).val = x.val - y.val := by
  have hx := x.hBounds
  show (BitVec.ofNat _ (max 0 (x.val - y.val))).toNat = x.val - y.val
  rw [BitVec.toNat_ofNat, Nat.zero_max]
  exact Nat.mod_eq_of_lt (lt_of_le_of_lt (Nat.sub_le _ _) hx)

set_option maxRecDepth 8192
set_option maxHeartbeats 4000000

@[local step]
theorem SFadjust_loop_spec (lit_c len_c : Std.Array Std.U32 256#usize)
    (be seam x : Std.Usize) (hx : x.val ≤ 256) :
    slot.SFadjust_loop lit_c len_c be seam x ⦃ fun _ => True ⦄ := by
  rw [slot.SFadjust_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, x') => 256 - x'.val)
    (inv := fun (_, _, x') => x'.val ≤ 256)
  · rintro ⟨l', c', x'⟩ hx'
    simp only [slot.SFadjust_loop.body, lift]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · exact hx

@[local step]
theorem SFadjust_spec (bstart : alloc.vec.Vec Std.U32) (b n : Std.Usize)
    (lit_c len_c : Std.Array Std.U32 256#usize) :
    slot.SFadjust bstart b n lit_c len_c ⦃ fun _ => True ⦄ := by
  simp only [slot.SFadjust, lift]
  step*
  repeat' (split <;> step*)
  all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))


set_option hygiene false in
local notation "Y127U1!" q0__:max => (by
  rw [q0__]
  have hmax:input.length  ≤  Std.Usize.max := Std.Slice.length_ineq input
  step*
  intro hvalid
  have hl:l = len := by simpa using hvalid
  subst hl
  refine ⟨by scalar_tac, by scalar_tac, by scalar_tac, by scalar_tac, by scalar_tac,
    by scalar_tac, ?_⟩
  rw [← src_post1]
  exact l_post2)
set_option hygiene false in
local notation "Y127U2!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, p) => n.val - p.val)
    (inv := fun (out, ntok, p) => p.val  ≤  n.val  ∧  ntok.val  ≤  p.val  ∧  out.length = out0.length  ∧ 
      LZ77.decode (toks out ntok.val) = some ((bytes input).take p.val))
  · rintro ⟨out, ntok, p⟩ ⟨hp, hnt, hlen, hde⟩
    simp only [q1__]
    have hmax:input.length  ≤  Std.Usize.max := Std.Slice.length_ineq input
    split
    case isTrue hlt =>
      have hntok_lt:ntok.val < out.length := by scalar_tac
      step*
      · -- `check` accepted `(len, dist)`: write the match token, advance `len`
        obtain ⟨h3, h258, hd1, hd32k, hdp, hend, hm⟩ := valid_post (by assumption)
        have htok:tok.val = LZ77.mkMatch dist.val len.val := by
          simp only [LZ77.mkMatch, LZ77.MATCH_BASE]
          scalar_tac
        refine ⟨by scalar_tac, by scalar_tac, by rw [s_post];simpa using hlen, ?_, by scalar_tac⟩
        rw [s_post, show ntok1.val = ntok.val + 1 by scalar_tac,
          show p1.val = p.val + len.val by scalar_tac]
        exact emit_match input out ntok p.val dist.val len.val tok hde hntok_lt hd1 hdp hd32k
          h3 h258 hend hm htok
      · -- anything else: write the literal `input[p]`, advance 1
        have hlit:lit.val = (bytes input)[p.val]! := by
          rw [bytes_getElem! input p.val (by scalar_tac)]
          scalar_tac
        refine ⟨by scalar_tac, by scalar_tac, by rw [s_post];simpa using hlen, ?_, by scalar_tac⟩
        rw [s_post, show ntok1.val = ntok.val + 1 by scalar_tac,
          show p1.val = p.val + 1 by scalar_tac]
        exact emit_lit input out ntok p.val lit hde (by scalar_tac) hntok_lt hlit
    case isFalse hge =>
      have hpn:p.val = input.length := by scalar_tac
      refine ⟨by scalar_tac, hlen, ?_⟩
      rw [hde, hpn]
      simp
  · exact ⟨hp0, hntok0, rfl, hdec0⟩)
set_option hygiene false in
local notation "Y127U3!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun (l_, _) => hi.val + 1 - l_.val)
    (inv := fun _ => True)
  · rintro ⟨l_, best_⟩ _
    simp only [q1__]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial)
set_option hygiene false in
local notation "Y127U4!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, z_) => cl.val - z_.val)
    (inv := fun (cost_, _) => cost_.length = cost.length)
  · rintro ⟨cost_, z_⟩ hinv
    simp only [q1__]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · rfl)
set_option hygiene false in
local notation "Y127U5!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, j_) => top.val - j_.val)
    (inv := fun (_, bd_, prev_, pd_, _) => prev.val  ≤  prev_.val  ∧  prev_.val  ≤  i.val + 258  ∧ 
      pd_.val  ≤  32768  ∧  bd_.val  ≤  32767)
  · rintro ⟨best_, bd_, prev_, pd_, j_⟩ ⟨hp0, hp1, hpd_, hbd_⟩
    simp only [q1__]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact ⟨le_refl _, hprev, hpd, hbd⟩)
set_option hygiene false in
local notation "Y127U6!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, i_, _, _, _) => i_.val)
    (inv := fun ((cost_:alloc.vec.Vec W), (ch_:alloc.vec.Vec W), (i_:R), _,
        (xl_:R), (xd_:R)) =>
      cost_.length = cl.val  ∧  ch_.length = ch.length  ∧  i_.val  ≤  i.val  ∧  xl_.val  ≤  258  ∧  xd_.val  ≤  32768)
  · rintro ⟨cost_, ch_, i_, e_, xl_, xd_⟩ ⟨hc_, hch_, hi_, hxl_, hxd_⟩
    simp only [q1__]
    step*
    apply WP.spec_bind (Pₘ := fun (top:R) => top.val  ≤  mb.length)
    · split <;> step* <;> scalar_tac
    rintro top htop
    step*
    apply WP.spec_bind (Pₘ := fun (el:R) => el.val  ≤  258)
    · split <;> step* <;> scalar_tac
    rintro el hel
    step*
    apply WP.spec_bind (Pₘ := fun (x:R  ×  R  ×  W  ×  W) =>
      x.1.val  ≤  258  ∧  x.2.1.val  ≤  32768  ∧  x.2.2.2.val  ≤  32767)
    · repeat' (split <;> step*)
      all_goals scalar_tac
    rintro ⟨xl1, xd1, best2, bd1⟩ ⟨hxl1, hxd1, hbd1⟩
    step*
    apply WP.spec_bind (Pₘ := fun (x:alloc.vec.Vec W  ×  W) => x.1.length = cost_.length)
    · split <;> step* <;> scalar_tac
    rintro ⟨cost1, i23⟩ hc1
    step*
    scalar_tac
  · exact ⟨hcl.symm, rfl, le_refl _, hxl, hxd⟩)
set_option hygiene false in
local notation "Y127U7!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun (zf_, b_) => 512 - b_.val)
    (inv := fun _ => True)
  · rintro ⟨zf_, b_⟩ _
    simp only [q1__]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial)
set_option hygiene false in
local notation "Y127U8!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun (zd_, b_) => 32 - b_.val)
    (inv := fun _ => True)
  · rintro ⟨zd_, b_⟩ _
    simp only [q1__]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial)
set_option hygiene false in
local notation "Y127U9!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun (lf_, b_) => 512 - b_.val)
    (inv := fun _ => True)
  · rintro ⟨lf_, b_⟩ _
    simp only [q1__]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial)
set_option hygiene false in
local notation "Y127U10!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun (df_, b_) => 32 - b_.val)
    (inv := fun _ => True)
  · rintro ⟨df_, b_⟩ _
    simp only [q1__]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial)
set_option hygiene false in
local notation "Y127U11!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, i_) => n.val + 1 - i_.val)
    (inv := fun (cost_, i_) => cost_.length = i_.val)
  · rintro ⟨cost_, i_⟩ hc_
    simp only [q1__]
    step*
    repeat' (split <;> step*)
    all_goals try simp only [alloc.vec.Vec.length, *, List.length_append, List.length_singleton]
    all_goals scalar_tac
  · exact hc)
set_option hygiene false in
local notation "Y127U12!" q0__:max => (by
  rw [q0__]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac)
set_option hygiene false in
local notation "Y127U13!" q0__:max => (by
  rw [q0__]
  step*
  refine ⟨by assumption, by assumption, ?_⟩
  unfold LZ77.Valid
  assumption)
set_option hygiene false in
local notation "Y127U14!" q0__:max => (by
 rw [q0__]
 step*
 all_goals repeat' (split <;> step*))
namespace EA
open Aeneas Aeneas.Std Result ControlFlow
open LZ77 (toks bytes)
set_option maxRecDepth 8192
set_option maxHeartbeats 4000000
namespace EA
open Aeneas Aeneas.Std Result ControlFlow
set_option maxRecDepth 8192
set_option maxHeartbeats 1000000
set_option linter.unusedTactic false
set_option linter.unreachableTactic false
set_option linter.unusedSimpArgs false
set_option linter.unusedVariables false
open LZ77 (toks bytes bytes_getElem! Matches emit_lit emit_match)
@[step]
theorem u0 {α:Type} (x:α):lift x ⦃ fun y => y = x ⦄ := by
  simp [lift, WP.spec_ok]
@[step]
theorem u1 (v:U) (i:R):slot.Z168 v i ⦃ Y112P0! ⦄ := by
  rw [slot.Z168];split <;> step*
@[local scalar_tac x &&& y]
theorem u2 (x y:Nat):x &&& y  ≤  y := Nat.and_le_right
@[local scalar_tac x >>> y]
theorem u3 (x y:Nat):x >>> y  ≤  x := Nat.shiftRight_le x y
theorem u4:32  ≤  System.Platform.numBits := by
  cases System.Platform.numBits_eq <;> simp [*]
@[local scalar_tac System.Platform.numBits]
theorem u5:32  ≤  System.Platform.numBits := u4
theorem u6 {w:Nat} (x:BitVec w):BitVec.leadingZeros x  ≤  w := by
  unfold BitVec.leadingZeros;split <;> omega
theorem u7 (x:W) :
    (core.num.U32.leading_zeros x).val = BitVec.leadingZeros x.bv := by
  simp only [core.num.U32.leading_zeros, UScalar.val]
  have := u6 x.bv
  apply Nat.mod_eq_of_lt
  simp at this ⊢
  omega
theorem lz32_eq (x:W) (h:x.val ≠ 0) :
    (core.num.U32.leading_zeros x).val = 31 - Nat.log 2 x.val := by
  rw [u7]
  unfold BitVec.leadingZeros
  have hx:x.bv ≠ 0 := by
    intro h0;apply h;show x.bv.toNat = 0;rw [h0];rfl
  rw [if_neg hx, UScalar.bv_toNat]
  omega
theorem lz32_le (x:W):(core.num.U32.leading_zeros x).val  ≤  32 := by
  rw [u7];exact u6 x.bv
theorem u9 (x:W) (k:Nat) (h:2 ^ k  ≤  x.val) :
    (core.num.U32.leading_zeros x).val + k  ≤  31 := by
  have hx:x.val ≠ 0 := by have := Nat.one_le_two_pow (n := k);omega
  rw [lz32_eq x hx]
  have hk:k  ≤  Nat.log 2 x.val := Nat.le_log_of_pow_le (by norm_num) h
  have:x.val < 2 ^ 32 := by scalar_tac
  have hl:Nat.log 2 x.val < 32 := Nat.log_lt_of_lt_pow (by omega) this
  omega
theorem u10 (x:W) (k:Nat) (h:x.val < 2 ^ k) :
    32 - k  ≤  (core.num.U32.leading_zeros x).val := by
  by_cases hx:x.val = 0
  · rw [u7];unfold BitVec.leadingZeros
    have:x.bv = 0 := by
      apply BitVec.eq_of_toNat_eq;rw [UScalar.bv_toNat];simpa using hx
    rw [if_pos this];omega
  · rw [lz32_eq x hx]
    have hl:Nat.log 2 x.val < k := Nat.log_lt_of_lt_pow hx h
    omega
theorem u11 (x:Std.U64) :
    (core.num.U64.leading_zeros x).val = BitVec.leadingZeros x.bv := by
  simp only [core.num.U64.leading_zeros, UScalar.val]
  have := u6 x.bv
  apply Nat.mod_eq_of_lt
  simp at this ⊢
  omega
theorem u12 (x:Std.U64):(core.num.U64.leading_zeros x).val  ≤  64 := by
  rw [u11];exact u6 x.bv
@[local scalar_tac core.num.U32.leading_zeros x]
theorem u13 (x:W) :
    (core.num.U32.leading_zeros x).val  ≤  32  ∧ 
      (x.val = 0  ∨  (core.num.U32.leading_zeros x).val  ≤  31) := by
  refine ⟨lz32_le x, ?_⟩
  by_cases h:x.val = 0
  · exact Or.inl h
  · right;rw [lz32_eq x h];omega
@[local scalar_tac core.num.U64.leading_zeros x]
theorem u14 (x:Std.U64):(core.num.U64.leading_zeros x).val  ≤  64 := u12 x
def u15 {ty:UScalarTy} (l:List (UScalar ty)) (B:Nat):Prop :=
  ∀ j (h:j < l.length), (l[j]).val  ≤  B
theorem u16 {ty:UScalarTy} {l:List (UScalar ty)} {B:Nat} (hl:u15 l B)
    (j:Nat) (hj:j < l.length):(l[j]).val  ≤  B := hl j hj
theorem u16! {ty:UScalarTy} {l:List (UScalar ty)} {B:Nat} (hl:u15 l B)
    (j:Nat) (hj:j < l.length):(l[j]!).val  ≤  B := by
  rw [List.getElem!_eq_getElem?_getD, List.getElem?_eq_getElem hj];exact hl j hj
theorem u17 {ty:UScalarTy} {l:List (UScalar ty)} {B B':Nat} (hl:u15 l B)
    (h:B  ≤  B'):u15 l B' := fun j hj => Nat.le_trans (hl j hj) h
theorem LeAll_replicate {ty:UScalarTy} (n:Nat) (x:UScalar ty) (B:Nat) (h:x.val  ≤  B) :
    u15 (List.replicate n x) B := by
  intro j hj;simp [List.getElem_replicate];exact h
theorem u18 {ty:UScalarTy} {l:List (UScalar ty)} {B:Nat} (hl:u15 l B)
    (i:Nat) (x:UScalar ty) (hx:x.val  ≤  B):u15 (l.set i x) B := by
  intro j hj
  rw [List.getElem_set]
  split
  · exact hx
  · exact hl j (by simpa using hj)
theorem u19 {ty:UScalarTy} {l:List (UScalar ty)} {B:Nat} (hl:u15 l B)
    (x:UScalar ty) (hx:x.val  ≤  B):u15 (l ++ [x]) B := by
  intro j hj
  rw [List.getElem_append]
  split
  · exact hl j (by assumption)
  · simp;exact hx
theorem u20 {ty:UScalarTy} {l:List (UScalar ty)} {t:Nat} (hl:u15 l t)
    (i:Nat) (x:UScalar ty) (hx:x.val  ≤  t + 1):u15 (l.set i x) (t + 1) :=
  u18 (u17 hl (Nat.le_succ t)) i x hx
theorem u21:0 < slot.Z7.val  ∧  slot.Z7.val  ≤  65536 := by
  simp [slot.Z7]
theorem u22 (input:I) (a b cap l0:R)
    (ha:a.val + cap.val  ≤  input.length) (hb:b.val + cap.val  ≤  input.length)
    (hl0:l0.val  ≤  cap.val) (h0:Matches input a.val b.val l0.val) :
    slot.Z170_loop input a b cap l0 ⦃ Y112P6! ⦄ := by
  rw [slot.Z170_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun l => cap.val - l.val)
    (inv := fun l => l.val  ≤  cap.val  ∧  Matches input a.val b.val l.val)
  · rintro l ⟨hle, hinv⟩
    simp only [slot.Z170_loop.body]
    have hmax:input.length  ≤  Std.Usize.max := Std.Slice.length_ineq input
    step*
    refine ⟨by scalar_tac, ?_, by scalar_tac⟩
    rw [show l1.val = l.val + 1 by scalar_tac]
    apply LZ77.Matches.succ hinv
    rw [getElem!_pos _ _ (by scalar_tac), getElem!_pos _ _ (by scalar_tac)]
    simp_all
  · exact ⟨hl0, h0⟩
@[step]
theorem u23 (input:I) (a b cap:R)
    (ha:a.val + cap.val  ≤  input.length) (hb:b.val + cap.val  ≤  input.length) :
    slot.Z170 input a b cap ⦃ Y112P6! ⦄ :=
  u22 input a b cap 0#usize ha hb (by scalar_tac) (LZ77.Matches.zero input a.val b.val)
@[step]
theorem u24 (input:I) (p len dist:R) :
    slot.Z166 input p len dist ⦃ fun valid => valid = true  → 
      3  ≤  len.val  ∧  len.val  ≤  258  ∧  1  ≤  dist.val  ∧  dist.val  ≤  32768  ∧  dist.val  ≤  p.val  ∧ 
      p.val + len.val  ≤  input.length  ∧  Matches input (p.val - dist.val) p.val len.val ⦄ := Y127U1! slot.Z166
theorem u25 (input:I) (plan out0:U)
    (n ntok0 p0:R) (hn:n.val = input.length) (hout:input.length  ≤  out0.length)
    (hp0:p0.val  ≤  n.val) (hntok0:ntok0.val  ≤  p0.val)
    (hdec0:LZ77.decode (toks out0 ntok0.val) = some ((bytes input).take p0.val)) :
    slot.Z167_loop input plan out0 n ntok0 p0 ⦃ Y112P2! ⦄ := Y127U2! slot.Z167_loop slot.Z167_loop.body
@[step]
theorem u26 (input:I) (plan out:U)
    (hout:input.length  ≤  out.length) :
    slot.Z167 input plan out ⦃ Y112P3! ⦄ := by
  rw [slot.Z167]
  exact u25 input plan out (Std.Slice.len input) 0#usize 0#usize (by simp) hout
    (by simp) (by simp) (by simp [toks, LZ77.decode])
@[step]
theorem u27 (n:R) (v0:alloc.vec.Vec W) (i0:R)
    (hv:v0.length = i0.val) (hi:i0.val  ≤  n.val) :
    slot.Z182_loop n v0 i0 ⦃ fun v => v.length = n.val ⦄ := by
  rw [slot.Z182_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, i) => n.val - i.val)
    (inv := fun (v, i) => v.length = i.val  ∧  i.val  ≤  n.val)
  · rintro ⟨v, i⟩ ⟨hvi, hin⟩
    simp only [slot.Z182_loop.body]
    step*
    all_goals have hlen:v1.length = v.length + 1 := by simp [v1_post]
    all_goals scalar_tac
  · exact ⟨hv, hi⟩
@[step]
theorem u28 (n:R):slot.Z182 n ⦃ fun v => v.length = n.val ⦄ := by
  rw [slot.Z182]
  step*
  simp [alloc.vec.Vec.with_capacity]
theorem u29 (a:R) :
    (core.num.Usize.wrapping_add a 1024#usize).val - a.val  ≤  1024 := by
  rw [core.num.Usize.wrapping_add_val_eq, UScalar.size_UScalarTyUsize]
  have ha:a.val < Usize.size := by scalar_tac
  have hs:1024 < Usize.size := by scalar_tac
  have h1:(1024#usize).val = 1024 := by simp
  rw [h1]
  by_cases h:a.val + 1024 < Usize.size
  · rw [Nat.mod_eq_of_lt h];omega
  · rw [Nat.mod_eq_sub_mod (by omega), Nat.mod_eq_of_lt (by omega)];omega
set_option hygiene false in
local notation "T1!" q0__:max => (by
  rw [q0__]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac)
theorem u30 (n:R) (B:Nat):u15 (Array.repeat n 0#usize).val B := by
  rw [Array.repeat_val];exact LeAll_replicate _ _ _ (by simp)
theorem u31 {ty:UScalarTy} {l:List (UScalar ty)} {B:Nat} (hl:u15 l B)
    {x:UScalar ty} {j:Nat} {hj:j < l.length} (hx:x = l[j]):x.val  ≤  B := by
  subst hx;exact hl j hj
theorem u33:u15 slot.Z1.val 64 := by
  unfold slot.Z1 u15;simp only [Array.make];decide
theorem u34:256  ≤  slot.Z5.val  ∧  slot.Z5.val  ≤  65536  ∧ 
    slot.Z5.val + 512  ≤  slot.Z5.val * slot.Z4.val  ∧ 
    slot.Z5.val * slot.Z4.val  ≤  1048576 := by
  simp
theorem u35:1  ≤  slot.Z0.val  ∧  slot.Z0.val  ≤  32 := by
  simp
theorem u36:0 < slot.Z7.val  ∧  slot.Z7.val  ≤  16384  ∧ 
    slot.Z2.val  ≤  65536  ∧  slot.Z6.val ≠ 0 := by
  simp
theorem u37 {α:Type} (c:Prop) [Decidable c] (a b:α) :
    (if c then (ok a:Result α) else ok b) = ok (if c then a else b) := by
  split <;> rfl
theorem u38 (x y:R) :
    (core.num.Usize.saturating_add x y).val = min Std.Usize.max (x.val + y.val) := by
  have hsz:Std.Usize.max < 2 ^ UScalarTy.Usize.numBits := by
    rw [Std.Usize.max_def, Std.Usize.numBits]
    have:0 < 2 ^ UScalarTy.Usize.numBits := Nat.two_pow_pos _
    omega
  show (BitVec.ofNat _ (min (UScalar.max UScalarTy.Usize) (x.val + y.val))).toNat = _
  rw [BitVec.toNat_ofNat, UScalar.max_USize_eq, Nat.mod_eq_of_lt (by omega)]
@[local scalar_tac core.num.Usize.saturating_add x y]
theorem u39 (x y:R) :
    (core.num.Usize.saturating_add x y).val = min Std.Usize.max (x.val + y.val) := u38 x y
theorem u40 {α β:Type} (c:Prop) [Decidable c] (a a':α) (b b':β) :
    (if c then (a, b) else (a', b')) = (if c then a else a', if c then b else b') := by
  split <;> rfl
theorem u41 {ty:UScalarTy} (n:R) (x:UScalar ty) (B:Nat) (h:x.val  ≤  B) :
    u15 (Array.repeat n x).val B := by
  rw [Array.repeat_val];exact LeAll_replicate _ _ _ h
theorem u42 {n:R} {a r:C n} {i:R} {v:W} {B:Nat}
    (hr:r = a.set i v) (ha:u15 a.val B) (hv:v.val  ≤  B):u15 r.val B := by
  rw [hr, Array.set_val_eq];exact u18 ha _ _ hv
@[step]
theorem u43 (x) :
    slot.Z158 x ⦃ Y112P0! ⦄ := by
  rw [slot.Z158]
  step*
@[step]
theorem u44 (len) :
    slot.Z150 len ⦃ fun r => r.val  ≤  28 ⦄ := by
  rw [slot.Z150]
  split
  · step*
  · split
    · step*
    · step*
      all_goals
        have hx:x.val = len.val - 3 := by
          rw [x_post, UScalar.cast_val_mod_pow_of_inBounds_eq _ _ (by scalar_tac)];scalar_tac
        have h1 := u9 x 3 (by scalar_tac)
        have h2 := u10 x 8 (by scalar_tac)
        subst i1_post
        scalar_tac
@[step]
theorem u45 (lf) :
    slot.Z163_loop0 lf 0#usize ⦃ fun r => u15 r.val 0 ⦄ := by
  rw [slot.Z163_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, k) => 512 - k.val)
    (inv := fun (lf', k) => k.val  ≤  512  ∧  ∀ j (hj:j < k.val) (hl:j < lf'.val.length), (lf'.val[j]).val = 0)
  · rintro ⟨lf', k⟩ ⟨hk, hz⟩
    simp only [slot.Z163_loop0.body]
    step*
    · -- one more entry zeroed
      refine ⟨by scalar_tac, ?_, by scalar_tac⟩
      intro j hj hl
      subst a_post
      simp only [Array.set_val_eq, List.getElem_set]
      split
      · rfl
      · exact hz j (by scalar_tac) (by simpa using hl)
    · -- exit: k = 512 covers the whole array
      intro j hl
      have:k.val = 512 := by scalar_tac
      have hl':j < 512 := by simpa using hl
      rw [hz j (by omega) hl]
  · exact ⟨by simp, fun j hj => by simp at hj⟩
@[step]
theorem u46 (df) :
    slot.Z163_loop1 df 0#usize ⦃ fun r => u15 r.val 0 ⦄ := by
  rw [slot.Z163_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, k) => 32 - k.val)
    (inv := fun (df', k) => k.val  ≤  32  ∧  ∀ j (hj:j < k.val) (hl:j < df'.val.length), (df'.val[j]).val = 0)
  · rintro ⟨df', k⟩ ⟨hk, hz⟩
    simp only [slot.Z163_loop1.body]
    step*
    · refine ⟨by scalar_tac, ?_, by scalar_tac⟩
      intro j hj hl
      subst a_post
      simp only [Array.set_val_eq, List.getElem_set]
      split
      · rfl
      · exact hz j (by scalar_tac) (by simpa using hl)
    · intro j hl
      have:k.val = 32 := by scalar_tac
      have hl':j < 32 := by simpa using hl
      rw [hz j (by omega) hl]
  · exact ⟨by simp, fun j hj => by simp at hj⟩
@[step]
theorem u47 (s:I) (ch) (lim need:R) (lf df) (i t:R)
    (hlim:lim.val  ≤  2 ^ 31) (hls:lim.val  ≤  s.length) (hneed:need.val  ≤  2 ^ 31)
    (hlf:u15 lf.val t.val) (hdf:u15 df.val t.val) :
    slot.Z163_loop2 s ch lim need lf df i t ⦃ fun r => i.val  ≤  r.2.2.1.val  ∧  r.2.2.2.val  ≤  max t.val need.val  ∧ 
      r.2.2.1.val  ≤  max i.val (lim.val + 511)  ∧  r.2.2.1.val + 511 * t.val  ≤  i.val + 511 * r.2.2.2.val ⦄ := by
  rw [slot.Z163_loop2]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, t') => need.val - t'.val)
    (inv := fun (lf', df', i', t') => u15 lf'.val t'.val  ∧  u15 df'.val t'.val  ∧ 
      i.val  ≤  i'.val  ∧  t'.val  ≤  max t.val need.val  ∧ 
      i'.val  ≤  max i.val (lim.val + 511)  ∧  i'.val + 511 * t.val  ≤  i.val + 511 * t'.val)
  · rintro ⟨lf', df', i', t'⟩ ⟨hlf', hdf', hi', ht', hi2', hi3'⟩
    simp only [slot.Z163_loop2.body]
    step*
    apply WP.spec_bind (Pₘ := fun (x:Std.Array W 512#usize  ×  Std.Array W 32#usize  ×  R) =>
      u15 x.1.val (t'.val + 1)  ∧  u15 x.2.1.val (t'.val + 1)  ∧  i'.val < x.2.2.val  ∧  x.2.2.val  ≤  i'.val + 511)
    · split
      · -- a match: one length counter and one distance counter go up
        step*
        all_goals try (have := u16 hlf' i6.val (by scalar_tac))
        all_goals try (have := u16 hdf' i14.val (by scalar_tac))
        all_goals try scalar_tac
        refine ⟨?_, ?_, by scalar_tac, by scalar_tac⟩
        · rw [a_post, Array.set_val_eq];exact u20 hlf' _ _ (by scalar_tac)
        · rw [a1_post, Array.set_val_eq];exact u20 hdf' _ _ (by scalar_tac)
      · -- a literal: one literal counter goes up
        step*
        all_goals try (have := u16 hlf' i5.val (by scalar_tac))
        all_goals try scalar_tac
        refine ⟨?_, u17 hdf' (by omega), by scalar_tac, by scalar_tac⟩
        rw [a_post, Array.set_val_eq];exact u20 hlf' _ _ (by scalar_tac)
    · rintro ⟨lf1, df1, i3⟩ ⟨h1, h2, h3, h4⟩
      step*
      refine ⟨?_, ?_, by scalar_tac, by scalar_tac, by scalar_tac, by scalar_tac, by scalar_tac⟩
      · rw [show t1.val = t'.val + 1 by scalar_tac];exact h1
      · rw [show t1.val = t'.val + 1 by scalar_tac];exact h2
  · exact ⟨hlf, hdf, le_refl _, by omega, by omega, by omega⟩
@[step]
theorem u48 (s:I) (ch) (p0 lim need:R) (lf df)
    (hlim:lim.val  ≤  2 ^ 31) (hls:lim.val  ≤  s.length) (hneed:need.val  ≤  2 ^ 31) :
    slot.Z163 s ch p0 lim need lf df ⦃ fun r => p0.val  ≤  r.1.1.val  ∧  r.1.2.val  ≤  need.val  ∧ 
      r.1.1.val  ≤  max p0.val (lim.val + 511)  ∧  r.1.1.val  ≤  p0.val + 511 * r.1.2.val ⦄ := T1! slot.Z163
@[local step]
theorem u49 (cost:U) (lc) (i hi:R) (base best l)
    (hhi:hi.val < 512) (hc:i.val + hi.val < cost.length) :
    slot.Z181_loop cost lc i hi base l best ⦃ Y112P0! ⦄ := Y127U3! slot.Z181_loop slot.Z181_loop.body
@[local step]
theorem u50 (cost:U) (lc i lo hi base width) :
    slot.Z181 cost lc i lo hi base width ⦃ Y112P0! ⦄ := T1! slot.Z181
@[local step]
theorem u51 (pe:R) (cost) (cl z:R) (hpe:pe.val  ≤  2 ^ 31) (hcl:cl.val = cost.length) :
    slot.Z143_loop0 pe cost cl z ⦃ fun r => r.length = cost.length ⦄ := Y127U4! slot.Z143_loop0 slot.Z143_loop0.body
@[local step]
theorem u52 (tail:R) (mb lc dc) (cost:alloc.vec.Vec W) (cl i:R) (bias best bd) (prev pd:R) (j top:R)
    (hcl:cl.val = cost.length) (hi:i.val  ≤  2 ^ 31) (htop:top.val  ≤  mb.length)
    (hprev:prev.val  ≤  i.val + 258) (hpv:i.val  ≤  prev.val) (hpd:pd.val  ≤  32768) (hbd:bd.val  ≤  32767) :
    slot.Z143_loop1_loop0 mb lc dc cost tail cl i bias best bd prev pd j top ⦃ Y112P7! ⦄ := Y127U5! slot.Z143_loop1_loop0 slot.Z143_loop1_loop0.body
@[local step]
theorem u53 (tail:R) (s:I) (mp mb:alloc.vec.Vec W) (p0 lit lc dc) (cost ch:alloc.vec.Vec W)
    (cl i e xl xd:R)
    (hcl:cl.val = cost.length) (hi:i.val < cl.val) (hmp:i.val < mp.length) (hs:i.val  ≤  s.length)
    (hch:i.val  ≤  ch.length) (hi31:i.val  ≤  2 ^ 31) (hxl:xl.val  ≤  258) (hxd:xd.val  ≤  32768) :
    slot.Z143_loop1 s mp mb p0 lit lc dc cost ch tail cl i e xl xd ⦃ Y112P0! ⦄ := Y127U6! slot.Z143_loop1 slot.Z143_loop1.body
@[local step]
theorem u54 (tail:R) (s:I) (mp mb) (p0 pe:R) (lit lc dc) (cost ch)
    (hpe:pe.val  ≤  2 ^ 31) :
    slot.Z143 s mp mb p0 pe lit lc dc cost ch tail ⦃ Y112P0! ⦄ := T1! slot.Z143
@[local step]
theorem u55 (lf zf b) :
    slot.Z154_loop0_loop0 lf zf b ⦃ Y112P0! ⦄ := Y127U7! slot.Z154_loop0_loop0 slot.Z154_loop0_loop0.body
@[local step]
theorem u56 (df zd b) :
    slot.Z154_loop0_loop1 df zd b ⦃ Y112P0! ⦄ := Y127U8! slot.Z154_loop0_loop1 slot.Z154_loop0_loop1.body
@[local step]
theorem u57 (tail:R) (s:I) (mp mb) (pe:R) (lit lc dc cost ch lf df zf zd) (sb st a:R)
    (hpe:pe.val  ≤  2 ^ 30) (hps:pe.val  ≤  s.length) (hsb:sb.val  ≤  a.val) (hst:st.val  ≤  a.val)
    (ha:a.val  ≤  pe.val + slot.Z5.val * slot.Z4.val) :
    slot.Z154_loop0 s mp mb pe lit lc dc cost ch lf df tail zf zd sb st a ⦃ Y112P0! ⦄ := by
  have hseg := u34
  rw [slot.Z154_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, _, _, _, _, a_) => pe.val - a_.val)
    (inv := fun (_, _, _, _, _, _, sb_, st_, a_) => sb_.val  ≤  a_.val  ∧  st_.val  ≤  a_.val  ∧ 
      a_.val  ≤  pe.val + slot.Z5.val * slot.Z4.val)
  · rintro ⟨cost_, ch_, lf_, df_, zf_, zd_, sb_, st_, a_⟩ ⟨hsb_, hst_, ha_⟩
    simp only [slot.Z154_loop0.body]
    step*
    cases ‹R  ×  R›
    step*
    all_goals scalar_tac
  · exact ⟨hsb, hst, ha⟩
@[local step]
theorem u58 (lf zf b) :
    slot.Z154_loop1 lf zf b ⦃ Y112P0! ⦄ := Y127U9! slot.Z154_loop1 slot.Z154_loop1.body
@[local step]
theorem u59 (df zd b) :
    slot.Z154_loop2 df zd b ⦃ Y112P0! ⦄ := Y127U10! slot.Z154_loop2 slot.Z154_loop2.body
@[local step]
theorem u60 (tail:R) (s:I) (mp mb) (p0 pe:R) (lit lc dc cost ch lf df)
    (hpe:pe.val  ≤  2 ^ 30) (hps:pe.val  ≤  s.length) (hp0:p0.val  ≤  pe.val) :
    slot.Z154 s mp mb p0 pe lit lc dc cost ch lf df tail ⦃ Y112P0! ⦄ := by
  have hseg := u34
  rw [slot.Z154]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac
@[step]
theorem u61 (dst a b k) :
    slot.Z141_loop0 dst a b k ⦃ Y112P0! ⦄ := by
  rw [slot.Z141_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (dst_, k_) => 512 - k_.val)
    (inv := fun _ => True)
  · rintro ⟨dst_, k_⟩ _
    simp only [slot.Z141_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial
@[step]
theorem u62 (dd x y k) :
    slot.Z141_loop1 dd x y k ⦃ Y112P0! ⦄ := by
  rw [slot.Z141_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (dd_, k_) => 32 - k_.val)
    (inv := fun _ => True)
  · rintro ⟨dd_, k_⟩ _
    simp only [slot.Z141_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial
@[step]
theorem u63 (dst a b dd x y) :
    slot.Z141 dst a b dd x y ⦃ Y112P0! ⦄ := T1! slot.Z141
@[step]
theorem u65 (x) :
    slot.Z151 x ⦃ fun r => r.val  ≤  2048 ⦄ := by
  rw [slot.Z151]
  have hlz := u13 x
  have htab := u33
  step*
  repeat' (split <;> step*)
  all_goals try (have := u16 htab i3.val (by scalar_tac))
  all_goals scalar_tac
@[step]
theorem u66 (f:W) (g:W) (hg:g.val  ≤  65536) :
    slot.Z160 f g ⦃ fun r => r.val  ≤  1152 ⦄ := T1! slot.Z160
@[step]
theorem u67 (slt:R) :
    slot.Z142 slt ⦃ fun r => r.val  ≤  slt.val / 2 ⦄ := T1! slot.Z142
@[step]
theorem u68 (slt) :
    slot.Z149 slt ⦃ fun r => r.val  ≤  5 ⦄ := T1! slot.Z149
@[step]
theorem u69 (lf tl i) :
    slot.Z155_loop0 lf tl i ⦃ Y112P0! ⦄ := by
  rw [slot.Z155_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (tl_, i_) => 286 - i_.val)
    (inv := fun _ => True)
  · rintro ⟨tl_, i_⟩ _
    simp only [slot.Z155_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial
set_option hygiene false in
local notation "T2!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun (i_, td_) => 30 - i_.val)
    (inv := fun _ => True)
  · rintro ⟨i_, td_⟩ _
    simp only [q1__]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial)
@[step]
theorem u70 (df i td) :
    slot.Z155_loop1 df i td ⦃ Y112P0! ⦄ := T2! slot.Z155_loop1 slot.Z155_loop1.body
@[step]
theorem u71 (lf lit i) (gl:W) (hgl:gl.val  ≤  65536) :
    slot.Z155_loop2 lf lit i gl ⦃ Y112P0! ⦄ := by
  rw [slot.Z155_loop2]
  apply Std.loop.spec_decr_nat
    (measure := fun (lit_, i_) => 256 - i_.val)
    (inv := fun _ => True)
  · rintro ⟨lit_, i_⟩ _
    simp only [slot.Z155_loop2.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial
@[step]
theorem u72 (lf lc i) (gl:W) (hgl:gl.val  ≤  65536) :
    slot.Z155_loop3 lf lc i gl ⦃ Y112P0! ⦄ := by
  rw [slot.Z155_loop3]
  apply Std.loop.spec_decr_nat
    (measure := fun (lc_, i_) => 258 + 1 - i_.val)
    (inv := fun _ => True)
  · rintro ⟨lc_, i_⟩ _
    simp only [slot.Z155_loop3.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial
@[step]
theorem u73 (df dc) (i:R) (gd:W) (hgd:gd.val  ≤  65536) :
    slot.Z155_loop4 df dc i gd ⦃ Y112P0! ⦄ := by
  rw [slot.Z155_loop4]
  apply Std.loop.spec_decr_nat
    (measure := fun (dc_, i_) => 30 - i_.val)
    (inv := fun _ => True)
  · rintro ⟨dc_, i_⟩ _
    simp only [slot.Z155_loop4.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial
@[step]
theorem u74 (lf df lit lc dc) :
    slot.Z155 lf df lit lc dc ⦃ Y112P0! ⦄ := T1! slot.Z155
@[step]
theorem u75 (s:I) (lf) (m i:R) (hm:m.val  ≤  s.length) (hm2:m.val  ≤  65536)
    (hlf:u15 lf.val i.val) :
    slot.Z146_loop0 s lf m i ⦃ Y112P0! ⦄ := by
  rw [slot.Z146_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, i_) => m.val - i_.val)
    (inv := fun (lf_, i_) => u15 lf_.val i_.val)
  · rintro ⟨lf_, i_⟩ hlf_
    simp only [slot.Z146_loop0.body]
    step*
    all_goals try (have := u16 hlf_ i2.val (by scalar_tac))
    all_goals try scalar_tac
    refine ⟨?_, by scalar_tac⟩
    rw [show i5.val = i_.val + 1 by scalar_tac, a_post, Array.set_val_eq]
    exact u20 hlf_ _ _ (by scalar_tac)
  · exact hlf
@[step]
theorem u76 (lf i) :
    slot.Z146_loop1 lf i ⦃ Y112P0! ⦄ := by
  rw [slot.Z146_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (lf_, i_) => 29 - i_.val)
    (inv := fun _ => True)
  · rintro ⟨lf_, i_⟩ _
    simp only [slot.Z146_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial
@[step]
theorem u77 (df i) :
    slot.Z146_loop2 df i ⦃ Y112P0! ⦄ := by
  rw [slot.Z146_loop2]
  apply Std.loop.spec_decr_nat
    (measure := fun (df_, i_) => 30 - i_.val)
    (inv := fun _ => True)
  · rintro ⟨df_, i_⟩ _
    simp only [slot.Z146_loop2.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial
@[step]
theorem u78 (s lit lc dc) :
    slot.Z146 s lit lc dc ⦃ Y112P0! ⦄ := by
  rw [slot.Z146]
  step*
  repeat' (split <;> step*)
  all_goals exact u41 _ _ _ (by simp)
@[step]
theorem u79 (sym m) (len:C 512#usize) (kraft q) (hlen:u15 len.val 15) :
    slot.Z148_loop sym m len kraft q ⦃ fun r => u15 r.val 15 ⦄ := by
  rw [slot.Z148_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun ((len_:C 512#usize), _, (q_:R)) =>
      (512 - q_.val) * 16 + (15 - (len_.val[(sym.val[q_.val]!).val % 512]!).val))
    (inv := fun (len_, _, _) => u15 len_.val 15)
  · rintro ⟨len_, kraft_, q_⟩ hlen_
    dsimp only at hlen_
    simp only [slot.Z148_loop.body]
    step*
    · -- one code gets one bit longer: the second component of the measure drops
      have hq:(sym.val[q_.val]!).val % 512 = s2.val := by
        rw [getElem!_pos sym.val q_.val (by scalar_tac), ← i_post];scalar_tac
      have ha:a.val[s2.val]! = i5 := by
        rw [a_post, Array.set_val_eq, getElem!_pos _ _ (by simp;scalar_tac), List.getElem_set_self]
      have hl:len_.val[s2.val]! = i2 := by
        rw [getElem!_pos _ _ (by scalar_tac), ← i2_post]
      refine ⟨?_, ?_⟩
      · rw [a_post, Array.set_val_eq];exact u18 hlen_ _ _ (by scalar_tac)
      · rw [hq, ha, hl];scalar_tac
    · -- the next symbol: the first component drops
      exact ⟨hlen_, by scalar_tac⟩
  · exact hlen
@[step]
theorem u80 (sym m) (len:C 512#usize) (kraft0) (hlen:u15 len.val 15) :
    slot.Z148 sym m len kraft0 ⦃ fun r => u15 r.val 15 ⦄ := by
  unfold slot.Z148
  step*
@[step]
theorem u81 (w a) (b:R) (m k) (hb:b.val  ≤  4096) :
    slot.Z152 w a b m k ⦃ fun r => r.2.1.val  ≤  a.val + 1  ∧  r.2.2.val  ≤  b.val + 1 ⦄ := T1! slot.Z152
@[step]
theorem u82 (sym freq fv) (j:R) (hj:j.val < 512) :
    slot.Z159_loop sym freq fv j ⦃ fun r => r.2.val < 512 ⦄ := by
  rw [slot.Z159_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, j_) => j_.val)
    (inv := fun (_, j_) => j_.val < 512)
  · rintro ⟨sym_, j_⟩ hinv
    simp only [slot.Z159_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact hj
@[step]
theorem u83 (sym freq m v) :
    slot.Z159 sym freq m v ⦃ Y112P0! ⦄ := T1! slot.Z159
@[step]
theorem u84 (freq n) (len:C 512#usize) (sym) (m i:R)
    (hm:m.val  ≤  i.val) (hi:i.val  ≤  512) (hlen:u15 len.val 15) :
    slot.Z147_loop0 freq n len sym m i ⦃ fun r => r.2.2.val  ≤  512  ∧  u15 r.1.val 15 ⦄ := by
  rw [slot.Z147_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, i_) => 512 - i_.val)
    (inv := fun (len_, _, m_, i_) => m_.val  ≤  i_.val  ∧  i_.val  ≤  512  ∧  u15 len_.val 15)
  · rintro ⟨len_, sym_, m_, i_⟩ ⟨hm_, hi_, hlen_⟩
    simp only [slot.Z147_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals
      refine ⟨by scalar_tac, by scalar_tac, ?_, by scalar_tac⟩
      rw [a_post, Array.set_val_eq];exact u18 hlen_ _ _ (by scalar_tac)
  · exact ⟨hm, hi, hlen⟩
@[step]
theorem u85 (freq sym m i w) :
    slot.Z147_loop1 freq sym m i w ⦃ Y112P0! ⦄ := by
  rw [slot.Z147_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (i_, w_) => m.val - i_.val)
    (inv := fun _ => True)
  · rintro ⟨i_, w_⟩ _
    simp only [slot.Z147_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial
@[step]
theorem u86 (m:R) (w par) (a b k:R) (hm:m.val  ≤  512)
    (ha:a.val  ≤  2 * k.val) (hb:b.val  ≤  2 * k.val) (hk:k.val  ≤  1024) :
    slot.Z147_loop2 m w par a b k ⦃ fun r => r.2.val  ≤  1024 ⦄ := by
  rw [slot.Z147_loop2]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, k_) => 1024 - k_.val)
    (inv := fun (_, _, a_, b_, k_) => a_.val  ≤  2 * k_.val  ∧  b_.val  ≤  2 * k_.val  ∧  k_.val  ≤  1024)
  · rintro ⟨w_, par_, a_, b_, k_⟩ ⟨ha_, hb_, hk_⟩
    simp only [slot.Z147_loop2.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact ⟨ha, hb, hk⟩
@[step]
theorem u87 (par d j) :
    slot.Z147_loop3 par d j ⦃ Y112P0! ⦄ := by
  rw [slot.Z147_loop3]
  apply Std.loop.spec_decr_nat
    (measure := fun (d_, j_) => j_.val)
    (inv := fun _ => True)
  · rintro ⟨d_, j_⟩ _
    simp only [slot.Z147_loop3.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial
@[step]
theorem u88 (len:C 512#usize) (sym m i d kraft) (hlen:u15 len.val 15) :
    slot.Z147_loop4 len sym m i d kraft ⦃ fun r => u15 r.1.val 15 ⦄ := by
  rw [slot.Z147_loop4]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, i_, _) => m.val - i_.val)
    (inv := fun (len_, _, _) => u15 len_.val 15)
  · rintro ⟨len_, i_, kraft_⟩ hlen_
    dsimp only at hlen_
    simp only [slot.Z147_loop4.body]
    step*
    repeat' (split <;> step*)
    all_goals try scalar_tac
    all_goals
      refine ⟨?_, by scalar_tac⟩
      rw [a_post, Array.set_val_eq];exact u18 hlen_ _ _ (by scalar_tac)
  · exact hlen
@[step]
theorem u89 (freq n) (len:C 512#usize) (hlen:u15 len.val 15) :
    slot.Z147 freq n len ⦃ fun r => u15 r.val 15 ⦄ := by
  rw [slot.Z147]
  step*
  repeat' (split <;> step*)
  all_goals try scalar_tac
  all_goals apply u42 (by assumption) (by assumption) (by scalar_tac)
@[step]
theorem u90 (lf0 lf z) :
    slot.Z156_loop0 lf0 lf z ⦃ Y112P0! ⦄ := by
  rw [slot.Z156_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (lf_, z_) => 286 - z_.val)
    (inv := fun _ => True)
  · rintro ⟨lf_, z_⟩ _
    simp only [slot.Z156_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial
@[step]
theorem u91 (df dd i) :
    slot.Z156_loop1 df dd i ⦃ Y112P0! ⦄ := by
  rw [slot.Z156_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (dd_, i_) => 30 - i_.val)
    (inv := fun _ => True)
  · rintro ⟨dd_, i_⟩ _
    simp only [slot.Z156_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial
@[step]
theorem u92 (lf i tl) :
    slot.Z156_loop2 lf i tl ⦃ Y112P0! ⦄ := by
  rw [slot.Z156_loop2]
  apply Std.loop.spec_decr_nat
    (measure := fun (i_, tl_) => 286 - i_.val)
    (inv := fun _ => True)
  · rintro ⟨i_, tl_⟩ _
    simp only [slot.Z156_loop2.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial
@[step]
theorem u93 (df i td) :
    slot.Z156_loop3 df i td ⦃ Y112P0! ⦄ := T2! slot.Z156_loop3 slot.Z156_loop3.body
@[step]
theorem u94 (lit) (hl:C 512#usize) (i) (ul:W) (hhl:u15 hl.val 15) :
    slot.Z156_loop4 lit hl i ul ⦃ Y112P0! ⦄ := by
  rw [slot.Z156_loop4]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, i_) => 256 - i_.val)
    (inv := fun _ => True)
  · rintro ⟨lit_, i_⟩ _
    simp only [slot.Z156_loop4.body]
    step*
    repeat' (split <;> step*)
    all_goals try (have := u16 hhl i_.val (by scalar_tac))
    all_goals scalar_tac
  · trivial
@[step]
theorem u95 (lc) (hl:C 512#usize) (i) (ul:W) (hhl:u15 hl.val 15) (hul:ul.val  ≤  1152) :
    slot.Z156_loop5 lc hl i ul ⦃ Y112P0! ⦄ := by
  rw [slot.Z156_loop5]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, i_) => 259 - i_.val)
    (inv := fun _ => True)
  · rintro ⟨lc_, i_⟩ _
    simp only [slot.Z156_loop5.body]
    step*
    repeat' (split <;> step*)
    all_goals try (have := u16 hhl i2.val (by scalar_tac))
    all_goals scalar_tac
  · trivial
@[step]
theorem u96 (dc) (i:R) (hd:C 512#usize) (ud:W) (hhd:u15 hd.val 15) (hud:ud.val  ≤  1152) :
    slot.Z156_loop6 dc i hd ud ⦃ Y112P0! ⦄ := by
  rw [slot.Z156_loop6]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, i_) => 30 - i_.val)
    (inv := fun _ => True)
  · rintro ⟨dc_, i_⟩ _
    simp only [slot.Z156_loop6.body]
    step*
    repeat' (split <;> step*)
    all_goals try (have := u16 hhd i_.val (by scalar_tac))
    all_goals scalar_tac
  · trivial
@[step]
theorem u97 (lf0 df lit lc dc) :
    slot.Z156 lf0 df lit lc dc ⦃ Y112P0! ⦄ := by
  rw [slot.Z156]
  step*
  all_goals exact u41 _ _ _ (by simp)
set_option hygiene false in
local notation "T3!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun k_ => lim.val - k_.val)
    (inv := fun _ => True)
  · rintro k_ _
    simp only [q1__]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial)
@[step]
theorem u98 (s:I) (a b lim:R) (k)
    (ha:a.val + lim.val  ≤  s.length) (hb:b.val + lim.val  ≤  s.length) :
    slot.Z157_loop s a b lim k ⦃ Y112P0! ⦄ := T3! slot.Z157_loop slot.Z157_loop.body
@[step]
theorem u99 (s:I) (a b lim:R)
    (ha:a.val + lim.val  ≤  s.length) (hb:b.val + lim.val  ≤  s.length) :
    slot.Z157 s a b lim ⦃ Y112P0! ⦄ := T1! slot.Z157
@[step]
theorem u100 (s) (i:R) (hi:i.val  ≤  2 ^ 31) :
    slot.Z164 s i ⦃ Y112P0! ⦄ := T1! slot.Z164
@[step]
theorem u101 (s) (a b:R) (ha:a.val  ≤  2 ^ 31) (hb:b.val  ≤  2 ^ 31) :
    slot.Z165 s a b ⦃ Y112P0! ⦄ := T1! slot.Z165
@[step]
theorem u102 (s) (p q k:R) (w) (hp:p.val  ≤  2 ^ 30) (hq:q.val  ≤  2 ^ 30) (hk:k.val  ≤  258) :
    slot.Z153_loop s p q k w ⦃ fun r => r.1.val  ≤  258 ⦄ := by
  rw [slot.Z153_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (k_, _) => 258 - k_.val)
    (inv := fun (k_, _) => k_.val  ≤  258)
  · rintro ⟨k_, ⟨w0, w1⟩⟩ hinv
    simp only [slot.Z153_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact hk
@[step]
theorem u103 (s) (p q k:R) (hp:p.val  ≤  2 ^ 30) (hq:q.val  ≤  2 ^ 30) (hk:k.val  ≤  258) :
    slot.Z153 s p q k ⦃ fun r => r.1.val  ≤  258 ⦄ := T1! slot.Z153
@[step]
theorem u104 (s:I) (kid) (pos depth oldest:R) (mb) (cur best:R) (seen:W) (lo_at hi_at lo_len hi_len steps:R)
    (hpos:pos.val + 266  ≤  s.length) (hn26:s.length < 67108864) (hlo:lo_len.val  ≤  258) (hhi:hi_len.val  ≤  258) (hbest:2  ≤  best.val) :
    slot.Z162_loop s kid pos depth mb oldest cur best seen lo_at hi_at lo_len hi_len steps ⦃ Y112P0! ⦄ := by
  rw [slot.Z162_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, _, _, _, _, _, steps_) => depth.val - steps_.val)
    (inv := fun (_, _, _, best_, _, _, _, lo_len_, hi_len_, _) => lo_len_.val  ≤  258  ∧  hi_len_.val  ≤  258  ∧  2  ≤  best_.val)
  · rintro ⟨kid_, mb_, cur_, best_, seen_, lo_at_, hi_at_, lo_len_, hi_len_, steps_⟩ ⟨hlo_, hhi_, hbest_⟩
    simp only [slot.Z162_loop.body, u37]
    step*
    · split <;> omega
    apply WP.spec_bind (Pₘ := fun (x:alloc.vec.Vec W  ×  R  ×  W) => 2  ≤  x.2.1.val)
    · split
      · step*
        repeat' (split <;> step*)
        all_goals scalar_tac
      · step*
        repeat' (split <;> step*)
        all_goals scalar_tac
    rintro ⟨mb1, best1, seen1⟩ hb1
    step*
    apply WP.spec_bind (Pₘ := fun (x:Std.Array W 65536#usize  ×  R  ×  R  ×  R  × 
        R  ×  R) => x.2.2.2.2.1.val  ≤  258  ∧  x.2.2.2.2.2.val  ≤  258)
    · repeat' (split <;> step*)
      all_goals scalar_tac
    rintro ⟨kid1, cur1, lo_at1, hi_at1, lo_len2, hi_len1⟩ ⟨hl2, hh1⟩
    step*
    all_goals scalar_tac
  · exact ⟨hlo, hhi, hbest⟩
@[step]
theorem u105 (s:I) (head kid h3 rct) (pos:R) (pre depth mb) (hpos:pos.val + 266  ≤  s.length)
    (hn26:s.length < 67108864) :
    slot.Z162 s head kid h3 rct pos pre depth mb ⦃ Y112P0! ⦄ := by
  obtain ⟨q, t, h, c3, cr, cur⟩ := pre
  rw [slot.Z162]
  apply WP.spec_bind (Pₘ := fun (_:R) => True)
  · split
    all_goals step*
  rintro oldest -
  step*
  apply WP.spec_bind (Pₘ := fun (x:alloc.vec.Vec W  ×  R) => 2  ≤  x.2.val)
  · repeat' (split <;> step*)
    all_goals scalar_tac
  rintro ⟨mb1, best⟩ hb
  step*
  apply WP.spec_bind (Pₘ := fun (x:alloc.vec.Vec W  ×  R) => 2  ≤  x.2.val)
  · repeat' (split <;> step*)
    all_goals scalar_tac
  rintro ⟨mb2, best1⟩ hb1
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac
set_option maxHeartbeats 4000000 in
@[step]
theorem u106 (i:W) (s:I) (mp:alloc.vec.Vec W) (mb depth) (skip n:R) (head kid h3 rct) (i1 cl cd:R) (nq nt nh n3 nr nc)
    (hn:n.val = s.length) (hn26:s.length < 67108864) (hi:i.val < 32) (hskip:3  ≤  skip.val)
    (hmp:mp.length  ≤  i1.val + 1) (hcd:1  ≤  cd.val) :
    slot.Z145_loop i s mp mb depth skip n head kid h3 rct i1 cl cd nq nt nh n3 nr nc ⦃ Y112P0! ⦄ := by
  rw [slot.Z145_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, _, _, i1_, _, _, _, _, _, _, _, _) => n.val - i1_.val)
    (inv := fun ((mp_:alloc.vec.Vec W), _, _, _, _, _, (i1_:R), _, (cd_:R), _, _, _, _, _, _) =>
      mp_.length  ≤  i1_.val + 1  ∧  1  ≤  cd_.val)
  · rintro ⟨mp_, mb_, head_, kid_, h3_, rct_, i1_, cl_, cd_, nq_, nt_, nh_, n3_, nr_, nc_⟩ ⟨hmp_, hcd_⟩
    unfold slot.Z145_loop.body
    simp only [u37, u40]
    step*
    apply WP.spec_bind (Pₘ := fun (x:alloc.vec.Vec W  ×  Std.Array W 65536#usize  ×  Std.Array W 65536#usize  × 
        Std.Array W 32768#usize  ×  Std.Array W 65536#usize  ×  R  ×  R  ×  Std.U64  ×  R  × 
        R  ×  R  ×  R  ×  R) => 1  ≤  x.2.2.2.2.2.2.1.val)
    · split
      · step*
        · -- a searched or skipped position (at least 266 bytes left)
          apply WP.spec_bind (Pₘ := fun (y:alloc.vec.Vec W  ×  Std.Array W 65536#usize  × 
              Std.Array W 65536#usize  ×  Std.Array W 32768#usize  ×  Std.Array W 65536#usize  × 
              R  ×  R  ×  R  ×  R  ×  R) => 1  ≤  y.2.2.2.2.2.2.1.val)
          · split
            · -- skip: the covering match's remainder as the only record (guarded push)
              step*
              split
              all_goals step*
              all_goals scalar_tac
            · -- search: tree insertion, then the new covering match (its distance code >= 1)
              step*
              apply WP.spec_bind (Pₘ := fun (z:Std.Array W 65536#usize  ×  Std.Array W 65536#usize  × 
                  Std.Array W 32768#usize  ×  Std.Array W 65536#usize  ×  R  ×  R) =>
                  1  ≤  z.2.2.2.2.2.val)
              · repeat' (split <;> step*)
                all_goals scalar_tac
              rintro ⟨head3, kid3, h33, rct3, cl2, cd2⟩ hcd2
              step*
          rintro ⟨v, a, a1, a2, a3, i17, i18, i19, i20, i21⟩ h18
          step*
        · -- one of the last positions: the latest 3-byte occurrence (guarded push)
          apply WP.spec_bind (Pₘ := fun (_:alloc.vec.Vec W  ×  Std.Array W 32768#usize) => True)
          · repeat' (split <;> step*)
            all_goals scalar_tac
          rintro ⟨v, a⟩ -
          step*
      · step*
        apply WP.spec_bind (Pₘ := fun (_:alloc.vec.Vec W  ×  Std.Array W 32768#usize) => True)
        · repeat' (split <;> step*)
          all_goals scalar_tac
        rintro ⟨v, a⟩ -
        step*
    rintro ⟨mb1, head1, kid1, h31, rct1, cl1, cd1, nq1, nt1, nh1, n31, nr1, nc1⟩ hcd1
    step*
    apply WP.spec_bind (Pₘ := fun (_:R) => True)
    · split
      all_goals step*
    rintro cl2 -
    step*
    simp only [alloc.vec.Vec.length, *, List.length_append, List.length_singleton]
    scalar_tac
  · exact ⟨hmp, hcd⟩
@[step]
theorem u107 (s:I) (mp:alloc.vec.Vec W) (mb depth) (skip:R)
    (hn26:s.length < 67108864) (hskip:3  ≤  skip.val) (hmp:mp.length = 0) :
    slot.Z145 s mp mb depth skip ⦃ Y112P0! ⦄ := by
  have hhb := u35
  rw [slot.Z145]
  step*
  all_goals try simp only [alloc.vec.Vec.length, *, List.length_append, List.length_singleton]
  all_goals scalar_tac
@[local step]
theorem u108 (n:R) (cost) (i:R) (hn:n.val < 67108864) (hc:cost.length = i.val) :
    slot.Z144_loop0 n cost i ⦃ Y112P0! ⦄ := Y127U11! slot.Z144_loop0 slot.Z144_loop0.body
@[step]
theorem u109 (k passes tail final_tail):slot.Z161 k passes tail final_tail ⦃ Y112P0! ⦄ := by
  rw [slot.Z161]
  step*
  repeat' (split <;> step*)
set_option aeneas.step.nla true in
@[local step]
theorem u110 (tail final_tail:R) (input:I) (ch) (n:R) (mp mb cost lit lc dc lf df bl bd sl sd) (rot p0 need passes sampled pe k p1 t:R)
    (hn:n.val = input.length) (hn26:n.val < 67108864) (hp0:p0.val < n.val) (hpe:p0.val  ≤  pe.val  ∧  pe.val  ≤  n.val)
    (hpe':pe.val = n.val  ∨  p0.val + slot.Z2.val  ≤  pe.val)
    (hneed:need.val  ≤  65536) (ht:t.val  ≤  need.val) (hp1:p0.val  ≤  p1.val  ∧  p1.val  ≤  p0.val + 511 * t.val) :
    slot.Z144_loop1_loop0 input ch tail final_tail n mp mb cost lit lc dc lf df bl bd sl sd rot p0 need passes sampled pe k p1 t ⦃ Y112P4! ⦄ := by
  have hbt := u36
  have hseg := u34
  rw [slot.Z144_loop1_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, _, _, _, _, _, _, k_, _, _) => passes.val - k_.val)
    (inv := fun (_, _, _, _, _, _, _, _, _, (pe_:R), _, (p1_:R), (t_:R)) =>
      p0.val  ≤  pe_.val  ∧  pe_.val  ≤  n.val  ∧  (pe_.val = n.val  ∨  p0.val + slot.Z2.val  ≤  pe_.val)  ∧ 
      t_.val  ≤  need.val  ∧  p0.val  ≤  p1_.val  ∧  p1_.val  ≤  p0.val + 511 * t_.val)
  · rintro ⟨ch_, cost_, lit_, lc_, dc_, lf_, df_, sl_, sd_, pe_, k_, p1_, t_⟩ ⟨hpe0, hpe1, hpe2, ht_, hp10, hp11⟩
    simp only [slot.Z144_loop1_loop0.body, u37]
    step*
    apply WP.spec_bind (Pₘ := fun (x:alloc.vec.Vec W  ×  alloc.vec.Vec W  ×  Std.Array W 512#usize  × 
        Std.Array W 32#usize  ×  R  ×  R  ×  R) =>
        p0.val  ≤  x.2.2.2.2.1.val  ∧  x.2.2.2.2.1.val  ≤  n.val  ∧ 
        (x.2.2.2.2.1.val = n.val  ∨  p0.val + slot.Z2.val  ≤  x.2.2.2.2.1.val)  ∧ 
        x.2.2.2.2.2.2.val  ≤  need.val  ∧  p0.val  ≤  x.2.2.2.2.2.1.val  ∧  x.2.2.2.2.2.1.val  ≤  p0.val + 511 * x.2.2.2.2.2.2.val)
    · split
      · step*
        · -- a sampled pass: the window end scales with the sampled bytes per token
          cases ‹R  ×  R›
          step*
          apply WP.spec_bind (Pₘ := fun (z:alloc.vec.Vec W  ×  alloc.vec.Vec W  ×  Std.Array W 512#usize  × 
              Std.Array W 32#usize  ×  R) => p0.val  ≤  z.2.2.2.2.val  ∧  z.2.2.2.2.val  ≤  n.val  ∧ 
              (z.2.2.2.2.val = n.val  ∨  p0.val + slot.Z2.val  ≤  z.2.2.2.2.val))
          · repeat' (split <;> step*)
            all_goals scalar_tac
          rintro ⟨v, v1, a, a1, i6⟩ hi6
          step*
          all_goals scalar_tac
        · -- a full pass: dynamic program, then the walk of the round's tokens
          apply WP.spec_bind (Pₘ := fun (lim:R) => lim.val  ≤  pe_.val)
          · split
            all_goals step*
            all_goals scalar_tac
          rintro lim hlim
          step*
          cases ‹R  ×  R›
          step*
          apply WP.spec_bind (Pₘ := fun (z:Std.Array W 512#usize  ×  Std.Array W 32#usize  ×  R) =>
              p0.val  ≤  z.2.2.val  ∧  z.2.2.val  ≤  n.val  ∧  (z.2.2.val = n.val  ∨  p0.val + slot.Z2.val  ≤  z.2.2.val))
          · repeat' (split <;> step*)
            all_goals scalar_tac
          rintro ⟨a, a1, i4⟩ hi4
          step*
          all_goals scalar_tac
        · -- a full pass: dynamic program, then the walk of the round's tokens
          apply WP.spec_bind (Pₘ := fun (lim:R) => lim.val  ≤  pe_.val)
          · split
            all_goals step*
            all_goals scalar_tac
          rintro lim hlim
          step*
          cases ‹R  ×  R›
          step*
          apply WP.spec_bind (Pₘ := fun (z:Std.Array W 512#usize  ×  Std.Array W 32#usize  ×  R) =>
              p0.val  ≤  z.2.2.val  ∧  z.2.2.val  ≤  n.val  ∧  (z.2.2.val = n.val  ∨  p0.val + slot.Z2.val  ≤  z.2.2.val))
          · repeat' (split <;> step*)
            all_goals scalar_tac
          rintro ⟨a, a1, i4⟩ hi4
          step*
          all_goals scalar_tac
      · step*
        · -- a full pass: dynamic program, then the walk of the round's tokens
          apply WP.spec_bind (Pₘ := fun (lim:R) => lim.val  ≤  pe_.val)
          · split
            all_goals step*
            all_goals scalar_tac
          rintro lim hlim
          step*
          cases ‹R  ×  R›
          step*
          apply WP.spec_bind (Pₘ := fun (z:Std.Array W 512#usize  ×  Std.Array W 32#usize  ×  R) =>
              p0.val  ≤  z.2.2.val  ∧  z.2.2.val  ≤  n.val  ∧  (z.2.2.val = n.val  ∨  p0.val + slot.Z2.val  ≤  z.2.2.val))
          · repeat' (split <;> step*)
            all_goals scalar_tac
          rintro ⟨a, a1, i4⟩ hi4
          step*
          all_goals scalar_tac
    rintro ⟨ch1, cost1, lf1, df1, pe1, p11, t1⟩ ⟨hq0, hq1, hq2, hq3, hq4, hq5⟩
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact ⟨hpe.1, hpe.2, hpe', ht, hp1.1, hp1.2⟩
@[local step]
theorem u111 (n depth skip tail):slot.Z173 n depth skip tail ⦃ Y112P0! ⦄ := by
  rw [slot.Z173]
  repeat' (split <;> step*)
@[local step]
theorem u112 (seed):slot.Z172 seed ⦃ fun r => r.val  ≤  2 ⦄ := by
  rw [slot.Z172]
  repeat' (split <;> step*)
  all_goals scalar_tac
@[local step]
theorem u113 (seed block):slot.Z176 seed block ⦃ fun r => 512  ≤  r.2.val  ∧  r.2.val  ≤  67108864 ⦄ := Y127U12! slot.Z176
@[local step]
theorem u114 (seed block):slot.Z178 seed block ⦃ fun r => 512  ≤  r.val  ∧  r.val  ≤  67108864 ⦄ := by
  rw [slot.Z178]
  step*
@[local step]
theorem u115 (lit base i):slot.Z174_loop0 lit base i ⦃ Y112P0! ⦄ := by
  rw [slot.Z174_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_,i_) => 256-i_.val)
    (inv := fun _ => True)
  · rintro ⟨lit_,i_⟩ _
    simp only [slot.Z174_loop0.body]
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem u116 (lc base i):slot.Z174_loop1 lc base i ⦃ Y112P0! ⦄ := by
  rw [slot.Z174_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (_,i_) => 259-i_.val)
    (inv := fun _ => True)
  · rintro ⟨lc_,i_⟩ _
    simp only [slot.Z174_loop1.body]
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem u117 (dc base i):slot.Z174_loop2 dc base i ⦃ Y112P0! ⦄ := by
  rw [slot.Z174_loop2]
  apply Std.loop.spec_decr_nat
    (measure := fun (_,i_) => 30-i_.val)
    (inv := fun _ => True)
  · rintro ⟨dc_,i_⟩ _
    simp only [slot.Z174_loop2.body]
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem u118 (seed block lit lc dc):slot.Z174 seed block lit lc dc ⦃ Y112P0! ⦄ := by
  rw [slot.Z174]
  repeat' (split <;> step*)
@[local step]
theorem u119 (seed p0 first later):slot.Z175 seed p0 first later ⦃ Y112P0! ⦄ := by
  rw [slot.Z175]
  repeat' (split <;> step*)
  all_goals scalar_tac
@[local step]
theorem u120 (seed p0 first later):slot.Z177 seed p0 first later ⦃ Y112P0! ⦄ := by
  rw [slot.Z177]
  repeat' (split <;> step*)
@[local step]
theorem u121 (seed block need bpt) (hneed:need.val  ≤  16384) (hbpt:bpt.val  ≤  130816) :
    slot.Z171 seed block need bpt ⦃ fun r => 512  ≤  r.val ⦄ := by
  rw [slot.Z171]
  have hmargin:slot.Z2.val = 512 := by simp
  have hmul:need.val*bpt.val  ≤  16384*130816 := Nat.mul_le_mul hneed hbpt
  split <;> step*
  all_goals scalar_tac
@[local step]
theorem u122 (tail final_tail:R) (input:I) (ch first_passes fspass passes_k) (n:R) (mp mb cost lit lc dc lf df bl bd sl sd zl zd) (rot spn p0 used bpt preset bidx:R)
    (hn:n.val = input.length) (hn26:n.val < 67108864) (hused:used.val < slot.Z7.val) (hbpt:256  ≤  bpt.val  ∧  bpt.val  ≤  65536) :
    slot.Z144_loop1 input ch first_passes fspass passes_k tail final_tail n preset mp mb cost lit lc dc lf df bl bd sl sd zl zd rot spn p0 used bpt bidx ⦃ Y112P0! ⦄ := by
  have hbt := u36
  rw [slot.Z144_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, _, _, _, _, _, _, _, p0_, _, _, _) => n.val - p0_.val)
    (inv := fun (_, _, _, _, _, _, _, _, _, _, _, _, used_, bpt_, _) => used_.val < slot.Z7.val  ∧ 
      256  ≤  bpt_.val  ∧  bpt_.val  ≤  130816)
  · rintro ⟨ch_, cost_, lit_, lc_, dc_, lf_, df_, bl_, bd_, sl_, sd_, p0_, used_, bpt_, bidx_⟩ ⟨hused_, hbpt0, hbpt1⟩
    simp only [slot.Z144_loop1.body, u37]
    step*
    all_goals try scalar_tac
    apply WP.spec_bind (Pₘ := fun (pe:R) => p0_.val  ≤  pe.val  ∧  pe.val  ≤  n.val  ∧ 
      (pe.val = n.val  ∨  p0_.val + slot.Z2.val  ≤  pe.val))
    · split
      all_goals step*
      all_goals scalar_tac
    rintro pe hpe
    step*
    apply WP.spec_bind (Pₘ := fun (x:Std.Array W 512#usize  ×  Std.Array W 32#usize  ×  R) =>
      x.2.2.val < slot.Z7.val)
    · split
      all_goals step*
      all_goals scalar_tac
    rintro ⟨bl1, bd1, used2⟩ hu2
    step*
    all_goals try (
      have hdiv:bpt1.val  ≤  130816 := by
        rw [bpt1_post];apply Nat.div_le_of_le_mul;scalar_tac
      by_cases hb:bpt1 < 256#usize
      all_goals simp only [hb, ite_true, ite_false])
    all_goals scalar_tac
  · -- the invariant allows up to 511 bytes per token (the snapshot never clamps `bpt` from above)
    exact ⟨hused, hbpt.1, by omega⟩
@[local step]
theorem u123 (tail final_tail:R) (input:I) (ch) (depth skip first_passes fspass passes_k spass:R)
    (hn:input.length < 67108864) (h1:depth.val  ≤  65536) (h2:skip.val  ≤  65536) (h2':3  ≤  skip.val)
    (h3:first_passes.val  ≤  65536) (h4:fspass.val  ≤  65536) (h5:passes_k.val  ≤  65536) (h6:spass.val  ≤  65536) :
    slot.Z144 input ch depth skip first_passes fspass passes_k spass tail final_tail ⦃ Y112P0! ⦄ := by
  have hbt := u36
  rw [slot.Z144]
  step*
  all_goals rfl
@[step]
theorem u124:slot.Z12 ⦃ fun x => x.val = 536870912 ⦄ := by
  unfold slot.Z12;step*
@[step]
theorem u125:slot.Z15 ⦃ Y112P0! ⦄ := by
  unfold slot.Z15
  have h := u4
  step*
theorem u126 {α:Type} (v:alloc.vec.Vec α) (i:R) :
    alloc.vec.Vec.index_mut_usize v i =
      (do let x ← alloc.vec.Vec.index_usize v i;ok (x, alloc.vec.Vec.set v i)) := by
  unfold alloc.vec.Vec.index_mut_usize
  cases alloc.vec.Vec.index_usize v i <;> rfl
theorem u127 (x:W):x.val >>> 15 < 131072 := by
  rw [Nat.shiftRight_eq_div_pow]
  have:x.val < 2 ^ 32 := by scalar_tac
  omega
theorem u128 {n:R} (a:Std.Array W n) (j:R) (B:Nat)
    (h:u15 a.val B) (hj:j.val < a.length) :
    a.index_usize j ⦃ fun x => x = a.val[j.val]  ∧  x.val  ≤  B ⦄ := by
  have := Std.Array.index_usize_spec a j hj
  apply WP.spec_mono this
  intro x hx
  exact ⟨hx, hx ▸ u16 h j.val (by simpa using hj)⟩
theorem u129 {n:R} (a:Std.Array W n) (j:R) (x:W)
    (B:Nat) (h:u15 a.val B) (hx:x.val < B + 1) (hj:j.val < a.length) :
    a.update j x ⦃ fun r => r = a.set j x  ∧  u15 r.val B ⦄ := by
  have := Std.Array.update_spec a j x hj
  apply WP.spec_mono this
  intro r hr
  exact ⟨hr, by rw [hr, Std.Array.set_val_eq];exact u18 h _ _ (by omega)⟩
theorem u130 {α:Type} {n:R} (v:Std.Array α n) (i:R)
    (hbound:i.val < v.length) :
    v.index_mut_usize i ⦃ x back => back = Std.Array.set v i ⦄ := by
  have := Std.Array.index_mut_usize_spec v i hbound
  apply WP.spec_mono this
  rintro ⟨x, back⟩ ⟨_, h⟩
  exact h
theorem u131 (l:V):u15 l 4294967295 := fun j hj => by scalar_tac
theorem u132 (x y:R) (h:y.val  ≤  x.val) :
    (core.num.Usize.wrapping_sub x y).val = x.val - y.val := by
  rw [core.num.Usize.wrapping_sub_val_eq]
  have hx:x.val < UScalar.size .Usize := by
    have := x.hBounds;simp only [UScalar.size];exact this
  rw [show x.val + (UScalar.size .Usize - y.val) = (x.val - y.val) + UScalar.size .Usize by omega,
    Nat.add_mod_right, Nat.mod_eq_of_lt (by omega)]
theorem u133 (x:W):x.val >>> 2 < 1073741824 := by
  rw [Nat.shiftRight_eq_div_pow]
  have:x.val < 2 ^ 32 := by scalar_tac
  omega
def u134 (l:V) (base K:Nat):Prop :=
  ∀ z, z < slot.Z11.val  →  ∀ x, l[base + z]? = some x  →  x.val  ≤  K
def u135 (l:V) (base n:Nat):Prop :=
  ∀ z, z < n  →  ∀ x, l[base + z]? = some x  →  x.val = 0
theorem u136 {l:V} {base K K':Nat} (h:u134 l base K) (hK:K  ≤  K') :
    u134 l base K' := fun z hz x hx => le_trans (h z hz x hx) hK
theorem u137 {l:V} {base K base' K':Nat} (h:u134 l base K)
    (hh:base = base'  ∧  K  ≤  K'):u134 l base' K' := by
  obtain ⟨rfl, hK⟩ := hh;exact u136 h hK
theorem u138 {l:V} {base K:Nat} (h:u134 l base K) {idx:Nat}
    {x:W} (h1:base  ≤  idx) (h2:idx < base + slot.Z11.val) (hl:idx < l.length)
    (hx:x = l[idx]):x.val  ≤  K := by
  have hx':l[base + (idx - base)]? = some x := by
    rw [show base + (idx - base) = idx by omega, hx];exact List.getElem?_eq_getElem hl
  exact h (idx - base) (by omega) _ hx'
theorem u139 {l:V} {base K K':Nat} (h:u134 l base K) (idx:Nat)
    (v:W) (hv:v.val  ≤  K') (hK:K  ≤  K'):u134 (l.set idx v) base K' := by
  intro z hz x hx
  rw [List.getElem?_set] at hx
  split at hx
  · split at hx
    · cases hx;exact hv
    · cases hx
  · exact le_trans (h z hz x hx) hK
theorem u140 (l:V) (base:Nat):u135 l base 0 :=
  fun z hz => absurd hz (Nat.not_lt_zero z)
theorem u141 {l:V} {base n:Nat} (h:u135 l base n) (idx:Nat)
    (hidx:idx = base + n):u135 (l.set idx 0#u32) base (n + 1) := by
  intro z hz x hx
  rw [List.getElem?_set] at hx
  split at hx
  · split at hx
    · cases hx;rfl
    · cases hx
  · exact h z (by omega) x hx
theorem u142 {l:V} {base n:Nat} (h:u135 l base n)
    (hlen:l.length = base + n):u135 (l ++ [0#u32]) base (n + 1) := by
  intro z hz x hx
  by_cases hzn:z < n
  · rw [List.getElem?_append_left (by omega)] at hx
    exact h z hzn x hx
  · have:base + z = l.length := by omega
    rw [this, List.getElem?_concat_length] at hx
    cases hx;rfl
theorem u143 {l:V} {base n:Nat} (h:u135 l base n)
    (hn:slot.Z11.val  ≤  n):u134 l base 0 :=
  fun z hz x hx => le_of_eq (h z (by omega) x hx)
def u144 (n:Nat) (bf bs:alloc.vec.Vec W) (nb pos t:Nat):Prop :=
  (pos  ≤  n  ∧  t  ≤  pos  ∧  t  ≤  nb * slot.Z7.val  ∧  nb * slot.Z7.val < t + slot.Z7.val  ∧ 
    nb * slot.Z11.val  ≤  bf.length  ∧  nb  ≤  bs.length)  ∧ 
    (0 < nb  →  u134 bf.val ((nb - 1) * slot.Z11.val) pos)
theorem engB_TPL.u145 {n:Nat} {bf bs:alloc.vec.Vec W} {nb pos t:Nat}
    (h1:pos  ≤  n  ∧  t  ≤  pos  ∧  t  ≤  nb * slot.Z7.val  ∧ 
      nb * slot.Z7.val < t + slot.Z7.val  ∧  nb * slot.Z11.val  ≤  bf.length  ∧ 
      nb  ≤  bs.length)
    (h2:0 < nb  →  u134 bf.val ((nb - 1) * slot.Z11.val) pos):u144 n bf bs nb pos t :=
  ⟨h1, h2⟩
def u146 (m:Nat) (bf bs:alloc.vec.Vec W) (nb inb j:Nat):Prop :=
  j  ≤  m  ∧  nb * slot.Z11.val  ≤  bf.length  ∧  nb  ≤  bs.length  ∧  (nb = 0  →  inb = slot.Z7.val)  ∧ 
    inb  ≤  slot.Z7.val  ∧  (0 < nb  →  (nb - 1) * slot.Z7.val + inb  ≤  m - j)
def u147 (m L:Nat) (bf bs:alloc.vec.Vec W) (nb inb j:Nat):Prop :=
  (L  ≤  bf.length  ∧  u146 m bf bs nb inb j)  ∧ 
    (0 < nb  →  u134 bf.val ((nb - 1) * slot.Z11.val) (m - j))
theorem engB_TSL.u148 {m L:Nat} {bf bs:alloc.vec.Vec W} {nb inb j:Nat}
    (h1:L  ≤  bf.length  ∧  j  ≤  m  ∧  nb * slot.Z11.val  ≤  bf.length  ∧  nb  ≤  bs.length  ∧ 
      (nb = 0  →  inb = slot.Z7.val)  ∧  inb  ≤  slot.Z7.val  ∧ 
      (0 < nb  →  (nb - 1) * slot.Z7.val + inb  ≤  m - j))
    (h2:0 < nb  →  u134 bf.val ((nb - 1) * slot.Z11.val) (m - j)) :
    u147 m L bf bs nb inb j :=
  ⟨⟨h1.1, h1.2⟩, h2⟩
attribute [local step] u128 u129 in
theorem u149 (t:Std.Array W 65536#usize) (lt ls rs cs cur l ll rl:R) (i L:Nat)
    (hT:u15 t.val i) (hcur:cur.val  ≤  i) (hi:i < 67108864) (hcs:cs.val  ≤  65534)
    (hl:l.val  ≤  L) (hll:ll.val  ≤  L) (hrl:rl.val  ≤  L) :
    (if lt = 1#usize then do
        let i16 ← ls % slot.Z112
        let i17 ← lift (UScalar.cast UScalarTy.U32 cur)
        let a5 ← t.update i16 i17
        let ls2 ← cs + 1#usize
        let i18 ← ls2 % slot.Z112
        let i19 ← a5.index_usize i18
        let cur2 ← lift (UScalar.cast UScalarTy.Usize i19)
        ok (a5, cur2, ls2, rs, l, rl)
      else do
        let i16 ← rs % slot.Z112
        let i17 ← lift (UScalar.cast UScalarTy.U32 cur)
        let a5 ← t.update i16 i17
        let i18 ← cs % slot.Z112
        let i19 ← a5.index_usize i18
        let cur2 ← lift (UScalar.cast UScalarTy.Usize i19)
        ok (a5, cur2, ls, cs, ll, l)) ⦃
      fun (x:Std.Array W 65536#usize  ×  R  ×  R  ×  R  ×  R  ×  R) =>
      u15 x.1.val i  ∧  x.2.1.val  ≤  i  ∧  x.2.2.2.2.1.val  ≤  L  ∧  x.2.2.2.2.2.val  ≤  L ⦄ := by
  have hc:(UScalar.cast UScalarTy.U32 cur).val = cur.val :=
    UScalar.cast_val_mod_pow_of_inBounds_eq _ _ (by scalar_tac)
  split
  · step*
    all_goals first
      | exact ⟨by assumption, by scalar_tac, hl, hrl⟩
      | scalar_tac
  · step*
    all_goals first
      | exact ⟨by assumption, by scalar_tac, hll, hl⟩
      | scalar_tac
def u150 (i:Nat) (tree:Std.Array W 65536#usize) (pn:Std.Array W 32#usize)
    (step cur ll rl fuel nr bl bd:Nat):Prop :=
  u15 tree.val i  ∧  u15 pn.val i  ∧  cur  ≤  i  ∧  ll  ≤  2 ^ 30  ∧  rl  ≤  2 ^ 30  ∧  step + fuel  ≤  2 ^ 20  ∧ 
    nr  ≤  slot.Z18.val  ∧  bl  ≤  2 ^ 30  ∧  bd  ≤  i
theorem engB_DInv.u151 {i:Nat} {tree:Std.Array W 65536#usize} {pn:Std.Array W 32#usize}
    {step cur ll rl fuel nr bl bd:Nat} (h1:u15 tree.val i) (h2:u15 pn.val i)
    (h3:cur  ≤  i  ∧  ll  ≤  2 ^ 30  ∧  rl  ≤  2 ^ 30  ∧  step + fuel  ≤  2 ^ 20  ∧  nr  ≤  slot.Z18.val  ∧ 
      bl  ≤  2 ^ 30  ∧  bd  ≤  i) :
    u150 i tree pn step cur ll rl fuel nr bl bd :=
  ⟨h1, h2, h3⟩
abbrev u152 := Std.Array W 65536#usize  ×  Std.Array W 32#usize  ×  Std.Array W 32#usize  × 
  Std.Array W 32#usize  ×  R  ×  R  ×  R  ×  R  ×  R  ×  R  ×  R  × 
  R  ×  R  ×  R  ×  R  ×  R  ×  R
abbrev u153 := Std.Array W 65536#usize  ×  Std.Array W 32#usize  ×  Std.Array W 32#usize  × 
  Std.Array W 32#usize  ×  R  ×  R  ×  R  ×  R  ×  R
def u154 (i fuel:Nat) (r:ControlFlow u152 u153):Prop :=
  match r with
  | .done y => u15 y.1.val i  ∧  u15 y.2.1.val i  ∧  y.2.2.2.2.2.1.val  ≤  slot.Z18.val  ∧ 
      y.2.2.2.2.2.2.2.1.val  ≤  2 ^ 30  ∧  y.2.2.2.2.2.2.2.2.val  ≤  i
  | .cont x' => u150 i x'.1 x'.2.1 x'.2.2.2.2.1.val x'.2.2.2.2.2.1.val x'.2.2.2.2.2.2.2.2.1.val
      x'.2.2.2.2.2.2.2.2.2.1.val x'.2.2.2.2.2.2.2.2.2.2.1.val x'.2.2.2.2.2.2.2.2.2.2.2.2.2.1.val
      x'.2.2.2.2.2.2.2.2.2.2.2.2.2.2.2.1.val x'.2.2.2.2.2.2.2.2.2.2.2.2.2.2.2.2.val  ∧ 
      x'.2.2.2.2.2.2.2.2.2.2.1.val < fuel
def u155 (mf:slot.Z8) (i:Nat):Prop :=
  u15 mf.head.val i  ∧  u15 mf.head3.val i  ∧  u15 mf.tree.val i  ∧  u15 mf.pn.val i  ∧ 
    mf.hl.val  ≤  2 ^ 30
theorem u156 (w:Std.Array Std.U64 32768#usize) (pf:Std.Array W 32#usize) (plen hn:R) :
    u155
      { head := Std.Array.repeat 65536#usize 0#u32, head3 := Std.Array.repeat 16384#usize 0#u32,
        tree := Std.Array.repeat 65536#usize 0#u32, w := w, pn := Std.Array.repeat 32#usize 0#u32, pf := pf,
        plen := plen, hn := hn, hl := 0#usize } (0#usize).val := by
  refine ⟨?_, ?_, ?_, ?_, ?_⟩ <;> simp only [Std.Array.repeat_val] <;>
    first | exact LeAll_replicate _ _ _ (by simp) | simp
def u157 (b i:Nat)
    (r:ControlFlow (slot.Z8  ×  Std.Array W 32#usize  ×  alloc.vec.Vec W  ×  Std.U64  ×  R  × 
      R  ×  R) (slot.Z8  ×  Std.Array W 32#usize  ×  alloc.vec.Vec W  ×  Std.U64  × 
      R  ×  R)):Prop :=
  match r with
  | .done y => u155 y.1 b  ∧  y.2.2.2.2.2.val  ≤  33 * b  ∧  y.2.2.2.2.2.val  ≤  y.2.2.1.length
  | .cont x' => x'.2.2.2.2.2.2.val  ≤  b  ∧  x'.2.2.2.2.2.1.val  ≤  33 * x'.2.2.2.2.2.2.val  ∧ 
      x'.2.2.2.2.2.1.val  ≤  x'.2.2.1.length  ∧  u155 x'.1 x'.2.2.2.2.2.2.val  ∧ 
      b - x'.2.2.2.2.2.2.val < b - i
@[step]
theorem u158:slot.Z30 ⦃ fun x => x.val = 2147483648 ⦄ := by
  unfold slot.Z30;step*
attribute [local step] u124
theorem u159:8192  ≤  slot.Z7.val  ∧  slot.Z7.val  ≤  1048576 := by simp [slot.Z7]
theorem C_WS_val:slot.Z20.val = 32768 := by simp [slot.Z20]
theorem u160:slot.Z112.val = 65536 := by simp [slot.Z112]
theorem C_HS_bounds:2  ≤  slot.Z112.val  ∧  slot.Z112.val  ≤  65536 := by simp [slot.Z112]
theorem u161:slot.Z33.val = 544 := by simp [slot.Z33]
theorem u162:slot.Z37.val < 2 ^ 27 := by simp [slot.Z37]
theorem u163:slot.Z4.val  ≤  32 := by simp [slot.Z4]
theorem u164:slot.Z0.val  ≤  256 := by simp [slot.Z0]
theorem C_UNUSED_LIT_le:slot.Z46.val  ≤  65536 := by simp [slot.Z46]
theorem C_UNUSED_DIST_le:slot.Z43.val  ≤  65536 := by simp [slot.Z43]
theorem u165:slot.Z45.val  ≤  65536 := by simp [slot.Z45]
theorem u166:slot.Z44.val  ≤  65536 := by simp [slot.Z44]
theorem u167:slot.Z0.val  ≤  65536 := by simp [slot.Z0]
theorem u168:slot.Z40.val  ≤  65536 := by simp [slot.Z40]
theorem u169:slot.Z41.val  ≤  65536 := by simp [slot.Z41]
theorem u170:slot.Z42.val  ≤  65536 := by simp [slot.Z42]
theorem u171:slot.Z24.val  ≤  65535 := by simp [slot.Z24]
theorem C_STOP_DIV_pos:0 < slot.Z39.val := by simp [slot.Z39]
theorem u172:1  ≤  slot.Z47.val := by simp [slot.Z47]
theorem u173:1  ≤  slot.Z10.val  ∧  slot.Z10.val  ≤  1048576 := by simp [slot.Z10]
theorem u174:slot.Z38.val  ≤  1048576 := by simp [slot.Z38]
theorem u175 (i:Nat) (h:i < 29):(slot.Z31.val[i]!).val  ≤  5 := by
  unfold slot.Z31;simp only [Array.make];revert i;decide
theorem u176 (i:Nat) (h:i < 30):(slot.Z26.val[i]!).val  ≤  13 := by
  unfold slot.Z26;simp only [Array.make];revert i;decide
@[step]
theorem u177 (i:R) (h:i.val < 29) :
    Array.index_usize slot.Z31 i ⦃ fun x => x.val  ≤  5 ⦄ := by
  have := u175 i.val h
  step*
  subst x_post
  rw [List.getElem!_eq_getElem?_getD, List.getElem?_eq_getElem (by scalar_tac)] at this
  exact this
@[step]
theorem u178 (i:R) (h:i.val < 30) :
    Array.index_usize slot.Z26 i ⦃ fun x => x.val  ≤  13 ⦄ := by
  have := u176 i.val h
  step*
  subst x_post
  rw [List.getElem!_eq_getElem?_getD, List.getElem?_eq_getElem (by scalar_tac)] at this
  exact this
@[step]
theorem u179 (x y:R) :
    lift (core.num.Usize.wrapping_add x y) ⦃ fun z => z = core.num.Usize.wrapping_add x y  ∧ 
      (x.val + y.val  ≤  Usize.max  →  z.val = x.val + y.val) ⦄ := by
  simp only [lift, WP.spec_ok, true_and]
  intro h
  rw [core.num.Usize.wrapping_add_val_eq, UScalar.size_UScalarTyUsize]
  apply Nat.mod_eq_of_lt
  scalar_tac
@[step]
theorem u180 (x y:W) :
    lift (core.num.U32.wrapping_add x y) ⦃ fun z => z = core.num.U32.wrapping_add x y  ∧ 
      (x.val + y.val  ≤  U32.max  →  z.val = x.val + y.val) ⦄ := by
  simp only [lift, WP.spec_ok, true_and]
  intro h
  rw [core.num.U32.wrapping_add_val_eq]
  apply Nat.mod_eq_of_lt
  scalar_tac
@[step]
theorem u181 (x y:Std.U64)
    (h:(x.val  ≤  4294967295  ∧  y.val  ≤  4294967295)  ∨  x.val * y.val  ≤  U64.max) :
    (x * y) ⦃ fun z => z.val = x.val * y.val  ∧  (x.val  ≤  4294967295  →  z.val  ≤  4294967295 * y.val) ⦄ := by
  have h':x.val * y.val  ≤  U64.max := by
    rcases h with ⟨hx, hy⟩ | h
    · have := Nat.mul_le_mul hx hy
      scalar_tac
    · exact h
  step*
  refine ⟨z_post, fun hx => ?_⟩
  rw [z_post]
  exact Nat.mul_le_mul_right _ hx
@[step]
theorem u182 (x y:W)
    (h:(x.val  ≤  16777215  ∧  y.val  ≤  256)  ∨  x.val * y.val  ≤  U32.max) :
    (x * y) ⦃ fun z => z.val = x.val * y.val  ∧  (y.val  ≤  256  →  z.val  ≤  256 * x.val) ⦄ := by
  have h':x.val * y.val  ≤  U32.max := by
    rcases h with ⟨hx, hy⟩ | h
    · have := Nat.mul_le_mul hx hy
      scalar_tac
    · exact h
  step*
  refine ⟨z_post, fun hy => ?_⟩
  rw [z_post, Nat.mul_comm]
  exact Nat.mul_le_mul_right _ hy
@[step]
theorem u183 (x y:Std.U64) (h:y.val ≠ 0) :
    (x / y) ⦃ fun z => z.val = x.val / y.val  ∧  (x.val  ≤  65536 * y.val  →  z.val  ≤  65536) ⦄ := by
  obtain ⟨z, hz, hv⟩ := UScalar.div_spec x h
  rw [hz]
  simp only [WP.spec_ok]
  refine ⟨hv, fun hx => ?_⟩
  rw [hv]
  exact Nat.div_le_of_le_mul (by rw [Nat.mul_comm];exact hx)
@[step]
theorem u184 (x:R) :
    lift (UScalar.cast .U64 x) ⦃ fun y => y = UScalar.cast .U64 x  ∧  y.val = x.val ⦄ := by
  simp only [lift, WP.spec_ok, true_and]
  apply UScalar.cast_val_mod_pow_of_inBounds_eq
  have := x.hBounds
  have:2 ^ UScalarTy.Usize.numBits  ≤  2 ^ UScalarTy.U64.numBits := by
    apply Nat.pow_le_pow_right (by decide)
    simp only [UScalarTy.numBits]
    cases System.Platform.numBits_eq <;> simp [*]
  omega
@[step]
theorem u185 (x:Std.U64) :
    lift (UScalar.cast .Usize x) ⦃ fun y => y = UScalar.cast .Usize x  ∧  (x.val  ≤  4294967295  →  y.val = x.val) ⦄ := by
  simp only [lift, WP.spec_ok, true_and]
  intro h
  apply UScalar.cast_val_mod_pow_of_inBounds_eq
  have:2 ^ 32  ≤  2 ^ UScalarTy.Usize.numBits := by
    apply Nat.pow_le_pow_right (by decide)
    simp only [UScalarTy.numBits]
    exact u4
  omega
@[step]
theorem u186 {α:Type} (v:alloc.vec.Vec α) (x:α) (h:v.length < Usize.max) :
    alloc.vec.Vec.push v x ⦃ fun v1 => v1.val = v.val ++ [x]  ∧  v1.length = v.length + 1 ⦄ := by
  step*
  exact ⟨v1_post, by simp [v1_post]⟩
theorem u187 {α:Type} (n:R):(alloc.vec.Vec.with_capacity α n).length = 0 := rfl
theorem u188 {α:Type} {c:Prop} [Decidable c] {A B:Result α} {P:α  →  Prop}
    (hA:c  →  A ⦃ P ⦄) (hB:¬c  →  B ⦃ P ⦄):(if c then A else B) ⦃ P ⦄ := by
  by_cases h:c
  · rw [if_pos h];exact hA h
  · rw [if_neg h];exact hB h
theorem u189 {α β:Type} {c:Prop} [Decidable c] {A B:Result α} {k:α  →  Result β}
    {P:β  →  Prop} (hA:c  →  (A >>= k) ⦃ P ⦄) (hB:¬c  →  (B >>= k) ⦃ P ⦄) :
    ((if c then A else B) >>= k) ⦃ P ⦄ := by
  by_cases h:c
  · rw [if_pos h];exact hA h
  · rw [if_neg h];exact hB h
theorem spine_CFG_le:∀ r ∈ slot.Z21.val, ∀ x ∈ r.val, x.val  ≤  65536 := by
  unfold slot.Z21;decide
theorem spine_CFG_skip:∀ r ∈ slot.Z21.val, (r.val[0]!).val = 0  →  3  ≤  (r.val[2]!).val := by
  unfold slot.Z21;decide
theorem spine_knob_le {m:R} {r:O m} (hr:∀ x ∈ r.val, x.val  ≤  65536)
    {x:R} {j:Nat} {hj:j < r.val.length} (hx:x = r.val[j]):x.val  ≤  65536 := by
  subst hx;exact hr _ (List.getElem_mem _)
theorem spine_knob_skip {m:R} {r:O m}
    (hs:(r.val[0]!).val = 0  →  3  ≤  (r.val[2]!).val)
    {x0 x2:R} {h0:0 < r.val.length} {h2:2 < r.val.length}
    (hx0:x0 = r.val[0]) (hz:x0 = 0#usize) (hx2:x2 = r.val[2]):3  ≤  x2.val := by
  rw [getElem!_pos r.val 0 h0, getElem!_pos r.val 2 h2, ← hx0, ← hx2, hz] at hs
  exact hs rfl
@[local step]
theorem u190 (input:I) (k) (hn:input.length < 67108864) :
    slot.Z180 input k ⦃ Y112P0! ⦄ := by
  rw [slot.Z180]
  step*
  all_goals
    have hc:c ∈ slot.Z21.val := by rw [c_post];exact List.getElem_mem _
    first
    | exact spine_knob_le (spine_CFG_le c hc) (by assumption)
    | exact spine_knob_skip (spine_CFG_skip c hc) (by assumption) (by assumption) (by assumption)
@[local step]
theorem u191 (input) (k:R):slot.Z169 input k ⦃ Y112P0! ⦄ := by
  rw [slot.Z169]
  step*
theorem u192 (input:I) (out:U) (k:R)
    (hlen:input.length  ≤  out.length) :
    slot.Z179 input out k ⦃ Y112P1! ⦄ := Y127U13! slot.Z179
end EA
namespace ED
open Aeneas Aeneas.Std Result ControlFlow
set_option maxRecDepth 8192
set_option maxHeartbeats 4000000
open LZ77 (toks bytes bytes_length bytes_getElem! toks_update bytes_congr Matches ite_ok)
theorem u193 (x:Std.U64) (i6:W) (i7:R)
    (h6:i6.val = (core.num.U64.leading_zeros x).val / 8)
    (h7:i7 = UScalar.cast .Usize i6):i7.val  ≤  8 := by
  have := EA.u12 x
  subst h7
  simp only [U32.cast_Usize_val_eq]
  omega
theorem u194 {α:Type} {n:R} (a:Array α n) (i:R) (v:α)
    (P:α  →  Prop) (ha:∀ x ∈ a.val, P x) (hv:P v):∀ x ∈ (a.set i v).val, P x := by
  intro x hx
  rw [Aeneas.Std.Array.set_val_eq] at hx
  rcases List.mem_or_eq_of_mem_set hx with h | h
  · exact ha x h
  · exact h ▸ hv
theorem u195 {α:Type} (n:R) (v:α) (P:α  →  Prop) (hv:P v) :
    ∀ x ∈ (Array.repeat n v).val, P x := by
  intro x hx
  rw [Aeneas.Std.Array.repeat_val] at hx
  rw [List.eq_of_mem_replicate hx]
  exact hv
theorem u196 {α:Type} {n:R} (a:Array α n) (P:α  →  Prop)
    (ha:∀ x ∈ a.val, P x) (i:Nat) (h:i < a.val.length):P (a.val[i]) :=
  ha _ (List.getElem_mem h)
theorem u197 (rest:R):(if rest < 258#usize then rest else 258#usize).val  ≤  258 := by
  split <;> scalar_tac
end ED
namespace EH
open Aeneas Aeneas.Std Result ControlFlow
set_option maxRecDepth 8192
set_option maxHeartbeats 4000000
set_option linter.unusedTactic false
set_option linter.unreachableTactic false
set_option linter.unusedSimpArgs false
open LZ77 (toks bytes bytes_length bytes_getElem! Matches emit_lit emit_match ite_ok)
theorem spec_ite_cut {α:Type} (c:Prop) [Decidable c] (a b:Result α) (Q:α  →  Prop)
    (ha:c  →  a ⦃ Q ⦄) (hb:¬c  →  b ⦃ Q ⦄):(if c then a else b) ⦃ Q ⦄ := by
  by_cases h:c
  · rw [if_pos h];exact ha h
  · rw [if_neg h];exact hb h
end EH
attribute [local step] EA.u192
@[local step]
theorem u198 (input:I) (out:U) (mode:R) (hlen:input.length  ≤  out.length):slot.Z183 input out mode ⦃ Y112P1! ⦄ := Y127U14! slot.Z183
end EA
set_option hygiene false in
local notation "Y127U15!" => (by
  refine ⟨Submission.EA.EA.lz32_le x, ?_⟩
  by_cases h:x.val = 0
  · exact Or.inl h
  · right;rw [Submission.EA.EA.lz32_eq x h];omega)
set_option hygiene false in
local notation "Y127U21!" q0__:max q1__:max => (by
  rw [q0__]
  step*
  all_goals
    have hc:c ∈ q1__ := by rw [c_post];exact List.getElem_mem _
    first
    | exact Submission.EA.EA.spine_knob_le (spine_CFG_le c hc) (by assumption)
    | exact Submission.EA.EA.spine_knob_skip (spine_CFG_skip c hc) (by assumption) (by assumption) (by assumption))
namespace EB
open Aeneas Aeneas.Std Result ControlFlow
set_option maxRecDepth 8192
set_option maxHeartbeats 1000000
set_option linter.unusedTactic false
set_option linter.unreachableTactic false
set_option linter.unusedSimpArgs false
set_option linter.unusedVariables false
attribute [-instance] instNoNatZeroDivisorsOfIsAddTorsionFree
open LZ77 (toks bytes bytes_getElem! Matches emit_lit emit_match)


@[local scalar_tac x &&& y]
theorem u199 (x y:Nat):x &&& y  ≤  y := Nat.and_le_right
@[local scalar_tac x >>> y]
theorem u200 (x y:Nat):x >>> y  ≤  x := Nat.shiftRight_le x y
@[local scalar_tac System.Platform.numBits]
theorem u201:32  ≤  System.Platform.numBits := EA.EA.u4
@[local scalar_tac core.num.U32.leading_zeros x]
theorem u202 (x:W) :
    (core.num.U32.leading_zeros x).val  ≤  32  ∧ 
      (x.val = 0  ∨  (core.num.U32.leading_zeros x).val  ≤  31) := Y127U15!
@[local scalar_tac core.num.U64.leading_zeros x]
theorem u203 (x:Std.U64):(core.num.U64.leading_zeros x).val  ≤  64 := EA.EA.u12 x
@[local step]
theorem u204 (v:U) (i:R) (x:W) :
    slot.Z304 v i x ⦃ fun r => r.length = v.length ⦄ := by
  rw [slot.Z304];split <;> step*
def u205 (nextl:Array Std.U16 512#usize):Prop := ∀ j, j < 512  →  j < (nextl.val[j]!).val
theorem u206 {n:Nat} (h:n + n  ≤  Std.Usize.max):n + 2147483648  ≤  Std.Usize.max := by
  have:Std.Usize.max = 2 ^ System.Platform.numBits - 1 := by
    simp [Std.Usize.max, Std.Usize.numBits]
  rcases System.Platform.numBits_eq with h32 | h64
  · rw [this, h32] at h ⊢;omega
  · rw [this, h64] at h ⊢;omega
theorem u207:slot.Z107.val = 8192 := by simp [slot.Z107]
theorem u208:slot.Z7.val = 16384 := by simp [slot.Z7]
theorem u209:1  ≤  slot.Z14.val  ∧  slot.Z14.val  ≤  32 := by simp [slot.Z14]
theorem u210:1  ≤  slot.Z0.val  ∧  slot.Z0.val  ≤  64 := by simp [slot.Z0]
theorem u211:slot.Z124.val  ≤  8 := by simp [slot.Z124]
theorem u212:slot.Z131.val  ≤  1048576 := by simp [slot.Z131]
theorem u213:slot.Z6.val  ≤  1048576 := by simp [slot.Z6]
theorem u214:slot.Z10.val  ≤  1048576 := by simp [slot.Z10]
theorem u215:EA.EA.u15 slot.Z120.val 16 := by
  unfold slot.Z120 EA.EA.u15;simp only [Array.make];decide
theorem u216 (c:W):c.val >>> 9 < 8388608 := by
  rw [Nat.shiftRight_eq_div_pow]
  have:c.val < 2 ^ 32 := by (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  omega
theorem u217 (n:R) (h:n.val < (core.num.Usize.wrapping_add n n).val) :
    n.val + n.val  ≤  Std.Usize.max := by
  rw [core.num.Usize.wrapping_add_val_eq] at h
  have hs:Std.Usize.max = UScalar.size .Usize - 1 := by
    simp [Std.Usize.max, Std.Usize.size, Std.Usize.numBits]
  have hn:n.val < UScalar.size .Usize := by
    have := n.hBounds;simp only [UScalar.size];exact this
  by_contra hc
  have h2:UScalar.size .Usize  ≤  n.val + n.val := by omega
  rw [Nat.mod_eq_sub_mod h2, Nat.mod_eq_of_lt (by omega)] at h
  omega
theorem u218 (x:Nat):x ||| 1  ≤  x + 1 := by
  have h := Nat.two_pow_add_eq_or_of_lt (i := 1) (b := 1) (by omega) (x / 2)
  have hx:x ||| 1 = 2 ^ 1 * (x / 2) ||| 1 := by
    rcases Nat.mod_two_eq_zero_or_one x with h0 | h1
    · have:x = 2 ^ 1 * (x / 2) := by omega
      conv_lhs => rw [this]
    · have e := Nat.two_pow_add_eq_or_of_lt (i := 1) (b := 1) (by omega) (x / 2)
      have:x = 2 ^ 1 * (x / 2) ||| 1 := by omega
      conv_lhs => rw [this]
      rw [Nat.or_assoc, Nat.or_self]
  rw [hx, ← h]
  omega
theorem u219 {ty:UScalarTy} {n:R} {a r:Array (UScalar ty) n} {i:R}
    {v:UScalar ty} {B:Nat} (hr:r = a.set i v) (ha:EA.EA.u15 a.val B) (hv:v.val  ≤  B):EA.EA.u15 r.val B := by
  rw [hr, Array.set_val_eq];exact EA.EA.u18 ha _ _ hv
theorem u220!_set {ty:UScalarTy} (l:List (UScalar ty)) (i j:Nat) (x:UScalar ty)
    (hi:i < l.length):(l.set i x)[j]! = if i = j then x else l[j]! := by
  simp only [List.getElem!_eq_getElem?_getD, List.getElem?_set]
  split
  · simp [*]
  · rfl
@[local step] theorem u221 (s:I) (i:R) (h:i.val + 8  ≤  Std.Usize.max) :
    slot.Z192 s i ⦃ Y112P0! ⦄ := by
  rw [slot.Z192]
  step*
@[local step]
theorem u222 (s:I) (a b cap k:R) (run:W)
    (ha:a.val + cap.val + 8  ≤  Std.Usize.max) (hb:b.val + cap.val + 8  ≤  Std.Usize.max) (hk:k.val  ≤  cap.val) :
    slot.Z224_loop0 s a b cap k run ⦃ fun r => r.1.val  ≤  cap.val ⦄ := by
  rw [slot.Z224_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (k', run') => cap.val + 9 - k'.val + run'.val)
    (inv := fun (k', _) => k'.val  ≤  cap.val)
  · rintro ⟨k', run'⟩ hk'
    simp only [slot.Z224_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals try (have := u203 x)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · exact hk
@[local step]
theorem u223 (s:I) (a b cap k:R) (run:W)
    (ha:a.val + cap.val + 8  ≤  Std.Usize.max) (hb:b.val + cap.val + 8  ≤  Std.Usize.max) (hk:k.val  ≤  cap.val) :
    slot.Z224_loop1 s a b cap k run ⦃ fun r => r.val  ≤  cap.val ⦄ := by
  rw [slot.Z224_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (k', run') => cap.val + 1 - k'.val + run'.val)
    (inv := fun (k', _) => k'.val  ≤  cap.val)
  · rintro ⟨k', run'⟩ hk'
    simp only [slot.Z224_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · exact hk
@[local step] theorem u224 (s:I) (a b cap:R)
    (ha:a.val + cap.val + 8  ≤  Std.Usize.max) (hb:b.val + cap.val + 8  ≤  Std.Usize.max) :
    slot.Z224 s a b cap ⦃ fun r => r.val  ≤  cap.val ⦄ := by
  rw [slot.Z224]
  step*
@[local step] theorem u225 (x:W):slot.Z278 x ⦃ fun r => r.val < 16384 ⦄ := by
  have := u209
  have := u208
  rw [slot.Z278]
  step*
@[local step] theorem u226 (x:W):slot.Z279 x ⦃ fun r => r.val < 65536 ⦄ := by
  have := EA.EA.u35
  have := EA.EA.u160
  rw [slot.Z279]
  step*
@[local step] theorem u227 (x:Std.U64):slot.Z280 x ⦃ fun r => r.val < 65536 ⦄ := by
  have := u210
  have := EA.EA.u160
  rw [slot.Z280]
  step*
@[local step] theorem u228 (s:I) (c i:R) (b8:Std.U64) (cap best:R)
    (hc:c.val  ≤  i.val) (hcap:9  ≤  cap.val) (hic:i.val + cap.val  ≤  s.length)
    (hs8:s.length + 8  ≤  Std.Usize.max) :
    slot.Z298 s c i b8 cap best ⦃ fun r => r.val  ≤  cap.val  ∧  (r.val = 0  ∨  best.val < r.val) ⦄ := by
  rw [slot.Z298]
  step*
  repeat' (split <;> step*)
  all_goals try (have := u203 x)
  all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
@[local step] theorem u229 (prev) (start depth:R) (same:Bool) :
    slot.Z305 prev start depth same ⦃ fun r => r.1.val  ≤  start.val ⦄ := by
  have hwn := Submission.EA.EA.C_WS_val
  rw [slot.Z305]
  step*
  repeat' (split <;> step*)
  all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
@[local step] theorem u230 (head3:C 16384#usize) (head4:C 65536#usize)
    (prev4) (head7:C 65536#usize) (prev7) (q:R) (b8:Std.U64) (sh7:W) (B:Nat)
    (h3:EA.EA.u15 head3.val B) (h4:EA.EA.u15 head4.val B) (h7:EA.EA.u15 head7.val B) (hq:q.val  ≤  B) :
    slot.Z288 head3 head4 prev4 head7 prev7 q b8 sh7 ⦃ fun r =>
      r.1.1.val  ≤  B  ∧  r.1.2.1.val  ≤  B  ∧  r.1.2.2.val  ≤  B  ∧ 
      EA.EA.u15 r.2.1.val B  ∧  EA.EA.u15 r.2.2.1.val B  ∧  EA.EA.u15 r.2.2.2.2.1.val B ⦄ := by
  have hwn := Submission.EA.EA.C_WS_val
  have H3 := h3
  have H4 := h4
  have H7 := h7
  rw [slot.Z288]
  step*
  have e3 := EA.EA.u16 H3 h3.val (by scalar_tac)
  have e4 := EA.EA.u16 H4 h4.val (by scalar_tac)
  have e7 := EA.EA.u16 H7 h7.val (by scalar_tac)
  refine ⟨by scalar_tac, by scalar_tac, by scalar_tac, ?_, ?_, ?_⟩
  · exact u219 head31_post H3 (by scalar_tac)
  · exact u219 head41_post H4 (by scalar_tac)
  · exact u219 head71_post H7 (by scalar_tac)
@[local step]
theorem u231 (input:I) (head3:C 16384#usize)
    (head4:C 65536#usize) (prev4) (head7:C 65536#usize) (prev7)
    (e:R) (sh7:W) (q:R) (B:Nat)
    (h3:EA.EA.u15 head3.val B) (h4:EA.EA.u15 head4.val B) (h7:EA.EA.u15 head7.val B)
    (he:e.val  ≤  B + 1) (he8:e.val + 8  ≤  Std.Usize.max) :
    slot.Z289_loop input head3 head4 prev4 head7 prev7 e sh7 q ⦃ fun r =>
      EA.EA.u15 r.1.val B  ∧  EA.EA.u15 r.2.1.val B  ∧  EA.EA.u15 r.2.2.2.1.val B ⦄ := by
  rw [slot.Z289_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, _, q') => e.val - q'.val)
    (inv := fun (h3', h4', _, h7', _, _) => EA.EA.u15 h3'.val B  ∧  EA.EA.u15 h4'.val B  ∧  EA.EA.u15 h7'.val B)
  · rintro ⟨h3', h4', p4', h7', p7', q'⟩ ⟨i3, i4, i7⟩
    simp only [slot.Z289_loop.body]
    split
    · step*
      all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
    · step*
  · exact ⟨h3, h4, h7⟩
@[local step] theorem u232 (input:I) (head3:C 16384#usize)
    (head4:C 65536#usize) (prev4) (head7:C 65536#usize) (prev7)
    (f e:R) (sh7:W) (B:Nat)
    (h3:EA.EA.u15 head3.val B) (h4:EA.EA.u15 head4.val B) (h7:EA.EA.u15 head7.val B)
    (he:e.val  ≤  B + 1) (he8:e.val + 8  ≤  Std.Usize.max) :
    slot.Z289 input head3 head4 prev4 head7 prev7 f e sh7 ⦃ fun r =>
      EA.EA.u15 r.1.val B  ∧  EA.EA.u15 r.2.1.val B  ∧  EA.EA.u15 r.2.2.2.1.val B ⦄ := by
  rw [slot.Z289]
  exact u231 input head3 head4 prev4 head7 prev7 e sh7 f B h3 h4 h7 he he8
theorem u233 {nextl:Array Std.U16 512#usize} (hnx:u205 nextl) (j:Nat)
    (hj:j < nextl.val.length):j < (nextl.val[j]).val := by
  have hl:nextl.val.length = 512 := by simp
  have := hnx j (by omega)
  rwa [List.getElem!_eq_getElem?_getD, List.getElem?_eq_getElem hj, Option.getD_some] at this
@[local step] theorem u234 (pa) (slt:R) (cost choice:W) :
    slot.Z301 pa slt cost choice ⦃ Y112P0! ⦄ := by
  have := u207
  rw [slot.Z301]
  step*
  repeat' (split <;> step*)
@[local step]
theorem u235 (pa lc) (nextl:Array Std.U16 512#usize) (i hi:R) (base dpack:W)
    (l:R) (hnx:u205 nextl) (hhi:hi.val  ≤  512) (hih:i.val + hi.val  ≤  Std.Usize.max) :
    slot.Z302_loop pa lc nextl i hi base dpack l ⦃ Y112P0! ⦄ := by
  have := u207
  rw [slot.Z302_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, l') => hi.val - l'.val)
    (inv := fun _ => True)
  · rintro ⟨pa', l'⟩ _
    simp only [slot.Z302_loop.body]
    split
    · step*
      repeat' (split <;> step*)
      all_goals
        have hx := u233 hnx i1.val (by scalar_tac)
        scalar_tac
    · step*
  · trivial
@[local step] theorem u236 (pa lc) (nextl:Array Std.U16 512#usize) (i lo hi:R)
    (base dpack:W) (hnx:u205 nextl) (hhi:hi.val < 512) (hih:i.val + hi.val  ≤  Std.Usize.max) :
    slot.Z302 pa lc nextl i lo hi base dpack ⦃ Y112P0! ⦄ := by
  have := u207
  rw [slot.Z302]
  step*
  repeat' (split <;> step*)
@[local step]
theorem u237 (input:I) (pa lc) (i s len dd t bt:R) (bv:W)
    (hi:i.val < input.length) (hlen:len.val < 512) (hdd:dd.val < 8388608)
    (hN:input.length + 2147483648  ≤  Std.Usize.max)
    (ht:t.val  ≤  i.val) (hbt:bt.val  ≤  t.val) (ht258:t.val = 0  ∨  len.val + t.val  ≤  258) :
    slot.Z190_loop input pa lc i s len dd t bt bv ⦃ fun r =>
      r.1.val  ≤  i.val  ∧  (r.1.val = 0  ∨  len.val + r.1.val  ≤  258) ⦄ := by
  have := u207
  rw [slot.Z190_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (t', _, _) => slot.Z6.val - t'.val)
    (inv := fun (t', bt', _) => t'.val  ≤  i.val  ∧  bt'.val  ≤  t'.val  ∧  (t'.val = 0  ∨  len.val + t'.val  ≤  258))
  · rintro ⟨t', bt', bv'⟩ ⟨h1, h2, h3⟩
    simp only [slot.Z190_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · exact ⟨ht, hbt, ht258⟩
@[local step] theorem u238 (input:I) (pa lc) (i s len dd:R)
    (hi:i.val < input.length) (hlen:len.val < 512) (hdd:dd.val < 8388608)
    (hN:input.length + 2147483648  ≤  Std.Usize.max) :
    slot.Z190 input pa lc i s len dd ⦃ fun r => r.1.val  ≤  i.val  ∧  (r.1.val = 0  ∨  len.val + r.1.val  ≤  258) ⦄ := by
  rw [slot.Z190]
  step*
@[local step] theorem u239 (dtab) (d:R):slot.Z270 dtab d ⦃ Y112P0! ⦄ := by
  rw [slot.Z270]
  step*
  repeat' (split <;> step*)
  all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
@[local step]
theorem u240 (input:I) (pa cands nc lc) (nextl:Array Std.U16 512#usize)
    (dtab dcc) (i s:R) (base:W) (pcd lo k:R)
    (hnx:u205 nextl) (hi:i.val < input.length) (hN:input.length + 2147483648  ≤  Std.Usize.max) :
    slot.Z300_loop input pa cands nc lc nextl dtab dcc i s base pcd lo k ⦃ Y112P0! ⦄ := by
  have := u207
  have := u214
  rw [slot.Z300_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, k') => 16 - k'.val)
    (inv := fun _ => True)
  · rintro ⟨pa', lo', k'⟩ _
    simp only [slot.Z300_loop.body]
    step*
    have := u216 c
    apply WP.spec_bind (Pₘ := fun _ => True)
    · repeat' (split <;> step*)
      all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
    · intro pa2 _
      step*
  · trivial
@[local step] theorem u241 (input:I) (pa cands nc lc) (nextl:Array Std.U16 512#usize)
    (dtab dcc) (i s:R) (base:W) (pcd:R)
    (hnx:u205 nextl) (hi:i.val < input.length) (hN:input.length + 2147483648  ≤  Std.Usize.max) :
    slot.Z300 input pa cands nc lc nextl dtab dcc i s base pcd ⦃ Y112P0! ⦄ := by
  rw [slot.Z300]
  step*
@[local step]
theorem u242 (cands) (cd nc:R) :
    slot.Z269_loop cands cd nc ⦃ Y112P0! ⦄ := by
  rw [slot.Z269_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun nc' => nc'.val)
    (inv := fun _ => True)
  · rintro nc' _
    simp only [slot.Z269_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · trivial
@[local step] theorem u243 (cands) (nc0 cd:R):slot.Z269 cands nc0 cd ⦃ Y112P0! ⦄ := by
  rw [slot.Z269]
  step*
@[local step] theorem u244 (anchor i cl best:R):slot.Z294 anchor i cl best ⦃ Y112P0! ⦄ := by
  rw [slot.Z294]
  repeat' (split <;> step*)
@[local step]
theorem u245 (input:I) (i d s max t:R)
    (hi:i.val < input.length) (hd:d.val < 8388608) (hN:input.length + 2147483648  ≤  Std.Usize.max)
    (hsi:s.val  ≤  i.val) (ht:t.val  ≤  i.val - s.val) :
    slot.Z274_loop input i d s max t ⦃ fun r => r.val  ≤  i.val - s.val ⦄ := by
  rw [slot.Z274_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun t' => max.val - t'.val)
    (inv := fun t' => t'.val  ≤  i.val - s.val)
  · rintro t' h1
    simp only [slot.Z274_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · exact ht
@[local step] theorem u246 (input:I) (i d s max:R)
    (hi:i.val < input.length) (hd:d.val < 8388608) (hN:input.length + 2147483648  ≤  Std.Usize.max)
    (hsi:s.val  ≤  i.val) :
    slot.Z274 input i d s max ⦃ fun r => r.val  ≤  i.val - s.val ⦄ := by
  rw [slot.Z274]
  step*
@[local step]
theorem u247 (pa) (s u:R) (hs:s.val + 259  ≤  Std.Usize.max) :
    slot.Z295_loop pa s u ⦃ Y112P0! ⦄ := by
  have := u207
  rw [slot.Z295_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, u') => 259 - u'.val)
    (inv := fun _ => True)
  · rintro ⟨pa', u'⟩ _
    simp only [slot.Z295_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · trivial
@[local step] theorem u248 (pa) (s:R) (hs:s.val + 259  ≤  Std.Usize.max) :
    slot.Z295 pa s ⦃ Y112P0! ⦄ := by
  have := u207
  rw [slot.Z295]
  step*
@[local step]
theorem u249 (plan tb lim k):slot.Z299_loop plan tb lim k ⦃ Y112P0! ⦄ := by
  have := u207
  rw [slot.Z299_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, k') => k'.val)
    (inv := fun _ => True)
  · rintro ⟨plan', k'⟩ _
    simp only [slot.Z299_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · trivial
@[local step] theorem u250 (plan tb nt lim):slot.Z299 plan tb nt lim ⦃ Y112P0! ⦄ := by
  rw [slot.Z299]
  step*
@[local step]
theorem u251 (input:I) (pa) (s:R) (lsym dtab lf df tb) (j nt guard:R)
    (hs:s.val  ≤  j.val) (hg:nt.val + guard.val  ≤  Std.Usize.max) :
    slot.Z191_loop input pa s lsym dtab lf df tb j nt guard ⦃ Y112P0! ⦄ := by
  have := u207
  rw [slot.Z191_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, _, g') => g'.val)
    (inv := fun (_, _, _, j', nt', g') => s.val  ≤  j'.val  ∧  nt'.val + g'.val  ≤  Std.Usize.max)
  · rintro ⟨lf', df', tb', j', nt', g'⟩ ⟨h1, h2⟩
    simp only [slot.Z191_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · exact ⟨hs, hg⟩
@[local step] theorem u252 (input:I) (pa plan) (s e:R) (lsym dtab lf df tb)
    (hse:s.val  ≤  e.val) (he:e.val < Std.Usize.max) :
    slot.Z191 input pa plan s e lsym dtab lf df tb ⦃ Y112P0! ⦄ := by
  rw [slot.Z191]
  step*
@[local step]
theorem u253 (lf s):slot.Z277_loop0 lf s ⦃ Y112P0! ⦄ := by
  rw [slot.Z277_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, s') => 286 - s'.val)
    (inv := fun _ => True)
  · rintro ⟨lf', s'⟩ _
    simp only [slot.Z277_loop0.body]
    step*
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · trivial
@[local step]
theorem u254 (df k):slot.Z277_loop1 df k ⦃ Y112P0! ⦄ := by
  rw [slot.Z277_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, k') => 30 - k'.val)
    (inv := fun _ => True)
  · rintro ⟨df', k'⟩ _
    simp only [slot.Z277_loop1.body]
    step*
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · trivial
@[local step] theorem u255 (lf df):slot.Z277 lf df ⦃ Y112P0! ⦄ := by
  rw [slot.Z277]
  step*
@[local step] theorem u256 (x:W):slot.Z291 x ⦃ Y112P0! ⦄ := by
  rw [slot.Z291]
  split
  · step*
  · step*
    all_goals try (have := u202 x)
    repeat' (split <;> step*)
    all_goals try (have := EA.EA.u16 u215 i3.val (by (subst_vars;scalar_tac (simpAllMaxSteps := 0))))
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
@[local step]
theorem u257 (freq total s):slot.Z225_loop0 freq total s ⦃ Y112P0! ⦄ := by
  rw [slot.Z225_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, s') => freq.length - s'.val)
    (inv := fun _ => True)
  · rintro ⟨total', s'⟩ _
    simp only [slot.Z225_loop0.body]
    step*
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · trivial
@[local step]
theorem u258 (freq out lt t):slot.Z225_loop1 freq out lt t ⦃ Y112P0! ⦄ := by
  rw [slot.Z225_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, t') => freq.length - t'.val)
    (inv := fun _ => True)
  · rintro ⟨out', t'⟩ _
    simp only [slot.Z225_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · trivial
@[local step] theorem u259 (freq out):slot.Z225 freq out ⦃ Y112P0! ⦄ := by
  rw [slot.Z225]
  step*
@[local step]
theorem u260 (freq:U) (sym) (f:W) (j:R) (hf:0 < freq.length) :
    slot.Z284_loop freq sym f j ⦃ Y112P0! ⦄ := by
  rw [slot.Z284_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, j') => j'.val)
    (inv := fun _ => True)
  · rintro ⟨sym', j'⟩ _
    simp only [slot.Z284_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · trivial
@[local step] theorem u261 (freq:U) (sym) (ns:R) (f:W) (hf:0 < freq.length) :
    slot.Z284 freq sym ns f ⦃ Y112P0! ⦄ := by
  rw [slot.Z284]
  step*
@[local step]
theorem u262 (freq:U) (m sym) (ns i:R)
    (hf:0 < freq.length) (hns:ns.val  ≤  i.val) (hi:i.val  ≤  320) :
    slot.Z285_loop freq m sym ns i ⦃ fun r => r.1.val  ≤  320 ⦄ := by
  rw [slot.Z285_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, i') => 320 - i'.val)
    (inv := fun (_, ns', i') => ns'.val  ≤  i'.val  ∧  i'.val  ≤  320)
  · rintro ⟨sym', ns', i'⟩ ⟨h1, h2⟩
    simp only [slot.Z285_loop.body]
    step*
    apply WP.spec_bind (Pₘ := fun (x:Std.Array R 320#usize  ×  R) => x.2.val  ≤  ns'.val + 1)
    · split
      · step*
      · step*
    · intro x hx
      rcases x with ⟨sym1, ns1⟩
      step*
      all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · exact ⟨hns, hi⟩
@[local step] theorem u263 (freq:U) (m sym) (hf:0 < freq.length) :
    slot.Z285 freq m sym ⦃ fun r => r.1.val  ≤  320 ⦄ := by
  rw [slot.Z285]
  step*
@[local step] theorem u264 (w) (a b ns nx:R) (hab:a.val + b.val < Std.Usize.max) :
    slot.Z286 w a b ns nx ⦃ fun r => r.2.1.val + r.2.2.val = a.val + b.val + 1 ⦄ := by
  rw [slot.Z286]
  step*
  repeat' (split <;> step*)
  all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
@[local step]
theorem u265 (w par) (ns a b nx:R) (hns:ns.val  ≤  320) (hnx:nx.val  ≤  639)
    (hab:a.val + b.val + ns.val = 2 * nx.val) :
    slot.Z281_loop w par ns a b nx ⦃ Y112P0! ⦄ := by
  rw [slot.Z281_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, nx') => 639 - nx'.val)
    (inv := fun (_, _, a', b', nx') => nx'.val  ≤  639  ∧  a'.val + b'.val + ns.val = 2 * nx'.val)
  · rintro ⟨w', par', a', b', nx'⟩ ⟨h1, h2⟩
    simp only [slot.Z281_loop.body]
    step*
    rcases y with ⟨i7, a1, b1⟩
    step*
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · exact ⟨hnx, hab⟩
@[local step] theorem u266 (w par) (ns:R) (hns:ns.val  ≤  320) :
    slot.Z281 w par ns ⦃ Y112P0! ⦄ := by
  rw [slot.Z281]
  step*
@[local step]
theorem u267 (par depth ns mx q):slot.Z283_loop par depth ns mx q ⦃ Y112P0! ⦄ := by
  rw [slot.Z283_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, q') => q'.val)
    (inv := fun _ => True)
  · rintro ⟨depth', mx', q'⟩ _
    simp only [slot.Z283_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · trivial
@[local step] theorem u268 (par depth nx ns):slot.Z283 par depth nx ns ⦃ Y112P0! ⦄ := by
  rw [slot.Z283]
  step*
  repeat' (split <;> step*)
@[local step]
theorem u269 (freq:U) (sym ns w k) (hf:0 < freq.length) :
    slot.Z282_loop0 freq sym ns w k ⦃ Y112P0! ⦄ := by
  rw [slot.Z282_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, k') => ns.val - k'.val)
    (inv := fun _ => True)
  · rintro ⟨w', k'⟩ _
    simp only [slot.Z282_loop0.body]
    step*
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · trivial
@[local step]
theorem u270 (m out) (mx:W) (t:R) (hmx:mx.val  ≤  15) :
    slot.Z282_loop1 m out mx t ⦃ Y112P0! ⦄ := by
  rw [slot.Z282_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, t') => m.val - t'.val)
    (inv := fun _ => True)
  · rintro ⟨out', t'⟩ _
    simp only [slot.Z282_loop1.body]
    step*
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · trivial
@[local step]
theorem u271 (out sym ns depth r):slot.Z282_loop2 out sym ns depth r ⦃ Y112P0! ⦄ := by
  rw [slot.Z282_loop2]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, r') => ns.val - r'.val)
    (inv := fun _ => True)
  · rintro ⟨out', r'⟩ _
    simp only [slot.Z282_loop2.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · trivial
@[local step] theorem u272 (freq:U) (m out) (hf:0 < freq.length) :
    slot.Z282 freq m out ⦃ Y112P0! ⦄ := by
  rw [slot.Z282]
  step*
  apply WP.spec_bind (Pₘ := fun _ => True)
  · split
    · step*
    · step*
  · intro x _
    rcases x with ⟨depth1, mx⟩
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
@[local step]
theorem u273 (litc llc b):slot.Z292_loop0 litc llc b ⦃ Y112P0! ⦄ := by
  rw [slot.Z292_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, b') => 256 - b'.val)
    (inv := fun _ => True)
  · rintro ⟨litc', b'⟩ _
    simp only [slot.Z292_loop0.body]
    step*
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · trivial
@[local step]
theorem u274 (lsym:G 512#usize) (lc) (llc:C 286#usize) (l:R)
    (hls:EA.EA.u15 lsym.val 28):slot.Z292_loop1 lsym lc llc l ⦃ Y112P0! ⦄ := by
  rw [slot.Z292_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, l') => 259 - l'.val)
    (inv := fun _ => True)
  · rintro ⟨lc', l'⟩ _
    simp only [slot.Z292_loop1.body]
    step*
    all_goals try (have := EA.EA.u16 hls l'.val (by (subst_vars;scalar_tac (simpAllMaxSteps := 0))))
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · trivial
@[local step]
theorem u275 (dcc dc k):slot.Z292_loop2 dcc dc k ⦃ Y112P0! ⦄ := by
  rw [slot.Z292_loop2]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, k') => 30 - k'.val)
    (inv := fun _ => True)
  · rintro ⟨dcc', k'⟩ _
    simp only [slot.Z292_loop2.body]
    step*
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · trivial
@[local step] theorem u276 (lf df) (lsym:G 512#usize) (litc lc dcc huff)
    (hls:EA.EA.u15 lsym.val 28):slot.Z292 lf df lsym litc lc dcc huff ⦃ Y112P0! ⦄ := by
  rw [slot.Z292]
  step*
  apply WP.spec_bind (Pₘ := fun _ => True)
  · split
    · step*
    · step*
  · intro x _
    rcases x with ⟨llc1, dc1⟩
    step*
@[local step]
theorem u277 (lf tot z):slot.Z306_loop lf tot z ⦃ Y112P0! ⦄ := by
  rw [slot.Z306_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, z') => 286 - z'.val)
    (inv := fun _ => True)
  · rintro ⟨tot', z'⟩ _
    simp only [slot.Z306_loop.body]
    step*
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · trivial
@[local step] theorem u278 (lf df) (lsym:G 512#usize) (litc lc dcc huff)
    (hls:EA.EA.u15 lsym.val 28):slot.Z306 lf df lsym litc lc dcc huff ⦃ Y112P0! ⦄ := by
  rw [slot.Z306]
  step*
  repeat' (split <;> step*)
@[local step]
theorem u279 (input:I) (lf) (n step i:R)
    (hn:n.val = input.length) (hstep:1  ≤  step.val) (hns:n.val + step.val  ≤  Std.Usize.max) :
    slot.Z287_loop0 input lf n step i ⦃ Y112P0! ⦄ := by
  rw [slot.Z287_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, i') => n.val - i'.val)
    (inv := fun _ => True)
  · rintro ⟨lf', i'⟩ _
    simp only [slot.Z287_loop0.body]
    step*
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · trivial
@[local step]
theorem u280 (lf s):slot.Z287_loop1 lf s ⦃ Y112P0! ⦄ := by
  rw [slot.Z287_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, s') => 286 - s'.val)
    (inv := fun _ => True)
  · rintro ⟨lf', s'⟩ _
    simp only [slot.Z287_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · trivial
@[local step]
theorem u281 (df k):slot.Z287_loop2 df k ⦃ Y112P0! ⦄ := by
  rw [slot.Z287_loop2]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, k') => 30 - k'.val)
    (inv := fun _ => True)
  · rintro ⟨df', k'⟩ _
    simp only [slot.Z287_loop2.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · trivial
@[local step] theorem u282 (input:I) (lf df)
    (hN:input.length + input.length  ≤  Std.Usize.max) :
    slot.Z287 input lf df ⦃ Y112P0! ⦄ := by
  rw [slot.Z287]
  step*
  all_goals
    have h1 := u218 (input.length / 8192)
    have h2:1  ≤  input.length / 8192 ||| 1 := Nat.right_le_or
    scalar_tac
@[local step]
theorem u283 (lsym:G 512#usize) (code l:R)
    (hc:code.val  ≤  28) (hls:EA.EA.u15 lsym.val 28) :
    slot.Z275_loop0 lsym code l ⦃ fun r => EA.EA.u15 r.val 28 ⦄ := by
  rw [slot.Z275_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, l') => 259 - l'.val)
    (inv := fun (ls', c', _) => c'.val  ≤  28  ∧  EA.EA.u15 ls'.val 28)
  · rintro ⟨ls', c', l'⟩ ⟨h1, h2⟩
    simp only [slot.Z275_loop0.body]
    split
    · apply WP.spec_bind (Pₘ := fun (x:R) => x.val  ≤  28)
      · repeat' (split <;> step*)
        all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
      · intro code1 hc1
        step*
        and_intros
        all_goals first
          | exact u219 a_post h2 (by (subst_vars;scalar_tac (simpAllMaxSteps := 0)))
          | (subst_vars;scalar_tac (simpAllMaxSteps := 0))
    · step*
  · exact ⟨hc, hls⟩
@[local step]
theorem u284 (dtab c j):slot.Z275_loop1 dtab c j ⦃ Y112P0! ⦄ := by
  rw [slot.Z275_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, j') => 256 - j'.val)
    (inv := fun _ => True)
  · rintro ⟨dtab', c', j'⟩ _
    simp only [slot.Z275_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · trivial
@[local step]
theorem u285 (c2 d):slot.Z275_loop2_loop0 c2 d ⦃ Y112P0! ⦄ := by
  rw [slot.Z275_loop2_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun c2' => 29 - c2'.val)
    (inv := fun _ => True)
  · rintro c2' _
    simp only [slot.Z275_loop2_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · trivial
@[local step]
theorem u286 (dtab c2 k):slot.Z275_loop2 dtab c2 k ⦃ Y112P0! ⦄ := by
  rw [slot.Z275_loop2]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, k') => 256 - k'.val)
    (inv := fun _ => True)
  · rintro ⟨dtab', c2', k'⟩ _
    simp only [slot.Z275_loop2.body]
    step*
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · trivial
@[local step] theorem u287 (lsym:G 512#usize) (dtab) (hls:EA.EA.u15 lsym.val 28) :
    slot.Z275 lsym dtab ⦃ fun r => EA.EA.u15 r.1.val 28 ⦄ := by
  rw [slot.Z275]
  step*
theorem u288 (x y:R) :
    (core.num.Usize.saturating_sub x y).val = x.val - y.val := by
  have hx := x.hBounds
  show (BitVec.ofNat _ (max 0 (x.val - y.val))).toNat = x.val - y.val
  rw [BitVec.toNat_ofNat, Nat.zero_max]
  exact Nat.mod_eq_of_lt (lt_of_le_of_lt (Nat.sub_le _ _) hx)
theorem u289 {α:Type} {a b c:Prop} [Decidable a] [Decidable b] [Decidable c]
    {X Y:Result α} {P:α  →  Prop} (hX:a  →  b  →  ¬c  →  X ⦃ P ⦄) (hY:Y ⦃ P ⦄) :
    (if a then (if b then (if c then Y else X) else Y) else Y) ⦃ P ⦄ := by
  by_cases ha:a
  · rw [if_pos ha]
    by_cases hb:b
    · rw [if_pos hb]
      by_cases hc:c
      · rw [if_pos hc];exact hY
      · rw [if_neg hc];exact hX ha hb hc
    · rw [if_neg hb];exact hY
  · rw [if_neg ha];exact hY
theorem u290 {α:Type} {a b:Prop} [Decidable a] [Decidable b]
    {X Y:Result α} {P:α  →  Prop} (hX:a  →  b  →  X ⦃ P ⦄) (hY:Y ⦃ P ⦄) :
    (if a then (if b then X else Y) else Y) ⦃ P ⦄ := by
  by_cases ha:a
  · rw [if_pos ha]
    by_cases hb:b
    · rw [if_pos hb];exact hX ha hb
    · rw [if_neg hb];exact hY
  · rw [if_neg ha];exact hY
@[local step]
theorem u291 (v x)  :
    slot.Z255 v x ⦃ Y112P5! ⦄ := Y127U12! slot.Z255
@[local step]
theorem u292 (s i)  :
    slot.Z232 s i ⦃ Y112P5! ⦄ := Y127U12! slot.Z232
@[local step]
theorem u293 (ring i)  :
    slot.Z234 ring i ⦃ Y112P5! ⦄ := Y127U12! slot.Z234
@[local step]
theorem u294 (a b)  :
    slot.Z248 a b ⦃ fun r => r.val  ≤  a.val  ∧  r.val  ≤  b.val ⦄ := Y127U12! slot.Z248
theorem u295 {α:Type} {x:α} {P:α  →  Prop} (h:P x):WP.spec (ok x) P :=
  (WP.spec_ok x).2 h
theorem u296 {α:Type} {c:Prop} {inst:Decidable c} {X Y:Result α} {P:α  →  Prop}
    (hX:c  →  WP.spec X P) (hY:¬c  →  WP.spec Y P):WP.spec (@ite _ c inst X Y) P := by
  by_cases h:c
  · rw [if_pos h];exact hX h
  · rw [if_neg h];exact hY h
theorem u297 {α β:Type} {m:Result α} {Q:α  →  Prop} {k:α  →  Result β} {P:β  →  Prop}
    (hm:WP.spec m Q) (hk:∀ x, Q x  →  WP.spec (k x) P):WP.spec (Bind.bind m k) P :=
  WP.spec_bind hm hk
theorem u298 {α β:Type} {m:Result α} {Q:α  →  Prop} {k:α  →  Result β} {P:β  →  Prop}
    (hm:WP.spec m Q) (hk:∀ x, WP.spec (k x) P):WP.spec (Bind.bind m k) P :=
  WP.spec_bind hm (fun x _ => hk x)
theorem u299 {α:Type} {m:Result α} {Q:α  →  Prop} (h:WP.spec m Q):WP.spec m (fun _ => True) :=
  WP.spec_mono h (fun _ _ => trivial)
theorem u300 {ty:UScalarTy} {β:Type} {x y:UScalar ty} {k:UScalar ty  →  Result β} {P:β  →  Prop}
    (w:UScalar ty) (h:x.val + y.val  ≤  w.val) (hk:∀ z:UScalar ty, z.val = x.val + y.val  →  WP.spec (k z) P) :
    WP.spec (Bind.bind (HAdd.hAdd x y:Result (UScalar ty)) k) P :=
  WP.spec_bind (UScalar.add_spec (Nat.le_trans h (ScalarTac.UScalar.bounds w))) hk
theorem u301 {ty:UScalarTy} {x y:UScalar ty} (w:UScalar ty) (h:x.val + y.val  ≤  w.val) :
    WP.spec (HAdd.hAdd x y:Result (UScalar ty)) (fun _ => True) :=
  u299 (UScalar.add_spec (Nat.le_trans h (ScalarTac.UScalar.bounds w)))
theorem u302 {ty:UScalarTy} {β:Type} {x y:UScalar ty} {k:UScalar ty  →  Result β} {P:β  →  Prop}
    (h:y.val  ≤  x.val) (hk:∀ z:UScalar ty, z.val + y.val = x.val  →  WP.spec (k z) P) :
    WP.spec (Bind.bind (HSub.hSub x y:Result (UScalar ty)) k) P :=
  WP.spec_bind (UScalar.sub_spec h) (fun z hz => hk z ((congrArg (· + y.val) hz.1).trans (Nat.sub_add_cancel h)))
theorem u303 {ty:UScalarTy} {β:Type} {x y:UScalar ty} {k:UScalar ty  →  Result β} {P:β  →  Prop}
    (h:0 < y.val) (hk:∀ z:UScalar ty, z.val < y.val  →  WP.spec (k z) P) :
    WP.spec (Bind.bind (HMod.hMod x y:Result (UScalar ty)) k) P :=
  WP.spec_bind (UScalar.rem_spec x (Nat.pos_iff_ne_zero.mp h)) (fun z hz => hk z (hz ▸ Nat.mod_lt _ h))
theorem u304 {β:Type} {x y:R} {k:R  →  Result β} {P:β  →  Prop}
    (h:y.val ≠ 0) (hk:∀ z:R, WP.spec (k z) P) :
    WP.spec (Bind.bind (HDiv.hDiv x y:Result R) k) P :=
  WP.spec_bind (Usize.div_spec x h) (fun z _ => hk z)
theorem u305 {ty ty1:UScalarTy} {β:Type} {x:UScalar ty} {y:UScalar ty1} {k:UScalar ty  →  Result β}
    {P:β  →  Prop} (h:y.val < ty.numBits) (hk:∀ z:UScalar ty, WP.spec (k z) P) :
    WP.spec (Bind.bind (HShiftRight.hShiftRight x y:Result (UScalar ty)) k) P :=
  WP.spec_bind (UScalar.ShiftRight_spec x y h) (fun z _ => hk z)
theorem u306 {ty ty1:UScalarTy} {β:Type} {x:UScalar ty} {y:UScalar ty1} {k:UScalar ty  →  Result β}
    {P:β  →  Prop} (h:y.val < ty.numBits) (hk:∀ z:UScalar ty, WP.spec (k z) P) :
    WP.spec (Bind.bind (HShiftLeft.hShiftLeft x y:Result (UScalar ty)) k) P :=
  WP.spec_bind (UScalar.ShiftLeft_spec x y _ h rfl) (fun z _ => hk z)
theorem u307 {ty:UScalarTy} {ty1:IScalarTy} {β:Type} {x:UScalar ty} {y:IScalar ty1}
    {k:UScalar ty  →  Result β} {P:β  →  Prop} (h0:0  ≤  y.val) (h:y.val < ty.numBits)
    (hk:∀ z:UScalar ty, WP.spec (k z) P) :
    WP.spec (Bind.bind (HShiftRight.hShiftRight x y:Result (UScalar ty)) k) P :=
  WP.spec_bind (UScalar.ShiftRight_IScalar_spec x y h0 h) (fun z _ => hk z)
theorem u308 {α β:Type} {n:R} {a:Std.Array α n} {i:R} {k:α  →  Result β} {P:β  →  Prop}
    (h:i.val < n.val) (hk:∀ x, WP.spec (k x) P):WP.spec (Bind.bind (Array.index_usize a i) k) P :=
  WP.spec_bind (Array.index_usize_spec a i (Nat.lt_of_lt_of_eq h a.property.symm)) (fun x _ => hk x)
theorem u309 {α β:Type} {n:R} {a:Std.Array α n} {i:R} {v:α}
    {k:Std.Array α n  →  Result β} {P:β  →  Prop} (h:i.val < n.val) (hk:∀ x, WP.spec (k x) P) :
    WP.spec (Bind.bind (Array.update a i v) k) P :=
  WP.spec_bind (Array.update_spec a i v (Nat.lt_of_lt_of_eq h a.property.symm)) (fun x _ => hk x)
theorem u310 {α β:Type} {s:Slice α} {i:R} {k:α  →  Result β} {P:β  →  Prop}
    (h:i.val < (Slice.len s).val) (hk:∀ x, WP.spec (k x) P) :
    WP.spec (Bind.bind (Slice.index_usize s i) k) P :=
  WP.spec_bind (Slice.index_usize_spec s i h) (fun x _ => hk x)
theorem u311 (b:Std.U8):(UScalar.cast .Usize b).val < (288#usize).val := by
  rw [U8.cast_Usize_val_eq];exact Nat.lt_of_le_of_lt (U8.le_max b) (by decide)
theorem u312 (l:Std.U8) {n:Nat} (h:l.val < n + 1):(UScalar.cast .U32 l).val  ≤  n := by
  rw [U8.cast_U32_val_eq];exact Nat.le_of_lt_succ h
theorem u313 {n:Nat}:0 < n + 1 := Nat.zero_lt_succ n
theorem u314 {a b:Nat} (h:a + 1 = b):a < b := h ▸ Nat.lt_succ_self a
theorem u315 {e l l1:Nat} (h:l < e) (h1:l1 = l + 1):e - l1 < e - l :=
  h1 ▸ Nat.sub_succ_lt_self e l h
theorem u316 {e l d l1:Nat} (h:l < e) (hd:0 < d) (h1:l1 = l + d):e - l1 < e - l :=
  h1 ▸ Nat.sub_lt_sub_left h (Nat.lt_add_of_pos_right hd)
theorem u317 {a b c n:Nat} (h:b  ≤  c) (hc:c + a = n):a + b  ≤  n :=
  Nat.le_trans (Nat.add_le_add_left h a) (Nat.le_of_eq ((Nat.add_comm a c).trans hc))
@[local step]
theorem u318 (w a b ns nx) :
    slot.Z264 w a b ns nx ⦃ Y112P0! ⦄ := by
  simp only [slot.Z264, lift, bind_tc_ok]
  refine u296 (fun ha => ?_) (fun _ => u295 trivial)
  refine u296 (fun _ => ?_) (fun _ => ?_)
  · exact u300 ns (Nat.succ_le_of_lt ha) fun _ _ => u295 trivial
  · refine u303 u313 fun i hi => ?_
    refine u308 hi fun i1 => ?_
    refine u303 u313 fun i2 hi2 => ?_
    refine u308 hi2 fun i3 => ?_
    exact u296 (fun _ => u300 ns (Nat.succ_le_of_lt ha) fun _ _ => u295 trivial) (fun _ => u295 trivial)
@[local step]
theorem u319 (d) :
    slot.Z235 d ⦃ Y112P0! ⦄ := by
  rw [slot.Z235]
  exact u296 (fun _ => u295 trivial) (fun _ => u296 (fun _ => u295 trivial) (fun _ => u295 trivial))
@[local step]
theorem u320 (freq sym f j) :
    slot.Z243_loop0_loop0 freq sym f j ⦃ Y112P0! ⦄ := by
  rw [slot.Z243_loop0_loop0]
  apply Std.loop.spec_decr_nat (measure := fun x => x.2.val) (inv := fun _ => True)
  · rintro ⟨sym', j'⟩ _
    simp only [slot.Z243_loop0_loop0.body, lift, bind_tc_ok]
    refine u296 (fun hj => ?_) (fun _ => u295 trivial)
    refine u302 (Nat.succ_le_of_lt hj) fun i hi => ?_
    refine u303 u313 fun i1 hi1 => ?_
    refine u308 hi1 fun i2 => ?_
    refine u303 u313 fun i4 hi4 => ?_
    refine u308 hi4 fun i5 => ?_
    refine u296 (fun _ => ?_) (fun _ => u295 trivial)
    refine u303 u313 fun i6 hi6 => ?_
    refine u308 hi6 fun i7 => ?_
    refine u303 u313 fun i8 hi8 => ?_
    refine u309 hi8 fun a => ?_
    exact u295 ⟨trivial, u314 hi⟩
  · trivial
@[local step]
theorem u321 (freq m len sym ns i) :
    slot.Z243_loop0 freq m len sym ns i ⦃ Y112P0! ⦄ := by
  rw [slot.Z243_loop0]
  apply Std.loop.spec_decr_nat (measure := fun x => 288 - x.2.2.2.val) (inv := fun _ => True)
  · rintro ⟨len', sym', ns', i'⟩ _
    simp only [slot.Z243_loop0.body, lift, bind_tc_ok]
    refine u296 (fun _ => ?_) (fun _ => u295 trivial)
    refine u296 (fun hi => ?_) (fun _ => u295 trivial)
    refine u308 hi fun f => ?_
    refine u296 (fun _ => ?_) (fun _ => ?_)
    · refine u298 (u320 _ _ _ _) fun ⟨sym1, j⟩ => ?_
      refine u303 u313 fun i1 hi1 => ?_
      refine u309 hi1 fun a => ?_
      refine u309 hi fun a1 => ?_
      refine u300 288#usize (Nat.succ_le_of_lt hi) fun i3 hi3 => ?_
      exact u295 ⟨trivial, u315 hi hi3⟩
    · refine u309 hi fun a => ?_
      refine u300 288#usize (Nat.succ_le_of_lt hi) fun i1 hi1 => ?_
      exact u295 ⟨trivial, u315 hi hi1⟩
  · trivial
@[local step]
theorem u322 (freq sym ns w k) :
    slot.Z243_loop1 freq sym ns w k ⦃ Y112P0! ⦄ := by
  rw [slot.Z243_loop1]
  apply Std.loop.spec_decr_nat (measure := fun x => ns.val - x.2.val) (inv := fun _ => True)
  · rintro ⟨w', k'⟩ _
    simp only [slot.Z243_loop1.body, lift, bind_tc_ok]
    refine u296 (fun hk => ?_) (fun _ => u295 trivial)
    refine u303 u313 fun i hi => ?_
    refine u308 hi fun i1 => ?_
    refine u303 u313 fun i3 hi3 => ?_
    refine u308 hi3 fun i4 => ?_
    refine u303 u313 fun i5 hi5 => ?_
    refine u309 hi5 fun a => ?_
    refine u300 ns (Nat.succ_le_of_lt hk) fun k1 hk1 => ?_
    exact u295 ⟨trivial, u315 hk hk1⟩
  · trivial
@[local step]
theorem u323 (ns w par a b nx) :
    slot.Z243_loop2 ns w par a b nx ⦃ Y112P0! ⦄ := by
  rw [slot.Z243_loop2]
  apply Std.loop.spec_decr_nat (measure := fun x => 575 - x.2.2.2.2.val) (inv := fun _ => True)
  · rintro ⟨w', par', a', b', nx'⟩ _
    simp only [slot.Z243_loop2.body, lift, bind_tc_ok]
    refine u296 (fun hn => ?_) (fun _ => u295 trivial)
    refine u300 575#usize (Nat.succ_le_of_lt hn) fun i hi => ?_
    refine u304 (by decide) fun i1 => ?_
    refine u296 (fun _ => ?_) (fun _ => u295 trivial)
    refine u298 (u318 _ _ _ _ _) fun ⟨x, a1, b1⟩ => ?_
    refine u298 (u318 _ _ _ _ _) fun ⟨y, a2, b2⟩ => ?_
    refine u303 u313 fun i2 hi2 => ?_
    refine u308 hi2 fun i3 => ?_
    refine u303 u313 fun i4 hi4 => ?_
    refine u308 hi4 fun i5 => ?_
    refine u303 u313 fun i7 hi7 => ?_
    refine u309 hi7 fun a3 => ?_
    refine u309 hi2 fun par1 => ?_
    refine u309 hi4 fun a4 => ?_
    exact u295 ⟨trivial, u315 hn hi⟩
  · trivial
@[local step]
theorem u324 (par depth q) :
    slot.Z243_loop3 par depth q ⦃ Y112P0! ⦄ := by
  rw [slot.Z243_loop3]
  apply Std.loop.spec_decr_nat (measure := fun x => x.2.val) (inv := fun _ => True)
  · rintro ⟨depth', q'⟩ _
    simp only [slot.Z243_loop3.body, lift, bind_tc_ok]
    refine u296 (fun hq => ?_) (fun _ => u295 trivial)
    refine u302 (Nat.succ_le_of_lt hq) fun q1 hq1 => ?_
    refine u303 u313 fun i hi => ?_
    refine u308 hi fun i1 => ?_
    refine u303 u313 fun i3 hi3 => ?_
    refine u308 hi3 fun i4 => ?_
    refine u309 hi fun a => ?_
    exact u295 ⟨trivial, u314 hq1⟩
  · trivial
@[local step]
theorem u325 (len sym ns k depth mx kraft) :
    slot.Z243_loop4 len sym ns k depth mx kraft ⦃ Y112P0! ⦄ := by
  rw [slot.Z243_loop4]
  apply Std.loop.spec_decr_nat (measure := fun x => ns.val - x.2.1.val) (inv := fun _ => True)
  · rintro ⟨len', k', mx', kraft'⟩ _
    simp only [slot.Z243_loop4.body, EA.EA.u37, lift, bind_tc_ok]
    refine u296 (fun hk => ?_) (fun _ => u295 trivial)
    refine u303 u313 fun i hi => ?_
    refine u308 hi fun i1 => ?_
    refine u298 (u319 _) fun l => ?_
    refine u303 u313 fun i2 hi2 => ?_
    refine u305 (Nat.lt_trans hi2 (by decide)) fun i3 => ?_
    refine u303 u313 fun i4 hi4 => ?_
    refine u308 hi4 fun i5 => ?_
    refine u303 u313 fun i7 hi7 => ?_
    refine u309 hi7 fun a => ?_
    refine u300 ns (Nat.succ_le_of_lt hk) fun k1 hk1 => ?_
    exact u295 ⟨trivial, u315 hk hk1⟩
  · trivial
@[local step]
theorem u326 (len sym ns mx kraft r fuel) :
    slot.Z243_loop5 len sym ns mx kraft r fuel ⦃ Y112P0! ⦄ := by
  rw [slot.Z243_loop5]
  apply Std.loop.spec_decr_nat (measure := fun x => x.2.2.2.2.val) (inv := fun _ => True)
  · rintro ⟨len', mx', kraft', r', fuel'⟩ _
    simp only [slot.Z243_loop5.body, lift, bind_tc_ok]
    refine u296 (fun _ => ?_) (fun _ => u295 trivial)
    refine u296 (fun hr => ?_) (fun _ => u295 trivial)
    refine u296 (fun hf => ?_) (fun _ => u295 trivial)
    refine u302 (Nat.succ_le_of_lt hf) fun fuel1 hf1 => ?_
    refine u303 u313 fun i hi => ?_
    refine u308 hi fun i1 => ?_
    refine u303 u313 fun s2 hs2 => ?_
    refine u308 hs2 fun l => ?_
    refine u296 (fun hl => ?_) (fun _ => ?_)
    · have hc := u312 l (n := 14) hl
      refine u302 hc fun i4 hi4 => ?_
      refine u306 (Nat.lt_of_le_of_lt (Nat.le_of_add_right_le (Nat.le_of_eq hi4)) (by decide)) fun i5 => ?_
      refine u300 15#u32 (Nat.succ_le_succ hc) fun i7 _ => ?_
      refine u298 (Q := fun _ => True)
        (u296 (fun _ => u301 15#u32 (Nat.succ_le_succ hc)) (fun _ => u295 trivial)) fun mx1 => ?_
      refine u300 15#u8 (Nat.succ_le_of_lt hl) fun i8 _ => ?_
      refine u309 hs2 fun a => ?_
      exact u295 ⟨trivial, u314 hf1⟩
    · refine u300 ns (Nat.succ_le_of_lt hr) fun r1 _ => ?_
      exact u295 ⟨trivial, u314 hf1⟩
  · trivial
@[local step]
theorem u327 (freq m len) :
    slot.Z243 freq m len ⦃ Y112P0! ⦄ := by
  simp only [slot.Z243, lift, bind_tc_ok]
  refine u298 (u321 _ _ _ _ _ _) fun ⟨len1, sym1, ns⟩ => ?_
  refine u296 (fun _ => u295 trivial) (fun _ => ?_)
  refine u296 (fun _ => ?_) (fun _ => ?_)
  · refine u308 (by decide) fun i => ?_
    refine u303 u313 fun i2 hi2 => ?_
    exact u309 hi2 fun _ => u295 trivial
  · refine u298 (u322 _ _ _ _ _) fun w1 => ?_
    refine u298 (u323 _ _ _ _ _ _) fun ⟨par1, nx⟩ => ?_
    refine u298 (u324 _ _ _) fun depth1 => ?_
    refine u298 (u325 _ _ _ _ _ _ _) fun ⟨len2, mx, kraft⟩ => ?_
    exact u326 _ _ _ _ _ _ _
@[local step]
theorem u328 (f lt) :
    slot.Z238 f lt ⦃ Y112P0! ⦄ := by
  rw [slot.Z238]
  refine u298 (Q := fun _ => True)
    (u296 (fun _ => u295 trivial) (fun _ => u298 (u256 _) fun _ => u295 trivial)) fun e => ?_
  exact u296 (fun _ => u295 trivial) (fun _ => u296 (fun _ => u295 trivial) (fun _ => u295 trivial))
@[local step]
theorem u329 (h e ck) :
    slot.Z249 h e ck ⦃ Y112P0! ⦄ := by
  simp only [slot.Z249, EA.EA.u37, lift, bind_tc_ok]
  refine u296 (fun _ => u295 trivial) (fun _ => ?_)
  refine u296 (fun _ => u295 trivial) (fun _ => ?_)
  refine u296 (fun _ => u299 (U32.div_spec _ (by decide))) (fun _ => ?_)
  refine u296 (fun hgt => ?_) (fun hle => ?_)
  · exact u302 (Nat.le_of_lt hgt) fun _ _ => u295 trivial
  · exact u302 (Nat.le_of_not_lt hle) fun _ _ => u295 trivial
@[local step]
theorem u330 (freq m total i) :
    slot.Z263_loop0 freq m total i ⦃ Y112P0! ⦄ := by
  rw [slot.Z263_loop0]
  apply Std.loop.spec_decr_nat (measure := fun x => 288 - x.2.val) (inv := fun _ => True)
  · rintro ⟨total', i'⟩ _
    simp only [slot.Z263_loop0.body, lift, bind_tc_ok]
    refine u296 (fun _ => ?_) (fun _ => u295 trivial)
    refine u296 (fun hi => ?_) (fun _ => u295 trivial)
    refine u308 hi fun i1 => ?_
    refine u300 288#usize (Nat.succ_le_of_lt hi) fun i2 hi2 => ?_
    exact u295 ⟨trivial, u315 hi hi2⟩
  · trivial
@[local step]
theorem u331 (freq m hl unseen ck out i lt) :
    slot.Z263_loop1 freq m hl unseen ck out i lt ⦃ Y112P0! ⦄ := by
  rw [slot.Z263_loop1]
  apply Std.loop.spec_decr_nat (measure := fun x => 288 - x.2.val) (inv := fun _ => True)
  · rintro ⟨out', i'⟩ _
    simp only [slot.Z263_loop1.body, EA.EA.u37, lift, bind_tc_ok]
    refine u296 (fun _ => ?_) (fun _ => u295 trivial)
    refine u296 (fun hi => ?_) (fun _ => u295 trivial)
    refine u308 hi fun i1 => ?_
    refine u308 hi fun i2 => ?_
    refine u298 (u328 _ _) fun e => ?_
    refine u298 (u329 _ _ _) fun i4 => ?_
    refine u309 hi fun a => ?_
    refine u300 288#usize (Nat.succ_le_of_lt hi) fun i5 hi5 => ?_
    exact u295 ⟨trivial, u315 hi hi5⟩
  · trivial
@[local step]
theorem u332 (freq m hl unseen ck out) :
    slot.Z263 freq m hl unseen ck out ⦃ Y112P0! ⦄ := by
  simp only [slot.Z263, lift, bind_tc_ok]
  refine u298 (u330 _ _ _ _) fun total => ?_
  refine u298 (u256 _) fun lt => ?_
  exact u331 _ _ _ _ _ _ _ _
@[local step]
theorem u333 (mx) :
    slot.Z267 mx ⦃ Y112P0! ⦄ := by
  rw [slot.Z267]
  exact u296 (fun h => u301 15#u32 (Nat.succ_le_of_lt h)) (fun _ => u295 trivial)
@[local step]
theorem u334 (tabs lcst i) :
    slot.Z256_loop0 tabs lcst i ⦃ Y112P0! ⦄ := by
  rw [slot.Z256_loop0]
  apply Std.loop.spec_decr_nat (measure := fun x => 256 - x.2.val) (inv := fun _ => True)
  · rintro ⟨tabs', i'⟩ _
    simp only [slot.Z256_loop0.body]
    refine u296 (fun hi => ?_) (fun _ => u295 trivial)
    refine u308 (Nat.lt_trans hi (by decide)) fun i1 => ?_
    refine u298 (u291 _ _) fun tabs1 => ?_
    refine u300 256#usize (Nat.succ_le_of_lt hi) fun i2 hi2 => ?_
    exact u295 ⟨trivial, u315 hi hi2⟩
  · trivial
@[local step]
theorem u335 (tabs lsym lcst l) :
    slot.Z256_loop1 tabs lsym lcst l ⦃ Y112P0! ⦄ := by
  rw [slot.Z256_loop1]
  apply Std.loop.spec_decr_nat (measure := fun x => 264 - x.2.val) (inv := fun _ => True)
  · rintro ⟨tabs', l'⟩ _
    simp only [slot.Z256_loop1.body, lift, bind_tc_ok]
    refine u296 (fun hl => ?_) (fun _ => u295 trivial)
    refine u303 u313 fun i hi => ?_
    refine u308 hi fun i1 => ?_
    refine u303 u313 fun c hc => ?_
    refine u298 (Q := fun _ => True) ?_ fun x => ?_
    · refine u296 (fun _ => u295 trivial) (fun _ => u296 (fun _ => u295 trivial) (fun _ => ?_))
      refine u300 288#usize (Nat.add_le_add_left (Nat.le_of_lt_succ hc) 257) fun i3 _ => ?_
      refine u303 u313 fun i4 hi4 => ?_
      refine u308 hi4 fun i5 => ?_
      exact u308 hc fun _ => u295 trivial
    refine u298 (u291 _ _) fun tabs1 => ?_
    refine u300 264#usize (Nat.succ_le_of_lt hl) fun l1 hl1 => ?_
    exact u295 ⟨trivial, u315 hl hl1⟩
  · trivial
@[local step]
theorem u336 (tabs dcst i) :
    slot.Z256_loop2 tabs dcst i ⦃ Y112P0! ⦄ := by
  rw [slot.Z256_loop2]
  apply Std.loop.spec_decr_nat (measure := fun x => 40 - x.2.val) (inv := fun _ => True)
  · rintro ⟨tabs', i'⟩ _
    simp only [slot.Z256_loop2.body, lift, bind_tc_ok]
    refine u296 (fun hi => ?_) (fun _ => u295 trivial)
    refine u298 (Q := fun _ => True) ?_ fun x => ?_
    · refine u296 (fun h30 => ?_) (fun _ => u295 trivial)
      refine u308 (Nat.lt_trans h30 (by decide)) fun i1 => ?_
      refine u303 u313 fun i2 hi2 => ?_
      exact u308 hi2 fun _ => u295 trivial
    refine u298 (u291 _ _) fun tabs1 => ?_
    refine u300 40#usize (Nat.succ_le_of_lt hi) fun i1 hi1 => ?_
    exact u295 ⟨trivial, u315 hi hi1⟩
  · trivial
@[local step]
theorem u337 (tabs lf df lsym ck) :
    slot.Z256 tabs lf df lsym ck ⦃ Y112P0! ⦄ := by
  simp only [slot.Z256]
  refine u298 (u327 _ _ _) fun ⟨mxl, ll1⟩ => ?_
  refine u298 (u327 _ _ _) fun ⟨mxd, dl1⟩ => ?_
  refine u298 (u333 _) fun i => ?_
  refine u298 (u332 _ _ _ _ _ _) fun lcst1 => ?_
  refine u298 (u333 _) fun i1 => ?_
  refine u298 (u332 _ _ _ _ _ _) fun dcst1 => ?_
  refine u298 (u334 _ _ _) fun tabs1 => ?_
  refine u298 (u335 _ _ _ _) fun tabs2 => ?_
  exact u336 _ _ _
@[local step]
theorem u338 (tabs bstart lf df lsym ck p t) :
    slot.Z231 tabs bstart lf df lsym ck p t ⦃ Y112P0! ⦄ := by
  simp only [slot.Z231, lift, bind_tc_ok]
  refine u296 (fun _ => u295 trivial) (fun _ => ?_)
  refine u309 (by decide) fun lf1 => ?_
  refine u298 (u337 _ _ _ _ _) fun tabs1 => ?_
  exact u298 (u291 _ _) fun _ => u295 trivial
@[local step]
theorem u339 (s plan lsym dtab tabs bstart ck lf df p t k) :
    slot.Z265_loop s plan lsym dtab tabs bstart ck lf df p t k ⦃ Y112P0! ⦄ := by
  rw [slot.Z265_loop]
  apply Std.loop.spec_decr_nat (measure := fun x => (Slice.len s).val - x.2.2.2.2.1.val) (inv := fun _ => True)
  · rintro ⟨tabs', bstart', lf', df', p', t', k'⟩ _
    simp only [slot.Z265_loop.body, lift, bind_tc_ok]
    refine u296 (fun hp => ?_) (fun _ => u295 trivial)
    refine u298 (u338 _ _ _ _ _ _ _ _) fun ⟨t1, tabs1, bstart1, lf1, df1⟩ => ?_
    refine u298 (EA.EA.u1 _ _) fun v => ?_
    refine u303 u313 fun i1 _ => ?_
    refine u297 (Q := fun r => (Slice.len s).val - r.2.2.2.2.val < (Slice.len s).val - p'.val) ?_
      fun ⟨tabs2, bstart2, lf2, df2, p1⟩ hq => u295 ⟨trivial, hq⟩
    refine u296 (fun h3 => ?_) (fun _ => ?_)
    · refine u302 (Nat.le_of_lt hp) fun i3 hi3 => ?_
      refine u297 (Q := fun r => (Slice.len s).val - r.2.2.val < (Slice.len s).val - p'.val) ?_
        fun ⟨a, a1, i4⟩ hq => u295 hq
      refine u296 (fun hle => ?_) (fun _ => ?_)
      · -- a match of `len` bytes: length and distance symbol counts
        refine u303 u313 fun i5 hi5 => ?_
        refine u308 hi5 fun i6 => ?_
        refine u303 u313 fun c hc => ?_
        refine u300 288#usize (Nat.add_le_add_left (Nat.le_of_lt_succ hc) 257) fun i8 _ => ?_
        refine u303 u313 fun i9 hi9 => ?_
        refine u308 hi9 fun i10 => ?_
        refine u303 u313 fun i12 hi12 => ?_
        refine u309 hi12 fun a2 => ?_
        refine u307 (by decide) (by decide) fun i13 => ?_
        refine u298 (u239 _ _) fun i15 => ?_
        refine u303 u313 fun dc hdc => ?_
        refine u308 (Nat.lt_trans hdc (by decide)) fun i16 => ?_
        refine u309 (Nat.lt_trans hdc (by decide)) fun a3 => ?_
        refine u300 (Slice.len s) (u317 hle hi3) fun p2 hp2 => ?_
        exact u295 (u316 hp (Nat.lt_of_lt_of_le (by decide) h3) hp2)
      · -- a literal (the planned match does not fit)
        refine u310 hp fun i5 => ?_
        refine u308 (u311 i5) fun i7 => ?_
        refine u309 (u311 i5) fun a2 => ?_
        refine u300 (Slice.len s) (Nat.succ_le_of_lt hp) fun p2 hp2 => ?_
        exact u295 (u315 hp hp2)
    · -- a literal
      refine u310 hp fun i2 => ?_
      refine u308 (u311 i2) fun i4 => ?_
      refine u309 (u311 i2) fun a => ?_
      refine u300 (Slice.len s) (Nat.succ_le_of_lt hp) fun p2 hp2 => ?_
      exact u295 (u315 hp hp2)
  · trivial
@[local step]
theorem u340 (s plan lsym dtab tabs bstart ck) :
    slot.Z265 s plan lsym dtab tabs bstart ck ⦃ Y112P0! ⦄ := by
  simp only [slot.Z265]
  refine u298 (u291 _ _) fun bstart1 => ?_
  refine u298 (u339 _ _ _ _ _ _ _ _ _ _ _ _) fun ⟨tabs1, bstart2, lf1, df1⟩ => ?_
  refine u309 (by decide) fun lf2 => ?_
  exact u298 (u337 _ _ _ _ _) fun _ => u295 trivial
@[local step]
theorem u341 (tabs tb litc i) :
    slot.Z247_loop0 tabs tb litc i ⦃ Y112P0! ⦄ := by
  rw [slot.Z247_loop0]
  apply Std.loop.spec_decr_nat (measure := fun x => 256 - x.2.val) (inv := fun _ => True)
  · rintro ⟨litc', i'⟩ _
    simp only [slot.Z247_loop0.body, lift, bind_tc_ok]
    refine u296 (fun hi => ?_) (fun _ => u295 trivial)
    refine u298 (EA.EA.u1 _ _) fun i2 => ?_
    refine u309 hi fun a => ?_
    refine u300 256#usize (Nat.succ_le_of_lt hi) fun i3 hi3 => ?_
    exact u295 ⟨trivial, u315 hi hi3⟩
  · trivial
@[local step]
theorem u342 (tabs tb lc l) :
    slot.Z247_loop1 tabs tb lc l ⦃ Y112P0! ⦄ := by
  rw [slot.Z247_loop1]
  apply Std.loop.spec_decr_nat (measure := fun x => 512 - x.2.val) (inv := fun _ => True)
  · rintro ⟨lc', l'⟩ _
    simp only [slot.Z247_loop1.body, lift, bind_tc_ok]
    refine u296 (fun hl => ?_) (fun _ => u295 trivial)
    refine u298 (Q := fun _ => True) (u296 (fun _ => EA.EA.u1 _ _) (fun _ => u295 trivial)) fun i => ?_
    refine u309 hl fun a => ?_
    refine u300 512#usize (Nat.succ_le_of_lt hl) fun l1 hl1 => ?_
    exact u295 ⟨trivial, u315 hl hl1⟩
  · trivial
@[local step]
theorem u343 (tabs tb dcc i) :
    slot.Z247_loop2 tabs tb dcc i ⦃ Y112P0! ⦄ := by
  rw [slot.Z247_loop2]
  apply Std.loop.spec_decr_nat (measure := fun x => 32 - x.2.val) (inv := fun _ => True)
  · rintro ⟨dcc', i'⟩ _
    simp only [slot.Z247_loop2.body, lift, bind_tc_ok]
    refine u296 (fun hi => ?_) (fun _ => u295 trivial)
    refine u298 (EA.EA.u1 _ _) fun i3 => ?_
    refine u309 hi fun a => ?_
    refine u300 32#usize (Nat.succ_le_of_lt hi) fun i4 hi4 => ?_
    exact u295 ⟨trivial, u315 hi hi4⟩
  · trivial
@[local step]
theorem u344 (tabs tb litc lc dcc) :
    slot.Z247 tabs tb litc lc dcc ⦃ Y112P0! ⦄ := by
  rw [slot.Z247]
  refine u298 (u341 _ _ _ _) fun litc1 => ?_
  refine u298 (u342 _ _ _ _) fun lc1 => ?_
  exact u298 (u343 _ _ _ _) fun _ => u295 trivial
theorem u345 {α:Type} {c:Prop} {inst:Decidable c} {a b:α} :
    WP.spec (@ite _ c inst (ok a) (ok b)) (fun _ => True) :=
  u296 (fun _ => u295 trivial) (fun _ => u295 trivial)
theorem u346 {ty:UScalarTy} {α:Type} {a b:UScalar ty} {inst:Decidable (a < b)} {X Y:Result α}
    {P:α  →  Prop} (hX:a.val < b.val  →  WP.spec X P) (hY:b.val  ≤  a.val  →  WP.spec Y P) :
    WP.spec (@ite _ (a < b) inst X Y) P :=
  u296 hX (fun h => hY (Nat.le_of_not_lt h))
theorem u347 {ty:UScalarTy} {α:Type} {a b:UScalar ty} {inst:Decidable (a  ≤  b)} {X Y:Result α}
    {P:α  →  Prop} (hX:a.val  ≤  b.val  →  WP.spec X P) (hY:b.val < a.val  →  WP.spec Y P) :
    WP.spec (@ite _ (a  ≤  b) inst X Y) P :=
  u296 hX (fun h => hY (Nat.lt_of_not_le h))
theorem u348 {α β:Type} {x:α} {k:α  →  Result β} {P:β  →  Prop}
    (h:WP.spec (k x) P):WP.spec (Bind.bind (lift x) k) P := h
theorem u349 (x:Usize):x.val  ≤  Usize.max := UScalar.max_USize_eq ▸ ScalarTac.UScalar.bounds x
theorem u350:4294967295  ≤  Usize.max := by
  rcases Usize.bounds_eq with h | h
  · rw [h, U32.max_eq]
  · rw [h, U64.max_eq];decide
theorem u351 {β:Type} {x y:Usize} {k:Usize  →  Result β} {P:β  →  Prop}
    (h:y.val  ≤  x.val) (hk:∀ z:Usize, z.val + y.val = x.val  →  WP.spec (k z) P) :
    WP.spec (Bind.bind (HSub.hSub x y:Result Usize) k) P :=
  WP.spec_bind (Usize.sub_spec h) (fun z hz => hk z ((congrArg (· + y.val) hz.1).trans (Nat.sub_add_cancel h)))
theorem u352 {β:Type} {x y:Usize} {k:Usize  →  Result β} {P:β  →  Prop}
    (h:y.val < x.val) (hk:∀ z:Usize, z.val + 1 = x.val  →  WP.spec (k z) P) :
    WP.spec (Bind.bind (HSub.hSub x 1#usize:Result Usize) k) P :=
  u351 (Nat.succ_le_of_lt (Nat.lt_of_le_of_lt (Nat.zero_le _) h)) hk
theorem u353 {β:Type} {x y:Usize} {k:Usize  →  Result β} {P:β  →  Prop}
    (h:x.val < y.val) (hk:∀ z:Usize, z.val = x.val + 1  →  WP.spec (k z) P) :
    WP.spec (Bind.bind (HAdd.hAdd x 1#usize:Result Usize) k) P :=
  WP.spec_bind (Usize.add_spec (Nat.le_trans (Nat.succ_le_of_lt h) (u349 y))) hk
theorem u354 {β:Type} {x:Usize} {k:Usize  →  Result β} {P:β  →  Prop} (c:Nat)
    (h:x.val  ≤  c) (hc:c < 4294967295) (hk:∀ z:Usize, z.val = x.val + 1  →  WP.spec (k z) P) :
    WP.spec (Bind.bind (HAdd.hAdd x 1#usize:Result Usize) k) P :=
  WP.spec_bind (Usize.add_spec (Nat.le_trans (Nat.succ_le_of_lt (Nat.lt_of_le_of_lt h hc)) u350)) hk
theorem u355 {β:Type} {x y w:Usize} {k:Usize  →  Result β} {P:β  →  Prop}
    (h:x.val + y.val  ≤  w.val) (hk:∀ z:Usize, z.val = x.val + y.val  →  WP.spec (k z) P) :
    WP.spec (Bind.bind (HAdd.hAdd x y:Result Usize) k) P :=
  WP.spec_bind (Usize.add_spec (Nat.le_trans h (u349 w))) hk
theorem u356 {β:Type} {x:Usize} {k:Usize  →  Result β} {P:β  →  Prop}
    (hk:∀ z:Usize, z.val < (1024#usize).val  →  WP.spec (k z) P) :
    WP.spec (Bind.bind (HMod.hMod x slot.Z139:Result Usize) k) P := by
  rw [slot.Z139];exact u303 (by decide) hk
theorem u357 {β:Type} {x y:Usize} {k:Usize  →  Result β} {P:β  →  Prop}
    (h:y.val ≠ 0) (hk:∀ z:Usize, WP.spec (k z) P) :
    WP.spec (Bind.bind (HDiv.hDiv x y:Result Usize) k) P :=
  WP.spec_bind (Usize.div_spec x h) (fun z _ => hk z)
theorem u358 (x:U64):WP.spec (HShiftRight.hShiftRight x 32#i32:Result U64) (fun _ => True) :=
  WP.spec_mono (U64.ShiftRight_IScalar_spec x 32#i32 (by decide) (by decide)) (fun _ _ => trivial)
theorem u359 (x:U64):WP.spec (HShiftLeft.hShiftLeft x 32#i32:Result U64) (fun _ => True) :=
  WP.spec_mono (U64.ShiftLeft_IScalar_spec x 32#i32 (by decide) (by decide)) (fun _ _ => trivial)
theorem u360 (x:U64):WP.spec (HShiftRight.hShiftRight x 9#i32:Result U64) (fun _ => True) :=
  WP.spec_mono (U64.ShiftRight_IScalar_spec x 9#i32 (by decide) (by decide)) (fun _ _ => trivial)
theorem u361 (x:U64):WP.spec (HShiftLeft.hShiftLeft x 9#i32:Result U64) (fun _ => True) :=
  WP.spec_mono (U64.ShiftLeft_IScalar_spec x 9#i32 (by decide) (by decide)) (fun _ _ => trivial)
theorem u362 (x:U32):WP.spec (HShiftRight.hShiftRight x 9#i32:Result U32) (fun _ => True) :=
  WP.spec_mono (U32.ShiftRight_IScalar_spec x 9#i32 (by decide) (by decide)) (fun _ _ => trivial)
theorem u363 (x:U32):WP.spec (HShiftRight.hShiftRight x 24#i32:Result U32) (fun _ => True) :=
  WP.spec_mono (U32.ShiftRight_IScalar_spec x 24#i32 (by decide) (by decide)) (fun _ _ => trivial)
theorem u364 {α β:Type} {n:Usize} {a:Std.Array α n} {i:Usize} {k:α  →  Result β} {P:β  →  Prop}
    (h:i.val < n.val) (hk:∀ x, WP.spec (k x) P):WP.spec (Bind.bind (Array.index_usize a i) k) P :=
  WP.spec_bind (Array.index_usize_spec a i (Nat.lt_of_lt_of_eq h a.property.symm)) (fun x _ => hk x)
theorem u365 {α β:Type} {n:Usize} {a:Std.Array α n} {i:Usize} {v:α} {k:Std.Array α n  →  Result β}
    {P:β  →  Prop} (h:i.val < n.val) (hk:∀ x, WP.spec (k x) P) :
    WP.spec (Bind.bind (Array.update a i v) k) P :=
  WP.spec_bind (Array.update_spec a i v (Nat.lt_of_lt_of_eq h a.property.symm)) (fun x _ => hk x)
theorem u366 {α β:Type} {s:Slice α} {i:Usize} {k:α  →  Result β} {P:β  →  Prop}
    (h:i.val < (Slice.len s).val) (hk:∀ x, WP.spec (k x) P) :
    WP.spec (Bind.bind (Slice.index_usize s i) k) P :=
  WP.spec_bind (Slice.index_usize_spec s i h) (fun x _ => hk x)
theorem u367 {α β:Type} {s:Slice α} {i:Usize} {v:α} {k:Slice α  →  Result β} {P:β  →  Prop}
    (h:i.val < (Slice.len s).val) (hk:∀ x:Slice α, x.length = s.length  →  WP.spec (k x) P) :
    WP.spec (Bind.bind (Slice.update s i v) k) P :=
  WP.spec_bind (Slice.update_spec s i v h) (fun x hx => hk x (hx ▸ Slice.set_length s i v))
theorem u368 {α β:Type} {v:alloc.vec.Vec α} {x:α} {n:Usize} {k:alloc.vec.Vec α  →  Result β}
    {P:β  →  Prop} (h:(alloc.vec.Vec.len v).val < n.val) (hk:∀ w, WP.spec (k w) P) :
    WP.spec (Bind.bind (alloc.vec.Vec.push v x) k) P :=
  WP.spec_bind (alloc.vec.Vec.push_spec v x (Nat.lt_of_lt_of_le h (u349 n))) (fun w _ => hk w)
theorem u369 {β:Type} {i:U32} {k:Usize  →  Result β} {P:β  →  Prop}
    (h:i.val < (32768#u32).val) (hk:∀ z:Usize, z.val  ≤  32768  →  WP.spec (k z) P) :
    WP.spec (Bind.bind (HAdd.hAdd (UScalar.cast .Usize i) 1#usize:Result Usize) k) P := by
  have hi:(UScalar.cast .Usize i).val  ≤  32767 := by
    rw [U32.cast_Usize_val_eq];exact Nat.le_of_lt_succ h
  exact u354 32767 hi (by decide) (fun z hz => hk z (Nat.le_trans (Nat.le_of_eq hz) (Nat.succ_le_succ hi)))
theorem u370 {β:Type} {z:Usize} {k:U64  →  Result β} {P:β  →  Prop}
    (h:z.val  ≤  32768) (hk:∀ c:U64, WP.spec (k c) P) :
    WP.spec (Bind.bind (HMul.hMul (UScalar.cast .U64 z) 512#u64:Result U64) k) P := by
  have h1:(UScalar.cast .U64 z).val  ≤  32768 := by
    rw [UScalar.cast_val_eq];exact Nat.le_trans (Nat.mod_le _ _) h
  have h2:(UScalar.cast .U64 z).val * (512#u64).val  ≤  U64.max := by
    rw [U64.max_eq];exact Nat.le_trans (Nat.mul_le_mul_right _ h1) (by decide)
  exact WP.spec_bind (U64.mul_spec h2) (fun c _ => hk c)
theorem u371 (b:U8):(UScalar.cast .Usize b).val < (256#usize).val := by
  rw [U8.cast_Usize_val_eq];exact b.hBounds
theorem u372 {x:Usize} (h:¬ x = 0#usize):(0#usize).val < x.val :=
  Nat.pos_of_ne_zero (fun h0 => h (UScalar.eq_imp x 0#usize h0))
theorem u373:slot.Z119.val ≠ 0 := by rw [slot.Z119];decide
theorem u374 {a b c:Nat} (h:a + 1 = b) (hb:b  ≤  c):a < c := Nat.lt_of_lt_of_le (u314 h) hb
theorem u375 {a k i e:Nat} (h1:a + k = i) (h2:i + 2 = e):a < e := by omega
@[local step]
theorem u376 (x stop q) :
    slot.Z236 x stop q ⦃ Y112P5! ⦄ := by
  rw [slot.Z236];exact u296 (fun _ => u345) (fun _ => u295 trivial)
@[local step]
theorem u377 (s litc ring out lo dlit q nxt mid) :
    slot.Z242_loop0 s litc ring out lo dlit q nxt mid ⦃ fun r => r.2.1.length = out.length ⦄ := by
  rw [slot.Z242_loop0]
  apply Std.loop.spec_decr_nat (measure := fun x => x.2.2.1.val) (inv := fun x => x.2.1.length = out.length)
  · rintro ⟨ring', out', q', nxt'⟩ hinv
    unfold slot.Z242_loop0.body
    refine u346 (fun h1 => ?_) (fun _ => u295 hinv)
    refine u347 (fun h2 => ?_) (fun _ => u295 hinv)
    refine u347 (fun h3 => ?_) (fun _ => u295 hinv)
    refine u352 h1 fun q1 hq1 => ?_
    refine u298 (u358 _) fun i2 => ?_
    refine u366 (u374 hq1 h2) fun i3 => ?_
    refine u348 <| u364 (u371 i3) fun i5 => ?_
    refine u348 <| u348 <| u298 (u359 _) fun i8 => ?_
    refine u348 <| u298 (Q := fun _ => True) ?_ fun v1 => ?_
    · exact u296 (fun _ => u356 fun i9 hi9 => u364 hi9 fun o => u345) (fun _ => u295 trivial)
    refine u356 fun i9 hi9 => ?_
    refine u365 hi9 fun a => ?_
    refine u348 <| u367 (u374 hq1 h3) fun s1 hs1 => ?_
    exact u295 ⟨hs1.trans hinv, u314 hq1⟩
  · rfl
@[local step]
theorem u378 (s litc lc ring out «end» chd dlit q nxt kc s1) :
    slot.Z242_loop1 s litc lc ring out «end» chd dlit q nxt kc s1 ⦃ fun r => r.2.1.length = out.length ⦄ := by
  rw [slot.Z242_loop1]
  apply Std.loop.spec_decr_nat (measure := fun x => x.2.2.1.val) (inv := fun x => x.2.1.length = out.length)
  · rintro ⟨ring', out', q', nxt'⟩ hinv
    unfold slot.Z242_loop1.body
    refine u346 (fun h1 => ?_) (fun _ => u295 hinv)
    refine u347 (fun h2 => ?_) (fun _ => u295 hinv)
    refine u347 (fun h3 => ?_) (fun _ => u295 hinv)
    refine u347 (fun h4 => ?_) (fun _ => u295 hinv)
    refine u352 h1 fun q1 hq1 => ?_
    refine u351 (Nat.le_of_lt (u374 hq1 h4)) fun rem _ => ?_
    refine u298 (u358 _) fun i2 => ?_
    refine u366 (u374 hq1 h2) fun i3 => ?_
    refine u348 <| u364 (u371 i3) fun i5 => ?_
    refine u348 <| u348 <| u298 (u359 _) fun i8 => ?_
    refine u348 <| u303 (by decide) fun i9 hi9 => ?_
    refine u364 hi9 fun i10 => ?_
    refine u348 <| u348 <| u298 (u359 _) fun i13 => ?_
    refine u348 <| u348 <| u348 <| u298 u345 fun v => ?_
    refine u356 fun i16 hi16 => ?_
    refine u364 hi16 fun o => ?_
    refine u298 u345 fun v1 => ?_
    refine u365 hi16 fun a => ?_
    refine u348 <| u367 (u374 hq1 h3) fun s2 hs2 => ?_
    exact u295 ⟨hs2.trans hinv, u314 hq1⟩
  · rfl
@[local step]
theorem u379 (s litc lc ring out stop «end» chd dlit q nxt kc) :
    slot.Z242_loop2 s litc lc ring out stop «end» chd dlit q nxt kc ⦃ fun r => r.2.2.length = out.length ⦄ := by
  rw [slot.Z242_loop2]
  apply Std.loop.spec_decr_nat (measure := fun x => x.2.2.1.val) (inv := fun x => x.2.1.length = out.length)
  · rintro ⟨ring', out', q', nxt'⟩ hinv
    unfold slot.Z242_loop2.body
    refine u346 (fun h1 => ?_) (fun _ => u295 hinv)
    refine u347 (fun h2 => ?_) (fun _ => u295 hinv)
    refine u347 (fun h3 => ?_) (fun _ => u295 hinv)
    refine u347 (fun h4 => ?_) (fun _ => u295 hinv)
    refine u352 h1 fun q1 hq1 => ?_
    refine u351 (Nat.le_of_lt (u374 hq1 h4)) fun rem _ => ?_
    refine u298 (u358 _) fun i2 => ?_
    refine u366 (u374 hq1 h2) fun i3 => ?_
    refine u348 <| u364 (u371 i3) fun i5 => ?_
    refine u348 <| u348 <| u298 (u359 _) fun i8 => ?_
    refine u348 <| u303 (by decide) fun i9 hi9 => ?_
    refine u364 hi9 fun i10 => ?_
    refine u348 <| u348 <| u298 (u359 _) fun i13 => ?_
    refine u348 <| u348 <| u348 <| u298 u345 fun v => ?_
    refine u356 fun i16 hi16 => ?_
    refine u365 hi16 fun a => ?_
    refine u348 <| u367 (u374 hq1 h3) fun s2 hs2 => ?_
    exact u295 ⟨hs2.trans hinv, u314 hq1⟩
  · rfl
@[local step]
theorem u380 (s litc lc ring out hi stop «end» kcd chd lo nxt0 dlit) :
    slot.Z242 s litc lc ring out hi stop «end» kcd chd lo nxt0 dlit ⦃ fun r => r.2.2.length = out.length ⦄ := by
  rw [slot.Z242]
  refine u348 <| u298 (u376 _ _ _) fun mid => ?_
  refine u297 (u377 s litc ring out lo dlit hi nxt0 mid) ?_
  rintro ⟨ring1, out1, q, nxt⟩ h0
  refine u298 (u293 _ _) fun i1 => ?_
  refine u298 (u358 _) fun i2 => ?_
  refine u348 <| u298 (u376 _ _ _) fun s1 => ?_
  refine u297 (u378 s litc lc ring1 out1 «end» chd dlit q nxt _ s1) ?_
  rintro ⟨ring2, out2, q1, nxt1⟩ h1
  exact WP.spec_mono (u379 s litc lc ring2 out2 stop «end» chd dlit q1 nxt1 _)
    (fun r h2 => h2.trans (h1.trans h0))
@[local step]
theorem u381 (lc ring p e bv l) :
    slot.Z229_loop lc ring p e bv l ⦃ Y112P5! ⦄ := by
  rw [slot.Z229_loop]
  apply Std.loop.spec_decr_nat (measure := fun x => e.val - x.2.val) (inv := fun _ => True)
  · rintro ⟨bv', l'⟩ _
    unfold slot.Z229_loop.body
    refine u346 (fun h1 => ?_) (fun _ => u295 trivial)
    refine u348 <| u356 fun i1 hi1 => ?_
    refine u364 hi1 fun i2 => ?_
    refine u298 (u358 _) fun i3 => ?_
    refine u303 (by decide) fun i4 hi4 => ?_
    refine u364 hi4 fun i5 => ?_
    refine u348 <| u348 <| u298 (u361 _) fun i8 => ?_
    refine u348 <| u348 <| u298 u345 fun bv1 => ?_
    refine u353 h1 fun l1 hl1 => ?_
    exact u295 ⟨trivial, u315 h1 hl1⟩
  · trivial
@[local step]
theorem u382 (lc ring p lo e) :
    slot.Z229 lc ring p lo e ⦃ Y112P5! ⦄ :=
  u381 lc ring p e _ lo
@[local step]
theorem u383 (lc ring p el t f chd x) :
    slot.Z254_loop lc ring p el t f chd x ⦃ Y112P5! ⦄ := by
  rw [slot.Z254_loop]
  apply Std.loop.spec_decr_nat (measure := fun x => 259 - x.2.val) (inv := fun _ => True)
  · rintro ⟨ring', x'⟩ _
    unfold slot.Z254_loop.body
    refine u347 (fun h1 => ?_) (fun _ => u295 trivial)
    refine u347 (fun h2 => ?_) (fun _ => u295 trivial)
    refine u347 (fun h3 => ?_) (fun _ => u295 trivial)
    refine u351 h3 fun i hi => ?_
    refine u347 (fun h4 => ?_) (fun _ => u295 trivial)
    have hx:el.val + x'.val  ≤  (258#usize).val :=
      Nat.add_comm x'.val el.val ▸ (Nat.add_le_add_right h4 el.val).trans (Nat.le_of_eq hi)
    have hx':x'.val  ≤  258 := Nat.le_trans (Nat.le_add_left _ _) hx
    refine u355 hx fun i1 _ => ?_
    refine u303 (by decide) fun i2 hi2 => ?_
    refine u364 hi2 fun i3 => ?_
    refine u348 <| u348 <| u298 (u359 _) fun i6 => ?_
    refine u348 <| u348 <| u348 <| u351 h2 fun i9 _ => ?_
    refine u356 fun i10 hi10 => ?_
    refine u364 hi10 fun o => ?_
    refine u298 u345 fun v1 => ?_
    refine u356 fun i11 hi11 => ?_
    refine u365 hi11 fun a => ?_
    refine u354 258 hx' (by decide) fun x1 hx1 => ?_
    exact u295 ⟨trivial, u315 (Nat.lt_succ_of_le hx') hx1⟩
  · trivial
@[local step]
theorem u384 (lc ring p el t f chd) :
    slot.Z254 lc ring p el t f chd ⦃ Y112P5! ⦄ :=
  u383 lc ring p el t f chd _
@[local step]
theorem u385 (ring top z) :
    slot.Z244_loop ring top z ⦃ Y112P5! ⦄ := by
  rw [slot.Z244_loop]
  apply Std.loop.spec_decr_nat (measure := fun x => top.val - x.2.val) (inv := fun _ => True)
  · rintro ⟨ring', z'⟩ _
    unfold slot.Z244_loop.body
    refine u346 (fun h1 => ?_) (fun _ => u295 trivial)
    refine u356 fun i hi => ?_
    refine u365 hi fun a => ?_
    refine u353 h1 fun z1 hz1 => ?_
    exact u295 ⟨trivial, u315 h1 hz1⟩
  · trivial
@[local step]
theorem u386 (ring st p z0) :
    slot.Z244 ring st p z0 ⦃ Y112P5! ⦄ := by
  rw [slot.Z244]
  refine u364 (by decide) fun i => ?_
  refine u348 <| u296 (fun _ => ?_) (fun _ => u295 trivial)
  refine u298 (u294 _ _) fun top => ?_
  refine u298 (u385 _ _ _) fun ring1 => ?_
  exact u348 <| u365 (by decide) fun st1 => u295 trivial
@[local step]
theorem u387 (lc ring p len bl t dcst chd2 pbest st) :
    slot.Z226 lc ring p len bl t dcst chd2 pbest st ⦃ Y112P5! ⦄ := by
  rw [slot.Z226]
  refine u296 (fun _ => u295 trivial) (fun _ => ?_)
  refine u297 (u294 t p) fun tt htt => ?_
  refine u351 htt.2 fun i _ => ?_
  refine u298 (u386 ring st p i) ?_
  rintro ⟨ring1, st1⟩
  refine u348 <| u298 (u293 _ _) fun i2 => ?_
  refine u298 (u358 _) fun i3 => ?_
  refine u348 <| u298 (u384 _ _ _ _ _ _ _) fun ring2 => ?_
  refine u296 (fun _ => ?_) (fun _ => u295 trivial)
  refine u296 (fun _ => ?_) (fun _ => u295 trivial)
  refine u296 (fun _ => ?_) (fun _ => u295 trivial)
  refine u348 <| u298 (u293 _ _) fun i5 => ?_
  refine u298 (u358 _) fun i6 => ?_
  exact u348 <| u298 (u384 _ _ _ _ _ _ _) fun ring3 => u295 trivial
@[local step]
theorem u388 (lc dcc dtab ring r p prev room pbest st) :
    slot.Z233 lc dcc dtab ring r p prev room pbest st ⦃ Y112P5! ⦄ := by
  rw [slot.Z233]
  refine u303 (by decide) fun i _ => ?_
  refine u348 <| u347 (fun _ => u295 trivial) (fun hA => ?_)
  refine u346 (fun _ => u295 trivial) (fun hB => ?_)
  refine u296 (fun _ => u295 trivial) (fun _ => ?_)
  refine u298 (u362 _) fun i1 => ?_
  refine u303 (by decide) fun i2 hi2 => ?_
  refine u348 <| u298 (u363 _) fun i3 => ?_
  refine u348 <| u369 hi2 fun i4 hi4 => ?_
  refine u298 (u239 _ _) fun i5 => ?_
  refine u303 (by decide) fun i6 hi6 => ?_
  refine u364 hi6 fun i7 => ?_
  refine u348 <| u348 <| u370 hi4 fun chd2 => ?_
  refine u353 hA fun i9 _ => ?_
  refine u354 258 hB (by decide) fun i10 _ => ?_
  refine u298 (u382 _ _ _ _ _) fun bb => ?_
  refine u303 (by decide) fun i11 _ => ?_
  refine u348 <| u298 (u360 _) fun i12 => ?_
  refine u348 <| u298 (u359 _) fun i14 => ?_
  refine u348 <| u348 <| u348 <| u298 (u387 _ _ _ _ _ _ _ _ _ _) ?_
  rintro ⟨ring1, st1⟩
  refine u364 (by decide) fun s0 => ?_
  refine u298 u345 fun cand1 => ?_
  exact u365 (by decide) fun st2 => u295 trivial
@[local step]
theorem u389 (tabs bstart litc lc dcc bs pos) :
    slot.Z230 tabs bstart litc lc dcc bs pos ⦃ Y112P5! ⦄ := by
  rw [slot.Z230]
  refine u364 (by decide) fun i => ?_
  refine u296 (fun _ => ?_) (fun _ => u295 trivial)
  refine u364 (by decide) fun i1 => ?_
  refine u346 (fun h => ?_) (fun _ => u295 trivial)
  refine u352 h fun b _ => ?_
  refine u348 <| u298 (u344 _ _ _ _ _) ?_
  rintro ⟨litc1, lc1, dcc1⟩
  refine u365 (by decide) fun bs1 => ?_
  refine u298 (EA.EA.u1 _ _) fun i3 => ?_
  exact u348 <| u365 (by decide) fun bs2 => u295 trivial
@[local step]
theorem u390 (rs e k) :
    slot.Z266 rs e k ⦃ Y112P5! ⦄ := by
  rw [slot.Z266]
  exact u296 (fun _ => u348 (EA.EA.u1 _ _)) (fun _ => u295 trivial)
@[local step]
theorem u391 (p cl room) :
    slot.Z239 p cl room ⦃ Y112P5! ⦄ := by
  rw [slot.Z239];exact u345
@[local step]
theorem u392 (bfirst p1 q) :
    slot.Z262 bfirst p1 q ⦃ Y112P5! ⦄ := by
  rw [slot.Z262];exact u296 (fun _ => u345) (fun _ => u295 trivial)
@[local step]
theorem u393 (ring p lo best) :
    slot.Z250 ring p lo best ⦃ Y112P5! ⦄ := by
  rw [slot.Z250]
  exact u296 (fun _ => u356 fun i hi => u364 hi fun o => u345) (fun _ => u295 trivial)
@[local step]
theorem u394 (s tabs bstart out ring litc lc dcc dlit bs dslot chd «end» lo p1 q nxt fuel) :
    slot.Z237_loop0_loop0 s tabs bstart out ring litc lc dcc dlit bs dslot chd «end» lo p1 q nxt fuel
      ⦃ fun r => r.1.length = out.length ⦄ := by
  rw [slot.Z237_loop0_loop0]
  apply Std.loop.spec_decr_nat (measure := fun x => x.2.2.2.2.2.2.2.2.val) (inv := fun x => x.1.length = out.length)
  · rintro ⟨out', ring', litc', lc', dcc', bs', q', nxt', fuel'⟩ hinv
    unfold slot.Z237_loop0_loop0.body
    refine u346 (fun h1 => ?_) (fun _ => u295 hinv)
    refine u346 (fun h2 => ?_) (fun _ => u295 hinv)
    refine u352 h2 fun fuel1 hf => ?_
    refine u352 h1 fun i _ => ?_
    refine u298 (u389 _ _ _ _ _ _ _) ?_
    rintro ⟨litc1, lc1, dcc1, bs1⟩
    refine u364 (by decide) fun i1 => ?_
    refine u298 (u392 _ _ _) fun stop => ?_
    refine u303 (by decide) fun i2 hi2 => ?_
    refine u364 hi2 fun i3 => ?_
    refine u348 <| u297 (u380 s litc1 lc1 ring' out' q' stop «end» _ chd lo nxt' dlit) ?_
    rintro ⟨nxt1, ring1, out1⟩ hg
    exact u295 ⟨hg.trans hinv, u314 hf⟩
  · rfl
@[local step]
theorem u395 (rs dtab ring lc dcc pbest st p e2 room prev j) :
    slot.Z237_loop0_loop1 rs dtab ring lc dcc pbest st p e2 room prev j ⦃ Y112P5! ⦄ := by
  rw [slot.Z237_loop0_loop1]
  apply Std.loop.spec_decr_nat (measure := fun x => e2.val - x.2.2.2.val) (inv := fun _ => True)
  · rintro ⟨ring', st', prev', j'⟩ _
    unfold slot.Z237_loop0_loop1.body
    refine u346 (fun h1 => ?_) (fun _ => u295 trivial)
    refine u298 (EA.EA.u1 _ _) fun i => ?_
    refine u298 (u388 _ _ _ _ _ _ _ _ _ _) ?_
    rintro ⟨prev1, ring1, st1⟩
    refine u353 h1 fun j1 hj1 => ?_
    exact u295 ⟨trivial, u315 h1 hj1⟩
  · trivial
@[local step]
theorem u396 (s rs tabs bstart dtab out n ring litc lc dcc dlit pbest st bs e hi) :
    slot.Z237_loop0 s rs tabs bstart dtab out n ring litc lc dcc dlit pbest st bs e hi
      ⦃ fun r => r.length = out.length ⦄ := by
  rw [slot.Z237_loop0]
  apply Std.loop.spec_decr_nat (measure := fun x => x.2.2.2.2.2.2.2.1.val) (inv := fun x => x.1.length = out.length)
  · rintro ⟨out', ring', litc', lc', dcc', st', bs', e', hi'⟩ hinv
    unfold slot.Z237_loop0.body
    refine u347 (fun h1 => ?_) (fun _ => u295 hinv)
    have he0:(0#usize).val < e'.val := Nat.lt_of_lt_of_le (by decide) h1
    refine u352 he0 fun i _ => ?_
    refine u298 (EA.EA.u1 _ _) fun i1 => ?_
    refine u348 <| u351 h1 fun i2 hi2 => ?_
    refine u298 (EA.EA.u1 _ _) fun i3 => ?_
    refine u348 <| u346 (fun _ => u295 ⟨hinv, he0⟩) (fun hk => ?_)
    refine u347 (fun _ => u295 ⟨hinv, he0⟩) (fun hp => ?_)
    refine u351 hk fun a ha => ?_
    refine u298 (u390 _ _ _) fun top => ?_
    refine u303 (by decide) fun i4 _ => ?_
    refine u348 <| u298 (u362 _) fun i5 => ?_
    refine u303 (by decide) fun i6 hi6 => ?_
    refine u348 <| u369 hi6 fun i7 hi7 => ?_
    refine u298 (u239 _ _) fun dslot => ?_
    refine u348 <| u370 hi7 fun chd => ?_
    refine u348 <| u298 (u391 _ _ _) fun «end» => ?_
    refine u364 (by decide) fun i9 => ?_
    refine u348 <| u353 hp fun p1 _ => ?_
    refine u298 (u293 _ _) fun nxt => ?_
    refine u348 <| u297 (u394 s tabs bstart out' ring' litc' lc' dcc' dlit bs' dslot chd «end»
      _ p1 hi' nxt _) ?_
    rintro ⟨out1, ring1, litc1, lc1, dcc1, bs1, nxt1⟩ ho1
    refine u298 (u389 _ _ _ _ _ _ _) ?_
    rintro ⟨litc2, lc2, dcc2, bs2⟩
    refine u298 (u358 _) fun i11 => ?_
    refine u298 (u292 _ _) fun i12 => ?_
    refine u303 (by decide) fun i13 hi13 => ?_
    refine u364 hi13 fun i14 => ?_
    refine u348 <| u348 <| u298 (u359 _) fun i17 => ?_
    refine u348 <| u365 (by decide) fun a1 => ?_
    refine u298 (u395 _ _ _ _ _ _ _ _ _ _ _ _) ?_
    rintro ⟨ring2, st1⟩
    refine u364 (by decide) fun i19 => ?_
    refine u298 (u393 _ _ _ _) fun best => ?_
    refine u356 fun i20 hi20 => ?_
    refine u365 hi20 fun a2 => ?_
    refine u348 <| u297 (u204 out1 _ _) fun out2 ho2 => ?_
    exact u295 ⟨ho2.trans (ho1.trans hinv), u375 ha hi2⟩
  · rfl
@[local step]
theorem u397 (s rs tabs bstart dtab out pmode) :
    slot.Z237 s rs tabs bstart dtab out pmode ⦃ fun r => r.length = out.length ⦄ := by
  rw [slot.Z237]
  refine u296 (fun _ => u295 rfl) (fun _ => ?_)
  refine u296 (fun _ => u295 rfl) (fun h0 => ?_)
  refine u357 u373 fun i3 => ?_
  refine u296 (fun _ => u295 rfl) (fun _ => ?_)
  refine u356 fun i5 hi5 => ?_
  refine u365 hi5 fun a => ?_
  refine u298 u345 fun dlit => ?_
  refine u303 (by decide) fun pbest _ => ?_
  refine u348 <| u352 (u372 h0) fun b0 _ => ?_
  refine u298 (EA.EA.u1 _ _) fun i8 => ?_
  refine u348 <| u348 <| u298 (u344 _ _ _ _ _) ?_
  rintro ⟨litc1, lc1, dcc1⟩
  exact u396 _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
@[local step]
theorem u398 (out n plan p) :
    slot.Z240_loop out n plan p ⦃ Y112P5! ⦄ := by
  rw [slot.Z240_loop]
  apply Std.loop.spec_decr_nat (measure := fun x => n.val - x.2.val) (inv := fun _ => True)
  · rintro ⟨plan', p'⟩ _
    unfold slot.Z240_loop.body
    refine u346 (fun h1 => ?_) (fun _ => u295 trivial)
    refine u346 (fun h2 => ?_) (fun _ => u295 trivial)
    refine u298 (EA.EA.u1 _ _) fun v => ?_
    refine u303 (by decide) fun i1 _ => ?_
    refine u348 <| u347 (fun h3 => ?_)
      (fun _ => u368 h2 fun plan1 => u353 h1 fun p1 hp1 => u295 ⟨trivial, u315 h1 hp1⟩)
    refine u351 (Nat.le_of_lt h1) fun i2 hi2 => ?_
    refine u347 (fun h4 => ?_)
      (fun _ => u368 h2 fun plan1 => u353 h1 fun p1 hp1 => u295 ⟨trivial, u315 h1 hp1⟩)
    refine u296 (fun _ => ?_)
      (fun _ => u368 h2 fun plan1 => u353 h1 fun p1 hp1 => u295 ⟨trivial, u315 h1 hp1⟩)
    refine u368 h2 fun plan1 => ?_
    have hle:p'.val + (UScalar.cast UScalarTy.Usize i1).val  ≤  n.val :=
      Nat.add_comm _ p'.val ▸ (Nat.add_le_add_right h4 p'.val).trans (Nat.le_of_eq hi2)
    refine u355 hle fun p1 hp1 => ?_
    exact u295 ⟨trivial, u316 h1 (Nat.lt_of_lt_of_le (by decide) h3) hp1⟩
  · trivial
@[local step]
theorem u399 (out n plan) :
    slot.Z240 out n plan ⦃ Y112P5! ⦄ :=
  u398 out n plan _
theorem u400 (x:R):x.val  ≤  Std.Usize.max := by scalar_tac
theorem u401 {α:Type} {x:α} {P:α  →  Prop} (h:P x):(ok x:Result α) ⦃ P ⦄ := (WP.spec_ok x).mpr h
theorem u402 {α β:Type} {m:Result α} {k:α  →  Result β} {Q:α  →  Prop} {P:β  →  Prop}
    (h1:m ⦃ Q ⦄) (h2:∀ x, Q x  →  k x ⦃ P ⦄):(do let x ← m;k x) ⦃ P ⦄ := WP.spec_bind h1 h2
theorem u403 {α β γ:Type} {f:α  →  β  →  Result γ} {a:α} {b:β} {P:γ  →  Prop} (h:f a b ⦃ P ⦄) :
    (uncurry f (a, b)) ⦃ P ⦄ := h
theorem u404 {x y:R} {β:Type} {k:R  →  Result β} {P:β  →  Prop} {a b:Nat}
    (hx:x.val = a) (hy:y.val = b) (h:a + b  ≤  Std.Usize.max)
    (hk:∀ z:R, z.val = a + b  →  k z ⦃ P ⦄):(do let z ← x + y;k z) ⦃ P ⦄ := by
  subst hx hy;exact WP.spec_bind (Usize.add_spec h) hk
theorem u405 {x y:R} {β:Type} {k:R  →  Result β} {P:β  →  Prop} {a b:Nat}
    (hx:x.val = a) (hy:y.val = b) (h:b  ≤  a)
    (hk:∀ z:R, z.val + b = a  →  k z ⦃ P ⦄):(do let z ← x - y;k z) ⦃ P ⦄ := by
  subst hx hy;exact WP.spec_bind (Usize.sub_spec h) (fun z hz => hk z (by omega))
theorem u406 {ty:UScalarTy} {x y:UScalar ty} {β:Type} {k:UScalar ty  →  Result β} {P:β  →  Prop} {b:Nat}
    (hy:y.val = b) (h:0 < b) (hk:∀ z:UScalar ty, z.val < b  →  k z ⦃ P ⦄) :
    (do let z ← x % y;k z) ⦃ P ⦄ := by
  subst hy
  exact WP.spec_bind (UScalar.rem_spec x (by omega)) (fun z hz => hk z (by rw [hz];exact Nat.mod_lt _ h))
theorem u407 {α:Type} {n:R} (v:Array α n) {i:R} {c:Nat}
    (hn:n.val = c) (h:i.val < c):i.val < v.length :=
  lt_of_lt_of_eq h ((Array.length_eq v).trans hn).symm
theorem u408 {α β:Type} {n:R} {v:Array α n} {i:R} {k:α  →  Result β} {P:β  →  Prop}
    {c:Nat} (hn:n.val = c) (h:i.val < c) (hk:∀ x, k x ⦃ P ⦄) :
    (do let x ← Array.index_usize v i;k x) ⦃ P ⦄ :=
  WP.spec_bind (Array.index_usize_spec v i (u407 v hn h)) (fun x _ => hk x)
theorem u409 {α β:Type} {n:R} {v:Array α n} {i:R} {x:α}
    {k:Array α n  →  Result β} {P:β  →  Prop}
    {c:Nat} (hn:n.val = c) (h:i.val < c) (hk:∀ a, a = v.set i x  →  k a ⦃ P ⦄) :
    (do let a ← Array.update v i x;k a) ⦃ P ⦄ :=
  WP.spec_bind (Array.update_spec v i x (u407 v hn h)) hk
theorem u410 {α β:Type} {v:Slice α} {i:R} {k:α  →  Result β} {P:β  →  Prop}
    (h:i.val < v.length) (hk:∀ x, k x ⦃ P ⦄):(do let x ← Slice.index_usize v i;k x) ⦃ P ⦄ :=
  WP.spec_bind (Slice.index_usize_spec v i h) (fun x _ => hk x)
theorem u411 {ty:UScalarTy} {ty1:IScalarTy} {x:UScalar ty} {y:IScalar ty1} {β:Type}
    {k:UScalar ty  →  Result β} {P:β  →  Prop}
    (h:0  ≤  y.val  ∧  y.val < ty.numBits) (hk:∀ z, k z ⦃ P ⦄):(do let z ← x <<< y;k z) ⦃ P ⦄ :=
  WP.spec_bind (UScalar.ShiftLeft_IScalar_spec x y _ h.1 h.2 rfl) (fun z _ => hk z)
theorem u412 {ty:UScalarTy} {ty1:IScalarTy} {x:UScalar ty} {y:IScalar ty1} {β:Type}
    {k:UScalar ty  →  Result β} {P:β  →  Prop} {n:Nat}
    (h:0  ≤  y.val  ∧  y.val < ty.numBits) (hn:y.toNat = n) (hk:∀ z:UScalar ty, z.val = x.val >>> n  →  k z ⦃ P ⦄) :
    (do let z ← x >>> y;k z) ⦃ P ⦄ := by
  subst hn
  exact WP.spec_bind (UScalar.ShiftRight_IScalar_spec x y h.1 h.2) (fun z hz => hk z hz.1)
theorem u413 {src:UScalarTy} (tgt:UScalarTy) (x:UScalar src):(UScalar.cast tgt x).val  ≤  x.val := by
  rw [UScalar.cast_val_eq];exact Nat.mod_le _ _
theorem u414:4294967295  ≤  Std.Usize.max := by scalar_tac
theorem u415 {α:Type} {m:Result α} {Q:α  →  Prop} (h:m ⦃ Q ⦄):m ⦃ Y112P0! ⦄ :=
  WP.spec_mono h (fun _ _ => trivial)
@[local step]
theorem u416 (s i):slot.Z246 s i ⦃ Y112P0! ⦄ := by
  rw [slot.Z246]
  all_goals simp only [lift, bind_tc_ok]
  apply EA.EA.u188 <;> intro h8
  · have h8':8  ≤  s.len.val := (UScalar.le_equiv _ _).mp h8
    refine u405 (b := 8) rfl rfl h8' ?_;intro i1 hi1
    apply EA.EA.u188 <;> intro hle
    · have hb:i.val + 8  ≤  s.length := by
        have hl := Slice.len_val s
        have hle':i.val  ≤  i1.val := (UScalar.le_equiv _ _).mp hle
        omega
      have hm:s.length  ≤  Std.Usize.max := Slice.length_ineq s
      clear hle hi1 h8' h8 i1
      refine u404 (b := 7) rfl rfl (by omega) ?_;intro i2 hi2
      refine u410 (by omega) ?_;intro i3;clear hi2
      refine u411 (by decide) ?_;intro i5
      refine u404 (b := 6) rfl rfl (by omega) ?_;intro i6 hi6
      refine u410 (by omega) ?_;intro i7;clear hi6
      refine u411 (by decide) ?_;intro i9
      refine u404 (b := 5) rfl rfl (by omega) ?_;intro i11 hi11
      refine u410 (by omega) ?_;intro i12;clear hi11
      refine u411 (by decide) ?_;intro i14
      refine u404 (b := 4) rfl rfl (by omega) ?_;intro i16 hi16
      refine u410 (by omega) ?_;intro i17;clear hi16
      refine u411 (by decide) ?_;intro i19
      refine u404 (b := 3) rfl rfl (by omega) ?_;intro i21 hi21
      refine u410 (by omega) ?_;intro i22;clear hi21
      refine u411 (by decide) ?_;intro i24
      refine u404 (b := 2) rfl rfl (by omega) ?_;intro i26 hi26
      refine u410 (by omega) ?_;intro i27;clear hi26
      refine u411 (by decide) ?_;intro i29
      refine u404 (b := 1) rfl rfl (by omega) ?_;intro i31 hi31
      refine u410 (by omega) ?_;intro i32;clear hi31
      refine u411 (by decide) ?_;intro i34
      refine u410 (by omega) ?_;intro i36
      exact u401 trivial
    · exact u401 trivial
  · exact u401 trivial
@[local step]
theorem u417 (s i d cap t run) :
    slot.Z228_loop0 s i d cap t run ⦃ Y112P0! ⦄ := by
  rw [slot.Z228_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (t', run') => cap.val - t'.val + run'.val)
    (inv := fun _ => True)
  · rintro ⟨t', run'⟩ _
    simp only [slot.Z228_loop0.body, lift, bind_tc_ok]
    apply EA.EA.u188 <;> intro hrun
    · have hr:run'.val = 1 := congrArg UScalar.val hrun
      apply EA.EA.u188 <;> intro hcap
      · have hcap':8  ≤  cap.val := (UScalar.le_equiv _ _).mp hcap
        refine u405 (b := 8) rfl rfl hcap' ?_;intro i1 hi1
        apply EA.EA.u188 <;> intro ht
        · have ht':t'.val  ≤  i1.val := (UScalar.le_equiv _ _).mp ht
          have hm := u400 cap
          refine u402 (u416 _ _) ?_;intro i3 _
          refine u402 (u416 _ _) ?_;intro i5 _
          apply EA.EA.u188 <;> intro hx
          · refine u404 (b := 8) rfl rfl (by omega) ?_;intro t1 ht1
            exact u401 ⟨trivial, (by omega:cap.val - t1.val + run'.val < cap.val - t'.val + run'.val)⟩
          · refine u402 (U32.div_spec _ (by decide)) ?_;intro i7 hi7
            have hi7':i7.val = (core.num.U64.leading_zeros (i3 ^^^ i5)).val / 8 := hi7
            have hlz := EA.EA.u12 (i3 ^^^ i5)
            have hc := u413 .Usize i7
            refine u404 rfl rfl (by omega) ?_;intro t1 ht1
            exact u401 ⟨trivial, (by omega:cap.val - t1.val + 0 < cap.val - t'.val + run'.val)⟩
        · exact u401 trivial
      · exact u401 trivial
    · exact u401 trivial
  · trivial
@[local step]
theorem u418 (s i d cap t run) :
    slot.Z228_loop1 s i d cap t run ⦃ Y112P0! ⦄ := by
  rw [slot.Z228_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (t', run') => cap.val - t'.val + run'.val)
    (inv := fun _ => True)
  · rintro ⟨t', run'⟩ _
    simp only [slot.Z228_loop1.body, lift, bind_tc_ok]
    apply EA.EA.u188 <;> intro hrun
    · have hr:run'.val = 1 := congrArg UScalar.val hrun
      apply EA.EA.u188 <;> intro ht
      · have ht':t'.val < cap.val := (UScalar.lt_equiv _ _).mp ht
        have hm := u400 cap
        apply EA.EA.u188 <;> intro ha
        · have ha' := (UScalar.lt_equiv _ _).mp ha
          have hl := Slice.len_val s
          apply EA.EA.u188 <;> intro hd
          · have hd' := (UScalar.le_equiv _ _).mp hd
            refine u410 (by omega) ?_;intro i3
            refine u405 rfl rfl hd' ?_;intro i4 hi4
            refine u410 (by omega) ?_;intro i5
            apply EA.EA.u188 <;> intro he
            · refine u404 (b := 1) rfl rfl (by omega) ?_;intro t1 ht1
              exact u401 ⟨trivial, (by omega:cap.val - t1.val + run'.val < cap.val - t'.val + run'.val)⟩
            · exact u401 ⟨trivial, (by omega:cap.val - t'.val + 0 < cap.val - t'.val + run'.val)⟩
          · exact u401 ⟨trivial, (by omega:cap.val - t'.val + 0 < cap.val - t'.val + run'.val)⟩
        · exact u401 ⟨trivial, (by omega:cap.val - t'.val + 0 < cap.val - t'.val + run'.val)⟩
      · exact u401 trivial
    · exact u401 trivial
  · trivial
@[local step]
theorem u419 (s i d max):slot.Z228 s i d max ⦃ Y112P0! ⦄ := by
  rw [slot.Z228]
  all_goals simp only [lift, bind_tc_ok]
  refine u402 (u415 (u294 ..)) ?_;intro cap _
  refine u402 (u417 _ _ _ _ _ _) ?_;rintro ⟨t, run⟩ _
  exact u403 (u418 _ _ _ _ _ _)
@[local step]
theorem u420 (pc pn want dup z):slot.Z261_loop pc pn want dup z ⦃ Y112P0! ⦄ := by
  rw [slot.Z261_loop]
  apply Std.loop.spec_decr_nat (measure := fun (_, z') => 16 - z'.val) (inv := fun _ => True)
  · rintro ⟨dup', z'⟩ _
    simp only [slot.Z261_loop.body]
    apply EA.EA.u188 <;> intro h1
    · apply EA.EA.u188 <;> intro h2
      · have h2':z'.val < 16 := (UScalar.lt_equiv _ _).mp h2
        refine u408 (c := 16) rfl h2' ?_;intro x
        refine u402 (Q := fun _ => True) ?_ ?_
        · split <;> exact u401 trivial
        intro dup1 _
        refine u404 (b := 1) rfl rfl (by have := u414;omega) ?_;intro z1 hz1
        exact u401 ⟨trivial, (by omega:16 - z1.val < 16 - z'.val)⟩
      · exact u401 trivial
    · exact u401 trivial
  · trivial
@[local step]
theorem u421 (pc pn want):slot.Z261 pc pn want ⦃ Y112P0! ⦄ := by
  rw [slot.Z261];exact u420 _ _ _ _ _
@[local step]
theorem u422 (pc pn c len dist cl cd adj dupmode) :
    slot.Z245 pc pn c len dist cl cd adj dupmode ⦃ Y112P0! ⦄ := by
  rw [slot.Z245]
  all_goals simp only [lift, bind_tc_ok]
  apply EA.EA.u188 <;> intro _
  · exact u401 trivial
  apply EA.EA.u188 <;> intro _
  · apply EA.EA.u188 <;> intro _
    · apply EA.EA.u188 <;> intro _
      · exact u401 trivial
      · apply EA.EA.u188 <;> intro _
        · exact u421 _ _ _
        · exact u401 trivial
    · apply EA.EA.u188 <;> intro _
      · exact u421 _ _ _
      · exact u401 trivial
  · apply EA.EA.u188 <;> intro _
    · exact u421 _ _ _
    · exact u401 trivial
@[local step]
theorem u423 (input rs c i last pc pn adj cl cd tbmax dupmode) :
    slot.Z257 input rs c i last pc pn adj cl cd tbmax dupmode ⦃ Y112P0! ⦄ := by
  rw [slot.Z257]
  all_goals simp only [lift, bind_tc_ok]
  refine u406 (b := 512) rfl (by decide) ?_;intro i1 _
  refine u412 (n := 9) (by decide) rfl ?_;intro i2 _
  apply EA.EA.u188 <;> intro h1
  · exact u401 trivial
  apply EA.EA.u188 <;> intro h2
  · exact u401 trivial
  apply EA.EA.u188 <;> intro h3
  · exact u401 trivial
  apply EA.EA.u188 <;> intro h4
  · exact u401 trivial
  apply EA.EA.u188 <;> intro h5
  · exact u401 trivial
  refine u402 (u422 _ _ _ _ _ _ _ _ _) ?_;intro dup _
  refine u402 (Q := fun _ => True) ?_ ?_
  · apply EA.EA.u188 <;> intro hd
    · have h5':¬ (258 < (UScalar.cast .Usize i1).val) := (UScalar.lt_equiv _ _).not.mp h5
      refine u405 (a := 258) rfl rfl (by omega) ?_;intro i3 _
      refine u402 (u415 (u294 ..)) ?_;intro i4 _
      exact u419 _ _ _ _
    · exact u401 trivial
  intro t _
  have h2':¬ ((UScalar.cast .Usize i2).val < 1) := (UScalar.lt_equiv _ _).not.mp h2
  refine u405 (b := 1) rfl rfl (by omega) ?_;intro i4 _
  refine u411 (by decide) ?_;intro i6
  refine u411 (by decide) ?_;intro i9
  refine u402 (u415 (u291 ..)) ?_;intro rs1 _
  exact u401 trivial
@[local step]
theorem u424 (input rs cands nc i pc pn cl cd tbmax dupmode adj q last) :
    slot.Z258_loop input rs cands nc i pc pn cl cd tbmax dupmode adj q last ⦃ Y112P0! ⦄ := by
  rw [slot.Z258_loop]
  apply Std.loop.spec_decr_nat (measure := fun (_, q', _) => 16 - q'.val) (inv := fun _ => True)
  · rintro ⟨rs', q', last'⟩ _
    simp only [slot.Z258_loop.body]
    apply EA.EA.u188 <;> intro h1
    · apply EA.EA.u188 <;> intro h2
      · have h2':q'.val < 16 := (UScalar.lt_equiv _ _).mp h2
        refine u408 (c := 16) rfl h2' ?_;intro c
        refine u402 (u423 _ _ _ _ _ _ _ _ _ _ _ _) ?_;rintro ⟨last1, rs1⟩ _
        refine u403 ?_
        refine u404 (b := 1) rfl rfl (by have := u414;omega) ?_;intro q1 hq1
        exact u401 ⟨trivial, (by omega:16 - q1.val < 16 - q'.val)⟩
      · exact u401 trivial
    · exact u401 trivial
  · trivial
@[local step]
theorem u425 (input rs cands nc i pc pn ppos cl cd tbmax dupmode) :
    slot.Z258 input rs cands nc i pc pn ppos cl cd tbmax dupmode ⦃ Y112P0! ⦄ := by
  rw [slot.Z258]
  all_goals simp only [lift, bind_tc_ok]
  refine u402 (u424 _ _ _ _ _ _ _ _ _ _ _ _ _ _) ?_;intro rs1 _
  refine u402 (u415 (u291 ..)) ?_;intro rs2 _
  exact u415 (u291 ..)
@[local step]
theorem u426 (lsym) (l e:R) (hl:l.val < 257) (he:e.val  ≤  258) :
    slot.Z241_loop0_loop0 lsym l e ⦃ fun r => e.val  ≤  r.val  ∧  r.val  ≤  258 ⦄ := by
  rw [slot.Z241_loop0_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun e' => 258 - e'.val)
    (inv := fun e' => e.val  ≤  e'.val  ∧  e'.val  ≤  258)
  · rintro e' ⟨h1, h2⟩
    simp only [slot.Z241_loop0_loop0.body]
    have hM := u414
    apply EA.EA.u188 <;> intro hlt
    · have hlt':e'.val < 258 := (UScalar.lt_equiv _ _).mp hlt
      refine u404 (b := 1) rfl rfl (by omega) ?_;intro i hi
      refine u408 (c := 512) rfl (by omega) ?_;intro i1
      refine u404 (b := 1) rfl rfl (by omega) ?_;intro i2 hi2
      refine u408 (c := 512) rfl (by omega) ?_;intro i3
      apply EA.EA.u188 <;> intro _
      · exact u401 ⟨⟨(by omega:e.val  ≤  i.val), (by omega:i.val  ≤  258)⟩,
          (by omega:258 - i.val < 258 - e'.val)⟩
      · exact u401 ⟨h1, h2⟩
    · exact u401 ⟨h1, h2⟩
  · exact ⟨le_refl _, he⟩
theorem u427 (nx a:Array Std.U16 512#usize) (l:R) (v:Std.U16)
    (hl:l.val < 512) (hv:l.val < v.val) (ha:a = nx.set l v)
    (h2:∀ j, j < l.val  →  j < (nx.val[j]!).val) :
    ∀ j, j < l.val + 1  →  j < (a.val[j]!).val := by
  intro j hj
  rw [ha, Array.set_val_eq, u220!_set _ _ _ _ (lt_of_lt_of_eq hl (Array.length_eq nx).symm)]
  split
  · omega
  · exact h2 j (by omega)
@[local step]
theorem u428 (lsym) (nextl:Array Std.U16 512#usize) (flen l:R)
    (hl:l.val  ≤  512) (hnx:∀ j, j < l.val  →  j < (nextl.val[j]!).val) :
    slot.Z241_loop0 lsym nextl flen l ⦃ fun r => u205 r ⦄ := by
  rw [slot.Z241_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, l') => 512 - l'.val)
    (inv := fun (nx', l') => l'.val  ≤  512  ∧  ∀ j, j < l'.val  →  j < (nx'.val[j]!).val)
  · rintro ⟨nx', l'⟩ ⟨h1, h2⟩
    simp only [slot.Z241_loop0.body, lift, bind_tc_ok]
    have hM := u414
    apply EA.EA.u188 <;> intro hlt
    · have hlt':l'.val < 512 := (UScalar.lt_equiv _ _).mp hlt
      apply EA.EA.u188 <;> intro _
      · refine u404 (b := 1) rfl rfl (by omega) ?_;intro i hi
        refine u409 (c := 512) rfl hlt' ?_;intro a ha
        have hv:(UScalar.cast .U16 i).val = i.val :=
          UScalar.cast_val_mod_pow_of_inBounds_eq _ _ (by show i.val < 65536;omega)
        have hs := u427 nx' a l' _ hlt' (by omega) ha h2
        exact u401 ⟨⟨(by omega:i.val  ≤  512), fun j (hj:j < i.val) => hs j (by omega)⟩,
          (by omega:512 - i.val < 512 - l'.val)⟩
      · apply EA.EA.u188 <;> intro h257
        · refine u404 (b := 1) rfl rfl (by omega) ?_;intro i hi
          refine u409 (c := 512) rfl hlt' ?_;intro a ha
          have hv:(UScalar.cast .U16 i).val = i.val :=
            UScalar.cast_val_mod_pow_of_inBounds_eq _ _ (by show i.val < 65536;omega)
          have hs := u427 nx' a l' _ hlt' (by omega) ha h2
          exact u401 ⟨⟨(by omega:i.val  ≤  512), fun j (hj:j < i.val) => hs j (by omega)⟩,
            (by omega:512 - i.val < 512 - l'.val)⟩
        · have h257':¬ (257  ≤  l'.val) := (UScalar.le_equiv _ _).not.mp h257
          refine u404 (b := 1) rfl rfl (by omega) ?_;intro e he
          refine u402 (u426 _ _ _ (by omega) (by omega)) ?_;intro e1 he1
          refine u409 (c := 512) rfl hlt' ?_;intro a ha
          refine u404 (b := 1) rfl rfl (by omega) ?_;intro l1 hl1
          have hv:(UScalar.cast .U16 e1).val = e1.val :=
            UScalar.cast_val_mod_pow_of_inBounds_eq _ _ (by show e1.val < 65536;omega)
          have hs := u427 nx' a l' _ hlt' (by omega) ha h2
          exact u401 ⟨⟨(by omega:l1.val  ≤  512), fun j (hj:j < l1.val) => hs j (by omega)⟩,
            (by omega:512 - l1.val < 512 - l'.val)⟩
    · have hge:¬ (l'.val < 512) := (UScalar.lt_equiv _ _).not.mp hlt
      exact u401 (fun j hj => h2 j (by omega))
  · exact ⟨hl, hnx⟩
@[local step]
theorem u429 (lsym) (nextl:Array Std.U16 512#usize) (flen:R) :
    slot.Z241 lsym nextl flen ⦃ fun r => u205 r ⦄ := by
  rw [slot.Z241]
  exact u428 _ _ _ _ (Nat.zero_le _) (fun j hj => absurd hj (Nat.not_lt_zero _))
@[local step]
theorem u430 (s:I) (prev:C 32768#usize) (i:R) (b8:Std.U64)
    (cap:R) (cands) (nice nc best c k:R)
    (hc:c.val  ≤  i.val) (hcap:9  ≤  cap.val) (hic:i.val + cap.val  ≤  s.length)
    (hs8:s.length + 8  ≤  Std.Usize.max) (hb:best.val  ≤  cap.val) :
    slot.Z268_loop s prev i b8 cap cands nice nc best c k
      ⦃ fun r => best.val  ≤  r.2.2.val  ∧  r.2.2.val  ≤  cap.val ⦄ := by
  rw [slot.Z268_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, k') => k'.val)
    (inv := fun (_, _, best', c', _) => c'.val  ≤  i.val  ∧  best.val  ≤  best'.val  ∧  best'.val  ≤  cap.val)
  · rintro ⟨cands', nc', best', c', k'⟩ ⟨h1, h2, h3⟩
    simp only [slot.Z268_loop.body, lift, bind_tc_ok]
    apply EA.EA.u188 <;> intro hk
    · have hk':0 < k'.val := (UScalar.lt_equiv _ _).mp hk
      apply EA.EA.u188 <;> intro _
      · apply EA.EA.u188 <;> intro _
        · apply EA.EA.u188 <;> intro _
          · apply EA.EA.u188 <;> intro hnc
            · have hnc':nc'.val < 15 := (UScalar.lt_equiv _ _).mp hnc
              refine u402 (u228 _ _ _ _ _ _ h1 hcap hic hs8) ?_;intro l hl
              refine u402 (Q := fun (x:C 16#usize  ×  R  ×  R) =>
                best.val  ≤  x.2.2.val  ∧  x.2.2.val  ≤  cap.val) ?_ ?_
              · apply EA.EA.u188 <;> intro hl0
                · have hl0':0 < l.val := (UScalar.lt_equiv _ _).mp hl0
                  apply EA.EA.u188 <;> intro _
                  · refine u411 (by decide) ?_;intro i4
                    refine u406 (b := 16) rfl (by decide) ?_;intro i5 hi5
                    refine u409 (c := 16) rfl hi5 ?_;intro a _
                    refine u404 (b := 1) rfl rfl (by have := u414;omega) ?_;intro nc2 _
                    exact u401 ⟨(by omega:best.val  ≤  l.val), hl.1⟩
                  · exact u401 ⟨h2, h3⟩
                · exact u401 ⟨h2, h3⟩
              rintro ⟨cands1, nc1, best1⟩ ⟨hb1, hb2⟩
              refine u403 (u403 ?_)
              refine u406 (b := 32768) Submission.EA.EA.C_WS_val (by decide) ?_;intro i2 hi2
              refine u408 (c := 32768) rfl hi2 ?_;intro i3
              apply EA.EA.u188 <;> intro hnx
              · have hnx' := (UScalar.lt_equiv _ _).mp hnx
                refine u405 (b := 1) rfl rfl (by omega) ?_;intro k1 hk1
                exact u401 ⟨⟨(by omega:(UScalar.cast .Usize i3).val  ≤  i.val), hb1, hb2⟩,
                  (by omega:k1.val < k'.val)⟩
              · exact u401 ⟨⟨h1, hb1, hb2⟩, hk'⟩
            · exact u401 ⟨⟨h1, h2, h3⟩, hk'⟩
          · exact u401 ⟨⟨h1, h2, h3⟩, hk'⟩
        · exact u401 ⟨⟨h1, h2, h3⟩, hk'⟩
      · exact u401 ⟨⟨h1, h2, h3⟩, hk'⟩
    · exact u401 ⟨h2, h3⟩
  · exact ⟨hc, le_refl _, hb⟩
@[local step]
theorem u431 (s:I) (prev) (i start depth:R) (b8:Std.U64)
    (cap:R) (cands) (nc0 best0 nice:R)
    (hst:start.val  ≤  i.val) (hcap:9  ≤  cap.val) (hic:i.val + cap.val  ≤  s.length)
    (hs8:s.length + 8  ≤  Std.Usize.max) (hb:best0.val  ≤  cap.val) :
    slot.Z268 s prev i start depth b8 cap cands nc0 best0 nice
      ⦃ fun r => best0.val  ≤  r.1.2.val  ∧  r.1.2.val  ≤  cap.val ⦄ := by
  rw [slot.Z268]
  refine u402 (u430 _ _ _ _ _ _ _ _ _ _ _ hst hcap hic hs8 hb) ?_
  rintro ⟨cands1, nc, best⟩ ⟨h1, h2⟩
  exact u403 (u403 (u401 ⟨h1, h2⟩))
@[local step]
theorem u432 (input:I) (pa lc) (i s len dd tmax t bt:R) (bv:W)
    (hi:i.val < input.length) (hlen:len.val < 512) (hdd:dd.val < 8388608)
    (hN:input.length + 2147483648  ≤  Std.Usize.max)
    (ht:t.val  ≤  i.val) (hbt:bt.val  ≤  t.val) :
    slot.Z227_loop input pa lc i s len dd tmax t bt bv ⦃ fun r => r.1.val  ≤  i.val ⦄ := by
  rw [slot.Z227_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (t', _, _) => tmax.val - t'.val)
    (inv := fun (t', bt', _) => t'.val  ≤  i.val  ∧  bt'.val  ≤  t'.val)
  · rintro ⟨t', bt', bv'⟩ ⟨h1, h2⟩
    simp only [slot.Z227_loop.body, lift, bind_tc_ok]
    have hbi:bt'.val  ≤  i.val := Nat.le_trans h2 h1
    have hiM:i.val + 2147483648  ≤  Std.Usize.max := by omega
    clear hN ht hbt
    apply EA.EA.u188 <;> intro ht
    · have ht':t'.val < tmax.val := (UScalar.lt_equiv _ _).mp ht
      refine u404 rfl rfl (by omega) ?_;intro i1 _
      apply EA.EA.u188 <;> intro _
      · refine u404 (b := 1) rfl rfl (by omega) ?_;intro i2 hi2
        refine u404 rfl rfl (by omega) ?_;intro i3 hi3
        apply EA.EA.u188 <;> intro hge
        · have hA:i2.val + dd.val  ≤  i.val := by have := (UScalar.le_equiv _ _).mp hge;omega
          clear hge hi3 i3 hdd
          refine u405 rfl rfl h1 ?_;intro i4 hi4
          refine u405 (b := 1) rfl rfl (by omega) ?_;intro i5 _
          apply EA.EA.u188 <;> intro _
          · refine u405 (b := 1) rfl rfl (by omega) ?_;intro i6 hi6
            refine u410 (by omega) ?_;intro i7;clear hi6
            refine u405 (b := 1) rfl rfl (by omega) ?_;intro i8 hi8
            refine u405 rfl rfl (by omega) ?_;intro i9 hi9
            refine u410 (by omega) ?_;intro i10;clear hi9 hi8 hi4
            apply EA.EA.u188 <;> intro _
            · have hle:i2.val  ≤  i.val := Nat.le_trans (Nat.le_add_right _ _) hA
              have hbt2:bt'.val  ≤  i2.val := by omega
              have hms:tmax.val - i2.val < tmax.val - t'.val := by omega
              refine u405 rfl rfl hle ?_;intro i11 _
              refine u406 (b := 8192) u207 (by decide) ?_;intro i12 hi12
              refine u408 (c := 8192) rfl hi12 ?_;intro i13
              refine u412 (n := 32) (by decide) rfl ?_;intro i14 _
              refine u404 rfl rfl (by omega) ?_;intro i16 _
              refine u406 (b := 512) rfl (by decide) ?_;intro i17 hi17
              refine u408 (c := 512) rfl hi17 ?_;intro i18
              apply EA.EA.u188 <;> intro _
              · exact u401 ⟨⟨hle, le_refl _⟩, hms⟩
              · exact u401 ⟨⟨hle, hbt2⟩, hms⟩
            · exact u401 hbi
          · exact u401 hbi
        · exact u401 hbi
      · exact u401 hbi
    · exact u401 hbi
  · exact ⟨ht, hbt⟩
@[local step]
theorem u433 (input:I) (pa lc) (i s len dd tmax:R)
    (hi:i.val < input.length) (hlen:len.val < 512) (hdd:dd.val < 8388608)
    (hN:input.length + 2147483648  ≤  Std.Usize.max) :
    slot.Z227 input pa lc i s len dd tmax ⦃ fun r => r.1.val  ≤  i.val ⦄ := by
  rw [slot.Z227]
  exact u432 _ _ _ _ _ _ _ _ _ _ _ hi hlen hdd hN (Nat.zero_le _) (le_refl _)
@[local step]
theorem u434 (input:I) (pa cands nc lc) (nextl:Array Std.U16 512#usize)
    (dtab dcc) (i s:R) (base:W) (pcd fback lo k:R)
    (hnx:u205 nextl) (hi:i.val < input.length) (hN:input.length + 2147483648  ≤  Std.Usize.max) :
    slot.Z260_loop input pa cands nc lc nextl dtab dcc i s base pcd fback lo k ⦃ Y112P0! ⦄ := by
  rw [slot.Z260_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, k') => 16 - k'.val)
    (inv := fun _ => True)
  · rintro ⟨pa', lo', k'⟩ _
    simp only [slot.Z260_loop.body, lift, bind_tc_ok]
    apply EA.EA.u188 <;> intro _
    · apply EA.EA.u188 <;> intro h2
      · have h2':k'.val < 16 := (UScalar.lt_equiv _ _).mp h2
        have hM := u414
        refine u408 (c := 16) rfl h2' ?_;intro c
        refine u406 (b := 512) rfl (by decide) ?_;intro i1 hi1
        refine u412 (n := 9) (by decide) rfl ?_;intro i2 hi2
        have hlen := u413 .Usize i1
        have hdd := u413 .Usize i2
        have h9 := u216 c
        refine u402 (u239 _ _) ?_;intro i3 _
        refine u406 (b := 32) rfl (by decide) ?_;intro ds hds
        refine u408 (c := 32) rfl hds ?_;intro i4
        refine u402 (u236 _ _ _ _ _ _ _ _ hnx (by omega) (by omega)) ?_;intro pa1 _
        refine u404 (b := 1) rfl rfl (by omega) ?_;intro lo1 _
        refine u402 (Q := fun _ => True) ?_ ?_
        · apply EA.EA.u188 <;> intro _
          · apply EA.EA.u188 <;> intro _
            · refine u404 rfl rfl (by have := u214;omega) ?_;intro i7 _
              apply EA.EA.u188 <;> intro _
              · refine u402 (u433 _ _ _ _ _ _ _ _ hi (by omega) (by omega) hN) ?_
                rintro ⟨i8, i9⟩ hbb
                have hbb':i8.val  ≤  i.val := hbb
                refine u403 ?_
                apply EA.EA.u188 <;> intro _
                · refine u404 rfl rfl (by omega) ?_;intro i10 _
                  refine u404 rfl rfl (by omega) ?_;intro i14 _
                  exact u234 _ _ _ _
                · exact u401 trivial
              · exact u401 trivial
            · exact u401 trivial
          · exact u401 trivial
        intro pa2 _
        refine u404 (b := 1) rfl rfl (by omega) ?_;intro k1 hk1
        exact u401 ⟨trivial, (by omega:16 - k1.val < 16 - k'.val)⟩
      · exact u401 trivial
    · exact u401 trivial
  · trivial
@[local step]
theorem u435 (input:I) (pa cands nc lc) (nextl:Array Std.U16 512#usize)
    (dtab dcc) (i s:R) (base:W) (pcd fback:R)
    (hnx:u205 nextl) (hi:i.val < input.length) (hN:input.length + 2147483648  ≤  Std.Usize.max) :
    slot.Z260 input pa cands nc lc nextl dtab dcc i s base pcd fback ⦃ Y112P0! ⦄ := by
  rw [slot.Z260]
  exact u434 _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ hnx hi hN
@[local step]
theorem u436 (input:I) (pa cands nc lc) (nextl:Array Std.U16 512#usize)
    (dtab dcc) (i s:R) (base:W) (pcd fback:R)
    (hnx:u205 nextl) (hi:i.val < input.length) (hN:input.length + 2147483648  ≤  Std.Usize.max) :
    slot.Z259 input pa cands nc lc nextl dtab dcc i s base pcd fback ⦃ Y112P0! ⦄ := by
  rw [slot.Z259]
  apply EA.EA.u188 <;> intro _
  · exact u241 _ _ _ _ _ _ _ _ _ _ _ _ hnx hi hN
  · exact u435 _ _ _ _ _ _ _ _ _ _ _ _ _ hnx hi hN
@[local step]
theorem u437 (input:I) (plan rs)
    (ct lazyn d4 d7 skip h3d tbmax lz2max dupmode fback d7l d7e nice n:R)
    (head3:C 16384#usize) (head4:C 65536#usize) (prev4)
    (head7:C 65536#usize) (prev7 pa tb) (lsym:G 512#usize) (dtab)
    (nextl:Array Std.U16 512#usize) (lf df litc lc dcc) (lim:R) (sh7:W)
    (s next_upd:R) (cands pc) (pn ppos cl cd:R) (cdc:W) (i anchor alen:R)
    (hn:n.val = input.length) (hlim:lim.val + 8 = n.val)
    (hN:input.length + input.length  ≤  Std.Usize.max)
    (hls:EA.EA.u15 lsym.val 28) (hnx:u205 nextl)
    (hsi:s.val  ≤  i.val) (hin:i.val  ≤  n.val) (hcl:cl.val < 512)
    (h3:EA.EA.u15 head3.val i.val) (h4:EA.EA.u15 head4.val i.val) (h7:EA.EA.u15 head7.val i.val) :
    slot.Z251_loop input plan rs ct lazyn d4 d7 skip h3d tbmax lz2max dupmode fback d7l d7e nice n
      head3 head4 prev4 head7 prev7 pa tb lsym dtab nextl lf df litc lc dcc lim sh7 s next_upd cands pc pn ppos
      cl cd cdc i anchor alen ⦃ Y112P0! ⦄ := by
  have hS := u206 hN
  rw [slot.Z251_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, i', _, _) => lim.val - i'.val)
    (inv := fun (_, _, h3', h4', _, h7', _, _, _, _, _, _, _, _, s', _, _, _, _, _, cl', _, _, i', _, _) =>
       s'.val  ≤  i'.val  ∧  i'.val  ≤  n.val  ∧  cl'.val < 512  ∧  EA.EA.u15 h3'.val i'.val  ∧  EA.EA.u15 h4'.val i'.val  ∧ 
       EA.EA.u15 h7'.val i'.val)
  · rintro ⟨plan', rs', h3', h4', p4', h7', p7', pa', tb', lf', df', litc', lc', dcc', s', nu', cands', pc', pn',
      ppos', cl', cd', cdc', i', anc', alen'⟩ ⟨hs', hi', hcl', hh3, hh4, hh7⟩
    clear hsi hin hcl h3 h4 h7
    clear plan rs head3 head4 prev4 head7 prev7 pa tb lf df litc lc dcc s next_upd cands pc pn ppos cl cd cdc i
      anchor alen
    simp only [slot.Z251_loop.body, lift, bind_tc_ok]
    apply EA.EA.u188 <;> intro hlt
    swap
    · exact u401 trivial
    have hlt':i'.val < lim.val := (UScalar.lt_equiv _ _).mp hlt
    have hiM:i'.val + 2147483648  ≤  Std.Usize.max := by clear * - hi' hn hS;omega
    refine u402 (Q := fun _ => True) ?_ ?_
    · apply EA.EA.u188 <;> intro _
      · refine u404 (b := 258) rfl rfl (by clear * - hiM;omega) ?_;intro i1 _
        refine u406 (b := 8192) u207 (by decide) ?_;intro i2 hi2
        exact u415 (Array.update_spec _ _ _ (u407 _ rfl hi2))
      · exact u401 trivial
    intro pa1 _
    refine u402 (u221 _ _ (by clear * - hiM;omega)) ?_;intro b8 _
    refine u402 (u230 _ _ _ _ _ _ _ _ i'.val hh3 hh4 hh7 (le_refl _)) ?_
    rintro ⟨⟨c3, c4, c7⟩, head31, head41, prev41, head71, prev71⟩ ⟨hq1, hq2, hq3, hL3, hL4, hL7⟩
    have hq1:c3.val  ≤  i'.val := hq1
    have hq2:c4.val  ≤  i'.val := hq2
    have hq3:c7.val  ≤  i'.val := hq3
    have hL3:EA.EA.u15 head31.val i'.val := hL3
    have hL4:EA.EA.u15 head41.val i'.val := hL4
    have hL7:EA.EA.u15 head71.val i'.val := hL7
    iterate 5 refine u403 ?_
    refine u406 (b := 8192) u207 (by decide) ?_;intro i1 hi1
    refine u408 (c := 8192) rfl hi1 ?_;intro i2
    refine u412 (n := 32) (by decide) rfl ?_;intro i3 _
    refine u404 (b := 1) rfl rfl (by clear * - hiM;omega) ?_;intro i4 hi4
    refine u412 (n := 56) (by decide) rfl ?_;intro i5 _
    refine u406 (b := 256) rfl (by decide) ?_;intro i7 hi7
    refine u408 (c := 256) rfl hi7 ?_;intro i8
    refine u402 (u234 _ _ _ _) ?_;intro pa2 _
    refine u402 (Q := fun _ => True) ?_ ?_
    · apply EA.EA.u188 <;> intro _ <;> exact u401 trivial
    intro lzn _
    refine u402 (Q := fun _ => True) ?_ ?_
    · apply EA.EA.u188 <;> intro _
      · exact u401 trivial
      · refine u402 (Q := fun _ => True) ?_ ?_
        · apply EA.EA.u188 <;> intro _ <;> exact u401 trivial
        intro _ _;exact u401 trivial
    rintro ⟨lazy_here, dep7⟩ _
    refine u403 ?_
    clear hi1 hi7 hh3 hh4 hh7 hlt
    refine u402 (Q := fun (x:alloc.vec.Vec W  ×  alloc.vec.Vec W  ×  C 16384#usize  × 
          C 65536#usize  ×  C 32768#usize  ×  C 65536#usize  ×  C 32768#usize  × 
          Array Std.U64 8192#usize  ×  C 8192#usize  ×  C 320#usize  ×  C 32#usize  × 
          R  ×  C 16#usize  ×  C 16#usize  ×  R  ×  R  ×  R  ×  R  × 
          W  ×  R  ×  R  ×  R) =>
        match x with
        | (_, _, g3, g4, _, g7, _, _, _, _, _, s1, _, _, _, _, cl1, _, _, i12, _, _) =>
          s1.val  ≤  i12.val  ∧  i'.val < i12.val  ∧  i12.val  ≤  n.val  ∧  cl1.val < 512  ∧ 
          EA.EA.u15 g3.val i12.val  ∧  EA.EA.u15 g4.val i12.val  ∧  EA.EA.u15 g7.val i12.val) ?_ ?_
    · apply u289
      · -- continue inside the running match
        intro _ hc3 _
        have hc3':3  ≤  cl'.val := (UScalar.le_equiv _ _).mp hc3
        have h14:i'.val < i4.val := by clear * - hi4;omega
        refine u404 rfl rfl (by clear * - hiM hcl';omega) ?_;intro i13 _
        refine u406 (b := 512) rfl (by decide) ?_;intro i15 hi15
        refine u408 (c := 512) rfl hi15 ?_;intro i16
        refine u411 (by decide) ?_;intro i19
        refine u402 (u234 _ _ _ _) ?_;intro pa4 _
        refine u405 (b := 1) rfl rfl (by clear * - hc3';omega) ?_;intro cl2 hcl2
        exact u401 ⟨(by clear * - hs' h14;omega:s'.val  ≤  i4.val), h14,
          (by clear * - hi4 hlt' hlim;omega:i4.val  ≤  n.val), (by clear * - hcl2 hcl';omega:cl2.val < 512),
          EA.EA.u17 hL3 (Nat.le_of_lt h14), EA.EA.u17 hL4 (Nat.le_of_lt h14), EA.EA.u17 hL7 (Nat.le_of_lt h14)⟩
      · -- the search
        refine u405 rfl rfl hi' ?_;intro cap hcap
        refine u402 (Q := fun (x:R) => 9  ≤  x.val  ∧  i'.val + x.val  ≤  n.val) ?_ ?_
        · apply EA.EA.u188 <;> intro h
          · have h':258 < cap.val := (UScalar.lt_equiv _ _).mp h
            exact u401 ⟨(by decide:9  ≤  258), (by clear * - h' hcap;omega:i'.val + 258  ≤  n.val)⟩
          · exact u401 ⟨(by clear * - hcap hlt' hlim;omega:9  ≤  cap.val),
              (by clear * - hcap;omega:i'.val + cap.val  ≤  n.val)⟩
        rintro cap1 ⟨hcap1, hcap2⟩
        iterate 2 refine u403 ?_
        have hic:i'.val + cap1.val  ≤  input.length := by clear * - hcap2 hn;omega
        have hs8:input.length + 8  ≤  Std.Usize.max := by clear * - hS;omega
        have hilt:i'.val < input.length := by clear * - hic hcap1;omega
        clear hcap cap
        refine u402 (Q := fun (x:C 16#usize  ×  R  ×  R  ×  Bool) =>
          2  ≤  x.2.2.1.val  ∧  x.2.2.1.val  ≤  cap1.val) ?_ ?_
        · apply EA.EA.u188 <;> intro _
          · refine u402 (u228 _ _ _ _ _ _ hq1 hcap1 hic hs8) ?_;intro l3 hl3
            refine u402 (Q := fun (x:C 16#usize  ×  R  ×  R) =>
              2  ≤  x.2.2.val  ∧  x.2.2.val  ≤  cap1.val) ?_ ?_
            · apply EA.EA.u188 <;> intro h0
              · have h0':0 < l3.val := (UScalar.lt_equiv _ _).mp h0
                have hl3':l3.val = 0  ∨  2 < l3.val := hl3.2
                refine u411 (by decide) ?_;intro i21
                refine u409 (c := 16) rfl (by decide) ?_;intro a1 _
                exact u401 ⟨(by clear * - h0' hl3';omega:2  ≤  l3.val), hl3.1⟩
              · exact u401 ⟨(by decide:2  ≤  2), (by clear * - hcap1;omega:2  ≤  cap1.val)⟩
            rintro ⟨a, i17, i18⟩ ⟨hb1, hb2⟩
            exact u403 (u403 (u401 ⟨hb1, hb2⟩))
          · exact u401 ⟨(by decide:2  ≤  2), (by clear * - hcap1;omega:2  ≤  cap1.val)⟩
        rintro ⟨cands2, nc, best, p3⟩ ⟨hb1, hb2⟩
        have hb1:2  ≤  best.val := hb1
        have hb2:best.val  ≤  cap1.val := hb2
        iterate 3 refine u403 ?_
        refine u402 (Q := fun _ => True) ?_ ?_
        · apply EA.EA.u188 <;> intro _ <;> exact u401 trivial
        intro b _
        refine u402 (u229 _ _ _ _) ?_;rintro ⟨i17, i18⟩ hsk
        have hsk:i17.val  ≤  i'.val := Nat.le_trans hsk hq2
        refine u403 ?_
        refine u402 (u431 _ _ _ _ _ _ _ _ _ _ _ hsk hcap1 hic hs8 hb2) ?_
        rintro ⟨⟨nc1, best1⟩, cands3⟩ ⟨hw1, hw2⟩
        have hw1:2  ≤  best1.val := Nat.le_trans hb1 hw1
        have hw2:best1.val  ≤  cap1.val := hw2
        iterate 2 refine u403 ?_
        refine u402 (Q := fun _ => True) ?_ ?_
        · apply EA.EA.u188 <;> intro _
          · exact u401 trivial
          · refine u402 (Q := fun _ => True) ?_ ?_
            · apply EA.EA.u188 <;> intro _ <;> exact u401 trivial
            intro _ _;exact u401 trivial
        rintro ⟨cands4, dep71⟩ _
        refine u403 ?_
        refine u402 (Q := fun _ => True) ?_ ?_
        · apply EA.EA.u188 <;> intro _
          · apply EA.EA.u188 <;> intro _
            · exact u401 trivial
            · apply EA.EA.u188 <;> intro _ <;> exact u401 trivial
          · apply EA.EA.u188 <;> intro _ <;> exact u401 trivial
        intro b1 _
        refine u402 (u229 _ _ _ _) ?_;rintro ⟨i19, i20⟩ hsk2
        have hsk2:i19.val  ≤  i'.val := Nat.le_trans hsk2 hq3
        refine u403 ?_
        refine u402 (u431 _ _ _ _ _ _ _ _ _ _ _ hsk2 hcap1 hic hs8 hw2) ?_
        rintro ⟨⟨nc2, best2⟩, cands5⟩ ⟨hw3, hw4⟩
        have hw3:2  ≤  best2.val := Nat.le_trans hw1 hw3
        have hw4:best2.val  ≤  cap1.val := hw4
        iterate 2 refine u403 ?_
        refine u402 (Q := fun (x:C 16#usize  ×  R  ×  R) =>
          2  ≤  x.2.2.val  ∧  x.2.2.val  ≤  cap1.val) ?_ ?_
        · apply u290
          · intro hgt hle
            have hgt':best2.val < cl'.val := (UScalar.lt_equiv _ _).mp hgt
            refine u402 (u243 _ _ _) ?_;intro nc4 _
            refine u411 (by decide) ?_;intro i23
            refine u406 (b := 16) rfl (by decide) ?_;intro i24 hi24
            refine u409 (c := 16) rfl hi24 ?_;intro a _
            refine u402 (Q := fun _ => True) ?_ ?_
            · apply EA.EA.u188 <;> intro h16
              · have h16':nc4.val < 16 := (UScalar.lt_equiv _ _).mp h16
                exact u415 (Usize.add_spec (by
                  have := u414
                  show nc4.val + 1  ≤  Std.Usize.max
                  clear * - h16' this;omega))
              · exact u401 trivial
            intro i26 _
            exact u401 ⟨(by clear * - hgt' hw3;omega:2  ≤  cl'.val), (UScalar.le_equiv _ _).mp hle⟩
          · exact u401 ⟨hw3, hw4⟩
        rintro ⟨cands6, nc3, best3⟩ ⟨hb3, hb4⟩
        have hb3:2  ≤  best3.val := hb3
        have hb4:best3.val  ≤  cap1.val := hb4
        iterate 2 refine u403 ?_
        clear hb1 hb2 hw1 hw2 hw3 hw4 hsk hsk2 hq1 hq2 hq3
        refine u402 (u425 _ _ _ _ _ _ _ _ _ _ _ _) ?_;intro rs2 _
        refine u402 (Q := fun _ => True) ?_ ?_
        · apply EA.EA.u188 <;> intro _ <;> exact u401 trivial
        intro pcd _
        refine u402 (u244 _ _ _ _) ?_;intro alen2 _
        refine u402 (u244 _ _ _ _) ?_;intro anchor2 _
        refine u402 (Q := fun (x:R  ×  R  ×  W) => x.1.val < 512) ?_ ?_
        · apply EA.EA.u188 <;> intro hnc
          · have hnc':0 < nc3.val := (UScalar.lt_equiv _ _).mp hnc
            refine u405 (b := 1) rfl rfl hnc' ?_;intro i21 _
            refine u406 (b := 16) rfl (by decide) ?_;intro i22 hi22
            refine u408 (c := 16) rfl hi22 ?_;intro top
            refine u406 (b := 512) rfl (by decide) ?_;intro i23 hi23
            refine u412 (n := 9) (by decide) rfl ?_;intro i25 _
            refine u402 (u239 _ _) ?_;intro i26 _
            refine u406 (b := 32) rfl (by decide) ?_;intro i27 hi27
            refine u408 (c := 32) rfl hi27 ?_;intro cdc3
            have hsat := u288 (UScalar.cast .Usize i23) 1#usize
            have hcst := u413 .Usize i23
            exact u401 (by
              show (core.num.Usize.saturating_sub (UScalar.cast .Usize i23) 1#usize).val < 512
              clear * - hsat hcst hi23;omega)
          · exact u401 (by decide:0 < 512)
        rintro ⟨cl2, cd2, cdc2⟩ hcl2
        have hcl2:cl2.val < 512 := hcl2
        iterate 2 refine u403 ?_
        refine u402 (Q := fun (x:alloc.vec.Vec W  ×  C 16384#usize  × 
              C 65536#usize  ×  C 32768#usize  ×  C 65536#usize  × 
              C 32768#usize  ×  Array Std.U64 8192#usize  ×  C 8192#usize  × 
              C 320#usize  ×  C 32#usize  ×  R  ×  R  ×  R) =>
            match x with
            | (_, g3, g4, _, g7, _, _, _, _, _, s1, cl1, i12) =>
              s1.val  ≤  i12.val  ∧  i'.val < i12.val  ∧  i12.val  ≤  n.val  ∧  cl1.val < 512  ∧ 
              EA.EA.u15 g3.val i12.val  ∧  EA.EA.u15 g4.val i12.val  ∧  EA.EA.u15 g7.val i12.val) ?_ ?_
        · apply u290
          · intro _ hnc
            have hnc':0 < nc3.val := (UScalar.lt_equiv _ _).mp hnc
            refine u405 (b := 1) rfl rfl hnc' ?_;intro i24 _
            refine u406 (b := 16) rfl (by decide) ?_;intro i25 hi25
            refine u408 (c := 16) rfl hi25 ?_;intro c0
            refine u412 (n := 9) (by decide) rfl ?_;intro i26 hi26
            refine u406 (b := 259) rfl (by decide) ?_;intro i27 hi27
            refine u405 (a := 258) rfl rfl (by clear * - hi27;omega) ?_;intro i28 _
            have hd0:(UScalar.cast .Usize i26).val < 8388608 := by
              have h9 := u216 c0
              have hc := u413 .Usize i26
              clear * - h9 hc hi26;omega
            refine u402 (u246 _ _ _ _ _ hilt hd0 hS hs') ?_;intro t ht
            have ht':t.val  ≤  i'.val := by clear * - ht;omega
            refine u405 rfl rfl ht' ?_;intro st hst
            refine u402 (u252 _ _ _ _ _ _ _ _ _ _
              (by clear * - hst ht hs';omega) (by clear * - hst hiM;omega)) ?_
            rintro ⟨plan2, lf2, df2, tb2⟩ _
            iterate 3 refine u403 ?_
            refine u402 (Q := fun _ => True) ?_ ?_
            · apply EA.EA.u188 <;> intro hpl
              · have hpl' := (UScalar.lt_equiv _ _).mp hpl
                have hlv:plan2.len.val = plan2.val.length := alloc.vec.Vec.len_val plan2
                have hnm := u400 n
                exact u415 (alloc.vec.Vec.push_spec _ _ (by clear * - hpl' hlv hnm;omega))
              · exact u401 trivial
            intro plan3 _
            refine u404 rfl rfl (by clear * - ht' hb4 hic hS;omega) ?_;intro i30 _
            refine u406 (b := 512) rfl (by decide) ?_;intro i31 hi31
            refine u408 (c := 512) rfl hi31 ?_;intro i32
            refine u406 (b := 32) rfl (by decide) ?_;intro ls hls'
            refine u404 (a := 257) rfl rfl (by have := u414;clear * - hls' this;omega) ?_;intro i34 hi34
            have hi34':i34.val < 320 := by clear * - hi34 hls';omega
            refine u408 (c := 320) rfl hi34' ?_;intro i35
            refine u409 (c := 320) rfl hi34' ?_;intro a9 _
            refine u402 (u239 _ _) ?_;intro i37 _
            refine u406 (b := 32) rfl (by decide) ?_;intro ds hds
            refine u408 (c := 32) rfl hds ?_;intro i38
            refine u409 (c := 32) rfl hds ?_;intro a10 _
            refine u404 rfl rfl (by clear * - hb4 hic hS;omega) ?_;intro «end» hend
            refine u402 (Q := fun (x:R) => x.val  ≤  «end».val  ∧  x.val  ≤  lim.val) ?_ ?_
            · apply EA.EA.u188 <;> intro h
              · have h':lim.val < «end».val := (UScalar.lt_equiv _ _).mp h
                exact u401 ⟨Nat.le_of_lt h', Nat.le_refl _⟩
              · have h':¬ (lim.val < «end».val) := (UScalar.lt_equiv _ _).not.mp h
                exact u401 ⟨Nat.le_refl _, (by clear * - h';omega:«end».val  ≤  lim.val)⟩
            rintro end1 ⟨he1, he2⟩
            have hE:i'.val  ≤  «end».val := by clear * - hend;omega
            refine u402 (u232 _ _ _ _ _ _ _ _ _ «end».val (EA.EA.u17 hL3 hE) (EA.EA.u17 hL4 hE)
              (EA.EA.u17 hL7 hE) (by clear * - he1;omega) (by clear * - he2 hlim hn hS;omega)) ?_
            rintro ⟨head33, head43, prev43, head73, prev73⟩ ⟨hr3, hr4, hr7⟩
            iterate 4 refine u403 ?_
            refine u402 (u248 _ _ (by clear * - hend hb4 hic hS;omega)) ?_;intro pa4 _
            exact u401 ⟨Nat.le_refl _, (by clear * - hend hb3;omega:i'.val < «end».val),
              (by clear * - hend hb4 hcap2;omega:«end».val  ≤  n.val), (by decide:0 < 512), hr3, hr4, hr7⟩
          · have h14:i'.val < i4.val := by clear * - hi4;omega
            refine u402 (u436 _ _ _ _ _ _ _ _ _ _ _ _ _ hnx hilt hS) ?_;intro pa4 _
            exact u401 ⟨(by clear * - hs' h14;omega:s'.val  ≤  i4.val), h14,
              (by clear * - hi4 hlt' hlim;omega:i4.val  ≤  n.val), hcl2,
              EA.EA.u17 hL3 (Nat.le_of_lt h14), EA.EA.u17 hL4 (Nat.le_of_lt h14), EA.EA.u17 hL7 (Nat.le_of_lt h14)⟩
        rintro ⟨v, a, a1, a2, a3, a4, a5, a6, a7, a8, i21, i22, i23⟩ ⟨hv1, hv2, hv3, hv4, hv5, hv6, hv7⟩
        iterate 12 refine u403 ?_
        exact u401 ⟨hv1, hv2, hv3, hv4, hv5, hv6, hv7⟩
    rintro ⟨plan1, rs1, head32, head42, prev42, head72, prev72, pa3, tb1, lf1, df1, s1, cands1, pc1, pn1, ppos1,
      cl1, cd1, cdc1, i12, anchor1, alen1⟩ ⟨hs1, hii, hin1, hcl1, hk3, hk4, hk7⟩
    iterate 21 refine u403 ?_
    have hs1:s1.val  ≤  i12.val := hs1
    have hii:i'.val < i12.val := hii
    have hin1:i12.val  ≤  n.val := hin1
    have hms:lim.val - i12.val < lim.val - i'.val := by clear * - hii hlt';omega
    have h12M:i12.val + 2147483648  ≤  Std.Usize.max := by clear * - hin1 hn hS;omega
    refine u405 rfl rfl hs1 ?_;intro i13 _
    refine u402 (Q := fun (x:alloc.vec.Vec W  ×  Array Std.U64 8192#usize  ×  C 8192#usize  × 
        C 320#usize  ×  C 32#usize  ×  R) => x.2.2.2.2.2.val  ≤  i12.val) ?_ ?_
    · apply EA.EA.u188 <;> intro _
      · refine u402 (u252 _ _ _ _ _ _ _ _ _ _ hs1 (by clear * - h12M;omega)) ?_
        rintro ⟨plan3, lf3, df3, tb3⟩ _
        iterate 3 refine u403 ?_
        refine u402 (u248 _ _ (by clear * - h12M;omega)) ?_;intro pa5 _
        exact u401 (Nat.le_refl _)
      · exact u401 hs1
    rintro ⟨plan2, pa4, tb2, lf2, df2, s2⟩ hs2
    have hs2:s2.val  ≤  i12.val := hs2
    iterate 5 refine u403 ?_
    apply EA.EA.u188 <;> intro _
    · refine u404 rfl rfl (by have hU := u212;clear * - h12M hU;omega) ?_;intro next_upd1 _
      refine u402 (u278 _ _ _ _ _ _ _ hls) ?_
      rintro ⟨lf3, df3, litc1, lc1, dcc1⟩ _
      iterate 4 refine u403 ?_
      refine u402 (u239 _ _) ?_;intro i14 _
      refine u406 (b := 32) rfl (by decide) ?_;intro i15 hi15
      refine u408 (c := 32) rfl hi15 ?_;intro cdc2
      exact u401 ⟨⟨hs2, hin1, hcl1, hk3, hk4, hk7⟩, hms⟩
    · exact u401 ⟨⟨hs2, hin1, hcl1, hk3, hk4, hk7⟩, hms⟩
  · exact ⟨hsi, hin, hcl, h3, h4, h7⟩
@[local step]
theorem u438 (input:I) (plan rs)
    (ct lazyn d4 d7 skip h3d flen tbmax lz2max dupmode fback d7l d7e nice:R)
    (h16:16  ≤  input.length) (hN:input.length + input.length  ≤  Std.Usize.max) :
    slot.Z251 input plan rs ct lazyn d4 d7 skip h3d flen tbmax lz2max dupmode fback d7l d7e nice
      ⦃ Y112P0! ⦄ := by
  have hl := Slice.len_val input
  have hM := u414
  have hk := u211
  rw [slot.Z251]
  refine u402 (u287 _ _ (EA.EA.u41 _ _ _ (Nat.zero_le _))) ?_
  rintro ⟨lsym1, dtab1⟩ hls
  have hls:EA.EA.u15 lsym1.val 28 := hls
  refine u403 ?_
  refine u402 (u429 _ _ _) ?_;intro nextl1 hnx
  refine u402 (u282 _ _ _ hN) ?_;rintro ⟨lf1, df1⟩ _
  refine u403 ?_
  refine u402 (u276 _ _ _ _ _ _ _ hls) ?_;rintro ⟨litc1, lc1, dcc1⟩ _
  iterate 2 refine u403 ?_
  refine u402 (u255 _ _) ?_;rintro ⟨lf2, df2⟩ _
  refine u403 ?_
  refine u402 (u255 _ _) ?_;rintro ⟨lf3, df3⟩ _
  refine u403 ?_
  refine u405 (b := 8) rfl rfl (by clear * - hl h16;omega) ?_;intro lim hlim
  refine u402 (U32.mul_spec (by
    have := U32.max_eq
    show 8 * slot.Z124.val  ≤  U32.max
    clear * - hk this;omega)) ?_
  intro i hi
  have hi:i.val = 8 * slot.Z124.val := hi
  refine u402 (U32.sub_spec (by show i.val  ≤  64;clear * - hi hk;omega)) ?_;intro sh7 _
  refine u402 (u248 _ _ (by show 0 + 259  ≤  Std.Usize.max;clear * - hM;omega)) ?_;intro pa1 _
  refine u402 (u437 (hn := hl) (hlim := hlim) (hN := hN) (hls := hls) (hnx := hnx)
    (hsi := Nat.le_refl _) (hin := Nat.zero_le _) (hcl := by decide)
    (h3 := EA.EA.u41 _ _ _ (Nat.le_refl _)) (h4 := EA.EA.u41 _ _ _ (Nat.le_refl _))
    (h7 := EA.EA.u41 _ _ _ (Nat.le_refl _)) ..) ?_
  rintro ⟨plan1, rs1, pa2, tb1, lf4, df4, s, i1⟩ _
  iterate 7 refine u403 ?_
  apply EA.EA.u188 <;> intro _
  · apply EA.EA.u188 <;> intro hin
    · have hin':i1.val  ≤  input.len.val := (UScalar.le_equiv _ _).mp hin
      refine u402 (Q := fun (e:R) => e.val  ≤  input.len.val) ?_ ?_
      · apply EA.EA.u188 <;> intro _
        · exact u401 hin'
        · exact u401 (by clear * - hlim;omega:lim.val  ≤  input.len.val)
      intro e he
      apply EA.EA.u188 <;> intro hes
      · have hes':s.val < e.val := (UScalar.lt_equiv _ _).mp hes
        refine u402 (u252 _ _ _ _ _ _ _ _ _ _ (Nat.le_of_lt hes')
          (by clear * - he hl hN h16;omega)) ?_
        rintro ⟨plan2, x1, x2, x3⟩ _
        iterate 3 refine u403 ?_
        exact u401 trivial
      · exact u401 trivial
    · exact u401 trivial
  · exact u401 trivial
@[local step]
theorem u439 (input:I) (out:U) (k) (n:R) (plan rs lsym dtab)
    (passes pass:R) :
    slot.Z253_loop input out k n plan rs lsym dtab passes pass ⦃ fun r => r.2.length = out.length ⦄ := by
  rw [slot.Z253_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, pass') => passes.val - pass'.val)
    (inv := fun (out', _, _) => out'.length = out.length)
  · rintro ⟨out', plan', pass'⟩ hinv'
    simp only [slot.Z253_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · rfl
@[local step]
theorem u440 (input:I) (out:U) (k) :
    slot.Z253 input out k ⦃ fun r => r.2.length = out.length ⦄ := by
  have z8:EA.EA.u15 (Array.repeat 512#usize 0#u8).val 28 := EA.EA.u41 _ _ _ (by simp)
  rw [slot.Z253]
  step*
  repeat' (split <;> step*)
  all_goals first
    | scalar_tac
    | (have hw := u217 input.len (by first | (rw [← i2_post];scalar_tac) | (rw [← i2_post1];scalar_tac))
       simpa using hw)
@[local step]
theorem u441 (input:I) (out:U) (dk:R) :
    slot.Z252 input out dk ⦃ fun r => r.2.length = out.length ⦄ := by
  rw [slot.Z252]
  step*
open LZ77 (Matches)
def u442 (input:I) (p:Nat):Nat :=
  ((((((((input.val[p]!).val * 256 + (input.val[p + 1]!).val) * 256
    + (input.val[p + 2]!).val) * 256 + (input.val[p + 3]!).val) * 256
    + (input.val[p + 4]!).val) * 256 + (input.val[p + 5]!).val) * 256
    + (input.val[p + 6]!).val) * 256 + (input.val[p + 7]!).val)
theorem u443 (x:Std.U8):x.val < 256 := by scalar_tac
theorem u444 (input:I) (p k:Nat) (hk:k < 8) :
    (input.val[p + k]!).val = u442 input p / 256 ^ (7 - k) % 256 := by
  have := u443 (input.val[p]!);have := u443 (input.val[p+1]!)
  have := u443 (input.val[p+2]!);have := u443 (input.val[p+3]!)
  have := u443 (input.val[p+4]!);have := u443 (input.val[p+5]!)
  have := u443 (input.val[p+6]!);have := u443 (input.val[p+7]!)
  simp only [u442]
  rcases (show k = 0  ∨  k = 1  ∨  k = 2  ∨  k = 3  ∨  k = 4  ∨  k = 5  ∨  k = 6  ∨  k = 7 by omega) with
    rfl | rfl | rfl | rfl | rfl | rfl | rfl | rfl <;> simp only [Nat.add_zero, Nat.pow_zero,
    Nat.pow_succ, Nat.one_mul, Nat.sub_self, Nat.reduceSub] <;> omega
theorem u445 (input:I) (a b d:Nat) (hd:d  ≤  8)
    (h:u442 input a / 2 ^ (64 - 8 * d) = u442 input b / 2 ^ (64 - 8 * d)) :
    ∀ k, k < d  →  input.val[b + k]! = input.val[a + k]! := by
  intro k hk
  have e:(256:Nat) ^ (7 - k) = 2 ^ (64 - 8 * d) * 2 ^ (8 * (d - 1 - k)) := by
    rw [← pow_add, show (256:Nat) = 2 ^ 8 by norm_num, ← pow_mul]
    congr 1;omega
  have key:u442 input a / 256 ^ (7 - k) = u442 input b / 256 ^ (7 - k) := by
    rw [e, ← Nat.div_div_eq_div_mul, ← Nat.div_div_eq_div_mul, h]
  have ha := u444 input a k (by omega)
  have hb := u444 input b k (by omega)
  rw [key] at ha
  scalar_tac
theorem Matches.u446 {input:I} {a b l d:Nat} (h:Matches input a b l)
    (hd:d  ≤  8)
    (hw:u442 input (a + l) / 2 ^ (64 - 8 * d) = u442 input (b + l) / 2 ^ (64 - 8 * d)) :
    Matches input a b (l + d) := by
  intro k hk
  by_cases hkl:k < l
  · exact h k hkl
  · have := u445 input (a + l) (b + l) d hd hw (k - l) (by omega)
    rw [show b + l + (k - l) = b + k by omega, show a + l + (k - l) = a + k by omega] at this
    exact this
theorem Matches.u447 {input:I} {a b l l':Nat} {pa pb d:R}
    {x y:Std.U64} (h:Matches input a b l) (hpa:pa.val = a + l) (hpb:pb.val = b + l)
    (hx:x.val = u442 input pa.val) (hy:y.val = u442 input pb.val)
    (hd8:d.val  ≤  8) (hdiv:x.val / 2 ^ (64 - 8 * d.val) = y.val / 2 ^ (64 - 8 * d.val))
    (hl':l' = l + d.val):Matches input a b l' := by
  subst hl'
  rw [hx, hy, hpa, hpb] at hdiv
  exact Matches.u446 h hd8 hdiv
theorem Matches.u448 {input:I} {a b l l':Nat} {pa pb:R}
    {x y:Std.U64} (h:Matches input a b l) (hpa:pa.val = a + l) (hpb:pb.val = b + l)
    (hx:x.val = u442 input pa.val) (hy:y.val = u442 input pb.val)
    (hxy:¬(x != y) = true) (hl':l' = l + 8):Matches input a b l' := by
  have hxy':x.val = y.val := by simpa using hxy
  subst hl'
  apply Matches.u446 h (le_refl 8)
  rw [← hpa, ← hpb, ← hx, ← hy, hxy']
theorem Matches.u449 {input:I} {a b l l':Nat} {pa pb:R}
    {x y:Std.U8} (h:Matches input a b l) (hpa:pa.val = a + l) (hpb:pb.val = b + l)
    (hpa':pa.val < input.val.length) (hpb':pb.val < input.val.length)
    (hx:x = input.val[pa.val]) (hy:y = input.val[pb.val]) (hxy:x = y)
    (hl':l' = l + 1):Matches input a b l' := by
  subst hl' hxy
  apply LZ77.Matches.succ h
  rw [← hpa, ← hpb, getElem!_pos input.val pa.val hpa', getElem!_pos input.val pb.val hpb',
    ← hx, ← hy]
theorem u450 {a b:Nat} (h:a ^^^ b = 0):a = b := by
  have:a ^^^ (a ^^^ b) = b := by rw [← Nat.xor_assoc, Nat.xor_self, Nat.zero_xor]
  rw [h, Nat.xor_zero] at this;exact this
theorem u451 {x y m:Nat} (hz:x ^^^ y < 2 ^ m):x / 2 ^ m = y / 2 ^ m := by
  have h:(x ^^^ y) >>> m = 0 := by rw [Nat.shiftRight_eq_div_pow];exact Nat.div_eq_of_lt hz
  rw [Nat.shiftRight_xor_distrib] at h
  have := u450 h
  simpa [Nat.shiftRight_eq_div_pow] using this
theorem u452 (z:BitVec 64) :
    z.toNat < 2 ^ (64 - 8 * (BitVec.leadingZeros z / 8)) := by
  unfold BitVec.leadingZeros
  split
  case isTrue h => subst h;simp
  case isFalse h =>
    have hz:z.toNat ≠ 0 := by
      intro h0;apply h;exact BitVec.eq_of_toNat_eq (by simpa using h0)
    have hlog:Nat.log 2 z.toNat < 64 := Nat.log_lt_of_lt_pow hz z.isLt
    have h1:z.toNat < 2 ^ (Nat.log 2 z.toNat).succ := Nat.lt_pow_succ_log_self (by norm_num) _
    refine lt_of_lt_of_le h1 (Nat.pow_le_pow_right (by norm_num) ?_)
    omega
@[local step]
theorem u453 (input:I) (p:R) (hp:p.val + 8  ≤  input.length) :
    slot.Z290 input p ⦃ fun v => v.val = u442 input p.val ⦄ := by
  have hlift := @EA.EA.u0
  rw [slot.Z290]
  step*
  simp only [← getElem!_pos] at *
  simp only [u442]
  simp_all only [U8.cast_U64_val_eq]
@[local step]
theorem u454 (x y:Std.U64) :
    slot.Z276 x y ⦃ fun d => d.val  ≤  8  ∧ 
      x.val / 2 ^ (64 - 8 * d.val) = y.val / 2 ^ (64 - 8 * d.val) ⦄ := by
  have hlift := @EA.EA.u0
  rw [slot.Z276]
  step*
  have hle:BitVec.leadingZeros z.bv  ≤  64 := by unfold BitVec.leadingZeros;split <;> omega
  have hlz:lz.val = BitVec.leadingZeros z.bv := by
    rw [lz_post]
    simp only [core.num.U64.leading_zeros, UScalar.val, UScalarTy.U32_numBits_eq,
      BitVec.natCast_eq_ofNat, BitVec.toNat_ofNat, Nat.reducePow]
    omega
  have hd:(UScalar.cast UScalarTy.Usize bytes).val = BitVec.leadingZeros z.bv / 8 := by
    simp only [U32.cast_Usize_val_eq, bytes_post, hlz]
  have hz:z.bv.toNat = x.val ^^^ y.val := by
    have:z.val = z.bv.toNat := rfl
    rw [← this, z_post, UScalar.val_xor]
  refine ⟨by rw [hd];omega, ?_⟩
  rw [hd]
  apply u451
  rw [← hz]
  exact u452 z.bv
@[local step]
theorem u455 (input:I) (a b cap l0:R)
    (ha:a.val + cap.val  ≤  input.length) (hb:b.val + cap.val  ≤  input.length)
    (hl0:l0.val  ≤  cap.val) (h0:Matches input a.val b.val l0.val) :
    slot.Z293_loop0_loop0 input a b cap l0 ⦃ Y112P6! ⦄ := by
  rw [slot.Z293_loop0_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun l => cap.val - l.val)
    (inv := fun l => l.val  ≤  cap.val  ∧  Matches input a.val b.val l.val)
  · rintro l ⟨hle, hm⟩
    simp only [slot.Z293_loop0_loop0.body]
    have hmax:input.length  ≤  Std.Usize.max := Std.Slice.length_ineq input
    step*
    refine ⟨by scalar_tac, ?_, by scalar_tac⟩
    exact Matches.u449 hm (by assumption) (by assumption) (by scalar_tac) (by scalar_tac)
      (by assumption) (by assumption) (by assumption) (by scalar_tac)
  · exact ⟨hl0, h0⟩
@[local step]
theorem u456 (input:I) (a b cap l0:R)
    (ha:a.val + cap.val  ≤  input.length) (hb:b.val + cap.val  ≤  input.length)
    (hl0:l0.val  ≤  cap.val) (h0:Matches input a.val b.val l0.val) :
    slot.Z293_loop0 input a b cap l0 ⦃ Y112P6! ⦄ := by
  rw [slot.Z293_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun l => cap.val - l.val)
    (inv := fun l => l.val  ≤  cap.val  ∧  Matches input a.val b.val l.val)
  · rintro l ⟨hle, hm⟩
    simp only [slot.Z293_loop0.body]
    have hmax:input.length  ≤  Std.Usize.max := Std.Slice.length_ineq input
    step*
    · -- the words differ: `first_diff` bytes more, and the loop is over
      refine ⟨by scalar_tac, ?_⟩
      exact Matches.u447 hm (by assumption) (by assumption) (by assumption) (by assumption)
        (by assumption) (by assumption) (by scalar_tac)
    · -- equal words: eight bytes more
      refine ⟨by scalar_tac, ?_, by scalar_tac⟩
      exact Matches.u448 hm (by assumption) (by assumption) (by assumption) (by assumption)
        (by assumption) (by scalar_tac)
  · exact ⟨hl0, h0⟩
@[local step]
theorem u457 (input:I) (a b cap:R)
    (ha:a.val + cap.val  ≤  input.length) (hb:b.val + cap.val  ≤  input.length) :
    slot.Z293 input a b cap ⦃ Y112P6! ⦄ :=
  u456 input a b cap 0#usize ha hb (by simp) (LZ77.Matches.zero input a.val b.val)
@[local step]
theorem u458 (input:I) (p len dist:R) :
    slot.Z223 input p len dist ⦃ fun valid => valid = true  → 
      3  ≤  len.val  ∧  len.val  ≤  258  ∧  1  ≤  dist.val  ∧  dist.val  ≤  32768  ∧  dist.val  ≤  p.val  ∧ 
      p.val + len.val  ≤  input.length  ∧  Matches input (p.val - dist.val) p.val len.val ⦄ := Y127U1! slot.Z223
@[local step]
theorem u459 (input:I) (plan out0:U)
    (n ntok0 k0 owed0 p0:R) (hn:n.val = input.length) (hout:input.length  ≤  out0.length)
    (hp0:p0.val  ≤  n.val) (hntok0:ntok0.val  ≤  p0.val) (hk0:k0.val  ≤  p0.val)
    (hdec0:LZ77.decode (toks out0 ntok0.val) = some ((bytes input).take p0.val)) :
    slot.Z271_loop input plan out0 n ntok0 k0 owed0 p0 ⦃ Y112P2! ⦄ := by
  have hlift := @EA.EA.u0
  rw [slot.Z271_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, p) => n.val - p.val)
    (inv := fun (out, ntok, k, _, p) => p.val  ≤  n.val  ∧  ntok.val  ≤  p.val  ∧  k.val  ≤  p.val  ∧ 
      out.length = out0.length  ∧ 
      LZ77.decode (toks out ntok.val) = some ((bytes input).take p.val))
  · rintro ⟨out, ntok, k, owed, p⟩ ⟨hp, hnt, hk, hlen, hde⟩
    simp only [slot.Z271_loop.body]
    have hmax:input.length  ≤  Std.Usize.max := Std.Slice.length_ineq input
    split
    case isTrue hlt =>
      have hntok_lt:ntok.val < out.length := by scalar_tac
      step*
      · -- an owed literal: `input[p]`, advance 1
        have hlit:i1.val = (bytes input)[p.val]! := by
          rw [bytes_getElem! input p.val (by scalar_tac)]
          scalar_tac
        refine ⟨by scalar_tac, by scalar_tac, by scalar_tac, by rw [s_post];simpa using hlen, ?_,
          by scalar_tac⟩
        rw [s_post, show ntok1.val = ntok.val + 1 by scalar_tac,
          show p1.val = p.val + 1 by scalar_tac]
        exact emit_lit input out ntok p.val i1 hde (by scalar_tac) hntok_lt hlit
      · -- `check` accepted the planned `(len, dist)`: write the match token, advance `len`
        obtain ⟨h3, h258, hd1, hd32k, hdp, hend, hm⟩ := valid_post (by assumption)
        have htok:tok.val = LZ77.mkMatch dist.val len.val := by
          simp only [LZ77.mkMatch, LZ77.MATCH_BASE]
          scalar_tac
        refine ⟨by scalar_tac, by scalar_tac, by scalar_tac, by rw [s_post];simpa using hlen, ?_,
          by scalar_tac⟩
        rw [s_post, show ntok1.val = ntok.val + 1 by scalar_tac,
          show p1.val = p.val + len.val by scalar_tac]
        exact emit_match input out ntok p.val dist.val len.val tok hde hntok_lt hd1 hdp hd32k
          h3 h258 hend hm htok
      all_goals
        have hlit:i3.val = (bytes input)[p.val]! := by
          rw [bytes_getElem! input p.val (by scalar_tac)]
          scalar_tac
        subst index_mut_back
        refine ⟨by scalar_tac, by scalar_tac, by scalar_tac, by simpa using hlen, ?_, by scalar_tac⟩
        rw [show ntok1.val = ntok.val + 1 by scalar_tac, show p1.val = p.val + 1 by scalar_tac]
        exact emit_lit input out ntok p.val i3 hde (by scalar_tac) hntok_lt hlit
    case isFalse hge =>
      have hpn:p.val = input.length := by scalar_tac
      refine ⟨by scalar_tac, hlen, ?_⟩
      rw [hde, hpn]
      simp
  · exact ⟨hp0, hntok0, hk0, rfl, hdec0⟩
@[local step]
theorem u460 (input:I) (plan out:U)
    (hout:input.length  ≤  out.length) :
    slot.Z271 input plan out ⦃ Y112P3! ⦄ := by
  rw [slot.Z271]
  exact u459 input plan out (Std.Slice.len input) 0#usize 0#usize 0#usize 0#usize
    (by simp) hout (by simp) (by simp) (by simp) (by simp [toks, LZ77.decode])
theorem u461 (input:I) (plan out0:U)
    (n ntok0 p0:R) (hn:n.val = input.length) (hout:input.length  ≤  out0.length)
    (hp0:p0.val  ≤  n.val) (hntok0:ntok0.val  ≤  p0.val)
    (hdec0:LZ77.decode (toks out0 ntok0.val) = some ((bytes input).take p0.val)) :
    slot.Z272_loop input plan out0 n ntok0 p0 ⦃ Y112P2! ⦄ := Y127U2! slot.Z272_loop slot.Z272_loop.body
@[local step]
theorem u462 (input:I) (plan out:U)
    (hout:input.length  ≤  out.length) :
    slot.Z272 input plan out ⦃ Y112P3! ⦄ := by
  rw [slot.Z272]
  exact u461 input plan out (Std.Slice.len input) 0#usize 0#usize (by simp) hout
    (by simp) (by simp) (by simp [toks, LZ77.decode])


@[local scalar_tac core.num.Usize.saturating_add x y]
theorem u463 (x y:R) :
    (core.num.Usize.saturating_add x y).val = min Std.Usize.max (x.val + y.val) := EA.EA.u38 x y






@[local step]
theorem u464 (pe:R) (cost) (cl z:R) (hpe:pe.val  ≤  2 ^ 31) (hcl:cl.val = cost.length) :
    slot.Z184_loop0 pe cost cl z ⦃ fun r => r.length = cost.length ⦄ := by
  rw [slot.Z184_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, z_) => cl.val - z_.val)
    (inv := fun (cost_, _) => cost_.length = cost.length)
  · rintro ⟨cost_, z_⟩ hinv
    simp only [slot.Z184_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · rfl
set_option hygiene false in
local notation "Y127U16!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun (mbest_, at0_, l_) => stop.val + 1 - at0_.val)
    (inv := fun _ => True)
  · rintro ⟨mbest_, at0_, l_⟩ _
    simp only [q1__]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · trivial)
@[local step]
theorem u465 (lc) (cost:alloc.vec.Vec W) (stop base mbest at0 l) (hstop:stop.val < cost.length) :
    slot.Z184_loop1_loop0_loop0 lc cost stop base mbest at0 l ⦃ Y112P0! ⦄ := Y127U16! slot.Z184_loop1_loop0_loop0 slot.Z184_loop1_loop0_loop0.body
@[local step]
theorem u466 (lc) (cost:alloc.vec.Vec W) (stop base mbest at0 l) (hstop:stop.val < cost.length) :
    slot.Z184_loop1_loop0_loop1 lc cost stop base mbest at0 l ⦃ Y112P0! ⦄ := Y127U16! slot.Z184_loop1_loop0_loop1 slot.Z184_loop1_loop0_loop1.body
@[local step]
theorem u467 (mb lc dc) (cost:alloc.vec.Vec W) (cl i:R) (bias best bd) (prev pd:R) (j top:R)
    (hcl:cl.val = cost.length) (hi:i.val  ≤  2 ^ 31) (htop:top.val  ≤  mb.length)
    (hprev:prev.val  ≤  i.val + 258) (hpd:pd.val  ≤  32768) (hbd:bd.val  ≤  32767) :
    slot.Z184_loop1_loop0 mb lc dc cost cl i bias best bd prev pd j top ⦃ Y112P7! ⦄ := by
  rw [slot.Z184_loop1_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, j_) => top.val - j_.val)
    (inv := fun (_, bd_, prev_, pd_, _) => prev.val  ≤  prev_.val  ∧  prev_.val  ≤  i.val + 258  ∧ 
      pd_.val  ≤  32768  ∧  bd_.val  ≤  32767)
  · rintro ⟨best_, bd_, prev_, pd_, j_⟩ ⟨hp0, hp1, hpd_, hbd_⟩
    simp only [slot.Z184_loop1_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · exact ⟨le_refl _, hprev, hpd, hbd⟩
@[local step]
theorem u468 (lc) (cost:alloc.vec.Vec W) (stop base mbest at0 l) (hstop:stop.val < cost.length) :
    slot.Z184_loop1_loop1 lc cost stop base mbest at0 l ⦃ Y112P0! ⦄ := Y127U16! slot.Z184_loop1_loop1 slot.Z184_loop1_loop1.body
set_option maxHeartbeats 4000000 in
@[local step]
theorem u469 (s:I) (mp mb:alloc.vec.Vec W) (p0 lit lc dc) (cost ch:alloc.vec.Vec W)
    (cl i e xl xd:R)
    (hcl:cl.val = cost.length) (hi:i.val < cl.val) (hmp:i.val < mp.length) (hs:i.val  ≤  s.length)
    (hch:i.val  ≤  ch.length) (hi31:i.val  ≤  2 ^ 31) (hxl:xl.val  ≤  258) (hxd:xd.val  ≤  32768) :
    slot.Z184_loop1 s mp mb p0 lit lc dc cost ch cl i e xl xd ⦃ Y112P0! ⦄ := by
  rw [slot.Z184_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, i_, _, _, _) => i_.val)
    (inv := fun ((cost_:alloc.vec.Vec W), (ch_:alloc.vec.Vec W), (i_:R), _,
        (xl_:R), (xd_:R)) =>
      cost_.length = cl.val  ∧  ch_.length = ch.length  ∧  i_.val  ≤  i.val  ∧  xl_.val  ≤  258  ∧  xd_.val  ≤  32768)
  · rintro ⟨cost_, ch_, i_, e_, xl_, xd_⟩ ⟨hc_, hch_, hi_, hxl_, hxd_⟩
    simp only [slot.Z184_loop1.body]
    step*
    apply WP.spec_bind (Pₘ := fun (top:R) => top.val  ≤  mb.length)
    · split <;> step* <;> (subst_vars;scalar_tac (simpAllMaxSteps := 0))
    rintro top htop
    step*
    apply WP.spec_bind (Pₘ := fun (el:R) => el.val  ≤  258)
    · split <;> step* <;> (subst_vars;scalar_tac (simpAllMaxSteps := 0))
    rintro el hel
    step*
    all_goals
      try (
        apply WP.spec_bind (Pₘ := fun (x:W  ×  W) => x.2.val  ≤  32767)
        · split <;> step* <;> (subst_vars;scalar_tac (simpAllMaxSteps := 0))
        rintro ⟨best2, bd1⟩ hbd1
        step*)
    all_goals
      apply WP.spec_bind (Pₘ := fun (x:alloc.vec.Vec W  ×  W) => x.1.length = cost_.length)
      · split <;> step* <;> (subst_vars;scalar_tac (simpAllMaxSteps := 0))
      rintro ⟨cost1, i23⟩ hc1
      step*
      (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · exact ⟨hcl.symm, rfl, le_refl _, hxl, hxd⟩
set_option hygiene false in
local notation "Y127U17!" q0__:max => (by
  rw [q0__]
  step*
  repeat' (split <;> step*)
  all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0)))
@[local step]
theorem u470 (s:I) (mp mb) (p0 pe:R) (lit lc dc) (cost ch)
    (hpe:pe.val  ≤  2 ^ 31) :
    slot.Z184 s mp mb p0 pe lit lc dc cost ch ⦃ Y112P0! ⦄ := Y127U17! slot.Z184
@[local step]
theorem u471 (lf zf b) :
    slot.Z187_loop0_loop0 lf zf b ⦃ Y112P0! ⦄ := by
  rw [slot.Z187_loop0_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (zf_, b_) => 512 - b_.val)
    (inv := fun _ => True)
  · rintro ⟨zf_, b_⟩ _
    simp only [slot.Z187_loop0_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · trivial
@[local step]
theorem u472 (df zd b) :
    slot.Z187_loop0_loop1 df zd b ⦃ Y112P0! ⦄ := by
  rw [slot.Z187_loop0_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (zd_, b_) => 32 - b_.val)
    (inv := fun _ => True)
  · rintro ⟨zd_, b_⟩ _
    simp only [slot.Z187_loop0_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · trivial
@[local step]
theorem u473 (s:I) (mp mb) (pe:R) (lit lc dc cost ch lf df zf zd) (sb st a:R)
    (hpe:pe.val  ≤  2 ^ 30) (hps:pe.val  ≤  s.length) (hsb:sb.val  ≤  a.val) (hst:st.val  ≤  a.val)
    (ha:a.val  ≤  pe.val + slot.Z5.val * slot.Z4.val) :
    slot.Z187_loop0 s mp mb pe lit lc dc cost ch lf df zf zd sb st a ⦃ Y112P0! ⦄ := by
  have hseg := EA.EA.u34
  rw [slot.Z187_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, _, _, _, _, a_) => pe.val - a_.val)
    (inv := fun (_, _, _, _, _, _, sb_, st_, a_) => sb_.val  ≤  a_.val  ∧  st_.val  ≤  a_.val  ∧ 
      a_.val  ≤  pe.val + slot.Z5.val * slot.Z4.val)
  · rintro ⟨cost_, ch_, lf_, df_, zf_, zd_, sb_, st_, a_⟩ ⟨hsb_, hst_, ha_⟩
    simp only [slot.Z187_loop0.body]
    step*
    cases ‹R  ×  R›
    step*
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · exact ⟨hsb, hst, ha⟩
@[local step]
theorem u474 (lf zf b) :
    slot.Z187_loop1 lf zf b ⦃ Y112P0! ⦄ := by
  rw [slot.Z187_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (lf_, b_) => 512 - b_.val)
    (inv := fun _ => True)
  · rintro ⟨lf_, b_⟩ _
    simp only [slot.Z187_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · trivial
@[local step]
theorem u475 (df zd b) :
    slot.Z187_loop2 df zd b ⦃ Y112P0! ⦄ := by
  rw [slot.Z187_loop2]
  apply Std.loop.spec_decr_nat
    (measure := fun (df_, b_) => 32 - b_.val)
    (inv := fun _ => True)
  · rintro ⟨df_, b_⟩ _
    simp only [slot.Z187_loop2.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · trivial
@[local step]
theorem u476 (s:I) (mp mb) (p0 pe:R) (lit lc dc cost ch lf df)
    (hpe:pe.val  ≤  2 ^ 30) (hps:pe.val  ≤  s.length) (hp0:p0.val  ≤  pe.val) :
    slot.Z187 s mp mb p0 pe lit lc dc cost ch lf df ⦃ Y112P0! ⦄ := by
  have hseg := EA.EA.u34
  rw [slot.Z187]
  step*
  repeat' (split <;> step*)
  all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))




























@[local step]
theorem u477 (lf0 lf z) :
    slot.Z188_loop0 lf0 lf z ⦃ Y112P0! ⦄ := by
  rw [slot.Z188_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (lf_, z_) => 286 - z_.val)
    (inv := fun _ => True)
  · rintro ⟨lf_, z_⟩ _
    simp only [slot.Z188_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · trivial
@[local step]
theorem u478 (df dd i) :
    slot.Z188_loop1 df dd i ⦃ Y112P0! ⦄ := by
  rw [slot.Z188_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (dd_, i_) => 30 - i_.val)
    (inv := fun _ => True)
  · rintro ⟨dd_, i_⟩ _
    simp only [slot.Z188_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · trivial
@[local step]
theorem u479 (lf i tl) :
    slot.Z188_loop2 lf i tl ⦃ Y112P0! ⦄ := by
  rw [slot.Z188_loop2]
  apply Std.loop.spec_decr_nat
    (measure := fun (i_, tl_) => 286 - i_.val)
    (inv := fun _ => True)
  · rintro ⟨i_, tl_⟩ _
    simp only [slot.Z188_loop2.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · trivial
@[local step]
theorem u480 (df i td) :
    slot.Z188_loop3 df i td ⦃ Y112P0! ⦄ := by
  rw [slot.Z188_loop3]
  apply Std.loop.spec_decr_nat
    (measure := fun (i_, td_) => 30 - i_.val)
    (inv := fun _ => True)
  · rintro ⟨i_, td_⟩ _
    simp only [slot.Z188_loop3.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · trivial
@[local step]
theorem u481 (lit) (hl:C 512#usize) (i) (ul:W) (hhl:EA.EA.u15 hl.val 15) :
    slot.Z188_loop4 lit hl i ul ⦃ Y112P0! ⦄ := by
  rw [slot.Z188_loop4]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, i_) => 256 - i_.val)
    (inv := fun _ => True)
  · rintro ⟨lit_, i_⟩ _
    simp only [slot.Z188_loop4.body]
    step*
    repeat' (split <;> step*)
    all_goals try (have := EA.EA.u16 hhl i_.val (by (subst_vars;scalar_tac (simpAllMaxSteps := 0))))
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · trivial
@[local step]
theorem u482 (lc) (hl:C 512#usize) (i) (ul:W) (hhl:EA.EA.u15 hl.val 15) (hul:ul.val  ≤  1152) :
    slot.Z188_loop5 lc hl i ul ⦃ Y112P0! ⦄ := by
  rw [slot.Z188_loop5]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, i_) => 259 - i_.val)
    (inv := fun _ => True)
  · rintro ⟨lc_, i_⟩ _
    simp only [slot.Z188_loop5.body]
    step*
    repeat' (split <;> step*)
    all_goals try (have := EA.EA.u16 hhl i2.val (by (subst_vars;scalar_tac (simpAllMaxSteps := 0))))
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · trivial
@[local step]
theorem u483 (dc) (i:R) (hd:C 512#usize) (ud:W) (hhd:EA.EA.u15 hd.val 15) (hud:ud.val  ≤  1152) :
    slot.Z188_loop6 dc i hd ud ⦃ Y112P0! ⦄ := by
  rw [slot.Z188_loop6]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, i_) => 30 - i_.val)
    (inv := fun _ => True)
  · rintro ⟨dc_, i_⟩ _
    simp only [slot.Z188_loop6.body]
    step*
    repeat' (split <;> step*)
    all_goals try (have := EA.EA.u16 hhd i_.val (by (subst_vars;scalar_tac (simpAllMaxSteps := 0))))
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · trivial
@[local step]
theorem u484 (lf0 df lit lc dc) :
    slot.Z188 lf0 df lit lc dc ⦃ Y112P0! ⦄ := by
  rw [slot.Z188]
  step*
  all_goals exact EA.EA.u41 _ _ _ (by simp)






@[local step]
theorem u485 (s:I) (kid) (pos depth oldest:R) (mb) (cur best lo_at hi_at lo_len hi_len steps:R)
    (hpos:pos.val + 266  ≤  s.length) (hn26:s.length < 67108864) (hlo:lo_len.val  ≤  258) (hhi:hi_len.val  ≤  258) (hbest:2  ≤  best.val) :
    slot.Z189_loop s kid pos depth mb oldest cur best lo_at hi_at lo_len hi_len steps ⦃ Y112P0! ⦄ := by
  rw [slot.Z189_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, _, _, _, _, steps_) => depth.val - steps_.val)
    (inv := fun (_, _, _, best_, _, _, lo_len_, hi_len_, _) => lo_len_.val  ≤  258  ∧  hi_len_.val  ≤  258  ∧  2  ≤  best_.val)
  · rintro ⟨kid_, mb_, cur_, best_, lo_at_, hi_at_, lo_len_, hi_len_, steps_⟩ ⟨hlo_, hhi_, hbest_⟩
    simp only [slot.Z189_loop.body, EA.EA.u37]
    step*
    · split <;> omega
    apply WP.spec_bind (Pₘ := fun (x:alloc.vec.Vec W  ×  R) => 2  ≤  x.2.val)
    · split
      · step*
        repeat' (split <;> step*)
        all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
      · step*
    rintro ⟨mb1, best1⟩ hb1
    step*
    apply WP.spec_bind (Pₘ := fun (x:Std.Array W 65536#usize  ×  R  ×  R  ×  R  × 
        R  ×  R) => x.2.2.2.2.1.val  ≤  258  ∧  x.2.2.2.2.2.val  ≤  258)
    · repeat' (split <;> step*)
      all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
    rintro ⟨kid1, cur1, lo_at1, hi_at1, lo_len2, hi_len1⟩ ⟨hl2, hh1⟩
    step*
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · exact ⟨hlo, hhi, hbest⟩
@[local step]
theorem u486 (s:I) (head kid h3 rct) (pos:R) (pre depth mb) (hpos:pos.val + 266  ≤  s.length)
    (hn26:s.length < 67108864) :
    slot.Z189 s head kid h3 rct pos pre depth mb ⦃ Y112P0! ⦄ := by
  obtain ⟨q, t, h, c3, cr, cur⟩ := pre
  rw [slot.Z189]
  apply WP.spec_bind (Pₘ := fun (_:R) => True)
  · split
    all_goals step*
  rintro oldest -
  step*
  apply WP.spec_bind (Pₘ := fun (x:alloc.vec.Vec W  ×  R) => 2  ≤  x.2.val)
  · repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  rintro ⟨mb1, best⟩ hb
  step*
  apply WP.spec_bind (Pₘ := fun (x:alloc.vec.Vec W  ×  R) => 2  ≤  x.2.val)
  · repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  rintro ⟨mb2, best1⟩ hb1
  step*
  repeat' (split <;> step*)
  all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
set_option maxHeartbeats 4000000 in
@[local step]
theorem u487 (i:W) (s:I) (mp:alloc.vec.Vec W) (mb depth) (skip n:R) (head kid h3 rct) (i1 cl cd:R) (nq nt nh n3 nr nc)
    (hn:n.val = s.length) (hn26:s.length < 67108864) (hi:i.val < 32) (hskip:3  ≤  skip.val)
    (hmp:mp.length  ≤  i1.val + 1) (hcd:1  ≤  cd.val) :
    slot.Z186_loop i s mp mb depth skip n head kid h3 rct i1 cl cd nq nt nh n3 nr nc ⦃ Y112P0! ⦄ := by
  rw [slot.Z186_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, _, _, i1_, _, _, _, _, _, _, _, _) => n.val - i1_.val)
    (inv := fun ((mp_:alloc.vec.Vec W), _, _, _, _, _, (i1_:R), _, (cd_:R), _, _, _, _, _, _) =>
      mp_.length  ≤  i1_.val + 1  ∧  1  ≤  cd_.val)
  · rintro ⟨mp_, mb_, head_, kid_, h3_, rct_, i1_, cl_, cd_, nq_, nt_, nh_, n3_, nr_, nc_⟩ ⟨hmp_, hcd_⟩
    unfold slot.Z186_loop.body
    simp only [EA.EA.u37, EA.EA.u40]
    step*
    apply WP.spec_bind (Pₘ := fun (x:alloc.vec.Vec W  ×  Std.Array W 65536#usize  ×  Std.Array W 65536#usize  × 
        Std.Array W 32768#usize  ×  Std.Array W 65536#usize  ×  R  ×  R  ×  Std.U64  ×  R  × 
        R  ×  R  ×  R  ×  R) => 1  ≤  x.2.2.2.2.2.2.1.val)
    · split
      · step*
        · -- a searched or skipped position (at least 266 bytes left)
          apply WP.spec_bind (Pₘ := fun (y:alloc.vec.Vec W  ×  Std.Array W 65536#usize  × 
              Std.Array W 65536#usize  ×  Std.Array W 32768#usize  ×  Std.Array W 65536#usize  × 
              R  ×  R  ×  R  ×  R  ×  R) => 1  ≤  y.2.2.2.2.2.2.1.val)
          · split
            · -- skip: the covering match's remainder as the only record (guarded push)
              step*
              split
              all_goals step*
              all_goals scalar_tac
            · -- search: tree insertion, then the new covering match (its distance code >= 1)
              step*
              apply WP.spec_bind (Pₘ := fun (z:Std.Array W 65536#usize  ×  Std.Array W 65536#usize  × 
                  Std.Array W 32768#usize  ×  Std.Array W 65536#usize  ×  R  ×  R) =>
                  1  ≤  z.2.2.2.2.2.val)
              · repeat' (split <;> step*)
                all_goals scalar_tac
              rintro ⟨head3, kid3, h33, rct3, cl2, cd2⟩ hcd2
              step*
          rintro ⟨v, a, a1, a2, a3, i17, i18, i19, i20, i21⟩ h18
          step*
        · -- one of the last positions: the latest 3-byte occurrence (guarded push)
          apply WP.spec_bind (Pₘ := fun (_:alloc.vec.Vec W  ×  Std.Array W 32768#usize) => True)
          · repeat' (split <;> step*)
            all_goals scalar_tac
          rintro ⟨v, a⟩ -
          step*
      · step*
        apply WP.spec_bind (Pₘ := fun (_:alloc.vec.Vec W  ×  Std.Array W 32768#usize) => True)
        · repeat' (split <;> step*)
          all_goals scalar_tac
        rintro ⟨v, a⟩ -
        step*
    rintro ⟨mb1, head1, kid1, h31, rct1, cl1, cd1, nq1, nt1, nh1, n31, nr1, nc1⟩ hcd1
    step*
    apply WP.spec_bind (Pₘ := fun (_:R) => True)
    · split
      all_goals step*
    rintro cl2 -
    step*
    simp only [alloc.vec.Vec.length, *, List.length_append, List.length_singleton]
    scalar_tac
  · exact ⟨hmp, hcd⟩
@[local step]
theorem u488 (s:I) (mp:alloc.vec.Vec W) (mb depth) (skip:R)
    (hn26:s.length < 67108864) (hskip:3  ≤  skip.val) (hmp:mp.length = 0) :
    slot.Z186 s mp mb depth skip ⦃ Y112P0! ⦄ := by
  have hhb := EA.EA.u35
  rw [slot.Z186]
  step*
  all_goals try simp only [alloc.vec.Vec.length, *, List.length_append, List.length_singleton]
  all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
@[local step]
theorem u489 (n:R) (cost) (i:R) (hn:n.val < 67108864) (hc:cost.length = i.val) :
    slot.Z185_loop0 n cost i ⦃ Y112P0! ⦄ := by
  rw [slot.Z185_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, i_) => n.val + 1 - i_.val)
    (inv := fun (cost_, i_) => cost_.length = i_.val)
  · rintro ⟨cost_, i_⟩ hc_
    simp only [slot.Z185_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals try simp only [alloc.vec.Vec.length, *, List.length_append, List.length_singleton]
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · exact hc
set_option aeneas.step.nla true in
@[local step]
theorem u490 (input:I) (ch) (n:R) (mp mb cost lit lc dc lf df bl bd sl sd) (rot p0 need passes sampled pe k p1 t:R)
    (hn:n.val = input.length) (hn26:n.val < 67108864) (hp0:p0.val < n.val) (hpe:p0.val  ≤  pe.val  ∧  pe.val  ≤  n.val)
    (hpe':pe.val = n.val  ∨  p0.val + slot.Z2.val  ≤  pe.val)
    (hneed:need.val  ≤  65536) (ht:t.val  ≤  need.val) (hp1:p0.val  ≤  p1.val  ∧  p1.val  ≤  p0.val + 511 * t.val) :
    slot.Z185_loop1_loop0 input ch n mp mb cost lit lc dc lf df bl bd sl sd rot p0 need passes sampled pe k p1 t ⦃ Y112P4! ⦄ := by
  have hbt := EA.EA.u36
  have hseg := EA.EA.u34
  rw [slot.Z185_loop1_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, _, _, _, _, _, _, k_, _, _) => passes.val - k_.val)
    (inv := fun (_, _, _, _, _, _, _, _, _, (pe_:R), _, (p1_:R), (t_:R)) =>
      p0.val  ≤  pe_.val  ∧  pe_.val  ≤  n.val  ∧  (pe_.val = n.val  ∨  p0.val + slot.Z2.val  ≤  pe_.val)  ∧ 
      t_.val  ≤  need.val  ∧  p0.val  ≤  p1_.val  ∧  p1_.val  ≤  p0.val + 511 * t_.val)
  · rintro ⟨ch_, cost_, lit_, lc_, dc_, lf_, df_, sl_, sd_, pe_, k_, p1_, t_⟩ ⟨hpe0, hpe1, hpe2, ht_, hp10, hp11⟩
    simp only [slot.Z185_loop1_loop0.body]
    step*
    apply WP.spec_bind (Pₘ := fun (x:alloc.vec.Vec W  ×  alloc.vec.Vec W  ×  Std.Array W 512#usize  × 
        Std.Array W 32#usize  ×  R  ×  R  ×  R) =>
        p0.val  ≤  x.2.2.2.2.1.val  ∧  x.2.2.2.2.1.val  ≤  n.val  ∧ 
        (x.2.2.2.2.1.val = n.val  ∨  p0.val + slot.Z2.val  ≤  x.2.2.2.2.1.val)  ∧ 
        x.2.2.2.2.2.2.val  ≤  need.val  ∧  p0.val  ≤  x.2.2.2.2.2.1.val  ∧  x.2.2.2.2.2.1.val  ≤  p0.val + 511 * x.2.2.2.2.2.2.val)
    · split
      · step*
        · -- a sampled pass: the window end scales with the sampled bytes per token
          cases ‹R  ×  R›
          step*
          apply WP.spec_bind (Pₘ := fun (z:alloc.vec.Vec W  ×  alloc.vec.Vec W  ×  Std.Array W 512#usize  × 
              Std.Array W 32#usize  ×  R) => p0.val  ≤  z.2.2.2.2.val  ∧  z.2.2.2.2.val  ≤  n.val  ∧ 
              (z.2.2.2.2.val = n.val  ∨  p0.val + slot.Z2.val  ≤  z.2.2.2.2.val))
          · repeat' (split <;> step*)
            all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
          rintro ⟨v, v1, a, a1, i6⟩ hi6
          step*
          all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
        · -- a full pass: dynamic program, then the walk of the round's tokens
          apply WP.spec_bind (Pₘ := fun (lim:R) => lim.val  ≤  pe_.val)
          · split
            all_goals step*
            all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
          rintro lim hlim
          step*
          cases ‹R  ×  R›
          step*
          apply WP.spec_bind (Pₘ := fun (z:Std.Array W 512#usize  ×  Std.Array W 32#usize  ×  R) =>
              p0.val  ≤  z.2.2.val  ∧  z.2.2.val  ≤  n.val  ∧  (z.2.2.val = n.val  ∨  p0.val + slot.Z2.val  ≤  z.2.2.val))
          · repeat' (split <;> step*)
            all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
          rintro ⟨a, a1, i4⟩ hi4
          step*
          all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
        · -- a full pass: dynamic program, then the walk of the round's tokens
          apply WP.spec_bind (Pₘ := fun (lim:R) => lim.val  ≤  pe_.val)
          · split
            all_goals step*
            all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
          rintro lim hlim
          step*
          cases ‹R  ×  R›
          step*
          apply WP.spec_bind (Pₘ := fun (z:Std.Array W 512#usize  ×  Std.Array W 32#usize  ×  R) =>
              p0.val  ≤  z.2.2.val  ∧  z.2.2.val  ≤  n.val  ∧  (z.2.2.val = n.val  ∨  p0.val + slot.Z2.val  ≤  z.2.2.val))
          · repeat' (split <;> step*)
            all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
          rintro ⟨a, a1, i4⟩ hi4
          step*
          all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
      · step*
        · -- a full pass: dynamic program, then the walk of the round's tokens
          apply WP.spec_bind (Pₘ := fun (lim:R) => lim.val  ≤  pe_.val)
          · split
            all_goals step*
            all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
          rintro lim hlim
          step*
          cases ‹R  ×  R›
          step*
          apply WP.spec_bind (Pₘ := fun (z:Std.Array W 512#usize  ×  Std.Array W 32#usize  ×  R) =>
              p0.val  ≤  z.2.2.val  ∧  z.2.2.val  ≤  n.val  ∧  (z.2.2.val = n.val  ∨  p0.val + slot.Z2.val  ≤  z.2.2.val))
          · repeat' (split <;> step*)
            all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
          rintro ⟨a, a1, i4⟩ hi4
          step*
          all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
    rintro ⟨ch1, cost1, lf1, df1, pe1, p11, t1⟩ ⟨hq0, hq1, hq2, hq3, hq4, hq5⟩
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · exact ⟨hpe.1, hpe.2, hpe', ht, hp1.1, hp1.2⟩
@[local step]
theorem u491 (input:I) (ch first_passes fspass passes_k) (n:R) (mp mb cost lit lc dc lf df bl bd sl sd zl zd) (rot spn p0 used bpt:R)
    (hn:n.val = input.length) (hn26:n.val < 67108864) (hused:used.val < slot.Z7.val) (hbpt:256  ≤  bpt.val  ∧  bpt.val  ≤  65536) :
    slot.Z185_loop1 input ch first_passes fspass passes_k n mp mb cost lit lc dc lf df bl bd sl sd zl zd rot spn p0 used bpt ⦃ Y112P0! ⦄ := by
  have hbt := EA.EA.u36
  rw [slot.Z185_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, _, _, _, _, _, _, _, p0_, _, _) => n.val - p0_.val)
    (inv := fun (_, _, _, _, _, _, _, _, _, _, _, _, used_, bpt_) => used_.val < slot.Z7.val  ∧ 
      256  ≤  bpt_.val  ∧  bpt_.val  ≤  130816)
  · rintro ⟨ch_, cost_, lit_, lc_, dc_, lf_, df_, bl_, bd_, sl_, sd_, p0_, used_, bpt_⟩ ⟨hused_, hbpt0, hbpt1⟩
    simp only [slot.Z185_loop1.body, EA.EA.u37]
    step*
    · -- the token estimate `need * bpt` fits in 32 bits
      have:need.val * bpt_.val  ≤  16384 * 130816 := Nat.mul_le_mul (by (subst_vars;scalar_tac (simpAllMaxSteps := 0))) hbpt1
      (subst_vars;scalar_tac (simpAllMaxSteps := 0))
    apply WP.spec_bind (Pₘ := fun (pe:R) => p0_.val  ≤  pe.val  ∧  pe.val  ≤  n.val  ∧ 
      (pe.val = n.val  ∨  p0_.val + slot.Z2.val  ≤  pe.val))
    · split
      all_goals step*
      all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
    rintro pe hpe
    step*
    apply WP.spec_bind (Pₘ := fun (x:Std.Array W 512#usize  ×  Std.Array W 32#usize  ×  R) =>
      x.2.2.val < slot.Z7.val)
    · split
      all_goals step*
      all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
    rintro ⟨bl1, bd1, used2⟩ hu2
    step*
    all_goals try (
      have hdiv:bpt1.val  ≤  130816 := by
        rw [bpt1_post];apply Nat.div_le_of_le_mul;(subst_vars;scalar_tac (simpAllMaxSteps := 0))
      by_cases hb:bpt1 < 256#usize
      all_goals simp only [hb, ite_true, ite_false])
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · -- the invariant allows up to 511 bytes per token (the snapshot never clamps `bpt` from above)
    exact ⟨hused, hbpt.1, by omega⟩
@[local step]
theorem u492 (input:I) (ch) (depth skip first_passes fspass passes_k spass:R)
    (hn:input.length < 67108864) (h1:depth.val  ≤  65536) (h2:skip.val  ≤  65536) (h2':3  ≤  skip.val)
    (h3:first_passes.val  ≤  65536) (h4:fspass.val  ≤  65536) (h5:passes_k.val  ≤  65536) (h6:spass.val  ≤  65536) :
    slot.Z185 input ch depth skip first_passes fspass passes_k spass ⦃ Y112P0! ⦄ := by
  have hbt := EA.EA.u36
  rw [slot.Z185]
  step*
  all_goals rfl












@[local step]
theorem u493 (s:I) (n:R) (head) (r4 r6 probes p:R)
    (hn:n.val = s.length) (hn26:n.val < 67108864) (hr4:r4.val  ≤  probes.val) (hr6:r6.val  ≤  probes.val)
    (hpr:probes.val  ≤  p.val) (hp:p.val  ≤  n.val + slot.Z10.val) :
    slot.Z218_loop s n head r4 r6 probes p ⦃ fun r => r.1.val  ≤  65536  ∧  r.2.val  ≤  65536 ⦄ := by
  have f1 := EA.EA.u173
  have f2 := EA.EA.u174
  have f3 := Submission.EA.EA.C_WS_val
  rw [slot.Z218_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, p') => n.val + slot.Z10.val - p'.val)
    (inv := fun (_, r4', r6', pr', p') => r4'.val  ≤  pr'.val  ∧  r6'.val  ≤  pr'.val  ∧  pr'.val  ≤  p'.val  ∧ 
      p'.val  ≤  n.val + slot.Z10.val)
  · rintro ⟨h', r4', r6', pr', p'⟩ ⟨i1, i2, i3, i4⟩
    simp only [slot.Z218_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact ⟨hr4, hr6, hpr, hp⟩
@[local step]
theorem u494 (s:I) (hn26:s.length < 67108864) :
    slot.Z218 s ⦃ fun r => r.1.val  ≤  65536  ∧  r.2.val  ≤  65536 ⦄ := Y127U17! slot.Z218
@[local step]
theorem u495 (plan e_nd p) :
    slot.Z195_loop plan e_nd p ⦃ fun r => r.length = plan.length ⦄ := by
  rw [slot.Z195_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, p') => e_nd.val - p'.val)
    (inv := fun (plan', _) => plan'.length = plan.length)
  · rintro ⟨plan', p'⟩ hinv
    simp only [slot.Z195_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · rfl
@[local step]
theorem u496 (plan p0 e_nd) :
    slot.Z195 plan p0 e_nd ⦃ fun r => r.length = plan.length ⦄ := Y127U17! slot.Z195
@[local step]
theorem u497 (d):slot.Z197 d ⦃ fun r => r.val < 256 ⦄ := Y127U17! slot.Z197
@[local step]
theorem u498 (len):slot.Z209 len ⦃ fun r => r.val < 256 ⦄ := Y127U17! slot.Z209
@[local step]
theorem u499 (lf df) :
    slot.Z212_loop0 lf df 0#usize ⦃ fun r => EA.EA.u15 r.1.val 0  ∧  EA.EA.u15 r.2.val 0 ⦄ := by
  rw [slot.Z212_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, k) => 288 - k.val)
    (inv := fun (lf', df', k) => k.val  ≤  288  ∧ 
      (∀ j (hj:j < k.val) (hl:j < lf'.val.length), (lf'.val[j]).val = 0)  ∧ 
      (∀ j (hj:j < k.val) (hl:j < df'.val.length), (df'.val[j]).val = 0))
  · rintro ⟨lf', df', k⟩ ⟨hk, hz1, hz2⟩
    simp only [slot.Z212_loop0.body]
    step*
    · refine ⟨by (subst_vars;scalar_tac (simpAllMaxSteps := 0)), ?_, ?_, by (subst_vars;scalar_tac (simpAllMaxSteps := 0))⟩
      · intro j hj hl
        subst a_post
        simp only [Array.set_val_eq, List.getElem_set]
        split
        · rfl
        · exact hz1 j (by (subst_vars;scalar_tac (simpAllMaxSteps := 0))) (by simpa using hl)
      · intro j hj hl
        subst a1_post
        simp only [Array.set_val_eq, List.getElem_set]
        split
        · rfl
        · exact hz2 j (by (subst_vars;scalar_tac (simpAllMaxSteps := 0))) (by simpa using hl)
    · have:k.val = 288 := by (subst_vars;scalar_tac (simpAllMaxSteps := 0))
      refine ⟨?_, ?_⟩
      · intro j hl
        have hl':j < 288 := by simpa using hl
        rw [hz1 j (by omega) hl]
      · intro j hl
        have hl':j < 288 := by simpa using hl
        rw [hz2 j (by omega) hl]
  · exact ⟨by simp, fun j hj => by simp at hj, fun j hj => by simp at hj⟩
@[local step]
theorem u500 (s:I) (choice) (lf df) (n p t:R)
    (hn:n.val = s.length) (hlf:EA.EA.u15 lf.val t.val) (hdf:EA.EA.u15 df.val t.val) :
    slot.Z212_loop1 s choice lf df n p t ⦃ fun r => p.val  ≤  r.2.2.val  ∧  (p.val  ≤  n.val  →  r.2.2.val  ≤  n.val) ⦄ := by
  have hB := EA.EA.u159
  rw [slot.Z212_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, t') => slot.Z7.val - t'.val)
    (inv := fun (lf', df', p', t') => EA.EA.u15 lf'.val t'.val  ∧  EA.EA.u15 df'.val t'.val  ∧  p.val  ≤  p'.val  ∧ 
      (p.val  ≤  n.val  →  p'.val  ≤  n.val))
  · rintro ⟨lf', df', p', t'⟩ ⟨hlf', hdf', hp1, hp2⟩
    simp only [slot.Z212_loop1.body]
    step*
    apply WP.spec_bind (Pₘ := fun (x:Std.Array W 288#usize  ×  Std.Array W 288#usize  ×  R) =>
      EA.EA.u15 x.1.val (t'.val + 1)  ∧  EA.EA.u15 x.2.1.val (t'.val + 1)  ∧  p'.val < x.2.2.val  ∧  x.2.2.val  ≤  n.val)
    · split
      · step*
        · -- a match: one length and one distance counter go up (wrapping, but they cannot wrap)
          have h6 := EA.EA.u16 hlf' i5.val (by (subst_vars;scalar_tac (simpAllMaxSteps := 0)))
          have h12 := EA.EA.u16 hdf' i11.val (by (subst_vars;scalar_tac (simpAllMaxSteps := 0)))
          refine ⟨?_, ?_, by (subst_vars;scalar_tac (simpAllMaxSteps := 0)), by (subst_vars;scalar_tac (simpAllMaxSteps := 0))⟩
          · rw [a_post, Array.set_val_eq];exact EA.EA.u20 hlf' _ _ (by (subst_vars;scalar_tac (simpAllMaxSteps := 0)))
          · rw [a1_post, Array.set_val_eq];exact EA.EA.u20 hdf' _ _ (by (subst_vars;scalar_tac (simpAllMaxSteps := 0)))
        · -- the literal counter cannot overflow
          have := EA.EA.u16 hlf' i4.val (by (subst_vars;scalar_tac (simpAllMaxSteps := 0)))
          (subst_vars;scalar_tac (simpAllMaxSteps := 0))
        · -- a literal (the match does not fit)
          have := EA.EA.u16 hlf' i4.val (by (subst_vars;scalar_tac (simpAllMaxSteps := 0)))
          refine ⟨?_, EA.EA.u17 hdf' (by omega), by (subst_vars;scalar_tac (simpAllMaxSteps := 0)), by (subst_vars;scalar_tac (simpAllMaxSteps := 0))⟩
          rw [a_post, Array.set_val_eq];exact EA.EA.u20 hlf' _ _ (by (subst_vars;scalar_tac (simpAllMaxSteps := 0)))
      · -- a literal
        step*
        · have := EA.EA.u16 hlf' i3.val (by (subst_vars;scalar_tac (simpAllMaxSteps := 0)))
          (subst_vars;scalar_tac (simpAllMaxSteps := 0))
        · have := EA.EA.u16 hlf' i3.val (by (subst_vars;scalar_tac (simpAllMaxSteps := 0)))
          refine ⟨?_, EA.EA.u17 hdf' (by omega), by (subst_vars;scalar_tac (simpAllMaxSteps := 0)), by (subst_vars;scalar_tac (simpAllMaxSteps := 0))⟩
          rw [a_post, Array.set_val_eq];exact EA.EA.u20 hlf' _ _ (by (subst_vars;scalar_tac (simpAllMaxSteps := 0)))
    · rintro ⟨lf1, df1, p1⟩ ⟨h1, h2, h3, h4⟩
      step*
  · exact ⟨hlf, hdf, le_refl _, fun h => h⟩
@[local step]
theorem u501 (s choice p0 lf df) :
    slot.Z212 s choice p0 lf df ⦃ fun r => p0.val  ≤  r.1.val  ∧  (p0.val  ≤  s.length  →  r.1.val  ≤  s.length) ⦄ := by
  rw [slot.Z212]
  step*
@[local step]
theorem u502 (lf) (bits:Std.U64) (i:R) (hi:i.val  ≤  288)
    (hb:bits.val  ≤  3 + i.val * 2 ^ 40) :
    slot.Z203_loop0 lf bits i ⦃ fun r => r.val  ≤  3 + 288 * 2 ^ 40 ⦄ := by
  rw [slot.Z203_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, i') => 288 - i'.val)
    (inv := fun (bits', i') => i'.val  ≤  288  ∧  bits'.val  ≤  3 + i'.val * 2 ^ 40)
  · rintro ⟨bits', i'⟩ ⟨hi', hb'⟩
    simp only [slot.Z203_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · exact ⟨hi, hb⟩
@[local step]
theorem u503 (df) (bits:Std.U64) (d:R) (hd:d.val  ≤  30)
    (hb:bits.val  ≤  3 + 288 * 2 ^ 40 + d.val * 2 ^ 40) :
    slot.Z203_loop1 df bits d ⦃ fun r => r.val  ≤  3 + 318 * 2 ^ 40 ⦄ := by
  rw [slot.Z203_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, d') => 30 - d'.val)
    (inv := fun (bits', d') => d'.val  ≤  30  ∧  bits'.val  ≤  3 + 288 * 2 ^ 40 + d'.val * 2 ^ 40)
  · rintro ⟨bits', d'⟩ ⟨hd', hb'⟩
    simp only [slot.Z203_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · exact ⟨hd, hb⟩
@[local step]
theorem u504 (lf df) :
    slot.Z203 lf df ⦃ Y112P0! ⦄ := Y127U17! slot.Z203
@[local step]
theorem u505 (clf) (r:R) (extra:Std.U64) (fuel:R)
    (hx:extra.val + 7 * fuel.val  ≤  2 ^ 40) :
    slot.Z220_loop0 clf r extra fuel ⦃ fun res => res.2.2.val  ≤  extra.val + 7 * fuel.val ⦄ := by
  rw [slot.Z220_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, f) => f.val)
    (inv := fun (_, _, e, f) => e.val + 7 * f.val  ≤  extra.val + 7 * fuel.val)
  · rintro ⟨clf', r', e', f'⟩ hinv
    simp only [slot.Z220_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · simp
@[local step]
theorem u506 (clf) (r:R) (extra:Std.U64) (fuel:R)
    (hx:extra.val + 2 * fuel.val  ≤  2 ^ 40) :
    slot.Z220_loop1 clf r extra fuel ⦃ fun res => res.2.2.val  ≤  extra.val + 2 * fuel.val ⦄ := by
  rw [slot.Z220_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, f) => f.val)
    (inv := fun (_, _, e, f) => e.val + 2 * f.val  ≤  extra.val + 2 * fuel.val)
  · rintro ⟨clf', r', e', f'⟩ hinv
    simp only [slot.Z220_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · simp
@[local step]
theorem u507 (clf v) (r0:R) (hr0:1  ≤  r0.val  ∧  r0.val  ≤  512) :
    slot.Z220 clf v r0 ⦃ fun r => r.1.val  ≤  7 * (r0.val + 1) ⦄ := Y127U17! slot.Z220
@[local step]
theorem u508 (sw) (k:R) (shift:W) (hshift:shift.val < 32) :
    slot.Z217_loop0 sw k shift (Array.repeat 257#usize 0#usize) 0#usize ⦃ fun r => EA.EA.u15 r.val 288 ⦄ := by
  rw [slot.Z217_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, i') => 288 - i'.val)
    (inv := fun (cnt', i') => i'.val  ≤  288  ∧  EA.EA.u15 cnt'.val i'.val)
  · rintro ⟨cnt', i'⟩ ⟨hi', hc'⟩
    simp only [slot.Z217_loop0.body]
    step*
    all_goals first
      | (subst_vars;scalar_tac (simpAllMaxSteps := 0))
      | exact EA.EA.u17 hc' (by (subst_vars;scalar_tac (simpAllMaxSteps := 0)))
      | (refine ⟨by (subst_vars;scalar_tac (simpAllMaxSteps := 0)), ?_, by (subst_vars;scalar_tac (simpAllMaxSteps := 0))⟩
         rw [a_post, Array.set_val_eq, show i9.val = i'.val + 1 by (subst_vars;scalar_tac (simpAllMaxSteps := 0))]
         apply EA.EA.u20 hc'
         have := EA.EA.u16 hc' i5.val (by (subst_vars;scalar_tac (simpAllMaxSteps := 0)))
         (subst_vars;scalar_tac (simpAllMaxSteps := 0)))
  · exact ⟨by simp, EA.EA.u41 _ _ _ (by simp)⟩
@[local step]
theorem u509 (cnt) (hcnt:EA.EA.u15 cnt.val 288) :
    slot.Z217_loop1 cnt 1#usize ⦃ fun r => EA.EA.u15 r.val 74016 ⦄ := by
  rw [slot.Z217_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, c') => 257 - c'.val)
    (inv := fun (cnt', c') => 1  ≤  c'.val  ∧  c'.val  ≤  257  ∧ 
      (∀ j (hj:j < cnt'.val.length), j < c'.val  →  (cnt'.val[j]).val  ≤  288 * c'.val)  ∧ 
      (∀ j (hj:j < cnt'.val.length), c'.val  ≤  j  →  (cnt'.val[j]).val  ≤  288))
  · rintro ⟨cnt', c'⟩ ⟨hc1, hc2, hlo, hhi⟩
    simp only [slot.Z217_loop1.body]
    step*
    · have hi:i.val  ≤  288 := by rw [i_post];exact hhi _ _ (le_refl _)
      have hi2:i2.val  ≤  288 * c'.val := by rw [i2_post];exact hlo _ _ (by (subst_vars;scalar_tac (simpAllMaxSteps := 0)))
      refine ⟨by (subst_vars;scalar_tac (simpAllMaxSteps := 0)), by (subst_vars;scalar_tac (simpAllMaxSteps := 0)), ?_, ?_, by (subst_vars;scalar_tac (simpAllMaxSteps := 0))⟩
      · intro j hj hjc
        subst a_post
        simp only [Array.set_val_eq, List.getElem_set]
        split
        · (subst_vars;scalar_tac (simpAllMaxSteps := 0))
        · have hj':j < (↑cnt':List R).length := by simpa using hj
          have := hlo j hj' (by (subst_vars;scalar_tac (simpAllMaxSteps := 0)))
          (subst_vars;scalar_tac (simpAllMaxSteps := 0))
      · intro j hj hjc
        subst a_post
        simp only [Array.set_val_eq, List.getElem_set]
        split
        · (subst_vars;scalar_tac (simpAllMaxSteps := 0))
        · exact hhi j (by simpa using hj) (by (subst_vars;scalar_tac (simpAllMaxSteps := 0)))
    · intro j hj
      have hj2:j < 257 := by simpa using hj
      have := hlo j hj (by (subst_vars;scalar_tac (simpAllMaxSteps := 0)))
      (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · refine ⟨by simp, by simp, ?_, ?_⟩
    · intro j hj hj1
      have := hcnt j hj
      simp at hj1 ⊢
      omega
    · intro j hj _
      exact hcnt j hj
@[local step]
theorem u510 (sw ss dw ds) (k:R) (shift:W) (cnt) (hshift:shift.val < 32)
    (hcnt:EA.EA.u15 cnt.val 74016) :
    slot.Z217_loop2 sw ss dw ds k shift cnt 0#usize ⦃ Y112P0! ⦄ := by
  rw [slot.Z217_loop2]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, j') => 288 - j'.val)
    (inv := fun (_, _, cnt', j') => j'.val  ≤  288  ∧  EA.EA.u15 cnt'.val (74016 + j'.val))
  · rintro ⟨dw', ds', cnt', j'⟩ ⟨hj', hc'⟩
    simp only [slot.Z217_loop2.body]
    step*
    all_goals first
      | (subst_vars;scalar_tac (simpAllMaxSteps := 0))
      | (have := EA.EA.u16 hc' i3.val (by (subst_vars;scalar_tac (simpAllMaxSteps := 0)))
         (subst_vars;scalar_tac (simpAllMaxSteps := 0)))
      | (refine ⟨by (subst_vars;scalar_tac (simpAllMaxSteps := 0)), ?_, by (subst_vars;scalar_tac (simpAllMaxSteps := 0))⟩
         rw [a2_post, Array.set_val_eq, show j1.val = j'.val + 1 by (subst_vars;scalar_tac (simpAllMaxSteps := 0)), ← Nat.add_assoc]
         apply EA.EA.u20 hc'
         have := EA.EA.u16 hc' i3.val (by (subst_vars;scalar_tac (simpAllMaxSteps := 0)))
         (subst_vars;scalar_tac (simpAllMaxSteps := 0)))
  · exact ⟨by simp, by simpa using hcnt⟩
@[local step]
theorem u511 (sw ss dw ds) (k:R) (shift:W) (hshift:shift.val < 32) :
    slot.Z217 sw ss dw ds k shift ⦃ Y112P0! ⦄ := by
  rw [slot.Z217]
  step*
@[local step]
theorem u512 (freq m lens aw asy) (k i:R) (hk:k.val  ≤  i.val) (hi:i.val  ≤  288) :
    slot.Z206_loop0 freq m lens aw asy k i ⦃ fun r => r.2.2.2.val  ≤  288 ⦄ := by
  rw [slot.Z206_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, i') => 288 - i'.val)
    (inv := fun (_, _, _, k', i') => k'.val  ≤  i'.val  ∧  i'.val  ≤  288)
  · rintro ⟨lens', aw', asy', k', i'⟩ ⟨hk', hi'⟩
    simp only [slot.Z206_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · exact ⟨hk, hi⟩
@[local step]
theorem u513 (aw) (k:R) (iw ipar lpar) (li ii ni:R) (w2) (t:R)
    (hii:ii.val  ≤  2 ^ 20) :
    slot.Z206_loop1_loop0 aw k iw ipar lpar li ii ni w2 t ⦃ fun r => r.2.2.2.1.val  ≤  ii.val + 2 ⦄ := by
  rw [slot.Z206_loop1_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, _, t') => 2 - t'.val)
    (inv := fun (_, _, _, ii', _, t') => ii'.val + t.val  ≤  ii.val + t'.val  ∧  t.val  ≤  t'.val  ∧ 
      (t.val  ≤  2  →  t'.val  ≤  2)  ∧  (2 < t.val  →  t'.val = t.val))
  · rintro ⟨ipar', lpar', li', ii', w2', t'⟩ ⟨h1, h2, h3, h4⟩
    simp only [slot.Z206_loop1_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · simp
@[local step]
theorem u514 (aw) (k:R) (iw ipar lpar) (li ii ni:R) (hii:ii.val  ≤  2 * ni.val)
    (hni:ni.val  ≤  287) (hk:k.val  ≤  288) :
    slot.Z206_loop1 aw k iw ipar lpar li ii ni ⦃ fun r => ni.val  ≤  r.2.2.val  ∧  (ni.val + 1 < k.val  →  ni.val < r.2.2.val) ⦄ := by
  rw [slot.Z206_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, _, ni') => 287 - ni'.val)
    (inv := fun (_, _, _, _, ii', ni') => ni.val  ≤  ni'.val  ∧  ni'.val  ≤  287  ∧  ii'.val  ≤  2 * ni'.val)
  · rintro ⟨iw', ipar', lpar', li', ii', ni'⟩ ⟨h1, h2, h3⟩
    simp only [slot.Z206_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · exact ⟨le_refl _, hni, hii⟩
@[local step]
theorem u515 (ipar idep j) :
    slot.Z206_loop2 ipar idep j ⦃ Y112P0! ⦄ := by
  rw [slot.Z206_loop2]
  apply Std.loop.spec_decr_nat
    (measure := fun (idep_, j_) => j_.val)
    (inv := fun _ => True)
  · rintro ⟨idep_, j_⟩ _
    simp only [slot.Z206_loop2.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · trivial
@[local step]
theorem u516 (lens asy k lpar idep x) :
    slot.Z206_loop3 lens asy k lpar idep x ⦃ Y112P0! ⦄ := by
  rw [slot.Z206_loop3]
  apply Std.loop.spec_decr_nat
    (measure := fun (lens_, x_) => k.val - x_.val)
    (inv := fun _ => True)
  · rintro ⟨lens_, x_⟩ _
    simp only [slot.Z206_loop3.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · trivial
@[local step]
theorem u517 (freq m lens):slot.Z206 freq m lens ⦃ Y112P0! ⦄ := Y127U17! slot.Z206
@[local step]
theorem u518 (lf ll) (body:Std.U64) (hlit i:R) (hi:i.val  ≤  286)
    (hb:body.val  ≤  i.val * 2 ^ 41) :
    slot.Z198_loop0 lf ll body hlit i ⦃ fun r => r.1.val  ≤  286 * 2 ^ 41  ∧  r.2.val  ≤  max hlit.val 286 ⦄ := by
  rw [slot.Z198_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, i') => 286 - i'.val)
    (inv := fun (b', h', i') => i'.val  ≤  286  ∧  b'.val  ≤  i'.val * 2 ^ 41  ∧  h'.val  ≤  max hlit.val 286)
  · rintro ⟨b', h', i'⟩ ⟨h1, h2, h3⟩
    simp only [slot.Z198_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · exact ⟨hi, hb, by (subst_vars;scalar_tac (simpAllMaxSteps := 0))⟩
@[local step]
theorem u519 (df dl) (body:Std.U64) (hdist any:R) (d:R) (hd:d.val  ≤  30)
    (hb:body.val  ≤  286 * 2 ^ 41 + d.val * 2 ^ 41) :
    slot.Z198_loop1 df dl body hdist any d ⦃ fun r => r.1.val  ≤  316 * 2 ^ 41  ∧  r.2.1.val  ≤  max hdist.val 30 ⦄ := by
  rw [slot.Z198_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, d') => 30 - d'.val)
    (inv := fun (b', h', _, d') => d'.val  ≤  30  ∧  b'.val  ≤  286 * 2 ^ 41 + d'.val * 2 ^ 41  ∧  h'.val  ≤  max hdist.val 30)
  · rintro ⟨b', h', a', d'⟩ ⟨h1, h2, h3⟩
    simp only [slot.Z198_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · exact ⟨hd, hb, by (subst_vars;scalar_tac (simpAllMaxSteps := 0))⟩
@[local step]
theorem u520 (ll dl hlit total seq i2) :
    slot.Z198_loop2 ll dl hlit total seq i2 ⦃ Y112P0! ⦄ := by
  rw [slot.Z198_loop2]
  apply Std.loop.spec_decr_nat
    (measure := fun (seq_, i2_) => total.val - i2_.val)
    (inv := fun _ => True)
  · rintro ⟨seq_, i2_⟩ _
    simp only [slot.Z198_loop2.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · trivial
@[local step]
theorem u521 (total seq) (j r:R) (v) (hj:j.val  ≤  512) (hr:r.val  ≤  512) :
    slot.Z198_loop3_loop0 total seq j v r ⦃ fun res => r.val  ≤  res.val  ∧  res.val  ≤  max r.val 512  ∧ 
      (j.val + r.val  ≤  512  →  j.val + res.val  ≤  512) ⦄ := by
  rw [slot.Z198_loop3_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun r' => 512 - r'.val)
    (inv := fun r' => r.val  ≤  r'.val  ∧  r'.val  ≤  max r.val 512  ∧  (j.val + r.val  ≤  512  →  j.val + r'.val  ≤  512))
  · rintro r' ⟨h1, h2, h3⟩
    simp only [slot.Z198_loop3_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · exact ⟨le_refl _, by (subst_vars;scalar_tac (simpAllMaxSteps := 0)), fun h => h⟩
@[local step]
theorem u522 (clf) (extra:Std.U64) (total seq) (j:R) (hj:j.val  ≤  512)
    (hx:extra.val  ≤  j.val * 4096) :
    slot.Z198_loop3 clf extra total seq j ⦃ fun r => r.2.val  ≤  513 * 4096 ⦄ := by
  rw [slot.Z198_loop3]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, j') => 512 - j'.val)
    (inv := fun (_, e', j') => j'.val  ≤  512  ∧  e'.val  ≤  j'.val * 4096)
  · rintro ⟨clf', e', j'⟩ ⟨h1, h2⟩
    simp only [slot.Z198_loop3.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · exact ⟨hj, hx⟩
@[local step]
theorem u523 (cl hclen) :
    slot.Z198_loop4 cl hclen ⦃ fun r => r.val  ≤  hclen.val ⦄ := by
  rw [slot.Z198_loop4]
  apply Std.loop.spec_decr_nat
    (measure := fun h' => h'.val)
    (inv := fun h' => h'.val  ≤  hclen.val)
  · rintro h' h1
    simp only [slot.Z198_loop4.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · exact le_refl _
@[local step]
theorem u524 (clf cl) (hdr:Std.U64) (c:R) (hc:c.val  ≤  19)
    (hh:hdr.val  ≤  2 ^ 40 + c.val * 2 ^ 35) :
    slot.Z198_loop5 clf cl hdr c ⦃ fun r => r.val  ≤  2 ^ 40 + 19 * 2 ^ 35 ⦄ := by
  rw [slot.Z198_loop5]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, c') => 19 - c'.val)
    (inv := fun (h', c') => c'.val  ≤  19  ∧  h'.val  ≤  2 ^ 40 + c'.val * 2 ^ 35)
  · rintro ⟨h', c'⟩ ⟨h1, h2⟩
    simp only [slot.Z198_loop5.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · exact ⟨hc, hh⟩
@[local step]
theorem u525 (lf df):slot.Z198 lf df ⦃ Y112P0! ⦄ := Y127U17! slot.Z198
@[local step]
theorem u526 (s:I) (ec q:R)
    (hec:ec.val  ≤  s.length) (hn26:s.length < 67108864) :
    slot.Z213_loop0_loop0 s ec (Array.repeat 288#usize 0#u32) q ⦃ Y112P0! ⦄ := by
  rw [slot.Z213_loop0_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, q') => ec.val - q'.val)
    (inv := fun (lb', q') => EA.EA.u15 lb'.val q'.val)
  · rintro ⟨lb', q'⟩ hlb'
    simp only [slot.Z213_loop0_loop0.body]
    step*
    all_goals first
      | (have := EA.EA.u16 hlb' i1.val (by (subst_vars;scalar_tac (simpAllMaxSteps := 0)))
         (subst_vars;scalar_tac (simpAllMaxSteps := 0)))
      | (refine ⟨?_, by (subst_vars;scalar_tac (simpAllMaxSteps := 0))⟩
         rw [a_post, Array.set_val_eq, show q1.val = q'.val + 1 by (subst_vars;scalar_tac (simpAllMaxSteps := 0))]
         apply EA.EA.u20 hlb'
         have := EA.EA.u16 hlb' i1.val (by (subst_vars;scalar_tac (simpAllMaxSteps := 0)))
         (subst_vars;scalar_tac (simpAllMaxSteps := 0)))
  · exact EA.EA.u41 _ _ _ (by simp)
@[local step]
theorem u527 (s:I) (plan) (n:R) (lf df p fuel) (hn:n.val = s.length)
    (hn26:n.val < 67108864) :
    slot.Z213_loop0 s plan n lf df p fuel ⦃ Y112P0! ⦄ := by
  have hB := EA.EA.u159
  rw [slot.Z213_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, f) => f.val)
    (inv := fun _ => True)
  · rintro ⟨plan', lf', df', p', f'⟩ _
    simp only [slot.Z213_loop0.body]
    step*
    apply WP.spec_bind (Pₘ := fun _ => True)
    · split <;> step*
    rintro ca _
    step*
    apply WP.spec_bind (Pₘ := fun (x:R) => p'.val  ≤  x.val  ∧  x.val  ≤  n.val)
    · split <;> step*
      all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
    rintro eb ⟨heb1, heb2⟩
    apply WP.spec_bind (Pₘ := fun (x:R) => p'.val  ≤  x.val  ∧  x.val  ≤  n.val)
    · split <;> step*
      all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
    rintro ec ⟨hec1, hec2⟩
    step*
    apply WP.spec_bind (Pₘ := fun _ => True)
    · split <;> step*
    rintro cb _
    apply WP.spec_bind (Pₘ := fun _ => True)
    · split <;> step*
    rintro cb1 _
    step*
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · trivial
@[local step]
theorem u528 (s:I) (plan) (hn26:s.length < 67108864) :
    slot.Z213 s plan ⦃ Y112P0! ⦄ := Y127U17! slot.Z213
@[local step]
theorem u529 (s:I) (n allow:R) (bad i:R) (hn:n.val  ≤  s.length)
    (hbad:bad.val  ≤  i.val) :
    slot.Z207_loop s n allow bad i ⦃ Y112P0! ⦄ := by
  rw [slot.Z207_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, i') => n.val - i'.val)
    (inv := fun (bad', i') => bad'.val  ≤  i'.val)
  · rintro ⟨bad', i'⟩ hb'
    simp only [slot.Z207_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · exact hbad
@[local step]
theorem u530 (s) :
    slot.Z207 s ⦃ Y112P0! ⦄ := Y127U17! slot.Z207
@[local step]
theorem u531 (lf df ll dl) (est:Std.U64) (q:R) (hq:q.val  ≤  288)
    (he:est.val  ≤  70 + q.val * 2 ^ 42) :
    slot.Z215_loop0 lf df ll dl est q ⦃ fun r => r.val  ≤  70 + 288 * 2 ^ 42 ⦄ := by
  rw [slot.Z215_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, q') => 288 - q'.val)
    (inv := fun (e', q') => q'.val  ≤  288  ∧  e'.val  ≤  70 + q'.val * 2 ^ 42)
  · rintro ⟨e', q'⟩ ⟨h1, h2⟩
    simp only [slot.Z215_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · exact ⟨hq, he⟩
@[local step]
theorem u532 (models) (tokpen:W) (ll) (i:R) (htok:tokpen.val  ≤  65536)
    (hm:models.length + (256 - i.val) < 4294967295) :
    slot.Z215_loop1 models tokpen ll i ⦃ fun r => r.length = models.length + (256 - i.val) ⦄ := by
  have h1 := EA.EA.u164
  have h2 := Submission.EA.EA.C_UNUSED_LIT_le
  rw [slot.Z215_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, i') => 256 - i'.val)
    (inv := fun (m', i') => m'.length = models.length + (i'.val - i.val)  ∧  i.val  ≤  i'.val  ∧  i'.val  ≤  max i.val 256)
  · rintro ⟨m', i'⟩ ⟨h3, h4, h5⟩
    simp only [slot.Z215_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · exact ⟨by simp, le_refl _, by (subst_vars;scalar_tac (simpAllMaxSteps := 0))⟩
@[local step]
theorem u533 (models) (tax ulen tokpen:W) (ll) (l:R) (htax:tax.val  ≤  65536)
    (hulen:ulen.val  ≤  65536) (htok:tokpen.val  ≤  65536) (hl:3  ≤  l.val)
    (hm:models.length + (259 - l.val) < 4294967295) :
    slot.Z215_loop2 models tax ulen tokpen ll l ⦃ fun r => r.length = models.length + (259 - l.val) ⦄ := by
  have h1 := EA.EA.u164
  rw [slot.Z215_loop2]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, l') => 259 - l'.val)
    (inv := fun (m', l') => m'.length = models.length + (l'.val - l.val)  ∧  l.val  ≤  l'.val  ∧  l'.val  ≤  max l.val 259)
  · rintro ⟨m', l'⟩ ⟨h3, h4, h5⟩
    simp only [slot.Z215_loop2.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · exact ⟨by simp, le_refl _, by (subst_vars;scalar_tac (simpAllMaxSteps := 0))⟩
@[local step]
theorem u534 (models) (udist:W) (dl) (d:R) (hud:udist.val  ≤  65536)
    (hm:models.length + (32 - d.val) < 4294967295) :
    slot.Z215_loop3 models udist dl d ⦃ fun r => r.length = models.length + (32 - d.val) ⦄ := by
  have h1 := EA.EA.u164
  rw [slot.Z215_loop3]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, d') => 32 - d'.val)
    (inv := fun (m', d') => m'.length = models.length + (d'.val - d.val)  ∧  d.val  ≤  d'.val  ∧  d'.val  ≤  max d.val 32)
  · rintro ⟨m', d'⟩ ⟨h3, h4, h5⟩
    simp only [slot.Z215_loop3.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · exact ⟨by simp, le_refl _, by (subst_vars;scalar_tac (simpAllMaxSteps := 0))⟩
@[local step]
theorem u535 (models lf df) (tax ulen udist tokpen:W) (htax:tax.val  ≤  65536) (hulen:ulen.val  ≤  65536)
    (hud:udist.val  ≤  65536) (htok:tokpen.val  ≤  65536) (hm:models.length + 544 < 4294967295) :
    slot.Z215 models lf df tax ulen udist tokpen ⦃ fun r => r.1.val  ≤  70 + 288 * 2 ^ 42  ∧  r.2.length = models.length + 544 ⦄ := Y127U17! slot.Z215
@[local step]
theorem u536 (s:I) (choice) (n:R) (lf df) (p t:R)
    (hn:n.val  ≤  s.length) (hnc:n.val  ≤  choice.length) (hn26:n.val < 67108864) :
    slot.Z219_loop0_loop0 s choice n lf df p t ⦃ fun r => p.val  ≤  r.2.2.val  ∧ 
      r.2.2.val  ≤  max p.val (n.val + 511)  ∧ 
      (p.val < n.val  →  t.val < slot.Z7.val  →  p.val < r.2.2.val)  ∧ 
      (r.2.2.val < n.val  →  p.val + (slot.Z7.val - t.val)  ≤  r.2.2.val) ⦄ := by
  have hB := EA.EA.u159
  rw [slot.Z219_loop0_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, t') => slot.Z7.val - t'.val)
    (inv := fun (_, _, p', t') => p.val + (t'.val - t.val)  ≤  p'.val  ∧  t.val  ≤  t'.val  ∧ 
      p'.val  ≤  max p.val (n.val + 511)  ∧  t'.val  ≤  max t.val slot.Z7.val)
  · rintro ⟨lf', df', p', t'⟩ ⟨h1, h2, h3, h4⟩
    simp only [slot.Z219_loop0_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · exact ⟨by simp, le_refl _, by (subst_vars;scalar_tac (simpAllMaxSteps := 0)), by (subst_vars;scalar_tac (simpAllMaxSteps := 0))⟩
@[local step]
theorem u537 (s:I) (choice models bstart) (tax ulen udist tokpen:W)
    (total:Std.U64) (n:R) (lf df) (p:R)
    (hn:n.val  ≤  s.length) (hnc:n.val  ≤  choice.length) (hn26:n.val < 67108864)
    (htax:tax.val  ≤  65536) (hulen:ulen.val  ≤  65536) (hud:udist.val  ≤  65536) (htok:tokpen.val  ≤  65536)
    (hb:544 * bstart.length  ≤  models.length + 544)
    (ht:544 * total.val  ≤  models.length * (70 + 288 * 2 ^ 42))
    (hm:models.length * 8192 < 544 * (n.val + 8192))
    (hp:p.val < n.val  →  models.length * 8192  ≤  544 * p.val) :
    slot.Z219_loop0 s choice models bstart tax ulen udist tokpen total n lf df p ⦃ fun r =>
      544 * r.2.1.length  ≤  r.1.length + 544  ∧  544 * r.2.2.1.val  ≤  r.1.length * (70 + 288 * 2 ^ 42)  ∧ 
      r.1.length * 8192 < 544 * (n.val + 8192) ⦄ := by
  have hB := EA.EA.u159
  rw [slot.Z219_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, _, p') => n.val - p'.val)
    (inv := fun (m', b', t', _, _, p') => 544 * b'.length  ≤  m'.length + 544  ∧ 
      544 * t'.val  ≤  m'.length * (70 + 288 * 2 ^ 42)  ∧  m'.length * 8192 < 544 * (n.val + 8192)  ∧ 
      (p'.val < n.val  →  m'.length * 8192  ≤  544 * p'.val))
  · rintro ⟨m', b', t', lf', df', p'⟩ ⟨h1, h2, h3, h4⟩
    simp only [slot.Z219_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · exact ⟨hb, ht, hm, hp⟩
@[local step]
theorem u538 (s:I) (choice models bstart) (tax ulen udist tokpen:W)
    (hn26:s.length < 67108864) (htax:tax.val  ≤  65536) (hulen:ulen.val  ≤  65536) (hud:udist.val  ≤  65536)
    (htok:tokpen.val  ≤  65536) :
    slot.Z219 s choice models bstart tax ulen udist tokpen ⦃ fun r => r.2.2.length  ≤  1048576 ⦄ := Y127U17! slot.Z219
@[local step]
theorem u539 (choice n p) :
    slot.Z204_loop0 choice n p ⦃ Y112P0! ⦄ := by
  rw [slot.Z204_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (choice_, p_) => n.val - p_.val)
    (inv := fun _ => True)
  · rintro ⟨choice_, p_⟩ _
    simp only [slot.Z204_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · trivial
@[local step]
theorem u540 (clist choice n gmin) (m k:R) (hm:m.val = clist.length) (hk:1  ≤  k.val) :
    slot.Z204_loop1 clist choice n gmin m k ⦃ Y112P0! ⦄ := by
  rw [slot.Z204_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, k') => m.val - k'.val)
    (inv := fun (_, k') => 1  ≤  k'.val)
  · rintro ⟨choice', k'⟩ hk'
    simp only [slot.Z204_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · exact hk
@[local step]
theorem u541 (clist choice n gmin) :
    slot.Z204 clist choice n gmin ⦃ Y112P0! ⦄ := Y127U17! slot.Z204
@[local step]
theorem u542 (models:alloc.vec.Vec W) (lit_c len_c) (base i:R) (hb:base.val + slot.Z33.val  ≤  models.length) :
    slot.Z208_loop0 models lit_c len_c base i ⦃ Y112P0! ⦄ := by
  rw [slot.Z208_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (lit_c_, len_c_, i_) => 256 - i_.val)
    (inv := fun _ => True)
  · rintro ⟨lit_c_, len_c_, i_⟩ _
    simp only [slot.Z208_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · trivial
@[local step]
theorem u543 (models:alloc.vec.Vec W) (dst_c) (base d:R) (hb:base.val + slot.Z33.val  ≤  models.length) :
    slot.Z208_loop1 models dst_c base d ⦃ Y112P0! ⦄ := by
  rw [slot.Z208_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (dst_c_, d_) => 32 - d_.val)
    (inv := fun _ => True)
  · rintro ⟨dst_c_, d_⟩ _
    simp only [slot.Z208_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · trivial
@[local step]
theorem u544 (models) (b:R) (lit_c len_c dst_c) (hb:b.val  ≤  1048576) :
    slot.Z208 models b lit_c len_c dst_c ⦃ Y112P0! ⦄ := Y127U17! slot.Z208
@[local step]
theorem u545 (clist ge) :
    slot.Z205 clist ge ⦃ fun r => r.val  ≤  ge.val ⦄ := Y127U17! slot.Z205
@[local step]
theorem u546 (bstart:alloc.vec.Vec W) (b q:R) (hb:b.val < bstart.length) :
    slot.Z196_loop0_loop0 bstart b q ⦃ fun r => r.val  ≤  b.val ⦄ := by
  rw [slot.Z196_loop0_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun b' => b'.val)
    (inv := fun b' => b'.val  ≤  b.val)
  · rintro b' hb'
    simp only [slot.Z196_loop0_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · exact le_refl _
@[local step]
theorem u547 (s:I) (choice:U) (ring lit_c next) (p lo:R)
    (hp:p.val  ≤  s.length) (hc:s.length  ≤  choice.length) :
    slot.Z196_loop0_loop1 s choice ring lit_c next p lo ⦃ fun r => r.1.length = choice.length  ∧  r.2.2.2.val  ≤  p.val ⦄ := by
  rw [slot.Z196_loop0_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, p') => p'.val)
    (inv := fun (c', _, _, p') => c'.length = choice.length  ∧  p'.val  ≤  p.val)
  · rintro ⟨c', r', n', p'⟩ ⟨h1, h2⟩
    simp only [slot.Z196_loop0_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · exact ⟨rfl, le_refl _⟩
@[local step]
theorem u548 (ring len_c) (p:R) (best ch) (l:R) (dc tag) (len:R)
    (hp:p.val  ≤  2 ^ 30) (hl:l.val  ≤  511) (hlen:3  ≤  len.val) :
    slot.Z196_loop0_loop2_loop0 ring len_c p best ch l dc tag len ⦃ Y112P0! ⦄ := by
  rw [slot.Z196_loop0_loop2_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, len') => l.val + 1 - len'.val)
    (inv := fun (_, _, len') => 3  ≤  len'.val)
  · rintro ⟨b', c', len'⟩ h1
    simp only [slot.Z196_loop0_loop2_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · exact hlen
@[local step]
theorem u549 (clist ring len_c dst_c) (ge p:R) (best ch) (prev room k:R)
    (hp:p.val  ≤  2 ^ 30) (hprev:2  ≤  prev.val  ∧  prev.val  ≤  511)
    (hk:k.val  ≤  clist.length) (hcl:clist.length < 4294967295) :
    slot.Z196_loop0_loop2 clist ring len_c dst_c ge p best ch prev room k ⦃ Y112P0! ⦄ := by
  rw [slot.Z196_loop0_loop2]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, k') => clist.length - k'.val)
    (inv := fun (_, _, prev', k') => 2  ≤  prev'.val  ∧  prev'.val  ≤  511  ∧  k'.val  ≤  clist.length)
  · rintro ⟨b', c', prev', k'⟩ ⟨h1, h2, h3⟩
    simp only [slot.Z196_loop0_loop2.body]
    step*
    apply WP.spec_bind (Pₘ := fun (x:R) => 2  ≤  x.val  ∧  x.val  ≤  511)
    · repeat' (split <;> step*)
      all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
    rintro prev1 ⟨hq1, hq2⟩
    step*
    apply WP.spec_bind (Pₘ := fun (x:R) => x.val  ≤  511)
    · split <;> step*
      all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
    rintro l1 hl1
    step*
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · exact ⟨hprev.1, hprev.2, hk⟩
@[local step]
theorem u550 (s:I) (clist models:alloc.vec.Vec W) (bstart:alloc.vec.Vec W) (choice:U)
    (n:R) (ring lit_c len_c dst_c) (b loaded ge gs gp:R) (next) (p fuel:R)
    (hn:n.val = s.length) (hn26:n.val < 67108864) (hc:n.val  ≤  choice.length) (hb:b.val < bstart.length)
    (hnb:bstart.length  ≤  1048576) (hp:p.val  ≤  n.val) (hgp:gp.val  ≤  n.val  ∨  gp.val < 2 ^ 27)
    (hcl:clist.length < 4294967295) (hgs:gs.val  ≤  ge.val) (hge:ge.val  ≤  clist.length) :
    slot.Z196_loop0 s clist models bstart choice n ring lit_c len_c dst_c b loaded ge gs gp next p fuel ⦃ Y112P0! ⦄ := by
  have hpm := EA.EA.u162
  rw [slot.Z196_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, _, _, _, _, _, _, _, _, f) => f.val)
    (inv := fun (c', _, _, _, _, b', _, ge', gs', gp', _, p', _) => c'.length = choice.length  ∧ 
      b'.val < bstart.length  ∧  p'.val  ≤  n.val  ∧  (gp'.val  ≤  n.val  ∨  gp'.val < 2 ^ 27)  ∧ 
      gs'.val  ≤  ge'.val  ∧  ge'.val  ≤  clist.length)
  · rintro ⟨c', r', l1', l2', d', b', ld', ge', gs', gp', nx', p', f'⟩ ⟨h1, h2, h3, h4, h5, h6⟩
    simp only [slot.Z196_loop0.body]
    step*
    apply WP.spec_bind (Pₘ := fun _ => True)
    · split <;> step*
    rintro ⟨lit_c1, len_c1, dst_c1, loaded1⟩ _
    step*
    apply WP.spec_bind (Pₘ := fun _ => True)
    · repeat' (split <;> step*)
    rintro lo _
    step*
    apply WP.spec_bind (Pₘ := fun _ => True)
    · split <;> step*
    rintro ⟨best1, ch1⟩ _
    step*
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · exact ⟨rfl, hb, hp, hgp, hgs, hge⟩
@[local step]
theorem u551 (s:I) (clist models) (bstart:alloc.vec.Vec W) (choice)
    (hn26:s.length < 67108864) (hnb:bstart.length  ≤  1048576) (hcl:clist.length < 4294967295) :
    slot.Z196 s clist models bstart choice ⦃ Y112P0! ⦄ := by
  have hms := EA.EA.u161
  have hpm := EA.EA.u162
  rw [slot.Z196]
  step*
  repeat' (split <;> step*)
  all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
@[local step]
theorem u552 (len) (d:R) (hd:1  ≤  d.val):slot.Z211 len d ⦃ Y112P0! ⦄ := Y127U17! slot.Z211
@[local step]
theorem u553 (clist:alloc.vec.Vec W) (ml md) (cnt:R) (flag) (top:R)
    (pushed:W) (i:R)
    (hcl:clist.length + (cnt.val - i.val) < 4294967295) (hpu:pushed.val  ≤  1) :
    slot.Z214_loop clist ml md cnt flag top pushed i ⦃ fun r =>
      r.1.length  ≤  clist.length + (cnt.val - i.val)  ∧  r.2.2.val  ≤  pushed.val + (cnt.val - i.val)  ∧ 
      (top.val  ≤  258  →  r.2.1.val  ≤  258) ⦄ := by
  rw [slot.Z214_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, i') => 64 - i'.val)
    (inv := fun (c', t', u', i') => c'.length + (cnt.val - i'.val)  ≤  clist.length + (cnt.val - i.val)  ∧ 
      u'.val + (cnt.val - i'.val)  ≤  pushed.val + (cnt.val - i.val)  ∧  i.val  ≤  i'.val  ∧ 
      (top.val  ≤  258  →  t'.val  ≤  258))
  · rintro ⟨c', t', u', i'⟩ ⟨h1, h2, h3, h4⟩
    simp only [slot.Z214_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · exact ⟨le_refl _, le_refl _, le_refl _, fun h => h⟩
@[local step]
theorem u554 (clist:alloc.vec.Vec W) (p ml md cnt r1 flag)
    (hcl:clist.length + slot.Z4.val + 2 < 4294967295) :
    slot.Z214 clist p ml md cnt r1 flag ⦃ fun r => r.2.length  ≤  clist.length + slot.Z4.val + 2  ∧ 
      r.1.val  ≤  258 ⦄ := Y127U17! slot.Z214
@[local step]
theorem u555 (b) :
    slot.Z210 b ⦃ Y112P0! ⦄ := Y127U17! slot.Z210
@[local step]
theorem u556 (s) (i:R) (hi:i.val + 8  ≤  Usize.max):slot.Z222 s i ⦃ Y112P0! ⦄ := Y127U17! slot.Z222
set_option hygiene false in
local notation "Y127U18!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun k_ => lim.val - k_.val)
    (inv := fun _ => True)
  · rintro k_ _
    simp only [q1__]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · trivial)
@[local step]
theorem u557 (s:I) (a b lim k:R) (ha:a.val + lim.val  ≤  s.length) (hb:b.val + lim.val  ≤  s.length) :
    slot.Z200_loop0_loop0 s a b lim k ⦃ Y112P0! ⦄ := Y127U18! slot.Z200_loop0_loop0 slot.Z200_loop0_loop0.body
@[local step]
theorem u558 (s:I) (a b lim k:R) (ha:a.val + lim.val  ≤  s.length) (hb:b.val + lim.val  ≤  s.length) :
    slot.Z200_loop0_loop1 s a b lim k ⦃ Y112P0! ⦄ := Y127U18! slot.Z200_loop0_loop1 slot.Z200_loop0_loop1.body
@[local step]
theorem u559 (s:I) (a b lim k fuel:R) (ha:a.val + lim.val  ≤  s.length)
    (hb:b.val + lim.val  ≤  s.length) (hk:k.val  ≤  2 ^ 31) (hlim:lim.val  ≤  2 ^ 31) :
    slot.Z200_loop0 s a b lim k fuel ⦃ Y112P0! ⦄ := by
  rw [slot.Z200_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, f') => f'.val)
    (inv := fun (k', _) => k'.val  ≤  2 ^ 31)
  · rintro ⟨k', f'⟩ hk'
    simp only [slot.Z200_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · exact hk
@[local step]
theorem u560 (s:I) (a b k0 lim:R) (ha:a.val + lim.val  ≤  s.length) (hb:b.val + lim.val  ≤  s.length)
    (hk0:k0.val  ≤  2 ^ 31) (hlim:lim.val  ≤  2 ^ 31) :
    slot.Z200 s a b k0 lim ⦃ Y112P0! ⦄ := Y127U17! slot.Z200
@[local step]
theorem u561 (s:I) (p k0 depth:R) (prev ml md) (lim cur best cnt steps:R)
    (hp:p.val + lim.val  ≤  s.length) (hlim:lim.val  ≤  258) (hk0:k0.val  ≤  2 ^ 31) :
    slot.Z194_loop s p k0 depth prev ml md lim cur best cnt steps ⦃ Y112P0! ⦄ := by
  have hws := Submission.EA.EA.C_WS_val
  rw [slot.Z194_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, _, st) => depth.val - st.val)
    (inv := fun _ => True)
  · rintro ⟨ml', md', cur', best', cnt', st'⟩ _
    simp only [slot.Z194_loop.body]
    step*
    apply WP.spec_bind (Pₘ := fun _ => True)
    · repeat' (split <;> step*)
      all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
    rintro ⟨ml1, md1, best1, cnt1⟩ _
    step*
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · trivial
set_option hygiene false in
local notation "Y127U19!" q0__:max => (by
  have hws := Submission.EA.EA.C_WS_val
  have hhs := Submission.EA.EA.C_HS_bounds
  rw [q0__]
  step*
  repeat' (split <;> step*)
  all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0)))
@[local step]
theorem u562 (s:I) (p key k0 best0 depth head prev ml md) (hp:p.val < s.length) (hk0:k0.val  ≤  2 ^ 31) :
    slot.Z194 s p key k0 best0 depth head prev ml md ⦃ Y112P0! ⦄ := Y127U19! slot.Z194
@[local step]
theorem u563 (kids) (which:R) (idx v) (hw:which.val  ≤  1) :
    slot.Z216 kids which idx v ⦃ Y112P0! ⦄ := by
  have hws := Submission.EA.EA.C_WS_val
  have hks := EA.EA.u160
  rw [slot.Z216]
  step*
  repeat' (split <;> step*)
  all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
@[local step]
theorem u564 (back) (s:I) (p depth kids ml md) (lim cur lw li gw gi llen glen:R)
    (best cnt steps i)
    (hp:p.val + lim.val  ≤  s.length) (hlim:lim.val  ≤  258) (hlw:lw.val  ≤  1) (hgw:gw.val  ≤  1)
    (hll:llen.val  ≤  lim.val) (hgl:glen.val  ≤  lim.val) :
    slot.Z193_loop back s p depth kids ml md lim cur lw li gw gi llen glen best cnt steps i ⦃ Y112P0! ⦄ := by
  have hws := Submission.EA.EA.C_WS_val
  have hks := EA.EA.u160
  rw [slot.Z193_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, _, _, _, _, _, _, _, _, st) => depth.val - st.val)
    (inv := fun (_, _, _, _, lw', _, gw', _, ll', gl', _, _, _) => lw'.val  ≤  1  ∧  gw'.val  ≤  1  ∧ 
      ll'.val  ≤  lim.val  ∧  gl'.val  ≤  lim.val)
  · rintro ⟨kids', ml', md', cur', lw', li', gw', gi', ll', gl', best', cnt', st'⟩ ⟨h1, h2, h3, h4⟩
    simp only [slot.Z193_loop.body]
    step*
    apply WP.spec_bind (Pₘ := fun (x:R) => x.val  ≤  lim.val)
    · split <;> step*
      all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
    rintro k0 hk0
    step*
    apply WP.spec_bind (Pₘ := fun _ => True)
    · repeat' (split <;> step*)
      all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
    rintro ⟨ml1, md1, best1, cnt1⟩ _
    step*
    apply WP.spec_bind (Pₘ := fun (x:Std.Array W 65536#usize  ×  R  ×  R  ×  R  × 
        R  ×  R  ×  R  ×  R) =>
      x.2.2.1.val  ≤  1  ∧  x.2.2.2.2.1.val  ≤  1  ∧  x.2.2.2.2.2.2.1.val  ≤  lim.val  ∧  x.2.2.2.2.2.2.2.val  ≤  lim.val)
    · split <;> step*
      all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
    rintro ⟨kids1, cur1, lw1, li1, gw1, gi1, llen1, glen1⟩ ⟨h5, h6, h7, h8⟩
    step*
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · exact ⟨hlw, hgw, hll, hgl⟩
@[local step]
theorem u565 (s:I) (p h depth head kids ml md) (hp:p.val < s.length) :
    slot.Z193 s p h depth head kids ml md ⦃ Y112P0! ⦄ := Y127U19! slot.Z193
@[local step]
theorem u566 (s:I) (n key:R) (run run2 q:R) (hn:n.val = s.length)
    (hrun:run.val  ≤  q.val) (hrun2:run2.val  ≤  q.val) (hq:q.val  ≤  7) :
    slot.Z202_loop0 s n key run run2 q ⦃ fun r => r.2.1.val  ≤  7  ∧  r.2.2.val  ≤  7 ⦄ := by
  rw [slot.Z202_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, q') => 7 - q'.val)
    (inv := fun (_, r1, r2, q') => r1.val  ≤  q'.val  ∧  r2.val  ≤  q'.val  ∧  q'.val  ≤  7)
  · rintro ⟨k', r1, r2, q'⟩ ⟨h1, h2, h3⟩
    simp only [slot.Z202_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · exact ⟨hrun, hrun2, hq⟩
@[local step]
theorem u567 (s:I) (clist) (depth_lo n:R) (head8 prev8 head3 kids ml md)
    (key run run2 p skip_to:R)
    (hn:n.val = s.length) (hn26:n.val < 67108864) (hrun:run.val  ≤  p.val + 7) (hrun2:run2.val  ≤  p.val + 7)
    (hp:p.val  ≤  n.val) (hcl:clist.length  ≤  34 * p.val) :
    slot.Z202_loop1 s clist depth_lo n head8 prev8 head3 kids ml md key run run2 p skip_to ⦃ fun r =>
      r.length  ≤  34 * n.val ⦄ := by
  have hws := Submission.EA.EA.C_WS_val
  have hhs := Submission.EA.EA.C_HS_bounds
  have hkp := EA.EA.u163
  have hup := EA.EA.u172
  rw [slot.Z202_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, _, _, _, _, _, _, p', _) => n.val - p'.val)
    (inv := fun (c', _, _, _, _, _, _, _, r1, r2, p', _) => r1.val  ≤  p'.val + 7  ∧  r2.val  ≤  p'.val + 7  ∧ 
      p'.val  ≤  n.val  ∧  c'.length  ≤  34 * p'.val)
  · rintro ⟨c', h8', pv8', h3', kids', ml', md', key', r1, r2, p', sk'⟩ ⟨h1, h2, h3, h4⟩
    unfold slot.Z202_loop1.body
    step*
    apply WP.spec_bind (Pₘ := fun (x:R  ×  R  ×  R) =>
      x.2.1.val  ≤  p'.val + 8  ∧  x.2.2.val  ≤  p'.val + 8)
    · repeat' (split <;> step*)
      all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
    rintro ⟨key1, run1, run21⟩ ⟨hr1, hr2⟩
    step*
    apply WP.spec_bind (Pₘ := fun (x:alloc.vec.Vec W  ×  Std.Array W 65536#usize  × 
        Std.Array W 32768#usize  ×  Std.Array W 65536#usize  ×  Std.Array W 65536#usize  × 
        Std.Array W 64#usize  ×  Std.Array W 64#usize  ×  R) =>
      x.1.length  ≤  c'.length + 34)
    · apply EA.EA.u188
      · intro hc
        step*
        · -- a lower-case letter: binary tree on 3-byte keys
          apply WP.spec_bind (Pₘ := fun (x:alloc.vec.Vec W  ×  _) => x.1.length  ≤  c'.length + 34)
          · apply EA.EA.u188
            · intro hs
              step*
              apply WP.spec_bind (Pₘ := fun (x:alloc.vec.Vec W  ×  _) => x.1.length  ≤  c'.length + 34)
              · apply EA.EA.u188
                · intro hcnt
                  step*
                  apply EA.EA.u189 <;> intro _ <;> step*
                · intro hcnt
                  step*
              · rintro ⟨v2, a4, a5, i17⟩ hv2
                step*
            · intro hs
              step*
          · rintro ⟨v1, a, a1, a2, a3, i16⟩ hv1
            step*
        · -- any other byte above 'z'
          apply WP.spec_bind (Pₘ := fun (x:alloc.vec.Vec W  ×  _) => x.1.length  ≤  c'.length + 34)
          · apply EA.EA.u188
            · -- a run of at least 8 nucleotides: exact 8-mer chains
              intro hr
              apply WP.spec_bind (Pₘ := fun (x:alloc.vec.Vec W  ×  _) => x.1.length  ≤  c'.length + 34)
              · apply EA.EA.u188
                · intro hs
                  step*
                  apply WP.spec_bind (Pₘ := fun (x:alloc.vec.Vec W  ×  _) => x.1.length  ≤  c'.length + 34)
                  · apply EA.EA.u188
                    · intro hcnt
                      step*
                      apply EA.EA.u189 <;> intro _ <;> step*
                    · intro hcnt
                      step*
                  · rintro ⟨v2, a9, a10, i5⟩ hv2
                    step*
                · intro hs
                  step*
              · rintro ⟨v1, a5, a6, a7, a8, i3⟩ hv1
                step*
            · -- other runs (newlines allowed): chains on whole words
              intro hr
              apply WP.spec_bind (Pₘ := fun (x:alloc.vec.Vec W  ×  _) => x.1.length  ≤  c'.length + 34)
              · apply EA.EA.u188
                · intro hr2
                  step*
                  apply WP.spec_bind (Pₘ := fun (x:alloc.vec.Vec W  ×  _) => x.1.length  ≤  c'.length + 34)
                  · apply EA.EA.u188
                    · intro hcnt
                      step*
                      apply EA.EA.u189 <;> intro _ <;> step*
                    · intro hcnt
                      step*
                  · rintro ⟨v2, a9, a10, i10⟩ hv2
                    step*
                · intro hr2
                  step*
              · rintro ⟨v1, a5, a6, a7, a8, i3⟩ hv1
                step*
          · rintro ⟨v, a, a1, a2, a3, a4, i2⟩ hv
            step*
        · -- any other byte below 'a'
          apply WP.spec_bind (Pₘ := fun (x:alloc.vec.Vec W  ×  _) => x.1.length  ≤  c'.length + 34)
          · apply EA.EA.u188
            · -- a run of at least 8 nucleotides: exact 8-mer chains
              intro hr
              apply WP.spec_bind (Pₘ := fun (x:alloc.vec.Vec W  ×  _) => x.1.length  ≤  c'.length + 34)
              · apply EA.EA.u188
                · intro hs
                  step*
                  apply WP.spec_bind (Pₘ := fun (x:alloc.vec.Vec W  ×  _) => x.1.length  ≤  c'.length + 34)
                  · apply EA.EA.u188
                    · intro hcnt
                      step*
                      apply EA.EA.u189 <;> intro _ <;> step*
                    · intro hcnt
                      step*
                  · rintro ⟨v2, a9, a10, i5⟩ hv2
                    step*
                · intro hs
                  step*
              · rintro ⟨v1, a5, a6, a7, a8, i3⟩ hv1
                step*
            · -- other runs (newlines allowed): chains on whole words
              intro hr
              apply WP.spec_bind (Pₘ := fun (x:alloc.vec.Vec W  ×  _) => x.1.length  ≤  c'.length + 34)
              · apply EA.EA.u188
                · intro hr2
                  step*
                  apply WP.spec_bind (Pₘ := fun (x:alloc.vec.Vec W  ×  _) => x.1.length  ≤  c'.length + 34)
                  · apply EA.EA.u188
                    · intro hcnt
                      step*
                      apply EA.EA.u189 <;> intro _ <;> step*
                    · intro hcnt
                      step*
                  · rintro ⟨v2, a9, a10, i10⟩ hv2
                    step*
                · intro hr2
                  step*
              · rintro ⟨v1, a5, a6, a7, a8, i3⟩ hv1
                step*
          · rintro ⟨v, a, a1, a2, a3, a4, i2⟩ hv
            step*
      · intro hc
        step*
    rintro ⟨clist1, head81, prev81, head31, kids1, ml1, md1, skip_to1⟩ hc1
    step*
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · exact ⟨hrun, hrun2, hp, hcl⟩
@[local step]
theorem u568 (s:I) (clist) (depth_lo) (hn26:s.length < 67108864) (hcl:clist.length = 0) :
    slot.Z202 s clist depth_lo ⦃ fun r => r.length  ≤  34 * s.length ⦄ := by
  rw [slot.Z202]
  step*
@[local step]
theorem u569 (s:I) (p:R) (hp:p.val  ≤  2 ^ 31):slot.Z221 s p ⦃ Y112P0! ⦄ := Y127U17! slot.Z221
@[local step]
theorem u570 (s:I) (clist) (chain depth n:R) (head lt kids ml md)
    (p skip_to pend:R)
    (hn:n.val = s.length) (hn26:n.val < 67108864) (hp:p.val  ≤  n.val) (hcl:clist.length  ≤  34 * p.val) :
    slot.Z201_loop s clist chain depth n head lt kids ml md p skip_to pend ⦃ fun r => r.length  ≤  34 * n.val ⦄ := by
  have hws := Submission.EA.EA.C_WS_val
  have hhs := Submission.EA.EA.C_HS_bounds
  have hkp := EA.EA.u163
  rw [slot.Z201_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, _, _, p', _, _) => n.val - p'.val)
    (inv := fun (c', _, _, _, _, _, p', _, _) => p'.val  ≤  n.val  ∧  c'.length  ≤  34 * p'.val)
  · rintro ⟨c', hd', lt', kids', ml', md', p', sk', pe'⟩ ⟨h1, h2⟩
    unfold slot.Z201_loop.body
    step*
    apply WP.spec_bind (Pₘ := fun _ => True)
    · split <;> step*
    rintro key _
    step*
    apply WP.spec_bind (Pₘ := fun (x:alloc.vec.Vec W  ×  Std.Array W 65536#usize  × 
        Std.Array W 32768#usize  ×  Std.Array W 65536#usize  ×  Std.Array W 64#usize  × 
        Std.Array W 64#usize  ×  R  ×  R) =>
      x.1.length  ≤  c'.length + 34)
    · split
      · -- p  ≥  skip_to: search, push the candidates, maybe skip ahead
        step*
        apply WP.spec_bind (Pₘ := fun _ => True)
        · split <;> step*
        rintro ⟨head2, lt2, kids2, ml2, md2, cnt⟩ _
        step*
        apply WP.spec_bind (Pₘ := fun _ => True)
        · repeat' (split <;> step*)
        rintro r1 _
        step*
        apply WP.spec_bind (Pₘ := fun (x:alloc.vec.Vec W  ×  R) =>
          x.1.length  ≤  c'.length + 34  ∧  x.2.val  ≤  258)
        · repeat' (split <;> step*)
          all_goals scalar_tac
        rintro ⟨clist2, top⟩ ⟨hc2, htop⟩
        step*
        apply WP.spec_bind (Pₘ := fun _ => True)
        · repeat' (split <;> step*)
          all_goals scalar_tac
        rintro ⟨i19, i20⟩ _
        step*
      · -- inside a skipped stretch: only the chain insert
        step*
        apply WP.spec_bind (Pₘ := fun _ => True)
        · split <;> step*
        rintro ⟨a, a1⟩ _
        step*
    rintro ⟨clist1, head1, lt1, kids1, ml1, md1, skip_to1, pend1⟩ hc1
    step*
    all_goals scalar_tac
  · exact ⟨hp, hcl⟩
@[local step]
theorem u571 (s:I) (clist chain depth) (hn26:s.length < 67108864) (hcl:clist.length = 0) :
    slot.Z201 s clist chain depth ⦃ fun r => r.length  ≤  34 * s.length ⦄ := by
  rw [slot.Z201]
  step*
set_option hygiene false in
local notation "Y127U20!" q0__:max q1__:max => (by
  have h1 := Submission.EA.EA.C_UNUSED_LIT_le
  have h2 := Submission.EA.EA.C_UNUSED_DIST_le
  have h3 := Submission.EA.EA.C_STOP_DIV_pos
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, pass') => passes.val - pass'.val)
    (inv := fun (_, _, b', _, _) => b'.length  ≤  1048576)
  · rintro ⟨out', models', b', le', pass'⟩ hb'
    simp only [q1__]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · exact hnb)
@[local step]
theorem u572 (input:I) (out min_dna dna) (clist:alloc.vec.Vec W) (models)
    (bstart:alloc.vec.Vec W) (passes) (tax tokpen:W) (last_est pass)
    (hn26:input.length < 67108864) (htax:tax.val  ≤  65536) (htok:tokpen.val  ≤  65536)
    (hnb:bstart.length  ≤  1048576) (hcl:clist.length < 4294967295) :
    slot.Z199_loop0 input out min_dna dna clist models bstart passes tax tokpen last_est pass ⦃ Y112P0! ⦄ := Y127U20! slot.Z199_loop0 slot.Z199_loop0.body
@[local step]
theorem u573 (input:I) (out min_dna dna) (clist:alloc.vec.Vec W) (models)
    (bstart:alloc.vec.Vec W) (passes) (tax tokpen:W) (last_est pass)
    (hn26:input.length < 67108864) (htax:tax.val  ≤  65536) (htok:tokpen.val  ≤  65536)
    (hnb:bstart.length  ≤  1048576) (hcl:clist.length < 4294967295) :
    slot.Z199_loop1 input out min_dna dna clist models bstart passes tax tokpen last_est pass ⦃ Y112P0! ⦄ := Y127U20! slot.Z199_loop1 slot.Z199_loop1.body
@[local step]
theorem u574 (input:I) (out min_dna dna) (clist:alloc.vec.Vec W) (models)
    (bstart:alloc.vec.Vec W) (passes) (tax tokpen:W) (last_est pass)
    (hn26:input.length < 67108864) (htax:tax.val  ≤  65536) (htok:tokpen.val  ≤  65536)
    (hnb:bstart.length  ≤  1048576) (hcl:clist.length < 4294967295) :
    slot.Z199_loop2 input out min_dna dna clist models bstart passes tax tokpen last_est pass ⦃ Y112P0! ⦄ := Y127U20! slot.Z199_loop2 slot.Z199_loop2.body
@[local step]
theorem u575 (input:I) (out) (depth depth_lo wdp passes_w passes_bt passes_dna min_dna passes_c4:R)
    (hn:input.length < 67108864) (h1:depth.val  ≤  65536) (h2:depth_lo.val  ≤  65536) (h3:wdp.val  ≤  65536)
    (h4:passes_w.val  ≤  65536) (h5:passes_bt.val  ≤  65536) (h6:passes_dna.val  ≤  65536) (h7:min_dna.val  ≤  65536)
    (h8:passes_c4.val  ≤  65536) :
    slot.Z199 input out depth depth_lo wdp passes_w passes_bt passes_dna min_dna passes_c4 ⦃ Y112P0! ⦄ := by
  have f1 := EA.EA.u167
  have f2 := EA.EA.u167
  have f3 := EA.EA.u168
  have f4 := EA.EA.u165
  have f5 := EA.EA.u166
  have f6 := EA.EA.u169
  have f7 := EA.EA.u169
  have f8 := EA.EA.u170
  have f9 := EA.EA.u169
  have f10 := Submission.EA.EA.C_UNUSED_LIT_le
  have f11 := Submission.EA.EA.C_UNUSED_DIST_le
  have f12 := EA.EA.u171
  rw [slot.Z199]
  step*
  · -- dna = 0, few 6-byte repeats: weights DP (4-byte chains)
    apply WP.spec_bind (Pₘ := fun (x:alloc.vec.Vec W) => x.length  ≤  34 * input.length)
    · repeat' (split <;> step*)
      all_goals exact EA.EA.u187 _
    rintro clist1 hc1
    apply WP.spec_bind (Pₘ := fun _ => True)
    · repeat' (split <;> step*)
    rintro passes _
    apply WP.spec_bind (Pₘ := fun (x:W) => x.val  ≤  65536)
    · repeat' (split <;> step*)
      all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
    rintro tax htax
    apply WP.spec_bind (Pₘ := fun (x:W) => x.val  ≤  65536)
    · repeat' (split <;> step*)
      all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
    rintro ulen hulen
    apply WP.spec_bind (Pₘ := fun (x:W) => x.val  ≤  65536)
    · repeat' (split <;> step*)
      all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
    rintro udist hudist
    apply WP.spec_bind (Pₘ := fun _ => True)
    · repeat' (split <;> step*)
    rintro gmin _
    step*
    apply WP.spec_bind (Pₘ := fun (x:alloc.vec.Vec W  ×  W) => x.2.val  ≤  65536)
    · repeat' (split <;> step*)
      all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
    rintro ⟨out1, tokpen⟩ htok
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · -- dna = 0, repetitive: tree or 4-byte chains
    apply WP.spec_bind (Pₘ := fun _ => True)
    · repeat' (split <;> step*)
      all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
    rintro chain4 _
    step*
    apply WP.spec_bind (Pₘ := fun (x:alloc.vec.Vec W) => x.length  ≤  34 * input.length)
    · repeat' (split <;> step*)
      all_goals exact EA.EA.u187 _
    rintro clist1 hc1
    apply WP.spec_bind (Pₘ := fun _ => True)
    · repeat' (split <;> step*)
    rintro passes _
    apply WP.spec_bind (Pₘ := fun (x:W) => x.val  ≤  65536)
    · repeat' (split <;> step*)
      all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
    rintro tax htax
    apply WP.spec_bind (Pₘ := fun (x:W) => x.val  ≤  65536)
    · repeat' (split <;> step*)
      all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
    rintro ulen hulen
    apply WP.spec_bind (Pₘ := fun (x:W) => x.val  ≤  65536)
    · repeat' (split <;> step*)
      all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
    rintro udist hudist
    apply WP.spec_bind (Pₘ := fun _ => True)
    · repeat' (split <;> step*)
    rintro gmin _
    step*
    apply WP.spec_bind (Pₘ := fun (x:alloc.vec.Vec W  ×  W) => x.2.val  ≤  65536)
    · repeat' (split <;> step*)
      all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
    rintro ⟨out1, tokpen⟩ htok
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · -- DNA
    apply WP.spec_bind (Pₘ := fun (x:alloc.vec.Vec W) => x.length  ≤  34 * input.length)
    · repeat' (split <;> step*)
      all_goals exact EA.EA.u187 _
    rintro clist1 hc1
    apply WP.spec_bind (Pₘ := fun _ => True)
    · repeat' (split <;> step*)
    rintro passes _
    apply WP.spec_bind (Pₘ := fun (x:W) => x.val  ≤  65536)
    · repeat' (split <;> step*)
      all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
    rintro tax htax
    apply WP.spec_bind (Pₘ := fun (x:W) => x.val  ≤  65536)
    · repeat' (split <;> step*)
      all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
    rintro ulen hulen
    apply WP.spec_bind (Pₘ := fun (x:W) => x.val  ≤  65536)
    · repeat' (split <;> step*)
      all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
    rintro udist hudist
    apply WP.spec_bind (Pₘ := fun _ => True)
    · repeat' (split <;> step*)
    rintro gmin _
    step*
    apply WP.spec_bind (Pₘ := fun (x:alloc.vec.Vec W  ×  W) => x.2.val  ≤  65536)
    · repeat' (split <;> step*)
      all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
    rintro ⟨out1, tokpen⟩ htok
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
theorem spine_CFG_le:∀ r ∈ slot.Z113.val, ∀ x ∈ r.val, x.val  ≤  65536 := by
  unfold slot.Z113;decide
theorem spine_CFG_skip:∀ r ∈ slot.Z113.val, (r.val[0]!).val = 0  →  3  ≤  (r.val[2]!).val := by
  unfold slot.Z113;decide
@[local step]
theorem u576 (input:I) (k) (hn:input.length < 67108864) :
    slot.Z297 input k ⦃ Y112P0! ⦄ := Y127U21! slot.Z297 slot.Z113.val
@[local step]
theorem u577 (input:I) (k:R):slot.Z303 input k ⦃ Y112P0! ⦄ := by
  rw [slot.Z303]
  step*
theorem u578 (input:I) (out:U) (mode:R)
    (hlen:input.length  ≤  out.length) :
    slot.Z273 input out mode ⦃ Y112P1! ⦄ := by
  rw [slot.Z273]
  step*
  all_goals (first | assumption | (subst_vars;scalar_tac (simpAllMaxSteps := 0)) |
    (refine ⟨by assumption, by assumption, ?_⟩;unfold LZ77.Valid;assumption) |
    (refine ⟨by assumption, by (subst_vars;scalar_tac (simpAllMaxSteps := 0)), ?_⟩;unfold LZ77.Valid;assumption))
attribute [local step] u578
@[local step]
theorem u579 (input:I) (out:U) (mode:R) (hlen:input.length  ≤  out.length):slot.Z296 input out mode ⦃ Y112P1! ⦄ := Y127U14! slot.Z296
end EB
set_option hygiene false in
local notation "Y127U22!" => (by
  refine ⟨?_, ?_, ?_, ?_, ?_⟩ <;> simp only [Std.Array.repeat_val] <;>
    first | exact Submission.EA.EA.LeAll_replicate _ _ _ (by simp) | simp)
namespace EC
open Aeneas Aeneas.Std Result ControlFlow
set_option maxRecDepth 8192
set_option maxHeartbeats 1000000
set_option linter.unusedTactic false
set_option linter.unreachableTactic false
set_option linter.unusedSimpArgs false
set_option linter.unusedVariables false
open LZ77 (toks bytes bytes_getElem! Matches emit_lit emit_match)


@[local scalar_tac x &&& y]
theorem u580 (x y:Nat):x &&& y  ≤  y := Nat.and_le_right
@[local scalar_tac x >>> y]
theorem u581 (x y:Nat):x >>> y  ≤  x := Nat.shiftRight_le x y
@[local scalar_tac System.Platform.numBits]
theorem u582:32  ≤  System.Platform.numBits := EA.EA.u4
@[local scalar_tac core.num.U32.leading_zeros x]
theorem u583 (x:W) :
    (core.num.U32.leading_zeros x).val  ≤  32  ∧ 
      (x.val = 0  ∨  (core.num.U32.leading_zeros x).val  ≤  31) := Y127U15!
@[local scalar_tac core.num.U64.leading_zeros x]
theorem u584 (x:Std.U64):(core.num.U64.leading_zeros x).val  ≤  64 := EA.EA.u12 x





@[local scalar_tac core.num.Usize.saturating_add x y]
theorem u585 (x y:R) :
    (core.num.Usize.saturating_add x y).val = min Std.Usize.max (x.val + y.val) := EA.EA.u38 x y






@[local step]
theorem u586 (cost:U) (lc) (i hi:R) (base best l)
    (hhi:hi.val < 512) (hc:i.val + hi.val < cost.length) :
    slot.Z314_loop cost lc i hi base l best ⦃ Y112P0! ⦄ := Y127U3! slot.Z314_loop slot.Z314_loop.body
@[local step]
theorem u587 (cost:U) (lc i lo hi base width) :
    slot.Z314 cost lc i lo hi base width ⦃ Y112P0! ⦄ := Y127U12! slot.Z314
@[local step]
theorem u588 (pe:R) (cost) (cl z:R) (hpe:pe.val  ≤  2 ^ 31) (hcl:cl.val = cost.length) :
    slot.Z307_loop0 pe cost cl z ⦃ fun r => r.length = cost.length ⦄ := Y127U4! slot.Z307_loop0 slot.Z307_loop0.body
@[local step]
theorem u589 (tail:R) (mb lc dc) (cost:alloc.vec.Vec W) (cl i:R) (bias best bd) (prev pd:R) (j top:R)
    (hcl:cl.val = cost.length) (hi:i.val  ≤  2 ^ 31) (htop:top.val  ≤  mb.length)
    (hprev:prev.val  ≤  i.val + 258) (hpv:i.val  ≤  prev.val) (hpd:pd.val  ≤  32768) (hbd:bd.val  ≤  32767) :
    slot.Z307_loop1_loop0 mb lc dc cost tail cl i bias best bd prev pd j top ⦃ Y112P7! ⦄ := Y127U5! slot.Z307_loop1_loop0 slot.Z307_loop1_loop0.body
@[local step]
theorem u590 (tail:R) (s:I) (mp mb:alloc.vec.Vec W) (p0 lit lc dc) (cost ch:alloc.vec.Vec W)
    (cl i e xl xd:R)
    (hcl:cl.val = cost.length) (hi:i.val < cl.val) (hmp:i.val < mp.length) (hs:i.val  ≤  s.length)
    (hch:i.val  ≤  ch.length) (hi31:i.val  ≤  2 ^ 31) (hxl:xl.val  ≤  258) (hxd:xd.val  ≤  32768) :
    slot.Z307_loop1 s mp mb p0 lit lc dc cost ch tail cl i e xl xd ⦃ Y112P0! ⦄ := Y127U6! slot.Z307_loop1 slot.Z307_loop1.body
@[local step]
theorem u591 (tail:R) (s:I) (mp mb) (p0 pe:R) (lit lc dc) (cost ch)
    (hpe:pe.val  ≤  2 ^ 31) :
    slot.Z307 s mp mb p0 pe lit lc dc cost ch tail ⦃ Y112P0! ⦄ := Y127U12! slot.Z307
@[local step]
theorem u592 (lf zf b) :
    slot.Z309_loop0_loop0 lf zf b ⦃ Y112P0! ⦄ := Y127U7! slot.Z309_loop0_loop0 slot.Z309_loop0_loop0.body
@[local step]
theorem u593 (df zd b) :
    slot.Z309_loop0_loop1 df zd b ⦃ Y112P0! ⦄ := Y127U8! slot.Z309_loop0_loop1 slot.Z309_loop0_loop1.body
@[local step]
theorem u594 (tail:R) (s:I) (mp mb) (pe:R) (lit lc dc cost ch lf df zf zd) (sb st a:R)
    (hpe:pe.val  ≤  2 ^ 30) (hps:pe.val  ≤  s.length) (hsb:sb.val  ≤  a.val) (hst:st.val  ≤  a.val)
    (ha:a.val  ≤  pe.val + slot.Z5.val * slot.Z4.val) :
    slot.Z309_loop0 s mp mb pe lit lc dc cost ch lf df tail zf zd sb st a ⦃ Y112P0! ⦄ := by
  have hseg := EA.EA.u34
  rw [slot.Z309_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, _, _, _, _, a_) => pe.val - a_.val)
    (inv := fun (_, _, _, _, _, _, sb_, st_, a_) => sb_.val  ≤  a_.val  ∧  st_.val  ≤  a_.val  ∧ 
      a_.val  ≤  pe.val + slot.Z5.val * slot.Z4.val)
  · rintro ⟨cost_, ch_, lf_, df_, zf_, zd_, sb_, st_, a_⟩ ⟨hsb_, hst_, ha_⟩
    simp only [slot.Z309_loop0.body]
    step*
    cases ‹R  ×  R›
    step*
    all_goals scalar_tac
  · exact ⟨hsb, hst, ha⟩
@[local step]
theorem u595 (lf zf b) :
    slot.Z309_loop1 lf zf b ⦃ Y112P0! ⦄ := Y127U9! slot.Z309_loop1 slot.Z309_loop1.body
@[local step]
theorem u596 (df zd b) :
    slot.Z309_loop2 df zd b ⦃ Y112P0! ⦄ := Y127U10! slot.Z309_loop2 slot.Z309_loop2.body
@[local step]
theorem u597 (tail:R) (s:I) (mp mb) (p0 pe:R) (lit lc dc cost ch lf df)
    (hpe:pe.val  ≤  2 ^ 30) (hps:pe.val  ≤  s.length) (hp0:p0.val  ≤  pe.val) :
    slot.Z309 s mp mb p0 pe lit lc dc cost ch lf df tail ⦃ Y112P0! ⦄ := by
  have hseg := EA.EA.u34
  rw [slot.Z309]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac














































@[local step]
theorem u598 (n:R) (cost) (i:R) (hn:n.val < 67108864) (hc:cost.length = i.val) :
    slot.Z308_loop0 n cost i ⦃ Y112P0! ⦄ := Y127U11! slot.Z308_loop0 slot.Z308_loop0.body

set_option aeneas.step.nla true in
@[local step]
theorem u599 (tail final_tail:R) (input:I) (ch) (n:R) (mp mb cost lit lc dc lf df bl bd sl sd) (rot p0 need passes sampled pe k p1 t:R)
    (hn:n.val = input.length) (hn26:n.val < 67108864) (hp0:p0.val < n.val) (hpe:p0.val  ≤  pe.val  ∧  pe.val  ≤  n.val)
    (hpe':pe.val = n.val  ∨  p0.val + slot.Z2.val  ≤  pe.val)
    (hneed:need.val  ≤  65536) (ht:t.val  ≤  need.val) (hp1:p0.val  ≤  p1.val  ∧  p1.val  ≤  p0.val + 511 * t.val) :
    slot.Z308_loop1_loop0 input ch tail final_tail n mp mb cost lit lc dc lf df bl bd sl sd rot p0 need passes sampled pe k p1 t ⦃ Y112P4! ⦄ := by
  have hbt := EA.EA.u36
  have hseg := EA.EA.u34
  rw [slot.Z308_loop1_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, _, _, _, _, _, _, k_, _, _) => passes.val - k_.val)
    (inv := fun (_, _, _, _, _, _, _, _, _, (pe_:R), _, (p1_:R), (t_:R)) =>
      p0.val  ≤  pe_.val  ∧  pe_.val  ≤  n.val  ∧  (pe_.val = n.val  ∨  p0.val + slot.Z2.val  ≤  pe_.val)  ∧ 
      t_.val  ≤  need.val  ∧  p0.val  ≤  p1_.val  ∧  p1_.val  ≤  p0.val + 511 * t_.val)
  · rintro ⟨ch_, cost_, lit_, lc_, dc_, lf_, df_, sl_, sd_, pe_, k_, p1_, t_⟩ ⟨hpe0, hpe1, hpe2, ht_, hp10, hp11⟩
    simp only [slot.Z308_loop1_loop0.body, EA.EA.u37]
    step*
    apply WP.spec_bind (Pₘ := fun (x:alloc.vec.Vec W  ×  alloc.vec.Vec W  ×  Std.Array W 512#usize  × 
        Std.Array W 32#usize  ×  R  ×  R  ×  R) =>
        p0.val  ≤  x.2.2.2.2.1.val  ∧  x.2.2.2.2.1.val  ≤  n.val  ∧ 
        (x.2.2.2.2.1.val = n.val  ∨  p0.val + slot.Z2.val  ≤  x.2.2.2.2.1.val)  ∧ 
        x.2.2.2.2.2.2.val  ≤  need.val  ∧  p0.val  ≤  x.2.2.2.2.2.1.val  ∧  x.2.2.2.2.2.1.val  ≤  p0.val + 511 * x.2.2.2.2.2.2.val)
    · split
      · step*
        · -- a sampled pass: the window end scales with the sampled bytes per token
          cases ‹R  ×  R›
          step*
          apply WP.spec_bind (Pₘ := fun (z:alloc.vec.Vec W  ×  alloc.vec.Vec W  ×  Std.Array W 512#usize  × 
              Std.Array W 32#usize  ×  R) => p0.val  ≤  z.2.2.2.2.val  ∧  z.2.2.2.2.val  ≤  n.val  ∧ 
              (z.2.2.2.2.val = n.val  ∨  p0.val + slot.Z2.val  ≤  z.2.2.2.2.val))
          · repeat' (split <;> step*)
            all_goals scalar_tac
          rintro ⟨v, v1, a, a1, i6⟩ hi6
          step*
          all_goals scalar_tac
        · -- a full pass: dynamic program, then the walk of the round's tokens
          apply WP.spec_bind (Pₘ := fun (lim:R) => lim.val  ≤  pe_.val)
          · split
            all_goals step*
            all_goals scalar_tac
          rintro lim hlim
          step*
          cases ‹R  ×  R›
          step*
          apply WP.spec_bind (Pₘ := fun (z:Std.Array W 512#usize  ×  Std.Array W 32#usize  ×  R) =>
              p0.val  ≤  z.2.2.val  ∧  z.2.2.val  ≤  n.val  ∧  (z.2.2.val = n.val  ∨  p0.val + slot.Z2.val  ≤  z.2.2.val))
          · repeat' (split <;> step*)
            all_goals scalar_tac
          rintro ⟨a, a1, i4⟩ hi4
          step*
          all_goals scalar_tac
        · -- a full pass: dynamic program, then the walk of the round's tokens
          apply WP.spec_bind (Pₘ := fun (lim:R) => lim.val  ≤  pe_.val)
          · split
            all_goals step*
            all_goals scalar_tac
          rintro lim hlim
          step*
          cases ‹R  ×  R›
          step*
          apply WP.spec_bind (Pₘ := fun (z:Std.Array W 512#usize  ×  Std.Array W 32#usize  ×  R) =>
              p0.val  ≤  z.2.2.val  ∧  z.2.2.val  ≤  n.val  ∧  (z.2.2.val = n.val  ∨  p0.val + slot.Z2.val  ≤  z.2.2.val))
          · repeat' (split <;> step*)
            all_goals scalar_tac
          rintro ⟨a, a1, i4⟩ hi4
          step*
          all_goals scalar_tac
      · step*
        · -- a full pass: dynamic program, then the walk of the round's tokens
          apply WP.spec_bind (Pₘ := fun (lim:R) => lim.val  ≤  pe_.val)
          · split
            all_goals step*
            all_goals scalar_tac
          rintro lim hlim
          step*
          cases ‹R  ×  R›
          step*
          apply WP.spec_bind (Pₘ := fun (z:Std.Array W 512#usize  ×  Std.Array W 32#usize  ×  R) =>
              p0.val  ≤  z.2.2.val  ∧  z.2.2.val  ≤  n.val  ∧  (z.2.2.val = n.val  ∨  p0.val + slot.Z2.val  ≤  z.2.2.val))
          · repeat' (split <;> step*)
            all_goals scalar_tac
          rintro ⟨a, a1, i4⟩ hi4
          step*
          all_goals scalar_tac
    rintro ⟨ch1, cost1, lf1, df1, pe1, p11, t1⟩ ⟨hq0, hq1, hq2, hq3, hq4, hq5⟩
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact ⟨hpe.1, hpe.2, hpe', ht, hp1.1, hp1.2⟩
@[local step]
theorem u600 (tail final_tail:R) (input:I) (ch first_passes fspass passes_k) (n:R) (mp mb cost lit lc dc lf df bl bd sl sd zl zd) (rot spn p0 used bpt:R)
    (hn:n.val = input.length) (hn26:n.val < 67108864) (hused:used.val < slot.Z7.val) (hbpt:256  ≤  bpt.val  ∧  bpt.val  ≤  65536) :
    slot.Z308_loop1 input ch first_passes fspass passes_k tail final_tail n mp mb cost lit lc dc lf df bl bd sl sd zl zd rot spn p0 used bpt ⦃ Y112P0! ⦄ := by
  have hbt := EA.EA.u36
  rw [slot.Z308_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, _, _, _, _, _, _, _, p0_, _, _) => n.val - p0_.val)
    (inv := fun (_, _, _, _, _, _, _, _, _, _, _, _, used_, bpt_) => used_.val < slot.Z7.val  ∧ 
      256  ≤  bpt_.val  ∧  bpt_.val  ≤  130816)
  · rintro ⟨ch_, cost_, lit_, lc_, dc_, lf_, df_, bl_, bd_, sl_, sd_, p0_, used_, bpt_⟩ ⟨hused_, hbpt0, hbpt1⟩
    simp only [slot.Z308_loop1.body, EA.EA.u37]
    step*
    · -- the token estimate `need * bpt` fits in 32 bits
      have:need.val * bpt_.val  ≤  16384 * 130816 := Nat.mul_le_mul (by scalar_tac) hbpt1
      scalar_tac
    apply WP.spec_bind (Pₘ := fun (pe:R) => p0_.val  ≤  pe.val  ∧  pe.val  ≤  n.val  ∧ 
      (pe.val = n.val  ∨  p0_.val + slot.Z2.val  ≤  pe.val))
    · split
      all_goals step*
      all_goals scalar_tac
    rintro pe hpe
    step*
    apply WP.spec_bind (Pₘ := fun (x:Std.Array W 512#usize  ×  Std.Array W 32#usize  ×  R) =>
      x.2.2.val < slot.Z7.val)
    · split
      all_goals step*
      all_goals scalar_tac
    rintro ⟨bl1, bd1, used2⟩ hu2
    step*
    all_goals try (
      have hdiv:bpt1.val  ≤  130816 := by
        rw [bpt1_post];apply Nat.div_le_of_le_mul;scalar_tac
      by_cases hb:bpt1 < 256#usize
      all_goals simp only [hb, ite_true, ite_false])
    all_goals scalar_tac
  · -- the invariant allows up to 511 bytes per token (the snapshot never clamps `bpt` from above)
    exact ⟨hused, hbpt.1, by omega⟩
@[local step]
theorem u601 (tail final_tail:R) (input:I) (ch) (depth skip first_passes fspass passes_k spass:R)
    (hn:input.length < 67108864) (h1:depth.val  ≤  65536) (h2:skip.val  ≤  65536) (h2':3  ≤  skip.val)
    (h3:first_passes.val  ≤  65536) (h4:fspass.val  ≤  65536) (h5:passes_k.val  ≤  65536) (h6:spass.val  ≤  65536) :
    slot.Z308 input ch depth skip first_passes fspass passes_k spass tail final_tail ⦃ Y112P0! ⦄ := by
  have hbt := EA.EA.u36
  rw [slot.Z308]
  step*
  all_goals rfl


attribute [local step] EA.EA.u149
def u602 (mf:slot.Z132) (i:Nat):Prop :=
  EA.EA.u15 mf.head.val i  ∧  EA.EA.u15 mf.head3.val i  ∧  EA.EA.u15 mf.tree.val i  ∧  EA.EA.u15 mf.pn.val i  ∧ 
    mf.hl.val  ≤  2 ^ 30
theorem u603 (w:Std.Array Std.U64 32768#usize) (pf:Std.Array W 32#usize) (plen hn:R) :
    u602
      { head := Std.Array.repeat 65536#usize 0#u32, head3 := Std.Array.repeat 16384#usize 0#u32,
        tree := Std.Array.repeat 65536#usize 0#u32, w := w, pn := Std.Array.repeat 32#usize 0#u32, pf := pf,
        plen := plen, hn := hn, hl := 0#usize } (0#usize).val := Y127U22!
def u604 (b i:Nat)
    (r:ControlFlow (slot.Z132  ×  Std.Array W 32#usize  ×  alloc.vec.Vec W  ×  Std.U64  ×  R  × 
      R  ×  R) (slot.Z132  ×  Std.Array W 32#usize  ×  alloc.vec.Vec W  ×  Std.U64  × 
      R  ×  R)):Prop :=
  match r with
  | .done y => u602 y.1 b  ∧  y.2.2.2.2.2.val  ≤  33 * b  ∧  y.2.2.2.2.2.val  ≤  y.2.2.1.length
  | .cont x' => x'.2.2.2.2.2.2.val  ≤  b  ∧  x'.2.2.2.2.2.1.val  ≤  33 * x'.2.2.2.2.2.2.val  ∧ 
      x'.2.2.2.2.2.1.val  ≤  x'.2.2.1.length  ∧  u602 x'.1 x'.2.2.2.2.2.2.val  ∧ 
      b - x'.2.2.2.2.2.2.val < b - i












attribute [local step] EB.u493
attribute [local step] EB.u494
attribute [local step] EB.u495
attribute [local step] EB.u496
attribute [local step] EB.u497
attribute [local step] EB.u498
attribute [local step] EB.u499
attribute [local step] EB.u500
attribute [local step] EB.u501
attribute [local step] EB.u502
attribute [local step] EB.u503
attribute [local step] EB.u504
attribute [local step] EB.u505
attribute [local step] EB.u506
attribute [local step] EB.u507
attribute [local step] EB.u508
attribute [local step] EB.u509
attribute [local step] EB.u510
attribute [local step] EB.u511
attribute [local step] EB.u512
attribute [local step] EB.u513
attribute [local step] EB.u514
attribute [local step] EB.u515
attribute [local step] EB.u516
attribute [local step] EB.u517
attribute [local step] EB.u518
attribute [local step] EB.u519
attribute [local step] EB.u520
attribute [local step] EB.u521
attribute [local step] EB.u522
attribute [local step] EB.u523
attribute [local step] EB.u524
attribute [local step] EB.u525
attribute [local step] EB.u526
attribute [local step] EB.u527
attribute [local step] EB.u528
attribute [local step] EB.u529
attribute [local step] EB.u530
attribute [local step] EB.u531
attribute [local step] EB.u532
attribute [local step] EB.u533
attribute [local step] EB.u534
attribute [local step] EB.u535
attribute [local step] EB.u536
attribute [local step] EB.u537
attribute [local step] EB.u538
attribute [local step] EB.u539
attribute [local step] EB.u540
attribute [local step] EB.u541
attribute [local step] EB.u542
attribute [local step] EB.u543
attribute [local step] EB.u544
attribute [local step] EB.u545
attribute [local step] EB.u546
attribute [local step] EB.u547
attribute [local step] EB.u548
attribute [local step] EB.u549
attribute [local step] EB.u550
attribute [local step] EB.u551
attribute [local step] EB.u552
attribute [local step] EB.u553
attribute [local step] EB.u554
attribute [local step] EB.u555
attribute [local step] EB.u556
attribute [local step] EB.u557
attribute [local step] EB.u558
attribute [local step] EB.u559
attribute [local step] EB.u560
attribute [local step] EB.u561
attribute [local step] EB.u562
attribute [local step] EB.u563
attribute [local step] EB.u564
attribute [local step] EB.u565
attribute [local step] EB.u566
attribute [local step] EB.u567
attribute [local step] EB.u568
attribute [local step] EB.u569
attribute [local step] EB.u570
attribute [local step] EB.u571
attribute [local step] EB.u572
attribute [local step] EB.u573
attribute [local step] EB.u574
attribute [local step] EB.u575
theorem spine_CFG_le:∀ r ∈ slot.Z133.val, ∀ x ∈ r.val, x.val  ≤  65536 := by
  unfold slot.Z133;decide
theorem spine_CFG_skip:∀ r ∈ slot.Z133.val, (r.val[0]!).val = 0  →  3  ≤  (r.val[2]!).val := by
  unfold slot.Z133;decide
@[local step]
theorem u605 (input:I) (k) (hn:input.length < 67108864) :
    slot.Z313 input k ⦃ Y112P0! ⦄ := Y127U21! slot.Z313 slot.Z133.val
@[local step]
theorem u606 (input) (k:R):slot.Z311 input k ⦃ Y112P0! ⦄ := by
  rw [slot.Z311]
  step*
theorem u607 (input:I) (out:U) (k:R)
    (hlen:input.length  ≤  out.length) :
    slot.Z310 input out k ⦃ Y112P1! ⦄ := Y127U13! slot.Z310
attribute [local step] u607
@[local step]
theorem u608 (input:I) (out:U) (mode:R) (hlen:input.length  ≤  out.length):slot.Z312 input out mode ⦃ Y112P1! ⦄ := Y127U14! slot.Z312
end EC
namespace ED
open Aeneas Aeneas.Std Result ControlFlow
open LZ77 (toks bytes)
set_option maxRecDepth 8192
set_option maxHeartbeats 4000000
namespace EA
open Aeneas Aeneas.Std Result ControlFlow
set_option maxRecDepth 8192
set_option maxHeartbeats 1000000
set_option linter.unusedTactic false
set_option linter.unreachableTactic false
set_option linter.unusedSimpArgs false
set_option linter.unusedVariables false
open LZ77 (toks bytes bytes_getElem! Matches emit_lit emit_match)


@[local scalar_tac x &&& y]
theorem u609 (x y:Nat):x &&& y  ≤  y := Nat.and_le_right
@[local scalar_tac x >>> y]
theorem u610 (x y:Nat):x >>> y  ≤  x := Nat.shiftRight_le x y
@[local scalar_tac System.Platform.numBits]
theorem u611:32  ≤  System.Platform.numBits := EA.EA.u4
@[local scalar_tac core.num.U32.leading_zeros x]
theorem u612 (x:W) :
    (core.num.U32.leading_zeros x).val  ≤  32  ∧ 
      (x.val = 0  ∨  (core.num.U32.leading_zeros x).val  ≤  31) := Y127U15!
@[local scalar_tac core.num.U64.leading_zeros x]
theorem u613 (x:Std.U64):(core.num.U64.leading_zeros x).val  ≤  64 := EA.EA.u12 x





set_option hygiene false in
local notation "T1!" q0__:max => (by
  rw [q0__]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac)
@[local scalar_tac core.num.Usize.saturating_add x y]
theorem u614 (x y:R) :
    (core.num.Usize.saturating_add x y).val = min Std.Usize.max (x.val + y.val) := EA.EA.u38 x y






attribute [local step] EC.u586
attribute [local step] EC.u587
attribute [local step] EC.u588
attribute [local step] EC.u589
attribute [local step] EC.u590
attribute [local step] EC.u591
attribute [local step] EC.u592
attribute [local step] EC.u593
attribute [local step] EC.u594
attribute [local step] EC.u595
attribute [local step] EC.u596
attribute [local step] EC.u597








set_option hygiene false in
local notation "T2!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun (i_, td_) => 30 - i_.val)
    (inv := fun _ => True)
  · rintro ⟨i_, td_⟩ _
    simp only [q1__]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial)




























set_option hygiene false in
local notation "T3!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun k_ => lim.val - k_.val)
    (inv := fun _ => True)
  · rintro k_ _
    simp only [q1__]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial)










attribute [local step] EC.u598

attribute [local step] EC.u599
attribute [local step] EC.u600
attribute [local step] EC.u601


attribute [local step] EA.EA.u149
def u615 (mf:slot.Z135) (i:Nat):Prop :=
  EA.EA.u15 mf.head.val i  ∧  EA.EA.u15 mf.head3.val i  ∧  EA.EA.u15 mf.tree.val i  ∧  EA.EA.u15 mf.pn.val i  ∧ 
    mf.hl.val  ≤  2 ^ 30
theorem u616 (w:Std.Array Std.U64 32768#usize) (pf:Std.Array W 32#usize) (plen hn:R) :
    u615
      { head := Std.Array.repeat 65536#usize 0#u32, head3 := Std.Array.repeat 16384#usize 0#u32,
        tree := Std.Array.repeat 65536#usize 0#u32, w := w, pn := Std.Array.repeat 32#usize 0#u32, pf := pf,
        plen := plen, hn := hn, hl := 0#usize } (0#usize).val := Y127U22!
def u617 (b i:Nat)
    (r:ControlFlow (slot.Z135  ×  Std.Array W 32#usize  ×  alloc.vec.Vec W  ×  Std.U64  ×  R  × 
      R  ×  R) (slot.Z135  ×  Std.Array W 32#usize  ×  alloc.vec.Vec W  ×  Std.U64  × 
      R  ×  R)):Prop :=
  match r with
  | .done y => u615 y.1 b  ∧  y.2.2.2.2.2.val  ≤  33 * b  ∧  y.2.2.2.2.2.val  ≤  y.2.2.1.length
  | .cont x' => x'.2.2.2.2.2.2.val  ≤  b  ∧  x'.2.2.2.2.2.1.val  ≤  33 * x'.2.2.2.2.2.2.val  ∧ 
      x'.2.2.2.2.2.1.val  ≤  x'.2.2.1.length  ∧  u615 x'.1 x'.2.2.2.2.2.2.val  ∧ 
      b - x'.2.2.2.2.2.2.val < b - i












attribute [local step] EB.u493
attribute [local step] EB.u494
attribute [local step] EB.u495
attribute [local step] EB.u496
attribute [local step] EB.u497
attribute [local step] EB.u498
attribute [local step] EB.u499
attribute [local step] EB.u500
attribute [local step] EB.u501
attribute [local step] EB.u502
attribute [local step] EB.u503
attribute [local step] EB.u504
attribute [local step] EB.u505
attribute [local step] EB.u506
attribute [local step] EB.u507
attribute [local step] EB.u508
attribute [local step] EB.u509
attribute [local step] EB.u510
attribute [local step] EB.u511
attribute [local step] EB.u512
attribute [local step] EB.u513
attribute [local step] EB.u514
attribute [local step] EB.u515
attribute [local step] EB.u516
attribute [local step] EB.u517
attribute [local step] EB.u518
attribute [local step] EB.u519
attribute [local step] EB.u520
attribute [local step] EB.u521
attribute [local step] EB.u522
attribute [local step] EB.u523
attribute [local step] EB.u524
attribute [local step] EB.u525
attribute [local step] EB.u526
attribute [local step] EB.u527
attribute [local step] EB.u528
attribute [local step] EB.u529
attribute [local step] EB.u530
attribute [local step] EB.u531
attribute [local step] EB.u532
attribute [local step] EB.u533
attribute [local step] EB.u534
attribute [local step] EB.u535
attribute [local step] EB.u536
attribute [local step] EB.u537
attribute [local step] EB.u538
attribute [local step] EB.u539
attribute [local step] EB.u540
attribute [local step] EB.u541
attribute [local step] EB.u542
attribute [local step] EB.u543
attribute [local step] EB.u544
attribute [local step] EB.u545
attribute [local step] EB.u546
attribute [local step] EB.u547
attribute [local step] EB.u548
attribute [local step] EB.u549
attribute [local step] EB.u550
attribute [local step] EB.u551
attribute [local step] EB.u552
attribute [local step] EB.u553
attribute [local step] EB.u554
attribute [local step] EB.u555
attribute [local step] EB.u556
attribute [local step] EB.u557
attribute [local step] EB.u558
attribute [local step] EB.u559
attribute [local step] EB.u560
attribute [local step] EB.u561
attribute [local step] EB.u562
attribute [local step] EB.u563
attribute [local step] EB.u564
attribute [local step] EB.u565
attribute [local step] EB.u566
attribute [local step] EB.u567
attribute [local step] EB.u568
attribute [local step] EB.u569
attribute [local step] EB.u570
attribute [local step] EB.u571
set_option hygiene false in
local notation "T8!" q0__:max q1__:max => (by
  have h1 := Submission.EA.EA.C_UNUSED_LIT_le
  have h2 := Submission.EA.EA.C_UNUSED_DIST_le
  have h3 := Submission.EA.EA.C_STOP_DIV_pos
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, pass') => passes.val - pass'.val)
    (inv := fun (_, _, b', _, _) => b'.length  ≤  1048576)
  · rintro ⟨out', models', b', le', pass'⟩ hb'
    simp only [q1__]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact hnb)
attribute [local step] EB.u572
attribute [local step] EB.u573
attribute [local step] EB.u574
attribute [local step] EB.u575
theorem spine_CFG_le:∀ r ∈ slot.Z136.val, ∀ x ∈ r.val, x.val  ≤  65536 := by
  unfold slot.Z136;decide
theorem spine_CFG_skip:∀ r ∈ slot.Z136.val, (r.val[0]!).val = 0  →  3  ≤  (r.val[2]!).val := by
  unfold slot.Z136;decide
@[local step]
theorem u618 (input:I) (k) (hn:input.length < 67108864) :
    slot.Z317 input k ⦃ Y112P0! ⦄ := Y127U21! slot.Z317 slot.Z136.val
@[local step]
theorem u619 (input) (k:R):slot.Z315 input k ⦃ Y112P0! ⦄ := by
  rw [slot.Z315]
  step*
theorem u620 (input:I) (out:U) (k:R)
    (hlen:input.length  ≤  out.length) :
    slot.Z316 input out k ⦃ Y112P1! ⦄ := Y127U13! slot.Z316
end EA
namespace ED
open Aeneas Aeneas.Std Result ControlFlow
set_option maxRecDepth 8192
set_option maxHeartbeats 4000000
open LZ77 (toks bytes bytes_length bytes_getElem! toks_update bytes_congr Matches ite_ok)
end ED
namespace EH
open Aeneas Aeneas.Std Result ControlFlow
set_option maxRecDepth 8192
set_option maxHeartbeats 4000000
set_option linter.unusedTactic false
set_option linter.unreachableTactic false
set_option linter.unusedSimpArgs false
open LZ77 (toks bytes bytes_length bytes_getElem! Matches emit_lit emit_match ite_ok)
end EH
attribute [local step] EA.u620
@[local step]
theorem u621 (input:I) (out:U) (mode:R) (hlen:input.length  ≤  out.length):slot.Z318 input out mode ⦃ Y112P1! ⦄ := Y127U14! slot.Z318
end ED
namespace EE
open Aeneas Aeneas.Std Result ControlFlow
open LZ77 (toks bytes)
set_option maxRecDepth 8192
set_option maxHeartbeats 4000000
namespace EA
open Aeneas Aeneas.Std Result ControlFlow
set_option maxRecDepth 8192
set_option maxHeartbeats 1000000
set_option linter.unusedTactic false
set_option linter.unreachableTactic false
set_option linter.unusedSimpArgs false
set_option linter.unusedVariables false
open LZ77 (toks bytes bytes_getElem! Matches emit_lit emit_match)

@[local scalar_tac x &&& y]
theorem u622 (x y:Nat):x &&& y  ≤  y := Nat.and_le_right
@[local scalar_tac x >>> y]
theorem u623 (x y:Nat):x >>> y  ≤  x := Nat.shiftRight_le x y
@[local scalar_tac System.Platform.numBits]
theorem u624:32  ≤  System.Platform.numBits := EA.EA.u4
@[local scalar_tac core.num.U32.leading_zeros x]
theorem u625 (x:W) :
    (core.num.U32.leading_zeros x).val  ≤  32  ∧ 
      (x.val = 0  ∨  (core.num.U32.leading_zeros x).val  ≤  31) := Y127U15!
@[local scalar_tac core.num.U64.leading_zeros x]
theorem u626 (x:Std.U64):(core.num.U64.leading_zeros x).val  ≤  64 := EA.EA.u12 x
@[local scalar_tac core.num.Usize.saturating_add x y]
theorem u627 (x y:R) :
    (core.num.Usize.saturating_add x y).val = min Std.Usize.max (x.val + y.val) := EA.EA.u38 x y


attribute [local step] EA.EA.u149
def u628 (mf:slot.Z137) (i:Nat):Prop :=
  EA.EA.u15 mf.head.val i  ∧  EA.EA.u15 mf.head3.val i  ∧  EA.EA.u15 mf.tree.val i  ∧  EA.EA.u15 mf.pn.val i  ∧ 
    mf.hl.val  ≤  2 ^ 30
theorem u629 (w:Std.Array Std.U64 32768#usize) (pf:Std.Array W 32#usize) (plen hn:R) :
    u628
      { head := Std.Array.repeat 65536#usize 0#u32, head3 := Std.Array.repeat 16384#usize 0#u32,
        tree := Std.Array.repeat 65536#usize 0#u32, w := w, pn := Std.Array.repeat 32#usize 0#u32, pf := pf,
        plen := plen, hn := hn, hl := 0#usize } (0#usize).val := Y127U22!
def u630 (b i:Nat)
    (r:ControlFlow (slot.Z137  ×  Std.Array W 32#usize  ×  alloc.vec.Vec W  ×  Std.U64  ×  R  × 
      R  ×  R) (slot.Z137  ×  Std.Array W 32#usize  ×  alloc.vec.Vec W  ×  Std.U64  × 
      R  ×  R)):Prop :=
  match r with
  | .done y => u628 y.1 b  ∧  y.2.2.2.2.2.val  ≤  33 * b  ∧  y.2.2.2.2.2.val  ≤  y.2.2.1.length
  | .cont x' => x'.2.2.2.2.2.2.val  ≤  b  ∧  x'.2.2.2.2.2.1.val  ≤  33 * x'.2.2.2.2.2.2.val  ∧ 
      x'.2.2.2.2.2.1.val  ≤  x'.2.2.1.length  ∧  u628 x'.1 x'.2.2.2.2.2.2.val  ∧ 
      b - x'.2.2.2.2.2.2.val < b - i












theorem spine_CFG_le:∀ r ∈ slot.Z138.val, ∀ x ∈ r.val, x.val  ≤  65536 := by
  unfold slot.Z138;decide
theorem spine_CFG_skip:∀ r ∈ slot.Z138.val, (r.val[0]!).val = 0  →  3  ≤  (r.val[2]!).val := by
  unfold slot.Z138;decide
end EA
set_option hygiene false in
local notation "T9!" q0__:max q1__:max => (by
  (
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun l => cap.val - l.val)
    (inv := fun l => l.val  ≤  cap.val  ∧  LZ77.Matches input a.val b.val l.val)
  · rintro l ⟨hle, hinv⟩
    simp only [q1__]
    split
    case isTrue hlt =>
      have hmax:input.length  ≤  Std.Usize.max := Std.Slice.length_ineq input
      step*
      all_goals first
        | scalar_tac
        | exact ⟨hle, hinv⟩
        | (refine ⟨by scalar_tac, ?_, by scalar_tac⟩
           rw [show l1.val = l.val + 1 by scalar_tac]
           apply LZ77.Matches.succ hinv
           rw [← i_post, ← i2_post, getElem!_pos _ _ (by scalar_tac),
             getElem!_pos _ _ (by scalar_tac), ← i1_post, ← i3_post]
           assumption)
    case isFalse => exact ⟨hle, hinv⟩
  · exact ⟨hl0, h0⟩))
set_option hygiene false in
local notation "T10!" => (by
  (
  exact match_len_loop_spec input a b cap 0#usize ha hb (by scalar_tac)
    (LZ77.Matches.zero input a.val b.val)))
namespace ED
open Aeneas Aeneas.Std Result ControlFlow
set_option maxRecDepth 8192
set_option maxHeartbeats 4000000
open LZ77 (toks bytes bytes_length bytes_getElem! toks_update bytes_congr Matches ite_ok)
end ED
namespace EH
open Aeneas Aeneas.Std Result ControlFlow
set_option maxRecDepth 8192
set_option maxHeartbeats 4000000
set_option linter.unusedTactic false
set_option linter.unreachableTactic false
set_option linter.unusedSimpArgs false
open LZ77 (toks bytes bytes_length bytes_getElem! Matches emit_lit emit_match ite_ok)
set_option hygiene false in
local notation "T14!" q0__:max => (by
  rw [q0__]
  try simp only [ite_ok]
  step*
  all_goals (repeat (split <;> step*))
  all_goals scalar_tac)

@[local step]
theorem u631 (v:U) (i:R) (x:W) :
    slot.Z304 v i x ⦃ Y112P0! ⦄ := T14! slot.Z304
set_option hygiene false in
local notation "T15!" q0__:max => (by
  rw [q0__]
  simp only [lift, ite_ok, alloc.vec.Vec.deref_mut, bind_tc_ok]
  step*
  all_goals (repeat (split <;> step*))
  all_goals scalar_tac)
@[local step]
theorem u632 (v:U) (i:R) (by0:W) :
    slot.Z331 v i by0 ⦃ Y112P0! ⦄ := T15! slot.Z331
@[local step]
theorem u633 (v:Slice Std.U64) (i:R) (x:Std.U64) :
    slot.Z449 v i x ⦃ Y112P0! ⦄ := T14! slot.Z449
@[local step]
theorem u634 (v:I) (i:R) :
    slot.Z379 v i ⦃ Y112P0! ⦄ := T14! slot.Z379
@[local step]
theorem u635 (input:I) (i:R) :
    slot.Z332 input i ⦃ Y112P0! ⦄ := T14! slot.Z332
@[local step]
theorem u636 (a:C 65536#usize) (i:R) (x:W) :
    slot.Z450 a i x ⦃ Y112P0! ⦄ := T14! slot.Z450
theorem u637 (x:W) (v0:alloc.vec.Vec W) (n8 i0:R)
    (hn8:8 * n8.val  ≤  Std.Usize.max) (h0:v0.length = 8 * i0.val) (hi:i0.val  ≤  n8.val) :
    slot.Z367_loop0 x v0 n8 i0 ⦃ fun r => r.length = 8 * n8.val ⦄ := by
  rw [slot.Z367_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun s => n8.val - s.2.val)
    (inv := fun s => s.1.length = 8 * s.2.val  ∧  s.2.val  ≤  n8.val)
  · rintro ⟨v, i⟩ ⟨hv, hle⟩
    simp only at hv hle
    simp only [slot.Z367_loop0.body]
    split
    case isTrue hlt =>
      step*
      all_goals (simp_all;scalar_tac)
    case isFalse hge =>
      simp only [Std.WP.spec_ok]
      scalar_tac
  · exact ⟨h0, hi⟩
theorem u638 (n:R) (x:W) (v0:alloc.vec.Vec W)
    (j0:R) (h0:v0.length = j0.val) (hj:j0.val  ≤  n.val) :
    slot.Z367_loop1 n x v0 j0 ⦃ fun r => r.length = n.val ⦄ := by
  rw [slot.Z367_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun s => n.val - s.2.val)
    (inv := fun s => s.1.length = s.2.val  ∧  s.2.val  ≤  n.val)
  · rintro ⟨v, j⟩ ⟨hv, hle⟩
    simp only at hv hle
    simp only [slot.Z367_loop1.body]
    split
    case isTrue hlt =>
      step*
      all_goals simp_all
      all_goals scalar_tac
    case isFalse hge =>
      simp only [Std.WP.spec_ok]
      scalar_tac
  · exact ⟨h0, hj⟩
@[local step]
theorem u639 (n:R) (x:W) :
    slot.Z367 n x ⦃ fun r => r.length = n.val ⦄ := by
  rw [slot.Z367]
  step*
  apply Std.WP.spec_bind (u637 x _ n8 0#usize (by scalar_tac)
    (by simp [alloc.vec.Vec.with_capacity]) (by scalar_tac))
  intro v1 hv1
  step*
  exact u638 n x v1 j (by scalar_tac) (by scalar_tac)
@[local step]
theorem u640 (v:alloc.vec.Vec W) (x:W) :
    slot.Z430 v x ⦃ Y112P0! ⦄ := T14! slot.Z430
@[local step]
theorem u641 (f:R) (a:R) (b:R) :
    slot.Z446 f a b ⦃ Y112P0! ⦄ := T14! slot.Z446
@[local step]
theorem u642 (f:R) (a:W) (b:W) :
    slot.Z447 f a b ⦃ Y112P0! ⦄ := T14! slot.Z447
@[local step]
theorem u643 (f:R) (a:Std.U64) (b:Std.U64) :
    slot.Z448 f a b ⦃ Y112P0! ⦄ := T14! slot.Z448
@[local step]
theorem u644 (a:R) (b:R) :
    slot.Z377 a b ⦃ Y112P0! ⦄ := T14! slot.Z377
@[local step]
theorem u645 (a:R) (b:R) :
    slot.Z404 a b ⦃ Y112P0! ⦄ := T14! slot.Z404
@[local step]
theorem u646 (a:R) (b:R) :
    slot.Z357 a b ⦃ Y112P0! ⦄ := T14! slot.Z357
@[local step]
theorem u647 (a:W) (b:W) :
    slot.Z405 a b ⦃ Y112P0! ⦄ := T14! slot.Z405
@[local step]
theorem u648 (a:Std.U64) (b:Std.U64) :
    slot.Z406 a b ⦃ Y112P0! ⦄ := T14! slot.Z406
@[local step]
theorem u649 (a:R) (b:R) :
    slot.Z248 a b ⦃ Y112P0! ⦄ := T14! slot.Z248
@[local step]
theorem u650 (a:R) (b:R) :
    slot.Z457 a b ⦃ Y112P0! ⦄ := T14! slot.Z457
@[local step]
theorem u651 (a:Std.U64) (b:Std.U64) :
    slot.Z358 a b ⦃ Y112P0! ⦄ := T14! slot.Z358
@[local step]
theorem u652 (a:Std.U64) (b:Std.U64) :
    slot.Z458 a b ⦃ Y112P0! ⦄ := T14! slot.Z458
@[local step]
theorem u653 (v:alloc.vec.Vec W) (f:R) (x:W) :
    slot.Z431 v f x ⦃ Y112P0! ⦄ := T14! slot.Z431
@[local step]
theorem u654 (d:R) :
    slot.Z353 d ⦃ Y112P0! ⦄ := T15! slot.Z353
@[local step]
theorem u655 (len:R) (d:R) :
    slot.Z415 len d ⦃ Y112P0! ⦄ := T15! slot.Z415
@[local step]
theorem u656 (v:alloc.vec.Vec W) (f:R) (len:R) (d:R) :
    slot.Z432 v f len d ⦃ Y112P0! ⦄ := T14! slot.Z432
@[local step]
theorem u657 (mc:alloc.vec.Vec W) (m0:R) (len:R) (d:R) :
    slot.Z434 mc m0 len d ⦃ Y112P0! ⦄ := T15! slot.Z434
@[local step]
theorem u658 (mc:alloc.vec.Vec W) (m0:R) (f:R) (len:R) (d:R) :
    slot.Z433 mc m0 f len d ⦃ Y112P0! ⦄ := T14! slot.Z433
@[local step]
theorem u659 (l room:R) :
    slot.Z339 l room ⦃ fun r => 1  ≤  r.val  ∧  (r.val = 1  ∨  r.val  ≤  room.val) ⦄ := by
  rw [slot.Z339]
  step*
@[local step]
theorem u660 (l room:R) :
    slot.Z338 l room ⦃ fun r => 1  ≤  r.val  ∧  (r.val = 1  ∨  r.val  ≤  room.val) ⦄ := by
  rw [slot.Z338]
  step*
@[local step]
theorem u661 (x:Std.U64):slot.Z411 x ⦃ fun r => 0 < r.val ⦄ := by
  rw [slot.Z411]
  step*

theorem u662 (input:I) (pos d ch:R) :
    slot.Z459 input pos d ch ⦃ fun b => b = true  → 
      3  ≤  ch.val  ∧  ch.val  ≤  258  ∧  1  ≤  d.val  ∧  d.val  ≤  32768  ∧  d.val  ≤  pos.val  ∧ 
      pos.val + ch.val  ≤  input.length  ∧  Matches input (pos.val - d.val) pos.val ch.val ⦄ := by
  rw [slot.Z459]
  have hmax:input.length  ≤  Std.Usize.max := Std.Slice.length_ineq input
  step*
  intro hv
  have hv':ch.val  ≤  v.val := by simpa using hv
  refine ⟨by scalar_tac, by scalar_tac, by scalar_tac, by scalar_tac, by scalar_tac,
    by scalar_tac, ?_⟩
  rw [show pos.val - d.val = i1.val by scalar_tac]
  exact Matches.mono v_post2 hv'
theorem u663 (input:I) (out0:U)
    (plan:U) (n k0 ntok0:R)
    (hn:n.val = input.length) (hout:input.length  ≤  out0.length)
    (hk:k0.val  ≤  n.val) (hntok:ntok0.val  ≤  k0.val)
    (hdec:LZ77.decode (toks out0 ntok0.val) = some ((bytes input).take k0.val)) :
    slot.Z354_loop input out0 plan n k0 ntok0 ⦃ Y112P2! ⦄ := by
  rw [slot.Z354_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => n.val - s.2.1.val)
    (inv := fun s =>
      s.2.1.val  ≤  n.val  ∧  s.2.2.val  ≤  s.2.1.val  ∧  s.1.length = out0.length  ∧ 
      LZ77.decode (toks s.1 s.2.2.val) = some ((bytes input).take s.2.1.val))
  · rintro ⟨out, k, ntok⟩ ⟨hkn, hnt, hlen, hde⟩
    simp only at hkn hnt hlen hde
    have hmax:input.length  ≤  Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.Z354_loop.body]
    split
    case isTrue hklt =>
      have hntok_lt:ntok.val < out.length := by scalar_tac
      step*
      apply Std.WP.spec_bind (u662 input k d ch)
      intro b hb
      split
      case isTrue hbt =>
        obtain ⟨hch3, hch258, hd1, hdmax, hdpos, hend, hmatch⟩ := hb hbt
        step*
        have htok:i7.val = LZ77.mkMatch d.val ch.val := by
          simp_all only [LZ77.mkMatch, LZ77.MATCH_BASE]
          all_goals scalar_tac
        refine ⟨by scalar_tac, by scalar_tac,
          by rw [s_post];simpa [Std.Slice.set_val_eq] using hlen, ?_, by scalar_tac⟩
        rw [s_post, show ntok1.val = ntok.val + 1 by scalar_tac,
          show k1.val = k.val + ch.val by scalar_tac]
        exact emit_match input out ntok k.val d.val ch.val i7 hde hntok_lt hd1 hdpos hdmax
          hch3 hch258 hend hmatch htok
      case isFalse hbf =>
        have hposlen:k.val < input.length := by scalar_tac
        step*
        have hval:i2.val = (bytes input)[k.val]! := by
          rw [bytes_getElem! input k.val hposlen, i2_post, Std.U8.cast_U32_val_eq, i1_post]
        refine ⟨by scalar_tac, by scalar_tac,
          by rw [s_post];simpa [Std.Slice.set_val_eq] using hlen, ?_, by scalar_tac⟩
        rw [s_post, show ntok1.val = ntok.val + 1 by scalar_tac,
          show k1.val = k.val + 1 by scalar_tac]
        exact emit_lit input out ntok k.val i2 hde hposlen hntok_lt hval
    case isFalse hge =>
      have hkn':k.val = input.length := by scalar_tac
      refine ⟨by scalar_tac, hlen, ?_⟩
      rw [hde, hkn']
      simp
  · exact ⟨hk, hntok, rfl, hdec⟩
@[local step]
theorem u664 (input:I) (out:U)
    (plan:U) (hout:input.length  ≤  out.length) :
    slot.Z354 input out plan ⦃ Y112P3! ⦄ := by
  rw [slot.Z354]
  exact u663 input out plan _ 0#usize 0#usize
    (by simp) hout (by scalar_tac) (by scalar_tac) (by simp [toks, LZ77.decode])
@[local step]
theorem u665 (input:I) (p:R) :
    slot.Z392 input p ⦃ Y112P0! ⦄ := T15! slot.Z392
@[local step]
theorem u666 (x:Std.U64) (y:Std.U64) :
    slot.Z372 x y ⦃ Y112P0! ⦄ := T15! slot.Z372
@[local step]
theorem u667 (input:I) (p:R) :
    slot.Z382 input p ⦃ Y112P0! ⦄ := T15! slot.Z382
@[local step]
theorem u668 (input:I) (p:R) :
    slot.Z381 input p ⦃ Y112P0! ⦄ := T15! slot.Z381
@[local step]
theorem u669 (s:R) :
    slot.Z347 s ⦃ Y112P0! ⦄ := T15! slot.Z347
@[local step]
theorem u670 (l:R) :
    slot.Z390 l ⦃ fun r => r.val  ≤  28 ⦄ := by
  rw [slot.Z390]
  simp only [lift, ite_ok, alloc.vec.Vec.deref_mut, bind_tc_ok]
  step*
  all_goals (repeat (split <;> try step*))
  all_goals (try split_ifs)
  all_goals first
    | scalar_tac
    | (simp only [core.num.Usize.wrapping_sub_val_eq, UScalar.size, UScalarTy.numBits]
       cases System.Platform.numBits_eq <;> simp_all <;> scalar_tac)
@[local step]
theorem u671 (c:R) :
    slot.Z395 c ⦃ Y112P0! ⦄ := T15! slot.Z395
@[local step]
theorem u672 (s:R) :
    slot.Z374 s ⦃ Y112P0! ⦄ := T14! slot.Z374
@[local step]
theorem u673 (input:I) (a:R) (b:R) (lim:R) (l:R) (it:R) :
    slot.Z364_loop input a b lim l it ⦃ Y112P0! ⦄ := by
  rw [slot.Z364_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 300 - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨l1, it1⟩ _
    have hmax:input.length  ≤  Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.Z364_loop.body, lift]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem u674 (input:I) (a:R) (b:R) (from0:R) (cap:R) :
    slot.Z364 input a b from0 cap ⦃ Y112P0! ⦄ := T15! slot.Z364
@[local step]
theorem u675 (input:I) (f:R) (a:R) (b:R) (from0:R) (cap:R) (dflt:R) :
    slot.Z363 input f a b from0 cap dflt ⦃ Y112P0! ⦄ := T14! slot.Z363
@[local step]
theorem u676 (input:I) (p:R) (x:Std.U64) (j:R) :
    slot.Z393_loop input p x j ⦃ Y112P0! ⦄ := by
  rw [slot.Z393_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 8 - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨x1, j1⟩ _
    have hmax:input.length  ≤  Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.Z393_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem u677 (input:I) (p:R) :
    slot.Z393 input p ⦃ Y112P0! ⦄ := T14! slot.Z393
@[local step]
theorem u678 (input:I) (p:R) :
    slot.Z394 input p ⦃ Y112P0! ⦄ := T14! slot.Z394
@[local step]
theorem u679 (x:Std.U64) (y:Std.U64) (k:R) :
    slot.Z335 x y k ⦃ Y112P0! ⦄ := T15! slot.Z335
@[local step]
theorem u680 (input:I) (a:R) (b:R) (lim:R) (l:R) (it:R) (z:Std.U64) (x:Std.U64) :
    slot.Z391_loop input a b lim l it z x ⦃ Y112P0! ⦄ := by
  rw [slot.Z391_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 40 - qq9.2.1.val)
    (inv := fun _ => True)
  · rintro ⟨l1, it1, z1, x1⟩ _
    have hmax:input.length  ≤  Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.Z391_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem u681 (input:I) (a:R) (b:R) (l0:R) (lim:R) :
    slot.Z391 input a b l0 lim ⦃ Y112P0! ⦄ := T15! slot.Z391
@[local step]
theorem u682 (input:I) (same:R) (a:R) (b:R) (l0:R) (x:Std.U64) (y:Std.U64) (lim:R) :
    slot.Z365 input same a b l0 x y lim ⦃ Y112P0! ⦄ := T15! slot.Z365
@[local step]
theorem u683 (input:I) (child:C 65536#usize) (pos:R) (rec:R) (maxd:R) (mc:alloc.vec.Vec W) (m0:R) (plt:R) (pgt:R) (cur:R) (ltl:R) (gtl:R) (len:R) (best:R) (wl:R) (wd:R) (depth:R) (go:R) (lim:R) (stop:R) (kcur:R) (kl:R) :
    slot.Z328_loop input child pos rec maxd mc m0 plt pgt cur ltl gtl len best wl wd depth go lim stop kcur kl ⦃ Y112P0! ⦄ := by
  rw [slot.Z328_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => maxd.val - qq9.2.2.2.2.2.2.2.2.2.2.2.1.val)
    (inv := fun _ => True)
  · rintro ⟨child1, mc1, plt1, pgt1, cur1, ltl1, gtl1, len1, best1, wl1, wd1, depth1, go1⟩ _
    have hmax:input.length  ≤  Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.Z328_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem u684 (input:I) (child:C 65536#usize) (root:R) (pos:R) (cap:R) (best0:R) (rec:R) (maxd:R) (hint:R) (mc:alloc.vec.Vec W) (m0:R) :
    slot.Z328 input child root pos cap best0 rec maxd hint mc m0 ⦃ Y112P0! ⦄ := T15! slot.Z328
@[local step]
theorem u685 (gap:R) :
    slot.Z451 gap ⦃ Y112P0! ⦄ := T15! slot.Z451
@[local step]
theorem u686 (input:I) (h4:C 65536#usize) (h3:C 131072#usize) (child:C 65536#usize) (mc:alloc.vec.Vec W) (st:O 4#usize) (pos:R) (maxd:R) :
    slot.Z370 input h4 h3 child mc st pos maxd ⦃ Y112P0! ⦄ := T15! slot.Z370
@[local step]
theorem u687 (input:I) (mstart:alloc.vec.Vec W) (mc:alloc.vec.Vec W) (maxd:R) (n:R) (h4:C 65536#usize) (h3:C 131072#usize) (child:C 65536#usize) (st:O 4#usize) (pos:R) :
    slot.Z368_loop input mstart mc maxd n h4 h3 child st pos ⦃ Y112P0! ⦄ := by
  rw [slot.Z368_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => n.val - qq9.2.2.2.2.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨mstart1, mc1, h41, h31, child1, st1, pos1⟩ _
    have hmax:input.length  ≤  Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.Z368_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem u688 (input:I) (mstart:alloc.vec.Vec W) (mc:alloc.vec.Vec W) (maxd:R) :
    slot.Z368 input mstart mc maxd ⦃ Y112P0! ⦄ := T15! slot.Z368
@[local step]
theorem u689 (input:I) (f:R) :
    slot.Z371 input f ⦃ Y112P0! ⦄ := T14! slot.Z371
@[local step]
theorem u690 (l:R) :
    slot.Z329 l ⦃ Y112P0! ⦄ := T15! slot.Z329
@[local step]
theorem u691 (bend:C 512#usize) (l:R) :
    slot.Z330_loop bend l ⦃ Y112P0! ⦄ := by
  rw [slot.Z330_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 259 - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨bend1, l1⟩ _
    simp only [slot.Z330_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem u692 (bend:C 512#usize) :
    slot.Z330 bend ⦃ Y112P0! ⦄ := T14! slot.Z330
@[local step]
theorem u693 (w:R) :
    slot.Z396 w ⦃ Y112P0! ⦄ := T15! slot.Z396
@[local step]
theorem u694 (tbl:U) (toff:R) (ct:C 1024#usize) (lam:W) (x:R) :
    slot.Z400_loop0 tbl toff ct lam x ⦃ Y112P0! ⦄ := by
  rw [slot.Z400_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 259 - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨ct1, x1⟩ _
    simp only [slot.Z400_loop0.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem u695 (tbl:U) (toff:R) (ct:C 1024#usize) (s:R) :
    slot.Z400_loop1 tbl toff ct s ⦃ Y112P0! ⦄ := by
  rw [slot.Z400_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 30 - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨ct1, s1⟩ _
    simp only [slot.Z400_loop1.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem u696 (tbl:U) (toff:R) (ct:C 1024#usize) (lam:W) (c:R) :
    slot.Z400_loop2 tbl toff ct lam c ⦃ Y112P0! ⦄ := by
  rw [slot.Z400_loop2]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 256 - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨ct1, c1⟩ _
    simp only [slot.Z400_loop2.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem u697 (tbl:U) (toff:R) (ct:C 1024#usize) (lam:W) :
    slot.Z400 tbl toff ct lam ⦃ Y112P0! ⦄ := T14! slot.Z400
@[local step]
theorem u698 (rm:Array Std.U64 4096#usize) (i:R) (c:Std.U64) :
    slot.Z443 rm i c ⦃ Y112P0! ⦄ := T15! slot.Z443
@[local step]
theorem u699 (rm:Array Std.U64 4096#usize) (i:R) (c:Std.U64) :
    slot.Z444 rm i c ⦃ Y112P0! ⦄ := T15! slot.Z444
@[local step]
theorem u700 (f:R) (rm:Array Std.U64 4096#usize) (i:R) (c:Std.U64) :
    slot.Z442 f rm i c ⦃ Y112P0! ⦄ := T14! slot.Z442
@[local step]
theorem u701 (rm:Array Std.U64 4096#usize) (ct:C 1024#usize) (i:R) (x:R) (e:R) (dcs:Std.U64) :
    slot.Z322 rm ct i x e dcs ⦃ Y112P0! ⦄ := T15! slot.Z322
@[local step]
theorem u702 (x:R) (y:R) (k:R) (slot0:R) :
    slot.Z435 x y k slot0 ⦃ Y112P0! ⦄ := T15! slot.Z435
@[local step]
theorem u703 (rm:Array Std.U64 4096#usize) (ct:C 1024#usize) (i:R) (hi:R) (dcs:Std.U64) (slot0:R) (keep:R) (items:alloc.vec.Vec W) (best:Std.U64) (x:R) :
    slot.Z429_loop rm ct i hi dcs slot0 keep items best x ⦃ Y112P0! ⦄ := by
  rw [slot.Z429_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 11 - qq9.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨items1, best1, x1⟩ _
    simp only [slot.Z429_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem u704 (rm:Array Std.U64 4096#usize) (ct:C 1024#usize) (i:R) (lo:R) (hi:R) (dcs:Std.U64) (slot0:R) (best0:Std.U64) (keep:R) (items:alloc.vec.Vec W) :
    slot.Z429 rm ct i lo hi dcs slot0 best0 keep items ⦃ Y112P0! ⦄ := T14! slot.Z429
@[local step]
theorem u705 (rm:Array Std.U64 4096#usize) (ct:C 1024#usize) (bend:C 512#usize) (i:R) (hi:R) (dcs:Std.U64) (slot0:R) (keep:R) (items:alloc.vec.Vec W) (best:Std.U64) (x:R) (it:R) :
    slot.Z426_loop rm ct bend i hi dcs slot0 keep items best x it ⦃ Y112P0! ⦄ := by
  rw [slot.Z426_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 32 - qq9.2.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨items1, best1, x1, it1⟩ _
    simp only [slot.Z426_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem u706 (rm:Array Std.U64 4096#usize) (ct:C 1024#usize) (bend:C 512#usize) (i:R) (lo:R) (hi:R) (dcs:Std.U64) (slot0:R) (best0:Std.U64) (keep:R) (items:alloc.vec.Vec W) :
    slot.Z426 rm ct bend i lo hi dcs slot0 best0 keep items ⦃ Y112P0! ⦄ := T14! slot.Z426
@[local step]
theorem u707 (rm:Array Std.U64 4096#usize) (ct:C 1024#usize) (bend:C 512#usize) (mc:U) (me:R) (i:R) (chw:R) (msub:W) (keep:R) (items:alloc.vec.Vec W) (best:Std.U64) (k:R) (lo:R) :
    slot.Z428_loop rm ct bend mc me i chw msub keep items best k lo ⦃ Y112P0! ⦄ := by
  rw [slot.Z428_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => me.val - qq9.2.2.1.val)
    (inv := fun _ => True)
  · rintro ⟨items1, best1, k1, lo1⟩ _
    simp only [slot.Z428_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem u708 (rm:Array Std.U64 4096#usize) (ct:C 1024#usize) (bend:C 512#usize) (mc:U) (ms:R) (me:R) (i:R) (lit:Std.U64) (chw:R) (msub:W) (keep:R) (items:alloc.vec.Vec W) :
    slot.Z428 rm ct bend mc ms me i lit chw msub keep items ⦃ Y112P0! ⦄ := T15! slot.Z428
@[local step]
theorem u709 (rm:Array Std.U64 4096#usize) (ct:C 1024#usize) (i:R) (hi:R) (dcs:Std.U64) (best:Std.U64) (x:R) :
    slot.Z440_loop rm ct i hi dcs best x ⦃ Y112P0! ⦄ := by
  rw [slot.Z440_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 11 - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨best1, x1⟩ _
    simp only [slot.Z440_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem u710 (rm:Array Std.U64 4096#usize) (ct:C 1024#usize) (i:R) (lo:R) (hi:R) (dcs:Std.U64) (best0:Std.U64) :
    slot.Z440 rm ct i lo hi dcs best0 ⦃ Y112P0! ⦄ := T14! slot.Z440
@[local step]
theorem u711 (rm:Array Std.U64 4096#usize) (ct:C 1024#usize) (bend:C 512#usize) (i:R) (hi:R) (dcs:Std.U64) (best:Std.U64) (x:R) (it:R) :
    slot.Z437_loop rm ct bend i hi dcs best x it ⦃ Y112P0! ⦄ := by
  rw [slot.Z437_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 32 - qq9.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨best1, x1, it1⟩ _
    simp only [slot.Z437_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem u712 (rm:Array Std.U64 4096#usize) (ct:C 1024#usize) (bend:C 512#usize) (i:R) (lo:R) (hi:R) (dcs:Std.U64) (best0:Std.U64) :
    slot.Z437 rm ct bend i lo hi dcs best0 ⦃ Y112P0! ⦄ := T14! slot.Z437
@[local step]
theorem u713 (rm:Array Std.U64 4096#usize) (ct:C 1024#usize) (bend:C 512#usize) (mc:U) (me:R) (i:R) (chw:R) (msub:W) (best:Std.U64) (k:R) (lo:R) :
    slot.Z439_loop rm ct bend mc me i chw msub best k lo ⦃ Y112P0! ⦄ := by
  rw [slot.Z439_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => me.val - qq9.2.1.val)
    (inv := fun _ => True)
  · rintro ⟨best1, k1, lo1⟩ _
    simp only [slot.Z439_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem u714 (rm:Array Std.U64 4096#usize) (ct:C 1024#usize) (bend:C 512#usize) (mc:U) (ms:R) (me:R) (i:R) (lit:Std.U64) (chw:R) (msub:W) :
    slot.Z439 rm ct bend mc ms me i lit chw msub ⦃ Y112P0! ⦄ := T14! slot.Z439
@[local step]
theorem u715 (rm:Array Std.U64 4096#usize) (ct:C 1024#usize) (bend:C 512#usize) (mc:U) (ms:R) (me:R) (i:R) (lit:Std.U64) (chw:R) (msub:W) (keep:R) (items:alloc.vec.Vec W) :
    slot.Z427 rm ct bend mc ms me i lit chw msub keep items ⦃ Y112P0! ⦄ := T14! slot.Z427
@[local step]
theorem u716 (rm:Array Std.U64 4096#usize) (ct:C 1024#usize) (items:U) (e:R) (i:R) (best:Std.U64) (t:R) :
    slot.Z438_loop rm ct items e i best t ⦃ Y112P0! ⦄ := by
  rw [slot.Z438_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => e.val - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨best1, t1⟩ _
    simp only [slot.Z438_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem u717 (rm:Array Std.U64 4096#usize) (ct:C 1024#usize) (items:U) (s:R) (e:R) (i:R) (lit:Std.U64) :
    slot.Z438 rm ct items s e i lit ⦃ Y112P0! ⦄ := T14! slot.Z438
@[local step]
theorem u718 (input:I) (rm:Array Std.U64 4096#usize) (ct:C 1024#usize) (bend:C 512#usize) (mstart:U) (mc:U) (choice:U) (chw:R) (msub:W) (keep:R) (items:alloc.vec.Vec W) (istart:alloc.vec.Vec W) (lo:R) (l4:R) (co:R) (i:R) :
    slot.Z352_loop input rm ct bend mstart mc choice chw msub keep items istart lo l4 co i ⦃ Y112P0! ⦄ := by
  rw [slot.Z352_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => qq9.2.2.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨rm1, choice1, items1, istart1, i1⟩ _
    have hmax:input.length  ≤  Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.Z352_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem u719 (input:I) (rm:Array Std.U64 4096#usize) (ct:C 1024#usize) (bend:C 512#usize) (mstart:U) (mc:U) (choice:U) (chw:R) (msub:W) (keep:R) (items:alloc.vec.Vec W) (istart:alloc.vec.Vec W) (lo:R) (hi:R) (l4:R) (co:R) :
    slot.Z352 input rm ct bend mstart mc choice chw msub keep items istart lo hi l4 co ⦃ Y112P0! ⦄ := T14! slot.Z352
@[local step]
theorem u720 (bpos:U) (b:R) (hi:R) :
    slot.Z324 bpos b hi ⦃ Y112P0! ⦄ := T15! slot.Z324
@[local step]
theorem u721 (input:I) (mstart:U) (mc:U) (tbl:U) (bend:C 512#usize) (bpos:U) (nb:R) (choice:U) (chw:R) (msub:W) (keep:R) (items:alloc.vec.Vec W) (istart:alloc.vec.Vec W) (co:R) (lam:W) (rm:Array Std.U64 4096#usize) (ct:C 1024#usize) (hi:R) (k:R) :
    slot.Z418_loop input mstart mc tbl bend bpos nb choice chw msub keep items istart co lam rm ct hi k ⦃ Y112P0! ⦄ := by
  rw [slot.Z418_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => nb.val - qq9.2.2.2.2.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨choice1, items1, istart1, rm1, ct1, hi1, k1⟩ _
    have hmax:input.length  ≤  Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.Z418_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem u722 (input:I) (mstart:U) (mc:U) (tbl:U) (bend:C 512#usize) (bpos:U) (nb:R) (choice:U) (chw:R) (msub:W) (keep:R) (items:alloc.vec.Vec W) (istart:alloc.vec.Vec W) (co:R) (lam:W) :
    slot.Z418 input mstart mc tbl bend bpos nb choice chw msub keep items istart co lam ⦃ Y112P0! ⦄ := T15! slot.Z418
@[local step]
theorem u723 (input:I) (rm:Array Std.U64 4096#usize) (ct:C 1024#usize) (choice:U) (items:U) (istart:U) (lo:R) (l4:R) (co:R) (n:R) (e:R) (i:R) :
    slot.Z350_loop input rm ct choice items istart lo l4 co n e i ⦃ Y112P0! ⦄ := by
  rw [slot.Z350_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => qq9.2.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨rm1, choice1, e1, i1⟩ _
    have hmax:input.length  ≤  Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.Z350_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem u724 (input:I) (rm:Array Std.U64 4096#usize) (ct:C 1024#usize) (choice:U) (items:U) (istart:U) (lo:R) (hi:R) (l4:R) (co:R) :
    slot.Z350 input rm ct choice items istart lo hi l4 co ⦃ Y112P0! ⦄ := T15! slot.Z350
@[local step]
theorem u725 (input:I) (tbl:U) (bpos:U) (nb:R) (choice:U) (items:U) (istart:U) (l4:R) (co:R) (lam:W) (rm:Array Std.U64 4096#usize) (ct:C 1024#usize) (hi:R) (k:R) :
    slot.Z417_loop input tbl bpos nb choice items istart l4 co lam rm ct hi k ⦃ Y112P0! ⦄ := by
  rw [slot.Z417_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => nb.val - qq9.2.2.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨choice1, rm1, ct1, hi1, k1⟩ _
    have hmax:input.length  ≤  Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.Z417_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem u726 (input:I) (tbl:U) (bpos:U) (nb:R) (choice:U) (items:U) (istart:U) (l4:R) (co:R) (lam:W) :
    slot.Z417 input tbl bpos nb choice items istart l4 co lam ⦃ Y112P0! ⦄ := T15! slot.Z417
@[local step]
theorem u727 (mc:U) (l:R) (me:R) (d:R) (k:R) :
    slot.Z369_loop mc l me d k ⦃ Y112P0! ⦄ := by
  rw [slot.Z369_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => me.val - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨d1, k1⟩ _
    simp only [slot.Z369_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem u728 (mstart:U) (mc:U) (p:R) (l:R) :
    slot.Z369 mstart mc p l ⦃ Y112P0! ⦄ := T15! slot.Z369
@[local step]
theorem u729 (v:U) (b:R) (i:R) :
    slot.Z341_loop v b i ⦃ Y112P0! ⦄ := by
  rw [slot.Z341_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => b.val - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨v1, i1⟩ _
    simp only [slot.Z341_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem u730 (v:U) (a:R) (b:R) :
    slot.Z341 v a b ⦃ Y112P0! ⦄ := T14! slot.Z341
@[local step]
theorem u731 (mstart:U) (mc:U) (pos:R) (len:R) (d0:R) :
    slot.Z348 mstart mc pos len d0 ⦃ Y112P0! ⦄ := T14! slot.Z348
@[local step]
theorem u732 (fr:U) (off:R) (st:R) (d:R) (b:R) :
    slot.Z461 fr off st d b ⦃ Y112P0! ⦄ := T15! slot.Z461
@[local step]
theorem u733 (input:I) (mstart:U) (mc:U) (choice:U) (co:R) (fr:U) (bpos:U) (n:R) (pos:R) (b:R) (t:R) :
    slot.Z460_loop input mstart mc choice co fr bpos n pos b t ⦃ Y112P0! ⦄ := by
  rw [slot.Z460_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => n.val - qq9.2.2.2.1.val)
    (inv := fun _ => True)
  · rintro ⟨choice1, fr1, bpos1, pos1, b1, t1⟩ _
    have hmax:input.length  ≤  Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.Z460_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem u734 (input:I) (mstart:U) (mc:U) (choice:U) (co:R) (fr:U) (bpos:U) :
    slot.Z460 input mstart mc choice co fr bpos ⦃ Y112P0! ⦄ := T15! slot.Z460
@[local step]
theorem u735 (order:U) (freq:U) (off:R) (fs:W) (j:R) :
    slot.Z386_loop order freq off fs j ⦃ Y112P0! ⦄ := by
  rw [slot.Z386_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨order1, j1⟩ _
    simp only [slot.Z386_loop.body, lift]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem u736 (order:U) (k:R) (s:R) (freq:U) (off:R) :
    slot.Z386 order k s freq off ⦃ Y112P0! ⦄ := T15! slot.Z386
set_option hygiene false in
local notation "T16!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 288 - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨cnt1, i1⟩ _
    simp only [q1__, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial)
@[local step]
theorem u737 (freq:U) (off:R) (src:U) (k:R) (sh:W) (cnt:C 256#usize) (i:R) :
    slot.Z436_loop0 freq off src k sh cnt i ⦃ Y112P0! ⦄ := T16! slot.Z436_loop0 slot.Z436_loop0.body
@[local step]
theorem u738 (cnt:C 256#usize) (acc:W) (d:R) :
    slot.Z436_loop1 cnt acc d ⦃ Y112P0! ⦄ := by
  rw [slot.Z436_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 256 - qq9.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨cnt1, acc1, d1⟩ _
    simp only [slot.Z436_loop1.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem u739 (freq:U) (off:R) (src:U) (dst:U) (k:R) (sh:W) (cnt:C 256#usize) (j:R) :
    slot.Z436_loop2 freq off src dst k sh cnt j ⦃ Y112P0! ⦄ := by
  rw [slot.Z436_loop2]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 288 - qq9.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨dst1, cnt1, j1⟩ _
    simp only [slot.Z436_loop2.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem u740 (freq:U) (off:R) (src:U) (dst:U) (k:R) (sh:W) :
    slot.Z436 freq off src dst k sh ⦃ Y112P0! ⦄ := T14! slot.Z436
@[local step]
theorem u741 (src:U) (soff:R) (dst:U) (doff:R) (m:R) (i:R) :
    slot.Z342_loop src soff dst doff m i ⦃ Y112P0! ⦄ := by
  rw [slot.Z342_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => m.val - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨dst1, i1⟩ _
    simp only [slot.Z342_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem u742 (src:U) (soff:R) (dst:U) (doff:R) (m:R) :
    slot.Z342 src soff dst doff m ⦃ Y112P0! ⦄ := T14! slot.Z342
@[local step]
theorem u743 (freq:U) (off:R) (nsym:R) (tmp:C 288#usize) (k:R) (big:R) (s:R) :
    slot.Z452_loop0 freq off nsym tmp k big s ⦃ Y112P0! ⦄ := by
  rw [slot.Z452_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 288 - qq9.2.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨tmp1, k1, big1, s1⟩ _
    simp only [slot.Z452_loop0.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem u744 (freq:U) (off:R) (order:U) (tmp:C 288#usize) (kb:R) (j:R) :
    slot.Z452_loop1 freq off order tmp kb j ⦃ Y112P0! ⦄ := by
  rw [slot.Z452_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 288 - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨order1, j1⟩ _
    simp only [slot.Z452_loop1.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem u745 (freq:U) (off:R) (nsym:R) (order:U) :
    slot.Z452 freq off nsym order ⦃ Y112P0! ⦄ := T14! slot.Z452
@[local step]
theorem u746 (freq:U) (off:R) (order:U) (k:R) (wa:Slice Std.U64) (i:R) :
    slot.Z401_loop freq off order k wa i ⦃ Y112P0! ⦄ := by
  rw [slot.Z401_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 288 - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨wa1, i1⟩ _
    simp only [slot.Z401_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem u747 (freq:U) (off:R) (order:U) (k:R) (wa:Slice Std.U64) :
    slot.Z401 freq off order k wa ⦃ Y112P0! ⦄ := T14! slot.Z401
@[local step]
theorem u748 (lw:Array Std.U64 288#usize) (k:R) (w:Array Std.U64 1152#usize) (src:R) (dst:R) (flags:G 9216#usize) (foff:R) (npk:R) (total:R) (a:R) (p:R) (t:R) :
    slot.Z421_loop lw k w src dst flags foff npk total a p t ⦃ Y112P0! ⦄ := by
  rw [slot.Z421_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 576 - qq9.2.2.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨w1, flags1, a1, p1, t1⟩ _
    simp only [slot.Z421_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem u749 (lw:Array Std.U64 288#usize) (k:R) (w:Array Std.U64 1152#usize) (src:R) (curlen:R) (dst:R) (flags:G 9216#usize) (foff:R) :
    slot.Z421 lw k w src curlen dst flags foff ⦃ Y112P0! ⦄ := T15! slot.Z421
@[local step]
theorem u750 (lw:Array Std.U64 288#usize) (k:R) (w:Array Std.U64 1152#usize) (flags:G 9216#usize) (maxbits:R) (curlen:R) (lev:R) :
    slot.Z422_loop lw k w flags maxbits curlen lev ⦃ Y112P0! ⦄ := by
  rw [slot.Z422_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 16 - qq9.2.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨w1, flags1, curlen1, lev1⟩ _
    simp only [slot.Z422_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem u751 (lw:Array Std.U64 288#usize) (k:R) (w:Array Std.U64 1152#usize) (flags:G 9216#usize) (maxbits:R) :
    slot.Z422 lw k w flags maxbits ⦃ Y112P0! ⦄ := T14! slot.Z422
@[local step]
theorem u752 (flags:I) (foff:R) (s:R) (c:R) (i:R) :
    slot.Z344_loop flags foff s c i ⦃ Y112P0! ⦄ := by
  rw [slot.Z344_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 576 - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨c1, i1⟩ _
    simp only [slot.Z344_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem u753 (flags:I) (foff:R) (s:R) :
    slot.Z344 flags foff s ⦃ Y112P0! ⦄ := T14! slot.Z344
@[local step]
theorem u754 (cnt:U) (m:R) (i:R) :
    slot.Z384_loop cnt m i ⦃ Y112P0! ⦄ := T16! slot.Z384_loop slot.Z384_loop.body
@[local step]
theorem u755 (cnt:U) (m:R) :
    slot.Z384 cnt m ⦃ Y112P0! ⦄ := T14! slot.Z384
@[local step]
theorem u756 (flags:I) (cnt:U) (s:R) (lv:R) :
    slot.Z343_loop flags cnt s lv ⦃ Y112P0! ⦄ := by
  rw [slot.Z343_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => qq9.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨cnt1, s1, lv1⟩ _
    simp only [slot.Z343_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem u757 (flags:I) (cnt:U) (k:R) (maxbits:R) :
    slot.Z343 flags cnt k maxbits ⦃ Y112P0! ⦄ := T15! slot.Z343
@[local step]
theorem u758 (order:U) (cnt:U) (k:R) (lens:U) (loff:R) (r:R) :
    slot.Z320_loop order cnt k lens loff r ⦃ Y112P0! ⦄ := by
  rw [slot.Z320_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 288 - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨lens1, r1⟩ _
    simp only [slot.Z320_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem u759 (order:U) (cnt:U) (k:R) (lens:U) (loff:R) :
    slot.Z320 order cnt k lens loff ⦃ Y112P0! ⦄ := T14! slot.Z320
@[local step]
theorem u760 (freq:U) (off:R) (nsym:R) (maxbits:R) (lens:U) (loff:R) :
    slot.Z420 freq off nsym maxbits lens loff ⦃ Y112P0! ⦄ := T14! slot.Z420
@[local step]
theorem u761 (freq:U) (off:R) (order:C 288#usize) (k:R) (weights:Array Std.U64 576#usize) (i:R) :
    slot.Z419_loop0 freq off order k weights i ⦃ Y112P0! ⦄ := by
  rw [slot.Z419_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 288 - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨weights1, i1⟩ _
    simp only [slot.Z419_loop0.body]
    try simp only [lift, ite_ok, alloc.vec.Vec.deref_mut, bind_tc_ok]
    step*
    all_goals repeat (first
      | (split <;> (try step*))
      | (guard_hyp x :~ _  ×  _  ×  _  ×  _  ×  _;obtain ⟨r1, r2, r3, r4, r5⟩ := x;try step*)
      | (guard_hyp x :~ _  ×  _  ×  _  ×  _;obtain ⟨r1, r2, r3, r4⟩ := x;try step*)
      | (guard_hyp x :~ _  ×  _  ×  _;obtain ⟨r1, r2, r3⟩ := x;try step*)
      | (guard_hyp x :~ _  ×  _;obtain ⟨r1, r2⟩ := x;try step*)
      | (apply Submission.EA.EH.spec_ite_cut <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _;repeat (obtain ⟨_, y⟩:_  ×  _ := y);try step*))
    all_goals scalar_tac
  · trivial
@[local step]
theorem u762 (k:R) (weights:Array Std.U64 576#usize) (parent:C 576#usize) (leaf:R) (pair:R) (next:R) (sum:Std.U64) (j:R) :
    slot.Z419_loop1_loop0 k weights parent leaf pair next sum j ⦃ Y112P0! ⦄ := by
  rw [slot.Z419_loop1_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 2 - qq9.2.2.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨parent1, leaf1, pair1, sum1, j1⟩ _
    simp only [slot.Z419_loop1_loop0.body]
    try simp only [lift, ite_ok, alloc.vec.Vec.deref_mut, bind_tc_ok]
    step*
    all_goals repeat (first
      | (split <;> (try step*))
      | (guard_hyp x :~ _  ×  _  ×  _  ×  _  ×  _;obtain ⟨r1, r2, r3, r4, r5⟩ := x;try step*)
      | (guard_hyp x :~ _  ×  _  ×  _  ×  _;obtain ⟨r1, r2, r3, r4⟩ := x;try step*)
      | (guard_hyp x :~ _  ×  _  ×  _;obtain ⟨r1, r2, r3⟩ := x;try step*)
      | (guard_hyp x :~ _  ×  _;obtain ⟨r1, r2⟩ := x;try step*)
      | (apply Submission.EA.EH.spec_ite_cut <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _;repeat (obtain ⟨_, y⟩:_  ×  _ := y);try step*))
    all_goals scalar_tac
  · trivial
@[local step]
theorem u763 (k:R) (weights:Array Std.U64 576#usize) (parent:C 576#usize) (leaf:R) (pair:R) (next:R) :
    slot.Z419_loop1 k weights parent leaf pair next ⦃ Y112P0! ⦄ := by
  rw [slot.Z419_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 575 - qq9.2.2.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨weights1, parent1, leaf1, pair1, next1⟩ _
    simp only [slot.Z419_loop1.body]
    try simp only [lift, ite_ok, alloc.vec.Vec.deref_mut, bind_tc_ok]
    step*
    all_goals repeat (first
      | (split <;> (try step*))
      | (guard_hyp x :~ _  ×  _  ×  _  ×  _  ×  _;obtain ⟨r1, r2, r3, r4, r5⟩ := x;try step*)
      | (guard_hyp x :~ _  ×  _  ×  _  ×  _;obtain ⟨r1, r2, r3, r4⟩ := x;try step*)
      | (guard_hyp x :~ _  ×  _  ×  _;obtain ⟨r1, r2, r3⟩ := x;try step*)
      | (guard_hyp x :~ _  ×  _;obtain ⟨r1, r2⟩ := x;try step*)
      | (apply Submission.EA.EH.spec_ite_cut <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _;repeat (obtain ⟨_, y⟩:_  ×  _ := y);try step*))
    all_goals scalar_tac
  · trivial
@[local step]
theorem u764 (parent:C 576#usize) (depth:C 576#usize) (mx:R) (node:R) :
    slot.Z419_loop2 parent depth mx node ⦃ Y112P0! ⦄ := by
  rw [slot.Z419_loop2]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => qq9.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨depth1, mx1, node1⟩ _
    simp only [slot.Z419_loop2.body]
    try simp only [lift, ite_ok, alloc.vec.Vec.deref_mut, bind_tc_ok]
    step*
    all_goals repeat (first
      | (split <;> (try step*))
      | (guard_hyp x :~ _  ×  _  ×  _  ×  _  ×  _;obtain ⟨r1, r2, r3, r4, r5⟩ := x;try step*)
      | (guard_hyp x :~ _  ×  _  ×  _  ×  _;obtain ⟨r1, r2, r3, r4⟩ := x;try step*)
      | (guard_hyp x :~ _  ×  _  ×  _;obtain ⟨r1, r2, r3⟩ := x;try step*)
      | (guard_hyp x :~ _  ×  _;obtain ⟨r1, r2⟩ := x;try step*)
      | (apply Submission.EA.EH.spec_ite_cut <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _;repeat (obtain ⟨_, y⟩:_  ×  _ := y);try step*))
    all_goals scalar_tac
  · trivial
@[local step]
theorem u765 (lens:U) (loff:R) (order:C 288#usize) (k:R) (depth:C 576#usize) (r:R) :
    slot.Z419_loop3 lens loff order k depth r ⦃ Y112P0! ⦄ := by
  rw [slot.Z419_loop3]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 288 - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨lens1, r1⟩ _
    simp only [slot.Z419_loop3.body]
    try simp only [lift, ite_ok, alloc.vec.Vec.deref_mut, bind_tc_ok]
    step*
    all_goals repeat (first
      | (split <;> (try step*))
      | (guard_hyp x :~ _  ×  _  ×  _  ×  _  ×  _;obtain ⟨r1, r2, r3, r4, r5⟩ := x;try step*)
      | (guard_hyp x :~ _  ×  _  ×  _  ×  _;obtain ⟨r1, r2, r3, r4⟩ := x;try step*)
      | (guard_hyp x :~ _  ×  _  ×  _;obtain ⟨r1, r2, r3⟩ := x;try step*)
      | (guard_hyp x :~ _  ×  _;obtain ⟨r1, r2⟩ := x;try step*)
      | (apply Submission.EA.EH.spec_ite_cut <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _;repeat (obtain ⟨_, y⟩:_  ×  _ := y);try step*))
    all_goals scalar_tac
  · trivial
@[local step]
theorem u766 (freq:U) (off:R) (nsym:R) (maxbits:R) (lens:U) (loff:R) :
    slot.Z419 freq off nsym maxbits lens loff ⦃ Y112P0! ⦄ := by
  rw [slot.Z419]
  step*
  all_goals simp only [lift, bind_tc_ok]
  all_goals step*
  all_goals (repeat (split <;> try step*))
  all_goals scalar_tac
@[local step]
theorem u767 (all:U) (i:R) (m:R) (v:W) (r:R) :
    slot.Z445_loop all i m v r ⦃ Y112P0! ⦄ := by
  rw [slot.Z445_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 1000 - qq9.val)
    (inv := fun _ => True)
  · rintro r1 _
    simp only [slot.Z445_loop.body, lift]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem u768 (all:U) (i:R) (m:R) :
    slot.Z445 all i m ⦃ Y112P0! ⦄ := T14! slot.Z445
@[local step]
theorem u769 (all:U) (m:R) (clf:U) (extra:Std.U64) (i:R) :
    slot.Z441_loop all m clf extra i ⦃ Y112P0! ⦄ := by
  rw [slot.Z441_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => m.val - qq9.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨clf1, extra1, i1⟩ _
    simp only [slot.Z441_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem u770 (all:U) (m:R) (clf:U) :
    slot.Z441 all m clf ⦃ Y112P0! ⦄ := T14! slot.Z441
@[local step]
theorem u771 (f:U) (foff:R) (l:U) (loff:R) (m:R) (s:Std.U64) (i:R) :
    slot.Z349_loop f foff l loff m s i ⦃ Y112P0! ⦄ := by
  rw [slot.Z349_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => m.val - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨s1, i1⟩ _
    simp only [slot.Z349_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem u772 (f:U) (foff:R) (l:U) (loff:R) (m:R) :
    slot.Z349 f foff l loff m ⦃ Y112P0! ⦄ := T14! slot.Z349
@[local step]
theorem u773 (f:U) (foff:R) (s:Std.U64) (i:R) :
    slot.Z373_loop f foff s i ⦃ Y112P0! ⦄ := by
  rw [slot.Z373_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 288 - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨s1, i1⟩ _
    simp only [slot.Z373_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem u774 (f:U) (foff:R) :
    slot.Z373 f foff ⦃ Y112P0! ⦄ := T14! slot.Z373
@[local step]
theorem u775 (f:U) (b:R) (s:Std.U64) (i:R) :
    slot.Z455_loop f b s i ⦃ Y112P0! ⦄ := by
  rw [slot.Z455_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => b.val - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨s1, i1⟩ _
    simp only [slot.Z455_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem u776 (f:U) (a:R) (b:R) :
    slot.Z455 f a b ⦃ Y112P0! ⦄ := T14! slot.Z455
@[local step]
theorem u777 (l:U) (off:R) (lo:R) (k:R) :
    slot.Z388_loop l off lo k ⦃ Y112P0! ⦄ := by
  rw [slot.Z388_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => qq9.val)
    (inv := fun _ => True)
  · rintro k1 _
    simp only [slot.Z388_loop.body, lift]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem u778 (l:U) (off:R) (m:R) (lo:R) :
    slot.Z388 l off m lo ⦃ Y112P0! ⦄ := T14! slot.Z388
@[local step]
theorem u779 (cl:U) (h:R) :
    slot.Z383_loop cl h ⦃ Y112P0! ⦄ := by
  rw [slot.Z383_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => qq9.val)
    (inv := fun _ => True)
  · rintro h1 _
    simp only [slot.Z383_loop.body, lift]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem u780 (cl:U) :
    slot.Z383 cl ⦃ Y112P0! ⦄ := T14! slot.Z383
@[local step]
theorem u781 (fr:U) (off:R) (lens:U) :
    slot.Z325 fr off lens ⦃ Y112P0! ⦄ := T14! slot.Z325
@[local step]
theorem u782 (x:Std.U64) :
    slot.Z402 x ⦃ Y112P0! ⦄ := T15! slot.Z402
set_option hygiene false in
local notation "T17!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 318 - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨sc1, s1⟩ _
    simp only [q1__, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial)
@[local step]
theorem u783 (fr:U) (off:R) (lens:U) (kind:W) (sc:U) (lt1:W) (ld:W) (s:R) :
    slot.Z456_loop fr off lens kind sc lt1 ld s ⦃ Y112P0! ⦄ := T17! slot.Z456_loop slot.Z456_loop.body
@[local step]
theorem u784 (fr:U) (off:R) (lens:U) (kind:W) (sc:U) :
    slot.Z456 fr off lens kind sc ⦃ Y112P0! ⦄ := T15! slot.Z456
@[local step]
theorem u785 (damp:W):slot.Z409 damp ⦃ Y112P0! ⦄ := by
  rw [slot.Z409];repeat (first | (split <;> step*) | scalar_tac)
@[local step]
theorem u786 (old:W) (new:W) (damp:W) :
    slot.Z323 old new damp ⦃ Y112P0! ⦄ := T15! slot.Z323
set_option hygiene false in
local notation "T18!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 256 - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨tbl1, c1⟩ _
    simp only [q1__, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial)
@[local step]
theorem u787 (sc:U) (tbl:U) (toff:R) (damp:W) (c:R) :
    slot.Z366_loop0 sc tbl toff damp c ⦃ Y112P0! ⦄ := T18! slot.Z366_loop0 slot.Z366_loop0.body
set_option hygiene false in
local notation "T19!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 259 - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨tbl1, len1⟩ _
    simp only [q1__, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial)
@[local step]
theorem u788 (sc:U) (tbl:U) (toff:R) (damp:W) (len:R) :
    slot.Z366_loop1 sc tbl toff damp len ⦃ Y112P0! ⦄ := T19! slot.Z366_loop1 slot.Z366_loop1.body
set_option hygiene false in
local notation "T20!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 30 - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨tbl1, s1⟩ _
    simp only [q1__, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial)
@[local step]
theorem u789 (sc:U) (tbl:U) (toff:R) (damp:W) (s:R) :
    slot.Z366_loop2 sc tbl toff damp s ⦃ Y112P0! ⦄ := T20! slot.Z366_loop2 slot.Z366_loop2.body
@[local step]
theorem u790 (sc:U) (tbl:U) (toff:R) (damp:W) :
    slot.Z366 sc tbl toff damp ⦃ Y112P0! ⦄ := T14! slot.Z366
@[local step]
theorem u791 (mstart:U) (mc:U) (p:R) :
    slot.Z403 mstart mc p ⦃ Y112P0! ⦄ := T15! slot.Z403
@[local step]
theorem u792 (input:I) (b:R) (fr:U) (i:R) :
    slot.Z327_loop input b fr i ⦃ Y112P0! ⦄ := by
  rw [slot.Z327_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => b.val - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨fr1, i1⟩ _
    have hmax:input.length  ≤  Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.Z327_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem u793 (input:I) (a:R) (b:R) (fr:U) :
    slot.Z327 input a b fr ⦃ Y112P0! ⦄ := T14! slot.Z327
@[local step]
theorem u794 (fr:U) (hist:C 256#usize) (c:R) :
    slot.Z319_loop fr hist c ⦃ Y112P0! ⦄ := by
  rw [slot.Z319_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 256 - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨hist1, c1⟩ _
    simp only [slot.Z319_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem u795 (fr:U) (hist:C 256#usize) :
    slot.Z319 fr hist ⦃ Y112P0! ⦄ := T14! slot.Z319
@[local step]
theorem u796 (fr:U) (lens:U) (f:R) :
    slot.Z326 fr lens f ⦃ Y112P0! ⦄ := T14! slot.Z326
@[local step]
theorem u797 (len:R) :
    slot.Z453 len ⦃ Y112P0! ⦄ := T15! slot.Z453
@[local step]
theorem u798 (lt1:W) (f:Std.U64) :
    slot.Z355 lt1 f ⦃ Y112P0! ⦄ := T14! slot.Z355
@[local step]
theorem u799 (fr:U) (tbl:U) (toff:R) (lt1:W) (c:R) :
    slot.Z385_loop0 fr tbl toff lt1 c ⦃ Y112P0! ⦄ := T18! slot.Z385_loop0 slot.Z385_loop0.body
@[local step]
theorem u800 (tbl:U) (toff:R) (len:R) :
    slot.Z385_loop1 tbl toff len ⦃ Y112P0! ⦄ := T19! slot.Z385_loop1 slot.Z385_loop1.body
@[local step]
theorem u801 (tbl:U) (toff:R) (s:R) :
    slot.Z385_loop2 tbl toff s ⦃ Y112P0! ⦄ := T20! slot.Z385_loop2 slot.Z385_loop2.body
@[local step]
theorem u802 (fr:U) (tbl:U) (toff:R) :
    slot.Z385 fr tbl toff ⦃ Y112P0! ⦄ := T15! slot.Z385
@[local step]
theorem u803 (input:I) (fr:U) (hist:C 256#usize) (tlit:U) (t5:U) (n:R) (lens:C 320#usize) (sc:C 320#usize) (total:Std.U64) (nblk:R) (b:R) :
    slot.Z399_loop input fr hist tlit t5 n lens sc total nblk b ⦃ Y112P0! ⦄ := by
  rw [slot.Z399_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => nblk.val - qq9.2.2.2.2.2.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨fr1, hist1, tlit1, t51, lens1, sc1, total1, b1⟩ _
    have hmax:input.length  ≤  Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.Z399_loop.body, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem u804 (input:I) (fr:U) (hist:C 256#usize) (tlit:U) (t5:U) :
    slot.Z399 input fr hist tlit t5 ⦃ Y112P0! ⦄ := T14! slot.Z399
@[local step]
theorem u805 (hist:C 256#usize) (n:R) :
    slot.Z321 hist n ⦃ Y112P0! ⦄ := T14! slot.Z321
@[local step]
theorem u806 (l:R) (d:R) :
    slot.Z360 l d ⦃ Y112P0! ⦄ := T15! slot.Z360
@[local step]
theorem u807 (f:R) (l:R) (d:R) :
    slot.Z359 f l d ⦃ Y112P0! ⦄ := T14! slot.Z359
@[local step]
theorem u808 (mstart:U) (mc:U) (pos:R) (st:R) (b:R) :
    slot.Z410 mstart mc pos st b ⦃ Y112P0! ⦄ := T15! slot.Z410
@[local step]
theorem u809 (mstart:U) (mc:U) (h16:W) (choice:U) (n:R) (pos:R) (nxt:R) (ec:W) (hv:R) :
    slot.Z389_loop mstart mc h16 choice n pos nxt ec hv ⦃ Y112P0! ⦄ := by
  rw [slot.Z389_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => n.val - qq9.2.1.val)
    (inv := fun _ => True)
  · rintro ⟨choice1, pos1, nxt1, ec1, hv1⟩ _
    simp only [slot.Z389_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem u810 (input:I) (mstart:U) (mc:U) (h16:W) (choice:U) :
    slot.Z389 input mstart mc h16 choice ⦃ Y112P0! ⦄ := T14! slot.Z389
@[local step]
theorem u811 (tbl:U) (toff:R) (len:R) :
    slot.Z375_loop tbl toff len ⦃ Y112P0! ⦄ := T19! slot.Z375_loop slot.Z375_loop.body
@[local step]
theorem u812 (tbl:U) (toff:R) :
    slot.Z375 tbl toff ⦃ Y112P0! ⦄ := T14! slot.Z375
@[local step]
theorem u813 (tbl:U) (toff:R) (f:R) :
    slot.Z376 tbl toff f ⦃ Y112P0! ⦄ := T14! slot.Z376
set_option hygiene false in
local notation "T21!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => lim.val - qq9.2.2.2.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨fr1, tbl1, lens1, sc1, total1, b1⟩ _
    simp only [q1__, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial)
@[local step]
theorem u814 (fr:U) (tbl:U) (damp:W) (lens:C 320#usize) (sc:C 320#usize) (total:Std.U64) (lim:R) (b:R) :
    slot.Z361_loop fr tbl damp lens sc total lim b ⦃ Y112P0! ⦄ := T21! slot.Z361_loop slot.Z361_loop.body
@[local step]
theorem u815 (fr:U) (tbl:U) (nb2:R) (nbmax:R) (damp:W) :
    slot.Z361 fr tbl nb2 nbmax damp ⦃ Y112P0! ⦄ := T14! slot.Z361
@[local step]
theorem u816 (input:I) (mstart:U) (mc:U) (tbl:U) (bend:C 512#usize) (bpos:U) (nb:R) (choice:U) (chw:R) (keep:R) (items:alloc.vec.Vec W) (istart:alloc.vec.Vec W) (pr:R) (msub:W) (co:R) (lam:W) :
    slot.Z351 input mstart mc tbl bend bpos nb choice chw keep items istart pr msub co lam ⦃ Y112P0! ⦄ := T14! slot.Z351
@[local step]
theorem u817 (prev:Std.U64) (r:Std.U64) (n:R) (it1:R) (gk:Std.U64) (minp:R) :
    slot.Z454 prev r n it1 gk minp ⦃ Y112P0! ⦄ := T15! slot.Z454
@[local step]
theorem u818 (prev:Std.U64) (n:R) (gk:Std.U64) :
    slot.Z413 prev n gk ⦃ Y112P0! ⦄ := T15! slot.Z413
@[local step]
theorem u819 (mode:R) (damp:W):slot.Z407 mode damp ⦃ Y112P0! ⦄ := by
  rw [slot.Z407];repeat (first | (split <;> step*) | scalar_tac)
@[local step]
theorem u820 (mode:R) (fr tbl:U) (nb nbmax:R) (damp ew:W) :
    slot.Z362 mode fr tbl nb nbmax damp ew ⦃ Y112P0! ⦄ := by
  rw [slot.Z362]
  step*
@[local step]
theorem u821 (x:W) :
    slot.Z397 x ⦃ Y112P0! ⦄ := T15! slot.Z397
@[local step]
theorem u822 (h:C 256#usize) (tot:Std.U64) (acc:Std.U64) (i:R) :
    slot.Z356_loop h tot acc i ⦃ Y112P0! ⦄ := by
  rw [slot.Z356_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 256 - qq9.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨tot1, acc1, i1⟩ _
    simp only [slot.Z356_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem u823 (h:C 256#usize) :
    slot.Z356 h ⦃ Y112P0! ⦄ := T14! slot.Z356
@[local step]
theorem u824 (input:I) (p:R) :
    slot.Z380 input p ⦃ Y112P0! ⦄ := T15! slot.Z380
@[local step]
theorem u825 (input:I) (ht:C 4096#usize) (s:R) (e:R) (n:R) (i:R) (cov:Std.U64) (nm:Std.U64) (it:R) :
    slot.Z425_loop input ht s e n i cov nm it ⦃ Y112P0! ⦄ := by
  rw [slot.Z425_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => slot.Z107.val - qq9.2.2.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨ht1, i1, cov1, nm1, it1⟩ _
    have hmax:input.length  ≤  Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.Z425_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem u826 (input:I) (ht:C 4096#usize) (s:R) (e:R) :
    slot.Z425 input ht s e ⦃ Y112P0! ⦄ := T15! slot.Z425
@[local step]
theorem u827 (input:I) (ht:C 4096#usize) (span:R) (acc:Std.U64) (k:R) :
    slot.Z423_loop input ht span acc k ⦃ Y112P0! ⦄ := by
  rw [slot.Z423_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => slot.Z24.val - qq9.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨ht1, acc1, k1⟩ _
    have hmax:input.length  ≤  Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.Z423_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem u828 (input:I) :
    slot.Z423 input ⦃ Y112P0! ⦄ := T15! slot.Z423
@[local step]
theorem u829 (input:I) (f:R) :
    slot.Z424 input f ⦃ Y112P0! ⦄ := T14! slot.Z424
@[local step]
theorem u830 (input:I) (h:C 256#usize) (n:R) (st:R) (k:R) (c:R) :
    slot.Z412_loop input h n st k c ⦃ Y112P0! ⦄ := by
  rw [slot.Z412_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 8192 - qq9.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨h1, k1, c1⟩ _
    have hmax:input.length  ≤  Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.Z412_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem u831 (input:I) (h:C 256#usize) :
    slot.Z412 input h ⦃ Y112P0! ⦄ := T15! slot.Z412
@[local step]
theorem u832 (a:Std.U64) (b:Std.U64) :
    slot.Z378 a b ⦃ Y112P0! ⦄ := T14! slot.Z378
@[local step]
theorem u833 (h:C 256#usize) (tot:Std.U64) (ctl:Std.U64) (hib:Std.U64) (i:R) :
    slot.Z333_loop h tot ctl hib i ⦃ Y112P0! ⦄ := by
  rw [slot.Z333_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 256 - qq9.2.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨tot1, ctl1, hib1, i1⟩ _
    simp only [slot.Z333_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem u834 (h:C 256#usize) :
    slot.Z333 h ⦃ Y112P0! ⦄ := T15! slot.Z333
@[local step]
theorem u835 (h:C 256#usize) (z0:Std.U64) (dig:Std.U64) (nz:Std.U64) (i:R) :
    slot.Z334_loop h z0 dig nz i ⦃ Y112P0! ⦄ := by
  rw [slot.Z334_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 256 - qq9.2.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨z01, dig1, nz1, i1⟩ _
    simp only [slot.Z334_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem u836 (h:C 256#usize) :
    slot.Z334 h ⦃ Y112P0! ⦄ := T15! slot.Z334
@[local step]
theorem u837 (input:I) :
    slot.Z340 input ⦃ Y112P0! ⦄ := T15! slot.Z340
@[local step]
theorem u838 (tbl:U) (seed:W) (amp:W) (off:R) (s:R) (hamp:amp.val < 33) :
    slot.Z345_loop0_loop0 tbl seed amp off s ⦃ Y112P0! ⦄ := by
  rw [slot.Z345_loop0_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 545 - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨tbl1, s1⟩ _
    simp only [slot.Z345_loop0_loop0.body]
    try simp only [lift, ite_ok, alloc.vec.Vec.deref_mut, bind_tc_ok]
    step*
    all_goals repeat (first
      | (split <;> (try step*))
      | (guard_hyp x :~ _  ×  _  ×  _  ×  _  ×  _;obtain ⟨r1, r2, r3, r4, r5⟩ := x;try step*)
      | (guard_hyp x :~ _  ×  _  ×  _  ×  _;obtain ⟨r1, r2, r3, r4⟩ := x;try step*)
      | (guard_hyp x :~ _  ×  _  ×  _;obtain ⟨r1, r2, r3⟩ := x;try step*)
      | (guard_hyp x :~ _  ×  _;obtain ⟨r1, r2⟩ := x;try step*)
      | (apply Submission.EA.EH.spec_ite_cut <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _;repeat (obtain ⟨_, y⟩:_  ×  _ := y);try step*))
    all_goals scalar_tac
  · trivial
@[local step]
theorem u839 (tbl:U) (nb:R) (seed:W) (amp:W) (b:R) (hamp:amp.val < 33) :
    slot.Z345_loop0 tbl nb seed amp b ⦃ Y112P0! ⦄ := by
  rw [slot.Z345_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => nb.val - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨tbl1, b1⟩ _
    simp only [slot.Z345_loop0.body]
    try simp only [lift, ite_ok, alloc.vec.Vec.deref_mut, bind_tc_ok]
    step*
    all_goals repeat (first
      | (split <;> (try step*))
      | (guard_hyp x :~ _  ×  _  ×  _  ×  _  ×  _;obtain ⟨r1, r2, r3, r4, r5⟩ := x;try step*)
      | (guard_hyp x :~ _  ×  _  ×  _  ×  _;obtain ⟨r1, r2, r3, r4⟩ := x;try step*)
      | (guard_hyp x :~ _  ×  _  ×  _;obtain ⟨r1, r2, r3⟩ := x;try step*)
      | (guard_hyp x :~ _  ×  _;obtain ⟨r1, r2⟩ := x;try step*)
      | (apply Submission.EA.EH.spec_ite_cut <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _;repeat (obtain ⟨_, y⟩:_  ×  _ := y);try step*))
    all_goals scalar_tac
  · trivial
set_option hygiene false in
local notation "T22!" q0__:max => (by
  rw [q0__]
  try simp only [lift, ite_ok, alloc.vec.Vec.deref_mut, bind_tc_ok]
  step*
  all_goals repeat (first
    | (split <;> (try step*))
    | (guard_hyp x :~ _  ×  _  ×  _  ×  _  ×  _;obtain ⟨r1, r2, r3, r4, r5⟩ := x;try step*)
    | (guard_hyp x :~ _  ×  _  ×  _  ×  _;obtain ⟨r1, r2, r3, r4⟩ := x;try step*)
    | (guard_hyp x :~ _  ×  _  ×  _;obtain ⟨r1, r2, r3⟩ := x;try step*)
    | (guard_hyp x :~ _  ×  _;obtain ⟨r1, r2⟩ := x;try step*)
    | (apply Submission.EA.EH.spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _;repeat (obtain ⟨_, y⟩:_  ×  _ := y);try step*))
  all_goals scalar_tac)
@[local step]
theorem u840 (tbl:U) (nb:R) (seed:W) (amplitude:W) :
    slot.Z345 tbl nb seed amplitude ⦃ Y112P0! ⦄ := T22! slot.Z345
@[local step]
theorem u841 (input:I) (mstart:U) (mc:U)
  (tbl:U) (fr:U) (bpos:U)
  (bend:C 512#usize) (choice:U)
  (plan:U) (nbmax:R) (lamh:W)
  (items:alloc.vec.Vec W) (istart:alloc.vec.Vec W)
  (pr:R) (chw:R) (n:R) (nbc:R)
  (bestp:Std.U64) (step:R) :
    slot.Z346_loop0_loop0 input mstart mc tbl fr bpos bend choice plan nbmax lamh items istart pr chw n nbc bestp step ⦃ Y112P0! ⦄ := by
  rw [slot.Z346_loop0_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun s => 3 - s.2.2.2.2.2.2.2.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨tbl1, fr1, bpos1, choice1, plan1, items1, istart1, nbc1, bestp1, step1⟩ _
    simp only [slot.Z346_loop0_loop0.body, lift, ite_ok]
    step*
    all_goals (repeat (split <;> step*))
    all_goals scalar_tac
  · trivial
@[local step]
theorem u842 (input:I) (mstart:U) (mc:U)
  (tbl:U) (fr:U) (bpos:U)
  (bend:C 512#usize) (choice:U)
  (plan:U) (nbmax:R) (lamh:W)
  (items:alloc.vec.Vec W) (istart:alloc.vec.Vec W)
  (pr:R) (chw:R) (restarts:R) (n:R)
  (jitteron:R) (restart:R) :
    slot.Z346_loop0 input mstart mc tbl fr bpos bend choice plan nbmax lamh items istart pr chw restarts n jitteron restart ⦃ Y112P0! ⦄ := by
  rw [slot.Z346_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun s => restarts.val - s.2.2.2.2.2.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨tbl1, fr1, bpos1, choice1, plan1, items1, istart1, restart1⟩ _
    simp only [slot.Z346_loop0.body, lift, ite_ok]
    step*
    all_goals (repeat (split <;> step*))
    all_goals scalar_tac
  · trivial
@[local step]
theorem u843 (input:I) (mstart:U) (mc:U)
  (tbl:U) (fr:U) (bpos:U)
  (bend:C 512#usize) (choice:U)
  (plan:U) (nbmax:R) (lamh:W)
  (items:alloc.vec.Vec W) (istart:alloc.vec.Vec W)
  (pr:R) (chw:R) (restarts:R) :
    slot.Z346 input mstart mc tbl fr bpos bend choice plan nbmax lamh items istart pr chw restarts ⦃ Y112P0! ⦄ := by
  rw [slot.Z346]
  try simp only [lift, ite_ok, alloc.vec.Vec.deref_mut, bind_tc_ok]
  step*
  all_goals (repeat (split <;> step*))
  all_goals scalar_tac
@[local step]
theorem u844 (mode:R) (input:I) (mstart:U) (mc:U) (tbl:U) (fr:U) (bpos:U) (bend:C 512#usize) (choice:U) (nbmax:R) (gk:Std.U64) (lamh:W) (minp:R) (ew:W) (n:R) (nb:R) (best:Std.U64) (prev:Std.U64) (stop:R) (it:R) (items:alloc.vec.Vec W) (istart:alloc.vec.Vec W) (kp0:R) (pr:R) (wh:R) (bh:R) (chw:R) :
    slot.Z387_loop mode input mstart mc tbl fr bpos bend choice nbmax gk lamh minp ew n nb best prev stop it items istart kp0 pr wh bh chw ⦃ Y112P0! ⦄ := by
  rw [slot.Z387_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => slot.Z98.val - qq9.2.2.2.2.2.2.2.2.1.val)
    (inv := fun _ => True)
  · rintro ⟨tbl1, fr1, bpos1, choice1, nb1, best1, prev1, stop1, it1, items1, istart1, pr1, wh1, bh1⟩ _
    have hmax:input.length  ≤  Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.Z387_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
attribute [local step] Submission.EA.EA.u1 Submission.EE.EH.u649 Submission.EE.EH.u631 Submission.EE.EH.u692 Submission.EE.EH.u632 Submission.EE.EH.u635 Submission.EE.EH.u742 Submission.EE.EH.u772 Submission.EE.EH.u790 Submission.EE.EH.u774 Submission.EE.EH.u672 Submission.EE.EH.u644 Submission.EE.EH.u780 Submission.EE.EH.u778 Submission.EE.EH.u697 Submission.EE.EH.u648 Submission.EE.EH.u760 Submission.EE.EH.u712 Submission.EE.EH.u710 Submission.EE.EH.u770 Submission.EE.EH.u698 Submission.EE.EH.u641 Submission.EE.EH.u642 Submission.EE.EH.u643 Submission.EE.EH.u776 Submission.EE.EH.u650 Submission.EE.EH.u734
@[local step]
theorem SCcharge_spec (c : Std.U64) (i : Std.Usize) (seam : Std.Usize) (trial : Std.Usize):
 slot.SCcharge c i seam trial ⦃ fun _ => True ⦄ := by
 rw [slot.SCcharge]
 step*
 repeat (split <;> step*)
 all_goals scalar_tac

@[local step]
theorem SCmatch_loop_spec (rm : Array Std.U64 4096#usize) (ct : Array Std.U32 1024#usize) (bend : Array Std.U32 512#usize) (mc : Slice Std.U32) (me : Std.Usize) (i : Std.Usize) («end» : Std.Usize) (best : Std.U64) (k : Std.Usize) (lo : Std.Usize):
 slot.SCmatch_loop rm ct bend mc me i «end» best k lo ⦃ fun _ => True ⦄ := by
 rw [slot.SCmatch_loop]
 apply Std.loop.spec_decr_nat
  (measure := fun q => me.val - q.2.1.val)
  (inv := fun _ => True)
 · rintro ⟨best1, k1, lo1⟩ _
   simp only [slot.SCmatch_loop.body]
   step*
   repeat (split <;> step*)
   all_goals (try cases x <;> step*)
   all_goals scalar_tac
 · trivial

@[local step]
theorem SCmatch_spec (rm : Array Std.U64 4096#usize) (ct : Array Std.U32 1024#usize) (bend : Array Std.U32 512#usize) (mc : Slice Std.U32) (ms : Std.Usize) (me : Std.Usize) (i : Std.Usize) («end» : Std.Usize) (lit : Std.U64):
 slot.SCmatch rm ct bend mc ms me i «end» lit ⦃ fun _ => True ⦄ := by
 rw [slot.SCmatch]
 step*
 repeat (split <;> step*)
 all_goals scalar_tac

@[local step]
theorem SCsolve_loop_spec (input : Slice Std.U8) (mstart : Slice Std.U32) (mc : Slice Std.U32) (ct : Array Std.U32 1024#usize) (bend : Array Std.U32 512#usize) (choice : Slice Std.U32) (s : Std.Usize) (e : Std.Usize) (seam : Std.Usize) (co : Std.Usize) (trial : Std.Usize) (rm : Array Std.U64 4096#usize) (i : Std.Usize):
 slot.SCsolve_loop input mstart mc ct bend choice s e seam co trial rm i ⦃ fun _ => True ⦄ := by
 rw [slot.SCsolve_loop]
 apply Std.loop.spec_decr_nat
  (measure := fun q => q.2.2.val)
  (inv := fun _ => True)
 · rintro ⟨choice1, rm1, i1⟩ _
   simp only [slot.SCsolve_loop.body]
   step*
   repeat (split <;> step*)
   all_goals (try cases x <;> step*)
   all_goals scalar_tac
 · trivial

@[local step]
theorem SCsolve_spec (input : Slice Std.U8) (mstart : Slice Std.U32) (mc : Slice Std.U32) (ct : Array Std.U32 1024#usize) (bend : Array Std.U32 512#usize) (choice : Slice Std.U32) (s : Std.Usize) (e : Std.Usize) (seam : Std.Usize) (co : Std.Usize) (trial : Std.Usize):
 slot.SCsolve input mstart mc ct bend choice s e seam co trial ⦃ fun _ => True ⦄ := by
 rw [slot.SCsolve]
 step*
 repeat (split <;> step*)
 all_goals scalar_tac

@[local step]
theorem SFblock_spec (fr : Slice Std.U32) (off : Std.Usize) (lens : Slice Std.U32):
 slot.SFblock fr off lens ⦃ fun _ => True ⦄ := by
 rw [slot.SFblock]
 step*
 repeat (split <;> step*)
 all_goals scalar_tac

@[local step]
theorem SCsum_loop_spec (fr : Slice Std.U32) (lens : Array Std.U32 320#usize) (total : Std.U64) (b : Std.Usize) (limit : Std.Usize):
 slot.SCsum_loop fr lens total b limit ⦃ fun _ => True ⦄ := by
 rw [slot.SCsum_loop]
 apply Std.loop.spec_decr_nat
  (measure := fun q => limit.val - q.2.2.2.val)
  (inv := fun _ => True)
 · rintro ⟨fr1, lens1, total1, b1⟩ _
   simp only [slot.SCsum_loop.body]
   step*
   repeat (split <;> step*)
   all_goals (try cases x <;> step*)
   all_goals scalar_tac
 · trivial

@[local step]
theorem SCsum_spec (fr : Slice Std.U32) (nb : Std.Usize) (cap : Std.Usize):
 slot.SCsum fr nb cap ⦃ fun _ => True ⦄ := by
 rw [slot.SCsum]
 step*
 repeat (split <;> step*)
 all_goals scalar_tac

@[local step]
theorem SCsymbol_loop_spec (lens : Slice Std.U32) (kind : Std.Usize) (sc : Array Std.U32 320#usize) (c : Std.Usize):
 slot.SCsymbol_loop lens kind sc c ⦃ fun _ => True ⦄ := by
 rw [slot.SCsymbol_loop]
 apply Std.loop.spec_decr_nat
  (measure := fun q => 318 - q.2.val)
  (inv := fun _ => True)
 · rintro ⟨sc1, c1⟩ _
   simp only [slot.SCsymbol_loop.body]
   step*
   repeat (split <;> step*)
   all_goals (try cases x <;> step*)
   all_goals scalar_tac
 · trivial

@[local step]
theorem SCsymbol_spec (lens : Slice Std.U32) (kind : Std.Usize) (sc : Array Std.U32 320#usize):
 slot.SCsymbol lens kind sc ⦃ fun _ => True ⦄ := by
 rw [slot.SCsymbol]
 step*
 repeat (split <;> step*)
 all_goals scalar_tac

@[local step]
theorem SCtables_loop_spec (fr : Slice Std.U32) (tbl : Slice Std.U32) (lens : Array Std.U32 320#usize) (sc : Array Std.U32 320#usize) (total : Std.U64) (b : Std.Usize) (limit : Std.Usize):
 slot.SCtables_loop fr tbl lens sc total b limit ⦃ fun _ => True ⦄ := by
 rw [slot.SCtables_loop]
 apply Std.loop.spec_decr_nat
  (measure := fun q => limit.val - q.2.2.2.2.2.val)
  (inv := fun _ => True)
 · rintro ⟨fr1, tbl1, lens1, sc1, total1, b1⟩ _
   simp only [slot.SCtables_loop.body]
   step*
   repeat (split <;> step*)
   all_goals (try cases x <;> step*)
   all_goals scalar_tac
 · trivial

@[local step]
theorem SCtables_spec (fr : Slice Std.U32) (tbl : Slice Std.U32) (nb : Std.Usize) (cap : Std.Usize):
 slot.SCtables fr tbl nb cap ⦃ fun _ => True ⦄ := by
 rw [slot.SCtables]
 step*
 repeat (split <;> step*)
 all_goals scalar_tac

@[local step]
theorem SCextra_loop0_loop0_spec (bpos : Slice Std.U32) (seam : Std.Usize) (nb : Std.Usize) (b : Std.Usize):
 slot.SCextra_loop0_loop0 bpos seam nb b ⦃ fun _ => True ⦄ := by
 rw [slot.SCextra_loop0_loop0]
 apply Std.loop.spec_decr_nat
  (measure := fun q => nb.val - q.val)
  (inv := fun _ => True)
 · rintro b1 _
   simp only [slot.SCextra_loop0_loop0.body]
   step*
   repeat (split <;> step*)
   all_goals (try cases x <;> step*)
   all_goals scalar_tac
 · trivial

@[local step]
theorem SCextra_loop0_loop1_spec (input : Slice Std.U8) (mstart : Slice Std.U32) (mc : Slice Std.U32) (fr : Slice Std.U32) (bpos : Slice Std.U32) (choice : Slice Std.U32) (plan : Slice Std.U32) (nbmax : Std.Usize) (n : Std.Usize) (co : Std.Usize) (bend : Array Std.U32 512#usize) (ct : Array Std.U32 1024#usize) (seam : Std.Usize) (last_end : Std.Usize) (base : Std.U64) (s : Std.Usize) (trial : Std.Usize):
 slot.SCextra_loop0_loop1 input mstart mc fr bpos choice plan nbmax n co bend ct seam last_end base s trial ⦃ fun _ => True ⦄ := by
 rw [slot.SCextra_loop0_loop1]
 apply Std.loop.spec_decr_nat
  (measure := fun q => slot.SCTRIALS.val - q.2.2.2.2.2.val)
  (inv := fun _ => True)
 · rintro ⟨fr1, bpos1, choice1, plan1, base1, trial1⟩ _
   simp only [slot.SCextra_loop0_loop1.body]
   step*
   repeat (split <;> step*)
   all_goals (try cases x <;> step*)
   all_goals scalar_tac
 · trivial

@[local step]
theorem SCextra_loop0_spec (input : Slice Std.U8) (mstart : Slice Std.U32) (mc : Slice Std.U32) (tbl : Slice Std.U32) (fr : Slice Std.U32) (bpos : Slice Std.U32) (choice : Slice Std.U32) (plan : Slice Std.U32) (nbmax : Std.Usize) (n : Std.Usize) (co : Std.Usize) (bend : Array Std.U32 512#usize) (ct : Array Std.U32 1024#usize) (seam : Std.Usize) (last_end : Std.Usize) (nb : Std.Usize) (base : Std.U64):
 slot.SCextra_loop0 input mstart mc tbl fr bpos choice plan nbmax n co bend ct seam last_end nb base ⦃ fun _ => True ⦄ := by
 rw [slot.SCextra_loop0]
 apply Std.loop.spec_decr_nat
  (measure := fun q => n.val - q.2.2.2.2.2.2.1.val)
  (inv := fun _ => True)
 · rintro ⟨tbl1, fr1, bpos1, choice1, plan1, ct1, seam1, last_end1, nb1, base1⟩ _
   have hplatform : 67174400 ≤ Std.Usize.max := by
     rcases System.Platform.numBits_eq with h32 | h64
     · simp [Std.Usize.max, Std.Usize.numBits, h32]
     · simp [Std.Usize.max, Std.Usize.numBits, h64]
   simp only [slot.SCextra_loop0.body]
   step*
   repeat (split <;> step*)
   all_goals (try cases x <;> step*)
   all_goals scalar_tac
 · trivial

@[local step]
theorem SCextra_spec (input : Slice Std.U8) (mstart : Slice Std.U32) (mc : Slice Std.U32) (tbl : Slice Std.U32) (fr : Slice Std.U32) (bpos : Slice Std.U32) (choice : Slice Std.U32) (plan : Slice Std.U32) (items : Slice Std.U32) (istart : Slice Std.U32) (nbmax : Std.Usize) (chw : Std.Usize) (lam : Std.U32):
 slot.SCextra input mstart mc tbl fr bpos choice plan items istart nbmax chw lam ⦃ fun _ => True ⦄ := by
 rw [slot.SCextra]
 step*
 repeat (split <;> step*)
 all_goals scalar_tac
@[local step]
theorem u845 (mode:R) (input:I) (mstart:U) (mc:U) (tbl:U) (fr:U) (bpos:U) (bend:C 512#usize) (choice:U) (plan:U) (nbmax:R) (nb0:R) (best0:Std.U64) (prev0:Std.U64) (gk:Std.U64) (lamh:W) (minp:R) (ew:W) :
    slot.Z387 mode input mstart mc tbl fr bpos bend choice plan nbmax nb0 best0 prev0 gk lamh minp ew ⦃ Y112P0! ⦄ := T15! slot.Z387
@[local step]
theorem u846 (bpos:U) (m:R) (b:R) :
    slot.Z398_loop bpos m b ⦃ Y112P0! ⦄ := by
  rw [slot.Z398_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => m.val - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨bpos1, b1⟩ _
    simp only [slot.Z398_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem u847 (bpos:U) (m:R) :
    slot.Z398 bpos m ⦃ Y112P0! ⦄ := T14! slot.Z398
@[local step]
theorem u848 (mode:R) (input:I) (mstart:U) (mc:U) (tbl:U) (fr:U) (bpos:U) (bend:C 512#usize) (choice:U) (plan:U) (nbmax:R) (gk:Std.U64) (i5:R) :
    slot.Z414 mode input mstart mc tbl fr bpos bend choice plan nbmax gk i5 ⦃ Y112P0! ⦄ := T15! slot.Z414
@[local step]
theorem u849 (mode:R) (base:Std.U64) :
    slot.Z408 mode base ⦃ Y112P0! ⦄ := by
  rw [slot.Z408]
  step*
  all_goals (repeat (split <;> step*))
  all_goals scalar_tac
@[local step]
theorem u850 (mode:R) (input:I) (plan:U) (gk:Std.U64) (i5:R) :
    slot.Z336 mode input plan gk i5 ⦃ Y112P0! ⦄ := T15! slot.Z336
@[local step]
theorem u851 (mode:R) (input:I) (plan:U) (on:R) (gk:Std.U64) (i5:R) :
    slot.Z337 mode input plan on gk i5 ⦃ Y112P0! ⦄ := T14! slot.Z337
@[local step]
theorem u852 (input:I) (out:U) (mode:R)
    (hlen:input.length  ≤  out.length) :
    slot.Z416 input out mode ⦃ Y112P1! ⦄ := by
  rw [slot.Z416]
  simp only [lift, alloc.vec.Vec.deref_mut, bind_tc_ok]
  step*
  exact ⟨r_post1, r_post2, r_post3⟩
end EH
attribute [local step] EH.u852
@[local step]
theorem u853 (input:I) (out:U) (mode:R) (hlen:input.length  ≤  out.length):slot.Z462 input out mode ⦃ Y112P1! ⦄ := Y127U14! slot.Z462
end EE
@[local step]
theorem u854 (input:I) (s:R) (hist:C 256#usize)
    (i:R) (hs:s.val  ≤  input.length) :
    slot.Z467_loop input s hist i ⦃ Y112P0! ⦄ := by
  rw [slot.Z467_loop]
  apply Std.loop.spec_decr_nat (measure := fun st => s.val - st.2.val) (inv := fun _ => True)
  · rintro ⟨h1, i1⟩ _
    simp only [slot.Z467_loop.body]
    have hmax:input.length  ≤  Std.Usize.max := Std.Slice.length_ineq input
    step*
    all_goals repeat' (first | (split <;> step*) | scalar_tac)
  · trivial
@[local step]
theorem u855 (input:I) (s:R) (hist:C 256#usize)
    (hs:s.val  ≤  input.length) :
    slot.Z467 input s hist ⦃ Y112P0! ⦄ := by
  rw [slot.Z467]
  step*
@[local step]
theorem u856 (hist:C 256#usize) (b:R) (t:Std.U64)
    (k:R) (hb:b.val  ≤  256) :
    slot.Z468_loop hist b t k ⦃ Y112P0! ⦄ := by
  rw [slot.Z468_loop]
  apply Std.loop.spec_decr_nat (measure := fun st => b.val - st.2.val) (inv := fun _ => True)
  · rintro ⟨t1, k1⟩ _
    simp only [slot.Z468_loop.body]
    step*
    all_goals repeat' (first | (split <;> step*) | scalar_tac)
  · trivial
@[local step]
theorem u857 (hist:C 256#usize) (a b:R) (hb:b.val  ≤  256) :
    slot.Z468 hist a b ⦃ Y112P0! ⦄ := by
  rw [slot.Z468]
  step*
@[local step]
theorem u858 (input:I):slot.Z469 input ⦃ Y112P0! ⦄ := by
  rw [slot.Z469]
  have hmax:input.length  ≤  Std.Usize.max := Std.Slice.length_ineq input
  step*
  all_goals repeat' (first | (split <;> step*) | scalar_tac)
theorem u859 (input:I) (out:U) (r:R)
    (hlen:input.length  ≤  out.length) :
    slot.Z463 input out r ⦃ Y112P1! ⦄ := by
  rw [slot.Z463]
  split
  · exact EA.u198 input out 0#usize hlen
  · split
    · exact EB.u579 input out 0#usize hlen
    · split
      · exact EB.u579 input out 1#usize hlen
      · split
        · exact EB.u579 input out 2#usize hlen
        · split
          · exact EB.u579 input out 3#usize hlen
          · split
            · exact EB.u579 input out 4#usize hlen
            · split
              · exact EB.u579 input out 5#usize hlen
              · exact EB.u579 input out 6#usize hlen
theorem u860 (input:I) (out:U) (r:R)
    (hlen:input.length  ≤  out.length) :
    slot.Z464 input out r ⦃ Y112P1! ⦄ := by
  rw [slot.Z464]
  split
  · exact EB.u579 input out 7#usize hlen
  · split
    · exact EB.u579 input out 8#usize hlen
    · split
      · exact EB.u579 input out 9#usize hlen
      · split
        · exact EB.u579 input out 10#usize hlen
        · split
          · exact EB.u579 input out 11#usize hlen
          · split
            · exact EC.u608 input out 0#usize hlen
            · split
              · exact EC.u608 input out 1#usize hlen
              · exact EC.u608 input out 2#usize hlen
theorem u861 (input:I) (out:U) (r:R)
    (hlen:input.length  ≤  out.length) :
    slot.Z465 input out r ⦃ Y112P1! ⦄ := by
  rw [slot.Z465]
  split
  · exact EC.u608 input out 3#usize hlen
  · split
    · exact EC.u608 input out 4#usize hlen
    · split
      · exact EC.u608 input out 5#usize hlen
      · split
        · exact ED.u621 input out 0#usize hlen
        · split
          · exact ED.u621 input out 1#usize hlen
          · split
            · exact ED.u621 input out 2#usize hlen
            · split
              · exact ED.u621 input out 3#usize hlen
              · exact ED.u621 input out 4#usize hlen
theorem u862 (input:I) (out:U) (r:R)
    (hlen:input.length  ≤  out.length) :
    slot.Z466 input out r ⦃ Y112P1! ⦄ := by
  rw [slot.Z466]
  split
  · exact ED.u621 input out 5#usize hlen
  · split
    · exact EE.u853 input out 0#usize hlen
    · split
      · exact EE.u853 input out 1#usize hlen
      · exact EE.u853 input out 2#usize hlen
theorem SFbase_spec (input:I) (out:U)
    (hlen:input.length  ≤  out.length) :
    slot.SFbase input out ⦃ Y112P1! ⦄ := by
  rw [slot.SFbase]
  apply Std.WP.spec_bind (u858 input)
  intro r _
  split
  · exact u859 input out r hlen
  · split
    · exact u860 input out r hlen
    · split
      · exact u861 input out r hlen
      · exact u862 input out r hlen
attribute [local step] Submission.EE.EH.SFblock_spec
attribute [local step] Submission.EA.EA.u100 Submission.EA.EA.u26 Submission.EA.EA.u1 Submission.EA.EA.u28 Submission.EE.EH.u649 Submission.EE.EH.u631 Submission.EE.EH.u692 Submission.EE.EH.u632 Submission.EE.EH.u635 Submission.EE.EH.u730 Submission.EE.EH.u742 Submission.EE.EH.u669 Submission.EE.EH.u772 Submission.EE.EH.u654 Submission.EE.EH.u774 Submission.EE.EH.u780 Submission.EE.EH.u778 Submission.EE.EH.u670 Submission.EE.EH.u671 Submission.EE.EH.u648 Submission.EE.EH.u760 Submission.EE.EH.u640 Submission.EE.EH.u712 Submission.EE.EH.u710 Submission.EE.EH.u770 Submission.EE.EH.u698 Submission.EE.EH.u642 Submission.EE.EH.u643 Submission.EE.EH.u776 Submission.EE.EH.u650 Submission.EE.EH.u732
@[local step]
theorem SFlen_spec (t : Std.U32) :
    slot.SFlen t ⦃ fun _ => True ⦄ := by
  rw [slot.SFlen]
  step*
  repeat (split <;> step*)
  all_goals scalar_tac

@[local step]
theorem SFdist_spec (t : Std.U32) :
    slot.SFdist t ⦃ fun _ => True ⦄ := by
  rw [slot.SFdist]
  step*
  repeat (split <;> step*)
  all_goals scalar_tac

@[local step]
theorem SFmt_spec (d : Std.Usize) (l : Std.Usize) :
    slot.SFmt d l ⦃ fun _ => True ⦄ := by
  rw [slot.SFmt]
  step*
  repeat (split <;> step*)
  all_goals scalar_tac

@[local step]
theorem SFhash_spec (input : Slice Std.U8) (p : Std.Usize) :
    slot.SFhash input p ⦃ fun _ => True ⦄ := by
  rw [slot.SFhash]
  step*
  repeat (split <;> step*)
  all_goals scalar_tac

@[local step]
theorem SFprev_loop_spec (input : Slice Std.U8) (v : alloc.vec.Vec Std.U32) (head : Array Std.U32 65536#usize) (p : Std.Usize) :
    slot.SFprev_loop input v head p ⦃ fun _ => True ⦄ := by
  rw [slot.SFprev_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun q => input.length - q.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨v1, head1, p1⟩ _
    simp only [slot.SFprev_loop.body]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial

@[local step]
theorem SFprev_spec (input : Slice Std.U8) :
    slot.SFprev input ⦃ fun _ => True ⦄ := by
  rw [slot.SFprev]
  step*
  repeat (split <;> step*)
  all_goals scalar_tac

@[local step]
theorem SFpositions_loop_spec (ts : Slice Std.U32) (v : alloc.vec.Vec Std.U32) (p : Std.U32) (j : Std.Usize) :
    slot.SFpositions_loop ts v p j ⦃ fun _ => True ⦄ := by
  rw [slot.SFpositions_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun q => ts.length - q.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨v1, p1, j1⟩ _
    simp only [slot.SFpositions_loop.body]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial

@[local step]
theorem SFpositions_spec (ts : Slice Std.U32) :
    slot.SFpositions ts ⦃ fun _ => True ⦄ := by
  rw [slot.SFpositions]
  step*
  repeat (split <;> step*)
  all_goals scalar_tac

@[local step]
theorem SFcopy_loop_spec (src : Slice Std.U32) (b : Std.Usize) (dst : alloc.vec.Vec Std.U32) (j : Std.Usize) :
    slot.SFcopy_loop src b dst j ⦃ fun _ => True ⦄ := by
  rw [slot.SFcopy_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun q => b.val - q.2.val)
    (inv := fun _ => True)
  · rintro ⟨dst1, j1⟩ _
    simp only [slot.SFcopy_loop.body]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial

@[local step]
theorem SFcopy_spec (src : Slice Std.U32) (a : Std.Usize) (b : Std.Usize) (dst : alloc.vec.Vec Std.U32) :
    slot.SFcopy src a b dst ⦃ fun _ => True ⦄ := by
  rw [slot.SFcopy]
  step*
  repeat (split <;> step*)
  all_goals scalar_tac

@[local step]
theorem SFhist_loop_spec (ts : Slice Std.U32) (hi : Std.Usize) (fr : Slice Std.U32) (j : Std.Usize) :
    slot.SFhist_loop ts hi fr j ⦃ fun _ => True ⦄ := by
  rw [slot.SFhist_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun q => hi.val - q.2.val)
    (inv := fun _ => True)
  · rintro ⟨fr1, j1⟩ _
    simp only [slot.SFhist_loop.body]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial

@[local step]
theorem SFhist_spec (ts : Slice Std.U32) (lo : Std.Usize) (hi : Std.Usize) (fr : Slice Std.U32) :
    slot.SFhist ts lo hi fr ⦃ fun _ => True ⦄ := by
  rw [slot.SFhist]
  step*
  repeat (split <;> step*)
  all_goals scalar_tac

@[local step]
theorem SFcost_loop_spec (ts : Slice Std.U32) (total : Std.U64) (j : Std.Usize) (t : Std.Usize) (fr : Array Std.U32 320#usize) (lens : Array Std.U32 320#usize) :
    slot.SFcost_loop ts total j t fr lens ⦃ fun _ => True ⦄ := by
  rw [slot.SFcost_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun q => ts.length - q.2.1.val)
    (inv := fun _ => True)
  · rintro ⟨total1, j1, t1, fr1, lens1⟩ _
    simp only [slot.SFcost_loop.body]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial

@[local step]
theorem SFcost_spec (ts : Slice Std.U32) :
    slot.SFcost ts ⦃ fun _ => True ⦄ := by
  rw [slot.SFcost]
  step*
  repeat (split <;> step*)
  all_goals scalar_tac

@[local step]
theorem SFtable_loop0_spec (ct : Array Std.U32 1024#usize) (lens : Array Std.U32 320#usize) (c : Std.Usize) :
    slot.SFtable_loop0 ct lens c ⦃ fun _ => True ⦄ := by
  rw [slot.SFtable_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun q => 256 - q.2.val)
    (inv := fun _ => True)
  · rintro ⟨ct1, c1⟩ _
    simp only [slot.SFtable_loop0.body]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial

@[local step]
theorem SFtable_loop1_spec (ct : Array Std.U32 1024#usize) (lens : Array Std.U32 320#usize) (l : Std.Usize) :
    slot.SFtable_loop1 ct lens l ⦃ fun _ => True ⦄ := by
  rw [slot.SFtable_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun q => 259 - q.2.val)
    (inv := fun _ => True)
  · rintro ⟨ct1, l1⟩ _
    simp only [slot.SFtable_loop1.body]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial

@[local step]
theorem SFtable_loop2_spec (ct : Array Std.U32 1024#usize) (lens : Array Std.U32 320#usize) (d : Std.Usize) :
    slot.SFtable_loop2 ct lens d ⦃ fun _ => True ⦄ := by
  rw [slot.SFtable_loop2]
  apply Std.loop.spec_decr_nat
    (measure := fun q => 30 - q.2.val)
    (inv := fun _ => True)
  · rintro ⟨ct1, d1⟩ _
    simp only [slot.SFtable_loop2.body]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial

@[local step]
theorem SFtable_spec (ts : Slice Std.U32) (lo : Std.Usize) (hi : Std.Usize) (ct : Array Std.U32 1024#usize) :
    slot.SFtable ts lo hi ct ⦃ fun _ => True ⦄ := by
  rw [slot.SFtable]
  step*
  repeat (split <;> step*)
  all_goals scalar_tac

@[local step]
theorem SForig_loop0_loop0_spec (v : alloc.vec.Vec Std.U32) (t : Std.U32) (l : Std.Usize) (d : Std.Usize) (start : Std.Usize) (x : Std.Usize) :
    slot.SForig_loop0_loop0 v t l d start x ⦃ fun _ => True ⦄ := by
  rw [slot.SForig_loop0_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun q => 256 - q.2.val)
    (inv := fun _ => True)
  · rintro ⟨v1, x1⟩ _
    simp only [slot.SForig_loop0_loop0.body, lift, alloc.vec.Vec.deref_mut, bind_tc_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial

@[local step]
theorem SForig_loop0_spec (ts : Slice Std.U32) (p : Slice Std.U32) (hi : Std.Usize) (a : Std.Usize) (v : alloc.vec.Vec Std.U32) (j : Std.Usize) :
    slot.SForig_loop0 ts p hi a v j ⦃ fun _ => True ⦄ := by
  rw [slot.SForig_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun q => hi.val - q.2.val)
    (inv := fun _ => True)
  · rintro ⟨v1, j1⟩ _
    simp only [slot.SForig_loop0.body]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial

@[local step]
theorem SForig_spec (ts : Slice Std.U32) (p : Slice Std.U32) (lo : Std.Usize) (hi : Std.Usize) (a : Std.Usize) (n : Std.Usize) :
    slot.SForig ts p lo hi a n ⦃ fun _ => True ⦄ := by
  rw [slot.SForig]
  step*
  repeat (split <;> step*)
  all_goals scalar_tac

@[local step]
theorem SFmatchlen_loop_spec (input : Slice Std.U8) (a : Std.Usize) (b : Std.Usize) (cap : Std.Usize) (l : Std.Usize):
 slot.SFmatchlen_loop input a b cap l ⦃ fun _ => True ⦄ := by
 rw [slot.SFmatchlen_loop]
 apply Std.loop.spec_decr_nat
  (measure := fun q => 258 - q.val)
  (inv := fun _ => True)
 · rintro l1 _
   simp only [slot.SFmatchlen_loop.body, lift, alloc.vec.Vec.deref_mut, bind_tc_ok]
   step*
   repeat (split <;> step*)
   all_goals (try cases x <;> step*)
   all_goals scalar_tac
 · trivial

@[local step]
theorem SFmatchlen_spec (input : Slice Std.U8) (a : Std.Usize) (b : Std.Usize) (cap : Std.Usize) (known : Std.Usize):
 slot.SFmatchlen input a b cap known ⦃ fun _ => True ⦄ := by
 rw [slot.SFmatchlen]
 step*
 repeat (split <;> step*)
 all_goals scalar_tac

@[local step]
theorem SFsmalladd_loop_spec (best : Array Std.U32 4#usize) (count : Std.Usize) (t : Std.U32) (j : Std.Usize) (dc : Std.Usize):
 slot.SFsmalladd_loop best count t j dc ⦃ fun _ => True ⦄ := by
 rw [slot.SFsmalladd_loop]
 apply Std.loop.spec_decr_nat
  (measure := fun q => 4 - q.val)
  (inv := fun _ => True)
 · rintro j1 _
   simp only [slot.SFsmalladd_loop.body, lift, alloc.vec.Vec.deref_mut, bind_tc_ok]
   step*
   repeat (split <;> step*)
   all_goals (try cases x <;> step*)
   all_goals scalar_tac
 · trivial

@[local step]
theorem SFsmalladd_spec (best : Array Std.U32 4#usize) (count : Std.Usize) (t : Std.U32):
 slot.SFsmalladd best count t ⦃ fun _ => True ⦄ := by
 rw [slot.SFsmalladd]
 step*
 repeat (split <;> step*)
 all_goals scalar_tac

@[local step]
theorem SFsmallkeep_loop_spec (best : Array Std.U32 4#usize) (count : Std.Usize) (j : Std.Usize) (ct : Array Std.U32 1024#usize) (price : Std.U32) (l : Std.Usize) (k : Std.Usize):
 slot.SFsmallkeep_loop best count j ct price l k ⦃ fun _ => True ⦄ := by
 rw [slot.SFsmallkeep_loop]
 apply Std.loop.spec_decr_nat
  (measure := fun q => 4 - q.val)
  (inv := fun _ => True)
 · rintro k1 _
   simp only [slot.SFsmallkeep_loop.body, lift, alloc.vec.Vec.deref_mut, bind_tc_ok]
   step*
   repeat (split <;> step*)
   all_goals (try cases x <;> step*)
   all_goals scalar_tac
 · trivial

@[local step]
theorem SFsmallkeep_spec (best : Array Std.U32 4#usize) (count : Std.Usize) (j : Std.Usize) (ct : Array Std.U32 1024#usize):
 slot.SFsmallkeep best count j ct ⦃ fun _ => True ⦄ := by
 rw [slot.SFsmallkeep]
 step*
 repeat (split <;> step*)
 all_goals scalar_tac

@[local step]
theorem SFknown_spec (ot : Std.U32) (d : Std.Usize) (cap : Std.Usize) :
 slot.SFknown ot d cap ⦃ fun _ => True ⦄ := by
 rw [slot.SFknown]
 step*
 repeat (split <;> step*)
 all_goals scalar_tac

@[local step]
theorem SFlookup_spec (prev : Slice Std.U32) (p : Std.Usize) (ot : Std.U32) :
 slot.SFlookup prev p ot ⦃ fun _ => True ⦄ := by
 rw [slot.SFlookup]
 step*
 repeat (split <;> step*)
 all_goals scalar_tac

@[local step]
theorem SFsmallmatches_loop0_loop0_spec (input : Slice Std.U8) (prev : Slice Std.U32) (e : Std.Usize) (p : Std.Usize) (best : Array Std.U32 4#usize) (ot : Std.U32) (count : Std.Usize) (q : Std.Usize) (k : Std.Usize):
 slot.SFsmallmatches_loop0_loop0 input prev e p best ot count q k ⦃ fun _ => True ⦄ := by
 rw [slot.SFsmallmatches_loop0_loop0]
 apply Std.loop.spec_decr_nat
  (measure := fun q => slot.SFDEPTH.val - q.2.2.2.val)
  (inv := fun _ => True)
 · rintro ⟨best1, count1, q1, k1⟩ _
   simp only [slot.SFsmallmatches_loop0_loop0.body, lift, alloc.vec.Vec.deref_mut, bind_tc_ok]
   step*
   repeat (split <;> step*)
   all_goals (try cases x <;> step*)
   all_goals scalar_tac
 · trivial

@[local step]
theorem SFsmallmatches_loop0_loop1_spec (ct : Array Std.U32 1024#usize) (items : alloc.vec.Vec Std.U32) (best : Array Std.U32 4#usize) (count : Std.Usize) (c : Std.Usize):
 slot.SFsmallmatches_loop0_loop1 ct items best count c ⦃ fun _ => True ⦄ := by
 rw [slot.SFsmallmatches_loop0_loop1]
 apply Std.loop.spec_decr_nat
  (measure := fun q => 4 - q.2.val)
  (inv := fun _ => True)
 · rintro ⟨items1, c1⟩ _
   simp only [slot.SFsmallmatches_loop0_loop1.body, lift, alloc.vec.Vec.deref_mut, bind_tc_ok]
   step*
   repeat (split <;> step*)
   all_goals (try cases x <;> step*)
   all_goals scalar_tac
 · trivial

@[local step]
theorem SFsmallmatches_loop0_spec (input : Slice Std.U8) (prev : Slice Std.U32) (orig : Slice Std.U32) (ct : Array Std.U32 1024#usize) (a : Std.Usize) (e : Std.Usize) (items : alloc.vec.Vec Std.U32) (starts : alloc.vec.Vec Std.U32) (p : Std.Usize):
 slot.SFsmallmatches_loop0 input prev orig ct a e items starts p ⦃ fun _ => True ⦄ := by
 rw [slot.SFsmallmatches_loop0]
 apply Std.loop.spec_decr_nat
  (measure := fun q => e.val - q.2.2.val)
  (inv := fun _ => True)
 · rintro ⟨items1, starts1, p1⟩ _
   simp only [slot.SFsmallmatches_loop0.body, lift, alloc.vec.Vec.deref_mut, bind_tc_ok]
   step*
   repeat (split <;> step*)
   all_goals (try cases x <;> step*)
   all_goals scalar_tac
 · trivial

@[local step]
theorem SFsmallmatches_spec (input : Slice Std.U8) (prev : Slice Std.U32) (orig : Slice Std.U32) (ct : Array Std.U32 1024#usize) (a : Std.Usize) (e : Std.Usize) (items : alloc.vec.Vec Std.U32) (starts : alloc.vec.Vec Std.U32):
 slot.SFsmallmatches input prev orig ct a e items starts ⦃ fun _ => True ⦄ := by
 rw [slot.SFsmallmatches]
 step*
 repeat (split <;> step*)
 all_goals scalar_tac

@[local step]
theorem SFpriced_spec (c : Std.U32) (lambda : Std.Usize) (before : Bool) :
    slot.SFpriced c lambda before ⦃ fun _ => True ⦄ := by
  rw [slot.SFpriced]
  step*
  repeat (split <;> step*)
  all_goals scalar_tac

@[local step]
theorem SFsolve_loop0_loop0_spec (items : Slice Std.U32) (ct : Array Std.U32 1024#usize) (i : Std.Usize) (rm : Array Std.U64 4096#usize) (bend : Array Std.U32 512#usize) (bc : Std.U64) (bt : Std.U32) (k : Std.Usize) («end» : Std.Usize) :
    slot.SFsolve_loop0_loop0 items ct i rm bend bc bt k «end» ⦃ fun _ => True ⦄ := by
  rw [slot.SFsolve_loop0_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun q => «end».val - q.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨bc1, bt1, k1⟩ _
    simp only [slot.SFsolve_loop0_loop0.body]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial

@[local step]
theorem SFsolve_loop0_spec (input : Slice Std.U8) (a : Std.Usize) (seam : Std.Usize) (items : Slice Std.U32) (starts : Slice Std.U32) (ct : Array Std.U32 1024#usize) (lambda : Std.Usize) (ch : alloc.vec.Vec Std.U32) (i : Std.Usize) (rm : Array Std.U64 4096#usize) (bend : Array Std.U32 512#usize) :
    slot.SFsolve_loop0 input a seam items starts ct lambda ch i rm bend ⦃ fun _ => True ⦄ := by
  rw [slot.SFsolve_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun q => q.2.1.val)
    (inv := fun _ => True)
  · rintro ⟨ch1, i1, rm1⟩ _
    simp only [slot.SFsolve_loop0.body, lift, alloc.vec.Vec.deref_mut, bind_tc_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial

@[local step]
theorem SFsolve_spec (input : Slice Std.U8) (a : Std.Usize) (e : Std.Usize) (seam : Std.Usize) (items : Slice Std.U32) (starts : Slice Std.U32) (ct : Array Std.U32 1024#usize) (lambda : Std.Usize) :
    slot.SFsolve input a e seam items starts ct lambda ⦃ fun _ => True ⦄ := by
  rw [slot.SFsolve]
  step*
  repeat (split <;> step*)
  all_goals scalar_tac

@[local step]
theorem SFpatch_loop_spec (ch : Slice Std.U32) (v : alloc.vec.Vec Std.U32) (i : Std.Usize) (j : Std.Usize) :
    slot.SFpatch_loop ch v i j ⦃ fun _ => True ⦄ := by
  rw [slot.SFpatch_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun q => ch.length - q.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨v1, i1, j1⟩ _
    simp only [slot.SFpatch_loop.body]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial

@[local step]
theorem SFpatch_spec (ts : Slice Std.U32) (lo : Std.Usize) (hi : Std.Usize) (ch : Slice Std.U32) :
    slot.SFpatch ts lo hi ch ⦃ fun _ => True ⦄ := by
  rw [slot.SFpatch]
  step*
  repeat (split <;> step*)
  all_goals scalar_tac

@[local step]
theorem SFplan_loop_spec (ts : Slice Std.U32) (plan : alloc.vec.Vec Std.U32) (p : Std.Usize) (j : Std.Usize) :
    slot.SFplan_loop ts plan p j ⦃ fun _ => True ⦄ := by
  rw [slot.SFplan_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun q => ts.length - q.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨plan1, p1, j1⟩ _
    simp only [slot.SFplan_loop.body, lift, alloc.vec.Vec.deref_mut, bind_tc_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial

@[local step]
theorem SFplan_spec (ts : Slice Std.U32) (n : Std.Usize) :
    slot.SFplan ts n ⦃ fun _ => True ⦄ := by
  rw [slot.SFplan]
  step*
  repeat (split <;> step*)
  all_goals scalar_tac

@[local step]
theorem SFcachedtrial_loop0_loop0_spec (cache : Slice Std.U32) (fr : Array Std.U32 320#usize) (off : Std.Usize) (c : Std.Usize) :
    slot.SFcachedtrial_loop0_loop0 cache fr off c ⦃ fun _ => True ⦄ := by
  rw [slot.SFcachedtrial_loop0_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun q => 320 - q.2.val)
    (inv := fun _ => True)
  · rintro ⟨fr1, c1⟩ _
    simp only [slot.SFcachedtrial_loop0_loop0.body]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial

@[local step]
theorem SFcachedtrial_loop0_loop1_spec (result : alloc.vec.Vec Std.U32) (fr : Array Std.U32 320#usize) (c : Std.Usize) :
    slot.SFcachedtrial_loop0_loop1 result fr c ⦃ fun _ => True ⦄ := by
  rw [slot.SFcachedtrial_loop0_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun q => 320 - q.2.val)
    (inv := fun _ => True)
  · rintro ⟨result1, c1⟩ _
    simp only [slot.SFcachedtrial_loop0_loop1.body]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial

@[local step]
theorem SFcachedtrial_loop0_loop2_spec (cache : Slice Std.U32) (fr : Array Std.U32 320#usize) (off : Std.Usize) (add : Array Std.U32 320#usize) (sub : Array Std.U32 320#usize) (c : Std.Usize) :
    slot.SFcachedtrial_loop0_loop2 cache fr off add sub c ⦃ fun _ => True ⦄ := by
  rw [slot.SFcachedtrial_loop0_loop2]
  apply Std.loop.spec_decr_nat
    (measure := fun q => 320 - q.2.val)
    (inv := fun _ => True)
  · rintro ⟨fr1, c1⟩ _
    simp only [slot.SFcachedtrial_loop0_loop2.body]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial

@[local step]
theorem SFcachedtrial_loop0_loop3_spec (result : alloc.vec.Vec Std.U32) (fr : Array Std.U32 320#usize) (c : Std.Usize) :
    slot.SFcachedtrial_loop0_loop3 result fr c ⦃ fun _ => True ⦄ := by
  rw [slot.SFcachedtrial_loop0_loop3]
  apply Std.loop.spec_decr_nat
    (measure := fun q => 320 - q.2.val)
    (inv := fun _ => True)
  · rintro ⟨result1, c1⟩ _
    simp only [slot.SFcachedtrial_loop0_loop3.body]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial

@[local step]
theorem SFcachedtrial_loop0_loop4_spec (result : alloc.vec.Vec Std.U32) (fr : Array Std.U32 320#usize) (c : Std.Usize) :
    slot.SFcachedtrial_loop0_loop4 result fr c ⦃ fun _ => True ⦄ := by
  rw [slot.SFcachedtrial_loop0_loop4]
  apply Std.loop.spec_decr_nat
    (measure := fun q => 320 - q.2.val)
    (inv := fun _ => True)
  · rintro ⟨result1, c1⟩ _
    simp only [slot.SFcachedtrial_loop0_loop4.body]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial

@[local step]
theorem SFcachedtrial_loop0_spec (ts : Slice Std.U32) (old : Slice Std.U32) (cache : Slice Std.U32) (lo : Std.Usize) (result : alloc.vec.Vec Std.U32) (positive : Bool) (shift : Std.Usize) (changed_end : Std.Usize) (total : Std.U64) (start : Std.Usize) (b : Std.Usize) (fuel : Std.Usize) :
    slot.SFcachedtrial_loop0 ts old cache lo result positive shift changed_end total start b fuel ⦃ fun _ => True ⦄ := by
  rw [slot.SFcachedtrial_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun q => ts.length - q.2.2.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨result1, total1, start1, b1, fuel1⟩ _
    simp only [slot.SFcachedtrial_loop0.body]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial

@[local step]
theorem SFcachedtrial_spec (ts : Slice Std.U32) (old : Slice Std.U32) (cache : Slice Std.U32) (lo : Std.Usize) (hi : Std.Usize) (result : alloc.vec.Vec Std.U32) :
    slot.SFcachedtrial ts old cache lo hi result ⦃ fun _ => True ⦄ := by
  rw [slot.SFcachedtrial]
  step*
  repeat (split <;> step*)
  all_goals scalar_tac

@[local step]
theorem SFcache_loop0_loop0_spec (v : alloc.vec.Vec Std.U32) (fr : Array Std.U32 320#usize) (c : Std.Usize) :
    slot.SFcache_loop0_loop0 v fr c ⦃ fun _ => True ⦄ := by
  rw [slot.SFcache_loop0_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun q => 320 - q.2.val)
    (inv := fun _ => True)
  · rintro ⟨v1, c1⟩ _
    simp only [slot.SFcache_loop0_loop0.body]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial

@[local step]
theorem SFcache_loop0_loop1_spec (v : alloc.vec.Vec Std.U32) (fr : Array Std.U32 320#usize) (c : Std.Usize) :
    slot.SFcache_loop0_loop1 v fr c ⦃ fun _ => True ⦄ := by
  rw [slot.SFcache_loop0_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun q => 320 - q.2.val)
    (inv := fun _ => True)
  · rintro ⟨v1, c1⟩ _
    simp only [slot.SFcache_loop0_loop1.body]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial

@[local step]
theorem SFcache_loop0_spec (ts : Slice Std.U32) (v : alloc.vec.Vec Std.U32) (fr : Array Std.U32 320#usize) (lens : Array Std.U32 320#usize) (j : Std.Usize) (t : Std.Usize) :
    slot.SFcache_loop0 ts v fr lens j t ⦃ fun _ => True ⦄ := by
  rw [slot.SFcache_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun q => ts.length - q.2.2.2.1.val)
    (inv := fun _ => True)
  · rintro ⟨v1, fr1, lens1, j1, t1⟩ _
    simp only [slot.SFcache_loop0.body]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial

@[local step]
theorem SFcache_spec (ts : Slice Std.U32) :
    slot.SFcache ts ⦃ fun _ => True ⦄ := by
  rw [slot.SFcache]
  step*
  repeat (split <;> step*)
  all_goals scalar_tac

@[local step]
theorem SFshape_loop0_loop0_spec (ts : alloc.vec.Vec Std.U32) (seam : Std.Usize) (p : alloc.vec.Vec Std.U32) (k : Std.Usize):
 slot.SFshape_loop0_loop0 ts seam p k ⦃ fun _ => True ⦄ := by
 rw [slot.SFshape_loop0_loop0]
 apply Std.loop.spec_decr_nat
  (measure := fun q => ts.length - q.val)
  (inv := fun _ => True)
 · rintro k1 _
   simp only [slot.SFshape_loop0_loop0.body, lift, alloc.vec.Vec.deref_mut, bind_tc_ok]
   step*
   repeat (split <;> step*)
   all_goals (try cases x <;> step*)
   all_goals scalar_tac
 · trivial

@[local step]
theorem SFshape_loop0_loop1_spec (input : Slice Std.U8) (ts : alloc.vec.Vec Std.U32) (last_end : Std.Usize) (seam : Std.Usize) (lo : Std.Usize) (hi : Std.Usize) (a : Std.Usize) (ct : Array Std.U32 1024#usize) (items : alloc.vec.Vec Std.U32) (starts : alloc.vec.Vec Std.U32) (lambda : Std.Usize) (next : alloc.vec.Vec Std.U32) (found : Bool):
 slot.SFshape_loop0_loop1 input ts last_end seam lo hi a ct items starts lambda next found ⦃ fun _ => True ⦄ := by
 rw [slot.SFshape_loop0_loop1]
 apply Std.loop.spec_decr_nat
  (measure := fun q => 1 - q.1.val)
  (inv := fun _ => True)
 · rintro ⟨lambda1, next1, found1⟩ _
   simp only [slot.SFshape_loop0_loop1.body, lift, alloc.vec.Vec.deref_mut, bind_tc_ok]
   step*
   repeat (split <;> step*)
   all_goals (try cases x <;> step*)
   all_goals scalar_tac
 · trivial

@[local step]
theorem SFshape_loop0_spec (input : Slice Std.U8) (ts : alloc.vec.Vec Std.U32) (prev : alloc.vec.Vec Std.U32) (s : Std.Usize) (last_end : Std.Usize):
 slot.SFshape_loop0 input ts prev s last_end ⦃ fun _ => True ⦄ := by
 rw [slot.SFshape_loop0]
 apply Std.loop.spec_decr_nat
  (measure := fun q => input.length / 65536 + 1 - q.2.1.val)
  (inv := fun _ => True)
 · rintro ⟨ts1, s1, last_end1⟩ _
   simp only [slot.SFshape_loop0.body, lift, alloc.vec.Vec.deref_mut, bind_tc_ok]
   step*
   repeat (split <;> step*)
   all_goals (try cases x <;> step*)
   all_goals scalar_tac
 · trivial

@[local step]
theorem SFshape_spec (input : Slice Std.U8) (out : Slice Std.U32) (nt : Std.Usize):
 slot.SFshape input out nt ⦃ fun _ => True ⦄ := by
 rw [slot.SFshape]
 step*
 repeat (split <;> step*)
 all_goals scalar_tac

@[local step]
theorem SFenabled_spec (input : Slice Std.U8) :
    slot.SFenabled input ⦃ fun _ => True ⦄ := by
  rw [slot.SFenabled]
  step*
  repeat (split <;> step*)
  all_goals scalar_tac


theorem parse_spec (input:I) (out:U)
    (hlen:input.length ≤ out.length) :
    slot.parse input out ⦃ Y112P1! ⦄ := by
  rw [slot.parse]
  exact SFbase_spec input out hlen

end Submission

