namespace Submission.UnderflowZero

open FloatLib.Floats Competition
open FloatLib.Floats.Formats.BinaryInterchange
open Model.NativeBinary32

/-- A sign-independent strict magnitude bound, rejecting all infinities/NaNs. -/
@[inline] def small (x : Binary32) : Bool :=
  R2W01b.magnitude x.raw.1 < (0x16000000 : UInt32)

theorem small_exp (x : Binary32) (h : small x = true) :
    (expField x.raw.1).toNat ≤ 43 := by
  unfold small at h
  simp only [decide_eq_true_eq, UInt32.lt_iff_toNat_lt, R2W01b.magnitude_toNat] at h
  have hw := x.raw.1.toNat_lt
  rw [FastMul.expField_toNat]
  change x.raw.1.toNat / 8388608 % 256 ≤ 43
  change x.raw.1.toNat % 2147483648 < 369098752 at h
  omega

theorem small_posZero : small posZero = true := by decide

theorem small_getD (a : Array Binary32) (ha : a.all small = true) (i : Nat) :
    small (a.getD i posZero) = true := by
  by_cases hi : i < a.size
  · simpa [Array.getD, hi] using (Array.all_eq_true.mp ha) i hi
  · simp [Array.getD, hi, small_posZero]

/- The following scale interpretation proof is ported from FloatLib Team, MIT,
   FiniteProof.lean (captured public R6-W01 source). The dependency is unchanged. -/
theorem finiteScale_toNat (exponent : UInt32) :
    (finiteScale exponent).toNat =
      if exponent = 0 then 0 else exponent.toNat - 1 := by
  by_cases hexponent : exponent = 0
  · subst exponent
    simp [finiteScale, FloatLib.Numerics.FixedWord.finiteScale]
  · have hwidened : exponent.toUInt64 ≠ 0 := by
      intro hzero
      apply hexponent
      apply UInt32.toNat_inj.mp
      have := congrArg UInt64.toNat hzero
      simpa using this
    rw [finiteScale, FloatLib.Numerics.FixedWord.finiteScale_toNat]
    simp [hexponent, hwidened]

theorem scale_small (e : UInt32) (he : e.toNat ≤ 43) :
    (finiteScale e).toNat ≤ 42 := by
  rw [finiteScale_toNat]
  split <;> omega

theorem scale_sum_small (x y : Binary32) (hx : small x = true) (hy : small y = true) :
    (finiteScale (expField x.raw.1) + finiteScale (expField y.raw.1)).toNat ≤ 84 := by
  have hsx := scale_small _ (small_exp x hx)
  have hsy := scale_small _ (small_exp y hy)
  rw [UInt64.toNat_add]
  change ((finiteScale (expField x.raw.1)).toNat +
    (finiteScale (expField y.raw.1)).toNat) % 18446744073709551616 ≤ 84
  rw [Nat.mod_eq_of_lt (by omega)]
  omega

/-- A shift of at least65 returns zero even for an arbitrary 64-bit product. -/
theorem rseAny_zero (product scale : UInt64) (hs : scale.toNat ≤ 84) :
    FastMul.rseAny product (149 - scale) = 0 := by
  have hscale : scale ≤ (149 : UInt64) := by
    rw [UInt64.le_iff_toNat_le]
    change scale.toNat ≤ 149
    omega
  have ht : (149 - scale).toNat = 149 - scale.toNat := by
    rw [UInt64.toNat_sub_of_le _ _ hscale]
    rfl
  have h0 : (149 - scale : UInt64) ≠ 0 := by
    intro h
    have hh := congrArg UInt64.toNat h
    rw [ht] at hh
    change 149 - scale.toNat = 0 at hh
    omega
  have h64 : ¬ (149 - scale : UInt64) < 64 := by
    rw [UInt64.lt_iff_toNat_lt, ht]
    change ¬ 149 - scale.toNat < 64
    omega
  have he64 : (149 - scale : UInt64) ≠ 64 := by
    intro h
    have hh := congrArg UInt64.toNat h
    rw [ht] at hh
    change 149 - scale.toNat = 64 at hh
    omega
  simp [FastMul.rseAny, h0, h64, he64]

/-- No mantissa bound is needed: even a full UInt64 rounds to zero here. -/
theorem roundP_zero (sign : Bool) (product scale : UInt64) (hs : scale.toNat ≤ 84) :
    FastMul.roundP sign product scale = (if sign then 0x80000000 else 0) := by
  have hl : (FastMul.fastLog2 product).toNat < 64 := by
    rw [FastMul.fastLog2_eq]
    exact FastMul.log2_lt_64 product
  have hposition : FastMul.fastLog2 product + scale < (172 : UInt64) := by
    rw [UInt64.lt_iff_toNat_lt, UInt64.toNat_add]
    change ((FastMul.fastLog2 product).toNat + scale.toNat) %
      18446744073709551616 < 172
    rw [Nat.mod_eq_of_lt (by omega)]
    omega
  have hscale : scale < (149 : UInt64) := by
    rw [UInt64.lt_iff_toNat_lt]
    change scale.toNat < 149
    omega
  have hf := rseAny_zero product scale hs
  simp [FastMul.roundP, hposition, hscale, hf]

theorem mul_signed_zero (x y : Binary32) (hx : small x = true) (hy : small y = true) :
    ExecFloat.mul x y = FastMul.ofBits
      (if Bool.xor (signBit x.raw.1) (signBit y.raw.1) then 0x80000000 else 0) := by
  have hxe : expField x.raw.1 ≠ 0xff := by
    intro h
    have hs := small_exp x hx
    have hh := congrArg UInt32.toNat h
    change (expField x.raw.1).toNat = 255 at hh
    omega
  have hye : expField y.raw.1 ≠ 0xff := by
    intro h
    have hs := small_exp y hy
    have hh := congrArg UInt32.toNat h
    change (expField y.raw.1).toNat = 255 at hh
    omega
  have hspecial : FastMul.special x.raw.1 y.raw.1 = false := by
    simp [FastMul.special, FastMul.sm1_eq, hxe, hye]
  have heq : ExecFloat.mul x y = FastMul.mul x y :=
    (ExecFloat.Proof.mul_eq_spec x y).trans (FastMul.mul_spec x y).symm
  rw [heq]
  simp only [FastMul.mul, hspecial, Bool.false_eq_true, ite_false, FastMul.core]
  congr 1
  exact roundP_zero _ _ _ (scale_sum_small x y hx hy)

theorem add_signed_zero (sign : Bool) :
    ExecFloat.add posZero (FastMul.ofBits (if sign then 0x80000000 else 0)) = posZero := by
  cases sign <;> decide

theorem add_mul_zero (x y : Binary32) (hx : small x = true) (hy : small y = true) :
    ExecFloat.add posZero (ExecFloat.mul x y) = posZero := by
  rw [mul_signed_zero x y hx hy]
  exact add_signed_zero _

theorem foldl_loop_zero (n : Nat) (step : Binary32 → Fin n → Binary32)
    (hstep : ∀ i, step posZero i = posZero) (k : Nat) :
    Fin.foldl.loop n step posZero k = posZero := by
  rw [Fin.foldl.loop]
  split
  · rename_i hk
    rw [hstep ⟨k, hk⟩]
    exact foldl_loop_zero n step hstep (k + 1)
  · rfl
termination_by n - k

theorem foldl_zero (n : Nat) (step : Binary32 → Fin n → Binary32)
    (hstep : ∀ i, step posZero i = posZero) :
    Fin.foldl n step posZero = posZero :=
  foldl_loop_zero n step hstep 0

def zeros (batch m p : Nat) : Vector Binary32 (batch * m * p) :=
  Vector.replicate (batch * m * p) posZero

theorem zeros_eq_reference (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n)) (B : Vector Binary32 (batch * n * p))
    (ha : A.toArray.all small = true) (hb : B.toArray.all small = true) :
    zeros batch m p = referenceBmm batch m n p A B := by
  apply Vector.ext
  intro q hq
  simp only [zeros, Vector.getElem_replicate, referenceBmm, Vector.getElem_ofFn,
    Submission.add_eq, Submission.mul_eq]
  symm
  apply foldl_zero
  intro k
  exact add_mul_zero _ _ (small_getD A.toArray ha _) (small_getD B.toArray hb _)

end Submission.UnderflowZero

namespace Submission
open FloatLib.Floats Competition

/-- Both short-circuiting scans and the zero fill are inside the timed entry. -/
def bmm (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Vector Binary32 (batch * m * p) :=
  if A.toArray.all UnderflowZero.small && B.toArray.all UnderflowZero.small then
    UnderflowZero.zeros batch m p
  else bmmBeforeUnderflowZero batch m n p A B

theorem bmm_spec : ∀ (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)),
    (bmm batch m n p A B).get = bmmSpec batch m n p A.get B.get := by
  intro batch m n p A B
  unfold bmm
  split
  · rename_i h
    have hh := Bool.and_eq_true.mp h
    rw [UnderflowZero.zeros_eq_reference batch m n p A B hh.1 hh.2]
    exact referenceBmm_spec batch m n p A B
  · exact bmmBeforeUnderflowZero_spec batch m n p A B

end Submission
