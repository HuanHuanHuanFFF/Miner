namespace Submission.R22ScaledFields
open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange

def scaledProduct (a b : UInt32) : UInt32 :=
  ((a.toUInt64*b.toUInt64).toFloat32*R21ScaledU32.powNeg23).toUInt32
def highWord (a b : UInt32) : UInt32 := scaledProduct a b >>> 24
def mantissaWord (a b : UInt32) : UInt32 := scaledProduct a b >>> highWord a b
def fractionWord (a b : UInt32) : UInt32 := mantissaWord a b - 8388608
def exponentWord (sum a b : UInt32) : UInt32 := sum - 127 + highWord a b

theorem highWord_nat (a b : UInt32)
    (ha0 : 8388608 ≤ a.toNat) (ha : a.toNat < 16777216)
    (hb0 : 8388608 ≤ b.toNat) (hb : b.toNat < 16777216) :
    (highWord a b).toNat =
      R14ExponentShift.middleExponent (R14ExponentShift.product a b)-173 := by
  have hp := R14ExponentShift.product_bounds a b ha0 ha hb0 hb
  have he := R14ExponentShift.middle_bounds _ hp.1 hp.2
  have h := (R21ScaledU32.integer_product_scaled_fields a b ha0 ha hb0 hb).1
  change (highWord a b).toNat =
    R17UInt64Integer.roundedShift (R14ExponentShift.product a b)-23 at h
  unfold R17UInt64Integer.roundedShift at h
  omega

theorem mantissaWord_nat (a b : UInt32)
    (ha0 : 8388608 ≤ a.toNat) (ha : a.toNat < 16777216)
    (hb0 : 8388608 ≤ b.toNat) (hb : b.toNat < 16777216) :
    (mantissaWord a b).toNat = R14NatNormal.mantissa (R14ExponentShift.product a b) :=
  (R21ScaledU32.integer_product_scaled_fields a b ha0 ha hb0 hb).2

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
  have hle : (127 : UInt32) ≤ sum := by
    rw [UInt32.le_iff_toNat_le]
    exact Nat.le_trans (by decide) hs0
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
    R21ScaledU32.normalCore sum u v =
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

end Submission.R22ScaledFields
