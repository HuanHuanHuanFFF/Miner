/- R22 two small bridges for fixed S174..380. NOT_RUN.
   Uses existing B2 real-value/native bridges; no public mul_spec or runtime change. -/
namespace Submission.R22NativeProductScaleMath
open FloatLib FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange

theorem synthetic_scale_decode (s : UInt32) (sign : Bool)
    (hs0 : 174 ≤ s.toNat) (hs1 : s.toNat ≤ 380) :
    Model.toDyadic? (R2W01c.nativeModel (R2W01b.scaleAt
      (((s - (150 : UInt32)) <<< (23 : UInt32)) |||
        (if sign then (0x80000000 : UInt32) else 0)))) =
      some ⟨sign, 8388608, (s.toNat : Int) - 323⟩ := by
  let q : UInt32 := (s - (150 : UInt32)) <<< (23 : UInt32)
  let w : UInt32 := q ||| (if sign then (0x80000000 : UInt32) else 0)
  change Model.toDyadic? (R2W01c.nativeModel (R2W01b.scaleAt w)) = _
  have hle : (150 : UInt32) ≤ s := by
    rw [UInt32.le_iff_toNat_le]
    change 150 ≤ s.toNat
    omega
  have hsub : (s - (150 : UInt32)).toNat = s.toNat - 150 :=
    UInt32.toNat_sub_of_le _ _ hle
  have hq : q.toNat = (s.toNat - 150) * 8388608 := by
    dsimp only [q]
    rw [UInt32.toNat_shiftLeft, hsub]
    change ((s.toNat - 150) <<< 23) % 4294967296 = _
    rw [Nat.shiftLeft_eq]
    change ((s.toNat - 150) * 8388608) % 4294967296 = _
    exact Nat.mod_eq_of_lt (by omega)
  have hmag : (s.toNat - 150) * 8388608 < 2147483648 := by omega
  have hw : w.toNat = (if sign then 2147483648 else 0) + (s.toNat - 150) * 8388608 := by
    dsimp only [w]
    rw [UInt32.toNat_or, hq]
    cases sign
    · change (s.toNat - 150) * 8388608 ||| 0 = 0 + (s.toNat - 150) * 8388608
      simp
    · change (s.toNat - 150) * 8388608 ||| 2 ^ 31 = 2147483648 + (s.toNat - 150) * 8388608
      rw [Nat.or_two_pow_eq_add_of_lt hmag]
      omega
  have hband : R2W01b.NormalBand w := by
    simp only [R2W01b.NormalBand, UInt32.le_iff_toNat_le, UInt32.lt_iff_toNat_lt,
      R2W01b.magnitude_toNat]
    change 201326592 ≤ w.toNat % 2147483648 ∧ w.toNat % 2147483648 < 2139095040
    simp only [hw]
    split_ifs <;> omega
  have hE : R2W01c.wordExp w = s.toNat - 150 := by
    simp only [R2W01c.wordExp, hw]
    split_ifs <;> omega
  have hsign : R2W01c.wordSign w = sign := by
    apply Bool.eq_iff_iff.mpr
    simp only [R2W01c.wordSign, decide_eq_true_eq, hw]
    cases sign <;> simp <;> omega
  have hd := R2W01c.scale_native_decode w hband
  have he : ((s.toNat - 150 : Nat) : Int) - 173 = (s.toNat : Int) - 323 := by omega
  simpa only [hE, hsign, he] using hd

theorem native_product_scale_eq_target (x : Float32) (s : UInt32) (sign : Bool) (m e : Nat)
    (hs0 : 174 ≤ s.toNat) (hs1 : s.toNat ≤ 380)
    (hm0 : 8388608 ≤ m) (hm1 : m < 16777216) (he : e = 23 ∨ e = 24)
    (hx : Model.toDyadic? (R2W01c.nativeModel x) = some ⟨false, m, (e : Int)⟩) :
    x * R2W01b.scaleAt (((s - (150 : UInt32)) <<< (23 : UInt32)) |||
      (if sign then (0x80000000 : UInt32) else 0)) =
      Float32.ofBits (Model.NativeBinary32.mkBits sign (e + s.toNat - 150) (m - 8388608)) := by
  let w : UInt32 := ((s - (150 : UInt32)) <<< (23 : UInt32)) |||
    (if sign then (0x80000000 : UInt32) else 0)
  let E : Nat := e + s.toNat - 150
  let z : UInt32 := Model.NativeBinary32.mkBits sign E (m - 8388608)
  change x * R2W01b.scaleAt w = Float32.ofBits z
  have hy := synthetic_scale_decode s sign hs0 hs1
  have hE0 : 0 < E := by dsimp [E]; omega
  have hE1 : E < 255 := by dsimp [E]; omega
  have hf : m - 8388608 < 8388608 := by omega
  have hm : 8388608 + (m - 8388608) = m := by omega
  have hexp : (E : Int) - 150 = (e : Int) + (s.toNat : Int) - 300 := by dsimp [E]; omega
  have hz : Model.toDyadic? (R2W01c.rawModel z) =
      some ⟨sign, m, (e : Int) + (s.toNat : Int) - 300⟩ := by
    rw [z, R2W01c.rawModel_eq_native32, Model.NativeBinary32.ofUInt32_mkBits]
    simpa only [hm, hexp] using R2W01c.fields32_toDyadic sign E (m - 8388608) hE0 hE1 hf
  have hz0 : Model.toReal (R2W01c.rawModel z) ≠ 0 := by
    have hd0 : (Numerics.Dyadic.mk sign m ((e : Int) + (s.toNat : Int) - 300)).toReal ≠ 0 :=
      (Numerics.Dyadic.toReal_eq_zero_iff _).not.mpr (by omega : m ≠ 0)
    simpa only [Model.toReal_eq, hz] using hd0
  have hvalue : (Numerics.Dyadic.mk false m (e : Int)).toReal *
      (Numerics.Dyadic.mk sign 8388608 ((s.toNat : Int) - 323)).toReal =
      (Numerics.Dyadic.mk sign m ((e : Int) + (s.toNat : Int) - 300)).toReal := by
    have hExp : (e : Int) + (s.toNat : Int) - 300 =
        (e : Int) + ((s.toNat : Int) - 323) + 23 := by omega
    rw [hExp]
    cases sign <;> norm_num [Numerics.Dyadic.toReal, Numerics.Dyadic.signedSignificand,
      zpow_add₀ (by norm_num : (2 : ℝ) ≠ 0)] <;> ring
  have hmul : Model.mul (R2W01c.nativeModel x) (R2W01c.nativeModel (R2W01b.scaleAt w)) =
      R2W01c.rawModel z := by
    apply R2W01cModel.mul_eq_of_finite_value _ _ _ (by decide)
      (Model.isFinite_eq_true_of_toDyadic?_some hx)
      (Model.isFinite_eq_true_of_toDyadic?_some hy)
      (Model.isFinite_eq_true_of_toDyadic?_some hz) hz0
    simpa only [Model.toReal_eq, hx, hy, hz] using hvalue
  exact R2W01c.native_mul_eq_of_decoded_raw_model_mul_eq x (R2W01b.scaleAt w) z hx hy hmul

end Submission.R22NativeProductScaleMath
