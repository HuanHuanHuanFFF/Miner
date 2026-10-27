/- R19 locally authored checked static scale-table representation.
   Lean 4.34 FloatArray stores Float64. The opaque widening/narrowing bridge is
   validated once for all 512 static source entries; a failed check retains
   the original boxed table. No input-dependent precomputation is hidden. -/
namespace R19CompactScales
open R2W01b

def packed : FloatArray := ⟨scaleTable.map Float32.toFloat⟩

theorem packed_size : packed.size = 512 := by
  simp only [packed, FloatArray.size, Array.size_map, scaleTable_size]

@[inline] def checkOne (x : Float32) : Bool :=
  (x.toFloat.toFloat32).toBits == x.toBits

def valid : Bool := scaleTable.all checkOne

theorem checked_entry (h : valid = true) (j : Fin 512) :
    ((packed.get j.val (by rw [packed_size]; exact j.isLt)).toFloat32) =
      scaleTable[j.val]'(by rw [scaleTable_size]; exact j.isLt) := by
  have hj : j.val < scaleTable.size := by rw [scaleTable_size]; exact j.isLt
  have hall : scaleTable.all checkOne = true := h
  have hone := (Array.all_eq_true.mp hall) j.val hj
  apply R2W01b.float32_eq_of_toBits_eq
  simpa [checkOne, packed, FloatArray.get, FloatArray.size] using hone

@[inline] def scale (u : UInt32) : Float32 :=
  (packed.get (tableIndex u).toNat (by
    rw [packed_size]
    exact tableIndex_toNat_lt u)).toFloat32

theorem scale_eq (h : valid = true) (u : UInt32) : scale u = scaleAt u := by
  exact checked_entry h ⟨(tableIndex u).toNat, tableIndex_toNat_lt u⟩

@[inline] def convert (u : UInt32) : Float32 :=
  if fastOK u then (mantissa u).toFloat32 * scale u else Float32.ofBits u

theorem convert_eq (h : valid = true) (u : UInt32) :
    convert u = R2W01b.convert u := by
  simp only [convert, scale_eq h, R2W01b.convert, tableProduct]

@[inline] def addNative (x y : UInt32) : Float32 :=
  if valid then convert x + convert y
  else R2W01b.convert x + R2W01b.convert y

theorem addNative_eq (x y : UInt32) :
    addNative x y = R2W01b.convert x + R2W01b.convert y := by
  unfold addNative
  split
  · rename_i h
    simp only [convert_eq h]
  · rfl

@[inline] def mulNative (x y : UInt32) : Float32 :=
  if valid then convert x * convert y
  else R2W01b.convert x * R2W01b.convert y

theorem mulNative_eq (x y : UInt32) :
    mulNative x y = R2W01b.convert x * R2W01b.convert y := by
  unfold mulNative
  split
  · rename_i h
    simp only [convert_eq h]
  · rfl

end R19CompactScales

