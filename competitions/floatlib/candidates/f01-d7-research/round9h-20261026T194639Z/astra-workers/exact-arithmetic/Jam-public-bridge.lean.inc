namespace Submission.R19Jam17
open FloatLib.Floats Competition
open FloatLib.Floats.Formats.BinaryInterchange

theorem fractionWord_nat (a b : UInt32)
    (ha0 : 8388608 ≤ a.toNat) (ha : a.toNat < 16777216)
    (hb0 : 8388608 ≤ b.toNat) (hb : b.toNat < 16777216) :
    (fractionWord a b).toNat = R14ExponentShift.storedFraction (R14ExponentShift.product a b) := by
  have hp := R14ExponentShift.product_bounds a b ha0 ha hb0 hb
  have hm := R14NatNormal.mantissa_bounds _ hp.1 (by omega)
  have hq := mantissaWord_nat a b ha0 ha hb0 hb
  have hle : (8388608 : UInt32) ≤ mantissaWord a b := by
    rw [UInt32.le_iff_toNat_le,hq]
    exact hm.1
  unfold fractionWord
  rw [UInt32.toNat_sub_of_le _ _ hle,hq]
  rfl

theorem exponentWord_nat (sum a b : UInt32)
    (ha0 : 8388608 ≤ a.toNat) (ha : a.toNat < 16777216)
    (hb0 : 8388608 ≤ b.toNat) (hb : b.toNat < 16777216)
    (hs0 : 128 ≤ sum.toNat) (hs : sum.toNat ≤ 380) :
    (exponentWord sum a b).toNat =
      R14ExponentShift.middleExponent (R14ExponentShift.product a b)+sum.toNat-300 := by
  have hp := R14ExponentShift.product_bounds a b ha0 ha hb0 hb
  have he := R14ExponentShift.middle_bounds _ hp.1 hp.2
  have hle : (127 : UInt32) ≤ sum := by rw [UInt32.le_iff_toNat_le]; exact Nat.le_trans (by decide) hs0
  unfold exponentWord
  rw [UInt32.toNat_add,UInt32.toNat_sub_of_le _ _ hle,highWord_nat a b ha0 ha hb0 hb]
  change (sum.toNat-127+(R14ExponentShift.middleExponent (R14ExponentShift.product a b)-173)) %
    4294967296 = _
  rw [Nat.mod_eq_of_lt (by omega)]
  omega

theorem output_fields (sum a b : UInt32)
    (ha0 : 8388608 ≤ a.toNat) (ha : a.toNat < 16777216)
    (hb0 : 8388608 ≤ b.toNat) (hb : b.toNat < 16777216)
    (hs0 : 128 ≤ sum.toNat) (hs : sum.toNat ≤ 380) :
    1 ≤ (exponentWord sum a b).toNat ∧ (exponentWord sum a b).toNat ≤ 254 ∧
      (fractionWord a b).toNat < 8388608 := by
  have hp := R14ExponentShift.product_bounds a b ha0 ha hb0 hb
  have he := R14ExponentShift.middle_bounds _ hp.1 hp.2
  rw [exponentWord_nat sum a b ha0 ha hb0 hb hs0 hs,
    fractionWord_nat a b ha0 ha hb0 hb]
  omega

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

theorem packed_fields (sign : Bool) (sum a b : UInt32)
    (ha0 : 8388608 ≤ a.toNat) (ha : a.toNat < 16777216)
    (hb0 : 8388608 ≤ b.toNat) (hb : b.toNat < 16777216)
    (hs0 : 128 ≤ sum.toNat) (hs : sum.toNat ≤ 380) :
    (if sign then (0x80000000 : UInt32) else 0) |||
        (exponentWord sum a b <<< 23) ||| fractionWord a b =
      Model.NativeBinary32.mkBits sign
        (R14ExponentShift.middleExponent (R14ExponentShift.product a b)+sum.toNat-300)
        (R14ExponentShift.storedFraction (R14ExponentShift.product a b)) := by
  have hbnds := output_fields sum a b ha0 ha hb0 hb hs0 hs
  rw [← mkW_eq_unmasked sign _ _ (by omega) hbnds.2.2]
  calc
    _ = FastMul.mkW sign (UInt32.ofNat (exponentWord sum a b).toNat)
        (UInt32.ofNat (fractionWord a b).toNat) := by rw [UInt32.ofNat_toNat,UInt32.ofNat_toNat]
    _ = Model.NativeBinary32.mkBits sign (exponentWord sum a b).toNat
        (fractionWord a b).toNat := FastMul.mkW_ofNat _ _ _
    _ = _ := by rw [exponentWord_nat sum a b ha0 ha hb0 hb hs0 hs,
      fractionWord_nat a b ha0 ha hb0 hb]

theorem normalCore_eq_fields (sum u v : UInt32) (sign : Bool)
    (hs0 : 128 ≤ sum.toNat) (hs : sum.toNat ≤ 380)
    (hsign : ((u ^^^ v) &&& (0x80000000 : UInt32)) =
      (if sign then (0x80000000 : UInt32) else 0)) :
    normalCore sum u v =
      Model.NativeBinary32.mkBits sign
        (R14ExponentShift.middleExponent
          (R14ExponentShift.product (R2W01b.mantissa u) (R2W01b.mantissa v))+sum.toNat-300)
        (R14ExponentShift.storedFraction
          (R14ExponentShift.product (R2W01b.mantissa u) (R2W01b.mantissa v))) := by
  have ha := R2W01c.mantissa_bounds u
  have hb := R2W01c.mantissa_bounds v
  change ((u ^^^ v) &&& (0x80000000 : UInt32)) |||
      (exponentWord sum (R2W01b.mantissa u) (R2W01b.mantissa v) <<< 23) |||
      fractionWord (R2W01b.mantissa u) (R2W01b.mantissa v) = _
  rw [hsign]
  exact packed_fields sign sum _ _ ha.1 ha.2 hb.1 hb.2 hs0 hs

theorem sign_word_eq (u v : UInt32) :
    ((u ^^^ v) &&& (0x80000000 : UInt32)) =
      (if Bool.xor (R2W01c.wordSign u) (R2W01c.wordSign v) then
        (0x80000000 : UInt32) else 0) := by
  apply UInt32.toBitVec_inj.mp
  rw [UInt32.toBitVec_and,UInt32.toBitVec_xor]
  change (u.toBitVec ^^^ v.toBitVec) &&& BitVec.twoPow 32 31 =
    (if Bool.xor (R2W01c.wordSign u) (R2W01c.wordSign v) then
      (0x80000000 : UInt32) else 0).toBitVec
  rw [BitVec.and_twoPow]
  have hm : (u.toBitVec ^^^ v.toBitVec).getLsbD 31 =
      Bool.xor (R2W01c.wordSign u) (R2W01c.wordSign v) := by
    calc
      _ = (u.toBitVec ^^^ v.toBitVec).msb := by
        simpa using (BitVec.msb_eq_getLsbD_last (u.toBitVec ^^^ v.toBitVec)).symm
      _ = _ := by
        rw [BitVec.msb_xor,BitVec.msb_eq_decide,BitVec.msb_eq_decide]
        rfl
  rw [hm]
  cases hs : Bool.xor (R2W01c.wordSign u) (R2W01c.wordSign v) <;> rfl

def core (u v : UInt32) : UInt32 :=
  normalCore (R14ExponentShift.ex u + R14ExponentShift.ex v) u v

theorem core_word (u v : UInt32)
    (hs : 128 ≤ R2W01c.wordExp u + R2W01c.wordExp v)
    (hs' : R2W01c.wordExp u + R2W01c.wordExp v ≤ 380) :
    core u v = Model.NativeBinary32.mkBits
      (Bool.xor (R2W01c.wordSign u) (R2W01c.wordSign v))
      (R14ExponentShift.middleExponent
          (R14ExponentShift.product (R2W01b.mantissa u) (R2W01b.mantissa v))+
        R2W01c.wordExp u+R2W01c.wordExp v-300)
      (R14ExponentShift.storedFraction
        (R14ExponentShift.product (R2W01b.mantissa u) (R2W01b.mantissa v))) := by
  have h := normalCore_eq_fields
    (R14ExponentShift.ex u+R14ExponentShift.ex v) u v
    (Bool.xor (R2W01c.wordSign u) (R2W01c.wordSign v))
    (by rw [R14ExponentShift.sum_nat]; exact hs)
    (by rw [R14ExponentShift.sum_nat]; exact hs') (sign_word_eq u v)
  rw [R14ExponentShift.sum_nat] at h
  simpa only [core,Nat.add_assoc] using h

theorem core_model (u v : UInt32)
    (hu0 : 0 < R2W01c.wordExp u) (hu : R2W01c.wordExp u < 255)
    (hv0 : 0 < R2W01c.wordExp v) (hv : R2W01c.wordExp v < 255)
    (hs : 128 ≤ R2W01c.wordExp u + R2W01c.wordExp v)
    (hs' : R2W01c.wordExp u + R2W01c.wordExp v ≤ 380) :
    Model.NativeBinary32.ofUInt32 (core u v) =
      Model.mul (R2W01c.rawModel u) (R2W01c.rawModel v) := by
  have hx := R14NatNormal.raw_normal_decode u hu0 hu
  have hy := R14NatNormal.raw_normal_decode v hv0 hv
  have ha := R2W01c.mantissa_bounds u
  have hb := R2W01c.mantissa_bounds v
  have hm := R14ExponentShift.model_mul_normal_fields (R2W01c.rawModel u) (R2W01c.rawModel v)
    (R2W01c.wordSign u) (R2W01c.wordSign v)
    (R2W01b.mantissa u).toNat (R2W01b.mantissa v).toNat
    (R2W01c.wordExp u) (R2W01c.wordExp v)
    ha.1 ha.2 hb.1 hb.2 hs hs' hx hy
  rw [core_word u v hs hs',Model.NativeBinary32.ofUInt32_mkBits]
  exact hm.symm

theorem core_spec (x y : Binary32)
    (hx0 : 0 < R2W01c.wordExp x.raw.1) (hx : R2W01c.wordExp x.raw.1 < 255)
    (hy0 : 0 < R2W01c.wordExp y.raw.1) (hy : R2W01c.wordExp y.raw.1 < 255)
    (hs : 128 ≤ R2W01c.wordExp x.raw.1 + R2W01c.wordExp y.raw.1)
    (hs' : R2W01c.wordExp x.raw.1 + R2W01c.wordExp y.raw.1 ≤ 380) :
    R7W02.fromRaw (core x.raw.1 y.raw.1) = ExecFloat.Spec.mul x y := by
  apply Configured.Family.toModel_injective
  change ExecFloat.Binary.toModel (R7W02.fromRaw (core x.raw.1 y.raw.1)) =
    ExecFloat.Binary.toModel (ExecFloat.Spec.mul x y)
  rw [R7W02.fromRaw_toModel,← ExecFloat.Proof.mul_eq_spec,R7W01.exec_toModel_mul,
    ← Model.Proof.mul_eq_spec,R7W02.exec_toModel_eq_rawModel x,
    R7W02.exec_toModel_eq_rawModel y,← R2W01c.rawModel_eq_native32 x.raw.1,
    ← R2W01c.rawModel_eq_native32 y.raw.1]
  exact core_model x.raw.1 y.raw.1 hx0 hx hy0 hy hs hs'

theorem guardedMul_spec (fallback : Binary32 → Binary32 → Binary32)
    (hf : ∀ x y, fallback x y = ExecFloat.Spec.mul x y) (x y : Binary32) :
    guardedMul fallback x y = ExecFloat.Spec.mul x y := by
  unfold guardedMul
  dsimp only
  split
  · rename_i hnormal
    split
    · rename_i hsum
      have he : R14ExponentShift.eligible x.raw.1 y.raw.1 = true := by
        simp only [R14ExponentShift.eligible,Bool.and_eq_true,decide_eq_true_eq]
        exact ⟨hnormal,hsum⟩
      rcases R14ExponentShift.eligible_conditions x.raw.1 y.raw.1 he with
        ⟨hx0,hx,hy0,hy,hs,hs'⟩
      change R7W02.fromRaw (core x.raw.1 y.raw.1) = _
      exact core_spec x y hx0 hx hy0 hy hs hs'
    · exact hf x y
  · exact hf x y

end Submission.R19Jam17
