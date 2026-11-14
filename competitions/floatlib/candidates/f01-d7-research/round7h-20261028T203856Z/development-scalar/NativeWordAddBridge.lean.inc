/- Portable FloatLib-only semantic interface, NOT_COMPILED.
   No new contest kernel, caller, timing target or imported primitive.
   Pins: FloatLib 0d91825727839f597fd06b22fdd038ea21480f0c, Lean4.34.
   Reuses operator-supplied finite native ADD and native representation theorems.
   raw_bits proof follows ExactToolkit.Decode.ofUInt32_bits (same UInt32 identity). -/
namespace R24NativeWordBridge
open FloatLib.Floats FloatLib.Floats.Formats.BinaryInterchange
abbrev F := FloatFormat.binary32
@[inline] def raw (w : UInt32) : Model F := Model.ofUInt32 w

theorem raw_bits (w : UInt32) : (raw w).bits = w.toBitVec := by
  show BitVec.ofNat 32 w.toNat = w.toBitVec
  rw [show w.toNat = w.toBitVec.toNat from rfl, BitVec.ofNat_toNat, BitVec.setWidth_eq]

theorem model_from_bits (w : UInt32) :
    Model.ofFloat32Model (Float32.ofBits w).toModel =
      Model.canonicalizeModel (raw w) := by
  change Model.ofFloat32Model (Float32.Model.pack
    (Float.Model.UnpackedFloat.unpack Float.Model.Format.binary32 w.toBitVec)) = _
  rw [Model.ofFloat32Model_pack]
  change Model.ofModel F
      (Float.Model.UnpackedFloat.unpack Float.Model.Format.binary32 w.toBitVec) =
    Model.ofModel F
      (Float.Model.UnpackedFloat.unpack Float.Model.Format.binary32 (raw w).bits)
  rw [raw_bits]

theorem unpack_from_bits (w : UInt32) :
    (Float32.ofBits w).toModel.unpack = Model.toModel (raw w) := by
  have h := congrArg Model.toModel (model_from_bits w)
  simpa only [Model.toModel_ofFloat32Model, Model.toModel_canonicalizeModel] using h

theorem native_word (f : Float32) :
    UInt32.ofNat (Model.ofFloat32Model f.toModel).toNatBits = f.toBits := by
  change UInt32.ofNat f.toModel.toBits.toNat = f.toModel.toBits
  simp only [UInt32.ofNat_toNat]

theorem native_add_model (u v : UInt32)
    (hu : (Model.toModel (raw u)).isFinite = true)
    (hv : (Model.toModel (raw v)).isFinite = true) :
    Model.ofFloat32Model (Float32.ofBits u + Float32.ofBits v).toModel =
      Model.add (raw u) (raw v) := by
  change Model.ofFloat32Model (Float32.Model.pack
    (Float.Model.UnpackedFloat.add Float.Model.Format.binary32
      (Float32.ofBits u).toModel.unpack (Float32.ofBits v).toModel.unpack)) = _
  rw [Model.ofFloat32Model_pack, unpack_from_bits, unpack_from_bits]
  exact (Model.add_eq_ofModel_add_of_isFinite (by decide) (raw u) (raw v) hu hv).symm

theorem native_add_word (u v : UInt32)
    (hu : (Model.toModel (raw u)).isFinite = true)
    (hv : (Model.toModel (raw v)).isFinite = true) :
    (Float32.ofBits u + Float32.ofBits v).toBits =
      UInt32.ofNat (Model.add (raw u) (raw v)).toNatBits := by
  rw [← native_add_model u v hu hv]
  exact (native_word _).symm
end R24NativeWordBridge
