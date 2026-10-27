
/- Draft dependencies: native-product1, nat-normal-form-draft, general-scale-fusion-draft. -/
namespace Submission.R14TableFactor

open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange
open FloatLib.Numerics

theorem mkBits_zero_nat (sign : Bool) (e : Nat) (he : e < 256) :
    (Model.NativeBinary32.mkBits sign e 0).toNat =
      (if sign then 2147483648 else 0) + e * 8388608 := by
  have hmask : (UInt32.ofNat e &&& 255).toNat = e := by
    rw [UInt32.toNat_and]
    change (e % 4294967296) &&& (2 ^ 8 - 1) = e
    rw [Nat.mod_eq_of_lt (by omega), Nat.and_two_pow_sub_one_eq_mod,
      Nat.mod_eq_of_lt he]
  have hfield : ((UInt32.ofNat e &&& 255) <<< 23).toNat = e * 8388608 := by
    rw [UInt32.toNat_shiftLeft, hmask]
    change (e <<< 23) % 4294967296 = e * 8388608
    rw [Nat.shiftLeft_eq]
    change (e * 8388608) % 4294967296 = _
    exact Nat.mod_eq_of_lt (by omega)
  have hlow : e * 8388608 < 2 ^ 31 := by norm_num; omega
  have hor : 2147483648 ||| (e * 8388608) = 2147483648 + e * 8388608 := by
    simpa using (Nat.two_pow_add_eq_or_of_lt hlow 1).symm
  cases sign <;>
    simp [Model.NativeBinary32.mkBits, UInt32.toNat_or, hfield, hor]

theorem mkBits_zero_exp (sign : Bool) (e : Nat) (he : e < 256) :
    R2W01c.wordExp (Model.NativeBinary32.mkBits sign e 0) = e := by
  unfold R2W01c.wordExp
  rw [mkBits_zero_nat sign e he]
  cases sign <;> simp only [Bool.false_eq_true, Bool.true_eq, ↓reduceIte, Nat.zero_add] <;> omega

theorem mkBits_zero_sign (sign : Bool) (e : Nat) (he : e < 256) :
    R2W01c.wordSign (Model.NativeBinary32.mkBits sign e 0) = sign := by
  apply Bool.eq_iff_iff.mpr
  simp only [R2W01c.wordSign, decide_eq_true_eq]
  rw [mkBits_zero_nat sign e he]
  cases sign <;> simp only [Bool.false_eq_true, Bool.true_eq, ↓reduceIte, Nat.zero_add] <;> omega

theorem mkBits_zero_magnitude (sign : Bool) (e : Nat) (he : e < 256) :
    (R2W01b.magnitude (Model.NativeBinary32.mkBits sign e 0)).toNat = e * 8388608 := by
  rw [R2W01b.magnitude_toNat, mkBits_zero_nat sign e he]
  cases sign <;> simp only [Bool.false_eq_true, Bool.true_eq, ↓reduceIte, Nat.zero_add] <;> omega

theorem mkBits_zero_normalBand (sign : Bool) (e : Nat) (he0 : 24 ≤ e) (hehi : e ≤ 254) :
    R2W01b.NormalBand (Model.NativeBinary32.mkBits sign e 0) := by
  have he : e < 256 := by omega
  unfold R2W01b.NormalBand
  constructor
  · rw [UInt32.le_iff_toNat_le, mkBits_zero_magnitude sign e he]
    change 201326592 ≤ e * 8388608
    omega
  · rw [UInt32.lt_iff_toNat_lt, mkBits_zero_magnitude sign e he]
    change e * 8388608 < 2139095040
    omega

theorem table_factor_decode (sign : Bool) (s : Nat) (hs : 174 ≤ s) (hs' : s ≤ 380) :
    Model.toDyadic? (R2W01c.nativeModel
      (R2W01b.scaleAt (Model.NativeBinary32.mkBits sign (s - 150) 0))) =
      some ⟨sign, 2 ^ 23, (s : Int) - 323⟩ := by
  have he0 : 24 ≤ s - 150 := by omega
  have hehi : s - 150 ≤ 254 := by omega
  have he : s - 150 < 256 := by omega
  have hn := mkBits_zero_normalBand sign (s - 150) he0 hehi
  have hd := R2W01c.scale_native_decode
    (Model.NativeBinary32.mkBits sign (s - 150) 0) hn
  rw [mkBits_zero_sign sign (s - 150) he, mkBits_zero_exp sign (s - 150) he] at hd
  have hexp : ((s - 150 : Nat) : Int) - 173 = (s : Int) - 323 := by omega
  simpa only [hexp] using hd

theorem native_eq_of_nonzero_decode (x y : Float32) (d : Dyadic)
    (hx : Model.toDyadic? (R2W01c.nativeModel x) = some d)
    (hy : Model.toDyadic? (R2W01c.nativeModel y) = some d)
    (hd : d.significand ≠ 0) : x = y := by
  apply R2W01c.native_eq_of_model_eq
  have hxf := Model.isFinite_eq_true_of_toDyadic?_some hx
  have hyf := Model.isFinite_eq_true_of_toDyadic?_some hy
  have hvalue : Model.toReal (R2W01c.nativeModel x) =
      Model.toReal (R2W01c.nativeModel y) := by
    simp only [Model.toReal_eq, hx, hy]
  have hx0 : Model.toReal (R2W01c.nativeModel x) ≠ 0 := by
    simp only [Model.toReal_eq, hx]
    exact (Dyadic.toReal_eq_zero_iff d).not.mpr hd
  exact Model.eq_of_toReal_eq_of_nonzero hxf hyf hvalue hx0

theorem table_factor_eq (sign : Bool) (s : Nat) (hs : 174 ≤ s) (hs' : s ≤ 380) :
    R2W01b.scaleAt (Model.NativeBinary32.mkBits sign (s - 150) 0) =
      Float32.ofBits (Model.NativeBinary32.mkBits sign (s - 173) 0) := by
  exact native_eq_of_nonzero_decode _ _ ⟨sign, 2 ^ 23, (s : Int) - 323⟩
    (table_factor_decode sign s hs hs')
    (R14GeneralFusion.factor_integer_decode sign s hs hs') (by decide)

theorem integer_table_fusion (mx my : UInt32) (s : Nat) (sign : Bool)
    (hmx : 8388608 ≤ mx.toNat) (hmx' : mx.toNat < 16777216)
    (hmy : 8388608 ≤ my.toNat) (hmy' : my.toNat < 16777216)
    (hs : 174 ≤ s) (hs' : s ≤ 380) :
    R2W01c.nativeModel
      ((mx.toFloat32 * my.toFloat32) *
        R2W01b.scaleAt (Model.NativeBinary32.mkBits sign (s - 150) 0)) =
      Model.roundDyadic FloatFormat.binary32
        ⟨sign, mx.toNat * my.toNat, (s : Int) - 300⟩ := by
  rw [table_factor_eq sign s hs hs']
  exact R14GeneralFusion.integer_mantissa_fusion mx my s sign hmx hmx' hmy hmy' hs hs'

end Submission.R14TableFactor
