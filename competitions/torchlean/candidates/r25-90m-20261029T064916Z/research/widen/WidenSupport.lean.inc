/- Minimal dependency closure extracted from the retained B2 source.
   Only word decoding and model canonicality; no B2 runtime or public endpoints. -/
namespace R2W01c
open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange

theorem modelCanonicalOfFinite {fmt : FloatFormat} (x : Model fmt)
    (hx : (Model.toModel x).isFinite = true) : Model.IsModelCanonical x := by
  constructor
  intro he hm
  have hnan : Model.toModel x = Float.Model.UnpackedFloat.notANumber := by
    simp only [Model.toModel, Float.Model.UnpackedFloat.unpack, he, hm, ite_true, ite_false]
  rw [hnan] at hx
  cases hx

theorem modelCanonical_of_decode {fmt : FloatFormat}
    (hfmt : fmt.isIEEE = true) (x : Model fmt) {d : FloatLib.Numerics.Dyadic}
    (hd : Model.toDyadic? x = some d) : Model.IsModelCanonical x := by
  apply modelCanonicalOfFinite
  rw [Model.toDyadic?_ieee_eq_model fmt hfmt x] at hd
  cases hx : Model.toModel x <;>
    simp_all [Model.unpackedToDyadic?, Float.Model.UnpackedFloat.isFinite]

theorem fields32_toDyadic (s : Bool) (e f : Nat)
    (he0 : 0 < e) (he : e < 255) (hf : f < 8388608) :
    Model.toDyadic? (Model.ofFields FloatFormat.binary32 s e f) =
      some ⟨s, 8388608 + f, (e : Int) - 150⟩ := by
  have h := Model.toDyadic?_ofFields_normal FloatFormat.binary32 s e f
    (Nat.ne_of_gt he0) he hf
  change Model.toDyadic? (Model.ofFields FloatFormat.binary32 s e f) =
    some ⟨s, 8388608 + f, (e : Int) - 127 - 23⟩ at h
  have hexp : (e : Int) - 127 - 23 = (e : Int) - 150 := by omega
  simpa only [hexp] using h

abbrev raw32 (u : UInt32) : Model FloatFormat.binary32 :=
  Model.ofUInt32 u

def wordSign (u : UInt32) : Bool :=
  decide (2147483648 ≤ u.toNat)

def wordExp (u : UInt32) : Nat :=
  u.toNat / 8388608 % 256

def wordFrac (u : UInt32) : Nat :=
  u.toNat % 8388608

theorem raw32_bits (u : UInt32) : (raw32 u).bits = u.toBitVec := by
  change BitVec.ofNat 32 u.toNat = u.toBitVec
  exact BitVec.ofNat_uInt32ToNat u

theorem raw32_sign (u : UInt32) : Model.signBit (raw32 u) = wordSign u := by
  rw [Model.signBit_eq_msb, raw32_bits]
  exact BitVec.msb_eq_decide u.toBitVec

theorem raw32_exp (u : UInt32) : Model.expField (raw32 u) = wordExp u := by
  unfold Model.expField
  rw [raw32_bits]
  change ((u.toBitVec >>> 23) &&& (BitVec.ofNat 32 255)).toNat = wordExp u
  rw [BitVec.toNat_and, BitVec.toNat_ushiftRight]
  change (u.toNat >>> 23) &&& (2 ^ 8 - 1) = u.toNat / 8388608 % 256
  rw [Nat.and_two_pow_sub_one_eq_mod, Nat.shiftRight_eq_div_pow]

theorem raw32_frac (u : UInt32) : Model.fracField (raw32 u) = wordFrac u := by
  unfold Model.fracField
  rw [raw32_bits]
  change (u.toBitVec &&& (BitVec.ofNat 32 8388607)).toNat = wordFrac u
  rw [BitVec.toNat_and]
  change u.toNat &&& (2 ^ 23 - 1) = u.toNat % 2 ^ 23
  exact Nat.and_two_pow_sub_one_eq_mod u.toNat 23

theorem raw32_eq_fields (u : UInt32) :
    raw32 u = Model.ofFields FloatFormat.binary32 (wordSign u) (wordExp u)
      (wordFrac u) := by
  rw [← raw32_sign, ← raw32_exp, ← raw32_frac]
  exact (Model.ofFields_signBit_expField_fracField (raw32 u)).symm

theorem wordFrac_lt (u : UInt32) : wordFrac u < 8388608 :=
  Nat.mod_lt _ (by decide)

end R2W01c
