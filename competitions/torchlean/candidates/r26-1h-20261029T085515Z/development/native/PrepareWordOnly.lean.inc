def prepare (raw : Array UInt32) : Prepared := Id.run do
  if raw.size > 1048576 then
    return ⟨raw, FloatArray.emptyWithCapacity 0, 0, 0, false, false⟩
  let mut low : UInt32 := 255
  let mut high : UInt32 := 0
  let mut valid := true
  let mut seen := false
  for word in raw do
    if rawExp word == 255 then valid := false
    else if rawMant word != 0 then
      let k := rawIdx word
      if k < low then low := k
      if high < k then high := k
      seen := true
  return ⟨raw, FloatArray.emptyWithCapacity 0,
    if seen then low else 0, if seen then high else 0, valid, seen⟩

