namespace Submission.R17UInt64Fields

open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange
open R17UInt64Integer

def numericProduct (a b : UInt32) : UInt64 :=
  (a.toUInt64 * b.toUInt64).toFloat32.toUInt64

def highWord (a b : UInt32) : UInt64 :=
  if (140737488355328 : UInt64) ≤ numericProduct a b then 1 else 0

def shiftWord (a b : UInt32) : UInt64 := 23 + highWord a b
def mantissaWord (a b : UInt32) : UInt32 :=
  (numericProduct a b >>> shiftWord a b).toUInt32
def fractionWord (a b : UInt32) : UInt32 := mantissaWord a b - 8388608
def exponentWord (sum a b : UInt32) : UInt32 := sum - 127 + (highWord a b).toUInt32

theorem highWord_nat (a b : UInt32)
    (ha0 : 8388608 ≤ a.toNat) (ha : a.toNat < 16777216)
    (hb0 : 8388608 ≤ b.toNat) (hb : b.toNat < 16777216) :
    (highWord a b).toNat = R14ExponentShift.middleExponent (R14ExponentShift.product a b)-173 := by
  have hp := R14ExponentShift.product_bounds a b ha0 ha hb0 hb
  have hr : (numericProduct a b).toNat = roundedInteger (R14ExponentShift.product a b) :=
    numeric_integer_product a b ha0 ha hb0 hb
  have ht := rounded_threshold _ hp.1 hp.2
  unfold highWord
  split
  · rename_i hh
    have hh' : 140737488355328 ≤ roundedInteger (R14ExponentShift.product a b) := by
      rw [UInt64.le_iff_toNat_le,hr] at hh
      exact hh
    change 1 = _
    simpa only [if_pos hh'] using ht
  · rename_i hh
    have hh' : ¬140737488355328 ≤ roundedInteger (R14ExponentShift.product a b) := by
      rw [UInt64.le_iff_toNat_le,hr] at hh
      exact hh
    change 0 = _
    simpa only [if_neg hh'] using ht

theorem shiftWord_nat (a b : UInt32)
    (ha0 : 8388608 ≤ a.toNat) (ha : a.toNat < 16777216)
    (hb0 : 8388608 ≤ b.toNat) (hb : b.toNat < 16777216) :
    (shiftWord a b).toNat = roundedShift (R14ExponentShift.product a b) := by
  have hp := R14ExponentShift.product_bounds a b ha0 ha hb0 hb
  have he := R14ExponentShift.middle_bounds _ hp.1 hp.2
  unfold shiftWord
  rw [UInt64.toNat_add,highWord_nat a b ha0 ha hb0 hb]
  change (23+(R14ExponentShift.middleExponent (R14ExponentShift.product a b)-173)) %
    18446744073709551616 = _
  rw [Nat.mod_eq_of_lt (by omega)]
  unfold roundedShift
  omega

theorem mantissaWord_nat (a b : UInt32)
    (ha0 : 8388608 ≤ a.toNat) (ha : a.toNat < 16777216)
    (hb0 : 8388608 ≤ b.toNat) (hb : b.toNat < 16777216) :
    (mantissaWord a b).toNat = R14NatNormal.mantissa (R14ExponentShift.product a b) := by
  have hp := R14ExponentShift.product_bounds a b ha0 ha hb0 hb
  have hm := R14NatNormal.mantissa_bounds _ hp.1 (by omega)
  have hq := shift_recovery a b (shiftWord a b) ha0 ha hb0 hb
    (shiftWord_nat a b ha0 ha hb0 hb)
  unfold mantissaWord numericProduct
  rw [FastMul.toUInt32_eq,UInt32.toNat_ofNat,hq]
  exact Nat.mod_eq_of_lt (by omega)

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

theorem highWord_toUInt32_nat (a b : UInt32)
    (ha0 : 8388608 ≤ a.toNat) (ha : a.toNat < 16777216)
    (hb0 : 8388608 ≤ b.toNat) (hb : b.toNat < 16777216) :
    (highWord a b).toUInt32.toNat =
      R14ExponentShift.middleExponent (R14ExponentShift.product a b)-173 := by
  have hp := R14ExponentShift.product_bounds a b ha0 ha hb0 hb
  have he := R14ExponentShift.middle_bounds _ hp.1 hp.2
  rw [FastMul.toUInt32_eq,UInt32.toNat_ofNat,highWord_nat a b ha0 ha hb0 hb]
  exact Nat.mod_eq_of_lt (by omega)

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
  rw [UInt32.toNat_add,UInt32.toNat_sub_of_le _ _ hle,highWord_toUInt32_nat a b ha0 ha hb0 hb]
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
  rw [UInt32.toNat_and,UInt32.toNat_ofNat]
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

end Submission.R17UInt64Fields
