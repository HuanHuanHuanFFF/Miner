/- R16 single high-N ADD entry, NOT_COMPILED. Exact N<2^23 and zero use fallback.
   Opposite equal-exponent inputs are rejected before unsigned subtraction:
   every such exact magnitude is below2^23. This is the single high-N domain. -/
namespace Submission.R16AddWord
open FloatLib.Floats Competition
open FloatLib.Floats.Formats.BinaryInterchange
open FloatLib.Numerics

theorem native_high_fields (n : UInt32) (hn : 8388608 ≤ n.toNat) :
    (Model.NativeBinary32.expField n.toFloat32.toBits).toNat =
      n.toNat.log2 + R14NatNormal.carry n.toNat + 127 ∧
    (Model.NativeBinary32.fracField n.toFloat32.toBits).toNat =
      R14NatNormal.mantissa n.toNat - 8388608 ∧
    150 ≤ n.toNat.log2 + R14NatNormal.carry n.toNat + 127 ∧
    n.toNat.log2 + R14NatNormal.carry n.toNat + 127 ≤ 159 := by
  have hn0 : n.toNat ≠ 0 := by omega
  have hl : 23 ≤ n.toNat.log2 := (Nat.le_log2 hn0).2 (by norm_num; exact hn)
  have hb := n.toNat_lt_size
  have hu : n.toNat.log2 < 32 := (Nat.log2_lt hn0).2 hb
  have hc := R14NatNormal.carry_le n.toNat
  have hr := R14WordAddRounding.rounded_bounds n.toNat hn0 hl
  have hf : R14NatNormal.mantissa n.toNat - 8388608 < 8388608 := by
    by_cases h : R14NatNormal.rounded n.toNat = 16777216
    · simp [R14NatNormal.mantissa, h]
    · simp only [R14NatNormal.mantissa, h, ↓reduceIte]
      omega
  have hs := R14NatNormal.native_round_normal false n.toNat 0 hn0 hl (by omega) (by omega)
  have he : Int.toNat ((n.toNat.log2 : Int) + 0 + (R14NatNormal.carry n.toNat : Int) + 127) =
      n.toNat.log2 + R14NatNormal.carry n.toNat + 127 := by omega
  rw [he] at hs
  have hp := R16AddUInt32Interface.uint32_native_fields_of_shape n _ _ (by omega) hf hs
  exact ⟨hp.1, hp.2, by omega, by omega⟩

@[inline] def middleWord (u v : UInt32) : UInt32 := (magnitudeWord u v).toFloat32.toBits
@[inline] def resultExponent (u v : UInt32) : UInt32 :=
  R14ExponentShift.ex (middleWord u v) + R14ExponentShift.ex (low u v) - (150 : UInt32)
@[inline] def resultSign (u v : UInt32) : Bool := decide ((2147483648 : UInt32) ≤ high u v)
@[inline] def nativeCore (u v : UInt32) : UInt32 :=
  let mid := middleWord u v
  FastMul.mkW (resultSign u v)
    (R14ExponentShift.ex mid + R14ExponentShift.ex (low u v) - (150 : UInt32))
    (Model.NativeBinary32.fracField mid)

theorem resultSign_eq (u v : UInt32) : resultSign u v = R2W01c.wordSign (high u v) := by
  simp only [resultSign, R2W01c.wordSign, UInt32.le_iff_toNat_le]
  rfl

theorem result_fields (u v : UInt32) (hd : eligible u v = true)
    (hn : (8388608 : UInt32) ≤ magnitudeWord u v) :
    (resultExponent u v).toNat =
      (magnitudeNat u v).log2 + R14NatNormal.carry (magnitudeNat u v) +
        R2W01c.wordExp (low u v) - 23 ∧
    1 ≤ (resultExponent u v).toNat ∧
    (Model.NativeBinary32.fracField (middleWord u v)).toNat =
      R14NatNormal.mantissa (magnitudeNat u v) - 8388608 := by
  have hn' : 8388608 ≤ (magnitudeWord u v).toNat := UInt32.le_iff_toNat_le.mp hn
  have hp := native_high_fields (magnitudeWord u v) hn'
  rw [magnitudeWord_nat u v hd] at hp
  have hd' := sorted_domain u v hd
  have ha0 := hd'.2.1.1
  have ha1 := hd'.2.1.2
  have hm : (R14ExponentShift.ex (middleWord u v)).toNat =
      (magnitudeNat u v).log2 + R14NatNormal.carry (magnitudeNat u v) + 127 := hp.1
  have hadd : (R14ExponentShift.ex (middleWord u v) + R14ExponentShift.ex (low u v)).toNat =
      (magnitudeNat u v).log2 + R14NatNormal.carry (magnitudeNat u v) + 127 +
        R2W01c.wordExp (low u v) := by
    rw [UInt32.toNat_add, hm, R14ExponentShift.ex_nat]
    exact Nat.mod_eq_of_lt (by omega)
  have hle : (150 : UInt32) ≤ R14ExponentShift.ex (middleWord u v) + R14ExponentShift.ex (low u v) := by
    rw [UInt32.le_iff_toNat_le, hadd]
    change 150 ≤ _
    omega
  have he : (resultExponent u v).toNat =
      (magnitudeNat u v).log2 + R14NatNormal.carry (magnitudeNat u v) +
        R2W01c.wordExp (low u v) - 23 := by
    rw [resultExponent, UInt32.toNat_sub_of_le _ _ hle, hadd]
    change _ - 150 = _
    omega
  exact ⟨he, by rw [he]; omega, hp.2.1⟩

theorem nativeCore_word (u v : UInt32) (hd : eligible u v = true)
    (hn : (8388608 : UInt32) ≤ magnitudeWord u v) :
    nativeCore u v = Model.NativeBinary32.mkBits (R2W01c.wordSign (high u v))
      ((magnitudeNat u v).log2 + R14NatNormal.carry (magnitudeNat u v) + R2W01c.wordExp (low u v) - 23)
      (R14NatNormal.mantissa (magnitudeNat u v) - 8388608) := by
  have h := result_fields u v hd hn
  change FastMul.mkW (resultSign u v) (resultExponent u v)
    (Model.NativeBinary32.fracField (middleWord u v)) = _
  calc
    _ = FastMul.mkW (resultSign u v) (UInt32.ofNat (resultExponent u v).toNat)
        (UInt32.ofNat (Model.NativeBinary32.fracField (middleWord u v)).toNat) := by
          rw [UInt32.ofNat_toNat, UInt32.ofNat_toNat]
    _ = _ := by rw [FastMul.mkW_ofNat, resultSign_eq, h.1, h.2.2]

theorem nativeCore_model (u v : UInt32) (hd : eligible u v = true)
    (hn : (8388608 : UInt32) ≤ magnitudeWord u v)
    (he : resultExponent u v - 1 ≤ (253 : UInt32)) :
    Model.NativeBinary32.ofUInt32 (nativeCore u v) =
      Model.add (R2W01c.rawModel u) (R2W01c.rawModel v) := by
  have hf := result_fields u v hd hn
  have hN : 8388608 ≤ magnitudeNat u v := by
    have h := UInt32.le_iff_toNat_le.mp hn
    simpa only [magnitudeWord_nat u v hd] using h
  have hN0 : magnitudeNat u v ≠ 0 := by omega
  have hl : 23 ≤ (magnitudeNat u v).log2 := (Nat.le_log2 hN0).2 (by norm_num; exact hN)
  have ha := (sorted_domain u v hd).2.1.1
  have hc := R14NatNormal.carry_le (magnitudeNat u v)
  have hle : (1 : UInt32) ≤ resultExponent u v := UInt32.le_iff_toNat_le.mpr hf.2.1
  have hup : (resultExponent u v).toNat ≤ 254 := by
    rw [UInt32.le_iff_toNat_le, UInt32.toNat_sub_of_le _ _ hle] at he
    change (resultExponent u v).toNat - 1 ≤ 253 at he
    omega
  rw [hf.1] at hup
  have hmin : -126 ≤ ((magnitudeNat u v).log2 : Int) + ((R2W01c.wordExp (low u v) : Int) - 150) := by omega
  have hmax : ((magnitudeNat u v).log2 : Int) + ((R2W01c.wordExp (low u v) : Int) - 150) +
      (R14NatNormal.carry (magnitudeNat u v) : Int) ≤ 127 := by omega
  have hexp : Int.toNat (((magnitudeNat u v).log2 : Int) + ((R2W01c.wordExp (low u v) : Int) - 150) +
      (R14NatNormal.carry (magnitudeNat u v) : Int) + 127) =
      (magnitudeNat u v).log2 + R14NatNormal.carry (magnitudeNat u v) + R2W01c.wordExp (low u v) - 23 := by omega
  rw [nativeCore_word u v hd hn, Model.NativeBinary32.ofUInt32_mkBits,
    raw_add_dyadic u v hd, R14NatNormal.model_round_normal _ _ _ hN0 hl hmin hmax, hexp]

theorem nativeCore_spec (x y : Binary32) (hd : eligible x.raw.1 y.raw.1 = true)
    (hn : (8388608 : UInt32) ≤ magnitudeWord x.raw.1 y.raw.1)
    (he : resultExponent x.raw.1 y.raw.1 - 1 ≤ (253 : UInt32)) :
    R7W02.fromRaw (nativeCore x.raw.1 y.raw.1) = ExecFloat.Spec.add x y := by
  apply Configured.Family.toModel_injective
  change ExecFloat.Binary.toModel (R7W02.fromRaw (nativeCore x.raw.1 y.raw.1)) = ExecFloat.Binary.toModel (ExecFloat.Spec.add x y)
  rw [R7W02.fromRaw_toModel, ← ExecFloat.Proof.add_eq_spec x y,
    R7Native.toModelExecAdd, ← Model.Proof.add_eq_spec,
    R7W02.exec_toModel_eq_rawModel x, R7W02.exec_toModel_eq_rawModel y,
    ← R2W01c.rawModel_eq_native32 x.raw.1, ← R2W01c.rawModel_eq_native32 y.raw.1]
  exact nativeCore_model x.raw.1 y.raw.1 hd hn he

@[inline] def guardedAdd (fallback : Binary32 → Binary32 → Binary32) (x y : Binary32) : Binary32 :=
  let u := x.raw.1
  let v := y.raw.1
  if eligible u v then
    let n := magnitudeWord u v
    if (8388608 : UInt32) ≤ n then
      let mid := n.toFloat32.toBits
      let e := R14ExponentShift.ex mid + R14ExponentShift.ex (low u v) - (150 : UInt32)
      if e - 1 ≤ (253 : UInt32) then
        R7W02.fromRaw (FastMul.mkW (resultSign u v) e (Model.NativeBinary32.fracField mid))
      else fallback x y
    else fallback x y
  else fallback x y

theorem guardedAdd_spec (fallback : Binary32 → Binary32 → Binary32)
    (hf : ∀ x y, fallback x y = ExecFloat.Spec.add x y) (x y : Binary32) :
    guardedAdd fallback x y = ExecFloat.Spec.add x y := by
  unfold guardedAdd
  dsimp only
  split
  · rename_i hd
    dsimp only
    split
    · rename_i hn
      dsimp only
      split
      · rename_i he
        exact nativeCore_spec x y hd hn he
      · exact hf x y
    · exact hf x y
  · exact hf x y
end Submission.R16AddWord
