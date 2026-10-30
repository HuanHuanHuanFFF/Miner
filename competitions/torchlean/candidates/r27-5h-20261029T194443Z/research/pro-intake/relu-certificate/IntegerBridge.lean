import ContractExact

/-!
STATUS: NOT_COMPILED. Original small algebra bridge, not a replacement Kernel.
No Lean/lake executable was available; no toolchain was installed.
Theorems below have ordinary tactic proof drafts, no sorry/axiom/native_decide.
They DO NOT close the UInt64, array/preparation, or FloatLib rounding connections.
See REPORT.md for exact remaining proof interfaces and runtime guards.
-/

namespace ReLUSignCertificate

def packA (a0 a1 a2 : Nat) : Nat :=
  a0 + 1048576 * a1 + 1099511627776 * a2

def packC (b0 b1 b2 : Nat) : Nat :=
  b2 + 1048576 * b1 + 1099511627776 * b0

/-- Only linear arithmetic with division/modulo by positive constants remains. -/
theorem middle_field (p lo mid hi : Nat)
    (hp : p = lo + 1099511627776 * mid + 1152921504606846976 * hi)
    (hl : lo < 1099511627776) (hm : mid < 1048576) :
    ((p % 18446744073709551616) / 1099511627776) % 1048576 = mid := by
  omega

/-- Universal six-byte result; multiplication is a natural product modulo 2^64.
The native UInt64 expression still needs its standard toNat/bit-operation bridge. -/
theorem packed_three (a0 a1 a2 b0 b1 b2 : Nat)
    (ha0 : a0 ≤ 255) (ha1 : a1 ≤ 255) (ha2 : a2 ≤ 255)
    (hb0 : b0 ≤ 255) (hb1 : b1 ≤ 255) (hb2 : b2 ≤ 255) :
    (((packA a0 a1 a2 * packC b0 b1 b2) % 18446744073709551616)
      / 1099511627776) % 1048576 = a0*b0 + a1*b1 + a2*b2 := by
  have h02 := Nat.mul_le_mul ha0 hb2
  have h01 := Nat.mul_le_mul ha0 hb1
  have h12 := Nat.mul_le_mul ha1 hb2
  have h00 := Nat.mul_le_mul ha0 hb0
  have h11 := Nat.mul_le_mul ha1 hb1
  have h22 := Nat.mul_le_mul ha2 hb2
  norm_num at h02 h01 h12 h00 h11 h22
  apply middle_field _
    (a0*b2 + 1048576*(a0*b1 + a1*b2))
    (a0*b0 + a1*b1 + a2*b2)
    (a1*b0 + a2*b1 + 1048576*a2*b0)
  · unfold packA packC
    ring
  · omega
  · omega

theorem signed_offset_three (a0 a1 a2 b0 b1 b2 : Int) :
    (a0+128)*(b0+128) + (a1+128)*(b1+128) + (a2+128)*(b2+128)
      -128*((a0+128)+(a1+128)+(a2+128))
      -128*((b0+128)+(b1+128)+(b2+128)) +16384*3
      = a0*b0+a1*b1+a2*b2 := by
  ring

theorem unsigned_left_offset_three (a0 a1 a2 b0 b1 b2 : Int) :
    a0*(b0+128)+a1*(b1+128)+a2*(b2+128)
      -128*(a0+a1+a2) = a0*b0+a1*b1+a2*b2 := by
  ring

theorem residual_expansion (ta tb qa qb ra rb : Int) :
    (ta*qa+ra)*(tb*qb+rb)-ta*tb*(qa*qb)
      = ta*qa*rb+tb*qb*ra+ra*rb := by
  ring

/-- Normalized nonnegative factors, local conservative error bound. -/
theorem positive_error (a b da db : ℚ)
    (ha : 0 ≤ a) (hb : 0 ≤ b)
    (hda0 : 0 ≤ da) (hda1 : da ≤ 1)
    (hdb0 : 0 ≤ db) (hdb1 : db ≤ 1) :
    (a+da)*(b+db)-a*b ≤ a+b+1 := by
  have h1 := mul_nonneg ha (sub_nonneg.mpr hdb1)
  have h2 := mul_nonneg hb (sub_nonneg.mpr hda1)
  have h3 : da*db ≤ 1 := by
    calc da*db ≤ 1*db := mul_le_mul_of_nonneg_right hda1 hdb0
         _ ≤ 1 := by simpa using hdb1
  nlinarith

/-- A negative weight's same-sign truncation residual cannot raise the sum. -/
theorem negative_weight_error (a b da db : ℚ)
    (ha : 0 ≤ a) (hb : b ≤ 0) (hda : 0 ≤ da) (hdb : db ≤ 0) :
    (a+da)*(b+db) ≤ a*b := by
  have h1 := mul_nonpos_of_nonneg_of_nonpos ha hdb
  have h2 := mul_nonpos_of_nonpos_of_nonneg hb hda
  have h3 := mul_nonpos_of_nonneg_of_nonpos hda hdb
  nlinarith

def prefixSum (f : Nat → ℚ) : Nat → ℚ
  | 0 => 0
  | n+1 => prefixSum f n + f n

theorem prefixSum_le (n : Nat) (f g : Nat → ℚ)
    (h : ∀ i, i < n → f i ≤ g i) : prefixSum f n ≤ prefixSum g n := by
  induction n with
  | zero => simp [prefixSum]
  | succ n ih =>
      have hs := ih (fun i hi => h i (Nat.lt.step hi))
      exact add_le_add hs (h n (Nat.lt_succ_self n))

/-- Metadata aggregation interface. hA/hAK/hP/hK are explicit remaining
preparation/summation obligations; none may be assumed by runtime unchecked. -/
theorem metadata_upper (dot q termA termP termK aSum aMax k eta p : ℚ)
    (hDot : dot ≤ q+termA+termP+termK)
    (hA : termA ≤ aSum) (hAK : termA ≤ aMax*k)
    (hP : termP ≤ eta*p) (hK : termK ≤ eta*k) :
    dot ≤ q + min aSum (aMax*k) + eta*(p+k) := by
  have hm : termA ≤ min aSum (aMax*k) := le_min hA hAK
  linarith

/-- Complete total: bias is part of the certificate, with an explicit upper bound. -/
theorem total_negative (dot bias q err biasHi : ℚ)
    (hd : dot ≤ q+err) (hb : bias ≤ biasHi)
    (hc : q+err+biasHi < 0) : dot+bias < 0 := by
  linarith

theorem positive_scale_negative (total scaled delta : ℚ)
    (heq : total = delta*scaled) (hd : 0 < delta) (hs : scaled < 0) :
    total < 0 := by
  rw [heq]
  exact mul_neg_of_pos_of_neg hd hs

/-- Direct evaluations of the ACTUAL Contract definitions, not an invented API. -/
example : ExactRuntime.act true (0x80000000 : UInt32) = 0 := by decide
example : ExactRuntime.act true (0xff800000 : UInt32) = 0 := by decide
example : ExactRuntime.act true (0xffc00001 : UInt32) = 0xffc00001 := by decide
example : ExactRuntime.act false (0x80000000 : UInt32) = 0x80000000 := by decide

end ReLUSignCertificate
