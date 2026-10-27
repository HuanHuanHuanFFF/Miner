namespace Submission.R19DirectBias
open FloatLib.Floats Competition
open FloatLib.Floats.Formats.BinaryInterchange
open Model.NativeBinary32 R19DirectBiasWord R19BiasShape

theorem low_mask_eq_self (n : UInt32) (k : Nat) (hk : k < 32) (hn : n.toNat < 2^k) :
    n &&& UInt32.ofNat (2^k-1) = n := by
  apply UInt32.toNat.inj
  simp only [UInt32.toNat_and,UInt32.toNat_ofNat']
  have hmask : 2^k-1 < 4294967296 := by
    have hpow : 2^k ≤ 2^31 := Nat.pow_le_pow_right (by decide) (by omega)
    norm_num at hpow
    omega
  rw [Nat.mod_eq_of_lt hmask,Nat.and_two_pow_sub_one_eq_mod,Nat.mod_eq_of_lt hn]

theorem mkW_eq_unmasked (sign : Bool) (e f : UInt32)
    (he : e.toNat < 256) (hf : f.toNat < 8388608) :
    FastMul.mkW sign e f =
      (if sign then (0x80000000 : UInt32) else 0) ||| (e <<< 23) ||| f := by
  have hem := low_mask_eq_self e 8 (by decide) he
  have hfm := low_mask_eq_self f 23 (by decide) hf
  change e &&& (255 : UInt32) = e at hem
  change f &&& (8388607 : UInt32) = f at hfm
  unfold FastMul.mkW
  rw [hem,hfm]

theorem product_bounds (u v : UInt32) :
    let p := (R2W01b.mantissa u).toUInt64 * (R2W01b.mantissa v).toUInt64
    70368744177664 ≤ p.toNat ∧ p.toNat ≤ 281474943156225 := by
  have hu := R2W01c.mantissa_bounds u
  have hv := R2W01c.mantissa_bounds v
  have hl := Nat.mul_le_mul hu.1 hv.1
  have hh := Nat.mul_le_mul (show (R2W01b.mantissa u).toNat ≤ 16777215 by omega)
    (show (R2W01b.mantissa v).toNat ≤ 16777215 by omega)
  norm_num at hl hh
  dsimp only
  rw [UInt64.toNat_mul,UInt32.toNat_toUInt64,UInt32.toNat_toUInt64,
    Nat.mod_eq_of_lt (by omega)]
  exact ⟨hl,hh⟩

theorem normalCore_eq_roundP (s u v : UInt32) (sign : Bool)
    (hs0 : 128 ≤ s.toNat) (hs1 : s.toNat ≤ 380)
    (hsign : ((u ^^^ v) &&& (0x80000000 : UInt32)) =
      (if sign then (0x80000000 : UInt32) else 0)) :
    normalCore s u v = FastMul.roundP sign
      ((R2W01b.mantissa u).toUInt64 * (R2W01b.mantissa v).toUInt64) (s.toUInt64-2) := by
  let p := (R2W01b.mantissa u).toUInt64 * (R2W01b.mantissa v).toUInt64
  have hp := product_bounds u v
  have hb := output_bounds p s hp.1 hp.2 hs0 hs1
  rw [roundP_normal sign p s hp.1 hp.2 hs0 hs1]
  change ((u ^^^ v) &&& (0x80000000 : UInt32)) |||
      (exponentWord s p <<< 23) ||| (mantissaWord p-8388608) =
    FastMul.mkW sign (oldPosition p s-171).toUInt32 (FastMul.fracW (oldMantissa p))
  rw [hsign,← mkW_eq_unmasked sign _ _ hb.1 hb.2,
    exponentWord_eq_old p s hp.1 hp.2 hs0 hs1,fractionWord_eq_old p hp.1 hp.2]

theorem finiteMantissa_eq (u : UInt32) (hu : expField u ≠ 0) :
    finiteMantissa (expField u) (fracField u) = (R2W01b.mantissa u).toUInt64 := by
  apply UInt64.toNat.inj
  simp only [finiteMantissa,beq_iff_eq,hu,if_false,UInt64.toNat_or,
    UInt32.toNat_toUInt64]
  rw [R2W01b.mantissa,UInt32.toNat_or]
  rfl

theorem exp_bound (u : UInt32) : (expField u).toNat < 256 := by
  rw [FastMul.expField_toNat]
  exact Nat.mod_lt _ (by decide)

theorem finiteScale_sum (u v : UInt32)
    (hu : 0 < (expField u).toNat) (hv : 0 < (expField v).toNat)
    (hs : 128 ≤ (expField u+expField v).toNat) :
    finiteScale (expField u)+finiteScale (expField v) =
      (expField u+expField v).toUInt64-2 := by
  have hub := exp_bound u
  have hvb := exp_bound v
  have hu0 : expField u ≠ 0 := by intro h; rw [h] at hu; norm_num at hu
  have hv0 : expField v ≠ 0 := by intro h; rw [h] at hv; norm_num at hv
  have hsum : (expField u+expField v).toNat = (expField u).toNat+(expField v).toNat := by
    rw [UInt32.toNat_add,Nat.mod_eq_of_lt (by omega)]
  apply UInt64.toNat.inj
  rw [normal_scale_nat _ hs,UInt64.toNat_add,UnderflowZero.finiteScale_toNat,
    UnderflowZero.finiteScale_toNat,if_neg hu0,if_neg hv0,hsum]
  rw [Nat.mod_eq_of_lt (by omega)]
  omega

theorem signBit_eq_bit (u : UInt32) : signBit u = u.toBitVec.getLsbD 31 := by
  have hm : u &&& (0x80000000 : UInt32) =
      if u.toBitVec.getLsbD 31 then (0x80000000 : UInt32) else 0 := by
    apply UInt32.toBitVec_inj.mp
    rw [UInt32.toBitVec_and]
    change u.toBitVec &&& BitVec.twoPow 32 31 = _
    rw [BitVec.and_twoPow]
    cases u.toBitVec.getLsbD 31 <;> rfl
  unfold signBit
  rw [hm]
  cases u.toBitVec.getLsbD 31 <;> rfl

theorem sign_word_eq (u v : UInt32) :
    ((u ^^^ v) &&& (0x80000000 : UInt32)) =
      (if Bool.xor (signBit u) (signBit v) then (0x80000000 : UInt32) else 0) := by
  apply UInt32.toBitVec_inj.mp
  rw [UInt32.toBitVec_and,UInt32.toBitVec_xor]
  change (u.toBitVec ^^^ v.toBitVec) &&& BitVec.twoPow 32 31 = _
  rw [BitVec.and_twoPow]
  have hm : (u.toBitVec ^^^ v.toBitVec).getLsbD 31 = Bool.xor (signBit u) (signBit v) := by
    calc
      _ = (u.toBitVec ^^^ v.toBitVec).msb := by
        simpa using (BitVec.msb_eq_getLsbD_last (u.toBitVec ^^^ v.toBitVec)).symm
      _ = _ := by
        rw [BitVec.msb_xor,signBit_eq_bit,signBit_eq_bit]
        congr 1 <;> simpa using BitVec.msb_eq_getLsbD_last _
  rw [hm]
  cases Bool.xor (signBit u) (signBit v) <;> rfl

theorem normalCore_eq_core (u v : UInt32)
    (hu : 0 < (expField u).toNat) (hv : 0 < (expField v).toNat)
    (hs0 : 128 ≤ (expField u+expField v).toNat)
    (hs1 : (expField u+expField v).toNat ≤ 380) :
    normalCore (expField u+expField v) u v = FastMul.core u v := by
  have hu0 : expField u ≠ 0 := by intro h; rw [h] at hu; norm_num at hu
  have hv0 : expField v ≠ 0 := by intro h; rw [h] at hv; norm_num at hv
  rw [normalCore_eq_roundP _ u v _ hs0 hs1 (sign_word_eq u v)]
  simp only [FastMul.core]
  rw [finiteMantissa_eq u hu0,finiteMantissa_eq v hv0,finiteScale_sum u v hu hv hs0]

theorem normal_guard (e : UInt32) (h : e-1 ≤ (253 : UInt32)) :
    0 < e.toNat ∧ e.toNat < 255 := by
  have he := e.toNat_lt
  rw [UInt32.le_iff_toNat_le,UInt32.toNat_sub] at h
  change (4294967295+e.toNat) % 4294967296 ≤ 253 at h
  omega

theorem sum_guard (s : UInt32) (h : s-128 ≤ (252 : UInt32)) :
    128 ≤ s.toNat ∧ s.toNat ≤ 380 := by
  have hs := s.toNat_lt
  rw [UInt32.le_iff_toNat_le,UInt32.toNat_sub] at h
  change (4294967168+s.toNat) % 4294967296 ≤ 252 at h
  omega

theorem guardedMul_spec (fallback : Binary32 → Binary32 → Binary32)
    (hf : ∀ x y, fallback x y = ExecFloat.Spec.mul x y) (x y : Binary32) :
    guardedMul fallback x y = ExecFloat.Spec.mul x y := by
  unfold guardedMul
  dsimp only
  split
  · rename_i hn
    have hu := normal_guard _ hn.1
    have hv := normal_guard _ hn.2
    split
    · rename_i hs
      have hb := sum_guard _ hs
      change 0 < (expField x.raw.1).toNat ∧ (expField x.raw.1).toNat < 255 at hu
      change 0 < (expField y.raw.1).toNat ∧ (expField y.raw.1).toNat < 255 at hv
      change 128 ≤ (expField x.raw.1+expField y.raw.1).toNat ∧
        (expField x.raw.1+expField y.raw.1).toNat ≤ 380 at hb
      change R7W02.fromRaw (normalCore (expField x.raw.1+expField y.raw.1) x.raw.1 y.raw.1) = _
      rw [normalCore_eq_core _ _ hu.1 hv.1 hb.1 hb.2]
      have hu255 : expField x.raw.1 ≠ (255 : UInt32) := by
        intro h; rw [h] at hu; norm_num at hu
      have hv255 : expField y.raw.1 ≠ (255 : UInt32) := by
        intro h; rw [h] at hv; norm_num at hv
      have hspecial : FastMul.special x.raw.1 y.raw.1 = false := by
        simp [FastMul.special,FastMul.sm1_eq,hu255,hv255]
      calc
        _ = FastMul.ofBits (FastMul.core x.raw.1 y.raw.1) := by
          apply Configured.Family.toModel_injective
          rfl
        _ = FastMul.mul x y := by simp only [FastMul.mul,hspecial,Bool.false_eq_true,if_false]
        _ = ExecFloat.Spec.mul x y := FastMul.mul_spec x y
    · exact hf x y
  · exact hf x y

end Submission.R19DirectBias
