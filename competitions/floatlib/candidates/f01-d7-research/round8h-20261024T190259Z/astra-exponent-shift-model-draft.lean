
/- Dependencies: model_mul_of_nonzero_decodes; nat-normal-form; exponent-shift-algebra. -/
namespace Submission.R14ExponentShift

open FloatLib.Floats Competition
open FloatLib.Floats.Formats.BinaryInterchange

def product (mx my : UInt32) : Nat := mx.toNat * my.toNat
def middleExponent (p : Nat) : Nat := p.log2 + R14NatNormal.carry p + 127
def storedFraction (p : Nat) : Nat := R14NatNormal.mantissa p - 8388608

theorem product_bounds (mx my : UInt32)
    (hx0 : 8388608 ≤ mx.toNat) (hx : mx.toNat < 16777216)
    (hy0 : 8388608 ≤ my.toNat) (hy : my.toNat < 16777216) :
    70368744177664 ≤ product mx my ∧ product mx my ≤ 281474943156225 := by
  have hl := Nat.mul_le_mul hx0 hy0
  have hh := Nat.mul_le_mul (show mx.toNat ≤ 16777215 by omega)
    (show my.toNat ≤ 16777215 by omega)
  norm_num at hl hh
  exact ⟨hl, hh⟩

theorem middle_bounds (p : Nat)
    (hp0 : 70368744177664 ≤ p) (hp : p ≤ 281474943156225) :
    173 ≤ middleExponent p ∧ middleExponent p ≤ 174 ∧ storedFraction p < 8388608 := by
  have hh : p < 281474976710656 := by omega
  have hl := R14NatNormal.leading_bounds p hp0 hh
  have hc := R14NatNormal.carry_le p
  have hm := R14NatNormal.mantissa_bounds p hp0 hh
  have hcases : p.log2 = 46 ∨ p.log2 = 47 := by omega
  unfold middleExponent storedFraction
  rcases hcases with h46 | h47
  · rw [h46]
    omega
  · have hc0 := R14NatNormal.no_carry_at_47 p hp h47
    rw [h47, hc0]
    omega

/-- The only floating arithmetic performed by the fast runtime is this actual native product.
Its toBits is identified through the existing finite native-model bridge. -/
theorem first_product_bits (mx my : UInt32)
    (hx0 : 8388608 ≤ mx.toNat) (hx : mx.toNat < 16777216)
    (hy0 : 8388608 ≤ my.toNat) (hy : my.toNat < 16777216) :
    (mx.toFloat32 * my.toFloat32).toBits =
      Model.NativeBinary32.mkBits false
        (middleExponent (product mx my)) (storedFraction (product mx my)) := by
  let p := product mx my
  have hp := product_bounds mx my hx0 hx hy0 hy
  have hpHi : p < 281474976710656 := by change product mx my < _; omega
  have hlead := R14NatNormal.leading_bounds p hp.1 hpHi
  have hcarry := R14NatNormal.carry_le p
  have hfirstLo : -126 ≤ (p.log2 : Int) + 0 := by omega
  have hfirstHi : (p.log2 : Int) + 0 + (R14NatNormal.carry p : Int) ≤ 127 := by omega
  have hmx := R2W01c.uint32_mantissa_model_decode mx hx0 hx
  have hmy := R2W01c.uint32_mantissa_model_decode my hy0 hy
  apply R2W01c.native_mul_bits_eq_of_raw_model_mul_eq
  · exact R2W01c.nativeFinite_of_decode mx.toFloat32 hmx
  · exact R2W01c.nativeFinite_of_decode my.toFloat32 hmy
  · have hm := R14NativeProduct.model_mul_of_nonzero_decodes
      (R2W01c.nativeModel mx.toFloat32) (R2W01c.nativeModel my.toFloat32)
      ⟨false, mx.toNat, 0⟩ ⟨false, my.toNat, 0⟩ hmx hmy (by omega) (by omega)
    have he : Int.toNat ((p.log2 : Int) + 0 + (R14NatNormal.carry p : Int) + 127) =
        middleExponent p := by unfold middleExponent; omega
    calc
      Model.mul (R2W01c.nativeModel mx.toFloat32) (R2W01c.nativeModel my.toFloat32) =
          Model.roundDyadic FloatFormat.binary32 ⟨false, p, 0⟩ := by
            simpa [p, product] using hm
      _ = Model.ofFields FloatFormat.binary32 false (middleExponent p) (storedFraction p) := by
          rw [R14NatNormal.model_round_normal false p 0 (by omega) (by omega)
            hfirstLo hfirstHi, he]
      _ = R2W01c.rawModel (Model.NativeBinary32.mkBits false
          (middleExponent p) (storedFraction p)) := by
          rw [R2W01c.rawModel_eq_native32, Model.NativeBinary32.ofUInt32_mkBits]

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
  Bool.xor (decide ((2147483648 : UInt32) ≤ u)) (decide ((2147483648 : UInt32) ≤ v))

theorem sign_eq (u v : UInt32) :
    sign u v = Bool.xor (R2W01c.wordSign u) (R2W01c.wordSign v) := by
  simp only [sign, R2W01c.wordSign, UInt32.le_iff_toNat_le]
  rfl

@[inline] def core (u v : UInt32) : UInt32 :=
  let mid := ((R2W01b.mantissa u).toFloat32 * (R2W01b.mantissa v).toFloat32).toBits
  (if sign u v then 2147483648 else 0) ||| (mid + ((ex u + ex v - 300) <<< 23))

theorem core_word (u v : UInt32)
    (hs : 128 ≤ R2W01c.wordExp u + R2W01c.wordExp v)
    (hs' : R2W01c.wordExp u + R2W01c.wordExp v ≤ 380) :
    core u v = Model.NativeBinary32.mkBits
      (Bool.xor (R2W01c.wordSign u) (R2W01c.wordSign v))
      (middleExponent (product (R2W01b.mantissa u) (R2W01b.mantissa v)) +
        R2W01c.wordExp u + R2W01c.wordExp v - 300)
      (storedFraction (product (R2W01b.mantissa u) (R2W01b.mantissa v))) := by
  have hx := R2W01c.mantissa_bounds u
  have hy := R2W01c.mantissa_bounds v
  have hp := product_bounds _ _ hx.1 hx.2 hy.1 hy.2
  have hb := middle_bounds _ hp.1 hp.2
  unfold core
  rw [first_product_bits _ _ hx.1 hx.2 hy.1 hy.2, sign_eq]
  have h := R14ExponentAlgebra.shifted_word
    (Bool.xor (R2W01c.wordSign u) (R2W01c.wordSign v))
    (middleExponent (product (R2W01b.mantissa u) (R2W01b.mantissa v)))
    (storedFraction (product (R2W01b.mantissa u) (R2W01b.mantissa v)))
    (ex u + ex v) hb.1 hb.2.1 hb.2.2 (by rw [sum_nat]; exact hs) (by rw [sum_nat]; exact hs')
  simpa only [sum_nat, Nat.add_assoc] using h

theorem core_model (u v : UInt32)
    (hu0 : 0 < R2W01c.wordExp u) (hu : R2W01c.wordExp u < 255)
    (hv0 : 0 < R2W01c.wordExp v) (hv : R2W01c.wordExp v < 255)
    (hs : 128 ≤ R2W01c.wordExp u + R2W01c.wordExp v)
    (hs' : R2W01c.wordExp u + R2W01c.wordExp v ≤ 380) :
    Model.NativeBinary32.ofUInt32 (core u v) =
      Model.mul (R2W01c.rawModel u) (R2W01c.rawModel v) := by
  let p := product (R2W01b.mantissa u) (R2W01b.mantissa v)
  let s := R2W01c.wordExp u + R2W01c.wordExp v
  have hmx := R2W01c.mantissa_bounds u
  have hmy := R2W01c.mantissa_bounds v
  have hp := product_bounds _ _ hmx.1 hmx.2 hmy.1 hmy.2
  have hpHi : p < 281474976710656 := by change product _ _ < _; omega
  have hl := R14NatNormal.leading_bounds p hp.1 hpHi
  have hc := R14NatNormal.carry_le p
  have hmid := middle_bounds p hp.1 hp.2
  have hmin : -126 ≤ (p.log2 : Int) + ((s : Int) - 300) := by dsimp [s]; omega
  have hmax : (p.log2 : Int) + ((s : Int) - 300) + (R14NatNormal.carry p : Int) ≤ 127 := by
    dsimp [middleExponent, s] at hmid ⊢
    omega
  have hx := R14NatNormal.raw_normal_decode u hu0 hu
  have hy := R14NatNormal.raw_normal_decode v hv0 hv
  have hm := R14NativeProduct.model_mul_of_nonzero_decodes
    (R2W01c.rawModel u) (R2W01c.rawModel v)
    ⟨R2W01c.wordSign u, (R2W01b.mantissa u).toNat, (R2W01c.wordExp u : Int) - 150⟩
    ⟨R2W01c.wordSign v, (R2W01b.mantissa v).toNat, (R2W01c.wordExp v : Int) - 150⟩
    hx hy (by omega) (by omega)
  have heOrig : (R2W01c.wordExp u : Int) - 150 +
      ((R2W01c.wordExp v : Int) - 150) = (s : Int) - 300 := by dsimp [s]; omega
  rw [heOrig] at hm
  have heTarget :
      Int.toNat ((p.log2 : Int) + ((s : Int) - 300) + (R14NatNormal.carry p : Int) + 127) =
      middleExponent p + s - 300 := by dsimp [middleExponent, s]; omega
  rw [R14NatNormal.model_round_normal _ p ((s : Int) - 300)
    (by omega) (by omega) hmin hmax, heTarget] at hm
  rw [core_word u v hs hs', Model.NativeBinary32.ofUInt32_mkBits]
  simpa only [s, Nat.add_assoc] using hm.symm

theorem core_spec (x y : Binary32)
    (hx0 : 0 < R2W01c.wordExp x.raw.1) (hx : R2W01c.wordExp x.raw.1 < 255)
    (hy0 : 0 < R2W01c.wordExp y.raw.1) (hy : R2W01c.wordExp y.raw.1 < 255)
    (hs : 128 ≤ R2W01c.wordExp x.raw.1 + R2W01c.wordExp y.raw.1)
    (hs' : R2W01c.wordExp x.raw.1 + R2W01c.wordExp y.raw.1 ≤ 380) :
    R7W02.fromRaw (core x.raw.1 y.raw.1) = ExecFloat.Spec.mul x y := by
  apply Configured.Family.toModel_injective
  change ExecFloat.Binary.toModel (R7W02.fromRaw (core x.raw.1 y.raw.1)) =
    ExecFloat.Binary.toModel (ExecFloat.Spec.mul x y)
  rw [R7W02.fromRaw_toModel, ← ExecFloat.Proof.mul_eq_spec, R7W01.exec_toModel_mul,
    ← Model.Proof.mul_eq_spec, R7W02.exec_toModel_eq_rawModel x,
    R7W02.exec_toModel_eq_rawModel y, ← R2W01c.rawModel_eq_native32 x.raw.1,
    ← R2W01c.rawModel_eq_native32 y.raw.1]
  exact core_model x.raw.1 y.raw.1 hx0 hx hy0 hy hs hs'

@[inline] def eligible (u v : UInt32) : Bool :=
  (decide (ex u - 1 ≤ 253) && decide (ex v - 1 ≤ 253)) &&
    decide (ex u + ex v - 128 ≤ 252)

theorem eligible_conditions (u v : UInt32) (h : eligible u v = true) :
    0 < R2W01c.wordExp u ∧ R2W01c.wordExp u < 255 ∧
    0 < R2W01c.wordExp v ∧ R2W01c.wordExp v < 255 ∧
    128 ≤ R2W01c.wordExp u + R2W01c.wordExp v ∧
    R2W01c.wordExp u + R2W01c.wordExp v ≤ 380 := by
  simp only [eligible, Bool.and_eq_true, decide_eq_true_eq] at h
  rcases h with ⟨⟨hu, hv⟩, hs⟩
  have hub := ex_bound u
  have hvb := ex_bound v
  have heSum := sum_nat u v
  rw [UInt32.le_iff_toNat_le, UInt32.toNat_sub] at hu hv hs
  change (4294967295 + (ex u).toNat) % 4294967296 ≤ 253 at hu
  change (4294967295 + (ex v).toNat) % 4294967296 ≤ 253 at hv
  change (4294967168 + (ex u + ex v).toNat) % 4294967296 ≤ 252 at hs
  rw [ex_nat] at hu hv hub hvb
  rw [heSum] at hs
  omega

@[inline] def guardedMul (fallback : Binary32 → Binary32 → Binary32)
    (x y : Binary32) : Binary32 :=
  if eligible x.raw.1 y.raw.1 then R7W02.fromRaw (core x.raw.1 y.raw.1)
  else fallback x y

theorem guardedMul_spec (fallback : Binary32 → Binary32 → Binary32)
    (hf : ∀ x y, fallback x y = ExecFloat.Spec.mul x y) (x y : Binary32) :
    guardedMul fallback x y = ExecFloat.Spec.mul x y := by
  unfold guardedMul
  split
  · rename_i h
    rcases eligible_conditions x.raw.1 y.raw.1 h with ⟨hx0, hx, hy0, hy, hs, hs'⟩
    exact core_spec x y hx0 hx hy0 hy hs hs'
  · exact hf x y

end Submission.R14ExponentShift
