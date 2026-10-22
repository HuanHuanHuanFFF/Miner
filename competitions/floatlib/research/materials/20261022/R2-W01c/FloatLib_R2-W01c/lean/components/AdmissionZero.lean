import ContractTensor

namespace R2W01b

def magnitude (u : UInt32) : UInt32 :=
  u &&& 0x7fffffff

def fastOK (u : UInt32) : Bool :=
  let a := magnitude u
  decide (0x0bffffff ≤ a - 1) && decide (a < 0x7f800000)

def NormalBand (u : UInt32) : Prop :=
  0x0c000000 ≤ magnitude u ∧ magnitude u < 0x7f800000

theorem wrap_gate_iff (a : UInt32) :
    (decide (0x0bffffff ≤ a - 1) && decide (a < 0x7f800000)) = true ↔
      a = 0 ∨ (0x0c000000 ≤ a ∧ a < 0x7f800000) := by
  have ha := a.toNat_lt_size
  simp only [Bool.and_eq_true, decide_eq_true_eq, UInt32.le_iff_toNat_le,
    UInt32.lt_iff_toNat_lt, UInt32.toNat_sub, ← UInt32.toNat_inj]
  change a.toNat < 4294967296 at ha
  change
    (201326591 ≤ (4294967295 + a.toNat) % 4294967296 ∧
      a.toNat < 2139095040) ↔
    (a.toNat = 0 ∨ (201326592 ≤ a.toNat ∧ a.toNat < 2139095040))
  omega

theorem fastOK_iff (u : UInt32) :
    fastOK u = true ↔ magnitude u = 0 ∨ NormalBand u := by
  exact wrap_gate_iff (magnitude u)

theorem magnitude_toNat (u : UInt32) :
    (magnitude u).toNat = u.toNat % 2147483648 := by
  rw [magnitude, UInt32.toNat_and]
  change u.toNat &&& (2 ^ 31 - 1) = u.toNat % 2 ^ 31
  exact Nat.and_two_pow_sub_one_eq_mod u.toNat 31

theorem magnitude_zero_iff (u : UInt32) :
    magnitude u = 0 ↔ u = 0 ∨ u = 0x80000000 := by
  have hu := u.toNat_lt_size
  simp only [← UInt32.toNat_inj, magnitude_toNat]
  change u.toNat < 4294967296 at hu
  change
    u.toNat % 2147483648 = 0 ↔ u.toNat = 0 ∨ u.toNat = 2147483648
  omega

theorem fastOK_positive_zero : fastOK 0 = true := by
  decide

theorem fastOK_negative_zero : fastOK 0x80000000 = true := by
  decide

def tableIndex (u : UInt32) : UInt32 :=
  u >>> 23

def mantissa (u : UInt32) : UInt32 :=
  (u &&& 0x7fffff) ||| 0x800000

def scaleBits (j : UInt32) : UInt32 :=
  let e := j &&& 255
  let s := (j &&& 256) <<< 23
  if decide (24 ≤ e) && decide (e ≤ 254) then
    s ||| ((e - 23) <<< 23)
  else
    s

theorem tableIndex_toNat_lt (u : UInt32) :
    (tableIndex u).toNat < 512 := by
  have hu := u.toNat_lt_size
  rw [tableIndex, UInt32.toNat_shiftRight]
  change u.toNat >>> 23 < 512
  rw [Nat.shiftRight_eq_div_pow]
  change u.toNat < 4294967296 at hu
  change u.toNat / 8388608 < 512
  omega

def scaleTable : Array Float32 :=
  Array.ofFn fun j : Fin 512 => Float32.ofBits (scaleBits (UInt32.ofNat j.val))

theorem scaleTable_size : scaleTable.size = 512 := by
  simp only [scaleTable, Array.size_ofFn]

theorem scaleTable_entry (j : Fin 512) :
    scaleTable[j.val]'(by rw [scaleTable_size]; exact j.isLt) =
      Float32.ofBits (scaleBits (UInt32.ofNat j.val)) := by
  simp only [scaleTable, Array.getElem_ofFn]

def scaleAt (u : UInt32) : Float32 :=
  scaleTable[(tableIndex u).toNat]'(by
    rw [scaleTable_size]
    exact tableIndex_toNat_lt u)

theorem scaleAt_eq (u : UInt32) :
    scaleAt u = Float32.ofBits (scaleBits (tableIndex u)) := by
  simp only [scaleAt, scaleTable, Array.getElem_ofFn, UInt32.ofNat_toNat]

theorem zero_fields (u : UInt32) (h : magnitude u = 0) :
    (u = 0 ∧ tableIndex u = 0 ∧ mantissa u = 0x800000 ∧
      scaleBits (tableIndex u) = 0) ∨
    (u = 0x80000000 ∧ tableIndex u = 256 ∧ mantissa u = 0x800000 ∧
      scaleBits (tableIndex u) = 0x80000000) := by
  cases (magnitude_zero_iff u).mp h with
  | inl hu =>
    subst u
    left
    decide
  | inr hu =>
    subst u
    right
    decide

theorem scaleAt_positive_zero : scaleAt 0 = Float32.ofBits 0 := by
  rw [scaleAt_eq]
  exact congrArg Float32.ofBits (by decide : scaleBits (tableIndex 0) = 0)

theorem scaleAt_negative_zero :
    scaleAt 0x80000000 = Float32.ofBits 0x80000000 := by
  rw [scaleAt_eq]
  exact congrArg Float32.ofBits
    (by decide : scaleBits (tableIndex 0x80000000) = 0x80000000)

theorem zero_mantissa_conversion :
    (0x800000 : UInt32).toFloat32 = Float32.ofBits 0x4b000000 := by
  decide

def tableProduct (u : UInt32) : Float32 :=
  (mantissa u).toFloat32 * scaleAt u

theorem tableProduct_positive_zero : tableProduct 0 = Float32.ofBits 0 := by
  rw [tableProduct, scaleAt_positive_zero]
  decide

theorem tableProduct_negative_zero :
    tableProduct 0x80000000 = Float32.ofBits 0x80000000 := by
  rw [tableProduct, scaleAt_negative_zero]
  decide

theorem tableProduct_zero_eq (u : UInt32) (h : magnitude u = 0) :
    tableProduct u = Float32.ofBits u := by
  cases (magnitude_zero_iff u).mp h with
  | inl hu =>
    subst u
    exact tableProduct_positive_zero
  | inr hu =>
    subst u
    exact tableProduct_negative_zero

theorem tableProduct_zero_bits_eq (u : UInt32) (h : magnitude u = 0) :
    (tableProduct u).toBits = (Float32.ofBits u).toBits := by
  exact congrArg Float32.toBits (tableProduct_zero_eq u h)

theorem zero_ofBits_toBits (u : UInt32) (h : magnitude u = 0) :
    (Float32.ofBits u).toBits = u := by
  cases (magnitude_zero_iff u).mp h with
  | inl hu => subst u; decide
  | inr hu => subst u; decide

theorem tableProduct_zero_bits (u : UInt32) (h : magnitude u = 0) :
    (tableProduct u).toBits = u := by
  exact (tableProduct_zero_bits_eq u h).trans (zero_ofBits_toBits u h)

theorem float32_eq_of_toBits_eq {x y : Float32} (h : x.toBits = y.toBits) :
    x = y := by
  cases x with
  | ofModel xm =>
    cases y with
    | ofModel ym =>
      cases xm with
      | mk xb xv =>
        cases ym with
        | mk yb yv =>
          change xb = yb at h
          cases h
          rfl

theorem float32_ofBits_toBits (x : Float32) : Float32.ofBits x.toBits = x := by
  simpa only [FloatLib.Floats.ExecFloat.Binary.toFloat32,
    FloatLib.Floats.ExecFloat.Binary.toBits32_ofFloat32] using
    FloatLib.Floats.ExecFloat.Binary.toFloat32_ofFloat32 x

theorem float32_eq_of_raw_bits {x : Float32} {u : UInt32} (h : x.toBits = u) :
    x = Float32.ofBits u := by
  calc
    x = Float32.ofBits x.toBits := (float32_ofBits_toBits x).symm
    _ = Float32.ofBits u := congrArg Float32.ofBits h

theorem normal_value_of_bits
    (hNormalBits : ∀ u, NormalBand u →
      (tableProduct u).toBits = (Float32.ofBits u).toBits) :
    ∀ u, NormalBand u → tableProduct u = Float32.ofBits u := by
  intro u hn
  exact float32_eq_of_toBits_eq (hNormalBits u hn)

theorem normal_value_of_raw_bits
    (hNormalRawBits : ∀ u, NormalBand u → (tableProduct u).toBits = u) :
    ∀ u, NormalBand u → tableProduct u = Float32.ofBits u := by
  intro u hn
  exact float32_eq_of_raw_bits (hNormalRawBits u hn)

theorem tableProduct_of_fastOK
    (hNormal : ∀ u, NormalBand u → tableProduct u = Float32.ofBits u)
    (u : UInt32) (h : fastOK u = true) :
    tableProduct u = Float32.ofBits u := by
  cases (fastOK_iff u).mp h with
  | inl hz => exact tableProduct_zero_eq u hz
  | inr hn => exact hNormal u hn

def convert (u : UInt32) : Float32 :=
  if fastOK u then tableProduct u else Float32.ofBits u

theorem convert_zero_path (u : UInt32) (h : magnitude u = 0) :
    convert u = tableProduct u := by
  have hf : fastOK u = true := (fastOK_iff u).mpr (Or.inl h)
  rw [convert, if_pos hf]

theorem convert_fallback (u : UInt32) (h : fastOK u = false) :
    convert u = Float32.ofBits u := by
  simp [convert, h]

theorem convert_eq
    (hNormal : ∀ u, NormalBand u → tableProduct u = Float32.ofBits u)
    (u : UInt32) : convert u = Float32.ofBits u := by
  by_cases h : fastOK u = true
  · rw [convert, if_pos h]
    exact tableProduct_of_fastOK hNormal u h
  · rw [convert, if_neg h]

theorem convert_bits_eq
    (hNormal : ∀ u, NormalBand u → tableProduct u = Float32.ofBits u)
    (u : UInt32) : (convert u).toBits = (Float32.ofBits u).toBits := by
  exact congrArg Float32.toBits (convert_eq hNormal u)

theorem convert_eq_of_normal_bits
    (hNormalBits : ∀ u, NormalBand u →
      (tableProduct u).toBits = (Float32.ofBits u).toBits)
    (u : UInt32) : convert u = Float32.ofBits u := by
  exact convert_eq (normal_value_of_bits hNormalBits) u

theorem convert_eq_of_normal_raw_bits
    (hNormalRawBits : ∀ u, NormalBand u → (tableProduct u).toBits = u)
    (u : UInt32) : convert u = Float32.ofBits u := by
  exact convert_eq (normal_value_of_raw_bits hNormalRawBits) u

theorem replace_decoder {α : Sort _}
    (hNormal : ∀ u, NormalBand u → tableProduct u = Float32.ofBits u)
    (core : (UInt32 → Float32) → α) : core convert = core Float32.ofBits := by
  exact congrArg core (funext (convert_eq hNormal))

theorem foldl_convert_eq
    (hNormal : ∀ u, NormalBand u → tableProduct u = Float32.ofBits u)
    (xs : List UInt32) (step : Float32 → Float32 → Float32) (acc : Float32) :
    xs.foldl (fun z u => step z (convert u)) acc =
      xs.foldl (fun z u => step z (Float32.ofBits u)) acc := by
  induction xs generalizing acc with
  | nil => rfl
  | cons u us ih =>
    simp only [List.foldl_cons, convert_eq hNormal u]
    exact ih _

end R2W01b
