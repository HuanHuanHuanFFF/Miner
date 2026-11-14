namespace Submission.R24DotEnclosure
open FloatLib.Floats FloatLib.Floats.Formats.BinaryInterchange FloatLib.Floats.Formats.Flocq
open Submission.R24RepresentationSum
abbrev F64 := FloatFormat.binary64
abbrev F32 := FloatFormat.binary32
abbrev raw32 (u : UInt32) : Model F32 := Model.ofUInt32 u
theorem native_mul (x y : Float) (hx : x.isFinite = true) (hy : y.isFinite = true) :
    native (x * y) = Model.mul (native x) (native y) := by
  change Model.ofFloatModel (Float.Model.mul x.toModel y.toModel) = _
  rw [Float.Model.mul, Model.ofFloatModel_pack]
  have h := R2W01c.NativeBridge.modelMulFinite (fmt := F64)
    (by decide) (Model.ofFloatModel x.toModel) (Model.ofFloatModel y.toModel)
    (by simpa only [Model.toModel_ofFloatModel, Float.isFinite,
      Float.Model.isFinite] using hx)
    (by simpa only [Model.toModel_ofFloatModel, Float.isFinite,
      Float.Model.isFinite] using hy)
  rw [Model.toModel_ofFloatModel, Model.toModel_ofFloatModel] at h
  exact h.symm
theorem f32_product_grid (a b : Model F32)
    (ha : Model.isFinite a = true) (hb : Model.isFinite b = true) :
    FloatLib.Floats.Formats.Flocq.genericFormat FloatLib.Numerics.binaryRadix
      (Model.fexpOf F64) (Model.toReal a * Model.toReal b) := by
  obtain ⟨da, hda⟩ := Model.exists_toDyadic?_of_isFinite ha
  obtain ⟨db, hdb⟩ := Model.exists_toDyadic?_of_isFinite hb
  let d : FloatLib.Numerics.Dyadic :=
    ⟨Bool.xor da.negative db.negative, da.significand * db.significand,
      da.exponent + db.exponent⟩
  have hma := Model.toDyadic?_significand_lt a hda
  have hmb := Model.toDyadic?_significand_lt b hdb
  change da.significand < 2 ^ 24 at hma
  change db.significand < 2 ^ 24 at hmb
  have hsig : d.significand < 2 ^ (F64.fracWidth + 1) := by
    change da.significand * db.significand < 2 ^ 53
    calc
      da.significand * db.significand < 2 ^ 24 * 2 ^ 24 := Nat.mul_lt_mul'' hma hmb
      _ < 2 ^ 53 := by norm_num
  have hea := Model.minSubnormalExponent_le_toDyadic? a hda
  have heb := Model.minSubnormalExponent_le_toDyadic? b hdb
  change (-149 : Int) ≤ da.exponent at hea
  change (-149 : Int) ≤ db.exponent at heb
  have he : F64.minSubnormalExponent ≤ d.exponent := by
    change (-1074 : Int) ≤ da.exponent + db.exponent
    omega
  have hg := Model.Dyadic.genericFormat_of_significand_lt F64 d hsig he
  have hv : d.toReal = Model.toReal a * Model.toReal b := by
    simpa only [d, Model.toReal_eq, hda, hdb] using Model.Dyadic.toReal_mul da db
  rw [hv] at hg
  exact hg
end Submission.R24DotEnclosure
