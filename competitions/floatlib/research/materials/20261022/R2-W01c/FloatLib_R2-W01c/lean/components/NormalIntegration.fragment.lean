namespace R2W01c

open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange
open R2W01b

theorem mantissa_native_decode (u : UInt32) :
    Model.toDyadic? (nativeModel (mantissa u).toFloat32) =
      some ⟨false, (mantissa u).toNat, 0⟩ := by
  have hm := mantissa_bounds u
  simpa only [nativeModel, ExecFloat.Binary.toModel_ofFloat32] using
    uint32_mantissa_model_decode (mantissa u) hm.1 hm.2

theorem scale_native_decode (u : UInt32) (hn : NormalBand u) :
    Model.toDyadic? (nativeModel (scaleAt u)) =
      some ⟨wordSign u, 2 ^ 23, (wordExp u : Int) - 173⟩ := by
  rw [scaleAt_eq]
  apply nativeModel_ofBits_decode
  rw [rawModel_eq_ofUInt32]
  exact scale_raw32_decode u hn

theorem target_raw_decode (u : UInt32) (hn : NormalBand u) :
    Model.toDyadic? (rawModel u) =
      some ⟨wordSign u, (mantissa u).toNat, (wordExp u : Int) - 150⟩ := by
  rw [rawModel_eq_ofUInt32]
  exact normal_raw32_decode u hn

theorem normal_model_mul (u : UInt32) (hn : NormalBand u) :
    Model.mul (nativeModel (mantissa u).toFloat32) (nativeModel (scaleAt u)) =
      rawModel u := by
  apply R2W01cModel.binary32_mantissa_scale_mul
    (nativeModel (mantissa u).toFloat32) (nativeModel (scaleAt u)) (rawModel u)
    (wordSign u) (mantissa u).toNat (wordExp u)
  · have hm := (mantissa_bounds u).1
    omega
  · exact mantissa_native_decode u
  · exact scale_native_decode u hn
  · exact target_raw_decode u hn

theorem normal_eq (u : UInt32) (hn : NormalBand u) :
    tableProduct u = Float32.ofBits u := by
  exact native_mul_eq_of_decoded_raw_model_mul_eq
    (mantissa u).toFloat32 (scaleAt u) u
    (mantissa_native_decode u) (scale_native_decode u hn) (normal_model_mul u hn)

theorem normal_bits (u : UInt32) (hn : NormalBand u) :
    (tableProduct u).toBits = u := by
  exact native_mul_bits_eq_of_raw_model_mul_eq
    (mantissa u).toFloat32 (scaleAt u) u
    (nativeFinite_of_decode _ (mantissa_native_decode u))
    (nativeFinite_of_decode _ (scale_native_decode u hn)) (normal_model_mul u hn)

theorem normal_finite (u : UInt32) (hn : NormalBand u) :
    (tableProduct u).isFinite = true := by
  rw [normal_eq u hn]
  exact nativeFinite_of_decode _
    (nativeModel_ofBits_decode u (target_raw_decode u hn))

theorem convert_eq (u : UInt32) : convert u = Float32.ofBits u := by
  exact R2W01b.convert_eq normal_eq u

theorem convert_bits_eq (u : UInt32) :
    (convert u).toBits = (Float32.ofBits u).toBits := by
  exact congrArg Float32.toBits (convert_eq u)

theorem replace_decoder {α : Sort _}
    (core : (UInt32 → Float32) → α) : core convert = core Float32.ofBits := by
  exact congrArg core (funext convert_eq)

theorem foldl_convert_eq
    (xs : List UInt32) (step : Float32 → Float32 → Float32) (acc : Float32) :
    xs.foldl (fun z u => step z (convert u)) acc =
      xs.foldl (fun z u => step z (Float32.ofBits u)) acc := by
  exact R2W01b.foldl_convert_eq normal_eq xs step acc

end R2W01c
