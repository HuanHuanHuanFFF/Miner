import ContractExact

/- Storage-only API probe. No floating addition/multiplication and no candidate kernel. -/
namespace Submission.R27RawPayloadCarrier
open FloatLib.Floats FloatLib.Floats.Formats.BinaryInterchange

abbrev F64 := FloatFormat.binary64
abbrev raw (w : UInt64) : Model F64 := Model.ofBits w.toBitVec
abbrev native (x : Float) : Model F64 := Model.ofFloatModel x.toModel

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

/-- Same finite canonicalization argument as accepted R27 native_ofBits;
the narrowed payload excludes all logical NaN payload collapse. -/
theorem payload_native (w : UInt64) (h : w.toNat < 4503599627370496) :
    native (Float.ofBits w) = raw w := by
  obtain ⟨d, hd⟩ := Model.exists_toDyadic?_of_isFinite (payload_finite w h)
  have hc : Model.IsModelCanonical (raw w) := by
    constructor
    intro he hm
    have hnan : Model.toModel (raw w) = Float.Model.UnpackedFloat.notANumber := by
      simp only [Model.toModel, Float.Model.UnpackedFloat.unpack, he, hm, ite_true, ite_false]
    rw [Model.toDyadic?_ieee_eq_model F64 (by decide), hnan] at hd
    simp [Model.unpackedToDyadic?] at hd
  change Model.ofFloatModel
    (ExecFloat.Binary.toFloat (ExecFloat.Binary.ofBits64 w)).toModel = raw w
  rw [ExecFloat.Binary.toModel_toFloat_eq, Model.ofFloatModel_toFloatModel]
  exact Model.canonicalizeModel_eq_self _ hc

theorem payload_roundtrip (w : UInt64) (h : w.toNat < 4503599627370496) :
    (Float.ofBits w).toBits = w := by
  apply UInt64.toNat_inj.mp
  have hb := congrArg (fun x : Model F64 => x.bits.toNat) (payload_native w h)
  change (Float.ofBits w).toBits.toNat = w.toNat at hb
  exact hb

/-- Real public push/fold construction. The map below appears only in its proof. -/
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

private theorem get_data (a : FloatArray) (i : Nat) : a.get! i = a.data[i]! := by
  cases a
  rfl

theorem prepare_size {α : Type} (pack : α → UInt64) (xs : Array α) :
    (prepare pack xs).size = xs.size := by
  rw [size_data, prepare_data, Array.size_map]

/-- The actual encoder must prove the bound, or derive it from its real guard.
This is not a new global assumption for an eventual twelve-kernel contract. -/
theorem prepare_get_roundtrip {α : Type} (pack : α → UInt64) (xs : Array α)
    (hpack : ∀ x ∈ xs.toList, (pack x).toNat < 4503599627370496)
    (i : Nat) (hi : i < xs.size) :
    ((prepare pack xs).get! i).toBits = pack xs[i] := by
  rw [get_data, prepare_data]
  rw [getElem!_pos _ i (by simpa only [Array.size_map] using hi), Array.getElem_map]
  exact payload_roundtrip (pack xs[i]) (hpack xs[i] (Array.getElem_mem_toList hi))

end Submission.R27RawPayloadCarrier
