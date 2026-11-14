/- R24 constant-only dense storage. Float64 is STORAGE only; read narrows to
   Float32 before every original multiply/add. Runtime validity is checked once
   for all 512 constants against their original native raw words. -/
@[inline] def denseScaleCheckOne (f : Float32) : Bool :=
  f.toFloat.toFloat32.toBits == f.toBits

def denseScaleValid : Bool := scaleTable.all denseScaleCheckOne

def denseScaleTable : FloatArray := ⟨scaleTable.map Float32.toFloat⟩

theorem denseScaleTable_size : denseScaleTable.size = 512 := by
  simp only [denseScaleTable, FloatArray.size, Array.size_map, scaleTable_size]

theorem denseScaleFloat_eq {x y : Float32} (h : x.toBits = y.toBits) : x = y := by
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

theorem denseScaleRead_eq (h : denseScaleValid = true) (j : Nat) (hj : j < 512) :
    (denseScaleTable.get j (by rw [denseScaleTable_size]; exact hj)).toFloat32 =
      scaleTable[j]'(by rw [scaleTable_size]; exact hj) := by
  have hb : j < scaleTable.size := by rw [scaleTable_size]; exact hj
  have hc := (Array.all_eq_true.mp h) j hb
  have he : scaleTable[j].toFloat.toFloat32 = scaleTable[j] := by
    apply denseScaleFloat_eq
    simpa only [denseScaleCheckOne, beq_iff_eq] using hc
  simpa only [denseScaleTable, FloatArray.get, Array.getElem_map] using he

@[inline] def scaleAt (u : UInt32) : Float32 :=
  if h : denseScaleValid = true then
    (denseScaleTable.get (tableIndex u).toNat
      (by rw [denseScaleTable_size]; exact tableIndex_toNat_lt u)).toFloat32
  else scaleTable[(tableIndex u).toNat]'(by
    rw [scaleTable_size]
    exact tableIndex_toNat_lt u)

theorem scaleAt_eq (u : UInt32) :
    scaleAt u = Float32.ofBits (scaleBits (tableIndex u)) := by
  unfold scaleAt
  split
  · rename_i h
    rw [denseScaleRead_eq h]
    simp only [scaleTable, Array.getElem_ofFn, UInt32.ofNat_toNat]
  · simp only [scaleTable, Array.getElem_ofFn, UInt32.ofNat_toNat]
