section R18PublicMULBridgeProbe
set_option maxRecDepth 8192

namespace Submission.R17NumericMulInteger
open FloatLib.Floats Competition

@[inline] def normalCore (sum u v : UInt32) : UInt32 :=
  let a := (u &&& (0x7fffff : UInt32)) ||| (0x800000 : UInt32)
  let b := (v &&& (0x7fffff : UInt32)) ||| (0x800000 : UInt32)
  let product : UInt64 := a.toUInt64 * b.toUInt64
  let r : UInt64 := product.toFloat32.toUInt64
  let high : UInt64 := if (0x800000000000 : UInt64) ≤ r then 1 else 0
  let q : UInt32 := (r >>> ((23 : UInt64) + high)).toUInt32
  let e : UInt32 := sum - (127 : UInt32) + high.toUInt32
  ((u ^^^ v) &&& (0x80000000 : UInt32)) ||| (e <<< 23) ||| (q - (0x800000 : UInt32))

@[inline] def guardedMul (fallback : Binary32 → Binary32 → Binary32)
    (x y : Binary32) : Binary32 :=
  let u := x.raw.1
  let v := y.raw.1
  let eu := (u >>> 23) &&& (255 : UInt32)
  let ev := (v >>> 23) &&& (255 : UInt32)
  if eu - 1 ≤ (253 : UInt32) ∧ ev - 1 ≤ (253 : UInt32) then
    let s := eu + ev
    if s - 128 ≤ (252 : UInt32) then R7W02.fromRaw (normalCore s u v)
    else fallback x y
  else fallback x y

end Submission.R17NumericMulInteger

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

namespace Submission.R17UInt64Fields

open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange

theorem normalCore_eq_fields (sum u v : UInt32) (sign : Bool)
    (hs0 : 128 ≤ sum.toNat) (hs : sum.toNat ≤ 380)
    (hsign : ((u ^^^ v) &&& (0x80000000 : UInt32)) =
      (if sign then (0x80000000 : UInt32) else 0)) :
    R17NumericMulInteger.normalCore sum u v =
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

end Submission.R17UInt64Fields

namespace Submission.R14NativeProduct

open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange
open FloatLib.Numerics
open Model.NativeBinary32

theorem model_mul_of_nonzero_decodes {fmt : FloatFormat}
    (x y : Model fmt) (dx dy : FloatLib.Numerics.Dyadic)
    (hx : Model.toDyadic? x = some dx) (hy : Model.toDyadic? y = some dy)
    (hx0 : dx.significand ≠ 0) (hy0 : dy.significand ≠ 0) :
    Model.mul x y = Model.roundDyadic fmt
      ⟨Bool.xor dx.negative dy.negative, dx.significand * dy.significand,
        dx.exponent + dy.exponent⟩ := by
  rw [Model.Proof.mul_eq_spec]
  unfold Model.Spec.mul
  rw [hx, hy]
  simp [hx0, hy0]

end Submission.R14NativeProduct


/- Draft: source dependency is retained df5c plus no other R14 fragment.
This version works directly in the actual Nat/Int word-rounder specification. -/

namespace Submission.R14NatNormal
open FloatLib.Floats Competition
open FloatLib.Floats.Formats.BinaryInterchange
theorem raw_normal_decode (u : UInt32)
    (he0 : 0 < R2W01c.wordExp u) (hehi : R2W01c.wordExp u < 255) :
    Model.toDyadic? (R2W01c.rawModel u) =
      some ⟨R2W01c.wordSign u, (R2W01b.mantissa u).toNat,
        (R2W01c.wordExp u : Int) - 150⟩ := by
  rw [R2W01c.rawModel_eq_ofUInt32]
  change Model.toDyadic? (R2W01c.raw32 u) = _
  rw [R2W01c.raw32_eq_fields, R2W01c.mantissa_toNat]
  exact R2W01c.fields32_toDyadic (R2W01c.wordSign u) (R2W01c.wordExp u)
    (R2W01c.wordFrac u) he0 hehi (R2W01c.wordFrac_lt u)



end Submission.R14NatNormal

namespace Submission.R14ExponentShift
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


end Submission.R14ExponentShift

namespace Submission.R14ExponentShift
open FloatLib.Floats Competition
open FloatLib.Floats.Formats.BinaryInterchange
theorem model_mul_normal_fields (x y : Model FloatFormat.binary32)
    (sx sy : Bool) (a b eu ev : Nat)
    (ha0 : 8388608 ≤ a) (ha : a < 16777216)
    (hb0 : 8388608 ≤ b) (hb : b < 16777216)
    (hs : 128 ≤ eu + ev) (hs' : eu + ev ≤ 380)
    (hx : Model.toDyadic? x = some ⟨sx, a, (eu : Int) - 150⟩)
    (hy : Model.toDyadic? y = some ⟨sy, b, (ev : Int) - 150⟩) :
    Model.mul x y = Model.ofFields FloatFormat.binary32 (Bool.xor sx sy)
      (middleExponent (a * b) + eu + ev - 300) (storedFraction (a * b)) := by
  let p := a * b
  let s := eu + ev
  have hpLo : 70368744177664 ≤ p := by
    have h := Nat.mul_le_mul ha0 hb0
    norm_num at h
    exact h
  have hpHi : p ≤ 281474943156225 := by
    have h := Nat.mul_le_mul (show a ≤ 16777215 by omega) (show b ≤ 16777215 by omega)
    norm_num at h
    exact h
  have hpFit : p < 281474976710656 := by omega
  have hp0 : p ≠ 0 := by omega
  have hl := R14NatNormal.leading_bounds p hpLo hpFit
  have hc := R14NatNormal.carry_le p
  have hmRange := middle_bounds p hpLo hpHi
  have hmin : -126 ≤ (p.log2 : Int) + ((s : Int) - 300) := by dsimp [s]; omega
  have hmax : (p.log2 : Int) + ((s : Int) - 300) + (R14NatNormal.carry p : Int) ≤ 127 := by
    dsimp [middleExponent, s] at hmRange ⊢
    omega
  have hm := R14NativeProduct.model_mul_of_nonzero_decodes x y
    ⟨sx, a, (eu : Int) - 150⟩ ⟨sy, b, (ev : Int) - 150⟩
    hx hy (show a ≠ 0 by omega) (show b ≠ 0 by omega)
  change Model.mul x y = Model.roundDyadic FloatFormat.binary32
    ⟨Bool.xor sx sy, p, (eu : Int) - 150 + ((ev : Int) - 150)⟩ at hm
  have hExp : (eu : Int) - 150 + ((ev : Int) - 150) = (s : Int) - 300 := by dsimp [s]; omega
  rw [hExp] at hm
  have hTarget : Int.toNat ((p.log2 : Int) + ((s : Int) - 300) +
      (R14NatNormal.carry p : Int) + 127) = middleExponent p + s - 300 := by
    dsimp [middleExponent, s]
    omega
  rw [R14NatNormal.model_round_normal _ p ((s : Int) - 300)
    hp0 (by omega) hmin hmax, hTarget] at hm
  have hmFields : Model.mul x y = Model.ofFields FloatFormat.binary32 (Bool.xor sx sy)
      (middleExponent p + s - 300) (storedFraction p) := hm
  change Model.mul x y = Model.ofFields FloatFormat.binary32 (Bool.xor sx sy)
    (middleExponent p + eu + ev - 300) (storedFraction p)
  rw [Nat.add_assoc (middleExponent p) eu ev]
  exact hmFields


end Submission.R14ExponentShift

namespace Submission.R14ExponentShift
open FloatLib.Floats Competition
open FloatLib.Floats.Formats.BinaryInterchange
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


end Submission.R14ExponentShift

namespace Submission.R18NumericMulSpec

open FloatLib.Floats Competition
open FloatLib.Floats.Formats.BinaryInterchange

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
  R17NumericMulInteger.normalCore (R14ExponentShift.ex u + R14ExponentShift.ex v) u v

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
  have h := R17UInt64Fields.normalCore_eq_fields
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
    R17NumericMulInteger.guardedMul fallback x y = ExecFloat.Spec.mul x y := by
  unfold R17NumericMulInteger.guardedMul
  try dsimp only
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

end Submission.R18NumericMulSpec

end R18PublicMULBridgeProbe
