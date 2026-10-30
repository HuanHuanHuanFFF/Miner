import ContractExact

/- Storage-only proof preflight, NOT_COMPILED. This file is not a kernel.
   Pinned Lean4.34 runtime uses NaN checks in both bit transports.
   No floating arithmetic, custom unsafe definition, or extra axiom is used. -/
namespace Submission.R27RawTransport
open FloatLib.Floats FloatLib.Floats.Formats.BinaryInterchange

abbrev F64 := FloatFormat.binary64
abbrev raw (w : UInt64) : Model F64 := Model.ofBits w.toBitVec

theorem payload_exp_zero (w : UInt64) (h : w.toNat < 4503599627370496) :
    Model.expField (raw w) = 0 := by
  unfold Model.expField
  change ((w.toBitVec >>> 52) &&& BitVec.ofNat 64 2047).toNat = 0
  rw [BitVec.toNat_and, BitVec.toNat_ushiftRight]
  change (w.toNat >>> 52) &&& (2 ^ 11 - 1) = 0
  rw [Nat.and_two_pow_sub_one_eq_mod, Nat.shiftRight_eq_div_pow]
  have hd : w.toNat / 4503599627370496 = 0 := Nat.div_eq_of_lt h
  change (w.toNat / 4503599627370496) % 2048 = 0
  rw [hd]
  rfl

theorem payload_finite (w : UInt64) (h : w.toNat < 4503599627370496) :
    Model.isFinite (raw w) = true := by
  have he := payload_exp_zero w h
  have hf : raw w = Model.ofFields F64 (Model.signBit (raw w)) 0
      (Model.fracField (raw w)) := by
    simpa only [he] using (Model.ofFields_signBit_expField_fracField (raw w)).symm
  rw [hf]
  exact Model.isFinite_ofFields_ieee F64 (by decide) _ _ _ (by decide)

/-- Canonicality here follows directly from exponent0; no real or Dyadic bridge. -/
theorem payload_valid (w : UInt64) (h : w.toNat < 4503599627370496) :
    Float.Model.Format.binary64.Valid w.toBitVec := by
  constructor
  intro he _
  have hzero := Model.unpackExponent_toNat (raw w)
  rw [payload_exp_zero w h] at hzero
  have hones := congrArg BitVec.toNat he
  change (Float.Model.UnpackedFloat.unpackExponent
    (spec := Float.Model.Format.binary64) w.toBitVec).toNat = 0 at hzero
  change (Float.Model.UnpackedFloat.unpackExponent
    (spec := Float.Model.Format.binary64) w.toBitVec).toNat = 2047 at hones
  omega

/-- Generic actual Float bit transport: the pinned library already proves pack/unpack.
    This explicit validity input is discharged below from the actual payload bound. -/
theorem roundtrip_of_valid (w : UInt64)
    (h : Float.Model.Format.binary64.Valid w.toBitVec) :
    (Float.ofBits w).toBits = w := by
  apply UInt64.toNat_inj.mp
  change (UInt64.ofBitVec (Float.Model.UnpackedFloat.pack Float.Model.Format.binary64
    (Float.Model.UnpackedFloat.unpack Float.Model.Format.binary64 w.toBitVec))).toNat = w.toNat
  rw [Model.pack_unpack_of_valid Float.Model.Format.binary64 _ h]
  rfl

theorem payload_roundtrip (w : UInt64) (h : w.toNat < 4503599627370496) :
    (Float.ofBits w).toBits = w :=
  roundtrip_of_valid w (payload_valid w h)

/-- The runtime body uses public push, without converting through Array Float.
    The .data and map expressions below belong only to erased proofs. -/
@[specialize] def prepare {α : Type} (pack : α → UInt64) (xs : Array α) : FloatArray :=
  xs.foldl (fun acc x => acc.push (Float.ofBits (pack x)))
    (FloatArray.emptyWithCapacity xs.size)

private theorem push_data (a : FloatArray) (w : UInt64) :
    (a.push (Float.ofBits w)).data = a.data.push (Float.ofBits w) := by
  cases a
  rfl

private theorem fold_data {α : Type} (pack : α → UInt64) (xs : List α) (acc : FloatArray) :
    (xs.foldl (fun a x => a.push (Float.ofBits (pack x))) acc).data.toList =
      acc.data.toList ++ xs.map (fun x => Float.ofBits (pack x)) := by
  induction xs generalizing acc with
  | nil => simp only [List.foldl_nil, List.map_nil, List.append_nil]
  | cons x xs ih =>
    rw [List.foldl_cons, ih, push_data, Array.toList_push, List.map_cons]
    simp only [List.append_assoc, List.singleton_append]

theorem prepare_data {α : Type} (pack : α → UInt64) (xs : Array α) :
    (prepare pack xs).data = xs.map (fun x => Float.ofBits (pack x)) := by
  unfold prepare
  apply Array.toList_inj.mp
  rw [← Array.foldl_toList, fold_data, Array.toList_map]
  simp only [FloatArray.emptyWithCapacity, List.nil_append]

private theorem size_data (a : FloatArray) : a.size = a.data.size := by
  cases a
  rfl

private theorem getBang_data (a : FloatArray) (i : Nat) : a.get! i = a.data[i]! := by
  cases a
  rfl

theorem prepare_size {α : Type} (pack : α → UInt64) (xs : Array α) :
    (prepare pack xs).size = xs.size := by
  rw [size_data, prepare_data, Array.size_map]

theorem prepare_getBang_roundtrip {α : Type} (pack : α → UInt64) (xs : Array α)
    (hpack : ∀ x ∈ xs.toList, (pack x).toNat < 4503599627370496)
    (i : Nat) (hi : i < xs.size) :
    ((prepare pack xs).get! i).toBits = pack xs[i] := by
  rw [getBang_data, prepare_data]
  rw [getElem!_pos _ i (by simpa only [Array.size_map] using hi), Array.getElem_map]
  exact payload_roundtrip (pack xs[i]) (hpack xs[i] (Array.getElem_mem_toList hi))

theorem getBang_eq_get (a : FloatArray) (i : Nat) (h : i < a.size) :
    a.get! i = a.get i h := by
  cases a with
  | mk ds => exact getElem!_pos ds i h

/-- The actual USize getter and Nat getter reduce to the same public Array element.
    This says nothing about Nat-to-USize conversion outside its valid range. -/
theorem uget_eq_get (a : FloatArray) (i : USize) (h : i.toNat < a.size) :
    a.uget i h = a.get i.toNat h := by
  cases a
  rfl

@[inline] def loadNat (a : FloatArray) (i : Nat) (h : i < a.size) : UInt64 :=
  (a.get i h).toBits

@[inline] def load (a : FloatArray) (i : USize) (h : i.toNat < a.size) : UInt64 :=
  (a.uget i h).toBits

theorem prepare_loadNat {α : Type} (pack : α → UInt64) (xs : Array α)
    (hpack : ∀ x ∈ xs.toList, (pack x).toNat < 4503599627370496)
    (i : Nat) (hi : i < xs.size) :
    loadNat (prepare pack xs) i (by rw [prepare_size]; exact hi) = pack xs[i] := by
  have hsz : i < (prepare pack xs).size := by rw [prepare_size]; exact hi
  have hv := prepare_getBang_roundtrip pack xs hpack i hi
  rw [getBang_eq_get (prepare pack xs) i hsz] at hv
  exact hv

theorem prepare_load {α : Type} (pack : α → UInt64) (xs : Array α)
    (hpack : ∀ x ∈ xs.toList, (pack x).toNat < 4503599627370496)
    (i : USize) (hi : i.toNat < xs.size) :
    load (prepare pack xs) i (by rw [prepare_size]; exact hi) = pack xs[i.toNat] := by
  unfold load
  rw [uget_eq_get]
  exact prepare_loadNat pack xs hpack i.toNat hi

end Submission.R27RawTransport

