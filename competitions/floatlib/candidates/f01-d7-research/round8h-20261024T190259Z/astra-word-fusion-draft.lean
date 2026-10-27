
/- Draft dependency: the complete R14 integer-table mathematical bundle.
All Nat/model work below is proof-only; this runtime uses UInt32 guards and packing. -/
namespace Submission.R14WordFusion

open FloatLib.Floats Competition
open FloatLib.Floats.Formats.BinaryInterchange

@[inline] def ex (u : UInt32) : UInt32 := Model.NativeBinary32.expField u

theorem ex_nat (u : UInt32) : (ex u).toNat = R2W01c.wordExp u := by
  rw [ex, Model.NativeBinary32.expField, UInt32.toNat_and, UInt32.toNat_shiftRight]
  change (u.toNat >>> 23) &&& (2 ^ 8 - 1) = u.toNat / 8388608 % 256
  rw [Nat.and_two_pow_sub_one_eq_mod, Nat.shiftRight_eq_div_pow]

theorem ex_bound (u : UInt32) : (ex u).toNat < 256 := by
  rw [ex_nat]
  exact Nat.mod_lt _ (by decide)

theorem sum_nat (u v : UInt32) :
    (ex u + ex v).toNat = R2W01c.wordExp u + R2W01c.wordExp v := by
  have hu := ex_bound u
  have hv := ex_bound v
  rw [UInt32.toNat_add, Nat.mod_eq_of_lt (by omega), ex_nat, ex_nat]

@[inline] def sign (u v : UInt32) : Bool :=
  Bool.xor (decide ((2147483648 : UInt32) ≤ u))
    (decide ((2147483648 : UInt32) ≤ v))

theorem sign_eq (u v : UInt32) :
    sign u v = Bool.xor (R2W01c.wordSign u) (R2W01c.wordSign v) := by
  simp only [sign, R2W01c.wordSign, UInt32.le_iff_toNat_le]
  rfl

@[inline] def eligible (u v : UInt32) : Bool :=
  (decide (ex u - 1 ≤ 253) && decide (ex v - 1 ≤ 253)) &&
    decide (ex u + ex v - 174 ≤ 206)

theorem eligible_valid (u v : UInt32) (h : eligible u v = true) :
    R14IntegerTable.valid u v := by
  simp only [eligible, Bool.and_eq_true, decide_eq_true_eq] at h
  rcases h with ⟨⟨hu, hv⟩, hs⟩
  have hub := ex_bound u
  have hvb := ex_bound v
  have heSum := sum_nat u v
  rw [UInt32.le_iff_toNat_le, UInt32.toNat_sub] at hu hv hs
  change (4294967295 + (ex u).toNat) % 4294967296 ≤ 253 at hu
  change (4294967295 + (ex v).toNat) % 4294967296 ≤ 253 at hv
  change (4294967122 + (ex u + ex v).toNat) % 4294967296 ≤ 206 at hs
  rw [ex_nat] at hu hv hub hvb
  rw [heSum] at hs
  unfold R14IntegerTable.valid
  omega

@[inline] def makeWord (s : Bool) (e : UInt32) : UInt32 :=
  (if s then 2147483648 else 0) ||| (e <<< 23)

theorem makeWord_eq (s : Bool) (e : UInt32) (he : e.toNat < 256) :
    makeWord s e = Model.NativeBinary32.mkBits s e.toNat 0 := by
  have hm : e &&& 255 = e := by
    apply UInt32.toNat_inj.mp
    rw [UInt32.toNat_and]
    change e.toNat &&& (2 ^ 8 - 1) = e.toNat
    rw [Nat.and_two_pow_sub_one_eq_mod, Nat.mod_eq_of_lt he]
  simp [makeWord, Model.NativeBinary32.mkBits, hm]

@[inline] def core (u v : UInt32) : Float32 :=
  ((R2W01b.mantissa u).toFloat32 * (R2W01b.mantissa v).toFloat32) *
    R2W01b.scaleAt (makeWord (sign u v) (ex u + ex v - 150))

theorem core_eq (u v : UInt32) (h : eligible u v = true) :
    core u v = R14IntegerTable.core u v := by
  have hv := eligible_valid u v h
  rcases hv with ⟨hu0, hu, hv0, hv, hs, hs'⟩
  have heSum := sum_nat u v
  have hle : (150 : UInt32) ≤ ex u + ex v := by
    rw [UInt32.le_iff_toNat_le, heSum]
    change 150 ≤ R2W01c.wordExp u + R2W01c.wordExp v
    omega
  have hsub : (ex u + ex v - 150).toNat =
      R2W01c.wordExp u + R2W01c.wordExp v - 150 := by
    rw [UInt32.toNat_sub_of_le _ _ hle, heSum]
    rfl
  have he : (ex u + ex v - 150).toNat < 256 := by rw [hsub]; omega
  unfold core R14IntegerTable.core
  rw [makeWord_eq _ _ he, hsub, sign_eq]

/-- Fast total prototype; the fallback remains explicit for independent integration. -/
@[inline] def guardedMul (fallback : Binary32 → Binary32 → Binary32)
    (x y : Binary32) : Binary32 :=
  if eligible x.raw.1 y.raw.1 then ExecFloat.Binary.ofFloat32 (core x.raw.1 y.raw.1)
  else fallback x y

theorem guardedMul_spec (fallback : Binary32 → Binary32 → Binary32)
    (hf : ∀ x y, fallback x y = ExecFloat.Spec.mul x y) (x y : Binary32) :
    guardedMul fallback x y = ExecFloat.Spec.mul x y := by
  unfold guardedMul
  split
  · rename_i h
    have hv := eligible_valid x.raw.1 y.raw.1 h
    rcases hv with ⟨hx0, hx, hy0, hy, hs, hs'⟩
    rw [core_eq x.raw.1 y.raw.1 h]
    exact R14IntegerTable.core_spec x y hx0 hx hy0 hy hs hs'
  · exact hf x y

end Submission.R14WordFusion
