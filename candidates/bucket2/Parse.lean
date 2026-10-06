import Lz77
import Slot

/-!
# fastX fx17 engine (`VERIFY = 0`): the proof of `parse_spec`

The engine: a content class from a strided byte histogram (`sniff`: DNA-like, text, prose,
structured text, high-entropy binaries with and without zero bytes, other binaries), then per
class hash chains on 4-byte keys (3 for structured binaries), a chain walk, a lazy step that
may move the match one byte on, **backward token merging** (a new match swallows the tokens
just written when their bytes also match at its distance), recording of the first `INS_MAX`,
every `STRIDE`-th and the last `TAIL` positions inside a match, and skip acceleration with a
cap. `walk`, `insert`, `find` and `run` are generic in the table sizes (`H` chain heads, `W`
window entries): small inputs get small tables. With `VERIFY = 0` nothing re-checks a match
when it is written, so the search itself must deliver the byte comparisons: this proof
carries them from `common` through `walk`, `find`, the lazy loop and the backward merge to
`put_match`.

## The tiny-input path (section 0)

`parse` sends inputs of at most `TF_N` bytes to `tf_plan` (a planner: search only) and `emit`
(plan + re-verify, pkB): a planned match is written only after `check` has re-compared its bytes
with `mlen`, else a literal. Section 0 is a `section` of its own placed before the fx17 sections:
0a (`get0`, `set_in`, `load8`, `first_diff`, `mlen`, `check`, `emit`: the decode invariant for any
plan), 0c (the planner: totality only, replaceable). `parse_spec` (section 15) splits on
`input.len() <= TF_N`; the larger inputs keep fx17's proof below unchanged.

## Layers (each one is replaced on its own)

1. `word8`, `be8_spec`: arithmetic of eight big-endian bytes (no Rust shape beyond `be8`).
2. `common_spec` (`l ≤ cap ∧ Matches s a b l`), `same_spec` (`r = 1 → Matches s a b len`):
   the only functions that compare bytes.
3. `gain_spec`, `insert_spec`: bookkeeping (no overflow; `insert` keeps `HeadBound`).
4. `walk_spec`, `find_spec`: the search; postcondition `FoundAt` (`l < 3 ∨ MatchAt`).
5. Token streams: `Dec` (tokens so far decode to the input so far) with its four steps
   `Dec.lit`, `Dec.match` (writes) and `Dec.pop_lit`, `Dec.pop_match` (retractions for the
   backward merge), `put_lit_spec`, `put_match_spec`.
6. The loops of `run`, each with a named invariant: `BackInv` (backward merge), `LazyInv`
   (lazy step), `MainInv` (main loop), and specs for the insert, stride, skip and tail loops.
7. `sniff_spec` (total), `run_spec` (any table sizes `0 < H`, `0 < W`), `run_rest_spec`,
   `parse_spec` (the obligation, statement unchanged).

## Invariants

* `Dec s out nt p := p ≤ n ∧ nt ≤ p ∧ n ≤ out.length ∧ decode (toks out nt) = take p`.
* `MatchAt s p l d := 3 ≤ l ≤ 258 ∧ p + l ≤ n ∧ 1 ≤ d ≤ 32768 ∧ d ≤ p ∧ Matches s (p-d) p l`
  (the real-match half of `LZ77.Found`, on `Nat`s).
* `HeadBound head B`: every head entry is `≤ B` (the chain start of a walk at `p` is `≤ p`),
  for a head table of any size.
* `MainInv := Dec ∧ out.length = L ∧ HeadBound head p ∧ miss ≤ p`.
* `LazyInv := Dec ∧ out.length = L ∧ MatchAt p l d ∧ HeadBound head (p+1) ∧ p < lim ∧ ins ≤ p+2`.
* `BackInv := Dec nt p ∧ MatchAt p l d ∧ p + l = E ∧ p ≤ P0`.
* Stride loop: `ins ≤ end ∧ (ins = its start ∨ ins + TAIL < end)`, measure `end - ins`.

## The Rust shapes this proof relies on

* `be8`: `if i + 8 <= s.len() { (s[i] as u64) << 56 | ... | s[i+7] as u64 } else { 0 }`
  (`be8_nat` is the or-to-sum identity for exactly this chain).
* `common`: word loop `while run == 1 && k + 8 <= cap` with `x == 0` / `leading_zeros(x) / 8`,
  then a byte loop; needs `cap ≤ 258`. `same`: word loop, masked last word
  `x >> (64 - 8 (len - k)) != 0`, byte loops; needs `len ≤ 258` and `a + len + 7 ≤ usize::MAX`.
* `walk`: candidate test `p.wrapping_sub(c).wrapping_sub(1) < 32768 && c + best < n`, chain
  step only if `nx < c` (so `c ≤ p` is invariant), counter `k` as the measure.
* `put_match` with `VERIFY = 0`: range checks, then the token `2^24 + (d-1)*256 + (l-3)`.
* `run`: the loop state is `(out, nt, p, head, prev, ins, miss, fuel)`; `fuel` decreases every
  iteration. Inside a match: `ins.wrapping_add(INS_MAX)` for the head cap, the stride loop
  `while end - ins > TAIL + STRIDE && ins < lim` under `if STRIDE > 0` (`ins ≤ end` there:
  `ins ≤ p + 2 < p + l = end`), the tail test `ins + TAIL < end`. `sniff` samples with
  `while i < n && tot < 4097` and `i.wrapping_add(step)`. These are the places where the
  first fx17 arithmetic could overflow in the model for a slice of `usize::MAX` bytes (never
  on a real input; the machine code is the same or shorter).
* The table sizes reach `run` as explicit arguments (literals in the model): `run_spec` needs
  only `0 < H` and `0 < W` (for `% H`, `% W`).

## Constants

The proof reads constant values only through the `slot.X.val = n` lemmas the verifier derives
from plain literal constants, inside `step*` and `scalar_tac` (and `GBASE` from its definition,
`GBASE_bound`); it holds for every value set with: `VERIFY = 0`; `TAIL ≤ 7`; `1 ≤ HB ≤ 64`;
table sizes `HN, WN, HS, WS ≥ 1`; `SAMPLE ≥ 1`, `SDIG ≥ 1`, `LSLACK ≥ 1`; every skip shift
`≤ 31`; `HLIT ≤ 4000000` and `|GBASE| ≤ 1000000000` (the `i32` arithmetic of `gain`);
`TAIL + STRIDE < 2^32`; every constant a plain decimal literal. Depths, lazy thresholds,
`NICE`, `INS_MAX`, `STRIDE` (0 included), `BACKTOK`, `SMALL`, the skip caps and the walk
depths of the lazy step are free.

## Tactic patterns

* Search code: `step*; repeat' (split <;> step*)`, then one `all_goals first | ... | ...`
  closer. Lemmas that close generated goals take the facts `step*` leaves in an order where
  `by assumption` only has to match cheap patterns (the goal fixes the new state; a
  `refine ⟨Lemma .., by scalar_tac⟩` elaborates the lemma against it first) and every
  arithmetic fact is `by scalar_tac`. `by assumption` on a pattern with a large literal
  (`↑?x = ↑t - 16777216`) recurses into `Nat.sub` and fails: prove those by `scalar_tac`.
* Ghost variables of a spec (`B` in `insert_spec`, `T` in `cnt_index_spec`, `L`) are fixed by
  `step*` from the hypotheses; state the other preconditions so that only the intended
  hypothesis matches (`i.val < B + 1` instead of `i.val ≤ B`), or wrap the spec (`back_loop_spec`,
  `lazy_loop_spec`, `main_loop_spec'`) so that it has no ghost and flat pre/postconditions.
* A precondition `step*` cannot prove (a `Dec`, `MatchAt` or `HeadBound` that needs a lemma)
  becomes a separate goal and `step*` goes on: close those in the final `first` block.
* The heartbeat budget is per declaration: the main loop (about 35 goals after `step*`) gets
  its own. `run_rest_spec` and `parse_spec` are written out (`split`, `exact run_spec ..`):
  through `step*` the kernel check of `run_rest_spec` alone took over a minute.
-/
namespace Submission
open Aeneas Aeneas.Std Result ControlFlow

set_option maxRecDepth 8192
set_option maxHeartbeats 4000000
set_option linter.unusedVariables false

open LZ77 (toks bytes bytes_length bytes_getElem! toks_update bytes_congr
  Matches Found emit_lit emit_match ite_ok)
open LZ77 (decode emit copyN tokLen tokDist MATCH_BASE TOK_LIMIT decode_snoc copyN_length)

/-! ## 0. The tiny-input path: plan + re-verify (sections 0a-0c)

`parse` sends inputs of at most `TF_N` bytes to `let plan = tf_plan(input); emit(input, &plan, out)`.
This block is a `section` of its own: its `@[local step]` rules end with it, and the rules of the fx17
sections below (`lz_spec`, `be8_spec`, `cnt_index_spec`, `insert_spec`, ...) are not in scope here, so
the planner's lemmas see a clean `step*`. Only two names leave it: `emit_spec` (0a) and
`tf_plan_spec` (0c), used by `parse_spec` at the end of the file.

* 0a (fixed, the load-bearing part): `get0`, `set_in` (guarded accessors), `load8`, `first_diff`,
  `mlen` (word-wise match length, `l ≤ cap ∧ Matches`), `check` (`valid = true →` exactly the
  hypotheses of `emit_match`), `emit` (pkB's greedy decode invariant with dnal's plan index `k` and
  `owed` literals: the plan is a token list, untrusted).
* 0b: step rules shared with the planner (`tp_lift_spec`, `tp_numBits_ge'` and the 0a specs, still in scope).
* 0c (replaceable): the planner, totality only (postcondition `True`), pkB's recipe. -/

section TinyPath

-- The search recipe is uniform on purpose; where a step of it has nothing to do, say nothing.
set_option linter.unusedTactic false
set_option linter.unreachableTactic false

/-! ### 0a. Step rules, words, the match check, the emission -/

/-- Any pure operation in bind position (`lift (saturating_add ..)`, `lift (deref_mut ..)`, casts,
    `wrapping_*`, `leading_zeros`): `step*` names its result instead of stopping. -/
@[local step]
theorem tp_lift_spec {α : Type} (x : α) : lift x ⦃ fun y => y = x ⦄ := by
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

/-- `usize` has at least 32 bits: a planner's `usize` shift by a variable below 32 needs it
    (`scalar_tac` instantiates it whenever `System.Platform.numBits` occurs). -/
theorem tp_numBits_ge : 32 ≤ System.Platform.numBits := by
  cases System.Platform.numBits_eq <;> simp [*]

@[local scalar_tac System.Platform.numBits]
theorem tp_numBits_ge' : 32 ≤ System.Platform.numBits := tp_numBits_ge

/-- The eight bytes at `p` as a big-endian number, in the Horner form `load8` computes:
    byte `p + k` is base-256 digit `7 - k`. -/
def sp_word8 (input : Slice Std.U8) (p : Nat) : Nat :=
  ((((((((input.val[p]!).val * 256 + (input.val[p + 1]!).val) * 256
    + (input.val[p + 2]!).val) * 256 + (input.val[p + 3]!).val) * 256
    + (input.val[p + 4]!).val) * 256 + (input.val[p + 5]!).val) * 256
    + (input.val[p + 6]!).val) * 256 + (input.val[p + 7]!).val)

theorem sp_u8_lt (x : Std.U8) : x.val < 256 := by scalar_tac

/-- Byte `p + k` of the word is digit `7 - k` of the number. -/
theorem sp_word8_digit (input : Slice Std.U8) (p k : Nat) (hk : k < 8) :
    (input.val[p + k]!).val = sp_word8 input p / 256 ^ (7 - k) % 256 := by
  have := sp_u8_lt (input.val[p]!); have := sp_u8_lt (input.val[p+1]!)
  have := sp_u8_lt (input.val[p+2]!); have := sp_u8_lt (input.val[p+3]!)
  have := sp_u8_lt (input.val[p+4]!); have := sp_u8_lt (input.val[p+5]!)
  have := sp_u8_lt (input.val[p+6]!); have := sp_u8_lt (input.val[p+7]!)
  simp only [sp_word8]
  rcases (show k = 0 ∨ k = 1 ∨ k = 2 ∨ k = 3 ∨ k = 4 ∨ k = 5 ∨ k = 6 ∨ k = 7 by omega) with
    rfl | rfl | rfl | rfl | rfl | rfl | rfl | rfl <;> simp only [Nat.add_zero, Nat.pow_zero,
    Nat.pow_succ, Nat.one_mul, Nat.sub_self, Nat.reduceSub] <;> omega

/-- Words that agree above bit `64 - 8 d` (their top `d` bytes, `d ≤ 8`) start with `d` equal
    bytes. `d = 8` is plain equality of the words. -/
theorem sp_word8_prefix (input : Slice Std.U8) (a b d : Nat) (hd : d ≤ 8)
    (h : sp_word8 input a / 2 ^ (64 - 8 * d) = sp_word8 input b / 2 ^ (64 - 8 * d)) :
    ∀ k, k < d → input.val[b + k]! = input.val[a + k]! := by
  intro k hk
  have e : (256 : Nat) ^ (7 - k) = 2 ^ (64 - 8 * d) * 2 ^ (8 * (d - 1 - k)) := by
    rw [← pow_add, show (256 : Nat) = 2 ^ 8 by norm_num, ← pow_mul]
    congr 1; omega
  have key : sp_word8 input a / 256 ^ (7 - k) = sp_word8 input b / 256 ^ (7 - k) := by
    rw [e, ← Nat.div_div_eq_div_mul, ← Nat.div_div_eq_div_mul, h]
  have ha := sp_word8_digit input a k (by omega)
  have hb := sp_word8_digit input b k (by omega)
  rw [key] at ha
  scalar_tac

/-- A match of `l` bytes followed by words sharing their top `d` bytes is a match of `l + d`. -/
theorem Matches.sp_add_prefix {input : Slice Std.U8} {a b l d : Nat} (h : Matches input a b l)
    (hd : d ≤ 8)
    (hw : sp_word8 input (a + l) / 2 ^ (64 - 8 * d) = sp_word8 input (b + l) / 2 ^ (64 - 8 * d)) :
    Matches input a b (l + d) := by
  intro k hk
  by_cases hkl : k < l
  · exact h k hkl
  · have := sp_word8_prefix input (a + l) (b + l) d hd hw (k - l) (by omega)
    rw [show b + l + (k - l) = b + k by omega, show a + l + (k - l) = a + k by omega] at this
    exact this

/-- `Matches.sp_add_prefix` in the shape the extracted loop body leaves: the loads at `a + l` and
    `b + l` returned `x` and `y`, and `first_diff x y` returned `d`. -/
theorem Matches.sp_word {input : Slice Std.U8} {a b l l' : Nat} {pa pb d : Std.Usize}
    {x y : Std.U64} (h : Matches input a b l) (hpa : pa.val = a + l) (hpb : pb.val = b + l)
    (hx : x.val = sp_word8 input pa.val) (hy : y.val = sp_word8 input pb.val)
    (hd8 : d.val ≤ 8) (hdiv : x.val / 2 ^ (64 - 8 * d.val) = y.val / 2 ^ (64 - 8 * d.val))
    (hl' : l' = l + d.val) : Matches input a b l' := by
  subst hl'
  rw [hx, hy, hpa, hpb] at hdiv
  exact Matches.sp_add_prefix h hd8 hdiv

/-- Equal words: eight more bytes. -/
theorem Matches.sp_word_eq {input : Slice Std.U8} {a b l l' : Nat} {pa pb : Std.Usize}
    {x y : Std.U64} (h : Matches input a b l) (hpa : pa.val = a + l) (hpb : pb.val = b + l)
    (hx : x.val = sp_word8 input pa.val) (hy : y.val = sp_word8 input pb.val)
    (hxy : ¬(x != y) = true) (hl' : l' = l + 8) : Matches input a b l' := by
  have hxy' : x.val = y.val := by simpa using hxy
  subst hl'
  apply Matches.sp_add_prefix h (le_refl 8)
  rw [← hpa, ← hpb, ← hx, ← hy, hxy']

/-- One more equal byte, in the shape the extracted byte loop leaves. -/
theorem Matches.sp_byte {input : Slice Std.U8} {a b l l' : Nat} {pa pb : Std.Usize}
    {x y : Std.U8} (h : Matches input a b l) (hpa : pa.val = a + l) (hpb : pb.val = b + l)
    (hpa' : pa.val < input.val.length) (hpb' : pb.val < input.val.length)
    (hx : x = input.val[pa.val]) (hy : y = input.val[pb.val]) (hxy : x = y)
    (hl' : l' = l + 1) : Matches input a b l' := by
  subst hl' hxy
  apply LZ77.Matches.succ h
  rw [← hpa, ← hpb, getElem!_pos input.val pa.val hpa', getElem!_pos input.val pb.val hpb',
    ← hx, ← hy]

theorem sp_nat_xor_eq_zero {a b : Nat} (h : a ^^^ b = 0) : a = b := by
  have : a ^^^ (a ^^^ b) = b := by rw [← Nat.xor_assoc, Nat.xor_self, Nat.zero_xor]
  rw [h, Nat.xor_zero] at this; exact this

/-- Numbers whose xor is below `2^m` agree above bit `m`. -/
theorem sp_div_eq_of_xor_lt {x y m : Nat} (hz : x ^^^ y < 2 ^ m) : x / 2 ^ m = y / 2 ^ m := by
  have h : (x ^^^ y) >>> m = 0 := by rw [Nat.shiftRight_eq_div_pow]; exact Nat.div_eq_of_lt hz
  rw [Nat.shiftRight_xor_distrib] at h
  have := sp_nat_xor_eq_zero h
  simpa [Nat.shiftRight_eq_div_pow] using this

/-- A 64-bit value is below `2^(64 - 8 (lz / 8))` where `lz` counts its leading zeros. -/
theorem sp_lt_pow_leadingZeros (z : BitVec 64) :
    z.toNat < 2 ^ (64 - 8 * (BitVec.leadingZeros z / 8)) := by
  unfold BitVec.leadingZeros
  split
  case isTrue h => subst h; simp
  case isFalse h =>
    have hz : z.toNat ≠ 0 := by
      intro h0; apply h; exact BitVec.eq_of_toNat_eq (by simpa using h0)
    have hlog : Nat.log 2 z.toNat < 64 := Nat.log_lt_of_lt_pow hz z.isLt
    have h1 : z.toNat < 2 ^ (Nat.log 2 z.toNat).succ := Nat.lt_pow_succ_log_self (by norm_num) _
    refine lt_of_lt_of_le h1 (Nat.pow_le_pow_right (by norm_num) ?_)
    omega

@[local step]
theorem load8_spec (input : Slice Std.U8) (p : Std.Usize) (hp : p.val + 8 ≤ input.length) :
    slot.load8 input p ⦃ fun v => v.val = sp_word8 input p.val ⦄ := by
  rw [slot.load8]
  step*
  simp only [← getElem!_pos] at *
  simp only [sp_word8]
  simp_all only [U8.cast_U64_val_eq]

@[local step]
theorem first_diff_spec (x y : Std.U64) :
    slot.first_diff x y ⦃ fun d => d.val ≤ 8 ∧
      x.val / 2 ^ (64 - 8 * d.val) = y.val / 2 ^ (64 - 8 * d.val) ⦄ := by
  rw [slot.first_diff]
  step*
  have hle : BitVec.leadingZeros z.bv ≤ 64 := by unfold BitVec.leadingZeros; split <;> omega
  have hlz : lz.val = BitVec.leadingZeros z.bv := by
    rw [lz_post]
    simp only [core.num.U64.leading_zeros, UScalar.val, UScalarTy.U32_numBits_eq,
      BitVec.natCast_eq_ofNat, BitVec.toNat_ofNat, Nat.reducePow]
    omega
  have hd : (UScalar.cast UScalarTy.Usize bytes).val = BitVec.leadingZeros z.bv / 8 := by
    simp only [U32.cast_Usize_val_eq, bytes_post, hlz]
  have hz : z.bv.toNat = x.val ^^^ y.val := by
    have : z.val = z.bv.toNat := rfl
    rw [← this, z_post1, UScalar.val_xor]
  refine ⟨by rw [hd]; omega, ?_⟩
  rw [hd]
  apply sp_div_eq_of_xor_lt
  rw [← hz]
  exact sp_lt_pow_leadingZeros z.bv

@[local step]
theorem mlen_loop0_loop0_spec (input : Slice Std.U8) (a b cap l0 : Std.Usize)
    (ha : a.val + cap.val ≤ input.length) (hb : b.val + cap.val ≤ input.length)
    (hl0 : l0.val ≤ cap.val) (h0 : Matches input a.val b.val l0.val) :
    slot.mlen_loop0_loop0 input a b cap l0 ⦃ fun l => l.val ≤ cap.val ∧ Matches input a.val b.val l.val ⦄ := by
  rw [slot.mlen_loop0_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun l => cap.val - l.val)
    (inv := fun l => l.val ≤ cap.val ∧ Matches input a.val b.val l.val)
  · rintro l ⟨hle, hm⟩
    simp only [slot.mlen_loop0_loop0.body]
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    step*
    refine ⟨by scalar_tac, ?_, by scalar_tac⟩
    exact Matches.sp_byte hm (by assumption) (by assumption) (by scalar_tac) (by scalar_tac)
      (by assumption) (by assumption) (by assumption) (by scalar_tac)
  · exact ⟨hl0, h0⟩

@[local step]
theorem mlen_loop0_spec (input : Slice Std.U8) (a b cap l0 : Std.Usize)
    (ha : a.val + cap.val ≤ input.length) (hb : b.val + cap.val ≤ input.length)
    (hl0 : l0.val ≤ cap.val) (h0 : Matches input a.val b.val l0.val) :
    slot.mlen_loop0 input a b cap l0 ⦃ fun l => l.val ≤ cap.val ∧ Matches input a.val b.val l.val ⦄ := by
  rw [slot.mlen_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun l => cap.val - l.val)
    (inv := fun l => l.val ≤ cap.val ∧ Matches input a.val b.val l.val)
  · rintro l ⟨hle, hm⟩
    simp only [slot.mlen_loop0.body]
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    -- `step*` also takes the exit branch, through `mlen_loop0_loop0_spec`
    step*
    · -- the words differ: `first_diff` bytes more, and the loop is over
      refine ⟨by scalar_tac, ?_⟩
      exact Matches.sp_word hm (by assumption) (by assumption) (by assumption) (by assumption)
        (by assumption) (by assumption) (by scalar_tac)
    · -- equal words: eight bytes more
      refine ⟨by scalar_tac, ?_, by scalar_tac⟩
      exact Matches.sp_word_eq hm (by assumption) (by assumption) (by assumption) (by assumption)
        (by assumption) (by scalar_tac)
  · exact ⟨hl0, h0⟩

/-- `mlen` is the length of an actual match, at most `cap` (both ranges inside the input). -/
@[local step]
theorem mlen_spec (input : Slice Std.U8) (a b cap : Std.Usize)
    (ha : a.val + cap.val ≤ input.length) (hb : b.val + cap.val ≤ input.length) :
    slot.mlen input a b cap ⦃ fun l => l.val ≤ cap.val ∧ Matches input a.val b.val l.val ⦄ :=
  mlen_loop0_spec input a b cap 0#usize ha hb (by simp) (LZ77.Matches.zero input a.val b.val)

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

/-- The emission: pkB's greedy decode invariant with the plan index `k` and the `owed` literals
    (the dnal form): every branch writes one token at `ntok` (`k ≤ p` keeps `k + 1` in range; `owed`
    is unconstrained). The plan is read only through `get0` and decides nothing (`check` does). -/
theorem emit_loop_spec (input : Slice Std.U8) (plan out0 : Slice Std.U32)
    (n ntok0 k0 owed0 p0 : Std.Usize) (hn : n.val = input.length) (hout : input.length ≤ out0.length)
    (hp0 : p0.val ≤ n.val) (hntok0 : ntok0.val ≤ p0.val) (hk0 : k0.val ≤ p0.val)
    (hdec0 : LZ77.decode (toks out0 ntok0.val) = some ((bytes input).take p0.val)) :
    slot.emit_loop input plan out0 n ntok0 k0 owed0 p0 ⦃ fun r =>
      r.1.val ≤ input.length ∧ r.2.length = out0.length ∧
      LZ77.decode (toks r.2 r.1.val) = some (bytes input) ⦄ := by
  rw [slot.emit_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, p) => n.val - p.val)
    (inv := fun (out, ntok, k, _, p) => p.val ≤ n.val ∧ ntok.val ≤ p.val ∧ k.val ≤ p.val ∧
      out.length = out0.length ∧
      LZ77.decode (toks out ntok.val) = some ((bytes input).take p.val))
  · rintro ⟨out, ntok, k, owed, p⟩ ⟨hp, hnt, hk, hlen, hde⟩
    simp only [slot.emit_loop.body]
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    split
    case isTrue hlt =>
      have hntok_lt : ntok.val < out.length := by scalar_tac
      step*
      · -- an owed literal: `input[p]`, advance 1
        have hlit : i1.val = (bytes input)[p.val]! := by
          rw [bytes_getElem! input p.val (by scalar_tac)]
          scalar_tac
        refine ⟨by scalar_tac, by scalar_tac, by scalar_tac, by rw [s_post]; simpa using hlen, ?_,
          by scalar_tac⟩
        rw [s_post, show ntok1.val = ntok.val + 1 by scalar_tac,
          show p1.val = p.val + 1 by scalar_tac]
        exact emit_lit input out ntok p.val i1 hde (by scalar_tac) hntok_lt hlit
      · -- `check` accepted the planned `(len, dist)`: write the match token, advance `len`
        obtain ⟨h3, h258, hd1, hd32k, hdp, hend, hm⟩ := valid_post (by assumption)
        have htok : tok.val = LZ77.mkMatch dist.val len.val := by
          simp only [LZ77.mkMatch, LZ77.MATCH_BASE]
          scalar_tac
        refine ⟨by scalar_tac, by scalar_tac, by scalar_tac, by rw [s_post]; simpa using hlen, ?_,
          by scalar_tac⟩
        rw [s_post, show ntok1.val = ntok.val + 1 by scalar_tac,
          show p1.val = p.val + len.val by scalar_tac]
        exact emit_match input out ntok p.val dist.val len.val tok hde hntok_lt hd1 hdp hd32k
          h3 h258 hend hm htok
      all_goals
        -- rejected: the literal `input[p]` (written through `index_mut_usize`), advance 1
        have hlit : i3.val = (bytes input)[p.val]! := by
          rw [bytes_getElem! input p.val (by scalar_tac)]
          scalar_tac
        subst index_mut_back
        refine ⟨by scalar_tac, by scalar_tac, by scalar_tac, by simpa using hlen, ?_, by scalar_tac⟩
        rw [show ntok1.val = ntok.val + 1 by scalar_tac, show p1.val = p.val + 1 by scalar_tac]
        exact emit_lit input out ntok p.val i3 hde (by scalar_tac) hntok_lt hlit
    case isFalse hge =>
      have hpn : p.val = input.length := by scalar_tac
      refine ⟨by scalar_tac, hlen, ?_⟩
      rw [hde, hpn]
      simp
  · exact ⟨hp0, hntok0, hk0, rfl, hdec0⟩

/-- Any plan: the tokens `emit` writes decode to the input. -/
@[local step]
theorem emit_spec (input : Slice Std.U8) (plan out : Slice Std.U32)
    (hout : input.length ≤ out.length) :
    slot.emit input plan out ⦃ fun r =>
      r.1.val ≤ input.length ∧ r.2.length = out.length ∧
      LZ77.decode (toks r.2 r.1.val) = some (bytes input) ⦄ := by
  rw [slot.emit]
  exact emit_loop_spec input plan out (Std.Slice.len input) 0#usize 0#usize 0#usize 0#usize
    (by simp) hout (by simp) (by simp) (by simp) (by simp [toks, LZ77.decode])

/-! ### 0c. The planner: totality only

`tf_plan` and everything it calls are search: the emission (0a) re-checks every planned match, so
these lemmas only show that the planner terminates and never fails (no overflow, no index out of
range). Postconditions are `True`, except for the few facts a caller's arithmetic needs (`tf_min`,
`tf_slot`, `tf_lslot`, `tf_dslot`, `tf_piece`, `tf_act`, `tf_extend`). Every proof is one of two
shapes (pkB's recipe): `rw [slot.f]` then the three lines below for a function, and for a loop

    rw [slot.f_loop]
    apply Std.loop.spec_decr_nat (measure := ..) (inv := ..)
    · rintro ⟨..⟩ _
      simp only [slot.f_loop.body]
      step*
      repeat' (split <;> step*)
      all_goals scalar_tac
    · trivial

The Rust side keeps every function's branching at its end (bigger steps are chains of small
helpers), so `step*` never carries a long continuation into both branches of an `if`. Binders are
left untyped where no precondition names them: array sizes and constant values can change without
touching a lemma. -/

@[local step] theorem tf_at_spec (s i) : slot.tf_at s i ⦃ fun _ => True ⦄ := by
  rw [slot.tf_at]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

@[local step] theorem tf_w8_spec (s i) : slot.tf_w8 s i ⦃ fun _ => True ⦄ := by
  rw [slot.tf_w8]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

@[local step] theorem tf_w4_spec (s i) : slot.tf_w4 s i ⦃ fun _ => True ⦄ := by
  rw [slot.tf_w4]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

@[local step] theorem tf_min_spec (a b : Std.Usize) :
    slot.tf_min a b ⦃ fun r => r.val ≤ a.val ∧ r.val ≤ b.val ∧ (r.val = a.val ∨ r.val = b.val) ⦄ := by
  rw [slot.tf_min]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

@[local step] theorem tf_max_spec (a b) : slot.tf_max a b ⦃ fun _ => True ⦄ := by
  rw [slot.tf_max]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

@[local step] theorem tf_shr_spec (x sh) : slot.tf_shr x sh ⦃ fun _ => True ⦄ := by
  rw [slot.tf_shr]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

@[local step] theorem tf_slot_spec (s p mask) : slot.tf_slot s p mask ⦃ fun r => r.val < slot.TF_HN.val ⦄ := by
  rw [slot.tf_slot]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

@[local step] theorem tf_lslot_spec (l) : slot.tf_lslot l ⦃ fun r => r.val < 64 ⦄ := by
  rw [slot.tf_lslot]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

@[local step] theorem tf_dslot_spec (d) : slot.tf_dslot d ⦃ fun r => r.val < 64 ⦄ := by
  rw [slot.tf_dslot]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

@[local step]
theorem tf_common_loop0_loop0_spec (s : Slice Std.U8) (a b lim l0 : Std.Usize)
    (hab : a.val < b.val) (hb : b.val + lim.val ≤ s.length) :
    slot.tf_common_loop0_loop0 s a b lim l0 ⦃ fun _ => True ⦄ := by
  rw [slot.tf_common_loop0_loop0]
  apply Std.loop.spec_decr_nat (measure := fun l => lim.val - l.val) (inv := fun _ => True)
  · rintro l _
    simp only [slot.tf_common_loop0_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial

@[local step]
theorem tf_common_loop0_spec (s : Slice Std.U8) (a b lim l0 : Std.Usize)
    (hab : a.val < b.val) (hb : b.val + lim.val ≤ s.length) (hl : l0.val ≤ lim.val) :
    slot.tf_common_loop0 s a b lim l0 ⦃ fun _ => True ⦄ := by
  rw [slot.tf_common_loop0]
  apply Std.loop.spec_decr_nat (measure := fun l => lim.val - l.val) (inv := fun l => l.val ≤ lim.val)
  · rintro l hl
    simp only [slot.tf_common_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · exact hl

@[local step] theorem tf_common_spec (s a b cap) : slot.tf_common s a b cap ⦃ fun _ => True ⦄ := by
  rw [slot.tf_common]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

/-- The guarded push: total (its guard `len < len.saturating_add 1` is the push's precondition). -/
@[local step] theorem tf_push_spec (v x) : slot.tf_push v x ⦃ fun _ => True ⦄ := by
  rw [slot.tf_push]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

@[local step] theorem tf_insert_spec (s head prev p mask) :
    slot.tf_insert s head prev p mask ⦃ fun _ => True ⦄ := by
  rw [slot.tf_insert]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

@[local step] theorem tf_chain_loop_spec (s head0 prev0 b mask i0) :
    slot.tf_chain_loop s head0 prev0 b mask i0 ⦃ fun _ => True ⦄ := by
  rw [slot.tf_chain_loop]
  apply Std.loop.spec_decr_nat (measure := fun (_, _, i) => b.val - i.val) (inv := fun _ => True)
  · rintro ⟨head, prev, i⟩ _
    simp only [slot.tf_chain_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial

@[local step] theorem tf_chain_spec (s head prev a b mask) :
    slot.tf_chain s head prev a b mask ⦃ fun _ => True ⦄ := by
  rw [slot.tf_chain]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

@[local step] theorem tf_near_spec (c p) : slot.tf_near c p ⦃ fun _ => True ⦄ := by
  rw [slot.tf_near]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

@[local step] theorem tf_try_spec (s c p cap best) : slot.tf_try s c p cap best ⦃ fun _ => True ⦄ := by
  rw [slot.tf_try]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

@[local step] theorem tf_walk_loop_spec (s prev p cap best0 bd0 c0 k0) :
    slot.tf_walk_loop s prev p cap best0 bd0 c0 k0 ⦃ fun _ => True ⦄ := by
  rw [slot.tf_walk_loop]
  apply Std.loop.spec_decr_nat (measure := fun (_, _, _, k) => k.val) (inv := fun _ => True)
  · rintro ⟨best, bd, c, k⟩ _
    simp only [slot.tf_walk_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial

@[local step] theorem tf_walk_spec (s prev p start cap h depth) :
    slot.tf_walk s prev p start cap h depth ⦃ fun _ => True ⦄ := by
  rw [slot.tf_walk]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

@[local step] theorem tf_cap_spec (n p) : slot.tf_cap n p ⦃ fun _ => True ⦄ := by
  rw [slot.tf_cap]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

@[local step] theorem tf_floor_spec (h minl) : slot.tf_floor h minl ⦃ fun _ => True ⦄ := by
  rw [slot.tf_floor]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

@[local step] theorem tf_cand1_spec (s p cap best bd rle) :
    slot.tf_cand1 s p cap best bd rle ⦃ fun _ => True ⦄ := by
  rw [slot.tf_cand1]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

@[local step] theorem tf_cand_rep_spec (s p rep cap best bd on) :
    slot.tf_cand_rep s p rep cap best bd on ⦃ fun _ => True ⦄ := by
  rw [slot.tf_cand_rep]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

@[local step] theorem tf_cand_chain_spec (s prev p ci cap best bd depth) :
    slot.tf_cand_chain s prev p ci cap best bd depth ⦃ fun _ => True ⦄ := by
  rw [slot.tf_cand_chain]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

@[local step] theorem tf_find_spec (s prev p ci rep minl depth h rle) :
    slot.tf_find s prev p ci rep minl depth h rle ⦃ fun _ => True ⦄ := by
  rw [slot.tf_find]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

@[local step] theorem tf_lits_loop_spec (plan0 r0) : slot.tf_lits_loop plan0 r0 ⦃ fun _ => True ⦄ := by
  rw [slot.tf_lits_loop]
  apply Std.loop.spec_decr_nat (measure := fun (_, r) => r.val) (inv := fun _ => True)
  · rintro ⟨plan, r⟩ _
    simp only [slot.tf_lits_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial

@[local step] theorem tf_lits_spec (plan run) : slot.tf_lits plan run ⦃ fun _ => True ⦄ := by
  rw [slot.tf_lits]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

@[local step] theorem tf_put_spec (plan run l d) : slot.tf_put plan run l d ⦃ fun _ => True ⦄ := by
  rw [slot.tf_put]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

@[local step] theorem tf_iszero_spec (b) : slot.tf_iszero b ⦃ fun _ => True ⦄ := by
  rw [slot.tf_iszero]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

@[local step] theorem tf_isctl_spec (b) : slot.tf_isctl b ⦃ fun _ => True ⦄ := by
  rw [slot.tf_isctl]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

@[local step] theorem tf_isdig_spec (b) : slot.tf_isdig b ⦃ fun _ => True ⦄ := by
  rw [slot.tf_isdig]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

@[local step]
theorem tf_class_loop_spec (s : Slice Std.U8) (n : Std.Usize) (step i0 tot0 ctl0 zero0 dig0)
    (hn : n.val = s.length) :
    slot.tf_class_loop s n step i0 tot0 ctl0 zero0 dig0 ⦃ fun _ => True ⦄ := by
  rw [slot.tf_class_loop]
  apply Std.loop.spec_decr_nat (measure := fun (_, tot, _, _, _) => 65536 - tot.val) (inv := fun _ => True)
  · rintro ⟨i, tot, ctl, zero, dig⟩ _
    simp only [slot.tf_class_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial

@[local step] theorem tf_class_spec (s) : slot.tf_class s ⦃ fun _ => True ⦄ := by
  rw [slot.tf_class]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

@[local step] theorem tf_cfg_spec (cls) : slot.tf_cfg cls ⦃ fun _ => True ⦄ := by
  rw [slot.tf_cfg]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

@[local step] theorem tf_run4_spec (s p) : slot.tf_run4 s p ⦃ fun _ => True ⦄ := by
  rw [slot.tf_run4]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

@[local step] theorem tf_first_cand_spec (s prev p ci rep minl depth rle) :
    slot.tf_first_cand s prev p ci rep minl depth rle ⦃ fun _ => True ⦄ := by
  rw [slot.tf_first_cand]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

@[local step] theorem tf_take_spec (l minl n p) : slot.tf_take l minl n p ⦃ fun _ => True ⦄ := by
  rw [slot.tf_take]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

@[local step] theorem tf_gain_spec (l d) : slot.tf_gain l d ⦃ fun _ => True ⦄ := by
  rw [slot.tf_gain]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

@[local step] theorem tf_better_spec (g0 g1 l d n q) : slot.tf_better g0 g1 l d n q ⦃ fun _ => True ⦄ := by
  rw [slot.tf_better]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

@[local step] theorem tf_lazy_loop_spec (s n lim rep mask minl depth lazy rle head0 prev0 p0 l0 d0 run0 ins0 go0) :
    slot.tf_lazy_loop s head0 prev0 n lim rep mask minl depth lazy rle p0 l0 d0 run0 ins0 go0
      ⦃ fun _ => True ⦄ := by
  rw [slot.tf_lazy_loop]
  apply Std.loop.spec_decr_nat (measure := fun (_, _, p, _, _, _, _, go) => lim.val - p.val + go.val)
    (inv := fun _ => True)
  · rintro ⟨head, prev, p, l, d, run, ins, go⟩ _
    simp only [slot.tf_lazy_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial

@[local step] theorem tf_lazy_spec (s head prev n lim rep mask minl depth lazy rle m) :
    slot.tf_lazy s head prev n lim rep mask minl depth lazy rle m ⦃ fun _ => True ⦄ := by
  rw [slot.tf_lazy]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

@[local step] theorem tf_back_loop_spec (s d p0 l0 run0) : slot.tf_back_loop s d p0 l0 run0 ⦃ fun _ => True ⦄ := by
  rw [slot.tf_back_loop]
  apply Std.loop.spec_decr_nat (measure := fun (_, _, run) => run.val) (inv := fun _ => True)
  · rintro ⟨p, l, run⟩ _
    simp only [slot.tf_back_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial

@[local step] theorem tf_back_spec (s p l d run) : slot.tf_back s p l d run ⦃ fun _ => True ⦄ := by
  rw [slot.tf_back]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

@[local step] theorem tf_fold_spec (s p l d run pl pd) : slot.tf_fold s p l d run pl pd ⦃ fun _ => True ⦄ := by
  rw [slot.tf_fold]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

@[local step] theorem tf_flush_spec (tk hist pl pd) : slot.tf_flush tk hist pl pd ⦃ fun _ => True ⦄ := by
  rw [slot.tf_flush]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

@[local step] theorem tf_tailfrom_spec (ins e) : slot.tf_tailfrom ins e ⦃ fun _ => True ⦄ := by
  rw [slot.tf_tailfrom]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

@[local step] theorem tf_ins_match_spec (s head prev ins e lim mask) :
    slot.tf_ins_match s head prev ins e lim mask ⦃ fun _ => True ⦄ := by
  rw [slot.tf_ins_match]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

@[local step] theorem tf_s1_match_spec (s tk head prev hist n lim p l d run pl pd ins rep mask minl depth lazy rle o) :
    slot.tf_s1_match s tk head prev hist n lim p l d run pl pd ins rep mask minl depth lazy rle o
      ⦃ fun _ => True ⦄ := by
  rw [slot.tf_s1_match]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

@[local step] theorem tf_skipn_spec (p lim miss skip) : slot.tf_skipn p lim miss skip ⦃ fun _ => True ⦄ := by
  rw [slot.tf_skipn]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

@[local step] theorem tf_rest_spec (n p run) : slot.tf_rest n p run ⦃ fun _ => True ⦄ := by
  rw [slot.tf_rest]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

@[local step] theorem tf_s1_loop_loop_spec (s tk0 head0 prev0 hist0 n lim mask minl depth lazy skip rle
    p0 run0 pl0 pd0 ins0 miss0 rep0 fuel0) :
    slot.tf_s1_loop_loop s tk0 head0 prev0 hist0 n lim mask minl depth lazy skip rle p0 run0 pl0 pd0 ins0
      miss0 rep0 fuel0 ⦃ fun _ => True ⦄ := by
  rw [slot.tf_s1_loop_loop]
  apply Std.loop.spec_decr_nat (measure := fun (_, _, _, _, _, _, _, _, _, _, _, fuel) => fuel.val)
    (inv := fun _ => True)
  · rintro ⟨tk, head, prev, hist, p, run, pl, pd, ins, miss, rep, fuel⟩ _
    simp only [slot.tf_s1_loop_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial

@[local step] theorem tf_s1_loop_spec (s tk head prev hist n lim mask minl depth lazy skip rle) :
    slot.tf_s1_loop s tk head prev hist n lim mask minl depth lazy skip rle ⦃ fun _ => True ⦄ := by
  rw [slot.tf_s1_loop]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

@[local step] theorem tf_stage1_spec (s tk head prev hist cls) :
    slot.tf_stage1 s tk head prev hist cls ⦃ fun _ => True ⦄ := by
  rw [slot.tf_stage1]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

@[local step] theorem tf_thr_spec (c kl kd) : slot.tf_thr c kl kd ⦃ fun _ => True ⦄ := by
  rw [slot.tf_thr]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

@[local step] theorem tf_kept_spec (h k) : slot.tf_kept h k ⦃ fun _ => True ⦄ := by
  rw [slot.tf_kept]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

@[local step] theorem tf_keep_loop_spec (hist keep0 kl kd c0) :
    slot.tf_keep_loop hist keep0 kl kd c0 ⦃ fun _ => True ⦄ := by
  rw [slot.tf_keep_loop]
  apply Std.loop.spec_decr_nat (measure := fun (_, c) => 64 - c.val) (inv := fun _ => True)
  · rintro ⟨keep, c⟩ _
    simp only [slot.tf_keep_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial

@[local step] theorem tf_keep_spec (hist keep kl kd) : slot.tf_keep hist keep kl kd ⦃ fun _ => True ⦄ := by
  rw [slot.tf_keep]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

@[local step] theorem tf_first_spec (kmin x kx) : slot.tf_first kmin x kx ⦃ fun _ => True ⦄ := by
  rw [slot.tf_first]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

@[local step] theorem tf_kx_spec (keep x) : slot.tf_kx keep x ⦃ fun _ => True ⦄ := by
  rw [slot.tf_kx]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

@[local step] theorem tf_cur_spec (cur x kx) : slot.tf_cur cur x kx ⦃ fun _ => True ⦄ := by
  rw [slot.tf_cur]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

@[local step] theorem tf_lle_loop_spec (keep lle0 x0 cur0 kmin0) :
    slot.tf_lle_loop keep lle0 x0 cur0 kmin0 ⦃ fun _ => True ⦄ := by
  rw [slot.tf_lle_loop]
  apply Std.loop.spec_decr_nat (measure := fun (_, x, _, _) => 259 - x.val) (inv := fun _ => True)
  · rintro ⟨lle, x, cur, kmin⟩ _
    simp only [slot.tf_lle_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial

@[local step] theorem tf_lle_spec (keep lle) : slot.tf_lle keep lle ⦃ fun _ => True ⦄ := by
  rw [slot.tf_lle]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

@[local step] theorem tf_pair1_spec (x c keep lle) : slot.tf_pair1 x c keep lle ⦃ fun _ => True ⦄ := by
  rw [slot.tf_pair1]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

@[local step] theorem tf_pair_loop_spec (x keep lle c0 a0) :
    slot.tf_pair_loop x keep lle c0 a0 ⦃ fun _ => True ⦄ := by
  rw [slot.tf_pair_loop]
  apply Std.loop.spec_decr_nat (measure := fun (c, _) => c.val) (inv := fun _ => True)
  · rintro ⟨c, a⟩ _
    simp only [slot.tf_pair_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial

@[local step] theorem tf_pair_spec (x keep lle) : slot.tf_pair x keep lle ⦃ fun _ => True ⦄ := by
  rw [slot.tf_pair]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

@[local step] theorem tf_lastpiece_spec (rem lle kmin) : slot.tf_lastpiece rem lle kmin ⦃ fun _ => True ⦄ := by
  rw [slot.tf_lastpiece]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

@[local step] theorem tf_piece0_spec (rem keep lle kmin) : slot.tf_piece0 rem keep lle kmin ⦃ fun _ => True ⦄ := by
  rw [slot.tf_piece0]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

@[local step] theorem tf_piece_spec (rem : Std.Usize) (keep lle kmin) :
    slot.tf_piece rem keep lle kmin ⦃ fun r => r.val ≤ rem.val ⦄ := by
  rw [slot.tf_piece]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

@[local step] theorem tf_left_loop_spec (keep lle kmin rem0 fuel0) :
    slot.tf_left_loop keep lle kmin rem0 fuel0 ⦃ fun _ => True ⦄ := by
  rw [slot.tf_left_loop]
  apply Std.loop.spec_decr_nat (measure := fun (_, fuel) => fuel.val) (inv := fun _ => True)
  · rintro ⟨rem, fuel⟩ _
    simp only [slot.tf_left_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial

@[local step] theorem tf_left_spec (l keep lle kmin) : slot.tf_left l keep lle kmin ⦃ fun _ => True ⦄ := by
  rw [slot.tf_left]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

@[local step] theorem tf_split_loop_spec (plan0 d keep lle kmin r0 rem0 fuel0) :
    slot.tf_split_loop plan0 d keep lle kmin r0 rem0 fuel0 ⦃ fun _ => True ⦄ := by
  rw [slot.tf_split_loop]
  apply Std.loop.spec_decr_nat (measure := fun (_, _, _, fuel) => fuel.val) (inv := fun _ => True)
  · rintro ⟨plan, r, rem, fuel⟩ _
    simp only [slot.tf_split_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial

@[local step] theorem tf_split_spec (plan run l d keep lle kmin) :
    slot.tf_split plan run l d keep lle kmin ⦃ fun _ => True ⦄ := by
  rw [slot.tf_split]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

@[local step] theorem tf_admit1_spec (keep r) : slot.tf_admit1 keep r ⦃ fun _ => True ⦄ := by
  rw [slot.tf_admit1]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

@[local step] theorem tf_admit_loop_spec (keep0 r0) : slot.tf_admit_loop keep0 r0 ⦃ fun _ => True ⦄ := by
  rw [slot.tf_admit_loop]
  apply Std.loop.spec_decr_nat (measure := fun (_, r) => r.val) (inv := fun _ => True)
  · rintro ⟨keep, r⟩ _
    simp only [slot.tf_admit_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial

@[local step] theorem tf_admit_spec (l keep lle) : slot.tf_admit l keep lle ⦃ fun _ => True ⦄ := by
  rw [slot.tf_admit]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

@[local step] theorem tf_split_st_spec (plan st l d keep lle) :
    slot.tf_split_st plan st l d keep lle ⦃ fun _ => True ⦄ := by
  rw [slot.tf_split_st]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

@[local step] theorem tf_fit_st_spec (l keep lle st) : slot.tf_fit_st l keep lle st ⦃ fun _ => True ⦄ := by
  rw [slot.tf_fit_st]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

@[local step] theorem tf_rcand_spec (s keep p d cap best bd) :
    slot.tf_rcand s keep p d cap best bd ⦃ fun _ => True ⦄ := by
  rw [slot.tf_rcand]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

@[local step] theorem tf_rtry_spec (s keep c p cap best bd) :
    slot.tf_rtry s keep c p cap best bd ⦃ fun _ => True ⦄ := by
  rw [slot.tf_rtry]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

@[local step] theorem tf_rwalk_loop_spec (s prev keep p cap best0 bd0 c0 k0) :
    slot.tf_rwalk_loop s prev keep p cap best0 bd0 c0 k0 ⦃ fun _ => True ⦄ := by
  rw [slot.tf_rwalk_loop]
  apply Std.loop.spec_decr_nat (measure := fun (_, _, _, k) => k.val) (inv := fun _ => True)
  · rintro ⟨best, bd, c, k⟩ _
    simp only [slot.tf_rwalk_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial

@[local step] theorem tf_rwalk_spec (s prev keep p cap best bd) :
    slot.tf_rwalk s prev keep p cap best bd ⦃ fun _ => True ⦄ := by
  rw [slot.tf_rwalk]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

@[local step] theorem tf_rchain_spec (s prev keep p chain cap best bd) :
    slot.tf_rchain s prev keep p chain cap best bd ⦃ fun _ => True ⦄ := by
  rw [slot.tf_rchain]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

@[local step] theorem tf_refind_spec (s prev keep p chain cap r1 r2) :
    slot.tf_refind s prev keep p chain cap r1 r2 ⦃ fun _ => True ⦄ := by
  rw [slot.tf_refind]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

@[local step] theorem tf_note_spec (rd d) : slot.tf_note rd d ⦃ fun _ => True ⦄ := by
  rw [slot.tf_note]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

@[local step] theorem tf_span_spec (plan st l d keep lle) : slot.tf_span plan st l d keep lle ⦃ fun _ => True ⦄ := by
  rw [slot.tf_span]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

/-- What `tf_redo` relies on: "take it" (0) only for a re-find of 3..rem bytes, "one literal" (1)
    only while literal tries are left. -/
@[local step] theorem tf_act_spec (fl rem shift : Std.Usize) :
    slot.tf_act fl rem shift ⦃ fun r => (r.val = 0 → 3 ≤ fl.val ∧ fl.val ≤ rem.val) ∧
      (r.val = 1 → 0 < shift.val) ⦄ := by
  rw [slot.tf_act]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

@[local step] theorem tf_step_spec (plan st rd keep lle act fl fd rem d) :
    slot.tf_step plan st rd keep lle act fl fd rem d ⦃ fun _ => True ⦄ := by
  rw [slot.tf_step]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

@[local step] theorem tf_redo_loop_spec (s prev d keep0 lle0 plan0 st0 rd0 q0 rem0 chain0 shift0) :
    slot.tf_redo_loop s prev keep0 lle0 plan0 st0 rd0 d q0 rem0 chain0 shift0 ⦃ fun _ => True ⦄ := by
  rw [slot.tf_redo_loop]
  apply Std.loop.spec_decr_nat (measure := fun (_, _, _, _, _, _, rem, _, _) => rem.val) (inv := fun _ => True)
  · rintro ⟨keep, lle, plan, st, rd, q, rem, chain, shift⟩ _
    simp only [slot.tf_redo_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial

@[local step] theorem tf_redo_spec (s prev keep lle plan st rd p l d) :
    slot.tf_redo s prev keep lle plan st rd p l d ⦃ fun _ => True ⦄ := by
  rw [slot.tf_redo]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

@[local step] theorem tf_tkind_spec (l d room keep) : slot.tf_tkind l d room keep ⦃ fun _ => True ⦄ := by
  rw [slot.tf_tkind]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

@[local step] theorem tf_litstep_spec (l room) : slot.tf_litstep l room ⦃ fun _ => True ⦄ := by
  rw [slot.tf_litstep]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

/-- The span never moves backwards (the rewrite's measure needs it). -/
@[local step] theorem tf_extend_loop_spec (tk : Slice Std.U32) (d room : Std.Usize) (k0 l0 : Std.Usize) :
    slot.tf_extend_loop tk d room k0 l0 ⦃ fun r => k0.val ≤ r.1.val ⦄ := by
  rw [slot.tf_extend_loop]
  apply Std.loop.spec_decr_nat (measure := fun (k, _) => tk.length - k.val)
    (inv := fun (k, _) => k0.val ≤ k.val)
  · rintro ⟨k, l⟩ hk
    simp only [slot.tf_extend_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · simp

@[local step] theorem tf_extend_spec (tk : Slice Std.U32) (k0 d room l0 : Std.Usize) :
    slot.tf_extend tk k0 d room l0 ⦃ fun r => k0.val ≤ r.1.val ⦄ := by
  rw [slot.tf_extend]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

@[local step] theorem tf_rewrite_loop_spec (s : Slice Std.U8) (tk : Slice Std.U32) (prev n keep0 lle0 plan0 st0
    p0 rd0 k0) :
    slot.tf_rewrite_loop s tk prev keep0 lle0 plan0 n st0 p0 rd0 k0 ⦃ fun _ => True ⦄ := by
  rw [slot.tf_rewrite_loop]
  apply Std.loop.spec_decr_nat (measure := fun (_, _, _, _, _, _, k) => tk.length - k.val) (inv := fun _ => True)
  · rintro ⟨keep, lle, plan, st, p, rd, k⟩ _
    simp only [slot.tf_rewrite_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals scalar_tac
  · trivial

@[local step] theorem tf_rewrite_spec (s tk prev keep lle kmin plan) :
    slot.tf_rewrite s tk prev keep lle kmin plan ⦃ fun _ => True ⦄ := by
  rw [slot.tf_rewrite]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

@[local step] theorem tf_thrs_spec (cls) : slot.tf_thrs cls ⦃ fun _ => True ⦄ := by
  rw [slot.tf_thrs]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

/-- The planner is total; its plan may be anything (the emission re-verifies it). -/
theorem tf_plan_spec (input : Slice Std.U8) (cls : Std.Usize) : slot.tf_plan input cls ⦃ fun _ => True ⦄ := by
  rw [slot.tf_plan]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

/-- The route is total (any value is fine for `parse`). -/
theorem tf_route_spec (input : Slice Std.U8) : slot.tf_route input ⦃ fun _ => True ⦄ := by
  rw [slot.tf_route]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

end TinyPath

/-! ## 1. Words: `be8` is the big-endian number of the eight bytes at `i`

`word8` is the arithmetic form; `be8_spec` proves the extracted shift/or chain equals it
(`or_eq_add_of_mod`: or-ing a byte into the zero low bits of a number is addition).
`word8_digit`/`word8_prefix`: two words that agree above bit `64 - 8d` start with `d` equal
bytes. `word8` is `@[irreducible]`: unfold it only with `simp only [word8]` (otherwise
`by assumption` tries to unfold it while unifying and hits the recursion limit). -/

@[irreducible] def word8 (input : Slice Std.U8) (p : Nat) : Nat :=
  (input.val[p]!).val * 2^56 + (input.val[p + 1]!).val * 2^48 + (input.val[p + 2]!).val * 2^40
    + (input.val[p + 3]!).val * 2^32 + (input.val[p + 4]!).val * 2^24
    + (input.val[p + 5]!).val * 2^16 + (input.val[p + 6]!).val * 2^8 + (input.val[p + 7]!).val

theorem u8_lt (x : Std.U8) : x.val < 256 := by scalar_tac

theorem word8_digit (input : Slice Std.U8) (p k : Nat) (hk : k < 8) :
    (input.val[p + k]!).val = word8 input p / 256 ^ (7 - k) % 256 := by
  have := u8_lt (input.val[p]!); have := u8_lt (input.val[p+1]!)
  have := u8_lt (input.val[p+2]!); have := u8_lt (input.val[p+3]!)
  have := u8_lt (input.val[p+4]!); have := u8_lt (input.val[p+5]!)
  have := u8_lt (input.val[p+6]!); have := u8_lt (input.val[p+7]!)
  simp only [word8]
  rcases (show k = 0 ∨ k = 1 ∨ k = 2 ∨ k = 3 ∨ k = 4 ∨ k = 5 ∨ k = 6 ∨ k = 7 by omega) with
    rfl | rfl | rfl | rfl | rfl | rfl | rfl | rfl <;> simp only [Nat.add_zero, Nat.pow_zero, Nat.pow_succ, Nat.one_mul,
    Nat.sub_self, Nat.reduceSub] <;> omega

theorem word8_prefix (input : Slice Std.U8) (a b d : Nat) (hd : d ≤ 8)
    (h : word8 input a / 2 ^ (64 - 8 * d) = word8 input b / 2 ^ (64 - 8 * d)) :
    ∀ k, k < d → input.val[b + k]! = input.val[a + k]! := by
  intro k hk
  have e : (256 : Nat) ^ (7 - k) = 2 ^ (64 - 8 * d) * 2 ^ (8 * (d - 1 - k)) := by
    rw [← pow_add, show (256 : Nat) = 2 ^ 8 by norm_num, ← pow_mul]
    congr 1; omega
  have key : word8 input a / 256 ^ (7 - k) = word8 input b / 256 ^ (7 - k) := by
    rw [e, ← Nat.div_div_eq_div_mul, ← Nat.div_div_eq_div_mul, h]
  have ha := word8_digit input a k (by omega)
  have hb := word8_digit input b k (by omega)
  rw [key] at ha
  scalar_tac

theorem Matches.add_prefix {input : Slice Std.U8} {a b l d : Nat} (h : Matches input a b l)
    (hd : d ≤ 8)
    (hw : word8 input (a + l) / 2 ^ (64 - 8 * d) = word8 input (b + l) / 2 ^ (64 - 8 * d)) :
    Matches input a b (l + d) := by
  intro k hk
  by_cases hkl : k < l
  · exact h k hkl
  · have := word8_prefix input (a + l) (b + l) d hd hw (k - l) (by omega)
    rw [show b + l + (k - l) = b + k by omega, show a + l + (k - l) = a + k by omega] at this
    exact this

theorem or_eq_add_of_mod {x t : Nat} (m : Nat) (hx : x % 2 ^ m = 0) (ht : t < 2 ^ m) :
    x ||| t = x + t := by
  have h := Nat.two_pow_add_eq_or_of_lt ht (x / 2 ^ m)
  have hx' : 2 ^ m * (x / 2 ^ m) = x := by
    have := Nat.div_add_mod x (2 ^ m); omega
  rw [hx'] at h
  exact h.symm

theorem shl_byte {x : Nat} (k : Nat) (hx : x < 256) (hk : k ≤ 56) :
    x <<< k % U64.size = x * 2 ^ k := by
  rw [Nat.shiftLeft_eq, U64.size_def]
  apply Nat.mod_eq_of_lt
  have : 2 ^ k ≤ 2 ^ 56 := Nat.pow_le_pow_right (by norm_num) hk
  have : x * 2 ^ k < 256 * 2 ^ 56 := by
    calc x * 2 ^ k < 256 * 2 ^ k := by
          apply Nat.mul_lt_mul_of_pos_right hx (Nat.two_pow_pos _)
      _ ≤ 256 * 2 ^ 56 := Nat.mul_le_mul_left _ this
  simp only [U64.numBits] at *
  omega

theorem be8_nat {a b c d e f g h : Nat} (ha : a < 256) (hb : b < 256) (hc : c < 256)
    (hd : d < 256) (he : e < 256) (hf : f < 256) (hg : g < 256) (hh : h < 256) :
    (a <<< 56 % U64.size ||| b <<< 48 % U64.size ||| c <<< 40 % U64.size |||
      d <<< 32 % U64.size ||| e <<< 24 % U64.size ||| f <<< 16 % U64.size |||
      g <<< 8 % U64.size ||| h) =
    a * 2^56 + b * 2^48 + c * 2^40 + d * 2^32 + e * 2^24 + f * 2^16 + g * 2^8 + h := by
  rw [shl_byte 56 ha (by norm_num), shl_byte 48 hb (by norm_num), shl_byte 40 hc (by norm_num),
    shl_byte 32 hd (by norm_num), shl_byte 24 he (by norm_num), shl_byte 16 hf (by norm_num),
    shl_byte 8 hg (by norm_num)]
  rw [or_eq_add_of_mod 56 (x := a * 2^56) (t := b * 2^48) (by omega) (by omega)]
  rw [or_eq_add_of_mod 48 (x := a * 2^56 + b * 2^48) (t := c * 2^40) (by omega) (by omega)]
  rw [or_eq_add_of_mod 40 (x := a * 2^56 + b * 2^48 + c * 2^40) (t := d * 2^32) (by omega)
    (by omega)]
  rw [or_eq_add_of_mod 32 (x := a * 2^56 + b * 2^48 + c * 2^40 + d * 2^32) (t := e * 2^24)
    (by omega) (by omega)]
  rw [or_eq_add_of_mod 24 (x := a * 2^56 + b * 2^48 + c * 2^40 + d * 2^32 + e * 2^24)
    (t := f * 2^16) (by omega) (by omega)]
  rw [or_eq_add_of_mod 16
    (x := a * 2^56 + b * 2^48 + c * 2^40 + d * 2^32 + e * 2^24 + f * 2^16)
    (t := g * 2^8) (by omega) (by omega)]
  rw [or_eq_add_of_mod 8
    (x := a * 2^56 + b * 2^48 + c * 2^40 + d * 2^32 + e * 2^24 + f * 2^16 + g * 2^8)
    (t := h) (by omega) (by omega)]

@[local step]
theorem be8_spec (s : Slice Std.U8) (i : Std.Usize) (h : i.val + 8 ≤ s.length) :
    slot.be8 s i ⦃ fun v => v.val = word8 s i.val ⦄ := by
  rw [slot.be8]
  step*
  simp only [← getElem!_pos] at *
  simp_all only [UScalar.val_or, U8.cast_U64_val_eq]
  rw [be8_nat (u8_lt _) (u8_lt _) (u8_lt _) (u8_lt _) (u8_lt _) (u8_lt _) (u8_lt _) (u8_lt _)]
  simp only [word8]

/-! ## 2. `common`: the length of an actual match, at most `cap`

The word loop compares eight bytes at a time; the first mismatching word adds
`leading_zeros(x ^ y) / 8` bytes and stops the loop (`run = 0`); the byte loop finishes.
Both loops keep `k ≤ cap ∧ Matches s a b k`; the measure is `cap - k + run`. -/

theorem nat_xor_eq_zero {a b : Nat} (h : a ^^^ b = 0) : a = b := by
  have : a ^^^ (a ^^^ b) = b := by rw [← Nat.xor_assoc, Nat.xor_self, Nat.zero_xor]
  rw [h, Nat.xor_zero] at this; exact this

theorem div_eq_of_xor_lt {x y m : Nat} (hz : x ^^^ y < 2 ^ m) : x / 2 ^ m = y / 2 ^ m := by
  have h : (x ^^^ y) >>> m = 0 := by rw [Nat.shiftRight_eq_div_pow]; exact Nat.div_eq_of_lt hz
  rw [Nat.shiftRight_xor_distrib] at h
  have := nat_xor_eq_zero h
  simpa [Nat.shiftRight_eq_div_pow] using this

theorem lt_pow_leadingZeros (z : BitVec 64) :
    z.toNat < 2 ^ (64 - 8 * (BitVec.leadingZeros z / 8)) := by
  unfold BitVec.leadingZeros
  split
  case isTrue h => subst h; simp
  case isFalse h =>
    have hz : z.toNat ≠ 0 := by
      intro h0; apply h; exact BitVec.eq_of_toNat_eq (by simpa using h0)
    have hlog : Nat.log 2 z.toNat < 64 := Nat.log_lt_of_lt_pow hz z.isLt
    have h1 : z.toNat < 2 ^ (Nat.log 2 z.toNat).succ := Nat.lt_pow_succ_log_self (by norm_num) _
    refine lt_of_lt_of_le h1 (Nat.pow_le_pow_right (by norm_num) ?_)
    omega

/-- A non-zero 64-bit value has fewer than 64 leading zeros. -/
theorem leadingZeros_lt_of_ne (z : BitVec 64) (h : z ≠ 0) : BitVec.leadingZeros z < 64 := by
  unfold BitVec.leadingZeros
  simp only [h, if_false]
  omega

/-- `leading_zeros` of a `u64`, as a number. -/
@[local step]
theorem lz_spec (x : Std.U64) :
    lift (core.num.U64.leading_zeros x) ⦃ fun r => r = core.num.U64.leading_zeros x ∧ r.val ≤ 64 ⦄ := by
  simp only [lift, Std.WP.spec_ok, true_and]
  have hle : BitVec.leadingZeros x.bv ≤ 64 := by unfold BitVec.leadingZeros; split <;> omega
  simp only [core.num.U64.leading_zeros, UScalar.val, UScalarTy.U32_numBits_eq,
    BitVec.natCast_eq_ofNat, BitVec.toNat_ofNat, Nat.reducePow]
  omega

/-- `leading_zeros` of a `u64`, as a number. -/
theorem lz_val (x : Std.U64) :
    (core.num.U64.leading_zeros x).val = BitVec.leadingZeros x.bv := by
  have hle : BitVec.leadingZeros x.bv ≤ 64 := by unfold BitVec.leadingZeros; split <;> omega
  simp only [core.num.U64.leading_zeros, UScalar.val, UScalarTy.U32_numBits_eq,
    BitVec.natCast_eq_ofNat, BitVec.toNat_ofNat, Nat.reducePow]
  omega

/-- The mismatching word of `common`: `leading_zeros(x ^ y) / 8` more bytes agree, fewer than 8. -/
theorem Matches.word_lz {input : Slice Std.U8} {a b k : Nat} {pa pb r k1 : Std.Usize}
    {x y z : Std.U64} {lz q : Std.U32}
    (h : Matches input a b k) (hpa : pa.val = a + k) (hpb : pb.val = b + k)
    (hx : x.val = word8 input pa.val) (hy : y.val = word8 input pb.val)
    (hz : z.val = (x ^^^ y).val) (hz0 : ¬z = 0#u64) (hlz : lz = core.num.U64.leading_zeros z)
    (hq : q.val = lz.val / 8) (hr : r = UScalar.cast .Usize q) (hk1 : k1.val = k + r.val) :
    Matches input a b k1.val ∧ k1.val < k + 8 := by
  have hbv : z.bv ≠ 0 := by
    intro h0; apply hz0; exact UScalar.eq_of_val_eq (by simp [UScalar.val, h0])
  have hlt : BitVec.leadingZeros z.bv < 64 := leadingZeros_lt_of_ne z.bv hbv
  have hrv : r.val = BitVec.leadingZeros z.bv / 8 := by
    rw [hr, U32.cast_Usize_val_eq, hq, hlz, lz_val]
  rw [hpa] at hx; rw [hpb] at hy
  refine ⟨?_, by omega⟩
  rw [hk1, hrv]
  have hle : BitVec.leadingZeros z.bv ≤ 64 := by unfold BitVec.leadingZeros; split <;> omega
  apply Matches.add_prefix h (by omega)
  rw [← hx, ← hy]
  apply div_eq_of_xor_lt
  rw [← UScalar.val_xor, ← hz]
  exact lt_pow_leadingZeros z.bv

/-- The equal words of `common`: eight more bytes agree. -/
theorem Matches.word_zero {input : Slice Std.U8} {a b k : Nat} {pa pb k1 : Std.Usize}
    {x y z : Std.U64}
    (h : Matches input a b k) (hpa : pa.val = a + k) (hpb : pb.val = b + k)
    (hx : x.val = word8 input pa.val) (hy : y.val = word8 input pb.val)
    (hz : z.val = (x ^^^ y).val) (hz0 : z = 0#u64) (hk1 : k1.val = k + 8) :
    Matches input a b k1.val := by
  have hxy : x.val = y.val := by
    apply nat_xor_eq_zero
    rw [← UScalar.val_xor, ← hz, hz0]; rfl
  rw [hpa] at hx; rw [hpb] at hy
  rw [hk1]
  apply Matches.add_prefix h (le_refl 8)
  rw [← hx, ← hy, hxy]

/-- One more equal byte, in the shape an extracted byte-compare loop leaves. -/
theorem Matches.byte' {input : Slice Std.U8} {a b l : Nat} {pa pb l1 : Std.Usize}
    {x y : Std.U8} (h : Matches input a b l) (hpa : pa.val = a + l) (hpb : pb.val = b + l)
    (hpa' : pa.val < input.val.length) (hpb' : pb.val < input.val.length)
    (hx : x = input.val[pa.val]) (hy : y = input.val[pb.val]) (hxy : x = y)
    (hl1 : l1.val = l + 1) : Matches input a b l1.val := by
  rw [hl1]
  apply LZ77.Matches.succ h
  rw [← hpa, ← hpb, getElem!_pos input.val pa.val hpa', getElem!_pos input.val pb.val hpb',
    ← hx, ← hy, hxy]

theorem common_loop0_spec (s : Slice Std.U8) (a b cap k : Std.Usize) (run : Std.U32)
    (ha : a.val + cap.val ≤ s.length) (hb : b.val + cap.val ≤ s.length) (hcap : cap.val ≤ 258)
    (hk : k.val ≤ cap.val) (hm : Matches s a.val b.val k.val) :
    slot.common_loop0 s a b cap k run ⦃ fun r =>
      r.1.val ≤ cap.val ∧ Matches s a.val b.val r.1.val ⦄ := by
  rw [slot.common_loop0]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  apply Std.loop.spec_decr_nat
    (measure := fun r => cap.val - r.1.val + r.2.val)
    (inv := fun r => r.1.val ≤ cap.val ∧ Matches s a.val b.val r.1.val)
  · rintro ⟨k, run⟩ ⟨hk, hm⟩
    simp only at hk hm
    simp only [slot.common_loop0.body]
    step*
    all_goals first
      | scalar_tac
      | (refine ⟨by scalar_tac, Matches.word_zero hm (by assumption) (by assumption)
          (by assumption) (by assumption) (by assumption) (by assumption) (by scalar_tac),
          by scalar_tac⟩)
      | (have hw := Matches.word_lz hm (by assumption) (by assumption) (by assumption)
          (by assumption) (by assumption) (by assumption) (by assumption) (by assumption)
          (by assumption) (by assumption)
         refine ⟨by scalar_tac, hw.1, by scalar_tac⟩)
  · exact ⟨hk, hm⟩

theorem common_loop1_spec (s : Slice Std.U8) (a b cap k : Std.Usize) (run : Std.U32)
    (ha : a.val + cap.val ≤ s.length) (hb : b.val + cap.val ≤ s.length)
    (hk : k.val ≤ cap.val) (hm : Matches s a.val b.val k.val) :
    slot.common_loop1 s a b cap k run ⦃ fun r =>
      r.val ≤ cap.val ∧ Matches s a.val b.val r.val ⦄ := by
  rw [slot.common_loop1]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  apply Std.loop.spec_decr_nat
    (measure := fun r => cap.val - r.1.val + r.2.val)
    (inv := fun r => r.1.val ≤ cap.val ∧ Matches s a.val b.val r.1.val)
  · rintro ⟨k, run⟩ ⟨hk, hm⟩
    simp only at hk hm
    simp only [slot.common_loop1.body]
    step*
    all_goals first
      | scalar_tac
      | exact ⟨hk, hm⟩
      | (refine ⟨by scalar_tac, Matches.byte' hm (by assumption) (by assumption) (by scalar_tac)
          (by scalar_tac) (by assumption) (by assumption) (by assumption) (by assumption),
          by scalar_tac⟩)
  · exact ⟨hk, hm⟩

/-- `common` is the length of an actual match, at most `cap`. -/
@[local step]
theorem common_spec (s : Slice Std.U8) (a b cap : Std.Usize)
    (ha : a.val + cap.val ≤ s.length) (hb : b.val + cap.val ≤ s.length) (hcap : cap.val ≤ 258) :
    slot.common s a b cap ⦃ fun l => l.val ≤ cap.val ∧ Matches s a.val b.val l.val ⦄ := by
  rw [slot.common]
  apply Std.WP.spec_bind (common_loop0_spec s a b cap 0#usize 1#u32 ha hb hcap (by simp)
    (LZ77.Matches.zero s a.val b.val))
  rintro ⟨k, run⟩ ⟨hk, hm⟩
  exact common_loop1_spec s a b cap k run ha hb hk hm

/-! ## 3. `same`: returns 1 only for an actual match of `len` bytes

Used by the backward merge to check a whole earlier match at the new distance (and by
`put_match` when `VERIFY = 1`). Postcondition `r = 1 → Matches s a b len`. -/

theorem Matches.mono_eq {input : Slice Std.U8} {a b n m : Nat} (h : Matches input a b n)
    (hm : m = n) : Matches input a b m := by subst hm; exact h

/-- Equal words (compared with `==`): eight more bytes agree. -/
theorem Matches.word_eq {input : Slice Std.U8} {a b k : Nat} {pa pb k1 : Std.Usize}
    {x y : Std.U64}
    (h : Matches input a b k) (hpa : pa.val = a + k) (hpb : pb.val = b + k)
    (hx : x.val = word8 input pa.val) (hy : y.val = word8 input pb.val)
    (hxy : x = y) (hk1 : k1.val = k + 8) :
    Matches input a b k1.val := by
  rw [hpa] at hx; rw [hpb] at hy
  rw [hk1]
  apply Matches.add_prefix h (le_refl 8)
  rw [← hx, ← hy, hxy]

theorem same_loop0_spec (s : Slice Std.U8) (a b len k ok : Std.Usize)
    (ha : a.val + len.val ≤ s.length) (hb : b.val + len.val ≤ s.length) (hlen : len.val ≤ 258)
    (hk : k.val ≤ len.val) (hm : Matches s a.val b.val k.val) :
    slot.same_loop0 s a b len k ok ⦃ fun r =>
      r.1.val ≤ len.val ∧ Matches s a.val b.val r.1.val ∧ (r.2.val = 1 → len.val < r.1.val + 8) ⦄ := by
  rw [slot.same_loop0]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  apply Std.loop.spec_decr_nat
    (measure := fun r => len.val - r.1.val + r.2.val)
    (inv := fun r => r.1.val ≤ len.val ∧ Matches s a.val b.val r.1.val)
  · rintro ⟨k, ok⟩ ⟨hk, hm⟩
    simp only at hk hm
    simp only [slot.same_loop0.body]
    step*
    all_goals first
      | scalar_tac
      | (refine ⟨by scalar_tac, Matches.word_eq hm (by assumption) (by assumption)
          (by assumption) (by assumption) (by assumption) (by scalar_tac), by scalar_tac⟩)
  · exact ⟨hk, hm⟩

@[local step]
theorem same_loop1_spec (s : Slice Std.U8) (a b len k ok : Std.Usize)
    (ha : a.val + len.val ≤ s.length) (hb : b.val + len.val ≤ s.length)
    (hk : k.val ≤ len.val) (hm : Matches s a.val b.val k.val) :
    slot.same_loop1 s a b len k ok ⦃ fun r => r.val = 1 → Matches s a.val b.val len.val ⦄ := by
  rw [slot.same_loop1]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  apply Std.loop.spec_decr_nat
    (measure := fun r => len.val - r.1.val + r.2.val)
    (inv := fun r => r.1.val ≤ len.val ∧ Matches s a.val b.val r.1.val)
  · rintro ⟨k, ok⟩ ⟨hk, hm⟩
    simp only at hk hm
    simp only [slot.same_loop1.body]
    step*
    all_goals first
      | scalar_tac
      | (refine ⟨by scalar_tac, Matches.byte' hm (by assumption) (by assumption) (by scalar_tac)
          (by scalar_tac) (by assumption) (by assumption) (by assumption) (by assumption),
          by scalar_tac⟩)
  · exact ⟨hk, hm⟩

@[local step]
theorem same_loop2_spec (s : Slice Std.U8) (a b len k ok : Std.Usize)
    (ha : a.val + len.val ≤ s.length) (hb : b.val + len.val ≤ s.length)
    (hk : k.val ≤ len.val) (hm : Matches s a.val b.val k.val) :
    slot.same_loop2 s a b len k ok ⦃ fun r => r.val = 1 → Matches s a.val b.val len.val ⦄ := by
  rw [slot.same_loop2]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  apply Std.loop.spec_decr_nat
    (measure := fun r => len.val - r.1.val + r.2.val)
    (inv := fun r => r.1.val ≤ len.val ∧ Matches s a.val b.val r.1.val)
  · rintro ⟨k, ok⟩ ⟨hk, hm⟩
    simp only at hk hm
    simp only [slot.same_loop2.body]
    step*
    all_goals first
      | scalar_tac
      | (refine ⟨by scalar_tac, Matches.byte' hm (by assumption) (by assumption) (by scalar_tac)
          (by scalar_tac) (by assumption) (by assumption) (by assumption) (by assumption),
          by scalar_tac⟩)
  · exact ⟨hk, hm⟩

/-- The masked last word of `same`: the top `len - k` bytes of the two words agree. -/
theorem Matches.mask {input : Slice Std.U8} {a b k len : Nat} {pa pb : Std.Usize}
    {x y z w : Std.U64} {sh : Std.U32}
    (h : Matches input a b k) (hpa : pa.val = a + k) (hpb : pb.val = b + k)
    (hx : x.val = word8 input pa.val) (hy : y.val = word8 input pb.val)
    (hz : z.val = (x ^^^ y).val) (hw : w.val = z.val >>> sh.val) (hw0 : ¬(w != 0#u64) = true)
    (hsh : sh.val = 64 - 8 * (len - k)) (hk : k < len) (hlen : len < k + 8) :
    Matches input a b len := by
  have hw0 : w.val = 0 := by simpa using hw0
  rw [hpa] at hx; rw [hpb] at hy
  have := Matches.add_prefix (d := len - k) h (by omega) (by
    rw [← hx, ← hy, ← hsh]
    have h0 : (x.val ^^^ y.val) >>> sh.val = 0 := by rw [← UScalar.val_xor, ← hz, ← hw, hw0]
    rw [Nat.shiftRight_xor_distrib] at h0
    have := nat_xor_eq_zero h0
    simpa [Nat.shiftRight_eq_div_pow] using this)
  rw [show k + (len - k) = len by omega] at this
  exact this

/-- `same` returns 1 only for an actual match of `len` bytes. -/
@[local step]
theorem same_spec (s : Slice Std.U8) (a b len : Std.Usize)
    (ha : a.val + len.val ≤ s.length) (hb : b.val + len.val ≤ s.length) (hlen : len.val ≤ 258)
    (ha8 : a.val + len.val + 7 ≤ Std.Usize.max) (hb8 : b.val + len.val + 7 ≤ Std.Usize.max) :
    slot.same s a b len ⦃ fun r => r.val = 1 → Matches s a.val b.val len.val ⦄ := by
  rw [slot.same]
  apply Std.WP.spec_bind (same_loop0_spec s a b len 0#usize 1#usize ha hb hlen (by simp)
    (LZ77.Matches.zero s a.val b.val))
  rintro ⟨k, ok⟩ ⟨hk, hm, hok⟩
  simp only at hk hm hok
  step*
  -- all paths but the masked last word are closed by `step*` (`ok ≠ 1`, or `k = len`)
  intro _
  exact Matches.mask hm (by assumption) (by assumption) (by assumption) (by assumption)
    (by assumption) (by assumption) (by assumption) (by scalar_tac) (by scalar_tac)
    (by scalar_tac)

/-! ## 4. `gain`: total for lengths `≤ 258` and distances `≤ 32768`

Only its termination and absence of overflow matter (postcondition `True`): the value only
steers the search. The `i32` arithmetic needs `HLIT ≤ 4000000` (from its `_val` lemma) and
`|GBASE| ≤ 1000000000` (`GBASE_bound`, read off the definition so that a negative `GBASE`,
which has no `_val` lemma, is covered too). -/

theorem lz32_le (x : Std.U32) (k : Nat) (hk : k < 32) (hx : 2 ^ k ≤ x.val) :
    (core.num.U32.leading_zeros x).val ≤ 31 - k := by
  have hne : x.bv ≠ 0 := by
    intro h0
    have : x.val = 0 := by simp [UScalar.val, h0]
    have : 0 < 2 ^ k := Nat.two_pow_pos k
    omega
  have hlog : k ≤ Nat.log 2 x.bv.toNat := by
    apply Nat.le_log_of_pow_le (by norm_num)
    have : x.val = x.bv.toNat := rfl
    omega
  have hle : BitVec.leadingZeros x.bv ≤ 32 := by unfold BitVec.leadingZeros; split <;> omega
  have hv : (core.num.U32.leading_zeros x).val = BitVec.leadingZeros x.bv := by
    simp only [core.num.U32.leading_zeros, UScalar.val, UScalarTy.U32_numBits_eq,
      BitVec.natCast_eq_ofNat, BitVec.toNat_ofNat, Nat.reducePow]
    omega
  rw [hv]
  unfold BitVec.leadingZeros
  simp only [hne, if_false]
  omega

@[local step]
theorem lz32_spec (x : Std.U32) :
    lift (core.num.U32.leading_zeros x) ⦃ fun r => r = core.num.U32.leading_zeros x ∧
      (4 ≤ x.val → r.val ≤ 29) ∧ (8 ≤ x.val → r.val ≤ 28) ⦄ := by
  simp only [lift, Std.WP.spec_ok, true_and]
  exact ⟨fun h => lz32_le x 2 (by norm_num) (by simpa using h),
    fun h => lz32_le x 3 (by norm_num) (by simpa using h)⟩

/-- A small unsigned value keeps its value when cast to `i32`. -/
@[local step]
theorem hcast_I32_spec {ty : UScalarTy} (x : UScalar ty) (h : x.val ≤ 2147483647) :
    lift (UScalar.hcast .I32 x) ⦃ fun y => y.val = x.val ⦄ :=
  UScalar.hcast_inBounds_spec .I32 x (by simp [I32.max_def, I32.numBits]; omega)

/-- `GBASE` read off its definition, whatever its sign: the verifier's `slot.X.val = n` lemmas
    exist only for non-negative literals, so a negative `GBASE` would otherwise be unknown. -/
theorem GBASE_bound : -1000000000 ≤ slot.GBASE.val ∧ slot.GBASE.val ≤ 1000000000 := by
  unfold slot.GBASE
  simp

@[local step]
theorem gain_spec (l d : Std.Usize) (hl : l.val ≤ 258) (hd : d.val ≤ 32768) :
    slot.gain l d ⦃ fun _ => True ⦄ := by
  rw [slot.gain]
  have ⟨hG0, hG1⟩ := GBASE_bound
  repeat' (split <;> step*)

/-! ## 5. The hash table: every head entry is a position already passed

`HeadBound head B`: all head entries are `≤ B`. This is the one data-structure fact the proof
needs: `walk` computes `c + best` for chain entries `c`, which overflows in the model (whose
`usize` may be 32 bits wide) unless the chain start is `≤ p`; the chain itself is strictly
decreasing (`nx < c` is checked), so `prev` needs no invariant at all.
`insert_spec` states its bound as `i < B + 1`, not `i ≤ B`: `step*` instantiates the ghost
`B` from the hypotheses, and any `x ≤ y` fact would otherwise be taken for it. -/

/-- Every head entry is at most `B` (a position already inserted, or 0). -/
def HeadBound {N : Std.Usize} (head : Array Std.U32 N) (B : Nat) : Prop :=
  ∀ j : Nat, j < head.val.length → (head.val[j]!).val ≤ B

theorem HeadBound.mono {N : Std.Usize} {head : Array Std.U32 N} {B B' : Nat}
    (h : HeadBound head B) (hB : B ≤ B') : HeadBound head B' := fun j hj => le_trans (h j hj) hB

theorem HeadBound.init (N : Std.Usize) : HeadBound (Std.Array.repeat N 0#u32) 0 := by
  intro j hj
  rw [Std.Array.repeat_val] at hj ⊢
  rw [List.getElem!_eq_getElem?_getD, List.getElem?_replicate_of_lt (by simpa using hj)]
  rfl

theorem HeadBound.set {N : Std.Usize} {head : Array Std.U32 N} {B : Nat} (h : HeadBound head B)
    (a : Std.Usize) (v : Std.U32) (hv : v.val ≤ B) : HeadBound (head.set a v) B := by
  intro j hj
  rw [Std.Array.set_val_eq] at hj ⊢
  rw [List.length_set] at hj
  by_cases hja : a.val = j
  · subst hja
    rw [List.getElem!_eq_getElem?_getD, List.getElem?_set_self hj]
    exact hv
  · rw [List.getElem!_eq_getElem?_getD, List.getElem?_set_ne hja, ← List.getElem!_eq_getElem?_getD]
    exact h j hj

/-- `head[a] = i as u32` with `i ≤ B` keeps the bound. -/
theorem HeadBound.update {N : Std.Usize} {head head1 : Array Std.U32 N} {B : Nat}
    {a i : Std.Usize} {v : Std.U32} (h : HeadBound head B) (hv : v = UScalar.cast .U32 i)
    (hi : i.val ≤ B) (h1 : head1 = head.set a v) : HeadBound head1 B := by
  subst h1
  apply HeadBound.set h a v
  rw [hv]
  have : (UScalar.cast .U32 i).val = i.val % 2 ^ 32 := by
    simp only [UScalar.cast_val_eq, UScalarTy.U32_numBits_eq]
  rw [this]
  exact le_trans (Nat.mod_le _ _) hi

theorem HeadBound.get {N : Std.Usize} {head : Array Std.U32 N} {B : Nat} (h : HeadBound head B)
    (a : Std.Usize) (x : Std.U32) (ha : a.val < head.val.length) (hx : x = head.val[a.val]) :
    x.val ≤ B := by
  have := h a.val ha
  rw [getElem!_pos head.val a.val ha, ← hx] at this
  exact this

theorem cast_usize_le {x : Std.U32} {y : Std.Usize} {B : Nat} (h : y = UScalar.cast .Usize x)
    (hx : x.val ≤ B) : y.val ≤ B := by
  rw [h, U32.cast_Usize_val_eq]; exact hx

@[local step]
theorem be4_spec (s : Slice Std.U8) (i : Std.Usize) (hi : i.val + 4 ≤ Std.Usize.max) :
    slot.be4 s i ⦃ fun _ => True ⦄ := by
  rw [slot.be4]
  step*

@[local step]
theorem insert_spec (s : Slice Std.U8) {H W : Std.Usize} (head : Array Std.U32 H)
    (prev : Array Std.U32 W) (i : Std.Usize) (mask : Std.U32) (B : Nat) (hB : HeadBound head B)
    (hi : i.val < B + 1) (hi4 : i.val + 4 ≤ Std.Usize.max) (hH : 0 < H.val) (hW : 0 < W.val) :
    slot.insert s head prev i mask ⦃ fun r => r.1.val ≤ B ∧ HeadBound r.2.1 B ⦄ := by
  rw [slot.insert]
  step*
  have hold : old.val ≤ B := HeadBound.get hB a old (by scalar_tac) (by assumption)
  exact ⟨cast_usize_le (by assumption) hold,
    HeadBound.update hB (by assumption) (by omega) (by assumption)⟩

/-! ## 6. The search: `walk` and `find` establish `FoundAt` (nothing about quality)

`Cand s p cap best bd`: nothing (`bd = 0`), or a real match of `best ≤ cap` bytes at distance
`bd`. The walk loop keeps `c ≤ p ∧ p + best ≤ n ∧ Cand`; `dist_of_wrapping` turns the
`p.wrapping_sub(c).wrapping_sub(1) < 32768` test into `d = p - c ∈ [1, 32768]`.
`find`'s postcondition `FoundAt s p l d := l < 3 ∨ MatchAt s p l d` (plus `l ≤ 258`,
`d ≤ 32768` as separate conjuncts, which `step*` hands to `scalar_tac` for `gain`). -/

/-- What a walk candidate `(best, bd)` means: nothing (`bd = 0`), or a real match at `p`
    of `best ≤ cap` bytes at distance `bd`. -/
def Cand (s : Slice Std.U8) (p cap best bd : Nat) : Prop :=
  bd = 0 ∨ (1 ≤ bd ∧ bd ≤ 32768 ∧ bd ≤ p ∧ best ≤ cap ∧ Matches s (p - bd) p best)

/-- The walk's distance check `p.wrapping_sub(c).wrapping_sub(1) < 32768`, with `c ≤ p`:
    `d = p - c` and `1 ≤ d ≤ 32768`. -/
theorem dist_of_wrapping {p c d i : Std.Usize} (hc : c.val ≤ p.val)
    (hd : d = core.num.Usize.wrapping_sub p c) (hi : i = core.num.Usize.wrapping_sub d 1#usize)
    (hlt : i < 32768#usize) : d.val = p.val - c.val ∧ 1 ≤ d.val ∧ d.val ≤ 32768 := by
  have hsz : 4294967296 ≤ Usize.size := by scalar_tac
  have hpl : p.val < Usize.size := by scalar_tac
  have hdv : d.val = p.val - c.val := by
    rw [hd, core.num.Usize.wrapping_sub_val_eq, UScalar.size_UScalarTyUsize]
    rw [show p.val + (Usize.size - c.val) = (p.val - c.val) + Usize.size by omega,
      Nat.add_mod_right, Nat.mod_eq_of_lt (by omega)]
  have hiv : i.val < 32768 := by scalar_tac
  have hdl : d.val < Usize.size := by omega
  rw [hi, core.num.Usize.wrapping_sub_val_eq, UScalar.size_UScalarTyUsize] at hiv
  simp only [show (1#usize).val = 1 by simp] at hiv
  refine ⟨hdv, ?_, ?_⟩
  · by_contra h0
    have : d.val = 0 := by omega
    rw [this, Nat.zero_add, Nat.mod_eq_of_lt (by omega)] at hiv
    omega
  · by_cases h0 : d.val = 0
    · rw [h0, Nat.zero_add, Nat.mod_eq_of_lt (by omega)] at hiv
      omega
    · rw [show d.val + (Usize.size - 1) = (d.val - 1) + Usize.size by omega, Nat.add_mod_right,
        Nat.mod_eq_of_lt (by omega)] at hiv
      omega

/-- A candidate taken by the walk is a `Cand`. -/
theorem Cand.of_common {s : Slice Std.U8} {p c d i l cap : Std.Usize} (hc : c.val ≤ p.val)
    (hd : d = core.num.Usize.wrapping_sub p c) (hi : i = core.num.Usize.wrapping_sub d 1#usize)
    (hlt : i < 32768#usize) (hl : l.val ≤ cap.val) (hm : Matches s c.val p.val l.val) :
    Cand s p.val cap.val l.val d.val := by
  obtain ⟨hdv, hd1, hd2⟩ := dist_of_wrapping hc hd hi hlt
  refine Or.inr ⟨hd1, hd2, by omega, hl, ?_⟩
  rw [show p.val - d.val = c.val by omega]
  exact hm

theorem walk_loop_spec (s : Slice Std.U8) {W : Std.Usize} (prev : Array Std.U32 W)
    (p cap gm n best bd : Std.Usize) (bg : Std.I32) (c k stop : Std.Usize) (pb : Std.U8)
    (hn : n.val = s.length) (hcap : p.val + cap.val ≤ s.length) (hcap258 : cap.val ≤ 258)
    (hc : c.val ≤ p.val) (hbest : p.val + best.val ≤ s.length)
    (hcand : Cand s p.val cap.val best.val bd.val) (hW : 0 < W.val) :
    slot.walk_loop s prev p cap gm n best bd bg c k stop pb ⦃ fun r =>
      p.val + r.1.val ≤ s.length ∧ Cand s p.val cap.val r.1.val r.2.val ⦄ := by
  rw [slot.walk_loop]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  apply Std.loop.spec_decr_nat
    (measure := fun r => r.2.2.2.2.1.val)
    (inv := fun r => r.2.2.2.1.val ≤ p.val ∧ p.val + r.1.val ≤ s.length ∧
      Cand s p.val cap.val r.1.val r.2.1.val)
  · rintro ⟨best, bd, bg, c, k, pb⟩ ⟨hc, hbest, hcand⟩
    simp only at hc hbest hcand
    simp only [slot.walk_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals first
      | exact (dist_of_wrapping hc (by assumption) (by assumption) (by assumption)).2.2
      | (refine ⟨by scalar_tac, by scalar_tac, Cand.of_common hc (by assumption) (by assumption)
          (by assumption) (by assumption) (by assumption), by scalar_tac⟩)
  · exact ⟨hc, hbest, hcand⟩

@[local step]
theorem walk_spec (s : Slice Std.U8) {W : Std.Usize} (prev : Array Std.U32 W)
    (p start cap «have» depth gm : Std.Usize)
    (hcap : p.val + cap.val ≤ s.length) (hcap258 : cap.val ≤ 258) (hst : start.val ≤ p.val)
    (hhave : p.val + «have».val ≤ s.length) (hW : 0 < W.val) :
    slot.walk s prev p start cap «have» depth gm ⦃ fun r =>
      p.val + r.1.val ≤ s.length ∧ Cand s p.val cap.val r.1.val r.2.val ⦄ := by
  rw [slot.walk]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  repeat' (split <;> step*)
  all_goals
    exact walk_loop_spec s prev p cap gm (Std.Slice.len s) «have» 0#usize _ start depth _ _
      (by simp) hcap hcap258 hst hhave (Or.inl rfl) hW

/-- A real match at `p`: the second half of `LZ77.Found`, on `Nat`s. -/
def MatchAt (s : Slice Std.U8) (p l d : Nat) : Prop :=
  3 ≤ l ∧ l ≤ 258 ∧ p + l ≤ s.length ∧ 1 ≤ d ∧ d ≤ 32768 ∧ d ≤ p ∧ Matches s (p - d) p l

/-- `find`'s postcondition: nothing usable (`l < 3`), or a real match. -/
def FoundAt (s : Slice Std.U8) (p l d : Nat) : Prop := l < 3 ∨ MatchAt s p l d

theorem FoundAt.of_cand {s : Slice Std.U8} {p cap : Nat} {l d : Std.Usize}
    (hc : Cand s p cap l.val d.val) (hd : ¬d = 0#usize) (hcap : cap ≤ 258)
    (hpl : p + l.val ≤ s.length) : FoundAt s p l.val d.val := by
  have hd' : d.val ≠ 0 := by intro h; apply hd; exact UScalar.eq_of_val_eq (by simp [h])
  rcases hc with h0 | ⟨hd1, hd2, hdp, hl, hm⟩
  · exact absurd h0 hd'
  · rcases Nat.lt_or_ge l.val 3 with h3 | h3
    · exact Or.inl h3
    · exact Or.inr ⟨h3, by omega, hpl, hd1, hd2, hdp, hm⟩

theorem Cand.len_le {s : Slice Std.U8} {p cap : Nat} {l d : Std.Usize}
    (hc : Cand s p cap l.val d.val) (hd : ¬d = 0#usize) (hcap : cap ≤ 258) : l.val ≤ 258 := by
  have hd' : d.val ≠ 0 := by intro h; apply hd; exact UScalar.eq_of_val_eq (by simp [h])
  rcases hc with h0 | ⟨_, _, _, hl, _⟩
  · exact absurd h0 hd'
  · omega

theorem Cand.dist_le {s : Slice Std.U8} {p cap l d : Nat} (hc : Cand s p cap l d) :
    d ≤ 32768 := by
  rcases hc with h0 | ⟨_, hd, _⟩ <;> omega

theorem FoundAt.none (s : Slice Std.U8) (p : Nat) : FoundAt s p (0#usize).val (0#usize).val :=
  Or.inl (by simp)

theorem FoundAt.real {s : Slice Std.U8} {p l d : Nat} (hf : FoundAt s p l d) (h3 : 3 ≤ l) :
    MatchAt s p l d := by
  rcases hf with h | h
  · omega
  · exact h

@[local step]
theorem find_spec (s : Slice Std.U8) {W : Std.Usize} (prev : Array Std.U32 W)
    (p st «have» minl depth gm : Std.Usize)
    (hp : p.val ≤ s.length) (hst : st.val ≤ p.val) (hhave : p.val + «have».val ≤ s.length)
    (hhave258 : «have».val ≤ 258) (hminl : 1 ≤ minl.val) (hminl' : p.val + minl.val ≤ s.length + 1)
    (hW : 0 < W.val) :
    slot.find s prev p st «have» minl depth gm ⦃ fun r => FoundAt s p.val r.1.val r.2.val ∧
      r.1.val ≤ 258 ∧ r.2.val ≤ 32768 ⦄ := by
  rw [slot.find]
  step*
  repeat' (split <;> step*)
  all_goals first
    | exact ⟨FoundAt.none s p.val, by simp, by simp⟩
    | exact ⟨FoundAt.of_cand (by assumption) (by assumption) (by scalar_tac) (by assumption),
        Cand.len_le (by assumption) (by assumption) (by scalar_tac),
        Cand.dist_le (by assumption)⟩

/-! ## 7. Token streams: retracting the last token

`toks out nt = toks out (nt - 1) ++ [out[nt-1]]` (`toks_pop`), and `decode` of a stream that
ends in a literal / a match of length `w` and decodes to `take p` means the shorter stream
decodes to `take (p - 1)` / `take (p - w)` (`decode_pop_lit`, `decode_pop_match`: the
emitted bytes are appended, `copyN_take_prefix`). `decode_length_le`: every token decodes to
at least one byte, so `nt ≤ p` survives a retraction. -/

theorem copyN_take_prefix (acc : List Nat) (d : Nat) :
    ∀ n, (copyN acc d n).take acc.length = acc := by
  intro n
  induction n with
  | zero => simp [copyN]
  | succ m ih =>
    simp only [copyN]
    rw [List.take_append_of_le_length (by simp)]
    exact ih

/-- Every token decodes to at least one byte, so a stream is never longer than its output. -/
theorem foldlM_emit_length : ∀ (ts : List Nat) (init acc : List Nat),
    ts.foldlM emit init = some acc → init.length + ts.length ≤ acc.length := by
  intro ts
  induction ts with
  | nil => intro init acc h; simp at h; subst h; simp
  | cons t ts ih =>
    intro init acc h
    simp only [List.foldlM_cons] at h
    cases he : emit init t with
    | none => rw [he] at h; simp at h
    | some a =>
      rw [he] at h
      simp only [Option.bind_eq_bind, Option.bind_some] at h
      have h1 := ih a acc h
      have h2 : init.length + 1 ≤ a.length := by
        simp only [emit] at he
        split at he
        · simp at he; subst he; simp
        · split at he
          · split at he
            · simp at he; subst he; rw [copyN_length]; simp only [tokLen]; omega
            · simp at he
          · simp at he
      simp only [List.length_cons]
      omega

theorem decode_length_le {ts acc : List Nat} (h : decode ts = some acc) :
    ts.length ≤ acc.length := by
  have := foldlM_emit_length ts [] acc h
  simpa using this

/-- Dropping a literal from the end of a stream that decodes to a prefix. -/
theorem decode_pop_lit {ts : List Nat} {t : Nat} {inp : List Nat} {p : Nat}
    (hp : p ≤ inp.length) (hd : decode (ts ++ [t]) = some (inp.take p)) (ht : t < 256) :
    1 ≤ p ∧ decode ts = some (inp.take (p - 1)) := by
  rw [decode_snoc] at hd
  cases hts : decode ts with
  | none => rw [hts] at hd; simp at hd
  | some acc =>
    rw [hts] at hd
    simp only [Option.bind_some, emit, if_pos ht] at hd
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
theorem decode_pop_match {ts : List Nat} {t : Nat} {inp : List Nat} {p : Nat}
    (hp : p ≤ inp.length) (hd : decode (ts ++ [t]) = some (inp.take p)) (ht : 256 ≤ t) :
    tokLen t ≤ p ∧ decode ts = some (inp.take (p - tokLen t)) := by
  rw [decode_snoc] at hd
  cases hts : decode ts with
  | none => rw [hts] at hd; simp at hd
  | some acc =>
    rw [hts] at hd
    simp only [Option.bind_some, emit, if_neg (show ¬ t < 256 by omega)] at hd
    split at hd
    · split at hd
      · have hacc : copyN acc (tokDist t) (tokLen t) = inp.take p := Option.some.inj hd
        have hlen : acc.length + tokLen t = p := by
          have := congrArg List.length hacc
          simp [List.length_take] at this; omega
        refine ⟨by omega, ?_⟩
        apply congrArg some
        have := congrArg (List.take acc.length) hacc
        rw [copyN_take_prefix, List.take_take] at this
        rw [this, show min acc.length p = p - tokLen t by omega]
      · simp at hd
    · simp at hd

/-- The first `nt` tokens are the first `nt - 1` and token `nt - 1`. -/
theorem toks_pop (out : Slice Std.U32) (nt : Nat) (h0 : 0 < nt) (hle : nt ≤ out.length) :
    toks out nt = toks out (nt - 1) ++ [(out.val[nt - 1]!).val] := by
  have hlt : nt - 1 < out.val.length := by
    have : out.length = out.val.length := rfl
    omega
  simp only [toks]
  conv_lhs => rw [show nt = (nt - 1) + 1 by omega]
  rw [List.take_add_one, List.getElem?_eq_getElem hlt, Option.toList_some, List.map_append]
  simp [getElem!_pos out.val (nt - 1) hlt]

theorem toks_length (out : Slice Std.U32) (nt : Nat) (h : nt ≤ out.length) :
    (toks out nt).length = nt := by
  simp only [toks, List.length_map, List.length_take]
  have : out.length = out.val.length := rfl
  omega

/-! ## 8. The decoding invariant `Dec` and the two token writers

`Dec s out nt p`: `p ≤ n`, `nt ≤ p`, `n ≤ out.length`, and the first `nt` tokens decode to the
first `p` bytes. Every loop carries it (with `out.length` fixed); each write steps it
(`Dec.lit`, `Dec.match`), each popped token retracts it (`Dec.pop_lit`, `Dec.pop_match`),
and `Dec.done` is the obligation once `p = n`. The `_step` forms take exactly the facts
`step*` leaves after `put_lit`/`put_match`. -/

/-- `nt` tokens written into `out` decode to the first `p` input bytes (`out` long enough). -/
def Dec (s : Slice Std.U8) (out : Slice Std.U32) (nt p : Nat) : Prop :=
  p ≤ s.length ∧ nt ≤ p ∧ s.length ≤ out.length ∧
    decode (toks out nt) = some ((bytes s).take p)

theorem Dec.init (input : Slice Std.U8) (out : Slice Std.U32) (h : input.length ≤ out.length) :
    Dec input out (0#usize).val (0#usize).val :=
  ⟨by simp, by simp, h, by simp [toks, LZ77.decode]⟩

/-- Writing the literal `s[p]` at `out[nt]`. -/
theorem Dec.lit {s : Slice Std.U8} {out : Slice Std.U32} {nt p : Nat} (h : Dec s out nt p)
    (hp : p < s.length) (ntU : Std.Usize) (hnt : ntU.val = nt) (v : Std.U32)
    (hv : v.val = (s.val[p]!).val) :
    Dec s (out.set ntU v) (nt + 1) (p + 1) := by
  obtain ⟨hps, hntp, hso, hde⟩ := h
  have hntl : ntU.val < out.length := by omega
  refine ⟨by omega, by omega, by rw [Std.Slice.set_length]; exact hso, ?_⟩
  rw [← hnt]
  refine emit_lit s out ntU p v (by rw [hnt]; exact hde) hp hntl ?_
  have hpl : p < s.val.length := hp
  rw [hv, bytes_getElem! s p hpl, getElem!_pos s.val p hpl]

/-- Writing the match token `(d, l)` at `out[nt]`. -/
theorem Dec.match {s : Slice Std.U8} {out : Slice Std.U32} {nt p l d : Nat} (h : Dec s out nt p)
    (hm : MatchAt s p l d) (ntU : Std.Usize) (hnt : ntU.val = nt) (v : Std.U32)
    (hv : v.val = LZ77.mkMatch d l) :
    Dec s (out.set ntU v) (nt + 1) (p + l) := by
  obtain ⟨hps, hntp, hso, hde⟩ := h
  obtain ⟨h3, h258, hpl, hd1, hd32, hdp, hmm⟩ := hm
  have hntl : ntU.val < out.length := by omega
  refine ⟨by omega, by omega, by rw [Std.Slice.set_length]; exact hso, ?_⟩
  rw [← hnt]
  exact emit_match s out ntU p d l v (by rw [hnt]; exact hde) hntl hd1 hdp hd32 h3 h258 hpl hmm hv

/-- Retracting a trailing literal. -/
theorem Dec.pop_lit {s : Slice Std.U8} {out : Slice Std.U32} {nt p : Nat} (h : Dec s out nt p)
    (h0 : 0 < nt) (hle : nt ≤ out.length) (ht : (out.val[nt - 1]!).val < 256) :
    1 ≤ p ∧ Dec s out (nt - 1) (p - 1) := by
  obtain ⟨hps, hntp, hso, hde⟩ := h
  rw [toks_pop out nt h0 hle] at hde
  obtain ⟨hp1, hde'⟩ := decode_pop_lit (by simpa using hps) hde ht
  exact ⟨hp1, by omega, by omega, hso, hde'⟩

/-- Retracting a trailing match token (of length `tokLen t`). -/
theorem Dec.pop_match {s : Slice Std.U8} {out : Slice Std.U32} {nt p : Nat} (h : Dec s out nt p)
    (h0 : 0 < nt) (hle : nt ≤ out.length) (ht : 256 ≤ (out.val[nt - 1]!).val) :
    tokLen (out.val[nt - 1]!).val ≤ p ∧
      Dec s out (nt - 1) (p - tokLen (out.val[nt - 1]!).val) := by
  obtain ⟨hps, hntp, hso, hde⟩ := h
  rw [toks_pop out nt h0 hle] at hde
  obtain ⟨hw, hde'⟩ := decode_pop_match (by simpa using hps) hde ht
  have hlen := decode_length_le hde'
  rw [toks_length out (nt - 1) (by omega), List.length_take, bytes_length] at hlen
  exact ⟨hw, by omega, by omega, hso, hde'⟩

/-- All `n` bytes consumed: the stream is valid. -/
theorem Dec.done {s : Slice Std.U8} {out : Slice Std.U32} {nt p : Nat} (h : Dec s out nt p)
    (hp : s.length ≤ p) : nt ≤ s.length ∧ LZ77.Valid (bytes s) (toks out nt) := by
  obtain ⟨hps, hntp, hso, hde⟩ := h
  refine ⟨by omega, ?_⟩
  unfold LZ77.Valid
  rw [hde, show p = s.length by omega, ← bytes_length, List.take_length]

/-- `Dec.lit` in the shape `put_lit` leaves: `b = s[p]; v = b as u32; out1 = out.set nt v`. -/
theorem Dec.lit_step {s : Slice Std.U8} {out out1 : Slice Std.U32} {ntU nt1 pU : Std.Usize}
    {b : Std.U8} {v : Std.U32} (h : Dec s out ntU.val pU.val) (hp : pU.val < s.val.length)
    (hb : b = s.val[pU.val]) (hv : v = UScalar.cast .U32 b) (hout1 : out1 = out.set ntU v)
    (hnt1 : nt1.val = ntU.val + 1) :
    nt1.val = ntU.val + 1 ∧ out1.length = out.length ∧ Dec s out1 nt1.val (pU.val + 1) := by
  subst hout1
  refine ⟨hnt1, Std.Slice.set_length .., ?_⟩
  rw [hnt1]
  exact Dec.lit h hp ntU rfl v (by rw [hv, U8.cast_U32_val_eq, hb, getElem!_pos s.val pU.val hp])

@[local step]
theorem put_lit_spec (s : Slice Std.U8) (out : Slice Std.U32) (nt p : Std.Usize)
    (hdec : Dec s out nt.val p.val) (hp : p.val < s.length) :
    slot.put_lit s out nt p ⦃ fun r => r.1.val = nt.val + 1 ∧ r.2.length = out.length ∧
      Dec s r.2 r.1.val (p.val + 1) ⦄ := by
  rw [slot.put_lit]
  step*
  exact Dec.lit_step hdec (by scalar_tac) (by assumption) (by assumption) (by assumption)
    (by assumption)

/-- `Dec.match` in the shape `put_match` leaves. -/
theorem Dec.match_step {s : Slice Std.U8} {out out1 : Slice Std.U32} {ntU nt1 pU dU lU e : Std.Usize}
    {v : Std.U32} (h : Dec s out ntU.val pU.val) (hm : MatchAt s pU.val lU.val dU.val)
    (hout1 : out1 = out.set ntU v) (hv : v.val = LZ77.mkMatch dU.val lU.val)
    (hnt1 : nt1.val = ntU.val + 1) (he : e.val = pU.val + lU.val) :
    nt1.val = ntU.val + 1 ∧ e.val = pU.val + lU.val ∧ out1.length = out.length ∧
      Dec s out1 nt1.val e.val := by
  subst hout1
  refine ⟨hnt1, he, Std.Slice.set_length .., ?_⟩
  rw [hnt1, he]
  exact Dec.match h hm ntU rfl v hv

/-- With `VERIFY = 0` and a real match, `put_match` writes the match token. -/
@[local step]
theorem put_match_spec (s : Slice Std.U8) (out : Slice Std.U32) (nt p d l : Std.Usize)
    (hdec : Dec s out nt.val p.val) (hm : MatchAt s p.val l.val d.val) :
    slot.put_match s out nt p d l ⦃ fun r => r.1.1.val = nt.val + 1 ∧
      r.1.2.val = p.val + l.val ∧ r.2.length = out.length ∧ Dec s r.2 r.1.1.val r.1.2.val ⦄ := by
  rw [slot.put_match]
  have hm' := hm
  obtain ⟨h3, h258, hpl, hd1, hd32, hdp, _⟩ := hm'
  step*
  -- only the `VERIFY = 0`, all-checks-pass branch is left: the others contradict `MatchAt`
  exact Dec.match_step hdec hm (by assumption)
    (by simp only [LZ77.mkMatch, LZ77.MATCH_BASE]; scalar_tac) (by assumption) (by assumption)

/-! ## 9. Backward token merging

Before a match `(l, d)` at `p` is written, the loop pops earlier tokens whose bytes also match
at distance `d`: a literal with `s[p-1] = s[p-1-d]` (`MatchAt.back_lit`) or a whole match of
`w` bytes with `same(p-w-d, p-w, w) = 1` (`MatchAt.back_match`). `BackInv` = `Dec` at the
current `(nt, p)` + `MatchAt` for `(p, l, d)` + the match still ends at `E` + `p ≤ P0`. -/

/-- One byte: `s[p-1] = s[p-1-d]`. -/
theorem MatchAt.back_lit {s : Slice Std.U8} {p l d : Nat} (h : MatchAt s p l d) (hl : l < 258)
    (hdp : d < p) (heq : s.val[p - 1]! = s.val[p - 1 - d]!) : MatchAt s (p - 1) (l + 1) d := by
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
theorem MatchAt.back_match {s : Slice Std.U8} {p l d w : Nat} (h : MatchAt s p l d)
    (hlw : l + w ≤ 258) (hw : w ≤ p) (hdw : d ≤ p - w) (hmw : Matches s (p - w - d) (p - w) w) :
    MatchAt s (p - w) (l + w) d := by
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

/-- The state of the backward merge: `nt` tokens decode to `p` bytes, the pending match
    `(l, d)` at `p` is real and ends at `E`, and `p` never grew past `P0`. -/
def BackInv (input : Slice Std.U8) (out : Slice Std.U32) (d E P0 : Nat) (nt p l : Nat) : Prop :=
  Dec input out nt p ∧ MatchAt input p l d ∧ p + l = E ∧ p ≤ P0

/-- Absorbing the literal `out[nt-1]` whose byte also matches at distance `d`. The hypotheses
    are ordered for `step*`'s facts: the new state `(i1, i2, l1)` is fixed by the goal, `t`, `x`,
    `y`, `i4` by `assumption`, everything else by `scalar_tac`. -/
theorem BackInv.lit {input : Slice Std.U8} {out : Slice Std.U32} {d E P0 : Nat}
    {nt p l i1 i2 i4 l1 : Std.Usize} {t : Std.U32} {x y : Std.U8}
    (h : BackInv input out d E P0 nt.val p.val l.val)
    (hi1 : i1.val = nt.val - 1) (hntl : nt.val ≤ out.length) (hnt0 : 1 ≤ nt.val)
    (hi1l : i1.val < out.val.length) (ht : t = out.val[i1.val]) (ht256 : t < 256#u32)
    (hi2 : i2.val = p.val - 1) (hi2l : i2.val < input.val.length) (hx : x = input.val[i2.val])
    (hxy : x = y) (hi4 : i4.val = i2.val - d) (hi4l : i4.val < input.val.length)
    (hy : y = input.val[i4.val]) (hl : l.val < 258) (hdp : d < p.val)
    (hl1 : l1.val = l.val + 1) :
    BackInv input out d E P0 i1.val i2.val l1.val := by
  obtain ⟨hdec, hm, hE, hP⟩ := h
  have ht' : (out.val[nt.val - 1]!).val < 256 := by
    rw [← hi1, getElem!_pos out.val i1.val hi1l, ← ht]; scalar_tac
  obtain ⟨hp1, hdec'⟩ := Dec.pop_lit hdec (by omega) hntl ht'
  have heq : input.val[p.val - 1]! = input.val[p.val - 1 - d]! := by
    rw [← hi2, getElem!_pos input.val i2.val hi2l, show i2.val - d = i4.val by omega,
      getElem!_pos input.val i4.val hi4l, ← hx, ← hy, hxy]
  have hm' := MatchAt.back_lit hm hl hdp heq
  rw [hi1, hi2, hl1]
  exact ⟨hdec', hm', by omega, by omega⟩

/-- Absorbing the whole match token `t = out[nt-1]` (length `w`) whose bytes also match at `d`.
    The new state `(i1, i10, i9)` is fixed by the goal; `t`, and `(i12, i11, w)` through
    `same`'s postcondition, by `assumption`; the rest by `scalar_tac`. -/
theorem BackInv.match {input : Slice Std.U8} {out : Slice Std.U32} {d E P0 : Nat}
    {nt p l i1 w i9 i10 i11 i12 : Std.Usize} {t : Std.U32}
    (h : BackInv input out d E P0 nt.val p.val l.val)
    (hi1 : i1.val = nt.val - 1) (hntl : nt.val ≤ out.length) (hnt0 : 1 ≤ nt.val)
    (hi1l : i1.val < out.val.length) (ht : t = out.val[i1.val])
    (hsame : i12.val = 1 → Matches input i11.val i10.val w.val) (hi12 : i12 = 1#usize)
    (ht24 : 16777216 ≤ t.val) (hwv : w.val = (t.val - 16777216) % 256 + 3)
    (hi9 : i9.val = l.val + w.val) (hi9' : i9.val ≤ 258) (hi10 : i10.val = p.val - w.val)
    (hwp : w.val ≤ p.val) (hdw : d ≤ i10.val) (hi11 : i11.val = i10.val - d) :
    BackInv input out d E P0 i1.val i10.val i9.val := by
  obtain ⟨hdec, hm, hE, hP⟩ := h
  have htv : (out.val[nt.val - 1]!).val = t.val := by
    rw [← hi1, getElem!_pos out.val i1.val hi1l, ← ht]
  have hwv' : w.val = tokLen (out.val[nt.val - 1]!).val := by
    rw [htv, hwv]
    simp only [tokLen, MATCH_BASE]
  obtain ⟨hwl, hdec'⟩ := Dec.pop_match hdec (by omega) hntl (by omega)
  rw [← hwv'] at hdec'
  have hmw : Matches input (p.val - w.val - d) (p.val - w.val) w.val := by
    have := hsame (by rw [hi12]; rfl)
    rw [hi11, hi10] at this
    exact this
  have hm' := MatchAt.back_match hm (by omega) hwp (by omega) hmw
  rw [hi1, hi10, hi9]
  exact ⟨hdec', hm', by omega, by omega⟩

theorem back_loop_inv (input : Slice Std.U8) (out : Slice Std.U32) (nt p l d back : Std.Usize)
    (E P0 : Nat) (hP0 : P0 + 8 ≤ input.length)
    (hinv : BackInv input out d.val E P0 nt.val p.val l.val) :
    slot.run_loop0_loop2 input out nt p l d back ⦃ fun r =>
      BackInv input out d.val E P0 r.1.val r.2.1.val r.2.2.val ⦄ := by
  rw [slot.run_loop0_loop2]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  apply Std.loop.spec_decr_nat
    (measure := fun r => slot.BACKTOK.val - r.2.2.2.val)
    (inv := fun r => BackInv input out d.val E P0 r.1.val r.2.1.val r.2.2.1.val)
  · rintro ⟨nt, p, l, back⟩ hinv
    simp only at hinv
    have hinv' := hinv
    obtain ⟨⟨hps, hntp, hso, _⟩, ⟨h3, h258, hpl, hd1, hd32, hdp, _⟩, hE, hp0⟩ := hinv'
    simp only [slot.run_loop0_loop2.body]
    step*
    all_goals first
      | (refine ⟨BackInv.lit hinv (by scalar_tac) (by scalar_tac) (by scalar_tac) (by scalar_tac)
          (by assumption) (by assumption) (by scalar_tac) (by scalar_tac) (by assumption)
          (by assumption) (by assumption) (by scalar_tac) (by assumption) (by scalar_tac)
          (by scalar_tac) (by scalar_tac), by scalar_tac⟩)
      | (refine ⟨BackInv.match hinv (by scalar_tac) (by scalar_tac) (by scalar_tac) (by scalar_tac)
          (by assumption) (by assumption) (by assumption) (by scalar_tac) (by scalar_tac)
          (by scalar_tac) (by scalar_tac) (by scalar_tac) (by scalar_tac) (by scalar_tac)
          (by scalar_tac), by scalar_tac⟩)
  · exact hinv

/-- The backward merge, ghost-free: the result is a real match ending where the input one did. -/
@[local step]
theorem back_loop_spec (input : Slice Std.U8) (out : Slice Std.U32) (nt p l d back : Std.Usize)
    (hp8 : p.val + 8 ≤ input.length) (hdec : Dec input out nt.val p.val)
    (hm : MatchAt input p.val l.val d.val) :
    slot.run_loop0_loop2 input out nt p l d back ⦃ fun r =>
      Dec input out r.1.val r.2.1.val ∧ MatchAt input r.2.1.val r.2.2.val d.val ∧
      r.2.1.val + r.2.2.val = p.val + l.val ∧ r.2.1.val ≤ p.val ⦄ := by
  apply Std.WP.spec_mono (back_loop_inv input out nt p l d back (p.val + l.val) p.val hp8
    ⟨hdec, hm, rfl, le_refl _⟩)
  intro r h
  exact h

/-! ## 10. The lazy step: move to `p + 1` while its match saves more

`LazyInv` = `Dec` + `out` length + `MatchAt` for the pending `(l, d)` at `p` + `HeadBound head
(p + 1)` + `p < lim` + `ins ≤ p + 2`. Accepting writes the literal at `p` and takes the
`FoundAt` match at `p + 1` (`LazyInv.accept`); rejecting only changed the table. -/

/-- The state of the lazy loop: tokens decode to `p` bytes, `out` keeps its length `L`, the
    pending match `(l, d)` at `p` is real, head entries are at most `p + 1`, `p < lim`, and
    the insertion cursor is at most `p + 2`. -/
def LazyInv (input : Slice Std.U8) (L lim : Nat) (out : Slice Std.U32) (nt p : Nat)
    {N : Std.Usize} (head : Array Std.U32 N) (ins l d : Nat) : Prop :=
  Dec input out nt p ∧ out.length = L ∧ MatchAt input p l d ∧ HeadBound head (p + 1) ∧
    p < lim ∧ ins ≤ p + 2

/-- The lazy step moved to `i = p + 1`: the literal at `p` is written, `(l1, d1)` is found at `i`. -/
theorem LazyInv.accept {input : Slice Std.U8} {L lim p' B : Nat} {out1 : Slice Std.U32}
    {nt1 i ins1 l1 d1 minl : Std.Usize} {N : Std.Usize} {head1 : Array Std.U32 N}
    (hdec : Dec input out1 nt1.val p') (hi : i.val = p') (hlen : out1.length = L)
    (hf : FoundAt input i.val l1.val d1.val) (hl1 : minl.val ≤ l1.val) (hminl : 3 ≤ minl.val)
    (hB : HeadBound head1 B) (hBi : B ≤ i.val + 1) (hilim : i.val < lim)
    (hins : ins1.val ≤ i.val + 2) :
    LazyInv input L lim out1 nt1.val i.val head1 ins1.val l1.val d1.val := by
  subst hi
  refine ⟨hdec, hlen, ?_, HeadBound.mono hB hBi, hilim, hins⟩
  rcases hf with h | h
  · omega
  · exact h

/-- The lazy step stays at `p` (only the table changed). -/
theorem LazyInv.reject {input : Slice Std.U8} {L lim : Nat} {out : Slice Std.U32}
    {nt p ins ins1 l d B : Nat} {N : Std.Usize} {head head1 : Array Std.U32 N}
    (h : LazyInv input L lim out nt p head ins l d) (hB : HeadBound head1 B) (hBp : B ≤ p + 1)
    (hins1 : ins1 ≤ p + 2) : LazyInv input L lim out nt p head1 ins1 l d := by
  obtain ⟨hdec, hlen, hm, _, hplim, _⟩ := h
  exact ⟨hdec, hlen, hm, HeadBound.mono hB hBp, hplim, hins1⟩

theorem lazy_loop_inv {H W : Std.Usize} (input : Slice Std.U8) (out : Slice Std.U32)
    (cls nt p : Std.Usize) (mask : Std.U32) (minl lazy : Std.Usize) (head : Array Std.U32 H)
    (prev : Array Std.U32 W) (lim ins l d : Std.Usize) (go : Std.U32) (L : Nat)
    (hlim : lim.val + 8 = input.length) (hminl : 3 ≤ minl.val) (hminl8 : minl.val ≤ 8)
    (hH : 0 < H.val) (hW : 0 < W.val)
    (hinv : LazyInv input L lim.val out nt.val p.val head ins.val l.val d.val) :
    slot.run_loop0_loop1 input out cls nt p mask minl lazy head prev lim ins l d go ⦃ fun r =>
      LazyInv input L lim.val r.1 r.2.1.val r.2.2.1.val r.2.2.2.1 r.2.2.2.2.2.1.val
        r.2.2.2.2.2.2.1.val r.2.2.2.2.2.2.2.val ⦄ := by
  rw [slot.run_loop0_loop1]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  apply Std.loop.spec_decr_nat
    (measure := fun r => lim.val - r.2.2.1.val + r.2.2.2.2.2.2.2.2.val)
    (inv := fun r => LazyInv input L lim.val r.1 r.2.1.val r.2.2.1.val r.2.2.2.1
      r.2.2.2.2.2.1.val r.2.2.2.2.2.2.1.val r.2.2.2.2.2.2.2.1.val)
  · rintro ⟨out, nt, p, head, prev, ins, l, d, go⟩ hinv
    simp only at hinv
    have hinv' := hinv
    obtain ⟨⟨hps, hntp, hso, _⟩, hL, ⟨h3, h258, hpl, hd1, hd32, hdp, _⟩, hB, hplim, hins⟩ := hinv'
    simp only [slot.run_loop0_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals first
      | exact hinv.1
      | (refine ⟨LazyInv.accept (by assumption) (by scalar_tac) (by scalar_tac) (by assumption)
          (by scalar_tac) hminl (by assumption) (by scalar_tac) (by scalar_tac) (by scalar_tac),
          by scalar_tac⟩)
      | (refine ⟨LazyInv.reject hinv (by assumption) (by scalar_tac) (by scalar_tac),
          by scalar_tac⟩)
  · exact hinv

/-- The lazy loop with flat pre- and postconditions (so `step*` can use it inside `run`'s body).
    The pending match ends at `p + l`, which bounds the head entries from then on. -/
@[local step]
theorem lazy_loop_spec {H W : Std.Usize} (input : Slice Std.U8) (out : Slice Std.U32)
    (cls nt p : Std.Usize) (mask : Std.U32) (minl lazy : Std.Usize) (head : Array Std.U32 H)
    (prev : Array Std.U32 W) (lim ins l d : Std.Usize) (go : Std.U32) (L : Nat)
    (hlim : lim.val + 8 = input.length) (hminl : 3 ≤ minl.val) (hminl8 : minl.val ≤ 8)
    (hH : 0 < H.val) (hW : 0 < W.val)
    (hdec : Dec input out nt.val p.val) (hlen : out.length = L)
    (hm : MatchAt input p.val l.val d.val) (hB : HeadBound head (p.val + 1))
    (hplim : p.val < lim.val) (hins : ins.val ≤ p.val + 2) :
    slot.run_loop0_loop1 input out cls nt p mask minl lazy head prev lim ins l d go ⦃ fun r =>
      Dec input r.1 r.2.1.val r.2.2.1.val ∧ r.1.length = L ∧
      MatchAt input r.2.2.1.val r.2.2.2.2.2.2.1.val r.2.2.2.2.2.2.2.val ∧
      HeadBound r.2.2.2.1 (r.2.2.1.val + r.2.2.2.2.2.2.1.val) ∧ r.2.2.1.val < lim.val ∧
      r.2.2.2.2.2.1.val ≤ r.2.2.1.val + 2 ∧ 3 ≤ r.2.2.2.2.2.2.1.val ⦄ := by
  apply Std.WP.spec_mono (lazy_loop_inv input out cls nt p mask minl lazy head prev lim ins l d go L
    hlim hminl hminl8 hH hW ⟨hdec, hlen, hm, hB, hplim, hins⟩)
  rintro ⟨out', nt', p', head', prev', ins', l', d'⟩ ⟨hdec', hlen', hm', hB', hplim', hins'⟩
  exact ⟨hdec', hlen', hm', HeadBound.mono hB' (by have := hm'.1; omega), hplim', hins', hm'.1⟩

/-! ## 11. The insert loops and the literal loops of `run`

Every insert loop keeps `HeadBound head B` for the bound `B` its caller picks (`p` before the
search, the match end `p + l` after a match): each inserted position is `< B + 1`. Inside a
match, loop 3 records the first positions (up to the `INS_MAX` cap and `lim`), the stride loop
every `STRIDE`-th position while `end - ins > TAIL + STRIDE` (only under `if STRIDE > 0`, which
gives the measure `end - ins`), and loops 5 and 6 (the two copies of the tail loop, one per
branch of `if STRIDE > 0`) the last `TAIL` positions. Loop 7 writes the skipped literals. -/

@[local step]
theorem ins_loop0_spec {H W : Std.Usize} (input : Slice Std.U8) (p : Std.Usize) (mask : Std.U32)
    (head : Array Std.U32 H) (prev : Array Std.U32 W) (ins : Std.Usize) (B : Nat)
    (hB : HeadBound head B) (hpB : p.val < B + 1) (hp4 : p.val + 4 ≤ Std.Usize.max)
    (hH : 0 < H.val) (hW : 0 < W.val) :
    slot.run_loop0_loop0 input p mask head prev ins ⦃ fun r => HeadBound r.1 B ⦄ := by
  rw [slot.run_loop0_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun r => p.val - r.2.2.val)
    (inv := fun r => HeadBound r.1 B)
  · rintro ⟨head, prev, ins⟩ hB
    simp only at hB
    simp only [slot.run_loop0_loop0.body]
    step*
  · exact hB

@[local step]
theorem ins_loop3_spec {H W : Std.Usize} (input : Slice Std.U8) (mask : Std.U32)
    (head : Array Std.U32 H) (prev : Array Std.U32 W) (ins stop : Std.Usize) (B : Nat)
    (hB : HeadBound head B) (hsB : stop.val < B + 1) (hs4 : stop.val + 4 ≤ Std.Usize.max)
    (hH : 0 < H.val) (hW : 0 < W.val) :
    slot.run_loop0_loop3 input mask head prev ins stop ⦃ fun r =>
      HeadBound r.1 B ∧ (r.2.2.val ≤ ins.val ∨ r.2.2.val ≤ stop.val) ⦄ := by
  rw [slot.run_loop0_loop3]
  apply Std.loop.spec_decr_nat
    (measure := fun r => stop.val - r.2.2.val)
    (inv := fun r => HeadBound r.1 B ∧ (r.2.2.val ≤ ins.val ∨ r.2.2.val ≤ stop.val))
  · rintro ⟨head, prev, ins'⟩ ⟨hB, hins⟩
    simp only at hB hins
    simp only [slot.run_loop0_loop3.body]
    step*
  · exact ⟨hB, Or.inl (le_refl _)⟩

/-- Sparse recording inside a long match: positions `ins, ins + STRIDE, ...` while
    `end - ins > TAIL + STRIDE` (so `ins + STRIDE + TAIL < end` after each step). -/
@[local step]
theorem stride_loop_spec {H W : Std.Usize} (input : Slice Std.U8) (mask : Std.U32)
    (head : Array Std.U32 H) (prev : Array Std.U32 W) (lim ins «end» : Std.Usize) (B : Nat)
    (hB : HeadBound head B) (heB : «end».val < B + 1) (hl4 : lim.val + 4 ≤ Std.Usize.max)
    (hH : 0 < H.val) (hW : 0 < W.val) (hS : 0 < slot.STRIDE.val)
    (hie : ins.val ≤ «end».val) :
    slot.run_loop0_loop4 input mask head prev lim ins «end» ⦃ fun r =>
      HeadBound r.1 B ∧ r.2.2.val ≤ «end».val ∧
        (r.2.2.val ≤ ins.val ∨ r.2.2.val + slot.TAIL.val < «end».val) ⦄ := by
  rw [slot.run_loop0_loop4]
  apply Std.loop.spec_decr_nat
    (measure := fun r => «end».val - r.2.2.val)
    (inv := fun r => HeadBound r.1 B ∧ r.2.2.val ≤ «end».val ∧
      (r.2.2.val ≤ ins.val ∨ r.2.2.val + slot.TAIL.val < «end».val))
  · rintro ⟨head, prev, ins'⟩ ⟨hB, hie', hins⟩
    simp only at hB hie' hins
    simp only [slot.run_loop0_loop4.body]
    step*
    all_goals first
      | exact ⟨hB, hie', hins⟩
      | exact ⟨by assumption, by scalar_tac, by scalar_tac, by scalar_tac⟩
  · exact ⟨hB, hie, Or.inl (le_refl _)⟩

@[local step]
theorem ins_loop5_spec {H W : Std.Usize} (input : Slice Std.U8) (mask : Std.U32)
    (head : Array Std.U32 H) (prev : Array Std.U32 W) (lim ins «end» : Std.Usize) (B : Nat)
    (hB : HeadBound head B) (heB : «end».val < B + 1) (hl4 : lim.val + 4 ≤ Std.Usize.max)
    (hH : 0 < H.val) (hW : 0 < W.val) :
    slot.run_loop0_loop5 input mask head prev lim ins «end» ⦃ fun r =>
      HeadBound r.1 B ∧ (r.2.2.val ≤ ins.val ∨ r.2.2.val ≤ «end».val) ⦄ := by
  rw [slot.run_loop0_loop5]
  apply Std.loop.spec_decr_nat
    (measure := fun r => «end».val - r.2.2.val)
    (inv := fun r => HeadBound r.1 B ∧ (r.2.2.val ≤ ins.val ∨ r.2.2.val ≤ «end».val))
  · rintro ⟨head, prev, ins'⟩ ⟨hB, hins⟩
    simp only at hB hins
    simp only [slot.run_loop0_loop5.body]
    step*
  · exact ⟨hB, Or.inl (le_refl _)⟩

@[local step]
theorem ins_loop6_spec {H W : Std.Usize} (input : Slice Std.U8) (mask : Std.U32)
    (head : Array Std.U32 H) (prev : Array Std.U32 W) (lim ins «end» : Std.Usize) (B : Nat)
    (hB : HeadBound head B) (heB : «end».val < B + 1) (hl4 : lim.val + 4 ≤ Std.Usize.max)
    (hH : 0 < H.val) (hW : 0 < W.val) :
    slot.run_loop0_loop6 input mask head prev lim ins «end» ⦃ fun r =>
      HeadBound r.1 B ∧ (r.2.2.val ≤ ins.val ∨ r.2.2.val ≤ «end».val) ⦄ := by
  rw [slot.run_loop0_loop6]
  apply Std.loop.spec_decr_nat
    (measure := fun r => «end».val - r.2.2.val)
    (inv := fun r => HeadBound r.1 B ∧ (r.2.2.val ≤ ins.val ∨ r.2.2.val ≤ «end».val))
  · rintro ⟨head, prev, ins'⟩ ⟨hB, hins⟩
    simp only at hB hins
    simp only [slot.run_loop0_loop6.body]
    step*
  · exact ⟨hB, Or.inl (le_refl _)⟩

@[local step]
theorem skip_loop_spec (input : Slice Std.U8) (out : Slice Std.U32) (nt p lim step : Std.Usize)
    (hdec : Dec input out nt.val p.val) (hlim : lim.val ≤ input.length) :
    slot.run_loop0_loop7 input out nt p lim step ⦃ fun r =>
      Dec input r.1 r.2.1.val r.2.2.val ∧ r.1.length = out.length ∧ p.val ≤ r.2.2.val ⦄ := by
  rw [slot.run_loop0_loop7]
  apply Std.loop.spec_decr_nat
    (measure := fun r => r.2.2.2.val)
    (inv := fun r => Dec input r.1 r.2.1.val r.2.2.1.val ∧ r.1.length = out.length ∧
      p.val ≤ r.2.2.1.val)
  · rintro ⟨out', nt', p', step'⟩ ⟨hdec', hlen', hp'⟩
    simp only at hdec' hlen' hp'
    simp only [slot.run_loop0_loop7.body]
    step*
  · exact ⟨hdec, rfl, le_refl _⟩

@[local step]
theorem tail_loop1_spec (input : Slice Std.U8) (out : Slice Std.U32) (n nt p : Std.Usize)
    (hn : n.val = input.length) (hdec : Dec input out nt.val p.val) :
    slot.run_loop1 input out n nt p ⦃ fun r => r.1.val ≤ input.length ∧
      r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
  rw [slot.run_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun r => n.val - r.2.2.val)
    (inv := fun r => Dec input r.1 r.2.1.val r.2.2.val ∧ r.1.length = out.length)
  · rintro ⟨out', nt', p'⟩ ⟨hdec', hlen'⟩
    simp only at hdec' hlen'
    simp only [slot.run_loop1.body]
    step*
    have hd := Dec.done hdec' (by scalar_tac)
    exact ⟨hd.1, hlen', hd.2⟩
  · exact ⟨hdec, rfl⟩

@[local step]
theorem tail_loop2_spec (input : Slice Std.U8) (out : Slice Std.U32) (n nt p : Std.Usize)
    (hn : n.val = input.length) (hdec : Dec input out nt.val p.val) :
    slot.run_loop2 input out n nt p ⦃ fun r => r.1.val ≤ input.length ∧
      r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
  rw [slot.run_loop2]
  apply Std.loop.spec_decr_nat
    (measure := fun r => n.val - r.2.2.val)
    (inv := fun r => Dec input r.1 r.2.1.val r.2.2.val ∧ r.1.length = out.length)
  · rintro ⟨out', nt', p'⟩ ⟨hdec', hlen'⟩
    simp only at hdec' hlen'
    simp only [slot.run_loop2.body]
    step*
    have hd := Dec.done hdec' (by scalar_tac)
    exact ⟨hd.1, hlen', hd.2⟩
  · exact ⟨hdec, rfl⟩

@[local step]
theorem tail_loop3_spec (input : Slice Std.U8) (out : Slice Std.U32) (n nt p : Std.Usize)
    (hn : n.val = input.length) (hdec : Dec input out nt.val p.val) :
    slot.run_loop3 input out n nt p ⦃ fun r => r.1.val ≤ input.length ∧
      r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
  rw [slot.run_loop3]
  apply Std.loop.spec_decr_nat
    (measure := fun r => n.val - r.2.2.val)
    (inv := fun r => Dec input r.1 r.2.1.val r.2.2.val ∧ r.1.length = out.length)
  · rintro ⟨out', nt', p'⟩ ⟨hdec', hlen'⟩
    simp only at hdec' hlen'
    simp only [slot.run_loop3.body]
    step*
    have hd := Dec.done hdec' (by scalar_tac)
    exact ⟨hd.1, hlen', hd.2⟩
  · exact ⟨hdec, rfl⟩

/-! ## 12. The main loop

`MainInv` = `Dec` + `out` length + `HeadBound head p` + `miss ≤ p`; the measure is `fuel`.
The body is one `step*` pass over the whole iteration (insert, find, lazy loop, backward
merge, `put_match`, insert and stride loops / literal + skip loop); the remaining goals are
the side conditions `step*` cannot see through (`FoundAt.real`, `HeadBound.mono`), a few
arithmetic facts (`ins ≤ end` for the stride loop, no overflow in `ins + TAIL`, the head bound
of the stride loop, the shift `miss >> skip`) and the invariant for the next iteration
(`MainInv.mk'`). The closers are tried from the cheapest failure to the most expensive. -/

theorem numBits_ge : 32 ≤ System.Platform.numBits := by
  rcases System.Platform.numBits_eq with h | h <;> omega

/-- The main loop's invariant: tokens decode to the `p` bytes consumed, `out` keeps its length
    `L`, head entries are at most `p`, and `miss` (literals since the last match) is at most `p`. -/
def MainInv (input : Slice Std.U8) (L : Nat) (out : Slice Std.U32) (nt p : Nat)
    {N : Std.Usize} (head : Array Std.U32 N) (miss : Nat) : Prop :=
  Dec input out nt p ∧ out.length = L ∧ HeadBound head p ∧ miss ≤ p

theorem MainInv.mk' {input : Slice Std.U8} {L : Nat} {out : Slice Std.U32} {nt p m B : Nat}
    {N : Std.Usize} {head : Array Std.U32 N} (hdec : Dec input out nt p) (hlen : out.length = L)
    (hB : HeadBound head B) (hBp : B ≤ p) (hm : m ≤ p) : MainInv input L out nt p head m :=
  ⟨hdec, hlen, HeadBound.mono hB hBp, hm⟩

set_option maxHeartbeats 16000000 in
theorem main_loop_spec {H W : Std.Usize} (input : Slice Std.U8) (out : Slice Std.U32)
    (cls nt p : Std.Usize) (mask : Std.U32) (minl depth lazy skip skcap : Std.Usize)
    (head : Array Std.U32 H) (prev : Array Std.U32 W)
    (lim ins miss fuel : Std.Usize) (L : Nat)
    (hlim : lim.val + 8 = input.length) (hminl : 3 ≤ minl.val) (hminl8 : minl.val ≤ 8)
    (hskip : skip.val < 32) (hH : 0 < H.val) (hW : 0 < W.val)
    (hinv : MainInv input L out nt.val p.val head miss.val) :
    slot.run_loop0 input out cls nt p mask minl depth lazy skip skcap head prev lim ins miss
      fuel ⦃ fun r => Dec input r.1 r.2.1.val r.2.2.val ∧ r.1.length = L ⦄ := by
  rw [slot.run_loop0]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  apply Std.loop.spec_decr_nat
    (measure := fun r => r.2.2.2.2.2.2.2.val)
    (inv := fun r => MainInv input L r.1 r.2.1.val r.2.2.1.val r.2.2.2.1 r.2.2.2.2.2.2.1.val)
  · rintro ⟨out, nt, p, head, prev, ins, miss, fuel⟩ hinv
    simp only at hinv
    have hinv' := hinv
    obtain ⟨hdec, hL, hB, hmiss⟩ := hinv'
    simp only [slot.run_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals first
      | exact FoundAt.real (by assumption) (by scalar_tac)
      | exact HeadBound.mono (by assumption) (by scalar_tac)
      | (refine ⟨MainInv.mk' (by assumption) (by scalar_tac) (by assumption) (by scalar_tac)
          (by scalar_tac), by scalar_tac⟩)
      | (have := numBits_ge; scalar_tac)
  · exact hinv

/-- The main loop, ghost-free: starts from `Dec`, a head bound and `miss ≤ p`. -/
@[local step]
theorem main_loop_spec' {H W : Std.Usize} (input : Slice Std.U8) (out : Slice Std.U32)
    (cls nt p : Std.Usize) (mask : Std.U32) (minl depth lazy skip skcap : Std.Usize)
    (head : Array Std.U32 H) (prev : Array Std.U32 W)
    (lim ins miss fuel : Std.Usize)
    (hlim : lim.val + 8 = input.length) (hminl : 3 ≤ minl.val) (hminl8 : minl.val ≤ 8)
    (hskip : skip.val < 32) (hH : 0 < H.val) (hW : 0 < W.val)
    (hdec : Dec input out nt.val p.val) (hB : HeadBound head p.val)
    (hmiss : miss.val ≤ p.val) :
    slot.run_loop0 input out cls nt p mask minl depth lazy skip skcap head prev lim ins miss
      fuel ⦃ fun r => Dec input r.1 r.2.1.val r.2.2.val ∧ r.1.length = out.length ⦄ :=
  main_loop_spec input out cls nt p mask minl depth lazy skip skcap head prev lim ins miss fuel
    out.length hlim hminl hminl8 hskip hH hW ⟨hdec, rfl, hB, hmiss⟩

/-! ## 13. `sniff`: total (the counts stay below 4098)

The sampling loop stops at 4097 samples (`tot < 4097`, never reached: at most 4095), so every
count and every sum of counts (`dna`, `text`, `high`, `words`, `syms`, `digits`) fits in `u32`;
the class tests divide by `SDIG ≥ 1`. -/

/-- Every count is at most `T`. -/
def CntBound (cnt : Array Std.U32 256#usize) (T : Nat) : Prop :=
  ∀ j : Nat, j < 256 → (cnt.val[j]!).val ≤ T

theorem CntBound.init : CntBound (Std.Array.repeat 256#usize 0#u32) 0 := by
  intro j hj
  rw [Std.Array.repeat_val, List.getElem!_eq_getElem?_getD,
    List.getElem?_replicate_of_lt (by simpa using hj)]
  rfl

theorem CntBound.get {cnt : Array Std.U32 256#usize} {T : Nat} (h : CntBound cnt T)
    (a : Std.Usize) (x : Std.U32) (ha : a.val < cnt.val.length) (hx : x = cnt.val[a.val]) :
    x.val ≤ T := by
  have := h a.val (by simpa using ha)
  rw [getElem!_pos cnt.val a.val ha, ← hx] at this
  exact this

@[local step]
theorem cnt_index_spec (cnt : Array Std.U32 256#usize) (T : Nat) (h : CntBound cnt T)
    (i : Std.Usize) (hi : i.val < 256) :
    Std.Array.index_usize cnt i ⦃ fun x => x = cnt.val[i.val]! ∧ x.val ≤ T ⦄ := by
  have hl : i.val < cnt.val.length := by simp; omega
  have := Std.Array.index_usize_spec cnt i (by simpa using hl)
  apply Std.WP.spec_mono this
  intro x hx
  refine ⟨by rw [getElem!_pos cnt.val i.val hl]; exact hx, CntBound.get h i x hl hx⟩

theorem CntBound.update {cnt : Array Std.U32 256#usize} {T : Nat} (h : CntBound cnt T)
    (a : Std.Usize) (v : Std.U32) (hv : v.val ≤ T + 1) : CntBound (cnt.set a v) (T + 1) := by
  intro j hj
  rw [Std.Array.set_val_eq]
  by_cases hja : a.val = j
  · subst hja
    have hlen : a.val < cnt.val.length := by simp; omega
    rw [List.getElem!_eq_getElem?_getD, List.getElem?_set_self hlen]
    exact hv
  · rw [List.getElem!_eq_getElem?_getD, List.getElem?_set_ne hja, ← List.getElem!_eq_getElem?_getD]
    exact le_trans (h j hj) (by omega)

/-- `cnt[x] += 1` with `cnt[x] ≤ T`, and `tot += 1`. -/
theorem CntBound.step {cnt a : Array Std.U32 256#usize} {T : Nat} {x : Std.Usize}
    {v tot1 : Std.U32} (hc : CntBound cnt T) (ha : a = cnt.set x v) (hv : v.val ≤ T + 1)
    (ht1 : tot1.val = T + 1) : CntBound a tot1.val := by
  rw [ha, ht1]
  exact CntBound.update hc x v hv

theorem CntBound.mono {cnt : Array Std.U32 256#usize} {T T' : Nat} (h : CntBound cnt T)
    (hT : T ≤ T') : CntBound cnt T' := fun j hj => le_trans (h j hj) hT

theorem sniff_loop0_spec (s : Slice Std.U8) (n : Std.Usize) (cnt : Array Std.U32 256#usize)
    (step i : Std.Usize) (tot : Std.U32) (hn : n.val = s.length) (hc : CntBound cnt tot.val)
    (ht : tot.val ≤ 4097) :
    slot.sniff_loop0 s n cnt step i tot ⦃ fun r => CntBound r.1 r.2.val ∧ r.2.val ≤ 4097 ⦄ := by
  rw [slot.sniff_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun r => 4097 - r.2.2.val)
    (inv := fun r => CntBound r.1 r.2.2.val ∧ r.2.2.val ≤ 4097)
  · rintro ⟨cnt, i, tot⟩ ⟨hc, ht⟩
    simp only at hc ht
    simp only [slot.sniff_loop0.body]
    step*
    all_goals first
      | exact ⟨hc, ht⟩
      | exact ⟨CntBound.step hc (by assumption) (by scalar_tac) (by scalar_tac), by scalar_tac,
          by scalar_tac⟩
  · exact ⟨hc, ht⟩

@[local step]
theorem sniff_loop1_spec (cnt : Array Std.U32 256#usize) (text high words : Std.U32) (b : Std.Usize)
    (hc : CntBound cnt 4097) (htext : text.val ≤ (b.val + 3) * 4097)
    (hhigh : high.val ≤ b.val * 4097) (hwords : words.val ≤ (b.val + 1) * 4097)
    (hb : b.val ≤ 256) :
    slot.sniff_loop1 cnt text high words b ⦃ fun _ => True ⦄ := by
  rw [slot.sniff_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun r => 256 - r.2.2.2.val)
    (inv := fun r => r.1.val ≤ (r.2.2.2.val + 3) * 4097 ∧ r.2.1.val ≤ r.2.2.2.val * 4097 ∧
      r.2.2.1.val ≤ (r.2.2.2.val + 1) * 4097 ∧ r.2.2.2.val ≤ 256)
  · rintro ⟨text, high, words, b⟩ ⟨htext, hhigh, hwords, hb⟩
    simp only at htext hhigh hwords hb
    simp only [slot.sniff_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals (refine ⟨?_, ?_, ?_, ?_, ?_⟩ <;> scalar_tac)
  · exact ⟨htext, hhigh, hwords, hb⟩

@[local step]
theorem sniff_spec (s : Slice Std.U8) : slot.sniff s ⦃ fun _ => True ⦄ := by
  rw [slot.sniff]
  step*
  apply Std.WP.spec_bind (sniff_loop0_spec s (Std.Slice.len s) _ step 0#usize 0#u32 (by simp)
    (by simpa using CntBound.init) (by simp))
  rintro ⟨cnt1, tot⟩ ⟨hc, ht⟩
  simp only at hc ht
  step*
  exact CntBound.mono hc ht

/-! ## 14. `run`, `run_rest` and the obligation

`run_spec` holds for every table size `0 < H`, `0 < W` and every class. `run_rest` and `parse`
only choose the class instance and the table sizes (literals in the model), so their proofs
split the `if`s and apply `run_spec`; `(by simp)` proves `0 < H` for the literal. -/

@[local step]
theorem lift_spec {α : Type} (x : α) : lift x ⦃ fun y => y = x ⦄ := by
  simp [lift]

@[local step]
theorem run_spec (H W : Std.Usize) (input : Slice Std.U8) (out : Slice Std.U32) (cls : Std.Usize)
    (hlen : input.length ≤ out.length) (hH : 0 < H.val) (hW : 0 < W.val) :
    slot.run H W input out cls ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧
      LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
  rw [slot.run]
  step*
  repeat' (split <;> step*)
  all_goals first
    | exact Dec.init input out hlen
    | exact HeadBound.init _

theorem run_rest_spec (input : Slice Std.U8) (out : Slice Std.U32) (cls : Std.Usize)
    (hlen : input.length ≤ out.length) :
    slot.run_rest input out cls ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧
      LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
  rw [slot.run_rest]
  split
  · split
    · exact run_spec _ _ input out _ hlen (by simp) (by simp)
    · exact run_spec _ _ input out _ hlen (by simp) (by simp)
  · exact run_spec _ _ input out _ hlen (by simp) (by simp)


namespace Bucket2

@[local step]
theorem insert_spec (s : Slice Std.U8) {H W : Std.Usize} (head : Array Std.U32 H)
    (prev : Array Std.U32 W) (i : Std.Usize) (mask : Std.U32) (B : Nat) (hB : HeadBound head B)
    (hi : i.val < B + 1) (hi4 : i.val + 4 ≤ Std.Usize.max) (hH : 0 < H.val) (hW : 0 < W.val) :
    slot.bucket_insert s head prev i mask ⦃ fun r => r.1.1.val ≤ B ∧ HeadBound r.2.1 B ⦄ := by
  rw [slot.bucket_insert]
  step*
  have hold : old.val ≤ B := HeadBound.get hB a old (by scalar_tac) (by assumption)
  exact ⟨cast_usize_le (by assumption) hold,
    HeadBound.update hB (by assumption) (by omega) (by assumption)⟩

@[local step]
theorem find_spec (s : Slice Std.U8) {W : Std.Usize} (prev : Array Std.U32 W)
    (p : Std.Usize) (st : Std.Usize × Std.Usize) («have» minl depth gm : Std.Usize)
    (hp : p.val ≤ s.length) (hst : st.1.val ≤ p.val) (hhave : p.val + «have».val ≤ s.length)
    (hhave258 : «have».val ≤ 258) (hminl : 1 ≤ minl.val) (hminl' : p.val + minl.val ≤ s.length + 1)
    (hW : 0 < W.val) :
    slot.bucket_find s prev p st «have» minl depth gm ⦃ fun r => FoundAt s p.val r.1.val r.2.val ∧
      r.1.val ≤ 258 ∧ r.2.val ≤ 32768 ⦄ := by
  rcases st with ⟨recent, older⟩
  rw [slot.bucket_find]
  dsimp only
  apply Std.WP.spec_bind (lift_spec (UScalar.cast .U32 older))
  intro older32 _
  exact Submission.find_spec s (Std.Array.repeat 1#usize older32) p recent «have» minl depth gm
    hp hst hhave hhave258 hminl hminl' (by simp)


theorem back_loop_inv (input : Slice Std.U8) (out : Slice Std.U32) (nt p l d back : Std.Usize)
    (E P0 : Nat) (hP0 : P0 + 8 ≤ input.length)
    (hinv : BackInv input out d.val E P0 nt.val p.val l.val) :
    slot.bucket_run_loop0_loop2 input out nt p l d back ⦃ fun r =>
      BackInv input out d.val E P0 r.1.val r.2.1.val r.2.2.val ⦄ := by
  rw [slot.bucket_run_loop0_loop2]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  apply Std.loop.spec_decr_nat
    (measure := fun r => slot.BACKTOK.val - r.2.2.2.val)
    (inv := fun r => BackInv input out d.val E P0 r.1.val r.2.1.val r.2.2.1.val)
  · rintro ⟨nt, p, l, back⟩ hinv
    simp only at hinv
    have hinv' := hinv
    obtain ⟨⟨hps, hntp, hso, _⟩, ⟨h3, h258, hpl, hd1, hd32, hdp, _⟩, hE, hp0⟩ := hinv'
    simp only [slot.bucket_run_loop0_loop2.body]
    step*
    all_goals first
      | (refine ⟨BackInv.lit hinv (by scalar_tac) (by scalar_tac) (by scalar_tac) (by scalar_tac)
          (by assumption) (by assumption) (by scalar_tac) (by scalar_tac) (by assumption)
          (by assumption) (by assumption) (by scalar_tac) (by assumption) (by scalar_tac)
          (by scalar_tac) (by scalar_tac), by scalar_tac⟩)
      | (refine ⟨BackInv.match hinv (by scalar_tac) (by scalar_tac) (by scalar_tac) (by scalar_tac)
          (by assumption) (by assumption) (by assumption) (by scalar_tac) (by scalar_tac)
          (by scalar_tac) (by scalar_tac) (by scalar_tac) (by scalar_tac) (by scalar_tac)
          (by scalar_tac), by scalar_tac⟩)
  · exact hinv

/-- The backward merge, ghost-free: the result is a real match ending where the input one did. -/
@[local step]
theorem back_loop_spec (input : Slice Std.U8) (out : Slice Std.U32) (nt p l d back : Std.Usize)
    (hp8 : p.val + 8 ≤ input.length) (hdec : Dec input out nt.val p.val)
    (hm : MatchAt input p.val l.val d.val) :
    slot.bucket_run_loop0_loop2 input out nt p l d back ⦃ fun r =>
      Dec input out r.1.val r.2.1.val ∧ MatchAt input r.2.1.val r.2.2.val d.val ∧
      r.2.1.val + r.2.2.val = p.val + l.val ∧ r.2.1.val ≤ p.val ⦄ := by
  apply Std.WP.spec_mono (back_loop_inv input out nt p l d back (p.val + l.val) p.val hp8
    ⟨hdec, hm, rfl, le_refl _⟩)
  intro r h
  exact h

/-! ## 10. The lazy step: move to `p + 1` while its match saves more

`LazyInv` = `Dec` + `out` length + `MatchAt` for the pending `(l, d)` at `p` + `HeadBound head
(p + 1)` + `p < lim` + `ins ≤ p + 2`. Accepting writes the literal at `p` and takes the
`FoundAt` match at `p + 1` (`LazyInv.accept`); rejecting only changed the table. -/

/-- The state of the lazy loop: tokens decode to `p` bytes, `out` keeps its length `L`, the
    pending match `(l, d)` at `p` is real, head entries are at most `p + 1`, `p < lim`, and
    the insertion cursor is at most `p + 2`. -/
def LazyInv (input : Slice Std.U8) (L lim : Nat) (out : Slice Std.U32) (nt p : Nat)
    {N : Std.Usize} (head : Array Std.U32 N) (ins l d : Nat) : Prop :=
  Dec input out nt p ∧ out.length = L ∧ MatchAt input p l d ∧ HeadBound head (p + 1) ∧
    p < lim ∧ ins ≤ p + 2

/-- The lazy step moved to `i = p + 1`: the literal at `p` is written, `(l1, d1)` is found at `i`. -/
theorem LazyInv.accept {input : Slice Std.U8} {L lim p' B : Nat} {out1 : Slice Std.U32}
    {nt1 i ins1 l1 d1 minl : Std.Usize} {N : Std.Usize} {head1 : Array Std.U32 N}
    (hdec : Dec input out1 nt1.val p') (hi : i.val = p') (hlen : out1.length = L)
    (hf : FoundAt input i.val l1.val d1.val) (hl1 : minl.val ≤ l1.val) (hminl : 3 ≤ minl.val)
    (hB : HeadBound head1 B) (hBi : B ≤ i.val + 1) (hilim : i.val < lim)
    (hins : ins1.val ≤ i.val + 2) :
    LazyInv input L lim out1 nt1.val i.val head1 ins1.val l1.val d1.val := by
  subst hi
  refine ⟨hdec, hlen, ?_, HeadBound.mono hB hBi, hilim, hins⟩
  rcases hf with h | h
  · omega
  · exact h

/-- The lazy step stays at `p` (only the table changed). -/
theorem LazyInv.reject {input : Slice Std.U8} {L lim : Nat} {out : Slice Std.U32}
    {nt p ins ins1 l d B : Nat} {N : Std.Usize} {head head1 : Array Std.U32 N}
    (h : LazyInv input L lim out nt p head ins l d) (hB : HeadBound head1 B) (hBp : B ≤ p + 1)
    (hins1 : ins1 ≤ p + 2) : LazyInv input L lim out nt p head1 ins1 l d := by
  obtain ⟨hdec, hlen, hm, _, hplim, _⟩ := h
  exact ⟨hdec, hlen, hm, HeadBound.mono hB hBp, hplim, hins1⟩

theorem lazy_loop_inv {H W : Std.Usize} (input : Slice Std.U8) (out : Slice Std.U32)
    (cls nt p : Std.Usize) (mask : Std.U32) (minl lazy : Std.Usize) (head : Array Std.U32 H)
    (prev : Array Std.U32 W) (lim ins l d : Std.Usize) (go : Std.U32) (L : Nat)
    (hlim : lim.val + 8 = input.length) (hminl : 3 ≤ minl.val) (hminl8 : minl.val ≤ 8)
    (hH : 0 < H.val) (hW : 0 < W.val)
    (hinv : LazyInv input L lim.val out nt.val p.val head ins.val l.val d.val) :
    slot.bucket_run_loop0_loop1 input out cls nt p mask minl lazy head prev lim ins l d go ⦃ fun r =>
      LazyInv input L lim.val r.1 r.2.1.val r.2.2.1.val r.2.2.2.1 r.2.2.2.2.2.1.val
        r.2.2.2.2.2.2.1.val r.2.2.2.2.2.2.2.val ⦄ := by
  rw [slot.bucket_run_loop0_loop1]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  apply Std.loop.spec_decr_nat
    (measure := fun r => lim.val - r.2.2.1.val + r.2.2.2.2.2.2.2.2.val)
    (inv := fun r => LazyInv input L lim.val r.1 r.2.1.val r.2.2.1.val r.2.2.2.1
      r.2.2.2.2.2.1.val r.2.2.2.2.2.2.1.val r.2.2.2.2.2.2.2.1.val)
  · rintro ⟨out, nt, p, head, prev, ins, l, d, go⟩ hinv
    simp only at hinv
    have hinv' := hinv
    obtain ⟨⟨hps, hntp, hso, _⟩, hL, ⟨h3, h258, hpl, hd1, hd32, hdp, _⟩, hB, hplim, hins⟩ := hinv'
    simp only [slot.bucket_run_loop0_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals first
      | exact hinv.1
      | (refine ⟨LazyInv.accept (by assumption) (by scalar_tac) (by scalar_tac) (by assumption)
          (by scalar_tac) hminl (by assumption) (by scalar_tac) (by scalar_tac) (by scalar_tac),
          by scalar_tac⟩)
      | (refine ⟨LazyInv.reject hinv (by assumption) (by scalar_tac) (by scalar_tac),
          by scalar_tac⟩)
  · exact hinv

/-- The lazy loop with flat pre- and postconditions (so `step*` can use it inside `run`'s body).
    The pending match ends at `p + l`, which bounds the head entries from then on. -/
@[local step]
theorem lazy_loop_spec {H W : Std.Usize} (input : Slice Std.U8) (out : Slice Std.U32)
    (cls nt p : Std.Usize) (mask : Std.U32) (minl lazy : Std.Usize) (head : Array Std.U32 H)
    (prev : Array Std.U32 W) (lim ins l d : Std.Usize) (go : Std.U32) (L : Nat)
    (hlim : lim.val + 8 = input.length) (hminl : 3 ≤ minl.val) (hminl8 : minl.val ≤ 8)
    (hH : 0 < H.val) (hW : 0 < W.val)
    (hdec : Dec input out nt.val p.val) (hlen : out.length = L)
    (hm : MatchAt input p.val l.val d.val) (hB : HeadBound head (p.val + 1))
    (hplim : p.val < lim.val) (hins : ins.val ≤ p.val + 2) :
    slot.bucket_run_loop0_loop1 input out cls nt p mask minl lazy head prev lim ins l d go ⦃ fun r =>
      Dec input r.1 r.2.1.val r.2.2.1.val ∧ r.1.length = L ∧
      MatchAt input r.2.2.1.val r.2.2.2.2.2.2.1.val r.2.2.2.2.2.2.2.val ∧
      HeadBound r.2.2.2.1 (r.2.2.1.val + r.2.2.2.2.2.2.1.val) ∧ r.2.2.1.val < lim.val ∧
      r.2.2.2.2.2.1.val ≤ r.2.2.1.val + 2 ∧ 3 ≤ r.2.2.2.2.2.2.1.val ⦄ := by
  apply Std.WP.spec_mono (lazy_loop_inv input out cls nt p mask minl lazy head prev lim ins l d go L
    hlim hminl hminl8 hH hW ⟨hdec, hlen, hm, hB, hplim, hins⟩)
  rintro ⟨out', nt', p', head', prev', ins', l', d'⟩ ⟨hdec', hlen', hm', hB', hplim', hins'⟩
  exact ⟨hdec', hlen', hm', HeadBound.mono hB' (by have := hm'.1; omega), hplim', hins', hm'.1⟩

/-! ## 11. The insert loops and the literal loops of `run`

Every insert loop keeps `HeadBound head B` for the bound `B` its caller picks (`p` before the
search, the match end `p + l` after a match): each inserted position is `< B + 1`. Inside a
match, loop 3 records the first positions (up to the `INS_MAX` cap and `lim`), the stride loop
every `STRIDE`-th position while `end - ins > TAIL + STRIDE` (only under `if STRIDE > 0`, which
gives the measure `end - ins`), and loops 5 and 6 (the two copies of the tail loop, one per
branch of `if STRIDE > 0`) the last `TAIL` positions. Loop 7 writes the skipped literals. -/

@[local step]
theorem ins_loop0_spec {H W : Std.Usize} (input : Slice Std.U8) (p : Std.Usize) (mask : Std.U32)
    (head : Array Std.U32 H) (prev : Array Std.U32 W) (ins : Std.Usize) (B : Nat)
    (hB : HeadBound head B) (hpB : p.val < B + 1) (hp4 : p.val + 4 ≤ Std.Usize.max)
    (hH : 0 < H.val) (hW : 0 < W.val) :
    slot.bucket_run_loop0_loop0 input p mask head prev ins ⦃ fun r => HeadBound r.1 B ⦄ := by
  rw [slot.bucket_run_loop0_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun r => p.val - r.2.2.val)
    (inv := fun r => HeadBound r.1 B)
  · rintro ⟨head, prev, ins⟩ hB
    simp only at hB
    simp only [slot.bucket_run_loop0_loop0.body]
    step*
  · exact hB

@[local step]
theorem ins_loop3_spec {H W : Std.Usize} (input : Slice Std.U8) (mask : Std.U32)
    (head : Array Std.U32 H) (prev : Array Std.U32 W) (ins stop : Std.Usize) (B : Nat)
    (hB : HeadBound head B) (hsB : stop.val < B + 1) (hs4 : stop.val + 4 ≤ Std.Usize.max)
    (hH : 0 < H.val) (hW : 0 < W.val) :
    slot.bucket_run_loop0_loop3 input mask head prev ins stop ⦃ fun r =>
      HeadBound r.1 B ∧ (r.2.2.val ≤ ins.val ∨ r.2.2.val ≤ stop.val) ⦄ := by
  rw [slot.bucket_run_loop0_loop3]
  apply Std.loop.spec_decr_nat
    (measure := fun r => stop.val - r.2.2.val)
    (inv := fun r => HeadBound r.1 B ∧ (r.2.2.val ≤ ins.val ∨ r.2.2.val ≤ stop.val))
  · rintro ⟨head, prev, ins'⟩ ⟨hB, hins⟩
    simp only at hB hins
    simp only [slot.bucket_run_loop0_loop3.body]
    step*
  · exact ⟨hB, Or.inl (le_refl _)⟩

/-- Sparse recording inside a long match: positions `ins, ins + STRIDE, ...` while
    `end - ins > TAIL + STRIDE` (so `ins + STRIDE + TAIL < end` after each step). -/
@[local step]
theorem stride_loop_spec {H W : Std.Usize} (input : Slice Std.U8) (mask : Std.U32)
    (head : Array Std.U32 H) (prev : Array Std.U32 W) (lim ins «end» : Std.Usize) (B : Nat)
    (hB : HeadBound head B) (heB : «end».val < B + 1) (hl4 : lim.val + 4 ≤ Std.Usize.max)
    (hH : 0 < H.val) (hW : 0 < W.val) (hS : 0 < slot.STRIDE.val)
    (hie : ins.val ≤ «end».val) :
    slot.bucket_run_loop0_loop4 input mask head prev lim ins «end» ⦃ fun r =>
      HeadBound r.1 B ∧ r.2.2.val ≤ «end».val ∧
        (r.2.2.val ≤ ins.val ∨ r.2.2.val + slot.TAIL.val < «end».val) ⦄ := by
  rw [slot.bucket_run_loop0_loop4]
  apply Std.loop.spec_decr_nat
    (measure := fun r => «end».val - r.2.2.val)
    (inv := fun r => HeadBound r.1 B ∧ r.2.2.val ≤ «end».val ∧
      (r.2.2.val ≤ ins.val ∨ r.2.2.val + slot.TAIL.val < «end».val))
  · rintro ⟨head, prev, ins'⟩ ⟨hB, hie', hins⟩
    simp only at hB hie' hins
    simp only [slot.bucket_run_loop0_loop4.body]
    step*
    all_goals first
      | exact ⟨hB, hie', hins⟩
      | exact ⟨by assumption, by scalar_tac, by scalar_tac, by scalar_tac⟩
  · exact ⟨hB, hie, Or.inl (le_refl _)⟩

@[local step]
theorem ins_loop5_spec {H W : Std.Usize} (input : Slice Std.U8) (mask : Std.U32)
    (head : Array Std.U32 H) (prev : Array Std.U32 W) (lim ins «end» : Std.Usize) (B : Nat)
    (hB : HeadBound head B) (heB : «end».val < B + 1) (hl4 : lim.val + 4 ≤ Std.Usize.max)
    (hH : 0 < H.val) (hW : 0 < W.val) :
    slot.bucket_run_loop0_loop5 input mask head prev lim ins «end» ⦃ fun r =>
      HeadBound r.1 B ∧ (r.2.2.val ≤ ins.val ∨ r.2.2.val ≤ «end».val) ⦄ := by
  rw [slot.bucket_run_loop0_loop5]
  apply Std.loop.spec_decr_nat
    (measure := fun r => «end».val - r.2.2.val)
    (inv := fun r => HeadBound r.1 B ∧ (r.2.2.val ≤ ins.val ∨ r.2.2.val ≤ «end».val))
  · rintro ⟨head, prev, ins'⟩ ⟨hB, hins⟩
    simp only at hB hins
    simp only [slot.bucket_run_loop0_loop5.body]
    step*
  · exact ⟨hB, Or.inl (le_refl _)⟩

@[local step]
theorem ins_loop6_spec {H W : Std.Usize} (input : Slice Std.U8) (mask : Std.U32)
    (head : Array Std.U32 H) (prev : Array Std.U32 W) (lim ins «end» : Std.Usize) (B : Nat)
    (hB : HeadBound head B) (heB : «end».val < B + 1) (hl4 : lim.val + 4 ≤ Std.Usize.max)
    (hH : 0 < H.val) (hW : 0 < W.val) :
    slot.bucket_run_loop0_loop6 input mask head prev lim ins «end» ⦃ fun r =>
      HeadBound r.1 B ∧ (r.2.2.val ≤ ins.val ∨ r.2.2.val ≤ «end».val) ⦄ := by
  rw [slot.bucket_run_loop0_loop6]
  apply Std.loop.spec_decr_nat
    (measure := fun r => «end».val - r.2.2.val)
    (inv := fun r => HeadBound r.1 B ∧ (r.2.2.val ≤ ins.val ∨ r.2.2.val ≤ «end».val))
  · rintro ⟨head, prev, ins'⟩ ⟨hB, hins⟩
    simp only at hB hins
    simp only [slot.bucket_run_loop0_loop6.body]
    step*
  · exact ⟨hB, Or.inl (le_refl _)⟩

@[local step]
theorem skip_loop_spec (input : Slice Std.U8) (out : Slice Std.U32) (nt p lim step : Std.Usize)
    (hdec : Dec input out nt.val p.val) (hlim : lim.val ≤ input.length) :
    slot.bucket_run_loop0_loop7 input out nt p lim step ⦃ fun r =>
      Dec input r.1 r.2.1.val r.2.2.val ∧ r.1.length = out.length ∧ p.val ≤ r.2.2.val ⦄ := by
  rw [slot.bucket_run_loop0_loop7]
  apply Std.loop.spec_decr_nat
    (measure := fun r => r.2.2.2.val)
    (inv := fun r => Dec input r.1 r.2.1.val r.2.2.1.val ∧ r.1.length = out.length ∧
      p.val ≤ r.2.2.1.val)
  · rintro ⟨out', nt', p', step'⟩ ⟨hdec', hlen', hp'⟩
    simp only at hdec' hlen' hp'
    simp only [slot.bucket_run_loop0_loop7.body]
    step*
  · exact ⟨hdec, rfl, le_refl _⟩

@[local step]
theorem tail_loop1_spec (input : Slice Std.U8) (out : Slice Std.U32) (n nt p : Std.Usize)
    (hn : n.val = input.length) (hdec : Dec input out nt.val p.val) :
    slot.bucket_run_loop1 input out n nt p ⦃ fun r => r.1.val ≤ input.length ∧
      r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
  rw [slot.bucket_run_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun r => n.val - r.2.2.val)
    (inv := fun r => Dec input r.1 r.2.1.val r.2.2.val ∧ r.1.length = out.length)
  · rintro ⟨out', nt', p'⟩ ⟨hdec', hlen'⟩
    simp only at hdec' hlen'
    simp only [slot.bucket_run_loop1.body]
    step*
    have hd := Dec.done hdec' (by scalar_tac)
    exact ⟨hd.1, hlen', hd.2⟩
  · exact ⟨hdec, rfl⟩

@[local step]
theorem tail_loop2_spec (input : Slice Std.U8) (out : Slice Std.U32) (n nt p : Std.Usize)
    (hn : n.val = input.length) (hdec : Dec input out nt.val p.val) :
    slot.bucket_run_loop2 input out n nt p ⦃ fun r => r.1.val ≤ input.length ∧
      r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
  rw [slot.bucket_run_loop2]
  apply Std.loop.spec_decr_nat
    (measure := fun r => n.val - r.2.2.val)
    (inv := fun r => Dec input r.1 r.2.1.val r.2.2.val ∧ r.1.length = out.length)
  · rintro ⟨out', nt', p'⟩ ⟨hdec', hlen'⟩
    simp only at hdec' hlen'
    simp only [slot.bucket_run_loop2.body]
    step*
    have hd := Dec.done hdec' (by scalar_tac)
    exact ⟨hd.1, hlen', hd.2⟩
  · exact ⟨hdec, rfl⟩

@[local step]
theorem tail_loop3_spec (input : Slice Std.U8) (out : Slice Std.U32) (n nt p : Std.Usize)
    (hn : n.val = input.length) (hdec : Dec input out nt.val p.val) :
    slot.bucket_run_loop3 input out n nt p ⦃ fun r => r.1.val ≤ input.length ∧
      r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
  rw [slot.bucket_run_loop3]
  apply Std.loop.spec_decr_nat
    (measure := fun r => n.val - r.2.2.val)
    (inv := fun r => Dec input r.1 r.2.1.val r.2.2.val ∧ r.1.length = out.length)
  · rintro ⟨out', nt', p'⟩ ⟨hdec', hlen'⟩
    simp only at hdec' hlen'
    simp only [slot.bucket_run_loop3.body]
    step*
    have hd := Dec.done hdec' (by scalar_tac)
    exact ⟨hd.1, hlen', hd.2⟩
  · exact ⟨hdec, rfl⟩

/-! ## 12. The main loop

`MainInv` = `Dec` + `out` length + `HeadBound head p` + `miss ≤ p`; the measure is `fuel`.
The body is one `step*` pass over the whole iteration (insert, find, lazy loop, backward
merge, `put_match`, insert and stride loops / literal + skip loop); the remaining goals are
the side conditions `step*` cannot see through (`FoundAt.real`, `HeadBound.mono`), a few
arithmetic facts (`ins ≤ end` for the stride loop, no overflow in `ins + TAIL`, the head bound
of the stride loop, the shift `miss >> skip`) and the invariant for the next iteration
(`MainInv.mk'`). The closers are tried from the cheapest failure to the most expensive. -/

theorem numBits_ge : 32 ≤ System.Platform.numBits := by
  rcases System.Platform.numBits_eq with h | h <;> omega

/-- The main loop's invariant: tokens decode to the `p` bytes consumed, `out` keeps its length
    `L`, head entries are at most `p`, and `miss` (literals since the last match) is at most `p`. -/
def MainInv (input : Slice Std.U8) (L : Nat) (out : Slice Std.U32) (nt p : Nat)
    {N : Std.Usize} (head : Array Std.U32 N) (miss : Nat) : Prop :=
  Dec input out nt p ∧ out.length = L ∧ HeadBound head p ∧ miss ≤ p

theorem MainInv.mk' {input : Slice Std.U8} {L : Nat} {out : Slice Std.U32} {nt p m B : Nat}
    {N : Std.Usize} {head : Array Std.U32 N} (hdec : Dec input out nt p) (hlen : out.length = L)
    (hB : HeadBound head B) (hBp : B ≤ p) (hm : m ≤ p) : MainInv input L out nt p head m :=
  ⟨hdec, hlen, HeadBound.mono hB hBp, hm⟩

set_option maxHeartbeats 16000000 in
theorem main_loop_spec {H W : Std.Usize} (input : Slice Std.U8) (out : Slice Std.U32)
    (cls nt p : Std.Usize) (mask : Std.U32) (minl depth lazy skip skcap : Std.Usize)
    (head : Array Std.U32 H) (prev : Array Std.U32 W)
    (lim ins miss fuel : Std.Usize) (L : Nat)
    (hlim : lim.val + 8 = input.length) (hminl : 3 ≤ minl.val) (hminl8 : minl.val ≤ 8)
    (hskip : skip.val < 32) (hH : 0 < H.val) (hW : 0 < W.val)
    (hinv : MainInv input L out nt.val p.val head miss.val) :
    slot.bucket_run_loop0 input out cls nt p mask minl depth lazy skip skcap head prev lim ins miss
      fuel ⦃ fun r => Dec input r.1 r.2.1.val r.2.2.val ∧ r.1.length = L ⦄ := by
  rw [slot.bucket_run_loop0]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  apply Std.loop.spec_decr_nat
    (measure := fun r => r.2.2.2.2.2.2.2.val)
    (inv := fun r => MainInv input L r.1 r.2.1.val r.2.2.1.val r.2.2.2.1 r.2.2.2.2.2.2.1.val)
  · rintro ⟨out, nt, p, head, prev, ins, miss, fuel⟩ hinv
    simp only at hinv
    have hinv' := hinv
    obtain ⟨hdec, hL, hB, hmiss⟩ := hinv'
    simp only [slot.bucket_run_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals first
      | exact FoundAt.real (by assumption) (by scalar_tac)
      | exact HeadBound.mono (by assumption) (by scalar_tac)
      | (refine ⟨MainInv.mk' (by assumption) (by scalar_tac) (by assumption) (by scalar_tac)
          (by scalar_tac), by scalar_tac⟩)
      | (have := numBits_ge; scalar_tac)
  · exact hinv

/-- The main loop, ghost-free: starts from `Dec`, a head bound and `miss ≤ p`. -/
@[local step]
theorem main_loop_spec' {H W : Std.Usize} (input : Slice Std.U8) (out : Slice Std.U32)
    (cls nt p : Std.Usize) (mask : Std.U32) (minl depth lazy skip skcap : Std.Usize)
    (head : Array Std.U32 H) (prev : Array Std.U32 W)
    (lim ins miss fuel : Std.Usize)
    (hlim : lim.val + 8 = input.length) (hminl : 3 ≤ minl.val) (hminl8 : minl.val ≤ 8)
    (hskip : skip.val < 32) (hH : 0 < H.val) (hW : 0 < W.val)
    (hdec : Dec input out nt.val p.val) (hB : HeadBound head p.val)
    (hmiss : miss.val ≤ p.val) :
    slot.bucket_run_loop0 input out cls nt p mask minl depth lazy skip skcap head prev lim ins miss
      fuel ⦃ fun r => Dec input r.1 r.2.1.val r.2.2.val ∧ r.1.length = out.length ⦄ :=
  main_loop_spec input out cls nt p mask minl depth lazy skip skcap head prev lim ins miss fuel
    out.length hlim hminl hminl8 hskip hH hW ⟨hdec, rfl, hB, hmiss⟩

@[local step]
theorem run_spec (H W : Std.Usize) (input : Slice Std.U8) (out : Slice Std.U32) (cls : Std.Usize)
    (hlen : input.length ≤ out.length) (hH : 0 < H.val) (hW : 0 < W.val) :
    slot.bucket_run H W input out cls ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧
      LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
  rw [slot.bucket_run]
  step*
  repeat' (split <;> step*)
  all_goals first
    | exact Dec.init input out hlen
    | exact HeadBound.init _

end Bucket2

/-! ## 15. The obligation

Tiny inputs that `tf_route` sends to the plan + re-verify path (kind < 3): the planner is total
(`tf_plan_spec`, section 0c) and the emission decodes to the input for any plan (`emit_spec`,
section 0a). Every other input: fx17's proof unchanged (`sniff_spec`, then the class instances and
table sizes of `parse` through `run_spec` / `run_rest_spec`). -/

theorem parse_spec (input : Slice Std.U8) (out : Slice Std.U32)
    (hlen : input.length ≤ out.length) :
    slot.parse input out ⦃ fun r =>
      r.1.val ≤ input.length ∧
      r.2.length = out.length ∧
      LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
  rw [slot.parse]
  apply Std.WP.spec_bind (tf_route_spec input)
  intro kind _
  split
  · apply Std.WP.spec_bind (tf_plan_spec input kind)
    intro plan _
    apply Std.WP.spec_mono (emit_spec input _ out hlen)
    rintro r ⟨h1, h2, h3⟩
    exact ⟨h1, h2, h3⟩
  · apply Std.WP.spec_bind (sniff_spec input)
    intro cls _
    repeat' ((try dsimp only); split)
    all_goals first
      | exact Bucket2.run_spec _ _ input out _ hlen (by simp) (by simp)
      | exact run_spec _ _ input out _ hlen (by simp) (by simp)
      | exact run_rest_spec input out _ hlen

end Submission
