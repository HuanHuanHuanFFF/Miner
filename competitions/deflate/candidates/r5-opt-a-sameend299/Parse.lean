-- RESEARCH ONLY: NOT_ADAPTED. Frozen parent proof is retained for migration, not acceptance.
import Lz77
import Slot

/-!
# S: plan + re-verify, the proof (assembled from sections)

Sections, in this order, form this file (see /root/66/work/pk/s/CONTRACT.md):
`sec_head` (this part: header, generic step rules, bound lemmas), `sec_spine` (emission,
router helpers), `sec_engA`, `sec_engB`, `sec_engC` (search engines, totality only),
`sec_spine_top` (plan_cfg, make_plan, parse_spec), then the closing `end Submission`.
-/

namespace Submission
open Aeneas Aeneas.Std Result ControlFlow

set_option maxRecDepth 8192
set_option maxHeartbeats 1000000
-- The search recipe is uniform on purpose; where a step of it has nothing to do, say nothing.
set_option linter.unusedTactic false
set_option linter.unreachableTactic false
set_option linter.unusedSimpArgs false
set_option linter.unusedVariables false

open LZ77 (toks bytes bytes_getElem! Matches emit_lit emit_match)

/-! ## Step rules shared by every section -/

/-- Any pure operation in bind position (`lift (saturating_add ..)`, `lift (deref_mut ..)`,
    casts, `leading_zeros`): `step*` names its result instead of stopping. -/
@[local step]
theorem lift_spec {α : Type} (x : α) : lift x ⦃ fun y => y = x ⦄ := by
  simp [lift, WP.spec_ok]

/-- The guarded read: total, and nothing is known about the value. -/
@[local step]
theorem get0_spec (v : Slice Std.U32) (i : Std.Usize) : slot.get0 v i ⦃ fun _ => True ⦄ := by
  rw [slot.get0]; split <;> step*

/-- The guarded write: total, and the slice keeps its length. -/
@[local step]
theorem set_in_spec (v : Slice Std.U32) (i : Std.Usize) (x : Std.U32) :
    slot.set_in v i x ⦃ fun r => r.length = v.length ⦄ := by
  rw [slot.set_in]; split <;> step*

/-! ## Facts `scalar_tac` instantiates by itself

`x &&& mask ≤ mask`, `x >>> k ≤ x` (after `scalar_tac_simps` turns `(a &&& b).val` into
`a.val &&& b.val`), and `usize` has at least 32 bits (a `usize` shift by a constant `k < 32`
needs `k < System.Platform.numBits`, which is otherwise unknown: the platform may be 32-bit). -/

@[local scalar_tac x &&& y]
theorem nat_and_le_right (x y : Nat) : x &&& y ≤ y := Nat.and_le_right

@[local scalar_tac x >>> y]
theorem nat_shiftRight_le (x y : Nat) : x >>> y ≤ x := Nat.shiftRight_le x y

theorem numBits_ge : 32 ≤ System.Platform.numBits := by
  cases System.Platform.numBits_eq <;> simp [*]

@[local scalar_tac System.Platform.numBits]
theorem numBits_ge' : 32 ≤ System.Platform.numBits := numBits_ge

/-! ## `leading_zeros`

`core.num.U32.leading_zeros x` is `⟨BitVec.leadingZeros x.bv⟩`; `step*` passes over it with
`lift_spec` and then knows nothing about the value. Use these before `scalar_tac`:
`have := lz32_le_of_pow_le x 3 (by scalar_tac)` gives `lz + 3 ≤ 31` when `8 ≤ x`. -/

theorem lz_le_w {w : Nat} (x : BitVec w) : BitVec.leadingZeros x ≤ w := by
  unfold BitVec.leadingZeros; split <;> omega

theorem lz32_val (x : Std.U32) :
    (core.num.U32.leading_zeros x).val = BitVec.leadingZeros x.bv := by
  simp only [core.num.U32.leading_zeros, UScalar.val]
  have := lz_le_w x.bv
  apply Nat.mod_eq_of_lt
  simp at this ⊢
  omega

theorem lz32_eq (x : Std.U32) (h : x.val ≠ 0) :
    (core.num.U32.leading_zeros x).val = 31 - Nat.log 2 x.val := by
  rw [lz32_val]
  unfold BitVec.leadingZeros
  have hx : x.bv ≠ 0 := by
    intro h0; apply h; show x.bv.toNat = 0; rw [h0]; rfl
  rw [if_neg hx, UScalar.bv_toNat]
  omega

theorem lz32_le (x : Std.U32) : (core.num.U32.leading_zeros x).val ≤ 32 := by
  rw [lz32_val]; exact lz_le_w x.bv

/-- `2^k ≤ x` (so `x ≠ 0`): at most `31 - k` leading zeros. -/
theorem lz32_le_of_pow_le (x : Std.U32) (k : Nat) (h : 2 ^ k ≤ x.val) :
    (core.num.U32.leading_zeros x).val + k ≤ 31 := by
  have hx : x.val ≠ 0 := by have := Nat.one_le_two_pow (n := k); omega
  rw [lz32_eq x hx]
  have hk : k ≤ Nat.log 2 x.val := Nat.le_log_of_pow_le (by norm_num) h
  have : x.val < 2 ^ 32 := by scalar_tac
  have hl : Nat.log 2 x.val < 32 := Nat.log_lt_of_lt_pow (by omega) this
  omega

/-- `x < 2^k`: at least `32 - k` leading zeros. -/
theorem lz32_ge_of_lt_pow (x : Std.U32) (k : Nat) (h : x.val < 2 ^ k) :
    32 - k ≤ (core.num.U32.leading_zeros x).val := by
  by_cases hx : x.val = 0
  · rw [lz32_val]; unfold BitVec.leadingZeros
    have : x.bv = 0 := by
      apply BitVec.eq_of_toNat_eq; rw [UScalar.bv_toNat]; simpa using hx
    rw [if_pos this]; omega
  · rw [lz32_eq x hx]
    have hl : Nat.log 2 x.val < k := Nat.log_lt_of_lt_pow hx h
    omega

theorem lz64_val (x : Std.U64) :
    (core.num.U64.leading_zeros x).val = BitVec.leadingZeros x.bv := by
  simp only [core.num.U64.leading_zeros, UScalar.val]
  have := lz_le_w x.bv
  apply Nat.mod_eq_of_lt
  simp at this ⊢
  omega

theorem lz64_le (x : Std.U64) : (core.num.U64.leading_zeros x).val ≤ 64 := by
  rw [lz64_val]; exact lz_le_w x.bv

/-- Registered for `scalar_tac`: `31 - lz` cannot underflow once `x ≠ 0` is known. -/
@[local scalar_tac core.num.U32.leading_zeros x]
theorem lz32_bound (x : Std.U32) :
    (core.num.U32.leading_zeros x).val ≤ 32 ∧
      (x.val = 0 ∨ (core.num.U32.leading_zeros x).val ≤ 31) := by
  refine ⟨lz32_le x, ?_⟩
  by_cases h : x.val = 0
  · exact Or.inl h
  · right; rw [lz32_eq x h]; omega

@[local scalar_tac core.num.U64.leading_zeros x]
theorem lz64_bound (x : Std.U64) : (core.num.U64.leading_zeros x).val ≤ 64 := lz64_le x

/-! ## Bounded tables

`LeAll l B`: every entry of the list `l` (an `Array`'s or a `Vec`'s `.val`) is at most `B`.
The invariant for tables whose entries are only ever written with bounded values (Huffman
lengths `≤ 15`) or that count loop iterations (`LeAll lf.val t`, then `lf[j] + 1` cannot
overflow while `t < 2^32 - 1`). After `step*`, a read `x = a.val[i]` plus
`have := LeAll_get hinv i.val (by scalar_tac)` gives `scalar_tac` the bound. -/

def LeAll {ty : UScalarTy} (l : List (UScalar ty)) (B : Nat) : Prop :=
  ∀ j (h : j < l.length), (l[j]).val ≤ B

theorem LeAll_get {ty : UScalarTy} {l : List (UScalar ty)} {B : Nat} (hl : LeAll l B)
    (j : Nat) (hj : j < l.length) : (l[j]).val ≤ B := hl j hj

theorem LeAll_get! {ty : UScalarTy} {l : List (UScalar ty)} {B : Nat} (hl : LeAll l B)
    (j : Nat) (hj : j < l.length) : (l[j]!).val ≤ B := by
  rw [List.getElem!_eq_getElem?_getD, List.getElem?_eq_getElem hj]; exact hl j hj

theorem LeAll_mono {ty : UScalarTy} {l : List (UScalar ty)} {B B' : Nat} (hl : LeAll l B)
    (h : B ≤ B') : LeAll l B' := fun j hj => Nat.le_trans (hl j hj) h

theorem LeAll_replicate {ty : UScalarTy} (n : Nat) (x : UScalar ty) (B : Nat) (h : x.val ≤ B) :
    LeAll (List.replicate n x) B := by
  intro j hj; simp [List.getElem_replicate]; exact h

theorem LeAll_set {ty : UScalarTy} {l : List (UScalar ty)} {B : Nat} (hl : LeAll l B)
    (i : Nat) (x : UScalar ty) (hx : x.val ≤ B) : LeAll (l.set i x) B := by
  intro j hj
  rw [List.getElem_set]
  split
  · exact hx
  · exact hl j (by simpa using hj)

theorem LeAll_append {ty : UScalarTy} {l : List (UScalar ty)} {B : Nat} (hl : LeAll l B)
    (x : UScalar ty) (hx : x.val ≤ B) : LeAll (l ++ [x]) B := by
  intro j hj
  rw [List.getElem_append]
  split
  · exact hl j (by assumption)
  · simp; exact hx

/-- The counter step: `l[i] ≤ t` everywhere, one entry goes up by one. -/
theorem LeAll_set_succ {ty : UScalarTy} {l : List (UScalar ty)} {t : Nat} (hl : LeAll l t)
    (i : Nat) (x : UScalar ty) (hx : x.val ≤ t + 1) : LeAll (l.set i x) (t + 1) :=
  LeAll_set (LeAll_mono hl (Nat.le_succ t)) i x hx

/-! ## Constants shared by two engines -/

theorem BLOCK_TOKENS_bounds : 0 < slot.BLOCK_TOKENS.val ∧ slot.BLOCK_TOKENS.val ≤ 65536 := by
  simp [slot.BLOCK_TOKENS]

/-! # sec_spine (owner: spine)
Emission (pkB verbatim: mlen, check, emit, zeros) and the router helpers (sample_counts, classify).
Statements are fixed by /root/66/work/pk/s/CONTRACT.md; `@status` tags: DONE (proof below works),
WORK (proof to write), BLOCKED(Rx) (needs Rust edit Rx; keep the placeholder until the new extraction). -/

-- @owner spine @status DONE (pkB verbatim)
-- [spine] loop callees: -
theorem mlen_loop_spec (input : Slice Std.U8) (a b cap l0 : Std.Usize)
    (ha : a.val + cap.val ≤ input.length) (hb : b.val + cap.val ≤ input.length)
    (hl0 : l0.val ≤ cap.val) (h0 : Matches input a.val b.val l0.val) :
    slot.mlen_loop input a b cap l0 ⦃ fun l =>
      l.val ≤ cap.val ∧ Matches input a.val b.val l.val ⦄ := by
  rw [slot.mlen_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun l => cap.val - l.val)
    (inv := fun l => l.val ≤ cap.val ∧ Matches input a.val b.val l.val)
  · rintro l ⟨hle, hinv⟩
    simp only [slot.mlen_loop.body]
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    step*
    -- the only goal left: the bytes at `b + l` and `a + l` agree, so one more matches
    refine ⟨by scalar_tac, ?_, by scalar_tac⟩
    rw [show l1.val = l.val + 1 by scalar_tac]
    apply LZ77.Matches.succ hinv
    rw [getElem!_pos _ _ (by scalar_tac), getElem!_pos _ _ (by scalar_tac)]
    simp_all
  · exact ⟨hl0, h0⟩

-- @owner spine @status DONE (pkB verbatim)
-- [spine] fn callees: mlen_loop
@[local step]
theorem mlen_spec (input : Slice Std.U8) (a b cap : Std.Usize)
    (ha : a.val + cap.val ≤ input.length) (hb : b.val + cap.val ≤ input.length) :
    slot.mlen input a b cap ⦃ fun l =>
      l.val ≤ cap.val ∧ Matches input a.val b.val l.val ⦄ :=
  mlen_loop_spec input a b cap 0#usize ha hb (by scalar_tac) (LZ77.Matches.zero input a.val b.val)

-- @owner spine @status DONE (pkB verbatim)
-- [spine] fn callees: mlen
/-- `check` says yes only for a legal match whose bytes `mlen` compared: exactly the
    hypotheses of `emit_match`. -/
@[local step]
theorem check_spec (input : Slice Std.U8) (p len dist : Std.Usize) :
    slot.check input p len dist ⦃ fun valid => valid = true →
      3 ≤ len.val ∧ len.val ≤ 258 ∧ 1 ≤ dist.val ∧ dist.val ≤ 32768 ∧ dist.val ≤ p.val ∧
      p.val + len.val ≤ input.length ∧ Matches input (p.val - dist.val) p.val len.val ⦄ := by
  rw [slot.check]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  step*
  intro hvalid
  have hl : l = len := by simpa using hvalid
  subst hl
  refine ⟨by scalar_tac, by scalar_tac, by scalar_tac, by scalar_tac, by scalar_tac,
    by scalar_tac, ?_⟩
  rw [← src_post1]
  exact l_post2

-- @owner spine @status DONE (pkB verbatim)
-- [spine] loop callees: check get0
theorem emit_loop_spec (input : Slice Std.U8) (plan out0 : Slice Std.U32)
    (n ntok0 p0 : Std.Usize) (hn : n.val = input.length) (hout : input.length ≤ out0.length)
    (hp0 : p0.val ≤ n.val) (hntok0 : ntok0.val ≤ p0.val)
    (hdec0 : LZ77.decode (toks out0 ntok0.val) = some ((bytes input).take p0.val)) :
    slot.emit_loop input plan out0 n ntok0 p0 ⦃ fun r =>
      r.1.val ≤ input.length ∧ r.2.length = out0.length ∧
      LZ77.decode (toks r.2 r.1.val) = some (bytes input) ⦄ := by
  rw [slot.emit_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, p) => n.val - p.val)
    (inv := fun (out, ntok, p) => p.val ≤ n.val ∧ ntok.val ≤ p.val ∧ out.length = out0.length ∧
      LZ77.decode (toks out ntok.val) = some ((bytes input).take p.val))
  · rintro ⟨out, ntok, p⟩ ⟨hp, hnt, hlen, hde⟩
    simp only [slot.emit_loop.body]
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    split
    case isTrue hlt =>
      have hntok_lt : ntok.val < out.length := by scalar_tac
      step*
      · -- `check` accepted `(len, dist)`: write the match token, advance `len`
        obtain ⟨h3, h258, hd1, hd32k, hdp, hend, hm⟩ := valid_post (by assumption)
        have htok : tok.val = LZ77.mkMatch dist.val len.val := by
          simp only [LZ77.mkMatch, LZ77.MATCH_BASE]
          scalar_tac
        refine ⟨by scalar_tac, by scalar_tac, by rw [s_post]; simpa using hlen, ?_, by scalar_tac⟩
        rw [s_post, show ntok1.val = ntok.val + 1 by scalar_tac,
          show p1.val = p.val + len.val by scalar_tac]
        exact emit_match input out ntok p.val dist.val len.val tok hde hntok_lt hd1 hdp hd32k
          h3 h258 hend hm htok
      · -- anything else: write the literal `input[p]`, advance 1
        have hlit : lit.val = (bytes input)[p.val]! := by
          rw [bytes_getElem! input p.val (by scalar_tac)]
          scalar_tac
        refine ⟨by scalar_tac, by scalar_tac, by rw [s_post]; simpa using hlen, ?_, by scalar_tac⟩
        rw [s_post, show ntok1.val = ntok.val + 1 by scalar_tac,
          show p1.val = p.val + 1 by scalar_tac]
        exact emit_lit input out ntok p.val lit hde (by scalar_tac) hntok_lt hlit
    case isFalse hge =>
      have hpn : p.val = input.length := by scalar_tac
      refine ⟨by scalar_tac, hlen, ?_⟩
      rw [hde, hpn]
      simp
  · exact ⟨hp0, hntok0, rfl, hdec0⟩

-- @owner spine @status DONE (pkB verbatim)
-- [spine] fn callees: emit_loop
@[local step]
theorem emit_spec (input : Slice Std.U8) (plan out : Slice Std.U32)
    (hout : input.length ≤ out.length) :
    slot.emit input plan out ⦃ fun r =>
      r.1.val ≤ input.length ∧ r.2.length = out.length ∧
      LZ77.decode (toks r.2 r.1.val) = some (bytes input) ⦄ := by
  rw [slot.emit]
  exact emit_loop_spec input plan out (Std.Slice.len input) 0#usize 0#usize (by simp) hout
    (by simp) (by simp) (by simp [toks, LZ77.decode])

-- @owner spine @status DONE (pkB verbatim)
-- [spine] loop callees: -
/-- The push loop, with the one invariant a push needs: the length is the counter. -/
@[local step]
theorem zeros_loop_spec (n : Std.Usize) (v0 : alloc.vec.Vec Std.U32) (i0 : Std.Usize)
    (hv : v0.length = i0.val) (hi : i0.val ≤ n.val) :
    slot.zeros_loop n v0 i0 ⦃ fun v => v.length = n.val ⦄ := by
  rw [slot.zeros_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, i) => n.val - i.val)
    (inv := fun (v, i) => v.length = i.val ∧ i.val ≤ n.val)
  · rintro ⟨v, i⟩ ⟨hvi, hin⟩
    simp only [slot.zeros_loop.body]
    step*
    have hlen : v1.length = v.length + 1 := by simp [v1_post]
    scalar_tac
  · exact ⟨hv, hi⟩

-- @owner spine @status DONE (pkB verbatim)
-- [spine] fn callees: zeros_loop
@[local step]
theorem zeros_spec (n : Std.Usize) : slot.zeros n ⦃ fun v => v.length = n.val ⦄ := by
  rw [slot.zeros]
  step*
  simp [alloc.vec.Vec.with_capacity]

-- @owner spine @status DONE @note measure n - i; inv LeAll f (c + (i - i0)), i0 <= i. With R4 (wrapping adds in classify) the LeAll parts are unnecessary: then (hn) and True
-- [spine] loop callees: -
@[local step]
theorem sample_counts_loop0_loop0_spec (s : Slice Std.U8) (f) (n e i : Std.Usize) (c : Nat)
    (hn : n.val ≤ s.length) (hc : c + (e.val - i.val) ≤ 2 ^ 31) (hf : LeAll f.val c) :
    slot.sample_counts_loop0_loop0 s f n e i ⦃ fun r => LeAll r.val (c + (e.val - i.val)) ⦄ := by
  rw [slot.sample_counts_loop0_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, i') => e.val - i'.val)
    (inv := fun (f', i') => i.val ≤ i'.val ∧ i'.val - i.val ≤ e.val - i.val ∧
      LeAll f'.val (c + (i'.val - i.val)))
  · rintro ⟨f', i'⟩ ⟨hi1, hi2, hf'⟩
    simp only [slot.sample_counts_loop0_loop0.body]
    step*
    all_goals try (exact LeAll_mono hf' (by omega))
    -- one byte counted: its class counter goes up by one (no wrap: every counter < 2^31)
    have h5 := LeAll_get hf' i4.val (by scalar_tac)
    rw [← i5_post] at h5
    have h6 : i6.val = i5.val + 1 := by
      simp only [i6_post, core.num.Usize.wrapping_add_val_eq, UScalar.size_UScalarTyUsize]
      rw [Nat.mod_eq_of_lt] <;> scalar_tac
    refine ⟨by scalar_tac, by scalar_tac, ?_, by scalar_tac⟩
    have heq : i7.val - i.val = (i'.val - i.val) + 1 := by scalar_tac
    rw [heq, ← Nat.add_assoc, a_post, Array.set_val_eq]
    exact LeAll_set_succ hf' _ _ (by scalar_tac)
  · exact ⟨le_refl _, by omega, by simpa using hf⟩

-- [spine] helper for sample_counts_loop0
/-- `a + 1024` (wrapping) is at most 1024 past `a` (and before `a` when it wraps). -/
theorem spine_wrap1024 (a : Std.Usize) :
    (core.num.Usize.wrapping_add a 1024#usize).val - a.val ≤ 1024 := by
  rw [core.num.Usize.wrapping_add_val_eq, UScalar.size_UScalarTyUsize]
  have ha : a.val < Usize.size := by scalar_tac
  have hs : 1024 < Usize.size := by scalar_tac
  have h1 : (1024#usize).val = 1024 := by simp
  rw [h1]
  by_cases h : a.val + 1024 < Usize.size
  · rw [Nat.mod_eq_of_lt h]; omega
  · rw [Nat.mod_eq_sub_mod (by omega), Nat.mod_eq_of_lt (by omega)]; omega

-- @owner spine @status DONE @note one window adds at most n (nw = 1) or 1024 (e = a + 1024 wrapping: e < a means no sample)
-- [spine] loop callees: sample_counts_loop0_loop0
@[local step]
theorem sample_counts_loop0_spec (s : Slice Std.U8) (f) (n nw step w : Std.Usize) (c : Nat)
    (hn : n.val ≤ s.length) (hnw : (nw.val = 1 ∧ n.val ≤ 32768) ∨ nw.val = 32)
    (hc : c ≤ 2 ^ 30) (hf : LeAll f.val c) :
    slot.sample_counts_loop0 s f n nw step w ⦃ fun r => LeAll r.val (c + (nw.val - w.val) * (32768 / nw.val)) ⦄ := by
  rw [slot.sample_counts_loop0]
  rcases hnw with ⟨h1, hn1⟩ | h32
  · -- the whole input is one window (`e = n ≤ 32768`)
    have hK : 32768 / nw.val = 32768 := by rw [h1]
    rw [hK]
    apply Std.loop.spec_decr_nat
      (measure := fun (_, w') => nw.val - w'.val)
      (inv := fun (f', w') => w.val ≤ w'.val ∧ w'.val - w.val ≤ nw.val - w.val ∧
        LeAll f'.val (c + (w'.val - w.val) * 32768))
    · rintro ⟨f', w'⟩ ⟨hw1, hw2, hf'⟩
      simp only [slot.sample_counts_loop0.body]
      step*
      repeat' (split <;> step*)
      all_goals try (exact LeAll_mono hf' (by scalar_tac))
      all_goals try scalar_tac
      refine ⟨by scalar_tac, by scalar_tac, LeAll_mono f1_post (by scalar_tac), by scalar_tac⟩
    · exact ⟨le_refl _, by omega, by simpa using hf⟩
  · -- 32 windows of 1024 bytes (`e = a + 1024` wrapping: at most 1024 bytes each)
    have hK : 32768 / nw.val = 1024 := by rw [h32]
    rw [hK]
    apply Std.loop.spec_decr_nat
      (measure := fun (_, w') => nw.val - w'.val)
      (inv := fun (f', w') => w.val ≤ w'.val ∧ w'.val - w.val ≤ nw.val - w.val ∧
        LeAll f'.val (c + (w'.val - w.val) * 1024))
    · rintro ⟨f', w'⟩ ⟨hw1, hw2, hf'⟩
      simp only [slot.sample_counts_loop0.body]
      step*
      repeat' (split <;> step*)
      all_goals try (exact LeAll_mono hf' (by scalar_tac))
      all_goals try (have := spine_wrap1024 a; scalar_tac)
      have := spine_wrap1024 a
      refine ⟨by scalar_tac, by scalar_tac, LeAll_mono f1_post (by scalar_tac), by scalar_tac⟩
    · exact ⟨le_refl _, by omega, by simpa using hf⟩

-- @owner spine @status DONE
-- [spine] fn callees: sample_counts_loop0
@[local step]
theorem sample_counts_spec (s) (f : Array Std.Usize 16#usize) (hf : LeAll f.val 0) :
    slot.sample_counts s f ⦃ fun r => LeAll r.val 32768 ⦄ := by
  rw [slot.sample_counts]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

-- @owner spine @status DONE
-- [spine] loop callees: -
@[local step]
theorem classify_loop0_spec (f tot k) :
    slot.classify_loop0 f tot k ⦃ fun _ => True ⦄ := by
  rw [slot.classify_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (tot_, k_) => 16 - k_.val)
    (inv := fun _ => True)
  · rintro ⟨tot_, k_⟩ _
    simp only [slot.classify_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial

-- @owner spine @status DONE @note m[k] = f[k].wrapping_mul(1000) / tot: no wrap since f[k] <= 32768
-- [spine] loop callees: -
@[local step]
theorem classify_loop1_spec (f : Array Std.Usize 16#usize) (tot : Std.Usize) (k) (m : Array Std.Usize 16#usize)
    (htot : 0 < tot.val) (hf : LeAll f.val 32768) (hm : LeAll m.val 32768000) :
    slot.classify_loop1 f tot k m ⦃ fun r => LeAll r.val 32768000 ⦄ := by
  rw [slot.classify_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (k', _) => 16 - k'.val)
    (inv := fun (_, m') => LeAll m'.val 32768000)
  · rintro ⟨k', m'⟩ (hm' : LeAll m'.val 32768000)
    simp only [slot.classify_loop1.body]
    step*
    -- `m[k] = f[k] * 1000 / tot`: the product does not wrap (`f[k] ≤ 32768`), the quotient is smaller
    have h0 : i.val ≤ 32768 := by rw [i_post]; exact LeAll_get hf k'.val (by scalar_tac)
    have h1 : i1.val = i.val * 1000 := by
      simp only [i1_post, core.num.Usize.wrapping_mul_val_eq, UScalar.size_UScalarTyUsize]
      rw [Nat.mod_eq_of_lt] <;> scalar_tac
    have h2 : i2.val ≤ i1.val := by rw [i2_post]; exact Nat.div_le_self _ _
    refine ⟨?_, by scalar_tac⟩
    rw [a_post, Array.set_val_eq]
    exact LeAll_set hm' _ _ (by scalar_tac)
  · exact hm

-- [spine] helpers for classify
/-- A zero-filled array is bounded by anything. -/
theorem spine_LeAll_repeat0 (n : Std.Usize) (B : Nat) : LeAll (Array.repeat n 0#usize).val B := by
  rw [Array.repeat_val]; exact LeAll_replicate _ _ _ (by simp)

/-- A read `x = l[j]` (the post of `Array.index_usize`) from a table bounded by `B`. -/
theorem spine_LeAll_read {ty : UScalarTy} {l : List (UScalar ty)} {B : Nat} (hl : LeAll l B)
    {x : UScalar ty} {j : Nat} {hj : j < l.length} (hx : x = l[j]) : x.val ≤ B := by
  subst hx; exact hl j hj

-- @owner spine @status DONE @note m[8] + m[9], m[12] + m[1] are checked adds: needs the LeAll posts above (or R4)
-- [spine] fn callees: classify_loop0 classify_loop1 sample_counts
@[local step]
theorem classify_spec (s) : slot.classify s ⦃ fun _ => True ⦄ := by
  rw [slot.classify]
  have h0 := spine_LeAll_repeat0 16#usize 0
  have h1 := spine_LeAll_repeat0 16#usize 32768000
  step*
  -- left: the checked arithmetic on the shares (`m[8] + m[9]`, `m[12] + m[1]`); every share read
  -- from `m` is at most 32768000 (each `try` line is a no-op when that read does not exist)
  all_goals
    try have hb1 := spine_LeAll_read m1_post nl_post
    try have hb3 := spine_LeAll_read m1_post dig_post
    try have hb4 := spine_LeAll_read m1_post lt_post
    try have hb5 := spine_LeAll_read m1_post q_post
    try have hb6 := spine_LeAll_read m1_post com_post
    try have hb7 := spine_LeAll_read m1_post hi_post
    try have hb8 := spine_LeAll_read m1_post zero_post
    try have hbi := spine_LeAll_read m1_post i_post
    try have hbi1 := spine_LeAll_read m1_post i1_post
    try have hbi2 := spine_LeAll_read m1_post i2_post
    try have hbi3 := spine_LeAll_read m1_post i3_post
    scalar_tac

/-! # sec_engA (owner: engA) -- engine A (text): totality only.
Exported: `a_engine_spec` (called by `plan_cfg` in sec_spine_top; its statement is frozen).
Constant facts (A_LOG_FRAC_le, A_SEG/A_SAMPLE/A_MARGIN bounds) go at the top of this section. -/

/-! ## engA facts: constants and tables (stated as bounds, so retuning a value keeps them) -/

/-- `A_LOG_FRAC` (64 * log2(1 + i/128)): every entry is at most 64. -/
theorem A_LOG_FRAC_le : LeAll slot.A_LOG_FRAC.val 64 := by
  unfold slot.A_LOG_FRAC LeAll; simp only [Array.make]; decide

/-- Segment sizes of the sampled statistics pass (`A_SEG`-byte segments, every `A_SAMPLE`-th). -/
theorem A_SEG_bounds : 256 ≤ slot.A_SEG.val ∧ slot.A_SEG.val ≤ 65536 ∧
    slot.A_SEG.val + 512 ≤ slot.A_SEG.val * slot.A_SAMPLE.val ∧
    slot.A_SEG.val * slot.A_SAMPLE.val ≤ 1048576 := by
  simp

/-- `32 - A_HB` is a valid `u32` shift and leaves a hash below `2^A_HB`. -/
theorem A_HB_bounds : 1 ≤ slot.A_HB.val ∧ slot.A_HB.val ≤ 32 := by
  simp

/-- The engine's block and margin sizes. -/
theorem A_BLOCK_bounds : 0 < slot.BLOCK_TOKENS.val ∧ slot.BLOCK_TOKENS.val ≤ 16384 ∧
    slot.A_MARGIN.val ≤ 65536 ∧ slot.A_SLACK.val ≠ 0 := by
  simp

/-- A pure two-way choice in bind position is a pure value: `step*` then passes over it. -/
theorem engA_ite_ok {α : Type} (c : Prop) [Decidable c] (a b : α) :
    (if c then (ok a : Result α) else ok b) = ok (if c then a else b) := by
  split <;> rfl

/-- `saturating_add` on `usize` (for the guarded pushes `if v.len() < v.len().saturating_add(1)`). -/
theorem engA_sat_add_val (x y : Std.Usize) :
    (core.num.Usize.saturating_add x y).val = min Std.Usize.max (x.val + y.val) := by
  have hsz : Std.Usize.max < 2 ^ UScalarTy.Usize.numBits := by
    rw [Std.Usize.max_def, Std.Usize.numBits]
    have : 0 < 2 ^ UScalarTy.Usize.numBits := Nat.two_pow_pos _
    omega
  show (BitVec.ofNat _ (min (UScalar.max UScalarTy.Usize) (x.val + y.val))).toNat = _
  rw [BitVec.toNat_ofNat, UScalar.max_USize_eq, Nat.mod_eq_of_lt (by omega)]

@[local scalar_tac core.num.Usize.saturating_add x y]
theorem engA_sat_add_val' (x y : Std.Usize) :
    (core.num.Usize.saturating_add x y).val = min Std.Usize.max (x.val + y.val) := engA_sat_add_val x y

/-- A two-way choice of pairs is a pair of choices (so a `let (a, b) := ..` pattern reduces). -/
theorem engA_ite_pair {α β : Type} (c : Prop) [Decidable c] (a a' : α) (b b' : β) :
    (if c then (a, b) else (a', b')) = (if c then a else a', if c then b else b') := by
  split <;> rfl

/-- A fresh table `[x; n]` is bounded by any bound of `x`. -/
theorem engA_LeAll_repeat {ty : UScalarTy} (n : Std.Usize) (x : UScalar ty) (B : Nat) (h : x.val ≤ B) :
    LeAll (Array.repeat n x).val B := by
  rw [Array.repeat_val]; exact LeAll_replicate _ _ _ h

/-- `r = a.set i v` with `a` and `v` bounded: `r` is bounded (name-free form of `LeAll_set`). -/
theorem engA_LeAll_set_of_eq {n : Std.Usize} {a r : Array Std.U32 n} {i : Std.Usize} {v : Std.U32} {B : Nat}
    (hr : r = a.set i v) (ha : LeAll a.val B) (hv : v.val ≤ B) : LeAll r.val B := by
  rw [hr, Array.set_val_eq]; exact LeAll_set ha _ _ hv

-- @owner engA @status DONE
-- [engA] fn callees: -
@[local step]
theorem a_slot_of_spec (x) :
    slot.a_slot_of x ⦃ fun _ => True ⦄ := by
  rw [slot.a_slot_of]
  step*

-- @owner engA @status DONE @note x = len-3 in [8,254]: lz32_le_of_pow_le x 3 and lz32_ge_of_lt_pow x 8 bound k = 31-lz to [3,7]
-- [engA] fn callees: -
@[local step]
theorem a_len_slot_spec (len) :
    slot.a_len_slot len ⦃ fun r => r.val ≤ 28 ⦄ := by
  rw [slot.a_len_slot]
  split
  · step*
  · split
    · step*
    · step*
      all_goals
        have hx : x.val = len.val - 3 := by
          rw [x_post, UScalar.cast_val_mod_pow_of_inBounds_eq _ _ (by scalar_tac)]; scalar_tac
        have h1 := lz32_le_of_pow_le x 3 (by scalar_tac)
        have h2 := lz32_ge_of_lt_pow x 8 (by scalar_tac)
        subst i1_post
        scalar_tac

-- @owner engA @status DONE @note zeroing loop; inv: forall j < k, lf[j]! = 0 (A4 makes the post unnecessary: then True)
-- [engA] loop callees: -
/-- A zeroing loop, stated for the call site (`k = 0`): afterwards every entry is 0. -/
@[local step]
theorem a_walk_loop0_spec (lf) :
    slot.a_walk_loop0 lf 0#usize ⦃ fun r => LeAll r.val 0 ⦄ := by
  rw [slot.a_walk_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, k) => 512 - k.val)
    (inv := fun (lf', k) => k.val ≤ 512 ∧ ∀ j (hj : j < k.val) (hl : j < lf'.val.length), (lf'.val[j]).val = 0)
  · rintro ⟨lf', k⟩ ⟨hk, hz⟩
    simp only [slot.a_walk_loop0.body]
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
      have : k.val = 512 := by scalar_tac
      have hl' : j < 512 := by simpa using hl
      rw [hz j (by omega) hl]
  · exact ⟨by simp, fun j hj => by simp at hj⟩

-- @owner engA @status DONE @note as a_walk_loop0
-- [engA] loop callees: -
/-- A zeroing loop, stated for the call site (`k = 0`): afterwards every entry is 0. -/
@[local step]
theorem a_walk_loop1_spec (df) :
    slot.a_walk_loop1 df 0#usize ⦃ fun r => LeAll r.val 0 ⦄ := by
  rw [slot.a_walk_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, k) => 32 - k.val)
    (inv := fun (df', k) => k.val ≤ 32 ∧ ∀ j (hj : j < k.val) (hl : j < df'.val.length), (df'.val[j]).val = 0)
  · rintro ⟨df', k⟩ ⟨hk, hz⟩
    simp only [slot.a_walk_loop1.body]
    step*
    · refine ⟨by scalar_tac, ?_, by scalar_tac⟩
      intro j hj hl
      subst a_post
      simp only [Array.set_val_eq, List.getElem_set]
      split
      · rfl
      · exact hz j (by scalar_tac) (by simpa using hl)
    · intro j hl
      have : k.val = 32 := by scalar_tac
      have hl' : j < 32 := by simpa using hl
      rw [hz j (by omega) hl]
  · exact ⟨by simp, fun j hj => by simp at hj⟩

-- @owner engA @status DONE @changed (CONTRACT_ISSUES engA A3) @note measure need-t (or lim-i); inv LeAll lf t, LeAll df t, i0<=i, t<=max t0 need; lf/df += 1 are the A4 sites; a_len_slot post <= 28 for 257+sl
-- [engA] loop callees: a_len_slot a_slot_of
/-- A counting loop: `lf[x] += 1` is a checked add, so the invariant bounds every counter by the
    number of iterations `t` (`LeAll`), and `t < need <= 2^31` rules out overflow. -/
@[local step]
theorem a_walk_loop2_spec (s : Slice Std.U8) (ch) (lim need : Std.Usize) (lf df) (i t : Std.Usize)
    (hlim : lim.val ≤ 2 ^ 31) (hls : lim.val ≤ s.length) (hneed : need.val ≤ 2 ^ 31)
    (hlf : LeAll lf.val t.val) (hdf : LeAll df.val t.val) :
    slot.a_walk_loop2 s ch lim need lf df i t ⦃ fun r => i.val ≤ r.2.2.1.val ∧ r.2.2.2.val ≤ max t.val need.val ∧
      r.2.2.1.val ≤ max i.val (lim.val + 511) ∧ r.2.2.1.val + 511 * t.val ≤ i.val + 511 * r.2.2.2.val ⦄ := by
  rw [slot.a_walk_loop2]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, t') => need.val - t'.val)
    (inv := fun (lf', df', i', t') => LeAll lf'.val t'.val ∧ LeAll df'.val t'.val ∧
      i.val ≤ i'.val ∧ t'.val ≤ max t.val need.val ∧
      i'.val ≤ max i.val (lim.val + 511) ∧ i'.val + 511 * t.val ≤ i.val + 511 * t'.val)
  · rintro ⟨lf', df', i', t'⟩ ⟨hlf', hdf', hi', ht', hi2', hi3'⟩
    simp only [slot.a_walk_loop2.body]
    step*
    -- `step*` stops at the tuple `if` (`let (lf1, df1, i3) ← if l ≥ 3 then .. else ..`).
    -- `WP.spec_bind` proves the `if` once against an intermediate post and the rest once after it,
    -- instead of `split` duplicating the rest per branch.
    apply WP.spec_bind (Pₘ := fun (x : Std.Array Std.U32 512#usize × Std.Array Std.U32 32#usize × Std.Usize) =>
      LeAll x.1.val (t'.val + 1) ∧ LeAll x.2.1.val (t'.val + 1) ∧ i'.val < x.2.2.val ∧ x.2.2.val ≤ i'.val + 511)
    · split
      · -- a match: one length counter and one distance counter go up
        step*
        all_goals try (have := LeAll_get hlf' i6.val (by scalar_tac))
        all_goals try (have := LeAll_get hdf' i14.val (by scalar_tac))
        all_goals try scalar_tac
        refine ⟨?_, ?_, by scalar_tac, by scalar_tac⟩
        · rw [a_post, Array.set_val_eq]; exact LeAll_set_succ hlf' _ _ (by scalar_tac)
        · rw [a1_post, Array.set_val_eq]; exact LeAll_set_succ hdf' _ _ (by scalar_tac)
      · -- a literal: one literal counter goes up
        step*
        all_goals try (have := LeAll_get hlf' i5.val (by scalar_tac))
        all_goals try scalar_tac
        refine ⟨?_, LeAll_mono hdf' (by omega), by scalar_tac, by scalar_tac⟩
        rw [a_post, Array.set_val_eq]; exact LeAll_set_succ hlf' _ _ (by scalar_tac)
    · rintro ⟨lf1, df1, i3⟩ ⟨h1, h2, h3, h4⟩
      step*
      refine ⟨?_, ?_, by scalar_tac, by scalar_tac, by scalar_tac, by scalar_tac, by scalar_tac⟩
      · rw [show t1.val = t'.val + 1 by scalar_tac]; exact h1
      · rw [show t1.val = t'.val + 1 by scalar_tac]; exact h2
  · exact ⟨hlf, hdf, le_refl _, by omega, by omega, by omega⟩

-- @owner engA @status DONE @changed (CONTRACT_ISSUES engA A3) @note posts used by a_engine (t <= need for used+t, p1 >= p0) and a_sample_pass (w.0 - a)
-- [engA] fn callees: a_walk_loop0 a_walk_loop1 a_walk_loop2
@[local step]
theorem a_walk_spec (s : Slice Std.U8) (ch) (p0 lim need : Std.Usize) (lf df)
    (hlim : lim.val ≤ 2 ^ 31) (hls : lim.val ≤ s.length) (hneed : need.val ≤ 2 ^ 31) :
    slot.a_walk s ch p0 lim need lf df ⦃ fun r => p0.val ≤ r.1.1.val ∧ r.1.2.val ≤ need.val ∧
      r.1.1.val ≤ max p0.val (lim.val + 511) ∧ r.1.1.val ≤ p0.val + 511 * r.1.2.val ⦄ := by
  rw [slot.a_walk]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

-- @owner engA @status DONE @note inv cost.length = cl
-- [engA] loop callees: -
@[local step]
theorem a_dp_pass_loop0_spec (pe : Std.Usize) (cost) (cl z : Std.Usize) (hpe : pe.val ≤ 2 ^ 31) (hcl : cl.val = cost.length) :
    slot.a_dp_pass_loop0 pe cost cl z ⦃ fun r => r.length = cost.length ⦄ := by
  rw [slot.a_dp_pass_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, z_) => cl.val - z_.val)
    (inv := fun (cost_, _) => cost_.length = cost.length)
  · rintro ⟨cost_, z_⟩ hinv
    simp only [slot.a_dp_pass_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · rfl

-- @owner engA @status DONE @note measure stop+1-at
-- [engA] loop callees: -
@[local step]
theorem a_dp_pass_loop1_loop0_loop0_spec (lc) (cost : alloc.vec.Vec Std.U32) (stop base mbest at0 l) (hstop : stop.val < cost.length) :
    slot.a_dp_pass_loop1_loop0_loop0 lc cost stop base mbest at0 l ⦃ fun _ => True ⦄ := by
  rw [slot.a_dp_pass_loop1_loop0_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (mbest_, at0_, l_) => stop.val + 1 - at0_.val)
    (inv := fun _ => True)
  · rintro ⟨mbest_, at0_, l_⟩ _
    simp only [slot.a_dp_pass_loop1_loop0_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial

-- @owner engA @status DONE @note copy of loop0 (Aeneas duplicated the continuation)
-- [engA] loop callees: -
@[local step]
theorem a_dp_pass_loop1_loop0_loop1_spec (lc) (cost : alloc.vec.Vec Std.U32) (stop base mbest at0 l) (hstop : stop.val < cost.length) :
    slot.a_dp_pass_loop1_loop0_loop1 lc cost stop base mbest at0 l ⦃ fun _ => True ⦄ := by
  rw [slot.a_dp_pass_loop1_loop0_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (mbest_, at0_, l_) => stop.val + 1 - at0_.val)
    (inv := fun _ => True)
  · rintro ⟨mbest_, at0_, l_⟩ _
    simp only [slot.a_dp_pass_loop1_loop0_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial

-- @owner engA @status DONE @changed (CONTRACT_ISSUES engA A4) @note the candidate loop of position i; state (best, bd, prev, pd, j); inv = the three bounds; stop <= i+258
-- [engA] loop callees: a_dp_pass_loop1_loop0_loop0 a_dp_pass_loop1_loop0_loop1
@[local step]
theorem a_dp_pass_loop1_loop0_spec (mb lc dc) (cost : alloc.vec.Vec Std.U32) (cl i : Std.Usize) (bias best bd) (prev pd : Std.Usize) (j top : Std.Usize)
    (hcl : cl.val = cost.length) (hi : i.val ≤ 2 ^ 31) (htop : top.val ≤ mb.length)
    (hprev : prev.val ≤ i.val + 258) (hpd : pd.val ≤ 32768) (hbd : bd.val ≤ 32767) :
    slot.a_dp_pass_loop1_loop0 mb lc dc cost cl i bias best bd prev pd j top ⦃ fun r =>
      prev.val ≤ r.2.2.1.val ∧ r.2.2.1.val ≤ i.val + 258 ∧ r.2.2.2.val ≤ 32768 ∧ r.2.1.val ≤ 32767 ⦄ := by
  rw [slot.a_dp_pass_loop1_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, j_) => top.val - j_.val)
    (inv := fun (_, bd_, prev_, pd_, _) => prev.val ≤ prev_.val ∧ prev_.val ≤ i.val + 258 ∧
      pd_.val ≤ 32768 ∧ bd_.val ≤ 32767)
  · rintro ⟨best_, bd_, prev_, pd_, j_⟩ ⟨hp0, hp1, hpd_, hbd_⟩
    simp only [slot.a_dp_pass_loop1_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact ⟨le_refl _, hprev, hpd, hbd⟩

-- @owner engA @status DONE @note the backward-extension length loop
-- [engA] loop callees: -
@[local step]
theorem a_dp_pass_loop1_loop1_spec (lc) (cost : alloc.vec.Vec Std.U32) (stop base mbest at0 l) (hstop : stop.val < cost.length) :
    slot.a_dp_pass_loop1_loop1 lc cost stop base mbest at0 l ⦃ fun _ => True ⦄ := by
  rw [slot.a_dp_pass_loop1_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (mbest_, at0_, l_) => stop.val + 1 - at0_.val)
    (inv := fun _ => True)
  · rintro ⟨mbest_, at0_, l_⟩ _
    simp only [slot.a_dp_pass_loop1_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial

-- @owner engA @status DONE @note i counts down (measure i); inv: i <= pe-bounds above, xl <= 258, xd <= 32768, cost/ch lengths kept. 11 bind-ifs: use WP.spec_bind (sec_examples) instead of repeat' split. Uses ~893k heartbeats (the default limit is 1M): per-theorem limit 4M as a margin
-- [engA] loop callees: a_dp_pass_loop1_loop0 a_dp_pass_loop1_loop1 a_slot_of
set_option maxHeartbeats 4000000 in
@[local step]
theorem a_dp_pass_loop1_spec (s : Slice Std.U8) (mp mb : alloc.vec.Vec Std.U32) (p0 lit lc dc) (cost ch : alloc.vec.Vec Std.U32)
    (cl i e xl xd : Std.Usize)
    (hcl : cl.val = cost.length) (hi : i.val < cl.val) (hmp : i.val < mp.length) (hs : i.val ≤ s.length)
    (hch : i.val ≤ ch.length) (hi31 : i.val ≤ 2 ^ 31) (hxl : xl.val ≤ 258) (hxd : xd.val ≤ 32768) :
    slot.a_dp_pass_loop1 s mp mb p0 lit lc dc cost ch cl i e xl xd ⦃ fun _ => True ⦄ := by
  rw [slot.a_dp_pass_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, i_, _, _, _) => i_.val)
    (inv := fun ((cost_ : alloc.vec.Vec Std.U32), (ch_ : alloc.vec.Vec Std.U32), (i_ : Std.Usize), _,
        (xl_ : Std.Usize), (xd_ : Std.Usize)) =>
      cost_.length = cl.val ∧ ch_.length = ch.length ∧ i_.val ≤ i.val ∧ xl_.val ≤ 258 ∧ xd_.val ≤ 32768)
  · rintro ⟨cost_, ch_, i_, e_, xl_, xd_⟩ ⟨hc_, hch_, hi_, hxl_, hxd_⟩
    simp only [slot.a_dp_pass_loop1.body]
    step*
    -- `top`: the pure `if` becomes an intermediate post
    apply WP.spec_bind (Pₘ := fun (top : Std.Usize) => top.val ≤ mb.length)
    · split <;> step* <;> scalar_tac
    rintro top htop
    step*
    apply WP.spec_bind (Pₘ := fun (el : Std.Usize) => el.val ≤ 258)
    · split <;> step* <;> scalar_tac
    rintro el hel
    step*
    -- seven leaves, each stopped at a tuple `if`: the extension's `(best2, bd1)` (two leaves),
    -- then `(cost1, i23)` (all): one intermediate post each instead of splitting the rest
    all_goals
      try (
        apply WP.spec_bind (Pₘ := fun (x : Std.U32 × Std.U32) => x.2.val ≤ 32767)
        · split <;> step* <;> scalar_tac
        rintro ⟨best2, bd1⟩ hbd1
        step*)
    all_goals
      apply WP.spec_bind (Pₘ := fun (x : alloc.vec.Vec Std.U32 × Std.U32) => x.1.length = cost_.length)
      · split <;> step* <;> scalar_tac
      rintro ⟨cost1, i23⟩ hc1
      step*
      scalar_tac
  · exact ⟨hcl.symm, rfl, le_refl _, hxl, hxd⟩

-- @owner engA @status DONE @note the guard pe < cl && pe < mp.len && pe <= s.len && pe <= ch.len gives the rest
-- [engA] fn callees: a_dp_pass_loop0 a_dp_pass_loop1
@[local step]
theorem a_dp_pass_spec (s : Slice Std.U8) (mp mb) (p0 pe : Std.Usize) (lit lc dc) (cost ch)
    (hpe : pe.val ≤ 2 ^ 31) :
    slot.a_dp_pass s mp mb p0 pe lit lc dc cost ch ⦃ fun _ => True ⦄ := by
  rw [slot.a_dp_pass]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

-- @owner engA @status DONE
-- [engA] loop callees: -
@[local step]
theorem a_sample_pass_loop0_loop0_spec (lf zf b) :
    slot.a_sample_pass_loop0_loop0 lf zf b ⦃ fun _ => True ⦄ := by
  rw [slot.a_sample_pass_loop0_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (zf_, b_) => 512 - b_.val)
    (inv := fun _ => True)
  · rintro ⟨zf_, b_⟩ _
    simp only [slot.a_sample_pass_loop0_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial

-- @owner engA @status DONE
-- [engA] loop callees: -
@[local step]
theorem a_sample_pass_loop0_loop1_spec (df zd b) :
    slot.a_sample_pass_loop0_loop1 df zd b ⦃ fun _ => True ⦄ := by
  rw [slot.a_sample_pass_loop0_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (zd_, b_) => 32 - b_.val)
    (inv := fun _ => True)
  · rintro ⟨zd_, b_⟩ _
    simp only [slot.a_sample_pass_loop0_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial

-- @owner engA @status DONE @changed (CONTRACT_ISSUES engA A1) @note measure pe+A_SEG*A_SAMPLE-a; needs A_SEG/A_SAMPLE facts (A_SEG >= 256, A_SEG*A_SAMPLE >= A_SEG+512); inv sb <= a, st <= a (A5 makes it unnecessary)
-- [engA] loop callees: a_dp_pass a_sample_pass_loop0_loop0 a_sample_pass_loop0_loop1 a_walk
@[local step]
theorem a_sample_pass_loop0_spec (s : Slice Std.U8) (mp mb) (pe : Std.Usize) (lit lc dc cost ch lf df zf zd) (sb st a : Std.Usize)
    (hpe : pe.val ≤ 2 ^ 30) (hps : pe.val ≤ s.length) (hsb : sb.val ≤ a.val) (hst : st.val ≤ a.val)
    (ha : a.val ≤ pe.val + slot.A_SEG.val * slot.A_SAMPLE.val) :
    slot.a_sample_pass_loop0 s mp mb pe lit lc dc cost ch lf df zf zd sb st a ⦃ fun _ => True ⦄ := by
  have hseg := A_SEG_bounds
  rw [slot.a_sample_pass_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, _, _, _, _, a_) => pe.val - a_.val)
    (inv := fun (_, _, _, _, _, _, sb_, st_, a_) => sb_.val ≤ a_.val ∧ st_.val ≤ a_.val ∧
      a_.val ≤ pe.val + slot.A_SEG.val * slot.A_SAMPLE.val)
  · rintro ⟨cost_, ch_, lf_, df_, zf_, zd_, sb_, st_, a_⟩ ⟨hsb_, hst_, ha_⟩
    simp only [slot.a_sample_pass_loop0.body]
    step*
    -- the walk's `(end, tokens)` pair is bound by a nested pattern: name its components
    cases ‹Std.Usize × Std.Usize›
    step*
    all_goals scalar_tac
  · exact ⟨hsb, hst, ha⟩

-- @owner engA @status DONE
-- [engA] loop callees: -
@[local step]
theorem a_sample_pass_loop1_spec (lf zf b) :
    slot.a_sample_pass_loop1 lf zf b ⦃ fun _ => True ⦄ := by
  rw [slot.a_sample_pass_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (lf_, b_) => 512 - b_.val)
    (inv := fun _ => True)
  · rintro ⟨lf_, b_⟩ _
    simp only [slot.a_sample_pass_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial

-- @owner engA @status DONE
-- [engA] loop callees: -
@[local step]
theorem a_sample_pass_loop2_spec (df zd b) :
    slot.a_sample_pass_loop2 df zd b ⦃ fun _ => True ⦄ := by
  rw [slot.a_sample_pass_loop2]
  apply Std.loop.spec_decr_nat
    (measure := fun (df_, b_) => 32 - b_.val)
    (inv := fun _ => True)
  · rintro ⟨df_, b_⟩ _
    simp only [slot.a_sample_pass_loop2.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial

-- @owner engA @status DONE @changed (CONTRACT_ISSUES engA A2)
-- [engA] fn callees: a_sample_pass_loop0 a_sample_pass_loop1 a_sample_pass_loop2
@[local step]
theorem a_sample_pass_spec (s : Slice Std.U8) (mp mb) (p0 pe : Std.Usize) (lit lc dc cost ch lf df)
    (hpe : pe.val ≤ 2 ^ 30) (hps : pe.val ≤ s.length) (hp0 : p0.val ≤ pe.val) :
    slot.a_sample_pass s mp mb p0 pe lit lc dc cost ch lf df ⦃ fun _ => True ⦄ := by
  have hseg := A_SEG_bounds
  rw [slot.a_sample_pass]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

-- @owner engA @status DONE
-- [engA] loop callees: -
@[local step]
theorem a_add_counts_loop0_spec (dst a b k) :
    slot.a_add_counts_loop0 dst a b k ⦃ fun _ => True ⦄ := by
  rw [slot.a_add_counts_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (dst_, k_) => 512 - k_.val)
    (inv := fun _ => True)
  · rintro ⟨dst_, k_⟩ _
    simp only [slot.a_add_counts_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial

-- @owner engA @status DONE
-- [engA] loop callees: -
@[local step]
theorem a_add_counts_loop1_spec (dd x y k) :
    slot.a_add_counts_loop1 dd x y k ⦃ fun _ => True ⦄ := by
  rw [slot.a_add_counts_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (dd_, k_) => 32 - k_.val)
    (inv := fun _ => True)
  · rintro ⟨dd_, k_⟩ _
    simp only [slot.a_add_counts_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial

-- @owner engA @status DONE
-- [engA] fn callees: a_add_counts_loop0 a_add_counts_loop1
@[local step]
theorem a_add_counts_spec (dst a b dd x y) :
    slot.a_add_counts dst a b dd x y ⦃ fun _ => True ⦄ := by
  rw [slot.a_add_counts]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

-- @owner engA @status DONE @note lz32_le_of_pow_le x 0; table fact A_LOG_FRAC_le (entries <= 64, by decide)
-- [engA] fn callees: -
@[local step]
theorem a_lg64_spec (x) :
    slot.a_lg64 x ⦃ fun r => r.val ≤ 2048 ⦄ := by
  rw [slot.a_lg64]
  have hlz := lz32_bound x
  have htab := A_LOG_FRAC_le
  step*
  repeat' (split <;> step*)
  all_goals try (have := LeAll_get htab i3.val (by scalar_tac))
  all_goals scalar_tac

-- @owner engA @status DONE
-- [engA] fn callees: a_lg64
@[local step]
theorem a_sym_cost_spec (f : Std.U32) (g : Std.U32) (hg : g.val ≤ 65536) :
    slot.a_sym_cost f g ⦃ fun r => r.val ≤ 1152 ⦄ := by
  rw [slot.a_sym_cost]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

-- @owner engA @status DONE @note the binder must not be called `slot` (it would shadow the namespace)
-- [engA] fn callees: -
@[local step]
theorem a_dist_extra_spec (slt : Std.Usize) :
    slot.a_dist_extra slt ⦃ fun r => r.val ≤ slt.val / 2 ⦄ := by
  rw [slot.a_dist_extra]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

-- @owner engA @status DONE
-- [engA] fn callees: -
@[local step]
theorem a_len_extra_spec (slt) :
    slot.a_len_extra slt ⦃ fun r => r.val ≤ 5 ⦄ := by
  rw [slot.a_len_extra]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

-- @owner engA @status DONE
-- [engA] loop callees: -
@[local step]
theorem a_set_costs_loop0_spec (lf tl i) :
    slot.a_set_costs_loop0 lf tl i ⦃ fun _ => True ⦄ := by
  rw [slot.a_set_costs_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (tl_, i_) => 286 - i_.val)
    (inv := fun _ => True)
  · rintro ⟨tl_, i_⟩ _
    simp only [slot.a_set_costs_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial

-- @owner engA @status DONE
-- [engA] loop callees: -
@[local step]
theorem a_set_costs_loop1_spec (df i td) :
    slot.a_set_costs_loop1 df i td ⦃ fun _ => True ⦄ := by
  rw [slot.a_set_costs_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (i_, td_) => 30 - i_.val)
    (inv := fun _ => True)
  · rintro ⟨i_, td_⟩ _
    simp only [slot.a_set_costs_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial

-- @owner engA @status DONE
-- [engA] loop callees: a_sym_cost
@[local step]
theorem a_set_costs_loop2_spec (lf lit i) (gl : Std.U32) (hgl : gl.val ≤ 65536) :
    slot.a_set_costs_loop2 lf lit i gl ⦃ fun _ => True ⦄ := by
  rw [slot.a_set_costs_loop2]
  apply Std.loop.spec_decr_nat
    (measure := fun (lit_, i_) => 256 - i_.val)
    (inv := fun _ => True)
  · rintro ⟨lit_, i_⟩ _
    simp only [slot.a_set_costs_loop2.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial

-- @owner engA @status DONE
-- [engA] loop callees: a_len_extra a_len_slot a_sym_cost
@[local step]
theorem a_set_costs_loop3_spec (lf lc i) (gl : Std.U32) (hgl : gl.val ≤ 65536) :
    slot.a_set_costs_loop3 lf lc i gl ⦃ fun _ => True ⦄ := by
  rw [slot.a_set_costs_loop3]
  apply Std.loop.spec_decr_nat
    (measure := fun (lc_, i_) => 258 + 1 - i_.val)
    (inv := fun _ => True)
  · rintro ⟨lc_, i_⟩ _
    simp only [slot.a_set_costs_loop3.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial

-- @owner engA @status DONE @note i < 30 in the guard: a_dist_extra i <= 14
-- [engA] loop callees: a_dist_extra a_sym_cost
@[local step]
theorem a_set_costs_loop4_spec (df dc) (i : Std.Usize) (gd : Std.U32) (hgd : gd.val ≤ 65536) :
    slot.a_set_costs_loop4 df dc i gd ⦃ fun _ => True ⦄ := by
  rw [slot.a_set_costs_loop4]
  apply Std.loop.spec_decr_nat
    (measure := fun (dc_, i_) => 30 - i_.val)
    (inv := fun _ => True)
  · rintro ⟨dc_, i_⟩ _
    simp only [slot.a_set_costs_loop4.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial

-- @owner engA @status DONE
-- [engA] fn callees: a_lg64 a_set_costs_loop0 a_set_costs_loop1 a_set_costs_loop2 a_set_costs_loop3 a_set_costs_loop4
@[local step]
theorem a_set_costs_spec (lf df lit lc dc) :
    slot.a_set_costs lf df lit lc dc ⦃ fun _ => True ⦄ := by
  rw [slot.a_set_costs]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

-- @owner engA @status DONE @note lf[s[i]] += 1 is an A4 site: inv LeAll lf i (i <= 65536); with A4: True, no LeAll
-- [engA] loop callees: -
@[local step]
theorem a_first_model_loop0_spec (s : Slice Std.U8) (lf) (m i : Std.Usize) (hm : m.val ≤ s.length) (hm2 : m.val ≤ 65536)
    (hlf : LeAll lf.val i.val) :
    slot.a_first_model_loop0 s lf m i ⦃ fun _ => True ⦄ := by
  rw [slot.a_first_model_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, i_) => m.val - i_.val)
    (inv := fun (lf_, i_) => LeAll lf_.val i_.val)
  · rintro ⟨lf_, i_⟩ hlf_
    simp only [slot.a_first_model_loop0.body]
    step*
    all_goals try (have := LeAll_get hlf_ i2.val (by scalar_tac))
    all_goals try scalar_tac
    refine ⟨?_, by scalar_tac⟩
    rw [show i5.val = i_.val + 1 by scalar_tac, a_post, Array.set_val_eq]
    exact LeAll_set_succ hlf_ _ _ (by scalar_tac)
  · exact hlf

-- @owner engA @status DONE
-- [engA] loop callees: -
@[local step]
theorem a_first_model_loop1_spec (lf i) :
    slot.a_first_model_loop1 lf i ⦃ fun _ => True ⦄ := by
  rw [slot.a_first_model_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (lf_, i_) => 29 - i_.val)
    (inv := fun _ => True)
  · rintro ⟨lf_, i_⟩ _
    simp only [slot.a_first_model_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial

-- @owner engA @status DONE
-- [engA] loop callees: -
@[local step]
theorem a_first_model_loop2_spec (df i) :
    slot.a_first_model_loop2 df i ⦃ fun _ => True ⦄ := by
  rw [slot.a_first_model_loop2]
  apply Std.loop.spec_decr_nat
    (measure := fun (df_, i_) => 30 - i_.val)
    (inv := fun _ => True)
  · rintro ⟨df_, i_⟩ _
    simp only [slot.a_first_model_loop2.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial

-- @owner engA @status DONE
-- [engA] fn callees: a_first_model_loop0 a_first_model_loop1 a_first_model_loop2 a_set_costs
@[local step]
theorem a_first_model_spec (s lit lc dc) :
    slot.a_first_model s lit lc dc ⦃ fun _ => True ⦄ := by
  rw [slot.a_first_model]
  step*
  repeat' (split <;> step*)
  all_goals exact engA_LeAll_repeat _ _ _ (by simp)

-- @owner engA @status DONE @changed (CONTRACT_ISSUES engA A6) @note kraft wraps: measure (512 - q) * 16 + (15 - len[sym[q] % 512]) (lexicographic); see sec_examples
-- [engA] loop callees: -
@[local step]
theorem a_kraft_fix_loop_spec (sym m) (len : Array Std.U32 512#usize) (kraft q) (hlen : LeAll len.val 15) :
    slot.a_kraft_fix_loop sym m len kraft q ⦃ fun r => LeAll r.val 15 ⦄ := by
  rw [slot.a_kraft_fix_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun ((len_ : Array Std.U32 512#usize), _, (q_ : Std.Usize)) =>
      (512 - q_.val) * 16 + (15 - (len_.val[(sym.val[q_.val]!).val % 512]!).val))
    (inv := fun (len_, _, _) => LeAll len_.val 15)
  · rintro ⟨len_, kraft_, q_⟩ hlen_
    dsimp only at hlen_
    simp only [slot.a_kraft_fix_loop.body]
    step*
    · -- one code gets one bit longer: the second component of the measure drops
      have hq : (sym.val[q_.val]!).val % 512 = s2.val := by
        rw [getElem!_pos sym.val q_.val (by scalar_tac), ← i_post]; scalar_tac
      have ha : a.val[s2.val]! = i5 := by
        rw [a_post, Array.set_val_eq, getElem!_pos _ _ (by simp; scalar_tac), List.getElem_set_self]
      have hl : len_.val[s2.val]! = i2 := by
        rw [getElem!_pos _ _ (by scalar_tac), ← i2_post]
      refine ⟨?_, ?_⟩
      · rw [a_post, Array.set_val_eq]; exact LeAll_set hlen_ _ _ (by scalar_tac)
      · rw [hq, ha, hl]; scalar_tac
    · -- the next symbol: the first component drops
      exact ⟨hlen_, by scalar_tac⟩
  · exact hlen

-- @owner engA @status DONE @note the loop keeps LeAll len 15 (increments only below 15); put the LeAll in a_kraft_fix_loop's post too
-- [engA] fn callees: a_kraft_fix_loop
@[local step]
theorem a_kraft_fix_spec (sym m) (len : Array Std.U32 512#usize) (kraft0) (hlen : LeAll len.val 15) :
    slot.a_kraft_fix sym m len kraft0 ⦃ fun r => LeAll r.val 15 ⦄ := by
  unfold slot.a_kraft_fix
  step*

-- @owner engA @status DONE
-- [engA] fn callees: -
@[local step]
theorem a_lighter_spec (w a) (b : Std.Usize) (m k) (hb : b.val ≤ 4096) :
    slot.a_lighter w a b m k ⦃ fun r => r.2.1.val ≤ a.val + 1 ∧ r.2.2.val ≤ b.val + 1 ⦄ := by
  rw [slot.a_lighter]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

-- @owner engA @status DONE @note measure j; inv j < 512
-- [engA] loop callees: -
@[local step]
theorem a_sorted_insert_loop_spec (sym freq fv) (j : Std.Usize) (hj : j.val < 512) :
    slot.a_sorted_insert_loop sym freq fv j ⦃ fun r => r.2.val < 512 ⦄ := by
  rw [slot.a_sorted_insert_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, j_) => j_.val)
    (inv := fun (_, j_) => j_.val < 512)
  · rintro ⟨sym_, j_⟩ hinv
    simp only [slot.a_sorted_insert_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact hj

-- @owner engA @status DONE
-- [engA] fn callees: a_sorted_insert_loop
@[local step]
theorem a_sorted_insert_spec (sym freq m v) :
    slot.a_sorted_insert sym freq m v ⦃ fun _ => True ⦄ := by
  rw [slot.a_sorted_insert]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

-- @owner engA @status DONE @changed (CONTRACT_ISSUES engA A5) @note measure 512-i; inv m <= i <= 512, LeAll len 15
-- [engA] loop callees: a_sorted_insert
@[local step]
theorem a_huff_lengths_loop0_spec (freq n) (len : Array Std.U32 512#usize) (sym) (m i : Std.Usize)
    (hm : m.val ≤ i.val) (hi : i.val ≤ 512) (hlen : LeAll len.val 15) :
    slot.a_huff_lengths_loop0 freq n len sym m i ⦃ fun r => r.2.2.val ≤ 512 ∧ LeAll r.1.val 15 ⦄ := by
  rw [slot.a_huff_lengths_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, i_) => 512 - i_.val)
    (inv := fun (len_, _, m_, i_) => m_.val ≤ i_.val ∧ i_.val ≤ 512 ∧ LeAll len_.val 15)
  · rintro ⟨len_, sym_, m_, i_⟩ ⟨hm_, hi_, hlen_⟩
    simp only [slot.a_huff_lengths_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals
      refine ⟨by scalar_tac, by scalar_tac, ?_, by scalar_tac⟩
      rw [a_post, Array.set_val_eq]; exact LeAll_set hlen_ _ _ (by scalar_tac)
  · exact ⟨hm, hi, hlen⟩

-- @owner engA @status DONE
-- [engA] loop callees: -
@[local step]
theorem a_huff_lengths_loop1_spec (freq sym m i w) :
    slot.a_huff_lengths_loop1 freq sym m i w ⦃ fun _ => True ⦄ := by
  rw [slot.a_huff_lengths_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (i_, w_) => m.val - i_.val)
    (inv := fun _ => True)
  · rintro ⟨i_, w_⟩ _
    simp only [slot.a_huff_lengths_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial

-- @owner engA @status DONE @note `let i <- k + 1; let i1 <- 2 * m; if i < i1` before the k < 1024 test; measure 1024 - k
-- [engA] loop callees: a_lighter
@[local step]
theorem a_huff_lengths_loop2_spec (m : Std.Usize) (w par) (a b k : Std.Usize) (hm : m.val ≤ 512)
    (ha : a.val ≤ 2 * k.val) (hb : b.val ≤ 2 * k.val) (hk : k.val ≤ 1024) :
    slot.a_huff_lengths_loop2 m w par a b k ⦃ fun r => r.2.val ≤ 1024 ⦄ := by
  rw [slot.a_huff_lengths_loop2]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, k_) => 1024 - k_.val)
    (inv := fun (_, _, a_, b_, k_) => a_.val ≤ 2 * k_.val ∧ b_.val ≤ 2 * k_.val ∧ k_.val ≤ 1024)
  · rintro ⟨w_, par_, a_, b_, k_⟩ ⟨ha_, hb_, hk_⟩
    simp only [slot.a_huff_lengths_loop2.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact ⟨ha, hb, hk⟩

-- @owner engA @status DONE
-- [engA] loop callees: -
@[local step]
theorem a_huff_lengths_loop3_spec (par d j) :
    slot.a_huff_lengths_loop3 par d j ⦃ fun _ => True ⦄ := by
  rw [slot.a_huff_lengths_loop3]
  apply Std.loop.spec_decr_nat
    (measure := fun (d_, j_) => j_.val)
    (inv := fun _ => True)
  · rintro ⟨d_, j_⟩ _
    simp only [slot.a_huff_lengths_loop3.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial

-- @owner engA @status DONE @note writes l in [1,15]
-- [engA] loop callees: -
@[local step]
theorem a_huff_lengths_loop4_spec (len : Array Std.U32 512#usize) (sym m i d kraft) (hlen : LeAll len.val 15) :
    slot.a_huff_lengths_loop4 len sym m i d kraft ⦃ fun r => LeAll r.1.val 15 ⦄ := by
  rw [slot.a_huff_lengths_loop4]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, i_, _) => m.val - i_.val)
    (inv := fun (len_, _, _) => LeAll len_.val 15)
  · rintro ⟨len_, i_, kraft_⟩ hlen_
    dsimp only at hlen_
    simp only [slot.a_huff_lengths_loop4.body]
    step*
    repeat' (split <;> step*)
    all_goals try scalar_tac
    all_goals
      refine ⟨?_, by scalar_tac⟩
      rw [a_post, Array.set_val_eq]; exact LeAll_set hlen_ _ _ (by scalar_tac)
  · exact hlen

-- @owner engA @status DONE @note needed by a_set_costs_huff (hl[i] * 64); A6 (wrapping_mul) would make it True
-- [engA] fn callees: a_huff_lengths_loop0 a_huff_lengths_loop1 a_huff_lengths_loop2 a_huff_lengths_loop3 a_huff_lengths_loop4 a_kraft_fix
@[local step]
theorem a_huff_lengths_spec (freq n) (len : Array Std.U32 512#usize) (hlen : LeAll len.val 15) :
    slot.a_huff_lengths freq n len ⦃ fun r => LeAll r.val 15 ⦄ := by
  rw [slot.a_huff_lengths]
  step*
  repeat' (split <;> step*)
  all_goals try scalar_tac
  all_goals apply engA_LeAll_set_of_eq (by assumption) (by assumption) (by scalar_tac)

-- @owner engA @status DONE
-- [engA] loop callees: -
@[local step]
theorem a_set_costs_huff_loop0_spec (lf0 lf z) :
    slot.a_set_costs_huff_loop0 lf0 lf z ⦃ fun _ => True ⦄ := by
  rw [slot.a_set_costs_huff_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (lf_, z_) => 286 - z_.val)
    (inv := fun _ => True)
  · rintro ⟨lf_, z_⟩ _
    simp only [slot.a_set_costs_huff_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial

-- @owner engA @status DONE
-- [engA] loop callees: -
@[local step]
theorem a_set_costs_huff_loop1_spec (df dd i) :
    slot.a_set_costs_huff_loop1 df dd i ⦃ fun _ => True ⦄ := by
  rw [slot.a_set_costs_huff_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (dd_, i_) => 30 - i_.val)
    (inv := fun _ => True)
  · rintro ⟨dd_, i_⟩ _
    simp only [slot.a_set_costs_huff_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial

-- @owner engA @status DONE
-- [engA] loop callees: -
@[local step]
theorem a_set_costs_huff_loop2_spec (lf i tl) :
    slot.a_set_costs_huff_loop2 lf i tl ⦃ fun _ => True ⦄ := by
  rw [slot.a_set_costs_huff_loop2]
  apply Std.loop.spec_decr_nat
    (measure := fun (i_, tl_) => 286 - i_.val)
    (inv := fun _ => True)
  · rintro ⟨i_, tl_⟩ _
    simp only [slot.a_set_costs_huff_loop2.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial

-- @owner engA @status DONE
-- [engA] loop callees: -
@[local step]
theorem a_set_costs_huff_loop3_spec (df i td) :
    slot.a_set_costs_huff_loop3 df i td ⦃ fun _ => True ⦄ := by
  rw [slot.a_set_costs_huff_loop3]
  apply Std.loop.spec_decr_nat
    (measure := fun (i_, td_) => 30 - i_.val)
    (inv := fun _ => True)
  · rintro ⟨i_, td_⟩ _
    simp only [slot.a_set_costs_huff_loop3.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial

-- @owner engA @status DONE
-- [engA] loop callees: -
@[local step]
theorem a_set_costs_huff_loop4_spec (lit) (hl : Array Std.U32 512#usize) (i) (ul : Std.U32) (hhl : LeAll hl.val 15) :
    slot.a_set_costs_huff_loop4 lit hl i ul ⦃ fun _ => True ⦄ := by
  rw [slot.a_set_costs_huff_loop4]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, i_) => 256 - i_.val)
    (inv := fun _ => True)
  · rintro ⟨lit_, i_⟩ _
    simp only [slot.a_set_costs_huff_loop4.body]
    step*
    repeat' (split <;> step*)
    all_goals try (have := LeAll_get hhl i_.val (by scalar_tac))
    all_goals scalar_tac
  · trivial

-- @owner engA @status DONE
-- [engA] loop callees: a_len_extra a_len_slot
@[local step]
theorem a_set_costs_huff_loop5_spec (lc) (hl : Array Std.U32 512#usize) (i) (ul : Std.U32) (hhl : LeAll hl.val 15) (hul : ul.val ≤ 1152) :
    slot.a_set_costs_huff_loop5 lc hl i ul ⦃ fun _ => True ⦄ := by
  rw [slot.a_set_costs_huff_loop5]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, i_) => 259 - i_.val)
    (inv := fun _ => True)
  · rintro ⟨lc_, i_⟩ _
    simp only [slot.a_set_costs_huff_loop5.body]
    step*
    repeat' (split <;> step*)
    all_goals try (have := LeAll_get hhl i2.val (by scalar_tac))
    all_goals scalar_tac
  · trivial

-- @owner engA @status DONE
-- [engA] loop callees: a_dist_extra
@[local step]
theorem a_set_costs_huff_loop6_spec (dc) (i : Std.Usize) (hd : Array Std.U32 512#usize) (ud : Std.U32) (hhd : LeAll hd.val 15) (hud : ud.val ≤ 1152) :
    slot.a_set_costs_huff_loop6 dc i hd ud ⦃ fun _ => True ⦄ := by
  rw [slot.a_set_costs_huff_loop6]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, i_) => 30 - i_.val)
    (inv := fun _ => True)
  · rintro ⟨dc_, i_⟩ _
    simp only [slot.a_set_costs_huff_loop6.body]
    step*
    repeat' (split <;> step*)
    all_goals try (have := LeAll_get hhd i_.val (by scalar_tac))
    all_goals scalar_tac
  · trivial

-- @owner engA @status DONE
-- [engA] fn callees: a_huff_lengths a_lg64 a_set_costs_huff_loop0 a_set_costs_huff_loop1 a_set_costs_huff_loop2 a_set_costs_huff_loop3 a_set_costs_huff_loop4 a_set_costs_huff_loop5 a_set_costs_huff_loop6 a_sym_cost
@[local step]
theorem a_set_costs_huff_spec (lf0 df lit lc dc) :
    slot.a_set_costs_huff lf0 df lit lc dc ⦃ fun _ => True ⦄ := by
  rw [slot.a_set_costs_huff]
  step*
  all_goals exact engA_LeAll_repeat _ _ _ (by simp)

-- @owner engA @status DONE @note like mlen_loop (measure lim-k)
-- [engA] loop callees: -
@[local step]
theorem a_shared_loop_spec (s : Slice Std.U8) (a b lim : Std.Usize) (k)
    (ha : a.val + lim.val ≤ s.length) (hb : b.val + lim.val ≤ s.length) :
    slot.a_shared_loop s a b lim k ⦃ fun _ => True ⦄ := by
  rw [slot.a_shared_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun k_ => lim.val - k_.val)
    (inv := fun _ => True)
  · rintro k_ _
    simp only [slot.a_shared_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial

-- @owner engA @status DONE
-- [engA] fn callees: a_shared_loop
@[local step]
theorem a_shared_spec (s : Slice Std.U8) (a b lim : Std.Usize)
    (ha : a.val + lim.val ≤ s.length) (hb : b.val + lim.val ≤ s.length) :
    slot.a_shared s a b lim ⦃ fun _ => True ⦄ := by
  rw [slot.a_shared]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

-- @owner engA @status DONE
-- [engA] fn callees: -
@[local step]
theorem a_word_at_spec (s) (i : Std.Usize) (hi : i.val ≤ 2 ^ 31) :
    slot.a_word_at s i ⦃ fun _ => True ⦄ := by
  rw [slot.a_word_at]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

-- @owner engA @status DONE
-- [engA] fn callees: a_word_at
@[local step]
theorem a_word_pair_spec (s) (a b : Std.Usize) (ha : a.val ≤ 2 ^ 31) (hb : b.val ≤ 2 ^ 31) :
    slot.a_word_pair s a b ⦃ fun _ => True ⦄ := by
  rw [slot.a_word_pair]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

-- @owner engA @status DONE @note state (k, w) with w a pair: `rintro ⟨k, ⟨w0, w1⟩⟩` and `measure := fun (k, _) => 258 - k.val`
-- [engA] loop callees: a_word_pair
@[local step]
theorem a_probe_loop_spec (s) (p q k : Std.Usize) (w) (hp : p.val ≤ 2 ^ 30) (hq : q.val ≤ 2 ^ 30) (hk : k.val ≤ 258) :
    slot.a_probe_loop s p q k w ⦃ fun r => r.1.val ≤ 258 ⦄ := by
  rw [slot.a_probe_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (k_, _) => 258 - k_.val)
    (inv := fun (k_, _) => k_.val ≤ 258)
  · rintro ⟨k_, ⟨w0, w1⟩⟩ hinv
    simp only [slot.a_probe_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact hk

-- @owner engA @status DONE
-- [engA] fn callees: a_probe_loop a_word_pair
@[local step]
theorem a_probe_spec (s) (p q k : Std.Usize) (hp : p.val ≤ 2 ^ 30) (hq : q.val ≤ 2 ^ 30) (hk : k.val ≤ 258) :
    slot.a_probe s p q k ⦃ fun r => r.1.val ≤ 258 ⦄ := by
  rw [slot.a_probe]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

-- @owner engA @status BLOCKED(A3) @changed (CONTRACT_ISSUES engA B2) @note mb.push: up to 256 pushes per position, n < 2^26 overflows a 32-bit usize length; A3 = guarded push. Otherwise measure depth-steps
-- [engA] loop callees: a_probe a_slot_of
@[local step]
theorem a_tree_insert_loop_spec (s : Slice Std.U8) (kid) (pos depth oldest : Std.Usize) (mb) (cur best lo_at hi_at lo_len hi_len steps : Std.Usize)
    (hpos : pos.val + 266 ≤ s.length) (hn26 : s.length < 67108864) (hlo : lo_len.val ≤ 258) (hhi : hi_len.val ≤ 258) (hbest : 2 ≤ best.val) :
    slot.a_tree_insert_loop s kid pos depth mb oldest cur best lo_at hi_at lo_len hi_len steps ⦃ fun _ => True ⦄ := by
  rw [slot.a_tree_insert_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, _, _, _, _, steps_) => depth.val - steps_.val)
    (inv := fun (_, _, _, best_, _, _, lo_len_, hi_len_, _) => lo_len_.val ≤ 258 ∧ hi_len_.val ≤ 258 ∧ 2 ≤ best_.val)
  · rintro ⟨kid_, mb_, cur_, best_, lo_at_, hi_at_, lo_len_, hi_len_, steps_⟩ ⟨hlo_, hhi_, hbest_⟩
    simp only [slot.a_tree_insert_loop.body, engA_ite_ok]
    step*
    · split <;> omega
    -- a longer match: a record (guarded push) and a new best
    apply WP.spec_bind (Pₘ := fun (x : alloc.vec.Vec Std.U32 × Std.Usize) => 2 ≤ x.2.val)
    · split
      · step*
        repeat' (split <;> step*)
        all_goals scalar_tac
      · step*
    rintro ⟨mb1, best1⟩ hb1
    step*
    -- the tree step: the new side lengths are probe lengths
    apply WP.spec_bind (Pₘ := fun (x : Std.Array Std.U32 65536#usize × Std.Usize × Std.Usize × Std.Usize ×
        Std.Usize × Std.Usize) => x.2.2.2.2.1.val ≤ 258 ∧ x.2.2.2.2.2.val ≤ 258)
    · repeat' (split <;> step*)
      all_goals scalar_tac
    rintro ⟨kid1, cur1, lo_at1, hi_at1, lo_len2, hi_len1⟩ ⟨hl2, hh1⟩
    step*
    all_goals scalar_tac
  · exact ⟨hlo, hhi, hbest⟩

-- @owner engA @status BLOCKED(A3) @changed (CONTRACT_ISSUES engA B2) @note `obtain ⟨q, t, h, c3, cr, cur⟩ := pre` before step* (the tuple parameter is destructured by a let)
-- [engA] fn callees: a_probe a_slot_of a_tree_insert_loop a_word_at
@[local step]
theorem a_tree_insert_spec (s : Slice Std.U8) (head kid h3 rct) (pos : Std.Usize) (pre depth mb) (hpos : pos.val + 266 ≤ s.length)
    (hn26 : s.length < 67108864) :
    slot.a_tree_insert s head kid h3 rct pos pre depth mb ⦃ fun _ => True ⦄ := by
  obtain ⟨q, t, h, c3, cr, cur⟩ := pre
  rw [slot.a_tree_insert]
  -- the window start: its value does not matter
  apply WP.spec_bind (Pₘ := fun (_ : Std.Usize) => True)
  · split
    all_goals step*
  rintro oldest -
  step*
  -- the latest 3-byte candidate (guarded push)
  apply WP.spec_bind (Pₘ := fun (x : alloc.vec.Vec Std.U32 × Std.Usize) => 2 ≤ x.2.val)
  · repeat' (split <;> step*)
    all_goals scalar_tac
  rintro ⟨mb1, best⟩ hb
  step*
  -- the latest 4-byte candidate (guarded push)
  apply WP.spec_bind (Pₘ := fun (x : alloc.vec.Vec Std.U32 × Std.Usize) => 2 ≤ x.2.val)
  · repeat' (split <;> step*)
    all_goals scalar_tac
  rintro ⟨mb2, best1⟩ hb1
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

-- @owner engA @status BLOCKED(A3) @changed (CONTRACT_ISSUES engA B2) @note the first arg `i` is `32 - A_HB` (facts 1 <= A_HB <= 32 in a_find_all); `cl - 3` in the skip branch needs skip >= 3; measure n - i1; mp.len = i1+1 needs inv (mp push) or A3; 15 bind-ifs + a big tuple: `simp only [body]` hits the recursion limit, use `unfold` + spec_bind
-- [engA] loop callees: a_shared a_slot_of a_tree_insert a_word_at
set_option maxHeartbeats 4000000 in
@[local step]
theorem a_find_all_loop_spec (i : Std.U32) (s : Slice Std.U8) (mp : alloc.vec.Vec Std.U32) (mb depth) (skip n : Std.Usize) (head kid h3 rct) (i1 cl cd : Std.Usize) (nq nt nh n3 nr nc)
    (hn : n.val = s.length) (hn26 : s.length < 67108864) (hi : i.val < 32) (hskip : 3 ≤ skip.val)
    (hmp : mp.length ≤ i1.val + 1) (hcd : 1 ≤ cd.val) :
    slot.a_find_all_loop i s mp mb depth skip n head kid h3 rct i1 cl cd nq nt nh n3 nr nc ⦃ fun _ => True ⦄ := by
  rw [slot.a_find_all_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, _, _, i1_, _, _, _, _, _, _, _, _) => n.val - i1_.val)
    (inv := fun ((mp_ : alloc.vec.Vec Std.U32), _, _, _, _, _, (i1_ : Std.Usize), _, (cd_ : Std.Usize), _, _, _, _, _, _) =>
      mp_.length ≤ i1_.val + 1 ∧ 1 ≤ cd_.val)
  · rintro ⟨mp_, mb_, head_, kid_, h3_, rct_, i1_, cl_, cd_, nq_, nt_, nh_, n3_, nr_, nc_⟩ ⟨hmp_, hcd_⟩
    unfold slot.a_find_all_loop.body
    simp only [engA_ite_ok, engA_ite_pair]
    step*
    -- one position: its records (tree search, skip record or tail record); only `cd >= 1` is carried
    apply WP.spec_bind (Pₘ := fun (x : alloc.vec.Vec Std.U32 × Std.Array Std.U32 65536#usize × Std.Array Std.U32 65536#usize ×
        Std.Array Std.U32 32768#usize × Std.Array Std.U32 65536#usize × Std.Usize × Std.Usize × Std.U64 × Std.Usize ×
        Std.Usize × Std.Usize × Std.Usize × Std.Usize) => 1 ≤ x.2.2.2.2.2.2.1.val)
    · split
      · step*
        · -- a searched or skipped position (at least 266 bytes left)
          apply WP.spec_bind (Pₘ := fun (y : alloc.vec.Vec Std.U32 × Std.Array Std.U32 65536#usize ×
              Std.Array Std.U32 65536#usize × Std.Array Std.U32 32768#usize × Std.Array Std.U32 65536#usize ×
              Std.Usize × Std.Usize × Std.Usize × Std.Usize × Std.Usize) => 1 ≤ y.2.2.2.2.2.2.1.val)
          · split
            · -- skip: the covering match's remainder as the only record (guarded push)
              step*
              split
              all_goals step*
              all_goals scalar_tac
            · -- search: tree insertion, then the new covering match (its distance code >= 1)
              step*
              apply WP.spec_bind (Pₘ := fun (z : Std.Array Std.U32 65536#usize × Std.Array Std.U32 65536#usize ×
                  Std.Array Std.U32 32768#usize × Std.Array Std.U32 65536#usize × Std.Usize × Std.Usize) =>
                  1 ≤ z.2.2.2.2.2.val)
              · repeat' (split <;> step*)
                all_goals scalar_tac
              rintro ⟨head3, kid3, h33, rct3, cl2, cd2⟩ hcd2
              step*
          rintro ⟨v, a, a1, a2, a3, i17, i18, i19, i20, i21⟩ h18
          step*
        · -- one of the last positions: the latest 3-byte occurrence (guarded push)
          apply WP.spec_bind (Pₘ := fun (_ : alloc.vec.Vec Std.U32 × Std.Array Std.U32 32768#usize) => True)
          · repeat' (split <;> step*)
            all_goals scalar_tac
          rintro ⟨v, a⟩ -
          step*
      · step*
        apply WP.spec_bind (Pₘ := fun (_ : alloc.vec.Vec Std.U32 × Std.Array Std.U32 32768#usize) => True)
        · repeat' (split <;> step*)
          all_goals scalar_tac
        rintro ⟨v, a⟩ -
        step*
    rintro ⟨mb1, head1, kid1, h31, rct1, cl1, cd1, nq1, nt1, nh1, n31, nr1, nc1⟩ hcd1
    step*
    apply WP.spec_bind (Pₘ := fun (_ : Std.Usize) => True)
    · split
      all_goals step*
    rintro cl2 -
    step*
    simp only [alloc.vec.Vec.length, *, List.length_append, List.length_singleton]
    scalar_tac
  · exact ⟨hmp, hcd⟩

-- @owner engA @status DONE @changed (CONTRACT_ISSUES engA A7) @note mp.push 0 needs mp.len < max: add (hmp : mp.length = 0) or A3
-- [engA] fn callees: a_find_all_loop a_word_at
@[local step]
theorem a_find_all_spec (s : Slice Std.U8) (mp : alloc.vec.Vec Std.U32) (mb depth) (skip : Std.Usize)
    (hn26 : s.length < 67108864) (hskip : 3 ≤ skip.val) (hmp : mp.length = 0) :
    slot.a_find_all s mp mb depth skip ⦃ fun _ => True ⦄ := by
  have hhb := A_HB_bounds
  rw [slot.a_find_all]
  step*
  all_goals try simp only [alloc.vec.Vec.length, *, List.length_append, List.length_singleton]
  all_goals scalar_tac

-- @owner engA @status DONE @note measure n+1-i; inv cost.length = i, i <= n+1
-- [engA] loop callees: -
@[local step]
theorem a_engine_loop0_spec (n : Std.Usize) (cost) (i : Std.Usize) (hn : n.val < 67108864) (hc : cost.length = i.val) :
    slot.a_engine_loop0 n cost i ⦃ fun _ => True ⦄ := by
  rw [slot.a_engine_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, i_) => n.val + 1 - i_.val)
    (inv := fun (cost_, i_) => cost_.length = i_.val)
  · rintro ⟨cost_, i_⟩ hc_
    simp only [slot.a_engine_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals try simp only [alloc.vec.Vec.length, *, List.length_append, List.length_singleton]
    all_goals scalar_tac
  · exact hc

-- @owner engA @status BLOCKED(A2) @changed (CONTRACT_ISSUES engA B1) @note the passes of one round (measure passes-k); `span = r.0 * need / r.1` and `(p1 - p0) * need / t` overflow a 32-bit usize: A2 (wrapping_mul + saturating grow). Post: t <= need, p0 <= p1 (for used += t, p1 - p0). Check the tuple projections against the extraction
-- [engA] loop callees: a_add_counts a_dp_pass a_sample_pass a_set_costs a_set_costs_huff a_walk
@[local step]
theorem a_engine_loop1_loop0_spec (input : Slice Std.U8) (ch) (n : Std.Usize) (mp mb cost lit lc dc lf df bl bd sl sd) (rot p0 need passes sampled pe k p1 t : Std.Usize)
    (hn : n.val = input.length) (hn26 : n.val < 67108864) (hp0 : p0.val < n.val) (hpe : p0.val ≤ pe.val ∧ pe.val ≤ n.val)
    (hpe' : pe.val = n.val ∨ p0.val + slot.A_MARGIN.val ≤ pe.val)
    (hneed : need.val ≤ 65536) (ht : t.val ≤ need.val) (hp1 : p0.val ≤ p1.val ∧ p1.val ≤ p0.val + 511 * t.val) :
    slot.a_engine_loop1_loop0 input ch n mp mb cost lit lc dc lf df bl bd sl sd rot p0 need passes sampled pe k p1 t ⦃ fun r =>
      r.2.2.2.2.2.2.2.2.2.2.val ≤ need.val ∧ p0.val ≤ r.2.2.2.2.2.2.2.2.2.1.val ∧
      r.2.2.2.2.2.2.2.2.2.1.val ≤ p0.val + 511 * r.2.2.2.2.2.2.2.2.2.2.val ⦄ := by
  have hbt := A_BLOCK_bounds
  have hseg := A_SEG_bounds
  rw [slot.a_engine_loop1_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, _, _, _, _, _, _, k_, _, _) => passes.val - k_.val)
    (inv := fun (_, _, _, _, _, _, _, _, _, (pe_ : Std.Usize), _, (p1_ : Std.Usize), (t_ : Std.Usize)) =>
      p0.val ≤ pe_.val ∧ pe_.val ≤ n.val ∧ (pe_.val = n.val ∨ p0.val + slot.A_MARGIN.val ≤ pe_.val) ∧
      t_.val ≤ need.val ∧ p0.val ≤ p1_.val ∧ p1_.val ≤ p0.val + 511 * t_.val)
  · rintro ⟨ch_, cost_, lit_, lc_, dc_, lf_, df_, sl_, sd_, pe_, k_, p1_, t_⟩ ⟨hpe0, hpe1, hpe2, ht_, hp10, hp11⟩
    simp only [slot.a_engine_loop1_loop0.body]
    step*
    -- one pass (sampled or full): the new window end `pe`, and the path end and tokens of a full pass
    apply WP.spec_bind (Pₘ := fun (x : alloc.vec.Vec Std.U32 × alloc.vec.Vec Std.U32 × Std.Array Std.U32 512#usize ×
        Std.Array Std.U32 32#usize × Std.Usize × Std.Usize × Std.Usize) =>
        p0.val ≤ x.2.2.2.2.1.val ∧ x.2.2.2.2.1.val ≤ n.val ∧
        (x.2.2.2.2.1.val = n.val ∨ p0.val + slot.A_MARGIN.val ≤ x.2.2.2.2.1.val) ∧
        x.2.2.2.2.2.2.val ≤ need.val ∧ p0.val ≤ x.2.2.2.2.2.1.val ∧ x.2.2.2.2.2.1.val ≤ p0.val + 511 * x.2.2.2.2.2.2.val)
    · split
      · step*
        · -- a sampled pass: the window end scales with the sampled bytes per token
          cases ‹Std.Usize × Std.Usize›
          step*
          apply WP.spec_bind (Pₘ := fun (z : alloc.vec.Vec Std.U32 × alloc.vec.Vec Std.U32 × Std.Array Std.U32 512#usize ×
              Std.Array Std.U32 32#usize × Std.Usize) => p0.val ≤ z.2.2.2.2.val ∧ z.2.2.2.2.val ≤ n.val ∧
              (z.2.2.2.2.val = n.val ∨ p0.val + slot.A_MARGIN.val ≤ z.2.2.2.2.val))
          · repeat' (split <;> step*)
            all_goals scalar_tac
          rintro ⟨v, v1, a, a1, i6⟩ hi6
          step*
          all_goals scalar_tac
        · -- a full pass: dynamic program, then the walk of the round's tokens
          apply WP.spec_bind (Pₘ := fun (lim : Std.Usize) => lim.val ≤ pe_.val)
          · split
            all_goals step*
            all_goals scalar_tac
          rintro lim hlim
          step*
          cases ‹Std.Usize × Std.Usize›
          step*
          apply WP.spec_bind (Pₘ := fun (z : Std.Array Std.U32 512#usize × Std.Array Std.U32 32#usize × Std.Usize) =>
              p0.val ≤ z.2.2.val ∧ z.2.2.val ≤ n.val ∧ (z.2.2.val = n.val ∨ p0.val + slot.A_MARGIN.val ≤ z.2.2.val))
          · repeat' (split <;> step*)
            all_goals scalar_tac
          rintro ⟨a, a1, i4⟩ hi4
          step*
          all_goals scalar_tac
        · -- a full pass: dynamic program, then the walk of the round's tokens
          apply WP.spec_bind (Pₘ := fun (lim : Std.Usize) => lim.val ≤ pe_.val)
          · split
            all_goals step*
            all_goals scalar_tac
          rintro lim hlim
          step*
          cases ‹Std.Usize × Std.Usize›
          step*
          apply WP.spec_bind (Pₘ := fun (z : Std.Array Std.U32 512#usize × Std.Array Std.U32 32#usize × Std.Usize) =>
              p0.val ≤ z.2.2.val ∧ z.2.2.val ≤ n.val ∧ (z.2.2.val = n.val ∨ p0.val + slot.A_MARGIN.val ≤ z.2.2.val))
          · repeat' (split <;> step*)
            all_goals scalar_tac
          rintro ⟨a, a1, i4⟩ hi4
          step*
          all_goals scalar_tac
      · step*
        · -- a full pass: dynamic program, then the walk of the round's tokens
          apply WP.spec_bind (Pₘ := fun (lim : Std.Usize) => lim.val ≤ pe_.val)
          · split
            all_goals step*
            all_goals scalar_tac
          rintro lim hlim
          step*
          cases ‹Std.Usize × Std.Usize›
          step*
          apply WP.spec_bind (Pₘ := fun (z : Std.Array Std.U32 512#usize × Std.Array Std.U32 32#usize × Std.Usize) =>
              p0.val ≤ z.2.2.val ∧ z.2.2.val ≤ n.val ∧ (z.2.2.val = n.val ∨ p0.val + slot.A_MARGIN.val ≤ z.2.2.val))
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

-- @owner engA @status DONE @note (statement verbatim; CONTRACT_ISSUES engA A8) measure n - p0 (p0 := p1 > p0 or n); NO Rust edit needed (A1 unnecessary): a walk token advances <= 511 bytes, so p1 - p0 <= 511 t, bpt <= 130816 and need * bpt, (p1 - p0) * 256 < 2^31
-- [engA] loop callees: a_add_counts a_engine_loop1_loop0
@[local step]
theorem a_engine_loop1_spec (input : Slice Std.U8) (ch first_passes fspass passes_k) (n : Std.Usize) (mp mb cost lit lc dc lf df bl bd sl sd zl zd) (rot spn p0 used bpt : Std.Usize)
    (hn : n.val = input.length) (hn26 : n.val < 67108864) (hused : used.val < slot.BLOCK_TOKENS.val) (hbpt : 256 ≤ bpt.val ∧ bpt.val ≤ 65536) :
    slot.a_engine_loop1 input ch first_passes fspass passes_k n mp mb cost lit lc dc lf df bl bd sl sd zl zd rot spn p0 used bpt ⦃ fun _ => True ⦄ := by
  have hbt := A_BLOCK_bounds
  rw [slot.a_engine_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, _, _, _, _, _, _, _, p0_, _, _) => n.val - p0_.val)
    (inv := fun (_, _, _, _, _, _, _, _, _, _, _, _, used_, bpt_) => used_.val < slot.BLOCK_TOKENS.val ∧
      256 ≤ bpt_.val ∧ bpt_.val ≤ 130816)
  · rintro ⟨ch_, cost_, lit_, lc_, dc_, lf_, df_, bl_, bd_, sl_, sd_, p0_, used_, bpt_⟩ ⟨hused_, hbpt0, hbpt1⟩
    simp only [slot.a_engine_loop1.body, engA_ite_ok]
    step*
    · -- the token estimate `need * bpt` fits in 32 bits
      have : need.val * bpt_.val ≤ 16384 * 130816 := Nat.mul_le_mul (by scalar_tac) hbpt1
      scalar_tac
    apply WP.spec_bind (Pₘ := fun (pe : Std.Usize) => p0_.val ≤ pe.val ∧ pe.val ≤ n.val ∧
      (pe.val = n.val ∨ p0_.val + slot.A_MARGIN.val ≤ pe.val))
    · split
      all_goals step*
      all_goals scalar_tac
    rintro pe hpe
    step*
    apply WP.spec_bind (Pₘ := fun (x : Std.Array Std.U32 512#usize × Std.Array Std.U32 32#usize × Std.Usize) =>
      x.2.2.val < slot.BLOCK_TOKENS.val)
    · split
      all_goals step*
      all_goals scalar_tac
    rintro ⟨bl1, bd1, used2⟩ hu2
    step*
    -- a new bytes-per-token estimate: at most 511 bytes per token, times 256
    all_goals try (
      have hdiv : bpt1.val ≤ 130816 := by
        rw [bpt1_post]; apply Nat.div_le_of_le_mul; scalar_tac
      by_cases hb : bpt1 < 256#usize
      all_goals simp only [hb, ite_true, ite_false])
    all_goals scalar_tac
  · -- the invariant allows up to 511 bytes per token (the snapshot never clamps `bpt` from above)
    exact ⟨hused, hbpt.1, by omega⟩

-- @owner engA @status DONE @export @note EXPORTED (called by plan_cfg). `3 <= skip` is needed by `cl - 3` in a_find_all (skip branch); A7 (`if cl >= skip && cl >= 3`) would drop it
-- [engA] fn callees: a_engine_loop0 a_engine_loop1 a_find_all a_first_model
@[local step]
theorem a_engine_spec (input : Slice Std.U8) (ch) (depth skip first_passes fspass passes_k spass : Std.Usize)
    (hn : input.length < 67108864) (h1 : depth.val ≤ 65536) (h2 : skip.val ≤ 65536) (h2' : 3 ≤ skip.val)
    (h3 : first_passes.val ≤ 65536) (h4 : fspass.val ≤ 65536) (h5 : passes_k.val ≤ 65536) (h6 : spass.val ≤ 65536) :
    slot.a_engine input ch depth skip first_passes fspass passes_k spass ⦃ fun _ => True ⦄ := by
  have hbt := A_BLOCK_bounds
  rw [slot.a_engine]
  step*
  all_goals rfl

/-! # sec_engB (owner: engB) -- engine B (structured): totality only.
Exported: `b_engine_spec` (frozen, statement verbatim). Result-typed constants need step specs (below).
Every lemma is proved except `B_NOHINT_spec`, BLOCKED by Rust edit R2 (CONTRACT_ISSUES engB-B1).
Statements that differ from CONTRACT.md section 8 are listed with their reasons in CONTRACT_ISSUES engB-1..7. -/

@[local step]
theorem B_FULL_spec : slot.B_FULL ⦃ fun x => x.val = 536870912 ⦄ := by
  unfold slot.B_FULL; step*

@[local step]
theorem B_KEEPMAX_spec : slot.B_KEEPMAX ⦃ fun _ => True ⦄ := by
  unfold slot.B_KEEPMAX
  have h := numBits_ge
  step*

-- @status BLOCKED(R2): `1 << 62` fails when usize has 32 bits (the model allows it), and it is evaluated on
-- every input with n >= 16, so no proof exists on the snapshot. Once the builder applies R2
-- (`B_NOHINT: usize = 0xFFFF_FFFF`), B_NOHINT is a plain constant: DELETE this lemma (nothing else changes;
-- checked on the extraction of snapshot + R2, CONTRACT_ISSUES engB-B1).
-- (sInt proofcheck: B_NOHINT_spec deleted, R2 makes B_NOHINT a plain constant)

/-! ## engB helpers (arithmetic facts `scalar_tac` does not find by itself) -/

/-- `index_mut` as a read followed by a pure `set`: after this rewrite `step*` substitutes the
    write-back function (for `let (_, back) ← v.index_mut_usize i` it otherwise loses its value). -/
theorem engB_vec_index_mut {α : Type} (v : alloc.vec.Vec α) (i : Std.Usize) :
    alloc.vec.Vec.index_mut_usize v i =
      (do let x ← alloc.vec.Vec.index_usize v i; ok (x, alloc.vec.Vec.set v i)) := by
  unfold alloc.vec.Vec.index_mut_usize
  cases alloc.vec.Vec.index_usize v i <;> rfl

theorem engB_u32_shr15 (x : Std.U32) : x.val >>> 15 < 131072 := by
  rw [Nat.shiftRight_eq_div_pow]
  have : x.val < 2 ^ 32 := by scalar_tac
  omega

/-! ## Bounded tables in the match finder (`b_descend`, `b_engine`)

The tree, the hash heads and the previous descent's nodes (`pn`) only ever hold positions `+ 1` of
earlier positions (or 0), so at position `i` all their entries are at most `i` (`LeAll`). The two
step rules below carry that bound through reads and writes of a `u32` array automatically; they are
enabled only for the lemmas that need them (`attribute [local step] .. in`). The write rule's value
bound is stated as `x < B + 1` so that `step*` fixes the ghost `B` from the `LeAll` hypothesis. -/

theorem engB_arr_index_le {n : Std.Usize} (a : Std.Array Std.U32 n) (j : Std.Usize) (B : Nat)
    (h : LeAll a.val B) (hj : j.val < a.length) :
    a.index_usize j ⦃ fun x => x = a.val[j.val] ∧ x.val ≤ B ⦄ := by
  have := Std.Array.index_usize_spec a j hj
  apply WP.spec_mono this
  intro x hx
  exact ⟨hx, hx ▸ LeAll_get h j.val (by simpa using hj)⟩

theorem engB_arr_update_le {n : Std.Usize} (a : Std.Array Std.U32 n) (j : Std.Usize) (x : Std.U32)
    (B : Nat) (h : LeAll a.val B) (hx : x.val < B + 1) (hj : j.val < a.length) :
    a.update j x ⦃ fun r => r = a.set j x ∧ LeAll r.val B ⦄ := by
  have := Std.Array.update_spec a j x hj
  apply WP.spec_mono this
  intro r hr
  exact ⟨hr, by rw [hr, Std.Array.set_val_eq]; exact LeAll_set h _ _ (by omega)⟩

/-- `index_mut` on an array whose read value is not needed (`let (_, back) ← ..`): keep the
    write-back (the library rule's two-part post is dropped when the value is anonymous). -/
theorem engB_arr_index_mut_spec {α : Type} {n : Std.Usize} (v : Std.Array α n) (i : Std.Usize)
    (hbound : i.val < v.length) :
    v.index_mut_usize i ⦃ x back => back = Std.Array.set v i ⦄ := by
  have := Std.Array.index_mut_usize_spec v i hbound
  apply WP.spec_mono this
  rintro ⟨x, back⟩ ⟨_, h⟩
  exact h

/- Registering a step rule a second time (`attribute [local step] .. in` for a second lemma) costs
   several seconds (its `mvcgen_spec` is generated again and rejected), so every user gets its own
   copy of the two rules. -/
theorem engB_arr_index_le_d {n : Std.Usize} (a : Std.Array Std.U32 n) (j : Std.Usize) (B : Nat)
    (h : LeAll a.val B) (hj : j.val < a.length) :
    a.index_usize j ⦃ fun x => x = a.val[j.val] ∧ x.val ≤ B ⦄ := engB_arr_index_le a j B h hj

theorem engB_arr_update_le_d {n : Std.Usize} (a : Std.Array Std.U32 n) (j : Std.Usize) (x : Std.U32)
    (B : Nat) (h : LeAll a.val B) (hx : x.val < B + 1) (hj : j.val < a.length) :
    a.update j x ⦃ fun r => r = a.set j x ∧ LeAll r.val B ⦄ := engB_arr_update_le a j x B h hx hj

theorem engB_arr_index_le_g {n : Std.Usize} (a : Std.Array Std.U32 n) (j : Std.Usize) (B : Nat)
    (h : LeAll a.val B) (hj : j.val < a.length) :
    a.index_usize j ⦃ fun x => x = a.val[j.val] ∧ x.val ≤ B ⦄ := engB_arr_index_le a j B h hj

theorem engB_arr_update_le_g {n : Std.Usize} (a : Std.Array Std.U32 n) (j : Std.Usize) (x : Std.U32)
    (B : Nat) (h : LeAll a.val B) (hx : x.val < B + 1) (hj : j.val < a.length) :
    a.update j x ⦃ fun r => r = a.set j x ∧ LeAll r.val B ⦄ := engB_arr_update_le a j x B h hx hj

theorem engB_arr_index_mut_spec_b {α : Type} {n : Std.Usize} (v : Std.Array α n) (i : Std.Usize)
    (hbound : i.val < v.length) :
    v.index_mut_usize i ⦃ x back => back = Std.Array.set v i ⦄ := engB_arr_index_mut_spec v i hbound

theorem engB_arr_index_mut_spec_c {α : Type} {n : Std.Usize} (v : Std.Array α n) (i : Std.Usize)
    (hbound : i.val < v.length) :
    v.index_mut_usize i ⦃ x back => back = Std.Array.set v i ⦄ := engB_arr_index_mut_spec v i hbound

theorem engB_arr_index_le_e {n : Std.Usize} (a : Std.Array Std.U32 n) (j : Std.Usize) (B : Nat)
    (h : LeAll a.val B) (hj : j.val < a.length) :
    a.index_usize j ⦃ fun x => x = a.val[j.val] ∧ x.val ≤ B ⦄ := engB_arr_index_le a j B h hj

theorem engB_LeAll_u32 (l : List Std.U32) : LeAll l 4294967295 := fun j hj => by scalar_tac

theorem engB_wsub_val (x y : Std.Usize) (h : y.val ≤ x.val) :
    (core.num.Usize.wrapping_sub x y).val = x.val - y.val := by
  rw [core.num.Usize.wrapping_sub_val_eq]
  have hx : x.val < UScalar.size .Usize := by
    have := x.hBounds; simp only [UScalar.size]; exact this
  rw [show x.val + (UScalar.size .Usize - y.val) = (x.val - y.val) + UScalar.size .Usize by omega,
    Nat.add_mod_right, Nat.mod_eq_of_lt (by omega)]

theorem engB_u32_shr2 (x : Std.U32) : x.val >>> 2 < 1073741824 := by
  rw [Nat.shiftRight_eq_div_pow]
  have : x.val < 2 ^ 32 := by scalar_tac
  omega

/-! ## Block counters (`b_tally_seg`, `b_tally_plan`)

`bf` holds `B_FSZ` counters per encoder block. A block is zeroed when it is opened and then only
incremented, once or twice per token, while the parse advances by at least one position per
increment of any one counter; so every counter of the open block is at most the number of positions
consumed so far (`< 2^26`) and `+= 1` cannot overflow. -/

/-- The `B_FSZ` counters of the block at `base` are at most `K`. -/
def engB_Blk (l : List Std.U32) (base K : Nat) : Prop :=
  ∀ z, z < slot.B_FSZ.val → ∀ x, l[base + z]? = some x → x.val ≤ K

/-- The first `n` counters of the block at `base` are zero. -/
def engB_Zero (l : List Std.U32) (base n : Nat) : Prop :=
  ∀ z, z < n → ∀ x, l[base + z]? = some x → x.val = 0

theorem engB_Blk_mono {l : List Std.U32} {base K K' : Nat} (h : engB_Blk l base K) (hK : K ≤ K') :
    engB_Blk l base K' := fun z hz x hx => le_trans (h z hz x hx) hK

theorem engB_Blk_of {l : List Std.U32} {base K base' K' : Nat} (h : engB_Blk l base K)
    (hh : base = base' ∧ K ≤ K') : engB_Blk l base' K' := by
  obtain ⟨rfl, hK⟩ := hh; exact engB_Blk_mono h hK

theorem engB_Blk_get {l : List Std.U32} {base K : Nat} (h : engB_Blk l base K) {idx : Nat}
    {x : Std.U32} (h1 : base ≤ idx) (h2 : idx < base + slot.B_FSZ.val) (hl : idx < l.length)
    (hx : x = l[idx]) : x.val ≤ K := by
  have hx' : l[base + (idx - base)]? = some x := by
    rw [show base + (idx - base) = idx by omega, hx]; exact List.getElem?_eq_getElem hl
  exact h (idx - base) (by omega) _ hx'

theorem engB_Blk_set {l : List Std.U32} {base K K' : Nat} (h : engB_Blk l base K) (idx : Nat)
    (v : Std.U32) (hv : v.val ≤ K') (hK : K ≤ K') : engB_Blk (l.set idx v) base K' := by
  intro z hz x hx
  rw [List.getElem?_set] at hx
  split at hx
  · split at hx
    · cases hx; exact hv
    · cases hx
  · exact le_trans (h z hz x hx) hK

theorem engB_Zero_zero (l : List Std.U32) (base : Nat) : engB_Zero l base 0 :=
  fun z hz => absurd hz (Nat.not_lt_zero z)

theorem engB_Zero_set {l : List Std.U32} {base n : Nat} (h : engB_Zero l base n) (idx : Nat)
    (hidx : idx = base + n) : engB_Zero (l.set idx 0#u32) base (n + 1) := by
  intro z hz x hx
  rw [List.getElem?_set] at hx
  split at hx
  · split at hx
    · cases hx; rfl
    · cases hx
  · exact h z (by omega) x hx

theorem engB_Zero_push {l : List Std.U32} {base n : Nat} (h : engB_Zero l base n)
    (hlen : l.length = base + n) : engB_Zero (l ++ [0#u32]) base (n + 1) := by
  intro z hz x hx
  by_cases hzn : z < n
  · rw [List.getElem?_append_left (by omega)] at hx
    exact h z hzn x hx
  · have : base + z = l.length := by omega
    rw [this, List.getElem?_concat_length] at hx
    cases hx; rfl

theorem engB_Zero_Blk {l : List Std.U32} {base n : Nat} (h : engB_Zero l base n)
    (hn : slot.B_FSZ.val ≤ n) : engB_Blk l base 0 :=
  fun z hz x hx => le_of_eq (h z (by omega) x hx)

-- @owner engB @status DONE @note B1 (rn.wrapping_add(1) + guarded push) would make it True with no precondition
-- [engB] fn callees: -
@[local step]
theorem b_put_spec (rs) (rn : Std.Usize) (v) (hrn : rn.val < 4294967295) (hrs : rn.val ≤ rs.length) :
    slot.b_put rs rn v ⦃ fun r => r.1.val = rn.val + 1 ∧ r.1.val ≤ r.2.length ⦄ := by
  rw [slot.b_put]
  split
  · step*
    obtain ⟨x1, x2⟩ := x
    simp only at x_post1 x_post2 ⊢
    subst x_post2
    step*
    all_goals simp_all [alloc.vec.Vec.set_val_eq]; scalar_tac
  · step*
    all_goals first
      | scalar_tac
      | (have : rs1.length = rs.length + 1 := by simp [rs1_post]
         scalar_tac)

-- @owner engB @status DONE @note measure j; inv j <= m
-- [engB] loop callees: set_in
@[local step]
theorem b_plan_seg_loop_spec (a m : Std.Usize) (cc : alloc.vec.Vec Std.U64) (plan) (j : Std.Usize)
    (ham : a.val + m.val ≤ Std.Usize.max) (hj : j.val ≤ m.val) (hm : m.val < cc.length) :
    slot.b_plan_seg_loop a m cc plan j ⦃ fun _ => True ⦄ := by
  rw [slot.b_plan_seg_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, j') => j'.val)
    (inv := fun (_, j') => j'.val ≤ m.val)
  · rintro ⟨plan', j'⟩ hj'
    simp only [slot.b_plan_seg_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals (try have := engB_u32_shr15 v); scalar_tac
  · exact hj

-- @owner engB @status DONE
-- [engB] fn callees: b_plan_seg_loop
@[local step]
theorem b_plan_seg_spec (a m : Std.Usize) (cc : alloc.vec.Vec Std.U64) (plan)
    (ham : a.val + m.val ≤ Std.Usize.max) (hm : m.val < cc.length) :
    slot.b_plan_seg a m cc plan ⦃ fun _ => True ⦄ := by
  rw [slot.b_plan_seg]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

-- @owner engB @status DONE @note v = min(d,32768)-1 in [4, 32767]: lz32_le_of_pow_le v 2, lz32_ge_of_lt_pow v 15
-- [engB] fn callees: -
@[local step]
theorem b_dist_slot_spec (d) : slot.b_dist_slot d ⦃ fun r => r.val ≤ 29 ⦄ := by
  rw [slot.b_dist_slot]
  step*
  repeat' (split <;> step*)
  all_goals
    try (have hx : v.val = i.val := by
          rw [v_post, UScalar.cast_val_mod_pow_of_inBounds_eq _ _ (by scalar_tac)])
    try (have h1 := lz32_le_of_pow_le v 2 (by scalar_tac))
    try (have h2 := lz32_ge_of_lt_pow v 15 (by scalar_tac))
    scalar_tac

-- @owner engB @status DONE @note v = l-3 in [8, 254]
-- [engB] fn callees: -
@[local step]
theorem b_len_code_spec (l) : slot.b_len_code l ⦃ fun r => r.1.val ≤ 28 ∧ r.2.val ≤ 5 ⦄ := by
  rw [slot.b_len_code]
  step*
  repeat' (split <;> step*)
  all_goals
    try (have hx : v.val = i.val := by
          rw [v_post, UScalar.cast_val_mod_pow_of_inBounds_eq _ _ (by scalar_tac)])
    try (have h1 := lz32_le_of_pow_le v 3 (by scalar_tac))
    try (have h2 := lz32_ge_of_lt_pow v 8 (by scalar_tac))
    scalar_tac

-- @owner engB @status DONE (statement corrected: CONTRACT_ISSUES engB-1) @note inv base + z <= bf.length (a push lands exactly at base + z)
-- [engB] loop callees: -
@[local step]
theorem b_tally_plan_loop0_loop0_spec (bf) (base : Std.Usize)
    (hz : base.val ≤ bf.length) (hb : base.val + slot.B_FSZ.val ≤ 4294967295) :
    slot.b_tally_plan_loop0_loop0 bf base 0#usize ⦃ fun r => base.val + slot.B_FSZ.val ≤ r.length ∧
      bf.length ≤ r.length ∧ engB_Blk r.val base.val 0 ⦄ := by
  rw [slot.b_tally_plan_loop0_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, z') => slot.B_FSZ.val - z'.val)
    (inv := fun (bf', z') => base.val + z'.val ≤ bf'.length ∧ bf.length ≤ bf'.length ∧
      engB_Zero bf'.val base.val z'.val)
  · rintro ⟨bf', z'⟩ ⟨h1, h2, h3⟩
    simp only [slot.b_tally_plan_loop0_loop0.body]
    split
    · step*
      split
      · step*
        obtain ⟨x1, x2⟩ := x
        simp only at x_post1 x_post2 ⊢
        subst x_post2
        step*
        refine ⟨by simp; scalar_tac, by simp; scalar_tac, ?_, by scalar_tac⟩
        simp only [alloc.vec.Vec.set_val_eq]
        rw [show z1.val = z'.val + 1 by scalar_tac]
        exact engB_Zero_set h3 i.val (by scalar_tac)
      · step*
        have hl : bf1.length = bf'.length + 1 := by simp [bf1_post]
        refine ⟨by scalar_tac, by scalar_tac, ?_, by scalar_tac⟩
        rw [bf1_post, show z1.val = z'.val + 1 by scalar_tac]
        exact engB_Zero_push h3 (by scalar_tac)
    · simp only [WP.spec_ok]
      exact ⟨by scalar_tac, h2, engB_Zero_Blk h3 (by scalar_tac)⟩
  · exact ⟨by simpa using hz, le_refl _, engB_Zero_zero _ _⟩

/-- One token of `b_tally_plan`: the plan entry at `pos` if it is a match that fits, else the literal
    at `pos`, counted into the open block at `f`. -/
theorem engB_tally_plan_tok (s : Slice Std.U8) (bf : alloc.vec.Vec Std.U32) (n pos f l v : Std.Usize)
    (K : Nat) (hn : n.val = s.length) (hpos : pos.val < n.val)
    (hf : f.val + slot.B_FSZ.val ≤ bf.length) (hblk : engB_Blk bf.val f.val K)
    (hK : K + 2 < 4294967295) :
    (if l ≥ 3#usize then do
        let i5 ← n - pos
        if l ≤ i5 then do
            let d ← v / 512#usize
            let (i6, _) ← slot.b_len_code l
            let i7 ← 257#usize + i6
            let i8 ← i7 % slot.B_FSZ
            let i9 ← f + i8
            let (i10, index_mut_back) ← bf.index_mut_usize i9
            let i11 ← i10 + 1#u32
            let i12 ← slot.b_dist_slot d
            let i13 ← 288#usize + i12
            let i14 ← i13 % slot.B_FSZ
            let i15 ← f + i14
            let (i16, index_mut_back1) ← (index_mut_back i11).index_mut_usize i15
            let i17 ← i16 + 1#u32
            let pos2 ← pos + l
            ok (index_mut_back1 i17, pos2)
          else do
            let i6 ← s.index_usize pos
            let i7 ← lift (UScalar.cast UScalarTy.Usize i6)
            let i8 ← f + i7
            let (i9, index_mut_back) ← bf.index_mut_usize i8
            let i10 ← i9 + 1#u32
            let pos2 ← pos + 1#usize
            ok (index_mut_back i10, pos2)
      else do
        let i6 ← s.index_usize pos
        let i7 ← lift (UScalar.cast UScalarTy.Usize i6)
        let i8 ← f + i7
        let (i9, index_mut_back) ← bf.index_mut_usize i8
        let i10 ← i9 + 1#u32
        let pos2 ← pos + 1#usize
        ok (index_mut_back i10, pos2)) ⦃ fun (x : alloc.vec.Vec Std.U32 × Std.Usize) =>
      x.1.length = bf.length ∧ pos.val < x.2.val ∧ x.2.val ≤ n.val ∧
        engB_Blk x.1.val f.val (K + (x.2.val - pos.val)) ⦄ := by
  split
  · step
    split
    · step*
      all_goals (try subst i10_post2)
      all_goals (try subst i16_post2)
      all_goals try
        (have hidx : f.val ≤ i9.val ∧ i9.val < f.val + slot.B_FSZ.val ∧ i9.val < bf.val.length := by
          scalar_tac
         have h10 := engB_Blk_get hblk hidx.1 hidx.2.1 hidx.2.2 i10_post1)
      all_goals try (have hb2 := engB_Blk_set hblk i9.val i11 (K' := K + 1) (by omega) (by omega))
      all_goals try
        (have hidx2 : f.val ≤ i15.val ∧ i15.val < f.val + slot.B_FSZ.val ∧
            i15.val < (bf.val.set i9.val i11).length := by
          rw [List.length_set]; scalar_tac
         have h16 := engB_Blk_get hb2 (x := i16) hidx2.1 hidx2.2.1 hidx2.2.2
          (by simp only [i16_post1, alloc.vec.Vec.set_val_eq]))
      all_goals try
        (have hb3 := engB_Blk_set hb2 i15.val i17 (K' := K + (pos2.val - pos.val))
          (by scalar_tac) (by scalar_tac))
      all_goals first
        | (refine ⟨by simp, by scalar_tac, by scalar_tac, ?_⟩
           simp only [alloc.vec.Vec.set_val_eq]; exact hb3)
        | scalar_tac
    · step*
      all_goals (try subst i9_post2)
      all_goals try
        (have hidx : f.val ≤ i8.val ∧ i8.val < f.val + slot.B_FSZ.val ∧ i8.val < bf.val.length := by
          scalar_tac
         have h9 := engB_Blk_get hblk hidx.1 hidx.2.1 hidx.2.2 i9_post1)
      all_goals try
        (have hb2 := engB_Blk_set hblk i8.val i10 (K' := K + (pos2.val - pos.val))
          (by scalar_tac) (by scalar_tac))
      all_goals first
        | (refine ⟨by simp, by scalar_tac, by scalar_tac, ?_⟩
           simp only [alloc.vec.Vec.set_val_eq]; exact hb2)
        | scalar_tac
  · step*
    all_goals (try subst i9_post2)
    all_goals try
      (have hidx : f.val ≤ i8.val ∧ i8.val < f.val + slot.B_FSZ.val ∧ i8.val < bf.val.length := by
        scalar_tac
       have h9 := engB_Blk_get hblk hidx.1 hidx.2.1 hidx.2.2 i9_post1)
    all_goals try
      (have hb2 := engB_Blk_set hblk i8.val i10 (K' := K + (pos2.val - pos.val))
        (by scalar_tac) (by scalar_tac))
    all_goals first
      | (refine ⟨by simp, by scalar_tac, by scalar_tac, ?_⟩
         simp only [alloc.vec.Vec.set_val_eq]; exact hb2)
      | scalar_tac

/-- The loop invariant of `b_tally_plan` (kept folded): `nb = ⌈t / BLOCK_TOKENS⌉` blocks exist, and
    the open block's counters are at most the `pos` positions consumed. -/
def engB_TPL (n : Nat) (bf bs : alloc.vec.Vec Std.U32) (nb pos t : Nat) : Prop :=
  (pos ≤ n ∧ t ≤ pos ∧ t ≤ nb * slot.BLOCK_TOKENS.val ∧ nb * slot.BLOCK_TOKENS.val < t + slot.BLOCK_TOKENS.val ∧
    nb * slot.B_FSZ.val ≤ bf.length ∧ nb ≤ bs.length) ∧
    (0 < nb → engB_Blk bf.val ((nb - 1) * slot.B_FSZ.val) pos)

theorem engB_TPL.mk {n : Nat} {bf bs : alloc.vec.Vec Std.U32} {nb pos t : Nat}
    (h1 : pos ≤ n ∧ t ≤ pos ∧ t ≤ nb * slot.BLOCK_TOKENS.val ∧
      nb * slot.BLOCK_TOKENS.val < t + slot.BLOCK_TOKENS.val ∧ nb * slot.B_FSZ.val ≤ bf.length ∧
      nb ≤ bs.length)
    (h2 : 0 < nb → engB_Blk bf.val ((nb - 1) * slot.B_FSZ.val) pos) : engB_TPL n bf bs nb pos t :=
  ⟨h1, h2⟩

-- @owner engB @status DONE (statement corrected: CONTRACT_ISSUES engB-1) @note bf[..] += 1 counters in a Vec block: B4 (wrapping_add). Measure n - pos; nb*B_FSZ index arithmetic needs the block-count invariant (a block per BLOCK_TOKENS tokens)
-- [engB] loop callees: b_dist_slot b_len_code b_tally_plan_loop0_loop0
@[local step]
theorem b_tally_plan_loop0_spec (s : Slice Std.U8) (plan) (bf bs : alloc.vec.Vec Std.U32) (n nb pos t : Std.Usize)
    (hn : n.val = s.length) (hn26 : n.val < 67108864)
    (hinv : engB_TPL n.val bf bs nb.val pos.val t.val) :
    slot.b_tally_plan_loop0 s plan bf bs n nb pos t ⦃ fun r =>
      r.2.2.val * slot.BLOCK_TOKENS.val ≤ n.val + slot.BLOCK_TOKENS.val ∧
      r.2.2.val * slot.B_FSZ.val ≤ r.1.length ∧
      (0 < r.2.2.val → engB_Blk r.1.val ((r.2.2.val - 1) * slot.B_FSZ.val) n.val) ⦄ := by
  rw [slot.b_tally_plan_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, pos', _) => n.val - pos'.val)
    (inv := fun (bf', bs', nb', pos', t') => engB_TPL n.val bf' bs' nb'.val pos'.val t'.val)
  · rintro ⟨bf', bs', nb', pos', t'⟩ ⟨⟨hp1, hp2, hp3, hp4, hp5, hp6⟩, hp7⟩
    simp only [slot.b_tally_plan_loop0.body]
    split
    · split
      · step*
        · -- a new block (t % BLOCK_TOKENS = 0)
          apply WP.spec_bind (Pₘ := fun (bs1 : alloc.vec.Vec Std.U32) => nb'.val < bs1.length)
          · split
            · step*
              all_goals first
                | scalar_tac
                | (simp only [alloc.vec.Vec.set_val_eq, List.length_set]; scalar_tac)
            · step*
              all_goals first
                | scalar_tac
                | (have : bs1.length = bs'.length + 1 := by simp [bs1_post]
                   scalar_tac)
          · intro bs1 hbs1
            step*
            apply WP.spec_bind (engB_tally_plan_tok s bf1 n pos' f l v 0 hn (by scalar_tac)
              (by scalar_tac) (by rw [show f.val = base.val by scalar_tac]; exact bf1_post3) (by norm_num))
            rintro ⟨bf2, pos1⟩ ⟨hb1, hb2, hb3, hb4⟩
            step*
            refine ⟨?_, by scalar_tac⟩
            apply engB_TPL.mk
            · scalar_tac
            · exact fun _ => engB_Blk_of hb4 (by scalar_tac)
        · -- the open block
          apply WP.spec_bind (engB_tally_plan_tok s bf' n pos' f l v pos'.val hn (by scalar_tac)
            (by scalar_tac) (engB_Blk_of (hp7 (by scalar_tac)) (by scalar_tac)) (by scalar_tac))
          rintro ⟨bf2, pos1⟩ ⟨hb1, hb2, hb3, hb4⟩
          step*
          refine ⟨?_, by scalar_tac⟩
          apply engB_TPL.mk
          · scalar_tac
          · exact fun _ => engB_Blk_of hb4 (by scalar_tac)
      · simp only [WP.spec_ok]
        exact ⟨by scalar_tac, hp5, fun h => engB_Blk_of (hp7 h) (by scalar_tac)⟩
    · simp only [WP.spec_ok]
      exact ⟨by scalar_tac, hp5, fun h => engB_Blk_of (hp7 h) (by scalar_tac)⟩
  · exact hinv

-- @owner engB @status DONE @note final bf[(nb-1)*B_FSZ + 256] += 1 is a B4 site
-- [engB] fn callees: b_tally_plan_loop0
@[local step]
theorem b_tally_plan_spec (s : Slice Std.U8) (plan bf bs) (hn26 : s.length < 67108864) :
    slot.b_tally_plan s plan bf bs ⦃ fun r => r.1.val ≤ 1048576 ⦄ := by
  rw [slot.b_tally_plan]
  step*
  · unfold engB_TPL; simp
  · have := engB_Blk_get (bf1_post3 (by scalar_tac)) (by scalar_tac) (by scalar_tac) (by scalar_tac)
      i3_post1
    scalar_tac

-- @owner engB @status DONE (statement corrected: CONTRACT_ISSUES engB-1)
-- [engB] loop callees: -
@[local step]
theorem b_tally_seg_loop0_loop0_spec (bf) (base : Std.Usize)
    (hz : base.val ≤ bf.length) (hb : base.val + slot.B_FSZ.val ≤ 4294967295) :
    slot.b_tally_seg_loop0_loop0 bf base 0#usize ⦃ fun r => base.val + slot.B_FSZ.val ≤ r.length ∧
      bf.length ≤ r.length ∧ engB_Blk r.val base.val 0 ⦄ := by
  rw [slot.b_tally_seg_loop0_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, z') => slot.B_FSZ.val - z'.val)
    (inv := fun (bf', z') => base.val + z'.val ≤ bf'.length ∧ bf.length ≤ bf'.length ∧
      engB_Zero bf'.val base.val z'.val)
  · rintro ⟨bf', z'⟩ ⟨h1, h2, h3⟩
    simp only [slot.b_tally_seg_loop0_loop0.body]
    split
    · step*
      split
      · step*
        obtain ⟨x1, x2⟩ := x
        simp only at x_post1 x_post2 ⊢
        subst x_post2
        step*
        refine ⟨by simp; scalar_tac, by simp; scalar_tac, ?_, by scalar_tac⟩
        simp only [alloc.vec.Vec.set_val_eq]
        rw [show z1.val = z'.val + 1 by scalar_tac]
        exact engB_Zero_set h3 i.val (by scalar_tac)
      · step*
        have hl : bf1.length = bf'.length + 1 := by simp [bf1_post]
        refine ⟨by scalar_tac, by scalar_tac, ?_, by scalar_tac⟩
        rw [bf1_post, show z1.val = z'.val + 1 by scalar_tac]
        exact engB_Zero_push h3 (by scalar_tac)
    · simp only [WP.spec_ok]
      exact ⟨by scalar_tac, h2, engB_Zero_Blk h3 (by scalar_tac)⟩
  · exact ⟨by simpa using hz, le_refl _, engB_Zero_zero _ _⟩

-- @owner engB @status DONE (statement corrected: CONTRACT_ISSUES engB-1)
-- [engB] loop callees: -
@[local step]
theorem b_tally_seg_loop0_loop1_spec (bf) (base : Std.Usize)
    (hz : base.val ≤ bf.length) (hb : base.val + slot.B_FSZ.val ≤ 4294967295) :
    slot.b_tally_seg_loop0_loop1 bf base 0#usize ⦃ fun r => base.val + slot.B_FSZ.val ≤ r.length ∧
      bf.length ≤ r.length ∧ engB_Blk r.val base.val 0 ⦄ := by
  rw [slot.b_tally_seg_loop0_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, z') => slot.B_FSZ.val - z'.val)
    (inv := fun (bf', z') => base.val + z'.val ≤ bf'.length ∧ bf.length ≤ bf'.length ∧
      engB_Zero bf'.val base.val z'.val)
  · rintro ⟨bf', z'⟩ ⟨h1, h2, h3⟩
    simp only [slot.b_tally_seg_loop0_loop1.body]
    split
    · step*
      split
      · step*
        obtain ⟨x1, x2⟩ := x
        simp only at x_post1 x_post2 ⊢
        subst x_post2
        step*
        refine ⟨by simp; scalar_tac, by simp; scalar_tac, ?_, by scalar_tac⟩
        simp only [alloc.vec.Vec.set_val_eq]
        rw [show z1.val = z'.val + 1 by scalar_tac]
        exact engB_Zero_set h3 i.val (by scalar_tac)
      · step*
        have hl : bf1.length = bf'.length + 1 := by simp [bf1_post]
        refine ⟨by scalar_tac, by scalar_tac, ?_, by scalar_tac⟩
        rw [bf1_post, show z1.val = z'.val + 1 by scalar_tac]
        exact engB_Zero_push h3 (by scalar_tac)
    · simp only [WP.spec_ok]
      exact ⟨by scalar_tac, h2, engB_Zero_Blk h3 (by scalar_tac)⟩
  · exact ⟨by simpa using hz, le_refl _, engB_Zero_zero _ _⟩

/-- One token of `b_tally_seg`: the match `(l, d)` read from `cc`, or the literal at `a + m - j`,
    counted into the open block at `f`; the counters grow by at most the positions consumed.
    (Stated in the form the loop body has after `simp only [body]`: `index_mut_usize`, no `let`.) -/
theorem engB_tally_seg_tok (s : Slice Std.U8) (a m : Std.Usize) (bf : alloc.vec.Vec Std.U32)
    (f j l : Std.Usize) (v : Std.U32) (K : Nat)
    (ham : a.val + m.val ≤ s.length) (hj : 0 < j.val) (hjm : j.val ≤ m.val)
    (hf : f.val + slot.B_FSZ.val ≤ bf.length) (hblk : engB_Blk bf.val f.val K)
    (hK : K + 2 < 4294967295) :
    (if l ≥ 3#usize then
      if l ≤ j then do
        let i5 ← lift (v &&& 32767#u32)
        let i6 ← lift (UScalar.cast UScalarTy.Usize i5)
        let d ← i6 + 1#usize
        let (i7, _) ← slot.b_len_code l
        let i8 ← 257#usize + i7
        let i9 ← i8 % slot.B_FSZ
        let i10 ← f + i9
        let (i11, index_mut_back) ← bf.index_mut_usize i10
        let i12 ← i11 + 1#u32
        let i13 ← slot.b_dist_slot d
        let i14 ← 288#usize + i13
        let i15 ← i14 % slot.B_FSZ
        let i16 ← f + i15
        let (i17, index_mut_back1) ← (index_mut_back i12).index_mut_usize i16
        let i18 ← i17 + 1#u32
        let j2 ← j - l
        ok (index_mut_back1 i18, j2)
      else do
        let i5 ← a + m
        let i6 ← i5 - j
        let i7 ← s.index_usize i6
        let i8 ← lift (UScalar.cast UScalarTy.Usize i7)
        let i9 ← i8 % slot.B_FSZ
        let i10 ← f + i9
        let (i11, index_mut_back) ← bf.index_mut_usize i10
        let i12 ← i11 + 1#u32
        let j2 ← j - 1#usize
        ok (index_mut_back i12, j2)
    else do
      let i5 ← a + m
      let i6 ← i5 - j
      let i7 ← s.index_usize i6
      let i8 ← lift (UScalar.cast UScalarTy.Usize i7)
      let i9 ← i8 % slot.B_FSZ
      let i10 ← f + i9
      let (i11, index_mut_back) ← bf.index_mut_usize i10
      let i12 ← i11 + 1#u32
      let j2 ← j - 1#usize
      ok (index_mut_back i12, j2)) ⦃ fun (x : alloc.vec.Vec Std.U32 × Std.Usize) =>
      x.1.length = bf.length ∧ x.2.val < j.val ∧ engB_Blk x.1.val f.val (K + (j.val - x.2.val)) ⦄ := by
  split
  · split
    · step*
      all_goals (try subst i11_post2)
      all_goals (try subst i17_post2)
      all_goals try
        (have hidx : f.val ≤ i10.val ∧ i10.val < f.val + slot.B_FSZ.val ∧ i10.val < bf.val.length := by
          scalar_tac
         have h11 := engB_Blk_get hblk hidx.1 hidx.2.1 hidx.2.2 i11_post1)
      all_goals try (have hb2 := engB_Blk_set hblk i10.val i12 (K' := K + 1) (by omega) (by omega))
      all_goals try
        (have hidx2 : f.val ≤ i16.val ∧ i16.val < f.val + slot.B_FSZ.val ∧
            i16.val < (bf.val.set i10.val i12).length := by
          rw [List.length_set]; scalar_tac
         have h17 := engB_Blk_get hb2 (x := i17) hidx2.1 hidx2.2.1 hidx2.2.2
          (by simp only [i17_post1, alloc.vec.Vec.set_val_eq]))
      all_goals try
        (have hb3 := engB_Blk_set hb2 i16.val i18 (K' := K + (j.val - j2.val))
          (by scalar_tac) (by scalar_tac))
      all_goals first
        | (refine ⟨by simp, by scalar_tac, ?_⟩
           simp only [alloc.vec.Vec.set_val_eq]; exact hb3)
        | scalar_tac
    · step*
      all_goals (try subst i11_post2)
      all_goals try
        (have hidx : f.val ≤ i10.val ∧ i10.val < f.val + slot.B_FSZ.val ∧ i10.val < bf.val.length := by
          scalar_tac
         have h11 := engB_Blk_get hblk hidx.1 hidx.2.1 hidx.2.2 i11_post1)
      all_goals try
        (have hb2 := engB_Blk_set hblk i10.val i12 (K' := K + (j.val - j2.val))
          (by scalar_tac) (by omega))
      all_goals first
        | (refine ⟨by simp, by scalar_tac, ?_⟩
           simp only [alloc.vec.Vec.set_val_eq]; exact hb2)
        | scalar_tac
  · step*
    all_goals (try subst i11_post2)
    all_goals try
      (have hidx : f.val ≤ i10.val ∧ i10.val < f.val + slot.B_FSZ.val ∧ i10.val < bf.val.length := by
        scalar_tac
       have h11 := engB_Blk_get hblk hidx.1 hidx.2.1 hidx.2.2 i11_post1)
    all_goals try
      (have hb2 := engB_Blk_set hblk i10.val i12 (K' := K + (j.val - j2.val))
        (by scalar_tac) (by omega))
    all_goals first
      | (refine ⟨by simp, by scalar_tac, ?_⟩
         simp only [alloc.vec.Vec.set_val_eq]; exact hb2)
      | scalar_tac

/-- The arithmetic invariant of `b_tally_seg`'s loop: `nb` blocks of counters exist in `bf` (and
    their offsets in `bs`), `inb` counts the tokens of the open block, `j ≤ m`. -/
def engB_TSInv (m : Nat) (bf bs : alloc.vec.Vec Std.U32) (nb inb j : Nat) : Prop :=
  j ≤ m ∧ nb * slot.B_FSZ.val ≤ bf.length ∧ nb ≤ bs.length ∧ (nb = 0 → inb = slot.BLOCK_TOKENS.val) ∧
    inb ≤ slot.BLOCK_TOKENS.val ∧ (0 < nb → (nb - 1) * slot.BLOCK_TOKENS.val + inb ≤ m - j)

/-- The whole loop invariant (kept folded so that `step*` does not reassociate it). -/
def engB_TSL (m L : Nat) (bf bs : alloc.vec.Vec Std.U32) (nb inb j : Nat) : Prop :=
  (L ≤ bf.length ∧ engB_TSInv m bf bs nb inb j) ∧
    (0 < nb → engB_Blk bf.val ((nb - 1) * slot.B_FSZ.val) (m - j))

theorem engB_TSL.mk {m L : Nat} {bf bs : alloc.vec.Vec Std.U32} {nb inb j : Nat}
    (h1 : L ≤ bf.length ∧ j ≤ m ∧ nb * slot.B_FSZ.val ≤ bf.length ∧ nb ≤ bs.length ∧
      (nb = 0 → inb = slot.BLOCK_TOKENS.val) ∧ inb ≤ slot.BLOCK_TOKENS.val ∧
      (0 < nb → (nb - 1) * slot.BLOCK_TOKENS.val + inb ≤ m - j))
    (h2 : 0 < nb → engB_Blk bf.val ((nb - 1) * slot.B_FSZ.val) (m - j)) :
    engB_TSL m L bf bs nb inb j :=
  ⟨⟨h1.1, h1.2⟩, h2⟩

-- @owner engB @status DONE (statement corrected: CONTRACT_ISSUES engB-1) @note measure j; body has 6 bind-ifs and a 348-line extraction: split with WP.spec_bind
-- [engB] loop callees: b_dist_slot b_len_code b_tally_seg_loop0_loop0 b_tally_seg_loop0_loop1
@[local step]
theorem b_tally_seg_loop0_spec (s : Slice Std.U8) (a m : Std.Usize) (cc : alloc.vec.Vec Std.U64) (whole) (bf bs : alloc.vec.Vec Std.U32) (nb inb j : Std.Usize)
    (ham : a.val + m.val ≤ s.length) (hm : m.val < cc.length) (hm26 : m.val < 67108864)
    (hinv : engB_TSInv m.val bf bs nb.val inb.val j.val)
    (hblk : 0 < nb.val → engB_Blk bf.val ((nb.val - 1) * slot.B_FSZ.val) (m.val - j.val)) :
    slot.b_tally_seg_loop0 s a m cc whole bf bs nb inb j ⦃ fun r =>
      r.2.2.val * slot.BLOCK_TOKENS.val ≤ m.val + slot.BLOCK_TOKENS.val ∧ bf.length ≤ r.1.length ∧
      r.2.2.val * slot.B_FSZ.val ≤ r.1.length ∧
      (0 < r.2.2.val → engB_Blk r.1.val ((r.2.2.val - 1) * slot.B_FSZ.val) m.val) ⦄ := by
  rw [slot.b_tally_seg_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, j') => j'.val)
    (inv := fun (bf', bs', nb', inb', j') => engB_TSL m.val bf.length bf' bs' nb'.val inb'.val j'.val)
  · rintro ⟨bf', bs', nb', inb', j'⟩ ⟨⟨hbf', hj', hI1, hI2, hI3, hI4, hI5⟩, hI6⟩
    simp only [slot.b_tally_seg_loop0.body]
    split
    · split
      · split
        · -- a new block (whole = 1)
          step*
          apply WP.spec_bind (Pₘ := fun (bs1 : alloc.vec.Vec Std.U32) => nb'.val < bs1.length)
          · split
            · step*
              all_goals first
                | scalar_tac
                | (simp only [alloc.vec.Vec.set_val_eq, List.length_set]; scalar_tac)
            · step*
              all_goals first
                | scalar_tac
                | (have : bs1.length = bs'.length + 1 := by simp [bs1_post]
                   scalar_tac)
          · intro bs1 hbs1
            step*
            apply WP.spec_bind (engB_tally_seg_tok s a m bf1 f j' l v 0 ham (by scalar_tac) hj'
              (by scalar_tac) (by rw [show f.val = base.val by scalar_tac]; exact bf1_post3) (by norm_num))
            rintro ⟨bf2, j1⟩ ⟨hb1, hb2, hb3⟩
            step*
            repeat' (split <;> step*)
            all_goals
              refine ⟨?_, by scalar_tac⟩
              apply engB_TSL.mk
              · scalar_tac
              · exact fun _ => engB_Blk_of hb3 (by scalar_tac)
        · split
          · -- the first block (nb = 0)
            step*
            apply WP.spec_bind (Pₘ := fun (bs1 : alloc.vec.Vec Std.U32) => nb'.val < bs1.length)
            · split
              · step*
                all_goals first
                  | scalar_tac
                  | (simp only [alloc.vec.Vec.set_val_eq, List.length_set]; scalar_tac)
              · step*
                all_goals first
                  | scalar_tac
                  | (have : bs1.length = bs'.length + 1 := by simp [bs1_post]
                     scalar_tac)
            · intro bs1 hbs1
              step*
              apply WP.spec_bind (engB_tally_seg_tok s a m bf1 f j' l v 0 ham (by scalar_tac) hj'
                (by scalar_tac) (by rw [show f.val = base.val by scalar_tac]; exact bf1_post3) (by norm_num))
              rintro ⟨bf2, j1⟩ ⟨hb1, hb2, hb3⟩
              step*
              repeat' (split <;> step*)
              all_goals
                refine ⟨?_, by scalar_tac⟩
                apply engB_TSL.mk
                · scalar_tac
                · exact fun _ => engB_Blk_of hb3 (by scalar_tac)
          · -- the open block, full (inb = BT, whole = 0)
            step*
            apply WP.spec_bind (engB_tally_seg_tok s a m bf' f j' l v (m.val - j'.val) ham
              (by scalar_tac) hj' (by scalar_tac)
              (engB_Blk_of (hI6 (by scalar_tac)) (by scalar_tac)) (by scalar_tac))
            rintro ⟨bf2, j1⟩ ⟨hb1, hb2, hb3⟩
            step*
            repeat' (split <;> step*)
            all_goals
              refine ⟨?_, by scalar_tac⟩
              apply engB_TSL.mk
              · scalar_tac
              · exact fun _ => engB_Blk_of hb3 (by scalar_tac)
      · -- the open block (inb < BT)
        step*
        apply WP.spec_bind (engB_tally_seg_tok s a m bf' f j' l v (m.val - j'.val) ham
          (by scalar_tac) hj' (by scalar_tac)
          (engB_Blk_of (hI6 (by scalar_tac)) (by scalar_tac)) (by scalar_tac))
        rintro ⟨bf2, j1⟩ ⟨hb1, hb2, hb3⟩
        step*
        repeat' (split <;> step*)
        all_goals
          refine ⟨?_, by scalar_tac⟩
          apply engB_TSL.mk
          · scalar_tac
          · exact fun _ => engB_Blk_of hb3 (by scalar_tac)
    · simp only [WP.spec_ok]
      exact ⟨by scalar_tac, hbf', by scalar_tac, fun h => engB_Blk_of (hI6 h) (by scalar_tac)⟩
  · exact ⟨⟨le_refl _, hinv⟩, hblk⟩

-- @owner engB @status DONE
-- [engB] fn callees: b_tally_seg_loop0
@[local step]
theorem b_tally_seg_spec (s : Slice Std.U8) (a m : Std.Usize) (cc : alloc.vec.Vec Std.U64) (whole bf bs)
    (ham : a.val + m.val ≤ s.length) (hm : m.val < cc.length) (hm26 : m.val < 67108864) :
    slot.b_tally_seg s a m cc whole bf bs ⦃ fun r => r.1.val ≤ 1048576 ∧ bf.length ≤ r.2.1.length ⦄ := by
  rw [slot.b_tally_seg]
  step*
  · unfold engB_TSInv; simp
  · have := engB_Blk_get (bf1_post4 (by scalar_tac)) (by scalar_tac) (by scalar_tac) (by scalar_tac)
      i3_post1
    scalar_tac
  · subst i3_post2; scalar_tac

-- @owner engB @status DONE @note e = 31 - lz <= 31, e*256 + u16 table value
-- [engB] fn callees: -
@[local step]
theorem b_log2_fix_spec (x) : slot.b_log2_fix x ⦃ fun r => r.val < 131072 ⦄ := by
  rw [slot.b_log2_fix]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

-- @owner engB @status DONE
-- [engB] fn callees: b_log2_fix
@[local step]
theorem b_sym_cost_spec (f total) : slot.b_sym_cost f total ⦃ fun r => r.val < 131072 ⦄ := by
  rw [slot.b_sym_cost]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

-- @owner engB @status DONE
-- [engB] loop callees: -
@[local step]
theorem b_build_table_loop0_spec (freq tl k) :
    slot.b_build_table_loop0 freq tl k ⦃ fun _ => True ⦄ := by
  rw [slot.b_build_table_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (tl_, k_) => 286 - k_.val)
    (inv := fun _ => True)
  · rintro ⟨tl_, k_⟩ _
    simp only [slot.b_build_table_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial

-- @owner engB @status DONE
-- [engB] loop callees: -
@[local step]
theorem b_build_table_loop1_spec (freq k td) :
    slot.b_build_table_loop1 freq k td ⦃ fun _ => True ⦄ := by
  rw [slot.b_build_table_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (k_, td_) => 30 - k_.val)
    (inv := fun _ => True)
  · rintro ⟨k_, td_⟩ _
    simp only [slot.b_build_table_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial

-- @owner engB @status DONE
-- [engB] loop callees: b_sym_cost
@[local step]
theorem b_build_table_loop2_spec (freq tb tl k) :
    slot.b_build_table_loop2 freq tb tl k ⦃ fun _ => True ⦄ := by
  rw [slot.b_build_table_loop2]
  apply Std.loop.spec_decr_nat
    (measure := fun (tb_, k_) => 256 - k_.val)
    (inv := fun _ => True)
  · rintro ⟨tb_, k_⟩ _
    simp only [slot.b_build_table_loop2.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial

-- @owner engB @status DONE
-- [engB] loop callees: b_len_code b_sym_cost
@[local step]
theorem b_build_table_loop3_spec (freq tb tl l) :
    slot.b_build_table_loop3 freq tb tl l ⦃ fun _ => True ⦄ := by
  rw [slot.b_build_table_loop3]
  apply Std.loop.spec_decr_nat
    (measure := fun (tb_, l_) => 258 + 1 - l_.val)
    (inv := fun _ => True)
  · rintro ⟨tb_, l_⟩ _
    simp only [slot.b_build_table_loop3.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial

-- @owner engB @status DONE
-- [engB] loop callees: b_sym_cost
@[local step]
theorem b_build_table_loop4_spec (freq tb k td) :
    slot.b_build_table_loop4 freq tb k td ⦃ fun _ => True ⦄ := by
  rw [slot.b_build_table_loop4]
  apply Std.loop.spec_decr_nat
    (measure := fun (tb_, k_) => 30 - k_.val)
    (inv := fun _ => True)
  · rintro ⟨tb_, k_⟩ _
    simp only [slot.b_build_table_loop4.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial

-- @owner engB @status DONE
-- [engB] fn callees: b_build_table_loop0 b_build_table_loop1 b_build_table_loop2 b_build_table_loop3 b_build_table_loop4
@[local step]
theorem b_build_table_spec (freq tb) :
    slot.b_build_table freq tb ⦃ fun _ => True ⦄ := by
  rw [slot.b_build_table]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

-- @owner engB @status DONE @note z < B_FSZ indexes a [u32; 320]: fact B_FSZ_val (slot.B_FSZ.val = 320, the array size is baked into the type)
-- [engB] loop callees: -
@[local step]
theorem b_block_table_loop_spec (bf) (b : Std.Usize) (fq z)
    (hb : b.val * slot.B_FSZ.val + slot.B_FSZ.val ≤ 4294967295) :
    slot.b_block_table_loop bf b fq z ⦃ fun _ => True ⦄ := by
  rw [slot.b_block_table_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (fq_, z_) => slot.B_FSZ.val - z_.val)
    (inv := fun _ => True)
  · rintro ⟨fq_, z_⟩ _
    simp only [slot.b_block_table_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial

-- @owner engB @status DONE
-- [engB] fn callees: b_block_table_loop b_build_table
@[local step]
theorem b_block_table_spec (bf) (b : Std.Usize) (tb) (hb : b.val * slot.B_FSZ.val + slot.B_FSZ.val ≤ 4294967295) :
    slot.b_block_table bf b tb ⦃ fun _ => True ⦄ := by
  rw [slot.b_block_table]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

-- @owner engB @status DONE (hand proof) @note measure ml + 1 - l
-- [engB] loop callees: -
/-- Innermost: the lengths `l..=min(ml, j)` of one record (recipe). -/
@[local step]
theorem b_dp_seg_loop0_loop0_loop0_spec (cc : alloc.vec.Vec Std.U64) (tb) (j : Std.Usize) (best choice v)
    (ml : Std.Usize) (dc l) (hj : j.val < cc.length) (hml : ml.val ≤ 511) :
    slot.b_dp_seg_loop0_loop0_loop0 cc tb j best choice v ml dc l ⦃ fun _ => True ⦄ := by
  rw [slot.b_dp_seg_loop0_loop0_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, l') => ml.val + 1 - l'.val)
    (inv := fun _ => True)
  · rintro ⟨best', choice', l'⟩ _
    simp only [slot.b_dp_seg_loop0_loop0_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial

-- @owner engB @status DONE (hand proof)
-- [engB] loop callees: -
/-- The same loop, a second copy Aeneas made for the other branch of `if v & B_FULL != 0`. -/
@[local step]
theorem b_dp_seg_loop0_loop0_loop1_spec (cc : alloc.vec.Vec Std.U64) (tb) (j : Std.Usize) (best choice v)
    (ml : Std.Usize) (dc l) (hj : j.val < cc.length) (hml : ml.val ≤ 511) :
    slot.b_dp_seg_loop0_loop0_loop1 cc tb j best choice v ml dc l ⦃ fun _ => True ⦄ := by
  rw [slot.b_dp_seg_loop0_loop0_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, l') => ml.val + 1 - l'.val)
    (inv := fun _ => True)
  · rintro ⟨best', choice', l'⟩ _
    simp only [slot.b_dp_seg_loop0_loop0_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial

-- @owner engB @status DONE (hand proof) @note measure e - q; inv lo <= 512 (lo = ml + 1 with ml <= 511)
-- [engB] loop callees: b_dp_seg_loop0_loop0_loop0 b_dp_seg_loop0_loop0_loop1
/-- Middle: the records `rs[q..e]` of one position. The inner loop's preconditions come from the
    parameters (`j < cc.length`) and from the record (`ml = (v >> 20) & 511`, bounded by the
    `x &&& y ≤ y` fact `scalar_tac` knows); the only state fact is `lo ≤ 512` (`lo + cuts`). -/
@[local step]
theorem b_dp_seg_loop0_loop0_spec (rs : alloc.vec.Vec Std.U32) (cc : alloc.vec.Vec Std.U64) (cuts : Std.Usize) (tb)
    (j e : Std.Usize) (best choice) (q lo : Std.Usize)
    (hj : j.val < cc.length) (he : e.val ≤ rs.length) (hcuts : cuts.val ≤ 65536) (hlo : lo.val ≤ 512) :
    slot.b_dp_seg_loop0_loop0 rs cc cuts tb j e best choice q lo ⦃ fun _ => True ⦄ := by
  rw [slot.b_dp_seg_loop0_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, q', _) => e.val - q'.val)
    (inv := fun (_, _, _, lo') => lo'.val ≤ 512)
  · rintro ⟨best', choice', q', lo'⟩ hlo'
    simp only [slot.b_dp_seg_loop0_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact hlo

-- @owner engB @status DONE @note measure m + 1 - j; inv cc.length kept, p <= rs.length, b <= b0, 1 <= j
-- [engB] loop callees: b_block_table b_dp_seg_loop0_loop0
@[local step]
theorem b_dp_seg_loop0_spec (s : Slice Std.U8) (a m : Std.Usize) (rs bf bs) (cc : alloc.vec.Vec Std.U64) (cuts : Std.Usize) (tb) (b bfirst p j : Std.Usize)
    (ham : a.val + m.val ≤ s.length) (hm : m.val < cc.length) (hp : p.val ≤ rs.length) (hj : 1 ≤ j.val)
    (hb : b.val ≤ 1048576) (hcuts : cuts.val ≤ 65536) :
    slot.b_dp_seg_loop0 s a m rs bf bs cc cuts tb b bfirst p j ⦃ fun r => r.length = cc.length ⦄ := by
  rw [slot.b_dp_seg_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, _, j') => m.val + 1 - j'.val)
    (inv := fun (cc', _, b', _, p', j') => cc'.length = cc.length ∧ p'.val ≤ rs.length ∧
      1 ≤ j'.val ∧ b'.val ≤ 1048576)
  · rintro ⟨cc', tb', b', bfirst', p', j'⟩ ⟨h1, h2, h3, h4⟩
    simp only [slot.b_dp_seg_loop0.body, alloc.vec.Vec.index_mut_slice_index, engB_vec_index_mut]
    split
    · split
      · step*
        apply WP.spec_bind (Pₘ := fun (x : Std.Array Std.U32 1024#usize × Std.Usize × Std.Usize) =>
          x.2.1.val ≤ b'.val)
        · split
          · split
            · step*
              repeat' (split <;> step*)
              all_goals scalar_tac
            · simp
          · simp
        · rintro ⟨tb1, b1, bfirst1⟩ hb1
          step*
          apply WP.spec_bind (Pₘ := fun (q : Std.Usize) => q.val < p'.val)
          · split
            · step*
              all_goals scalar_tac
            · simp; scalar_tac
          · intro q hq
            step*
            all_goals scalar_tac
      · simp; scalar_tac
    · simp; scalar_tac
  · exact ⟨rfl, hp, hj, hb⟩

-- @owner engB @status DONE @note R5 (`ml.saturating_sub(cuts) > lo` instead of `ml > lo + cuts`) would drop hcuts
-- [engB] fn callees: b_block_table b_dp_seg_loop0
@[local step]
theorem b_dp_seg_spec (s : Slice Std.U8) (a m : Std.Usize) (rs : alloc.vec.Vec Std.U32) (rn : Std.Usize) (bf bs) (nb : Std.Usize)
    (cc : alloc.vec.Vec Std.U64) (cuts : Std.Usize)
    (ham : a.val + m.val ≤ s.length) (hm : m.val < cc.length) (hrn : rn.val ≤ rs.length)
    (hnb : nb.val ≤ 1048576) (hcuts : cuts.val ≤ 65536) :
    slot.b_dp_seg s a m rs rn bf bs nb cc cuts ⦃ fun r => r.length = cc.length ⦄ := by
  rw [slot.b_dp_seg]
  simp only [alloc.vec.Vec.index_mut_slice_index, engB_vec_index_mut]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

-- @owner engB @status DONE @note inv k <= f.length; the push branch has f.length = k. A goal `let (_, back) := x` with x a pair: `obtain ⟨x1, x2⟩ := x`
-- [engB] loop callees: -
@[local step]
theorem b_static_freq_loop_spec (f) (k : Std.Usize) (hk : k.val ≤ f.length) :
    slot.b_static_freq_loop f k ⦃ fun r => slot.B_FSZ.val ≤ r.length ⦄ := by
  rw [slot.b_static_freq_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, k') => slot.B_FSZ.val - k'.val)
    (inv := fun (f', k') => k'.val ≤ f'.length)
  · rintro ⟨f', k'⟩ hk'
    simp only [slot.b_static_freq_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals try (obtain ⟨x1, x2⟩ := x; simp only at x_post1 x_post2 ⊢; subst x_post2; step*)
    all_goals first
      | scalar_tac
      | (have : f1.length = f'.length + 1 := by simp [f1_post]
         scalar_tac)
      | (simp [alloc.vec.Vec.set_val_eq]; scalar_tac)
  · exact hk

-- @owner engB @status DONE
-- [engB] fn callees: b_static_freq_loop
@[local step]
theorem b_static_freq_spec (f) : slot.b_static_freq f ⦃ fun r => slot.B_FSZ.val ≤ r.length ⦄ := by
  rw [slot.b_static_freq]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

-- @owner engB @status DONE (statement corrected: CONTRACT_ISSUES engB-2)
-- [engB] loop callees: -
@[local step]
theorem b_extra_bits_loop0_spec (freq) (c : Std.U64) (k : Std.Usize) (hk : 8 ≤ k.val) (hk28 : k.val ≤ 28)
    (hc : c.val ≤ (k.val - 8) * 2 ^ 35) :
    slot.b_extra_bits_loop0 freq c k ⦃ fun r => r.val ≤ 20 * 2 ^ 35 ⦄ := by
  rw [slot.b_extra_bits_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, k') => 28 - k'.val)
    (inv := fun (c', k') => 8 ≤ k'.val ∧ k'.val ≤ 28 ∧ c'.val ≤ (k'.val - 8) * 2 ^ 35)
  · rintro ⟨c', k'⟩ ⟨h1, h2, h3⟩
    simp only [slot.b_extra_bits_loop0.body]
    step*
    all_goals
      try (have := Nat.mul_le_mul (show i3.val ≤ 4294967295 by scalar_tac) (show i6.val ≤ 5 by scalar_tac))
      scalar_tac
  · exact ⟨hk, hk28, hc⟩

-- @owner engB @status DONE (statement corrected: CONTRACT_ISSUES engB-2)
-- [engB] loop callees: -
@[local step]
theorem b_extra_bits_loop1_spec (freq) (c : Std.U64) (k : Std.Usize) (hk : 4 ≤ k.val) (hk30 : k.val ≤ 30)
    (hc : c.val ≤ 20 * 2 ^ 35 + (k.val - 4) * 2 ^ 36) :
    slot.b_extra_bits_loop1 freq c k ⦃ fun r => r.val ≤ 20 * 2 ^ 35 + 26 * 2 ^ 36 ⦄ := by
  rw [slot.b_extra_bits_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, k') => 30 - k'.val)
    (inv := fun (c', k') => 4 ≤ k'.val ∧ k'.val ≤ 30 ∧ c'.val ≤ 20 * 2 ^ 35 + (k'.val - 4) * 2 ^ 36)
  · rintro ⟨c', k'⟩ ⟨h1, h2, h3⟩
    simp only [slot.b_extra_bits_loop1.body]
    step*
    all_goals
      try (have := Nat.mul_le_mul (show i2.val ≤ 4294967295 by scalar_tac) (show i5.val ≤ 14 by scalar_tac))
      scalar_tac
  · exact ⟨hk, hk30, hc⟩

-- @owner engB @status DONE
-- [engB] fn callees: b_extra_bits_loop0 b_extra_bits_loop1
@[local step]
theorem b_extra_bits_spec (freq) :
    slot.b_extra_bits freq ⦃ fun _ => True ⦄ := by
  rw [slot.b_extra_bits]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

-- @owner engB @status DONE
-- [engB] loop callees: -
@[local step]
theorem b_self_cost_loop0_spec (freq tl k) :
    slot.b_self_cost_loop0 freq tl k ⦃ fun _ => True ⦄ := by
  rw [slot.b_self_cost_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (tl_, k_) => 286 - k_.val)
    (inv := fun _ => True)
  · rintro ⟨tl_, k_⟩ _
    simp only [slot.b_self_cost_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial

-- @owner engB @status DONE
-- [engB] loop callees: -
@[local step]
theorem b_self_cost_loop1_spec (freq k td) :
    slot.b_self_cost_loop1 freq k td ⦃ fun _ => True ⦄ := by
  rw [slot.b_self_cost_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (k_, td_) => 30 - k_.val)
    (inv := fun _ => True)
  · rintro ⟨k_, td_⟩ _
    simp only [slot.b_self_cost_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial

-- @owner engB @status DONE (statement corrected: CONTRACT_ISSUES engB-2)
-- [engB] loop callees: b_log2_fix
@[local step]
theorem b_self_cost_loop2_spec (freq) (k : Std.Usize) (lt c : Std.U64) (hlt : lt.val < 131072) (hk : k.val ≤ 286)
    (hc : c.val ≤ k.val * 2 ^ 49) :
    slot.b_self_cost_loop2 freq k lt c ⦃ fun r => r.val ≤ 286 * 2 ^ 49 ⦄ := by
  rw [slot.b_self_cost_loop2]
  apply Std.loop.spec_decr_nat
    (measure := fun (k', _) => 286 - k'.val)
    (inv := fun (k', c') => k'.val ≤ 286 ∧ c'.val ≤ k'.val * 2 ^ 49)
  · rintro ⟨k', c'⟩ ⟨h1, h2⟩
    simp only [slot.b_self_cost_loop2.body]
    split
    · step*
      apply WP.spec_bind (Pₘ := fun (c1 : Std.U64) => c1.val ≤ c'.val + 2 ^ 49)
      · split
        · split
          · step*
            all_goals
              have := Nat.mul_le_mul (show i1.val ≤ 4294967295 by scalar_tac)
                (show i2.val ≤ 131071 by scalar_tac)
              scalar_tac
          · simp
        · simp
      · intro c1 hc1
        step*
        scalar_tac
    · simp; scalar_tac
  · exact ⟨hk, hc⟩

-- @owner engB @status DONE (statement corrected: CONTRACT_ISSUES engB-2)
-- [engB] loop callees: b_log2_fix
@[local step]
theorem b_self_cost_loop3_spec (freq) (k : Std.Usize) (ld c : Std.U64) (hld : ld.val < 131072) (hk : k.val ≤ 30)
    (hc : c.val ≤ 286 * 2 ^ 49 + k.val * 2 ^ 49) :
    slot.b_self_cost_loop3 freq k ld c ⦃ fun r => r.val ≤ 316 * 2 ^ 49 ⦄ := by
  rw [slot.b_self_cost_loop3]
  apply Std.loop.spec_decr_nat
    (measure := fun (k', _) => 30 - k'.val)
    (inv := fun (k', c') => k'.val ≤ 30 ∧ c'.val ≤ 286 * 2 ^ 49 + k'.val * 2 ^ 49)
  · rintro ⟨k', c'⟩ ⟨h1, h2⟩
    simp only [slot.b_self_cost_loop3.body]
    split
    · step*
      apply WP.spec_bind (Pₘ := fun (c1 : Std.U64) => c1.val ≤ c'.val + 2 ^ 49)
      · split
        · split
          · step*
            all_goals
              have := Nat.mul_le_mul (show i2.val ≤ 4294967295 by scalar_tac)
                (show i3.val ≤ 131071 by scalar_tac)
              scalar_tac
          · simp
        · simp
      · intro c1 hc1
        step*
        scalar_tac
    · simp; scalar_tac
  · exact ⟨hk, hc⟩

-- @owner engB @status DONE (statement corrected: CONTRACT_ISSUES engB-3)
-- [engB] fn callees: b_log2_fix b_self_cost_loop0 b_self_cost_loop1 b_self_cost_loop2 b_self_cost_loop3
@[local step]
theorem b_self_cost_spec (freq) : slot.b_self_cost freq ⦃ fun r => r.val ≤ 316 * 2 ^ 45 ⦄ := by
  rw [slot.b_self_cost]
  step*
  repeat' (split <;> step*)
  all_goals (rw [r_post1, Nat.shiftRight_eq_div_pow]; scalar_tac)

-- @owner engB @status DONE
-- [engB] fn callees: b_dist_slot
@[local step]
theorem b_rec_spec (l) (d : Std.Usize) (full) (hd : 1 ≤ d.val) : slot.b_rec l d full ⦃ fun _ => True ⦄ := by
  rw [slot.b_rec]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

-- @owner engB @status DONE @note measure nr - q
-- [engB] loop callees: -
@[local step]
theorem b_add_record_loop_spec (rv) (nr q wq : Std.Usize) (dropped) (hwq : wq.val ≤ q.val) :
    slot.b_add_record_loop rv nr q wq dropped ⦃ fun r => r.2.val ≤ max q.val nr.val ⦄ := by
  rw [slot.b_add_record_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, q', _, _) => nr.val - q'.val)
    (inv := fun (_, q', wq', _) => wq'.val ≤ q'.val ∧ q'.val ≤ max q.val nr.val)
  · rintro ⟨rv', q', wq', dr'⟩ ⟨h1, h2⟩
    simp only [slot.b_add_record_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact ⟨hwq, by scalar_tac⟩

-- @owner engB @status DONE @note facts B_RB (nonzero), B_FMAX (>= 1, for nf - 1); post bounds nr for b_engine's rn (not needed with B1)
-- [engB] fn callees: b_add_record_loop b_rec
@[local step]
theorem b_add_record_spec (rv) (nr nf l : Std.Usize) (d : Std.Usize) (flag) (hd : 1 ≤ d.val) :
    slot.b_add_record rv nr nf l d flag ⦃ fun r => r.1.1.val ≤ max nr.val slot.B_RB.val ⦄ := by
  rw [slot.b_add_record]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

-- @owner engB @status DONE (statement corrected: CONTRACT_ISSUES engB-4) @note measure `fun (l, _, _, run) => if run.val = 1 then cap.val + 9 - l.val else 0`
-- [engB] loop callees: -
@[local step]
theorem b_descend_loop0_loop0_spec (a) (i cap c l : Std.Usize) (wc wi) (run : Std.Usize) (hl : l.val ≤ 2 ^ 31) (hcap : cap.val ≤ 258) :
    slot.b_descend_loop0_loop0 a i cap c l wc wi run ⦃ fun r => r.1.val ≤ max l.val cap.val + 8 ⦄ := by
  rw [slot.b_descend_loop0_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (l', _, _, run') => cap.val + 8 - l'.val + min run'.val 1)
    (inv := fun (l', _, _, run') => l'.val ≤ max l.val cap.val + 8 ∧ (run'.val = 1 → l'.val ≤ max l.val cap.val))
  · rintro ⟨l', wc', wi', run'⟩ ⟨h1, h2⟩
    simp only [slot.b_descend_loop0_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact ⟨by scalar_tac, fun _ => by scalar_tac⟩

/-- The record block of one descent step (the same in the four paths of `b_descend`'s loop): a new
    longest match `l` at distance `d` may add a record. -/
theorem engB_rec_blk (a1 : Std.Array Std.U64 32768#usize) (rv : Std.Array Std.U32 32#usize) (wp : Std.U64)
    (l best scap rbest c d nr nf bl bd : Std.Usize) (L D : Nat) (hd : 1 ≤ d.val) (hl : l.val ≤ L)
    (hbl : bl.val ≤ L) (hdD : d.val ≤ D) (hbd : bd.val ≤ D) (hnr : nr.val ≤ slot.B_RB.val) :
    (if l > best then do
        let rl2 ← if l < scap then ok l else ok scap
        let (a4, i15, i16, i17) ←
          if rl2 > rbest then do
              let flag ←
                if c ≥ 1#usize then do
                    let i18 ← c - 1#usize
                    let i19 ← i18 % slot.B_WR
                    let i20 ← a1.index_usize i19
                    let i21 ← i20 >>> 56#i32
                    if i21 = wp then slot.B_FULL else ok 0#u32
                  else ok 0#u32
              let ((nr2, nf2), rv2) ← slot.b_add_record rv nr nf rl2 d flag
              ok (rv2, rl2, nr2, nf2)
            else ok (rv, rbest, nr, nf)
        ok (a4, l, i15, i16, i17, l, d)
      else ok (rv, best, rbest, nr, nf, bl, bd)) ⦃
      fun (x : Std.Array Std.U32 32#usize × Std.Usize × Std.Usize × Std.Usize × Std.Usize × Std.Usize ×
        Std.Usize) =>
      x.2.2.2.1.val ≤ slot.B_RB.val ∧ x.2.2.2.2.2.1.val ≤ L ∧ x.2.2.2.2.2.2.val ≤ D ⦄ := by
  split
  · step*
    repeat' (split <;> step*)
    all_goals try (obtain ⟨⟨x1, x2⟩, x3⟩ := x; simp only at *; step*)
    all_goals scalar_tac
  · simp only [WP.spec_ok]; exact ⟨hnr, hbl, hbd⟩

attribute [local step] engB_arr_index_le engB_arr_update_le in
/-- The tree-link block of one descent step: link the current node on the side the comparison
    chose and move to its child there. Entries stay at most `i`. -/
theorem engB_tree_blk (t : Std.Array Std.U32 65536#usize) (lt ls rs cs cur l ll rl : Std.Usize) (i L : Nat)
    (hT : LeAll t.val i) (hcur : cur.val ≤ i) (hi : i < 67108864) (hcs : cs.val ≤ 65534)
    (hl : l.val ≤ L) (hll : ll.val ≤ L) (hrl : rl.val ≤ L) :
    (if lt = 1#usize then do
        let i16 ← ls % slot.B_TS
        let i17 ← lift (UScalar.cast UScalarTy.U32 cur)
        let a5 ← t.update i16 i17
        let ls2 ← cs + 1#usize
        let i18 ← ls2 % slot.B_TS
        let i19 ← a5.index_usize i18
        let cur2 ← lift (UScalar.cast UScalarTy.Usize i19)
        ok (a5, cur2, ls2, rs, l, rl)
      else do
        let i16 ← rs % slot.B_TS
        let i17 ← lift (UScalar.cast UScalarTy.U32 cur)
        let a5 ← t.update i16 i17
        let i18 ← cs % slot.B_TS
        let i19 ← a5.index_usize i18
        let cur2 ← lift (UScalar.cast UScalarTy.Usize i19)
        ok (a5, cur2, ls, cs, ll, l)) ⦃
      fun (x : Std.Array Std.U32 65536#usize × Std.Usize × Std.Usize × Std.Usize × Std.Usize × Std.Usize) =>
      LeAll x.1.val i ∧ x.2.1.val ≤ i ∧ x.2.2.2.2.1.val ≤ L ∧ x.2.2.2.2.2.val ≤ L ⦄ := by
  have hc : (UScalar.cast UScalarTy.U32 cur).val = cur.val :=
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

/-- The loop invariant of `b_descend` (kept folded): tree and `pn` entries are earlier positions `+ 1`
    (at most `i`), the current node too; the kept lengths and the best length are below `2^30`
    (a length replayed from `pf` is `(pf >> 2) - 1`); `step + fuel` stays at most the depth
    (`≤ 2^20`); at most `B_RB` records; the best distance is at most `i`. -/
def engB_DInv (i : Nat) (tree : Std.Array Std.U32 65536#usize) (pn : Std.Array Std.U32 32#usize)
    (step cur ll rl fuel nr bl bd : Nat) : Prop :=
  LeAll tree.val i ∧ LeAll pn.val i ∧ cur ≤ i ∧ ll ≤ 2 ^ 30 ∧ rl ≤ 2 ^ 30 ∧ step + fuel ≤ 2 ^ 20 ∧
    nr ≤ slot.B_RB.val ∧ bl ≤ 2 ^ 30 ∧ bd ≤ i

theorem engB_DInv.mk {i : Nat} {tree : Std.Array Std.U32 65536#usize} {pn : Std.Array Std.U32 32#usize}
    {step cur ll rl fuel nr bl bd : Nat} (h1 : LeAll tree.val i) (h2 : LeAll pn.val i)
    (h3 : cur ≤ i ∧ ll ≤ 2 ^ 30 ∧ rl ≤ 2 ^ 30 ∧ step + fuel ≤ 2 ^ 20 ∧ nr ≤ slot.B_RB.val ∧
      bl ≤ 2 ^ 30 ∧ bd ≤ i) :
    engB_DInv i tree pn step cur ll rl fuel nr bl bd :=
  ⟨h1, h2, h3⟩

/-- The loop state of `b_descend` and its exit value. -/
abbrev engB_DState := Std.Array Std.U32 65536#usize × Std.Array Std.U32 32#usize × Std.Array Std.U32 32#usize ×
  Std.Array Std.U32 32#usize × Std.Usize × Std.Usize × Std.Usize × Std.Usize × Std.Usize × Std.Usize × Std.Usize ×
  Std.Usize × Std.Usize × Std.Usize × Std.Usize × Std.Usize × Std.Usize

abbrev engB_DOut := Std.Array Std.U32 65536#usize × Std.Array Std.U32 32#usize × Std.Array Std.U32 32#usize ×
  Std.Array Std.U32 32#usize × Std.Usize × Std.Usize × Std.Usize × Std.Usize × Std.Usize

/-- What one iteration of `b_descend`'s loop must establish (the form `loop.spec_decr_nat` gives). -/
def engB_DPost (i fuel : Nat) (r : ControlFlow engB_DState engB_DOut) : Prop :=
  match r with
  | .done y => LeAll y.1.val i ∧ LeAll y.2.1.val i ∧ y.2.2.2.2.2.1.val ≤ slot.B_RB.val ∧
      y.2.2.2.2.2.2.2.1.val ≤ 2 ^ 30 ∧ y.2.2.2.2.2.2.2.2.val ≤ i
  | .cont x' => engB_DInv i x'.1 x'.2.1 x'.2.2.2.2.1.val x'.2.2.2.2.2.1.val x'.2.2.2.2.2.2.2.2.1.val
      x'.2.2.2.2.2.2.2.2.2.1.val x'.2.2.2.2.2.2.2.2.2.2.1.val x'.2.2.2.2.2.2.2.2.2.2.2.2.2.1.val
      x'.2.2.2.2.2.2.2.2.2.2.2.2.2.2.2.1.val x'.2.2.2.2.2.2.2.2.2.2.2.2.2.2.2.2.val ∧
      x'.2.2.2.2.2.2.2.2.2.2.1.val < fuel

set_option maxHeartbeats 4000000 in
attribute [local step] engB_arr_index_le_d engB_arr_update_le_d in
/-- The end of one descent step (shared by its four paths): record a longer match, then either stop
    (the match reaches `cap`: copy the node's links) or link the node and descend. -/
theorem engB_desc_tail (a1 : Std.Array Std.U64 32768#usize) (t : Std.Array Std.U32 65536#usize)
    (PN PF rv : Std.Array Std.U32 32#usize) (wp : Std.U64)
    (i cap scap l c d lt ls rs cur ll rl fuel best rbest nr nf bl bd step1 : Std.Usize)
    (hT : LeAll t.val i.val) (hPN : LeAll PN.val i.val) (hi : i.val < 67108864) (hcap : cap.val ≤ 258)
    (hcur : cur.val ≤ i.val) (hll : ll.val ≤ 2 ^ 30) (hrl : rl.val ≤ 2 ^ 30) (hl : l.val ≤ 2 ^ 30)
    (hf : 0 < fuel.val) (hsf : step1.val + fuel.val ≤ 2 ^ 20 + 1) (hnr : nr.val ≤ slot.B_RB.val)
    (hbl : bl.val ≤ 2 ^ 30) (hd1 : 1 ≤ d.val) (hd : d.val ≤ i.val) (hbd : bd.val ≤ i.val) (hc : c.val < i.val) :
    (do
      let (rv1, best1, rbest1, nr1, nf1, bl1, bd1) ←
        if l > best then do
            let rl2 ← if l < scap then ok l else ok scap
            let (a4, i15, i16, i17) ←
              if rl2 > rbest then do
                  let flag ←
                    if c ≥ 1#usize then do
                        let i18 ← c - 1#usize
                        let i19 ← i18 % slot.B_WR
                        let i20 ← a1.index_usize i19
                        let i21 ← i20 >>> 56#i32
                        if i21 = wp then slot.B_FULL else ok 0#u32
                      else ok 0#u32
                  let ((nr2, nf2), rv2) ← slot.b_add_record rv nr nf rl2 d flag
                  ok (rv2, rl2, nr2, nf2)
                else ok (rv, rbest, nr, nf)
            ok (a4, l, i15, i16, i17, l, d)
          else ok (rv, best, rbest, nr, nf, bl, bd)
      let i15 ← c % slot.B_WR
      let cs ← 2#usize * i15
      if l ≥ cap then do
          let i16 ← cs % slot.B_TS
          let i17 ← t.index_usize i16
          let i18 ← ls % slot.B_TS
          let a4 ← t.update i18 i17
          let i19 ← cs + 1#usize
          let i20 ← i19 % slot.B_TS
          let i21 ← a4.index_usize i20
          let i22 ← rs % slot.B_TS
          let a5 ← a4.update i22 i21
          ok
              (cont
                (a5, PN, PF, rv1, step1, cur, ls, rs, ll, rl, 0#usize, best1, rbest1, nr1, nf1, bl1, bd1))
        else do
          let (a4, cur1, ls1, rs1, ll1, rl1) ←
            if lt = 1#usize then do
                let i16 ← ls % slot.B_TS
                let i17 ← lift (UScalar.cast UScalarTy.U32 cur)
                let a5 ← t.update i16 i17
                let ls2 ← cs + 1#usize
                let i18 ← ls2 % slot.B_TS
                let i19 ← a5.index_usize i18
                let cur2 ← lift (UScalar.cast UScalarTy.Usize i19)
                ok (a5, cur2, ls2, rs, l, rl)
              else do
                let i16 ← rs % slot.B_TS
                let i17 ← lift (UScalar.cast UScalarTy.U32 cur)
                let a5 ← t.update i16 i17
                let i18 ← cs % slot.B_TS
                let i19 ← a5.index_usize i18
                let cur2 ← lift (UScalar.cast UScalarTy.Usize i19)
                ok (a5, cur2, ls, cs, ll, l)
          let fuel1 ← fuel - 1#usize
          if fuel1 = 0#usize then do
              let i16 ← ls1 % slot.B_TS
              let a5 ← a4.update i16 0#u32
              let i17 ← rs1 % slot.B_TS
              let a6 ← a5.update i17 0#u32
              ok
                  (cont
                    (a6, PN, PF, rv1, step1, cur1, ls1, rs1, ll1, rl1, fuel1, best1, rbest1, nr1, nf1, bl1, bd1))
            else
              ok
                (cont
                  (a4, PN, PF, rv1, step1, cur1, ls1, rs1, ll1, rl1, fuel1, best1, rbest1, nr1, nf1, bl1, bd1)))
      ⦃ engB_DPost i.val fuel.val ⦄ := by
  apply WP.spec_bind (engB_rec_blk a1 rv wp l best scap rbest c d nr nf bl bd (2 ^ 30) i.val hd1 hl hbl hd hbd hnr)
  rintro ⟨rv1, best1, rbest1, nr1, nf1, bl1, bd1⟩ ⟨hr1, hr2, hr3⟩
  step* +scalarTac -grind
  · exact ⟨engB_DInv.mk (by assumption) hPN (by scalar_tac), by scalar_tac⟩
  · apply WP.spec_bind (engB_tree_blk t lt ls rs cs cur l ll rl i.val (2 ^ 30) hT hcur hi (by scalar_tac) hl hll hrl)
    rintro ⟨a4, cur1, ls1, rs1, ll1, rl1⟩ ⟨ht1, ht2, ht3, ht4⟩
    step* +scalarTac -grind
    all_goals exact ⟨engB_DInv.mk (by assumption) hPN (by scalar_tac), by scalar_tac⟩

set_option maxHeartbeats 4000000 in
attribute [local step] engB_arr_index_mut_spec in
/-- The known branch of one descent step: the previous position's descent met `c - 1` at this
    step, so the comparison is replayed from `pf` (`l = (pf >> 2) - 1`, `pf ≥ 4`). -/
theorem engB_desc_known (a1 : Std.Array Std.U64 32768#usize) (t : Std.Array Std.U32 65536#usize)
    (pn pf' rv : Std.Array Std.U32 32#usize) (wp : Std.U64) (pf : Std.U32)
    (i cap scap c d i2 ls rs cur ll rl fuel best rbest nr nf bl bd step : Std.Usize)
    (hT : LeAll t.val i.val) (hP : LeAll pn.val i.val) (hi : i.val < 67108864) (hcap : cap.val ≤ 258)
    (hcur : cur.val ≤ i.val) (hll : ll.val ≤ 2 ^ 30) (hrl : rl.val ≤ 2 ^ 30) (h4 : 4 ≤ pf.val)
    (hf : 0 < fuel.val) (hsf : step.val + fuel.val ≤ 2 ^ 20) (hnr : nr.val ≤ slot.B_RB.val)
    (hbl : bl.val ≤ 2 ^ 30) (hd1 : 1 ≤ d.val) (hd : d.val ≤ i.val) (hbd : bd.val ≤ i.val) (hc : c.val < i.val)
    (hi2 : i2.val < 32) :
    (do
      let i3 ← pf >>> 2#i32
      let i4 ← lift (UScalar.cast UScalarTy.Usize i3)
      let l1 ← i4 - 1#usize
      let i5 ← pf >>> 1#i32
      let i6 ← lift (i5 &&& 1#u32)
      let lt ← lift (UScalar.cast UScalarTy.Usize i6)
      if step < slot.B_PS then do
          let (_, index_mut_back) ← pn.index_mut_usize i2
          let i7 ← lift (UScalar.cast UScalarTy.U32 c)
          let i8 ← if l1 < cap then ok 1#u32 else ok 0#u32
          let i9 ← lift (UScalar.cast UScalarTy.U32 lt)
          let i10 ← i9 <<< 1#i32
          let i11 ← lift (i8 ||| i10)
          let i12 ← lift (UScalar.cast UScalarTy.U32 l1)
          let i13 ← i12 <<< 2#i32
          let (_, index_mut_back1) ← pf'.index_mut_usize i2
          let i14 ← lift (i11 ||| i13)
          let step1 ← step + 1#usize
          let (rv1, best1, rbest1, nr1, nf1, bl1, bd1) ←
            if l1 > best then do
                let rl2 ← if l1 < scap then ok l1 else ok scap
                let (a4, u15, u16, u17) ←
                  if rl2 > rbest then do
                      let flag ←
                        if c ≥ 1#usize then do
                            let u18 ← c - 1#usize
                            let u19 ← u18 % slot.B_WR
                            let u20 ← a1.index_usize u19
                            let u21 ← u20 >>> 56#i32
                            if u21 = wp then slot.B_FULL else ok 0#u32
                          else ok 0#u32
                      let ((nr2, nf2), rv2) ← slot.b_add_record rv nr nf rl2 d flag
                      ok (rv2, rl2, nr2, nf2)
                    else ok (rv, rbest, nr, nf)
                ok (a4, l1, u15, u16, u17, l1, d)
              else ok (rv, best, rbest, nr, nf, bl, bd)
          let u15 ← c % slot.B_WR
          let cs ← 2#usize * u15
          if l1 ≥ cap then do
              let u16 ← cs % slot.B_TS
              let u17 ← t.index_usize u16
              let u18 ← ls % slot.B_TS
              let a4 ← t.update u18 u17
              let u19 ← cs + 1#usize
              let u20 ← u19 % slot.B_TS
              let u21 ← a4.index_usize u20
              let u22 ← rs % slot.B_TS
              let a5 ← a4.update u22 u21
              ok
                  (cont
                    (a5, index_mut_back i7, index_mut_back1 i14, rv1, step1, cur, ls, rs, ll, rl, 0#usize, best1, rbest1, nr1, nf1, bl1, bd1))
            else do
              let (a4, cur1, ls1, rs1, ll1, rl1) ←
                if lt = 1#usize then do
                    let u16 ← ls % slot.B_TS
                    let u17 ← lift (UScalar.cast UScalarTy.U32 cur)
                    let a5 ← t.update u16 u17
                    let ls2 ← cs + 1#usize
                    let u18 ← ls2 % slot.B_TS
                    let u19 ← a5.index_usize u18
                    let cur2 ← lift (UScalar.cast UScalarTy.Usize u19)
                    ok (a5, cur2, ls2, rs, l1, rl)
                  else do
                    let u16 ← rs % slot.B_TS
                    let u17 ← lift (UScalar.cast UScalarTy.U32 cur)
                    let a5 ← t.update u16 u17
                    let u18 ← cs % slot.B_TS
                    let u19 ← a5.index_usize u18
                    let cur2 ← lift (UScalar.cast UScalarTy.Usize u19)
                    ok (a5, cur2, ls, cs, ll, l1)
              let fuel1 ← fuel - 1#usize
              if fuel1 = 0#usize then do
                  let u16 ← ls1 % slot.B_TS
                  let a5 ← a4.update u16 0#u32
                  let u17 ← rs1 % slot.B_TS
                  let a6 ← a5.update u17 0#u32
                  ok
                      (cont
                        (a6, index_mut_back i7, index_mut_back1 i14, rv1, step1, cur1, ls1, rs1, ll1, rl1, fuel1, best1, rbest1, nr1, nf1, bl1, bd1))
                else
                  ok
                    (cont
                      (a4, index_mut_back i7, index_mut_back1 i14, rv1, step1, cur1, ls1, rs1, ll1, rl1, fuel1, best1, rbest1, nr1, nf1, bl1, bd1))
        else do
          let step1 ← step + 1#usize
          let (rv1, best1, rbest1, nr1, nf1, bl1, bd1) ←
            if l1 > best then do
                let rl2 ← if l1 < scap then ok l1 else ok scap
                let (a4, u15, u16, u17) ←
                  if rl2 > rbest then do
                      let flag ←
                        if c ≥ 1#usize then do
                            let u18 ← c - 1#usize
                            let u19 ← u18 % slot.B_WR
                            let u20 ← a1.index_usize u19
                            let u21 ← u20 >>> 56#i32
                            if u21 = wp then slot.B_FULL else ok 0#u32
                          else ok 0#u32
                      let ((nr2, nf2), rv2) ← slot.b_add_record rv nr nf rl2 d flag
                      ok (rv2, rl2, nr2, nf2)
                    else ok (rv, rbest, nr, nf)
                ok (a4, l1, u15, u16, u17, l1, d)
              else ok (rv, best, rbest, nr, nf, bl, bd)
          let u15 ← c % slot.B_WR
          let cs ← 2#usize * u15
          if l1 ≥ cap then do
              let u16 ← cs % slot.B_TS
              let u17 ← t.index_usize u16
              let u18 ← ls % slot.B_TS
              let a4 ← t.update u18 u17
              let u19 ← cs + 1#usize
              let u20 ← u19 % slot.B_TS
              let u21 ← a4.index_usize u20
              let u22 ← rs % slot.B_TS
              let a5 ← a4.update u22 u21
              ok
                  (cont
                    (a5, pn, pf', rv1, step1, cur, ls, rs, ll, rl, 0#usize, best1, rbest1, nr1, nf1, bl1, bd1))
            else do
              let (a4, cur1, ls1, rs1, ll1, rl1) ←
                if lt = 1#usize then do
                    let u16 ← ls % slot.B_TS
                    let u17 ← lift (UScalar.cast UScalarTy.U32 cur)
                    let a5 ← t.update u16 u17
                    let ls2 ← cs + 1#usize
                    let u18 ← ls2 % slot.B_TS
                    let u19 ← a5.index_usize u18
                    let cur2 ← lift (UScalar.cast UScalarTy.Usize u19)
                    ok (a5, cur2, ls2, rs, l1, rl)
                  else do
                    let u16 ← rs % slot.B_TS
                    let u17 ← lift (UScalar.cast UScalarTy.U32 cur)
                    let a5 ← t.update u16 u17
                    let u18 ← cs % slot.B_TS
                    let u19 ← a5.index_usize u18
                    let cur2 ← lift (UScalar.cast UScalarTy.Usize u19)
                    ok (a5, cur2, ls, cs, ll, l1)
              let fuel1 ← fuel - 1#usize
              if fuel1 = 0#usize then do
                  let u16 ← ls1 % slot.B_TS
                  let a5 ← a4.update u16 0#u32
                  let u17 ← rs1 % slot.B_TS
                  let a6 ← a5.update u17 0#u32
                  ok
                      (cont
                        (a6, pn, pf', rv1, step1, cur1, ls1, rs1, ll1, rl1, fuel1, best1, rbest1, nr1, nf1, bl1, bd1))
                else
                  ok
                    (cont
                      (a4, pn, pf', rv1, step1, cur1, ls1, rs1, ll1, rl1, fuel1, best1, rbest1, nr1, nf1, bl1, bd1))) ⦃ engB_DPost i.val fuel.val ⦄ := by
  have hpf2 := engB_u32_shr2 pf
  have hc32 : (UScalar.cast UScalarTy.U32 c).val = c.val :=
    UScalar.cast_val_mod_pow_of_inBounds_eq _ _ (by scalar_tac)
  step* +scalarTac -grind
  · apply WP.spec_bind (Pₘ := fun (_ : Std.U32) => True)
    · split <;> simp
    · intro i8 _
      step* +scalarTac -grind
      exact engB_desc_tail a1 t (index_mut_back i7) (index_mut_back1 i14) rv wp i cap scap l1 c d lt ls rs
        cur ll rl fuel best rbest nr nf bl bd step1 hT
        (by rw [‹index_mut_back = pn.set _›, Std.Array.set_val_eq]
            exact LeAll_set hP _ _ (by scalar_tac))
        hi hcap hcur hll hrl (by scalar_tac) hf (by scalar_tac) hnr hbl hd1 hd hbd hc
  · exact engB_desc_tail a1 t pn pf' rv wp i cap scap l1 c d lt ls rs cur ll rl fuel best
      rbest nr nf bl bd step1 hT hP hi hcap hcur hll hrl (by scalar_tac) hf (by scalar_tac)
      hnr hbl hd1 hd hbd hc

set_option maxHeartbeats 4000000 in
attribute [local step] engB_arr_index_mut_spec_b in
/-- The other branch of one descent step: compare the ring words of `c` and `i` from the common
    length `l` (or from the hint `hl` when `c` is the hinted node). -/
theorem engB_desc_cmp (a1 : Std.Array Std.U64 32768#usize) (t : Std.Array Std.U32 65536#usize)
    (pn pf' rv : Std.Array Std.U32 32#usize) (wp : Std.U64)
    (i cap scap c d hn hl l ls rs cur ll rl fuel best rbest nr nf bl bd step : Std.Usize)
    (hT : LeAll t.val i.val) (hP : LeAll pn.val i.val) (hi : i.val < 67108864) (hcap : cap.val ≤ 258)
    (hcur : cur.val ≤ i.val) (hll : ll.val ≤ 2 ^ 30) (hrl : rl.val ≤ 2 ^ 30) (hlb : l.val ≤ 2 ^ 30)
    (hhl : hl.val ≤ 2 ^ 30)
    (hf : 0 < fuel.val) (hsf : step.val + fuel.val ≤ 2 ^ 20) (hnr : nr.val ≤ slot.B_RB.val)
    (hbl : bl.val ≤ 2 ^ 30) (hd1 : 1 ≤ d.val) (hd : d.val ≤ i.val) (hbd : bd.val ≤ i.val) (hc : c.val < i.val) :
    (do
      let l1 ← if c = hn then if hl > l then ok hl else ok l else ok l
      let i3 ← lift (core.num.Usize.wrapping_add c l1)
      let i4 ← i3 % slot.B_WR
      let wc ← a1.index_usize i4
      let i5 ← lift (core.num.Usize.wrapping_add i l1)
      let i6 ← i5 % slot.B_WR
      let wi ← a1.index_usize i6
      let (l2, wc1, wi1, run) ← slot.b_descend_loop0_loop0 a1 i cap c l1 wc wi 1#usize
      let l3 ←
        if run = 1#usize then do
            let i7 ← lift (wc1 ^^^ wi1)
            let i8 ← lift (core.num.U64.leading_zeros i7)
            let i9 ← i8 / 8#u32
            let i10 ← lift (UScalar.cast UScalarTy.Usize i9)
            l2 + i10
          else ok l2
      let l4 ← if l3 > cap then ok cap else ok l3
      let lt ← if wc1 < wi1 then ok 1#usize else ok 0#usize
      if step < slot.B_PS then do
          let i7 ← step % slot.B_PS
          let (_, index_mut_back) ← pn.index_mut_usize i7
          let i8 ← lift (UScalar.cast UScalarTy.U32 c)
          let i9 ← if l4 < cap then ok 1#u32 else ok 0#u32
          let i10 ← lift (UScalar.cast UScalarTy.U32 lt)
          let i11 ← i10 <<< 1#i32
          let i12 ← lift (i9 ||| i11)
          let i13 ← lift (UScalar.cast UScalarTy.U32 l4)
          let i14 ← i13 <<< 2#i32
          let (_, index_mut_back1) ← pf'.index_mut_usize i7
          let i15 ← lift (i12 ||| i14)
          let step1 ← step + 1#usize
          let (rv1, best1, rbest1, nr1, nf1, bl1, bd1) ←
            if l4 > best then do
                let rl2 ← if l4 < scap then ok l4 else ok scap
                let (a4, u15, u16, u17) ←
                  if rl2 > rbest then do
                      let flag ←
                        if c ≥ 1#usize then do
                            let u18 ← c - 1#usize
                            let u19 ← u18 % slot.B_WR
                            let u20 ← a1.index_usize u19
                            let u21 ← u20 >>> 56#i32
                            if u21 = wp then slot.B_FULL else ok 0#u32
                          else ok 0#u32
                      let ((nr2, nf2), rv2) ← slot.b_add_record rv nr nf rl2 d flag
                      ok (rv2, rl2, nr2, nf2)
                    else ok (rv, rbest, nr, nf)
                ok (a4, l4, u15, u16, u17, l4, d)
              else ok (rv, best, rbest, nr, nf, bl, bd)
          let u15 ← c % slot.B_WR
          let cs ← 2#usize * u15
          if l4 ≥ cap then do
              let u16 ← cs % slot.B_TS
              let u17 ← t.index_usize u16
              let u18 ← ls % slot.B_TS
              let a4 ← t.update u18 u17
              let u19 ← cs + 1#usize
              let u20 ← u19 % slot.B_TS
              let u21 ← a4.index_usize u20
              let u22 ← rs % slot.B_TS
              let a5 ← a4.update u22 u21
              ok
                  (cont
                    (a5, index_mut_back i8, index_mut_back1 i15, rv1, step1, cur, ls, rs, ll, rl, 0#usize, best1, rbest1, nr1, nf1, bl1, bd1))
            else do
              let (a4, cur1, ls1, rs1, ll1, rl1) ←
                if lt = 1#usize then do
                    let u16 ← ls % slot.B_TS
                    let u17 ← lift (UScalar.cast UScalarTy.U32 cur)
                    let a5 ← t.update u16 u17
                    let ls2 ← cs + 1#usize
                    let u18 ← ls2 % slot.B_TS
                    let u19 ← a5.index_usize u18
                    let cur2 ← lift (UScalar.cast UScalarTy.Usize u19)
                    ok (a5, cur2, ls2, rs, l4, rl)
                  else do
                    let u16 ← rs % slot.B_TS
                    let u17 ← lift (UScalar.cast UScalarTy.U32 cur)
                    let a5 ← t.update u16 u17
                    let u18 ← cs % slot.B_TS
                    let u19 ← a5.index_usize u18
                    let cur2 ← lift (UScalar.cast UScalarTy.Usize u19)
                    ok (a5, cur2, ls, cs, ll, l4)
              let fuel1 ← fuel - 1#usize
              if fuel1 = 0#usize then do
                  let u16 ← ls1 % slot.B_TS
                  let a5 ← a4.update u16 0#u32
                  let u17 ← rs1 % slot.B_TS
                  let a6 ← a5.update u17 0#u32
                  ok
                      (cont
                        (a6, index_mut_back i8, index_mut_back1 i15, rv1, step1, cur1, ls1, rs1, ll1, rl1, fuel1, best1, rbest1, nr1, nf1, bl1, bd1))
                else
                  ok
                    (cont
                      (a4, index_mut_back i8, index_mut_back1 i15, rv1, step1, cur1, ls1, rs1, ll1, rl1, fuel1, best1, rbest1, nr1, nf1, bl1, bd1))
        else do
          let step1 ← step + 1#usize
          let (rv1, best1, rbest1, nr1, nf1, bl1, bd1) ←
            if l4 > best then do
                let rl2 ← if l4 < scap then ok l4 else ok scap
                let (a4, u15, u16, u17) ←
                  if rl2 > rbest then do
                      let flag ←
                        if c ≥ 1#usize then do
                            let u18 ← c - 1#usize
                            let u19 ← u18 % slot.B_WR
                            let u20 ← a1.index_usize u19
                            let u21 ← u20 >>> 56#i32
                            if u21 = wp then slot.B_FULL else ok 0#u32
                          else ok 0#u32
                      let ((nr2, nf2), rv2) ← slot.b_add_record rv nr nf rl2 d flag
                      ok (rv2, rl2, nr2, nf2)
                    else ok (rv, rbest, nr, nf)
                ok (a4, l4, u15, u16, u17, l4, d)
              else ok (rv, best, rbest, nr, nf, bl, bd)
          let u15 ← c % slot.B_WR
          let cs ← 2#usize * u15
          if l4 ≥ cap then do
              let u16 ← cs % slot.B_TS
              let u17 ← t.index_usize u16
              let u18 ← ls % slot.B_TS
              let a4 ← t.update u18 u17
              let u19 ← cs + 1#usize
              let u20 ← u19 % slot.B_TS
              let u21 ← a4.index_usize u20
              let u22 ← rs % slot.B_TS
              let a5 ← a4.update u22 u21
              ok
                  (cont
                    (a5, pn, pf', rv1, step1, cur, ls, rs, ll, rl, 0#usize, best1, rbest1, nr1, nf1, bl1, bd1))
            else do
              let (a4, cur1, ls1, rs1, ll1, rl1) ←
                if lt = 1#usize then do
                    let u16 ← ls % slot.B_TS
                    let u17 ← lift (UScalar.cast UScalarTy.U32 cur)
                    let a5 ← t.update u16 u17
                    let ls2 ← cs + 1#usize
                    let u18 ← ls2 % slot.B_TS
                    let u19 ← a5.index_usize u18
                    let cur2 ← lift (UScalar.cast UScalarTy.Usize u19)
                    ok (a5, cur2, ls2, rs, l4, rl)
                  else do
                    let u16 ← rs % slot.B_TS
                    let u17 ← lift (UScalar.cast UScalarTy.U32 cur)
                    let a5 ← t.update u16 u17
                    let u18 ← cs % slot.B_TS
                    let u19 ← a5.index_usize u18
                    let cur2 ← lift (UScalar.cast UScalarTy.Usize u19)
                    ok (a5, cur2, ls, cs, ll, l4)
              let fuel1 ← fuel - 1#usize
              if fuel1 = 0#usize then do
                  let u16 ← ls1 % slot.B_TS
                  let a5 ← a4.update u16 0#u32
                  let u17 ← rs1 % slot.B_TS
                  let a6 ← a5.update u17 0#u32
                  ok
                      (cont
                        (a6, pn, pf', rv1, step1, cur1, ls1, rs1, ll1, rl1, fuel1, best1, rbest1, nr1, nf1, bl1, bd1))
                else
                  ok
                    (cont
                      (a4, pn, pf', rv1, step1, cur1, ls1, rs1, ll1, rl1, fuel1, best1, rbest1, nr1, nf1, bl1, bd1))) ⦃ engB_DPost i.val fuel.val ⦄ := by
  have hc32 : (UScalar.cast UScalarTy.U32 c).val = c.val :=
    UScalar.cast_val_mod_pow_of_inBounds_eq _ _ (by scalar_tac)
  apply WP.spec_bind (Pₘ := fun (l1 : Std.Usize) => l1.val ≤ 2 ^ 30)
  · split
    · split <;> simp <;> scalar_tac
    · simp; scalar_tac
  · intro l1 hl1
    step* +scalarTac -grind
    apply WP.spec_bind (Pₘ := fun (l3 : Std.Usize) => l3.val ≤ 2 ^ 30 + 300)
    · split
      · step* +scalarTac -grind
        all_goals scalar_tac
      · simp; scalar_tac
    · intro l3 hl3
      apply WP.spec_bind (Pₘ := fun (l4 : Std.Usize) => l4.val ≤ cap.val)
      · split <;> simp <;> scalar_tac
      · intro l4 hl4
        apply WP.spec_bind (Pₘ := fun (_ : Std.Usize) => True)
        · split <;> simp
        · intro lt _
          step* +scalarTac -grind
          · apply WP.spec_bind (Pₘ := fun (_ : Std.U32) => True)
            · split <;> simp
            · intro i9 _
              step* +scalarTac -grind
              exact engB_desc_tail a1 t (index_mut_back i8) (index_mut_back1 i15) rv wp i cap scap l4 c d lt
                ls rs cur ll rl fuel best rbest nr nf bl bd step1 hT
                (by rw [‹index_mut_back = pn.set _›, Std.Array.set_val_eq]
                    exact LeAll_set hP _ _ (by scalar_tac))
                hi hcap hcur hll hrl (by scalar_tac) hf (by scalar_tac) hnr hbl hd1 hd hbd hc
          · exact engB_desc_tail a1 t pn pf' rv wp i cap scap l4 c d lt ls rs cur ll rl fuel
              best rbest nr nf bl bd step1 hT hP hi hcap hcur hll hrl (by scalar_tac) hf
              (by scalar_tac) hnr hbl hd1 hd hbd hc

-- @owner engB @status DONE (statement corrected: CONTRACT_ISSUES engB-5) @note `c = i - d` needs cur <= i (tree entries are older positions + 1): either the LeAll tree invariant here, or B7 (add `|| cur > i` to the exit test). 467-line body, 28 bind-ifs: WP.spec_bind per `if`; `simp only [body]` overflows, use `unfold`. Measure: fuel. Check tuple projections against the extraction
-- [engB] loop callees: b_add_record b_descend_loop0_loop0
set_option maxHeartbeats 8000000 in
attribute [local step] engB_arr_index_le_g engB_arr_update_le_g engB_arr_index_mut_spec_c in
@[local step]
theorem b_descend_loop0_spec (a : Std.Array Std.U32 65536#usize) (a1) (a2 : Std.Array Std.U32 32#usize) (a3)
    (plen hn hl i cap scap : Std.Usize) (wp rv) (step cur ls rs ll rl fuel best rbest nr nf bl bd : Std.Usize)
    (hi : i.val < 67108864) (hcap : cap.val ≤ 258) (hhl : hl.val ≤ 2 ^ 30)
    (hinv : engB_DInv i.val a a2 step.val cur.val ll.val rl.val fuel.val nr.val bl.val bd.val) :
    slot.b_descend_loop0 a a1 a2 a3 plen hn hl i cap scap wp rv step cur ls rs ll rl fuel best rbest nr nf bl bd
      ⦃ fun r => LeAll r.1.val i.val ∧ LeAll r.2.1.val i.val ∧ r.2.2.2.2.2.1.val ≤ slot.B_RB.val ∧
        r.2.2.2.2.2.2.2.1.val ≤ 2 ^ 30 ∧ r.2.2.2.2.2.2.2.2.val ≤ i.val ⦄ := by
  rw [slot.b_descend_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, _, _, _, _, _, _, fuel', _, _, _, _, _, _) => fuel'.val)
    (inv := fun (t', pn', _, _, step', cur', _, _, ll', rl', fuel', _, _, nr', _, bl', bd') =>
      engB_DInv i.val t' pn' step'.val cur'.val ll'.val rl'.val fuel'.val nr'.val bl'.val bd'.val)
  · rintro ⟨t', pn', pf', rv', step', cur', ls', rs', ll', rl', fuel', best', rbest', nr', nf', bl', bd'⟩
      ⟨hT, hP, hcur, hll, hrl, hsf, hnr, hbl, hbd⟩
    have hpf : LeAll pf'.val 4294967295 := engB_LeAll_u32 _
    show WP.spec (slot.b_descend_loop0.body a1 plen hn hl i cap scap wp t' pn' pf' rv' step' cur' ls' rs'
      ll' rl' fuel' best' rbest' nr' nf' bl' bd') _
    unfold slot.b_descend_loop0.body
    by_cases hf : fuel' > 0#usize
    · rw [if_pos hf]
      have hf' : 0 < fuel'.val := by scalar_tac
      step* +scalarTac -grind
      -- the three exits (`cur = 0`, `d = 0`, `d ≥ B_WLIM`): two links cleared, fuel 0
      all_goals try (refine ⟨engB_DInv.mk ‹LeAll a5.val i.val› hP (by scalar_tac), by scalar_tac⟩)
      · -- `c = i - d`: the wrapping distance is exact since `cur ≤ i`
        rw [d_post, engB_wsub_val i1 cur' (by scalar_tac)]; scalar_tac
      · have hd1 : 1 ≤ d.val := by
          rw [d_post, engB_wsub_val i1 cur' (by scalar_tac)]; scalar_tac
        have hci : c.val < i.val := by scalar_tac
        apply WP.spec_bind (Pₘ := fun (k : Bool) => k = true → 4 ≤ pf.val)
        · split
          · step* +scalarTac -grind
            all_goals first
              | (intro h; simp at h)
              | (intro h; simp only [decide_eq_true_eq] at h; scalar_tac)
          · simp
        · intro known hknown
          apply WP.spec_bind (Pₘ := fun (l : Std.Usize) => l.val ≤ 2 ^ 30)
          · split <;> simp <;> scalar_tac
          · intro l hlb
            split
            · refine WP.spec_mono (engB_desc_known a1 t' pn' pf' rv' wp pf i cap scap c d i2 ls' rs' cur' ll'
                rl' fuel' best' rbest' nr' nf' bl' bd' step' hT hP hi hcap hcur hll hrl (hknown ‹_›) hf' hsf
                hnr hbl hd1 (by scalar_tac) hbd hci (by scalar_tac)) ?_
              intro r hr; cases r <;> exact hr
            · refine WP.spec_mono (engB_desc_cmp a1 t' pn' pf' rv' wp i cap scap c d hn hl l ls' rs' cur' ll'
                rl' fuel' best' rbest' nr' nf' bl' bd' step' hT hP hi hcap hcur hll hrl hlb hhl hf' hsf
                hnr hbl hd1 (by scalar_tac) hbd hci) ?_
              intro r hr; cases r <;> exact hr
    · rw [if_neg hf]
      simp only [WP.spec_ok]
      exact ⟨hT, hP, hnr, hbl, hbd⟩
  · exact hinv

-- @owner engB @status DONE (proved; uses B_NOHINT_spec, BLOCKED R2) @note statement corrected: CONTRACT_ISSUES engB-6
-- [engB] fn callees: b_descend_loop0
@[local step]
theorem b_descend_spec (mf : slot.BMf) (first i cap scap best0 wp rv) (nr0 : Std.Usize) (nf0) (depth : Std.Usize)
    (hi : i.val < 67108864) (hcap : cap.val ≤ 258) (hfirst : first.val ≤ i.val)
    (htree : LeAll mf.tree.val i.val) (hpn : LeAll mf.pn.val i.val) (hhl : mf.hl.val ≤ 2 ^ 30)
    (hnr : nr0.val ≤ slot.B_RB.val) (hdepth : depth.val ≤ 1048576) :
    slot.b_descend mf first i cap scap best0 wp rv nr0 nf0 depth ⦃ fun r =>
      r.1.1.val ≤ slot.B_RB.val ∧ LeAll r.2.1.tree.val i.val ∧ LeAll r.2.1.pn.val i.val ∧
      r.2.1.hl.val ≤ 2 ^ 30 ∧ r.2.1.head = mf.head ∧ r.2.1.head3 = mf.head3 ⦄ := by
  rw [slot.b_descend]
  have hinv : engB_DInv i.val mf.tree mf.pn (0#usize).val first.val (0#usize).val (0#usize).val
      depth.val nr0.val (0#usize).val (0#usize).val := engB_DInv.mk htree hpn (by simp; scalar_tac)
  step*
  repeat' (split <;> step*)
  all_goals simp_all <;> scalar_tac

-- @owner engB @status DONE
-- [engB] fn callees: -
@[local step]
theorem b_byte_at_spec (s p) :
    slot.b_byte_at s p ⦃ fun _ => True ⦄ := by
  rw [slot.b_byte_at]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

-- @owner engB @status DONE @note measure `fun cc => segcap.val + 1 - cc.length`
-- [engB] loop callees: -
@[local step]
theorem b_engine_loop0_spec (segcap : Std.Usize) (cc) (hseg : segcap.val < 67108864) :
    slot.b_engine_loop0 segcap cc ⦃ fun r => segcap.val < r.length ⦄ := by
  rw [slot.b_engine_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun cc_ => segcap.val + 1 - cc_.length)
    (inv := fun _ => True)
  · rintro cc_ _
    simp only [slot.b_engine_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial

-- @owner engB @status DONE
-- [engB] loop callees: b_byte_at
@[local step]
theorem b_engine_loop1_spec (input x k) :
    slot.b_engine_loop1 input x k ⦃ fun _ => True ⦄ := by
  rw [slot.b_engine_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (x_, k_) => 8 - k_.val)
    (inv := fun _ => True)
  · rintro ⟨x_, k_⟩ _
    simp only [slot.b_engine_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial

/-- The match finder's tables at position `i`: hash heads, tree and `pn` entries are earlier
    positions `+ 1` (so at most `i`); the hint length is at most `2^30`. -/
def engB_MfInv (mf : slot.BMf) (i : Nat) : Prop :=
  LeAll mf.head.val i ∧ LeAll mf.head3.val i ∧ LeAll mf.tree.val i ∧ LeAll mf.pn.val i ∧
    mf.hl.val ≤ 2 ^ 30

/-- The empty match finder (`b_engine`'s initial state) satisfies the table invariant at 0. -/
theorem engB_MfInv_init (w : Std.Array Std.U64 32768#usize) (pf : Std.Array Std.U32 32#usize) (plen hn : Std.Usize) :
    engB_MfInv
      { head := Std.Array.repeat 65536#usize 0#u32, head3 := Std.Array.repeat 16384#usize 0#u32,
        tree := Std.Array.repeat 65536#usize 0#u32, w := w, pn := Std.Array.repeat 32#usize 0#u32, pf := pf,
        plen := plen, hn := hn, hl := 0#usize } (0#usize).val := by
  refine ⟨?_, ?_, ?_, ?_, ?_⟩ <;> simp only [Std.Array.repeat_val] <;>
    first | exact LeAll_replicate _ _ _ (by simp) | simp

-- @owner engB @status DONE (statement corrected: CONTRACT_ISSUES engB-7) (post strengthened: only the word ring changes)
-- [engB] loop callees: b_byte_at
@[local step]
theorem b_engine_loop2_loop0_loop0_spec (input : Slice Std.U8) (mf : slot.BMf) (x) (wfill top : Std.Usize)
    (htop : top.val ≤ input.length) (hn26 : input.length < 67108864) :
    slot.b_engine_loop2_loop0_loop0 input mf x wfill top ⦃ fun r =>
      r.1.head = mf.head ∧ r.1.head3 = mf.head3 ∧ r.1.tree = mf.tree ∧ r.1.pn = mf.pn ∧ r.1.hl = mf.hl ⦄ := by
  rw [slot.b_engine_loop2_loop0_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, wfill_) => top.val - wfill_.val)
    (inv := fun (mf_, _, _) => mf_.head = mf.head ∧ mf_.head3 = mf.head3 ∧ mf_.tree = mf.tree ∧
      mf_.pn = mf.pn ∧ mf_.hl = mf.hl)
  · rintro ⟨mf_, x_, wfill_⟩ ⟨h1, h2, h3, h4, h5⟩
    simp only [slot.b_engine_loop2_loop0_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals first
      | exact ⟨h1, h2, h3, h4, h5⟩
      | (refine ⟨⟨h1, h2, h3, h4, h5⟩, ?_⟩; scalar_tac)
      | scalar_tac
  · exact ⟨rfl, rfl, rfl, rfl, rfl⟩

-- @owner engB @status DONE @note measure nr - q; inv rn0 + (q - q0) = rn, rn <= rs.length
-- [engB] loop callees: b_put
@[local step]
theorem b_engine_loop2_loop0_loop1_spec (rv) (rs : alloc.vec.Vec Std.U32) (rn nr q : Std.Usize)
    (hrn : rn.val + nr.val < 4294967295) (hrs : rn.val ≤ rs.length) :
    slot.b_engine_loop2_loop0_loop1 rv rs rn nr q ⦃ fun r => r.2.val ≤ rn.val + nr.val ∧ r.2.val ≤ r.1.length ⦄ := by
  rw [slot.b_engine_loop2_loop0_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, q') => nr.val - q'.val)
    (inv := fun (rs', rn', q') => rn'.val + q.val = rn.val + q'.val ∧ q.val ≤ q'.val ∧
      q'.val ≤ max q.val nr.val ∧ rn'.val ≤ rs'.length)
  · rintro ⟨rs', rn', q'⟩ ⟨h1, h2, h3, h4⟩
    simp only [slot.b_engine_loop2_loop0_loop1.body]
    step*
    all_goals scalar_tac
  · exact ⟨rfl, le_refl _, by scalar_tac, hrs⟩

/-- The exact-3 candidate of a position (`b_engine`): the latest earlier position with the same
    3-byte hash, taken when its distance is within `h3dist`, gives at most one record. -/
theorem engB_h3_blk (w : Std.Array Std.U64 32768#usize) (rv : Std.Array Std.U32 32#usize)
    (wi wp : Std.U64) (i p3 d3 h3dist scap : Std.Usize) (hd : 0 < p3.val → d3.val ≤ i.val) :
    (if p3 > 0#usize then
        if d3 ≥ 1#usize then
          if d3 ≤ h3dist then
            if scap ≥ 3#usize then do
              let c ← i - d3
              let i14 ← c % slot.B_WR
              let i15 ← w.index_usize i14
              let x3 ← lift (i15 ^^^ wi)
              let i16 ← x3 >>> 40#i32
              if i16 = 0#u64 then do
                  let i17 ← x3 >>> 32#i32
                  if (i17 != 0#u64) = true then do
                      let flag ←
                        if c ≥ 1#usize then do
                            let i18 ← c - 1#usize
                            let i19 ← i18 % slot.B_WR
                            let i20 ← w.index_usize i19
                            let i21 ← i20 >>> 56#i32
                            if i21 = wp then slot.B_FULL else ok 0#u32
                          else ok 0#u32
                      let ((nr1, nf1), rv2) ← slot.b_add_record rv 0#usize 0#usize 3#usize d3 flag
                      ok (rv2, nr1, nf1, 3#usize)
                    else ok (rv, 0#usize, 0#usize, 2#usize)
                else ok (rv, 0#usize, 0#usize, 2#usize)
            else ok (rv, 0#usize, 0#usize, 2#usize)
          else ok (rv, 0#usize, 0#usize, 2#usize)
        else ok (rv, 0#usize, 0#usize, 2#usize)
      else ok (rv, 0#usize, 0#usize, 2#usize)) ⦃
      fun (x : Std.Array Std.U32 32#usize × Std.Usize × Std.Usize × Std.Usize) =>
        x.2.1.val ≤ slot.B_RB.val ⦄ := by
  repeat' (split <;> step*)
  all_goals scalar_tac

/-- What one iteration of `b_engine`'s position loop must establish (the form
    `loop.spec_decr_nat` gives for its invariant and measure). -/
def engB_PPost (b i : Nat)
    (r : ControlFlow (slot.BMf × Std.Array Std.U32 32#usize × alloc.vec.Vec Std.U32 × Std.U64 × Std.Usize ×
      Std.Usize × Std.Usize) (slot.BMf × Std.Array Std.U32 32#usize × alloc.vec.Vec Std.U32 × Std.U64 ×
      Std.Usize × Std.Usize)) : Prop :=
  match r with
  | .done y => engB_MfInv y.1 b ∧ y.2.2.2.2.2.val ≤ 33 * b ∧ y.2.2.2.2.2.val ≤ y.2.2.1.length
  | .cont x' => x'.2.2.2.2.2.2.val ≤ b ∧ x'.2.2.2.2.2.1.val ≤ 33 * x'.2.2.2.2.2.2.val ∧
      x'.2.2.2.2.2.1.val ≤ x'.2.2.1.length ∧ engB_MfInv x'.1 x'.2.2.2.2.2.2.val ∧
      b - x'.2.2.2.2.2.2.val < b - i

theorem engB_arr_index_le_f {n : Std.Usize} (a : Std.Array Std.U32 n) (j : Std.Usize) (B : Nat)
    (h : LeAll a.val B) (hj : j.val < a.length) :
    a.index_usize j ⦃ fun x => x = a.val[j.val] ∧ x.val ≤ B ⦄ := engB_arr_index_le a j B h hj

attribute [local step] engB_arr_index_le_f in
/-- The rest of one position of `b_engine`'s position loop: insert the position into its 4-byte
    hash bucket's tree (`b_descend`), then append its records and their count to the stream. -/
theorem engB_pos_tail (depth : Std.Usize) (mf1 : slot.BMf) (a1 : Std.Array Std.U32 16384#usize)
    (rv1 : Std.Array Std.U32 32#usize) (rs : alloc.vec.Vec Std.U32) (x1 : Std.U64) (wfill1 : Std.Usize)
    (wi wp : Std.U64) (i i12 cap scap nr nf best rn b : Std.Usize)
    (hib : i.val < b.val) (hb : b.val < 67108864) (hi12 : i12.val = i.val + 1) (hcap : cap.val ≤ 258)
    (hH : LeAll mf1.head.val i.val) (hH3 : LeAll a1.val (i.val + 1)) (hT : LeAll mf1.tree.val i.val)
    (hP : LeAll mf1.pn.val i.val) (hL : mf1.hl.val ≤ 2 ^ 30) (hnr : nr.val ≤ slot.B_RB.val)
    (hdepth : depth.val ≤ 1048576) (hrn : rn.val ≤ 33 * i.val) (hrs : rn.val ≤ rs.length) :
    (do
      let i14 ← wi >>> 32#i32
      let i15 ← lift (UScalar.cast UScalarTy.U32 i14)
      let i16 ← lift (core.num.U32.wrapping_mul i15 2654435761#u32)
      let i17 ← 32#u32 - slot.B_HBITS
      let i18 ← i16 >>> i17
      let i19 ← lift (UScalar.cast UScalarTy.Usize i18)
      let h ← i19 % slot.B_HSIZE
      let i20 ← mf1.head.index_usize h
      let first ← lift (UScalar.cast UScalarTy.Usize i20)
      let i21 ← lift (UScalar.cast UScalarTy.U32 i12)
      let a2 ← mf1.head.update h i21
      let ((nr1, _, _, _), mf2, rv2) ←
        slot.b_descend
            { head := a2, head3 := a1, tree := mf1.tree, w := mf1.w, pn := mf1.pn, pf := mf1.pf,
              plen := mf1.plen, hn := mf1.hn, hl := mf1.hl }
            first i cap scap best wp rv1 nr nf depth
      let (rs1, rn1) ← slot.b_engine_loop2_loop0_loop1 rv2 rs rn nr1 0#usize
      let i22 ← lift (UScalar.cast UScalarTy.U32 nr1)
      let (rn2, rs2) ← slot.b_put rs1 rn1 i22
      let i23 ← i + 1#usize
      ok (cont (mf2, rv2, rs2, x1, wfill1, rn2, i23))) ⦃ engB_PPost b.val i.val ⦄ := by
  have hi21 : (UScalar.cast UScalarTy.U32 i12).val = i.val + 1 := by
    rw [UScalar.cast_val_mod_pow_of_inBounds_eq _ _ (by scalar_tac)]; scalar_tac
  step*
  rename Std.Usize × Std.Usize × Std.Usize × Std.Usize => xr
  obtain ⟨nr1, x2, x3, x4⟩ := xr
  have hnr1 : nr1.val ≤ slot.B_RB.val := by assumption
  try simp only
  step*
  simp only [engB_PPost]
  refine ⟨by scalar_tac, by scalar_tac, by scalar_tac, ⟨?_, ?_, ?_, ?_, ?_⟩, by scalar_tac⟩
  · rw [‹mf2.head = a2›, a2_post, Std.Array.set_val_eq]
    exact LeAll_set (LeAll_mono hH (by scalar_tac)) _ _ (by scalar_tac)
  · rw [‹mf2.head3 = a1›]; exact LeAll_mono hH3 (by scalar_tac)
  · exact LeAll_mono ‹LeAll mf2.tree.val i.val› (by scalar_tac)
  · exact LeAll_mono ‹LeAll mf2.pn.val i.val› (by scalar_tac)
  · exact ‹mf2.hl.val ≤ 2 ^ 30›

-- @owner engB @status DONE (statement corrected: CONTRACT_ISSUES engB-7) @note positions of one segment; inv: rn <= rs.length, rn <= 33 * i (records per position <= B_RB + 1), BMf invariants of b_descend (hl <= 258, tree/head/head3 entries <= i + 1); `c = i - d3` needs head3 entries <= i or B7b. Final statement = these as preconditions + posts
-- [engB] loop callees: b_add_record b_descend b_engine_loop2_loop0_loop0 b_engine_loop2_loop0_loop1 b_put
set_option maxHeartbeats 4000000 in
attribute [local step] engB_arr_index_le_e in
@[local step]
theorem b_engine_loop2_loop0_spec (input : Slice Std.U8) (depth h3dist n : Std.Usize) (mf : slot.BMf) (rv)
    (rs : alloc.vec.Vec Std.U32) (x wfill) (rn a b i : Std.Usize)
    (hn : n.val = input.length) (hn26 : n.val < 67108864) (hdepth : depth.val ≤ 1048576)
    (hb : b.val ≤ n.val) (hib : i.val ≤ b.val) (hrn : rn.val ≤ 33 * i.val) (hrs : rn.val ≤ rs.length)
    (hmf : engB_MfInv mf i.val) :
    slot.b_engine_loop2_loop0 input depth h3dist n mf rv rs x wfill rn a b i ⦃ fun r =>
      engB_MfInv r.1 b.val ∧ r.2.2.2.2.2.val ≤ 33 * b.val ∧ r.2.2.2.2.2.val ≤ r.2.2.1.length ⦄ := by
  rw [slot.b_engine_loop2_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, _, _, i') => b.val - i'.val)
    (inv := fun (mf', _, rs', _, _, rn', i') => i'.val ≤ b.val ∧ rn'.val ≤ 33 * i'.val ∧
      rn'.val ≤ rs'.length ∧ engB_MfInv mf' i'.val)
  · rintro ⟨mf', rv', rs', x', wfill', rn', i'⟩ ⟨hib', hrn', hrs', hH, hH3, hT, hP, hL⟩
    simp only [slot.b_engine_loop2_loop0.body]
    by_cases hlt : i' < b
    · rw [if_pos hlt]
      have hlt' : i'.val < b.val := hlt
      step*
      apply WP.spec_bind (Pₘ := fun (top : Std.Usize) => top.val ≤ n.val)
      · split <;> simp <;> scalar_tac
      intro top htop
      step*
      · -- n - i ≥ 4
        simp only [← mf1_post1, ← mf1_post2, ← mf1_post3, ← mf1_post4, ← mf1_post5] at hH hH3 hT hP hL
        apply WP.spec_bind (Pₘ := fun (cap : Std.Usize) => cap.val ≤ 258)
        · split <;> simp <;> scalar_tac
        intro cap hcap
        step*
        apply WP.spec_bind (Pₘ := fun (_ : Std.Usize) => True)
        · split <;> simp
        intro scap _
        step*
        apply WP.spec_bind (Pₘ := fun (_ : Std.U64) => True)
        · split
          · step*
          · simp
        intro wp _
        step*
        have hp3 : p3.val = i11.val := by
          rw [p3_post]; exact UScalar.cast_val_mod_pow_of_inBounds_eq _ _ (by scalar_tac)
        have hd3 : d3.val = i'.val + 1 - p3.val := by
          rw [d3_post, engB_wsub_val i12 p3 (by omega)]; omega
        have hi13 : i13.val = i'.val + 1 := by
          rw [i13_post, UScalar.cast_val_mod_pow_of_inBounds_eq _ _ (by scalar_tac)]; omega
        have hH3' : LeAll a1.val (i'.val + 1) := by
          rw [a1_post, Std.Array.set_val_eq]
          exact LeAll_set (LeAll_mono hH3 (by omega)) _ _ (by omega)
        apply WP.spec_bind (engB_h3_blk mf1.w rv' wi wp i' p3 d3 h3dist scap (fun _ => by omega))
        rintro ⟨rv1, nr, nf, best⟩ hnr
        simp only [Std.uncurry_apply_pair]
        refine WP.spec_mono (engB_pos_tail depth mf1 a1 rv1 rs' x1 wfill1 wi wp i' i12 cap scap nr nf best rn' b
          hlt' (by omega) (by omega) hcap hH hH3' hT hP hL hnr hdepth hrn' hrs') ?_
        intro r hr; cases r <;> exact hr
      · -- n - i < 4: one empty record count
        refine ⟨by scalar_tac, by scalar_tac, rn1_post2, ⟨?_, ?_, ?_, ?_, ?_⟩, by scalar_tac⟩
        · rw [mf1_post1]; exact LeAll_mono hH (by scalar_tac)
        · rw [mf1_post2]; exact LeAll_mono hH3 (by scalar_tac)
        · rw [mf1_post3]; exact LeAll_mono hT (by scalar_tac)
        · rw [mf1_post4]; exact LeAll_mono hP (by scalar_tac)
        · rw [mf1_post5]; exact hL
    · rw [if_neg hlt]
      simp only [WP.spec_ok]
      have he : i'.val = b.val := by scalar_tac
      rw [he] at hH hH3 hT hP hrn'
      exact ⟨⟨hH, hH3, hT, hP, hL⟩, hrn', hrs'⟩
  · exact ⟨hib, hrn, hrs, hmf⟩

-- @owner engB @status DONE (statement corrected: CONTRACT_ISSUES engB-7) @note mode-1 passes: a + m <= n, m < cc.length, rn <= rs.length as preconditions; post cc.length kept
-- [engB] loop callees: b_dp_seg b_tally_seg
@[local step]
theorem b_engine_loop2_loop1_spec (input : Slice Std.U8) (bpasses cuts : Std.Usize)
    (bf bs rs : alloc.vec.Vec Std.U32) (cc : alloc.vec.Vec Std.U64) (rn a m p : Std.Usize)
    (ham : a.val + m.val ≤ input.length) (hm : m.val < cc.length) (hm26 : m.val < 67108864)
    (hrn : rn.val ≤ rs.length) (hcuts : cuts.val ≤ 65536) :
    slot.b_engine_loop2_loop1 input bpasses cuts bf bs rs cc rn a m p ⦃ fun r =>
      bf.length ≤ r.1.length ∧ r.2.2.length = cc.length ⦄ := by
  rw [slot.b_engine_loop2_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, p') => bpasses.val - p'.val)
    (inv := fun (bf', _, cc', _) => bf.length ≤ bf'.length ∧ cc'.length = cc.length)
  · rintro ⟨bf', bs', cc', p'⟩ ⟨h1, h2⟩
    simp only [slot.b_engine_loop2_loop1.body]
    step*
    all_goals scalar_tac
  · exact ⟨le_refl _, rfl⟩

-- @owner engB @status DONE
-- [engB] loop callees: -
@[local step]
theorem b_engine_loop2_loop2_spec (freq) (bf : alloc.vec.Vec Std.U32) (k2) (hbf : slot.B_FSZ.val ≤ bf.length) :
    slot.b_engine_loop2_loop2 freq bf k2 ⦃ fun _ => True ⦄ := by
  rw [slot.b_engine_loop2_loop2]
  apply Std.loop.spec_decr_nat
    (measure := fun (freq_, k2_) => slot.B_FSZ.val - k2_.val)
    (inv := fun _ => True)
  · rintro ⟨freq_, k2_⟩ _
    simp only [slot.b_engine_loop2_loop2.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial

-- @owner engB @status DONE (B6 not needed: b_self_cost post, engB-3) @note statement corrected: CONTRACT_ISSUES engB-7
-- [engB] loop callees: b_dp_seg b_engine_loop2_loop0 b_engine_loop2_loop1 b_engine_loop2_loop2 b_extra_bits b_plan_seg b_self_cost b_static_freq b_tally_seg
@[local step]
theorem b_engine_loop2_spec (input : Slice Std.U8) (plan) (depth h3dist mode bpasses cuts n : Std.Usize)
    (mf : slot.BMf) (rv freq) (bf bs : alloc.vec.Vec Std.U32) (keep) (rs : alloc.vec.Vec Std.U32)
    (cc : alloc.vec.Vec Std.U64) (x wfill) (rn a : Std.Usize)
    (hn : n.val = input.length) (hn26 : n.val < 67108864) (hcuts : cuts.val ≤ 65536)
    (hdepth : depth.val ≤ 1048576) (ha : a.val ≤ n.val) (hrn : rn.val ≤ 33 * a.val) (hrs : rn.val ≤ rs.length)
    (hmf : engB_MfInv mf a.val) (hcc : n.val < cc.length ∨ slot.B_SEG.val < cc.length)
    (hbf : 0 < a.val → slot.B_FSZ.val ≤ bf.length) :
    slot.b_engine_loop2 input plan depth h3dist mode bpasses cuts n mf rv freq bf bs keep rs cc x wfill rn a
      ⦃ fun r => r.2.2.2.2.2.val ≤ r.2.2.2.1.length ∧ r.2.2.2.2.1.length = cc.length ⦄ := by
  rw [slot.b_engine_loop2]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, _, _, _, _, _, _, _, a') => n.val - a'.val)
    (inv := fun (_, mf', _, _, bf', _, rs', cc', _, _, rn', a') => a'.val ≤ n.val ∧
      rn'.val ≤ 33 * a'.val ∧ rn'.val ≤ rs'.length ∧ engB_MfInv mf' a'.val ∧ cc'.length = cc.length ∧
      (0 < a'.val → slot.B_FSZ.val ≤ bf'.length))
  · rintro ⟨plan', mf', rv', freq', bf', bs', rs', cc', x', wfill', rn', a'⟩ ⟨ha', hrn', hrs', hmf', hcc', hbf'⟩
    simp only [slot.b_engine_loop2.body]
    split
    · step*
      apply WP.spec_bind (Pₘ := fun (m : Std.Usize) =>
        0 < m.val ∧ m.val ≤ n.val - a'.val ∧ m.val ≤ slot.B_SEG.val)
      · split <;> simp <;> scalar_tac
      rintro m ⟨hm0, hm1, hm2⟩
      have hmc : m.val < cc'.length := by scalar_tac
      step*
      apply WP.spec_bind (Pₘ := fun (rn1 : Std.Usize) => rn1.val ≤ rn'.val)
      · split <;> simp <;> scalar_tac
      intro rn1 hrn1
      step*
      apply WP.spec_bind (Pₘ := fun (bf1 : alloc.vec.Vec Std.U32) => slot.B_FSZ.val ≤ bf1.length)
      · split
        · step*
        · simp only [WP.spec_ok]; scalar_tac
      intro bf1 hbf1
      step*
      apply WP.spec_bind (Pₘ := fun (bs1 : alloc.vec.Vec Std.U32) => 0 < bs1.length)
      · split
        · step*
        · simp only [WP.spec_ok]; scalar_tac
      intro bs1 hbs1
      step*
      · -- mode 1: block passes on this segment
        exact ⟨by scalar_tac, mf1_post2, mf1_post3, mf1_post1, by scalar_tac, fun _ => by scalar_tac,
          by scalar_tac⟩
      · -- modes 0 and 2: refine the segment when its parse costs more than its own entropy
        apply WP.spec_bind (Pₘ := fun (x : alloc.vec.Vec Std.U32 × alloc.vec.Vec Std.U32 ×
            alloc.vec.Vec Std.U64) => slot.B_FSZ.val ≤ x.1.length ∧ x.2.2.length = cc.length)
        · split
          · step*
            all_goals scalar_tac
          · split
            · step*
              all_goals scalar_tac
            · simp only [WP.spec_ok]; scalar_tac
        rintro ⟨bf3, bs4, cc2⟩ ⟨hbf3, hcc2⟩
        step*
        exact ⟨by scalar_tac, mf1_post2, mf1_post3, mf1_post1, by scalar_tac, fun _ => hbf3,
          by scalar_tac⟩
    · simp only [WP.spec_ok]
      exact ⟨hrs', hcc'⟩
  · exact ⟨ha, hrn, hrs, hmf, rfl, hbf⟩

-- @owner engB @status DONE (statement corrected: CONTRACT_ISSUES engB-7) @note keep-mode passes: n < cc.length, rn <= rs.length, nb <= 2^20 as preconditions
-- [engB] loop callees: b_dp_seg b_tally_seg
@[local step]
theorem b_engine_loop3_spec (input : Slice Std.U8) (bpasses cuts n : Std.Usize)
    (bf bs rs : alloc.vec.Vec Std.U32) (cc : alloc.vec.Vec Std.U64) (rn nb p : Std.Usize)
    (hn : n.val = input.length) (hn26 : n.val < 67108864) (hcc : n.val < cc.length)
    (hrn : rn.val ≤ rs.length) (hnb : nb.val ≤ 1048576) (hcuts : cuts.val ≤ 65536) :
    slot.b_engine_loop3 input bpasses cuts n bf bs rs cc rn nb p ⦃ fun r => r.length = cc.length ⦄ := by
  rw [slot.b_engine_loop3]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, p') => bpasses.val - p'.val)
    (inv := fun (_, _, cc', nb', _) => cc'.length = cc.length ∧ nb'.val ≤ 1048576)
  · rintro ⟨bf', bs', cc', nb', p'⟩ ⟨h1, h2⟩
    simp only [slot.b_engine_loop3.body]
    step*
    repeat' (split <;> step*)
    all_goals try (obtain ⟨x1, x2, x3⟩ := x; simp only at x_post1 x_post2 ⊢; step*)
    all_goals scalar_tac
  · exact ⟨rfl, hnb⟩

-- @owner engB @status DONE (proved; uses B_NOHINT_spec, BLOCKED R2) @export @note EXPORTED (called by plan_cfg), statement verbatim
-- [engB] fn callees: b_engine_loop0 b_engine_loop1 b_engine_loop2 b_engine_loop3 b_plan_seg b_tally_plan
@[local step]
theorem b_engine_spec (input : Slice Std.U8) (plan) (depth h3dist mode bpasses cuts : Std.Usize)
    (hn : input.length < 67108864) (h1 : depth.val ≤ 65536) (h2 : h3dist.val ≤ 65536)
    (h3 : mode.val ≤ 65536) (h4 : bpasses.val ≤ 65536) (h5 : cuts.val ≤ 65536) :
    slot.b_engine input plan depth h3dist mode bpasses cuts ⦃ fun _ => True ⦄ := by
  rw [slot.b_engine]
  step*
  apply WP.spec_bind (Pₘ := fun (_ : Std.Usize) => True)
  · split
    · step*
    · simp only [WP.spec_ok]
  intro keep _
  apply WP.spec_bind (Pₘ := fun (segcap : Std.Usize) =>
    (segcap.val = input.length ∨ segcap.val = slot.B_SEG.val) ∧ (keep = 1#usize → segcap.val = input.length))
  · split
    · simp only [WP.spec_ok]; exact ⟨Or.inl (by simp), fun _ => by simp⟩
    · split
      · simp only [WP.spec_ok]; exact ⟨Or.inl (by simp), fun _ => by simp⟩
      · simp only [WP.spec_ok]; exact ⟨Or.inr (by simp), fun h => absurd h ‹_›⟩
  rintro segcap ⟨hs1, hs2⟩
  step*
  all_goals first
    | exact engB_MfInv_init _ _ _ _
    | scalar_tac

/-! PROTOTYPE: sec_engC.lean for the snapshot + Rust edit C1 (/root/66/work/pk/s/engC/proto/parse.rs).
Identical to /root/66/work/pk/s/sec_engC.lean except that `c_rep_rates_loop_spec` is proved here.
Check: /root/66/work/pk/s/engC/tp.sh (workspace engC/dev_proto, extraction of proto/parse.rs). -/

/-! # sec_engC (owner: engC) -- engine C (DNA / binary): totality only.

Exported: `c_engine_spec` (frozen statement, unchanged). Every other lemma is internal to this file;
statements that differ from CONTRACT.md section 8 are marked `@changed` and explained in
/root/66/work/pk/s/CONTRACT_ISSUES.md (engC part). The one unproved lemma is `c_rep_rates_loop_spec`,
BLOCKED(C1): the snapshot's `r4 * 65536` overflows a 32-bit `usize`. The same statement is proved on
snapshot + C1 in /root/66/work/pk/s/engC/proto/sec_engC_proto.lean (this section with that proof).

How the proofs work (see also /root/66/work/pk/s/engC/NOTES.md):
* The recipe (`step*; repeat' (split <;> step*); all_goals scalar_tac`) with an invariant where needed.
* Section step rules (below): reads of the extra-bits tables carry their bound; `wrapping_add`
  without wrap-around is `+`; a `u64` product with a `u32`-sized left factor and a `u32` product
  with a factor `≤ 256` get a linear bound (`scalar_tac` bounds a product by the factors' type
  bounds, which is too weak); a `u64` quotient `x / y` is `≤ 65536` when `x ≤ 65536 * y`; `usize`/`u64`
  casts keep (small) values; `Vec.push` states the new length. All posts include the generic ones.
* Counters: `LeAll` invariants (checked `+= 1` on `lf`, `lb`, radix counts); the block loop of
  `c_restat` carries a division-free block count (`|models| * 8192 < 544 * (n + 8192)`, ...).
* Many bind-`if`s (`c_dp_pass_loop0`, `c_find_dna_loop1`, `c_find_bin_loop`, `c_engine`): one
  `WP.spec_bind` per `if` with the fact the rest needs; a tuple result that `step*` leaves as
  `uncurry f x` after a `split` is opened with `obtain ⟨..⟩ := x; simp only [Std.uncurry_apply_pair]`.
* Candidate lists grow by at most `C_KEEP + 2 ≤ 34` per position: `clist.length ≤ 34 * n < 2^32 - 1`. -/

/-! Constants: facts and Result-typed constants -/

-- @owner engC @status DONE (constant step spec)
@[local step]
theorem C_GROUP_spec : slot.C_GROUP ⦃ fun x => x.val = 2147483648 ⦄ := by
  unfold slot.C_GROUP; step*

-- @owner engC @status DONE (constant step spec)
@[local step]
theorem C_LONG_ONLY_spec : slot.C_LONG_ONLY ⦃ fun x => x.val = 536870912 ⦄ := by
  unfold slot.C_LONG_ONLY; step*

theorem C_BLOCK_bounds : 8192 ≤ slot.C_BLOCK.val ∧ slot.C_BLOCK.val ≤ 1048576 := by simp [slot.C_BLOCK]

theorem C_WS_val : slot.C_WS.val = 32768 := by simp [slot.C_WS]

theorem C_KS_val : slot.C_KS.val = 65536 := by simp [slot.C_KS]

theorem C_HS_bounds : 2 ≤ slot.C_HS.val ∧ slot.C_HS.val ≤ 65536 := by simp [slot.C_HS]

theorem C_MS_val : slot.C_MS.val = 544 := by simp [slot.C_MS]

theorem C_PMASK_lt : slot.C_PMASK.val < 2 ^ 27 := by simp [slot.C_PMASK]

theorem C_KEEP_le : slot.C_KEEP.val ≤ 32 := by simp [slot.C_KEEP]

theorem C_SCALE_le : slot.C_SCALE.val ≤ 256 := by simp [slot.C_SCALE]

theorem C_UNUSED_LIT_le : slot.C_UNUSED_LIT.val ≤ 65536 := by simp [slot.C_UNUSED_LIT]

theorem C_UNUSED_LEN_le : slot.C_UNUSED_LEN.val ≤ 65536 := by simp [slot.C_UNUSED_LEN]

theorem C_UNUSED_DIST_le : slot.C_UNUSED_DIST.val ≤ 65536 := by simp [slot.C_UNUSED_DIST]

theorem C_UNUSED_LEN_W_le : slot.C_UNUSED_LEN_W.val ≤ 65536 := by simp [slot.C_UNUSED_LEN_W]

theorem C_UNUSED_DIST_W_le : slot.C_UNUSED_DIST_W.val ≤ 65536 := by simp [slot.C_UNUSED_DIST_W]

theorem C_TAX_W_le : slot.C_TAX_W.val ≤ 65536 := by simp [slot.C_TAX_W]

theorem C_TAX_C4_le : slot.C_TAX_C4.val ≤ 65536 := by simp [slot.C_TAX_C4]

theorem C_TAX_BT_le : slot.C_TAX_BT.val ≤ 65536 := by simp [slot.C_TAX_BT]

theorem C_TOKPEN_le : slot.C_TOKPEN.val ≤ 65536 := by simp [slot.C_TOKPEN]

theorem C_TOKPEN_W_le : slot.C_TOKPEN_W.val ≤ 65536 := by simp [slot.C_TOKPEN_W]

theorem C_TOKPEN_C4_le : slot.C_TOKPEN_C4.val ≤ 65536 := by simp [slot.C_TOKPEN_C4]

theorem C_TOKPEN_BT_le : slot.C_TOKPEN_BT.val ≤ 65536 := by simp [slot.C_TOKPEN_BT]

theorem C_CHAIN4_RATIO_le : slot.C_CHAIN4_RATIO.val ≤ 65535 := by simp [slot.C_CHAIN4_RATIO]

theorem C_STOP_DIV_pos : 0 < slot.C_STOP_DIV.val := by simp [slot.C_STOP_DIV]

theorem C_UP_MIN_ge : 1 ≤ slot.C_UP_MIN.val := by simp [slot.C_UP_MIN]

theorem C_REP_STEP_bounds : 1 ≤ slot.C_REP_STEP.val ∧ slot.C_REP_STEP.val ≤ 1048576 := by simp [slot.C_REP_STEP]

theorem C_REP6_MIN_le : slot.C_REP6_MIN.val ≤ 1048576 := by simp [slot.C_REP6_MIN]

theorem engC_LEXTRA_le (i : Nat) (h : i < 29) : (slot.C_LEXTRA.val[i]!).val ≤ 5 := by
  unfold slot.C_LEXTRA; simp only [Array.make]; revert i; decide

theorem engC_DEXTRA_le (i : Nat) (h : i < 30) : (slot.C_DEXTRA.val[i]!).val ≤ 13 := by
  unfold slot.C_DEXTRA; simp only [Array.make]; revert i; decide

/-! Step rules of this section -/

/-- Reads of the extra-bits tables come with their bound (`step*` prefers this over the generic
    array read). -/
@[local step]
theorem C_LEXTRA_index_spec (i : Std.Usize) (h : i.val < 29) :
    Array.index_usize slot.C_LEXTRA i ⦃ fun x => x.val ≤ 5 ⦄ := by
  have := engC_LEXTRA_le i.val h
  step*
  subst x_post
  rw [List.getElem!_eq_getElem?_getD, List.getElem?_eq_getElem (by scalar_tac)] at this
  exact this

@[local step]
theorem C_DEXTRA_index_spec (i : Std.Usize) (h : i.val < 30) :
    Array.index_usize slot.C_DEXTRA i ⦃ fun x => x.val ≤ 13 ⦄ := by
  have := engC_DEXTRA_le i.val h
  step*
  subst x_post
  rw [List.getElem!_eq_getElem?_getD, List.getElem?_eq_getElem (by scalar_tac)] at this
  exact this

/-- `wrapping_add` without wrap-around is `+` (`step*` prefers this over `lift_spec`; the post keeps
    `lift_spec`'s equation, so later sections lose nothing). -/
@[local step]
theorem engC_wadd_usize_spec (x y : Std.Usize) :
    lift (core.num.Usize.wrapping_add x y) ⦃ fun z => z = core.num.Usize.wrapping_add x y ∧
      (x.val + y.val ≤ Usize.max → z.val = x.val + y.val) ⦄ := by
  simp only [lift, WP.spec_ok, true_and]
  intro h
  rw [core.num.Usize.wrapping_add_val_eq, UScalar.size_UScalarTyUsize]
  apply Nat.mod_eq_of_lt
  scalar_tac

@[local step]
theorem engC_wadd_u32_spec (x y : Std.U32) :
    lift (core.num.U32.wrapping_add x y) ⦃ fun z => z = core.num.U32.wrapping_add x y ∧
      (x.val + y.val ≤ U32.max → z.val = x.val + y.val) ⦄ := by
  simp only [lift, WP.spec_ok, true_and]
  intro h
  rw [core.num.U32.wrapping_add_val_eq]
  apply Nat.mod_eq_of_lt
  scalar_tac

/-- A product with a `u32`-sized left factor: the bound is linear in the right factor.
    (`scalar_tac` picks the type bounds of the factors for a product, so a small right factor is
    lost; this post keeps it linear.) -/
@[local step]
theorem engC_mul_u64_spec (x y : Std.U64)
    (h : (x.val ≤ 4294967295 ∧ y.val ≤ 4294967295) ∨ x.val * y.val ≤ U64.max) :
    (x * y) ⦃ fun z => z.val = x.val * y.val ∧ (x.val ≤ 4294967295 → z.val ≤ 4294967295 * y.val) ⦄ := by
  have h' : x.val * y.val ≤ U64.max := by
    rcases h with ⟨hx, hy⟩ | h
    · have := Nat.mul_le_mul hx hy
      scalar_tac
    · exact h
  step*
  refine ⟨z_post, fun hx => ?_⟩
  rw [z_post]
  exact Nat.mul_le_mul_right _ hx

/-- A `u32` product with a factor `≤ 256` (a cost scale): the bound stays linear. -/
@[local step]
theorem engC_mul_u32_spec (x y : Std.U32)
    (h : (x.val ≤ 16777215 ∧ y.val ≤ 256) ∨ x.val * y.val ≤ U32.max) :
    (x * y) ⦃ fun z => z.val = x.val * y.val ∧ (y.val ≤ 256 → z.val ≤ 256 * x.val) ⦄ := by
  have h' : x.val * y.val ≤ U32.max := by
    rcases h with ⟨hx, hy⟩ | h
    · have := Nat.mul_le_mul hx hy
      scalar_tac
    · exact h
  step*
  refine ⟨z_post, fun hy => ?_⟩
  rw [z_post, Nat.mul_comm]
  exact Nat.mul_le_mul_right _ hy

/-- A `u64` quotient is at most `65536` when the dividend is at most `65536` times the divisor
    (`scalar_tac` does not reason about a division by a variable). -/
@[local step]
theorem engC_div_u64_spec (x y : Std.U64) (h : y.val ≠ 0) :
    (x / y) ⦃ fun z => z.val = x.val / y.val ∧ (x.val ≤ 65536 * y.val → z.val ≤ 65536) ⦄ := by
  obtain ⟨z, hz, hv⟩ := UScalar.div_spec x h
  rw [hz]
  simp only [WP.spec_ok]
  refine ⟨hv, fun hx => ?_⟩
  rw [hv]
  exact Nat.div_le_of_le_mul (by rw [Nat.mul_comm]; exact hx)

/-- A `usize` cast to `u64` keeps its value. -/
@[local step]
theorem engC_cast_usize_u64_spec (x : Std.Usize) :
    lift (UScalar.cast .U64 x) ⦃ fun y => y = UScalar.cast .U64 x ∧ y.val = x.val ⦄ := by
  simp only [lift, WP.spec_ok, true_and]
  apply UScalar.cast_val_mod_pow_of_inBounds_eq
  have := x.hBounds
  have : 2 ^ UScalarTy.Usize.numBits ≤ 2 ^ UScalarTy.U64.numBits := by
    apply Nat.pow_le_pow_right (by decide)
    simp only [UScalarTy.numBits]
    cases System.Platform.numBits_eq <;> simp [*]
  omega

/-- A `u64` below `2^32` cast to `usize` keeps its value. -/
@[local step]
theorem engC_cast_u64_usize_spec (x : Std.U64) :
    lift (UScalar.cast .Usize x) ⦃ fun y => y = UScalar.cast .Usize x ∧ (x.val ≤ 4294967295 → y.val = x.val) ⦄ := by
  simp only [lift, WP.spec_ok, true_and]
  intro h
  apply UScalar.cast_val_mod_pow_of_inBounds_eq
  have : 2 ^ 32 ≤ 2 ^ UScalarTy.Usize.numBits := by
    apply Nat.pow_le_pow_right (by decide)
    simp only [UScalarTy.numBits]
    exact numBits_ge
  omega

/-- `Vec.push` with its length (the list post `v1.val = v.val ++ [x]` alone is not what `scalar_tac` needs). -/
@[local step]
theorem engC_push_spec {α : Type} (v : alloc.vec.Vec α) (x : α) (h : v.length < Usize.max) :
    alloc.vec.Vec.push v x ⦃ fun v1 => v1.val = v.val ++ [x] ∧ v1.length = v.length + 1 ⦄ := by
  step*
  exact ⟨v1_post, by simp [v1_post]⟩

theorem engC_LeAll_repeat {ty : UScalarTy} (n : Std.Usize) (x : UScalar ty) (B : Nat) (h : x.val ≤ B) :
    LeAll (Array.repeat n x).val B := by
  simp only [Array.repeat]
  exact LeAll_replicate _ _ _ h

/-- `Vec::with_capacity` is an empty vector. -/
theorem engC_with_capacity_length {α : Type} (n : Std.Usize) : (alloc.vec.Vec.with_capacity α n).length = 0 := rfl

/-- `if` as a spec rule (cheaper than `split` on a large program term). -/
theorem engC_ite_spec {α : Type} {c : Prop} [Decidable c] {A B : Result α} {P : α → Prop}
    (hA : c → A ⦃ P ⦄) (hB : ¬c → B ⦃ P ⦄) : (if c then A else B) ⦃ P ⦄ := by
  by_cases h : c
  · rw [if_pos h]; exact hA h
  · rw [if_neg h]; exact hB h

/-- A bind-`if` as a spec rule (the continuation is proved once per branch, as with `split`). -/
theorem engC_bind_ite_spec {α β : Type} {c : Prop} [Decidable c] {A B : Result α} {k : α → Result β}
    {P : β → Prop} (hA : c → (A >>= k) ⦃ P ⦄) (hB : ¬c → (B >>= k) ⦃ P ⦄) :
    ((if c then A else B) >>= k) ⦃ P ⦄ := by
  by_cases h : c
  · rw [if_pos h]; exact hA h
  · rw [if_neg h]; exact hB h

/-! Engine C, callees first -/

-- @owner engC @status DONE on snapshot + C1 (BLOCKED(C1) on the snapshot) @changed binders typed, + hr4 hr6 hpr hp, post r.1 r.2 <= 65536 (CONTRACT_ISSUES engC-B1)
/-- BLOCKED(C1) on the snapshot: `r4 * 65536 / (probes + 1)` overflows a 32-bit `usize` once `r4 ≥ 2^16`
    (inputs of 2^17+ bytes that are mostly 4-byte repeats). The statement is the one the C1 version (u64
    arithmetic) proves: /root/66/work/pk/s/engC/proto/sec_engC_proto.lean proves it on snapshot + C1
    (engC/proto/parse.rs); the proof there replaces this stub once C1 is in the Rust. -/
@[local step]
theorem c_rep_rates_loop_spec (s : Slice Std.U8) (n : Std.Usize) (head) (r4 r6 probes p : Std.Usize)
    (hn : n.val = s.length) (hn26 : n.val < 67108864) (hr4 : r4.val ≤ probes.val) (hr6 : r6.val ≤ probes.val)
    (hpr : probes.val ≤ p.val) (hp : p.val ≤ n.val + slot.C_REP_STEP.val) :
    slot.c_rep_rates_loop s n head r4 r6 probes p ⦃ fun r => r.1.val ≤ 65536 ∧ r.2.val ≤ 65536 ⦄ := by
  have f1 := C_REP_STEP_bounds
  have f2 := C_REP6_MIN_le
  have f3 := C_WS_val
  rw [slot.c_rep_rates_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, p') => n.val + slot.C_REP_STEP.val - p'.val)
    (inv := fun (_, r4', r6', pr', p') => r4'.val ≤ pr'.val ∧ r6'.val ≤ pr'.val ∧ pr'.val ≤ p'.val ∧
      p'.val ≤ n.val + slot.C_REP_STEP.val)
  · rintro ⟨h', r4', r6', pr', p'⟩ ⟨i1, i2, i3, i4⟩
    simp only [slot.c_rep_rates_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact ⟨hr4, hr6, hpr, hp⟩

-- @owner engC @status DONE (given the loop stub) @changed post r.1 r.2 <= 65536 (CONTRACT_ISSUES engC-B1)
/-- Both rates are at most 65536 (c_engine computes `C_CHAIN4_RATIO * r6`). -/
@[local step]
theorem c_rep_rates_spec (s : Slice Std.U8) (hn26 : s.length < 67108864) :
    slot.c_rep_rates s ⦃ fun r => r.1.val ≤ 65536 ∧ r.2.val ≤ 65536 ⦄ := by
  rw [slot.c_rep_rates]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

-- @owner engC @status DONE
@[local step]
theorem c_clear_span_loop_spec (plan e_nd p) :
    slot.c_clear_span_loop plan e_nd p ⦃ fun r => r.length = plan.length ⦄ := by
  rw [slot.c_clear_span_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, p') => e_nd.val - p'.val)
    (inv := fun (plan', _) => plan'.length = plan.length)
  · rintro ⟨plan', p'⟩ hinv
    simp only [slot.c_clear_span_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · rfl

-- @owner engC @status DONE
@[local step]
theorem c_clear_span_spec (plan p0 e_nd) :
    slot.c_clear_span plan p0 e_nd ⦃ fun r => r.length = plan.length ⦄ := by
  rw [slot.c_clear_span]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

-- @owner engC @status DONE
@[local step]
theorem c_dsym_spec (d) : slot.c_dsym d ⦃ fun r => r.val < 256 ⦄ := by
  rw [slot.c_dsym]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

-- @owner engC @status DONE
@[local step]
theorem c_lsym_spec (len) : slot.c_lsym len ⦃ fun r => r.val < 256 ⦄ := by
  rw [slot.c_lsym]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

-- @owner engC @status DONE
@[local step]
theorem c_path_block_loop0_spec (lf df) :
    slot.c_path_block_loop0 lf df 0#usize ⦃ fun r => LeAll r.1.val 0 ∧ LeAll r.2.val 0 ⦄ := by
  rw [slot.c_path_block_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, k) => 288 - k.val)
    (inv := fun (lf', df', k) => k.val ≤ 288 ∧
      (∀ j (hj : j < k.val) (hl : j < lf'.val.length), (lf'.val[j]).val = 0) ∧
      (∀ j (hj : j < k.val) (hl : j < df'.val.length), (df'.val[j]).val = 0))
  · rintro ⟨lf', df', k⟩ ⟨hk, hz1, hz2⟩
    simp only [slot.c_path_block_loop0.body]
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
    · have : k.val = 288 := by scalar_tac
      refine ⟨?_, ?_⟩
      · intro j hl
        have hl' : j < 288 := by simpa using hl
        rw [hz1 j (by omega) hl]
      · intro j hl
        have hl' : j < 288 := by simpa using hl
        rw [hz2 j (by omega) hl]
  · exact ⟨by simp, fun j hj => by simp at hj, fun j hj => by simp at hj⟩

-- @owner engC @status DONE @changed post p <= r.p, p <= n -> r.p <= n (CONTRACT_ISSUES engC-1)
@[local step]
theorem c_path_block_loop1_spec (s : Slice Std.U8) (choice) (lf df) (n p t : Std.Usize)
    (hn : n.val = s.length) (hlf : LeAll lf.val t.val) (hdf : LeAll df.val t.val) :
    slot.c_path_block_loop1 s choice lf df n p t ⦃ fun r => p.val ≤ r.2.2.val ∧ (p.val ≤ n.val → r.2.2.val ≤ n.val) ⦄ := by
  have hB := C_BLOCK_bounds
  rw [slot.c_path_block_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, t') => slot.C_BLOCK.val - t'.val)
    (inv := fun (lf', df', p', t') => LeAll lf'.val t'.val ∧ LeAll df'.val t'.val ∧ p.val ≤ p'.val ∧
      (p.val ≤ n.val → p'.val ≤ n.val))
  · rintro ⟨lf', df', p', t'⟩ ⟨hlf', hdf', hp1, hp2⟩
    simp only [slot.c_path_block_loop1.body]
    step*
    apply WP.spec_bind (Pₘ := fun (x : Std.Array Std.U32 288#usize × Std.Array Std.U32 288#usize × Std.Usize) =>
      LeAll x.1.val (t'.val + 1) ∧ LeAll x.2.1.val (t'.val + 1) ∧ p'.val < x.2.2.val ∧ x.2.2.val ≤ n.val)
    · split
      · step*
        · -- a match: one length and one distance counter go up (wrapping, but they cannot wrap)
          have h6 := LeAll_get hlf' i5.val (by scalar_tac)
          have h12 := LeAll_get hdf' i11.val (by scalar_tac)
          refine ⟨?_, ?_, by scalar_tac, by scalar_tac⟩
          · rw [a_post, Array.set_val_eq]; exact LeAll_set_succ hlf' _ _ (by scalar_tac)
          · rw [a1_post, Array.set_val_eq]; exact LeAll_set_succ hdf' _ _ (by scalar_tac)
        · -- the literal counter cannot overflow
          have := LeAll_get hlf' i4.val (by scalar_tac)
          scalar_tac
        · -- a literal (the match does not fit)
          have := LeAll_get hlf' i4.val (by scalar_tac)
          refine ⟨?_, LeAll_mono hdf' (by omega), by scalar_tac, by scalar_tac⟩
          rw [a_post, Array.set_val_eq]; exact LeAll_set_succ hlf' _ _ (by scalar_tac)
      · -- a literal
        step*
        · have := LeAll_get hlf' i3.val (by scalar_tac)
          scalar_tac
        · have := LeAll_get hlf' i3.val (by scalar_tac)
          refine ⟨?_, LeAll_mono hdf' (by omega), by scalar_tac, by scalar_tac⟩
          rw [a_post, Array.set_val_eq]; exact LeAll_set_succ hlf' _ _ (by scalar_tac)
    · rintro ⟨lf1, df1, p1⟩ ⟨h1, h2, h3, h4⟩
      step*
  · exact ⟨hlf, hdf, le_refl _, fun h => h⟩

-- @owner engC @status DONE @changed post + (p0 <= s.length -> r.1 <= s.length) (CONTRACT_ISSUES engC-1)
@[local step]
theorem c_path_block_spec (s choice p0 lf df) :
    slot.c_path_block s choice p0 lf df ⦃ fun r => p0.val ≤ r.1.val ∧ (p0.val ≤ s.length → r.1.val ≤ s.length) ⦄ := by
  rw [slot.c_path_block]
  step*

-- @owner engC @status DONE @changed + hi : i <= 288 (CONTRACT_ISSUES engC-2)
@[local step]
theorem c_fixed_bits_loop0_spec (lf) (bits : Std.U64) (i : Std.Usize) (hi : i.val ≤ 288)
    (hb : bits.val ≤ 3 + i.val * 2 ^ 40) :
    slot.c_fixed_bits_loop0 lf bits i ⦃ fun r => r.val ≤ 3 + 288 * 2 ^ 40 ⦄ := by
  rw [slot.c_fixed_bits_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, i') => 288 - i'.val)
    (inv := fun (bits', i') => i'.val ≤ 288 ∧ bits'.val ≤ 3 + i'.val * 2 ^ 40)
  · rintro ⟨bits', i'⟩ ⟨hi', hb'⟩
    simp only [slot.c_fixed_bits_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact ⟨hi, hb⟩

-- @owner engC @status DONE @changed + hd : d <= 30 (CONTRACT_ISSUES engC-2)
@[local step]
theorem c_fixed_bits_loop1_spec (df) (bits : Std.U64) (d : Std.Usize) (hd : d.val ≤ 30)
    (hb : bits.val ≤ 3 + 288 * 2 ^ 40 + d.val * 2 ^ 40) :
    slot.c_fixed_bits_loop1 df bits d ⦃ fun r => r.val ≤ 3 + 318 * 2 ^ 40 ⦄ := by
  rw [slot.c_fixed_bits_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, d') => 30 - d'.val)
    (inv := fun (bits', d') => d'.val ≤ 30 ∧ bits'.val ≤ 3 + 288 * 2 ^ 40 + d'.val * 2 ^ 40)
  · rintro ⟨bits', d'⟩ ⟨hd', hb'⟩
    simp only [slot.c_fixed_bits_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact ⟨hd, hb⟩

-- @owner engC @status DONE
@[local step]
theorem c_fixed_bits_spec (lf df) :
    slot.c_fixed_bits lf df ⦃ fun _ => True ⦄ := by
  rw [slot.c_fixed_bits]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

-- @owner engC @status DONE
@[local step]
theorem c_rle_run_loop0_spec (clf) (r : Std.Usize) (extra : Std.U64) (fuel : Std.Usize)
    (hx : extra.val + 7 * fuel.val ≤ 2 ^ 40) :
    slot.c_rle_run_loop0 clf r extra fuel ⦃ fun res => res.2.2.val ≤ extra.val + 7 * fuel.val ⦄ := by
  rw [slot.c_rle_run_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, f) => f.val)
    (inv := fun (_, _, e, f) => e.val + 7 * f.val ≤ extra.val + 7 * fuel.val)
  · rintro ⟨clf', r', e', f'⟩ hinv
    simp only [slot.c_rle_run_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · simp

-- @owner engC @status DONE
@[local step]
theorem c_rle_run_loop1_spec (clf) (r : Std.Usize) (extra : Std.U64) (fuel : Std.Usize)
    (hx : extra.val + 2 * fuel.val ≤ 2 ^ 40) :
    slot.c_rle_run_loop1 clf r extra fuel ⦃ fun res => res.2.2.val ≤ extra.val + 2 * fuel.val ⦄ := by
  rw [slot.c_rle_run_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, f) => f.val)
    (inv := fun (_, _, e, f) => e.val + 2 * f.val ≤ extra.val + 2 * fuel.val)
  · rintro ⟨clf', r', e', f'⟩ hinv
    simp only [slot.c_rle_run_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · simp

-- @owner engC @status DONE
@[local step]
theorem c_rle_run_spec (clf v) (r0 : Std.Usize) (hr0 : 1 ≤ r0.val ∧ r0.val ≤ 512) :
    slot.c_rle_run clf v r0 ⦃ fun r => r.1.val ≤ 7 * (r0.val + 1) ⦄ := by
  rw [slot.c_rle_run]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

-- @owner engC @status DONE @changed stated at the call (cnt = 0s, i = 0), post LeAll r 288 (CONTRACT_ISSUES engC-3)
/-- Counting sort, pass 1: each of the at most 288 keys bumps one counter. -/
@[local step]
theorem c_radix_pass_loop0_spec (sw) (k : Std.Usize) (shift : Std.U32) (hshift : shift.val < 32) :
    slot.c_radix_pass_loop0 sw k shift (Array.repeat 257#usize 0#usize) 0#usize ⦃ fun r => LeAll r.val 288 ⦄ := by
  rw [slot.c_radix_pass_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, i') => 288 - i'.val)
    (inv := fun (cnt', i') => i'.val ≤ 288 ∧ LeAll cnt'.val i'.val)
  · rintro ⟨cnt', i'⟩ ⟨hi', hc'⟩
    simp only [slot.c_radix_pass_loop0.body]
    step*
    all_goals first
      | scalar_tac
      | exact LeAll_mono hc' (by scalar_tac)
      | (refine ⟨by scalar_tac, ?_, by scalar_tac⟩
         rw [a_post, Array.set_val_eq, show i9.val = i'.val + 1 by scalar_tac]
         apply LeAll_set_succ hc'
         have := LeAll_get hc' i5.val (by scalar_tac)
         scalar_tac)
  · exact ⟨by simp, engC_LeAll_repeat _ _ _ (by simp)⟩

-- @owner engC @status DONE @changed stated at c = 1, + LeAll cnt 288, post LeAll r 74016 (CONTRACT_ISSUES engC-3)
/-- Counting sort, pass 2: prefix sums. Entries below `c` are sums of at most `c` counts
    (`≤ 288 * c`), entries from `c` on are still counts (`≤ 288`). -/
@[local step]
theorem c_radix_pass_loop1_spec (cnt) (hcnt : LeAll cnt.val 288) :
    slot.c_radix_pass_loop1 cnt 1#usize ⦃ fun r => LeAll r.val 74016 ⦄ := by
  rw [slot.c_radix_pass_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, c') => 257 - c'.val)
    (inv := fun (cnt', c') => 1 ≤ c'.val ∧ c'.val ≤ 257 ∧
      (∀ j (hj : j < cnt'.val.length), j < c'.val → (cnt'.val[j]).val ≤ 288 * c'.val) ∧
      (∀ j (hj : j < cnt'.val.length), c'.val ≤ j → (cnt'.val[j]).val ≤ 288))
  · rintro ⟨cnt', c'⟩ ⟨hc1, hc2, hlo, hhi⟩
    simp only [slot.c_radix_pass_loop1.body]
    step*
    · have hi : i.val ≤ 288 := by rw [i_post]; exact hhi _ _ (le_refl _)
      have hi2 : i2.val ≤ 288 * c'.val := by rw [i2_post]; exact hlo _ _ (by scalar_tac)
      refine ⟨by scalar_tac, by scalar_tac, ?_, ?_, by scalar_tac⟩
      · intro j hj hjc
        subst a_post
        simp only [Array.set_val_eq, List.getElem_set]
        split
        · scalar_tac
        · have hj' : j < (↑cnt' : List Std.Usize).length := by simpa using hj
          have := hlo j hj' (by scalar_tac)
          scalar_tac
      · intro j hj hjc
        subst a_post
        simp only [Array.set_val_eq, List.getElem_set]
        split
        · scalar_tac
        · exact hhi j (by simpa using hj) (by scalar_tac)
    · intro j hj
      have hj2 : j < 257 := by simpa using hj
      have := hlo j hj (by scalar_tac)
      scalar_tac
  · refine ⟨by simp, by simp, ?_, ?_⟩
    · intro j hj hj1
      have := hcnt j hj
      simp at hj1 ⊢
      omega
    · intro j hj _
      exact hcnt j hj

-- @owner engC @status DONE @changed stated at j = 0, + LeAll cnt 74016 (CONTRACT_ISSUES engC-3)
/-- Counting sort, pass 3: `cnt[b] = at + 1` (checked); every slot grows by at most one per key. -/
@[local step]
theorem c_radix_pass_loop2_spec (sw ss dw ds) (k : Std.Usize) (shift : Std.U32) (cnt) (hshift : shift.val < 32)
    (hcnt : LeAll cnt.val 74016) :
    slot.c_radix_pass_loop2 sw ss dw ds k shift cnt 0#usize ⦃ fun _ => True ⦄ := by
  rw [slot.c_radix_pass_loop2]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, j') => 288 - j'.val)
    (inv := fun (_, _, cnt', j') => j'.val ≤ 288 ∧ LeAll cnt'.val (74016 + j'.val))
  · rintro ⟨dw', ds', cnt', j'⟩ ⟨hj', hc'⟩
    simp only [slot.c_radix_pass_loop2.body]
    step*
    all_goals first
      | scalar_tac
      | (have := LeAll_get hc' i3.val (by scalar_tac)
         scalar_tac)
      | (refine ⟨by scalar_tac, ?_, by scalar_tac⟩
         rw [a2_post, Array.set_val_eq, show j1.val = j'.val + 1 by scalar_tac, ← Nat.add_assoc]
         apply LeAll_set_succ hc'
         have := LeAll_get hc' i3.val (by scalar_tac)
         scalar_tac)
  · exact ⟨by simp, by simpa using hcnt⟩

-- @owner engC @status DONE
@[local step]
theorem c_radix_pass_spec (sw ss dw ds) (k : Std.Usize) (shift : Std.U32) (hshift : shift.val < 32) :
    slot.c_radix_pass sw ss dw ds k shift ⦃ fun _ => True ⦄ := by
  rw [slot.c_radix_pass]
  step*

-- @owner engC @status DONE @changed + hi : i <= 288 (CONTRACT_ISSUES engC-4)
@[local step]
theorem c_huff_lengths_loop0_spec (freq m lens aw asy) (k i : Std.Usize) (hk : k.val ≤ i.val) (hi : i.val ≤ 288) :
    slot.c_huff_lengths_loop0 freq m lens aw asy k i ⦃ fun r => r.2.2.2.val ≤ 288 ⦄ := by
  rw [slot.c_huff_lengths_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, i') => 288 - i'.val)
    (inv := fun (_, _, _, k', i') => k'.val ≤ i'.val ∧ i'.val ≤ 288)
  · rintro ⟨lens', aw', asy', k', i'⟩ ⟨hk', hi'⟩
    simp only [slot.c_huff_lengths_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact ⟨hk, hi⟩

-- @owner engC @status DONE
@[local step]
theorem c_huff_lengths_loop1_loop0_spec (aw) (k : Std.Usize) (iw ipar lpar) (li ii ni : Std.Usize) (w2) (t : Std.Usize)
    (hii : ii.val ≤ 2 ^ 20) :
    slot.c_huff_lengths_loop1_loop0 aw k iw ipar lpar li ii ni w2 t ⦃ fun r => r.2.2.2.1.val ≤ ii.val + 2 ⦄ := by
  rw [slot.c_huff_lengths_loop1_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, _, t') => 2 - t'.val)
    (inv := fun (_, _, _, ii', _, t') => ii'.val + t.val ≤ ii.val + t'.val ∧ t.val ≤ t'.val ∧
      (t.val ≤ 2 → t'.val ≤ 2) ∧ (2 < t.val → t'.val = t.val))
  · rintro ⟨ipar', lpar', li', ii', w2', t'⟩ ⟨h1, h2, h3, h4⟩
    simp only [slot.c_huff_lengths_loop1_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · simp

-- @owner engC @status DONE @changed + hk : k <= 288 (CONTRACT_ISSUES engC-4)
@[local step]
theorem c_huff_lengths_loop1_spec (aw) (k : Std.Usize) (iw ipar lpar) (li ii ni : Std.Usize) (hii : ii.val ≤ 2 * ni.val)
    (hni : ni.val ≤ 287) (hk : k.val ≤ 288) :
    slot.c_huff_lengths_loop1 aw k iw ipar lpar li ii ni ⦃ fun r => ni.val ≤ r.2.2.val ∧ (ni.val + 1 < k.val → ni.val < r.2.2.val) ⦄ := by
  rw [slot.c_huff_lengths_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, _, ni') => 287 - ni'.val)
    (inv := fun (_, _, _, _, ii', ni') => ni.val ≤ ni'.val ∧ ni'.val ≤ 287 ∧ ii'.val ≤ 2 * ni'.val)
  · rintro ⟨iw', ipar', lpar', li', ii', ni'⟩ ⟨h1, h2, h3⟩
    simp only [slot.c_huff_lengths_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact ⟨le_refl _, hni, hii⟩

-- @owner engC @status DONE
@[local step]
theorem c_huff_lengths_loop2_spec (ipar idep j) :
    slot.c_huff_lengths_loop2 ipar idep j ⦃ fun _ => True ⦄ := by
  rw [slot.c_huff_lengths_loop2]
  apply Std.loop.spec_decr_nat
    (measure := fun (idep_, j_) => j_.val)
    (inv := fun _ => True)
  · rintro ⟨idep_, j_⟩ _
    simp only [slot.c_huff_lengths_loop2.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial

-- @owner engC @status DONE
@[local step]
theorem c_huff_lengths_loop3_spec (lens asy k lpar idep x) :
    slot.c_huff_lengths_loop3 lens asy k lpar idep x ⦃ fun _ => True ⦄ := by
  rw [slot.c_huff_lengths_loop3]
  apply Std.loop.spec_decr_nat
    (measure := fun (lens_, x_) => k.val - x_.val)
    (inv := fun _ => True)
  · rintro ⟨lens_, x_⟩ _
    simp only [slot.c_huff_lengths_loop3.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial

-- @owner engC @status DONE
@[local step]
theorem c_huff_lengths_spec (freq m lens) : slot.c_huff_lengths freq m lens ⦃ fun _ => True ⦄ := by
  rw [slot.c_huff_lengths]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

-- @owner engC @status DONE @changed + hi : i <= 286, post + hlit bound (CONTRACT_ISSUES engC-5)
@[local step]
theorem c_dyn_bits_loop0_spec (lf ll) (body : Std.U64) (hlit i : Std.Usize) (hi : i.val ≤ 286)
    (hb : body.val ≤ i.val * 2 ^ 41) :
    slot.c_dyn_bits_loop0 lf ll body hlit i ⦃ fun r => r.1.val ≤ 286 * 2 ^ 41 ∧ r.2.val ≤ max hlit.val 286 ⦄ := by
  rw [slot.c_dyn_bits_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, i') => 286 - i'.val)
    (inv := fun (b', h', i') => i'.val ≤ 286 ∧ b'.val ≤ i'.val * 2 ^ 41 ∧ h'.val ≤ max hlit.val 286)
  · rintro ⟨b', h', i'⟩ ⟨h1, h2, h3⟩
    simp only [slot.c_dyn_bits_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact ⟨hi, hb, by scalar_tac⟩

-- @owner engC @status DONE @changed + hd : d <= 30, post + hdist bound (CONTRACT_ISSUES engC-5)
@[local step]
theorem c_dyn_bits_loop1_spec (df dl) (body : Std.U64) (hdist any : Std.Usize) (d : Std.Usize) (hd : d.val ≤ 30)
    (hb : body.val ≤ 286 * 2 ^ 41 + d.val * 2 ^ 41) :
    slot.c_dyn_bits_loop1 df dl body hdist any d ⦃ fun r => r.1.val ≤ 316 * 2 ^ 41 ∧ r.2.1.val ≤ max hdist.val 30 ⦄ := by
  rw [slot.c_dyn_bits_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, d') => 30 - d'.val)
    (inv := fun (b', h', _, d') => d'.val ≤ 30 ∧ b'.val ≤ 286 * 2 ^ 41 + d'.val * 2 ^ 41 ∧ h'.val ≤ max hdist.val 30)
  · rintro ⟨b', h', a', d'⟩ ⟨h1, h2, h3⟩
    simp only [slot.c_dyn_bits_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact ⟨hd, hb, by scalar_tac⟩

-- @owner engC @status DONE
@[local step]
theorem c_dyn_bits_loop2_spec (ll dl hlit total seq i2) :
    slot.c_dyn_bits_loop2 ll dl hlit total seq i2 ⦃ fun _ => True ⦄ := by
  rw [slot.c_dyn_bits_loop2]
  apply Std.loop.spec_decr_nat
    (measure := fun (seq_, i2_) => total.val - i2_.val)
    (inv := fun _ => True)
  · rintro ⟨seq_, i2_⟩ _
    simp only [slot.c_dyn_bits_loop2.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial

-- @owner engC @status DONE @changed post + r <= res, j + r <= 512 -> j + res <= 512 (CONTRACT_ISSUES engC-5)
@[local step]
theorem c_dyn_bits_loop3_loop0_spec (total seq) (j r : Std.Usize) (v) (hj : j.val ≤ 512) (hr : r.val ≤ 512) :
    slot.c_dyn_bits_loop3_loop0 total seq j v r ⦃ fun res => r.val ≤ res.val ∧ res.val ≤ max r.val 512 ∧
      (j.val + r.val ≤ 512 → j.val + res.val ≤ 512) ⦄ := by
  rw [slot.c_dyn_bits_loop3_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun r' => 512 - r'.val)
    (inv := fun r' => r.val ≤ r'.val ∧ r'.val ≤ max r.val 512 ∧ (j.val + r.val ≤ 512 → j.val + r'.val ≤ 512))
  · rintro r' ⟨h1, h2, h3⟩
    simp only [slot.c_dyn_bits_loop3_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact ⟨le_refl _, by scalar_tac, fun h => h⟩

-- @owner engC @status DONE @changed + hj : j <= 512 (CONTRACT_ISSUES engC-5)
@[local step]
theorem c_dyn_bits_loop3_spec (clf) (extra : Std.U64) (total seq) (j : Std.Usize) (hj : j.val ≤ 512)
    (hx : extra.val ≤ j.val * 4096) :
    slot.c_dyn_bits_loop3 clf extra total seq j ⦃ fun r => r.2.val ≤ 513 * 4096 ⦄ := by
  rw [slot.c_dyn_bits_loop3]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, j') => 512 - j'.val)
    (inv := fun (_, e', j') => j'.val ≤ 512 ∧ e'.val ≤ j'.val * 4096)
  · rintro ⟨clf', e', j'⟩ ⟨h1, h2⟩
    simp only [slot.c_dyn_bits_loop3.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact ⟨hj, hx⟩

-- @owner engC @status DONE @changed post r <= hclen (CONTRACT_ISSUES engC-5)
@[local step]
theorem c_dyn_bits_loop4_spec (cl hclen) :
    slot.c_dyn_bits_loop4 cl hclen ⦃ fun r => r.val ≤ hclen.val ⦄ := by
  rw [slot.c_dyn_bits_loop4]
  apply Std.loop.spec_decr_nat
    (measure := fun h' => h'.val)
    (inv := fun h' => h'.val ≤ hclen.val)
  · rintro h' h1
    simp only [slot.c_dyn_bits_loop4.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact le_refl _

-- @owner engC @status DONE @changed + hc : c <= 19 (CONTRACT_ISSUES engC-5)
@[local step]
theorem c_dyn_bits_loop5_spec (clf cl) (hdr : Std.U64) (c : Std.Usize) (hc : c.val ≤ 19)
    (hh : hdr.val ≤ 2 ^ 40 + c.val * 2 ^ 35) :
    slot.c_dyn_bits_loop5 clf cl hdr c ⦃ fun r => r.val ≤ 2 ^ 40 + 19 * 2 ^ 35 ⦄ := by
  rw [slot.c_dyn_bits_loop5]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, c') => 19 - c'.val)
    (inv := fun (h', c') => c'.val ≤ 19 ∧ h'.val ≤ 2 ^ 40 + c'.val * 2 ^ 35)
  · rintro ⟨h', c'⟩ ⟨h1, h2⟩
    simp only [slot.c_dyn_bits_loop5.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact ⟨hc, hh⟩

-- @owner engC @status DONE
@[local step]
theorem c_dyn_bits_spec (lf df) : slot.c_dyn_bits lf df ⦃ fun _ => True ⦄ := by
  rw [slot.c_dyn_bits]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

-- @owner engC @status DONE @changed stated at lb = zeros, no hlb (CONTRACT_ISSUES engC-6)
/-- Literal counts of `s[q..ec]`, starting from zero counters: each counter stays below `ec < 2^26`. -/
@[local step]
theorem c_plan_blocks_loop0_loop0_spec (s : Slice Std.U8) (ec q : Std.Usize)
    (hec : ec.val ≤ s.length) (hn26 : s.length < 67108864) :
    slot.c_plan_blocks_loop0_loop0 s ec (Array.repeat 288#usize 0#u32) q ⦃ fun _ => True ⦄ := by
  rw [slot.c_plan_blocks_loop0_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, q') => ec.val - q'.val)
    (inv := fun (lb', q') => LeAll lb'.val q'.val)
  · rintro ⟨lb', q'⟩ hlb'
    simp only [slot.c_plan_blocks_loop0_loop0.body]
    step*
    all_goals first
      | (have := LeAll_get hlb' i1.val (by scalar_tac)
         scalar_tac)
      | (refine ⟨?_, by scalar_tac⟩
         rw [a_post, Array.set_val_eq, show q1.val = q'.val + 1 by scalar_tac]
         apply LeAll_set_succ hlb'
         have := LeAll_get hlb' i1.val (by scalar_tac)
         scalar_tac)
  · exact engC_LeAll_repeat _ _ _ (by simp)

-- @owner engC @status DONE
@[local step]
theorem c_plan_blocks_loop0_spec (s : Slice Std.U8) (plan) (n : Std.Usize) (lf df p fuel) (hn : n.val = s.length)
    (hn26 : n.val < 67108864) :
    slot.c_plan_blocks_loop0 s plan n lf df p fuel ⦃ fun _ => True ⦄ := by
  have hB := C_BLOCK_bounds
  rw [slot.c_plan_blocks_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, f) => f.val)
    (inv := fun _ => True)
  · rintro ⟨plan', lf', df', p', f'⟩ _
    simp only [slot.c_plan_blocks_loop0.body]
    step*
    apply WP.spec_bind (Pₘ := fun _ => True)
    · split <;> step*
    rintro ca _
    step*
    apply WP.spec_bind (Pₘ := fun (x : Std.Usize) => p'.val ≤ x.val ∧ x.val ≤ n.val)
    · split <;> step*
      all_goals scalar_tac
    rintro eb ⟨heb1, heb2⟩
    apply WP.spec_bind (Pₘ := fun (x : Std.Usize) => p'.val ≤ x.val ∧ x.val ≤ n.val)
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

-- @owner engC @status DONE
@[local step]
theorem c_plan_blocks_spec (s : Slice Std.U8) (plan) (hn26 : s.length < 67108864) :
    slot.c_plan_blocks s plan ⦃ fun _ => True ⦄ := by
  rw [slot.c_plan_blocks]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

-- @owner engC @status DONE
@[local step]
theorem c_is_dna_loop_spec (s : Slice Std.U8) (n allow : Std.Usize) (bad i : Std.Usize) (hn : n.val ≤ s.length)
    (hbad : bad.val ≤ i.val) :
    slot.c_is_dna_loop s n allow bad i ⦃ fun _ => True ⦄ := by
  rw [slot.c_is_dna_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, i') => n.val - i'.val)
    (inv := fun (bad', i') => bad'.val ≤ i'.val)
  · rintro ⟨bad', i'⟩ hb'
    simp only [slot.c_is_dna_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact hbad

-- @owner engC @status DONE
@[local step]
theorem c_is_dna_spec (s) :
    slot.c_is_dna s ⦃ fun _ => True ⦄ := by
  rw [slot.c_is_dna]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

-- @owner engC @status DONE @changed + hq : q <= 288 (CONTRACT_ISSUES engC-7)
@[local step]
theorem c_push_model_loop0_spec (lf df ll dl) (est : Std.U64) (q : Std.Usize) (hq : q.val ≤ 288)
    (he : est.val ≤ 70 + q.val * 2 ^ 42) :
    slot.c_push_model_loop0 lf df ll dl est q ⦃ fun r => r.val ≤ 70 + 288 * 2 ^ 42 ⦄ := by
  rw [slot.c_push_model_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, q') => 288 - q'.val)
    (inv := fun (e', q') => q'.val ≤ 288 ∧ e'.val ≤ 70 + q'.val * 2 ^ 42)
  · rintro ⟨e', q'⟩ ⟨h1, h2⟩
    simp only [slot.c_push_model_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact ⟨hq, he⟩

-- @owner engC @status DONE
@[local step]
theorem c_push_model_loop1_spec (models) (tokpen : Std.U32) (ll) (i : Std.Usize) (htok : tokpen.val ≤ 65536)
    (hm : models.length + (256 - i.val) < 4294967295) :
    slot.c_push_model_loop1 models tokpen ll i ⦃ fun r => r.length = models.length + (256 - i.val) ⦄ := by
  have h1 := C_SCALE_le
  have h2 := C_UNUSED_LIT_le
  rw [slot.c_push_model_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, i') => 256 - i'.val)
    (inv := fun (m', i') => m'.length = models.length + (i'.val - i.val) ∧ i.val ≤ i'.val ∧ i'.val ≤ max i.val 256)
  · rintro ⟨m', i'⟩ ⟨h3, h4, h5⟩
    simp only [slot.c_push_model_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact ⟨by simp, le_refl _, by scalar_tac⟩

-- @owner engC @status DONE
@[local step]
theorem c_push_model_loop2_spec (models) (tax ulen tokpen : Std.U32) (ll) (l : Std.Usize) (htax : tax.val ≤ 65536)
    (hulen : ulen.val ≤ 65536) (htok : tokpen.val ≤ 65536) (hl : 3 ≤ l.val)
    (hm : models.length + (259 - l.val) < 4294967295) :
    slot.c_push_model_loop2 models tax ulen tokpen ll l ⦃ fun r => r.length = models.length + (259 - l.val) ⦄ := by
  have h1 := C_SCALE_le
  rw [slot.c_push_model_loop2]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, l') => 259 - l'.val)
    (inv := fun (m', l') => m'.length = models.length + (l'.val - l.val) ∧ l.val ≤ l'.val ∧ l'.val ≤ max l.val 259)
  · rintro ⟨m', l'⟩ ⟨h3, h4, h5⟩
    simp only [slot.c_push_model_loop2.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact ⟨by simp, le_refl _, by scalar_tac⟩

-- @owner engC @status DONE
@[local step]
theorem c_push_model_loop3_spec (models) (udist : Std.U32) (dl) (d : Std.Usize) (hud : udist.val ≤ 65536)
    (hm : models.length + (32 - d.val) < 4294967295) :
    slot.c_push_model_loop3 models udist dl d ⦃ fun r => r.length = models.length + (32 - d.val) ⦄ := by
  have h1 := C_SCALE_le
  rw [slot.c_push_model_loop3]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, d') => 32 - d'.val)
    (inv := fun (m', d') => m'.length = models.length + (d'.val - d.val) ∧ d.val ≤ d'.val ∧ d'.val ≤ max d.val 32)
  · rintro ⟨m', d'⟩ ⟨h3, h4, h5⟩
    simp only [slot.c_push_model_loop3.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact ⟨by simp, le_refl _, by scalar_tac⟩

-- @owner engC @status DONE
@[local step]
theorem c_push_model_spec (models lf df) (tax ulen udist tokpen : Std.U32) (htax : tax.val ≤ 65536) (hulen : ulen.val ≤ 65536)
    (hud : udist.val ≤ 65536) (htok : tokpen.val ≤ 65536) (hm : models.length + 544 < 4294967295) :
    slot.c_push_model models lf df tax ulen udist tokpen ⦃ fun r => r.1.val ≤ 70 + 288 * 2 ^ 42 ∧ r.2.length = models.length + 544 ⦄ := by
  rw [slot.c_push_model]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

-- @owner engC @status DONE @changed post: progress + block length facts (CONTRACT_ISSUES engC-8)
/-- One block of the chosen path: at least one token when `p < n` and `t < C_BLOCK`; a block that
    stops before `n` has `C_BLOCK - t` tokens, each at least one byte. -/
@[local step]
theorem c_restat_loop0_loop0_spec (s : Slice Std.U8) (choice) (n : Std.Usize) (lf df) (p t : Std.Usize)
    (hn : n.val ≤ s.length) (hnc : n.val ≤ choice.length) (hn26 : n.val < 67108864) :
    slot.c_restat_loop0_loop0 s choice n lf df p t ⦃ fun r => p.val ≤ r.2.2.val ∧
      r.2.2.val ≤ max p.val (n.val + 511) ∧
      (p.val < n.val → t.val < slot.C_BLOCK.val → p.val < r.2.2.val) ∧
      (r.2.2.val < n.val → p.val + (slot.C_BLOCK.val - t.val) ≤ r.2.2.val) ⦄ := by
  have hB := C_BLOCK_bounds
  rw [slot.c_restat_loop0_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, t') => slot.C_BLOCK.val - t'.val)
    (inv := fun (_, _, p', t') => p.val + (t'.val - t.val) ≤ p'.val ∧ t.val ≤ t'.val ∧
      p'.val ≤ max p.val (n.val + 511) ∧ t'.val ≤ max t.val slot.C_BLOCK.val)
  · rintro ⟨lf', df', p', t'⟩ ⟨h1, h2, h3, h4⟩
    simp only [slot.c_restat_loop0_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact ⟨by simp, le_refl _, by scalar_tac, by scalar_tac⟩

-- @owner engC @status DONE @changed + hn hnc knob bounds + block-count invariant, post = invariant (CONTRACT_ISSUES engC-8)
/-- The block loop. With `k = models.length / 544` blocks done: every block but the last covers at
    least `C_BLOCK ≥ 8192` bytes, so `k ≤ n / 8192 + 1`; this bounds `models` (544 entries per
    block), `bstart` (one start per block) and `total` (one estimate `≤ 70 + 288 * 2^42` per block),
    all stated without division. -/
@[local step]
theorem c_restat_loop0_spec (s : Slice Std.U8) (choice models bstart) (tax ulen udist tokpen : Std.U32)
    (total : Std.U64) (n : Std.Usize) (lf df) (p : Std.Usize)
    (hn : n.val ≤ s.length) (hnc : n.val ≤ choice.length) (hn26 : n.val < 67108864)
    (htax : tax.val ≤ 65536) (hulen : ulen.val ≤ 65536) (hud : udist.val ≤ 65536) (htok : tokpen.val ≤ 65536)
    (hb : 544 * bstart.length ≤ models.length + 544)
    (ht : 544 * total.val ≤ models.length * (70 + 288 * 2 ^ 42))
    (hm : models.length * 8192 < 544 * (n.val + 8192))
    (hp : p.val < n.val → models.length * 8192 ≤ 544 * p.val) :
    slot.c_restat_loop0 s choice models bstart tax ulen udist tokpen total n lf df p ⦃ fun r =>
      544 * r.2.1.length ≤ r.1.length + 544 ∧ 544 * r.2.2.1.val ≤ r.1.length * (70 + 288 * 2 ^ 42) ∧
      r.1.length * 8192 < 544 * (n.val + 8192) ⦄ := by
  have hB := C_BLOCK_bounds
  rw [slot.c_restat_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, _, p') => n.val - p'.val)
    (inv := fun (m', b', t', _, _, p') => 544 * b'.length ≤ m'.length + 544 ∧
      544 * t'.val ≤ m'.length * (70 + 288 * 2 ^ 42) ∧ m'.length * 8192 < 544 * (n.val + 8192) ∧
      (p'.val < n.val → m'.length * 8192 ≤ 544 * p'.val))
  · rintro ⟨m', b', t', lf', df', p'⟩ ⟨h1, h2, h3, h4⟩
    simp only [slot.c_restat_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact ⟨hb, ht, hm, hp⟩

-- @owner engC @status DONE
@[local step]
theorem c_restat_spec (s : Slice Std.U8) (choice models bstart) (tax ulen udist tokpen : Std.U32)
    (hn26 : s.length < 67108864) (htax : tax.val ≤ 65536) (hulen : ulen.val ≤ 65536) (hud : udist.val ≤ 65536)
    (htok : tokpen.val ≤ 65536) :
    slot.c_restat s choice models bstart tax ulen udist tokpen ⦃ fun r => r.2.2.length ≤ 1048576 ⦄ := by
  rw [slot.c_restat]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

-- @owner engC @status DONE
@[local step]
theorem c_greedy_choice_loop0_spec (choice n p) :
    slot.c_greedy_choice_loop0 choice n p ⦃ fun _ => True ⦄ := by
  rw [slot.c_greedy_choice_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (choice_, p_) => n.val - p_.val)
    (inv := fun _ => True)
  · rintro ⟨choice_, p_⟩ _
    simp only [slot.c_greedy_choice_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial

-- @owner engC @status DONE
@[local step]
theorem c_greedy_choice_loop1_spec (clist choice n gmin) (m k : Std.Usize) (hm : m.val = clist.length) (hk : 1 ≤ k.val) :
    slot.c_greedy_choice_loop1 clist choice n gmin m k ⦃ fun _ => True ⦄ := by
  rw [slot.c_greedy_choice_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, k') => m.val - k'.val)
    (inv := fun (_, k') => 1 ≤ k'.val)
  · rintro ⟨choice', k'⟩ hk'
    simp only [slot.c_greedy_choice_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact hk

-- @owner engC @status DONE
@[local step]
theorem c_greedy_choice_spec (clist choice n gmin) :
    slot.c_greedy_choice clist choice n gmin ⦃ fun _ => True ⦄ := by
  rw [slot.c_greedy_choice]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

-- @owner engC @status DONE
@[local step]
theorem c_load_model_loop0_spec (models : alloc.vec.Vec Std.U32) (lit_c len_c) (base i : Std.Usize) (hb : base.val + slot.C_MS.val ≤ models.length) :
    slot.c_load_model_loop0 models lit_c len_c base i ⦃ fun _ => True ⦄ := by
  rw [slot.c_load_model_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (lit_c_, len_c_, i_) => 256 - i_.val)
    (inv := fun _ => True)
  · rintro ⟨lit_c_, len_c_, i_⟩ _
    simp only [slot.c_load_model_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial

-- @owner engC @status DONE
@[local step]
theorem c_load_model_loop1_spec (models : alloc.vec.Vec Std.U32) (dst_c) (base d : Std.Usize) (hb : base.val + slot.C_MS.val ≤ models.length) :
    slot.c_load_model_loop1 models dst_c base d ⦃ fun _ => True ⦄ := by
  rw [slot.c_load_model_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (dst_c_, d_) => 32 - d_.val)
    (inv := fun _ => True)
  · rintro ⟨dst_c_, d_⟩ _
    simp only [slot.c_load_model_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial

-- @owner engC @status DONE
@[local step]
theorem c_load_model_spec (models) (b : Std.Usize) (lit_c len_c dst_c) (hb : b.val ≤ 1048576) :
    slot.c_load_model models b lit_c len_c dst_c ⦃ fun _ => True ⦄ := by
  rw [slot.c_load_model]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

-- @owner engC @status DONE @changed post r <= ge (CONTRACT_ISSUES engC-9)
@[local step]
theorem c_group_start_spec (clist ge) :
    slot.c_group_start clist ge ⦃ fun r => r.val ≤ ge.val ⦄ := by
  rw [slot.c_group_start]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

-- @owner engC @status DONE
@[local step]
theorem c_dp_pass_loop0_loop0_spec (bstart : alloc.vec.Vec Std.U32) (b q : Std.Usize) (hb : b.val < bstart.length) :
    slot.c_dp_pass_loop0_loop0 bstart b q ⦃ fun r => r.val ≤ b.val ⦄ := by
  rw [slot.c_dp_pass_loop0_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun b' => b'.val)
    (inv := fun b' => b'.val ≤ b.val)
  · rintro b' hb'
    simp only [slot.c_dp_pass_loop0_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact le_refl _

-- @owner engC @status DONE
@[local step]
theorem c_dp_pass_loop0_loop1_spec (s : Slice Std.U8) (choice : Slice Std.U32) (ring lit_c next) (p lo : Std.Usize)
    (hp : p.val ≤ s.length) (hc : s.length ≤ choice.length) :
    slot.c_dp_pass_loop0_loop1 s choice ring lit_c next p lo ⦃ fun r => r.1.length = choice.length ∧ r.2.2.2.val ≤ p.val ⦄ := by
  rw [slot.c_dp_pass_loop0_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, p') => p'.val)
    (inv := fun (c', _, _, p') => c'.length = choice.length ∧ p'.val ≤ p.val)
  · rintro ⟨c', r', n', p'⟩ ⟨h1, h2⟩
    simp only [slot.c_dp_pass_loop0_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact ⟨rfl, le_refl _⟩

-- @owner engC @status DONE
@[local step]
theorem c_dp_pass_loop0_loop2_loop0_spec (ring len_c) (p : Std.Usize) (best ch) (l : Std.Usize) (dc tag) (len : Std.Usize)
    (hp : p.val ≤ 2 ^ 30) (hl : l.val ≤ 511) (hlen : 3 ≤ len.val) :
    slot.c_dp_pass_loop0_loop2_loop0 ring len_c p best ch l dc tag len ⦃ fun _ => True ⦄ := by
  rw [slot.c_dp_pass_loop0_loop2_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, len') => l.val + 1 - len'.val)
    (inv := fun (_, _, len') => 3 ≤ len'.val)
  · rintro ⟨b', c', len'⟩ h1
    simp only [slot.c_dp_pass_loop0_loop2_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact hlen

-- @owner engC @status DONE @changed + hk : k <= clist.length, hcl (CONTRACT_ISSUES engC-9)
@[local step]
theorem c_dp_pass_loop0_loop2_spec (clist ring len_c dst_c) (ge p : Std.Usize) (best ch) (prev room k : Std.Usize)
    (hp : p.val ≤ 2 ^ 30) (hprev : 2 ≤ prev.val ∧ prev.val ≤ 511)
    (hk : k.val ≤ clist.length) (hcl : clist.length < 4294967295) :
    slot.c_dp_pass_loop0_loop2 clist ring len_c dst_c ge p best ch prev room k ⦃ fun _ => True ⦄ := by
  rw [slot.c_dp_pass_loop0_loop2]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, k') => clist.length - k'.val)
    (inv := fun (_, _, prev', k') => 2 ≤ prev'.val ∧ prev'.val ≤ 511 ∧ k'.val ≤ clist.length)
  · rintro ⟨b', c', prev', k'⟩ ⟨h1, h2, h3⟩
    simp only [slot.c_dp_pass_loop0_loop2.body]
    step*
    apply WP.spec_bind (Pₘ := fun (x : Std.Usize) => 2 ≤ x.val ∧ x.val ≤ 511)
    · repeat' (split <;> step*)
      all_goals scalar_tac
    rintro prev1 ⟨hq1, hq2⟩
    step*
    apply WP.spec_bind (Pₘ := fun (x : Std.Usize) => x.val ≤ 511)
    · split <;> step*
      all_goals scalar_tac
    rintro l1 hl1
    step*
    all_goals scalar_tac
  · exact ⟨hprev.1, hprev.2, hk⟩

-- @owner engC @status DONE @changed + hcl, gs <= ge <= clist.length (CONTRACT_ISSUES engC-9)
@[local step]
theorem c_dp_pass_loop0_spec (s : Slice Std.U8) (clist models : alloc.vec.Vec Std.U32) (bstart : alloc.vec.Vec Std.U32) (choice : Slice Std.U32)
    (n : Std.Usize) (ring lit_c len_c dst_c) (b loaded ge gs gp : Std.Usize) (next) (p fuel : Std.Usize)
    (hn : n.val = s.length) (hn26 : n.val < 67108864) (hc : n.val ≤ choice.length) (hb : b.val < bstart.length)
    (hnb : bstart.length ≤ 1048576) (hp : p.val ≤ n.val) (hgp : gp.val ≤ n.val ∨ gp.val < 2 ^ 27)
    (hcl : clist.length < 4294967295) (hgs : gs.val ≤ ge.val) (hge : ge.val ≤ clist.length) :
    slot.c_dp_pass_loop0 s clist models bstart choice n ring lit_c len_c dst_c b loaded ge gs gp next p fuel ⦃ fun _ => True ⦄ := by
  have hpm := C_PMASK_lt
  rw [slot.c_dp_pass_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, _, _, _, _, _, _, _, _, f) => f.val)
    (inv := fun (c', _, _, _, _, b', _, ge', gs', gp', _, p', _) => c'.length = choice.length ∧
      b'.val < bstart.length ∧ p'.val ≤ n.val ∧ (gp'.val ≤ n.val ∨ gp'.val < 2 ^ 27) ∧
      gs'.val ≤ ge'.val ∧ ge'.val ≤ clist.length)
  · rintro ⟨c', r', l1', l2', d', b', ld', ge', gs', gp', nx', p', f'⟩ ⟨h1, h2, h3, h4, h5, h6⟩
    simp only [slot.c_dp_pass_loop0.body]
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

-- @owner engC @status DONE @changed + hcl : clist.length < 2^32 - 1 (CONTRACT_ISSUES engC-9)
@[local step]
theorem c_dp_pass_spec (s : Slice Std.U8) (clist models) (bstart : alloc.vec.Vec Std.U32) (choice)
    (hn26 : s.length < 67108864) (hnb : bstart.length ≤ 1048576) (hcl : clist.length < 4294967295) :
    slot.c_dp_pass s clist models bstart choice ⦃ fun _ => True ⦄ := by
  have hms := C_MS_val
  have hpm := C_PMASK_lt
  rw [slot.c_dp_pass]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

-- @owner engC @status DONE
@[local step]
theorem c_pack_spec (len) (d : Std.Usize) (hd : 1 ≤ d.val) : slot.c_pack len d ⦃ fun _ => True ⦄ := by
  rw [slot.c_pack]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

-- @owner engC @status DONE @changed hcl : clist.length + (cnt - i) < 2^32 - 1, post + top <= 258 (CONTRACT_ISSUES engC-10)
/-- At most one push per candidate index `i < cnt`, and a pushed length is `≤ 258`. -/
@[local step]
theorem c_push_cands_loop_spec (clist : alloc.vec.Vec Std.U32) (ml md) (cnt : Std.Usize) (flag) (top : Std.Usize)
    (pushed : Std.U32) (i : Std.Usize)
    (hcl : clist.length + (cnt.val - i.val) < 4294967295) (hpu : pushed.val ≤ 1) :
    slot.c_push_cands_loop clist ml md cnt flag top pushed i ⦃ fun r =>
      r.1.length ≤ clist.length + (cnt.val - i.val) ∧ r.2.2.val ≤ pushed.val + (cnt.val - i.val) ∧
      (top.val ≤ 258 → r.2.1.val ≤ 258) ⦄ := by
  rw [slot.c_push_cands_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, i') => 64 - i'.val)
    (inv := fun (c', t', u', i') => c'.length + (cnt.val - i'.val) ≤ clist.length + (cnt.val - i.val) ∧
      u'.val + (cnt.val - i'.val) ≤ pushed.val + (cnt.val - i.val) ∧ i.val ≤ i'.val ∧
      (top.val ≤ 258 → t'.val ≤ 258))
  · rintro ⟨c', t', u', i'⟩ ⟨h1, h2, h3, h4⟩
    simp only [slot.c_push_cands_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact ⟨le_refl _, le_refl _, le_refl _, fun h => h⟩

-- @owner engC @status DONE @changed post + r.1 <= 258 (CONTRACT_ISSUES engC-10)
@[local step]
theorem c_push_cands_spec (clist : alloc.vec.Vec Std.U32) (p ml md cnt r1 flag)
    (hcl : clist.length + slot.C_KEEP.val + 2 < 4294967295) :
    slot.c_push_cands clist p ml md cnt r1 flag ⦃ fun r => r.2.length ≤ clist.length + slot.C_KEEP.val + 2 ∧
      r.1.val ≤ 258 ⦄ := by
  rw [slot.c_push_cands]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

-- @owner engC @status DONE
@[local step]
theorem c_nt_code_spec (b) :
    slot.c_nt_code b ⦃ fun _ => True ⦄ := by
  rw [slot.c_nt_code]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

-- @owner engC @status DONE @changed hi : i + 8 <= Usize.max (CONTRACT_ISSUES engC-12)
@[local step]
theorem c_word_be_spec (s) (i : Std.Usize) (hi : i.val + 8 ≤ Usize.max) : slot.c_word_be s i ⦃ fun _ => True ⦄ := by
  rw [slot.c_word_be]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

-- @owner engC @status DONE
@[local step]
theorem c_extend_loop0_loop0_spec (s : Slice Std.U8) (a b lim k : Std.Usize) (ha : a.val + lim.val ≤ s.length) (hb : b.val + lim.val ≤ s.length) :
    slot.c_extend_loop0_loop0 s a b lim k ⦃ fun _ => True ⦄ := by
  rw [slot.c_extend_loop0_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun k_ => lim.val - k_.val)
    (inv := fun _ => True)
  · rintro k_ _
    simp only [slot.c_extend_loop0_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial

-- @owner engC @status DONE
@[local step]
theorem c_extend_loop0_loop1_spec (s : Slice Std.U8) (a b lim k : Std.Usize) (ha : a.val + lim.val ≤ s.length) (hb : b.val + lim.val ≤ s.length) :
    slot.c_extend_loop0_loop1 s a b lim k ⦃ fun _ => True ⦄ := by
  rw [slot.c_extend_loop0_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun k_ => lim.val - k_.val)
    (inv := fun _ => True)
  · rintro k_ _
    simp only [slot.c_extend_loop0_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial

-- @owner engC @status DONE
@[local step]
theorem c_extend_loop0_spec (s : Slice Std.U8) (a b lim k fuel : Std.Usize) (ha : a.val + lim.val ≤ s.length)
    (hb : b.val + lim.val ≤ s.length) (hk : k.val ≤ 2 ^ 31) (hlim : lim.val ≤ 2 ^ 31) :
    slot.c_extend_loop0 s a b lim k fuel ⦃ fun _ => True ⦄ := by
  rw [slot.c_extend_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, f') => f'.val)
    (inv := fun (k', _) => k'.val ≤ 2 ^ 31)
  · rintro ⟨k', f'⟩ hk'
    simp only [slot.c_extend_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact hk

-- @owner engC @status DONE
@[local step]
theorem c_extend_spec (s : Slice Std.U8) (a b k0 lim : Std.Usize) (ha : a.val + lim.val ≤ s.length) (hb : b.val + lim.val ≤ s.length)
    (hk0 : k0.val ≤ 2 ^ 31) (hlim : lim.val ≤ 2 ^ 31) :
    slot.c_extend s a b k0 lim ⦃ fun _ => True ⦄ := by
  rw [slot.c_extend]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

-- @owner engC @status DONE
@[local step]
theorem c_chain_walk_loop_spec (s : Slice Std.U8) (p k0 depth : Std.Usize) (prev ml md) (lim cur best cnt steps : Std.Usize)
    (hp : p.val + lim.val ≤ s.length) (hlim : lim.val ≤ 258) (hk0 : k0.val ≤ 2 ^ 31) :
    slot.c_chain_walk_loop s p k0 depth prev ml md lim cur best cnt steps ⦃ fun _ => True ⦄ := by
  have hws := C_WS_val
  rw [slot.c_chain_walk_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, _, st) => depth.val - st.val)
    (inv := fun _ => True)
  · rintro ⟨ml', md', cur', best', cnt', st'⟩ _
    simp only [slot.c_chain_walk_loop.body]
    step*
    apply WP.spec_bind (Pₘ := fun _ => True)
    · repeat' (split <;> step*)
      all_goals scalar_tac
    rintro ⟨ml1, md1, best1, cnt1⟩ _
    step*
    all_goals scalar_tac
  · trivial

-- @owner engC @status DONE
@[local step]
theorem c_chain_walk_spec (s : Slice Std.U8) (p key k0 best0 depth head prev ml md) (hp : p.val < s.length) (hk0 : k0.val ≤ 2 ^ 31) :
    slot.c_chain_walk s p key k0 best0 depth head prev ml md ⦃ fun _ => True ⦄ := by
  have hws := C_WS_val
  have hhs := C_HS_bounds
  rw [slot.c_chain_walk]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

-- @owner engC @status DONE
@[local step]
theorem c_put_kid_spec (kids) (which : Std.Usize) (idx v) (hw : which.val ≤ 1) :
    slot.c_put_kid kids which idx v ⦃ fun _ => True ⦄ := by
  have hws := C_WS_val
  have hks := C_KS_val
  rw [slot.c_put_kid]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

-- @owner engC @status DONE @changed + hp hlim hlw hgw hll hgl (CONTRACT_ISSUES engC-12)
@[local step]
theorem c_bt_find_loop_spec (back) (s : Slice Std.U8) (p depth kids ml md) (lim cur lw li gw gi llen glen : Std.Usize)
    (best cnt steps i)
    (hp : p.val + lim.val ≤ s.length) (hlim : lim.val ≤ 258) (hlw : lw.val ≤ 1) (hgw : gw.val ≤ 1)
    (hll : llen.val ≤ lim.val) (hgl : glen.val ≤ lim.val) :
    slot.c_bt_find_loop back s p depth kids ml md lim cur lw li gw gi llen glen best cnt steps i ⦃ fun _ => True ⦄ := by
  have hws := C_WS_val
  have hks := C_KS_val
  rw [slot.c_bt_find_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, _, _, _, _, _, _, _, _, st) => depth.val - st.val)
    (inv := fun (_, _, _, _, lw', _, gw', _, ll', gl', _, _, _) => lw'.val ≤ 1 ∧ gw'.val ≤ 1 ∧
      ll'.val ≤ lim.val ∧ gl'.val ≤ lim.val)
  · rintro ⟨kids', ml', md', cur', lw', li', gw', gi', ll', gl', best', cnt', st'⟩ ⟨h1, h2, h3, h4⟩
    simp only [slot.c_bt_find_loop.body]
    step*
    apply WP.spec_bind (Pₘ := fun (x : Std.Usize) => x.val ≤ lim.val)
    · split <;> step*
      all_goals scalar_tac
    rintro k0 hk0
    step*
    apply WP.spec_bind (Pₘ := fun _ => True)
    · repeat' (split <;> step*)
      all_goals scalar_tac
    rintro ⟨ml1, md1, best1, cnt1⟩ _
    step*
    apply WP.spec_bind (Pₘ := fun (x : Std.Array Std.U32 65536#usize × Std.Usize × Std.Usize × Std.Usize ×
        Std.Usize × Std.Usize × Std.Usize × Std.Usize) =>
      x.2.2.1.val ≤ 1 ∧ x.2.2.2.2.1.val ≤ 1 ∧ x.2.2.2.2.2.2.1.val ≤ lim.val ∧ x.2.2.2.2.2.2.2.val ≤ lim.val)
    · split <;> step*
      all_goals scalar_tac
    rintro ⟨kids1, cur1, lw1, li1, gw1, gi1, llen1, glen1⟩ ⟨h5, h6, h7, h8⟩
    step*
    all_goals scalar_tac
  · exact ⟨hlw, hgw, hll, hgl⟩

-- @owner engC @status DONE
@[local step]
theorem c_bt_find_spec (s : Slice Std.U8) (p h depth head kids ml md) (hp : p.val < s.length) :
    slot.c_bt_find s p h depth head kids ml md ⦃ fun _ => True ⦄ := by
  have hws := C_WS_val
  have hhs := C_HS_bounds
  rw [slot.c_bt_find]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

-- @owner engC @status DONE @changed + hq : q <= 7 (CONTRACT_ISSUES engC-11)
@[local step]
theorem c_find_dna_loop0_spec (s : Slice Std.U8) (n key : Std.Usize) (run run2 q : Std.Usize) (hn : n.val = s.length)
    (hrun : run.val ≤ q.val) (hrun2 : run2.val ≤ q.val) (hq : q.val ≤ 7) :
    slot.c_find_dna_loop0 s n key run run2 q ⦃ fun r => r.2.1.val ≤ 7 ∧ r.2.2.val ≤ 7 ⦄ := by
  rw [slot.c_find_dna_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, q') => 7 - q'.val)
    (inv := fun (_, r1, r2, q') => r1.val ≤ q'.val ∧ r2.val ≤ q'.val ∧ q'.val ≤ 7)
  · rintro ⟨k', r1, r2, q'⟩ ⟨h1, h2, h3⟩
    simp only [slot.c_find_dna_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact ⟨hrun, hrun2, hq⟩

-- @owner engC @status DONE @changed hcl : clist <= 34 p, + hp, post clist <= 34 n (CONTRACT_ISSUES engC-11)
@[local step]
theorem c_find_dna_loop1_spec (s : Slice Std.U8) (clist) (depth_lo n : Std.Usize) (head8 prev8 head3 kids ml md)
    (key run run2 p skip_to : Std.Usize)
    (hn : n.val = s.length) (hn26 : n.val < 67108864) (hrun : run.val ≤ p.val + 7) (hrun2 : run2.val ≤ p.val + 7)
    (hp : p.val ≤ n.val) (hcl : clist.length ≤ 34 * p.val) :
    slot.c_find_dna_loop1 s clist depth_lo n head8 prev8 head3 kids ml md key run run2 p skip_to ⦃ fun r =>
      r.length ≤ 34 * n.val ⦄ := by
  have hws := C_WS_val
  have hhs := C_HS_bounds
  have hkp := C_KEEP_le
  have hup := C_UP_MIN_ge
  rw [slot.c_find_dna_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, _, _, _, _, _, _, p', _) => n.val - p'.val)
    (inv := fun (c', _, _, _, _, _, _, _, r1, r2, p', _) => r1.val ≤ p'.val + 7 ∧ r2.val ≤ p'.val + 7 ∧
      p'.val ≤ n.val ∧ c'.length ≤ 34 * p'.val)
  · rintro ⟨c', h8', pv8', h3', kids', ml', md', key', r1, r2, p', sk'⟩ ⟨h1, h2, h3, h4⟩
    unfold slot.c_find_dna_loop1.body
    step*
    -- the rolling key and the two run counters
    apply WP.spec_bind (Pₘ := fun (x : Std.Usize × Std.Usize × Std.Usize) =>
      x.2.1.val ≤ p'.val + 8 ∧ x.2.2.val ≤ p'.val + 8)
    · repeat' (split <;> step*)
      all_goals scalar_tac
    rintro ⟨key1, run1, run21⟩ ⟨hr1, hr2⟩
    step*
    -- the search at p' (lower case: tree; 8-mer run: exact chains; other run: word chains)
    apply WP.spec_bind (Pₘ := fun (x : alloc.vec.Vec Std.U32 × Std.Array Std.U32 65536#usize ×
        Std.Array Std.U32 32768#usize × Std.Array Std.U32 65536#usize × Std.Array Std.U32 65536#usize ×
        Std.Array Std.U32 64#usize × Std.Array Std.U32 64#usize × Std.Usize) =>
      x.1.length ≤ c'.length + 34)
    · apply engC_ite_spec
      · intro hc
        step*
        · -- a lower-case letter: binary tree on 3-byte keys
          apply WP.spec_bind (Pₘ := fun (x : alloc.vec.Vec Std.U32 × _) => x.1.length ≤ c'.length + 34)
          · apply engC_ite_spec
            · intro hs
              step*
              apply WP.spec_bind (Pₘ := fun (x : alloc.vec.Vec Std.U32 × _) => x.1.length ≤ c'.length + 34)
              · apply engC_ite_spec
                · intro hcnt
                  step*
                  apply engC_bind_ite_spec <;> intro _ <;> step*
                · intro hcnt
                  step*
              · rintro ⟨v2, a4, a5, i17⟩ hv2
                step*
            · intro hs
              step*
          · rintro ⟨v1, a, a1, a2, a3, i16⟩ hv1
            step*
        · -- any other byte above 'z'
          apply WP.spec_bind (Pₘ := fun (x : alloc.vec.Vec Std.U32 × _) => x.1.length ≤ c'.length + 34)
          · apply engC_ite_spec
            · -- a run of at least 8 nucleotides: exact 8-mer chains
              intro hr
              apply WP.spec_bind (Pₘ := fun (x : alloc.vec.Vec Std.U32 × _) => x.1.length ≤ c'.length + 34)
              · apply engC_ite_spec
                · intro hs
                  step*
                  apply WP.spec_bind (Pₘ := fun (x : alloc.vec.Vec Std.U32 × _) => x.1.length ≤ c'.length + 34)
                  · apply engC_ite_spec
                    · intro hcnt
                      step*
                      apply engC_bind_ite_spec <;> intro _ <;> step*
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
              apply WP.spec_bind (Pₘ := fun (x : alloc.vec.Vec Std.U32 × _) => x.1.length ≤ c'.length + 34)
              · apply engC_ite_spec
                · intro hr2
                  step*
                  apply WP.spec_bind (Pₘ := fun (x : alloc.vec.Vec Std.U32 × _) => x.1.length ≤ c'.length + 34)
                  · apply engC_ite_spec
                    · intro hcnt
                      step*
                      apply engC_bind_ite_spec <;> intro _ <;> step*
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
          apply WP.spec_bind (Pₘ := fun (x : alloc.vec.Vec Std.U32 × _) => x.1.length ≤ c'.length + 34)
          · apply engC_ite_spec
            · -- a run of at least 8 nucleotides: exact 8-mer chains
              intro hr
              apply WP.spec_bind (Pₘ := fun (x : alloc.vec.Vec Std.U32 × _) => x.1.length ≤ c'.length + 34)
              · apply engC_ite_spec
                · intro hs
                  step*
                  apply WP.spec_bind (Pₘ := fun (x : alloc.vec.Vec Std.U32 × _) => x.1.length ≤ c'.length + 34)
                  · apply engC_ite_spec
                    · intro hcnt
                      step*
                      apply engC_bind_ite_spec <;> intro _ <;> step*
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
              apply WP.spec_bind (Pₘ := fun (x : alloc.vec.Vec Std.U32 × _) => x.1.length ≤ c'.length + 34)
              · apply engC_ite_spec
                · intro hr2
                  step*
                  apply WP.spec_bind (Pₘ := fun (x : alloc.vec.Vec Std.U32 × _) => x.1.length ≤ c'.length + 34)
                  · apply engC_ite_spec
                    · intro hcnt
                      step*
                      apply engC_bind_ite_spec <;> intro _ <;> step*
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

-- @owner engC @status DONE @changed post r.length <= 34 * s.length (CONTRACT_ISSUES engC-11)
@[local step]
theorem c_find_dna_spec (s : Slice Std.U8) (clist) (depth_lo) (hn26 : s.length < 67108864) (hcl : clist.length = 0) :
    slot.c_find_dna s clist depth_lo ⦃ fun r => r.length ≤ 34 * s.length ⦄ := by
  rw [slot.c_find_dna]
  step*

-- @owner engC @status DONE
@[local step]
theorem c_run_len_spec (s : Slice Std.U8) (p : Std.Usize) (hp : p.val ≤ 2 ^ 31) : slot.c_run_len s p ⦃ fun _ => True ⦄ := by
  rw [slot.c_run_len]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

-- @owner engC @status DONE @changed hcl : clist <= 34 p, + hp, post clist <= 34 n (CONTRACT_ISSUES engC-11)
@[local step]
theorem c_find_bin_loop_spec (s : Slice Std.U8) (clist) (chain depth n : Std.Usize) (head lt kids ml md)
    (p skip_to pend : Std.Usize)
    (hn : n.val = s.length) (hn26 : n.val < 67108864) (hp : p.val ≤ n.val) (hcl : clist.length ≤ 34 * p.val) :
    slot.c_find_bin_loop s clist chain depth n head lt kids ml md p skip_to pend ⦃ fun r => r.length ≤ 34 * n.val ⦄ := by
  have hws := C_WS_val
  have hhs := C_HS_bounds
  have hkp := C_KEEP_le
  rw [slot.c_find_bin_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, _, _, p', _, _) => n.val - p'.val)
    (inv := fun (c', _, _, _, _, _, p', _, _) => p'.val ≤ n.val ∧ c'.length ≤ 34 * p'.val)
  · rintro ⟨c', hd', lt', kids', ml', md', p', sk', pe'⟩ ⟨h1, h2⟩
    unfold slot.c_find_bin_loop.body
    step*
    apply WP.spec_bind (Pₘ := fun _ => True)
    · split <;> step*
    rintro key _
    step*
    apply WP.spec_bind (Pₘ := fun (x : alloc.vec.Vec Std.U32 × Std.Array Std.U32 65536#usize ×
        Std.Array Std.U32 32768#usize × Std.Array Std.U32 65536#usize × Std.Array Std.U32 64#usize ×
        Std.Array Std.U32 64#usize × Std.Usize × Std.Usize) =>
      x.1.length ≤ c'.length + 34)
    · split
      · -- p ≥ skip_to: search, push the candidates, maybe skip ahead
        step*
        apply WP.spec_bind (Pₘ := fun _ => True)
        · split <;> step*
        rintro ⟨head2, lt2, kids2, ml2, md2, cnt⟩ _
        step*
        apply WP.spec_bind (Pₘ := fun _ => True)
        · repeat' (split <;> step*)
        rintro r1 _
        step*
        apply WP.spec_bind (Pₘ := fun (x : alloc.vec.Vec Std.U32 × Std.Usize) =>
          x.1.length ≤ c'.length + 34 ∧ x.2.val ≤ 258)
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

-- @owner engC @status DONE @changed post r.length <= 34 * s.length (CONTRACT_ISSUES engC-11)
@[local step]
theorem c_find_bin_spec (s : Slice Std.U8) (clist chain depth) (hn26 : s.length < 67108864) (hcl : clist.length = 0) :
    slot.c_find_bin s clist chain depth ⦃ fun r => r.length ≤ 34 * s.length ⦄ := by
  rw [slot.c_find_bin]
  step*

-- @owner engC @status DONE @changed + hcl : clist.length < 2^32 - 1 (CONTRACT_ISSUES engC-13)
@[local step]
theorem c_engine_loop0_spec (input : Slice Std.U8) (out min_dna dna) (clist : alloc.vec.Vec Std.U32) (models)
    (bstart : alloc.vec.Vec Std.U32) (passes) (tax tokpen : Std.U32) (last_est pass)
    (hn26 : input.length < 67108864) (htax : tax.val ≤ 65536) (htok : tokpen.val ≤ 65536)
    (hnb : bstart.length ≤ 1048576) (hcl : clist.length < 4294967295) :
    slot.c_engine_loop0 input out min_dna dna clist models bstart passes tax tokpen last_est pass ⦃ fun _ => True ⦄ := by
  have h1 := C_UNUSED_LEN_le
  have h2 := C_UNUSED_DIST_le
  have h3 := C_STOP_DIV_pos
  rw [slot.c_engine_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, pass') => passes.val - pass'.val)
    (inv := fun (_, _, b', _, _) => b'.length ≤ 1048576)
  · rintro ⟨out', models', b', le', pass'⟩ hb'
    simp only [slot.c_engine_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact hnb

-- @owner engC @status DONE @changed + hcl (CONTRACT_ISSUES engC-13)
@[local step]
theorem c_engine_loop1_spec (input : Slice Std.U8) (out min_dna dna) (clist : alloc.vec.Vec Std.U32) (models)
    (bstart : alloc.vec.Vec Std.U32) (passes) (tax tokpen : Std.U32) (last_est pass)
    (hn26 : input.length < 67108864) (htax : tax.val ≤ 65536) (htok : tokpen.val ≤ 65536)
    (hnb : bstart.length ≤ 1048576) (hcl : clist.length < 4294967295) :
    slot.c_engine_loop1 input out min_dna dna clist models bstart passes tax tokpen last_est pass ⦃ fun _ => True ⦄ := by
  have h1 := C_UNUSED_LEN_le
  have h2 := C_UNUSED_DIST_le
  have h3 := C_STOP_DIV_pos
  rw [slot.c_engine_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, pass') => passes.val - pass'.val)
    (inv := fun (_, _, b', _, _) => b'.length ≤ 1048576)
  · rintro ⟨out', models', b', le', pass'⟩ hb'
    simp only [slot.c_engine_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact hnb

-- @owner engC @status DONE @changed + hcl (CONTRACT_ISSUES engC-13)
@[local step]
theorem c_engine_loop2_spec (input : Slice Std.U8) (out min_dna dna) (clist : alloc.vec.Vec Std.U32) (models)
    (bstart : alloc.vec.Vec Std.U32) (passes) (tax tokpen : Std.U32) (last_est pass)
    (hn26 : input.length < 67108864) (htax : tax.val ≤ 65536) (htok : tokpen.val ≤ 65536)
    (hnb : bstart.length ≤ 1048576) (hcl : clist.length < 4294967295) :
    slot.c_engine_loop2 input out min_dna dna clist models bstart passes tax tokpen last_est pass ⦃ fun _ => True ⦄ := by
  have h1 := C_UNUSED_LEN_le
  have h2 := C_UNUSED_DIST_le
  have h3 := C_STOP_DIV_pos
  rw [slot.c_engine_loop2]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, pass') => passes.val - pass'.val)
    (inv := fun (_, _, b', _, _) => b'.length ≤ 1048576)
  · rintro ⟨out', models', b', le', pass'⟩ hb'
    simp only [slot.c_engine_loop2.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact hnb

-- @owner engC @status DONE (given c_rep_rates_loop_spec, BLOCKED(C1)) @export statement exactly as frozen
@[local step]
theorem c_engine_spec (input : Slice Std.U8) (out) (depth depth_lo wdp passes_w passes_bt passes_dna min_dna passes_c4 : Std.Usize)
    (hn : input.length < 67108864) (h1 : depth.val ≤ 65536) (h2 : depth_lo.val ≤ 65536) (h3 : wdp.val ≤ 65536)
    (h4 : passes_w.val ≤ 65536) (h5 : passes_bt.val ≤ 65536) (h6 : passes_dna.val ≤ 65536) (h7 : min_dna.val ≤ 65536)
    (h8 : passes_c4.val ≤ 65536) :
    slot.c_engine input out depth depth_lo wdp passes_w passes_bt passes_dna min_dna passes_c4 ⦃ fun _ => True ⦄ := by
  have f1 := C_TAX_W_le
  have f2 := C_TAX_C4_le
  have f3 := C_TAX_BT_le
  have f4 := C_UNUSED_LEN_W_le
  have f5 := C_UNUSED_DIST_W_le
  have f6 := C_TOKPEN_le
  have f7 := C_TOKPEN_W_le
  have f8 := C_TOKPEN_C4_le
  have f9 := C_TOKPEN_BT_le
  have f10 := C_UNUSED_LEN_le
  have f11 := C_UNUSED_DIST_le
  have f12 := C_CHAIN4_RATIO_le
  rw [slot.c_engine]
  step*
  · -- dna = 0, few 6-byte repeats: weights DP (4-byte chains)
    apply WP.spec_bind (Pₘ := fun (x : alloc.vec.Vec Std.U32) => x.length ≤ 34 * input.length)
    · repeat' (split <;> step*)
      all_goals exact engC_with_capacity_length _
    rintro clist1 hc1
    apply WP.spec_bind (Pₘ := fun _ => True)
    · repeat' (split <;> step*)
    rintro passes _
    apply WP.spec_bind (Pₘ := fun (x : Std.U32) => x.val ≤ 65536)
    · repeat' (split <;> step*)
      all_goals scalar_tac
    rintro tax htax
    apply WP.spec_bind (Pₘ := fun (x : Std.U32) => x.val ≤ 65536)
    · repeat' (split <;> step*)
      all_goals scalar_tac
    rintro ulen hulen
    apply WP.spec_bind (Pₘ := fun (x : Std.U32) => x.val ≤ 65536)
    · repeat' (split <;> step*)
      all_goals scalar_tac
    rintro udist hudist
    apply WP.spec_bind (Pₘ := fun _ => True)
    · repeat' (split <;> step*)
    rintro gmin _
    step*
    apply WP.spec_bind (Pₘ := fun (x : alloc.vec.Vec Std.U32 × Std.U32) => x.2.val ≤ 65536)
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
    apply WP.spec_bind (Pₘ := fun (x : alloc.vec.Vec Std.U32) => x.length ≤ 34 * input.length)
    · repeat' (split <;> step*)
      all_goals exact engC_with_capacity_length _
    rintro clist1 hc1
    apply WP.spec_bind (Pₘ := fun _ => True)
    · repeat' (split <;> step*)
    rintro passes _
    apply WP.spec_bind (Pₘ := fun (x : Std.U32) => x.val ≤ 65536)
    · repeat' (split <;> step*)
      all_goals scalar_tac
    rintro tax htax
    apply WP.spec_bind (Pₘ := fun (x : Std.U32) => x.val ≤ 65536)
    · repeat' (split <;> step*)
      all_goals scalar_tac
    rintro ulen hulen
    apply WP.spec_bind (Pₘ := fun (x : Std.U32) => x.val ≤ 65536)
    · repeat' (split <;> step*)
      all_goals scalar_tac
    rintro udist hudist
    apply WP.spec_bind (Pₘ := fun _ => True)
    · repeat' (split <;> step*)
    rintro gmin _
    step*
    apply WP.spec_bind (Pₘ := fun (x : alloc.vec.Vec Std.U32 × Std.U32) => x.2.val ≤ 65536)
    · repeat' (split <;> step*)
      all_goals scalar_tac
    rintro ⟨out1, tokpen⟩ htok
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · -- DNA
    apply WP.spec_bind (Pₘ := fun (x : alloc.vec.Vec Std.U32) => x.length ≤ 34 * input.length)
    · repeat' (split <;> step*)
      all_goals exact engC_with_capacity_length _
    rintro clist1 hc1
    apply WP.spec_bind (Pₘ := fun _ => True)
    · repeat' (split <;> step*)
    rintro passes _
    apply WP.spec_bind (Pₘ := fun (x : Std.U32) => x.val ≤ 65536)
    · repeat' (split <;> step*)
      all_goals scalar_tac
    rintro tax htax
    apply WP.spec_bind (Pₘ := fun (x : Std.U32) => x.val ≤ 65536)
    · repeat' (split <;> step*)
      all_goals scalar_tac
    rintro ulen hulen
    apply WP.spec_bind (Pₘ := fun (x : Std.U32) => x.val ≤ 65536)
    · repeat' (split <;> step*)
      all_goals scalar_tac
    rintro udist hudist
    apply WP.spec_bind (Pₘ := fun _ => True)
    · repeat' (split <;> step*)
    rintro gmin _
    step*
    apply WP.spec_bind (Pₘ := fun (x : alloc.vec.Vec Std.U32 × Std.U32) => x.2.val ≤ 65536)
    · repeat' (split <;> step*)
      all_goals scalar_tac
    rintro ⟨out1, tokpen⟩ htok
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac

/-! # sec_spine_top (owner: spine) -- plan_cfg, make_plan and the obligation.
Uses the exported engine specs a_engine_spec, b_engine_spec, c_engine_spec (frozen statements;
develop against /root/66/work/pk/s/stubs/iface_engines.lean). -/

/-! ## Configuration facts (the only place `slot.CFG` is unfolded; stated as bounds, so retuning a
knob keeps them true as long as every knob stays `≤ 65536` and engine A's `skip` stays `≥ 3`) -/

-- [spine_top] fact: every knob of every configuration row is at most 65536 (the engine specs' bound)
theorem spine_CFG_le : ∀ r ∈ slot.CFG.val, ∀ x ∈ r.val, x.val ≤ 65536 := by
  unfold slot.CFG; decide

-- [spine_top] fact: a row for engine A (entry 0 = 0) has `skip` (entry 2) at least 3
theorem spine_CFG_skip : ∀ r ∈ slot.CFG.val, (r.val[0]!).val = 0 → 3 ≤ (r.val[2]!).val := by
  unfold slot.CFG; decide

-- [spine_top] helper: a knob read from a row (the post of `Array.index_usize`) is bounded
theorem spine_knob_le {m : Std.Usize} {r : Array Std.Usize m} (hr : ∀ x ∈ r.val, x.val ≤ 65536)
    {x : Std.Usize} {j : Nat} {hj : j < r.val.length} (hx : x = r.val[j]) : x.val ≤ 65536 := by
  subst hx; exact hr _ (List.getElem_mem _)

-- [spine_top] helper: engine A's `skip` knob (entry 2 of a row whose entry 0 was read as 0)
theorem spine_knob_skip {m : Std.Usize} {r : Array Std.Usize m}
    (hs : (r.val[0]!).val = 0 → 3 ≤ (r.val[2]!).val)
    {x0 x2 : Std.Usize} {h0 : 0 < r.val.length} {h2 : 2 < r.val.length}
    (hx0 : x0 = r.val[0]) (hz : x0 = 0#usize) (hx2 : x2 = r.val[2]) : 3 ≤ x2.val := by
  rw [getElem!_pos r.val 0 h0, getElem!_pos r.val 2 h2, ← hx0, ← hx2, hz] at hs
  exact hs rfl

-- @owner spine_top @status DONE @note needs a_engine_spec, b_engine_spec, c_engine_spec (knob hypotheses from a CFG fact: every entry <= 65536, by decide)
-- [spine_top] fn callees: a_engine b_engine c_engine zeros
@[local step]
theorem plan_cfg_spec (input : Slice Std.U8) (k) (hn : input.length < 67108864) :
    slot.plan_cfg input k ⦃ fun _ => True ⦄ := by
  rw [slot.plan_cfg]
  step*
  -- left: the knob hypotheses of the engine specs, facts about the row `c = CFG[k % 16]`
  all_goals
    have hc : c ∈ slot.CFG.val := by rw [c_post]; exact List.getElem_mem _
    first
    | exact spine_knob_le (spine_CFG_le c hc) (by assumption)
    | exact spine_knob_skip (spine_CFG_skip c hc) (by assumption) (by assumption) (by assumption)

-- [spine_top] helper: make_plan below the input cap of the engine specs (what R3 reduces make_plan_spec to)
theorem spine_make_plan_lt_spec (input : Slice Std.U8) (hn : input.length < 67108864) :
    slot.make_plan input ⦃ fun _ => True ⦄ := by
  rw [slot.make_plan]
  step*

-- @owner spine_top @status BLOCKED(R3) @note plan_cfg needs input.length < 2^26: R3 adds `if input.len() >= 67108864 { return Vec::new(); }` at the top of make_plan
-- [spine_top] fn callees: classify plan_cfg
-- Unprovable on the snapshot: for `input.length ≥ 2^26` the engines overflow (e.g. a_engine's
-- `n * 3 + 16`). With R3 in the Rust, the proof is `rw [slot.make_plan]; step*`.
@[local step]
theorem make_plan_spec (input) : slot.make_plan input ⦃ fun _ => True ⦄ := by
  rw [slot.make_plan]
  step*

/-! ## The obligation (pkB verbatim) -/

theorem s_parse_spec (input : Slice Std.U8) (out : Slice Std.U32)
    (hlen : input.length ≤ out.length) :
    slot.s_parse input out ⦃ fun r =>
      r.1.val ≤ input.length ∧
      r.2.length = out.length ∧
      LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
  rw [slot.s_parse]
  step*
  refine ⟨by assumption, by assumption, ?_⟩
  unfold LZ77.Valid
  assumption

end Submission

namespace Submission
open Aeneas Aeneas.Std Result ControlFlow
open LZ77 (toks bytes)
set_option maxRecDepth 8192
set_option maxHeartbeats 4000000
set_option hygiene false in
local notation "T9!" q0__:max q1__:max => (by
  (
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun l => cap.val - l.val)
    (inv := fun l => l.val ≤ cap.val ∧ LZ77.Matches input a.val b.val l.val)
  · rintro l ⟨hle, hinv⟩
    simp only [q1__]
    split
    case isTrue hlt =>
      have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
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
namespace EH
open Aeneas Aeneas.Std Result ControlFlow
set_option maxRecDepth 8192
set_option maxHeartbeats 4000000
set_option linter.unusedTactic false
set_option linter.unreachableTactic false
set_option linter.unusedSimpArgs false
open LZ77 (toks bytes bytes_length bytes_getElem! Matches emit_lit emit_match ite_ok)
theorem spec_ite_cut {α : Type} (c : Prop) [Decidable c] (a b : Result α) (Q : α → Prop)
    (ha : c → a ⦃ Q ⦄) (hb : ¬c → b ⦃ Q ⦄) : (if c then a else b) ⦃ Q ⦄ := by
  by_cases h : c
  · rw [if_pos h]; exact ha h
  · rw [if_neg h]; exact hb h
set_option hygiene false in
local notation "T14!" q0__:max => (by
  rw [q0__]
  try simp only [ite_ok]
  step*
  all_goals (repeat (split <;> step*))
  all_goals scalar_tac)
@[local step]
theorem get_spec (v : Slice Std.U32) (i : Std.Usize) :
    slot.h_get v i ⦃ fun _ => True ⦄ := T14! slot.h_get
@[local step]
theorem set_spec (v : Slice Std.U32) (i : Std.Usize) (x : Std.U32) :
    slot.h_set v i x ⦃ fun _ => True ⦄ := T14! slot.h_set
set_option hygiene false in
local notation "T15!" q0__:max => (by
  rw [q0__]
  simp only [lift, ite_ok, alloc.vec.Vec.deref_mut, bind_tc_ok]
  step*
  all_goals (repeat (split <;> step*))
  all_goals scalar_tac)
@[local step]
theorem bump_spec (v : Slice Std.U32) (i : Std.Usize) (by0 : Std.U32) :
    slot.h_bump v i by0 ⦃ fun _ => True ⦄ := T15! slot.h_bump
@[local step]
theorem set64_spec (v : Slice Std.U64) (i : Std.Usize) (x : Std.U64) :
    slot.h_set64 v i x ⦃ fun _ => True ⦄ := T14! slot.h_set64
@[local step]
theorem get8_spec (v : Slice Std.U8) (i : Std.Usize) :
    slot.h_get8 v i ⦃ fun _ => True ⦄ := T14! slot.h_get8
@[local step]
theorem byte_at_spec (input : Slice Std.U8) (i : Std.Usize) :
    slot.h_byte_at input i ⦃ fun _ => True ⦄ := T14! slot.h_byte_at
@[local step]
theorem setc_spec (a : Array Std.U32 65536#usize) (i : Std.Usize) (x : Std.U32) :
    slot.h_setc a i x ⦃ fun _ => True ⦄ := T14! slot.h_setc
theorem filled_loop0_spec (x : Std.U32) (v0 : alloc.vec.Vec Std.U32) (n8 i0 : Std.Usize)
    (hn8 : 8 * n8.val ≤ Std.Usize.max) (h0 : v0.length = 8 * i0.val) (hi : i0.val ≤ n8.val) :
    slot.h_filled_loop0 x v0 n8 i0 ⦃ fun r => r.length = 8 * n8.val ⦄ := by
  rw [slot.h_filled_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun s => n8.val - s.2.val)
    (inv := fun s => s.1.length = 8 * s.2.val ∧ s.2.val ≤ n8.val)
  · rintro ⟨v, i⟩ ⟨hv, hle⟩
    simp only at hv hle
    simp only [slot.h_filled_loop0.body]
    split
    case isTrue hlt =>
      step*
      all_goals (simp_all; scalar_tac)
    case isFalse hge =>
      simp only [Std.WP.spec_ok]
      scalar_tac
  · exact ⟨h0, hi⟩
theorem filled_loop1_spec (n : Std.Usize) (x : Std.U32) (v0 : alloc.vec.Vec Std.U32)
    (j0 : Std.Usize) (h0 : v0.length = j0.val) (hj : j0.val ≤ n.val) :
    slot.h_filled_loop1 n x v0 j0 ⦃ fun r => r.length = n.val ⦄ := by
  rw [slot.h_filled_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun s => n.val - s.2.val)
    (inv := fun s => s.1.length = s.2.val ∧ s.2.val ≤ n.val)
  · rintro ⟨v, j⟩ ⟨hv, hle⟩
    simp only at hv hle
    simp only [slot.h_filled_loop1.body]
    split
    case isTrue hlt =>
      step*
      simp_all
      scalar_tac
    case isFalse hge =>
      simp only [Std.WP.spec_ok]
      scalar_tac
  · exact ⟨h0, hj⟩
@[local step]
theorem filled_spec (n : Std.Usize) (x : Std.U32) :
    slot.h_filled n x ⦃ fun r => r.length = n.val ⦄ := by
  rw [slot.h_filled]
  step*
  apply Std.WP.spec_bind (filled_loop0_spec x _ n8 0#usize (by scalar_tac)
    (by simp [alloc.vec.Vec.with_capacity]) (by scalar_tac))
  intro v1 hv1
  step*
  exact filled_loop1_spec n x v1 j (by scalar_tac) (by scalar_tac)
@[local step]
theorem push_guarded_spec (v : alloc.vec.Vec Std.U32) (x : Std.U32) :
    slot.h_push_guarded v x ⦃ fun _ => True ⦄ := T14! slot.h_push_guarded
@[local step]
theorem sel_spec (f : Std.Usize) (a : Std.Usize) (b : Std.Usize) :
    slot.h_sel f a b ⦃ fun _ => True ⦄ := T14! slot.h_sel
@[local step]
theorem sel32_spec (f : Std.Usize) (a : Std.U32) (b : Std.U32) :
    slot.h_sel32 f a b ⦃ fun _ => True ⦄ := T14! slot.h_sel32
@[local step]
theorem sel64_spec (f : Std.Usize) (a : Std.U64) (b : Std.U64) :
    slot.h_sel64 f a b ⦃ fun _ => True ⦄ := T14! slot.h_sel64
@[local step]
theorem ge_spec (a : Std.Usize) (b : Std.Usize) :
    slot.h_ge a b ⦃ fun _ => True ⦄ := T14! slot.h_ge
@[local step]
theorem lt_spec (a : Std.Usize) (b : Std.Usize) :
    slot.h_lt a b ⦃ fun _ => True ⦄ := T14! slot.h_lt
@[local step]
theorem eq_spec (a : Std.Usize) (b : Std.Usize) :
    slot.h_eq a b ⦃ fun _ => True ⦄ := T14! slot.h_eq
@[local step]
theorem lt32_spec (a : Std.U32) (b : Std.U32) :
    slot.h_lt32 a b ⦃ fun _ => True ⦄ := T14! slot.h_lt32
@[local step]
theorem lt64_spec (a : Std.U64) (b : Std.U64) :
    slot.h_lt64 a b ⦃ fun _ => True ⦄ := T14! slot.h_lt64
@[local step]
theorem umin_spec (a : Std.Usize) (b : Std.Usize) :
    slot.h_umin a b ⦃ fun _ => True ⦄ := T14! slot.h_umin
@[local step]
theorem umax_spec (a : Std.Usize) (b : Std.Usize) :
    slot.h_umax a b ⦃ fun _ => True ⦄ := T14! slot.h_umax
@[local step]
theorem eq64_spec (a : Std.U64) (b : Std.U64) :
    slot.h_eq64 a b ⦃ fun _ => True ⦄ := T14! slot.h_eq64
@[local step]
theorem umin64_spec (a : Std.U64) (b : Std.U64) :
    slot.h_umin64 a b ⦃ fun _ => True ⦄ := T14! slot.h_umin64
@[local step]
theorem push_if_spec (v : alloc.vec.Vec Std.U32) (f : Std.Usize) (x : Std.U32) :
    slot.h_push_if v f x ⦃ fun _ => True ⦄ := T14! slot.h_push_if
@[local step]
theorem dslot_spec (d : Std.Usize) :
    slot.h_dslot d ⦃ fun _ => True ⦄ := T15! slot.h_dslot
@[local step]
theorem pack_m_spec (len : Std.Usize) (d : Std.Usize) :
    slot.h_pack_m len d ⦃ fun _ => True ⦄ := T15! slot.h_pack_m
@[local step]
theorem push_m_spec (v : alloc.vec.Vec Std.U32) (f : Std.Usize) (len : Std.Usize) (d : Std.Usize) :
    slot.h_push_m v f len d ⦃ fun _ => True ⦄ := T14! slot.h_push_m
@[local step]
theorem push_slot1_spec (mc : alloc.vec.Vec Std.U32) (m0 : Std.Usize) (len : Std.Usize) (d : Std.Usize) :
    slot.h_push_slot1 mc m0 len d ⦃ fun _ => True ⦄ := T15! slot.h_push_slot1
@[local step]
theorem push_slot_spec (mc : alloc.vec.Vec Std.U32) (m0 : Std.Usize) (f : Std.Usize) (len : Std.Usize) (d : Std.Usize) :
    slot.h_push_slot mc m0 f len d ⦃ fun _ => True ⦄ := T14! slot.h_push_slot
@[local step]
theorem clamp_step_spec (l room : Std.Usize) :
    slot.h_clamp_step l room ⦃ fun r => 1 ≤ r.val ∧ (r.val = 1 ∨ r.val ≤ room.val) ⦄ := by
  rw [slot.h_clamp_step]
  step*
@[local step]
theorem clamp1_spec (l room : Std.Usize) :
    slot.h_clamp1 l room ⦃ fun r => 1 ≤ r.val ∧ (r.val = 1 ∨ r.val ≤ room.val) ⦄ := by
  rw [slot.h_clamp1]
  step*
@[local step]
theorem nz64_spec (x : Std.U64) : slot.h_nz64 x ⦃ fun r => 0 < r.val ⦄ := by
  rw [slot.h_nz64]
  step*
theorem match_len_loop_spec (input : Slice Std.U8) (a b cap l0 : Std.Usize)
    (ha : a.val + cap.val ≤ input.length) (hb : b.val + cap.val ≤ input.length)
    (hl0 : l0.val ≤ cap.val) (h0 : Matches input a.val b.val l0.val) :
    slot.h_match_len_loop input a b cap l0 ⦃ fun l =>
      l.val ≤ cap.val ∧ Matches input a.val b.val l.val ⦄ := T9! slot.h_match_len_loop slot.h_match_len_loop.body
@[local step]
theorem match_len_spec (input : Slice Std.U8) (a b cap : Std.Usize)
    (ha : a.val + cap.val ≤ input.length) (hb : b.val + cap.val ≤ input.length) :
    slot.h_match_len input a b cap ⦃ fun l =>
      l.val ≤ cap.val ∧ Matches input a.val b.val l.val ⦄ := T10!
theorem verified_spec (input : Slice Std.U8) (pos d ch : Std.Usize) :
    slot.h_verified input pos d ch ⦃ fun b => b = true →
      3 ≤ ch.val ∧ ch.val ≤ 258 ∧ 1 ≤ d.val ∧ d.val ≤ 32768 ∧ d.val ≤ pos.val ∧
      pos.val + ch.val ≤ input.length ∧ Matches input (pos.val - d.val) pos.val ch.val ⦄ := by
  rw [slot.h_verified]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  step*
  intro hv
  have hv' : ch.val ≤ v.val := by simpa using hv
  refine ⟨by scalar_tac, by scalar_tac, by scalar_tac, by scalar_tac, by scalar_tac,
    by scalar_tac, ?_⟩
  rw [show pos.val - d.val = i1.val by scalar_tac]
  exact Matches.mono v_post2 hv'
theorem emit_all_loop_spec (input : Slice Std.U8) (out0 : Slice Std.U32)
    (plan : Slice Std.U32) (n k0 ntok0 : Std.Usize)
    (hn : n.val = input.length) (hout : input.length ≤ out0.length)
    (hk : k0.val ≤ n.val) (hntok : ntok0.val ≤ k0.val)
    (hdec : LZ77.decode (toks out0 ntok0.val) = some ((bytes input).take k0.val)) :
    slot.h_emit_all_loop input out0 plan n k0 ntok0 ⦃ fun r =>
      r.1.val ≤ input.length ∧ r.2.length = out0.length ∧
      LZ77.decode (toks r.2 r.1.val) = some (bytes input) ⦄ := by
  rw [slot.h_emit_all_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => n.val - s.2.1.val)
    (inv := fun s =>
      s.2.1.val ≤ n.val ∧ s.2.2.val ≤ s.2.1.val ∧ s.1.length = out0.length ∧
      LZ77.decode (toks s.1 s.2.2.val) = some ((bytes input).take s.2.1.val))
  · rintro ⟨out, k, ntok⟩ ⟨hkn, hnt, hlen, hde⟩
    simp only at hkn hnt hlen hde
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.h_emit_all_loop.body]
    split
    case isTrue hklt =>
      have hntok_lt : ntok.val < out.length := by scalar_tac
      step*
      apply Std.WP.spec_bind (verified_spec input k d ch)
      intro b hb
      split
      case isTrue hbt =>
        obtain ⟨hch3, hch258, hd1, hdmax, hdpos, hend, hmatch⟩ := hb hbt
        step*
        have htok : i7.val = LZ77.mkMatch d.val ch.val := by
          simp only [LZ77.mkMatch, LZ77.MATCH_BASE, i7_post, i4_post, i3_post]
          scalar_tac
        refine ⟨by scalar_tac, by scalar_tac,
          by rw [s_post]; simpa [Std.Slice.set_val_eq] using hlen, ?_, by scalar_tac⟩
        rw [s_post, show ntok1.val = ntok.val + 1 by scalar_tac,
          show k1.val = k.val + ch.val by scalar_tac]
        exact emit_match input out ntok k.val d.val ch.val i7 hde hntok_lt hd1 hdpos hdmax
          hch3 hch258 hend hmatch htok
      case isFalse hbf =>
        have hposlen : k.val < input.length := by scalar_tac
        step*
        have hval : i2.val = (bytes input)[k.val]! := by
          rw [bytes_getElem! input k.val hposlen, i2_post, Std.U8.cast_U32_val_eq, i1_post]
        refine ⟨by scalar_tac, by scalar_tac,
          by rw [s_post]; simpa [Std.Slice.set_val_eq] using hlen, ?_, by scalar_tac⟩
        rw [s_post, show ntok1.val = ntok.val + 1 by scalar_tac,
          show k1.val = k.val + 1 by scalar_tac]
        exact emit_lit input out ntok k.val i2 hde hposlen hntok_lt hval
    case isFalse hge =>
      have hkn' : k.val = input.length := by scalar_tac
      refine ⟨by scalar_tac, hlen, ?_⟩
      rw [hde, hkn']
      simp
  · exact ⟨hk, hntok, rfl, hdec⟩
@[local step]
theorem emit_all_spec (input : Slice Std.U8) (out : Slice Std.U32)
    (plan : Slice Std.U32) (hout : input.length ≤ out.length) :
    slot.h_emit_all input out plan ⦃ fun r =>
      r.1.val ≤ input.length ∧ r.2.length = out.length ∧
      LZ77.decode (toks r.2 r.1.val) = some (bytes input) ⦄ := by
  rw [slot.h_emit_all]
  exact emit_all_loop_spec input out plan _ 0#usize 0#usize
    (by simp) hout (by scalar_tac) (by scalar_tac) (by simp [toks, LZ77.decode])
@[local step]
theorem le64_spec (input : Slice Std.U8) (p : Std.Usize) :
    slot.h_le64 input p ⦃ fun _ => True ⦄ := T15! slot.h_le64
@[local step]
theorem first_diff_spec (x : Std.U64) (y : Std.U64) :
    slot.h_first_diff x y ⦃ fun _ => True ⦄ := T15! slot.h_first_diff
@[local step]
theorem hash4_spec (input : Slice Std.U8) (p : Std.Usize) :
    slot.h_hash4 input p ⦃ fun _ => True ⦄ := T15! slot.h_hash4
@[local step]
theorem hash3_spec (input : Slice Std.U8) (p : Std.Usize) :
    slot.h_hash3 input p ⦃ fun _ => True ⦄ := T15! slot.h_hash3
@[local step]
theorem dextra_spec (s : Std.Usize) :
    slot.h_dextra s ⦃ fun _ => True ⦄ := T15! slot.h_dextra
@[local step]
theorem lcode_spec (l : Std.Usize) :
    slot.h_lcode l ⦃ fun r => r.val ≤ 28 ⦄ := by
  rw [slot.h_lcode]
  simp only [lift, ite_ok, alloc.vec.Vec.deref_mut, bind_tc_ok]
  step*
  all_goals (repeat (split <;> try step*))
  all_goals (try split_ifs)
  all_goals first
    | scalar_tac
    | (simp only [core.num.Usize.wrapping_sub_val_eq, UScalar.size, UScalarTy.numBits]
       cases System.Platform.numBits_eq <;> simp_all <;> scalar_tac)
@[local step]
theorem lextra_spec (c : Std.Usize) :
    slot.h_lextra c ⦃ fun _ => True ⦄ := T15! slot.h_lextra
@[local step]
theorem fixed_len_spec (s : Std.Usize) :
    slot.h_fixed_len s ⦃ fun _ => True ⦄ := T14! slot.h_fixed_len
@[local step]
theorem ext_len_loop_spec (input : Slice Std.U8) (a : Std.Usize) (b : Std.Usize) (lim : Std.Usize) (l : Std.Usize) (it : Std.Usize) :
    slot.h_ext_len_loop input a b lim l it ⦃ fun _ => True ⦄ := by
  rw [slot.h_ext_len_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 300 - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨l1, it1⟩ _
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.h_ext_len_loop.body, lift]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem ext_len_spec (input : Slice Std.U8) (a : Std.Usize) (b : Std.Usize) (from0 : Std.Usize) (cap : Std.Usize) :
    slot.h_ext_len input a b from0 cap ⦃ fun _ => True ⦄ := T15! slot.h_ext_len
@[local step]
theorem ext_if_spec (input : Slice Std.U8) (f : Std.Usize) (a : Std.Usize) (b : Std.Usize) (from0 : Std.Usize) (cap : Std.Usize) (dflt : Std.Usize) :
    slot.h_ext_if input f a b from0 cap dflt ⦃ fun _ => True ⦄ := T14! slot.h_ext_if
@[local step]
theorem le64_tail_loop_spec (input : Slice Std.U8) (p : Std.Usize) (x : Std.U64) (j : Std.Usize) :
    slot.h_le64_tail_loop input p x j ⦃ fun _ => True ⦄ := by
  rw [slot.h_le64_tail_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 8 - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨x1, j1⟩ _
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.h_le64_tail_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem le64_tail_spec (input : Slice Std.U8) (p : Std.Usize) :
    slot.h_le64_tail input p ⦃ fun _ => True ⦄ := T14! slot.h_le64_tail
@[local step]
theorem le64z_spec (input : Slice Std.U8) (p : Std.Usize) :
    slot.h_le64z input p ⦃ fun _ => True ⦄ := T14! slot.h_le64z
@[local step]
theorem byte_lt_spec (x : Std.U64) (y : Std.U64) (k : Std.Usize) :
    slot.h_byte_lt x y k ⦃ fun _ => True ⦄ := T15! slot.h_byte_lt
@[local step]
theorem lcp_words_loop_spec (input : Slice Std.U8) (a : Std.Usize) (b : Std.Usize) (lim : Std.Usize) (l : Std.Usize) (it : Std.Usize) (z : Std.U64) (x : Std.U64) :
    slot.h_lcp_words_loop input a b lim l it z x ⦃ fun _ => True ⦄ := by
  rw [slot.h_lcp_words_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 40 - qq9.2.1.val)
    (inv := fun _ => True)
  · rintro ⟨l1, it1, z1, x1⟩ _
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.h_lcp_words_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem lcp_words_spec (input : Slice Std.U8) (a : Std.Usize) (b : Std.Usize) (l0 : Std.Usize) (lim : Std.Usize) :
    slot.h_lcp_words input a b l0 lim ⦃ fun _ => True ⦄ := T15! slot.h_lcp_words
@[local step]
theorem ext_words_spec (input : Slice Std.U8) (same : Std.Usize) (a : Std.Usize) (b : Std.Usize) (l0 : Std.Usize) (x : Std.U64) (y : Std.U64) (lim : Std.Usize) :
    slot.h_ext_words input same a b l0 x y lim ⦃ fun _ => True ⦄ := T15! slot.h_ext_words
@[local step]
theorem bt_walk_loop_spec (input : Slice Std.U8) (child : Array Std.U32 65536#usize) (pos : Std.Usize) (rec : Std.Usize) (maxd : Std.Usize) (mc : alloc.vec.Vec Std.U32) (m0 : Std.Usize) (plt : Std.Usize) (pgt : Std.Usize) (cur : Std.Usize) (ltl : Std.Usize) (gtl : Std.Usize) (len : Std.Usize) (best : Std.Usize) (wl : Std.Usize) (wd : Std.Usize) (depth : Std.Usize) (go : Std.Usize) (lim : Std.Usize) (stop : Std.Usize) (kcur : Std.Usize) (kl : Std.Usize) :
    slot.h_bt_walk_loop input child pos rec maxd mc m0 plt pgt cur ltl gtl len best wl wd depth go lim stop kcur kl ⦃ fun _ => True ⦄ := by
  rw [slot.h_bt_walk_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => maxd.val - qq9.2.2.2.2.2.2.2.2.2.2.2.1.val)
    (inv := fun _ => True)
  · rintro ⟨child1, mc1, plt1, pgt1, cur1, ltl1, gtl1, len1, best1, wl1, wd1, depth1, go1⟩ _
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.h_bt_walk_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem bt_walk_spec (input : Slice Std.U8) (child : Array Std.U32 65536#usize) (root : Std.Usize) (pos : Std.Usize) (cap : Std.Usize) (best0 : Std.Usize) (rec : Std.Usize) (maxd : Std.Usize) (hint : Std.Usize) (mc : alloc.vec.Vec Std.U32) (m0 : Std.Usize) :
    slot.h_bt_walk input child root pos cap best0 rec maxd hint mc m0 ⦃ fun _ => True ⦄ := T15! slot.h_bt_walk
@[local step]
theorem sks_rec_spec (gap : Std.Usize) :
    slot.h_sks_rec gap ⦃ fun _ => True ⦄ := T15! slot.h_sks_rec
@[local step]
theorem find_pos_spec (input : Slice Std.U8) (h4 : Array Std.U32 65536#usize) (h3 : Array Std.U32 131072#usize) (child : Array Std.U32 65536#usize) (mc : alloc.vec.Vec Std.U32) (st : Array Std.Usize 4#usize) (pos : Std.Usize) (maxd : Std.Usize) :
    slot.h_find_pos input h4 h3 child mc st pos maxd ⦃ fun _ => True ⦄ := T15! slot.h_find_pos
@[local step]
theorem find_all_loop_spec (input : Slice Std.U8) (mstart : alloc.vec.Vec Std.U32) (mc : alloc.vec.Vec Std.U32) (maxd : Std.Usize) (n : Std.Usize) (h4 : Array Std.U32 65536#usize) (h3 : Array Std.U32 131072#usize) (child : Array Std.U32 65536#usize) (st : Array Std.Usize 4#usize) (pos : Std.Usize) :
    slot.h_find_all_loop input mstart mc maxd n h4 h3 child st pos ⦃ fun _ => True ⦄ := by
  rw [slot.h_find_all_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => n.val - qq9.2.2.2.2.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨mstart1, mc1, h41, h31, child1, st1, pos1⟩ _
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.h_find_all_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem find_all_spec (input : Slice Std.U8) (mstart : alloc.vec.Vec Std.U32) (mc : alloc.vec.Vec Std.U32) (maxd : Std.Usize) :
    slot.h_find_all input mstart mc maxd ⦃ fun _ => True ⦄ := T15! slot.h_find_all
@[local step]
theorem find_spare_spec (input : Slice Std.U8) (f : Std.Usize) :
    slot.h_find_spare input f ⦃ fun _ => True ⦄ := T14! slot.h_find_spare
@[local step]
theorem bucket_end_spec (l : Std.Usize) :
    slot.h_bucket_end l ⦃ fun _ => True ⦄ := T15! slot.h_bucket_end
@[local step]
theorem build_bend_loop_spec (bend : Array Std.U32 512#usize) (l : Std.Usize) :
    slot.h_build_bend_loop bend l ⦃ fun _ => True ⦄ := by
  rw [slot.h_build_bend_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 259 - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨bend1, l1⟩ _
    simp only [slot.h_build_bend_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem build_bend_spec (bend : Array Std.U32 512#usize) :
    slot.h_build_bend bend ⦃ fun _ => True ⦄ := T14! slot.h_build_bend
@[local step]
theorem lg5_spec (w : Std.Usize) :
    slot.h_lg5 w ⦃ fun _ => True ⦄ := T15! slot.h_lg5
@[local step]
theorem load_ct_loop0_spec (tbl : Slice Std.U32) (toff : Std.Usize) (ct : Array Std.U32 1024#usize) (lam : Std.U32) (x : Std.Usize) :
    slot.h_load_ct_loop0 tbl toff ct lam x ⦃ fun _ => True ⦄ := by
  rw [slot.h_load_ct_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 259 - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨ct1, x1⟩ _
    simp only [slot.h_load_ct_loop0.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem load_ct_loop1_spec (tbl : Slice Std.U32) (toff : Std.Usize) (ct : Array Std.U32 1024#usize) (s : Std.Usize) :
    slot.h_load_ct_loop1 tbl toff ct s ⦃ fun _ => True ⦄ := by
  rw [slot.h_load_ct_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 30 - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨ct1, s1⟩ _
    simp only [slot.h_load_ct_loop1.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem load_ct_loop2_spec (tbl : Slice Std.U32) (toff : Std.Usize) (ct : Array Std.U32 1024#usize) (lam : Std.U32) (c : Std.Usize) :
    slot.h_load_ct_loop2 tbl toff ct lam c ⦃ fun _ => True ⦄ := by
  rw [slot.h_load_ct_loop2]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 256 - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨ct1, c1⟩ _
    simp only [slot.h_load_ct_loop2.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem load_ct_spec (tbl : Slice Std.U32) (toff : Std.Usize) (ct : Array Std.U32 1024#usize) (lam : Std.U32) :
    slot.h_load_ct tbl toff ct lam ⦃ fun _ => True ⦄ := T14! slot.h_load_ct
@[local step]
theorem rm_update_spec (rm : Array Std.U64 4096#usize) (i : Std.Usize) (c : Std.U64) :
    slot.h_rm_update rm i c ⦃ fun _ => True ⦄ := T15! slot.h_rm_update
@[local step]
theorem rm_update3_spec (rm : Array Std.U64 4096#usize) (i : Std.Usize) (c : Std.U64) :
    slot.h_rm_update3 rm i c ⦃ fun _ => True ⦄ := T15! slot.h_rm_update3
@[local step]
theorem rm_upd_spec (f : Std.Usize) (rm : Array Std.U64 4096#usize) (i : Std.Usize) (c : Std.U64) :
    slot.h_rm_upd f rm i c ⦃ fun _ => True ⦄ := T14! slot.h_rm_upd
@[local step]
theorem bkt_val_spec (rm : Array Std.U64 4096#usize) (ct : Array Std.U32 1024#usize) (i : Std.Usize) (x : Std.Usize) (e : Std.Usize) (dcs : Std.U64) :
    slot.h_bkt_val rm ct i x e dcs ⦃ fun _ => True ⦄ := T15! slot.h_bkt_val
@[local step]
theorem query_spec (x : Std.Usize) (y : Std.Usize) (k : Std.Usize) (slot0 : Std.Usize) :
    slot.h_query x y k slot0 ⦃ fun _ => True ⦄ := T15! slot.h_query
@[local step]
theorem prune_short_loop_spec (rm : Array Std.U64 4096#usize) (ct : Array Std.U32 1024#usize) (i : Std.Usize) (hi : Std.Usize) (dcs : Std.U64) (slot0 : Std.Usize) (keep : Std.Usize) (items : alloc.vec.Vec Std.U32) (best : Std.U64) (x : Std.Usize) :
    slot.h_prune_short_loop rm ct i hi dcs slot0 keep items best x ⦃ fun _ => True ⦄ := by
  rw [slot.h_prune_short_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 11 - qq9.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨items1, best1, x1⟩ _
    simp only [slot.h_prune_short_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem prune_short_spec (rm : Array Std.U64 4096#usize) (ct : Array Std.U32 1024#usize) (i : Std.Usize) (lo : Std.Usize) (hi : Std.Usize) (dcs : Std.U64) (slot0 : Std.Usize) (best0 : Std.U64) (keep : Std.Usize) (items : alloc.vec.Vec Std.U32) :
    slot.h_prune_short rm ct i lo hi dcs slot0 best0 keep items ⦃ fun _ => True ⦄ := T14! slot.h_prune_short
@[local step]
theorem prune_bkt_loop_spec (rm : Array Std.U64 4096#usize) (ct : Array Std.U32 1024#usize) (bend : Array Std.U32 512#usize) (i : Std.Usize) (hi : Std.Usize) (dcs : Std.U64) (slot0 : Std.Usize) (keep : Std.Usize) (items : alloc.vec.Vec Std.U32) (best : Std.U64) (x : Std.Usize) (it : Std.Usize) :
    slot.h_prune_bkt_loop rm ct bend i hi dcs slot0 keep items best x it ⦃ fun _ => True ⦄ := by
  rw [slot.h_prune_bkt_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 32 - qq9.2.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨items1, best1, x1, it1⟩ _
    simp only [slot.h_prune_bkt_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem prune_bkt_spec (rm : Array Std.U64 4096#usize) (ct : Array Std.U32 1024#usize) (bend : Array Std.U32 512#usize) (i : Std.Usize) (lo : Std.Usize) (hi : Std.Usize) (dcs : Std.U64) (slot0 : Std.Usize) (best0 : Std.U64) (keep : Std.Usize) (items : alloc.vec.Vec Std.U32) :
    slot.h_prune_bkt rm ct bend i lo hi dcs slot0 best0 keep items ⦃ fun _ => True ⦄ := T14! slot.h_prune_bkt
@[local step]
theorem prune_pos_loop_spec (rm : Array Std.U64 4096#usize) (ct : Array Std.U32 1024#usize) (bend : Array Std.U32 512#usize) (mc : Slice Std.U32) (me : Std.Usize) (i : Std.Usize) (chw : Std.Usize) (msub : Std.U32) (keep : Std.Usize) (items : alloc.vec.Vec Std.U32) (best : Std.U64) (k : Std.Usize) (lo : Std.Usize) :
    slot.h_prune_pos_loop rm ct bend mc me i chw msub keep items best k lo ⦃ fun _ => True ⦄ := by
  rw [slot.h_prune_pos_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => me.val - qq9.2.2.1.val)
    (inv := fun _ => True)
  · rintro ⟨items1, best1, k1, lo1⟩ _
    simp only [slot.h_prune_pos_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem prune_pos_spec (rm : Array Std.U64 4096#usize) (ct : Array Std.U32 1024#usize) (bend : Array Std.U32 512#usize) (mc : Slice Std.U32) (ms : Std.Usize) (me : Std.Usize) (i : Std.Usize) (lit : Std.U64) (chw : Std.Usize) (msub : Std.U32) (keep : Std.Usize) (items : alloc.vec.Vec Std.U32) :
    slot.h_prune_pos rm ct bend mc ms me i lit chw msub keep items ⦃ fun _ => True ⦄ := T15! slot.h_prune_pos
@[local step]
theorem relax_short_loop_spec (rm : Array Std.U64 4096#usize) (ct : Array Std.U32 1024#usize) (i : Std.Usize) (hi : Std.Usize) (dcs : Std.U64) (best : Std.U64) (x : Std.Usize) :
    slot.h_relax_short_loop rm ct i hi dcs best x ⦃ fun _ => True ⦄ := by
  rw [slot.h_relax_short_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 11 - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨best1, x1⟩ _
    simp only [slot.h_relax_short_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem relax_short_spec (rm : Array Std.U64 4096#usize) (ct : Array Std.U32 1024#usize) (i : Std.Usize) (lo : Std.Usize) (hi : Std.Usize) (dcs : Std.U64) (best0 : Std.U64) :
    slot.h_relax_short rm ct i lo hi dcs best0 ⦃ fun _ => True ⦄ := T14! slot.h_relax_short
@[local step]
theorem relax_bkt_loop_spec (rm : Array Std.U64 4096#usize) (ct : Array Std.U32 1024#usize) (bend : Array Std.U32 512#usize) (i : Std.Usize) (hi : Std.Usize) (dcs : Std.U64) (best : Std.U64) (x : Std.Usize) (it : Std.Usize) :
    slot.h_relax_bkt_loop rm ct bend i hi dcs best x it ⦃ fun _ => True ⦄ := by
  rw [slot.h_relax_bkt_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 32 - qq9.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨best1, x1, it1⟩ _
    simp only [slot.h_relax_bkt_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem relax_bkt_spec (rm : Array Std.U64 4096#usize) (ct : Array Std.U32 1024#usize) (bend : Array Std.U32 512#usize) (i : Std.Usize) (lo : Std.Usize) (hi : Std.Usize) (dcs : Std.U64) (best0 : Std.U64) :
    slot.h_relax_bkt rm ct bend i lo hi dcs best0 ⦃ fun _ => True ⦄ := T14! slot.h_relax_bkt
@[local step]
theorem relax_pos_loop_spec (rm : Array Std.U64 4096#usize) (ct : Array Std.U32 1024#usize) (bend : Array Std.U32 512#usize) (mc : Slice Std.U32) (me : Std.Usize) (i : Std.Usize) (chw : Std.Usize) (msub : Std.U32) (best : Std.U64) (k : Std.Usize) (lo : Std.Usize) :
    slot.h_relax_pos_loop rm ct bend mc me i chw msub best k lo ⦃ fun _ => True ⦄ := by
  rw [slot.h_relax_pos_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => me.val - qq9.2.1.val)
    (inv := fun _ => True)
  · rintro ⟨best1, k1, lo1⟩ _
    simp only [slot.h_relax_pos_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem relax_pos_spec (rm : Array Std.U64 4096#usize) (ct : Array Std.U32 1024#usize) (bend : Array Std.U32 512#usize) (mc : Slice Std.U32) (ms : Std.Usize) (me : Std.Usize) (i : Std.Usize) (lit : Std.U64) (chw : Std.Usize) (msub : Std.U32) :
    slot.h_relax_pos rm ct bend mc ms me i lit chw msub ⦃ fun _ => True ⦄ := T14! slot.h_relax_pos
@[local step]
theorem prune_or_relax_spec (rm : Array Std.U64 4096#usize) (ct : Array Std.U32 1024#usize) (bend : Array Std.U32 512#usize) (mc : Slice Std.U32) (ms : Std.Usize) (me : Std.Usize) (i : Std.Usize) (lit : Std.U64) (chw : Std.Usize) (msub : Std.U32) (keep : Std.Usize) (items : alloc.vec.Vec Std.U32) :
    slot.h_prune_or_relax rm ct bend mc ms me i lit chw msub keep items ⦃ fun _ => True ⦄ := T14! slot.h_prune_or_relax
@[local step]
theorem relax_items_loop_spec (rm : Array Std.U64 4096#usize) (ct : Array Std.U32 1024#usize) (items : Slice Std.U32) (e : Std.Usize) (i : Std.Usize) (best : Std.U64) (t : Std.Usize) :
    slot.h_relax_items_loop rm ct items e i best t ⦃ fun _ => True ⦄ := by
  rw [slot.h_relax_items_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => e.val - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨best1, t1⟩ _
    simp only [slot.h_relax_items_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem relax_items_spec (rm : Array Std.U64 4096#usize) (ct : Array Std.U32 1024#usize) (items : Slice Std.U32) (s : Std.Usize) (e : Std.Usize) (i : Std.Usize) (lit : Std.U64) :
    slot.h_relax_items rm ct items s e i lit ⦃ fun _ => True ⦄ := T14! slot.h_relax_items
@[local step]
theorem dp_prune_loop_spec (input : Slice Std.U8) (rm : Array Std.U64 4096#usize) (ct : Array Std.U32 1024#usize) (bend : Array Std.U32 512#usize) (mstart : Slice Std.U32) (mc : Slice Std.U32) (choice : Slice Std.U32) (chw : Std.Usize) (msub : Std.U32) (keep : Std.Usize) (items : alloc.vec.Vec Std.U32) (istart : alloc.vec.Vec Std.U32) (lo : Std.Usize) (l4 : Std.Usize) (co : Std.Usize) (i : Std.Usize) :
    slot.h_dp_prune_loop input rm ct bend mstart mc choice chw msub keep items istart lo l4 co i ⦃ fun _ => True ⦄ := by
  rw [slot.h_dp_prune_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => qq9.2.2.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨rm1, choice1, items1, istart1, i1⟩ _
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.h_dp_prune_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem dp_prune_spec (input : Slice Std.U8) (rm : Array Std.U64 4096#usize) (ct : Array Std.U32 1024#usize) (bend : Array Std.U32 512#usize) (mstart : Slice Std.U32) (mc : Slice Std.U32) (choice : Slice Std.U32) (chw : Std.Usize) (msub : Std.U32) (keep : Std.Usize) (items : alloc.vec.Vec Std.U32) (istart : alloc.vec.Vec Std.U32) (lo : Std.Usize) (hi : Std.Usize) (l4 : Std.Usize) (co : Std.Usize) :
    slot.h_dp_prune input rm ct bend mstart mc choice chw msub keep items istart lo hi l4 co ⦃ fun _ => True ⦄ := T14! slot.h_dp_prune
@[local step]
theorem blk_lo_spec (bpos : Slice Std.U32) (b : Std.Usize) (hi : Std.Usize) :
    slot.h_blk_lo bpos b hi ⦃ fun _ => True ⦄ := T15! slot.h_blk_lo
@[local step]
theorem pass_prune_loop_spec (input : Slice Std.U8) (mstart : Slice Std.U32) (mc : Slice Std.U32) (tbl : Slice Std.U32) (bend : Array Std.U32 512#usize) (bpos : Slice Std.U32) (nb : Std.Usize) (choice : Slice Std.U32) (chw : Std.Usize) (msub : Std.U32) (keep : Std.Usize) (items : alloc.vec.Vec Std.U32) (istart : alloc.vec.Vec Std.U32) (co : Std.Usize) (lam : Std.U32) (rm : Array Std.U64 4096#usize) (ct : Array Std.U32 1024#usize) (hi : Std.Usize) (k : Std.Usize) :
    slot.h_pass_prune_loop input mstart mc tbl bend bpos nb choice chw msub keep items istart co lam rm ct hi k ⦃ fun _ => True ⦄ := by
  rw [slot.h_pass_prune_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => nb.val - qq9.2.2.2.2.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨choice1, items1, istart1, rm1, ct1, hi1, k1⟩ _
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.h_pass_prune_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem pass_prune_spec (input : Slice Std.U8) (mstart : Slice Std.U32) (mc : Slice Std.U32) (tbl : Slice Std.U32) (bend : Array Std.U32 512#usize) (bpos : Slice Std.U32) (nb : Std.Usize) (choice : Slice Std.U32) (chw : Std.Usize) (msub : Std.U32) (keep : Std.Usize) (items : alloc.vec.Vec Std.U32) (istart : alloc.vec.Vec Std.U32) (co : Std.Usize) (lam : Std.U32) :
    slot.h_pass_prune input mstart mc tbl bend bpos nb choice chw msub keep items istart co lam ⦃ fun _ => True ⦄ := T15! slot.h_pass_prune
@[local step]
theorem dp_items_loop_spec (input : Slice Std.U8) (rm : Array Std.U64 4096#usize) (ct : Array Std.U32 1024#usize) (choice : Slice Std.U32) (items : Slice Std.U32) (istart : Slice Std.U32) (lo : Std.Usize) (l4 : Std.Usize) (co : Std.Usize) (n : Std.Usize) (e : Std.Usize) (i : Std.Usize) :
    slot.h_dp_items_loop input rm ct choice items istart lo l4 co n e i ⦃ fun _ => True ⦄ := by
  rw [slot.h_dp_items_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => qq9.2.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨rm1, choice1, e1, i1⟩ _
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.h_dp_items_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem dp_items_spec (input : Slice Std.U8) (rm : Array Std.U64 4096#usize) (ct : Array Std.U32 1024#usize) (choice : Slice Std.U32) (items : Slice Std.U32) (istart : Slice Std.U32) (lo : Std.Usize) (hi : Std.Usize) (l4 : Std.Usize) (co : Std.Usize) :
    slot.h_dp_items input rm ct choice items istart lo hi l4 co ⦃ fun _ => True ⦄ := T15! slot.h_dp_items
@[local step]
theorem pass_items_loop_spec (input : Slice Std.U8) (tbl : Slice Std.U32) (bpos : Slice Std.U32) (nb : Std.Usize) (choice : Slice Std.U32) (items : Slice Std.U32) (istart : Slice Std.U32) (l4 : Std.Usize) (co : Std.Usize) (lam : Std.U32) (rm : Array Std.U64 4096#usize) (ct : Array Std.U32 1024#usize) (hi : Std.Usize) (k : Std.Usize) :
    slot.h_pass_items_loop input tbl bpos nb choice items istart l4 co lam rm ct hi k ⦃ fun _ => True ⦄ := by
  rw [slot.h_pass_items_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => nb.val - qq9.2.2.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨choice1, rm1, ct1, hi1, k1⟩ _
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.h_pass_items_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem pass_items_spec (input : Slice Std.U8) (tbl : Slice Std.U32) (bpos : Slice Std.U32) (nb : Std.Usize) (choice : Slice Std.U32) (items : Slice Std.U32) (istart : Slice Std.U32) (l4 : Std.Usize) (co : Std.Usize) (lam : Std.U32) :
    slot.h_pass_items input tbl bpos nb choice items istart l4 co lam ⦃ fun _ => True ⦄ := T15! slot.h_pass_items
@[local step]
theorem find_dist_loop_spec (mc : Slice Std.U32) (l : Std.Usize) (me : Std.Usize) (d : Std.Usize) (k : Std.Usize) :
    slot.h_find_dist_loop mc l me d k ⦃ fun _ => True ⦄ := by
  rw [slot.h_find_dist_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => me.val - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨d1, k1⟩ _
    simp only [slot.h_find_dist_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem find_dist_spec (mstart : Slice Std.U32) (mc : Slice Std.U32) (p : Std.Usize) (l : Std.Usize) :
    slot.h_find_dist mstart mc p l ⦃ fun _ => True ⦄ := T15! slot.h_find_dist
@[local step]
theorem clear_loop_spec (v : Slice Std.U32) (b : Std.Usize) (i : Std.Usize) :
    slot.h_clear_loop v b i ⦃ fun _ => True ⦄ := by
  rw [slot.h_clear_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => b.val - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨v1, i1⟩ _
    simp only [slot.h_clear_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem clear_spec (v : Slice Std.U32) (a : Std.Usize) (b : Std.Usize) :
    slot.h_clear v a b ⦃ fun _ => True ⦄ := T14! slot.h_clear
@[local step]
theorem dist_of_spec (mstart : Slice Std.U32) (mc : Slice Std.U32) (pos : Std.Usize) (len : Std.Usize) (d0 : Std.Usize) :
    slot.h_dist_of mstart mc pos len d0 ⦃ fun _ => True ⦄ := T14! slot.h_dist_of
@[local step]
theorem walk_bump_spec (fr : Slice Std.U32) (off : Std.Usize) (st : Std.Usize) (d : Std.Usize) (b : Std.Usize) :
    slot.h_walk_bump fr off st d b ⦃ fun _ => True ⦄ := T15! slot.h_walk_bump
@[local step]
theorem walk_loop_spec (input : Slice Std.U8) (mstart : Slice Std.U32) (mc : Slice Std.U32) (choice : Slice Std.U32) (co : Std.Usize) (fr : Slice Std.U32) (bpos : Slice Std.U32) (n : Std.Usize) (pos : Std.Usize) (b : Std.Usize) (t : Std.Usize) :
    slot.h_walk_loop input mstart mc choice co fr bpos n pos b t ⦃ fun _ => True ⦄ := by
  rw [slot.h_walk_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => n.val - qq9.2.2.2.1.val)
    (inv := fun _ => True)
  · rintro ⟨choice1, fr1, bpos1, pos1, b1, t1⟩ _
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.h_walk_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem walk_spec (input : Slice Std.U8) (mstart : Slice Std.U32) (mc : Slice Std.U32) (choice : Slice Std.U32) (co : Std.Usize) (fr : Slice Std.U32) (bpos : Slice Std.U32) :
    slot.h_walk input mstart mc choice co fr bpos ⦃ fun _ => True ⦄ := T15! slot.h_walk
@[local step]
theorem insert_sorted_loop_spec (order : Slice Std.U32) (freq : Slice Std.U32) (off : Std.Usize) (fs : Std.U32) (j : Std.Usize) :
    slot.h_insert_sorted_loop order freq off fs j ⦃ fun _ => True ⦄ := by
  rw [slot.h_insert_sorted_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨order1, j1⟩ _
    simp only [slot.h_insert_sorted_loop.body, lift]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem insert_sorted_spec (order : Slice Std.U32) (k : Std.Usize) (s : Std.Usize) (freq : Slice Std.U32) (off : Std.Usize) :
    slot.h_insert_sorted order k s freq off ⦃ fun _ => True ⦄ := T15! slot.h_insert_sorted
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
theorem radix_pass_loop0_spec (freq : Slice Std.U32) (off : Std.Usize) (src : Slice Std.U32) (k : Std.Usize) (sh : Std.U32) (cnt : Array Std.U32 256#usize) (i : Std.Usize) :
    slot.h_radix_pass_loop0 freq off src k sh cnt i ⦃ fun _ => True ⦄ := T16! slot.h_radix_pass_loop0 slot.h_radix_pass_loop0.body
@[local step]
theorem radix_pass_loop1_spec (cnt : Array Std.U32 256#usize) (acc : Std.U32) (d : Std.Usize) :
    slot.h_radix_pass_loop1 cnt acc d ⦃ fun _ => True ⦄ := by
  rw [slot.h_radix_pass_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 256 - qq9.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨cnt1, acc1, d1⟩ _
    simp only [slot.h_radix_pass_loop1.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem radix_pass_loop2_spec (freq : Slice Std.U32) (off : Std.Usize) (src : Slice Std.U32) (dst : Slice Std.U32) (k : Std.Usize) (sh : Std.U32) (cnt : Array Std.U32 256#usize) (j : Std.Usize) :
    slot.h_radix_pass_loop2 freq off src dst k sh cnt j ⦃ fun _ => True ⦄ := by
  rw [slot.h_radix_pass_loop2]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 288 - qq9.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨dst1, cnt1, j1⟩ _
    simp only [slot.h_radix_pass_loop2.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem radix_pass_spec (freq : Slice Std.U32) (off : Std.Usize) (src : Slice Std.U32) (dst : Slice Std.U32) (k : Std.Usize) (sh : Std.U32) :
    slot.h_radix_pass freq off src dst k sh ⦃ fun _ => True ⦄ := T14! slot.h_radix_pass
@[local step]
theorem copy32_loop_spec (src : Slice Std.U32) (soff : Std.Usize) (dst : Slice Std.U32) (doff : Std.Usize) (m : Std.Usize) (i : Std.Usize) :
    slot.h_copy32_loop src soff dst doff m i ⦃ fun _ => True ⦄ := by
  rw [slot.h_copy32_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => m.val - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨dst1, i1⟩ _
    simp only [slot.h_copy32_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem copy32_spec (src : Slice Std.U32) (soff : Std.Usize) (dst : Slice Std.U32) (doff : Std.Usize) (m : Std.Usize) :
    slot.h_copy32 src soff dst doff m ⦃ fun _ => True ⦄ := T14! slot.h_copy32
@[local step]
theorem sort_live_loop0_spec (freq : Slice Std.U32) (off : Std.Usize) (nsym : Std.Usize) (tmp : Array Std.U32 288#usize) (k : Std.Usize) (big : Std.Usize) (s : Std.Usize) :
    slot.h_sort_live_loop0 freq off nsym tmp k big s ⦃ fun _ => True ⦄ := by
  rw [slot.h_sort_live_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 288 - qq9.2.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨tmp1, k1, big1, s1⟩ _
    simp only [slot.h_sort_live_loop0.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem sort_live_loop1_spec (freq : Slice Std.U32) (off : Std.Usize) (order : Slice Std.U32) (tmp : Array Std.U32 288#usize) (kb : Std.Usize) (j : Std.Usize) :
    slot.h_sort_live_loop1 freq off order tmp kb j ⦃ fun _ => True ⦄ := by
  rw [slot.h_sort_live_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 288 - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨order1, j1⟩ _
    simp only [slot.h_sort_live_loop1.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem sort_live_spec (freq : Slice Std.U32) (off : Std.Usize) (nsym : Std.Usize) (order : Slice Std.U32) :
    slot.h_sort_live freq off nsym order ⦃ fun _ => True ⦄ := T14! slot.h_sort_live
@[local step]
theorem load_w_loop_spec (freq : Slice Std.U32) (off : Std.Usize) (order : Slice Std.U32) (k : Std.Usize) (wa : Slice Std.U64) (i : Std.Usize) :
    slot.h_load_w_loop freq off order k wa i ⦃ fun _ => True ⦄ := by
  rw [slot.h_load_w_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 288 - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨wa1, i1⟩ _
    simp only [slot.h_load_w_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem load_w_spec (freq : Slice Std.U32) (off : Std.Usize) (order : Slice Std.U32) (k : Std.Usize) (wa : Slice Std.U64) :
    slot.h_load_w freq off order k wa ⦃ fun _ => True ⦄ := T14! slot.h_load_w
@[local step]
theorem pm_level_loop_spec (lw : Array Std.U64 288#usize) (k : Std.Usize) (w : Array Std.U64 1152#usize) (src : Std.Usize) (dst : Std.Usize) (flags : Array Std.U8 9216#usize) (foff : Std.Usize) (npk : Std.Usize) (total : Std.Usize) (a : Std.Usize) (p : Std.Usize) (t : Std.Usize) :
    slot.h_pm_level_loop lw k w src dst flags foff npk total a p t ⦃ fun _ => True ⦄ := by
  rw [slot.h_pm_level_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 576 - qq9.2.2.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨w1, flags1, a1, p1, t1⟩ _
    simp only [slot.h_pm_level_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem pm_level_spec (lw : Array Std.U64 288#usize) (k : Std.Usize) (w : Array Std.U64 1152#usize) (src : Std.Usize) (curlen : Std.Usize) (dst : Std.Usize) (flags : Array Std.U8 9216#usize) (foff : Std.Usize) :
    slot.h_pm_level lw k w src curlen dst flags foff ⦃ fun _ => True ⦄ := T15! slot.h_pm_level
@[local step]
theorem pm_levels_loop_spec (lw : Array Std.U64 288#usize) (k : Std.Usize) (w : Array Std.U64 1152#usize) (flags : Array Std.U8 9216#usize) (maxbits : Std.Usize) (curlen : Std.Usize) (lev : Std.Usize) :
    slot.h_pm_levels_loop lw k w flags maxbits curlen lev ⦃ fun _ => True ⦄ := by
  rw [slot.h_pm_levels_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 16 - qq9.2.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨w1, flags1, curlen1, lev1⟩ _
    simp only [slot.h_pm_levels_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem pm_levels_spec (lw : Array Std.U64 288#usize) (k : Std.Usize) (w : Array Std.U64 1152#usize) (flags : Array Std.U8 9216#usize) (maxbits : Std.Usize) :
    slot.h_pm_levels lw k w flags maxbits ⦃ fun _ => True ⦄ := T14! slot.h_pm_levels
@[local step]
theorem count_leaves_loop_spec (flags : Slice Std.U8) (foff : Std.Usize) (s : Std.Usize) (c : Std.Usize) (i : Std.Usize) :
    slot.h_count_leaves_loop flags foff s c i ⦃ fun _ => True ⦄ := by
  rw [slot.h_count_leaves_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 576 - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨c1, i1⟩ _
    simp only [slot.h_count_leaves_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem count_leaves_spec (flags : Slice Std.U8) (foff : Std.Usize) (s : Std.Usize) :
    slot.h_count_leaves flags foff s ⦃ fun _ => True ⦄ := T14! slot.h_count_leaves
@[local step]
theorem inc_prefix_loop_spec (cnt : Slice Std.U32) (m : Std.Usize) (i : Std.Usize) :
    slot.h_inc_prefix_loop cnt m i ⦃ fun _ => True ⦄ := T16! slot.h_inc_prefix_loop slot.h_inc_prefix_loop.body
@[local step]
theorem inc_prefix_spec (cnt : Slice Std.U32) (m : Std.Usize) :
    slot.h_inc_prefix cnt m ⦃ fun _ => True ⦄ := T14! slot.h_inc_prefix
@[local step]
theorem count_back_loop_spec (flags : Slice Std.U8) (cnt : Slice Std.U32) (s : Std.Usize) (lv : Std.Usize) :
    slot.h_count_back_loop flags cnt s lv ⦃ fun _ => True ⦄ := by
  rw [slot.h_count_back_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => qq9.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨cnt1, s1, lv1⟩ _
    simp only [slot.h_count_back_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem count_back_spec (flags : Slice Std.U8) (cnt : Slice Std.U32) (k : Std.Usize) (maxbits : Std.Usize) :
    slot.h_count_back flags cnt k maxbits ⦃ fun _ => True ⦄ := T15! slot.h_count_back
@[local step]
theorem assign_lens_loop_spec (order : Slice Std.U32) (cnt : Slice Std.U32) (k : Std.Usize) (lens : Slice Std.U32) (loff : Std.Usize) (r : Std.Usize) :
    slot.h_assign_lens_loop order cnt k lens loff r ⦃ fun _ => True ⦄ := by
  rw [slot.h_assign_lens_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 288 - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨lens1, r1⟩ _
    simp only [slot.h_assign_lens_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem assign_lens_spec (order : Slice Std.U32) (cnt : Slice Std.U32) (k : Std.Usize) (lens : Slice Std.U32) (loff : Std.Usize) :
    slot.h_assign_lens order cnt k lens loff ⦃ fun _ => True ⦄ := T14! slot.h_assign_lens
@[local step]
theorem pkg_merge_pm_spec (freq : Slice Std.U32) (off : Std.Usize) (nsym : Std.Usize) (maxbits : Std.Usize) (lens : Slice Std.U32) (loff : Std.Usize) :
    slot.h_pkg_merge_pm freq off nsym maxbits lens loff ⦃ fun _ => True ⦄ := T14! slot.h_pkg_merge_pm
@[local step]
theorem pkg_merge_loop0_spec (freq : Slice Std.U32) (off : Std.Usize) (order : Array Std.U32 288#usize) (k : Std.Usize) (weights : Array Std.U64 576#usize) (i : Std.Usize) :
    slot.h_pkg_merge_loop0 freq off order k weights i ⦃ fun _ => True ⦄ := by
  rw [slot.h_pkg_merge_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 288 - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨weights1, i1⟩ _
    simp only [slot.h_pkg_merge_loop0.body]
    try simp only [lift, ite_ok, alloc.vec.Vec.deref_mut, bind_tc_ok]
    step*
    all_goals repeat (first
      | (split <;> (try step*))
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply spec_ite_cut <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals scalar_tac
  · trivial
@[local step]
theorem pkg_merge_loop1_loop0_spec (k : Std.Usize) (weights : Array Std.U64 576#usize) (parent : Array Std.U32 576#usize) (leaf : Std.Usize) (pair : Std.Usize) (next : Std.Usize) (sum : Std.U64) (j : Std.Usize) :
    slot.h_pkg_merge_loop1_loop0 k weights parent leaf pair next sum j ⦃ fun _ => True ⦄ := by
  rw [slot.h_pkg_merge_loop1_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 2 - qq9.2.2.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨parent1, leaf1, pair1, sum1, j1⟩ _
    simp only [slot.h_pkg_merge_loop1_loop0.body]
    try simp only [lift, ite_ok, alloc.vec.Vec.deref_mut, bind_tc_ok]
    step*
    all_goals repeat (first
      | (split <;> (try step*))
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply spec_ite_cut <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals scalar_tac
  · trivial
@[local step]
theorem pkg_merge_loop1_spec (k : Std.Usize) (weights : Array Std.U64 576#usize) (parent : Array Std.U32 576#usize) (leaf : Std.Usize) (pair : Std.Usize) (next : Std.Usize) :
    slot.h_pkg_merge_loop1 k weights parent leaf pair next ⦃ fun _ => True ⦄ := by
  rw [slot.h_pkg_merge_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 575 - qq9.2.2.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨weights1, parent1, leaf1, pair1, next1⟩ _
    simp only [slot.h_pkg_merge_loop1.body]
    try simp only [lift, ite_ok, alloc.vec.Vec.deref_mut, bind_tc_ok]
    step*
    all_goals repeat (first
      | (split <;> (try step*))
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply spec_ite_cut <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals scalar_tac
  · trivial
@[local step]
theorem pkg_merge_loop2_spec (parent : Array Std.U32 576#usize) (depth : Array Std.U32 576#usize) (mx : Std.Usize) (node : Std.Usize) :
    slot.h_pkg_merge_loop2 parent depth mx node ⦃ fun _ => True ⦄ := by
  rw [slot.h_pkg_merge_loop2]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => qq9.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨depth1, mx1, node1⟩ _
    simp only [slot.h_pkg_merge_loop2.body]
    try simp only [lift, ite_ok, alloc.vec.Vec.deref_mut, bind_tc_ok]
    step*
    all_goals repeat (first
      | (split <;> (try step*))
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply spec_ite_cut <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals scalar_tac
  · trivial
@[local step]
theorem pkg_merge_loop3_spec (lens : Slice Std.U32) (loff : Std.Usize) (order : Array Std.U32 288#usize) (k : Std.Usize) (depth : Array Std.U32 576#usize) (r : Std.Usize) :
    slot.h_pkg_merge_loop3 lens loff order k depth r ⦃ fun _ => True ⦄ := by
  rw [slot.h_pkg_merge_loop3]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 288 - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨lens1, r1⟩ _
    simp only [slot.h_pkg_merge_loop3.body]
    try simp only [lift, ite_ok, alloc.vec.Vec.deref_mut, bind_tc_ok]
    step*
    all_goals repeat (first
      | (split <;> (try step*))
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply spec_ite_cut <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals scalar_tac
  · trivial
@[local step]
theorem pkg_merge_spec (freq : Slice Std.U32) (off : Std.Usize) (nsym : Std.Usize) (maxbits : Std.Usize) (lens : Slice Std.U32) (loff : Std.Usize) :
    slot.h_pkg_merge freq off nsym maxbits lens loff ⦃ fun _ => True ⦄ := by
  rw [slot.h_pkg_merge]
  step*
  simp only [lift, bind_tc_ok]
  step*
  all_goals (repeat (split <;> try step*))
  all_goals scalar_tac
@[local step]
theorem run_len_loop_spec (all : Slice Std.U32) (i : Std.Usize) (m : Std.Usize) (v : Std.U32) (r : Std.Usize) :
    slot.h_run_len_loop all i m v r ⦃ fun _ => True ⦄ := by
  rw [slot.h_run_len_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 1000 - qq9.val)
    (inv := fun _ => True)
  · rintro r1 _
    simp only [slot.h_run_len_loop.body, lift]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem run_len_spec (all : Slice Std.U32) (i : Std.Usize) (m : Std.Usize) :
    slot.h_run_len all i m ⦃ fun _ => True ⦄ := T14! slot.h_run_len
@[local step]
theorem rle_stats_loop_spec (all : Slice Std.U32) (m : Std.Usize) (clf : Slice Std.U32) (extra : Std.U64) (i : Std.Usize) :
    slot.h_rle_stats_loop all m clf extra i ⦃ fun _ => True ⦄ := by
  rw [slot.h_rle_stats_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => m.val - qq9.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨clf1, extra1, i1⟩ _
    simp only [slot.h_rle_stats_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem rle_stats_spec (all : Slice Std.U32) (m : Std.Usize) (clf : Slice Std.U32) :
    slot.h_rle_stats all m clf ⦃ fun _ => True ⦄ := T14! slot.h_rle_stats
@[local step]
theorem dot_loop_spec (f : Slice Std.U32) (foff : Std.Usize) (l : Slice Std.U32) (loff : Std.Usize) (m : Std.Usize) (s : Std.U64) (i : Std.Usize) :
    slot.h_dot_loop f foff l loff m s i ⦃ fun _ => True ⦄ := by
  rw [slot.h_dot_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => m.val - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨s1, i1⟩ _
    simp only [slot.h_dot_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem dot_spec (f : Slice Std.U32) (foff : Std.Usize) (l : Slice Std.U32) (loff : Std.Usize) (m : Std.Usize) :
    slot.h_dot f foff l loff m ⦃ fun _ => True ⦄ := T14! slot.h_dot
@[local step]
theorem fixed_dot_loop_spec (f : Slice Std.U32) (foff : Std.Usize) (s : Std.U64) (i : Std.Usize) :
    slot.h_fixed_dot_loop f foff s i ⦃ fun _ => True ⦄ := by
  rw [slot.h_fixed_dot_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 288 - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨s1, i1⟩ _
    simp only [slot.h_fixed_dot_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem fixed_dot_spec (f : Slice Std.U32) (foff : Std.Usize) :
    slot.h_fixed_dot f foff ⦃ fun _ => True ⦄ := T14! slot.h_fixed_dot
@[local step]
theorem sum_range_loop_spec (f : Slice Std.U32) (b : Std.Usize) (s : Std.U64) (i : Std.Usize) :
    slot.h_sum_range_loop f b s i ⦃ fun _ => True ⦄ := by
  rw [slot.h_sum_range_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => b.val - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨s1, i1⟩ _
    simp only [slot.h_sum_range_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem sum_range_spec (f : Slice Std.U32) (a : Std.Usize) (b : Std.Usize) :
    slot.h_sum_range f a b ⦃ fun _ => True ⦄ := T14! slot.h_sum_range
@[local step]
theorem last_nz_loop_spec (l : Slice Std.U32) (off : Std.Usize) (lo : Std.Usize) (k : Std.Usize) :
    slot.h_last_nz_loop l off lo k ⦃ fun _ => True ⦄ := by
  rw [slot.h_last_nz_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => qq9.val)
    (inv := fun _ => True)
  · rintro k1 _
    simp only [slot.h_last_nz_loop.body, lift]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem last_nz_spec (l : Slice Std.U32) (off : Std.Usize) (m : Std.Usize) (lo : Std.Usize) :
    slot.h_last_nz l off m lo ⦃ fun _ => True ⦄ := T14! slot.h_last_nz
@[local step]
theorem hclen_of_loop_spec (cl : Slice Std.U32) (h : Std.Usize) :
    slot.h_hclen_of_loop cl h ⦃ fun _ => True ⦄ := by
  rw [slot.h_hclen_of_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => qq9.val)
    (inv := fun _ => True)
  · rintro h1 _
    simp only [slot.h_hclen_of_loop.body, lift]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem hclen_of_spec (cl : Slice Std.U32) :
    slot.h_hclen_of cl ⦃ fun _ => True ⦄ := T14! slot.h_hclen_of
@[local step]
theorem block_bits_spec (fr : Slice Std.U32) (off : Std.Usize) (lens : Slice Std.U32) :
    slot.h_block_bits fr off lens ⦃ fun _ => True ⦄ := T14! slot.h_block_bits
@[local step]
theorem log2x16_spec (x : Std.U64) :
    slot.h_log2x16 x ⦃ fun _ => True ⦄ := T15! slot.h_log2x16
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
theorem sym_costs_loop_spec (fr : Slice Std.U32) (off : Std.Usize) (lens : Slice Std.U32) (kind : Std.U32) (sc : Slice Std.U32) (lt1 : Std.U32) (ld : Std.U32) (s : Std.Usize) :
    slot.h_sym_costs_loop fr off lens kind sc lt1 ld s ⦃ fun _ => True ⦄ := T17! slot.h_sym_costs_loop slot.h_sym_costs_loop.body
@[local step]
theorem sym_costs_spec (fr : Slice Std.U32) (off : Std.Usize) (lens : Slice Std.U32) (kind : Std.U32) (sc : Slice Std.U32) :
    slot.h_sym_costs fr off lens kind sc ⦃ fun _ => True ⦄ := T15! slot.h_sym_costs
@[local step]
theorem mode_ov_spec (damp : Std.U32) : slot.h_mode_ov damp ⦃ fun _ => True ⦄ := by
  rw [slot.h_mode_ov]; repeat (first | (split <;> step*) | scalar_tac)
@[local step]
theorem blend_spec (old : Std.U32) (new : Std.U32) (damp : Std.U32) :
    slot.h_blend old new damp ⦃ fun _ => True ⦄ := T15! slot.h_blend
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
theorem fill_table_loop0_spec (sc : Slice Std.U32) (tbl : Slice Std.U32) (toff : Std.Usize) (damp : Std.U32) (c : Std.Usize) :
    slot.h_fill_table_loop0 sc tbl toff damp c ⦃ fun _ => True ⦄ := T18! slot.h_fill_table_loop0 slot.h_fill_table_loop0.body
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
theorem fill_table_loop1_spec (sc : Slice Std.U32) (tbl : Slice Std.U32) (toff : Std.Usize) (damp : Std.U32) (len : Std.Usize) :
    slot.h_fill_table_loop1 sc tbl toff damp len ⦃ fun _ => True ⦄ := T19! slot.h_fill_table_loop1 slot.h_fill_table_loop1.body
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
theorem fill_table_loop2_spec (sc : Slice Std.U32) (tbl : Slice Std.U32) (toff : Std.Usize) (damp : Std.U32) (s : Std.Usize) :
    slot.h_fill_table_loop2 sc tbl toff damp s ⦃ fun _ => True ⦄ := T20! slot.h_fill_table_loop2 slot.h_fill_table_loop2.body
@[local step]
theorem fill_table_spec (sc : Slice Std.U32) (tbl : Slice Std.U32) (toff : Std.Usize) (damp : Std.U32) :
    slot.h_fill_table sc tbl toff damp ⦃ fun _ => True ⦄ := T14! slot.h_fill_table
@[local step]
theorem longest_spec (mstart : Slice Std.U32) (mc : Slice Std.U32) (p : Std.Usize) :
    slot.h_longest mstart mc p ⦃ fun _ => True ⦄ := T15! slot.h_longest
@[local step]
theorem block_hist_loop_spec (input : Slice Std.U8) (b : Std.Usize) (fr : Slice Std.U32) (i : Std.Usize) :
    slot.h_block_hist_loop input b fr i ⦃ fun _ => True ⦄ := by
  rw [slot.h_block_hist_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => b.val - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨fr1, i1⟩ _
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.h_block_hist_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem block_hist_spec (input : Slice Std.U8) (a : Std.Usize) (b : Std.Usize) (fr : Slice Std.U32) :
    slot.h_block_hist input a b fr ⦃ fun _ => True ⦄ := T14! slot.h_block_hist
@[local step]
theorem add_hist_loop_spec (fr : Slice Std.U32) (hist : Array Std.U32 256#usize) (c : Std.Usize) :
    slot.h_add_hist_loop fr hist c ⦃ fun _ => True ⦄ := by
  rw [slot.h_add_hist_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 256 - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨hist1, c1⟩ _
    simp only [slot.h_add_hist_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem add_hist_spec (fr : Slice Std.U32) (hist : Array Std.U32 256#usize) :
    slot.h_add_hist fr hist ⦃ fun _ => True ⦄ := T14! slot.h_add_hist
@[local step]
theorem block_bits_if_spec (fr : Slice Std.U32) (lens : Slice Std.U32) (f : Std.Usize) :
    slot.h_block_bits_if fr lens f ⦃ fun _ => True ⦄ := T14! slot.h_block_bits_if
@[local step]
theorem st5len_spec (len : Std.Usize) :
    slot.h_st5len len ⦃ fun _ => True ⦄ := T15! slot.h_st5len
@[local step]
theorem ent5_spec (lt1 : Std.U32) (f : Std.U64) :
    slot.h_ent5 lt1 f ⦃ fun _ => True ⦄ := T14! slot.h_ent5
@[local step]
theorem init5_table_loop0_spec (fr : Slice Std.U32) (tbl : Slice Std.U32) (toff : Std.Usize) (lt1 : Std.U32) (c : Std.Usize) :
    slot.h_init5_table_loop0 fr tbl toff lt1 c ⦃ fun _ => True ⦄ := T18! slot.h_init5_table_loop0 slot.h_init5_table_loop0.body
@[local step]
theorem init5_table_loop1_spec (tbl : Slice Std.U32) (toff : Std.Usize) (len : Std.Usize) :
    slot.h_init5_table_loop1 tbl toff len ⦃ fun _ => True ⦄ := T19! slot.h_init5_table_loop1 slot.h_init5_table_loop1.body
@[local step]
theorem init5_table_loop2_spec (tbl : Slice Std.U32) (toff : Std.Usize) (s : Std.Usize) :
    slot.h_init5_table_loop2 tbl toff s ⦃ fun _ => True ⦄ := T20! slot.h_init5_table_loop2 slot.h_init5_table_loop2.body
@[local step]
theorem init5_table_spec (fr : Slice Std.U32) (tbl : Slice Std.U32) (toff : Std.Usize) :
    slot.h_init5_table fr tbl toff ⦃ fun _ => True ⦄ := T15! slot.h_init5_table
@[local step]
theorem literal_bits_loop_spec (input : Slice Std.U8) (fr : Slice Std.U32) (hist : Array Std.U32 256#usize) (tlit : Slice Std.U32) (t5 : Slice Std.U32) (n : Std.Usize) (lens : Array Std.U32 320#usize) (sc : Array Std.U32 320#usize) (total : Std.U64) (nblk : Std.Usize) (b : Std.Usize) :
    slot.h_literal_bits_loop input fr hist tlit t5 n lens sc total nblk b ⦃ fun _ => True ⦄ := by
  rw [slot.h_literal_bits_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => nblk.val - qq9.2.2.2.2.2.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨fr1, hist1, tlit1, t51, lens1, sc1, total1, b1⟩ _
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.h_literal_bits_loop.body, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem literal_bits_spec (input : Slice Std.U8) (fr : Slice Std.U32) (hist : Array Std.U32 256#usize) (tlit : Slice Std.U32) (t5 : Slice Std.U32) :
    slot.h_literal_bits input fr hist tlit t5 ⦃ fun _ => True ⦄ := T14! slot.h_literal_bits
@[local step]
theorem avg_lit16_h_spec (hist : Array Std.U32 256#usize) (n : Std.Usize) :
    slot.h_avg_lit16_h hist n ⦃ fun _ => True ⦄ := T14! slot.h_avg_lit16_h
@[local step]
theorem est_match16_spec (l : Std.Usize) (d : Std.Usize) :
    slot.h_est_match16 l d ⦃ fun _ => True ⦄ := T15! slot.h_est_match16
@[local step]
theorem est_if_spec (f : Std.Usize) (l : Std.Usize) (d : Std.Usize) :
    slot.h_est_if f l d ⦃ fun _ => True ⦄ := T14! slot.h_est_if
@[local step]
theorem next_longest_spec (mstart : Slice Std.U32) (mc : Slice Std.U32) (pos : Std.Usize) (st : Std.Usize) (b : Std.Usize) :
    slot.h_next_longest mstart mc pos st b ⦃ fun _ => True ⦄ := T15! slot.h_next_longest
@[local step]
theorem lazy_cost_init_loop_spec (mstart : Slice Std.U32) (mc : Slice Std.U32) (h16 : Std.U32) (choice : Slice Std.U32) (n : Std.Usize) (pos : Std.Usize) (nxt : Std.Usize) (ec : Std.U32) (hv : Std.Usize) :
    slot.h_lazy_cost_init_loop mstart mc h16 choice n pos nxt ec hv ⦃ fun _ => True ⦄ := by
  rw [slot.h_lazy_cost_init_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => n.val - qq9.2.1.val)
    (inv := fun _ => True)
  · rintro ⟨choice1, pos1, nxt1, ec1, hv1⟩ _
    simp only [slot.h_lazy_cost_init_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem lazy_cost_init_spec (input : Slice Std.U8) (mstart : Slice Std.U32) (mc : Slice Std.U32) (h16 : Std.U32) (choice : Slice Std.U32) :
    slot.h_lazy_cost_init input mstart mc h16 choice ⦃ fun _ => True ⦄ := T14! slot.h_lazy_cost_init
@[local step]
theorem forbid_block_loop_spec (tbl : Slice Std.U32) (toff : Std.Usize) (len : Std.Usize) :
    slot.h_forbid_block_loop tbl toff len ⦃ fun _ => True ⦄ := T19! slot.h_forbid_block_loop slot.h_forbid_block_loop.body
@[local step]
theorem forbid_block_spec (tbl : Slice Std.U32) (toff : Std.Usize) :
    slot.h_forbid_block tbl toff ⦃ fun _ => True ⦄ := T14! slot.h_forbid_block
@[local step]
theorem forbid_if_spec (tbl : Slice Std.U32) (toff : Std.Usize) (f : Std.Usize) :
    slot.h_forbid_if tbl toff f ⦃ fun _ => True ⦄ := T14! slot.h_forbid_if
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
theorem eval_blocks_loop_spec (fr : Slice Std.U32) (tbl : Slice Std.U32) (damp : Std.U32) (lens : Array Std.U32 320#usize) (sc : Array Std.U32 320#usize) (total : Std.U64) (lim : Std.Usize) (b : Std.Usize) :
    slot.h_eval_blocks_loop fr tbl damp lens sc total lim b ⦃ fun _ => True ⦄ := T21! slot.h_eval_blocks_loop slot.h_eval_blocks_loop.body
@[local step]
theorem eval_blocks_spec (fr : Slice Std.U32) (tbl : Slice Std.U32) (nb2 : Std.Usize) (nbmax : Std.Usize) (damp : Std.U32) :
    slot.h_eval_blocks fr tbl nb2 nbmax damp ⦃ fun _ => True ⦄ := T14! slot.h_eval_blocks
@[local step]
theorem dp_pass_spec (input : Slice Std.U8) (mstart : Slice Std.U32) (mc : Slice Std.U32) (tbl : Slice Std.U32) (bend : Array Std.U32 512#usize) (bpos : Slice Std.U32) (nb : Std.Usize) (choice : Slice Std.U32) (chw : Std.Usize) (keep : Std.Usize) (items : alloc.vec.Vec Std.U32) (istart : alloc.vec.Vec Std.U32) (pr : Std.Usize) (msub : Std.U32) (co : Std.Usize) (lam : Std.U32) :
    slot.h_dp_pass input mstart mc tbl bend bpos nb choice chw keep items istart pr msub co lam ⦃ fun _ => True ⦄ := T14! slot.h_dp_pass
@[local step]
theorem stop_rule_spec (prev : Std.U64) (r : Std.U64) (n : Std.Usize) (it1 : Std.Usize) (gk : Std.U64) (minp : Std.Usize) :
    slot.h_stop_rule prev r n it1 gk minp ⦃ fun _ => True ⦄ := T15! slot.h_stop_rule
@[local step]
theorem one_pass_spec (prev : Std.U64) (n : Std.Usize) (gk : Std.U64) :
    slot.h_one_pass prev n gk ⦃ fun _ => True ⦄ := T15! slot.h_one_pass
@[local step]
theorem mode_damp_spec (mode : Std.Usize) (damp : Std.U32) : slot.h_mode_damp mode damp ⦃ fun _ => True ⦄ := by
  rw [slot.h_mode_damp]; repeat (first | (split <;> step*) | scalar_tac)
@[local step]
theorem eval_mode_spec (mode : Std.Usize) (fr tbl : Slice Std.U32) (nb nbmax : Std.Usize) (damp ew : Std.U32) :
    slot.h_eval_mode mode fr tbl nb nbmax damp ew ⦃ fun _ => True ⦄ := by
  rw [slot.h_eval_mode]
  step*
@[local step]
theorem lg8_spec (x : Std.U32) :
    slot.h_lg8 x ⦃ fun _ => True ⦄ := T15! slot.h_lg8
@[local step]
theorem entropy256_loop_spec (h : Array Std.U32 256#usize) (tot : Std.U64) (acc : Std.U64) (i : Std.Usize) :
    slot.h_entropy256_loop h tot acc i ⦃ fun _ => True ⦄ := by
  rw [slot.h_entropy256_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 256 - qq9.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨tot1, acc1, i1⟩ _
    simp only [slot.h_entropy256_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem entropy256_spec (h : Array Std.U32 256#usize) :
    slot.h_entropy256 h ⦃ fun _ => True ⦄ := T14! slot.h_entropy256
@[local step]
theorem hash12_spec (input : Slice Std.U8) (p : Std.Usize) :
    slot.h_hash12 input p ⦃ fun _ => True ⦄ := T15! slot.h_hash12
@[local step]
theorem probe_win_loop_spec (input : Slice Std.U8) (ht : Array Std.U32 4096#usize) (s : Std.Usize) (e : Std.Usize) (n : Std.Usize) (i : Std.Usize) (cov : Std.U64) (nm : Std.U64) (it : Std.Usize) :
    slot.h_probe_win_loop input ht s e n i cov nm it ⦃ fun _ => True ⦄ := by
  rw [slot.h_probe_win_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => slot.H_PR_W.val - qq9.2.2.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨ht1, i1, cov1, nm1, it1⟩ _
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.h_probe_win_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem probe_win_spec (input : Slice Std.U8) (ht : Array Std.U32 4096#usize) (s : Std.Usize) (e : Std.Usize) :
    slot.h_probe_win input ht s e ⦃ fun _ => True ⦄ := T15! slot.h_probe_win
@[local step]
theorem probe_all_loop_spec (input : Slice Std.U8) (ht : Array Std.U32 4096#usize) (span : Std.Usize) (acc : Std.U64) (k : Std.Usize) :
    slot.h_probe_all_loop input ht span acc k ⦃ fun _ => True ⦄ := by
  rw [slot.h_probe_all_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => slot.H_PR_N.val - qq9.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨ht1, acc1, k1⟩ _
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.h_probe_all_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem probe_all_spec (input : Slice Std.U8) :
    slot.h_probe_all input ⦃ fun _ => True ⦄ := T15! slot.h_probe_all
@[local step]
theorem probe_if_spec (input : Slice Std.U8) (f : Std.Usize) :
    slot.h_probe_if input f ⦃ fun _ => True ⦄ := T14! slot.h_probe_if
@[local step]
theorem odd_sample_loop_spec (input : Slice Std.U8) (h : Array Std.U32 256#usize) (n : Std.Usize) (st : Std.Usize) (k : Std.Usize) (c : Std.Usize) :
    slot.h_odd_sample_loop input h n st k c ⦃ fun _ => True ⦄ := by
  rw [slot.h_odd_sample_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 8192 - qq9.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨h1, k1, c1⟩ _
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.h_odd_sample_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem odd_sample_spec (input : Slice Std.U8) (h : Array Std.U32 256#usize) :
    slot.h_odd_sample input h ⦃ fun _ => True ⦄ := T15! slot.h_odd_sample
@[local step]
theorem ge64_spec (a : Std.U64) (b : Std.U64) :
    slot.h_ge64 a b ⦃ fun _ => True ⦄ := T14! slot.h_ge64
@[local step]
theorem byte_classes_loop_spec (h : Array Std.U32 256#usize) (tot : Std.U64) (ctl : Std.U64) (hib : Std.U64) (i : Std.Usize) :
    slot.h_byte_classes_loop h tot ctl hib i ⦃ fun _ => True ⦄ := by
  rw [slot.h_byte_classes_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 256 - qq9.2.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨tot1, ctl1, hib1, i1⟩ _
    simp only [slot.h_byte_classes_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem byte_classes_spec (h : Array Std.U32 256#usize) :
    slot.h_byte_classes h ⦃ fun _ => True ⦄ := T15! slot.h_byte_classes
@[local step]
theorem byte_classes2_loop_spec (h : Array Std.U32 256#usize) (z0 : Std.U64) (dig : Std.U64) (nz : Std.U64) (i : Std.Usize) :
    slot.h_byte_classes2_loop h z0 dig nz i ⦃ fun _ => True ⦄ := by
  rw [slot.h_byte_classes2_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 256 - qq9.2.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨z01, dig1, nz1, i1⟩ _
    simp only [slot.h_byte_classes2_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem byte_classes2_spec (h : Array Std.U32 256#usize) :
    slot.h_byte_classes2 h ⦃ fun _ => True ⦄ := T15! slot.h_byte_classes2
@[local step]
theorem classify_spec (input : Slice Std.U8) :
    slot.h_classify input ⦃ fun _ => True ⦄ := T15! slot.h_classify
@[local step]
theorem cx_jitter_loop0_loop0_spec (tbl : Slice Std.U32) (seed : Std.U32) (amp : Std.U32) (off : Std.Usize) (s : Std.Usize) (hamp : amp.val < 33) :
    slot.h_cx_jitter_loop0_loop0 tbl seed amp off s ⦃ fun _ => True ⦄ := by
  rw [slot.h_cx_jitter_loop0_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 545 - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨tbl1, s1⟩ _
    simp only [slot.h_cx_jitter_loop0_loop0.body]
    try simp only [lift, ite_ok, alloc.vec.Vec.deref_mut, bind_tc_ok]
    step*
    all_goals repeat (first
      | (split <;> (try step*))
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply spec_ite_cut <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals scalar_tac
  · trivial
@[local step]
theorem cx_jitter_loop0_spec (tbl : Slice Std.U32) (nb : Std.Usize) (seed : Std.U32) (amp : Std.U32) (b : Std.Usize) (hamp : amp.val < 33) :
    slot.h_cx_jitter_loop0 tbl nb seed amp b ⦃ fun _ => True ⦄ := by
  rw [slot.h_cx_jitter_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => nb.val - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨tbl1, b1⟩ _
    simp only [slot.h_cx_jitter_loop0.body]
    try simp only [lift, ite_ok, alloc.vec.Vec.deref_mut, bind_tc_ok]
    step*
    all_goals repeat (first
      | (split <;> (try step*))
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply spec_ite_cut <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals scalar_tac
  · trivial
set_option hygiene false in
local notation "T22!" q0__:max => (by
  rw [q0__]
  try simp only [lift, ite_ok, alloc.vec.Vec.deref_mut, bind_tc_ok]
  step*
  all_goals repeat (first
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals scalar_tac)
@[local step]
theorem cx_jitter_spec (tbl : Slice Std.U32) (nb : Std.Usize) (seed : Std.U32) (amplitude : Std.U32) :
    slot.h_cx_jitter tbl nb seed amplitude ⦃ fun _ => True ⦄ := T22! slot.h_cx_jitter
@[local step]
theorem cx_restarts_loop0_loop0_spec (input : Slice Std.U8) (mstart : Slice Std.U32) (mc : Slice Std.U32)
  (tbl : Slice Std.U32) (fr : Slice Std.U32) (bpos : Slice Std.U32)
  (bend : Array Std.U32 512#usize) (choice : Slice Std.U32)
  (plan : Slice Std.U32) (nbmax : Std.Usize) (lamh : Std.U32)
  (items : alloc.vec.Vec Std.U32) (istart : alloc.vec.Vec Std.U32)
  (pr : Std.Usize) (chw : Std.Usize) (n : Std.Usize) (nbc : Std.Usize)
  (bestp : Std.U64) (step : Std.Usize) :
    slot.h_cx_restarts_loop0_loop0 input mstart mc tbl fr bpos bend choice plan nbmax lamh items istart pr chw n nbc bestp step ⦃ fun _ => True ⦄ := by
  rw [slot.h_cx_restarts_loop0_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun s => 3 - s.2.2.2.2.2.2.2.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨tbl1, fr1, bpos1, choice1, plan1, items1, istart1, nbc1, bestp1, step1⟩ _
    simp only [slot.h_cx_restarts_loop0_loop0.body, lift, ite_ok]
    step*
    all_goals (repeat (split <;> step*))
    all_goals scalar_tac
  · trivial
@[local step]
theorem cx_restarts_loop0_spec (input : Slice Std.U8) (mstart : Slice Std.U32) (mc : Slice Std.U32)
  (tbl : Slice Std.U32) (fr : Slice Std.U32) (bpos : Slice Std.U32)
  (bend : Array Std.U32 512#usize) (choice : Slice Std.U32)
  (plan : Slice Std.U32) (nbmax : Std.Usize) (lamh : Std.U32)
  (items : alloc.vec.Vec Std.U32) (istart : alloc.vec.Vec Std.U32)
  (pr : Std.Usize) (chw : Std.Usize) (restarts : Std.Usize) (n : Std.Usize)
  (jitteron : Std.Usize) (restart : Std.Usize) :
    slot.h_cx_restarts_loop0 input mstart mc tbl fr bpos bend choice plan nbmax lamh items istart pr chw restarts n jitteron restart ⦃ fun _ => True ⦄ := by
  rw [slot.h_cx_restarts_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun s => restarts.val - s.2.2.2.2.2.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨tbl1, fr1, bpos1, choice1, plan1, items1, istart1, restart1⟩ _
    simp only [slot.h_cx_restarts_loop0.body, lift, ite_ok]
    step*
    all_goals (repeat (split <;> step*))
    all_goals scalar_tac
  · trivial
@[local step]
theorem cx_restarts_spec (input : Slice Std.U8) (mstart : Slice Std.U32) (mc : Slice Std.U32)
  (tbl : Slice Std.U32) (fr : Slice Std.U32) (bpos : Slice Std.U32)
  (bend : Array Std.U32 512#usize) (choice : Slice Std.U32)
  (plan : Slice Std.U32) (nbmax : Std.Usize) (lamh : Std.U32)
  (items : alloc.vec.Vec Std.U32) (istart : alloc.vec.Vec Std.U32)
  (pr : Std.Usize) (chw : Std.Usize) (restarts : Std.Usize) :
    slot.h_cx_restarts input mstart mc tbl fr bpos bend choice plan nbmax lamh items istart pr chw restarts ⦃ fun _ => True ⦄ := by
  rw [slot.h_cx_restarts]
  try simp only [lift, ite_ok, alloc.vec.Vec.deref_mut, bind_tc_ok]
  step*
  all_goals (repeat (split <;> step*))
  all_goals scalar_tac
@[local step]
theorem iterate_loop_spec (mode : Std.Usize) (input : Slice Std.U8) (mstart : Slice Std.U32) (mc : Slice Std.U32) (tbl : Slice Std.U32) (fr : Slice Std.U32) (bpos : Slice Std.U32) (bend : Array Std.U32 512#usize) (choice : Slice Std.U32) (nbmax : Std.Usize) (gk : Std.U64) (lamh : Std.U32) (minp : Std.Usize) (ew : Std.U32) (n : Std.Usize) (nb : Std.Usize) (best : Std.U64) (prev : Std.U64) (stop : Std.Usize) (it : Std.Usize) (items : alloc.vec.Vec Std.U32) (istart : alloc.vec.Vec Std.U32) (kp0 : Std.Usize) (pr : Std.Usize) (wh : Std.Usize) (bh : Std.Usize) (chw : Std.Usize) :
    slot.h_iterate_loop mode input mstart mc tbl fr bpos bend choice nbmax gk lamh minp ew n nb best prev stop it items istart kp0 pr wh bh chw ⦃ fun _ => True ⦄ := by
  rw [slot.h_iterate_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => slot.H_ITERS.val - qq9.2.2.2.2.2.2.2.2.1.val)
    (inv := fun _ => True)
  · rintro ⟨tbl1, fr1, bpos1, choice1, nb1, best1, prev1, stop1, it1, items1, istart1, pr1, wh1, bh1⟩ _
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.h_iterate_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem iterate_spec (mode : Std.Usize) (input : Slice Std.U8) (mstart : Slice Std.U32) (mc : Slice Std.U32) (tbl : Slice Std.U32) (fr : Slice Std.U32) (bpos : Slice Std.U32) (bend : Array Std.U32 512#usize) (choice : Slice Std.U32) (plan : Slice Std.U32) (nbmax : Std.Usize) (nb0 : Std.Usize) (best0 : Std.U64) (prev0 : Std.U64) (gk : Std.U64) (lamh : Std.U32) (minp : Std.Usize) (ew : Std.U32) :
    slot.h_iterate mode input mstart mc tbl fr bpos bend choice plan nbmax nb0 best0 prev0 gk lamh minp ew ⦃ fun _ => True ⦄ := T15! slot.h_iterate
@[local step]
theorem lit_bpos_loop_spec (bpos : Slice Std.U32) (m : Std.Usize) (b : Std.Usize) :
    slot.h_lit_bpos_loop bpos m b ⦃ fun _ => True ⦄ := by
  rw [slot.h_lit_bpos_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => m.val - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨bpos1, b1⟩ _
    simp only [slot.h_lit_bpos_loop.body, lift, ite_ok]
    step*
    repeat (split <;> step*)
    all_goals scalar_tac
  · trivial
@[local step]
theorem lit_bpos_spec (bpos : Slice Std.U32) (m : Std.Usize) :
    slot.h_lit_bpos bpos m ⦃ fun _ => True ⦄ := T14! slot.h_lit_bpos
@[local step]
theorem optimize_spec (mode : Std.Usize) (input : Slice Std.U8) (mstart : Slice Std.U32) (mc : Slice Std.U32) (tbl : Slice Std.U32) (fr : Slice Std.U32) (bpos : Slice Std.U32) (bend : Array Std.U32 512#usize) (choice : Slice Std.U32) (plan : Slice Std.U32) (nbmax : Std.Usize) (gk : Std.U64) (i5 : Std.Usize) :
    slot.h_optimize mode input mstart mc tbl fr bpos bend choice plan nbmax gk i5 ⦃ fun _ => True ⦄ := T15! slot.h_optimize
set_option hygiene false in
local notation "T23!" q0__:max => (by
  rw [q0__]
  try simp only [ite_ok]
  step*
  repeat (first
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals scalar_tac)
set_option hygiene false in
local notation "T24!" q0__:max => (by
  rw [q0__]
  simp only [lift, ite_ok, alloc.vec.Vec.deref_mut, bind_tc_ok]
  step*
  repeat (first
    | (split <;> (try step*))
    | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
    | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
    | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals scalar_tac)
set_option hygiene false in
local notation "T25!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 512 - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨dst1, i1⟩ _
    simp only [q1__, lift, ite_ok]
    step*
    repeat (first
      | (split <;> (try step*))
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply spec_ite_cut <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals scalar_tac
  · trivial)
set_option hygiene false in
local notation "T26!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 32 - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨dst1, i1⟩ _
    simp only [q1__, lift, ite_ok]
    step*
    repeat (first
      | (split <;> (try step*))
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply spec_ite_cut <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals scalar_tac
  · trivial)
set_option hygiene false in
local notation "T27!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => nb.val - qq9.val)
    (inv := fun b => b.val < Std.Usize.max)
  · rintro b1 hb1
    simp only [q1__]
    try simp only [lift, ite_ok, alloc.vec.Vec.deref_mut, bind_tc_ok]
    step*
    all_goals repeat (first
      | (split <;> (try step*))
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply spec_ite_cut <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals (split_ifs at * <;> simp_all <;> scalar_tac)
  · exact hb)
set_option hygiene false in
local notation "T28!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => 32768 - qq9.2.val)
    (inv := fun _ => True)
  · rintro ⟨ed1, e1⟩ _
    simp only [q1__]
    try simp only [lift, ite_ok, alloc.vec.Vec.deref_mut, bind_tc_ok]
    step*
    all_goals repeat (first
      | (split <;> (try step*))
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply spec_ite_cut <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals scalar_tac
  · trivial)
set_option hygiene false in
local notation "T29!" q0__:max q1__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => starts.length - qq9.2.2.2.2.2.2.2.2.2.1.val)
    (inv := fun s => s.2.2.2.2.2.2.2.2.2.2.val < Std.Usize.max)
  · rintro ⟨cand1, arr1, ed1, llf1, df1, litc1, lcost1, dcs1, dcb1, j1, b1⟩ hb1
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    have hstarts : starts.length ≤ Std.Usize.max := Std.Slice.length_ineq starts
    simp only [q1__]
    try simp only [lift, ite_ok, alloc.vec.Vec.deref_mut, bind_tc_ok]
    step*
    all_goals repeat (first
      | (split <;> (try step*))
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply spec_ite_cut <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals scalar_tac
  · exact hb)
set_option hygiene false in
local notation "T30!" q0__:max q1__:max q2__:max => (by
  rw [q0__]
  apply Std.loop.spec_decr_nat
    (measure := fun qq9 => q1__ - qq9.2.2.2.2.2.2.2.2.2.2.2.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨plan1, tbl1, fr1, bpos1, cand1, arr1, ed1, llf1, df1, litc1, lcost1, dcs1, dcb1, pi1⟩ _
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    have hstarts : starts.length ≤ Std.Usize.max := Std.Slice.length_ineq starts
    simp only [q2__]
    try simp only [lift, ite_ok, alloc.vec.Vec.deref_mut, bind_tc_ok]
    step*
    all_goals repeat (first
      | (split <;> (try step*))
      | (guard_hyp x :~ _ × _ × _ × _ × _; obtain ⟨r1, r2, r3, r4, r5⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _ × _; obtain ⟨r1, r2, r3, r4⟩ := x; try step*)
      | (guard_hyp x :~ _ × _ × _; obtain ⟨r1, r2, r3⟩ := x; try step*)
      | (guard_hyp x :~ _ × _; obtain ⟨r1, r2⟩ := x; try step*)
      | (apply spec_ite_cut <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals scalar_tac
  · trivial)
@[local step]
theorem mode_gk_spec (mode : Std.Usize) (base : Std.U64) :
    slot.h_mode_gk mode base ⦃ fun _ => True ⦄ := by
  rw [slot.h_mode_gk]
  step*
  all_goals (repeat (split <;> step*))
  all_goals scalar_tac
@[local step]
theorem champ_spec (mode : Std.Usize) (input : Slice Std.U8) (plan : Slice Std.U32) (gk : Std.U64) (i5 : Std.Usize) :
    slot.h_champ mode input plan gk i5 ⦃ fun _ => True ⦄ := T15! slot.h_champ
@[local step]
theorem champ_if_spec (mode : Std.Usize) (input : Slice Std.U8) (plan : Slice Std.U32) (on : Std.Usize) (gk : Std.U64) (i5 : Std.Usize) :
    slot.h_champ_if mode input plan on gk i5 ⦃ fun _ => True ⦄ := T14! slot.h_champ_if
@[local step]
theorem parse_mode_spec (input : Slice Std.U8) (out : Slice Std.U32) (mode : Std.Usize)
    (hlen : input.length ≤ out.length) :
    slot.h_parse_mode input out mode ⦃ fun r =>
      r.1.val ≤ input.length ∧
      r.2.length = out.length ∧
      LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
  rw [slot.h_parse_mode]
  simp only [lift, alloc.vec.Vec.deref_mut, bind_tc_ok]
  step*
  exact ⟨r_post1, r_post2, r_post3⟩
end EH


end Submission

namespace Submission
open Aeneas Aeneas.Std Result ControlFlow
open LZ77 (toks bytes)
set_option maxRecDepth 8192
set_option maxHeartbeats 4000000

attribute [local step] s_parse_spec EH.parse_mode_spec classify_spec

theorem parse_spec (input : Slice Std.U8) (out : Slice Std.U32)
    (hlen : input.length ≤ out.length) :
    slot.parse input out ⦃ fun r =>
      r.1.val ≤ input.length ∧
      r.2.length = out.length ∧
      LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
  rw [slot.parse]
  step*

end Submission
