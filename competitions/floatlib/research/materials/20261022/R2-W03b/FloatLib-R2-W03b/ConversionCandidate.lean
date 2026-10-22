import ContractTensor

/-
R2-W03b. Fixed-source proof draft. Compilation status: NOT_RUN.
The proofs round_at_target and ofNat_eq_round are local adaptations from
FloatLib/Floats/Formats/IEEE754/Native/Integer/Constructors.lean,
commit 0d91825727839f597fd06b22fdd038ea21480f0c.
Authors of the adapted portions: FloatLib Team.

MIT License

Copyright (c) 2026 FloatLib

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
-/

namespace R2W03b

open Float.Model
open Float.Model.UnpackedFloat

abbrev f32Spec := Float.Model.Format.binary32

def zero32 : Float32 := Float32.ofBits 0x00000000

@[inline] def exponent (u : UInt32) : UInt32 := (u >>> 23) &&& 255

@[inline] def mantissa (u : UInt32) : UInt32 :=
  (u &&& 0x007fffff) ||| 0x00800000

def signedScaleTable : Array Float32 :=
  Array.ofFn fun (i : Fin 512) =>
    let j := UInt32.ofNat i.val
    let e := j &&& 255
    let s := (j &&& 256) <<< 23
    let b := if 24 <= e ∧ e <= 254 then s ||| ((e - 23) <<< 23) else s
    Float32.ofBits b

@[inline] def fromBitsTableWith
    (table : @& Array Float32) (z : Float32) (u : UInt32) : Float32 :=
  if u == 0 then z
  else
    let e := exponent u
    if 24 <= e ∧ e <= 254 then
      (mantissa u).toFloat32 * table.getD (u >>> 23).toNat z
    else Float32.ofBits u

@[inline] def fromBitsTable (u : UInt32) : Float32 :=
  fromBitsTableWith signedScaleTable zero32 u

theorem float32_eq_of_toModel_eq (a b : Float32)
    (h : a.toModel = b.toModel) : a = b := by
  cases a
  cases b
  cases h
  rfl

theorem round_at_target
    (spec : Format) (s : Sign) (m : Nat) (e : Int) (hm : m ≠ 0)
    (he : spec.targetExponent (totalExponent m e) = e) :
    round spec s m e = .finite s m e (Nat.pos_of_ne_zero hm) := by
  have hshift (em : ExtendedMantissa) : em >>> 0 = em := rfl
  simp [Float.Model.UnpackedFloat.round, decreaseExponent, he, roundWithAccuracy,
    shiftToTargetExponent, shiftToExponent, ExtendedMantissa.ofMantissaAndAccuracy,
    ExtendedMantissa.roundedMantissa, ExtendedMantissa.accuracy,
    Accuracy.roundToNearestEven, hshift, hm]

theorem round_normalized24 (s : Sign) (m : Nat)
    (hm : m ≠ 0) (hlog : m.log2 = 23) (e : Int) (hmin : -149 ≤ e) :
    round f32Spec s m e = .finite s m e (Nat.pos_of_ne_zero hm) := by
  apply round_at_target f32Spec s m e hm
  simp only [f32Spec, Format.targetExponent, totalExponent, hlog]
  change max (24 + e - 24) (-149) = e
  have he : (24 : Int) + e - 24 = e := by omega
  rw [he]
  exact max_eq_left hmin

theorem ofNat_eq_round (spec : Format) (m : Nat) (hm : m ≠ 0) :
    ofNat spec m = round spec .positive m 0 := by
  have hp : (0 : Int) < (m : Int) := by omega
  simp [Float.Model.UnpackedFloat.ofNat, Float.Model.UnpackedFloat.ofInt,
    Float.Model.UnpackedFloat.normalize, Int.compare_eq_gt.mpr hp]

theorem ofNat_exact24 (m : Nat) (hm : m ≠ 0) (hlog : m.log2 = 23) :
    ofNat f32Spec m = .finite .positive m 0 (Nat.pos_of_ne_zero hm) := by
  rw [ofNat_eq_round f32Spec m hm]
  exact round_normalized24 .positive m hm hlog 0 (by decide)

theorem unpack_pack_normal24 (s : Sign) (m : Nat) (e : Int)
    (hm : m ≠ 0) (hlog : m.log2 = 23)
    (hmin : -149 ≤ e) (hmax : e ≤ 104) :
    unpack f32Spec (pack f32Spec (.finite s m e (Nat.pos_of_ne_zero hm))) =
      .finite s m e (Nat.pos_of_ne_zero hm) := by
  apply FloatLib.Floats.Formats.BinaryInterchange.Model.unpack_pack_finite_normal
    f32Spec s m e hm
  · change m.log2 + 1 = 24
    omega
  · change 0 ≤ e + 127 + 23
    omega
  · change 0 < e + 127 + 23
    omega
  · change (e + 127 + 23).toNat + 1 < 256
    omega

theorem uint32_unpack_exact24 (n : UInt32)
    (hn : n.toNat ≠ 0) (hlog : n.toNat.log2 = 23) :
    n.toFloat32.toModel.unpack =
      .finite .positive n.toNat 0 (Nat.pos_of_ne_zero hn) := by
  change unpack f32Spec (pack f32Spec (ofNat f32Spec n.toNat)) = _
  rw [ofNat_exact24 n.toNat hn hlog]
  exact unpack_pack_normal24 .positive n.toNat 0 hn hlog (by decide) (by decide)

theorem mul_normal_scale_target (m : Nat) (hm : m ≠ 0)
    (hlog : m.log2 = 23) (e : Int) (hmin : -149 ≤ e) :
    f32Spec.targetExponent (totalExponent (m <<< 23) (e - 23)) = e := by
  unfold Format.targetExponent totalExponent
  rw [Nat.log2_shiftLeft_of_ne_zero _ _ hm, hlog]
  change max (46 + 1 + (e - 23) - 24) (-149) = e
  have he : (46 : Int) + 1 + (e - 23) - 24 = e := by omega
  rw [he]
  exact max_eq_left hmin

theorem mul_normal_scale_exact (s : Sign) (m : Nat)
    (hm : m ≠ 0) (hlog : m.log2 = 23) (e : Int) (hmin : -149 ≤ e) :
    Float.Model.UnpackedFloat.mul f32Spec
      (.finite .positive m 0 (Nat.pos_of_ne_zero hm))
      (.finite s (2 ^ 23) (e - 23) (by decide)) =
      .finite s m e (Nat.pos_of_ne_zero hm) := by
  have hsign : (.positive : Sign) * s = s := by cases s <;> rfl
  change roundWithAccuracy f32Spec (.positive * s) (m * 2 ^ 23)
    (0 + (e - 23)) .exact = _
  rw [hsign, zero_add]
  have hmul : m * 2 ^ 23 = m <<< 23 := by simp [Nat.shiftLeft_eq]
  rw [hmul]
  have htarget := mul_normal_scale_target m hm hlog e hmin
  have hle : e - 23 ≤ f32Spec.targetExponent
      (totalExponent (m <<< 23) (e - 23)) := by
    rw [htarget]
    omega
  rw [FloatLib.Floats.Formats.BinaryInterchange.Model.roundWithAccuracy_exact_eq_round_of_le_targetExponent
      f32Spec s (m <<< 23) (e - 23) hle]
  rw [FloatLib.Floats.Formats.BinaryInterchange.Model.round_shiftLeft
    f32Spec s m 23 e hm]
  exact round_normalized24 s m hm hlog e hmin

theorem uint32_mul_scale_toModel (n : UInt32) (scale : Float32) (s : Sign)
    (hn : n.toNat ≠ 0) (hlog : n.toNat.log2 = 23) (e : Int)
    (hmin : -149 ≤ e)
    (hscale : scale.toModel.unpack = .finite s (2 ^ 23) (e - 23) (by decide)) :
    (n.toFloat32 * scale).toModel =
      Float32.Model.pack (.finite s n.toNat e (Nat.pos_of_ne_zero hn)) := by
  change Float32.Model.pack (Float.Model.UnpackedFloat.mul f32Spec
    n.toFloat32.toModel.unpack scale.toModel.unpack) = _
  rw [uint32_unpack_exact24 n hn hlog, hscale,
    mul_normal_scale_exact s n.toNat hn hlog e hmin]

theorem uint32_mul_scale_eq_ofBits (u n : UInt32) (scale : Float32) (s : Sign)
    (hn : n.toNat ≠ 0) (hlog : n.toNat.log2 = 23) (e : Int)
    (hmin : -149 ≤ e)
    (hscale : scale.toModel.unpack = .finite s (2 ^ 23) (e - 23) (by decide))
    (hraw : unpack f32Spec u.toBitVec =
      .finite s n.toNat e (Nat.pos_of_ne_zero hn)) :
    n.toFloat32 * scale = Float32.ofBits u := by
  apply float32_eq_of_toModel_eq
  rw [uint32_mul_scale_toModel n scale s hn hlog e hmin hscale]
  change Float32.Model.pack (.finite s n.toNat e (Nat.pos_of_ne_zero hn)) =
    Float32.Model.pack (unpack f32Spec u.toBitVec)
  rw [hraw]

def scaleWord (u : UInt32) : UInt32 :=
  (((u >>> 23) &&& 256) <<< 23) ||| ((exponent u - 23) <<< 23)

def rawSign (u : UInt32) : Sign :=
  Sign.ofBitVec (unpackSign (spec := f32Spec) u.toBitVec)

theorem exponent_toNat (u : UInt32) :
    (exponent u).toNat = (u.toNat / 8388608) % 256 := by
  simp only [exponent, UInt32.toNat_and, UInt32.toNat_shiftRight]
  change (u.toNat >>> 23) &&& (2 ^ 8 - 1) = _
  rw [Nat.and_two_pow_sub_one_eq_mod, Nat.shiftRight_eq_div_pow]

theorem mantissa_toNat (u : UInt32) :
    (mantissa u).toNat = u.toNat % 8388608 + 8388608 := by
  simp only [mantissa, UInt32.toNat_or, UInt32.toNat_and]
  change (u.toNat &&& (2 ^ 23 - 1)) ||| 2 ^ 23 = _
  rw [Nat.and_two_pow_sub_one_eq_mod]
  rw [Nat.or_two_pow_eq_add_of_lt (n := 23)
    (Nat.mod_lt _ (by decide : 0 < 2 ^ 23))]

theorem mantissa_positive (u : UInt32) : 0 < (mantissa u).toNat := by
  rw [mantissa_toNat]
  omega

theorem mantissa_ne_zero (u : UInt32) : (mantissa u).toNat ≠ 0 := by
  have := mantissa_positive u
  omega

theorem mantissa_log2 (u : UInt32) : (mantissa u).toNat.log2 = 23 := by
  apply (Nat.log2_eq_iff (mantissa_ne_zero u)).2
  rw [mantissa_toNat]
  have h := Nat.mod_lt u.toNat (by decide : 0 < 8388608)
  constructor <;> omega

theorem unpackExponent_toNat (u : UInt32) :
    (unpackExponent (spec := f32Spec) u.toBitVec).toNat =
      (exponent u).toNat := by
  rw [exponent_toNat]
  simp [unpackExponent, f32Spec, BitVec.extractLsb'_toNat,
    Nat.shiftRight_eq_div_pow]

theorem unpackMantissa_toNat (u : UInt32) :
    (unpackMantissa (spec := f32Spec) u.toBitVec).toNat =
      u.toNat % 8388608 := by
  simp [unpackMantissa, f32Spec, BitVec.extractLsb'_toNat,
    Nat.shiftRight_eq_div_pow]

theorem unpackSign_toNat (u : UInt32) :
    (unpackSign (spec := f32Spec) u.toBitVec).toNat =
      u.toNat / 2147483648 := by
  have hu := u.toNat_lt
  simp only [unpackSign, BitVec.extractLsb'_toNat,
    UInt32.toNat_toBitVec, Nat.shiftRight_eq_div_pow]
  change (u.toNat / 2147483648) % 2 = _
  omega

theorem fullMantissa_toNat (u : UInt32) :
    (1#1 ++ unpackMantissa (spec := f32Spec) u.toBitVec).toNat =
      (mantissa u).toNat := by
  rw [BitVec.toNat_append,
    ← Nat.shiftLeft_add_eq_or_of_lt
      (unpackMantissa (spec := f32Spec) u.toBitVec).isLt]
  rw [unpackMantissa_toNat, mantissa_toNat]
  simp [Nat.shiftLeft_eq, Nat.add_comm]

theorem exponent_bounds (u : UInt32)
    (hlo : (24 : UInt32) ≤ exponent u)
    (hhi : exponent u ≤ (254 : UInt32)) :
    -126 ≤ ((exponent u).toNat : Int) - 150 ∧
      ((exponent u).toNat : Int) - 150 ≤ 104 := by
  change 24 ≤ (exponent u).toNat at hlo
  change (exponent u).toNat ≤ 254 at hhi
  omega

theorem raw_unpack_normal (u : UInt32)
    (hlo : (24 : UInt32) ≤ exponent u)
    (hhi : exponent u ≤ (254 : UInt32)) :
    unpack f32Spec u.toBitVec =
      .finite (rawSign u) (mantissa u).toNat
        (((exponent u).toNat : Int) - 150) (mantissa_positive u) := by
  have hlo' : 24 ≤ (exponent u).toNat := hlo
  have hhi' : (exponent u).toNat ≤ 254 := hhi
  have hnz : unpackExponent (spec := f32Spec) u.toBitVec ≠ 0#8 := by
    intro h
    have hn := congrArg BitVec.toNat h
    rw [unpackExponent_toNat] at hn
    change (exponent u).toNat = 0 at hn
    omega
  have htop : unpackExponent (spec := f32Spec) u.toBitVec ≠ -1#8 := by
    intro h
    have hn := congrArg BitVec.toNat h
    rw [unpackExponent_toNat] at hn
    change (exponent u).toNat = 255 at hn
    omega
  simpa only [Float.Model.UnpackedFloat.unpack, htop, hnz, ite_false, fullMantissa_toNat,
    unpackExponent_toNat, rawSign]

theorem nat_and_256_of_lt (n : Nat) (hn : n < 512) :
    n &&& 256 = n / 256 * 256 := by
  have hdiv : (n &&& 256) / 256 = n / 256 := by
    have h := Nat.and_div_two_pow (a := n) (b := 256) (n := 8)
    change (n &&& 256) / 256 = (n / 256) &&& 1 at h
    rw [h, Nat.and_one_is_mod]
    exact Nat.mod_eq_of_lt (by omega)
  have hmod : (n &&& 256) % 256 = 0 := by
    have h := Nat.and_mod_two_pow (a := n) (b := 256) (n := 8)
    simpa using h
  omega

theorem scaleWord_toNat (u : UInt32)
    (hlo : (24 : UInt32) ≤ exponent u)
    (hhi : exponent u ≤ (254 : UInt32)) :
    (scaleWord u).toNat =
      (u.toNat / 2147483648) * 2147483648 +
        ((exponent u).toNat - 23) * 8388608 := by
  have hu : u.toNat < 4294967296 := u.toNat_lt
  have hlo' : 24 ≤ (exponent u).toNat := hlo
  have hhi' : (exponent u).toNat ≤ 254 := hhi
  have hq : (u >>> 23).toNat = u.toNat / 8388608 := by
    simp [Nat.shiftRight_eq_div_pow]
  have hq_lt : (u >>> 23).toNat < 512 := by rw [hq]; omega
  have hs : (((u >>> 23) &&& 256)).toNat =
      (u.toNat / 2147483648) * 256 := by
    rw [UInt32.toNat_and]
    change (u >>> 23).toNat &&& 256 = _
    rw [nat_and_256_of_lt _ hq_lt, hq]
    omega
  have hl : ((((u >>> 23) &&& 256) <<< 23)).toNat =
      (u.toNat / 2147483648) * 2147483648 := by
    simp only [UInt32.toNat_shiftLeft, Nat.shiftLeft_eq]
    change ((((u >>> 23) &&& 256)).toNat * 8388608) % 4294967296 = _
    rw [hs]
    omega
  have hsub : (exponent u - 23).toNat = (exponent u).toNat - 23 := by
    exact UInt32.toNat_sub_of_le _ _ (show (23 : UInt32) ≤ exponent u by
      change 23 ≤ (exponent u).toNat
      omega)
  have hr : ((exponent u - 23) <<< 23).toNat =
      ((exponent u).toNat - 23) * 8388608 := by
    simp only [UInt32.toNat_shiftLeft, Nat.shiftLeft_eq]
    change ((exponent u - 23).toNat * 8388608) % 4294967296 = _
    rw [hsub]
    omega
  have hb : ((exponent u).toNat - 23) * 8388608 < 2 ^ 31 := by omega
  have hor := Nat.shiftLeft_add_eq_or_of_lt hb (u.toNat / 2147483648)
  simp only [Nat.shiftLeft_eq] at hor
  change (u.toNat / 2147483648) * 2147483648 +
      ((exponent u).toNat - 23) * 8388608 =
      ((u.toNat / 2147483648) * 2147483648) |||
        (((exponent u).toNat - 23) * 8388608) at hor
  unfold scaleWord
  rw [UInt32.toNat_or, hl, hr, ← hor]

theorem scale_unpack_fields (u : UInt32)
    (hlo : (24 : UInt32) ≤ exponent u)
    (hhi : exponent u ≤ (254 : UInt32)) :
    unpackSign (spec := f32Spec) (scaleWord u).toBitVec =
        unpackSign (spec := f32Spec) u.toBitVec ∧
      (unpackExponent (spec := f32Spec) (scaleWord u).toBitVec).toNat =
        (exponent u).toNat - 23 ∧
      unpackMantissa (spec := f32Spec) (scaleWord u).toBitVec = 0#23 := by
  have hu : u.toNat < 4294967296 := u.toNat_lt
  have hlo' : 24 ≤ (exponent u).toNat := hlo
  have hhi' : (exponent u).toNat ≤ 254 := hhi
  have hw := scaleWord_toNat u hlo hhi
  constructor
  · apply BitVec.eq_of_toNat_eq
    rw [unpackSign_toNat, unpackSign_toNat, hw]
    omega
  constructor
  · simp only [unpackExponent, BitVec.extractLsb'_toNat,
      UInt32.toNat_toBitVec, Nat.shiftRight_eq_div_pow]
    change ((scaleWord u).toNat / 8388608) % 256 = _
    rw [hw]
    omega
  · apply BitVec.eq_of_toNat_eq
    rw [unpackMantissa_toNat, hw]
    change ((u.toNat / 2147483648) * 2147483648 +
      ((exponent u).toNat - 23) * 8388608) % 8388608 = 0
    omega

theorem scale_raw_unpack_normal (u : UInt32)
    (hlo : (24 : UInt32) ≤ exponent u)
    (hhi : exponent u ≤ (254 : UInt32)) :
    unpack f32Spec (scaleWord u).toBitVec =
      .finite (rawSign u) (2 ^ 23)
        ((((exponent u).toNat : Int) - 150) - 23) (by decide) := by
  obtain ⟨hs, he, hm⟩ := scale_unpack_fields u hlo hhi
  have hlo' : 24 ≤ (exponent u).toNat := hlo
  have hhi' : (exponent u).toNat ≤ 254 := hhi
  have hnz : unpackExponent (spec := f32Spec) (scaleWord u).toBitVec ≠ 0#8 := by
    intro h
    have hn := congrArg BitVec.toNat h
    rw [he] at hn
    change (exponent u).toNat - 23 = 0 at hn
    omega
  have htop : unpackExponent (spec := f32Spec) (scaleWord u).toBitVec ≠ -1#8 := by
    intro h
    have hn := congrArg BitVec.toNat h
    rw [he] at hn
    change (exponent u).toNat - 23 = 255 at hn
    omega
  have he' : (((exponent u).toNat - 23 : Nat) : Int) - 150 =
      (((exponent u).toNat : Int) - 150) - 23 := by omega
  simp only [Float.Model.UnpackedFloat.unpack, htop, hnz, ite_false, hs, he, hm]
  change UnpackedFloat.finite (rawSign u) (2 ^ 23)
      ((((exponent u).toNat - 23 : Nat) : Int) - 150) _ = _
  rw [he']

theorem ofBits_unpack (u : UInt32) :
    (Float32.ofBits u).toModel.unpack = unpack f32Spec u.toBitVec := by
  change unpack f32Spec (pack f32Spec (unpack f32Spec u.toBitVec)) = _
  exact FloatLib.Floats.Formats.BinaryInterchange.Model.unpack_pack_unpack _ _

theorem scale_unpack_normal (u : UInt32)
    (hlo : (24 : UInt32) ≤ exponent u)
    (hhi : exponent u ≤ (254 : UInt32)) :
    (Float32.ofBits (scaleWord u)).toModel.unpack =
      .finite (rawSign u) (2 ^ 23)
        ((((exponent u).toNat : Int) - 150) - 23) (by decide) := by
  rw [ofBits_unpack]
  exact scale_raw_unpack_normal u hlo hhi

theorem table_index_lt (u : UInt32) : (u >>> 23).toNat < 512 := by
  have hu : u.toNat < 4294967296 := u.toNat_lt_size
  simp only [UInt32.toNat_shiftRight]
  change u.toNat >>> 23 < 512
  rw [Nat.shiftRight_eq_div_pow]
  change u.toNat / 8388608 < 512
  omega

theorem signedScaleTable_lookup (u : UInt32)
    (hlo : (24 : UInt32) ≤ exponent u)
    (hhi : exponent u ≤ (254 : UInt32)) :
    signedScaleTable.getD (u >>> 23).toNat zero32 =
      Float32.ofBits (scaleWord u) := by
  have hi := table_index_lt u
  have hg : (24 : UInt32) ≤ exponent u ∧ exponent u ≤ (254 : UInt32) := ⟨hlo, hhi⟩
  simp only [signedScaleTable, Array.getD_eq_getD_getElem?, Array.getElem?_ofFn,
    dif_pos hi, Option.getD_some, UInt32.ofNat_toNat]
  change Float32.ofBits
    (if (24 : UInt32) ≤ exponent u ∧ exponent u ≤ (254 : UInt32) then
      (((u >>> 23) &&& 256) <<< 23) ||| ((exponent u - 23) <<< 23)
    else ((u >>> 23) &&& 256) <<< 23) = _
  simp only [if_pos hg, scaleWord]

theorem reconstruct_normal (u : UInt32)
    (hlo : (24 : UInt32) ≤ exponent u)
    (hhi : exponent u ≤ (254 : UInt32)) :
    (mantissa u).toFloat32 * Float32.ofBits (scaleWord u) =
      Float32.ofBits u := by
  have he := (exponent_bounds u hlo hhi).1
  exact uint32_mul_scale_eq_ofBits u (mantissa u)
    (Float32.ofBits (scaleWord u)) (rawSign u)
    (mantissa_ne_zero u) (mantissa_log2 u)
    (((exponent u).toNat : Int) - 150) (by omega)
    (scale_unpack_normal u hlo hhi) (raw_unpack_normal u hlo hhi)

theorem fromBitsTable_eq_ofBits (u : UInt32) :
    fromBitsTable u = Float32.ofBits u := by
  by_cases hz : u = 0
  · subst u
    rfl
  · by_cases hg : (24 : UInt32) ≤ exponent u ∧ exponent u ≤ (254 : UInt32)
    · simp only [fromBitsTable, fromBitsTableWith, beq_iff_eq, hz, if_false,
        hg, if_true]
      rw [signedScaleTable_lookup u hg.1 hg.2]
      exact reconstruct_normal u hg.1 hg.2
    · simp [fromBitsTable, fromBitsTableWith, hz, hg]

theorem fromBitsTable_all :
    ∀ u : UInt32, fromBitsTable u = Float32.ofBits u :=
  fromBitsTable_eq_ofBits

theorem fromBitsTable_eq : fromBitsTable = Float32.ofBits := by
  funext u
  exact fromBitsTable_eq_ofBits u

end R2W03b
