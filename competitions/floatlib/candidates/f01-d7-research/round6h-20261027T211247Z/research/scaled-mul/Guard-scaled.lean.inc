namespace Submission.R22ScaledGuard
open FloatLib.Floats Competition
open FloatLib.Floats.Formats.BinaryInterchange

@[inline] def ex (u : UInt32) : UInt32 := Model.NativeBinary32.expField u

theorem ex_nat (u : UInt32) : (ex u).toNat = R2W01c.wordExp u := by
  rw [ex,Model.NativeBinary32.expField,UInt32.toNat_and,UInt32.toNat_shiftRight]
  change (u.toNat >>> 23) &&& (2^8-1) = u.toNat / 8388608 % 256
  rw [Nat.and_two_pow_sub_one_eq_mod,Nat.shiftRight_eq_div_pow]

theorem ex_bound (u : UInt32) : (ex u).toNat < 256 := by
  rw [ex_nat]
  exact Nat.mod_lt _ (by decide)

theorem sum_nat (u v : UInt32) :
    (ex u + ex v).toNat = R2W01c.wordExp u + R2W01c.wordExp v := by
  have hu := ex_bound u
  have hv := ex_bound v
  rw [UInt32.toNat_add,Nat.mod_eq_of_lt (by omega),ex_nat,ex_nat]

theorem guard_conditions (u v : UInt32)
    (hnormal : ex u - 1 ≤ 253 ∧ ex v - 1 ≤ 253)
    (hsum : ex u + ex v - 128 ≤ 252) :
    0 < R2W01c.wordExp u ∧ R2W01c.wordExp u < 255 ∧
    0 < R2W01c.wordExp v ∧ R2W01c.wordExp v < 255 ∧
    128 ≤ R2W01c.wordExp u + R2W01c.wordExp v ∧
    R2W01c.wordExp u + R2W01c.wordExp v ≤ 380 := by
  rcases hnormal with ⟨hu,hv⟩
  have hub := ex_bound u
  have hvb := ex_bound v
  have heSum := sum_nat u v
  rw [UInt32.le_iff_toNat_le,UInt32.toNat_sub] at hu hv hsum
  change (4294967295+(ex u).toNat) % 4294967296 ≤ 253 at hu
  change (4294967295+(ex v).toNat) % 4294967296 ≤ 253 at hv
  change (4294967168+(ex u+ex v).toNat) % 4294967296 ≤ 252 at hsum
  rw [ex_nat] at hu hv hub hvb
  rw [heSum] at hsum
  omega

/-- Explicitly conditional: the missing core-to-model bridge remains a premise.
    This only closes original guard/fallback transport, never claims mul_spec. -/
theorem guardedMul_spec_of_core_spec
    (hcore : ∀ (x y : Binary32),
      0 < R2W01c.wordExp x.raw.1 → R2W01c.wordExp x.raw.1 < 255 →
      0 < R2W01c.wordExp y.raw.1 → R2W01c.wordExp y.raw.1 < 255 →
      128 ≤ R2W01c.wordExp x.raw.1+R2W01c.wordExp y.raw.1 →
      R2W01c.wordExp x.raw.1+R2W01c.wordExp y.raw.1 ≤ 380 →
      R7W02.fromRaw (R21ScaledU32.normalCore (ex x.raw.1+ex y.raw.1) x.raw.1 y.raw.1) =
        ExecFloat.Spec.mul x y)
    (fallback : Binary32 → Binary32 → Binary32)
    (hf : ∀ x y, fallback x y = ExecFloat.Spec.mul x y) (x y : Binary32) :
    R21ScaledU32.guardedMul fallback x y = ExecFloat.Spec.mul x y := by
  unfold R21ScaledU32.guardedMul
  try dsimp only
  split
  · rename_i hnormal
    split
    · rename_i hsum
      rcases guard_conditions x.raw.1 y.raw.1 hnormal hsum with
        ⟨hx0,hx,hy0,hy,hs,hs'⟩
      exact hcore x y hx0 hx hy0 hy hs hs'
    · exact hf x y
  · exact hf x y

end Submission.R22ScaledGuard
