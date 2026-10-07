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
local notation "Y112P2!" => (fun r => True)
set_option hygiene false in
local notation "Y112P3!" => (fun l => l.val  ≤  cap.val  ∧  Matches input a.val b.val l.val)
set_option hygiene false in
local notation "Y112P4!" => (fun r => r.1.val  ≤  input.length  ∧  r.2.length = out0.length  ∧  LZ77.decode (toks r.2 r.1.val) = some (bytes input))
set_option hygiene false in
local notation "Y112P5!" => (fun r => r.1.val  ≤  input.length  ∧  r.2.length = out.length  ∧  LZ77.decode (toks r.2 r.1.val) = some (bytes input))
set_option hygiene false in
local notation "Y112P6!" => (fun r => prev.val  ≤  r.2.2.1.val  ∧  r.2.2.1.val  ≤  i.val + 258  ∧  r.2.2.2.val  ≤  32768  ∧  r.2.1.val  ≤  32767)
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
set_option hygiene false in
local notation "Y127U1!" q0__:max => (by
  rw [q0__]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac)
set_option hygiene false in
local notation "Y127U2!" q0__:max => (by
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
local notation "Y127U3!" q0__:max => (by
  rw [q0__]
  step*
  all_goals (first | assumption | (subst_vars;scalar_tac (simpAllMaxSteps := 0)) |
    (refine ⟨by assumption, by assumption, ?_⟩;unfold LZ77.Valid;assumption) |
    (refine ⟨by assumption, by (subst_vars;scalar_tac (simpAllMaxSteps := 0)), ?_⟩;unfold LZ77.Valid;assumption)))
namespace EA
open Aeneas Aeneas.Std Result ControlFlow
set_option maxRecDepth 8192
set_option maxHeartbeats 1000000
set_option linter.unusedTactic false
set_option linter.unreachableTactic false
set_option linter.unusedSimpArgs false
set_option linter.unusedVariables false
attribute [-instance] instNoNatZeroDivisorsOfIsAddTorsionFree
open LZ77 (toks bytes bytes_getElem! Matches emit_lit emit_match)
@[step]
theorem u0 {α:Type} (x:α):lift x ⦃ fun y => y = x ⦄ := by
  simp [lift, WP.spec_ok]
@[step]
theorem u1 (v:U) (i:R):slot.Z148 v i ⦃ Y112P0! ⦄ := by
  rw [slot.Z148];split <;> step*
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
theorem LeAll_get {ty:UScalarTy} {l:List (UScalar ty)} {B:Nat} (hl:u15 l B)
    (j:Nat) (hj:j < l.length):(l[j]).val  ≤  B := hl j hj
theorem LeAll_get! {ty:UScalarTy} {l:List (UScalar ty)} {B:Nat} (hl:u15 l B)
    (j:Nat) (hj:j < l.length):(l[j]!).val  ≤  B := by
  rw [List.getElem!_eq_getElem?_getD, List.getElem?_eq_getElem hj];exact hl j hj
theorem u16 {ty:UScalarTy} {l:List (UScalar ty)} {B B':Nat} (hl:u15 l B)
    (h:B  ≤  B'):u15 l B' := fun j hj => Nat.le_trans (hl j hj) h
theorem LeAll_replicate {ty:UScalarTy} (n:Nat) (x:UScalar ty) (B:Nat) (h:x.val  ≤  B) :
    u15 (List.replicate n x) B := by
  intro j hj;simp [List.getElem_replicate];exact h
theorem u17 {ty:UScalarTy} {l:List (UScalar ty)} {B:Nat} (hl:u15 l B)
    (i:Nat) (x:UScalar ty) (hx:x.val  ≤  B):u15 (l.set i x) B := by
  intro j hj
  rw [List.getElem_set]
  split
  · exact hx
  · exact hl j (by simpa using hj)
theorem u18 {ty:UScalarTy} {l:List (UScalar ty)} {B:Nat} (hl:u15 l B)
    (x:UScalar ty) (hx:x.val  ≤  B):u15 (l ++ [x]) B := by
  intro j hj
  rw [List.getElem_append]
  split
  · exact hl j (by assumption)
  · simp;exact hx
theorem u19 {ty:UScalarTy} {l:List (UScalar ty)} {t:Nat} (hl:u15 l t)
    (i:Nat) (x:UScalar ty) (hx:x.val  ≤  t + 1):u15 (l.set i x) (t + 1) :=
  u17 (u16 hl (Nat.le_succ t)) i x hx
@[local step]
theorem u20 (v:U) (i:R) (x:W) :
    slot.Z174 v i x ⦃ fun r => r.length = v.length ⦄ := by
  rw [slot.Z174];split <;> step*
theorem u21:0 < slot.Z45.val  ∧  slot.Z45.val  ≤  65536 := by
  simp [slot.Z45]
def u22 (nextl:Array Std.U16 512#usize):Prop := ∀ j, j < 512  →  j < (nextl.val[j]!).val
theorem u23 {n:Nat} (h:n + n  ≤  Std.Usize.max):n + 2147483648  ≤  Std.Usize.max := by
  have:Std.Usize.max = 2 ^ System.Platform.numBits - 1 := by
    simp [Std.Usize.max, Std.Usize.numBits]
  rcases System.Platform.numBits_eq with h32 | h64
  · rw [this, h32] at h ⊢;omega
  · rw [this, h64] at h ⊢;omega
theorem u24:slot.Z57.val = 8192 := by simp [slot.Z57]
theorem dp_WN_val:slot.Z62.val = 32768 := by simp [slot.Z62]
theorem u25:slot.Z45.val = 16384 := by simp [slot.Z45]
theorem u26:slot.Z47.val = 65536 := by simp [slot.Z47]
theorem u27:1  ≤  slot.Z44.val  ∧  slot.Z44.val  ≤  32 := by simp [slot.Z44]
theorem dp_H4B_bound:1  ≤  slot.Z46.val  ∧  slot.Z46.val  ≤  32 := by simp [slot.Z46]
theorem u28:1  ≤  slot.Z46.val  ∧  slot.Z46.val  ≤  64 := by simp [slot.Z46]
theorem u29:slot.Z50.val  ≤  8 := by simp [slot.Z50]
theorem u30:slot.Z61.val  ≤  1048576 := by simp [slot.Z61]
theorem u31:slot.Z59.val  ≤  1048576 := by simp [slot.Z59]
theorem u33:slot.Z4.val  ≤  1048576 := by simp [slot.Z4]
theorem u34:u15 slot.Z41.val 16 := by
  unfold slot.Z41 u15;simp only [Array.make];decide
theorem u35 (c:W):c.val >>> 9 < 8388608 := by
  rw [Nat.shiftRight_eq_div_pow]
  have:c.val < 2 ^ 32 := by (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  omega
theorem u36 (n:R) (h:n.val < (core.num.Usize.wrapping_add n n).val) :
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
theorem u37 (x:Nat):x ||| 1  ≤  x + 1 := by
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
theorem u38 {ty:UScalarTy} (n:R) (x:UScalar ty) (B:Nat) (h:x.val  ≤  B) :
    u15 (Array.repeat n x).val B := by
  rw [Array.repeat_val];exact LeAll_replicate _ _ _ h
theorem u39 {ty:UScalarTy} {n:R} {a r:Array (UScalar ty) n} {i:R}
    {v:UScalar ty} {B:Nat} (hr:r = a.set i v) (ha:u15 a.val B) (hv:v.val  ≤  B):u15 r.val B := by
  rw [hr, Array.set_val_eq];exact u17 ha _ _ hv
theorem u40!_set {ty:UScalarTy} (l:List (UScalar ty)) (i j:Nat) (x:UScalar ty)
    (hi:i < l.length):(l.set i x)[j]! = if i = j then x else l[j]! := by
  simp only [List.getElem!_eq_getElem?_getD, List.getElem?_set]
  split
  · simp [*]
  · rfl
@[local step] theorem u41 (s:I) (i:R) (h:i.val + 8  ≤  Std.Usize.max) :
    slot.Z94 s i ⦃ Y112P0! ⦄ := by
  rw [slot.Z94]
  step*
@[local step]
theorem u42 (s:I) (a b cap k:R) (run:W)
    (ha:a.val + cap.val + 8  ≤  Std.Usize.max) (hb:b.val + cap.val + 8  ≤  Std.Usize.max) (hk:k.val  ≤  cap.val) :
    slot.Z96_loop0 s a b cap k run ⦃ fun r => r.1.val  ≤  cap.val ⦄ := by
  rw [slot.Z96_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (k', run') => cap.val + 9 - k'.val + run'.val)
    (inv := fun (k', _) => k'.val  ≤  cap.val)
  · rintro ⟨k', run'⟩ hk'
    simp only [slot.Z96_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals try (have := u14 x)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · exact hk
@[local step]
theorem u43 (s:I) (a b cap k:R) (run:W)
    (ha:a.val + cap.val + 8  ≤  Std.Usize.max) (hb:b.val + cap.val + 8  ≤  Std.Usize.max) (hk:k.val  ≤  cap.val) :
    slot.Z96_loop1 s a b cap k run ⦃ fun r => r.val  ≤  cap.val ⦄ := by
  rw [slot.Z96_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (k', run') => cap.val + 1 - k'.val + run'.val)
    (inv := fun (k', _) => k'.val  ≤  cap.val)
  · rintro ⟨k', run'⟩ hk'
    simp only [slot.Z96_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · exact hk
@[local step] theorem u44 (s:I) (a b cap:R)
    (ha:a.val + cap.val + 8  ≤  Std.Usize.max) (hb:b.val + cap.val + 8  ≤  Std.Usize.max) :
    slot.Z96 s a b cap ⦃ fun r => r.val  ≤  cap.val ⦄ := by
  rw [slot.Z96]
  step*
@[local step] theorem u45 (x:W):slot.Z150 x ⦃ fun r => r.val < 16384 ⦄ := by
  have := u27
  have := u25
  rw [slot.Z150]
  step*
@[local step] theorem u46 (x:W):slot.Z151 x ⦃ fun r => r.val < 65536 ⦄ := by
  have := dp_H4B_bound
  have := u26
  rw [slot.Z151]
  step*
@[local step] theorem u47 (x:Std.U64):slot.Z152 x ⦃ fun r => r.val < 65536 ⦄ := by
  have := u28
  have := u26
  rw [slot.Z152]
  step*
@[local step] theorem u48 (s:I) (c i:R) (b8:Std.U64) (cap best:R)
    (hc:c.val  ≤  i.val) (hcap:9  ≤  cap.val) (hic:i.val + cap.val  ≤  s.length)
    (hs8:s.length + 8  ≤  Std.Usize.max) :
    slot.Z169 s c i b8 cap best ⦃ fun r => r.val  ≤  cap.val  ∧  (r.val = 0  ∨  best.val < r.val) ⦄ := by
  rw [slot.Z169]
  step*
  repeat' (split <;> step*)
  all_goals try (have := u14 x)
  all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
@[local step] theorem u49 (prev) (start depth:R) (same:Bool) :
    slot.Z175 prev start depth same ⦃ fun r => r.1.val  ≤  start.val ⦄ := by
  have hwn := dp_WN_val
  rw [slot.Z175]
  step*
  repeat' (split <;> step*)
  all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
@[local step] theorem u50 (head3:C 16384#usize) (head4:C 65536#usize)
    (prev4) (head7:C 65536#usize) (prev7) (q:R) (b8:Std.U64) (sh7:W) (B:Nat)
    (h3:u15 head3.val B) (h4:u15 head4.val B) (h7:u15 head7.val B) (hq:q.val  ≤  B) :
    slot.Z160 head3 head4 prev4 head7 prev7 q b8 sh7 ⦃ fun r =>
      r.1.1.val  ≤  B  ∧  r.1.2.1.val  ≤  B  ∧  r.1.2.2.val  ≤  B  ∧ 
      u15 r.2.1.val B  ∧  u15 r.2.2.1.val B  ∧  u15 r.2.2.2.2.1.val B ⦄ := by
  have hwn := dp_WN_val
  have H3 := h3
  have H4 := h4
  have H7 := h7
  rw [slot.Z160]
  step*
  have e3 := LeAll_get H3 h3.val (by scalar_tac)
  have e4 := LeAll_get H4 h4.val (by scalar_tac)
  have e7 := LeAll_get H7 h7.val (by scalar_tac)
  refine ⟨by scalar_tac, by scalar_tac, by scalar_tac, ?_, ?_, ?_⟩
  · exact u39 head31_post H3 (by scalar_tac)
  · exact u39 head41_post H4 (by scalar_tac)
  · exact u39 head71_post H7 (by scalar_tac)
@[local step]
theorem u51 (input:I) (head3:C 16384#usize)
    (head4:C 65536#usize) (prev4) (head7:C 65536#usize) (prev7)
    (e:R) (sh7:W) (q:R) (B:Nat)
    (h3:u15 head3.val B) (h4:u15 head4.val B) (h7:u15 head7.val B)
    (he:e.val  ≤  B + 1) (he8:e.val + 8  ≤  Std.Usize.max) :
    slot.Z161_loop input head3 head4 prev4 head7 prev7 e sh7 q ⦃ fun r =>
      u15 r.1.val B  ∧  u15 r.2.1.val B  ∧  u15 r.2.2.2.1.val B ⦄ := by
  rw [slot.Z161_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, _, q') => e.val - q'.val)
    (inv := fun (h3', h4', _, h7', _, _) => u15 h3'.val B  ∧  u15 h4'.val B  ∧  u15 h7'.val B)
  · rintro ⟨h3', h4', p4', h7', p7', q'⟩ ⟨i3, i4, i7⟩
    simp only [slot.Z161_loop.body]
    split
    · step*
      all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
    · step*
  · exact ⟨h3, h4, h7⟩
@[local step] theorem u52 (input:I) (head3:C 16384#usize)
    (head4:C 65536#usize) (prev4) (head7:C 65536#usize) (prev7)
    (f e:R) (sh7:W) (B:Nat)
    (h3:u15 head3.val B) (h4:u15 head4.val B) (h7:u15 head7.val B)
    (he:e.val  ≤  B + 1) (he8:e.val + 8  ≤  Std.Usize.max) :
    slot.Z161 input head3 head4 prev4 head7 prev7 f e sh7 ⦃ fun r =>
      u15 r.1.val B  ∧  u15 r.2.1.val B  ∧  u15 r.2.2.2.1.val B ⦄ := by
  rw [slot.Z161]
  exact u51 input head3 head4 prev4 head7 prev7 e sh7 f B h3 h4 h7 he he8
theorem u53 {nextl:Array Std.U16 512#usize} (hnx:u22 nextl) (j:Nat)
    (hj:j < nextl.val.length):j < (nextl.val[j]).val := by
  have hl:nextl.val.length = 512 := by simp
  have := hnx j (by omega)
  rwa [List.getElem!_eq_getElem?_getD, List.getElem?_eq_getElem hj, Option.getD_some] at this
@[local step] theorem u54 (pa) (slt:R) (cost choice:W) :
    slot.Z172 pa slt cost choice ⦃ Y112P0! ⦄ := by
  have := u24
  rw [slot.Z172]
  step*
  repeat' (split <;> step*)
@[local step]
theorem u55 (pa lc) (nextl:Array Std.U16 512#usize) (i hi:R) (base dpack:W)
    (l:R) (hnx:u22 nextl) (hhi:hi.val  ≤  512) (hih:i.val + hi.val  ≤  Std.Usize.max) :
    slot.Z173_loop pa lc nextl i hi base dpack l ⦃ Y112P0! ⦄ := by
  have := u24
  rw [slot.Z173_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, l') => hi.val - l'.val)
    (inv := fun _ => True)
  · rintro ⟨pa', l'⟩ _
    simp only [slot.Z173_loop.body]
    split
    · step*
      repeat' (split <;> step*)
      all_goals
        have hx := u53 hnx i1.val (by scalar_tac)
        scalar_tac
    · step*
  · trivial
@[local step] theorem u56 (pa lc) (nextl:Array Std.U16 512#usize) (i lo hi:R)
    (base dpack:W) (hnx:u22 nextl) (hhi:hi.val < 512) (hih:i.val + hi.val  ≤  Std.Usize.max) :
    slot.Z173 pa lc nextl i lo hi base dpack ⦃ Y112P0! ⦄ := by
  have := u24
  rw [slot.Z173]
  step*
  repeat' (split <;> step*)
@[local step]
theorem u57 (input:I) (pa lc) (i s len dd t bt:R) (bv:W)
    (hi:i.val < input.length) (hlen:len.val < 512) (hdd:dd.val < 8388608)
    (hN:input.length + 2147483648  ≤  Std.Usize.max)
    (ht:t.val  ≤  i.val) (hbt:bt.val  ≤  t.val) (ht258:t.val = 0  ∨  len.val + t.val  ≤  258) :
    slot.Z92_loop input pa lc i s len dd t bt bv ⦃ fun r =>
      r.1.val  ≤  i.val  ∧  (r.1.val = 0  ∨  len.val + r.1.val  ≤  258) ⦄ := by
  have := u24
  rw [slot.Z92_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (t', _, _) => slot.Z59.val - t'.val)
    (inv := fun (t', bt', _) => t'.val  ≤  i.val  ∧  bt'.val  ≤  t'.val  ∧  (t'.val = 0  ∨  len.val + t'.val  ≤  258))
  · rintro ⟨t', bt', bv'⟩ ⟨h1, h2, h3⟩
    simp only [slot.Z92_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · exact ⟨ht, hbt, ht258⟩
@[local step] theorem u58 (input:I) (pa lc) (i s len dd:R)
    (hi:i.val < input.length) (hlen:len.val < 512) (hdd:dd.val < 8388608)
    (hN:input.length + 2147483648  ≤  Std.Usize.max) :
    slot.Z92 input pa lc i s len dd ⦃ fun r => r.1.val  ≤  i.val  ∧  (r.1.val = 0  ∨  len.val + r.1.val  ≤  258) ⦄ := by
  rw [slot.Z92]
  step*
@[local step] theorem u59 (dtab) (d:R):slot.Z142 dtab d ⦃ Y112P0! ⦄ := by
  rw [slot.Z142]
  step*
  repeat' (split <;> step*)
  all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
@[local step]
theorem u60 (input:I) (pa cands nc lc) (nextl:Array Std.U16 512#usize)
    (dtab dcc) (i s:R) (base:W) (pcd lo k:R)
    (hnx:u22 nextl) (hi:i.val < input.length) (hN:input.length + 2147483648  ≤  Std.Usize.max) :
    slot.Z171_loop input pa cands nc lc nextl dtab dcc i s base pcd lo k ⦃ Y112P0! ⦄ := by
  have := u24
  have := u33
  rw [slot.Z171_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, k') => 16 - k'.val)
    (inv := fun _ => True)
  · rintro ⟨pa', lo', k'⟩ _
    simp only [slot.Z171_loop.body]
    step*
    have := u35 c
    apply WP.spec_bind (Pₘ := fun _ => True)
    · repeat' (split <;> step*)
      all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
    · intro pa2 _
      step*
  · trivial
@[local step] theorem u61 (input:I) (pa cands nc lc) (nextl:Array Std.U16 512#usize)
    (dtab dcc) (i s:R) (base:W) (pcd:R)
    (hnx:u22 nextl) (hi:i.val < input.length) (hN:input.length + 2147483648  ≤  Std.Usize.max) :
    slot.Z171 input pa cands nc lc nextl dtab dcc i s base pcd ⦃ Y112P0! ⦄ := by
  rw [slot.Z171]
  step*
@[local step]
theorem u62 (cands) (cd nc:R) :
    slot.Z141_loop cands cd nc ⦃ Y112P0! ⦄ := by
  rw [slot.Z141_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun nc' => nc'.val)
    (inv := fun _ => True)
  · rintro nc' _
    simp only [slot.Z141_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · trivial
@[local step] theorem u63 (cands) (nc0 cd:R):slot.Z141 cands nc0 cd ⦃ Y112P0! ⦄ := by
  rw [slot.Z141]
  step*
@[local step] theorem u65 (anchor i cl best:R):slot.Z166 anchor i cl best ⦃ Y112P0! ⦄ := by
  rw [slot.Z166]
  repeat' (split <;> step*)
@[local step]
theorem u66 (input:I) (i d s max t:R)
    (hi:i.val < input.length) (hd:d.val < 8388608) (hN:input.length + 2147483648  ≤  Std.Usize.max)
    (hsi:s.val  ≤  i.val) (ht:t.val  ≤  i.val - s.val) :
    slot.Z145_loop input i d s max t ⦃ fun r => r.val  ≤  i.val - s.val ⦄ := by
  rw [slot.Z145_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun t' => max.val - t'.val)
    (inv := fun t' => t'.val  ≤  i.val - s.val)
  · rintro t' h1
    simp only [slot.Z145_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · exact ht
@[local step] theorem u67 (input:I) (i d s max:R)
    (hi:i.val < input.length) (hd:d.val < 8388608) (hN:input.length + 2147483648  ≤  Std.Usize.max)
    (hsi:s.val  ≤  i.val) :
    slot.Z145 input i d s max ⦃ fun r => r.val  ≤  i.val - s.val ⦄ := by
  rw [slot.Z145]
  step*
@[local step]
theorem u68 (pa) (s u:R) (hs:s.val + 259  ≤  Std.Usize.max) :
    slot.Z167_loop pa s u ⦃ Y112P0! ⦄ := by
  have := u24
  rw [slot.Z167_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, u') => 259 - u'.val)
    (inv := fun _ => True)
  · rintro ⟨pa', u'⟩ _
    simp only [slot.Z167_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · trivial
@[local step] theorem u69 (pa) (s:R) (hs:s.val + 259  ≤  Std.Usize.max) :
    slot.Z167 pa s ⦃ Y112P0! ⦄ := by
  have := u24
  rw [slot.Z167]
  step*
@[local step]
theorem u70 (plan tb lim k):slot.Z170_loop plan tb lim k ⦃ Y112P0! ⦄ := by
  have := u24
  rw [slot.Z170_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, k') => k'.val)
    (inv := fun _ => True)
  · rintro ⟨plan', k'⟩ _
    simp only [slot.Z170_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · trivial
@[local step] theorem u71 (plan tb nt lim):slot.Z170 plan tb nt lim ⦃ Y112P0! ⦄ := by
  rw [slot.Z170]
  step*
@[local step]
theorem u72 (input:I) (pa) (s:R) (lsym dtab lf df tb) (j nt guard:R)
    (hs:s.val  ≤  j.val) (hg:nt.val + guard.val  ≤  Std.Usize.max) :
    slot.Z93_loop input pa s lsym dtab lf df tb j nt guard ⦃ Y112P0! ⦄ := by
  have := u24
  rw [slot.Z93_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, _, g') => g'.val)
    (inv := fun (_, _, _, j', nt', g') => s.val  ≤  j'.val  ∧  nt'.val + g'.val  ≤  Std.Usize.max)
  · rintro ⟨lf', df', tb', j', nt', g'⟩ ⟨h1, h2⟩
    simp only [slot.Z93_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · exact ⟨hs, hg⟩
@[local step] theorem u73 (input:I) (pa plan) (s e:R) (lsym dtab lf df tb)
    (hse:s.val  ≤  e.val) (he:e.val < Std.Usize.max) :
    slot.Z93 input pa plan s e lsym dtab lf df tb ⦃ Y112P0! ⦄ := by
  rw [slot.Z93]
  step*
@[local step]
theorem u74 (lf s):slot.Z149_loop0 lf s ⦃ Y112P0! ⦄ := by
  rw [slot.Z149_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, s') => 286 - s'.val)
    (inv := fun _ => True)
  · rintro ⟨lf', s'⟩ _
    simp only [slot.Z149_loop0.body]
    step*
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · trivial
@[local step]
theorem u75 (df k):slot.Z149_loop1 df k ⦃ Y112P0! ⦄ := by
  rw [slot.Z149_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, k') => 30 - k'.val)
    (inv := fun _ => True)
  · rintro ⟨df', k'⟩ _
    simp only [slot.Z149_loop1.body]
    step*
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · trivial
@[local step] theorem u76 (lf df):slot.Z149 lf df ⦃ Y112P0! ⦄ := by
  rw [slot.Z149]
  step*
@[local step] theorem u77 (x:W):slot.Z163 x ⦃ Y112P0! ⦄ := by
  rw [slot.Z163]
  split
  · step*
  · step*
    all_goals try (have := u13 x)
    repeat' (split <;> step*)
    all_goals try (have := LeAll_get u34 i3.val (by (subst_vars;scalar_tac (simpAllMaxSteps := 0))))
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
@[local step]
theorem u78 (freq total s):slot.Z97_loop0 freq total s ⦃ Y112P0! ⦄ := by
  rw [slot.Z97_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, s') => freq.length - s'.val)
    (inv := fun _ => True)
  · rintro ⟨total', s'⟩ _
    simp only [slot.Z97_loop0.body]
    step*
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · trivial
@[local step]
theorem u79 (freq out lt t):slot.Z97_loop1 freq out lt t ⦃ Y112P0! ⦄ := by
  rw [slot.Z97_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, t') => freq.length - t'.val)
    (inv := fun _ => True)
  · rintro ⟨out', t'⟩ _
    simp only [slot.Z97_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · trivial
@[local step] theorem u80 (freq out):slot.Z97 freq out ⦃ Y112P0! ⦄ := by
  rw [slot.Z97]
  step*
@[local step]
theorem u81 (freq:U) (sym) (f:W) (j:R) (hf:0 < freq.length) :
    slot.Z156_loop freq sym f j ⦃ Y112P0! ⦄ := by
  rw [slot.Z156_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, j') => j'.val)
    (inv := fun _ => True)
  · rintro ⟨sym', j'⟩ _
    simp only [slot.Z156_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · trivial
@[local step] theorem u82 (freq:U) (sym) (ns:R) (f:W) (hf:0 < freq.length) :
    slot.Z156 freq sym ns f ⦃ Y112P0! ⦄ := by
  rw [slot.Z156]
  step*
@[local step]
theorem u83 (freq:U) (m sym) (ns i:R)
    (hf:0 < freq.length) (hns:ns.val  ≤  i.val) (hi:i.val  ≤  320) :
    slot.Z157_loop freq m sym ns i ⦃ fun r => r.1.val  ≤  320 ⦄ := by
  rw [slot.Z157_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, i') => 320 - i'.val)
    (inv := fun (_, ns', i') => ns'.val  ≤  i'.val  ∧  i'.val  ≤  320)
  · rintro ⟨sym', ns', i'⟩ ⟨h1, h2⟩
    simp only [slot.Z157_loop.body]
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
@[local step] theorem u84 (freq:U) (m sym) (hf:0 < freq.length) :
    slot.Z157 freq m sym ⦃ fun r => r.1.val  ≤  320 ⦄ := by
  rw [slot.Z157]
  step*
@[local step] theorem u85 (w) (a b ns nx:R) (hab:a.val + b.val < Std.Usize.max) :
    slot.Z158 w a b ns nx ⦃ fun r => r.2.1.val + r.2.2.val = a.val + b.val + 1 ⦄ := by
  rw [slot.Z158]
  step*
  repeat' (split <;> step*)
  all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
@[local step]
theorem u86 (w par) (ns a b nx:R) (hns:ns.val  ≤  320) (hnx:nx.val  ≤  639)
    (hab:a.val + b.val + ns.val = 2 * nx.val) :
    slot.Z153_loop w par ns a b nx ⦃ Y112P0! ⦄ := by
  rw [slot.Z153_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, nx') => 639 - nx'.val)
    (inv := fun (_, _, a', b', nx') => nx'.val  ≤  639  ∧  a'.val + b'.val + ns.val = 2 * nx'.val)
  · rintro ⟨w', par', a', b', nx'⟩ ⟨h1, h2⟩
    simp only [slot.Z153_loop.body]
    step*
    rcases y with ⟨i7, a1, b1⟩
    step*
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · exact ⟨hnx, hab⟩
@[local step] theorem u87 (w par) (ns:R) (hns:ns.val  ≤  320) :
    slot.Z153 w par ns ⦃ Y112P0! ⦄ := by
  rw [slot.Z153]
  step*
@[local step]
theorem u88 (par depth ns mx q):slot.Z155_loop par depth ns mx q ⦃ Y112P0! ⦄ := by
  rw [slot.Z155_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, q') => q'.val)
    (inv := fun _ => True)
  · rintro ⟨depth', mx', q'⟩ _
    simp only [slot.Z155_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · trivial
@[local step] theorem u89 (par depth nx ns):slot.Z155 par depth nx ns ⦃ Y112P0! ⦄ := by
  rw [slot.Z155]
  step*
  repeat' (split <;> step*)
@[local step]
theorem u90 (freq:U) (sym ns w k) (hf:0 < freq.length) :
    slot.Z154_loop0 freq sym ns w k ⦃ Y112P0! ⦄ := by
  rw [slot.Z154_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, k') => ns.val - k'.val)
    (inv := fun _ => True)
  · rintro ⟨w', k'⟩ _
    simp only [slot.Z154_loop0.body]
    step*
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · trivial
@[local step]
theorem u91 (m out) (mx:W) (t:R) (hmx:mx.val  ≤  15) :
    slot.Z154_loop1 m out mx t ⦃ Y112P0! ⦄ := by
  rw [slot.Z154_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, t') => m.val - t'.val)
    (inv := fun _ => True)
  · rintro ⟨out', t'⟩ _
    simp only [slot.Z154_loop1.body]
    step*
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · trivial
@[local step]
theorem u92 (out sym ns depth r):slot.Z154_loop2 out sym ns depth r ⦃ Y112P0! ⦄ := by
  rw [slot.Z154_loop2]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, r') => ns.val - r'.val)
    (inv := fun _ => True)
  · rintro ⟨out', r'⟩ _
    simp only [slot.Z154_loop2.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · trivial
@[local step] theorem u93 (freq:U) (m out) (hf:0 < freq.length) :
    slot.Z154 freq m out ⦃ Y112P0! ⦄ := by
  rw [slot.Z154]
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
theorem u94 (litc llc b):slot.Z164_loop0 litc llc b ⦃ Y112P0! ⦄ := by
  rw [slot.Z164_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, b') => 256 - b'.val)
    (inv := fun _ => True)
  · rintro ⟨litc', b'⟩ _
    simp only [slot.Z164_loop0.body]
    step*
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · trivial
@[local step]
theorem u95 (lsym:G 512#usize) (lc) (llc:C 286#usize) (l:R)
    (hls:u15 lsym.val 28):slot.Z164_loop1 lsym lc llc l ⦃ Y112P0! ⦄ := by
  rw [slot.Z164_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, l') => 259 - l'.val)
    (inv := fun _ => True)
  · rintro ⟨lc', l'⟩ _
    simp only [slot.Z164_loop1.body]
    step*
    all_goals try (have := LeAll_get hls l'.val (by (subst_vars;scalar_tac (simpAllMaxSteps := 0))))
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · trivial
@[local step]
theorem u96 (dcc dc k):slot.Z164_loop2 dcc dc k ⦃ Y112P0! ⦄ := by
  rw [slot.Z164_loop2]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, k') => 30 - k'.val)
    (inv := fun _ => True)
  · rintro ⟨dcc', k'⟩ _
    simp only [slot.Z164_loop2.body]
    step*
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · trivial
@[local step] theorem u97 (lf df) (lsym:G 512#usize) (litc lc dcc huff)
    (hls:u15 lsym.val 28):slot.Z164 lf df lsym litc lc dcc huff ⦃ Y112P0! ⦄ := by
  rw [slot.Z164]
  step*
  apply WP.spec_bind (Pₘ := fun _ => True)
  · split
    · step*
    · step*
  · intro x _
    rcases x with ⟨llc1, dc1⟩
    step*
@[local step]
theorem u98 (lf tot z):slot.Z176_loop lf tot z ⦃ Y112P0! ⦄ := by
  rw [slot.Z176_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, z') => 286 - z'.val)
    (inv := fun _ => True)
  · rintro ⟨tot', z'⟩ _
    simp only [slot.Z176_loop.body]
    step*
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · trivial
@[local step] theorem u99 (lf df) (lsym:G 512#usize) (litc lc dcc huff)
    (hls:u15 lsym.val 28):slot.Z176 lf df lsym litc lc dcc huff ⦃ Y112P0! ⦄ := by
  rw [slot.Z176]
  step*
  repeat' (split <;> step*)
@[local step]
theorem u100 (input:I) (lf) (n step i:R)
    (hn:n.val = input.length) (hstep:1  ≤  step.val) (hns:n.val + step.val  ≤  Std.Usize.max) :
    slot.Z159_loop0 input lf n step i ⦃ Y112P0! ⦄ := by
  rw [slot.Z159_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, i') => n.val - i'.val)
    (inv := fun _ => True)
  · rintro ⟨lf', i'⟩ _
    simp only [slot.Z159_loop0.body]
    step*
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · trivial
@[local step]
theorem u101 (lf s):slot.Z159_loop1 lf s ⦃ Y112P0! ⦄ := by
  rw [slot.Z159_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, s') => 286 - s'.val)
    (inv := fun _ => True)
  · rintro ⟨lf', s'⟩ _
    simp only [slot.Z159_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · trivial
@[local step]
theorem u102 (df k):slot.Z159_loop2 df k ⦃ Y112P0! ⦄ := by
  rw [slot.Z159_loop2]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, k') => 30 - k'.val)
    (inv := fun _ => True)
  · rintro ⟨df', k'⟩ _
    simp only [slot.Z159_loop2.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · trivial
@[local step] theorem u103 (input:I) (lf df)
    (hN:input.length + input.length  ≤  Std.Usize.max) :
    slot.Z159 input lf df ⦃ Y112P0! ⦄ := by
  rw [slot.Z159]
  step*
  all_goals
    have h1 := u37 (input.length / 8192)
    have h2:1  ≤  input.length / 8192 ||| 1 := Nat.right_le_or
    scalar_tac
@[local step]
theorem u104 (lsym:G 512#usize) (code l:R)
    (hc:code.val  ≤  28) (hls:u15 lsym.val 28) :
    slot.Z146_loop0 lsym code l ⦃ fun r => u15 r.val 28 ⦄ := by
  rw [slot.Z146_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, l') => 259 - l'.val)
    (inv := fun (ls', c', _) => c'.val  ≤  28  ∧  u15 ls'.val 28)
  · rintro ⟨ls', c', l'⟩ ⟨h1, h2⟩
    simp only [slot.Z146_loop0.body]
    split
    · apply WP.spec_bind (Pₘ := fun (x:R) => x.val  ≤  28)
      · repeat' (split <;> step*)
        all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
      · intro code1 hc1
        step*
        and_intros
        all_goals first
          | exact u39 a_post h2 (by (subst_vars;scalar_tac (simpAllMaxSteps := 0)))
          | (subst_vars;scalar_tac (simpAllMaxSteps := 0))
    · step*
  · exact ⟨hc, hls⟩
@[local step]
theorem u105 (dtab c j):slot.Z146_loop1 dtab c j ⦃ Y112P0! ⦄ := by
  rw [slot.Z146_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, j') => 256 - j'.val)
    (inv := fun _ => True)
  · rintro ⟨dtab', c', j'⟩ _
    simp only [slot.Z146_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · trivial
@[local step]
theorem u106 (c2 d):slot.Z146_loop2_loop0 c2 d ⦃ Y112P0! ⦄ := by
  rw [slot.Z146_loop2_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun c2' => 29 - c2'.val)
    (inv := fun _ => True)
  · rintro c2' _
    simp only [slot.Z146_loop2_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · trivial
@[local step]
theorem u107 (dtab c2 k):slot.Z146_loop2 dtab c2 k ⦃ Y112P0! ⦄ := by
  rw [slot.Z146_loop2]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, k') => 256 - k'.val)
    (inv := fun _ => True)
  · rintro ⟨dtab', c2', k'⟩ _
    simp only [slot.Z146_loop2.body]
    step*
    all_goals (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  · trivial
@[local step] theorem u108 (lsym:G 512#usize) (dtab) (hls:u15 lsym.val 28) :
    slot.Z146 lsym dtab ⦃ fun r => u15 r.1.val 28 ⦄ := by
  rw [slot.Z146]
  step*
theorem u109 (x y:R) :
    (core.num.Usize.saturating_sub x y).val = x.val - y.val := by
  have hx := x.hBounds
  show (BitVec.ofNat _ (max 0 (x.val - y.val))).toNat = x.val - y.val
  rw [BitVec.toNat_ofNat, Nat.zero_max]
  exact Nat.mod_eq_of_lt (lt_of_le_of_lt (Nat.sub_le _ _) hx)
theorem u110 {α:Type} {a b c:Prop} [Decidable a] [Decidable b] [Decidable c]
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
theorem u111 {α:Type} {c:Prop} [Decidable c] {A B:Result α} {P:α  →  Prop}
    (hA:c  →  A ⦃ P ⦄) (hB:¬c  →  B ⦃ P ⦄):(if c then A else B) ⦃ P ⦄ := by
  by_cases h:c
  · rw [if_pos h];exact hA h
  · rw [if_neg h];exact hB h
theorem u112 {α:Type} {a b:Prop} [Decidable a] [Decidable b]
    {X Y:Result α} {P:α  →  Prop} (hX:a  →  b  →  X ⦃ P ⦄) (hY:Y ⦃ P ⦄) :
    (if a then (if b then X else Y) else Y) ⦃ P ⦄ := by
  by_cases ha:a
  · rw [if_pos ha]
    by_cases hb:b
    · rw [if_pos hb];exact hX ha hb
    · rw [if_neg hb];exact hY
  · rw [if_neg ha];exact hY
@[local step]
theorem u113 (v x)  :
    slot.Z127 v x ⦃ Y112P2! ⦄ := Y127U1! slot.Z127
@[local step]
theorem u114 (s i)  :
    slot.Z104 s i ⦃ Y112P2! ⦄ := Y127U1! slot.Z104
@[local step]
theorem u115 (ring i)  :
    slot.Z106 ring i ⦃ Y112P2! ⦄ := Y127U1! slot.Z106
@[local step]
theorem u116 (a b)  :
    slot.Z120 a b ⦃ fun r => r.val  ≤  a.val  ∧  r.val  ≤  b.val ⦄ := Y127U1! slot.Z120
theorem u117 {α:Type} {x:α} {P:α  →  Prop} (h:P x):WP.spec (ok x) P :=
  (WP.spec_ok x).2 h
theorem u118 {α:Type} {c:Prop} {inst:Decidable c} {X Y:Result α} {P:α  →  Prop}
    (hX:c  →  WP.spec X P) (hY:¬c  →  WP.spec Y P):WP.spec (@ite _ c inst X Y) P := by
  by_cases h:c
  · rw [if_pos h];exact hX h
  · rw [if_neg h];exact hY h
theorem d1_ite_ok {α:Type} (c:Prop) [Decidable c] (a b:α) :
    (if c then (ok a:Result α) else ok b) = ok (if c then a else b) := by split <;> rfl
theorem u119 {α β:Type} {m:Result α} {Q:α  →  Prop} {k:α  →  Result β} {P:β  →  Prop}
    (hm:WP.spec m Q) (hk:∀ x, Q x  →  WP.spec (k x) P):WP.spec (Bind.bind m k) P :=
  WP.spec_bind hm hk
theorem u120 {α β:Type} {m:Result α} {Q:α  →  Prop} {k:α  →  Result β} {P:β  →  Prop}
    (hm:WP.spec m Q) (hk:∀ x, WP.spec (k x) P):WP.spec (Bind.bind m k) P :=
  WP.spec_bind hm (fun x _ => hk x)
theorem u121 {α:Type} {m:Result α} {Q:α  →  Prop} (h:WP.spec m Q):WP.spec m (fun _ => True) :=
  WP.spec_mono h (fun _ _ => trivial)
theorem u122 {ty:UScalarTy} {β:Type} {x y:UScalar ty} {k:UScalar ty  →  Result β} {P:β  →  Prop}
    (w:UScalar ty) (h:x.val + y.val  ≤  w.val) (hk:∀ z:UScalar ty, z.val = x.val + y.val  →  WP.spec (k z) P) :
    WP.spec (Bind.bind (HAdd.hAdd x y:Result (UScalar ty)) k) P :=
  WP.spec_bind (UScalar.add_spec (Nat.le_trans h (ScalarTac.UScalar.bounds w))) hk
theorem u123 {ty:UScalarTy} {x y:UScalar ty} (w:UScalar ty) (h:x.val + y.val  ≤  w.val) :
    WP.spec (HAdd.hAdd x y:Result (UScalar ty)) (fun _ => True) :=
  u121 (UScalar.add_spec (Nat.le_trans h (ScalarTac.UScalar.bounds w)))
theorem u124 {ty:UScalarTy} {β:Type} {x y:UScalar ty} {k:UScalar ty  →  Result β} {P:β  →  Prop}
    (h:y.val  ≤  x.val) (hk:∀ z:UScalar ty, z.val + y.val = x.val  →  WP.spec (k z) P) :
    WP.spec (Bind.bind (HSub.hSub x y:Result (UScalar ty)) k) P :=
  WP.spec_bind (UScalar.sub_spec h) (fun z hz => hk z ((congrArg (· + y.val) hz.1).trans (Nat.sub_add_cancel h)))
theorem u125 {ty:UScalarTy} {β:Type} {x y:UScalar ty} {k:UScalar ty  →  Result β} {P:β  →  Prop}
    (h:0 < y.val) (hk:∀ z:UScalar ty, z.val < y.val  →  WP.spec (k z) P) :
    WP.spec (Bind.bind (HMod.hMod x y:Result (UScalar ty)) k) P :=
  WP.spec_bind (UScalar.rem_spec x (Nat.pos_iff_ne_zero.mp h)) (fun z hz => hk z (hz ▸ Nat.mod_lt _ h))
theorem u126 {β:Type} {x y:R} {k:R  →  Result β} {P:β  →  Prop}
    (h:y.val ≠ 0) (hk:∀ z:R, WP.spec (k z) P) :
    WP.spec (Bind.bind (HDiv.hDiv x y:Result R) k) P :=
  WP.spec_bind (Usize.div_spec x h) (fun z _ => hk z)
theorem u127 {ty ty1:UScalarTy} {β:Type} {x:UScalar ty} {y:UScalar ty1} {k:UScalar ty  →  Result β}
    {P:β  →  Prop} (h:y.val < ty.numBits) (hk:∀ z:UScalar ty, WP.spec (k z) P) :
    WP.spec (Bind.bind (HShiftRight.hShiftRight x y:Result (UScalar ty)) k) P :=
  WP.spec_bind (UScalar.ShiftRight_spec x y h) (fun z _ => hk z)
theorem u128 {ty ty1:UScalarTy} {β:Type} {x:UScalar ty} {y:UScalar ty1} {k:UScalar ty  →  Result β}
    {P:β  →  Prop} (h:y.val < ty.numBits) (hk:∀ z:UScalar ty, WP.spec (k z) P) :
    WP.spec (Bind.bind (HShiftLeft.hShiftLeft x y:Result (UScalar ty)) k) P :=
  WP.spec_bind (UScalar.ShiftLeft_spec x y _ h rfl) (fun z _ => hk z)
theorem u129 {ty:UScalarTy} {ty1:IScalarTy} {β:Type} {x:UScalar ty} {y:IScalar ty1}
    {k:UScalar ty  →  Result β} {P:β  →  Prop} (h0:0  ≤  y.val) (h:y.val < ty.numBits)
    (hk:∀ z:UScalar ty, WP.spec (k z) P) :
    WP.spec (Bind.bind (HShiftRight.hShiftRight x y:Result (UScalar ty)) k) P :=
  WP.spec_bind (UScalar.ShiftRight_IScalar_spec x y h0 h) (fun z _ => hk z)
theorem u130 {α β:Type} {n:R} {a:Std.Array α n} {i:R} {k:α  →  Result β} {P:β  →  Prop}
    (h:i.val < n.val) (hk:∀ x, WP.spec (k x) P):WP.spec (Bind.bind (Array.index_usize a i) k) P :=
  WP.spec_bind (Array.index_usize_spec a i (Nat.lt_of_lt_of_eq h a.property.symm)) (fun x _ => hk x)
theorem u131 {α β:Type} {n:R} {a:Std.Array α n} {i:R} {v:α}
    {k:Std.Array α n  →  Result β} {P:β  →  Prop} (h:i.val < n.val) (hk:∀ x, WP.spec (k x) P) :
    WP.spec (Bind.bind (Array.update a i v) k) P :=
  WP.spec_bind (Array.update_spec a i v (Nat.lt_of_lt_of_eq h a.property.symm)) (fun x _ => hk x)
theorem u132 {α β:Type} {s:Slice α} {i:R} {k:α  →  Result β} {P:β  →  Prop}
    (h:i.val < (Slice.len s).val) (hk:∀ x, WP.spec (k x) P) :
    WP.spec (Bind.bind (Slice.index_usize s i) k) P :=
  WP.spec_bind (Slice.index_usize_spec s i h) (fun x _ => hk x)
theorem u133 (b:Std.U8):(UScalar.cast .Usize b).val < (288#usize).val := by
  rw [U8.cast_Usize_val_eq];exact Nat.lt_of_le_of_lt (U8.le_max b) (by decide)
theorem u134 (l:Std.U8) {n:Nat} (h:l.val < n + 1):(UScalar.cast .U32 l).val  ≤  n := by
  rw [U8.cast_U32_val_eq];exact Nat.le_of_lt_succ h
theorem u135 {n:Nat}:0 < n + 1 := Nat.zero_lt_succ n
theorem u136 {a b:Nat} (h:a + 1 = b):a < b := h ▸ Nat.lt_succ_self a
theorem u137 {e l l1:Nat} (h:l < e) (h1:l1 = l + 1):e - l1 < e - l :=
  h1 ▸ Nat.sub_succ_lt_self e l h
theorem u138 {e l d l1:Nat} (h:l < e) (hd:0 < d) (h1:l1 = l + d):e - l1 < e - l :=
  h1 ▸ Nat.sub_lt_sub_left h (Nat.lt_add_of_pos_right hd)
theorem u139 {a b c n:Nat} (h:b  ≤  c) (hc:c + a = n):a + b  ≤  n :=
  Nat.le_trans (Nat.add_le_add_left h a) (Nat.le_of_eq ((Nat.add_comm a c).trans hc))
@[local step]
theorem u140 (w a b ns nx) :
    slot.Z136 w a b ns nx ⦃ Y112P0! ⦄ := by
  simp only [slot.Z136, lift, bind_tc_ok]
  refine u118 (fun ha => ?_) (fun _ => u117 trivial)
  refine u118 (fun _ => ?_) (fun _ => ?_)
  · exact u122 ns (Nat.succ_le_of_lt ha) fun _ _ => u117 trivial
  · refine u125 u135 fun i hi => ?_
    refine u130 hi fun i1 => ?_
    refine u125 u135 fun i2 hi2 => ?_
    refine u130 hi2 fun i3 => ?_
    exact u118 (fun _ => u122 ns (Nat.succ_le_of_lt ha) fun _ _ => u117 trivial) (fun _ => u117 trivial)
@[local step]
theorem u141 (d) :
    slot.Z107 d ⦃ Y112P0! ⦄ := by
  rw [slot.Z107]
  exact u118 (fun _ => u117 trivial) (fun _ => u118 (fun _ => u117 trivial) (fun _ => u117 trivial))
@[local step]
theorem u142 (freq sym f j) :
    slot.Z115_loop0_loop0 freq sym f j ⦃ Y112P0! ⦄ := by
  rw [slot.Z115_loop0_loop0]
  apply Std.loop.spec_decr_nat (measure := fun x => x.2.val) (inv := fun _ => True)
  · rintro ⟨sym', j'⟩ _
    simp only [slot.Z115_loop0_loop0.body, lift, bind_tc_ok]
    refine u118 (fun hj => ?_) (fun _ => u117 trivial)
    refine u124 (Nat.succ_le_of_lt hj) fun i hi => ?_
    refine u125 u135 fun i1 hi1 => ?_
    refine u130 hi1 fun i2 => ?_
    refine u125 u135 fun i4 hi4 => ?_
    refine u130 hi4 fun i5 => ?_
    refine u118 (fun _ => ?_) (fun _ => u117 trivial)
    refine u125 u135 fun i6 hi6 => ?_
    refine u130 hi6 fun i7 => ?_
    refine u125 u135 fun i8 hi8 => ?_
    refine u131 hi8 fun a => ?_
    exact u117 ⟨trivial, u136 hi⟩
  · trivial
@[local step]
theorem u143 (freq m len sym ns i) :
    slot.Z115_loop0 freq m len sym ns i ⦃ Y112P0! ⦄ := by
  rw [slot.Z115_loop0]
  apply Std.loop.spec_decr_nat (measure := fun x => 288 - x.2.2.2.val) (inv := fun _ => True)
  · rintro ⟨len', sym', ns', i'⟩ _
    simp only [slot.Z115_loop0.body, lift, bind_tc_ok]
    refine u118 (fun _ => ?_) (fun _ => u117 trivial)
    refine u118 (fun hi => ?_) (fun _ => u117 trivial)
    refine u130 hi fun f => ?_
    refine u118 (fun _ => ?_) (fun _ => ?_)
    · refine u120 (u142 _ _ _ _) fun ⟨sym1, j⟩ => ?_
      refine u125 u135 fun i1 hi1 => ?_
      refine u131 hi1 fun a => ?_
      refine u131 hi fun a1 => ?_
      refine u122 288#usize (Nat.succ_le_of_lt hi) fun i3 hi3 => ?_
      exact u117 ⟨trivial, u137 hi hi3⟩
    · refine u131 hi fun a => ?_
      refine u122 288#usize (Nat.succ_le_of_lt hi) fun i1 hi1 => ?_
      exact u117 ⟨trivial, u137 hi hi1⟩
  · trivial
@[local step]
theorem u144 (freq sym ns w k) :
    slot.Z115_loop1 freq sym ns w k ⦃ Y112P0! ⦄ := by
  rw [slot.Z115_loop1]
  apply Std.loop.spec_decr_nat (measure := fun x => ns.val - x.2.val) (inv := fun _ => True)
  · rintro ⟨w', k'⟩ _
    simp only [slot.Z115_loop1.body, lift, bind_tc_ok]
    refine u118 (fun hk => ?_) (fun _ => u117 trivial)
    refine u125 u135 fun i hi => ?_
    refine u130 hi fun i1 => ?_
    refine u125 u135 fun i3 hi3 => ?_
    refine u130 hi3 fun i4 => ?_
    refine u125 u135 fun i5 hi5 => ?_
    refine u131 hi5 fun a => ?_
    refine u122 ns (Nat.succ_le_of_lt hk) fun k1 hk1 => ?_
    exact u117 ⟨trivial, u137 hk hk1⟩
  · trivial
@[local step]
theorem u145 (ns w par a b nx) :
    slot.Z115_loop2 ns w par a b nx ⦃ Y112P0! ⦄ := by
  rw [slot.Z115_loop2]
  apply Std.loop.spec_decr_nat (measure := fun x => 575 - x.2.2.2.2.val) (inv := fun _ => True)
  · rintro ⟨w', par', a', b', nx'⟩ _
    simp only [slot.Z115_loop2.body, lift, bind_tc_ok]
    refine u118 (fun hn => ?_) (fun _ => u117 trivial)
    refine u122 575#usize (Nat.succ_le_of_lt hn) fun i hi => ?_
    refine u126 (by decide) fun i1 => ?_
    refine u118 (fun _ => ?_) (fun _ => u117 trivial)
    refine u120 (u140 _ _ _ _ _) fun ⟨x, a1, b1⟩ => ?_
    refine u120 (u140 _ _ _ _ _) fun ⟨y, a2, b2⟩ => ?_
    refine u125 u135 fun i2 hi2 => ?_
    refine u130 hi2 fun i3 => ?_
    refine u125 u135 fun i4 hi4 => ?_
    refine u130 hi4 fun i5 => ?_
    refine u125 u135 fun i7 hi7 => ?_
    refine u131 hi7 fun a3 => ?_
    refine u131 hi2 fun par1 => ?_
    refine u131 hi4 fun a4 => ?_
    exact u117 ⟨trivial, u137 hn hi⟩
  · trivial
@[local step]
theorem u146 (par depth q) :
    slot.Z115_loop3 par depth q ⦃ Y112P0! ⦄ := by
  rw [slot.Z115_loop3]
  apply Std.loop.spec_decr_nat (measure := fun x => x.2.val) (inv := fun _ => True)
  · rintro ⟨depth', q'⟩ _
    simp only [slot.Z115_loop3.body, lift, bind_tc_ok]
    refine u118 (fun hq => ?_) (fun _ => u117 trivial)
    refine u124 (Nat.succ_le_of_lt hq) fun q1 hq1 => ?_
    refine u125 u135 fun i hi => ?_
    refine u130 hi fun i1 => ?_
    refine u125 u135 fun i3 hi3 => ?_
    refine u130 hi3 fun i4 => ?_
    refine u131 hi fun a => ?_
    exact u117 ⟨trivial, u136 hq1⟩
  · trivial
@[local step]
theorem u147 (len sym ns k depth mx kraft) :
    slot.Z115_loop4 len sym ns k depth mx kraft ⦃ Y112P0! ⦄ := by
  rw [slot.Z115_loop4]
  apply Std.loop.spec_decr_nat (measure := fun x => ns.val - x.2.1.val) (inv := fun _ => True)
  · rintro ⟨len', k', mx', kraft'⟩ _
    simp only [slot.Z115_loop4.body, d1_ite_ok, lift, bind_tc_ok]
    refine u118 (fun hk => ?_) (fun _ => u117 trivial)
    refine u125 u135 fun i hi => ?_
    refine u130 hi fun i1 => ?_
    refine u120 (u141 _) fun l => ?_
    refine u125 u135 fun i2 hi2 => ?_
    refine u127 (Nat.lt_trans hi2 (by decide)) fun i3 => ?_
    refine u125 u135 fun i4 hi4 => ?_
    refine u130 hi4 fun i5 => ?_
    refine u125 u135 fun i7 hi7 => ?_
    refine u131 hi7 fun a => ?_
    refine u122 ns (Nat.succ_le_of_lt hk) fun k1 hk1 => ?_
    exact u117 ⟨trivial, u137 hk hk1⟩
  · trivial
@[local step]
theorem u148 (len sym ns mx kraft r fuel) :
    slot.Z115_loop5 len sym ns mx kraft r fuel ⦃ Y112P0! ⦄ := by
  rw [slot.Z115_loop5]
  apply Std.loop.spec_decr_nat (measure := fun x => x.2.2.2.2.val) (inv := fun _ => True)
  · rintro ⟨len', mx', kraft', r', fuel'⟩ _
    simp only [slot.Z115_loop5.body, lift, bind_tc_ok]
    refine u118 (fun _ => ?_) (fun _ => u117 trivial)
    refine u118 (fun hr => ?_) (fun _ => u117 trivial)
    refine u118 (fun hf => ?_) (fun _ => u117 trivial)
    refine u124 (Nat.succ_le_of_lt hf) fun fuel1 hf1 => ?_
    refine u125 u135 fun i hi => ?_
    refine u130 hi fun i1 => ?_
    refine u125 u135 fun s2 hs2 => ?_
    refine u130 hs2 fun l => ?_
    refine u118 (fun hl => ?_) (fun _ => ?_)
    · have hc := u134 l (n := 14) hl
      refine u124 hc fun i4 hi4 => ?_
      refine u128 (Nat.lt_of_le_of_lt (Nat.le_of_add_right_le (Nat.le_of_eq hi4)) (by decide)) fun i5 => ?_
      refine u122 15#u32 (Nat.succ_le_succ hc) fun i7 _ => ?_
      refine u120 (Q := fun _ => True)
        (u118 (fun _ => u123 15#u32 (Nat.succ_le_succ hc)) (fun _ => u117 trivial)) fun mx1 => ?_
      refine u122 15#u8 (Nat.succ_le_of_lt hl) fun i8 _ => ?_
      refine u131 hs2 fun a => ?_
      exact u117 ⟨trivial, u136 hf1⟩
    · refine u122 ns (Nat.succ_le_of_lt hr) fun r1 _ => ?_
      exact u117 ⟨trivial, u136 hf1⟩
  · trivial
@[local step]
theorem u149 (freq m len) :
    slot.Z115 freq m len ⦃ Y112P0! ⦄ := by
  simp only [slot.Z115, lift, bind_tc_ok]
  refine u120 (u143 _ _ _ _ _ _) fun ⟨len1, sym1, ns⟩ => ?_
  refine u118 (fun _ => u117 trivial) (fun _ => ?_)
  refine u118 (fun _ => ?_) (fun _ => ?_)
  · refine u130 (by decide) fun i => ?_
    refine u125 u135 fun i2 hi2 => ?_
    exact u131 hi2 fun _ => u117 trivial
  · refine u120 (u144 _ _ _ _ _) fun w1 => ?_
    refine u120 (u145 _ _ _ _ _ _) fun ⟨par1, nx⟩ => ?_
    refine u120 (u146 _ _ _) fun depth1 => ?_
    refine u120 (u147 _ _ _ _ _ _ _) fun ⟨len2, mx, kraft⟩ => ?_
    exact u148 _ _ _ _ _ _ _
@[local step]
theorem u150 (f lt) :
    slot.Z110 f lt ⦃ Y112P0! ⦄ := by
  rw [slot.Z110]
  refine u120 (Q := fun _ => True)
    (u118 (fun _ => u117 trivial) (fun _ => u120 (u77 _) fun _ => u117 trivial)) fun e => ?_
  exact u118 (fun _ => u117 trivial) (fun _ => u118 (fun _ => u117 trivial) (fun _ => u117 trivial))
@[local step]
theorem u151 (h e ck) :
    slot.Z121 h e ck ⦃ Y112P0! ⦄ := by
  simp only [slot.Z121, d1_ite_ok, lift, bind_tc_ok]
  refine u118 (fun _ => u117 trivial) (fun _ => ?_)
  refine u118 (fun _ => u117 trivial) (fun _ => ?_)
  refine u118 (fun _ => u121 (U32.div_spec _ (by decide))) (fun _ => ?_)
  refine u118 (fun hgt => ?_) (fun hle => ?_)
  · exact u124 (Nat.le_of_lt hgt) fun _ _ => u117 trivial
  · exact u124 (Nat.le_of_not_lt hle) fun _ _ => u117 trivial
@[local step]
theorem u152 (freq m total i) :
    slot.Z135_loop0 freq m total i ⦃ Y112P0! ⦄ := by
  rw [slot.Z135_loop0]
  apply Std.loop.spec_decr_nat (measure := fun x => 288 - x.2.val) (inv := fun _ => True)
  · rintro ⟨total', i'⟩ _
    simp only [slot.Z135_loop0.body, lift, bind_tc_ok]
    refine u118 (fun _ => ?_) (fun _ => u117 trivial)
    refine u118 (fun hi => ?_) (fun _ => u117 trivial)
    refine u130 hi fun i1 => ?_
    refine u122 288#usize (Nat.succ_le_of_lt hi) fun i2 hi2 => ?_
    exact u117 ⟨trivial, u137 hi hi2⟩
  · trivial
@[local step]
theorem u153 (freq m hl unseen ck out i lt) :
    slot.Z135_loop1 freq m hl unseen ck out i lt ⦃ Y112P0! ⦄ := by
  rw [slot.Z135_loop1]
  apply Std.loop.spec_decr_nat (measure := fun x => 288 - x.2.val) (inv := fun _ => True)
  · rintro ⟨out', i'⟩ _
    simp only [slot.Z135_loop1.body, d1_ite_ok, lift, bind_tc_ok]
    refine u118 (fun _ => ?_) (fun _ => u117 trivial)
    refine u118 (fun hi => ?_) (fun _ => u117 trivial)
    refine u130 hi fun i1 => ?_
    refine u130 hi fun i2 => ?_
    refine u120 (u150 _ _) fun e => ?_
    refine u120 (u151 _ _ _) fun i4 => ?_
    refine u131 hi fun a => ?_
    refine u122 288#usize (Nat.succ_le_of_lt hi) fun i5 hi5 => ?_
    exact u117 ⟨trivial, u137 hi hi5⟩
  · trivial
@[local step]
theorem u154 (freq m hl unseen ck out) :
    slot.Z135 freq m hl unseen ck out ⦃ Y112P0! ⦄ := by
  simp only [slot.Z135, lift, bind_tc_ok]
  refine u120 (u152 _ _ _ _) fun total => ?_
  refine u120 (u77 _) fun lt => ?_
  exact u153 _ _ _ _ _ _ _ _
@[local step]
theorem u155 (mx) :
    slot.Z139 mx ⦃ Y112P0! ⦄ := by
  rw [slot.Z139]
  exact u118 (fun h => u123 15#u32 (Nat.succ_le_of_lt h)) (fun _ => u117 trivial)
@[local step]
theorem u156 (tabs lcst i) :
    slot.Z128_loop0 tabs lcst i ⦃ Y112P0! ⦄ := by
  rw [slot.Z128_loop0]
  apply Std.loop.spec_decr_nat (measure := fun x => 256 - x.2.val) (inv := fun _ => True)
  · rintro ⟨tabs', i'⟩ _
    simp only [slot.Z128_loop0.body]
    refine u118 (fun hi => ?_) (fun _ => u117 trivial)
    refine u130 (Nat.lt_trans hi (by decide)) fun i1 => ?_
    refine u120 (u113 _ _) fun tabs1 => ?_
    refine u122 256#usize (Nat.succ_le_of_lt hi) fun i2 hi2 => ?_
    exact u117 ⟨trivial, u137 hi hi2⟩
  · trivial
@[local step]
theorem u157 (tabs lsym lcst l) :
    slot.Z128_loop1 tabs lsym lcst l ⦃ Y112P0! ⦄ := by
  rw [slot.Z128_loop1]
  apply Std.loop.spec_decr_nat (measure := fun x => 264 - x.2.val) (inv := fun _ => True)
  · rintro ⟨tabs', l'⟩ _
    simp only [slot.Z128_loop1.body, lift, bind_tc_ok]
    refine u118 (fun hl => ?_) (fun _ => u117 trivial)
    refine u125 u135 fun i hi => ?_
    refine u130 hi fun i1 => ?_
    refine u125 u135 fun c hc => ?_
    refine u120 (Q := fun _ => True) ?_ fun x => ?_
    · refine u118 (fun _ => u117 trivial) (fun _ => u118 (fun _ => u117 trivial) (fun _ => ?_))
      refine u122 288#usize (Nat.add_le_add_left (Nat.le_of_lt_succ hc) 257) fun i3 _ => ?_
      refine u125 u135 fun i4 hi4 => ?_
      refine u130 hi4 fun i5 => ?_
      exact u130 hc fun _ => u117 trivial
    refine u120 (u113 _ _) fun tabs1 => ?_
    refine u122 264#usize (Nat.succ_le_of_lt hl) fun l1 hl1 => ?_
    exact u117 ⟨trivial, u137 hl hl1⟩
  · trivial
@[local step]
theorem u158 (tabs dcst i) :
    slot.Z128_loop2 tabs dcst i ⦃ Y112P0! ⦄ := by
  rw [slot.Z128_loop2]
  apply Std.loop.spec_decr_nat (measure := fun x => 40 - x.2.val) (inv := fun _ => True)
  · rintro ⟨tabs', i'⟩ _
    simp only [slot.Z128_loop2.body, lift, bind_tc_ok]
    refine u118 (fun hi => ?_) (fun _ => u117 trivial)
    refine u120 (Q := fun _ => True) ?_ fun x => ?_
    · refine u118 (fun h30 => ?_) (fun _ => u117 trivial)
      refine u130 (Nat.lt_trans h30 (by decide)) fun i1 => ?_
      refine u125 u135 fun i2 hi2 => ?_
      exact u130 hi2 fun _ => u117 trivial
    refine u120 (u113 _ _) fun tabs1 => ?_
    refine u122 40#usize (Nat.succ_le_of_lt hi) fun i1 hi1 => ?_
    exact u117 ⟨trivial, u137 hi hi1⟩
  · trivial
@[local step]
theorem u159 (tabs lf df lsym ck) :
    slot.Z128 tabs lf df lsym ck ⦃ Y112P0! ⦄ := by
  simp only [slot.Z128]
  refine u120 (u149 _ _ _) fun ⟨mxl, ll1⟩ => ?_
  refine u120 (u149 _ _ _) fun ⟨mxd, dl1⟩ => ?_
  refine u120 (u155 _) fun i => ?_
  refine u120 (u154 _ _ _ _ _ _) fun lcst1 => ?_
  refine u120 (u155 _) fun i1 => ?_
  refine u120 (u154 _ _ _ _ _ _) fun dcst1 => ?_
  refine u120 (u156 _ _ _) fun tabs1 => ?_
  refine u120 (u157 _ _ _ _) fun tabs2 => ?_
  exact u158 _ _ _
@[local step]
theorem u160 (tabs bstart lf df lsym ck p t) :
    slot.Z103 tabs bstart lf df lsym ck p t ⦃ Y112P0! ⦄ := by
  simp only [slot.Z103, lift, bind_tc_ok]
  refine u118 (fun _ => u117 trivial) (fun _ => ?_)
  refine u131 (by decide) fun lf1 => ?_
  refine u120 (u159 _ _ _ _ _) fun tabs1 => ?_
  exact u120 (u113 _ _) fun _ => u117 trivial
@[local step]
theorem u161 (s plan lsym dtab tabs bstart ck lf df p t k) :
    slot.Z137_loop s plan lsym dtab tabs bstart ck lf df p t k ⦃ Y112P0! ⦄ := by
  rw [slot.Z137_loop]
  apply Std.loop.spec_decr_nat (measure := fun x => (Slice.len s).val - x.2.2.2.2.1.val) (inv := fun _ => True)
  · rintro ⟨tabs', bstart', lf', df', p', t', k'⟩ _
    simp only [slot.Z137_loop.body, lift, bind_tc_ok]
    refine u118 (fun hp => ?_) (fun _ => u117 trivial)
    refine u120 (u160 _ _ _ _ _ _ _ _) fun ⟨t1, tabs1, bstart1, lf1, df1⟩ => ?_
    refine u120 (u1 _ _) fun v => ?_
    refine u125 u135 fun i1 _ => ?_
    refine u119 (Q := fun r => (Slice.len s).val - r.2.2.2.2.val < (Slice.len s).val - p'.val) ?_
      fun ⟨tabs2, bstart2, lf2, df2, p1⟩ hq => u117 ⟨trivial, hq⟩
    refine u118 (fun h3 => ?_) (fun _ => ?_)
    · refine u124 (Nat.le_of_lt hp) fun i3 hi3 => ?_
      refine u119 (Q := fun r => (Slice.len s).val - r.2.2.val < (Slice.len s).val - p'.val) ?_
        fun ⟨a, a1, i4⟩ hq => u117 hq
      refine u118 (fun hle => ?_) (fun _ => ?_)
      · -- a match of `len` bytes: length and distance symbol counts
        refine u125 u135 fun i5 hi5 => ?_
        refine u130 hi5 fun i6 => ?_
        refine u125 u135 fun c hc => ?_
        refine u122 288#usize (Nat.add_le_add_left (Nat.le_of_lt_succ hc) 257) fun i8 _ => ?_
        refine u125 u135 fun i9 hi9 => ?_
        refine u130 hi9 fun i10 => ?_
        refine u125 u135 fun i12 hi12 => ?_
        refine u131 hi12 fun a2 => ?_
        refine u129 (by decide) (by decide) fun i13 => ?_
        refine u120 (u59 _ _) fun i15 => ?_
        refine u125 u135 fun dc hdc => ?_
        refine u130 (Nat.lt_trans hdc (by decide)) fun i16 => ?_
        refine u131 (Nat.lt_trans hdc (by decide)) fun a3 => ?_
        refine u122 (Slice.len s) (u139 hle hi3) fun p2 hp2 => ?_
        exact u117 (u138 hp (Nat.lt_of_lt_of_le (by decide) h3) hp2)
      · -- a literal (the planned match does not fit)
        refine u132 hp fun i5 => ?_
        refine u130 (u133 i5) fun i7 => ?_
        refine u131 (u133 i5) fun a2 => ?_
        refine u122 (Slice.len s) (Nat.succ_le_of_lt hp) fun p2 hp2 => ?_
        exact u117 (u137 hp hp2)
    · -- a literal
      refine u132 hp fun i2 => ?_
      refine u130 (u133 i2) fun i4 => ?_
      refine u131 (u133 i2) fun a => ?_
      refine u122 (Slice.len s) (Nat.succ_le_of_lt hp) fun p2 hp2 => ?_
      exact u117 (u137 hp hp2)
  · trivial
@[local step]
theorem u162 (s plan lsym dtab tabs bstart ck) :
    slot.Z137 s plan lsym dtab tabs bstart ck ⦃ Y112P0! ⦄ := by
  simp only [slot.Z137]
  refine u120 (u113 _ _) fun bstart1 => ?_
  refine u120 (u161 _ _ _ _ _ _ _ _ _ _ _ _) fun ⟨tabs1, bstart2, lf1, df1⟩ => ?_
  refine u131 (by decide) fun lf2 => ?_
  exact u120 (u159 _ _ _ _ _) fun _ => u117 trivial
@[local step]
theorem u163 (tabs tb litc i) :
    slot.Z119_loop0 tabs tb litc i ⦃ Y112P0! ⦄ := by
  rw [slot.Z119_loop0]
  apply Std.loop.spec_decr_nat (measure := fun x => 256 - x.2.val) (inv := fun _ => True)
  · rintro ⟨litc', i'⟩ _
    simp only [slot.Z119_loop0.body, lift, bind_tc_ok]
    refine u118 (fun hi => ?_) (fun _ => u117 trivial)
    refine u120 (u1 _ _) fun i2 => ?_
    refine u131 hi fun a => ?_
    refine u122 256#usize (Nat.succ_le_of_lt hi) fun i3 hi3 => ?_
    exact u117 ⟨trivial, u137 hi hi3⟩
  · trivial
@[local step]
theorem u164 (tabs tb lc l) :
    slot.Z119_loop1 tabs tb lc l ⦃ Y112P0! ⦄ := by
  rw [slot.Z119_loop1]
  apply Std.loop.spec_decr_nat (measure := fun x => 512 - x.2.val) (inv := fun _ => True)
  · rintro ⟨lc', l'⟩ _
    simp only [slot.Z119_loop1.body, lift, bind_tc_ok]
    refine u118 (fun hl => ?_) (fun _ => u117 trivial)
    refine u120 (Q := fun _ => True) (u118 (fun _ => u1 _ _) (fun _ => u117 trivial)) fun i => ?_
    refine u131 hl fun a => ?_
    refine u122 512#usize (Nat.succ_le_of_lt hl) fun l1 hl1 => ?_
    exact u117 ⟨trivial, u137 hl hl1⟩
  · trivial
@[local step]
theorem u165 (tabs tb dcc i) :
    slot.Z119_loop2 tabs tb dcc i ⦃ Y112P0! ⦄ := by
  rw [slot.Z119_loop2]
  apply Std.loop.spec_decr_nat (measure := fun x => 32 - x.2.val) (inv := fun _ => True)
  · rintro ⟨dcc', i'⟩ _
    simp only [slot.Z119_loop2.body, lift, bind_tc_ok]
    refine u118 (fun hi => ?_) (fun _ => u117 trivial)
    refine u120 (u1 _ _) fun i3 => ?_
    refine u131 hi fun a => ?_
    refine u122 32#usize (Nat.succ_le_of_lt hi) fun i4 hi4 => ?_
    exact u117 ⟨trivial, u137 hi hi4⟩
  · trivial
@[local step]
theorem u166 (tabs tb litc lc dcc) :
    slot.Z119 tabs tb litc lc dcc ⦃ Y112P0! ⦄ := by
  rw [slot.Z119]
  refine u120 (u163 _ _ _ _) fun litc1 => ?_
  refine u120 (u164 _ _ _ _) fun lc1 => ?_
  exact u120 (u165 _ _ _ _) fun _ => u117 trivial
theorem u167 {α:Type} {c:Prop} {inst:Decidable c} {a b:α} :
    WP.spec (@ite _ c inst (ok a) (ok b)) (fun _ => True) :=
  u118 (fun _ => u117 trivial) (fun _ => u117 trivial)
theorem u168 {ty:UScalarTy} {α:Type} {a b:UScalar ty} {inst:Decidable (a < b)} {X Y:Result α}
    {P:α  →  Prop} (hX:a.val < b.val  →  WP.spec X P) (hY:b.val  ≤  a.val  →  WP.spec Y P) :
    WP.spec (@ite _ (a < b) inst X Y) P :=
  u118 hX (fun h => hY (Nat.le_of_not_lt h))
theorem u169 {ty:UScalarTy} {α:Type} {a b:UScalar ty} {inst:Decidable (a  ≤  b)} {X Y:Result α}
    {P:α  →  Prop} (hX:a.val  ≤  b.val  →  WP.spec X P) (hY:b.val < a.val  →  WP.spec Y P) :
    WP.spec (@ite _ (a  ≤  b) inst X Y) P :=
  u118 hX (fun h => hY (Nat.lt_of_not_le h))
theorem u170 {α β:Type} {x:α} {k:α  →  Result β} {P:β  →  Prop}
    (h:WP.spec (k x) P):WP.spec (Bind.bind (lift x) k) P := h
theorem u171 (x:Usize):x.val  ≤  Usize.max := UScalar.max_USize_eq ▸ ScalarTac.UScalar.bounds x
theorem u172:4294967295  ≤  Usize.max := by
  rcases Usize.bounds_eq with h | h
  · rw [h, U32.max_eq]
  · rw [h, U64.max_eq];decide
theorem u173 {β:Type} {x y:Usize} {k:Usize  →  Result β} {P:β  →  Prop}
    (h:y.val  ≤  x.val) (hk:∀ z:Usize, z.val + y.val = x.val  →  WP.spec (k z) P) :
    WP.spec (Bind.bind (HSub.hSub x y:Result Usize) k) P :=
  WP.spec_bind (Usize.sub_spec h) (fun z hz => hk z ((congrArg (· + y.val) hz.1).trans (Nat.sub_add_cancel h)))
theorem u174 {β:Type} {x y:Usize} {k:Usize  →  Result β} {P:β  →  Prop}
    (h:y.val < x.val) (hk:∀ z:Usize, z.val + 1 = x.val  →  WP.spec (k z) P) :
    WP.spec (Bind.bind (HSub.hSub x 1#usize:Result Usize) k) P :=
  u173 (Nat.succ_le_of_lt (Nat.lt_of_le_of_lt (Nat.zero_le _) h)) hk
theorem u175 {β:Type} {x y:Usize} {k:Usize  →  Result β} {P:β  →  Prop}
    (h:x.val < y.val) (hk:∀ z:Usize, z.val = x.val + 1  →  WP.spec (k z) P) :
    WP.spec (Bind.bind (HAdd.hAdd x 1#usize:Result Usize) k) P :=
  WP.spec_bind (Usize.add_spec (Nat.le_trans (Nat.succ_le_of_lt h) (u171 y))) hk
theorem u176 {β:Type} {x:Usize} {k:Usize  →  Result β} {P:β  →  Prop} (c:Nat)
    (h:x.val  ≤  c) (hc:c < 4294967295) (hk:∀ z:Usize, z.val = x.val + 1  →  WP.spec (k z) P) :
    WP.spec (Bind.bind (HAdd.hAdd x 1#usize:Result Usize) k) P :=
  WP.spec_bind (Usize.add_spec (Nat.le_trans (Nat.succ_le_of_lt (Nat.lt_of_le_of_lt h hc)) u172)) hk
theorem u177 {β:Type} {x y w:Usize} {k:Usize  →  Result β} {P:β  →  Prop}
    (h:x.val + y.val  ≤  w.val) (hk:∀ z:Usize, z.val = x.val + y.val  →  WP.spec (k z) P) :
    WP.spec (Bind.bind (HAdd.hAdd x y:Result Usize) k) P :=
  WP.spec_bind (Usize.add_spec (Nat.le_trans h (u171 w))) hk
theorem u178 {β:Type} {x:Usize} {k:Usize  →  Result β} {P:β  →  Prop}
    (hk:∀ z:Usize, z.val < (1024#usize).val  →  WP.spec (k z) P) :
    WP.spec (Bind.bind (HMod.hMod x slot.Z90:Result Usize) k) P := by
  rw [slot.Z90];exact u125 (by decide) hk
theorem u179 {β:Type} {x y:Usize} {k:Usize  →  Result β} {P:β  →  Prop}
    (h:y.val ≠ 0) (hk:∀ z:Usize, WP.spec (k z) P) :
    WP.spec (Bind.bind (HDiv.hDiv x y:Result Usize) k) P :=
  WP.spec_bind (Usize.div_spec x h) (fun z _ => hk z)
theorem u180 (x:U64):WP.spec (HShiftRight.hShiftRight x 32#i32:Result U64) (fun _ => True) :=
  WP.spec_mono (U64.ShiftRight_IScalar_spec x 32#i32 (by decide) (by decide)) (fun _ _ => trivial)
theorem u181 (x:U64):WP.spec (HShiftLeft.hShiftLeft x 32#i32:Result U64) (fun _ => True) :=
  WP.spec_mono (U64.ShiftLeft_IScalar_spec x 32#i32 (by decide) (by decide)) (fun _ _ => trivial)
theorem u182 (x:U64):WP.spec (HShiftRight.hShiftRight x 9#i32:Result U64) (fun _ => True) :=
  WP.spec_mono (U64.ShiftRight_IScalar_spec x 9#i32 (by decide) (by decide)) (fun _ _ => trivial)
theorem u183 (x:U64):WP.spec (HShiftLeft.hShiftLeft x 9#i32:Result U64) (fun _ => True) :=
  WP.spec_mono (U64.ShiftLeft_IScalar_spec x 9#i32 (by decide) (by decide)) (fun _ _ => trivial)
theorem u184 (x:U32):WP.spec (HShiftRight.hShiftRight x 9#i32:Result U32) (fun _ => True) :=
  WP.spec_mono (U32.ShiftRight_IScalar_spec x 9#i32 (by decide) (by decide)) (fun _ _ => trivial)
theorem u185 (x:U32):WP.spec (HShiftRight.hShiftRight x 24#i32:Result U32) (fun _ => True) :=
  WP.spec_mono (U32.ShiftRight_IScalar_spec x 24#i32 (by decide) (by decide)) (fun _ _ => trivial)
theorem u186 {α β:Type} {n:Usize} {a:Std.Array α n} {i:Usize} {k:α  →  Result β} {P:β  →  Prop}
    (h:i.val < n.val) (hk:∀ x, WP.spec (k x) P):WP.spec (Bind.bind (Array.index_usize a i) k) P :=
  WP.spec_bind (Array.index_usize_spec a i (Nat.lt_of_lt_of_eq h a.property.symm)) (fun x _ => hk x)
theorem u187 {α β:Type} {n:Usize} {a:Std.Array α n} {i:Usize} {v:α} {k:Std.Array α n  →  Result β}
    {P:β  →  Prop} (h:i.val < n.val) (hk:∀ x, WP.spec (k x) P) :
    WP.spec (Bind.bind (Array.update a i v) k) P :=
  WP.spec_bind (Array.update_spec a i v (Nat.lt_of_lt_of_eq h a.property.symm)) (fun x _ => hk x)
theorem u188 {α β:Type} {s:Slice α} {i:Usize} {k:α  →  Result β} {P:β  →  Prop}
    (h:i.val < (Slice.len s).val) (hk:∀ x, WP.spec (k x) P) :
    WP.spec (Bind.bind (Slice.index_usize s i) k) P :=
  WP.spec_bind (Slice.index_usize_spec s i h) (fun x _ => hk x)
theorem u189 {α β:Type} {s:Slice α} {i:Usize} {v:α} {k:Slice α  →  Result β} {P:β  →  Prop}
    (h:i.val < (Slice.len s).val) (hk:∀ x:Slice α, x.length = s.length  →  WP.spec (k x) P) :
    WP.spec (Bind.bind (Slice.update s i v) k) P :=
  WP.spec_bind (Slice.update_spec s i v h) (fun x hx => hk x (hx ▸ Slice.set_length s i v))
theorem u190 {α β:Type} {v:alloc.vec.Vec α} {x:α} {n:Usize} {k:alloc.vec.Vec α  →  Result β}
    {P:β  →  Prop} (h:(alloc.vec.Vec.len v).val < n.val) (hk:∀ w, WP.spec (k w) P) :
    WP.spec (Bind.bind (alloc.vec.Vec.push v x) k) P :=
  WP.spec_bind (alloc.vec.Vec.push_spec v x (Nat.lt_of_lt_of_le h (u171 n))) (fun w _ => hk w)
theorem u191 {β:Type} {i:U32} {k:Usize  →  Result β} {P:β  →  Prop}
    (h:i.val < (32768#u32).val) (hk:∀ z:Usize, z.val  ≤  32768  →  WP.spec (k z) P) :
    WP.spec (Bind.bind (HAdd.hAdd (UScalar.cast .Usize i) 1#usize:Result Usize) k) P := by
  have hi:(UScalar.cast .Usize i).val  ≤  32767 := by
    rw [U32.cast_Usize_val_eq];exact Nat.le_of_lt_succ h
  exact u176 32767 hi (by decide) (fun z hz => hk z (Nat.le_trans (Nat.le_of_eq hz) (Nat.succ_le_succ hi)))
theorem u192 {β:Type} {z:Usize} {k:U64  →  Result β} {P:β  →  Prop}
    (h:z.val  ≤  32768) (hk:∀ c:U64, WP.spec (k c) P) :
    WP.spec (Bind.bind (HMul.hMul (UScalar.cast .U64 z) 512#u64:Result U64) k) P := by
  have h1:(UScalar.cast .U64 z).val  ≤  32768 := by
    rw [UScalar.cast_val_eq];exact Nat.le_trans (Nat.mod_le _ _) h
  have h2:(UScalar.cast .U64 z).val * (512#u64).val  ≤  U64.max := by
    rw [U64.max_eq];exact Nat.le_trans (Nat.mul_le_mul_right _ h1) (by decide)
  exact WP.spec_bind (U64.mul_spec h2) (fun c _ => hk c)
theorem u193 (b:U8):(UScalar.cast .Usize b).val < (256#usize).val := by
  rw [U8.cast_Usize_val_eq];exact b.hBounds
theorem u194 {x:Usize} (h:¬ x = 0#usize):(0#usize).val < x.val :=
  Nat.pos_of_ne_zero (fun h0 => h (UScalar.eq_imp x 0#usize h0))
theorem u195:slot.Z40.val ≠ 0 := by rw [slot.Z40];decide
theorem u196 {a b c:Nat} (h:a + 1 = b) (hb:b  ≤  c):a < c := Nat.lt_of_lt_of_le (u136 h) hb
theorem u197 {a k i e:Nat} (h1:a + k = i) (h2:i + 2 = e):a < e := by omega
@[local step]
theorem u198 (x stop q) :
    slot.Z108 x stop q ⦃ Y112P2! ⦄ := by
  rw [slot.Z108];exact u118 (fun _ => u167) (fun _ => u117 trivial)
@[local step]
theorem u199 (s litc ring out lo dlit q nxt mid) :
    slot.Z114_loop0 s litc ring out lo dlit q nxt mid ⦃ fun r => r.2.1.length = out.length ⦄ := by
  rw [slot.Z114_loop0]
  apply Std.loop.spec_decr_nat (measure := fun x => x.2.2.1.val) (inv := fun x => x.2.1.length = out.length)
  · rintro ⟨ring', out', q', nxt'⟩ hinv
    unfold slot.Z114_loop0.body
    refine u168 (fun h1 => ?_) (fun _ => u117 hinv)
    refine u169 (fun h2 => ?_) (fun _ => u117 hinv)
    refine u169 (fun h3 => ?_) (fun _ => u117 hinv)
    refine u174 h1 fun q1 hq1 => ?_
    refine u120 (u180 _) fun i2 => ?_
    refine u188 (u196 hq1 h2) fun i3 => ?_
    refine u170 <| u186 (u193 i3) fun i5 => ?_
    refine u170 <| u170 <| u120 (u181 _) fun i8 => ?_
    refine u170 <| u120 (Q := fun _ => True) ?_ fun v1 => ?_
    · exact u118 (fun _ => u178 fun i9 hi9 => u186 hi9 fun o => u167) (fun _ => u117 trivial)
    refine u178 fun i9 hi9 => ?_
    refine u187 hi9 fun a => ?_
    refine u170 <| u189 (u196 hq1 h3) fun s1 hs1 => ?_
    exact u117 ⟨hs1.trans hinv, u136 hq1⟩
  · rfl
@[local step]
theorem u200 (s litc lc ring out «end» chd dlit q nxt kc s1) :
    slot.Z114_loop1 s litc lc ring out «end» chd dlit q nxt kc s1 ⦃ fun r => r.2.1.length = out.length ⦄ := by
  rw [slot.Z114_loop1]
  apply Std.loop.spec_decr_nat (measure := fun x => x.2.2.1.val) (inv := fun x => x.2.1.length = out.length)
  · rintro ⟨ring', out', q', nxt'⟩ hinv
    unfold slot.Z114_loop1.body
    refine u168 (fun h1 => ?_) (fun _ => u117 hinv)
    refine u169 (fun h2 => ?_) (fun _ => u117 hinv)
    refine u169 (fun h3 => ?_) (fun _ => u117 hinv)
    refine u169 (fun h4 => ?_) (fun _ => u117 hinv)
    refine u174 h1 fun q1 hq1 => ?_
    refine u173 (Nat.le_of_lt (u196 hq1 h4)) fun rem _ => ?_
    refine u120 (u180 _) fun i2 => ?_
    refine u188 (u196 hq1 h2) fun i3 => ?_
    refine u170 <| u186 (u193 i3) fun i5 => ?_
    refine u170 <| u170 <| u120 (u181 _) fun i8 => ?_
    refine u170 <| u125 (by decide) fun i9 hi9 => ?_
    refine u186 hi9 fun i10 => ?_
    refine u170 <| u170 <| u120 (u181 _) fun i13 => ?_
    refine u170 <| u170 <| u170 <| u120 u167 fun v => ?_
    refine u178 fun i16 hi16 => ?_
    refine u186 hi16 fun o => ?_
    refine u120 u167 fun v1 => ?_
    refine u187 hi16 fun a => ?_
    refine u170 <| u189 (u196 hq1 h3) fun s2 hs2 => ?_
    exact u117 ⟨hs2.trans hinv, u136 hq1⟩
  · rfl
@[local step]
theorem u201 (s litc lc ring out stop «end» chd dlit q nxt kc) :
    slot.Z114_loop2 s litc lc ring out stop «end» chd dlit q nxt kc ⦃ fun r => r.2.2.length = out.length ⦄ := by
  rw [slot.Z114_loop2]
  apply Std.loop.spec_decr_nat (measure := fun x => x.2.2.1.val) (inv := fun x => x.2.1.length = out.length)
  · rintro ⟨ring', out', q', nxt'⟩ hinv
    unfold slot.Z114_loop2.body
    refine u168 (fun h1 => ?_) (fun _ => u117 hinv)
    refine u169 (fun h2 => ?_) (fun _ => u117 hinv)
    refine u169 (fun h3 => ?_) (fun _ => u117 hinv)
    refine u169 (fun h4 => ?_) (fun _ => u117 hinv)
    refine u174 h1 fun q1 hq1 => ?_
    refine u173 (Nat.le_of_lt (u196 hq1 h4)) fun rem _ => ?_
    refine u120 (u180 _) fun i2 => ?_
    refine u188 (u196 hq1 h2) fun i3 => ?_
    refine u170 <| u186 (u193 i3) fun i5 => ?_
    refine u170 <| u170 <| u120 (u181 _) fun i8 => ?_
    refine u170 <| u125 (by decide) fun i9 hi9 => ?_
    refine u186 hi9 fun i10 => ?_
    refine u170 <| u170 <| u120 (u181 _) fun i13 => ?_
    refine u170 <| u170 <| u170 <| u120 u167 fun v => ?_
    refine u178 fun i16 hi16 => ?_
    refine u187 hi16 fun a => ?_
    refine u170 <| u189 (u196 hq1 h3) fun s2 hs2 => ?_
    exact u117 ⟨hs2.trans hinv, u136 hq1⟩
  · rfl
@[local step]
theorem u202 (s litc lc ring out hi stop «end» kcd chd lo nxt0 dlit) :
    slot.Z114 s litc lc ring out hi stop «end» kcd chd lo nxt0 dlit ⦃ fun r => r.2.2.length = out.length ⦄ := by
  rw [slot.Z114]
  refine u170 <| u120 (u198 _ _ _) fun mid => ?_
  refine u119 (u199 s litc ring out lo dlit hi nxt0 mid) ?_
  rintro ⟨ring1, out1, q, nxt⟩ h0
  refine u120 (u115 _ _) fun i1 => ?_
  refine u120 (u180 _) fun i2 => ?_
  refine u170 <| u120 (u198 _ _ _) fun s1 => ?_
  refine u119 (u200 s litc lc ring1 out1 «end» chd dlit q nxt _ s1) ?_
  rintro ⟨ring2, out2, q1, nxt1⟩ h1
  exact WP.spec_mono (u201 s litc lc ring2 out2 stop «end» chd dlit q1 nxt1 _)
    (fun r h2 => h2.trans (h1.trans h0))
@[local step]
theorem u203 (lc ring p e bv l) :
    slot.Z101_loop lc ring p e bv l ⦃ Y112P2! ⦄ := by
  rw [slot.Z101_loop]
  apply Std.loop.spec_decr_nat (measure := fun x => e.val - x.2.val) (inv := fun _ => True)
  · rintro ⟨bv', l'⟩ _
    unfold slot.Z101_loop.body
    refine u168 (fun h1 => ?_) (fun _ => u117 trivial)
    refine u170 <| u178 fun i1 hi1 => ?_
    refine u186 hi1 fun i2 => ?_
    refine u120 (u180 _) fun i3 => ?_
    refine u125 (by decide) fun i4 hi4 => ?_
    refine u186 hi4 fun i5 => ?_
    refine u170 <| u170 <| u120 (u183 _) fun i8 => ?_
    refine u170 <| u170 <| u120 u167 fun bv1 => ?_
    refine u175 h1 fun l1 hl1 => ?_
    exact u117 ⟨trivial, u137 h1 hl1⟩
  · trivial
@[local step]
theorem u204 (lc ring p lo e) :
    slot.Z101 lc ring p lo e ⦃ Y112P2! ⦄ :=
  u203 lc ring p e _ lo
@[local step]
theorem u205 (lc ring p el t f chd x) :
    slot.Z126_loop lc ring p el t f chd x ⦃ Y112P2! ⦄ := by
  rw [slot.Z126_loop]
  apply Std.loop.spec_decr_nat (measure := fun x => 259 - x.2.val) (inv := fun _ => True)
  · rintro ⟨ring', x'⟩ _
    unfold slot.Z126_loop.body
    refine u169 (fun h1 => ?_) (fun _ => u117 trivial)
    refine u169 (fun h2 => ?_) (fun _ => u117 trivial)
    refine u169 (fun h3 => ?_) (fun _ => u117 trivial)
    refine u173 h3 fun i hi => ?_
    refine u169 (fun h4 => ?_) (fun _ => u117 trivial)
    have hx:el.val + x'.val  ≤  (258#usize).val :=
      Nat.add_comm x'.val el.val ▸ (Nat.add_le_add_right h4 el.val).trans (Nat.le_of_eq hi)
    have hx':x'.val  ≤  258 := Nat.le_trans (Nat.le_add_left _ _) hx
    refine u177 hx fun i1 _ => ?_
    refine u125 (by decide) fun i2 hi2 => ?_
    refine u186 hi2 fun i3 => ?_
    refine u170 <| u170 <| u120 (u181 _) fun i6 => ?_
    refine u170 <| u170 <| u170 <| u173 h2 fun i9 _ => ?_
    refine u178 fun i10 hi10 => ?_
    refine u186 hi10 fun o => ?_
    refine u120 u167 fun v1 => ?_
    refine u178 fun i11 hi11 => ?_
    refine u187 hi11 fun a => ?_
    refine u176 258 hx' (by decide) fun x1 hx1 => ?_
    exact u117 ⟨trivial, u137 (Nat.lt_succ_of_le hx') hx1⟩
  · trivial
@[local step]
theorem u206 (lc ring p el t f chd) :
    slot.Z126 lc ring p el t f chd ⦃ Y112P2! ⦄ :=
  u205 lc ring p el t f chd _
@[local step]
theorem u207 (ring top z) :
    slot.Z116_loop ring top z ⦃ Y112P2! ⦄ := by
  rw [slot.Z116_loop]
  apply Std.loop.spec_decr_nat (measure := fun x => top.val - x.2.val) (inv := fun _ => True)
  · rintro ⟨ring', z'⟩ _
    unfold slot.Z116_loop.body
    refine u168 (fun h1 => ?_) (fun _ => u117 trivial)
    refine u178 fun i hi => ?_
    refine u187 hi fun a => ?_
    refine u175 h1 fun z1 hz1 => ?_
    exact u117 ⟨trivial, u137 h1 hz1⟩
  · trivial
@[local step]
theorem u208 (ring st p z0) :
    slot.Z116 ring st p z0 ⦃ Y112P2! ⦄ := by
  rw [slot.Z116]
  refine u186 (by decide) fun i => ?_
  refine u170 <| u118 (fun _ => ?_) (fun _ => u117 trivial)
  refine u120 (u116 _ _) fun top => ?_
  refine u120 (u207 _ _ _) fun ring1 => ?_
  exact u170 <| u187 (by decide) fun st1 => u117 trivial
@[local step]
theorem u209 (lc ring p len bl t dcst chd2 pbest st) :
    slot.Z98 lc ring p len bl t dcst chd2 pbest st ⦃ Y112P2! ⦄ := by
  rw [slot.Z98]
  refine u118 (fun _ => u117 trivial) (fun _ => ?_)
  refine u119 (u116 t p) fun tt htt => ?_
  refine u173 htt.2 fun i _ => ?_
  refine u120 (u208 ring st p i) ?_
  rintro ⟨ring1, st1⟩
  refine u170 <| u120 (u115 _ _) fun i2 => ?_
  refine u120 (u180 _) fun i3 => ?_
  refine u170 <| u120 (u206 _ _ _ _ _ _ _) fun ring2 => ?_
  refine u118 (fun _ => ?_) (fun _ => u117 trivial)
  refine u118 (fun _ => ?_) (fun _ => u117 trivial)
  refine u118 (fun _ => ?_) (fun _ => u117 trivial)
  refine u170 <| u120 (u115 _ _) fun i5 => ?_
  refine u120 (u180 _) fun i6 => ?_
  exact u170 <| u120 (u206 _ _ _ _ _ _ _) fun ring3 => u117 trivial
@[local step]
theorem u210 (lc dcc dtab ring r p prev room pbest st) :
    slot.Z105 lc dcc dtab ring r p prev room pbest st ⦃ Y112P2! ⦄ := by
  rw [slot.Z105]
  refine u125 (by decide) fun i _ => ?_
  refine u170 <| u169 (fun _ => u117 trivial) (fun hA => ?_)
  refine u168 (fun _ => u117 trivial) (fun hB => ?_)
  refine u118 (fun _ => u117 trivial) (fun _ => ?_)
  refine u120 (u184 _) fun i1 => ?_
  refine u125 (by decide) fun i2 hi2 => ?_
  refine u170 <| u120 (u185 _) fun i3 => ?_
  refine u170 <| u191 hi2 fun i4 hi4 => ?_
  refine u120 (u59 _ _) fun i5 => ?_
  refine u125 (by decide) fun i6 hi6 => ?_
  refine u186 hi6 fun i7 => ?_
  refine u170 <| u170 <| u192 hi4 fun chd2 => ?_
  refine u175 hA fun i9 _ => ?_
  refine u176 258 hB (by decide) fun i10 _ => ?_
  refine u120 (u204 _ _ _ _ _) fun bb => ?_
  refine u125 (by decide) fun i11 _ => ?_
  refine u170 <| u120 (u182 _) fun i12 => ?_
  refine u170 <| u120 (u181 _) fun i14 => ?_
  refine u170 <| u170 <| u170 <| u120 (u209 _ _ _ _ _ _ _ _ _ _) ?_
  rintro ⟨ring1, st1⟩
  refine u186 (by decide) fun s0 => ?_
  refine u120 u167 fun cand1 => ?_
  exact u187 (by decide) fun st2 => u117 trivial
@[local step]
theorem u211 (tabs bstart litc lc dcc bs pos) :
    slot.Z102 tabs bstart litc lc dcc bs pos ⦃ Y112P2! ⦄ := by
  rw [slot.Z102]
  refine u186 (by decide) fun i => ?_
  refine u118 (fun _ => ?_) (fun _ => u117 trivial)
  refine u186 (by decide) fun i1 => ?_
  refine u168 (fun h => ?_) (fun _ => u117 trivial)
  refine u174 h fun b _ => ?_
  refine u170 <| u120 (u166 _ _ _ _ _) ?_
  rintro ⟨litc1, lc1, dcc1⟩
  refine u187 (by decide) fun bs1 => ?_
  refine u120 (u1 _ _) fun i3 => ?_
  exact u170 <| u187 (by decide) fun bs2 => u117 trivial
@[local step]
theorem u212 (rs e k) :
    slot.Z138 rs e k ⦃ Y112P2! ⦄ := by
  rw [slot.Z138]
  exact u118 (fun _ => u170 (u1 _ _)) (fun _ => u117 trivial)
@[local step]
theorem u213 (p cl room) :
    slot.Z111 p cl room ⦃ Y112P2! ⦄ := by
  rw [slot.Z111];exact u167
@[local step]
theorem u214 (bfirst p1 q) :
    slot.Z134 bfirst p1 q ⦃ Y112P2! ⦄ := by
  rw [slot.Z134];exact u118 (fun _ => u167) (fun _ => u117 trivial)
@[local step]
theorem u215 (ring p lo best) :
    slot.Z122 ring p lo best ⦃ Y112P2! ⦄ := by
  rw [slot.Z122]
  exact u118 (fun _ => u178 fun i hi => u186 hi fun o => u167) (fun _ => u117 trivial)
@[local step]
theorem u216 (s tabs bstart out ring litc lc dcc dlit bs dslot chd «end» lo p1 q nxt fuel) :
    slot.Z109_loop0_loop0 s tabs bstart out ring litc lc dcc dlit bs dslot chd «end» lo p1 q nxt fuel
      ⦃ fun r => r.1.length = out.length ⦄ := by
  rw [slot.Z109_loop0_loop0]
  apply Std.loop.spec_decr_nat (measure := fun x => x.2.2.2.2.2.2.2.2.val) (inv := fun x => x.1.length = out.length)
  · rintro ⟨out', ring', litc', lc', dcc', bs', q', nxt', fuel'⟩ hinv
    unfold slot.Z109_loop0_loop0.body
    refine u168 (fun h1 => ?_) (fun _ => u117 hinv)
    refine u168 (fun h2 => ?_) (fun _ => u117 hinv)
    refine u174 h2 fun fuel1 hf => ?_
    refine u174 h1 fun i _ => ?_
    refine u120 (u211 _ _ _ _ _ _ _) ?_
    rintro ⟨litc1, lc1, dcc1, bs1⟩
    refine u186 (by decide) fun i1 => ?_
    refine u120 (u214 _ _ _) fun stop => ?_
    refine u125 (by decide) fun i2 hi2 => ?_
    refine u186 hi2 fun i3 => ?_
    refine u170 <| u119 (u202 s litc1 lc1 ring' out' q' stop «end» _ chd lo nxt' dlit) ?_
    rintro ⟨nxt1, ring1, out1⟩ hg
    exact u117 ⟨hg.trans hinv, u136 hf⟩
  · rfl
@[local step]
theorem u217 (rs dtab ring lc dcc pbest st p e2 room prev j) :
    slot.Z109_loop0_loop1 rs dtab ring lc dcc pbest st p e2 room prev j ⦃ Y112P2! ⦄ := by
  rw [slot.Z109_loop0_loop1]
  apply Std.loop.spec_decr_nat (measure := fun x => e2.val - x.2.2.2.val) (inv := fun _ => True)
  · rintro ⟨ring', st', prev', j'⟩ _
    unfold slot.Z109_loop0_loop1.body
    refine u168 (fun h1 => ?_) (fun _ => u117 trivial)
    refine u120 (u1 _ _) fun i => ?_
    refine u120 (u210 _ _ _ _ _ _ _ _ _ _) ?_
    rintro ⟨prev1, ring1, st1⟩
    refine u175 h1 fun j1 hj1 => ?_
    exact u117 ⟨trivial, u137 h1 hj1⟩
  · trivial
@[local step]
theorem u218 (s rs tabs bstart dtab out n ring litc lc dcc dlit pbest st bs e hi) :
    slot.Z109_loop0 s rs tabs bstart dtab out n ring litc lc dcc dlit pbest st bs e hi
      ⦃ fun r => r.length = out.length ⦄ := by
  rw [slot.Z109_loop0]
  apply Std.loop.spec_decr_nat (measure := fun x => x.2.2.2.2.2.2.2.1.val) (inv := fun x => x.1.length = out.length)
  · rintro ⟨out', ring', litc', lc', dcc', st', bs', e', hi'⟩ hinv
    unfold slot.Z109_loop0.body
    refine u169 (fun h1 => ?_) (fun _ => u117 hinv)
    have he0:(0#usize).val < e'.val := Nat.lt_of_lt_of_le (by decide) h1
    refine u174 he0 fun i _ => ?_
    refine u120 (u1 _ _) fun i1 => ?_
    refine u170 <| u173 h1 fun i2 hi2 => ?_
    refine u120 (u1 _ _) fun i3 => ?_
    refine u170 <| u168 (fun _ => u117 ⟨hinv, he0⟩) (fun hk => ?_)
    refine u169 (fun _ => u117 ⟨hinv, he0⟩) (fun hp => ?_)
    refine u173 hk fun a ha => ?_
    refine u120 (u212 _ _ _) fun top => ?_
    refine u125 (by decide) fun i4 _ => ?_
    refine u170 <| u120 (u184 _) fun i5 => ?_
    refine u125 (by decide) fun i6 hi6 => ?_
    refine u170 <| u191 hi6 fun i7 hi7 => ?_
    refine u120 (u59 _ _) fun dslot => ?_
    refine u170 <| u192 hi7 fun chd => ?_
    refine u170 <| u120 (u213 _ _ _) fun «end» => ?_
    refine u186 (by decide) fun i9 => ?_
    refine u170 <| u175 hp fun p1 _ => ?_
    refine u120 (u115 _ _) fun nxt => ?_
    refine u170 <| u119 (u216 s tabs bstart out' ring' litc' lc' dcc' dlit bs' dslot chd «end»
      _ p1 hi' nxt _) ?_
    rintro ⟨out1, ring1, litc1, lc1, dcc1, bs1, nxt1⟩ ho1
    refine u120 (u211 _ _ _ _ _ _ _) ?_
    rintro ⟨litc2, lc2, dcc2, bs2⟩
    refine u120 (u180 _) fun i11 => ?_
    refine u120 (u114 _ _) fun i12 => ?_
    refine u125 (by decide) fun i13 hi13 => ?_
    refine u186 hi13 fun i14 => ?_
    refine u170 <| u170 <| u120 (u181 _) fun i17 => ?_
    refine u170 <| u187 (by decide) fun a1 => ?_
    refine u120 (u217 _ _ _ _ _ _ _ _ _ _ _ _) ?_
    rintro ⟨ring2, st1⟩
    refine u186 (by decide) fun i19 => ?_
    refine u120 (u215 _ _ _ _) fun best => ?_
    refine u178 fun i20 hi20 => ?_
    refine u187 hi20 fun a2 => ?_
    refine u170 <| u119 (u20 out1 _ _) fun out2 ho2 => ?_
    exact u117 ⟨ho2.trans (ho1.trans hinv), u197 ha hi2⟩
  · rfl
@[local step]
theorem u219 (s rs tabs bstart dtab out pmode) :
    slot.Z109 s rs tabs bstart dtab out pmode ⦃ fun r => r.length = out.length ⦄ := by
  rw [slot.Z109]
  refine u118 (fun _ => u117 rfl) (fun _ => ?_)
  refine u118 (fun _ => u117 rfl) (fun h0 => ?_)
  refine u179 u195 fun i3 => ?_
  refine u118 (fun _ => u117 rfl) (fun _ => ?_)
  refine u178 fun i5 hi5 => ?_
  refine u187 hi5 fun a => ?_
  refine u120 u167 fun dlit => ?_
  refine u125 (by decide) fun pbest _ => ?_
  refine u170 <| u174 (u194 h0) fun b0 _ => ?_
  refine u120 (u1 _ _) fun i8 => ?_
  refine u170 <| u170 <| u120 (u166 _ _ _ _ _) ?_
  rintro ⟨litc1, lc1, dcc1⟩
  exact u218 _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
@[local step]
theorem u220 (out n plan p) :
    slot.Z112_loop out n plan p ⦃ Y112P2! ⦄ := by
  rw [slot.Z112_loop]
  apply Std.loop.spec_decr_nat (measure := fun x => n.val - x.2.val) (inv := fun _ => True)
  · rintro ⟨plan', p'⟩ _
    unfold slot.Z112_loop.body
    refine u168 (fun h1 => ?_) (fun _ => u117 trivial)
    refine u168 (fun h2 => ?_) (fun _ => u117 trivial)
    refine u120 (u1 _ _) fun v => ?_
    refine u125 (by decide) fun i1 _ => ?_
    refine u170 <| u169 (fun h3 => ?_)
      (fun _ => u190 h2 fun plan1 => u175 h1 fun p1 hp1 => u117 ⟨trivial, u137 h1 hp1⟩)
    refine u173 (Nat.le_of_lt h1) fun i2 hi2 => ?_
    refine u169 (fun h4 => ?_)
      (fun _ => u190 h2 fun plan1 => u175 h1 fun p1 hp1 => u117 ⟨trivial, u137 h1 hp1⟩)
    refine u118 (fun _ => ?_)
      (fun _ => u190 h2 fun plan1 => u175 h1 fun p1 hp1 => u117 ⟨trivial, u137 h1 hp1⟩)
    refine u190 h2 fun plan1 => ?_
    have hle:p'.val + (UScalar.cast UScalarTy.Usize i1).val  ≤  n.val :=
      Nat.add_comm _ p'.val ▸ (Nat.add_le_add_right h4 p'.val).trans (Nat.le_of_eq hi2)
    refine u177 hle fun p1 hp1 => ?_
    exact u117 ⟨trivial, u138 h1 (Nat.lt_of_lt_of_le (by decide) h3) hp1⟩
  · trivial
@[local step]
theorem u221 (out n plan) :
    slot.Z112 out n plan ⦃ Y112P2! ⦄ :=
  u220 out n plan _
theorem u222 (x:R):x.val  ≤  Std.Usize.max := by scalar_tac
theorem u223 {α:Type} {x:α} {P:α  →  Prop} (h:P x):(ok x:Result α) ⦃ P ⦄ := (WP.spec_ok x).mpr h
theorem u224 {α β:Type} {m:Result α} {k:α  →  Result β} {Q:α  →  Prop} {P:β  →  Prop}
    (h1:m ⦃ Q ⦄) (h2:∀ x, Q x  →  k x ⦃ P ⦄):(do let x ← m;k x) ⦃ P ⦄ := WP.spec_bind h1 h2
theorem u225 {α β γ:Type} {f:α  →  β  →  Result γ} {a:α} {b:β} {P:γ  →  Prop} (h:f a b ⦃ P ⦄) :
    (uncurry f (a, b)) ⦃ P ⦄ := h
theorem u226 {x y:R} {β:Type} {k:R  →  Result β} {P:β  →  Prop} {a b:Nat}
    (hx:x.val = a) (hy:y.val = b) (h:a + b  ≤  Std.Usize.max)
    (hk:∀ z:R, z.val = a + b  →  k z ⦃ P ⦄):(do let z ← x + y;k z) ⦃ P ⦄ := by
  subst hx hy;exact WP.spec_bind (Usize.add_spec h) hk
theorem u227 {x y:R} {β:Type} {k:R  →  Result β} {P:β  →  Prop} {a b:Nat}
    (hx:x.val = a) (hy:y.val = b) (h:b  ≤  a)
    (hk:∀ z:R, z.val + b = a  →  k z ⦃ P ⦄):(do let z ← x - y;k z) ⦃ P ⦄ := by
  subst hx hy;exact WP.spec_bind (Usize.sub_spec h) (fun z hz => hk z (by omega))
theorem u228 {ty:UScalarTy} {x y:UScalar ty} {β:Type} {k:UScalar ty  →  Result β} {P:β  →  Prop} {b:Nat}
    (hy:y.val = b) (h:0 < b) (hk:∀ z:UScalar ty, z.val < b  →  k z ⦃ P ⦄) :
    (do let z ← x % y;k z) ⦃ P ⦄ := by
  subst hy
  exact WP.spec_bind (UScalar.rem_spec x (by omega)) (fun z hz => hk z (by rw [hz];exact Nat.mod_lt _ h))
theorem u229 {α:Type} {n:R} (v:Array α n) {i:R} {c:Nat}
    (hn:n.val = c) (h:i.val < c):i.val < v.length :=
  lt_of_lt_of_eq h ((Array.length_eq v).trans hn).symm
theorem u230 {α β:Type} {n:R} {v:Array α n} {i:R} {k:α  →  Result β} {P:β  →  Prop}
    {c:Nat} (hn:n.val = c) (h:i.val < c) (hk:∀ x, k x ⦃ P ⦄) :
    (do let x ← Array.index_usize v i;k x) ⦃ P ⦄ :=
  WP.spec_bind (Array.index_usize_spec v i (u229 v hn h)) (fun x _ => hk x)
theorem u231 {α β:Type} {n:R} {v:Array α n} {i:R} {x:α}
    {k:Array α n  →  Result β} {P:β  →  Prop}
    {c:Nat} (hn:n.val = c) (h:i.val < c) (hk:∀ a, a = v.set i x  →  k a ⦃ P ⦄) :
    (do let a ← Array.update v i x;k a) ⦃ P ⦄ :=
  WP.spec_bind (Array.update_spec v i x (u229 v hn h)) hk
theorem u232 {α β:Type} {v:Slice α} {i:R} {k:α  →  Result β} {P:β  →  Prop}
    (h:i.val < v.length) (hk:∀ x, k x ⦃ P ⦄):(do let x ← Slice.index_usize v i;k x) ⦃ P ⦄ :=
  WP.spec_bind (Slice.index_usize_spec v i h) (fun x _ => hk x)
theorem u233 {ty:UScalarTy} {ty1:IScalarTy} {x:UScalar ty} {y:IScalar ty1} {β:Type}
    {k:UScalar ty  →  Result β} {P:β  →  Prop}
    (h:0  ≤  y.val  ∧  y.val < ty.numBits) (hk:∀ z, k z ⦃ P ⦄):(do let z ← x <<< y;k z) ⦃ P ⦄ :=
  WP.spec_bind (UScalar.ShiftLeft_IScalar_spec x y _ h.1 h.2 rfl) (fun z _ => hk z)
theorem u234 {ty:UScalarTy} {ty1:IScalarTy} {x:UScalar ty} {y:IScalar ty1} {β:Type}
    {k:UScalar ty  →  Result β} {P:β  →  Prop} {n:Nat}
    (h:0  ≤  y.val  ∧  y.val < ty.numBits) (hn:y.toNat = n) (hk:∀ z:UScalar ty, z.val = x.val >>> n  →  k z ⦃ P ⦄) :
    (do let z ← x >>> y;k z) ⦃ P ⦄ := by
  subst hn
  exact WP.spec_bind (UScalar.ShiftRight_IScalar_spec x y h.1 h.2) (fun z hz => hk z hz.1)
theorem u235 {src:UScalarTy} (tgt:UScalarTy) (x:UScalar src):(UScalar.cast tgt x).val  ≤  x.val := by
  rw [UScalar.cast_val_eq];exact Nat.mod_le _ _
theorem u236:4294967295  ≤  Std.Usize.max := by scalar_tac
theorem u237 {α:Type} {m:Result α} {Q:α  →  Prop} (h:m ⦃ Q ⦄):m ⦃ Y112P0! ⦄ :=
  WP.spec_mono h (fun _ _ => trivial)
@[local step]
theorem u238 (s i):slot.Z118 s i ⦃ Y112P0! ⦄ := by
  rw [slot.Z118]
  simp only [lift, bind_tc_ok]
  apply u111 <;> intro h8
  · have h8':8  ≤  s.len.val := (UScalar.le_equiv _ _).mp h8
    refine u227 (b := 8) rfl rfl h8' ?_;intro i1 hi1
    apply u111 <;> intro hle
    · have hb:i.val + 8  ≤  s.length := by
        have hl := Slice.len_val s
        have hle':i.val  ≤  i1.val := (UScalar.le_equiv _ _).mp hle
        omega
      have hm:s.length  ≤  Std.Usize.max := Slice.length_ineq s
      clear hle hi1 h8' h8 i1
      refine u226 (b := 7) rfl rfl (by omega) ?_;intro i2 hi2
      refine u232 (by omega) ?_;intro i3;clear hi2
      refine u233 (by decide) ?_;intro i5
      refine u226 (b := 6) rfl rfl (by omega) ?_;intro i6 hi6
      refine u232 (by omega) ?_;intro i7;clear hi6
      refine u233 (by decide) ?_;intro i9
      refine u226 (b := 5) rfl rfl (by omega) ?_;intro i11 hi11
      refine u232 (by omega) ?_;intro i12;clear hi11
      refine u233 (by decide) ?_;intro i14
      refine u226 (b := 4) rfl rfl (by omega) ?_;intro i16 hi16
      refine u232 (by omega) ?_;intro i17;clear hi16
      refine u233 (by decide) ?_;intro i19
      refine u226 (b := 3) rfl rfl (by omega) ?_;intro i21 hi21
      refine u232 (by omega) ?_;intro i22;clear hi21
      refine u233 (by decide) ?_;intro i24
      refine u226 (b := 2) rfl rfl (by omega) ?_;intro i26 hi26
      refine u232 (by omega) ?_;intro i27;clear hi26
      refine u233 (by decide) ?_;intro i29
      refine u226 (b := 1) rfl rfl (by omega) ?_;intro i31 hi31
      refine u232 (by omega) ?_;intro i32;clear hi31
      refine u233 (by decide) ?_;intro i34
      refine u232 (by omega) ?_;intro i36
      exact u223 trivial
    · exact u223 trivial
  · exact u223 trivial
@[local step]
theorem u239 (s i d cap t run) :
    slot.Z100_loop0 s i d cap t run ⦃ Y112P0! ⦄ := by
  rw [slot.Z100_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (t', run') => cap.val - t'.val + run'.val)
    (inv := fun _ => True)
  · rintro ⟨t', run'⟩ _
    simp only [slot.Z100_loop0.body, lift, bind_tc_ok]
    apply u111 <;> intro hrun
    · have hr:run'.val = 1 := congrArg UScalar.val hrun
      apply u111 <;> intro hcap
      · have hcap':8  ≤  cap.val := (UScalar.le_equiv _ _).mp hcap
        refine u227 (b := 8) rfl rfl hcap' ?_;intro i1 hi1
        apply u111 <;> intro ht
        · have ht':t'.val  ≤  i1.val := (UScalar.le_equiv _ _).mp ht
          have hm := u222 cap
          refine u224 (u238 _ _) ?_;intro i3 _
          refine u224 (u238 _ _) ?_;intro i5 _
          apply u111 <;> intro hx
          · refine u226 (b := 8) rfl rfl (by omega) ?_;intro t1 ht1
            exact u223 ⟨trivial, (by omega:cap.val - t1.val + run'.val < cap.val - t'.val + run'.val)⟩
          · refine u224 (U32.div_spec _ (by decide)) ?_;intro i7 hi7
            have hi7':i7.val = (core.num.U64.leading_zeros (i3 ^^^ i5)).val / 8 := hi7
            have hlz := u12 (i3 ^^^ i5)
            have hc := u235 .Usize i7
            refine u226 rfl rfl (by omega) ?_;intro t1 ht1
            exact u223 ⟨trivial, (by omega:cap.val - t1.val + 0 < cap.val - t'.val + run'.val)⟩
        · exact u223 trivial
      · exact u223 trivial
    · exact u223 trivial
  · trivial
@[local step]
theorem u240 (s i d cap t run) :
    slot.Z100_loop1 s i d cap t run ⦃ Y112P0! ⦄ := by
  rw [slot.Z100_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (t', run') => cap.val - t'.val + run'.val)
    (inv := fun _ => True)
  · rintro ⟨t', run'⟩ _
    simp only [slot.Z100_loop1.body, lift, bind_tc_ok]
    apply u111 <;> intro hrun
    · have hr:run'.val = 1 := congrArg UScalar.val hrun
      apply u111 <;> intro ht
      · have ht':t'.val < cap.val := (UScalar.lt_equiv _ _).mp ht
        have hm := u222 cap
        apply u111 <;> intro ha
        · have ha' := (UScalar.lt_equiv _ _).mp ha
          have hl := Slice.len_val s
          apply u111 <;> intro hd
          · have hd' := (UScalar.le_equiv _ _).mp hd
            refine u232 (by omega) ?_;intro i3
            refine u227 rfl rfl hd' ?_;intro i4 hi4
            refine u232 (by omega) ?_;intro i5
            apply u111 <;> intro he
            · refine u226 (b := 1) rfl rfl (by omega) ?_;intro t1 ht1
              exact u223 ⟨trivial, (by omega:cap.val - t1.val + run'.val < cap.val - t'.val + run'.val)⟩
            · exact u223 ⟨trivial, (by omega:cap.val - t'.val + 0 < cap.val - t'.val + run'.val)⟩
          · exact u223 ⟨trivial, (by omega:cap.val - t'.val + 0 < cap.val - t'.val + run'.val)⟩
        · exact u223 ⟨trivial, (by omega:cap.val - t'.val + 0 < cap.val - t'.val + run'.val)⟩
      · exact u223 trivial
    · exact u223 trivial
  · trivial
@[local step]
theorem u241 (s i d max):slot.Z100 s i d max ⦃ Y112P0! ⦄ := by
  rw [slot.Z100]
  simp only [lift, bind_tc_ok]
  refine u224 (u237 (u116 ..)) ?_;intro cap _
  refine u224 (u239 _ _ _ _ _ _) ?_;rintro ⟨t, run⟩ _
  exact u225 (u240 _ _ _ _ _ _)
@[local step]
theorem u242 (pc pn want dup z):slot.Z133_loop pc pn want dup z ⦃ Y112P0! ⦄ := by
  rw [slot.Z133_loop]
  apply Std.loop.spec_decr_nat (measure := fun (_, z') => 16 - z'.val) (inv := fun _ => True)
  · rintro ⟨dup', z'⟩ _
    simp only [slot.Z133_loop.body]
    apply u111 <;> intro h1
    · apply u111 <;> intro h2
      · have h2':z'.val < 16 := (UScalar.lt_equiv _ _).mp h2
        refine u230 (c := 16) rfl h2' ?_;intro x
        refine u224 (Q := fun _ => True) ?_ ?_
        · split <;> exact u223 trivial
        intro dup1 _
        refine u226 (b := 1) rfl rfl (by have := u236;omega) ?_;intro z1 hz1
        exact u223 ⟨trivial, (by omega:16 - z1.val < 16 - z'.val)⟩
      · exact u223 trivial
    · exact u223 trivial
  · trivial
@[local step]
theorem u243 (pc pn want):slot.Z133 pc pn want ⦃ Y112P0! ⦄ := by
  rw [slot.Z133];exact u242 _ _ _ _ _
@[local step]
theorem u244 (pc pn c len dist cl cd adj dupmode) :
    slot.Z117 pc pn c len dist cl cd adj dupmode ⦃ Y112P0! ⦄ := by
  rw [slot.Z117]
  simp only [lift, bind_tc_ok]
  apply u111 <;> intro _
  · exact u223 trivial
  apply u111 <;> intro _
  · apply u111 <;> intro _
    · apply u111 <;> intro _
      · exact u223 trivial
      · apply u111 <;> intro _
        · exact u243 _ _ _
        · exact u223 trivial
    · apply u111 <;> intro _
      · exact u243 _ _ _
      · exact u223 trivial
  · apply u111 <;> intro _
    · exact u243 _ _ _
    · exact u223 trivial
@[local step]
theorem u245 (input rs c i last pc pn adj cl cd tbmax dupmode) :
    slot.Z129 input rs c i last pc pn adj cl cd tbmax dupmode ⦃ Y112P0! ⦄ := by
  rw [slot.Z129]
  simp only [lift, bind_tc_ok]
  refine u228 (b := 512) rfl (by decide) ?_;intro i1 _
  refine u234 (n := 9) (by decide) rfl ?_;intro i2 _
  apply u111 <;> intro h1
  · exact u223 trivial
  apply u111 <;> intro h2
  · exact u223 trivial
  apply u111 <;> intro h3
  · exact u223 trivial
  apply u111 <;> intro h4
  · exact u223 trivial
  apply u111 <;> intro h5
  · exact u223 trivial
  refine u224 (u244 _ _ _ _ _ _ _ _ _) ?_;intro dup _
  refine u224 (Q := fun _ => True) ?_ ?_
  · apply u111 <;> intro hd
    · have h5':¬ (258 < (UScalar.cast .Usize i1).val) := (UScalar.lt_equiv _ _).not.mp h5
      refine u227 (a := 258) rfl rfl (by omega) ?_;intro i3 _
      refine u224 (u237 (u116 ..)) ?_;intro i4 _
      exact u241 _ _ _ _
    · exact u223 trivial
  intro t _
  have h2':¬ ((UScalar.cast .Usize i2).val < 1) := (UScalar.lt_equiv _ _).not.mp h2
  refine u227 (b := 1) rfl rfl (by omega) ?_;intro i4 _
  refine u233 (by decide) ?_;intro i6
  refine u233 (by decide) ?_;intro i9
  refine u224 (u237 (u113 ..)) ?_;intro rs1 _
  exact u223 trivial
@[local step]
theorem u246 (input rs cands nc i pc pn cl cd tbmax dupmode adj q last) :
    slot.Z130_loop input rs cands nc i pc pn cl cd tbmax dupmode adj q last ⦃ Y112P0! ⦄ := by
  rw [slot.Z130_loop]
  apply Std.loop.spec_decr_nat (measure := fun (_, q', _) => 16 - q'.val) (inv := fun _ => True)
  · rintro ⟨rs', q', last'⟩ _
    simp only [slot.Z130_loop.body]
    apply u111 <;> intro h1
    · apply u111 <;> intro h2
      · have h2':q'.val < 16 := (UScalar.lt_equiv _ _).mp h2
        refine u230 (c := 16) rfl h2' ?_;intro c
        refine u224 (u245 _ _ _ _ _ _ _ _ _ _ _ _) ?_;rintro ⟨last1, rs1⟩ _
        refine u225 ?_
        refine u226 (b := 1) rfl rfl (by have := u236;omega) ?_;intro q1 hq1
        exact u223 ⟨trivial, (by omega:16 - q1.val < 16 - q'.val)⟩
      · exact u223 trivial
    · exact u223 trivial
  · trivial
@[local step]
theorem u247 (input rs cands nc i pc pn ppos cl cd tbmax dupmode) :
    slot.Z130 input rs cands nc i pc pn ppos cl cd tbmax dupmode ⦃ Y112P0! ⦄ := by
  rw [slot.Z130]
  simp only [lift, bind_tc_ok]
  refine u224 (u246 _ _ _ _ _ _ _ _ _ _ _ _ _ _) ?_;intro rs1 _
  refine u224 (u237 (u113 ..)) ?_;intro rs2 _
  exact u237 (u113 ..)
@[local step]
theorem u248 (lsym) (l e:R) (hl:l.val < 257) (he:e.val  ≤  258) :
    slot.Z113_loop0_loop0 lsym l e ⦃ fun r => e.val  ≤  r.val  ∧  r.val  ≤  258 ⦄ := by
  rw [slot.Z113_loop0_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun e' => 258 - e'.val)
    (inv := fun e' => e.val  ≤  e'.val  ∧  e'.val  ≤  258)
  · rintro e' ⟨h1, h2⟩
    simp only [slot.Z113_loop0_loop0.body]
    have hM := u236
    apply u111 <;> intro hlt
    · have hlt':e'.val < 258 := (UScalar.lt_equiv _ _).mp hlt
      refine u226 (b := 1) rfl rfl (by omega) ?_;intro i hi
      refine u230 (c := 512) rfl (by omega) ?_;intro i1
      refine u226 (b := 1) rfl rfl (by omega) ?_;intro i2 hi2
      refine u230 (c := 512) rfl (by omega) ?_;intro i3
      apply u111 <;> intro _
      · exact u223 ⟨⟨(by omega:e.val  ≤  i.val), (by omega:i.val  ≤  258)⟩,
          (by omega:258 - i.val < 258 - e'.val)⟩
      · exact u223 ⟨h1, h2⟩
    · exact u223 ⟨h1, h2⟩
  · exact ⟨le_refl _, he⟩
theorem u249 (nx a:Array Std.U16 512#usize) (l:R) (v:Std.U16)
    (hl:l.val < 512) (hv:l.val < v.val) (ha:a = nx.set l v)
    (h2:∀ j, j < l.val  →  j < (nx.val[j]!).val) :
    ∀ j, j < l.val + 1  →  j < (a.val[j]!).val := by
  intro j hj
  rw [ha, Array.set_val_eq, u40!_set _ _ _ _ (lt_of_lt_of_eq hl (Array.length_eq nx).symm)]
  split
  · omega
  · exact h2 j (by omega)
@[local step]
theorem u250 (lsym) (nextl:Array Std.U16 512#usize) (flen l:R)
    (hl:l.val  ≤  512) (hnx:∀ j, j < l.val  →  j < (nextl.val[j]!).val) :
    slot.Z113_loop0 lsym nextl flen l ⦃ fun r => u22 r ⦄ := by
  rw [slot.Z113_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, l') => 512 - l'.val)
    (inv := fun (nx', l') => l'.val  ≤  512  ∧  ∀ j, j < l'.val  →  j < (nx'.val[j]!).val)
  · rintro ⟨nx', l'⟩ ⟨h1, h2⟩
    simp only [slot.Z113_loop0.body, lift, bind_tc_ok]
    have hM := u236
    apply u111 <;> intro hlt
    · have hlt':l'.val < 512 := (UScalar.lt_equiv _ _).mp hlt
      apply u111 <;> intro _
      · refine u226 (b := 1) rfl rfl (by omega) ?_;intro i hi
        refine u231 (c := 512) rfl hlt' ?_;intro a ha
        have hv:(UScalar.cast .U16 i).val = i.val :=
          UScalar.cast_val_mod_pow_of_inBounds_eq _ _ (by show i.val < 65536;omega)
        have hs := u249 nx' a l' _ hlt' (by omega) ha h2
        exact u223 ⟨⟨(by omega:i.val  ≤  512), fun j (hj:j < i.val) => hs j (by omega)⟩,
          (by omega:512 - i.val < 512 - l'.val)⟩
      · apply u111 <;> intro h257
        · refine u226 (b := 1) rfl rfl (by omega) ?_;intro i hi
          refine u231 (c := 512) rfl hlt' ?_;intro a ha
          have hv:(UScalar.cast .U16 i).val = i.val :=
            UScalar.cast_val_mod_pow_of_inBounds_eq _ _ (by show i.val < 65536;omega)
          have hs := u249 nx' a l' _ hlt' (by omega) ha h2
          exact u223 ⟨⟨(by omega:i.val  ≤  512), fun j (hj:j < i.val) => hs j (by omega)⟩,
            (by omega:512 - i.val < 512 - l'.val)⟩
        · have h257':¬ (257  ≤  l'.val) := (UScalar.le_equiv _ _).not.mp h257
          refine u226 (b := 1) rfl rfl (by omega) ?_;intro e he
          refine u224 (u248 _ _ _ (by omega) (by omega)) ?_;intro e1 he1
          refine u231 (c := 512) rfl hlt' ?_;intro a ha
          refine u226 (b := 1) rfl rfl (by omega) ?_;intro l1 hl1
          have hv:(UScalar.cast .U16 e1).val = e1.val :=
            UScalar.cast_val_mod_pow_of_inBounds_eq _ _ (by show e1.val < 65536;omega)
          have hs := u249 nx' a l' _ hlt' (by omega) ha h2
          exact u223 ⟨⟨(by omega:l1.val  ≤  512), fun j (hj:j < l1.val) => hs j (by omega)⟩,
            (by omega:512 - l1.val < 512 - l'.val)⟩
    · have hge:¬ (l'.val < 512) := (UScalar.lt_equiv _ _).not.mp hlt
      exact u223 (fun j hj => h2 j (by omega))
  · exact ⟨hl, hnx⟩
@[local step]
theorem u251 (lsym) (nextl:Array Std.U16 512#usize) (flen:R) :
    slot.Z113 lsym nextl flen ⦃ fun r => u22 r ⦄ := by
  rw [slot.Z113]
  exact u250 _ _ _ _ (Nat.zero_le _) (fun j hj => absurd hj (Nat.not_lt_zero _))
@[local step]
theorem u252 (s:I) (prev:C 32768#usize) (i:R) (b8:Std.U64)
    (cap:R) (cands) (nice nc best c k:R)
    (hc:c.val  ≤  i.val) (hcap:9  ≤  cap.val) (hic:i.val + cap.val  ≤  s.length)
    (hs8:s.length + 8  ≤  Std.Usize.max) (hb:best.val  ≤  cap.val) :
    slot.Z140_loop s prev i b8 cap cands nice nc best c k
      ⦃ fun r => best.val  ≤  r.2.2.val  ∧  r.2.2.val  ≤  cap.val ⦄ := by
  rw [slot.Z140_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, k') => k'.val)
    (inv := fun (_, _, best', c', _) => c'.val  ≤  i.val  ∧  best.val  ≤  best'.val  ∧  best'.val  ≤  cap.val)
  · rintro ⟨cands', nc', best', c', k'⟩ ⟨h1, h2, h3⟩
    simp only [slot.Z140_loop.body, lift, bind_tc_ok]
    apply u111 <;> intro hk
    · have hk':0 < k'.val := (UScalar.lt_equiv _ _).mp hk
      apply u111 <;> intro _
      · apply u111 <;> intro _
        · apply u111 <;> intro _
          · apply u111 <;> intro hnc
            · have hnc':nc'.val < 15 := (UScalar.lt_equiv _ _).mp hnc
              refine u224 (u48 _ _ _ _ _ _ h1 hcap hic hs8) ?_;intro l hl
              refine u224 (Q := fun (x:C 16#usize  ×  R  ×  R) =>
                best.val  ≤  x.2.2.val  ∧  x.2.2.val  ≤  cap.val) ?_ ?_
              · apply u111 <;> intro hl0
                · have hl0':0 < l.val := (UScalar.lt_equiv _ _).mp hl0
                  apply u111 <;> intro _
                  · refine u233 (by decide) ?_;intro i4
                    refine u228 (b := 16) rfl (by decide) ?_;intro i5 hi5
                    refine u231 (c := 16) rfl hi5 ?_;intro a _
                    refine u226 (b := 1) rfl rfl (by have := u236;omega) ?_;intro nc2 _
                    exact u223 ⟨(by omega:best.val  ≤  l.val), hl.1⟩
                  · exact u223 ⟨h2, h3⟩
                · exact u223 ⟨h2, h3⟩
              rintro ⟨cands1, nc1, best1⟩ ⟨hb1, hb2⟩
              refine u225 (u225 ?_)
              refine u228 (b := 32768) dp_WN_val (by decide) ?_;intro i2 hi2
              refine u230 (c := 32768) rfl hi2 ?_;intro i3
              apply u111 <;> intro hnx
              · have hnx' := (UScalar.lt_equiv _ _).mp hnx
                refine u227 (b := 1) rfl rfl (by omega) ?_;intro k1 hk1
                exact u223 ⟨⟨(by omega:(UScalar.cast .Usize i3).val  ≤  i.val), hb1, hb2⟩,
                  (by omega:k1.val < k'.val)⟩
              · exact u223 ⟨⟨h1, hb1, hb2⟩, hk'⟩
            · exact u223 ⟨⟨h1, h2, h3⟩, hk'⟩
          · exact u223 ⟨⟨h1, h2, h3⟩, hk'⟩
        · exact u223 ⟨⟨h1, h2, h3⟩, hk'⟩
      · exact u223 ⟨⟨h1, h2, h3⟩, hk'⟩
    · exact u223 ⟨h2, h3⟩
  · exact ⟨hc, le_refl _, hb⟩
@[local step]
theorem u253 (s:I) (prev) (i start depth:R) (b8:Std.U64)
    (cap:R) (cands) (nc0 best0 nice:R)
    (hst:start.val  ≤  i.val) (hcap:9  ≤  cap.val) (hic:i.val + cap.val  ≤  s.length)
    (hs8:s.length + 8  ≤  Std.Usize.max) (hb:best0.val  ≤  cap.val) :
    slot.Z140 s prev i start depth b8 cap cands nc0 best0 nice
      ⦃ fun r => best0.val  ≤  r.1.2.val  ∧  r.1.2.val  ≤  cap.val ⦄ := by
  rw [slot.Z140]
  refine u224 (u252 _ _ _ _ _ _ _ _ _ _ _ hst hcap hic hs8 hb) ?_
  rintro ⟨cands1, nc, best⟩ ⟨h1, h2⟩
  exact u225 (u225 (u223 ⟨h1, h2⟩))
@[local step]
theorem u254 (input:I) (pa lc) (i s len dd tmax t bt:R) (bv:W)
    (hi:i.val < input.length) (hlen:len.val < 512) (hdd:dd.val < 8388608)
    (hN:input.length + 2147483648  ≤  Std.Usize.max)
    (ht:t.val  ≤  i.val) (hbt:bt.val  ≤  t.val) :
    slot.Z99_loop input pa lc i s len dd tmax t bt bv ⦃ fun r => r.1.val  ≤  i.val ⦄ := by
  rw [slot.Z99_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (t', _, _) => tmax.val - t'.val)
    (inv := fun (t', bt', _) => t'.val  ≤  i.val  ∧  bt'.val  ≤  t'.val)
  · rintro ⟨t', bt', bv'⟩ ⟨h1, h2⟩
    simp only [slot.Z99_loop.body, lift, bind_tc_ok]
    have hbi:bt'.val  ≤  i.val := Nat.le_trans h2 h1
    have hiM:i.val + 2147483648  ≤  Std.Usize.max := by omega
    clear hN ht hbt
    apply u111 <;> intro ht
    · have ht':t'.val < tmax.val := (UScalar.lt_equiv _ _).mp ht
      refine u226 rfl rfl (by omega) ?_;intro i1 _
      apply u111 <;> intro _
      · refine u226 (b := 1) rfl rfl (by omega) ?_;intro i2 hi2
        refine u226 rfl rfl (by omega) ?_;intro i3 hi3
        apply u111 <;> intro hge
        · have hA:i2.val + dd.val  ≤  i.val := by have := (UScalar.le_equiv _ _).mp hge;omega
          clear hge hi3 i3 hdd
          refine u227 rfl rfl h1 ?_;intro i4 hi4
          refine u227 (b := 1) rfl rfl (by omega) ?_;intro i5 _
          apply u111 <;> intro _
          · refine u227 (b := 1) rfl rfl (by omega) ?_;intro i6 hi6
            refine u232 (by omega) ?_;intro i7;clear hi6
            refine u227 (b := 1) rfl rfl (by omega) ?_;intro i8 hi8
            refine u227 rfl rfl (by omega) ?_;intro i9 hi9
            refine u232 (by omega) ?_;intro i10;clear hi9 hi8 hi4
            apply u111 <;> intro _
            · have hle:i2.val  ≤  i.val := Nat.le_trans (Nat.le_add_right _ _) hA
              have hbt2:bt'.val  ≤  i2.val := by omega
              have hms:tmax.val - i2.val < tmax.val - t'.val := by omega
              refine u227 rfl rfl hle ?_;intro i11 _
              refine u228 (b := 8192) u24 (by decide) ?_;intro i12 hi12
              refine u230 (c := 8192) rfl hi12 ?_;intro i13
              refine u234 (n := 32) (by decide) rfl ?_;intro i14 _
              refine u226 rfl rfl (by omega) ?_;intro i16 _
              refine u228 (b := 512) rfl (by decide) ?_;intro i17 hi17
              refine u230 (c := 512) rfl hi17 ?_;intro i18
              apply u111 <;> intro _
              · exact u223 ⟨⟨hle, le_refl _⟩, hms⟩
              · exact u223 ⟨⟨hle, hbt2⟩, hms⟩
            · exact u223 hbi
          · exact u223 hbi
        · exact u223 hbi
      · exact u223 hbi
    · exact u223 hbi
  · exact ⟨ht, hbt⟩
@[local step]
theorem u255 (input:I) (pa lc) (i s len dd tmax:R)
    (hi:i.val < input.length) (hlen:len.val < 512) (hdd:dd.val < 8388608)
    (hN:input.length + 2147483648  ≤  Std.Usize.max) :
    slot.Z99 input pa lc i s len dd tmax ⦃ fun r => r.1.val  ≤  i.val ⦄ := by
  rw [slot.Z99]
  exact u254 _ _ _ _ _ _ _ _ _ _ _ hi hlen hdd hN (Nat.zero_le _) (le_refl _)
@[local step]
theorem u256 (input:I) (pa cands nc lc) (nextl:Array Std.U16 512#usize)
    (dtab dcc) (i s:R) (base:W) (pcd fback lo k:R)
    (hnx:u22 nextl) (hi:i.val < input.length) (hN:input.length + 2147483648  ≤  Std.Usize.max) :
    slot.Z132_loop input pa cands nc lc nextl dtab dcc i s base pcd fback lo k ⦃ Y112P0! ⦄ := by
  rw [slot.Z132_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, k') => 16 - k'.val)
    (inv := fun _ => True)
  · rintro ⟨pa', lo', k'⟩ _
    simp only [slot.Z132_loop.body, lift, bind_tc_ok]
    apply u111 <;> intro _
    · apply u111 <;> intro h2
      · have h2':k'.val < 16 := (UScalar.lt_equiv _ _).mp h2
        have hM := u236
        refine u230 (c := 16) rfl h2' ?_;intro c
        refine u228 (b := 512) rfl (by decide) ?_;intro i1 hi1
        refine u234 (n := 9) (by decide) rfl ?_;intro i2 hi2
        have hlen := u235 .Usize i1
        have hdd := u235 .Usize i2
        have h9 := u35 c
        refine u224 (u59 _ _) ?_;intro i3 _
        refine u228 (b := 32) rfl (by decide) ?_;intro ds hds
        refine u230 (c := 32) rfl hds ?_;intro i4
        refine u224 (u56 _ _ _ _ _ _ _ _ hnx (by omega) (by omega)) ?_;intro pa1 _
        refine u226 (b := 1) rfl rfl (by omega) ?_;intro lo1 _
        refine u224 (Q := fun _ => True) ?_ ?_
        · apply u111 <;> intro _
          · apply u111 <;> intro _
            · refine u226 rfl rfl (by have := u33;omega) ?_;intro i7 _
              apply u111 <;> intro _
              · refine u224 (u255 _ _ _ _ _ _ _ _ hi (by omega) (by omega) hN) ?_
                rintro ⟨i8, i9⟩ hbb
                have hbb':i8.val  ≤  i.val := hbb
                refine u225 ?_
                apply u111 <;> intro _
                · refine u226 rfl rfl (by omega) ?_;intro i10 _
                  refine u226 rfl rfl (by omega) ?_;intro i14 _
                  exact u54 _ _ _ _
                · exact u223 trivial
              · exact u223 trivial
            · exact u223 trivial
          · exact u223 trivial
        intro pa2 _
        refine u226 (b := 1) rfl rfl (by omega) ?_;intro k1 hk1
        exact u223 ⟨trivial, (by omega:16 - k1.val < 16 - k'.val)⟩
      · exact u223 trivial
    · exact u223 trivial
  · trivial
@[local step]
theorem u257 (input:I) (pa cands nc lc) (nextl:Array Std.U16 512#usize)
    (dtab dcc) (i s:R) (base:W) (pcd fback:R)
    (hnx:u22 nextl) (hi:i.val < input.length) (hN:input.length + 2147483648  ≤  Std.Usize.max) :
    slot.Z132 input pa cands nc lc nextl dtab dcc i s base pcd fback ⦃ Y112P0! ⦄ := by
  rw [slot.Z132]
  exact u256 _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ hnx hi hN
@[local step]
theorem u258 (input:I) (pa cands nc lc) (nextl:Array Std.U16 512#usize)
    (dtab dcc) (i s:R) (base:W) (pcd fback:R)
    (hnx:u22 nextl) (hi:i.val < input.length) (hN:input.length + 2147483648  ≤  Std.Usize.max) :
    slot.Z131 input pa cands nc lc nextl dtab dcc i s base pcd fback ⦃ Y112P0! ⦄ := by
  rw [slot.Z131]
  apply u111 <;> intro _
  · exact u61 _ _ _ _ _ _ _ _ _ _ _ _ hnx hi hN
  · exact u257 _ _ _ _ _ _ _ _ _ _ _ _ _ hnx hi hN
@[local step]
theorem u259 (input:I) (plan rs)
    (ct lazyn d4 d7 skip h3d tbmax lz2max dupmode fback d7l d7e nice n:R)
    (head3:C 16384#usize) (head4:C 65536#usize) (prev4)
    (head7:C 65536#usize) (prev7 pa tb) (lsym:G 512#usize) (dtab)
    (nextl:Array Std.U16 512#usize) (lf df litc lc dcc) (lim:R) (sh7:W)
    (s next_upd:R) (cands pc) (pn ppos cl cd:R) (cdc:W) (i anchor alen:R)
    (hn:n.val = input.length) (hlim:lim.val + 8 = n.val)
    (hN:input.length + input.length  ≤  Std.Usize.max)
    (hls:u15 lsym.val 28) (hnx:u22 nextl)
    (hsi:s.val  ≤  i.val) (hin:i.val  ≤  n.val) (hcl:cl.val < 512)
    (h3:u15 head3.val i.val) (h4:u15 head4.val i.val) (h7:u15 head7.val i.val) :
    slot.Z123_loop input plan rs ct lazyn d4 d7 skip h3d tbmax lz2max dupmode fback d7l d7e nice n
      head3 head4 prev4 head7 prev7 pa tb lsym dtab nextl lf df litc lc dcc lim sh7 s next_upd cands pc pn ppos
      cl cd cdc i anchor alen ⦃ Y112P0! ⦄ := by
  have hS := u23 hN
  rw [slot.Z123_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, i', _, _) => lim.val - i'.val)
    (inv := fun (_, _, h3', h4', _, h7', _, _, _, _, _, _, _, _, s', _, _, _, _, _, cl', _, _, i', _, _) =>
       s'.val  ≤  i'.val  ∧  i'.val  ≤  n.val  ∧  cl'.val < 512  ∧  u15 h3'.val i'.val  ∧  u15 h4'.val i'.val  ∧ 
       u15 h7'.val i'.val)
  · rintro ⟨plan', rs', h3', h4', p4', h7', p7', pa', tb', lf', df', litc', lc', dcc', s', nu', cands', pc', pn',
      ppos', cl', cd', cdc', i', anc', alen'⟩ ⟨hs', hi', hcl', hh3, hh4, hh7⟩
    clear hsi hin hcl h3 h4 h7
    clear plan rs head3 head4 prev4 head7 prev7 pa tb lf df litc lc dcc s next_upd cands pc pn ppos cl cd cdc i
      anchor alen
    simp only [slot.Z123_loop.body, lift, bind_tc_ok]
    apply u111 <;> intro hlt
    swap
    · exact u223 trivial
    have hlt':i'.val < lim.val := (UScalar.lt_equiv _ _).mp hlt
    have hiM:i'.val + 2147483648  ≤  Std.Usize.max := by clear * - hi' hn hS;omega
    refine u224 (Q := fun _ => True) ?_ ?_
    · apply u111 <;> intro _
      · refine u226 (b := 258) rfl rfl (by clear * - hiM;omega) ?_;intro i1 _
        refine u228 (b := 8192) u24 (by decide) ?_;intro i2 hi2
        exact u237 (Array.update_spec _ _ _ (u229 _ rfl hi2))
      · exact u223 trivial
    intro pa1 _
    refine u224 (u41 _ _ (by clear * - hiM;omega)) ?_;intro b8 _
    refine u224 (u50 _ _ _ _ _ _ _ _ i'.val hh3 hh4 hh7 (le_refl _)) ?_
    rintro ⟨⟨c3, c4, c7⟩, head31, head41, prev41, head71, prev71⟩ ⟨hq1, hq2, hq3, hL3, hL4, hL7⟩
    have hq1:c3.val  ≤  i'.val := hq1
    have hq2:c4.val  ≤  i'.val := hq2
    have hq3:c7.val  ≤  i'.val := hq3
    have hL3:u15 head31.val i'.val := hL3
    have hL4:u15 head41.val i'.val := hL4
    have hL7:u15 head71.val i'.val := hL7
    iterate 5 refine u225 ?_
    refine u228 (b := 8192) u24 (by decide) ?_;intro i1 hi1
    refine u230 (c := 8192) rfl hi1 ?_;intro i2
    refine u234 (n := 32) (by decide) rfl ?_;intro i3 _
    refine u226 (b := 1) rfl rfl (by clear * - hiM;omega) ?_;intro i4 hi4
    refine u234 (n := 56) (by decide) rfl ?_;intro i5 _
    refine u228 (b := 256) rfl (by decide) ?_;intro i7 hi7
    refine u230 (c := 256) rfl hi7 ?_;intro i8
    refine u224 (u54 _ _ _ _) ?_;intro pa2 _
    refine u224 (Q := fun _ => True) ?_ ?_
    · apply u111 <;> intro _ <;> exact u223 trivial
    intro lzn _
    refine u224 (Q := fun _ => True) ?_ ?_
    · apply u111 <;> intro _
      · exact u223 trivial
      · refine u224 (Q := fun _ => True) ?_ ?_
        · apply u111 <;> intro _ <;> exact u223 trivial
        intro _ _;exact u223 trivial
    rintro ⟨lazy_here, dep7⟩ _
    refine u225 ?_
    clear hi1 hi7 hh3 hh4 hh7 hlt
    refine u224 (Q := fun (x:alloc.vec.Vec W  ×  alloc.vec.Vec W  ×  C 16384#usize  × 
          C 65536#usize  ×  C 32768#usize  ×  C 65536#usize  ×  C 32768#usize  × 
          Array Std.U64 8192#usize  ×  C 8192#usize  ×  C 320#usize  ×  C 32#usize  × 
          R  ×  C 16#usize  ×  C 16#usize  ×  R  ×  R  ×  R  ×  R  × 
          W  ×  R  ×  R  ×  R) =>
        match x with
        | (_, _, g3, g4, _, g7, _, _, _, _, _, s1, _, _, _, _, cl1, _, _, i12, _, _) =>
          s1.val  ≤  i12.val  ∧  i'.val < i12.val  ∧  i12.val  ≤  n.val  ∧  cl1.val < 512  ∧ 
          u15 g3.val i12.val  ∧  u15 g4.val i12.val  ∧  u15 g7.val i12.val) ?_ ?_
    · apply u110
      · -- continue inside the running match
        intro _ hc3 _
        have hc3':3  ≤  cl'.val := (UScalar.le_equiv _ _).mp hc3
        have h14:i'.val < i4.val := by clear * - hi4;omega
        refine u226 rfl rfl (by clear * - hiM hcl';omega) ?_;intro i13 _
        refine u228 (b := 512) rfl (by decide) ?_;intro i15 hi15
        refine u230 (c := 512) rfl hi15 ?_;intro i16
        refine u233 (by decide) ?_;intro i19
        refine u224 (u54 _ _ _ _) ?_;intro pa4 _
        refine u227 (b := 1) rfl rfl (by clear * - hc3';omega) ?_;intro cl2 hcl2
        exact u223 ⟨(by clear * - hs' h14;omega:s'.val  ≤  i4.val), h14,
          (by clear * - hi4 hlt' hlim;omega:i4.val  ≤  n.val), (by clear * - hcl2 hcl';omega:cl2.val < 512),
          u16 hL3 (Nat.le_of_lt h14), u16 hL4 (Nat.le_of_lt h14), u16 hL7 (Nat.le_of_lt h14)⟩
      · -- the search
        refine u227 rfl rfl hi' ?_;intro cap hcap
        refine u224 (Q := fun (x:R) => 9  ≤  x.val  ∧  i'.val + x.val  ≤  n.val) ?_ ?_
        · apply u111 <;> intro h
          · have h':258 < cap.val := (UScalar.lt_equiv _ _).mp h
            exact u223 ⟨(by decide:9  ≤  258), (by clear * - h' hcap;omega:i'.val + 258  ≤  n.val)⟩
          · exact u223 ⟨(by clear * - hcap hlt' hlim;omega:9  ≤  cap.val),
              (by clear * - hcap;omega:i'.val + cap.val  ≤  n.val)⟩
        rintro cap1 ⟨hcap1, hcap2⟩
        iterate 2 refine u225 ?_
        have hic:i'.val + cap1.val  ≤  input.length := by clear * - hcap2 hn;omega
        have hs8:input.length + 8  ≤  Std.Usize.max := by clear * - hS;omega
        have hilt:i'.val < input.length := by clear * - hic hcap1;omega
        clear hcap cap
        refine u224 (Q := fun (x:C 16#usize  ×  R  ×  R  ×  Bool) =>
          2  ≤  x.2.2.1.val  ∧  x.2.2.1.val  ≤  cap1.val) ?_ ?_
        · apply u111 <;> intro _
          · refine u224 (u48 _ _ _ _ _ _ hq1 hcap1 hic hs8) ?_;intro l3 hl3
            refine u224 (Q := fun (x:C 16#usize  ×  R  ×  R) =>
              2  ≤  x.2.2.val  ∧  x.2.2.val  ≤  cap1.val) ?_ ?_
            · apply u111 <;> intro h0
              · have h0':0 < l3.val := (UScalar.lt_equiv _ _).mp h0
                have hl3':l3.val = 0  ∨  2 < l3.val := hl3.2
                refine u233 (by decide) ?_;intro i21
                refine u231 (c := 16) rfl (by decide) ?_;intro a1 _
                exact u223 ⟨(by clear * - h0' hl3';omega:2  ≤  l3.val), hl3.1⟩
              · exact u223 ⟨(by decide:2  ≤  2), (by clear * - hcap1;omega:2  ≤  cap1.val)⟩
            rintro ⟨a, i17, i18⟩ ⟨hb1, hb2⟩
            exact u225 (u225 (u223 ⟨hb1, hb2⟩))
          · exact u223 ⟨(by decide:2  ≤  2), (by clear * - hcap1;omega:2  ≤  cap1.val)⟩
        rintro ⟨cands2, nc, best, p3⟩ ⟨hb1, hb2⟩
        have hb1:2  ≤  best.val := hb1
        have hb2:best.val  ≤  cap1.val := hb2
        iterate 3 refine u225 ?_
        refine u224 (Q := fun _ => True) ?_ ?_
        · apply u111 <;> intro _ <;> exact u223 trivial
        intro b _
        refine u224 (u49 _ _ _ _) ?_;rintro ⟨i17, i18⟩ hsk
        have hsk:i17.val  ≤  i'.val := Nat.le_trans hsk hq2
        refine u225 ?_
        refine u224 (u253 _ _ _ _ _ _ _ _ _ _ _ hsk hcap1 hic hs8 hb2) ?_
        rintro ⟨⟨nc1, best1⟩, cands3⟩ ⟨hw1, hw2⟩
        have hw1:2  ≤  best1.val := Nat.le_trans hb1 hw1
        have hw2:best1.val  ≤  cap1.val := hw2
        iterate 2 refine u225 ?_
        refine u224 (Q := fun _ => True) ?_ ?_
        · apply u111 <;> intro _
          · exact u223 trivial
          · refine u224 (Q := fun _ => True) ?_ ?_
            · apply u111 <;> intro _ <;> exact u223 trivial
            intro _ _;exact u223 trivial
        rintro ⟨cands4, dep71⟩ _
        refine u225 ?_
        refine u224 (Q := fun _ => True) ?_ ?_
        · apply u111 <;> intro _
          · apply u111 <;> intro _
            · exact u223 trivial
            · apply u111 <;> intro _ <;> exact u223 trivial
          · apply u111 <;> intro _ <;> exact u223 trivial
        intro b1 _
        refine u224 (u49 _ _ _ _) ?_;rintro ⟨i19, i20⟩ hsk2
        have hsk2:i19.val  ≤  i'.val := Nat.le_trans hsk2 hq3
        refine u225 ?_
        refine u224 (u253 _ _ _ _ _ _ _ _ _ _ _ hsk2 hcap1 hic hs8 hw2) ?_
        rintro ⟨⟨nc2, best2⟩, cands5⟩ ⟨hw3, hw4⟩
        have hw3:2  ≤  best2.val := Nat.le_trans hw1 hw3
        have hw4:best2.val  ≤  cap1.val := hw4
        iterate 2 refine u225 ?_
        refine u224 (Q := fun (x:C 16#usize  ×  R  ×  R) =>
          2  ≤  x.2.2.val  ∧  x.2.2.val  ≤  cap1.val) ?_ ?_
        · apply u112
          · intro hgt hle
            have hgt':best2.val < cl'.val := (UScalar.lt_equiv _ _).mp hgt
            refine u224 (u63 _ _ _) ?_;intro nc4 _
            refine u233 (by decide) ?_;intro i23
            refine u228 (b := 16) rfl (by decide) ?_;intro i24 hi24
            refine u231 (c := 16) rfl hi24 ?_;intro a _
            refine u224 (Q := fun _ => True) ?_ ?_
            · apply u111 <;> intro h16
              · have h16':nc4.val < 16 := (UScalar.lt_equiv _ _).mp h16
                exact u237 (Usize.add_spec (by
                  have := u236
                  show nc4.val + 1  ≤  Std.Usize.max
                  clear * - h16' this;omega))
              · exact u223 trivial
            intro i26 _
            exact u223 ⟨(by clear * - hgt' hw3;omega:2  ≤  cl'.val), (UScalar.le_equiv _ _).mp hle⟩
          · exact u223 ⟨hw3, hw4⟩
        rintro ⟨cands6, nc3, best3⟩ ⟨hb3, hb4⟩
        have hb3:2  ≤  best3.val := hb3
        have hb4:best3.val  ≤  cap1.val := hb4
        iterate 2 refine u225 ?_
        clear hb1 hb2 hw1 hw2 hw3 hw4 hsk hsk2 hq1 hq2 hq3
        refine u224 (u247 _ _ _ _ _ _ _ _ _ _ _ _) ?_;intro rs2 _
        refine u224 (Q := fun _ => True) ?_ ?_
        · apply u111 <;> intro _ <;> exact u223 trivial
        intro pcd _
        refine u224 (u65 _ _ _ _) ?_;intro alen2 _
        refine u224 (u65 _ _ _ _) ?_;intro anchor2 _
        refine u224 (Q := fun (x:R  ×  R  ×  W) => x.1.val < 512) ?_ ?_
        · apply u111 <;> intro hnc
          · have hnc':0 < nc3.val := (UScalar.lt_equiv _ _).mp hnc
            refine u227 (b := 1) rfl rfl hnc' ?_;intro i21 _
            refine u228 (b := 16) rfl (by decide) ?_;intro i22 hi22
            refine u230 (c := 16) rfl hi22 ?_;intro top
            refine u228 (b := 512) rfl (by decide) ?_;intro i23 hi23
            refine u234 (n := 9) (by decide) rfl ?_;intro i25 _
            refine u224 (u59 _ _) ?_;intro i26 _
            refine u228 (b := 32) rfl (by decide) ?_;intro i27 hi27
            refine u230 (c := 32) rfl hi27 ?_;intro cdc3
            have hsat := u109 (UScalar.cast .Usize i23) 1#usize
            have hcst := u235 .Usize i23
            exact u223 (by
              show (core.num.Usize.saturating_sub (UScalar.cast .Usize i23) 1#usize).val < 512
              clear * - hsat hcst hi23;omega)
          · exact u223 (by decide:0 < 512)
        rintro ⟨cl2, cd2, cdc2⟩ hcl2
        have hcl2:cl2.val < 512 := hcl2
        iterate 2 refine u225 ?_
        refine u224 (Q := fun (x:alloc.vec.Vec W  ×  C 16384#usize  × 
              C 65536#usize  ×  C 32768#usize  ×  C 65536#usize  × 
              C 32768#usize  ×  Array Std.U64 8192#usize  ×  C 8192#usize  × 
              C 320#usize  ×  C 32#usize  ×  R  ×  R  ×  R) =>
            match x with
            | (_, g3, g4, _, g7, _, _, _, _, _, s1, cl1, i12) =>
              s1.val  ≤  i12.val  ∧  i'.val < i12.val  ∧  i12.val  ≤  n.val  ∧  cl1.val < 512  ∧ 
              u15 g3.val i12.val  ∧  u15 g4.val i12.val  ∧  u15 g7.val i12.val) ?_ ?_
        · apply u112
          · intro _ hnc
            have hnc':0 < nc3.val := (UScalar.lt_equiv _ _).mp hnc
            refine u227 (b := 1) rfl rfl hnc' ?_;intro i24 _
            refine u228 (b := 16) rfl (by decide) ?_;intro i25 hi25
            refine u230 (c := 16) rfl hi25 ?_;intro c0
            refine u234 (n := 9) (by decide) rfl ?_;intro i26 hi26
            refine u228 (b := 259) rfl (by decide) ?_;intro i27 hi27
            refine u227 (a := 258) rfl rfl (by clear * - hi27;omega) ?_;intro i28 _
            have hd0:(UScalar.cast .Usize i26).val < 8388608 := by
              have h9 := u35 c0
              have hc := u235 .Usize i26
              clear * - h9 hc hi26;omega
            refine u224 (u67 _ _ _ _ _ hilt hd0 hS hs') ?_;intro t ht
            have ht':t.val  ≤  i'.val := by clear * - ht;omega
            refine u227 rfl rfl ht' ?_;intro st hst
            refine u224 (u73 _ _ _ _ _ _ _ _ _ _
              (by clear * - hst ht hs';omega) (by clear * - hst hiM;omega)) ?_
            rintro ⟨plan2, lf2, df2, tb2⟩ _
            iterate 3 refine u225 ?_
            refine u224 (Q := fun _ => True) ?_ ?_
            · apply u111 <;> intro hpl
              · have hpl' := (UScalar.lt_equiv _ _).mp hpl
                have hlv:plan2.len.val = plan2.val.length := alloc.vec.Vec.len_val plan2
                have hnm := u222 n
                exact u237 (alloc.vec.Vec.push_spec _ _ (by clear * - hpl' hlv hnm;omega))
              · exact u223 trivial
            intro plan3 _
            refine u226 rfl rfl (by clear * - ht' hb4 hic hS;omega) ?_;intro i30 _
            refine u228 (b := 512) rfl (by decide) ?_;intro i31 hi31
            refine u230 (c := 512) rfl hi31 ?_;intro i32
            refine u228 (b := 32) rfl (by decide) ?_;intro ls hls'
            refine u226 (a := 257) rfl rfl (by have := u236;clear * - hls' this;omega) ?_;intro i34 hi34
            have hi34':i34.val < 320 := by clear * - hi34 hls';omega
            refine u230 (c := 320) rfl hi34' ?_;intro i35
            refine u231 (c := 320) rfl hi34' ?_;intro a9 _
            refine u224 (u59 _ _) ?_;intro i37 _
            refine u228 (b := 32) rfl (by decide) ?_;intro ds hds
            refine u230 (c := 32) rfl hds ?_;intro i38
            refine u231 (c := 32) rfl hds ?_;intro a10 _
            refine u226 rfl rfl (by clear * - hb4 hic hS;omega) ?_;intro «end» hend
            refine u224 (Q := fun (x:R) => x.val  ≤  «end».val  ∧  x.val  ≤  lim.val) ?_ ?_
            · apply u111 <;> intro h
              · have h':lim.val < «end».val := (UScalar.lt_equiv _ _).mp h
                exact u223 ⟨Nat.le_of_lt h', Nat.le_refl _⟩
              · have h':¬ (lim.val < «end».val) := (UScalar.lt_equiv _ _).not.mp h
                exact u223 ⟨Nat.le_refl _, (by clear * - h';omega:«end».val  ≤  lim.val)⟩
            rintro end1 ⟨he1, he2⟩
            have hE:i'.val  ≤  «end».val := by clear * - hend;omega
            refine u224 (u52 _ _ _ _ _ _ _ _ _ «end».val (u16 hL3 hE) (u16 hL4 hE)
              (u16 hL7 hE) (by clear * - he1;omega) (by clear * - he2 hlim hn hS;omega)) ?_
            rintro ⟨head33, head43, prev43, head73, prev73⟩ ⟨hr3, hr4, hr7⟩
            iterate 4 refine u225 ?_
            refine u224 (u69 _ _ (by clear * - hend hb4 hic hS;omega)) ?_;intro pa4 _
            exact u223 ⟨Nat.le_refl _, (by clear * - hend hb3;omega:i'.val < «end».val),
              (by clear * - hend hb4 hcap2;omega:«end».val  ≤  n.val), (by decide:0 < 512), hr3, hr4, hr7⟩
          · have h14:i'.val < i4.val := by clear * - hi4;omega
            refine u224 (u258 _ _ _ _ _ _ _ _ _ _ _ _ _ hnx hilt hS) ?_;intro pa4 _
            exact u223 ⟨(by clear * - hs' h14;omega:s'.val  ≤  i4.val), h14,
              (by clear * - hi4 hlt' hlim;omega:i4.val  ≤  n.val), hcl2,
              u16 hL3 (Nat.le_of_lt h14), u16 hL4 (Nat.le_of_lt h14), u16 hL7 (Nat.le_of_lt h14)⟩
        rintro ⟨v, a, a1, a2, a3, a4, a5, a6, a7, a8, i21, i22, i23⟩ ⟨hv1, hv2, hv3, hv4, hv5, hv6, hv7⟩
        iterate 12 refine u225 ?_
        exact u223 ⟨hv1, hv2, hv3, hv4, hv5, hv6, hv7⟩
    rintro ⟨plan1, rs1, head32, head42, prev42, head72, prev72, pa3, tb1, lf1, df1, s1, cands1, pc1, pn1, ppos1,
      cl1, cd1, cdc1, i12, anchor1, alen1⟩ ⟨hs1, hii, hin1, hcl1, hk3, hk4, hk7⟩
    iterate 21 refine u225 ?_
    have hs1:s1.val  ≤  i12.val := hs1
    have hii:i'.val < i12.val := hii
    have hin1:i12.val  ≤  n.val := hin1
    have hms:lim.val - i12.val < lim.val - i'.val := by clear * - hii hlt';omega
    have h12M:i12.val + 2147483648  ≤  Std.Usize.max := by clear * - hin1 hn hS;omega
    refine u227 rfl rfl hs1 ?_;intro i13 _
    refine u224 (Q := fun (x:alloc.vec.Vec W  ×  Array Std.U64 8192#usize  ×  C 8192#usize  × 
        C 320#usize  ×  C 32#usize  ×  R) => x.2.2.2.2.2.val  ≤  i12.val) ?_ ?_
    · apply u111 <;> intro _
      · refine u224 (u73 _ _ _ _ _ _ _ _ _ _ hs1 (by clear * - h12M;omega)) ?_
        rintro ⟨plan3, lf3, df3, tb3⟩ _
        iterate 3 refine u225 ?_
        refine u224 (u69 _ _ (by clear * - h12M;omega)) ?_;intro pa5 _
        exact u223 (Nat.le_refl _)
      · exact u223 hs1
    rintro ⟨plan2, pa4, tb2, lf2, df2, s2⟩ hs2
    have hs2:s2.val  ≤  i12.val := hs2
    iterate 5 refine u225 ?_
    apply u111 <;> intro _
    · refine u226 rfl rfl (by have hU := u30;clear * - h12M hU;omega) ?_;intro next_upd1 _
      refine u224 (u99 _ _ _ _ _ _ _ hls) ?_
      rintro ⟨lf3, df3, litc1, lc1, dcc1⟩ _
      iterate 4 refine u225 ?_
      refine u224 (u59 _ _) ?_;intro i14 _
      refine u228 (b := 32) rfl (by decide) ?_;intro i15 hi15
      refine u230 (c := 32) rfl hi15 ?_;intro cdc2
      exact u223 ⟨⟨hs2, hin1, hcl1, hk3, hk4, hk7⟩, hms⟩
    · exact u223 ⟨⟨hs2, hin1, hcl1, hk3, hk4, hk7⟩, hms⟩
  · exact ⟨hsi, hin, hcl, h3, h4, h7⟩
@[local step]
theorem u260 (input:I) (plan rs)
    (ct lazyn d4 d7 skip h3d flen tbmax lz2max dupmode fback d7l d7e nice:R)
    (h16:16  ≤  input.length) (hN:input.length + input.length  ≤  Std.Usize.max) :
    slot.Z123 input plan rs ct lazyn d4 d7 skip h3d flen tbmax lz2max dupmode fback d7l d7e nice
      ⦃ Y112P0! ⦄ := by
  have hl := Slice.len_val input
  have hM := u236
  have hk := u29
  rw [slot.Z123]
  refine u224 (u108 _ _ (u38 _ _ _ (Nat.zero_le _))) ?_
  rintro ⟨lsym1, dtab1⟩ hls
  have hls:u15 lsym1.val 28 := hls
  refine u225 ?_
  refine u224 (u251 _ _ _) ?_;intro nextl1 hnx
  refine u224 (u103 _ _ _ hN) ?_;rintro ⟨lf1, df1⟩ _
  refine u225 ?_
  refine u224 (u97 _ _ _ _ _ _ _ hls) ?_;rintro ⟨litc1, lc1, dcc1⟩ _
  iterate 2 refine u225 ?_
  refine u224 (u76 _ _) ?_;rintro ⟨lf2, df2⟩ _
  refine u225 ?_
  refine u224 (u76 _ _) ?_;rintro ⟨lf3, df3⟩ _
  refine u225 ?_
  refine u227 (b := 8) rfl rfl (by clear * - hl h16;omega) ?_;intro lim hlim
  refine u224 (U32.mul_spec (by
    have := U32.max_eq
    show 8 * slot.Z50.val  ≤  U32.max
    clear * - hk this;omega)) ?_
  intro i hi
  have hi:i.val = 8 * slot.Z50.val := hi
  refine u224 (U32.sub_spec (by show i.val  ≤  64;clear * - hi hk;omega)) ?_;intro sh7 _
  refine u224 (u69 _ _ (by show 0 + 259  ≤  Std.Usize.max;clear * - hM;omega)) ?_;intro pa1 _
  refine u224 (u259 (hn := hl) (hlim := hlim) (hN := hN) (hls := hls) (hnx := hnx)
    (hsi := Nat.le_refl _) (hin := Nat.zero_le _) (hcl := by decide)
    (h3 := u38 _ _ _ (Nat.le_refl _)) (h4 := u38 _ _ _ (Nat.le_refl _))
    (h7 := u38 _ _ _ (Nat.le_refl _)) ..) ?_
  rintro ⟨plan1, rs1, pa2, tb1, lf4, df4, s, i1⟩ _
  iterate 7 refine u225 ?_
  apply u111 <;> intro _
  · apply u111 <;> intro hin
    · have hin':i1.val  ≤  input.len.val := (UScalar.le_equiv _ _).mp hin
      refine u224 (Q := fun (e:R) => e.val  ≤  input.len.val) ?_ ?_
      · apply u111 <;> intro _
        · exact u223 hin'
        · exact u223 (by clear * - hlim;omega:lim.val  ≤  input.len.val)
      intro e he
      apply u111 <;> intro hes
      · have hes':s.val < e.val := (UScalar.lt_equiv _ _).mp hes
        refine u224 (u73 _ _ _ _ _ _ _ _ _ _ (Nat.le_of_lt hes')
          (by clear * - he hl hN h16;omega)) ?_
        rintro ⟨plan2, x1, x2, x3⟩ _
        iterate 3 refine u225 ?_
        exact u223 trivial
      · exact u223 trivial
    · exact u223 trivial
  · exact u223 trivial
@[local step]
theorem u261 (input:I) (out:U) (k) (n:R) (plan rs lsym dtab)
    (passes pass:R) :
    slot.Z125_loop input out k n plan rs lsym dtab passes pass ⦃ fun r => r.2.length = out.length ⦄ := by
  rw [slot.Z125_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, pass') => passes.val - pass'.val)
    (inv := fun (out', _, _) => out'.length = out.length)
  · rintro ⟨out', plan', pass'⟩ hinv'
    simp only [slot.Z125_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · rfl
@[local step]
theorem u262 (input:I) (out:U) (k) :
    slot.Z125 input out k ⦃ fun r => r.2.length = out.length ⦄ := by
  have z8:u15 (Array.repeat 512#usize 0#u8).val 28 := u38 _ _ _ (by simp)
  rw [slot.Z125]
  step*
  repeat' (split <;> step*)
  all_goals first
    | scalar_tac
    | (have hw := u36 input.len (by rw [← i2_post];scalar_tac)
       simpa using hw)
@[local step]
theorem u263 (input:I) (out:U) (dk:R) :
    slot.Z124 input out dk ⦃ fun r => r.2.length = out.length ⦄ := by
  rw [slot.Z124]
  step*
open LZ77 (Matches)
def u264 (input:I) (p:Nat):Nat :=
  ((((((((input.val[p]!).val * 256 + (input.val[p + 1]!).val) * 256
    + (input.val[p + 2]!).val) * 256 + (input.val[p + 3]!).val) * 256
    + (input.val[p + 4]!).val) * 256 + (input.val[p + 5]!).val) * 256
    + (input.val[p + 6]!).val) * 256 + (input.val[p + 7]!).val)
theorem u265 (x:Std.U8):x.val < 256 := by scalar_tac
theorem u266 (input:I) (p k:Nat) (hk:k < 8) :
    (input.val[p + k]!).val = u264 input p / 256 ^ (7 - k) % 256 := by
  have := u265 (input.val[p]!);have := u265 (input.val[p+1]!)
  have := u265 (input.val[p+2]!);have := u265 (input.val[p+3]!)
  have := u265 (input.val[p+4]!);have := u265 (input.val[p+5]!)
  have := u265 (input.val[p+6]!);have := u265 (input.val[p+7]!)
  simp only [u264]
  rcases (show k = 0  ∨  k = 1  ∨  k = 2  ∨  k = 3  ∨  k = 4  ∨  k = 5  ∨  k = 6  ∨  k = 7 by omega) with
    rfl | rfl | rfl | rfl | rfl | rfl | rfl | rfl <;> simp only [Nat.add_zero, Nat.pow_zero,
    Nat.pow_succ, Nat.one_mul, Nat.sub_self, Nat.reduceSub] <;> omega
theorem u267 (input:I) (a b d:Nat) (hd:d  ≤  8)
    (h:u264 input a / 2 ^ (64 - 8 * d) = u264 input b / 2 ^ (64 - 8 * d)) :
    ∀ k, k < d  →  input.val[b + k]! = input.val[a + k]! := by
  intro k hk
  have e:(256:Nat) ^ (7 - k) = 2 ^ (64 - 8 * d) * 2 ^ (8 * (d - 1 - k)) := by
    rw [← pow_add, show (256:Nat) = 2 ^ 8 by norm_num, ← pow_mul]
    congr 1;omega
  have key:u264 input a / 256 ^ (7 - k) = u264 input b / 256 ^ (7 - k) := by
    rw [e, ← Nat.div_div_eq_div_mul, ← Nat.div_div_eq_div_mul, h]
  have ha := u266 input a k (by omega)
  have hb := u266 input b k (by omega)
  rw [key] at ha
  scalar_tac
theorem Matches.u268 {input:I} {a b l d:Nat} (h:Matches input a b l)
    (hd:d  ≤  8)
    (hw:u264 input (a + l) / 2 ^ (64 - 8 * d) = u264 input (b + l) / 2 ^ (64 - 8 * d)) :
    Matches input a b (l + d) := by
  intro k hk
  by_cases hkl:k < l
  · exact h k hkl
  · have := u267 input (a + l) (b + l) d hd hw (k - l) (by omega)
    rw [show b + l + (k - l) = b + k by omega, show a + l + (k - l) = a + k by omega] at this
    exact this
theorem Matches.u269 {input:I} {a b l l':Nat} {pa pb d:R}
    {x y:Std.U64} (h:Matches input a b l) (hpa:pa.val = a + l) (hpb:pb.val = b + l)
    (hx:x.val = u264 input pa.val) (hy:y.val = u264 input pb.val)
    (hd8:d.val  ≤  8) (hdiv:x.val / 2 ^ (64 - 8 * d.val) = y.val / 2 ^ (64 - 8 * d.val))
    (hl':l' = l + d.val):Matches input a b l' := by
  subst hl'
  rw [hx, hy, hpa, hpb] at hdiv
  exact Matches.u268 h hd8 hdiv
theorem Matches.u270 {input:I} {a b l l':Nat} {pa pb:R}
    {x y:Std.U64} (h:Matches input a b l) (hpa:pa.val = a + l) (hpb:pb.val = b + l)
    (hx:x.val = u264 input pa.val) (hy:y.val = u264 input pb.val)
    (hxy:¬(x != y) = true) (hl':l' = l + 8):Matches input a b l' := by
  have hxy':x.val = y.val := by simpa using hxy
  subst hl'
  apply Matches.u268 h (le_refl 8)
  rw [← hpa, ← hpb, ← hx, ← hy, hxy']
theorem Matches.u271 {input:I} {a b l l':Nat} {pa pb:R}
    {x y:Std.U8} (h:Matches input a b l) (hpa:pa.val = a + l) (hpb:pb.val = b + l)
    (hpa':pa.val < input.val.length) (hpb':pb.val < input.val.length)
    (hx:x = input.val[pa.val]) (hy:y = input.val[pb.val]) (hxy:x = y)
    (hl':l' = l + 1):Matches input a b l' := by
  subst hl' hxy
  apply LZ77.Matches.succ h
  rw [← hpa, ← hpb, getElem!_pos input.val pa.val hpa', getElem!_pos input.val pb.val hpb',
    ← hx, ← hy]
theorem u272 {a b:Nat} (h:a ^^^ b = 0):a = b := by
  have:a ^^^ (a ^^^ b) = b := by rw [← Nat.xor_assoc, Nat.xor_self, Nat.zero_xor]
  rw [h, Nat.xor_zero] at this;exact this
theorem u273 {x y m:Nat} (hz:x ^^^ y < 2 ^ m):x / 2 ^ m = y / 2 ^ m := by
  have h:(x ^^^ y) >>> m = 0 := by rw [Nat.shiftRight_eq_div_pow];exact Nat.div_eq_of_lt hz
  rw [Nat.shiftRight_xor_distrib] at h
  have := u272 h
  simpa [Nat.shiftRight_eq_div_pow] using this
theorem u274 (z:BitVec 64) :
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
@[step]
theorem u275 (input:I) (p:R) (hp:p.val + 8  ≤  input.length) :
    slot.Z162 input p ⦃ fun v => v.val = u264 input p.val ⦄ := by
  have hlift := @u0
  rw [slot.Z162]
  step*
  simp only [← getElem!_pos] at *
  simp only [u264]
  simp_all only [U8.cast_U64_val_eq]
@[step]
theorem u276 (x y:Std.U64) :
    slot.Z147 x y ⦃ fun d => d.val  ≤  8  ∧ 
      x.val / 2 ^ (64 - 8 * d.val) = y.val / 2 ^ (64 - 8 * d.val) ⦄ := by
  have hlift := @u0
  rw [slot.Z147]
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
  apply u273
  rw [← hz]
  exact u274 z.bv
@[step]
theorem u277 (input:I) (a b cap l0:R)
    (ha:a.val + cap.val  ≤  input.length) (hb:b.val + cap.val  ≤  input.length)
    (hl0:l0.val  ≤  cap.val) (h0:Matches input a.val b.val l0.val) :
    slot.Z165_loop0_loop0 input a b cap l0 ⦃ Y112P3! ⦄ := by
  rw [slot.Z165_loop0_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun l => cap.val - l.val)
    (inv := fun l => l.val  ≤  cap.val  ∧  Matches input a.val b.val l.val)
  · rintro l ⟨hle, hm⟩
    simp only [slot.Z165_loop0_loop0.body]
    have hmax:input.length  ≤  Std.Usize.max := Std.Slice.length_ineq input
    step*
    refine ⟨by scalar_tac, ?_, by scalar_tac⟩
    exact Matches.u271 hm (by assumption) (by assumption) (by scalar_tac) (by scalar_tac)
      (by assumption) (by assumption) (by assumption) (by scalar_tac)
  · exact ⟨hl0, h0⟩
@[step]
theorem u278 (input:I) (a b cap l0:R)
    (ha:a.val + cap.val  ≤  input.length) (hb:b.val + cap.val  ≤  input.length)
    (hl0:l0.val  ≤  cap.val) (h0:Matches input a.val b.val l0.val) :
    slot.Z165_loop0 input a b cap l0 ⦃ Y112P3! ⦄ := by
  rw [slot.Z165_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun l => cap.val - l.val)
    (inv := fun l => l.val  ≤  cap.val  ∧  Matches input a.val b.val l.val)
  · rintro l ⟨hle, hm⟩
    simp only [slot.Z165_loop0.body]
    have hmax:input.length  ≤  Std.Usize.max := Std.Slice.length_ineq input
    step*
    · -- the words differ: `first_diff` bytes more, and the loop is over
      refine ⟨by scalar_tac, ?_⟩
      exact Matches.u269 hm (by assumption) (by assumption) (by assumption) (by assumption)
        (by assumption) (by assumption) (by scalar_tac)
    · -- equal words: eight bytes more
      refine ⟨by scalar_tac, ?_, by scalar_tac⟩
      exact Matches.u270 hm (by assumption) (by assumption) (by assumption) (by assumption)
        (by assumption) (by scalar_tac)
  · exact ⟨hl0, h0⟩
@[step]
theorem u279 (input:I) (a b cap:R)
    (ha:a.val + cap.val  ≤  input.length) (hb:b.val + cap.val  ≤  input.length) :
    slot.Z165 input a b cap ⦃ Y112P3! ⦄ :=
  u278 input a b cap 0#usize ha hb (by simp) (LZ77.Matches.zero input a.val b.val)
@[step]
theorem u280 (input:I) (p len dist:R) :
    slot.Z95 input p len dist ⦃ fun valid => valid = true  → 
      3  ≤  len.val  ∧  len.val  ≤  258  ∧  1  ≤  dist.val  ∧  dist.val  ≤  32768  ∧  dist.val  ≤  p.val  ∧ 
      p.val + len.val  ≤  input.length  ∧  Matches input (p.val - dist.val) p.val len.val ⦄ := Y127U2! slot.Z95
@[local step]
theorem u281 (input:I) (plan out0:U)
    (n ntok0 k0 owed0 p0:R) (hn:n.val = input.length) (hout:input.length  ≤  out0.length)
    (hp0:p0.val  ≤  n.val) (hntok0:ntok0.val  ≤  p0.val) (hk0:k0.val  ≤  p0.val)
    (hdec0:LZ77.decode (toks out0 ntok0.val) = some ((bytes input).take p0.val)) :
    slot.Z143_loop input plan out0 n ntok0 k0 owed0 p0 ⦃ Y112P4! ⦄ := by
  have hlift := @u0
  rw [slot.Z143_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, p) => n.val - p.val)
    (inv := fun (out, ntok, k, _, p) => p.val  ≤  n.val  ∧  ntok.val  ≤  p.val  ∧  k.val  ≤  p.val  ∧ 
      out.length = out0.length  ∧ 
      LZ77.decode (toks out ntok.val) = some ((bytes input).take p.val))
  · rintro ⟨out, ntok, k, owed, p⟩ ⟨hp, hnt, hk, hlen, hde⟩
    simp only [slot.Z143_loop.body]
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
theorem u282 (input:I) (plan out:U)
    (hout:input.length  ≤  out.length) :
    slot.Z143 input plan out ⦃ Y112P5! ⦄ := by
  rw [slot.Z143]
  exact u281 input plan out (Std.Slice.len input) 0#usize 0#usize 0#usize 0#usize
    (by simp) hout (by simp) (by simp) (by simp) (by simp [toks, LZ77.decode])
theorem u283 (a:R) :
    (core.num.Usize.wrapping_add a 1024#usize).val - a.val  ≤  1024 := by
  rw [core.num.Usize.wrapping_add_val_eq, UScalar.size_UScalarTyUsize]
  have ha:a.val < Usize.size := by (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  have hs:1024 < Usize.size := by (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  have h1:(1024#usize).val = 1024 := by simp
  rw [h1]
  by_cases h:a.val + 1024 < Usize.size
  · rw [Nat.mod_eq_of_lt h];omega
  · rw [Nat.mod_eq_sub_mod (by omega), Nat.mod_eq_of_lt (by omega)];omega
theorem u284 (n:R) (B:Nat):u15 (Array.repeat n 0#usize).val B := by
  rw [Array.repeat_val];exact LeAll_replicate _ _ _ (by simp)
theorem u285 {ty:UScalarTy} {l:List (UScalar ty)} {B:Nat} (hl:u15 l B)
    {x:UScalar ty} {j:Nat} {hj:j < l.length} (hx:x = l[j]):x.val  ≤  B := by
  subst hx;exact hl j hj
theorem u286:u15 slot.Z0.val 64 := by
  unfold slot.Z0 u15;simp only [Array.make];decide
theorem A_SEG_bounds:256  ≤  slot.Z8.val  ∧  slot.Z8.val  ≤  65536  ∧ 
    slot.Z8.val + 512  ≤  slot.Z8.val * slot.Z3.val  ∧ 
    slot.Z8.val * slot.Z3.val  ≤  1048576 := by
  simp
theorem A_BLOCK_bounds:0 < slot.Z45.val  ∧  slot.Z45.val  ≤  16384  ∧ 
    slot.Z1.val  ≤  65536  ∧  slot.Z59.val ≠ 0 := by
  simp
theorem u287 (x y:R) :
    (core.num.Usize.saturating_add x y).val = min Std.Usize.max (x.val + y.val) := by
  have hsz:Std.Usize.max < 2 ^ UScalarTy.Usize.numBits := by
    rw [Std.Usize.max_def, Std.Usize.numBits]
    have:0 < 2 ^ UScalarTy.Usize.numBits := Nat.two_pow_pos _
    omega
  show (BitVec.ofNat _ (min (UScalar.max UScalarTy.Usize) (x.val + y.val))).toNat = _
  rw [BitVec.toNat_ofNat, UScalar.max_USize_eq, Nat.mod_eq_of_lt (by omega)]
@[local scalar_tac core.num.Usize.saturating_add x y]
theorem u288 (x y:R) :
    (core.num.Usize.saturating_add x y).val = min Std.Usize.max (x.val + y.val) := u287 x y
theorem engA_ite_pair {α β:Type} (c:Prop) [Decidable c] (a a':α) (b b':β) :
    (if c then (a, b) else (a', b')) = (if c then a else a', if c then b else b') := by
  split <;> rfl
theorem u289 {n:R} {a r:C n} {i:R} {v:W} {B:Nat}
    (hr:r = a.set i v) (ha:u15 a.val B) (hv:v.val  ≤  B):u15 r.val B := by
  rw [hr, Array.set_val_eq];exact u17 ha _ _ hv
@[step]
theorem u290:slot.Z16 ⦃ fun x => x.val = 2147483648 ⦄ := by
  unfold slot.Z16;step*
@[step]
theorem u291:slot.Z18 ⦃ fun x => x.val = 536870912 ⦄ := by
  unfold slot.Z18;step*
theorem u292:8192  ≤  slot.Z45.val  ∧  slot.Z45.val  ≤  1048576 := by simp [slot.Z45]
theorem C_HS_bounds:2  ≤  slot.Z47.val  ∧  slot.Z47.val  ≤  65536 := by simp [slot.Z47]
theorem u293:slot.Z20.val = 544 := by simp [slot.Z20]
theorem u294:slot.Z22.val < 2 ^ 27 := by simp [slot.Z22]
theorem u295:slot.Z3.val  ≤  32 := by simp [slot.Z3]
theorem u296:slot.Z46.val  ≤  256 := by simp [slot.Z46]
theorem C_UNUSED_LIT_le:slot.Z31.val  ≤  65536 := by simp [slot.Z31]
theorem C_UNUSED_DIST_le:slot.Z28.val  ≤  65536 := by simp [slot.Z28]
theorem u297:slot.Z30.val  ≤  65536 := by simp [slot.Z30]
theorem u298:slot.Z29.val  ≤  65536 := by simp [slot.Z29]
theorem u299:slot.Z46.val  ≤  65536 := by simp [slot.Z46]
theorem u300:slot.Z25.val  ≤  65536 := by simp [slot.Z25]
theorem u301:slot.Z26.val  ≤  65536 := by simp [slot.Z26]
theorem u302:slot.Z27.val  ≤  65536 := by simp [slot.Z27]
theorem u303:slot.Z11.val  ≤  65535 := by simp [slot.Z11]
theorem C_STOP_DIV_pos:0 < slot.Z24.val := by simp [slot.Z24]
theorem u304:1  ≤  slot.Z32.val := by simp [slot.Z32]
theorem u305:1  ≤  slot.Z4.val  ∧  slot.Z4.val  ≤  1048576 := by simp [slot.Z4]
theorem u306:slot.Z23.val  ≤  1048576 := by simp [slot.Z23]
theorem u307 (i:Nat) (h:i < 29):(slot.Z17.val[i]!).val  ≤  5 := by
  unfold slot.Z17;simp only [Array.make];revert i;decide
theorem u308 (i:Nat) (h:i < 30):(slot.Z12.val[i]!).val  ≤  13 := by
  unfold slot.Z12;simp only [Array.make];revert i;decide
@[step]
theorem u309 (i:R) (h:i.val < 29) :
    Array.index_usize slot.Z17 i ⦃ fun x => x.val  ≤  5 ⦄ := by
  have := u307 i.val h
  step*
  subst x_post
  rw [List.getElem!_eq_getElem?_getD, List.getElem?_eq_getElem (by (subst_vars;scalar_tac (simpAllMaxSteps := 0)))] at this
  exact this
@[step]
theorem u310 (i:R) (h:i.val < 30) :
    Array.index_usize slot.Z12 i ⦃ fun x => x.val  ≤  13 ⦄ := by
  have := u308 i.val h
  step*
  subst x_post
  rw [List.getElem!_eq_getElem?_getD, List.getElem?_eq_getElem (by (subst_vars;scalar_tac (simpAllMaxSteps := 0)))] at this
  exact this
@[step]
theorem u311 (x y:R) :
    lift (core.num.Usize.wrapping_add x y) ⦃ fun z => z = core.num.Usize.wrapping_add x y  ∧ 
      (x.val + y.val  ≤  Usize.max  →  z.val = x.val + y.val) ⦄ := by
  simp only [lift, WP.spec_ok, true_and]
  intro h
  rw [core.num.Usize.wrapping_add_val_eq, UScalar.size_UScalarTyUsize]
  apply Nat.mod_eq_of_lt
  (subst_vars;scalar_tac (simpAllMaxSteps := 0))
@[step]
theorem u312 (x y:W) :
    lift (core.num.U32.wrapping_add x y) ⦃ fun z => z = core.num.U32.wrapping_add x y  ∧ 
      (x.val + y.val  ≤  U32.max  →  z.val = x.val + y.val) ⦄ := by
  simp only [lift, WP.spec_ok, true_and]
  intro h
  rw [core.num.U32.wrapping_add_val_eq]
  apply Nat.mod_eq_of_lt
  (subst_vars;scalar_tac (simpAllMaxSteps := 0))
@[step]
theorem u313 (x y:Std.U64)
    (h:(x.val  ≤  4294967295  ∧  y.val  ≤  4294967295)  ∨  x.val * y.val  ≤  U64.max) :
    (x * y) ⦃ fun z => z.val = x.val * y.val  ∧  (x.val  ≤  4294967295  →  z.val  ≤  4294967295 * y.val) ⦄ := by
  have h':x.val * y.val  ≤  U64.max := by
    rcases h with ⟨hx, hy⟩ | h
    · have := Nat.mul_le_mul hx hy
      (subst_vars;scalar_tac (simpAllMaxSteps := 0))
    · exact h
  step*
  refine ⟨z_post, fun hx => ?_⟩
  rw [z_post]
  exact Nat.mul_le_mul_right _ hx
@[step]
theorem u314 (x y:W)
    (h:(x.val  ≤  16777215  ∧  y.val  ≤  256)  ∨  x.val * y.val  ≤  U32.max) :
    (x * y) ⦃ fun z => z.val = x.val * y.val  ∧  (y.val  ≤  256  →  z.val  ≤  256 * x.val) ⦄ := by
  have h':x.val * y.val  ≤  U32.max := by
    rcases h with ⟨hx, hy⟩ | h
    · have := Nat.mul_le_mul hx hy
      (subst_vars;scalar_tac (simpAllMaxSteps := 0))
    · exact h
  step*
  refine ⟨z_post, fun hy => ?_⟩
  rw [z_post, Nat.mul_comm]
  exact Nat.mul_le_mul_right _ hy
@[step]
theorem u315 (x y:Std.U64) (h:y.val ≠ 0) :
    (x / y) ⦃ fun z => z.val = x.val / y.val  ∧  (x.val  ≤  65536 * y.val  →  z.val  ≤  65536) ⦄ := by
  obtain ⟨z, hz, hv⟩ := UScalar.div_spec x h
  rw [hz]
  simp only [WP.spec_ok]
  refine ⟨hv, fun hx => ?_⟩
  rw [hv]
  exact Nat.div_le_of_le_mul (by rw [Nat.mul_comm];exact hx)
@[step]
theorem u316 (x:R) :
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
theorem u317 (x:Std.U64) :
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
theorem u318 {α:Type} (v:alloc.vec.Vec α) (x:α) (h:v.length < Usize.max) :
    alloc.vec.Vec.push v x ⦃ fun v1 => v1.val = v.val ++ [x]  ∧  v1.length = v.length + 1 ⦄ := by
  step*
  exact ⟨v1_post, by simp [v1_post]⟩
theorem u319 {α:Type} (n:R):(alloc.vec.Vec.with_capacity α n).length = 0 := rfl
theorem u320 {α β:Type} {c:Prop} [Decidable c] {A B:Result α} {k:α  →  Result β}
    {P:β  →  Prop} (hA:c  →  (A >>= k) ⦃ P ⦄) (hB:¬c  →  (B >>= k) ⦃ P ⦄) :
    ((if c then A else B) >>= k) ⦃ P ⦄ := by
  by_cases h:c
  · rw [if_pos h];exact hA h
  · rw [if_neg h];exact hB h
theorem spine_CFG_le:∀ r ∈ slot.Z7.val, ∀ x ∈ r.val, x.val  ≤  65536 := by
  unfold slot.Z7;decide
theorem spine_CFG_skip:∀ r ∈ slot.Z7.val, (r.val[0]!).val = 0  →  3  ≤  (r.val[2]!).val := by
  unfold slot.Z7;decide
theorem spine_knob_le {m:R} {r:O m} (hr:∀ x ∈ r.val, x.val  ≤  65536)
    {x:R} {j:Nat} {hj:j < r.val.length} (hx:x = r.val[j]):x.val  ≤  65536 := by
  subst hx;exact hr _ (List.getElem_mem _)
theorem spine_knob_skip {m:R} {r:O m}
    (hs:(r.val[0]!).val = 0  →  3  ≤  (r.val[2]!).val)
    {x0 x2:R} {h0:0 < r.val.length} {h2:2 < r.val.length}
    (hx0:x0 = r.val[0]) (hz:x0 = 0#usize) (hx2:x2 = r.val[2]):3  ≤  x2.val := by
  rw [getElem!_pos r.val 0 h0, getElem!_pos r.val 2 h2, ← hx0, ← hx2, hz] at hs
  exact hs rfl
theorem u321 (input:I) (out:U) (mode:R)
    (hlen:input.length  ≤  out.length) :
    slot.Z144 input out mode ⦃ Y112P1! ⦄ := Y127U3! slot.Z144
attribute [local step] u321
@[local step]
theorem u322 (input:I) (out:U) (mode:R) (hlen:input.length  ≤  out.length):slot.Z168 input out mode ⦃ Y112P1! ⦄ := by
 rw [slot.Z168]
 step*
 all_goals repeat' (split <;> step*)
end EA
set_option hygiene false in
local notation "Y127U4!" => (by
  refine ⟨Submission.EA.lz32_le x, ?_⟩
  by_cases h:x.val = 0
  · exact Or.inl h
  · right;rw [Submission.EA.lz32_eq x h];omega)
set_option hygiene false in
local notation "Y127U5!" q0__:max q1__:max => (by
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
local notation "Y127U7!" q0__:max q1__:max => (by
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
local notation "Y127U8!" q0__:max q1__:max => (by
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
local notation "Y127U9!" q0__:max q1__:max => (by
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
local notation "Y127U10!" q0__:max q1__:max => (by
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
local notation "Y127U11!" q0__:max q1__:max => (by
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
local notation "Y127U12!" q0__:max q1__:max q2__:max q3__:max => (by
  have hseg := Submission.EA.A_SEG_bounds
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, _, _, _, _, a_) => pe.val - a_.val)
    (inv := fun (_, _, _, _, _, _, sb_, st_, a_) => sb_.val  ≤  a_.val  ∧  st_.val  ≤  a_.val  ∧ 
      a_.val  ≤  pe.val + q1__ * q2__)
  · rintro ⟨cost_, ch_, lf_, df_, zf_, zd_, sb_, st_, a_⟩ ⟨hsb_, hst_, ha_⟩
    simp only [q3__]
    step*
    cases ‹R  ×  R›
    step*
    all_goals scalar_tac
  · exact ⟨hsb, hst, ha⟩)
set_option hygiene false in
local notation "Y127U13!" q0__:max q1__:max => (by
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
local notation "Y127U14!" q0__:max q1__:max => (by
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
local notation "Y127U15!" q0__:max q1__:max => (by
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
local notation "Y127U16!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun (lf_, z_) => 286 - z_.val)
    (inv := fun _ => True)
  · rintro ⟨lf_, z_⟩ _
    simp only [q1__]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial)
set_option hygiene false in
local notation "Y127U17!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun (dd_, i_) => 30 - i_.val)
    (inv := fun _ => True)
  · rintro ⟨dd_, i_⟩ _
    simp only [q1__]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial)
set_option hygiene false in
local notation "Y127U18!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun (i_, tl_) => 286 - i_.val)
    (inv := fun _ => True)
  · rintro ⟨i_, tl_⟩ _
    simp only [q1__]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial)
set_option hygiene false in
local notation "Y127U19!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, i_) => 256 - i_.val)
    (inv := fun _ => True)
  · rintro ⟨lit_, i_⟩ _
    simp only [q1__]
    step*
    repeat' (split <;> step*)
    all_goals try (have := Submission.EA.LeAll_get hhl i_.val (by scalar_tac))
    all_goals scalar_tac
  · trivial)
set_option hygiene false in
local notation "Y127U20!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, i_) => 259 - i_.val)
    (inv := fun _ => True)
  · rintro ⟨lc_, i_⟩ _
    simp only [q1__]
    step*
    repeat' (split <;> step*)
    all_goals try (have := Submission.EA.LeAll_get hhl i2.val (by scalar_tac))
    all_goals scalar_tac
  · trivial)
set_option hygiene false in
local notation "Y127U21!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, i_) => 30 - i_.val)
    (inv := fun _ => True)
  · rintro ⟨dc_, i_⟩ _
    simp only [q1__]
    step*
    repeat' (split <;> step*)
    all_goals try (have := Submission.EA.LeAll_get hhd i_.val (by scalar_tac))
    all_goals scalar_tac
  · trivial)
set_option hygiene false in
local notation "Y127U22!" q0__:max q1__:max => (by
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
set_option hygiene false in
local notation "Y127U23!" q0__:max => (by
  obtain ⟨q, t, h, c3, cr, cur⟩ := pre
  rw [q0__]
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
  all_goals scalar_tac)
set_option hygiene false in
local notation "Y127U24!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, _, _, i1_, _, _, _, _, _, _, _, _) => n.val - i1_.val)
    (inv := fun ((mp_:alloc.vec.Vec W), _, _, _, _, _, (i1_:R), _, (cd_:R), _, _, _, _, _, _) =>
      mp_.length  ≤  i1_.val + 1  ∧  1  ≤  cd_.val)
  · rintro ⟨mp_, mb_, head_, kid_, h3_, rct_, i1_, cl_, cd_, nq_, nt_, nh_, n3_, nr_, nc_⟩ ⟨hmp_, hcd_⟩
    unfold q1__
    simp only [Submission.EA.d1_ite_ok, Submission.EA.engA_ite_pair]
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
  · exact ⟨hmp, hcd⟩)
set_option hygiene false in
local notation "Y127U25!" q0__:max => (by
  have hhb := Submission.EA.dp_H4B_bound
  rw [q0__]
  step*
  all_goals try simp only [alloc.vec.Vec.length, *, List.length_append, List.length_singleton]
  all_goals scalar_tac)
set_option hygiene false in
local notation "Y127U26!" q0__:max q1__:max => (by
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
local notation "Y127U27!" q0__:max q1__:max q2__:max q3__:max => (by
  have hbt := Submission.EA.A_BLOCK_bounds
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, _, _, _, _, _, _, _, p0_, _, _) => n.val - p0_.val)
    (inv := fun (_, _, _, _, _, _, _, _, _, _, _, _, used_, bpt_) => used_.val < q1__  ∧ 
      256  ≤  bpt_.val  ∧  bpt_.val  ≤  130816)
  · rintro ⟨ch_, cost_, lit_, lc_, dc_, lf_, df_, bl_, bd_, sl_, sd_, p0_, used_, bpt_⟩ ⟨hused_, hbpt0, hbpt1⟩
    simp only [q2__, Submission.EA.d1_ite_ok]
    step*
    · -- the token estimate `need * bpt` fits in 32 bits
      have:need.val * bpt_.val  ≤  16384 * 130816 := Nat.mul_le_mul (by scalar_tac) hbpt1
      scalar_tac
    apply WP.spec_bind (Pₘ := fun (pe:R) => p0_.val  ≤  pe.val  ∧  pe.val  ≤  n.val  ∧ 
      (pe.val = n.val  ∨  p0_.val + q3__  ≤  pe.val))
    · split
      all_goals step*
      all_goals scalar_tac
    rintro pe hpe
    step*
    apply WP.spec_bind (Pₘ := fun (x:Std.Array W 512#usize  ×  Std.Array W 32#usize  ×  R) =>
      x.2.2.val < q1__)
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
    exact ⟨hused, hbpt.1, by omega⟩)
set_option hygiene false in
local notation "Y127U28!" => (by
  refine ⟨?_, ?_, ?_, ?_, ?_⟩ <;> simp only [Std.Array.repeat_val] <;>
    first | exact Submission.EA.LeAll_replicate _ _ _ (by simp) | simp)
set_option hygiene false in
local notation "Y127U29!" q0__:max q1__:max => (by
  rw [q0__]
  step*
  all_goals
    have hc:c ∈ q1__ := by rw [c_post];exact List.getElem_mem _
    first
    | exact Submission.EA.spine_knob_le (spine_CFG_le c hc) (by assumption)
    | exact Submission.EA.spine_knob_skip (spine_CFG_skip c hc) (by assumption) (by assumption) (by assumption))
namespace EB
open Aeneas Aeneas.Std Result ControlFlow
set_option maxRecDepth 8192
set_option maxHeartbeats 1000000
set_option linter.unusedTactic false
set_option linter.unreachableTactic false
set_option linter.unusedSimpArgs false
set_option linter.unusedVariables false
open LZ77 (toks bytes bytes_getElem! Matches emit_lit emit_match)


@[local scalar_tac x &&& y]
theorem u323 (x y:Nat):x &&& y  ≤  y := Nat.and_le_right
@[local scalar_tac x >>> y]
theorem u324 (x y:Nat):x >>> y  ≤  x := Nat.shiftRight_le x y
@[local scalar_tac System.Platform.numBits]
theorem u325:32  ≤  System.Platform.numBits := EA.u4
@[local scalar_tac core.num.U32.leading_zeros x]
theorem u326 (x:W) :
    (core.num.U32.leading_zeros x).val  ≤  32  ∧ 
      (x.val = 0  ∨  (core.num.U32.leading_zeros x).val  ≤  31) := Y127U4!
@[local scalar_tac core.num.U64.leading_zeros x]
theorem u327 (x:Std.U64):(core.num.U64.leading_zeros x).val  ≤  64 := EA.u12 x
theorem u328 (input:I) (a b cap l0:R)
    (ha:a.val + cap.val  ≤  input.length) (hb:b.val + cap.val  ≤  input.length)
    (hl0:l0.val  ≤  cap.val) (h0:Matches input a.val b.val l0.val) :
    slot.Z205_loop input a b cap l0 ⦃ Y112P3! ⦄ := by
  rw [slot.Z205_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun l => cap.val - l.val)
    (inv := fun l => l.val  ≤  cap.val  ∧  Matches input a.val b.val l.val)
  · rintro l ⟨hle, hinv⟩
    simp only [slot.Z205_loop.body]
    have hmax:input.length  ≤  Std.Usize.max := Std.Slice.length_ineq input
    step*
    refine ⟨by scalar_tac, ?_, by scalar_tac⟩
    rw [show l1.val = l.val + 1 by scalar_tac]
    apply LZ77.Matches.succ hinv
    rw [getElem!_pos _ _ (by scalar_tac), getElem!_pos _ _ (by scalar_tac)]
    simp_all
  · exact ⟨hl0, h0⟩
@[local step]
theorem u329 (input:I) (a b cap:R)
    (ha:a.val + cap.val  ≤  input.length) (hb:b.val + cap.val  ≤  input.length) :
    slot.Z205 input a b cap ⦃ Y112P3! ⦄ :=
  u328 input a b cap 0#usize ha hb (by scalar_tac) (LZ77.Matches.zero input a.val b.val)
@[local step]
theorem u330 (input:I) (p len dist:R) :
    slot.Z201 input p len dist ⦃ fun valid => valid = true  → 
      3  ≤  len.val  ∧  len.val  ≤  258  ∧  1  ≤  dist.val  ∧  dist.val  ≤  32768  ∧  dist.val  ≤  p.val  ∧ 
      p.val + len.val  ≤  input.length  ∧  Matches input (p.val - dist.val) p.val len.val ⦄ := Y127U2! slot.Z201
theorem u331 (input:I) (plan out0:U)
    (n ntok0 p0:R) (hn:n.val = input.length) (hout:input.length  ≤  out0.length)
    (hp0:p0.val  ≤  n.val) (hntok0:ntok0.val  ≤  p0.val)
    (hdec0:LZ77.decode (toks out0 ntok0.val) = some ((bytes input).take p0.val)) :
    slot.Z202_loop input plan out0 n ntok0 p0 ⦃ Y112P4! ⦄ := by
  rw [slot.Z202_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, p) => n.val - p.val)
    (inv := fun (out, ntok, p) => p.val  ≤  n.val  ∧  ntok.val  ≤  p.val  ∧  out.length = out0.length  ∧ 
      LZ77.decode (toks out ntok.val) = some ((bytes input).take p.val))
  · rintro ⟨out, ntok, p⟩ ⟨hp, hnt, hlen, hde⟩
    simp only [slot.Z202_loop.body]
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
  · exact ⟨hp0, hntok0, rfl, hdec0⟩
@[local step]
theorem u332 (input:I) (plan out:U)
    (hout:input.length  ≤  out.length) :
    slot.Z202 input plan out ⦃ Y112P5! ⦄ := by
  rw [slot.Z202]
  exact u331 input plan out (Std.Slice.len input) 0#usize 0#usize (by simp) hout
    (by simp) (by simp) (by simp [toks, LZ77.decode])
@[local step]
theorem u333 (n:R) (v0:alloc.vec.Vec W) (i0:R)
    (hv:v0.length = i0.val) (hi:i0.val  ≤  n.val) :
    slot.Z210_loop n v0 i0 ⦃ fun v => v.length = n.val ⦄ := by
  rw [slot.Z210_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, i) => n.val - i.val)
    (inv := fun (v, i) => v.length = i.val  ∧  i.val  ≤  n.val)
  · rintro ⟨v, i⟩ ⟨hvi, hin⟩
    simp only [slot.Z210_loop.body]
    step*
    all_goals have hlen:v1.length = v.length + 1 := by simp [v1_post]
    all_goals scalar_tac
  · exact ⟨hv, hi⟩
@[local step]
theorem u334 (n:R):slot.Z210 n ⦃ fun v => v.length = n.val ⦄ := by
  rw [slot.Z210]
  step*
  simp [alloc.vec.Vec.with_capacity]
@[local scalar_tac core.num.Usize.saturating_add x y]
theorem u335 (x y:R) :
    (core.num.Usize.saturating_add x y).val = min Std.Usize.max (x.val + y.val) := EA.u287 x y
@[local step]
theorem u336 (x) :
    slot.Z194 x ⦃ Y112P0! ⦄ := by
  rw [slot.Z194]
  step*
@[local step]
theorem u337 (len) :
    slot.Z186 len ⦃ fun r => r.val  ≤  28 ⦄ := by
  rw [slot.Z186]
  split
  · step*
  · split
    · step*
    · step*
      all_goals
        have hx:x.val = len.val - 3 := by
          rw [x_post, UScalar.cast_val_mod_pow_of_inBounds_eq _ _ (by scalar_tac)];scalar_tac
        have h1 := EA.u9 x 3 (by scalar_tac)
        have h2 := EA.u10 x 8 (by scalar_tac)
        subst i1_post
        scalar_tac
@[local step]
theorem u338 (lf) :
    slot.Z198_loop0 lf 0#usize ⦃ fun r => EA.u15 r.val 0 ⦄ := by
  rw [slot.Z198_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, k) => 512 - k.val)
    (inv := fun (lf', k) => k.val  ≤  512  ∧  ∀ j (hj:j < k.val) (hl:j < lf'.val.length), (lf'.val[j]).val = 0)
  · rintro ⟨lf', k⟩ ⟨hk, hz⟩
    simp only [slot.Z198_loop0.body]
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
@[local step]
theorem u339 (df) :
    slot.Z198_loop1 df 0#usize ⦃ fun r => EA.u15 r.val 0 ⦄ := by
  rw [slot.Z198_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, k) => 32 - k.val)
    (inv := fun (df', k) => k.val  ≤  32  ∧  ∀ j (hj:j < k.val) (hl:j < df'.val.length), (df'.val[j]).val = 0)
  · rintro ⟨df', k⟩ ⟨hk, hz⟩
    simp only [slot.Z198_loop1.body]
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
@[local step]
theorem u340 (s:I) (ch) (lim need:R) (lf df) (i t:R)
    (hlim:lim.val  ≤  2 ^ 31) (hls:lim.val  ≤  s.length) (hneed:need.val  ≤  2 ^ 31)
    (hlf:EA.u15 lf.val t.val) (hdf:EA.u15 df.val t.val) :
    slot.Z198_loop2 s ch lim need lf df i t ⦃ fun r => i.val  ≤  r.2.2.1.val  ∧  r.2.2.2.val  ≤  max t.val need.val  ∧ 
      r.2.2.1.val  ≤  max i.val (lim.val + 511)  ∧  r.2.2.1.val + 511 * t.val  ≤  i.val + 511 * r.2.2.2.val ⦄ := by
  rw [slot.Z198_loop2]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, t') => need.val - t'.val)
    (inv := fun (lf', df', i', t') => EA.u15 lf'.val t'.val  ∧  EA.u15 df'.val t'.val  ∧ 
      i.val  ≤  i'.val  ∧  t'.val  ≤  max t.val need.val  ∧ 
      i'.val  ≤  max i.val (lim.val + 511)  ∧  i'.val + 511 * t.val  ≤  i.val + 511 * t'.val)
  · rintro ⟨lf', df', i', t'⟩ ⟨hlf', hdf', hi', ht', hi2', hi3'⟩
    simp only [slot.Z198_loop2.body]
    step*
    apply WP.spec_bind (Pₘ := fun (x:Std.Array W 512#usize  ×  Std.Array W 32#usize  ×  R) =>
      EA.u15 x.1.val (t'.val + 1)  ∧  EA.u15 x.2.1.val (t'.val + 1)  ∧  i'.val < x.2.2.val  ∧  x.2.2.val  ≤  i'.val + 511)
    · split
      · -- a match: one length counter and one distance counter go up
        step*
        all_goals try (have := Submission.EA.LeAll_get hlf' i6.val (by scalar_tac))
        all_goals try (have := Submission.EA.LeAll_get hdf' i14.val (by scalar_tac))
        all_goals try scalar_tac
        refine ⟨?_, ?_, by scalar_tac, by scalar_tac⟩
        · rw [a_post, Array.set_val_eq];exact EA.u19 hlf' _ _ (by scalar_tac)
        · rw [a1_post, Array.set_val_eq];exact EA.u19 hdf' _ _ (by scalar_tac)
      · -- a literal: one literal counter goes up
        step*
        all_goals try (have := Submission.EA.LeAll_get hlf' i5.val (by scalar_tac))
        all_goals try scalar_tac
        refine ⟨?_, EA.u16 hdf' (by omega), by scalar_tac, by scalar_tac⟩
        rw [a_post, Array.set_val_eq];exact EA.u19 hlf' _ _ (by scalar_tac)
    · rintro ⟨lf1, df1, i3⟩ ⟨h1, h2, h3, h4⟩
      step*
      refine ⟨?_, ?_, by scalar_tac, by scalar_tac, by scalar_tac, by scalar_tac, by scalar_tac⟩
      · rw [show t1.val = t'.val + 1 by scalar_tac];exact h1
      · rw [show t1.val = t'.val + 1 by scalar_tac];exact h2
  · exact ⟨hlf, hdf, le_refl _, by omega, by omega, by omega⟩
@[local step]
theorem u341 (s:I) (ch) (p0 lim need:R) (lf df)
    (hlim:lim.val  ≤  2 ^ 31) (hls:lim.val  ≤  s.length) (hneed:need.val  ≤  2 ^ 31) :
    slot.Z198 s ch p0 lim need lf df ⦃ fun r => p0.val  ≤  r.1.1.val  ∧  r.1.2.val  ≤  need.val  ∧ 
      r.1.1.val  ≤  max p0.val (lim.val + 511)  ∧  r.1.1.val  ≤  p0.val + 511 * r.1.2.val ⦄ := Y127U1! slot.Z198
@[local step]
theorem u342 (pe:R) (cost) (cl z:R) (hpe:pe.val  ≤  2 ^ 31) (hcl:cl.val = cost.length) :
    slot.Z179_loop0 pe cost cl z ⦃ fun r => r.length = cost.length ⦄ := Y127U5! slot.Z179_loop0 slot.Z179_loop0.body
set_option hygiene false in
local notation "Y127U6!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun (mbest_, at0_, l_) => stop.val + 1 - at0_.val)
    (inv := fun _ => True)
  · rintro ⟨mbest_, at0_, l_⟩ _
    simp only [q1__]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial)
@[local step]
theorem u343 (lc) (cost:alloc.vec.Vec W) (stop base mbest at0 l) (hstop:stop.val < cost.length) :
    slot.Z179_loop1_loop0_loop0 lc cost stop base mbest at0 l ⦃ Y112P0! ⦄ := Y127U6! slot.Z179_loop1_loop0_loop0 slot.Z179_loop1_loop0_loop0.body
@[local step]
theorem u344 (lc) (cost:alloc.vec.Vec W) (stop base mbest at0 l) (hstop:stop.val < cost.length) :
    slot.Z179_loop1_loop0_loop1 lc cost stop base mbest at0 l ⦃ Y112P0! ⦄ := Y127U6! slot.Z179_loop1_loop0_loop1 slot.Z179_loop1_loop0_loop1.body
@[local step]
theorem u345 (mb lc dc) (cost:alloc.vec.Vec W) (cl i:R) (bias best bd) (prev pd:R) (j top:R)
    (hcl:cl.val = cost.length) (hi:i.val  ≤  2 ^ 31) (htop:top.val  ≤  mb.length)
    (hprev:prev.val  ≤  i.val + 258) (hpd:pd.val  ≤  32768) (hbd:bd.val  ≤  32767) :
    slot.Z179_loop1_loop0 mb lc dc cost cl i bias best bd prev pd j top ⦃ Y112P6! ⦄ := Y127U7! slot.Z179_loop1_loop0 slot.Z179_loop1_loop0.body
@[local step]
theorem u346 (lc) (cost:alloc.vec.Vec W) (stop base mbest at0 l) (hstop:stop.val < cost.length) :
    slot.Z179_loop1_loop1 lc cost stop base mbest at0 l ⦃ Y112P0! ⦄ := Y127U6! slot.Z179_loop1_loop1 slot.Z179_loop1_loop1.body
set_option maxHeartbeats 4000000 in
@[local step]
theorem u347 (s:I) (mp mb:alloc.vec.Vec W) (p0 lit lc dc) (cost ch:alloc.vec.Vec W)
    (cl i e xl xd:R)
    (hcl:cl.val = cost.length) (hi:i.val < cl.val) (hmp:i.val < mp.length) (hs:i.val  ≤  s.length)
    (hch:i.val  ≤  ch.length) (hi31:i.val  ≤  2 ^ 31) (hxl:xl.val  ≤  258) (hxd:xd.val  ≤  32768) :
    slot.Z179_loop1 s mp mb p0 lit lc dc cost ch cl i e xl xd ⦃ Y112P0! ⦄ := by
  rw [slot.Z179_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, i_, _, _, _) => i_.val)
    (inv := fun ((cost_:alloc.vec.Vec W), (ch_:alloc.vec.Vec W), (i_:R), _,
        (xl_:R), (xd_:R)) =>
      cost_.length = cl.val  ∧  ch_.length = ch.length  ∧  i_.val  ≤  i.val  ∧  xl_.val  ≤  258  ∧  xd_.val  ≤  32768)
  · rintro ⟨cost_, ch_, i_, e_, xl_, xd_⟩ ⟨hc_, hch_, hi_, hxl_, hxd_⟩
    simp only [slot.Z179_loop1.body]
    step*
    apply WP.spec_bind (Pₘ := fun (top:R) => top.val  ≤  mb.length)
    · split <;> step* <;> scalar_tac
    rintro top htop
    step*
    apply WP.spec_bind (Pₘ := fun (el:R) => el.val  ≤  258)
    · split <;> step* <;> scalar_tac
    rintro el hel
    step*
    all_goals
      try (
        apply WP.spec_bind (Pₘ := fun (x:W  ×  W) => x.2.val  ≤  32767)
        · split <;> step* <;> scalar_tac
        rintro ⟨best2, bd1⟩ hbd1
        step*)
    all_goals
      apply WP.spec_bind (Pₘ := fun (x:alloc.vec.Vec W  ×  W) => x.1.length = cost_.length)
      · split <;> step* <;> scalar_tac
      rintro ⟨cost1, i23⟩ hc1
      step*
      scalar_tac
  · exact ⟨hcl.symm, rfl, le_refl _, hxl, hxd⟩
@[local step]
theorem u348 (s:I) (mp mb) (p0 pe:R) (lit lc dc) (cost ch)
    (hpe:pe.val  ≤  2 ^ 31) :
    slot.Z179 s mp mb p0 pe lit lc dc cost ch ⦃ Y112P0! ⦄ := Y127U1! slot.Z179
@[local step]
theorem u349 (cost:U) (lc) (i hi:R) (base best l)
    (hhi:hi.val < 512) (hc:i.val + hi.val < cost.length) :
    slot.Z209_loop cost lc i hi base l best ⦃ Y112P0! ⦄ := Y127U8! slot.Z209_loop slot.Z209_loop.body
@[local step]
theorem u350 (cost:U) (lc i lo hi base width) :
    slot.Z209 cost lc i lo hi base width ⦃ Y112P0! ⦄ := Y127U1! slot.Z209
@[local step]
theorem u351 (pe:R) (cost) (cl z:R) (hpe:pe.val  ≤  2 ^ 31) (hcl:cl.val = cost.length) :
    slot.Z208_loop0 pe cost cl z ⦃ fun r => r.length = cost.length ⦄ := Y127U5! slot.Z208_loop0 slot.Z208_loop0.body
@[local step]
theorem u352 (mb lc dc) (cost:alloc.vec.Vec W) (cl i:R) (bias best bd) (prev pd:R) (j top:R)
    (hcl:cl.val = cost.length) (hi:i.val  ≤  2 ^ 31) (htop:top.val  ≤  mb.length)
    (hprev:prev.val  ≤  i.val + 258) (hpv:i.val  ≤  prev.val) (hpd:pd.val  ≤  32768) (hbd:bd.val  ≤  32767) :
    slot.Z208_loop1_loop0 mb lc dc cost cl i bias best bd prev pd j top ⦃ Y112P6! ⦄ := Y127U7! slot.Z208_loop1_loop0 slot.Z208_loop1_loop0.body
@[local step]
theorem u353 (s:I) (mp mb:alloc.vec.Vec W) (p0 lit lc dc) (cost ch:alloc.vec.Vec W)
    (cl i e xl xd:R)
    (hcl:cl.val = cost.length) (hi:i.val < cl.val) (hmp:i.val < mp.length) (hs:i.val  ≤  s.length)
    (hch:i.val  ≤  ch.length) (hi31:i.val  ≤  2 ^ 31) (hxl:xl.val  ≤  258) (hxd:xd.val  ≤  32768) :
    slot.Z208_loop1 s mp mb p0 lit lc dc cost ch cl i e xl xd ⦃ Y112P0! ⦄ := Y127U9! slot.Z208_loop1 slot.Z208_loop1.body
@[local step]
theorem u354 (s:I) (mp mb) (p0 pe:R) (lit lc dc) (cost ch)
    (hpe:pe.val  ≤  2 ^ 31) :
    slot.Z208 s mp mb p0 pe lit lc dc cost ch ⦃ Y112P0! ⦄ := Y127U1! slot.Z208
@[local step]
theorem u355 (lf zf b) :
    slot.Z190_loop0_loop0 lf zf b ⦃ Y112P0! ⦄ := Y127U10! slot.Z190_loop0_loop0 slot.Z190_loop0_loop0.body
@[local step]
theorem u356 (df zd b) :
    slot.Z190_loop0_loop1 df zd b ⦃ Y112P0! ⦄ := Y127U11! slot.Z190_loop0_loop1 slot.Z190_loop0_loop1.body
@[local step]
theorem u357 (s:I) (mp mb) (pe:R) (lit lc dc cost ch lf df zf zd) (sb st a:R)
    (hpe:pe.val  ≤  2 ^ 30) (hps:pe.val  ≤  s.length) (hsb:sb.val  ≤  a.val) (hst:st.val  ≤  a.val)
    (ha:a.val  ≤  pe.val + slot.Z8.val * slot.Z3.val) :
    slot.Z190_loop0 s mp mb pe lit lc dc cost ch lf df zf zd sb st a ⦃ Y112P0! ⦄ := Y127U12! slot.Z190_loop0 slot.Z8.val slot.Z3.val slot.Z190_loop0.body
@[local step]
theorem u358 (lf zf b) :
    slot.Z190_loop1 lf zf b ⦃ Y112P0! ⦄ := Y127U13! slot.Z190_loop1 slot.Z190_loop1.body
@[local step]
theorem u359 (df zd b) :
    slot.Z190_loop2 df zd b ⦃ Y112P0! ⦄ := Y127U14! slot.Z190_loop2 slot.Z190_loop2.body
@[local step]
theorem u360 (s:I) (mp mb) (p0 pe:R) (lit lc dc cost ch lf df)
    (hpe:pe.val  ≤  2 ^ 30) (hps:pe.val  ≤  s.length) (hp0:p0.val  ≤  pe.val) :
    slot.Z190 s mp mb p0 pe lit lc dc cost ch lf df ⦃ Y112P0! ⦄ := by
  have hseg := Submission.EA.A_SEG_bounds
  rw [slot.Z190]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac
@[local step]
theorem u361 (dst a b k) :
    slot.Z177_loop0 dst a b k ⦃ Y112P0! ⦄ := by
  rw [slot.Z177_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (dst_, k_) => 512 - k_.val)
    (inv := fun _ => True)
  · rintro ⟨dst_, k_⟩ _
    simp only [slot.Z177_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem u362 (dd x y k) :
    slot.Z177_loop1 dd x y k ⦃ Y112P0! ⦄ := by
  rw [slot.Z177_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (dd_, k_) => 32 - k_.val)
    (inv := fun _ => True)
  · rintro ⟨dd_, k_⟩ _
    simp only [slot.Z177_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem u363 (dst a b dd x y) :
    slot.Z177 dst a b dd x y ⦃ Y112P0! ⦄ := Y127U1! slot.Z177
@[local step]
theorem u364 (x) :
    slot.Z187 x ⦃ fun r => r.val  ≤  2048 ⦄ := by
  rw [slot.Z187]
  have hlz := u326 x
  have htab := EA.u286
  step*
  repeat' (split <;> step*)
  all_goals try (have := Submission.EA.LeAll_get htab i3.val (by scalar_tac))
  all_goals scalar_tac
@[local step]
theorem u365 (f:W) (g:W) (hg:g.val  ≤  65536) :
    slot.Z196 f g ⦃ fun r => r.val  ≤  1152 ⦄ := Y127U1! slot.Z196
@[local step]
theorem u366 (slt:R) :
    slot.Z178 slt ⦃ fun r => r.val  ≤  slt.val / 2 ⦄ := Y127U1! slot.Z178
@[local step]
theorem u367 (slt) :
    slot.Z185 slt ⦃ fun r => r.val  ≤  5 ⦄ := Y127U1! slot.Z185
@[local step]
theorem u368 (lf tl i) :
    slot.Z191_loop0 lf tl i ⦃ Y112P0! ⦄ := by
  rw [slot.Z191_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (tl_, i_) => 286 - i_.val)
    (inv := fun _ => True)
  · rintro ⟨tl_, i_⟩ _
    simp only [slot.Z191_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem u369 (df i td) :
    slot.Z191_loop1 df i td ⦃ Y112P0! ⦄ := Y127U15! slot.Z191_loop1 slot.Z191_loop1.body
@[local step]
theorem u370 (lf lit i) (gl:W) (hgl:gl.val  ≤  65536) :
    slot.Z191_loop2 lf lit i gl ⦃ Y112P0! ⦄ := by
  rw [slot.Z191_loop2]
  apply Std.loop.spec_decr_nat
    (measure := fun (lit_, i_) => 256 - i_.val)
    (inv := fun _ => True)
  · rintro ⟨lit_, i_⟩ _
    simp only [slot.Z191_loop2.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem u371 (lf lc i) (gl:W) (hgl:gl.val  ≤  65536) :
    slot.Z191_loop3 lf lc i gl ⦃ Y112P0! ⦄ := by
  rw [slot.Z191_loop3]
  apply Std.loop.spec_decr_nat
    (measure := fun (lc_, i_) => 258 + 1 - i_.val)
    (inv := fun _ => True)
  · rintro ⟨lc_, i_⟩ _
    simp only [slot.Z191_loop3.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem u372 (df dc) (i:R) (gd:W) (hgd:gd.val  ≤  65536) :
    slot.Z191_loop4 df dc i gd ⦃ Y112P0! ⦄ := by
  rw [slot.Z191_loop4]
  apply Std.loop.spec_decr_nat
    (measure := fun (dc_, i_) => 30 - i_.val)
    (inv := fun _ => True)
  · rintro ⟨dc_, i_⟩ _
    simp only [slot.Z191_loop4.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem u373 (lf df lit lc dc) :
    slot.Z191 lf df lit lc dc ⦃ Y112P0! ⦄ := Y127U1! slot.Z191
@[local step]
theorem u374 (s:I) (lf) (m i:R) (hm:m.val  ≤  s.length) (hm2:m.val  ≤  65536)
    (hlf:EA.u15 lf.val i.val) :
    slot.Z182_loop0 s lf m i ⦃ Y112P0! ⦄ := by
  rw [slot.Z182_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, i_) => m.val - i_.val)
    (inv := fun (lf_, i_) => EA.u15 lf_.val i_.val)
  · rintro ⟨lf_, i_⟩ hlf_
    simp only [slot.Z182_loop0.body]
    step*
    all_goals try (have := Submission.EA.LeAll_get hlf_ i2.val (by scalar_tac))
    all_goals try scalar_tac
    refine ⟨?_, by scalar_tac⟩
    rw [show i5.val = i_.val + 1 by scalar_tac, a_post, Array.set_val_eq]
    exact EA.u19 hlf_ _ _ (by scalar_tac)
  · exact hlf
@[local step]
theorem u375 (lf i) :
    slot.Z182_loop1 lf i ⦃ Y112P0! ⦄ := by
  rw [slot.Z182_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (lf_, i_) => 29 - i_.val)
    (inv := fun _ => True)
  · rintro ⟨lf_, i_⟩ _
    simp only [slot.Z182_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem u376 (df i) :
    slot.Z182_loop2 df i ⦃ Y112P0! ⦄ := by
  rw [slot.Z182_loop2]
  apply Std.loop.spec_decr_nat
    (measure := fun (df_, i_) => 30 - i_.val)
    (inv := fun _ => True)
  · rintro ⟨df_, i_⟩ _
    simp only [slot.Z182_loop2.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem u377 (s lit lc dc) :
    slot.Z182 s lit lc dc ⦃ Y112P0! ⦄ := by
  rw [slot.Z182]
  step*
  repeat' (split <;> step*)
  all_goals exact EA.u38 _ _ _ (by simp)
@[local step]
theorem u378 (sym m) (len:C 512#usize) (kraft q) (hlen:EA.u15 len.val 15) :
    slot.Z184_loop sym m len kraft q ⦃ fun r => EA.u15 r.val 15 ⦄ := by
  rw [slot.Z184_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun ((len_:C 512#usize), _, (q_:R)) =>
      (512 - q_.val) * 16 + (15 - (len_.val[(sym.val[q_.val]!).val % 512]!).val))
    (inv := fun (len_, _, _) => EA.u15 len_.val 15)
  · rintro ⟨len_, kraft_, q_⟩ hlen_
    dsimp only at hlen_
    simp only [slot.Z184_loop.body]
    step*
    · -- one code gets one bit longer: the second component of the measure drops
      have hq:(sym.val[q_.val]!).val % 512 = s2.val := by
        rw [getElem!_pos sym.val q_.val (by scalar_tac), ← i_post];scalar_tac
      have ha:a.val[s2.val]! = i5 := by
        rw [a_post, Array.set_val_eq, getElem!_pos _ _ (by simp;scalar_tac), List.getElem_set_self]
      have hl:len_.val[s2.val]! = i2 := by
        rw [getElem!_pos _ _ (by scalar_tac), ← i2_post]
      refine ⟨?_, ?_⟩
      · rw [a_post, Array.set_val_eq];exact EA.u17 hlen_ _ _ (by scalar_tac)
      · rw [hq, ha, hl];scalar_tac
    · -- the next symbol: the first component drops
      exact ⟨hlen_, by scalar_tac⟩
  · exact hlen
@[local step]
theorem u379 (sym m) (len:C 512#usize) (kraft0) (hlen:EA.u15 len.val 15) :
    slot.Z184 sym m len kraft0 ⦃ fun r => EA.u15 r.val 15 ⦄ := by
  unfold slot.Z184
  step*
@[local step]
theorem u380 (w a) (b:R) (m k) (hb:b.val  ≤  4096) :
    slot.Z188 w a b m k ⦃ fun r => r.2.1.val  ≤  a.val + 1  ∧  r.2.2.val  ≤  b.val + 1 ⦄ := Y127U1! slot.Z188
@[local step]
theorem u381 (sym freq fv) (j:R) (hj:j.val < 512) :
    slot.Z195_loop sym freq fv j ⦃ fun r => r.2.val < 512 ⦄ := by
  rw [slot.Z195_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, j_) => j_.val)
    (inv := fun (_, j_) => j_.val < 512)
  · rintro ⟨sym_, j_⟩ hinv
    simp only [slot.Z195_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact hj
@[local step]
theorem u382 (sym freq m v) :
    slot.Z195 sym freq m v ⦃ Y112P0! ⦄ := Y127U1! slot.Z195
@[local step]
theorem u383 (freq n) (len:C 512#usize) (sym) (m i:R)
    (hm:m.val  ≤  i.val) (hi:i.val  ≤  512) (hlen:EA.u15 len.val 15) :
    slot.Z183_loop0 freq n len sym m i ⦃ fun r => r.2.2.val  ≤  512  ∧  EA.u15 r.1.val 15 ⦄ := by
  rw [slot.Z183_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, i_) => 512 - i_.val)
    (inv := fun (len_, _, m_, i_) => m_.val  ≤  i_.val  ∧  i_.val  ≤  512  ∧  EA.u15 len_.val 15)
  · rintro ⟨len_, sym_, m_, i_⟩ ⟨hm_, hi_, hlen_⟩
    simp only [slot.Z183_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals
      refine ⟨by scalar_tac, by scalar_tac, ?_, by scalar_tac⟩
      rw [a_post, Array.set_val_eq];exact EA.u17 hlen_ _ _ (by scalar_tac)
  · exact ⟨hm, hi, hlen⟩
@[local step]
theorem u384 (freq sym m i w) :
    slot.Z183_loop1 freq sym m i w ⦃ Y112P0! ⦄ := by
  rw [slot.Z183_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (i_, w_) => m.val - i_.val)
    (inv := fun _ => True)
  · rintro ⟨i_, w_⟩ _
    simp only [slot.Z183_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem u385 (m:R) (w par) (a b k:R) (hm:m.val  ≤  512)
    (ha:a.val  ≤  2 * k.val) (hb:b.val  ≤  2 * k.val) (hk:k.val  ≤  1024) :
    slot.Z183_loop2 m w par a b k ⦃ fun r => r.2.val  ≤  1024 ⦄ := by
  rw [slot.Z183_loop2]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, k_) => 1024 - k_.val)
    (inv := fun (_, _, a_, b_, k_) => a_.val  ≤  2 * k_.val  ∧  b_.val  ≤  2 * k_.val  ∧  k_.val  ≤  1024)
  · rintro ⟨w_, par_, a_, b_, k_⟩ ⟨ha_, hb_, hk_⟩
    simp only [slot.Z183_loop2.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact ⟨ha, hb, hk⟩
@[local step]
theorem u386 (par d j) :
    slot.Z183_loop3 par d j ⦃ Y112P0! ⦄ := by
  rw [slot.Z183_loop3]
  apply Std.loop.spec_decr_nat
    (measure := fun (d_, j_) => j_.val)
    (inv := fun _ => True)
  · rintro ⟨d_, j_⟩ _
    simp only [slot.Z183_loop3.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem u387 (len:C 512#usize) (sym m i d kraft) (hlen:EA.u15 len.val 15) :
    slot.Z183_loop4 len sym m i d kraft ⦃ fun r => EA.u15 r.1.val 15 ⦄ := by
  rw [slot.Z183_loop4]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, i_, _) => m.val - i_.val)
    (inv := fun (len_, _, _) => EA.u15 len_.val 15)
  · rintro ⟨len_, i_, kraft_⟩ hlen_
    dsimp only at hlen_
    simp only [slot.Z183_loop4.body]
    step*
    repeat' (split <;> step*)
    all_goals try scalar_tac
    all_goals
      refine ⟨?_, by scalar_tac⟩
      rw [a_post, Array.set_val_eq];exact EA.u17 hlen_ _ _ (by scalar_tac)
  · exact hlen
@[local step]
theorem u388 (freq n) (len:C 512#usize) (hlen:EA.u15 len.val 15) :
    slot.Z183 freq n len ⦃ fun r => EA.u15 r.val 15 ⦄ := by
  rw [slot.Z183]
  step*
  repeat' (split <;> step*)
  all_goals try scalar_tac
  all_goals apply EA.u289 (by assumption) (by assumption) (by scalar_tac)
@[local step]
theorem u389 (lf0 lf z) :
    slot.Z192_loop0 lf0 lf z ⦃ Y112P0! ⦄ := Y127U16! slot.Z192_loop0 slot.Z192_loop0.body
@[local step]
theorem u390 (df dd i) :
    slot.Z192_loop1 df dd i ⦃ Y112P0! ⦄ := Y127U17! slot.Z192_loop1 slot.Z192_loop1.body
@[local step]
theorem u391 (lf i tl) :
    slot.Z192_loop2 lf i tl ⦃ Y112P0! ⦄ := Y127U18! slot.Z192_loop2 slot.Z192_loop2.body
@[local step]
theorem u392 (df i td) :
    slot.Z192_loop3 df i td ⦃ Y112P0! ⦄ := Y127U15! slot.Z192_loop3 slot.Z192_loop3.body
@[local step]
theorem u393 (lit) (hl:C 512#usize) (i) (ul:W) (hhl:EA.u15 hl.val 15) :
    slot.Z192_loop4 lit hl i ul ⦃ Y112P0! ⦄ := Y127U19! slot.Z192_loop4 slot.Z192_loop4.body
@[local step]
theorem u394 (lc) (hl:C 512#usize) (i) (ul:W) (hhl:EA.u15 hl.val 15) (hul:ul.val  ≤  1152) :
    slot.Z192_loop5 lc hl i ul ⦃ Y112P0! ⦄ := Y127U20! slot.Z192_loop5 slot.Z192_loop5.body
@[local step]
theorem u395 (dc) (i:R) (hd:C 512#usize) (ud:W) (hhd:EA.u15 hd.val 15) (hud:ud.val  ≤  1152) :
    slot.Z192_loop6 dc i hd ud ⦃ Y112P0! ⦄ := Y127U21! slot.Z192_loop6 slot.Z192_loop6.body
@[local step]
theorem u396 (lf0 df lit lc dc) :
    slot.Z192 lf0 df lit lc dc ⦃ Y112P0! ⦄ := by
  rw [slot.Z192]
  step*
  all_goals exact EA.u38 _ _ _ (by simp)
@[local step]
theorem u397 (s:I) (a b lim:R) (k)
    (ha:a.val + lim.val  ≤  s.length) (hb:b.val + lim.val  ≤  s.length) :
    slot.Z193_loop s a b lim k ⦃ Y112P0! ⦄ := Y127U22! slot.Z193_loop slot.Z193_loop.body
@[local step]
theorem u398 (s:I) (a b lim:R)
    (ha:a.val + lim.val  ≤  s.length) (hb:b.val + lim.val  ≤  s.length) :
    slot.Z193 s a b lim ⦃ Y112P0! ⦄ := Y127U1! slot.Z193
@[local step]
theorem u399 (s) (i:R) (hi:i.val  ≤  2 ^ 31) :
    slot.Z199 s i ⦃ Y112P0! ⦄ := Y127U1! slot.Z199
@[local step]
theorem u400 (s) (a b:R) (ha:a.val  ≤  2 ^ 31) (hb:b.val  ≤  2 ^ 31) :
    slot.Z200 s a b ⦃ Y112P0! ⦄ := Y127U1! slot.Z200
@[local step]
theorem u401 (s) (p q k:R) (w) (hp:p.val  ≤  2 ^ 30) (hq:q.val  ≤  2 ^ 30) (hk:k.val  ≤  258) :
    slot.Z189_loop s p q k w ⦃ fun r => r.1.val  ≤  258 ⦄ := by
  rw [slot.Z189_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (k_, _) => 258 - k_.val)
    (inv := fun (k_, _) => k_.val  ≤  258)
  · rintro ⟨k_, ⟨w0, w1⟩⟩ hinv
    simp only [slot.Z189_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact hk
@[local step]
theorem u402 (s) (p q k:R) (hp:p.val  ≤  2 ^ 30) (hq:q.val  ≤  2 ^ 30) (hk:k.val  ≤  258) :
    slot.Z189 s p q k ⦃ fun r => r.1.val  ≤  258 ⦄ := Y127U1! slot.Z189
@[local step]
theorem u403 (s:I) (kid) (pos depth oldest:R) (mb) (cur best lo_at hi_at lo_len hi_len steps:R)
    (hpos:pos.val + 266  ≤  s.length) (hn26:s.length < 67108864) (hlo:lo_len.val  ≤  258) (hhi:hi_len.val  ≤  258) (hbest:2  ≤  best.val) :
    slot.Z197_loop s kid pos depth mb oldest cur best lo_at hi_at lo_len hi_len steps ⦃ Y112P0! ⦄ := by
  rw [slot.Z197_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, _, _, _, _, steps_) => depth.val - steps_.val)
    (inv := fun (_, _, _, best_, _, _, lo_len_, hi_len_, _) => lo_len_.val  ≤  258  ∧  hi_len_.val  ≤  258  ∧  2  ≤  best_.val)
  · rintro ⟨kid_, mb_, cur_, best_, lo_at_, hi_at_, lo_len_, hi_len_, steps_⟩ ⟨hlo_, hhi_, hbest_⟩
    simp only [slot.Z197_loop.body, Submission.EA.d1_ite_ok]
    step*
    · split <;> omega
    apply WP.spec_bind (Pₘ := fun (x:alloc.vec.Vec W  ×  R) => 2  ≤  x.2.val)
    · split
      · step*
        repeat' (split <;> step*)
        all_goals scalar_tac
      · step*
    rintro ⟨mb1, best1⟩ hb1
    step*
    apply WP.spec_bind (Pₘ := fun (x:Std.Array W 65536#usize  ×  R  ×  R  ×  R  × 
        R  ×  R) => x.2.2.2.2.1.val  ≤  258  ∧  x.2.2.2.2.2.val  ≤  258)
    · repeat' (split <;> step*)
      all_goals scalar_tac
    rintro ⟨kid1, cur1, lo_at1, hi_at1, lo_len2, hi_len1⟩ ⟨hl2, hh1⟩
    step*
    all_goals scalar_tac
  · exact ⟨hlo, hhi, hbest⟩
@[local step]
theorem u404 (s:I) (head kid h3 rct) (pos:R) (pre depth mb) (hpos:pos.val + 266  ≤  s.length)
    (hn26:s.length < 67108864) :
    slot.Z197 s head kid h3 rct pos pre depth mb ⦃ Y112P0! ⦄ := Y127U23! slot.Z197
set_option maxHeartbeats 4000000 in
@[local step]
theorem u405 (i:W) (s:I) (mp:alloc.vec.Vec W) (mb depth) (skip n:R) (head kid h3 rct) (i1 cl cd:R) (nq nt nh n3 nr nc)
    (hn:n.val = s.length) (hn26:s.length < 67108864) (hi:i.val < 32) (hskip:3  ≤  skip.val)
    (hmp:mp.length  ≤  i1.val + 1) (hcd:1  ≤  cd.val) :
    slot.Z181_loop i s mp mb depth skip n head kid h3 rct i1 cl cd nq nt nh n3 nr nc ⦃ Y112P0! ⦄ := Y127U24! slot.Z181_loop slot.Z181_loop.body
@[local step]
theorem u406 (s:I) (mp:alloc.vec.Vec W) (mb depth) (skip:R)
    (hn26:s.length < 67108864) (hskip:3  ≤  skip.val) (hmp:mp.length = 0) :
    slot.Z181 s mp mb depth skip ⦃ Y112P0! ⦄ := Y127U25! slot.Z181
@[local step]
theorem u407 (n:R) (cost) (i:R) (hn:n.val < 67108864) (hc:cost.length = i.val) :
    slot.Z180_loop0 n cost i ⦃ Y112P0! ⦄ := Y127U26! slot.Z180_loop0 slot.Z180_loop0.body
set_option aeneas.step.nla true in
@[local step]
theorem u408 (input:I) (ch) (n:R) (mp mb cost lit lc dc lf df bl bd sl sd) (rot p0 need passes sampled pe k p1 t:R)
    (hn:n.val = input.length) (hn26:n.val < 67108864) (hp0:p0.val < n.val) (hpe:p0.val  ≤  pe.val  ∧  pe.val  ≤  n.val)
    (hpe':pe.val = n.val  ∨  p0.val + slot.Z1.val  ≤  pe.val)
    (hneed:need.val  ≤  65536) (ht:t.val  ≤  need.val) (hp1:p0.val  ≤  p1.val  ∧  p1.val  ≤  p0.val + 511 * t.val) :
    slot.Z180_loop1_loop0 input ch n mp mb cost lit lc dc lf df bl bd sl sd rot p0 need passes sampled pe k p1 t ⦃ fun r =>
      r.2.2.2.2.2.2.2.2.2.2.val  ≤  need.val  ∧  p0.val  ≤  r.2.2.2.2.2.2.2.2.2.1.val  ∧ 
      r.2.2.2.2.2.2.2.2.2.1.val  ≤  p0.val + 511 * r.2.2.2.2.2.2.2.2.2.2.val ⦄ := by
  have hbt := Submission.EA.A_BLOCK_bounds
  have hseg := Submission.EA.A_SEG_bounds
  rw [slot.Z180_loop1_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, _, _, _, _, _, _, k_, _, _) => passes.val - k_.val)
    (inv := fun (_, _, _, _, _, _, _, _, _, (pe_:R), _, (p1_:R), (t_:R)) =>
      p0.val  ≤  pe_.val  ∧  pe_.val  ≤  n.val  ∧  (pe_.val = n.val  ∨  p0.val + slot.Z1.val  ≤  pe_.val)  ∧ 
      t_.val  ≤  need.val  ∧  p0.val  ≤  p1_.val  ∧  p1_.val  ≤  p0.val + 511 * t_.val)
  · rintro ⟨ch_, cost_, lit_, lc_, dc_, lf_, df_, sl_, sd_, pe_, k_, p1_, t_⟩ ⟨hpe0, hpe1, hpe2, ht_, hp10, hp11⟩
    simp only [slot.Z180_loop1_loop0.body]
    step*
    apply WP.spec_bind (Pₘ := fun (x:alloc.vec.Vec W  ×  alloc.vec.Vec W  ×  Std.Array W 512#usize  × 
        Std.Array W 32#usize  ×  R  ×  R  ×  R) =>
        p0.val  ≤  x.2.2.2.2.1.val  ∧  x.2.2.2.2.1.val  ≤  n.val  ∧ 
        (x.2.2.2.2.1.val = n.val  ∨  p0.val + slot.Z1.val  ≤  x.2.2.2.2.1.val)  ∧ 
        x.2.2.2.2.2.2.val  ≤  need.val  ∧  p0.val  ≤  x.2.2.2.2.2.1.val  ∧  x.2.2.2.2.2.1.val  ≤  p0.val + 511 * x.2.2.2.2.2.2.val)
    · split
      · step*
        · -- a sampled pass: the window end scales with the sampled bytes per token
          cases ‹R  ×  R›
          step*
          apply WP.spec_bind (Pₘ := fun (z:alloc.vec.Vec W  ×  alloc.vec.Vec W  ×  Std.Array W 512#usize  × 
              Std.Array W 32#usize  ×  R) => p0.val  ≤  z.2.2.2.2.val  ∧  z.2.2.2.2.val  ≤  n.val  ∧ 
              (z.2.2.2.2.val = n.val  ∨  p0.val + slot.Z1.val  ≤  z.2.2.2.2.val))
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
          apply WP.spec_bind (Pₘ := fun (_:alloc.vec.Vec W  ×  alloc.vec.Vec W) => True)
          · split <;> step*
          rintro ⟨ch2, cost2⟩ _
          step*
          cases ‹R  ×  R›
          step*
          apply WP.spec_bind (Pₘ := fun (z:Std.Array W 512#usize  ×  Std.Array W 32#usize  ×  R) =>
              p0.val  ≤  z.2.2.val  ∧  z.2.2.val  ≤  n.val  ∧  (z.2.2.val = n.val  ∨  p0.val + slot.Z1.val  ≤  z.2.2.val))
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
          apply WP.spec_bind (Pₘ := fun (_:alloc.vec.Vec W  ×  alloc.vec.Vec W) => True)
          · split <;> step*
          rintro ⟨ch2, cost2⟩ _
          step*
          cases ‹R  ×  R›
          step*
          apply WP.spec_bind (Pₘ := fun (z:Std.Array W 512#usize  ×  Std.Array W 32#usize  ×  R) =>
              p0.val  ≤  z.2.2.val  ∧  z.2.2.val  ≤  n.val  ∧  (z.2.2.val = n.val  ∨  p0.val + slot.Z1.val  ≤  z.2.2.val))
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
          apply WP.spec_bind (Pₘ := fun (_:alloc.vec.Vec W  ×  alloc.vec.Vec W) => True)
          · split <;> step*
          rintro ⟨ch2, cost2⟩ _
          step*
          cases ‹R  ×  R›
          step*
          apply WP.spec_bind (Pₘ := fun (z:Std.Array W 512#usize  ×  Std.Array W 32#usize  ×  R) =>
              p0.val  ≤  z.2.2.val  ∧  z.2.2.val  ≤  n.val  ∧  (z.2.2.val = n.val  ∨  p0.val + slot.Z1.val  ≤  z.2.2.val))
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
theorem u409 (input:I) (ch first_passes fspass passes_k) (n:R) (mp mb cost lit lc dc lf df bl bd sl sd zl zd) (rot spn p0 used bpt:R)
    (hn:n.val = input.length) (hn26:n.val < 67108864) (hused:used.val < slot.Z45.val) (hbpt:256  ≤  bpt.val  ∧  bpt.val  ≤  65536) :
    slot.Z180_loop1 input ch first_passes fspass passes_k n mp mb cost lit lc dc lf df bl bd sl sd zl zd rot spn p0 used bpt ⦃ Y112P0! ⦄ := Y127U27! slot.Z180_loop1 slot.Z45.val slot.Z180_loop1.body slot.Z1.val
@[local step]
theorem u410 (input:I) (ch) (depth skip first_passes fspass passes_k spass:R)
    (hn:input.length < 67108864) (h1:depth.val  ≤  65536) (h2:skip.val  ≤  65536) (h2':3  ≤  skip.val)
    (h3:first_passes.val  ≤  65536) (h4:fspass.val  ≤  65536) (h5:passes_k.val  ≤  65536) (h6:spass.val  ≤  65536) :
    slot.Z180 input ch depth skip first_passes fspass passes_k spass ⦃ Y112P0! ⦄ := by
  have hbt := Submission.EA.A_BLOCK_bounds
  rw [slot.Z180]
  step*
  all_goals rfl

@[local step]
theorem u411:slot.Z66 ⦃ Y112P0! ⦄ := by
  unfold slot.Z66
  have h := EA.u4
  step*
theorem u412 {α:Type} (v:alloc.vec.Vec α) (i:R) :
    alloc.vec.Vec.index_mut_usize v i =
      (do let x ← alloc.vec.Vec.index_usize v i;ok (x, alloc.vec.Vec.set v i)) := by
  unfold alloc.vec.Vec.index_mut_usize
  cases alloc.vec.Vec.index_usize v i <;> rfl
theorem u413 (x:W):x.val >>> 15 < 131072 := by
  rw [Nat.shiftRight_eq_div_pow]
  have:x.val < 2 ^ 32 := by scalar_tac
  omega
theorem u414 {n:R} (a:Std.Array W n) (j:R) (B:Nat)
    (h:EA.u15 a.val B) (hj:j.val < a.length) :
    a.index_usize j ⦃ fun x => x = a.val[j.val]  ∧  x.val  ≤  B ⦄ := by
  have := Std.Array.index_usize_spec a j hj
  apply WP.spec_mono this
  intro x hx
  exact ⟨hx, hx ▸ Submission.EA.LeAll_get h j.val (by simpa using hj)⟩
theorem u415 {n:R} (a:Std.Array W n) (j:R) (x:W)
    (B:Nat) (h:EA.u15 a.val B) (hx:x.val < B + 1) (hj:j.val < a.length) :
    a.update j x ⦃ fun r => r = a.set j x  ∧  EA.u15 r.val B ⦄ := by
  have := Std.Array.update_spec a j x hj
  apply WP.spec_mono this
  intro r hr
  exact ⟨hr, by rw [hr, Std.Array.set_val_eq];exact EA.u17 h _ _ (by omega)⟩
theorem u416 {α:Type} {n:R} (v:Std.Array α n) (i:R)
    (hbound:i.val < v.length) :
    v.index_mut_usize i ⦃ x back => back = Std.Array.set v i ⦄ := by
  have := Std.Array.index_mut_usize_spec v i hbound
  apply WP.spec_mono this
  rintro ⟨x, back⟩ ⟨_, h⟩
  exact h
theorem u417 (l:V):EA.u15 l 4294967295 := fun j hj => by scalar_tac
theorem u418 (x y:R) (h:y.val  ≤  x.val) :
    (core.num.Usize.wrapping_sub x y).val = x.val - y.val := by
  rw [core.num.Usize.wrapping_sub_val_eq]
  have hx:x.val < UScalar.size .Usize := by
    have := x.hBounds;simp only [UScalar.size];exact this
  rw [show x.val + (UScalar.size .Usize - y.val) = (x.val - y.val) + UScalar.size .Usize by omega,
    Nat.add_mod_right, Nat.mod_eq_of_lt (by omega)]
theorem u419 (x:W):x.val >>> 2 < 1073741824 := by
  rw [Nat.shiftRight_eq_div_pow]
  have:x.val < 2 ^ 32 := by scalar_tac
  omega
def u420 (l:V) (base K:Nat):Prop :=
  ∀ z, z < slot.Z64.val  →  ∀ x, l[base + z]? = some x  →  x.val  ≤  K
def u421 (l:V) (base n:Nat):Prop :=
  ∀ z, z < n  →  ∀ x, l[base + z]? = some x  →  x.val = 0
theorem u422 {l:V} {base K K':Nat} (h:u420 l base K) (hK:K  ≤  K') :
    u420 l base K' := fun z hz x hx => le_trans (h z hz x hx) hK
theorem u423 {l:V} {base K base' K':Nat} (h:u420 l base K)
    (hh:base = base'  ∧  K  ≤  K'):u420 l base' K' := by
  obtain ⟨rfl, hK⟩ := hh;exact u422 h hK
theorem u424 {l:V} {base K:Nat} (h:u420 l base K) {idx:Nat}
    {x:W} (h1:base  ≤  idx) (h2:idx < base + slot.Z64.val) (hl:idx < l.length)
    (hx:x = l[idx]):x.val  ≤  K := by
  have hx':l[base + (idx - base)]? = some x := by
    rw [show base + (idx - base) = idx by omega, hx];exact List.getElem?_eq_getElem hl
  exact h (idx - base) (by omega) _ hx'
theorem u425 {l:V} {base K K':Nat} (h:u420 l base K) (idx:Nat)
    (v:W) (hv:v.val  ≤  K') (hK:K  ≤  K'):u420 (l.set idx v) base K' := by
  intro z hz x hx
  rw [List.getElem?_set] at hx
  split at hx
  · split at hx
    · cases hx;exact hv
    · cases hx
  · exact le_trans (h z hz x hx) hK
theorem u426 (l:V) (base:Nat):u421 l base 0 :=
  fun z hz => absurd hz (Nat.not_lt_zero z)
theorem u427 {l:V} {base n:Nat} (h:u421 l base n) (idx:Nat)
    (hidx:idx = base + n):u421 (l.set idx 0#u32) base (n + 1) := by
  intro z hz x hx
  rw [List.getElem?_set] at hx
  split at hx
  · split at hx
    · cases hx;rfl
    · cases hx
  · exact h z (by omega) x hx
theorem u428 {l:V} {base n:Nat} (h:u421 l base n)
    (hlen:l.length = base + n):u421 (l ++ [0#u32]) base (n + 1) := by
  intro z hz x hx
  by_cases hzn:z < n
  · rw [List.getElem?_append_left (by omega)] at hx
    exact h z hzn x hx
  · have:base + z = l.length := by omega
    rw [this, List.getElem?_concat_length] at hx
    cases hx;rfl
theorem u429 {l:V} {base n:Nat} (h:u421 l base n)
    (hn:slot.Z64.val  ≤  n):u420 l base 0 :=
  fun z hz x hx => le_of_eq (h z (by omega) x hx)
def u430 (n:Nat) (bf bs:alloc.vec.Vec W) (nb pos t:Nat):Prop :=
  (pos  ≤  n  ∧  t  ≤  pos  ∧  t  ≤  nb * slot.Z45.val  ∧  nb * slot.Z45.val < t + slot.Z45.val  ∧ 
    nb * slot.Z64.val  ≤  bf.length  ∧  nb  ≤  bs.length)  ∧ 
    (0 < nb  →  u420 bf.val ((nb - 1) * slot.Z64.val) pos)
theorem engB_TPL.u431 {n:Nat} {bf bs:alloc.vec.Vec W} {nb pos t:Nat}
    (h1:pos  ≤  n  ∧  t  ≤  pos  ∧  t  ≤  nb * slot.Z45.val  ∧ 
      nb * slot.Z45.val < t + slot.Z45.val  ∧  nb * slot.Z64.val  ≤  bf.length  ∧ 
      nb  ≤  bs.length)
    (h2:0 < nb  →  u420 bf.val ((nb - 1) * slot.Z64.val) pos):u430 n bf bs nb pos t :=
  ⟨h1, h2⟩
def u432 (m:Nat) (bf bs:alloc.vec.Vec W) (nb inb j:Nat):Prop :=
  j  ≤  m  ∧  nb * slot.Z64.val  ≤  bf.length  ∧  nb  ≤  bs.length  ∧  (nb = 0  →  inb = slot.Z45.val)  ∧ 
    inb  ≤  slot.Z45.val  ∧  (0 < nb  →  (nb - 1) * slot.Z45.val + inb  ≤  m - j)
def u433 (m L:Nat) (bf bs:alloc.vec.Vec W) (nb inb j:Nat):Prop :=
  (L  ≤  bf.length  ∧  u432 m bf bs nb inb j)  ∧ 
    (0 < nb  →  u420 bf.val ((nb - 1) * slot.Z64.val) (m - j))
theorem engB_TSL.u434 {m L:Nat} {bf bs:alloc.vec.Vec W} {nb inb j:Nat}
    (h1:L  ≤  bf.length  ∧  j  ≤  m  ∧  nb * slot.Z64.val  ≤  bf.length  ∧  nb  ≤  bs.length  ∧ 
      (nb = 0  →  inb = slot.Z45.val)  ∧  inb  ≤  slot.Z45.val  ∧ 
      (0 < nb  →  (nb - 1) * slot.Z45.val + inb  ≤  m - j))
    (h2:0 < nb  →  u420 bf.val ((nb - 1) * slot.Z64.val) (m - j)) :
    u433 m L bf bs nb inb j :=
  ⟨⟨h1.1, h1.2⟩, h2⟩
attribute [local step] u414 u415 in
theorem u435 (t:Std.Array W 65536#usize) (lt ls rs cs cur l ll rl:R) (i L:Nat)
    (hT:EA.u15 t.val i) (hcur:cur.val  ≤  i) (hi:i < 67108864) (hcs:cs.val  ≤  65534)
    (hl:l.val  ≤  L) (hll:ll.val  ≤  L) (hrl:rl.val  ≤  L) :
    (if lt = 1#usize then do
        let i16 ← ls % slot.Z47
        let i17 ← lift (UScalar.cast UScalarTy.U32 cur)
        let a5 ← t.update i16 i17
        let ls2 ← cs + 1#usize
        let i18 ← ls2 % slot.Z47
        let i19 ← a5.index_usize i18
        let cur2 ← lift (UScalar.cast UScalarTy.Usize i19)
        ok (a5, cur2, ls2, rs, l, rl)
      else do
        let i16 ← rs % slot.Z47
        let i17 ← lift (UScalar.cast UScalarTy.U32 cur)
        let a5 ← t.update i16 i17
        let i18 ← cs % slot.Z47
        let i19 ← a5.index_usize i18
        let cur2 ← lift (UScalar.cast UScalarTy.Usize i19)
        ok (a5, cur2, ls, cs, ll, l)) ⦃
      fun (x:Std.Array W 65536#usize  ×  R  ×  R  ×  R  ×  R  ×  R) =>
      EA.u15 x.1.val i  ∧  x.2.1.val  ≤  i  ∧  x.2.2.2.2.1.val  ≤  L  ∧  x.2.2.2.2.2.val  ≤  L ⦄ := by
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
def u436 (i:Nat) (tree:Std.Array W 65536#usize) (pn:Std.Array W 32#usize)
    (step cur ll rl fuel nr bl bd:Nat):Prop :=
  EA.u15 tree.val i  ∧  EA.u15 pn.val i  ∧  cur  ≤  i  ∧  ll  ≤  2 ^ 30  ∧  rl  ≤  2 ^ 30  ∧  step + fuel  ≤  2 ^ 20  ∧ 
    nr  ≤  slot.Z39.val  ∧  bl  ≤  2 ^ 30  ∧  bd  ≤  i
theorem engB_DInv.u437 {i:Nat} {tree:Std.Array W 65536#usize} {pn:Std.Array W 32#usize}
    {step cur ll rl fuel nr bl bd:Nat} (h1:EA.u15 tree.val i) (h2:EA.u15 pn.val i)
    (h3:cur  ≤  i  ∧  ll  ≤  2 ^ 30  ∧  rl  ≤  2 ^ 30  ∧  step + fuel  ≤  2 ^ 20  ∧  nr  ≤  slot.Z39.val  ∧ 
      bl  ≤  2 ^ 30  ∧  bd  ≤  i) :
    u436 i tree pn step cur ll rl fuel nr bl bd :=
  ⟨h1, h2, h3⟩
abbrev u438 := Std.Array W 65536#usize  ×  Std.Array W 32#usize  ×  Std.Array W 32#usize  × 
  Std.Array W 32#usize  ×  R  ×  R  ×  R  ×  R  ×  R  ×  R  ×  R  × 
  R  ×  R  ×  R  ×  R  ×  R  ×  R
abbrev u439 := Std.Array W 65536#usize  ×  Std.Array W 32#usize  ×  Std.Array W 32#usize  × 
  Std.Array W 32#usize  ×  R  ×  R  ×  R  ×  R  ×  R
def u440 (i fuel:Nat) (r:ControlFlow u438 u439):Prop :=
  match r with
  | .done y => EA.u15 y.1.val i  ∧  EA.u15 y.2.1.val i  ∧  y.2.2.2.2.2.1.val  ≤  slot.Z39.val  ∧ 
      y.2.2.2.2.2.2.2.1.val  ≤  2 ^ 30  ∧  y.2.2.2.2.2.2.2.2.val  ≤  i
  | .cont x' => u436 i x'.1 x'.2.1 x'.2.2.2.2.1.val x'.2.2.2.2.2.1.val x'.2.2.2.2.2.2.2.2.1.val
      x'.2.2.2.2.2.2.2.2.2.1.val x'.2.2.2.2.2.2.2.2.2.2.1.val x'.2.2.2.2.2.2.2.2.2.2.2.2.2.1.val
      x'.2.2.2.2.2.2.2.2.2.2.2.2.2.2.2.1.val x'.2.2.2.2.2.2.2.2.2.2.2.2.2.2.2.2.val  ∧ 
      x'.2.2.2.2.2.2.2.2.2.2.1.val < fuel
def u441 (mf:slot.Z63) (i:Nat):Prop :=
  EA.u15 mf.head.val i  ∧  EA.u15 mf.head3.val i  ∧  EA.u15 mf.tree.val i  ∧  EA.u15 mf.pn.val i  ∧ 
    mf.hl.val  ≤  2 ^ 30
theorem u442 (w:Std.Array Std.U64 32768#usize) (pf:Std.Array W 32#usize) (plen hn:R) :
    u441
      { head := Std.Array.repeat 65536#usize 0#u32, head3 := Std.Array.repeat 16384#usize 0#u32,
        tree := Std.Array.repeat 65536#usize 0#u32, w := w, pn := Std.Array.repeat 32#usize 0#u32, pf := pf,
        plen := plen, hn := hn, hl := 0#usize } (0#usize).val := Y127U28!
def u443 (b i:Nat)
    (r:ControlFlow (slot.Z63  ×  Std.Array W 32#usize  ×  alloc.vec.Vec W  ×  Std.U64  ×  R  × 
      R  ×  R) (slot.Z63  ×  Std.Array W 32#usize  ×  alloc.vec.Vec W  ×  Std.U64  × 
      R  ×  R)):Prop :=
  match r with
  | .done y => u441 y.1 b  ∧  y.2.2.2.2.2.val  ≤  33 * b  ∧  y.2.2.2.2.2.val  ≤  y.2.2.1.length
  | .cont x' => x'.2.2.2.2.2.2.val  ≤  b  ∧  x'.2.2.2.2.2.1.val  ≤  33 * x'.2.2.2.2.2.2.val  ∧ 
      x'.2.2.2.2.2.1.val  ≤  x'.2.2.1.length  ∧  u441 x'.1 x'.2.2.2.2.2.2.val  ∧ 
      b - x'.2.2.2.2.2.2.val < b - i












theorem spine_CFG_le:∀ r ∈ slot.Z70.val, ∀ x ∈ r.val, x.val  ≤  65536 := by
  unfold slot.Z70;decide
theorem spine_CFG_skip:∀ r ∈ slot.Z70.val, (r.val[0]!).val = 0  →  3  ≤  (r.val[2]!).val := by
  unfold slot.Z70;decide
@[local step]
theorem u444 (input:I) (k) (hn:input.length < 67108864) :
    slot.Z207 input k ⦃ Y112P0! ⦄ := Y127U29! slot.Z207 slot.Z70.val
@[local step]
theorem u445 (input) (k:R):slot.Z204 input k ⦃ Y112P0! ⦄ := by
  rw [slot.Z204]
  step*
theorem u446 (input:I) (out:U) (k:R)
    (hlen:input.length  ≤  out.length) :
    slot.Z203 input out k ⦃ Y112P1! ⦄ := by
  rw [slot.Z203]
  step*
  refine ⟨by assumption, by assumption, ?_⟩
  unfold LZ77.Valid
  assumption
attribute [local step] u446
@[local step]
theorem u447 (input:I) (out:U) (mode:R) (hlen:input.length  ≤  out.length):slot.Z206 input out mode ⦃ Y112P1! ⦄ := by
 rw [slot.Z206]
 step*
 all_goals repeat' (split <;> step*)
end EB
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
theorem u448 (x y:Nat):x &&& y  ≤  y := Nat.and_le_right
@[local scalar_tac x >>> y]
theorem u449 (x y:Nat):x >>> y  ≤  x := Nat.shiftRight_le x y
@[local scalar_tac System.Platform.numBits]
theorem u450:32  ≤  System.Platform.numBits := EA.u4
@[local scalar_tac core.num.U32.leading_zeros x]
theorem u451 (x:W) :
    (core.num.U32.leading_zeros x).val  ≤  32  ∧ 
      (x.val = 0  ∨  (core.num.U32.leading_zeros x).val  ≤  31) := Y127U4!
@[local scalar_tac core.num.U64.leading_zeros x]
theorem u452 (x:Std.U64):(core.num.U64.leading_zeros x).val  ≤  64 := EA.u12 x
attribute [local step] EB.u329
attribute [local step] EB.u330
attribute [local step] EB.u332
attribute [local step] EB.u333
attribute [local step] EB.u334
@[local scalar_tac core.num.Usize.saturating_add x y]
theorem u453 (x y:R) :
    (core.num.Usize.saturating_add x y).val = min Std.Usize.max (x.val + y.val) := EA.u287 x y
attribute [local step] EB.u336
attribute [local step] EB.u337
attribute [local step] EB.u338
attribute [local step] EB.u339
attribute [local step] EB.u340
attribute [local step] EB.u341
@[local step]
theorem u454 (cost:U) (lc) (i hi:R) (base best l)
    (hhi:hi.val < 512) (hc:i.val + hi.val < cost.length) :
    slot.Z252_loop cost lc i hi base l best ⦃ Y112P0! ⦄ := Y127U8! slot.Z252_loop slot.Z252_loop.body
@[local step]
theorem u455 (cost:U) (lc i lo hi base width) :
    slot.Z252 cost lc i lo hi base width ⦃ Y112P0! ⦄ := Y127U1! slot.Z252
@[local step]
theorem u456 (pe:R) (cost) (cl z:R) (hpe:pe.val  ≤  2 ^ 31) (hcl:cl.val = cost.length) :
    slot.Z211_loop0 pe cost cl z ⦃ fun r => r.length = cost.length ⦄ := Y127U5! slot.Z211_loop0 slot.Z211_loop0.body
@[local step]
theorem u457 (tail:R) (mb lc dc) (cost:alloc.vec.Vec W) (cl i:R) (bias best bd) (prev pd:R) (j top:R)
    (hcl:cl.val = cost.length) (hi:i.val  ≤  2 ^ 31) (htop:top.val  ≤  mb.length)
    (hprev:prev.val  ≤  i.val + 258) (hpv:i.val  ≤  prev.val) (hpd:pd.val  ≤  32768) (hbd:bd.val  ≤  32767) :
    slot.Z211_loop1_loop0 mb lc dc cost tail cl i bias best bd prev pd j top ⦃ Y112P6! ⦄ := Y127U7! slot.Z211_loop1_loop0 slot.Z211_loop1_loop0.body
@[local step]
theorem u458 (tail:R) (s:I) (mp mb:alloc.vec.Vec W) (p0 lit lc dc) (cost ch:alloc.vec.Vec W)
    (cl i e xl xd:R)
    (hcl:cl.val = cost.length) (hi:i.val < cl.val) (hmp:i.val < mp.length) (hs:i.val  ≤  s.length)
    (hch:i.val  ≤  ch.length) (hi31:i.val  ≤  2 ^ 31) (hxl:xl.val  ≤  258) (hxd:xd.val  ≤  32768) :
    slot.Z211_loop1 s mp mb p0 lit lc dc cost ch tail cl i e xl xd ⦃ Y112P0! ⦄ := Y127U9! slot.Z211_loop1 slot.Z211_loop1.body
@[local step]
theorem u459 (tail:R) (s:I) (mp mb) (p0 pe:R) (lit lc dc) (cost ch)
    (hpe:pe.val  ≤  2 ^ 31) :
    slot.Z211 s mp mb p0 pe lit lc dc cost ch tail ⦃ Y112P0! ⦄ := Y127U1! slot.Z211
@[local step]
theorem u460 (lf zf b) :
    slot.Z214_loop0_loop0 lf zf b ⦃ Y112P0! ⦄ := Y127U10! slot.Z214_loop0_loop0 slot.Z214_loop0_loop0.body
@[local step]
theorem u461 (df zd b) :
    slot.Z214_loop0_loop1 df zd b ⦃ Y112P0! ⦄ := Y127U11! slot.Z214_loop0_loop1 slot.Z214_loop0_loop1.body
@[local step]
theorem u462 (tail:R) (s:I) (mp mb) (pe:R) (lit lc dc cost ch lf df zf zd) (sb st a:R)
    (hpe:pe.val  ≤  2 ^ 30) (hps:pe.val  ≤  s.length) (hsb:sb.val  ≤  a.val) (hst:st.val  ≤  a.val)
    (ha:a.val  ≤  pe.val + slot.Z8.val * slot.Z3.val) :
    slot.Z214_loop0 s mp mb pe lit lc dc cost ch lf df tail zf zd sb st a ⦃ Y112P0! ⦄ := Y127U12! slot.Z214_loop0 slot.Z8.val slot.Z3.val slot.Z214_loop0.body
@[local step]
theorem u463 (lf zf b) :
    slot.Z214_loop1 lf zf b ⦃ Y112P0! ⦄ := Y127U13! slot.Z214_loop1 slot.Z214_loop1.body
@[local step]
theorem u464 (df zd b) :
    slot.Z214_loop2 df zd b ⦃ Y112P0! ⦄ := Y127U14! slot.Z214_loop2 slot.Z214_loop2.body
@[local step]
theorem u465 (tail:R) (s:I) (mp mb) (p0 pe:R) (lit lc dc cost ch lf df)
    (hpe:pe.val  ≤  2 ^ 30) (hps:pe.val  ≤  s.length) (hp0:p0.val  ≤  pe.val) :
    slot.Z214 s mp mb p0 pe lit lc dc cost ch lf df tail ⦃ Y112P0! ⦄ := by
  have hseg := Submission.EA.A_SEG_bounds
  rw [slot.Z214]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac
attribute [local step] EB.u361
attribute [local step] EB.u362
attribute [local step] EB.u363
attribute [local step] EB.u364
attribute [local step] EB.u365
attribute [local step] EB.u366
attribute [local step] EB.u367
attribute [local step] EB.u368
attribute [local step] EB.u369
attribute [local step] EB.u370
attribute [local step] EB.u371
attribute [local step] EB.u372
attribute [local step] EB.u373
attribute [local step] EB.u374
attribute [local step] EB.u375
attribute [local step] EB.u376
attribute [local step] EB.u377
attribute [local step] EB.u378
attribute [local step] EB.u379
attribute [local step] EB.u380
attribute [local step] EB.u381
attribute [local step] EB.u382
attribute [local step] EB.u383
attribute [local step] EB.u384
attribute [local step] EB.u385
attribute [local step] EB.u386
attribute [local step] EB.u387
attribute [local step] EB.u388
@[local step]
theorem u466 (lf0 lf z) :
    slot.Z215_loop0 lf0 lf z ⦃ Y112P0! ⦄ := Y127U16! slot.Z215_loop0 slot.Z215_loop0.body
@[local step]
theorem u467 (df dd i) :
    slot.Z215_loop1 df dd i ⦃ Y112P0! ⦄ := Y127U17! slot.Z215_loop1 slot.Z215_loop1.body
@[local step]
theorem u468 (lf i tl) :
    slot.Z215_loop2 lf i tl ⦃ Y112P0! ⦄ := Y127U18! slot.Z215_loop2 slot.Z215_loop2.body
@[local step]
theorem u469 (df i td) :
    slot.Z215_loop3 df i td ⦃ Y112P0! ⦄ := Y127U15! slot.Z215_loop3 slot.Z215_loop3.body
@[local step]
theorem u470 (lit) (hl:C 512#usize) (i) (ul:W) (hhl:EA.u15 hl.val 15) :
    slot.Z215_loop4 lit hl i ul ⦃ Y112P0! ⦄ := Y127U19! slot.Z215_loop4 slot.Z215_loop4.body
@[local step]
theorem u471 (lc) (hl:C 512#usize) (i) (ul:W) (hhl:EA.u15 hl.val 15) (hul:ul.val  ≤  1152) :
    slot.Z215_loop5 lc hl i ul ⦃ Y112P0! ⦄ := Y127U20! slot.Z215_loop5 slot.Z215_loop5.body
@[local step]
theorem u472 (dc) (i:R) (hd:C 512#usize) (ud:W) (hhd:EA.u15 hd.val 15) (hud:ud.val  ≤  1152) :
    slot.Z215_loop6 dc i hd ud ⦃ Y112P0! ⦄ := Y127U21! slot.Z215_loop6 slot.Z215_loop6.body
@[local step]
theorem u473 (lf0 df lit lc dc) :
    slot.Z215 lf0 df lit lc dc ⦃ Y112P0! ⦄ := by
  rw [slot.Z215]
  step*
  all_goals exact EA.u38 _ _ _ (by simp)
attribute [local step] EB.u397
attribute [local step] EB.u398
attribute [local step] EB.u399
attribute [local step] EB.u400
attribute [local step] EB.u401
attribute [local step] EB.u402
@[local step]
theorem u474 (s:I) (kid) (pos depth oldest:R) (mb) (cur best:R) (seen:W) (lo_at hi_at lo_len hi_len steps:R)
    (hpos:pos.val + 266  ≤  s.length) (hn26:s.length < 67108864) (hlo:lo_len.val  ≤  258) (hhi:hi_len.val  ≤  258) (hbest:2  ≤  best.val) :
    slot.Z217_loop s kid pos depth mb oldest cur best seen lo_at hi_at lo_len hi_len steps ⦃ Y112P0! ⦄ := by
  rw [slot.Z217_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, _, _, _, _, _, steps_) => depth.val - steps_.val)
    (inv := fun (_, _, _, best_, _, _, _, lo_len_, hi_len_, _) => lo_len_.val  ≤  258  ∧  hi_len_.val  ≤  258  ∧  2  ≤  best_.val)
  · rintro ⟨kid_, mb_, cur_, best_, seen_, lo_at_, hi_at_, lo_len_, hi_len_, steps_⟩ ⟨hlo_, hhi_, hbest_⟩
    simp only [slot.Z217_loop.body, Submission.EA.d1_ite_ok]
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
@[local step]
theorem u475 (s:I) (head kid h3 rct) (pos:R) (pre depth mb) (hpos:pos.val + 266  ≤  s.length)
    (hn26:s.length < 67108864) :
    slot.Z217 s head kid h3 rct pos pre depth mb ⦃ Y112P0! ⦄ := Y127U23! slot.Z217
set_option maxHeartbeats 4000000 in
@[local step]
theorem u476 (i:W) (s:I) (mp:alloc.vec.Vec W) (mb depth) (skip n:R) (head kid h3 rct) (i1 cl cd:R) (nq nt nh n3 nr nc)
    (hn:n.val = s.length) (hn26:s.length < 67108864) (hi:i.val < 32) (hskip:3  ≤  skip.val)
    (hmp:mp.length  ≤  i1.val + 1) (hcd:1  ≤  cd.val) :
    slot.Z213_loop i s mp mb depth skip n head kid h3 rct i1 cl cd nq nt nh n3 nr nc ⦃ Y112P0! ⦄ := Y127U24! slot.Z213_loop slot.Z213_loop.body
@[local step]
theorem u477 (s:I) (mp:alloc.vec.Vec W) (mb depth) (skip:R)
    (hn26:s.length < 67108864) (hskip:3  ≤  skip.val) (hmp:mp.length = 0) :
    slot.Z213 s mp mb depth skip ⦃ Y112P0! ⦄ := Y127U25! slot.Z213
@[local step]
theorem u478 (n:R) (cost) (i:R) (hn:n.val < 67108864) (hc:cost.length = i.val) :
    slot.Z212_loop0 n cost i ⦃ Y112P0! ⦄ := Y127U26! slot.Z212_loop0 slot.Z212_loop0.body
@[local step]
theorem u479 (k passes tail final_tail):slot.Z216 k passes tail final_tail ⦃ Y112P0! ⦄ := by
  rw [slot.Z216]
  step*
  repeat' (split <;> step*)
set_option aeneas.step.nla true in
@[local step]
theorem u480 (tail final_tail:R) (input:I) (ch) (n:R) (mp mb cost lit lc dc lf df bl bd sl sd) (rot p0 need passes sampled pe k p1 t:R)
    (hn:n.val = input.length) (hn26:n.val < 67108864) (hp0:p0.val < n.val) (hpe:p0.val  ≤  pe.val  ∧  pe.val  ≤  n.val)
    (hpe':pe.val = n.val  ∨  p0.val + slot.Z1.val  ≤  pe.val)
    (hneed:need.val  ≤  65536) (ht:t.val  ≤  need.val) (hp1:p0.val  ≤  p1.val  ∧  p1.val  ≤  p0.val + 511 * t.val) :
    slot.Z212_loop1_loop0 input ch tail final_tail n mp mb cost lit lc dc lf df bl bd sl sd rot p0 need passes sampled pe k p1 t ⦃ fun r =>
      r.2.2.2.2.2.2.2.2.2.2.val  ≤  need.val  ∧  p0.val  ≤  r.2.2.2.2.2.2.2.2.2.1.val  ∧ 
      r.2.2.2.2.2.2.2.2.2.1.val  ≤  p0.val + 511 * r.2.2.2.2.2.2.2.2.2.2.val ⦄ := by
  have hbt := Submission.EA.A_BLOCK_bounds
  have hseg := Submission.EA.A_SEG_bounds
  rw [slot.Z212_loop1_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, _, _, _, _, _, _, k_, _, _) => passes.val - k_.val)
    (inv := fun (_, _, _, _, _, _, _, _, _, (pe_:R), _, (p1_:R), (t_:R)) =>
      p0.val  ≤  pe_.val  ∧  pe_.val  ≤  n.val  ∧  (pe_.val = n.val  ∨  p0.val + slot.Z1.val  ≤  pe_.val)  ∧ 
      t_.val  ≤  need.val  ∧  p0.val  ≤  p1_.val  ∧  p1_.val  ≤  p0.val + 511 * t_.val)
  · rintro ⟨ch_, cost_, lit_, lc_, dc_, lf_, df_, sl_, sd_, pe_, k_, p1_, t_⟩ ⟨hpe0, hpe1, hpe2, ht_, hp10, hp11⟩
    simp only [slot.Z212_loop1_loop0.body, Submission.EA.d1_ite_ok]
    step*
    apply WP.spec_bind (Pₘ := fun (x:alloc.vec.Vec W  ×  alloc.vec.Vec W  ×  Std.Array W 512#usize  × 
        Std.Array W 32#usize  ×  R  ×  R  ×  R) =>
        p0.val  ≤  x.2.2.2.2.1.val  ∧  x.2.2.2.2.1.val  ≤  n.val  ∧ 
        (x.2.2.2.2.1.val = n.val  ∨  p0.val + slot.Z1.val  ≤  x.2.2.2.2.1.val)  ∧ 
        x.2.2.2.2.2.2.val  ≤  need.val  ∧  p0.val  ≤  x.2.2.2.2.2.1.val  ∧  x.2.2.2.2.2.1.val  ≤  p0.val + 511 * x.2.2.2.2.2.2.val)
    · split
      · step*
        · -- a sampled pass: the window end scales with the sampled bytes per token
          cases ‹R  ×  R›
          step*
          apply WP.spec_bind (Pₘ := fun (z:alloc.vec.Vec W  ×  alloc.vec.Vec W  ×  Std.Array W 512#usize  × 
              Std.Array W 32#usize  ×  R) => p0.val  ≤  z.2.2.2.2.val  ∧  z.2.2.2.2.val  ≤  n.val  ∧ 
              (z.2.2.2.2.val = n.val  ∨  p0.val + slot.Z1.val  ≤  z.2.2.2.2.val))
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
              p0.val  ≤  z.2.2.val  ∧  z.2.2.val  ≤  n.val  ∧  (z.2.2.val = n.val  ∨  p0.val + slot.Z1.val  ≤  z.2.2.val))
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
              p0.val  ≤  z.2.2.val  ∧  z.2.2.val  ≤  n.val  ∧  (z.2.2.val = n.val  ∨  p0.val + slot.Z1.val  ≤  z.2.2.val))
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
              p0.val  ≤  z.2.2.val  ∧  z.2.2.val  ≤  n.val  ∧  (z.2.2.val = n.val  ∨  p0.val + slot.Z1.val  ≤  z.2.2.val))
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
theorem u481 (tail final_tail:R) (input:I) (ch first_passes fspass passes_k) (n:R) (mp mb cost lit lc dc lf df bl bd sl sd zl zd) (rot spn p0 used bpt:R)
    (hn:n.val = input.length) (hn26:n.val < 67108864) (hused:used.val < slot.Z45.val) (hbpt:256  ≤  bpt.val  ∧  bpt.val  ≤  65536) :
    slot.Z212_loop1 input ch first_passes fspass passes_k tail final_tail n mp mb cost lit lc dc lf df bl bd sl sd zl zd rot spn p0 used bpt ⦃ Y112P0! ⦄ := Y127U27! slot.Z212_loop1 slot.Z45.val slot.Z212_loop1.body slot.Z1.val
@[local step]
theorem u482 (tail final_tail:R) (input:I) (ch) (depth skip first_passes fspass passes_k spass:R)
    (hn:input.length < 67108864) (h1:depth.val  ≤  65536) (h2:skip.val  ≤  65536) (h2':3  ≤  skip.val)
    (h3:first_passes.val  ≤  65536) (h4:fspass.val  ≤  65536) (h5:passes_k.val  ≤  65536) (h6:spass.val  ≤  65536) :
    slot.Z212 input ch depth skip first_passes fspass passes_k spass tail final_tail ⦃ Y112P0! ⦄ := by
  have hbt := Submission.EA.A_BLOCK_bounds
  rw [slot.Z212]
  step*
  all_goals rfl

attribute [local step] EB.u411
attribute [local step] EB.u435
def u483 (mf:slot.Z72) (i:Nat):Prop :=
  EA.u15 mf.head.val i  ∧  EA.u15 mf.head3.val i  ∧  EA.u15 mf.tree.val i  ∧  EA.u15 mf.pn.val i  ∧ 
    mf.hl.val  ≤  2 ^ 30
theorem u484 (w:Std.Array Std.U64 32768#usize) (pf:Std.Array W 32#usize) (plen hn:R) :
    u483
      { head := Std.Array.repeat 65536#usize 0#u32, head3 := Std.Array.repeat 16384#usize 0#u32,
        tree := Std.Array.repeat 65536#usize 0#u32, w := w, pn := Std.Array.repeat 32#usize 0#u32, pf := pf,
        plen := plen, hn := hn, hl := 0#usize } (0#usize).val := Y127U28!
def u485 (b i:Nat)
    (r:ControlFlow (slot.Z72  ×  Std.Array W 32#usize  ×  alloc.vec.Vec W  ×  Std.U64  ×  R  × 
      R  ×  R) (slot.Z72  ×  Std.Array W 32#usize  ×  alloc.vec.Vec W  ×  Std.U64  × 
      R  ×  R)):Prop :=
  match r with
  | .done y => u483 y.1 b  ∧  y.2.2.2.2.2.val  ≤  33 * b  ∧  y.2.2.2.2.2.val  ≤  y.2.2.1.length
  | .cont x' => x'.2.2.2.2.2.2.val  ≤  b  ∧  x'.2.2.2.2.2.1.val  ≤  33 * x'.2.2.2.2.2.2.val  ∧ 
      x'.2.2.2.2.2.1.val  ≤  x'.2.2.1.length  ∧  u483 x'.1 x'.2.2.2.2.2.2.val  ∧ 
      b - x'.2.2.2.2.2.2.val < b - i












@[local step]
theorem u486 (s:I) (n:R) (head) (r4 r6 probes p:R)
    (hn:n.val = s.length) (hn26:n.val < 67108864) (hr4:r4.val  ≤  probes.val) (hr6:r6.val  ≤  probes.val)
    (hpr:probes.val  ≤  p.val) (hp:p.val  ≤  n.val + slot.Z4.val) :
    slot.Z243_loop s n head r4 r6 probes p ⦃ fun r => r.1.val  ≤  65536  ∧  r.2.val  ≤  65536 ⦄ := by
  have f1 := EA.u305
  have f2 := EA.u306
  have f3 := Submission.EA.dp_WN_val
  rw [slot.Z243_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, p') => n.val + slot.Z4.val - p'.val)
    (inv := fun (_, r4', r6', pr', p') => r4'.val  ≤  pr'.val  ∧  r6'.val  ≤  pr'.val  ∧  pr'.val  ≤  p'.val  ∧ 
      p'.val  ≤  n.val + slot.Z4.val)
  · rintro ⟨h', r4', r6', pr', p'⟩ ⟨i1, i2, i3, i4⟩
    simp only [slot.Z243_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact ⟨hr4, hr6, hpr, hp⟩
@[local step]
theorem u487 (s:I) (hn26:s.length < 67108864) :
    slot.Z243 s ⦃ fun r => r.1.val  ≤  65536  ∧  r.2.val  ≤  65536 ⦄ := Y127U1! slot.Z243
@[local step]
theorem u488 (plan e_nd p) :
    slot.Z220_loop plan e_nd p ⦃ fun r => r.length = plan.length ⦄ := by
  rw [slot.Z220_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, p') => e_nd.val - p'.val)
    (inv := fun (plan', _) => plan'.length = plan.length)
  · rintro ⟨plan', p'⟩ hinv
    simp only [slot.Z220_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · rfl
@[local step]
theorem u489 (plan p0 e_nd) :
    slot.Z220 plan p0 e_nd ⦃ fun r => r.length = plan.length ⦄ := Y127U1! slot.Z220
@[local step]
theorem u490 (d):slot.Z222 d ⦃ fun r => r.val < 256 ⦄ := Y127U1! slot.Z222
@[local step]
theorem u491 (len):slot.Z234 len ⦃ fun r => r.val < 256 ⦄ := Y127U1! slot.Z234
@[local step]
theorem u492 (lf df) :
    slot.Z237_loop0 lf df 0#usize ⦃ fun r => EA.u15 r.1.val 0  ∧  EA.u15 r.2.val 0 ⦄ := by
  rw [slot.Z237_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, k) => 288 - k.val)
    (inv := fun (lf', df', k) => k.val  ≤  288  ∧ 
      (∀ j (hj:j < k.val) (hl:j < lf'.val.length), (lf'.val[j]).val = 0)  ∧ 
      (∀ j (hj:j < k.val) (hl:j < df'.val.length), (df'.val[j]).val = 0))
  · rintro ⟨lf', df', k⟩ ⟨hk, hz1, hz2⟩
    simp only [slot.Z237_loop0.body]
    step*
    · refine ⟨by scalar_tac, ?_, ?_, by scalar_tac⟩
      · intro j hj hl
        subst a_post
        simp only [Array.set_val_eq, List.getElem_set]
        split
        · rfl
        · exact hz1 j (by scalar_tac) (by simpa using hl)
      · intro j hj hl
        subst a1_post
        simp only [Array.set_val_eq, List.getElem_set]
        split
        · rfl
        · exact hz2 j (by scalar_tac) (by simpa using hl)
    · have:k.val = 288 := by scalar_tac
      refine ⟨?_, ?_⟩
      · intro j hl
        have hl':j < 288 := by simpa using hl
        rw [hz1 j (by omega) hl]
      · intro j hl
        have hl':j < 288 := by simpa using hl
        rw [hz2 j (by omega) hl]
  · exact ⟨by simp, fun j hj => by simp at hj, fun j hj => by simp at hj⟩
@[local step]
theorem u493 (s:I) (choice) (lf df) (n p t:R)
    (hn:n.val = s.length) (hlf:EA.u15 lf.val t.val) (hdf:EA.u15 df.val t.val) :
    slot.Z237_loop1 s choice lf df n p t ⦃ fun r => p.val  ≤  r.2.2.val  ∧  (p.val  ≤  n.val  →  r.2.2.val  ≤  n.val) ⦄ := by
  have hB := EA.u292
  rw [slot.Z237_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, t') => slot.Z45.val - t'.val)
    (inv := fun (lf', df', p', t') => EA.u15 lf'.val t'.val  ∧  EA.u15 df'.val t'.val  ∧  p.val  ≤  p'.val  ∧ 
      (p.val  ≤  n.val  →  p'.val  ≤  n.val))
  · rintro ⟨lf', df', p', t'⟩ ⟨hlf', hdf', hp1, hp2⟩
    simp only [slot.Z237_loop1.body]
    step*
    apply WP.spec_bind (Pₘ := fun (x:Std.Array W 288#usize  ×  Std.Array W 288#usize  ×  R) =>
      EA.u15 x.1.val (t'.val + 1)  ∧  EA.u15 x.2.1.val (t'.val + 1)  ∧  p'.val < x.2.2.val  ∧  x.2.2.val  ≤  n.val)
    · split
      · step*
        · -- a match: one length and one distance counter go up (wrapping, but they cannot wrap)
          have h6 := Submission.EA.LeAll_get hlf' i5.val (by scalar_tac)
          have h12 := Submission.EA.LeAll_get hdf' i11.val (by scalar_tac)
          refine ⟨?_, ?_, by scalar_tac, by scalar_tac⟩
          · rw [a_post, Array.set_val_eq];exact EA.u19 hlf' _ _ (by scalar_tac)
          · rw [a1_post, Array.set_val_eq];exact EA.u19 hdf' _ _ (by scalar_tac)
        · -- the literal counter cannot overflow
          have := Submission.EA.LeAll_get hlf' i4.val (by scalar_tac)
          scalar_tac
        · -- a literal (the match does not fit)
          have := Submission.EA.LeAll_get hlf' i4.val (by scalar_tac)
          refine ⟨?_, EA.u16 hdf' (by omega), by scalar_tac, by scalar_tac⟩
          rw [a_post, Array.set_val_eq];exact EA.u19 hlf' _ _ (by scalar_tac)
      · -- a literal
        step*
        · have := Submission.EA.LeAll_get hlf' i3.val (by scalar_tac)
          scalar_tac
        · have := Submission.EA.LeAll_get hlf' i3.val (by scalar_tac)
          refine ⟨?_, EA.u16 hdf' (by omega), by scalar_tac, by scalar_tac⟩
          rw [a_post, Array.set_val_eq];exact EA.u19 hlf' _ _ (by scalar_tac)
    · rintro ⟨lf1, df1, p1⟩ ⟨h1, h2, h3, h4⟩
      step*
  · exact ⟨hlf, hdf, le_refl _, fun h => h⟩
@[local step]
theorem u494 (s choice p0 lf df) :
    slot.Z237 s choice p0 lf df ⦃ fun r => p0.val  ≤  r.1.val  ∧  (p0.val  ≤  s.length  →  r.1.val  ≤  s.length) ⦄ := by
  rw [slot.Z237]
  step*
@[local step]
theorem u495 (lf) (bits:Std.U64) (i:R) (hi:i.val  ≤  288)
    (hb:bits.val  ≤  3 + i.val * 2 ^ 40) :
    slot.Z228_loop0 lf bits i ⦃ fun r => r.val  ≤  3 + 288 * 2 ^ 40 ⦄ := by
  rw [slot.Z228_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, i') => 288 - i'.val)
    (inv := fun (bits', i') => i'.val  ≤  288  ∧  bits'.val  ≤  3 + i'.val * 2 ^ 40)
  · rintro ⟨bits', i'⟩ ⟨hi', hb'⟩
    simp only [slot.Z228_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact ⟨hi, hb⟩
@[local step]
theorem u496 (df) (bits:Std.U64) (d:R) (hd:d.val  ≤  30)
    (hb:bits.val  ≤  3 + 288 * 2 ^ 40 + d.val * 2 ^ 40) :
    slot.Z228_loop1 df bits d ⦃ fun r => r.val  ≤  3 + 318 * 2 ^ 40 ⦄ := by
  rw [slot.Z228_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, d') => 30 - d'.val)
    (inv := fun (bits', d') => d'.val  ≤  30  ∧  bits'.val  ≤  3 + 288 * 2 ^ 40 + d'.val * 2 ^ 40)
  · rintro ⟨bits', d'⟩ ⟨hd', hb'⟩
    simp only [slot.Z228_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact ⟨hd, hb⟩
@[local step]
theorem u497 (lf df) :
    slot.Z228 lf df ⦃ Y112P0! ⦄ := Y127U1! slot.Z228
@[local step]
theorem u498 (clf) (r:R) (extra:Std.U64) (fuel:R)
    (hx:extra.val + 7 * fuel.val  ≤  2 ^ 40) :
    slot.Z245_loop0 clf r extra fuel ⦃ fun res => res.2.2.val  ≤  extra.val + 7 * fuel.val ⦄ := by
  rw [slot.Z245_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, f) => f.val)
    (inv := fun (_, _, e, f) => e.val + 7 * f.val  ≤  extra.val + 7 * fuel.val)
  · rintro ⟨clf', r', e', f'⟩ hinv
    simp only [slot.Z245_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · simp
@[local step]
theorem u499 (clf) (r:R) (extra:Std.U64) (fuel:R)
    (hx:extra.val + 2 * fuel.val  ≤  2 ^ 40) :
    slot.Z245_loop1 clf r extra fuel ⦃ fun res => res.2.2.val  ≤  extra.val + 2 * fuel.val ⦄ := by
  rw [slot.Z245_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, f) => f.val)
    (inv := fun (_, _, e, f) => e.val + 2 * f.val  ≤  extra.val + 2 * fuel.val)
  · rintro ⟨clf', r', e', f'⟩ hinv
    simp only [slot.Z245_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · simp
@[local step]
theorem u500 (clf v) (r0:R) (hr0:1  ≤  r0.val  ∧  r0.val  ≤  512) :
    slot.Z245 clf v r0 ⦃ fun r => r.1.val  ≤  7 * (r0.val + 1) ⦄ := Y127U1! slot.Z245
@[local step]
theorem u501 (sw) (k:R) (shift:W) (hshift:shift.val < 32) :
    slot.Z242_loop0 sw k shift (Array.repeat 257#usize 0#usize) 0#usize ⦃ fun r => EA.u15 r.val 288 ⦄ := by
  rw [slot.Z242_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, i') => 288 - i'.val)
    (inv := fun (cnt', i') => i'.val  ≤  288  ∧  EA.u15 cnt'.val i'.val)
  · rintro ⟨cnt', i'⟩ ⟨hi', hc'⟩
    simp only [slot.Z242_loop0.body]
    step*
    all_goals first
      | scalar_tac
      | exact EA.u16 hc' (by scalar_tac)
      | (refine ⟨by scalar_tac, ?_, by scalar_tac⟩
         rw [a_post, Array.set_val_eq, show i9.val = i'.val + 1 by scalar_tac]
         apply EA.u19 hc'
         have := Submission.EA.LeAll_get hc' i5.val (by scalar_tac)
         scalar_tac)
  · exact ⟨by simp, EA.u38 _ _ _ (by simp)⟩
@[local step]
theorem u502 (cnt) (hcnt:EA.u15 cnt.val 288) :
    slot.Z242_loop1 cnt 1#usize ⦃ fun r => EA.u15 r.val 74016 ⦄ := by
  rw [slot.Z242_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, c') => 257 - c'.val)
    (inv := fun (cnt', c') => 1  ≤  c'.val  ∧  c'.val  ≤  257  ∧ 
      (∀ j (hj:j < cnt'.val.length), j < c'.val  →  (cnt'.val[j]).val  ≤  288 * c'.val)  ∧ 
      (∀ j (hj:j < cnt'.val.length), c'.val  ≤  j  →  (cnt'.val[j]).val  ≤  288))
  · rintro ⟨cnt', c'⟩ ⟨hc1, hc2, hlo, hhi⟩
    simp only [slot.Z242_loop1.body]
    step*
    · have hi:i.val  ≤  288 := by rw [i_post];exact hhi _ _ (le_refl _)
      have hi2:i2.val  ≤  288 * c'.val := by rw [i2_post];exact hlo _ _ (by scalar_tac)
      refine ⟨by scalar_tac, by scalar_tac, ?_, ?_, by scalar_tac⟩
      · intro j hj hjc
        subst a_post
        simp only [Array.set_val_eq, List.getElem_set]
        split
        · scalar_tac
        · have hj':j < (↑cnt':List R).length := by simpa using hj
          have := hlo j hj' (by scalar_tac)
          scalar_tac
      · intro j hj hjc
        subst a_post
        simp only [Array.set_val_eq, List.getElem_set]
        split
        · scalar_tac
        · exact hhi j (by simpa using hj) (by scalar_tac)
    · intro j hj
      have hj2:j < 257 := by simpa using hj
      have := hlo j hj (by scalar_tac)
      scalar_tac
  · refine ⟨by simp, by simp, ?_, ?_⟩
    · intro j hj hj1
      have := hcnt j hj
      simp at hj1 ⊢
      omega
    · intro j hj _
      exact hcnt j hj
@[local step]
theorem u503 (sw ss dw ds) (k:R) (shift:W) (cnt) (hshift:shift.val < 32)
    (hcnt:EA.u15 cnt.val 74016) :
    slot.Z242_loop2 sw ss dw ds k shift cnt 0#usize ⦃ Y112P0! ⦄ := by
  rw [slot.Z242_loop2]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, j') => 288 - j'.val)
    (inv := fun (_, _, cnt', j') => j'.val  ≤  288  ∧  EA.u15 cnt'.val (74016 + j'.val))
  · rintro ⟨dw', ds', cnt', j'⟩ ⟨hj', hc'⟩
    simp only [slot.Z242_loop2.body]
    step*
    all_goals first
      | scalar_tac
      | (have := Submission.EA.LeAll_get hc' i3.val (by scalar_tac)
         scalar_tac)
      | (refine ⟨by scalar_tac, ?_, by scalar_tac⟩
         rw [a2_post, Array.set_val_eq, show j1.val = j'.val + 1 by scalar_tac, ← Nat.add_assoc]
         apply EA.u19 hc'
         have := Submission.EA.LeAll_get hc' i3.val (by scalar_tac)
         scalar_tac)
  · exact ⟨by simp, by simpa using hcnt⟩
@[local step]
theorem u504 (sw ss dw ds) (k:R) (shift:W) (hshift:shift.val < 32) :
    slot.Z242 sw ss dw ds k shift ⦃ Y112P0! ⦄ := by
  rw [slot.Z242]
  step*
@[local step]
theorem u505 (freq m lens aw asy) (k i:R) (hk:k.val  ≤  i.val) (hi:i.val  ≤  288) :
    slot.Z231_loop0 freq m lens aw asy k i ⦃ fun r => r.2.2.2.val  ≤  288 ⦄ := by
  rw [slot.Z231_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, i') => 288 - i'.val)
    (inv := fun (_, _, _, k', i') => k'.val  ≤  i'.val  ∧  i'.val  ≤  288)
  · rintro ⟨lens', aw', asy', k', i'⟩ ⟨hk', hi'⟩
    simp only [slot.Z231_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact ⟨hk, hi⟩
@[local step]
theorem u506 (aw) (k:R) (iw ipar lpar) (li ii ni:R) (w2) (t:R)
    (hii:ii.val  ≤  2 ^ 20) :
    slot.Z231_loop1_loop0 aw k iw ipar lpar li ii ni w2 t ⦃ fun r => r.2.2.2.1.val  ≤  ii.val + 2 ⦄ := by
  rw [slot.Z231_loop1_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, _, t') => 2 - t'.val)
    (inv := fun (_, _, _, ii', _, t') => ii'.val + t.val  ≤  ii.val + t'.val  ∧  t.val  ≤  t'.val  ∧ 
      (t.val  ≤  2  →  t'.val  ≤  2)  ∧  (2 < t.val  →  t'.val = t.val))
  · rintro ⟨ipar', lpar', li', ii', w2', t'⟩ ⟨h1, h2, h3, h4⟩
    simp only [slot.Z231_loop1_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · simp
@[local step]
theorem u507 (aw) (k:R) (iw ipar lpar) (li ii ni:R) (hii:ii.val  ≤  2 * ni.val)
    (hni:ni.val  ≤  287) (hk:k.val  ≤  288) :
    slot.Z231_loop1 aw k iw ipar lpar li ii ni ⦃ fun r => ni.val  ≤  r.2.2.val  ∧  (ni.val + 1 < k.val  →  ni.val < r.2.2.val) ⦄ := by
  rw [slot.Z231_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, _, ni') => 287 - ni'.val)
    (inv := fun (_, _, _, _, ii', ni') => ni.val  ≤  ni'.val  ∧  ni'.val  ≤  287  ∧  ii'.val  ≤  2 * ni'.val)
  · rintro ⟨iw', ipar', lpar', li', ii', ni'⟩ ⟨h1, h2, h3⟩
    simp only [slot.Z231_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact ⟨le_refl _, hni, hii⟩
@[local step]
theorem u508 (ipar idep j) :
    slot.Z231_loop2 ipar idep j ⦃ Y112P0! ⦄ := by
  rw [slot.Z231_loop2]
  apply Std.loop.spec_decr_nat
    (measure := fun (idep_, j_) => j_.val)
    (inv := fun _ => True)
  · rintro ⟨idep_, j_⟩ _
    simp only [slot.Z231_loop2.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem u509 (lens asy k lpar idep x) :
    slot.Z231_loop3 lens asy k lpar idep x ⦃ Y112P0! ⦄ := by
  rw [slot.Z231_loop3]
  apply Std.loop.spec_decr_nat
    (measure := fun (lens_, x_) => k.val - x_.val)
    (inv := fun _ => True)
  · rintro ⟨lens_, x_⟩ _
    simp only [slot.Z231_loop3.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem u510 (freq m lens):slot.Z231 freq m lens ⦃ Y112P0! ⦄ := Y127U1! slot.Z231
@[local step]
theorem u511 (lf ll) (body:Std.U64) (hlit i:R) (hi:i.val  ≤  286)
    (hb:body.val  ≤  i.val * 2 ^ 41) :
    slot.Z223_loop0 lf ll body hlit i ⦃ fun r => r.1.val  ≤  286 * 2 ^ 41  ∧  r.2.val  ≤  max hlit.val 286 ⦄ := by
  rw [slot.Z223_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, i') => 286 - i'.val)
    (inv := fun (b', h', i') => i'.val  ≤  286  ∧  b'.val  ≤  i'.val * 2 ^ 41  ∧  h'.val  ≤  max hlit.val 286)
  · rintro ⟨b', h', i'⟩ ⟨h1, h2, h3⟩
    simp only [slot.Z223_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact ⟨hi, hb, by scalar_tac⟩
@[local step]
theorem u512 (df dl) (body:Std.U64) (hdist any:R) (d:R) (hd:d.val  ≤  30)
    (hb:body.val  ≤  286 * 2 ^ 41 + d.val * 2 ^ 41) :
    slot.Z223_loop1 df dl body hdist any d ⦃ fun r => r.1.val  ≤  316 * 2 ^ 41  ∧  r.2.1.val  ≤  max hdist.val 30 ⦄ := by
  rw [slot.Z223_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, d') => 30 - d'.val)
    (inv := fun (b', h', _, d') => d'.val  ≤  30  ∧  b'.val  ≤  286 * 2 ^ 41 + d'.val * 2 ^ 41  ∧  h'.val  ≤  max hdist.val 30)
  · rintro ⟨b', h', a', d'⟩ ⟨h1, h2, h3⟩
    simp only [slot.Z223_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact ⟨hd, hb, by scalar_tac⟩
@[local step]
theorem u513 (ll dl hlit total seq i2) :
    slot.Z223_loop2 ll dl hlit total seq i2 ⦃ Y112P0! ⦄ := by
  rw [slot.Z223_loop2]
  apply Std.loop.spec_decr_nat
    (measure := fun (seq_, i2_) => total.val - i2_.val)
    (inv := fun _ => True)
  · rintro ⟨seq_, i2_⟩ _
    simp only [slot.Z223_loop2.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem u514 (total seq) (j r:R) (v) (hj:j.val  ≤  512) (hr:r.val  ≤  512) :
    slot.Z223_loop3_loop0 total seq j v r ⦃ fun res => r.val  ≤  res.val  ∧  res.val  ≤  max r.val 512  ∧ 
      (j.val + r.val  ≤  512  →  j.val + res.val  ≤  512) ⦄ := by
  rw [slot.Z223_loop3_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun r' => 512 - r'.val)
    (inv := fun r' => r.val  ≤  r'.val  ∧  r'.val  ≤  max r.val 512  ∧  (j.val + r.val  ≤  512  →  j.val + r'.val  ≤  512))
  · rintro r' ⟨h1, h2, h3⟩
    simp only [slot.Z223_loop3_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact ⟨le_refl _, by scalar_tac, fun h => h⟩
@[local step]
theorem u515 (clf) (extra:Std.U64) (total seq) (j:R) (hj:j.val  ≤  512)
    (hx:extra.val  ≤  j.val * 4096) :
    slot.Z223_loop3 clf extra total seq j ⦃ fun r => r.2.val  ≤  513 * 4096 ⦄ := by
  rw [slot.Z223_loop3]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, j') => 512 - j'.val)
    (inv := fun (_, e', j') => j'.val  ≤  512  ∧  e'.val  ≤  j'.val * 4096)
  · rintro ⟨clf', e', j'⟩ ⟨h1, h2⟩
    simp only [slot.Z223_loop3.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact ⟨hj, hx⟩
@[local step]
theorem u516 (cl hclen) :
    slot.Z223_loop4 cl hclen ⦃ fun r => r.val  ≤  hclen.val ⦄ := by
  rw [slot.Z223_loop4]
  apply Std.loop.spec_decr_nat
    (measure := fun h' => h'.val)
    (inv := fun h' => h'.val  ≤  hclen.val)
  · rintro h' h1
    simp only [slot.Z223_loop4.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact le_refl _
@[local step]
theorem u517 (clf cl) (hdr:Std.U64) (c:R) (hc:c.val  ≤  19)
    (hh:hdr.val  ≤  2 ^ 40 + c.val * 2 ^ 35) :
    slot.Z223_loop5 clf cl hdr c ⦃ fun r => r.val  ≤  2 ^ 40 + 19 * 2 ^ 35 ⦄ := by
  rw [slot.Z223_loop5]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, c') => 19 - c'.val)
    (inv := fun (h', c') => c'.val  ≤  19  ∧  h'.val  ≤  2 ^ 40 + c'.val * 2 ^ 35)
  · rintro ⟨h', c'⟩ ⟨h1, h2⟩
    simp only [slot.Z223_loop5.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact ⟨hc, hh⟩
@[local step]
theorem u518 (lf df):slot.Z223 lf df ⦃ Y112P0! ⦄ := Y127U1! slot.Z223
@[local step]
theorem u519 (s:I) (ec q:R)
    (hec:ec.val  ≤  s.length) (hn26:s.length < 67108864) :
    slot.Z238_loop0_loop0 s ec (Array.repeat 288#usize 0#u32) q ⦃ Y112P0! ⦄ := by
  rw [slot.Z238_loop0_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, q') => ec.val - q'.val)
    (inv := fun (lb', q') => EA.u15 lb'.val q'.val)
  · rintro ⟨lb', q'⟩ hlb'
    simp only [slot.Z238_loop0_loop0.body]
    step*
    all_goals first
      | (have := Submission.EA.LeAll_get hlb' i1.val (by scalar_tac)
         scalar_tac)
      | (refine ⟨?_, by scalar_tac⟩
         rw [a_post, Array.set_val_eq, show q1.val = q'.val + 1 by scalar_tac]
         apply EA.u19 hlb'
         have := Submission.EA.LeAll_get hlb' i1.val (by scalar_tac)
         scalar_tac)
  · exact EA.u38 _ _ _ (by simp)
@[local step]
theorem u520 (s:I) (plan) (n:R) (lf df p fuel) (hn:n.val = s.length)
    (hn26:n.val < 67108864) :
    slot.Z238_loop0 s plan n lf df p fuel ⦃ Y112P0! ⦄ := by
  have hB := EA.u292
  rw [slot.Z238_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, f) => f.val)
    (inv := fun _ => True)
  · rintro ⟨plan', lf', df', p', f'⟩ _
    simp only [slot.Z238_loop0.body]
    step*
    apply WP.spec_bind (Pₘ := fun _ => True)
    · split <;> step*
    rintro ca _
    step*
    apply WP.spec_bind (Pₘ := fun (x:R) => p'.val  ≤  x.val  ∧  x.val  ≤  n.val)
    · split <;> step*
      all_goals scalar_tac
    rintro eb ⟨heb1, heb2⟩
    apply WP.spec_bind (Pₘ := fun (x:R) => p'.val  ≤  x.val  ∧  x.val  ≤  n.val)
    · split <;> step*
      all_goals scalar_tac
    rintro ec ⟨hec1, hec2⟩
    step*
    apply WP.spec_bind (Pₘ := fun _ => True)
    · split <;> step*
    rintro cb _
    apply WP.spec_bind (Pₘ := fun _ => True)
    · split <;> step*
    rintro cb1 _
    step*
    all_goals scalar_tac
  · trivial
@[local step]
theorem u521 (s:I) (plan) (hn26:s.length < 67108864) :
    slot.Z238 s plan ⦃ Y112P0! ⦄ := Y127U1! slot.Z238
@[local step]
theorem u522 (s:I) (n allow:R) (bad i:R) (hn:n.val  ≤  s.length)
    (hbad:bad.val  ≤  i.val) :
    slot.Z232_loop s n allow bad i ⦃ Y112P0! ⦄ := by
  rw [slot.Z232_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, i') => n.val - i'.val)
    (inv := fun (bad', i') => bad'.val  ≤  i'.val)
  · rintro ⟨bad', i'⟩ hb'
    simp only [slot.Z232_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact hbad
@[local step]
theorem u523 (s) :
    slot.Z232 s ⦃ Y112P0! ⦄ := Y127U1! slot.Z232
@[local step]
theorem u524 (lf df ll dl) (est:Std.U64) (q:R) (hq:q.val  ≤  288)
    (he:est.val  ≤  70 + q.val * 2 ^ 42) :
    slot.Z240_loop0 lf df ll dl est q ⦃ fun r => r.val  ≤  70 + 288 * 2 ^ 42 ⦄ := by
  rw [slot.Z240_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, q') => 288 - q'.val)
    (inv := fun (e', q') => q'.val  ≤  288  ∧  e'.val  ≤  70 + q'.val * 2 ^ 42)
  · rintro ⟨e', q'⟩ ⟨h1, h2⟩
    simp only [slot.Z240_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact ⟨hq, he⟩
@[local step]
theorem u525 (models) (tokpen:W) (ll) (i:R) (htok:tokpen.val  ≤  65536)
    (hm:models.length + (256 - i.val) < 4294967295) :
    slot.Z240_loop1 models tokpen ll i ⦃ fun r => r.length = models.length + (256 - i.val) ⦄ := by
  have h1 := EA.u296
  have h2 := Submission.EA.C_UNUSED_LIT_le
  rw [slot.Z240_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, i') => 256 - i'.val)
    (inv := fun (m', i') => m'.length = models.length + (i'.val - i.val)  ∧  i.val  ≤  i'.val  ∧  i'.val  ≤  max i.val 256)
  · rintro ⟨m', i'⟩ ⟨h3, h4, h5⟩
    simp only [slot.Z240_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact ⟨by simp, le_refl _, by scalar_tac⟩
@[local step]
theorem u526 (models) (tax ulen tokpen:W) (ll) (l:R) (htax:tax.val  ≤  65536)
    (hulen:ulen.val  ≤  65536) (htok:tokpen.val  ≤  65536) (hl:3  ≤  l.val)
    (hm:models.length + (259 - l.val) < 4294967295) :
    slot.Z240_loop2 models tax ulen tokpen ll l ⦃ fun r => r.length = models.length + (259 - l.val) ⦄ := by
  have h1 := EA.u296
  rw [slot.Z240_loop2]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, l') => 259 - l'.val)
    (inv := fun (m', l') => m'.length = models.length + (l'.val - l.val)  ∧  l.val  ≤  l'.val  ∧  l'.val  ≤  max l.val 259)
  · rintro ⟨m', l'⟩ ⟨h3, h4, h5⟩
    simp only [slot.Z240_loop2.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact ⟨by simp, le_refl _, by scalar_tac⟩
@[local step]
theorem u527 (models) (udist:W) (dl) (d:R) (hud:udist.val  ≤  65536)
    (hm:models.length + (32 - d.val) < 4294967295) :
    slot.Z240_loop3 models udist dl d ⦃ fun r => r.length = models.length + (32 - d.val) ⦄ := by
  have h1 := EA.u296
  rw [slot.Z240_loop3]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, d') => 32 - d'.val)
    (inv := fun (m', d') => m'.length = models.length + (d'.val - d.val)  ∧  d.val  ≤  d'.val  ∧  d'.val  ≤  max d.val 32)
  · rintro ⟨m', d'⟩ ⟨h3, h4, h5⟩
    simp only [slot.Z240_loop3.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact ⟨by simp, le_refl _, by scalar_tac⟩
@[local step]
theorem u528 (models lf df) (tax ulen udist tokpen:W) (htax:tax.val  ≤  65536) (hulen:ulen.val  ≤  65536)
    (hud:udist.val  ≤  65536) (htok:tokpen.val  ≤  65536) (hm:models.length + 544 < 4294967295) :
    slot.Z240 models lf df tax ulen udist tokpen ⦃ fun r => r.1.val  ≤  70 + 288 * 2 ^ 42  ∧  r.2.length = models.length + 544 ⦄ := Y127U1! slot.Z240
@[local step]
theorem u529 (s:I) (choice) (n:R) (lf df) (p t:R)
    (hn:n.val  ≤  s.length) (hnc:n.val  ≤  choice.length) (hn26:n.val < 67108864) :
    slot.Z244_loop0_loop0 s choice n lf df p t ⦃ fun r => p.val  ≤  r.2.2.val  ∧ 
      r.2.2.val  ≤  max p.val (n.val + 511)  ∧ 
      (p.val < n.val  →  t.val < slot.Z45.val  →  p.val < r.2.2.val)  ∧ 
      (r.2.2.val < n.val  →  p.val + (slot.Z45.val - t.val)  ≤  r.2.2.val) ⦄ := by
  have hB := EA.u292
  rw [slot.Z244_loop0_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, t') => slot.Z45.val - t'.val)
    (inv := fun (_, _, p', t') => p.val + (t'.val - t.val)  ≤  p'.val  ∧  t.val  ≤  t'.val  ∧ 
      p'.val  ≤  max p.val (n.val + 511)  ∧  t'.val  ≤  max t.val slot.Z45.val)
  · rintro ⟨lf', df', p', t'⟩ ⟨h1, h2, h3, h4⟩
    simp only [slot.Z244_loop0_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact ⟨by simp, le_refl _, by scalar_tac, by scalar_tac⟩
@[local step]
theorem u530 (s:I) (choice models bstart) (tax ulen udist tokpen:W)
    (total:Std.U64) (n:R) (lf df) (p:R)
    (hn:n.val  ≤  s.length) (hnc:n.val  ≤  choice.length) (hn26:n.val < 67108864)
    (htax:tax.val  ≤  65536) (hulen:ulen.val  ≤  65536) (hud:udist.val  ≤  65536) (htok:tokpen.val  ≤  65536)
    (hb:544 * bstart.length  ≤  models.length + 544)
    (ht:544 * total.val  ≤  models.length * (70 + 288 * 2 ^ 42))
    (hm:models.length * 8192 < 544 * (n.val + 8192))
    (hp:p.val < n.val  →  models.length * 8192  ≤  544 * p.val) :
    slot.Z244_loop0 s choice models bstart tax ulen udist tokpen total n lf df p ⦃ fun r =>
      544 * r.2.1.length  ≤  r.1.length + 544  ∧  544 * r.2.2.1.val  ≤  r.1.length * (70 + 288 * 2 ^ 42)  ∧ 
      r.1.length * 8192 < 544 * (n.val + 8192) ⦄ := by
  have hB := EA.u292
  rw [slot.Z244_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, _, p') => n.val - p'.val)
    (inv := fun (m', b', t', _, _, p') => 544 * b'.length  ≤  m'.length + 544  ∧ 
      544 * t'.val  ≤  m'.length * (70 + 288 * 2 ^ 42)  ∧  m'.length * 8192 < 544 * (n.val + 8192)  ∧ 
      (p'.val < n.val  →  m'.length * 8192  ≤  544 * p'.val))
  · rintro ⟨m', b', t', lf', df', p'⟩ ⟨h1, h2, h3, h4⟩
    simp only [slot.Z244_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact ⟨hb, ht, hm, hp⟩
@[local step]
theorem u531 (s:I) (choice models bstart) (tax ulen udist tokpen:W)
    (hn26:s.length < 67108864) (htax:tax.val  ≤  65536) (hulen:ulen.val  ≤  65536) (hud:udist.val  ≤  65536)
    (htok:tokpen.val  ≤  65536) :
    slot.Z244 s choice models bstart tax ulen udist tokpen ⦃ fun r => r.2.2.length  ≤  1048576 ⦄ := Y127U1! slot.Z244
@[local step]
theorem u532 (choice n p) :
    slot.Z229_loop0 choice n p ⦃ Y112P0! ⦄ := by
  rw [slot.Z229_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (choice_, p_) => n.val - p_.val)
    (inv := fun _ => True)
  · rintro ⟨choice_, p_⟩ _
    simp only [slot.Z229_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem u533 (clist choice n gmin) (m k:R) (hm:m.val = clist.length) (hk:1  ≤  k.val) :
    slot.Z229_loop1 clist choice n gmin m k ⦃ Y112P0! ⦄ := by
  rw [slot.Z229_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, k') => m.val - k'.val)
    (inv := fun (_, k') => 1  ≤  k'.val)
  · rintro ⟨choice', k'⟩ hk'
    simp only [slot.Z229_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact hk
@[local step]
theorem u534 (clist choice n gmin) :
    slot.Z229 clist choice n gmin ⦃ Y112P0! ⦄ := Y127U1! slot.Z229
@[local step]
theorem u535 (models:alloc.vec.Vec W) (lit_c len_c) (base i:R) (hb:base.val + slot.Z20.val  ≤  models.length) :
    slot.Z233_loop0 models lit_c len_c base i ⦃ Y112P0! ⦄ := by
  rw [slot.Z233_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (lit_c_, len_c_, i_) => 256 - i_.val)
    (inv := fun _ => True)
  · rintro ⟨lit_c_, len_c_, i_⟩ _
    simp only [slot.Z233_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem u536 (models:alloc.vec.Vec W) (dst_c) (base d:R) (hb:base.val + slot.Z20.val  ≤  models.length) :
    slot.Z233_loop1 models dst_c base d ⦃ Y112P0! ⦄ := by
  rw [slot.Z233_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (dst_c_, d_) => 32 - d_.val)
    (inv := fun _ => True)
  · rintro ⟨dst_c_, d_⟩ _
    simp only [slot.Z233_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem u537 (models) (b:R) (lit_c len_c dst_c) (hb:b.val  ≤  1048576) :
    slot.Z233 models b lit_c len_c dst_c ⦃ Y112P0! ⦄ := Y127U1! slot.Z233
@[local step]
theorem u538 (clist ge) :
    slot.Z230 clist ge ⦃ fun r => r.val  ≤  ge.val ⦄ := Y127U1! slot.Z230
@[local step]
theorem u539 (bstart:alloc.vec.Vec W) (b q:R) (hb:b.val < bstart.length) :
    slot.Z221_loop0_loop0 bstart b q ⦃ fun r => r.val  ≤  b.val ⦄ := by
  rw [slot.Z221_loop0_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun b' => b'.val)
    (inv := fun b' => b'.val  ≤  b.val)
  · rintro b' hb'
    simp only [slot.Z221_loop0_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact le_refl _
@[local step]
theorem u540 (s:I) (choice:U) (ring lit_c next) (p lo:R)
    (hp:p.val  ≤  s.length) (hc:s.length  ≤  choice.length) :
    slot.Z221_loop0_loop1 s choice ring lit_c next p lo ⦃ fun r => r.1.length = choice.length  ∧  r.2.2.2.val  ≤  p.val ⦄ := by
  rw [slot.Z221_loop0_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, p') => p'.val)
    (inv := fun (c', _, _, p') => c'.length = choice.length  ∧  p'.val  ≤  p.val)
  · rintro ⟨c', r', n', p'⟩ ⟨h1, h2⟩
    simp only [slot.Z221_loop0_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact ⟨rfl, le_refl _⟩
@[local step]
theorem u541 (ring len_c) (p:R) (best ch) (l:R) (dc tag) (len:R)
    (hp:p.val  ≤  2 ^ 30) (hl:l.val  ≤  511) (hlen:3  ≤  len.val) :
    slot.Z221_loop0_loop2_loop0 ring len_c p best ch l dc tag len ⦃ Y112P0! ⦄ := by
  rw [slot.Z221_loop0_loop2_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, len') => l.val + 1 - len'.val)
    (inv := fun (_, _, len') => 3  ≤  len'.val)
  · rintro ⟨b', c', len'⟩ h1
    simp only [slot.Z221_loop0_loop2_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact hlen
@[local step]
theorem u542 (clist ring len_c dst_c) (ge p:R) (best ch) (prev room k:R)
    (hp:p.val  ≤  2 ^ 30) (hprev:2  ≤  prev.val  ∧  prev.val  ≤  511)
    (hk:k.val  ≤  clist.length) (hcl:clist.length < 4294967295) :
    slot.Z221_loop0_loop2 clist ring len_c dst_c ge p best ch prev room k ⦃ Y112P0! ⦄ := by
  rw [slot.Z221_loop0_loop2]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, k') => clist.length - k'.val)
    (inv := fun (_, _, prev', k') => 2  ≤  prev'.val  ∧  prev'.val  ≤  511  ∧  k'.val  ≤  clist.length)
  · rintro ⟨b', c', prev', k'⟩ ⟨h1, h2, h3⟩
    simp only [slot.Z221_loop0_loop2.body]
    step*
    apply WP.spec_bind (Pₘ := fun (x:R) => 2  ≤  x.val  ∧  x.val  ≤  511)
    · repeat' (split <;> step*)
      all_goals scalar_tac
    rintro prev1 ⟨hq1, hq2⟩
    step*
    apply WP.spec_bind (Pₘ := fun (x:R) => x.val  ≤  511)
    · split <;> step*
      all_goals scalar_tac
    rintro l1 hl1
    step*
    all_goals scalar_tac
  · exact ⟨hprev.1, hprev.2, hk⟩
@[local step]
theorem u543 (s:I) (clist models:alloc.vec.Vec W) (bstart:alloc.vec.Vec W) (choice:U)
    (n:R) (ring lit_c len_c dst_c) (b loaded ge gs gp:R) (next) (p fuel:R)
    (hn:n.val = s.length) (hn26:n.val < 67108864) (hc:n.val  ≤  choice.length) (hb:b.val < bstart.length)
    (hnb:bstart.length  ≤  1048576) (hp:p.val  ≤  n.val) (hgp:gp.val  ≤  n.val  ∨  gp.val < 2 ^ 27)
    (hcl:clist.length < 4294967295) (hgs:gs.val  ≤  ge.val) (hge:ge.val  ≤  clist.length) :
    slot.Z221_loop0 s clist models bstart choice n ring lit_c len_c dst_c b loaded ge gs gp next p fuel ⦃ Y112P0! ⦄ := by
  have hpm := EA.u294
  rw [slot.Z221_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, _, _, _, _, _, _, _, _, f) => f.val)
    (inv := fun (c', _, _, _, _, b', _, ge', gs', gp', _, p', _) => c'.length = choice.length  ∧ 
      b'.val < bstart.length  ∧  p'.val  ≤  n.val  ∧  (gp'.val  ≤  n.val  ∨  gp'.val < 2 ^ 27)  ∧ 
      gs'.val  ≤  ge'.val  ∧  ge'.val  ≤  clist.length)
  · rintro ⟨c', r', l1', l2', d', b', ld', ge', gs', gp', nx', p', f'⟩ ⟨h1, h2, h3, h4, h5, h6⟩
    simp only [slot.Z221_loop0.body]
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
    all_goals scalar_tac
  · exact ⟨rfl, hb, hp, hgp, hgs, hge⟩
@[local step]
theorem u544 (s:I) (clist models) (bstart:alloc.vec.Vec W) (choice)
    (hn26:s.length < 67108864) (hnb:bstart.length  ≤  1048576) (hcl:clist.length < 4294967295) :
    slot.Z221 s clist models bstart choice ⦃ Y112P0! ⦄ := by
  have hms := EA.u293
  have hpm := EA.u294
  rw [slot.Z221]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac
@[local step]
theorem u545 (len) (d:R) (hd:1  ≤  d.val):slot.Z236 len d ⦃ Y112P0! ⦄ := Y127U1! slot.Z236
@[local step]
theorem u546 (clist:alloc.vec.Vec W) (ml md) (cnt:R) (flag) (top:R)
    (pushed:W) (i:R)
    (hcl:clist.length + (cnt.val - i.val) < 4294967295) (hpu:pushed.val  ≤  1) :
    slot.Z239_loop clist ml md cnt flag top pushed i ⦃ fun r =>
      r.1.length  ≤  clist.length + (cnt.val - i.val)  ∧  r.2.2.val  ≤  pushed.val + (cnt.val - i.val)  ∧ 
      (top.val  ≤  258  →  r.2.1.val  ≤  258) ⦄ := by
  rw [slot.Z239_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, i') => 64 - i'.val)
    (inv := fun (c', t', u', i') => c'.length + (cnt.val - i'.val)  ≤  clist.length + (cnt.val - i.val)  ∧ 
      u'.val + (cnt.val - i'.val)  ≤  pushed.val + (cnt.val - i.val)  ∧  i.val  ≤  i'.val  ∧ 
      (top.val  ≤  258  →  t'.val  ≤  258))
  · rintro ⟨c', t', u', i'⟩ ⟨h1, h2, h3, h4⟩
    simp only [slot.Z239_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact ⟨le_refl _, le_refl _, le_refl _, fun h => h⟩
@[local step]
theorem u547 (clist:alloc.vec.Vec W) (p ml md cnt r1 flag)
    (hcl:clist.length + slot.Z3.val + 2 < 4294967295) :
    slot.Z239 clist p ml md cnt r1 flag ⦃ fun r => r.2.length  ≤  clist.length + slot.Z3.val + 2  ∧ 
      r.1.val  ≤  258 ⦄ := Y127U1! slot.Z239
@[local step]
theorem u548 (b) :
    slot.Z235 b ⦃ Y112P0! ⦄ := Y127U1! slot.Z235
@[local step]
theorem u549 (s) (i:R) (hi:i.val + 8  ≤  Usize.max):slot.Z247 s i ⦃ Y112P0! ⦄ := Y127U1! slot.Z247
@[local step]
theorem u550 (s:I) (a b lim k:R) (ha:a.val + lim.val  ≤  s.length) (hb:b.val + lim.val  ≤  s.length) :
    slot.Z225_loop0_loop0 s a b lim k ⦃ Y112P0! ⦄ := Y127U22! slot.Z225_loop0_loop0 slot.Z225_loop0_loop0.body
@[local step]
theorem u551 (s:I) (a b lim k:R) (ha:a.val + lim.val  ≤  s.length) (hb:b.val + lim.val  ≤  s.length) :
    slot.Z225_loop0_loop1 s a b lim k ⦃ Y112P0! ⦄ := Y127U22! slot.Z225_loop0_loop1 slot.Z225_loop0_loop1.body
@[local step]
theorem u552 (s:I) (a b lim k fuel:R) (ha:a.val + lim.val  ≤  s.length)
    (hb:b.val + lim.val  ≤  s.length) (hk:k.val  ≤  2 ^ 31) (hlim:lim.val  ≤  2 ^ 31) :
    slot.Z225_loop0 s a b lim k fuel ⦃ Y112P0! ⦄ := by
  rw [slot.Z225_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, f') => f'.val)
    (inv := fun (k', _) => k'.val  ≤  2 ^ 31)
  · rintro ⟨k', f'⟩ hk'
    simp only [slot.Z225_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact hk
@[local step]
theorem u553 (s:I) (a b k0 lim:R) (ha:a.val + lim.val  ≤  s.length) (hb:b.val + lim.val  ≤  s.length)
    (hk0:k0.val  ≤  2 ^ 31) (hlim:lim.val  ≤  2 ^ 31) :
    slot.Z225 s a b k0 lim ⦃ Y112P0! ⦄ := Y127U1! slot.Z225
@[local step]
theorem u554 (s:I) (p k0 depth:R) (prev ml md) (lim cur best cnt steps:R)
    (hp:p.val + lim.val  ≤  s.length) (hlim:lim.val  ≤  258) (hk0:k0.val  ≤  2 ^ 31) :
    slot.Z219_loop s p k0 depth prev ml md lim cur best cnt steps ⦃ Y112P0! ⦄ := by
  have hws := Submission.EA.dp_WN_val
  rw [slot.Z219_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, _, st) => depth.val - st.val)
    (inv := fun _ => True)
  · rintro ⟨ml', md', cur', best', cnt', st'⟩ _
    simp only [slot.Z219_loop.body]
    step*
    apply WP.spec_bind (Pₘ := fun _ => True)
    · repeat' (split <;> step*)
      all_goals scalar_tac
    rintro ⟨ml1, md1, best1, cnt1⟩ _
    step*
    all_goals scalar_tac
  · trivial
set_option hygiene false in
local notation "Y127U30!" q0__:max => (by
  have hws := Submission.EA.dp_WN_val
  have hhs := Submission.EA.C_HS_bounds
  rw [q0__]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac)
@[local step]
theorem u555 (s:I) (p key k0 best0 depth head prev ml md) (hp:p.val < s.length) (hk0:k0.val  ≤  2 ^ 31) :
    slot.Z219 s p key k0 best0 depth head prev ml md ⦃ Y112P0! ⦄ := Y127U30! slot.Z219
@[local step]
theorem u556 (kids) (which:R) (idx v) (hw:which.val  ≤  1) :
    slot.Z241 kids which idx v ⦃ Y112P0! ⦄ := by
  have hws := Submission.EA.dp_WN_val
  have hks := EA.u26
  rw [slot.Z241]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac
@[local step]
theorem u557 (back) (s:I) (p depth kids ml md) (lim cur lw li gw gi llen glen:R)
    (best cnt steps i)
    (hp:p.val + lim.val  ≤  s.length) (hlim:lim.val  ≤  258) (hlw:lw.val  ≤  1) (hgw:gw.val  ≤  1)
    (hll:llen.val  ≤  lim.val) (hgl:glen.val  ≤  lim.val) :
    slot.Z218_loop back s p depth kids ml md lim cur lw li gw gi llen glen best cnt steps i ⦃ Y112P0! ⦄ := by
  have hws := Submission.EA.dp_WN_val
  have hks := EA.u26
  rw [slot.Z218_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, _, _, _, _, _, _, _, _, st) => depth.val - st.val)
    (inv := fun (_, _, _, _, lw', _, gw', _, ll', gl', _, _, _) => lw'.val  ≤  1  ∧  gw'.val  ≤  1  ∧ 
      ll'.val  ≤  lim.val  ∧  gl'.val  ≤  lim.val)
  · rintro ⟨kids', ml', md', cur', lw', li', gw', gi', ll', gl', best', cnt', st'⟩ ⟨h1, h2, h3, h4⟩
    simp only [slot.Z218_loop.body]
    step*
    apply WP.spec_bind (Pₘ := fun (x:R) => x.val  ≤  lim.val)
    · split <;> step*
      all_goals scalar_tac
    rintro k0 hk0
    step*
    apply WP.spec_bind (Pₘ := fun _ => True)
    · repeat' (split <;> step*)
      all_goals scalar_tac
    rintro ⟨ml1, md1, best1, cnt1⟩ _
    step*
    apply WP.spec_bind (Pₘ := fun (x:Std.Array W 65536#usize  ×  R  ×  R  ×  R  × 
        R  ×  R  ×  R  ×  R) =>
      x.2.2.1.val  ≤  1  ∧  x.2.2.2.2.1.val  ≤  1  ∧  x.2.2.2.2.2.2.1.val  ≤  lim.val  ∧  x.2.2.2.2.2.2.2.val  ≤  lim.val)
    · split <;> step*
      all_goals scalar_tac
    rintro ⟨kids1, cur1, lw1, li1, gw1, gi1, llen1, glen1⟩ ⟨h5, h6, h7, h8⟩
    step*
    all_goals scalar_tac
  · exact ⟨hlw, hgw, hll, hgl⟩
@[local step]
theorem u558 (s:I) (p h depth head kids ml md) (hp:p.val < s.length) :
    slot.Z218 s p h depth head kids ml md ⦃ Y112P0! ⦄ := Y127U30! slot.Z218
@[local step]
theorem u559 (s:I) (n key:R) (run run2 q:R) (hn:n.val = s.length)
    (hrun:run.val  ≤  q.val) (hrun2:run2.val  ≤  q.val) (hq:q.val  ≤  7) :
    slot.Z227_loop0 s n key run run2 q ⦃ fun r => r.2.1.val  ≤  7  ∧  r.2.2.val  ≤  7 ⦄ := by
  rw [slot.Z227_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, q') => 7 - q'.val)
    (inv := fun (_, r1, r2, q') => r1.val  ≤  q'.val  ∧  r2.val  ≤  q'.val  ∧  q'.val  ≤  7)
  · rintro ⟨k', r1, r2, q'⟩ ⟨h1, h2, h3⟩
    simp only [slot.Z227_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact ⟨hrun, hrun2, hq⟩
@[local step]
theorem u560 (s:I) (clist) (depth_lo n:R) (head8 prev8 head3 kids ml md)
    (key run run2 p skip_to:R)
    (hn:n.val = s.length) (hn26:n.val < 67108864) (hrun:run.val  ≤  p.val + 7) (hrun2:run2.val  ≤  p.val + 7)
    (hp:p.val  ≤  n.val) (hcl:clist.length  ≤  34 * p.val) :
    slot.Z227_loop1 s clist depth_lo n head8 prev8 head3 kids ml md key run run2 p skip_to ⦃ fun r =>
      r.length  ≤  34 * n.val ⦄ := by
  have hws := Submission.EA.dp_WN_val
  have hhs := Submission.EA.C_HS_bounds
  have hkp := EA.u295
  have hup := EA.u304
  rw [slot.Z227_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, _, _, _, _, _, _, p', _) => n.val - p'.val)
    (inv := fun (c', _, _, _, _, _, _, _, r1, r2, p', _) => r1.val  ≤  p'.val + 7  ∧  r2.val  ≤  p'.val + 7  ∧ 
      p'.val  ≤  n.val  ∧  c'.length  ≤  34 * p'.val)
  · rintro ⟨c', h8', pv8', h3', kids', ml', md', key', r1, r2, p', sk'⟩ ⟨h1, h2, h3, h4⟩
    unfold slot.Z227_loop1.body
    step*
    apply WP.spec_bind (Pₘ := fun (x:R  ×  R  ×  R) =>
      x.2.1.val  ≤  p'.val + 8  ∧  x.2.2.val  ≤  p'.val + 8)
    · repeat' (split <;> step*)
      all_goals scalar_tac
    rintro ⟨key1, run1, run21⟩ ⟨hr1, hr2⟩
    step*
    apply WP.spec_bind (Pₘ := fun (x:alloc.vec.Vec W  ×  Std.Array W 65536#usize  × 
        Std.Array W 32768#usize  ×  Std.Array W 65536#usize  ×  Std.Array W 65536#usize  × 
        Std.Array W 64#usize  ×  Std.Array W 64#usize  ×  R) =>
      x.1.length  ≤  c'.length + 34)
    · apply EA.u111
      · intro hc
        step*
        · -- a lower-case letter: binary tree on 3-byte keys
          apply WP.spec_bind (Pₘ := fun (x:alloc.vec.Vec W  ×  _) => x.1.length  ≤  c'.length + 34)
          · apply EA.u111
            · intro hs
              step*
              apply WP.spec_bind (Pₘ := fun (x:alloc.vec.Vec W  ×  _) => x.1.length  ≤  c'.length + 34)
              · apply EA.u111
                · intro hcnt
                  step*
                  apply EA.u320 <;> intro _ <;> step*
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
          · apply EA.u111
            · -- a run of at least 8 nucleotides: exact 8-mer chains
              intro hr
              apply WP.spec_bind (Pₘ := fun (x:alloc.vec.Vec W  ×  _) => x.1.length  ≤  c'.length + 34)
              · apply EA.u111
                · intro hs
                  step*
                  apply WP.spec_bind (Pₘ := fun (x:alloc.vec.Vec W  ×  _) => x.1.length  ≤  c'.length + 34)
                  · apply EA.u111
                    · intro hcnt
                      step*
                      apply EA.u320 <;> intro _ <;> step*
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
              · apply EA.u111
                · intro hr2
                  step*
                  apply WP.spec_bind (Pₘ := fun (x:alloc.vec.Vec W  ×  _) => x.1.length  ≤  c'.length + 34)
                  · apply EA.u111
                    · intro hcnt
                      step*
                      apply EA.u320 <;> intro _ <;> step*
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
          · apply EA.u111
            · -- a run of at least 8 nucleotides: exact 8-mer chains
              intro hr
              apply WP.spec_bind (Pₘ := fun (x:alloc.vec.Vec W  ×  _) => x.1.length  ≤  c'.length + 34)
              · apply EA.u111
                · intro hs
                  step*
                  apply WP.spec_bind (Pₘ := fun (x:alloc.vec.Vec W  ×  _) => x.1.length  ≤  c'.length + 34)
                  · apply EA.u111
                    · intro hcnt
                      step*
                      apply EA.u320 <;> intro _ <;> step*
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
              · apply EA.u111
                · intro hr2
                  step*
                  apply WP.spec_bind (Pₘ := fun (x:alloc.vec.Vec W  ×  _) => x.1.length  ≤  c'.length + 34)
                  · apply EA.u111
                    · intro hcnt
                      step*
                      apply EA.u320 <;> intro _ <;> step*
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
    all_goals scalar_tac
  · exact ⟨hrun, hrun2, hp, hcl⟩
@[local step]
theorem u561 (s:I) (clist) (depth_lo) (hn26:s.length < 67108864) (hcl:clist.length = 0) :
    slot.Z227 s clist depth_lo ⦃ fun r => r.length  ≤  34 * s.length ⦄ := by
  rw [slot.Z227]
  step*
@[local step]
theorem u562 (s:I) (p:R) (hp:p.val  ≤  2 ^ 31):slot.Z246 s p ⦃ Y112P0! ⦄ := Y127U1! slot.Z246
@[local step]
theorem u563 (s:I) (clist) (chain depth n:R) (head lt kids ml md)
    (p skip_to pend:R)
    (hn:n.val = s.length) (hn26:n.val < 67108864) (hp:p.val  ≤  n.val) (hcl:clist.length  ≤  34 * p.val) :
    slot.Z226_loop s clist chain depth n head lt kids ml md p skip_to pend ⦃ fun r => r.length  ≤  34 * n.val ⦄ := by
  have hws := Submission.EA.dp_WN_val
  have hhs := Submission.EA.C_HS_bounds
  have hkp := EA.u295
  rw [slot.Z226_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, _, _, p', _, _) => n.val - p'.val)
    (inv := fun (c', _, _, _, _, _, p', _, _) => p'.val  ≤  n.val  ∧  c'.length  ≤  34 * p'.val)
  · rintro ⟨c', hd', lt', kids', ml', md', p', sk', pe'⟩ ⟨h1, h2⟩
    unfold slot.Z226_loop.body
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
theorem u564 (s:I) (clist chain depth) (hn26:s.length < 67108864) (hcl:clist.length = 0) :
    slot.Z226 s clist chain depth ⦃ fun r => r.length  ≤  34 * s.length ⦄ := by
  rw [slot.Z226]
  step*
set_option hygiene false in
local notation "Y127U31!" q0__:max q1__:max => (by
  have h1 := Submission.EA.C_UNUSED_LIT_le
  have h2 := Submission.EA.C_UNUSED_DIST_le
  have h3 := Submission.EA.C_STOP_DIV_pos
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
@[local step]
theorem u565 (input:I) (out min_dna dna) (clist:alloc.vec.Vec W) (models)
    (bstart:alloc.vec.Vec W) (passes) (tax tokpen:W) (last_est pass)
    (hn26:input.length < 67108864) (htax:tax.val  ≤  65536) (htok:tokpen.val  ≤  65536)
    (hnb:bstart.length  ≤  1048576) (hcl:clist.length < 4294967295) :
    slot.Z224_loop0 input out min_dna dna clist models bstart passes tax tokpen last_est pass ⦃ Y112P0! ⦄ := Y127U31! slot.Z224_loop0 slot.Z224_loop0.body
@[local step]
theorem u566 (input:I) (out min_dna dna) (clist:alloc.vec.Vec W) (models)
    (bstart:alloc.vec.Vec W) (passes) (tax tokpen:W) (last_est pass)
    (hn26:input.length < 67108864) (htax:tax.val  ≤  65536) (htok:tokpen.val  ≤  65536)
    (hnb:bstart.length  ≤  1048576) (hcl:clist.length < 4294967295) :
    slot.Z224_loop1 input out min_dna dna clist models bstart passes tax tokpen last_est pass ⦃ Y112P0! ⦄ := Y127U31! slot.Z224_loop1 slot.Z224_loop1.body
@[local step]
theorem u567 (input:I) (out min_dna dna) (clist:alloc.vec.Vec W) (models)
    (bstart:alloc.vec.Vec W) (passes) (tax tokpen:W) (last_est pass)
    (hn26:input.length < 67108864) (htax:tax.val  ≤  65536) (htok:tokpen.val  ≤  65536)
    (hnb:bstart.length  ≤  1048576) (hcl:clist.length < 4294967295) :
    slot.Z224_loop2 input out min_dna dna clist models bstart passes tax tokpen last_est pass ⦃ Y112P0! ⦄ := Y127U31! slot.Z224_loop2 slot.Z224_loop2.body
@[local step]
theorem u568 (input:I) (out) (depth depth_lo wdp passes_w passes_bt passes_dna min_dna passes_c4:R)
    (hn:input.length < 67108864) (h1:depth.val  ≤  65536) (h2:depth_lo.val  ≤  65536) (h3:wdp.val  ≤  65536)
    (h4:passes_w.val  ≤  65536) (h5:passes_bt.val  ≤  65536) (h6:passes_dna.val  ≤  65536) (h7:min_dna.val  ≤  65536)
    (h8:passes_c4.val  ≤  65536) :
    slot.Z224 input out depth depth_lo wdp passes_w passes_bt passes_dna min_dna passes_c4 ⦃ Y112P0! ⦄ := by
  have f1 := EA.u299
  have f2 := EA.u299
  have f3 := EA.u300
  have f4 := EA.u297
  have f5 := EA.u298
  have f6 := EA.u301
  have f7 := EA.u301
  have f8 := EA.u302
  have f9 := EA.u301
  have f10 := Submission.EA.C_UNUSED_LIT_le
  have f11 := Submission.EA.C_UNUSED_DIST_le
  have f12 := EA.u303
  rw [slot.Z224]
  step*
  · -- dna = 0, few 6-byte repeats: weights DP (4-byte chains)
    apply WP.spec_bind (Pₘ := fun (x:alloc.vec.Vec W) => x.length  ≤  34 * input.length)
    · repeat' (split <;> step*)
      all_goals exact EA.u319 _
    rintro clist1 hc1
    apply WP.spec_bind (Pₘ := fun _ => True)
    · repeat' (split <;> step*)
    rintro passes _
    apply WP.spec_bind (Pₘ := fun (x:W) => x.val  ≤  65536)
    · repeat' (split <;> step*)
      all_goals scalar_tac
    rintro tax htax
    apply WP.spec_bind (Pₘ := fun (x:W) => x.val  ≤  65536)
    · repeat' (split <;> step*)
      all_goals scalar_tac
    rintro ulen hulen
    apply WP.spec_bind (Pₘ := fun (x:W) => x.val  ≤  65536)
    · repeat' (split <;> step*)
      all_goals scalar_tac
    rintro udist hudist
    apply WP.spec_bind (Pₘ := fun _ => True)
    · repeat' (split <;> step*)
    rintro gmin _
    step*
    apply WP.spec_bind (Pₘ := fun (x:alloc.vec.Vec W  ×  W) => x.2.val  ≤  65536)
    · repeat' (split <;> step*)
      all_goals scalar_tac
    rintro ⟨out1, tokpen⟩ htok
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · -- dna = 0, repetitive: tree or 4-byte chains
    apply WP.spec_bind (Pₘ := fun _ => True)
    · repeat' (split <;> step*)
      all_goals scalar_tac
    rintro chain4 _
    step*
    apply WP.spec_bind (Pₘ := fun (x:alloc.vec.Vec W) => x.length  ≤  34 * input.length)
    · repeat' (split <;> step*)
      all_goals exact EA.u319 _
    rintro clist1 hc1
    apply WP.spec_bind (Pₘ := fun _ => True)
    · repeat' (split <;> step*)
    rintro passes _
    apply WP.spec_bind (Pₘ := fun (x:W) => x.val  ≤  65536)
    · repeat' (split <;> step*)
      all_goals scalar_tac
    rintro tax htax
    apply WP.spec_bind (Pₘ := fun (x:W) => x.val  ≤  65536)
    · repeat' (split <;> step*)
      all_goals scalar_tac
    rintro ulen hulen
    apply WP.spec_bind (Pₘ := fun (x:W) => x.val  ≤  65536)
    · repeat' (split <;> step*)
      all_goals scalar_tac
    rintro udist hudist
    apply WP.spec_bind (Pₘ := fun _ => True)
    · repeat' (split <;> step*)
    rintro gmin _
    step*
    apply WP.spec_bind (Pₘ := fun (x:alloc.vec.Vec W  ×  W) => x.2.val  ≤  65536)
    · repeat' (split <;> step*)
      all_goals scalar_tac
    rintro ⟨out1, tokpen⟩ htok
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · -- DNA
    apply WP.spec_bind (Pₘ := fun (x:alloc.vec.Vec W) => x.length  ≤  34 * input.length)
    · repeat' (split <;> step*)
      all_goals exact EA.u319 _
    rintro clist1 hc1
    apply WP.spec_bind (Pₘ := fun _ => True)
    · repeat' (split <;> step*)
    rintro passes _
    apply WP.spec_bind (Pₘ := fun (x:W) => x.val  ≤  65536)
    · repeat' (split <;> step*)
      all_goals scalar_tac
    rintro tax htax
    apply WP.spec_bind (Pₘ := fun (x:W) => x.val  ≤  65536)
    · repeat' (split <;> step*)
      all_goals scalar_tac
    rintro ulen hulen
    apply WP.spec_bind (Pₘ := fun (x:W) => x.val  ≤  65536)
    · repeat' (split <;> step*)
      all_goals scalar_tac
    rintro udist hudist
    apply WP.spec_bind (Pₘ := fun _ => True)
    · repeat' (split <;> step*)
    rintro gmin _
    step*
    apply WP.spec_bind (Pₘ := fun (x:alloc.vec.Vec W  ×  W) => x.2.val  ≤  65536)
    · repeat' (split <;> step*)
      all_goals scalar_tac
    rintro ⟨out1, tokpen⟩ htok
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
theorem spine_CFG_le:∀ r ∈ slot.Z73.val, ∀ x ∈ r.val, x.val  ≤  65536 := by
  unfold slot.Z73;decide
theorem spine_CFG_skip:∀ r ∈ slot.Z73.val, (r.val[0]!).val = 0  →  3  ≤  (r.val[2]!).val := by
  unfold slot.Z73;decide
@[local step]
theorem u569 (input:I) (k) (hn:input.length < 67108864) :
    slot.Z251 input k ⦃ Y112P0! ⦄ := Y127U29! slot.Z251 slot.Z73.val
@[local step]
theorem u570 (input) (k:R):slot.Z249 input k ⦃ Y112P0! ⦄ := by
  rw [slot.Z249]
  step*
theorem u571 (input:I) (out:U) (k:R)
    (hlen:input.length  ≤  out.length) :
    slot.Z248 input out k ⦃ Y112P1! ⦄ := by
  rw [slot.Z248]
  step*
  refine ⟨by assumption, by assumption, ?_⟩
  unfold LZ77.Valid
  assumption
attribute [local step] u571
@[local step]
theorem u572 (input:I) (out:U) (mode:R) (hlen:input.length  ≤  out.length):slot.Z250 input out mode ⦃ Y112P1! ⦄ := by
 rw [slot.Z250]
 step*
 all_goals repeat' (split <;> step*)
end EC
namespace ED
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
theorem u573 (x y:Nat):x &&& y  ≤  y := Nat.and_le_right
@[local scalar_tac x >>> y]
theorem u574 (x y:Nat):x >>> y  ≤  x := Nat.shiftRight_le x y
@[local scalar_tac System.Platform.numBits]
theorem u575:32  ≤  System.Platform.numBits := EA.u4
@[local scalar_tac core.num.U32.leading_zeros x]
theorem u576 (x:W) :
    (core.num.U32.leading_zeros x).val  ≤  32  ∧ 
      (x.val = 0  ∨  (core.num.U32.leading_zeros x).val  ≤  31) := Y127U4!
@[local scalar_tac core.num.U64.leading_zeros x]
theorem u577 (x:Std.U64):(core.num.U64.leading_zeros x).val  ≤  64 := EA.u12 x
theorem u578:Std.Usize.max + 1 = Usize.size := by
  simp only [Std.Usize.max, Usize.size, Std.Usize.numBits, UScalar.size, UScalarTy.numBits]
  have := Nat.one_le_two_pow (n := System.Platform.numBits)
  omega
theorem u579 (x:R) (h:x.val + 1  ≤  Std.Usize.max) :
    (core.num.Usize.wrapping_add x 1#usize).val = x.val + 1 := by
  have hmx := u578
  have h1:(1#usize).val = 1 := by simp
  rw [core.num.Usize.wrapping_add_val_eq, UScalar.size_UScalarTyUsize, h1, Nat.mod_eq_of_lt (by omega)]
theorem u580 (x b:R) (h:x.val + b.val + 1  ≤  Std.Usize.max) (hb:8  ≤  b.val) :
    (core.num.Usize.wrapping_sub (core.num.Usize.wrapping_add x b) 7#usize).val = x.val + b.val - 7 := by
  have hmx := u578
  have e1:(core.num.Usize.wrapping_add x b).val = x.val + b.val := by
    rw [core.num.Usize.wrapping_add_val_eq, UScalar.size_UScalarTyUsize, Nat.mod_eq_of_lt (by omega)]
  rw [core.num.Usize.wrapping_sub_val_eq, UScalar.size_UScalarTyUsize, e1]
  have h7:(7#usize).val = 7 := by simp
  rw [h7, show x.val + b.val + (Usize.size - 7) = (x.val + b.val - 7) + Usize.size by omega,
    Nat.add_mod_right, Nat.mod_eq_of_lt (by omega)]
theorem u581 {α:Type} (c:Prop) [Decidable c] (a b:α) (P:α  →  Prop) (ha:P a) (hb:P b) :
    (if c then (ok a:Result α) else ok b) ⦃ P ⦄ := by
  split <;> simpa [Std.WP.spec_ok]
theorem u582 {α:Type} (c:Prop) [Decidable c] (a b:α) (P:α  →  Prop) (ha:c  →  P a)
    (hb:¬c  →  P b):(if c then (ok a:Result α) else ok b) ⦃ P ⦄ := by
  split
  · simpa [Std.WP.spec_ok] using ha (by assumption)
  · simpa [Std.WP.spec_ok] using hb (by assumption)
@[irreducible] def u583 (input:I) (p:Nat):Nat :=
  (input.val[p]!).val * 2^56 + (input.val[p + 1]!).val * 2^48 + (input.val[p + 2]!).val * 2^40
    + (input.val[p + 3]!).val * 2^32 + (input.val[p + 4]!).val * 2^24
    + (input.val[p + 5]!).val * 2^16 + (input.val[p + 6]!).val * 2^8 + (input.val[p + 7]!).val
theorem u584 (input:I) (p k:Nat) (hk:k < 8) :
    (input.val[p + k]!).val = u583 input p / 256 ^ (7 - k) % 256 := by
  have := EA.u265 (input.val[p]!);have := EA.u265 (input.val[p+1]!)
  have := EA.u265 (input.val[p+2]!);have := EA.u265 (input.val[p+3]!)
  have := EA.u265 (input.val[p+4]!);have := EA.u265 (input.val[p+5]!)
  have := EA.u265 (input.val[p+6]!);have := EA.u265 (input.val[p+7]!)
  simp only [u583]
  rcases (show k = 0  ∨  k = 1  ∨  k = 2  ∨  k = 3  ∨  k = 4  ∨  k = 5  ∨  k = 6  ∨  k = 7 by omega) with
    rfl | rfl | rfl | rfl | rfl | rfl | rfl | rfl <;> simp only [Nat.add_zero, Nat.pow_zero, Nat.pow_succ, Nat.one_mul,
    Nat.sub_self, Nat.reduceSub] <;> omega
theorem u585 (input:I) (a b d:Nat) (hd:d  ≤  8)
    (h:u583 input a / 2 ^ (64 - 8 * d) = u583 input b / 2 ^ (64 - 8 * d)) :
    ∀ k, k < d  →  input.val[b + k]! = input.val[a + k]! := by
  intro k hk
  have e:(256:Nat) ^ (7 - k) = 2 ^ (64 - 8 * d) * 2 ^ (8 * (d - 1 - k)) := by
    rw [← pow_add, show (256:Nat) = 2 ^ 8 by norm_num, ← pow_mul]
    congr 1;omega
  have key:u583 input a / 256 ^ (7 - k) = u583 input b / 256 ^ (7 - k) := by
    rw [e, ← Nat.div_div_eq_div_mul, ← Nat.div_div_eq_div_mul, h]
  have ha := u584 input a k (by omega)
  have hb := u584 input b k (by omega)
  rw [key] at ha
  (subst_vars;scalar_tac (simpAllMaxSteps := 0))
theorem Matches.u586 {input:I} {a b l d:Nat} (h:Matches input a b l)
    (hd:d  ≤  8)
    (hw:u583 input (a + l) / 2 ^ (64 - 8 * d) = u583 input (b + l) / 2 ^ (64 - 8 * d)) :
    Matches input a b (l + d) := by
  intro k hk
  by_cases hkl:k < l
  · exact h k hkl
  · have := u585 input (a + l) (b + l) d hd hw (k - l) (by omega)
    rw [show b + l + (k - l) = b + k by omega, show a + l + (k - l) = a + k by omega] at this
    exact this
theorem u587 {x t:Nat} (m:Nat) (hx:x % 2 ^ m = 0) (ht:t < 2 ^ m) :
    x ||| t = x + t := by
  have h := Nat.two_pow_add_eq_or_of_lt ht (x / 2 ^ m)
  have hx':2 ^ m * (x / 2 ^ m) = x := by
    have := Nat.div_add_mod x (2 ^ m);omega
  rw [hx'] at h
  exact h.symm
theorem u588 {x:Nat} (k:Nat) (hx:x < 256) (hk:k  ≤  56) :
    x <<< k % U64.size = x * 2 ^ k := by
  rw [Nat.shiftLeft_eq, U64.size_def]
  apply Nat.mod_eq_of_lt
  have:2 ^ k  ≤  2 ^ 56 := Nat.pow_le_pow_right (by norm_num) hk
  have:x * 2 ^ k < 256 * 2 ^ 56 := by
    calc x * 2 ^ k < 256 * 2 ^ k := by
          apply Nat.mul_lt_mul_of_pos_right hx (Nat.two_pow_pos _)
      _  ≤  256 * 2 ^ 56 := Nat.mul_le_mul_left _ this
  simp only [U64.numBits] at *
  omega
theorem u589 {a b c d e f g h:Nat} (ha:a < 256) (hb:b < 256) (hc:c < 256)
    (hd:d < 256) (he:e < 256) (hf:f < 256) (hg:g < 256) (hh:h < 256) :
    (a <<< 56 % U64.size ||| b <<< 48 % U64.size ||| c <<< 40 % U64.size |||
      d <<< 32 % U64.size ||| e <<< 24 % U64.size ||| f <<< 16 % U64.size |||
      g <<< 8 % U64.size ||| h) =
    a * 2^56 + b * 2^48 + c * 2^40 + d * 2^32 + e * 2^24 + f * 2^16 + g * 2^8 + h := by
  rw [u588 56 ha (by norm_num), u588 48 hb (by norm_num), u588 40 hc (by norm_num),
    u588 32 hd (by norm_num), u588 24 he (by norm_num), u588 16 hf (by norm_num),
    u588 8 hg (by norm_num)]
  rw [u587 56 (x := a * 2^56) (t := b * 2^48) (by omega) (by omega)]
  rw [u587 48 (x := a * 2^56 + b * 2^48) (t := c * 2^40) (by omega) (by omega)]
  rw [u587 40 (x := a * 2^56 + b * 2^48 + c * 2^40) (t := d * 2^32) (by omega)
    (by omega)]
  rw [u587 32 (x := a * 2^56 + b * 2^48 + c * 2^40 + d * 2^32) (t := e * 2^24)
    (by omega) (by omega)]
  rw [u587 24 (x := a * 2^56 + b * 2^48 + c * 2^40 + d * 2^32 + e * 2^24)
    (t := f * 2^16) (by omega) (by omega)]
  rw [u587 16
    (x := a * 2^56 + b * 2^48 + c * 2^40 + d * 2^32 + e * 2^24 + f * 2^16)
    (t := g * 2^8) (by omega) (by omega)]
  rw [u587 8
    (x := a * 2^56 + b * 2^48 + c * 2^40 + d * 2^32 + e * 2^24 + f * 2^16 + g * 2^8)
    (t := h) (by omega) (by omega)]
theorem u590 (z:BitVec 64) (h:z ≠ 0):BitVec.leadingZeros z < 64 := by
  unfold BitVec.leadingZeros
  simp only [h, if_false]
  omega
theorem u591 (x:Std.U64) :
    lift (core.num.U64.leading_zeros x) ⦃ fun r => r = core.num.U64.leading_zeros x  ∧  r.val  ≤  64 ⦄ := by
  simp only [lift, Std.WP.spec_ok, true_and]
  have hle:BitVec.leadingZeros x.bv  ≤  64 := by unfold BitVec.leadingZeros;split <;> omega
  simp only [core.num.U64.leading_zeros, UScalar.val, UScalarTy.U32_numBits_eq,
    BitVec.natCast_eq_ofNat, BitVec.toNat_ofNat, Nat.reducePow]
  omega
theorem Matches.u592 {input:I} {a b k:Nat} {pa pb r k1:R}
    {x y z:Std.U64} {lz q:W}
    (h:Matches input a b k) (hpa:pa.val = a + k) (hpb:pb.val = b + k)
    (hx:x.val = u583 input pa.val) (hy:y.val = u583 input pb.val)
    (hz:z.val = (x ^^^ y).val) (hz0:¬z = 0#u64) (hlz:lz = core.num.U64.leading_zeros z)
    (hq:q.val = lz.val / 8) (hr:r = UScalar.cast .Usize q) (hk1:k1.val = k + r.val) :
    Matches input a b k1.val  ∧  k1.val < k + 8 := by
  have hbv:z.bv ≠ 0 := by
    intro h0;apply hz0;exact UScalar.eq_of_val_eq (by simp [UScalar.val, h0])
  have hlt:BitVec.leadingZeros z.bv < 64 := u590 z.bv hbv
  have hrv:r.val = BitVec.leadingZeros z.bv / 8 := by
    rw [hr, U32.cast_Usize_val_eq, hq, hlz, EA.u11]
  rw [hpa] at hx;rw [hpb] at hy
  refine ⟨?_, by omega⟩
  rw [hk1, hrv]
  have hle:BitVec.leadingZeros z.bv  ≤  64 := by unfold BitVec.leadingZeros;split <;> omega
  apply Matches.u586 h (by omega)
  rw [← hx, ← hy]
  apply EA.u273
  rw [← UScalar.val_xor, ← hz]
  exact EA.u274 z.bv
theorem Matches.u593 {input:I} {a b k:Nat} {pa pb k1:R}
    {x y z:Std.U64}
    (h:Matches input a b k) (hpa:pa.val = a + k) (hpb:pb.val = b + k)
    (hx:x.val = u583 input pa.val) (hy:y.val = u583 input pb.val)
    (hz:z.val = (x ^^^ y).val) (hz0:z = 0#u64) (hk1:k1.val = k + 8) :
    Matches input a b k1.val := by
  have hxy:x.val = y.val := by
    apply EA.u272
    rw [← UScalar.val_xor, ← hz, hz0];rfl
  rw [hpa] at hx;rw [hpb] at hy
  rw [hk1]
  apply Matches.u586 h (le_refl 8)
  rw [← hx, ← hy, hxy]
theorem Matches.u594 {input:I} {a b l:Nat} {pa pb l1:R}
    {x y:Std.U8} (h:Matches input a b l) (hpa:pa.val = a + l) (hpb:pb.val = b + l)
    (hpa':pa.val < input.val.length) (hpb':pb.val < input.val.length)
    (hx:x = input.val[pa.val]) (hy:y = input.val[pb.val]) (hxy:x = y)
    (hl1:l1.val = l + 1):Matches input a b l1.val := by
  rw [hl1]
  apply LZ77.Matches.succ h
  rw [← hpa, ← hpb, getElem!_pos input.val pa.val hpa', getElem!_pos input.val pb.val hpb',
    ← hx, ← hy, hxy]
theorem Matches.u595 {input:I} {a b n m:Nat} (h:Matches input a b n)
    (hm:m = n):Matches input a b m := by subst hm;exact h
theorem Matches.u596 {input:I} {a b k:Nat} {pa pb k1:R}
    {x y:Std.U64}
    (h:Matches input a b k) (hpa:pa.val = a + k) (hpb:pb.val = b + k)
    (hx:x.val = u583 input pa.val) (hy:y.val = u583 input pb.val)
    (hxy:x = y) (hk1:k1.val = k + 8) :
    Matches input a b k1.val := by
  rw [hpa] at hx;rw [hpb] at hy
  rw [hk1]
  apply Matches.u586 h (le_refl 8)
  rw [← hx, ← hy, hxy]
theorem Matches.u597 {input:I} {a b k len:Nat} {pa pb:R}
    {x y z w:Std.U64} {sh:W}
    (h:Matches input a b k) (hpa:pa.val = a + k) (hpb:pb.val = b + k)
    (hx:x.val = u583 input pa.val) (hy:y.val = u583 input pb.val)
    (hz:z.val = (x ^^^ y).val) (hw:w.val = z.val >>> sh.val) (hw0:¬(w != 0#u64) = true)
    (hsh:sh.val = 64 - 8 * (len - k)) (hk:k < len) (hlen:len < k + 8) :
    Matches input a b len := by
  have hw0:w.val = 0 := by simpa using hw0
  rw [hpa] at hx;rw [hpb] at hy
  have := Matches.u586 (d := len - k) h (by omega) (by
    rw [← hx, ← hy, ← hsh]
    have h0:(x.val ^^^ y.val) >>> sh.val = 0 := by rw [← UScalar.val_xor, ← hz, ← hw, hw0]
    rw [Nat.shiftRight_xor_distrib] at h0
    have := EA.u272 h0
    simpa [Nat.shiftRight_eq_div_pow] using this)
  rw [show k + (len - k) = len by omega] at this
  exact this
theorem u598 (x:W) (k:Nat) (hk:k < 32) (hx:2 ^ k  ≤  x.val) :
    (core.num.U32.leading_zeros x).val  ≤  31 - k := by
  have hne:x.bv ≠ 0 := by
    intro h0
    have:x.val = 0 := by simp [UScalar.val, h0]
    have:0 < 2 ^ k := Nat.two_pow_pos k
    omega
  have hlog:k  ≤  Nat.log 2 x.bv.toNat := by
    apply Nat.le_log_of_pow_le (by norm_num)
    have:x.val = x.bv.toNat := rfl
    omega
  have hle:BitVec.leadingZeros x.bv  ≤  32 := by unfold BitVec.leadingZeros;split <;> omega
  have hv:(core.num.U32.leading_zeros x).val = BitVec.leadingZeros x.bv := by
    simp only [core.num.U32.leading_zeros, UScalar.val, UScalarTy.U32_numBits_eq,
      BitVec.natCast_eq_ofNat, BitVec.toNat_ofNat, Nat.reducePow]
    omega
  rw [hv]
  unfold BitVec.leadingZeros
  simp only [hne, if_false]
  omega
theorem u599 (x:W) :
    lift (core.num.U32.leading_zeros x) ⦃ fun r => r = core.num.U32.leading_zeros x  ∧ 
      (4  ≤  x.val  →  r.val  ≤  29)  ∧  (8  ≤  x.val  →  r.val  ≤  28) ⦄ := by
  simp only [lift, Std.WP.spec_ok, true_and]
  exact ⟨fun h => u598 x 2 (by norm_num) (by simpa using h),
    fun h => u598 x 3 (by norm_num) (by simpa using h)⟩
theorem u600 {ty:UScalarTy} (x:UScalar ty) (h:x.val  ≤  2147483647) :
    lift (UScalar.hcast .I32 x) ⦃ fun y => y.val = x.val ⦄ :=
  UScalar.hcast_inBounds_spec .I32 x (by simp [I32.max_def, I32.numBits];omega)
theorem u601 {ty:UScalarTy} (x:UScalar ty) (h:x.val  ≤  2147483647) :
    (UScalar.hcast .I32 x).val = x.val := by
  have := u600 x h
  simpa [lift] using this
theorem u602:-500000000  ≤  slot.Z77.val  ∧  slot.Z77.val  ≤  500000000 := by
  unfold slot.Z77
  simp
theorem u603:-500000000  ≤  slot.Z81.val  ∧  slot.Z81.val  ≤  500000000 := by
  unfold slot.Z81
  simp
theorem u604 {i hlit:Int} {l:Nat} (hi:i = (l:Int)) (hl:l  ≤  258) (h0:0  ≤  hlit)
    (h1:hlit  ≤  1000000):0  ≤  i * hlit  ∧  i * hlit  ≤  258000000 := by
  subst hi
  refine ⟨Int.mul_nonneg (by omega) h0, ?_⟩
  calc (l:Int) * hlit  ≤  258 * hlit := Int.mul_le_mul_of_nonneg_right (by omega) h0
    _  ≤  258000000 := by omega
def u605 {N:R} (head:C N) (B:Nat):Prop :=
  ∀ j:Nat, j < head.val.length  →  (head.val[j]!).val  ≤  B
theorem AHeadBound.u606 {N:R} {head:C N} {B B':Nat}
    (h:u605 head B) (hB:B  ≤  B'):u605 head B' := fun j hj => le_trans (h j hj) hB
theorem AHeadBound.u607 (N:R):u605 (Std.Array.repeat N 0#u32) 0 := by
  intro j hj
  rw [Std.Array.repeat_val] at hj ⊢
  rw [List.getElem!_eq_getElem?_getD, List.getElem?_replicate_of_lt (by simpa using hj)]
  rfl
theorem AHeadBound.u608 {N:R} {head:C N} {B:Nat} (h:u605 head B)
    (a:R) (v:W) (hv:v.val  ≤  B):u605 (head.set a v) B := by
  intro j hj
  rw [Std.Array.set_val_eq] at hj ⊢
  rw [List.length_set] at hj
  by_cases hja:a.val = j
  · subst hja
    rw [List.getElem!_eq_getElem?_getD, List.getElem?_set_self hj]
    exact hv
  · rw [List.getElem!_eq_getElem?_getD, List.getElem?_set_ne hja, ← List.getElem!_eq_getElem?_getD]
    exact h j hj
theorem AHeadBound.u609 {N:R} {head head1:C N} {B:Nat}
    {a i:R} {v:W} (h:u605 head B) (hv:v = UScalar.cast .U32 i)
    (hi:i.val  ≤  B) (h1:head1 = head.set a v):u605 head1 B := by
  subst h1
  apply AHeadBound.u608 h a v
  rw [hv]
  have:(UScalar.cast .U32 i).val = i.val % 2 ^ 32 := by
    simp only [UScalar.cast_val_eq, UScalarTy.U32_numBits_eq]
  rw [this]
  exact le_trans (Nat.mod_le _ _) hi
theorem AHeadBound.u610 {N:R} {head:C N} {B:Nat} (h:u605 head B)
    (a:R) (x:W) (ha:a.val < head.val.length) (hx:x = head.val[a.val]) :
    x.val  ≤  B := by
  have := h a.val ha
  rw [getElem!_pos head.val a.val ha, ← hx] at this
  exact this
theorem u611 {x:W} {y:R} {B:Nat} (h:y = UScalar.cast .Usize x)
    (hx:x.val  ≤  B):y.val  ≤  B := by
  rw [h, U32.cast_Usize_val_eq];exact hx
def u612 (s:I) (p cap best bd:Nat):Prop :=
  bd = 0  ∨  (1  ≤  bd  ∧  bd  ≤  32768  ∧  bd  ≤  p  ∧  best  ≤  cap  ∧  Matches s (p - bd) p best)
theorem u613 {p c d i:R} (hc:c.val  ≤  p.val)
    (hd:d = core.num.Usize.wrapping_sub p c) (hi:i = core.num.Usize.wrapping_sub d 1#usize)
    (hlt:i < 32768#usize):d.val = p.val - c.val  ∧  1  ≤  d.val  ∧  d.val  ≤  32768 := by
  have hsz:4294967296  ≤  Usize.size := by (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  have hpl:p.val < Usize.size := by (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  have hdv:d.val = p.val - c.val := by
    rw [hd, core.num.Usize.wrapping_sub_val_eq, UScalar.size_UScalarTyUsize]
    rw [show p.val + (Usize.size - c.val) = (p.val - c.val) + Usize.size by omega,
      Nat.add_mod_right, Nat.mod_eq_of_lt (by omega)]
  have hiv:i.val < 32768 := by (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  have hdl:d.val < Usize.size := by omega
  rw [hi, core.num.Usize.wrapping_sub_val_eq, UScalar.size_UScalarTyUsize] at hiv
  simp only [show (1#usize).val = 1 by simp] at hiv
  refine ⟨hdv, ?_, ?_⟩
  · by_contra h0
    have:d.val = 0 := by omega
    rw [this, Nat.zero_add, Nat.mod_eq_of_lt (by omega)] at hiv
    omega
  · by_cases h0:d.val = 0
    · rw [h0, Nat.zero_add, Nat.mod_eq_of_lt (by omega)] at hiv
      omega
    · rw [show d.val + (Usize.size - 1) = (d.val - 1) + Usize.size by omega, Nat.add_mod_right,
        Nat.mod_eq_of_lt (by omega)] at hiv
      omega
theorem ACand.u614 {s:I} {p c d i l cap:R} (hc:c.val  ≤  p.val)
    (hd:d = core.num.Usize.wrapping_sub p c) (hi:i = core.num.Usize.wrapping_sub d 1#usize)
    (hlt:i < 32768#usize) (hl:l.val  ≤  cap.val) (hm:Matches s c.val p.val l.val) :
    u612 s p.val cap.val l.val d.val := by
  obtain ⟨hdv, hd1, hd2⟩ := u613 hc hd hi hlt
  refine Or.inr ⟨hd1, hd2, by omega, hl, ?_⟩
  rw [show p.val - d.val = c.val by omega]
  exact hm
theorem u615 {p c d i:R} (hc:c.val  ≤  p.val + 2)
    (hd:d = core.num.Usize.wrapping_sub p c) (hi:i = core.num.Usize.wrapping_sub d 1#usize)
    (hlt:i < 32768#usize):c.val  ≤  p.val := by
  by_contra hcp
  have hsz:4294967296  ≤  Usize.size := by (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  have hcl:c.val < Usize.size := by (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  have hdv:d.val = Usize.size - (c.val - p.val) := by
    rw [hd, core.num.Usize.wrapping_sub_val_eq, UScalar.size_UScalarTyUsize]
    rw [show p.val + (Usize.size - c.val) = Usize.size - (c.val - p.val) by omega,
      Nat.mod_eq_of_lt (by omega)]
  have hiv:i.val < 32768 := by (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  rw [hi, core.num.Usize.wrapping_sub_val_eq, UScalar.size_UScalarTyUsize] at hiv
  simp only [show (1#usize).val = 1 by simp] at hiv
  rw [show d.val + (Usize.size - 1) = (d.val - 1) + Usize.size by omega, Nat.add_mod_right,
    Nat.mod_eq_of_lt (by omega)] at hiv
  omega
def u616 (s:I) (p l d:Nat):Prop :=
  3  ≤  l  ∧  l  ≤  258  ∧  p + l  ≤  s.length  ∧  1  ≤  d  ∧  d  ≤  32768  ∧  d  ≤  p  ∧  Matches s (p - d) p l
def u617 (s:I) (p l d:Nat):Prop := l < 3  ∨  u616 s p l d
theorem AFoundAt.u618 {s:I} {p cap:Nat} {l d:R}
    (hc:u612 s p cap l.val d.val) (hd:¬d = 0#usize) (hcap:cap  ≤  258)
    (hpc:p + cap  ≤  s.length):u617 s p l.val d.val := by
  have hd':d.val ≠ 0 := by intro h;apply hd;exact UScalar.eq_of_val_eq (by simp [h])
  rcases hc with h0 | ⟨hd1, hd2, hdp, hl, hm⟩
  · exact absurd h0 hd'
  · rcases Nat.lt_or_ge l.val 3 with h3 | h3
    · exact Or.inl h3
    · exact Or.inr ⟨h3, by omega, by omega, hd1, hd2, hdp, hm⟩
theorem ACand.u619 {s:I} {p cap:Nat} {l d:R}
    (hc:u612 s p cap l.val d.val) (hd:¬d = 0#usize) (hcap:cap  ≤  258):l.val  ≤  258 := by
  have hd':d.val ≠ 0 := by intro h;apply hd;exact UScalar.eq_of_val_eq (by simp [h])
  rcases hc with h0 | ⟨_, _, _, hl, _⟩
  · exact absurd h0 hd'
  · omega
theorem ACand.u620 {s:I} {p cap l d:Nat} (hc:u612 s p cap l d) :
    d  ≤  32768 := by
  rcases hc with h0 | ⟨_, hd, _⟩ <;> omega
theorem AFoundAt.u621 (s:I) (p:Nat):u617 s p (0#usize).val (0#usize).val :=
  Or.inl (by simp)
theorem AFoundAt.u622 {s:I} {p l d:Nat} (hf:u617 s p l d) (h3:3  ≤  l) :
    u616 s p l d := by
  rcases hf with h | h
  · omega
  · exact h
def u623 (s:I) (p len r:Nat):Prop :=
  r = 0  ∨  (1  ≤  r  ∧  r  ≤  32768  ∧  r  ≤  p  ∧  Matches s (p - r) p len)
theorem ANear.u624 (s:I) (p len:Nat):u623 s p len (0#usize).val := Or.inl (by simp)
theorem ANear.u625 {s:I} {p c d i len r:R} (hc:c.val < p.val)
    (hd:d = core.num.Usize.wrapping_sub p c) (hi:i = core.num.Usize.wrapping_sub d 1#usize)
    (hlt:i < 32768#usize) (hsame:r.val = 1  →  Matches s c.val p.val len.val)
    (hr:r = 1#usize):u623 s p.val len.val d.val := by
  obtain ⟨hdv, hd1, hd2⟩ := u613 (le_of_lt hc) hd hi hlt
  refine Or.inr ⟨hd1, hd2, by omega, ?_⟩
  rw [show p.val - d.val = c.val by omega]
  exact hsame (by rw [hr];rfl)
theorem u626 (acc:List Nat) (d:Nat) :
    ∀ n, (LZ77.copyN acc d n).take acc.length = acc := by
  intro n
  induction n with
  | zero => simp [LZ77.copyN]
  | succ m ih =>
    simp only [LZ77.copyN]
    rw [List.take_append_of_le_length (by simp)]
    exact ih
theorem u627:∀ (ts:List Nat) (init acc:List Nat),
    ts.foldlM LZ77.emit init = some acc  →  init.length + ts.length  ≤  acc.length := by
  intro ts
  induction ts with
  | nil => intro init acc h;simp at h;subst h;simp
  | cons t ts ih =>
    intro init acc h
    simp only [List.foldlM_cons] at h
    cases he:LZ77.emit init t with
    | none => rw [he] at h;simp at h
    | some a =>
      rw [he] at h
      simp only [Option.bind_eq_bind, Option.bind_some] at h
      have h1 := ih a acc h
      have h2:init.length + 1  ≤  a.length := by
        simp only [LZ77.emit] at he
        split at he
        · simp at he;subst he;simp
        · split at he
          · split at he
            · simp at he;subst he;rw [LZ77.copyN_length];simp only [LZ77.tokLen];omega
            · simp at he
          · simp at he
      simp only [List.length_cons]
      omega
theorem u628 {ts acc:List Nat} (h:LZ77.decode ts = some acc) :
    ts.length  ≤  acc.length := by
  have := u627 ts [] acc h
  simpa using this
theorem u629 {ts:List Nat} {t:Nat} {inp:List Nat} {p:Nat}
    (hp:p  ≤  inp.length) (hd:LZ77.decode (ts ++ [t]) = some (inp.take p)) (ht:t < 256) :
    1  ≤  p  ∧  LZ77.decode ts = some (inp.take (p - 1)) := by
  rw [LZ77.decode_snoc] at hd
  cases hts:LZ77.decode ts with
  | none => rw [hts] at hd;simp at hd
  | some acc =>
    rw [hts] at hd
    simp only [Option.bind_some, LZ77.emit, if_pos ht] at hd
    have hacc:acc ++ [t] = inp.take p := Option.some.inj hd
    have hlen:acc.length + 1 = p := by
      have := congrArg List.length hacc
      simp [List.length_take] at this;omega
    refine ⟨by omega, ?_⟩
    apply congrArg some
    have := congrArg (List.take acc.length) hacc
    rw [List.take_append_of_le_length (le_refl _), List.take_length, List.take_take] at this
    rw [this, show min acc.length p = p - 1 by omega]
theorem u630 {ts:List Nat} {t:Nat} {inp:List Nat} {p:Nat}
    (hp:p  ≤  inp.length) (hd:LZ77.decode (ts ++ [t]) = some (inp.take p)) (ht:256  ≤  t) :
    LZ77.tokLen t  ≤  p  ∧  LZ77.decode ts = some (inp.take (p - LZ77.tokLen t)) := by
  rw [LZ77.decode_snoc] at hd
  cases hts:LZ77.decode ts with
  | none => rw [hts] at hd;simp at hd
  | some acc =>
    rw [hts] at hd
    simp only [Option.bind_some, LZ77.emit, if_neg (show ¬ t < 256 by omega)] at hd
    split at hd
    · split at hd
      · have hacc:LZ77.copyN acc (LZ77.tokDist t) (LZ77.tokLen t) = inp.take p := Option.some.inj hd
        have hlen:acc.length + LZ77.tokLen t = p := by
          have := congrArg List.length hacc
          simp [List.length_take] at this;omega
        refine ⟨by omega, ?_⟩
        apply congrArg some
        have := congrArg (List.take acc.length) hacc
        rw [u626, List.take_take] at this
        rw [this, show min acc.length p = p - LZ77.tokLen t by omega]
      · simp at hd
    · simp at hd
theorem u631 (out:U) (nt:Nat) (h0:0 < nt) (hle:nt  ≤  out.length) :
    toks out nt = toks out (nt - 1) ++ [(out.val[nt - 1]!).val] := by
  have hlt:nt - 1 < out.val.length := by
    have:out.length = out.val.length := rfl
    omega
  simp only [toks]
  conv_lhs => rw [show nt = (nt - 1) + 1 by omega]
  rw [List.take_add_one, List.getElem?_eq_getElem hlt, Option.toList_some, List.map_append]
  simp [getElem!_pos out.val (nt - 1) hlt]
theorem u632 (out:U) (nt:Nat) (h:nt  ≤  out.length) :
    (toks out nt).length = nt := by
  simp only [toks, List.length_map, List.length_take]
  have:out.length = out.val.length := rfl
  omega
def u633 (s:I) (out:U) (nt p:Nat):Prop :=
  p  ≤  s.length  ∧  nt  ≤  p  ∧  s.length  ≤  out.length  ∧ 
    LZ77.decode (toks out nt) = some ((bytes s).take p)
theorem ADec.u634 (input:I) (out:U) (h:input.length  ≤  out.length) :
    u633 input out (0#usize).val (0#usize).val :=
  ⟨by simp, by simp, h, by simp [toks, LZ77.decode]⟩
theorem ADec.u635 {s:I} {out:U} {nt p:Nat} (h:u633 s out nt p)
    (hp:p < s.length) (ntU:R) (hnt:ntU.val = nt) (v:W)
    (hv:v.val = (s.val[p]!).val) :
    u633 s (out.set ntU v) (nt + 1) (p + 1) := by
  obtain ⟨hps, hntp, hso, hde⟩ := h
  have hntl:ntU.val < out.length := by omega
  refine ⟨by omega, by omega, by rw [Std.Slice.set_length];exact hso, ?_⟩
  rw [← hnt]
  refine emit_lit s out ntU p v (by rw [hnt];exact hde) hp hntl ?_
  have hpl:p < s.val.length := hp
  rw [hv, bytes_getElem! s p hpl, getElem!_pos s.val p hpl]
theorem ADec.match {s:I} {out:U} {nt p l d:Nat} (h:u633 s out nt p)
    (hm:u616 s p l d) (ntU:R) (hnt:ntU.val = nt) (v:W)
    (hv:v.val = LZ77.mkMatch d l) :
    u633 s (out.set ntU v) (nt + 1) (p + l) := by
  obtain ⟨hps, hntp, hso, hde⟩ := h
  obtain ⟨h3, h258, hpl, hd1, hd32, hdp, hmm⟩ := hm
  have hntl:ntU.val < out.length := by omega
  refine ⟨by omega, by omega, by rw [Std.Slice.set_length];exact hso, ?_⟩
  rw [← hnt]
  exact emit_match s out ntU p d l v (by rw [hnt];exact hde) hntl hd1 hdp hd32 h3 h258 hpl hmm hv
theorem ADec.u636 {s:I} {out:U} {nt p:Nat} (h:u633 s out nt p)
    (h0:0 < nt) (hle:nt  ≤  out.length) (ht:(out.val[nt - 1]!).val < 256) :
    1  ≤  p  ∧  u633 s out (nt - 1) (p - 1) := by
  obtain ⟨hps, hntp, hso, hde⟩ := h
  rw [u631 out nt h0 hle] at hde
  obtain ⟨hp1, hde'⟩ := u629 (by simpa using hps) hde ht
  exact ⟨hp1, by omega, by omega, hso, hde'⟩
theorem ADec.u637 {s:I} {out:U} {nt p:Nat} (h:u633 s out nt p)
    (h0:0 < nt) (hle:nt  ≤  out.length) (ht:256  ≤  (out.val[nt - 1]!).val) :
    LZ77.tokLen (out.val[nt - 1]!).val  ≤  p  ∧ 
      u633 s out (nt - 1) (p - LZ77.tokLen (out.val[nt - 1]!).val) := by
  obtain ⟨hps, hntp, hso, hde⟩ := h
  rw [u631 out nt h0 hle] at hde
  obtain ⟨hw, hde'⟩ := u630 (by simpa using hps) hde ht
  have hlen := u628 hde'
  rw [u632 out (nt - 1) (by omega), List.length_take, LZ77.bytes_length] at hlen
  exact ⟨hw, by omega, by omega, hso, hde'⟩
theorem ADec.u638 {s:I} {out:U} {nt p:Nat} (h:u633 s out nt p)
    (hp:s.length  ≤  p):nt  ≤  s.length  ∧  LZ77.Valid (bytes s) (toks out nt) := by
  obtain ⟨hps, hntp, hso, hde⟩ := h
  refine ⟨by omega, ?_⟩
  unfold LZ77.Valid
  rw [hde, show p = s.length by omega, ← LZ77.bytes_length, List.take_length]
theorem ADec.u639 {s:I} {out out1:U} {ntU nt1 pU:R}
    {b:Std.U8} {v:W} (h:u633 s out ntU.val pU.val) (hp:pU.val < s.val.length)
    (hb:b = s.val[pU.val]) (hv:v = UScalar.cast .U32 b) (hout1:out1 = out.set ntU v)
    (hnt1:nt1.val = ntU.val + 1) :
    nt1.val = ntU.val + 1  ∧  out1.length = out.length  ∧  u633 s out1 nt1.val (pU.val + 1) := by
  subst hout1
  refine ⟨hnt1, Std.Slice.set_length .., ?_⟩
  rw [hnt1]
  exact ADec.u635 h hp ntU rfl v (by rw [hv, U8.cast_U32_val_eq, hb, getElem!_pos s.val pU.val hp])
theorem ADec.u640 {s:I} {out out1:U} {ntU nt1 pU dU lU e:R}
    {v:W} (h:u633 s out ntU.val pU.val) (hm:u616 s pU.val lU.val dU.val)
    (hout1:out1 = out.set ntU v) (hv:v.val = LZ77.mkMatch dU.val lU.val)
    (hnt1:nt1.val = ntU.val + 1) (he:e.val = pU.val + lU.val) :
    nt1.val = ntU.val + 1  ∧  e.val = pU.val + lU.val  ∧  out1.length = out.length  ∧ 
      u633 s out1 nt1.val e.val := by
  subst hout1
  refine ⟨hnt1, he, Std.Slice.set_length .., ?_⟩
  rw [hnt1, he]
  exact ADec.match h hm ntU rfl v hv
theorem AMatchAt.u641 {s:I} {p l d:Nat} (h:u616 s p l d) (hl:l < 258)
    (hdp:d < p) (heq:s.val[p - 1]! = s.val[p - 1 - d]!):u616 s (p - 1) (l + 1) d := by
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
theorem AMatchAt.u642 {s:I} {p l d w:Nat} (h:u616 s p l d)
    (hlw:l + w  ≤  258) (hw:w  ≤  p) (hdw:d  ≤  p - w) (hmw:Matches s (p - w - d) (p - w) w) :
    u616 s (p - w) (l + w) d := by
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
def u643 (input:I) (L d E P0:Nat) (out:U) (nt p l:Nat):Prop :=
  u633 input out nt p  ∧  out.length = L  ∧  u616 input p l d  ∧  p + l = E  ∧  p  ≤  P0
theorem ABackInv.u644 {input:I} {out:U} {L d E P0:Nat}
    {nt p l i1 i2 i4 l1:R} {t:W} {x y:Std.U8}
    (h:u643 input L d E P0 out nt.val p.val l.val)
    (hi1:i1.val = nt.val - 1) (hntl:nt.val  ≤  out.length) (hnt0:1  ≤  nt.val)
    (hi1l:i1.val < out.val.length) (ht:t = out.val[i1.val]) (ht256:t < 256#u32)
    (hi2:i2.val = p.val - 1) (hi2l:i2.val < input.val.length) (hx:x = input.val[i2.val])
    (hxy:x = y) (hi4:i4.val = i2.val - d) (hi4l:i4.val < input.val.length)
    (hy:y = input.val[i4.val]) (hl:l.val < 258) (hdp:d < p.val)
    (hl1:l1.val = l.val + 1) :
    u643 input L d E P0 out i1.val i2.val l1.val := by
  obtain ⟨hdec, hL, hm, hE, hP⟩ := h
  have ht':(out.val[nt.val - 1]!).val < 256 := by
    rw [← hi1, getElem!_pos out.val i1.val hi1l, ← ht];(subst_vars;scalar_tac (simpAllMaxSteps := 0))
  obtain ⟨hp1, hdec'⟩ := ADec.u636 hdec (by omega) hntl ht'
  have heq:input.val[p.val - 1]! = input.val[p.val - 1 - d]! := by
    rw [← hi2, getElem!_pos input.val i2.val hi2l, show i2.val - d = i4.val by omega,
      getElem!_pos input.val i4.val hi4l, ← hx, ← hy, hxy]
  have hm' := AMatchAt.u641 hm hl hdp heq
  rw [hi1, hi2, hl1]
  exact ⟨hdec', hL, hm', by omega, by omega⟩
theorem ABackInv.match {input:I} {out:U} {L d E P0:Nat}
    {nt p l i1 w i9 i10 i11 i12:R} {t:W}
    (h:u643 input L d E P0 out nt.val p.val l.val)
    (hi1:i1.val = nt.val - 1) (hntl:nt.val  ≤  out.length) (hnt0:1  ≤  nt.val)
    (hi1l:i1.val < out.val.length) (ht:t = out.val[i1.val])
    (hsame:i12.val = 1  →  Matches input i11.val i10.val w.val) (hi12:i12 = 1#usize)
    (ht24:16777216  ≤  t.val) (hwv:w.val = (t.val - 16777216) % 256 + 3)
    (hi9:i9.val = l.val + w.val) (hi9':i9.val  ≤  258) (hi10:i10.val = p.val - w.val)
    (hwp:w.val  ≤  p.val) (hdw:d  ≤  i10.val) (hi11:i11.val = i10.val - d) :
    u643 input L d E P0 out i1.val i10.val i9.val := by
  obtain ⟨hdec, hL, hm, hE, hP⟩ := h
  have htv:(out.val[nt.val - 1]!).val = t.val := by
    rw [← hi1, getElem!_pos out.val i1.val hi1l, ← ht]
  have hwv':w.val = LZ77.tokLen (out.val[nt.val - 1]!).val := by
    rw [htv, hwv]
    simp only [LZ77.tokLen, LZ77.MATCH_BASE]
  obtain ⟨hwl, hdec'⟩ := ADec.u637 hdec (by omega) hntl (by omega)
  rw [← hwv'] at hdec'
  have hmw:Matches input (p.val - w.val - d) (p.val - w.val) w.val := by
    have := hsame (by rw [hi12];rfl)
    rw [hi11, hi10] at this
    exact this
  have hm' := AMatchAt.u642 hm (by omega) hwp (by omega) hmw
  rw [hi1, hi10, hi9]
  exact ⟨hdec', hL, hm', by omega, by omega⟩
theorem ABackInv.u645 {input:I} {out out1:U} {L d E P0:Nat}
    {nt p l:Nat} {p1 l1:R} (h:u643 input L d E P0 out nt p l)
    (hlen:out1.length = out.length) (hdec:u633 input out1 nt p1.val)
    (hm:u616 input p1.val l1.val d) (hE:p1.val + l1.val = p + l) (hp:p1.val  ≤  p) :
    u643 input L d E P0 out1 nt p1.val l1.val := by
  obtain ⟨_, hL, _, hE0, hP⟩ := h
  exact ⟨hdec, by rw [hlen, hL], hm, by omega, by omega⟩
theorem ABackInv.u646 {input:I} {out:U} {L E P0:Nat}
    {nt p l d back i1 i2 i4 l1 back1:R} {t:W} {x y:Std.U8}
    (h:u643 input L d.val E P0 out nt.val p.val l.val)
    (hbk:back < slot.Z55) (hntl:nt  ≤  Std.Slice.len out) (hl:l < 258#usize) (hdp:d < p)
    (hi1:i1.val = nt.val - 1) (hnt0:1  ≤  nt.val) {hb1:i1.val < out.val.length}
    (ht:t = out.val[i1.val]'hb1) (ht256:t < 256#u32)
    (hi2:i2.val = p.val - 1) {hb2:i2.val < input.val.length} (hx:x = input.val[i2.val]'hb2)
    (hi4:i4.val = i2.val - d.val) {hb4:i4.val < input.val.length}
    (hy:y = input.val[i4.val]'hb4) (hxy:x = y)
    (hl1:l1.val = l.val + 1) (hb1':back1.val = back.val + 1) :
    u643 input L d.val E P0 out i1.val i2.val l1.val  ∧ 
      slot.Z55.val - back1.val < slot.Z55.val - back.val :=
  ⟨ABackInv.u644 h hi1 (by (subst_vars;scalar_tac (simpAllMaxSteps := 0))) hnt0 hb1 ht ht256 hi2 hb2 hx hxy hi4 hb4 hy
    (by (subst_vars;scalar_tac (simpAllMaxSteps := 0))) (by (subst_vars;scalar_tac (simpAllMaxSteps := 0))) hl1, by (subst_vars;scalar_tac (simpAllMaxSteps := 0))⟩
theorem ABackInv.u647 {input:I} {out:U} {L E P0:Nat}
    {nt p l d back i1 w i9 i10 i11 i12 back1:R} {t i6 i7 i8:W}
    (h:u643 input L d.val E P0 out nt.val p.val l.val)
    (hbk:back < slot.Z55) (hntl:nt  ≤  Std.Slice.len out)
    (hi1:i1.val = nt.val - 1) (hnt0:1  ≤  nt.val) {hb1:i1.val < out.val.length}
    (ht:t = out.val[i1.val]'hb1) (hi6:i6.val = t.val - 16777216) (ht24:16777216  ≤  t.val)
    (hi7:i7.val = i6.val % 256) (hi8:i8.val = i7.val + 3) (hw:w = UScalar.cast .Usize i8)
    (hi9:i9.val = l.val + w.val) (hi9':i9  ≤  258#usize) (hi10:i10.val = p.val - w.val)
    (hwp:w.val  ≤  p.val) (hdw:d  ≤  i10) (hi11:i11.val = i10.val - d.val)
    (hsame:i12.val = 1  →  Matches input i11.val i10.val w.val) (hi12:i12 = 1#usize)
    (hb1':back1.val = back.val + 1) :
    u643 input L d.val E P0 out i1.val i10.val i9.val  ∧ 
      slot.Z55.val - back1.val < slot.Z55.val - back.val := by
  have hwv:w.val = (t.val - 16777216) % 256 + 3 := by rw [hw];scalar_tac
  exact ⟨ABackInv.match h hi1 (by scalar_tac) hnt0 hb1 ht hsame hi12 ht24 hwv hi9 (by scalar_tac)
    hi10 hwp (by scalar_tac) hi11, by scalar_tac⟩
theorem ABackInv.u648 {input:I} {out out1:U} {L E P0:Nat}
    {nt p l d back p1 l1:R} (h:u643 input L d.val E P0 out nt.val p.val l.val)
    (hbk:back < slot.Z55) (hlen:out1.length = out.length)
    (hdec:u633 input out1 nt.val p1.val) (hm:u616 input p1.val l1.val d.val)
    (hE:p1.val + l1.val = p.val + l.val) (hp:p1.val  ≤  p.val) :
    u643 input L d.val E P0 out1 nt.val p1.val l1.val  ∧ 
      slot.Z55.val - slot.Z55.val < slot.Z55.val - back.val :=
  ⟨ABackInv.u645 h hlen hdec hm hE hp, by (subst_vars;scalar_tac (simpAllMaxSteps := 0))⟩
theorem Matches.u649 {input:I} {a b n:Nat} (h:Matches input (a + 1) (b + 1) n)
    (heq:input.val[b]! = input.val[a]!):Matches input a b (n + 1) := by
  intro k hk
  rcases Nat.eq_zero_or_pos k with h0 | hk0
  · subst h0;simpa using heq
  · have := h (k - 1) (by omega)
    rw [show b + 1 + (k - 1) = b + k by omega, show a + 1 + (k - 1) = a + k by omega] at this
    exact this
theorem Matches.u650 {input:I} {a b k l:Nat} (h1:Matches input a b k)
    (h2:Matches input (a + k) (b + k) l):Matches input a b (k + l) := by
  intro j hj
  rcases Nat.lt_or_ge j k with hjk | hjk
  · exact h1 j hjk
  · have := h2 (j - k) (by omega)
    rw [show b + k + (j - k) = b + j by omega, show a + k + (j - k) = a + j by omega] at this
    exact this
theorem AMatchAt.u651 {s:I} {p l d k:Nat} (h:u616 s p l d)
    (hmk:Matches s (p - k - d) (p - k) k) (hlk:l + k  ≤  258) (hdk:d + k  ≤  p) :
    u616 s (p - k) (l + k) d := by
  obtain ⟨h3, h258, hpl, hd1, hd32, _, hm⟩ := h
  refine ⟨by omega, hlk, by omega, hd1, hd32, by omega, ?_⟩
  have hm':Matches s (p - k - d + k) (p - k + k) l := by
    rw [show p - k - d + k = p - d by omega, show p - k + k = p by omega];exact hm
  have := Matches.u650 hmk hm'
  rw [show k + l = l + k by omega] at this
  exact this
theorem Matches.u652 {input:I} {p d k:Nat} {i4 i7 k1:R}
    {x y:Std.U8} (h:Matches input (p - k - d) (p - k) k) (hdk:d + k < p)
    (hi4:i4.val = p - 1 - k) (hi4l:i4.val < input.val.length) (hx:x = input.val[i4.val])
    (hi7:i7.val = p - 1 - k - d) (hi7l:i7.val < input.val.length)
    (hy:y = input.val[i7.val]) (hxy:x = y) (hk1:k1.val = k + 1) :
    Matches input (p - k1.val - d) (p - k1.val) k1.val := by
  rw [hk1]
  apply Matches.u649
  · rw [show p - (k + 1) - d + 1 = p - k - d by omega, show p - (k + 1) + 1 = p - k by omega]
    exact h
  · rw [show p - (k + 1) - d = i7.val by omega, show p - (k + 1) = i4.val by omega,
      getElem!_pos input.val i4.val hi4l, getElem!_pos input.val i7.val hi7l, ← hx, ← hy, hxy]
theorem u653 {input:I} {out out1:U}
    {nt p l d w k c nl pp p1 l1:Nat} {ntU:R} {v:W}
    (hdec:u633 input out nt p) (hm:u616 input p l d)
    (hnt0:1  ≤  nt) (hntl:nt  ≤  out.length) (ht24:256  ≤  (out.val[nt - 1]!).val)
    (hw:w = LZ77.tokLen (out.val[nt - 1]!).val)
    (hmk:Matches input (p - k - d) (p - k) k) (hc:u623 input pp nl c)
    (hout1:out1 = out.set ntU v)
    (hlk:l + k  ≤  258) (hdk:d + k  ≤  p) (hk:k  ≤  w) (hpp:pp = p - w) (hnl:nl = w - k)
    (hnl3:3  ≤  nl) (hnl258:nl  ≤  258) (hc0:0 < c) (hcp:c  ≤  pp)
    (hntU:ntU.val = nt - 1) (hv:v.val = LZ77.mkMatch c nl) (hp1:p1 = p - k)
    (hl1:l1 = l + k) :
    out1.length = out.length  ∧  u633 input out1 nt p1  ∧  u616 input p1 l1 d  ∧ 
      p1 + l1 = p + l  ∧  p1  ≤  p := by
  subst hp1 hl1 hpp
  obtain ⟨hwp, hdec'⟩ := ADec.u637 hdec (by omega) hntl ht24
  rw [← hw] at hdec' hwp
  have hpn:p  ≤  input.length := hdec.1
  have hmc:u616 input (p - w) nl c := by
    rcases hc with h0 | ⟨hc1, hc32, _, hmm⟩
    · omega
    · exact ⟨hnl3, hnl258, by omega, hc1, hc32, hcp, hmm⟩
  have hd2 := ADec.match hdec' hmc ntU hntU v hv
  rw [show nt - 1 + 1 = nt by omega, show p - w + nl = p - k by omega, ← hout1] at hd2
  refine ⟨by rw [hout1, Std.Slice.set_length], hd2, AMatchAt.u651 hm hmk hlk hdk,
    by omega, by omega⟩
def u654 (input:I) (L lim:Nat) (out:U) (nt p:Nat)
    {N:R} (head:C N) (ins l d:Nat):Prop :=
  u633 input out nt p  ∧  out.length = L  ∧  u616 input p l d  ∧  u605 head (p + 2)  ∧ 
    p < lim  ∧  ins  ≤  p + 3
theorem ALazyInv.u655 {input:I} {L lim p' B:Nat} {out1:U}
    {nt1 i ins1 l1 d1 minl:R} {N:R} {head1:C N}
    (hdec:u633 input out1 nt1.val p') (hi:i.val = p') (hlen:out1.length = L)
    (hf:u617 input i.val l1.val d1.val) (hl1:minl.val  ≤  l1.val) (hminl:3  ≤  minl.val)
    (hB:u605 head1 B) (hBi:B  ≤  i.val + 2) (hilim:i.val < lim)
    (hins:ins1.val  ≤  i.val + 3) :
    u654 input L lim out1 nt1.val i.val head1 ins1.val l1.val d1.val := by
  subst hi
  refine ⟨hdec, hlen, ?_, AHeadBound.u606 hB hBi, hilim, hins⟩
  rcases hf with h | h
  · omega
  · exact h
theorem ALazyInv.u656 {input:I} {L lim:Nat} {out:U}
    {nt p ins ins1 l d B:Nat} {N:R} {head head1:C N}
    (h:u654 input L lim out nt p head ins l d) (hB:u605 head1 B) (hBp:B  ≤  p + 2)
    (hins1:ins1  ≤  p + 3):u654 input L lim out nt p head1 ins1 l d := by
  obtain ⟨hdec, hlen, hm, _, hplim, _⟩ := h
  exact ⟨hdec, hlen, hm, AHeadBound.u606 hB hBp, hplim, hins1⟩
theorem ALazyInv.u657 {input:I} {L:Nat} {lim:R}
    {out out1:U} {nt p ins l d nt1 i ins1 l1 d1 minl:R} {B q:Nat}
    {N:R} {head head1:C N}
    (h:u654 input L lim.val out nt.val p.val head ins.val l.val d.val)
    (hminl:3  ≤  minl.val) (hilim:i < lim) (hf:u617 input i.val l1.val d1.val)
    (hl1:l1  ≥  minl) (hB:u605 head1 B) (hBi:B  ≤  i.val + 2) (hpi:p.val < i.val)
    (hins1:ins1.val  ≤  i.val + 3) (hlen:out1.length = out.length)
    (hdec:u633 input out1 nt1.val q) (hq:q = i.val) :
    u654 input L lim.val out1 nt1.val i.val head1 ins1.val l1.val d1.val  ∧ 
      lim.val - i.val + (1#u32:W).val < lim.val - p.val + (1#u32:W).val := by
  obtain ⟨_, hL, _, _, _, _⟩ := h
  exact ⟨ALazyInv.u655 hdec hq.symm (by rw [hlen, hL]) hf (by (subst_vars;scalar_tac (simpAllMaxSteps := 0))) hminl hB hBi
    (by (subst_vars;scalar_tac (simpAllMaxSteps := 0))) hins1, by (subst_vars;scalar_tac (simpAllMaxSteps := 0))⟩
theorem ALazyInv.u658 {input:I} {L:Nat} {lim:R}
    {out:U} {nt p ins l d ins1:R} {B:Nat}
    {N:R} {head head1:C N}
    (h:u654 input L lim.val out nt.val p.val head ins.val l.val d.val)
    (hB:u605 head1 B) (hBp:B  ≤  p.val + 2) (hins1:ins1.val  ≤  p.val + 3) :
    u654 input L lim.val out nt.val p.val head1 ins1.val l.val d.val  ∧ 
      lim.val - p.val + (0#u32:W).val < lim.val - p.val + (1#u32:W).val := by
  refine ⟨ALazyInv.u656 h hB hBp hins1, by simp⟩
theorem ADec.u659 {s:I} {out:U} {nt p p':Nat} (h:u633 s out nt p)
    (hp:p' = p):u633 s out nt p' := by
  subst hp;exact h
theorem u660 {out:U} {nt i1:R} {t:W}
    (hi1:i1.val = nt.val - 1) (hl:i1.val < out.val.length) (ht:t = out.val[i1.val]) :
    (out.val[nt.val - 1]!).val = t.val := by
  rw [← hi1, getElem!_pos out.val i1.val hl, ← ht]
theorem u661 {out:U} {nt i1:R} {t:W}
    (hi1:i1.val = nt.val - 1) {hb:i1.val < out.val.length} (ht:t = out.val[i1.val]'hb) :
    (out.val[nt.val - 1]!).val = t.val :=
  u660 hi1 hb ht
theorem u662 (x y:R) :
    lift (core.num.Usize.saturating_add x y) ⦃ fun r =>
      r.val = x.val + y.val  ∨  (r.val = Std.Usize.max  ∧  Std.Usize.max < x.val + y.val) ⦄ := by
  simp only [lift, Std.WP.spec_ok]
  rw [EA.u287]
  omega
theorem u663 (x y:R) :
    lift (core.num.Usize.saturating_sub x y) ⦃ fun r => r.val = x.val - y.val ⦄ := by
  simp only [lift, Std.WP.spec_ok]
  exact EA.u109 x y
theorem u664 {ins e t i:R} (hi:i = core.num.Usize.wrapping_add ins t)
    (hlt:i < e) (hie:ins.val  ≤  e.val) (ht:t.val  ≤  2147483648):t.val  ≤  e.val := by
  have hsz:4294967296  ≤  Usize.size := by (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  have hil:i.val < e.val := by (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  have hel:e.val < Usize.size := by (subst_vars;scalar_tac (simpAllMaxSteps := 0))
  rw [hi, core.num.Usize.wrapping_add_val_eq, UScalar.size_UScalarTyUsize] at hil
  by_cases hw:ins.val + t.val < Usize.size
  · rw [Nat.mod_eq_of_lt hw] at hil;omega
  · omega
theorem u665 {ins e t i:R} (hi:i = core.num.Usize.wrapping_add ins t)
    (hie:ins.val  ≤  e.val) (ht:t.val  ≤  2147483648) :
    (if i < e then e - t else ok ins) ⦃ Y112P0! ⦄ := by
  split
  · have := u664 hi (by assumption) hie ht
    step*
  · simp only [Std.WP.spec_ok]
def u666 (input:I) (L:Nat) (out:U) (nt p:Nat)
    {N:R} (head:C N) (miss:Nat):Prop :=
  u633 input out nt p  ∧  out.length = L  ∧  u605 head p  ∧  miss  ≤  p
theorem AMainInv.u667 {input:I} {L:Nat} {out:U} {nt p m B:Nat}
    {N:R} {head:C N} (hdec:u633 input out nt p) (hlen:out.length = L)
    (hB:u605 head B) (hBp:B  ≤  p) (hm:m  ≤  p):u666 input L out nt p head m :=
  ⟨hdec, hlen, AHeadBound.u606 hB hBp, hm⟩
def u668 (cnt:C 256#usize) (T:Nat):Prop :=
  ∀ j:Nat, j < 256  →  (cnt.val[j]!).val  ≤  T
theorem ACntBound.u669:u668 (Std.Array.repeat 256#usize 0#u32) 0 := by
  intro j hj
  rw [Std.Array.repeat_val, List.getElem!_eq_getElem?_getD,
    List.getElem?_replicate_of_lt (by simpa using hj)]
  rfl
theorem ACntBound.u670 {cnt:C 256#usize} {T:Nat} (h:u668 cnt T)
    (a:R) (x:W) (ha:a.val < cnt.val.length) (hx:x = cnt.val[a.val]) :
    x.val  ≤  T := by
  have := h a.val (by simpa using ha)
  rw [getElem!_pos cnt.val a.val ha, ← hx] at this
  exact this
theorem u671 (cnt:C 256#usize) (T:Nat) (h:u668 cnt T)
    (i:R) (hi:i.val < 256) :
    Std.Array.index_usize cnt i ⦃ fun x => x = cnt.val[i.val]!  ∧  x.val  ≤  T ⦄ := by
  have hl:i.val < cnt.val.length := by simp;omega
  have := Std.Array.index_usize_spec cnt i (by simpa using hl)
  apply Std.WP.spec_mono this
  intro x hx
  refine ⟨by rw [getElem!_pos cnt.val i.val hl];exact hx, ACntBound.u670 h i x hl hx⟩
theorem ACntBound.u672 {cnt:C 256#usize} {T:Nat} (h:u668 cnt T)
    (a:R) (v:W) (hv:v.val  ≤  T + 1):u668 (cnt.set a v) (T + 1) := by
  intro j hj
  rw [Std.Array.set_val_eq]
  by_cases hja:a.val = j
  · subst hja
    have hlen:a.val < cnt.val.length := by simp;omega
    rw [List.getElem!_eq_getElem?_getD, List.getElem?_set_self hlen]
    exact hv
  · rw [List.getElem!_eq_getElem?_getD, List.getElem?_set_ne hja, ← List.getElem!_eq_getElem?_getD]
    exact le_trans (h j hj) (by omega)
theorem ACntBound.step {cnt a:C 256#usize} {T:Nat} {x:R}
    {v tot1:W} (hc:u668 cnt T) (ha:a = cnt.set x v) (hv:v.val  ≤  T + 1)
    (ht1:tot1.val = T + 1):u668 a tot1.val := by
  rw [ha, ht1]
  exact ACntBound.u672 hc x v hv
theorem ACntBound.u673 {cnt:C 256#usize} {T T':Nat} (h:u668 cnt T)
    (hT:T  ≤  T'):u668 cnt T' := fun j hj => le_trans (h j hj) hT
theorem u674:0 < slot.Z47.val := by simp [slot.Z47]
open LZ77 (Matches)






theorem u675 (input:I) (plan out0:U)
    (n ntok0 p0:R) (hn:n.val = input.length) (hout:input.length  ≤  out0.length)
    (hp0:p0.val  ≤  n.val) (hntok0:ntok0.val  ≤  p0.val)
    (hdec0:LZ77.decode (toks out0 ntok0.val) = some ((bytes input).take p0.val)) :
    slot.Z253_loop input plan out0 n ntok0 p0 ⦃ Y112P4! ⦄ := by
  rw [slot.Z253_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, p) => n.val - p.val)
    (inv := fun (out, ntok, p) => p.val  ≤  n.val  ∧  ntok.val  ≤  p.val  ∧  out.length = out0.length  ∧ 
      LZ77.decode (toks out ntok.val) = some ((bytes input).take p.val))
  · rintro ⟨out, ntok, p⟩ ⟨hp, hnt, hlen, hde⟩
    simp only [slot.Z253_loop.body]
    have hmax:input.length  ≤  Std.Usize.max := Std.Slice.length_ineq input
    split
    case isTrue hlt =>
      have hntok_lt:ntok.val < out.length := by (subst_vars;scalar_tac (simpAllMaxSteps := 0))
      step*
      ·
        obtain ⟨h3, h258, hd1, hd32k, hdp, hend, hm⟩ := valid_post (by assumption)
        have htok:tok.val = LZ77.mkMatch dist.val len.val := by
          simp only [LZ77.mkMatch, LZ77.MATCH_BASE]
          (subst_vars;scalar_tac (simpAllMaxSteps := 0))
        refine ⟨by (subst_vars;scalar_tac (simpAllMaxSteps := 0)), by (subst_vars;scalar_tac (simpAllMaxSteps := 0)), by rw [s_post];simpa using hlen, ?_, by (subst_vars;scalar_tac (simpAllMaxSteps := 0))⟩
        rw [s_post, show ntok1.val = ntok.val + 1 by (subst_vars;scalar_tac (simpAllMaxSteps := 0)),
          show p1.val = p.val + len.val by (subst_vars;scalar_tac (simpAllMaxSteps := 0))]
        exact emit_match input out ntok p.val dist.val len.val tok hde hntok_lt hd1 hdp hd32k
          h3 h258 hend hm htok
      ·
        have hlit:lit.val = (bytes input)[p.val]! := by
          rw [bytes_getElem! input p.val (by (subst_vars;scalar_tac (simpAllMaxSteps := 0)))]
          (subst_vars;scalar_tac (simpAllMaxSteps := 0))
        refine ⟨by (subst_vars;scalar_tac (simpAllMaxSteps := 0)), by (subst_vars;scalar_tac (simpAllMaxSteps := 0)), by rw [s_post];simpa using hlen, ?_, by (subst_vars;scalar_tac (simpAllMaxSteps := 0))⟩
        rw [s_post, show ntok1.val = ntok.val + 1 by (subst_vars;scalar_tac (simpAllMaxSteps := 0)),
          show p1.val = p.val + 1 by (subst_vars;scalar_tac (simpAllMaxSteps := 0))]
        exact emit_lit input out ntok p.val lit hde (by (subst_vars;scalar_tac (simpAllMaxSteps := 0))) hntok_lt hlit
    case isFalse hge =>
      have hpn:p.val = input.length := by (subst_vars;scalar_tac (simpAllMaxSteps := 0))
      refine ⟨by (subst_vars;scalar_tac (simpAllMaxSteps := 0)), hlen, ?_⟩
      rw [hde, hpn]
      simp
  · exact ⟨hp0, hntok0, rfl, hdec0⟩
@[local step]
theorem u676 (input:I) (plan out:U)
    (hout:input.length  ≤  out.length) :
    slot.Z253 input plan out ⦃ Y112P5! ⦄ := by
  rw [slot.Z253]
  exact u675 input plan out (Std.Slice.len input) 0#usize 0#usize (by simp) hout
    (by simp) (by simp) (by simp [toks, LZ77.decode])
attribute [local step] EB.u333
attribute [local step] EB.u334












attribute [local step] EC.u486
attribute [local step] EC.u487
attribute [local step] EC.u488
attribute [local step] EC.u489
attribute [local step] EC.u490
attribute [local step] EC.u491
attribute [local step] EC.u492
attribute [local step] EC.u493
attribute [local step] EC.u494
attribute [local step] EC.u495
attribute [local step] EC.u496
attribute [local step] EC.u497
attribute [local step] EC.u498
attribute [local step] EC.u499
attribute [local step] EC.u500
attribute [local step] EC.u501
attribute [local step] EC.u502
attribute [local step] EC.u503
attribute [local step] EC.u504
attribute [local step] EC.u505
attribute [local step] EC.u506
attribute [local step] EC.u507
attribute [local step] EC.u508
attribute [local step] EC.u509
attribute [local step] EC.u510
attribute [local step] EC.u511
attribute [local step] EC.u512
attribute [local step] EC.u513
attribute [local step] EC.u514
attribute [local step] EC.u515
attribute [local step] EC.u516
attribute [local step] EC.u517
attribute [local step] EC.u518
attribute [local step] EC.u519
attribute [local step] EC.u520
attribute [local step] EC.u521
attribute [local step] EC.u522
attribute [local step] EC.u523
attribute [local step] EC.u524
attribute [local step] EC.u525
attribute [local step] EC.u526
attribute [local step] EC.u527
attribute [local step] EC.u528
attribute [local step] EC.u529
attribute [local step] EC.u530
attribute [local step] EC.u531
attribute [local step] EC.u532
attribute [local step] EC.u533
attribute [local step] EC.u534
attribute [local step] EC.u535
attribute [local step] EC.u536
attribute [local step] EC.u537
attribute [local step] EC.u538
attribute [local step] EC.u539
attribute [local step] EC.u540
attribute [local step] EC.u541
attribute [local step] EC.u542
attribute [local step] EC.u543
attribute [local step] EC.u544
attribute [local step] EC.u545
attribute [local step] EC.u546
attribute [local step] EC.u547
attribute [local step] EC.u548
attribute [local step] EC.u549
attribute [local step] EC.u550
attribute [local step] EC.u551
attribute [local step] EC.u552
attribute [local step] EC.u553
attribute [local step] EC.u554
attribute [local step] EC.u555
attribute [local step] EC.u556
attribute [local step] EC.u557
attribute [local step] EC.u558
attribute [local step] EC.u559
attribute [local step] EC.u560
attribute [local step] EC.u561
attribute [local step] EC.u562
attribute [local step] EC.u563
attribute [local step] EC.u564
attribute [local step] EC.u565
attribute [local step] EC.u566
attribute [local step] EC.u567
attribute [local step] EC.u568
theorem spine_CFG_le:∀ r ∈ slot.Z84.val, ∀ x ∈ r.val, x.val  ≤  65536 := by
  unfold slot.Z84;decide
@[local step]
theorem u677 (input:I) (k) (hn:input.length < 67108864) :
    slot.Z256 input k ⦃ Y112P0! ⦄ := by
  rw [slot.Z256]
  step*
  all_goals
    have hc:c ∈ slot.Z84.val := by rw [c_post];exact List.getElem_mem _
    exact Submission.EA.spine_knob_le (spine_CFG_le c hc) (by assumption)
@[local step]
theorem u678 (input:I) (k:R):slot.Z257 input k ⦃ Y112P0! ⦄ := by
  rw [slot.Z257]
  step*
theorem u679 (input:I) (out:U) (mode:R)
    (hlen:input.length  ≤  out.length) :
    slot.Z254 input out mode ⦃ Y112P1! ⦄ := Y127U3! slot.Z254
attribute [local step] u679
@[local step]
theorem u680 (input:I) (out:U) (mode:R) (hlen:input.length  ≤  out.length):slot.Z255 input out mode ⦃ Y112P1! ⦄ := by
 rw [slot.Z255]
 step*
 all_goals repeat' (split <;> step*)
end ED
@[local step]
theorem u681 (input:I) (s:R) (hist:C 256#usize)
    (i:R) (hs:s.val  ≤  input.length) :
    slot.Z262_loop input s hist i ⦃ Y112P0! ⦄ := by
  rw [slot.Z262_loop]
  apply Std.loop.spec_decr_nat (measure := fun st => s.val - st.2.val) (inv := fun _ => True)
  · rintro ⟨h1, i1⟩ _
    simp only [slot.Z262_loop.body]
    have hmax:input.length  ≤  Std.Usize.max := Std.Slice.length_ineq input
    step*
    all_goals repeat' (first | (split <;> step*) | scalar_tac)
  · trivial
@[local step]
theorem u682 (input:I) (s:R) (hist:C 256#usize)
    (hs:s.val  ≤  input.length) :
    slot.Z262 input s hist ⦃ Y112P0! ⦄ := by
  rw [slot.Z262]
  step*
@[local step]
theorem u683 (hist:C 256#usize) (b:R) (t:Std.U64)
    (k:R) (hb:b.val  ≤  256) :
    slot.Z263_loop hist b t k ⦃ Y112P0! ⦄ := by
  rw [slot.Z263_loop]
  apply Std.loop.spec_decr_nat (measure := fun st => b.val - st.2.val) (inv := fun _ => True)
  · rintro ⟨t1, k1⟩ _
    simp only [slot.Z263_loop.body]
    step*
    all_goals repeat' (first | (split <;> step*) | scalar_tac)
  · trivial
@[local step]
theorem u684 (hist:C 256#usize) (a b:R) (hb:b.val  ≤  256) :
    slot.Z263 hist a b ⦃ Y112P0! ⦄ := by
  rw [slot.Z263]
  step*
@[local step]
theorem u685 (input:I):slot.Z264 input ⦃ Y112P0! ⦄ := by
  rw [slot.Z264]
  have hmax:input.length  ≤  Std.Usize.max := Std.Slice.length_ineq input
  step*
  all_goals repeat' (first | (split <;> step*) | scalar_tac)
theorem u686 (input:I) (out:U) (r:R)
    (hlen:input.length  ≤  out.length) :
    slot.Z258 input out r ⦃ Y112P1! ⦄ := by
  rw [slot.Z258]
  split
  · exact EA.u322 input out 0#usize hlen
  · split
    · exact EA.u322 input out 1#usize hlen
    · split
      · exact EA.u322 input out 2#usize hlen
      · split
        · exact EA.u322 input out 3#usize hlen
        · split
          · exact EA.u322 input out 1#usize hlen
          · split
            · exact EA.u322 input out 2#usize hlen
            · split
              · exact EA.u322 input out 4#usize hlen
              · exact EA.u322 input out 5#usize hlen
theorem u687 (input:I) (out:U) (r:R)
    (hlen:input.length  ≤  out.length) :
    slot.Z259 input out r ⦃ Y112P1! ⦄ := by
  rw [slot.Z259]
  split
  · exact EA.u322 input out 6#usize hlen
  · split
    · exact EA.u322 input out 7#usize hlen
    · split
      · exact EA.u322 input out 8#usize hlen
      · split
        · exact EA.u322 input out 9#usize hlen
        · split
          · exact EA.u322 input out 10#usize hlen
          · split
            · exact EB.u447 input out 0#usize hlen
            · split
              · exact EB.u447 input out 0#usize hlen
              · exact EB.u447 input out 1#usize hlen
theorem u688 (input:I) (out:U) (r:R)
    (hlen:input.length  ≤  out.length) :
    slot.Z260 input out r ⦃ Y112P1! ⦄ := by
  rw [slot.Z260]
  split
  · exact EB.u447 input out 2#usize hlen
  · split
    · exact EB.u447 input out 3#usize hlen
    · split
      · exact EC.u572 input out 0#usize hlen
      · split
        · exact EC.u572 input out 1#usize hlen
        · split
          · exact EC.u572 input out 2#usize hlen
          · split
            · exact EC.u572 input out 3#usize hlen
            · split
              · exact EC.u572 input out 4#usize hlen
              · exact EC.u572 input out 5#usize hlen
theorem u689 (input:I) (out:U) (r:R)
    (hlen:input.length  ≤  out.length) :
    slot.Z261 input out r ⦃ Y112P1! ⦄ := by
  rw [slot.Z261]
  split
  · exact EC.u572 input out 0#usize hlen
  · split
    · exact EC.u572 input out 6#usize hlen
    · split
      · exact EC.u572 input out 7#usize hlen
      · exact ED.u680 input out 0#usize hlen
theorem parse_spec (input:I) (out:U)
    (hlen:input.length  ≤  out.length) :
    slot.parse input out ⦃ Y112P1! ⦄ := by
  rw [slot.parse]
  apply Std.WP.spec_bind (u685 input)
  intro r _
  split
  · exact u686 input out r hlen
  · split
    · exact u687 input out r hlen
    · split
      · exact u688 input out r hlen
      · exact u689 input out r hlen
end Submission

