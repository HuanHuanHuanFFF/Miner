/- R16 research fragment, NOT_COMPILED.
   Dependencies are copied byte-for-byte from the full-gated R14 mul-cache-rse2
   mathematical namespaces. Runtime is native mantissa multiplication plus
   explicit field repacking; there is no software RSE runtime in this arm. -/

theorem first_product_bits (mx my : UInt32)
    (hx0 : 8388608 ≤ mx.toNat) (hx : mx.toNat < 16777216)
    (hy0 : 8388608 ≤ my.toNat) (hy : my.toNat < 16777216) :
    (mx.toFloat32 * my.toFloat32).toBits =
      Model.NativeBinary32.mkBits false
        (middleExponent (product mx my)) (storedFraction (product mx my)) := by
  have hmx := R2W01c.uint32_mantissa_model_decode mx hx0 hx
  have hmy := R2W01c.uint32_mantissa_model_decode my hy0 hy
  apply R2W01c.native_mul_bits_eq_of_raw_model_mul_eq
  · exact R2W01c.nativeFinite_of_decode mx.toFloat32 hmx
  · exact R2W01c.nativeFinite_of_decode my.toFloat32 hmy
  · have hm := model_mul_normal_fields
      (R2W01c.nativeModel mx.toFloat32) (R2W01c.nativeModel my.toFloat32)
      false false mx.toNat my.toNat 150 150 hx0 hx hy0 hy
      (by decide) (by decide) (by simpa using hmx) (by simpa using hmy)
    have he : middleExponent (mx.toNat * my.toNat) + 150 + 150 - 300 =
        middleExponent (mx.toNat * my.toNat) := by omega
    rw [he, Bool.false_xor] at hm
    rw [R2W01c.rawModel_eq_native32, Model.NativeBinary32.ofUInt32_mkBits]
    exact hm

theorem packed_ex_nat (e f : Nat) (he : e < 256) :
    (ex (Model.NativeBinary32.mkBits false e f)).toNat = e := by
  unfold ex
  rw [← Model.NativeBinary32.toUInt32_ofFields, Model.NativeBinary32.expField_toNat]
  exact Model.expField_ofFields_of_lt FloatFormat.binary32 false e f he

theorem packed_frac_nat (e f : Nat) (hf : f < 8388608) :
    (Model.NativeBinary32.fracField
      (Model.NativeBinary32.mkBits false e f)).toNat = f := by
  rw [← Model.NativeBinary32.toUInt32_ofFields, Model.NativeBinary32.fracField_toNat]
  exact Model.fracField_ofFields_of_lt FloatFormat.binary32 false e f hf

@[inline] def middleWord (u v : UInt32) : UInt32 :=
  ((R2W01b.mantissa u).toFloat32 * (R2W01b.mantissa v).toFloat32).toBits

@[inline] def outputExponent (u v : UInt32) : UInt32 :=
  ex (middleWord u v) + ex u + ex v - (300 : UInt32)

@[inline] def core (u v : UInt32) : UInt32 :=
  let mid := middleWord u v
  FastMul.mkW (sign u v) (ex mid + ex u + ex v - (300 : UInt32))
    (Model.NativeBinary32.fracField mid)

theorem middleWord_eq (u v : UInt32) :
    middleWord u v = Model.NativeBinary32.mkBits false
      (middleExponent (product (R2W01b.mantissa u) (R2W01b.mantissa v)))
      (storedFraction (product (R2W01b.mantissa u) (R2W01b.mantissa v))) := by
  have hx := R2W01c.mantissa_bounds u
  have hy := R2W01c.mantissa_bounds v
  exact first_product_bits _ _ hx.1 hx.2 hy.1 hy.2

theorem middle_fields (u v : UInt32) :
    (ex (middleWord u v)).toNat =
        middleExponent (product (R2W01b.mantissa u) (R2W01b.mantissa v)) ∧
    (Model.NativeBinary32.fracField (middleWord u v)).toNat =
        storedFraction (product (R2W01b.mantissa u) (R2W01b.mantissa v)) := by
  have hx := R2W01c.mantissa_bounds u
  have hy := R2W01c.mantissa_bounds v
  have hp := product_bounds _ _ hx.1 hx.2 hy.1 hy.2
  have hb := middle_bounds _ hp.1 hp.2
  rw [middleWord_eq]
  exact ⟨packed_ex_nat _ _ (by omega), packed_frac_nat _ _ hb.2.2⟩

theorem outputExponent_nat (u v : UInt32)
    (hs : 128 ≤ R2W01c.wordExp u + R2W01c.wordExp v) :
    (outputExponent u v).toNat =
      middleExponent (product (R2W01b.mantissa u) (R2W01b.mantissa v)) +
        R2W01c.wordExp u + R2W01c.wordExp v - 300 := by
  have hx := R2W01c.mantissa_bounds u
  have hy := R2W01c.mantissa_bounds v
  have hp := product_bounds _ _ hx.1 hx.2 hy.1 hy.2
  have hb := middle_bounds _ hp.1 hp.2
  have hu := ex_bound u
  have hv := ex_bound v
  rw [ex_nat] at hu hv
  have hmid := (middle_fields u v).1
  have hsum : (ex (middleWord u v) + ex u + ex v).toNat =
      middleExponent (product (R2W01b.mantissa u) (R2W01b.mantissa v)) +
        R2W01c.wordExp u + R2W01c.wordExp v := by
    rw [UInt32.toNat_add, UInt32.toNat_add, hmid, ex_nat, ex_nat]
    rw [Nat.mod_eq_of_lt (by omega), Nat.mod_eq_of_lt (by omega)]
  have hle : (300 : UInt32) ≤ ex (middleWord u v) + ex u + ex v := by
    rw [UInt32.le_iff_toNat_le, hsum]
    change 300 ≤ _
    omega
  unfold outputExponent
  rw [UInt32.toNat_sub_of_le _ _ hle, hsum]
  rfl

theorem core_word (u v : UInt32)
    (hs : 128 ≤ R2W01c.wordExp u + R2W01c.wordExp v)
    (hs' : R2W01c.wordExp u + R2W01c.wordExp v ≤ 380) :
    core u v = Model.NativeBinary32.mkBits
      (Bool.xor (R2W01c.wordSign u) (R2W01c.wordSign v))
      (middleExponent (product (R2W01b.mantissa u) (R2W01b.mantissa v)) +
        R2W01c.wordExp u + R2W01c.wordExp v - 300)
      (storedFraction (product (R2W01b.mantissa u) (R2W01b.mantissa v))) := by
  change FastMul.mkW (sign u v) (outputExponent u v)
    (Model.NativeBinary32.fracField (middleWord u v)) = _
  calc
    _ = FastMul.mkW (sign u v)
        (UInt32.ofNat (outputExponent u v).toNat)
        (UInt32.ofNat (Model.NativeBinary32.fracField (middleWord u v)).toNat) := by
          rw [UInt32.ofNat_toNat, UInt32.ofNat_toNat]
    _ = Model.NativeBinary32.mkBits (sign u v)
        (outputExponent u v).toNat
        (Model.NativeBinary32.fracField (middleWord u v)).toNat :=
          FastMul.mkW_ofNat _ _ _
    _ = _ := by rw [outputExponent_nat u v hs, (middle_fields u v).2, sign_eq]
