import Lz77
import Slot
set_option linter.unusedTactic false
set_option linter.unreachableTactic false
namespace Submission
open Aeneas Aeneas.Std Result ControlFlow
open LZ77 (toks bytes)
set_option maxRecDepth 8192
namespace E_M
open Aeneas Aeneas.Std Result ControlFlow
set_option maxRecDepth 8192
set_option maxHeartbeats 4000000
set_option linter.unusedVariables false
open LZ77 (toks bytes bytes_length bytes_getElem! toks_update bytes_congr
  Matches Found emit_lit emit_match ite_ok)
open LZ77 (decode emit copyN tokLen tokDist MATCH_BASE TOK_LIMIT decode_snoc copyN_length)
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
theorem leadingZeros_lt_of_ne (z : BitVec 64) (h : z ≠ 0) : BitVec.leadingZeros z < 64 := by
  unfold BitVec.leadingZeros
  simp only [h, if_false]
  omega
@[local step]
theorem lz_spec (x : Std.U64) :
    lift (core.num.U64.leading_zeros x) ⦃ fun r => r = core.num.U64.leading_zeros x ∧ r.val ≤ 64 ⦄ := by
  simp only [lift, Std.WP.spec_ok, true_and]
  have hle : BitVec.leadingZeros x.bv ≤ 64 := by unfold BitVec.leadingZeros; split <;> omega
  simp only [core.num.U64.leading_zeros, UScalar.val, UScalarTy.U32_numBits_eq,
    BitVec.natCast_eq_ofNat, BitVec.toNat_ofNat, Nat.reducePow]
  omega
theorem lz_val (x : Std.U64) :
    (core.num.U64.leading_zeros x).val = BitVec.leadingZeros x.bv := by
  have hle : BitVec.leadingZeros x.bv ≤ 64 := by unfold BitVec.leadingZeros; split <;> omega
  simp only [core.num.U64.leading_zeros, UScalar.val, UScalarTy.U32_numBits_eq,
    BitVec.natCast_eq_ofNat, BitVec.toNat_ofNat, Nat.reducePow]
  omega
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
@[local step]
theorem common_spec (s : Slice Std.U8) (a b cap : Std.Usize)
    (ha : a.val + cap.val ≤ s.length) (hb : b.val + cap.val ≤ s.length) (hcap : cap.val ≤ 258) :
    slot.common s a b cap ⦃ fun l => l.val ≤ cap.val ∧ Matches s a.val b.val l.val ⦄ := by
  rw [slot.common]
  apply Std.WP.spec_bind (common_loop0_spec s a b cap 0#usize 1#u32 ha hb hcap (by simp)
    (LZ77.Matches.zero s a.val b.val))
  rintro ⟨k, run⟩ ⟨hk, hm⟩
  exact common_loop1_spec s a b cap k run ha hb hk hm
theorem Matches.mono_eq {input : Slice Std.U8} {a b n m : Nat} (h : Matches input a b n)
    (hm : m = n) : Matches input a b m := by subst hm; exact h
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
  intro _
  exact Matches.mask hm (by assumption) (by assumption) (by assumption) (by assumption)
    (by assumption) (by assumption) (by assumption) (by scalar_tac) (by scalar_tac)
    (by scalar_tac)
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
@[local step]
theorem hcast_I32_spec {ty : UScalarTy} (x : UScalar ty) (h : x.val ≤ 2147483647) :
    lift (UScalar.hcast .I32 x) ⦃ fun y => y.val = x.val ⦄ :=
  UScalar.hcast_inBounds_spec .I32 x (by simp [I32.max_def, I32.numBits]; omega)
theorem hcast_I32_val {ty : UScalarTy} (x : UScalar ty) (h : x.val ≤ 2147483647) :
    (UScalar.hcast .I32 x).val = x.val := by
  have := hcast_I32_spec x h
  simpa [lift] using this
theorem GBASE_bound : -500000000 ≤ slot.GBASE.val ∧ slot.GBASE.val ≤ 500000000 := by
  unfold slot.GBASE
  simp
theorem L2B_bound : -500000000 ≤ slot.L2B.val ∧ slot.L2B.val ≤ 500000000 := by
  unfold slot.L2B
  simp
theorem prod_bound {i hlit : Int} {l : Nat} (hi : i = (l : Int)) (hl : l ≤ 258) (h0 : 0 ≤ hlit)
    (h1 : hlit ≤ 1000000) : 0 ≤ i * hlit ∧ i * hlit ≤ 258000000 := by
  subst hi
  refine ⟨Int.mul_nonneg (by omega) h0, ?_⟩
  calc (l : Int) * hlit ≤ 258 * hlit := Int.mul_le_mul_of_nonneg_right (by omega) h0
    _ ≤ 258000000 := by omega
@[local step]
theorem gain_spec (l d : Std.Usize) (hlit : Std.I32) (hl : l.val ≤ 258) (hd : d.val ≤ 32768)
    (hh0 : 0 ≤ hlit.val) (hh1 : hlit.val ≤ 1000000) :
    slot.gain l d hlit ⦃ fun r => -1000000000 ≤ r.val ∧ r.val ≤ 1000000000 ⦄ := by
  rw [slot.gain]
  have ⟨hG0, hG1⟩ := GBASE_bound
  repeat' (split <;> step*)
  all_goals first
    | scalar_tac
    | (have := prod_bound (by assumption) hl hh0 hh1; scalar_tac)
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
@[local step]
theorem insert_dna_spec (s : Slice Std.U8) {H W : Std.Usize} (head : Array Std.U32 H)
    (prev : Array Std.U32 W) (i : Std.Usize) (mask : Std.U32) (B : Nat) (hB : HeadBound head B)
    (hi : i.val < B + 1) (hi8 : i.val + 8 ≤ s.length) (hH : 0 < H.val) (hW : 0 < W.val) :
    slot.insert_dna s head prev i mask ⦃ fun r => r.1.val ≤ B ∧ HeadBound r.2.1 B ⦄ := by
  rw [slot.insert_dna]
  step*
  have hold : old.val ≤ B := HeadBound.get hB a old (by scalar_tac) (by assumption)
  exact ⟨cast_usize_le (by assumption) hold,
    HeadBound.update hB (by assumption) (by omega) (by assumption)⟩
def Cand (s : Slice Std.U8) (p cap best bd : Nat) : Prop :=
  bd = 0 ∨ (1 ≤ bd ∧ bd ≤ 32768 ∧ bd ≤ p ∧ best ≤ cap ∧ Matches s (p - bd) p best)
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
theorem Cand.of_common {s : Slice Std.U8} {p c d i l cap : Std.Usize} (hc : c.val ≤ p.val)
    (hd : d = core.num.Usize.wrapping_sub p c) (hi : i = core.num.Usize.wrapping_sub d 1#usize)
    (hlt : i < 32768#usize) (hl : l.val ≤ cap.val) (hm : Matches s c.val p.val l.val) :
    Cand s p.val cap.val l.val d.val := by
  obtain ⟨hdv, hd1, hd2⟩ := dist_of_wrapping hc hd hi hlt
  refine Or.inr ⟨hd1, hd2, by omega, hl, ?_⟩
  rw [show p.val - d.val = c.val by omega]
  exact hm
theorem dist_of_wrapping2 {p c d i : Std.Usize} (hc : c.val ≤ p.val + 2)
    (hd : d = core.num.Usize.wrapping_sub p c) (hi : i = core.num.Usize.wrapping_sub d 1#usize)
    (hlt : i < 32768#usize) : c.val ≤ p.val := by
  by_contra hcp
  have hsz : 4294967296 ≤ Usize.size := by scalar_tac
  have hcl : c.val < Usize.size := by scalar_tac
  have hdv : d.val = Usize.size - (c.val - p.val) := by
    rw [hd, core.num.Usize.wrapping_sub_val_eq, UScalar.size_UScalarTyUsize]
    rw [show p.val + (Usize.size - c.val) = Usize.size - (c.val - p.val) by omega,
      Nat.mod_eq_of_lt (by omega)]
  have hiv : i.val < 32768 := by scalar_tac
  rw [hi, core.num.Usize.wrapping_sub_val_eq, UScalar.size_UScalarTyUsize] at hiv
  simp only [show (1#usize).val = 1 by simp] at hiv
  rw [show d.val + (Usize.size - 1) = (d.val - 1) + Usize.size by omega, Nat.add_mod_right,
    Nat.mod_eq_of_lt (by omega)] at hiv
  omega
theorem walk_loop_spec (s : Slice Std.U8) {W : Std.Usize} (prev : Array Std.U32 W)
    (p cap gm : Std.Usize) (hlit : Std.I32) (n best bd : Std.Usize) (bg : Std.I32)
    (c k stop : Std.Usize) (pb : Std.U8)
    (hn : n.val = s.length) (hcap : p.val + cap.val ≤ s.length) (hcap258 : cap.val ≤ 258)
    (hc : c.val ≤ p.val + 2) (hbest : p.val + best.val ≤ s.length)
    (hcand : Cand s p.val cap.val best.val bd.val) (hW : 0 < W.val)
    (hh0 : 0 ≤ hlit.val) (hh1 : hlit.val ≤ 1000000) :
    slot.walk_loop s prev p cap gm hlit n best bd bg c k stop pb ⦃ fun r =>
      p.val + r.1.val ≤ s.length ∧ Cand s p.val cap.val r.1.val r.2.val ⦄ := by
  rw [slot.walk_loop]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  apply Std.loop.spec_decr_nat
    (measure := fun r => r.2.2.2.2.1.val)
    (inv := fun r => r.2.2.2.1.val ≤ p.val + 2 ∧ p.val + r.1.val ≤ s.length ∧
      Cand s p.val cap.val r.1.val r.2.1.val)
  · rintro ⟨best, bd, bg, c, k, pb⟩ ⟨hc, hbest, hcand⟩
    simp only at hc hbest hcand
    simp only [slot.walk_loop.body]
    split
    · step
      step
      split
      · have hcp := dist_of_wrapping2 hc (by assumption) (by assumption) (by assumption)
        step*
        repeat' (split <;> step*)
        all_goals first
          | exact (dist_of_wrapping hcp (by assumption) (by assumption) (by assumption)).2.2
          | (refine ⟨by scalar_tac, by scalar_tac, Cand.of_common hcp (by assumption)
              (by assumption) (by assumption) (by assumption) (by assumption), by scalar_tac⟩)
      · step*
    · step*
  · exact ⟨hc, hbest, hcand⟩
@[local step]
theorem walk_spec (s : Slice Std.U8) {W : Std.Usize} (prev : Array Std.U32 W)
    (p start cap «have» depth nice gm : Std.Usize) (hlit : Std.I32)
    (hcap : p.val + cap.val ≤ s.length) (hcap258 : cap.val ≤ 258) (hst : start.val ≤ p.val + 2)
    (hhave : p.val + «have».val ≤ s.length) (hW : 0 < W.val)
    (hh0 : 0 ≤ hlit.val) (hh1 : hlit.val ≤ 1000000) :
    slot.walk s prev p start cap «have» depth nice gm hlit ⦃ fun r =>
      p.val + r.1.val ≤ s.length ∧ Cand s p.val cap.val r.1.val r.2.val ⦄ := by
  rw [slot.walk]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  repeat' (split <;> step*)
  all_goals
    exact walk_loop_spec s prev p cap gm hlit (Std.Slice.len s) «have» 0#usize _ start depth _ _
      (by simp) hcap hcap258 hst hhave (Or.inl rfl) hW hh0 hh1
def MatchAt (s : Slice Std.U8) (p l d : Nat) : Prop :=
  3 ≤ l ∧ l ≤ 258 ∧ p + l ≤ s.length ∧ 1 ≤ d ∧ d ≤ 32768 ∧ d ≤ p ∧ Matches s (p - d) p l
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
    (p st «have» minl depth nice gm : Std.Usize) (hlit : Std.I32)
    (hp : p.val ≤ s.length) (hst : st.val ≤ p.val + 2) (hhave : p.val + «have».val ≤ s.length)
    (hhave258 : «have».val ≤ 258) (hminl : 1 ≤ minl.val) (hminl' : p.val + minl.val ≤ s.length + 1)
    (hW : 0 < W.val) (hh0 : 0 ≤ hlit.val) (hh1 : hlit.val ≤ 1000000) :
    slot.find s prev p st «have» minl depth nice gm hlit ⦃ fun r => FoundAt s p.val r.1.val r.2.val ∧
      r.1.val ≤ 258 ∧ r.2.val ≤ 32768 ⦄ := by
  rw [slot.find]
  step*
  repeat' (split <;> step*)
  all_goals first
    | exact ⟨FoundAt.none s p.val, by simp, by simp⟩
    | exact ⟨FoundAt.of_cand (by assumption) (by assumption) (by scalar_tac) (by assumption),
        Cand.len_le (by assumption) (by assumption) (by scalar_tac),
        Cand.dist_le (by assumption)⟩
def Near (s : Slice Std.U8) (p len r : Nat) : Prop :=
  r = 0 ∨ (1 ≤ r ∧ r ≤ 32768 ∧ r ≤ p ∧ Matches s (p - r) p len)
theorem Near.none (s : Slice Std.U8) (p len : Nat) : Near s p len (0#usize).val := Or.inl (by simp)
theorem Near.found {s : Slice Std.U8} {p c d i len r : Std.Usize} (hc : c.val < p.val)
    (hd : d = core.num.Usize.wrapping_sub p c) (hi : i = core.num.Usize.wrapping_sub d 1#usize)
    (hlt : i < 32768#usize) (hsame : r.val = 1 → Matches s c.val p.val len.val)
    (hr : r = 1#usize) : Near s p.val len.val d.val := by
  obtain ⟨hdv, hd1, hd2⟩ := dist_of_wrapping (le_of_lt hc) hd hi hlt
  refine Or.inr ⟨hd1, hd2, by omega, ?_⟩
  rw [show p.val - d.val = c.val by omega]
  exact hsame (by rw [hr]; rfl)
theorem closest_loop_spec (s : Slice Std.U8) {W : Std.Usize} (prev : Array Std.U32 W)
    (p len n c k res : Std.Usize) (hn : n.val = s.length) (hp : p.val + len.val + 8 ≤ s.length)
    (hlen : len.val ≤ 258) (hW : 0 < W.val) (hres : Near s p.val len.val res.val) :
    slot.closest_loop s prev p len n c k res ⦃ fun r => Near s p.val len.val r.val ⦄ := by
  rw [slot.closest_loop]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  apply Std.loop.spec_decr_nat
    (measure := fun r => r.2.1.val)
    (inv := fun r => Near s p.val len.val r.2.2.val)
  · rintro ⟨c, k, res⟩ hres
    simp only at hres
    simp only [slot.closest_loop.body]
    step*
    all_goals first
      | exact ⟨hres, by scalar_tac⟩
      | exact hres
      | exact ⟨Near.found (by assumption) (by assumption) (by assumption) (by assumption)
          (by assumption) (by assumption), by scalar_tac⟩
  · exact hres
@[local step]
theorem closest_spec (s : Slice Std.U8) {W : Std.Usize} (prev : Array Std.U32 W)
    (p start len depth : Std.Usize) (hp : p.val + len.val + 8 ≤ s.length) (hlen : len.val ≤ 258)
    (hW : 0 < W.val) :
    slot.closest s prev p start len depth ⦃ fun r => Near s p.val len.val r.val ⦄ := by
  rw [slot.closest]
  exact closest_loop_spec s prev p len (Std.Slice.len s) start depth 0#usize (by simp) hp hlen hW
    (Near.none s p.val len.val)
theorem copyN_take_prefix (acc : List Nat) (d : Nat) :
    ∀ n, (copyN acc d n).take acc.length = acc := by
  intro n
  induction n with
  | zero => simp [copyN]
  | succ m ih =>
    simp only [copyN]
    rw [List.take_append_of_le_length (by simp)]
    exact ih
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
def Dec (s : Slice Std.U8) (out : Slice Std.U32) (nt p : Nat) : Prop :=
  p ≤ s.length ∧ nt ≤ p ∧ s.length ≤ out.length ∧
    decode (toks out nt) = some ((bytes s).take p)
theorem Dec.init (input : Slice Std.U8) (out : Slice Std.U32) (h : input.length ≤ out.length) :
    Dec input out (0#usize).val (0#usize).val :=
  ⟨by simp, by simp, h, by simp [toks, LZ77.decode]⟩
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
theorem Dec.pop_lit {s : Slice Std.U8} {out : Slice Std.U32} {nt p : Nat} (h : Dec s out nt p)
    (h0 : 0 < nt) (hle : nt ≤ out.length) (ht : (out.val[nt - 1]!).val < 256) :
    1 ≤ p ∧ Dec s out (nt - 1) (p - 1) := by
  obtain ⟨hps, hntp, hso, hde⟩ := h
  rw [toks_pop out nt h0 hle] at hde
  obtain ⟨hp1, hde'⟩ := decode_pop_lit (by simpa using hps) hde ht
  exact ⟨hp1, by omega, by omega, hso, hde'⟩
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
theorem Dec.done {s : Slice Std.U8} {out : Slice Std.U32} {nt p : Nat} (h : Dec s out nt p)
    (hp : s.length ≤ p) : nt ≤ s.length ∧ LZ77.Valid (bytes s) (toks out nt) := by
  obtain ⟨hps, hntp, hso, hde⟩ := h
  refine ⟨by omega, ?_⟩
  unfold LZ77.Valid
  rw [hde, show p = s.length by omega, ← bytes_length, List.take_length]
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
@[local step]
theorem put_match_spec (s : Slice Std.U8) (out : Slice Std.U32) (nt p d l : Std.Usize)
    (hdec : Dec s out nt.val p.val) (hm : MatchAt s p.val l.val d.val) :
    slot.put_match s out nt p d l ⦃ fun r => r.1.1.val = nt.val + 1 ∧
      r.1.2.val = p.val + l.val ∧ r.2.length = out.length ∧ Dec s r.2 r.1.1.val r.1.2.val ⦄ := by
  rw [slot.put_match]
  have hm' := hm
  obtain ⟨h3, h258, hpl, hd1, hd32, hdp, _⟩ := hm'
  step*
  exact Dec.match_step hdec hm (by assumption)
    (by simp only [LZ77.mkMatch, LZ77.MATCH_BASE]; scalar_tac) (by assumption) (by assumption)
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
def BackInv (input : Slice Std.U8) (L d E P0 : Nat) (out : Slice Std.U32) (nt p l : Nat) : Prop :=
  Dec input out nt p ∧ out.length = L ∧ MatchAt input p l d ∧ p + l = E ∧ p ≤ P0
theorem BackInv.lit {input : Slice Std.U8} {out : Slice Std.U32} {L d E P0 : Nat}
    {nt p l i1 i2 i4 l1 : Std.Usize} {t : Std.U32} {x y : Std.U8}
    (h : BackInv input L d E P0 out nt.val p.val l.val)
    (hi1 : i1.val = nt.val - 1) (hntl : nt.val ≤ out.length) (hnt0 : 1 ≤ nt.val)
    (hi1l : i1.val < out.val.length) (ht : t = out.val[i1.val]) (ht256 : t < 256#u32)
    (hi2 : i2.val = p.val - 1) (hi2l : i2.val < input.val.length) (hx : x = input.val[i2.val])
    (hxy : x = y) (hi4 : i4.val = i2.val - d) (hi4l : i4.val < input.val.length)
    (hy : y = input.val[i4.val]) (hl : l.val < 258) (hdp : d < p.val)
    (hl1 : l1.val = l.val + 1) :
    BackInv input L d E P0 out i1.val i2.val l1.val := by
  obtain ⟨hdec, hL, hm, hE, hP⟩ := h
  have ht' : (out.val[nt.val - 1]!).val < 256 := by
    rw [← hi1, getElem!_pos out.val i1.val hi1l, ← ht]; scalar_tac
  obtain ⟨hp1, hdec'⟩ := Dec.pop_lit hdec (by omega) hntl ht'
  have heq : input.val[p.val - 1]! = input.val[p.val - 1 - d]! := by
    rw [← hi2, getElem!_pos input.val i2.val hi2l, show i2.val - d = i4.val by omega,
      getElem!_pos input.val i4.val hi4l, ← hx, ← hy, hxy]
  have hm' := MatchAt.back_lit hm hl hdp heq
  rw [hi1, hi2, hl1]
  exact ⟨hdec', hL, hm', by omega, by omega⟩
theorem BackInv.match {input : Slice Std.U8} {out : Slice Std.U32} {L d E P0 : Nat}
    {nt p l i1 w i9 i10 i11 i12 : Std.Usize} {t : Std.U32}
    (h : BackInv input L d E P0 out nt.val p.val l.val)
    (hi1 : i1.val = nt.val - 1) (hntl : nt.val ≤ out.length) (hnt0 : 1 ≤ nt.val)
    (hi1l : i1.val < out.val.length) (ht : t = out.val[i1.val])
    (hsame : i12.val = 1 → Matches input i11.val i10.val w.val) (hi12 : i12 = 1#usize)
    (ht24 : 16777216 ≤ t.val) (hwv : w.val = (t.val - 16777216) % 256 + 3)
    (hi9 : i9.val = l.val + w.val) (hi9' : i9.val ≤ 258) (hi10 : i10.val = p.val - w.val)
    (hwp : w.val ≤ p.val) (hdw : d ≤ i10.val) (hi11 : i11.val = i10.val - d) :
    BackInv input L d E P0 out i1.val i10.val i9.val := by
  obtain ⟨hdec, hL, hm, hE, hP⟩ := h
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
  exact ⟨hdec', hL, hm', by omega, by omega⟩
theorem BackInv.part {input : Slice Std.U8} {out out1 : Slice Std.U32} {L d E P0 : Nat}
    {nt p l : Nat} {p1 l1 : Std.Usize} (h : BackInv input L d E P0 out nt p l)
    (hlen : out1.length = out.length) (hdec : Dec input out1 nt p1.val)
    (hm : MatchAt input p1.val l1.val d) (hE : p1.val + l1.val = p + l) (hp : p1.val ≤ p) :
    BackInv input L d E P0 out1 nt p1.val l1.val := by
  obtain ⟨_, hL, _, hE0, hP⟩ := h
  exact ⟨hdec, by rw [hlen, hL], hm, by omega, by omega⟩
theorem Matches.cons {input : Slice Std.U8} {a b n : Nat} (h : Matches input (a + 1) (b + 1) n)
    (heq : input.val[b]! = input.val[a]!) : Matches input a b (n + 1) := by
  intro k hk
  rcases Nat.eq_zero_or_pos k with h0 | hk0
  · subst h0; simpa using heq
  · have := h (k - 1) (by omega)
    rw [show b + 1 + (k - 1) = b + k by omega, show a + 1 + (k - 1) = a + k by omega] at this
    exact this
theorem Matches.append {input : Slice Std.U8} {a b k l : Nat} (h1 : Matches input a b k)
    (h2 : Matches input (a + k) (b + k) l) : Matches input a b (k + l) := by
  intro j hj
  rcases Nat.lt_or_ge j k with hjk | hjk
  · exact h1 j hjk
  · have := h2 (j - k) (by omega)
    rw [show b + k + (j - k) = b + j by omega, show a + k + (j - k) = a + j by omega] at this
    exact this
theorem MatchAt.back_part {s : Slice Std.U8} {p l d k : Nat} (h : MatchAt s p l d)
    (hmk : Matches s (p - k - d) (p - k) k) (hlk : l + k ≤ 258) (hdk : d + k ≤ p) :
    MatchAt s (p - k) (l + k) d := by
  obtain ⟨h3, h258, hpl, hd1, hd32, _, hm⟩ := h
  refine ⟨by omega, hlk, by omega, hd1, hd32, by omega, ?_⟩
  have hm' : Matches s (p - k - d + k) (p - k + k) l := by
    rw [show p - k - d + k = p - d by omega, show p - k + k = p by omega]; exact hm
  have := Matches.append hmk hm'
  rw [show k + l = l + k by omega] at this
  exact this
theorem Matches.back_step {input : Slice Std.U8} {p d k : Nat} {i4 i7 k1 : Std.Usize}
    {x y : Std.U8} (h : Matches input (p - k - d) (p - k) k) (hdk : d + k < p)
    (hi4 : i4.val = p - 1 - k) (hi4l : i4.val < input.val.length) (hx : x = input.val[i4.val])
    (hi7 : i7.val = p - 1 - k - d) (hi7l : i7.val < input.val.length)
    (hy : y = input.val[i7.val]) (hxy : x = y) (hk1 : k1.val = k + 1) :
    Matches input (p - k1.val - d) (p - k1.val) k1.val := by
  rw [hk1]
  apply Matches.cons
  · rw [show p - (k + 1) - d + 1 = p - k - d by omega, show p - (k + 1) + 1 = p - k by omega]
    exact h
  · rw [show p - (k + 1) - d = i7.val by omega, show p - (k + 1) = i4.val by omega,
      getElem!_pos input.val i4.val hi4l, getElem!_pos input.val i7.val hi7l, ← hx, ← hy, hxy]
theorem part_merge_loop_spec (input : Slice Std.U8) (p0 l0 d w k : Std.Usize)
    (hp0 : p0.val ≤ input.length) (hkw : k.val ≤ w.val) (hl0 : l0.val + k.val ≤ 258)
    (hdk : d.val + k.val ≤ p0.val)
    (hm : Matches input (p0.val - k.val - d.val) (p0.val - k.val) k.val) :
    slot.part_merge_loop input p0 l0 d w k ⦃ fun r =>
      r.val ≤ w.val ∧ l0.val + r.val ≤ 258 ∧ d.val + r.val ≤ p0.val ∧
      Matches input (p0.val - r.val - d.val) (p0.val - r.val) r.val ⦄ := by
  rw [slot.part_merge_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun r => w.val - r.val)
    (inv := fun r => r.val ≤ w.val ∧ l0.val + r.val ≤ 258 ∧ d.val + r.val ≤ p0.val ∧
      Matches input (p0.val - r.val - d.val) (p0.val - r.val) r.val)
  · rintro k ⟨hkw, hl0, hdk, hm⟩
    simp only [slot.part_merge_loop.body]
    step*
    all_goals first
      | exact ⟨hkw, hl0, hdk, hm⟩
      | (refine ⟨by scalar_tac, by scalar_tac, by scalar_tac,
          Matches.back_step (i4 := i4) (i7 := i7) (x := i5) (y := i8) hm (by scalar_tac)
            (by scalar_tac) (by scalar_tac) (by assumption) (by scalar_tac) (by scalar_tac)
            (by assumption) (by assumption) (by scalar_tac),
          by scalar_tac⟩)
  · exact ⟨hkw, hl0, hdk, hm⟩
@[local step]
theorem part_merge_loop_spec0 (input : Slice Std.U8) (p0 l0 d w : Std.Usize)
    (hp0 : p0.val ≤ input.length) (hl0 : l0.val ≤ 258) (hdk : d.val ≤ p0.val) :
    slot.part_merge_loop input p0 l0 d w 0#usize ⦃ fun r =>
      r.val ≤ w.val ∧ l0.val + r.val ≤ 258 ∧ d.val + r.val ≤ p0.val ∧
      Matches input (p0.val - r.val - d.val) (p0.val - r.val) r.val ⦄ :=
  part_merge_loop_spec input p0 l0 d w 0#usize hp0 (by simp) (by simpa using hl0)
    (by simpa using hdk) (by simpa using LZ77.Matches.zero input (p0.val - d.val) p0.val)
theorem part_post {input : Slice Std.U8} {out out1 : Slice Std.U32}
    {nt p l d w k c nl pp p1 l1 : Nat} {ntU : Std.Usize} {v : Std.U32}
    (hdec : Dec input out nt p) (hm : MatchAt input p l d)
    (hnt0 : 1 ≤ nt) (hntl : nt ≤ out.length) (ht24 : 256 ≤ (out.val[nt - 1]!).val)
    (hw : w = tokLen (out.val[nt - 1]!).val)
    (hmk : Matches input (p - k - d) (p - k) k) (hc : Near input pp nl c)
    (hout1 : out1 = out.set ntU v)
    (hlk : l + k ≤ 258) (hdk : d + k ≤ p) (hk : k ≤ w) (hpp : pp = p - w) (hnl : nl = w - k)
    (hnl3 : 3 ≤ nl) (hnl258 : nl ≤ 258) (hc0 : 0 < c) (hcp : c ≤ pp)
    (hntU : ntU.val = nt - 1) (hv : v.val = LZ77.mkMatch c nl) (hp1 : p1 = p - k)
    (hl1 : l1 = l + k) :
    out1.length = out.length ∧ Dec input out1 nt p1 ∧ MatchAt input p1 l1 d ∧
      p1 + l1 = p + l ∧ p1 ≤ p := by
  subst hp1 hl1 hpp
  obtain ⟨hwp, hdec'⟩ := Dec.pop_match hdec (by omega) hntl ht24
  rw [← hw] at hdec' hwp
  have hpn : p ≤ input.length := hdec.1
  have hmc : MatchAt input (p - w) nl c := by
    rcases hc with h0 | ⟨hc1, hc32, _, hmm⟩
    · omega
    · exact ⟨hnl3, hnl258, by omega, hc1, hc32, hcp, hmm⟩
  have hd2 := Dec.match hdec' hmc ntU hntU v hv
  rw [show nt - 1 + 1 = nt by omega, show p - w + nl = p - k by omega, ← hout1] at hd2
  refine ⟨by rw [hout1, Std.Slice.set_length], hd2, MatchAt.back_part hm hmk hlk hdk,
    by omega, by omega⟩
@[local step]
theorem part_merge_spec {W : Std.Usize} (input : Slice Std.U8) (out : Slice Std.U32)
    (prev : Array Std.U32 W) (nt p l d : Std.Usize) (t : Std.U32) (w : Std.Usize)
    (hdec : Dec input out nt.val p.val) (hm : MatchAt input p.val l.val d.val)
    (hp8 : p.val + 8 ≤ input.length) (hnt0 : 1 ≤ nt.val) (hntl : nt.val ≤ out.length)
    (ht : (out.val[nt.val - 1]!).val = t.val) (ht24 : 16777216 ≤ t.val)
    (hw : w.val = (t.val - 16777216) % 256 + 3) (hW : 0 < W.val) :
    slot.part_merge input out prev nt p l d t w ⦃ fun r =>
      r.2.length = out.length ∧ Dec input r.2 nt.val r.1.1.val ∧
      MatchAt input r.1.1.val r.1.2.val d.val ∧ r.1.1.val + r.1.2.val = p.val + l.val ∧
      r.1.1.val ≤ p.val ⦄ := by
  rw [slot.part_merge]
  have hm' := hm
  obtain ⟨h3, h258, hpl, hd1, hd32, hdp, _⟩ := hm'
  have hwt : w.val = tokLen (out.val[nt.val - 1]!).val := by
    rw [ht, hw]; simp only [tokLen, MATCH_BASE]
  have ht256 : 256 ≤ (out.val[nt.val - 1]!).val := by rw [ht]; omega
  step*
  all_goals first
    | exact ⟨rfl, hdec, hm, rfl, le_refl _⟩
    | exact part_post hdec hm hnt0 hntl ht256 hwt (by assumption) (by assumption)
        (by assumption) (by scalar_tac) (by scalar_tac) (by scalar_tac) (by scalar_tac)
        (by scalar_tac) (by scalar_tac) (by scalar_tac) (by scalar_tac) (by scalar_tac)
        (by scalar_tac) (by simp only [LZ77.mkMatch, LZ77.MATCH_BASE]; scalar_tac)
        (by scalar_tac) (by scalar_tac)
def LazyInv (input : Slice Std.U8) (L lim : Nat) (out : Slice Std.U32) (nt p : Nat)
    {N : Std.Usize} (head : Array Std.U32 N) (ins l d : Nat) : Prop :=
  Dec input out nt p ∧ out.length = L ∧ MatchAt input p l d ∧ HeadBound head (p + 2) ∧
    p < lim ∧ ins ≤ p + 3
theorem LazyInv.accept {input : Slice Std.U8} {L lim p' B : Nat} {out1 : Slice Std.U32}
    {nt1 i ins1 l1 d1 minl : Std.Usize} {N : Std.Usize} {head1 : Array Std.U32 N}
    (hdec : Dec input out1 nt1.val p') (hi : i.val = p') (hlen : out1.length = L)
    (hf : FoundAt input i.val l1.val d1.val) (hl1 : minl.val ≤ l1.val) (hminl : 3 ≤ minl.val)
    (hB : HeadBound head1 B) (hBi : B ≤ i.val + 2) (hilim : i.val < lim)
    (hins : ins1.val ≤ i.val + 3) :
    LazyInv input L lim out1 nt1.val i.val head1 ins1.val l1.val d1.val := by
  subst hi
  refine ⟨hdec, hlen, ?_, HeadBound.mono hB hBi, hilim, hins⟩
  rcases hf with h | h
  · omega
  · exact h
theorem LazyInv.reject {input : Slice Std.U8} {L lim : Nat} {out : Slice Std.U32}
    {nt p ins ins1 l d B : Nat} {N : Std.Usize} {head head1 : Array Std.U32 N}
    (h : LazyInv input L lim out nt p head ins l d) (hB : HeadBound head1 B) (hBp : B ≤ p + 2)
    (hins1 : ins1 ≤ p + 3) : LazyInv input L lim out nt p head1 ins1 l d := by
  obtain ⟨hdec, hlen, hm, _, hplim, _⟩ := h
  exact ⟨hdec, hlen, hm, HeadBound.mono hB hBp, hplim, hins1⟩
theorem Dec.cast {s : Slice Std.U8} {out : Slice Std.U32} {nt p p' : Nat} (h : Dec s out nt p)
    (hp : p' = p) : Dec s out nt p' := by
  subst hp; exact h
theorem lazy_loop_inv {H W : Std.Usize} (L2 : Std.Usize) (input : Slice Std.U8) (out : Slice Std.U32)
    (n nt p : Std.Usize) (mask : Std.U32) (minl lazy nice ldep : Std.Usize) (hlit : Std.I32)
    (head : Array Std.U32 H) (prev : Array Std.U32 W) (lim ins l d : Std.Usize) (go : Std.U32)
    (L : Nat) (hn : n.val = input.length) (hlim : lim.val + 8 = input.length)
    (hminl : 3 ≤ minl.val) (hminl8 : minl.val ≤ 8) (hH : 0 < H.val) (hW : 0 < W.val)
    (hh0 : 0 ≤ hlit.val) (hh1 : hlit.val ≤ 1000000)
    (hinv : LazyInv input L lim.val out nt.val p.val head ins.val l.val d.val) :
    slot.run_loop0_loop1 L2 input out n nt p mask minl lazy nice ldep hlit head prev lim ins l d go
      ⦃ fun r => LazyInv input L lim.val r.1 r.2.1.val r.2.2.1.val r.2.2.2.1
        r.2.2.2.2.2.1.val r.2.2.2.2.2.2.1.val r.2.2.2.2.2.2.2.val ⦄ := by
  rw [slot.run_loop0_loop1]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  have ⟨hL0, hL1⟩ := L2B_bound
  apply Std.loop.spec_decr_nat
    (measure := fun r => lim.val - r.2.2.1.val + r.2.2.2.2.2.2.2.2.val)
    (inv := fun r => LazyInv input L lim.val r.1 r.2.1.val r.2.2.1.val r.2.2.2.1
      r.2.2.2.2.2.1.val r.2.2.2.2.2.2.1.val r.2.2.2.2.2.2.2.1.val)
  · rintro ⟨out, nt, p, head, prev, ins, l, d, go⟩ hinv
    simp only at hinv
    have hinv' := hinv
    obtain ⟨hdec, hL, hm, hB, hplim, hins⟩ := hinv'
    have hdec' := hdec
    have hm' := hm
    obtain ⟨hps, hntp, hso, _⟩ := hdec'
    obtain ⟨h3, h258, hpl, hd1, hd32, hdp, _⟩ := hm'
    simp only [slot.run_loop0_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals first
      | (refine ⟨LazyInv.accept (by assumption) (by scalar_tac) (by scalar_tac) (by assumption)
          (by scalar_tac) hminl (by assumption) (by scalar_tac) (by scalar_tac) (by scalar_tac),
          by scalar_tac⟩)
      | (refine ⟨LazyInv.reject hinv (by assumption) (by scalar_tac) (by scalar_tac),
          by scalar_tac⟩)
      | exact Dec.cast (by assumption) (by scalar_tac)
  · exact hinv
@[local step]
theorem lazy_loop_spec {H W : Std.Usize} (L2 : Std.Usize) (input : Slice Std.U8) (out : Slice Std.U32)
    (n nt p : Std.Usize) (mask : Std.U32) (minl lazy nice ldep : Std.Usize) (hlit : Std.I32)
    (head : Array Std.U32 H) (prev : Array Std.U32 W) (lim ins l d : Std.Usize) (go : Std.U32)
    (L : Nat) (hn : n.val = input.length) (hlim : lim.val + 8 = input.length)
    (hminl : 3 ≤ minl.val) (hminl8 : minl.val ≤ 8) (hH : 0 < H.val) (hW : 0 < W.val)
    (hh0 : 0 ≤ hlit.val) (hh1 : hlit.val ≤ 1000000)
    (hdec : Dec input out nt.val p.val) (hlen : out.length = L)
    (hm : MatchAt input p.val l.val d.val) (hB : HeadBound head (p.val + 2))
    (hplim : p.val < lim.val) (hins : ins.val ≤ p.val + 3) :
    slot.run_loop0_loop1 L2 input out n nt p mask minl lazy nice ldep hlit head prev lim ins l d go
      ⦃ fun r =>
      Dec input r.1 r.2.1.val r.2.2.1.val ∧ r.1.length = L ∧
      MatchAt input r.2.2.1.val r.2.2.2.2.2.2.1.val r.2.2.2.2.2.2.2.val ∧
      HeadBound r.2.2.2.1 (r.2.2.1.val + r.2.2.2.2.2.2.1.val) ∧ r.2.2.1.val < lim.val ∧
      r.2.2.2.2.2.1.val ≤ r.2.2.1.val + 3 ∧ 3 ≤ r.2.2.2.2.2.2.1.val ⦄ := by
  apply Std.WP.spec_mono (lazy_loop_inv L2 input out n nt p mask minl lazy nice ldep hlit head prev
    lim ins l d go L hn hlim hminl hminl8 hH hW hh0 hh1 ⟨hdec, hlen, hm, hB, hplim, hins⟩)
  rintro ⟨out', nt', p', head', prev', ins', l', d'⟩ ⟨hdec', hlen', hm', hB', hplim', hins'⟩
  exact ⟨hdec', hlen', hm', HeadBound.mono hB' (by have := hm'.1; omega), hplim', hins', hm'.1⟩
theorem idx_bang {out : Slice Std.U32} {nt i1 : Std.Usize} {t : Std.U32}
    (hi1 : i1.val = nt.val - 1) (hl : i1.val < out.val.length) (ht : t = out.val[i1.val]) :
    (out.val[nt.val - 1]!).val = t.val := by
  rw [← hi1, getElem!_pos out.val i1.val hl, ← ht]
theorem back_loop_inv {W : Std.Usize} (input : Slice Std.U8) (out : Slice Std.U32)
    (nt p : Std.Usize) (prev : Array Std.U32 W) (l d back : Std.Usize) (L E P0 : Nat)
    (hP0 : P0 + 8 ≤ input.length) (hW : 0 < W.val)
    (hinv : BackInv input L d.val E P0 out nt.val p.val l.val) :
    slot.run_loop0_loop2 input out nt p prev l d back ⦃ fun r =>
      BackInv input L d.val E P0 r.1 r.2.1.val r.2.2.1.val r.2.2.2.val ⦄ := by
  rw [slot.run_loop0_loop2]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  apply Std.loop.spec_decr_nat
    (measure := fun r => slot.BACKTOK.val - r.2.2.2.2.val)
    (inv := fun r => BackInv input L d.val E P0 r.1 r.2.1.val r.2.2.1.val r.2.2.2.1.val)
  · rintro ⟨out, nt, p, l, back⟩ hinv
    simp only at hinv
    have hinv' := hinv
    obtain ⟨hdec, hL, hm, hE, hp0⟩ := hinv'
    have hdec' := hdec
    have hm' := hm
    obtain ⟨hps, hntp, hso, _⟩ := hdec'
    obtain ⟨h3, h258, hpl, hd1, hd32, hdp, _⟩ := hm'
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
      | (refine ⟨BackInv.part hinv (by assumption) (by assumption) (by assumption)
          (by scalar_tac) (by scalar_tac), by scalar_tac⟩)
      | exact ⟨hinv, by scalar_tac⟩
      | exact idx_bang (i1 := i1) (by scalar_tac) (by scalar_tac) (by assumption)
      | (exfalso; scalar_tac)
  · exact hinv
@[local step]
theorem back_loop_spec {W : Std.Usize} (input : Slice Std.U8) (out : Slice Std.U32)
    (nt p : Std.Usize) (prev : Array Std.U32 W) (l d back : Std.Usize)
    (hp8 : p.val + 8 ≤ input.length) (hW : 0 < W.val) (hdec : Dec input out nt.val p.val)
    (hm : MatchAt input p.val l.val d.val) :
    slot.run_loop0_loop2 input out nt p prev l d back ⦃ fun r =>
      Dec input r.1 r.2.1.val r.2.2.1.val ∧ r.1.length = out.length ∧
      MatchAt input r.2.2.1.val r.2.2.2.val d.val ∧
      r.2.2.1.val + r.2.2.2.val = p.val + l.val ∧ r.2.2.1.val ≤ p.val ⦄ := by
  apply Std.WP.spec_mono (back_loop_inv input out nt p prev l d back out.length (p.val + l.val)
    p.val hp8 hW ⟨hdec, rfl, hm, rfl, le_refl _⟩)
  intro r h
  obtain ⟨h1, h2, h3, h4, h5⟩ := h
  exact ⟨h1, h2, h3, h4, h5⟩
theorem sat_add_val (x y : Std.Usize) :
    (core.num.Usize.saturating_add x y).val = min Std.Usize.max (x.val + y.val) := by
  have hsz : Std.Usize.max < 2 ^ UScalarTy.Usize.numBits := by
    rw [Std.Usize.max_def, Std.Usize.numBits]
    have : 0 < 2 ^ UScalarTy.Usize.numBits := Nat.two_pow_pos _
    omega
  show (BitVec.ofNat _ (min (UScalar.max UScalarTy.Usize) (x.val + y.val))).toNat = _
  rw [BitVec.toNat_ofNat, UScalar.max_USize_eq, Nat.mod_eq_of_lt (by omega)]
@[local step]
theorem sat_add_spec (x y : Std.Usize) :
    lift (core.num.Usize.saturating_add x y) ⦃ fun r =>
      r.val = x.val + y.val ∨ (r.val = Std.Usize.max ∧ Std.Usize.max < x.val + y.val) ⦄ := by
  simp only [lift, Std.WP.spec_ok]
  rw [sat_add_val]
  omega
theorem sat_sub_val (x y : Std.Usize) :
    (core.num.Usize.saturating_sub x y).val = x.val - y.val := by
  have hx := x.hBounds
  show (BitVec.ofNat _ (max 0 (x.val - y.val))).toNat = x.val - y.val
  rw [BitVec.toNat_ofNat, Nat.zero_max]
  exact Nat.mod_eq_of_lt (lt_of_le_of_lt (Nat.sub_le _ _) hx)
@[local step]
theorem sat_sub_spec (x y : Std.Usize) :
    lift (core.num.Usize.saturating_sub x y) ⦃ fun r => r.val = x.val - y.val ⦄ := by
  simp only [lift, Std.WP.spec_ok]
  exact sat_sub_val x y
theorem tail_sub_ok {ins e t i : Std.Usize} (hi : i = core.num.Usize.wrapping_add ins t)
    (hlt : i < e) (hie : ins.val ≤ e.val) (ht : t.val ≤ 2147483648) : t.val ≤ e.val := by
  have hsz : 4294967296 ≤ Usize.size := by scalar_tac
  have hil : i.val < e.val := by scalar_tac
  have hel : e.val < Usize.size := by scalar_tac
  rw [hi, core.num.Usize.wrapping_add_val_eq, UScalar.size_UScalarTyUsize] at hil
  by_cases hw : ins.val + t.val < Usize.size
  · rw [Nat.mod_eq_of_lt hw] at hil; omega
  · omega
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
@[local step]
theorem stride_loop_spec {H W : Std.Usize} (input : Slice Std.U8) (mask : Std.U32)
    (stride : Std.Usize) (head : Array Std.U32 H) (prev : Array Std.U32 W) (lim ins e2 : Std.Usize)
    (B : Nat) (hB : HeadBound head B) (heB : e2.val < B + 1) (hl4 : lim.val + 4 ≤ Std.Usize.max)
    (hH : 0 < H.val) (hW : 0 < W.val) (hS : 0 < stride.val)
    (hS2 : e2.val + stride.val ≤ Std.Usize.max) :
    slot.run_loop0_loop4 input mask stride head prev lim ins e2 ⦃ fun r =>
      HeadBound r.1 B ∧ (r.2.2.val ≤ ins.val ∨ (0 < e2.val ∧ r.2.2.val < e2.val + stride.val)) ⦄ := by
  rw [slot.run_loop0_loop4]
  apply Std.loop.spec_decr_nat
    (measure := fun r => e2.val - r.2.2.val)
    (inv := fun r => HeadBound r.1 B ∧
      (r.2.2.val ≤ ins.val ∨ (0 < e2.val ∧ r.2.2.val < e2.val + stride.val)))
  · rintro ⟨head, prev, ins'⟩ ⟨hB, hins⟩
    simp only at hB hins
    simp only [slot.run_loop0_loop4.body]
    step*
    all_goals first
      | exact ⟨hB, hins⟩
      | exact ⟨by assumption, by scalar_tac, by scalar_tac⟩
  · exact ⟨hB, Or.inl (le_refl _)⟩
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
theorem numBits_ge : 32 ≤ System.Platform.numBits := by
  rcases System.Platform.numBits_eq with h | h <;> omega
def MainInv (input : Slice Std.U8) (L : Nat) (out : Slice Std.U32) (nt p : Nat)
    {N : Std.Usize} (head : Array Std.U32 N) (miss : Nat) : Prop :=
  Dec input out nt p ∧ out.length = L ∧ HeadBound head p ∧ miss ≤ p
theorem MainInv.mk' {input : Slice Std.U8} {L : Nat} {out : Slice Std.U32} {nt p m B : Nat}
    {N : Std.Usize} {head : Array Std.U32 N} (hdec : Dec input out nt p) (hlen : out.length = L)
    (hB : HeadBound head B) (hBp : B ≤ p) (hm : m ≤ p) : MainInv input L out nt p head m :=
  ⟨hdec, hlen, HeadBound.mono hB hBp, hm⟩
set_option maxHeartbeats 16000000 in
theorem main_loop_spec {H W : Std.Usize} (L2 : Std.Usize) (input : Slice Std.U8) (out : Slice Std.U32)
    (n nt p : Std.Usize) (mask : Std.U32)
    (minl depth lazy skip skcap nice ldep insm stride : Std.Usize) (hlit : Std.I32)
    (head : Array Std.U32 H) (prev : Array Std.U32 W) (lim ins miss fuel : Std.Usize) (L : Nat)
    (hn : n.val = input.length) (hlim : lim.val + 8 = input.length) (hminl : 3 ≤ minl.val)
    (hminl8 : minl.val ≤ 8) (hskip : skip.val < 32) (hH : 0 < H.val) (hW : 0 < W.val)
    (hh0 : 0 ≤ hlit.val) (hh1 : hlit.val ≤ 1000000)
    (hinv : MainInv input L out nt.val p.val head miss.val) :
    slot.run_loop0 L2 input out n nt p mask minl depth lazy skip skcap nice ldep insm stride hlit
      head prev lim ins miss fuel ⦃ fun r => Dec input r.1 r.2.1.val r.2.2.val ∧ r.1.length = L ⦄ := by
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
      | (refine ⟨MainInv.mk' (by assumption) (by omega) (by assumption) (by omega)
          (by first | omega | simp), by omega⟩)
      | exact FoundAt.real (by assumption) (by scalar_tac)
      | exact HeadBound.mono (by assumption) (by omega)
      | exact tail_sub_ok (by assumption) (by assumption) (by scalar_tac) (by scalar_tac)
      | exact Dec.cast (by assumption) (by omega)
      | omega
      | (have := numBits_ge; scalar_tac)
  · exact hinv
@[local step]
theorem main_loop_spec' {H W : Std.Usize} (L2 : Std.Usize) (input : Slice Std.U8) (out : Slice Std.U32)
    (n nt p : Std.Usize) (mask : Std.U32)
    (minl depth lazy skip skcap nice ldep insm stride : Std.Usize) (hlit : Std.I32)
    (head : Array Std.U32 H) (prev : Array Std.U32 W) (lim ins miss fuel : Std.Usize)
    (hn : n.val = input.length) (hlim : lim.val + 8 = input.length) (hminl : 3 ≤ minl.val)
    (hminl8 : minl.val ≤ 8) (hskip : skip.val < 32) (hH : 0 < H.val) (hW : 0 < W.val)
    (hh0 : 0 ≤ hlit.val) (hh1 : hlit.val ≤ 1000000)
    (hdec : Dec input out nt.val p.val) (hB : HeadBound head p.val) (hmiss : miss.val ≤ p.val) :
    slot.run_loop0 L2 input out n nt p mask minl depth lazy skip skcap nice ldep insm stride hlit
      head prev lim ins miss fuel ⦃ fun r =>
        Dec input r.1 r.2.1.val r.2.2.val ∧ r.1.length = out.length ⦄ :=
  main_loop_spec L2 input out n nt p mask minl depth lazy skip skcap nice ldep insm stride hlit head
    prev lim ins miss fuel out.length hn hlim hminl hminl8 hskip hH hW hh0 hh1
    ⟨hdec, rfl, hB, hmiss⟩
theorem lazy_dna_inv {H W : Std.Usize} (input : Slice Std.U8) (out : Slice Std.U32)
    (nt p minl lazy : Std.Usize) (hlit : Std.I32) (head : Array Std.U32 H)
    (prev : Array Std.U32 W) (lim ins l d : Std.Usize) (go : Std.U32) (L : Nat)
    (hlim : lim.val + 8 = input.length) (hminl : 3 ≤ minl.val) (hminl10 : minl.val ≤ 10)
    (hH : 0 < H.val) (hW : 0 < W.val) (hh0 : 0 ≤ hlit.val) (hh1 : hlit.val ≤ 1000000)
    (hinv : LazyInv input L lim.val out nt.val p.val head ins.val l.val d.val) :
    slot.run_dna_loop0_loop1 input out nt p minl lazy hlit head prev lim ins l d go ⦃ fun r =>
      LazyInv input L lim.val r.1 r.2.1.val r.2.2.1.val r.2.2.2.1 r.2.2.2.2.2.1.val
        r.2.2.2.2.2.2.1.val r.2.2.2.2.2.2.2.val ⦄ := by
  rw [slot.run_dna_loop0_loop1]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  apply Std.loop.spec_decr_nat
    (measure := fun r => lim.val - r.2.2.1.val + r.2.2.2.2.2.2.2.2.val)
    (inv := fun r => LazyInv input L lim.val r.1 r.2.1.val r.2.2.1.val r.2.2.2.1
      r.2.2.2.2.2.1.val r.2.2.2.2.2.2.1.val r.2.2.2.2.2.2.2.1.val)
  · rintro ⟨out, nt, p, head, prev, ins, l, d, go⟩ hinv
    simp only at hinv
    have hinv' := hinv
    obtain ⟨hdec, hL, hm, hB, hplim, hins⟩ := hinv'
    have hdec' := hdec
    have hm' := hm
    obtain ⟨hps, hntp, hso, _⟩ := hdec'
    obtain ⟨h3, h258, hpl, hd1, hd32, hdp, _⟩ := hm'
    simp only [slot.run_dna_loop0_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals first
      | (refine ⟨LazyInv.accept (by assumption) (by scalar_tac) (by scalar_tac) (by assumption)
          (by scalar_tac) hminl (by assumption) (by scalar_tac) (by scalar_tac) (by scalar_tac),
          by scalar_tac⟩)
      | (refine ⟨LazyInv.reject hinv (by assumption) (by scalar_tac) (by scalar_tac),
          by scalar_tac⟩)
  · exact hinv
@[local step]
theorem lazy_dna_spec {H W : Std.Usize} (input : Slice Std.U8) (out : Slice Std.U32)
    (nt p minl lazy : Std.Usize) (hlit : Std.I32) (head : Array Std.U32 H)
    (prev : Array Std.U32 W) (lim ins l d : Std.Usize) (go : Std.U32) (L : Nat)
    (hlim : lim.val + 8 = input.length) (hminl : 3 ≤ minl.val) (hminl10 : minl.val ≤ 10)
    (hH : 0 < H.val) (hW : 0 < W.val) (hh0 : 0 ≤ hlit.val) (hh1 : hlit.val ≤ 1000000)
    (hdec : Dec input out nt.val p.val) (hlen : out.length = L)
    (hm : MatchAt input p.val l.val d.val) (hB : HeadBound head (p.val + 2))
    (hplim : p.val < lim.val) (hins : ins.val ≤ p.val + 3) :
    slot.run_dna_loop0_loop1 input out nt p minl lazy hlit head prev lim ins l d go ⦃ fun r =>
      Dec input r.1 r.2.1.val r.2.2.1.val ∧ r.1.length = L ∧
      MatchAt input r.2.2.1.val r.2.2.2.2.2.2.1.val r.2.2.2.2.2.2.2.val ∧
      HeadBound r.2.2.2.1 (r.2.2.1.val + r.2.2.2.2.2.2.1.val) ∧ r.2.2.1.val < lim.val ∧
      r.2.2.2.2.2.1.val ≤ r.2.2.1.val + 3 ∧ 3 ≤ r.2.2.2.2.2.2.1.val ⦄ := by
  apply Std.WP.spec_mono (lazy_dna_inv input out nt p minl lazy hlit head prev lim ins l d go L
    hlim hminl hminl10 hH hW hh0 hh1 ⟨hdec, hlen, hm, hB, hplim, hins⟩)
  rintro ⟨out', nt', p', head', prev', ins', l', d'⟩ ⟨hdec', hlen', hm', hB', hplim', hins'⟩
  exact ⟨hdec', hlen', hm', HeadBound.mono hB' (by have := hm'.1; omega), hplim', hins', hm'.1⟩
theorem back_dna_inv (input : Slice Std.U8) (out : Slice Std.U32) (nt p l d back : Std.Usize)
    (L E P0 : Nat) (hP0 : P0 + 8 ≤ input.length)
    (hinv : BackInv input L d.val E P0 out nt.val p.val l.val) :
    slot.run_dna_loop0_loop2 input out nt p l d back ⦃ fun r =>
      BackInv input L d.val E P0 out r.1.val r.2.1.val r.2.2.val ⦄ := by
  rw [slot.run_dna_loop0_loop2]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  apply Std.loop.spec_decr_nat
    (measure := fun r => slot.BACKTOK.val - r.2.2.2.val)
    (inv := fun r => BackInv input L d.val E P0 out r.1.val r.2.1.val r.2.2.1.val)
  · rintro ⟨nt, p, l, back⟩ hinv
    simp only at hinv
    have hinv' := hinv
    obtain ⟨⟨hps, hntp, hso, _⟩, hL, ⟨h3, h258, hpl, hd1, hd32, hdp, _⟩, hE, hp0⟩ := hinv'
    simp only [slot.run_dna_loop0_loop2.body]
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
@[local step]
theorem back_dna_spec (input : Slice Std.U8) (out : Slice Std.U32) (nt p l d back : Std.Usize)
    (hp8 : p.val + 8 ≤ input.length) (hdec : Dec input out nt.val p.val)
    (hm : MatchAt input p.val l.val d.val) :
    slot.run_dna_loop0_loop2 input out nt p l d back ⦃ fun r =>
      Dec input out r.1.val r.2.1.val ∧ MatchAt input r.2.1.val r.2.2.val d.val ∧
      r.2.1.val + r.2.2.val = p.val + l.val ∧ r.2.1.val ≤ p.val ⦄ := by
  apply Std.WP.spec_mono (back_dna_inv input out nt p l d back out.length (p.val + l.val) p.val hp8
    ⟨hdec, rfl, hm, rfl, le_refl _⟩)
  intro r h
  obtain ⟨h1, _, h3, h4, h5⟩ := h
  exact ⟨h1, h3, h4, h5⟩
@[local step]
theorem ins_dna0_spec {H W : Std.Usize} (input : Slice Std.U8) (p : Std.Usize)
    (head : Array Std.U32 H) (prev : Array Std.U32 W) (ins : Std.Usize) (B : Nat)
    (hB : HeadBound head B) (hpB : p.val < B + 1) (hp8 : p.val + 8 ≤ input.length)
    (hH : 0 < H.val) (hW : 0 < W.val) :
    slot.run_dna_loop0_loop0 input p head prev ins ⦃ fun r => HeadBound r.1 B ⦄ := by
  rw [slot.run_dna_loop0_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun r => p.val - r.2.2.val)
    (inv := fun r => HeadBound r.1 B)
  · rintro ⟨head, prev, ins⟩ hB
    simp only at hB
    simp only [slot.run_dna_loop0_loop0.body]
    step*
  · exact hB
@[local step]
theorem ins_dna3_spec {H W : Std.Usize} (input : Slice Std.U8)
    (head : Array Std.U32 H) (prev : Array Std.U32 W) (ins stop : Std.Usize) (B : Nat)
    (hB : HeadBound head B) (hsB : stop.val < B + 1) (hs8 : stop.val + 8 ≤ input.length)
    (hH : 0 < H.val) (hW : 0 < W.val) :
    slot.run_dna_loop0_loop3 input head prev ins stop ⦃ fun r =>
      HeadBound r.1 B ∧ (r.2.2.val ≤ ins.val ∨ r.2.2.val ≤ stop.val) ⦄ := by
  rw [slot.run_dna_loop0_loop3]
  apply Std.loop.spec_decr_nat
    (measure := fun r => stop.val - r.2.2.val)
    (inv := fun r => HeadBound r.1 B ∧ (r.2.2.val ≤ ins.val ∨ r.2.2.val ≤ stop.val))
  · rintro ⟨head, prev, ins'⟩ ⟨hB, hins⟩
    simp only at hB hins
    simp only [slot.run_dna_loop0_loop3.body]
    step*
  · exact ⟨hB, Or.inl (le_refl _)⟩
@[local step]
theorem stride_dna_spec {H W : Std.Usize} (input : Slice Std.U8)
    (head : Array Std.U32 H) (prev : Array Std.U32 W) (lim ins e2 : Std.Usize)
    (B : Nat) (hB : HeadBound head B) (heB : e2.val < B + 1) (hl8 : lim.val + 8 = input.length)
    (hH : 0 < H.val) (hW : 0 < W.val) (hS : 0 < slot.STRIDE.val)
    (hS2 : e2.val + slot.STRIDE.val ≤ Std.Usize.max) :
    slot.run_dna_loop0_loop4 input head prev lim ins e2 ⦃ fun r =>
      HeadBound r.1 B ∧
        (r.2.2.val ≤ ins.val ∨ (0 < e2.val ∧ r.2.2.val < e2.val + slot.STRIDE.val)) ⦄ := by
  rw [slot.run_dna_loop0_loop4]
  apply Std.loop.spec_decr_nat
    (measure := fun r => e2.val - r.2.2.val)
    (inv := fun r => HeadBound r.1 B ∧
      (r.2.2.val ≤ ins.val ∨ (0 < e2.val ∧ r.2.2.val < e2.val + slot.STRIDE.val)))
  · rintro ⟨head, prev, ins'⟩ ⟨hB, hins⟩
    simp only at hB hins
    simp only [slot.run_dna_loop0_loop4.body]
    step*
    all_goals first
      | exact ⟨hB, hins⟩
      | exact ⟨by assumption, by scalar_tac, by scalar_tac⟩
  · exact ⟨hB, Or.inl (le_refl _)⟩
@[local step]
theorem ins_dna5_spec {H W : Std.Usize} (input : Slice Std.U8)
    (head : Array Std.U32 H) (prev : Array Std.U32 W) (lim ins «end» : Std.Usize) (B : Nat)
    (hB : HeadBound head B) (heB : «end».val < B + 1) (hl8 : lim.val + 8 = input.length)
    (hH : 0 < H.val) (hW : 0 < W.val) :
    slot.run_dna_loop0_loop5 input head prev lim ins «end» ⦃ fun r =>
      HeadBound r.1 B ∧ (r.2.2.val ≤ ins.val ∨ r.2.2.val ≤ «end».val) ⦄ := by
  rw [slot.run_dna_loop0_loop5]
  apply Std.loop.spec_decr_nat
    (measure := fun r => «end».val - r.2.2.val)
    (inv := fun r => HeadBound r.1 B ∧ (r.2.2.val ≤ ins.val ∨ r.2.2.val ≤ «end».val))
  · rintro ⟨head, prev, ins'⟩ ⟨hB, hins⟩
    simp only at hB hins
    simp only [slot.run_dna_loop0_loop5.body]
    step*
  · exact ⟨hB, Or.inl (le_refl _)⟩
@[local step]
theorem ins_dna6_spec {H W : Std.Usize} (input : Slice Std.U8)
    (head : Array Std.U32 H) (prev : Array Std.U32 W) (lim ins «end» : Std.Usize) (B : Nat)
    (hB : HeadBound head B) (heB : «end».val < B + 1) (hl8 : lim.val + 8 = input.length)
    (hH : 0 < H.val) (hW : 0 < W.val) :
    slot.run_dna_loop0_loop6 input head prev lim ins «end» ⦃ fun r =>
      HeadBound r.1 B ∧ (r.2.2.val ≤ ins.val ∨ r.2.2.val ≤ «end».val) ⦄ := by
  rw [slot.run_dna_loop0_loop6]
  apply Std.loop.spec_decr_nat
    (measure := fun r => «end».val - r.2.2.val)
    (inv := fun r => HeadBound r.1 B ∧ (r.2.2.val ≤ ins.val ∨ r.2.2.val ≤ «end».val))
  · rintro ⟨head, prev, ins'⟩ ⟨hB, hins⟩
    simp only at hB hins
    simp only [slot.run_dna_loop0_loop6.body]
    step*
  · exact ⟨hB, Or.inl (le_refl _)⟩
@[local step]
theorem skip_dna_spec (input : Slice Std.U8) (out : Slice Std.U32) (nt p lim step : Std.Usize)
    (hdec : Dec input out nt.val p.val) (hlim : lim.val ≤ input.length) :
    slot.run_dna_loop0_loop7 input out nt p lim step ⦃ fun r =>
      Dec input r.1 r.2.1.val r.2.2.val ∧ r.1.length = out.length ∧ p.val ≤ r.2.2.val ⦄ := by
  rw [slot.run_dna_loop0_loop7]
  apply Std.loop.spec_decr_nat
    (measure := fun r => r.2.2.2.val)
    (inv := fun r => Dec input r.1 r.2.1.val r.2.2.1.val ∧ r.1.length = out.length ∧
      p.val ≤ r.2.2.1.val)
  · rintro ⟨out', nt', p', step'⟩ ⟨hdec', hlen', hp'⟩
    simp only at hdec' hlen' hp'
    simp only [slot.run_dna_loop0_loop7.body]
    step*
  · exact ⟨hdec, rfl, le_refl _⟩
@[local step]
theorem tail_dna1_spec (input : Slice Std.U8) (out : Slice Std.U32) (n nt p : Std.Usize)
    (hn : n.val = input.length) (hdec : Dec input out nt.val p.val) :
    slot.run_dna_loop1 input out n nt p ⦃ fun r => r.1.val ≤ input.length ∧
      r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
  rw [slot.run_dna_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun r => n.val - r.2.2.val)
    (inv := fun r => Dec input r.1 r.2.1.val r.2.2.val ∧ r.1.length = out.length)
  · rintro ⟨out', nt', p'⟩ ⟨hdec', hlen'⟩
    simp only at hdec' hlen'
    simp only [slot.run_dna_loop1.body]
    step*
    have hd := Dec.done hdec' (by scalar_tac)
    exact ⟨hd.1, hlen', hd.2⟩
  · exact ⟨hdec, rfl⟩
@[local step]
theorem tail_dna2_spec (input : Slice Std.U8) (out : Slice Std.U32) (n nt p : Std.Usize)
    (hn : n.val = input.length) (hdec : Dec input out nt.val p.val) :
    slot.run_dna_loop2 input out n nt p ⦃ fun r => r.1.val ≤ input.length ∧
      r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
  rw [slot.run_dna_loop2]
  apply Std.loop.spec_decr_nat
    (measure := fun r => n.val - r.2.2.val)
    (inv := fun r => Dec input r.1 r.2.1.val r.2.2.val ∧ r.1.length = out.length)
  · rintro ⟨out', nt', p'⟩ ⟨hdec', hlen'⟩
    simp only at hdec' hlen'
    simp only [slot.run_dna_loop2.body]
    step*
    have hd := Dec.done hdec' (by scalar_tac)
    exact ⟨hd.1, hlen', hd.2⟩
  · exact ⟨hdec, rfl⟩
set_option maxHeartbeats 16000000 in
theorem main_dna_spec {H W : Std.Usize} (input : Slice Std.U8) (out : Slice Std.U32)
    (nt p minl depth lazy skip skcap : Std.Usize) (hlit : Std.I32)
    (head : Array Std.U32 H) (prev : Array Std.U32 W) (lim ins miss fuel : Std.Usize) (L : Nat)
    (hlim : lim.val + 8 = input.length) (hminl : 3 ≤ minl.val) (hminl10 : minl.val ≤ 10)
    (hskip : skip.val < 32) (hH : 0 < H.val) (hW : 0 < W.val)
    (hh0 : 0 ≤ hlit.val) (hh1 : hlit.val ≤ 1000000)
    (hinv : MainInv input L out nt.val p.val head miss.val) :
    slot.run_dna_loop0 input out nt p minl depth lazy skip skcap hlit head prev lim ins miss fuel
      ⦃ fun r => Dec input r.1 r.2.1.val r.2.2.val ∧ r.1.length = L ⦄ := by
  rw [slot.run_dna_loop0]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  apply Std.loop.spec_decr_nat
    (measure := fun r => r.2.2.2.2.2.2.2.val)
    (inv := fun r => MainInv input L r.1 r.2.1.val r.2.2.1.val r.2.2.2.1 r.2.2.2.2.2.2.1.val)
  · rintro ⟨out, nt, p, head, prev, ins, miss, fuel⟩ hinv
    simp only at hinv
    have hinv' := hinv
    obtain ⟨hdec, hL, hB, hmiss⟩ := hinv'
    simp only [slot.run_dna_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals first
      | (refine ⟨MainInv.mk' (by assumption) (by omega) (by assumption) (by omega)
          (by first | omega | simp), by omega⟩)
      | exact FoundAt.real (by assumption) (by scalar_tac)
      | exact HeadBound.mono (by assumption) (by omega)
      | exact tail_sub_ok (by assumption) (by assumption) (by scalar_tac) (by scalar_tac)
      | exact Dec.cast (by assumption) (by omega)
      | omega
      | (have := numBits_ge; scalar_tac)
  · exact hinv
@[local step]
theorem main_dna_spec' {H W : Std.Usize} (input : Slice Std.U8) (out : Slice Std.U32)
    (nt p minl depth lazy skip skcap : Std.Usize) (hlit : Std.I32)
    (head : Array Std.U32 H) (prev : Array Std.U32 W) (lim ins miss fuel : Std.Usize)
    (hlim : lim.val + 8 = input.length) (hminl : 3 ≤ minl.val) (hminl10 : minl.val ≤ 10)
    (hskip : skip.val < 32) (hH : 0 < H.val) (hW : 0 < W.val)
    (hh0 : 0 ≤ hlit.val) (hh1 : hlit.val ≤ 1000000)
    (hdec : Dec input out nt.val p.val) (hB : HeadBound head p.val) (hmiss : miss.val ≤ p.val) :
    slot.run_dna_loop0 input out nt p minl depth lazy skip skcap hlit head prev lim ins miss fuel
      ⦃ fun r => Dec input r.1 r.2.1.val r.2.2.val ∧ r.1.length = out.length ⦄ :=
  main_dna_spec input out nt p minl depth lazy skip skcap hlit head prev lim ins miss fuel
    out.length hlim hminl hminl10 hskip hH hW hh0 hh1 ⟨hdec, rfl, hB, hmiss⟩
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
theorem sniff_loop2_spec (cnt : Array Std.U32 256#usize) (mx : Std.U32) (sq : Std.U64)
    (b2 : Std.Usize) (hc : CntBound cnt 4097) (hb : b2.val ≤ 256) :
    slot.sniff_loop2 cnt mx sq b2 ⦃ fun _ => True ⦄ := by
  rw [slot.sniff_loop2]
  apply Std.loop.spec_decr_nat
    (measure := fun r => 256 - r.2.2.val)
    (inv := fun r => r.2.2.val ≤ 256)
  · rintro ⟨mx, sq, b2⟩ hb
    simp only at hb
    simp only [slot.sniff_loop2.body]
    step*
    repeat' (split <;> step*)
  · exact hb
@[local step]
theorem sniff_loop3_spec (cnt : Array Std.U32 256#usize) (mx : Std.U32) (sq : Std.U64)
    (b2 : Std.Usize) (hc : CntBound cnt 4097) (hb : b2.val ≤ 256) :
    slot.sniff_loop3 cnt mx sq b2 ⦃ fun _ => True ⦄ := by
  rw [slot.sniff_loop3]
  apply Std.loop.spec_decr_nat
    (measure := fun r => 256 - r.2.2.val)
    (inv := fun r => r.2.2.val ≤ 256)
  · rintro ⟨mx, sq, b2⟩ hb
    simp only at hb
    simp only [slot.sniff_loop3.body]
    step*
    repeat' (split <;> step*)
  · exact hb
@[local step]
theorem sniff_loop4_spec (cnt : Array Std.U32 256#usize) (mx : Std.U32) (sq : Std.U64)
    (b2 : Std.Usize) (hc : CntBound cnt 4097) (hb : b2.val ≤ 256) :
    slot.sniff_loop4 cnt mx sq b2 ⦃ fun _ => True ⦄ := by
  rw [slot.sniff_loop4]
  apply Std.loop.spec_decr_nat
    (measure := fun r => 256 - r.2.2.val)
    (inv := fun r => r.2.2.val ≤ 256)
  · rintro ⟨mx, sq, b2⟩ hb
    simp only at hb
    simp only [slot.sniff_loop4.body]
    step*
    repeat' (split <;> step*)
  · exact hb
@[local step]
theorem sniff_loop5_spec (cnt : Array Std.U32 256#usize) (mx : Std.U32) (sq : Std.U64)
    (b2 : Std.Usize) (hc : CntBound cnt 4097) (hb : b2.val ≤ 256) :
    slot.sniff_loop5 cnt mx sq b2 ⦃ fun _ => True ⦄ := by
  rw [slot.sniff_loop5]
  apply Std.loop.spec_decr_nat
    (measure := fun r => 256 - r.2.2.val)
    (inv := fun r => r.2.2.val ≤ 256)
  · rintro ⟨mx, sq, b2⟩ hb
    simp only at hb
    simp only [slot.sniff_loop5.body]
    step*
    repeat' (split <;> step*)
  · exact hb
@[local step]
theorem sniff_spec (s : Slice Std.U8) : slot.sniff s ⦃ fun _ => True ⦄ := by
  rw [slot.sniff]
  step*
  apply Std.WP.spec_bind (sniff_loop0_spec s (Std.Slice.len s) _ step 0#usize 0#u32 (by simp)
    (by simpa using CntBound.init) (by simp))
  rintro ⟨cnt1, tot⟩ ⟨hc, ht⟩
  simp only at hc ht
  have hc4 := CntBound.mono hc ht
  clear hc
  step*
  repeat' (split <;> step*)
@[local step]
theorem lift_spec {α : Type} (x : α) : lift x ⦃ fun y => y = x ⦄ := by
  simp [lift]
@[local step]
theorem run_spec (H W : Std.Usize) (MASK : Std.U32)
    (MINL DEPTH LAZY SKIP CAP STOP LD INS STR : Std.Usize) (LIT : Std.I32) (L2 : Std.Usize)
    (input : Slice Std.U8) (out : Slice Std.U32)
    (hlen : input.length ≤ out.length) (hH : 0 < H.val) (hW : 0 < W.val)
    (hmin : 3 ≤ MINL.val) (hmax : MINL.val ≤ 8) (hs : SKIP.val < 32)
    (hl0 : 0 ≤ LIT.val) (hl1 : LIT.val ≤ 1000000) :
    slot.run H W MASK MINL DEPTH LAZY SKIP CAP STOP LD INS STR LIT L2 input out
      ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧
      LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
  rw [slot.run]
  step*
  repeat' (split <;> step*)
  all_goals first
    | exact Dec.init input out hlen
    | exact HeadBound.init _
@[local step]
theorem run_dna_spec (H W : Std.Usize) (input : Slice Std.U8) (out : Slice Std.U32)
    (cls : Std.Usize) (hlen : input.length ≤ out.length) (hH : 0 < H.val) (hW : 0 < W.val) :
    slot.run_dna H W input out cls ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧
      LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
  rw [slot.run_dna]
  step*
  repeat' (split <;> step*)
  all_goals first
    | exact Dec.init input out hlen
    | exact HeadBound.init _
theorem format_id_loop_spec (s : Slice Std.U8) (n : Std.Usize) (cnt : Array Std.U32 256#usize)
    (step i : Std.Usize) (tot : Std.U32) (hn : n.val = s.length) (hc : CntBound cnt tot.val)
    (ht : tot.val ≤ 4097) :
    slot.format_id_loop s n cnt step i tot ⦃ fun r => CntBound r.1 r.2.val ∧ r.2.val ≤ 4097 ⦄ := by
  rw [slot.format_id_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun r => 4097 - r.2.2.val)
    (inv := fun r => CntBound r.1 r.2.2.val ∧ r.2.2.val ≤ 4097)
  · rintro ⟨cnt, i, tot⟩ ⟨hc, ht⟩
    simp only at hc ht
    simp only [slot.format_id_loop.body]
    step*
    all_goals first
      | exact ⟨hc, ht⟩
      | exact ⟨CntBound.step hc (by assumption) (by scalar_tac) (by scalar_tac), by scalar_tac,
          by scalar_tac⟩
  · exact ⟨hc, ht⟩
@[local step]
theorem format_id_spec (s : Slice Std.U8) : slot.format_id s ⦃ fun _ => True ⦄ := by
  rw [slot.format_id]
  step*
  apply Std.WP.spec_bind (format_id_loop_spec s (Std.Slice.len s) _ step 0#usize 0#u32 (by simp)
    (by simpa using CntBound.init) (by simp))
  rintro ⟨cnt1, tot⟩ ⟨hc, ht⟩
  simp only at hc ht
  have hc4 := CntBound.mono hc ht
  clear hc
  step*
  repeat' (split <;> step*)
end E_M
attribute [local step] E_M.sniff_spec E_M.format_id_spec
namespace EY
open Aeneas Aeneas.Std Result ControlFlow
open LZ77 (toks bytes)
set_option maxRecDepth 8192
set_option maxHeartbeats 4000000
namespace EA
open Aeneas Aeneas.Std Result ControlFlow
set_option maxRecDepth 8192
set_option maxHeartbeats 4000000
open LZ77 (toks bytes bytes_length bytes_getElem! Matches emit_lit emit_match ite_ok)
theorem decode_nil (input : Slice Std.U8) (out : Slice Std.U32) :
    LZ77.decode (toks out (0#usize).val) = some ((bytes input).take (0#usize).val) := by
  simp [toks, LZ77.decode]
theorem valid_of_decode {input : Slice Std.U8} {o : Slice Std.U32} {t p : Std.Usize}
    (hde : LZ77.decode (toks o t.val) = some ((bytes input).take p.val)) (hp : p.val = input.length) :
    LZ77.Valid (bytes input) (toks o t.val) := by
  unfold LZ77.Valid
  rw [hde, hp]
  simp
theorem spec_ite_cut {α : Type} (c : Prop) [Decidable c] (a b : Result α) (Q : α → Prop)
    (ha : c → a ⦃ Q ⦄) (hb : ¬c → b ⦃ Q ⦄) : (if c then a else b) ⦃ Q ⦄ := by
  by_cases h : c
  · rw [if_pos h]; exact ha h
  · rw [if_neg h]; exact hb h
theorem ite_prod_spec {α β : Type} (c : Prop) [Decidable c] (A B : Result (α × β))
    (hA : c → A ⦃ fun _ => True ⦄) (hB : ¬c → B ⦃ fun _ => True ⦄) :
    (if c then A else B) ⦃ fun _ => True ⦄ := by
  by_cases h : c
  · rw [if_pos h]; exact hA h
  · rw [if_neg h]; exact hB h
theorem ite_true_spec {α : Type} (c : Prop) [Decidable c] (A B : Result α)
    (hA : c → A ⦃ fun _ => True ⦄) (hB : ¬c → B ⦃ fun _ => True ⦄) :
    (if c then A else B) ⦃ fun _ => True ⦄ := by
  by_cases h : c
  · rw [if_pos h]; exact hA h
  · rw [if_neg h]; exact hB h
@[local step]
theorem ld8_spec (input : Slice Std.U8) (p : Std.Usize) :
    slot.y_a_ld8 input p ⦃ fun _ => True ⦄ := by
  rw [slot.y_a_ld8]
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
  all_goals scalar_tac
@[local step]
theorem first_diff_spec (x : Std.U64) :
    slot.y_a_first_diff x ⦃ fun _ => True ⦄ := by
  rw [slot.y_a_first_diff]
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
  all_goals scalar_tac
@[local step]
theorem fast_len_loop_spec (input : Slice Std.U8) (a : Std.Usize) (b : Std.Usize) (cap : Std.Usize) (l : Std.Usize) (go : Std.Usize) (it : Std.Usize)  :
    slot.y_a_fast_len_loop input a b cap l go it ⦃ fun _ => True ⦄ := by
  rw [slot.y_a_fast_len_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => 40 - s.2.2.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1, x2⟩ _
    simp only [slot.y_a_fast_len_loop.body, lift, Array.to_slice_mut]
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
    all_goals scalar_tac
  · trivial
@[local step]
theorem fast_len_spec (input : Slice Std.U8) (a : Std.Usize) (b : Std.Usize) (cap : Std.Usize) :
    slot.y_a_fast_len input a b cap ⦃ fun _ => True ⦄ := by
  rw [slot.y_a_fast_len]
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
  all_goals scalar_tac
@[local step]
theorem fast_len2_loop_spec (input : Slice Std.U8) (a : Std.Usize) (b : Std.Usize) (cap : Std.Usize) (l : Std.Usize) (go : Std.Usize) (it : Std.Usize)  :
    slot.y_a_fast_len2_loop input a b cap l go it ⦃ fun _ => True ⦄ := by
  rw [slot.y_a_fast_len2_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => 40 - s.2.2.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1, x2⟩ _
    simp only [slot.y_a_fast_len2_loop.body, lift, Array.to_slice_mut]
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
    all_goals scalar_tac
  · trivial
@[local step]
theorem fast_len2_spec (input : Slice Std.U8) (a : Std.Usize) (b : Std.Usize) (cap : Std.Usize) :
    slot.y_a_fast_len2 input a b cap ⦃ fun _ => True ⦄ := by
  rw [slot.y_a_fast_len2]
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
  all_goals scalar_tac
@[local step]
theorem fast_len3_loop_spec (input : Slice Std.U8) (a : Std.Usize) (b : Std.Usize) (cap : Std.Usize) (l : Std.Usize) (go : Std.Usize) (it : Std.Usize)  :
    slot.y_a_fast_len3_loop input a b cap l go it ⦃ fun _ => True ⦄ := by
  rw [slot.y_a_fast_len3_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => 40 - s.2.2.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1, x2⟩ _
    simp only [slot.y_a_fast_len3_loop.body, lift, Array.to_slice_mut]
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
    all_goals scalar_tac
  · trivial
@[local step]
theorem fast_len3_spec (input : Slice Std.U8) (a : Std.Usize) (b : Std.Usize) (cap : Std.Usize) :
    slot.y_a_fast_len3 input a b cap ⦃ fun _ => True ⦄ := by
  rw [slot.y_a_fast_len3]
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
  all_goals scalar_tac
@[local step]
theorem hashp_spec (input : Slice Std.U8) (p : Std.Usize) :
    slot.y_a_hashp input p ⦃ fun r => r.val < 65536 ⦄ := by
  rw [slot.y_a_hashp]
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
  all_goals scalar_tac
@[local step]
theorem hashl_spec (input : Slice Std.U8) (p : Std.Usize) :
    slot.y_a_hashl input p ⦃ fun r => r.val < 65536 ⦄ := by
  rw [slot.y_a_hashl]
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
  all_goals scalar_tac
@[local step]
theorem eval_spec (input : Slice Std.U8) (p : Std.Usize) (cs : Std.Usize) (cl : Std.Usize) :
    slot.y_a_eval input p cs cl ⦃ fun _ => True ⦄ := by
  rw [slot.y_a_eval]
  try simp only [lift, Array.to_slice_mut, ite_ok]
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
  all_goals scalar_tac
@[local step]
theorem eval2_spec (input : Slice Std.U8) (p : Std.Usize) (cs : Std.Usize) (cl : Std.Usize) (floor : Std.Usize) :
    slot.y_a_eval2 input p cs cl floor ⦃ fun _ => True ⦄ := by
  rw [slot.y_a_eval2]
  try simp only [lift, Array.to_slice_mut, ite_ok]
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
  all_goals scalar_tac
@[local step]
theorem eval3_spec (input : Slice Std.U8) (p : Std.Usize) (cs : Std.Usize) (cl : Std.Usize) (floor : Std.Usize) :
    slot.y_a_eval3 input p cs cl floor ⦃ fun _ => True ⦄ := by
  rw [slot.y_a_eval3]
  try simp only [lift, Array.to_slice_mut, ite_ok]
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
  all_goals scalar_tac
@[local step]
theorem insert_range_loop_spec (input : Slice Std.U8) (head : Array Std.U32 131072#usize) («to» : Std.Usize) (n : Std.Usize) (p : Std.Usize) (hn : n.val = input.length) :
    slot.y_a_insert_range_loop input head «to» n p ⦃ fun _ => True ⦄ := by
  rw [slot.y_a_insert_range_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => «to».val - s.2.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1⟩ _
    simp only [slot.y_a_insert_range_loop.body, lift, Array.to_slice_mut]
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
    all_goals scalar_tac
  · trivial
@[local step]
theorem insert_range_spec (input : Slice Std.U8) (head : Array Std.U32 131072#usize) («from» : Std.Usize) («to» : Std.Usize) :
    slot.y_a_insert_range input head «from» «to» ⦃ fun _ => True ⦄ := by
  rw [slot.y_a_insert_range]
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
  all_goals scalar_tac
@[local step]
theorem insert_range2_loop_spec (TS_ : Std.Usize) (input : Slice Std.U8) (head : Array Std.U32 131072#usize) («to» : Std.Usize) (n : Std.Usize) (p : Std.Usize) (c : Std.Usize) (hn : n.val = input.length) :
    slot.y_a_insert_range2_loop TS_ input head «to» n p c ⦃ fun _ => True ⦄ := by
  rw [slot.y_a_insert_range2_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => «to».val - s.2.2.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1, x2⟩ _
    simp only [slot.y_a_insert_range2_loop.body, lift, Array.to_slice_mut]
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
    all_goals scalar_tac
  · trivial
@[local step]
theorem insert_range2_spec (TS_ : Std.Usize) (input : Slice Std.U8) (head : Array Std.U32 131072#usize) («from» : Std.Usize) («to» : Std.Usize) :
    slot.y_a_insert_range2 TS_ input head «from» «to» ⦃ fun _ => True ⦄ := by
  rw [slot.y_a_insert_range2]
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
  all_goals scalar_tac
@[local step]
theorem insert_match_spec (IH_ : Std.Usize) (IT_ : Std.Usize) (TS_ : Std.Usize) (input : Slice Std.U8) (head : Array Std.U32 131072#usize) («from» : Std.Usize) («to» : Std.Usize) :
    slot.y_a_insert_match IH_ IT_ TS_ input head «from» «to» ⦃ fun _ => True ⦄ := by
  rw [slot.y_a_insert_match]
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
  all_goals scalar_tac
@[local step]
theorem run_len_spec (ACC_ : Std.U64) (k : Std.Usize) :
    slot.y_a_run_len ACC_ k ⦃ fun _ => True ⦄ := by
  rw [slot.y_a_run_len]
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
  all_goals scalar_tac
@[local step]
theorem q8ok_spec (q : Std.Usize) (d : Std.Usize) :
    slot.y_a_q8ok q d ⦃ fun _ => True ⦄ := by
  rw [slot.y_a_q8ok]
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
  all_goals scalar_tac
@[local step]
theorem bext_loop_spec (input : Slice Std.U8) (p : Std.Usize) (d : Std.Usize) (lim : Std.Usize) (e : Std.Usize) (go : Std.Usize) (it : Std.Usize)  :
    slot.y_a_bext_loop input p d lim e go it ⦃ fun _ => True ⦄ := by
  rw [slot.y_a_bext_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => 40 - s.2.2.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1, x2⟩ _
    simp only [slot.y_a_bext_loop.body, lift, Array.to_slice_mut]
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
    all_goals scalar_tac
  · trivial
@[local step]
theorem bext_spec (input : Slice Std.U8) (lo : Std.Usize) (p : Std.Usize) (d : Std.Usize) (l : Std.Usize) :
    slot.y_a_bext input lo p d l ⦃ fun _ => True ⦄ := by
  rw [slot.y_a_bext]
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
  all_goals scalar_tac
@[local step]
theorem back1_spec (input : Slice Std.U8) (q : Std.Usize) (d : Std.Usize) :
    slot.y_a_back1 input q d ⦃ fun _ => True ⦄ := by
  rw [slot.y_a_back1]
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
  all_goals scalar_tac
@[local step]
theorem tab_step_spec (head : Array Std.U32 131072#usize) (hs : Std.Usize) (hl : Std.Usize) (hs1 : Std.Usize) (hl1 : Std.Usize) (p : Std.Usize) :
    slot.y_a_tab_step head hs hl hs1 hl1 p ⦃ fun _ => True ⦄ := by
  rw [slot.y_a_tab_step]
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
  all_goals scalar_tac
@[local step]
theorem tab_step2_spec (head : Array Std.U32 131072#usize) (hs : Std.Usize) (hl : Std.Usize) (q : Std.Usize) :
    slot.y_a_tab_step2 head hs hl q ⦃ fun _ => True ⦄ := by
  rw [slot.y_a_tab_step2]
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
  all_goals scalar_tac
@[local step]
theorem scan_loop_spec (ACC_ : Std.U64) (input : Slice Std.U8) (head : Array Std.U32 131072#usize) (n : Std.Usize) (p : Std.Usize) (res : Std.Usize) (it : Std.Usize) (hs : Std.Usize) (hl : Std.Usize) (cs : Std.Usize) (cl : Std.Usize) (hn : n.val = input.length) :
    slot.y_a_scan_loop ACC_ input head n p res it hs hl cs cl ⦃ fun _ => True ⦄ := by
  rw [slot.y_a_scan_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => n.val - s.2.2.2.1.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1, x2, x3, x4, x5, x6, x7⟩ _
    simp only [slot.y_a_scan_loop.body, lift, Array.to_slice_mut]
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
    all_goals scalar_tac
  · trivial
@[local step]
theorem scan_spec (ACC_ : Std.U64) (input : Slice Std.U8) (head : Array Std.U32 131072#usize) (pos : Std.Usize) :
    slot.y_a_scan ACC_ input head pos ⦃ fun _ => True ⦄ := by
  rw [slot.y_a_scan]
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
  all_goals scalar_tac
@[local step]
theorem lazy_step_spec (LZT_ : Std.Usize) (input : Slice Std.U8) (head : Array Std.U32 131072#usize) (m : Std.U64) :
    slot.y_a_lazy_step LZT_ input head m ⦃ fun _ => True ⦄ := by
  rw [slot.y_a_lazy_step]
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
  all_goals scalar_tac
@[local step]
theorem lazy_more_loop_spec (LZT_ : Std.Usize) (input : Slice Std.U8) (head : Array Std.U32 131072#usize) (m : Std.U64) (go : Std.Usize) (it : Std.Usize)  :
    slot.y_a_lazy_more_loop LZT_ input head m go it ⦃ fun _ => True ⦄ := by
  rw [slot.y_a_lazy_more_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => slot.Y_A_LZN.val - s.2.2.2.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1, x2, x3⟩ _
    simp only [slot.y_a_lazy_more_loop.body, lift, Array.to_slice_mut]
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
    all_goals scalar_tac
  · trivial
@[local step]
theorem find_spec (ACC_ : Std.U64) (LZT_ : Std.Usize) (input : Slice Std.U8) (head : Array Std.U32 131072#usize) (pos : Std.Usize) :
    slot.y_a_find ACC_ LZT_ input head pos ⦃ fun _ => True ⦄ := by
  rw [slot.y_a_find]
  try simp only [lift, Array.to_slice_mut, ite_ok]
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
  all_goals scalar_tac
def w8 (input : Slice Std.U8) (p : Nat) : Nat :=
  (input.val[p]!).val + (input.val[p + 1]!).val * 256 + (input.val[p + 2]!).val * 65536 +
  (input.val[p + 3]!).val * 16777216 + (input.val[p + 4]!).val * 4294967296 +
  (input.val[p + 5]!).val * 1099511627776 + (input.val[p + 6]!).val * 281474976710656 +
  (input.val[p + 7]!).val * 72057594037927936
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
theorem Matches.add8 {input : Slice Std.U8} {a b l : Nat} (h : Matches input a b l)
    (hw : w8 input (a + l) = w8 input (b + l)) : Matches input a b (l + 8) := by
  have hb := w8_bytes input (a + l) (b + l) hw
  intro k hk
  by_cases hkl : k < l
  · exact h k hkl
  · have := hb (k - l) (by omega)
    rw [show b + k = b + l + (k - l) by omega, show a + k = a + l + (k - l) by omega]
    exact this
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
@[local step]
theorem tw8_spec (input : Slice Std.U8) (p : Std.Usize) (h : p.val + 8 ≤ input.length) :
    slot.y_a_tw8 input p ⦃ fun r => r.val = w8 input p.val ⦄ := by
  rw [slot.y_a_tw8]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  step*
  unfold w8
  rw [getElem!_pos input.val p.val (by scalar_tac), getElem!_pos input.val (p.val + 1) (by scalar_tac),
    getElem!_pos input.val (p.val + 2) (by scalar_tac), getElem!_pos input.val (p.val + 3) (by scalar_tac),
    getElem!_pos input.val (p.val + 4) (by scalar_tac), getElem!_pos input.val (p.val + 5) (by scalar_tac),
    getElem!_pos input.val (p.val + 6) (by scalar_tac), getElem!_pos input.val (p.val + 7) (by scalar_tac)]
  scalar_tac
@[local step]
theorem tw4_spec (input : Slice Std.U8) (p : Std.Usize) (h : p.val + 4 ≤ input.length) :
    slot.y_a_tw4 input p ⦃ fun r => r.val = w4 input p.val ⦄ := by
  rw [slot.y_a_tw4]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  step*
  unfold w4
  rw [getElem!_pos input.val p.val (by scalar_tac), getElem!_pos input.val (p.val + 1) (by scalar_tac),
    getElem!_pos input.val (p.val + 2) (by scalar_tac), getElem!_pos input.val (p.val + 3) (by scalar_tac)]
  scalar_tac
theorem words_eq_loop_spec (input : Slice Std.U8) (a b cap l0 : Std.Usize)
    (ha : a.val + cap.val ≤ input.length) (hb : b.val + cap.val ≤ input.length)
    (hl0 : l0.val ≤ cap.val) (h0 : Matches input a.val b.val l0.val) :
    slot.y_a_words_eq_loop input a b cap l0 ⦃ fun l =>
      l.val ≤ cap.val ∧ Matches input a.val b.val l.val ⦄ := by
  rw [slot.y_a_words_eq_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun l => cap.val - l.val)
    (inv := fun l => l.val ≤ cap.val ∧ Matches input a.val b.val l.val)
  · rintro l ⟨hle, hinv⟩
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.y_a_words_eq_loop.body]
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
    slot.y_a_tail_eq input a b cap l ⦃ fun r => r.val = 1 →
      8 ≤ cap.val ∧ cap.val ≤ l.val + 8 ∧
      w8 input (a.val + (cap.val - 8)) = w8 input (b.val + (cap.val - 8)) ⦄ := by
  rw [slot.y_a_tail_eq]
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
    slot.y_a_short_eq input a b cap ⦃ fun r => r.val = 1 →
      4 ≤ cap.val ∧ cap.val < 8 ∧ w4 input a.val = w4 input b.val ∧
      w4 input (a.val + (cap.val - 4)) = w4 input (b.val + (cap.val - 4)) ⦄ := by
  rw [slot.y_a_short_eq]
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
    slot.y_a_words_eq input a b cap ⦃ fun l =>
      l.val ≤ cap.val ∧ Matches input a.val b.val l.val ⦄ := by
  rw [slot.y_a_words_eq]
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
    slot.y_a_match_len_loop input a b cap l0 ⦃ fun l =>
      l.val ≤ cap.val ∧ Matches input a.val b.val l.val ⦄ := by
  (
  rw [slot.y_a_match_len_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun l => cap.val - l.val)
    (inv := fun l => l.val ≤ cap.val ∧ LZ77.Matches input a.val b.val l.val)
  · rintro l ⟨hle, hinv⟩
    simp only [slot.y_a_match_len_loop.body]
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
  · exact ⟨hl0, h0⟩)
@[local step]
theorem match_len_spec (input : Slice Std.U8) (a b cap : Std.Usize)
    (ha : a.val + cap.val ≤ input.length) (hb : b.val + cap.val ≤ input.length) :
    slot.y_a_match_len input a b cap ⦃ fun l =>
      l.val ≤ cap.val ∧ Matches input a.val b.val l.val ⦄ := by
  rw [slot.y_a_match_len]
  apply Std.WP.spec_bind (words_eq_spec input a b cap ha hb)
  rintro l0 ⟨hle, hm⟩
  exact match_len_loop_spec input a b cap l0 ha hb hle hm
theorem verified_spec (input : Slice Std.U8) (pos d ch : Std.Usize) :
    slot.y_a_verified input pos d ch ⦃ fun b => b = true →
      3 ≤ ch.val ∧ ch.val ≤ 258 ∧ 1 ≤ d.val ∧ d.val ≤ 32768 ∧ d.val ≤ pos.val ∧
      pos.val + ch.val ≤ input.length ∧ Matches input (pos.val - d.val) pos.val ch.val ⦄ := by
  rw [slot.y_a_verified]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  step*
  intro hv
  have hv' : ch.val ≤ v.val := by simpa using hv
  refine ⟨by scalar_tac, by scalar_tac, by scalar_tac, by scalar_tac, by scalar_tac,
    by scalar_tac, ?_⟩
  rw [show pos.val - d.val = i1.val by scalar_tac]
  exact Matches.mono v_post2 hv'
theorem emit_lits_loop_spec (input : Slice Std.U8) (out0 : Slice Std.U32)
    (n cnt1 k0 c0 ntok0 : Std.Usize)
    (hn : n.val = input.length) (hout : input.length ≤ out0.length)
    (hk : k0.val ≤ n.val) (hntok : ntok0.val ≤ k0.val) (hc0 : c0.val = 0)
    (hdec : LZ77.decode (toks out0 ntok0.val) = some ((bytes input).take k0.val)) :
    slot.y_a_emit_lits_loop input out0 n cnt1 k0 c0 ntok0 ⦃ fun r =>
      r.2.1.val ≤ n.val ∧ (k0.val < r.2.1.val ∨ cnt1.val = 0 ∨ k0.val = n.val) ∧
      r.2.2.val ≤ r.2.1.val ∧ r.1.length = out0.length ∧
      LZ77.decode (toks r.1 r.2.2.val) = some ((bytes input).take r.2.1.val) ⦄ := by
  rw [slot.y_a_emit_lits_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => n.val - s.2.1.val)
    (inv := fun s =>
      s.2.1.val ≤ n.val ∧ s.2.1.val = k0.val + s.2.2.1.val ∧ s.2.2.2.val ≤ s.2.1.val ∧
      s.1.length = out0.length ∧
      LZ77.decode (toks s.1 s.2.2.2.val) = some ((bytes input).take s.2.1.val))
  · rintro ⟨out, k, c, ntok⟩ ⟨hkn, hkc, hnt, hlen, hde⟩
    simp only at hkn hkc hnt hlen hde
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.y_a_emit_lits_loop.body]
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
    slot.y_a_emit_lits input out pos0 cnt ntok0 ⦃ fun r =>
      (pos0.val < r.1.2.val ∨ pos0.val = input.length) ∧ r.1.2.val ≤ input.length ∧ r.1.1.val ≤ r.1.2.val ∧
      r.2.length = out.length ∧
      LZ77.decode (toks r.2 r.1.1.val) = some ((bytes input).take r.1.2.val) ⦄ := by
  rw [slot.y_a_emit_lits]
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
    slot.y_a_emit_step input out pos d l lits ntok ⦃ fun r =>
      pos.val < r.1.2.val ∧ r.1.2.val ≤ input.length ∧ r.1.1.val ≤ r.1.2.val ∧
      r.2.length = out.length ∧
      LZ77.decode (toks r.2 r.1.1.val) = some ((bytes input).take r.1.2.val) ⦄ := by
  rw [slot.y_a_emit_step]
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
@[local step]
theorem lane_emit_spec (input : Slice Std.U8) (out : Slice Std.U32) (pos d l lits ntok : Std.Usize)
    (hout : input.length ≤ out.length) (hpos : pos.val < input.length)
    (hntok : ntok.val ≤ pos.val)
    (hdec : LZ77.decode (toks out ntok.val) = some ((bytes input).take pos.val)) :
    slot.y_a_lane_emit input out pos d l lits ntok ⦃ fun r =>
      pos.val < r.1.2.val ∧ r.1.2.val ≤ input.length ∧ r.1.1.val ≤ r.1.2.val ∧
      r.2.length = out.length ∧
      LZ77.decode (toks r.2 r.1.1.val) = some ((bytes input).take r.1.2.val) ⦄ := by
  rw [slot.y_a_lane_emit]
  exact emit_step_spec input out pos d l lits ntok hout hpos hntok hdec
@[local step]
theorem fl_ld8_spec (input : Slice Std.U8) (p : Std.Usize) :
    slot.y_a_fl_ld8 input p ⦃ fun _ => True ⦄ := by
  rw [slot.y_a_fl_ld8]
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
  all_goals scalar_tac
@[local step]
theorem fl_len_loop_spec (input : Slice Std.U8) (a : Std.Usize) (b : Std.Usize) (cap : Std.Usize) (l : Std.Usize) (go : Std.Usize) (it : Std.Usize)  :
    slot.y_a_fl_len_loop input a b cap l go it ⦃ fun _ => True ⦄ := by
  rw [slot.y_a_fl_len_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => 40 - s.2.2.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1, x2⟩ _
    simp only [slot.y_a_fl_len_loop.body, lift, Array.to_slice_mut]
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
    all_goals scalar_tac
  · trivial
@[local step]
theorem fl_len_spec (input : Slice Std.U8) (a : Std.Usize) (b : Std.Usize) (cap : Std.Usize) :
    slot.y_a_fl_len input a b cap ⦃ fun _ => True ⦄ := by
  rw [slot.y_a_fl_len]
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
  all_goals scalar_tac
section
attribute [local step] ite_true_spec
end
section
attribute [local step] ite_true_spec
end
section
attribute [local step] ite_true_spec
end
section
attribute [local step] ite_true_spec
end
section
attribute [local step] ite_true_spec
@[local step]
theorem fl_rle_parse_loop_spec (input : Slice Std.U8) (out0 : Slice Std.U32) (n : Std.Usize) (pos0 : Std.Usize) (ntok0 : Std.Usize)
    (hn : n.val = input.length) (hout : input.length ≤ out0.length)
    (hp : pos0.val ≤ n.val) (hntok : ntok0.val ≤ pos0.val)
    (hdec : LZ77.decode (toks out0 ntok0.val) = some ((bytes input).take pos0.val)) :
    slot.y_a_fl_rle_parse_loop input out0 n pos0 ntok0 ⦃ fun r =>
      r.2.1.val ≤ n.val ∧ r.2.2.val ≤ r.2.1.val ∧ r.1.length = out0.length ∧
      LZ77.decode (toks r.1 r.2.2.val) = some ((bytes input).take r.2.1.val) ⦄ := by
  rw [slot.y_a_fl_rle_parse_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => n.val - s.2.1.val)
    (inv := fun s =>
      s.2.1.val ≤ n.val ∧ s.2.2.val ≤ s.2.1.val ∧ s.1.length = out0.length ∧
      LZ77.decode (toks s.1 s.2.2.val) = some ((bytes input).take s.2.1.val))
  · rintro ⟨out, pos, ntok⟩ ⟨hpn, hnt, hlen, hde⟩
    simp only at hpn hnt hlen hde
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.y_a_fl_rle_parse_loop.body, lift, Array.to_slice_mut, alloc.vec.Vec.deref_mut, bind_tc_ok]
    split
    case isTrue hlt =>
      step*
      all_goals (repeat (first
        | (refine ⟨by scalar_tac, by scalar_tac, by assumption, by assumption, by scalar_tac⟩)
        | (intro hc; (try step*))
        | (casesm* _ × _; (try simp only []); (try step*))
        | (split <;> (try step*))
        | (step <;> (try step*))))
      all_goals (try scalar_tac)
    case isFalse hge =>
      exact ⟨hpn, hnt, hlen, hde⟩
  · exact ⟨hp, hntok, rfl, hdec⟩
end
attribute [local step] fl_rle_parse_loop_spec
section
attribute [local step] ite_true_spec
@[local step]
theorem fl_rle_parse_spec (input : Slice Std.U8) (out : Slice Std.U32)
    (hlen : input.length ≤ out.length) :
    slot.y_a_fl_rle_parse input out ⦃ fun r =>
      r.1.2.val ≤ input.length ∧ r.1.1.val ≤ r.1.2.val ∧ r.2.length = out.length ∧
      LZ77.decode (toks r.2 r.1.1.val) = some ((bytes input).take r.1.2.val) ⦄ := by
  rw [slot.y_a_fl_rle_parse]
  have h0 := decode_nil input out
  try simp only [lift, Array.to_slice_mut, alloc.vec.Vec.deref_mut, bind_tc_ok]
  step*
  all_goals (repeat (first
    | (refine ⟨by scalar_tac, by scalar_tac, by scalar_tac, by assumption⟩)
    | (intro hc; (try step*))
    | (casesm* _ × _; (try simp only []); (try step*))
    | (split <;> (try step*))
    | (step <;> (try step*))))
  all_goals (try scalar_tac)
end
attribute [local step] fl_rle_parse_spec
section
end
section
attribute [local step] ite_true_spec
end
@[local step]
theorem sh_lc_spec (l : Std.Usize) :
    slot.y_a_sh_lc l ⦃ fun _ => True ⦄ := by
  rw [slot.y_a_sh_lc]
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
  all_goals scalar_tac
@[local step]
theorem sh_dc_spec (d : Std.Usize) :
    slot.y_a_sh_dc d ⦃ fun _ => True ⦄ := by
  rw [slot.y_a_sh_dc]
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
  all_goals scalar_tac
@[local step]
theorem sh_add_spec (stats : Array Std.U32 128#usize) (l : Std.Usize) (d : Std.Usize) :
    slot.y_a_sh_add stats l d ⦃ fun _ => True ⦄ := by
  rw [slot.y_a_sh_add]
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
  all_goals scalar_tac
@[local step]
theorem sh_fill_loop_spec (q : Array Std.Usize 320#usize) (end0 best keep l : Std.Usize) :
    slot.y_a_sh_fill_loop q end0 best keep l ⦃ fun _ => True ⦄ := by
  rw [slot.y_a_sh_fill_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => 259 - s.2.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1⟩ _
    simp only [slot.y_a_sh_fill_loop.body, lift, Array.to_slice_mut]
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
    all_goals scalar_tac
  · trivial
@[local step]
theorem sh_fill_spec (q : Array Std.Usize 320#usize) (begin0 end0 best keep : Std.Usize) :
    slot.y_a_sh_fill q begin0 end0 best keep ⦃ fun _ => True ⦄ := by
  rw [slot.y_a_sh_fill]
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
  all_goals scalar_tac
@[local step]
theorem sh_table_loop0_spec (SH_L_ : Std.U32) (SH_BUDGET_ : Std.Usize) (stats : Array Std.U32 128#usize) (q : Array Std.Usize 320#usize)
  (lb : Array Std.Usize 29#usize) (best : Std.Usize) (c : Std.Usize) :
    slot.y_a_sh_table_loop0 SH_L_ SH_BUDGET_ stats q lb best c ⦃ fun _ => True ⦄ := by
  rw [slot.y_a_sh_table_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun s => 29 - s.2.2.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1, x2⟩ _
    simp only [slot.y_a_sh_table_loop0.body, lift, Array.to_slice_mut]
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
    all_goals scalar_tac
  · trivial
@[local step]
theorem sh_table_loop1_spec (SH_D_ : Std.U32) (SH_DM_ : Std.U32) (stats : Array Std.U32 128#usize) (q : Array Std.Usize 320#usize)
  (c : Std.Usize) :
    slot.y_a_sh_table_loop1 SH_D_ SH_DM_ stats q c ⦃ fun _ => True ⦄ := by
  rw [slot.y_a_sh_table_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun s => 30 - s.2.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1⟩ _
    simp only [slot.y_a_sh_table_loop1.body, lift, Array.to_slice_mut]
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
    all_goals scalar_tac
  · trivial
@[local step]
theorem sh_table_spec (SH_L_ : Std.U32) (SH_D_ : Std.U32) (SH_BUDGET_ : Std.Usize) (SH_DM_ : Std.U32) (stats : Array Std.U32 128#usize) (q : Array Std.Usize 320#usize) :
    slot.y_a_sh_table SH_L_ SH_D_ SH_BUDGET_ SH_DM_ stats q ⦃ fun _ => True ⦄ := by
  rw [slot.y_a_sh_table]
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
  all_goals scalar_tac
@[local step]
theorem sh_rle_probe_loop_spec (input : Slice Std.U8) (cache : Array Std.U32 4096#usize)
  (stats : Array Std.U32 128#usize) (n : Std.Usize) (pos : Std.Usize)
  (ntok : Std.Usize) :
    slot.y_a_sh_rle_probe_loop input cache stats n pos ntok ⦃ fun _ => True ⦄ := by
  rw [slot.y_a_sh_rle_probe_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => 4096 - s.2.2.2.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1, x2, x3⟩ _
    simp only [slot.y_a_sh_rle_probe_loop.body, lift, Array.to_slice_mut]
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
    all_goals scalar_tac
  · trivial
@[local step]
theorem sh_rle_probe_spec (input : Slice Std.U8) (cache : Array Std.U32 4096#usize)
  (stats : Array Std.U32 128#usize) :
    slot.y_a_sh_rle_probe input cache stats ⦃ fun _ => True ⦄ := by
  rw [slot.y_a_sh_rle_probe]
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
  all_goals scalar_tac
@[local step]
theorem sh_litrun_loop_spec (cache : Array Std.U32 4096#usize) (ix : Std.Usize) (sum : Std.Usize)
  (k : Std.Usize) :
    slot.y_a_sh_litrun_loop cache ix sum k ⦃ fun _ => True ⦄ := by
  rw [slot.y_a_sh_litrun_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => 4096 - s.2.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1⟩ _
    simp only [slot.y_a_sh_litrun_loop.body, lift, Array.to_slice_mut]
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
    all_goals scalar_tac
  · trivial
@[local step]
theorem sh_litrun_spec (cache : Array Std.U32 4096#usize) (ix : Std.Usize) :
    slot.y_a_sh_litrun cache ix ⦃ fun _ => True ⦄ := by
  rw [slot.y_a_sh_litrun]
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
  all_goals scalar_tac
section
attribute [local step] ite_true_spec
theorem sh_replay_loop_spec (input : Slice Std.U8) (out0 : Slice Std.U32) (cache : Array Std.U32 4096#usize) (q : Array Std.Usize 320#usize)
    (n pos0 ntok0 ix0 rem0 dist0 : Std.Usize)
    (hn : n.val = input.length) (hout : input.length ≤ out0.length)
    (hp : pos0.val ≤ n.val) (hntok : ntok0.val ≤ pos0.val)
    (hdec : LZ77.decode (toks out0 ntok0.val) = some ((bytes input).take pos0.val)) :
    slot.y_a_sh_replay_loop input out0 cache q n pos0 ntok0 ix0 rem0 dist0 ⦃ fun r =>
      r.2.1.val ≤ n.val ∧ r.2.2.val ≤ r.2.1.val ∧ r.1.length = out0.length ∧
      LZ77.decode (toks r.1 r.2.2.val) = some ((bytes input).take r.2.1.val) ⦄ := by
  rw [slot.y_a_sh_replay_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => n.val - s.2.1.val)
    (inv := fun s =>
      s.2.1.val ≤ n.val ∧ s.2.2.1.val ≤ s.2.1.val ∧ s.1.length = out0.length ∧
      LZ77.decode (toks s.1 s.2.2.1.val) = some ((bytes input).take s.2.1.val))
  · rintro ⟨out, pos, ntok, ix, rem, dist⟩ ⟨hpn, hnt, hlen, hde⟩
    simp only at hpn hnt hlen hde
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.y_a_sh_replay_loop.body, lift, Array.to_slice_mut, alloc.vec.Vec.deref_mut, bind_tc_ok]
    split
    case isTrue hlt =>
      step*
      all_goals (repeat (first
        | (refine ⟨by scalar_tac, by scalar_tac, by assumption, by assumption, by scalar_tac⟩)
        | (intro hc; (try step*))
        | (casesm* _ × _; (try simp only []); (try step*))
        | (split <;> (try step*))
        | (step <;> (try step*))))
      all_goals (try scalar_tac)
    case isFalse hge =>
      exact ⟨hpn, hnt, hlen, hde⟩
  · exact ⟨hp, hntok, rfl, hdec⟩
end
section
attribute [local step] ite_true_spec
@[local step]
theorem sh_replay_spec (input : Slice Std.U8) (out : Slice Std.U32) (cache : Array Std.U32 4096#usize) (q : Array Std.Usize 320#usize)
    (hlen : input.length ≤ out.length) :
    slot.y_a_sh_replay input out cache q ⦃ fun r =>
      r.1.2.val ≤ input.length ∧ r.1.1.val ≤ r.1.2.val ∧ r.2.length = out.length ∧
      LZ77.decode (toks r.2 r.1.1.val) = some ((bytes input).take r.1.2.val) ⦄ := by
  rw [slot.y_a_sh_replay]
  have h0 := decode_nil input out
  try simp only [lift, Array.to_slice_mut, alloc.vec.Vec.deref_mut, bind_tc_ok]
  step*
  all_goals (try (step with sh_replay_loop_spec <;> try step*))
  all_goals (repeat (first
    | (refine ⟨by scalar_tac, by scalar_tac, by scalar_tac, by assumption⟩)
    | (intro hc; (try step*))
    | (casesm* _ × _; (try simp only []); (try step*))
    | (split <;> (try step*))
    | (step <;> (try step*))))
  all_goals (try scalar_tac)
end
attribute [local step] sh_replay_spec
section
attribute [local step] ite_true_spec
@[local step]
theorem sh_rle_phase_spec (SH_L_ : Std.U32) (SH_D_ : Std.U32) (SH_BUDGET_ : Std.Usize) (SH_DM_ : Std.U32) (input : Slice Std.U8) (out : Slice Std.U32)
    (hlen : input.length ≤ out.length) :
    slot.y_a_sh_rle_phase SH_L_ SH_D_ SH_BUDGET_ SH_DM_ input out ⦃ fun r =>
      r.1.2.val ≤ input.length ∧ r.1.1.val ≤ r.1.2.val ∧ r.2.length = out.length ∧
      LZ77.decode (toks r.2 r.1.1.val) = some ((bytes input).take r.1.2.val) ⦄ := by
  rw [slot.y_a_sh_rle_phase]
  have h0 := decode_nil input out
  try simp only [lift, Array.to_slice_mut, alloc.vec.Vec.deref_mut, bind_tc_ok]
  step*
  all_goals (repeat (first
    | (refine ⟨by scalar_tac, by scalar_tac, by scalar_tac, by assumption⟩)
    | (intro hc; (try step*))
    | (casesm* _ × _; (try simp only []); (try step*))
    | (split <;> (try step*))
    | (step <;> (try step*))))
  all_goals (try scalar_tac)
end
attribute [local step] sh_rle_phase_spec
section
attribute [local step] ite_true_spec
end
section
attribute [local step] ite_true_spec
end
section
attribute [local step] ite_true_spec
end
section
@[local step]
theorem run_greedy_loop_spec (IH_ : Std.Usize) (IT_ : Std.Usize) (TS_ : Std.Usize) (ACC_ : Std.U64) (LZT_ : Std.Usize) (input : Slice Std.U8) (out0 : Slice Std.U32) (head0 : Array Std.U32 131072#usize) (n : Std.Usize) (pos0 : Std.Usize) (ntok0 : Std.Usize)
    (hn : n.val = input.length) (hout : input.length ≤ out0.length)
    (hp : pos0.val ≤ n.val) (hntok : ntok0.val ≤ pos0.val)
    (hdec : LZ77.decode (toks out0 ntok0.val) = some ((bytes input).take pos0.val)) :
    slot.y_a_run_greedy_loop IH_ IT_ TS_ ACC_ LZT_ input out0 head0 n pos0 ntok0 ⦃ fun r =>
      r.1.val ≤ input.length ∧ r.2.1.length = out0.length ∧
      LZ77.Valid (bytes input) (toks r.2.1 r.1.val) ⦄ := by
  rw [slot.y_a_run_greedy_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => n.val - s.2.2.1.val)
    (inv := fun s =>
      s.2.2.1.val ≤ n.val ∧ s.2.2.2.val ≤ s.2.2.1.val ∧ s.1.length = out0.length ∧
      LZ77.decode (toks s.1 s.2.2.2.val) = some ((bytes input).take s.2.2.1.val))
  · rintro ⟨out, head, pos, ntok⟩ ⟨hpn, hnt, hlen, hde⟩
    simp only at hpn hnt hlen hde
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.y_a_run_greedy_loop.body, lift, Array.to_slice_mut, alloc.vec.Vec.deref_mut, bind_tc_ok]
    split
    case isTrue hlt =>
      step*
      all_goals (repeat (first
        | (refine ⟨by scalar_tac, by scalar_tac, by assumption, by assumption, by scalar_tac⟩)
        | (intro hc; (try step*))
        | (casesm* _ × _; (try simp only []); (try step*))
        | (split <;> (try step*))
        | (step <;> (try step*))))
      all_goals (try scalar_tac)
    case isFalse hge =>
      have hpn' : pos.val = input.length := by scalar_tac
      refine ⟨by scalar_tac, hlen, ?_⟩
      unfold LZ77.Valid
      rw [hde, hpn']
      simp
  · exact ⟨hp, hntok, rfl, hdec⟩
end
attribute [local step] run_greedy_loop_spec
section
attribute [local step] ite_true_spec
@[local step]
theorem run_greedy_spec (IH_ : Std.Usize) (IT_ : Std.Usize) (TS_ : Std.Usize) (ACC_ : Std.U64) (LZT_ : Std.Usize) (input : Slice Std.U8) (out : Slice Std.U32) (head : Array Std.U32 131072#usize) (pos0 : Std.Usize) (ntok0 : Std.Usize)
    (hlen : input.length ≤ out.length)
    (hp : pos0.val ≤ input.length) (hntok : ntok0.val ≤ pos0.val)
    (hdec : LZ77.decode (toks out ntok0.val) = some ((bytes input).take pos0.val)) :
    slot.y_a_run_greedy IH_ IT_ TS_ ACC_ LZT_ input out head pos0 ntok0 ⦃ fun r =>
      r.1.val ≤ input.length ∧
      r.2.1.length = out.length ∧
      LZ77.Valid (bytes input) (toks r.2.1 r.1.val) ⦄ := by
  rw [slot.y_a_run_greedy]
  have h0 := decode_nil input out
  try simp only [lift, Array.to_slice_mut, alloc.vec.Vec.deref_mut, bind_tc_ok]
  step*
  all_goals (repeat (first
    | (refine ⟨by scalar_tac, by scalar_tac, valid_of_decode (by assumption) (by scalar_tac)⟩)
    | (intro hc; (try step*))
    | (casesm* _ × _; (try simp only []); (try step*))
    | (split <;> (try step*))
    | (step <;> (try step*))))
  all_goals (try scalar_tac)
end
attribute [local step] run_greedy_spec
section
attribute [local step] ite_true_spec
@[local step]
theorem main_part_spec (IH_ : Std.Usize) (IT_ : Std.Usize) (TS_ : Std.Usize) (ACC_ : Std.U64) (LZT_ : Std.Usize) (input : Slice Std.U8) (out : Slice Std.U32) (m : Std.Usize) (pos0 : Std.Usize) (ntok0 : Std.Usize)
    (hlen : input.length ≤ out.length)
    (hp : pos0.val ≤ input.length) (hntok : ntok0.val ≤ pos0.val)
    (hdec : LZ77.decode (toks out ntok0.val) = some ((bytes input).take pos0.val)) :
    slot.y_a_main_part IH_ IT_ TS_ ACC_ LZT_ input out m pos0 ntok0 ⦃ fun r =>
      r.1.val ≤ input.length ∧
      r.2.length = out.length ∧
      LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
  rw [slot.y_a_main_part]
  have h0 := decode_nil input out
  try simp only [lift, Array.to_slice_mut, alloc.vec.Vec.deref_mut, bind_tc_ok]
  step*
  all_goals (repeat (first
    | (refine ⟨by scalar_tac, by scalar_tac, valid_of_decode (by assumption) (by scalar_tac)⟩)
    | (intro hc; (try step*))
    | (casesm* _ × _; (try simp only []); (try step*))
    | (split <;> (try step*))
    | (step <;> (try step*))))
  all_goals (try scalar_tac)
end
attribute [local step] main_part_spec
section
attribute [local step] ite_true_spec
end
end EA
namespace EB
open EA
attribute [local step] EA.match_len_spec EA.verified_spec EA.emit_lits_spec EA.emit_step_spec EA.lane_emit_spec
open Aeneas Aeneas.Std Result ControlFlow
set_option maxRecDepth 8192
set_option maxHeartbeats 4000000
open LZ77 (toks bytes bytes_length bytes_getElem! Matches emit_lit emit_match ite_ok)
theorem decode_nil (input : Slice Std.U8) (out : Slice Std.U32) :
    LZ77.decode (toks out (0#usize).val) = some ((bytes input).take (0#usize).val) := by
  simp [toks, LZ77.decode]
theorem valid_of_decode {input : Slice Std.U8} {o : Slice Std.U32} {t p : Std.Usize}
    (hde : LZ77.decode (toks o t.val) = some ((bytes input).take p.val)) (hp : p.val = input.length) :
    LZ77.Valid (bytes input) (toks o t.val) := by
  unfold LZ77.Valid
  rw [hde, hp]
  simp
theorem spec_ite_cut {α : Type} (c : Prop) [Decidable c] (a b : Result α) (Q : α → Prop)
    (ha : c → a ⦃ Q ⦄) (hb : ¬c → b ⦃ Q ⦄) : (if c then a else b) ⦃ Q ⦄ := by
  by_cases h : c
  · rw [if_pos h]; exact ha h
  · rw [if_neg h]; exact hb h
theorem ite_prod_spec {α β : Type} (c : Prop) [Decidable c] (A B : Result (α × β))
    (hA : c → A ⦃ fun _ => True ⦄) (hB : ¬c → B ⦃ fun _ => True ⦄) :
    (if c then A else B) ⦃ fun _ => True ⦄ := by
  by_cases h : c
  · rw [if_pos h]; exact hA h
  · rw [if_neg h]; exact hB h
theorem ite_true_spec {α : Type} (c : Prop) [Decidable c] (A B : Result α)
    (hA : c → A ⦃ fun _ => True ⦄) (hB : ¬c → B ⦃ fun _ => True ⦄) :
    (if c then A else B) ⦃ fun _ => True ⦄ := by
  by_cases h : c
  · rw [if_pos h]; exact hA h
  · rw [if_neg h]; exact hB h
@[local step]
theorem ld4_spec (input : Slice Std.U8) (p : Std.Usize) :
    slot.y_b_ld4 input p ⦃ fun _ => True ⦄ := by
  rw [slot.y_b_ld4]
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
  all_goals scalar_tac
@[local step]
theorem ld8_spec (input : Slice Std.U8) (p : Std.Usize) :
    slot.y_b_ld8 input p ⦃ fun _ => True ⦄ := by
  rw [slot.y_b_ld8]
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
  all_goals scalar_tac
@[local step]
theorem first_diff_spec (x : Std.U64) :
    slot.y_b_first_diff x ⦃ fun _ => True ⦄ := by
  rw [slot.y_b_first_diff]
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
  all_goals scalar_tac
@[local step]
theorem fast_len_loop_spec (input : Slice Std.U8) (a : Std.Usize) (b : Std.Usize) (cap : Std.Usize) (l : Std.Usize) (go : Std.Usize) (it : Std.Usize)  :
    slot.y_b_fast_len_loop input a b cap l go it ⦃ fun _ => True ⦄ := by
  rw [slot.y_b_fast_len_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => 40 - s.2.2.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1, x2⟩ _
    simp only [slot.y_b_fast_len_loop.body, lift, Array.to_slice_mut]
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
    all_goals scalar_tac
  · trivial
@[local step]
theorem fast_len_spec (input : Slice Std.U8) (a : Std.Usize) (b : Std.Usize) (cap : Std.Usize) :
    slot.y_b_fast_len input a b cap ⦃ fun _ => True ⦄ := by
  rw [slot.y_b_fast_len]
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
  all_goals scalar_tac
@[local step]
theorem hashp_spec (input : Slice Std.U8) (p : Std.Usize) (hs : Std.U32) :
    slot.y_b_hashp input p hs ⦃ fun _ => True ⦄ := by
  rw [slot.y_b_hashp]
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
  all_goals scalar_tac
@[local step]
theorem hash3_spec (w : Std.U32) :
    slot.y_b_hash3 w ⦃ fun _ => True ⦄ := by
  rw [slot.y_b_hash3]
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
  all_goals scalar_tac
@[local step]
theorem dextra_spec (d : Std.Usize) :
    slot.y_b_dextra d ⦃ fun _ => True ⦄ := by
  rw [slot.y_b_dextra]
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
  all_goals scalar_tac
@[local step]
theorem lextra_spec (l : Std.Usize) :
    slot.y_b_lextra l ⦃ fun _ => True ⦄ := by
  rw [slot.y_b_lextra]
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
  all_goals scalar_tac
@[local step]
theorem score_spec (l : Std.Usize) (d : Std.Usize) (cq : Std.Usize) :
    slot.y_b_score l d cq ⦃ fun _ => True ⦄ := by
  rw [slot.y_b_score]
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
  all_goals scalar_tac
@[local step]
theorem lg8_spec (x : Std.U32) :
    slot.y_b_lg8 x ⦃ fun _ => True ⦄ := by
  rw [slot.y_b_lg8]
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
  all_goals scalar_tac
@[local step]
theorem sample_loop_spec (input : Slice Std.U8) (h : Array Std.U32 256#usize) (n : Std.Usize) (st : Std.Usize) (k : Std.Usize) (c : Std.Usize) (hn : n.val = input.length) :
    slot.y_b_sample_loop input h n st k c ⦃ fun _ => True ⦄ := by
  rw [slot.y_b_sample_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => 8192 - s.2.2.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1, x2⟩ _
    simp only [slot.y_b_sample_loop.body, lift, Array.to_slice_mut]
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
    all_goals scalar_tac
  · trivial
@[local step]
theorem sample_spec (input : Slice Std.U8) (h : Array Std.U32 256#usize) :
    slot.y_b_sample input h ⦃ fun _ => True ⦄ := by
  rw [slot.y_b_sample]
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
  all_goals scalar_tac
@[local step]
theorem entropy256_loop_spec (h : Array Std.U32 256#usize) (tot : Std.U64) (acc : Std.U64) (i : Std.Usize)  :
    slot.y_b_entropy256_loop h tot acc i ⦃ fun _ => True ⦄ := by
  rw [slot.y_b_entropy256_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => 256 - s.2.2.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1, x2⟩ _
    simp only [slot.y_b_entropy256_loop.body, lift, Array.to_slice_mut]
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
    all_goals scalar_tac
  · trivial
@[local step]
theorem entropy256_spec (h : Array Std.U32 256#usize) :
    slot.y_b_entropy256 h ⦃ fun _ => True ⦄ := by
  rw [slot.y_b_entropy256]
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
  all_goals scalar_tac
@[local step]
theorem share_loop_spec (h : Array Std.U32 256#usize) (lo : Std.Usize) (hi : Std.Usize) (t : Std.Usize) (s : Std.Usize) (i : Std.Usize)  :
    slot.y_b_share_loop h lo hi t s i ⦃ fun _ => True ⦄ := by
  rw [slot.y_b_share_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => 256 - s.2.2.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1, x2⟩ _
    simp only [slot.y_b_share_loop.body, lift, Array.to_slice_mut]
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
    all_goals scalar_tac
  · trivial
@[local step]
theorem share_spec (h : Array Std.U32 256#usize) (lo : Std.Usize) (hi : Std.Usize) :
    slot.y_b_share h lo hi ⦃ fun _ => True ⦄ := by
  rw [slot.y_b_share]
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
  all_goals scalar_tac
@[local step]
theorem low_mode_spec (e : Std.Usize) (dp : slot.Y_B_Params) :
    slot.y_b_low_mode e dp ⦃ fun _ => True ⦄ := by
  rw [slot.y_b_low_mode]
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
  all_goals scalar_tac
@[local step]
theorem lit_cost_spec (e : Std.Usize) (low : Std.Usize) (dp : slot.Y_B_Params) :
    slot.y_b_lit_cost e low dp ⦃ fun _ => True ⦄ := by
  rw [slot.y_b_lit_cost]
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
  all_goals scalar_tac
@[local step]
theorem m3_mode_spec (h : Array Std.U32 256#usize) (e : Std.Usize) (dp : slot.Y_B_Params) :
    slot.y_b_m3_mode h e dp ⦃ fun _ => True ⦄ := by
  rw [slot.y_b_m3_mode]
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
  all_goals scalar_tac
@[local step]
theorem h3_mode_spec (h : Array Std.U32 256#usize) (e : Std.Usize) (dp : slot.Y_B_Params) :
    slot.y_b_h3_mode h e dp ⦃ fun _ => True ⦄ := by
  rw [slot.y_b_h3_mode]
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
  all_goals scalar_tac
@[local step]
theorem numeric_spec (h : Array Std.U32 256#usize) (n : Std.Usize) (low : Std.Usize) (dp : slot.Y_B_Params) :
    slot.y_b_numeric h n low dp ⦃ fun _ => True ⦄ := by
  rw [slot.y_b_numeric]
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
  all_goals scalar_tac
@[local step]
theorem walk_loop_spec (input : Slice Std.U8) (prev : Array Std.U32 65536#usize) (pos : Std.Usize) (cap : Std.Usize) (probes : Std.Usize) (litq : Std.Usize) (lim : Std.Usize) (stop : Std.Usize) (cur : Std.Usize) (k : Std.Usize) (bl : Std.Usize) (bs : Std.Usize) (bd : Std.Usize) (off : Std.Usize) (want : Std.U32)  :
    slot.y_b_walk_loop input prev pos cap probes litq lim stop cur k bl bs bd off want ⦃ fun _ => True ⦄ := by
  rw [slot.y_b_walk_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => probes.val - s.2.1.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1, x2, x3, x4, x5, x6⟩ _
    simp only [slot.y_b_walk_loop.body, lift, Array.to_slice_mut]
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
    all_goals scalar_tac
  · trivial
@[local step]
theorem walk_spec (input : Slice Std.U8) (prev : Array Std.U32 65536#usize) (pos : Std.Usize) (start : Std.Usize) (cap : Std.Usize) (probes : Std.Usize) (bl0 : Std.Usize) (bs0 : Std.Usize) (litq : Std.Usize) :
    slot.y_b_walk input prev pos start cap probes bl0 bs0 litq ⦃ fun _ => True ⦄ := by
  rw [slot.y_b_walk]
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
  all_goals scalar_tac
@[local step]
theorem lwalk_loop_spec (input : Slice Std.U8) (prev : Array Std.U32 65536#usize) (pos : Std.Usize) (cap : Std.Usize) (probes : Std.Usize) (litq : Std.Usize) (lim : Std.Usize) (stop : Std.Usize) (cur : Std.Usize) (k : Std.Usize) (bl : Std.Usize) (bs : Std.Usize) (bd : Std.Usize) (off : Std.Usize) (want : Std.U32)  :
    slot.y_b_lwalk_loop input prev pos cap probes litq lim stop cur k bl bs bd off want ⦃ fun _ => True ⦄ := by
  rw [slot.y_b_lwalk_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => probes.val - s.2.1.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1, x2, x3, x4, x5, x6⟩ _
    simp only [slot.y_b_lwalk_loop.body, lift, Array.to_slice_mut]
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
    all_goals scalar_tac
  · trivial
@[local step]
theorem lwalk_spec (input : Slice Std.U8) (prev : Array Std.U32 65536#usize) (pos : Std.Usize) (start : Std.Usize) (cap : Std.Usize) (probes : Std.Usize) (bl0 : Std.Usize) (bs0 : Std.Usize) (litq : Std.Usize) :
    slot.y_b_lwalk input prev pos start cap probes bl0 bs0 litq ⦃ fun _ => True ⦄ := by
  rw [slot.y_b_lwalk]
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
  all_goals scalar_tac
@[local step]
theorem cand3_spec (input : Slice Std.U8) (pos : Std.Usize) (s3 : Std.Usize) (cap : Std.Usize) (bs0 : Std.Usize) (litq : Std.Usize) :
    slot.y_b_cand3 input pos s3 cap bs0 litq ⦃ fun _ => True ⦄ := by
  rw [slot.y_b_cand3]
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
  all_goals scalar_tac
@[local step]
theorem cand3_long_spec (input : Slice Std.U8) (pos : Std.Usize) (s3 : Std.Usize) (cap : Std.Usize) (bs0 : Std.Usize) (litq : Std.Usize) :
    slot.y_b_cand3_long input pos s3 cap bs0 litq ⦃ fun _ => True ⦄ := by
  rw [slot.y_b_cand3_long]
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
  all_goals scalar_tac
@[local step]
theorem upd3_spec (input : Slice Std.U8) (head3 : Array Std.U32 16384#usize) (pos : Std.Usize) (on : Std.Usize) :
    slot.y_b_upd3 input head3 pos on ⦃ fun _ => True ⦄ := by
  rw [slot.y_b_upd3]
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
  all_goals scalar_tac
@[local step]
theorem suffix_walk_loop_spec (input : Slice Std.U8) (prev : Array Std.U32 65536#usize)
    (pos cap litq off q lim cur best k : Std.Usize) :
    slot.y_b_suffix_walk_loop input prev pos cap litq off q lim cur best k ⦃ fun _ => True ⦄ := by
  rw [slot.y_b_suffix_walk_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => slot.Y_B_SUFFIX_DEPTH.val - s.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨cur, best, k⟩ _
    simp only [slot.y_b_suffix_walk_loop.body, lift, Array.to_slice_mut]
    step*
    repeat (first
      | (intro hc; try step*)
      | (split <;> try step*)
      | (casesm* _ × _; try step*)
      | (apply spec_ite_cut <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals scalar_tac
  · trivial
@[local step]
theorem suffix_walk_spec (input : Slice Std.U8) (prev : Array Std.U32 65536#usize)
    (pos cap best0 litq probes : Std.Usize) :
    slot.y_b_suffix_walk input prev pos cap best0 litq probes ⦃ fun _ => True ⦄ := by
  rw [slot.y_b_suffix_walk]
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat (first
    | (intro hc; try step*)
    | (split <;> try step*)
    | (casesm* _ × _; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals scalar_tac
@[local step]
theorem search_spec (input : Slice Std.U8) (head : Array Std.U32 65536#usize) (prev : Array Std.U32 65536#usize) (head3 : Array Std.U32 16384#usize) (shorts : Array Std.U32 4096#usize) (pos : Std.Usize) (probes : Std.Usize) (bl0 : Std.Usize) (bs0 : Std.Usize) (litq : Std.Usize) (hs : Std.U32) (h3on : Std.Usize) :
    slot.y_b_search input head prev head3 shorts pos probes bl0 bs0 litq hs h3on ⦃ fun _ => True ⦄ := by
  rw [slot.y_b_search]
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
  all_goals scalar_tac
@[local step]
theorem lazy_probe_spec (input : Slice Std.U8) (head : Array Std.U32 65536#usize) (prev : Array Std.U32 65536#usize) (head3 : Array Std.U32 16384#usize) (q : Std.Usize) (go : Std.Usize) (p2 : Std.Usize) (l1 : Std.Usize) (sv1 : Std.Usize) (litq : Std.Usize) (hs : Std.U32) (h3on : Std.Usize) :
    slot.y_b_lazy_probe input head prev head3 q go p2 l1 sv1 litq hs h3on ⦃ fun _ => True ⦄ := by
  rw [slot.y_b_lazy_probe]
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
  all_goals scalar_tac
@[local step]
theorem ext_ok_spec (input : Slice Std.U8) (pos : Std.Usize) (l2 : Std.Usize) (d2 : Std.Usize) :
    slot.y_b_ext_ok input pos l2 d2 ⦃ fun _ => True ⦄ := by
  rw [slot.y_b_ext_ok]
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
  all_goals scalar_tac
@[local step]
theorem fl_mode_spec (input : Slice Std.U8) (st : Std.U64) (dp : slot.Y_B_Params) :
    slot.y_b_fl_mode input st dp ⦃ fun _ => True ⦄ := by
  rw [slot.y_b_fl_mode]
  try simp only [lift, Array.to_slice_mut, ite_ok]
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
  all_goals scalar_tac
section
attribute [local step] ite_true_spec
@[local step]
theorem fl_lit_parse_spec (input : Slice Std.U8) (out : Slice Std.U32)
    (hlen : input.length ≤ out.length) :
    slot.y_b_fl_lit_parse input out ⦃ fun r =>
      r.1.2.val ≤ input.length ∧ r.1.1.val ≤ r.1.2.val ∧ r.2.length = out.length ∧
      LZ77.decode (toks r.2 r.1.1.val) = some ((bytes input).take r.1.2.val) ⦄ := by
  rw [slot.y_b_fl_lit_parse]
  have h0 := decode_nil input out
  try simp only [lift, Array.to_slice_mut, alloc.vec.Vec.deref_mut, bind_tc_ok]
  step*
  all_goals (repeat (first
    | (refine ⟨by scalar_tac, by scalar_tac, by scalar_tac, by assumption⟩)
    | (intro hc; (try step*))
    | (casesm* _ × _; (try simp only []); (try step*))
    | (split <;> (try step*))
    | (step <;> (try step*))))
  all_goals (try scalar_tac)
end
attribute [local step] fl_lit_parse_spec
section
attribute [local step] ite_true_spec
end
section
attribute [local step] ite_true_spec
end
section
attribute [local step] ite_true_spec
end
section
attribute [local step] ite_true_spec
end
section
attribute [local step] ite_true_spec
end
section
attribute [local step] ite_true_spec
end
section
attribute [local step] ite_true_spec
@[local step]
theorem fl_part_spec (input : Slice Std.U8) (out : Slice Std.U32) (mc : Std.Usize) (fh : Array Std.U32 256#usize) (dp : slot.Y_B_Params)
    (hlen : input.length ≤ out.length) :
    slot.y_b_fl_part input out mc fh dp ⦃ fun r =>
      r.1.2.val ≤ input.length ∧ r.1.1.val ≤ r.1.2.val ∧ r.2.length = out.length ∧
      LZ77.decode (toks r.2 r.1.1.val) = some ((bytes input).take r.1.2.val) ⦄ := by
  rw [slot.y_b_fl_part]
  have h0 := decode_nil input out
  try simp only [lift, Array.to_slice_mut, alloc.vec.Vec.deref_mut, bind_tc_ok]
  step*
  all_goals (repeat (first
    | (refine ⟨by scalar_tac, by scalar_tac, by scalar_tac, by assumption⟩)
    | (intro hc; (try step*))
    | (casesm* _ × _; (try simp only []); (try step*))
    | (split <;> (try step*))
    | (step <;> (try step*))))
  all_goals (try scalar_tac)
end
attribute [local step] fl_part_spec
@[local step]
theorem prepare_loop_spec (input : Slice Std.U8) (head : Array Std.U32 65536#usize) (prev : Array Std.U32 65536#usize) (head3 : Array Std.U32 16384#usize) (shorts : Array Std.U32 4096#usize) (hs : Std.U32) (h3on : Std.Usize) («end» : Std.Usize) (p : Std.Usize)  :
    slot.y_b_prepare_loop input head prev head3 shorts h3on hs «end» p ⦃ fun _ => True ⦄ := by
  rw [slot.y_b_prepare_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => «end».val - s.2.2.2.2.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1, x2, x3, x4⟩ _
    simp only [slot.y_b_prepare_loop.body, lift, Array.to_slice_mut]
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
    all_goals scalar_tac
  · trivial
@[local step]
theorem prepare_spec (input : Slice Std.U8) (head : Array Std.U32 65536#usize) (prev : Array Std.U32 65536#usize) (head3 : Array Std.U32 16384#usize) (shorts : Array Std.U32 4096#usize) («from» : Std.Usize) (pos : Std.Usize) (hs : Std.U32) (h3on : Std.Usize) :
    slot.y_b_prepare input head prev head3 shorts «from» pos hs h3on ⦃ fun _ => True ⦄ := by
  rw [slot.y_b_prepare]
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
  all_goals scalar_tac
open LZ77
theorem copyN_take_prefix (acc : List Nat) (d : Nat) :
    ∀ n, (copyN acc d n).take acc.length = acc := by
  intro n
  induction n with
  | zero => simp [copyN]
  | succ m ih =>
    simp only [copyN]
    rw [List.take_append_of_le_length (by simp)]
    exact ih
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
def BackDec (input : Slice Std.U8) (out : Slice Std.U32) (nt p : Nat) : Prop :=
  p ≤ input.length ∧ nt ≤ p ∧ input.length ≤ out.length ∧
    LZ77.decode (toks out nt) = some ((bytes input).take p)
theorem BackDec.pop_lit {s : Slice Std.U8} {out : Slice Std.U32} {nt p : Nat} (h : BackDec s out nt p)
    (h0 : 0 < nt) (hle : nt ≤ out.length) (ht : (out.val[nt - 1]!).val < 256) :
    1 ≤ p ∧ BackDec s out (nt - 1) (p - 1) := by
  obtain ⟨hps, hntp, hso, hde⟩ := h
  rw [toks_pop out nt h0 hle] at hde
  obtain ⟨hp1, hde'⟩ := decode_pop_lit (by simpa using hps) hde ht
  exact ⟨hp1, by omega, by omega, hso, hde'⟩
theorem BackDec.pop_match {s : Slice Std.U8} {out : Slice Std.U32} {nt p : Nat} (h : BackDec s out nt p)
    (h0 : 0 < nt) (hle : nt ≤ out.length) (ht : 256 ≤ (out.val[nt - 1]!).val) :
    tokLen (out.val[nt - 1]!).val ≤ p ∧
      BackDec s out (nt - 1) (p - tokLen (out.val[nt - 1]!).val) := by
  obtain ⟨hps, hntp, hso, hde⟩ := h
  rw [toks_pop out nt h0 hle] at hde
  obtain ⟨hw, hde'⟩ := decode_pop_match (by simpa using hps) hde ht
  have hlen := decode_length_le hde'
  rw [toks_length out (nt - 1) (by omega), List.length_take, bytes_length] at hlen
  exact ⟨hw, by omega, by omega, hso, hde'⟩
def MergeInv (input : Slice Std.U8) (out : Slice Std.U32) (P E : Nat) (p t len : Nat) : Prop :=
  BackDec input out t p ∧ p ≤ P ∧ p + len = E
theorem MergeInv.pop {input : Slice Std.U8} {out : Slice Std.U32} {P E : Nat}
    {p t len i1 w p1 len1 : Std.Usize} {tok : Std.U32}
    (h : MergeInv input out P E p.val t.val len.val)
    (hi1 : i1.val = t.val - 1) (ht0 : 0 < t.val) (htl : t.val ≤ out.length)
    (hi1l : i1.val < out.val.length) (htok : tok = out.val[i1.val])
    (hwlit : tok.val < 256 → w.val = 1)
    (hwmat : ¬tok.val < 256 → 16777216 ≤ tok.val ∧ w.val = (tok.val - 16777216) % 256 + 3)
    (hw0 : 0 < w.val) (hwp : w.val ≤ p.val) (hlenw : len.val + w.val ≤ 258)
    (hp1 : p1.val = p.val - w.val) (hlen1 : len1.val = len.val + w.val) :
    MergeInv input out P E p1.val i1.val len1.val := by
  obtain ⟨hd, hpP, hE⟩ := h
  have hv : (out.val[t.val - 1]!).val = tok.val := by
    rw [← hi1, getElem!_pos out.val i1.val hi1l, ← htok]
  have hd' : BackDec input out (t.val - 1) (p.val - w.val) := by
    by_cases hlit : tok.val < 256
    · have hw1 : w.val = 1 := hwlit hlit
      rw [hw1]
      exact (BackDec.pop_lit hd ht0 htl (by rw [hv]; exact hlit)).2
    · obtain ⟨hm, hw⟩ := hwmat hlit
      have hwm : w.val = LZ77.tokLen (out.val[t.val - 1]!).val := by
        rw [hv]; simp only [LZ77.tokLen, LZ77.MATCH_BASE]; exact hw
      rw [hwm]
      exact (BackDec.pop_match hd ht0 htl (by rw [hv]; omega)).2
  rw [hi1, hp1, hlen1]
  exact ⟨hd', by omega, by omega⟩
@[local step]
theorem back_emit_loop_spec (input : Slice Std.U8) (out : Slice Std.U32) (d : Std.Usize) (good : Bool) (p t len k : Std.Usize)
    (P E : Nat) (hinv : MergeInv input out P E p.val t.val len.val) :
    slot.y_b_back_emit_loop input out d good p t len k ⦃ fun r =>
      MergeInv input out P E r.1.val r.2.1.val r.2.2.val ⦄ := by
  rw [slot.y_b_back_emit_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => slot.Y_B_BACK_LIMIT.val - s.2.2.2.2.val)
    (inv := fun s => MergeInv input out P E s.2.1.val s.2.2.1.val s.2.2.2.1.val)
  · rintro ⟨good, p, t, len, k⟩ hi
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    have hib := hi
    obtain ⟨⟨hpn, htp, hout, hde⟩, hpP, hE⟩ := hib
    simp only [slot.y_b_back_emit_loop.body]
    step*
    all_goals (repeat (first
      | (refine ⟨MergeInv.pop (w := 1#usize) hi (by scalar_tac) (by scalar_tac) (by scalar_tac) (by scalar_tac)
          (by assumption) (by intro hc; scalar_tac) (by intro hc; constructor <;> scalar_tac) (by scalar_tac) (by scalar_tac) (by scalar_tac)
          (by scalar_tac) (by scalar_tac), by scalar_tac⟩)
      | (refine ⟨MergeInv.pop (w := UScalar.cast .Usize x) hi (by scalar_tac) (by scalar_tac) (by scalar_tac) (by scalar_tac)
          (by assumption) (by intro hc; scalar_tac) (by intro hc; constructor <;> scalar_tac) (by scalar_tac) (by scalar_tac) (by scalar_tac)
          (by scalar_tac) (by scalar_tac), by scalar_tac⟩)
      | (exact hi)
      | (refine ⟨hi, by scalar_tac⟩)
      | (intro hc; try step*)
      | (casesm* _ × _; try step*)
      | (split <;> try step*)
      | (apply spec_ite_cut <;> intro hc <;> try step*)
      | (step <;> try step*)))
    all_goals try scalar_tac
  · exact hinv
theorem back_verified_eq (input : Slice Std.U8) (pos d len : Std.Usize) :
    slot.y_b_back_verified input pos d len = slot.y_a_verified input pos d len := by
  unfold slot.y_b_back_verified slot.y_a_verified
  rfl
@[local step]
theorem back_verified_spec (input : Slice Std.U8) (pos d ch : Std.Usize) :
    slot.y_b_back_verified input pos d ch ⦃ fun b => b = true →
      3 ≤ ch.val ∧ ch.val ≤ 258 ∧ 1 ≤ d.val ∧ d.val ≤ 32768 ∧ d.val ≤ pos.val ∧
      pos.val + ch.val ≤ input.length ∧ Matches input (pos.val - d.val) pos.val ch.val ⦄ := by
  rw [back_verified_eq]
  exact verified_spec input pos d ch
theorem back_emit_loop_false_eq (input : Slice Std.U8) (out : Slice Std.U32) (d pos ntok l k : Std.Usize) :
    slot.y_b_back_emit_loop input out d false pos ntok l k = ok (pos, ntok, l) := by
  rw [slot.y_b_back_emit_loop, Std.loop]
  simp only [slot.y_b_back_emit_loop.body, Bool.false_eq_true, if_false]
@[local step]
theorem back_emit_loop_init_spec (input : Slice Std.U8) (out : Slice Std.U32) (d : Std.Usize)
    (good : Bool) (pos ntok l k : Std.Usize)
    (hout : input.length ≤ out.length) (hpos : pos.val < input.length)
    (hntok : ntok.val ≤ pos.val)
    (hdec : LZ77.decode (toks out ntok.val) = some ((bytes input).take pos.val)) :
    slot.y_b_back_emit_loop input out d good pos ntok l k ⦃ fun r =>
      r.1.val ≤ pos.val ∧ r.2.1.val ≤ r.1.val ∧ r.1.val + r.2.2.val = pos.val + l.val ∧
      LZ77.decode (toks out r.2.1.val) = some ((bytes input).take r.1.val) ∧
      (good = false → r.1 = pos) ⦄ := by
  obtain ⟨⟨p, t, len⟩, heq, ⟨⟨hpn, htp, hso, hde⟩, hpP, hE⟩⟩ :=
    Std.WP.spec_imp_exists (back_emit_loop_spec input out d good pos ntok l k pos.val (pos.val + l.val)
      ⟨⟨by omega, hntok, hout, hdec⟩, le_refl _, rfl⟩)
  apply Std.WP.exists_imp_spec
  refine ⟨(p, t, len), heq, hpP, htp, hE, hde, ?_⟩
  intro hg
  subst good
  rw [back_emit_loop_false_eq] at heq
  exact (Prod.mk.inj (Result.ok.inj heq)).1.symm
@[local step]
theorem merge_good_spec (l : Std.Usize) :
    (if l >= 3#usize then ok (decide (l <= 258#usize)) else ok false) ⦃ fun b =>
      b = true → 3 ≤ l.val ∧ l.val ≤ 258 ⦄ := by
  split <;> simp only [Std.WP.spec_ok]
  · intro h; constructor <;> scalar_tac
  · simp
@[local step]
theorem back_emit_spec (input : Slice Std.U8) (out : Slice Std.U32) (pos d l lits ntok : Std.Usize)
    (hout : input.length ≤ out.length) (hpos : pos.val < input.length)
    (hntok : ntok.val ≤ pos.val)
    (hdec : LZ77.decode (toks out ntok.val) = some ((bytes input).take pos.val)) :
    slot.y_b_back_emit input out pos d l lits ntok ⦃ fun r =>
      pos.val < r.1.2.val ∧ r.1.2.val ≤ input.length ∧ r.1.1.val ≤ r.1.2.val ∧
      r.2.length = out.length ∧
      LZ77.decode (toks r.2 r.1.1.val) = some ((bytes input).take r.1.2.val) ⦄ := by
  rw [slot.y_b_back_emit]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  step*
  have hgood : good = true := by cases good <;> simp_all
  obtain ⟨hl3, hl258⟩ := good_post hgood
  obtain ⟨hlen3, hlen258, hd1, hdmax, hdpos, hend, hm⟩ := b_post (by assumption)
  have htok : i6.val = LZ77.mkMatch d.val len.val := by
    simp only [LZ77.mkMatch, LZ77.MATCH_BASE, i6_post, i3_post, i2_post]
    scalar_tac
  refine ⟨by scalar_tac, by scalar_tac, by scalar_tac,
    by rw [out1_post]; simp [Std.Slice.set_val_eq], ?_⟩
  rw [out1_post, show i7.val = t.val + 1 by scalar_tac,
    show i8.val = p.val + len.val by scalar_tac]
  exact emit_match input out t p.val d.val len.val i6 p_post4 (by scalar_tac) hd1 hdpos hdmax
    hlen3 hlen258 hend hm htok
@[local step]
theorem merge_emit_spec (input : Slice Std.U8) (out : Slice Std.U32) (pos d l lits ntok lz : Std.Usize)
    (hout : input.length ≤ out.length) (hpos : pos.val < input.length)
    (hntok : ntok.val ≤ pos.val)
    (hdec : LZ77.decode (toks out ntok.val) = some ((bytes input).take pos.val)) :
    slot.y_b_merge_emit input out pos d l lits ntok lz ⦃ fun r =>
      pos.val < r.1.2.val ∧ r.1.2.val ≤ input.length ∧ r.1.1.val ≤ r.1.2.val ∧
      r.2.length = out.length ∧
      LZ77.decode (toks r.2 r.1.1.val) = some ((bytes input).take r.1.2.val) ⦄ := by
  rw [slot.y_b_merge_emit]
  split
  · exact emit_step_spec input out pos d l lits ntok hout hpos hntok hdec
  · exact back_emit_spec input out pos d l lits ntok hout hpos hntok hdec
section
attribute [local step] ite_true_spec
@[local step]
theorem main_parse_loop_spec (input : Slice Std.U8) (out0 : Slice Std.U32) (n : Std.Usize) (head0 : Array Std.U32 65536#usize) (prev0 : Array Std.U32 65536#usize) (head30 : Array Std.U32 16384#usize) (shorts0 : Array Std.U32 4096#usize) (litq : Std.Usize) (hs : Std.U32) (acc : Std.U64) (depth : Std.Usize) (lz : Std.Usize) (p2 : Std.Usize) (h3on : Std.Usize) (stepmax : Std.Usize) (pos0 : Std.Usize) (ntok0 : Std.Usize) (carry0 : Std.Usize) (miss0 : Std.Usize) (filled0 : Std.Usize)
    (hstep : 1 ≤ stepmax.val ∧ stepmax.val ≤ 32)
    (hn : n.val = input.length) (hout : input.length ≤ out0.length)
    (hp : pos0.val ≤ n.val) (hntok : ntok0.val ≤ pos0.val)
    (hdec : LZ77.decode (toks out0 ntok0.val) = some ((bytes input).take pos0.val)) :
    slot.y_b_main_parse_loop input out0 lz n head0 prev0 head30 shorts0 litq acc depth hs p2 h3on stepmax pos0 ntok0 carry0 miss0 filled0 ⦃ fun r =>
      r.1.val ≤ input.length ∧ r.2.length = out0.length ∧
      LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
  rw [slot.y_b_main_parse_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => n.val - s.2.2.2.2.2.1.val)
    (inv := fun s =>
      s.2.2.2.2.2.1.val ≤ n.val ∧ s.2.2.2.2.2.2.1.val ≤ s.2.2.2.2.2.1.val ∧ s.1.length = out0.length ∧
      LZ77.decode (toks s.1 s.2.2.2.2.2.2.1.val) = some ((bytes input).take s.2.2.2.2.2.1.val))
  · rintro ⟨out, head, prev, head3, shorts, pos, ntok, carry, miss, filled⟩ ⟨hpn, hnt, hlen, hde⟩
    simp only at hpn hnt hlen hde
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.y_b_main_parse_loop.body, lift, Array.to_slice_mut, alloc.vec.Vec.deref_mut, bind_tc_ok]
    split
    case isTrue hlt =>
      step*
      all_goals (repeat (first
        | (refine ⟨by scalar_tac, by scalar_tac, by assumption, by assumption, by scalar_tac⟩)
        | (intro hc; (try step*))
        | (casesm* _ × _; (try simp only []); (try step*))
        | (split <;> (try step*))
        | (step <;> (try step*))))
      all_goals (try scalar_tac)
    case isFalse hge =>
      have hpn' : pos.val = input.length := by scalar_tac
      refine ⟨by scalar_tac, hlen, ?_⟩
      unfold LZ77.Valid
      rw [hde, hpn']
      simp
  · exact ⟨hp, hntok, rfl, hdec⟩
end
attribute [local step] main_parse_loop_spec
@[local step]
theorem bounded_step_spec (x : Std.Usize) :
    slot.y_b_bounded_step x ⦃ fun r => 1 ≤ r.val ∧ r.val ≤ 32 ⦄ := by
  rw [slot.y_b_bounded_step]
  step*
  all_goals (repeat (split <;> step*))
  all_goals scalar_tac
section
attribute [local step] ite_true_spec
@[local step]
theorem main_parse_spec (input : Slice Std.U8) (out : Slice Std.U32) (pos0 : Std.Usize) (ntok0 : Std.Usize) (dp : slot.Y_B_Params)
    (hlen : input.length ≤ out.length)
    (hp : pos0.val ≤ input.length) (hntok : ntok0.val ≤ pos0.val)
    (hdec : LZ77.decode (toks out ntok0.val) = some ((bytes input).take pos0.val)) :
    slot.y_b_main_parse input out pos0 ntok0 dp ⦃ fun r =>
      r.1.val ≤ input.length ∧
      r.2.length = out.length ∧
      LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
  rw [slot.y_b_main_parse]
  have h0 := decode_nil input out
  try simp only [lift, Array.to_slice_mut, alloc.vec.Vec.deref_mut, bind_tc_ok]
  step*
  all_goals (repeat (first
    | (refine ⟨by scalar_tac, by scalar_tac, valid_of_decode (by assumption) (by scalar_tac)⟩)
    | (intro hc; (try step*))
    | (casesm* _ × _; (try simp only []); (try step*))
    | (split <;> (try step*))
    | (step <;> (try step*))))
  all_goals (try (repeat split <;> scalar_tac))
end
attribute [local step] main_parse_spec
section
attribute [local step] ite_true_spec
@[local step]
theorem parse_mode_spec (input : Slice Std.U8) (out : Slice Std.U32) (m : Std.Usize)
    (hlen : input.length ≤ out.length) :
    slot.y_b_parse_mode input out m ⦃ fun r =>
      r.1.val ≤ input.length ∧
      r.2.length = out.length ∧
      LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
  rw [slot.y_b_parse_mode]
  have h0 := decode_nil input out
  try simp only [lift, Array.to_slice_mut, alloc.vec.Vec.deref_mut, bind_tc_ok]
  step*
  all_goals (repeat (first
    | (refine ⟨by scalar_tac, by scalar_tac, valid_of_decode (by assumption) (by scalar_tac)⟩)
    | (intro hc; (try step*))
    | (casesm* _ × _; (try simp only []); (try step*))
    | (split <;> (try step*))
    | (step <;> (try step*))))
  all_goals (try scalar_tac)
end
end EB
attribute [local step] EA.main_part_spec EB.parse_mode_spec
@[local step]
theorem prose_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.y_prose input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.y_prose]
 exact EA.main_part_spec _ _ _ _ _ input out 0#usize 0#usize 0#usize hlen (by simp) (by simp) (EA.decode_nil input out)
@[local step]
theorem sparse_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) :
 slot.y_sparse input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.y_sparse]
 apply Std.WP.spec_bind (EA.sh_rle_phase_spec _ _ _ _ input out hlen)
 rintro ⟨⟨nt, p⟩, out'⟩ ⟨hp, ht, ho, hd⟩
 have hout : input.length ≤ out'.length := by rw [ho]; exact hlen
 simp only
 step*
 repeat' (split <;> step*)
 all_goals first
  | exact ⟨by scalar_tac, by scalar_tac, by assumption⟩
  | exact ⟨by scalar_tac, ho, EA.valid_of_decode hd (by scalar_tac)⟩
theorem parse_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.y_parse input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.y_parse]
 step*
 repeat' (split <;> step*)
end EY
namespace EV
open Aeneas Aeneas.Std Result ControlFlow
set_option maxRecDepth 8192
set_option maxHeartbeats 4000000
open LZ77 (toks bytes bytes_length bytes_getElem! Matches emit_lit emit_match ite_ok)
theorem decode_nil (input : Slice Std.U8) (out : Slice Std.U32) :
    LZ77.decode (toks out (0#usize).val) = some ((bytes input).take (0#usize).val) := by
  simp [toks, LZ77.decode]
theorem valid_of_decode {input : Slice Std.U8} {o : Slice Std.U32} {t p : Std.Usize}
    (hde : LZ77.decode (toks o t.val) = some ((bytes input).take p.val)) (hp : p.val = input.length) :
    LZ77.Valid (bytes input) (toks o t.val) := by
  unfold LZ77.Valid
  rw [hde, hp]
  simp
theorem spec_ite_cut {α : Type} (c : Prop) [Decidable c] (a b : Result α) (Q : α → Prop)
    (ha : c → a ⦃ Q ⦄) (hb : ¬c → b ⦃ Q ⦄) : (if c then a else b) ⦃ Q ⦄ := by
  by_cases h : c
  · rw [if_pos h]; exact ha h
  · rw [if_neg h]; exact hb h
theorem ite_prod_spec {α β : Type} (c : Prop) [Decidable c] (A B : Result (α × β))
    (hA : c → A ⦃ fun _ => True ⦄) (hB : ¬c → B ⦃ fun _ => True ⦄) :
    (if c then A else B) ⦃ fun _ => True ⦄ := by
  by_cases h : c
  · rw [if_pos h]; exact hA h
  · rw [if_neg h]; exact hB h
theorem ite_true_spec {α : Type} (c : Prop) [Decidable c] (A B : Result α)
    (hA : c → A ⦃ fun _ => True ⦄) (hB : ¬c → B ⦃ fun _ => True ⦄) :
    (if c then A else B) ⦃ fun _ => True ⦄ := by
  by_cases h : c
  · rw [if_pos h]; exact hA h
  · rw [if_neg h]; exact hB h
@[local step]
theorem ld4_spec (input : Slice Std.U8) (p : Std.Usize) :
    slot.v_ld4 input p ⦃ fun _ => True ⦄ := by
  rw [slot.v_ld4]
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
  all_goals scalar_tac
@[local step]
theorem ld8_spec (input : Slice Std.U8) (p : Std.Usize) :
    slot.v_ld8 input p ⦃ fun _ => True ⦄ := by
  rw [slot.v_ld8]
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
  all_goals scalar_tac
@[local step]
theorem first_diff_spec (x : Std.U64) :
    slot.v_first_diff x ⦃ fun _ => True ⦄ := by
  rw [slot.v_first_diff]
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
  all_goals scalar_tac
@[local step]
theorem fast_len_loop_spec (input : Slice Std.U8) (a : Std.Usize) (b : Std.Usize) (cap : Std.Usize) (l : Std.Usize) (go : Std.Usize) (it : Std.Usize)  :
    slot.v_fast_len_loop input a b cap l go it ⦃ fun _ => True ⦄ := by
  rw [slot.v_fast_len_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => 40 - s.2.2.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1, x2⟩ _
    simp only [slot.v_fast_len_loop.body, lift, Array.to_slice_mut]
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
    all_goals scalar_tac
  · trivial
@[local step]
theorem fast_len_spec (input : Slice Std.U8) (a : Std.Usize) (b : Std.Usize) (cap : Std.Usize) :
    slot.v_fast_len input a b cap ⦃ fun _ => True ⦄ := by
  rw [slot.v_fast_len]
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
  all_goals scalar_tac
@[local step]
theorem hashp_spec (input : Slice Std.U8) (p : Std.Usize) (hs : Std.U32) :
    slot.v_hashp input p hs ⦃ fun _ => True ⦄ := by
  rw [slot.v_hashp]
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
  all_goals scalar_tac
@[local step]
theorem hash3_spec (w : Std.U32) :
    slot.v_hash3 w ⦃ fun _ => True ⦄ := by
  rw [slot.v_hash3]
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
  all_goals scalar_tac
@[local step]
theorem dextra_spec (d : Std.Usize) :
    slot.v_dextra d ⦃ fun _ => True ⦄ := by
  rw [slot.v_dextra]
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
  all_goals scalar_tac
@[local step]
theorem lextra_spec (l : Std.Usize) :
    slot.v_lextra l ⦃ fun _ => True ⦄ := by
  rw [slot.v_lextra]
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
  all_goals scalar_tac
@[local step]
theorem score_spec (l : Std.Usize) (d : Std.Usize) (cq : Std.Usize) :
    slot.v_score l d cq ⦃ fun _ => True ⦄ := by
  rw [slot.v_score]
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
  all_goals scalar_tac
@[local step]
theorem lg8_spec (x : Std.U32) :
    slot.v_lg8 x ⦃ fun _ => True ⦄ := by
  rw [slot.v_lg8]
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
  all_goals scalar_tac
@[local step]
theorem sample_loop_spec (input : Slice Std.U8) (h : Array Std.U32 256#usize) (n : Std.Usize) (st : Std.Usize) (k : Std.Usize) (c : Std.Usize) (hn : n.val = input.length) :
    slot.v_sample_loop input h n st k c ⦃ fun _ => True ⦄ := by
  rw [slot.v_sample_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => 8192 - s.2.2.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1, x2⟩ _
    simp only [slot.v_sample_loop.body, lift, Array.to_slice_mut]
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
    all_goals scalar_tac
  · trivial
@[local step]
theorem sample_spec (input : Slice Std.U8) (h : Array Std.U32 256#usize) :
    slot.v_sample input h ⦃ fun _ => True ⦄ := by
  rw [slot.v_sample]
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
  all_goals scalar_tac
@[local step]
theorem entropy256_loop_spec (h : Array Std.U32 256#usize) (tot : Std.U64) (acc : Std.U64) (i : Std.Usize)  :
    slot.v_entropy256_loop h tot acc i ⦃ fun _ => True ⦄ := by
  rw [slot.v_entropy256_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => 256 - s.2.2.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1, x2⟩ _
    simp only [slot.v_entropy256_loop.body, lift, Array.to_slice_mut]
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
    all_goals scalar_tac
  · trivial
@[local step]
theorem entropy256_spec (h : Array Std.U32 256#usize) :
    slot.v_entropy256 h ⦃ fun _ => True ⦄ := by
  rw [slot.v_entropy256]
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
  all_goals scalar_tac
@[local step]
theorem share_loop_spec (h : Array Std.U32 256#usize) (lo : Std.Usize) (hi : Std.Usize) (t : Std.Usize) (s : Std.Usize) (i : Std.Usize)  :
    slot.v_share_loop h lo hi t s i ⦃ fun _ => True ⦄ := by
  rw [slot.v_share_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => 256 - s.2.2.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1, x2⟩ _
    simp only [slot.v_share_loop.body, lift, Array.to_slice_mut]
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
    all_goals scalar_tac
  · trivial
@[local step]
theorem share_spec (h : Array Std.U32 256#usize) (lo : Std.Usize) (hi : Std.Usize) :
    slot.v_share h lo hi ⦃ fun _ => True ⦄ := by
  rw [slot.v_share]
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
  all_goals scalar_tac
@[local step]
theorem low_mode_spec (e : Std.Usize) (dp : slot.V_Params) :
    slot.v_low_mode e dp ⦃ fun _ => True ⦄ := by
  rw [slot.v_low_mode]
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
  all_goals scalar_tac
@[local step]
theorem lit_cost_spec (e : Std.Usize) (low : Std.Usize) (dp : slot.V_Params) :
    slot.v_lit_cost e low dp ⦃ fun _ => True ⦄ := by
  rw [slot.v_lit_cost]
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
  all_goals scalar_tac
@[local step]
theorem m3_mode_spec (h : Array Std.U32 256#usize) (e : Std.Usize) (dp : slot.V_Params) :
    slot.v_m3_mode h e dp ⦃ fun _ => True ⦄ := by
  rw [slot.v_m3_mode]
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
  all_goals scalar_tac
@[local step]
theorem h3_mode_spec (h : Array Std.U32 256#usize) (e : Std.Usize) (dp : slot.V_Params) :
    slot.v_h3_mode h e dp ⦃ fun _ => True ⦄ := by
  rw [slot.v_h3_mode]
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
  all_goals scalar_tac
@[local step]
theorem numeric_spec (h : Array Std.U32 256#usize) (n : Std.Usize) (low : Std.Usize) (dp : slot.V_Params) :
    slot.v_numeric h n low dp ⦃ fun _ => True ⦄ := by
  rw [slot.v_numeric]
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
  all_goals scalar_tac
@[local step]
theorem walk_loop_spec (input : Slice Std.U8) (prev : Array Std.U32 65536#usize) (pos : Std.Usize) (cap : Std.Usize) (probes : Std.Usize) (litq : Std.Usize) (lim : Std.Usize) (stop : Std.Usize) (cur : Std.Usize) (k : Std.Usize) (bl : Std.Usize) (bs : Std.Usize) (bd : Std.Usize) (off : Std.Usize) (want : Std.U32)  :
    slot.v_walk_loop input prev pos cap probes litq lim stop cur k bl bs bd off want ⦃ fun _ => True ⦄ := by
  rw [slot.v_walk_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => probes.val - s.2.1.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1, x2, x3, x4, x5, x6⟩ _
    simp only [slot.v_walk_loop.body, lift, Array.to_slice_mut]
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
    all_goals scalar_tac
  · trivial
@[local step]
theorem walk_spec (input : Slice Std.U8) (prev : Array Std.U32 65536#usize) (pos : Std.Usize) (start : Std.Usize) (cap : Std.Usize) (probes : Std.Usize) (bl0 : Std.Usize) (bs0 : Std.Usize) (litq : Std.Usize) :
    slot.v_walk input prev pos start cap probes bl0 bs0 litq ⦃ fun _ => True ⦄ := by
  rw [slot.v_walk]
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
  all_goals scalar_tac
@[local step]
theorem lwalk_loop_spec (input : Slice Std.U8) (prev : Array Std.U32 65536#usize) (pos : Std.Usize) (cap : Std.Usize) (probes : Std.Usize) (litq : Std.Usize) (lim : Std.Usize) (stop : Std.Usize) (cur : Std.Usize) (k : Std.Usize) (bl : Std.Usize) (bs : Std.Usize) (bd : Std.Usize) (off : Std.Usize) (want : Std.U32)  :
    slot.v_lwalk_loop input prev pos cap probes litq lim stop cur k bl bs bd off want ⦃ fun _ => True ⦄ := by
  rw [slot.v_lwalk_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => probes.val - s.2.1.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1, x2, x3, x4, x5, x6⟩ _
    simp only [slot.v_lwalk_loop.body, lift, Array.to_slice_mut]
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
    all_goals scalar_tac
  · trivial
@[local step]
theorem lwalk_spec (input : Slice Std.U8) (prev : Array Std.U32 65536#usize) (pos : Std.Usize) (start : Std.Usize) (cap : Std.Usize) (probes : Std.Usize) (bl0 : Std.Usize) (bs0 : Std.Usize) (litq : Std.Usize) :
    slot.v_lwalk input prev pos start cap probes bl0 bs0 litq ⦃ fun _ => True ⦄ := by
  rw [slot.v_lwalk]
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
  all_goals scalar_tac
@[local step]
theorem cand3_spec (input : Slice Std.U8) (pos : Std.Usize) (s3 : Std.Usize) (cap : Std.Usize) (bs0 : Std.Usize) (litq : Std.Usize) :
    slot.v_cand3 input pos s3 cap bs0 litq ⦃ fun _ => True ⦄ := by
  rw [slot.v_cand3]
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
  all_goals scalar_tac
@[local step]
theorem cand3_long_spec (input : Slice Std.U8) (pos : Std.Usize) (s3 : Std.Usize) (cap : Std.Usize) (bs0 : Std.Usize) (litq : Std.Usize) :
    slot.v_cand3_long input pos s3 cap bs0 litq ⦃ fun _ => True ⦄ := by
  rw [slot.v_cand3_long]
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
  all_goals scalar_tac
@[local step]
theorem upd3_spec (input : Slice Std.U8) (head3 : Array Std.U32 16384#usize) (pos : Std.Usize) (on : Std.Usize) :
    slot.v_upd3 input head3 pos on ⦃ fun _ => True ⦄ := by
  rw [slot.v_upd3]
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
  all_goals scalar_tac
@[local step]
theorem suffix_walk_loop_spec (input : Slice Std.U8) (prev : Array Std.U32 65536#usize)
    (pos cap litq off q lim cur best k : Std.Usize) :
    slot.v_suffix_walk_loop input prev pos cap litq off q lim cur best k ⦃ fun _ => True ⦄ := by
  rw [slot.v_suffix_walk_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => slot.V_SUFFIX_DEPTH.val - s.2.2.val)
    (inv := fun _ => True)
  · rintro ⟨cur, best, k⟩ _
    simp only [slot.v_suffix_walk_loop.body, lift, Array.to_slice_mut]
    step*
    repeat (first
      | (intro hc; try step*)
      | (split <;> try step*)
      | (casesm* _ × _; try step*)
      | (apply spec_ite_cut <;> intro hc <;> try step*)
      | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
      | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
    all_goals scalar_tac
  · trivial
@[local step]
theorem suffix_walk_spec (input : Slice Std.U8) (prev : Array Std.U32 65536#usize)
    (pos cap best0 litq probes : Std.Usize) :
    slot.v_suffix_walk input prev pos cap best0 litq probes ⦃ fun _ => True ⦄ := by
  rw [slot.v_suffix_walk]
  try simp only [lift, Array.to_slice_mut]
  step*
  repeat (first
    | (intro hc; try step*)
    | (split <;> try step*)
    | (casesm* _ × _; try step*)
    | (apply spec_ite_cut <;> intro hc <;> try step*)
    | (apply Std.WP.spec_bind (Pₘ := fun _ => True))
    | (intro y _; repeat (obtain ⟨_, y⟩ : _ × _ := y); try step*))
  all_goals scalar_tac
@[local step]
theorem search_spec (input : Slice Std.U8) (head : Array Std.U32 65536#usize) (prev : Array Std.U32 65536#usize) (head3 : Array Std.U32 16384#usize) (shorts : Array Std.U32 4096#usize) (pos : Std.Usize) (probes : Std.Usize) (bl0 : Std.Usize) (bs0 : Std.Usize) (litq : Std.Usize) (hs : Std.U32) (h3on : Std.Usize) :
    slot.v_search input head prev head3 shorts pos probes bl0 bs0 litq hs h3on ⦃ fun _ => True ⦄ := by
  rw [slot.v_search]
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
  all_goals scalar_tac
@[local step]
theorem insert_range_loop_spec (input : Slice Std.U8) (head : Array Std.U32 65536#usize) (prev : Array Std.U32 32768#usize) («to» : Std.Usize) (hs : Std.U32) (lim : Std.Usize) (p : Std.Usize)  :
    slot.v_insert_range_loop input head prev «to» hs lim p ⦃ fun _ => True ⦄ := by
  rw [slot.v_insert_range_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => «to».val - s.2.2.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1, x2⟩ _
    simp only [slot.v_insert_range_loop.body, lift, Array.to_slice_mut]
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
    all_goals scalar_tac
  · trivial
@[local step]
theorem insert_range_spec (input : Slice Std.U8) (head : Array Std.U32 65536#usize) (prev : Array Std.U32 32768#usize) («from» : Std.Usize) («to» : Std.Usize) (hs : Std.U32) :
    slot.v_insert_range input head prev «from» «to» hs ⦃ fun _ => True ⦄ := by
  rw [slot.v_insert_range]
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
  all_goals scalar_tac
@[local step]
theorem insert_range3_loop_spec (input : Slice Std.U8) (head : Array Std.U32 65536#usize) (prev : Array Std.U32 32768#usize) (head3 : Array Std.U32 16384#usize) («to» : Std.Usize) (hs : Std.U32) (lim : Std.Usize) (p : Std.Usize)  :
    slot.v_insert_range3_loop input head prev head3 «to» hs lim p ⦃ fun _ => True ⦄ := by
  rw [slot.v_insert_range3_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => «to».val - s.2.2.2.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1, x2, x3⟩ _
    simp only [slot.v_insert_range3_loop.body, lift, Array.to_slice_mut]
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
    all_goals scalar_tac
  · trivial
@[local step]
theorem insert_range3_spec (input : Slice Std.U8) (head : Array Std.U32 65536#usize) (prev : Array Std.U32 32768#usize) (head3 : Array Std.U32 16384#usize) («from» : Std.Usize) («to» : Std.Usize) (hs : Std.U32) :
    slot.v_insert_range3 input head prev head3 «from» «to» hs ⦃ fun _ => True ⦄ := by
  rw [slot.v_insert_range3]
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
  all_goals scalar_tac
@[local step]
theorem insert_match_spec (input : Slice Std.U8) (head : Array Std.U32 65536#usize) (prev : Array Std.U32 32768#usize) (head3 : Array Std.U32 16384#usize) («from» : Std.Usize) («to» : Std.Usize) (hs : Std.U32) (h3on : Std.Usize) :
    slot.v_insert_match input head prev head3 «from» «to» hs h3on ⦃ fun _ => True ⦄ := by
  rw [slot.v_insert_match]
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
  all_goals scalar_tac
def w8 (input : Slice Std.U8) (p : Nat) : Nat :=
  (input.val[p]!).val + (input.val[p + 1]!).val * 256 + (input.val[p + 2]!).val * 65536 +
  (input.val[p + 3]!).val * 16777216 + (input.val[p + 4]!).val * 4294967296 +
  (input.val[p + 5]!).val * 1099511627776 + (input.val[p + 6]!).val * 281474976710656 +
  (input.val[p + 7]!).val * 72057594037927936
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
theorem Matches.add8 {input : Slice Std.U8} {a b l : Nat} (h : Matches input a b l)
    (hw : w8 input (a + l) = w8 input (b + l)) : Matches input a b (l + 8) := by
  have hb := w8_bytes input (a + l) (b + l) hw
  intro k hk
  by_cases hkl : k < l
  · exact h k hkl
  · have := hb (k - l) (by omega)
    rw [show b + k = b + l + (k - l) by omega, show a + k = a + l + (k - l) by omega]
    exact this
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
@[local step]
theorem tw8_spec (input : Slice Std.U8) (p : Std.Usize) (h : p.val + 8 ≤ input.length) :
    slot.v_tw8 input p ⦃ fun r => r.val = w8 input p.val ⦄ := by
  rw [slot.v_tw8]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  step*
  unfold w8
  rw [getElem!_pos input.val p.val (by scalar_tac), getElem!_pos input.val (p.val + 1) (by scalar_tac),
    getElem!_pos input.val (p.val + 2) (by scalar_tac), getElem!_pos input.val (p.val + 3) (by scalar_tac),
    getElem!_pos input.val (p.val + 4) (by scalar_tac), getElem!_pos input.val (p.val + 5) (by scalar_tac),
    getElem!_pos input.val (p.val + 6) (by scalar_tac), getElem!_pos input.val (p.val + 7) (by scalar_tac)]
  scalar_tac
@[local step]
theorem tw4_spec (input : Slice Std.U8) (p : Std.Usize) (h : p.val + 4 ≤ input.length) :
    slot.v_tw4 input p ⦃ fun r => r.val = w4 input p.val ⦄ := by
  rw [slot.v_tw4]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  step*
  unfold w4
  rw [getElem!_pos input.val p.val (by scalar_tac), getElem!_pos input.val (p.val + 1) (by scalar_tac),
    getElem!_pos input.val (p.val + 2) (by scalar_tac), getElem!_pos input.val (p.val + 3) (by scalar_tac)]
  scalar_tac
theorem words_eq_loop_spec (input : Slice Std.U8) (a b cap l0 : Std.Usize)
    (ha : a.val + cap.val ≤ input.length) (hb : b.val + cap.val ≤ input.length)
    (hl0 : l0.val ≤ cap.val) (h0 : Matches input a.val b.val l0.val) :
    slot.v_words_eq_loop input a b cap l0 ⦃ fun l =>
      l.val ≤ cap.val ∧ Matches input a.val b.val l.val ⦄ := by
  rw [slot.v_words_eq_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun l => cap.val - l.val)
    (inv := fun l => l.val ≤ cap.val ∧ Matches input a.val b.val l.val)
  · rintro l ⟨hle, hinv⟩
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.v_words_eq_loop.body]
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
    slot.v_tail_eq input a b cap l ⦃ fun r => r.val = 1 →
      8 ≤ cap.val ∧ cap.val ≤ l.val + 8 ∧
      w8 input (a.val + (cap.val - 8)) = w8 input (b.val + (cap.val - 8)) ⦄ := by
  rw [slot.v_tail_eq]
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
    slot.v_short_eq input a b cap ⦃ fun r => r.val = 1 →
      4 ≤ cap.val ∧ cap.val < 8 ∧ w4 input a.val = w4 input b.val ∧
      w4 input (a.val + (cap.val - 4)) = w4 input (b.val + (cap.val - 4)) ⦄ := by
  rw [slot.v_short_eq]
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
    slot.v_words_eq input a b cap ⦃ fun l =>
      l.val ≤ cap.val ∧ Matches input a.val b.val l.val ⦄ := by
  rw [slot.v_words_eq]
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
    slot.v_match_len_loop input a b cap l0 ⦃ fun l =>
      l.val ≤ cap.val ∧ Matches input a.val b.val l.val ⦄ := by
  (
  rw [slot.v_match_len_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun l => cap.val - l.val)
    (inv := fun l => l.val ≤ cap.val ∧ LZ77.Matches input a.val b.val l.val)
  · rintro l ⟨hle, hinv⟩
    simp only [slot.v_match_len_loop.body]
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
  · exact ⟨hl0, h0⟩)
@[local step]
theorem match_len_spec (input : Slice Std.U8) (a b cap : Std.Usize)
    (ha : a.val + cap.val ≤ input.length) (hb : b.val + cap.val ≤ input.length) :
    slot.v_match_len input a b cap ⦃ fun l =>
      l.val ≤ cap.val ∧ Matches input a.val b.val l.val ⦄ := by
  rw [slot.v_match_len]
  apply Std.WP.spec_bind (words_eq_spec input a b cap ha hb)
  rintro l0 ⟨hle, hm⟩
  exact match_len_loop_spec input a b cap l0 ha hb hle hm
theorem verified_spec (input : Slice Std.U8) (pos d ch : Std.Usize) :
    slot.v_verified input pos d ch ⦃ fun b => b = true →
      3 ≤ ch.val ∧ ch.val ≤ 258 ∧ 1 ≤ d.val ∧ d.val ≤ 32768 ∧ d.val ≤ pos.val ∧
      pos.val + ch.val ≤ input.length ∧ Matches input (pos.val - d.val) pos.val ch.val ⦄ := by
  rw [slot.v_verified]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  step*
  intro hv
  have hv' : ch.val ≤ v.val := by simpa using hv
  refine ⟨by scalar_tac, by scalar_tac, by scalar_tac, by scalar_tac, by scalar_tac,
    by scalar_tac, ?_⟩
  rw [show pos.val - d.val = i1.val by scalar_tac]
  exact Matches.mono v_post2 hv'
theorem emit_lits_loop_spec (input : Slice Std.U8) (out0 : Slice Std.U32)
    (n cnt1 k0 c0 ntok0 : Std.Usize)
    (hn : n.val = input.length) (hout : input.length ≤ out0.length)
    (hk : k0.val ≤ n.val) (hntok : ntok0.val ≤ k0.val) (hc0 : c0.val = 0)
    (hdec : LZ77.decode (toks out0 ntok0.val) = some ((bytes input).take k0.val)) :
    slot.v_emit_lits_loop input out0 n cnt1 k0 c0 ntok0 ⦃ fun r =>
      r.2.1.val ≤ n.val ∧ (k0.val < r.2.1.val ∨ cnt1.val = 0 ∨ k0.val = n.val) ∧
      r.2.2.val ≤ r.2.1.val ∧ r.1.length = out0.length ∧
      LZ77.decode (toks r.1 r.2.2.val) = some ((bytes input).take r.2.1.val) ⦄ := by
  rw [slot.v_emit_lits_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => n.val - s.2.1.val)
    (inv := fun s =>
      s.2.1.val ≤ n.val ∧ s.2.1.val = k0.val + s.2.2.1.val ∧ s.2.2.2.val ≤ s.2.1.val ∧
      s.1.length = out0.length ∧
      LZ77.decode (toks s.1 s.2.2.2.val) = some ((bytes input).take s.2.1.val))
  · rintro ⟨out, k, c, ntok⟩ ⟨hkn, hkc, hnt, hlen, hde⟩
    simp only at hkn hkc hnt hlen hde
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.v_emit_lits_loop.body]
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
    slot.v_emit_lits input out pos0 cnt ntok0 ⦃ fun r =>
      (pos0.val < r.1.2.val ∨ pos0.val = input.length) ∧ r.1.2.val ≤ input.length ∧ r.1.1.val ≤ r.1.2.val ∧
      r.2.length = out.length ∧
      LZ77.decode (toks r.2 r.1.1.val) = some ((bytes input).take r.1.2.val) ⦄ := by
  rw [slot.v_emit_lits]
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
    slot.v_emit_step input out pos d l lits ntok ⦃ fun r =>
      pos.val < r.1.2.val ∧ r.1.2.val ≤ input.length ∧ r.1.1.val ≤ r.1.2.val ∧
      r.2.length = out.length ∧
      LZ77.decode (toks r.2 r.1.1.val) = some ((bytes input).take r.1.2.val) ⦄ := by
  rw [slot.v_emit_step]
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
@[local step]
theorem lazy_probe_spec (input : Slice Std.U8) (head : Array Std.U32 65536#usize) (prev : Array Std.U32 65536#usize) (head3 : Array Std.U32 16384#usize) (q : Std.Usize) (go : Std.Usize) (p2 : Std.Usize) (l1 : Std.Usize) (sv1 : Std.Usize) (litq : Std.Usize) (hs : Std.U32) (h3on : Std.Usize) :
    slot.v_lazy_probe input head prev head3 q go p2 l1 sv1 litq hs h3on ⦃ fun _ => True ⦄ := by
  rw [slot.v_lazy_probe]
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
  all_goals scalar_tac
@[local step]
theorem ext_ok_spec (input : Slice Std.U8) (pos : Std.Usize) (l2 : Std.Usize) (d2 : Std.Usize) :
    slot.v_ext_ok input pos l2 d2 ⦃ fun _ => True ⦄ := by
  rw [slot.v_ext_ok]
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
  all_goals scalar_tac
@[local step]
theorem fl_tw8_spec (input : Slice Std.U8) (p : Std.Usize) (h : p.val + 8 ≤ input.length) :
    slot.v_fl_tw8 input p ⦃ fun r => r.val = w8 input p.val ⦄ := by
  rw [slot.v_fl_tw8]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  step*
  unfold w8
  rw [getElem!_pos input.val p.val (by scalar_tac), getElem!_pos input.val (p.val + 1) (by scalar_tac),
    getElem!_pos input.val (p.val + 2) (by scalar_tac), getElem!_pos input.val (p.val + 3) (by scalar_tac),
    getElem!_pos input.val (p.val + 4) (by scalar_tac), getElem!_pos input.val (p.val + 5) (by scalar_tac),
    getElem!_pos input.val (p.val + 6) (by scalar_tac), getElem!_pos input.val (p.val + 7) (by scalar_tac)]
  scalar_tac
@[local step]
theorem fl_tw4_spec (input : Slice Std.U8) (p : Std.Usize) (h : p.val + 4 ≤ input.length) :
    slot.v_fl_tw4 input p ⦃ fun r => r.val = w4 input p.val ⦄ := by
  rw [slot.v_fl_tw4]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  step*
  unfold w4
  rw [getElem!_pos input.val p.val (by scalar_tac), getElem!_pos input.val (p.val + 1) (by scalar_tac),
    getElem!_pos input.val (p.val + 2) (by scalar_tac), getElem!_pos input.val (p.val + 3) (by scalar_tac)]
  scalar_tac
theorem fl_words_eq_loop_spec (input : Slice Std.U8) (a b cap l0 : Std.Usize)
    (ha : a.val + cap.val ≤ input.length) (hb : b.val + cap.val ≤ input.length)
    (hl0 : l0.val ≤ cap.val) (h0 : Matches input a.val b.val l0.val) :
    slot.v_fl_words_eq_loop input a b cap l0 ⦃ fun l =>
      l.val ≤ cap.val ∧ Matches input a.val b.val l.val ⦄ := by
  rw [slot.v_fl_words_eq_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun l => cap.val - l.val)
    (inv := fun l => l.val ≤ cap.val ∧ Matches input a.val b.val l.val)
  · rintro l ⟨hle, hinv⟩
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.v_fl_words_eq_loop.body]
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
theorem fl_tail_eq_spec (input : Slice Std.U8) (a b cap l : Std.Usize)
    (ha : a.val + cap.val ≤ input.length) (hb : b.val + cap.val ≤ input.length) (hl : l.val ≤ cap.val) :
    slot.v_fl_tail_eq input a b cap l ⦃ fun r => r.val = 1 →
      8 ≤ cap.val ∧ cap.val ≤ l.val + 8 ∧
      w8 input (a.val + (cap.val - 8)) = w8 input (b.val + (cap.val - 8)) ⦄ := by
  rw [slot.v_fl_tail_eq]
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
theorem fl_short_eq_spec (input : Slice Std.U8) (a b cap : Std.Usize)
    (ha : a.val + cap.val ≤ input.length) (hb : b.val + cap.val ≤ input.length) :
    slot.v_fl_short_eq input a b cap ⦃ fun r => r.val = 1 →
      4 ≤ cap.val ∧ cap.val < 8 ∧ w4 input a.val = w4 input b.val ∧
      w4 input (a.val + (cap.val - 4)) = w4 input (b.val + (cap.val - 4)) ⦄ := by
  rw [slot.v_fl_short_eq]
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
theorem fl_words_eq_spec (input : Slice Std.U8) (a b cap : Std.Usize)
    (ha : a.val + cap.val ≤ input.length) (hb : b.val + cap.val ≤ input.length) :
    slot.v_fl_words_eq input a b cap ⦃ fun l =>
      l.val ≤ cap.val ∧ Matches input a.val b.val l.val ⦄ := by
  rw [slot.v_fl_words_eq]
  apply Std.WP.spec_bind (fl_words_eq_loop_spec input a b cap 0#usize ha hb (by scalar_tac)
    (LZ77.Matches.zero input a.val b.val))
  rintro l ⟨hle, hm⟩
  apply Std.WP.spec_bind (fl_tail_eq_spec input a b cap l ha hb hle)
  rintro big hbig
  apply Std.WP.spec_bind (fl_short_eq_spec input a b cap ha hb)
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
theorem fl_match_len_loop_spec (input : Slice Std.U8) (a b cap l0 : Std.Usize)
    (ha : a.val + cap.val ≤ input.length) (hb : b.val + cap.val ≤ input.length)
    (hl0 : l0.val ≤ cap.val) (h0 : Matches input a.val b.val l0.val) :
    slot.v_fl_match_len_loop input a b cap l0 ⦃ fun l =>
      l.val ≤ cap.val ∧ Matches input a.val b.val l.val ⦄ := by
  rw [slot.v_fl_match_len_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun l => cap.val - l.val)
    (inv := fun l => l.val ≤ cap.val ∧ LZ77.Matches input a.val b.val l.val)
  · rintro l ⟨hle, hinv⟩
    simp only [slot.v_fl_match_len_loop.body]
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
  · exact ⟨hl0, h0⟩
@[local step]
theorem fl_match_len_spec (input : Slice Std.U8) (a b cap : Std.Usize)
    (ha : a.val + cap.val ≤ input.length) (hb : b.val + cap.val ≤ input.length) :
    slot.v_fl_match_len input a b cap ⦃ fun l =>
      l.val ≤ cap.val ∧ Matches input a.val b.val l.val ⦄ := by
  rw [slot.v_fl_match_len]
  apply Std.WP.spec_bind (fl_words_eq_spec input a b cap ha hb)
  rintro l0 ⟨hle, hm⟩
  exact fl_match_len_loop_spec input a b cap l0 ha hb hle hm
theorem fl_verified_spec (input : Slice Std.U8) (pos d ch : Std.Usize) :
    slot.v_fl_verified input pos d ch ⦃ fun b => b = true →
      3 ≤ ch.val ∧ ch.val ≤ 258 ∧ 1 ≤ d.val ∧ d.val ≤ 32768 ∧ d.val ≤ pos.val ∧
      pos.val + ch.val ≤ input.length ∧ Matches input (pos.val - d.val) pos.val ch.val ⦄ := by
  rw [slot.v_fl_verified]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  step*
  intro hv
  have hv' : ch.val ≤ v.val := by simpa using hv
  refine ⟨by scalar_tac, by scalar_tac, by scalar_tac, by scalar_tac, by scalar_tac,
    by scalar_tac, ?_⟩
  rw [show pos.val - d.val = i1.val by scalar_tac]
  exact Matches.mono v_post2 hv'
theorem fl_emit_lits_loop_spec (input : Slice Std.U8) (out0 : Slice Std.U32)
    (n cnt1 k0 c0 ntok0 : Std.Usize)
    (hn : n.val = input.length) (hout : input.length ≤ out0.length)
    (hk : k0.val ≤ n.val) (hntok : ntok0.val ≤ k0.val) (hc0 : c0.val = 0)
    (hdec : LZ77.decode (toks out0 ntok0.val) = some ((bytes input).take k0.val)) :
    slot.v_fl_emit_lits_loop input out0 n cnt1 k0 c0 ntok0 ⦃ fun r =>
      r.2.1.val ≤ n.val ∧ (k0.val < r.2.1.val ∨ cnt1.val = 0 ∨ k0.val = n.val) ∧
      r.2.2.val ≤ r.2.1.val ∧ r.1.length = out0.length ∧
      LZ77.decode (toks r.1 r.2.2.val) = some ((bytes input).take r.2.1.val) ⦄ := by
  rw [slot.v_fl_emit_lits_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => n.val - s.2.1.val)
    (inv := fun s =>
      s.2.1.val ≤ n.val ∧ s.2.1.val = k0.val + s.2.2.1.val ∧ s.2.2.2.val ≤ s.2.1.val ∧
      s.1.length = out0.length ∧
      LZ77.decode (toks s.1 s.2.2.2.val) = some ((bytes input).take s.2.1.val))
  · rintro ⟨out, k, c, ntok⟩ ⟨hkn, hkc, hnt, hlen, hde⟩
    simp only at hkn hkc hnt hlen hde
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.v_fl_emit_lits_loop.body]
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
theorem fl_emit_lits_spec (input : Slice Std.U8) (out : Slice Std.U32) (pos0 cnt ntok0 : Std.Usize)
    (hout : input.length ≤ out.length) (hpos : pos0.val ≤ input.length)
    (hntok : ntok0.val ≤ pos0.val)
    (hdec : LZ77.decode (toks out ntok0.val) = some ((bytes input).take pos0.val)) :
    slot.v_fl_emit_lits input out pos0 cnt ntok0 ⦃ fun r =>
      (pos0.val < r.1.2.val ∨ pos0.val = input.length) ∧ r.1.2.val ≤ input.length ∧ r.1.1.val ≤ r.1.2.val ∧
      r.2.length = out.length ∧
      LZ77.decode (toks r.2 r.1.1.val) = some ((bytes input).take r.1.2.val) ⦄ := by
  rw [slot.v_fl_emit_lits]
  apply Std.WP.spec_bind (Pₘ := fun (c : Std.Usize) => 1 ≤ c.val)
  · split <;> simp only [Std.WP.spec_ok] <;> scalar_tac
  intro cnt1 hc1
  apply Std.WP.spec_bind (fl_emit_lits_loop_spec input out _ cnt1 pos0 0#usize ntok0
    (by simp) hout (by scalar_tac) hntok (by simp) hdec)
  rintro ⟨out1, k, ntok⟩ ⟨h1, h2, h3, h4, h5⟩
  simp only at h1 h2 h3 h4 h5
  step*
  all_goals exact ⟨by scalar_tac, by scalar_tac, h3, h4, h5⟩
@[local step]
theorem fl_emit_step_spec (input : Slice Std.U8) (out : Slice Std.U32) (pos d l lits ntok : Std.Usize)
    (hout : input.length ≤ out.length) (hpos : pos.val < input.length)
    (hntok : ntok.val ≤ pos.val)
    (hdec : LZ77.decode (toks out ntok.val) = some ((bytes input).take pos.val)) :
    slot.v_fl_emit_step input out pos d l lits ntok ⦃ fun r =>
      pos.val < r.1.2.val ∧ r.1.2.val ≤ input.length ∧ r.1.1.val ≤ r.1.2.val ∧
      r.2.length = out.length ∧
      LZ77.decode (toks r.2 r.1.1.val) = some ((bytes input).take r.1.2.val) ⦄ := by
  rw [slot.v_fl_emit_step]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  apply Std.WP.spec_bind (fl_verified_spec input pos d l)
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
    apply Std.WP.spec_mono (fl_emit_lits_spec input out pos lits ntok hout (by scalar_tac) hntok hdec)
    rintro ⟨⟨t, k⟩, o⟩ ⟨h1, h2, h3, h4, h5⟩
    exact ⟨by scalar_tac, h2, h3, h4, h5⟩
@[local step]
theorem fl_byte_spec (input : Slice Std.U8) (i : Std.Usize) :
    slot.v_fl_byte input i ⦃ fun _ => True ⦄ := by
  rw [slot.v_fl_byte]
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
  all_goals scalar_tac
@[local step]
theorem fl_ld4_spec (input : Slice Std.U8) (p : Std.Usize) :
    slot.v_fl_ld4 input p ⦃ fun _ => True ⦄ := by
  rw [slot.v_fl_ld4]
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
  all_goals scalar_tac
@[local step]
theorem fl_ld8_spec (input : Slice Std.U8) (p : Std.Usize) :
    slot.v_fl_ld8 input p ⦃ fun _ => True ⦄ := by
  rw [slot.v_fl_ld8]
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
  all_goals scalar_tac
@[local step]
theorem fl_len_loop_spec (input : Slice Std.U8) (a : Std.Usize) (b : Std.Usize) (cap : Std.Usize) (l : Std.Usize) (go : Std.Usize) (it : Std.Usize)  :
    slot.v_fl_len_loop input a b cap l go it ⦃ fun _ => True ⦄ := by
  rw [slot.v_fl_len_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => 40 - s.2.2.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1, x2⟩ _
    simp only [slot.v_fl_len_loop.body, lift, Array.to_slice_mut]
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
    all_goals scalar_tac
  · trivial
@[local step]
theorem fl_len_spec (input : Slice Std.U8) (a : Std.Usize) (b : Std.Usize) (cap : Std.Usize) :
    slot.v_fl_len input a b cap ⦃ fun _ => True ⦄ := by
  rw [slot.v_fl_len]
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
  all_goals scalar_tac
@[local step]
theorem fl_hashp_spec (input : Slice Std.U8) (p : Std.Usize) (hsh : Std.U64) :
    slot.v_fl_hashp input p hsh ⦃ fun r => r.val < 65536 ⦄ := by
  rw [slot.v_fl_hashp]
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
  all_goals scalar_tac
@[local step]
theorem fl_log16_spec (f : Std.U32) :
    slot.v_fl_log16 f ⦃ fun _ => True ⦄ := by
  rw [slot.v_fl_log16]
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
  all_goals scalar_tac
@[local step]
theorem fl_sample_loop_spec (input : Slice Std.U8) (h : Array Std.U32 256#usize) (n : Std.Usize) (st : Std.Usize) (k : Std.Usize) (c : Std.Usize) (hn : n.val = input.length) :
    slot.v_fl_sample_loop input h n st k c ⦃ fun _ => True ⦄ := by
  rw [slot.v_fl_sample_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => 8192 - s.2.2.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1, x2⟩ _
    simp only [slot.v_fl_sample_loop.body, lift, Array.to_slice_mut]
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
    all_goals scalar_tac
  · trivial
@[local step]
theorem fl_sample_spec (input : Slice Std.U8) (h : Array Std.U32 256#usize) :
    slot.v_fl_sample input h ⦃ fun _ => True ⦄ := by
  rw [slot.v_fl_sample]
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
  all_goals scalar_tac
@[local step]
theorem fl_costs_loop0_spec (h : Array Std.U32 256#usize) (t : Std.U32) (i : Std.Usize)  :
    slot.v_fl_costs_loop0 h t i ⦃ fun _ => True ⦄ := by
  rw [slot.v_fl_costs_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun s => 256 - s.2.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1⟩ _
    simp only [slot.v_fl_costs_loop0.body, lift, Array.to_slice_mut]
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
    all_goals scalar_tac
  · trivial
@[local step]
theorem fl_costs_loop1_spec (h : Array Std.U32 256#usize) (cost : Array Std.U32 256#usize) (lt : Std.U32) (j : Std.Usize)  :
    slot.v_fl_costs_loop1 h cost lt j ⦃ fun _ => True ⦄ := by
  rw [slot.v_fl_costs_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun s => 256 - s.2.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1⟩ _
    simp only [slot.v_fl_costs_loop1.body, lift, Array.to_slice_mut]
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
    all_goals scalar_tac
  · trivial
@[local step]
theorem fl_costs_spec (h : Array Std.U32 256#usize) (cost : Array Std.U32 256#usize) :
    slot.v_fl_costs h cost ⦃ fun _ => True ⦄ := by
  rw [slot.v_fl_costs]
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
  all_goals scalar_tac
@[local step]
theorem fl_ent_loop0_spec (h : Array Std.U32 1024#usize) (base : Std.Usize) (t : Std.U32) (i : Std.Usize)  :
    slot.v_fl_ent_loop0 h base t i ⦃ fun _ => True ⦄ := by
  rw [slot.v_fl_ent_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun s => 256 - s.2.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1⟩ _
    simp only [slot.v_fl_ent_loop0.body, lift, Array.to_slice_mut]
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
    all_goals scalar_tac
  · trivial
@[local step]
theorem fl_ent_loop1_spec (h : Array Std.U32 1024#usize) (base : Std.Usize) (lt : Std.U32) (bits : Std.Usize) (j : Std.Usize)  :
    slot.v_fl_ent_loop1 h base lt bits j ⦃ fun _ => True ⦄ := by
  rw [slot.v_fl_ent_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun s => 256 - s.2.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1⟩ _
    simp only [slot.v_fl_ent_loop1.body, lift, Array.to_slice_mut]
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
    all_goals scalar_tac
  · trivial
@[local step]
theorem fl_ent_spec (h : Array Std.U32 1024#usize) (base : Std.Usize) :
    slot.v_fl_ent h base ⦃ fun _ => True ⦄ := by
  rw [slot.v_fl_ent]
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
  all_goals scalar_tac
@[local step]
theorem fl_stats_loop0_spec (h : Array Std.U32 256#usize) (t : Std.U32) (i : Std.Usize)  :
    slot.v_fl_stats_loop0 h t i ⦃ fun _ => True ⦄ := by
  rw [slot.v_fl_stats_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun s => 256 - s.2.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1⟩ _
    simp only [slot.v_fl_stats_loop0.body, lift, Array.to_slice_mut]
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
    all_goals scalar_tac
  · trivial
@[local step]
theorem fl_stats_loop1_spec (h : Array Std.U32 256#usize) (t : Std.U32) (lt : Std.U32) (bits : Std.Usize) (top : Std.U32) (np : Std.Usize) (big : Std.Usize) (bigsum : Std.Usize) (j : Std.Usize)  :
    slot.v_fl_stats_loop1 h t lt bits top np big bigsum j ⦃ fun _ => True ⦄ := by
  rw [slot.v_fl_stats_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun s => 256 - s.2.2.2.2.2.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1, x2, x3, x4, x5⟩ _
    simp only [slot.v_fl_stats_loop1.body, lift, Array.to_slice_mut]
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
    all_goals scalar_tac
  · trivial
@[local step]
theorem fl_stats_spec (h : Array Std.U32 256#usize) :
    slot.v_fl_stats h ⦃ fun _ => True ⦄ := by
  rw [slot.v_fl_stats]
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
  all_goals scalar_tac
@[local step]
theorem fl_probe_chunk_loop_spec (input : Slice Std.U8) (tab : Array Std.U32 4096#usize) (ph : Array Std.U32 1024#usize) (s : Std.Usize) (p : Std.Usize) (k : Std.Usize) (c4 : Std.Usize)  :
    slot.v_fl_probe_chunk_loop input tab ph s p k c4 ⦃ fun _ => True ⦄ := by
  rw [slot.v_fl_probe_chunk_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => slot.V_FL_PCH.val - s.2.2.2.1.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1, x2, x3, x4⟩ _
    simp only [slot.v_fl_probe_chunk_loop.body, lift, Array.to_slice_mut]
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
    all_goals scalar_tac
  · trivial
@[local step]
theorem fl_weights_loop_spec (input : Slice Std.U8) (tab : Array Std.U32 4096#usize) (ph : Array Std.U32 1024#usize) (pnc : Std.Usize) (span : Std.Usize) (c4 : Std.Usize) (i : Std.Usize)  :
    slot.v_fl_weights_loop input tab ph pnc span c4 i ⦃ fun _ => True ⦄ := by
  rw [slot.v_fl_weights_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => pnc.val - s.2.2.2.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1, x2, x3⟩ _
    simp only [slot.v_fl_weights_loop.body, lift, Array.to_slice_mut]
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
    all_goals scalar_tac
  · trivial
@[local step]
theorem fl_weights_spec (input : Slice Std.U8) (dp : slot.V_Params) :
    slot.v_fl_weights input dp ⦃ fun _ => True ⦄ := by
  have hpnc : 0 < (if dp.fl_pnc = 0#usize then 1#usize else dp.fl_pnc).val := by
    split <;> scalar_tac
  rw [slot.v_fl_weights]
  try simp only [lift, Array.to_slice_mut, ite_ok]
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
  all_goals scalar_tac
@[local step]
theorem fl_mode_spec (input : Slice Std.U8) (st : Std.U64) (dp : slot.V_Params) :
    slot.v_fl_mode input st dp ⦃ fun _ => True ⦄ := by
  rw [slot.v_fl_mode]
  try simp only [lift, Array.to_slice_mut, ite_ok]
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
  all_goals scalar_tac
@[local step]
theorem fl_config_spec («class» : Std.Usize) (cf : Array Std.Usize 8#usize) (dp : slot.V_Params) :
    slot.v_fl_config «class» cf dp ⦃ fun _ => True ⦄ := by
  rw [slot.v_fl_config]
  try simp only [lift, Array.to_slice_mut, ite_ok]
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
  all_goals scalar_tac
section
attribute [local step] ite_true_spec
@[local step]
theorem fl_lit_parse_spec (input : Slice Std.U8) (out : Slice Std.U32)
    (hlen : input.length ≤ out.length) :
    slot.v_fl_lit_parse input out ⦃ fun r =>
      r.1.2.val ≤ input.length ∧ r.1.1.val ≤ r.1.2.val ∧ r.2.length = out.length ∧
      LZ77.decode (toks r.2 r.1.1.val) = some ((bytes input).take r.1.2.val) ⦄ := by
  rw [slot.v_fl_lit_parse]
  have h0 := decode_nil input out
  try simp only [lift, Array.to_slice_mut, alloc.vec.Vec.deref_mut, bind_tc_ok]
  step*
  all_goals (repeat (first
    | (refine ⟨by scalar_tac, by scalar_tac, by scalar_tac, by assumption⟩)
    | (intro hc; (try step*))
    | (casesm* _ × _; (try simp only []); (try step*))
    | (split <;> (try step*))
    | (step <;> (try step*))))
  all_goals (try scalar_tac)
end
attribute [local step] fl_lit_parse_spec
section
attribute [local step] ite_true_spec
@[local step]
theorem fl_rle_parse_loop_spec (input : Slice Std.U8) (out0 : Slice Std.U32) (n : Std.Usize) (pos0 : Std.Usize) (ntok0 : Std.Usize)
    (hn : n.val = input.length) (hout : input.length ≤ out0.length)
    (hp : pos0.val ≤ n.val) (hntok : ntok0.val ≤ pos0.val)
    (hdec : LZ77.decode (toks out0 ntok0.val) = some ((bytes input).take pos0.val)) :
    slot.v_fl_rle_parse_loop input out0 n pos0 ntok0 ⦃ fun r =>
      r.2.1.val ≤ n.val ∧ r.2.2.val ≤ r.2.1.val ∧ r.1.length = out0.length ∧
      LZ77.decode (toks r.1 r.2.2.val) = some ((bytes input).take r.2.1.val) ⦄ := by
  rw [slot.v_fl_rle_parse_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => n.val - s.2.1.val)
    (inv := fun s =>
      s.2.1.val ≤ n.val ∧ s.2.2.val ≤ s.2.1.val ∧ s.1.length = out0.length ∧
      LZ77.decode (toks s.1 s.2.2.val) = some ((bytes input).take s.2.1.val))
  · rintro ⟨out, pos, ntok⟩ ⟨hpn, hnt, hlen, hde⟩
    simp only at hpn hnt hlen hde
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.v_fl_rle_parse_loop.body, lift, Array.to_slice_mut, alloc.vec.Vec.deref_mut, bind_tc_ok]
    split
    case isTrue hlt =>
      step*
      all_goals (repeat (first
        | (refine ⟨by scalar_tac, by scalar_tac, by assumption, by assumption, by scalar_tac⟩)
        | (intro hc; (try step*))
        | (casesm* _ × _; (try simp only []); (try step*))
        | (split <;> (try step*))
        | (step <;> (try step*))))
      all_goals (try scalar_tac)
    case isFalse hge =>
      exact ⟨hpn, hnt, hlen, hde⟩
  · exact ⟨hp, hntok, rfl, hdec⟩
end
attribute [local step] fl_rle_parse_loop_spec
section
attribute [local step] ite_true_spec
@[local step]
theorem fl_rle_parse_spec (input : Slice Std.U8) (out : Slice Std.U32)
    (hlen : input.length ≤ out.length) :
    slot.v_fl_rle_parse input out ⦃ fun r =>
      r.1.2.val ≤ input.length ∧ r.1.1.val ≤ r.1.2.val ∧ r.2.length = out.length ∧
      LZ77.decode (toks r.2 r.1.1.val) = some ((bytes input).take r.1.2.val) ⦄ := by
  rw [slot.v_fl_rle_parse]
  have h0 := decode_nil input out
  try simp only [lift, Array.to_slice_mut, alloc.vec.Vec.deref_mut, bind_tc_ok]
  step*
  all_goals (repeat (first
    | (refine ⟨by scalar_tac, by scalar_tac, by scalar_tac, by assumption⟩)
    | (intro hc; (try step*))
    | (casesm* _ × _; (try simp only []); (try step*))
    | (split <;> (try step*))
    | (step <;> (try step*))))
  all_goals (try scalar_tac)
end
attribute [local step] fl_rle_parse_spec
@[local step]
theorem fl_cheap_run_loop_spec (input : Slice Std.U8) (cost : Array Std.U32 256#usize) (n : Std.Usize) (k : Std.Usize) (hn : n.val = input.length) :
    slot.v_fl_cheap_run_loop input cost n k ⦃ fun _ => True ⦄ := by
  rw [slot.v_fl_cheap_run_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => n.val - s.val)
    (inv := fun s => True)
  · rintro x0 _
    simp only [slot.v_fl_cheap_run_loop.body, lift, Array.to_slice_mut]
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
    all_goals scalar_tac
  · trivial
@[local step]
theorem fl_cheap_run_spec (input : Slice Std.U8) (cost : Array Std.U32 256#usize) (pos : Std.Usize) :
    slot.v_fl_cheap_run input cost pos ⦃ fun _ => True ⦄ := by
  rw [slot.v_fl_cheap_run]
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
  all_goals scalar_tac
@[local step]
theorem fl_span_cost_loop_spec (input : Slice Std.U8) (cost : Array Std.U32 256#usize) (pos : Std.Usize) (l : Std.Usize) (s : Std.Usize) (i : Std.Usize)  :
    slot.v_fl_span_cost_loop input cost pos l s i ⦃ fun _ => True ⦄ := by
  rw [slot.v_fl_span_cost_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => l.val - s.2.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1⟩ _
    simp only [slot.v_fl_span_cost_loop.body, lift, Array.to_slice_mut]
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
    all_goals scalar_tac
  · trivial
@[local step]
theorem fl_dextra_spec (d : Std.Usize) :
    slot.v_fl_dextra d ⦃ fun _ => True ⦄ := by
  rw [slot.v_fl_dextra]
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
  all_goals scalar_tac
@[local step]
theorem fl_lextra_spec (l : Std.Usize) :
    slot.v_fl_lextra l ⦃ fun _ => True ⦄ := by
  rw [slot.v_fl_lextra]
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
  all_goals scalar_tac
@[local step]
theorem fl_dna_ok_spec (input : Slice Std.U8) (cost : Array Std.U32 256#usize) (pos : Std.Usize) (l : Std.Usize) (d : Std.Usize) :
    slot.v_fl_dna_ok input cost pos l d ⦃ fun _ => True ⦄ := by
  rw [slot.v_fl_dna_ok]
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
  all_goals scalar_tac
@[local step]
theorem fl_dwalk_loop_spec (input : Slice Std.U8) (prev : Array Std.U32 32768#usize) (pos : Std.Usize) (cap : Std.Usize) (depth : Std.Usize) (bl : Std.Usize) (bd : Std.Usize) (cur : Std.Usize) (k : Std.Usize)  :
    slot.v_fl_dwalk_loop input prev pos cap depth bl bd cur k ⦃ fun _ => True ⦄ := by
  rw [slot.v_fl_dwalk_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => depth.val - s.2.2.2.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1, x2, x3⟩ _
    simp only [slot.v_fl_dwalk_loop.body, lift, Array.to_slice_mut]
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
    all_goals scalar_tac
  · trivial
@[local step]
theorem fl_dwalk_spec (input : Slice Std.U8) (prev : Array Std.U32 32768#usize) (pos : Std.Usize) (start : Std.Usize) (cap : Std.Usize) (depth : Std.Usize) :
    slot.v_fl_dwalk input prev pos start cap depth ⦃ fun _ => True ⦄ := by
  rw [slot.v_fl_dwalk]
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
  all_goals scalar_tac
@[local step]
theorem fl_dsearch_spec (input : Slice Std.U8) (head : Array Std.U32 65536#usize) (prev : Array Std.U32 32768#usize) (p : Std.Usize) (depth : Std.Usize) :
    slot.v_fl_dsearch input head prev p depth ⦃ fun _ => True ⦄ := by
  rw [slot.v_fl_dsearch]
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
  all_goals scalar_tac
@[local step]
theorem fl_tinsert_loop_spec (input : Slice Std.U8) (head : Array Std.U16 16384#usize) (prev : Array Std.U16 32768#usize) («to» : Std.Usize) (hsh : Std.U64) (lim : Std.Usize) (p : Std.Usize)  :
    slot.v_fl_tinsert_loop input head prev «to» hsh lim p ⦃ fun _ => True ⦄ := by
  rw [slot.v_fl_tinsert_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => «to».val - s.2.2.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1, x2⟩ _
    simp only [slot.v_fl_tinsert_loop.body, lift, Array.to_slice_mut]
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
    all_goals scalar_tac
  · trivial
@[local step]
theorem fl_tinsert_spec (input : Slice Std.U8) (head : Array Std.U16 16384#usize) (prev : Array Std.U16 32768#usize) («from» : Std.Usize) («to» : Std.Usize) (hsh : Std.U64) :
    slot.v_fl_tinsert input head prev «from» «to» hsh ⦃ fun _ => True ⦄ := by
  rw [slot.v_fl_tinsert]
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
  all_goals scalar_tac
@[local step]
theorem fl_insert_loop_spec (input : Slice Std.U8) (head : Array Std.U32 65536#usize) (prev : Array Std.U32 32768#usize) («to» : Std.Usize) (hsh : Std.U64) (lim : Std.Usize) (p : Std.Usize)  :
    slot.v_fl_insert_loop input head prev «to» hsh lim p ⦃ fun _ => True ⦄ := by
  rw [slot.v_fl_insert_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => «to».val - s.2.2.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1, x2⟩ _
    simp only [slot.v_fl_insert_loop.body, lift, Array.to_slice_mut]
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
    all_goals scalar_tac
  · trivial
@[local step]
theorem fl_insert_spec (input : Slice Std.U8) (head : Array Std.U32 65536#usize) (prev : Array Std.U32 32768#usize) («from» : Std.Usize) («to» : Std.Usize) (hsh : Std.U64) :
    slot.v_fl_insert input head prev «from» «to» hsh ⦃ fun _ => True ⦄ := by
  rw [slot.v_fl_insert]
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
  all_goals scalar_tac
section
attribute [local step] ite_true_spec
@[local step]
theorem fl_dna_parse_loop_spec (input : Slice Std.U8) (out0 : Slice Std.U32) (cost : Array Std.U32 256#usize) (n : Std.Usize) (head0 : Array Std.U32 65536#usize) (prev0 : Array Std.U32 32768#usize) (pos0 : Std.Usize) (ntok0 : Std.Usize)
    (hn : n.val = input.length) (hout : input.length ≤ out0.length)
    (hp : pos0.val ≤ n.val) (hntok : ntok0.val ≤ pos0.val)
    (hdec : LZ77.decode (toks out0 ntok0.val) = some ((bytes input).take pos0.val)) :
    slot.v_fl_dna_parse_loop input out0 cost n head0 prev0 pos0 ntok0 ⦃ fun r =>
      r.2.1.val ≤ n.val ∧ r.2.2.val ≤ r.2.1.val ∧ r.1.length = out0.length ∧
      LZ77.decode (toks r.1 r.2.2.val) = some ((bytes input).take r.2.1.val) ⦄ := by
  rw [slot.v_fl_dna_parse_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => n.val - s.2.2.2.1.val)
    (inv := fun s =>
      s.2.2.2.1.val ≤ n.val ∧ s.2.2.2.2.val ≤ s.2.2.2.1.val ∧ s.1.length = out0.length ∧
      LZ77.decode (toks s.1 s.2.2.2.2.val) = some ((bytes input).take s.2.2.2.1.val))
  · rintro ⟨out, head, prev, pos, ntok⟩ ⟨hpn, hnt, hlen, hde⟩
    simp only at hpn hnt hlen hde
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.v_fl_dna_parse_loop.body, lift, Array.to_slice_mut, alloc.vec.Vec.deref_mut, bind_tc_ok]
    split
    case isTrue hlt =>
      step*
      all_goals (repeat (first
        | (refine ⟨by scalar_tac, by scalar_tac, by assumption, by assumption, by scalar_tac⟩)
        | (intro hc; (try step*))
        | (casesm* _ × _; (try simp only []); (try step*))
        | (split <;> (try step*))
        | (step <;> (try step*))))
      all_goals (try scalar_tac)
    case isFalse hge =>
      exact ⟨hpn, hnt, hlen, hde⟩
  · exact ⟨hp, hntok, rfl, hdec⟩
end
attribute [local step] fl_dna_parse_loop_spec
section
attribute [local step] ite_true_spec
@[local step]
theorem fl_dna_parse_spec (input : Slice Std.U8) (out : Slice Std.U32) (cost : Array Std.U32 256#usize)
    (hlen : input.length ≤ out.length) :
    slot.v_fl_dna_parse input out cost ⦃ fun r =>
      r.1.2.val ≤ input.length ∧ r.1.1.val ≤ r.1.2.val ∧ r.2.length = out.length ∧
      LZ77.decode (toks r.2 r.1.1.val) = some ((bytes input).take r.1.2.val) ⦄ := by
  rw [slot.v_fl_dna_parse]
  have h0 := decode_nil input out
  try simp only [lift, Array.to_slice_mut, alloc.vec.Vec.deref_mut, bind_tc_ok]
  step*
  all_goals (repeat (first
    | (refine ⟨by scalar_tac, by scalar_tac, by scalar_tac, by assumption⟩)
    | (intro hc; (try step*))
    | (casesm* _ × _; (try simp only []); (try step*))
    | (split <;> (try step*))
    | (step <;> (try step*))))
  all_goals (try scalar_tac)
end
attribute [local step] fl_dna_parse_spec
@[local step]
theorem fl_score_spec (l : Std.Usize) (d : Std.Usize) (litq : Std.Usize) :
    slot.v_fl_score l d litq ⦃ fun _ => True ⦄ := by
  rw [slot.v_fl_score]
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
  all_goals scalar_tac
@[local step]
theorem fl_lg8_spec (x : Std.U32) :
    slot.v_fl_lg8 x ⦃ fun _ => True ⦄ := by
  rw [slot.v_fl_lg8]
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
  all_goals scalar_tac
@[local step]
theorem fl_entropy256_loop_spec (h : Array Std.U32 256#usize) (tot : Std.U64) (acc : Std.U64) (i : Std.Usize)  :
    slot.v_fl_entropy256_loop h tot acc i ⦃ fun _ => True ⦄ := by
  rw [slot.v_fl_entropy256_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => 256 - s.2.2.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1, x2⟩ _
    simp only [slot.v_fl_entropy256_loop.body, lift, Array.to_slice_mut]
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
    all_goals scalar_tac
  · trivial
@[local step]
theorem fl_entropy256_spec (h : Array Std.U32 256#usize) :
    slot.v_fl_entropy256 h ⦃ fun _ => True ⦄ := by
  rw [slot.v_fl_entropy256]
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
  all_goals scalar_tac
@[local step]
theorem fl_lit_cost_spec (h0 : Std.Usize) (dp : slot.V_Params) :
    slot.v_fl_lit_cost h0 dp ⦃ fun _ => True ⦄ := by
  have hladj : (if dp.fl_ladj > 36#usize then 36#usize else dp.fl_ladj).val ≤ 36 := by
    split <;> scalar_tac
  rw [slot.v_fl_lit_cost]
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
  all_goals scalar_tac
@[local step]
theorem fl_walk_loop_spec (input : Slice Std.U8) (prev : Array Std.U16 32768#usize) (pos : Std.Usize) (cap : Std.Usize) (depth : Std.Usize) (litq : Std.Usize) (nice : Std.Usize) (bl : Std.Usize) (bd : Std.Usize) (bs : Std.Usize) (cur : Std.Usize) (k : Std.Usize) (off : Std.Usize) (want : Std.U32)  :
    slot.v_fl_walk_loop input prev pos cap depth litq nice bl bd bs cur k off want ⦃ fun _ => True ⦄ := by
  rw [slot.v_fl_walk_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => depth.val - s.2.2.2.2.1.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1, x2, x3, x4, x5, x6⟩ _
    simp only [slot.v_fl_walk_loop.body, lift, Array.to_slice_mut]
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
    all_goals scalar_tac
  · trivial
@[local step]
theorem fl_walk_spec (input : Slice Std.U8) (prev : Array Std.U16 32768#usize) (pos : Std.Usize) (start : Std.Usize) (cap : Std.Usize) (depth : Std.Usize) (bl0 : Std.Usize) (bs0 : Std.Usize) (litq : Std.Usize) (nice : Std.Usize) :
    slot.v_fl_walk input prev pos start cap depth bl0 bs0 litq nice ⦃ fun _ => True ⦄ := by
  rw [slot.v_fl_walk]
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
  all_goals scalar_tac
@[local step]
theorem fl_search_spec (input : Slice Std.U8) (head : Array Std.U16 16384#usize) (prev : Array Std.U16 32768#usize) (pos : Std.Usize) (depth : Std.Usize) (ins : Std.Usize) (bl0 : Std.Usize) (bs0 : Std.Usize) (litq : Std.Usize) (hsh : Std.U64) (nice : Std.Usize) :
    slot.v_fl_search input head prev pos depth ins bl0 bs0 litq hsh nice ⦃ fun _ => True ⦄ := by
  rw [slot.v_fl_search]
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
  all_goals scalar_tac
@[local step]
theorem fl_insert_match_spec (input : Slice Std.U8) (head : Array Std.U16 16384#usize) (prev : Array Std.U16 32768#usize) («from» : Std.Usize) («to» : Std.Usize) (hsh : Std.U64) (ih : Std.Usize) (it : Std.Usize) :
    slot.v_fl_insert_match input head prev «from» «to» hsh ih it ⦃ fun _ => True ⦄ := by
  rw [slot.v_fl_insert_match]
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
  all_goals scalar_tac
@[local step]
theorem fl_lits_spec (miss : Std.Usize) (acc : Std.Usize) :
    slot.v_fl_lits miss acc ⦃ fun _ => True ⦄ := by
  rw [slot.v_fl_lits]
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
  all_goals scalar_tac
@[local step]
theorem fl_litq_spec (h0 : Std.Usize) (dp : slot.V_Params) :
    slot.v_fl_litq h0 dp ⦃ fun _ => True ⦄ := by
  rw [slot.v_fl_litq]
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
  all_goals scalar_tac
@[local step]
theorem fl_hsh_spec (h0 : Std.Usize) (dp : slot.V_Params) :
    slot.v_fl_hsh h0 dp ⦃ fun _ => True ⦄ := by
  rw [slot.v_fl_hsh]
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
  all_goals scalar_tac
section
attribute [local step] ite_true_spec
@[local step]
theorem fl_lazy_parse_loop_spec (input : Slice Std.U8) (out0 : Slice Std.U32) (n : Std.Usize) (depth : Std.Usize) (depth2 : Std.Usize) (lazy : Std.Usize) (nice : Std.Usize) (ih : Std.Usize) (it : Std.Usize) (acc : Std.Usize) (litq : Std.Usize) (hsh : Std.U64) (head0 : Array Std.U16 16384#usize) (prev0 : Array Std.U16 32768#usize) (pos0 : Std.Usize) (ntok0 : Std.Usize) (carry0 : Std.Usize) (miss0 : Std.Usize)
    (hn : n.val = input.length) (hout : input.length ≤ out0.length)
    (hp : pos0.val ≤ n.val) (hntok : ntok0.val ≤ pos0.val)
    (hdec : LZ77.decode (toks out0 ntok0.val) = some ((bytes input).take pos0.val)) :
    slot.v_fl_lazy_parse_loop input out0 n depth depth2 lazy nice ih it acc litq hsh head0 prev0 pos0 ntok0 carry0 miss0 ⦃ fun r =>
      r.2.1.val ≤ n.val ∧ r.2.2.val ≤ r.2.1.val ∧ r.1.length = out0.length ∧
      LZ77.decode (toks r.1 r.2.2.val) = some ((bytes input).take r.2.1.val) ⦄ := by
  rw [slot.v_fl_lazy_parse_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => n.val - s.2.2.2.1.val)
    (inv := fun s =>
      s.2.2.2.1.val ≤ n.val ∧ s.2.2.2.2.1.val ≤ s.2.2.2.1.val ∧ s.1.length = out0.length ∧
      LZ77.decode (toks s.1 s.2.2.2.2.1.val) = some ((bytes input).take s.2.2.2.1.val))
  · rintro ⟨out, head, prev, pos, ntok, carry, miss⟩ ⟨hpn, hnt, hlen, hde⟩
    simp only at hpn hnt hlen hde
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.v_fl_lazy_parse_loop.body, lift, Array.to_slice_mut, alloc.vec.Vec.deref_mut, bind_tc_ok]
    split
    case isTrue hlt =>
      step*
      all_goals (repeat (first
        | (refine ⟨by scalar_tac, by scalar_tac, by assumption, by assumption, by scalar_tac⟩)
        | (intro hc; (try step*))
        | (casesm* _ × _; (try simp only []); (try step*))
        | (split <;> (try step*))
        | (step <;> (try step*))))
      all_goals (try scalar_tac)
    case isFalse hge =>
      exact ⟨hpn, hnt, hlen, hde⟩
  · exact ⟨hp, hntok, rfl, hdec⟩
end
attribute [local step] fl_lazy_parse_loop_spec
section
attribute [local step] ite_true_spec
@[local step]
theorem fl_lazy_parse_spec (input : Slice Std.U8) (out : Slice Std.U32) (lh : Array Std.U32 256#usize) (cf : Array Std.Usize 8#usize) (dp : slot.V_Params)
    (hlen : input.length ≤ out.length) :
    slot.v_fl_lazy_parse input out lh cf dp ⦃ fun r =>
      r.1.2.val ≤ input.length ∧ r.1.1.val ≤ r.1.2.val ∧ r.2.length = out.length ∧
      LZ77.decode (toks r.2 r.1.1.val) = some ((bytes input).take r.1.2.val) ⦄ := by
  rw [slot.v_fl_lazy_parse]
  have h0 := decode_nil input out
  try simp only [lift, Array.to_slice_mut, alloc.vec.Vec.deref_mut, bind_tc_ok]
  step*
  all_goals (repeat (first
    | (refine ⟨by scalar_tac, by scalar_tac, by scalar_tac, by assumption⟩)
    | (intro hc; (try step*))
    | (casesm* _ × _; (try simp only []); (try step*))
    | (split <;> (try step*))
    | (step <;> (try step*))))
  all_goals (try scalar_tac)
end
attribute [local step] fl_lazy_parse_spec
section
attribute [local step] ite_true_spec
@[local step]
theorem fl_part_spec (input : Slice Std.U8) (out : Slice Std.U32) (mc : Std.Usize) (fh : Array Std.U32 256#usize) (dp : slot.V_Params)
    (hlen : input.length ≤ out.length) :
    slot.v_fl_part input out mc fh dp ⦃ fun r =>
      r.1.2.val ≤ input.length ∧ r.1.1.val ≤ r.1.2.val ∧ r.2.length = out.length ∧
      LZ77.decode (toks r.2 r.1.1.val) = some ((bytes input).take r.1.2.val) ⦄ := by
  rw [slot.v_fl_part]
  have h0 := decode_nil input out
  try simp only [lift, Array.to_slice_mut, alloc.vec.Vec.deref_mut, bind_tc_ok]
  step*
  all_goals (repeat (first
    | (refine ⟨by scalar_tac, by scalar_tac, by scalar_tac, by assumption⟩)
    | (intro hc; (try step*))
    | (casesm* _ × _; (try simp only []); (try step*))
    | (split <;> (try step*))
    | (step <;> (try step*))))
  all_goals (try scalar_tac)
end
attribute [local step] fl_part_spec
@[local step]
theorem prepare_loop_spec (input : Slice Std.U8) (head : Array Std.U32 65536#usize) (prev : Array Std.U32 65536#usize) (head3 : Array Std.U32 16384#usize) (shorts : Array Std.U32 4096#usize) (hs : Std.U32) (h3on : Std.Usize) («end» : Std.Usize) (p : Std.Usize)  :
    slot.v_prepare_loop input head prev head3 shorts h3on hs «end» p ⦃ fun _ => True ⦄ := by
  rw [slot.v_prepare_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => «end».val - s.2.2.2.2.val)
    (inv := fun s => True)
  · rintro ⟨x0, x1, x2, x3, x4⟩ _
    simp only [slot.v_prepare_loop.body, lift, Array.to_slice_mut]
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
    all_goals scalar_tac
  · trivial
@[local step]
theorem prepare_spec (input : Slice Std.U8) (head : Array Std.U32 65536#usize) (prev : Array Std.U32 65536#usize) (head3 : Array Std.U32 16384#usize) (shorts : Array Std.U32 4096#usize) («from» : Std.Usize) (pos : Std.Usize) (hs : Std.U32) (h3on : Std.Usize) :
    slot.v_prepare input head prev head3 shorts «from» pos hs h3on ⦃ fun _ => True ⦄ := by
  rw [slot.v_prepare]
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
  all_goals scalar_tac
open LZ77
theorem copyN_take_prefix (acc : List Nat) (d : Nat) :
    ∀ n, (copyN acc d n).take acc.length = acc := by
  intro n
  induction n with
  | zero => simp [copyN]
  | succ m ih =>
    simp only [copyN]
    rw [List.take_append_of_le_length (by simp)]
    exact ih
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
def BackDec (input : Slice Std.U8) (out : Slice Std.U32) (nt p : Nat) : Prop :=
  p ≤ input.length ∧ nt ≤ p ∧ input.length ≤ out.length ∧
    LZ77.decode (toks out nt) = some ((bytes input).take p)
theorem BackDec.pop_lit {s : Slice Std.U8} {out : Slice Std.U32} {nt p : Nat} (h : BackDec s out nt p)
    (h0 : 0 < nt) (hle : nt ≤ out.length) (ht : (out.val[nt - 1]!).val < 256) :
    1 ≤ p ∧ BackDec s out (nt - 1) (p - 1) := by
  obtain ⟨hps, hntp, hso, hde⟩ := h
  rw [toks_pop out nt h0 hle] at hde
  obtain ⟨hp1, hde'⟩ := decode_pop_lit (by simpa using hps) hde ht
  exact ⟨hp1, by omega, by omega, hso, hde'⟩
theorem BackDec.pop_match {s : Slice Std.U8} {out : Slice Std.U32} {nt p : Nat} (h : BackDec s out nt p)
    (h0 : 0 < nt) (hle : nt ≤ out.length) (ht : 256 ≤ (out.val[nt - 1]!).val) :
    tokLen (out.val[nt - 1]!).val ≤ p ∧
      BackDec s out (nt - 1) (p - tokLen (out.val[nt - 1]!).val) := by
  obtain ⟨hps, hntp, hso, hde⟩ := h
  rw [toks_pop out nt h0 hle] at hde
  obtain ⟨hw, hde'⟩ := decode_pop_match (by simpa using hps) hde ht
  have hlen := decode_length_le hde'
  rw [toks_length out (nt - 1) (by omega), List.length_take, bytes_length] at hlen
  exact ⟨hw, by omega, by omega, hso, hde'⟩
def MergeInv (input : Slice Std.U8) (out : Slice Std.U32) (P E : Nat) (p t len : Nat) : Prop :=
  BackDec input out t p ∧ p ≤ P ∧ p + len = E
theorem MergeInv.pop {input : Slice Std.U8} {out : Slice Std.U32} {P E : Nat}
    {p t len i1 w p1 len1 : Std.Usize} {tok : Std.U32}
    (h : MergeInv input out P E p.val t.val len.val)
    (hi1 : i1.val = t.val - 1) (ht0 : 0 < t.val) (htl : t.val ≤ out.length)
    (hi1l : i1.val < out.val.length) (htok : tok = out.val[i1.val])
    (hwlit : tok.val < 256 → w.val = 1)
    (hwmat : ¬tok.val < 256 → 16777216 ≤ tok.val ∧ w.val = (tok.val - 16777216) % 256 + 3)
    (hw0 : 0 < w.val) (hwp : w.val ≤ p.val) (hlenw : len.val + w.val ≤ 258)
    (hp1 : p1.val = p.val - w.val) (hlen1 : len1.val = len.val + w.val) :
    MergeInv input out P E p1.val i1.val len1.val := by
  obtain ⟨hd, hpP, hE⟩ := h
  have hv : (out.val[t.val - 1]!).val = tok.val := by
    rw [← hi1, getElem!_pos out.val i1.val hi1l, ← htok]
  have hd' : BackDec input out (t.val - 1) (p.val - w.val) := by
    by_cases hlit : tok.val < 256
    · have hw1 : w.val = 1 := hwlit hlit
      rw [hw1]
      exact (BackDec.pop_lit hd ht0 htl (by rw [hv]; exact hlit)).2
    · obtain ⟨hm, hw⟩ := hwmat hlit
      have hwm : w.val = LZ77.tokLen (out.val[t.val - 1]!).val := by
        rw [hv]; simp only [LZ77.tokLen, LZ77.MATCH_BASE]; exact hw
      rw [hwm]
      exact (BackDec.pop_match hd ht0 htl (by rw [hv]; omega)).2
  rw [hi1, hp1, hlen1]
  exact ⟨hd', by omega, by omega⟩
@[local step]
theorem back_emit_loop_spec (input : Slice Std.U8) (out : Slice Std.U32) (d : Std.Usize) (good : Bool) (p t len k : Std.Usize)
    (P E : Nat) (hinv : MergeInv input out P E p.val t.val len.val) :
    slot.v_back_emit_loop input out d good p t len k ⦃ fun r =>
      MergeInv input out P E r.1.val r.2.1.val r.2.2.val ⦄ := by
  rw [slot.v_back_emit_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => slot.V_BACK_LIMIT.val - s.2.2.2.2.val)
    (inv := fun s => MergeInv input out P E s.2.1.val s.2.2.1.val s.2.2.2.1.val)
  · rintro ⟨good, p, t, len, k⟩ hi
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    have hib := hi
    obtain ⟨⟨hpn, htp, hout, hde⟩, hpP, hE⟩ := hib
    simp only [slot.v_back_emit_loop.body]
    step*
    all_goals (repeat (first
      | (refine ⟨MergeInv.pop (w := 1#usize) hi (by scalar_tac) (by scalar_tac) (by scalar_tac) (by scalar_tac)
          (by assumption) (by intro hc; scalar_tac) (by intro hc; constructor <;> scalar_tac) (by scalar_tac) (by scalar_tac) (by scalar_tac)
          (by scalar_tac) (by scalar_tac), by scalar_tac⟩)
      | (refine ⟨MergeInv.pop (w := UScalar.cast .Usize x) hi (by scalar_tac) (by scalar_tac) (by scalar_tac) (by scalar_tac)
          (by assumption) (by intro hc; scalar_tac) (by intro hc; constructor <;> scalar_tac) (by scalar_tac) (by scalar_tac) (by scalar_tac)
          (by scalar_tac) (by scalar_tac), by scalar_tac⟩)
      | (exact hi)
      | (refine ⟨hi, by scalar_tac⟩)
      | (intro hc; try step*)
      | (casesm* _ × _; try step*)
      | (split <;> try step*)
      | (apply spec_ite_cut <;> intro hc <;> try step*)
      | (step <;> try step*)))
    all_goals try scalar_tac
  · exact hinv
theorem back_verified_eq (input : Slice Std.U8) (pos d len : Std.Usize) :
    slot.v_back_verified input pos d len = slot.v_verified input pos d len := by
  unfold slot.v_back_verified slot.v_verified
  rfl
@[local step]
theorem back_verified_spec (input : Slice Std.U8) (pos d ch : Std.Usize) :
    slot.v_back_verified input pos d ch ⦃ fun b => b = true →
      3 ≤ ch.val ∧ ch.val ≤ 258 ∧ 1 ≤ d.val ∧ d.val ≤ 32768 ∧ d.val ≤ pos.val ∧
      pos.val + ch.val ≤ input.length ∧ Matches input (pos.val - d.val) pos.val ch.val ⦄ := by
  rw [back_verified_eq]
  exact verified_spec input pos d ch
theorem back_emit_loop_false_eq (input : Slice Std.U8) (out : Slice Std.U32) (d pos ntok l k : Std.Usize) :
    slot.v_back_emit_loop input out d false pos ntok l k = ok (pos, ntok, l) := by
  rw [slot.v_back_emit_loop, Std.loop]
  simp only [slot.v_back_emit_loop.body, Bool.false_eq_true, if_false]
@[local step]
theorem back_emit_loop_init_spec (input : Slice Std.U8) (out : Slice Std.U32) (d : Std.Usize)
    (good : Bool) (pos ntok l k : Std.Usize)
    (hout : input.length ≤ out.length) (hpos : pos.val < input.length)
    (hntok : ntok.val ≤ pos.val)
    (hdec : LZ77.decode (toks out ntok.val) = some ((bytes input).take pos.val)) :
    slot.v_back_emit_loop input out d good pos ntok l k ⦃ fun r =>
      r.1.val ≤ pos.val ∧ r.2.1.val ≤ r.1.val ∧ r.1.val + r.2.2.val = pos.val + l.val ∧
      LZ77.decode (toks out r.2.1.val) = some ((bytes input).take r.1.val) ∧
      (good = false → r.1 = pos) ⦄ := by
  obtain ⟨⟨p, t, len⟩, heq, ⟨⟨hpn, htp, hso, hde⟩, hpP, hE⟩⟩ :=
    Std.WP.spec_imp_exists (back_emit_loop_spec input out d good pos ntok l k pos.val (pos.val + l.val)
      ⟨⟨by omega, hntok, hout, hdec⟩, le_refl _, rfl⟩)
  apply Std.WP.exists_imp_spec
  refine ⟨(p, t, len), heq, hpP, htp, hE, hde, ?_⟩
  intro hg
  subst good
  rw [back_emit_loop_false_eq] at heq
  exact (Prod.mk.inj (Result.ok.inj heq)).1.symm
@[local step]
theorem merge_good_spec (l : Std.Usize) :
    (if l >= 3#usize then ok (decide (l <= 258#usize)) else ok false) ⦃ fun b =>
      b = true → 3 ≤ l.val ∧ l.val ≤ 258 ⦄ := by
  split <;> simp only [Std.WP.spec_ok]
  · intro h; constructor <;> scalar_tac
  · simp
@[local step]
theorem back_emit_spec (input : Slice Std.U8) (out : Slice Std.U32) (pos d l lits ntok : Std.Usize)
    (hout : input.length ≤ out.length) (hpos : pos.val < input.length)
    (hntok : ntok.val ≤ pos.val)
    (hdec : LZ77.decode (toks out ntok.val) = some ((bytes input).take pos.val)) :
    slot.v_back_emit input out pos d l lits ntok ⦃ fun r =>
      pos.val < r.1.2.val ∧ r.1.2.val ≤ input.length ∧ r.1.1.val ≤ r.1.2.val ∧
      r.2.length = out.length ∧
      LZ77.decode (toks r.2 r.1.1.val) = some ((bytes input).take r.1.2.val) ⦄ := by
  rw [slot.v_back_emit]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  step*
  have hgood : good = true := by cases good <;> simp_all
  obtain ⟨hl3, hl258⟩ := good_post hgood
  obtain ⟨hlen3, hlen258, hd1, hdmax, hdpos, hend, hm⟩ := b_post (by assumption)
  have htok : i6.val = LZ77.mkMatch d.val len.val := by
    simp only [LZ77.mkMatch, LZ77.MATCH_BASE, i6_post, i3_post, i2_post]
    scalar_tac
  refine ⟨by scalar_tac, by scalar_tac, by scalar_tac,
    by rw [out1_post]; simp [Std.Slice.set_val_eq], ?_⟩
  rw [out1_post, show i7.val = t.val + 1 by scalar_tac,
    show i8.val = p.val + len.val by scalar_tac]
  exact emit_match input out t p.val d.val len.val i6 p_post4 (by scalar_tac) hd1 hdpos hdmax
    hlen3 hlen258 hend hm htok
section
attribute [local step] ite_true_spec
@[local step]
theorem main_parse_loop_spec (input : Slice Std.U8) (out0 : Slice Std.U32) (n : Std.Usize) (head0 : Array Std.U32 65536#usize) (prev0 : Array Std.U32 65536#usize) (head30 : Array Std.U32 16384#usize) (shorts0 : Array Std.U32 4096#usize) (litq : Std.Usize) (hs : Std.U32) (acc : Std.U64) (depth : Std.Usize) (lz : Std.Usize) (p2 : Std.Usize) (h3on : Std.Usize) (stepmax : Std.Usize) (pos0 : Std.Usize) (ntok0 : Std.Usize) (carry0 : Std.Usize) (miss0 : Std.Usize) (filled0 : Std.Usize)
    (hstep : 1 ≤ stepmax.val ∧ stepmax.val ≤ 32)
    (hn : n.val = input.length) (hout : input.length ≤ out0.length)
    (hp : pos0.val ≤ n.val) (hntok : ntok0.val ≤ pos0.val)
    (hdec : LZ77.decode (toks out0 ntok0.val) = some ((bytes input).take pos0.val)) :
    slot.v_main_parse_loop input out0 lz n head0 prev0 head30 shorts0 litq acc depth hs p2 h3on stepmax pos0 ntok0 carry0 miss0 filled0 ⦃ fun r =>
      r.1.val ≤ input.length ∧ r.2.length = out0.length ∧
      LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
  rw [slot.v_main_parse_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun s => n.val - s.2.2.2.2.2.1.val)
    (inv := fun s =>
      s.2.2.2.2.2.1.val ≤ n.val ∧ s.2.2.2.2.2.2.1.val ≤ s.2.2.2.2.2.1.val ∧ s.1.length = out0.length ∧
      LZ77.decode (toks s.1 s.2.2.2.2.2.2.1.val) = some ((bytes input).take s.2.2.2.2.2.1.val))
  · rintro ⟨out, head, prev, head3, shorts, pos, ntok, carry, miss, filled⟩ ⟨hpn, hnt, hlen, hde⟩
    simp only at hpn hnt hlen hde
    have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
    simp only [slot.v_main_parse_loop.body, lift, Array.to_slice_mut, alloc.vec.Vec.deref_mut, bind_tc_ok]
    split
    case isTrue hlt =>
      step*
      all_goals (repeat (first
        | (refine ⟨by scalar_tac, by scalar_tac, by assumption, by assumption, by scalar_tac⟩)
        | (intro hc; (try step*))
        | (casesm* _ × _; (try simp only []); (try step*))
        | (split <;> (try step*))
        | (step <;> (try step*))))
      all_goals (try scalar_tac)
    case isFalse hge =>
      have hpn' : pos.val = input.length := by scalar_tac
      refine ⟨by scalar_tac, hlen, ?_⟩
      unfold LZ77.Valid
      rw [hde, hpn']
      simp
  · exact ⟨hp, hntok, rfl, hdec⟩
end
attribute [local step] main_parse_loop_spec
@[local step]
theorem bounded_step_spec (x : Std.Usize) :
    slot.v_bounded_step x ⦃ fun r => 1 ≤ r.val ∧ r.val ≤ 32 ⦄ := by
  rw [slot.v_bounded_step]
  step*
  all_goals (repeat (split <;> step*))
  all_goals scalar_tac
section
attribute [local step] ite_true_spec
@[local step]
theorem main_parse_spec (input : Slice Std.U8) (out : Slice Std.U32) (pos0 : Std.Usize) (ntok0 : Std.Usize) (dp : slot.V_Params)
    (hlen : input.length ≤ out.length)
    (hp : pos0.val ≤ input.length) (hntok : ntok0.val ≤ pos0.val)
    (hdec : LZ77.decode (toks out ntok0.val) = some ((bytes input).take pos0.val)) :
    slot.v_main_parse input out pos0 ntok0 dp ⦃ fun r =>
      r.1.val ≤ input.length ∧
      r.2.length = out.length ∧
      LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
  rw [slot.v_main_parse]
  have h0 := decode_nil input out
  try simp only [lift, Array.to_slice_mut, alloc.vec.Vec.deref_mut, bind_tc_ok]
  step*
  all_goals (repeat (first
    | (refine ⟨by scalar_tac, by scalar_tac, valid_of_decode (by assumption) (by scalar_tac)⟩)
    | (intro hc; (try step*))
    | (casesm* _ × _; (try simp only []); (try step*))
    | (split <;> (try step*))
    | (step <;> (try step*))))
  all_goals (try (repeat split <;> scalar_tac))
end
attribute [local step] main_parse_spec
section
attribute [local step] ite_true_spec
@[local step]
theorem parse_mode_spec (input : Slice Std.U8) (out : Slice Std.U32) (m : Std.Usize)
    (hlen : input.length ≤ out.length) :
    slot.v_parse_mode input out m ⦃ fun r =>
      r.1.val ≤ input.length ∧
      r.2.length = out.length ∧
      LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
  rw [slot.v_parse_mode]
  have h0 := decode_nil input out
  try simp only [lift, Array.to_slice_mut, alloc.vec.Vec.deref_mut, bind_tc_ok]
  step*
  all_goals (repeat (first
    | (refine ⟨by scalar_tac, by scalar_tac, valid_of_decode (by assumption) (by scalar_tac)⟩)
    | (intro hc; (try step*))
    | (casesm* _ × _; (try simp only []); (try step*))
    | (split <;> (try step*))
    | (step <;> (try step*))))
  all_goals (try scalar_tac)
end
attribute [local step] parse_mode_spec
theorem parse_spec (input : Slice Std.U8) (out : Slice Std.U32)
    (hlen : input.length ≤ out.length) :
    slot.v_parse input out ⦃ fun r =>
      r.1.val ≤ input.length ∧ r.2.length = out.length ∧
      LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
  rw [slot.v_parse]
  exact parse_mode_spec input out 7#usize hlen
end EV
@[local step]
theorem row_0_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.row_0 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧
 LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.row_0]
 exact E_M.run_spec _ _ _ _ _ _ _ _ _ _ _ _ _ _ input out hlen (by simp) (by simp) (by simp) (by simp) (by simp) (by simp) (by simp)
@[local step]
theorem row_1_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.row_1 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧
 LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.row_1]
 exact E_M.run_spec _ _ _ _ _ _ _ _ _ _ _ _ _ _ input out hlen (by simp) (by simp) (by simp) (by simp) (by simp) (by simp) (by simp)
@[local step]
theorem row_2_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.row_2 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧
 LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.row_2]
 exact E_M.run_spec _ _ _ _ _ _ _ _ _ _ _ _ _ _ input out hlen (by simp) (by simp) (by simp) (by simp) (by simp) (by simp) (by simp)
@[local step]
theorem row_3_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.row_3 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧
 LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.row_3]
 exact E_M.run_spec _ _ _ _ _ _ _ _ _ _ _ _ _ _ input out hlen (by simp) (by simp) (by simp) (by simp) (by simp) (by simp) (by simp)
@[local step]
theorem row_4_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.row_4 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧
 LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.row_4]
 exact E_M.run_spec _ _ _ _ _ _ _ _ _ _ _ _ _ _ input out hlen (by simp) (by simp) (by simp) (by simp) (by simp) (by simp) (by simp)
@[local step]
theorem row_5_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.row_5 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧
 LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.row_5]
 exact E_M.run_spec _ _ _ _ _ _ _ _ _ _ _ _ _ _ input out hlen (by simp) (by simp) (by simp) (by simp) (by simp) (by simp) (by simp)
@[local step]
theorem row_6_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.row_6 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧
 LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.row_6]
 exact E_M.run_spec _ _ _ _ _ _ _ _ _ _ _ _ _ _ input out hlen (by simp) (by simp) (by simp) (by simp) (by simp) (by simp) (by simp)
@[local step]
theorem row_7_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.row_7 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧
 LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.row_7]
 exact E_M.run_spec _ _ _ _ _ _ _ _ _ _ _ _ _ _ input out hlen (by simp) (by simp) (by simp) (by simp) (by simp) (by simp) (by simp)
@[local step]
theorem row_8_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.row_8 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧
 LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.row_8]
 exact E_M.run_spec _ _ _ _ _ _ _ _ _ _ _ _ _ _ input out hlen (by simp) (by simp) (by simp) (by simp) (by simp) (by simp) (by simp)
@[local step]
theorem row_9_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.row_9 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧
 LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.row_9]
 exact E_M.run_spec _ _ _ _ _ _ _ _ _ _ _ _ _ _ input out hlen (by simp) (by simp) (by simp) (by simp) (by simp) (by simp) (by simp)
@[local step]
theorem row_10_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.row_10 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧
 LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.row_10]
 exact E_M.run_spec _ _ _ _ _ _ _ _ _ _ _ _ _ _ input out hlen (by simp) (by simp) (by simp) (by simp) (by simp) (by simp) (by simp)
@[local step]
theorem row_11_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.row_11 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧
 LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.row_11]
 exact E_M.run_spec _ _ _ _ _ _ _ _ _ _ _ _ _ _ input out hlen (by simp) (by simp) (by simp) (by simp) (by simp) (by simp) (by simp)
@[local step]
theorem row_12_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.row_12 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧
 LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.row_12]
 exact E_M.run_spec _ _ _ _ _ _ _ _ _ _ _ _ _ _ input out hlen (by simp) (by simp) (by simp) (by simp) (by simp) (by simp) (by simp)
@[local step]
theorem row_13_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.row_13 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧
 LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.row_13]
 exact E_M.run_spec _ _ _ _ _ _ _ _ _ _ _ _ _ _ input out hlen (by simp) (by simp) (by simp) (by simp) (by simp) (by simp) (by simp)
@[local step]
theorem row_14_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.row_14 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧
 LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.row_14]
 exact E_M.run_spec _ _ _ _ _ _ _ _ _ _ _ _ _ _ input out hlen (by simp) (by simp) (by simp) (by simp) (by simp) (by simp) (by simp)
@[local step]
theorem row_15_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.row_15 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧
 LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.row_15]
 exact E_M.run_spec _ _ _ _ _ _ _ _ _ _ _ _ _ _ input out hlen (by simp) (by simp) (by simp) (by simp) (by simp) (by simp) (by simp)
@[local step]
theorem row_16_spec (input : Slice Std.U8) (out : Slice Std.U32) (hlen : input.length ≤ out.length) : slot.row_16 input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧
 LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.row_16]
 exact E_M.run_spec _ _ _ _ _ _ _ _ _ _ _ _ _ _ input out hlen (by simp) (by simp) (by simp) (by simp) (by simp) (by simp) (by simp)
attribute [local step] E_M.run_spec E_M.run_dna_spec EY.parse_spec EV.parse_spec
@[local step]
theorem fallback_spec (input : Slice Std.U8) (out : Slice Std.U32)
 (hlen : input.length ≤ out.length) : slot.fallback input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧
 LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.fallback]
 apply Std.WP.spec_bind (E_M.sniff_spec input)
 intro cls _
 repeat' ((try dsimp only); split)
 all_goals step*
@[local step]
theorem route_spec (input : Slice Std.U8) : slot.route input ⦃ fun _ => True ⦄ := by
 rw [slot.route]
 step*
 all_goals repeat' (first | (split <;> step*) | scalar_tac)
theorem parse_spec (input : Slice Std.U8) (out : Slice Std.U32)
 (hlen : input.length ≤ out.length) : slot.parse input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧
 LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
 rw [slot.parse]
 apply Std.WP.spec_bind (route_spec input)
 intro k _
 repeat' ((try dsimp only); split)
 all_goals step*
end Submission
