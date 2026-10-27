
namespace R7LowTableDecode

@[inline] def lowNormalDecode (u : UInt32) : Float32 :=
  R2W01b.tableProduct (u + (0x10000000 : UInt32)) * constantFromTable u

theorem lowNormalDecode_eq_proved (u : UInt32) :
    lowNormalDecode u = R7W13.lowNormalDecode u := by
  simp only [lowNormalDecode, R7W13.lowNormalDecode, constantFromTable_eq]

@[inline] def convert (u : UInt32) : Float32 :=
  let a := R2W01b.magnitude u
  if decide (0x0bffffff ≤ a - 1) then
    if decide (a < 0x7f800000) then
      R2W01b.tableProduct u
    else Float32.ofBits u
  else
    if decide (0x00800000 ≤ a) then lowNormalDecode u
    else Float32.ofBits u

theorem convert_eq_wrapper (u : UInt32) : convert u = R7W13b.wrapper u := by
  simp only [convert, R7W13b.wrapper, lowNormalDecode_eq_proved]

theorem convert_eq (u : UInt32) : convert u = Float32.ofBits u :=
  (convert_eq_wrapper u).trans (R7W13b.wrapper_eq_ofBits u)

end R7LowTableDecode
